<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#अगर_अघोषित __MESON_VDEC_DOS_REGS_H_
#घोषणा __MESON_VDEC_DOS_REGS_H_

/* DOS रेजिस्टरs */
#घोषणा VDEC_ASSIST_AMR1_INT8	0x00b4

#घोषणा ASSIST_MBOX1_CLR_REG	0x01d4
#घोषणा ASSIST_MBOX1_MASK	0x01d8

#घोषणा MPSR			0x0c04
#घोषणा MCPU_INTR_MSK		0x0c10
#घोषणा CPSR			0x0c84

#घोषणा IMEM_DMA_CTRL		0x0d00
#घोषणा IMEM_DMA_ADR		0x0d04
#घोषणा IMEM_DMA_COUNT		0x0d08
#घोषणा LMEM_DMA_CTRL		0x0d40

#घोषणा MC_STATUS0		0x2424
#घोषणा MC_CTRL1		0x242c

#घोषणा PSCALE_RST		0x2440
#घोषणा PSCALE_CTRL		0x2444
#घोषणा PSCALE_BMEM_ADDR	0x247c
#घोषणा PSCALE_BMEM_DAT		0x2480

#घोषणा DBLK_CTRL		0x2544
#घोषणा DBLK_STATUS		0x254c

#घोषणा GCLK_EN			0x260c
#घोषणा MDEC_PIC_DC_CTRL	0x2638
#घोषणा MDEC_PIC_DC_STATUS	0x263c
#घोषणा ANC0_CANVAS_ADDR	0x2640
#घोषणा MDEC_PIC_DC_THRESH	0x26e0

/* Firmware पूर्णांकerface रेजिस्टरs */
#घोषणा AV_SCRATCH_0		0x2700
#घोषणा AV_SCRATCH_1		0x2704
#घोषणा AV_SCRATCH_2		0x2708
#घोषणा AV_SCRATCH_3		0x270c
#घोषणा AV_SCRATCH_4		0x2710
#घोषणा AV_SCRATCH_5		0x2714
#घोषणा AV_SCRATCH_6		0x2718
#घोषणा AV_SCRATCH_7		0x271c
#घोषणा AV_SCRATCH_8		0x2720
#घोषणा AV_SCRATCH_9		0x2724
#घोषणा AV_SCRATCH_A		0x2728
#घोषणा AV_SCRATCH_B		0x272c
#घोषणा AV_SCRATCH_C		0x2730
#घोषणा AV_SCRATCH_D		0x2734
#घोषणा AV_SCRATCH_E		0x2738
#घोषणा AV_SCRATCH_F		0x273c
#घोषणा AV_SCRATCH_G		0x2740
#घोषणा AV_SCRATCH_H		0x2744
#घोषणा AV_SCRATCH_I		0x2748
#घोषणा AV_SCRATCH_J		0x274c
#घोषणा AV_SCRATCH_K		0x2750
#घोषणा AV_SCRATCH_L		0x2754

#घोषणा MPEG1_2_REG		0x3004
#घोषणा PIC_HEAD_INFO		0x300c
#घोषणा POWER_CTL_VLD		0x3020
#घोषणा M4_CONTROL_REG		0x30a4

/* Stream Buffer (stbuf) regs */
#घोषणा VLD_MEM_VIFIFO_START_PTR	0x3100
#घोषणा VLD_MEM_VIFIFO_CURR_PTR	0x3104
#घोषणा VLD_MEM_VIFIFO_END_PTR	0x3108
#घोषणा VLD_MEM_VIFIFO_CONTROL	0x3110
	#घोषणा MEM_FIFO_CNT_BIT	16
	#घोषणा MEM_FILL_ON_LEVEL	BIT(10)
	#घोषणा MEM_CTRL_EMPTY_EN	BIT(2)
	#घोषणा MEM_CTRL_FILL_EN	BIT(1)
#घोषणा VLD_MEM_VIFIFO_WP	0x3114
#घोषणा VLD_MEM_VIFIFO_RP	0x3118
#घोषणा VLD_MEM_VIFIFO_LEVEL	0x311c
#घोषणा VLD_MEM_VIFIFO_BUF_CNTL	0x3120
	#घोषणा MEM_BUFCTRL_MANUAL	BIT(1)
#घोषणा VLD_MEM_VIFIFO_WRAP_COUNT	0x3144

#घोषणा DCAC_DMA_CTRL		0x3848

#घोषणा DOS_SW_RESET0		0xfc00
#घोषणा DOS_GCLK_EN0		0xfc04
#घोषणा DOS_GEN_CTRL0		0xfc08
#घोषणा DOS_MEM_PD_VDEC		0xfcc0
#घोषणा DOS_MEM_PD_HEVC		0xfccc
#घोषणा DOS_SW_RESET3		0xfcd0
#घोषणा DOS_GCLK_EN3		0xfcd4
#घोषणा DOS_VDEC_MCRCC_STALL_CTRL	0xfd00

#पूर्ण_अगर
