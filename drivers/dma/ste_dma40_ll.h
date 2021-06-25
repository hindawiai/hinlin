<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2007-2010
 * Author: Per Friden <per.friden@stericsson.com> क्रम ST-Ericsson SA
 * Author: Jonas Aaberg <jonas.aberg@stericsson.com> क्रम ST-Ericsson SA
 */
#अगर_अघोषित STE_DMA40_LL_H
#घोषणा STE_DMA40_LL_H

#घोषणा D40_DREG_PCBASE		0x400
#घोषणा D40_DREG_PCDELTA	(8 * 4)
#घोषणा D40_LLI_ALIGN		16 /* LLI alignment must be 16 bytes. */

#घोषणा D40_LCPA_CHAN_SIZE 32
#घोषणा D40_LCPA_CHAN_DST_DELTA 16

#घोषणा D40_TYPE_TO_GROUP(type) (type / 16)
#घोषणा D40_TYPE_TO_EVENT(type) (type % 16)
#घोषणा D40_GROUP_SIZE 8
#घोषणा D40_PHYS_TO_GROUP(phys) ((phys & (D40_GROUP_SIZE - 1)) / 2)

/* Most bits of the CFG रेजिस्टर are the same in log as in phy mode */
#घोषणा D40_SREG_CFG_MST_POS		15
#घोषणा D40_SREG_CFG_TIM_POS		14
#घोषणा D40_SREG_CFG_EIM_POS		13
#घोषणा D40_SREG_CFG_LOG_INCR_POS	12
#घोषणा D40_SREG_CFG_PHY_PEN_POS	12
#घोषणा D40_SREG_CFG_PSIZE_POS		10
#घोषणा D40_SREG_CFG_ESIZE_POS		 8
#घोषणा D40_SREG_CFG_PRI_POS		 7
#घोषणा D40_SREG_CFG_LBE_POS		 6
#घोषणा D40_SREG_CFG_LOG_GIM_POS	 5
#घोषणा D40_SREG_CFG_LOG_MFU_POS	 4
#घोषणा D40_SREG_CFG_PHY_TM_POS		 4
#घोषणा D40_SREG_CFG_PHY_EVTL_POS	 0


/* Standard channel parameters - basic mode (element रेजिस्टर) */
#घोषणा D40_SREG_ELEM_PHY_ECNT_POS	16
#घोषणा D40_SREG_ELEM_PHY_EIDX_POS	 0

#घोषणा D40_SREG_ELEM_PHY_ECNT_MASK	(0xFFFF << D40_SREG_ELEM_PHY_ECNT_POS)

/* Standard channel parameters - basic mode (Link रेजिस्टर) */
#घोषणा D40_SREG_LNK_PHY_TCP_POS	0
#घोषणा D40_SREG_LNK_PHY_LMP_POS	1
#घोषणा D40_SREG_LNK_PHY_PRE_POS	2
/*
 * Source  destination link address. Contains the
 * 29-bit byte word aligned address of the reload area.
 */
#घोषणा D40_SREG_LNK_PHYS_LNK_MASK	0xFFFFFFF8UL

/* Standard basic channel logical mode */

/* Element रेजिस्टर */
#घोषणा D40_SREG_ELEM_LOG_ECNT_POS	16
#घोषणा D40_SREG_ELEM_LOG_LIDX_POS	 8
#घोषणा D40_SREG_ELEM_LOG_LOS_POS	 1
#घोषणा D40_SREG_ELEM_LOG_TCP_POS	 0

#घोषणा D40_SREG_ELEM_LOG_LIDX_MASK	(0xFF << D40_SREG_ELEM_LOG_LIDX_POS)

/* Link रेजिस्टर */
#घोषणा D40_EVENTLINE_POS(i)		(2 * i)
#घोषणा D40_EVENTLINE_MASK(i)		(0x3 << D40_EVENTLINE_POS(i))

/* Standard basic channel logical params in memory */

/* LCSP0 */
#घोषणा D40_MEM_LCSP0_ECNT_POS		16
#घोषणा D40_MEM_LCSP0_SPTR_POS		 0

#घोषणा D40_MEM_LCSP0_ECNT_MASK		(0xFFFF << D40_MEM_LCSP0_ECNT_POS)
#घोषणा D40_MEM_LCSP0_SPTR_MASK		(0xFFFF << D40_MEM_LCSP0_SPTR_POS)

/* LCSP1 */
#घोषणा D40_MEM_LCSP1_SPTR_POS		16
#घोषणा D40_MEM_LCSP1_SCFG_MST_POS	15
#घोषणा D40_MEM_LCSP1_SCFG_TIM_POS	14
#घोषणा D40_MEM_LCSP1_SCFG_EIM_POS	13
#घोषणा D40_MEM_LCSP1_SCFG_INCR_POS	12
#घोषणा D40_MEM_LCSP1_SCFG_PSIZE_POS	10
#घोषणा D40_MEM_LCSP1_SCFG_ESIZE_POS	 8
#घोषणा D40_MEM_LCSP1_SLOS_POS		 1
#घोषणा D40_MEM_LCSP1_STCP_POS		 0

#घोषणा D40_MEM_LCSP1_SPTR_MASK		(0xFFFF << D40_MEM_LCSP1_SPTR_POS)
#घोषणा D40_MEM_LCSP1_SCFG_TIM_MASK	(0x1 << D40_MEM_LCSP1_SCFG_TIM_POS)
#घोषणा D40_MEM_LCSP1_SCFG_INCR_MASK	(0x1 << D40_MEM_LCSP1_SCFG_INCR_POS)
#घोषणा D40_MEM_LCSP1_SCFG_PSIZE_MASK	(0x3 << D40_MEM_LCSP1_SCFG_PSIZE_POS)
#घोषणा D40_MEM_LCSP1_SLOS_MASK		(0x7F << D40_MEM_LCSP1_SLOS_POS)
#घोषणा D40_MEM_LCSP1_STCP_MASK		(0x1 << D40_MEM_LCSP1_STCP_POS)

/* LCSP2 */
#घोषणा D40_MEM_LCSP2_ECNT_POS		16

#घोषणा D40_MEM_LCSP2_ECNT_MASK		(0xFFFF << D40_MEM_LCSP2_ECNT_POS)

/* LCSP3 */
#घोषणा D40_MEM_LCSP3_DCFG_MST_POS	15
#घोषणा D40_MEM_LCSP3_DCFG_TIM_POS	14
#घोषणा D40_MEM_LCSP3_DCFG_EIM_POS	13
#घोषणा D40_MEM_LCSP3_DCFG_INCR_POS	12
#घोषणा D40_MEM_LCSP3_DCFG_PSIZE_POS	10
#घोषणा D40_MEM_LCSP3_DCFG_ESIZE_POS	 8
#घोषणा D40_MEM_LCSP3_DLOS_POS		 1
#घोषणा D40_MEM_LCSP3_DTCP_POS		 0

#घोषणा D40_MEM_LCSP3_DLOS_MASK		(0x7F << D40_MEM_LCSP3_DLOS_POS)
#घोषणा D40_MEM_LCSP3_DTCP_MASK		(0x1 << D40_MEM_LCSP3_DTCP_POS)


/* Standard channel parameter रेजिस्टर offsets */
#घोषणा D40_CHAN_REG_SSCFG	0x00
#घोषणा D40_CHAN_REG_SSELT	0x04
#घोषणा D40_CHAN_REG_SSPTR	0x08
#घोषणा D40_CHAN_REG_SSLNK	0x0C
#घोषणा D40_CHAN_REG_SDCFG	0x10
#घोषणा D40_CHAN_REG_SDELT	0x14
#घोषणा D40_CHAN_REG_SDPTR	0x18
#घोषणा D40_CHAN_REG_SDLNK	0x1C

/* DMA Register Offsets */
#घोषणा D40_DREG_GCC		0x000
#घोषणा D40_DREG_GCC_ENA	0x1
/* This assumes that there are only 4 event groups */
#घोषणा D40_DREG_GCC_ENABLE_ALL	0x3ff01
#घोषणा D40_DREG_GCC_EVTGRP_POS 8
#घोषणा D40_DREG_GCC_SRC 0
#घोषणा D40_DREG_GCC_DST 1
#घोषणा D40_DREG_GCC_EVTGRP_ENA(x, y) \
	(1 << (D40_DREG_GCC_EVTGRP_POS + 2 * x + y))

#घोषणा D40_DREG_PRTYP		0x004
#घोषणा D40_DREG_PRSME		0x008
#घोषणा D40_DREG_PRSMO		0x00C
#घोषणा D40_DREG_PRMSE		0x010
#घोषणा D40_DREG_PRMSO		0x014
#घोषणा D40_DREG_PRMOE		0x018
#घोषणा D40_DREG_PRMOO		0x01C
#घोषणा D40_DREG_PRMO_PCHAN_BASIC		0x1
#घोषणा D40_DREG_PRMO_PCHAN_MODULO		0x2
#घोषणा D40_DREG_PRMO_PCHAN_DOUBLE_DST		0x3
#घोषणा D40_DREG_PRMO_LCHAN_SRC_PHY_DST_LOG	0x1
#घोषणा D40_DREG_PRMO_LCHAN_SRC_LOG_DST_PHY	0x2
#घोषणा D40_DREG_PRMO_LCHAN_SRC_LOG_DST_LOG	0x3

#घोषणा D40_DREG_LCPA		0x020
#घोषणा D40_DREG_LCLA		0x024

#घोषणा D40_DREG_SSEG1		0x030
#घोषणा D40_DREG_SSEG2		0x034
#घोषणा D40_DREG_SSEG3		0x038
#घोषणा D40_DREG_SSEG4		0x03C

#घोषणा D40_DREG_SCEG1		0x040
#घोषणा D40_DREG_SCEG2		0x044
#घोषणा D40_DREG_SCEG3		0x048
#घोषणा D40_DREG_SCEG4		0x04C

#घोषणा D40_DREG_ACTIVE		0x050
#घोषणा D40_DREG_ACTIVO		0x054
#घोषणा D40_DREG_CIDMOD		0x058
#घोषणा D40_DREG_TCIDV		0x05C
#घोषणा D40_DREG_PCMIS		0x060
#घोषणा D40_DREG_PCICR		0x064
#घोषणा D40_DREG_PCTIS		0x068
#घोषणा D40_DREG_PCEIS		0x06C

#घोषणा D40_DREG_SPCMIS		0x070
#घोषणा D40_DREG_SPCICR		0x074
#घोषणा D40_DREG_SPCTIS		0x078
#घोषणा D40_DREG_SPCEIS		0x07C

#घोषणा D40_DREG_LCMIS0		0x080
#घोषणा D40_DREG_LCMIS1		0x084
#घोषणा D40_DREG_LCMIS2		0x088
#घोषणा D40_DREG_LCMIS3		0x08C
#घोषणा D40_DREG_LCICR0		0x090
#घोषणा D40_DREG_LCICR1		0x094
#घोषणा D40_DREG_LCICR2		0x098
#घोषणा D40_DREG_LCICR3		0x09C
#घोषणा D40_DREG_LCTIS0		0x0A0
#घोषणा D40_DREG_LCTIS1		0x0A4
#घोषणा D40_DREG_LCTIS2		0x0A8
#घोषणा D40_DREG_LCTIS3		0x0AC
#घोषणा D40_DREG_LCEIS0		0x0B0
#घोषणा D40_DREG_LCEIS1		0x0B4
#घोषणा D40_DREG_LCEIS2		0x0B8
#घोषणा D40_DREG_LCEIS3		0x0BC

#घोषणा D40_DREG_SLCMIS1	0x0C0
#घोषणा D40_DREG_SLCMIS2	0x0C4
#घोषणा D40_DREG_SLCMIS3	0x0C8
#घोषणा D40_DREG_SLCMIS4	0x0CC

#घोषणा D40_DREG_SLCICR1	0x0D0
#घोषणा D40_DREG_SLCICR2	0x0D4
#घोषणा D40_DREG_SLCICR3	0x0D8
#घोषणा D40_DREG_SLCICR4	0x0DC

#घोषणा D40_DREG_SLCTIS1	0x0E0
#घोषणा D40_DREG_SLCTIS2	0x0E4
#घोषणा D40_DREG_SLCTIS3	0x0E8
#घोषणा D40_DREG_SLCTIS4	0x0EC

#घोषणा D40_DREG_SLCEIS1	0x0F0
#घोषणा D40_DREG_SLCEIS2	0x0F4
#घोषणा D40_DREG_SLCEIS3	0x0F8
#घोषणा D40_DREG_SLCEIS4	0x0FC

#घोषणा D40_DREG_FSESS1		0x100
#घोषणा D40_DREG_FSESS2		0x104

#घोषणा D40_DREG_FSEBS1		0x108
#घोषणा D40_DREG_FSEBS2		0x10C

#घोषणा D40_DREG_PSEG1		0x110
#घोषणा D40_DREG_PSEG2		0x114
#घोषणा D40_DREG_PSEG3		0x118
#घोषणा D40_DREG_PSEG4		0x11C
#घोषणा D40_DREG_PCEG1		0x120
#घोषणा D40_DREG_PCEG2		0x124
#घोषणा D40_DREG_PCEG3		0x128
#घोषणा D40_DREG_PCEG4		0x12C
#घोषणा D40_DREG_RSEG1		0x130
#घोषणा D40_DREG_RSEG2		0x134
#घोषणा D40_DREG_RSEG3		0x138
#घोषणा D40_DREG_RSEG4		0x13C
#घोषणा D40_DREG_RCEG1		0x140
#घोषणा D40_DREG_RCEG2		0x144
#घोषणा D40_DREG_RCEG3		0x148
#घोषणा D40_DREG_RCEG4		0x14C

#घोषणा D40_DREG_PREFOT		0x15C
#घोषणा D40_DREG_EXTCFG		0x160

#घोषणा D40_DREG_CPSEG1		0x200
#घोषणा D40_DREG_CPSEG2		0x204
#घोषणा D40_DREG_CPSEG3		0x208
#घोषणा D40_DREG_CPSEG4		0x20C
#घोषणा D40_DREG_CPSEG5		0x210

#घोषणा D40_DREG_CPCEG1		0x220
#घोषणा D40_DREG_CPCEG2		0x224
#घोषणा D40_DREG_CPCEG3		0x228
#घोषणा D40_DREG_CPCEG4		0x22C
#घोषणा D40_DREG_CPCEG5		0x230

#घोषणा D40_DREG_CRSEG1		0x240
#घोषणा D40_DREG_CRSEG2		0x244
#घोषणा D40_DREG_CRSEG3		0x248
#घोषणा D40_DREG_CRSEG4		0x24C
#घोषणा D40_DREG_CRSEG5		0x250

#घोषणा D40_DREG_CRCEG1		0x260
#घोषणा D40_DREG_CRCEG2		0x264
#घोषणा D40_DREG_CRCEG3		0x268
#घोषणा D40_DREG_CRCEG4		0x26C
#घोषणा D40_DREG_CRCEG5		0x270

#घोषणा D40_DREG_CFSESS1	0x280
#घोषणा D40_DREG_CFSESS2	0x284
#घोषणा D40_DREG_CFSESS3	0x288

#घोषणा D40_DREG_CFSEBS1	0x290
#घोषणा D40_DREG_CFSEBS2	0x294
#घोषणा D40_DREG_CFSEBS3	0x298

#घोषणा D40_DREG_CLCMIS1	0x300
#घोषणा D40_DREG_CLCMIS2	0x304
#घोषणा D40_DREG_CLCMIS3	0x308
#घोषणा D40_DREG_CLCMIS4	0x30C
#घोषणा D40_DREG_CLCMIS5	0x310

#घोषणा D40_DREG_CLCICR1	0x320
#घोषणा D40_DREG_CLCICR2	0x324
#घोषणा D40_DREG_CLCICR3	0x328
#घोषणा D40_DREG_CLCICR4	0x32C
#घोषणा D40_DREG_CLCICR5	0x330

#घोषणा D40_DREG_CLCTIS1	0x340
#घोषणा D40_DREG_CLCTIS2	0x344
#घोषणा D40_DREG_CLCTIS3	0x348
#घोषणा D40_DREG_CLCTIS4	0x34C
#घोषणा D40_DREG_CLCTIS5	0x350

#घोषणा D40_DREG_CLCEIS1	0x360
#घोषणा D40_DREG_CLCEIS2	0x364
#घोषणा D40_DREG_CLCEIS3	0x368
#घोषणा D40_DREG_CLCEIS4	0x36C
#घोषणा D40_DREG_CLCEIS5	0x370

#घोषणा D40_DREG_CPCMIS		0x380
#घोषणा D40_DREG_CPCICR		0x384
#घोषणा D40_DREG_CPCTIS		0x388
#घोषणा D40_DREG_CPCEIS		0x38C

#घोषणा D40_DREG_SCCIDA1	0xE80
#घोषणा D40_DREG_SCCIDA2	0xE90
#घोषणा D40_DREG_SCCIDA3	0xEA0
#घोषणा D40_DREG_SCCIDA4	0xEB0
#घोषणा D40_DREG_SCCIDA5	0xEC0

#घोषणा D40_DREG_SCCIDB1	0xE84
#घोषणा D40_DREG_SCCIDB2	0xE94
#घोषणा D40_DREG_SCCIDB3	0xEA4
#घोषणा D40_DREG_SCCIDB4	0xEB4
#घोषणा D40_DREG_SCCIDB5	0xEC4

#घोषणा D40_DREG_PRSCCIDA	0xF80
#घोषणा D40_DREG_PRSCCIDB	0xF84

#घोषणा D40_DREG_STFU		0xFC8
#घोषणा D40_DREG_ICFG		0xFCC
#घोषणा D40_DREG_PERIPHID0	0xFE0
#घोषणा D40_DREG_PERIPHID1	0xFE4
#घोषणा D40_DREG_PERIPHID2	0xFE8
#घोषणा D40_DREG_PERIPHID3	0xFEC
#घोषणा D40_DREG_CELLID0	0xFF0
#घोषणा D40_DREG_CELLID1	0xFF4
#घोषणा D40_DREG_CELLID2	0xFF8
#घोषणा D40_DREG_CELLID3	0xFFC

/* LLI related काष्ठाures */

/**
 * काष्ठा d40_phy_lli - The basic configuration रेजिस्टर क्रम each physical
 * channel.
 *
 * @reg_cfg: The configuration रेजिस्टर.
 * @reg_elt: The element रेजिस्टर.
 * @reg_ptr: The poपूर्णांकer रेजिस्टर.
 * @reg_lnk: The link रेजिस्टर.
 *
 * These रेजिस्टरs are set up क्रम both physical and logical transfers
 * Note that the bit in each रेजिस्टर means dअगरferently in logical and
 * physical(standard) mode.
 *
 * This काष्ठा must be 16 bytes aligned, and only contain physical रेजिस्टरs
 * since it will be directly accessed by the DMA.
 */
काष्ठा d40_phy_lli अणु
	u32 reg_cfg;
	u32 reg_elt;
	u32 reg_ptr;
	u32 reg_lnk;
पूर्ण;

/**
 * काष्ठा d40_phy_lli_bidir - काष्ठा क्रम a transfer.
 *
 * @src: Register settings क्रम src channel.
 * @dst: Register settings क्रम dst channel.
 *
 * All DMA transfers have a source and a destination.
 */

काष्ठा d40_phy_lli_bidir अणु
	काष्ठा d40_phy_lli	*src;
	काष्ठा d40_phy_lli	*dst;
पूर्ण;


/**
 * काष्ठा d40_log_lli - logical lli configuration
 *
 * @lcsp02: Either maps to रेजिस्टर lcsp0 अगर src or lcsp2 अगर dst.
 * @lcsp13: Either maps to रेजिस्टर lcsp1 अगर src or lcsp3 अगर dst.
 *
 * This काष्ठा must be 8 bytes aligned since it will be accessed directy by
 * the DMA. Never add any none hw mapped रेजिस्टरs to this काष्ठा.
 */

काष्ठा d40_log_lli अणु
	u32 lcsp02;
	u32 lcsp13;
पूर्ण;

/**
 * काष्ठा d40_log_lli_bidir - For both src and dst
 *
 * @src: poपूर्णांकer to src lli configuration.
 * @dst: poपूर्णांकer to dst lli configuration.
 *
 * You always have a src and a dst when करोing DMA transfers.
 */

काष्ठा d40_log_lli_bidir अणु
	काष्ठा d40_log_lli *src;
	काष्ठा d40_log_lli *dst;
पूर्ण;

/**
 * काष्ठा d40_log_lli_full - LCPA layout
 *
 * @lcsp0: Logical Channel Standard Param 0 - Src.
 * @lcsp1: Logical Channel Standard Param 1 - Src.
 * @lcsp2: Logical Channel Standard Param 2 - Dst.
 * @lcsp3: Logical Channel Standard Param 3 - Dst.
 *
 * This काष्ठा maps to LCPA physical memory layout. Must map to
 * the hw.
 */
काष्ठा d40_log_lli_full अणु
	u32 lcsp0;
	u32 lcsp1;
	u32 lcsp2;
	u32 lcsp3;
पूर्ण;

/**
 * काष्ठा d40_def_lcsp - Default LCSP1 and LCSP3 settings
 *
 * @lcsp3: The शेष configuration क्रम dst.
 * @lcsp1: The शेष configuration क्रम src.
 */
काष्ठा d40_def_lcsp अणु
	u32 lcsp3;
	u32 lcsp1;
पूर्ण;

/* Physical channels */

क्रमागत d40_lli_flags अणु
	LLI_ADDR_INC	= 1 << 0,
	LLI_TERM_INT	= 1 << 1,
	LLI_CYCLIC	= 1 << 2,
	LLI_LAST_LINK	= 1 << 3,
पूर्ण;

व्योम d40_phy_cfg(काष्ठा stedma40_chan_cfg *cfg,
		 u32 *src_cfg,
		 u32 *dst_cfg);

व्योम d40_log_cfg(काष्ठा stedma40_chan_cfg *cfg,
		 u32 *lcsp1,
		 u32 *lcsp2);

पूर्णांक d40_phy_sg_to_lli(काष्ठा scatterlist *sg,
		      पूर्णांक sg_len,
		      dma_addr_t target,
		      काष्ठा d40_phy_lli *lli,
		      dma_addr_t lli_phys,
		      u32 reg_cfg,
		      काष्ठा stedma40_half_channel_info *info,
		      काष्ठा stedma40_half_channel_info *otherinfo,
		      अचिन्हित दीर्घ flags);

/* Logical channels */

पूर्णांक d40_log_sg_to_lli(काष्ठा scatterlist *sg,
		      पूर्णांक sg_len,
		      dma_addr_t dev_addr,
		      काष्ठा d40_log_lli *lli_sg,
		      u32 lcsp13, /* src or dst*/
		      u32 data_width1, u32 data_width2);

व्योम d40_log_lli_lcpa_ग_लिखो(काष्ठा d40_log_lli_full *lcpa,
			    काष्ठा d40_log_lli *lli_dst,
			    काष्ठा d40_log_lli *lli_src,
			    पूर्णांक next, अचिन्हित पूर्णांक flags);

व्योम d40_log_lli_lcla_ग_लिखो(काष्ठा d40_log_lli *lcla,
			    काष्ठा d40_log_lli *lli_dst,
			    काष्ठा d40_log_lli *lli_src,
			    पूर्णांक next, अचिन्हित पूर्णांक flags);

#पूर्ण_अगर /* STE_DMA40_LLI_H */
