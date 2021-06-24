<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm Serial USB driver
 *
 *	Copyright (c) 2008 QUALCOMM Incorporated.
 *	Copyright (c) 2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 *	Copyright (c) 2009 Novell Inc.
 */

#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/slab.h>
#समावेश "usb-wwan.h"

#घोषणा DRIVER_AUTHOR "Qualcomm Inc"
#घोषणा DRIVER_DESC "Qualcomm USB Serial driver"

#घोषणा QUECTEL_EC20_PID	0x9215

/* standard device layouts supported by this driver */
क्रमागत qcserial_layouts अणु
	QCSERIAL_G2K = 0,	/* Gobi 2000 */
	QCSERIAL_G1K = 1,	/* Gobi 1000 */
	QCSERIAL_SWI = 2,	/* Sierra Wireless */
	QCSERIAL_HWI = 3,	/* Huawei */
पूर्ण;

#घोषणा DEVICE_G1K(v, p) \
	USB_DEVICE(v, p), .driver_info = QCSERIAL_G1K
#घोषणा DEVICE_SWI(v, p) \
	USB_DEVICE(v, p), .driver_info = QCSERIAL_SWI
#घोषणा DEVICE_HWI(v, p) \
	USB_DEVICE(v, p), .driver_info = QCSERIAL_HWI

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	/* Gobi 1000 devices */
	अणुDEVICE_G1K(0x05c6, 0x9211)पूर्ण,	/* Acer Gobi QDL device */
	अणुDEVICE_G1K(0x05c6, 0x9212)पूर्ण,	/* Acer Gobi Modem Device */
	अणुDEVICE_G1K(0x03f0, 0x1f1d)पूर्ण,	/* HP un2400 Gobi Modem Device */
	अणुDEVICE_G1K(0x03f0, 0x201d)पूर्ण,	/* HP un2400 Gobi QDL Device */
	अणुDEVICE_G1K(0x04da, 0x250d)पूर्ण,	/* Panasonic Gobi Modem device */
	अणुDEVICE_G1K(0x04da, 0x250c)पूर्ण,	/* Panasonic Gobi QDL device */
	अणुDEVICE_G1K(0x413c, 0x8172)पूर्ण,	/* Dell Gobi Modem device */
	अणुDEVICE_G1K(0x413c, 0x8171)पूर्ण,	/* Dell Gobi QDL device */
	अणुDEVICE_G1K(0x1410, 0xa001)पूर्ण,	/* Novatel/Verizon USB-1000 */
	अणुDEVICE_G1K(0x1410, 0xa002)पूर्ण,	/* Novatel Gobi Modem device */
	अणुDEVICE_G1K(0x1410, 0xa003)पूर्ण,	/* Novatel Gobi Modem device */
	अणुDEVICE_G1K(0x1410, 0xa004)पूर्ण,	/* Novatel Gobi Modem device */
	अणुDEVICE_G1K(0x1410, 0xa005)पूर्ण,	/* Novatel Gobi Modem device */
	अणुDEVICE_G1K(0x1410, 0xa006)पूर्ण,	/* Novatel Gobi Modem device */
	अणुDEVICE_G1K(0x1410, 0xa007)पूर्ण,	/* Novatel Gobi Modem device */
	अणुDEVICE_G1K(0x1410, 0xa008)पूर्ण,	/* Novatel Gobi QDL device */
	अणुDEVICE_G1K(0x0b05, 0x1776)पूर्ण,	/* Asus Gobi Modem device */
	अणुDEVICE_G1K(0x0b05, 0x1774)पूर्ण,	/* Asus Gobi QDL device */
	अणुDEVICE_G1K(0x19d2, 0xfff3)पूर्ण,	/* ONDA Gobi Modem device */
	अणुDEVICE_G1K(0x19d2, 0xfff2)पूर्ण,	/* ONDA Gobi QDL device */
	अणुDEVICE_G1K(0x1557, 0x0a80)पूर्ण,	/* OQO Gobi QDL device */
	अणुDEVICE_G1K(0x05c6, 0x9001)पूर्ण,   /* Generic Gobi Modem device */
	अणुDEVICE_G1K(0x05c6, 0x9002)पूर्ण,	/* Generic Gobi Modem device */
	अणुDEVICE_G1K(0x05c6, 0x9202)पूर्ण,	/* Generic Gobi Modem device */
	अणुDEVICE_G1K(0x05c6, 0x9203)पूर्ण,	/* Generic Gobi Modem device */
	अणुDEVICE_G1K(0x05c6, 0x9222)पूर्ण,	/* Generic Gobi Modem device */
	अणुDEVICE_G1K(0x05c6, 0x9008)पूर्ण,	/* Generic Gobi QDL device */
	अणुDEVICE_G1K(0x05c6, 0x9009)पूर्ण,	/* Generic Gobi Modem device */
	अणुDEVICE_G1K(0x05c6, 0x9201)पूर्ण,	/* Generic Gobi QDL device */
	अणुDEVICE_G1K(0x05c6, 0x9221)पूर्ण,	/* Generic Gobi QDL device */
	अणुDEVICE_G1K(0x05c6, 0x9231)पूर्ण,	/* Generic Gobi QDL device */
	अणुDEVICE_G1K(0x1f45, 0x0001)पूर्ण,	/* Unknown Gobi QDL device */
	अणुDEVICE_G1K(0x1bc7, 0x900e)पूर्ण,	/* Telit Gobi QDL device */

	/* Gobi 2000 devices */
	अणुUSB_DEVICE(0x1410, 0xa010)पूर्ण,	/* Novatel Gobi 2000 QDL device */
	अणुUSB_DEVICE(0x1410, 0xa011)पूर्ण,	/* Novatel Gobi 2000 QDL device */
	अणुUSB_DEVICE(0x1410, 0xa012)पूर्ण,	/* Novatel Gobi 2000 QDL device */
	अणुUSB_DEVICE(0x1410, 0xa013)पूर्ण,	/* Novatel Gobi 2000 QDL device */
	अणुUSB_DEVICE(0x1410, 0xa014)पूर्ण,	/* Novatel Gobi 2000 QDL device */
	अणुUSB_DEVICE(0x413c, 0x8185)पूर्ण,	/* Dell Gobi 2000 QDL device (N0218, VU936) */
	अणुUSB_DEVICE(0x413c, 0x8186)पूर्ण,	/* Dell Gobi 2000 Modem device (N0218, VU936) */
	अणुUSB_DEVICE(0x05c6, 0x9208)पूर्ण,	/* Generic Gobi 2000 QDL device */
	अणुUSB_DEVICE(0x05c6, 0x920b)पूर्ण,	/* Generic Gobi 2000 Modem device */
	अणुUSB_DEVICE(0x05c6, 0x9224)पूर्ण,	/* Sony Gobi 2000 QDL device (N0279, VU730) */
	अणुUSB_DEVICE(0x05c6, 0x9225)पूर्ण,	/* Sony Gobi 2000 Modem device (N0279, VU730) */
	अणुUSB_DEVICE(0x05c6, 0x9244)पूर्ण,	/* Samsung Gobi 2000 QDL device (VL176) */
	अणुUSB_DEVICE(0x05c6, 0x9245)पूर्ण,	/* Samsung Gobi 2000 Modem device (VL176) */
	अणुUSB_DEVICE(0x03f0, 0x241d)पूर्ण,	/* HP Gobi 2000 QDL device (VP412) */
	अणुUSB_DEVICE(0x03f0, 0x251d)पूर्ण,	/* HP Gobi 2000 Modem device (VP412) */
	अणुUSB_DEVICE(0x05c6, 0x9214)पूर्ण,	/* Acer Gobi 2000 QDL device (VP413) */
	अणुUSB_DEVICE(0x05c6, 0x9215)पूर्ण,	/* Acer Gobi 2000 Modem device (VP413) */
	अणुUSB_DEVICE(0x05c6, 0x9264)पूर्ण,	/* Asus Gobi 2000 QDL device (VR305) */
	अणुUSB_DEVICE(0x05c6, 0x9265)पूर्ण,	/* Asus Gobi 2000 Modem device (VR305) */
	अणुUSB_DEVICE(0x05c6, 0x9234)पूर्ण,	/* Top Global Gobi 2000 QDL device (VR306) */
	अणुUSB_DEVICE(0x05c6, 0x9235)पूर्ण,	/* Top Global Gobi 2000 Modem device (VR306) */
	अणुUSB_DEVICE(0x05c6, 0x9274)पूर्ण,	/* iRex Technologies Gobi 2000 QDL device (VR307) */
	अणुUSB_DEVICE(0x05c6, 0x9275)पूर्ण,	/* iRex Technologies Gobi 2000 Modem device (VR307) */
	अणुUSB_DEVICE(0x1199, 0x9000)पूर्ण,	/* Sierra Wireless Gobi 2000 QDL device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9001)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9002)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9003)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9004)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9005)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9006)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9007)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9008)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9009)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x900a)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुUSB_DEVICE(0x1199, 0x9011)पूर्ण,   /* Sierra Wireless Gobi 2000 Modem device (MC8305) */
	अणुUSB_DEVICE(0x16d8, 0x8001)पूर्ण,	/* CMDTech Gobi 2000 QDL device (VU922) */
	अणुUSB_DEVICE(0x16d8, 0x8002)पूर्ण,	/* CMDTech Gobi 2000 Modem device (VU922) */
	अणुUSB_DEVICE(0x05c6, 0x9204)पूर्ण,	/* Gobi 2000 QDL device */
	अणुUSB_DEVICE(0x05c6, 0x9205)पूर्ण,	/* Gobi 2000 Modem device */

	/* Gobi 3000 devices */
	अणुUSB_DEVICE(0x03f0, 0x371d)पूर्ण,	/* HP un2430 Gobi 3000 QDL */
	अणुUSB_DEVICE(0x05c6, 0x920c)पूर्ण,	/* Gobi 3000 QDL */
	अणुUSB_DEVICE(0x05c6, 0x920d)पूर्ण,	/* Gobi 3000 Composite */
	अणुUSB_DEVICE(0x1410, 0xa020)पूर्ण,   /* Novatel Gobi 3000 QDL */
	अणुUSB_DEVICE(0x1410, 0xa021)पूर्ण,	/* Novatel Gobi 3000 Composite */
	अणुUSB_DEVICE(0x413c, 0x8193)पूर्ण,	/* Dell Gobi 3000 QDL */
	अणुUSB_DEVICE(0x413c, 0x8194)पूर्ण,	/* Dell Gobi 3000 Composite */
	अणुUSB_DEVICE(0x413c, 0x81a6)पूर्ण,	/* Dell DW5570 QDL (MC8805) */
	अणुUSB_DEVICE(0x1199, 0x68a4)पूर्ण,	/* Sierra Wireless QDL */
	अणुUSB_DEVICE(0x1199, 0x68a5)पूर्ण,	/* Sierra Wireless Modem */
	अणुUSB_DEVICE(0x1199, 0x68a8)पूर्ण,	/* Sierra Wireless QDL */
	अणुUSB_DEVICE(0x1199, 0x68a9)पूर्ण,	/* Sierra Wireless Modem */
	अणुUSB_DEVICE(0x1199, 0x9010)पूर्ण,	/* Sierra Wireless Gobi 3000 QDL */
	अणुUSB_DEVICE(0x1199, 0x9012)पूर्ण,	/* Sierra Wireless Gobi 3000 QDL */
	अणुUSB_DEVICE(0x1199, 0x9013)पूर्ण,	/* Sierra Wireless Gobi 3000 Modem device (MC8355) */
	अणुUSB_DEVICE(0x1199, 0x9014)पूर्ण,	/* Sierra Wireless Gobi 3000 QDL */
	अणुUSB_DEVICE(0x1199, 0x9015)पूर्ण,	/* Sierra Wireless Gobi 3000 Modem device */
	अणुUSB_DEVICE(0x1199, 0x9018)पूर्ण,	/* Sierra Wireless Gobi 3000 QDL */
	अणुUSB_DEVICE(0x1199, 0x9019)पूर्ण,	/* Sierra Wireless Gobi 3000 Modem device */
	अणुUSB_DEVICE(0x1199, 0x901b)पूर्ण,	/* Sierra Wireless MC7770 */
	अणुUSB_DEVICE(0x12D1, 0x14F0)पूर्ण,	/* Sony Gobi 3000 QDL */
	अणुUSB_DEVICE(0x12D1, 0x14F1)पूर्ण,	/* Sony Gobi 3000 Composite */
	अणुUSB_DEVICE(0x0AF0, 0x8120)पूर्ण,	/* Option GTM681W */

	/* non-Gobi Sierra Wireless devices */
	अणुDEVICE_SWI(0x03f0, 0x4e1d)पूर्ण,	/* HP lt4111 LTE/EV-DO/HSPA+ Gobi 4G Module */
	अणुDEVICE_SWI(0x0f3d, 0x68a2)पूर्ण,	/* Sierra Wireless MC7700 */
	अणुDEVICE_SWI(0x114f, 0x68a2)पूर्ण,	/* Sierra Wireless MC7750 */
	अणुDEVICE_SWI(0x1199, 0x68a2)पूर्ण,	/* Sierra Wireless MC7710 */
	अणुDEVICE_SWI(0x1199, 0x68c0)पूर्ण,	/* Sierra Wireless MC7304/MC7354 */
	अणुDEVICE_SWI(0x1199, 0x901c)पूर्ण,	/* Sierra Wireless EM7700 */
	अणुDEVICE_SWI(0x1199, 0x901e)पूर्ण,	/* Sierra Wireless EM7355 QDL */
	अणुDEVICE_SWI(0x1199, 0x901f)पूर्ण,	/* Sierra Wireless EM7355 */
	अणुDEVICE_SWI(0x1199, 0x9040)पूर्ण,	/* Sierra Wireless Modem */
	अणुDEVICE_SWI(0x1199, 0x9041)पूर्ण,	/* Sierra Wireless MC7305/MC7355 */
	अणुDEVICE_SWI(0x1199, 0x9051)पूर्ण,	/* Netgear AirCard 340U */
	अणुDEVICE_SWI(0x1199, 0x9053)पूर्ण,	/* Sierra Wireless Modem */
	अणुDEVICE_SWI(0x1199, 0x9054)पूर्ण,	/* Sierra Wireless Modem */
	अणुDEVICE_SWI(0x1199, 0x9055)पूर्ण,	/* Netgear AirCard 341U */
	अणुDEVICE_SWI(0x1199, 0x9056)पूर्ण,	/* Sierra Wireless Modem */
	अणुDEVICE_SWI(0x1199, 0x9060)पूर्ण,	/* Sierra Wireless Modem */
	अणुDEVICE_SWI(0x1199, 0x9061)पूर्ण,	/* Sierra Wireless Modem */
	अणुDEVICE_SWI(0x1199, 0x9062)पूर्ण,	/* Sierra Wireless EM7305 QDL */
	अणुDEVICE_SWI(0x1199, 0x9063)पूर्ण,	/* Sierra Wireless EM7305 */
	अणुDEVICE_SWI(0x1199, 0x9070)पूर्ण,	/* Sierra Wireless MC74xx */
	अणुDEVICE_SWI(0x1199, 0x9071)पूर्ण,	/* Sierra Wireless MC74xx */
	अणुDEVICE_SWI(0x1199, 0x9078)पूर्ण,	/* Sierra Wireless EM74xx */
	अणुDEVICE_SWI(0x1199, 0x9079)पूर्ण,	/* Sierra Wireless EM74xx */
	अणुDEVICE_SWI(0x1199, 0x907a)पूर्ण,	/* Sierra Wireless EM74xx QDL */
	अणुDEVICE_SWI(0x1199, 0x907b)पूर्ण,	/* Sierra Wireless EM74xx */
	अणुDEVICE_SWI(0x1199, 0x9090)पूर्ण,	/* Sierra Wireless EM7565 QDL */
	अणुDEVICE_SWI(0x1199, 0x9091)पूर्ण,	/* Sierra Wireless EM7565 */
	अणुDEVICE_SWI(0x413c, 0x81a2)पूर्ण,	/* Dell Wireless 5806 Gobi(TM) 4G LTE Mobile Broadband Card */
	अणुDEVICE_SWI(0x413c, 0x81a3)पूर्ण,	/* Dell Wireless 5570 HSPA+ (42Mbps) Mobile Broadband Card */
	अणुDEVICE_SWI(0x413c, 0x81a4)पूर्ण,	/* Dell Wireless 5570e HSPA+ (42Mbps) Mobile Broadband Card */
	अणुDEVICE_SWI(0x413c, 0x81a8)पूर्ण,	/* Dell Wireless 5808 Gobi(TM) 4G LTE Mobile Broadband Card */
	अणुDEVICE_SWI(0x413c, 0x81a9)पूर्ण,	/* Dell Wireless 5808e Gobi(TM) 4G LTE Mobile Broadband Card */
	अणुDEVICE_SWI(0x413c, 0x81b1)पूर्ण,	/* Dell Wireless 5809e Gobi(TM) 4G LTE Mobile Broadband Card */
	अणुDEVICE_SWI(0x413c, 0x81b3)पूर्ण,	/* Dell Wireless 5809e Gobi(TM) 4G LTE Mobile Broadband Card (rev3) */
	अणुDEVICE_SWI(0x413c, 0x81b5)पूर्ण,	/* Dell Wireless 5811e QDL */
	अणुDEVICE_SWI(0x413c, 0x81b6)पूर्ण,	/* Dell Wireless 5811e QDL */
	अणुDEVICE_SWI(0x413c, 0x81cb)पूर्ण,	/* Dell Wireless 5816e QDL */
	अणुDEVICE_SWI(0x413c, 0x81cc)पूर्ण,	/* Dell Wireless 5816e */
	अणुDEVICE_SWI(0x413c, 0x81cf)पूर्ण,   /* Dell Wireless 5819 */
	अणुDEVICE_SWI(0x413c, 0x81d0)पूर्ण,   /* Dell Wireless 5819 */
	अणुDEVICE_SWI(0x413c, 0x81d1)पूर्ण,   /* Dell Wireless 5818 */
	अणुDEVICE_SWI(0x413c, 0x81d2)पूर्ण,   /* Dell Wireless 5818 */

	/* Huawei devices */
	अणुDEVICE_HWI(0x03f0, 0x581d)पूर्ण,	/* HP lt4112 LTE/HSPA+ Gobi 4G Modem (Huawei me906e) */

	अणु पूर्ण				/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल पूर्णांक handle_quectel_ec20(काष्ठा device *dev, पूर्णांक अगरnum)
अणु
	पूर्णांक altsetting = 0;

	/*
	 * Quectel EC20 Mini PCIe LTE module layout:
	 * 0: DM/DIAG (use libqcdm from ModemManager क्रम communication)
	 * 1: NMEA
	 * 2: AT-capable modem port
	 * 3: Modem पूर्णांकerface
	 * 4: NDIS
	 */
	चयन (अगरnum) अणु
	हाल 0:
		dev_dbg(dev, "Quectel EC20 DM/DIAG interface found\n");
		अवरोध;
	हाल 1:
		dev_dbg(dev, "Quectel EC20 NMEA GPS interface found\n");
		अवरोध;
	हाल 2:
	हाल 3:
		dev_dbg(dev, "Quectel EC20 Modem port found\n");
		अवरोध;
	हाल 4:
		/* Don't claim the QMI/net पूर्णांकerface */
		altsetting = -1;
		अवरोध;
	पूर्ण

	वापस altsetting;
पूर्ण

अटल पूर्णांक qcprobe(काष्ठा usb_serial *serial, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकf = serial->पूर्णांकerface->cur_altsetting;
	काष्ठा device *dev = &serial->dev->dev;
	पूर्णांक retval = -ENODEV;
	__u8 nपूर्णांकf;
	__u8 अगरnum;
	पूर्णांक altsetting = -1;
	bool sendsetup = false;

	/* we only support venकरोr specअगरic functions */
	अगर (पूर्णांकf->desc.bInterfaceClass != USB_CLASS_VENDOR_SPEC)
		जाओ करोne;

	nपूर्णांकf = serial->dev->actconfig->desc.bNumInterfaces;
	dev_dbg(dev, "Num Interfaces = %d\n", nपूर्णांकf);
	अगरnum = पूर्णांकf->desc.bInterfaceNumber;
	dev_dbg(dev, "This Interface = %d\n", अगरnum);

	अगर (nपूर्णांकf == 1) अणु
		/* QDL mode */
		/* Gobi 2000 has a single altsetting, older ones have two */
		अगर (serial->पूर्णांकerface->num_altsetting == 2)
			पूर्णांकf = usb_altnum_to_altsetting(serial->पूर्णांकerface, 1);
		अन्यथा अगर (serial->पूर्णांकerface->num_altsetting > 2)
			जाओ करोne;

		अगर (पूर्णांकf && पूर्णांकf->desc.bNumEndpoपूर्णांकs == 2 &&
		    usb_endpoपूर्णांक_is_bulk_in(&पूर्णांकf->endpoपूर्णांक[0].desc) &&
		    usb_endpoपूर्णांक_is_bulk_out(&पूर्णांकf->endpoपूर्णांक[1].desc)) अणु
			dev_dbg(dev, "QDL port found\n");

			अगर (serial->पूर्णांकerface->num_altsetting == 1)
				retval = 0; /* Success */
			अन्यथा
				altsetting = 1;
		पूर्ण
		जाओ करोne;

	पूर्ण

	/* शेष to enabling पूर्णांकerface */
	altsetting = 0;

	/*
	 * Composite mode; करोn't bind to the QMI/net पूर्णांकerface as that
	 * माला_लो handled by other drivers.
	 */

	चयन (id->driver_info) अणु
	हाल QCSERIAL_G1K:
		/*
		 * Gobi 1K USB layout:
		 * 0: DM/DIAG (use libqcdm from ModemManager क्रम communication)
		 * 1: serial port (करोesn't respond)
		 * 2: AT-capable modem port
		 * 3: QMI/net
		 */
		अगर (nपूर्णांकf < 3 || nपूर्णांकf > 4) अणु
			dev_err(dev, "unknown number of interfaces: %d\n", nपूर्णांकf);
			altsetting = -1;
			जाओ करोne;
		पूर्ण

		अगर (अगरnum == 0) अणु
			dev_dbg(dev, "Gobi 1K DM/DIAG interface found\n");
			altsetting = 1;
		पूर्ण अन्यथा अगर (अगरnum == 2)
			dev_dbg(dev, "Modem port found\n");
		अन्यथा
			altsetting = -1;
		अवरोध;
	हाल QCSERIAL_G2K:
		/* handle non-standard layouts */
		अगर (nपूर्णांकf == 5 && id->idProduct == QUECTEL_EC20_PID) अणु
			altsetting = handle_quectel_ec20(dev, अगरnum);
			जाओ करोne;
		पूर्ण

		/*
		 * Gobi 2K+ USB layout:
		 * 0: QMI/net
		 * 1: DM/DIAG (use libqcdm from ModemManager क्रम communication)
		 * 2: AT-capable modem port
		 * 3: NMEA
		 */
		अगर (nपूर्णांकf < 3 || nपूर्णांकf > 4) अणु
			dev_err(dev, "unknown number of interfaces: %d\n", nपूर्णांकf);
			altsetting = -1;
			जाओ करोne;
		पूर्ण

		चयन (अगरnum) अणु
		हाल 0:
			/* Don't claim the QMI/net पूर्णांकerface */
			altsetting = -1;
			अवरोध;
		हाल 1:
			dev_dbg(dev, "Gobi 2K+ DM/DIAG interface found\n");
			अवरोध;
		हाल 2:
			dev_dbg(dev, "Modem port found\n");
			अवरोध;
		हाल 3:
			/*
			 * NMEA (serial line 9600 8N1)
			 * # echo "\$GPS_START" > /dev/ttyUSBx
			 * # echo "\$GPS_STOP"  > /dev/ttyUSBx
			 */
			dev_dbg(dev, "Gobi 2K+ NMEA GPS interface found\n");
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QCSERIAL_SWI:
		/*
		 * Sierra Wireless layout:
		 * 0: DM/DIAG (use libqcdm from ModemManager क्रम communication)
		 * 2: NMEA
		 * 3: AT-capable modem port
		 * 8: QMI/net
		 */
		चयन (अगरnum) अणु
		हाल 0:
			dev_dbg(dev, "DM/DIAG interface found\n");
			अवरोध;
		हाल 2:
			dev_dbg(dev, "NMEA GPS interface found\n");
			sendsetup = true;
			अवरोध;
		हाल 3:
			dev_dbg(dev, "Modem port found\n");
			sendsetup = true;
			अवरोध;
		शेष:
			/* करोn't claim any unsupported पूर्णांकerface */
			altsetting = -1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QCSERIAL_HWI:
		/*
		 * Huawei devices map functions by subclass + protocol
		 * instead of पूर्णांकerface numbers. The protocol identअगरy
		 * a specअगरic function, जबतक the subclass indicate a
		 * specअगरic firmware source
		 *
		 * This is a list of functions known to be non-serial.  The rest
		 * are assumed to be serial and will be handled by this driver
		 */
		चयन (पूर्णांकf->desc.bInterfaceProtocol) अणु
			/* QMI combined (qmi_wwan) */
		हाल 0x07:
		हाल 0x37:
		हाल 0x67:
			/* QMI data (qmi_wwan) */
		हाल 0x08:
		हाल 0x38:
		हाल 0x68:
			/* QMI control (qmi_wwan) */
		हाल 0x09:
		हाल 0x39:
		हाल 0x69:
			/* NCM like (huawei_cdc_ncm) */
		हाल 0x16:
		हाल 0x46:
		हाल 0x76:
			altsetting = -1;
			अवरोध;
		शेष:
			dev_dbg(dev, "Huawei type serial port found (%02x/%02x/%02x)\n",
				पूर्णांकf->desc.bInterfaceClass,
				पूर्णांकf->desc.bInterfaceSubClass,
				पूर्णांकf->desc.bInterfaceProtocol);
		पूर्ण
		अवरोध;
	शेष:
		dev_err(dev, "unsupported device layout type: %lu\n",
			id->driver_info);
		अवरोध;
	पूर्ण

करोne:
	अगर (altsetting >= 0) अणु
		retval = usb_set_पूर्णांकerface(serial->dev, अगरnum, altsetting);
		अगर (retval < 0) अणु
			dev_err(dev,
				"Could not set interface, error %d\n",
				retval);
			retval = -ENODEV;
		पूर्ण
	पूर्ण

	अगर (!retval)
		usb_set_serial_data(serial, (व्योम *)(अचिन्हित दीर्घ)sendsetup);

	वापस retval;
पूर्ण

अटल पूर्णांक qc_attach(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_wwan_पूर्णांकf_निजी *data;
	bool sendsetup;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	sendsetup = !!(अचिन्हित दीर्घ)(usb_get_serial_data(serial));
	अगर (sendsetup)
		data->use_send_setup = 1;

	spin_lock_init(&data->susp_lock);

	usb_set_serial_data(serial, data);

	वापस 0;
पूर्ण

अटल व्योम qc_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_wwan_पूर्णांकf_निजी *priv = usb_get_serial_data(serial);

	usb_set_serial_data(serial, शून्य);
	kमुक्त(priv);
पूर्ण

अटल काष्ठा usb_serial_driver qcdevice = अणु
	.driver = अणु
		.owner     = THIS_MODULE,
		.name      = "qcserial",
	पूर्ण,
	.description         = "Qualcomm USB modem",
	.id_table            = id_table,
	.num_ports           = 1,
	.probe               = qcprobe,
	.खोलो		     = usb_wwan_खोलो,
	.बंद		     = usb_wwan_बंद,
	.dtr_rts	     = usb_wwan_dtr_rts,
	.ग_लिखो		     = usb_wwan_ग_लिखो,
	.ग_लिखो_room	     = usb_wwan_ग_लिखो_room,
	.अक्षरs_in_buffer     = usb_wwan_अक्षरs_in_buffer,
	.tiocmget            = usb_wwan_tiocmget,
	.tiocmset            = usb_wwan_tiocmset,
	.attach              = qc_attach,
	.release	     = qc_release,
	.port_probe          = usb_wwan_port_probe,
	.port_हटाओ	     = usb_wwan_port_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	     = usb_wwan_suspend,
	.resume		     = usb_wwan_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&qcdevice, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
