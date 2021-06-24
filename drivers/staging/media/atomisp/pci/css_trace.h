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

#अगर_अघोषित __CSS_TRACE_H_
#घोषणा __CSS_TRACE_H_

#समावेश <type_support.h>
#समावेश "sh_css_internal.h"	/* क्रम SH_CSS_MAX_SP_THREADS */

/*
	काष्ठाs and स्थिरants क्रम tracing
*/

/* one tracer item: major, minor and counter. The counter value can be used क्रम GP data */
काष्ठा trace_item_t अणु
	u8   major;
	u8   minor;
	u16  counter;
पूर्ण;

#घोषणा MAX_SCRATCH_DATA	4
#घोषणा MAX_CMD_DATA		2

/* trace header: holds the version and the topology of the tracer. */
काष्ठा trace_header_t अणु
	/* 1st dword: descriptor */
	u8   version;
	u8   max_thपढ़ोs;
	u16  max_tracer_poपूर्णांकs;
	/* 2nd field: command + data */
	/* 2nd dword */
	u32  command;
	/* 3rd & 4th dword */
	u32  data[MAX_CMD_DATA];
	/* 3rd field: debug poपूर्णांकer */
	/* 5th & 6th dword: debug poपूर्णांकer mechanism */
	u32  debug_ptr_signature;
	u32  debug_ptr_value;
	/* Rest of the header: status & scratch data */
	u8   thr_status_byte[SH_CSS_MAX_SP_THREADS];
	u16  thr_status_word[SH_CSS_MAX_SP_THREADS];
	u32  thr_status_dword[SH_CSS_MAX_SP_THREADS];
	u32  scratch_debug[MAX_SCRATCH_DATA];
पूर्ण;

/* offsets क्रम master_port पढ़ो/ग_लिखो */
#घोषणा HDR_HDR_OFFSET              0	/* offset of the header */
#घोषणा HDR_COMMAND_OFFSET          दुरत्व(काष्ठा trace_header_t, command)
#घोषणा HDR_DATA_OFFSET             दुरत्व(काष्ठा trace_header_t, data)
#घोषणा HDR_DEBUG_SIGNATURE_OFFSET  दुरत्व(काष्ठा trace_header_t, debug_ptr_signature)
#घोषणा HDR_DEBUG_POINTER_OFFSET    दुरत्व(काष्ठा trace_header_t, debug_ptr_value)
#घोषणा HDR_STATUS_OFFSET           दुरत्व(काष्ठा trace_header_t, thr_status_byte)
#घोषणा HDR_STATUS_OFFSET_BYTE      दुरत्व(काष्ठा trace_header_t, thr_status_byte)
#घोषणा HDR_STATUS_OFFSET_WORD      दुरत्व(काष्ठा trace_header_t, thr_status_word)
#घोषणा HDR_STATUS_OFFSET_DWORD     दुरत्व(काष्ठा trace_header_t, thr_status_dword)
#घोषणा HDR_STATUS_OFFSET_SCRATCH   दुरत्व(काष्ठा trace_header_t, scratch_debug)

/*
Trace version history:
 1: initial version, hdr = descr, command & ptr.
 2: added ISP + 24-bit fields.
 3: added thपढ़ो ID.
 4: added status in header.
*/
#घोषणा TRACER_VER			4

#घोषणा TRACE_BUFF_ADDR       0xA000
#घोषणा TRACE_BUFF_SIZE       0x1000	/* 4K allocated */

#घोषणा TRACE_ENABLE_SP0 0
#घोषणा TRACE_ENABLE_SP1 0
#घोषणा TRACE_ENABLE_ISP 0

क्रमागत TRACE_CORE_ID अणु
	TRACE_SP0_ID,
	TRACE_SP1_ID,
	TRACE_ISP_ID
पूर्ण;

/* TODO: add timing क्रमmat? */
क्रमागत TRACE_DUMP_FORMAT अणु
	TRACE_DUMP_FORMAT_POINT_NO_TID,
	TRACE_DUMP_FORMAT_VALUE24,
	TRACE_DUMP_FORMAT_VALUE24_TIMING,
	TRACE_DUMP_FORMAT_VALUE24_TIMING_DELTA,
	TRACE_DUMP_FORMAT_POINT
पूर्ण;

/* currently भागided as follows:*/
#अगर (TRACE_ENABLE_SP0 + TRACE_ENABLE_SP1 + TRACE_ENABLE_ISP == 3)
/* can be भागided as needed */
#घोषणा TRACE_SP0_SIZE (TRACE_BUFF_SIZE / 4)
#घोषणा TRACE_SP1_SIZE (TRACE_BUFF_SIZE / 4)
#घोषणा TRACE_ISP_SIZE (TRACE_BUFF_SIZE / 2)
#या_अगर (TRACE_ENABLE_SP0 + TRACE_ENABLE_SP1 + TRACE_ENABLE_ISP == 2)
#अगर TRACE_ENABLE_SP0
#घोषणा TRACE_SP0_SIZE (TRACE_BUFF_SIZE / 2)
#अन्यथा
#घोषणा TRACE_SP0_SIZE (0)
#पूर्ण_अगर
#अगर TRACE_ENABLE_SP1
#घोषणा TRACE_SP1_SIZE (TRACE_BUFF_SIZE / 2)
#अन्यथा
#घोषणा TRACE_SP1_SIZE (0)
#पूर्ण_अगर
#अगर TRACE_ENABLE_ISP
#घोषणा TRACE_ISP_SIZE (TRACE_BUFF_SIZE / 2)
#अन्यथा
#घोषणा TRACE_ISP_SIZE (0)
#पूर्ण_अगर
#या_अगर (TRACE_ENABLE_SP0 + TRACE_ENABLE_SP1 + TRACE_ENABLE_ISP == 1)
#अगर TRACE_ENABLE_SP0
#घोषणा TRACE_SP0_SIZE (TRACE_BUFF_SIZE)
#अन्यथा
#घोषणा TRACE_SP0_SIZE (0)
#पूर्ण_अगर
#अगर TRACE_ENABLE_SP1
#घोषणा TRACE_SP1_SIZE (TRACE_BUFF_SIZE)
#अन्यथा
#घोषणा TRACE_SP1_SIZE (0)
#पूर्ण_अगर
#अगर TRACE_ENABLE_ISP
#घोषणा TRACE_ISP_SIZE (TRACE_BUFF_SIZE)
#अन्यथा
#घोषणा TRACE_ISP_SIZE (0)
#पूर्ण_अगर
#अन्यथा
#घोषणा TRACE_SP0_SIZE (0)
#घोषणा TRACE_SP1_SIZE (0)
#घोषणा TRACE_ISP_SIZE (0)
#पूर्ण_अगर

#घोषणा TRACE_SP0_ADDR (TRACE_BUFF_ADDR)
#घोषणा TRACE_SP1_ADDR (TRACE_SP0_ADDR + TRACE_SP0_SIZE)
#घोषणा TRACE_ISP_ADDR (TRACE_SP1_ADDR + TRACE_SP1_SIZE)

/* check अगर it's a legal भागision */
#अगर (TRACE_BUFF_SIZE < TRACE_SP0_SIZE + TRACE_SP1_SIZE + TRACE_ISP_SIZE)
#त्रुटि trace sizes are not भागided correctly and are above limit
#पूर्ण_अगर

#घोषणा TRACE_SP0_HEADER_ADDR (TRACE_SP0_ADDR)
#घोषणा TRACE_SP0_HEADER_SIZE (माप(काष्ठा trace_header_t))
#घोषणा TRACE_SP0_ITEM_SIZE   (माप(काष्ठा trace_item_t))
#घोषणा TRACE_SP0_DATA_ADDR   (TRACE_SP0_HEADER_ADDR + TRACE_SP0_HEADER_SIZE)
#घोषणा TRACE_SP0_DATA_SIZE   (TRACE_SP0_SIZE - TRACE_SP0_HEADER_SIZE)
#घोषणा TRACE_SP0_MAX_POINTS  (TRACE_SP0_DATA_SIZE / TRACE_SP0_ITEM_SIZE)

#घोषणा TRACE_SP1_HEADER_ADDR (TRACE_SP1_ADDR)
#घोषणा TRACE_SP1_HEADER_SIZE (माप(काष्ठा trace_header_t))
#घोषणा TRACE_SP1_ITEM_SIZE   (माप(काष्ठा trace_item_t))
#घोषणा TRACE_SP1_DATA_ADDR   (TRACE_SP1_HEADER_ADDR + TRACE_SP1_HEADER_SIZE)
#घोषणा TRACE_SP1_DATA_SIZE   (TRACE_SP1_SIZE - TRACE_SP1_HEADER_SIZE)
#घोषणा TRACE_SP1_MAX_POINTS  (TRACE_SP1_DATA_SIZE / TRACE_SP1_ITEM_SIZE)

#घोषणा TRACE_ISP_HEADER_ADDR (TRACE_ISP_ADDR)
#घोषणा TRACE_ISP_HEADER_SIZE (माप(काष्ठा trace_header_t))
#घोषणा TRACE_ISP_ITEM_SIZE   (माप(काष्ठा trace_item_t))
#घोषणा TRACE_ISP_DATA_ADDR   (TRACE_ISP_HEADER_ADDR + TRACE_ISP_HEADER_SIZE)
#घोषणा TRACE_ISP_DATA_SIZE   (TRACE_ISP_SIZE - TRACE_ISP_HEADER_SIZE)
#घोषणा TRACE_ISP_MAX_POINTS  (TRACE_ISP_DATA_SIZE / TRACE_ISP_ITEM_SIZE)

/* common majors */
/* SP0 */
#घोषणा MAJOR_MAIN              1
#घोषणा MAJOR_ISP_STAGE_ENTRY   2
#घोषणा MAJOR_DMA_PRXY          3
#घोषणा MAJOR_START_ISP         4
/* SP1 */
#घोषणा MAJOR_OBSERVER_ISP0_EVENT          21
#घोषणा MAJOR_OBSERVER_OUTPUT_FORM_EVENT   22
#घोषणा MAJOR_OBSERVER_OUTPUT_SCAL_EVENT   23
#घोषणा MAJOR_OBSERVER_IF_ACK              24
#घोषणा MAJOR_OBSERVER_SP0_EVENT           25
#घोषणा MAJOR_OBSERVER_SP_TERMINATE_EVENT  26
#घोषणा MAJOR_OBSERVER_DMA_ACK             27
#घोषणा MAJOR_OBSERVER_ACC_ACK             28

#घोषणा DEBUG_PTR_SIGNATURE     0xABCD	/* signature क्रम the debug parameter poपूर्णांकer */

/* command codes (1st byte) */
प्रकार क्रमागत अणु
	CMD_SET_ONE_MAJOR = 1,		/* mask in one major. 2nd byte in the command is the major code */
	CMD_UNSET_ONE_MAJOR = 2,	/* mask out one major. 2nd byte in the command is the major code */
	CMD_SET_ALL_MAJORS = 3,		/* set the major prपूर्णांक mask. the full mask is in the data DWORD */
	CMD_SET_VERBOSITY = 4		/* set verbosity level */
पूर्ण DBG_commands;

/* command signature */
#घोषणा CMD_SIGNATURE	0xAABBCC00

/* shared macros in traces infraकाष्ठाure */
/* increment the poपूर्णांकer cyclicly */
#घोषणा DBG_NEXT_ITEM(x, max_items) (((x + 1) >= max_items) ? 0 : x + 1)
#घोषणा DBG_PREV_ITEM(x, max_items) ((x) ? x - 1 : max_items - 1)

#घोषणा FIELD_MASK(width) (((1 << (width)) - 1))
#घोषणा FIELD_PACK(value, mask, offset) (((value) & (mask)) << (offset))
#घोषणा FIELD_UNPACK(value, mask, offset) (((value) >> (offset)) & (mask))

#घोषणा FIELD_VALUE_OFFSET		(0)
#घोषणा FIELD_VALUE_WIDTH		(16)
#घोषणा FIELD_VALUE_MASK		FIELD_MASK(FIELD_VALUE_WIDTH)
#घोषणा FIELD_VALUE_PACK(f)		FIELD_PACK(f, FIELD_VALUE_MASK, FIELD_VALUE_OFFSET)
#घोषणा FIELD_VALUE_UNPACK(f)		FIELD_UNPACK(f, FIELD_VALUE_MASK, FIELD_VALUE_OFFSET)

#घोषणा FIELD_MINOR_OFFSET		(FIELD_VALUE_OFFSET + FIELD_VALUE_WIDTH)
#घोषणा FIELD_MINOR_WIDTH		(8)
#घोषणा FIELD_MINOR_MASK		FIELD_MASK(FIELD_MINOR_WIDTH)
#घोषणा FIELD_MINOR_PACK(f)		FIELD_PACK(f, FIELD_MINOR_MASK, FIELD_MINOR_OFFSET)
#घोषणा FIELD_MINOR_UNPACK(f)		FIELD_UNPACK(f, FIELD_MINOR_MASK, FIELD_MINOR_OFFSET)

#घोषणा FIELD_MAJOR_OFFSET		(FIELD_MINOR_OFFSET + FIELD_MINOR_WIDTH)
#घोषणा FIELD_MAJOR_WIDTH		(5)
#घोषणा FIELD_MAJOR_MASK		FIELD_MASK(FIELD_MAJOR_WIDTH)
#घोषणा FIELD_MAJOR_PACK(f)		FIELD_PACK(f, FIELD_MAJOR_MASK, FIELD_MAJOR_OFFSET)
#घोषणा FIELD_MAJOR_UNPACK(f)		FIELD_UNPACK(f, FIELD_MAJOR_MASK, FIELD_MAJOR_OFFSET)

/* क्रम quick traces - only insertion, compatible with the regular poपूर्णांक */
#घोषणा FIELD_FULL_MAJOR_WIDTH		(8)
#घोषणा FIELD_FULL_MAJOR_MASK		FIELD_MASK(FIELD_FULL_MAJOR_WIDTH)
#घोषणा FIELD_FULL_MAJOR_PACK(f)	FIELD_PACK(f, FIELD_FULL_MAJOR_MASK, FIELD_MAJOR_OFFSET)

/* The following 2 fields are used only when FIELD_TID value is 111b.
 * it means we करोn't want to use thपढ़ो id, but क्रमmat. In this हाल,
 * the last 2 MSB bits of the major field will indicates the क्रमmat
 */
#घोषणा FIELD_MAJOR_W_FMT_OFFSET	FIELD_MAJOR_OFFSET
#घोषणा FIELD_MAJOR_W_FMT_WIDTH		(3)
#घोषणा FIELD_MAJOR_W_FMT_MASK		FIELD_MASK(FIELD_MAJOR_W_FMT_WIDTH)
#घोषणा FIELD_MAJOR_W_FMT_PACK(f)	FIELD_PACK(f, FIELD_MAJOR_W_FMT_MASK, FIELD_MAJOR_W_FMT_OFFSET)
#घोषणा FIELD_MAJOR_W_FMT_UNPACK(f)	FIELD_UNPACK(f, FIELD_MAJOR_W_FMT_MASK, FIELD_MAJOR_W_FMT_OFFSET)

#घोषणा FIELD_FORMAT_OFFSET		(FIELD_MAJOR_OFFSET + FIELD_MAJOR_W_FMT_WIDTH)
#घोषणा FIELD_FORMAT_WIDTH		(2)
#घोषणा FIELD_FORMAT_MASK		FIELD_MASK(FIELD_MAJOR_W_FMT_WIDTH)
#घोषणा FIELD_FORMAT_PACK(f)		FIELD_PACK(f, FIELD_FORMAT_MASK, FIELD_FORMAT_OFFSET)
#घोषणा FIELD_FORMAT_UNPACK(f)		FIELD_UNPACK(f, FIELD_FORMAT_MASK, FIELD_FORMAT_OFFSET)

#घोषणा FIELD_TID_SEL_FORMAT_PAT	(7)

#घोषणा FIELD_TID_OFFSET		(FIELD_MAJOR_OFFSET + FIELD_MAJOR_WIDTH)
#घोषणा FIELD_TID_WIDTH			(3)
#घोषणा FIELD_TID_MASK			FIELD_MASK(FIELD_TID_WIDTH)
#घोषणा FIELD_TID_PACK(f)		FIELD_PACK(f, FIELD_TID_MASK, FIELD_TID_OFFSET)
#घोषणा FIELD_TID_UNPACK(f)		FIELD_UNPACK(f, FIELD_TID_MASK, FIELD_TID_OFFSET)

#घोषणा FIELD_VALUE_24_OFFSET		(0)
#घोषणा FIELD_VALUE_24_WIDTH		(24)
#घोषणा FIELD_VALUE_24_MASK		FIELD_MASK(FIELD_VALUE_24_WIDTH)
#घोषणा FIELD_VALUE_24_PACK(f)		FIELD_PACK(f, FIELD_VALUE_24_MASK, FIELD_VALUE_24_OFFSET)
#घोषणा FIELD_VALUE_24_UNPACK(f)	FIELD_UNPACK(f, FIELD_VALUE_24_MASK, FIELD_VALUE_24_OFFSET)

#घोषणा PACK_TRACEPOINT(tid, major, minor, value)	\
	(FIELD_TID_PACK(tid) | FIELD_MAJOR_PACK(major) | FIELD_MINOR_PACK(minor) | FIELD_VALUE_PACK(value))

#घोषणा PACK_QUICK_TRACEPOINT(major, minor)	\
	(FIELD_FULL_MAJOR_PACK(major) | FIELD_MINOR_PACK(minor))

#घोषणा PACK_FORMATTED_TRACEPOINT(क्रमmat, major, minor, value)	\
	(FIELD_TID_PACK(FIELD_TID_SEL_FORMAT_PAT) | FIELD_FORMAT_PACK(क्रमmat) | FIELD_MAJOR_PACK(major) | FIELD_MINOR_PACK(minor) | FIELD_VALUE_PACK(value))

#घोषणा PACK_TRACE_VALUE24(major, value)	\
	(FIELD_TID_PACK(FIELD_TID_SEL_FORMAT_PAT) | FIELD_MAJOR_PACK(major) | FIELD_VALUE_24_PACK(value))

#पूर्ण_अगर /* __CSS_TRACE_H_ */
