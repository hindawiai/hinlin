<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम USB Winकरोws Media Center Ed. eHome Infrared Transceivers
 *
 * Copyright (c) 2010-2011, Jarod Wilson <jarod@redhat.com>
 *
 * Based on the original lirc_mceusb and lirc_mceusb2 drivers, by Dan
 * Conti, Martin Blatter and Daniel Melander, the latter of which was
 * in turn also based on the lirc_atiusb driver by Paul Miller. The
 * two mce drivers were merged पूर्णांकo one by Jarod Wilson, with transmit
 * support क्रम the 1st-gen device added primarily by Patrick Calhoun,
 * with a bit of tweaks by Jarod. Debugging improvements and proper
 * support क्रम what appears to be 3rd-gen hardware added by Jarod.
 * Initial port from lirc driver to ir-core drivery by Jarod, based
 * partially on a port to an earlier proposed IR infraकाष्ठाure by
 * Jon Smirl, which included enhancements and simplअगरications to the
 * incoming IR buffer parsing routines.
 *
 * Updated in July of 2011 with the aid of Microsoft's official
 * remote/transceiver requirements and specअगरication करोcument, found at
 * करोwnload.microsoft.com, title
 * Winकरोws-Media-Center-RC-IR-Collection-Green-Button-Specअगरication-03-08-2011-V2.pdf
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/pm_wakeup.h>
#समावेश <media/rc-core.h>

#घोषणा DRIVER_VERSION	"1.95"
#घोषणा DRIVER_AUTHOR	"Jarod Wilson <jarod@redhat.com>"
#घोषणा DRIVER_DESC	"Windows Media Center Ed. eHome Infrared Transceiver " \
			"device driver"
#घोषणा DRIVER_NAME	"mceusb"

#घोषणा USB_TX_TIMEOUT		1000 /* in milliseconds */
#घोषणा USB_CTRL_MSG_SZ		2  /* Size of usb ctrl msg on gen1 hw */
#घोषणा MCE_G1_INIT_MSGS	40 /* Init messages on gen1 hw to throw out */

/* MCE स्थिरants */
#घोषणा MCE_IRBUF_SIZE		128  /* TX IR buffer length */
#घोषणा MCE_TIME_UNIT		50   /* Approx 50us resolution */
#घोषणा MCE_PACKET_SIZE		31   /* Max length of packet (with header) */
#घोषणा MCE_IRDATA_HEADER	(0x80 + MCE_PACKET_SIZE - 1)
				     /* Actual क्रमmat is 0x80 + num_bytes */
#घोषणा MCE_IRDATA_TRAILER	0x80 /* End of IR data */
#घोषणा MCE_MAX_CHANNELS	2    /* Two transmitters, hardware dependent? */
#घोषणा MCE_DEFAULT_TX_MASK	0x03 /* Vals: TX1=0x01, TX2=0x02, ALL=0x03 */
#घोषणा MCE_PULSE_BIT		0x80 /* Pulse bit, MSB set == PULSE अन्यथा SPACE */
#घोषणा MCE_PULSE_MASK		0x7f /* Pulse mask */
#घोषणा MCE_MAX_PULSE_LENGTH	0x7f /* Longest transmittable pulse symbol */

/*
 * The पूर्णांकerface between the host and the IR hardware is command-response
 * based. All commands and responses have a consistent क्रमmat, where a lead
 * byte always identअगरies the type of data following it. The lead byte has
 * a port value in the 3 highest bits and a length value in the 5 lowest
 * bits.
 *
 * The length field is overloaded, with a value of 11111 indicating that the
 * following byte is a command or response code, and the length of the entire
 * message is determined by the code. If the length field is not 11111, then
 * it specअगरies the number of bytes of port data that follow.
 */
#घोषणा MCE_CMD			0x1f
#घोषणा MCE_PORT_IR		0x4	/* (0x4 << 5) | MCE_CMD = 0x9f */
#घोषणा MCE_PORT_SYS		0x7	/* (0x7 << 5) | MCE_CMD = 0xff */
#घोषणा MCE_PORT_SER		0x6	/* 0xc0 through 0xdf flush & 0x1f bytes */
#घोषणा MCE_PORT_MASK		0xe0	/* Mask out command bits */

/* Command port headers */
#घोषणा MCE_CMD_PORT_IR		0x9f	/* IR-related cmd/rsp */
#घोषणा MCE_CMD_PORT_SYS	0xff	/* System (non-IR) device cmd/rsp */

/* Commands that set device state  (2-4 bytes in length) */
#घोषणा MCE_CMD_RESET		0xfe	/* Reset device, 2 bytes */
#घोषणा MCE_CMD_RESUME		0xaa	/* Resume device after error, 2 bytes */
#घोषणा MCE_CMD_SETIRCFS	0x06	/* Set tx carrier, 4 bytes */
#घोषणा MCE_CMD_SETIRTIMEOUT	0x0c	/* Set समयout, 4 bytes */
#घोषणा MCE_CMD_SETIRTXPORTS	0x08	/* Set tx ports, 3 bytes */
#घोषणा MCE_CMD_SETIRRXPORTEN	0x14	/* Set rx ports, 3 bytes */
#घोषणा MCE_CMD_FLASHLED	0x23	/* Flash receiver LED, 2 bytes */

/* Commands that query device state (all 2 bytes, unless noted) */
#घोषणा MCE_CMD_GETIRCFS	0x07	/* Get carrier */
#घोषणा MCE_CMD_GETIRTIMEOUT	0x0d	/* Get समयout */
#घोषणा MCE_CMD_GETIRTXPORTS	0x13	/* Get tx ports */
#घोषणा MCE_CMD_GETIRRXPORTEN	0x15	/* Get rx ports */
#घोषणा MCE_CMD_GETPORTSTATUS	0x11	/* Get tx port status, 3 bytes */
#घोषणा MCE_CMD_GETIRNUMPORTS	0x16	/* Get number of ports */
#घोषणा MCE_CMD_GETWAKESOURCE	0x17	/* Get wake source */
#घोषणा MCE_CMD_GETEMVER	0x22	/* Get emulator पूर्णांकerface version */
#घोषणा MCE_CMD_GETDEVDETAILS	0x21	/* Get device details (em ver2 only) */
#घोषणा MCE_CMD_GETWAKESUPPORT	0x20	/* Get wake details (em ver2 only) */
#घोषणा MCE_CMD_GETWAKEVERSION	0x18	/* Get wake pattern (em ver2 only) */

/* Misc commands */
#घोषणा MCE_CMD_NOP		0xff	/* No operation */

/* Responses to commands (non-error हालs) */
#घोषणा MCE_RSP_EQIRCFS		0x06	/* tx carrier, 4 bytes */
#घोषणा MCE_RSP_EQIRTIMEOUT	0x0c	/* rx समयout, 4 bytes */
#घोषणा MCE_RSP_GETWAKESOURCE	0x17	/* wake source, 3 bytes */
#घोषणा MCE_RSP_EQIRTXPORTS	0x08	/* tx port mask, 3 bytes */
#घोषणा MCE_RSP_EQIRRXPORTEN	0x14	/* rx port mask, 3 bytes */
#घोषणा MCE_RSP_GETPORTSTATUS	0x11	/* tx port status, 7 bytes */
#घोषणा MCE_RSP_EQIRRXCFCNT	0x15	/* rx carrier count, 4 bytes */
#घोषणा MCE_RSP_EQIRNUMPORTS	0x16	/* number of ports, 4 bytes */
#घोषणा MCE_RSP_EQWAKESUPPORT	0x20	/* wake capabilities, 3 bytes */
#घोषणा MCE_RSP_EQWAKEVERSION	0x18	/* wake pattern details, 6 bytes */
#घोषणा MCE_RSP_EQDEVDETAILS	0x21	/* device capabilities, 3 bytes */
#घोषणा MCE_RSP_EQEMVER		0x22	/* emulator पूर्णांकerface ver, 3 bytes */
#घोषणा MCE_RSP_FLASHLED	0x23	/* success flashing LED, 2 bytes */

/* Responses to error हालs, must send MCE_CMD_RESUME to clear them */
#घोषणा MCE_RSP_CMD_ILLEGAL	0xfe	/* illegal command क्रम port, 2 bytes */
#घोषणा MCE_RSP_TX_TIMEOUT	0x81	/* tx समयd out, 2 bytes */

/* Misc commands/responses not defined in the MCE remote/transceiver spec */
#घोषणा MCE_CMD_SIG_END		0x01	/* End of संकेत */
#घोषणा MCE_CMD_PING		0x03	/* Ping device */
#घोषणा MCE_CMD_UNKNOWN		0x04	/* Unknown */
#घोषणा MCE_CMD_UNKNOWN2	0x05	/* Unknown */
#घोषणा MCE_CMD_UNKNOWN3	0x09	/* Unknown */
#घोषणा MCE_CMD_UNKNOWN4	0x0a	/* Unknown */
#घोषणा MCE_CMD_G_REVISION	0x0b	/* Get hw/sw revision */
#घोषणा MCE_CMD_UNKNOWN5	0x0e	/* Unknown */
#घोषणा MCE_CMD_UNKNOWN6	0x0f	/* Unknown */
#घोषणा MCE_CMD_UNKNOWN8	0x19	/* Unknown */
#घोषणा MCE_CMD_UNKNOWN9	0x1b	/* Unknown */
#घोषणा MCE_CMD_शून्य		0x00	/* These show up various places... */

/* अगर buf[i] & MCE_PORT_MASK == 0x80 and buf[i] != MCE_CMD_PORT_IR,
 * then we're looking at a raw IR data sample */
#घोषणा MCE_COMMAND_IRDATA	0x80
#घोषणा MCE_PACKET_LENGTH_MASK	0x1f /* Packet length mask */

#घोषणा VENDOR_PHILIPS		0x0471
#घोषणा VENDOR_SMK		0x0609
#घोषणा VENDOR_TATUNG		0x1460
#घोषणा VENDOR_GATEWAY		0x107b
#घोषणा VENDOR_SHUTTLE		0x1308
#घोषणा VENDOR_SHUTTLE2		0x051c
#घोषणा VENDOR_MITSUMI		0x03ee
#घोषणा VENDOR_TOPSEED		0x1784
#घोषणा VENDOR_RICAVISION	0x179d
#घोषणा VENDOR_ITRON		0x195d
#घोषणा VENDOR_FIC		0x1509
#घोषणा VENDOR_LG		0x043e
#घोषणा VENDOR_MICROSOFT	0x045e
#घोषणा VENDOR_FORMOSA		0x147a
#घोषणा VENDOR_FINTEK		0x1934
#घोषणा VENDOR_PINNACLE		0x2304
#घोषणा VENDOR_ECS		0x1019
#घोषणा VENDOR_WISTRON		0x0fb8
#घोषणा VENDOR_COMPRO		0x185b
#घोषणा VENDOR_NORTHSTAR	0x04eb
#घोषणा VENDOR_REALTEK		0x0bda
#घोषणा VENDOR_TIVO		0x105a
#घोषणा VENDOR_CONEXANT		0x0572
#घोषणा VENDOR_TWISTEDMELON	0x2596
#घोषणा VENDOR_HAUPPAUGE	0x2040
#घोषणा VENDOR_PCTV		0x2013
#घोषणा VENDOR_ADAPTEC		0x03f3

क्रमागत mceusb_model_type अणु
	MCE_GEN2 = 0,		/* Most boards */
	MCE_GEN1,
	MCE_GEN3,
	MCE_GEN3_BROKEN_IRTIMEOUT,
	MCE_GEN2_TX_INV,
	MCE_GEN2_TX_INV_RX_GOOD,
	POLARIS_EVK,
	CX_HYBRID_TV,
	MULTIFUNCTION,
	TIVO_KIT,
	MCE_GEN2_NO_TX,
	HAUPPAUGE_CX_HYBRID_TV,
	EVROMEDIA_FULL_HYBRID_FULLHD,
	ASTROMETA_T2HYBRID,
पूर्ण;

काष्ठा mceusb_model अणु
	u32 mce_gen1:1;
	u32 mce_gen2:1;
	u32 mce_gen3:1;
	u32 tx_mask_normal:1;
	u32 no_tx:1;
	u32 broken_irसमयout:1;
	/*
	 * 2nd IR receiver (लघु-range, wideband) क्रम learning mode:
	 *     0, असलent 2nd receiver (rx2)
	 *     1, rx2 present
	 *     2, rx2 which under counts IR carrier cycles
	 */
	u32 rx2;

	पूर्णांक ir_पूर्णांकfnum;

	स्थिर अक्षर *rc_map;	/* Allow specअगरy a per-board map */
	स्थिर अक्षर *name;	/* per-board name */
पूर्ण;

अटल स्थिर काष्ठा mceusb_model mceusb_model[] = अणु
	[MCE_GEN1] = अणु
		.mce_gen1 = 1,
		.tx_mask_normal = 1,
		.rx2 = 2,
	पूर्ण,
	[MCE_GEN2] = अणु
		.mce_gen2 = 1,
		.rx2 = 2,
	पूर्ण,
	[MCE_GEN2_NO_TX] = अणु
		.mce_gen2 = 1,
		.no_tx = 1,
	पूर्ण,
	[MCE_GEN2_TX_INV] = अणु
		.mce_gen2 = 1,
		.tx_mask_normal = 1,
		.rx2 = 1,
	पूर्ण,
	[MCE_GEN2_TX_INV_RX_GOOD] = अणु
		.mce_gen2 = 1,
		.tx_mask_normal = 1,
		.rx2 = 2,
	पूर्ण,
	[MCE_GEN3] = अणु
		.mce_gen3 = 1,
		.tx_mask_normal = 1,
		.rx2 = 2,
	पूर्ण,
	[MCE_GEN3_BROKEN_IRTIMEOUT] = अणु
		.mce_gen3 = 1,
		.tx_mask_normal = 1,
		.rx2 = 2,
		.broken_irसमयout = 1
	पूर्ण,
	[POLARIS_EVK] = अणु
		/*
		 * In fact, the EVK is shipped without
		 * remotes, but we should have something handy,
		 * to allow testing it
		 */
		.name = "Conexant Hybrid TV (cx231xx) MCE IR",
		.rx2 = 2,
	पूर्ण,
	[CX_HYBRID_TV] = अणु
		.no_tx = 1, /* tx isn't wired up at all */
		.name = "Conexant Hybrid TV (cx231xx) MCE IR",
	पूर्ण,
	[HAUPPAUGE_CX_HYBRID_TV] = अणु
		.no_tx = 1, /* eeprom says it has no tx */
		.name = "Conexant Hybrid TV (cx231xx) MCE IR no TX",
	पूर्ण,
	[MULTIFUNCTION] = अणु
		.mce_gen2 = 1,
		.ir_पूर्णांकfnum = 2,
		.rx2 = 2,
	पूर्ण,
	[TIVO_KIT] = अणु
		.mce_gen2 = 1,
		.rc_map = RC_MAP_TIVO,
		.rx2 = 2,
	पूर्ण,
	[EVROMEDIA_FULL_HYBRID_FULLHD] = अणु
		.name = "Evromedia USB Full Hybrid Full HD",
		.no_tx = 1,
		.rc_map = RC_MAP_MSI_DIGIVOX_III,
	पूर्ण,
	[ASTROMETA_T2HYBRID] = अणु
		.name = "Astrometa T2Hybrid",
		.no_tx = 1,
		.rc_map = RC_MAP_ASTROMETA_T2HYBRID,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id mceusb_dev_table[] = अणु
	/* Original Microsoft MCE IR Transceiver (often HP-bअक्रमed) */
	अणु USB_DEVICE(VENDOR_MICROSOFT, 0x006d),
	  .driver_info = MCE_GEN1 पूर्ण,
	/* Philips Infrared Transceiver - Sahara bअक्रमed */
	अणु USB_DEVICE(VENDOR_PHILIPS, 0x0608) पूर्ण,
	/* Philips Infrared Transceiver - HP bअक्रमed */
	अणु USB_DEVICE(VENDOR_PHILIPS, 0x060c),
	  .driver_info = MCE_GEN2_TX_INV पूर्ण,
	/* Philips SRM5100 */
	अणु USB_DEVICE(VENDOR_PHILIPS, 0x060d) पूर्ण,
	/* Philips Infrared Transceiver - Omaura */
	अणु USB_DEVICE(VENDOR_PHILIPS, 0x060f) पूर्ण,
	/* Philips Infrared Transceiver - Spinel plus */
	अणु USB_DEVICE(VENDOR_PHILIPS, 0x0613) पूर्ण,
	/* Philips eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_PHILIPS, 0x0815) पूर्ण,
	/* Philips/Spinel plus IR transceiver क्रम ASUS */
	अणु USB_DEVICE(VENDOR_PHILIPS, 0x206c) पूर्ण,
	/* Philips/Spinel plus IR transceiver क्रम ASUS */
	अणु USB_DEVICE(VENDOR_PHILIPS, 0x2088) पूर्ण,
	/* Philips IR transceiver (Dell bअक्रमed) */
	अणु USB_DEVICE(VENDOR_PHILIPS, 0x2093),
	  .driver_info = MCE_GEN2_TX_INV पूर्ण,
	/* Realtek MCE IR Receiver and card पढ़ोer */
	अणु USB_DEVICE(VENDOR_REALTEK, 0x0161),
	  .driver_info = MULTIFUNCTION पूर्ण,
	/* SMK/Toshiba G83C0004D410 */
	अणु USB_DEVICE(VENDOR_SMK, 0x031d),
	  .driver_info = MCE_GEN2_TX_INV_RX_GOOD पूर्ण,
	/* SMK eHome Infrared Transceiver (Sony VAIO) */
	अणु USB_DEVICE(VENDOR_SMK, 0x0322),
	  .driver_info = MCE_GEN2_TX_INV पूर्ण,
	/* bundled with Hauppauge PVR-150 */
	अणु USB_DEVICE(VENDOR_SMK, 0x0334),
	  .driver_info = MCE_GEN2_TX_INV पूर्ण,
	/* SMK eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_SMK, 0x0338) पूर्ण,
	/* SMK/I-O Data GV-MC7/RCKIT Receiver */
	अणु USB_DEVICE(VENDOR_SMK, 0x0353),
	  .driver_info = MCE_GEN2_NO_TX पूर्ण,
	/* SMK RXX6000 Infrared Receiver */
	अणु USB_DEVICE(VENDOR_SMK, 0x0357),
	  .driver_info = MCE_GEN2_NO_TX पूर्ण,
	/* Tatung eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_TATUNG, 0x9150) पूर्ण,
	/* Shuttle eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_SHUTTLE, 0xc001) पूर्ण,
	/* Shuttle eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_SHUTTLE2, 0xc001) पूर्ण,
	/* Gateway eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_GATEWAY, 0x3009) पूर्ण,
	/* Mitsumi */
	अणु USB_DEVICE(VENDOR_MITSUMI, 0x2501) पूर्ण,
	/* Topseed eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_TOPSEED, 0x0001),
	  .driver_info = MCE_GEN2_TX_INV पूर्ण,
	/* Topseed HP eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_TOPSEED, 0x0006),
	  .driver_info = MCE_GEN2_TX_INV पूर्ण,
	/* Topseed eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_TOPSEED, 0x0007),
	  .driver_info = MCE_GEN2_TX_INV पूर्ण,
	/* Topseed eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_TOPSEED, 0x0008),
	  .driver_info = MCE_GEN3 पूर्ण,
	/* Topseed eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_TOPSEED, 0x000a),
	  .driver_info = MCE_GEN2_TX_INV पूर्ण,
	/* Topseed eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_TOPSEED, 0x0011),
	  .driver_info = MCE_GEN3_BROKEN_IRTIMEOUT पूर्ण,
	/* Ricavision पूर्णांकernal Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_RICAVISION, 0x0010) पूर्ण,
	/* Itron ione Libra Q-11 */
	अणु USB_DEVICE(VENDOR_ITRON, 0x7002) पूर्ण,
	/* FIC eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_FIC, 0x9242) पूर्ण,
	/* LG eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_LG, 0x9803) पूर्ण,
	/* Microsoft MCE Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_MICROSOFT, 0x00a0) पूर्ण,
	/* Formosa eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_FORMOSA, 0xe015) पूर्ण,
	/* Formosa21 / eHome Infrared Receiver */
	अणु USB_DEVICE(VENDOR_FORMOSA, 0xe016) पूर्ण,
	/* Formosa aim / Trust MCE Infrared Receiver */
	अणु USB_DEVICE(VENDOR_FORMOSA, 0xe017),
	  .driver_info = MCE_GEN2_NO_TX पूर्ण,
	/* Formosa Industrial Computing / Beanbag Emulation Device */
	अणु USB_DEVICE(VENDOR_FORMOSA, 0xe018) पूर्ण,
	/* Formosa21 / eHome Infrared Receiver */
	अणु USB_DEVICE(VENDOR_FORMOSA, 0xe03a) पूर्ण,
	/* Formosa Industrial Computing AIM IR605/A */
	अणु USB_DEVICE(VENDOR_FORMOSA, 0xe03c) पूर्ण,
	/* Formosa Industrial Computing */
	अणु USB_DEVICE(VENDOR_FORMOSA, 0xe03e) पूर्ण,
	/* Formosa Industrial Computing */
	अणु USB_DEVICE(VENDOR_FORMOSA, 0xe042) पूर्ण,
	/* Fपूर्णांकek eHome Infrared Transceiver (HP bअक्रमed) */
	अणु USB_DEVICE(VENDOR_FINTEK, 0x5168),
	  .driver_info = MCE_GEN2_TX_INV पूर्ण,
	/* Fपूर्णांकek eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_FINTEK, 0x0602) पूर्ण,
	/* Fपूर्णांकek eHome Infrared Transceiver (in the AOpen MP45) */
	अणु USB_DEVICE(VENDOR_FINTEK, 0x0702) पूर्ण,
	/* Pinnacle Remote Kit */
	अणु USB_DEVICE(VENDOR_PINNACLE, 0x0225),
	  .driver_info = MCE_GEN3 पूर्ण,
	/* Elitegroup Computer Systems IR */
	अणु USB_DEVICE(VENDOR_ECS, 0x0f38) पूर्ण,
	/* Wistron Corp. eHome Infrared Receiver */
	अणु USB_DEVICE(VENDOR_WISTRON, 0x0002) पूर्ण,
	/* Compro K100 */
	अणु USB_DEVICE(VENDOR_COMPRO, 0x3020) पूर्ण,
	/* Compro K100 v2 */
	अणु USB_DEVICE(VENDOR_COMPRO, 0x3082) पूर्ण,
	/* Northstar Systems, Inc. eHome Infrared Transceiver */
	अणु USB_DEVICE(VENDOR_NORTHSTAR, 0xe004) पूर्ण,
	/* TiVo PC IR Receiver */
	अणु USB_DEVICE(VENDOR_TIVO, 0x2000),
	  .driver_info = TIVO_KIT पूर्ण,
	/* Conexant Hybrid TV "Shelby" Polaris SDK */
	अणु USB_DEVICE(VENDOR_CONEXANT, 0x58a1),
	  .driver_info = POLARIS_EVK पूर्ण,
	/* Conexant Hybrid TV RDU253S Polaris */
	अणु USB_DEVICE(VENDOR_CONEXANT, 0x58a5),
	  .driver_info = CX_HYBRID_TV पूर्ण,
	/* Twisted Melon Inc. - Manta Mini Receiver */
	अणु USB_DEVICE(VENDOR_TWISTEDMELON, 0x8008) पूर्ण,
	/* Twisted Melon Inc. - Manta Pico Receiver */
	अणु USB_DEVICE(VENDOR_TWISTEDMELON, 0x8016) पूर्ण,
	/* Twisted Melon Inc. - Manta Transceiver */
	अणु USB_DEVICE(VENDOR_TWISTEDMELON, 0x8042) पूर्ण,
	/* Hauppauge WINTV-HVR-HVR 930C-HD - based on cx231xx */
	अणु USB_DEVICE(VENDOR_HAUPPAUGE, 0xb130),
	  .driver_info = HAUPPAUGE_CX_HYBRID_TV पूर्ण,
	अणु USB_DEVICE(VENDOR_HAUPPAUGE, 0xb131),
	  .driver_info = HAUPPAUGE_CX_HYBRID_TV पूर्ण,
	अणु USB_DEVICE(VENDOR_HAUPPAUGE, 0xb138),
	  .driver_info = HAUPPAUGE_CX_HYBRID_TV पूर्ण,
	अणु USB_DEVICE(VENDOR_HAUPPAUGE, 0xb139),
	  .driver_info = HAUPPAUGE_CX_HYBRID_TV पूर्ण,
	/* Hauppauge WinTV-HVR-935C - based on cx231xx */
	अणु USB_DEVICE(VENDOR_HAUPPAUGE, 0xb151),
	  .driver_info = HAUPPAUGE_CX_HYBRID_TV पूर्ण,
	/* Hauppauge WinTV-HVR-955Q - based on cx231xx */
	अणु USB_DEVICE(VENDOR_HAUPPAUGE, 0xb123),
	  .driver_info = HAUPPAUGE_CX_HYBRID_TV पूर्ण,
	/* Hauppauge WinTV-HVR-975 - based on cx231xx */
	अणु USB_DEVICE(VENDOR_HAUPPAUGE, 0xb150),
	  .driver_info = HAUPPAUGE_CX_HYBRID_TV पूर्ण,
	अणु USB_DEVICE(VENDOR_PCTV, 0x0259),
	  .driver_info = HAUPPAUGE_CX_HYBRID_TV पूर्ण,
	अणु USB_DEVICE(VENDOR_PCTV, 0x025e),
	  .driver_info = HAUPPAUGE_CX_HYBRID_TV पूर्ण,
	/* Adaptec / HP eHome Receiver */
	अणु USB_DEVICE(VENDOR_ADAPTEC, 0x0094) पूर्ण,
	/* Evromedia USB Full Hybrid Full HD */
	अणु USB_DEVICE(0x1b80, 0xd3b2),
	  .driver_info = EVROMEDIA_FULL_HYBRID_FULLHD पूर्ण,
	/* Astrometa T2hybrid */
	अणु USB_DEVICE(0x15f4, 0x0135),
	  .driver_info = ASTROMETA_T2HYBRID पूर्ण,

	/* Terminating entry */
	अणु पूर्ण
पूर्ण;

/* data काष्ठाure क्रम each usb transceiver */
काष्ठा mceusb_dev अणु
	/* ir-core bits */
	काष्ठा rc_dev *rc;

	/* optional features we can enable */
	bool carrier_report_enabled;
	bool wideband_rx_enabled;	/* aka learning mode, लघु-range rx */

	/* core device bits */
	काष्ठा device *dev;

	/* usb */
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *usbपूर्णांकf;
	काष्ठा urb *urb_in;
	अचिन्हित पूर्णांक pipe_in;
	काष्ठा usb_endpoपूर्णांक_descriptor *usb_ep_out;
	अचिन्हित पूर्णांक pipe_out;

	/* buffers and dma */
	अचिन्हित अक्षर *buf_in;
	अचिन्हित पूर्णांक len_in;
	dma_addr_t dma_in;

	क्रमागत अणु
		CMD_HEADER = 0,
		SUBCMD,
		CMD_DATA,
		PARSE_IRDATA,
	पूर्ण parser_state;

	u8 cmd, rem;		/* Reमुख्यing IR data bytes in packet */

	काष्ठा अणु
		u32 connected:1;
		u32 tx_mask_normal:1;
		u32 microsoft_gen1:1;
		u32 no_tx:1;
		u32 rx2;
	पूर्ण flags;

	/* transmit support */
	u32 carrier;
	अचिन्हित अक्षर tx_mask;

	अक्षर name[128];
	अक्षर phys[64];
	क्रमागत mceusb_model_type model;

	bool need_reset;	/* flag to issue a device resume cmd */
	u8 emver;		/* emulator पूर्णांकerface version */
	u8 num_txports;		/* number of transmit ports */
	u8 num_rxports;		/* number of receive sensors */
	u8 txports_cabled;	/* biपंचांगask of transmitters with cable */
	u8 rxports_active;	/* biपंचांगask of active receive sensors */
	bool learning_active;	/* wideband rx is active */

	/* receiver carrier frequency detection support */
	u32 pulse_tunit;	/* IR pulse "on" cumulative समय units */
	u32 pulse_count;	/* pulse "on" count in measurement पूर्णांकerval */

	/*
	 * support क्रम async error handler mceusb_deferred_kevent()
	 * where usb_clear_halt(), usb_reset_configuration(),
	 * usb_reset_device(), etc. must be करोne in process context
	 */
	काष्ठा work_काष्ठा kevent;
	अचिन्हित दीर्घ kevent_flags;
#		define EVENT_TX_HALT	0
#		define EVENT_RX_HALT	1
#		define EVENT_RST_PEND	31
पूर्ण;

/* MCE Device Command Strings, generally a port and command pair */
अटल अक्षर DEVICE_RESUME[]	= अणुMCE_CMD_शून्य, MCE_CMD_PORT_SYS,
				   MCE_CMD_RESUMEपूर्ण;
अटल अक्षर GET_REVISION[]	= अणुMCE_CMD_PORT_SYS, MCE_CMD_G_REVISIONपूर्ण;
अटल अक्षर GET_EMVER[]		= अणुMCE_CMD_PORT_SYS, MCE_CMD_GETEMVERपूर्ण;
अटल अक्षर GET_WAKEVERSION[]	= अणुMCE_CMD_PORT_SYS, MCE_CMD_GETWAKEVERSIONपूर्ण;
अटल अक्षर FLASH_LED[]		= अणुMCE_CMD_PORT_SYS, MCE_CMD_FLASHLEDपूर्ण;
अटल अक्षर GET_UNKNOWN2[]	= अणुMCE_CMD_PORT_IR, MCE_CMD_UNKNOWN2पूर्ण;
अटल अक्षर GET_CARRIER_FREQ[]	= अणुMCE_CMD_PORT_IR, MCE_CMD_GETIRCFSपूर्ण;
अटल अक्षर GET_RX_TIMEOUT[]	= अणुMCE_CMD_PORT_IR, MCE_CMD_GETIRTIMEOUTपूर्ण;
अटल अक्षर GET_NUM_PORTS[]	= अणुMCE_CMD_PORT_IR, MCE_CMD_GETIRNUMPORTSपूर्ण;
अटल अक्षर GET_TX_BITMASK[]	= अणुMCE_CMD_PORT_IR, MCE_CMD_GETIRTXPORTSपूर्ण;
अटल अक्षर GET_RX_SENSOR[]	= अणुMCE_CMD_PORT_IR, MCE_CMD_GETIRRXPORTENपूर्ण;
/* sub in desired values in lower byte or bytes क्रम full command */
/* FIXME: make use of these क्रम transmit.
अटल अक्षर SET_CARRIER_FREQ[]	= अणुMCE_CMD_PORT_IR,
				   MCE_CMD_SETIRCFS, 0x00, 0x00पूर्ण;
अटल अक्षर SET_TX_BITMASK[]	= अणुMCE_CMD_PORT_IR, MCE_CMD_SETIRTXPORTS, 0x00पूर्ण;
अटल अक्षर SET_RX_TIMEOUT[]	= अणुMCE_CMD_PORT_IR,
				   MCE_CMD_SETIRTIMEOUT, 0x00, 0x00पूर्ण;
अटल अक्षर SET_RX_SENSOR[]	= अणुMCE_CMD_PORT_IR,
				   MCE_RSP_EQIRRXPORTEN, 0x00पूर्ण;
*/

अटल पूर्णांक mceusb_cmd_datasize(u8 cmd, u8 subcmd)
अणु
	पूर्णांक datasize = 0;

	चयन (cmd) अणु
	हाल MCE_CMD_शून्य:
		अगर (subcmd == MCE_CMD_PORT_SYS)
			datasize = 1;
		अवरोध;
	हाल MCE_CMD_PORT_SYS:
		चयन (subcmd) अणु
		हाल MCE_RSP_GETPORTSTATUS:
			datasize = 5;
			अवरोध;
		हाल MCE_RSP_EQWAKEVERSION:
			datasize = 4;
			अवरोध;
		हाल MCE_CMD_G_REVISION:
			datasize = 4;
			अवरोध;
		हाल MCE_RSP_EQWAKESUPPORT:
		हाल MCE_RSP_GETWAKESOURCE:
		हाल MCE_RSP_EQDEVDETAILS:
		हाल MCE_RSP_EQEMVER:
			datasize = 1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MCE_CMD_PORT_IR:
		चयन (subcmd) अणु
		हाल MCE_CMD_UNKNOWN:
		हाल MCE_RSP_EQIRCFS:
		हाल MCE_RSP_EQIRTIMEOUT:
		हाल MCE_RSP_EQIRRXCFCNT:
		हाल MCE_RSP_EQIRNUMPORTS:
			datasize = 2;
			अवरोध;
		हाल MCE_CMD_SIG_END:
		हाल MCE_RSP_EQIRTXPORTS:
		हाल MCE_RSP_EQIRRXPORTEN:
			datasize = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस datasize;
पूर्ण

अटल व्योम mceusb_dev_prपूर्णांकdata(काष्ठा mceusb_dev *ir, u8 *buf, पूर्णांक buf_len,
				 पूर्णांक offset, पूर्णांक len, bool out)
अणु
#अगर defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
	अक्षर *inout;
	u8 cmd, subcmd, *data;
	काष्ठा device *dev = ir->dev;
	u32 carrier, period;

	अगर (offset < 0 || offset >= buf_len)
		वापस;

	dev_dbg(dev, "%cx data[%d]: %*ph (len=%d sz=%d)",
		(out ? 't' : 'r'), offset,
		min(len, buf_len - offset), buf + offset, len, buf_len);

	inout = out ? "Request" : "Got";

	cmd    = buf[offset];
	subcmd = (offset + 1 < buf_len) ? buf[offset + 1] : 0;
	data   = &buf[offset] + 2;

	/* Trace meaningless 0xb1 0x60 header bytes on original receiver */
	अगर (ir->flags.microsoft_gen1 && !out && !offset) अणु
		dev_dbg(dev, "MCE gen 1 header");
		वापस;
	पूर्ण

	/* Trace IR data header or trailer */
	अगर (cmd != MCE_CMD_PORT_IR &&
	    (cmd & MCE_PORT_MASK) == MCE_COMMAND_IRDATA) अणु
		अगर (cmd == MCE_IRDATA_TRAILER)
			dev_dbg(dev, "End of raw IR data");
		अन्यथा
			dev_dbg(dev, "Raw IR data, %d pulse/space samples",
				cmd & MCE_PACKET_LENGTH_MASK);
		वापस;
	पूर्ण

	/* Unexpected end of buffer? */
	अगर (offset + len > buf_len)
		वापस;

	/* Decode MCE command/response */
	चयन (cmd) अणु
	हाल MCE_CMD_शून्य:
		अगर (subcmd == MCE_CMD_शून्य)
			अवरोध;
		अगर ((subcmd == MCE_CMD_PORT_SYS) &&
		    (data[0] == MCE_CMD_RESUME))
			dev_dbg(dev, "Device resume requested");
		अन्यथा
			dev_dbg(dev, "Unknown command 0x%02x 0x%02x",
				 cmd, subcmd);
		अवरोध;
	हाल MCE_CMD_PORT_SYS:
		चयन (subcmd) अणु
		हाल MCE_RSP_EQEMVER:
			अगर (!out)
				dev_dbg(dev, "Emulator interface version %x",
					 data[0]);
			अवरोध;
		हाल MCE_CMD_G_REVISION:
			अगर (len == 2)
				dev_dbg(dev, "Get hw/sw rev?");
			अन्यथा
				dev_dbg(dev, "hw/sw rev %*ph",
					4, &buf[offset + 2]);
			अवरोध;
		हाल MCE_CMD_RESUME:
			dev_dbg(dev, "Device resume requested");
			अवरोध;
		हाल MCE_RSP_CMD_ILLEGAL:
			dev_dbg(dev, "Illegal PORT_SYS command");
			अवरोध;
		हाल MCE_RSP_EQWAKEVERSION:
			अगर (!out)
				dev_dbg(dev, "Wake version, proto: 0x%02x, payload: 0x%02x, address: 0x%02x, version: 0x%02x",
					data[0], data[1], data[2], data[3]);
			अवरोध;
		हाल MCE_RSP_GETPORTSTATUS:
			अगर (!out)
				/* We use data1 + 1 here, to match hw labels */
				dev_dbg(dev, "TX port %d: blaster is%s connected",
					 data[0] + 1, data[3] ? " not" : "");
			अवरोध;
		हाल MCE_CMD_FLASHLED:
			dev_dbg(dev, "Attempting to flash LED");
			अवरोध;
		शेष:
			dev_dbg(dev, "Unknown command 0x%02x 0x%02x",
				 cmd, subcmd);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MCE_CMD_PORT_IR:
		चयन (subcmd) अणु
		हाल MCE_CMD_SIG_END:
			dev_dbg(dev, "End of signal");
			अवरोध;
		हाल MCE_CMD_PING:
			dev_dbg(dev, "Ping");
			अवरोध;
		हाल MCE_CMD_UNKNOWN:
			dev_dbg(dev, "Resp to 9f 05 of 0x%02x 0x%02x",
				data[0], data[1]);
			अवरोध;
		हाल MCE_RSP_EQIRCFS:
			अगर (!data[0] && !data[1]) अणु
				dev_dbg(dev, "%s: no carrier", inout);
				अवरोध;
			पूर्ण
			// prescaler should make sense
			अगर (data[0] > 8)
				अवरोध;
			period = DIV_ROUND_CLOSEST((1U << data[0] * 2) *
						   (data[1] + 1), 10);
			अगर (!period)
				अवरोध;
			carrier = USEC_PER_SEC / period;
			dev_dbg(dev, "%s carrier of %u Hz (period %uus)",
				 inout, carrier, period);
			अवरोध;
		हाल MCE_CMD_GETIRCFS:
			dev_dbg(dev, "Get carrier mode and freq");
			अवरोध;
		हाल MCE_RSP_EQIRTXPORTS:
			dev_dbg(dev, "%s transmit blaster mask of 0x%02x",
				 inout, data[0]);
			अवरोध;
		हाल MCE_RSP_EQIRTIMEOUT:
			/* value is in units of 50us, so x*50/1000 ms */
			period = ((data[0] << 8) | data[1]) *
				  MCE_TIME_UNIT / 1000;
			dev_dbg(dev, "%s receive timeout of %d ms",
				 inout, period);
			अवरोध;
		हाल MCE_CMD_GETIRTIMEOUT:
			dev_dbg(dev, "Get receive timeout");
			अवरोध;
		हाल MCE_CMD_GETIRTXPORTS:
			dev_dbg(dev, "Get transmit blaster mask");
			अवरोध;
		हाल MCE_RSP_EQIRRXPORTEN:
			dev_dbg(dev, "%s %s-range receive sensor in use",
				 inout, data[0] == 0x02 ? "short" : "long");
			अवरोध;
		हाल MCE_CMD_GETIRRXPORTEN:
		/* aka MCE_RSP_EQIRRXCFCNT */
			अगर (out)
				dev_dbg(dev, "Get receive sensor");
			अन्यथा
				dev_dbg(dev, "RX carrier cycle count: %d",
					((data[0] << 8) | data[1]));
			अवरोध;
		हाल MCE_RSP_EQIRNUMPORTS:
			अगर (out)
				अवरोध;
			dev_dbg(dev, "Num TX ports: %x, num RX ports: %x",
				data[0], data[1]);
			अवरोध;
		हाल MCE_RSP_CMD_ILLEGAL:
			dev_dbg(dev, "Illegal PORT_IR command");
			अवरोध;
		हाल MCE_RSP_TX_TIMEOUT:
			dev_dbg(dev, "IR TX timeout (TX buffer underrun)");
			अवरोध;
		शेष:
			dev_dbg(dev, "Unknown command 0x%02x 0x%02x",
				 cmd, subcmd);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Schedule work that can't be करोne in पूर्णांकerrupt handlers
 * (mceusb_dev_recv() and mce_ग_लिखो_callback()) nor tasklets.
 * Invokes mceusb_deferred_kevent() क्रम recovering from
 * error events specअगरied by the kevent bit field.
 */
अटल व्योम mceusb_defer_kevent(काष्ठा mceusb_dev *ir, पूर्णांक kevent)
अणु
	set_bit(kevent, &ir->kevent_flags);

	अगर (test_bit(EVENT_RST_PEND, &ir->kevent_flags)) अणु
		dev_dbg(ir->dev, "kevent %d dropped pending USB Reset Device",
			kevent);
		वापस;
	पूर्ण

	अगर (!schedule_work(&ir->kevent))
		dev_dbg(ir->dev, "kevent %d already scheduled", kevent);
	अन्यथा
		dev_dbg(ir->dev, "kevent %d scheduled", kevent);
पूर्ण

अटल व्योम mce_ग_लिखो_callback(काष्ठा urb *urb)
अणु
	अगर (!urb)
		वापस;

	complete(urb->context);
पूर्ण

/*
 * Write (TX/send) data to MCE device USB endpoपूर्णांक out.
 * Used क्रम IR blaster TX and MCE device commands.
 *
 * Return: The number of bytes written (> 0) or त्रुटि_सं (< 0).
 */
अटल पूर्णांक mce_ग_लिखो(काष्ठा mceusb_dev *ir, u8 *data, पूर्णांक size)
अणु
	पूर्णांक ret;
	काष्ठा urb *urb;
	काष्ठा device *dev = ir->dev;
	अचिन्हित अक्षर *buf_out;
	काष्ठा completion tx_करोne;
	अचिन्हित दीर्घ expire;
	अचिन्हित दीर्घ ret_रुको;

	mceusb_dev_prपूर्णांकdata(ir, data, size, 0, size, true);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (unlikely(!urb)) अणु
		dev_err(dev, "Error: mce write couldn't allocate urb");
		वापस -ENOMEM;
	पूर्ण

	buf_out = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf_out) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	init_completion(&tx_करोne);

	/* outbound data */
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ir->usb_ep_out))
		usb_fill_पूर्णांक_urb(urb, ir->usbdev, ir->pipe_out,
				 buf_out, size, mce_ग_लिखो_callback, &tx_करोne,
				 ir->usb_ep_out->bInterval);
	अन्यथा
		usb_fill_bulk_urb(urb, ir->usbdev, ir->pipe_out,
				  buf_out, size, mce_ग_लिखो_callback, &tx_करोne);
	स_नकल(buf_out, data, size);

	ret = usb_submit_urb(urb, GFP_KERNEL);
	अगर (ret) अणु
		dev_err(dev, "Error: mce write submit urb error = %d", ret);
		kमुक्त(buf_out);
		usb_मुक्त_urb(urb);
		वापस ret;
	पूर्ण

	expire = msecs_to_jअगरfies(USB_TX_TIMEOUT);
	ret_रुको = रुको_क्रम_completion_समयout(&tx_करोne, expire);
	अगर (!ret_रुको) अणु
		dev_err(dev, "Error: mce write timed out (expire = %lu (%dms))",
			expire, USB_TX_TIMEOUT);
		usb_समाप्त_urb(urb);
		ret = (urb->status == -ENOENT ? -ETIMEDOUT : urb->status);
	पूर्ण अन्यथा अणु
		ret = urb->status;
	पूर्ण
	अगर (ret >= 0)
		ret = urb->actual_length;	/* bytes written */

	चयन (urb->status) अणु
	/* success */
	हाल 0:
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -EILSEQ:
	हाल -ESHUTDOWN:
		अवरोध;

	हाल -EPIPE:
		dev_err(ir->dev, "Error: mce write urb status = %d (TX HALT)",
			urb->status);
		mceusb_defer_kevent(ir, EVENT_TX_HALT);
		अवरोध;

	शेष:
		dev_err(ir->dev, "Error: mce write urb status = %d",
			urb->status);
		अवरोध;
	पूर्ण

	dev_dbg(dev, "tx done status = %d (wait = %lu, expire = %lu (%dms), urb->actual_length = %d, urb->status = %d)",
		ret, ret_रुको, expire, USB_TX_TIMEOUT,
		urb->actual_length, urb->status);

	kमुक्त(buf_out);
	usb_मुक्त_urb(urb);

	वापस ret;
पूर्ण

अटल व्योम mce_command_out(काष्ठा mceusb_dev *ir, u8 *data, पूर्णांक size)
अणु
	पूर्णांक rsize = माप(DEVICE_RESUME);

	अगर (ir->need_reset) अणु
		ir->need_reset = false;
		mce_ग_लिखो(ir, DEVICE_RESUME, rsize);
		msleep(10);
	पूर्ण

	mce_ग_लिखो(ir, data, size);
	msleep(10);
पूर्ण

/*
 * Transmit IR out the MCE device IR blaster port(s).
 *
 * Convert IR pulse/space sequence from LIRC to MCE क्रमmat.
 * Break up a दीर्घ IR sequence पूर्णांकo multiple parts (MCE IR data packets).
 *
 * u32 txbuf[] consists of IR pulse, space, ..., and pulse बार in usec.
 * Pulses and spaces are implicit by their position.
 * The first IR sample, txbuf[0], is always a pulse.
 *
 * u8 irbuf[] consists of multiple IR data packets क्रम the MCE device.
 * A packet is 1 u8 MCE_IRDATA_HEADER and up to 30 u8 IR samples.
 * An IR sample is 1-bit pulse/space flag with 7-bit समय
 * in MCE समय units (50usec).
 *
 * Return: The number of IR samples sent (> 0) or त्रुटि_सं (< 0).
 */
अटल पूर्णांक mceusb_tx_ir(काष्ठा rc_dev *dev, अचिन्हित *txbuf, अचिन्हित count)
अणु
	काष्ठा mceusb_dev *ir = dev->priv;
	u8 cmdbuf[3] = अणु MCE_CMD_PORT_IR, MCE_CMD_SETIRTXPORTS, 0x00 पूर्ण;
	u8 irbuf[MCE_IRBUF_SIZE];
	पूर्णांक ircount = 0;
	अचिन्हित पूर्णांक irsample;
	पूर्णांक i, length, ret;

	/* Send the set TX ports command */
	cmdbuf[2] = ir->tx_mask;
	mce_command_out(ir, cmdbuf, माप(cmdbuf));

	/* Generate mce IR data packet */
	क्रम (i = 0; i < count; i++) अणु
		irsample = txbuf[i] / MCE_TIME_UNIT;

		/* loop to support दीर्घ pulses/spaces > 6350us (127*50us) */
		जबतक (irsample > 0) अणु
			/* Insert IR header every 30th entry */
			अगर (ircount % MCE_PACKET_SIZE == 0) अणु
				/* Room क्रम IR header and one IR sample? */
				अगर (ircount >= MCE_IRBUF_SIZE - 1) अणु
					/* Send near full buffer */
					ret = mce_ग_लिखो(ir, irbuf, ircount);
					अगर (ret < 0)
						वापस ret;
					ircount = 0;
				पूर्ण
				irbuf[ircount++] = MCE_IRDATA_HEADER;
			पूर्ण

			/* Insert IR sample */
			अगर (irsample <= MCE_MAX_PULSE_LENGTH) अणु
				irbuf[ircount] = irsample;
				irsample = 0;
			पूर्ण अन्यथा अणु
				irbuf[ircount] = MCE_MAX_PULSE_LENGTH;
				irsample -= MCE_MAX_PULSE_LENGTH;
			पूर्ण
			/*
			 * Even i = IR pulse
			 * Odd  i = IR space
			 */
			irbuf[ircount] |= (i & 1 ? 0 : MCE_PULSE_BIT);
			ircount++;

			/* IR buffer full? */
			अगर (ircount >= MCE_IRBUF_SIZE) अणु
				/* Fix packet length in last header */
				length = ircount % MCE_PACKET_SIZE;
				अगर (length > 0)
					irbuf[ircount - length] -=
						MCE_PACKET_SIZE - length;
				/* Send full buffer */
				ret = mce_ग_लिखो(ir, irbuf, ircount);
				अगर (ret < 0)
					वापस ret;
				ircount = 0;
			पूर्ण
		पूर्ण
	पूर्ण /* after क्रम loop, 0 <= ircount < MCE_IRBUF_SIZE */

	/* Fix packet length in last header */
	length = ircount % MCE_PACKET_SIZE;
	अगर (length > 0)
		irbuf[ircount - length] -= MCE_PACKET_SIZE - length;

	/* Append IR trailer (0x80) to final partial (or empty) IR buffer */
	irbuf[ircount++] = MCE_IRDATA_TRAILER;

	/* Send final buffer */
	ret = mce_ग_लिखो(ir, irbuf, ircount);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

/* Sets active IR outमाला_दो -- mce devices typically have two */
अटल पूर्णांक mceusb_set_tx_mask(काष्ठा rc_dev *dev, u32 mask)
अणु
	काष्ठा mceusb_dev *ir = dev->priv;

	/* वापस number of transmitters */
	पूर्णांक emitters = ir->num_txports ? ir->num_txports : 2;

	अगर (mask >= (1 << emitters))
		वापस emitters;

	अगर (ir->flags.tx_mask_normal)
		ir->tx_mask = mask;
	अन्यथा
		ir->tx_mask = (mask != MCE_DEFAULT_TX_MASK ?
				mask ^ MCE_DEFAULT_TX_MASK : mask) << 1;

	वापस 0;
पूर्ण

/* Sets the send carrier frequency and mode */
अटल पूर्णांक mceusb_set_tx_carrier(काष्ठा rc_dev *dev, u32 carrier)
अणु
	काष्ठा mceusb_dev *ir = dev->priv;
	पूर्णांक clk = 10000000;
	पूर्णांक prescaler = 0, भागisor = 0;
	अचिन्हित अक्षर cmdbuf[4] = अणु MCE_CMD_PORT_IR,
				    MCE_CMD_SETIRCFS, 0x00, 0x00 पूर्ण;

	/* Carrier has changed */
	अगर (ir->carrier != carrier) अणु

		अगर (carrier == 0) अणु
			ir->carrier = carrier;
			cmdbuf[2] = MCE_CMD_SIG_END;
			cmdbuf[3] = MCE_IRDATA_TRAILER;
			dev_dbg(ir->dev, "disabling carrier modulation");
			mce_command_out(ir, cmdbuf, माप(cmdbuf));
			वापस 0;
		पूर्ण

		क्रम (prescaler = 0; prescaler < 4; ++prescaler) अणु
			भागisor = (clk >> (2 * prescaler)) / carrier;
			अगर (भागisor <= 0xff) अणु
				ir->carrier = carrier;
				cmdbuf[2] = prescaler;
				cmdbuf[3] = भागisor;
				dev_dbg(ir->dev, "requesting %u HZ carrier",
								carrier);

				/* Transmit new carrier to mce device */
				mce_command_out(ir, cmdbuf, माप(cmdbuf));
				वापस 0;
			पूर्ण
		पूर्ण

		वापस -EINVAL;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mceusb_set_समयout(काष्ठा rc_dev *dev, अचिन्हित पूर्णांक समयout)
अणु
	u8 cmdbuf[4] = अणु MCE_CMD_PORT_IR, MCE_CMD_SETIRTIMEOUT, 0, 0 पूर्ण;
	काष्ठा mceusb_dev *ir = dev->priv;
	अचिन्हित पूर्णांक units;

	units = DIV_ROUND_CLOSEST(समयout, MCE_TIME_UNIT);

	cmdbuf[2] = units >> 8;
	cmdbuf[3] = units;

	mce_command_out(ir, cmdbuf, माप(cmdbuf));

	/* get receiver समयout value */
	mce_command_out(ir, GET_RX_TIMEOUT, माप(GET_RX_TIMEOUT));

	वापस 0;
पूर्ण

/*
 * Select or deselect the 2nd receiver port.
 * Second receiver is learning mode, wide-band, लघु-range receiver.
 * Only one receiver (दीर्घ or लघु range) may be active at a समय.
 */
अटल पूर्णांक mceusb_set_rx_wideband(काष्ठा rc_dev *dev, पूर्णांक enable)
अणु
	काष्ठा mceusb_dev *ir = dev->priv;
	अचिन्हित अक्षर cmdbuf[3] = अणु MCE_CMD_PORT_IR,
				    MCE_CMD_SETIRRXPORTEN, 0x00 पूर्ण;

	dev_dbg(ir->dev, "select %s-range receive sensor",
		enable ? "short" : "long");
	अगर (enable) अणु
		ir->wideband_rx_enabled = true;
		cmdbuf[2] = 2;	/* port 2 is लघु range receiver */
	पूर्ण अन्यथा अणु
		ir->wideband_rx_enabled = false;
		cmdbuf[2] = 1;	/* port 1 is दीर्घ range receiver */
	पूर्ण
	mce_command_out(ir, cmdbuf, माप(cmdbuf));
	/* response from device sets ir->learning_active */

	वापस 0;
पूर्ण

/*
 * Enable/disable receiver carrier frequency pass through reporting.
 * Only the लघु-range receiver has carrier frequency measuring capability.
 * Implicitly select this receiver when enabling carrier frequency reporting.
 */
अटल पूर्णांक mceusb_set_rx_carrier_report(काष्ठा rc_dev *dev, पूर्णांक enable)
अणु
	काष्ठा mceusb_dev *ir = dev->priv;
	अचिन्हित अक्षर cmdbuf[3] = अणु MCE_CMD_PORT_IR,
				    MCE_CMD_SETIRRXPORTEN, 0x00 पूर्ण;

	dev_dbg(ir->dev, "%s short-range receiver carrier reporting",
		enable ? "enable" : "disable");
	अगर (enable) अणु
		ir->carrier_report_enabled = true;
		अगर (!ir->learning_active) अणु
			cmdbuf[2] = 2;	/* port 2 is लघु range receiver */
			mce_command_out(ir, cmdbuf, माप(cmdbuf));
		पूर्ण
	पूर्ण अन्यथा अणु
		ir->carrier_report_enabled = false;
		/*
		 * Revert to normal (दीर्घ-range) receiver only अगर the
		 * wideband (लघु-range) receiver wasn't explicitly
		 * enabled.
		 */
		अगर (ir->learning_active && !ir->wideband_rx_enabled) अणु
			cmdbuf[2] = 1;	/* port 1 is दीर्घ range receiver */
			mce_command_out(ir, cmdbuf, माप(cmdbuf));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Handle PORT_SYS/IR command response received from the MCE device.
 *
 * Assumes single response with all its data (not truncated)
 * in buf_in[]. The response itself determines its total length
 * (mceusb_cmd_datasize() + 2) and hence the minimum size of buf_in[].
 *
 * We करोn't करो anything but prपूर्णांक debug spew क्रम many of the command bits
 * we receive from the hardware, but some of them are useful inक्रमmation
 * we want to store so that we can use them.
 */
अटल व्योम mceusb_handle_command(काष्ठा mceusb_dev *ir, u8 *buf_in)
अणु
	u8 cmd = buf_in[0];
	u8 subcmd = buf_in[1];
	u8 *hi = &buf_in[2];		/* पढ़ो only when required */
	u8 *lo = &buf_in[3];		/* पढ़ो only when required */
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	u32 carrier_cycles;
	u32 cycles_fix;

	अगर (cmd == MCE_CMD_PORT_SYS) अणु
		चयन (subcmd) अणु
		/* the one and only 5-byte वापस value command */
		हाल MCE_RSP_GETPORTSTATUS:
			अगर (buf_in[5] == 0 && *hi < 8)
				ir->txports_cabled |= 1 << *hi;
			अवरोध;

		/* 1-byte वापस value commands */
		हाल MCE_RSP_EQEMVER:
			ir->emver = *hi;
			अवरोध;

		/* No वापस value commands */
		हाल MCE_RSP_CMD_ILLEGAL:
			ir->need_reset = true;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		वापस;
	पूर्ण

	अगर (cmd != MCE_CMD_PORT_IR)
		वापस;

	चयन (subcmd) अणु
	/* 2-byte वापस value commands */
	हाल MCE_RSP_EQIRTIMEOUT:
		ir->rc->समयout = (*hi << 8 | *lo) * MCE_TIME_UNIT;
		अवरोध;
	हाल MCE_RSP_EQIRNUMPORTS:
		ir->num_txports = *hi;
		ir->num_rxports = *lo;
		अवरोध;
	हाल MCE_RSP_EQIRRXCFCNT:
		/*
		 * The carrier cycle counter can overflow and wrap around
		 * without notice from the device. So frequency measurement
		 * will be inaccurate with दीर्घ duration IR.
		 *
		 * The दीर्घ-range (non learning) receiver always reports
		 * zero count so we always ignore its report.
		 */
		अगर (ir->carrier_report_enabled && ir->learning_active &&
		    ir->pulse_tunit > 0) अणु
			carrier_cycles = (*hi << 8 | *lo);
			/*
			 * Adjust carrier cycle count by adding
			 * 1 missed count per pulse "on"
			 */
			cycles_fix = ir->flags.rx2 == 2 ? ir->pulse_count : 0;
			rawir.carrier_report = 1;
			rawir.carrier = (1000000u / MCE_TIME_UNIT) *
					(carrier_cycles + cycles_fix) /
					ir->pulse_tunit;
			dev_dbg(ir->dev, "RX carrier frequency %u Hz (pulse count = %u, cycles = %u, duration = %u, rx2 = %u)",
				rawir.carrier, ir->pulse_count, carrier_cycles,
				ir->pulse_tunit, ir->flags.rx2);
			ir_raw_event_store(ir->rc, &rawir);
		पूर्ण
		अवरोध;

	/* 1-byte वापस value commands */
	हाल MCE_RSP_EQIRTXPORTS:
		ir->tx_mask = *hi;
		अवरोध;
	हाल MCE_RSP_EQIRRXPORTEN:
		ir->learning_active = ((*hi & 0x02) == 0x02);
		अगर (ir->rxports_active != *hi) अणु
			dev_info(ir->dev, "%s-range (0x%x) receiver active",
				 ir->learning_active ? "short" : "long", *hi);
			ir->rxports_active = *hi;
		पूर्ण
		अवरोध;

	/* No वापस value commands */
	हाल MCE_RSP_CMD_ILLEGAL:
	हाल MCE_RSP_TX_TIMEOUT:
		ir->need_reset = true;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mceusb_process_ir_data(काष्ठा mceusb_dev *ir, पूर्णांक buf_len)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	bool event = false;
	पूर्णांक i = 0;

	/* skip meaningless 0xb1 0x60 header bytes on orig receiver */
	अगर (ir->flags.microsoft_gen1)
		i = 2;

	/* अगर there's no data, just वापस now */
	अगर (buf_len <= i)
		वापस;

	क्रम (; i < buf_len; i++) अणु
		चयन (ir->parser_state) अणु
		हाल SUBCMD:
			ir->rem = mceusb_cmd_datasize(ir->cmd, ir->buf_in[i]);
			mceusb_dev_prपूर्णांकdata(ir, ir->buf_in, buf_len, i - 1,
					     ir->rem + 2, false);
			अगर (i + ir->rem < buf_len)
				mceusb_handle_command(ir, &ir->buf_in[i - 1]);
			ir->parser_state = CMD_DATA;
			अवरोध;
		हाल PARSE_IRDATA:
			ir->rem--;
			rawir.pulse = ((ir->buf_in[i] & MCE_PULSE_BIT) != 0);
			rawir.duration = (ir->buf_in[i] & MCE_PULSE_MASK);
			अगर (unlikely(!rawir.duration)) अणु
				dev_dbg(ir->dev, "nonsensical irdata %02x with duration 0",
					ir->buf_in[i]);
				अवरोध;
			पूर्ण
			अगर (rawir.pulse) अणु
				ir->pulse_tunit += rawir.duration;
				ir->pulse_count++;
			पूर्ण
			rawir.duration *= MCE_TIME_UNIT;

			dev_dbg(ir->dev, "Storing %s %u us (%02x)",
				rawir.pulse ? "pulse" : "space",
				rawir.duration,	ir->buf_in[i]);

			अगर (ir_raw_event_store_with_filter(ir->rc, &rawir))
				event = true;
			अवरोध;
		हाल CMD_DATA:
			ir->rem--;
			अवरोध;
		हाल CMD_HEADER:
			ir->cmd = ir->buf_in[i];
			अगर ((ir->cmd == MCE_CMD_PORT_IR) ||
			    ((ir->cmd & MCE_PORT_MASK) !=
			     MCE_COMMAND_IRDATA)) अणु
				/*
				 * got PORT_SYS, PORT_IR, or unknown
				 * command response prefix
				 */
				ir->parser_state = SUBCMD;
				जारी;
			पूर्ण
			/*
			 * got IR data prefix (0x80 + num_bytes)
			 * decode MCE packets of the क्रमm अणु0x83, AA, BB, CCपूर्ण
			 * IR data packets can span USB messages
			 */
			ir->rem = (ir->cmd & MCE_PACKET_LENGTH_MASK);
			mceusb_dev_prपूर्णांकdata(ir, ir->buf_in, buf_len,
					     i, ir->rem + 1, false);
			अगर (ir->rem) अणु
				ir->parser_state = PARSE_IRDATA;
			पूर्ण अन्यथा अणु
				काष्ठा ir_raw_event ev = अणु
					.समयout = 1,
					.duration = ir->rc->समयout
				पूर्ण;

				अगर (ir_raw_event_store_with_filter(ir->rc,
								   &ev))
					event = true;
				ir->pulse_tunit = 0;
				ir->pulse_count = 0;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (ir->parser_state != CMD_HEADER && !ir->rem)
			ir->parser_state = CMD_HEADER;
	पूर्ण

	/*
	 * Accept IR data spanning multiple rx buffers.
	 * Reject MCE command response spanning multiple rx buffers.
	 */
	अगर (ir->parser_state != PARSE_IRDATA || !ir->rem)
		ir->parser_state = CMD_HEADER;

	अगर (event) अणु
		dev_dbg(ir->dev, "processed IR data");
		ir_raw_event_handle(ir->rc);
	पूर्ण
पूर्ण

अटल व्योम mceusb_dev_recv(काष्ठा urb *urb)
अणु
	काष्ठा mceusb_dev *ir;

	अगर (!urb)
		वापस;

	ir = urb->context;
	अगर (!ir) अणु
		usb_unlink_urb(urb);
		वापस;
	पूर्ण

	चयन (urb->status) अणु
	/* success */
	हाल 0:
		mceusb_process_ir_data(ir, urb->actual_length);
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -EILSEQ:
	हाल -ESHUTDOWN:
		usb_unlink_urb(urb);
		वापस;

	हाल -EPIPE:
		dev_err(ir->dev, "Error: urb status = %d (RX HALT)",
			urb->status);
		mceusb_defer_kevent(ir, EVENT_RX_HALT);
		वापस;

	शेष:
		dev_err(ir->dev, "Error: urb status = %d", urb->status);
		अवरोध;
	पूर्ण

	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल व्योम mceusb_get_emulator_version(काष्ठा mceusb_dev *ir)
अणु
	/* If we get no reply or an illegal command reply, its ver 1, says MS */
	ir->emver = 1;
	mce_command_out(ir, GET_EMVER, माप(GET_EMVER));
पूर्ण

अटल व्योम mceusb_gen1_init(काष्ठा mceusb_dev *ir)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = ir->dev;
	अक्षर *data;

	data = kzalloc(USB_CTRL_MSG_SZ, GFP_KERNEL);
	अगर (!data) अणु
		dev_err(dev, "%s: memory allocation failed!", __func__);
		वापस;
	पूर्ण

	/*
	 * This is a strange one. Winकरोws issues a set address to the device
	 * on the receive control pipe and expect a certain value pair back
	 */
	ret = usb_control_msg(ir->usbdev, usb_rcvctrlpipe(ir->usbdev, 0),
			      USB_REQ_SET_ADDRESS, USB_TYPE_VENDOR, 0, 0,
			      data, USB_CTRL_MSG_SZ, HZ * 3);
	dev_dbg(dev, "set address - ret = %d", ret);
	dev_dbg(dev, "set address - data[0] = %d, data[1] = %d",
						data[0], data[1]);

	/* set feature: bit rate 38400 bps */
	ret = usb_control_msg(ir->usbdev, usb_sndctrlpipe(ir->usbdev, 0),
			      USB_REQ_SET_FEATURE, USB_TYPE_VENDOR,
			      0xc04e, 0x0000, शून्य, 0, HZ * 3);

	dev_dbg(dev, "set feature - ret = %d", ret);

	/* bRequest 4: set अक्षर length to 8 bits */
	ret = usb_control_msg(ir->usbdev, usb_sndctrlpipe(ir->usbdev, 0),
			      4, USB_TYPE_VENDOR,
			      0x0808, 0x0000, शून्य, 0, HZ * 3);
	dev_dbg(dev, "set char length - retB = %d", ret);

	/* bRequest 2: set handshaking to use DTR/DSR */
	ret = usb_control_msg(ir->usbdev, usb_sndctrlpipe(ir->usbdev, 0),
			      2, USB_TYPE_VENDOR,
			      0x0000, 0x0100, शून्य, 0, HZ * 3);
	dev_dbg(dev, "set handshake  - retC = %d", ret);

	/* device resume */
	mce_command_out(ir, DEVICE_RESUME, माप(DEVICE_RESUME));

	/* get hw/sw revision? */
	mce_command_out(ir, GET_REVISION, माप(GET_REVISION));

	kमुक्त(data);
पूर्ण

अटल व्योम mceusb_gen2_init(काष्ठा mceusb_dev *ir)
अणु
	/* device resume */
	mce_command_out(ir, DEVICE_RESUME, माप(DEVICE_RESUME));

	/* get wake version (protocol, key, address) */
	mce_command_out(ir, GET_WAKEVERSION, माप(GET_WAKEVERSION));

	/* unknown what this one actually वापसs... */
	mce_command_out(ir, GET_UNKNOWN2, माप(GET_UNKNOWN2));
पूर्ण

अटल व्योम mceusb_get_parameters(काष्ठा mceusb_dev *ir)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर cmdbuf[3] = अणु MCE_CMD_PORT_SYS,
				    MCE_CMD_GETPORTSTATUS, 0x00 पूर्ण;

	/* शेषs, अगर the hardware करोesn't support querying */
	ir->num_txports = 2;
	ir->num_rxports = 2;

	/* get number of tx and rx ports */
	mce_command_out(ir, GET_NUM_PORTS, माप(GET_NUM_PORTS));

	/* get the carrier and frequency */
	mce_command_out(ir, GET_CARRIER_FREQ, माप(GET_CARRIER_FREQ));

	अगर (ir->num_txports && !ir->flags.no_tx)
		/* get the transmitter biपंचांगask */
		mce_command_out(ir, GET_TX_BITMASK, माप(GET_TX_BITMASK));

	/* get receiver समयout value */
	mce_command_out(ir, GET_RX_TIMEOUT, माप(GET_RX_TIMEOUT));

	/* get receiver sensor setting */
	mce_command_out(ir, GET_RX_SENSOR, माप(GET_RX_SENSOR));

	क्रम (i = 0; i < ir->num_txports; i++) अणु
		cmdbuf[2] = i;
		mce_command_out(ir, cmdbuf, माप(cmdbuf));
	पूर्ण
पूर्ण

अटल व्योम mceusb_flash_led(काष्ठा mceusb_dev *ir)
अणु
	अगर (ir->emver < 2)
		वापस;

	mce_command_out(ir, FLASH_LED, माप(FLASH_LED));
पूर्ण

/*
 * Workqueue function
 * क्रम resetting or recovering device after occurrence of error events
 * specअगरied in ir->kevent bit field.
 * Function runs (via schedule_work()) in non-पूर्णांकerrupt context, क्रम
 * calls here (such as usb_clear_halt()) requiring non-पूर्णांकerrupt context.
 */
अटल व्योम mceusb_deferred_kevent(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mceusb_dev *ir =
		container_of(work, काष्ठा mceusb_dev, kevent);
	पूर्णांक status;

	dev_err(ir->dev, "kevent handler called (flags 0x%lx)",
		ir->kevent_flags);

	अगर (test_bit(EVENT_RST_PEND, &ir->kevent_flags)) अणु
		dev_err(ir->dev, "kevent handler canceled pending USB Reset Device");
		वापस;
	पूर्ण

	अगर (test_bit(EVENT_RX_HALT, &ir->kevent_flags)) अणु
		usb_unlink_urb(ir->urb_in);
		status = usb_clear_halt(ir->usbdev, ir->pipe_in);
		dev_err(ir->dev, "rx clear halt status = %d", status);
		अगर (status < 0) अणु
			/*
			 * Unable to clear RX halt/stall.
			 * Will need to call usb_reset_device().
			 */
			dev_err(ir->dev,
				"stuck RX HALT state requires USB Reset Device to clear");
			usb_queue_reset_device(ir->usbपूर्णांकf);
			set_bit(EVENT_RST_PEND, &ir->kevent_flags);
			clear_bit(EVENT_RX_HALT, &ir->kevent_flags);

			/* Cancel all other error events and handlers */
			clear_bit(EVENT_TX_HALT, &ir->kevent_flags);
			वापस;
		पूर्ण
		clear_bit(EVENT_RX_HALT, &ir->kevent_flags);
		status = usb_submit_urb(ir->urb_in, GFP_KERNEL);
		अगर (status < 0) अणु
			dev_err(ir->dev, "rx unhalt submit urb error = %d",
				status);
		पूर्ण
	पूर्ण

	अगर (test_bit(EVENT_TX_HALT, &ir->kevent_flags)) अणु
		status = usb_clear_halt(ir->usbdev, ir->pipe_out);
		dev_err(ir->dev, "tx clear halt status = %d", status);
		अगर (status < 0) अणु
			/*
			 * Unable to clear TX halt/stall.
			 * Will need to call usb_reset_device().
			 */
			dev_err(ir->dev,
				"stuck TX HALT state requires USB Reset Device to clear");
			usb_queue_reset_device(ir->usbपूर्णांकf);
			set_bit(EVENT_RST_PEND, &ir->kevent_flags);
			clear_bit(EVENT_TX_HALT, &ir->kevent_flags);

			/* Cancel all other error events and handlers */
			clear_bit(EVENT_RX_HALT, &ir->kevent_flags);
			वापस;
		पूर्ण
		clear_bit(EVENT_TX_HALT, &ir->kevent_flags);
	पूर्ण
पूर्ण

अटल काष्ठा rc_dev *mceusb_init_rc_dev(काष्ठा mceusb_dev *ir)
अणु
	काष्ठा usb_device *udev = ir->usbdev;
	काष्ठा device *dev = ir->dev;
	काष्ठा rc_dev *rc;
	पूर्णांक ret;

	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rc) अणु
		dev_err(dev, "remote dev allocation failed");
		जाओ out;
	पूर्ण

	snम_लिखो(ir->name, माप(ir->name), "%s (%04x:%04x)",
		 mceusb_model[ir->model].name ?
			mceusb_model[ir->model].name :
			"Media Center Ed. eHome Infrared Remote Transceiver",
		 le16_to_cpu(ir->usbdev->descriptor.idVenकरोr),
		 le16_to_cpu(ir->usbdev->descriptor.idProduct));

	usb_make_path(ir->usbdev, ir->phys, माप(ir->phys));

	rc->device_name = ir->name;
	rc->input_phys = ir->phys;
	usb_to_input_id(ir->usbdev, &rc->input_id);
	rc->dev.parent = dev;
	rc->priv = ir;
	rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rc->min_समयout = MCE_TIME_UNIT;
	rc->समयout = MS_TO_US(100);
	अगर (!mceusb_model[ir->model].broken_irसमयout) अणु
		rc->s_समयout = mceusb_set_समयout;
		rc->max_समयout = 10 * IR_DEFAULT_TIMEOUT;
	पूर्ण अन्यथा अणु
		/*
		 * If we can't set the समयout using CMD_SETIRTIMEOUT, we can
		 * rely on software समयouts क्रम समयouts < 100ms.
		 */
		rc->max_समयout = rc->समयout;
	पूर्ण
	अगर (!ir->flags.no_tx) अणु
		rc->s_tx_mask = mceusb_set_tx_mask;
		rc->s_tx_carrier = mceusb_set_tx_carrier;
		rc->tx_ir = mceusb_tx_ir;
	पूर्ण
	अगर (ir->flags.rx2 > 0) अणु
		rc->s_learning_mode = mceusb_set_rx_wideband;
		rc->s_carrier_report = mceusb_set_rx_carrier_report;
	पूर्ण
	rc->driver_name = DRIVER_NAME;

	चयन (le16_to_cpu(udev->descriptor.idVenकरोr)) अणु
	हाल VENDOR_HAUPPAUGE:
		rc->map_name = RC_MAP_HAUPPAUGE;
		अवरोध;
	हाल VENDOR_PCTV:
		rc->map_name = RC_MAP_PINNACLE_PCTV_HD;
		अवरोध;
	शेष:
		rc->map_name = RC_MAP_RC6_MCE;
	पूर्ण
	अगर (mceusb_model[ir->model].rc_map)
		rc->map_name = mceusb_model[ir->model].rc_map;

	ret = rc_रेजिस्टर_device(rc);
	अगर (ret < 0) अणु
		dev_err(dev, "remote dev registration failed");
		जाओ out;
	पूर्ण

	वापस rc;

out:
	rc_मुक्त_device(rc);
	वापस शून्य;
पूर्ण

अटल पूर्णांक mceusb_dev_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *idesc;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_in = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_out = शून्य;
	काष्ठा mceusb_dev *ir = शून्य;
	पूर्णांक pipe, maxp, i, res;
	अक्षर buf[63], name[128] = "";
	क्रमागत mceusb_model_type model = id->driver_info;
	bool is_gen3;
	bool is_microsoft_gen1;
	bool tx_mask_normal;
	पूर्णांक ir_पूर्णांकfnum;

	dev_dbg(&पूर्णांकf->dev, "%s called", __func__);

	idesc  = पूर्णांकf->cur_altsetting;

	is_gen3 = mceusb_model[model].mce_gen3;
	is_microsoft_gen1 = mceusb_model[model].mce_gen1;
	tx_mask_normal = mceusb_model[model].tx_mask_normal;
	ir_पूर्णांकfnum = mceusb_model[model].ir_पूर्णांकfnum;

	/* There are multi-function devices with non-IR पूर्णांकerfaces */
	अगर (idesc->desc.bInterfaceNumber != ir_पूर्णांकfnum)
		वापस -ENODEV;

	/* step through the endpoपूर्णांकs to find first bulk in and out endpoपूर्णांक */
	क्रम (i = 0; i < idesc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		ep = &idesc->endpoपूर्णांक[i].desc;

		अगर (ep_in == शून्य) अणु
			अगर (usb_endpoपूर्णांक_is_bulk_in(ep)) अणु
				ep_in = ep;
				dev_dbg(&पूर्णांकf->dev, "acceptable bulk inbound endpoint found\n");
			पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_पूर्णांक_in(ep)) अणु
				ep_in = ep;
				ep_in->bInterval = 1;
				dev_dbg(&पूर्णांकf->dev, "acceptable interrupt inbound endpoint found\n");
			पूर्ण
		पूर्ण

		अगर (ep_out == शून्य) अणु
			अगर (usb_endpoपूर्णांक_is_bulk_out(ep)) अणु
				ep_out = ep;
				dev_dbg(&पूर्णांकf->dev, "acceptable bulk outbound endpoint found\n");
			पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_पूर्णांक_out(ep)) अणु
				ep_out = ep;
				ep_out->bInterval = 1;
				dev_dbg(&पूर्णांकf->dev, "acceptable interrupt outbound endpoint found\n");
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!ep_in || !ep_out) अणु
		dev_dbg(&पूर्णांकf->dev, "required endpoints not found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep_in))
		pipe = usb_rcvपूर्णांकpipe(dev, ep_in->bEndpoपूर्णांकAddress);
	अन्यथा
		pipe = usb_rcvbulkpipe(dev, ep_in->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe));

	ir = kzalloc(माप(काष्ठा mceusb_dev), GFP_KERNEL);
	अगर (!ir)
		जाओ mem_alloc_fail;

	ir->pipe_in = pipe;
	ir->buf_in = usb_alloc_coherent(dev, maxp, GFP_KERNEL, &ir->dma_in);
	अगर (!ir->buf_in)
		जाओ buf_in_alloc_fail;

	ir->urb_in = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!ir->urb_in)
		जाओ urb_in_alloc_fail;

	ir->usbपूर्णांकf = पूर्णांकf;
	ir->usbdev = usb_get_dev(dev);
	ir->dev = &पूर्णांकf->dev;
	ir->len_in = maxp;
	ir->flags.microsoft_gen1 = is_microsoft_gen1;
	ir->flags.tx_mask_normal = tx_mask_normal;
	ir->flags.no_tx = mceusb_model[model].no_tx;
	ir->flags.rx2 = mceusb_model[model].rx2;
	ir->model = model;

	/* Saving usb पूर्णांकerface data क्रम use by the transmitter routine */
	ir->usb_ep_out = ep_out;
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep_out))
		ir->pipe_out = usb_sndपूर्णांकpipe(ir->usbdev,
					      ep_out->bEndpoपूर्णांकAddress);
	अन्यथा
		ir->pipe_out = usb_sndbulkpipe(ir->usbdev,
					       ep_out->bEndpoपूर्णांकAddress);

	अगर (dev->descriptor.iManufacturer
	    && usb_string(dev, dev->descriptor.iManufacturer,
			  buf, माप(buf)) > 0)
		strscpy(name, buf, माप(name));
	अगर (dev->descriptor.iProduct
	    && usb_string(dev, dev->descriptor.iProduct,
			  buf, माप(buf)) > 0)
		snम_लिखो(name + म_माप(name), माप(name) - म_माप(name),
			 " %s", buf);

	/*
	 * Initialize async USB error handler beक्रमe रेजिस्टरing
	 * or activating any mceusb RX and TX functions
	 */
	INIT_WORK(&ir->kevent, mceusb_deferred_kevent);

	ir->rc = mceusb_init_rc_dev(ir);
	अगर (!ir->rc)
		जाओ rc_dev_fail;

	/* wire up inbound data handler */
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep_in))
		usb_fill_पूर्णांक_urb(ir->urb_in, dev, pipe, ir->buf_in, maxp,
				 mceusb_dev_recv, ir, ep_in->bInterval);
	अन्यथा
		usb_fill_bulk_urb(ir->urb_in, dev, pipe, ir->buf_in, maxp,
				  mceusb_dev_recv, ir);

	ir->urb_in->transfer_dma = ir->dma_in;
	ir->urb_in->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* flush buffers on the device */
	dev_dbg(&पूर्णांकf->dev, "Flushing receive buffers");
	res = usb_submit_urb(ir->urb_in, GFP_KERNEL);
	अगर (res)
		dev_err(&पूर्णांकf->dev, "failed to flush buffers: %d", res);

	/* figure out which firmware/emulator version this hardware has */
	mceusb_get_emulator_version(ir);

	/* initialize device */
	अगर (ir->flags.microsoft_gen1)
		mceusb_gen1_init(ir);
	अन्यथा अगर (!is_gen3)
		mceusb_gen2_init(ir);

	mceusb_get_parameters(ir);

	mceusb_flash_led(ir);

	अगर (!ir->flags.no_tx)
		mceusb_set_tx_mask(ir->rc, MCE_DEFAULT_TX_MASK);

	usb_set_पूर्णांकfdata(पूर्णांकf, ir);

	/* enable wake via this device */
	device_set_wakeup_capable(ir->dev, true);
	device_set_wakeup_enable(ir->dev, true);

	dev_info(&पूर्णांकf->dev, "Registered %s with mce emulator interface version %x",
		name, ir->emver);
	dev_info(&पूर्णांकf->dev, "%x tx ports (0x%x cabled) and %x rx sensors (0x%x active)",
		 ir->num_txports, ir->txports_cabled,
		 ir->num_rxports, ir->rxports_active);

	वापस 0;

	/* Error-handling path */
rc_dev_fail:
	cancel_work_sync(&ir->kevent);
	usb_put_dev(ir->usbdev);
	usb_समाप्त_urb(ir->urb_in);
	usb_मुक्त_urb(ir->urb_in);
urb_in_alloc_fail:
	usb_मुक्त_coherent(dev, maxp, ir->buf_in, ir->dma_in);
buf_in_alloc_fail:
	kमुक्त(ir);
mem_alloc_fail:
	dev_err(&पूर्णांकf->dev, "%s: device setup failed!", __func__);

	वापस -ENOMEM;
पूर्ण


अटल व्योम mceusb_dev_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा mceusb_dev *ir = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_dbg(&पूर्णांकf->dev, "%s called", __func__);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (!ir)
		वापस;

	ir->usbdev = शून्य;
	cancel_work_sync(&ir->kevent);
	rc_unरेजिस्टर_device(ir->rc);
	usb_समाप्त_urb(ir->urb_in);
	usb_मुक्त_urb(ir->urb_in);
	usb_मुक्त_coherent(dev, ir->len_in, ir->buf_in, ir->dma_in);
	usb_put_dev(dev);

	kमुक्त(ir);
पूर्ण

अटल पूर्णांक mceusb_dev_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा mceusb_dev *ir = usb_get_पूर्णांकfdata(पूर्णांकf);
	dev_info(ir->dev, "suspend");
	usb_समाप्त_urb(ir->urb_in);
	वापस 0;
पूर्ण

अटल पूर्णांक mceusb_dev_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा mceusb_dev *ir = usb_get_पूर्णांकfdata(पूर्णांकf);
	dev_info(ir->dev, "resume");
	अगर (usb_submit_urb(ir->urb_in, GFP_ATOMIC))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा usb_driver mceusb_dev_driver = अणु
	.name =		DRIVER_NAME,
	.probe =	mceusb_dev_probe,
	.disconnect =	mceusb_dev_disconnect,
	.suspend =	mceusb_dev_suspend,
	.resume =	mceusb_dev_resume,
	.reset_resume =	mceusb_dev_resume,
	.id_table =	mceusb_dev_table
पूर्ण;

module_usb_driver(mceusb_dev_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(usb, mceusb_dev_table);
