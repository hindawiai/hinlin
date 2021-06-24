<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "system_local.h"

/* ISP */
स्थिर hrt_address ISP_CTRL_BASE[N_ISP_ID] = अणु
	0x0000000000020000ULL
पूर्ण;

स्थिर hrt_address ISP_DMEM_BASE[N_ISP_ID] = अणु
	0x0000000000200000ULL
पूर्ण;

स्थिर hrt_address ISP_BAMEM_BASE[N_BAMEM_ID] = अणु
	0x0000000000100000ULL
पूर्ण;

/* SP */
स्थिर hrt_address SP_CTRL_BASE[N_SP_ID] = अणु
	0x0000000000010000ULL
पूर्ण;

स्थिर hrt_address SP_DMEM_BASE[N_SP_ID] = अणु
	0x0000000000300000ULL
पूर्ण;

/* MMU */
/*
 * MMU0_ID: The data MMU
 * MMU1_ID: The icache MMU
 */
स्थिर hrt_address MMU_BASE[N_MMU_ID] = अणु
	0x0000000000070000ULL,
	0x00000000000A0000ULL
पूर्ण;

/* DMA */
स्थिर hrt_address DMA_BASE[N_DMA_ID] = अणु
	0x0000000000040000ULL
पूर्ण;

स्थिर hrt_address ISYS2401_DMA_BASE[N_ISYS2401_DMA_ID] = अणु
	0x00000000000CA000ULL
पूर्ण;

/* IRQ */
स्थिर hrt_address IRQ_BASE[N_IRQ_ID] = अणु
	0x0000000000000500ULL,
	0x0000000000030A00ULL,
	0x000000000008C000ULL,
	0x0000000000090200ULL
पूर्ण;

/*
	0x0000000000000500ULLपूर्ण;
 */

/* GDC */
स्थिर hrt_address GDC_BASE[N_GDC_ID] = अणु
	0x0000000000050000ULL,
	0x0000000000060000ULL
पूर्ण;

/* FIFO_MONITOR (not a subset of GP_DEVICE) */
स्थिर hrt_address FIFO_MONITOR_BASE[N_FIFO_MONITOR_ID] = अणु
	0x0000000000000000ULL
पूर्ण;

/*
स्थिर hrt_address GP_REGS_BASE[N_GP_REGS_ID] = अणु
	0x0000000000000000ULLपूर्ण;

स्थिर hrt_address GP_DEVICE_BASE[N_GP_DEVICE_ID] = अणु
	0x0000000000090000ULLपूर्ण;
*/

/* GP_DEVICE (single base क्रम all separate GP_REG instances) */
स्थिर hrt_address GP_DEVICE_BASE[N_GP_DEVICE_ID] = अणु
	0x0000000000000000ULL
पूर्ण;

/*GP TIMER , all समयr रेजिस्टरs are पूर्णांकer-twined,
 * so, having multiple base addresses क्रम
 * dअगरferent समयrs करोes not help*/
स्थिर hrt_address GP_TIMER_BASE =
    (hrt_address)0x0000000000000600ULL;

/* GPIO */
स्थिर hrt_address GPIO_BASE[N_GPIO_ID] = अणु
	0x0000000000000400ULL
पूर्ण;

/* TIMED_CTRL */
स्थिर hrt_address TIMED_CTRL_BASE[N_TIMED_CTRL_ID] = अणु
	0x0000000000000100ULL
पूर्ण;

/* INPUT_FORMATTER */
स्थिर hrt_address INPUT_FORMATTER_BASE[N_INPUT_FORMATTER_ID] = अणु
	0x0000000000030000ULL,
	0x0000000000030200ULL,
	0x0000000000030400ULL,
	0x0000000000030600ULL
पूर्ण; /* स_नकल() */

/* INPUT_SYSTEM */
स्थिर hrt_address INPUT_SYSTEM_BASE[N_INPUT_SYSTEM_ID] = अणु
	0x0000000000080000ULL
पूर्ण;

/*	0x0000000000081000ULL, */ /* capture A */
/*	0x0000000000082000ULL, */ /* capture B */
/*	0x0000000000083000ULL, */ /* capture C */
/*	0x0000000000084000ULL, */ /* Acquisition */
/*	0x0000000000085000ULL, */ /* DMA */
/*	0x0000000000089000ULL, */ /* ctrl */
/*	0x000000000008A000ULL, */ /* GP regs */
/*	0x000000000008B000ULL, */ /* FIFO */
/*	0x000000000008C000ULL, */ /* IRQ */

/* RX, the MIPI lane control regs start at offset 0 */
स्थिर hrt_address RX_BASE[N_RX_ID] = अणु
	0x0000000000080100ULL
पूर्ण;

/* IBUF_CTRL, part of the Input System 2401 */
स्थिर hrt_address IBUF_CTRL_BASE[N_IBUF_CTRL_ID] = अणु
	0x00000000000C1800ULL,	/* ibuf controller A */
	0x00000000000C3800ULL,	/* ibuf controller B */
	0x00000000000C5800ULL	/* ibuf controller C */
पूर्ण;

/* ISYS IRQ Controllers, part of the Input System 2401 */
स्थिर hrt_address ISYS_IRQ_BASE[N_ISYS_IRQ_ID] = अणु
	0x00000000000C1400ULL,	/* port a */
	0x00000000000C3400ULL,	/* port b */
	0x00000000000C5400ULL	/* port c */
पूर्ण;

/* CSI FE, part of the Input System 2401 */
स्थिर hrt_address CSI_RX_FE_CTRL_BASE[N_CSI_RX_FRONTEND_ID] = अणु
	0x00000000000C0400ULL,	/* csi fe controller A */
	0x00000000000C2400ULL,	/* csi fe controller B */
	0x00000000000C4400ULL	/* csi fe controller C */
पूर्ण;

/* CSI BE, part of the Input System 2401 */
स्थिर hrt_address CSI_RX_BE_CTRL_BASE[N_CSI_RX_BACKEND_ID] = अणु
	0x00000000000C0800ULL,	/* csi be controller A */
	0x00000000000C2800ULL,	/* csi be controller B */
	0x00000000000C4800ULL	/* csi be controller C */
पूर्ण;

/* PIXEL Generator, part of the Input System 2401 */
स्थिर hrt_address PIXELGEN_CTRL_BASE[N_PIXELGEN_ID] = अणु
	0x00000000000C1000ULL,	/* pixel gen controller A */
	0x00000000000C3000ULL,	/* pixel gen controller B */
	0x00000000000C5000ULL	/* pixel gen controller C */
पूर्ण;

/* Stream2MMIO, part of the Input System 2401 */
स्थिर hrt_address STREAM2MMIO_CTRL_BASE[N_STREAM2MMIO_ID] = अणु
	0x00000000000C0C00ULL,	/* stream2mmio controller A */
	0x00000000000C2C00ULL,	/* stream2mmio controller B */
	0x00000000000C4C00ULL	/* stream2mmio controller C */
पूर्ण;
