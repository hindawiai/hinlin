<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Author: Hugues Fruchet <hugues.fruchet@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/rpmsg.h>

#समावेश "delta.h"
#समावेश "delta-ipc.h"
#समावेश "delta-mem.h"

#घोषणा IPC_TIMEOUT 100
#घोषणा IPC_SANITY_TAG 0xDEADBEEF

क्रमागत delta_ipc_fw_command अणु
	DELTA_IPC_OPEN,
	DELTA_IPC_SET_STREAM,
	DELTA_IPC_DECODE,
	DELTA_IPC_CLOSE
पूर्ण;

#घोषणा to_rpmsg_driver(__drv) container_of(__drv, काष्ठा rpmsg_driver, drv)
#घोषणा to_delta(__d) container_of(__d, काष्ठा delta_dev, rpmsg_driver)

#घोषणा to_ctx(hdl) ((काष्ठा delta_ipc_ctx *)hdl)
#घोषणा to_pctx(ctx) container_of(ctx, काष्ठा delta_ctx, ipc_ctx)

काष्ठा delta_ipc_header_msg अणु
	u32 tag;
	व्योम *host_hdl;
	u32 copro_hdl;
	u32 command;
पूर्ण;

#घोषणा to_host_hdl(ctx) ((व्योम *)ctx)

#घोषणा msg_to_ctx(msg) ((काष्ठा delta_ipc_ctx *)(msg)->header.host_hdl)
#घोषणा msg_to_copro_hdl(msg) ((msg)->header.copro_hdl)

अटल अंतरभूत dma_addr_t to_paddr(काष्ठा delta_ipc_ctx *ctx, व्योम *vaddr)
अणु
	वापस (ctx->ipc_buf->paddr + (vaddr - ctx->ipc_buf->vaddr));
पूर्ण

अटल अंतरभूत bool is_valid_data(काष्ठा delta_ipc_ctx *ctx,
				 व्योम *data, u32 size)
अणु
	वापस ((data >= ctx->ipc_buf->vaddr) &&
		((data + size) <= (ctx->ipc_buf->vaddr + ctx->ipc_buf->size)));
पूर्ण

/*
 * IPC shared memory (@ipc_buf_size, @ipc_buf_paddr) is sent to copro
 * at each instance खोलोing. This memory is allocated by IPC client
 * and given through delta_ipc_खोलो(). All messages parameters
 * (खोलो, set_stream, decode) will have their phy address within
 * this IPC shared memory, aव्योमing de-facto recopies inside delta-ipc.
 * All the below messages काष्ठाures are used on both host and firmware
 * side and are packed (use only of 32 bits size fields in messages
 * काष्ठाures to ensure packing):
 * - काष्ठा delta_ipc_खोलो_msg
 * - काष्ठा delta_ipc_set_stream_msg
 * - काष्ठा delta_ipc_decode_msg
 * - काष्ठा delta_ipc_बंद_msg
 * - काष्ठा delta_ipc_cb_msg
 */
काष्ठा delta_ipc_खोलो_msg अणु
	काष्ठा delta_ipc_header_msg header;
	u32 ipc_buf_size;
	dma_addr_t ipc_buf_paddr;
	अक्षर name[32];
	u32 param_size;
	dma_addr_t param_paddr;
पूर्ण;

काष्ठा delta_ipc_set_stream_msg अणु
	काष्ठा delta_ipc_header_msg header;
	u32 param_size;
	dma_addr_t param_paddr;
पूर्ण;

काष्ठा delta_ipc_decode_msg अणु
	काष्ठा delta_ipc_header_msg header;
	u32 param_size;
	dma_addr_t param_paddr;
	u32 status_size;
	dma_addr_t status_paddr;
पूर्ण;

काष्ठा delta_ipc_बंद_msg अणु
	काष्ठा delta_ipc_header_msg header;
पूर्ण;

काष्ठा delta_ipc_cb_msg अणु
	काष्ठा delta_ipc_header_msg header;
	पूर्णांक err;
पूर्ण;

अटल व्योम build_msg_header(काष्ठा delta_ipc_ctx *ctx,
			     क्रमागत delta_ipc_fw_command command,
			     काष्ठा delta_ipc_header_msg *header)
अणु
	header->tag = IPC_SANITY_TAG;
	header->host_hdl = to_host_hdl(ctx);
	header->copro_hdl = ctx->copro_hdl;
	header->command = command;
पूर्ण

पूर्णांक delta_ipc_खोलो(काष्ठा delta_ctx *pctx, स्थिर अक्षर *name,
		   काष्ठा delta_ipc_param *param, u32 ipc_buf_size,
		   काष्ठा delta_buf **ipc_buf, व्योम **hdl)
अणु
	काष्ठा delta_dev *delta = pctx->dev;
	काष्ठा rpmsg_device *rpmsg_device = delta->rpmsg_device;
	काष्ठा delta_ipc_ctx *ctx = &pctx->ipc_ctx;
	काष्ठा delta_ipc_खोलो_msg msg;
	काष्ठा delta_buf *buf = &ctx->ipc_buf_काष्ठा;
	पूर्णांक ret;

	अगर (!rpmsg_device) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to open, rpmsg is not initialized\n",
			pctx->name);
		pctx->sys_errors++;
		वापस -EINVAL;
	पूर्ण

	अगर (!name) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to open, no name given\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!param || !param->data || !param->size) अणु
		dev_err(delta->dev,
			"%s  ipc: failed to open, empty parameter\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!ipc_buf_size) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to open, no size given for ipc buffer\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (param->size > ipc_buf_size) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to open, too large ipc parameter (%d bytes while max %d expected)\n",
			pctx->name,
			param->size, ctx->ipc_buf->size);
		वापस -EINVAL;
	पूर्ण

	/* init */
	init_completion(&ctx->करोne);

	/*
	 * allocation of contiguous buffer क्रम
	 * data of commands exchanged between
	 * host and firmware coprocessor
	 */
	ret = hw_alloc(pctx, ipc_buf_size,
		       "ipc data buffer", buf);
	अगर (ret)
		वापस ret;
	ctx->ipc_buf = buf;

	/* build rpmsg message */
	build_msg_header(ctx, DELTA_IPC_OPEN, &msg.header);

	msg.ipc_buf_size = ipc_buf_size;
	msg.ipc_buf_paddr = ctx->ipc_buf->paddr;

	स_नकल(msg.name, name, माप(msg.name));
	msg.name[माप(msg.name) - 1] = 0;

	msg.param_size = param->size;
	स_नकल(ctx->ipc_buf->vaddr, param->data, msg.param_size);
	msg.param_paddr = ctx->ipc_buf->paddr;

	/* send it */
	ret = rpmsg_send(rpmsg_device->ept, &msg, माप(msg));
	अगर (ret) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to open, rpmsg_send failed (%d) for DELTA_IPC_OPEN (name=%s, size=%d, data=%p)\n",
			pctx->name,
			ret, name, param->size, param->data);
		जाओ err;
	पूर्ण

	/* रुको क्रम acknowledge */
	अगर (!रुको_क्रम_completion_समयout
	    (&ctx->करोne, msecs_to_jअगरfies(IPC_TIMEOUT))) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to open, timeout waiting for DELTA_IPC_OPEN callback (name=%s, size=%d, data=%p)\n",
			pctx->name,
			name, param->size, param->data);
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	/* command completed, check error */
	अगर (ctx->cb_err) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to open, DELTA_IPC_OPEN completed but with error (%d) (name=%s, size=%d, data=%p)\n",
			pctx->name,
			ctx->cb_err, name, param->size, param->data);
		ret = -EIO;
		जाओ err;
	पूर्ण

	*ipc_buf = ctx->ipc_buf;
	*hdl = (व्योम *)ctx;

	वापस 0;

err:
	pctx->sys_errors++;
	hw_मुक्त(pctx, ctx->ipc_buf);
	ctx->ipc_buf = शून्य;

	वापस ret;
पूर्ण;

पूर्णांक delta_ipc_set_stream(व्योम *hdl, काष्ठा delta_ipc_param *param)
अणु
	काष्ठा delta_ipc_ctx *ctx = to_ctx(hdl);
	काष्ठा delta_ctx *pctx = to_pctx(ctx);
	काष्ठा delta_dev *delta = pctx->dev;
	काष्ठा rpmsg_device *rpmsg_device = delta->rpmsg_device;
	काष्ठा delta_ipc_set_stream_msg msg;
	पूर्णांक ret;

	अगर (!hdl) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to set stream, invalid ipc handle\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!rpmsg_device) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to set stream, rpmsg is not initialized\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!param || !param->data || !param->size) अणु
		dev_err(delta->dev,
			"%s  ipc: failed to set stream, empty parameter\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (param->size > ctx->ipc_buf->size) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to set stream, too large ipc parameter(%d bytes while max %d expected)\n",
			pctx->name,
			param->size, ctx->ipc_buf->size);
		वापस -EINVAL;
	पूर्ण

	अगर (!is_valid_data(ctx, param->data, param->size)) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to set stream, parameter is not in expected address range (size=%d, data=%p not in %p..%p)\n",
			pctx->name,
			param->size,
			param->data,
			ctx->ipc_buf->vaddr,
			ctx->ipc_buf->vaddr + ctx->ipc_buf->size - 1);
		वापस -EINVAL;
	पूर्ण

	/* build rpmsg message */
	build_msg_header(ctx, DELTA_IPC_SET_STREAM, &msg.header);

	msg.param_size = param->size;
	msg.param_paddr = to_paddr(ctx, param->data);

	/* send it */
	ret = rpmsg_send(rpmsg_device->ept, &msg, माप(msg));
	अगर (ret) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to set stream, rpmsg_send failed (%d) for DELTA_IPC_SET_STREAM (size=%d, data=%p)\n",
			pctx->name,
			ret, param->size, param->data);
		pctx->sys_errors++;
		वापस ret;
	पूर्ण

	/* रुको क्रम acknowledge */
	अगर (!रुको_क्रम_completion_समयout
	    (&ctx->करोne, msecs_to_jअगरfies(IPC_TIMEOUT))) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to set stream, timeout waiting for DELTA_IPC_SET_STREAM callback (size=%d, data=%p)\n",
			pctx->name,
			param->size, param->data);
		pctx->sys_errors++;
		वापस -ETIMEDOUT;
	पूर्ण

	/* command completed, check status */
	अगर (ctx->cb_err) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to set stream, DELTA_IPC_SET_STREAM completed but with error (%d) (size=%d, data=%p)\n",
			pctx->name,
			ctx->cb_err, param->size, param->data);
		pctx->sys_errors++;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक delta_ipc_decode(व्योम *hdl, काष्ठा delta_ipc_param *param,
		     काष्ठा delta_ipc_param *status)
अणु
	काष्ठा delta_ipc_ctx *ctx = to_ctx(hdl);
	काष्ठा delta_ctx *pctx = to_pctx(ctx);
	काष्ठा delta_dev *delta = pctx->dev;
	काष्ठा rpmsg_device *rpmsg_device = delta->rpmsg_device;
	काष्ठा delta_ipc_decode_msg msg;
	पूर्णांक ret;

	अगर (!hdl) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to decode, invalid ipc handle\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!rpmsg_device) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to decode, rpmsg is not initialized\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!param || !param->data || !param->size) अणु
		dev_err(delta->dev,
			"%s  ipc: failed to decode, empty parameter\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!status || !status->data || !status->size) अणु
		dev_err(delta->dev,
			"%s  ipc: failed to decode, empty status\n",
			pctx->name);
		वापस -EINVAL;
	पूर्ण

	अगर (param->size + status->size > ctx->ipc_buf->size) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to decode, too large ipc parameter (%d bytes (param) + %d bytes (status) while max %d expected)\n",
			pctx->name,
			param->size,
			status->size,
			ctx->ipc_buf->size);
		वापस -EINVAL;
	पूर्ण

	अगर (!is_valid_data(ctx, param->data, param->size)) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to decode, parameter is not in expected address range (size=%d, data=%p not in %p..%p)\n",
			pctx->name,
			param->size,
			param->data,
			ctx->ipc_buf->vaddr,
			ctx->ipc_buf->vaddr + ctx->ipc_buf->size - 1);
		वापस -EINVAL;
	पूर्ण

	अगर (!is_valid_data(ctx, status->data, status->size)) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to decode, status is not in expected address range (size=%d, data=%p not in %p..%p)\n",
			pctx->name,
			status->size,
			status->data,
			ctx->ipc_buf->vaddr,
			ctx->ipc_buf->vaddr + ctx->ipc_buf->size - 1);
		वापस -EINVAL;
	पूर्ण

	/* build rpmsg message */
	build_msg_header(ctx, DELTA_IPC_DECODE, &msg.header);

	msg.param_size = param->size;
	msg.param_paddr = to_paddr(ctx, param->data);

	msg.status_size = status->size;
	msg.status_paddr = to_paddr(ctx, status->data);

	/* send it */
	ret = rpmsg_send(rpmsg_device->ept, &msg, माप(msg));
	अगर (ret) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to decode, rpmsg_send failed (%d) for DELTA_IPC_DECODE (size=%d, data=%p)\n",
			pctx->name,
			ret, param->size, param->data);
		pctx->sys_errors++;
		वापस ret;
	पूर्ण

	/* रुको क्रम acknowledge */
	अगर (!रुको_क्रम_completion_समयout
	    (&ctx->करोne, msecs_to_jअगरfies(IPC_TIMEOUT))) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to decode, timeout waiting for DELTA_IPC_DECODE callback (size=%d, data=%p)\n",
			pctx->name,
			param->size, param->data);
		pctx->sys_errors++;
		वापस -ETIMEDOUT;
	पूर्ण

	/* command completed, check status */
	अगर (ctx->cb_err) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to decode, DELTA_IPC_DECODE completed but with error (%d) (size=%d, data=%p)\n",
			pctx->name,
			ctx->cb_err, param->size, param->data);
		pctx->sys_errors++;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण;

व्योम delta_ipc_बंद(व्योम *hdl)
अणु
	काष्ठा delta_ipc_ctx *ctx = to_ctx(hdl);
	काष्ठा delta_ctx *pctx = to_pctx(ctx);
	काष्ठा delta_dev *delta = pctx->dev;
	काष्ठा rpmsg_device *rpmsg_device = delta->rpmsg_device;
	काष्ठा delta_ipc_बंद_msg msg;
	पूर्णांक ret;

	अगर (!hdl) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to close, invalid ipc handle\n",
			pctx->name);
		वापस;
	पूर्ण

	अगर (ctx->ipc_buf) अणु
		hw_मुक्त(pctx, ctx->ipc_buf);
		ctx->ipc_buf = शून्य;
	पूर्ण

	अगर (!rpmsg_device) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to close, rpmsg is not initialized\n",
			pctx->name);
		वापस;
	पूर्ण

	/* build rpmsg message */
	build_msg_header(ctx, DELTA_IPC_CLOSE, &msg.header);

	/* send it */
	ret = rpmsg_send(rpmsg_device->ept, &msg, माप(msg));
	अगर (ret) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to close, rpmsg_send failed (%d) for DELTA_IPC_CLOSE\n",
			pctx->name, ret);
		pctx->sys_errors++;
		वापस;
	पूर्ण

	/* रुको क्रम acknowledge */
	अगर (!रुको_क्रम_completion_समयout
	    (&ctx->करोne, msecs_to_jअगरfies(IPC_TIMEOUT))) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to close, timeout waiting for DELTA_IPC_CLOSE callback\n",
			pctx->name);
		pctx->sys_errors++;
		वापस;
	पूर्ण

	/* command completed, check status */
	अगर (ctx->cb_err) अणु
		dev_err(delta->dev,
			"%s   ipc: failed to close, DELTA_IPC_CLOSE completed but with error (%d)\n",
			pctx->name, ctx->cb_err);
		pctx->sys_errors++;
	पूर्ण
पूर्ण;

अटल पूर्णांक delta_ipc_cb(काष्ठा rpmsg_device *rpdev, व्योम *data,
			पूर्णांक len, व्योम *priv, u32 src)
अणु
	काष्ठा delta_ipc_ctx *ctx;
	काष्ठा delta_ipc_cb_msg *msg;

	/* sanity check */
	अगर (!rpdev) अणु
		dev_err(शून्य, "rpdev is NULL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!data || !len) अणु
		dev_err(&rpdev->dev,
			"unexpected empty message received from src=%d\n", src);
		वापस -EINVAL;
	पूर्ण

	अगर (len != माप(*msg)) अणु
		dev_err(&rpdev->dev,
			"unexpected message length received from src=%d (received %d bytes while %zu bytes expected)\n",
			len, src, माप(*msg));
		वापस -EINVAL;
	पूर्ण

	msg = (काष्ठा delta_ipc_cb_msg *)data;
	अगर (msg->header.tag != IPC_SANITY_TAG) अणु
		dev_err(&rpdev->dev,
			"unexpected message tag received from src=%d (received %x tag while %x expected)\n",
			src, msg->header.tag, IPC_SANITY_TAG);
		वापस -EINVAL;
	पूर्ण

	ctx = msg_to_ctx(msg);
	अगर (!ctx) अणु
		dev_err(&rpdev->dev,
			"unexpected message with NULL host_hdl received from src=%d\n",
			src);
		वापस -EINVAL;
	पूर्ण

	/*
	 * अगर not alपढ़ोy known, save copro instance context
	 * to ensure re-entrance on copro side
	 */
	अगर (!ctx->copro_hdl)
		ctx->copro_hdl = msg_to_copro_hdl(msg);

	/*
	 * all is fine,
	 * update status & complete command
	 */
	ctx->cb_err = msg->err;
	complete(&ctx->करोne);

	वापस 0;
पूर्ण

अटल पूर्णांक delta_ipc_probe(काष्ठा rpmsg_device *rpmsg_device)
अणु
	काष्ठा rpmsg_driver *rpdrv = to_rpmsg_driver(rpmsg_device->dev.driver);
	काष्ठा delta_dev *delta = to_delta(rpdrv);

	delta->rpmsg_device = rpmsg_device;

	वापस 0;
पूर्ण

अटल व्योम delta_ipc_हटाओ(काष्ठा rpmsg_device *rpmsg_device)
अणु
	काष्ठा rpmsg_driver *rpdrv = to_rpmsg_driver(rpmsg_device->dev.driver);
	काष्ठा delta_dev *delta = to_delta(rpdrv);

	delta->rpmsg_device = शून्य;
पूर्ण

अटल काष्ठा rpmsg_device_id delta_ipc_device_id_table[] = अणु
	अणु.name = "rpmsg-delta"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा rpmsg_driver delta_rpmsg_driver = अणु
	.drv = अणु.name = KBUILD_MODNAMEपूर्ण,
	.id_table = delta_ipc_device_id_table,
	.probe = delta_ipc_probe,
	.callback = delta_ipc_cb,
	.हटाओ = delta_ipc_हटाओ,
पूर्ण;

पूर्णांक delta_ipc_init(काष्ठा delta_dev *delta)
अणु
	delta->rpmsg_driver = delta_rpmsg_driver;

	वापस रेजिस्टर_rpmsg_driver(&delta->rpmsg_driver);
पूर्ण

व्योम delta_ipc_निकास(काष्ठा delta_dev *delta)
अणु
	unरेजिस्टर_rpmsg_driver(&delta->rpmsg_driver);
पूर्ण
