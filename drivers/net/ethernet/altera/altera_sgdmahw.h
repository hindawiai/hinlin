<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Altera TSE SGDMA and MSGDMA Linux driver
 * Copyright (C) 2014 Altera Corporation. All rights reserved
 */

#अगर_अघोषित __ALTERA_SGDMAHW_H__
#घोषणा __ALTERA_SGDMAHW_H__

/* SGDMA descriptor काष्ठाure */
काष्ठा sgdma_descrip अणु
	u32	raddr; /* address of data to be पढ़ो */
	u32	pad1;
	u32	waddr;
	u32	pad2;
	u32	next;
	u32	pad3;
	u16	bytes;
	u8	rburst;
	u8	wburst;
	u16	bytes_xferred;	/* 16 bits, bytes xferred */

	/* bit 0: error
	 * bit 1: length error
	 * bit 2: crc error
	 * bit 3: truncated error
	 * bit 4: phy error
	 * bit 5: collision error
	 * bit 6: reserved
	 * bit 7: status eop क्रम recv हाल
	 */
	u8	status;

	/* bit 0: eop
	 * bit 1: पढ़ो_fixed
	 * bit 2: ग_लिखो fixed
	 * bits 3,4,5,6: Channel (always 0)
	 * bit 7: hardware owned
	 */
	u8	control;
पूर्ण __packed;

#घोषणा SGDMA_DESC_LEN	माप(काष्ठा sgdma_descrip)

#घोषणा SGDMA_STATUS_ERR		BIT(0)
#घोषणा SGDMA_STATUS_LENGTH_ERR		BIT(1)
#घोषणा SGDMA_STATUS_CRC_ERR		BIT(2)
#घोषणा SGDMA_STATUS_TRUNC_ERR		BIT(3)
#घोषणा SGDMA_STATUS_PHY_ERR		BIT(4)
#घोषणा SGDMA_STATUS_COLL_ERR		BIT(5)
#घोषणा SGDMA_STATUS_EOP		BIT(7)

#घोषणा SGDMA_CONTROL_EOP		BIT(0)
#घोषणा SGDMA_CONTROL_RD_FIXED		BIT(1)
#घोषणा SGDMA_CONTROL_WR_FIXED		BIT(2)

/* Channel is always 0, so just zero initialize it */

#घोषणा SGDMA_CONTROL_HW_OWNED		BIT(7)

/* SGDMA रेजिस्टर space */
काष्ठा sgdma_csr अणु
	/* bit 0: error
	 * bit 1: eop
	 * bit 2: descriptor completed
	 * bit 3: chain completed
	 * bit 4: busy
	 * reमुख्यder reserved
	 */
	u32	status;
	u32	pad1[3];

	/* bit 0: पूर्णांकerrupt on error
	 * bit 1: पूर्णांकerrupt on eop
	 * bit 2: पूर्णांकerrupt after every descriptor
	 * bit 3: पूर्णांकerrupt after last descrip in a chain
	 * bit 4: global पूर्णांकerrupt enable
	 * bit 5: starts descriptor processing
	 * bit 6: stop core on dma error
	 * bit 7: पूर्णांकerrupt on max descriptors
	 * bits 8-15: max descriptors to generate पूर्णांकerrupt
	 * bit 16: Software reset
	 * bit 17: clears owned by hardware अगर 0, करोes not clear otherwise
	 * bit 18: enables descriptor polling mode
	 * bit 19-26: घड़ीs beक्रमe polling again
	 * bit 27-30: reserved
	 * bit 31: clear पूर्णांकerrupt
	 */
	u32	control;
	u32	pad2[3];
	u32	next_descrip;
	u32	pad3[3];
पूर्ण;

#घोषणा sgdma_csroffs(a) (दुरत्व(काष्ठा sgdma_csr, a))
#घोषणा sgdma_descroffs(a) (दुरत्व(काष्ठा sgdma_descrip, a))

#घोषणा SGDMA_STSREG_ERR	BIT(0) /* Error */
#घोषणा SGDMA_STSREG_EOP	BIT(1) /* EOP */
#घोषणा SGDMA_STSREG_DESCRIP	BIT(2) /* Descriptor completed */
#घोषणा SGDMA_STSREG_CHAIN	BIT(3) /* Chain completed */
#घोषणा SGDMA_STSREG_BUSY	BIT(4) /* Controller busy */

#घोषणा SGDMA_CTRLREG_IOE	BIT(0) /* Interrupt on error */
#घोषणा SGDMA_CTRLREG_IOEOP	BIT(1) /* Interrupt on EOP */
#घोषणा SGDMA_CTRLREG_IDESCRIP	BIT(2) /* Interrupt after every descriptor */
#घोषणा SGDMA_CTRLREG_ILASTD	BIT(3) /* Interrupt after last descriptor */
#घोषणा SGDMA_CTRLREG_INTEN	BIT(4) /* Global Interrupt enable */
#घोषणा SGDMA_CTRLREG_START	BIT(5) /* starts descriptor processing */
#घोषणा SGDMA_CTRLREG_STOPERR	BIT(6) /* stop on dma error */
#घोषणा SGDMA_CTRLREG_INTMAX	BIT(7) /* Interrupt on max descriptors */
#घोषणा SGDMA_CTRLREG_RESET	BIT(16)/* Software reset */
#घोषणा SGDMA_CTRLREG_COBHW	BIT(17)/* Clears owned by hardware */
#घोषणा SGDMA_CTRLREG_POLL	BIT(18)/* enables descriptor polling mode */
#घोषणा SGDMA_CTRLREG_CLRINT	BIT(31)/* Clears पूर्णांकerrupt */

#पूर्ण_अगर /* __ALTERA_SGDMAHW_H__ */
