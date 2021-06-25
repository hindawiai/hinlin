<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x Channel
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#समावेश <linux/host1x.h>
#समावेश <linux/iommu.h>
#समावेश <linux/slab.h>

#समावेश <trace/events/host1x.h>

#समावेश "../channel.h"
#समावेश "../dev.h"
#समावेश "../intr.h"
#समावेश "../job.h"

#घोषणा TRACE_MAX_LENGTH 128U

अटल व्योम trace_ग_लिखो_gather(काष्ठा host1x_cdma *cdma, काष्ठा host1x_bo *bo,
			       u32 offset, u32 words)
अणु
	काष्ठा device *dev = cdma_to_channel(cdma)->dev;
	व्योम *mem = शून्य;

	अगर (host1x_debug_trace_cmdbuf)
		mem = host1x_bo_mmap(bo);

	अगर (mem) अणु
		u32 i;
		/*
		 * Write in batches of 128 as there seems to be a limit
		 * of how much you can output to ftrace at once.
		 */
		क्रम (i = 0; i < words; i += TRACE_MAX_LENGTH) अणु
			u32 num_words = min(words - i, TRACE_MAX_LENGTH);

			offset += i * माप(u32);

			trace_host1x_cdma_push_gather(dev_name(dev), bo,
						      num_words, offset,
						      mem);
		पूर्ण

		host1x_bo_munmap(bo, mem);
	पूर्ण
पूर्ण

अटल व्योम submit_gathers(काष्ठा host1x_job *job)
अणु
	काष्ठा host1x_cdma *cdma = &job->channel->cdma;
#अगर HOST1X_HW < 6
	काष्ठा device *dev = job->channel->dev;
#पूर्ण_अगर
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < job->num_gathers; i++) अणु
		काष्ठा host1x_job_gather *g = &job->gathers[i];
		dma_addr_t addr = g->base + g->offset;
		u32 op2, op3;

		op2 = lower_32_bits(addr);
		op3 = upper_32_bits(addr);

		trace_ग_लिखो_gather(cdma, g->bo, g->offset, g->words);

		अगर (op3 != 0) अणु
#अगर HOST1X_HW >= 6
			u32 op1 = host1x_opcode_gather_wide(g->words);
			u32 op4 = HOST1X_OPCODE_NOP;

			host1x_cdma_push_wide(cdma, op1, op2, op3, op4);
#अन्यथा
			dev_err(dev, "invalid gather for push buffer %pad\n",
				&addr);
			जारी;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			u32 op1 = host1x_opcode_gather(g->words);

			host1x_cdma_push(cdma, op1, op2);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम synchronize_syncpt_base(काष्ठा host1x_job *job)
अणु
	काष्ठा host1x_syncpt *sp = job->syncpt;
	अचिन्हित पूर्णांक id;
	u32 value;

	value = host1x_syncpt_पढ़ो_max(sp);
	id = sp->base->id;

	host1x_cdma_push(&job->channel->cdma,
			 host1x_opcode_setclass(HOST1X_CLASS_HOST1X,
				HOST1X_UCLASS_LOAD_SYNCPT_BASE, 1),
			 HOST1X_UCLASS_LOAD_SYNCPT_BASE_BASE_INDX_F(id) |
			 HOST1X_UCLASS_LOAD_SYNCPT_BASE_VALUE_F(value));
पूर्ण

अटल व्योम host1x_channel_set_streamid(काष्ठा host1x_channel *channel)
अणु
#अगर HOST1X_HW >= 6
	u32 sid = 0x7f;
#अगर_घोषित CONFIG_IOMMU_API
	काष्ठा iommu_fwspec *spec = dev_iommu_fwspec_get(channel->dev->parent);
	अगर (spec)
		sid = spec->ids[0] & 0xffff;
#पूर्ण_अगर

	host1x_ch_ग_लिखोl(channel, sid, HOST1X_CHANNEL_SMMU_STREAMID);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक channel_submit(काष्ठा host1x_job *job)
अणु
	काष्ठा host1x_channel *ch = job->channel;
	काष्ठा host1x_syncpt *sp = job->syncpt;
	u32 user_syncpt_incrs = job->syncpt_incrs;
	u32 prev_max = 0;
	u32 syncval;
	पूर्णांक err;
	काष्ठा host1x_रुकोlist *completed_रुकोer = शून्य;
	काष्ठा host1x *host = dev_get_drvdata(ch->dev->parent);

	trace_host1x_channel_submit(dev_name(ch->dev),
				    job->num_gathers, job->num_relocs,
				    job->syncpt->id, job->syncpt_incrs);

	/* beक्रमe error checks, वापस current max */
	prev_max = job->syncpt_end = host1x_syncpt_पढ़ो_max(sp);

	/* get submit lock */
	err = mutex_lock_पूर्णांकerruptible(&ch->submitlock);
	अगर (err)
		जाओ error;

	completed_रुकोer = kzalloc(माप(*completed_रुकोer), GFP_KERNEL);
	अगर (!completed_रुकोer) अणु
		mutex_unlock(&ch->submitlock);
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	host1x_channel_set_streamid(ch);

	/* begin a CDMA submit */
	err = host1x_cdma_begin(&ch->cdma, job);
	अगर (err) अणु
		mutex_unlock(&ch->submitlock);
		जाओ error;
	पूर्ण

	अगर (job->serialize) अणु
		/*
		 * Force serialization by inserting a host रुको क्रम the
		 * previous job to finish beक्रमe this one can commence.
		 */
		host1x_cdma_push(&ch->cdma,
				 host1x_opcode_setclass(HOST1X_CLASS_HOST1X,
					host1x_uclass_रुको_syncpt_r(), 1),
				 host1x_class_host_रुको_syncpt(job->syncpt->id,
					host1x_syncpt_पढ़ो_max(sp)));
	पूर्ण

	/* Synchronize base रेजिस्टर to allow using it क्रम relative रुकोing */
	अगर (sp->base)
		synchronize_syncpt_base(job);

	syncval = host1x_syncpt_incr_max(sp, user_syncpt_incrs);

	host1x_hw_syncpt_assign_to_channel(host, sp, ch);

	job->syncpt_end = syncval;

	/* add a setclass क्रम modules that require it */
	अगर (job->class)
		host1x_cdma_push(&ch->cdma,
				 host1x_opcode_setclass(job->class, 0, 0),
				 HOST1X_OPCODE_NOP);

	submit_gathers(job);

	/* end CDMA submit & stash pinned hMems पूर्णांकo sync queue */
	host1x_cdma_end(&ch->cdma, job);

	trace_host1x_channel_submitted(dev_name(ch->dev), prev_max, syncval);

	/* schedule a submit complete पूर्णांकerrupt */
	err = host1x_पूर्णांकr_add_action(host, sp, syncval,
				     HOST1X_INTR_ACTION_SUBMIT_COMPLETE, ch,
				     completed_रुकोer, शून्य);
	completed_रुकोer = शून्य;
	WARN(err, "Failed to set submit complete interrupt");

	mutex_unlock(&ch->submitlock);

	वापस 0;

error:
	kमुक्त(completed_रुकोer);
	वापस err;
पूर्ण

अटल व्योम enable_gather_filter(काष्ठा host1x *host,
				 काष्ठा host1x_channel *ch)
अणु
#अगर HOST1X_HW >= 6
	u32 val;

	अगर (!host->hv_regs)
		वापस;

	val = host1x_hypervisor_पढ़ोl(
		host, HOST1X_HV_CH_KERNEL_FILTER_GBUFFER(ch->id / 32));
	val |= BIT(ch->id % 32);
	host1x_hypervisor_ग_लिखोl(
		host, val, HOST1X_HV_CH_KERNEL_FILTER_GBUFFER(ch->id / 32));
#या_अगर HOST1X_HW >= 4
	host1x_ch_ग_लिखोl(ch,
			 HOST1X_CHANNEL_CHANNELCTRL_KERNEL_FILTER_GBUFFER(1),
			 HOST1X_CHANNEL_CHANNELCTRL);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक host1x_channel_init(काष्ठा host1x_channel *ch, काष्ठा host1x *dev,
			       अचिन्हित पूर्णांक index)
अणु
#अगर HOST1X_HW < 6
	ch->regs = dev->regs + index * 0x4000;
#अन्यथा
	ch->regs = dev->regs + index * 0x100;
#पूर्ण_अगर
	enable_gather_filter(dev, ch);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा host1x_channel_ops host1x_channel_ops = अणु
	.init = host1x_channel_init,
	.submit = channel_submit,
पूर्ण;
