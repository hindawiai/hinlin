<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file holds Hub protocol स्थिरants and data काष्ठाures that are
 * defined in chapter 11 (Hub Specअगरication) of the USB 2.0 specअगरication.
 *
 * It is used/shared between the USB core, the HCDs and couple of other USB
 * drivers.
 */

#अगर_अघोषित __LINUX_CH11_H
#घोषणा __LINUX_CH11_H

#समावेश <linux/types.h>	/* __u8 etc */

/* This is arbitrary.
 * From USB 2.0 spec Table 11-13, offset 7, a hub can
 * have up to 255 ports. The most yet reported is 10.
 *
 * Current Wireless USB host hardware (Intel i1480 क्रम example) allows
 * up to 22 devices to connect. Upcoming hardware might उठाओ that
 * limit. Because the arrays need to add a bit क्रम hub status data, we
 * use 31, so plus one evens out to four bytes.
 */
#घोषणा USB_MAXCHILDREN		31

/* See USB 3.1 spec Table 10-5 */
#घोषणा USB_SS_MAXPORTS		15

/*
 * Hub request types
 */

#घोषणा USB_RT_HUB	(USB_TYPE_CLASS | USB_RECIP_DEVICE)
#घोषणा USB_RT_PORT	(USB_TYPE_CLASS | USB_RECIP_OTHER)

/*
 * Port status type क्रम GetPortStatus requests added in USB 3.1
 * See USB 3.1 spec Table 10-12
 */
#घोषणा HUB_PORT_STATUS		0
#घोषणा HUB_PORT_PD_STATUS	1
#घोषणा HUB_EXT_PORT_STATUS	2

/*
 * Hub class requests
 * See USB 2.0 spec Table 11-16
 */
#घोषणा HUB_CLEAR_TT_BUFFER	8
#घोषणा HUB_RESET_TT		9
#घोषणा HUB_GET_TT_STATE	10
#घोषणा HUB_STOP_TT		11

/*
 * Hub class additional requests defined by USB 3.0 spec
 * See USB 3.0 spec Table 10-6
 */
#घोषणा HUB_SET_DEPTH		12
#घोषणा HUB_GET_PORT_ERR_COUNT	13

/*
 * Hub Class feature numbers
 * See USB 2.0 spec Table 11-17
 */
#घोषणा C_HUB_LOCAL_POWER	0
#घोषणा C_HUB_OVER_CURRENT	1

/*
 * Port feature numbers
 * See USB 2.0 spec Table 11-17
 */
#घोषणा USB_PORT_FEAT_CONNECTION	0
#घोषणा USB_PORT_FEAT_ENABLE		1
#घोषणा USB_PORT_FEAT_SUSPEND		2	/* L2 suspend */
#घोषणा USB_PORT_FEAT_OVER_CURRENT	3
#घोषणा USB_PORT_FEAT_RESET		4
#घोषणा USB_PORT_FEAT_L1		5	/* L1 suspend */
#घोषणा USB_PORT_FEAT_POWER		8
#घोषणा USB_PORT_FEAT_LOWSPEED		9	/* Should never be used */
#घोषणा USB_PORT_FEAT_C_CONNECTION	16
#घोषणा USB_PORT_FEAT_C_ENABLE		17
#घोषणा USB_PORT_FEAT_C_SUSPEND		18
#घोषणा USB_PORT_FEAT_C_OVER_CURRENT	19
#घोषणा USB_PORT_FEAT_C_RESET		20
#घोषणा USB_PORT_FEAT_TEST              21
#घोषणा USB_PORT_FEAT_INDICATOR         22
#घोषणा USB_PORT_FEAT_C_PORT_L1         23

/*
 * Port feature selectors added by USB 3.0 spec.
 * See USB 3.0 spec Table 10-7
 */
#घोषणा USB_PORT_FEAT_LINK_STATE		5
#घोषणा USB_PORT_FEAT_U1_TIMEOUT		23
#घोषणा USB_PORT_FEAT_U2_TIMEOUT		24
#घोषणा USB_PORT_FEAT_C_PORT_LINK_STATE		25
#घोषणा USB_PORT_FEAT_C_PORT_CONFIG_ERROR	26
#घोषणा USB_PORT_FEAT_REMOTE_WAKE_MASK		27
#घोषणा USB_PORT_FEAT_BH_PORT_RESET		28
#घोषणा USB_PORT_FEAT_C_BH_PORT_RESET		29
#घोषणा USB_PORT_FEAT_FORCE_LINKPM_ACCEPT	30

#घोषणा USB_PORT_LPM_TIMEOUT(p)			(((p) & 0xff) << 8)

/* USB 3.0 hub remote wake mask bits, see table 10-14 */
#घोषणा USB_PORT_FEAT_REMOTE_WAKE_CONNECT	(1 << 8)
#घोषणा USB_PORT_FEAT_REMOTE_WAKE_DISCONNECT	(1 << 9)
#घोषणा USB_PORT_FEAT_REMOTE_WAKE_OVER_CURRENT	(1 << 10)

/*
 * Hub Status and Hub Change results
 * See USB 2.0 spec Table 11-19 and Table 11-20
 * USB 3.1 extends the port status request and may वापस 4 additional bytes.
 * See USB 3.1 spec section 10.16.2.6 Table 10-12 and 10-15
 */
काष्ठा usb_port_status अणु
	__le16 wPortStatus;
	__le16 wPortChange;
	__le32 dwExtPortStatus;
पूर्ण __attribute__ ((packed));

/*
 * wPortStatus bit field
 * See USB 2.0 spec Table 11-21
 */
#घोषणा USB_PORT_STAT_CONNECTION	0x0001
#घोषणा USB_PORT_STAT_ENABLE		0x0002
#घोषणा USB_PORT_STAT_SUSPEND		0x0004
#घोषणा USB_PORT_STAT_OVERCURRENT	0x0008
#घोषणा USB_PORT_STAT_RESET		0x0010
#घोषणा USB_PORT_STAT_L1		0x0020
/* bits 6 to 7 are reserved */
#घोषणा USB_PORT_STAT_POWER		0x0100
#घोषणा USB_PORT_STAT_LOW_SPEED		0x0200
#घोषणा USB_PORT_STAT_HIGH_SPEED        0x0400
#घोषणा USB_PORT_STAT_TEST              0x0800
#घोषणा USB_PORT_STAT_INDICATOR         0x1000
/* bits 13 to 15 are reserved */

/*
 * Additions to wPortStatus bit field from USB 3.0
 * See USB 3.0 spec Table 10-10
 */
#घोषणा USB_PORT_STAT_LINK_STATE	0x01e0
#घोषणा USB_SS_PORT_STAT_POWER		0x0200
#घोषणा USB_SS_PORT_STAT_SPEED		0x1c00
#घोषणा USB_PORT_STAT_SPEED_5GBPS	0x0000
/* Valid only अगर port is enabled */
/* Bits that are the same from USB 2.0 */
#घोषणा USB_SS_PORT_STAT_MASK (USB_PORT_STAT_CONNECTION |	    \
				USB_PORT_STAT_ENABLE |	    \
				USB_PORT_STAT_OVERCURRENT | \
				USB_PORT_STAT_RESET)

/*
 * Definitions क्रम PORT_LINK_STATE values
 * (bits 5-8) in wPortStatus
 */
#घोषणा USB_SS_PORT_LS_U0		0x0000
#घोषणा USB_SS_PORT_LS_U1		0x0020
#घोषणा USB_SS_PORT_LS_U2		0x0040
#घोषणा USB_SS_PORT_LS_U3		0x0060
#घोषणा USB_SS_PORT_LS_SS_DISABLED	0x0080
#घोषणा USB_SS_PORT_LS_RX_DETECT	0x00a0
#घोषणा USB_SS_PORT_LS_SS_INACTIVE	0x00c0
#घोषणा USB_SS_PORT_LS_POLLING		0x00e0
#घोषणा USB_SS_PORT_LS_RECOVERY		0x0100
#घोषणा USB_SS_PORT_LS_HOT_RESET	0x0120
#घोषणा USB_SS_PORT_LS_COMP_MOD		0x0140
#घोषणा USB_SS_PORT_LS_LOOPBACK		0x0160

/*
 * wPortChange bit field
 * See USB 2.0 spec Table 11-22 and USB 2.0 LPM ECN Table-4.10
 * Bits 0 to 5 shown, bits 6 to 15 are reserved
 */
#घोषणा USB_PORT_STAT_C_CONNECTION	0x0001
#घोषणा USB_PORT_STAT_C_ENABLE		0x0002
#घोषणा USB_PORT_STAT_C_SUSPEND		0x0004
#घोषणा USB_PORT_STAT_C_OVERCURRENT	0x0008
#घोषणा USB_PORT_STAT_C_RESET		0x0010
#घोषणा USB_PORT_STAT_C_L1		0x0020
/*
 * USB 3.0 wPortChange bit fields
 * See USB 3.0 spec Table 10-11
 */
#घोषणा USB_PORT_STAT_C_BH_RESET	0x0020
#घोषणा USB_PORT_STAT_C_LINK_STATE	0x0040
#घोषणा USB_PORT_STAT_C_CONFIG_ERROR	0x0080

/*
 * USB 3.1 dwExtPortStatus field masks
 * See USB 3.1 spec 10.16.2.6.3 Table 10-15
 */

#घोषणा USB_EXT_PORT_STAT_RX_SPEED_ID	0x0000000f
#घोषणा USB_EXT_PORT_STAT_TX_SPEED_ID	0x000000f0
#घोषणा USB_EXT_PORT_STAT_RX_LANES	0x00000f00
#घोषणा USB_EXT_PORT_STAT_TX_LANES	0x0000f000

#घोषणा USB_EXT_PORT_RX_LANES(p) \
			(((p) & USB_EXT_PORT_STAT_RX_LANES) >> 8)
#घोषणा USB_EXT_PORT_TX_LANES(p) \
			(((p) & USB_EXT_PORT_STAT_TX_LANES) >> 12)

/*
 * wHubCharacteristics (masks)
 * See USB 2.0 spec Table 11-13, offset 3
 */
#घोषणा HUB_CHAR_LPSM		0x0003 /* Logical Power Switching Mode mask */
#घोषणा HUB_CHAR_COMMON_LPSM	0x0000 /* All ports घातer control at once */
#घोषणा HUB_CHAR_INDV_PORT_LPSM	0x0001 /* per-port घातer control */
#घोषणा HUB_CHAR_NO_LPSM	0x0002 /* no घातer चयनing */

#घोषणा HUB_CHAR_COMPOUND	0x0004 /* hub is part of a compound device */

#घोषणा HUB_CHAR_OCPM		0x0018 /* Over-Current Protection Mode mask */
#घोषणा HUB_CHAR_COMMON_OCPM	0x0000 /* All ports Over-Current reporting */
#घोषणा HUB_CHAR_INDV_PORT_OCPM	0x0008 /* per-port Over-current reporting */
#घोषणा HUB_CHAR_NO_OCPM	0x0010 /* No Over-current Protection support */

#घोषणा HUB_CHAR_TTTT		0x0060 /* TT Think Time mask */
#घोषणा HUB_CHAR_PORTIND	0x0080 /* per-port indicators (LEDs) */

काष्ठा usb_hub_status अणु
	__le16 wHubStatus;
	__le16 wHubChange;
पूर्ण __attribute__ ((packed));

/*
 * Hub Status & Hub Change bit masks
 * See USB 2.0 spec Table 11-19 and Table 11-20
 * Bits 0 and 1 क्रम wHubStatus and wHubChange
 * Bits 2 to 15 are reserved क्रम both
 */
#घोषणा HUB_STATUS_LOCAL_POWER	0x0001
#घोषणा HUB_STATUS_OVERCURRENT	0x0002
#घोषणा HUB_CHANGE_LOCAL_POWER	0x0001
#घोषणा HUB_CHANGE_OVERCURRENT	0x0002


/*
 * Hub descriptor
 * See USB 2.0 spec Table 11-13
 */

#घोषणा USB_DT_HUB			(USB_TYPE_CLASS | 0x09)
#घोषणा USB_DT_SS_HUB			(USB_TYPE_CLASS | 0x0a)
#घोषणा USB_DT_HUB_NONVAR_SIZE		7
#घोषणा USB_DT_SS_HUB_SIZE              12

/*
 * Hub Device descriptor
 * USB Hub class device protocols
 */

#घोषणा USB_HUB_PR_FS		0 /* Full speed hub */
#घोषणा USB_HUB_PR_HS_NO_TT	0 /* Hi-speed hub without TT */
#घोषणा USB_HUB_PR_HS_SINGLE_TT	1 /* Hi-speed hub with single TT */
#घोषणा USB_HUB_PR_HS_MULTI_TT	2 /* Hi-speed hub with multiple TT */
#घोषणा USB_HUB_PR_SS		3 /* Super speed hub */

काष्ठा usb_hub_descriptor अणु
	__u8  bDescLength;
	__u8  bDescriptorType;
	__u8  bNbrPorts;
	__le16 wHubCharacteristics;
	__u8  bPwrOn2PwrGood;
	__u8  bHubContrCurrent;

	/* 2.0 and 3.0 hubs dअगरfer here */
	जोड़ अणु
		काष्ठा अणु
			/* add 1 bit क्रम hub status change; round to bytes */
			__u8  DeviceRemovable[(USB_MAXCHILDREN + 1 + 7) / 8];
			__u8  PortPwrCtrlMask[(USB_MAXCHILDREN + 1 + 7) / 8];
		पूर्ण  __attribute__ ((packed)) hs;

		काष्ठा अणु
			__u8 bHubHdrDecLat;
			__le16 wHubDelay;
			__le16 DeviceRemovable;
		पूर्ण  __attribute__ ((packed)) ss;
	पूर्ण u;
पूर्ण __attribute__ ((packed));

/* port indicator status selectors, tables 11-7 and 11-25 */
#घोषणा HUB_LED_AUTO	0
#घोषणा HUB_LED_AMBER	1
#घोषणा HUB_LED_GREEN	2
#घोषणा HUB_LED_OFF	3

क्रमागत hub_led_mode अणु
	INDICATOR_AUTO = 0,
	INDICATOR_CYCLE,
	/* software blinks क्रम attention:  software, hardware, reserved */
	INDICATOR_GREEN_BLINK, INDICATOR_GREEN_BLINK_OFF,
	INDICATOR_AMBER_BLINK, INDICATOR_AMBER_BLINK_OFF,
	INDICATOR_ALT_BLINK, INDICATOR_ALT_BLINK_OFF
पूर्ण __attribute__ ((packed));

/* Transaction Translator Think Times, in bits */
#घोषणा HUB_TTTT_8_BITS		0x00
#घोषणा HUB_TTTT_16_BITS	0x20
#घोषणा HUB_TTTT_24_BITS	0x40
#घोषणा HUB_TTTT_32_BITS	0x60

#पूर्ण_अगर /* __LINUX_CH11_H */
