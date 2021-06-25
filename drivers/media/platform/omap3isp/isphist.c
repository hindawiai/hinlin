<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isphist.c
 *
 * TI OMAP3 ISP - Histogram module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: David Cohen <dacohen@gmail.com>
 *	     Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "isp.h"
#समावेश "ispreg.h"
#समावेश "isphist.h"

#घोषणा HIST_CONFIG_DMA	1

/*
 * hist_reset_mem - clear Histogram memory beक्रमe start stats engine.
 */
अटल व्योम hist_reset_mem(काष्ठा ispstat *hist)
अणु
	काष्ठा isp_device *isp = hist->isp;
	काष्ठा omap3isp_hist_config *conf = hist->priv;
	अचिन्हित पूर्णांक i;

	isp_reg_ग_लिखोl(isp, 0, OMAP3_ISP_IOMEM_HIST, ISPHIST_ADDR);

	/*
	 * By setting it, the histogram पूर्णांकernal buffer is being cleared at the
	 * same समय it's being पढ़ो. This bit must be cleared afterwards.
	 */
	isp_reg_set(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT, ISPHIST_CNT_CLEAR);

	/*
	 * We'll clear 4 words at each iteration क्रम optimization. It aव्योमs
	 * 3/4 of the jumps. We also know HIST_MEM_SIZE is भागisible by 4.
	 */
	क्रम (i = OMAP3ISP_HIST_MEM_SIZE / 4; i > 0; i--) अणु
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
	पूर्ण
	isp_reg_clr(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT, ISPHIST_CNT_CLEAR);

	hist->रुको_acc_frames = conf->num_acc_frames;
पूर्ण

/*
 * hist_setup_regs - Helper function to update Histogram रेजिस्टरs.
 */
अटल व्योम hist_setup_regs(काष्ठा ispstat *hist, व्योम *priv)
अणु
	काष्ठा isp_device *isp = hist->isp;
	काष्ठा omap3isp_hist_config *conf = priv;
	पूर्णांक c;
	u32 cnt;
	u32 wb_gain;
	u32 reg_hor[OMAP3ISP_HIST_MAX_REGIONS];
	u32 reg_ver[OMAP3ISP_HIST_MAX_REGIONS];

	अगर (!hist->update || hist->state == ISPSTAT_DISABLED ||
	    hist->state == ISPSTAT_DISABLING)
		वापस;

	cnt = conf->cfa << ISPHIST_CNT_CFA_SHIFT;

	wb_gain = conf->wg[0] << ISPHIST_WB_GAIN_WG00_SHIFT;
	wb_gain |= conf->wg[1] << ISPHIST_WB_GAIN_WG01_SHIFT;
	wb_gain |= conf->wg[2] << ISPHIST_WB_GAIN_WG02_SHIFT;
	अगर (conf->cfa == OMAP3ISP_HIST_CFA_BAYER)
		wb_gain |= conf->wg[3] << ISPHIST_WB_GAIN_WG03_SHIFT;

	/* Regions size and position */
	क्रम (c = 0; c < OMAP3ISP_HIST_MAX_REGIONS; c++) अणु
		अगर (c < conf->num_regions) अणु
			reg_hor[c] = (conf->region[c].h_start <<
				     ISPHIST_REG_START_SHIFT)
				   | (conf->region[c].h_end <<
				     ISPHIST_REG_END_SHIFT);
			reg_ver[c] = (conf->region[c].v_start <<
				     ISPHIST_REG_START_SHIFT)
				   | (conf->region[c].v_end <<
				     ISPHIST_REG_END_SHIFT);
		पूर्ण अन्यथा अणु
			reg_hor[c] = 0;
			reg_ver[c] = 0;
		पूर्ण
	पूर्ण

	cnt |= conf->hist_bins << ISPHIST_CNT_BINS_SHIFT;
	चयन (conf->hist_bins) अणु
	हाल OMAP3ISP_HIST_BINS_256:
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 8) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		अवरोध;
	हाल OMAP3ISP_HIST_BINS_128:
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 7) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		अवरोध;
	हाल OMAP3ISP_HIST_BINS_64:
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 6) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		अवरोध;
	शेष: /* OMAP3ISP_HIST_BINS_32 */
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 5) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		अवरोध;
	पूर्ण

	hist_reset_mem(hist);

	isp_reg_ग_लिखोl(isp, cnt, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT);
	isp_reg_ग_लिखोl(isp, wb_gain,  OMAP3_ISP_IOMEM_HIST, ISPHIST_WB_GAIN);
	isp_reg_ग_लिखोl(isp, reg_hor[0], OMAP3_ISP_IOMEM_HIST, ISPHIST_R0_HORZ);
	isp_reg_ग_लिखोl(isp, reg_ver[0], OMAP3_ISP_IOMEM_HIST, ISPHIST_R0_VERT);
	isp_reg_ग_लिखोl(isp, reg_hor[1], OMAP3_ISP_IOMEM_HIST, ISPHIST_R1_HORZ);
	isp_reg_ग_लिखोl(isp, reg_ver[1], OMAP3_ISP_IOMEM_HIST, ISPHIST_R1_VERT);
	isp_reg_ग_लिखोl(isp, reg_hor[2], OMAP3_ISP_IOMEM_HIST, ISPHIST_R2_HORZ);
	isp_reg_ग_लिखोl(isp, reg_ver[2], OMAP3_ISP_IOMEM_HIST, ISPHIST_R2_VERT);
	isp_reg_ग_लिखोl(isp, reg_hor[3], OMAP3_ISP_IOMEM_HIST, ISPHIST_R3_HORZ);
	isp_reg_ग_लिखोl(isp, reg_ver[3], OMAP3_ISP_IOMEM_HIST, ISPHIST_R3_VERT);

	hist->update = 0;
	hist->config_counter += hist->inc_config;
	hist->inc_config = 0;
	hist->buf_size = conf->buf_size;
पूर्ण

अटल व्योम hist_enable(काष्ठा ispstat *hist, पूर्णांक enable)
अणु
	अगर (enable) अणु
		isp_reg_set(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_PCR,
			    ISPHIST_PCR_ENABLE);
		omap3isp_subclk_enable(hist->isp, OMAP3_ISP_SUBCLK_HIST);
	पूर्ण अन्यथा अणु
		isp_reg_clr(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_PCR,
			    ISPHIST_PCR_ENABLE);
		omap3isp_subclk_disable(hist->isp, OMAP3_ISP_SUBCLK_HIST);
	पूर्ण
पूर्ण

अटल पूर्णांक hist_busy(काष्ठा ispstat *hist)
अणु
	वापस isp_reg_पढ़ोl(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_PCR)
						& ISPHIST_PCR_BUSY;
पूर्ण

अटल व्योम hist_dma_cb(व्योम *data)
अणु
	काष्ठा ispstat *hist = data;

	/* FIXME: The DMA engine API can't report transfer errors :-/ */

	isp_reg_clr(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT,
		    ISPHIST_CNT_CLEAR);

	omap3isp_stat_dma_isr(hist);
	अगर (hist->state != ISPSTAT_DISABLED)
		omap3isp_hist_dma_करोne(hist->isp);
पूर्ण

अटल पूर्णांक hist_buf_dma(काष्ठा ispstat *hist)
अणु
	dma_addr_t dma_addr = hist->active_buf->dma_addr;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dma_slave_config cfg;
	dma_cookie_t cookie;
	पूर्णांक ret;

	अगर (unlikely(!dma_addr)) अणु
		dev_dbg(hist->isp->dev, "hist: invalid DMA buffer address\n");
		जाओ error;
	पूर्ण

	isp_reg_ग_लिखोl(hist->isp, 0, OMAP3_ISP_IOMEM_HIST, ISPHIST_ADDR);
	isp_reg_set(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT,
		    ISPHIST_CNT_CLEAR);
	omap3isp_flush(hist->isp);

	स_रखो(&cfg, 0, माप(cfg));
	cfg.src_addr = hist->isp->mmio_hist_base_phys + ISPHIST_DATA;
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.src_maxburst = hist->buf_size / 4;

	ret = dmaengine_slave_config(hist->dma_ch, &cfg);
	अगर (ret < 0) अणु
		dev_dbg(hist->isp->dev,
			"hist: DMA slave configuration failed\n");
		जाओ error;
	पूर्ण

	tx = dmaengine_prep_slave_single(hist->dma_ch, dma_addr,
					 hist->buf_size, DMA_DEV_TO_MEM,
					 DMA_CTRL_ACK);
	अगर (tx == शून्य) अणु
		dev_dbg(hist->isp->dev,
			"hist: DMA slave preparation failed\n");
		जाओ error;
	पूर्ण

	tx->callback = hist_dma_cb;
	tx->callback_param = hist;
	cookie = tx->tx_submit(tx);
	अगर (dma_submit_error(cookie)) अणु
		dev_dbg(hist->isp->dev, "hist: DMA submission failed\n");
		जाओ error;
	पूर्ण

	dma_async_issue_pending(hist->dma_ch);

	वापस STAT_BUF_WAITING_DMA;

error:
	hist_reset_mem(hist);
	वापस STAT_NO_BUF;
पूर्ण

अटल पूर्णांक hist_buf_pio(काष्ठा ispstat *hist)
अणु
	काष्ठा isp_device *isp = hist->isp;
	u32 *buf = hist->active_buf->virt_addr;
	अचिन्हित पूर्णांक i;

	अगर (!buf) अणु
		dev_dbg(isp->dev, "hist: invalid PIO buffer address\n");
		hist_reset_mem(hist);
		वापस STAT_NO_BUF;
	पूर्ण

	isp_reg_ग_लिखोl(isp, 0, OMAP3_ISP_IOMEM_HIST, ISPHIST_ADDR);

	/*
	 * By setting it, the histogram पूर्णांकernal buffer is being cleared at the
	 * same समय it's being पढ़ो. This bit must be cleared just after all
	 * data is acquired.
	 */
	isp_reg_set(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT, ISPHIST_CNT_CLEAR);

	/*
	 * We'll पढ़ो 4 बार a 4-bytes-word at each iteration क्रम
	 * optimization. It aव्योमs 3/4 of the jumps. We also know buf_size is
	 * भागisible by 16.
	 */
	क्रम (i = hist->buf_size / 16; i > 0; i--) अणु
		*buf++ = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		*buf++ = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		*buf++ = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		*buf++ = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
	पूर्ण
	isp_reg_clr(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT,
		    ISPHIST_CNT_CLEAR);

	वापस STAT_BUF_DONE;
पूर्ण

/*
 * hist_buf_process - Callback from ISP driver क्रम HIST पूर्णांकerrupt.
 */
अटल पूर्णांक hist_buf_process(काष्ठा ispstat *hist)
अणु
	काष्ठा omap3isp_hist_config *user_cfg = hist->priv;
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&hist->buf_err) || hist->state != ISPSTAT_ENABLED) अणु
		hist_reset_mem(hist);
		वापस STAT_NO_BUF;
	पूर्ण

	अगर (--(hist->रुको_acc_frames))
		वापस STAT_NO_BUF;

	अगर (hist->dma_ch)
		ret = hist_buf_dma(hist);
	अन्यथा
		ret = hist_buf_pio(hist);

	hist->रुको_acc_frames = user_cfg->num_acc_frames;

	वापस ret;
पूर्ण

अटल u32 hist_get_buf_size(काष्ठा omap3isp_hist_config *conf)
अणु
	वापस OMAP3ISP_HIST_MEM_SIZE_BINS(conf->hist_bins) * conf->num_regions;
पूर्ण

/*
 * hist_validate_params - Helper function to check user given params.
 * @new_conf: Poपूर्णांकer to user configuration काष्ठाure.
 *
 * Returns 0 on success configuration.
 */
अटल पूर्णांक hist_validate_params(काष्ठा ispstat *hist, व्योम *new_conf)
अणु
	काष्ठा omap3isp_hist_config *user_cfg = new_conf;
	पूर्णांक c;
	u32 buf_size;

	अगर (user_cfg->cfa > OMAP3ISP_HIST_CFA_FOVEONX3)
		वापस -EINVAL;

	/* Regions size and position */

	अगर ((user_cfg->num_regions < OMAP3ISP_HIST_MIN_REGIONS) ||
	    (user_cfg->num_regions > OMAP3ISP_HIST_MAX_REGIONS))
		वापस -EINVAL;

	/* Regions */
	क्रम (c = 0; c < user_cfg->num_regions; c++) अणु
		अगर (user_cfg->region[c].h_start & ~ISPHIST_REG_START_END_MASK)
			वापस -EINVAL;
		अगर (user_cfg->region[c].h_end & ~ISPHIST_REG_START_END_MASK)
			वापस -EINVAL;
		अगर (user_cfg->region[c].v_start & ~ISPHIST_REG_START_END_MASK)
			वापस -EINVAL;
		अगर (user_cfg->region[c].v_end & ~ISPHIST_REG_START_END_MASK)
			वापस -EINVAL;
		अगर (user_cfg->region[c].h_start > user_cfg->region[c].h_end)
			वापस -EINVAL;
		अगर (user_cfg->region[c].v_start > user_cfg->region[c].v_end)
			वापस -EINVAL;
	पूर्ण

	चयन (user_cfg->num_regions) अणु
	हाल 1:
		अगर (user_cfg->hist_bins > OMAP3ISP_HIST_BINS_256)
			वापस -EINVAL;
		अवरोध;
	हाल 2:
		अगर (user_cfg->hist_bins > OMAP3ISP_HIST_BINS_128)
			वापस -EINVAL;
		अवरोध;
	शेष: /* 3 or 4 */
		अगर (user_cfg->hist_bins > OMAP3ISP_HIST_BINS_64)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	buf_size = hist_get_buf_size(user_cfg);
	अगर (buf_size > user_cfg->buf_size)
		/* User's buf_size request wasn't enough */
		user_cfg->buf_size = buf_size;
	अन्यथा अगर (user_cfg->buf_size > OMAP3ISP_HIST_MAX_BUF_SIZE)
		user_cfg->buf_size = OMAP3ISP_HIST_MAX_BUF_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक hist_comp_params(काष्ठा ispstat *hist,
			    काष्ठा omap3isp_hist_config *user_cfg)
अणु
	काष्ठा omap3isp_hist_config *cur_cfg = hist->priv;
	पूर्णांक c;

	अगर (cur_cfg->cfa != user_cfg->cfa)
		वापस 1;

	अगर (cur_cfg->num_acc_frames != user_cfg->num_acc_frames)
		वापस 1;

	अगर (cur_cfg->hist_bins != user_cfg->hist_bins)
		वापस 1;

	क्रम (c = 0; c < OMAP3ISP_HIST_MAX_WG; c++) अणु
		अगर (c == 3 && user_cfg->cfa == OMAP3ISP_HIST_CFA_FOVEONX3)
			अवरोध;
		अन्यथा अगर (cur_cfg->wg[c] != user_cfg->wg[c])
			वापस 1;
	पूर्ण

	अगर (cur_cfg->num_regions != user_cfg->num_regions)
		वापस 1;

	/* Regions */
	क्रम (c = 0; c < user_cfg->num_regions; c++) अणु
		अगर (cur_cfg->region[c].h_start != user_cfg->region[c].h_start)
			वापस 1;
		अगर (cur_cfg->region[c].h_end != user_cfg->region[c].h_end)
			वापस 1;
		अगर (cur_cfg->region[c].v_start != user_cfg->region[c].v_start)
			वापस 1;
		अगर (cur_cfg->region[c].v_end != user_cfg->region[c].v_end)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * hist_update_params - Helper function to check and store user given params.
 * @new_conf: Poपूर्णांकer to user configuration काष्ठाure.
 */
अटल व्योम hist_set_params(काष्ठा ispstat *hist, व्योम *new_conf)
अणु
	काष्ठा omap3isp_hist_config *user_cfg = new_conf;
	काष्ठा omap3isp_hist_config *cur_cfg = hist->priv;

	अगर (!hist->configured || hist_comp_params(hist, user_cfg)) अणु
		स_नकल(cur_cfg, user_cfg, माप(*user_cfg));
		अगर (user_cfg->num_acc_frames == 0)
			user_cfg->num_acc_frames = 1;
		hist->inc_config++;
		hist->update = 1;
		/*
		 * User might be asked क्रम a bigger buffer than necessary क्रम
		 * this configuration. In order to वापस the right amount of
		 * data during buffer request, let's calculate the size here
		 * instead of stick with user_cfg->buf_size.
		 */
		cur_cfg->buf_size = hist_get_buf_size(cur_cfg);

	पूर्ण
पूर्ण

अटल दीर्घ hist_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा ispstat *stat = v4l2_get_subdevdata(sd);

	चयन (cmd) अणु
	हाल VIDIOC_OMAP3ISP_HIST_CFG:
		वापस omap3isp_stat_config(stat, arg);
	हाल VIDIOC_OMAP3ISP_STAT_REQ:
		वापस omap3isp_stat_request_statistics(stat, arg);
	हाल VIDIOC_OMAP3ISP_STAT_REQ_TIME32:
		वापस omap3isp_stat_request_statistics_समय32(stat, arg);
	हाल VIDIOC_OMAP3ISP_STAT_EN: अणु
		पूर्णांक *en = arg;
		वापस omap3isp_stat_enable(stat, !!*en);
	पूर्ण
	पूर्ण

	वापस -ENOIOCTLCMD;

पूर्ण

अटल स्थिर काष्ठा ispstat_ops hist_ops = अणु
	.validate_params	= hist_validate_params,
	.set_params		= hist_set_params,
	.setup_regs		= hist_setup_regs,
	.enable			= hist_enable,
	.busy			= hist_busy,
	.buf_process		= hist_buf_process,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops hist_subdev_core_ops = अणु
	.ioctl = hist_ioctl,
	.subscribe_event = omap3isp_stat_subscribe_event,
	.unsubscribe_event = omap3isp_stat_unsubscribe_event,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops hist_subdev_video_ops = अणु
	.s_stream = omap3isp_stat_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops hist_subdev_ops = अणु
	.core = &hist_subdev_core_ops,
	.video = &hist_subdev_video_ops,
पूर्ण;

/*
 * omap3isp_hist_init - Module Initialization.
 */
पूर्णांक omap3isp_hist_init(काष्ठा isp_device *isp)
अणु
	काष्ठा ispstat *hist = &isp->isp_hist;
	काष्ठा omap3isp_hist_config *hist_cfg;
	पूर्णांक ret;

	hist_cfg = kzalloc(माप(*hist_cfg), GFP_KERNEL);
	अगर (hist_cfg == शून्य)
		वापस -ENOMEM;

	hist->isp = isp;

	अगर (HIST_CONFIG_DMA) अणु
		dma_cap_mask_t mask;

		/*
		 * We need slave capable channel without DMA request line क्रम
		 * पढ़ोing out the data.
		 * For this we can use dma_request_chan_by_mask() as we are
		 * happy with any channel as दीर्घ as it is capable of slave
		 * configuration.
		 */
		dma_cap_zero(mask);
		dma_cap_set(DMA_SLAVE, mask);
		hist->dma_ch = dma_request_chan_by_mask(&mask);
		अगर (IS_ERR(hist->dma_ch)) अणु
			ret = PTR_ERR(hist->dma_ch);
			अगर (ret == -EPROBE_DEFER)
				जाओ err;

			hist->dma_ch = शून्य;
			dev_warn(isp->dev,
				 "hist: DMA channel request failed, using PIO\n");
		पूर्ण अन्यथा अणु
			dev_dbg(isp->dev, "hist: using DMA channel %s\n",
				dma_chan_name(hist->dma_ch));
		पूर्ण
	पूर्ण

	hist->ops = &hist_ops;
	hist->priv = hist_cfg;
	hist->event_type = V4L2_EVENT_OMAP3ISP_HIST;

	ret = omap3isp_stat_init(hist, "histogram", &hist_subdev_ops);

err:
	अगर (ret) अणु
		अगर (!IS_ERR_OR_शून्य(hist->dma_ch))
			dma_release_channel(hist->dma_ch);
		kमुक्त(hist_cfg);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * omap3isp_hist_cleanup - Module cleanup.
 */
व्योम omap3isp_hist_cleanup(काष्ठा isp_device *isp)
अणु
	काष्ठा ispstat *hist = &isp->isp_hist;

	अगर (hist->dma_ch)
		dma_release_channel(hist->dma_ch);

	omap3isp_stat_cleanup(hist);
पूर्ण
