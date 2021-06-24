<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB Compaq iPAQ driver
 *
 *	Copyright (C) 2001 - 2002
 *	    Ganesh Varadarajan <ganesh@veritas.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

#घोषणा KP_RETRIES	100

#घोषणा DRIVER_AUTHOR "Ganesh Varadarajan <ganesh@veritas.com>"
#घोषणा DRIVER_DESC "USB PocketPC PDA driver"

अटल पूर्णांक connect_retries = KP_RETRIES;
अटल पूर्णांक initial_रुको;

/* Function prototypes क्रम an ipaq */
अटल पूर्णांक  ipaq_खोलो(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port);
अटल पूर्णांक ipaq_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds);
अटल पूर्णांक  ipaq_startup(काष्ठा usb_serial *serial);

अटल स्थिर काष्ठा usb_device_id ipaq_id_table[] = अणु
	अणु USB_DEVICE(0x0104, 0x00BE) पूर्ण, /* Socket USB Sync */
	अणु USB_DEVICE(0x03F0, 0x1016) पूर्ण, /* HP USB Sync */
	अणु USB_DEVICE(0x03F0, 0x1116) पूर्ण, /* HP USB Sync 1611 */
	अणु USB_DEVICE(0x03F0, 0x1216) पूर्ण, /* HP USB Sync 1612 */
	अणु USB_DEVICE(0x03F0, 0x2016) पूर्ण, /* HP USB Sync 1620 */
	अणु USB_DEVICE(0x03F0, 0x2116) पूर्ण, /* HP USB Sync 1621 */
	अणु USB_DEVICE(0x03F0, 0x2216) पूर्ण, /* HP USB Sync 1622 */
	अणु USB_DEVICE(0x03F0, 0x3016) पूर्ण, /* HP USB Sync 1630 */
	अणु USB_DEVICE(0x03F0, 0x3116) पूर्ण, /* HP USB Sync 1631 */
	अणु USB_DEVICE(0x03F0, 0x3216) पूर्ण, /* HP USB Sync 1632 */
	अणु USB_DEVICE(0x03F0, 0x4016) पूर्ण, /* HP USB Sync 1640 */
	अणु USB_DEVICE(0x03F0, 0x4116) पूर्ण, /* HP USB Sync 1641 */
	अणु USB_DEVICE(0x03F0, 0x4216) पूर्ण, /* HP USB Sync 1642 */
	अणु USB_DEVICE(0x03F0, 0x5016) पूर्ण, /* HP USB Sync 1650 */
	अणु USB_DEVICE(0x03F0, 0x5116) पूर्ण, /* HP USB Sync 1651 */
	अणु USB_DEVICE(0x03F0, 0x5216) पूर्ण, /* HP USB Sync 1652 */
	अणु USB_DEVICE(0x0409, 0x00D5) पूर्ण, /* NEC USB Sync */
	अणु USB_DEVICE(0x0409, 0x00D6) पूर्ण, /* NEC USB Sync */
	अणु USB_DEVICE(0x0409, 0x00D7) पूर्ण, /* NEC USB Sync */
	अणु USB_DEVICE(0x0409, 0x8024) पूर्ण, /* NEC USB Sync */
	अणु USB_DEVICE(0x0409, 0x8025) पूर्ण, /* NEC USB Sync */
	अणु USB_DEVICE(0x043E, 0x9C01) पूर्ण, /* LGE USB Sync */
	अणु USB_DEVICE(0x045E, 0x00CE) पूर्ण, /* Microsoft USB Sync */
	अणु USB_DEVICE(0x045E, 0x0400) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0401) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0402) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0403) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0404) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0405) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0406) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0407) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0408) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0409) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x040A) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x040B) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x040C) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x040D) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x040E) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x040F) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0410) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0411) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0412) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0413) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0414) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0415) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0416) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0417) पूर्ण, /* Winकरोws Powered Pocket PC 2002 */
	अणु USB_DEVICE(0x045E, 0x0432) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0433) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0434) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0435) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0436) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0437) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0438) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0439) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x043A) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x043B) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x043C) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x043D) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x043E) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x043F) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0440) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0441) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0442) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0443) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0444) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0445) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0446) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0447) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0448) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0449) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x044A) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x044B) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x044C) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x044D) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x044E) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x044F) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0450) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0451) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0452) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0453) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0454) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0455) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0456) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0457) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0458) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0459) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x045A) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x045B) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x045C) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x045D) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x045E) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x045F) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0460) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0461) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0462) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0463) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0464) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0465) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0466) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0467) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0468) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0469) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x046A) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x046B) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x046C) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x046D) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x046E) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x046F) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0470) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0471) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0472) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0473) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0474) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0475) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0476) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0477) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0478) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x0479) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x047A) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x047B) पूर्ण, /* Winकरोws Powered Pocket PC 2003 */
	अणु USB_DEVICE(0x045E, 0x04C8) पूर्ण, /* Winकरोws Powered Smartphone 2002 */
	अणु USB_DEVICE(0x045E, 0x04C9) पूर्ण, /* Winकरोws Powered Smartphone 2002 */
	अणु USB_DEVICE(0x045E, 0x04CA) पूर्ण, /* Winकरोws Powered Smartphone 2002 */
	अणु USB_DEVICE(0x045E, 0x04CB) पूर्ण, /* Winकरोws Powered Smartphone 2002 */
	अणु USB_DEVICE(0x045E, 0x04CC) पूर्ण, /* Winकरोws Powered Smartphone 2002 */
	अणु USB_DEVICE(0x045E, 0x04CD) पूर्ण, /* Winकरोws Powered Smartphone 2002 */
	अणु USB_DEVICE(0x045E, 0x04CE) पूर्ण, /* Winकरोws Powered Smartphone 2002 */
	अणु USB_DEVICE(0x045E, 0x04D7) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04D8) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04D9) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04DA) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04DB) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04DC) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04DD) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04DE) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04DF) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E0) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E1) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E2) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E3) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E4) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E5) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E6) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E7) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E8) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04E9) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x045E, 0x04EA) पूर्ण, /* Winकरोws Powered Smartphone 2003 */
	अणु USB_DEVICE(0x049F, 0x0003) पूर्ण, /* Compaq iPAQ USB Sync */
	अणु USB_DEVICE(0x049F, 0x0032) पूर्ण, /* Compaq iPAQ USB Sync */
	अणु USB_DEVICE(0x04A4, 0x0014) पूर्ण, /* Hitachi USB Sync */
	अणु USB_DEVICE(0x04AD, 0x0301) पूर्ण, /* USB Sync 0301 */
	अणु USB_DEVICE(0x04AD, 0x0302) पूर्ण, /* USB Sync 0302 */
	अणु USB_DEVICE(0x04AD, 0x0303) पूर्ण, /* USB Sync 0303 */
	अणु USB_DEVICE(0x04AD, 0x0306) पूर्ण, /* GPS Pocket PC USB Sync */
	अणु USB_DEVICE(0x04B7, 0x0531) पूर्ण, /* MyGuide 7000 XL USB Sync */
	अणु USB_DEVICE(0x04C5, 0x1058) पूर्ण, /* FUJITSU USB Sync */
	अणु USB_DEVICE(0x04C5, 0x1079) पूर्ण, /* FUJITSU USB Sync */
	अणु USB_DEVICE(0x04DA, 0x2500) पूर्ण, /* Panasonic USB Sync */
	अणु USB_DEVICE(0x04DD, 0x9102) पूर्ण, /* SHARP WS003SH USB Modem */
	अणु USB_DEVICE(0x04DD, 0x9121) पूर्ण, /* SHARP WS004SH USB Modem */
	अणु USB_DEVICE(0x04DD, 0x9123) पूर्ण, /* SHARP WS007SH USB Modem */
	अणु USB_DEVICE(0x04DD, 0x9151) पूर्ण, /* SHARP S01SH USB Modem */
	अणु USB_DEVICE(0x04DD, 0x91AC) पूर्ण, /* SHARP WS011SH USB Modem */
	अणु USB_DEVICE(0x04E8, 0x5F00) पूर्ण, /* Samsung NEXiO USB Sync */
	अणु USB_DEVICE(0x04E8, 0x5F01) पूर्ण, /* Samsung NEXiO USB Sync */
	अणु USB_DEVICE(0x04E8, 0x5F02) पूर्ण, /* Samsung NEXiO USB Sync */
	अणु USB_DEVICE(0x04E8, 0x5F03) पूर्ण, /* Samsung NEXiO USB Sync */
	अणु USB_DEVICE(0x04E8, 0x5F04) पूर्ण, /* Samsung NEXiO USB Sync */
	अणु USB_DEVICE(0x04E8, 0x6611) पूर्ण, /* Samsung MITs USB Sync */
	अणु USB_DEVICE(0x04E8, 0x6613) पूर्ण, /* Samsung MITs USB Sync */
	अणु USB_DEVICE(0x04E8, 0x6615) पूर्ण, /* Samsung MITs USB Sync */
	अणु USB_DEVICE(0x04E8, 0x6617) पूर्ण, /* Samsung MITs USB Sync */
	अणु USB_DEVICE(0x04E8, 0x6619) पूर्ण, /* Samsung MITs USB Sync */
	अणु USB_DEVICE(0x04E8, 0x661B) पूर्ण, /* Samsung MITs USB Sync */
	अणु USB_DEVICE(0x04E8, 0x662E) पूर्ण, /* Samsung MITs USB Sync */
	अणु USB_DEVICE(0x04E8, 0x6630) पूर्ण, /* Samsung MITs USB Sync */
	अणु USB_DEVICE(0x04E8, 0x6632) पूर्ण, /* Samsung MITs USB Sync */
	अणु USB_DEVICE(0x04f1, 0x3011) पूर्ण, /* JVC USB Sync */
	अणु USB_DEVICE(0x04F1, 0x3012) पूर्ण, /* JVC USB Sync */
	अणु USB_DEVICE(0x0502, 0x1631) पूर्ण, /* c10 Series */
	अणु USB_DEVICE(0x0502, 0x1632) पूर्ण, /* c20 Series */
	अणु USB_DEVICE(0x0502, 0x16E1) पूर्ण, /* Acer n10 Handheld USB Sync */
	अणु USB_DEVICE(0x0502, 0x16E2) पूर्ण, /* Acer n20 Handheld USB Sync */
	अणु USB_DEVICE(0x0502, 0x16E3) पूर्ण, /* Acer n30 Handheld USB Sync */
	अणु USB_DEVICE(0x0536, 0x01A0) पूर्ण, /* HHP PDT */
	अणु USB_DEVICE(0x0543, 0x0ED9) पूर्ण, /* ViewSonic Color Pocket PC V35 */
	अणु USB_DEVICE(0x0543, 0x1527) पूर्ण, /* ViewSonic Color Pocket PC V36 */
	अणु USB_DEVICE(0x0543, 0x1529) पूर्ण, /* ViewSonic Color Pocket PC V37 */
	अणु USB_DEVICE(0x0543, 0x152B) पूर्ण, /* ViewSonic Color Pocket PC V38 */
	अणु USB_DEVICE(0x0543, 0x152E) पूर्ण, /* ViewSonic Pocket PC */
	अणु USB_DEVICE(0x0543, 0x1921) पूर्ण, /* ViewSonic Communicator Pocket PC */
	अणु USB_DEVICE(0x0543, 0x1922) पूर्ण, /* ViewSonic Smartphone */
	अणु USB_DEVICE(0x0543, 0x1923) पूर्ण, /* ViewSonic Pocket PC V30 */
	अणु USB_DEVICE(0x05E0, 0x2000) पूर्ण, /* Symbol USB Sync */
	अणु USB_DEVICE(0x05E0, 0x2001) पूर्ण, /* Symbol USB Sync 0x2001 */
	अणु USB_DEVICE(0x05E0, 0x2002) पूर्ण, /* Symbol USB Sync 0x2002 */
	अणु USB_DEVICE(0x05E0, 0x2003) पूर्ण, /* Symbol USB Sync 0x2003 */
	अणु USB_DEVICE(0x05E0, 0x2004) पूर्ण, /* Symbol USB Sync 0x2004 */
	अणु USB_DEVICE(0x05E0, 0x2005) पूर्ण, /* Symbol USB Sync 0x2005 */
	अणु USB_DEVICE(0x05E0, 0x2006) पूर्ण, /* Symbol USB Sync 0x2006 */
	अणु USB_DEVICE(0x05E0, 0x2007) पूर्ण, /* Symbol USB Sync 0x2007 */
	अणु USB_DEVICE(0x05E0, 0x2008) पूर्ण, /* Symbol USB Sync 0x2008 */
	अणु USB_DEVICE(0x05E0, 0x2009) पूर्ण, /* Symbol USB Sync 0x2009 */
	अणु USB_DEVICE(0x05E0, 0x200A) पूर्ण, /* Symbol USB Sync 0x200A */
	अणु USB_DEVICE(0x067E, 0x1001) पूर्ण, /* Intermec Mobile Computer */
	अणु USB_DEVICE(0x07CF, 0x2001) पूर्ण, /* CASIO USB Sync 2001 */
	अणु USB_DEVICE(0x07CF, 0x2002) पूर्ण, /* CASIO USB Sync 2002 */
	अणु USB_DEVICE(0x07CF, 0x2003) पूर्ण, /* CASIO USB Sync 2003 */
	अणु USB_DEVICE(0x0930, 0x0700) पूर्ण, /* TOSHIBA USB Sync 0700 */
	अणु USB_DEVICE(0x0930, 0x0705) पूर्ण, /* TOSHIBA Pocket PC e310 */
	अणु USB_DEVICE(0x0930, 0x0706) पूर्ण, /* TOSHIBA Pocket PC e740 */
	अणु USB_DEVICE(0x0930, 0x0707) पूर्ण, /* TOSHIBA Pocket PC e330 Series */
	अणु USB_DEVICE(0x0930, 0x0708) पूर्ण, /* TOSHIBA Pocket PC e350 Series */
	अणु USB_DEVICE(0x0930, 0x0709) पूर्ण, /* TOSHIBA Pocket PC e750 Series */
	अणु USB_DEVICE(0x0930, 0x070A) पूर्ण, /* TOSHIBA Pocket PC e400 Series */
	अणु USB_DEVICE(0x0930, 0x070B) पूर्ण, /* TOSHIBA Pocket PC e800 Series */
	अणु USB_DEVICE(0x094B, 0x0001) पूर्ण, /* Linkup Systems USB Sync */
	अणु USB_DEVICE(0x0960, 0x0065) पूर्ण, /* BCOM USB Sync 0065 */
	अणु USB_DEVICE(0x0960, 0x0066) पूर्ण, /* BCOM USB Sync 0066 */
	अणु USB_DEVICE(0x0960, 0x0067) पूर्ण, /* BCOM USB Sync 0067 */
	अणु USB_DEVICE(0x0961, 0x0010) पूर्ण, /* Portatec USB Sync */
	अणु USB_DEVICE(0x099E, 0x0052) पूर्ण, /* Trimble GeoExplorer */
	अणु USB_DEVICE(0x099E, 0x4000) पूर्ण, /* TDS Data Collector */
	अणु USB_DEVICE(0x0B05, 0x4200) पूर्ण, /* ASUS USB Sync */
	अणु USB_DEVICE(0x0B05, 0x4201) पूर्ण, /* ASUS USB Sync */
	अणु USB_DEVICE(0x0B05, 0x4202) पूर्ण, /* ASUS USB Sync */
	अणु USB_DEVICE(0x0B05, 0x420F) पूर्ण, /* ASUS USB Sync */
	अणु USB_DEVICE(0x0B05, 0x9200) पूर्ण, /* ASUS USB Sync */
	अणु USB_DEVICE(0x0B05, 0x9202) पूर्ण, /* ASUS USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x00CE) पूर्ण, /* HTC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x00CF) पूर्ण, /* HTC USB Modem */
	अणु USB_DEVICE(0x0BB4, 0x0A01) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A02) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A03) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A04) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A05) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A06) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A07) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A08) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A09) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A0A) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A0B) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A0C) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A0D) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A0E) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A0F) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A10) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A11) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A12) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A13) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A14) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A15) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A16) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A17) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A18) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A19) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A1A) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A1B) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A1C) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A1D) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A1E) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A1F) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A20) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A21) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A22) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A23) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A24) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A25) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A26) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A27) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A28) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A29) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A2A) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A2B) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A2C) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A2D) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A2E) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A2F) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A30) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A31) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A32) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A33) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A34) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A35) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A36) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A37) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A38) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A39) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A3A) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A3B) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A3C) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A3D) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A3E) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A3F) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A40) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A41) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A42) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A43) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A44) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A45) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A46) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A47) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A48) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A49) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A4A) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A4B) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A4C) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A4D) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A4E) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A4F) पूर्ण, /* PocketPC USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A50) पूर्ण, /* HTC SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A51) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A52) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A53) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A54) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A55) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A56) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A57) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A58) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A59) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A5A) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A5B) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A5C) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A5D) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A5E) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A5F) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A60) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A61) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A62) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A63) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A64) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A65) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A66) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A67) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A68) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A69) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A6A) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A6B) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A6C) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A6D) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A6E) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A6F) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A70) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A71) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A72) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A73) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A74) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A75) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A76) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A77) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A78) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A79) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A7A) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A7B) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A7C) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A7D) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A7E) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A7F) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A80) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A81) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A82) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A83) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A84) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A85) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A86) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A87) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A88) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A89) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A8A) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A8B) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A8C) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A8D) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A8E) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A8F) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A90) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A91) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A92) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A93) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A94) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A95) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A96) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A97) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A98) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A99) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A9A) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A9B) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A9C) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A9D) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A9E) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0A9F) पूर्ण, /* SmartPhone USB Sync */
	अणु USB_DEVICE(0x0BB4, 0x0BCE) पूर्ण, /* "High Tech Computer Corp" */
	अणु USB_DEVICE(0x0BF8, 0x1001) पूर्ण, /* Fujitsu Siemens Computers USB Sync */
	अणु USB_DEVICE(0x0C44, 0x03A2) पूर्ण, /* Motorola iDEN Smartphone */
	अणु USB_DEVICE(0x0C8E, 0x6000) पूर्ण, /* Cesscom Luxian Series */
	अणु USB_DEVICE(0x0CAD, 0x9001) पूर्ण, /* Motorola PowerPad Pocket PC Device */
	अणु USB_DEVICE(0x0F4E, 0x0200) पूर्ण, /* Freeकरोm Scientअगरic USB Sync */
	अणु USB_DEVICE(0x0F98, 0x0201) पूर्ण, /* Cyberbank USB Sync */
	अणु USB_DEVICE(0x0FB8, 0x3001) पूर्ण, /* Wistron USB Sync */
	अणु USB_DEVICE(0x0FB8, 0x3002) पूर्ण, /* Wistron USB Sync */
	अणु USB_DEVICE(0x0FB8, 0x3003) पूर्ण, /* Wistron USB Sync */
	अणु USB_DEVICE(0x0FB8, 0x4001) पूर्ण, /* Wistron USB Sync */
	अणु USB_DEVICE(0x1066, 0x00CE) पूर्ण, /* E-TEN USB Sync */
	अणु USB_DEVICE(0x1066, 0x0300) पूर्ण, /* E-TEN P3XX Pocket PC */
	अणु USB_DEVICE(0x1066, 0x0500) पूर्ण, /* E-TEN P5XX Pocket PC */
	अणु USB_DEVICE(0x1066, 0x0600) पूर्ण, /* E-TEN P6XX Pocket PC */
	अणु USB_DEVICE(0x1066, 0x0700) पूर्ण, /* E-TEN P7XX Pocket PC */
	अणु USB_DEVICE(0x1114, 0x0001) पूर्ण, /* Psion Teklogix Sync 753x */
	अणु USB_DEVICE(0x1114, 0x0004) पूर्ण, /* Psion Teklogix Sync netBookPro */
	अणु USB_DEVICE(0x1114, 0x0006) पूर्ण, /* Psion Teklogix Sync 7525 */
	अणु USB_DEVICE(0x1182, 0x1388) पूर्ण, /* VES USB Sync */
	अणु USB_DEVICE(0x11D9, 0x1002) पूर्ण, /* Rugged Pocket PC 2003 */
	अणु USB_DEVICE(0x11D9, 0x1003) पूर्ण, /* Rugged Pocket PC 2003 */
	अणु USB_DEVICE(0x1231, 0xCE01) पूर्ण, /* USB Sync 03 */
	अणु USB_DEVICE(0x1231, 0xCE02) पूर्ण, /* USB Sync 03 */
	अणु USB_DEVICE(0x1690, 0x0601) पूर्ण, /* Askey USB Sync */
	अणु USB_DEVICE(0x22B8, 0x4204) पूर्ण, /* Motorola MPx200 Smartphone */
	अणु USB_DEVICE(0x22B8, 0x4214) पूर्ण, /* Motorola MPc GSM */
	अणु USB_DEVICE(0x22B8, 0x4224) पूर्ण, /* Motorola MPx220 Smartphone */
	अणु USB_DEVICE(0x22B8, 0x4234) पूर्ण, /* Motorola MPc CDMA */
	अणु USB_DEVICE(0x22B8, 0x4244) पूर्ण, /* Motorola MPx100 Smartphone */
	अणु USB_DEVICE(0x3340, 0x011C) पूर्ण, /* Mio DigiWalker PPC StrongARM */
	अणु USB_DEVICE(0x3340, 0x0326) पूर्ण, /* Mio DigiWalker 338 */
	अणु USB_DEVICE(0x3340, 0x0426) पूर्ण, /* Mio DigiWalker 338 */
	अणु USB_DEVICE(0x3340, 0x043A) पूर्ण, /* Mio DigiWalker USB Sync */
	अणु USB_DEVICE(0x3340, 0x051C) पूर्ण, /* MiTAC USB Sync 528 */
	अणु USB_DEVICE(0x3340, 0x053A) पूर्ण, /* Mio DigiWalker SmartPhone USB Sync */
	अणु USB_DEVICE(0x3340, 0x071C) पूर्ण, /* MiTAC USB Sync */
	अणु USB_DEVICE(0x3340, 0x0B1C) पूर्ण, /* Generic PPC StrongARM */
	अणु USB_DEVICE(0x3340, 0x0E3A) पूर्ण, /* Generic PPC USB Sync */
	अणु USB_DEVICE(0x3340, 0x0F1C) पूर्ण, /* Itautec USB Sync */
	अणु USB_DEVICE(0x3340, 0x0F3A) पूर्ण, /* Generic SmartPhone USB Sync */
	अणु USB_DEVICE(0x3340, 0x1326) पूर्ण, /* Itautec USB Sync */
	अणु USB_DEVICE(0x3340, 0x191C) पूर्ण, /* YAKUMO USB Sync */
	अणु USB_DEVICE(0x3340, 0x2326) पूर्ण, /* Vobis USB Sync */
	अणु USB_DEVICE(0x3340, 0x3326) पूर्ण, /* MEDION Winodws Moble USB Sync */
	अणु USB_DEVICE(0x3708, 0x20CE) पूर्ण, /* Legend USB Sync */
	अणु USB_DEVICE(0x3708, 0x21CE) पूर्ण, /* Lenovo USB Sync */
	अणु USB_DEVICE(0x4113, 0x0210) पूर्ण, /* Mobile Media Technology USB Sync */
	अणु USB_DEVICE(0x4113, 0x0211) पूर्ण, /* Mobile Media Technology USB Sync */
	अणु USB_DEVICE(0x4113, 0x0400) पूर्ण, /* Mobile Media Technology USB Sync */
	अणु USB_DEVICE(0x4113, 0x0410) पूर्ण, /* Mobile Media Technology USB Sync */
	अणु USB_DEVICE(0x413C, 0x4001) पूर्ण, /* Dell Axim USB Sync */
	अणु USB_DEVICE(0x413C, 0x4002) पूर्ण, /* Dell Axim USB Sync */
	अणु USB_DEVICE(0x413C, 0x4003) पूर्ण, /* Dell Axim USB Sync */
	अणु USB_DEVICE(0x413C, 0x4004) पूर्ण, /* Dell Axim USB Sync */
	अणु USB_DEVICE(0x413C, 0x4005) पूर्ण, /* Dell Axim USB Sync */
	अणु USB_DEVICE(0x413C, 0x4006) पूर्ण, /* Dell Axim USB Sync */
	अणु USB_DEVICE(0x413C, 0x4007) पूर्ण, /* Dell Axim USB Sync */
	अणु USB_DEVICE(0x413C, 0x4008) पूर्ण, /* Dell Axim USB Sync */
	अणु USB_DEVICE(0x413C, 0x4009) पूर्ण, /* Dell Axim USB Sync */
	अणु USB_DEVICE(0x4505, 0x0010) पूर्ण, /* Smartphone */
	अणु USB_DEVICE(0x5E04, 0xCE00) पूर्ण, /* SAGEM Wireless Assistant */
	अणु पूर्ण                             /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, ipaq_id_table);


/* All of the device info needed क्रम the Compaq iPAQ */
अटल काष्ठा usb_serial_driver ipaq_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"ipaq",
	पूर्ण,
	.description =		"PocketPC PDA",
	.id_table =		ipaq_id_table,
	.bulk_in_size =		256,
	.bulk_out_size =	256,
	.खोलो =			ipaq_खोलो,
	.attach =		ipaq_startup,
	.calc_num_ports =	ipaq_calc_num_ports,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&ipaq_device, शून्य
पूर्ण;

अटल पूर्णांक ipaq_खोलो(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial	*serial = port->serial;
	पूर्णांक			result = 0;
	पूर्णांक			retries = connect_retries;

	msleep(1000*initial_रुको);

	/*
	 * Send out control message observed in win98 snअगरfs. Not sure what
	 * it करोes, but from empirical observations, it seems that the device
	 * will start the chat sequence once one of these messages माला_लो
	 * through. Since this has a reasonably high failure rate, we retry
	 * several बार.
	 */
	जबतक (retries) अणु
		retries--;
		result = usb_control_msg(serial->dev,
				usb_sndctrlpipe(serial->dev, 0), 0x22, 0x21,
				0x1, 0, शून्य, 0, 100);
		अगर (!result)
			अवरोध;

		msleep(1000);
	पूर्ण
	अगर (!retries && result) अणु
		dev_err(&port->dev, "%s - failed doing control urb, error %d\n",
							__func__, result);
		वापस result;
	पूर्ण

	वापस usb_serial_generic_खोलो(tty, port);
पूर्ण

अटल पूर्णांक ipaq_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	/*
	 * Some of the devices in ipaq_id_table[] are composite, and we
	 * shouldn't bind to all the पूर्णांकerfaces. This test will rule out
	 * some obviously invalid possibilities.
	 */
	अगर (epds->num_bulk_in == 0 || epds->num_bulk_out == 0)
		वापस -ENODEV;

	/*
	 * A few devices have four endpoपूर्णांकs, seemingly Yakuma devices, and
	 * we need the second pair.
	 */
	अगर (epds->num_bulk_in > 1 && epds->num_bulk_out > 1) अणु
		epds->bulk_in[0] = epds->bulk_in[1];
		epds->bulk_out[0] = epds->bulk_out[1];
	पूर्ण

	/*
	 * Other devices have 3 endpoपूर्णांकs, but we only use the first bulk in
	 * and out endpoपूर्णांकs.
	 */
	epds->num_bulk_in = 1;
	epds->num_bulk_out = 1;

	वापस 1;
पूर्ण

अटल पूर्णांक ipaq_startup(काष्ठा usb_serial *serial)
अणु
	अगर (serial->dev->actconfig->desc.bConfigurationValue != 1) अणु
		/*
		 * FIXME: HP iPaq rx3715, possibly others, have 1 config that
		 * is labeled as 2
		 */

		dev_err(&serial->dev->dev, "active config #%d != 1 ??\n",
			serial->dev->actconfig->desc.bConfigurationValue);
		वापस -ENODEV;
	पूर्ण

	वापस usb_reset_configuration(serial->dev);
पूर्ण

module_usb_serial_driver(serial_drivers, ipaq_id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

module_param(connect_retries, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(connect_retries,
		"Maximum number of connect retries (one second each)");

module_param(initial_रुको, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(initial_रुको,
		"Time to wait before attempting a connection (in seconds)");
