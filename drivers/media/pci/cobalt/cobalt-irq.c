<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cobalt पूर्णांकerrupt handling
 *
 *  Copyright 2012-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#समावेश <media/i2c/adv7604.h>

#समावेश "cobalt-driver.h"
#समावेश "cobalt-irq.h"
#समावेश "cobalt-omnitek.h"

अटल व्योम cobalt_dma_stream_queue_handler(काष्ठा cobalt_stream *s)
अणु
	काष्ठा cobalt *cobalt = s->cobalt;
	पूर्णांक rx = s->video_channel;
	काष्ठा m00473_मुक्तwheel_regmap __iomem *fw =
		COBALT_CVI_FREEWHEEL(s->cobalt, rx);
	काष्ठा m00233_video_measure_regmap __iomem *vmr =
		COBALT_CVI_VMR(s->cobalt, rx);
	काष्ठा m00389_cvi_regmap __iomem *cvi =
		COBALT_CVI(s->cobalt, rx);
	काष्ठा m00479_clk_loss_detector_regmap __iomem *clkloss =
		COBALT_CVI_CLK_LOSS(s->cobalt, rx);
	काष्ठा cobalt_buffer *cb;
	bool skip = false;

	spin_lock(&s->irqlock);

	अगर (list_empty(&s->bufs)) अणु
		pr_err("no buffers!\n");
		spin_unlock(&s->irqlock);
		वापस;
	पूर्ण

	/* Give the fresh filled up buffer to the user.
	 * Note that the पूर्णांकerrupt is only sent अगर the DMA can जारी
	 * with a new buffer, so it is always safe to वापस this buffer
	 * to userspace. */
	cb = list_first_entry(&s->bufs, काष्ठा cobalt_buffer, list);
	list_del(&cb->list);
	spin_unlock(&s->irqlock);

	अगर (s->is_audio || s->is_output)
		जाओ करोne;

	अगर (s->unstable_frame) अणु
		uपूर्णांक32_t stat = ioपढ़ो32(&vmr->irq_status);

		ioग_लिखो32(stat, &vmr->irq_status);
		अगर (!(ioपढ़ो32(&vmr->status) &
		      M00233_STATUS_BITMAP_INIT_DONE_MSK)) अणु
			cobalt_dbg(1, "!init_done\n");
			अगर (s->enable_मुक्तwheel)
				जाओ restart_fw;
			जाओ करोne;
		पूर्ण

		अगर (ioपढ़ो32(&clkloss->status) &
		    M00479_STATUS_BITMAP_CLOCK_MISSING_MSK) अणु
			ioग_लिखो32(0, &clkloss->ctrl);
			ioग_लिखो32(M00479_CTRL_BITMAP_ENABLE_MSK, &clkloss->ctrl);
			cobalt_dbg(1, "no clock\n");
			अगर (s->enable_मुक्तwheel)
				जाओ restart_fw;
			जाओ करोne;
		पूर्ण
		अगर ((stat & (M00233_IRQ_STATUS_BITMAP_VACTIVE_AREA_MSK |
			     M00233_IRQ_STATUS_BITMAP_HACTIVE_AREA_MSK)) ||
				ioपढ़ो32(&vmr->vactive_area) != s->timings.bt.height ||
				ioपढ़ो32(&vmr->hactive_area) != s->timings.bt.width) अणु
			cobalt_dbg(1, "unstable\n");
			अगर (s->enable_मुक्तwheel)
				जाओ restart_fw;
			जाओ करोne;
		पूर्ण
		अगर (!s->enable_cvi) अणु
			s->enable_cvi = true;
			ioग_लिखो32(M00389_CONTROL_BITMAP_ENABLE_MSK, &cvi->control);
			जाओ करोne;
		पूर्ण
		अगर (!(ioपढ़ो32(&cvi->status) & M00389_STATUS_BITMAP_LOCK_MSK)) अणु
			cobalt_dbg(1, "cvi no lock\n");
			अगर (s->enable_मुक्तwheel)
				जाओ restart_fw;
			जाओ करोne;
		पूर्ण
		अगर (!s->enable_मुक्तwheel) अणु
			cobalt_dbg(1, "stable\n");
			s->enable_मुक्तwheel = true;
			ioग_लिखो32(0, &fw->ctrl);
			जाओ करोne;
		पूर्ण
		cobalt_dbg(1, "enabled fw\n");
		ioग_लिखो32(M00233_CONTROL_BITMAP_ENABLE_MEASURE_MSK |
			  M00233_CONTROL_BITMAP_ENABLE_INTERRUPT_MSK,
			  &vmr->control);
		ioग_लिखो32(M00473_CTRL_BITMAP_ENABLE_MSK, &fw->ctrl);
		s->enable_मुक्तwheel = false;
		s->unstable_frame = false;
		s->skip_first_frames = 2;
		skip = true;
		जाओ करोne;
	पूर्ण
	अगर (ioपढ़ो32(&fw->status) & M00473_STATUS_BITMAP_FREEWHEEL_MODE_MSK) अणु
restart_fw:
		cobalt_dbg(1, "lost lock\n");
		ioग_लिखो32(M00233_CONTROL_BITMAP_ENABLE_MEASURE_MSK,
			  &vmr->control);
		ioग_लिखो32(M00473_CTRL_BITMAP_ENABLE_MSK |
			  M00473_CTRL_BITMAP_FORCE_FREEWHEEL_MODE_MSK,
			  &fw->ctrl);
		ioग_लिखो32(0, &cvi->control);
		s->unstable_frame = true;
		s->enable_मुक्तwheel = false;
		s->enable_cvi = false;
	पूर्ण
करोne:
	अगर (s->skip_first_frames) अणु
		skip = true;
		s->skip_first_frames--;
	पूर्ण
	cb->vb.vb2_buf.बारtamp = kसमय_get_ns();
	/* TODO: the sequence number should be पढ़ो from the FPGA so we
	   also know about dropped frames. */
	cb->vb.sequence = s->sequence++;
	vb2_buffer_करोne(&cb->vb.vb2_buf,
			(skip || s->unstable_frame) ?
			VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
पूर्ण

irqवापस_t cobalt_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cobalt *cobalt = (काष्ठा cobalt *)dev_id;
	u32 dma_पूर्णांकerrupt =
		cobalt_पढ़ो_bar0(cobalt, DMA_INTERRUPT_STATUS_REG) & 0xffff;
	u32 mask = cobalt_पढ़ो_bar1(cobalt, COBALT_SYS_STAT_MASK);
	u32 edge = cobalt_पढ़ो_bar1(cobalt, COBALT_SYS_STAT_EDGE);
	पूर्णांक i;

	/* Clear DMA पूर्णांकerrupt */
	cobalt_ग_लिखो_bar0(cobalt, DMA_INTERRUPT_STATUS_REG, dma_पूर्णांकerrupt);
	cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_STAT_MASK, mask & ~edge);
	cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_STAT_EDGE, edge);

	क्रम (i = 0; i < COBALT_NUM_STREAMS; i++) अणु
		काष्ठा cobalt_stream *s = &cobalt->streams[i];
		अचिन्हित dma_fअगरo_mask = s->dma_fअगरo_mask;

		अगर (dma_पूर्णांकerrupt & (1 << s->dma_channel)) अणु
			cobalt->irq_dma[i]++;
			/* Give fresh buffer to user and chain newly
			 * queued buffers */
			cobalt_dma_stream_queue_handler(s);
			अगर (!s->is_audio) अणु
				edge &= ~dma_fअगरo_mask;
				cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_STAT_MASK,
						  mask & ~edge);
			पूर्ण
		पूर्ण
		अगर (s->is_audio)
			जारी;
		अगर (edge & s->adv_irq_mask)
			set_bit(COBALT_STREAM_FL_ADV_IRQ, &s->flags);
		अगर ((edge & mask & dma_fअगरo_mask) && vb2_is_streaming(&s->q)) अणु
			cobalt_info("full rx FIFO %d\n", i);
			cobalt->irq_full_fअगरo++;
		पूर्ण
	पूर्ण

	queue_work(cobalt->irq_work_queues, &cobalt->irq_work_queue);

	अगर (edge & mask & (COBALT_SYSSTAT_VI0_INT1_MSK |
			   COBALT_SYSSTAT_VI1_INT1_MSK |
			   COBALT_SYSSTAT_VI2_INT1_MSK |
			   COBALT_SYSSTAT_VI3_INT1_MSK |
			   COBALT_SYSSTAT_VIHSMA_INT1_MSK |
			   COBALT_SYSSTAT_VOHSMA_INT1_MSK))
		cobalt->irq_adv1++;
	अगर (edge & mask & (COBALT_SYSSTAT_VI0_INT2_MSK |
			   COBALT_SYSSTAT_VI1_INT2_MSK |
			   COBALT_SYSSTAT_VI2_INT2_MSK |
			   COBALT_SYSSTAT_VI3_INT2_MSK |
			   COBALT_SYSSTAT_VIHSMA_INT2_MSK))
		cobalt->irq_adv2++;
	अगर (edge & mask & COBALT_SYSSTAT_VOHSMA_INT1_MSK)
		cobalt->irq_advout++;
	अगर (dma_पूर्णांकerrupt)
		cobalt->irq_dma_tot++;
	अगर (!(edge & mask) && !dma_पूर्णांकerrupt)
		cobalt->irq_none++;
	dma_पूर्णांकerrupt = cobalt_पढ़ो_bar0(cobalt, DMA_INTERRUPT_STATUS_REG);

	वापस IRQ_HANDLED;
पूर्ण

व्योम cobalt_irq_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cobalt *cobalt =
		container_of(work, काष्ठा cobalt, irq_work_queue);
	पूर्णांक i;

	क्रम (i = 0; i < COBALT_NUM_NODES; i++) अणु
		काष्ठा cobalt_stream *s = &cobalt->streams[i];

		अगर (test_and_clear_bit(COBALT_STREAM_FL_ADV_IRQ, &s->flags)) अणु
			u32 mask;

			v4l2_subdev_call(cobalt->streams[i].sd, core,
					पूर्णांकerrupt_service_routine, 0, शून्य);
			mask = cobalt_पढ़ो_bar1(cobalt, COBALT_SYS_STAT_MASK);
			cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_STAT_MASK,
				mask | s->adv_irq_mask);
		पूर्ण
	पूर्ण
पूर्ण

व्योम cobalt_irq_log_status(काष्ठा cobalt *cobalt)
अणु
	u32 mask;
	पूर्णांक i;

	cobalt_info("irq: adv1=%u adv2=%u advout=%u none=%u full=%u\n",
		    cobalt->irq_adv1, cobalt->irq_adv2, cobalt->irq_advout,
		    cobalt->irq_none, cobalt->irq_full_fअगरo);
	cobalt_info("irq: dma_tot=%u (", cobalt->irq_dma_tot);
	क्रम (i = 0; i < COBALT_NUM_STREAMS; i++)
		pr_cont("%s%u", i ? "/" : "", cobalt->irq_dma[i]);
	pr_cont(")\n");
	cobalt->irq_dma_tot = cobalt->irq_adv1 = cobalt->irq_adv2 = 0;
	cobalt->irq_advout = cobalt->irq_none = cobalt->irq_full_fअगरo = 0;
	स_रखो(cobalt->irq_dma, 0, माप(cobalt->irq_dma));

	mask = cobalt_पढ़ो_bar1(cobalt, COBALT_SYS_STAT_MASK);
	cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_STAT_MASK,
			mask |
			COBALT_SYSSTAT_VI0_LOST_DATA_MSK |
			COBALT_SYSSTAT_VI1_LOST_DATA_MSK |
			COBALT_SYSSTAT_VI2_LOST_DATA_MSK |
			COBALT_SYSSTAT_VI3_LOST_DATA_MSK |
			COBALT_SYSSTAT_VIHSMA_LOST_DATA_MSK |
			COBALT_SYSSTAT_VOHSMA_LOST_DATA_MSK |
			COBALT_SYSSTAT_AUD_IN_LOST_DATA_MSK |
			COBALT_SYSSTAT_AUD_OUT_LOST_DATA_MSK);
पूर्ण
