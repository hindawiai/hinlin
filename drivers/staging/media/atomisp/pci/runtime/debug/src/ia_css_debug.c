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

#समावेश "debug.h"

#अगर_अघोषित __INLINE_INPUT_SYSTEM__
#घोषणा __INLINE_INPUT_SYSTEM__
#पूर्ण_अगर
#अगर_अघोषित __INLINE_IBUF_CTRL__
#घोषणा __INLINE_IBUF_CTRL__
#पूर्ण_अगर
#अगर_अघोषित __INLINE_CSI_RX__
#घोषणा __INLINE_CSI_RX__
#पूर्ण_अगर
#अगर_अघोषित __INLINE_PIXELGEN__
#घोषणा __INLINE_PIXELGEN__
#पूर्ण_अगर
#अगर_अघोषित __INLINE_STREAM2MMIO__
#घोषणा __INLINE_STREAM2MMIO__
#पूर्ण_अगर

#समावेश <linux/माला.स> /* क्रम strscpy() */

#समावेश "ia_css_debug.h"
#समावेश "ia_css_debug_pipe.h"
#समावेश "ia_css_irq.h"
#समावेश "ia_css_stream.h"
#समावेश "ia_css_pipeline.h"
#समावेश "ia_css_isp_param.h"
#समावेश "sh_css_params.h"
#समावेश "ia_css_bufq.h"
/* ISP2401 */
#समावेश "ia_css_queue.h"

#समावेश "ia_css_isp_params.h"

#समावेश "system_local.h"
#समावेश "assert_support.h"
#समावेश "print_support.h"

#समावेश "fifo_monitor.h"

#समावेश "input_formatter.h"
#समावेश "dma.h"
#समावेश "irq.h"
#समावेश "gp_device.h"
#समावेश "sp.h"
#समावेश "isp.h"
#समावेश "type_support.h"
#समावेश "math_support.h" /* CEIL_DIV */
#समावेश "input_system.h"	/* input_क्रमmatter_reg_load */
#समावेश "ia_css_tagger_common.h"

#समावेश "sh_css_internal.h"
#समावेश "ia_css_isys.h"
#समावेश "sh_css_sp.h"		/* sh_css_sp_get_debug_state() */

#समावेश "css_trace.h"      /* tracer */

#समावेश "device_access.h"	/* क्रम ia_css_device_load_uपूर्णांक32 */

/* Include all kernel host पूर्णांकerfaces क्रम ISP1 */
#समावेश "anr/anr_1.0/ia_css_anr.host.h"
#समावेश "cnr/cnr_1.0/ia_css_cnr.host.h"
#समावेश "csc/csc_1.0/ia_css_csc.host.h"
#समावेश "de/de_1.0/ia_css_de.host.h"
#समावेश "dp/dp_1.0/ia_css_dp.host.h"
#समावेश "bnr/bnr_1.0/ia_css_bnr.host.h"
#समावेश "fpn/fpn_1.0/ia_css_fpn.host.h"
#समावेश "gc/gc_1.0/ia_css_gc.host.h"
#समावेश "ob/ob_1.0/ia_css_ob.host.h"
#समावेश "s3a/s3a_1.0/ia_css_s3a.host.h"
#समावेश "sc/sc_1.0/ia_css_sc.host.h"
#समावेश "tnr/tnr_1.0/ia_css_tnr.host.h"
#समावेश "uds/uds_1.0/ia_css_uds_param.h"
#समावेश "wb/wb_1.0/ia_css_wb.host.h"
#समावेश "ynr/ynr_1.0/ia_css_ynr.host.h"

/* Include additional kernel host पूर्णांकerfaces क्रम ISP2 */
#समावेश "aa/aa_2/ia_css_aa2.host.h"
#समावेश "anr/anr_2/ia_css_anr2.host.h"
#समावेश "cnr/cnr_2/ia_css_cnr2.host.h"
#समावेश "de/de_2/ia_css_de2.host.h"
#समावेश "gc/gc_2/ia_css_gc2.host.h"
#समावेश "ynr/ynr_2/ia_css_ynr2.host.h"

#घोषणा DPG_START "ia_css_debug_pipe_graph_dump_start "
#घोषणा DPG_END   " ia_css_debug_pipe_graph_dump_end\n"

#घोषणा ENABLE_LINE_MAX_LENGTH (25)

/*
 * TODO:SH_CSS_MAX_SP_THREADS is not the max number of sp thपढ़ोs
 * future rework should fix this and हटाओ the define MAX_THREAD_NUM
 */
#घोषणा MAX_THREAD_NUM (SH_CSS_MAX_SP_THREADS + SH_CSS_MAX_SP_INTERNAL_THREADS)

अटल काष्ठा pipe_graph_class अणु
	bool करो_init;
	पूर्णांक height;
	पूर्णांक width;
	पूर्णांक eff_height;
	पूर्णांक eff_width;
	क्रमागत atomisp_input_क्रमmat stream_क्रमmat;
पूर्ण pg_inst = अणुtrue, 0, 0, 0, 0, N_ATOMISP_INPUT_FORMATपूर्ण;

अटल स्थिर अक्षर *स्थिर queue_id_to_str[] = अणु
	/* [SH_CSS_QUEUE_A_ID]     =*/ "queue_A",
	/* [SH_CSS_QUEUE_B_ID]     =*/ "queue_B",
	/* [SH_CSS_QUEUE_C_ID]     =*/ "queue_C",
	/* [SH_CSS_QUEUE_D_ID]     =*/ "queue_D",
	/* [SH_CSS_QUEUE_E_ID]     =*/ "queue_E",
	/* [SH_CSS_QUEUE_F_ID]     =*/ "queue_F",
	/* [SH_CSS_QUEUE_G_ID]     =*/ "queue_G",
	/* [SH_CSS_QUEUE_H_ID]     =*/ "queue_H"
पूर्ण;

अटल स्थिर अक्षर *स्थिर pipe_id_to_str[] = अणु
	/* [IA_CSS_PIPE_ID_PREVIEW]   =*/ "preview",
	/* [IA_CSS_PIPE_ID_COPY]      =*/ "copy",
	/* [IA_CSS_PIPE_ID_VIDEO]     =*/ "video",
	/* [IA_CSS_PIPE_ID_CAPTURE]   =*/ "capture",
	/* [IA_CSS_PIPE_ID_YUVPP]     =*/ "yuvpp",
	/* [IA_CSS_PIPE_ID_ACC]       =*/ "accelerator"
पूर्ण;

अटल अक्षर करोt_id_input_bin[SH_CSS_MAX_BINARY_NAME + 10];
अटल अक्षर ring_buffer[200];

व्योम ia_css_debug_dtrace(अचिन्हित पूर्णांक level, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	ia_css_debug_vdtrace(level, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

अटल व्योम debug_dump_दीर्घ_array_क्रमmatted(
    स्थिर sp_ID_t sp_id,
    hrt_address stack_sp_addr,
    अचिन्हित पूर्णांक stack_size)
अणु
	अचिन्हित पूर्णांक i;
	u32 val;
	u32 addr = (uपूर्णांक32_t)stack_sp_addr;
	u32 stack_size_words = CEIL_DIV(stack_size, माप(uपूर्णांक32_t));

	/* When size is not multiple of four, last word is only relevant क्रम
	 * reमुख्यing bytes */
	क्रम (i = 0; i < stack_size_words; i++) अणु
		val = sp_dmem_load_uपूर्णांक32(sp_id, (hrt_address)addr);
		अगर ((i % 8) == 0)
			ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "\n");

		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "0x%08x ", val);
		addr += माप(uपूर्णांक32_t);
	पूर्ण

	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "\n");
पूर्ण

अटल व्योम debug_dump_sp_stack_info(
    स्थिर sp_ID_t sp_id)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_thपढ़ोs_stack;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_thपढ़ोs_stack_size;
	u32 stack_sizes[MAX_THREAD_NUM];
	u32 stack_sp_addr[MAX_THREAD_NUM];
	अचिन्हित पूर्णांक i;

	fw = &sh_css_sp_fw;

	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "sp_id(%u) stack info\n", sp_id);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "from objects stack_addr_offset:0x%x stack_size_offset:0x%x\n",
			    fw->info.sp.thपढ़ोs_stack,
			    fw->info.sp.thपढ़ोs_stack_size);

	HIVE_ADDR_sp_thपढ़ोs_stack = fw->info.sp.thपढ़ोs_stack;
	HIVE_ADDR_sp_thपढ़ोs_stack_size = fw->info.sp.thपढ़ोs_stack_size;

	अगर (fw->info.sp.thपढ़ोs_stack == 0 ||
	    fw->info.sp.thपढ़ोs_stack_size == 0)
		वापस;

	(व्योम)HIVE_ADDR_sp_thपढ़ोs_stack;
	(व्योम)HIVE_ADDR_sp_thपढ़ोs_stack_size;

	sp_dmem_load(sp_id,
		     (अचिन्हित पूर्णांक)sp_address_of(sp_thपढ़ोs_stack),
		     &stack_sp_addr, माप(stack_sp_addr));
	sp_dmem_load(sp_id,
		     (अचिन्हित पूर्णांक)sp_address_of(sp_thपढ़ोs_stack_size),
		     &stack_sizes, माप(stack_sizes));

	क्रम (i = 0 ; i < MAX_THREAD_NUM; i++) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
				    "thread: %u stack_addr: 0x%08x stack_size: %u\n",
				    i, stack_sp_addr[i], stack_sizes[i]);
		debug_dump_दीर्घ_array_क्रमmatted(sp_id, (hrt_address)stack_sp_addr[i],
						stack_sizes[i]);
	पूर्ण
पूर्ण

व्योम ia_css_debug_dump_sp_stack_info(व्योम)
अणु
	debug_dump_sp_stack_info(SP0_ID);
पूर्ण

व्योम ia_css_debug_set_dtrace_level(स्थिर अचिन्हित पूर्णांक trace_level)
अणु
	dbg_level = trace_level;
	वापस;
पूर्ण

अचिन्हित पूर्णांक ia_css_debug_get_dtrace_level(व्योम)
अणु
	वापस dbg_level;
पूर्ण

अटल स्थिर अक्षर *debug_stream_क्रमmat2str(स्थिर क्रमागत atomisp_input_क्रमmat
	stream_क्रमmat)
अणु
	चयन (stream_क्रमmat) अणु
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY:
		वापस "yuv420-8-legacy";
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:
		वापस "yuv420-8";
	हाल ATOMISP_INPUT_FORMAT_YUV420_10:
		वापस "yuv420-10";
	हाल ATOMISP_INPUT_FORMAT_YUV420_16:
		वापस "yuv420-16";
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:
		वापस "yuv422-8";
	हाल ATOMISP_INPUT_FORMAT_YUV422_10:
		वापस "yuv422-10";
	हाल ATOMISP_INPUT_FORMAT_YUV422_16:
		वापस "yuv422-16";
	हाल ATOMISP_INPUT_FORMAT_RGB_444:
		वापस "rgb444";
	हाल ATOMISP_INPUT_FORMAT_RGB_555:
		वापस "rgb555";
	हाल ATOMISP_INPUT_FORMAT_RGB_565:
		वापस "rgb565";
	हाल ATOMISP_INPUT_FORMAT_RGB_666:
		वापस "rgb666";
	हाल ATOMISP_INPUT_FORMAT_RGB_888:
		वापस "rgb888";
	हाल ATOMISP_INPUT_FORMAT_RAW_6:
		वापस "raw6";
	हाल ATOMISP_INPUT_FORMAT_RAW_7:
		वापस "raw7";
	हाल ATOMISP_INPUT_FORMAT_RAW_8:
		वापस "raw8";
	हाल ATOMISP_INPUT_FORMAT_RAW_10:
		वापस "raw10";
	हाल ATOMISP_INPUT_FORMAT_RAW_12:
		वापस "raw12";
	हाल ATOMISP_INPUT_FORMAT_RAW_14:
		वापस "raw14";
	हाल ATOMISP_INPUT_FORMAT_RAW_16:
		वापस "raw16";
	हाल ATOMISP_INPUT_FORMAT_BINARY_8:
		वापस "binary8";
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT1:
		वापस "generic-short1";
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT2:
		वापस "generic-short2";
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT3:
		वापस "generic-short3";
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT4:
		वापस "generic-short4";
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT5:
		वापस "generic-short5";
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT6:
		वापस "generic-short6";
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT7:
		वापस "generic-short7";
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT8:
		वापस "generic-short8";
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_SHIFT:
		वापस "yuv420-8-shift";
	हाल ATOMISP_INPUT_FORMAT_YUV420_10_SHIFT:
		वापस "yuv420-10-shift";
	हाल ATOMISP_INPUT_FORMAT_EMBEDDED:
		वापस "embedded-8";
	हाल ATOMISP_INPUT_FORMAT_USER_DEF1:
		वापस "user-def-8-type-1";
	हाल ATOMISP_INPUT_FORMAT_USER_DEF2:
		वापस "user-def-8-type-2";
	हाल ATOMISP_INPUT_FORMAT_USER_DEF3:
		वापस "user-def-8-type-3";
	हाल ATOMISP_INPUT_FORMAT_USER_DEF4:
		वापस "user-def-8-type-4";
	हाल ATOMISP_INPUT_FORMAT_USER_DEF5:
		वापस "user-def-8-type-5";
	हाल ATOMISP_INPUT_FORMAT_USER_DEF6:
		वापस "user-def-8-type-6";
	हाल ATOMISP_INPUT_FORMAT_USER_DEF7:
		वापस "user-def-8-type-7";
	हाल ATOMISP_INPUT_FORMAT_USER_DEF8:
		वापस "user-def-8-type-8";

	शेष:
		निश्चित(!"Unknown stream format");
		वापस "unknown-stream-format";
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर *debug_frame_क्रमmat2str(स्थिर क्रमागत ia_css_frame_क्रमmat
	frame_क्रमmat)
अणु
	चयन (frame_क्रमmat) अणु
	हाल IA_CSS_FRAME_FORMAT_NV11:
		वापस "NV11";
	हाल IA_CSS_FRAME_FORMAT_NV12:
		वापस "NV12";
	हाल IA_CSS_FRAME_FORMAT_NV12_16:
		वापस "NV12_16";
	हाल IA_CSS_FRAME_FORMAT_NV12_TILEY:
		वापस "NV12_TILEY";
	हाल IA_CSS_FRAME_FORMAT_NV16:
		वापस "NV16";
	हाल IA_CSS_FRAME_FORMAT_NV21:
		वापस "NV21";
	हाल IA_CSS_FRAME_FORMAT_NV61:
		वापस "NV61";
	हाल IA_CSS_FRAME_FORMAT_YV12:
		वापस "YV12";
	हाल IA_CSS_FRAME_FORMAT_YV16:
		वापस "YV16";
	हाल IA_CSS_FRAME_FORMAT_YUV420:
		वापस "YUV420";
	हाल IA_CSS_FRAME_FORMAT_YUV420_16:
		वापस "YUV420_16";
	हाल IA_CSS_FRAME_FORMAT_YUV422:
		वापस "YUV422";
	हाल IA_CSS_FRAME_FORMAT_YUV422_16:
		वापस "YUV422_16";
	हाल IA_CSS_FRAME_FORMAT_UYVY:
		वापस "UYVY";
	हाल IA_CSS_FRAME_FORMAT_YUYV:
		वापस "YUYV";
	हाल IA_CSS_FRAME_FORMAT_YUV444:
		वापस "YUV444";
	हाल IA_CSS_FRAME_FORMAT_YUV_LINE:
		वापस "YUV_LINE";
	हाल IA_CSS_FRAME_FORMAT_RAW:
		वापस "RAW";
	हाल IA_CSS_FRAME_FORMAT_RGB565:
		वापस "RGB565";
	हाल IA_CSS_FRAME_FORMAT_PLANAR_RGB888:
		वापस "PLANAR_RGB888";
	हाल IA_CSS_FRAME_FORMAT_RGBA888:
		वापस "RGBA888";
	हाल IA_CSS_FRAME_FORMAT_QPLANE6:
		वापस "QPLANE6";
	हाल IA_CSS_FRAME_FORMAT_BINARY_8:
		वापस "BINARY_8";
	हाल IA_CSS_FRAME_FORMAT_MIPI:
		वापस "MIPI";
	हाल IA_CSS_FRAME_FORMAT_RAW_PACKED:
		वापस "RAW_PACKED";
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_8:
		वापस "CSI_MIPI_YUV420_8";
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8:
		वापस "CSI_MIPI_LEGACY_YUV420_8";
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_10:
		वापस "CSI_MIPI_YUV420_10";

	शेष:
		निश्चित(!"Unknown frame format");
		वापस "unknown-frame-format";
	पूर्ण
पूर्ण

अटल व्योम debug_prपूर्णांक_sp_state(स्थिर sp_state_t *state, स्थिर अक्षर *cell)
अणु
	निश्चित(cell);
	निश्चित(state);

	ia_css_debug_dtrace(2, "%s state:\n", cell);
	ia_css_debug_dtrace(2, "\t%-32s: 0x%X\n", "PC", state->pc);
	ia_css_debug_dtrace(2, "\t%-32s: 0x%X\n", "Status register",
			    state->status_रेजिस्टर);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "Is broken", state->is_broken);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "Is idle", state->is_idle);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "Is sleeping",
			    state->is_sleeping);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "Is stalling",
			    state->is_stalling);
	वापस;
पूर्ण

अटल व्योम debug_prपूर्णांक_isp_state(स्थिर isp_state_t *state, स्थिर अक्षर *cell)
अणु
	निश्चित(state);
	निश्चित(cell);

	ia_css_debug_dtrace(2, "%s state:\n", cell);
	ia_css_debug_dtrace(2, "\t%-32s: 0x%X\n", "PC", state->pc);
	ia_css_debug_dtrace(2, "\t%-32s: 0x%X\n", "Status register",
			    state->status_रेजिस्टर);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "Is broken", state->is_broken);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "Is idle", state->is_idle);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "Is sleeping",
			    state->is_sleeping);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "Is stalling",
			    state->is_stalling);
	वापस;
पूर्ण

व्योम ia_css_debug_dump_isp_state(व्योम)
अणु
	isp_state_t state;
	isp_stall_t stall;

	isp_get_state(ISP0_ID, &state, &stall);

	debug_prपूर्णांक_isp_state(&state, "ISP");

	अगर (state.is_stalling) अणु
		अगर (!IS_ISP2401) अणु
			ia_css_debug_dtrace(2, "\t%-32s: %d\n",
					    "[0] if_prim_a_FIFO stalled", stall.fअगरo0);
			ia_css_debug_dtrace(2, "\t%-32s: %d\n",
					    "[1] if_prim_b_FIFO stalled", stall.fअगरo1);
		पूर्ण
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "[2] dma_FIFO stalled",
				    stall.fअगरo2);

		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "[3] gdc0_FIFO stalled",
				    stall.fअगरo3);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "[4] gdc1_FIFO stalled",
				    stall.fअगरo4);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "[5] gpio_FIFO stalled",
				    stall.fअगरo5);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "[6] sp_FIFO stalled",
				    stall.fअगरo6);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n",
				    "status & control stalled",
				    stall.stat_ctrl);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "dmem stalled",
				    stall.dmem);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "vmem stalled",
				    stall.vmem);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "vamem1 stalled",
				    stall.vamem1);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "vamem2 stalled",
				    stall.vamem2);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "vamem3 stalled",
				    stall.vamem3);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "hmem stalled",
				    stall.hmem);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "pmem stalled",
				    stall.pmem);
	पूर्ण
	वापस;
पूर्ण

व्योम ia_css_debug_dump_sp_state(व्योम)
अणु
	sp_state_t state;
	sp_stall_t stall;

	sp_get_state(SP0_ID, &state, &stall);
	debug_prपूर्णांक_sp_state(&state, "SP");
	अगर (state.is_stalling) अणु
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "isys_FIFO stalled",
				    stall.fअगरo0);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "if_sec_FIFO stalled",
				    stall.fअगरo1);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n",
				    "str_to_mem_FIFO stalled", stall.fअगरo2);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "dma_FIFO stalled",
				    stall.fअगरo3);
		अगर (!IS_ISP2401)
			ia_css_debug_dtrace(2, "\t%-32s: %d\n",
					    "if_prim_a_FIFO stalled", stall.fअगरo4);

		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "isp_FIFO stalled",
				    stall.fअगरo5);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "gp_FIFO stalled",
				    stall.fअगरo6);
		अगर (!IS_ISP2401)
			ia_css_debug_dtrace(2, "\t%-32s: %d\n",
					    "if_prim_b_FIFO stalled", stall.fअगरo7);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "gdc0_FIFO stalled",
				    stall.fअगरo8);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "gdc1_FIFO stalled",
				    stall.fअगरo9);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "irq FIFO stalled",
				    stall.fअगरoa);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "dmem stalled",
				    stall.dmem);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n",
				    "control master stalled",
				    stall.control_master);
		ia_css_debug_dtrace(2, "\t%-32s: %d\n",
				    "i-cache master stalled",
				    stall.icache_master);
	पूर्ण
	ia_css_debug_dump_trace();
	वापस;
पूर्ण

अटल व्योम debug_prपूर्णांक_fअगरo_channel_state(स्थिर fअगरo_channel_state_t *state,
	स्थिर अक्षर *descr)
अणु
	निश्चित(state);
	निश्चित(descr);

	ia_css_debug_dtrace(2, "FIFO channel: %s\n", descr);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "source valid",
			    state->src_valid);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "fifo accept",
			    state->fअगरo_accept);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "fifo valid",
			    state->fअगरo_valid);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "sink accept",
			    state->sink_accept);
	वापस;
पूर्ण

व्योम ia_css_debug_dump_pअगर_a_isp_fअगरo_state(व्योम)
अणु
	fअगरo_channel_state_t pअगर_to_isp, isp_to_pअगर;

	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_IF0_TO_ISP0, &pअगर_to_isp);
	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_ISP0_TO_IF0, &isp_to_pअगर);
	debug_prपूर्णांक_fअगरo_channel_state(&pअगर_to_isp, "Primary IF A to ISP");
	debug_prपूर्णांक_fअगरo_channel_state(&isp_to_pअगर, "ISP to Primary IF A");
पूर्ण

व्योम ia_css_debug_dump_pअगर_b_isp_fअगरo_state(व्योम)
अणु
	fअगरo_channel_state_t pअगर_to_isp, isp_to_pअगर;

	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_IF1_TO_ISP0, &pअगर_to_isp);
	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_ISP0_TO_IF1, &isp_to_pअगर);
	debug_prपूर्णांक_fअगरo_channel_state(&pअगर_to_isp, "Primary IF B to ISP");
	debug_prपूर्णांक_fअगरo_channel_state(&isp_to_pअगर, "ISP to Primary IF B");
पूर्ण

व्योम ia_css_debug_dump_str2mem_sp_fअगरo_state(व्योम)
अणु
	fअगरo_channel_state_t s2m_to_sp, sp_to_s2m;

	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_STREAM2MEM0_TO_SP0, &s2m_to_sp);
	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_SP0_TO_STREAM2MEM0, &sp_to_s2m);
	debug_prपूर्णांक_fअगरo_channel_state(&s2m_to_sp, "Stream-to-memory to SP");
	debug_prपूर्णांक_fअगरo_channel_state(&sp_to_s2m, "SP to stream-to-memory");
पूर्ण

#अगर_अघोषित ISP2401
अटल व्योम debug_prपूर्णांक_अगर_state(input_क्रमmatter_state_t *state, स्थिर अक्षर *id)
अणु
	अचिन्हित पूर्णांक val;

	स्थिर अक्षर *st_vsync_active_low =
	    (state->vsync_active_low ? "low" : "high");
	स्थिर अक्षर *st_hsync_active_low =
	    (state->hsync_active_low ? "low" : "high");

	स्थिर अक्षर *fsm_sync_status_str = "unknown";
	स्थिर अक्षर *fsm_crop_status_str = "unknown";
	स्थिर अक्षर *fsm_padding_status_str = "unknown";

	पूर्णांक st_stline = state->start_line;
	पूर्णांक st_stcol = state->start_column;
	पूर्णांक st_crpht = state->cropped_height;
	पूर्णांक st_crpwd = state->cropped_width;
	पूर्णांक st_verdcm = state->ver_decimation;
	पूर्णांक st_hordcm = state->hor_decimation;
	पूर्णांक st_ver_deपूर्णांकerleaving = state->ver_deपूर्णांकerleaving;
	पूर्णांक st_hor_deपूर्णांकerleaving = state->hor_deपूर्णांकerleaving;
	पूर्णांक st_leftpd = state->left_padding;
	पूर्णांक st_eoloff = state->eol_offset;
	पूर्णांक st_vmstartaddr = state->vmem_start_address;
	पूर्णांक st_vmendaddr = state->vmem_end_address;
	पूर्णांक st_vmincr = state->vmem_increment;
	पूर्णांक st_yuv420 = state->is_yuv420;
	पूर्णांक st_allow_fअगरo_overflow = state->allow_fअगरo_overflow;
	पूर्णांक st_block_fअगरo_when_no_req = state->block_fअगरo_when_no_req;

	निश्चित(state);
	ia_css_debug_dtrace(2, "InputFormatter State (%s):\n", id);

	ia_css_debug_dtrace(2, "\tConfiguration:\n");

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Start line", st_stline);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Start column", st_stcol);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Cropped height", st_crpht);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Cropped width", st_crpwd);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Ver decimation", st_verdcm);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Hor decimation", st_hordcm);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Ver deinterleaving", st_ver_deपूर्णांकerleaving);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Hor deinterleaving", st_hor_deपूर्णांकerleaving);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Left padding", st_leftpd);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "EOL offset (bytes)", st_eoloff);
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%06X\n",
			    "VMEM start address", st_vmstartaddr);
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%06X\n",
			    "VMEM end address", st_vmendaddr);
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%06X\n",
			    "VMEM increment", st_vmincr);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "YUV 420 format", st_yuv420);
	ia_css_debug_dtrace(2, "\t\t%-32s: Active %s\n",
			    "Vsync", st_vsync_active_low);
	ia_css_debug_dtrace(2, "\t\t%-32s: Active %s\n",
			    "Hsync", st_hsync_active_low);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Allow FIFO overflow", st_allow_fअगरo_overflow);
	/* Flag that tells whether the IF gives backpressure on frames */
	/*
	 * FYI, this is only on the frame request (indicate), when the IF has
	 * synch'd on a frame it will always give back pressure
	 */
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Block when no request", st_block_fअगरo_when_no_req);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "IF_BLOCKED_FIFO_NO_REQ_ADDRESS",
			    input_क्रमmatter_reg_load(INPUT_FORMATTER0_ID,
				    HIVE_IF_BLOCK_FIFO_NO_REQ_ADDRESS)
			   );

	ia_css_debug_dtrace(2, "\t%-32s:\n", "InputSwitch State");

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_input_switch_lut_reg0",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_input_चयन_lut_reg0));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_input_switch_lut_reg1",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_input_चयन_lut_reg1));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_input_switch_lut_reg2",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_input_चयन_lut_reg2));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_input_switch_lut_reg3",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_input_चयन_lut_reg3));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_input_switch_lut_reg4",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_input_चयन_lut_reg4));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_input_switch_lut_reg5",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_input_चयन_lut_reg5));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_input_switch_lut_reg6",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_input_चयन_lut_reg6));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_input_switch_lut_reg7",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_input_चयन_lut_reg7));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_input_switch_fsync_lut",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_input_चयन_fsync_lut));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_srst",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_srst));

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "_REG_GP_IFMT_slv_reg_srst",
			    gp_device_reg_load(GP_DEVICE0_ID,
					       _REG_GP_IFMT_slv_reg_srst));

	ia_css_debug_dtrace(2, "\tFSM Status:\n");

	val = state->fsm_sync_status;

	अगर (val > 7)
		fsm_sync_status_str = "ERROR";

	चयन (val & 0x7) अणु
	हाल 0:
		fsm_sync_status_str = "idle";
		अवरोध;
	हाल 1:
		fsm_sync_status_str = "request frame";
		अवरोध;
	हाल 2:
		fsm_sync_status_str = "request lines";
		अवरोध;
	हाल 3:
		fsm_sync_status_str = "request vectors";
		अवरोध;
	हाल 4:
		fsm_sync_status_str = "send acknowledge";
		अवरोध;
	शेष:
		fsm_sync_status_str = "unknown";
		अवरोध;
	पूर्ण

	ia_css_debug_dtrace(2, "\t\t%-32s: (0x%X: %s)\n",
			    "FSM Synchronization Status", val,
			    fsm_sync_status_str);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM Synchronization Counter",
			    state->fsm_sync_counter);

	val = state->fsm_crop_status;

	अगर (val > 7)
		fsm_crop_status_str = "ERROR";

	चयन (val & 0x7) अणु
	हाल 0:
		fsm_crop_status_str = "idle";
		अवरोध;
	हाल 1:
		fsm_crop_status_str = "wait line";
		अवरोध;
	हाल 2:
		fsm_crop_status_str = "crop line";
		अवरोध;
	हाल 3:
		fsm_crop_status_str = "crop pixel";
		अवरोध;
	हाल 4:
		fsm_crop_status_str = "pass pixel";
		अवरोध;
	हाल 5:
		fsm_crop_status_str = "pass line";
		अवरोध;
	हाल 6:
		fsm_crop_status_str = "lost line";
		अवरोध;
	शेष:
		fsm_crop_status_str = "unknown";
		अवरोध;
	पूर्ण
	ia_css_debug_dtrace(2, "\t\t%-32s: (0x%X: %s)\n",
			    "FSM Crop Status", val, fsm_crop_status_str);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM Crop Line Counter",
			    state->fsm_crop_line_counter);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM Crop Pixel Counter",
			    state->fsm_crop_pixel_counter);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM Deinterleaving idx buffer",
			    state->fsm_deपूर्णांकerleaving_index);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM H decimation counter",
			    state->fsm_dec_h_counter);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM V decimation counter",
			    state->fsm_dec_v_counter);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM block V decimation counter",
			    state->fsm_dec_block_v_counter);

	val = state->fsm_padding_status;

	अगर (val > 7)
		fsm_padding_status_str = "ERROR";

	चयन (val & 0x7) अणु
	हाल 0:
		fsm_padding_status_str = "idle";
		अवरोध;
	हाल 1:
		fsm_padding_status_str = "left pad";
		अवरोध;
	हाल 2:
		fsm_padding_status_str = "write";
		अवरोध;
	हाल 3:
		fsm_padding_status_str = "right pad";
		अवरोध;
	हाल 4:
		fsm_padding_status_str = "send end of line";
		अवरोध;
	शेष:
		fsm_padding_status_str = "unknown";
		अवरोध;
	पूर्ण

	ia_css_debug_dtrace(2, "\t\t%-32s: (0x%X: %s)\n", "FSM Padding Status",
			    val, fsm_padding_status_str);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM Padding element idx counter",
			    state->fsm_padding_elem_counter);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Vector support error",
			    state->fsm_vector_support_error);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Vector support buf full",
			    state->fsm_vector_buffer_full);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Vector support",
			    state->vector_support);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Fifo sensor data lost",
			    state->sensor_data_lost);
पूर्ण

अटल व्योम debug_prपूर्णांक_अगर_bin_state(input_क्रमmatter_bin_state_t *state)
अणु
	ia_css_debug_dtrace(2, "Stream-to-memory state:\n");
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "reset", state->reset);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "input endianness",
			    state->input_endianness);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "output endianness",
			    state->output_endianness);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "bitswap", state->bitswap);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "block_synch",
			    state->block_synch);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "packet_synch",
			    state->packet_synch);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "readpostwrite_sync",
			    state->पढ़ोpostग_लिखो_synch);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "is_2ppc", state->is_2ppc);
	ia_css_debug_dtrace(2, "\t%-32s: %d\n", "en_status_update",
			    state->en_status_update);
पूर्ण

अटल व्योम ia_css_debug_dump_अगर_state(व्योम)
अणु
	input_क्रमmatter_state_t अगर_state;
	input_क्रमmatter_bin_state_t अगर_bin_state;

	input_क्रमmatter_get_state(INPUT_FORMATTER0_ID, &अगर_state);
	debug_prपूर्णांक_अगर_state(&अगर_state, "Primary IF A");
	ia_css_debug_dump_pअगर_a_isp_fअगरo_state();

	input_क्रमmatter_get_state(INPUT_FORMATTER1_ID, &अगर_state);
	debug_prपूर्णांक_अगर_state(&अगर_state, "Primary IF B");
	ia_css_debug_dump_pअगर_b_isp_fअगरo_state();

	input_क्रमmatter_bin_get_state(INPUT_FORMATTER3_ID, &अगर_bin_state);
	debug_prपूर्णांक_अगर_bin_state(&अगर_bin_state);
	ia_css_debug_dump_str2mem_sp_fअगरo_state();
पूर्ण
#पूर्ण_अगर

व्योम ia_css_debug_dump_dma_state(व्योम)
अणु
	/* note: the var below is made अटल as it is quite large;
	   अगर it is not अटल it ends up on the stack which could
	   cause issues क्रम drivers
	*/
	अटल dma_state_t state;
	पूर्णांक i, ch_id;

	स्थिर अक्षर *fsm_cmd_st_lbl = "FSM Command flag state";
	स्थिर अक्षर *fsm_ctl_st_lbl = "FSM Control flag state";
	स्थिर अक्षर *fsm_ctl_state = शून्य;
	स्थिर अक्षर *fsm_ctl_flag = शून्य;
	स्थिर अक्षर *fsm_pack_st = शून्य;
	स्थिर अक्षर *fsm_पढ़ो_st = शून्य;
	स्थिर अक्षर *fsm_ग_लिखो_st = शून्य;
	अक्षर last_cmd_str[64];

	dma_get_state(DMA0_ID, &state);
	/* Prपूर्णांक header क्रम DMA dump status */
	ia_css_debug_dtrace(2, "DMA dump status:\n");

	/* Prपूर्णांक FSM command flag state */
	अगर (state.fsm_command_idle)
		ia_css_debug_dtrace(2, "\t%-32s: %s\n", fsm_cmd_st_lbl, "IDLE");
	अगर (state.fsm_command_run)
		ia_css_debug_dtrace(2, "\t%-32s: %s\n", fsm_cmd_st_lbl, "RUN");
	अगर (state.fsm_command_stalling)
		ia_css_debug_dtrace(2, "\t%-32s: %s\n", fsm_cmd_st_lbl,
				    "STALL");
	अगर (state.fsm_command_error)
		ia_css_debug_dtrace(2, "\t%-32s: %s\n", fsm_cmd_st_lbl,
				    "ERROR");

	/* Prपूर्णांक last command aदीर्घ with the channel */
	ch_id = state.last_command_channel;

	चयन (state.last_command) अणु
	हाल DMA_COMMAND_READ:
		snम_लिखो(last_cmd_str, 64,
			 "Read 2D Block [Channel: %d]", ch_id);
		अवरोध;
	हाल DMA_COMMAND_WRITE:
		snम_लिखो(last_cmd_str, 64,
			 "Write 2D Block [Channel: %d]", ch_id);
		अवरोध;
	हाल DMA_COMMAND_SET_CHANNEL:
		snम_लिखो(last_cmd_str, 64, "Set Channel [Channel: %d]", ch_id);
		अवरोध;
	हाल DMA_COMMAND_SET_PARAM:
		snम_लिखो(last_cmd_str, 64,
			 "Set Param: %d [Channel: %d]",
			 state.last_command_param, ch_id);
		अवरोध;
	हाल DMA_COMMAND_READ_SPECIFIC:
		snम_लिखो(last_cmd_str, 64,
			 "Read Specific 2D Block [Channel: %d]", ch_id);
		अवरोध;
	हाल DMA_COMMAND_WRITE_SPECIFIC:
		snम_लिखो(last_cmd_str, 64,
			 "Write Specific 2D Block [Channel: %d]", ch_id);
		अवरोध;
	हाल DMA_COMMAND_INIT:
		snम_लिखो(last_cmd_str, 64,
			 "Init 2D Block on Device A [Channel: %d]", ch_id);
		अवरोध;
	हाल DMA_COMMAND_INIT_SPECIFIC:
		snम_लिखो(last_cmd_str, 64,
			 "Init Specific 2D Block [Channel: %d]", ch_id);
		अवरोध;
	हाल DMA_COMMAND_RST:
		snम_लिखो(last_cmd_str, 64, "DMA SW Reset");
		अवरोध;
	हाल N_DMA_COMMANDS:
		snम_लिखो(last_cmd_str, 64, "UNKNOWN");
		अवरोध;
	शेष:
		snम_लिखो(last_cmd_str, 64,
			 "unknown [Channel: %d]", ch_id);
		अवरोध;
	पूर्ण
	ia_css_debug_dtrace(2, "\t%-32s: (0x%X : %s)\n",
			    "last command received", state.last_command,
			    last_cmd_str);

	/* Prपूर्णांक DMA रेजिस्टरs */
	ia_css_debug_dtrace(2, "\t%-32s\n",
			    "DMA registers, connection group 0");
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%X\n", "Cmd Fifo Command",
			    state.current_command);
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%X\n", "Cmd Fifo Address A",
			    state.current_addr_a);
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%X\n", "Cmd Fifo Address B",
			    state.current_addr_b);

	अगर (state.fsm_ctrl_idle)
		fsm_ctl_flag = "IDLE";
	अन्यथा अगर (state.fsm_ctrl_run)
		fsm_ctl_flag = "RUN";
	अन्यथा अगर (state.fsm_ctrl_stalling)
		fsm_ctl_flag = "STAL";
	अन्यथा अगर (state.fsm_ctrl_error)
		fsm_ctl_flag = "ERROR";
	अन्यथा
		fsm_ctl_flag = "UNKNOWN";

	चयन (state.fsm_ctrl_state) अणु
	हाल DMA_CTRL_STATE_IDLE:
		fsm_ctl_state = "Idle state";
		अवरोध;
	हाल DMA_CTRL_STATE_REQ_RCV:
		fsm_ctl_state = "Req Rcv state";
		अवरोध;
	हाल DMA_CTRL_STATE_RCV:
		fsm_ctl_state = "Rcv state";
		अवरोध;
	हाल DMA_CTRL_STATE_RCV_REQ:
		fsm_ctl_state = "Rcv Req state";
		अवरोध;
	हाल DMA_CTRL_STATE_INIT:
		fsm_ctl_state = "Init state";
		अवरोध;
	हाल N_DMA_CTRL_STATES:
		fsm_ctl_state = "Unknown";
		अवरोध;
	पूर्ण

	ia_css_debug_dtrace(2, "\t\t%-32s: %s -> %s\n", fsm_ctl_st_lbl,
			    fsm_ctl_flag, fsm_ctl_state);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl source dev",
			    state.fsm_ctrl_source_dev);
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%X\n", "FSM Ctrl source addr",
			    state.fsm_ctrl_source_addr);
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%X\n", "FSM Ctrl source stride",
			    state.fsm_ctrl_source_stride);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl source width",
			    state.fsm_ctrl_source_width);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl source height",
			    state.fsm_ctrl_source_height);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl pack source dev",
			    state.fsm_ctrl_pack_source_dev);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl pack dest dev",
			    state.fsm_ctrl_pack_dest_dev);
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%X\n", "FSM Ctrl dest addr",
			    state.fsm_ctrl_dest_addr);
	ia_css_debug_dtrace(2, "\t\t%-32s: 0x%X\n", "FSM Ctrl dest stride",
			    state.fsm_ctrl_dest_stride);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl pack source width",
			    state.fsm_ctrl_pack_source_width);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl pack dest height",
			    state.fsm_ctrl_pack_dest_height);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl pack dest width",
			    state.fsm_ctrl_pack_dest_width);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl pack source elems",
			    state.fsm_ctrl_pack_source_elems);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl pack dest elems",
			    state.fsm_ctrl_pack_dest_elems);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Ctrl pack extension",
			    state.fsm_ctrl_pack_extension);

	अगर (state.pack_idle)
		fsm_pack_st = "IDLE";
	अगर (state.pack_run)
		fsm_pack_st = "RUN";
	अगर (state.pack_stalling)
		fsm_pack_st = "STALL";
	अगर (state.pack_error)
		fsm_pack_st = "ERROR";

	ia_css_debug_dtrace(2, "\t\t%-32s: %s\n", "FSM Pack flag state",
			    fsm_pack_st);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Pack cnt height",
			    state.pack_cnt_height);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Pack src cnt width",
			    state.pack_src_cnt_width);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Pack dest cnt width",
			    state.pack_dest_cnt_width);

	अगर (state.पढ़ो_state == DMA_RW_STATE_IDLE)
		fsm_पढ़ो_st = "Idle state";
	अगर (state.पढ़ो_state == DMA_RW_STATE_REQ)
		fsm_पढ़ो_st = "Req state";
	अगर (state.पढ़ो_state == DMA_RW_STATE_NEXT_LINE)
		fsm_पढ़ो_st = "Next line";
	अगर (state.पढ़ो_state == DMA_RW_STATE_UNLOCK_CHANNEL)
		fsm_पढ़ो_st = "Unlock channel";

	ia_css_debug_dtrace(2, "\t\t%-32s: %s\n", "FSM Read state",
			    fsm_पढ़ो_st);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Read cnt height",
			    state.पढ़ो_cnt_height);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Read cnt width",
			    state.पढ़ो_cnt_width);

	अगर (state.ग_लिखो_state == DMA_RW_STATE_IDLE)
		fsm_ग_लिखो_st = "Idle state";
	अगर (state.ग_लिखो_state == DMA_RW_STATE_REQ)
		fsm_ग_लिखो_st = "Req state";
	अगर (state.ग_लिखो_state == DMA_RW_STATE_NEXT_LINE)
		fsm_ग_लिखो_st = "Next line";
	अगर (state.ग_लिखो_state == DMA_RW_STATE_UNLOCK_CHANNEL)
		fsm_ग_लिखो_st = "Unlock channel";

	ia_css_debug_dtrace(2, "\t\t%-32s: %s\n", "FSM Write state",
			    fsm_ग_लिखो_st);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Write height",
			    state.ग_लिखो_height);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "FSM Write width",
			    state.ग_लिखो_width);

	क्रम (i = 0; i < HIVE_ISP_NUM_DMA_CONNS; i++) अणु
		dma_port_state_t *port = &state.port_states[i];

		ia_css_debug_dtrace(2, "\tDMA device interface %d\n", i);
		ia_css_debug_dtrace(2, "\t\tDMA internal side state\n");
		ia_css_debug_dtrace(2,
				    "\t\t\tCS:%d - We_n:%d - Run:%d - Ack:%d\n",
				    port->req_cs, port->req_we_n, port->req_run,
				    port->req_ack);
		ia_css_debug_dtrace(2, "\t\tMaster Output side state\n");
		ia_css_debug_dtrace(2,
				    "\t\t\tCS:%d - We_n:%d - Run:%d - Ack:%d\n",
				    port->send_cs, port->send_we_n,
				    port->send_run, port->send_ack);
		ia_css_debug_dtrace(2, "\t\tFifo state\n");
		अगर (port->fअगरo_state == DMA_FIFO_STATE_WILL_BE_FULL)
			ia_css_debug_dtrace(2, "\t\t\tFiFo will be full\n");
		अन्यथा अगर (port->fअगरo_state == DMA_FIFO_STATE_FULL)
			ia_css_debug_dtrace(2, "\t\t\tFifo Full\n");
		अन्यथा अगर (port->fअगरo_state == DMA_FIFO_STATE_EMPTY)
			ia_css_debug_dtrace(2, "\t\t\tFifo Empty\n");
		अन्यथा
			ia_css_debug_dtrace(2, "\t\t\tFifo state unknown\n");

		ia_css_debug_dtrace(2, "\t\tFifo counter %d\n\n",
				    port->fअगरo_counter);
	पूर्ण

	क्रम (i = 0; i < HIVE_DMA_NUM_CHANNELS; i++) अणु
		dma_channel_state_t *ch = &state.channel_states[i];

		ia_css_debug_dtrace(2, "\t%-32s: %d\n", "DMA channel register",
				    i);
		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Connection",
				    ch->connection);
		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Sign extend",
				    ch->sign_extend);
		ia_css_debug_dtrace(2, "\t\t%-32s: 0x%X\n", "Stride Dev A",
				    ch->stride_a);
		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Elems Dev A",
				    ch->elems_a);
		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Cropping Dev A",
				    ch->cropping_a);
		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Width Dev A",
				    ch->width_a);
		ia_css_debug_dtrace(2, "\t\t%-32s: 0x%X\n", "Stride Dev B",
				    ch->stride_b);
		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Elems Dev B",
				    ch->elems_b);
		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Cropping Dev B",
				    ch->cropping_b);
		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Width Dev B",
				    ch->width_b);
		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "Height", ch->height);
	पूर्ण
	ia_css_debug_dtrace(2, "\n");
	वापस;
पूर्ण

व्योम ia_css_debug_dump_dma_sp_fअगरo_state(व्योम)
अणु
	fअगरo_channel_state_t dma_to_sp, sp_to_dma;

	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_DMA0_TO_SP0, &dma_to_sp);
	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_SP0_TO_DMA0, &sp_to_dma);
	debug_prपूर्णांक_fअगरo_channel_state(&dma_to_sp, "DMA to SP");
	debug_prपूर्णांक_fअगरo_channel_state(&sp_to_dma, "SP to DMA");
	वापस;
पूर्ण

व्योम ia_css_debug_dump_dma_isp_fअगरo_state(व्योम)
अणु
	fअगरo_channel_state_t dma_to_isp, isp_to_dma;

	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_DMA0_TO_ISP0, &dma_to_isp);
	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_ISP0_TO_DMA0, &isp_to_dma);
	debug_prपूर्णांक_fअगरo_channel_state(&dma_to_isp, "DMA to ISP");
	debug_prपूर्णांक_fअगरo_channel_state(&isp_to_dma, "ISP to DMA");
	वापस;
पूर्ण

व्योम ia_css_debug_dump_isp_sp_fअगरo_state(व्योम)
अणु
	fअगरo_channel_state_t sp_to_isp, isp_to_sp;

	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_SP0_TO_ISP0, &sp_to_isp);
	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_ISP0_TO_SP0, &isp_to_sp);
	debug_prपूर्णांक_fअगरo_channel_state(&sp_to_isp, "SP to ISP");
	debug_prपूर्णांक_fअगरo_channel_state(&isp_to_sp, "ISP to SP");
	वापस;
पूर्ण

व्योम ia_css_debug_dump_isp_gdc_fअगरo_state(व्योम)
अणु
	fअगरo_channel_state_t gdc_to_isp, isp_to_gdc;

	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_GDC0_TO_ISP0, &gdc_to_isp);
	fअगरo_channel_get_state(FIFO_MONITOR0_ID,
			       FIFO_CHANNEL_ISP0_TO_GDC0, &isp_to_gdc);
	debug_prपूर्णांक_fअगरo_channel_state(&gdc_to_isp, "GDC to ISP");
	debug_prपूर्णांक_fअगरo_channel_state(&isp_to_gdc, "ISP to GDC");
	वापस;
पूर्ण

व्योम ia_css_debug_dump_all_fअगरo_state(व्योम)
अणु
	पूर्णांक i;
	fअगरo_monitor_state_t state;

	fअगरo_monitor_get_state(FIFO_MONITOR0_ID, &state);

	क्रम (i = 0; i < N_FIFO_CHANNEL; i++)
		debug_prपूर्णांक_fअगरo_channel_state(&state.fअगरo_channels[i],
					       "squepfstqkt");
	वापस;
पूर्ण

अटल व्योम debug_binary_info_prपूर्णांक(स्थिर काष्ठा ia_css_binary_xinfo *info)
अणु
	निश्चित(info);
	ia_css_debug_dtrace(2, "id = %d\n", info->sp.id);
	ia_css_debug_dtrace(2, "mode = %d\n", info->sp.pipeline.mode);
	ia_css_debug_dtrace(2, "max_input_width = %d\n", info->sp.input.max_width);
	ia_css_debug_dtrace(2, "min_output_width = %d\n",
			    info->sp.output.min_width);
	ia_css_debug_dtrace(2, "max_output_width = %d\n",
			    info->sp.output.max_width);
	ia_css_debug_dtrace(2, "top_cropping = %d\n", info->sp.pipeline.top_cropping);
	ia_css_debug_dtrace(2, "left_cropping = %d\n", info->sp.pipeline.left_cropping);
	ia_css_debug_dtrace(2, "xmem_addr = %d\n", info->xmem_addr);
	ia_css_debug_dtrace(2, "enable_vf_veceven = %d\n",
			    info->sp.enable.vf_veceven);
	ia_css_debug_dtrace(2, "enable_dis = %d\n", info->sp.enable.dis);
	ia_css_debug_dtrace(2, "enable_uds = %d\n", info->sp.enable.uds);
	ia_css_debug_dtrace(2, "enable ds = %d\n", info->sp.enable.ds);
	ia_css_debug_dtrace(2, "s3atbl_use_dmem = %d\n", info->sp.s3a.s3atbl_use_dmem);
	वापस;
पूर्ण

व्योम ia_css_debug_binary_prपूर्णांक(स्थिर काष्ठा ia_css_binary *bi)
अणु
	अचिन्हित पूर्णांक i;

	debug_binary_info_prपूर्णांक(bi->info);
	ia_css_debug_dtrace(2,
			    "input:  %dx%d, format = %d, padded width = %d\n",
			    bi->in_frame_info.res.width,
			    bi->in_frame_info.res.height,
			    bi->in_frame_info.क्रमmat,
			    bi->in_frame_info.padded_width);
	ia_css_debug_dtrace(2,
			    "internal :%dx%d, format = %d, padded width = %d\n",
			    bi->पूर्णांकernal_frame_info.res.width,
			    bi->पूर्णांकernal_frame_info.res.height,
			    bi->पूर्णांकernal_frame_info.क्रमmat,
			    bi->पूर्णांकernal_frame_info.padded_width);
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		अगर (bi->out_frame_info[i].res.width != 0) अणु
			ia_css_debug_dtrace(2,
					    "out%d:    %dx%d, format = %d, padded width = %d\n",
					    i,
					    bi->out_frame_info[i].res.width,
					    bi->out_frame_info[i].res.height,
					    bi->out_frame_info[i].क्रमmat,
					    bi->out_frame_info[i].padded_width);
		पूर्ण
	पूर्ण
	ia_css_debug_dtrace(2,
			    "vf out: %dx%d, format = %d, padded width = %d\n",
			    bi->vf_frame_info.res.width,
			    bi->vf_frame_info.res.height,
			    bi->vf_frame_info.क्रमmat,
			    bi->vf_frame_info.padded_width);
	ia_css_debug_dtrace(2, "online = %d\n", bi->online);
	ia_css_debug_dtrace(2, "input_buf_vectors = %d\n",
			    bi->input_buf_vectors);
	ia_css_debug_dtrace(2, "deci_factor_log2 = %d\n", bi->deci_factor_log2);
	ia_css_debug_dtrace(2, "vf_downscale_log2 = %d\n",
			    bi->vf_करोwnscale_log2);
	ia_css_debug_dtrace(2, "dis_deci_factor_log2 = %d\n",
			    bi->dis.deci_factor_log2);
	ia_css_debug_dtrace(2, "dis hor coef num = %d\n",
			    bi->dis.coef.pad.width);
	ia_css_debug_dtrace(2, "dis ver coef num = %d\n",
			    bi->dis.coef.pad.height);
	ia_css_debug_dtrace(2, "dis hor proj num = %d\n",
			    bi->dis.proj.pad.height);
	ia_css_debug_dtrace(2, "sctbl_width_per_color = %d\n",
			    bi->sctbl_width_per_color);
	ia_css_debug_dtrace(2, "s3atbl_width = %d\n", bi->s3atbl_width);
	ia_css_debug_dtrace(2, "s3atbl_height = %d\n", bi->s3atbl_height);
	वापस;
पूर्ण

व्योम ia_css_debug_frame_prपूर्णांक(स्थिर काष्ठा ia_css_frame *frame,
			      स्थिर अक्षर *descr)
अणु
	अक्षर *data = शून्य;

	निश्चित(frame);
	निश्चित(descr);

	data = (अक्षर *)HOST_ADDRESS(frame->data);
	ia_css_debug_dtrace(2, "frame %s (%p):\n", descr, frame);
	ia_css_debug_dtrace(2, "  resolution    = %dx%d\n",
			    frame->info.res.width, frame->info.res.height);
	ia_css_debug_dtrace(2, "  padded width  = %d\n",
			    frame->info.padded_width);
	ia_css_debug_dtrace(2, "  format        = %d\n", frame->info.क्रमmat);
	ia_css_debug_dtrace(2, "  is contiguous = %s\n",
			    frame->contiguous ? "yes" : "no");
	चयन (frame->info.क्रमmat) अणु
	हाल IA_CSS_FRAME_FORMAT_NV12:
	हाल IA_CSS_FRAME_FORMAT_NV16:
	हाल IA_CSS_FRAME_FORMAT_NV21:
	हाल IA_CSS_FRAME_FORMAT_NV61:
		ia_css_debug_dtrace(2, "  Y = %p\n",
				    data + frame->planes.nv.y.offset);
		ia_css_debug_dtrace(2, "  UV = %p\n",
				    data + frame->planes.nv.uv.offset);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUYV:
	हाल IA_CSS_FRAME_FORMAT_UYVY:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_YUV_LINE:
		ia_css_debug_dtrace(2, "  YUYV = %p\n",
				    data + frame->planes.yuyv.offset);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUV420:
	हाल IA_CSS_FRAME_FORMAT_YUV422:
	हाल IA_CSS_FRAME_FORMAT_YUV444:
	हाल IA_CSS_FRAME_FORMAT_YV12:
	हाल IA_CSS_FRAME_FORMAT_YV16:
	हाल IA_CSS_FRAME_FORMAT_YUV420_16:
	हाल IA_CSS_FRAME_FORMAT_YUV422_16:
		ia_css_debug_dtrace(2, "  Y = %p\n",
				    data + frame->planes.yuv.y.offset);
		ia_css_debug_dtrace(2, "  U = %p\n",
				    data + frame->planes.yuv.u.offset);
		ia_css_debug_dtrace(2, "  V = %p\n",
				    data + frame->planes.yuv.v.offset);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_RAW_PACKED:
		ia_css_debug_dtrace(2, "  RAW PACKED = %p\n",
				    data + frame->planes.raw.offset);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_RAW:
		ia_css_debug_dtrace(2, "  RAW = %p\n",
				    data + frame->planes.raw.offset);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_RGBA888:
	हाल IA_CSS_FRAME_FORMAT_RGB565:
		ia_css_debug_dtrace(2, "  RGB = %p\n",
				    data + frame->planes.rgb.offset);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_QPLANE6:
		ia_css_debug_dtrace(2, "  R    = %p\n",
				    data + frame->planes.plane6.r.offset);
		ia_css_debug_dtrace(2, "  RatB = %p\n",
				    data + frame->planes.plane6.r_at_b.offset);
		ia_css_debug_dtrace(2, "  Gr   = %p\n",
				    data + frame->planes.plane6.gr.offset);
		ia_css_debug_dtrace(2, "  Gb   = %p\n",
				    data + frame->planes.plane6.gb.offset);
		ia_css_debug_dtrace(2, "  B    = %p\n",
				    data + frame->planes.plane6.b.offset);
		ia_css_debug_dtrace(2, "  BatR = %p\n",
				    data + frame->planes.plane6.b_at_r.offset);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_BINARY_8:
		ia_css_debug_dtrace(2, "  Binary data = %p\n",
				    data + frame->planes.binary.data.offset);
		अवरोध;
	शेष:
		ia_css_debug_dtrace(2, "  unknown frame type\n");
		अवरोध;
	पूर्ण
	वापस;
पूर्ण

#अगर SP_DEBUG != SP_DEBUG_NONE

व्योम ia_css_debug_prपूर्णांक_sp_debug_state(स्थिर काष्ठा sh_css_sp_debug_state
				       *state)
अणु
#पूर्ण_अगर

#अगर SP_DEBUG == SP_DEBUG_DUMP

	निश्चित(state);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "current SP software counter: %d\n",
			    state->debug[0]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty output buffer queue head: 0x%x\n",
			    state->debug[1]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty output buffer queue tail: 0x%x\n",
			    state->debug[2]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty s3a buffer queue head: 0x%x\n",
			    state->debug[3]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty s3a buffer queue tail: 0x%x\n",
			    state->debug[4]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "full output buffer queue head: 0x%x\n",
			    state->debug[5]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "full output buffer queue tail: 0x%x\n",
			    state->debug[6]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "full s3a buffer queue head: 0x%x\n",
			    state->debug[7]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "full s3a buffer queue tail: 0x%x\n",
			    state->debug[8]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "event queue head: 0x%x\n",
			    state->debug[9]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "event queue tail: 0x%x\n",
			    state->debug[10]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "num of stages of current pipeline: 0x%x\n",
			    state->debug[11]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "DDR address of stage 1: 0x%x\n",
			    state->debug[12]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "DDR address of stage 2: 0x%x\n",
			    state->debug[13]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "current stage out_vf buffer idx: 0x%x\n",
			    state->debug[14]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "current stage output buffer idx: 0x%x\n",
			    state->debug[15]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "current stage s3a buffer idx: 0x%x\n",
			    state->debug[16]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first char of current stage name: 0x%x\n",
			    state->debug[17]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "current SP thread id: 0x%x\n",
			    state->debug[18]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty output buffer address 1: 0x%x\n",
			    state->debug[19]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty output buffer address 2: 0x%x\n",
			    state->debug[20]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty out_vf buffer address 1: 0x%x\n",
			    state->debug[21]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty out_vf buffer address 2: 0x%x\n",
			    state->debug[22]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty s3a_hi buffer address 1: 0x%x\n",
			    state->debug[23]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty s3a_hi buffer address 2: 0x%x\n",
			    state->debug[24]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty s3a_lo buffer address 1: 0x%x\n",
			    state->debug[25]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty s3a_lo buffer address 2: 0x%x\n",
			    state->debug[26]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty dis_hor buffer address 1: 0x%x\n",
			    state->debug[27]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty dis_hor buffer address 2: 0x%x\n",
			    state->debug[28]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty dis_ver buffer address 1: 0x%x\n",
			    state->debug[29]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty dis_ver buffer address 2: 0x%x\n",
			    state->debug[30]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "empty param buffer address: 0x%x\n",
			    state->debug[31]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first incorrect frame address: 0x%x\n",
			    state->debug[32]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first incorrect frame container address: 0x%x\n",
			    state->debug[33]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first incorrect frame container payload: 0x%x\n",
			    state->debug[34]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first incorrect s3a_hi address: 0x%x\n",
			    state->debug[35]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first incorrect s3a_hi container address: 0x%x\n",
			    state->debug[36]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first incorrect s3a_hi container payload: 0x%x\n",
			    state->debug[37]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first incorrect s3a_lo address: 0x%x\n",
			    state->debug[38]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first incorrect s3a_lo container address: 0x%x\n",
			    state->debug[39]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "first incorrect s3a_lo container payload: 0x%x\n",
			    state->debug[40]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "number of calling flash start function: 0x%x\n",
			    state->debug[41]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "number of calling flash close function: 0x%x\n",
			    state->debug[42]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "number of flashed frame: 0x%x\n",
			    state->debug[43]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "flash in use flag: 0x%x\n",
			    state->debug[44]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "number of update frame flashed flag: 0x%x\n",
			    state->debug[46]);
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
			    "number of active threads: 0x%x\n",
			    state->debug[45]);

#या_अगर SP_DEBUG == SP_DEBUG_COPY

	/* Remember last_index because we only want to prपूर्णांक new entries */
	अटल पूर्णांक last_index;
	पूर्णांक sp_index = state->index;
	पूर्णांक n;

	निश्चित(state);
	अगर (sp_index < last_index) अणु
		/* SP has been reset */
		last_index = 0;
	पूर्ण

	अगर (last_index == 0) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
				    "copy-trace init: sp_dbg_if_start_line=%d, sp_dbg_if_start_column=%d, sp_dbg_if_cropped_height=%d, sp_debg_if_cropped_width=%d\n",
				    state->अगर_start_line,
				    state->अगर_start_column,
				    state->अगर_cropped_height,
				    state->अगर_cropped_width);
	पूर्ण

	अगर ((last_index + SH_CSS_SP_DBG_TRACE_DEPTH) < sp_index) अणु
		/* last index can be multiple rounds behind */
		/* जबतक trace size is only SH_CSS_SP_DBG_TRACE_DEPTH */
		last_index = sp_index - SH_CSS_SP_DBG_TRACE_DEPTH;
	पूर्ण

	क्रम (n = last_index; n < sp_index; n++) अणु
		पूर्णांक i = n % SH_CSS_SP_DBG_TRACE_DEPTH;

		अगर (state->trace[i].frame != 0) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
					    "copy-trace: frame=%d, line=%d, pixel_distance=%d, mipi_used_dword=%d, sp_index=%d\n",
					    state->trace[i].frame,
					    state->trace[i].line,
					    state->trace[i].pixel_distance,
					    state->trace[i].mipi_used_dword,
					    state->trace[i].sp_index);
		पूर्ण
	पूर्ण

	last_index = sp_index;

#या_अगर SP_DEBUG == SP_DEBUG_TRACE

	/*
	 * This is just an example how TRACE_खाता_ID (see ia_css_debug.sp.h) will
	 * me mapped on the file name string.
	 *
	 * Adjust this to your trace हाल!
	 */
	अटल अक्षर स्थिर *स्थिर id2filename[8] = अणु
		"param_buffer.sp.c | tagger.sp.c | pipe_data.sp.c",
		"isp_init.sp.c",
		"sp_raw_copy.hive.c",
		"dma_configure.sp.c",
		"sp.hive.c",
		"event_proxy_sp.hive.c",
		"circular_buffer.sp.c",
		"frame_buffer.sp.c"
	पूर्ण;

	/* Example SH_CSS_SP_DBG_NR_OF_TRACES==1 */
	/* Adjust this to your trace हाल */
	अटल अक्षर स्थिर *trace_name[SH_CSS_SP_DBG_NR_OF_TRACES] = अणु
		"default"
	पूर्ण;

	/* Remember host_index_last because we only want to prपूर्णांक new entries */
	अटल पूर्णांक host_index_last[SH_CSS_SP_DBG_NR_OF_TRACES] = अणु 0 पूर्ण;
	पूर्णांक t, n;

	निश्चित(state);

	क्रम (t = 0; t < SH_CSS_SP_DBG_NR_OF_TRACES; t++) अणु
		पूर्णांक sp_index_last = state->index_last[t];

		अगर (sp_index_last < host_index_last[t]) अणु
			/* SP has been reset */
			host_index_last[t] = 0;
		पूर्ण

		अगर ((host_index_last[t] + SH_CSS_SP_DBG_TRACE_DEPTH) <
		    sp_index_last) अणु
			/* last index can be multiple rounds behind */
			/* जबतक trace size is only SH_CSS_SP_DBG_TRACE_DEPTH */
			ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
					    "Warning: trace %s has gap of %d traces\n",
					    trace_name[t],
					    (sp_index_last -
					     (host_index_last[t] +
					      SH_CSS_SP_DBG_TRACE_DEPTH)));

			host_index_last[t] =
			    sp_index_last - SH_CSS_SP_DBG_TRACE_DEPTH;
		पूर्ण

		क्रम (n = host_index_last[t]; n < sp_index_last; n++) अणु
			पूर्णांक i = n % SH_CSS_SP_DBG_TRACE_DEPTH;
			पूर्णांक l = state->trace[t][i].location &
				((1 << SH_CSS_SP_DBG_TRACE_खाता_ID_BIT_POS) - 1);
			पूर्णांक fid = state->trace[t][i].location >>
				  SH_CSS_SP_DBG_TRACE_खाता_ID_BIT_POS;
			पूर्णांक ts = state->trace[t][i].समय_stamp;

			अगर (ts) अणु
				ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
						    "%05d trace=%s, file=%s:%d, data=0x%08x\n",
						    ts,
						    trace_name[t],
						    id2filename[fid], l,
						    state->trace[t][i].data);
			पूर्ण
		पूर्ण
		host_index_last[t] = sp_index_last;
	पूर्ण

#या_अगर SP_DEBUG == SP_DEBUG_MINIMAL
	पूर्णांक i;
	पूर्णांक base = 0;
	पूर्णांक limit = SH_CSS_NUM_SP_DEBUG;
	पूर्णांक step = 1;

	निश्चित(state);

	क्रम (i = base; i < limit; i += step) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
				    "sp_dbg_trace[%d] = %d\n",
				    i, state->debug[i]);
	पूर्ण
#पूर्ण_अगर

#अगर SP_DEBUG != SP_DEBUG_NONE

	वापस;
पूर्ण
#पूर्ण_अगर

#अगर !defined(ISP2401)
अटल व्योम debug_prपूर्णांक_rx_mipi_port_state(mipi_port_state_t *state)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक bits, infos;

	निश्चित(state);

	bits = state->irq_status;
	infos = ia_css_isys_rx_translate_irq_infos(bits);

	ia_css_debug_dtrace(2, "\t\t%-32s: (irq reg = 0x%X)\n",
			    "receiver errors", bits);

	अगर (infos & IA_CSS_RX_IRQ_INFO_BUFFER_OVERRUN)
		ia_css_debug_dtrace(2, "\t\t\tbuffer overrun\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_SOT)
		ia_css_debug_dtrace(2, "\t\t\tstart-of-transmission error\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_SOT_SYNC)
		ia_css_debug_dtrace(2, "\t\t\tstart-of-transmission sync error\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_CONTROL)
		ia_css_debug_dtrace(2, "\t\t\tcontrol error\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_ECC_DOUBLE)
		ia_css_debug_dtrace(2, "\t\t\t2 or more ECC errors\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_CRC)
		ia_css_debug_dtrace(2, "\t\t\tCRC mismatch\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ID)
		ia_css_debug_dtrace(2, "\t\t\tunknown error\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_FRAME_SYNC)
		ia_css_debug_dtrace(2, "\t\t\tframe sync error\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_FRAME_DATA)
		ia_css_debug_dtrace(2, "\t\t\tframe data error\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_DATA_TIMEOUT)
		ia_css_debug_dtrace(2, "\t\t\tdata timeout\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ESC)
		ia_css_debug_dtrace(2, "\t\t\tunknown escape command entry\n");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_LINE_SYNC)
		ia_css_debug_dtrace(2, "\t\t\tline sync error\n");

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "device_ready", state->device_पढ़ोy);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "irq_status", state->irq_status);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "irq_enable", state->irq_enable);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "timeout_count", state->समयout_count);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "init_count", state->init_count);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "raw16_18", state->raw16_18);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "sync_count", state->sync_count);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "rx_count", state->rx_count);

	क्रम (i = 0; i < MIPI_4LANE_CFG; i++) अणु
		ia_css_debug_dtrace(2, "\t\t%-32s%d%-32s: %d\n",
				    "lane_sync_count[", i, "]",
				    state->lane_sync_count[i]);
	पूर्ण

	क्रम (i = 0; i < MIPI_4LANE_CFG; i++) अणु
		ia_css_debug_dtrace(2, "\t\t%-32s%d%-32s: %d\n",
				    "lane_rx_count[", i, "]",
				    state->lane_rx_count[i]);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम debug_prपूर्णांक_rx_channel_state(rx_channel_state_t *state)
अणु
	पूर्णांक i;

	निश्चित(state);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "compression_scheme0", state->comp_scheme0);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "compression_scheme1", state->comp_scheme1);

	क्रम (i = 0; i < N_MIPI_FORMAT_CUSTOM; i++) अणु
		ia_css_debug_dtrace(2, "\t\t%-32s%d: %d\n",
				    "MIPI Predictor ", i, state->pred[i]);
	पूर्ण

	क्रम (i = 0; i < N_MIPI_FORMAT_CUSTOM; i++) अणु
		ia_css_debug_dtrace(2, "\t\t%-32s%d: %d\n",
				    "MIPI Compressor ", i, state->comp[i]);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम debug_prपूर्णांक_rx_state(receiver_state_t *state)
अणु
	पूर्णांक i;

	निश्चित(state);
	ia_css_debug_dtrace(2, "CSI Receiver State:\n");

	ia_css_debug_dtrace(2, "\tConfiguration:\n");

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "fs_to_ls_delay", state->fs_to_ls_delay);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "ls_to_data_delay", state->ls_to_data_delay);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "data_to_le_delay", state->data_to_le_delay);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "le_to_fe_delay", state->le_to_fe_delay);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "fe_to_fs_delay", state->fe_to_fs_delay);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "le_to_fs_delay", state->le_to_fs_delay);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "is_two_ppc", state->is_two_ppc);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "backend_rst", state->backend_rst);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "raw18", state->raw18);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "force_raw8", state->क्रमce_raw8);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "raw16", state->raw16);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_gsp_acc_ovl", state->be_gsp_acc_ovl);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "be_srst", state->be_srst);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_is_two_ppc", state->be_is_two_ppc);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_comp_format0", state->be_comp_क्रमmat0);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_comp_format1", state->be_comp_क्रमmat1);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_comp_format2", state->be_comp_क्रमmat2);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_comp_format3", state->be_comp_क्रमmat3);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "be_sel", state->be_sel);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_raw16_config", state->be_raw16_config);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_raw18_config", state->be_raw18_config);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_force_raw8", state->be_क्रमce_raw8);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_irq_status", state->be_irq_status);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "be_irq_clear", state->be_irq_clear);

	/* mipi port state */
	क्रम (i = 0; i < N_MIPI_PORT_ID; i++) अणु
		ia_css_debug_dtrace(2, "\tMIPI Port %d State:\n", i);

		debug_prपूर्णांक_rx_mipi_port_state(&state->mipi_port_state[i]);
	पूर्ण
	/* end of mipi port state */

	/* rx channel state */
	क्रम (i = 0; i < N_RX_CHANNEL_ID; i++) अणु
		ia_css_debug_dtrace(2, "\tRX Channel %d State:\n", i);

		debug_prपूर्णांक_rx_channel_state(&state->rx_channel_state[i]);
	पूर्ण
	/* end of rx channel state */

	वापस;
पूर्ण
#पूर्ण_अगर

व्योम ia_css_debug_dump_rx_state(व्योम)
अणु
#अगर !defined(ISP2401)
	receiver_state_t state;

	receiver_get_state(RX0_ID, &state);
	debug_prपूर्णांक_rx_state(&state);
#पूर्ण_अगर
पूर्ण

व्योम ia_css_debug_dump_sp_sw_debug_info(व्योम)
अणु
#अगर SP_DEBUG != SP_DEBUG_NONE
	काष्ठा sh_css_sp_debug_state state;

	sh_css_sp_get_debug_state(&state);
	ia_css_debug_prपूर्णांक_sp_debug_state(&state);
#पूर्ण_अगर
	ia_css_bufq_dump_queue_info();
	ia_css_pipeline_dump_thपढ़ो_map_info();
	वापस;
पूर्ण

#अगर !defined(ISP2401)
अटल व्योम debug_prपूर्णांक_isys_capture_unit_state(capture_unit_state_t *state)
अणु
	निश्चित(state);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Packet_Length", state->Packet_Length);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Received_Length", state->Received_Length);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Received_Short_Packets",
			    state->Received_Short_Packets);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Received_Long_Packets",
			    state->Received_Long_Packets);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Last_Command", state->Last_Command);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Next_Command", state->Next_Command);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Last_Acknowledge", state->Last_Acknowledge);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Next_Acknowledge", state->Next_Acknowledge);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM_State_Info", state->FSM_State_Info);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "StartMode", state->StartMode);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Start_Addr", state->Start_Addr);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Mem_Region_Size", state->Mem_Region_Size);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Num_Mem_Regions", state->Num_Mem_Regions);
	वापस;
पूर्ण

अटल व्योम debug_prपूर्णांक_isys_acquisition_unit_state(
    acquisition_unit_state_t *state)
अणु
	निश्चित(state);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Received_Short_Packets",
			    state->Received_Short_Packets);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Received_Long_Packets",
			    state->Received_Long_Packets);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Last_Command", state->Last_Command);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Next_Command", state->Next_Command);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Last_Acknowledge", state->Last_Acknowledge);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Next_Acknowledge", state->Next_Acknowledge);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "FSM_State_Info", state->FSM_State_Info);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Int_Cntr_Info", state->Int_Cntr_Info);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Start_Addr", state->Start_Addr);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Mem_Region_Size", state->Mem_Region_Size);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "Num_Mem_Regions", state->Num_Mem_Regions);
पूर्ण

अटल व्योम debug_prपूर्णांक_isys_ctrl_unit_state(ctrl_unit_state_t *state)
अणु
	निश्चित(state);
	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "last_cmd", state->last_cmd);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "next_cmd", state->next_cmd);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "last_ack", state->last_ack);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n", "next_ack", state->next_ack);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "top_fsm_state", state->top_fsm_state);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captA_fsm_state", state->captA_fsm_state);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captB_fsm_state", state->captB_fsm_state);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captC_fsm_state", state->captC_fsm_state);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "acq_fsm_state", state->acq_fsm_state);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captA_start_addr", state->captA_start_addr);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captB_start_addr", state->captB_start_addr);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captC_start_addr", state->captC_start_addr);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captA_mem_region_size",
			    state->captA_mem_region_size);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captB_mem_region_size",
			    state->captB_mem_region_size);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captC_mem_region_size",
			    state->captC_mem_region_size);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captA_num_mem_regions",
			    state->captA_num_mem_regions);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captB_num_mem_regions",
			    state->captB_num_mem_regions);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "captC_num_mem_regions",
			    state->captC_num_mem_regions);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "acq_start_addr", state->acq_start_addr);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "acq_mem_region_size", state->acq_mem_region_size);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "acq_num_mem_regions", state->acq_num_mem_regions);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "capt_reserve_one_mem_region",
			    state->capt_reserve_one_mem_region);

	वापस;
पूर्ण

अटल व्योम debug_prपूर्णांक_isys_state(input_प्रणाली_state_t *state)
अणु
	पूर्णांक i;

	निश्चित(state);
	ia_css_debug_dtrace(2, "InputSystem State:\n");

	/* configuration */
	ia_css_debug_dtrace(2, "\tConfiguration:\n");

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "str_multiCastA_sel", state->str_multicastA_sel);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "str_multicastB_sel", state->str_multicastB_sel);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "str_multicastC_sel", state->str_multicastC_sel);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "str_mux_sel", state->str_mux_sel);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "str_mon_status", state->str_mon_status);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "str_mon_irq_cond", state->str_mon_irq_cond);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "str_mon_irq_en", state->str_mon_irq_en);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "isys_srst", state->isys_srst);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "isys_slv_reg_srst", state->isys_slv_reg_srst);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "str_deint_portA_cnt", state->str_deपूर्णांक_portA_cnt);

	ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
			    "str_deint_portB_cnd", state->str_deपूर्णांक_portB_cnt);
	/* end of configuration */

	/* capture unit state */
	क्रम (i = 0; i < N_CAPTURE_UNIT_ID; i++) अणु
		capture_unit_state_t *capture_unit_state;

		ia_css_debug_dtrace(2, "\tCaptureUnit %d State:\n", i);

		capture_unit_state = &state->capture_unit[i];
		debug_prपूर्णांक_isys_capture_unit_state(capture_unit_state);
	पूर्ण
	/* end of capture unit state */

	/* acquisition unit state */
	क्रम (i = 0; i < N_ACQUISITION_UNIT_ID; i++) अणु
		acquisition_unit_state_t *acquisition_unit_state;

		ia_css_debug_dtrace(2, "\tAcquisitionUnit %d State:\n", i);

		acquisition_unit_state = &state->acquisition_unit[i];
		debug_prपूर्णांक_isys_acquisition_unit_state(acquisition_unit_state);
	पूर्ण
	/* end of acquisition unit state */

	/* control unit state */
	क्रम (i = 0; i < N_CTRL_UNIT_ID; i++) अणु
		ia_css_debug_dtrace(2, "\tControlUnit %d State:\n", i);

		debug_prपूर्णांक_isys_ctrl_unit_state(&state->ctrl_unit_state[i]);
	पूर्ण
	/* end of control unit state */
पूर्ण
#पूर्ण_अगर

व्योम ia_css_debug_dump_isys_state(व्योम)
अणु
	अटल input_प्रणाली_state_t state;

	input_प्रणाली_get_state(INPUT_SYSTEM0_ID, &state);

#अगर_अघोषित ISP2401
	debug_prपूर्णांक_isys_state(&state);
#अन्यथा
	input_प्रणाली_dump_state(INPUT_SYSTEM0_ID, &state);
#पूर्ण_अगर
पूर्ण

व्योम ia_css_debug_dump_debug_info(स्थिर अक्षर *context)
अणु
	अगर (!context)
		context = "No Context provided";

	ia_css_debug_dtrace(2, "CSS Debug Info dump [Context = %s]\n", context);
	अगर (!IS_ISP2401)
		ia_css_debug_dump_rx_state();

#अगर_अघोषित ISP2401
	ia_css_debug_dump_अगर_state();
#पूर्ण_अगर
	ia_css_debug_dump_isp_state();
	ia_css_debug_dump_isp_sp_fअगरo_state();
	ia_css_debug_dump_isp_gdc_fअगरo_state();
	ia_css_debug_dump_sp_state();
	ia_css_debug_dump_perf_counters();

#अगर_घोषित HAS_WATCHDOG_SP_THREAD_DEBUG
	sh_css_dump_thपढ़ो_रुको_info();
	sh_css_dump_pipe_stage_info();
	sh_css_dump_pipe_stripe_info();
#पूर्ण_अगर
	ia_css_debug_dump_dma_isp_fअगरo_state();
	ia_css_debug_dump_dma_sp_fअगरo_state();
	ia_css_debug_dump_dma_state();

	अगर (!IS_ISP2401) अणु
		काष्ठा irq_controller_state state;

		ia_css_debug_dump_isys_state();

		irq_controller_get_state(IRQ2_ID, &state);

		ia_css_debug_dtrace(2, "\t%-32s:\n",
				    "Input System IRQ Controller State");

		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
				    "irq_edge", state.irq_edge);

		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
				    "irq_mask", state.irq_mask);

		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
				    "irq_status", state.irq_status);

		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
				    "irq_enable", state.irq_enable);

		ia_css_debug_dtrace(2, "\t\t%-32s: %d\n",
				    "irq_level_not_pulse",
				    state.irq_level_not_pulse);
	पूर्ण अन्यथा अणु
		ia_css_debug_dump_isys_state();
	पूर्ण

	ia_css_debug_tagger_state();

	वापस;
पूर्ण

/* this function is क्रम debug use, it can make SP go to sleep
  state after each frame, then user can dump the stable SP dmem.
  this function can be called after ia_css_start_sp()
  and beक्रमe sh_css_init_buffer_queues()
*/
व्योम ia_css_debug_enable_sp_sleep_mode(क्रमागत ia_css_sp_sleep_mode mode)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_sleep_mode;

	fw = &sh_css_sp_fw;
	HIVE_ADDR_sp_sleep_mode = fw->info.sp.sleep_mode;

	(व्योम)HIVE_ADDR_sp_sleep_mode;	/* Suppres warnings in CRUN */

	sp_dmem_store_uपूर्णांक32(SP0_ID,
			     (अचिन्हित पूर्णांक)sp_address_of(sp_sleep_mode),
			     (uपूर्णांक32_t)mode);
पूर्ण

व्योम ia_css_debug_wake_up_sp(व्योम)
अणु
	/*hrt_ctl_start(SP); */
	sp_ctrl_setbit(SP0_ID, SP_SC_REG, SP_START_BIT);
पूर्ण

#घोषणा FIND_DMEM_PARAMS_TYPE(stream, kernel, type) \
	(काष्ठा HRTCAT(HRTCAT(sh_css_isp_, type), _params) *) \
	findf_dmem_params(stream, दुरत्व(काष्ठा ia_css_memory_offsets, dmem.kernel))

#घोषणा FIND_DMEM_PARAMS(stream, kernel) FIND_DMEM_PARAMS_TYPE(stream, kernel, kernel)

/* Find a stage that support the kernel and वापस the parameters क्रम that kernel */
अटल अक्षर *
findf_dmem_params(काष्ठा ia_css_stream *stream, लघु idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < stream->num_pipes; i++) अणु
		काष्ठा ia_css_pipe *pipe = stream->pipes[i];
		काष्ठा ia_css_pipeline *pipeline = ia_css_pipe_get_pipeline(pipe);
		काष्ठा ia_css_pipeline_stage *stage;

		क्रम (stage = pipeline->stages; stage; stage = stage->next) अणु
			काष्ठा ia_css_binary *binary = stage->binary;
			लघु *offsets = (लघु *)&binary->info->mem_offsets.offsets.param->dmem;
			लघु dmem_offset = offsets[idx];
			स्थिर काष्ठा ia_css_host_data *isp_data =
			    ia_css_isp_param_get_mem_init(&binary->mem_params,
							  IA_CSS_PARAM_CLASS_PARAM, IA_CSS_ISP_DMEM0);
			अगर (dmem_offset < 0)
				जारी;
			वापस &isp_data->address[dmem_offset];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम ia_css_debug_dump_isp_params(काष्ठा ia_css_stream *stream,
				  अचिन्हित पूर्णांक enable)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "ISP PARAMETERS:\n");

	निश्चित(stream);
	अगर ((enable & IA_CSS_DEBUG_DUMP_FPN)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_fpn_dump(FIND_DMEM_PARAMS(stream, fpn), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_OB)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_ob_dump(FIND_DMEM_PARAMS(stream, ob), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_SC)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_sc_dump(FIND_DMEM_PARAMS(stream, sc), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_WB)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_wb_dump(FIND_DMEM_PARAMS(stream, wb), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_DP)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_dp_dump(FIND_DMEM_PARAMS(stream, dp), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_BNR)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_bnr_dump(FIND_DMEM_PARAMS(stream, bnr), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_S3A)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_s3a_dump(FIND_DMEM_PARAMS(stream, s3a), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_DE)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_de_dump(FIND_DMEM_PARAMS(stream, de), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_YNR)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_nr_dump(FIND_DMEM_PARAMS_TYPE(stream, nr, ynr),  IA_CSS_DEBUG_VERBOSE);
		ia_css_yee_dump(FIND_DMEM_PARAMS(stream, yee), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_CSC)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_csc_dump(FIND_DMEM_PARAMS(stream, csc), IA_CSS_DEBUG_VERBOSE);
		ia_css_yuv2rgb_dump(FIND_DMEM_PARAMS_TYPE(stream, yuv2rgb, csc),
				    IA_CSS_DEBUG_VERBOSE);
		ia_css_rgb2yuv_dump(FIND_DMEM_PARAMS_TYPE(stream, rgb2yuv, csc),
				    IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_GC)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_gc_dump(FIND_DMEM_PARAMS(stream, gc), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_TNR)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_tnr_dump(FIND_DMEM_PARAMS(stream, tnr), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_ANR)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_anr_dump(FIND_DMEM_PARAMS(stream, anr), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
	अगर ((enable & IA_CSS_DEBUG_DUMP_CE)
	    || (enable & IA_CSS_DEBUG_DUMP_ALL)) अणु
		ia_css_ce_dump(FIND_DMEM_PARAMS(stream, ce), IA_CSS_DEBUG_VERBOSE);
	पूर्ण
पूर्ण

व्योम sh_css_dump_sp_raw_copy_linecount(bool reduced)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक HIVE_ADDR_raw_copy_line_count;
	s32 raw_copy_line_count;
	अटल s32 prev_raw_copy_line_count = -1;

	fw = &sh_css_sp_fw;
	HIVE_ADDR_raw_copy_line_count =
	    fw->info.sp.raw_copy_line_count;

	(व्योम)HIVE_ADDR_raw_copy_line_count;

	sp_dmem_load(SP0_ID,
		     (अचिन्हित पूर्णांक)sp_address_of(raw_copy_line_count),
		     &raw_copy_line_count,
		     माप(raw_copy_line_count));

	/* only indicate अगर copy loop is active */
	अगर (reduced)
		raw_copy_line_count = (raw_copy_line_count < 0) ? raw_copy_line_count : 1;
	/* करो the handling */
	अगर (prev_raw_copy_line_count != raw_copy_line_count) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
				    "sh_css_dump_sp_raw_copy_linecount() line_count=%d\n",
				    raw_copy_line_count);
		prev_raw_copy_line_count = raw_copy_line_count;
	पूर्ण
पूर्ण

व्योम ia_css_debug_dump_isp_binary(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक HIVE_ADDR_pipeline_sp_curr_binary_id;
	u32 curr_binary_id;
	अटल u32 prev_binary_id = 0xFFFFFFFF;
	अटल u32 sample_count;

	fw = &sh_css_sp_fw;
	HIVE_ADDR_pipeline_sp_curr_binary_id = fw->info.sp.curr_binary_id;

	(व्योम)HIVE_ADDR_pipeline_sp_curr_binary_id;

	sp_dmem_load(SP0_ID,
		     (अचिन्हित पूर्णांक)sp_address_of(pipeline_sp_curr_binary_id),
		     &curr_binary_id,
		     माप(curr_binary_id));

	/* करो the handling */
	sample_count++;
	अगर (prev_binary_id != curr_binary_id) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
				    "sh_css_dump_isp_binary() pipe_id=%d, binary_id=%d, sample_count=%d\n",
				    (curr_binary_id >> 16),
				    (curr_binary_id & 0x0ffff),
				    sample_count);
		sample_count = 0;
		prev_binary_id = curr_binary_id;
	पूर्ण
पूर्ण

व्योम ia_css_debug_dump_perf_counters(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	पूर्णांक i;
	अचिन्हित पूर्णांक HIVE_ADDR_ia_css_isys_sp_error_cnt;
	/* N_MIPI_PORT_ID + 1: 3 Capture Units and 1 Acquire Unit. */
	s32 ia_css_sp_input_प्रणाली_error_cnt[N_MIPI_PORT_ID + 1];

	अगर (IS_ISP2401)
		वापस;

	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "Input System Error Counters:\n");

	fw = &sh_css_sp_fw;
	HIVE_ADDR_ia_css_isys_sp_error_cnt =
	    fw->info.sp.perf_counter_input_प्रणाली_error;

	(व्योम)HIVE_ADDR_ia_css_isys_sp_error_cnt;

	sp_dmem_load(SP0_ID,
		     (अचिन्हित पूर्णांक)sp_address_of(ia_css_isys_sp_error_cnt),
		     &ia_css_sp_input_प्रणाली_error_cnt,
		     माप(ia_css_sp_input_प्रणाली_error_cnt));

	क्रम (i = 0; i < N_MIPI_PORT_ID + 1; i++) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "\tport[%d] = %d\n",
				    i, ia_css_sp_input_प्रणाली_error_cnt[i]);
	पूर्ण
पूर्ण

/*
 * @brief Initialize the debug mode.
 * Refer to "ia_css_debug.h" क्रम more details.
 */
bool ia_css_debug_mode_init(व्योम)
अणु
	bool rc;

	rc = sh_css_sp_init_dma_sw_reg(0);
	वापस rc;
पूर्ण

/*
 * @brief Disable the DMA channel.
 * Refer to "ia_css_debug.h" क्रम more details.
 */
bool
ia_css_debug_mode_disable_dma_channel(पूर्णांक dma_id,
				      पूर्णांक channel_id, पूर्णांक request_type)
अणु
	bool rc;

	rc = sh_css_sp_set_dma_sw_reg(dma_id, channel_id, request_type, false);

	वापस rc;
पूर्ण

/*
 * @brief Enable the DMA channel.
 * Refer to "ia_css_debug.h" क्रम more details.
 */
bool
ia_css_debug_mode_enable_dma_channel(पूर्णांक dma_id,
				     पूर्णांक channel_id, पूर्णांक request_type)
अणु
	bool rc;

	rc = sh_css_sp_set_dma_sw_reg(dma_id, channel_id, request_type, true);

	वापस rc;
पूर्ण

अटल व्योम __म_लिखो(1, 2) dtrace_करोt(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	निश्चित(fmt);
	बहु_शुरू(ap, fmt);

	ia_css_debug_dtrace(IA_CSS_DEBUG_INFO, "%s", DPG_START);
	ia_css_debug_vdtrace(IA_CSS_DEBUG_INFO, fmt, ap);
	ia_css_debug_dtrace(IA_CSS_DEBUG_INFO, "%s", DPG_END);
	बहु_पूर्ण(ap);
पूर्ण

#अगर_घोषित HAS_WATCHDOG_SP_THREAD_DEBUG
व्योम sh_css_dump_thपढ़ो_रुको_info(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	पूर्णांक i;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_thपढ़ो_रुको;
	s32 sp_thपढ़ो_रुको[MAX_THREAD_NUM];

	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "SEM WAITS:\n");

	fw = &sh_css_sp_fw;
	HIVE_ADDR_sp_thपढ़ो_रुको =
	    fw->info.sp.debug_रुको;

	(व्योम)HIVE_ADDR_sp_thपढ़ो_रुको;

	sp_dmem_load(SP0_ID,
		     (अचिन्हित पूर्णांक)sp_address_of(sp_thपढ़ो_रुको),
		     &sp_thपढ़ो_रुको,
		     माप(sp_thपढ़ो_रुको));
	क्रम (i = 0; i < MAX_THREAD_NUM; i++) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
				    "\twait[%d] = 0x%X\n",
				    i, sp_thपढ़ो_रुको[i]);
	पूर्ण
पूर्ण

व्योम sh_css_dump_pipe_stage_info(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	पूर्णांक i;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_pipe_stage;
	s32 sp_pipe_stage[MAX_THREAD_NUM];

	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "PIPE STAGE:\n");

	fw = &sh_css_sp_fw;
	HIVE_ADDR_sp_pipe_stage =
	    fw->info.sp.debug_stage;

	(व्योम)HIVE_ADDR_sp_pipe_stage;

	sp_dmem_load(SP0_ID,
		     (अचिन्हित पूर्णांक)sp_address_of(sp_pipe_stage),
		     &sp_pipe_stage,
		     माप(sp_pipe_stage));
	क्रम (i = 0; i < MAX_THREAD_NUM; i++) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
				    "\tstage[%d] = %d\n",
				    i, sp_pipe_stage[i]);
	पूर्ण
पूर्ण

व्योम sh_css_dump_pipe_stripe_info(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	पूर्णांक i;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_pipe_stripe;
	s32 sp_pipe_stripe[MAX_THREAD_NUM];

	ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE, "PIPE STRIPE:\n");

	fw = &sh_css_sp_fw;
	HIVE_ADDR_sp_pipe_stripe =
	    fw->info.sp.debug_stripe;

	(व्योम)HIVE_ADDR_sp_pipe_stripe;

	sp_dmem_load(SP0_ID,
		     (अचिन्हित पूर्णांक)sp_address_of(sp_pipe_stripe),
		     &sp_pipe_stripe,
		     माप(sp_pipe_stripe));
	क्रम (i = 0; i < MAX_THREAD_NUM; i++) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_VERBOSE,
				    "\tstripe[%d] = %d\n",
				    i, sp_pipe_stripe[i]);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम
ia_css_debug_pipe_graph_dump_frame(
    स्थिर काष्ठा ia_css_frame *frame,
    क्रमागत ia_css_pipe_id id,
    अक्षर स्थिर *blob_name,
    अक्षर स्थिर *frame_name,
    bool in_frame)
अणु
	अक्षर bufinfo[100];

	अगर (frame->dynamic_queue_id == SH_CSS_INVALID_QUEUE_ID) अणु
		snम_लिखो(bufinfo, माप(bufinfo), "Internal");
	पूर्ण अन्यथा अणु
		snम_लिखो(bufinfo, माप(bufinfo), "Queue: %s %s",
			 pipe_id_to_str[id],
			 queue_id_to_str[frame->dynamic_queue_id]);
	पूर्ण
	dtrace_करोt(
	    "node [shape = box, fixedsize=true, width=2, height=0.7]; \"%p\" [label = \"%s\\n%d(%d) x %d, %dbpp\\n%s\"];",
	    frame,
	    debug_frame_क्रमmat2str(frame->info.क्रमmat),
	    frame->info.res.width,
	    frame->info.padded_width,
	    frame->info.res.height,
	    frame->info.raw_bit_depth,
	    bufinfo);

	अगर (in_frame) अणु
		dtrace_करोt(
		    "\"%p\"->\"%s(pipe%d)\" [label = %s_frame];",
		    frame,
		    blob_name, id, frame_name);
	पूर्ण अन्यथा अणु
		dtrace_करोt(
		    "\"%s(pipe%d)\"->\"%p\" [label = %s_frame];",
		    blob_name, id,
		    frame,
		    frame_name);
	पूर्ण
पूर्ण

व्योम
ia_css_debug_pipe_graph_dump_prologue(व्योम)
अणु
	dtrace_करोt("digraph sh_css_pipe_graph {");
	dtrace_करोt("rankdir=LR;");

	dtrace_करोt("fontsize=9;");
	dtrace_करोt("label = \"\\nEnable options: rp=reduced pipe, vfve=vf_veceven, dvse=dvs_envelope, dvs6=dvs_6axis, bo=block_out, fbds=fixed_bayer_ds, bf6=bayer_fir_6db, rawb=raw_binning, cont=continuous, disc=dis_crop\\n"
		   "dp2a=dp_2adjacent, outp=output, outt=out_table, reff=ref_frame, par=params, gam=gamma, cagdc=ca_gdc, ispa=isp_addresses, inf=in_frame, outf=out_frame, hs=high_speed, inpc=input_chunking\"");
पूर्ण

व्योम ia_css_debug_pipe_graph_dump_epilogue(व्योम)
अणु
	अगर (म_माप(ring_buffer) > 0) अणु
		dtrace_करोt(ring_buffer);
	पूर्ण

	अगर (pg_inst.stream_क्रमmat != N_ATOMISP_INPUT_FORMAT) अणु
		/* An input stream क्रमmat has been set so assume we have
		 * an input प्रणाली and sensor
		 */

		dtrace_करोt(
		    "node [shape = doublecircle, fixedsize=true, width=2.5]; \"input_system\" [label = \"Input system\"];");

		dtrace_करोt(
		    "\"input_system\"->\"%s\" [label = \"%s\"];",
		    करोt_id_input_bin, debug_stream_क्रमmat2str(pg_inst.stream_क्रमmat));

		dtrace_करोt(
		    "node [shape = doublecircle, fixedsize=true, width=2.5]; \"sensor\" [label = \"Sensor\"];");

		dtrace_करोt(
		    "\"sensor\"->\"input_system\" [label = \"%s\\n%d x %d\\n(%d x %d)\"];",
		    debug_stream_क्रमmat2str(pg_inst.stream_क्रमmat),
		    pg_inst.width, pg_inst.height,
		    pg_inst.eff_width, pg_inst.eff_height);
	पूर्ण

	dtrace_करोt("}");

	/* Reset temp strings */
	स_रखो(करोt_id_input_bin, 0, माप(करोt_id_input_bin));
	स_रखो(ring_buffer, 0, माप(ring_buffer));

	pg_inst.करो_init = true;
	pg_inst.width = 0;
	pg_inst.height = 0;
	pg_inst.eff_width = 0;
	pg_inst.eff_height = 0;
	pg_inst.stream_क्रमmat = N_ATOMISP_INPUT_FORMAT;
पूर्ण

व्योम
ia_css_debug_pipe_graph_dump_stage(
    काष्ठा ia_css_pipeline_stage *stage,
    क्रमागत ia_css_pipe_id id)
अणु
	अक्षर blob_name[SH_CSS_MAX_BINARY_NAME + 10] = "<unknown type>";
	अक्षर स्थिर *bin_type = "<unknown type>";
	पूर्णांक i;

	निश्चित(stage);
	अगर (stage->sp_func != IA_CSS_PIPELINE_NO_FUNC)
		वापस;

	अगर (pg_inst.करो_init) अणु
		ia_css_debug_pipe_graph_dump_prologue();
		pg_inst.करो_init = false;
	पूर्ण

	अगर (stage->binary) अणु
		bin_type = "binary";
		अगर (stage->binary->info->blob)
			snम_लिखो(blob_name, माप(blob_name), "%s_stage%d",
				 stage->binary->info->blob->name, stage->stage_num);
	पूर्ण अन्यथा अगर (stage->firmware) अणु
		bin_type = "firmware";

		strscpy(blob_name, IA_CSS_EXT_ISP_PROG_NAME(stage->firmware),
			माप(blob_name));
	पूर्ण

	/* Guard in हाल of binaries that करोn't have any binary_info */
	अगर (stage->binary_info) अणु
		अक्षर enable_info1[100];
		अक्षर enable_info2[100];
		अक्षर enable_info3[100];
		अक्षर enable_info[200];
		काष्ठा ia_css_binary_info *bi = stage->binary_info;

		/* Split it in 2 function-calls to keep the amount of
		 * parameters per call "reasonable"
		 */
		snम_लिखो(enable_info1, माप(enable_info1),
			 "%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
			 bi->enable.reduced_pipe ?	"rp," : "",
			 bi->enable.vf_veceven ?		"vfve," : "",
			 bi->enable.dis ?		"dis," : "",
			 bi->enable.dvs_envelope ?	"dvse," : "",
			 bi->enable.uds ?		"uds," : "",
			 bi->enable.dvs_6axis ?		"dvs6," : "",
			 bi->enable.block_output ?	"bo," : "",
			 bi->enable.ds ?			"ds," : "",
			 bi->enable.bayer_fir_6db ?	"bf6," : "",
			 bi->enable.raw_binning ?	"rawb," : "",
			 bi->enable.continuous ?		"cont," : "",
			 bi->enable.s3a ?		"s3a," : "",
			 bi->enable.fpnr ?		"fpnr," : "",
			 bi->enable.sc ?			"sc," : ""
			);

		snम_लिखो(enable_info2, माप(enable_info2),
			 "%s%s%s%s%s%s%s%s%s%s%s",
			 bi->enable.macc ?		"macc," : "",
			 bi->enable.output ?		"outp," : "",
			 bi->enable.ref_frame ?		"reff," : "",
			 bi->enable.tnr ?		"tnr," : "",
			 bi->enable.xnr ?		"xnr," : "",
			 bi->enable.params ?		"par," : "",
			 bi->enable.ca_gdc ?		"cagdc," : "",
			 bi->enable.isp_addresses ?	"ispa," : "",
			 bi->enable.in_frame ?		"inf," : "",
			 bi->enable.out_frame ?		"outf," : "",
			 bi->enable.high_speed ?		"hs," : ""
			);

		/* And merge them पूर्णांकo one string */
		snम_लिखो(enable_info, माप(enable_info), "%s%s",
			 enable_info1, enable_info2);
		अणु
			पूर्णांक l, p;
			अक्षर *ei = enable_info;

			l = म_माप(ei);

			/* Replace last ',' with \0 अगर present */
			अगर (l && enable_info[l - 1] == ',')
				enable_info[--l] = '\0';

			अगर (l > ENABLE_LINE_MAX_LENGTH) अणु
				/* Too big क्रम one line, find last comma */
				p = ENABLE_LINE_MAX_LENGTH;
				जबतक (ei[p] != ',')
					p--;
				/* Last comma found, copy till that comma */
				strscpy(enable_info1, ei,
                                        p > माप(enable_info1) ? माप(enable_info1) : p);

				ei += p + 1;
				l = म_माप(ei);

				अगर (l <= ENABLE_LINE_MAX_LENGTH) अणु
					/* The 2nd line fits */
					/* we cannot use ei as argument because
					 * it is not guaranteed dword aligned
					 */

					strscpy(enable_info2, ei,
						l > माप(enable_info2) ? माप(enable_info2) : l);

					snम_लिखो(enable_info, माप(enable_info), "%s\\n%s",
						 enable_info1, enable_info2);

				पूर्ण अन्यथा अणु
					/* 2nd line is still too दीर्घ */
					p = ENABLE_LINE_MAX_LENGTH;
					जबतक (ei[p] != ',')
						p--;

					strscpy(enable_info2, ei,
						p > माप(enable_info2) ? माप(enable_info2) : p);

					ei += p + 1;
					l = म_माप(ei);

					अगर (l <= ENABLE_LINE_MAX_LENGTH) अणु
						/* The 3rd line fits */
						/* we cannot use ei as argument because
						* it is not guaranteed dword aligned
						*/
						strscpy(enable_info3, ei,
							माप(enable_info3));
						snम_लिखो(enable_info, माप(enable_info),
							 "%s\\n%s\\n%s",
							 enable_info1, enable_info2,
							 enable_info3);
					पूर्ण अन्यथा अणु
						/* 3rd line is still too दीर्घ */
						p = ENABLE_LINE_MAX_LENGTH;
						जबतक (ei[p] != ',')
							p--;
						strscpy(enable_info3, ei,
							p > माप(enable_info3) ? माप(enable_info3) : p);
						ei += p + 1;
						strscpy(enable_info3, ei,
							माप(enable_info3));
						snम_लिखो(enable_info, माप(enable_info),
							 "%s\\n%s\\n%s",
							 enable_info1, enable_info2,
							 enable_info3);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		dtrace_करोt("node [shape = circle, fixedsize=true, width=2.5, label=\"%s\\n%s\\n\\n%s\"]; \"%s(pipe%d)\"",
			   bin_type, blob_name, enable_info, blob_name, id);
	पूर्ण अन्यथा अणु
		dtrace_करोt("node [shape = circle, fixedsize=true, width=2.5, label=\"%s\\n%s\\n\"]; \"%s(pipe%d)\"",
			   bin_type, blob_name, blob_name, id);
	पूर्ण

	अगर (stage->stage_num == 0) अणु
		/*
		 * There are some implicite assumptions about which bin is the
		 * input binary e.g. which one is connected to the input प्रणाली
		 * Priority:
		 * 1) sp_raw_copy bin has highest priority
		 * 2) First stage==0 binary of preview, video or capture
		 */
		अगर (म_माप(करोt_id_input_bin) == 0) अणु
			snम_लिखो(करोt_id_input_bin, माप(करोt_id_input_bin),
				 "%s(pipe%d)", blob_name, id);
		पूर्ण
	पूर्ण

	अगर (stage->args.in_frame) अणु
		ia_css_debug_pipe_graph_dump_frame(
		    stage->args.in_frame, id, blob_name,
		    "in", true);
	पूर्ण

	क्रम (i = 0; i < NUM_TNR_FRAMES; i++) अणु
		अगर (stage->args.tnr_frames[i]) अणु
			ia_css_debug_pipe_graph_dump_frame(
			    stage->args.tnr_frames[i], id,
			    blob_name, "tnr_frame", true);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MAX_NUM_VIDEO_DELAY_FRAMES; i++) अणु
		अगर (stage->args.delay_frames[i]) अणु
			ia_css_debug_pipe_graph_dump_frame(
			    stage->args.delay_frames[i], id,
			    blob_name, "delay_frame", true);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		अगर (stage->args.out_frame[i]) अणु
			ia_css_debug_pipe_graph_dump_frame(
			    stage->args.out_frame[i], id, blob_name,
			    "out", false);
		पूर्ण
	पूर्ण

	अगर (stage->args.out_vf_frame) अणु
		ia_css_debug_pipe_graph_dump_frame(
		    stage->args.out_vf_frame, id, blob_name,
		    "out_vf", false);
	पूर्ण
पूर्ण

व्योम
ia_css_debug_pipe_graph_dump_sp_raw_copy(
    काष्ठा ia_css_frame *out_frame)
अणु
	निश्चित(out_frame);
	अगर (pg_inst.करो_init) अणु
		ia_css_debug_pipe_graph_dump_prologue();
		pg_inst.करो_init = false;
	पूर्ण

	dtrace_करोt("node [shape = circle, fixedsize=true, width=2.5, label=\"%s\\n%s\"]; \"%s(pipe%d)\"",
		   "sp-binary", "sp_raw_copy", "sp_raw_copy", 1);

	snम_लिखो(ring_buffer, माप(ring_buffer),
		 "node [shape = box, fixedsize=true, width=2, height=0.7]; \"%p\" [label = \"%s\\n%d(%d) x %d\\nRingbuffer\"];",
		 out_frame,
		 debug_frame_क्रमmat2str(out_frame->info.क्रमmat),
		 out_frame->info.res.width,
		 out_frame->info.padded_width,
		 out_frame->info.res.height);

	dtrace_करोt(ring_buffer);

	dtrace_करोt(
	    "\"%s(pipe%d)\"->\"%p\" [label = out_frame];",
	    "sp_raw_copy", 1, out_frame);

	snम_लिखो(करोt_id_input_bin, माप(करोt_id_input_bin), "%s(pipe%d)",
		 "sp_raw_copy", 1);
पूर्ण

व्योम
ia_css_debug_pipe_graph_dump_stream_config(
    स्थिर काष्ठा ia_css_stream_config *stream_config)
अणु
	pg_inst.width = stream_config->input_config.input_res.width;
	pg_inst.height = stream_config->input_config.input_res.height;
	pg_inst.eff_width = stream_config->input_config.effective_res.width;
	pg_inst.eff_height = stream_config->input_config.effective_res.height;
	pg_inst.stream_क्रमmat = stream_config->input_config.क्रमmat;
पूर्ण

व्योम
ia_css_debug_dump_resolution(
    स्थिर काष्ठा ia_css_resolution *res,
    स्थिर अक्षर *label)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s: =%d x =%d\n",
			    label, res->width, res->height);
पूर्ण

व्योम
ia_css_debug_dump_frame_info(
    स्थिर काष्ठा ia_css_frame_info *info,
    स्थिर अक्षर *label)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s\n", label);
	ia_css_debug_dump_resolution(&info->res, "res");
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "padded_width: %d\n",
			    info->padded_width);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "format: %d\n", info->क्रमmat);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "raw_bit_depth: %d\n",
			    info->raw_bit_depth);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "raw_bayer_order: %d\n",
			    info->raw_bayer_order);
पूर्ण

व्योम
ia_css_debug_dump_capture_config(
    स्थिर काष्ठा ia_css_capture_config *config)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s\n", __func__);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "mode: %d\n", config->mode);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "enable_xnr:  %d\n",
			    config->enable_xnr);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "enable_raw_output: %d\n",
			    config->enable_raw_output);
पूर्ण

व्योम
ia_css_debug_dump_pipe_extra_config(
    स्थिर काष्ठा ia_css_pipe_extra_config *extra_config)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s\n", __func__);
	अगर (extra_config) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "enable_raw_binning: %d\n",
				    extra_config->enable_raw_binning);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "enable_yuv_ds: %d\n",
				    extra_config->enable_yuv_ds);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "enable_high_speed:  %d\n",
				    extra_config->enable_high_speed);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "enable_dvs_6axis: %d\n",
				    extra_config->enable_dvs_6axis);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "enable_reduced_pipe: %d\n",
				    extra_config->enable_reduced_pipe);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "enable_fractional_ds: %d\n",
				    extra_config->enable_fractional_ds);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "disable_vf_pp: %d\n",
				    extra_config->disable_vf_pp);
	पूर्ण
पूर्ण

व्योम
ia_css_debug_dump_pipe_config(
    स्थिर काष्ठा ia_css_pipe_config *config)
अणु
	अचिन्हित पूर्णांक i;

	IA_CSS_ENTER_PRIVATE("config = %p", config);
	अगर (!config) अणु
		IA_CSS_ERROR("NULL input parameter");
		IA_CSS_LEAVE_PRIVATE("");
		वापस;
	पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "mode: %d\n", config->mode);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "isp_pipe_version: %d\n",
			    config->isp_pipe_version);
	ia_css_debug_dump_resolution(&config->bayer_ds_out_res,
				     "bayer_ds_out_res");
	ia_css_debug_dump_resolution(&config->capt_pp_in_res,
				     "capt_pp_in_res");
	ia_css_debug_dump_resolution(&config->vf_pp_in_res, "vf_pp_in_res");

	अगर (IS_ISP2401) अणु
		ia_css_debug_dump_resolution(&config->output_प्रणाली_in_res,
					    "output_system_in_res");
	पूर्ण
	ia_css_debug_dump_resolution(&config->dvs_crop_out_res,
				     "dvs_crop_out_res");
	क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++) अणु
		ia_css_debug_dump_frame_info(&config->output_info[i], "output_info");
		ia_css_debug_dump_frame_info(&config->vf_output_info[i],
					     "vf_output_info");
	पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "acc_extension: %p\n",
			    config->acc_extension);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "num_acc_stages: %d\n",
			    config->num_acc_stages);
	ia_css_debug_dump_capture_config(&config->शेष_capture_config);
	ia_css_debug_dump_resolution(&config->dvs_envelope, "dvs_envelope");
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "dvs_frame_delay: %d\n",
			    config->dvs_frame_delay);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "acc_num_execs: %d\n",
			    config->acc_num_execs);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "enable_dz: %d\n",
			    config->enable_dz);
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम
ia_css_debug_dump_stream_config_source(
    स्थिर काष्ठा ia_css_stream_config *config)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s()\n", __func__);
	चयन (config->mode) अणु
	हाल IA_CSS_INPUT_MODE_SENSOR:
	हाल IA_CSS_INPUT_MODE_BUFFERED_SENSOR:
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "source.port\n");
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "port: %d\n",
				    config->source.port.port);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "num_lanes: %d\n",
				    config->source.port.num_lanes);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "timeout: %d\n",
				    config->source.port.समयout);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "compression: %d\n",
				    config->source.port.compression.type);
		अवरोध;
	हाल IA_CSS_INPUT_MODE_TPG:
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "source.tpg\n");
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "id: %d\n",
				    config->source.tpg.id);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "mode: %d\n",
				    config->source.tpg.mode);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "x_mask: 0x%x\n",
				    config->source.tpg.x_mask);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "x_delta: %d\n",
				    config->source.tpg.x_delta);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "y_mask: 0x%x\n",
				    config->source.tpg.y_mask);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "y_delta: %d\n",
				    config->source.tpg.y_delta);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "xy_mask: 0x%x\n",
				    config->source.tpg.xy_mask);
		अवरोध;
	हाल IA_CSS_INPUT_MODE_PRBS:
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "source.prbs\n");
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "id: %d\n",
				    config->source.prbs.id);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "h_blank: %d\n",
				    config->source.prbs.h_blank);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "v_blank: %d\n",
				    config->source.prbs.v_blank);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "seed: 0x%x\n",
				    config->source.prbs.seed);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "seed1: 0x%x\n",
				    config->source.prbs.seed1);
		अवरोध;
	शेष:
	हाल IA_CSS_INPUT_MODE_FIFO:
	हाल IA_CSS_INPUT_MODE_MEMORY:
		अवरोध;
	पूर्ण
पूर्ण

व्योम
ia_css_debug_dump_mipi_buffer_config(
    स्थिर काष्ठा ia_css_mipi_buffer_config *config)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s()\n", __func__);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "size_mem_words: %d\n",
			    config->size_mem_words);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "nof_mipi_buffers: %d\n",
			    config->nof_mipi_buffers);
पूर्ण

व्योम
ia_css_debug_dump_metadata_config(
    स्थिर काष्ठा ia_css_metadata_config *config)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s()\n", __func__);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "data_type: %d\n",
			    config->data_type);
	ia_css_debug_dump_resolution(&config->resolution, "resolution");
पूर्ण

व्योम
ia_css_debug_dump_stream_config(
    स्थिर काष्ठा ia_css_stream_config *config,
    पूर्णांक num_pipes)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s()\n", __func__);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "num_pipes: %d\n", num_pipes);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "mode: %d\n", config->mode);
	ia_css_debug_dump_stream_config_source(config);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "channel_id: %d\n",
			    config->channel_id);
	ia_css_debug_dump_resolution(&config->input_config.input_res, "input_res");
	ia_css_debug_dump_resolution(&config->input_config.effective_res,
				     "effective_res");
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "format: %d\n",
			    config->input_config.क्रमmat);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "bayer_order: %d\n",
			    config->input_config.bayer_order);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "sensor_binning_factor: %d\n",
			    config->sensor_binning_factor);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "pixels_per_clock: %d\n",
			    config->pixels_per_घड़ी);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "online: %d\n",
			    config->online);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "init_num_cont_raw_buf: %d\n",
			    config->init_num_cont_raw_buf);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "target_num_cont_raw_buf: %d\n",
			    config->target_num_cont_raw_buf);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "pack_raw_pixels: %d\n",
			    config->pack_raw_pixels);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "continuous: %d\n",
			    config->continuous);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "flash_gpio_pin: %d\n",
			    config->flash_gpio_pin);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "left_padding: %d\n",
			    config->left_padding);
	ia_css_debug_dump_mipi_buffer_config(&config->mipi_buffer_config);
	ia_css_debug_dump_metadata_config(&config->metadata_config);
पूर्ण

/*
    Trace support.

    This tracer is using a buffer to trace the flow of the FW and dump misc values (see below क्रम details).
    Currently, support is only क्रम SKC.
    To enable support क्रम other platक्रमms:
     - Allocate a buffer क्रम tracing in DMEM. The दीर्घer the better.
     - Use the DBG_init routine in sp.hive.c to initiatilize the tracer with the address and size selected.
     - Add trace poपूर्णांकs in the SP code wherever needed.
     - Enable the dump below with the required address and required adjusपंचांगents.
	   Dump is called at the end of ia_css_debug_dump_sp_state().
*/

/*
 dump_trace() : dump the trace poपूर्णांकs from DMEM2.
 क्रम every trace poपूर्णांक, the following are prपूर्णांकed: index, major:minor and the 16-bit attached value.
 The routine looks क्रम the first 0, and then prपूर्णांकs from it cyclically.
 Data क्रमma in DMEM2:
  first 4 DWORDS: header
   DWORD 0: data description
    byte 0: version
    byte 1: number of thपढ़ोs (क्रम future use)
    byte 2+3: number ot TPs
   DWORD 1: command byte + data (क्रम future use)
    byte 0: command
    byte 1-3: command signature
   DWORD 2-3: additional data (क्रम future use)
  Following data is 4-byte oriented:
    byte 0:   major
	byte 1:   minor
	byte 2-3: data
*/
#अगर TRACE_ENABLE_SP0 || TRACE_ENABLE_SP1 || TRACE_ENABLE_ISP
अटल व्योम debug_dump_one_trace(क्रमागत TRACE_CORE_ID proc_id)
अणु
#अगर defined(HAS_TRACER_V2)
	u32 start_addr;
	u32 start_addr_data;
	u32 item_size;
	u32 पंचांगp;
	u8 tid_val;
	क्रमागत TRACE_DUMP_FORMAT dump_क्रमmat;

	पूर्णांक i, j, max_trace_poपूर्णांकs, poपूर्णांक_num, limit = -1;
	/* using a अटल buffer here as the driver has issues allocating memory */
	अटल u32 trace_पढ़ो_buf[TRACE_BUFF_SIZE] = अणु0पूर्ण;
	अटल काष्ठा trace_header_t header;
	u8 *header_arr;

	/* पढ़ो the header and parse it */
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "~~~ Tracer ");
	चयन (proc_id) अणु
	हाल TRACE_SP0_ID:
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "SP0");
		start_addr = TRACE_SP0_ADDR;
		start_addr_data = TRACE_SP0_DATA_ADDR;
		item_size = TRACE_SP0_ITEM_SIZE;
		max_trace_poपूर्णांकs = TRACE_SP0_MAX_POINTS;
		अवरोध;
	हाल TRACE_SP1_ID:
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "SP1");
		start_addr = TRACE_SP1_ADDR;
		start_addr_data = TRACE_SP1_DATA_ADDR;
		item_size = TRACE_SP1_ITEM_SIZE;
		max_trace_poपूर्णांकs = TRACE_SP1_MAX_POINTS;
		अवरोध;
	हाल TRACE_ISP_ID:
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ISP");
		start_addr = TRACE_ISP_ADDR;
		start_addr_data = TRACE_ISP_DATA_ADDR;
		item_size = TRACE_ISP_ITEM_SIZE;
		max_trace_poपूर्णांकs = TRACE_ISP_MAX_POINTS;
		अवरोध;
	शेष:
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "\t\ttraces are not supported for this processor ID - exiting\n");
		वापस;
	पूर्ण

	अगर (!IS_ISP2401) अणु
		पंचांगp = ia_css_device_load_uपूर्णांक32(start_addr);
		poपूर्णांक_num = (पंचांगp >> 16) & 0xFFFF;

		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, " ver %d %d points\n", पंचांगp & 0xFF,
				    poपूर्णांक_num);
	पूर्ण अन्यथा अणु
		/* Loading byte-by-byte as using the master routine had issues */
		header_arr = (uपूर्णांक8_t *)&header;
		क्रम (i = 0; i < (पूर्णांक)माप(काष्ठा trace_header_t); i++)
			header_arr[i] = ia_css_device_load_uपूर्णांक8(start_addr + (i));

		poपूर्णांक_num = header.max_tracer_poपूर्णांकs;

		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, " ver %d %d points\n", header.version,
				    poपूर्णांक_num);

		पंचांगp = header.version;
	पूर्ण
	अगर ((पंचांगp & 0xFF) != TRACER_VER) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "\t\tUnknown version - exiting\n");
		वापस;
	पूर्ण
	अगर (poपूर्णांक_num > max_trace_poपूर्णांकs) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "\t\tToo many points - exiting\n");
		वापस;
	पूर्ण
	/* copy the TPs and find the first 0 */
	क्रम (i = 0; i < poपूर्णांक_num; i++) अणु
		trace_पढ़ो_buf[i] = ia_css_device_load_uपूर्णांक32(start_addr_data +
				    (i * item_size));
		अगर ((limit == (-1)) && (trace_पढ़ो_buf[i] == 0))
			limit = i;
	पूर्ण
	अगर (IS_ISP2401) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "Status:\n");
		क्रम (i = 0; i < SH_CSS_MAX_SP_THREADS; i++)
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "\tT%d: %3d (%02x)  %6d (%04x)  %10d (%08x)\n", i,
					    header.thr_status_byte[i], header.thr_status_byte[i],
					    header.thr_status_word[i], header.thr_status_word[i],
					    header.thr_status_dword[i], header.thr_status_dword[i]);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "Scratch:\n");
		क्रम (i = 0; i < MAX_SCRATCH_DATA; i++)
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%10d (%08x)  ",
					    header.scratch_debug[i], header.scratch_debug[i]);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "\n");
	पूर्ण
	/* two 0s in the beginning: empty buffer */
	अगर ((trace_पढ़ो_buf[0] == 0) && (trace_पढ़ो_buf[1] == 0)) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "\t\tEmpty tracer - exiting\n");
		वापस;
	पूर्ण
	/* no overrun: start from 0 */
	अगर ((limit == poपूर्णांक_num - 1) ||
	    /* first 0 is at the end - border हाल */
	    (trace_पढ़ो_buf[limit + 1] ==
	     0))   /* did not make a full cycle after the स_रखो */
		limit = 0;
	/* overrun: limit is the first non-zero after the first zero */
	अन्यथा
		limit++;

	/* prपूर्णांक the TPs */
	क्रम (i = 0; i < poपूर्णांक_num; i++) अणु
		j = (limit + i) % poपूर्णांक_num;
		अगर (trace_पढ़ो_buf[j]) अणु
			अगर (!IS_ISP2401) अणु
				TRACE_DUMP_FORMAT dump_क्रमmat = FIELD_FORMAT_UNPACK(trace_पढ़ो_buf[j]);
			पूर्ण अन्यथा अणु
				tid_val = FIELD_TID_UNPACK(trace_पढ़ो_buf[j]);
				dump_क्रमmat = TRACE_DUMP_FORMAT_POINT;

				/*
				* When tid value is 111b, the data will be पूर्णांकerpreted dअगरferently:
				* tid val is ignored, major field contains 2 bits (msb) क्रम क्रमmat type
				*/
				अगर (tid_val == FIELD_TID_SEL_FORMAT_PAT) अणु
					dump_क्रमmat = FIELD_FORMAT_UNPACK(trace_पढ़ो_buf[j]);
				पूर्ण
			पूर्ण
			चयन (dump_क्रमmat) अणु
			हाल TRACE_DUMP_FORMAT_POINT:
				ia_css_debug_dtrace(
				    IA_CSS_DEBUG_TRACE,	"\t\t%d %d:%d value - %d\n",
				    j, FIELD_MAJOR_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_MINOR_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_VALUE_UNPACK(trace_पढ़ो_buf[j]));
				अवरोध;
			/* ISP2400 */
			हाल TRACE_DUMP_FORMAT_VALUE24_HEX:
				ia_css_debug_dtrace(
				    IA_CSS_DEBUG_TRACE,	"\t\t%d, %d, 24bit value %x H\n",
				    j,
				    FIELD_MAJOR_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_VALUE_24_UNPACK(trace_पढ़ो_buf[j]));
				अवरोध;
			/* ISP2400 */
			हाल TRACE_DUMP_FORMAT_VALUE24_DEC:
				ia_css_debug_dtrace(
				    IA_CSS_DEBUG_TRACE,	"\t\t%d, %d, 24bit value %d D\n",
				    j,
				    FIELD_MAJOR_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_VALUE_24_UNPACK(trace_पढ़ो_buf[j]));
				अवरोध;
			/* ISP2401 */
			हाल TRACE_DUMP_FORMAT_POINT_NO_TID:
				ia_css_debug_dtrace(
				    IA_CSS_DEBUG_TRACE,	"\t\t%d %d:%d value - %x (%d)\n",
				    j,
				    FIELD_MAJOR_W_FMT_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_MINOR_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_VALUE_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_VALUE_UNPACK(trace_पढ़ो_buf[j]));
				अवरोध;
			/* ISP2401 */
			हाल TRACE_DUMP_FORMAT_VALUE24:
				ia_css_debug_dtrace(
				    IA_CSS_DEBUG_TRACE,	"\t\t%d, %d, 24bit value %x (%d)\n",
				    j,
				    FIELD_MAJOR_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_MAJOR_W_FMT_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_VALUE_24_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_VALUE_24_UNPACK(trace_पढ़ो_buf[j]));
				अवरोध;
			हाल TRACE_DUMP_FORMAT_VALUE24_TIMING:
				ia_css_debug_dtrace(
				    IA_CSS_DEBUG_TRACE,	"\t\t%d, %d, timing %x\n",
				    j,
				    FIELD_MAJOR_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_VALUE_24_UNPACK(trace_पढ़ो_buf[j]));
				अवरोध;
			हाल TRACE_DUMP_FORMAT_VALUE24_TIMING_DELTA:
				ia_css_debug_dtrace(
				    IA_CSS_DEBUG_TRACE,	"\t\t%d, %d, timing delta %x\n",
				    j,
				    FIELD_MAJOR_UNPACK(trace_पढ़ो_buf[j]),
				    FIELD_VALUE_24_UNPACK(trace_पढ़ो_buf[j]));
				अवरोध;
			शेष:
				ia_css_debug_dtrace(
				    IA_CSS_DEBUG_TRACE,
				    "no such trace dump format %d",
				    dump_क्रमmat);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
#अन्यथा
	(व्योम)proc_id;
#पूर्ण_अगर /* HAS_TRACER_V2 */
पूर्ण
#पूर्ण_अगर /* TRACE_ENABLE_SP0 || TRACE_ENABLE_SP1 || TRACE_ENABLE_ISP */

व्योम ia_css_debug_dump_trace(व्योम)
अणु
#अगर TRACE_ENABLE_SP0
	debug_dump_one_trace(TRACE_SP0_ID);
#पूर्ण_अगर
#अगर TRACE_ENABLE_SP1
	debug_dump_one_trace(TRACE_SP1_ID);
#पूर्ण_अगर
#अगर TRACE_ENABLE_ISP
	debug_dump_one_trace(TRACE_ISP_ID);
#पूर्ण_अगर
पूर्ण

/* Tagger state dump function. The tagger is only available when the CSS
 * contains an input प्रणाली (2400 or 2401). */
व्योम ia_css_debug_tagger_state(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक HIVE_ADDR_tagger_frames;
	ia_css_tagger_buf_sp_elem_t tbuf_frames[MAX_CB_ELEMS_FOR_TAGGER];

	HIVE_ADDR_tagger_frames = sh_css_sp_fw.info.sp.tagger_frames_addr;

	/* This variable is not used in crun */
	(व्योम)HIVE_ADDR_tagger_frames;

	/* 2400 and 2401 only have 1 SP, so the tagger lives on SP0 */
	sp_dmem_load(SP0_ID,
		     (अचिन्हित पूर्णांक)sp_address_of(tagger_frames),
		     tbuf_frames,
		     माप(tbuf_frames));

	ia_css_debug_dtrace(2, "Tagger Info:\n");
	क्रम (i = 0; i < MAX_CB_ELEMS_FOR_TAGGER; i++) अणु
		ia_css_debug_dtrace(2, "\t tagger frame[%d]: exp_id=%d, marked=%d, locked=%d\n",
				    i, tbuf_frames[i].exp_id, tbuf_frames[i].mark, tbuf_frames[i].lock);
	पूर्ण
पूर्ण

/* ISP2401 */
व्योम ia_css_debug_pc_dump(sp_ID_t id, अचिन्हित पूर्णांक num_of_dumps)
अणु
	अचिन्हित पूर्णांक pc;
	अचिन्हित पूर्णांक i;
	hrt_data sc = sp_ctrl_load(id, SP_SC_REG);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "SP%-1d Status reg: 0x%X\n", id, sc);
	sc = sp_ctrl_load(id, SP_CTRL_SINK_REG);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "SP%-1d Stall reg: 0x%X\n", id, sc);
	क्रम (i = 0; i < num_of_dumps; i++) अणु
		pc = sp_ctrl_load(id, SP_PC_REG);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "SP%-1d PC: 0x%X\n", id, pc);
	पूर्ण
पूर्ण
