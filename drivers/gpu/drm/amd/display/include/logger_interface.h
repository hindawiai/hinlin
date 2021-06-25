<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_LOGGER_INTERFACE_H__
#घोषणा __DAL_LOGGER_INTERFACE_H__

#समावेश "logger_types.h"

काष्ठा dc_context;
काष्ठा dc_link;
काष्ठा dc_surface_update;
काष्ठा resource_context;
काष्ठा dc_state;

/*
 *
 * DAL logger functionality
 *
 */

व्योम pre_surface_trace(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_plane_state *स्थिर *plane_states,
		पूर्णांक surface_count);

व्योम update_surface_trace(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_surface_update *updates,
		पूर्णांक surface_count);

व्योम post_surface_trace(काष्ठा dc *dc);

व्योम context_timing_trace(
		काष्ठा dc *dc,
		काष्ठा resource_context *res_ctx);

व्योम context_घड़ी_प्रकारrace(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);

/* Any function which is empty or have incomplete implementation should be
 * marked by this macro.
 * Note that the message will be prपूर्णांकed exactly once क्रम every function
 * it is used in order to aव्योम repeating of the same message. */

#घोषणा DAL_LOGGER_NOT_IMPL(fmt, ...) \
	करो अणु \
		अटल bool prपूर्णांक_not_impl = true; \
		अगर (prपूर्णांक_not_impl == true) अणु \
			prपूर्णांक_not_impl = false; \
			DRM_WARN("DAL_NOT_IMPL: " fmt, ##__VA_ARGS__); \
		पूर्ण \
	पूर्ण जबतक (0)

/******************************************************************************
 * Convenience macros to save on typing.
 *****************************************************************************/

#घोषणा DC_ERROR(...) \
		करो अणु \
			(व्योम)(dc_ctx); \
			DC_LOG_ERROR(__VA_ARGS__); \
		पूर्ण जबतक (0)

#घोषणा DC_SYNC_INFO(...) \
		करो अणु \
			(व्योम)(dc_ctx); \
			DC_LOG_SYNC(__VA_ARGS__); \
		पूर्ण जबतक (0)

/* Connectivity log क्रमmat:
 * [समय stamp]   [drm] [Major_minor] [connector name] message.....
 * eg:
 * [   26.590965] [drm] [Conn_LKTN]	  [DP-1] HBRx4 pass VS=0, PE=0^
 * [   26.881060] [drm] [Conn_Mode]	  [DP-1] अणु2560x1080, 2784x1111@185580Khzपूर्ण^
 */

#घोषणा CONN_DATA_DETECT(link, hex_data, hex_len, ...) \
		करो अणु \
			(व्योम)(link); \
			DC_LOG_EVENT_DETECTION(__VA_ARGS__); \
		पूर्ण जबतक (0)

#घोषणा CONN_DATA_LINK_LOSS(link, hex_data, hex_len, ...) \
		करो अणु \
			(व्योम)(link); \
			DC_LOG_EVENT_LINK_LOSS(__VA_ARGS__); \
		पूर्ण जबतक (0)

#घोषणा CONN_MSG_LT(link, ...) \
		करो अणु \
			(व्योम)(link); \
			DC_LOG_EVENT_LINK_TRAINING(__VA_ARGS__); \
		पूर्ण जबतक (0)

#घोषणा CONN_MSG_MODE(link, ...) \
		करो अणु \
			(व्योम)(link); \
			DC_LOG_EVENT_MODE_SET(__VA_ARGS__); \
		पूर्ण जबतक (0)

/*
 * Display Test Next logging
 */
#घोषणा DTN_INFO_BEGIN() \
	dm_dtn_log_begin(dc_ctx, log_ctx)

#घोषणा DTN_INFO(msg, ...) \
	dm_dtn_log_append_v(dc_ctx, log_ctx, msg, ##__VA_ARGS__)

#घोषणा DTN_INFO_END() \
	dm_dtn_log_end(dc_ctx, log_ctx)

#घोषणा PERFORMANCE_TRACE_START() \
	अचिन्हित दीर्घ दीर्घ perf_trc_start_sपंचांगp = dm_get_बारtamp(dc->ctx)

#घोषणा PERFORMANCE_TRACE_END() \
	करो अणु \
		अचिन्हित दीर्घ दीर्घ perf_trc_end_sपंचांगp = dm_get_बारtamp(dc->ctx); \
		अगर (dc->debug.perक्रमmance_trace) अणु \
			DC_LOG_PERF_TRACE("%s duration: %lld ticks\n", __func__, \
				perf_trc_end_sपंचांगp - perf_trc_start_sपंचांगp); \
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा DISPLAY_STATS_BEGIN(entry) (व्योम)(entry)

#घोषणा DISPLAY_STATS(msg, ...) DC_LOG_PERF_TRACE(msg, __VA_ARGS__)

#घोषणा DISPLAY_STATS_END(entry) (व्योम)(entry)

#घोषणा LOG_GAMMA_WRITE(msg, ...)

#पूर्ण_अगर /* __DAL_LOGGER_INTERFACE_H__ */
