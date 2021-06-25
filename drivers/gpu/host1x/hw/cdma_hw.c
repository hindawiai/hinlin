<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x Command DMA
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>

#समावेश "../cdma.h"
#समावेश "../channel.h"
#समावेश "../dev.h"
#समावेश "../debug.h"

/*
 * Put the restart at the end of pushbuffer memory
 */
अटल व्योम push_buffer_init(काष्ठा push_buffer *pb)
अणु
	*(u32 *)(pb->mapped + pb->size) = host1x_opcode_restart(0);
पूर्ण

/*
 * Increment समयकरोut buffer's syncpt via CPU.
 */
अटल व्योम cdma_समयout_cpu_incr(काष्ठा host1x_cdma *cdma, u32 getptr,
				u32 syncpt_incrs, u32 syncval, u32 nr_slots)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < syncpt_incrs; i++)
		host1x_syncpt_incr(cdma->समयout.syncpt);

	/* after CPU incr, ensure shaकरोw is up to date */
	host1x_syncpt_load(cdma->समयout.syncpt);
पूर्ण

/*
 * Start channel DMA
 */
अटल व्योम cdma_start(काष्ठा host1x_cdma *cdma)
अणु
	काष्ठा host1x_channel *ch = cdma_to_channel(cdma);
	u64 start, end;

	अगर (cdma->running)
		वापस;

	cdma->last_pos = cdma->push_buffer.pos;
	start = cdma->push_buffer.dma;
	end = cdma->push_buffer.size + 4;

	host1x_ch_ग_लिखोl(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP,
			 HOST1X_CHANNEL_DMACTRL);

	/* set base, put and end poपूर्णांकer */
	host1x_ch_ग_लिखोl(ch, lower_32_bits(start), HOST1X_CHANNEL_DMASTART);
#अगर HOST1X_HW >= 6
	host1x_ch_ग_लिखोl(ch, upper_32_bits(start), HOST1X_CHANNEL_DMASTART_HI);
#पूर्ण_अगर
	host1x_ch_ग_लिखोl(ch, cdma->push_buffer.pos, HOST1X_CHANNEL_DMAPUT);
#अगर HOST1X_HW >= 6
	host1x_ch_ग_लिखोl(ch, 0, HOST1X_CHANNEL_DMAPUT_HI);
#पूर्ण_अगर
	host1x_ch_ग_लिखोl(ch, lower_32_bits(end), HOST1X_CHANNEL_DMAEND);
#अगर HOST1X_HW >= 6
	host1x_ch_ग_लिखोl(ch, upper_32_bits(end), HOST1X_CHANNEL_DMAEND_HI);
#पूर्ण_अगर

	/* reset GET */
	host1x_ch_ग_लिखोl(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP |
			 HOST1X_CHANNEL_DMACTRL_DMAGETRST |
			 HOST1X_CHANNEL_DMACTRL_DMAINITGET,
			 HOST1X_CHANNEL_DMACTRL);

	/* start the command DMA */
	host1x_ch_ग_लिखोl(ch, 0, HOST1X_CHANNEL_DMACTRL);

	cdma->running = true;
पूर्ण

/*
 * Similar to cdma_start(), but rather than starting from an idle
 * state (where DMA GET is set to DMA PUT), on a समयout we restore
 * DMA GET from an explicit value (so DMA may again be pending).
 */
अटल व्योम cdma_समयout_restart(काष्ठा host1x_cdma *cdma, u32 getptr)
अणु
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);
	काष्ठा host1x_channel *ch = cdma_to_channel(cdma);
	u64 start, end;

	अगर (cdma->running)
		वापस;

	cdma->last_pos = cdma->push_buffer.pos;

	host1x_ch_ग_लिखोl(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP,
			 HOST1X_CHANNEL_DMACTRL);

	start = cdma->push_buffer.dma;
	end = cdma->push_buffer.size + 4;

	/* set base, end poपूर्णांकer (all of memory) */
	host1x_ch_ग_लिखोl(ch, lower_32_bits(start), HOST1X_CHANNEL_DMASTART);
#अगर HOST1X_HW >= 6
	host1x_ch_ग_लिखोl(ch, upper_32_bits(start), HOST1X_CHANNEL_DMASTART_HI);
#पूर्ण_अगर
	host1x_ch_ग_लिखोl(ch, lower_32_bits(end), HOST1X_CHANNEL_DMAEND);
#अगर HOST1X_HW >= 6
	host1x_ch_ग_लिखोl(ch, upper_32_bits(end), HOST1X_CHANNEL_DMAEND_HI);
#पूर्ण_अगर

	/* set GET, by loading the value in PUT (then reset GET) */
	host1x_ch_ग_लिखोl(ch, getptr, HOST1X_CHANNEL_DMAPUT);
	host1x_ch_ग_लिखोl(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP |
			 HOST1X_CHANNEL_DMACTRL_DMAGETRST |
			 HOST1X_CHANNEL_DMACTRL_DMAINITGET,
			 HOST1X_CHANNEL_DMACTRL);

	dev_dbg(host1x->dev,
		"%s: DMA GET 0x%x, PUT HW 0x%x / shadow 0x%x\n", __func__,
		host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMAGET),
		host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMAPUT),
		cdma->last_pos);

	/* deनिश्चित GET reset and set PUT */
	host1x_ch_ग_लिखोl(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP,
			 HOST1X_CHANNEL_DMACTRL);
	host1x_ch_ग_लिखोl(ch, cdma->push_buffer.pos, HOST1X_CHANNEL_DMAPUT);

	/* start the command DMA */
	host1x_ch_ग_लिखोl(ch, 0, HOST1X_CHANNEL_DMACTRL);

	cdma->running = true;
पूर्ण

/*
 * Kick channel DMA पूर्णांकo action by writing its PUT offset (अगर it has changed)
 */
अटल व्योम cdma_flush(काष्ठा host1x_cdma *cdma)
अणु
	काष्ठा host1x_channel *ch = cdma_to_channel(cdma);

	अगर (cdma->push_buffer.pos != cdma->last_pos) अणु
		host1x_ch_ग_लिखोl(ch, cdma->push_buffer.pos,
				 HOST1X_CHANNEL_DMAPUT);
		cdma->last_pos = cdma->push_buffer.pos;
	पूर्ण
पूर्ण

अटल व्योम cdma_stop(काष्ठा host1x_cdma *cdma)
अणु
	काष्ठा host1x_channel *ch = cdma_to_channel(cdma);

	mutex_lock(&cdma->lock);

	अगर (cdma->running) अणु
		host1x_cdma_रुको_locked(cdma, CDMA_EVENT_SYNC_QUEUE_EMPTY);
		host1x_ch_ग_लिखोl(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP,
				 HOST1X_CHANNEL_DMACTRL);
		cdma->running = false;
	पूर्ण

	mutex_unlock(&cdma->lock);
पूर्ण

अटल व्योम cdma_hw_cmdproc_stop(काष्ठा host1x *host, काष्ठा host1x_channel *ch,
				 bool stop)
अणु
#अगर HOST1X_HW >= 6
	host1x_ch_ग_लिखोl(ch, stop ? 0x1 : 0x0, HOST1X_CHANNEL_CMDPROC_STOP);
#अन्यथा
	u32 cmdproc_stop = host1x_sync_पढ़ोl(host, HOST1X_SYNC_CMDPROC_STOP);
	अगर (stop)
		cmdproc_stop |= BIT(ch->id);
	अन्यथा
		cmdproc_stop &= ~BIT(ch->id);
	host1x_sync_ग_लिखोl(host, cmdproc_stop, HOST1X_SYNC_CMDPROC_STOP);
#पूर्ण_अगर
पूर्ण

अटल व्योम cdma_hw_tearकरोwn(काष्ठा host1x *host, काष्ठा host1x_channel *ch)
अणु
#अगर HOST1X_HW >= 6
	host1x_ch_ग_लिखोl(ch, 0x1, HOST1X_CHANNEL_TEARDOWN);
#अन्यथा
	host1x_sync_ग_लिखोl(host, BIT(ch->id), HOST1X_SYNC_CH_TEARDOWN);
#पूर्ण_अगर
पूर्ण

/*
 * Stops both channel's command processor and CDMA immediately.
 * Also, tears करोwn the channel and resets corresponding module.
 */
अटल व्योम cdma_मुक्तze(काष्ठा host1x_cdma *cdma)
अणु
	काष्ठा host1x *host = cdma_to_host1x(cdma);
	काष्ठा host1x_channel *ch = cdma_to_channel(cdma);

	अगर (cdma->tornकरोwn && !cdma->running) अणु
		dev_warn(host->dev, "Already torn down\n");
		वापस;
	पूर्ण

	dev_dbg(host->dev, "freezing channel (id %d)\n", ch->id);

	cdma_hw_cmdproc_stop(host, ch, true);

	dev_dbg(host->dev, "%s: DMA GET 0x%x, PUT HW 0x%x / shadow 0x%x\n",
		__func__, host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMAGET),
		host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMAPUT),
		cdma->last_pos);

	host1x_ch_ग_लिखोl(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP,
			 HOST1X_CHANNEL_DMACTRL);

	cdma_hw_tearकरोwn(host, ch);

	cdma->running = false;
	cdma->tornकरोwn = true;
पूर्ण

अटल व्योम cdma_resume(काष्ठा host1x_cdma *cdma, u32 getptr)
अणु
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);
	काष्ठा host1x_channel *ch = cdma_to_channel(cdma);

	dev_dbg(host1x->dev,
		"resuming channel (id %u, DMAGET restart = 0x%x)\n",
		ch->id, getptr);

	cdma_hw_cmdproc_stop(host1x, ch, false);

	cdma->tornकरोwn = false;
	cdma_समयout_restart(cdma, getptr);
पूर्ण

/*
 * If this समयout fires, it indicates the current sync_queue entry has
 * exceeded its TTL and the userctx should be समयd out and reमुख्यing
 * submits alपढ़ोy issued cleaned up (future submits वापस an error).
 */
अटल व्योम cdma_समयout_handler(काष्ठा work_काष्ठा *work)
अणु
	u32 syncpt_val;
	काष्ठा host1x_cdma *cdma;
	काष्ठा host1x *host1x;
	काष्ठा host1x_channel *ch;

	cdma = container_of(to_delayed_work(work), काष्ठा host1x_cdma,
			    समयout.wq);
	host1x = cdma_to_host1x(cdma);
	ch = cdma_to_channel(cdma);

	host1x_debug_dump(cdma_to_host1x(cdma));

	mutex_lock(&cdma->lock);

	अगर (!cdma->समयout.client) अणु
		dev_dbg(host1x->dev,
			"cdma_timeout: expired, but has no clientid\n");
		mutex_unlock(&cdma->lock);
		वापस;
	पूर्ण

	/* stop processing to get a clean snapshot */
	cdma_hw_cmdproc_stop(host1x, ch, true);

	syncpt_val = host1x_syncpt_load(cdma->समयout.syncpt);

	/* has buffer actually completed? */
	अगर ((s32)(syncpt_val - cdma->समयout.syncpt_val) >= 0) अणु
		dev_dbg(host1x->dev,
			"cdma_timeout: expired, but buffer had completed\n");
		/* restore */
		cdma_hw_cmdproc_stop(host1x, ch, false);
		mutex_unlock(&cdma->lock);
		वापस;
	पूर्ण

	dev_warn(host1x->dev, "%s: timeout: %u (%s), HW thresh %d, done %d\n",
		 __func__, cdma->समयout.syncpt->id, cdma->समयout.syncpt->name,
		 syncpt_val, cdma->समयout.syncpt_val);

	/* stop HW, resetting channel/module */
	host1x_hw_cdma_मुक्तze(host1x, cdma);

	host1x_cdma_update_sync_queue(cdma, ch->dev);
	mutex_unlock(&cdma->lock);
पूर्ण

/*
 * Init समयout resources
 */
अटल पूर्णांक cdma_समयout_init(काष्ठा host1x_cdma *cdma)
अणु
	INIT_DELAYED_WORK(&cdma->समयout.wq, cdma_समयout_handler);
	cdma->समयout.initialized = true;

	वापस 0;
पूर्ण

/*
 * Clean up समयout resources
 */
अटल व्योम cdma_समयout_destroy(काष्ठा host1x_cdma *cdma)
अणु
	अगर (cdma->समयout.initialized)
		cancel_delayed_work(&cdma->समयout.wq);

	cdma->समयout.initialized = false;
पूर्ण

अटल स्थिर काष्ठा host1x_cdma_ops host1x_cdma_ops = अणु
	.start = cdma_start,
	.stop = cdma_stop,
	.flush = cdma_flush,

	.समयout_init = cdma_समयout_init,
	.समयout_destroy = cdma_समयout_destroy,
	.मुक्तze = cdma_मुक्तze,
	.resume = cdma_resume,
	.समयout_cpu_incr = cdma_समयout_cpu_incr,
पूर्ण;

अटल स्थिर काष्ठा host1x_pushbuffer_ops host1x_pushbuffer_ops = अणु
	.init = push_buffer_init,
पूर्ण;
