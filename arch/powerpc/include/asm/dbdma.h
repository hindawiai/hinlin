<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम using the Apple Descriptor-Based DMA controller
 * in Power Macपूर्णांकosh computers.
 *
 * Copyright (C) 1996 Paul Mackerras.
 */

#अगर_घोषित __KERNEL__
#अगर_अघोषित _ASM_DBDMA_H_
#घोषणा _ASM_DBDMA_H_
/*
 * DBDMA control/status रेजिस्टरs.  All little-endian.
 */
काष्ठा dbdma_regs अणु
    अचिन्हित पूर्णांक control;	/* lets you change bits in status */
    अचिन्हित पूर्णांक status;	/* DMA and device status bits (see below) */
    अचिन्हित पूर्णांक cmdptr_hi;	/* upper 32 bits of command address */
    अचिन्हित पूर्णांक cmdptr;	/* (lower 32 bits of) command address (phys) */
    अचिन्हित पूर्णांक पूर्णांकr_sel;	/* select पूर्णांकerrupt condition bit */
    अचिन्हित पूर्णांक br_sel;	/* select branch condition bit */
    अचिन्हित पूर्णांक रुको_sel;	/* select रुको condition bit */
    अचिन्हित पूर्णांक xfer_mode;
    अचिन्हित पूर्णांक data2ptr_hi;
    अचिन्हित पूर्णांक data2ptr;
    अचिन्हित पूर्णांक res1;
    अचिन्हित पूर्णांक address_hi;
    अचिन्हित पूर्णांक br_addr_hi;
    अचिन्हित पूर्णांक res2[3];
पूर्ण;

/* Bits in control and status रेजिस्टरs */
#घोषणा RUN	0x8000
#घोषणा PAUSE	0x4000
#घोषणा FLUSH	0x2000
#घोषणा WAKE	0x1000
#घोषणा DEAD	0x0800
#घोषणा ACTIVE	0x0400
#घोषणा BT	0x0100
#घोषणा DEVSTAT	0x00ff

/*
 * DBDMA command काष्ठाure.  These fields are all little-endian!
 */
काष्ठा dbdma_cmd अणु
	__le16 req_count;	/* requested byte transfer count */
	__le16 command;		/* command word (has bit-fields) */
	__le32 phy_addr;	/* physical data address */
	__le32 cmd_dep;		/* command-dependent field */
	__le16 res_count;	/* residual count after completion */
	__le16 xfer_status;	/* transfer status */
पूर्ण;

/* DBDMA command values in command field */
#घोषणा OUTPUT_MORE	0	/* transfer memory data to stream */
#घोषणा OUTPUT_LAST	0x1000	/* ditto followed by end marker */
#घोषणा INPUT_MORE	0x2000	/* transfer stream data to memory */
#घोषणा INPUT_LAST	0x3000	/* ditto, expect end marker */
#घोषणा STORE_WORD	0x4000	/* ग_लिखो word (4 bytes) to device reg */
#घोषणा LOAD_WORD	0x5000	/* पढ़ो word (4 bytes) from device reg */
#घोषणा DBDMA_NOP	0x6000	/* करो nothing */
#घोषणा DBDMA_STOP	0x7000	/* suspend processing */

/* Key values in command field */
#घोषणा KEY_STREAM0	0	/* usual data stream */
#घोषणा KEY_STREAM1	0x100	/* control/status stream */
#घोषणा KEY_STREAM2	0x200	/* device-dependent stream */
#घोषणा KEY_STREAM3	0x300	/* device-dependent stream */
#घोषणा KEY_REGS	0x500	/* device रेजिस्टर space */
#घोषणा KEY_SYSTEM	0x600	/* प्रणाली memory-mapped space */
#घोषणा KEY_DEVICE	0x700	/* device memory-mapped space */

/* Interrupt control values in command field */
#घोषणा INTR_NEVER	0	/* करोn't पूर्णांकerrupt */
#घोषणा INTR_IFSET	0x10	/* पूर्णांकr अगर condition bit is 1 */
#घोषणा INTR_IFCLR	0x20	/* पूर्णांकr अगर condition bit is 0 */
#घोषणा INTR_ALWAYS	0x30	/* always पूर्णांकerrupt */

/* Branch control values in command field */
#घोषणा BR_NEVER	0	/* करोn't branch */
#घोषणा BR_IFSET	0x4	/* branch अगर condition bit is 1 */
#घोषणा BR_IFCLR	0x8	/* branch अगर condition bit is 0 */
#घोषणा BR_ALWAYS	0xc	/* always branch */

/* Wait control values in command field */
#घोषणा WAIT_NEVER	0	/* करोn't रुको */
#घोषणा WAIT_IFSET	1	/* रुको अगर condition bit is 1 */
#घोषणा WAIT_IFCLR	2	/* रुको अगर condition bit is 0 */
#घोषणा WAIT_ALWAYS	3	/* always रुको */

/* Align an address क्रम a DBDMA command काष्ठाure */
#घोषणा DBDMA_ALIGN(x)	(((अचिन्हित दीर्घ)(x) + माप(काष्ठा dbdma_cmd) - 1) \
			 & -माप(काष्ठा dbdma_cmd))

/* Useful macros */
#घोषणा DBDMA_DO_STOP(regs) करो अणु				\
	out_le32(&((regs)->control), (RUN|FLUSH)<<16);		\
	जबतक(in_le32(&((regs)->status)) & (ACTIVE|FLUSH))	\
		; \
पूर्ण जबतक(0)

#घोषणा DBDMA_DO_RESET(regs) करो अणु				\
	out_le32(&((regs)->control), (ACTIVE|DEAD|WAKE|FLUSH|PAUSE|RUN)<<16);\
	जबतक(in_le32(&((regs)->status)) & (RUN)) \
		; \
पूर्ण जबतक(0)

#पूर्ण_अगर /* _ASM_DBDMA_H_ */
#पूर्ण_अगर /* __KERNEL__ */
