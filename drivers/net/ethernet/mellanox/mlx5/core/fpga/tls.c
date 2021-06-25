<शैली गुरु>
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/mlx5/device.h>
#समावेश "fpga/tls.h"
#समावेश "fpga/cmd.h"
#समावेश "fpga/sdk.h"
#समावेश "fpga/core.h"
#समावेश "accel/tls.h"

काष्ठा mlx5_fpga_tls_command_context;

प्रकार व्योम (*mlx5_fpga_tls_command_complete)
	(काष्ठा mlx5_fpga_conn *conn, काष्ठा mlx5_fpga_device *fdev,
	 काष्ठा mlx5_fpga_tls_command_context *ctx,
	 काष्ठा mlx5_fpga_dma_buf *resp);

काष्ठा mlx5_fpga_tls_command_context अणु
	काष्ठा list_head list;
	/* There is no guarantee on the order between the TX completion
	 * and the command response.
	 * The TX completion is going to touch cmd->buf even in
	 * the हाल of successful transmission.
	 * So instead of requiring separate allocations क्रम cmd
	 * and cmd->buf we've decided to use a reference counter
	 */
	refcount_t ref;
	काष्ठा mlx5_fpga_dma_buf buf;
	mlx5_fpga_tls_command_complete complete;
पूर्ण;

अटल व्योम
mlx5_fpga_tls_put_command_ctx(काष्ठा mlx5_fpga_tls_command_context *ctx)
अणु
	अगर (refcount_dec_and_test(&ctx->ref))
		kमुक्त(ctx);
पूर्ण

अटल व्योम mlx5_fpga_tls_cmd_complete(काष्ठा mlx5_fpga_device *fdev,
				       काष्ठा mlx5_fpga_dma_buf *resp)
अणु
	काष्ठा mlx5_fpga_conn *conn = fdev->tls->conn;
	काष्ठा mlx5_fpga_tls_command_context *ctx;
	काष्ठा mlx5_fpga_tls *tls = fdev->tls;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tls->pending_cmds_lock, flags);
	ctx = list_first_entry(&tls->pending_cmds,
			       काष्ठा mlx5_fpga_tls_command_context, list);
	list_del(&ctx->list);
	spin_unlock_irqrestore(&tls->pending_cmds_lock, flags);
	ctx->complete(conn, fdev, ctx, resp);
पूर्ण

अटल व्योम mlx5_fpga_cmd_send_complete(काष्ठा mlx5_fpga_conn *conn,
					काष्ठा mlx5_fpga_device *fdev,
					काष्ठा mlx5_fpga_dma_buf *buf,
					u8 status)
अणु
	काष्ठा mlx5_fpga_tls_command_context *ctx =
	    container_of(buf, काष्ठा mlx5_fpga_tls_command_context, buf);

	mlx5_fpga_tls_put_command_ctx(ctx);

	अगर (unlikely(status))
		mlx5_fpga_tls_cmd_complete(fdev, शून्य);
पूर्ण

अटल व्योम mlx5_fpga_tls_cmd_send(काष्ठा mlx5_fpga_device *fdev,
				   काष्ठा mlx5_fpga_tls_command_context *cmd,
				   mlx5_fpga_tls_command_complete complete)
अणु
	काष्ठा mlx5_fpga_tls *tls = fdev->tls;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	refcount_set(&cmd->ref, 2);
	cmd->complete = complete;
	cmd->buf.complete = mlx5_fpga_cmd_send_complete;

	spin_lock_irqsave(&tls->pending_cmds_lock, flags);
	/* mlx5_fpga_sbu_conn_sendmsg is called under pending_cmds_lock
	 * to make sure commands are inserted to the tls->pending_cmds list
	 * and the command QP in the same order.
	 */
	ret = mlx5_fpga_sbu_conn_sendmsg(tls->conn, &cmd->buf);
	अगर (likely(!ret))
		list_add_tail(&cmd->list, &tls->pending_cmds);
	अन्यथा
		complete(tls->conn, fdev, cmd, शून्य);
	spin_unlock_irqrestore(&tls->pending_cmds_lock, flags);
पूर्ण

/* Start of context identअगरiers range (inclusive) */
#घोषणा SWID_START	0
/* End of context identअगरiers range (exclusive) */
#घोषणा SWID_END	BIT(24)

अटल पूर्णांक mlx5_fpga_tls_alloc_swid(काष्ठा idr *idr, spinlock_t *idr_spinlock,
				    व्योम *ptr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* TLS metadata क्रमmat is 1 byte क्रम syndrome followed
	 * by 3 bytes of swid (software ID)
	 * swid must not exceed 3 bytes.
	 * See tls_rxtx.c:insert_pet() क्रम details
	 */
	BUILD_BUG_ON((SWID_END - 1) & 0xFF000000);

	idr_preload(GFP_KERNEL);
	spin_lock_irqsave(idr_spinlock, flags);
	ret = idr_alloc(idr, ptr, SWID_START, SWID_END, GFP_ATOMIC);
	spin_unlock_irqrestore(idr_spinlock, flags);
	idr_preload_end();

	वापस ret;
पूर्ण

अटल व्योम *mlx5_fpga_tls_release_swid(काष्ठा idr *idr,
					spinlock_t *idr_spinlock, u32 swid)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *ptr;

	spin_lock_irqsave(idr_spinlock, flags);
	ptr = idr_हटाओ(idr, swid);
	spin_unlock_irqrestore(idr_spinlock, flags);
	वापस ptr;
पूर्ण

अटल व्योम mlx_tls_kमुक्त_complete(काष्ठा mlx5_fpga_conn *conn,
				   काष्ठा mlx5_fpga_device *fdev,
				   काष्ठा mlx5_fpga_dma_buf *buf, u8 status)
अणु
	kमुक्त(buf);
पूर्ण

अटल व्योम
mlx5_fpga_tls_tearकरोwn_completion(काष्ठा mlx5_fpga_conn *conn,
				  काष्ठा mlx5_fpga_device *fdev,
				  काष्ठा mlx5_fpga_tls_command_context *cmd,
				  काष्ठा mlx5_fpga_dma_buf *resp)
अणु
	अगर (resp) अणु
		u32 syndrome = MLX5_GET(tls_resp, resp->sg[0].data, syndrome);

		अगर (syndrome)
			mlx5_fpga_err(fdev,
				      "Teardown stream failed with syndrome = %d",
				      syndrome);
	पूर्ण
	mlx5_fpga_tls_put_command_ctx(cmd);
पूर्ण

अटल व्योम mlx5_fpga_tls_flow_to_cmd(व्योम *flow, व्योम *cmd)
अणु
	स_नकल(MLX5_ADDR_OF(tls_cmd, cmd, src_port), flow,
	       MLX5_BYTE_OFF(tls_flow, ipv6));

	MLX5_SET(tls_cmd, cmd, ipv6, MLX5_GET(tls_flow, flow, ipv6));
	MLX5_SET(tls_cmd, cmd, direction_sx,
		 MLX5_GET(tls_flow, flow, direction_sx));
पूर्ण

पूर्णांक mlx5_fpga_tls_resync_rx(काष्ठा mlx5_core_dev *mdev, __be32 handle,
			    u32 seq, __be64 rcd_sn)
अणु
	काष्ठा mlx5_fpga_dma_buf *buf;
	पूर्णांक size = माप(*buf) + MLX5_TLS_COMMAND_SIZE;
	व्योम *flow;
	व्योम *cmd;
	पूर्णांक ret;

	buf = kzalloc(size, GFP_ATOMIC);
	अगर (!buf)
		वापस -ENOMEM;

	cmd = (buf + 1);

	rcu_पढ़ो_lock();
	flow = idr_find(&mdev->fpga->tls->rx_idr, ntohl(handle));
	अगर (unlikely(!flow)) अणु
		rcu_पढ़ो_unlock();
		WARN_ONCE(1, "Received NULL pointer for handle\n");
		kमुक्त(buf);
		वापस -EINVAL;
	पूर्ण
	mlx5_fpga_tls_flow_to_cmd(flow, cmd);
	rcu_पढ़ो_unlock();

	MLX5_SET(tls_cmd, cmd, swid, ntohl(handle));
	MLX5_SET64(tls_cmd, cmd, tls_rcd_sn, be64_to_cpu(rcd_sn));
	MLX5_SET(tls_cmd, cmd, tcp_sn, seq);
	MLX5_SET(tls_cmd, cmd, command_type, CMD_RESYNC_RX);

	buf->sg[0].data = cmd;
	buf->sg[0].size = MLX5_TLS_COMMAND_SIZE;
	buf->complete = mlx_tls_kमुक्त_complete;

	ret = mlx5_fpga_sbu_conn_sendmsg(mdev->fpga->tls->conn, buf);
	अगर (ret < 0)
		kमुक्त(buf);

	वापस ret;
पूर्ण

अटल व्योम mlx5_fpga_tls_send_tearकरोwn_cmd(काष्ठा mlx5_core_dev *mdev,
					    व्योम *flow, u32 swid, gfp_t flags)
अणु
	काष्ठा mlx5_fpga_tls_command_context *ctx;
	काष्ठा mlx5_fpga_dma_buf *buf;
	व्योम *cmd;

	ctx = kzalloc(माप(*ctx) + MLX5_TLS_COMMAND_SIZE, flags);
	अगर (!ctx)
		वापस;

	buf = &ctx->buf;
	cmd = (ctx + 1);
	MLX5_SET(tls_cmd, cmd, command_type, CMD_TEARDOWN_STREAM);
	MLX5_SET(tls_cmd, cmd, swid, swid);

	mlx5_fpga_tls_flow_to_cmd(flow, cmd);
	kमुक्त(flow);

	buf->sg[0].data = cmd;
	buf->sg[0].size = MLX5_TLS_COMMAND_SIZE;

	mlx5_fpga_tls_cmd_send(mdev->fpga, ctx,
			       mlx5_fpga_tls_tearकरोwn_completion);
पूर्ण

व्योम mlx5_fpga_tls_del_flow(काष्ठा mlx5_core_dev *mdev, u32 swid,
			    gfp_t flags, bool direction_sx)
अणु
	काष्ठा mlx5_fpga_tls *tls = mdev->fpga->tls;
	व्योम *flow;

	अगर (direction_sx)
		flow = mlx5_fpga_tls_release_swid(&tls->tx_idr,
						  &tls->tx_idr_spinlock,
						  swid);
	अन्यथा
		flow = mlx5_fpga_tls_release_swid(&tls->rx_idr,
						  &tls->rx_idr_spinlock,
						  swid);

	अगर (!flow) अणु
		mlx5_fpga_err(mdev->fpga, "No flow information for swid %u\n",
			      swid);
		वापस;
	पूर्ण

	synchronize_rcu(); /* beक्रमe kमुक्त(flow) */
	mlx5_fpga_tls_send_tearकरोwn_cmd(mdev, flow, swid, flags);
पूर्ण

क्रमागत mlx5_fpga_setup_stream_status अणु
	MLX5_FPGA_CMD_PENDING,
	MLX5_FPGA_CMD_SEND_FAILED,
	MLX5_FPGA_CMD_RESPONSE_RECEIVED,
	MLX5_FPGA_CMD_ABANDONED,
पूर्ण;

काष्ठा mlx5_setup_stream_context अणु
	काष्ठा mlx5_fpga_tls_command_context cmd;
	atomic_t status;
	u32 syndrome;
	काष्ठा completion comp;
पूर्ण;

अटल व्योम
mlx5_fpga_tls_setup_completion(काष्ठा mlx5_fpga_conn *conn,
			       काष्ठा mlx5_fpga_device *fdev,
			       काष्ठा mlx5_fpga_tls_command_context *cmd,
			       काष्ठा mlx5_fpga_dma_buf *resp)
अणु
	काष्ठा mlx5_setup_stream_context *ctx =
	    container_of(cmd, काष्ठा mlx5_setup_stream_context, cmd);
	पूर्णांक status = MLX5_FPGA_CMD_SEND_FAILED;
	व्योम *tls_cmd = ctx + 1;

	/* If we failed to send to command resp == शून्य */
	अगर (resp) अणु
		ctx->syndrome = MLX5_GET(tls_resp, resp->sg[0].data, syndrome);
		status = MLX5_FPGA_CMD_RESPONSE_RECEIVED;
	पूर्ण

	status = atomic_xchg_release(&ctx->status, status);
	अगर (likely(status != MLX5_FPGA_CMD_ABANDONED)) अणु
		complete(&ctx->comp);
		वापस;
	पूर्ण

	mlx5_fpga_err(fdev, "Command was abandoned, syndrome = %u\n",
		      ctx->syndrome);

	अगर (!ctx->syndrome) अणु
		/* The process was समाप्तed जबतक रुकोing क्रम the context to be
		 * added, and the add completed successfully.
		 * We need to destroy the HW context, and we can't can't reuse
		 * the command context because we might not have received
		 * the tx completion yet.
		 */
		mlx5_fpga_tls_del_flow(fdev->mdev,
				       MLX5_GET(tls_cmd, tls_cmd, swid),
				       GFP_ATOMIC,
				       MLX5_GET(tls_cmd, tls_cmd,
						direction_sx));
	पूर्ण

	mlx5_fpga_tls_put_command_ctx(cmd);
पूर्ण

अटल पूर्णांक mlx5_fpga_tls_setup_stream_cmd(काष्ठा mlx5_core_dev *mdev,
					  काष्ठा mlx5_setup_stream_context *ctx)
अणु
	काष्ठा mlx5_fpga_dma_buf *buf;
	व्योम *cmd = ctx + 1;
	पूर्णांक status, ret = 0;

	buf = &ctx->cmd.buf;
	buf->sg[0].data = cmd;
	buf->sg[0].size = MLX5_TLS_COMMAND_SIZE;
	MLX5_SET(tls_cmd, cmd, command_type, CMD_SETUP_STREAM);

	init_completion(&ctx->comp);
	atomic_set(&ctx->status, MLX5_FPGA_CMD_PENDING);
	ctx->syndrome = -1;

	mlx5_fpga_tls_cmd_send(mdev->fpga, &ctx->cmd,
			       mlx5_fpga_tls_setup_completion);
	रुको_क्रम_completion_समाप्तable(&ctx->comp);

	status = atomic_xchg_acquire(&ctx->status, MLX5_FPGA_CMD_ABANDONED);
	अगर (unlikely(status == MLX5_FPGA_CMD_PENDING))
	/* ctx is going to be released in mlx5_fpga_tls_setup_completion */
		वापस -EINTR;

	अगर (unlikely(ctx->syndrome))
		ret = -ENOMEM;

	mlx5_fpga_tls_put_command_ctx(&ctx->cmd);
	वापस ret;
पूर्ण

अटल व्योम mlx5_fpga_tls_hw_qp_recv_cb(व्योम *cb_arg,
					काष्ठा mlx5_fpga_dma_buf *buf)
अणु
	काष्ठा mlx5_fpga_device *fdev = (काष्ठा mlx5_fpga_device *)cb_arg;

	mlx5_fpga_tls_cmd_complete(fdev, buf);
पूर्ण

bool mlx5_fpga_is_tls_device(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (!mdev->fpga || !MLX5_CAP_GEN(mdev, fpga))
		वापस false;

	अगर (MLX5_CAP_FPGA(mdev, ieee_venकरोr_id) !=
	    MLX5_FPGA_CAP_SANDBOX_VENDOR_ID_MLNX)
		वापस false;

	अगर (MLX5_CAP_FPGA(mdev, sandbox_product_id) !=
	    MLX5_FPGA_CAP_SANDBOX_PRODUCT_ID_TLS)
		वापस false;

	अगर (MLX5_CAP_FPGA(mdev, sandbox_product_version) != 0)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक mlx5_fpga_tls_get_caps(काष्ठा mlx5_fpga_device *fdev,
				  u32 *p_caps)
अणु
	पूर्णांक err, cap_size = MLX5_ST_SZ_BYTES(tls_extended_cap);
	u32 caps = 0;
	व्योम *buf;

	buf = kzalloc(cap_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	err = mlx5_fpga_get_sbu_caps(fdev, cap_size, buf);
	अगर (err)
		जाओ out;

	अगर (MLX5_GET(tls_extended_cap, buf, tx))
		caps |= MLX5_ACCEL_TLS_TX;
	अगर (MLX5_GET(tls_extended_cap, buf, rx))
		caps |= MLX5_ACCEL_TLS_RX;
	अगर (MLX5_GET(tls_extended_cap, buf, tls_v12))
		caps |= MLX5_ACCEL_TLS_V12;
	अगर (MLX5_GET(tls_extended_cap, buf, tls_v13))
		caps |= MLX5_ACCEL_TLS_V13;
	अगर (MLX5_GET(tls_extended_cap, buf, lro))
		caps |= MLX5_ACCEL_TLS_LRO;
	अगर (MLX5_GET(tls_extended_cap, buf, ipv6))
		caps |= MLX5_ACCEL_TLS_IPV6;

	अगर (MLX5_GET(tls_extended_cap, buf, aes_gcm_128))
		caps |= MLX5_ACCEL_TLS_AES_GCM128;
	अगर (MLX5_GET(tls_extended_cap, buf, aes_gcm_256))
		caps |= MLX5_ACCEL_TLS_AES_GCM256;

	*p_caps = caps;
	err = 0;
out:
	kमुक्त(buf);
	वापस err;
पूर्ण

पूर्णांक mlx5_fpga_tls_init(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;
	काष्ठा mlx5_fpga_conn_attr init_attr = अणु0पूर्ण;
	काष्ठा mlx5_fpga_conn *conn;
	काष्ठा mlx5_fpga_tls *tls;
	पूर्णांक err = 0;

	अगर (!mlx5_fpga_is_tls_device(mdev) || !fdev)
		वापस 0;

	tls = kzalloc(माप(*tls), GFP_KERNEL);
	अगर (!tls)
		वापस -ENOMEM;

	err = mlx5_fpga_tls_get_caps(fdev, &tls->caps);
	अगर (err)
		जाओ error;

	अगर (!(tls->caps & (MLX5_ACCEL_TLS_V12 | MLX5_ACCEL_TLS_AES_GCM128))) अणु
		err = -ENOTSUPP;
		जाओ error;
	पूर्ण

	init_attr.rx_size = SBU_QP_QUEUE_SIZE;
	init_attr.tx_size = SBU_QP_QUEUE_SIZE;
	init_attr.recv_cb = mlx5_fpga_tls_hw_qp_recv_cb;
	init_attr.cb_arg = fdev;
	conn = mlx5_fpga_sbu_conn_create(fdev, &init_attr);
	अगर (IS_ERR(conn)) अणु
		err = PTR_ERR(conn);
		mlx5_fpga_err(fdev, "Error creating TLS command connection %d\n",
			      err);
		जाओ error;
	पूर्ण

	tls->conn = conn;
	spin_lock_init(&tls->pending_cmds_lock);
	INIT_LIST_HEAD(&tls->pending_cmds);

	idr_init(&tls->tx_idr);
	idr_init(&tls->rx_idr);
	spin_lock_init(&tls->tx_idr_spinlock);
	spin_lock_init(&tls->rx_idr_spinlock);
	fdev->tls = tls;
	वापस 0;

error:
	kमुक्त(tls);
	वापस err;
पूर्ण

व्योम mlx5_fpga_tls_cleanup(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;

	अगर (!fdev || !fdev->tls)
		वापस;

	mlx5_fpga_sbu_conn_destroy(fdev->tls->conn);
	kमुक्त(fdev->tls);
	fdev->tls = शून्य;
पूर्ण

अटल व्योम mlx5_fpga_tls_set_aes_gcm128_ctx(व्योम *cmd,
					     काष्ठा tls_crypto_info *info,
					     __be64 *rcd_sn)
अणु
	काष्ठा tls12_crypto_info_aes_gcm_128 *crypto_info =
	    (काष्ठा tls12_crypto_info_aes_gcm_128 *)info;

	स_नकल(MLX5_ADDR_OF(tls_cmd, cmd, tls_rcd_sn), crypto_info->rec_seq,
	       TLS_CIPHER_AES_GCM_128_REC_SEQ_SIZE);

	स_नकल(MLX5_ADDR_OF(tls_cmd, cmd, tls_implicit_iv),
	       crypto_info->salt, TLS_CIPHER_AES_GCM_128_SALT_SIZE);
	स_नकल(MLX5_ADDR_OF(tls_cmd, cmd, encryption_key),
	       crypto_info->key, TLS_CIPHER_AES_GCM_128_KEY_SIZE);

	/* in AES-GCM 128 we need to ग_लिखो the key twice */
	स_नकल(MLX5_ADDR_OF(tls_cmd, cmd, encryption_key) +
		   TLS_CIPHER_AES_GCM_128_KEY_SIZE,
	       crypto_info->key, TLS_CIPHER_AES_GCM_128_KEY_SIZE);

	MLX5_SET(tls_cmd, cmd, alg, MLX5_TLS_ALG_AES_GCM_128);
पूर्ण

अटल पूर्णांक mlx5_fpga_tls_set_key_material(व्योम *cmd, u32 caps,
					  काष्ठा tls_crypto_info *crypto_info)
अणु
	__be64 rcd_sn;

	चयन (crypto_info->cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128:
		अगर (!(caps & MLX5_ACCEL_TLS_AES_GCM128))
			वापस -EINVAL;
		mlx5_fpga_tls_set_aes_gcm128_ctx(cmd, crypto_info, &rcd_sn);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _mlx5_fpga_tls_add_flow(काष्ठा mlx5_core_dev *mdev, व्योम *flow,
				   काष्ठा tls_crypto_info *crypto_info,
				   u32 swid, u32 tcp_sn)
अणु
	u32 caps = mlx5_fpga_tls_device_caps(mdev);
	काष्ठा mlx5_setup_stream_context *ctx;
	पूर्णांक ret = -ENOMEM;
	माप_प्रकार cmd_size;
	व्योम *cmd;

	cmd_size = MLX5_TLS_COMMAND_SIZE + माप(*ctx);
	ctx = kzalloc(cmd_size, GFP_KERNEL);
	अगर (!ctx)
		जाओ out;

	cmd = ctx + 1;
	ret = mlx5_fpga_tls_set_key_material(cmd, caps, crypto_info);
	अगर (ret)
		जाओ मुक्त_ctx;

	mlx5_fpga_tls_flow_to_cmd(flow, cmd);

	MLX5_SET(tls_cmd, cmd, swid, swid);
	MLX5_SET(tls_cmd, cmd, tcp_sn, tcp_sn);

	वापस mlx5_fpga_tls_setup_stream_cmd(mdev, ctx);

मुक्त_ctx:
	kमुक्त(ctx);
out:
	वापस ret;
पूर्ण

पूर्णांक mlx5_fpga_tls_add_flow(काष्ठा mlx5_core_dev *mdev, व्योम *flow,
			   काष्ठा tls_crypto_info *crypto_info,
			   u32 start_offload_tcp_sn, u32 *p_swid,
			   bool direction_sx)
अणु
	काष्ठा mlx5_fpga_tls *tls = mdev->fpga->tls;
	पूर्णांक ret = -ENOMEM;
	u32 swid;

	अगर (direction_sx)
		ret = mlx5_fpga_tls_alloc_swid(&tls->tx_idr,
					       &tls->tx_idr_spinlock, flow);
	अन्यथा
		ret = mlx5_fpga_tls_alloc_swid(&tls->rx_idr,
					       &tls->rx_idr_spinlock, flow);

	अगर (ret < 0)
		वापस ret;

	swid = ret;
	MLX5_SET(tls_flow, flow, direction_sx, direction_sx ? 1 : 0);

	ret = _mlx5_fpga_tls_add_flow(mdev, flow, crypto_info, swid,
				      start_offload_tcp_sn);
	अगर (ret && ret != -EINTR)
		जाओ मुक्त_swid;

	*p_swid = swid;
	वापस 0;
मुक्त_swid:
	अगर (direction_sx)
		mlx5_fpga_tls_release_swid(&tls->tx_idr,
					   &tls->tx_idr_spinlock, swid);
	अन्यथा
		mlx5_fpga_tls_release_swid(&tls->rx_idr,
					   &tls->rx_idr_spinlock, swid);

	वापस ret;
पूर्ण
