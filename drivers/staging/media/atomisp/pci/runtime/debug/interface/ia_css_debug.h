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

#अगर_अघोषित _IA_CSS_DEBUG_H_
#घोषणा _IA_CSS_DEBUG_H_

/*! \पile */

#समावेश <type_support.h>
#समावेश <मानकतर्क.स>
#समावेश "ia_css_types.h"
#समावेश "ia_css_binary.h"
#समावेश "ia_css_frame_public.h"
#समावेश "ia_css_pipe_public.h"
#समावेश "ia_css_stream_public.h"
#समावेश "ia_css_metadata.h"
#समावेश "sh_css_internal.h"
/* ISP2500 */
#समावेश "ia_css_pipe.h"

/* available levels */
/*! Level क्रम tracing errors */
#घोषणा IA_CSS_DEBUG_ERROR   1
/*! Level क्रम tracing warnings */
#घोषणा IA_CSS_DEBUG_WARNING 3
/*! Level क्रम tracing debug messages */
#घोषणा IA_CSS_DEBUG_VERBOSE   5
/*! Level क्रम tracing trace messages a.o. ia_css खुला function calls */
#घोषणा IA_CSS_DEBUG_TRACE   6
/*! Level क्रम tracing trace messages a.o. ia_css निजी function calls */
#घोषणा IA_CSS_DEBUG_TRACE_PRIVATE   7
/*! Level क्रम tracing parameter messages e.g. in and out params of functions */
#घोषणा IA_CSS_DEBUG_PARAM   8
/*! Level क्रम tracing info messages */
#घोषणा IA_CSS_DEBUG_INFO    9

/* Global variable which controls the verbosity levels of the debug tracing */
बाह्य पूर्णांक dbg_level;

/*! @brief Enum defining the dअगरferent isp parameters to dump.
 *  Values can be combined to dump a combination of sets.
 */
क्रमागत ia_css_debug_enable_param_dump अणु
	IA_CSS_DEBUG_DUMP_FPN = 1 << 0, /** FPN table */
	IA_CSS_DEBUG_DUMP_OB = 1 << 1,  /** OB table */
	IA_CSS_DEBUG_DUMP_SC = 1 << 2,  /** Shading table */
	IA_CSS_DEBUG_DUMP_WB = 1 << 3,  /** White balance */
	IA_CSS_DEBUG_DUMP_DP = 1 << 4,  /** Defect Pixel */
	IA_CSS_DEBUG_DUMP_BNR = 1 << 5,  /** Bayer Noise Reductions */
	IA_CSS_DEBUG_DUMP_S3A = 1 << 6,  /** 3A Statistics */
	IA_CSS_DEBUG_DUMP_DE = 1 << 7,  /** De Mosaicing */
	IA_CSS_DEBUG_DUMP_YNR = 1 << 8,  /** Luma Noise Reduction */
	IA_CSS_DEBUG_DUMP_CSC = 1 << 9,  /** Color Space Conversion */
	IA_CSS_DEBUG_DUMP_GC = 1 << 10,  /** Gamma Correction */
	IA_CSS_DEBUG_DUMP_TNR = 1 << 11,  /** Temporal Noise Reduction */
	IA_CSS_DEBUG_DUMP_ANR = 1 << 12,  /** Advanced Noise Reduction */
	IA_CSS_DEBUG_DUMP_CE = 1 << 13,  /** Chroma Enhancement */
	IA_CSS_DEBUG_DUMP_ALL = 1 << 14  /** Dump all device parameters */
पूर्ण;

#घोषणा IA_CSS_ERROR(fmt, ...) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR, \
		"%s() %d: error: " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)

#घोषणा IA_CSS_WARNING(fmt, ...) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_WARNING, \
		"%s() %d: warning: " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)

/* Logging macros क्रम खुला functions (API functions) */
#घोषणा IA_CSS_ENTER(fmt, ...) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, \
		"%s(): enter: " fmt "\n", __func__, ##__VA_ARGS__)

/* Use this macro क्रम small functions that करो not call other functions. */
#घोषणा IA_CSS_ENTER_LEAVE(fmt, ...) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, \
		"%s(): enter: leave: " fmt "\n", __func__, ##__VA_ARGS__)

#घोषणा IA_CSS_LEAVE(fmt, ...) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, \
		"%s(): leave: " fmt "\n", __func__, ##__VA_ARGS__)

/* Shorthand क्रम वापसing an पूर्णांक वापस value */
#घोषणा IA_CSS_LEAVE_ERR(__err) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, \
		"%s() %d: leave: return_err=%d\n", __func__, __LINE__, __err)

/* Use this macro क्रम logging other than enter/leave.
 * Note that this macro always uses the PRIVATE logging level.
 */
#घोषणा IA_CSS_LOG(fmt, ...) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, \
		"%s(): " fmt "\n", __func__, ##__VA_ARGS__)

/* Logging macros क्रम non-API functions. These have a lower trace level */
#घोषणा IA_CSS_ENTER_PRIVATE(fmt, ...) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, \
		"%s(): enter: " fmt "\n", __func__, ##__VA_ARGS__)

#घोषणा IA_CSS_LEAVE_PRIVATE(fmt, ...) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, \
		"%s(): leave: " fmt "\n", __func__, ##__VA_ARGS__)

/* Shorthand क्रम वापसing an पूर्णांक वापस value */
#घोषणा IA_CSS_LEAVE_ERR_PRIVATE(__err) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, \
		"%s() %d: leave: return_err=%d\n", __func__, __LINE__, __err)

/* Use this macro क्रम small functions that करो not call other functions. */
#घोषणा IA_CSS_ENTER_LEAVE_PRIVATE(fmt, ...) \
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, \
		"%s(): enter: leave: " fmt "\n", __func__, ##__VA_ARGS__)

/*! @brief Function क्रम tracing to the provided म_लिखो function in the
 *	environment.
 * @param[in]	level		Level of the message.
 * @param[in]	fmt		म_लिखो like क्रमmat string
 * @param[in]	args		arguments क्रम the क्रमmat string
 */
अटल अंतरभूत व्योम __म_लिखो(2, 0) ia_css_debug_vdtrace(अचिन्हित पूर्णांक level,
						       स्थिर अक्षर *fmt,
						       बहु_सूची args)
अणु
	अगर (dbg_level >= level)
		sh_css_vprपूर्णांक(fmt, args);
पूर्ण

__म_लिखो(2, 3) व्योम ia_css_debug_dtrace(अचिन्हित पूर्णांक level,
					स्थिर अक्षर *fmt, ...);

/*! @brief Dump sp thपढ़ो's stack contents
 * SP thपढ़ो's stack contents are set to 0xcafecafe. This function dumps the
 * stack to inspect अगर the stack's boundaries are compromised.
 * @वापस	None
 */
व्योम ia_css_debug_dump_sp_stack_info(व्योम);

/*! @brief Function to set the global dtrace verbosity level.
 * @param[in]	trace_level	Maximum level of the messages to be traced.
 * @वापस	None
 */
व्योम ia_css_debug_set_dtrace_level(
    स्थिर अचिन्हित पूर्णांक	trace_level);

/*! @brief Function to get the global dtrace verbosity level.
 * @वापस	global dtrace verbosity level
 */
अचिन्हित पूर्णांक ia_css_debug_get_dtrace_level(व्योम);

/*! @brief Dump isp hardware state.
 * Dumps the isp hardware state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_isp_state(व्योम);

/*! @brief Dump sp hardware state.
 * Dumps the sp hardware state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_sp_state(व्योम);

/* ISP2401 */
/*! @brief Dump GAC hardware state.
 * Dumps the GAC ACB hardware रेजिस्टरs. may be useful क्रम
 * detecting a GAC which got hang.
 * @वापस	None
 */
व्योम ia_css_debug_dump_gac_state(व्योम);

/*! @brief Dump dma controller state.
 * Dumps the dma controller state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_dma_state(व्योम);

/*! @brief Dump पूर्णांकernal sp software state.
 * Dumps the sp software state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_sp_sw_debug_info(व्योम);

/*! @brief Dump all related hardware state to the trace output
 * @param[in]  context	String to identअगरy context in output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_debug_info(
    स्थिर अक्षर	*context);

#अगर SP_DEBUG != SP_DEBUG_NONE
व्योम ia_css_debug_prपूर्णांक_sp_debug_state(
    स्थिर काष्ठा sh_css_sp_debug_state *state);
#पूर्ण_अगर

/*! @brief Dump all related binary info data
 * @param[in]  bi	Binary info काष्ठा.
 * @वापस	None
 */
व्योम ia_css_debug_binary_prपूर्णांक(
    स्थिर काष्ठा ia_css_binary *bi);

व्योम ia_css_debug_sp_dump_mipi_fअगरo_high_water(व्योम);

/*! @brief Dump isp gdc fअगरo state to the trace output
 * Dumps the isp gdc fअगरo state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_isp_gdc_fअगरo_state(व्योम);

/*! @brief Dump dma isp fअगरo state
 * Dumps the dma isp fअगरo state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_dma_isp_fअगरo_state(व्योम);

/*! @brief Dump dma sp fअगरo state
 * Dumps the dma sp fअगरo state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_dma_sp_fअगरo_state(व्योम);

/*! \मrief Dump pअगर A isp fअगरo state
 * Dumps the primary input क्रमmatter state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_pअगर_a_isp_fअगरo_state(व्योम);

/*! \मrief Dump pअगर B isp fअगरo state
 * Dumps the primary input क्रमmatter state to tracing output.
 * \लeturn	None
 */
व्योम ia_css_debug_dump_pअगर_b_isp_fअगरo_state(व्योम);

/*! @brief Dump stream-to-memory sp fअगरo state
 * Dumps the stream-to-memory block state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_str2mem_sp_fअगरo_state(व्योम);

/*! @brief Dump isp sp fअगरo state
 * Dumps the isp sp fअगरo state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_isp_sp_fअगरo_state(व्योम);

/*! @brief Dump all fअगरo state info to the output
 * Dumps all fअगरo state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_all_fअगरo_state(व्योम);

/*! @brief Dump the rx state to the output
 * Dumps the rx state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_rx_state(व्योम);

/*! @brief Dump the input प्रणाली state to the output
 * Dumps the input प्रणाली state to tracing output.
 * @वापस	None
 */
व्योम ia_css_debug_dump_isys_state(व्योम);

/*! @brief Dump the frame info to the trace output
 * Dumps the frame info to tracing output.
 * @param[in]	frame		poपूर्णांकer to काष्ठा ia_css_frame
 * @param[in]	descr		description output aदीर्घ with the frame info
 * @वापस	None
 */
व्योम ia_css_debug_frame_prपूर्णांक(
    स्थिर काष्ठा ia_css_frame	*frame,
    स्थिर अक्षर	*descr);

/*! @brief Function to enable sp sleep mode.
 * Function that enables sp sleep mode
 * @param[in]	mode		indicates when to put sp to sleep
 * @वापस	None
 */
व्योम ia_css_debug_enable_sp_sleep_mode(क्रमागत ia_css_sp_sleep_mode mode);

/*! @brief Function to wake up sp when in sleep mode.
 * After sp has been put to sleep, use this function to let it जारी
 * to run again.
 * @वापस	None
 */
व्योम ia_css_debug_wake_up_sp(व्योम);

/*! @brief Function to dump isp parameters.
 * Dump isp parameters to tracing output
 * @param[in]	stream		poपूर्णांकer to ia_css_stream काष्ठा
 * @param[in]	enable		flag indicating which parameters to dump.
 * @वापस	None
 */
व्योम ia_css_debug_dump_isp_params(काष्ठा ia_css_stream *stream,
				  अचिन्हित पूर्णांक enable);

/*! @brief Function to dump some sp perक्रमmance counters.
 * Dump sp perक्रमmance counters, currently input प्रणाली errors.
 * @वापस	None
 */
व्योम ia_css_debug_dump_perf_counters(व्योम);

#अगर_घोषित HAS_WATCHDOG_SP_THREAD_DEBUG
व्योम sh_css_dump_thपढ़ो_रुको_info(व्योम);
व्योम sh_css_dump_pipe_stage_info(व्योम);
व्योम sh_css_dump_pipe_stripe_info(व्योम);
#पूर्ण_अगर

व्योम ia_css_debug_dump_isp_binary(व्योम);

व्योम sh_css_dump_sp_raw_copy_linecount(bool reduced);

/*! @brief Dump the resolution info to the trace output
 * Dumps the resolution info to the trace output.
 * @param[in]	res	poपूर्णांकer to काष्ठा ia_css_resolution
 * @param[in]	label	description of resolution output
 * @वापस	None
 */
व्योम ia_css_debug_dump_resolution(
    स्थिर काष्ठा ia_css_resolution *res,
    स्थिर अक्षर *label);

/*! @brief Dump the frame info to the trace output
 * Dumps the frame info to the trace output.
 * @param[in]	info	poपूर्णांकer to काष्ठा ia_css_frame_info
 * @param[in]	label	description of frame_info output
 * @वापस	None
 */
व्योम ia_css_debug_dump_frame_info(
    स्थिर काष्ठा ia_css_frame_info *info,
    स्थिर अक्षर *label);

/*! @brief Dump the capture config info to the trace output
 * Dumps the capture config info to the trace output.
 * @param[in]	config	poपूर्णांकer to काष्ठा ia_css_capture_config
 * @वापस	None
 */
व्योम ia_css_debug_dump_capture_config(
    स्थिर काष्ठा ia_css_capture_config *config);

/*! @brief Dump the pipe extra config info to the trace output
 * Dumps the pipe extra config info to the trace output.
 * @param[in]	extra_config	poपूर्णांकer to काष्ठा ia_css_pipe_extra_config
 * @वापस	None
 */
व्योम ia_css_debug_dump_pipe_extra_config(
    स्थिर काष्ठा ia_css_pipe_extra_config *extra_config);

/*! @brief Dump the pipe config info to the trace output
 * Dumps the pipe config info to the trace output.
 * @param[in]	config	poपूर्णांकer to काष्ठा ia_css_pipe_config
 * @वापस	None
 */
व्योम ia_css_debug_dump_pipe_config(
    स्थिर काष्ठा ia_css_pipe_config *config);

/*! @brief Dump the stream config source info to the trace output
 * Dumps the stream config source info to the trace output.
 * @param[in]	config	poपूर्णांकer to काष्ठा ia_css_stream_config
 * @वापस	None
 */
व्योम ia_css_debug_dump_stream_config_source(
    स्थिर काष्ठा ia_css_stream_config *config);

/*! @brief Dump the mipi buffer config info to the trace output
 * Dumps the mipi buffer config info to the trace output.
 * @param[in]	config	poपूर्णांकer to काष्ठा ia_css_mipi_buffer_config
 * @वापस	None
 */
व्योम ia_css_debug_dump_mipi_buffer_config(
    स्थिर काष्ठा ia_css_mipi_buffer_config *config);

/*! @brief Dump the metadata config info to the trace output
 * Dumps the metadata config info to the trace output.
 * @param[in]	config	poपूर्णांकer to काष्ठा ia_css_metadata_config
 * @वापस	None
 */
व्योम ia_css_debug_dump_metadata_config(
    स्थिर काष्ठा ia_css_metadata_config *config);

/*! @brief Dump the stream config info to the trace output
 * Dumps the stream config info to the trace output.
 * @param[in]	config		poपूर्णांकer to काष्ठा ia_css_stream_config
 * @param[in]	num_pipes	number of pipes क्रम the stream
 * @वापस	None
 */
व्योम ia_css_debug_dump_stream_config(
    स्थिर काष्ठा ia_css_stream_config *config,
    पूर्णांक num_pipes);

/*! @brief Dump the state of the SP tagger
 * Dumps the पूर्णांकernal state of the SP tagger
 * @वापस	None
 */
व्योम ia_css_debug_tagger_state(व्योम);

/**
 * @brief Initialize the debug mode.
 *
 * WARNING:
 * This API should be called ONLY once in the debug mode.
 *
 * @वापस
 *	- true, अगर it is successful.
 *	- false, otherwise.
 */
bool ia_css_debug_mode_init(व्योम);

/**
 * @brief Disable the DMA channel.
 *
 * @param[in]	dma_ID		The ID of the target DMA.
 * @param[in]	channel_id	The ID of the target DMA channel.
 * @param[in]	request_type	The type of the DMA request.
 *				For example:
 *				- "0" indicates the writing request.
 *				- "1" indicates the पढ़ोing request.
 *
 * This is part of the DMA API -> dma.h
 *
 * @वापस
 *	- true, अगर it is successful.
 *	- false, otherwise.
 */
bool ia_css_debug_mode_disable_dma_channel(
    पूर्णांक dma_ID,
    पूर्णांक channel_id,
    पूर्णांक request_type);
/**
 * @brief Enable the DMA channel.
 *
 * @param[in]	dma_ID		The ID of the target DMA.
 * @param[in]	channel_id	The ID of the target DMA channel.
 * @param[in]	request_type	The type of the DMA request.
 *				For example:
 *				- "0" indicates the writing request.
 *				- "1" indicates the पढ़ोing request.
 *
 * @वापस
 *	- true, अगर it is successful.
 *	- false, otherwise.
 */
bool ia_css_debug_mode_enable_dma_channel(
    पूर्णांक dma_ID,
    पूर्णांक channel_id,
    पूर्णांक request_type);

/**
 * @brief Dump tracer data.
 * [Currently support is only क्रम SKC]
 *
 * @वापस
 *	- none.
 */
व्योम ia_css_debug_dump_trace(व्योम);

/* ISP2401 */
/**
 * @brief Program counter dumping (in loop)
 *
 * @param[in]	id		The ID of the SP
 * @param[in]	num_of_dumps	The number of dumps
 *
 * @वापस
 *	- none
 */
व्योम ia_css_debug_pc_dump(sp_ID_t id, अचिन्हित पूर्णांक num_of_dumps);

/* ISP2500 */
/*! @brief Dump all states क्रम ISP hang हाल.
 * Dumps the ISP previous and current configurations
 * GACs status, SP0/1 statuses.
 *
 * @param[in]	pipe	The current pipe
 *
 * @वापस	None
 */
व्योम ia_css_debug_dump_hang_status(
    काष्ठा ia_css_pipe *pipe);

/*! @brief External command handler
 * External command handler
 *
 * @वापस	None
 */
व्योम ia_css_debug_ext_command_handler(व्योम);

#पूर्ण_अगर /* _IA_CSS_DEBUG_H_ */
