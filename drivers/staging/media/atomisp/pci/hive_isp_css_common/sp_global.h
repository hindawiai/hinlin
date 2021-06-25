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

#अगर_अघोषित __SP_GLOBAL_H_INCLUDED__
#घोषणा __SP_GLOBAL_H_INCLUDED__

#समावेश <प्रणाली_local.h>

#समावेश <scalar_processor_2400_params.h>

#घोषणा SP_PMEM_WIDTH_LOG2		SP_PMEM_LOG_WIDTH_BITS
#घोषणा SP_PMEM_SIZE			SP_PMEM_DEPTH

#घोषणा SP_DMEM_SIZE			0x4000

/* SP Registers */
#घोषणा SP_PC_REG				0x09
#घोषणा SP_SC_REG				0x00
#घोषणा SP_START_ADDR_REG		0x01
#घोषणा SP_ICACHE_ADDR_REG		0x05
#घोषणा SP_IRQ_READY_REG		0x00
#घोषणा SP_IRQ_CLEAR_REG		0x00
#घोषणा SP_ICACHE_INV_REG		0x00
#घोषणा SP_CTRL_SINK_REG		0x0A

/* SP Register bits */
#घोषणा SP_RST_BIT			0x00
#घोषणा SP_START_BIT			0x01
#घोषणा SP_BREAK_BIT			0x02
#घोषणा SP_RUN_BIT			0x03
#घोषणा SP_BROKEN_BIT			0x04
#घोषणा SP_IDLE_BIT			0x05     /* READY */
#घोषणा SP_SLEEPING_BIT			0x06
#घोषणा SP_STALLING_BIT			0x07
#घोषणा SP_IRQ_CLEAR_BIT		0x08
#घोषणा SP_IRQ_READY_BIT		0x0A
#घोषणा SP_IRQ_SLEEPING_BIT		0x0B

#घोषणा SP_ICACHE_INV_BIT		0x0C
#घोषणा SP_IPREFETCH_EN_BIT		0x0D

#घोषणा SP_FIFO0_SINK_BIT		0x00
#घोषणा SP_FIFO1_SINK_BIT		0x01
#घोषणा SP_FIFO2_SINK_BIT		0x02
#घोषणा SP_FIFO3_SINK_BIT		0x03
#घोषणा SP_FIFO4_SINK_BIT		0x04
#घोषणा SP_FIFO5_SINK_BIT		0x05
#घोषणा SP_FIFO6_SINK_BIT		0x06
#घोषणा SP_FIFO7_SINK_BIT		0x07
#घोषणा SP_FIFO8_SINK_BIT		0x08
#घोषणा SP_FIFO9_SINK_BIT		0x09
#घोषणा SP_FIFOA_SINK_BIT		0x0A
#घोषणा SP_DMEM_SINK_BIT		0x0B
#घोषणा SP_CTRL_MT_SINK_BIT		0x0C
#घोषणा SP_ICACHE_MT_SINK_BIT	0x0D

#घोषणा SP_FIFO0_SINK_REG		0x0A
#घोषणा SP_FIFO1_SINK_REG		0x0A
#घोषणा SP_FIFO2_SINK_REG		0x0A
#घोषणा SP_FIFO3_SINK_REG		0x0A
#घोषणा SP_FIFO4_SINK_REG		0x0A
#घोषणा SP_FIFO5_SINK_REG		0x0A
#घोषणा SP_FIFO6_SINK_REG		0x0A
#घोषणा SP_FIFO7_SINK_REG		0x0A
#घोषणा SP_FIFO8_SINK_REG		0x0A
#घोषणा SP_FIFO9_SINK_REG		0x0A
#घोषणा SP_FIFOA_SINK_REG		0x0A
#घोषणा SP_DMEM_SINK_REG		0x0A
#घोषणा SP_CTRL_MT_SINK_REG		0x0A
#घोषणा SP_ICACHE_MT_SINK_REG	0x0A

#पूर्ण_अगर /* __SP_GLOBAL_H_INCLUDED__ */
