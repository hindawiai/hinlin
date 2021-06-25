<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* hw_ops.c - query/set operations on active SPU context.
 *
 * Copyright (C) IBM 2005
 * Author: Mark Nutter <mnutter@us.ibm.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/poll.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <यंत्र/spu_csa.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश "spufs.h"

अटल पूर्णांक spu_hw_mbox_पढ़ो(काष्ठा spu_context *ctx, u32 * data)
अणु
	काष्ठा spu *spu = ctx->spu;
	काष्ठा spu_problem __iomem *prob = spu->problem;
	u32 mbox_stat;
	पूर्णांक ret = 0;

	spin_lock_irq(&spu->रेजिस्टर_lock);
	mbox_stat = in_be32(&prob->mb_stat_R);
	अगर (mbox_stat & 0x0000ff) अणु
		*data = in_be32(&prob->pu_mb_R);
		ret = 4;
	पूर्ण
	spin_unlock_irq(&spu->रेजिस्टर_lock);
	वापस ret;
पूर्ण

अटल u32 spu_hw_mbox_stat_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस in_be32(&ctx->spu->problem->mb_stat_R);
पूर्ण

अटल __poll_t spu_hw_mbox_stat_poll(काष्ठा spu_context *ctx, __poll_t events)
अणु
	काष्ठा spu *spu = ctx->spu;
	__poll_t ret = 0;
	u32 stat;

	spin_lock_irq(&spu->रेजिस्टर_lock);
	stat = in_be32(&spu->problem->mb_stat_R);

	/* अगर the requested event is there, वापस the poll
	   mask, otherwise enable the पूर्णांकerrupt to get notअगरied,
	   but first mark any pending पूर्णांकerrupts as करोne so
	   we करोn't get woken up unnecessarily */

	अगर (events & (EPOLLIN | EPOLLRDNORM)) अणु
		अगर (stat & 0xff0000)
			ret |= EPOLLIN | EPOLLRDNORM;
		अन्यथा अणु
			spu_पूर्णांक_stat_clear(spu, 2, CLASS2_MAILBOX_INTR);
			spu_पूर्णांक_mask_or(spu, 2, CLASS2_ENABLE_MAILBOX_INTR);
		पूर्ण
	पूर्ण
	अगर (events & (EPOLLOUT | EPOLLWRNORM)) अणु
		अगर (stat & 0x00ff00)
			ret = EPOLLOUT | EPOLLWRNORM;
		अन्यथा अणु
			spu_पूर्णांक_stat_clear(spu, 2,
					CLASS2_MAILBOX_THRESHOLD_INTR);
			spu_पूर्णांक_mask_or(spu, 2,
					CLASS2_ENABLE_MAILBOX_THRESHOLD_INTR);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&spu->रेजिस्टर_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक spu_hw_ibox_पढ़ो(काष्ठा spu_context *ctx, u32 * data)
अणु
	काष्ठा spu *spu = ctx->spu;
	काष्ठा spu_problem __iomem *prob = spu->problem;
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	पूर्णांक ret;

	spin_lock_irq(&spu->रेजिस्टर_lock);
	अगर (in_be32(&prob->mb_stat_R) & 0xff0000) अणु
		/* पढ़ो the first available word */
		*data = in_be64(&priv2->puपूर्णांक_mb_R);
		ret = 4;
	पूर्ण अन्यथा अणु
		/* make sure we get woken up by the पूर्णांकerrupt */
		spu_पूर्णांक_mask_or(spu, 2, CLASS2_ENABLE_MAILBOX_INTR);
		ret = 0;
	पूर्ण
	spin_unlock_irq(&spu->रेजिस्टर_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक spu_hw_wbox_ग_लिखो(काष्ठा spu_context *ctx, u32 data)
अणु
	काष्ठा spu *spu = ctx->spu;
	काष्ठा spu_problem __iomem *prob = spu->problem;
	पूर्णांक ret;

	spin_lock_irq(&spu->रेजिस्टर_lock);
	अगर (in_be32(&prob->mb_stat_R) & 0x00ff00) अणु
		/* we have space to ग_लिखो wbox_data to */
		out_be32(&prob->spu_mb_W, data);
		ret = 4;
	पूर्ण अन्यथा अणु
		/* make sure we get woken up by the पूर्णांकerrupt when space
		   becomes available */
		spu_पूर्णांक_mask_or(spu, 2, CLASS2_ENABLE_MAILBOX_THRESHOLD_INTR);
		ret = 0;
	पूर्ण
	spin_unlock_irq(&spu->रेजिस्टर_lock);
	वापस ret;
पूर्ण

अटल व्योम spu_hw_संकेत1_ग_लिखो(काष्ठा spu_context *ctx, u32 data)
अणु
	out_be32(&ctx->spu->problem->संकेत_notअगरy1, data);
पूर्ण

अटल व्योम spu_hw_संकेत2_ग_लिखो(काष्ठा spu_context *ctx, u32 data)
अणु
	out_be32(&ctx->spu->problem->संकेत_notअगरy2, data);
पूर्ण

अटल व्योम spu_hw_संकेत1_type_set(काष्ठा spu_context *ctx, u64 val)
अणु
	काष्ठा spu *spu = ctx->spu;
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	u64 पंचांगp;

	spin_lock_irq(&spu->रेजिस्टर_lock);
	पंचांगp = in_be64(&priv2->spu_cfg_RW);
	अगर (val)
		पंचांगp |= 1;
	अन्यथा
		पंचांगp &= ~1;
	out_be64(&priv2->spu_cfg_RW, पंचांगp);
	spin_unlock_irq(&spu->रेजिस्टर_lock);
पूर्ण

अटल u64 spu_hw_संकेत1_type_get(काष्ठा spu_context *ctx)
अणु
	वापस ((in_be64(&ctx->spu->priv2->spu_cfg_RW) & 1) != 0);
पूर्ण

अटल व्योम spu_hw_संकेत2_type_set(काष्ठा spu_context *ctx, u64 val)
अणु
	काष्ठा spu *spu = ctx->spu;
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	u64 पंचांगp;

	spin_lock_irq(&spu->रेजिस्टर_lock);
	पंचांगp = in_be64(&priv2->spu_cfg_RW);
	अगर (val)
		पंचांगp |= 2;
	अन्यथा
		पंचांगp &= ~2;
	out_be64(&priv2->spu_cfg_RW, पंचांगp);
	spin_unlock_irq(&spu->रेजिस्टर_lock);
पूर्ण

अटल u64 spu_hw_संकेत2_type_get(काष्ठा spu_context *ctx)
अणु
	वापस ((in_be64(&ctx->spu->priv2->spu_cfg_RW) & 2) != 0);
पूर्ण

अटल u32 spu_hw_npc_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस in_be32(&ctx->spu->problem->spu_npc_RW);
पूर्ण

अटल व्योम spu_hw_npc_ग_लिखो(काष्ठा spu_context *ctx, u32 val)
अणु
	out_be32(&ctx->spu->problem->spu_npc_RW, val);
पूर्ण

अटल u32 spu_hw_status_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस in_be32(&ctx->spu->problem->spu_status_R);
पूर्ण

अटल अक्षर *spu_hw_get_ls(काष्ठा spu_context *ctx)
अणु
	वापस ctx->spu->local_store;
पूर्ण

अटल व्योम spu_hw_privcntl_ग_लिखो(काष्ठा spu_context *ctx, u64 val)
अणु
	out_be64(&ctx->spu->priv2->spu_privcntl_RW, val);
पूर्ण

अटल u32 spu_hw_runcntl_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस in_be32(&ctx->spu->problem->spu_runcntl_RW);
पूर्ण

अटल व्योम spu_hw_runcntl_ग_लिखो(काष्ठा spu_context *ctx, u32 val)
अणु
	spin_lock_irq(&ctx->spu->रेजिस्टर_lock);
	अगर (val & SPU_RUNCNTL_ISOLATE)
		spu_hw_privcntl_ग_लिखो(ctx,
			SPU_PRIVCNT_LOAD_REQUEST_ENABLE_MASK);
	out_be32(&ctx->spu->problem->spu_runcntl_RW, val);
	spin_unlock_irq(&ctx->spu->रेजिस्टर_lock);
पूर्ण

अटल व्योम spu_hw_runcntl_stop(काष्ठा spu_context *ctx)
अणु
	spin_lock_irq(&ctx->spu->रेजिस्टर_lock);
	out_be32(&ctx->spu->problem->spu_runcntl_RW, SPU_RUNCNTL_STOP);
	जबतक (in_be32(&ctx->spu->problem->spu_status_R) & SPU_STATUS_RUNNING)
		cpu_relax();
	spin_unlock_irq(&ctx->spu->रेजिस्टर_lock);
पूर्ण

अटल व्योम spu_hw_master_start(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu *spu = ctx->spu;
	u64 sr1;

	spin_lock_irq(&spu->रेजिस्टर_lock);
	sr1 = spu_mfc_sr1_get(spu) | MFC_STATE1_MASTER_RUN_CONTROL_MASK;
	spu_mfc_sr1_set(spu, sr1);
	spin_unlock_irq(&spu->रेजिस्टर_lock);
पूर्ण

अटल व्योम spu_hw_master_stop(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu *spu = ctx->spu;
	u64 sr1;

	spin_lock_irq(&spu->रेजिस्टर_lock);
	sr1 = spu_mfc_sr1_get(spu) & ~MFC_STATE1_MASTER_RUN_CONTROL_MASK;
	spu_mfc_sr1_set(spu, sr1);
	spin_unlock_irq(&spu->रेजिस्टर_lock);
पूर्ण

अटल पूर्णांक spu_hw_set_mfc_query(काष्ठा spu_context * ctx, u32 mask, u32 mode)
अणु
	काष्ठा spu_problem __iomem *prob = ctx->spu->problem;
	पूर्णांक ret;

	spin_lock_irq(&ctx->spu->रेजिस्टर_lock);
	ret = -EAGAIN;
	अगर (in_be32(&prob->dma_querytype_RW))
		जाओ out;
	ret = 0;
	out_be32(&prob->dma_querymask_RW, mask);
	out_be32(&prob->dma_querytype_RW, mode);
out:
	spin_unlock_irq(&ctx->spu->रेजिस्टर_lock);
	वापस ret;
पूर्ण

अटल u32 spu_hw_पढ़ो_mfc_tagstatus(काष्ठा spu_context * ctx)
अणु
	वापस in_be32(&ctx->spu->problem->dma_tagstatus_R);
पूर्ण

अटल u32 spu_hw_get_mfc_मुक्त_elements(काष्ठा spu_context *ctx)
अणु
	वापस in_be32(&ctx->spu->problem->dma_qstatus_R);
पूर्ण

अटल पूर्णांक spu_hw_send_mfc_command(काष्ठा spu_context *ctx,
					काष्ठा mfc_dma_command *cmd)
अणु
	u32 status;
	काष्ठा spu_problem __iomem *prob = ctx->spu->problem;

	spin_lock_irq(&ctx->spu->रेजिस्टर_lock);
	out_be32(&prob->mfc_lsa_W, cmd->lsa);
	out_be64(&prob->mfc_ea_W, cmd->ea);
	out_be32(&prob->mfc_जोड़_W.by32.mfc_माप_प्रकारag32,
				cmd->size << 16 | cmd->tag);
	out_be32(&prob->mfc_जोड़_W.by32.mfc_class_cmd32,
				cmd->class << 16 | cmd->cmd);
	status = in_be32(&prob->mfc_जोड़_W.by32.mfc_class_cmd32);
	spin_unlock_irq(&ctx->spu->रेजिस्टर_lock);

	चयन (status & 0xffff) अणु
	हाल 0:
		वापस 0;
	हाल 2:
		वापस -EAGAIN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम spu_hw_restart_dma(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = ctx->spu->priv2;

	अगर (!test_bit(SPU_CONTEXT_SWITCH_PENDING, &ctx->spu->flags))
		out_be64(&priv2->mfc_control_RW, MFC_CNTL_RESTART_DMA_COMMAND);
पूर्ण

काष्ठा spu_context_ops spu_hw_ops = अणु
	.mbox_पढ़ो = spu_hw_mbox_पढ़ो,
	.mbox_stat_पढ़ो = spu_hw_mbox_stat_पढ़ो,
	.mbox_stat_poll = spu_hw_mbox_stat_poll,
	.ibox_पढ़ो = spu_hw_ibox_पढ़ो,
	.wbox_ग_लिखो = spu_hw_wbox_ग_लिखो,
	.संकेत1_ग_लिखो = spu_hw_संकेत1_ग_लिखो,
	.संकेत2_ग_लिखो = spu_hw_संकेत2_ग_लिखो,
	.संकेत1_type_set = spu_hw_संकेत1_type_set,
	.संकेत1_type_get = spu_hw_संकेत1_type_get,
	.संकेत2_type_set = spu_hw_संकेत2_type_set,
	.संकेत2_type_get = spu_hw_संकेत2_type_get,
	.npc_पढ़ो = spu_hw_npc_पढ़ो,
	.npc_ग_लिखो = spu_hw_npc_ग_लिखो,
	.status_पढ़ो = spu_hw_status_पढ़ो,
	.get_ls = spu_hw_get_ls,
	.privcntl_ग_लिखो = spu_hw_privcntl_ग_लिखो,
	.runcntl_पढ़ो = spu_hw_runcntl_पढ़ो,
	.runcntl_ग_लिखो = spu_hw_runcntl_ग_लिखो,
	.runcntl_stop = spu_hw_runcntl_stop,
	.master_start = spu_hw_master_start,
	.master_stop = spu_hw_master_stop,
	.set_mfc_query = spu_hw_set_mfc_query,
	.पढ़ो_mfc_tagstatus = spu_hw_पढ़ो_mfc_tagstatus,
	.get_mfc_मुक्त_elements = spu_hw_get_mfc_मुक्त_elements,
	.send_mfc_command = spu_hw_send_mfc_command,
	.restart_dma = spu_hw_restart_dma,
पूर्ण;
