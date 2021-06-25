<शैली गुरु>
/*
 * Copyright (c) 2013-2016, Mellanox Technologies. All rights reserved.
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
 */

#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/io-mapping.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/eq.h>
#समावेश <linux/debugfs.h>

#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"

क्रमागत अणु
	CMD_IF_REV = 5,
पूर्ण;

क्रमागत अणु
	CMD_MODE_POLLING,
	CMD_MODE_EVENTS
पूर्ण;

क्रमागत अणु
	MLX5_CMD_DELIVERY_STAT_OK			= 0x0,
	MLX5_CMD_DELIVERY_STAT_SIGNAT_ERR		= 0x1,
	MLX5_CMD_DELIVERY_STAT_TOK_ERR			= 0x2,
	MLX5_CMD_DELIVERY_STAT_BAD_BLK_NUM_ERR		= 0x3,
	MLX5_CMD_DELIVERY_STAT_OUT_PTR_ALIGN_ERR	= 0x4,
	MLX5_CMD_DELIVERY_STAT_IN_PTR_ALIGN_ERR		= 0x5,
	MLX5_CMD_DELIVERY_STAT_FW_ERR			= 0x6,
	MLX5_CMD_DELIVERY_STAT_IN_LENGTH_ERR		= 0x7,
	MLX5_CMD_DELIVERY_STAT_OUT_LENGTH_ERR		= 0x8,
	MLX5_CMD_DELIVERY_STAT_RES_FLD_NOT_CLR_ERR	= 0x9,
	MLX5_CMD_DELIVERY_STAT_CMD_DESCR_ERR		= 0x10,
पूर्ण;

अटल काष्ठा mlx5_cmd_work_ent *
cmd_alloc_ent(काष्ठा mlx5_cmd *cmd, काष्ठा mlx5_cmd_msg *in,
	      काष्ठा mlx5_cmd_msg *out, व्योम *uout, पूर्णांक uout_size,
	      mlx5_cmd_cbk_t cbk, व्योम *context, पूर्णांक page_queue)
अणु
	gfp_t alloc_flags = cbk ? GFP_ATOMIC : GFP_KERNEL;
	काष्ठा mlx5_cmd_work_ent *ent;

	ent = kzalloc(माप(*ent), alloc_flags);
	अगर (!ent)
		वापस ERR_PTR(-ENOMEM);

	ent->idx	= -EINVAL;
	ent->in		= in;
	ent->out	= out;
	ent->uout	= uout;
	ent->uout_size	= uout_size;
	ent->callback	= cbk;
	ent->context	= context;
	ent->cmd	= cmd;
	ent->page_queue = page_queue;
	refcount_set(&ent->refcnt, 1);

	वापस ent;
पूर्ण

अटल व्योम cmd_मुक्त_ent(काष्ठा mlx5_cmd_work_ent *ent)
अणु
	kमुक्त(ent);
पूर्ण

अटल u8 alloc_token(काष्ठा mlx5_cmd *cmd)
अणु
	u8 token;

	spin_lock(&cmd->token_lock);
	cmd->token++;
	अगर (cmd->token == 0)
		cmd->token++;
	token = cmd->token;
	spin_unlock(&cmd->token_lock);

	वापस token;
पूर्ण

अटल पूर्णांक cmd_alloc_index(काष्ठा mlx5_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cmd->alloc_lock, flags);
	ret = find_first_bit(&cmd->biपंचांगask, cmd->max_reg_cmds);
	अगर (ret < cmd->max_reg_cmds)
		clear_bit(ret, &cmd->biपंचांगask);
	spin_unlock_irqrestore(&cmd->alloc_lock, flags);

	वापस ret < cmd->max_reg_cmds ? ret : -ENOMEM;
पूर्ण

अटल व्योम cmd_मुक्त_index(काष्ठा mlx5_cmd *cmd, पूर्णांक idx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cmd->alloc_lock, flags);
	set_bit(idx, &cmd->biपंचांगask);
	spin_unlock_irqrestore(&cmd->alloc_lock, flags);
पूर्ण

अटल व्योम cmd_ent_get(काष्ठा mlx5_cmd_work_ent *ent)
अणु
	refcount_inc(&ent->refcnt);
पूर्ण

अटल व्योम cmd_ent_put(काष्ठा mlx5_cmd_work_ent *ent)
अणु
	अगर (!refcount_dec_and_test(&ent->refcnt))
		वापस;

	अगर (ent->idx >= 0)
		cmd_मुक्त_index(ent->cmd, ent->idx);

	cmd_मुक्त_ent(ent);
पूर्ण

अटल काष्ठा mlx5_cmd_layout *get_inst(काष्ठा mlx5_cmd *cmd, पूर्णांक idx)
अणु
	वापस cmd->cmd_buf + (idx << cmd->log_stride);
पूर्ण

अटल पूर्णांक mlx5_calc_cmd_blocks(काष्ठा mlx5_cmd_msg *msg)
अणु
	पूर्णांक size = msg->len;
	पूर्णांक blen = size - min_t(पूर्णांक, माप(msg->first.data), size);

	वापस DIV_ROUND_UP(blen, MLX5_CMD_DATA_BLOCK_SIZE);
पूर्ण

अटल u8 xor8_buf(व्योम *buf, माप_प्रकार offset, पूर्णांक len)
अणु
	u8 *ptr = buf;
	u8 sum = 0;
	पूर्णांक i;
	पूर्णांक end = len + offset;

	क्रम (i = offset; i < end; i++)
		sum ^= ptr[i];

	वापस sum;
पूर्ण

अटल पूर्णांक verअगरy_block_sig(काष्ठा mlx5_cmd_prot_block *block)
अणु
	माप_प्रकार rsvd0_off = दुरत्व(काष्ठा mlx5_cmd_prot_block, rsvd0);
	पूर्णांक xor_len = माप(*block) - माप(block->data) - 1;

	अगर (xor8_buf(block, rsvd0_off, xor_len) != 0xff)
		वापस -EINVAL;

	अगर (xor8_buf(block, 0, माप(*block)) != 0xff)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम calc_block_sig(काष्ठा mlx5_cmd_prot_block *block)
अणु
	पूर्णांक ctrl_xor_len = माप(*block) - माप(block->data) - 2;
	माप_प्रकार rsvd0_off = दुरत्व(काष्ठा mlx5_cmd_prot_block, rsvd0);

	block->ctrl_sig = ~xor8_buf(block, rsvd0_off, ctrl_xor_len);
	block->sig = ~xor8_buf(block, 0, माप(*block) - 1);
पूर्ण

अटल व्योम calc_chain_sig(काष्ठा mlx5_cmd_msg *msg)
अणु
	काष्ठा mlx5_cmd_mailbox *next = msg->next;
	पूर्णांक n = mlx5_calc_cmd_blocks(msg);
	पूर्णांक i = 0;

	क्रम (i = 0; i < n && next; i++)  अणु
		calc_block_sig(next->buf);
		next = next->next;
	पूर्ण
पूर्ण

अटल व्योम set_signature(काष्ठा mlx5_cmd_work_ent *ent, पूर्णांक csum)
अणु
	ent->lay->sig = ~xor8_buf(ent->lay, 0,  माप(*ent->lay));
	अगर (csum) अणु
		calc_chain_sig(ent->in);
		calc_chain_sig(ent->out);
	पूर्ण
पूर्ण

अटल व्योम poll_समयout(काष्ठा mlx5_cmd_work_ent *ent)
अणु
	अचिन्हित दीर्घ poll_end = jअगरfies + msecs_to_jअगरfies(MLX5_CMD_TIMEOUT_MSEC + 1000);
	u8 own;

	करो अणु
		own = READ_ONCE(ent->lay->status_own);
		अगर (!(own & CMD_OWNER_HW)) अणु
			ent->ret = 0;
			वापस;
		पूर्ण
		cond_resched();
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, poll_end));

	ent->ret = -ETIMEDOUT;
पूर्ण

अटल पूर्णांक verअगरy_signature(काष्ठा mlx5_cmd_work_ent *ent)
अणु
	काष्ठा mlx5_cmd_mailbox *next = ent->out->next;
	पूर्णांक n = mlx5_calc_cmd_blocks(ent->out);
	पूर्णांक err;
	u8 sig;
	पूर्णांक i = 0;

	sig = xor8_buf(ent->lay, 0, माप(*ent->lay));
	अगर (sig != 0xff)
		वापस -EINVAL;

	क्रम (i = 0; i < n && next; i++) अणु
		err = verअगरy_block_sig(next->buf);
		अगर (err)
			वापस err;

		next = next->next;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dump_buf(व्योम *buf, पूर्णांक size, पूर्णांक data_only, पूर्णांक offset, पूर्णांक idx)
अणु
	__be32 *p = buf;
	पूर्णांक i;

	क्रम (i = 0; i < size; i += 16) अणु
		pr_debug("cmd[%d]: %03x: %08x %08x %08x %08x\n", idx, offset,
			 be32_to_cpu(p[0]), be32_to_cpu(p[1]),
			 be32_to_cpu(p[2]), be32_to_cpu(p[3]));
		p += 4;
		offset += 16;
	पूर्ण
	अगर (!data_only)
		pr_debug("\n");
पूर्ण

अटल पूर्णांक mlx5_पूर्णांकernal_err_ret_value(काष्ठा mlx5_core_dev *dev, u16 op,
				       u32 *synd, u8 *status)
अणु
	*synd = 0;
	*status = 0;

	चयन (op) अणु
	हाल MLX5_CMD_OP_TEARDOWN_HCA:
	हाल MLX5_CMD_OP_DISABLE_HCA:
	हाल MLX5_CMD_OP_MANAGE_PAGES:
	हाल MLX5_CMD_OP_DESTROY_MKEY:
	हाल MLX5_CMD_OP_DESTROY_EQ:
	हाल MLX5_CMD_OP_DESTROY_CQ:
	हाल MLX5_CMD_OP_DESTROY_QP:
	हाल MLX5_CMD_OP_DESTROY_PSV:
	हाल MLX5_CMD_OP_DESTROY_SRQ:
	हाल MLX5_CMD_OP_DESTROY_XRC_SRQ:
	हाल MLX5_CMD_OP_DESTROY_XRQ:
	हाल MLX5_CMD_OP_DESTROY_DCT:
	हाल MLX5_CMD_OP_DEALLOC_Q_COUNTER:
	हाल MLX5_CMD_OP_DESTROY_SCHEDULING_ELEMENT:
	हाल MLX5_CMD_OP_DESTROY_QOS_PARA_VPORT:
	हाल MLX5_CMD_OP_DEALLOC_PD:
	हाल MLX5_CMD_OP_DEALLOC_UAR:
	हाल MLX5_CMD_OP_DETACH_FROM_MCG:
	हाल MLX5_CMD_OP_DEALLOC_XRCD:
	हाल MLX5_CMD_OP_DEALLOC_TRANSPORT_DOMAIN:
	हाल MLX5_CMD_OP_DELETE_VXLAN_UDP_DPORT:
	हाल MLX5_CMD_OP_DELETE_L2_TABLE_ENTRY:
	हाल MLX5_CMD_OP_DESTROY_LAG:
	हाल MLX5_CMD_OP_DESTROY_VPORT_LAG:
	हाल MLX5_CMD_OP_DESTROY_TIR:
	हाल MLX5_CMD_OP_DESTROY_SQ:
	हाल MLX5_CMD_OP_DESTROY_RQ:
	हाल MLX5_CMD_OP_DESTROY_RMP:
	हाल MLX5_CMD_OP_DESTROY_TIS:
	हाल MLX5_CMD_OP_DESTROY_RQT:
	हाल MLX5_CMD_OP_DESTROY_FLOW_TABLE:
	हाल MLX5_CMD_OP_DESTROY_FLOW_GROUP:
	हाल MLX5_CMD_OP_DELETE_FLOW_TABLE_ENTRY:
	हाल MLX5_CMD_OP_DEALLOC_FLOW_COUNTER:
	हाल MLX5_CMD_OP_2ERR_QP:
	हाल MLX5_CMD_OP_2RST_QP:
	हाल MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_MODIFY_FLOW_TABLE:
	हाल MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
	हाल MLX5_CMD_OP_SET_FLOW_TABLE_ROOT:
	हाल MLX5_CMD_OP_DEALLOC_PACKET_REFORMAT_CONTEXT:
	हाल MLX5_CMD_OP_DEALLOC_MODIFY_HEADER_CONTEXT:
	हाल MLX5_CMD_OP_FPGA_DESTROY_QP:
	हाल MLX5_CMD_OP_DESTROY_GENERAL_OBJECT:
	हाल MLX5_CMD_OP_DEALLOC_MEMIC:
	हाल MLX5_CMD_OP_PAGE_FAULT_RESUME:
	हाल MLX5_CMD_OP_QUERY_ESW_FUNCTIONS:
	हाल MLX5_CMD_OP_DEALLOC_SF:
		वापस MLX5_CMD_STAT_OK;

	हाल MLX5_CMD_OP_QUERY_HCA_CAP:
	हाल MLX5_CMD_OP_QUERY_ADAPTER:
	हाल MLX5_CMD_OP_INIT_HCA:
	हाल MLX5_CMD_OP_ENABLE_HCA:
	हाल MLX5_CMD_OP_QUERY_PAGES:
	हाल MLX5_CMD_OP_SET_HCA_CAP:
	हाल MLX5_CMD_OP_QUERY_ISSI:
	हाल MLX5_CMD_OP_SET_ISSI:
	हाल MLX5_CMD_OP_CREATE_MKEY:
	हाल MLX5_CMD_OP_QUERY_MKEY:
	हाल MLX5_CMD_OP_QUERY_SPECIAL_CONTEXTS:
	हाल MLX5_CMD_OP_CREATE_EQ:
	हाल MLX5_CMD_OP_QUERY_EQ:
	हाल MLX5_CMD_OP_GEN_EQE:
	हाल MLX5_CMD_OP_CREATE_CQ:
	हाल MLX5_CMD_OP_QUERY_CQ:
	हाल MLX5_CMD_OP_MODIFY_CQ:
	हाल MLX5_CMD_OP_CREATE_QP:
	हाल MLX5_CMD_OP_RST2INIT_QP:
	हाल MLX5_CMD_OP_INIT2RTR_QP:
	हाल MLX5_CMD_OP_RTR2RTS_QP:
	हाल MLX5_CMD_OP_RTS2RTS_QP:
	हाल MLX5_CMD_OP_SQERR2RTS_QP:
	हाल MLX5_CMD_OP_QUERY_QP:
	हाल MLX5_CMD_OP_SQD_RTS_QP:
	हाल MLX5_CMD_OP_INIT2INIT_QP:
	हाल MLX5_CMD_OP_CREATE_PSV:
	हाल MLX5_CMD_OP_CREATE_SRQ:
	हाल MLX5_CMD_OP_QUERY_SRQ:
	हाल MLX5_CMD_OP_ARM_RQ:
	हाल MLX5_CMD_OP_CREATE_XRC_SRQ:
	हाल MLX5_CMD_OP_QUERY_XRC_SRQ:
	हाल MLX5_CMD_OP_ARM_XRC_SRQ:
	हाल MLX5_CMD_OP_CREATE_XRQ:
	हाल MLX5_CMD_OP_QUERY_XRQ:
	हाल MLX5_CMD_OP_ARM_XRQ:
	हाल MLX5_CMD_OP_CREATE_DCT:
	हाल MLX5_CMD_OP_DRAIN_DCT:
	हाल MLX5_CMD_OP_QUERY_DCT:
	हाल MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION:
	हाल MLX5_CMD_OP_QUERY_VPORT_STATE:
	हाल MLX5_CMD_OP_MODIFY_VPORT_STATE:
	हाल MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_MODIFY_ESW_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_QUERY_ROCE_ADDRESS:
	हाल MLX5_CMD_OP_SET_ROCE_ADDRESS:
	हाल MLX5_CMD_OP_QUERY_HCA_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_MODIFY_HCA_VPORT_CONTEXT:
	हाल MLX5_CMD_OP_QUERY_HCA_VPORT_GID:
	हाल MLX5_CMD_OP_QUERY_HCA_VPORT_PKEY:
	हाल MLX5_CMD_OP_QUERY_VNIC_ENV:
	हाल MLX5_CMD_OP_QUERY_VPORT_COUNTER:
	हाल MLX5_CMD_OP_ALLOC_Q_COUNTER:
	हाल MLX5_CMD_OP_QUERY_Q_COUNTER:
	हाल MLX5_CMD_OP_SET_MONITOR_COUNTER:
	हाल MLX5_CMD_OP_ARM_MONITOR_COUNTER:
	हाल MLX5_CMD_OP_SET_PP_RATE_LIMIT:
	हाल MLX5_CMD_OP_QUERY_RATE_LIMIT:
	हाल MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT:
	हाल MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT:
	हाल MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT:
	हाल MLX5_CMD_OP_CREATE_QOS_PARA_VPORT:
	हाल MLX5_CMD_OP_ALLOC_PD:
	हाल MLX5_CMD_OP_ALLOC_UAR:
	हाल MLX5_CMD_OP_CONFIG_INT_MODERATION:
	हाल MLX5_CMD_OP_ACCESS_REG:
	हाल MLX5_CMD_OP_ATTACH_TO_MCG:
	हाल MLX5_CMD_OP_GET_DROPPED_PACKET_LOG:
	हाल MLX5_CMD_OP_MAD_IFC:
	हाल MLX5_CMD_OP_QUERY_MAD_DEMUX:
	हाल MLX5_CMD_OP_SET_MAD_DEMUX:
	हाल MLX5_CMD_OP_NOP:
	हाल MLX5_CMD_OP_ALLOC_XRCD:
	हाल MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN:
	हाल MLX5_CMD_OP_QUERY_CONG_STATUS:
	हाल MLX5_CMD_OP_MODIFY_CONG_STATUS:
	हाल MLX5_CMD_OP_QUERY_CONG_PARAMS:
	हाल MLX5_CMD_OP_MODIFY_CONG_PARAMS:
	हाल MLX5_CMD_OP_QUERY_CONG_STATISTICS:
	हाल MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
	हाल MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
	हाल MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY:
	हाल MLX5_CMD_OP_CREATE_LAG:
	हाल MLX5_CMD_OP_MODIFY_LAG:
	हाल MLX5_CMD_OP_QUERY_LAG:
	हाल MLX5_CMD_OP_CREATE_VPORT_LAG:
	हाल MLX5_CMD_OP_CREATE_TIR:
	हाल MLX5_CMD_OP_MODIFY_TIR:
	हाल MLX5_CMD_OP_QUERY_TIR:
	हाल MLX5_CMD_OP_CREATE_SQ:
	हाल MLX5_CMD_OP_MODIFY_SQ:
	हाल MLX5_CMD_OP_QUERY_SQ:
	हाल MLX5_CMD_OP_CREATE_RQ:
	हाल MLX5_CMD_OP_MODIFY_RQ:
	हाल MLX5_CMD_OP_QUERY_RQ:
	हाल MLX5_CMD_OP_CREATE_RMP:
	हाल MLX5_CMD_OP_MODIFY_RMP:
	हाल MLX5_CMD_OP_QUERY_RMP:
	हाल MLX5_CMD_OP_CREATE_TIS:
	हाल MLX5_CMD_OP_MODIFY_TIS:
	हाल MLX5_CMD_OP_QUERY_TIS:
	हाल MLX5_CMD_OP_CREATE_RQT:
	हाल MLX5_CMD_OP_MODIFY_RQT:
	हाल MLX5_CMD_OP_QUERY_RQT:

	हाल MLX5_CMD_OP_CREATE_FLOW_TABLE:
	हाल MLX5_CMD_OP_QUERY_FLOW_TABLE:
	हाल MLX5_CMD_OP_CREATE_FLOW_GROUP:
	हाल MLX5_CMD_OP_QUERY_FLOW_GROUP:
	हाल MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY:
	हाल MLX5_CMD_OP_ALLOC_FLOW_COUNTER:
	हाल MLX5_CMD_OP_QUERY_FLOW_COUNTER:
	हाल MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT:
	हाल MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT:
	हाल MLX5_CMD_OP_FPGA_CREATE_QP:
	हाल MLX5_CMD_OP_FPGA_MODIFY_QP:
	हाल MLX5_CMD_OP_FPGA_QUERY_QP:
	हाल MLX5_CMD_OP_FPGA_QUERY_QP_COUNTERS:
	हाल MLX5_CMD_OP_CREATE_GENERAL_OBJECT:
	हाल MLX5_CMD_OP_MODIFY_GENERAL_OBJECT:
	हाल MLX5_CMD_OP_QUERY_GENERAL_OBJECT:
	हाल MLX5_CMD_OP_CREATE_UCTX:
	हाल MLX5_CMD_OP_DESTROY_UCTX:
	हाल MLX5_CMD_OP_CREATE_UMEM:
	हाल MLX5_CMD_OP_DESTROY_UMEM:
	हाल MLX5_CMD_OP_ALLOC_MEMIC:
	हाल MLX5_CMD_OP_MODIFY_XRQ:
	हाल MLX5_CMD_OP_RELEASE_XRQ_ERROR:
	हाल MLX5_CMD_OP_QUERY_VHCA_STATE:
	हाल MLX5_CMD_OP_MODIFY_VHCA_STATE:
	हाल MLX5_CMD_OP_ALLOC_SF:
		*status = MLX5_DRIVER_STATUS_ABORTED;
		*synd = MLX5_DRIVER_SYND;
		वापस -EIO;
	शेष:
		mlx5_core_err(dev, "Unknown FW command (%d)\n", op);
		वापस -EINVAL;
	पूर्ण
पूर्ण

स्थिर अक्षर *mlx5_command_str(पूर्णांक command)
अणु
#घोषणा MLX5_COMMAND_STR_CASE(__cmd) हाल MLX5_CMD_OP_ ## __cmd: वापस #__cmd

	चयन (command) अणु
	MLX5_COMMAND_STR_CASE(QUERY_HCA_CAP);
	MLX5_COMMAND_STR_CASE(QUERY_ADAPTER);
	MLX5_COMMAND_STR_CASE(INIT_HCA);
	MLX5_COMMAND_STR_CASE(TEARDOWN_HCA);
	MLX5_COMMAND_STR_CASE(ENABLE_HCA);
	MLX5_COMMAND_STR_CASE(DISABLE_HCA);
	MLX5_COMMAND_STR_CASE(QUERY_PAGES);
	MLX5_COMMAND_STR_CASE(MANAGE_PAGES);
	MLX5_COMMAND_STR_CASE(SET_HCA_CAP);
	MLX5_COMMAND_STR_CASE(QUERY_ISSI);
	MLX5_COMMAND_STR_CASE(SET_ISSI);
	MLX5_COMMAND_STR_CASE(SET_DRIVER_VERSION);
	MLX5_COMMAND_STR_CASE(CREATE_MKEY);
	MLX5_COMMAND_STR_CASE(QUERY_MKEY);
	MLX5_COMMAND_STR_CASE(DESTROY_MKEY);
	MLX5_COMMAND_STR_CASE(QUERY_SPECIAL_CONTEXTS);
	MLX5_COMMAND_STR_CASE(PAGE_FAULT_RESUME);
	MLX5_COMMAND_STR_CASE(CREATE_EQ);
	MLX5_COMMAND_STR_CASE(DESTROY_EQ);
	MLX5_COMMAND_STR_CASE(QUERY_EQ);
	MLX5_COMMAND_STR_CASE(GEN_EQE);
	MLX5_COMMAND_STR_CASE(CREATE_CQ);
	MLX5_COMMAND_STR_CASE(DESTROY_CQ);
	MLX5_COMMAND_STR_CASE(QUERY_CQ);
	MLX5_COMMAND_STR_CASE(MODIFY_CQ);
	MLX5_COMMAND_STR_CASE(CREATE_QP);
	MLX5_COMMAND_STR_CASE(DESTROY_QP);
	MLX5_COMMAND_STR_CASE(RST2INIT_QP);
	MLX5_COMMAND_STR_CASE(INIT2RTR_QP);
	MLX5_COMMAND_STR_CASE(RTR2RTS_QP);
	MLX5_COMMAND_STR_CASE(RTS2RTS_QP);
	MLX5_COMMAND_STR_CASE(SQERR2RTS_QP);
	MLX5_COMMAND_STR_CASE(2ERR_QP);
	MLX5_COMMAND_STR_CASE(2RST_QP);
	MLX5_COMMAND_STR_CASE(QUERY_QP);
	MLX5_COMMAND_STR_CASE(SQD_RTS_QP);
	MLX5_COMMAND_STR_CASE(INIT2INIT_QP);
	MLX5_COMMAND_STR_CASE(CREATE_PSV);
	MLX5_COMMAND_STR_CASE(DESTROY_PSV);
	MLX5_COMMAND_STR_CASE(CREATE_SRQ);
	MLX5_COMMAND_STR_CASE(DESTROY_SRQ);
	MLX5_COMMAND_STR_CASE(QUERY_SRQ);
	MLX5_COMMAND_STR_CASE(ARM_RQ);
	MLX5_COMMAND_STR_CASE(CREATE_XRC_SRQ);
	MLX5_COMMAND_STR_CASE(DESTROY_XRC_SRQ);
	MLX5_COMMAND_STR_CASE(QUERY_XRC_SRQ);
	MLX5_COMMAND_STR_CASE(ARM_XRC_SRQ);
	MLX5_COMMAND_STR_CASE(CREATE_DCT);
	MLX5_COMMAND_STR_CASE(DESTROY_DCT);
	MLX5_COMMAND_STR_CASE(DRAIN_DCT);
	MLX5_COMMAND_STR_CASE(QUERY_DCT);
	MLX5_COMMAND_STR_CASE(ARM_DCT_FOR_KEY_VIOLATION);
	MLX5_COMMAND_STR_CASE(QUERY_VPORT_STATE);
	MLX5_COMMAND_STR_CASE(MODIFY_VPORT_STATE);
	MLX5_COMMAND_STR_CASE(QUERY_ESW_VPORT_CONTEXT);
	MLX5_COMMAND_STR_CASE(MODIFY_ESW_VPORT_CONTEXT);
	MLX5_COMMAND_STR_CASE(QUERY_NIC_VPORT_CONTEXT);
	MLX5_COMMAND_STR_CASE(MODIFY_NIC_VPORT_CONTEXT);
	MLX5_COMMAND_STR_CASE(QUERY_ROCE_ADDRESS);
	MLX5_COMMAND_STR_CASE(SET_ROCE_ADDRESS);
	MLX5_COMMAND_STR_CASE(QUERY_HCA_VPORT_CONTEXT);
	MLX5_COMMAND_STR_CASE(MODIFY_HCA_VPORT_CONTEXT);
	MLX5_COMMAND_STR_CASE(QUERY_HCA_VPORT_GID);
	MLX5_COMMAND_STR_CASE(QUERY_HCA_VPORT_PKEY);
	MLX5_COMMAND_STR_CASE(QUERY_VNIC_ENV);
	MLX5_COMMAND_STR_CASE(QUERY_VPORT_COUNTER);
	MLX5_COMMAND_STR_CASE(ALLOC_Q_COUNTER);
	MLX5_COMMAND_STR_CASE(DEALLOC_Q_COUNTER);
	MLX5_COMMAND_STR_CASE(QUERY_Q_COUNTER);
	MLX5_COMMAND_STR_CASE(SET_MONITOR_COUNTER);
	MLX5_COMMAND_STR_CASE(ARM_MONITOR_COUNTER);
	MLX5_COMMAND_STR_CASE(SET_PP_RATE_LIMIT);
	MLX5_COMMAND_STR_CASE(QUERY_RATE_LIMIT);
	MLX5_COMMAND_STR_CASE(CREATE_SCHEDULING_ELEMENT);
	MLX5_COMMAND_STR_CASE(DESTROY_SCHEDULING_ELEMENT);
	MLX5_COMMAND_STR_CASE(QUERY_SCHEDULING_ELEMENT);
	MLX5_COMMAND_STR_CASE(MODIFY_SCHEDULING_ELEMENT);
	MLX5_COMMAND_STR_CASE(CREATE_QOS_PARA_VPORT);
	MLX5_COMMAND_STR_CASE(DESTROY_QOS_PARA_VPORT);
	MLX5_COMMAND_STR_CASE(ALLOC_PD);
	MLX5_COMMAND_STR_CASE(DEALLOC_PD);
	MLX5_COMMAND_STR_CASE(ALLOC_UAR);
	MLX5_COMMAND_STR_CASE(DEALLOC_UAR);
	MLX5_COMMAND_STR_CASE(CONFIG_INT_MODERATION);
	MLX5_COMMAND_STR_CASE(ACCESS_REG);
	MLX5_COMMAND_STR_CASE(ATTACH_TO_MCG);
	MLX5_COMMAND_STR_CASE(DETACH_FROM_MCG);
	MLX5_COMMAND_STR_CASE(GET_DROPPED_PACKET_LOG);
	MLX5_COMMAND_STR_CASE(MAD_IFC);
	MLX5_COMMAND_STR_CASE(QUERY_MAD_DEMUX);
	MLX5_COMMAND_STR_CASE(SET_MAD_DEMUX);
	MLX5_COMMAND_STR_CASE(NOP);
	MLX5_COMMAND_STR_CASE(ALLOC_XRCD);
	MLX5_COMMAND_STR_CASE(DEALLOC_XRCD);
	MLX5_COMMAND_STR_CASE(ALLOC_TRANSPORT_DOMAIN);
	MLX5_COMMAND_STR_CASE(DEALLOC_TRANSPORT_DOMAIN);
	MLX5_COMMAND_STR_CASE(QUERY_CONG_STATUS);
	MLX5_COMMAND_STR_CASE(MODIFY_CONG_STATUS);
	MLX5_COMMAND_STR_CASE(QUERY_CONG_PARAMS);
	MLX5_COMMAND_STR_CASE(MODIFY_CONG_PARAMS);
	MLX5_COMMAND_STR_CASE(QUERY_CONG_STATISTICS);
	MLX5_COMMAND_STR_CASE(ADD_VXLAN_UDP_DPORT);
	MLX5_COMMAND_STR_CASE(DELETE_VXLAN_UDP_DPORT);
	MLX5_COMMAND_STR_CASE(SET_L2_TABLE_ENTRY);
	MLX5_COMMAND_STR_CASE(QUERY_L2_TABLE_ENTRY);
	MLX5_COMMAND_STR_CASE(DELETE_L2_TABLE_ENTRY);
	MLX5_COMMAND_STR_CASE(SET_WOL_ROL);
	MLX5_COMMAND_STR_CASE(QUERY_WOL_ROL);
	MLX5_COMMAND_STR_CASE(CREATE_LAG);
	MLX5_COMMAND_STR_CASE(MODIFY_LAG);
	MLX5_COMMAND_STR_CASE(QUERY_LAG);
	MLX5_COMMAND_STR_CASE(DESTROY_LAG);
	MLX5_COMMAND_STR_CASE(CREATE_VPORT_LAG);
	MLX5_COMMAND_STR_CASE(DESTROY_VPORT_LAG);
	MLX5_COMMAND_STR_CASE(CREATE_TIR);
	MLX5_COMMAND_STR_CASE(MODIFY_TIR);
	MLX5_COMMAND_STR_CASE(DESTROY_TIR);
	MLX5_COMMAND_STR_CASE(QUERY_TIR);
	MLX5_COMMAND_STR_CASE(CREATE_SQ);
	MLX5_COMMAND_STR_CASE(MODIFY_SQ);
	MLX5_COMMAND_STR_CASE(DESTROY_SQ);
	MLX5_COMMAND_STR_CASE(QUERY_SQ);
	MLX5_COMMAND_STR_CASE(CREATE_RQ);
	MLX5_COMMAND_STR_CASE(MODIFY_RQ);
	MLX5_COMMAND_STR_CASE(DESTROY_RQ);
	MLX5_COMMAND_STR_CASE(QUERY_RQ);
	MLX5_COMMAND_STR_CASE(CREATE_RMP);
	MLX5_COMMAND_STR_CASE(MODIFY_RMP);
	MLX5_COMMAND_STR_CASE(DESTROY_RMP);
	MLX5_COMMAND_STR_CASE(QUERY_RMP);
	MLX5_COMMAND_STR_CASE(CREATE_TIS);
	MLX5_COMMAND_STR_CASE(MODIFY_TIS);
	MLX5_COMMAND_STR_CASE(DESTROY_TIS);
	MLX5_COMMAND_STR_CASE(QUERY_TIS);
	MLX5_COMMAND_STR_CASE(CREATE_RQT);
	MLX5_COMMAND_STR_CASE(MODIFY_RQT);
	MLX5_COMMAND_STR_CASE(DESTROY_RQT);
	MLX5_COMMAND_STR_CASE(QUERY_RQT);
	MLX5_COMMAND_STR_CASE(SET_FLOW_TABLE_ROOT);
	MLX5_COMMAND_STR_CASE(CREATE_FLOW_TABLE);
	MLX5_COMMAND_STR_CASE(DESTROY_FLOW_TABLE);
	MLX5_COMMAND_STR_CASE(QUERY_FLOW_TABLE);
	MLX5_COMMAND_STR_CASE(CREATE_FLOW_GROUP);
	MLX5_COMMAND_STR_CASE(DESTROY_FLOW_GROUP);
	MLX5_COMMAND_STR_CASE(QUERY_FLOW_GROUP);
	MLX5_COMMAND_STR_CASE(SET_FLOW_TABLE_ENTRY);
	MLX5_COMMAND_STR_CASE(QUERY_FLOW_TABLE_ENTRY);
	MLX5_COMMAND_STR_CASE(DELETE_FLOW_TABLE_ENTRY);
	MLX5_COMMAND_STR_CASE(ALLOC_FLOW_COUNTER);
	MLX5_COMMAND_STR_CASE(DEALLOC_FLOW_COUNTER);
	MLX5_COMMAND_STR_CASE(QUERY_FLOW_COUNTER);
	MLX5_COMMAND_STR_CASE(MODIFY_FLOW_TABLE);
	MLX5_COMMAND_STR_CASE(ALLOC_PACKET_REFORMAT_CONTEXT);
	MLX5_COMMAND_STR_CASE(DEALLOC_PACKET_REFORMAT_CONTEXT);
	MLX5_COMMAND_STR_CASE(ALLOC_MODIFY_HEADER_CONTEXT);
	MLX5_COMMAND_STR_CASE(DEALLOC_MODIFY_HEADER_CONTEXT);
	MLX5_COMMAND_STR_CASE(FPGA_CREATE_QP);
	MLX5_COMMAND_STR_CASE(FPGA_MODIFY_QP);
	MLX5_COMMAND_STR_CASE(FPGA_QUERY_QP);
	MLX5_COMMAND_STR_CASE(FPGA_QUERY_QP_COUNTERS);
	MLX5_COMMAND_STR_CASE(FPGA_DESTROY_QP);
	MLX5_COMMAND_STR_CASE(CREATE_XRQ);
	MLX5_COMMAND_STR_CASE(DESTROY_XRQ);
	MLX5_COMMAND_STR_CASE(QUERY_XRQ);
	MLX5_COMMAND_STR_CASE(ARM_XRQ);
	MLX5_COMMAND_STR_CASE(CREATE_GENERAL_OBJECT);
	MLX5_COMMAND_STR_CASE(DESTROY_GENERAL_OBJECT);
	MLX5_COMMAND_STR_CASE(MODIFY_GENERAL_OBJECT);
	MLX5_COMMAND_STR_CASE(QUERY_GENERAL_OBJECT);
	MLX5_COMMAND_STR_CASE(QUERY_MODIFY_HEADER_CONTEXT);
	MLX5_COMMAND_STR_CASE(ALLOC_MEMIC);
	MLX5_COMMAND_STR_CASE(DEALLOC_MEMIC);
	MLX5_COMMAND_STR_CASE(QUERY_ESW_FUNCTIONS);
	MLX5_COMMAND_STR_CASE(CREATE_UCTX);
	MLX5_COMMAND_STR_CASE(DESTROY_UCTX);
	MLX5_COMMAND_STR_CASE(CREATE_UMEM);
	MLX5_COMMAND_STR_CASE(DESTROY_UMEM);
	MLX5_COMMAND_STR_CASE(RELEASE_XRQ_ERROR);
	MLX5_COMMAND_STR_CASE(MODIFY_XRQ);
	MLX5_COMMAND_STR_CASE(QUERY_VHCA_STATE);
	MLX5_COMMAND_STR_CASE(MODIFY_VHCA_STATE);
	MLX5_COMMAND_STR_CASE(ALLOC_SF);
	MLX5_COMMAND_STR_CASE(DEALLOC_SF);
	शेष: वापस "unknown command opcode";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *cmd_status_str(u8 status)
अणु
	चयन (status) अणु
	हाल MLX5_CMD_STAT_OK:
		वापस "OK";
	हाल MLX5_CMD_STAT_INT_ERR:
		वापस "internal error";
	हाल MLX5_CMD_STAT_BAD_OP_ERR:
		वापस "bad operation";
	हाल MLX5_CMD_STAT_BAD_PARAM_ERR:
		वापस "bad parameter";
	हाल MLX5_CMD_STAT_BAD_SYS_STATE_ERR:
		वापस "bad system state";
	हाल MLX5_CMD_STAT_BAD_RES_ERR:
		वापस "bad resource";
	हाल MLX5_CMD_STAT_RES_BUSY:
		वापस "resource busy";
	हाल MLX5_CMD_STAT_LIM_ERR:
		वापस "limits exceeded";
	हाल MLX5_CMD_STAT_BAD_RES_STATE_ERR:
		वापस "bad resource state";
	हाल MLX5_CMD_STAT_IX_ERR:
		वापस "bad index";
	हाल MLX5_CMD_STAT_NO_RES_ERR:
		वापस "no resources";
	हाल MLX5_CMD_STAT_BAD_INP_LEN_ERR:
		वापस "bad input length";
	हाल MLX5_CMD_STAT_BAD_OUTP_LEN_ERR:
		वापस "bad output length";
	हाल MLX5_CMD_STAT_BAD_QP_STATE_ERR:
		वापस "bad QP state";
	हाल MLX5_CMD_STAT_BAD_PKT_ERR:
		वापस "bad packet (discarded)";
	हाल MLX5_CMD_STAT_BAD_SIZE_OUTS_CQES_ERR:
		वापस "bad size too many outstanding CQEs";
	शेष:
		वापस "unknown status";
	पूर्ण
पूर्ण

अटल पूर्णांक cmd_status_to_err(u8 status)
अणु
	चयन (status) अणु
	हाल MLX5_CMD_STAT_OK:				वापस 0;
	हाल MLX5_CMD_STAT_INT_ERR:			वापस -EIO;
	हाल MLX5_CMD_STAT_BAD_OP_ERR:			वापस -EINVAL;
	हाल MLX5_CMD_STAT_BAD_PARAM_ERR:		वापस -EINVAL;
	हाल MLX5_CMD_STAT_BAD_SYS_STATE_ERR:		वापस -EIO;
	हाल MLX5_CMD_STAT_BAD_RES_ERR:			वापस -EINVAL;
	हाल MLX5_CMD_STAT_RES_BUSY:			वापस -EBUSY;
	हाल MLX5_CMD_STAT_LIM_ERR:			वापस -ENOMEM;
	हाल MLX5_CMD_STAT_BAD_RES_STATE_ERR:		वापस -EINVAL;
	हाल MLX5_CMD_STAT_IX_ERR:			वापस -EINVAL;
	हाल MLX5_CMD_STAT_NO_RES_ERR:			वापस -EAGAIN;
	हाल MLX5_CMD_STAT_BAD_INP_LEN_ERR:		वापस -EIO;
	हाल MLX5_CMD_STAT_BAD_OUTP_LEN_ERR:		वापस -EIO;
	हाल MLX5_CMD_STAT_BAD_QP_STATE_ERR:		वापस -EINVAL;
	हाल MLX5_CMD_STAT_BAD_PKT_ERR:			वापस -EINVAL;
	हाल MLX5_CMD_STAT_BAD_SIZE_OUTS_CQES_ERR:	वापस -EINVAL;
	शेष:					वापस -EIO;
	पूर्ण
पूर्ण

काष्ठा mlx5_अगरc_mbox_out_bits अणु
	u8         status[0x8];
	u8         reserved_at_8[0x18];

	u8         syndrome[0x20];

	u8         reserved_at_40[0x40];
पूर्ण;

काष्ठा mlx5_अगरc_mbox_in_bits अणु
	u8         opcode[0x10];
	u8         uid[0x10];

	u8         reserved_at_20[0x10];
	u8         op_mod[0x10];

	u8         reserved_at_40[0x40];
पूर्ण;

व्योम mlx5_cmd_mbox_status(व्योम *out, u8 *status, u32 *syndrome)
अणु
	*status = MLX5_GET(mbox_out, out, status);
	*syndrome = MLX5_GET(mbox_out, out, syndrome);
पूर्ण

अटल पूर्णांक mlx5_cmd_check(काष्ठा mlx5_core_dev *dev, व्योम *in, व्योम *out)
अणु
	u32 syndrome;
	u8  status;
	u16 opcode;
	u16 op_mod;
	u16 uid;

	mlx5_cmd_mbox_status(out, &status, &syndrome);
	अगर (!status)
		वापस 0;

	opcode = MLX5_GET(mbox_in, in, opcode);
	op_mod = MLX5_GET(mbox_in, in, op_mod);
	uid    = MLX5_GET(mbox_in, in, uid);

	अगर (!uid && opcode != MLX5_CMD_OP_DESTROY_MKEY)
		mlx5_core_err_rl(dev,
			"%s(0x%x) op_mod(0x%x) failed, status %s(0x%x), syndrome (0x%x)\n",
			mlx5_command_str(opcode), opcode, op_mod,
			cmd_status_str(status), status, syndrome);
	अन्यथा
		mlx5_core_dbg(dev,
		      "%s(0x%x) op_mod(0x%x) failed, status %s(0x%x), syndrome (0x%x)\n",
		      mlx5_command_str(opcode),
		      opcode, op_mod,
		      cmd_status_str(status),
		      status,
		      syndrome);

	वापस cmd_status_to_err(status);
पूर्ण

अटल व्योम dump_command(काष्ठा mlx5_core_dev *dev,
			 काष्ठा mlx5_cmd_work_ent *ent, पूर्णांक input)
अणु
	काष्ठा mlx5_cmd_msg *msg = input ? ent->in : ent->out;
	u16 op = MLX5_GET(mbox_in, ent->lay->in, opcode);
	काष्ठा mlx5_cmd_mailbox *next = msg->next;
	पूर्णांक n = mlx5_calc_cmd_blocks(msg);
	पूर्णांक data_only;
	u32 offset = 0;
	पूर्णांक dump_len;
	पूर्णांक i;

	mlx5_core_dbg(dev, "cmd[%d]: start dump\n", ent->idx);
	data_only = !!(mlx5_core_debug_mask & (1 << MLX5_CMD_DATA));

	अगर (data_only)
		mlx5_core_dbg_mask(dev, 1 << MLX5_CMD_DATA,
				   "cmd[%d]: dump command data %s(0x%x) %s\n",
				   ent->idx, mlx5_command_str(op), op,
				   input ? "INPUT" : "OUTPUT");
	अन्यथा
		mlx5_core_dbg(dev, "cmd[%d]: dump command %s(0x%x) %s\n",
			      ent->idx, mlx5_command_str(op), op,
			      input ? "INPUT" : "OUTPUT");

	अगर (data_only) अणु
		अगर (input) अणु
			dump_buf(ent->lay->in, माप(ent->lay->in), 1, offset, ent->idx);
			offset += माप(ent->lay->in);
		पूर्ण अन्यथा अणु
			dump_buf(ent->lay->out, माप(ent->lay->out), 1, offset, ent->idx);
			offset += माप(ent->lay->out);
		पूर्ण
	पूर्ण अन्यथा अणु
		dump_buf(ent->lay, माप(*ent->lay), 0, offset, ent->idx);
		offset += माप(*ent->lay);
	पूर्ण

	क्रम (i = 0; i < n && next; i++)  अणु
		अगर (data_only) अणु
			dump_len = min_t(पूर्णांक, MLX5_CMD_DATA_BLOCK_SIZE, msg->len - offset);
			dump_buf(next->buf, dump_len, 1, offset, ent->idx);
			offset += MLX5_CMD_DATA_BLOCK_SIZE;
		पूर्ण अन्यथा अणु
			mlx5_core_dbg(dev, "cmd[%d]: command block:\n", ent->idx);
			dump_buf(next->buf, माप(काष्ठा mlx5_cmd_prot_block), 0, offset,
				 ent->idx);
			offset += माप(काष्ठा mlx5_cmd_prot_block);
		पूर्ण
		next = next->next;
	पूर्ण

	अगर (data_only)
		pr_debug("\n");

	mlx5_core_dbg(dev, "cmd[%d]: end dump\n", ent->idx);
पूर्ण

अटल u16 msg_to_opcode(काष्ठा mlx5_cmd_msg *in)
अणु
	वापस MLX5_GET(mbox_in, in->first.data, opcode);
पूर्ण

अटल व्योम mlx5_cmd_comp_handler(काष्ठा mlx5_core_dev *dev, u64 vec, bool क्रमced);

अटल व्योम cb_समयout_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = container_of(work, काष्ठा delayed_work,
						  work);
	काष्ठा mlx5_cmd_work_ent *ent = container_of(dwork,
						     काष्ठा mlx5_cmd_work_ent,
						     cb_समयout_work);
	काष्ठा mlx5_core_dev *dev = container_of(ent->cmd, काष्ठा mlx5_core_dev,
						 cmd);

	mlx5_cmd_eq_recover(dev);

	/* Maybe got handled by eq recover ? */
	अगर (!test_bit(MLX5_CMD_ENT_STATE_PENDING_COMP, &ent->state)) अणु
		mlx5_core_warn(dev, "cmd[%d]: %s(0x%x) Async, recovered after timeout\n", ent->idx,
			       mlx5_command_str(msg_to_opcode(ent->in)), msg_to_opcode(ent->in));
		जाओ out; /* phew, alपढ़ोy handled */
	पूर्ण

	ent->ret = -ETIMEDOUT;
	mlx5_core_warn(dev, "cmd[%d]: %s(0x%x) Async, timeout. Will cause a leak of a command resource\n",
		       ent->idx, mlx5_command_str(msg_to_opcode(ent->in)), msg_to_opcode(ent->in));
	mlx5_cmd_comp_handler(dev, 1UL << ent->idx, true);

out:
	cmd_ent_put(ent); /* क्रम the cmd_ent_get() took on schedule delayed work */
पूर्ण

अटल व्योम मुक्त_msg(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_cmd_msg *msg);
अटल व्योम mlx5_मुक्त_cmd_msg(काष्ठा mlx5_core_dev *dev,
			      काष्ठा mlx5_cmd_msg *msg);

अटल bool opcode_allowed(काष्ठा mlx5_cmd *cmd, u16 opcode)
अणु
	अगर (cmd->allowed_opcode == CMD_ALLOWED_OPCODE_ALL)
		वापस true;

	वापस cmd->allowed_opcode == opcode;
पूर्ण

अटल पूर्णांक cmd_alloc_index_retry(काष्ठा mlx5_cmd *cmd)
अणु
	अचिन्हित दीर्घ alloc_end = jअगरfies + msecs_to_jअगरfies(1000);
	पूर्णांक idx;

retry:
	idx = cmd_alloc_index(cmd);
	अगर (idx < 0 && समय_beक्रमe(jअगरfies, alloc_end)) अणु
		/* Index allocation can fail on heavy load of commands. This is a temporary
		 * situation as the current command alपढ़ोy holds the semaphore, meaning that
		 * another command completion is being handled and it is expected to release
		 * the entry index soon.
		 */
		cpu_relax();
		जाओ retry;
	पूर्ण
	वापस idx;
पूर्ण

bool mlx5_cmd_is_करोwn(काष्ठा mlx5_core_dev *dev)
अणु
	वापस pci_channel_offline(dev->pdev) ||
	       dev->cmd.state != MLX5_CMDIF_STATE_UP ||
	       dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR;
पूर्ण

अटल व्योम cmd_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_cmd_work_ent *ent = container_of(work, काष्ठा mlx5_cmd_work_ent, work);
	काष्ठा mlx5_cmd *cmd = ent->cmd;
	काष्ठा mlx5_core_dev *dev = container_of(cmd, काष्ठा mlx5_core_dev, cmd);
	अचिन्हित दीर्घ cb_समयout = msecs_to_jअगरfies(MLX5_CMD_TIMEOUT_MSEC);
	काष्ठा mlx5_cmd_layout *lay;
	काष्ठा semaphore *sem;
	अचिन्हित दीर्घ flags;
	bool poll_cmd = ent->polling;
	पूर्णांक alloc_ret;
	पूर्णांक cmd_mode;

	complete(&ent->handling);
	sem = ent->page_queue ? &cmd->pages_sem : &cmd->sem;
	करोwn(sem);
	अगर (!ent->page_queue) अणु
		alloc_ret = cmd_alloc_index_retry(cmd);
		अगर (alloc_ret < 0) अणु
			mlx5_core_err_rl(dev, "failed to allocate command entry\n");
			अगर (ent->callback) अणु
				ent->callback(-EAGAIN, ent->context);
				mlx5_मुक्त_cmd_msg(dev, ent->out);
				मुक्त_msg(dev, ent->in);
				cmd_ent_put(ent);
			पूर्ण अन्यथा अणु
				ent->ret = -EAGAIN;
				complete(&ent->करोne);
			पूर्ण
			up(sem);
			वापस;
		पूर्ण
		ent->idx = alloc_ret;
	पूर्ण अन्यथा अणु
		ent->idx = cmd->max_reg_cmds;
		spin_lock_irqsave(&cmd->alloc_lock, flags);
		clear_bit(ent->idx, &cmd->biपंचांगask);
		spin_unlock_irqrestore(&cmd->alloc_lock, flags);
	पूर्ण

	cmd->ent_arr[ent->idx] = ent;
	lay = get_inst(cmd, ent->idx);
	ent->lay = lay;
	स_रखो(lay, 0, माप(*lay));
	स_नकल(lay->in, ent->in->first.data, माप(lay->in));
	ent->op = be32_to_cpu(lay->in[0]) >> 16;
	अगर (ent->in->next)
		lay->in_ptr = cpu_to_be64(ent->in->next->dma);
	lay->inlen = cpu_to_be32(ent->in->len);
	अगर (ent->out->next)
		lay->out_ptr = cpu_to_be64(ent->out->next->dma);
	lay->outlen = cpu_to_be32(ent->out->len);
	lay->type = MLX5_PCI_CMD_XPORT;
	lay->token = ent->token;
	lay->status_own = CMD_OWNER_HW;
	set_signature(ent, !cmd->checksum_disabled);
	dump_command(dev, ent, 1);
	ent->ts1 = kसमय_get_ns();
	cmd_mode = cmd->mode;

	अगर (ent->callback && schedule_delayed_work(&ent->cb_समयout_work, cb_समयout))
		cmd_ent_get(ent);
	set_bit(MLX5_CMD_ENT_STATE_PENDING_COMP, &ent->state);

	/* Skip sending command to fw अगर पूर्णांकernal error */
	अगर (mlx5_cmd_is_करोwn(dev) || !opcode_allowed(&dev->cmd, ent->op)) अणु
		u8 status = 0;
		u32 drv_synd;

		ent->ret = mlx5_पूर्णांकernal_err_ret_value(dev, msg_to_opcode(ent->in), &drv_synd, &status);
		MLX5_SET(mbox_out, ent->out, status, status);
		MLX5_SET(mbox_out, ent->out, syndrome, drv_synd);

		mlx5_cmd_comp_handler(dev, 1UL << ent->idx, true);
		वापस;
	पूर्ण

	cmd_ent_get(ent); /* क्रम the _real_ FW event on completion */
	/* ring करोorbell after the descriptor is valid */
	mlx5_core_dbg(dev, "writing 0x%x to command doorbell\n", 1 << ent->idx);
	wmb();
	ioग_लिखो32be(1 << ent->idx, &dev->iseg->cmd_dbell);
	/* अगर not in polling करोn't use ent after this poपूर्णांक */
	अगर (cmd_mode == CMD_MODE_POLLING || poll_cmd) अणु
		poll_समयout(ent);
		/* make sure we पढ़ो the descriptor after ownership is SW */
		rmb();
		mlx5_cmd_comp_handler(dev, 1UL << ent->idx, (ent->ret == -ETIMEDOUT));
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *deliv_status_to_str(u8 status)
अणु
	चयन (status) अणु
	हाल MLX5_CMD_DELIVERY_STAT_OK:
		वापस "no errors";
	हाल MLX5_CMD_DELIVERY_STAT_SIGNAT_ERR:
		वापस "signature error";
	हाल MLX5_CMD_DELIVERY_STAT_TOK_ERR:
		वापस "token error";
	हाल MLX5_CMD_DELIVERY_STAT_BAD_BLK_NUM_ERR:
		वापस "bad block number";
	हाल MLX5_CMD_DELIVERY_STAT_OUT_PTR_ALIGN_ERR:
		वापस "output pointer not aligned to block size";
	हाल MLX5_CMD_DELIVERY_STAT_IN_PTR_ALIGN_ERR:
		वापस "input pointer not aligned to block size";
	हाल MLX5_CMD_DELIVERY_STAT_FW_ERR:
		वापस "firmware internal error";
	हाल MLX5_CMD_DELIVERY_STAT_IN_LENGTH_ERR:
		वापस "command input length error";
	हाल MLX5_CMD_DELIVERY_STAT_OUT_LENGTH_ERR:
		वापस "command output length error";
	हाल MLX5_CMD_DELIVERY_STAT_RES_FLD_NOT_CLR_ERR:
		वापस "reserved fields not cleared";
	हाल MLX5_CMD_DELIVERY_STAT_CMD_DESCR_ERR:
		वापस "bad command descriptor type";
	शेष:
		वापस "unknown status code";
	पूर्ण
पूर्ण

क्रमागत अणु
	MLX5_CMD_TIMEOUT_RECOVER_MSEC   = 5 * 1000,
पूर्ण;

अटल व्योम रुको_func_handle_exec_समयout(काष्ठा mlx5_core_dev *dev,
					  काष्ठा mlx5_cmd_work_ent *ent)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(MLX5_CMD_TIMEOUT_RECOVER_MSEC);

	mlx5_cmd_eq_recover(dev);

	/* Re-रुको on the ent->करोne after executing the recovery flow. If the
	 * recovery flow (or any other recovery flow running simultaneously)
	 * has recovered an EQE, it should cause the entry to be completed by
	 * the command पूर्णांकerface.
	 */
	अगर (रुको_क्रम_completion_समयout(&ent->करोne, समयout)) अणु
		mlx5_core_warn(dev, "cmd[%d]: %s(0x%x) recovered after timeout\n", ent->idx,
			       mlx5_command_str(msg_to_opcode(ent->in)), msg_to_opcode(ent->in));
		वापस;
	पूर्ण

	mlx5_core_warn(dev, "cmd[%d]: %s(0x%x) No done completion\n", ent->idx,
		       mlx5_command_str(msg_to_opcode(ent->in)), msg_to_opcode(ent->in));

	ent->ret = -ETIMEDOUT;
	mlx5_cmd_comp_handler(dev, 1UL << ent->idx, true);
पूर्ण

अटल पूर्णांक रुको_func(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_cmd_work_ent *ent)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(MLX5_CMD_TIMEOUT_MSEC);
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	पूर्णांक err;

	अगर (!रुको_क्रम_completion_समयout(&ent->handling, समयout) &&
	    cancel_work_sync(&ent->work)) अणु
		ent->ret = -ECANCELED;
		जाओ out_err;
	पूर्ण
	अगर (cmd->mode == CMD_MODE_POLLING || ent->polling)
		रुको_क्रम_completion(&ent->करोne);
	अन्यथा अगर (!रुको_क्रम_completion_समयout(&ent->करोne, समयout))
		रुको_func_handle_exec_समयout(dev, ent);

out_err:
	err = ent->ret;

	अगर (err == -ETIMEDOUT) अणु
		mlx5_core_warn(dev, "%s(0x%x) timeout. Will cause a leak of a command resource\n",
			       mlx5_command_str(msg_to_opcode(ent->in)),
			       msg_to_opcode(ent->in));
	पूर्ण अन्यथा अगर (err == -ECANCELED) अणु
		mlx5_core_warn(dev, "%s(0x%x) canceled on out of queue timeout.\n",
			       mlx5_command_str(msg_to_opcode(ent->in)),
			       msg_to_opcode(ent->in));
	पूर्ण
	mlx5_core_dbg(dev, "err %d, delivery status %s(%d)\n",
		      err, deliv_status_to_str(ent->status), ent->status);

	वापस err;
पूर्ण

/*  Notes:
 *    1. Callback functions may not sleep
 *    2. page queue commands करो not support asynchrous completion
 */
अटल पूर्णांक mlx5_cmd_invoke(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_cmd_msg *in,
			   काष्ठा mlx5_cmd_msg *out, व्योम *uout, पूर्णांक uout_size,
			   mlx5_cmd_cbk_t callback,
			   व्योम *context, पूर्णांक page_queue, u8 *status,
			   u8 token, bool क्रमce_polling)
अणु
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	काष्ठा mlx5_cmd_work_ent *ent;
	काष्ठा mlx5_cmd_stats *stats;
	पूर्णांक err = 0;
	s64 ds;
	u16 op;

	अगर (callback && page_queue)
		वापस -EINVAL;

	ent = cmd_alloc_ent(cmd, in, out, uout, uout_size,
			    callback, context, page_queue);
	अगर (IS_ERR(ent))
		वापस PTR_ERR(ent);

	/* put क्रम this ent is when consumed, depending on the use हाल
	 * 1) (!callback) blocking flow: by caller after रुको_func completes
	 * 2) (callback) flow: by mlx5_cmd_comp_handler() when ent is handled
	 */

	ent->token = token;
	ent->polling = क्रमce_polling;

	init_completion(&ent->handling);
	अगर (!callback)
		init_completion(&ent->करोne);

	INIT_DELAYED_WORK(&ent->cb_समयout_work, cb_समयout_handler);
	INIT_WORK(&ent->work, cmd_work_handler);
	अगर (page_queue) अणु
		cmd_work_handler(&ent->work);
	पूर्ण अन्यथा अगर (!queue_work(cmd->wq, &ent->work)) अणु
		mlx5_core_warn(dev, "failed to queue work\n");
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	अगर (callback)
		जाओ out; /* mlx5_cmd_comp_handler() will put(ent) */

	err = रुको_func(dev, ent);
	अगर (err == -ETIMEDOUT || err == -ECANCELED)
		जाओ out_मुक्त;

	ds = ent->ts2 - ent->ts1;
	op = MLX5_GET(mbox_in, in->first.data, opcode);
	अगर (op < MLX5_CMD_OP_MAX) अणु
		stats = &cmd->stats[op];
		spin_lock_irq(&stats->lock);
		stats->sum += ds;
		++stats->n;
		spin_unlock_irq(&stats->lock);
	पूर्ण
	mlx5_core_dbg_mask(dev, 1 << MLX5_CMD_TIME,
			   "fw exec time for %s is %lld nsec\n",
			   mlx5_command_str(op), ds);
	*status = ent->status;

out_मुक्त:
	cmd_ent_put(ent);
out:
	वापस err;
पूर्ण

अटल sमाप_प्रकार dbg_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mlx5_core_dev *dev = filp->निजी_data;
	काष्ठा mlx5_cmd_debug *dbg = &dev->cmd.dbg;
	अक्षर lbuf[3];
	पूर्णांक err;

	अगर (!dbg->in_msg || !dbg->out_msg)
		वापस -ENOMEM;

	अगर (count < माप(lbuf) - 1)
		वापस -EINVAL;

	अगर (copy_from_user(lbuf, buf, माप(lbuf) - 1))
		वापस -EFAULT;

	lbuf[माप(lbuf) - 1] = 0;

	अगर (म_भेद(lbuf, "go"))
		वापस -EINVAL;

	err = mlx5_cmd_exec(dev, dbg->in_msg, dbg->inlen, dbg->out_msg, dbg->outlen);

	वापस err ? err : count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= simple_खोलो,
	.ग_लिखो	= dbg_ग_लिखो,
पूर्ण;

अटल पूर्णांक mlx5_copy_to_msg(काष्ठा mlx5_cmd_msg *to, व्योम *from, पूर्णांक size,
			    u8 token)
अणु
	काष्ठा mlx5_cmd_prot_block *block;
	काष्ठा mlx5_cmd_mailbox *next;
	पूर्णांक copy;

	अगर (!to || !from)
		वापस -ENOMEM;

	copy = min_t(पूर्णांक, size, माप(to->first.data));
	स_नकल(to->first.data, from, copy);
	size -= copy;
	from += copy;

	next = to->next;
	जबतक (size) अणु
		अगर (!next) अणु
			/* this is a BUG */
			वापस -ENOMEM;
		पूर्ण

		copy = min_t(पूर्णांक, size, MLX5_CMD_DATA_BLOCK_SIZE);
		block = next->buf;
		स_नकल(block->data, from, copy);
		from += copy;
		size -= copy;
		block->token = token;
		next = next->next;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_copy_from_msg(व्योम *to, काष्ठा mlx5_cmd_msg *from, पूर्णांक size)
अणु
	काष्ठा mlx5_cmd_prot_block *block;
	काष्ठा mlx5_cmd_mailbox *next;
	पूर्णांक copy;

	अगर (!to || !from)
		वापस -ENOMEM;

	copy = min_t(पूर्णांक, size, माप(from->first.data));
	स_नकल(to, from->first.data, copy);
	size -= copy;
	to += copy;

	next = from->next;
	जबतक (size) अणु
		अगर (!next) अणु
			/* this is a BUG */
			वापस -ENOMEM;
		पूर्ण

		copy = min_t(पूर्णांक, size, MLX5_CMD_DATA_BLOCK_SIZE);
		block = next->buf;

		स_नकल(to, block->data, copy);
		to += copy;
		size -= copy;
		next = next->next;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mlx5_cmd_mailbox *alloc_cmd_box(काष्ठा mlx5_core_dev *dev,
					      gfp_t flags)
अणु
	काष्ठा mlx5_cmd_mailbox *mailbox;

	mailbox = kदो_स्मृति(माप(*mailbox), flags);
	अगर (!mailbox)
		वापस ERR_PTR(-ENOMEM);

	mailbox->buf = dma_pool_zalloc(dev->cmd.pool, flags,
				       &mailbox->dma);
	अगर (!mailbox->buf) अणु
		mlx5_core_dbg(dev, "failed allocation\n");
		kमुक्त(mailbox);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	mailbox->next = शून्य;

	वापस mailbox;
पूर्ण

अटल व्योम मुक्त_cmd_box(काष्ठा mlx5_core_dev *dev,
			 काष्ठा mlx5_cmd_mailbox *mailbox)
अणु
	dma_pool_मुक्त(dev->cmd.pool, mailbox->buf, mailbox->dma);
	kमुक्त(mailbox);
पूर्ण

अटल काष्ठा mlx5_cmd_msg *mlx5_alloc_cmd_msg(काष्ठा mlx5_core_dev *dev,
					       gfp_t flags, पूर्णांक size,
					       u8 token)
अणु
	काष्ठा mlx5_cmd_mailbox *पंचांगp, *head = शून्य;
	काष्ठा mlx5_cmd_prot_block *block;
	काष्ठा mlx5_cmd_msg *msg;
	पूर्णांक err;
	पूर्णांक n;
	पूर्णांक i;

	msg = kzalloc(माप(*msg), flags);
	अगर (!msg)
		वापस ERR_PTR(-ENOMEM);

	msg->len = size;
	n = mlx5_calc_cmd_blocks(msg);

	क्रम (i = 0; i < n; i++) अणु
		पंचांगp = alloc_cmd_box(dev, flags);
		अगर (IS_ERR(पंचांगp)) अणु
			mlx5_core_warn(dev, "failed allocating block\n");
			err = PTR_ERR(पंचांगp);
			जाओ err_alloc;
		पूर्ण

		block = पंचांगp->buf;
		पंचांगp->next = head;
		block->next = cpu_to_be64(पंचांगp->next ? पंचांगp->next->dma : 0);
		block->block_num = cpu_to_be32(n - i - 1);
		block->token = token;
		head = पंचांगp;
	पूर्ण
	msg->next = head;
	वापस msg;

err_alloc:
	जबतक (head) अणु
		पंचांगp = head->next;
		मुक्त_cmd_box(dev, head);
		head = पंचांगp;
	पूर्ण
	kमुक्त(msg);

	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlx5_मुक्त_cmd_msg(काष्ठा mlx5_core_dev *dev,
			      काष्ठा mlx5_cmd_msg *msg)
अणु
	काष्ठा mlx5_cmd_mailbox *head = msg->next;
	काष्ठा mlx5_cmd_mailbox *next;

	जबतक (head) अणु
		next = head->next;
		मुक्त_cmd_box(dev, head);
		head = next;
	पूर्ण
	kमुक्त(msg);
पूर्ण

अटल sमाप_प्रकार data_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mlx5_core_dev *dev = filp->निजी_data;
	काष्ठा mlx5_cmd_debug *dbg = &dev->cmd.dbg;
	व्योम *ptr;

	अगर (*pos != 0)
		वापस -EINVAL;

	kमुक्त(dbg->in_msg);
	dbg->in_msg = शून्य;
	dbg->inlen = 0;
	ptr = memdup_user(buf, count);
	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);
	dbg->in_msg = ptr;
	dbg->inlen = count;

	*pos = count;

	वापस count;
पूर्ण

अटल sमाप_प्रकार data_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			 loff_t *pos)
अणु
	काष्ठा mlx5_core_dev *dev = filp->निजी_data;
	काष्ठा mlx5_cmd_debug *dbg = &dev->cmd.dbg;

	अगर (!dbg->out_msg)
		वापस -ENOMEM;

	वापस simple_पढ़ो_from_buffer(buf, count, pos, dbg->out_msg,
				       dbg->outlen);
पूर्ण

अटल स्थिर काष्ठा file_operations dfops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= simple_खोलो,
	.ग_लिखो	= data_ग_लिखो,
	.पढ़ो	= data_पढ़ो,
पूर्ण;

अटल sमाप_प्रकार outlen_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			   loff_t *pos)
अणु
	काष्ठा mlx5_core_dev *dev = filp->निजी_data;
	काष्ठा mlx5_cmd_debug *dbg = &dev->cmd.dbg;
	अक्षर outlen[8];
	पूर्णांक err;

	err = snम_लिखो(outlen, माप(outlen), "%d", dbg->outlen);
	अगर (err < 0)
		वापस err;

	वापस simple_पढ़ो_from_buffer(buf, count, pos, outlen, err);
पूर्ण

अटल sमाप_प्रकार outlen_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mlx5_core_dev *dev = filp->निजी_data;
	काष्ठा mlx5_cmd_debug *dbg = &dev->cmd.dbg;
	अक्षर outlen_str[8] = अणु0पूर्ण;
	पूर्णांक outlen;
	व्योम *ptr;
	पूर्णांक err;

	अगर (*pos != 0 || count > 6)
		वापस -EINVAL;

	kमुक्त(dbg->out_msg);
	dbg->out_msg = शून्य;
	dbg->outlen = 0;

	अगर (copy_from_user(outlen_str, buf, count))
		वापस -EFAULT;

	err = माला_पूछो(outlen_str, "%d", &outlen);
	अगर (err < 0)
		वापस err;

	ptr = kzalloc(outlen, GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	dbg->out_msg = ptr;
	dbg->outlen = outlen;

	*pos = count;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations olfops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= simple_खोलो,
	.ग_लिखो	= outlen_ग_लिखो,
	.पढ़ो	= outlen_पढ़ो,
पूर्ण;

अटल व्योम set_wqname(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_cmd *cmd = &dev->cmd;

	snम_लिखो(cmd->wq_name, माप(cmd->wq_name), "mlx5_cmd_%s",
		 dev_name(dev->device));
पूर्ण

अटल व्योम clean_debug_files(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_cmd_debug *dbg = &dev->cmd.dbg;

	अगर (!mlx5_debugfs_root)
		वापस;

	mlx5_cmdअगर_debugfs_cleanup(dev);
	debugfs_हटाओ_recursive(dbg->dbg_root);
पूर्ण

अटल व्योम create_debugfs_files(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_cmd_debug *dbg = &dev->cmd.dbg;

	dbg->dbg_root = debugfs_create_dir("cmd", dev->priv.dbg_root);

	debugfs_create_file("in", 0400, dbg->dbg_root, dev, &dfops);
	debugfs_create_file("out", 0200, dbg->dbg_root, dev, &dfops);
	debugfs_create_file("out_len", 0600, dbg->dbg_root, dev, &olfops);
	debugfs_create_u8("status", 0600, dbg->dbg_root, &dbg->status);
	debugfs_create_file("run", 0200, dbg->dbg_root, dev, &fops);

	mlx5_cmdअगर_debugfs_init(dev);
पूर्ण

व्योम mlx5_cmd_allowed_opcode(काष्ठा mlx5_core_dev *dev, u16 opcode)
अणु
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	पूर्णांक i;

	क्रम (i = 0; i < cmd->max_reg_cmds; i++)
		करोwn(&cmd->sem);
	करोwn(&cmd->pages_sem);

	cmd->allowed_opcode = opcode;

	up(&cmd->pages_sem);
	क्रम (i = 0; i < cmd->max_reg_cmds; i++)
		up(&cmd->sem);
पूर्ण

अटल व्योम mlx5_cmd_change_mod(काष्ठा mlx5_core_dev *dev, पूर्णांक mode)
अणु
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	पूर्णांक i;

	क्रम (i = 0; i < cmd->max_reg_cmds; i++)
		करोwn(&cmd->sem);
	करोwn(&cmd->pages_sem);

	cmd->mode = mode;

	up(&cmd->pages_sem);
	क्रम (i = 0; i < cmd->max_reg_cmds; i++)
		up(&cmd->sem);
पूर्ण

अटल पूर्णांक cmd_comp_notअगरier(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mlx5_cmd *cmd;
	काष्ठा mlx5_eqe *eqe;

	cmd = mlx5_nb_cof(nb, काष्ठा mlx5_cmd, nb);
	dev = container_of(cmd, काष्ठा mlx5_core_dev, cmd);
	eqe = data;

	mlx5_cmd_comp_handler(dev, be32_to_cpu(eqe->data.cmd.vector), false);

	वापस NOTIFY_OK;
पूर्ण
व्योम mlx5_cmd_use_events(काष्ठा mlx5_core_dev *dev)
अणु
	MLX5_NB_INIT(&dev->cmd.nb, cmd_comp_notअगरier, CMD);
	mlx5_eq_notअगरier_रेजिस्टर(dev, &dev->cmd.nb);
	mlx5_cmd_change_mod(dev, CMD_MODE_EVENTS);
पूर्ण

व्योम mlx5_cmd_use_polling(काष्ठा mlx5_core_dev *dev)
अणु
	mlx5_cmd_change_mod(dev, CMD_MODE_POLLING);
	mlx5_eq_notअगरier_unरेजिस्टर(dev, &dev->cmd.nb);
पूर्ण

अटल व्योम मुक्त_msg(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_cmd_msg *msg)
अणु
	अचिन्हित दीर्घ flags;

	अगर (msg->parent) अणु
		spin_lock_irqsave(&msg->parent->lock, flags);
		list_add_tail(&msg->list, &msg->parent->head);
		spin_unlock_irqrestore(&msg->parent->lock, flags);
	पूर्ण अन्यथा अणु
		mlx5_मुक्त_cmd_msg(dev, msg);
	पूर्ण
पूर्ण

अटल व्योम mlx5_cmd_comp_handler(काष्ठा mlx5_core_dev *dev, u64 vec, bool क्रमced)
अणु
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	काष्ठा mlx5_cmd_work_ent *ent;
	mlx5_cmd_cbk_t callback;
	व्योम *context;
	पूर्णांक err;
	पूर्णांक i;
	s64 ds;
	काष्ठा mlx5_cmd_stats *stats;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ vector;

	/* there can be at most 32 command queues */
	vector = vec & 0xffffffff;
	क्रम (i = 0; i < (1 << cmd->log_sz); i++) अणु
		अगर (test_bit(i, &vector)) अणु
			काष्ठा semaphore *sem;

			ent = cmd->ent_arr[i];

			/* अगर we alपढ़ोy completed the command, ignore it */
			अगर (!test_and_clear_bit(MLX5_CMD_ENT_STATE_PENDING_COMP,
						&ent->state)) अणु
				/* only real completion can मुक्त the cmd slot */
				अगर (!क्रमced) अणु
					mlx5_core_err(dev, "Command completion arrived after timeout (entry idx = %d).\n",
						      ent->idx);
					cmd_ent_put(ent);
				पूर्ण
				जारी;
			पूर्ण

			अगर (ent->callback && cancel_delayed_work(&ent->cb_समयout_work))
				cmd_ent_put(ent); /* समयout work was canceled */

			अगर (!क्रमced || /* Real FW completion */
			    pci_channel_offline(dev->pdev) || /* FW is inaccessible */
			    dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
				cmd_ent_put(ent);

			अगर (ent->page_queue)
				sem = &cmd->pages_sem;
			अन्यथा
				sem = &cmd->sem;
			ent->ts2 = kसमय_get_ns();
			स_नकल(ent->out->first.data, ent->lay->out, माप(ent->lay->out));
			dump_command(dev, ent, 0);
			अगर (!ent->ret) अणु
				अगर (!cmd->checksum_disabled)
					ent->ret = verअगरy_signature(ent);
				अन्यथा
					ent->ret = 0;
				अगर (vec & MLX5_TRIGGERED_CMD_COMP)
					ent->status = MLX5_DRIVER_STATUS_ABORTED;
				अन्यथा
					ent->status = ent->lay->status_own >> 1;

				mlx5_core_dbg(dev, "command completed. ret 0x%x, delivery status %s(0x%x)\n",
					      ent->ret, deliv_status_to_str(ent->status), ent->status);
			पूर्ण

			अगर (ent->callback) अणु
				ds = ent->ts2 - ent->ts1;
				अगर (ent->op < MLX5_CMD_OP_MAX) अणु
					stats = &cmd->stats[ent->op];
					spin_lock_irqsave(&stats->lock, flags);
					stats->sum += ds;
					++stats->n;
					spin_unlock_irqrestore(&stats->lock, flags);
				पूर्ण

				callback = ent->callback;
				context = ent->context;
				err = ent->ret;
				अगर (!err) अणु
					err = mlx5_copy_from_msg(ent->uout,
								 ent->out,
								 ent->uout_size);

					err = err ? err : mlx5_cmd_check(dev,
									ent->in->first.data,
									ent->uout);
				पूर्ण

				mlx5_मुक्त_cmd_msg(dev, ent->out);
				मुक्त_msg(dev, ent->in);

				err = err ? err : ent->status;
				/* final consumer is करोne, release ent */
				cmd_ent_put(ent);
				callback(err, context);
			पूर्ण अन्यथा अणु
				/* release रुको_func() so mlx5_cmd_invoke()
				 * can make the final ent_put()
				 */
				complete(&ent->करोne);
			पूर्ण
			up(sem);
		पूर्ण
	पूर्ण
पूर्ण

व्योम mlx5_cmd_trigger_completions(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	अचिन्हित दीर्घ biपंचांगask;
	अचिन्हित दीर्घ flags;
	u64 vector;
	पूर्णांक i;

	/* रुको क्रम pending handlers to complete */
	mlx5_eq_synchronize_cmd_irq(dev);
	spin_lock_irqsave(&dev->cmd.alloc_lock, flags);
	vector = ~dev->cmd.biपंचांगask & ((1ul << (1 << dev->cmd.log_sz)) - 1);
	अगर (!vector)
		जाओ no_trig;

	biपंचांगask = vector;
	/* we must increment the allocated entries refcount beक्रमe triggering the completions
	 * to guarantee pending commands will not get मुक्तd in the meanजबतक.
	 * For that reason, it also has to be करोne inside the alloc_lock.
	 */
	क्रम_each_set_bit(i, &biपंचांगask, (1 << cmd->log_sz))
		cmd_ent_get(cmd->ent_arr[i]);
	vector |= MLX5_TRIGGERED_CMD_COMP;
	spin_unlock_irqrestore(&dev->cmd.alloc_lock, flags);

	mlx5_core_dbg(dev, "vector 0x%llx\n", vector);
	mlx5_cmd_comp_handler(dev, vector, true);
	क्रम_each_set_bit(i, &biपंचांगask, (1 << cmd->log_sz))
		cmd_ent_put(cmd->ent_arr[i]);
	वापस;

no_trig:
	spin_unlock_irqrestore(&dev->cmd.alloc_lock, flags);
पूर्ण

व्योम mlx5_cmd_flush(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	पूर्णांक i;

	क्रम (i = 0; i < cmd->max_reg_cmds; i++)
		जबतक (करोwn_trylock(&cmd->sem))
			mlx5_cmd_trigger_completions(dev);

	जबतक (करोwn_trylock(&cmd->pages_sem))
		mlx5_cmd_trigger_completions(dev);

	/* Unlock cmdअगर */
	up(&cmd->pages_sem);
	क्रम (i = 0; i < cmd->max_reg_cmds; i++)
		up(&cmd->sem);
पूर्ण

अटल पूर्णांक status_to_err(u8 status)
अणु
	चयन (status) अणु
	हाल MLX5_CMD_DELIVERY_STAT_OK:
	हाल MLX5_DRIVER_STATUS_ABORTED:
		वापस 0;
	हाल MLX5_CMD_DELIVERY_STAT_SIGNAT_ERR:
	हाल MLX5_CMD_DELIVERY_STAT_TOK_ERR:
		वापस -EBADR;
	हाल MLX5_CMD_DELIVERY_STAT_BAD_BLK_NUM_ERR:
	हाल MLX5_CMD_DELIVERY_STAT_OUT_PTR_ALIGN_ERR:
	हाल MLX5_CMD_DELIVERY_STAT_IN_PTR_ALIGN_ERR:
		वापस -EFAULT; /* Bad address */
	हाल MLX5_CMD_DELIVERY_STAT_IN_LENGTH_ERR:
	हाल MLX5_CMD_DELIVERY_STAT_OUT_LENGTH_ERR:
	हाल MLX5_CMD_DELIVERY_STAT_CMD_DESCR_ERR:
	हाल MLX5_CMD_DELIVERY_STAT_RES_FLD_NOT_CLR_ERR:
		वापस -ENOMSG;
	हाल MLX5_CMD_DELIVERY_STAT_FW_ERR:
		वापस -EIO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा mlx5_cmd_msg *alloc_msg(काष्ठा mlx5_core_dev *dev, पूर्णांक in_size,
				      gfp_t gfp)
अणु
	काष्ठा mlx5_cmd_msg *msg = ERR_PTR(-ENOMEM);
	काष्ठा cmd_msg_cache *ch = शून्य;
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	पूर्णांक i;

	अगर (in_size <= 16)
		जाओ cache_miss;

	क्रम (i = 0; i < MLX5_NUM_COMMAND_CACHES; i++) अणु
		ch = &cmd->cache[i];
		अगर (in_size > ch->max_inbox_size)
			जारी;
		spin_lock_irq(&ch->lock);
		अगर (list_empty(&ch->head)) अणु
			spin_unlock_irq(&ch->lock);
			जारी;
		पूर्ण
		msg = list_entry(ch->head.next, typeof(*msg), list);
		/* For cached lists, we must explicitly state what is
		 * the real size
		 */
		msg->len = in_size;
		list_del(&msg->list);
		spin_unlock_irq(&ch->lock);
		अवरोध;
	पूर्ण

	अगर (!IS_ERR(msg))
		वापस msg;

cache_miss:
	msg = mlx5_alloc_cmd_msg(dev, gfp, in_size, 0);
	वापस msg;
पूर्ण

अटल पूर्णांक is_manage_pages(व्योम *in)
अणु
	वापस MLX5_GET(mbox_in, in, opcode) == MLX5_CMD_OP_MANAGE_PAGES;
पूर्ण

अटल पूर्णांक cmd_exec(काष्ठा mlx5_core_dev *dev, व्योम *in, पूर्णांक in_size, व्योम *out,
		    पूर्णांक out_size, mlx5_cmd_cbk_t callback, व्योम *context,
		    bool क्रमce_polling)
अणु
	काष्ठा mlx5_cmd_msg *inb;
	काष्ठा mlx5_cmd_msg *outb;
	पूर्णांक pages_queue;
	gfp_t gfp;
	पूर्णांक err;
	u8 status = 0;
	u32 drv_synd;
	u16 opcode;
	u8 token;

	opcode = MLX5_GET(mbox_in, in, opcode);
	अगर (mlx5_cmd_is_करोwn(dev) || !opcode_allowed(&dev->cmd, opcode)) अणु
		err = mlx5_पूर्णांकernal_err_ret_value(dev, opcode, &drv_synd, &status);
		MLX5_SET(mbox_out, out, status, status);
		MLX5_SET(mbox_out, out, syndrome, drv_synd);
		वापस err;
	पूर्ण

	pages_queue = is_manage_pages(in);
	gfp = callback ? GFP_ATOMIC : GFP_KERNEL;

	inb = alloc_msg(dev, in_size, gfp);
	अगर (IS_ERR(inb)) अणु
		err = PTR_ERR(inb);
		वापस err;
	पूर्ण

	token = alloc_token(&dev->cmd);

	err = mlx5_copy_to_msg(inb, in, in_size, token);
	अगर (err) अणु
		mlx5_core_warn(dev, "err %d\n", err);
		जाओ out_in;
	पूर्ण

	outb = mlx5_alloc_cmd_msg(dev, gfp, out_size, token);
	अगर (IS_ERR(outb)) अणु
		err = PTR_ERR(outb);
		जाओ out_in;
	पूर्ण

	err = mlx5_cmd_invoke(dev, inb, outb, out, out_size, callback, context,
			      pages_queue, &status, token, क्रमce_polling);
	अगर (err)
		जाओ out_out;

	mlx5_core_dbg(dev, "err %d, status %d\n", err, status);
	अगर (status) अणु
		err = status_to_err(status);
		जाओ out_out;
	पूर्ण

	अगर (!callback)
		err = mlx5_copy_from_msg(out, outb, out_size);

out_out:
	अगर (!callback)
		mlx5_मुक्त_cmd_msg(dev, outb);

out_in:
	अगर (!callback)
		मुक्त_msg(dev, inb);
	वापस err;
पूर्ण

पूर्णांक mlx5_cmd_exec(काष्ठा mlx5_core_dev *dev, व्योम *in, पूर्णांक in_size, व्योम *out,
		  पूर्णांक out_size)
अणु
	पूर्णांक err;

	err = cmd_exec(dev, in, in_size, out, out_size, शून्य, शून्य, false);
	वापस err ? : mlx5_cmd_check(dev, in, out);
पूर्ण
EXPORT_SYMBOL(mlx5_cmd_exec);

व्योम mlx5_cmd_init_async_ctx(काष्ठा mlx5_core_dev *dev,
			     काष्ठा mlx5_async_ctx *ctx)
अणु
	ctx->dev = dev;
	/* Starts at 1 to aव्योम करोing wake_up अगर we are not cleaning up */
	atomic_set(&ctx->num_inflight, 1);
	init_रुकोqueue_head(&ctx->रुको);
पूर्ण
EXPORT_SYMBOL(mlx5_cmd_init_async_ctx);

/**
 * mlx5_cmd_cleanup_async_ctx - Clean up an async_ctx
 * @ctx: The ctx to clean
 *
 * Upon वापस all callbacks given to mlx5_cmd_exec_cb() have been called. The
 * caller must ensure that mlx5_cmd_exec_cb() is not called during or after
 * the call mlx5_cleanup_async_ctx().
 */
व्योम mlx5_cmd_cleanup_async_ctx(काष्ठा mlx5_async_ctx *ctx)
अणु
	atomic_dec(&ctx->num_inflight);
	रुको_event(ctx->रुको, atomic_पढ़ो(&ctx->num_inflight) == 0);
पूर्ण
EXPORT_SYMBOL(mlx5_cmd_cleanup_async_ctx);

अटल व्योम mlx5_cmd_exec_cb_handler(पूर्णांक status, व्योम *_work)
अणु
	काष्ठा mlx5_async_work *work = _work;
	काष्ठा mlx5_async_ctx *ctx = work->ctx;

	work->user_callback(status, work);
	अगर (atomic_dec_and_test(&ctx->num_inflight))
		wake_up(&ctx->रुको);
पूर्ण

पूर्णांक mlx5_cmd_exec_cb(काष्ठा mlx5_async_ctx *ctx, व्योम *in, पूर्णांक in_size,
		     व्योम *out, पूर्णांक out_size, mlx5_async_cbk_t callback,
		     काष्ठा mlx5_async_work *work)
अणु
	पूर्णांक ret;

	work->ctx = ctx;
	work->user_callback = callback;
	अगर (WARN_ON(!atomic_inc_not_zero(&ctx->num_inflight)))
		वापस -EIO;
	ret = cmd_exec(ctx->dev, in, in_size, out, out_size,
		       mlx5_cmd_exec_cb_handler, work, false);
	अगर (ret && atomic_dec_and_test(&ctx->num_inflight))
		wake_up(&ctx->रुको);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mlx5_cmd_exec_cb);

पूर्णांक mlx5_cmd_exec_polling(काष्ठा mlx5_core_dev *dev, व्योम *in, पूर्णांक in_size,
			  व्योम *out, पूर्णांक out_size)
अणु
	पूर्णांक err;

	err = cmd_exec(dev, in, in_size, out, out_size, शून्य, शून्य, true);

	वापस err ? : mlx5_cmd_check(dev, in, out);
पूर्ण
EXPORT_SYMBOL(mlx5_cmd_exec_polling);

अटल व्योम destroy_msg_cache(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा cmd_msg_cache *ch;
	काष्ठा mlx5_cmd_msg *msg;
	काष्ठा mlx5_cmd_msg *n;
	पूर्णांक i;

	क्रम (i = 0; i < MLX5_NUM_COMMAND_CACHES; i++) अणु
		ch = &dev->cmd.cache[i];
		list_क्रम_each_entry_safe(msg, n, &ch->head, list) अणु
			list_del(&msg->list);
			mlx5_मुक्त_cmd_msg(dev, msg);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित cmd_cache_num_ent[MLX5_NUM_COMMAND_CACHES] = अणु
	512, 32, 16, 8, 2
पूर्ण;

अटल अचिन्हित cmd_cache_ent_size[MLX5_NUM_COMMAND_CACHES] = अणु
	16 + MLX5_CMD_DATA_BLOCK_SIZE,
	16 + MLX5_CMD_DATA_BLOCK_SIZE * 2,
	16 + MLX5_CMD_DATA_BLOCK_SIZE * 16,
	16 + MLX5_CMD_DATA_BLOCK_SIZE * 256,
	16 + MLX5_CMD_DATA_BLOCK_SIZE * 512,
पूर्ण;

अटल व्योम create_msg_cache(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	काष्ठा cmd_msg_cache *ch;
	काष्ठा mlx5_cmd_msg *msg;
	पूर्णांक i;
	पूर्णांक k;

	/* Initialize and fill the caches with initial entries */
	क्रम (k = 0; k < MLX5_NUM_COMMAND_CACHES; k++) अणु
		ch = &cmd->cache[k];
		spin_lock_init(&ch->lock);
		INIT_LIST_HEAD(&ch->head);
		ch->num_ent = cmd_cache_num_ent[k];
		ch->max_inbox_size = cmd_cache_ent_size[k];
		क्रम (i = 0; i < ch->num_ent; i++) अणु
			msg = mlx5_alloc_cmd_msg(dev, GFP_KERNEL | __GFP_NOWARN,
						 ch->max_inbox_size, 0);
			अगर (IS_ERR(msg))
				अवरोध;
			msg->parent = ch;
			list_add_tail(&msg->list, &ch->head);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_cmd_page(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_cmd *cmd)
अणु
	cmd->cmd_alloc_buf = dma_alloc_coherent(mlx5_core_dma_dev(dev), MLX5_ADAPTER_PAGE_SIZE,
						&cmd->alloc_dma, GFP_KERNEL);
	अगर (!cmd->cmd_alloc_buf)
		वापस -ENOMEM;

	/* make sure it is aligned to 4K */
	अगर (!((uपूर्णांकptr_t)cmd->cmd_alloc_buf & (MLX5_ADAPTER_PAGE_SIZE - 1))) अणु
		cmd->cmd_buf = cmd->cmd_alloc_buf;
		cmd->dma = cmd->alloc_dma;
		cmd->alloc_size = MLX5_ADAPTER_PAGE_SIZE;
		वापस 0;
	पूर्ण

	dma_मुक्त_coherent(mlx5_core_dma_dev(dev), MLX5_ADAPTER_PAGE_SIZE, cmd->cmd_alloc_buf,
			  cmd->alloc_dma);
	cmd->cmd_alloc_buf = dma_alloc_coherent(mlx5_core_dma_dev(dev),
						2 * MLX5_ADAPTER_PAGE_SIZE - 1,
						&cmd->alloc_dma, GFP_KERNEL);
	अगर (!cmd->cmd_alloc_buf)
		वापस -ENOMEM;

	cmd->cmd_buf = PTR_ALIGN(cmd->cmd_alloc_buf, MLX5_ADAPTER_PAGE_SIZE);
	cmd->dma = ALIGN(cmd->alloc_dma, MLX5_ADAPTER_PAGE_SIZE);
	cmd->alloc_size = 2 * MLX5_ADAPTER_PAGE_SIZE - 1;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_cmd_page(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_cmd *cmd)
अणु
	dma_मुक्त_coherent(mlx5_core_dma_dev(dev), cmd->alloc_size, cmd->cmd_alloc_buf,
			  cmd->alloc_dma);
पूर्ण

अटल u16 cmdअगर_rev(काष्ठा mlx5_core_dev *dev)
अणु
	वापस ioपढ़ो32be(&dev->iseg->cmdअगर_rev_fw_sub) >> 16;
पूर्ण

पूर्णांक mlx5_cmd_init(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक size = माप(काष्ठा mlx5_cmd_prot_block);
	पूर्णांक align = roundup_घात_of_two(size);
	काष्ठा mlx5_cmd *cmd = &dev->cmd;
	u32 cmd_h, cmd_l;
	u16 cmd_अगर_rev;
	पूर्णांक err;
	पूर्णांक i;

	स_रखो(cmd, 0, माप(*cmd));
	cmd_अगर_rev = cmdअगर_rev(dev);
	अगर (cmd_अगर_rev != CMD_IF_REV) अणु
		mlx5_core_err(dev,
			      "Driver cmdif rev(%d) differs from firmware's(%d)\n",
			      CMD_IF_REV, cmd_अगर_rev);
		वापस -EINVAL;
	पूर्ण

	cmd->stats = kvzalloc(MLX5_CMD_OP_MAX * माप(*cmd->stats), GFP_KERNEL);
	अगर (!cmd->stats)
		वापस -ENOMEM;

	cmd->pool = dma_pool_create("mlx5_cmd", mlx5_core_dma_dev(dev), size, align, 0);
	अगर (!cmd->pool) अणु
		err = -ENOMEM;
		जाओ dma_pool_err;
	पूर्ण

	err = alloc_cmd_page(dev, cmd);
	अगर (err)
		जाओ err_मुक्त_pool;

	cmd_l = ioपढ़ो32be(&dev->iseg->cmdq_addr_l_sz) & 0xff;
	cmd->log_sz = cmd_l >> 4 & 0xf;
	cmd->log_stride = cmd_l & 0xf;
	अगर (1 << cmd->log_sz > MLX5_MAX_COMMANDS) अणु
		mlx5_core_err(dev, "firmware reports too many outstanding commands %d\n",
			      1 << cmd->log_sz);
		err = -EINVAL;
		जाओ err_मुक्त_page;
	पूर्ण

	अगर (cmd->log_sz + cmd->log_stride > MLX5_ADAPTER_PAGE_SHIFT) अणु
		mlx5_core_err(dev, "command queue size overflow\n");
		err = -EINVAL;
		जाओ err_मुक्त_page;
	पूर्ण

	cmd->state = MLX5_CMDIF_STATE_DOWN;
	cmd->checksum_disabled = 1;
	cmd->max_reg_cmds = (1 << cmd->log_sz) - 1;
	cmd->biपंचांगask = (1UL << cmd->max_reg_cmds) - 1;

	cmd->cmdअगर_rev = ioपढ़ो32be(&dev->iseg->cmdअगर_rev_fw_sub) >> 16;
	अगर (cmd->cmdअगर_rev > CMD_IF_REV) अणु
		mlx5_core_err(dev, "driver does not support command interface version. driver %d, firmware %d\n",
			      CMD_IF_REV, cmd->cmdअगर_rev);
		err = -EOPNOTSUPP;
		जाओ err_मुक्त_page;
	पूर्ण

	spin_lock_init(&cmd->alloc_lock);
	spin_lock_init(&cmd->token_lock);
	क्रम (i = 0; i < MLX5_CMD_OP_MAX; i++)
		spin_lock_init(&cmd->stats[i].lock);

	sema_init(&cmd->sem, cmd->max_reg_cmds);
	sema_init(&cmd->pages_sem, 1);

	cmd_h = (u32)((u64)(cmd->dma) >> 32);
	cmd_l = (u32)(cmd->dma);
	अगर (cmd_l & 0xfff) अणु
		mlx5_core_err(dev, "invalid command queue address\n");
		err = -ENOMEM;
		जाओ err_मुक्त_page;
	पूर्ण

	ioग_लिखो32be(cmd_h, &dev->iseg->cmdq_addr_h);
	ioग_लिखो32be(cmd_l, &dev->iseg->cmdq_addr_l_sz);

	/* Make sure firmware sees the complete address beक्रमe we proceed */
	wmb();

	mlx5_core_dbg(dev, "descriptor at dma 0x%llx\n", (अचिन्हित दीर्घ दीर्घ)(cmd->dma));

	cmd->mode = CMD_MODE_POLLING;
	cmd->allowed_opcode = CMD_ALLOWED_OPCODE_ALL;

	create_msg_cache(dev);

	set_wqname(dev);
	cmd->wq = create_singlethपढ़ो_workqueue(cmd->wq_name);
	अगर (!cmd->wq) अणु
		mlx5_core_err(dev, "failed to create command workqueue\n");
		err = -ENOMEM;
		जाओ err_cache;
	पूर्ण

	create_debugfs_files(dev);

	वापस 0;

err_cache:
	destroy_msg_cache(dev);

err_मुक्त_page:
	मुक्त_cmd_page(dev, cmd);

err_मुक्त_pool:
	dma_pool_destroy(cmd->pool);
dma_pool_err:
	kvमुक्त(cmd->stats);
	वापस err;
पूर्ण

व्योम mlx5_cmd_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_cmd *cmd = &dev->cmd;

	clean_debug_files(dev);
	destroy_workqueue(cmd->wq);
	destroy_msg_cache(dev);
	मुक्त_cmd_page(dev, cmd);
	dma_pool_destroy(cmd->pool);
	kvमुक्त(cmd->stats);
पूर्ण

व्योम mlx5_cmd_set_state(काष्ठा mlx5_core_dev *dev,
			क्रमागत mlx5_cmdअगर_state cmdअगर_state)
अणु
	dev->cmd.state = cmdअगर_state;
पूर्ण
