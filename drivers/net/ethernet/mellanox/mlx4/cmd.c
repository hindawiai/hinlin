<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems, Inc.  All rights reserved.
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

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/mlx4/device.h>
#समावेश <linux/semaphore.h>
#समावेश <rdma/ib_smi.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>

#समावेश <यंत्र/पन.स>

#समावेश "mlx4.h"
#समावेश "fw.h"
#समावेश "fw_qos.h"
#समावेश "mlx4_stats.h"

#घोषणा CMD_POLL_TOKEN 0xffff
#घोषणा INBOX_MASK	0xffffffffffffff00ULL

#घोषणा CMD_CHAN_VER 1
#घोषणा CMD_CHAN_IF_REV 1

क्रमागत अणु
	/* command completed successfully: */
	CMD_STAT_OK		= 0x00,
	/* Internal error (such as a bus error) occurred जबतक processing command: */
	CMD_STAT_INTERNAL_ERR	= 0x01,
	/* Operation/command not supported or opcode modअगरier not supported: */
	CMD_STAT_BAD_OP		= 0x02,
	/* Parameter not supported or parameter out of range: */
	CMD_STAT_BAD_PARAM	= 0x03,
	/* System not enabled or bad प्रणाली state: */
	CMD_STAT_BAD_SYS_STATE	= 0x04,
	/* Attempt to access reserved or unallocaterd resource: */
	CMD_STAT_BAD_RESOURCE	= 0x05,
	/* Requested resource is currently executing a command, or is otherwise busy: */
	CMD_STAT_RESOURCE_BUSY	= 0x06,
	/* Required capability exceeds device limits: */
	CMD_STAT_EXCEED_LIM	= 0x08,
	/* Resource is not in the appropriate state or ownership: */
	CMD_STAT_BAD_RES_STATE	= 0x09,
	/* Index out of range: */
	CMD_STAT_BAD_INDEX	= 0x0a,
	/* FW image corrupted: */
	CMD_STAT_BAD_NVMEM	= 0x0b,
	/* Error in ICM mapping (e.g. not enough auxiliary ICM pages to execute command): */
	CMD_STAT_ICM_ERROR	= 0x0c,
	/* Attempt to modअगरy a QP/EE which is not in the presumed state: */
	CMD_STAT_BAD_QP_STATE   = 0x10,
	/* Bad segment parameters (Address/Size): */
	CMD_STAT_BAD_SEG_PARAM	= 0x20,
	/* Memory Region has Memory Winकरोws bound to: */
	CMD_STAT_REG_BOUND	= 0x21,
	/* HCA local attached memory not present: */
	CMD_STAT_LAM_NOT_PRE	= 0x22,
	/* Bad management packet (silently discarded): */
	CMD_STAT_BAD_PKT	= 0x30,
	/* More outstanding CQEs in CQ than new CQ size: */
	CMD_STAT_BAD_SIZE	= 0x40,
	/* Multi Function device support required: */
	CMD_STAT_MULTI_FUNC_REQ	= 0x50,
पूर्ण;

क्रमागत अणु
	HCR_IN_PARAM_OFFSET	= 0x00,
	HCR_IN_MODIFIER_OFFSET	= 0x08,
	HCR_OUT_PARAM_OFFSET	= 0x0c,
	HCR_TOKEN_OFFSET	= 0x14,
	HCR_STATUS_OFFSET	= 0x18,

	HCR_OPMOD_SHIFT		= 12,
	HCR_T_BIT		= 21,
	HCR_E_BIT		= 22,
	HCR_GO_BIT		= 23
पूर्ण;

क्रमागत अणु
	GO_BIT_TIMEOUT_MSECS	= 10000
पूर्ण;

क्रमागत mlx4_vlan_transition अणु
	MLX4_VLAN_TRANSITION_VST_VST = 0,
	MLX4_VLAN_TRANSITION_VST_VGT = 1,
	MLX4_VLAN_TRANSITION_VGT_VST = 2,
	MLX4_VLAN_TRANSITION_VGT_VGT = 3,
पूर्ण;


काष्ठा mlx4_cmd_context अणु
	काष्ठा completion	करोne;
	पूर्णांक			result;
	पूर्णांक			next;
	u64			out_param;
	u16			token;
	u8			fw_status;
पूर्ण;

अटल पूर्णांक mlx4_master_process_vhcr(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				    काष्ठा mlx4_vhcr_cmd *in_vhcr);

अटल पूर्णांक mlx4_status_to_त्रुटि_सं(u8 status)
अणु
	अटल स्थिर पूर्णांक trans_table[] = अणु
		[CMD_STAT_INTERNAL_ERR]	  = -EIO,
		[CMD_STAT_BAD_OP]	  = -EPERM,
		[CMD_STAT_BAD_PARAM]	  = -EINVAL,
		[CMD_STAT_BAD_SYS_STATE]  = -ENXIO,
		[CMD_STAT_BAD_RESOURCE]	  = -EBADF,
		[CMD_STAT_RESOURCE_BUSY]  = -EBUSY,
		[CMD_STAT_EXCEED_LIM]	  = -ENOMEM,
		[CMD_STAT_BAD_RES_STATE]  = -EBADF,
		[CMD_STAT_BAD_INDEX]	  = -EBADF,
		[CMD_STAT_BAD_NVMEM]	  = -EFAULT,
		[CMD_STAT_ICM_ERROR]	  = -ENखाता,
		[CMD_STAT_BAD_QP_STATE]   = -EINVAL,
		[CMD_STAT_BAD_SEG_PARAM]  = -EFAULT,
		[CMD_STAT_REG_BOUND]	  = -EBUSY,
		[CMD_STAT_LAM_NOT_PRE]	  = -EAGAIN,
		[CMD_STAT_BAD_PKT]	  = -EINVAL,
		[CMD_STAT_BAD_SIZE]	  = -ENOMEM,
		[CMD_STAT_MULTI_FUNC_REQ] = -EACCES,
	पूर्ण;

	अगर (status >= ARRAY_SIZE(trans_table) ||
	    (status != CMD_STAT_OK && trans_table[status] == 0))
		वापस -EIO;

	वापस trans_table[status];
पूर्ण

अटल u8 mlx4_त्रुटि_सं_to_status(पूर्णांक त्रुटि_सं)
अणु
	चयन (त्रुटि_सं) अणु
	हाल -EPERM:
		वापस CMD_STAT_BAD_OP;
	हाल -EINVAL:
		वापस CMD_STAT_BAD_PARAM;
	हाल -ENXIO:
		वापस CMD_STAT_BAD_SYS_STATE;
	हाल -EBUSY:
		वापस CMD_STAT_RESOURCE_BUSY;
	हाल -ENOMEM:
		वापस CMD_STAT_EXCEED_LIM;
	हाल -ENखाता:
		वापस CMD_STAT_ICM_ERROR;
	शेष:
		वापस CMD_STAT_INTERNAL_ERR;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_पूर्णांकernal_err_ret_value(काष्ठा mlx4_dev *dev, u16 op,
				       u8 op_modअगरier)
अणु
	चयन (op) अणु
	हाल MLX4_CMD_UNMAP_ICM:
	हाल MLX4_CMD_UNMAP_ICM_AUX:
	हाल MLX4_CMD_UNMAP_FA:
	हाल MLX4_CMD_2RST_QP:
	हाल MLX4_CMD_HW2SW_EQ:
	हाल MLX4_CMD_HW2SW_CQ:
	हाल MLX4_CMD_HW2SW_SRQ:
	हाल MLX4_CMD_HW2SW_MPT:
	हाल MLX4_CMD_CLOSE_HCA:
	हाल MLX4_QP_FLOW_STEERING_DETACH:
	हाल MLX4_CMD_FREE_RES:
	हाल MLX4_CMD_CLOSE_PORT:
		वापस CMD_STAT_OK;

	हाल MLX4_CMD_QP_ATTACH:
		/* On Detach हाल वापस success */
		अगर (op_modअगरier == 0)
			वापस CMD_STAT_OK;
		वापस mlx4_status_to_त्रुटि_सं(CMD_STAT_INTERNAL_ERR);

	शेष:
		वापस mlx4_status_to_त्रुटि_सं(CMD_STAT_INTERNAL_ERR);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_closing_cmd_fatal_error(u16 op, u8 fw_status)
अणु
	/* Any error during the closing commands below is considered fatal */
	अगर (op == MLX4_CMD_CLOSE_HCA ||
	    op == MLX4_CMD_HW2SW_EQ ||
	    op == MLX4_CMD_HW2SW_CQ ||
	    op == MLX4_CMD_2RST_QP ||
	    op == MLX4_CMD_HW2SW_SRQ ||
	    op == MLX4_CMD_SYNC_TPT ||
	    op == MLX4_CMD_UNMAP_ICM ||
	    op == MLX4_CMD_UNMAP_ICM_AUX ||
	    op == MLX4_CMD_UNMAP_FA)
		वापस 1;
	/* Error on MLX4_CMD_HW2SW_MPT is fatal except when fw status equals
	  * CMD_STAT_REG_BOUND.
	  * This status indicates that memory region has memory winकरोws bound to it
	  * which may result from invalid user space usage and is not fatal.
	  */
	अगर (op == MLX4_CMD_HW2SW_MPT && fw_status != CMD_STAT_REG_BOUND)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_cmd_reset_flow(काष्ठा mlx4_dev *dev, u16 op, u8 op_modअगरier,
			       पूर्णांक err)
अणु
	/* Only अगर reset flow is really active वापस code is based on
	  * command, otherwise current error code is वापसed.
	  */
	अगर (mlx4_पूर्णांकernal_err_reset) अणु
		mlx4_enter_error_state(dev->persist);
		err = mlx4_पूर्णांकernal_err_ret_value(dev, op, op_modअगरier);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक comm_pending(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	u32 status = पढ़ोl(&priv->mfunc.comm->slave_पढ़ो);

	वापस (swab32(status) >> 31) != priv->cmd.comm_toggle;
पूर्ण

अटल पूर्णांक mlx4_comm_cmd_post(काष्ठा mlx4_dev *dev, u8 cmd, u16 param)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	u32 val;

	/* To aव्योम writing to unknown addresses after the device state was
	 * changed to पूर्णांकernal error and the function was rest,
	 * check the INTERNAL_ERROR flag which is updated under
	 * device_state_mutex lock.
	 */
	mutex_lock(&dev->persist->device_state_mutex);

	अगर (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR) अणु
		mutex_unlock(&dev->persist->device_state_mutex);
		वापस -EIO;
	पूर्ण

	priv->cmd.comm_toggle ^= 1;
	val = param | (cmd << 16) | (priv->cmd.comm_toggle << 31);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(val),
		     &priv->mfunc.comm->slave_ग_लिखो);
	mutex_unlock(&dev->persist->device_state_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_comm_cmd_poll(काष्ठा mlx4_dev *dev, u8 cmd, u16 param,
		       अचिन्हित दीर्घ समयout)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	अचिन्हित दीर्घ end;
	पूर्णांक err = 0;
	पूर्णांक ret_from_pending = 0;

	/* First, verअगरy that the master reports correct status */
	अगर (comm_pending(dev)) अणु
		mlx4_warn(dev, "Communication channel is not idle - my toggle is %d (cmd:0x%x)\n",
			  priv->cmd.comm_toggle, cmd);
		वापस -EAGAIN;
	पूर्ण

	/* Write command */
	करोwn(&priv->cmd.poll_sem);
	अगर (mlx4_comm_cmd_post(dev, cmd, param)) अणु
		/* Only in हाल the device state is INTERNAL_ERROR,
		 * mlx4_comm_cmd_post वापसs with an error
		 */
		err = mlx4_status_to_त्रुटि_सं(CMD_STAT_INTERNAL_ERR);
		जाओ out;
	पूर्ण

	end = msecs_to_jअगरfies(समयout) + jअगरfies;
	जबतक (comm_pending(dev) && समय_beक्रमe(jअगरfies, end))
		cond_resched();
	ret_from_pending = comm_pending(dev);
	अगर (ret_from_pending) अणु
		/* check अगर the slave is trying to boot in the middle of
		 * FLR process. The only non-zero result in the RESET command
		 * is MLX4_DELAY_RESET_SLAVE*/
		अगर ((MLX4_COMM_CMD_RESET == cmd)) अणु
			err = MLX4_DELAY_RESET_SLAVE;
			जाओ out;
		पूर्ण अन्यथा अणु
			mlx4_warn(dev, "Communication channel command 0x%x timed out\n",
				  cmd);
			err = mlx4_status_to_त्रुटि_सं(CMD_STAT_INTERNAL_ERR);
		पूर्ण
	पूर्ण

	अगर (err)
		mlx4_enter_error_state(dev->persist);
out:
	up(&priv->cmd.poll_sem);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_comm_cmd_रुको(काष्ठा mlx4_dev *dev, u8 vhcr_cmd,
			      u16 param, u16 op, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा mlx4_cmd *cmd = &mlx4_priv(dev)->cmd;
	काष्ठा mlx4_cmd_context *context;
	अचिन्हित दीर्घ end;
	पूर्णांक err = 0;

	करोwn(&cmd->event_sem);

	spin_lock(&cmd->context_lock);
	BUG_ON(cmd->मुक्त_head < 0);
	context = &cmd->context[cmd->मुक्त_head];
	context->token += cmd->token_mask + 1;
	cmd->मुक्त_head = context->next;
	spin_unlock(&cmd->context_lock);

	reinit_completion(&context->करोne);

	अगर (mlx4_comm_cmd_post(dev, vhcr_cmd, param)) अणु
		/* Only in हाल the device state is INTERNAL_ERROR,
		 * mlx4_comm_cmd_post वापसs with an error
		 */
		err = mlx4_status_to_त्रुटि_सं(CMD_STAT_INTERNAL_ERR);
		जाओ out;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&context->करोne,
					 msecs_to_jअगरfies(समयout))) अणु
		mlx4_warn(dev, "communication channel command 0x%x (op=0x%x) timed out\n",
			  vhcr_cmd, op);
		जाओ out_reset;
	पूर्ण

	err = context->result;
	अगर (err && context->fw_status != CMD_STAT_MULTI_FUNC_REQ) अणु
		mlx4_err(dev, "command 0x%x failed: fw status = 0x%x\n",
			 vhcr_cmd, context->fw_status);
		अगर (mlx4_closing_cmd_fatal_error(op, context->fw_status))
			जाओ out_reset;
	पूर्ण

	/* रुको क्रम comm channel पढ़ोy
	 * this is necessary क्रम prevention the race
	 * when चयनing between event to polling mode
	 * Skipping this section in हाल the device is in FATAL_ERROR state,
	 * In this state, no commands are sent via the comm channel until
	 * the device has वापसed from reset.
	 */
	अगर (!(dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)) अणु
		end = msecs_to_jअगरfies(समयout) + jअगरfies;
		जबतक (comm_pending(dev) && समय_beक्रमe(jअगरfies, end))
			cond_resched();
	पूर्ण
	जाओ out;

out_reset:
	err = mlx4_status_to_त्रुटि_सं(CMD_STAT_INTERNAL_ERR);
	mlx4_enter_error_state(dev->persist);
out:
	spin_lock(&cmd->context_lock);
	context->next = cmd->मुक्त_head;
	cmd->मुक्त_head = context - cmd->context;
	spin_unlock(&cmd->context_lock);

	up(&cmd->event_sem);
	वापस err;
पूर्ण

पूर्णांक mlx4_comm_cmd(काष्ठा mlx4_dev *dev, u8 cmd, u16 param,
		  u16 op, अचिन्हित दीर्घ समयout)
अणु
	अगर (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
		वापस mlx4_status_to_त्रुटि_सं(CMD_STAT_INTERNAL_ERR);

	अगर (mlx4_priv(dev)->cmd.use_events)
		वापस mlx4_comm_cmd_रुको(dev, cmd, param, op, समयout);
	वापस mlx4_comm_cmd_poll(dev, cmd, param, समयout);
पूर्ण

अटल पूर्णांक cmd_pending(काष्ठा mlx4_dev *dev)
अणु
	u32 status;

	अगर (pci_channel_offline(dev->persist->pdev))
		वापस -EIO;

	status = पढ़ोl(mlx4_priv(dev)->cmd.hcr + HCR_STATUS_OFFSET);

	वापस (status & swab32(1 << HCR_GO_BIT)) ||
		(mlx4_priv(dev)->cmd.toggle ==
		 !!(status & swab32(1 << HCR_T_BIT)));
पूर्ण

अटल पूर्णांक mlx4_cmd_post(काष्ठा mlx4_dev *dev, u64 in_param, u64 out_param,
			 u32 in_modअगरier, u8 op_modअगरier, u16 op, u16 token,
			 पूर्णांक event)
अणु
	काष्ठा mlx4_cmd *cmd = &mlx4_priv(dev)->cmd;
	u32 __iomem *hcr = cmd->hcr;
	पूर्णांक ret = -EIO;
	अचिन्हित दीर्घ end;

	mutex_lock(&dev->persist->device_state_mutex);
	/* To aव्योम writing to unknown addresses after the device state was
	  * changed to पूर्णांकernal error and the chip was reset,
	  * check the INTERNAL_ERROR flag which is updated under
	  * device_state_mutex lock.
	  */
	अगर (pci_channel_offline(dev->persist->pdev) ||
	    (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)) अणु
		/*
		 * Device is going through error recovery
		 * and cannot accept commands.
		 */
		जाओ out;
	पूर्ण

	end = jअगरfies;
	अगर (event)
		end += msecs_to_jअगरfies(GO_BIT_TIMEOUT_MSECS);

	जबतक (cmd_pending(dev)) अणु
		अगर (pci_channel_offline(dev->persist->pdev)) अणु
			/*
			 * Device is going through error recovery
			 * and cannot accept commands.
			 */
			जाओ out;
		पूर्ण

		अगर (समय_after_eq(jअगरfies, end)) अणु
			mlx4_err(dev, "%s:cmd_pending failed\n", __func__);
			जाओ out;
		पूर्ण
		cond_resched();
	पूर्ण

	/*
	 * We use ग_लिखोl (instead of something like स_नकल_toio)
	 * because ग_लिखोs of less than 32 bits to the HCR करोn't work
	 * (and some architectures such as ia64 implement स_नकल_toio
	 * in terms of ग_लिखोb).
	 */
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(in_param >> 32),		  hcr + 0);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(in_param & 0xfffffffful),  hcr + 1);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(in_modअगरier),		  hcr + 2);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(out_param >> 32),	  hcr + 3);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(out_param & 0xfffffffful), hcr + 4);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(token << 16),		  hcr + 5);

	/* __raw_ग_लिखोl may not order ग_लिखोs. */
	wmb();

	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32((1 << HCR_GO_BIT)		|
					       (cmd->toggle << HCR_T_BIT)	|
					       (event ? (1 << HCR_E_BIT) : 0)	|
					       (op_modअगरier << HCR_OPMOD_SHIFT) |
					       op), hcr + 6);

	cmd->toggle = cmd->toggle ^ 1;

	ret = 0;

out:
	अगर (ret)
		mlx4_warn(dev, "Could not post command 0x%x: ret=%d, in_param=0x%llx, in_mod=0x%x, op_mod=0x%x\n",
			  op, ret, in_param, in_modअगरier, op_modअगरier);
	mutex_unlock(&dev->persist->device_state_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_slave_cmd(काष्ठा mlx4_dev *dev, u64 in_param, u64 *out_param,
			  पूर्णांक out_is_imm, u32 in_modअगरier, u8 op_modअगरier,
			  u16 op, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_vhcr_cmd *vhcr = priv->mfunc.vhcr;
	पूर्णांक ret;

	mutex_lock(&priv->cmd.slave_cmd_mutex);

	vhcr->in_param = cpu_to_be64(in_param);
	vhcr->out_param = out_param ? cpu_to_be64(*out_param) : 0;
	vhcr->in_modअगरier = cpu_to_be32(in_modअगरier);
	vhcr->opcode = cpu_to_be16((((u16) op_modअगरier) << 12) | (op & 0xfff));
	vhcr->token = cpu_to_be16(CMD_POLL_TOKEN);
	vhcr->status = 0;
	vhcr->flags = !!(priv->cmd.use_events) << 6;

	अगर (mlx4_is_master(dev)) अणु
		ret = mlx4_master_process_vhcr(dev, dev->caps.function, vhcr);
		अगर (!ret) अणु
			अगर (out_is_imm) अणु
				अगर (out_param)
					*out_param =
						be64_to_cpu(vhcr->out_param);
				अन्यथा अणु
					mlx4_err(dev, "response expected while output mailbox is NULL for command 0x%x\n",
						 op);
					vhcr->status = CMD_STAT_BAD_PARAM;
				पूर्ण
			पूर्ण
			ret = mlx4_status_to_त्रुटि_सं(vhcr->status);
		पूर्ण
		अगर (ret &&
		    dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
			ret = mlx4_पूर्णांकernal_err_ret_value(dev, op, op_modअगरier);
	पूर्ण अन्यथा अणु
		ret = mlx4_comm_cmd(dev, MLX4_COMM_CMD_VHCR_POST, 0, op,
				    MLX4_COMM_TIME + समयout);
		अगर (!ret) अणु
			अगर (out_is_imm) अणु
				अगर (out_param)
					*out_param =
						be64_to_cpu(vhcr->out_param);
				अन्यथा अणु
					mlx4_err(dev, "response expected while output mailbox is NULL for command 0x%x\n",
						 op);
					vhcr->status = CMD_STAT_BAD_PARAM;
				पूर्ण
			पूर्ण
			ret = mlx4_status_to_त्रुटि_सं(vhcr->status);
		पूर्ण अन्यथा अणु
			अगर (dev->persist->state &
			    MLX4_DEVICE_STATE_INTERNAL_ERROR)
				ret = mlx4_पूर्णांकernal_err_ret_value(dev, op,
								  op_modअगरier);
			अन्यथा
				mlx4_err(dev, "failed execution of VHCR_POST command opcode 0x%x\n", op);
		पूर्ण
	पूर्ण

	mutex_unlock(&priv->cmd.slave_cmd_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_cmd_poll(काष्ठा mlx4_dev *dev, u64 in_param, u64 *out_param,
			 पूर्णांक out_is_imm, u32 in_modअगरier, u8 op_modअगरier,
			 u16 op, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	व्योम __iomem *hcr = priv->cmd.hcr;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ end;
	u32 stat;

	करोwn(&priv->cmd.poll_sem);

	अगर (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR) अणु
		/*
		 * Device is going through error recovery
		 * and cannot accept commands.
		 */
		err = mlx4_पूर्णांकernal_err_ret_value(dev, op, op_modअगरier);
		जाओ out;
	पूर्ण

	अगर (out_is_imm && !out_param) अणु
		mlx4_err(dev, "response expected while output mailbox is NULL for command 0x%x\n",
			 op);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = mlx4_cmd_post(dev, in_param, out_param ? *out_param : 0,
			    in_modअगरier, op_modअगरier, op, CMD_POLL_TOKEN, 0);
	अगर (err)
		जाओ out_reset;

	end = msecs_to_jअगरfies(समयout) + jअगरfies;
	जबतक (cmd_pending(dev) && समय_beक्रमe(jअगरfies, end)) अणु
		अगर (pci_channel_offline(dev->persist->pdev)) अणु
			/*
			 * Device is going through error recovery
			 * and cannot accept commands.
			 */
			err = -EIO;
			जाओ out_reset;
		पूर्ण

		अगर (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR) अणु
			err = mlx4_पूर्णांकernal_err_ret_value(dev, op, op_modअगरier);
			जाओ out;
		पूर्ण

		cond_resched();
	पूर्ण

	अगर (cmd_pending(dev)) अणु
		mlx4_warn(dev, "command 0x%x timed out (go bit not cleared)\n",
			  op);
		err = -EIO;
		जाओ out_reset;
	पूर्ण

	अगर (out_is_imm)
		*out_param =
			(u64) be32_to_cpu((__क्रमce __be32)
					  __raw_पढ़ोl(hcr + HCR_OUT_PARAM_OFFSET)) << 32 |
			(u64) be32_to_cpu((__क्रमce __be32)
					  __raw_पढ़ोl(hcr + HCR_OUT_PARAM_OFFSET + 4));
	stat = be32_to_cpu((__क्रमce __be32)
			   __raw_पढ़ोl(hcr + HCR_STATUS_OFFSET)) >> 24;
	err = mlx4_status_to_त्रुटि_सं(stat);
	अगर (err) अणु
		mlx4_err(dev, "command 0x%x failed: fw status = 0x%x\n",
			 op, stat);
		अगर (mlx4_closing_cmd_fatal_error(op, stat))
			जाओ out_reset;
		जाओ out;
	पूर्ण

out_reset:
	अगर (err)
		err = mlx4_cmd_reset_flow(dev, op, op_modअगरier, err);
out:
	up(&priv->cmd.poll_sem);
	वापस err;
पूर्ण

व्योम mlx4_cmd_event(काष्ठा mlx4_dev *dev, u16 token, u8 status, u64 out_param)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cmd_context *context =
		&priv->cmd.context[token & priv->cmd.token_mask];

	/* previously समयd out command completing at दीर्घ last */
	अगर (token != context->token)
		वापस;

	context->fw_status = status;
	context->result    = mlx4_status_to_त्रुटि_सं(status);
	context->out_param = out_param;

	complete(&context->करोne);
पूर्ण

अटल पूर्णांक mlx4_cmd_रुको(काष्ठा mlx4_dev *dev, u64 in_param, u64 *out_param,
			 पूर्णांक out_is_imm, u32 in_modअगरier, u8 op_modअगरier,
			 u16 op, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा mlx4_cmd *cmd = &mlx4_priv(dev)->cmd;
	काष्ठा mlx4_cmd_context *context;
	दीर्घ ret_रुको;
	पूर्णांक err = 0;

	करोwn(&cmd->event_sem);

	spin_lock(&cmd->context_lock);
	BUG_ON(cmd->मुक्त_head < 0);
	context = &cmd->context[cmd->मुक्त_head];
	context->token += cmd->token_mask + 1;
	cmd->मुक्त_head = context->next;
	spin_unlock(&cmd->context_lock);

	अगर (out_is_imm && !out_param) अणु
		mlx4_err(dev, "response expected while output mailbox is NULL for command 0x%x\n",
			 op);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	reinit_completion(&context->करोne);

	err = mlx4_cmd_post(dev, in_param, out_param ? *out_param : 0,
			    in_modअगरier, op_modअगरier, op, context->token, 1);
	अगर (err)
		जाओ out_reset;

	अगर (op == MLX4_CMD_SENSE_PORT) अणु
		ret_रुको =
			रुको_क्रम_completion_पूर्णांकerruptible_समयout(&context->करोne,
								  msecs_to_jअगरfies(समयout));
		अगर (ret_रुको < 0) अणु
			context->fw_status = 0;
			context->out_param = 0;
			context->result = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret_रुको = (दीर्घ)रुको_क्रम_completion_समयout(&context->करोne,
							     msecs_to_jअगरfies(समयout));
	पूर्ण
	अगर (!ret_रुको) अणु
		mlx4_warn(dev, "command 0x%x timed out (go bit not cleared)\n",
			  op);
		अगर (op == MLX4_CMD_NOP) अणु
			err = -EBUSY;
			जाओ out;
		पूर्ण अन्यथा अणु
			err = -EIO;
			जाओ out_reset;
		पूर्ण
	पूर्ण

	err = context->result;
	अगर (err) अणु
		/* Since we करो not want to have this error message always
		 * displayed at driver start when there are ConnectX2 HCAs
		 * on the host, we deprecate the error message क्रम this
		 * specअगरic command/input_mod/opcode_mod/fw-status to be debug.
		 */
		अगर (op == MLX4_CMD_SET_PORT &&
		    (in_modअगरier == 1 || in_modअगरier == 2) &&
		    op_modअगरier == MLX4_SET_PORT_IB_OPCODE &&
		    context->fw_status == CMD_STAT_BAD_SIZE)
			mlx4_dbg(dev, "command 0x%x failed: fw status = 0x%x\n",
				 op, context->fw_status);
		अन्यथा
			mlx4_err(dev, "command 0x%x failed: fw status = 0x%x\n",
				 op, context->fw_status);
		अगर (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
			err = mlx4_पूर्णांकernal_err_ret_value(dev, op, op_modअगरier);
		अन्यथा अगर (mlx4_closing_cmd_fatal_error(op, context->fw_status))
			जाओ out_reset;

		जाओ out;
	पूर्ण

	अगर (out_is_imm)
		*out_param = context->out_param;

out_reset:
	अगर (err)
		err = mlx4_cmd_reset_flow(dev, op, op_modअगरier, err);
out:
	spin_lock(&cmd->context_lock);
	context->next = cmd->मुक्त_head;
	cmd->मुक्त_head = context - cmd->context;
	spin_unlock(&cmd->context_lock);

	up(&cmd->event_sem);
	वापस err;
पूर्ण

पूर्णांक __mlx4_cmd(काष्ठा mlx4_dev *dev, u64 in_param, u64 *out_param,
	       पूर्णांक out_is_imm, u32 in_modअगरier, u8 op_modअगरier,
	       u16 op, अचिन्हित दीर्घ समयout, पूर्णांक native)
अणु
	अगर (pci_channel_offline(dev->persist->pdev))
		वापस mlx4_cmd_reset_flow(dev, op, op_modअगरier, -EIO);

	अगर (!mlx4_is_mfunc(dev) || (native && mlx4_is_master(dev))) अणु
		पूर्णांक ret;

		अगर (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
			वापस mlx4_पूर्णांकernal_err_ret_value(dev, op,
							  op_modअगरier);
		करोwn_पढ़ो(&mlx4_priv(dev)->cmd.चयन_sem);
		अगर (mlx4_priv(dev)->cmd.use_events)
			ret = mlx4_cmd_रुको(dev, in_param, out_param,
					    out_is_imm, in_modअगरier,
					    op_modअगरier, op, समयout);
		अन्यथा
			ret = mlx4_cmd_poll(dev, in_param, out_param,
					    out_is_imm, in_modअगरier,
					    op_modअगरier, op, समयout);

		up_पढ़ो(&mlx4_priv(dev)->cmd.चयन_sem);
		वापस ret;
	पूर्ण
	वापस mlx4_slave_cmd(dev, in_param, out_param, out_is_imm,
			      in_modअगरier, op_modअगरier, op, समयout);
पूर्ण
EXPORT_SYMBOL_GPL(__mlx4_cmd);


पूर्णांक mlx4_ARM_COMM_CHANNEL(काष्ठा mlx4_dev *dev)
अणु
	वापस mlx4_cmd(dev, 0, 0, 0, MLX4_CMD_ARM_COMM_CHANNEL,
			MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
पूर्ण

अटल पूर्णांक mlx4_ACCESS_MEM(काष्ठा mlx4_dev *dev, u64 master_addr,
			   पूर्णांक slave, u64 slave_addr,
			   पूर्णांक size, पूर्णांक is_पढ़ो)
अणु
	u64 in_param;
	u64 out_param;

	अगर ((slave_addr & 0xfff) | (master_addr & 0xfff) |
	    (slave & ~0x7f) | (size & 0xff)) अणु
		mlx4_err(dev, "Bad access mem params - slave_addr:0x%llx master_addr:0x%llx slave_id:%d size:%d\n",
			 slave_addr, master_addr, slave, size);
		वापस -EINVAL;
	पूर्ण

	अगर (is_पढ़ो) अणु
		in_param = (u64) slave | slave_addr;
		out_param = (u64) dev->caps.function | master_addr;
	पूर्ण अन्यथा अणु
		in_param = (u64) dev->caps.function | master_addr;
		out_param = (u64) slave | slave_addr;
	पूर्ण

	वापस mlx4_cmd_imm(dev, in_param, &out_param, size, 0,
			    MLX4_CMD_ACCESS_MEM,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
पूर्ण

अटल पूर्णांक query_pkey_block(काष्ठा mlx4_dev *dev, u8 port, u16 index, u16 *pkey,
			       काष्ठा mlx4_cmd_mailbox *inbox,
			       काष्ठा mlx4_cmd_mailbox *outbox)
अणु
	काष्ठा ib_smp *in_mad = (काष्ठा ib_smp *)(inbox->buf);
	काष्ठा ib_smp *out_mad = (काष्ठा ib_smp *)(outbox->buf);
	पूर्णांक err;
	पूर्णांक i;

	अगर (index & 0x1f)
		वापस -EINVAL;

	in_mad->attr_mod = cpu_to_be32(index / 32);

	err = mlx4_cmd_box(dev, inbox->dma, outbox->dma, port, 3,
			   MLX4_CMD_MAD_IFC, MLX4_CMD_TIME_CLASS_C,
			   MLX4_CMD_NATIVE);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < 32; ++i)
		pkey[i] = be16_to_cpu(((__be16 *) out_mad->data)[i]);

	वापस err;
पूर्ण

अटल पूर्णांक get_full_pkey_table(काष्ठा mlx4_dev *dev, u8 port, u16 *table,
			       काष्ठा mlx4_cmd_mailbox *inbox,
			       काष्ठा mlx4_cmd_mailbox *outbox)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < dev->caps.pkey_table_len[port]; i += 32) अणु
		err = query_pkey_block(dev, port, i, table + i, inbox, outbox);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
#घोषणा PORT_CAPABILITY_LOCATION_IN_SMP 20
#घोषणा PORT_STATE_OFFSET 32

अटल क्रमागत ib_port_state vf_port_state(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक vf)
अणु
	अगर (mlx4_get_slave_port_state(dev, vf, port) == SLAVE_PORT_UP)
		वापस IB_PORT_ACTIVE;
	अन्यथा
		वापस IB_PORT_DOWN;
पूर्ण

अटल पूर्णांक mlx4_MAD_IFC_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				काष्ठा mlx4_vhcr *vhcr,
				काष्ठा mlx4_cmd_mailbox *inbox,
				काष्ठा mlx4_cmd_mailbox *outbox,
				काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा ib_smp *smp = inbox->buf;
	u32 index;
	u8 port, slave_port;
	u8 opcode_modअगरier;
	u16 *table;
	पूर्णांक err;
	पूर्णांक vidx, pidx;
	पूर्णांक network_view;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा ib_smp *outsmp = outbox->buf;
	__be16 *outtab = (__be16 *)(outsmp->data);
	__be32 slave_cap_mask;
	__be64 slave_node_guid;

	slave_port = vhcr->in_modअगरier;
	port = mlx4_slave_convert_port(dev, slave, slave_port);

	/* network-view bit is क्रम driver use only, and should not be passed to FW */
	opcode_modअगरier = vhcr->op_modअगरier & ~0x8; /* clear netw view bit */
	network_view = !!(vhcr->op_modअगरier & 0x8);

	अगर (smp->base_version == 1 &&
	    smp->mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED &&
	    smp->class_version == 1) अणु
		/* host view is paraभवized */
		अगर (!network_view && smp->method == IB_MGMT_METHOD_GET) अणु
			अगर (smp->attr_id == IB_SMP_ATTR_PKEY_TABLE) अणु
				index = be32_to_cpu(smp->attr_mod);
				अगर (port < 1 || port > dev->caps.num_ports)
					वापस -EINVAL;
				table = kसुस्मृति((dev->caps.pkey_table_len[port] / 32) + 1,
						माप(*table) * 32, GFP_KERNEL);

				अगर (!table)
					वापस -ENOMEM;
				/* need to get the full pkey table because the paraभवized
				 * pkeys may be scattered among several pkey blocks.
				 */
				err = get_full_pkey_table(dev, port, table, inbox, outbox);
				अगर (!err) अणु
					क्रम (vidx = index * 32; vidx < (index + 1) * 32; ++vidx) अणु
						pidx = priv->virt2phys_pkey[slave][port - 1][vidx];
						outtab[vidx % 32] = cpu_to_be16(table[pidx]);
					पूर्ण
				पूर्ण
				kमुक्त(table);
				वापस err;
			पूर्ण
			अगर (smp->attr_id == IB_SMP_ATTR_PORT_INFO) अणु
				/*get the slave specअगरic caps:*/
				/*करो the command */
				smp->attr_mod = cpu_to_be32(port);
				err = mlx4_cmd_box(dev, inbox->dma, outbox->dma,
					    port, opcode_modअगरier,
					    vhcr->op, MLX4_CMD_TIME_CLASS_C, MLX4_CMD_NATIVE);
				/* modअगरy the response क्रम slaves */
				अगर (!err && slave != mlx4_master_func_num(dev)) अणु
					u8 *state = outsmp->data + PORT_STATE_OFFSET;

					*state = (*state & 0xf0) | vf_port_state(dev, port, slave);
					slave_cap_mask = priv->mfunc.master.slave_state[slave].ib_cap_mask[port];
					स_नकल(outsmp->data + PORT_CAPABILITY_LOCATION_IN_SMP, &slave_cap_mask, 4);
				पूर्ण
				वापस err;
			पूर्ण
			अगर (smp->attr_id == IB_SMP_ATTR_GUID_INFO) अणु
				__be64 guid = mlx4_get_admin_guid(dev, slave,
								  port);

				/* set the PF admin guid to the FW/HW burned
				 * GUID, अगर it wasn't yet set
				 */
				अगर (slave == 0 && guid == 0) अणु
					smp->attr_mod = 0;
					err = mlx4_cmd_box(dev,
							   inbox->dma,
							   outbox->dma,
							   vhcr->in_modअगरier,
							   opcode_modअगरier,
							   vhcr->op,
							   MLX4_CMD_TIME_CLASS_C,
							   MLX4_CMD_NATIVE);
					अगर (err)
						वापस err;
					mlx4_set_admin_guid(dev,
							    *(__be64 *)outsmp->
							    data, slave, port);
				पूर्ण अन्यथा अणु
					स_नकल(outsmp->data, &guid, 8);
				पूर्ण

				/* clean all other gids */
				स_रखो(outsmp->data + 8, 0, 56);
				वापस 0;
			पूर्ण
			अगर (smp->attr_id == IB_SMP_ATTR_NODE_INFO) अणु
				err = mlx4_cmd_box(dev, inbox->dma, outbox->dma,
					     port, opcode_modअगरier,
					     vhcr->op, MLX4_CMD_TIME_CLASS_C, MLX4_CMD_NATIVE);
				अगर (!err) अणु
					slave_node_guid =  mlx4_get_slave_node_guid(dev, slave);
					स_नकल(outsmp->data + 12, &slave_node_guid, 8);
				पूर्ण
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Non-privileged VFs are only allowed "host" view LID-routed 'Get' MADs.
	 * These are the MADs used by ib verbs (such as ib_query_gids).
	 */
	अगर (slave != mlx4_master_func_num(dev) &&
	    !mlx4_vf_smi_enabled(dev, slave, port)) अणु
		अगर (!(smp->mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED &&
		      smp->method == IB_MGMT_METHOD_GET) || network_view) अणु
			mlx4_err(dev, "Unprivileged slave %d is trying to execute a Subnet MGMT MAD, class 0x%x, method 0x%x, view=%s for attr 0x%x. Rejecting\n",
				 slave, smp->mgmt_class, smp->method,
				 network_view ? "Network" : "Host",
				 be16_to_cpu(smp->attr_id));
			वापस -EPERM;
		पूर्ण
	पूर्ण

	वापस mlx4_cmd_box(dev, inbox->dma, outbox->dma,
				    vhcr->in_modअगरier, opcode_modअगरier,
				    vhcr->op, MLX4_CMD_TIME_CLASS_C, MLX4_CMD_NATIVE);
पूर्ण

अटल पूर्णांक mlx4_CMD_EPERM_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
		     काष्ठा mlx4_vhcr *vhcr,
		     काष्ठा mlx4_cmd_mailbox *inbox,
		     काष्ठा mlx4_cmd_mailbox *outbox,
		     काष्ठा mlx4_cmd_info *cmd)
अणु
	वापस -EPERM;
पूर्ण

पूर्णांक mlx4_DMA_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
		     काष्ठा mlx4_vhcr *vhcr,
		     काष्ठा mlx4_cmd_mailbox *inbox,
		     काष्ठा mlx4_cmd_mailbox *outbox,
		     काष्ठा mlx4_cmd_info *cmd)
अणु
	u64 in_param;
	u64 out_param;
	पूर्णांक err;

	in_param = cmd->has_inbox ? (u64) inbox->dma : vhcr->in_param;
	out_param = cmd->has_outbox ? (u64) outbox->dma : vhcr->out_param;
	अगर (cmd->encode_slave_id) अणु
		in_param &= 0xffffffffffffff00ll;
		in_param |= slave;
	पूर्ण

	err = __mlx4_cmd(dev, in_param, &out_param, cmd->out_is_imm,
			 vhcr->in_modअगरier, vhcr->op_modअगरier, vhcr->op,
			 MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);

	अगर (cmd->out_is_imm)
		vhcr->out_param = out_param;

	वापस err;
पूर्ण

अटल काष्ठा mlx4_cmd_info cmd_info[] = अणु
	अणु
		.opcode = MLX4_CMD_QUERY_FW,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QUERY_FW_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_HCA,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = शून्य
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_DEV_CAP,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QUERY_DEV_CAP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_FUNC_CAP,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QUERY_FUNC_CAP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_ADAPTER,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = शून्य
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_INIT_PORT,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_INIT_PORT_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_CLOSE_PORT,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm  = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_CLOSE_PORT_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_PORT,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QUERY_PORT_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SET_PORT,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_SET_PORT_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_MAP_EQ,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_MAP_EQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SW2HW_EQ,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = true,
		.verअगरy = शून्य,
		.wrapper = mlx4_SW2HW_EQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_HW_HEALTH_CHECK,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = शून्य
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_NOP,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = शून्य
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_CONFIG_DEV,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_CONFIG_DEV_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_ALLOC_RES,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = true,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_ALLOC_RES_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_FREE_RES,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_FREE_RES_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SW2HW_MPT,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = true,
		.verअगरy = शून्य,
		.wrapper = mlx4_SW2HW_MPT_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_MPT,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QUERY_MPT_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_HW2SW_MPT,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_HW2SW_MPT_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_READ_MTT,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = शून्य
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_WRITE_MTT,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_WRITE_MTT_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SYNC_TPT,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = शून्य
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_HW2SW_EQ,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = true,
		.verअगरy = शून्य,
		.wrapper = mlx4_HW2SW_EQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_EQ,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = true,
		.verअगरy = शून्य,
		.wrapper = mlx4_QUERY_EQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SW2HW_CQ,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = true,
		.verअगरy = शून्य,
		.wrapper = mlx4_SW2HW_CQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_HW2SW_CQ,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_HW2SW_CQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_CQ,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QUERY_CQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_MODIFY_CQ,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = true,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_MODIFY_CQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SW2HW_SRQ,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = true,
		.verअगरy = शून्य,
		.wrapper = mlx4_SW2HW_SRQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_HW2SW_SRQ,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_HW2SW_SRQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_SRQ,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QUERY_SRQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_ARM_SRQ,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_ARM_SRQ_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_RST2INIT_QP,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = true,
		.verअगरy = शून्य,
		.wrapper = mlx4_RST2INIT_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_INIT2INIT_QP,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_INIT2INIT_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_INIT2RTR_QP,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_INIT2RTR_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_RTR2RTS_QP,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_RTR2RTS_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_RTS2RTS_QP,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_RTS2RTS_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SQERR2RTS_QP,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_SQERR2RTS_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_2ERR_QP,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_GEN_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_RTS2SQD_QP,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_GEN_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SQD2SQD_QP,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_SQD2SQD_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SQD2RTS_QP,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_SQD2RTS_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_2RST_QP,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_2RST_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_QP,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_GEN_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SUSPEND_QP,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_GEN_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_UNSUSPEND_QP,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_GEN_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_UPDATE_QP,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_UPDATE_QP_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_GET_OP_REQ,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_CMD_EPERM_wrapper,
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_ALLOCATE_VPP,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_CMD_EPERM_wrapper,
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SET_VPORT_QOS,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_CMD_EPERM_wrapper,
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_CONF_SPECIAL_QP,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य, /* XXX verअगरy: only demux can करो this */
		.wrapper = शून्य
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_MAD_IFC,
		.has_inbox = true,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_MAD_IFC_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_MAD_DEMUX,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_CMD_EPERM_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_QUERY_IF_STAT,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QUERY_IF_STAT_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_ACCESS_REG,
		.has_inbox = true,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_ACCESS_REG_wrapper,
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_CONGESTION_CTRL_OPCODE,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_CMD_EPERM_wrapper,
	पूर्ण,
	/* Native multicast commands are not available क्रम guests */
	अणु
		.opcode = MLX4_CMD_QP_ATTACH,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QP_ATTACH_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_PROMISC,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_PROMISC_wrapper
	पूर्ण,
	/* Ethernet specअगरic commands */
	अणु
		.opcode = MLX4_CMD_SET_VLAN_FLTR,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_SET_VLAN_FLTR_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_SET_MCAST_FLTR,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_SET_MCAST_FLTR_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_DUMP_ETH_STATS,
		.has_inbox = false,
		.has_outbox = true,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_DUMP_ETH_STATS_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_INFORM_FLR_DONE,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = शून्य
	पूर्ण,
	/* flow steering commands */
	अणु
		.opcode = MLX4_QP_FLOW_STEERING_ATTACH,
		.has_inbox = true,
		.has_outbox = false,
		.out_is_imm = true,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QP_FLOW_STEERING_ATTACH_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_QP_FLOW_STEERING_DETACH,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_QP_FLOW_STEERING_DETACH_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_FLOW_STEERING_IB_UC_QP_RANGE,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_CMD_EPERM_wrapper
	पूर्ण,
	अणु
		.opcode = MLX4_CMD_VIRT_PORT_MAP,
		.has_inbox = false,
		.has_outbox = false,
		.out_is_imm = false,
		.encode_slave_id = false,
		.verअगरy = शून्य,
		.wrapper = mlx4_CMD_EPERM_wrapper
	पूर्ण,
पूर्ण;

अटल पूर्णांक mlx4_master_process_vhcr(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				    काष्ठा mlx4_vhcr_cmd *in_vhcr)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cmd_info *cmd = शून्य;
	काष्ठा mlx4_vhcr_cmd *vhcr_cmd = in_vhcr ? in_vhcr : priv->mfunc.vhcr;
	काष्ठा mlx4_vhcr *vhcr;
	काष्ठा mlx4_cmd_mailbox *inbox = शून्य;
	काष्ठा mlx4_cmd_mailbox *outbox = शून्य;
	u64 in_param;
	u64 out_param;
	पूर्णांक ret = 0;
	पूर्णांक i;
	पूर्णांक err = 0;

	/* Create sw representation of Virtual HCR */
	vhcr = kzalloc(माप(काष्ठा mlx4_vhcr), GFP_KERNEL);
	अगर (!vhcr)
		वापस -ENOMEM;

	/* DMA in the vHCR */
	अगर (!in_vhcr) अणु
		ret = mlx4_ACCESS_MEM(dev, priv->mfunc.vhcr_dma, slave,
				      priv->mfunc.master.slave_state[slave].vhcr_dma,
				      ALIGN(माप(काष्ठा mlx4_vhcr_cmd),
					    MLX4_ACCESS_MEM_ALIGN), 1);
		अगर (ret) अणु
			अगर (!(dev->persist->state &
			    MLX4_DEVICE_STATE_INTERNAL_ERROR))
				mlx4_err(dev, "%s: Failed reading vhcr ret: 0x%x\n",
					 __func__, ret);
			kमुक्त(vhcr);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Fill SW VHCR fields */
	vhcr->in_param = be64_to_cpu(vhcr_cmd->in_param);
	vhcr->out_param = be64_to_cpu(vhcr_cmd->out_param);
	vhcr->in_modअगरier = be32_to_cpu(vhcr_cmd->in_modअगरier);
	vhcr->token = be16_to_cpu(vhcr_cmd->token);
	vhcr->op = be16_to_cpu(vhcr_cmd->opcode) & 0xfff;
	vhcr->op_modअगरier = (u8) (be16_to_cpu(vhcr_cmd->opcode) >> 12);
	vhcr->e_bit = vhcr_cmd->flags & (1 << 6);

	/* Lookup command */
	क्रम (i = 0; i < ARRAY_SIZE(cmd_info); ++i) अणु
		अगर (vhcr->op == cmd_info[i].opcode) अणु
			cmd = &cmd_info[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!cmd) अणु
		mlx4_err(dev, "Unknown command:0x%x accepted from slave:%d\n",
			 vhcr->op, slave);
		vhcr_cmd->status = CMD_STAT_BAD_PARAM;
		जाओ out_status;
	पूर्ण

	/* Read inbox */
	अगर (cmd->has_inbox) अणु
		vhcr->in_param &= INBOX_MASK;
		inbox = mlx4_alloc_cmd_mailbox(dev);
		अगर (IS_ERR(inbox)) अणु
			vhcr_cmd->status = CMD_STAT_BAD_SIZE;
			inbox = शून्य;
			जाओ out_status;
		पूर्ण

		ret = mlx4_ACCESS_MEM(dev, inbox->dma, slave,
				      vhcr->in_param,
				      MLX4_MAILBOX_SIZE, 1);
		अगर (ret) अणु
			अगर (!(dev->persist->state &
			    MLX4_DEVICE_STATE_INTERNAL_ERROR))
				mlx4_err(dev, "%s: Failed reading inbox (cmd:0x%x)\n",
					 __func__, cmd->opcode);
			vhcr_cmd->status = CMD_STAT_INTERNAL_ERR;
			जाओ out_status;
		पूर्ण
	पूर्ण

	/* Apply permission and bound checks अगर applicable */
	अगर (cmd->verअगरy && cmd->verअगरy(dev, slave, vhcr, inbox)) अणु
		mlx4_warn(dev, "Command:0x%x from slave: %d failed protection checks for resource_id:%d\n",
			  vhcr->op, slave, vhcr->in_modअगरier);
		vhcr_cmd->status = CMD_STAT_BAD_OP;
		जाओ out_status;
	पूर्ण

	/* Allocate outbox */
	अगर (cmd->has_outbox) अणु
		outbox = mlx4_alloc_cmd_mailbox(dev);
		अगर (IS_ERR(outbox)) अणु
			vhcr_cmd->status = CMD_STAT_BAD_SIZE;
			outbox = शून्य;
			जाओ out_status;
		पूर्ण
	पूर्ण

	/* Execute the command! */
	अगर (cmd->wrapper) अणु
		err = cmd->wrapper(dev, slave, vhcr, inbox, outbox,
				   cmd);
		अगर (cmd->out_is_imm)
			vhcr_cmd->out_param = cpu_to_be64(vhcr->out_param);
	पूर्ण अन्यथा अणु
		in_param = cmd->has_inbox ? (u64) inbox->dma :
			vhcr->in_param;
		out_param = cmd->has_outbox ? (u64) outbox->dma :
			vhcr->out_param;
		err = __mlx4_cmd(dev, in_param, &out_param,
				 cmd->out_is_imm, vhcr->in_modअगरier,
				 vhcr->op_modअगरier, vhcr->op,
				 MLX4_CMD_TIME_CLASS_A,
				 MLX4_CMD_NATIVE);

		अगर (cmd->out_is_imm) अणु
			vhcr->out_param = out_param;
			vhcr_cmd->out_param = cpu_to_be64(vhcr->out_param);
		पूर्ण
	पूर्ण

	अगर (err) अणु
		अगर (!(dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)) अणु
			अगर (vhcr->op == MLX4_CMD_ALLOC_RES &&
			    (vhcr->in_modअगरier & 0xff) == RES_COUNTER &&
			    err == -EDQUOT)
				mlx4_dbg(dev,
					 "Unable to allocate counter for slave %d (%d)\n",
					 slave, err);
			अन्यथा
				mlx4_warn(dev, "vhcr command:0x%x slave:%d failed with error:%d, status %d\n",
					  vhcr->op, slave, vhcr->त्रुटि_सं, err);
		पूर्ण
		vhcr_cmd->status = mlx4_त्रुटि_सं_to_status(err);
		जाओ out_status;
	पूर्ण


	/* Write outbox अगर command completed successfully */
	अगर (cmd->has_outbox && !vhcr_cmd->status) अणु
		ret = mlx4_ACCESS_MEM(dev, outbox->dma, slave,
				      vhcr->out_param,
				      MLX4_MAILBOX_SIZE, MLX4_CMD_WRAPPED);
		अगर (ret) अणु
			/* If we failed to ग_लिखो back the outbox after the
			 *command was successfully executed, we must fail this
			 * slave, as it is now in undefined state */
			अगर (!(dev->persist->state &
			    MLX4_DEVICE_STATE_INTERNAL_ERROR))
				mlx4_err(dev, "%s:Failed writing outbox\n", __func__);
			जाओ out;
		पूर्ण
	पूर्ण

out_status:
	/* DMA back vhcr result */
	अगर (!in_vhcr) अणु
		ret = mlx4_ACCESS_MEM(dev, priv->mfunc.vhcr_dma, slave,
				      priv->mfunc.master.slave_state[slave].vhcr_dma,
				      ALIGN(माप(काष्ठा mlx4_vhcr),
					    MLX4_ACCESS_MEM_ALIGN),
				      MLX4_CMD_WRAPPED);
		अगर (ret)
			mlx4_err(dev, "%s:Failed writing vhcr result\n",
				 __func__);
		अन्यथा अगर (vhcr->e_bit &&
			 mlx4_GEN_EQE(dev, slave, &priv->mfunc.master.cmd_eqe))
				mlx4_warn(dev, "Failed to generate command completion eqe for slave %d\n",
					  slave);
	पूर्ण

out:
	kमुक्त(vhcr);
	mlx4_मुक्त_cmd_mailbox(dev, inbox);
	mlx4_मुक्त_cmd_mailbox(dev, outbox);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_master_immediate_activate_vlan_qos(काष्ठा mlx4_priv *priv,
					    पूर्णांक slave, पूर्णांक port)
अणु
	काष्ठा mlx4_vport_oper_state *vp_oper;
	काष्ठा mlx4_vport_state *vp_admin;
	काष्ठा mlx4_vf_immed_vlan_work *work;
	काष्ठा mlx4_dev *dev = &(priv->dev);
	पूर्णांक err;
	पूर्णांक admin_vlan_ix = NO_INDX;

	vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
	vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];

	अगर (vp_oper->state.शेष_vlan == vp_admin->शेष_vlan &&
	    vp_oper->state.शेष_qos == vp_admin->शेष_qos &&
	    vp_oper->state.vlan_proto == vp_admin->vlan_proto &&
	    vp_oper->state.link_state == vp_admin->link_state &&
	    vp_oper->state.qos_vport == vp_admin->qos_vport)
		वापस 0;

	अगर (!(priv->mfunc.master.slave_state[slave].active &&
	      dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_UPDATE_QP)) अणु
		/* even अगर the UPDATE_QP command isn't supported, we still want
		 * to set this VF link according to the admin directive
		 */
		vp_oper->state.link_state = vp_admin->link_state;
		वापस -1;
	पूर्ण

	mlx4_dbg(dev, "updating immediately admin params slave %d port %d\n",
		 slave, port);
	mlx4_dbg(dev, "vlan %d QoS %d link down %d\n",
		 vp_admin->शेष_vlan, vp_admin->शेष_qos,
		 vp_admin->link_state);

	work = kzalloc(माप(*work), GFP_KERNEL);
	अगर (!work)
		वापस -ENOMEM;

	अगर (vp_oper->state.शेष_vlan != vp_admin->शेष_vlan) अणु
		अगर (MLX4_VGT != vp_admin->शेष_vlan) अणु
			err = __mlx4_रेजिस्टर_vlan(&priv->dev, port,
						   vp_admin->शेष_vlan,
						   &admin_vlan_ix);
			अगर (err) अणु
				kमुक्त(work);
				mlx4_warn(&priv->dev,
					  "No vlan resources slave %d, port %d\n",
					  slave, port);
				वापस err;
			पूर्ण
		पूर्ण अन्यथा अणु
			admin_vlan_ix = NO_INDX;
		पूर्ण
		work->flags |= MLX4_VF_IMMED_VLAN_FLAG_VLAN;
		mlx4_dbg(&priv->dev,
			 "alloc vlan %d idx  %d slave %d port %d\n",
			 (पूर्णांक)(vp_admin->शेष_vlan),
			 admin_vlan_ix, slave, port);
	पूर्ण

	/* save original vlan ix and vlan id */
	work->orig_vlan_id = vp_oper->state.शेष_vlan;
	work->orig_vlan_ix = vp_oper->vlan_idx;

	/* handle new qos */
	अगर (vp_oper->state.शेष_qos != vp_admin->शेष_qos)
		work->flags |= MLX4_VF_IMMED_VLAN_FLAG_QOS;

	अगर (work->flags & MLX4_VF_IMMED_VLAN_FLAG_VLAN)
		vp_oper->vlan_idx = admin_vlan_ix;

	vp_oper->state.शेष_vlan = vp_admin->शेष_vlan;
	vp_oper->state.शेष_qos = vp_admin->शेष_qos;
	vp_oper->state.vlan_proto = vp_admin->vlan_proto;
	vp_oper->state.link_state = vp_admin->link_state;
	vp_oper->state.qos_vport = vp_admin->qos_vport;

	अगर (vp_admin->link_state == IFLA_VF_LINK_STATE_DISABLE)
		work->flags |= MLX4_VF_IMMED_VLAN_FLAG_LINK_DISABLE;

	/* iterate over QPs owned by this slave, using UPDATE_QP */
	work->port = port;
	work->slave = slave;
	work->qos = vp_oper->state.शेष_qos;
	work->qos_vport = vp_oper->state.qos_vport;
	work->vlan_id = vp_oper->state.शेष_vlan;
	work->vlan_ix = vp_oper->vlan_idx;
	work->vlan_proto = vp_oper->state.vlan_proto;
	work->priv = priv;
	INIT_WORK(&work->work, mlx4_vf_immed_vlan_work_handler);
	queue_work(priv->mfunc.master.comm_wq, &work->work);

	वापस 0;
पूर्ण

अटल व्योम mlx4_set_शेष_port_qos(काष्ठा mlx4_dev *dev, पूर्णांक port)
अणु
	काष्ठा mlx4_qos_manager *port_qos_ctl;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	port_qos_ctl = &priv->mfunc.master.qos_ctl[port];
	biपंचांगap_zero(port_qos_ctl->priority_bm, MLX4_NUM_UP);

	/* Enable only शेष prio at PF init routine */
	set_bit(MLX4_DEFAULT_QOS_PRIO, port_qos_ctl->priority_bm);
पूर्ण

अटल व्योम mlx4_allocate_port_vpps(काष्ठा mlx4_dev *dev, पूर्णांक port)
अणु
	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक num_vfs;
	u16 available_vpp;
	u8 vpp_param[MLX4_NUM_UP];
	काष्ठा mlx4_qos_manager *port_qos;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	err = mlx4_ALLOCATE_VPP_get(dev, port, &available_vpp, vpp_param);
	अगर (err) अणु
		mlx4_info(dev, "Failed query available VPPs\n");
		वापस;
	पूर्ण

	port_qos = &priv->mfunc.master.qos_ctl[port];
	num_vfs = (available_vpp /
		   biपंचांगap_weight(port_qos->priority_bm, MLX4_NUM_UP));

	क्रम (i = 0; i < MLX4_NUM_UP; i++) अणु
		अगर (test_bit(i, port_qos->priority_bm))
			vpp_param[i] = num_vfs;
	पूर्ण

	err = mlx4_ALLOCATE_VPP_set(dev, port, vpp_param);
	अगर (err) अणु
		mlx4_info(dev, "Failed allocating VPPs\n");
		वापस;
	पूर्ण

	/* Query actual allocated VPP, just to make sure */
	err = mlx4_ALLOCATE_VPP_get(dev, port, &available_vpp, vpp_param);
	अगर (err) अणु
		mlx4_info(dev, "Failed query available VPPs\n");
		वापस;
	पूर्ण

	port_qos->num_of_qos_vfs = num_vfs;
	mlx4_dbg(dev, "Port %d Available VPPs %d\n", port, available_vpp);

	क्रम (i = 0; i < MLX4_NUM_UP; i++)
		mlx4_dbg(dev, "Port %d UP %d Allocated %d VPPs\n", port, i,
			 vpp_param[i]);
पूर्ण

अटल पूर्णांक mlx4_master_activate_admin_state(काष्ठा mlx4_priv *priv, पूर्णांक slave)
अणु
	पूर्णांक port, err;
	काष्ठा mlx4_vport_state *vp_admin;
	काष्ठा mlx4_vport_oper_state *vp_oper;
	काष्ठा mlx4_slave_state *slave_state =
		&priv->mfunc.master.slave_state[slave];
	काष्ठा mlx4_active_ports actv_ports = mlx4_get_active_ports(
			&priv->dev, slave);
	पूर्णांक min_port = find_first_bit(actv_ports.ports,
				      priv->dev.caps.num_ports) + 1;
	पूर्णांक max_port = min_port - 1 +
		biपंचांगap_weight(actv_ports.ports, priv->dev.caps.num_ports);

	क्रम (port = min_port; port <= max_port; port++) अणु
		अगर (!test_bit(port - 1, actv_ports.ports))
			जारी;
		priv->mfunc.master.vf_oper[slave].smi_enabled[port] =
			priv->mfunc.master.vf_admin[slave].enable_smi[port];
		vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
		vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];
		अगर (vp_admin->vlan_proto != htons(ETH_P_8021AD) ||
		    slave_state->vst_qinq_supported) अणु
			vp_oper->state.vlan_proto   = vp_admin->vlan_proto;
			vp_oper->state.शेष_vlan = vp_admin->शेष_vlan;
			vp_oper->state.शेष_qos  = vp_admin->शेष_qos;
		पूर्ण
		vp_oper->state.link_state = vp_admin->link_state;
		vp_oper->state.mac        = vp_admin->mac;
		vp_oper->state.spoofchk   = vp_admin->spoofchk;
		vp_oper->state.tx_rate    = vp_admin->tx_rate;
		vp_oper->state.qos_vport  = vp_admin->qos_vport;
		vp_oper->state.guid       = vp_admin->guid;

		अगर (MLX4_VGT != vp_admin->शेष_vlan) अणु
			err = __mlx4_रेजिस्टर_vlan(&priv->dev, port,
						   vp_admin->शेष_vlan, &(vp_oper->vlan_idx));
			अगर (err) अणु
				vp_oper->vlan_idx = NO_INDX;
				vp_oper->state.शेष_vlan = MLX4_VGT;
				vp_oper->state.vlan_proto = htons(ETH_P_8021Q);
				mlx4_warn(&priv->dev,
					  "No vlan resources slave %d, port %d\n",
					  slave, port);
				वापस err;
			पूर्ण
			mlx4_dbg(&priv->dev, "alloc vlan %d idx  %d slave %d port %d\n",
				 (पूर्णांक)(vp_oper->state.शेष_vlan),
				 vp_oper->vlan_idx, slave, port);
		पूर्ण
		अगर (vp_admin->spoofchk) अणु
			vp_oper->mac_idx = __mlx4_रेजिस्टर_mac(&priv->dev,
							       port,
							       vp_admin->mac);
			अगर (0 > vp_oper->mac_idx) अणु
				err = vp_oper->mac_idx;
				vp_oper->mac_idx = NO_INDX;
				mlx4_warn(&priv->dev,
					  "No mac resources slave %d, port %d\n",
					  slave, port);
				वापस err;
			पूर्ण
			mlx4_dbg(&priv->dev, "alloc mac %llx idx  %d slave %d port %d\n",
				 vp_oper->state.mac, vp_oper->mac_idx, slave, port);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx4_master_deactivate_admin_state(काष्ठा mlx4_priv *priv, पूर्णांक slave)
अणु
	पूर्णांक port;
	काष्ठा mlx4_vport_oper_state *vp_oper;
	काष्ठा mlx4_active_ports actv_ports = mlx4_get_active_ports(
			&priv->dev, slave);
	पूर्णांक min_port = find_first_bit(actv_ports.ports,
				      priv->dev.caps.num_ports) + 1;
	पूर्णांक max_port = min_port - 1 +
		biपंचांगap_weight(actv_ports.ports, priv->dev.caps.num_ports);


	क्रम (port = min_port; port <= max_port; port++) अणु
		अगर (!test_bit(port - 1, actv_ports.ports))
			जारी;
		priv->mfunc.master.vf_oper[slave].smi_enabled[port] =
			MLX4_VF_SMI_DISABLED;
		vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
		अगर (NO_INDX != vp_oper->vlan_idx) अणु
			__mlx4_unरेजिस्टर_vlan(&priv->dev,
					       port, vp_oper->state.शेष_vlan);
			vp_oper->vlan_idx = NO_INDX;
		पूर्ण
		अगर (NO_INDX != vp_oper->mac_idx) अणु
			__mlx4_unरेजिस्टर_mac(&priv->dev, port, vp_oper->state.mac);
			vp_oper->mac_idx = NO_INDX;
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

अटल व्योम mlx4_master_करो_cmd(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 cmd,
			       u16 param, u8 toggle)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *slave_state = priv->mfunc.master.slave_state;
	u32 reply;
	u8 is_going_करोwn = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	slave_state[slave].comm_toggle ^= 1;
	reply = (u32) slave_state[slave].comm_toggle << 31;
	अगर (toggle != slave_state[slave].comm_toggle) अणु
		mlx4_warn(dev, "Incorrect toggle %d from slave %d. *** MASTER STATE COMPROMISED ***\n",
			  toggle, slave);
		जाओ reset_slave;
	पूर्ण
	अगर (cmd == MLX4_COMM_CMD_RESET) अणु
		mlx4_warn(dev, "Received reset from slave:%d\n", slave);
		slave_state[slave].active = false;
		slave_state[slave].old_vlan_api = false;
		slave_state[slave].vst_qinq_supported = false;
		mlx4_master_deactivate_admin_state(priv, slave);
		क्रम (i = 0; i < MLX4_EVENT_TYPES_NUM; ++i) अणु
				slave_state[slave].event_eq[i].eqn = -1;
				slave_state[slave].event_eq[i].token = 0;
		पूर्ण
		/*check अगर we are in the middle of FLR process,
		अगर so वापस "retry" status to the slave*/
		अगर (MLX4_COMM_CMD_FLR == slave_state[slave].last_cmd)
			जाओ inक्रमm_slave_state;

		mlx4_dispatch_event(dev, MLX4_DEV_EVENT_SLAVE_SHUTDOWN, slave);

		/* ग_लिखो the version in the event field */
		reply |= mlx4_comm_get_version();

		जाओ reset_slave;
	पूर्ण
	/*command from slave in the middle of FLR*/
	अगर (cmd != MLX4_COMM_CMD_RESET &&
	    MLX4_COMM_CMD_FLR == slave_state[slave].last_cmd) अणु
		mlx4_warn(dev, "slave:%d is Trying to run cmd(0x%x) in the middle of FLR\n",
			  slave, cmd);
		वापस;
	पूर्ण

	चयन (cmd) अणु
	हाल MLX4_COMM_CMD_VHCR0:
		अगर (slave_state[slave].last_cmd != MLX4_COMM_CMD_RESET)
			जाओ reset_slave;
		slave_state[slave].vhcr_dma = ((u64) param) << 48;
		priv->mfunc.master.slave_state[slave].cookie = 0;
		अवरोध;
	हाल MLX4_COMM_CMD_VHCR1:
		अगर (slave_state[slave].last_cmd != MLX4_COMM_CMD_VHCR0)
			जाओ reset_slave;
		slave_state[slave].vhcr_dma |= ((u64) param) << 32;
		अवरोध;
	हाल MLX4_COMM_CMD_VHCR2:
		अगर (slave_state[slave].last_cmd != MLX4_COMM_CMD_VHCR1)
			जाओ reset_slave;
		slave_state[slave].vhcr_dma |= ((u64) param) << 16;
		अवरोध;
	हाल MLX4_COMM_CMD_VHCR_EN:
		अगर (slave_state[slave].last_cmd != MLX4_COMM_CMD_VHCR2)
			जाओ reset_slave;
		slave_state[slave].vhcr_dma |= param;
		अगर (mlx4_master_activate_admin_state(priv, slave))
				जाओ reset_slave;
		slave_state[slave].active = true;
		mlx4_dispatch_event(dev, MLX4_DEV_EVENT_SLAVE_INIT, slave);
		अवरोध;
	हाल MLX4_COMM_CMD_VHCR_POST:
		अगर ((slave_state[slave].last_cmd != MLX4_COMM_CMD_VHCR_EN) &&
		    (slave_state[slave].last_cmd != MLX4_COMM_CMD_VHCR_POST)) अणु
			mlx4_warn(dev, "slave:%d is out of sync, cmd=0x%x, last command=0x%x, reset is needed\n",
				  slave, cmd, slave_state[slave].last_cmd);
			जाओ reset_slave;
		पूर्ण

		mutex_lock(&priv->cmd.slave_cmd_mutex);
		अगर (mlx4_master_process_vhcr(dev, slave, शून्य)) अणु
			mlx4_err(dev, "Failed processing vhcr for slave:%d, resetting slave\n",
				 slave);
			mutex_unlock(&priv->cmd.slave_cmd_mutex);
			जाओ reset_slave;
		पूर्ण
		mutex_unlock(&priv->cmd.slave_cmd_mutex);
		अवरोध;
	शेष:
		mlx4_warn(dev, "Bad comm cmd:%d from slave:%d\n", cmd, slave);
		जाओ reset_slave;
	पूर्ण
	spin_lock_irqsave(&priv->mfunc.master.slave_state_lock, flags);
	अगर (!slave_state[slave].is_slave_going_करोwn)
		slave_state[slave].last_cmd = cmd;
	अन्यथा
		is_going_करोwn = 1;
	spin_unlock_irqrestore(&priv->mfunc.master.slave_state_lock, flags);
	अगर (is_going_करोwn) अणु
		mlx4_warn(dev, "Slave is going down aborting command(%d) executing from slave:%d\n",
			  cmd, slave);
		वापस;
	पूर्ण
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(reply),
		     &priv->mfunc.comm[slave].slave_पढ़ो);

	वापस;

reset_slave:
	/* cleanup any slave resources */
	अगर (dev->persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_UP)
		mlx4_delete_all_resources_क्रम_slave(dev, slave);

	अगर (cmd != MLX4_COMM_CMD_RESET) अणु
		mlx4_warn(dev, "Turn on internal error to force reset, slave=%d, cmd=0x%x\n",
			  slave, cmd);
		/* Turn on पूर्णांकernal error letting slave reset itself immeditaly,
		 * otherwise it might take till समयout on command is passed
		 */
		reply |= ((u32)COMM_CHAN_EVENT_INTERNAL_ERR);
	पूर्ण

	spin_lock_irqsave(&priv->mfunc.master.slave_state_lock, flags);
	अगर (!slave_state[slave].is_slave_going_करोwn)
		slave_state[slave].last_cmd = MLX4_COMM_CMD_RESET;
	spin_unlock_irqrestore(&priv->mfunc.master.slave_state_lock, flags);
	/*with slave in the middle of flr, no need to clean resources again.*/
inक्रमm_slave_state:
	स_रखो(&slave_state[slave].event_eq, 0,
	       माप(काष्ठा mlx4_slave_event_eq_info));
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(reply),
		     &priv->mfunc.comm[slave].slave_पढ़ो);
	wmb();
पूर्ण

/* master command processing */
व्योम mlx4_master_comm_channel(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_mfunc_master_ctx *master =
		container_of(work,
			     काष्ठा mlx4_mfunc_master_ctx,
			     comm_work);
	काष्ठा mlx4_mfunc *mfunc =
		container_of(master, काष्ठा mlx4_mfunc, master);
	काष्ठा mlx4_priv *priv =
		container_of(mfunc, काष्ठा mlx4_priv, mfunc);
	काष्ठा mlx4_dev *dev = &priv->dev;
	u32 lbit_vec[COMM_CHANNEL_BIT_ARRAY_SIZE];
	u32 nmbr_bits;
	u32 comm_cmd;
	पूर्णांक i, slave;
	पूर्णांक toggle;
	bool first = true;
	पूर्णांक served = 0;
	पूर्णांक reported = 0;
	u32 slt;

	क्रम (i = 0; i < COMM_CHANNEL_BIT_ARRAY_SIZE; i++)
		lbit_vec[i] = be32_to_cpu(master->comm_arm_bit_vector[i]);
	nmbr_bits = dev->persist->num_vfs + 1;
	अगर (++master->next_slave >= nmbr_bits)
		master->next_slave = 0;
	slave = master->next_slave;
	जबतक (true) अणु
		slave = find_next_bit((स्थिर अचिन्हित दीर्घ *)&lbit_vec, nmbr_bits, slave);
		अगर  (!first && slave >= master->next_slave)
			अवरोध;
		अगर (slave == nmbr_bits) अणु
			अगर (!first)
				अवरोध;
			first = false;
			slave = 0;
			जारी;
		पूर्ण
		++reported;
		comm_cmd = swab32(पढ़ोl(&mfunc->comm[slave].slave_ग_लिखो));
		slt = swab32(पढ़ोl(&mfunc->comm[slave].slave_पढ़ो)) >> 31;
		toggle = comm_cmd >> 31;
		अगर (toggle != slt) अणु
			अगर (master->slave_state[slave].comm_toggle
			    != slt) अणु
				pr_info("slave %d out of sync. read toggle %d, state toggle %d. Resynching.\n",
					slave, slt,
					master->slave_state[slave].comm_toggle);
				master->slave_state[slave].comm_toggle =
					slt;
			पूर्ण
			mlx4_master_करो_cmd(dev, slave,
					   comm_cmd >> 16 & 0xff,
					   comm_cmd & 0xffff, toggle);
			++served;
		पूर्ण
		slave++;
	पूर्ण

	अगर (reported && reported != served)
		mlx4_warn(dev, "Got command event with bitmask from %d slaves but %d were served\n",
			  reported, served);

	अगर (mlx4_ARM_COMM_CHANNEL(dev))
		mlx4_warn(dev, "Failed to arm comm channel events\n");
पूर्ण

अटल पूर्णांक sync_toggles(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	u32 wr_toggle;
	u32 rd_toggle;
	अचिन्हित दीर्घ end;

	wr_toggle = swab32(पढ़ोl(&priv->mfunc.comm->slave_ग_लिखो));
	अगर (wr_toggle == 0xffffffff)
		end = jअगरfies + msecs_to_jअगरfies(30000);
	अन्यथा
		end = jअगरfies + msecs_to_jअगरfies(5000);

	जबतक (समय_beक्रमe(jअगरfies, end)) अणु
		rd_toggle = swab32(पढ़ोl(&priv->mfunc.comm->slave_पढ़ो));
		अगर (wr_toggle == 0xffffffff || rd_toggle == 0xffffffff) अणु
			/* PCI might be offline */

			/* If device removal has been requested,
			 * करो not जारी retrying.
			 */
			अगर (dev->persist->पूर्णांकerface_state &
			    MLX4_INTERFACE_STATE_NOWAIT) अणु
				mlx4_warn(dev,
					  "communication channel is offline\n");
				वापस -EIO;
			पूर्ण

			msleep(100);
			wr_toggle = swab32(पढ़ोl(&priv->mfunc.comm->
					   slave_ग_लिखो));
			जारी;
		पूर्ण

		अगर (rd_toggle >> 31 == wr_toggle >> 31) अणु
			priv->cmd.comm_toggle = rd_toggle >> 31;
			वापस 0;
		पूर्ण

		cond_resched();
	पूर्ण

	/*
	 * we could reach here अगर क्रम example the previous VM using this
	 * function misbehaved and left the channel with unsynced state. We
	 * should fix this here and give this VM a chance to use a properly
	 * synced channel
	 */
	mlx4_warn(dev, "recovering from previously mis-behaved VM\n");
	__raw_ग_लिखोl((__क्रमce u32) 0, &priv->mfunc.comm->slave_पढ़ो);
	__raw_ग_लिखोl((__क्रमce u32) 0, &priv->mfunc.comm->slave_ग_लिखो);
	priv->cmd.comm_toggle = 0;

	वापस 0;
पूर्ण

पूर्णांक mlx4_multi_func_init(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *s_state;
	पूर्णांक i, j, err, port;

	अगर (mlx4_is_master(dev))
		priv->mfunc.comm =
		ioremap(pci_resource_start(dev->persist->pdev,
					   priv->fw.comm_bar) +
			priv->fw.comm_base, MLX4_COMM_PAGESIZE);
	अन्यथा
		priv->mfunc.comm =
		ioremap(pci_resource_start(dev->persist->pdev, 2) +
			MLX4_SLAVE_COMM_BASE, MLX4_COMM_PAGESIZE);
	अगर (!priv->mfunc.comm) अणु
		mlx4_err(dev, "Couldn't map communication vector\n");
		जाओ err_vhcr;
	पूर्ण

	अगर (mlx4_is_master(dev)) अणु
		काष्ठा mlx4_vf_oper_state *vf_oper;
		काष्ठा mlx4_vf_admin_state *vf_admin;

		priv->mfunc.master.slave_state =
			kसुस्मृति(dev->num_slaves,
				माप(काष्ठा mlx4_slave_state),
				GFP_KERNEL);
		अगर (!priv->mfunc.master.slave_state)
			जाओ err_comm;

		priv->mfunc.master.vf_admin =
			kसुस्मृति(dev->num_slaves,
				माप(काष्ठा mlx4_vf_admin_state),
				GFP_KERNEL);
		अगर (!priv->mfunc.master.vf_admin)
			जाओ err_comm_admin;

		priv->mfunc.master.vf_oper =
			kसुस्मृति(dev->num_slaves,
				माप(काष्ठा mlx4_vf_oper_state),
				GFP_KERNEL);
		अगर (!priv->mfunc.master.vf_oper)
			जाओ err_comm_oper;

		priv->mfunc.master.next_slave = 0;

		क्रम (i = 0; i < dev->num_slaves; ++i) अणु
			vf_admin = &priv->mfunc.master.vf_admin[i];
			vf_oper = &priv->mfunc.master.vf_oper[i];
			s_state = &priv->mfunc.master.slave_state[i];
			s_state->last_cmd = MLX4_COMM_CMD_RESET;
			s_state->vst_qinq_supported = false;
			mutex_init(&priv->mfunc.master.gen_eqe_mutex[i]);
			क्रम (j = 0; j < MLX4_EVENT_TYPES_NUM; ++j)
				s_state->event_eq[j].eqn = -1;
			__raw_ग_लिखोl((__क्रमce u32) 0,
				     &priv->mfunc.comm[i].slave_ग_लिखो);
			__raw_ग_लिखोl((__क्रमce u32) 0,
				     &priv->mfunc.comm[i].slave_पढ़ो);
			क्रम (port = 1; port <= MLX4_MAX_PORTS; port++) अणु
				काष्ठा mlx4_vport_state *admin_vport;
				काष्ठा mlx4_vport_state *oper_vport;

				s_state->vlan_filter[port] =
					kzalloc(माप(काष्ठा mlx4_vlan_fltr),
						GFP_KERNEL);
				अगर (!s_state->vlan_filter[port]) अणु
					अगर (--port)
						kमुक्त(s_state->vlan_filter[port]);
					जाओ err_slaves;
				पूर्ण

				admin_vport = &vf_admin->vport[port];
				oper_vport = &vf_oper->vport[port].state;
				INIT_LIST_HEAD(&s_state->mcast_filters[port]);
				admin_vport->शेष_vlan = MLX4_VGT;
				oper_vport->शेष_vlan = MLX4_VGT;
				admin_vport->qos_vport =
						MLX4_VPP_DEFAULT_VPORT;
				oper_vport->qos_vport = MLX4_VPP_DEFAULT_VPORT;
				admin_vport->vlan_proto = htons(ETH_P_8021Q);
				oper_vport->vlan_proto = htons(ETH_P_8021Q);
				vf_oper->vport[port].vlan_idx = NO_INDX;
				vf_oper->vport[port].mac_idx = NO_INDX;
				mlx4_set_अक्रमom_admin_guid(dev, i, port);
			पूर्ण
			spin_lock_init(&s_state->lock);
		पूर्ण

		अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QOS_VPP) अणु
			क्रम (port = 1; port <= dev->caps.num_ports; port++) अणु
				अगर (mlx4_is_eth(dev, port)) अणु
					mlx4_set_शेष_port_qos(dev, port);
					mlx4_allocate_port_vpps(dev, port);
				पूर्ण
			पूर्ण
		पूर्ण

		स_रखो(&priv->mfunc.master.cmd_eqe, 0, माप(काष्ठा mlx4_eqe));
		priv->mfunc.master.cmd_eqe.type = MLX4_EVENT_TYPE_CMD;
		INIT_WORK(&priv->mfunc.master.comm_work,
			  mlx4_master_comm_channel);
		INIT_WORK(&priv->mfunc.master.slave_event_work,
			  mlx4_gen_slave_eqe);
		INIT_WORK(&priv->mfunc.master.slave_flr_event_work,
			  mlx4_master_handle_slave_flr);
		spin_lock_init(&priv->mfunc.master.slave_state_lock);
		spin_lock_init(&priv->mfunc.master.slave_eq.event_lock);
		priv->mfunc.master.comm_wq =
			create_singlethपढ़ो_workqueue("mlx4_comm");
		अगर (!priv->mfunc.master.comm_wq)
			जाओ err_slaves;

		अगर (mlx4_init_resource_tracker(dev))
			जाओ err_thपढ़ो;

	पूर्ण अन्यथा अणु
		err = sync_toggles(dev);
		अगर (err) अणु
			mlx4_err(dev, "Couldn't sync toggles\n");
			जाओ err_comm;
		पूर्ण
	पूर्ण
	वापस 0;

err_thपढ़ो:
	flush_workqueue(priv->mfunc.master.comm_wq);
	destroy_workqueue(priv->mfunc.master.comm_wq);
err_slaves:
	जबतक (i--) अणु
		क्रम (port = 1; port <= MLX4_MAX_PORTS; port++)
			kमुक्त(priv->mfunc.master.slave_state[i].vlan_filter[port]);
	पूर्ण
	kमुक्त(priv->mfunc.master.vf_oper);
err_comm_oper:
	kमुक्त(priv->mfunc.master.vf_admin);
err_comm_admin:
	kमुक्त(priv->mfunc.master.slave_state);
err_comm:
	iounmap(priv->mfunc.comm);
	priv->mfunc.comm = शून्य;
err_vhcr:
	dma_मुक्त_coherent(&dev->persist->pdev->dev, PAGE_SIZE,
			  priv->mfunc.vhcr,
			  priv->mfunc.vhcr_dma);
	priv->mfunc.vhcr = शून्य;
	वापस -ENOMEM;
पूर्ण

पूर्णांक mlx4_cmd_init(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक flags = 0;

	अगर (!priv->cmd.initialized) अणु
		init_rwsem(&priv->cmd.चयन_sem);
		mutex_init(&priv->cmd.slave_cmd_mutex);
		sema_init(&priv->cmd.poll_sem, 1);
		priv->cmd.use_events = 0;
		priv->cmd.toggle     = 1;
		priv->cmd.initialized = 1;
		flags |= MLX4_CMD_CLEANUP_STRUCT;
	पूर्ण

	अगर (!mlx4_is_slave(dev) && !priv->cmd.hcr) अणु
		priv->cmd.hcr = ioremap(pci_resource_start(dev->persist->pdev,
					0) + MLX4_HCR_BASE, MLX4_HCR_SIZE);
		अगर (!priv->cmd.hcr) अणु
			mlx4_err(dev, "Couldn't map command register\n");
			जाओ err;
		पूर्ण
		flags |= MLX4_CMD_CLEANUP_HCR;
	पूर्ण

	अगर (mlx4_is_mfunc(dev) && !priv->mfunc.vhcr) अणु
		priv->mfunc.vhcr = dma_alloc_coherent(&dev->persist->pdev->dev,
						      PAGE_SIZE,
						      &priv->mfunc.vhcr_dma,
						      GFP_KERNEL);
		अगर (!priv->mfunc.vhcr)
			जाओ err;

		flags |= MLX4_CMD_CLEANUP_VHCR;
	पूर्ण

	अगर (!priv->cmd.pool) अणु
		priv->cmd.pool = dma_pool_create("mlx4_cmd",
						 &dev->persist->pdev->dev,
						 MLX4_MAILBOX_SIZE,
						 MLX4_MAILBOX_SIZE, 0);
		अगर (!priv->cmd.pool)
			जाओ err;

		flags |= MLX4_CMD_CLEANUP_POOL;
	पूर्ण

	वापस 0;

err:
	mlx4_cmd_cleanup(dev, flags);
	वापस -ENOMEM;
पूर्ण

व्योम mlx4_report_पूर्णांकernal_err_comm_event(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक slave;
	u32 slave_पढ़ो;

	/* If the comm channel has not yet been initialized,
	 * skip reporting the पूर्णांकernal error event to all
	 * the communication channels.
	 */
	अगर (!priv->mfunc.comm)
		वापस;

	/* Report an पूर्णांकernal error event to all
	 * communication channels.
	 */
	क्रम (slave = 0; slave < dev->num_slaves; slave++) अणु
		slave_पढ़ो = swab32(पढ़ोl(&priv->mfunc.comm[slave].slave_पढ़ो));
		slave_पढ़ो |= (u32)COMM_CHAN_EVENT_INTERNAL_ERR;
		__raw_ग_लिखोl((__क्रमce u32)cpu_to_be32(slave_पढ़ो),
			     &priv->mfunc.comm[slave].slave_पढ़ो);
	पूर्ण
पूर्ण

व्योम mlx4_multi_func_cleanup(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक i, port;

	अगर (mlx4_is_master(dev)) अणु
		flush_workqueue(priv->mfunc.master.comm_wq);
		destroy_workqueue(priv->mfunc.master.comm_wq);
		क्रम (i = 0; i < dev->num_slaves; i++) अणु
			क्रम (port = 1; port <= MLX4_MAX_PORTS; port++)
				kमुक्त(priv->mfunc.master.slave_state[i].vlan_filter[port]);
		पूर्ण
		kमुक्त(priv->mfunc.master.slave_state);
		kमुक्त(priv->mfunc.master.vf_admin);
		kमुक्त(priv->mfunc.master.vf_oper);
		dev->num_slaves = 0;
	पूर्ण

	iounmap(priv->mfunc.comm);
	priv->mfunc.comm = शून्य;
पूर्ण

व्योम mlx4_cmd_cleanup(काष्ठा mlx4_dev *dev, पूर्णांक cleanup_mask)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (priv->cmd.pool && (cleanup_mask & MLX4_CMD_CLEANUP_POOL)) अणु
		dma_pool_destroy(priv->cmd.pool);
		priv->cmd.pool = शून्य;
	पूर्ण

	अगर (!mlx4_is_slave(dev) && priv->cmd.hcr &&
	    (cleanup_mask & MLX4_CMD_CLEANUP_HCR)) अणु
		iounmap(priv->cmd.hcr);
		priv->cmd.hcr = शून्य;
	पूर्ण
	अगर (mlx4_is_mfunc(dev) && priv->mfunc.vhcr &&
	    (cleanup_mask & MLX4_CMD_CLEANUP_VHCR)) अणु
		dma_मुक्त_coherent(&dev->persist->pdev->dev, PAGE_SIZE,
				  priv->mfunc.vhcr, priv->mfunc.vhcr_dma);
		priv->mfunc.vhcr = शून्य;
	पूर्ण
	अगर (priv->cmd.initialized && (cleanup_mask & MLX4_CMD_CLEANUP_STRUCT))
		priv->cmd.initialized = 0;
पूर्ण

/*
 * Switch to using events to issue FW commands (can only be called
 * after event queue क्रम command events has been initialized).
 */
पूर्णांक mlx4_cmd_use_events(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक i;
	पूर्णांक err = 0;

	priv->cmd.context = kदो_स्मृति_array(priv->cmd.max_cmds,
					  माप(काष्ठा mlx4_cmd_context),
					  GFP_KERNEL);
	अगर (!priv->cmd.context)
		वापस -ENOMEM;

	अगर (mlx4_is_mfunc(dev))
		mutex_lock(&priv->cmd.slave_cmd_mutex);
	करोwn_ग_लिखो(&priv->cmd.चयन_sem);
	क्रम (i = 0; i < priv->cmd.max_cmds; ++i) अणु
		priv->cmd.context[i].token = i;
		priv->cmd.context[i].next  = i + 1;
		/* To support fatal error flow, initialize all
		 * cmd contexts to allow simulating completions
		 * with complete() at any समय.
		 */
		init_completion(&priv->cmd.context[i].करोne);
	पूर्ण

	priv->cmd.context[priv->cmd.max_cmds - 1].next = -1;
	priv->cmd.मुक्त_head = 0;

	sema_init(&priv->cmd.event_sem, priv->cmd.max_cmds);

	क्रम (priv->cmd.token_mask = 1;
	     priv->cmd.token_mask < priv->cmd.max_cmds;
	     priv->cmd.token_mask <<= 1)
		; /* nothing */
	--priv->cmd.token_mask;

	करोwn(&priv->cmd.poll_sem);
	priv->cmd.use_events = 1;
	up_ग_लिखो(&priv->cmd.चयन_sem);
	अगर (mlx4_is_mfunc(dev))
		mutex_unlock(&priv->cmd.slave_cmd_mutex);

	वापस err;
पूर्ण

/*
 * Switch back to polling (used when shutting करोwn the device)
 */
व्योम mlx4_cmd_use_polling(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक i;

	अगर (mlx4_is_mfunc(dev))
		mutex_lock(&priv->cmd.slave_cmd_mutex);
	करोwn_ग_लिखो(&priv->cmd.चयन_sem);
	priv->cmd.use_events = 0;

	क्रम (i = 0; i < priv->cmd.max_cmds; ++i)
		करोwn(&priv->cmd.event_sem);

	kमुक्त(priv->cmd.context);
	priv->cmd.context = शून्य;

	up(&priv->cmd.poll_sem);
	up_ग_लिखो(&priv->cmd.चयन_sem);
	अगर (mlx4_is_mfunc(dev))
		mutex_unlock(&priv->cmd.slave_cmd_mutex);
पूर्ण

काष्ठा mlx4_cmd_mailbox *mlx4_alloc_cmd_mailbox(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;

	mailbox = kदो_स्मृति(माप(*mailbox), GFP_KERNEL);
	अगर (!mailbox)
		वापस ERR_PTR(-ENOMEM);

	mailbox->buf = dma_pool_zalloc(mlx4_priv(dev)->cmd.pool, GFP_KERNEL,
				       &mailbox->dma);
	अगर (!mailbox->buf) अणु
		kमुक्त(mailbox);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस mailbox;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_alloc_cmd_mailbox);

व्योम mlx4_मुक्त_cmd_mailbox(काष्ठा mlx4_dev *dev,
			   काष्ठा mlx4_cmd_mailbox *mailbox)
अणु
	अगर (!mailbox)
		वापस;

	dma_pool_मुक्त(mlx4_priv(dev)->cmd.pool, mailbox->buf, mailbox->dma);
	kमुक्त(mailbox);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_मुक्त_cmd_mailbox);

u32 mlx4_comm_get_version(व्योम)
अणु
	 वापस ((u32) CMD_CHAN_IF_REV << 8) | (u32) CMD_CHAN_VER;
पूर्ण

अटल पूर्णांक mlx4_get_slave_indx(काष्ठा mlx4_dev *dev, पूर्णांक vf)
अणु
	अगर ((vf < 0) || (vf >= dev->persist->num_vfs)) अणु
		mlx4_err(dev, "Bad vf number:%d (number of activated vf: %d)\n",
			 vf, dev->persist->num_vfs);
		वापस -EINVAL;
	पूर्ण

	वापस vf+1;
पूर्ण

पूर्णांक mlx4_get_vf_indx(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	अगर (slave < 1 || slave > dev->persist->num_vfs) अणु
		mlx4_err(dev,
			 "Bad slave number:%d (number of activated slaves: %lu)\n",
			 slave, dev->num_slaves);
		वापस -EINVAL;
	पूर्ण
	वापस slave - 1;
पूर्ण

व्योम mlx4_cmd_wake_completions(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cmd_context *context;
	पूर्णांक i;

	spin_lock(&priv->cmd.context_lock);
	अगर (priv->cmd.context) अणु
		क्रम (i = 0; i < priv->cmd.max_cmds; ++i) अणु
			context = &priv->cmd.context[i];
			context->fw_status = CMD_STAT_INTERNAL_ERR;
			context->result    =
				mlx4_status_to_त्रुटि_सं(CMD_STAT_INTERNAL_ERR);
			complete(&context->करोne);
		पूर्ण
	पूर्ण
	spin_unlock(&priv->cmd.context_lock);
पूर्ण

काष्ठा mlx4_active_ports mlx4_get_active_ports(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_active_ports actv_ports;
	पूर्णांक vf;

	biपंचांगap_zero(actv_ports.ports, MLX4_MAX_PORTS);

	अगर (slave == 0) अणु
		biपंचांगap_fill(actv_ports.ports, dev->caps.num_ports);
		वापस actv_ports;
	पूर्ण

	vf = mlx4_get_vf_indx(dev, slave);
	अगर (vf < 0)
		वापस actv_ports;

	biपंचांगap_set(actv_ports.ports, dev->dev_vfs[vf].min_port - 1,
		   min((पूर्णांक)dev->dev_vfs[mlx4_get_vf_indx(dev, slave)].n_ports,
		   dev->caps.num_ports));

	वापस actv_ports;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_active_ports);

पूर्णांक mlx4_slave_convert_port(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port)
अणु
	अचिन्हित n;
	काष्ठा mlx4_active_ports actv_ports = mlx4_get_active_ports(dev, slave);
	अचिन्हित m = biपंचांगap_weight(actv_ports.ports, dev->caps.num_ports);

	अगर (port <= 0 || port > m)
		वापस -EINVAL;

	n = find_first_bit(actv_ports.ports, dev->caps.num_ports);
	अगर (port <= n)
		port = n + 1;

	वापस port;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_slave_convert_port);

पूर्णांक mlx4_phys_to_slave_port(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port)
अणु
	काष्ठा mlx4_active_ports actv_ports = mlx4_get_active_ports(dev, slave);
	अगर (test_bit(port - 1, actv_ports.ports))
		वापस port -
			find_first_bit(actv_ports.ports, dev->caps.num_ports);

	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_phys_to_slave_port);

काष्ठा mlx4_slaves_pport mlx4_phys_to_slaves_pport(काष्ठा mlx4_dev *dev,
						   पूर्णांक port)
अणु
	अचिन्हित i;
	काष्ठा mlx4_slaves_pport slaves_pport;

	biपंचांगap_zero(slaves_pport.slaves, MLX4_MFUNC_MAX);

	अगर (port <= 0 || port > dev->caps.num_ports)
		वापस slaves_pport;

	क्रम (i = 0; i < dev->persist->num_vfs + 1; i++) अणु
		काष्ठा mlx4_active_ports actv_ports =
			mlx4_get_active_ports(dev, i);
		अगर (test_bit(port - 1, actv_ports.ports))
			set_bit(i, slaves_pport.slaves);
	पूर्ण

	वापस slaves_pport;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_phys_to_slaves_pport);

काष्ठा mlx4_slaves_pport mlx4_phys_to_slaves_pport_actv(
		काष्ठा mlx4_dev *dev,
		स्थिर काष्ठा mlx4_active_ports *crit_ports)
अणु
	अचिन्हित i;
	काष्ठा mlx4_slaves_pport slaves_pport;

	biपंचांगap_zero(slaves_pport.slaves, MLX4_MFUNC_MAX);

	क्रम (i = 0; i < dev->persist->num_vfs + 1; i++) अणु
		काष्ठा mlx4_active_ports actv_ports =
			mlx4_get_active_ports(dev, i);
		अगर (biपंचांगap_equal(crit_ports->ports, actv_ports.ports,
				 dev->caps.num_ports))
			set_bit(i, slaves_pport.slaves);
	पूर्ण

	वापस slaves_pport;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_phys_to_slaves_pport_actv);

अटल पूर्णांक mlx4_slaves_बंदst_port(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port)
अणु
	काष्ठा mlx4_active_ports actv_ports = mlx4_get_active_ports(dev, slave);
	पूर्णांक min_port = find_first_bit(actv_ports.ports, dev->caps.num_ports)
			+ 1;
	पूर्णांक max_port = min_port +
		biपंचांगap_weight(actv_ports.ports, dev->caps.num_ports);

	अगर (port < min_port)
		port = min_port;
	अन्यथा अगर (port >= max_port)
		port = max_port - 1;

	वापस port;
पूर्ण

अटल पूर्णांक mlx4_set_vport_qos(काष्ठा mlx4_priv *priv, पूर्णांक slave, पूर्णांक port,
			      पूर्णांक max_tx_rate)
अणु
	पूर्णांक i;
	पूर्णांक err;
	काष्ठा mlx4_qos_manager *port_qos;
	काष्ठा mlx4_dev *dev = &priv->dev;
	काष्ठा mlx4_vport_qos_param vpp_qos[MLX4_NUM_UP];

	port_qos = &priv->mfunc.master.qos_ctl[port];
	स_रखो(vpp_qos, 0, माप(काष्ठा mlx4_vport_qos_param) * MLX4_NUM_UP);

	अगर (slave > port_qos->num_of_qos_vfs) अणु
		mlx4_info(dev, "No available VPP resources for this VF\n");
		वापस -EINVAL;
	पूर्ण

	/* Query क्रम शेष QoS values from Vport 0 is needed */
	err = mlx4_SET_VPORT_QOS_get(dev, port, 0, vpp_qos);
	अगर (err) अणु
		mlx4_info(dev, "Failed to query Vport 0 QoS values\n");
		वापस err;
	पूर्ण

	क्रम (i = 0; i < MLX4_NUM_UP; i++) अणु
		अगर (test_bit(i, port_qos->priority_bm) && max_tx_rate) अणु
			vpp_qos[i].max_avg_bw = max_tx_rate;
			vpp_qos[i].enable = 1;
		पूर्ण अन्यथा अणु
			/* अगर user supplied tx_rate == 0, meaning no rate limit
			 * configuration is required. so we are leaving the
			 * value of max_avg_bw as queried from Vport 0.
			 */
			vpp_qos[i].enable = 0;
		पूर्ण
	पूर्ण

	err = mlx4_SET_VPORT_QOS_set(dev, port, slave, vpp_qos);
	अगर (err) अणु
		mlx4_info(dev, "Failed to set Vport %d QoS values\n", slave);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool mlx4_is_vf_vst_and_prio_qos(काष्ठा mlx4_dev *dev, पूर्णांक port,
					काष्ठा mlx4_vport_state *vf_admin)
अणु
	काष्ठा mlx4_qos_manager *info;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (!mlx4_is_master(dev) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QOS_VPP))
		वापस false;

	info = &priv->mfunc.master.qos_ctl[port];

	अगर (vf_admin->शेष_vlan != MLX4_VGT &&
	    test_bit(vf_admin->शेष_qos, info->priority_bm))
		वापस true;

	वापस false;
पूर्ण

अटल bool mlx4_valid_vf_state_change(काष्ठा mlx4_dev *dev, पूर्णांक port,
				       काष्ठा mlx4_vport_state *vf_admin,
				       पूर्णांक vlan, पूर्णांक qos)
अणु
	काष्ठा mlx4_vport_state dummy_admin = अणु0पूर्ण;

	अगर (!mlx4_is_vf_vst_and_prio_qos(dev, port, vf_admin) ||
	    !vf_admin->tx_rate)
		वापस true;

	dummy_admin.शेष_qos = qos;
	dummy_admin.शेष_vlan = vlan;

	/* VF wants to move to other VST state which is valid with current
	 * rate limit. Either dअगरfernt शेष vlan in VST or other
	 * supported QoS priority. Otherwise we करोn't allow this change when
	 * the TX rate is still configured.
	 */
	अगर (mlx4_is_vf_vst_and_prio_qos(dev, port, &dummy_admin))
		वापस true;

	mlx4_info(dev, "Cannot change VF state to %s while rate is set\n",
		  (vlan == MLX4_VGT) ? "VGT" : "VST");

	अगर (vlan != MLX4_VGT)
		mlx4_info(dev, "VST priority %d not supported for QoS\n", qos);

	mlx4_info(dev, "Please set rate to 0 prior to this VF state change\n");

	वापस false;
पूर्ण

पूर्णांक mlx4_set_vf_mac(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_vport_state *s_info;
	पूर्णांक slave;

	अगर (!mlx4_is_master(dev))
		वापस -EPROTONOSUPPORT;

	अगर (is_multicast_ether_addr(mac))
		वापस -EINVAL;

	slave = mlx4_get_slave_indx(dev, vf);
	अगर (slave < 0)
		वापस -EINVAL;

	port = mlx4_slaves_बंदst_port(dev, slave, port);
	s_info = &priv->mfunc.master.vf_admin[slave].vport[port];

	अगर (s_info->spoofchk && is_zero_ether_addr(mac)) अणु
		mlx4_info(dev, "MAC invalidation is not allowed when spoofchk is on\n");
		वापस -EPERM;
	पूर्ण

	s_info->mac = mlx4_mac_to_u64(mac);
	mlx4_info(dev, "default mac on vf %d port %d to %llX will take effect only after vf restart\n",
		  vf, port, s_info->mac);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_set_vf_mac);


पूर्णांक mlx4_set_vf_vlan(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक vf, u16 vlan, u8 qos,
		     __be16 proto)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_vport_state *vf_admin;
	काष्ठा mlx4_slave_state *slave_state;
	काष्ठा mlx4_vport_oper_state *vf_oper;
	पूर्णांक slave;

	अगर ((!mlx4_is_master(dev)) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_VLAN_CONTROL))
		वापस -EPROTONOSUPPORT;

	अगर ((vlan > 4095) || (qos > 7))
		वापस -EINVAL;

	अगर (proto == htons(ETH_P_8021AD) &&
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SVLAN_BY_QP))
		वापस -EPROTONOSUPPORT;

	अगर (proto != htons(ETH_P_8021Q) &&
	    proto != htons(ETH_P_8021AD))
		वापस -EINVAL;

	अगर ((proto == htons(ETH_P_8021AD)) &&
	    ((vlan == 0) || (vlan == MLX4_VGT)))
		वापस -EINVAL;

	slave = mlx4_get_slave_indx(dev, vf);
	अगर (slave < 0)
		वापस -EINVAL;

	slave_state = &priv->mfunc.master.slave_state[slave];
	अगर ((proto == htons(ETH_P_8021AD)) && (slave_state->active) &&
	    (!slave_state->vst_qinq_supported)) अणु
		mlx4_err(dev, "vf %d does not support VST QinQ mode\n", vf);
		वापस -EPROTONOSUPPORT;
	पूर्ण
	port = mlx4_slaves_बंदst_port(dev, slave, port);
	vf_admin = &priv->mfunc.master.vf_admin[slave].vport[port];
	vf_oper = &priv->mfunc.master.vf_oper[slave].vport[port];

	अगर (!mlx4_valid_vf_state_change(dev, port, vf_admin, vlan, qos))
		वापस -EPERM;

	अगर ((0 == vlan) && (0 == qos))
		vf_admin->शेष_vlan = MLX4_VGT;
	अन्यथा
		vf_admin->शेष_vlan = vlan;
	vf_admin->शेष_qos = qos;
	vf_admin->vlan_proto = proto;

	/* If rate was configured prior to VST, we saved the configured rate
	 * in vf_admin->rate and now, अगर priority supported we enक्रमce the QoS
	 */
	अगर (mlx4_is_vf_vst_and_prio_qos(dev, port, vf_admin) &&
	    vf_admin->tx_rate)
		vf_admin->qos_vport = slave;

	/* Try to activate new vf state without restart,
	 * this option is not supported जबतक moving to VST QinQ mode.
	 */
	अगर ((proto == htons(ETH_P_8021AD) &&
	     vf_oper->state.vlan_proto != proto) ||
	    mlx4_master_immediate_activate_vlan_qos(priv, slave, port))
		mlx4_info(dev,
			  "updating vf %d port %d config will take effect on next VF restart\n",
			  vf, port);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_set_vf_vlan);

पूर्णांक mlx4_set_vf_rate(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक vf, पूर्णांक min_tx_rate,
		     पूर्णांक max_tx_rate)
अणु
	पूर्णांक err;
	पूर्णांक slave;
	काष्ठा mlx4_vport_state *vf_admin;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (!mlx4_is_master(dev) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QOS_VPP))
		वापस -EPROTONOSUPPORT;

	अगर (min_tx_rate) अणु
		mlx4_info(dev, "Minimum BW share not supported\n");
		वापस -EPROTONOSUPPORT;
	पूर्ण

	slave = mlx4_get_slave_indx(dev, vf);
	अगर (slave < 0)
		वापस -EINVAL;

	port = mlx4_slaves_बंदst_port(dev, slave, port);
	vf_admin = &priv->mfunc.master.vf_admin[slave].vport[port];

	err = mlx4_set_vport_qos(priv, slave, port, max_tx_rate);
	अगर (err) अणु
		mlx4_info(dev, "vf %d failed to set rate %d\n", vf,
			  max_tx_rate);
		वापस err;
	पूर्ण

	vf_admin->tx_rate = max_tx_rate;
	/* अगर VF is not in supported mode (VST with supported prio),
	 * we करो not change vport configuration क्रम its QPs, but save
	 * the rate, so it will be enक्रमced when it moves to supported
	 * mode next समय.
	 */
	अगर (!mlx4_is_vf_vst_and_prio_qos(dev, port, vf_admin)) अणु
		mlx4_info(dev,
			  "rate set for VF %d when not in valid state\n", vf);

		अगर (vf_admin->शेष_vlan != MLX4_VGT)
			mlx4_info(dev, "VST priority not supported by QoS\n");
		अन्यथा
			mlx4_info(dev, "VF in VGT mode (needed VST)\n");

		mlx4_info(dev,
			  "rate %d take affect when VF moves to valid state\n",
			  max_tx_rate);
		वापस 0;
	पूर्ण

	/* If user sets rate 0 assigning शेष vport क्रम its QPs */
	vf_admin->qos_vport = max_tx_rate ? slave : MLX4_VPP_DEFAULT_VPORT;

	अगर (priv->mfunc.master.slave_state[slave].active &&
	    dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_UPDATE_QP)
		mlx4_master_immediate_activate_vlan_qos(priv, slave, port);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_set_vf_rate);

 /* mlx4_get_slave_शेष_vlan -
 * वापस true अगर VST ( शेष vlan)
 * अगर VST, will वापस vlan & qos (अगर not शून्य)
 */
bool mlx4_get_slave_शेष_vlan(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक slave,
				 u16 *vlan, u8 *qos)
अणु
	काष्ठा mlx4_vport_oper_state *vp_oper;
	काष्ठा mlx4_priv *priv;

	priv = mlx4_priv(dev);
	port = mlx4_slaves_बंदst_port(dev, slave, port);
	vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];

	अगर (MLX4_VGT != vp_oper->state.शेष_vlan) अणु
		अगर (vlan)
			*vlan = vp_oper->state.शेष_vlan;
		अगर (qos)
			*qos = vp_oper->state.शेष_qos;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_slave_शेष_vlan);

पूर्णांक mlx4_set_vf_spoofchk(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक vf, bool setting)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_vport_state *s_info;
	पूर्णांक slave;
	u8 mac[ETH_ALEN];

	अगर ((!mlx4_is_master(dev)) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_FSM))
		वापस -EPROTONOSUPPORT;

	slave = mlx4_get_slave_indx(dev, vf);
	अगर (slave < 0)
		वापस -EINVAL;

	port = mlx4_slaves_बंदst_port(dev, slave, port);
	s_info = &priv->mfunc.master.vf_admin[slave].vport[port];

	mlx4_u64_to_mac(mac, s_info->mac);
	अगर (setting && !is_valid_ether_addr(mac)) अणु
		mlx4_info(dev, "Illegal MAC with spoofchk\n");
		वापस -EPERM;
	पूर्ण

	s_info->spoofchk = setting;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_set_vf_spoofchk);

पूर्णांक mlx4_get_vf_config(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक vf, काष्ठा अगरla_vf_info *ivf)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_vport_state *s_info;
	पूर्णांक slave;

	अगर (!mlx4_is_master(dev))
		वापस -EPROTONOSUPPORT;

	slave = mlx4_get_slave_indx(dev, vf);
	अगर (slave < 0)
		वापस -EINVAL;

	s_info = &priv->mfunc.master.vf_admin[slave].vport[port];
	ivf->vf = vf;

	/* need to convert it to a func */
	ivf->mac[0] = ((s_info->mac >> (5*8)) & 0xff);
	ivf->mac[1] = ((s_info->mac >> (4*8)) & 0xff);
	ivf->mac[2] = ((s_info->mac >> (3*8)) & 0xff);
	ivf->mac[3] = ((s_info->mac >> (2*8)) & 0xff);
	ivf->mac[4] = ((s_info->mac >> (1*8)) & 0xff);
	ivf->mac[5] = ((s_info->mac)  & 0xff);

	ivf->vlan		= s_info->शेष_vlan;
	ivf->qos		= s_info->शेष_qos;
	ivf->vlan_proto		= s_info->vlan_proto;

	अगर (mlx4_is_vf_vst_and_prio_qos(dev, port, s_info))
		ivf->max_tx_rate = s_info->tx_rate;
	अन्यथा
		ivf->max_tx_rate = 0;

	ivf->min_tx_rate	= 0;
	ivf->spoofchk		= s_info->spoofchk;
	ivf->linkstate		= s_info->link_state;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_vf_config);

पूर्णांक mlx4_set_vf_link_state(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक vf, पूर्णांक link_state)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_vport_state *s_info;
	पूर्णांक slave;
	u8 link_stat_event;

	slave = mlx4_get_slave_indx(dev, vf);
	अगर (slave < 0)
		वापस -EINVAL;

	port = mlx4_slaves_बंदst_port(dev, slave, port);
	चयन (link_state) अणु
	हाल IFLA_VF_LINK_STATE_AUTO:
		/* get current link state */
		अगर (!priv->sense.करो_sense_port[port])
			link_stat_event = MLX4_PORT_CHANGE_SUBTYPE_ACTIVE;
		अन्यथा
			link_stat_event = MLX4_PORT_CHANGE_SUBTYPE_DOWN;
	    अवरोध;

	हाल IFLA_VF_LINK_STATE_ENABLE:
		link_stat_event = MLX4_PORT_CHANGE_SUBTYPE_ACTIVE;
	    अवरोध;

	हाल IFLA_VF_LINK_STATE_DISABLE:
		link_stat_event = MLX4_PORT_CHANGE_SUBTYPE_DOWN;
	    अवरोध;

	शेष:
		mlx4_warn(dev, "unknown value for link_state %02x on slave %d port %d\n",
			  link_state, slave, port);
		वापस -EINVAL;
	पूर्ण
	s_info = &priv->mfunc.master.vf_admin[slave].vport[port];
	s_info->link_state = link_state;

	/* send event */
	mlx4_gen_port_state_change_eqe(dev, slave, port, link_stat_event);

	अगर (mlx4_master_immediate_activate_vlan_qos(priv, slave, port))
		mlx4_dbg(dev,
			 "updating vf %d port %d no link state HW enforcement\n",
			 vf, port);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_set_vf_link_state);

पूर्णांक mlx4_get_counter_stats(काष्ठा mlx4_dev *dev, पूर्णांक counter_index,
			   काष्ठा mlx4_counter *counter_stats, पूर्णांक reset)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox = शून्य;
	काष्ठा mlx4_counter *पंचांगp_counter;
	पूर्णांक err;
	u32 अगर_stat_in_mod;

	अगर (!counter_stats)
		वापस -EINVAL;

	अगर (counter_index == MLX4_SINK_COUNTER_INDEX(dev))
		वापस 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	स_रखो(mailbox->buf, 0, माप(काष्ठा mlx4_counter));
	अगर_stat_in_mod = counter_index;
	अगर (reset)
		अगर_stat_in_mod |= MLX4_QUERY_IF_STAT_RESET;
	err = mlx4_cmd_box(dev, 0, mailbox->dma,
			   अगर_stat_in_mod, 0,
			   MLX4_CMD_QUERY_IF_STAT,
			   MLX4_CMD_TIME_CLASS_C,
			   MLX4_CMD_NATIVE);
	अगर (err) अणु
		mlx4_dbg(dev, "%s: failed to read statistics for counter index %d\n",
			 __func__, counter_index);
		जाओ अगर_stat_out;
	पूर्ण
	पंचांगp_counter = (काष्ठा mlx4_counter *)mailbox->buf;
	counter_stats->counter_mode = पंचांगp_counter->counter_mode;
	अगर (counter_stats->counter_mode == 0) अणु
		counter_stats->rx_frames =
			cpu_to_be64(be64_to_cpu(counter_stats->rx_frames) +
				    be64_to_cpu(पंचांगp_counter->rx_frames));
		counter_stats->tx_frames =
			cpu_to_be64(be64_to_cpu(counter_stats->tx_frames) +
				    be64_to_cpu(पंचांगp_counter->tx_frames));
		counter_stats->rx_bytes =
			cpu_to_be64(be64_to_cpu(counter_stats->rx_bytes) +
				    be64_to_cpu(पंचांगp_counter->rx_bytes));
		counter_stats->tx_bytes =
			cpu_to_be64(be64_to_cpu(counter_stats->tx_bytes) +
				    be64_to_cpu(पंचांगp_counter->tx_bytes));
	पूर्ण

अगर_stat_out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_counter_stats);

पूर्णांक mlx4_get_vf_stats(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक vf_idx,
		      काष्ठा अगरla_vf_stats *vf_stats)
अणु
	काष्ठा mlx4_counter पंचांगp_vf_stats;
	पूर्णांक slave;
	पूर्णांक err = 0;

	अगर (!vf_stats)
		वापस -EINVAL;

	अगर (!mlx4_is_master(dev))
		वापस -EPROTONOSUPPORT;

	slave = mlx4_get_slave_indx(dev, vf_idx);
	अगर (slave < 0)
		वापस -EINVAL;

	port = mlx4_slaves_बंदst_port(dev, slave, port);
	err = mlx4_calc_vf_counters(dev, slave, port, &पंचांगp_vf_stats);
	अगर (!err && पंचांगp_vf_stats.counter_mode == 0) अणु
		vf_stats->rx_packets = be64_to_cpu(पंचांगp_vf_stats.rx_frames);
		vf_stats->tx_packets = be64_to_cpu(पंचांगp_vf_stats.tx_frames);
		vf_stats->rx_bytes = be64_to_cpu(पंचांगp_vf_stats.rx_bytes);
		vf_stats->tx_bytes = be64_to_cpu(पंचांगp_vf_stats.tx_bytes);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_vf_stats);

पूर्णांक mlx4_vf_smi_enabled(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (slave < 1 || slave >= dev->num_slaves ||
	    port < 1 || port > MLX4_MAX_PORTS)
		वापस 0;

	वापस priv->mfunc.master.vf_oper[slave].smi_enabled[port] ==
		MLX4_VF_SMI_ENABLED;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_vf_smi_enabled);

पूर्णांक mlx4_vf_get_enable_smi_admin(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (slave == mlx4_master_func_num(dev))
		वापस 1;

	अगर (slave < 1 || slave >= dev->num_slaves ||
	    port < 1 || port > MLX4_MAX_PORTS)
		वापस 0;

	वापस priv->mfunc.master.vf_admin[slave].enable_smi[port] ==
		MLX4_VF_SMI_ENABLED;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_vf_get_enable_smi_admin);

पूर्णांक mlx4_vf_set_enable_smi_admin(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port,
				 पूर्णांक enabled)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_active_ports actv_ports = mlx4_get_active_ports(
			&priv->dev, slave);
	पूर्णांक min_port = find_first_bit(actv_ports.ports,
				      priv->dev.caps.num_ports) + 1;
	पूर्णांक max_port = min_port - 1 +
		biपंचांगap_weight(actv_ports.ports, priv->dev.caps.num_ports);

	अगर (slave == mlx4_master_func_num(dev))
		वापस 0;

	अगर (slave < 1 || slave >= dev->num_slaves ||
	    port < 1 || port > MLX4_MAX_PORTS ||
	    enabled < 0 || enabled > 1)
		वापस -EINVAL;

	अगर (min_port == max_port && dev->caps.num_ports > 1) अणु
		mlx4_info(dev, "SMI access disallowed for single ported VFs\n");
		वापस -EPROTONOSUPPORT;
	पूर्ण

	priv->mfunc.master.vf_admin[slave].enable_smi[port] = enabled;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_vf_set_enable_smi_admin);
