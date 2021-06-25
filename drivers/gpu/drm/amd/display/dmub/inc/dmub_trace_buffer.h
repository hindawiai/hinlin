<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */
#अगर_अघोषित _DMUB_TRACE_BUFFER_H_
#घोषणा _DMUB_TRACE_BUFFER_H_

#समावेश "dmub_cmd.h"

#घोषणा LOAD_DMCU_FW	1
#घोषणा LOAD_PHY_FW	2


क्रमागत dmucb_trace_code अणु
	DMCUB__UNKNOWN,
	DMCUB__MAIN_BEGIN,
	DMCUB__PHY_INIT_BEGIN,
	DMCUB__PHY_FW_SRAM_LOAD_BEGIN,
	DMCUB__PHY_FW_SRAM_LOAD_END,
	DMCUB__PHY_INIT_POLL_DONE,
	DMCUB__PHY_INIT_END,
	DMCUB__DMCU_ERAM_LOAD_BEGIN,
	DMCUB__DMCU_ERAM_LOAD_END,
	DMCUB__DMCU_ISR_LOAD_BEGIN,
	DMCUB__DMCU_ISR_LOAD_END,
	DMCUB__MAIN_IDLE,
	DMCUB__PERF_TRACE,
	DMCUB__PG_DONE,
पूर्ण;

काष्ठा dmcub_trace_buf_entry अणु
	क्रमागत dmucb_trace_code trace_code;
	uपूर्णांक32_t tick_count;
	uपूर्णांक32_t param0;
	uपूर्णांक32_t param1;
पूर्ण;

#घोषणा TRACE_BUF_SIZE (1024) //1 kB
#घोषणा PERF_TRACE_MAX_ENTRY ((TRACE_BUF_SIZE - 8)/माप(काष्ठा dmcub_trace_buf_entry))


काष्ठा dmcub_trace_buf अणु
	uपूर्णांक32_t entry_count;
	uपूर्णांक32_t clk_freq;
	काष्ठा dmcub_trace_buf_entry entries[PERF_TRACE_MAX_ENTRY];
पूर्ण;

#पूर्ण_अगर /* _DMUB_TRACE_BUFFER_H_ */
