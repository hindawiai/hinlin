<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _DMUB_DC_SRV_H_
#घोषणा _DMUB_DC_SRV_H_

#समावेश "os_types.h"
#समावेश "dmub/dmub_srv.h"

काष्ठा dmub_srv;
काष्ठा dc;

काष्ठा dc_reg_helper_state अणु
	bool gather_in_progress;
	uपूर्णांक32_t same_addr_count;
	bool should_burst_ग_लिखो;
	जोड़ dmub_rb_cmd cmd_data;
	अचिन्हित पूर्णांक reg_seq_count;
पूर्ण;

काष्ठा dc_dmub_srv अणु
	काष्ठा dmub_srv *dmub;
	काष्ठा dc_reg_helper_state reg_helper_offload;

	काष्ठा dc_context *ctx;
	व्योम *dm;
पूर्ण;

व्योम dc_dmub_srv_cmd_queue(काष्ठा dc_dmub_srv *dc_dmub_srv,
			   जोड़ dmub_rb_cmd *cmd);

व्योम dc_dmub_srv_cmd_execute(काष्ठा dc_dmub_srv *dc_dmub_srv);

व्योम dc_dmub_srv_रुको_idle(काष्ठा dc_dmub_srv *dc_dmub_srv);

व्योम dc_dmub_srv_रुको_phy_init(काष्ठा dc_dmub_srv *dc_dmub_srv);

bool dc_dmub_srv_cmd_with_reply_data(काष्ठा dc_dmub_srv *dc_dmub_srv, जोड़ dmub_rb_cmd *cmd);

bool dc_dmub_srv_notअगरy_stream_mask(काष्ठा dc_dmub_srv *dc_dmub_srv,
				    अचिन्हित पूर्णांक stream_mask);

bool dc_dmub_srv_get_dmub_outbox0_msg(स्थिर काष्ठा dc *dc, काष्ठा dmcub_trace_buf_entry *entry);

व्योम dc_dmub_trace_event_control(काष्ठा dc *dc, bool enable);

#पूर्ण_अगर /* _DMUB_DC_SRV_H_ */
