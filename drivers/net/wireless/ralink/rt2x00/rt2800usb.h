<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2009 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2009 Mattias Nissler <mattias.nissler@gmx.de>
	Copyright (C) 2009 Felix Fietkau <nbd@खोलोwrt.org>
	Copyright (C) 2009 Xose Vazquez Perez <xose.vazquez@gmail.com>
	Copyright (C) 2009 Axel Kollhofer <rain_maker@root-क्रमum.org>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2800usb
	Abstract: Data काष्ठाures and रेजिस्टरs क्रम the rt2800usb module.
	Supported chipsets: RT2800U.
 */

#अगर_अघोषित RT2800USB_H
#घोषणा RT2800USB_H

/*
 * 8051 firmware image.
 */
#घोषणा FIRMWARE_RT2870			"rt2870.bin"
#घोषणा FIRMWARE_IMAGE_BASE		0x3000

/*
 * DMA descriptor defines.
 */
#घोषणा TXINFO_DESC_SIZE		(1 * माप(__le32))
#घोषणा RXINFO_DESC_SIZE		(1 * माप(__le32))

/*
 * TX Info काष्ठाure
 */

/*
 * Word0
 * WIV: Wireless Info Valid. 1: Driver filled WI,  0: DMA needs to copy WI
 * QSEL: Select on-chip FIFO ID क्रम 2nd-stage output scheduler.
 *       0:MGMT, 1:HCCA 2:EDCA
 * USB_DMA_NEXT_VALID: Used ONLY in USB bulk Aggregation, NextValid
 * DMA_TX_BURST: used ONLY in USB bulk Aggregation.
 *               Force USB DMA transmit frame from current selected endpoपूर्णांक
 */
#घोषणा TXINFO_W0_USB_DMA_TX_PKT_LEN	FIELD32(0x0000ffff)
#घोषणा TXINFO_W0_WIV			FIELD32(0x01000000)
#घोषणा TXINFO_W0_QSEL			FIELD32(0x06000000)
#घोषणा TXINFO_W0_SW_USE_LAST_ROUND	FIELD32(0x08000000)
#घोषणा TXINFO_W0_USB_DMA_NEXT_VALID	FIELD32(0x40000000)
#घोषणा TXINFO_W0_USB_DMA_TX_BURST	FIELD32(0x80000000)

/*
 * RX Info काष्ठाure
 */

/*
 * Word 0
 */

#घोषणा RXINFO_W0_USB_DMA_RX_PKT_LEN	FIELD32(0x0000ffff)

/*
 * RX descriptor क्रमmat क्रम RX Ring.
 */

/*
 * Word0
 * UNICAST_TO_ME: This RX frame is unicast to me.
 * MULTICAST: This is a multicast frame.
 * BROADCAST: This is a broadcast frame.
 * MY_BSS: this frame beदीर्घs to the same BSSID.
 * CRC_ERROR: CRC error.
 * CIPHER_ERROR: 0: decryption okay, 1:ICV error, 2:MIC error, 3:KEY not valid.
 * AMSDU: rx with 802.3 header, not 802.11 header.
 */

#घोषणा RXD_W0_BA			FIELD32(0x00000001)
#घोषणा RXD_W0_DATA			FIELD32(0x00000002)
#घोषणा RXD_W0_शून्यDATA			FIELD32(0x00000004)
#घोषणा RXD_W0_FRAG			FIELD32(0x00000008)
#घोषणा RXD_W0_UNICAST_TO_ME		FIELD32(0x00000010)
#घोषणा RXD_W0_MULTICAST		FIELD32(0x00000020)
#घोषणा RXD_W0_BROADCAST		FIELD32(0x00000040)
#घोषणा RXD_W0_MY_BSS			FIELD32(0x00000080)
#घोषणा RXD_W0_CRC_ERROR		FIELD32(0x00000100)
#घोषणा RXD_W0_CIPHER_ERROR		FIELD32(0x00000600)
#घोषणा RXD_W0_AMSDU			FIELD32(0x00000800)
#घोषणा RXD_W0_HTC			FIELD32(0x00001000)
#घोषणा RXD_W0_RSSI			FIELD32(0x00002000)
#घोषणा RXD_W0_L2PAD			FIELD32(0x00004000)
#घोषणा RXD_W0_AMPDU			FIELD32(0x00008000)
#घोषणा RXD_W0_DECRYPTED		FIELD32(0x00010000)
#घोषणा RXD_W0_PLCP_RSSI		FIELD32(0x00020000)
#घोषणा RXD_W0_CIPHER_ALG		FIELD32(0x00040000)
#घोषणा RXD_W0_LAST_AMSDU		FIELD32(0x00080000)
#घोषणा RXD_W0_PLCP_SIGNAL		FIELD32(0xfff00000)

#पूर्ण_अगर /* RT2800USB_H */
