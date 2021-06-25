<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * at76c503/at76c505 USB driver
 *
 * Copyright (c) 2002 - 2003 Oliver Kurth
 * Copyright (c) 2004 Joerg Albert <joerg.albert@gmx.de>
 * Copyright (c) 2004 Nick Jones
 * Copyright (c) 2004 Balपूर्णांक Seeber <n0_5p4m_p13453@hoपंचांगail.com>
 * Copyright (c) 2007 Guiकरो Guenther <agx@sigxcpu.org>
 * Copyright (c) 2007 Kalle Valo <kalle.valo@iki.fi>
 * Copyright (c) 2010 Sebastian Smolorz <sesmo@gmx.net>
 *
 * This file is part of the Berlios driver क्रम WLAN USB devices based on the
 * Aपंचांगel AT76C503A/505/505A.
 *
 * Some iw_handler code was taken from airo.c, (C) 1999 Benjamin Reed
 *
 * TODO list is at the wiki:
 *
 * https://wireless.wiki.kernel.org/en/users/Drivers/at76c50x-usb#TODO
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <linux/firmware.h>
#समावेश <linux/leds.h>
#समावेश <net/mac80211.h>

#समावेश "at76c50x-usb.h"

/* Version inक्रमmation */
#घोषणा DRIVER_NAME "at76c50x-usb"
#घोषणा DRIVER_VERSION	"0.17"
#घोषणा DRIVER_DESC "Atmel at76x USB Wireless LAN Driver"

/* at76_debug bits */
#घोषणा DBG_PROGRESS		0x00000001	/* authentication/accociation */
#घोषणा DBG_BSS_TABLE		0x00000002	/* show BSS table after scans */
#घोषणा DBG_IOCTL		0x00000004	/* ioctl calls / settings */
#घोषणा DBG_MAC_STATE		0x00000008	/* MAC state transitions */
#घोषणा DBG_TX_DATA		0x00000010	/* tx header */
#घोषणा DBG_TX_DATA_CONTENT	0x00000020	/* tx content */
#घोषणा DBG_TX_MGMT		0x00000040	/* tx management */
#घोषणा DBG_RX_DATA		0x00000080	/* rx data header */
#घोषणा DBG_RX_DATA_CONTENT	0x00000100	/* rx data content */
#घोषणा DBG_RX_MGMT		0x00000200	/* rx mgmt frame headers */
#घोषणा DBG_RX_BEACON		0x00000400	/* rx beacon */
#घोषणा DBG_RX_CTRL		0x00000800	/* rx control */
#घोषणा DBG_RX_MGMT_CONTENT	0x00001000	/* rx mgmt content */
#घोषणा DBG_RX_FRAGS		0x00002000	/* rx data fragment handling */
#घोषणा DBG_DEVSTART		0x00004000	/* fw करोwnload, device start */
#घोषणा DBG_URB			0x00008000	/* rx urb status, ... */
#घोषणा DBG_RX_ATMEL_HDR	0x00010000	/* Aपंचांगel-specअगरic Rx headers */
#घोषणा DBG_PROC_ENTRY		0x00020000	/* procedure entries/निकासs */
#घोषणा DBG_PM			0x00040000	/* घातer management settings */
#घोषणा DBG_BSS_MATCH		0x00080000	/* BSS match failures */
#घोषणा DBG_PARAMS		0x00100000	/* show configured parameters */
#घोषणा DBG_WAIT_COMPLETE	0x00200000	/* command completion */
#घोषणा DBG_RX_FRAGS_SKB	0x00400000	/* skb header of Rx fragments */
#घोषणा DBG_BSS_TABLE_RM	0x00800000	/* purging bss table entries */
#घोषणा DBG_MONITOR_MODE	0x01000000	/* monitor mode */
#घोषणा DBG_MIB			0x02000000	/* dump all MIBs on startup */
#घोषणा DBG_MGMT_TIMER		0x04000000	/* dump mgmt_समयr ops */
#घोषणा DBG_WE_EVENTS		0x08000000	/* dump wireless events */
#घोषणा DBG_FW			0x10000000	/* firmware करोwnload */
#घोषणा DBG_DFU			0x20000000	/* device firmware upgrade */
#घोषणा DBG_CMD			0x40000000
#घोषणा DBG_MAC80211		0x80000000

#घोषणा DBG_DEFAULTS		0

/* Use our own dbg macro */
#घोषणा at76_dbg(bits, क्रमmat, arg...)					\
करो अणु									\
	अगर (at76_debug & (bits))					\
		prपूर्णांकk(KERN_DEBUG DRIVER_NAME ": " क्रमmat "\n", ##arg);	\
पूर्ण जबतक (0)

#घोषणा at76_dbg_dump(bits, buf, len, क्रमmat, arg...)			\
करो अणु									\
	अगर (at76_debug & (bits)) अणु					\
		prपूर्णांकk(KERN_DEBUG DRIVER_NAME ": " क्रमmat "\n", ##arg);	\
		prपूर्णांक_hex_dump_bytes("", DUMP_PREFIX_OFFSET, buf, len);	\
	पूर्ण								\
पूर्ण जबतक (0)

अटल uपूर्णांक at76_debug = DBG_DEFAULTS;

/* Protect against concurrent firmware loading and parsing */
अटल DEFINE_MUTEX(fw_mutex);

अटल काष्ठा fwentry firmwares[] = अणु
	[0] = अणु "" पूर्ण,
	[BOARD_503_ISL3861] = अणु "atmel_at76c503-i3861.bin" पूर्ण,
	[BOARD_503_ISL3863] = अणु "atmel_at76c503-i3863.bin" पूर्ण,
	[BOARD_503] = अणु "atmel_at76c503-rfmd.bin" पूर्ण,
	[BOARD_503_ACC] = अणु "atmel_at76c503-rfmd-acc.bin" पूर्ण,
	[BOARD_505] = अणु "atmel_at76c505-rfmd.bin" पूर्ण,
	[BOARD_505_2958] = अणु "atmel_at76c505-rfmd2958.bin" पूर्ण,
	[BOARD_505A] = अणु "atmel_at76c505a-rfmd2958.bin" पूर्ण,
	[BOARD_505AMX] = अणु "atmel_at76c505amx-rfmd.bin" पूर्ण,
पूर्ण;
MODULE_FIRMWARE("atmel_at76c503-i3861.bin");
MODULE_FIRMWARE("atmel_at76c503-i3863.bin");
MODULE_FIRMWARE("atmel_at76c503-rfmd.bin");
MODULE_FIRMWARE("atmel_at76c503-rfmd-acc.bin");
MODULE_FIRMWARE("atmel_at76c505-rfmd.bin");
MODULE_FIRMWARE("atmel_at76c505-rfmd2958.bin");
MODULE_FIRMWARE("atmel_at76c505a-rfmd2958.bin");
MODULE_FIRMWARE("atmel_at76c505amx-rfmd.bin");

#घोषणा USB_DEVICE_DATA(__ops)	.driver_info = (kernel_uदीर्घ_t)(__ops)

अटल स्थिर काष्ठा usb_device_id dev_table[] = अणु
	/*
	 * at76c503-i3861
	 */
	/* Generic AT76C503/3861 device */
	अणु USB_DEVICE(0x03eb, 0x7603), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* Linksys WUSB11 v2.1/v2.6 */
	अणु USB_DEVICE(0x066b, 0x2211), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* Netgear MA101 rev. A */
	अणु USB_DEVICE(0x0864, 0x4100), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* Tekram U300C / Allnet ALL0193 */
	अणु USB_DEVICE(0x0b3b, 0x1612), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* HP HN210W J7801A */
	अणु USB_DEVICE(0x03f0, 0x011c), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* Sitecom/Z-Com/Zyxel M4Y-750 */
	अणु USB_DEVICE(0x0cde, 0x0001), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* Dynalink/Askey WLL013 (पूर्णांकersil) */
	अणु USB_DEVICE(0x069a, 0x0320), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* EZ connect 11Mpbs Wireless USB Adapter SMC2662W v1 */
	अणु USB_DEVICE(0x0d5c, 0xa001), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* BenQ AWL300 */
	अणु USB_DEVICE(0x04a5, 0x9000), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* Addtron AWU-120, Compex WLU11 */
	अणु USB_DEVICE(0x05dd, 0xff31), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* Intel AP310 AnyPoपूर्णांक II USB */
	अणु USB_DEVICE(0x8086, 0x0200), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* Dynalink L11U */
	अणु USB_DEVICE(0x0d8e, 0x7100), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* Arescom WL-210, FCC id 07J-GL2411USB */
	अणु USB_DEVICE(0x0d8e, 0x7110), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* I-O DATA WN-B11/USB */
	अणु USB_DEVICE(0x04bb, 0x0919), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/* BT Voyager 1010 */
	अणु USB_DEVICE(0x069a, 0x0821), USB_DEVICE_DATA(BOARD_503_ISL3861) पूर्ण,
	/*
	 * at76c503-i3863
	 */
	/* Generic AT76C503/3863 device */
	अणु USB_DEVICE(0x03eb, 0x7604), USB_DEVICE_DATA(BOARD_503_ISL3863) पूर्ण,
	/* Samsung SWL-2100U */
	अणु USB_DEVICE(0x055d, 0xa000), USB_DEVICE_DATA(BOARD_503_ISL3863) पूर्ण,
	/*
	 * at76c503-rfmd
	 */
	/* Generic AT76C503/RFMD device */
	अणु USB_DEVICE(0x03eb, 0x7605), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Dynalink/Askey WLL013 (rfmd) */
	अणु USB_DEVICE(0x069a, 0x0321), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Linksys WUSB11 v2.6 */
	अणु USB_DEVICE(0x077b, 0x2219), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Network Everywhere NWU11B */
	अणु USB_DEVICE(0x077b, 0x2227), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Netgear MA101 rev. B */
	अणु USB_DEVICE(0x0864, 0x4102), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* D-Link DWL-120 rev. E */
	अणु USB_DEVICE(0x2001, 0x3200), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Actiontec 802UAT1, HWU01150-01UK */
	अणु USB_DEVICE(0x1668, 0x7605), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* AirVast W-Buddie WN210 */
	अणु USB_DEVICE(0x03eb, 0x4102), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Dick Smith Electronics XH1153 802.11b USB adapter */
	अणु USB_DEVICE(0x1371, 0x5743), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* CNet CNUSB611 */
	अणु USB_DEVICE(0x1371, 0x0001), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* FiberLine FL-WL200U */
	अणु USB_DEVICE(0x1371, 0x0002), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* BenQ AWL400 USB stick */
	अणु USB_DEVICE(0x04a5, 0x9001), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* 3Com 3CRSHEW696 */
	अणु USB_DEVICE(0x0506, 0x0a01), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Siemens Santis ADSL WLAN USB adapter WLL 013 */
	अणु USB_DEVICE(0x0681, 0x001b), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Belkin F5D6050, version 2 */
	अणु USB_DEVICE(0x050d, 0x0050), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* iBlitzz, BWU613 (not *B or *SB) */
	अणु USB_DEVICE(0x07b8, 0xb000), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Gigabyte GN-WLBM101 */
	अणु USB_DEVICE(0x1044, 0x8003), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Planex GW-US11S */
	अणु USB_DEVICE(0x2019, 0x3220), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Internal WLAN adapter in h5[4,5]xx series iPAQs */
	अणु USB_DEVICE(0x049f, 0x0032), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Corega Wireless LAN USB-11 mini */
	अणु USB_DEVICE(0x07aa, 0x0011), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Corega Wireless LAN USB-11 mini2 */
	अणु USB_DEVICE(0x07aa, 0x0018), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/* Uniden PCW100 */
	अणु USB_DEVICE(0x05dd, 0xff35), USB_DEVICE_DATA(BOARD_503) पूर्ण,
	/*
	 * at76c503-rfmd-acc
	 */
	/* SMC2664W */
	अणु USB_DEVICE(0x083a, 0x3501), USB_DEVICE_DATA(BOARD_503_ACC) पूर्ण,
	/* Belkin F5D6050, SMC2662W v2, SMC2662W-AR */
	अणु USB_DEVICE(0x0d5c, 0xa002), USB_DEVICE_DATA(BOARD_503_ACC) पूर्ण,
	/*
	 * at76c505-rfmd
	 */
	/* Generic AT76C505/RFMD */
	अणु USB_DEVICE(0x03eb, 0x7606), USB_DEVICE_DATA(BOARD_505) पूर्ण,
	/*
	 * at76c505-rfmd2958
	 */
	/* Generic AT76C505/RFMD, OvisLink WL-1130USB */
	अणु USB_DEVICE(0x03eb, 0x7613), USB_DEVICE_DATA(BOARD_505_2958) पूर्ण,
	/* Fiberline FL-WL240U */
	अणु USB_DEVICE(0x1371, 0x0014), USB_DEVICE_DATA(BOARD_505_2958) पूर्ण,
	/* CNet CNUSB-611G */
	अणु USB_DEVICE(0x1371, 0x0013), USB_DEVICE_DATA(BOARD_505_2958) पूर्ण,
	/* Linksys WUSB11 v2.8 */
	अणु USB_DEVICE(0x1915, 0x2233), USB_DEVICE_DATA(BOARD_505_2958) पूर्ण,
	/* Xterasys XN-2122B, IBlitzz BWU613B/BWU613SB */
	अणु USB_DEVICE(0x12fd, 0x1001), USB_DEVICE_DATA(BOARD_505_2958) पूर्ण,
	/* Corega WLAN USB Stick 11 */
	अणु USB_DEVICE(0x07aa, 0x7613), USB_DEVICE_DATA(BOARD_505_2958) पूर्ण,
	/* Microstar MSI Box MS6978 */
	अणु USB_DEVICE(0x0db0, 0x1020), USB_DEVICE_DATA(BOARD_505_2958) पूर्ण,
	/*
	 * at76c505a-rfmd2958
	 */
	/* Generic AT76C505A device */
	अणु USB_DEVICE(0x03eb, 0x7614), USB_DEVICE_DATA(BOARD_505A) पूर्ण,
	/* Generic AT76C505AS device */
	अणु USB_DEVICE(0x03eb, 0x7617), USB_DEVICE_DATA(BOARD_505A) पूर्ण,
	/* Siemens Gigaset USB WLAN Adapter 11 */
	अणु USB_DEVICE(0x1690, 0x0701), USB_DEVICE_DATA(BOARD_505A) पूर्ण,
	/* OQO Model 01+ Internal Wi-Fi */
	अणु USB_DEVICE(0x1557, 0x0002), USB_DEVICE_DATA(BOARD_505A) पूर्ण,
	/*
	 * at76c505amx-rfmd
	 */
	/* Generic AT76C505AMX device */
	अणु USB_DEVICE(0x03eb, 0x7615), USB_DEVICE_DATA(BOARD_505AMX) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, dev_table);

/* Supported rates of this hardware, bit 7 marks basic rates */
अटल स्थिर u8 hw_rates[] = अणु 0x82, 0x84, 0x0b, 0x16 पूर्ण;

अटल स्थिर अक्षर *स्थिर preambles[] = अणु "long", "short", "auto" पूर्ण;

/* Firmware करोwnload */
/* DFU states */
#घोषणा STATE_IDLE			0x00
#घोषणा STATE_DETACH			0x01
#घोषणा STATE_DFU_IDLE			0x02
#घोषणा STATE_DFU_DOWNLOAD_SYNC		0x03
#घोषणा STATE_DFU_DOWNLOAD_BUSY		0x04
#घोषणा STATE_DFU_DOWNLOAD_IDLE		0x05
#घोषणा STATE_DFU_MANIFEST_SYNC		0x06
#घोषणा STATE_DFU_MANIFEST		0x07
#घोषणा STATE_DFU_MANIFEST_WAIT_RESET	0x08
#घोषणा STATE_DFU_UPLOAD_IDLE		0x09
#घोषणा STATE_DFU_ERROR			0x0a

/* DFU commands */
#घोषणा DFU_DETACH			0
#घोषणा DFU_DNLOAD			1
#घोषणा DFU_UPLOAD			2
#घोषणा DFU_GETSTATUS			3
#घोषणा DFU_CLRSTATUS			4
#घोषणा DFU_GETSTATE			5
#घोषणा DFU_ABORT			6

#घोषणा FW_BLOCK_SIZE 1024

काष्ठा dfu_status अणु
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर poll_समयout[3];
	अचिन्हित अक्षर state;
	अचिन्हित अक्षर string;
पूर्ण __packed;

अटल अंतरभूत पूर्णांक at76_is_पूर्णांकersil(क्रमागत board_type board)
अणु
	वापस (board == BOARD_503_ISL3861 || board == BOARD_503_ISL3863);
पूर्ण

अटल अंतरभूत पूर्णांक at76_is_503rfmd(क्रमागत board_type board)
अणु
	वापस (board == BOARD_503 || board == BOARD_503_ACC);
पूर्ण

अटल अंतरभूत पूर्णांक at76_is_505a(क्रमागत board_type board)
अणु
	वापस (board == BOARD_505A || board == BOARD_505AMX);
पूर्ण

/* Load a block of the first (पूर्णांकernal) part of the firmware */
अटल पूर्णांक at76_load_पूर्णांक_fw_block(काष्ठा usb_device *udev, पूर्णांक blockno,
				  व्योम *block, पूर्णांक size)
अणु
	वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0), DFU_DNLOAD,
			       USB_TYPE_CLASS | USB_सूची_OUT |
			       USB_RECIP_INTERFACE, blockno, 0, block, size,
			       USB_CTRL_GET_TIMEOUT);
पूर्ण

अटल पूर्णांक at76_dfu_get_status(काष्ठा usb_device *udev,
			       काष्ठा dfu_status *status)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), DFU_GETSTATUS,
			      USB_TYPE_CLASS | USB_सूची_IN | USB_RECIP_INTERFACE,
			      0, 0, status, माप(काष्ठा dfu_status),
			      USB_CTRL_GET_TIMEOUT);
	वापस ret;
पूर्ण

अटल पूर्णांक at76_dfu_get_state(काष्ठा usb_device *udev, u8 *state)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), DFU_GETSTATE,
			      USB_TYPE_CLASS | USB_सूची_IN | USB_RECIP_INTERFACE,
			      0, 0, state, 1, USB_CTRL_GET_TIMEOUT);
	वापस ret;
पूर्ण

/* Convert समयout from the DFU status to jअगरfies */
अटल अंतरभूत अचिन्हित दीर्घ at76_get_समयout(काष्ठा dfu_status *s)
अणु
	वापस msecs_to_jअगरfies((s->poll_समयout[2] << 16)
				| (s->poll_समयout[1] << 8)
				| (s->poll_समयout[0]));
पूर्ण

/* Load पूर्णांकernal firmware from the buffer.  If manअगरest_sync_समयout > 0, use
 * its value in jअगरfies in the MANIFEST_SYNC state.  */
अटल पूर्णांक at76_usbdfu_करोwnload(काष्ठा usb_device *udev, u8 *buf, u32 size,
				पूर्णांक manअगरest_sync_समयout)
अणु
	पूर्णांक ret = 0;
	पूर्णांक need_dfu_state = 1;
	पूर्णांक is_करोne = 0;
	u32 dfu_समयout = 0;
	पूर्णांक bsize = 0;
	पूर्णांक blockno = 0;
	काष्ठा dfu_status *dfu_stat_buf = शून्य;
	u8 *dfu_state = शून्य;
	u8 *block = शून्य;

	at76_dbg(DBG_DFU, "%s( %p, %u, %d)", __func__, buf, size,
		 manअगरest_sync_समयout);

	अगर (!size) अणु
		dev_err(&udev->dev, "FW buffer length invalid!\n");
		वापस -EINVAL;
	पूर्ण

	dfu_stat_buf = kदो_स्मृति(माप(काष्ठा dfu_status), GFP_KERNEL);
	अगर (!dfu_stat_buf) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	block = kदो_स्मृति(FW_BLOCK_SIZE, GFP_KERNEL);
	अगर (!block) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	dfu_state = kदो_स्मृति(माप(u8), GFP_KERNEL);
	अगर (!dfu_state) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण
	*dfu_state = 0;

	करो अणु
		अगर (need_dfu_state) अणु
			ret = at76_dfu_get_state(udev, dfu_state);
			अगर (ret < 0) अणु
				dev_err(&udev->dev,
					"cannot get DFU state: %d\n", ret);
				जाओ निकास;
			पूर्ण
			need_dfu_state = 0;
		पूर्ण

		चयन (*dfu_state) अणु
		हाल STATE_DFU_DOWNLOAD_SYNC:
			at76_dbg(DBG_DFU, "STATE_DFU_DOWNLOAD_SYNC");
			ret = at76_dfu_get_status(udev, dfu_stat_buf);
			अगर (ret >= 0) अणु
				*dfu_state = dfu_stat_buf->state;
				dfu_समयout = at76_get_समयout(dfu_stat_buf);
				need_dfu_state = 0;
			पूर्ण अन्यथा
				dev_err(&udev->dev,
					"at76_dfu_get_status returned %d\n",
					ret);
			अवरोध;

		हाल STATE_DFU_DOWNLOAD_BUSY:
			at76_dbg(DBG_DFU, "STATE_DFU_DOWNLOAD_BUSY");
			need_dfu_state = 1;

			at76_dbg(DBG_DFU, "DFU: Resetting device");
			schedule_समयout_पूर्णांकerruptible(dfu_समयout);
			अवरोध;

		हाल STATE_DFU_DOWNLOAD_IDLE:
			at76_dbg(DBG_DFU, "DOWNLOAD...");
			fallthrough;
		हाल STATE_DFU_IDLE:
			at76_dbg(DBG_DFU, "DFU IDLE");

			bsize = min_t(पूर्णांक, size, FW_BLOCK_SIZE);
			स_नकल(block, buf, bsize);
			at76_dbg(DBG_DFU, "int fw, size left = %5d, "
				 "bsize = %4d, blockno = %2d", size, bsize,
				 blockno);
			ret =
			    at76_load_पूर्णांक_fw_block(udev, blockno, block, bsize);
			buf += bsize;
			size -= bsize;
			blockno++;

			अगर (ret != bsize)
				dev_err(&udev->dev,
					"at76_load_int_fw_block returned %d\n",
					ret);
			need_dfu_state = 1;
			अवरोध;

		हाल STATE_DFU_MANIFEST_SYNC:
			at76_dbg(DBG_DFU, "STATE_DFU_MANIFEST_SYNC");

			ret = at76_dfu_get_status(udev, dfu_stat_buf);
			अगर (ret < 0)
				अवरोध;

			*dfu_state = dfu_stat_buf->state;
			dfu_समयout = at76_get_समयout(dfu_stat_buf);
			need_dfu_state = 0;

			/* override the समयout from the status response,
			   needed क्रम AT76C505A */
			अगर (manअगरest_sync_समयout > 0)
				dfu_समयout = manअगरest_sync_समयout;

			at76_dbg(DBG_DFU, "DFU: Waiting for manifest phase");
			schedule_समयout_पूर्णांकerruptible(dfu_समयout);
			अवरोध;

		हाल STATE_DFU_MANIFEST:
			at76_dbg(DBG_DFU, "STATE_DFU_MANIFEST");
			is_करोne = 1;
			अवरोध;

		हाल STATE_DFU_MANIFEST_WAIT_RESET:
			at76_dbg(DBG_DFU, "STATE_DFU_MANIFEST_WAIT_RESET");
			is_करोne = 1;
			अवरोध;

		हाल STATE_DFU_UPLOAD_IDLE:
			at76_dbg(DBG_DFU, "STATE_DFU_UPLOAD_IDLE");
			अवरोध;

		हाल STATE_DFU_ERROR:
			at76_dbg(DBG_DFU, "STATE_DFU_ERROR");
			ret = -EPIPE;
			अवरोध;

		शेष:
			at76_dbg(DBG_DFU, "DFU UNKNOWN STATE (%d)", *dfu_state);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!is_करोne && (ret >= 0));

निकास:
	kमुक्त(dfu_state);
	kमुक्त(block);
	kमुक्त(dfu_stat_buf);

	अगर (ret >= 0)
		ret = 0;

	वापस ret;
पूर्ण

/* LED trigger */
अटल पूर्णांक tx_activity;
अटल व्योम at76_ledtrig_tx_समयrfunc(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(ledtrig_tx_समयr, at76_ledtrig_tx_समयrfunc);
DEFINE_LED_TRIGGER(ledtrig_tx);

अटल व्योम at76_ledtrig_tx_समयrfunc(काष्ठा समयr_list *unused)
अणु
	अटल पूर्णांक tx_lastactivity;

	अगर (tx_lastactivity != tx_activity) अणु
		tx_lastactivity = tx_activity;
		led_trigger_event(ledtrig_tx, LED_FULL);
		mod_समयr(&ledtrig_tx_समयr, jअगरfies + HZ / 4);
	पूर्ण अन्यथा
		led_trigger_event(ledtrig_tx, LED_OFF);
पूर्ण

अटल व्योम at76_ledtrig_tx_activity(व्योम)
अणु
	tx_activity++;
	अगर (!समयr_pending(&ledtrig_tx_समयr))
		mod_समयr(&ledtrig_tx_समयr, jअगरfies + HZ / 4);
पूर्ण

अटल पूर्णांक at76_remap(काष्ठा usb_device *udev)
अणु
	पूर्णांक ret;
	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x0a,
			      USB_TYPE_VENDOR | USB_सूची_OUT |
			      USB_RECIP_INTERFACE, 0, 0, शून्य, 0,
			      USB_CTRL_GET_TIMEOUT);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक at76_get_op_mode(काष्ठा usb_device *udev)
अणु
	पूर्णांक ret;
	u8 saved;
	u8 *op_mode;

	op_mode = kदो_स्मृति(1, GFP_NOIO);
	अगर (!op_mode)
		वापस -ENOMEM;
	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0x33,
			      USB_TYPE_VENDOR | USB_सूची_IN |
			      USB_RECIP_INTERFACE, 0x01, 0, op_mode, 1,
			      USB_CTRL_GET_TIMEOUT);
	saved = *op_mode;
	kमुक्त(op_mode);

	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret < 1)
		वापस -EIO;
	अन्यथा
		वापस saved;
पूर्ण

/* Load a block of the second ("external") part of the firmware */
अटल अंतरभूत पूर्णांक at76_load_ext_fw_block(काष्ठा usb_device *udev, पूर्णांक blockno,
					 व्योम *block, पूर्णांक size)
अणु
	वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x0e,
			       USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE,
			       0x0802, blockno, block, size,
			       USB_CTRL_GET_TIMEOUT);
पूर्ण

अटल अंतरभूत पूर्णांक at76_get_hw_cfg(काष्ठा usb_device *udev,
				  जोड़ at76_hwcfg *buf, पूर्णांक buf_size)
अणु
	वापस usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0x33,
			       USB_TYPE_VENDOR | USB_सूची_IN |
			       USB_RECIP_INTERFACE, 0x0a02, 0,
			       buf, buf_size, USB_CTRL_GET_TIMEOUT);
पूर्ण

/* Intersil boards use a dअगरferent "value" क्रम GetHWConfig requests */
अटल अंतरभूत पूर्णांक at76_get_hw_cfg_पूर्णांकersil(काष्ठा usb_device *udev,
					   जोड़ at76_hwcfg *buf, पूर्णांक buf_size)
अणु
	वापस usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0x33,
			       USB_TYPE_VENDOR | USB_सूची_IN |
			       USB_RECIP_INTERFACE, 0x0902, 0,
			       buf, buf_size, USB_CTRL_GET_TIMEOUT);
पूर्ण

/* Get the hardware configuration क्रम the adapter and put it to the appropriate
 * fields of 'priv' (the GetHWConfig request and पूर्णांकerpretation of the result
 * depends on the board type) */
अटल पूर्णांक at76_get_hw_config(काष्ठा at76_priv *priv)
अणु
	पूर्णांक ret;
	जोड़ at76_hwcfg *hwcfg = kदो_स्मृति(माप(*hwcfg), GFP_KERNEL);

	अगर (!hwcfg)
		वापस -ENOMEM;

	अगर (at76_is_पूर्णांकersil(priv->board_type)) अणु
		ret = at76_get_hw_cfg_पूर्णांकersil(priv->udev, hwcfg,
					       माप(hwcfg->i));
		अगर (ret < 0)
			जाओ निकास;
		स_नकल(priv->mac_addr, hwcfg->i.mac_addr, ETH_ALEN);
		priv->regulatory_करोमुख्य = hwcfg->i.regulatory_करोमुख्य;
	पूर्ण अन्यथा अगर (at76_is_503rfmd(priv->board_type)) अणु
		ret = at76_get_hw_cfg(priv->udev, hwcfg, माप(hwcfg->r3));
		अगर (ret < 0)
			जाओ निकास;
		स_नकल(priv->mac_addr, hwcfg->r3.mac_addr, ETH_ALEN);
		priv->regulatory_करोमुख्य = hwcfg->r3.regulatory_करोमुख्य;
	पूर्ण अन्यथा अणु
		ret = at76_get_hw_cfg(priv->udev, hwcfg, माप(hwcfg->r5));
		अगर (ret < 0)
			जाओ निकास;
		स_नकल(priv->mac_addr, hwcfg->r5.mac_addr, ETH_ALEN);
		priv->regulatory_करोमुख्य = hwcfg->r5.regulatory_करोमुख्य;
	पूर्ण

निकास:
	kमुक्त(hwcfg);
	अगर (ret < 0)
		wiphy_err(priv->hw->wiphy, "cannot get HW Config (error %d)\n",
			  ret);

	वापस ret;
पूर्ण

अटल काष्ठा reg_करोमुख्य स्थिर *at76_get_reg_करोमुख्य(u16 code)
अणु
	पूर्णांक i;
	अटल काष्ठा reg_करोमुख्य स्थिर fd_tab[] = अणु
		अणु 0x10, "FCC (USA)", 0x7ff पूर्ण,	/* ch 1-11 */
		अणु 0x20, "IC (Canada)", 0x7ff पूर्ण,	/* ch 1-11 */
		अणु 0x30, "ETSI (most of Europe)", 0x1fff पूर्ण,	/* ch 1-13 */
		अणु 0x31, "Spain", 0x600 पूर्ण,	/* ch 10-11 */
		अणु 0x32, "France", 0x1e00 पूर्ण,	/* ch 10-13 */
		अणु 0x40, "MKK (Japan)", 0x2000 पूर्ण,	/* ch 14 */
		अणु 0x41, "MKK1 (Japan)", 0x3fff पूर्ण,	/* ch 1-14 */
		अणु 0x50, "Israel", 0x3fc पूर्ण,	/* ch 3-9 */
		अणु 0x00, "<unknown>", 0xffffffff पूर्ण	/* ch 1-32 */
	पूर्ण;

	/* Last entry is fallback क्रम unknown करोमुख्य code */
	क्रम (i = 0; i < ARRAY_SIZE(fd_tab) - 1; i++)
		अगर (code == fd_tab[i].code)
			अवरोध;

	वापस &fd_tab[i];
पूर्ण

अटल अंतरभूत पूर्णांक at76_get_mib(काष्ठा usb_device *udev, u16 mib, व्योम *buf,
			       पूर्णांक buf_size)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0x33,
			      USB_TYPE_VENDOR | USB_सूची_IN |
			      USB_RECIP_INTERFACE, mib << 8, 0, buf, buf_size,
			      USB_CTRL_GET_TIMEOUT);
	अगर (ret >= 0 && ret != buf_size)
		वापस -EIO;
	वापस ret;
पूर्ण

/* Return positive number क्रम status, negative क्रम an error */
अटल अंतरभूत पूर्णांक at76_get_cmd_status(काष्ठा usb_device *udev, u8 cmd)
अणु
	u8 *stat_buf;
	पूर्णांक ret;

	stat_buf = kदो_स्मृति(40, GFP_NOIO);
	अगर (!stat_buf)
		वापस -ENOMEM;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0x22,
			USB_TYPE_VENDOR | USB_सूची_IN |
			USB_RECIP_INTERFACE, cmd, 0, stat_buf,
			40, USB_CTRL_GET_TIMEOUT);
	अगर (ret >= 0)
		ret = stat_buf[5];
	kमुक्त(stat_buf);

	वापस ret;
पूर्ण

#घोषणा MAKE_CMD_CASE(c) हाल (c): वापस #c
अटल स्थिर अक्षर *at76_get_cmd_string(u8 cmd_status)
अणु
	चयन (cmd_status) अणु
		MAKE_CMD_CASE(CMD_SET_MIB);
		MAKE_CMD_CASE(CMD_GET_MIB);
		MAKE_CMD_CASE(CMD_SCAN);
		MAKE_CMD_CASE(CMD_JOIN);
		MAKE_CMD_CASE(CMD_START_IBSS);
		MAKE_CMD_CASE(CMD_RADIO_ON);
		MAKE_CMD_CASE(CMD_RADIO_OFF);
		MAKE_CMD_CASE(CMD_STARTUP);
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

अटल पूर्णांक at76_set_card_command(काष्ठा usb_device *udev, u8 cmd, व्योम *buf,
				 पूर्णांक buf_size)
अणु
	पूर्णांक ret;
	काष्ठा at76_command *cmd_buf = kदो_स्मृति(माप(काष्ठा at76_command) +
					       buf_size, GFP_KERNEL);

	अगर (!cmd_buf)
		वापस -ENOMEM;

	cmd_buf->cmd = cmd;
	cmd_buf->reserved = 0;
	cmd_buf->size = cpu_to_le16(buf_size);
	स_नकल(cmd_buf->data, buf, buf_size);

	at76_dbg_dump(DBG_CMD, cmd_buf, माप(काष्ठा at76_command) + buf_size,
		      "issuing command %s (0x%02x)",
		      at76_get_cmd_string(cmd), cmd);

	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x0e,
			      USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE,
			      0, 0, cmd_buf,
			      माप(काष्ठा at76_command) + buf_size,
			      USB_CTRL_GET_TIMEOUT);
	kमुक्त(cmd_buf);
	वापस ret;
पूर्ण

#घोषणा MAKE_CMD_STATUS_CASE(c)	हाल (c): वापस #c
अटल स्थिर अक्षर *at76_get_cmd_status_string(u8 cmd_status)
अणु
	चयन (cmd_status) अणु
		MAKE_CMD_STATUS_CASE(CMD_STATUS_IDLE);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_COMPLETE);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_UNKNOWN);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_INVALID_PARAMETER);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_FUNCTION_NOT_SUPPORTED);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_TIME_OUT);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_IN_PROGRESS);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_HOST_FAILURE);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_SCAN_FAILED);
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

/* Wait until the command is completed */
अटल पूर्णांक at76_रुको_completion(काष्ठा at76_priv *priv, पूर्णांक cmd)
अणु
	पूर्णांक status = 0;
	अचिन्हित दीर्घ समयout = jअगरfies + CMD_COMPLETION_TIMEOUT;

	करो अणु
		status = at76_get_cmd_status(priv->udev, cmd);
		अगर (status < 0) अणु
			wiphy_err(priv->hw->wiphy,
				  "at76_get_cmd_status failed: %d\n",
				  status);
			अवरोध;
		पूर्ण

		at76_dbg(DBG_WAIT_COMPLETE,
			 "%s: Waiting on cmd %d, status = %d (%s)",
			 wiphy_name(priv->hw->wiphy), cmd, status,
			 at76_get_cmd_status_string(status));

		अगर (status != CMD_STATUS_IN_PROGRESS
		    && status != CMD_STATUS_IDLE)
			अवरोध;

		schedule_समयout_पूर्णांकerruptible(HZ / 10);	/* 100 ms */
		अगर (समय_after(jअगरfies, समयout)) अणु
			wiphy_err(priv->hw->wiphy,
				  "completion timeout for command %d\n", cmd);
			status = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	वापस status;
पूर्ण

अटल पूर्णांक at76_set_mib(काष्ठा at76_priv *priv, काष्ठा set_mib_buffer *buf)
अणु
	पूर्णांक ret;

	ret = at76_set_card_command(priv->udev, CMD_SET_MIB, buf,
				    दुरत्व(काष्ठा set_mib_buffer,
					     data) + buf->size);
	अगर (ret < 0)
		वापस ret;

	ret = at76_रुको_completion(priv, CMD_SET_MIB);
	अगर (ret != CMD_STATUS_COMPLETE) अणु
		wiphy_info(priv->hw->wiphy,
			   "set_mib: at76_wait_completion failed with %d\n",
			   ret);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

/* Return < 0 on error, == 0 अगर no command sent, == 1 अगर cmd sent */
अटल पूर्णांक at76_set_radio(काष्ठा at76_priv *priv, पूर्णांक enable)
अणु
	पूर्णांक ret;
	पूर्णांक cmd;

	अगर (priv->radio_on == enable)
		वापस 0;

	cmd = enable ? CMD_RADIO_ON : CMD_RADIO_OFF;

	ret = at76_set_card_command(priv->udev, cmd, शून्य, 0);
	अगर (ret < 0)
		wiphy_err(priv->hw->wiphy,
			  "at76_set_card_command(%d) failed: %d\n", cmd, ret);
	अन्यथा
		ret = 1;

	priv->radio_on = enable;
	वापस ret;
पूर्ण

/* Set current घातer save mode (AT76_PM_OFF/AT76_PM_ON/AT76_PM_SMART) */
अटल पूर्णांक at76_set_pm_mode(काष्ठा at76_priv *priv)
अणु
	पूर्णांक ret = 0;

	priv->mib_buf.type = MIB_MAC_MGMT;
	priv->mib_buf.size = 1;
	priv->mib_buf.index = दुरत्व(काष्ठा mib_mac_mgmt, घातer_mgmt_mode);
	priv->mib_buf.data.byte = priv->pm_mode;

	ret = at76_set_mib(priv, &priv->mib_buf);
	अगर (ret < 0)
		wiphy_err(priv->hw->wiphy, "set_mib (pm_mode) failed: %d\n",
			  ret);

	वापस ret;
पूर्ण

अटल पूर्णांक at76_set_preamble(काष्ठा at76_priv *priv, u8 type)
अणु
	पूर्णांक ret = 0;

	priv->mib_buf.type = MIB_LOCAL;
	priv->mib_buf.size = 1;
	priv->mib_buf.index = दुरत्व(काष्ठा mib_local, preamble_type);
	priv->mib_buf.data.byte = type;

	ret = at76_set_mib(priv, &priv->mib_buf);
	अगर (ret < 0)
		wiphy_err(priv->hw->wiphy, "set_mib (preamble) failed: %d\n",
			  ret);

	वापस ret;
पूर्ण

अटल पूर्णांक at76_set_frag(काष्ठा at76_priv *priv, u16 size)
अणु
	पूर्णांक ret = 0;

	priv->mib_buf.type = MIB_MAC;
	priv->mib_buf.size = 2;
	priv->mib_buf.index = दुरत्व(काष्ठा mib_mac, frag_threshold);
	priv->mib_buf.data.word = cpu_to_le16(size);

	ret = at76_set_mib(priv, &priv->mib_buf);
	अगर (ret < 0)
		wiphy_err(priv->hw->wiphy,
			  "set_mib (frag threshold) failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक at76_set_rts(काष्ठा at76_priv *priv, u16 size)
अणु
	पूर्णांक ret = 0;

	priv->mib_buf.type = MIB_MAC;
	priv->mib_buf.size = 2;
	priv->mib_buf.index = दुरत्व(काष्ठा mib_mac, rts_threshold);
	priv->mib_buf.data.word = cpu_to_le16(size);

	ret = at76_set_mib(priv, &priv->mib_buf);
	अगर (ret < 0)
		wiphy_err(priv->hw->wiphy, "set_mib (rts) failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक at76_set_स्वतःrate_fallback(काष्ठा at76_priv *priv, पूर्णांक onoff)
अणु
	पूर्णांक ret = 0;

	priv->mib_buf.type = MIB_LOCAL;
	priv->mib_buf.size = 1;
	priv->mib_buf.index = दुरत्व(काष्ठा mib_local, txस्वतःrate_fallback);
	priv->mib_buf.data.byte = onoff;

	ret = at76_set_mib(priv, &priv->mib_buf);
	अगर (ret < 0)
		wiphy_err(priv->hw->wiphy,
			  "set_mib (autorate fallback) failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम at76_dump_mib_mac_addr(काष्ठा at76_priv *priv)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा mib_mac_addr *m = kदो_स्मृति(माप(काष्ठा mib_mac_addr),
					 GFP_KERNEL);

	अगर (!m)
		वापस;

	ret = at76_get_mib(priv->udev, MIB_MAC_ADDR, m,
			   माप(काष्ठा mib_mac_addr));
	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MAC_ADDR) failed: %d\n", ret);
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_MIB, "%s: MIB MAC_ADDR: mac_addr %pM res 0x%x 0x%x",
		 wiphy_name(priv->hw->wiphy),
		 m->mac_addr, m->res[0], m->res[1]);
	क्रम (i = 0; i < ARRAY_SIZE(m->group_addr); i++)
		at76_dbg(DBG_MIB, "%s: MIB MAC_ADDR: group addr %d: %pM, "
			 "status %d", wiphy_name(priv->hw->wiphy), i,
			 m->group_addr[i], m->group_addr_status[i]);
निकास:
	kमुक्त(m);
पूर्ण

अटल व्योम at76_dump_mib_mac_wep(काष्ठा at76_priv *priv)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक key_len;
	काष्ठा mib_mac_wep *m = kदो_स्मृति(माप(काष्ठा mib_mac_wep), GFP_KERNEL);

	अगर (!m)
		वापस;

	ret = at76_get_mib(priv->udev, MIB_MAC_WEP, m,
			   माप(काष्ठा mib_mac_wep));
	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MAC_WEP) failed: %d\n", ret);
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_MIB, "%s: MIB MAC_WEP: priv_invoked %u def_key_id %u "
		 "key_len %u excl_unencr %u wep_icv_err %u wep_excluded %u "
		 "encr_level %u key %d", wiphy_name(priv->hw->wiphy),
		 m->privacy_invoked, m->wep_शेष_key_id,
		 m->wep_key_mapping_len, m->exclude_unencrypted,
		 le32_to_cpu(m->wep_icv_error_count),
		 le32_to_cpu(m->wep_excluded_count), m->encryption_level,
		 m->wep_शेष_key_id);

	key_len = (m->encryption_level == 1) ?
	    WEP_SMALL_KEY_LEN : WEP_LARGE_KEY_LEN;

	क्रम (i = 0; i < WEP_KEYS; i++)
		at76_dbg(DBG_MIB, "%s: MIB MAC_WEP: key %d: %*phD",
			 wiphy_name(priv->hw->wiphy), i,
			 key_len, m->wep_शेष_keyvalue[i]);
निकास:
	kमुक्त(m);
पूर्ण

अटल व्योम at76_dump_mib_mac_mgmt(काष्ठा at76_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा mib_mac_mgmt *m = kदो_स्मृति(माप(काष्ठा mib_mac_mgmt),
					 GFP_KERNEL);

	अगर (!m)
		वापस;

	ret = at76_get_mib(priv->udev, MIB_MAC_MGMT, m,
			   माप(काष्ठा mib_mac_mgmt));
	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MAC_MGMT) failed: %d\n", ret);
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_MIB, "%s: MIB MAC_MGMT: beacon_period %d CFP_max_duration "
		 "%d medium_occupancy_limit %d station_id 0x%x ATIM_window %d "
		 "CFP_mode %d privacy_opt_impl %d DTIM_period %d CFP_period %d "
		 "current_bssid %pM current_essid %*phD current_bss_type %d "
		 "pm_mode %d ibss_change %d res %d "
		 "multi_domain_capability_implemented %d "
		 "international_roaming %d country_string %.3s",
		 wiphy_name(priv->hw->wiphy), le16_to_cpu(m->beacon_period),
		 le16_to_cpu(m->CFP_max_duration),
		 le16_to_cpu(m->medium_occupancy_limit),
		 le16_to_cpu(m->station_id), le16_to_cpu(m->ATIM_winकरोw),
		 m->CFP_mode, m->privacy_option_implemented, m->DTIM_period,
		 m->CFP_period, m->current_bssid,
		 IW_ESSID_MAX_SIZE, m->current_essid,
		 m->current_bss_type, m->घातer_mgmt_mode, m->ibss_change,
		 m->res, m->multi_करोमुख्य_capability_implemented,
		 m->multi_करोमुख्य_capability_enabled, m->country_string);
निकास:
	kमुक्त(m);
पूर्ण

अटल व्योम at76_dump_mib_mac(काष्ठा at76_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा mib_mac *m = kदो_स्मृति(माप(काष्ठा mib_mac), GFP_KERNEL);

	अगर (!m)
		वापस;

	ret = at76_get_mib(priv->udev, MIB_MAC, m, माप(काष्ठा mib_mac));
	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MAC) failed: %d\n", ret);
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_MIB, "%s: MIB MAC: max_tx_msdu_lifetime %d "
		 "max_rx_lifetime %d frag_threshold %d rts_threshold %d "
		 "cwmin %d cwmax %d short_retry_time %d long_retry_time %d "
		 "scan_type %d scan_channel %d probe_delay %u "
		 "min_channel_time %d max_channel_time %d listen_int %d "
		 "desired_ssid %*phD desired_bssid %pM desired_bsstype %d",
		 wiphy_name(priv->hw->wiphy),
		 le32_to_cpu(m->max_tx_msdu_lअगरeसमय),
		 le32_to_cpu(m->max_rx_lअगरeसमय),
		 le16_to_cpu(m->frag_threshold), le16_to_cpu(m->rts_threshold),
		 le16_to_cpu(m->cwmin), le16_to_cpu(m->cwmax),
		 m->लघु_retry_समय, m->दीर्घ_retry_समय, m->scan_type,
		 m->scan_channel, le16_to_cpu(m->probe_delay),
		 le16_to_cpu(m->min_channel_समय),
		 le16_to_cpu(m->max_channel_समय),
		 le16_to_cpu(m->listen_पूर्णांकerval),
		 IW_ESSID_MAX_SIZE, m->desired_ssid,
		 m->desired_bssid, m->desired_bsstype);
निकास:
	kमुक्त(m);
पूर्ण

अटल व्योम at76_dump_mib_phy(काष्ठा at76_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा mib_phy *m = kदो_स्मृति(माप(काष्ठा mib_phy), GFP_KERNEL);

	अगर (!m)
		वापस;

	ret = at76_get_mib(priv->udev, MIB_PHY, m, माप(काष्ठा mib_phy));
	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (PHY) failed: %d\n", ret);
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_MIB, "%s: MIB PHY: ed_threshold %d slot_time %d "
		 "sifs_time %d preamble_length %d plcp_header_length %d "
		 "mpdu_max_length %d cca_mode_supported %d operation_rate_set "
		 "0x%x 0x%x 0x%x 0x%x channel_id %d current_cca_mode %d "
		 "phy_type %d current_reg_domain %d",
		 wiphy_name(priv->hw->wiphy), le32_to_cpu(m->ed_threshold),
		 le16_to_cpu(m->slot_समय), le16_to_cpu(m->sअगरs_समय),
		 le16_to_cpu(m->preamble_length),
		 le16_to_cpu(m->plcp_header_length),
		 le16_to_cpu(m->mpdu_max_length),
		 le16_to_cpu(m->cca_mode_supported), m->operation_rate_set[0],
		 m->operation_rate_set[1], m->operation_rate_set[2],
		 m->operation_rate_set[3], m->channel_id, m->current_cca_mode,
		 m->phy_type, m->current_reg_करोमुख्य);
निकास:
	kमुक्त(m);
पूर्ण

अटल व्योम at76_dump_mib_local(काष्ठा at76_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा mib_local *m = kदो_स्मृति(माप(*m), GFP_KERNEL);

	अगर (!m)
		वापस;

	ret = at76_get_mib(priv->udev, MIB_LOCAL, m, माप(*m));
	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (LOCAL) failed: %d\n", ret);
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_MIB, "%s: MIB LOCAL: beacon_enable %d "
		 "txautorate_fallback %d ssid_size %d promiscuous_mode %d "
		 "preamble_type %d", wiphy_name(priv->hw->wiphy),
		 m->beacon_enable,
		 m->txस्वतःrate_fallback, m->ssid_size, m->promiscuous_mode,
		 m->preamble_type);
निकास:
	kमुक्त(m);
पूर्ण

अटल व्योम at76_dump_mib_mकरोमुख्य(काष्ठा at76_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा mib_mकरोमुख्य *m = kदो_स्मृति(माप(काष्ठा mib_mकरोमुख्य), GFP_KERNEL);

	अगर (!m)
		वापस;

	ret = at76_get_mib(priv->udev, MIB_MDOMAIN, m,
			   माप(काष्ठा mib_mकरोमुख्य));
	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MDOMAIN) failed: %d\n", ret);
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_MIB, "%s: MIB MDOMAIN: channel_list %*phD",
		 wiphy_name(priv->hw->wiphy),
		 (पूर्णांक)माप(m->channel_list), m->channel_list);

	at76_dbg(DBG_MIB, "%s: MIB MDOMAIN: tx_powerlevel %*phD",
		 wiphy_name(priv->hw->wiphy),
		 (पूर्णांक)माप(m->tx_घातerlevel), m->tx_घातerlevel);
निकास:
	kमुक्त(m);
पूर्ण

/* Enable monitor mode */
अटल पूर्णांक at76_start_monitor(काष्ठा at76_priv *priv)
अणु
	काष्ठा at76_req_scan scan;
	पूर्णांक ret;

	स_रखो(&scan, 0, माप(काष्ठा at76_req_scan));
	eth_broadcast_addr(scan.bssid);

	scan.channel = priv->channel;
	scan.scan_type = SCAN_TYPE_PASSIVE;
	scan.पूर्णांकernational_scan = 0;
	scan.min_channel_समय = cpu_to_le16(priv->scan_min_समय);
	scan.max_channel_समय = cpu_to_le16(priv->scan_max_समय);
	scan.probe_delay = cpu_to_le16(0);

	ret = at76_set_card_command(priv->udev, CMD_SCAN, &scan, माप(scan));
	अगर (ret >= 0)
		ret = at76_get_cmd_status(priv->udev, CMD_SCAN);

	वापस ret;
पूर्ण

/* Calculate padding from txbuf->wlength (which excludes the USB TX header),
   likely to compensate a flaw in the AT76C503A USB part ... */
अटल अंतरभूत पूर्णांक at76_calc_padding(पूर्णांक wlen)
अणु
	/* add the USB TX header */
	wlen += AT76_TX_HDRLEN;

	wlen = wlen % 64;

	अगर (wlen < 50)
		वापस 50 - wlen;

	अगर (wlen >= 61)
		वापस 64 + 50 - wlen;

	वापस 0;
पूर्ण

अटल व्योम at76_rx_callback(काष्ठा urb *urb)
अणु
	काष्ठा at76_priv *priv = urb->context;

	tasklet_schedule(&priv->rx_tasklet);
पूर्ण

अटल पूर्णांक at76_submit_rx_urb(काष्ठा at76_priv *priv)
अणु
	पूर्णांक ret;
	पूर्णांक size;
	काष्ठा sk_buff *skb = priv->rx_skb;

	अगर (!priv->rx_urb) अणु
		wiphy_err(priv->hw->wiphy, "%s: priv->rx_urb is NULL\n",
			  __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (!skb) अणु
		skb = dev_alloc_skb(माप(काष्ठा at76_rx_buffer));
		अगर (!skb) अणु
			wiphy_err(priv->hw->wiphy,
				  "cannot allocate rx skbuff\n");
			ret = -ENOMEM;
			जाओ निकास;
		पूर्ण
		priv->rx_skb = skb;
	पूर्ण अन्यथा अणु
		skb_push(skb, skb_headroom(skb));
		skb_trim(skb, 0);
	पूर्ण

	size = skb_tailroom(skb);
	usb_fill_bulk_urb(priv->rx_urb, priv->udev, priv->rx_pipe,
			  skb_put(skb, size), size, at76_rx_callback, priv);
	ret = usb_submit_urb(priv->rx_urb, GFP_ATOMIC);
	अगर (ret < 0) अणु
		अगर (ret == -ENODEV)
			at76_dbg(DBG_DEVSTART,
				 "usb_submit_urb returned -ENODEV");
		अन्यथा
			wiphy_err(priv->hw->wiphy,
				  "rx, usb_submit_urb failed: %d\n", ret);
	पूर्ण

निकास:
	अगर (ret < 0 && ret != -ENODEV)
		wiphy_err(priv->hw->wiphy,
			  "cannot submit rx urb - please unload the driver and/or power cycle the device\n");

	वापस ret;
पूर्ण

/* Download बाह्यal firmware */
अटल पूर्णांक at76_load_बाह्यal_fw(काष्ठा usb_device *udev, काष्ठा fwentry *fwe)
अणु
	पूर्णांक ret;
	पूर्णांक op_mode;
	पूर्णांक blockno = 0;
	पूर्णांक bsize;
	u8 *block;
	u8 *buf = fwe->extfw;
	पूर्णांक size = fwe->extfw_size;

	अगर (!buf || !size)
		वापस -ENOENT;

	op_mode = at76_get_op_mode(udev);
	at76_dbg(DBG_DEVSTART, "opmode %d", op_mode);

	अगर (op_mode != OPMODE_NORMAL_NIC_WITHOUT_FLASH) अणु
		dev_err(&udev->dev, "unexpected opmode %d\n", op_mode);
		वापस -EINVAL;
	पूर्ण

	block = kदो_स्मृति(FW_BLOCK_SIZE, GFP_KERNEL);
	अगर (!block)
		वापस -ENOMEM;

	at76_dbg(DBG_DEVSTART, "downloading external firmware");

	/* क्रम fw >= 0.100, the device needs an extra empty block */
	करो अणु
		bsize = min_t(पूर्णांक, size, FW_BLOCK_SIZE);
		स_नकल(block, buf, bsize);
		at76_dbg(DBG_DEVSTART,
			 "ext fw, size left = %5d, bsize = %4d, blockno = %2d",
			 size, bsize, blockno);
		ret = at76_load_ext_fw_block(udev, blockno, block, bsize);
		अगर (ret != bsize) अणु
			dev_err(&udev->dev,
				"loading %dth firmware block failed: %d\n",
				blockno, ret);
			ret = -EIO;
			जाओ निकास;
		पूर्ण
		buf += bsize;
		size -= bsize;
		blockno++;
	पूर्ण जबतक (bsize > 0);

	अगर (at76_is_505a(fwe->board_type)) अणु
		at76_dbg(DBG_DEVSTART, "200 ms delay for 505a");
		schedule_समयout_पूर्णांकerruptible(HZ / 5 + 1);
	पूर्ण

निकास:
	kमुक्त(block);
	अगर (ret < 0)
		dev_err(&udev->dev,
			"downloading external firmware failed: %d\n", ret);
	वापस ret;
पूर्ण

/* Download पूर्णांकernal firmware */
अटल पूर्णांक at76_load_पूर्णांकernal_fw(काष्ठा usb_device *udev, काष्ठा fwentry *fwe)
अणु
	पूर्णांक ret;
	पूर्णांक need_remap = !at76_is_505a(fwe->board_type);

	ret = at76_usbdfu_करोwnload(udev, fwe->पूर्णांकfw, fwe->पूर्णांकfw_size,
				   need_remap ? 0 : 2 * HZ);

	अगर (ret < 0) अणु
		dev_err(&udev->dev,
			"downloading internal fw failed with %d\n", ret);
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_DEVSTART, "sending REMAP");

	/* no REMAP क्रम 505A (see SF driver) */
	अगर (need_remap) अणु
		ret = at76_remap(udev);
		अगर (ret < 0) अणु
			dev_err(&udev->dev,
				"sending REMAP failed with %d\n", ret);
			जाओ निकास;
		पूर्ण
	पूर्ण

	at76_dbg(DBG_DEVSTART, "sleeping for 2 seconds");
	schedule_समयout_पूर्णांकerruptible(2 * HZ + 1);
	usb_reset_device(udev);

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक at76_startup_device(काष्ठा at76_priv *priv)
अणु
	काष्ठा at76_card_config *ccfg = &priv->card_config;
	पूर्णांक ret;

	at76_dbg(DBG_PARAMS,
		 "%s param: ssid %.*s (%*phD) mode %s ch %d wep %s key %d "
		 "keylen %d", wiphy_name(priv->hw->wiphy), priv->essid_size,
		 priv->essid, IW_ESSID_MAX_SIZE, priv->essid,
		 priv->iw_mode == IW_MODE_ADHOC ? "adhoc" : "infra",
		 priv->channel, priv->wep_enabled ? "enabled" : "disabled",
		 priv->wep_key_id, priv->wep_keys_len[priv->wep_key_id]);
	at76_dbg(DBG_PARAMS,
		 "%s param: preamble %s rts %d retry %d frag %d "
		 "txrate %s auth_mode %d", wiphy_name(priv->hw->wiphy),
		 preambles[priv->preamble_type], priv->rts_threshold,
		 priv->लघु_retry_limit, priv->frag_threshold,
		 priv->txrate == TX_RATE_1MBIT ? "1MBit" : priv->txrate ==
		 TX_RATE_2MBIT ? "2MBit" : priv->txrate ==
		 TX_RATE_5_5MBIT ? "5.5MBit" : priv->txrate ==
		 TX_RATE_11MBIT ? "11MBit" : priv->txrate ==
		 TX_RATE_AUTO ? "auto" : "<invalid>", priv->auth_mode);
	at76_dbg(DBG_PARAMS,
		 "%s param: pm_mode %d pm_period %d auth_mode %s "
		 "scan_times %d %d scan_mode %s",
		 wiphy_name(priv->hw->wiphy), priv->pm_mode, priv->pm_period,
		 priv->auth_mode == WLAN_AUTH_OPEN ? "open" : "shared_secret",
		 priv->scan_min_समय, priv->scan_max_समय,
		 priv->scan_mode == SCAN_TYPE_ACTIVE ? "active" : "passive");

	स_रखो(ccfg, 0, माप(काष्ठा at76_card_config));
	ccfg->promiscuous_mode = 0;
	ccfg->लघु_retry_limit = priv->लघु_retry_limit;

	अगर (priv->wep_enabled) अणु
		अगर (priv->wep_keys_len[priv->wep_key_id] > WEP_SMALL_KEY_LEN)
			ccfg->encryption_type = 2;
		अन्यथा
			ccfg->encryption_type = 1;

		/* jal: always exclude unencrypted अगर WEP is active */
		ccfg->exclude_unencrypted = 1;
	पूर्ण अन्यथा अणु
		ccfg->exclude_unencrypted = 0;
		ccfg->encryption_type = 0;
	पूर्ण

	ccfg->rts_threshold = cpu_to_le16(priv->rts_threshold);
	ccfg->fragmentation_threshold = cpu_to_le16(priv->frag_threshold);

	स_नकल(ccfg->basic_rate_set, hw_rates, 4);
	/* jal: really needed, we करो a set_mib क्रम स्वतःrate later ??? */
	ccfg->स्वतः_rate_fallback = (priv->txrate == TX_RATE_AUTO ? 1 : 0);
	ccfg->channel = priv->channel;
	ccfg->privacy_invoked = priv->wep_enabled;
	स_नकल(ccfg->current_ssid, priv->essid, IW_ESSID_MAX_SIZE);
	ccfg->ssid_len = priv->essid_size;

	ccfg->wep_शेष_key_id = priv->wep_key_id;
	स_नकल(ccfg->wep_शेष_key_value, priv->wep_keys,
	       माप(priv->wep_keys));

	ccfg->लघु_preamble = priv->preamble_type;
	ccfg->beacon_period = cpu_to_le16(priv->beacon_period);

	ret = at76_set_card_command(priv->udev, CMD_STARTUP, &priv->card_config,
				    माप(काष्ठा at76_card_config));
	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy, "at76_set_card_command failed: %d\n",
			  ret);
		वापस ret;
	पूर्ण

	at76_रुको_completion(priv, CMD_STARTUP);

	/* हटाओ BSSID from previous run */
	eth_zero_addr(priv->bssid);

	priv->scanning = false;

	अगर (at76_set_radio(priv, 1) == 1)
		at76_रुको_completion(priv, CMD_RADIO_ON);

	ret = at76_set_preamble(priv, priv->preamble_type);
	अगर (ret < 0)
		वापस ret;

	ret = at76_set_frag(priv, priv->frag_threshold);
	अगर (ret < 0)
		वापस ret;

	ret = at76_set_rts(priv, priv->rts_threshold);
	अगर (ret < 0)
		वापस ret;

	ret = at76_set_स्वतःrate_fallback(priv,
					 priv->txrate == TX_RATE_AUTO ? 1 : 0);
	अगर (ret < 0)
		वापस ret;

	ret = at76_set_pm_mode(priv);
	अगर (ret < 0)
		वापस ret;

	अगर (at76_debug & DBG_MIB) अणु
		at76_dump_mib_mac(priv);
		at76_dump_mib_mac_addr(priv);
		at76_dump_mib_mac_mgmt(priv);
		at76_dump_mib_mac_wep(priv);
		at76_dump_mib_mकरोमुख्य(priv);
		at76_dump_mib_phy(priv);
		at76_dump_mib_local(priv);
	पूर्ण

	वापस 0;
पूर्ण

/* Enable or disable promiscuous mode */
अटल व्योम at76_work_set_promisc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा at76_priv *priv = container_of(work, काष्ठा at76_priv,
					      work_set_promisc);
	पूर्णांक ret = 0;

	अगर (priv->device_unplugged)
		वापस;

	mutex_lock(&priv->mtx);

	priv->mib_buf.type = MIB_LOCAL;
	priv->mib_buf.size = 1;
	priv->mib_buf.index = दुरत्व(काष्ठा mib_local, promiscuous_mode);
	priv->mib_buf.data.byte = priv->promisc ? 1 : 0;

	ret = at76_set_mib(priv, &priv->mib_buf);
	अगर (ret < 0)
		wiphy_err(priv->hw->wiphy,
			  "set_mib (promiscuous_mode) failed: %d\n", ret);

	mutex_unlock(&priv->mtx);
पूर्ण

/* Submit Rx urb back to the device */
अटल व्योम at76_work_submit_rx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा at76_priv *priv = container_of(work, काष्ठा at76_priv,
					      work_submit_rx);

	mutex_lock(&priv->mtx);
	at76_submit_rx_urb(priv);
	mutex_unlock(&priv->mtx);
पूर्ण

/* This is a workaround to make scan working:
 * currently mac80211 करोes not process frames with no frequency
 * inक्रमmation.
 * However during scan the HW perक्रमms a sweep by itself, and we
 * are unable to know where the radio is actually tuned.
 * This function tries to करो its best to guess this inक्रमmation..
 * During scan, If the current frame is a beacon or a probe response,
 * the channel inक्रमmation is extracted from it.
 * When not scanning, क्रम other frames, or अगर it happens that क्रम
 * whatever reason we fail to parse beacons and probe responses, this
 * function वापसs the priv->channel inक्रमmation, that should be correct
 * at least when we are not scanning.
 */
अटल अंतरभूत पूर्णांक at76_guess_freq(काष्ठा at76_priv *priv)
अणु
	माप_प्रकार el_off;
	स्थिर u8 *el;
	पूर्णांक channel = priv->channel;
	पूर्णांक len = priv->rx_skb->len;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)priv->rx_skb->data;

	अगर (!priv->scanning)
		जाओ निकास;

	अगर (len < 24)
		जाओ निकास;

	अगर (ieee80211_is_probe_resp(hdr->frame_control)) अणु
		el_off = दुरत्व(काष्ठा ieee80211_mgmt, u.probe_resp.variable);
		el = ((काष्ठा ieee80211_mgmt *)hdr)->u.probe_resp.variable;
	पूर्ण अन्यथा अगर (ieee80211_is_beacon(hdr->frame_control)) अणु
		el_off = दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
		el = ((काष्ठा ieee80211_mgmt *)hdr)->u.beacon.variable;
	पूर्ण अन्यथा अणु
		जाओ निकास;
	पूर्ण
	len -= el_off;

	el = cfg80211_find_ie(WLAN_EID_DS_PARAMS, el, len);
	अगर (el && el[1] > 0)
		channel = el[2];

निकास:
	वापस ieee80211_channel_to_frequency(channel, NL80211_BAND_2GHZ);
पूर्ण

अटल व्योम at76_rx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा at76_priv *priv = from_tasklet(priv, t, rx_tasklet);
	काष्ठा urb *urb = priv->rx_urb;
	काष्ठा at76_rx_buffer *buf;
	काष्ठा ieee80211_rx_status rx_status = अणु 0 पूर्ण;

	अगर (priv->device_unplugged) अणु
		at76_dbg(DBG_DEVSTART, "device unplugged");
		at76_dbg(DBG_DEVSTART, "urb status %d", urb->status);
		वापस;
	पूर्ण

	अगर (!priv->rx_skb || !priv->rx_skb->data)
		वापस;

	buf = (काष्ठा at76_rx_buffer *)priv->rx_skb->data;

	अगर (urb->status != 0) अणु
		अगर (urb->status != -ENOENT && urb->status != -ECONNRESET)
			at76_dbg(DBG_URB,
				 "%s %s: - nonzero Rx bulk status received: %d",
				 __func__, wiphy_name(priv->hw->wiphy),
				 urb->status);
		वापस;
	पूर्ण

	at76_dbg(DBG_RX_ATMEL_HDR,
		 "%s: rx frame: rate %d rssi %d noise %d link %d",
		 wiphy_name(priv->hw->wiphy), buf->rx_rate, buf->rssi,
		 buf->noise_level, buf->link_quality);

	skb_pull(priv->rx_skb, AT76_RX_HDRLEN);
	skb_trim(priv->rx_skb, le16_to_cpu(buf->wlength));
	at76_dbg_dump(DBG_RX_DATA, priv->rx_skb->data,
		      priv->rx_skb->len, "RX: len=%d", priv->rx_skb->len);

	rx_status.संकेत = buf->rssi;
	rx_status.flag |= RX_FLAG_DECRYPTED;
	rx_status.flag |= RX_FLAG_IV_STRIPPED;
	rx_status.band = NL80211_BAND_2GHZ;
	rx_status.freq = at76_guess_freq(priv);

	at76_dbg(DBG_MAC80211, "calling ieee80211_rx_irqsafe(): %d/%d",
		 priv->rx_skb->len, priv->rx_skb->data_len);
	स_नकल(IEEE80211_SKB_RXCB(priv->rx_skb), &rx_status, माप(rx_status));
	ieee80211_rx_irqsafe(priv->hw, priv->rx_skb);

	/* Use a new skb क्रम the next receive */
	priv->rx_skb = शून्य;

	at76_submit_rx_urb(priv);
पूर्ण

/* Load firmware पूर्णांकo kernel memory and parse it */
अटल काष्ठा fwentry *at76_load_firmware(काष्ठा usb_device *udev,
					  क्रमागत board_type board_type)
अणु
	पूर्णांक ret;
	अक्षर *str;
	काष्ठा at76_fw_header *fwh;
	काष्ठा fwentry *fwe = &firmwares[board_type];

	mutex_lock(&fw_mutex);

	अगर (fwe->loaded) अणु
		at76_dbg(DBG_FW, "re-using previously loaded fw");
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_FW, "downloading firmware %s", fwe->fwname);
	ret = request_firmware(&fwe->fw, fwe->fwname, &udev->dev);
	अगर (ret < 0) अणु
		dev_err(&udev->dev, "firmware %s not found!\n",
			fwe->fwname);
		dev_err(&udev->dev,
			"you may need to download the firmware from http://developer.berlios.de/projects/at76c503a/\n");
		जाओ निकास;
	पूर्ण

	at76_dbg(DBG_FW, "got it.");
	fwh = (काष्ठा at76_fw_header *)(fwe->fw->data);

	अगर (fwe->fw->size <= माप(*fwh)) अणु
		dev_err(&udev->dev,
			"firmware is too short (0x%zx)\n", fwe->fw->size);
		जाओ निकास;
	पूर्ण

	/* CRC currently not checked */
	fwe->board_type = le32_to_cpu(fwh->board_type);
	अगर (fwe->board_type != board_type) अणु
		dev_err(&udev->dev,
			"board type mismatch, requested %u, got %u\n",
			board_type, fwe->board_type);
		जाओ निकास;
	पूर्ण

	fwe->fw_version.major = fwh->major;
	fwe->fw_version.minor = fwh->minor;
	fwe->fw_version.patch = fwh->patch;
	fwe->fw_version.build = fwh->build;

	str = (अक्षर *)fwh + le32_to_cpu(fwh->str_offset);
	fwe->पूर्णांकfw = (u8 *)fwh + le32_to_cpu(fwh->पूर्णांक_fw_offset);
	fwe->पूर्णांकfw_size = le32_to_cpu(fwh->पूर्णांक_fw_len);
	fwe->extfw = (u8 *)fwh + le32_to_cpu(fwh->ext_fw_offset);
	fwe->extfw_size = le32_to_cpu(fwh->ext_fw_len);

	fwe->loaded = 1;

	dev_prपूर्णांकk(KERN_DEBUG, &udev->dev,
		   "using firmware %s (version %d.%d.%d-%d)\n",
		   fwe->fwname, fwh->major, fwh->minor, fwh->patch, fwh->build);

	at76_dbg(DBG_DEVSTART, "board %u, int %d:%d, ext %d:%d", board_type,
		 le32_to_cpu(fwh->पूर्णांक_fw_offset), le32_to_cpu(fwh->पूर्णांक_fw_len),
		 le32_to_cpu(fwh->ext_fw_offset), le32_to_cpu(fwh->ext_fw_len));
	at76_dbg(DBG_DEVSTART, "firmware id %s", str);

निकास:
	mutex_unlock(&fw_mutex);

	अगर (fwe->loaded)
		वापस fwe;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक at76_join(काष्ठा at76_priv *priv)
अणु
	काष्ठा at76_req_join join;
	पूर्णांक ret;

	स_रखो(&join, 0, माप(काष्ठा at76_req_join));
	स_नकल(join.essid, priv->essid, priv->essid_size);
	join.essid_size = priv->essid_size;
	स_नकल(join.bssid, priv->bssid, ETH_ALEN);
	join.bss_type = INFRASTRUCTURE_MODE;
	join.channel = priv->channel;
	join.समयout = cpu_to_le16(2000);

	at76_dbg(DBG_MAC80211, "%s: sending CMD_JOIN", __func__);
	ret = at76_set_card_command(priv->udev, CMD_JOIN, &join,
				    माप(काष्ठा at76_req_join));

	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy, "at76_set_card_command failed: %d\n",
			  ret);
		वापस 0;
	पूर्ण

	ret = at76_रुको_completion(priv, CMD_JOIN);
	at76_dbg(DBG_MAC80211, "%s: CMD_JOIN returned: 0x%02x", __func__, ret);
	अगर (ret != CMD_STATUS_COMPLETE) अणु
		wiphy_err(priv->hw->wiphy, "at76_wait_completion failed: %d\n",
			  ret);
		वापस 0;
	पूर्ण

	at76_set_pm_mode(priv);

	वापस 0;
पूर्ण

अटल व्योम at76_work_join_bssid(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा at76_priv *priv = container_of(work, काष्ठा at76_priv,
					      work_join_bssid);

	अगर (priv->device_unplugged)
		वापस;

	mutex_lock(&priv->mtx);

	अगर (is_valid_ether_addr(priv->bssid))
		at76_join(priv);

	mutex_unlock(&priv->mtx);
पूर्ण

अटल व्योम at76_mac80211_tx_callback(काष्ठा urb *urb)
अणु
	काष्ठा at76_priv *priv = urb->context;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(priv->tx_skb);

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		info->flags |= IEEE80211_TX_STAT_ACK;
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
		/* fail, urb has been unlinked */
		/* FIXME: add error message */
		अवरोध;
	शेष:
		at76_dbg(DBG_URB, "%s - nonzero tx status received: %d",
			 __func__, urb->status);
		अवरोध;
	पूर्ण

	स_रखो(&info->status, 0, माप(info->status));

	ieee80211_tx_status_irqsafe(priv->hw, priv->tx_skb);

	priv->tx_skb = शून्य;

	ieee80211_wake_queues(priv->hw);
पूर्ण

अटल व्योम at76_mac80211_tx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_tx_control *control,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा at76_priv *priv = hw->priv;
	काष्ठा at76_tx_buffer *tx_buffer = priv->bulk_out_buffer;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
	पूर्णांक padding, submit_len, ret;

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	अगर (priv->tx_urb->status == -EINPROGRESS) अणु
		wiphy_err(priv->hw->wiphy,
			  "%s called while tx urb is pending\n", __func__);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	/* The following code lines are important when the device is going to
	 * authenticate with a new bssid. The driver must send CMD_JOIN beक्रमe
	 * an authentication frame is transmitted. For this to succeed, the
	 * correct bssid of the AP must be known. As mac80211 करोes not inक्रमm
	 * drivers about the bssid prior to the authentication process the
	 * following workaround is necessary. If the TX frame is an
	 * authentication frame extract the bssid and send the CMD_JOIN. */
	अगर (mgmt->frame_control & cpu_to_le16(IEEE80211_STYPE_AUTH)) अणु
		अगर (!ether_addr_equal_64bits(priv->bssid, mgmt->bssid)) अणु
			स_नकल(priv->bssid, mgmt->bssid, ETH_ALEN);
			ieee80211_queue_work(hw, &priv->work_join_bssid);
			dev_kमुक्त_skb_any(skb);
			वापस;
		पूर्ण
	पूर्ण

	ieee80211_stop_queues(hw);

	at76_ledtrig_tx_activity();	/* tell ledtrigger we send a packet */

	WARN_ON(priv->tx_skb != शून्य);

	priv->tx_skb = skb;
	padding = at76_calc_padding(skb->len);
	submit_len = AT76_TX_HDRLEN + skb->len + padding;

	/* setup 'Atmel' header */
	स_रखो(tx_buffer, 0, माप(*tx_buffer));
	tx_buffer->padding = padding;
	tx_buffer->wlength = cpu_to_le16(skb->len);
	tx_buffer->tx_rate = ieee80211_get_tx_rate(hw, info)->hw_value;
	स_रखो(tx_buffer->reserved, 0, माप(tx_buffer->reserved));
	स_नकल(tx_buffer->packet, skb->data, skb->len);

	at76_dbg(DBG_TX_DATA, "%s tx: wlen 0x%x pad 0x%x rate %d hdr",
		 wiphy_name(priv->hw->wiphy), le16_to_cpu(tx_buffer->wlength),
		 tx_buffer->padding, tx_buffer->tx_rate);

	/* send stuff */
	at76_dbg_dump(DBG_TX_DATA_CONTENT, tx_buffer, submit_len,
		      "%s(): tx_buffer %d bytes:", __func__, submit_len);
	usb_fill_bulk_urb(priv->tx_urb, priv->udev, priv->tx_pipe, tx_buffer,
			  submit_len, at76_mac80211_tx_callback, priv);
	ret = usb_submit_urb(priv->tx_urb, GFP_ATOMIC);
	अगर (ret) अणु
		wiphy_err(priv->hw->wiphy, "error in tx submit urb: %d\n", ret);
		अगर (ret == -EINVAL)
			wiphy_err(priv->hw->wiphy,
				  "-EINVAL: tx urb %p hcpriv %p complete %p\n",
				  priv->tx_urb,
				  priv->tx_urb->hcpriv, priv->tx_urb->complete);
	पूर्ण
पूर्ण

अटल पूर्णांक at76_mac80211_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा at76_priv *priv = hw->priv;
	पूर्णांक ret;

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	mutex_lock(&priv->mtx);

	ret = at76_submit_rx_urb(priv);
	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy, "open: submit_rx_urb failed: %d\n",
			  ret);
		जाओ error;
	पूर्ण

	at76_startup_device(priv);

	at76_start_monitor(priv);

error:
	mutex_unlock(&priv->mtx);

	वापस 0;
पूर्ण

अटल व्योम at76_mac80211_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा at76_priv *priv = hw->priv;

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	cancel_delayed_work(&priv->dwork_hw_scan);
	cancel_work_sync(&priv->work_join_bssid);
	cancel_work_sync(&priv->work_set_promisc);

	mutex_lock(&priv->mtx);

	अगर (!priv->device_unplugged) अणु
		/* We are called by "ifconfig ethX down", not because the
		 * device is not available anymore. */
		at76_set_radio(priv, 0);

		/* We unlink rx_urb because at76_खोलो() re-submits it.
		 * If unplugged, at76_delete_device() takes care of it. */
		usb_समाप्त_urb(priv->rx_urb);
	पूर्ण

	mutex_unlock(&priv->mtx);
पूर्ण

अटल पूर्णांक at76_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा at76_priv *priv = hw->priv;
	पूर्णांक ret = 0;

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	mutex_lock(&priv->mtx);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		priv->iw_mode = IW_MODE_INFRA;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		जाओ निकास;
	पूर्ण

निकास:
	mutex_unlock(&priv->mtx);

	वापस ret;
पूर्ण

अटल व्योम at76_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	at76_dbg(DBG_MAC80211, "%s()", __func__);
पूर्ण

अटल व्योम at76_dwork_hw_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा at76_priv *priv = container_of(work, काष्ठा at76_priv,
					      dwork_hw_scan.work);
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = false,
	पूर्ण;
	पूर्णांक ret;

	अगर (priv->device_unplugged)
		वापस;

	mutex_lock(&priv->mtx);

	ret = at76_get_cmd_status(priv->udev, CMD_SCAN);
	at76_dbg(DBG_MAC80211, "%s: CMD_SCAN status 0x%02x", __func__, ret);

	/* FIXME: add maximum समय क्रम scan to complete */

	अगर (ret != CMD_STATUS_COMPLETE) अणु
		ieee80211_queue_delayed_work(priv->hw, &priv->dwork_hw_scan,
					     SCAN_POLL_INTERVAL);
		mutex_unlock(&priv->mtx);
		वापस;
	पूर्ण

	अगर (is_valid_ether_addr(priv->bssid))
		at76_join(priv);

	priv->scanning = false;

	mutex_unlock(&priv->mtx);

	ieee80211_scan_completed(priv->hw, &info);

	ieee80211_wake_queues(priv->hw);
पूर्ण

अटल पूर्णांक at76_hw_scan(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा cfg80211_scan_request *req = &hw_req->req;
	काष्ठा at76_priv *priv = hw->priv;
	काष्ठा at76_req_scan scan;
	u8 *ssid = शून्य;
	पूर्णांक ret, len = 0;

	at76_dbg(DBG_MAC80211, "%s():", __func__);

	अगर (priv->device_unplugged)
		वापस 0;

	mutex_lock(&priv->mtx);

	ieee80211_stop_queues(hw);

	स_रखो(&scan, 0, माप(काष्ठा at76_req_scan));
	eth_broadcast_addr(scan.bssid);

	अगर (req->n_ssids) अणु
		scan.scan_type = SCAN_TYPE_ACTIVE;
		ssid = req->ssids[0].ssid;
		len = req->ssids[0].ssid_len;
	पूर्ण अन्यथा अणु
		scan.scan_type = SCAN_TYPE_PASSIVE;
	पूर्ण

	अगर (len) अणु
		स_नकल(scan.essid, ssid, len);
		scan.essid_size = len;
	पूर्ण

	scan.min_channel_समय = cpu_to_le16(priv->scan_min_समय);
	scan.max_channel_समय = cpu_to_le16(priv->scan_max_समय);
	scan.probe_delay = cpu_to_le16(priv->scan_min_समय * 1000);
	scan.पूर्णांकernational_scan = 0;

	at76_dbg(DBG_MAC80211, "%s: sending CMD_SCAN", __func__);
	ret = at76_set_card_command(priv->udev, CMD_SCAN, &scan, माप(scan));

	अगर (ret < 0) अणु
		wiphy_err(priv->hw->wiphy, "CMD_SCAN failed: %d\n", ret);
		जाओ निकास;
	पूर्ण

	priv->scanning = true;
	ieee80211_queue_delayed_work(priv->hw, &priv->dwork_hw_scan,
				     SCAN_POLL_INTERVAL);

निकास:
	mutex_unlock(&priv->mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक at76_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा at76_priv *priv = hw->priv;

	at76_dbg(DBG_MAC80211, "%s(): channel %d",
		 __func__, hw->conf.chandef.chan->hw_value);
	at76_dbg_dump(DBG_MAC80211, priv->bssid, ETH_ALEN, "bssid:");

	mutex_lock(&priv->mtx);

	priv->channel = hw->conf.chandef.chan->hw_value;

	अगर (is_valid_ether_addr(priv->bssid))
		at76_join(priv);
	अन्यथा
		at76_start_monitor(priv);

	mutex_unlock(&priv->mtx);

	वापस 0;
पूर्ण

अटल व्योम at76_bss_info_changed(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_bss_conf *conf,
				  u32 changed)
अणु
	काष्ठा at76_priv *priv = hw->priv;

	at76_dbg(DBG_MAC80211, "%s():", __func__);

	अगर (!(changed & BSS_CHANGED_BSSID))
		वापस;

	at76_dbg_dump(DBG_MAC80211, conf->bssid, ETH_ALEN, "bssid:");

	mutex_lock(&priv->mtx);

	स_नकल(priv->bssid, conf->bssid, ETH_ALEN);

	अगर (is_valid_ether_addr(priv->bssid))
		/* mac80211 is joining a bss */
		at76_join(priv);

	mutex_unlock(&priv->mtx);
पूर्ण

/* must be atomic */
अटल व्योम at76_configure_filter(काष्ठा ieee80211_hw *hw,
				  अचिन्हित पूर्णांक changed_flags,
				  अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा at76_priv *priv = hw->priv;
	पूर्णांक flags;

	at76_dbg(DBG_MAC80211, "%s(): changed_flags=0x%08x "
		 "total_flags=0x%08x",
		 __func__, changed_flags, *total_flags);

	flags = changed_flags & AT76_SUPPORTED_FILTERS;
	*total_flags = AT76_SUPPORTED_FILTERS;

	/* Bail out after updating flags to prevent a WARN_ON in mac80211. */
	अगर (priv->device_unplugged)
		वापस;

	/* FIXME: access to priv->promisc should be रक्षित with
	 * priv->mtx, but it's impossible because this function needs to be
	 * atomic */

	अगर (flags && !priv->promisc) अणु
		/* mac80211 wants us to enable promiscuous mode */
		priv->promisc = 1;
	पूर्ण अन्यथा अगर (!flags && priv->promisc) अणु
		/* we need to disable promiscuous mode */
		priv->promisc = 0;
	पूर्ण अन्यथा
		वापस;

	ieee80211_queue_work(hw, &priv->work_set_promisc);
पूर्ण

अटल पूर्णांक at76_set_wep(काष्ठा at76_priv *priv)
अणु
	पूर्णांक ret = 0;
	काष्ठा mib_mac_wep *mib_data = &priv->mib_buf.data.wep_mib;

	priv->mib_buf.type = MIB_MAC_WEP;
	priv->mib_buf.size = माप(काष्ठा mib_mac_wep);
	priv->mib_buf.index = 0;

	स_रखो(mib_data, 0, माप(*mib_data));

	अगर (priv->wep_enabled) अणु
		अगर (priv->wep_keys_len[priv->wep_key_id] > WEP_SMALL_KEY_LEN)
			mib_data->encryption_level = 2;
		अन्यथा
			mib_data->encryption_level = 1;

		/* always exclude unencrypted अगर WEP is active */
		mib_data->exclude_unencrypted = 1;
	पूर्ण अन्यथा अणु
		mib_data->exclude_unencrypted = 0;
		mib_data->encryption_level = 0;
	पूर्ण

	mib_data->privacy_invoked = priv->wep_enabled;
	mib_data->wep_शेष_key_id = priv->wep_key_id;
	स_नकल(mib_data->wep_शेष_keyvalue, priv->wep_keys,
	       माप(priv->wep_keys));

	ret = at76_set_mib(priv, &priv->mib_buf);

	अगर (ret < 0)
		wiphy_err(priv->hw->wiphy,
			  "set_mib (wep) failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक at76_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
			काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा at76_priv *priv = hw->priv;

	पूर्णांक i;

	at76_dbg(DBG_MAC80211, "%s(): cmd %d key->cipher %d key->keyidx %d "
		 "key->keylen %d",
		 __func__, cmd, key->cipher, key->keyidx, key->keylen);

	अगर ((key->cipher != WLAN_CIPHER_SUITE_WEP40) &&
	    (key->cipher != WLAN_CIPHER_SUITE_WEP104))
		वापस -EOPNOTSUPP;

	key->hw_key_idx = key->keyidx;

	mutex_lock(&priv->mtx);

	चयन (cmd) अणु
	हाल SET_KEY:
		स_नकल(priv->wep_keys[key->keyidx], key->key, key->keylen);
		priv->wep_keys_len[key->keyidx] = key->keylen;

		/* FIXME: find out how to करो this properly */
		priv->wep_key_id = key->keyidx;

		अवरोध;
	हाल DISABLE_KEY:
	शेष:
		priv->wep_keys_len[key->keyidx] = 0;
		अवरोध;
	पूर्ण

	priv->wep_enabled = 0;

	क्रम (i = 0; i < WEP_KEYS; i++) अणु
		अगर (priv->wep_keys_len[i] != 0)
			priv->wep_enabled = 1;
	पूर्ण

	at76_set_wep(priv);

	mutex_unlock(&priv->mtx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops at76_ops = अणु
	.tx = at76_mac80211_tx,
	.add_पूर्णांकerface = at76_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = at76_हटाओ_पूर्णांकerface,
	.config = at76_config,
	.bss_info_changed = at76_bss_info_changed,
	.configure_filter = at76_configure_filter,
	.start = at76_mac80211_start,
	.stop = at76_mac80211_stop,
	.hw_scan = at76_hw_scan,
	.set_key = at76_set_key,
पूर्ण;

/* Allocate network device and initialize निजी data */
अटल काष्ठा at76_priv *at76_alloc_new_device(काष्ठा usb_device *udev)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा at76_priv *priv;

	hw = ieee80211_alloc_hw(माप(काष्ठा at76_priv), &at76_ops);
	अगर (!hw) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": could not register"
		       " ieee80211_hw\n");
		वापस शून्य;
	पूर्ण

	priv = hw->priv;
	priv->hw = hw;

	priv->udev = udev;

	mutex_init(&priv->mtx);
	INIT_WORK(&priv->work_set_promisc, at76_work_set_promisc);
	INIT_WORK(&priv->work_submit_rx, at76_work_submit_rx);
	INIT_WORK(&priv->work_join_bssid, at76_work_join_bssid);
	INIT_DELAYED_WORK(&priv->dwork_hw_scan, at76_dwork_hw_scan);

	tasklet_setup(&priv->rx_tasklet, at76_rx_tasklet);

	priv->pm_mode = AT76_PM_OFF;
	priv->pm_period = 0;

	/* unit us */

	वापस priv;
पूर्ण

अटल पूर्णांक at76_alloc_urbs(काष्ठा at76_priv *priv,
			   काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक, *ep_in, *ep_out;
	पूर्णांक i;
	पूर्णांक buffer_size;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;

	at76_dbg(DBG_PROC_ENTRY, "%s: ENTER", __func__);

	at76_dbg(DBG_URB, "%s: NumEndpoints %d ", __func__,
		 पूर्णांकerface->cur_altsetting->desc.bNumEndpoपूर्णांकs);

	ep_in = शून्य;
	ep_out = शून्य;
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		at76_dbg(DBG_URB, "%s: %d. endpoint: addr 0x%x attr 0x%x",
			 __func__, i, endpoपूर्णांक->bEndpoपूर्णांकAddress,
			 endpoपूर्णांक->bmAttributes);

		अगर (!ep_in && usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक))
			ep_in = endpoपूर्णांक;

		अगर (!ep_out && usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक))
			ep_out = endpoपूर्णांक;
	पूर्ण

	अगर (!ep_in || !ep_out) अणु
		dev_err(&पूर्णांकerface->dev, "bulk endpoints missing\n");
		वापस -ENXIO;
	पूर्ण

	priv->rx_pipe = usb_rcvbulkpipe(priv->udev, ep_in->bEndpoपूर्णांकAddress);
	priv->tx_pipe = usb_sndbulkpipe(priv->udev, ep_out->bEndpoपूर्णांकAddress);

	priv->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	priv->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!priv->rx_urb || !priv->tx_urb) अणु
		dev_err(&पूर्णांकerface->dev, "cannot allocate URB\n");
		वापस -ENOMEM;
	पूर्ण

	buffer_size = माप(काष्ठा at76_tx_buffer) + MAX_PADDING_SIZE;
	priv->bulk_out_buffer = kदो_स्मृति(buffer_size, GFP_KERNEL);
	अगर (!priv->bulk_out_buffer)
		वापस -ENOMEM;

	at76_dbg(DBG_PROC_ENTRY, "%s: EXIT", __func__);

	वापस 0;
पूर्ण

अटल काष्ठा ieee80211_rate at76_rates[] = अणु
	अणु .bitrate = 10, .hw_value = TX_RATE_1MBIT, पूर्ण,
	अणु .bitrate = 20, .hw_value = TX_RATE_2MBIT, पूर्ण,
	अणु .bitrate = 55, .hw_value = TX_RATE_5_5MBIT, पूर्ण,
	अणु .bitrate = 110, .hw_value = TX_RATE_11MBIT, पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_channel at76_channels[] = अणु
	अणु .center_freq = 2412, .hw_value = 1 पूर्ण,
	अणु .center_freq = 2417, .hw_value = 2 पूर्ण,
	अणु .center_freq = 2422, .hw_value = 3 पूर्ण,
	अणु .center_freq = 2427, .hw_value = 4 पूर्ण,
	अणु .center_freq = 2432, .hw_value = 5 पूर्ण,
	अणु .center_freq = 2437, .hw_value = 6 पूर्ण,
	अणु .center_freq = 2442, .hw_value = 7 पूर्ण,
	अणु .center_freq = 2447, .hw_value = 8 पूर्ण,
	अणु .center_freq = 2452, .hw_value = 9 पूर्ण,
	अणु .center_freq = 2457, .hw_value = 10 पूर्ण,
	अणु .center_freq = 2462, .hw_value = 11 पूर्ण,
	अणु .center_freq = 2467, .hw_value = 12 पूर्ण,
	अणु .center_freq = 2472, .hw_value = 13 पूर्ण,
	अणु .center_freq = 2484, .hw_value = 14 पूर्ण
पूर्ण;

अटल काष्ठा ieee80211_supported_band at76_supported_band = अणु
	.channels = at76_channels,
	.n_channels = ARRAY_SIZE(at76_channels),
	.bitrates = at76_rates,
	.n_bitrates = ARRAY_SIZE(at76_rates),
पूर्ण;

/* Register network device and initialize the hardware */
अटल पूर्णांक at76_init_new_device(काष्ठा at76_priv *priv,
				काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा wiphy *wiphy;
	माप_प्रकार len;
	पूर्णांक ret;

	/* set up the endpoपूर्णांक inक्रमmation */
	/* check out the endpoपूर्णांकs */

	at76_dbg(DBG_DEVSTART, "USB interface: %d endpoints",
		 पूर्णांकerface->cur_altsetting->desc.bNumEndpoपूर्णांकs);

	ret = at76_alloc_urbs(priv, पूर्णांकerface);
	अगर (ret < 0)
		जाओ निकास;

	/* MAC address */
	ret = at76_get_hw_config(priv);
	अगर (ret < 0) अणु
		dev_err(&पूर्णांकerface->dev, "cannot get MAC address\n");
		जाओ निकास;
	पूर्ण

	priv->करोमुख्य = at76_get_reg_करोमुख्य(priv->regulatory_करोमुख्य);

	priv->channel = DEF_CHANNEL;
	priv->iw_mode = IW_MODE_INFRA;
	priv->rts_threshold = DEF_RTS_THRESHOLD;
	priv->frag_threshold = DEF_FRAG_THRESHOLD;
	priv->लघु_retry_limit = DEF_SHORT_RETRY_LIMIT;
	priv->txrate = TX_RATE_AUTO;
	priv->preamble_type = PREAMBLE_TYPE_LONG;
	priv->beacon_period = 100;
	priv->auth_mode = WLAN_AUTH_OPEN;
	priv->scan_min_समय = DEF_SCAN_MIN_TIME;
	priv->scan_max_समय = DEF_SCAN_MAX_TIME;
	priv->scan_mode = SCAN_TYPE_ACTIVE;
	priv->device_unplugged = 0;

	/* mac80211 initialisation */
	wiphy = priv->hw->wiphy;
	priv->hw->wiphy->max_scan_ssids = 1;
	priv->hw->wiphy->max_scan_ie_len = 0;
	priv->hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION);
	priv->hw->wiphy->bands[NL80211_BAND_2GHZ] = &at76_supported_band;
	ieee80211_hw_set(priv->hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(priv->hw, SIGNAL_UNSPEC);
	priv->hw->max_संकेत = 100;

	SET_IEEE80211_DEV(priv->hw, &पूर्णांकerface->dev);
	SET_IEEE80211_PERM_ADDR(priv->hw, priv->mac_addr);

	len = माप(wiphy->fw_version);
	snम_लिखो(wiphy->fw_version, len, "%d.%d.%d-%d",
		 priv->fw_version.major, priv->fw_version.minor,
		 priv->fw_version.patch, priv->fw_version.build);

	wiphy->hw_version = priv->board_type;

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	ret = ieee80211_रेजिस्टर_hw(priv->hw);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "cannot register mac80211 hw (status %d)!\n",
		       ret);
		जाओ निकास;
	पूर्ण

	priv->mac80211_रेजिस्टरed = 1;

	wiphy_info(priv->hw->wiphy, "USB %s, MAC %pM, firmware %d.%d.%d-%d\n",
		   dev_name(&पूर्णांकerface->dev), priv->mac_addr,
		   priv->fw_version.major, priv->fw_version.minor,
		   priv->fw_version.patch, priv->fw_version.build);
	wiphy_info(priv->hw->wiphy, "regulatory domain 0x%02x: %s\n",
		   priv->regulatory_करोमुख्य, priv->करोमुख्य->name);

निकास:
	वापस ret;
पूर्ण

अटल व्योम at76_delete_device(काष्ठा at76_priv *priv)
अणु
	at76_dbg(DBG_PROC_ENTRY, "%s: ENTER", __func__);

	/* The device is gone, करोn't bother turning it off */
	priv->device_unplugged = 1;

	tasklet_समाप्त(&priv->rx_tasklet);

	अगर (priv->mac80211_रेजिस्टरed)
		ieee80211_unरेजिस्टर_hw(priv->hw);

	अगर (priv->tx_urb) अणु
		usb_समाप्त_urb(priv->tx_urb);
		usb_मुक्त_urb(priv->tx_urb);
	पूर्ण
	अगर (priv->rx_urb) अणु
		usb_समाप्त_urb(priv->rx_urb);
		usb_मुक्त_urb(priv->rx_urb);
	पूर्ण

	at76_dbg(DBG_PROC_ENTRY, "%s: unlinked urbs", __func__);

	kमुक्त(priv->bulk_out_buffer);

	del_समयr_sync(&ledtrig_tx_समयr);

	kमुक्त_skb(priv->rx_skb);

	at76_dbg(DBG_PROC_ENTRY, "%s: before freeing priv/ieee80211_hw",
		 __func__);
	ieee80211_मुक्त_hw(priv->hw);

	at76_dbg(DBG_PROC_ENTRY, "%s: EXIT", __func__);
पूर्ण

अटल पूर्णांक at76_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		      स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा at76_priv *priv;
	काष्ठा fwentry *fwe;
	काष्ठा usb_device *udev;
	पूर्णांक op_mode;
	पूर्णांक need_ext_fw = 0;
	काष्ठा mib_fw_version *fwv = शून्य;
	पूर्णांक board_type = (पूर्णांक)id->driver_info;

	udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));

	fwv = kदो_स्मृति(माप(*fwv), GFP_KERNEL);
	अगर (!fwv) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	/* Load firmware पूर्णांकo kernel memory */
	fwe = at76_load_firmware(udev, board_type);
	अगर (!fwe) अणु
		ret = -ENOENT;
		जाओ निकास;
	पूर्ण

	op_mode = at76_get_op_mode(udev);

	at76_dbg(DBG_DEVSTART, "opmode %d", op_mode);

	/* we get OPMODE_NONE with 2.4.23, SMC2662W-AR ???
	   we get 204 with 2.4.23, Fiberline FL-WL240u (505A+RFMD2958) ??? */

	अगर (op_mode == OPMODE_HW_CONFIG_MODE) अणु
		dev_err(&पूर्णांकerface->dev,
			"cannot handle a device in HW_CONFIG_MODE\n");
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	अगर (op_mode != OPMODE_NORMAL_NIC_WITH_FLASH
	    && op_mode != OPMODE_NORMAL_NIC_WITHOUT_FLASH) अणु
		/* करोwnload पूर्णांकernal firmware part */
		dev_prपूर्णांकk(KERN_DEBUG, &पूर्णांकerface->dev,
			   "downloading internal firmware\n");
		ret = at76_load_पूर्णांकernal_fw(udev, fwe);
		अगर (ret < 0) अणु
			dev_err(&पूर्णांकerface->dev,
				"error %d downloading internal firmware\n",
				ret);
		पूर्ण
		जाओ निकास;
	पूर्ण

	/* Internal firmware alपढ़ोy inside the device.  Get firmware
	 * version to test अगर बाह्यal firmware is loaded.
	 * This works only क्रम newer firmware, e.g. the Intersil 0.90.x
	 * says "control timeout on ep0in" and subsequent
	 * at76_get_op_mode() fail too :-( */

	/* अगर version >= 0.100.x.y or device with built-in flash we can
	 * query the device क्रम the fw version */
	अगर ((fwe->fw_version.major > 0 || fwe->fw_version.minor >= 100)
	    || (op_mode == OPMODE_NORMAL_NIC_WITH_FLASH)) अणु
		ret = at76_get_mib(udev, MIB_FW_VERSION, fwv, माप(*fwv));
		अगर (ret < 0 || (fwv->major | fwv->minor) == 0)
			need_ext_fw = 1;
	पूर्ण अन्यथा
		/* No way to check firmware version, reload to be sure */
		need_ext_fw = 1;

	अगर (need_ext_fw) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &पूर्णांकerface->dev,
			   "downloading external firmware\n");

		ret = at76_load_बाह्यal_fw(udev, fwe);
		अगर (ret < 0)
			जाओ निकास;

		/* Re-check firmware version */
		ret = at76_get_mib(udev, MIB_FW_VERSION, fwv, माप(*fwv));
		अगर (ret < 0) अणु
			dev_err(&पूर्णांकerface->dev,
				"error %d getting firmware version\n", ret);
			जाओ निकास;
		पूर्ण
	पूर्ण

	priv = at76_alloc_new_device(udev);
	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकerface, priv);

	स_नकल(&priv->fw_version, fwv, माप(काष्ठा mib_fw_version));
	priv->board_type = board_type;

	ret = at76_init_new_device(priv, पूर्णांकerface);
	अगर (ret < 0)
		at76_delete_device(priv);

निकास:
	kमुक्त(fwv);
	अगर (ret < 0)
		usb_put_dev(udev);
	वापस ret;
पूर्ण

अटल व्योम at76_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा at76_priv *priv;

	priv = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	/* Disconnect after loading पूर्णांकernal firmware */
	अगर (!priv)
		वापस;

	wiphy_info(priv->hw->wiphy, "disconnecting\n");
	at76_delete_device(priv);
	usb_put_dev(priv->udev);
	dev_info(&पूर्णांकerface->dev, "disconnected\n");
पूर्ण

/* Structure क्रम रेजिस्टरing this driver with the USB subप्रणाली */
अटल काष्ठा usb_driver at76_driver = अणु
	.name = DRIVER_NAME,
	.probe = at76_probe,
	.disconnect = at76_disconnect,
	.id_table = dev_table,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

अटल पूर्णांक __init at76_mod_init(व्योम)
अणु
	पूर्णांक result;

	prपूर्णांकk(KERN_INFO DRIVER_DESC " " DRIVER_VERSION " loading\n");

	/* रेजिस्टर this driver with the USB subप्रणाली */
	result = usb_रेजिस्टर(&at76_driver);
	अगर (result < 0)
		prपूर्णांकk(KERN_ERR DRIVER_NAME
		       ": usb_register failed (status %d)\n", result);
	अन्यथा
		led_trigger_रेजिस्टर_simple("at76_usb-tx", &ledtrig_tx);
	वापस result;
पूर्ण

अटल व्योम __निकास at76_mod_निकास(व्योम)
अणु
	पूर्णांक i;

	prपूर्णांकk(KERN_INFO DRIVER_DESC " " DRIVER_VERSION " unloading\n");
	usb_deरेजिस्टर(&at76_driver);
	क्रम (i = 0; i < ARRAY_SIZE(firmwares); i++)
		release_firmware(firmwares[i].fw);
	led_trigger_unरेजिस्टर_simple(ledtrig_tx);
पूर्ण

module_param_named(debug, at76_debug, uपूर्णांक, 0600);
MODULE_PARM_DESC(debug, "Debugging level");

module_init(at76_mod_init);
module_निकास(at76_mod_निकास);

MODULE_AUTHOR("Oliver Kurth <oku@masqmail.cx>");
MODULE_AUTHOR("Joerg Albert <joerg.albert@gmx.de>");
MODULE_AUTHOR("Alex <alex@foogod.com>");
MODULE_AUTHOR("Nick Jones");
MODULE_AUTHOR("Balint Seeber <n0_5p4m_p13453@hotmail.com>");
MODULE_AUTHOR("Pavel Roskin <proski@gnu.org>");
MODULE_AUTHOR("Guido Guenther <agx@sigxcpu.org>");
MODULE_AUTHOR("Kalle Valo <kalle.valo@iki.fi>");
MODULE_AUTHOR("Sebastian Smolorz <sesmo@gmx.net>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
