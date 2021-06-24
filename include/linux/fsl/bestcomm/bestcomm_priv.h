<शैली गुरु>
/*
 * Private header क्रम the MPC52xx processor BestComm driver
 *
 * By निजी, we mean that driver should not use it directly. It's meant
 * to be used by the BestComm engine driver itself and by the पूर्णांकermediate
 * layer between the core and the drivers.
 *
 * Copyright (C) 2006      Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2005      Varma Electronics Oy,
 *                         ( by Andrey Volkov <avolkov@varma-el.com> )
 * Copyright (C) 2003-2004 MontaVista, Software, Inc.
 *                         ( by Dale Farnsworth <dfarnsworth@mvista.com> )
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __BESTCOMM_PRIV_H__
#घोषणा __BESTCOMM_PRIV_H__

#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mpc52xx.h>

#समावेश "sram.h"


/* ======================================================================== */
/* Engine related stuff                                                     */
/* ======================================================================== */

/* Zones sizes and needed alignments */
#घोषणा BCOM_MAX_TASKS		16
#घोषणा BCOM_MAX_VAR		24
#घोषणा BCOM_MAX_INC		8
#घोषणा BCOM_MAX_FDT		64
#घोषणा BCOM_MAX_CTX		20
#घोषणा BCOM_CTX_SIZE		(BCOM_MAX_CTX * माप(u32))
#घोषणा BCOM_CTX_ALIGN		0x100
#घोषणा BCOM_VAR_SIZE		(BCOM_MAX_VAR * माप(u32))
#घोषणा BCOM_INC_SIZE		(BCOM_MAX_INC * माप(u32))
#घोषणा BCOM_VAR_ALIGN		0x80
#घोषणा BCOM_FDT_SIZE		(BCOM_MAX_FDT * माप(u32))
#घोषणा BCOM_FDT_ALIGN		0x100

/**
 * काष्ठा bcom_tdt - Task Descriptor Table Entry
 *
 */
काष्ठा bcom_tdt अणु
	u32 start;
	u32 stop;
	u32 var;
	u32 fdt;
	u32 exec_status;	/* used पूर्णांकernally by BestComm engine */
	u32 mvtp;		/* used पूर्णांकernally by BestComm engine */
	u32 context;
	u32 litbase;
पूर्ण;

/**
 * काष्ठा bcom_engine
 *
 * This holds all info needed globaly to handle the engine
 */
काष्ठा bcom_engine अणु
	काष्ठा device_node		*ofnode;
	काष्ठा mpc52xx_sdma __iomem     *regs;
	phys_addr_t                      regs_base;

	काष्ठा bcom_tdt			*tdt;
	u32				*ctx;
	u32				*var;
	u32				*fdt;

	spinlock_t			lock;
पूर्ण;

बाह्य काष्ठा bcom_engine *bcom_eng;


/* ======================================================================== */
/* Tasks related stuff                                                      */
/* ======================================================================== */

/* Tasks image header */
#घोषणा BCOM_TASK_MAGIC		0x4243544B	/* 'BCTK' */

काष्ठा bcom_task_header अणु
	u32	magic;
	u8	desc_size;	/* the size fields     */
	u8	var_size;	/* are given in number */
	u8	inc_size;	/* of 32-bits words    */
	u8	first_var;
	u8	reserved[8];
पूर्ण;

/* Descriptors काष्ठाure & co */
#घोषणा BCOM_DESC_NOP		0x000001f8
#घोषणा BCOM_LCD_MASK		0x80000000
#घोषणा BCOM_DRD_EXTENDED	0x40000000
#घोषणा BCOM_DRD_INITIATOR_SHIFT	21

/* Tasks pragma */
#घोषणा BCOM_PRAGMA_BIT_RSV		7	/* reserved pragma bit */
#घोषणा BCOM_PRAGMA_BIT_PRECISE_INC	6	/* increment 0=when possible, */
						/*           1=iter end */
#घोषणा BCOM_PRAGMA_BIT_RST_ERROR_NO	5	/* करोn't reset errors on */
						/* task enable */
#घोषणा BCOM_PRAGMA_BIT_PACK		4	/* pack data enable */
#घोषणा BCOM_PRAGMA_BIT_INTEGER		3	/* data alignment */
						/* 0=frac(msb), 1=पूर्णांक(lsb) */
#घोषणा BCOM_PRAGMA_BIT_SPECREAD	2	/* XLB speculative पढ़ो */
#घोषणा BCOM_PRAGMA_BIT_CW		1	/* ग_लिखो line buffer enable */
#घोषणा BCOM_PRAGMA_BIT_RL		0	/* पढ़ो line buffer enable */

	/* Looks like XLB speculative पढ़ो generates XLB errors when a buffer
	 * is at the end of the physical memory. i.e. when accessing the
	 * lasts words, the engine tries to prefetch the next but there is no
	 * next ...
	 */
#घोषणा BCOM_STD_PRAGMA		((0 << BCOM_PRAGMA_BIT_RSV)		| \
				 (0 << BCOM_PRAGMA_BIT_PRECISE_INC)	| \
				 (0 << BCOM_PRAGMA_BIT_RST_ERROR_NO)	| \
				 (0 << BCOM_PRAGMA_BIT_PACK)		| \
				 (0 << BCOM_PRAGMA_BIT_INTEGER)		| \
				 (0 << BCOM_PRAGMA_BIT_SPECREAD)	| \
				 (1 << BCOM_PRAGMA_BIT_CW)		| \
				 (1 << BCOM_PRAGMA_BIT_RL))

#घोषणा BCOM_PCI_PRAGMA		((0 << BCOM_PRAGMA_BIT_RSV)		| \
				 (0 << BCOM_PRAGMA_BIT_PRECISE_INC)	| \
				 (0 << BCOM_PRAGMA_BIT_RST_ERROR_NO)	| \
				 (0 << BCOM_PRAGMA_BIT_PACK)		| \
				 (1 << BCOM_PRAGMA_BIT_INTEGER)		| \
				 (0 << BCOM_PRAGMA_BIT_SPECREAD)	| \
				 (1 << BCOM_PRAGMA_BIT_CW)		| \
				 (1 << BCOM_PRAGMA_BIT_RL))

#घोषणा BCOM_ATA_PRAGMA		BCOM_STD_PRAGMA
#घोषणा BCOM_CRC16_DP_0_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_CRC16_DP_1_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_FEC_RX_BD_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_FEC_TX_BD_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_GEN_DP_0_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_GEN_DP_1_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_GEN_DP_2_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_GEN_DP_3_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_GEN_DP_BD_0_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_GEN_DP_BD_1_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_GEN_RX_BD_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_GEN_TX_BD_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_GEN_LPC_PRAGMA	BCOM_STD_PRAGMA
#घोषणा BCOM_PCI_RX_PRAGMA	BCOM_PCI_PRAGMA
#घोषणा BCOM_PCI_TX_PRAGMA	BCOM_PCI_PRAGMA

/* Initiators number */
#घोषणा BCOM_INITIATOR_ALWAYS	 0
#घोषणा BCOM_INITIATOR_SCTMR_0	 1
#घोषणा BCOM_INITIATOR_SCTMR_1	 2
#घोषणा BCOM_INITIATOR_FEC_RX	 3
#घोषणा BCOM_INITIATOR_FEC_TX	 4
#घोषणा BCOM_INITIATOR_ATA_RX	 5
#घोषणा BCOM_INITIATOR_ATA_TX	 6
#घोषणा BCOM_INITIATOR_SCPCI_RX	 7
#घोषणा BCOM_INITIATOR_SCPCI_TX	 8
#घोषणा BCOM_INITIATOR_PSC3_RX	 9
#घोषणा BCOM_INITIATOR_PSC3_TX	10
#घोषणा BCOM_INITIATOR_PSC2_RX	11
#घोषणा BCOM_INITIATOR_PSC2_TX	12
#घोषणा BCOM_INITIATOR_PSC1_RX	13
#घोषणा BCOM_INITIATOR_PSC1_TX	14
#घोषणा BCOM_INITIATOR_SCTMR_2	15
#घोषणा BCOM_INITIATOR_SCLPC	16
#घोषणा BCOM_INITIATOR_PSC5_RX	17
#घोषणा BCOM_INITIATOR_PSC5_TX	18
#घोषणा BCOM_INITIATOR_PSC4_RX	19
#घोषणा BCOM_INITIATOR_PSC4_TX	20
#घोषणा BCOM_INITIATOR_I2C2_RX	21
#घोषणा BCOM_INITIATOR_I2C2_TX	22
#घोषणा BCOM_INITIATOR_I2C1_RX	23
#घोषणा BCOM_INITIATOR_I2C1_TX	24
#घोषणा BCOM_INITIATOR_PSC6_RX	25
#घोषणा BCOM_INITIATOR_PSC6_TX	26
#घोषणा BCOM_INITIATOR_IRDA_RX	25
#घोषणा BCOM_INITIATOR_IRDA_TX	26
#घोषणा BCOM_INITIATOR_SCTMR_3	27
#घोषणा BCOM_INITIATOR_SCTMR_4	28
#घोषणा BCOM_INITIATOR_SCTMR_5	29
#घोषणा BCOM_INITIATOR_SCTMR_6	30
#घोषणा BCOM_INITIATOR_SCTMR_7	31

/* Initiators priorities */
#घोषणा BCOM_IPR_ALWAYS		7
#घोषणा BCOM_IPR_SCTMR_0	2
#घोषणा BCOM_IPR_SCTMR_1	2
#घोषणा BCOM_IPR_FEC_RX		6
#घोषणा BCOM_IPR_FEC_TX		5
#घोषणा BCOM_IPR_ATA_RX		7
#घोषणा BCOM_IPR_ATA_TX		7
#घोषणा BCOM_IPR_SCPCI_RX	2
#घोषणा BCOM_IPR_SCPCI_TX	2
#घोषणा BCOM_IPR_PSC3_RX	2
#घोषणा BCOM_IPR_PSC3_TX	2
#घोषणा BCOM_IPR_PSC2_RX	2
#घोषणा BCOM_IPR_PSC2_TX	2
#घोषणा BCOM_IPR_PSC1_RX	2
#घोषणा BCOM_IPR_PSC1_TX	2
#घोषणा BCOM_IPR_SCTMR_2	2
#घोषणा BCOM_IPR_SCLPC		2
#घोषणा BCOM_IPR_PSC5_RX	2
#घोषणा BCOM_IPR_PSC5_TX	2
#घोषणा BCOM_IPR_PSC4_RX	2
#घोषणा BCOM_IPR_PSC4_TX	2
#घोषणा BCOM_IPR_I2C2_RX	2
#घोषणा BCOM_IPR_I2C2_TX	2
#घोषणा BCOM_IPR_I2C1_RX	2
#घोषणा BCOM_IPR_I2C1_TX	2
#घोषणा BCOM_IPR_PSC6_RX	2
#घोषणा BCOM_IPR_PSC6_TX	2
#घोषणा BCOM_IPR_IRDA_RX	2
#घोषणा BCOM_IPR_IRDA_TX	2
#घोषणा BCOM_IPR_SCTMR_3	2
#घोषणा BCOM_IPR_SCTMR_4	2
#घोषणा BCOM_IPR_SCTMR_5	2
#घोषणा BCOM_IPR_SCTMR_6	2
#घोषणा BCOM_IPR_SCTMR_7	2


/* ======================================================================== */
/* API                                                                      */
/* ======================================================================== */

बाह्य काष्ठा bcom_task *bcom_task_alloc(पूर्णांक bd_count, पूर्णांक bd_size, पूर्णांक priv_size);
बाह्य व्योम bcom_task_मुक्त(काष्ठा bcom_task *tsk);
बाह्य पूर्णांक bcom_load_image(पूर्णांक task, u32 *task_image);
बाह्य व्योम bcom_set_initiator(पूर्णांक task, पूर्णांक initiator);


#घोषणा TASK_ENABLE             0x8000

/**
 * bcom_disable_prefetch - Hook to disable bus prefetching
 *
 * ATA DMA and the original MPC5200 need this due to silicon bugs.  At the
 * moment disabling prefetch is a one-way street.  There is no mechanism
 * in place to turn prefetch back on after it has been disabled.  There is
 * no reason it couldn't be करोne, it would just be more complex to implement.
 */
अटल अंतरभूत व्योम bcom_disable_prefetch(व्योम)
अणु
	u16 regval;

	regval = in_be16(&bcom_eng->regs->PtdCntrl);
	out_be16(&bcom_eng->regs->PtdCntrl, regval | 1);
पूर्ण;

अटल अंतरभूत व्योम
bcom_enable_task(पूर्णांक task)
अणु
        u16 reg;
        reg = in_be16(&bcom_eng->regs->tcr[task]);
        out_be16(&bcom_eng->regs->tcr[task],  reg | TASK_ENABLE);
पूर्ण

अटल अंतरभूत व्योम
bcom_disable_task(पूर्णांक task)
अणु
        u16 reg = in_be16(&bcom_eng->regs->tcr[task]);
        out_be16(&bcom_eng->regs->tcr[task], reg & ~TASK_ENABLE);
पूर्ण


अटल अंतरभूत u32 *
bcom_task_desc(पूर्णांक task)
अणु
	वापस bcom_sram_pa2va(bcom_eng->tdt[task].start);
पूर्ण

अटल अंतरभूत पूर्णांक
bcom_task_num_descs(पूर्णांक task)
अणु
	वापस (bcom_eng->tdt[task].stop - bcom_eng->tdt[task].start)/माप(u32) + 1;
पूर्ण

अटल अंतरभूत u32 *
bcom_task_var(पूर्णांक task)
अणु
	वापस bcom_sram_pa2va(bcom_eng->tdt[task].var);
पूर्ण

अटल अंतरभूत u32 *
bcom_task_inc(पूर्णांक task)
अणु
	वापस &bcom_task_var(task)[BCOM_MAX_VAR];
पूर्ण


अटल अंतरभूत पूर्णांक
bcom_drd_is_extended(u32 desc)
अणु
	वापस (desc) & BCOM_DRD_EXTENDED;
पूर्ण

अटल अंतरभूत पूर्णांक
bcom_desc_is_drd(u32 desc)
अणु
	वापस !(desc & BCOM_LCD_MASK) && desc != BCOM_DESC_NOP;
पूर्ण

अटल अंतरभूत पूर्णांक
bcom_desc_initiator(u32 desc)
अणु
	वापस (desc >> BCOM_DRD_INITIATOR_SHIFT) & 0x1f;
पूर्ण

अटल अंतरभूत व्योम
bcom_set_desc_initiator(u32 *desc, पूर्णांक initiator)
अणु
	*desc = (*desc & ~(0x1f << BCOM_DRD_INITIATOR_SHIFT)) |
			((initiator & 0x1f) << BCOM_DRD_INITIATOR_SHIFT);
पूर्ण


अटल अंतरभूत व्योम
bcom_set_task_pragma(पूर्णांक task, पूर्णांक pragma)
अणु
	u32 *fdt = &bcom_eng->tdt[task].fdt;
	*fdt = (*fdt & ~0xff) | pragma;
पूर्ण

अटल अंतरभूत व्योम
bcom_set_task_स्वतः_start(पूर्णांक task, पूर्णांक next_task)
अणु
	u16 __iomem *tcr = &bcom_eng->regs->tcr[task];
	out_be16(tcr, (in_be16(tcr) & ~0xff) | 0x00c0 | next_task);
पूर्ण

अटल अंतरभूत व्योम
bcom_set_tcr_initiator(पूर्णांक task, पूर्णांक initiator)
अणु
	u16 __iomem *tcr = &bcom_eng->regs->tcr[task];
	out_be16(tcr, (in_be16(tcr) & ~0x1f00) | ((initiator & 0x1f) << 8));
पूर्ण


#पूर्ण_अगर /* __BESTCOMM_PRIV_H__ */

