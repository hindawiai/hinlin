<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
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

#समावेश <linux/dmapool.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "hns_roce_common.h"
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_cmd.h"

#घोषणा CMD_POLL_TOKEN 0xffff
#घोषणा CMD_MAX_NUM 32

अटल पूर्णांक hns_roce_cmd_mbox_post_hw(काष्ठा hns_roce_dev *hr_dev, u64 in_param,
				     u64 out_param, u32 in_modअगरier,
				     u8 op_modअगरier, u16 op, u16 token,
				     पूर्णांक event)
अणु
	वापस hr_dev->hw->post_mbox(hr_dev, in_param, out_param, in_modअगरier,
				     op_modअगरier, op, token, event);
पूर्ण

/* this should be called with "poll_sem" */
अटल पूर्णांक __hns_roce_cmd_mbox_poll(काष्ठा hns_roce_dev *hr_dev, u64 in_param,
				    u64 out_param, अचिन्हित दीर्घ in_modअगरier,
				    u8 op_modअगरier, u16 op,
				    अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक ret;

	ret = hns_roce_cmd_mbox_post_hw(hr_dev, in_param, out_param,
					in_modअगरier, op_modअगरier, op,
					CMD_POLL_TOKEN, 0);
	अगर (ret) अणु
		dev_err_ratelimited(hr_dev->dev,
				    "failed to post mailbox %x in poll mode, ret = %d.\n",
				    op, ret);
		वापस ret;
	पूर्ण

	वापस hr_dev->hw->poll_mbox_करोne(hr_dev, समयout);
पूर्ण

अटल पूर्णांक hns_roce_cmd_mbox_poll(काष्ठा hns_roce_dev *hr_dev, u64 in_param,
				  u64 out_param, अचिन्हित दीर्घ in_modअगरier,
				  u8 op_modअगरier, u16 op, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक ret;

	करोwn(&hr_dev->cmd.poll_sem);
	ret = __hns_roce_cmd_mbox_poll(hr_dev, in_param, out_param, in_modअगरier,
				       op_modअगरier, op, समयout);
	up(&hr_dev->cmd.poll_sem);

	वापस ret;
पूर्ण

व्योम hns_roce_cmd_event(काष्ठा hns_roce_dev *hr_dev, u16 token, u8 status,
			u64 out_param)
अणु
	काष्ठा hns_roce_cmd_context *context =
		&hr_dev->cmd.context[token % hr_dev->cmd.max_cmds];

	अगर (unlikely(token != context->token)) अणु
		dev_err_ratelimited(hr_dev->dev,
				    "[cmd] invalid ae token %x,context token is %x!\n",
				    token, context->token);
		वापस;
	पूर्ण

	context->result = (status == HNS_ROCE_CMD_SUCCESS) ? 0 : (-EIO);
	context->out_param = out_param;
	complete(&context->करोne);
पूर्ण

अटल पूर्णांक __hns_roce_cmd_mbox_रुको(काष्ठा hns_roce_dev *hr_dev, u64 in_param,
				    u64 out_param, अचिन्हित दीर्घ in_modअगरier,
				    u8 op_modअगरier, u16 op,
				    अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा hns_roce_cmdq *cmd = &hr_dev->cmd;
	काष्ठा hns_roce_cmd_context *context;
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक ret;

	spin_lock(&cmd->context_lock);

	करो अणु
		context = &cmd->context[cmd->मुक्त_head];
		cmd->मुक्त_head = context->next;
	पूर्ण जबतक (context->busy);

	context->busy = 1;
	context->token += cmd->max_cmds;

	spin_unlock(&cmd->context_lock);

	reinit_completion(&context->करोne);

	ret = hns_roce_cmd_mbox_post_hw(hr_dev, in_param, out_param,
					in_modअगरier, op_modअगरier, op,
					context->token, 1);
	अगर (ret) अणु
		dev_err_ratelimited(dev,
				    "failed to post mailbox %x in event mode, ret = %d.\n",
				    op, ret);
		जाओ out;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&context->करोne,
					 msecs_to_jअगरfies(समयout))) अणु
		dev_err_ratelimited(dev, "[cmd] token %x mailbox %x timeout.\n",
				    context->token, op);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = context->result;
	अगर (ret)
		dev_err_ratelimited(dev, "[cmd] token %x mailbox %x error %d\n",
				    context->token, op, ret);

out:
	context->busy = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_cmd_mbox_रुको(काष्ठा hns_roce_dev *hr_dev, u64 in_param,
				  u64 out_param, अचिन्हित दीर्घ in_modअगरier,
				  u8 op_modअगरier, u16 op, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक ret;

	करोwn(&hr_dev->cmd.event_sem);
	ret = __hns_roce_cmd_mbox_रुको(hr_dev, in_param, out_param, in_modअगरier,
				       op_modअगरier, op, समयout);
	up(&hr_dev->cmd.event_sem);

	वापस ret;
पूर्ण

पूर्णांक hns_roce_cmd_mbox(काष्ठा hns_roce_dev *hr_dev, u64 in_param, u64 out_param,
		      अचिन्हित दीर्घ in_modअगरier, u8 op_modअगरier, u16 op,
		      अचिन्हित पूर्णांक समयout)
अणु
	bool is_busy;

	अगर (hr_dev->hw->chk_mbox_avail)
		अगर (!hr_dev->hw->chk_mbox_avail(hr_dev, &is_busy))
			वापस is_busy ? -EBUSY : 0;

	अगर (hr_dev->cmd.use_events)
		वापस hns_roce_cmd_mbox_रुको(hr_dev, in_param, out_param,
					      in_modअगरier, op_modअगरier, op,
					      समयout);
	अन्यथा
		वापस hns_roce_cmd_mbox_poll(hr_dev, in_param, out_param,
					      in_modअगरier, op_modअगरier, op,
					      समयout);
पूर्ण

पूर्णांक hns_roce_cmd_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	sema_init(&hr_dev->cmd.poll_sem, 1);
	hr_dev->cmd.use_events = 0;
	hr_dev->cmd.max_cmds = CMD_MAX_NUM;
	hr_dev->cmd.pool = dma_pool_create("hns_roce_cmd", hr_dev->dev,
					   HNS_ROCE_MAILBOX_SIZE,
					   HNS_ROCE_MAILBOX_SIZE, 0);
	अगर (!hr_dev->cmd.pool)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम hns_roce_cmd_cleanup(काष्ठा hns_roce_dev *hr_dev)
अणु
	dma_pool_destroy(hr_dev->cmd.pool);
पूर्ण

पूर्णांक hns_roce_cmd_use_events(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_cmdq *hr_cmd = &hr_dev->cmd;
	पूर्णांक i;

	hr_cmd->context =
		kसुस्मृति(hr_cmd->max_cmds, माप(*hr_cmd->context), GFP_KERNEL);
	अगर (!hr_cmd->context)
		वापस -ENOMEM;

	क्रम (i = 0; i < hr_cmd->max_cmds; ++i) अणु
		hr_cmd->context[i].token = i;
		hr_cmd->context[i].next = i + 1;
		init_completion(&hr_cmd->context[i].करोne);
	पूर्ण
	hr_cmd->context[hr_cmd->max_cmds - 1].next = 0;
	hr_cmd->मुक्त_head = 0;

	sema_init(&hr_cmd->event_sem, hr_cmd->max_cmds);
	spin_lock_init(&hr_cmd->context_lock);

	hr_cmd->use_events = 1;
	करोwn(&hr_cmd->poll_sem);

	वापस 0;
पूर्ण

व्योम hns_roce_cmd_use_polling(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_cmdq *hr_cmd = &hr_dev->cmd;

	kमुक्त(hr_cmd->context);
	hr_cmd->use_events = 0;

	up(&hr_cmd->poll_sem);
पूर्ण

काष्ठा hns_roce_cmd_mailbox *
hns_roce_alloc_cmd_mailbox(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_cmd_mailbox *mailbox;

	mailbox = kदो_स्मृति(माप(*mailbox), GFP_KERNEL);
	अगर (!mailbox)
		वापस ERR_PTR(-ENOMEM);

	mailbox->buf =
		dma_pool_alloc(hr_dev->cmd.pool, GFP_KERNEL, &mailbox->dma);
	अगर (!mailbox->buf) अणु
		kमुक्त(mailbox);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस mailbox;
पूर्ण

व्योम hns_roce_मुक्त_cmd_mailbox(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा hns_roce_cmd_mailbox *mailbox)
अणु
	अगर (!mailbox)
		वापस;

	dma_pool_मुक्त(hr_dev->cmd.pool, mailbox->buf, mailbox->dma);
	kमुक्त(mailbox);
पूर्ण
