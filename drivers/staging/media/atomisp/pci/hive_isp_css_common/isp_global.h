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

#अगर_अघोषित __ISP_GLOBAL_H_INCLUDED__
#घोषणा __ISP_GLOBAL_H_INCLUDED__

#समावेश <प्रणाली_local.h>

#समावेश "mamoiada_params.h"

#घोषणा ISP_PMEM_WIDTH_LOG2		ISP_LOG2_PMEM_WIDTH
#घोषणा ISP_PMEM_SIZE			ISP_PMEM_DEPTH

#घोषणा ISP_NWAY_LOG2			6
#घोषणा ISP_VEC_NELEMS_LOG2		ISP_NWAY_LOG2

#अगर_घोषित PIPE_GENERATION
#घोषणा PIPEMEM(x) MEM(x)
#घोषणा ISP_NWAY   BIT(ISP_NWAY_LOG2)
#अन्यथा
#घोषणा PIPEMEM(x)
#पूर्ण_अगर

/* The number of data bytes in a vector disregarding the reduced precision */
#घोषणा ISP_VEC_BYTES			(ISP_VEC_NELEMS * माप(uपूर्णांक16_t))

/* ISP SC Registers */
#घोषणा ISP_SC_REG			0x00
#घोषणा ISP_PC_REG			0x07
#घोषणा ISP_IRQ_READY_REG		0x00
#घोषणा ISP_IRQ_CLEAR_REG		0x00

/* ISP SC Register bits */
#घोषणा ISP_RST_BIT			0x00
#घोषणा ISP_START_BIT			0x01
#घोषणा ISP_BREAK_BIT			0x02
#घोषणा ISP_RUN_BIT			0x03
#घोषणा ISP_BROKEN_BIT			0x04
#घोषणा ISP_IDLE_BIT			0x05     /* READY */
#घोषणा ISP_SLEEPING_BIT		0x06
#घोषणा ISP_STALLING_BIT		0x07
#घोषणा ISP_IRQ_CLEAR_BIT		0x08
#घोषणा ISP_IRQ_READY_BIT		0x0A
#घोषणा ISP_IRQ_SLEEPING_BIT		0x0B

/* ISP Register bits */
#घोषणा ISP_CTRL_SINK_BIT		0x00
#घोषणा ISP_PMEM_SINK_BIT		0x01
#घोषणा ISP_DMEM_SINK_BIT		0x02
#घोषणा ISP_FIFO0_SINK_BIT		0x03
#घोषणा ISP_FIFO1_SINK_BIT		0x04
#घोषणा ISP_FIFO2_SINK_BIT		0x05
#घोषणा ISP_FIFO3_SINK_BIT		0x06
#घोषणा ISP_FIFO4_SINK_BIT		0x07
#घोषणा ISP_FIFO5_SINK_BIT		0x08
#घोषणा ISP_FIFO6_SINK_BIT		0x09
#घोषणा ISP_VMEM_SINK_BIT		0x0A
#घोषणा ISP_VAMEM1_SINK_BIT		0x0B
#घोषणा ISP_VAMEM2_SINK_BIT		0x0C
#घोषणा ISP_VAMEM3_SINK_BIT		0x0D
#घोषणा ISP_HMEM_SINK_BIT		0x0E

#घोषणा ISP_CTRL_SINK_REG		0x08
#घोषणा ISP_PMEM_SINK_REG		0x08
#घोषणा ISP_DMEM_SINK_REG		0x08
#घोषणा ISP_FIFO0_SINK_REG		0x08
#घोषणा ISP_FIFO1_SINK_REG		0x08
#घोषणा ISP_FIFO2_SINK_REG		0x08
#घोषणा ISP_FIFO3_SINK_REG		0x08
#घोषणा ISP_FIFO4_SINK_REG		0x08
#घोषणा ISP_FIFO5_SINK_REG		0x08
#घोषणा ISP_FIFO6_SINK_REG		0x08
#घोषणा ISP_VMEM_SINK_REG		0x08
#घोषणा ISP_VAMEM1_SINK_REG		0x08
#घोषणा ISP_VAMEM2_SINK_REG		0x08
#घोषणा ISP_VAMEM3_SINK_REG		0x08
#घोषणा ISP_HMEM_SINK_REG		0x08

/* ISP2401 */
#घोषणा BAMEM VMEM
#घोषणा XNR3_DOWN_BAMEM_BASE_ADDRESS    (0x16880)
#घोषणा XNR3_UP_BAMEM_BASE_ADDRESS      (0x12880)
#घोषणा bmem_ldrow(fu, pid, offset, data) bmem_ldrow_s(fu, pid, offset, data)
#घोषणा bmem_strow(fu, pid, offset, data) bmem_strow_s(fu, pid, offset, data)
#घोषणा bmem_ldblk(fu, pid, offset, data) bmem_ldblk_s(fu, pid, offset, data)
#घोषणा bmem_stblk(fu, pid, offset, data) bmem_stblk_s(fu, pid, offset, data)

#पूर्ण_अगर /* __ISP_GLOBAL_H_INCLUDED__ */
