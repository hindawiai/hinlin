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

#अगर_अघोषित __DEBUG_GLOBAL_H_INCLUDED__
#घोषणा __DEBUG_GLOBAL_H_INCLUDED__

#समावेश <type_support.h>

#घोषणा DEBUG_BUF_SIZE	1024
#घोषणा DEBUG_BUF_MASK	(DEBUG_BUF_SIZE - 1)

#घोषणा DEBUG_DATA_ENABLE_ADDR		0x00
#घोषणा DEBUG_DATA_BUF_MODE_ADDR	0x04
#घोषणा DEBUG_DATA_HEAD_ADDR		0x08
#घोषणा DEBUG_DATA_TAIL_ADDR		0x0C
#घोषणा DEBUG_DATA_BUF_ADDR			0x10

#घोषणा DEBUG_DATA_ENABLE_DDR_ADDR		0x00
#घोषणा DEBUG_DATA_BUF_MODE_DDR_ADDR	HIVE_ISP_DDR_WORD_BYTES
#घोषणा DEBUG_DATA_HEAD_DDR_ADDR		(2 * HIVE_ISP_DDR_WORD_BYTES)
#घोषणा DEBUG_DATA_TAIL_DDR_ADDR		(3 * HIVE_ISP_DDR_WORD_BYTES)
#घोषणा DEBUG_DATA_BUF_DDR_ADDR			(4 * HIVE_ISP_DDR_WORD_BYTES)

#घोषणा DEBUG_BUFFER_ISP_DMEM_ADDR       0x0

/*
 * Enable HAS_WATCHDOG_SP_THREAD_DEBUG क्रम additional SP thपढ़ो and
 * pipe inक्रमmation on watchकरोg output
 * #अघोषित HAS_WATCHDOG_SP_THREAD_DEBUG
 * #घोषणा HAS_WATCHDOG_SP_THREAD_DEBUG
 */

/*
 * The linear buffer mode will accept data until the first
 * overflow and then stop accepting new data
 * The circular buffer mode will accept अगर there is place
 * and discard the data अगर the buffer is full
 */
प्रकार क्रमागत अणु
	DEBUG_BUFFER_MODE_LINEAR = 0,
	DEBUG_BUFFER_MODE_CIRCULAR,
	N_DEBUG_BUFFER_MODE
पूर्ण debug_buf_mode_t;

काष्ठा debug_data_s अणु
	u32			enable;
	u32			buभ_शेषe;
	u32			head;
	u32			tail;
	u32			buf[DEBUG_BUF_SIZE];
पूर्ण;

/* thपढ़ो.sp.c करोesn't have a notion of HIVE_ISP_DDR_WORD_BYTES
   still one poपूर्णांक of control is needed क्रम debug purposes */

#अगर_घोषित HIVE_ISP_DDR_WORD_BYTES
काष्ठा debug_data_ddr_s अणु
	u32			enable;
	s8				padding1[HIVE_ISP_DDR_WORD_BYTES - माप(uपूर्णांक32_t)];
	u32			buभ_शेषe;
	s8				padding2[HIVE_ISP_DDR_WORD_BYTES - माप(uपूर्णांक32_t)];
	u32			head;
	s8				padding3[HIVE_ISP_DDR_WORD_BYTES - माप(uपूर्णांक32_t)];
	u32			tail;
	s8				padding4[HIVE_ISP_DDR_WORD_BYTES - माप(uपूर्णांक32_t)];
	u32			buf[DEBUG_BUF_SIZE];
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* __DEBUG_GLOBAL_H_INCLUDED__ */
