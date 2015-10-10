/*
 * main.c
 *
 *  Created on: Apr 28, 2011
 *      Author: Sebastiaan Pierrot
 *
 *  HID prank, this module sends an caps lock to the host every 2 minutes.
 *  revision: 1.01
 *
 *   based on HID-Test by Christian Starkjohann
 *
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: usbconfig-prototype.h 785 2010-05-30 17:57:07Z cs $
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

#include "hid.h"
#include "usbdrv.h"
#include "oddebug.h"
#include <util/delay.h>

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

static uchar   reportBuffer[2];    /* buffer for HID reports */
static uchar    idleRate;           /* in 4 ms units */

const PROGMEM char usbHidReportDescriptor[35] = { /* USB report descriptor */
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
};
/* We use a simplifed keyboard report descriptor which does not support the
 * boot protocol. We don't allow setting status LEDs and we only allow one
 * simultaneous key press (except modifiers). We can therefore use short
 * 2 byte input reports.
 * The report descriptor has been created with usb.org's "HID Descriptor Tool"
 * which can be downloaded from http://www.usb.org/developers/hidpage/.
 * Redundant entries (such as LOGICAL_MINIMUM and USAGE_PAGE) have been omitted
 * for the second INPUT item.
 */


static void setupDevice(){
	uchar   i;

    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */

    i = 0;
    while(--i){             /* fake USB disconnect for > 250 ms */
	    wdt_reset();
	    _delay_ms(1);
    }

    usbDeviceConnect();
	
    TCCR1 = 0x0f;           /* select clock: 16.5M/1k -> overflow rate = 16.5M/256k = 62.94 Hz */

}

uchar	usbFunctionSetup(uchar data[8])
{
usbRequest_t    *rq = (void *)data;

    usbMsgPtr = reportBuffer;
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* class request type */
        if(rq->bRequest == USBRQ_HID_GET_REPORT){  /* wValue: ReportType (highbyte), ReportID (lowbyte) */
            /* we only have one report type, so don't look at wValue */
        	reportBuffer[0]=0;  //no extra keys
        	reportBuffer[1]=HID_CAPS_LOCK;
            return sizeof(reportBuffer);
        }else if(rq->bRequest == USBRQ_HID_GET_IDLE){
            usbMsgPtr = &idleRate;
            return 1;
        }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
            idleRate = rq->wValue.bytes[1];
        }
    }else{
        /* no vendor specific requests implemented */
    }
	return 0;
}


int main(){
	unsigned char tick=0;
	unsigned char keyUp=0;

	wdt_enable(WDTO_2S);
	setupDevice();

	usbInit();
	sei();
	while(1){
		wdt_reset();
		usbPoll();

		if(TIFR & _BV(TOV1)){   //6 seconds
			TIFR = _BV(TOV1);
			tick++;
		}
		if(tick>=100 && usbInterruptIsReady()){//every 60 seconds a report
			reportBuffer[0]=0;  //no extra modifiers
			if(!keyUp){
				keyUp=1;
				reportBuffer[1]=HID_CAPS_LOCK;
			}else{
				tick=0;
				keyUp=0;
				reportBuffer[1]=0;
			}
			usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
		}
	}
	return 0;
}

