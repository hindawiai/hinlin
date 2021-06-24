<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* backing_ops.c - query/set operations on saved SPU context.
 *
 * Copyright (C) IBM 2005
 * Author: Mark Nutter <mnutter@us.ibm.com>
 *
 * These रेजिस्टर operations allow SPUFS to operate on saved
 * SPU contexts rather than hardware.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/poll.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_csa.h>
#समावेश <यंत्र/spu_info.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश "spufs.h"

/*
 * Reads/ग_लिखोs to various problem and priv2 रेजिस्टरs require
 * state changes, i.e.  generate SPU events, modअगरy channel
 * counts, etc.
 */

अटल व्योम gen_spu_event(काष्ठा spu_context *ctx, u32 event)
अणु
	u64 ch0_cnt;
	u64 ch0_data;
	u64 ch1_data;

	ch0_cnt = ctx->csa.spu_chnlcnt_RW[0];
	ch0_data = ctx->csa.spu_chnldata_RW[0];
	ch1_data = ctx->csa.spu_chnldata_RW[1];
	ctx->csa.spu_chnldata_RW[0] |= event;
	अगर ((ch0_cnt == 0) && !(ch0_data & event) && (ch1_data & event)) अणु
		ctx->csa.spu_chnlcnt_RW[0] = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक spu_backing_mbox_पढ़ो(काष्ठा spu_context *ctx, u32 * data)
अणु
	u32 mbox_stat;
	पूर्णांक ret = 0;

	spin_lock(&ctx->csa.रेजिस्टर_lock);
	mbox_stat = ctx->csa.prob.mb_stat_R;
	अगर (mbox_stat & 0x0000ff) अणु
		/* Read the first available word.
		 * Implementation note: the depth
		 * of pu_mb_R is currently 1.
		 */
		*data = ctx->csa.prob.pu_mb_R;
		ctx->csa.prob.mb_stat_R &= ~(0x0000ff);
		ctx->csa.spu_chnlcnt_RW[28] = 1;
		gen_spu_event(ctx, MFC_PU_MAILBOX_AVAILABLE_EVENT);
		ret = 4;
	पूर्ण
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
	वापस ret;
पूर्ण

अटल u32 spu_backing_mbox_stat_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस ctx->csa.prob.mb_stat_R;
पूर्ण

अटल __poll_t spu_backing_mbox_stat_poll(काष्ठा spu_context *ctx,
					  __poll_t events)
अणु
	__poll_t ret;
	u32 stat;

	ret = 0;
	spin_lock_irq(&ctx->csa.रेजिस्टर_lock);
	stat = ctx->csa.prob.mb_stat_R;

	/* अगर the requested event is there, वापस the poll
	   mask, otherwise enable the पूर्णांकerrupt to get notअगरied,
	   but first mark any pending पूर्णांकerrupts as करोne so
	   we करोn't get woken up unnecessarily */

	अगर (events & (EPOLLIN | EPOLLRDNORM)) अणु
		अगर (stat & 0xff0000)
			ret |= EPOLLIN | EPOLLRDNORM;
		अन्यथा अणु
			ctx->csa.priv1.पूर्णांक_stat_class2_RW &=
				~CLASS2_MAILBOX_INTR;
			ctx->csa.priv1.पूर्णांक_mask_class2_RW |=
				CLASS2_ENABLE_MAILBOX_INTR;
		पूर्ण
	पूर्ण
	अगर (events & (EPOLLOUT | EPOLLWRNORM)) अणु
		अगर (stat & 0x00ff00)
			ret = EPOLLOUT | EPOLLWRNORM;
		अन्यथा अणु
			ctx->csa.priv1.पूर्णांक_stat_class2_RW &=
				~CLASS2_MAILBOX_THRESHOLD_INTR;
			ctx->csa.priv1.पूर्णांक_mask_class2_RW |=
				CLASS2_ENABLE_MAILBOX_THRESHOLD_INTR;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&ctx->csa.रेजिस्टर_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक spu_backing_ibox_पढ़ो(काष्ठा spu_context *ctx, u32 * data)
अणु
	पूर्णांक ret;

	spin_lock(&ctx->csa.रेजिस्टर_lock);
	अगर (ctx->csa.prob.mb_stat_R & 0xff0000) अणु
		/* Read the first available word.
		 * Implementation note: the depth
		 * of puपूर्णांक_mb_R is currently 1.
		 */
		*data = ctx->csa.priv2.puपूर्णांक_mb_R;
		ctx->csa.prob.mb_stat_R &= ~(0xff0000);
		ctx->csa.spu_chnlcnt_RW[30] = 1;
		gen_spu_event(ctx, MFC_PU_INT_MAILBOX_AVAILABLE_EVENT);
		ret = 4;
	पूर्ण अन्यथा अणु
		/* make sure we get woken up by the पूर्णांकerrupt */
		ctx->csa.priv1.पूर्णांक_mask_class2_RW |= CLASS2_ENABLE_MAILBOX_INTR;
		ret = 0;
	पूर्ण
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक spu_backing_wbox_ग_लिखो(काष्ठा spu_context *ctx, u32 data)
अणु
	पूर्णांक ret;

	spin_lock(&ctx->csa.रेजिस्टर_lock);
	अगर ((ctx->csa.prob.mb_stat_R) & 0x00ff00) अणु
		पूर्णांक slot = ctx->csa.spu_chnlcnt_RW[29];
		पूर्णांक avail = (ctx->csa.prob.mb_stat_R & 0x00ff00) >> 8;

		/* We have space to ग_लिखो wbox_data.
		 * Implementation note: the depth
		 * of spu_mb_W is currently 4.
		 */
		BUG_ON(avail != (4 - slot));
		ctx->csa.spu_mailbox_data[slot] = data;
		ctx->csa.spu_chnlcnt_RW[29] = ++slot;
		ctx->csa.prob.mb_stat_R &= ~(0x00ff00);
		ctx->csa.prob.mb_stat_R |= (((4 - slot) & 0xff) << 8);
		gen_spu_event(ctx, MFC_SPU_MAILBOX_WRITTEN_EVENT);
		ret = 4;
	पूर्ण अन्यथा अणु
		/* make sure we get woken up by the पूर्णांकerrupt when space
		   becomes available */
		ctx->csa.priv1.पूर्णांक_mask_class2_RW |=
			CLASS2_ENABLE_MAILBOX_THRESHOLD_INTR;
		ret = 0;
	पूर्ण
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
	वापस ret;
पूर्ण

अटल u32 spu_backing_संकेत1_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस ctx->csa.spu_chnldata_RW[3];
पूर्ण

अटल व्योम spu_backing_संकेत1_ग_लिखो(काष्ठा spu_context *ctx, u32 data)
अणु
	spin_lock(&ctx->csa.रेजिस्टर_lock);
	अगर (ctx->csa.priv2.spu_cfg_RW & 0x1)
		ctx->csa.spu_chnldata_RW[3] |= data;
	अन्यथा
		ctx->csa.spu_chnldata_RW[3] = data;
	ctx->csa.spu_chnlcnt_RW[3] = 1;
	gen_spu_event(ctx, MFC_SIGNAL_1_EVENT);
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
पूर्ण

अटल u32 spu_backing_संकेत2_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस ctx->csa.spu_chnldata_RW[4];
पूर्ण

अटल व्योम spu_backing_संकेत2_ग_लिखो(काष्ठा spu_context *ctx, u32 data)
अणु
	spin_lock(&ctx->csa.रेजिस्टर_lock);
	अगर (ctx->csa.priv2.spu_cfg_RW & 0x2)
		ctx->csa.spu_chnldata_RW[4] |= data;
	अन्यथा
		ctx->csa.spu_chnldata_RW[4] = data;
	ctx->csa.spu_chnlcnt_RW[4] = 1;
	gen_spu_event(ctx, MFC_SIGNAL_2_EVENT);
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
पूर्ण

अटल व्योम spu_backing_संकेत1_type_set(काष्ठा spu_context *ctx, u64 val)
अणु
	u64 पंचांगp;

	spin_lock(&ctx->csa.रेजिस्टर_lock);
	पंचांगp = ctx->csa.priv2.spu_cfg_RW;
	अगर (val)
		पंचांगp |= 1;
	अन्यथा
		पंचांगp &= ~1;
	ctx->csa.priv2.spu_cfg_RW = पंचांगp;
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
पूर्ण

अटल u64 spu_backing_संकेत1_type_get(काष्ठा spu_context *ctx)
अणु
	वापस ((ctx->csa.priv2.spu_cfg_RW & 1) != 0);
पूर्ण

अटल व्योम spu_backing_संकेत2_type_set(काष्ठा spu_context *ctx, u64 val)
अणु
	u64 पंचांगp;

	spin_lock(&ctx->csa.रेजिस्टर_lock);
	पंचांगp = ctx->csa.priv2.spu_cfg_RW;
	अगर (val)
		पंचांगp |= 2;
	अन्यथा
		पंचांगp &= ~2;
	ctx->csa.priv2.spu_cfg_RW = पंचांगp;
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
पूर्ण

अटल u64 spu_backing_संकेत2_type_get(काष्ठा spu_context *ctx)
अणु
	वापस ((ctx->csa.priv2.spu_cfg_RW & 2) != 0);
पूर्ण

अटल u32 spu_backing_npc_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस ctx->csa.prob.spu_npc_RW;
पूर्ण

अटल व्योम spu_backing_npc_ग_लिखो(काष्ठा spu_context *ctx, u32 val)
अणु
	ctx->csa.prob.spu_npc_RW = val;
पूर्ण

अटल u32 spu_backing_status_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस ctx->csa.prob.spu_status_R;
पूर्ण

अटल अक्षर *spu_backing_get_ls(काष्ठा spu_context *ctx)
अणु
	वापस ctx->csa.lscsa->ls;
पूर्ण

अटल व्योम spu_backing_privcntl_ग_लिखो(काष्ठा spu_context *ctx, u64 val)
अणु
	ctx->csa.priv2.spu_privcntl_RW = val;
पूर्ण

अटल u32 spu_backing_runcntl_पढ़ो(काष्ठा spu_context *ctx)
अणु
	वापस ctx->csa.prob.spu_runcntl_RW;
पूर्ण

अटल व्योम spu_backing_runcntl_ग_लिखो(काष्ठा spu_context *ctx, u32 val)
अणु
	spin_lock(&ctx->csa.रेजिस्टर_lock);
	ctx->csa.prob.spu_runcntl_RW = val;
	अगर (val & SPU_RUNCNTL_RUNNABLE) अणु
		ctx->csa.prob.spu_status_R &=
			~SPU_STATUS_STOPPED_BY_STOP &
			~SPU_STATUS_STOPPED_BY_HALT &
			~SPU_STATUS_SINGLE_STEP &
			~SPU_STATUS_INVALID_INSTR &
			~SPU_STATUS_INVALID_CH;
		ctx->csa.prob.spu_status_R |= SPU_STATUS_RUNNING;
	पूर्ण अन्यथा अणु
		ctx->csa.prob.spu_status_R &= ~SPU_STATUS_RUNNING;
	पूर्ण
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
पूर्ण

अटल व्योम spu_backing_runcntl_stop(काष्ठा spu_context *ctx)
अणु
	spu_backing_runcntl_ग_लिखो(ctx, SPU_RUNCNTL_STOP);
पूर्ण

अटल व्योम spu_backing_master_start(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_state *csa = &ctx->csa;
	u64 sr1;

	spin_lock(&csa->रेजिस्टर_lock);
	sr1 = csa->priv1.mfc_sr1_RW | MFC_STATE1_MASTER_RUN_CONTROL_MASK;
	csa->priv1.mfc_sr1_RW = sr1;
	spin_unlock(&csa->रेजिस्टर_lock);
पूर्ण

अटल व्योम spu_backing_master_stop(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_state *csa = &ctx->csa;
	u64 sr1;

	spin_lock(&csa->रेजिस्टर_lock);
	sr1 = csa->priv1.mfc_sr1_RW & ~MFC_STATE1_MASTER_RUN_CONTROL_MASK;
	csa->priv1.mfc_sr1_RW = sr1;
	spin_unlock(&csa->रेजिस्टर_lock);
पूर्ण

अटल पूर्णांक spu_backing_set_mfc_query(काष्ठा spu_context * ctx, u32 mask,
					u32 mode)
अणु
	काष्ठा spu_problem_collapsed *prob = &ctx->csa.prob;
	पूर्णांक ret;

	spin_lock(&ctx->csa.रेजिस्टर_lock);
	ret = -EAGAIN;
	अगर (prob->dma_querytype_RW)
		जाओ out;
	ret = 0;
	/* FIXME: what are the side-effects of this? */
	prob->dma_querymask_RW = mask;
	prob->dma_querytype_RW = mode;
	/* In the current implementation, the SPU context is always
	 * acquired in runnable state when new bits are added to the
	 * mask (tagरुको), so it's sufficient just to mask
	 * dma_tagstatus_R with the 'mask' parameter here.
	 */
	ctx->csa.prob.dma_tagstatus_R &= mask;
out:
	spin_unlock(&ctx->csa.रेजिस्टर_lock);

	वापस ret;
पूर्ण

अटल u32 spu_backing_पढ़ो_mfc_tagstatus(काष्ठा spu_context * ctx)
अणु
	वापस ctx->csa.prob.dma_tagstatus_R;
पूर्ण

अटल u32 spu_backing_get_mfc_मुक्त_elements(काष्ठा spu_context *ctx)
अणु
	वापस ctx->csa.prob.dma_qstatus_R;
पूर्ण

अटल पूर्णांक spu_backing_send_mfc_command(काष्ठा spu_context *ctx,
					काष्ठा mfc_dma_command *cmd)
अणु
	पूर्णांक ret;

	spin_lock(&ctx->csa.रेजिस्टर_lock);
	ret = -EAGAIN;
	/* FIXME: set up priv2->puq */
	spin_unlock(&ctx->csa.रेजिस्टर_lock);

	वापस ret;
पूर्ण

अटल व्योम spu_backing_restart_dma(काष्ठा spu_context *ctx)
अणु
	ctx->csa.priv2.mfc_control_RW |= MFC_CNTL_RESTART_DMA_COMMAND;
पूर्ण

काष्ठा spu_context_ops spu_backing_ops = अणु
	.mbox_पढ़ो = spu_backing_mbox_पढ़ो,
	.mbox_stat_पढ़ो = spu_backing_mbox_stat_पढ़ो,
	.mbox_stat_poll = spu_backing_mbox_stat_poll,
	.ibox_पढ़ो = spu_backing_ibox_पढ़ो,
	.wbox_ग_लिखो = spu_backing_wbox_ग_लिखो,
	.संकेत1_पढ़ो = spu_backing_संकेत1_पढ़ो,
	.संकेत1_ग_लिखो = spu_backing_संकेत1_ग_लिखो,
	.संकेत2_पढ़ो = spu_backing_संकेत2_पढ़ो,
	.संकेत2_ग_लिखो = spu_backing_संकेत2_ग_लिखो,
	.संकेत1_type_set = spu_backing_संकेत1_type_set,
	.संकेत1_type_get = spu_backing_संकेत1_type_get,
	.संकेत2_type_set = spu_backing_संकेत2_type_set,
	.संकेत2_type_get = spu_backing_संकेत2_type_get,
	.npc_पढ़ो = spu_backing_npc_पढ़ो,
	.npc_ग_लिखो = spu_backing_npc_ग_लिखो,
	.status_पढ़ो = spu_backing_status_पढ़ो,
	.get_ls = spu_backing_get_ls,
	.privcntl_ग_लिखो = spu_backing_privcntl_ग_लिखो,
	.runcntl_पढ़ो = spu_backing_runcntl_पढ़ो,
	.runcntl_ग_लिखो = spu_backing_runcntl_ग_लिखो,
	.runcntl_stop = spu_backing_runcntl_stop,
	.master_start = spu_backing_master_start,
	.master_stop = spu_backing_master_stop,
	.set_mfc_query = spu_backing_set_mfc_query,
	.पढ़ो_mfc_tagstatus = spu_backing_पढ़ो_mfc_tagstatus,
	.get_mfc_मुक्त_elements = spu_backing_get_mfc_मुक्त_elements,
	.send_mfc_command = spu_backing_send_mfc_command,
	.restart_dma = spu_backing_restart_dma,
पूर्ण;
