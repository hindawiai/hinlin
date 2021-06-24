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

/**
 * This file defines helper functions provided by the Display Manager to
 * Display Core.
 */
#अगर_अघोषित __DM_HELPERS__
#घोषणा __DM_HELPERS__

#समावेश "dc_types.h"
#समावेश "dc.h"

काष्ठा dp_mst_stream_allocation_table;

/*
 * Allocate memory accessible by the GPU
 *
 * frame buffer allocations must be aligned to a 4096-byte boundary
 *
 * Returns भव address, sets addr to physical address
 */
व्योम *dm_helpers_allocate_gpu_mem(
		काष्ठा dc_context *ctx,
		क्रमागत dc_gpu_mem_alloc_type type,
		माप_प्रकार size,
		दीर्घ दीर्घ *addr);

/*
 * Free the GPU-accessible memory at the भव address pvMem
 */
व्योम dm_helpers_मुक्त_gpu_mem(
		काष्ठा dc_context *ctx,
		क्रमागत dc_gpu_mem_alloc_type type,
		व्योम *pvMem);

क्रमागत dc_edid_status dm_helpers_parse_edid_caps(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dc_edid *edid,
	काष्ठा dc_edid_caps *edid_caps);


/*
 * Update DP branch info
 */
व्योम dm_helpers_dp_update_branch_info(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_link *link);

/*
 * Writes payload allocation table in immediate करोwnstream device.
 */
bool dm_helpers_dp_mst_ग_लिखो_payload_allocation_table(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा dp_mst_stream_allocation_table *proposed_table,
		bool enable);

/*
 * poll pending करोwn reply
 */
व्योम dm_helpers_dp_mst_poll_pending_करोwn_reply(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dc_link *link);

/*
 * Clear payload allocation table beक्रमe enable MST DP link.
 */
व्योम dm_helpers_dp_mst_clear_payload_allocation_table(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dc_link *link);

/*
 * Polls क्रम ACT (allocation change trigger) handled and
 */
क्रमागत act_वापस_status dm_helpers_dp_mst_poll_क्रम_allocation_change_trigger(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_stream_state *stream);
/*
 * Sends ALLOCATE_PAYLOAD message.
 */
bool dm_helpers_dp_mst_send_payload_allocation(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_stream_state *stream,
		bool enable);

bool dm_helpers_dp_mst_start_top_mgr(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_link *link,
		bool boot);

व्योम dm_helpers_dp_mst_stop_top_mgr(
		काष्ठा dc_context *ctx,
		काष्ठा dc_link *link);
/**
 * OS specअगरic aux पढ़ो callback.
 */
bool dm_helpers_dp_पढ़ो_dpcd(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_link *link,
		uपूर्णांक32_t address,
		uपूर्णांक8_t *data,
		uपूर्णांक32_t size);

/**
 * OS specअगरic aux ग_लिखो callback.
 */
bool dm_helpers_dp_ग_लिखो_dpcd(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_link *link,
		uपूर्णांक32_t address,
		स्थिर uपूर्णांक8_t *data,
		uपूर्णांक32_t size);

bool dm_helpers_submit_i2c(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_link *link,
		काष्ठा i2c_command *cmd);

bool dm_helpers_dp_ग_लिखो_dsc_enable(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_stream_state *stream,
		bool enable
);
bool dm_helpers_is_dp_sink_present(
		काष्ठा dc_link *link);

व्योम dm_helpers_mst_enable_stream_features(स्थिर काष्ठा dc_stream_state *stream);

क्रमागत dc_edid_status dm_helpers_पढ़ो_local_edid(
		काष्ठा dc_context *ctx,
		काष्ठा dc_link *link,
		काष्ठा dc_sink *sink);

व्योम dm_set_dcn_घड़ीs(
		काष्ठा dc_context *ctx,
		काष्ठा dc_घड़ीs *clks);

bool dm_helpers_dmub_outbox0_पूर्णांकerrupt_control(काष्ठा dc_context *ctx, bool enable);

#पूर्ण_अगर /* __DM_HELPERS__ */
