<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __SYSTEM_LOCAL_H_INCLUDED__
#घोषणा __SYSTEM_LOCAL_H_INCLUDED__

#अगर_घोषित HRT_ISP_CSS_CUSTOM_HOST
#अगर_अघोषित HRT_USE_VIR_ADDRS
#घोषणा HRT_USE_VIR_ADDRS
#पूर्ण_अगर
#पूर्ण_अगर

#समावेश "system_global.h"

/* This पूर्णांकerface is deprecated */
#समावेश "hive_types.h"

/*
 * Cell specअगरic address maps
 */

#घोषणा GP_FIFO_BASE   ((hrt_address)0x0000000000090104)		/* This is NOT a base address */

/* ISP */
बाह्य स्थिर hrt_address ISP_CTRL_BASE[N_ISP_ID];
बाह्य स्थिर hrt_address ISP_DMEM_BASE[N_ISP_ID];
बाह्य स्थिर hrt_address ISP_BAMEM_BASE[N_BAMEM_ID];

/* SP */
बाह्य स्थिर hrt_address SP_CTRL_BASE[N_SP_ID];
बाह्य स्थिर hrt_address SP_DMEM_BASE[N_SP_ID];

/* MMU */

बाह्य स्थिर hrt_address MMU_BASE[N_MMU_ID];

/* DMA */
बाह्य स्थिर hrt_address DMA_BASE[N_DMA_ID];
बाह्य स्थिर hrt_address ISYS2401_DMA_BASE[N_ISYS2401_DMA_ID];

/* IRQ */
बाह्य स्थिर hrt_address IRQ_BASE[N_IRQ_ID];

/* GDC */
बाह्य स्थिर hrt_address GDC_BASE[N_GDC_ID];

/* FIFO_MONITOR (not a subset of GP_DEVICE) */
बाह्य स्थिर hrt_address FIFO_MONITOR_BASE[N_FIFO_MONITOR_ID];

/* GP_DEVICE (single base क्रम all separate GP_REG instances) */
बाह्य स्थिर hrt_address GP_DEVICE_BASE[N_GP_DEVICE_ID];

/*GP TIMER , all समयr रेजिस्टरs are पूर्णांकer-twined,
 * so, having multiple base addresses क्रम
 * dअगरferent समयrs करोes not help*/
बाह्य स्थिर hrt_address GP_TIMER_BASE;

/* GPIO */
बाह्य स्थिर hrt_address GPIO_BASE[N_GPIO_ID];

/* TIMED_CTRL */
बाह्य स्थिर hrt_address TIMED_CTRL_BASE[N_TIMED_CTRL_ID];

/* INPUT_FORMATTER */
बाह्य स्थिर hrt_address INPUT_FORMATTER_BASE[N_INPUT_FORMATTER_ID];

/* INPUT_SYSTEM */
बाह्य स्थिर hrt_address INPUT_SYSTEM_BASE[N_INPUT_SYSTEM_ID];

/* RX, the MIPI lane control regs start at offset 0 */
बाह्य स्थिर hrt_address RX_BASE[N_RX_ID];

/* IBUF_CTRL, part of the Input System 2401 */
बाह्य स्थिर hrt_address IBUF_CTRL_BASE[N_IBUF_CTRL_ID];

/* ISYS IRQ Controllers, part of the Input System 2401 */
बाह्य स्थिर hrt_address ISYS_IRQ_BASE[N_ISYS_IRQ_ID];

/* CSI FE, part of the Input System 2401 */
बाह्य स्थिर hrt_address CSI_RX_FE_CTRL_BASE[N_CSI_RX_FRONTEND_ID];

/* CSI BE, part of the Input System 2401 */
बाह्य स्थिर hrt_address CSI_RX_BE_CTRL_BASE[N_CSI_RX_BACKEND_ID];

/* PIXEL Generator, part of the Input System 2401 */
बाह्य स्थिर hrt_address PIXELGEN_CTRL_BASE[N_PIXELGEN_ID];

/* Stream2MMIO, part of the Input System 2401 */
बाह्य स्थिर hrt_address STREAM2MMIO_CTRL_BASE[N_STREAM2MMIO_ID];

#पूर्ण_अगर /* __SYSTEM_LOCAL_H_INCLUDED__ */
