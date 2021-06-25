<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * USB IrDA Bridge Device Definition
 */

#अगर_अघोषित __LINUX_USB_IRDA_H
#घोषणा __LINUX_USB_IRDA_H

/* This device should use Application-specअगरic class */

#घोषणा USB_SUBCLASS_IRDA			0x02

/*-------------------------------------------------------------------------*/

/* Class-Specअगरic requests (bRequest field) */

#घोषणा USB_REQ_CS_IRDA_RECEIVING		1
#घोषणा USB_REQ_CS_IRDA_CHECK_MEDIA_BUSY	3
#घोषणा USB_REQ_CS_IRDA_RATE_SNIFF		4
#घोषणा USB_REQ_CS_IRDA_UNICAST_LIST		5
#घोषणा USB_REQ_CS_IRDA_GET_CLASS_DESC		6

/*-------------------------------------------------------------------------*/

/* Class-Specअगरic descriptor */

#घोषणा USB_DT_CS_IRDA				0x21

/*-------------------------------------------------------------------------*/

/* Data sizes */

#घोषणा USB_IRDA_DS_2048			(1 << 5)
#घोषणा USB_IRDA_DS_1024			(1 << 4)
#घोषणा USB_IRDA_DS_512				(1 << 3)
#घोषणा USB_IRDA_DS_256				(1 << 2)
#घोषणा USB_IRDA_DS_128				(1 << 1)
#घोषणा USB_IRDA_DS_64				(1 << 0)

/* Winकरोw sizes */

#घोषणा USB_IRDA_WS_7				(1 << 6)
#घोषणा USB_IRDA_WS_6				(1 << 5)
#घोषणा USB_IRDA_WS_5				(1 << 4)
#घोषणा USB_IRDA_WS_4				(1 << 3)
#घोषणा USB_IRDA_WS_3				(1 << 2)
#घोषणा USB_IRDA_WS_2				(1 << 1)
#घोषणा USB_IRDA_WS_1				(1 << 0)

/* Min turnaround बार in usecs */

#घोषणा USB_IRDA_MTT_0				(1 << 7)
#घोषणा USB_IRDA_MTT_10				(1 << 6)
#घोषणा USB_IRDA_MTT_50				(1 << 5)
#घोषणा USB_IRDA_MTT_100			(1 << 4)
#घोषणा USB_IRDA_MTT_500			(1 << 3)
#घोषणा USB_IRDA_MTT_1000			(1 << 2)
#घोषणा USB_IRDA_MTT_5000			(1 << 1)
#घोषणा USB_IRDA_MTT_10000			(1 << 0)

/* Baud rates */

#घोषणा USB_IRDA_BR_4000000			(1 << 8)
#घोषणा USB_IRDA_BR_1152000			(1 << 7)
#घोषणा USB_IRDA_BR_576000			(1 << 6)
#घोषणा USB_IRDA_BR_115200			(1 << 5)
#घोषणा USB_IRDA_BR_57600			(1 << 4)
#घोषणा USB_IRDA_BR_38400			(1 << 3)
#घोषणा USB_IRDA_BR_19200			(1 << 2)
#घोषणा USB_IRDA_BR_9600			(1 << 1)
#घोषणा USB_IRDA_BR_2400			(1 << 0)

/* Additional BOFs */

#घोषणा USB_IRDA_AB_0				(1 << 7)
#घोषणा USB_IRDA_AB_1				(1 << 6)
#घोषणा USB_IRDA_AB_2				(1 << 5)
#घोषणा USB_IRDA_AB_3				(1 << 4)
#घोषणा USB_IRDA_AB_6				(1 << 3)
#घोषणा USB_IRDA_AB_12				(1 << 2)
#घोषणा USB_IRDA_AB_24				(1 << 1)
#घोषणा USB_IRDA_AB_48				(1 << 0)

/* IRDA Rate Snअगरf */

#घोषणा USB_IRDA_RATE_SNIFF			1

/*-------------------------------------------------------------------------*/

काष्ठा usb_irda_cs_descriptor अणु
	__u8	bLength;
	__u8	bDescriptorType;

	__le16	bcdSpecRevision;
	__u8	bmDataSize;
	__u8	bmWinकरोwSize;
	__u8	bmMinTurnaroundTime;
	__le16	wBaudRate;
	__u8	bmAdditionalBOFs;
	__u8	bIrdaRateSnअगरf;
	__u8	bMaxUnicastList;
पूर्ण __attribute__ ((packed));

/*-------------------------------------------------------------------------*/

/* Data Format */

#घोषणा USB_IRDA_STATUS_MEDIA_BUSY	(1 << 7)

/* The following is a 4-bit value used क्रम both
 * inbound and outbound headers:
 *
 * 0 - speed ignored
 * 1 - 2400 bps
 * 2 - 9600 bps
 * 3 - 19200 bps
 * 4 - 38400 bps
 * 5 - 57600 bps
 * 6 - 115200 bps
 * 7 - 576000 bps
 * 8 - 1.152 Mbps
 * 9 - 4 Mbps
 * 10..15 - Reserved
 */
#घोषणा USB_IRDA_STATUS_LINK_SPEED	0x0f

#घोषणा USB_IRDA_LS_NO_CHANGE		0
#घोषणा USB_IRDA_LS_2400		1
#घोषणा USB_IRDA_LS_9600		2
#घोषणा USB_IRDA_LS_19200		3
#घोषणा USB_IRDA_LS_38400		4
#घोषणा USB_IRDA_LS_57600		5
#घोषणा USB_IRDA_LS_115200		6
#घोषणा USB_IRDA_LS_576000		7
#घोषणा USB_IRDA_LS_1152000		8
#घोषणा USB_IRDA_LS_4000000		9

/* The following is a 4-bit value used only क्रम
 * outbound header:
 *
 * 0 - No change (BOF ignored)
 * 1 - 48 BOFs
 * 2 - 24 BOFs
 * 3 - 12 BOFs
 * 4 - 6 BOFs
 * 5 - 3 BOFs
 * 6 - 2 BOFs
 * 7 - 1 BOFs
 * 8 - 0 BOFs
 * 9..15 - Reserved
 */
#घोषणा USB_IRDA_EXTRA_BOFS		0xf0

काष्ठा usb_irda_inbound_header अणु
	__u8		bmStatus;
पूर्ण;

काष्ठा usb_irda_outbound_header अणु
	__u8		bmChange;
पूर्ण;

#पूर्ण_अगर /* __LINUX_USB_IRDA_H */

