<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wanXL serial card driver क्रम Linux
 * definitions common to host driver and card firmware
 *
 * Copyright (C) 2003 Krzysztof Halasa <khc@pm.waw.pl>
 */

#घोषणा RESET_WHILE_LOADING 0

/* you must rebuild the firmware अगर any of the following is changed */
#घोषणा DETECT_RAM 0		/* needed क्रम > 4MB RAM, 16 MB maximum */
#घोषणा QUICC_MEMCPY_USES_PLX 1	/* must be used अगर the host has > 256 MB RAM */


#घोषणा STATUS_CABLE_V35	2
#घोषणा STATUS_CABLE_X21	3
#घोषणा STATUS_CABLE_V24	4
#घोषणा STATUS_CABLE_EIA530	5
#घोषणा STATUS_CABLE_INVALID	6
#घोषणा STATUS_CABLE_NONE	7

#घोषणा STATUS_CABLE_DCE	0x8000
#घोषणा STATUS_CABLE_DSR	0x0010
#घोषणा STATUS_CABLE_DCD	0x0008
#घोषणा STATUS_CABLE_PM_SHIFT	5

#घोषणा PDM_OFFSET 0x1000

#घोषणा TX_BUFFERS 10		/* per port */
#घोषणा RX_BUFFERS 30
#घोषणा RX_QUEUE_LENGTH 40	/* card->host queue length - per card */

#घोषणा PACKET_EMPTY		0x00
#घोषणा PACKET_FULL		0x10
#घोषणा PACKET_SENT		0x20 /* TX only */
#घोषणा PACKET_UNDERRUN		0x30 /* TX only */
#घोषणा PACKET_PORT_MASK	0x03 /* RX only */

/* bit numbers in PLX9060 करोorbell रेजिस्टरs */
#घोषणा DOORBELL_FROM_CARD_TX_0		0 /* packet sent by the card */
#घोषणा DOORBELL_FROM_CARD_TX_1		1
#घोषणा DOORBELL_FROM_CARD_TX_2		2
#घोषणा DOORBELL_FROM_CARD_TX_3		3
#घोषणा DOORBELL_FROM_CARD_RX		4
#घोषणा DOORBELL_FROM_CARD_CABLE_0	5 /* cable/PM/etc. changed */
#घोषणा DOORBELL_FROM_CARD_CABLE_1	6
#घोषणा DOORBELL_FROM_CARD_CABLE_2	7
#घोषणा DOORBELL_FROM_CARD_CABLE_3	8

#घोषणा DOORBELL_TO_CARD_OPEN_0		0
#घोषणा DOORBELL_TO_CARD_OPEN_1		1
#घोषणा DOORBELL_TO_CARD_OPEN_2		2
#घोषणा DOORBELL_TO_CARD_OPEN_3		3
#घोषणा DOORBELL_TO_CARD_CLOSE_0	4
#घोषणा DOORBELL_TO_CARD_CLOSE_1	5
#घोषणा DOORBELL_TO_CARD_CLOSE_2	6
#घोषणा DOORBELL_TO_CARD_CLOSE_3	7
#घोषणा DOORBELL_TO_CARD_TX_0		8 /* outbound packet queued */
#घोषणा DOORBELL_TO_CARD_TX_1		9
#घोषणा DOORBELL_TO_CARD_TX_2		10
#घोषणा DOORBELL_TO_CARD_TX_3		11

/* firmware-only status bits, starting from last DOORBELL_TO_CARD + 1 */
#घोषणा TASK_SCC_0			12
#घोषणा TASK_SCC_1			13
#घोषणा TASK_SCC_2			14
#घोषणा TASK_SCC_3			15

#घोषणा ALIGN32(x) (((x) + 3) & 0xFFFFFFFC)
#घोषणा BUFFER_LENGTH	ALIGN32(HDLC_MAX_MRU + 4) /* 4 bytes क्रम 32-bit CRC */

/* Address of TX and RX buffers in 68360 address space */
#घोषणा BUFFERS_ADDR	0x4000	/* 16 KB */

#अगर_अघोषित __ASSEMBLER__
#घोषणा PLX_OFFSET		0
#अन्यथा
#घोषणा PLX_OFFSET		PLX + 0x80
#पूर्ण_अगर

#घोषणा PLX_MAILBOX_0		(PLX_OFFSET + 0x40)
#घोषणा PLX_MAILBOX_1		(PLX_OFFSET + 0x44)
#घोषणा PLX_MAILBOX_2		(PLX_OFFSET + 0x48)
#घोषणा PLX_MAILBOX_3		(PLX_OFFSET + 0x4C)
#घोषणा PLX_MAILBOX_4		(PLX_OFFSET + 0x50)
#घोषणा PLX_MAILBOX_5		(PLX_OFFSET + 0x54)
#घोषणा PLX_MAILBOX_6		(PLX_OFFSET + 0x58)
#घोषणा PLX_MAILBOX_7		(PLX_OFFSET + 0x5C)
#घोषणा PLX_DOORBELL_TO_CARD	(PLX_OFFSET + 0x60)
#घोषणा PLX_DOORBELL_FROM_CARD	(PLX_OFFSET + 0x64)
#घोषणा PLX_INTERRUPT_CS	(PLX_OFFSET + 0x68)
#घोषणा PLX_CONTROL		(PLX_OFFSET + 0x6C)

#अगर_घोषित __ASSEMBLER__
#घोषणा PLX_DMA_0_MODE		(PLX + 0x100)
#घोषणा PLX_DMA_0_PCI		(PLX + 0x104)
#घोषणा PLX_DMA_0_LOCAL		(PLX + 0x108)
#घोषणा PLX_DMA_0_LENGTH	(PLX + 0x10C)
#घोषणा PLX_DMA_0_DESC		(PLX + 0x110)
#घोषणा PLX_DMA_1_MODE		(PLX + 0x114)
#घोषणा PLX_DMA_1_PCI		(PLX + 0x118)
#घोषणा PLX_DMA_1_LOCAL		(PLX + 0x11C)
#घोषणा PLX_DMA_1_LENGTH	(PLX + 0x120)
#घोषणा PLX_DMA_1_DESC		(PLX + 0x124)
#घोषणा PLX_DMA_CMD_STS		(PLX + 0x128)
#घोषणा PLX_DMA_ARBITR_0	(PLX + 0x12C)
#घोषणा PLX_DMA_ARBITR_1	(PLX + 0x130)
#पूर्ण_अगर

#घोषणा DESC_LENGTH 12

/* offsets from start of status_t */
/* card to host */
#घोषणा STATUS_OPEN		0
#घोषणा STATUS_CABLE		(STATUS_OPEN + 4)
#घोषणा STATUS_RX_OVERRUNS	(STATUS_CABLE + 4)
#घोषणा STATUS_RX_FRAME_ERRORS	(STATUS_RX_OVERRUNS + 4)

/* host to card */
#घोषणा STATUS_PARITY		(STATUS_RX_FRAME_ERRORS + 4)
#घोषणा STATUS_ENCODING		(STATUS_PARITY + 4)
#घोषणा STATUS_CLOCKING		(STATUS_ENCODING + 4)
#घोषणा STATUS_TX_DESCS		(STATUS_CLOCKING + 4)

#अगर_अघोषित __ASSEMBLER__

प्रकार काष्ठा अणु
	अस्थिर u32 stat;
	u32 address;		/* PCI address */
	अस्थिर u32 length;
पूर्णdesc_t;


प्रकार काष्ठा अणु
// Card to host
	अस्थिर u32 खोलो;
	अस्थिर u32 cable;
	अस्थिर u32 rx_overruns;
	अस्थिर u32 rx_frame_errors;

// Host to card
	u32 parity;
	u32 encoding;
	u32 घड़ीing;
	desc_t tx_descs[TX_BUFFERS];
पूर्णport_status_t;

#पूर्ण_अगर /* __ASSEMBLER__ */
