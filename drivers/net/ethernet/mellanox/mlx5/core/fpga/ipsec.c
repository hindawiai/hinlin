<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/rhashtable.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/fs_helpers.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/rbtree.h>

#समावेश "mlx5_core.h"
#समावेश "fs_cmd.h"
#समावेश "fpga/ipsec.h"
#समावेश "fpga/sdk.h"
#समावेश "fpga/core.h"

क्रमागत mlx5_fpga_ipsec_cmd_status अणु
	MLX5_FPGA_IPSEC_CMD_PENDING,
	MLX5_FPGA_IPSEC_CMD_SEND_FAIL,
	MLX5_FPGA_IPSEC_CMD_COMPLETE,
पूर्ण;

काष्ठा mlx5_fpga_ipsec_cmd_context अणु
	काष्ठा mlx5_fpga_dma_buf buf;
	क्रमागत mlx5_fpga_ipsec_cmd_status status;
	काष्ठा mlx5_अगरc_fpga_ipsec_cmd_resp resp;
	पूर्णांक status_code;
	काष्ठा completion complete;
	काष्ठा mlx5_fpga_device *dev;
	काष्ठा list_head list; /* Item in pending_cmds */
	u8 command[];
पूर्ण;

काष्ठा mlx5_fpga_esp_xfrm;

काष्ठा mlx5_fpga_ipsec_sa_ctx अणु
	काष्ठा rhash_head		hash;
	काष्ठा mlx5_अगरc_fpga_ipsec_sa	hw_sa;
	u32				sa_handle;
	काष्ठा mlx5_core_dev		*dev;
	काष्ठा mlx5_fpga_esp_xfrm	*fpga_xfrm;
पूर्ण;

काष्ठा mlx5_fpga_esp_xfrm अणु
	अचिन्हित पूर्णांक			num_rules;
	काष्ठा mlx5_fpga_ipsec_sa_ctx	*sa_ctx;
	काष्ठा mutex			lock; /* xfrm lock */
	काष्ठा mlx5_accel_esp_xfrm	accel_xfrm;
पूर्ण;

काष्ठा mlx5_fpga_ipsec_rule अणु
	काष्ठा rb_node			node;
	काष्ठा fs_fte			*fte;
	काष्ठा mlx5_fpga_ipsec_sa_ctx	*ctx;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params rhash_sa = अणु
	/* Keep out "cmd" field from the key as it's
	 * value is not स्थिरant during the lअगरeसमय
	 * of the key object.
	 */
	.key_len = माप_field(काष्ठा mlx5_fpga_ipsec_sa_ctx, hw_sa) -
		   माप_field(काष्ठा mlx5_अगरc_fpga_ipsec_sa_v1, cmd),
	.key_offset = दुरत्व(काष्ठा mlx5_fpga_ipsec_sa_ctx, hw_sa) +
		      माप_field(काष्ठा mlx5_अगरc_fpga_ipsec_sa_v1, cmd),
	.head_offset = दुरत्व(काष्ठा mlx5_fpga_ipsec_sa_ctx, hash),
	.स्वतःmatic_shrinking = true,
	.min_size = 1,
पूर्ण;

काष्ठा mlx5_fpga_ipsec अणु
	काष्ठा mlx5_fpga_device *fdev;
	काष्ठा list_head pending_cmds;
	spinlock_t pending_cmds_lock; /* Protects pending_cmds */
	u32 caps[MLX5_ST_SZ_DW(ipsec_extended_cap)];
	काष्ठा mlx5_fpga_conn *conn;

	काष्ठा notअगरier_block	fs_notअगरier_ingress_bypass;
	काष्ठा notअगरier_block	fs_notअगरier_egress;

	/* Map hardware SA           -->  SA context
	 *     (mlx5_fpga_ipsec_sa)       (mlx5_fpga_ipsec_sa_ctx)
	 * We will use this hash to aव्योम SAs duplication in fpga which
	 * aren't allowed
	 */
	काष्ठा rhashtable sa_hash;	/* hw_sa -> mlx5_fpga_ipsec_sa_ctx */
	काष्ठा mutex sa_hash_lock;

	/* Tree holding all rules क्रम this fpga device
	 * Key क्रम searching a rule (mlx5_fpga_ipsec_rule) is (ft, id)
	 */
	काष्ठा rb_root rules_rb;
	काष्ठा mutex rules_rb_lock; /* rules lock */

	काष्ठा ida halloc;
पूर्ण;

bool mlx5_fpga_is_ipsec_device(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (!mdev->fpga || !MLX5_CAP_GEN(mdev, fpga))
		वापस false;

	अगर (MLX5_CAP_FPGA(mdev, ieee_venकरोr_id) !=
	    MLX5_FPGA_CAP_SANDBOX_VENDOR_ID_MLNX)
		वापस false;

	अगर (MLX5_CAP_FPGA(mdev, sandbox_product_id) !=
	    MLX5_FPGA_CAP_SANDBOX_PRODUCT_ID_IPSEC)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम mlx5_fpga_ipsec_send_complete(काष्ठा mlx5_fpga_conn *conn,
					  काष्ठा mlx5_fpga_device *fdev,
					  काष्ठा mlx5_fpga_dma_buf *buf,
					  u8 status)
अणु
	काष्ठा mlx5_fpga_ipsec_cmd_context *context;

	अगर (status) अणु
		context = container_of(buf, काष्ठा mlx5_fpga_ipsec_cmd_context,
				       buf);
		mlx5_fpga_warn(fdev, "IPSec command send failed with status %u\n",
			       status);
		context->status = MLX5_FPGA_IPSEC_CMD_SEND_FAIL;
		complete(&context->complete);
	पूर्ण
पूर्ण

अटल अंतरभूत
पूर्णांक syndrome_to_त्रुटि_सं(क्रमागत mlx5_अगरc_fpga_ipsec_response_syndrome syndrome)
अणु
	चयन (syndrome) अणु
	हाल MLX5_FPGA_IPSEC_RESPONSE_SUCCESS:
		वापस 0;
	हाल MLX5_FPGA_IPSEC_RESPONSE_SADB_ISSUE:
		वापस -EEXIST;
	हाल MLX5_FPGA_IPSEC_RESPONSE_ILLEGAL_REQUEST:
		वापस -EINVAL;
	हाल MLX5_FPGA_IPSEC_RESPONSE_WRITE_RESPONSE_ISSUE:
		वापस -EIO;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल व्योम mlx5_fpga_ipsec_recv(व्योम *cb_arg, काष्ठा mlx5_fpga_dma_buf *buf)
अणु
	काष्ठा mlx5_अगरc_fpga_ipsec_cmd_resp *resp = buf->sg[0].data;
	काष्ठा mlx5_fpga_ipsec_cmd_context *context;
	क्रमागत mlx5_अगरc_fpga_ipsec_response_syndrome syndrome;
	काष्ठा mlx5_fpga_device *fdev = cb_arg;
	अचिन्हित दीर्घ flags;

	अगर (buf->sg[0].size < माप(*resp)) अणु
		mlx5_fpga_warn(fdev, "Short receive from FPGA IPSec: %u < %zu bytes\n",
			       buf->sg[0].size, माप(*resp));
		वापस;
	पूर्ण

	mlx5_fpga_dbg(fdev, "mlx5_ipsec recv_cb syndrome %08x\n",
		      ntohl(resp->syndrome));

	spin_lock_irqsave(&fdev->ipsec->pending_cmds_lock, flags);
	context = list_first_entry_or_null(&fdev->ipsec->pending_cmds,
					   काष्ठा mlx5_fpga_ipsec_cmd_context,
					   list);
	अगर (context)
		list_del(&context->list);
	spin_unlock_irqrestore(&fdev->ipsec->pending_cmds_lock, flags);

	अगर (!context) अणु
		mlx5_fpga_warn(fdev, "Received IPSec offload response without pending command request\n");
		वापस;
	पूर्ण
	mlx5_fpga_dbg(fdev, "Handling response for %p\n", context);

	syndrome = ntohl(resp->syndrome);
	context->status_code = syndrome_to_त्रुटि_सं(syndrome);
	context->status = MLX5_FPGA_IPSEC_CMD_COMPLETE;
	स_नकल(&context->resp, resp, माप(*resp));

	अगर (context->status_code)
		mlx5_fpga_warn(fdev, "IPSec command failed with syndrome %08x\n",
			       syndrome);

	complete(&context->complete);
पूर्ण

अटल व्योम *mlx5_fpga_ipsec_cmd_exec(काष्ठा mlx5_core_dev *mdev,
				      स्थिर व्योम *cmd, पूर्णांक cmd_size)
अणु
	काष्ठा mlx5_fpga_ipsec_cmd_context *context;
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	अगर (!fdev || !fdev->ipsec)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (cmd_size & 3)
		वापस ERR_PTR(-EINVAL);

	context = kzalloc(माप(*context) + cmd_size, GFP_ATOMIC);
	अगर (!context)
		वापस ERR_PTR(-ENOMEM);

	context->status = MLX5_FPGA_IPSEC_CMD_PENDING;
	context->dev = fdev;
	context->buf.complete = mlx5_fpga_ipsec_send_complete;
	init_completion(&context->complete);
	स_नकल(&context->command, cmd, cmd_size);
	context->buf.sg[0].size = cmd_size;
	context->buf.sg[0].data = &context->command;

	spin_lock_irqsave(&fdev->ipsec->pending_cmds_lock, flags);
	res = mlx5_fpga_sbu_conn_sendmsg(fdev->ipsec->conn, &context->buf);
	अगर (!res)
		list_add_tail(&context->list, &fdev->ipsec->pending_cmds);
	spin_unlock_irqrestore(&fdev->ipsec->pending_cmds_lock, flags);

	अगर (res) अणु
		mlx5_fpga_warn(fdev, "Failed to send IPSec command: %d\n", res);
		kमुक्त(context);
		वापस ERR_PTR(res);
	पूर्ण

	/* Context should be मुक्तd by the caller after completion. */
	वापस context;
पूर्ण

अटल पूर्णांक mlx5_fpga_ipsec_cmd_रुको(व्योम *ctx)
अणु
	काष्ठा mlx5_fpga_ipsec_cmd_context *context = ctx;
	अचिन्हित दीर्घ समयout =
		msecs_to_jअगरfies(MLX5_FPGA_CMD_TIMEOUT_MSEC);
	पूर्णांक res;

	res = रुको_क्रम_completion_समयout(&context->complete, समयout);
	अगर (!res) अणु
		mlx5_fpga_warn(context->dev, "Failure waiting for IPSec command response\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (context->status == MLX5_FPGA_IPSEC_CMD_COMPLETE)
		res = context->status_code;
	अन्यथा
		res = -EIO;

	वापस res;
पूर्ण

अटल अंतरभूत bool is_v2_sadb_supported(काष्ठा mlx5_fpga_ipsec *fipsec)
अणु
	अगर (MLX5_GET(ipsec_extended_cap, fipsec->caps, v2_command))
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक mlx5_fpga_ipsec_update_hw_sa(काष्ठा mlx5_fpga_device *fdev,
					काष्ठा mlx5_अगरc_fpga_ipsec_sa *hw_sa,
					पूर्णांक opcode)
अणु
	काष्ठा mlx5_core_dev *dev = fdev->mdev;
	काष्ठा mlx5_अगरc_fpga_ipsec_sa *sa;
	काष्ठा mlx5_fpga_ipsec_cmd_context *cmd_context;
	माप_प्रकार sa_cmd_size;
	पूर्णांक err;

	hw_sa->ipsec_sa_v1.cmd = htonl(opcode);
	अगर (is_v2_sadb_supported(fdev->ipsec))
		sa_cmd_size = माप(*hw_sa);
	अन्यथा
		sa_cmd_size = माप(hw_sa->ipsec_sa_v1);

	cmd_context = (काष्ठा mlx5_fpga_ipsec_cmd_context *)
			mlx5_fpga_ipsec_cmd_exec(dev, hw_sa, sa_cmd_size);
	अगर (IS_ERR(cmd_context))
		वापस PTR_ERR(cmd_context);

	err = mlx5_fpga_ipsec_cmd_रुको(cmd_context);
	अगर (err)
		जाओ out;

	sa = (काष्ठा mlx5_अगरc_fpga_ipsec_sa *)&cmd_context->command;
	अगर (sa->ipsec_sa_v1.sw_sa_handle != cmd_context->resp.sw_sa_handle) अणु
		mlx5_fpga_err(fdev, "mismatch SA handle. cmd 0x%08x vs resp 0x%08x\n",
			      ntohl(sa->ipsec_sa_v1.sw_sa_handle),
			      ntohl(cmd_context->resp.sw_sa_handle));
		err = -EIO;
	पूर्ण

out:
	kमुक्त(cmd_context);
	वापस err;
पूर्ण

u32 mlx5_fpga_ipsec_device_caps(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;
	u32 ret = 0;

	अगर (mlx5_fpga_is_ipsec_device(mdev)) अणु
		ret |= MLX5_ACCEL_IPSEC_CAP_DEVICE;
		ret |= MLX5_ACCEL_IPSEC_CAP_REQUIRED_METADATA;
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

	अगर (!fdev->ipsec)
		वापस ret;

	अगर (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, esp))
		ret |= MLX5_ACCEL_IPSEC_CAP_ESP;

	अगर (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, ipv6))
		ret |= MLX5_ACCEL_IPSEC_CAP_IPV6;

	अगर (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, lso))
		ret |= MLX5_ACCEL_IPSEC_CAP_LSO;

	अगर (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, rx_no_trailer))
		ret |= MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER;

	अगर (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, esn)) अणु
		ret |= MLX5_ACCEL_IPSEC_CAP_ESN;
		ret |= MLX5_ACCEL_IPSEC_CAP_TX_IV_IS_ESN;
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक mlx5_fpga_ipsec_counters_count(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;

	अगर (!fdev || !fdev->ipsec)
		वापस 0;

	वापस MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps,
			number_of_ipsec_counters);
पूर्ण

अटल पूर्णांक mlx5_fpga_ipsec_counters_पढ़ो(काष्ठा mlx5_core_dev *mdev, u64 *counters,
					 अचिन्हित पूर्णांक counters_count)
अणु
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;
	अचिन्हित पूर्णांक i;
	__be32 *data;
	u32 count;
	u64 addr;
	पूर्णांक ret;

	अगर (!fdev || !fdev->ipsec)
		वापस 0;

	addr = (u64)MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps,
			     ipsec_counters_addr_low) +
	       ((u64)MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps,
			     ipsec_counters_addr_high) << 32);

	count = mlx5_fpga_ipsec_counters_count(mdev);

	data = kzalloc(array3_size(माप(*data), count, 2), GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = mlx5_fpga_mem_पढ़ो(fdev, count * माप(u64), addr, data,
				 MLX5_FPGA_ACCESS_TYPE_DONTCARE);
	अगर (ret < 0) अणु
		mlx5_fpga_err(fdev, "Failed to read IPSec counters from HW: %d\n",
			      ret);
		जाओ out;
	पूर्ण
	ret = 0;

	अगर (count > counters_count)
		count = counters_count;

	/* Each counter is low word, then high. But each word is big-endian */
	क्रम (i = 0; i < count; i++)
		counters[i] = (u64)ntohl(data[i * 2]) |
			      ((u64)ntohl(data[i * 2 + 1]) << 32);

out:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_fpga_ipsec_set_caps(काष्ठा mlx5_core_dev *mdev, u32 flags)
अणु
	काष्ठा mlx5_fpga_ipsec_cmd_context *context;
	काष्ठा mlx5_अगरc_fpga_ipsec_cmd_cap cmd = अणु0पूर्ण;
	पूर्णांक err;

	cmd.cmd = htonl(MLX5_FPGA_IPSEC_CMD_OP_SET_CAP);
	cmd.flags = htonl(flags);
	context = mlx5_fpga_ipsec_cmd_exec(mdev, &cmd, माप(cmd));
	अगर (IS_ERR(context))
		वापस PTR_ERR(context);

	err = mlx5_fpga_ipsec_cmd_रुको(context);
	अगर (err)
		जाओ out;

	अगर ((context->resp.flags & cmd.flags) != cmd.flags) अणु
		mlx5_fpga_err(context->dev, "Failed to set capabilities. cmd 0x%08x vs resp 0x%08x\n",
			      cmd.flags,
			      context->resp.flags);
		err = -EIO;
	पूर्ण

out:
	kमुक्त(context);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_fpga_ipsec_enable_supported_caps(काष्ठा mlx5_core_dev *mdev)
अणु
	u32 dev_caps = mlx5_fpga_ipsec_device_caps(mdev);
	u32 flags = 0;

	अगर (dev_caps & MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER)
		flags |= MLX5_FPGA_IPSEC_CAP_NO_TRAILER;

	वापस mlx5_fpga_ipsec_set_caps(mdev, flags);
पूर्ण

अटल व्योम
mlx5_fpga_ipsec_build_hw_xfrm(काष्ठा mlx5_core_dev *mdev,
			      स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *xfrm_attrs,
			      काष्ठा mlx5_अगरc_fpga_ipsec_sa *hw_sa)
अणु
	स्थिर काष्ठा aes_gcm_keymat *aes_gcm = &xfrm_attrs->keymat.aes_gcm;

	/* key */
	स_नकल(&hw_sa->ipsec_sa_v1.key_enc, aes_gcm->aes_key,
	       aes_gcm->key_len / 8);
	/* Duplicate 128 bit key twice according to HW layout */
	अगर (aes_gcm->key_len == 128)
		स_नकल(&hw_sa->ipsec_sa_v1.key_enc[16],
		       aes_gcm->aes_key, aes_gcm->key_len / 8);

	/* salt and seq_iv */
	स_नकल(&hw_sa->ipsec_sa_v1.gcm.salt_iv, &aes_gcm->seq_iv,
	       माप(aes_gcm->seq_iv));
	स_नकल(&hw_sa->ipsec_sa_v1.gcm.salt, &aes_gcm->salt,
	       माप(aes_gcm->salt));

	/* esn */
	अगर (xfrm_attrs->flags & MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED) अणु
		hw_sa->ipsec_sa_v1.flags |= MLX5_FPGA_IPSEC_SA_ESN_EN;
		hw_sa->ipsec_sa_v1.flags |=
				(xfrm_attrs->flags &
				 MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP) ?
					MLX5_FPGA_IPSEC_SA_ESN_OVERLAP : 0;
		hw_sa->esn = htonl(xfrm_attrs->esn);
	पूर्ण अन्यथा अणु
		hw_sa->ipsec_sa_v1.flags &= ~MLX5_FPGA_IPSEC_SA_ESN_EN;
		hw_sa->ipsec_sa_v1.flags &=
				~(xfrm_attrs->flags &
				  MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP) ?
					MLX5_FPGA_IPSEC_SA_ESN_OVERLAP : 0;
		hw_sa->esn = 0;
	पूर्ण

	/* rx handle */
	hw_sa->ipsec_sa_v1.sw_sa_handle = htonl(xfrm_attrs->sa_handle);

	/* enc mode */
	चयन (aes_gcm->key_len) अणु
	हाल 128:
		hw_sa->ipsec_sa_v1.enc_mode =
			MLX5_FPGA_IPSEC_SA_ENC_MODE_AES_GCM_128_AUTH_128;
		अवरोध;
	हाल 256:
		hw_sa->ipsec_sa_v1.enc_mode =
			MLX5_FPGA_IPSEC_SA_ENC_MODE_AES_GCM_256_AUTH_128;
		अवरोध;
	पूर्ण

	/* flags */
	hw_sa->ipsec_sa_v1.flags |= MLX5_FPGA_IPSEC_SA_SA_VALID |
			MLX5_FPGA_IPSEC_SA_SPI_EN |
			MLX5_FPGA_IPSEC_SA_IP_ESP;

	अगर (xfrm_attrs->action & MLX5_ACCEL_ESP_ACTION_ENCRYPT)
		hw_sa->ipsec_sa_v1.flags |= MLX5_FPGA_IPSEC_SA_सूची_SX;
	अन्यथा
		hw_sa->ipsec_sa_v1.flags &= ~MLX5_FPGA_IPSEC_SA_सूची_SX;
पूर्ण

अटल व्योम
mlx5_fpga_ipsec_build_hw_sa(काष्ठा mlx5_core_dev *mdev,
			    काष्ठा mlx5_accel_esp_xfrm_attrs *xfrm_attrs,
			    स्थिर __be32 saddr[4],
			    स्थिर __be32 daddr[4],
			    स्थिर __be32 spi, bool is_ipv6,
			    काष्ठा mlx5_अगरc_fpga_ipsec_sa *hw_sa)
अणु
	mlx5_fpga_ipsec_build_hw_xfrm(mdev, xfrm_attrs, hw_sa);

	/* IPs */
	स_नकल(hw_sa->ipsec_sa_v1.sip, saddr, माप(hw_sa->ipsec_sa_v1.sip));
	स_नकल(hw_sa->ipsec_sa_v1.dip, daddr, माप(hw_sa->ipsec_sa_v1.dip));

	/* SPI */
	hw_sa->ipsec_sa_v1.spi = spi;

	/* flags */
	अगर (is_ipv6)
		hw_sa->ipsec_sa_v1.flags |= MLX5_FPGA_IPSEC_SA_IPV6;
पूर्ण

अटल bool is_full_mask(स्थिर व्योम *p, माप_प्रकार len)
अणु
	WARN_ON(len % 4);

	वापस !स_प्रथम_inv(p, 0xff, len);
पूर्ण

अटल bool validate_fpga_full_mask(काष्ठा mlx5_core_dev *dev,
				    स्थिर u32 *match_c,
				    स्थिर u32 *match_v)
अणु
	स्थिर व्योम *misc_params_c = MLX5_ADDR_OF(fte_match_param,
						 match_c,
						 misc_parameters);
	स्थिर व्योम *headers_c = MLX5_ADDR_OF(fte_match_param,
					     match_c,
					     outer_headers);
	स्थिर व्योम *headers_v = MLX5_ADDR_OF(fte_match_param,
					     match_v,
					     outer_headers);

	अगर (mlx5_fs_is_outer_ipv4_flow(dev, headers_c, headers_v)) अणु
		स्थिर व्योम *s_ipv4_c = MLX5_ADDR_OF(fte_match_set_lyr_2_4,
						    headers_c,
						    src_ipv4_src_ipv6.ipv4_layout.ipv4);
		स्थिर व्योम *d_ipv4_c = MLX5_ADDR_OF(fte_match_set_lyr_2_4,
						    headers_c,
						    dst_ipv4_dst_ipv6.ipv4_layout.ipv4);

		अगर (!is_full_mask(s_ipv4_c, MLX5_FLD_SZ_BYTES(ipv4_layout,
							      ipv4)) ||
		    !is_full_mask(d_ipv4_c, MLX5_FLD_SZ_BYTES(ipv4_layout,
							      ipv4)))
			वापस false;
	पूर्ण अन्यथा अणु
		स्थिर व्योम *s_ipv6_c = MLX5_ADDR_OF(fte_match_set_lyr_2_4,
						    headers_c,
						    src_ipv4_src_ipv6.ipv6_layout.ipv6);
		स्थिर व्योम *d_ipv6_c = MLX5_ADDR_OF(fte_match_set_lyr_2_4,
						    headers_c,
						    dst_ipv4_dst_ipv6.ipv6_layout.ipv6);

		अगर (!is_full_mask(s_ipv6_c, MLX5_FLD_SZ_BYTES(ipv6_layout,
							      ipv6)) ||
		    !is_full_mask(d_ipv6_c, MLX5_FLD_SZ_BYTES(ipv6_layout,
							      ipv6)))
			वापस false;
	पूर्ण

	अगर (!is_full_mask(MLX5_ADDR_OF(fte_match_set_misc, misc_params_c,
				       outer_esp_spi),
			  MLX5_FLD_SZ_BYTES(fte_match_set_misc, outer_esp_spi)))
		वापस false;

	वापस true;
पूर्ण

अटल bool mlx5_is_fpga_ipsec_rule(काष्ठा mlx5_core_dev *dev,
				    u8 match_criteria_enable,
				    स्थिर u32 *match_c,
				    स्थिर u32 *match_v)
अणु
	u32 ipsec_dev_caps = mlx5_fpga_ipsec_device_caps(dev);
	bool ipv6_flow;

	ipv6_flow = mlx5_fs_is_outer_ipv6_flow(dev, match_c, match_v);

	अगर (!(match_criteria_enable & MLX5_MATCH_OUTER_HEADERS) ||
	    mlx5_fs_is_outer_udp_flow(match_c, match_v) ||
	    mlx5_fs_is_outer_tcp_flow(match_c, match_v) ||
	    mlx5_fs_is_vxlan_flow(match_c) ||
	    !(mlx5_fs_is_outer_ipv4_flow(dev, match_c, match_v) ||
	      ipv6_flow))
		वापस false;

	अगर (!(ipsec_dev_caps & MLX5_ACCEL_IPSEC_CAP_DEVICE))
		वापस false;

	अगर (!(ipsec_dev_caps & MLX5_ACCEL_IPSEC_CAP_ESP) &&
	    mlx5_fs_is_outer_ipsec_flow(match_c))
		वापस false;

	अगर (!(ipsec_dev_caps & MLX5_ACCEL_IPSEC_CAP_IPV6) &&
	    ipv6_flow)
		वापस false;

	अगर (!validate_fpga_full_mask(dev, match_c, match_v))
		वापस false;

	वापस true;
पूर्ण

अटल bool mlx5_is_fpga_egress_ipsec_rule(काष्ठा mlx5_core_dev *dev,
					   u8 match_criteria_enable,
					   स्थिर u32 *match_c,
					   स्थिर u32 *match_v,
					   काष्ठा mlx5_flow_act *flow_act,
					   काष्ठा mlx5_flow_context *flow_context)
अणु
	स्थिर व्योम *outer_c = MLX5_ADDR_OF(fte_match_param, match_c,
					   outer_headers);
	bool is_dmac = MLX5_GET(fte_match_set_lyr_2_4, outer_c, dmac_47_16) ||
			MLX5_GET(fte_match_set_lyr_2_4, outer_c, dmac_15_0);
	bool is_smac = MLX5_GET(fte_match_set_lyr_2_4, outer_c, smac_47_16) ||
			MLX5_GET(fte_match_set_lyr_2_4, outer_c, smac_15_0);
	पूर्णांक ret;

	ret = mlx5_is_fpga_ipsec_rule(dev, match_criteria_enable, match_c,
				      match_v);
	अगर (!ret)
		वापस ret;

	अगर (is_dmac || is_smac ||
	    (match_criteria_enable &
	     ~(MLX5_MATCH_OUTER_HEADERS | MLX5_MATCH_MISC_PARAMETERS)) ||
	    (flow_act->action & ~(MLX5_FLOW_CONTEXT_ACTION_ENCRYPT | MLX5_FLOW_CONTEXT_ACTION_ALLOW)) ||
	     (flow_context->flags & FLOW_CONTEXT_HAS_TAG))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम *mlx5_fpga_ipsec_create_sa_ctx(काष्ठा mlx5_core_dev *mdev,
					   काष्ठा mlx5_accel_esp_xfrm *accel_xfrm,
					   स्थिर __be32 saddr[4], स्थिर __be32 daddr[4],
					   स्थिर __be32 spi, bool is_ipv6, u32 *sa_handle)
अणु
	काष्ठा mlx5_fpga_ipsec_sa_ctx *sa_ctx;
	काष्ठा mlx5_fpga_esp_xfrm *fpga_xfrm =
			container_of(accel_xfrm, typeof(*fpga_xfrm),
				     accel_xfrm);
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;
	काष्ठा mlx5_fpga_ipsec *fipsec = fdev->ipsec;
	पूर्णांक opcode, err;
	व्योम *context;

	/* alloc SA */
	sa_ctx = kzalloc(माप(*sa_ctx), GFP_KERNEL);
	अगर (!sa_ctx)
		वापस ERR_PTR(-ENOMEM);

	sa_ctx->dev = mdev;

	/* build candidate SA */
	mlx5_fpga_ipsec_build_hw_sa(mdev, &accel_xfrm->attrs,
				    saddr, daddr, spi, is_ipv6,
				    &sa_ctx->hw_sa);

	mutex_lock(&fpga_xfrm->lock);

	अगर (fpga_xfrm->sa_ctx) अणु        /* multiple rules क्रम same accel_xfrm */
		/* all rules must be with same IPs and SPI */
		अगर (स_भेद(&sa_ctx->hw_sa, &fpga_xfrm->sa_ctx->hw_sa,
			   माप(sa_ctx->hw_sa))) अणु
			context = ERR_PTR(-EINVAL);
			जाओ exists;
		पूर्ण

		++fpga_xfrm->num_rules;
		context = fpga_xfrm->sa_ctx;
		जाओ exists;
	पूर्ण

	अगर (accel_xfrm->attrs.action == MLX5_ACCEL_ESP_ACTION_DECRYPT) अणु
		err = ida_alloc_min(&fipsec->halloc, 1, GFP_KERNEL);
		अगर (err < 0) अणु
			context = ERR_PTR(err);
			जाओ exists;
		पूर्ण

		sa_ctx->sa_handle = err;
		अगर (sa_handle)
			*sa_handle = sa_ctx->sa_handle;
	पूर्ण
	/* This is unbounded fpga_xfrm, try to add to hash */
	mutex_lock(&fipsec->sa_hash_lock);

	err = rhashtable_lookup_insert_fast(&fipsec->sa_hash, &sa_ctx->hash,
					    rhash_sa);
	अगर (err) अणु
		/* Can't bound dअगरferent accel_xfrm to alपढ़ोy existing sa_ctx.
		 * This is because we can't support multiple keपंचांगats क्रम
		 * same IPs and SPI
		 */
		context = ERR_PTR(-EEXIST);
		जाओ unlock_hash;
	पूर्ण

	/* Bound accel_xfrm to sa_ctx */
	opcode = is_v2_sadb_supported(fdev->ipsec) ?
			MLX5_FPGA_IPSEC_CMD_OP_ADD_SA_V2 :
			MLX5_FPGA_IPSEC_CMD_OP_ADD_SA;
	err = mlx5_fpga_ipsec_update_hw_sa(fdev, &sa_ctx->hw_sa, opcode);
	sa_ctx->hw_sa.ipsec_sa_v1.cmd = 0;
	अगर (err) अणु
		context = ERR_PTR(err);
		जाओ delete_hash;
	पूर्ण

	mutex_unlock(&fipsec->sa_hash_lock);

	++fpga_xfrm->num_rules;
	fpga_xfrm->sa_ctx = sa_ctx;
	sa_ctx->fpga_xfrm = fpga_xfrm;

	mutex_unlock(&fpga_xfrm->lock);

	वापस sa_ctx;

delete_hash:
	WARN_ON(rhashtable_हटाओ_fast(&fipsec->sa_hash, &sa_ctx->hash,
				       rhash_sa));
unlock_hash:
	mutex_unlock(&fipsec->sa_hash_lock);
	अगर (accel_xfrm->attrs.action == MLX5_ACCEL_ESP_ACTION_DECRYPT)
		ida_मुक्त(&fipsec->halloc, sa_ctx->sa_handle);
exists:
	mutex_unlock(&fpga_xfrm->lock);
	kमुक्त(sa_ctx);
	वापस context;
पूर्ण

अटल व्योम *
mlx5_fpga_ipsec_fs_create_sa_ctx(काष्ठा mlx5_core_dev *mdev,
				 काष्ठा fs_fte *fte,
				 bool is_egress)
अणु
	काष्ठा mlx5_accel_esp_xfrm *accel_xfrm;
	__be32 saddr[4], daddr[4], spi;
	काष्ठा mlx5_flow_group *fg;
	bool is_ipv6 = false;

	fs_get_obj(fg, fte->node.parent);
	/* validate */
	अगर (is_egress &&
	    !mlx5_is_fpga_egress_ipsec_rule(mdev,
					    fg->mask.match_criteria_enable,
					    fg->mask.match_criteria,
					    fte->val,
					    &fte->action,
					    &fte->flow_context))
		वापस ERR_PTR(-EINVAL);
	अन्यथा अगर (!mlx5_is_fpga_ipsec_rule(mdev,
					  fg->mask.match_criteria_enable,
					  fg->mask.match_criteria,
					  fte->val))
		वापस ERR_PTR(-EINVAL);

	/* get xfrm context */
	accel_xfrm =
		(काष्ठा mlx5_accel_esp_xfrm *)fte->action.esp_id;

	/* IPs */
	अगर (mlx5_fs_is_outer_ipv4_flow(mdev, fg->mask.match_criteria,
				       fte->val)) अणु
		स_नकल(&saddr[3],
		       MLX5_ADDR_OF(fte_match_set_lyr_2_4,
				    fte->val,
				    src_ipv4_src_ipv6.ipv4_layout.ipv4),
				    माप(saddr[3]));
		स_नकल(&daddr[3],
		       MLX5_ADDR_OF(fte_match_set_lyr_2_4,
				    fte->val,
				    dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
				    माप(daddr[3]));
	पूर्ण अन्यथा अणु
		स_नकल(saddr,
		       MLX5_ADDR_OF(fte_match_param,
				    fte->val,
				    outer_headers.src_ipv4_src_ipv6.ipv6_layout.ipv6),
				    माप(saddr));
		स_नकल(daddr,
		       MLX5_ADDR_OF(fte_match_param,
				    fte->val,
				    outer_headers.dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
				    माप(daddr));
		is_ipv6 = true;
	पूर्ण

	/* SPI */
	spi = MLX5_GET_BE(typeof(spi),
			  fte_match_param, fte->val,
			  misc_parameters.outer_esp_spi);

	/* create */
	वापस mlx5_fpga_ipsec_create_sa_ctx(mdev, accel_xfrm,
					     saddr, daddr,
					     spi, is_ipv6, शून्य);
पूर्ण

अटल व्योम
mlx5_fpga_ipsec_release_sa_ctx(काष्ठा mlx5_fpga_ipsec_sa_ctx *sa_ctx)
अणु
	काष्ठा mlx5_fpga_device *fdev = sa_ctx->dev->fpga;
	काष्ठा mlx5_fpga_ipsec *fipsec = fdev->ipsec;
	पूर्णांक opcode = is_v2_sadb_supported(fdev->ipsec) ?
			MLX5_FPGA_IPSEC_CMD_OP_DEL_SA_V2 :
			MLX5_FPGA_IPSEC_CMD_OP_DEL_SA;
	पूर्णांक err;

	err = mlx5_fpga_ipsec_update_hw_sa(fdev, &sa_ctx->hw_sa, opcode);
	sa_ctx->hw_sa.ipsec_sa_v1.cmd = 0;
	अगर (err) अणु
		WARN_ON(err);
		वापस;
	पूर्ण

	अगर (sa_ctx->fpga_xfrm->accel_xfrm.attrs.action ==
	    MLX5_ACCEL_ESP_ACTION_DECRYPT)
		ida_मुक्त(&fipsec->halloc, sa_ctx->sa_handle);

	mutex_lock(&fipsec->sa_hash_lock);
	WARN_ON(rhashtable_हटाओ_fast(&fipsec->sa_hash, &sa_ctx->hash,
				       rhash_sa));
	mutex_unlock(&fipsec->sa_hash_lock);
पूर्ण

अटल व्योम mlx5_fpga_ipsec_delete_sa_ctx(व्योम *context)
अणु
	काष्ठा mlx5_fpga_esp_xfrm *fpga_xfrm =
			((काष्ठा mlx5_fpga_ipsec_sa_ctx *)context)->fpga_xfrm;

	mutex_lock(&fpga_xfrm->lock);
	अगर (!--fpga_xfrm->num_rules) अणु
		mlx5_fpga_ipsec_release_sa_ctx(fpga_xfrm->sa_ctx);
		kमुक्त(fpga_xfrm->sa_ctx);
		fpga_xfrm->sa_ctx = शून्य;
	पूर्ण
	mutex_unlock(&fpga_xfrm->lock);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_fpga_ipsec_rule *
_rule_search(काष्ठा rb_root *root, काष्ठा fs_fte *fte)
अणु
	काष्ठा rb_node *node = root->rb_node;

	जबतक (node) अणु
		काष्ठा mlx5_fpga_ipsec_rule *rule =
				container_of(node, काष्ठा mlx5_fpga_ipsec_rule,
					     node);

		अगर (rule->fte < fte)
			node = node->rb_left;
		अन्यथा अगर (rule->fte > fte)
			node = node->rb_right;
		अन्यथा
			वापस rule;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mlx5_fpga_ipsec_rule *
rule_search(काष्ठा mlx5_fpga_ipsec *ipsec_dev, काष्ठा fs_fte *fte)
अणु
	काष्ठा mlx5_fpga_ipsec_rule *rule;

	mutex_lock(&ipsec_dev->rules_rb_lock);
	rule = _rule_search(&ipsec_dev->rules_rb, fte);
	mutex_unlock(&ipsec_dev->rules_rb_lock);

	वापस rule;
पूर्ण

अटल अंतरभूत पूर्णांक _rule_insert(काष्ठा rb_root *root,
			       काष्ठा mlx5_fpga_ipsec_rule *rule)
अणु
	काष्ठा rb_node **new = &root->rb_node, *parent = शून्य;

	/* Figure out where to put new node */
	जबतक (*new) अणु
		काष्ठा mlx5_fpga_ipsec_rule *this =
				container_of(*new, काष्ठा mlx5_fpga_ipsec_rule,
					     node);

		parent = *new;
		अगर (rule->fte < this->fte)
			new = &((*new)->rb_left);
		अन्यथा अगर (rule->fte > this->fte)
			new = &((*new)->rb_right);
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	/* Add new node and rebalance tree. */
	rb_link_node(&rule->node, parent, new);
	rb_insert_color(&rule->node, root);

	वापस 0;
पूर्ण

अटल पूर्णांक rule_insert(काष्ठा mlx5_fpga_ipsec *ipsec_dev,
		       काष्ठा mlx5_fpga_ipsec_rule *rule)
अणु
	पूर्णांक ret;

	mutex_lock(&ipsec_dev->rules_rb_lock);
	ret = _rule_insert(&ipsec_dev->rules_rb, rule);
	mutex_unlock(&ipsec_dev->rules_rb_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम _rule_delete(काष्ठा mlx5_fpga_ipsec *ipsec_dev,
				काष्ठा mlx5_fpga_ipsec_rule *rule)
अणु
	काष्ठा rb_root *root = &ipsec_dev->rules_rb;

	mutex_lock(&ipsec_dev->rules_rb_lock);
	rb_erase(&rule->node, root);
	mutex_unlock(&ipsec_dev->rules_rb_lock);
पूर्ण

अटल व्योम rule_delete(काष्ठा mlx5_fpga_ipsec *ipsec_dev,
			काष्ठा mlx5_fpga_ipsec_rule *rule)
अणु
	_rule_delete(ipsec_dev, rule);
	kमुक्त(rule);
पूर्ण

काष्ठा mailbox_mod अणु
	uपूर्णांकptr_t			saved_esp_id;
	u32				saved_action;
	u32				saved_outer_esp_spi_value;
पूर्ण;

अटल व्योम restore_spec_mailbox(काष्ठा fs_fte *fte,
				 काष्ठा mailbox_mod *mbox_mod)
अणु
	अक्षर *misc_params_v = MLX5_ADDR_OF(fte_match_param,
					   fte->val,
					   misc_parameters);

	MLX5_SET(fte_match_set_misc, misc_params_v, outer_esp_spi,
		 mbox_mod->saved_outer_esp_spi_value);
	fte->action.action |= mbox_mod->saved_action;
	fte->action.esp_id = (uपूर्णांकptr_t)mbox_mod->saved_esp_id;
पूर्ण

अटल व्योम modअगरy_spec_mailbox(काष्ठा mlx5_core_dev *mdev,
				काष्ठा fs_fte *fte,
				काष्ठा mailbox_mod *mbox_mod)
अणु
	अक्षर *misc_params_v = MLX5_ADDR_OF(fte_match_param,
					   fte->val,
					   misc_parameters);

	mbox_mod->saved_esp_id = fte->action.esp_id;
	mbox_mod->saved_action = fte->action.action &
			(MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
			 MLX5_FLOW_CONTEXT_ACTION_DECRYPT);
	mbox_mod->saved_outer_esp_spi_value =
			MLX5_GET(fte_match_set_misc, misc_params_v,
				 outer_esp_spi);

	fte->action.esp_id = 0;
	fte->action.action &= ~(MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
				MLX5_FLOW_CONTEXT_ACTION_DECRYPT);
	अगर (!MLX5_CAP_FLOWTABLE(mdev,
				flow_table_properties_nic_receive.ft_field_support.outer_esp_spi))
		MLX5_SET(fte_match_set_misc, misc_params_v, outer_esp_spi, 0);
पूर्ण

अटल क्रमागत fs_flow_table_type egress_to_fs_ft(bool egress)
अणु
	वापस egress ? FS_FT_NIC_TX : FS_FT_NIC_RX;
पूर्ण

अटल पूर्णांक fpga_ipsec_fs_create_flow_group(काष्ठा mlx5_flow_root_namespace *ns,
					   काष्ठा mlx5_flow_table *ft,
					   u32 *in,
					   काष्ठा mlx5_flow_group *fg,
					   bool is_egress)
अणु
	पूर्णांक (*create_flow_group)(काष्ठा mlx5_flow_root_namespace *ns,
				 काष्ठा mlx5_flow_table *ft, u32 *in,
				 काष्ठा mlx5_flow_group *fg) =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(is_egress))->create_flow_group;
	अक्षर *misc_params_c = MLX5_ADDR_OF(create_flow_group_in, in,
					   match_criteria.misc_parameters);
	काष्ठा mlx5_core_dev *dev = ns->dev;
	u32 saved_outer_esp_spi_mask;
	u8 match_criteria_enable;
	पूर्णांक ret;

	अगर (MLX5_CAP_FLOWTABLE(dev,
			       flow_table_properties_nic_receive.ft_field_support.outer_esp_spi))
		वापस create_flow_group(ns, ft, in, fg);

	match_criteria_enable =
		MLX5_GET(create_flow_group_in, in, match_criteria_enable);
	saved_outer_esp_spi_mask =
		MLX5_GET(fte_match_set_misc, misc_params_c, outer_esp_spi);
	अगर (!match_criteria_enable || !saved_outer_esp_spi_mask)
		वापस create_flow_group(ns, ft, in, fg);

	MLX5_SET(fte_match_set_misc, misc_params_c, outer_esp_spi, 0);

	अगर (!(*misc_params_c) &&
	    !स_भेद(misc_params_c, misc_params_c + 1, MLX5_ST_SZ_BYTES(fte_match_set_misc) - 1))
		MLX5_SET(create_flow_group_in, in, match_criteria_enable,
			 match_criteria_enable & ~MLX5_MATCH_MISC_PARAMETERS);

	ret = create_flow_group(ns, ft, in, fg);

	MLX5_SET(fte_match_set_misc, misc_params_c, outer_esp_spi, saved_outer_esp_spi_mask);
	MLX5_SET(create_flow_group_in, in, match_criteria_enable, match_criteria_enable);

	वापस ret;
पूर्ण

अटल पूर्णांक fpga_ipsec_fs_create_fte(काष्ठा mlx5_flow_root_namespace *ns,
				    काष्ठा mlx5_flow_table *ft,
				    काष्ठा mlx5_flow_group *fg,
				    काष्ठा fs_fte *fte,
				    bool is_egress)
अणु
	पूर्णांक (*create_fte)(काष्ठा mlx5_flow_root_namespace *ns,
			  काष्ठा mlx5_flow_table *ft,
			  काष्ठा mlx5_flow_group *fg,
			  काष्ठा fs_fte *fte) =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(is_egress))->create_fte;
	काष्ठा mlx5_core_dev *dev = ns->dev;
	काष्ठा mlx5_fpga_device *fdev = dev->fpga;
	काष्ठा mlx5_fpga_ipsec *fipsec = fdev->ipsec;
	काष्ठा mlx5_fpga_ipsec_rule *rule;
	bool is_esp = fte->action.esp_id;
	काष्ठा mailbox_mod mbox_mod;
	पूर्णांक ret;

	अगर (!is_esp ||
	    !(fte->action.action &
	      (MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
	       MLX5_FLOW_CONTEXT_ACTION_DECRYPT)))
		वापस create_fte(ns, ft, fg, fte);

	rule = kzalloc(माप(*rule), GFP_KERNEL);
	अगर (!rule)
		वापस -ENOMEM;

	rule->ctx = mlx5_fpga_ipsec_fs_create_sa_ctx(dev, fte, is_egress);
	अगर (IS_ERR(rule->ctx)) अणु
		पूर्णांक err = PTR_ERR(rule->ctx);

		kमुक्त(rule);
		वापस err;
	पूर्ण

	rule->fte = fte;
	WARN_ON(rule_insert(fipsec, rule));

	modअगरy_spec_mailbox(dev, fte, &mbox_mod);
	ret = create_fte(ns, ft, fg, fte);
	restore_spec_mailbox(fte, &mbox_mod);
	अगर (ret) अणु
		_rule_delete(fipsec, rule);
		mlx5_fpga_ipsec_delete_sa_ctx(rule->ctx);
		kमुक्त(rule);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fpga_ipsec_fs_update_fte(काष्ठा mlx5_flow_root_namespace *ns,
				    काष्ठा mlx5_flow_table *ft,
				    काष्ठा mlx5_flow_group *fg,
				    पूर्णांक modअगरy_mask,
				    काष्ठा fs_fte *fte,
				    bool is_egress)
अणु
	पूर्णांक (*update_fte)(काष्ठा mlx5_flow_root_namespace *ns,
			  काष्ठा mlx5_flow_table *ft,
			  काष्ठा mlx5_flow_group *fg,
			  पूर्णांक modअगरy_mask,
			  काष्ठा fs_fte *fte) =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(is_egress))->update_fte;
	काष्ठा mlx5_core_dev *dev = ns->dev;
	bool is_esp = fte->action.esp_id;
	काष्ठा mailbox_mod mbox_mod;
	पूर्णांक ret;

	अगर (!is_esp ||
	    !(fte->action.action &
	      (MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
	       MLX5_FLOW_CONTEXT_ACTION_DECRYPT)))
		वापस update_fte(ns, ft, fg, modअगरy_mask, fte);

	modअगरy_spec_mailbox(dev, fte, &mbox_mod);
	ret = update_fte(ns, ft, fg, modअगरy_mask, fte);
	restore_spec_mailbox(fte, &mbox_mod);

	वापस ret;
पूर्ण

अटल पूर्णांक fpga_ipsec_fs_delete_fte(काष्ठा mlx5_flow_root_namespace *ns,
				    काष्ठा mlx5_flow_table *ft,
				    काष्ठा fs_fte *fte,
				    bool is_egress)
अणु
	पूर्णांक (*delete_fte)(काष्ठा mlx5_flow_root_namespace *ns,
			  काष्ठा mlx5_flow_table *ft,
			  काष्ठा fs_fte *fte) =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(is_egress))->delete_fte;
	काष्ठा mlx5_core_dev *dev = ns->dev;
	काष्ठा mlx5_fpga_device *fdev = dev->fpga;
	काष्ठा mlx5_fpga_ipsec *fipsec = fdev->ipsec;
	काष्ठा mlx5_fpga_ipsec_rule *rule;
	bool is_esp = fte->action.esp_id;
	काष्ठा mailbox_mod mbox_mod;
	पूर्णांक ret;

	अगर (!is_esp ||
	    !(fte->action.action &
	      (MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
	       MLX5_FLOW_CONTEXT_ACTION_DECRYPT)))
		वापस delete_fte(ns, ft, fte);

	rule = rule_search(fipsec, fte);
	अगर (!rule)
		वापस -ENOENT;

	mlx5_fpga_ipsec_delete_sa_ctx(rule->ctx);
	rule_delete(fipsec, rule);

	modअगरy_spec_mailbox(dev, fte, &mbox_mod);
	ret = delete_fte(ns, ft, fte);
	restore_spec_mailbox(fte, &mbox_mod);

	वापस ret;
पूर्ण

अटल पूर्णांक
mlx5_fpga_ipsec_fs_create_flow_group_egress(काष्ठा mlx5_flow_root_namespace *ns,
					    काष्ठा mlx5_flow_table *ft,
					    u32 *in,
					    काष्ठा mlx5_flow_group *fg)
अणु
	वापस fpga_ipsec_fs_create_flow_group(ns, ft, in, fg, true);
पूर्ण

अटल पूर्णांक
mlx5_fpga_ipsec_fs_create_fte_egress(काष्ठा mlx5_flow_root_namespace *ns,
				     काष्ठा mlx5_flow_table *ft,
				     काष्ठा mlx5_flow_group *fg,
				     काष्ठा fs_fte *fte)
अणु
	वापस fpga_ipsec_fs_create_fte(ns, ft, fg, fte, true);
पूर्ण

अटल पूर्णांक
mlx5_fpga_ipsec_fs_update_fte_egress(काष्ठा mlx5_flow_root_namespace *ns,
				     काष्ठा mlx5_flow_table *ft,
				     काष्ठा mlx5_flow_group *fg,
				     पूर्णांक modअगरy_mask,
				     काष्ठा fs_fte *fte)
अणु
	वापस fpga_ipsec_fs_update_fte(ns, ft, fg, modअगरy_mask, fte,
					true);
पूर्ण

अटल पूर्णांक
mlx5_fpga_ipsec_fs_delete_fte_egress(काष्ठा mlx5_flow_root_namespace *ns,
				     काष्ठा mlx5_flow_table *ft,
				     काष्ठा fs_fte *fte)
अणु
	वापस fpga_ipsec_fs_delete_fte(ns, ft, fte, true);
पूर्ण

अटल पूर्णांक
mlx5_fpga_ipsec_fs_create_flow_group_ingress(काष्ठा mlx5_flow_root_namespace *ns,
					     काष्ठा mlx5_flow_table *ft,
					     u32 *in,
					     काष्ठा mlx5_flow_group *fg)
अणु
	वापस fpga_ipsec_fs_create_flow_group(ns, ft, in, fg, false);
पूर्ण

अटल पूर्णांक
mlx5_fpga_ipsec_fs_create_fte_ingress(काष्ठा mlx5_flow_root_namespace *ns,
				      काष्ठा mlx5_flow_table *ft,
				      काष्ठा mlx5_flow_group *fg,
				      काष्ठा fs_fte *fte)
अणु
	वापस fpga_ipsec_fs_create_fte(ns, ft, fg, fte, false);
पूर्ण

अटल पूर्णांक
mlx5_fpga_ipsec_fs_update_fte_ingress(काष्ठा mlx5_flow_root_namespace *ns,
				      काष्ठा mlx5_flow_table *ft,
				      काष्ठा mlx5_flow_group *fg,
				      पूर्णांक modअगरy_mask,
				      काष्ठा fs_fte *fte)
अणु
	वापस fpga_ipsec_fs_update_fte(ns, ft, fg, modअगरy_mask, fte,
					false);
पूर्ण

अटल पूर्णांक
mlx5_fpga_ipsec_fs_delete_fte_ingress(काष्ठा mlx5_flow_root_namespace *ns,
				      काष्ठा mlx5_flow_table *ft,
				      काष्ठा fs_fte *fte)
अणु
	वापस fpga_ipsec_fs_delete_fte(ns, ft, fte, false);
पूर्ण

अटल काष्ठा mlx5_flow_cmds fpga_ipsec_ingress;
अटल काष्ठा mlx5_flow_cmds fpga_ipsec_egress;

स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_शेष_ipsec_fpga_cmds(क्रमागत fs_flow_table_type type)
अणु
	चयन (type) अणु
	हाल FS_FT_NIC_RX:
		वापस &fpga_ipsec_ingress;
	हाल FS_FT_NIC_TX:
		वापस &fpga_ipsec_egress;
	शेष:
		WARN_ON(true);
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_fpga_ipsec_init(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_conn_attr init_attr = अणु0पूर्ण;
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;
	काष्ठा mlx5_fpga_conn *conn;
	पूर्णांक err;

	अगर (!mlx5_fpga_is_ipsec_device(mdev))
		वापस 0;

	fdev->ipsec = kzalloc(माप(*fdev->ipsec), GFP_KERNEL);
	अगर (!fdev->ipsec)
		वापस -ENOMEM;

	fdev->ipsec->fdev = fdev;

	err = mlx5_fpga_get_sbu_caps(fdev, माप(fdev->ipsec->caps),
				     fdev->ipsec->caps);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to retrieve IPSec extended capabilities: %d\n",
			      err);
		जाओ error;
	पूर्ण

	INIT_LIST_HEAD(&fdev->ipsec->pending_cmds);
	spin_lock_init(&fdev->ipsec->pending_cmds_lock);

	init_attr.rx_size = SBU_QP_QUEUE_SIZE;
	init_attr.tx_size = SBU_QP_QUEUE_SIZE;
	init_attr.recv_cb = mlx5_fpga_ipsec_recv;
	init_attr.cb_arg = fdev;
	conn = mlx5_fpga_sbu_conn_create(fdev, &init_attr);
	अगर (IS_ERR(conn)) अणु
		err = PTR_ERR(conn);
		mlx5_fpga_err(fdev, "Error creating IPSec command connection %d\n",
			      err);
		जाओ error;
	पूर्ण
	fdev->ipsec->conn = conn;

	err = rhashtable_init(&fdev->ipsec->sa_hash, &rhash_sa);
	अगर (err)
		जाओ err_destroy_conn;
	mutex_init(&fdev->ipsec->sa_hash_lock);

	fdev->ipsec->rules_rb = RB_ROOT;
	mutex_init(&fdev->ipsec->rules_rb_lock);

	err = mlx5_fpga_ipsec_enable_supported_caps(mdev);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to enable IPSec extended capabilities: %d\n",
			      err);
		जाओ err_destroy_hash;
	पूर्ण

	ida_init(&fdev->ipsec->halloc);

	वापस 0;

err_destroy_hash:
	rhashtable_destroy(&fdev->ipsec->sa_hash);

err_destroy_conn:
	mlx5_fpga_sbu_conn_destroy(conn);

error:
	kमुक्त(fdev->ipsec);
	fdev->ipsec = शून्य;
	वापस err;
पूर्ण

अटल व्योम destroy_rules_rb(काष्ठा rb_root *root)
अणु
	काष्ठा mlx5_fpga_ipsec_rule *r, *पंचांगp;

	rbtree_postorder_क्रम_each_entry_safe(r, पंचांगp, root, node) अणु
		rb_erase(&r->node, root);
		mlx5_fpga_ipsec_delete_sa_ctx(r->ctx);
		kमुक्त(r);
	पूर्ण
पूर्ण

अटल व्योम mlx5_fpga_ipsec_cleanup(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;

	अगर (!mlx5_fpga_is_ipsec_device(mdev))
		वापस;

	ida_destroy(&fdev->ipsec->halloc);
	destroy_rules_rb(&fdev->ipsec->rules_rb);
	rhashtable_destroy(&fdev->ipsec->sa_hash);

	mlx5_fpga_sbu_conn_destroy(fdev->ipsec->conn);
	kमुक्त(fdev->ipsec);
	fdev->ipsec = शून्य;
पूर्ण

व्योम mlx5_fpga_ipsec_build_fs_cmds(व्योम)
अणु
	/* ingress */
	fpga_ipsec_ingress.create_flow_table =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(false))->create_flow_table;
	fpga_ipsec_ingress.destroy_flow_table =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(false))->destroy_flow_table;
	fpga_ipsec_ingress.modअगरy_flow_table =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(false))->modअगरy_flow_table;
	fpga_ipsec_ingress.create_flow_group =
		mlx5_fpga_ipsec_fs_create_flow_group_ingress;
	fpga_ipsec_ingress.destroy_flow_group =
		 mlx5_fs_cmd_get_शेष(egress_to_fs_ft(false))->destroy_flow_group;
	fpga_ipsec_ingress.create_fte =
		mlx5_fpga_ipsec_fs_create_fte_ingress;
	fpga_ipsec_ingress.update_fte =
		mlx5_fpga_ipsec_fs_update_fte_ingress;
	fpga_ipsec_ingress.delete_fte =
		mlx5_fpga_ipsec_fs_delete_fte_ingress;
	fpga_ipsec_ingress.update_root_ft =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(false))->update_root_ft;

	/* egress */
	fpga_ipsec_egress.create_flow_table =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(true))->create_flow_table;
	fpga_ipsec_egress.destroy_flow_table =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(true))->destroy_flow_table;
	fpga_ipsec_egress.modअगरy_flow_table =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(true))->modअगरy_flow_table;
	fpga_ipsec_egress.create_flow_group =
		mlx5_fpga_ipsec_fs_create_flow_group_egress;
	fpga_ipsec_egress.destroy_flow_group =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(true))->destroy_flow_group;
	fpga_ipsec_egress.create_fte =
		mlx5_fpga_ipsec_fs_create_fte_egress;
	fpga_ipsec_egress.update_fte =
		mlx5_fpga_ipsec_fs_update_fte_egress;
	fpga_ipsec_egress.delete_fte =
		mlx5_fpga_ipsec_fs_delete_fte_egress;
	fpga_ipsec_egress.update_root_ft =
		mlx5_fs_cmd_get_शेष(egress_to_fs_ft(true))->update_root_ft;
पूर्ण

अटल पूर्णांक
mlx5_fpga_esp_validate_xfrm_attrs(काष्ठा mlx5_core_dev *mdev,
				  स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs)
अणु
	अगर (attrs->tfc_pad) अणु
		mlx5_core_err(mdev, "Cannot offload xfrm states with tfc padding\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (attrs->replay_type != MLX5_ACCEL_ESP_REPLAY_NONE) अणु
		mlx5_core_err(mdev, "Cannot offload xfrm states with anti replay\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (attrs->keymat_type != MLX5_ACCEL_ESP_KEYMAT_AES_GCM) अणु
		mlx5_core_err(mdev, "Only aes gcm keymat is supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (attrs->keymat.aes_gcm.iv_algo !=
	    MLX5_ACCEL_ESP_AES_GCM_IV_ALGO_SEQ) अणु
		mlx5_core_err(mdev, "Only iv sequence algo is supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (attrs->keymat.aes_gcm.icv_len != 128) अणु
		mlx5_core_err(mdev, "Cannot offload xfrm states with AEAD ICV length other than 128bit\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (attrs->keymat.aes_gcm.key_len != 128 &&
	    attrs->keymat.aes_gcm.key_len != 256) अणु
		mlx5_core_err(mdev, "Cannot offload xfrm states with AEAD key length other than 128/256 bit\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((attrs->flags & MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED) &&
	    (!MLX5_GET(ipsec_extended_cap, mdev->fpga->ipsec->caps,
		       v2_command))) अणु
		mlx5_core_err(mdev, "Cannot offload xfrm states with AEAD key length other than 128/256 bit\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mlx5_accel_esp_xfrm *
mlx5_fpga_esp_create_xfrm(काष्ठा mlx5_core_dev *mdev,
			  स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
			  u32 flags)
अणु
	काष्ठा mlx5_fpga_esp_xfrm *fpga_xfrm;

	अगर (!(flags & MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA)) अणु
		mlx5_core_warn(mdev, "Tried to create an esp action without metadata\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (mlx5_fpga_esp_validate_xfrm_attrs(mdev, attrs)) अणु
		mlx5_core_warn(mdev, "Tried to create an esp with unsupported attrs\n");
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	fpga_xfrm = kzalloc(माप(*fpga_xfrm), GFP_KERNEL);
	अगर (!fpga_xfrm)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&fpga_xfrm->lock);
	स_नकल(&fpga_xfrm->accel_xfrm.attrs, attrs,
	       माप(fpga_xfrm->accel_xfrm.attrs));

	वापस &fpga_xfrm->accel_xfrm;
पूर्ण

अटल व्योम mlx5_fpga_esp_destroy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm)
अणु
	काष्ठा mlx5_fpga_esp_xfrm *fpga_xfrm =
			container_of(xfrm, काष्ठा mlx5_fpga_esp_xfrm,
				     accel_xfrm);
	/* assuming no sa_ctx are connected to this xfrm_ctx */
	kमुक्त(fpga_xfrm);
पूर्ण

अटल पूर्णांक mlx5_fpga_esp_modअगरy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm,
				     स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs)
अणु
	काष्ठा mlx5_core_dev *mdev = xfrm->mdev;
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;
	काष्ठा mlx5_fpga_ipsec *fipsec = fdev->ipsec;
	काष्ठा mlx5_fpga_esp_xfrm *fpga_xfrm;
	काष्ठा mlx5_अगरc_fpga_ipsec_sa org_hw_sa;

	पूर्णांक err = 0;

	अगर (!स_भेद(&xfrm->attrs, attrs, माप(xfrm->attrs)))
		वापस 0;

	अगर (mlx5_fpga_esp_validate_xfrm_attrs(mdev, attrs)) अणु
		mlx5_core_warn(mdev, "Tried to create an esp with unsupported attrs\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (is_v2_sadb_supported(fipsec)) अणु
		mlx5_core_warn(mdev, "Modify esp is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	fpga_xfrm = container_of(xfrm, काष्ठा mlx5_fpga_esp_xfrm, accel_xfrm);

	mutex_lock(&fpga_xfrm->lock);

	अगर (!fpga_xfrm->sa_ctx)
		/* Unbounded xfrm, chane only sw attrs */
		जाओ change_sw_xfrm_attrs;

	/* copy original hw sa */
	स_नकल(&org_hw_sa, &fpga_xfrm->sa_ctx->hw_sa, माप(org_hw_sa));
	mutex_lock(&fipsec->sa_hash_lock);
	/* हटाओ original hw sa from hash */
	WARN_ON(rhashtable_हटाओ_fast(&fipsec->sa_hash,
				       &fpga_xfrm->sa_ctx->hash, rhash_sa));
	/* update hw_sa with new xfrm attrs*/
	mlx5_fpga_ipsec_build_hw_xfrm(xfrm->mdev, attrs,
				      &fpga_xfrm->sa_ctx->hw_sa);
	/* try to insert new hw_sa to hash */
	err = rhashtable_insert_fast(&fipsec->sa_hash,
				     &fpga_xfrm->sa_ctx->hash, rhash_sa);
	अगर (err)
		जाओ rollback_sa;

	/* modअगरy device with new hw_sa */
	err = mlx5_fpga_ipsec_update_hw_sa(fdev, &fpga_xfrm->sa_ctx->hw_sa,
					   MLX5_FPGA_IPSEC_CMD_OP_MOD_SA_V2);
	fpga_xfrm->sa_ctx->hw_sa.ipsec_sa_v1.cmd = 0;
	अगर (err)
		WARN_ON(rhashtable_हटाओ_fast(&fipsec->sa_hash,
					       &fpga_xfrm->sa_ctx->hash,
					       rhash_sa));
rollback_sa:
	अगर (err) अणु
		/* वापस original hw_sa to hash */
		स_नकल(&fpga_xfrm->sa_ctx->hw_sa, &org_hw_sa,
		       माप(org_hw_sa));
		WARN_ON(rhashtable_insert_fast(&fipsec->sa_hash,
					       &fpga_xfrm->sa_ctx->hash,
					       rhash_sa));
	पूर्ण
	mutex_unlock(&fipsec->sa_hash_lock);

change_sw_xfrm_attrs:
	अगर (!err)
		स_नकल(&xfrm->attrs, attrs, माप(xfrm->attrs));
	mutex_unlock(&fpga_xfrm->lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा mlx5_accel_ipsec_ops fpga_ipsec_ops = अणु
	.device_caps = mlx5_fpga_ipsec_device_caps,
	.counters_count = mlx5_fpga_ipsec_counters_count,
	.counters_पढ़ो = mlx5_fpga_ipsec_counters_पढ़ो,
	.create_hw_context = mlx5_fpga_ipsec_create_sa_ctx,
	.मुक्त_hw_context = mlx5_fpga_ipsec_delete_sa_ctx,
	.init = mlx5_fpga_ipsec_init,
	.cleanup = mlx5_fpga_ipsec_cleanup,
	.esp_create_xfrm = mlx5_fpga_esp_create_xfrm,
	.esp_modअगरy_xfrm = mlx5_fpga_esp_modअगरy_xfrm,
	.esp_destroy_xfrm = mlx5_fpga_esp_destroy_xfrm,
पूर्ण;

स्थिर काष्ठा mlx5_accel_ipsec_ops *mlx5_fpga_ipsec_ops(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (!mlx5_fpga_is_ipsec_device(mdev))
		वापस शून्य;

	वापस &fpga_ipsec_ops;
पूर्ण
