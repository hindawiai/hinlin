<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
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

#समावेश <linux/completion.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <rdma/ib_mad.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_config_reg.h"
#समावेश "mthca_cmd.h"
#समावेश "mthca_memfree.h"

#घोषणा CMD_POLL_TOKEN 0xffff

क्रमागत अणु
	HCR_IN_PARAM_OFFSET    = 0x00,
	HCR_IN_MODIFIER_OFFSET = 0x08,
	HCR_OUT_PARAM_OFFSET   = 0x0c,
	HCR_TOKEN_OFFSET       = 0x14,
	HCR_STATUS_OFFSET      = 0x18,

	HCR_OPMOD_SHIFT        = 12,
	HCA_E_BIT              = 22,
	HCR_GO_BIT             = 23
पूर्ण;

क्रमागत अणु
	/* initialization and general commands */
	CMD_SYS_EN          = 0x1,
	CMD_SYS_DIS         = 0x2,
	CMD_MAP_FA          = 0xfff,
	CMD_UNMAP_FA        = 0xffe,
	CMD_RUN_FW          = 0xff6,
	CMD_MOD_STAT_CFG    = 0x34,
	CMD_QUERY_DEV_LIM   = 0x3,
	CMD_QUERY_FW        = 0x4,
	CMD_ENABLE_LAM      = 0xff8,
	CMD_DISABLE_LAM     = 0xff7,
	CMD_QUERY_DDR       = 0x5,
	CMD_QUERY_ADAPTER   = 0x6,
	CMD_INIT_HCA        = 0x7,
	CMD_CLOSE_HCA       = 0x8,
	CMD_INIT_IB         = 0x9,
	CMD_CLOSE_IB        = 0xa,
	CMD_QUERY_HCA       = 0xb,
	CMD_SET_IB          = 0xc,
	CMD_ACCESS_DDR      = 0x2e,
	CMD_MAP_ICM         = 0xffa,
	CMD_UNMAP_ICM       = 0xff9,
	CMD_MAP_ICM_AUX     = 0xffc,
	CMD_UNMAP_ICM_AUX   = 0xffb,
	CMD_SET_ICM_SIZE    = 0xffd,

	/* TPT commands */
	CMD_SW2HW_MPT 	    = 0xd,
	CMD_QUERY_MPT 	    = 0xe,
	CMD_HW2SW_MPT 	    = 0xf,
	CMD_READ_MTT        = 0x10,
	CMD_WRITE_MTT       = 0x11,
	CMD_SYNC_TPT        = 0x2f,

	/* EQ commands */
	CMD_MAP_EQ          = 0x12,
	CMD_SW2HW_EQ 	    = 0x13,
	CMD_HW2SW_EQ 	    = 0x14,
	CMD_QUERY_EQ        = 0x15,

	/* CQ commands */
	CMD_SW2HW_CQ 	    = 0x16,
	CMD_HW2SW_CQ 	    = 0x17,
	CMD_QUERY_CQ 	    = 0x18,
	CMD_RESIZE_CQ       = 0x2c,

	/* SRQ commands */
	CMD_SW2HW_SRQ 	    = 0x35,
	CMD_HW2SW_SRQ 	    = 0x36,
	CMD_QUERY_SRQ       = 0x37,
	CMD_ARM_SRQ         = 0x40,

	/* QP/EE commands */
	CMD_RST2INIT_QPEE   = 0x19,
	CMD_INIT2RTR_QPEE   = 0x1a,
	CMD_RTR2RTS_QPEE    = 0x1b,
	CMD_RTS2RTS_QPEE    = 0x1c,
	CMD_SQERR2RTS_QPEE  = 0x1d,
	CMD_2ERR_QPEE       = 0x1e,
	CMD_RTS2SQD_QPEE    = 0x1f,
	CMD_SQD2SQD_QPEE    = 0x38,
	CMD_SQD2RTS_QPEE    = 0x20,
	CMD_ERR2RST_QPEE    = 0x21,
	CMD_QUERY_QPEE      = 0x22,
	CMD_INIT2INIT_QPEE  = 0x2d,
	CMD_SUSPEND_QPEE    = 0x32,
	CMD_UNSUSPEND_QPEE  = 0x33,
	/* special QPs and management commands */
	CMD_CONF_SPECIAL_QP = 0x23,
	CMD_MAD_IFC         = 0x24,

	/* multicast commands */
	CMD_READ_MGM        = 0x25,
	CMD_WRITE_MGM       = 0x26,
	CMD_MGID_HASH       = 0x27,

	/* miscellaneous commands */
	CMD_DIAG_RPRT       = 0x30,
	CMD_NOP             = 0x31,

	/* debug commands */
	CMD_QUERY_DEBUG_MSG = 0x2a,
	CMD_SET_DEBUG_MSG   = 0x2b,
पूर्ण;

/*
 * According to Mellanox code, FW may be starved and never complete
 * commands.  So we can't use strict समयouts described in PRM -- we
 * just arbitrarily select 60 seconds क्रम now.
 */
#अगर 0
/*
 * Round up and add 1 to make sure we get the full रुको समय (since we
 * will be starting in the middle of a jअगरfy)
 */
क्रमागत अणु
	CMD_TIME_CLASS_A = (HZ + 999) / 1000 + 1,
	CMD_TIME_CLASS_B = (HZ +  99) /  100 + 1,
	CMD_TIME_CLASS_C = (HZ +   9) /   10 + 1,
	CMD_TIME_CLASS_D = 60 * HZ
पूर्ण;
#अन्यथा
क्रमागत अणु
	CMD_TIME_CLASS_A = 60 * HZ,
	CMD_TIME_CLASS_B = 60 * HZ,
	CMD_TIME_CLASS_C = 60 * HZ,
	CMD_TIME_CLASS_D = 60 * HZ
पूर्ण;
#पूर्ण_अगर

क्रमागत अणु
	GO_BIT_TIMEOUT = HZ * 10
पूर्ण;

काष्ठा mthca_cmd_context अणु
	काष्ठा completion करोne;
	पूर्णांक               result;
	पूर्णांक               next;
	u64               out_param;
	u16               token;
	u8                status;
पूर्ण;

अटल पूर्णांक fw_cmd_करोorbell = 0;
module_param(fw_cmd_करोorbell, पूर्णांक, 0644);
MODULE_PARM_DESC(fw_cmd_करोorbell, "post FW commands through doorbell page if nonzero "
		 "(and supported by FW)");

अटल अंतरभूत पूर्णांक go_bit(काष्ठा mthca_dev *dev)
अणु
	वापस पढ़ोl(dev->hcr + HCR_STATUS_OFFSET) &
		swab32(1 << HCR_GO_BIT);
पूर्ण

अटल व्योम mthca_cmd_post_dbell(काष्ठा mthca_dev *dev,
				 u64 in_param,
				 u64 out_param,
				 u32 in_modअगरier,
				 u8 op_modअगरier,
				 u16 op,
				 u16 token)
अणु
	व्योम __iomem *ptr = dev->cmd.dbell_map;
	u16 *offs = dev->cmd.dbell_offsets;

	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(in_param >> 32),           ptr + offs[0]);
	wmb();
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(in_param & 0xfffffffful),  ptr + offs[1]);
	wmb();
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(in_modअगरier),              ptr + offs[2]);
	wmb();
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(out_param >> 32),          ptr + offs[3]);
	wmb();
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(out_param & 0xfffffffful), ptr + offs[4]);
	wmb();
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(token << 16),              ptr + offs[5]);
	wmb();
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32((1 << HCR_GO_BIT)                |
					       (1 << HCA_E_BIT)                 |
					       (op_modअगरier << HCR_OPMOD_SHIFT) |
						op),			  ptr + offs[6]);
	wmb();
	__raw_ग_लिखोl((__क्रमce u32) 0,                                     ptr + offs[7]);
	wmb();
पूर्ण

अटल पूर्णांक mthca_cmd_post_hcr(काष्ठा mthca_dev *dev,
			      u64 in_param,
			      u64 out_param,
			      u32 in_modअगरier,
			      u8 op_modअगरier,
			      u16 op,
			      u16 token,
			      पूर्णांक event)
अणु
	अगर (event) अणु
		अचिन्हित दीर्घ end = jअगरfies + GO_BIT_TIMEOUT;

		जबतक (go_bit(dev) && समय_beक्रमe(jअगरfies, end)) अणु
			set_current_state(TASK_RUNNING);
			schedule();
		पूर्ण
	पूर्ण

	अगर (go_bit(dev))
		वापस -EAGAIN;

	/*
	 * We use ग_लिखोl (instead of something like स_नकल_toio)
	 * because ग_लिखोs of less than 32 bits to the HCR करोn't work
	 * (and some architectures such as ia64 implement स_नकल_toio
	 * in terms of ग_लिखोb).
	 */
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(in_param >> 32),           dev->hcr + 0 * 4);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(in_param & 0xfffffffful),  dev->hcr + 1 * 4);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(in_modअगरier),              dev->hcr + 2 * 4);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(out_param >> 32),          dev->hcr + 3 * 4);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(out_param & 0xfffffffful), dev->hcr + 4 * 4);
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(token << 16),              dev->hcr + 5 * 4);

	/* __raw_ग_लिखोl may not order ग_लिखोs. */
	wmb();

	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32((1 << HCR_GO_BIT)                |
					       (event ? (1 << HCA_E_BIT) : 0)   |
					       (op_modअगरier << HCR_OPMOD_SHIFT) |
					       op),                       dev->hcr + 6 * 4);

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_cmd_post(काष्ठा mthca_dev *dev,
			  u64 in_param,
			  u64 out_param,
			  u32 in_modअगरier,
			  u8 op_modअगरier,
			  u16 op,
			  u16 token,
			  पूर्णांक event)
अणु
	पूर्णांक err = 0;

	mutex_lock(&dev->cmd.hcr_mutex);

	अगर (event && dev->cmd.flags & MTHCA_CMD_POST_DOORBELLS && fw_cmd_करोorbell)
		mthca_cmd_post_dbell(dev, in_param, out_param, in_modअगरier,
					   op_modअगरier, op, token);
	अन्यथा
		err = mthca_cmd_post_hcr(dev, in_param, out_param, in_modअगरier,
					 op_modअगरier, op, token, event);

	mutex_unlock(&dev->cmd.hcr_mutex);
	वापस err;
पूर्ण


अटल पूर्णांक mthca_status_to_त्रुटि_सं(u8 status)
अणु
	अटल स्थिर पूर्णांक trans_table[] = अणु
		[MTHCA_CMD_STAT_INTERNAL_ERR]   = -EIO,
		[MTHCA_CMD_STAT_BAD_OP]         = -EPERM,
		[MTHCA_CMD_STAT_BAD_PARAM]      = -EINVAL,
		[MTHCA_CMD_STAT_BAD_SYS_STATE]  = -ENXIO,
		[MTHCA_CMD_STAT_BAD_RESOURCE]   = -EBADF,
		[MTHCA_CMD_STAT_RESOURCE_BUSY]  = -EBUSY,
		[MTHCA_CMD_STAT_DDR_MEM_ERR]    = -ENOMEM,
		[MTHCA_CMD_STAT_EXCEED_LIM]     = -ENOMEM,
		[MTHCA_CMD_STAT_BAD_RES_STATE]  = -EBADF,
		[MTHCA_CMD_STAT_BAD_INDEX]      = -EBADF,
		[MTHCA_CMD_STAT_BAD_NVMEM]      = -EFAULT,
		[MTHCA_CMD_STAT_BAD_QPEE_STATE] = -EINVAL,
		[MTHCA_CMD_STAT_BAD_SEG_PARAM]  = -EFAULT,
		[MTHCA_CMD_STAT_REG_BOUND]      = -EBUSY,
		[MTHCA_CMD_STAT_LAM_NOT_PRE]    = -EAGAIN,
		[MTHCA_CMD_STAT_BAD_PKT]        = -EBADMSG,
		[MTHCA_CMD_STAT_BAD_SIZE]       = -ENOMEM,
	पूर्ण;

	अगर (status >= ARRAY_SIZE(trans_table) ||
			(status != MTHCA_CMD_STAT_OK
			 && trans_table[status] == 0))
		वापस -EINVAL;

	वापस trans_table[status];
पूर्ण


अटल पूर्णांक mthca_cmd_poll(काष्ठा mthca_dev *dev,
			  u64 in_param,
			  u64 *out_param,
			  पूर्णांक out_is_imm,
			  u32 in_modअगरier,
			  u8 op_modअगरier,
			  u16 op,
			  अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ end;
	u8 status;

	करोwn(&dev->cmd.poll_sem);

	err = mthca_cmd_post(dev, in_param,
			     out_param ? *out_param : 0,
			     in_modअगरier, op_modअगरier,
			     op, CMD_POLL_TOKEN, 0);
	अगर (err)
		जाओ out;

	end = समयout + jअगरfies;
	जबतक (go_bit(dev) && समय_beक्रमe(jअगरfies, end)) अणु
		set_current_state(TASK_RUNNING);
		schedule();
	पूर्ण

	अगर (go_bit(dev)) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (out_is_imm && out_param) अणु
		*out_param =
			(u64) be32_to_cpu((__क्रमce __be32)
					  __raw_पढ़ोl(dev->hcr + HCR_OUT_PARAM_OFFSET)) << 32 |
			(u64) be32_to_cpu((__क्रमce __be32)
					  __raw_पढ़ोl(dev->hcr + HCR_OUT_PARAM_OFFSET + 4));
	पूर्ण अन्यथा अगर (out_is_imm) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	status = be32_to_cpu((__क्रमce __be32) __raw_पढ़ोl(dev->hcr + HCR_STATUS_OFFSET)) >> 24;
	अगर (status) अणु
		mthca_dbg(dev, "Command %02x completed with status %02x\n",
			  op, status);
		err = mthca_status_to_त्रुटि_सं(status);
	पूर्ण

out:
	up(&dev->cmd.poll_sem);
	वापस err;
पूर्ण

व्योम mthca_cmd_event(काष्ठा mthca_dev *dev,
		     u16 token,
		     u8  status,
		     u64 out_param)
अणु
	काष्ठा mthca_cmd_context *context =
		&dev->cmd.context[token & dev->cmd.token_mask];

	/* previously समयd out command completing at दीर्घ last */
	अगर (token != context->token)
		वापस;

	context->result    = 0;
	context->status    = status;
	context->out_param = out_param;

	complete(&context->करोne);
पूर्ण

अटल पूर्णांक mthca_cmd_रुको(काष्ठा mthca_dev *dev,
			  u64 in_param,
			  u64 *out_param,
			  पूर्णांक out_is_imm,
			  u32 in_modअगरier,
			  u8 op_modअगरier,
			  u16 op,
			  अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक err = 0;
	काष्ठा mthca_cmd_context *context;

	करोwn(&dev->cmd.event_sem);

	spin_lock(&dev->cmd.context_lock);
	BUG_ON(dev->cmd.मुक्त_head < 0);
	context = &dev->cmd.context[dev->cmd.मुक्त_head];
	context->token += dev->cmd.token_mask + 1;
	dev->cmd.मुक्त_head = context->next;
	spin_unlock(&dev->cmd.context_lock);

	init_completion(&context->करोne);

	err = mthca_cmd_post(dev, in_param,
			     out_param ? *out_param : 0,
			     in_modअगरier, op_modअगरier,
			     op, context->token, 1);
	अगर (err)
		जाओ out;

	अगर (!रुको_क्रम_completion_समयout(&context->करोne, समयout)) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	err = context->result;
	अगर (err)
		जाओ out;

	अगर (context->status) अणु
		mthca_dbg(dev, "Command %02x completed with status %02x\n",
			  op, context->status);
		err = mthca_status_to_त्रुटि_सं(context->status);
	पूर्ण

	अगर (out_is_imm && out_param) अणु
		*out_param = context->out_param;
	पूर्ण अन्यथा अगर (out_is_imm) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

out:
	spin_lock(&dev->cmd.context_lock);
	context->next = dev->cmd.मुक्त_head;
	dev->cmd.मुक्त_head = context - dev->cmd.context;
	spin_unlock(&dev->cmd.context_lock);

	up(&dev->cmd.event_sem);
	वापस err;
पूर्ण

/* Invoke a command with an output mailbox */
अटल पूर्णांक mthca_cmd_box(काष्ठा mthca_dev *dev,
			 u64 in_param,
			 u64 out_param,
			 u32 in_modअगरier,
			 u8 op_modअगरier,
			 u16 op,
			 अचिन्हित दीर्घ समयout)
अणु
	अगर (dev->cmd.flags & MTHCA_CMD_USE_EVENTS)
		वापस mthca_cmd_रुको(dev, in_param, &out_param, 0,
				      in_modअगरier, op_modअगरier, op,
				      समयout);
	अन्यथा
		वापस mthca_cmd_poll(dev, in_param, &out_param, 0,
				      in_modअगरier, op_modअगरier, op,
				      समयout);
पूर्ण

/* Invoke a command with no output parameter */
अटल पूर्णांक mthca_cmd(काष्ठा mthca_dev *dev,
		     u64 in_param,
		     u32 in_modअगरier,
		     u8 op_modअगरier,
		     u16 op,
		     अचिन्हित दीर्घ समयout)
अणु
	वापस mthca_cmd_box(dev, in_param, 0, in_modअगरier,
			     op_modअगरier, op, समयout);
पूर्ण

/*
 * Invoke a command with an immediate output parameter (and copy the
 * output पूर्णांकo the caller's out_param poपूर्णांकer after the command
 * executes).
 */
अटल पूर्णांक mthca_cmd_imm(काष्ठा mthca_dev *dev,
			 u64 in_param,
			 u64 *out_param,
			 u32 in_modअगरier,
			 u8 op_modअगरier,
			 u16 op,
			 अचिन्हित दीर्घ समयout)
अणु
	अगर (dev->cmd.flags & MTHCA_CMD_USE_EVENTS)
		वापस mthca_cmd_रुको(dev, in_param, out_param, 1,
				      in_modअगरier, op_modअगरier, op,
				      समयout);
	अन्यथा
		वापस mthca_cmd_poll(dev, in_param, out_param, 1,
				      in_modअगरier, op_modअगरier, op,
				      समयout);
पूर्ण

पूर्णांक mthca_cmd_init(काष्ठा mthca_dev *dev)
अणु
	mutex_init(&dev->cmd.hcr_mutex);
	sema_init(&dev->cmd.poll_sem, 1);
	dev->cmd.flags = 0;

	dev->hcr = ioremap(pci_resource_start(dev->pdev, 0) + MTHCA_HCR_BASE,
			   MTHCA_HCR_SIZE);
	अगर (!dev->hcr) अणु
		mthca_err(dev, "Couldn't map command register.");
		वापस -ENOMEM;
	पूर्ण

	dev->cmd.pool = dma_pool_create("mthca_cmd", &dev->pdev->dev,
					MTHCA_MAILBOX_SIZE,
					MTHCA_MAILBOX_SIZE, 0);
	अगर (!dev->cmd.pool) अणु
		iounmap(dev->hcr);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mthca_cmd_cleanup(काष्ठा mthca_dev *dev)
अणु
	dma_pool_destroy(dev->cmd.pool);
	iounmap(dev->hcr);
	अगर (dev->cmd.flags & MTHCA_CMD_POST_DOORBELLS)
		iounmap(dev->cmd.dbell_map);
पूर्ण

/*
 * Switch to using events to issue FW commands (should be called after
 * event queue to command events has been initialized).
 */
पूर्णांक mthca_cmd_use_events(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक i;

	dev->cmd.context = kदो_स्मृति_array(dev->cmd.max_cmds,
					 माप(काष्ठा mthca_cmd_context),
					 GFP_KERNEL);
	अगर (!dev->cmd.context)
		वापस -ENOMEM;

	क्रम (i = 0; i < dev->cmd.max_cmds; ++i) अणु
		dev->cmd.context[i].token = i;
		dev->cmd.context[i].next = i + 1;
	पूर्ण

	dev->cmd.context[dev->cmd.max_cmds - 1].next = -1;
	dev->cmd.मुक्त_head = 0;

	sema_init(&dev->cmd.event_sem, dev->cmd.max_cmds);
	spin_lock_init(&dev->cmd.context_lock);

	क्रम (dev->cmd.token_mask = 1;
	     dev->cmd.token_mask < dev->cmd.max_cmds;
	     dev->cmd.token_mask <<= 1)
		; /* nothing */
	--dev->cmd.token_mask;

	dev->cmd.flags |= MTHCA_CMD_USE_EVENTS;

	करोwn(&dev->cmd.poll_sem);

	वापस 0;
पूर्ण

/*
 * Switch back to polling (used when shutting करोwn the device)
 */
व्योम mthca_cmd_use_polling(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक i;

	dev->cmd.flags &= ~MTHCA_CMD_USE_EVENTS;

	क्रम (i = 0; i < dev->cmd.max_cmds; ++i)
		करोwn(&dev->cmd.event_sem);

	kमुक्त(dev->cmd.context);

	up(&dev->cmd.poll_sem);
पूर्ण

काष्ठा mthca_mailbox *mthca_alloc_mailbox(काष्ठा mthca_dev *dev,
					  gfp_t gfp_mask)
अणु
	काष्ठा mthca_mailbox *mailbox;

	mailbox = kदो_स्मृति(माप *mailbox, gfp_mask);
	अगर (!mailbox)
		वापस ERR_PTR(-ENOMEM);

	mailbox->buf = dma_pool_alloc(dev->cmd.pool, gfp_mask, &mailbox->dma);
	अगर (!mailbox->buf) अणु
		kमुक्त(mailbox);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस mailbox;
पूर्ण

व्योम mthca_मुक्त_mailbox(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox)
अणु
	अगर (!mailbox)
		वापस;

	dma_pool_मुक्त(dev->cmd.pool, mailbox->buf, mailbox->dma);
	kमुक्त(mailbox);
पूर्ण

पूर्णांक mthca_SYS_EN(काष्ठा mthca_dev *dev)
अणु
	u64 out;
	पूर्णांक ret;

	ret = mthca_cmd_imm(dev, 0, &out, 0, 0, CMD_SYS_EN, CMD_TIME_CLASS_D);

	अगर (ret == -ENOMEM)
		mthca_warn(dev, "SYS_EN DDR error: syn=%x, sock=%d, "
			   "sladdr=%d, SPD source=%s\n",
			   (पूर्णांक) (out >> 6) & 0xf, (पूर्णांक) (out >> 4) & 3,
			   (पूर्णांक) (out >> 1) & 7, (पूर्णांक) out & 1 ? "NVMEM" : "DIMM");

	वापस ret;
पूर्ण

पूर्णांक mthca_SYS_DIS(काष्ठा mthca_dev *dev)
अणु
	वापस mthca_cmd(dev, 0, 0, 0, CMD_SYS_DIS, CMD_TIME_CLASS_C);
पूर्ण

अटल पूर्णांक mthca_map_cmd(काष्ठा mthca_dev *dev, u16 op, काष्ठा mthca_icm *icm,
			 u64 virt)
अणु
	काष्ठा mthca_mailbox *mailbox;
	काष्ठा mthca_icm_iter iter;
	__be64 *pages;
	पूर्णांक lg;
	पूर्णांक nent = 0;
	पूर्णांक i;
	पूर्णांक err = 0;
	पूर्णांक ts = 0, tc = 0;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	स_रखो(mailbox->buf, 0, MTHCA_MAILBOX_SIZE);
	pages = mailbox->buf;

	क्रम (mthca_icm_first(icm, &iter);
	     !mthca_icm_last(&iter);
	     mthca_icm_next(&iter)) अणु
		/*
		 * We have to pass pages that are aligned to their
		 * size, so find the least signअगरicant 1 in the
		 * address or size and use that as our log2 size.
		 */
		lg = ffs(mthca_icm_addr(&iter) | mthca_icm_size(&iter)) - 1;
		अगर (lg < MTHCA_ICM_PAGE_SHIFT) अणु
			mthca_warn(dev, "Got FW area not aligned to %d (%llx/%lx).\n",
				   MTHCA_ICM_PAGE_SIZE,
				   (अचिन्हित दीर्घ दीर्घ) mthca_icm_addr(&iter),
				   mthca_icm_size(&iter));
			err = -EINVAL;
			जाओ out;
		पूर्ण
		क्रम (i = 0; i < mthca_icm_size(&iter) >> lg; ++i) अणु
			अगर (virt != -1) अणु
				pages[nent * 2] = cpu_to_be64(virt);
				virt += 1ULL << lg;
			पूर्ण

			pages[nent * 2 + 1] =
				cpu_to_be64((mthca_icm_addr(&iter) + (i << lg)) |
					    (lg - MTHCA_ICM_PAGE_SHIFT));
			ts += 1 << (lg - 10);
			++tc;

			अगर (++nent == MTHCA_MAILBOX_SIZE / 16) अणु
				err = mthca_cmd(dev, mailbox->dma, nent, 0, op,
						CMD_TIME_CLASS_B);
				अगर (err)
					जाओ out;
				nent = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (nent)
		err = mthca_cmd(dev, mailbox->dma, nent, 0, op,
				CMD_TIME_CLASS_B);

	चयन (op) अणु
	हाल CMD_MAP_FA:
		mthca_dbg(dev, "Mapped %d chunks/%d KB for FW.\n", tc, ts);
		अवरोध;
	हाल CMD_MAP_ICM_AUX:
		mthca_dbg(dev, "Mapped %d chunks/%d KB for ICM aux.\n", tc, ts);
		अवरोध;
	हाल CMD_MAP_ICM:
		mthca_dbg(dev, "Mapped %d chunks/%d KB at %llx for ICM.\n",
			  tc, ts, (अचिन्हित दीर्घ दीर्घ) virt - (ts << 10));
		अवरोध;
	पूर्ण

out:
	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_MAP_FA(काष्ठा mthca_dev *dev, काष्ठा mthca_icm *icm)
अणु
	वापस mthca_map_cmd(dev, CMD_MAP_FA, icm, -1);
पूर्ण

पूर्णांक mthca_UNMAP_FA(काष्ठा mthca_dev *dev)
अणु
	वापस mthca_cmd(dev, 0, 0, 0, CMD_UNMAP_FA, CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_RUN_FW(काष्ठा mthca_dev *dev)
अणु
	वापस mthca_cmd(dev, 0, 0, 0, CMD_RUN_FW, CMD_TIME_CLASS_A);
पूर्ण

अटल व्योम mthca_setup_cmd_करोorbells(काष्ठा mthca_dev *dev, u64 base)
अणु
	phys_addr_t addr;
	u16 max_off = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 8; ++i)
		max_off = max(max_off, dev->cmd.dbell_offsets[i]);

	अगर ((base & PAGE_MASK) != ((base + max_off) & PAGE_MASK)) अणु
		mthca_warn(dev, "Firmware doorbell region at 0x%016llx, "
			   "length 0x%x crosses a page boundary\n",
			   (अचिन्हित दीर्घ दीर्घ) base, max_off);
		वापस;
	पूर्ण

	addr = pci_resource_start(dev->pdev, 2) +
		((pci_resource_len(dev->pdev, 2) - 1) & base);
	dev->cmd.dbell_map = ioremap(addr, max_off + माप(u32));
	अगर (!dev->cmd.dbell_map)
		वापस;

	dev->cmd.flags |= MTHCA_CMD_POST_DOORBELLS;
	mthca_dbg(dev, "Mapped doorbell page for posting FW commands\n");
पूर्ण

पूर्णांक mthca_QUERY_FW(काष्ठा mthca_dev *dev)
अणु
	काष्ठा mthca_mailbox *mailbox;
	u32 *outbox;
	u64 base;
	u32 पंचांगp;
	पूर्णांक err = 0;
	u8 lg;
	पूर्णांक i;

#घोषणा QUERY_FW_OUT_SIZE             0x100
#घोषणा QUERY_FW_VER_OFFSET            0x00
#घोषणा QUERY_FW_MAX_CMD_OFFSET        0x0f
#घोषणा QUERY_FW_ERR_START_OFFSET      0x30
#घोषणा QUERY_FW_ERR_SIZE_OFFSET       0x38

#घोषणा QUERY_FW_CMD_DB_EN_OFFSET      0x10
#घोषणा QUERY_FW_CMD_DB_OFFSET         0x50
#घोषणा QUERY_FW_CMD_DB_BASE           0x60

#घोषणा QUERY_FW_START_OFFSET          0x20
#घोषणा QUERY_FW_END_OFFSET            0x28

#घोषणा QUERY_FW_SIZE_OFFSET           0x00
#घोषणा QUERY_FW_CLR_INT_BASE_OFFSET   0x20
#घोषणा QUERY_FW_EQ_ARM_BASE_OFFSET    0x40
#घोषणा QUERY_FW_EQ_SET_CI_BASE_OFFSET 0x48

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mthca_cmd_box(dev, 0, mailbox->dma, 0, 0, CMD_QUERY_FW,
			    CMD_TIME_CLASS_A);

	अगर (err)
		जाओ out;

	MTHCA_GET(dev->fw_ver,   outbox, QUERY_FW_VER_OFFSET);
	/*
	 * FW subminor version is at more signअगरicant bits than minor
	 * version, so swap here.
	 */
	dev->fw_ver = (dev->fw_ver & 0xffff00000000ull) |
		((dev->fw_ver & 0xffff0000ull) >> 16) |
		((dev->fw_ver & 0x0000ffffull) << 16);

	MTHCA_GET(lg, outbox, QUERY_FW_MAX_CMD_OFFSET);
	dev->cmd.max_cmds = 1 << lg;

	mthca_dbg(dev, "FW version %012llx, max commands %d\n",
		  (अचिन्हित दीर्घ दीर्घ) dev->fw_ver, dev->cmd.max_cmds);

	MTHCA_GET(dev->catas_err.addr, outbox, QUERY_FW_ERR_START_OFFSET);
	MTHCA_GET(dev->catas_err.size, outbox, QUERY_FW_ERR_SIZE_OFFSET);

	mthca_dbg(dev, "Catastrophic error buffer at 0x%llx, size 0x%x\n",
		  (अचिन्हित दीर्घ दीर्घ) dev->catas_err.addr, dev->catas_err.size);

	MTHCA_GET(पंचांगp, outbox, QUERY_FW_CMD_DB_EN_OFFSET);
	अगर (पंचांगp & 0x1) अणु
		mthca_dbg(dev, "FW supports commands through doorbells\n");

		MTHCA_GET(base, outbox, QUERY_FW_CMD_DB_BASE);
		क्रम (i = 0; i < MTHCA_CMD_NUM_DBELL_DWORDS; ++i)
			MTHCA_GET(dev->cmd.dbell_offsets[i], outbox,
				  QUERY_FW_CMD_DB_OFFSET + (i << 1));

		mthca_setup_cmd_करोorbells(dev, base);
	पूर्ण

	अगर (mthca_is_memमुक्त(dev)) अणु
		MTHCA_GET(dev->fw.arbel.fw_pages,       outbox, QUERY_FW_SIZE_OFFSET);
		MTHCA_GET(dev->fw.arbel.clr_पूर्णांक_base,   outbox, QUERY_FW_CLR_INT_BASE_OFFSET);
		MTHCA_GET(dev->fw.arbel.eq_arm_base,    outbox, QUERY_FW_EQ_ARM_BASE_OFFSET);
		MTHCA_GET(dev->fw.arbel.eq_set_ci_base, outbox, QUERY_FW_EQ_SET_CI_BASE_OFFSET);
		mthca_dbg(dev, "FW size %d KB\n", dev->fw.arbel.fw_pages << 2);

		/*
		 * Round up number of प्रणाली pages needed in हाल
		 * MTHCA_ICM_PAGE_SIZE < PAGE_SIZE.
		 */
		dev->fw.arbel.fw_pages =
			ALIGN(dev->fw.arbel.fw_pages, PAGE_SIZE / MTHCA_ICM_PAGE_SIZE) >>
				(PAGE_SHIFT - MTHCA_ICM_PAGE_SHIFT);

		mthca_dbg(dev, "Clear int @ %llx, EQ arm @ %llx, EQ set CI @ %llx\n",
			  (अचिन्हित दीर्घ दीर्घ) dev->fw.arbel.clr_पूर्णांक_base,
			  (अचिन्हित दीर्घ दीर्घ) dev->fw.arbel.eq_arm_base,
			  (अचिन्हित दीर्घ दीर्घ) dev->fw.arbel.eq_set_ci_base);
	पूर्ण अन्यथा अणु
		MTHCA_GET(dev->fw.tavor.fw_start, outbox, QUERY_FW_START_OFFSET);
		MTHCA_GET(dev->fw.tavor.fw_end,   outbox, QUERY_FW_END_OFFSET);

		mthca_dbg(dev, "FW size %d KB (start %llx, end %llx)\n",
			  (पूर्णांक) ((dev->fw.tavor.fw_end - dev->fw.tavor.fw_start) >> 10),
			  (अचिन्हित दीर्घ दीर्घ) dev->fw.tavor.fw_start,
			  (अचिन्हित दीर्घ दीर्घ) dev->fw.tavor.fw_end);
	पूर्ण

out:
	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_ENABLE_LAM(काष्ठा mthca_dev *dev)
अणु
	काष्ठा mthca_mailbox *mailbox;
	u8 info;
	u32 *outbox;
	पूर्णांक err = 0;

#घोषणा ENABLE_LAM_OUT_SIZE         0x100
#घोषणा ENABLE_LAM_START_OFFSET     0x00
#घोषणा ENABLE_LAM_END_OFFSET       0x08
#घोषणा ENABLE_LAM_INFO_OFFSET      0x13

#घोषणा ENABLE_LAM_INFO_HIDDEN_FLAG (1 << 4)
#घोषणा ENABLE_LAM_INFO_ECC_MASK    0x3

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mthca_cmd_box(dev, 0, mailbox->dma, 0, 0, CMD_ENABLE_LAM,
			    CMD_TIME_CLASS_C);

	अगर (err)
		जाओ out;

	MTHCA_GET(dev->ddr_start, outbox, ENABLE_LAM_START_OFFSET);
	MTHCA_GET(dev->ddr_end,   outbox, ENABLE_LAM_END_OFFSET);
	MTHCA_GET(info,           outbox, ENABLE_LAM_INFO_OFFSET);

	अगर (!!(info & ENABLE_LAM_INFO_HIDDEN_FLAG) !=
	    !!(dev->mthca_flags & MTHCA_FLAG_DDR_HIDDEN)) अणु
		mthca_info(dev, "FW reports that HCA-attached memory "
			   "is %s hidden; does not match PCI config\n",
			   (info & ENABLE_LAM_INFO_HIDDEN_FLAG) ?
			   "" : "not");
	पूर्ण
	अगर (info & ENABLE_LAM_INFO_HIDDEN_FLAG)
		mthca_dbg(dev, "HCA-attached memory is hidden.\n");

	mthca_dbg(dev, "HCA memory size %d KB (start %llx, end %llx)\n",
		  (पूर्णांक) ((dev->ddr_end - dev->ddr_start) >> 10),
		  (अचिन्हित दीर्घ दीर्घ) dev->ddr_start,
		  (अचिन्हित दीर्घ दीर्घ) dev->ddr_end);

out:
	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_DISABLE_LAM(काष्ठा mthca_dev *dev)
अणु
	वापस mthca_cmd(dev, 0, 0, 0, CMD_SYS_DIS, CMD_TIME_CLASS_C);
पूर्ण

पूर्णांक mthca_QUERY_DDR(काष्ठा mthca_dev *dev)
अणु
	काष्ठा mthca_mailbox *mailbox;
	u8 info;
	u32 *outbox;
	पूर्णांक err = 0;

#घोषणा QUERY_DDR_OUT_SIZE         0x100
#घोषणा QUERY_DDR_START_OFFSET     0x00
#घोषणा QUERY_DDR_END_OFFSET       0x08
#घोषणा QUERY_DDR_INFO_OFFSET      0x13

#घोषणा QUERY_DDR_INFO_HIDDEN_FLAG (1 << 4)
#घोषणा QUERY_DDR_INFO_ECC_MASK    0x3

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mthca_cmd_box(dev, 0, mailbox->dma, 0, 0, CMD_QUERY_DDR,
			    CMD_TIME_CLASS_A);

	अगर (err)
		जाओ out;

	MTHCA_GET(dev->ddr_start, outbox, QUERY_DDR_START_OFFSET);
	MTHCA_GET(dev->ddr_end,   outbox, QUERY_DDR_END_OFFSET);
	MTHCA_GET(info,           outbox, QUERY_DDR_INFO_OFFSET);

	अगर (!!(info & QUERY_DDR_INFO_HIDDEN_FLAG) !=
	    !!(dev->mthca_flags & MTHCA_FLAG_DDR_HIDDEN)) अणु
		mthca_info(dev, "FW reports that HCA-attached memory "
			   "is %s hidden; does not match PCI config\n",
			   (info & QUERY_DDR_INFO_HIDDEN_FLAG) ?
			   "" : "not");
	पूर्ण
	अगर (info & QUERY_DDR_INFO_HIDDEN_FLAG)
		mthca_dbg(dev, "HCA-attached memory is hidden.\n");

	mthca_dbg(dev, "HCA memory size %d KB (start %llx, end %llx)\n",
		  (पूर्णांक) ((dev->ddr_end - dev->ddr_start) >> 10),
		  (अचिन्हित दीर्घ दीर्घ) dev->ddr_start,
		  (अचिन्हित दीर्घ दीर्घ) dev->ddr_end);

out:
	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_QUERY_DEV_LIM(काष्ठा mthca_dev *dev,
			काष्ठा mthca_dev_lim *dev_lim)
अणु
	काष्ठा mthca_mailbox *mailbox;
	u32 *outbox;
	u8 field;
	u16 size;
	u16 stat_rate;
	पूर्णांक err;

#घोषणा QUERY_DEV_LIM_OUT_SIZE             0x100
#घोषणा QUERY_DEV_LIM_MAX_SRQ_SZ_OFFSET     0x10
#घोषणा QUERY_DEV_LIM_MAX_QP_SZ_OFFSET      0x11
#घोषणा QUERY_DEV_LIM_RSVD_QP_OFFSET        0x12
#घोषणा QUERY_DEV_LIM_MAX_QP_OFFSET         0x13
#घोषणा QUERY_DEV_LIM_RSVD_SRQ_OFFSET       0x14
#घोषणा QUERY_DEV_LIM_MAX_SRQ_OFFSET        0x15
#घोषणा QUERY_DEV_LIM_RSVD_EEC_OFFSET       0x16
#घोषणा QUERY_DEV_LIM_MAX_EEC_OFFSET        0x17
#घोषणा QUERY_DEV_LIM_MAX_CQ_SZ_OFFSET      0x19
#घोषणा QUERY_DEV_LIM_RSVD_CQ_OFFSET        0x1a
#घोषणा QUERY_DEV_LIM_MAX_CQ_OFFSET         0x1b
#घोषणा QUERY_DEV_LIM_MAX_MPT_OFFSET        0x1d
#घोषणा QUERY_DEV_LIM_RSVD_EQ_OFFSET        0x1e
#घोषणा QUERY_DEV_LIM_MAX_EQ_OFFSET         0x1f
#घोषणा QUERY_DEV_LIM_RSVD_MTT_OFFSET       0x20
#घोषणा QUERY_DEV_LIM_MAX_MRW_SZ_OFFSET     0x21
#घोषणा QUERY_DEV_LIM_RSVD_MRW_OFFSET       0x22
#घोषणा QUERY_DEV_LIM_MAX_MTT_SEG_OFFSET    0x23
#घोषणा QUERY_DEV_LIM_MAX_AV_OFFSET         0x27
#घोषणा QUERY_DEV_LIM_MAX_REQ_QP_OFFSET     0x29
#घोषणा QUERY_DEV_LIM_MAX_RES_QP_OFFSET     0x2b
#घोषणा QUERY_DEV_LIM_MAX_RDMA_OFFSET       0x2f
#घोषणा QUERY_DEV_LIM_RSZ_SRQ_OFFSET        0x33
#घोषणा QUERY_DEV_LIM_ACK_DELAY_OFFSET      0x35
#घोषणा QUERY_DEV_LIM_MTU_WIDTH_OFFSET      0x36
#घोषणा QUERY_DEV_LIM_VL_PORT_OFFSET        0x37
#घोषणा QUERY_DEV_LIM_MAX_GID_OFFSET        0x3b
#घोषणा QUERY_DEV_LIM_RATE_SUPPORT_OFFSET   0x3c
#घोषणा QUERY_DEV_LIM_MAX_PKEY_OFFSET       0x3f
#घोषणा QUERY_DEV_LIM_FLAGS_OFFSET          0x44
#घोषणा QUERY_DEV_LIM_RSVD_UAR_OFFSET       0x48
#घोषणा QUERY_DEV_LIM_UAR_SZ_OFFSET         0x49
#घोषणा QUERY_DEV_LIM_PAGE_SZ_OFFSET        0x4b
#घोषणा QUERY_DEV_LIM_MAX_SG_OFFSET         0x51
#घोषणा QUERY_DEV_LIM_MAX_DESC_SZ_OFFSET    0x52
#घोषणा QUERY_DEV_LIM_MAX_SG_RQ_OFFSET      0x55
#घोषणा QUERY_DEV_LIM_MAX_DESC_SZ_RQ_OFFSET 0x56
#घोषणा QUERY_DEV_LIM_MAX_QP_MCG_OFFSET     0x61
#घोषणा QUERY_DEV_LIM_RSVD_MCG_OFFSET       0x62
#घोषणा QUERY_DEV_LIM_MAX_MCG_OFFSET        0x63
#घोषणा QUERY_DEV_LIM_RSVD_PD_OFFSET        0x64
#घोषणा QUERY_DEV_LIM_MAX_PD_OFFSET         0x65
#घोषणा QUERY_DEV_LIM_RSVD_RDD_OFFSET       0x66
#घोषणा QUERY_DEV_LIM_MAX_RDD_OFFSET        0x67
#घोषणा QUERY_DEV_LIM_EEC_ENTRY_SZ_OFFSET   0x80
#घोषणा QUERY_DEV_LIM_QPC_ENTRY_SZ_OFFSET   0x82
#घोषणा QUERY_DEV_LIM_EEEC_ENTRY_SZ_OFFSET  0x84
#घोषणा QUERY_DEV_LIM_EQPC_ENTRY_SZ_OFFSET  0x86
#घोषणा QUERY_DEV_LIM_EQC_ENTRY_SZ_OFFSET   0x88
#घोषणा QUERY_DEV_LIM_CQC_ENTRY_SZ_OFFSET   0x8a
#घोषणा QUERY_DEV_LIM_SRQ_ENTRY_SZ_OFFSET   0x8c
#घोषणा QUERY_DEV_LIM_UAR_ENTRY_SZ_OFFSET   0x8e
#घोषणा QUERY_DEV_LIM_MTT_ENTRY_SZ_OFFSET   0x90
#घोषणा QUERY_DEV_LIM_MPT_ENTRY_SZ_OFFSET   0x92
#घोषणा QUERY_DEV_LIM_PBL_SZ_OFFSET         0x96
#घोषणा QUERY_DEV_LIM_BMME_FLAGS_OFFSET     0x97
#घोषणा QUERY_DEV_LIM_RSVD_LKEY_OFFSET      0x98
#घोषणा QUERY_DEV_LIM_LAMR_OFFSET           0x9f
#घोषणा QUERY_DEV_LIM_MAX_ICM_SZ_OFFSET     0xa0

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mthca_cmd_box(dev, 0, mailbox->dma, 0, 0, CMD_QUERY_DEV_LIM,
			    CMD_TIME_CLASS_A);

	अगर (err)
		जाओ out;

	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_QP_OFFSET);
	dev_lim->reserved_qps = 1 << (field & 0xf);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_QP_OFFSET);
	dev_lim->max_qps = 1 << (field & 0x1f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_SRQ_OFFSET);
	dev_lim->reserved_srqs = 1 << (field >> 4);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_SRQ_OFFSET);
	dev_lim->max_srqs = 1 << (field & 0x1f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_EEC_OFFSET);
	dev_lim->reserved_eecs = 1 << (field & 0xf);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_EEC_OFFSET);
	dev_lim->max_eecs = 1 << (field & 0x1f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_CQ_SZ_OFFSET);
	dev_lim->max_cq_sz = 1 << field;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_CQ_OFFSET);
	dev_lim->reserved_cqs = 1 << (field & 0xf);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_CQ_OFFSET);
	dev_lim->max_cqs = 1 << (field & 0x1f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_MPT_OFFSET);
	dev_lim->max_mpts = 1 << (field & 0x3f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_EQ_OFFSET);
	dev_lim->reserved_eqs = 1 << (field & 0xf);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_EQ_OFFSET);
	dev_lim->max_eqs = 1 << (field & 0x7);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_MTT_OFFSET);
	अगर (mthca_is_memमुक्त(dev))
		dev_lim->reserved_mtts = ALIGN((1 << (field >> 4)) * माप(u64),
					       dev->limits.mtt_seg_size) / dev->limits.mtt_seg_size;
	अन्यथा
		dev_lim->reserved_mtts = 1 << (field >> 4);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_MRW_SZ_OFFSET);
	dev_lim->max_mrw_sz = 1 << field;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_MRW_OFFSET);
	dev_lim->reserved_mrws = 1 << (field & 0xf);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_MTT_SEG_OFFSET);
	dev_lim->max_mtt_seg = 1 << (field & 0x3f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_REQ_QP_OFFSET);
	dev_lim->max_requester_per_qp = 1 << (field & 0x3f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_RES_QP_OFFSET);
	dev_lim->max_responder_per_qp = 1 << (field & 0x3f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_RDMA_OFFSET);
	dev_lim->max_rdma_global = 1 << (field & 0x3f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_ACK_DELAY_OFFSET);
	dev_lim->local_ca_ack_delay = field & 0x1f;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MTU_WIDTH_OFFSET);
	dev_lim->max_mtu        = field >> 4;
	dev_lim->max_port_width = field & 0xf;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_VL_PORT_OFFSET);
	dev_lim->max_vl    = field >> 4;
	dev_lim->num_ports = field & 0xf;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_GID_OFFSET);
	dev_lim->max_gids = 1 << (field & 0xf);
	MTHCA_GET(stat_rate, outbox, QUERY_DEV_LIM_RATE_SUPPORT_OFFSET);
	dev_lim->stat_rate_support = stat_rate;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_PKEY_OFFSET);
	dev_lim->max_pkeys = 1 << (field & 0xf);
	MTHCA_GET(dev_lim->flags, outbox, QUERY_DEV_LIM_FLAGS_OFFSET);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_UAR_OFFSET);
	dev_lim->reserved_uars = field >> 4;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_UAR_SZ_OFFSET);
	dev_lim->uar_size = 1 << ((field & 0x3f) + 20);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_PAGE_SZ_OFFSET);
	dev_lim->min_page_sz = 1 << field;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_SG_OFFSET);
	dev_lim->max_sg = field;

	MTHCA_GET(size, outbox, QUERY_DEV_LIM_MAX_DESC_SZ_OFFSET);
	dev_lim->max_desc_sz = size;

	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_QP_MCG_OFFSET);
	dev_lim->max_qp_per_mcg = 1 << field;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_MCG_OFFSET);
	dev_lim->reserved_mgms = field & 0xf;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_MCG_OFFSET);
	dev_lim->max_mcgs = 1 << field;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_PD_OFFSET);
	dev_lim->reserved_pds = field >> 4;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_PD_OFFSET);
	dev_lim->max_pds = 1 << (field & 0x3f);
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSVD_RDD_OFFSET);
	dev_lim->reserved_rdds = field >> 4;
	MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_RDD_OFFSET);
	dev_lim->max_rdds = 1 << (field & 0x3f);

	MTHCA_GET(size, outbox, QUERY_DEV_LIM_EEC_ENTRY_SZ_OFFSET);
	dev_lim->eec_entry_sz = size;
	MTHCA_GET(size, outbox, QUERY_DEV_LIM_QPC_ENTRY_SZ_OFFSET);
	dev_lim->qpc_entry_sz = size;
	MTHCA_GET(size, outbox, QUERY_DEV_LIM_EEEC_ENTRY_SZ_OFFSET);
	dev_lim->eeec_entry_sz = size;
	MTHCA_GET(size, outbox, QUERY_DEV_LIM_EQPC_ENTRY_SZ_OFFSET);
	dev_lim->eqpc_entry_sz = size;
	MTHCA_GET(size, outbox, QUERY_DEV_LIM_EQC_ENTRY_SZ_OFFSET);
	dev_lim->eqc_entry_sz = size;
	MTHCA_GET(size, outbox, QUERY_DEV_LIM_CQC_ENTRY_SZ_OFFSET);
	dev_lim->cqc_entry_sz = size;
	MTHCA_GET(size, outbox, QUERY_DEV_LIM_SRQ_ENTRY_SZ_OFFSET);
	dev_lim->srq_entry_sz = size;
	MTHCA_GET(size, outbox, QUERY_DEV_LIM_UAR_ENTRY_SZ_OFFSET);
	dev_lim->uar_scratch_entry_sz = size;

	अगर (mthca_is_memमुक्त(dev)) अणु
		MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_SRQ_SZ_OFFSET);
		dev_lim->max_srq_sz = 1 << field;
		MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_QP_SZ_OFFSET);
		dev_lim->max_qp_sz = 1 << field;
		MTHCA_GET(field, outbox, QUERY_DEV_LIM_RSZ_SRQ_OFFSET);
		dev_lim->hca.arbel.resize_srq = field & 1;
		MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_SG_RQ_OFFSET);
		dev_lim->max_sg = min_t(पूर्णांक, field, dev_lim->max_sg);
		MTHCA_GET(size, outbox, QUERY_DEV_LIM_MAX_DESC_SZ_RQ_OFFSET);
		dev_lim->max_desc_sz = min_t(पूर्णांक, size, dev_lim->max_desc_sz);
		MTHCA_GET(size, outbox, QUERY_DEV_LIM_MPT_ENTRY_SZ_OFFSET);
		dev_lim->mpt_entry_sz = size;
		MTHCA_GET(field, outbox, QUERY_DEV_LIM_PBL_SZ_OFFSET);
		dev_lim->hca.arbel.max_pbl_sz = 1 << (field & 0x3f);
		MTHCA_GET(dev_lim->hca.arbel.bmme_flags, outbox,
			  QUERY_DEV_LIM_BMME_FLAGS_OFFSET);
		MTHCA_GET(dev_lim->hca.arbel.reserved_lkey, outbox,
			  QUERY_DEV_LIM_RSVD_LKEY_OFFSET);
		MTHCA_GET(field, outbox, QUERY_DEV_LIM_LAMR_OFFSET);
		dev_lim->hca.arbel.lam_required = field & 1;
		MTHCA_GET(dev_lim->hca.arbel.max_icm_sz, outbox,
			  QUERY_DEV_LIM_MAX_ICM_SZ_OFFSET);

		अगर (dev_lim->hca.arbel.bmme_flags & 1)
			mthca_dbg(dev, "Base MM extensions: yes "
				  "(flags %d, max PBL %d, rsvd L_Key %08x)\n",
				  dev_lim->hca.arbel.bmme_flags,
				  dev_lim->hca.arbel.max_pbl_sz,
				  dev_lim->hca.arbel.reserved_lkey);
		अन्यथा
			mthca_dbg(dev, "Base MM extensions: no\n");

		mthca_dbg(dev, "Max ICM size %lld MB\n",
			  (अचिन्हित दीर्घ दीर्घ) dev_lim->hca.arbel.max_icm_sz >> 20);
	पूर्ण अन्यथा अणु
		MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_SRQ_SZ_OFFSET);
		dev_lim->max_srq_sz = (1 << field) - 1;
		MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_QP_SZ_OFFSET);
		dev_lim->max_qp_sz = (1 << field) - 1;
		MTHCA_GET(field, outbox, QUERY_DEV_LIM_MAX_AV_OFFSET);
		dev_lim->hca.tavor.max_avs = 1 << (field & 0x3f);
		dev_lim->mpt_entry_sz = MTHCA_MPT_ENTRY_SIZE;
	पूर्ण

	mthca_dbg(dev, "Max QPs: %d, reserved QPs: %d, entry size: %d\n",
		  dev_lim->max_qps, dev_lim->reserved_qps, dev_lim->qpc_entry_sz);
	mthca_dbg(dev, "Max SRQs: %d, reserved SRQs: %d, entry size: %d\n",
		  dev_lim->max_srqs, dev_lim->reserved_srqs, dev_lim->srq_entry_sz);
	mthca_dbg(dev, "Max CQs: %d, reserved CQs: %d, entry size: %d\n",
		  dev_lim->max_cqs, dev_lim->reserved_cqs, dev_lim->cqc_entry_sz);
	mthca_dbg(dev, "Max EQs: %d, reserved EQs: %d, entry size: %d\n",
		  dev_lim->max_eqs, dev_lim->reserved_eqs, dev_lim->eqc_entry_sz);
	mthca_dbg(dev, "reserved MPTs: %d, reserved MTTs: %d\n",
		  dev_lim->reserved_mrws, dev_lim->reserved_mtts);
	mthca_dbg(dev, "Max PDs: %d, reserved PDs: %d, reserved UARs: %d\n",
		  dev_lim->max_pds, dev_lim->reserved_pds, dev_lim->reserved_uars);
	mthca_dbg(dev, "Max QP/MCG: %d, reserved MGMs: %d\n",
		  dev_lim->max_pds, dev_lim->reserved_mgms);
	mthca_dbg(dev, "Max CQEs: %d, max WQEs: %d, max SRQ WQEs: %d\n",
		  dev_lim->max_cq_sz, dev_lim->max_qp_sz, dev_lim->max_srq_sz);

	mthca_dbg(dev, "Flags: %08x\n", dev_lim->flags);

out:
	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

अटल व्योम get_board_id(व्योम *vsd, अक्षर *board_id)
अणु
	पूर्णांक i;

#घोषणा VSD_OFFSET_SIG1		0x00
#घोषणा VSD_OFFSET_SIG2		0xde
#घोषणा VSD_OFFSET_MLX_BOARD_ID	0xd0
#घोषणा VSD_OFFSET_TS_BOARD_ID	0x20

#घोषणा VSD_SIGNATURE_TOPSPIN	0x5ad

	स_रखो(board_id, 0, MTHCA_BOARD_ID_LEN);

	अगर (be16_to_cpup(vsd + VSD_OFFSET_SIG1) == VSD_SIGNATURE_TOPSPIN &&
	    be16_to_cpup(vsd + VSD_OFFSET_SIG2) == VSD_SIGNATURE_TOPSPIN) अणु
		strlcpy(board_id, vsd + VSD_OFFSET_TS_BOARD_ID, MTHCA_BOARD_ID_LEN);
	पूर्ण अन्यथा अणु
		/*
		 * The board ID is a string but the firmware byte
		 * swaps each 4-byte word beक्रमe passing it back to
		 * us.  Thereक्रमe we need to swab it beक्रमe prपूर्णांकing.
		 */
		क्रम (i = 0; i < 4; ++i)
			((u32 *) board_id)[i] =
				swab32(*(u32 *) (vsd + VSD_OFFSET_MLX_BOARD_ID + i * 4));
	पूर्ण
पूर्ण

पूर्णांक mthca_QUERY_ADAPTER(काष्ठा mthca_dev *dev,
			काष्ठा mthca_adapter *adapter)
अणु
	काष्ठा mthca_mailbox *mailbox;
	u32 *outbox;
	पूर्णांक err;

#घोषणा QUERY_ADAPTER_OUT_SIZE             0x100
#घोषणा QUERY_ADAPTER_VENDOR_ID_OFFSET     0x00
#घोषणा QUERY_ADAPTER_DEVICE_ID_OFFSET     0x04
#घोषणा QUERY_ADAPTER_REVISION_ID_OFFSET   0x08
#घोषणा QUERY_ADAPTER_INTA_PIN_OFFSET      0x10
#घोषणा QUERY_ADAPTER_VSD_OFFSET           0x20

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mthca_cmd_box(dev, 0, mailbox->dma, 0, 0, CMD_QUERY_ADAPTER,
			    CMD_TIME_CLASS_A);

	अगर (err)
		जाओ out;

	अगर (!mthca_is_memमुक्त(dev)) अणु
		MTHCA_GET(adapter->venकरोr_id, outbox,
			  QUERY_ADAPTER_VENDOR_ID_OFFSET);
		MTHCA_GET(adapter->device_id, outbox,
			  QUERY_ADAPTER_DEVICE_ID_OFFSET);
		MTHCA_GET(adapter->revision_id, outbox,
			  QUERY_ADAPTER_REVISION_ID_OFFSET);
	पूर्ण
	MTHCA_GET(adapter->पूर्णांकa_pin, outbox,    QUERY_ADAPTER_INTA_PIN_OFFSET);

	get_board_id(outbox + QUERY_ADAPTER_VSD_OFFSET / 4,
		     adapter->board_id);

out:
	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_INIT_HCA(काष्ठा mthca_dev *dev,
		   काष्ठा mthca_init_hca_param *param)
अणु
	काष्ठा mthca_mailbox *mailbox;
	__be32 *inbox;
	पूर्णांक err;

#घोषणा INIT_HCA_IN_SIZE             	 0x200
#घोषणा INIT_HCA_FLAGS1_OFFSET           0x00c
#घोषणा INIT_HCA_FLAGS2_OFFSET           0x014
#घोषणा INIT_HCA_QPC_OFFSET          	 0x020
#घोषणा  INIT_HCA_QPC_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x10)
#घोषणा  INIT_HCA_LOG_QP_OFFSET      	 (INIT_HCA_QPC_OFFSET + 0x17)
#घोषणा  INIT_HCA_EEC_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x20)
#घोषणा  INIT_HCA_LOG_EEC_OFFSET     	 (INIT_HCA_QPC_OFFSET + 0x27)
#घोषणा  INIT_HCA_SRQC_BASE_OFFSET   	 (INIT_HCA_QPC_OFFSET + 0x28)
#घोषणा  INIT_HCA_LOG_SRQ_OFFSET     	 (INIT_HCA_QPC_OFFSET + 0x2f)
#घोषणा  INIT_HCA_CQC_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x30)
#घोषणा  INIT_HCA_LOG_CQ_OFFSET      	 (INIT_HCA_QPC_OFFSET + 0x37)
#घोषणा  INIT_HCA_EQPC_BASE_OFFSET   	 (INIT_HCA_QPC_OFFSET + 0x40)
#घोषणा  INIT_HCA_EEEC_BASE_OFFSET   	 (INIT_HCA_QPC_OFFSET + 0x50)
#घोषणा  INIT_HCA_EQC_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x60)
#घोषणा  INIT_HCA_LOG_EQ_OFFSET      	 (INIT_HCA_QPC_OFFSET + 0x67)
#घोषणा  INIT_HCA_RDB_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x70)
#घोषणा INIT_HCA_UDAV_OFFSET         	 0x0b0
#घोषणा  INIT_HCA_UDAV_LKEY_OFFSET   	 (INIT_HCA_UDAV_OFFSET + 0x0)
#घोषणा  INIT_HCA_UDAV_PD_OFFSET     	 (INIT_HCA_UDAV_OFFSET + 0x4)
#घोषणा INIT_HCA_MCAST_OFFSET        	 0x0c0
#घोषणा  INIT_HCA_MC_BASE_OFFSET         (INIT_HCA_MCAST_OFFSET + 0x00)
#घोषणा  INIT_HCA_LOG_MC_ENTRY_SZ_OFFSET (INIT_HCA_MCAST_OFFSET + 0x12)
#घोषणा  INIT_HCA_MC_HASH_SZ_OFFSET      (INIT_HCA_MCAST_OFFSET + 0x16)
#घोषणा  INIT_HCA_LOG_MC_TABLE_SZ_OFFSET (INIT_HCA_MCAST_OFFSET + 0x1b)
#घोषणा INIT_HCA_TPT_OFFSET              0x0f0
#घोषणा  INIT_HCA_MPT_BASE_OFFSET        (INIT_HCA_TPT_OFFSET + 0x00)
#घोषणा  INIT_HCA_MTT_SEG_SZ_OFFSET      (INIT_HCA_TPT_OFFSET + 0x09)
#घोषणा  INIT_HCA_LOG_MPT_SZ_OFFSET      (INIT_HCA_TPT_OFFSET + 0x0b)
#घोषणा  INIT_HCA_MTT_BASE_OFFSET        (INIT_HCA_TPT_OFFSET + 0x10)
#घोषणा INIT_HCA_UAR_OFFSET              0x120
#घोषणा  INIT_HCA_UAR_BASE_OFFSET        (INIT_HCA_UAR_OFFSET + 0x00)
#घोषणा  INIT_HCA_UARC_SZ_OFFSET         (INIT_HCA_UAR_OFFSET + 0x09)
#घोषणा  INIT_HCA_LOG_UAR_SZ_OFFSET      (INIT_HCA_UAR_OFFSET + 0x0a)
#घोषणा  INIT_HCA_UAR_PAGE_SZ_OFFSET     (INIT_HCA_UAR_OFFSET + 0x0b)
#घोषणा  INIT_HCA_UAR_SCATCH_BASE_OFFSET (INIT_HCA_UAR_OFFSET + 0x10)
#घोषणा  INIT_HCA_UAR_CTX_BASE_OFFSET    (INIT_HCA_UAR_OFFSET + 0x18)

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	inbox = mailbox->buf;

	स_रखो(inbox, 0, INIT_HCA_IN_SIZE);

	अगर (dev->mthca_flags & MTHCA_FLAG_SINAI_OPT)
		MTHCA_PUT(inbox, 0x1, INIT_HCA_FLAGS1_OFFSET);

#अगर defined(__LITTLE_ENDIAN)
	*(inbox + INIT_HCA_FLAGS2_OFFSET / 4) &= ~cpu_to_be32(1 << 1);
#या_अगर defined(__BIG_ENDIAN)
	*(inbox + INIT_HCA_FLAGS2_OFFSET / 4) |= cpu_to_be32(1 << 1);
#अन्यथा
#त्रुटि Host endianness not defined
#पूर्ण_अगर
	/* Check port क्रम UD address vector: */
	*(inbox + INIT_HCA_FLAGS2_OFFSET / 4) |= cpu_to_be32(1);

	/* Enable IPoIB checksumming अगर we can: */
	अगर (dev->device_cap_flags & IB_DEVICE_UD_IP_CSUM)
		*(inbox + INIT_HCA_FLAGS2_OFFSET / 4) |= cpu_to_be32(7 << 3);

	/* We leave wqe_quota, responder_exu, etc as 0 (शेष) */

	/* QPC/EEC/CQC/EQC/RDB attributes */

	MTHCA_PUT(inbox, param->qpc_base,     INIT_HCA_QPC_BASE_OFFSET);
	MTHCA_PUT(inbox, param->log_num_qps,  INIT_HCA_LOG_QP_OFFSET);
	MTHCA_PUT(inbox, param->eec_base,     INIT_HCA_EEC_BASE_OFFSET);
	MTHCA_PUT(inbox, param->log_num_eecs, INIT_HCA_LOG_EEC_OFFSET);
	MTHCA_PUT(inbox, param->srqc_base,    INIT_HCA_SRQC_BASE_OFFSET);
	MTHCA_PUT(inbox, param->log_num_srqs, INIT_HCA_LOG_SRQ_OFFSET);
	MTHCA_PUT(inbox, param->cqc_base,     INIT_HCA_CQC_BASE_OFFSET);
	MTHCA_PUT(inbox, param->log_num_cqs,  INIT_HCA_LOG_CQ_OFFSET);
	MTHCA_PUT(inbox, param->eqpc_base,    INIT_HCA_EQPC_BASE_OFFSET);
	MTHCA_PUT(inbox, param->eeec_base,    INIT_HCA_EEEC_BASE_OFFSET);
	MTHCA_PUT(inbox, param->eqc_base,     INIT_HCA_EQC_BASE_OFFSET);
	MTHCA_PUT(inbox, param->log_num_eqs,  INIT_HCA_LOG_EQ_OFFSET);
	MTHCA_PUT(inbox, param->rdb_base,     INIT_HCA_RDB_BASE_OFFSET);

	/* UD AV attributes */

	/* multicast attributes */

	MTHCA_PUT(inbox, param->mc_base,         INIT_HCA_MC_BASE_OFFSET);
	MTHCA_PUT(inbox, param->log_mc_entry_sz, INIT_HCA_LOG_MC_ENTRY_SZ_OFFSET);
	MTHCA_PUT(inbox, param->mc_hash_sz,      INIT_HCA_MC_HASH_SZ_OFFSET);
	MTHCA_PUT(inbox, param->log_mc_table_sz, INIT_HCA_LOG_MC_TABLE_SZ_OFFSET);

	/* TPT attributes */

	MTHCA_PUT(inbox, param->mpt_base,   INIT_HCA_MPT_BASE_OFFSET);
	अगर (!mthca_is_memमुक्त(dev))
		MTHCA_PUT(inbox, param->mtt_seg_sz, INIT_HCA_MTT_SEG_SZ_OFFSET);
	MTHCA_PUT(inbox, param->log_mpt_sz, INIT_HCA_LOG_MPT_SZ_OFFSET);
	MTHCA_PUT(inbox, param->mtt_base,   INIT_HCA_MTT_BASE_OFFSET);

	/* UAR attributes */
	अणु
		u8 uar_page_sz = PAGE_SHIFT - 12;
		MTHCA_PUT(inbox, uar_page_sz, INIT_HCA_UAR_PAGE_SZ_OFFSET);
	पूर्ण

	MTHCA_PUT(inbox, param->uar_scratch_base, INIT_HCA_UAR_SCATCH_BASE_OFFSET);

	अगर (mthca_is_memमुक्त(dev)) अणु
		MTHCA_PUT(inbox, param->log_uarc_sz, INIT_HCA_UARC_SZ_OFFSET);
		MTHCA_PUT(inbox, param->log_uar_sz,  INIT_HCA_LOG_UAR_SZ_OFFSET);
		MTHCA_PUT(inbox, param->uarc_base,   INIT_HCA_UAR_CTX_BASE_OFFSET);
	पूर्ण

	err = mthca_cmd(dev, mailbox->dma, 0, 0,
			CMD_INIT_HCA, CMD_TIME_CLASS_D);

	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_INIT_IB(काष्ठा mthca_dev *dev,
		  काष्ठा mthca_init_ib_param *param,
		  पूर्णांक port)
अणु
	काष्ठा mthca_mailbox *mailbox;
	u32 *inbox;
	पूर्णांक err;
	u32 flags;

#घोषणा INIT_IB_IN_SIZE          56
#घोषणा INIT_IB_FLAGS_OFFSET     0x00
#घोषणा INIT_IB_FLAG_SIG         (1 << 18)
#घोषणा INIT_IB_FLAG_NG          (1 << 17)
#घोषणा INIT_IB_FLAG_G0          (1 << 16)
#घोषणा INIT_IB_VL_SHIFT         4
#घोषणा INIT_IB_PORT_WIDTH_SHIFT 8
#घोषणा INIT_IB_MTU_SHIFT        12
#घोषणा INIT_IB_MAX_GID_OFFSET   0x06
#घोषणा INIT_IB_MAX_PKEY_OFFSET  0x0a
#घोषणा INIT_IB_GUID0_OFFSET     0x10
#घोषणा INIT_IB_NODE_GUID_OFFSET 0x18
#घोषणा INIT_IB_SI_GUID_OFFSET   0x20

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	inbox = mailbox->buf;

	स_रखो(inbox, 0, INIT_IB_IN_SIZE);

	flags = 0;
	flags |= param->set_guid0     ? INIT_IB_FLAG_G0  : 0;
	flags |= param->set_node_guid ? INIT_IB_FLAG_NG  : 0;
	flags |= param->set_si_guid   ? INIT_IB_FLAG_SIG : 0;
	flags |= param->vl_cap << INIT_IB_VL_SHIFT;
	flags |= param->port_width << INIT_IB_PORT_WIDTH_SHIFT;
	flags |= param->mtu_cap << INIT_IB_MTU_SHIFT;
	MTHCA_PUT(inbox, flags, INIT_IB_FLAGS_OFFSET);

	MTHCA_PUT(inbox, param->gid_cap,   INIT_IB_MAX_GID_OFFSET);
	MTHCA_PUT(inbox, param->pkey_cap,  INIT_IB_MAX_PKEY_OFFSET);
	MTHCA_PUT(inbox, param->guid0,     INIT_IB_GUID0_OFFSET);
	MTHCA_PUT(inbox, param->node_guid, INIT_IB_NODE_GUID_OFFSET);
	MTHCA_PUT(inbox, param->si_guid,   INIT_IB_SI_GUID_OFFSET);

	err = mthca_cmd(dev, mailbox->dma, port, 0, CMD_INIT_IB,
			CMD_TIME_CLASS_A);

	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_CLOSE_IB(काष्ठा mthca_dev *dev, पूर्णांक port)
अणु
	वापस mthca_cmd(dev, 0, port, 0, CMD_CLOSE_IB, CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_CLOSE_HCA(काष्ठा mthca_dev *dev, पूर्णांक panic)
अणु
	वापस mthca_cmd(dev, 0, 0, panic, CMD_CLOSE_HCA, CMD_TIME_CLASS_C);
पूर्ण

पूर्णांक mthca_SET_IB(काष्ठा mthca_dev *dev, काष्ठा mthca_set_ib_param *param,
		 पूर्णांक port)
अणु
	काष्ठा mthca_mailbox *mailbox;
	u32 *inbox;
	पूर्णांक err;
	u32 flags = 0;

#घोषणा SET_IB_IN_SIZE         0x40
#घोषणा SET_IB_FLAGS_OFFSET    0x00
#घोषणा SET_IB_FLAG_SIG        (1 << 18)
#घोषणा SET_IB_FLAG_RQK        (1 <<  0)
#घोषणा SET_IB_CAP_MASK_OFFSET 0x04
#घोषणा SET_IB_SI_GUID_OFFSET  0x08

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	inbox = mailbox->buf;

	स_रखो(inbox, 0, SET_IB_IN_SIZE);

	flags |= param->set_si_guid     ? SET_IB_FLAG_SIG : 0;
	flags |= param->reset_qkey_viol ? SET_IB_FLAG_RQK : 0;
	MTHCA_PUT(inbox, flags, SET_IB_FLAGS_OFFSET);

	MTHCA_PUT(inbox, param->cap_mask, SET_IB_CAP_MASK_OFFSET);
	MTHCA_PUT(inbox, param->si_guid,  SET_IB_SI_GUID_OFFSET);

	err = mthca_cmd(dev, mailbox->dma, port, 0, CMD_SET_IB,
			CMD_TIME_CLASS_B);

	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_MAP_ICM(काष्ठा mthca_dev *dev, काष्ठा mthca_icm *icm, u64 virt)
अणु
	वापस mthca_map_cmd(dev, CMD_MAP_ICM, icm, virt);
पूर्ण

पूर्णांक mthca_MAP_ICM_page(काष्ठा mthca_dev *dev, u64 dma_addr, u64 virt)
अणु
	काष्ठा mthca_mailbox *mailbox;
	__be64 *inbox;
	पूर्णांक err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	inbox = mailbox->buf;

	inbox[0] = cpu_to_be64(virt);
	inbox[1] = cpu_to_be64(dma_addr);

	err = mthca_cmd(dev, mailbox->dma, 1, 0, CMD_MAP_ICM,
			CMD_TIME_CLASS_B);

	mthca_मुक्त_mailbox(dev, mailbox);

	अगर (!err)
		mthca_dbg(dev, "Mapped page at %llx to %llx for ICM.\n",
			  (अचिन्हित दीर्घ दीर्घ) dma_addr, (अचिन्हित दीर्घ दीर्घ) virt);

	वापस err;
पूर्ण

पूर्णांक mthca_UNMAP_ICM(काष्ठा mthca_dev *dev, u64 virt, u32 page_count)
अणु
	mthca_dbg(dev, "Unmapping %d pages at %llx from ICM.\n",
		  page_count, (अचिन्हित दीर्घ दीर्घ) virt);

	वापस mthca_cmd(dev, virt, page_count, 0,
			CMD_UNMAP_ICM, CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_MAP_ICM_AUX(काष्ठा mthca_dev *dev, काष्ठा mthca_icm *icm)
अणु
	वापस mthca_map_cmd(dev, CMD_MAP_ICM_AUX, icm, -1);
पूर्ण

पूर्णांक mthca_UNMAP_ICM_AUX(काष्ठा mthca_dev *dev)
अणु
	वापस mthca_cmd(dev, 0, 0, 0, CMD_UNMAP_ICM_AUX, CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_SET_ICM_SIZE(काष्ठा mthca_dev *dev, u64 icm_size, u64 *aux_pages)
अणु
	पूर्णांक ret = mthca_cmd_imm(dev, icm_size, aux_pages, 0,
			0, CMD_SET_ICM_SIZE, CMD_TIME_CLASS_A);

	अगर (ret)
		वापस ret;

	/*
	 * Round up number of प्रणाली pages needed in हाल
	 * MTHCA_ICM_PAGE_SIZE < PAGE_SIZE.
	 */
	*aux_pages = ALIGN(*aux_pages, PAGE_SIZE / MTHCA_ICM_PAGE_SIZE) >>
		(PAGE_SHIFT - MTHCA_ICM_PAGE_SHIFT);

	वापस 0;
पूर्ण

पूर्णांक mthca_SW2HW_MPT(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक mpt_index)
अणु
	वापस mthca_cmd(dev, mailbox->dma, mpt_index, 0, CMD_SW2HW_MPT,
			 CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_HW2SW_MPT(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक mpt_index)
अणु
	वापस mthca_cmd_box(dev, 0, mailbox ? mailbox->dma : 0, mpt_index,
			     !mailbox, CMD_HW2SW_MPT,
			     CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_WRITE_MTT(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक num_mtt)
अणु
	वापस mthca_cmd(dev, mailbox->dma, num_mtt, 0, CMD_WRITE_MTT,
			 CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_SYNC_TPT(काष्ठा mthca_dev *dev)
अणु
	वापस mthca_cmd(dev, 0, 0, 0, CMD_SYNC_TPT, CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_MAP_EQ(काष्ठा mthca_dev *dev, u64 event_mask, पूर्णांक unmap,
		 पूर्णांक eq_num)
अणु
	mthca_dbg(dev, "%s mask %016llx for eqn %d\n",
		  unmap ? "Clearing" : "Setting",
		  (अचिन्हित दीर्घ दीर्घ) event_mask, eq_num);
	वापस mthca_cmd(dev, event_mask, (unmap << 31) | eq_num,
			 0, CMD_MAP_EQ, CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_SW2HW_EQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		   पूर्णांक eq_num)
अणु
	वापस mthca_cmd(dev, mailbox->dma, eq_num, 0, CMD_SW2HW_EQ,
			 CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_HW2SW_EQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		   पूर्णांक eq_num)
अणु
	वापस mthca_cmd_box(dev, 0, mailbox->dma, eq_num, 0,
			     CMD_HW2SW_EQ,
			     CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_SW2HW_CQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		   पूर्णांक cq_num)
अणु
	वापस mthca_cmd(dev, mailbox->dma, cq_num, 0, CMD_SW2HW_CQ,
			CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_HW2SW_CQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		   पूर्णांक cq_num)
अणु
	वापस mthca_cmd_box(dev, 0, mailbox->dma, cq_num, 0,
			     CMD_HW2SW_CQ,
			     CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_RESIZE_CQ(काष्ठा mthca_dev *dev, पूर्णांक cq_num, u32 lkey, u8 log_size)
अणु
	काष्ठा mthca_mailbox *mailbox;
	__be32 *inbox;
	पूर्णांक err;

#घोषणा RESIZE_CQ_IN_SIZE		0x40
#घोषणा RESIZE_CQ_LOG_SIZE_OFFSET	0x0c
#घोषणा RESIZE_CQ_LKEY_OFFSET		0x1c

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	inbox = mailbox->buf;

	स_रखो(inbox, 0, RESIZE_CQ_IN_SIZE);
	/*
	 * Leave start address fields zeroed out -- mthca assumes that
	 * MRs क्रम CQs always start at भव address 0.
	 */
	MTHCA_PUT(inbox, log_size, RESIZE_CQ_LOG_SIZE_OFFSET);
	MTHCA_PUT(inbox, lkey,     RESIZE_CQ_LKEY_OFFSET);

	err = mthca_cmd(dev, mailbox->dma, cq_num, 1, CMD_RESIZE_CQ,
			CMD_TIME_CLASS_B);

	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_SW2HW_SRQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक srq_num)
अणु
	वापस mthca_cmd(dev, mailbox->dma, srq_num, 0, CMD_SW2HW_SRQ,
			CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_HW2SW_SRQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक srq_num)
अणु
	वापस mthca_cmd_box(dev, 0, mailbox->dma, srq_num, 0,
			     CMD_HW2SW_SRQ,
			     CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_QUERY_SRQ(काष्ठा mthca_dev *dev, u32 num,
		    काष्ठा mthca_mailbox *mailbox)
अणु
	वापस mthca_cmd_box(dev, 0, mailbox->dma, num, 0,
			     CMD_QUERY_SRQ, CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_ARM_SRQ(काष्ठा mthca_dev *dev, पूर्णांक srq_num, पूर्णांक limit)
अणु
	वापस mthca_cmd(dev, limit, srq_num, 0, CMD_ARM_SRQ,
			 CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_MODIFY_QP(काष्ठा mthca_dev *dev, क्रमागत ib_qp_state cur,
		    क्रमागत ib_qp_state next, u32 num, पूर्णांक is_ee,
		    काष्ठा mthca_mailbox *mailbox, u32 opपंचांगask)
अणु
	अटल स्थिर u16 op[IB_QPS_ERR + 1][IB_QPS_ERR + 1] = अणु
		[IB_QPS_RESET] = अणु
			[IB_QPS_RESET]	= CMD_ERR2RST_QPEE,
			[IB_QPS_ERR]	= CMD_2ERR_QPEE,
			[IB_QPS_INIT]	= CMD_RST2INIT_QPEE,
		पूर्ण,
		[IB_QPS_INIT]  = अणु
			[IB_QPS_RESET]	= CMD_ERR2RST_QPEE,
			[IB_QPS_ERR]	= CMD_2ERR_QPEE,
			[IB_QPS_INIT]	= CMD_INIT2INIT_QPEE,
			[IB_QPS_RTR]	= CMD_INIT2RTR_QPEE,
		पूर्ण,
		[IB_QPS_RTR]   = अणु
			[IB_QPS_RESET]	= CMD_ERR2RST_QPEE,
			[IB_QPS_ERR]	= CMD_2ERR_QPEE,
			[IB_QPS_RTS]	= CMD_RTR2RTS_QPEE,
		पूर्ण,
		[IB_QPS_RTS]   = अणु
			[IB_QPS_RESET]	= CMD_ERR2RST_QPEE,
			[IB_QPS_ERR]	= CMD_2ERR_QPEE,
			[IB_QPS_RTS]	= CMD_RTS2RTS_QPEE,
			[IB_QPS_SQD]	= CMD_RTS2SQD_QPEE,
		पूर्ण,
		[IB_QPS_SQD] = अणु
			[IB_QPS_RESET]	= CMD_ERR2RST_QPEE,
			[IB_QPS_ERR]	= CMD_2ERR_QPEE,
			[IB_QPS_RTS]	= CMD_SQD2RTS_QPEE,
			[IB_QPS_SQD]	= CMD_SQD2SQD_QPEE,
		पूर्ण,
		[IB_QPS_SQE] = अणु
			[IB_QPS_RESET]	= CMD_ERR2RST_QPEE,
			[IB_QPS_ERR]	= CMD_2ERR_QPEE,
			[IB_QPS_RTS]	= CMD_SQERR2RTS_QPEE,
		पूर्ण,
		[IB_QPS_ERR] = अणु
			[IB_QPS_RESET]	= CMD_ERR2RST_QPEE,
			[IB_QPS_ERR]	= CMD_2ERR_QPEE,
		पूर्ण
	पूर्ण;

	u8 op_mod = 0;
	पूर्णांक my_mailbox = 0;
	पूर्णांक err;

	अगर (op[cur][next] == CMD_ERR2RST_QPEE) अणु
		op_mod = 3;	/* करोn't ग_लिखो outbox, any->reset */

		/* For debugging */
		अगर (!mailbox) अणु
			mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
			अगर (!IS_ERR(mailbox)) अणु
				my_mailbox = 1;
				op_mod     = 2;	/* ग_लिखो outbox, any->reset */
			पूर्ण अन्यथा
				mailbox = शून्य;
		पूर्ण

		err = mthca_cmd_box(dev, 0, mailbox ? mailbox->dma : 0,
				    (!!is_ee << 24) | num, op_mod,
				    op[cur][next], CMD_TIME_CLASS_C);

		अगर (0 && mailbox) अणु
			पूर्णांक i;
			mthca_dbg(dev, "Dumping QP context:\n");
			prपूर्णांकk(" %08x\n", be32_to_cpup(mailbox->buf));
			क्रम (i = 0; i < 0x100 / 4; ++i) अणु
				अगर (i % 8 == 0)
					prपूर्णांकk("[%02x] ", i * 4);
				prपूर्णांकk(" %08x",
				       be32_to_cpu(((__be32 *) mailbox->buf)[i + 2]));
				अगर ((i + 1) % 8 == 0)
					prपूर्णांकk("\n");
			पूर्ण
		पूर्ण

		अगर (my_mailbox)
			mthca_मुक्त_mailbox(dev, mailbox);
	पूर्ण अन्यथा अणु
		अगर (0) अणु
			पूर्णांक i;
			mthca_dbg(dev, "Dumping QP context:\n");
			prपूर्णांकk("  opt param mask: %08x\n", be32_to_cpup(mailbox->buf));
			क्रम (i = 0; i < 0x100 / 4; ++i) अणु
				अगर (i % 8 == 0)
					prपूर्णांकk("  [%02x] ", i * 4);
				prपूर्णांकk(" %08x",
				       be32_to_cpu(((__be32 *) mailbox->buf)[i + 2]));
				अगर ((i + 1) % 8 == 0)
					prपूर्णांकk("\n");
			पूर्ण
		पूर्ण

		err = mthca_cmd(dev, mailbox->dma, opपंचांगask | (!!is_ee << 24) | num,
				op_mod, op[cur][next], CMD_TIME_CLASS_C);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mthca_QUERY_QP(काष्ठा mthca_dev *dev, u32 num, पूर्णांक is_ee,
		   काष्ठा mthca_mailbox *mailbox)
अणु
	वापस mthca_cmd_box(dev, 0, mailbox->dma, (!!is_ee << 24) | num, 0,
			     CMD_QUERY_QPEE, CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_CONF_SPECIAL_QP(काष्ठा mthca_dev *dev, पूर्णांक type, u32 qpn)
अणु
	u8 op_mod;

	चयन (type) अणु
	हाल IB_QPT_SMI:
		op_mod = 0;
		अवरोध;
	हाल IB_QPT_GSI:
		op_mod = 1;
		अवरोध;
	हाल IB_QPT_RAW_IPV6:
		op_mod = 2;
		अवरोध;
	हाल IB_QPT_RAW_ETHERTYPE:
		op_mod = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mthca_cmd(dev, 0, qpn, op_mod, CMD_CONF_SPECIAL_QP,
			 CMD_TIME_CLASS_B);
पूर्ण

पूर्णांक mthca_MAD_IFC(काष्ठा mthca_dev *dev, पूर्णांक ignore_mkey, पूर्णांक ignore_bkey,
		  पूर्णांक port, स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		  स्थिर व्योम *in_mad, व्योम *response_mad)
अणु
	काष्ठा mthca_mailbox *inmailbox, *ouपंचांगailbox;
	व्योम *inbox;
	पूर्णांक err;
	u32 in_modअगरier = port;
	u8 op_modअगरier = 0;

#घोषणा MAD_IFC_BOX_SIZE      0x400
#घोषणा MAD_IFC_MY_QPN_OFFSET 0x100
#घोषणा MAD_IFC_RQPN_OFFSET   0x108
#घोषणा MAD_IFC_SL_OFFSET     0x10c
#घोषणा MAD_IFC_G_PATH_OFFSET 0x10d
#घोषणा MAD_IFC_RLID_OFFSET   0x10e
#घोषणा MAD_IFC_PKEY_OFFSET   0x112
#घोषणा MAD_IFC_GRH_OFFSET    0x140

	inmailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(inmailbox))
		वापस PTR_ERR(inmailbox);
	inbox = inmailbox->buf;

	ouपंचांगailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(ouपंचांगailbox)) अणु
		mthca_मुक्त_mailbox(dev, inmailbox);
		वापस PTR_ERR(ouपंचांगailbox);
	पूर्ण

	स_नकल(inbox, in_mad, 256);

	/*
	 * Key check traps can't be generated unless we have in_wc to
	 * tell us where to send the trap.
	 */
	अगर (ignore_mkey || !in_wc)
		op_modअगरier |= 0x1;
	अगर (ignore_bkey || !in_wc)
		op_modअगरier |= 0x2;

	अगर (in_wc) अणु
		u8 val;

		स_रखो(inbox + 256, 0, 256);

		MTHCA_PUT(inbox, in_wc->qp->qp_num, MAD_IFC_MY_QPN_OFFSET);
		MTHCA_PUT(inbox, in_wc->src_qp,     MAD_IFC_RQPN_OFFSET);

		val = in_wc->sl << 4;
		MTHCA_PUT(inbox, val,               MAD_IFC_SL_OFFSET);

		val = in_wc->dlid_path_bits |
			(in_wc->wc_flags & IB_WC_GRH ? 0x80 : 0);
		MTHCA_PUT(inbox, val,               MAD_IFC_G_PATH_OFFSET);

		MTHCA_PUT(inbox, ib_lid_cpu16(in_wc->slid), MAD_IFC_RLID_OFFSET);
		MTHCA_PUT(inbox, in_wc->pkey_index, MAD_IFC_PKEY_OFFSET);

		अगर (in_grh)
			स_नकल(inbox + MAD_IFC_GRH_OFFSET, in_grh, 40);

		op_modअगरier |= 0x4;

		in_modअगरier |= ib_lid_cpu16(in_wc->slid) << 16;
	पूर्ण

	err = mthca_cmd_box(dev, inmailbox->dma, ouपंचांगailbox->dma,
			    in_modअगरier, op_modअगरier,
			    CMD_MAD_IFC, CMD_TIME_CLASS_C);

	अगर (!err)
		स_नकल(response_mad, ouपंचांगailbox->buf, 256);

	mthca_मुक्त_mailbox(dev, inmailbox);
	mthca_मुक्त_mailbox(dev, ouपंचांगailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_READ_MGM(काष्ठा mthca_dev *dev, पूर्णांक index,
		   काष्ठा mthca_mailbox *mailbox)
अणु
	वापस mthca_cmd_box(dev, 0, mailbox->dma, index, 0,
			     CMD_READ_MGM, CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_WRITE_MGM(काष्ठा mthca_dev *dev, पूर्णांक index,
		    काष्ठा mthca_mailbox *mailbox)
अणु
	वापस mthca_cmd(dev, mailbox->dma, index, 0, CMD_WRITE_MGM,
			 CMD_TIME_CLASS_A);
पूर्ण

पूर्णांक mthca_MGID_HASH(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    u16 *hash)
अणु
	u64 imm;
	पूर्णांक err;

	err = mthca_cmd_imm(dev, mailbox->dma, &imm, 0, 0, CMD_MGID_HASH,
			    CMD_TIME_CLASS_A);

	*hash = imm;
	वापस err;
पूर्ण

पूर्णांक mthca_NOP(काष्ठा mthca_dev *dev)
अणु
	वापस mthca_cmd(dev, 0, 0x1f, 0, CMD_NOP, msecs_to_jअगरfies(100));
पूर्ण
