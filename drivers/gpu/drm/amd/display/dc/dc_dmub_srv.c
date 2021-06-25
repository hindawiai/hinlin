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

#समावेश "dc.h"
#समावेश "dc_dmub_srv.h"
#समावेश "../dmub/dmub_srv.h"
#समावेश "dm_helpers.h"

#घोषणा CTX dc_dmub_srv->ctx
#घोषणा DC_LOGGER CTX->logger

अटल व्योम dc_dmub_srv_स्थिरruct(काष्ठा dc_dmub_srv *dc_srv, काष्ठा dc *dc,
				  काष्ठा dmub_srv *dmub)
अणु
	dc_srv->dmub = dmub;
	dc_srv->ctx = dc->ctx;
पूर्ण

काष्ठा dc_dmub_srv *dc_dmub_srv_create(काष्ठा dc *dc, काष्ठा dmub_srv *dmub)
अणु
	काष्ठा dc_dmub_srv *dc_srv =
		kzalloc(माप(काष्ठा dc_dmub_srv), GFP_KERNEL);

	अगर (dc_srv == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dc_dmub_srv_स्थिरruct(dc_srv, dc, dmub);

	वापस dc_srv;
पूर्ण

व्योम dc_dmub_srv_destroy(काष्ठा dc_dmub_srv **dmub_srv)
अणु
	अगर (*dmub_srv) अणु
		kमुक्त(*dmub_srv);
		*dmub_srv = शून्य;
	पूर्ण
पूर्ण

व्योम dc_dmub_srv_cmd_queue(काष्ठा dc_dmub_srv *dc_dmub_srv,
			   जोड़ dmub_rb_cmd *cmd)
अणु
	काष्ठा dmub_srv *dmub = dc_dmub_srv->dmub;
	काष्ठा dc_context *dc_ctx = dc_dmub_srv->ctx;
	क्रमागत dmub_status status;

	status = dmub_srv_cmd_queue(dmub, cmd);
	अगर (status == DMUB_STATUS_OK)
		वापस;

	अगर (status != DMUB_STATUS_QUEUE_FULL)
		जाओ error;

	/* Execute and रुको क्रम queue to become empty again. */
	dc_dmub_srv_cmd_execute(dc_dmub_srv);
	dc_dmub_srv_रुको_idle(dc_dmub_srv);

	/* Requeue the command. */
	status = dmub_srv_cmd_queue(dmub, cmd);
	अगर (status == DMUB_STATUS_OK)
		वापस;

error:
	DC_ERROR("Error queuing DMUB command: status=%d\n", status);
पूर्ण

व्योम dc_dmub_srv_cmd_execute(काष्ठा dc_dmub_srv *dc_dmub_srv)
अणु
	काष्ठा dmub_srv *dmub = dc_dmub_srv->dmub;
	काष्ठा dc_context *dc_ctx = dc_dmub_srv->ctx;
	क्रमागत dmub_status status;

	status = dmub_srv_cmd_execute(dmub);
	अगर (status != DMUB_STATUS_OK)
		DC_ERROR("Error starting DMUB execution: status=%d\n", status);
पूर्ण

व्योम dc_dmub_srv_रुको_idle(काष्ठा dc_dmub_srv *dc_dmub_srv)
अणु
	काष्ठा dmub_srv *dmub = dc_dmub_srv->dmub;
	काष्ठा dc_context *dc_ctx = dc_dmub_srv->ctx;
	क्रमागत dmub_status status;

	status = dmub_srv_रुको_क्रम_idle(dmub, 100000);
	अगर (status != DMUB_STATUS_OK)
		DC_ERROR("Error waiting for DMUB idle: status=%d\n", status);
पूर्ण

bool dc_dmub_srv_cmd_with_reply_data(काष्ठा dc_dmub_srv *dc_dmub_srv, जोड़ dmub_rb_cmd *cmd)
अणु
	काष्ठा dmub_srv *dmub;
	क्रमागत dmub_status status;

	अगर (!dc_dmub_srv || !dc_dmub_srv->dmub)
		वापस false;

	dmub = dc_dmub_srv->dmub;

	status = dmub_srv_cmd_with_reply_data(dmub, cmd);
	अगर (status != DMUB_STATUS_OK) अणु
		DC_LOG_DEBUG("No reply for DMUB command: status=%d\n", status);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम dc_dmub_srv_रुको_phy_init(काष्ठा dc_dmub_srv *dc_dmub_srv)
अणु
	काष्ठा dmub_srv *dmub = dc_dmub_srv->dmub;
	काष्ठा dc_context *dc_ctx = dc_dmub_srv->ctx;
	क्रमागत dmub_status status;

	क्रम (;;) अणु
		/* Wait up to a second क्रम PHY init. */
		status = dmub_srv_रुको_क्रम_phy_init(dmub, 1000000);
		अगर (status == DMUB_STATUS_OK)
			/* Initialization OK */
			अवरोध;

		DC_ERROR("DMCUB PHY init failed: status=%d\n", status);
		ASSERT(0);

		अगर (status != DMUB_STATUS_TIMEOUT)
			/*
			 * Server likely initialized or we करोn't have
			 * DMCUB HW support - this won't end.
			 */
			अवरोध;

		/* Continue spinning so we करोn't hang the ASIC. */
	पूर्ण
पूर्ण

bool dc_dmub_srv_notअगरy_stream_mask(काष्ठा dc_dmub_srv *dc_dmub_srv,
				    अचिन्हित पूर्णांक stream_mask)
अणु
	काष्ठा dmub_srv *dmub;
	स्थिर uपूर्णांक32_t समयout = 30;

	अगर (!dc_dmub_srv || !dc_dmub_srv->dmub)
		वापस false;

	dmub = dc_dmub_srv->dmub;

	वापस dmub_srv_send_gpपूर्णांक_command(
		       dmub, DMUB_GPINT__IDLE_OPT_NOTIFY_STREAM_MASK,
		       stream_mask, समयout) == DMUB_STATUS_OK;
पूर्ण

bool dc_dmub_srv_get_dmub_outbox0_msg(स्थिर काष्ठा dc *dc, काष्ठा dmcub_trace_buf_entry *entry)
अणु
	काष्ठा dmub_srv *dmub = dc->ctx->dmub_srv->dmub;
	वापस dmub_srv_get_outbox0_msg(dmub, entry);
पूर्ण

व्योम dc_dmub_trace_event_control(काष्ठा dc *dc, bool enable)
अणु
	dm_helpers_dmub_outbox0_पूर्णांकerrupt_control(dc->ctx, enable);
पूर्ण
