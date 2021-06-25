<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
 */

#समावेश "dmub_outbox.h"
#समावेश "dc_dmub_srv.h"
#समावेश "dmub/inc/dmub_cmd.h"

/**
 *****************************************************************************
 *  Function: dmub_enable_outbox_notअगरication
 *
 *  @brief
 *		Sends inbox cmd to dmub to enable outbox1 messages with पूर्णांकerrupt.
 *		Dmub sends outbox1 message and triggers outbox1 पूर्णांकerrupt.
 *
 *  @param
 *		[in] dc: dc काष्ठाure
 *
 *  @वापस
 *     None
 *****************************************************************************
 */
व्योम dmub_enable_outbox_notअगरication(काष्ठा dc *dc)
अणु
	जोड़ dmub_rb_cmd cmd;
	काष्ठा dc_context *dc_ctx = dc->ctx;

	स_रखो(&cmd, 0x0, माप(cmd));
	cmd.outbox1_enable.header.type = DMUB_CMD__OUTBOX1_ENABLE;
	cmd.outbox1_enable.header.sub_type = 0;
	cmd.outbox1_enable.header.payload_bytes =
		माप(cmd.outbox1_enable) -
		माप(cmd.outbox1_enable.header);
	cmd.outbox1_enable.enable = true;

	dc_dmub_srv_cmd_queue(dc_ctx->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc_ctx->dmub_srv);
	dc_dmub_srv_रुको_idle(dc_ctx->dmub_srv);
पूर्ण
