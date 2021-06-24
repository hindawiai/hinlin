<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isph3a.c
 *
 * TI OMAP3 ISP - H3A module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: David Cohen <dacohen@gmail.com>
 *	     Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "isp.h"
#समावेश "isph3a.h"
#समावेश "ispstat.h"

/*
 * h3a_aewb_update_regs - Helper function to update h3a रेजिस्टरs.
 */
अटल व्योम h3a_aewb_setup_regs(काष्ठा ispstat *aewb, व्योम *priv)
अणु
	काष्ठा omap3isp_h3a_aewb_config *conf = priv;
	u32 pcr;
	u32 win1;
	u32 start;
	u32 blk;
	u32 subwin;

	अगर (aewb->state == ISPSTAT_DISABLED)
		वापस;

	isp_reg_ग_लिखोl(aewb->isp, aewb->active_buf->dma_addr,
		       OMAP3_ISP_IOMEM_H3A, ISPH3A_AEWBUFST);

	अगर (!aewb->update)
		वापस;

	/* Converting config metadata पूर्णांकo reg values */
	pcr = conf->saturation_limit << ISPH3A_PCR_AEW_AVE2LMT_SHIFT;
	pcr |= !!conf->alaw_enable << ISPH3A_PCR_AEW_ALAW_EN_SHIFT;

	win1 = ((conf->win_height >> 1) - 1) << ISPH3A_AEWWIN1_WINH_SHIFT;
	win1 |= ((conf->win_width >> 1) - 1) << ISPH3A_AEWWIN1_WINW_SHIFT;
	win1 |= (conf->ver_win_count - 1) << ISPH3A_AEWWIN1_WINVC_SHIFT;
	win1 |= (conf->hor_win_count - 1) << ISPH3A_AEWWIN1_WINHC_SHIFT;

	start = conf->hor_win_start << ISPH3A_AEWINSTART_WINSH_SHIFT;
	start |= conf->ver_win_start << ISPH3A_AEWINSTART_WINSV_SHIFT;

	blk = conf->blk_ver_win_start << ISPH3A_AEWINBLK_WINSV_SHIFT;
	blk |= ((conf->blk_win_height >> 1) - 1) << ISPH3A_AEWINBLK_WINH_SHIFT;

	subwin = ((conf->subsample_ver_inc >> 1) - 1) <<
		 ISPH3A_AEWSUBWIN_AEWINCV_SHIFT;
	subwin |= ((conf->subsample_hor_inc >> 1) - 1) <<
		  ISPH3A_AEWSUBWIN_AEWINCH_SHIFT;

	isp_reg_ग_लिखोl(aewb->isp, win1, OMAP3_ISP_IOMEM_H3A, ISPH3A_AEWWIN1);
	isp_reg_ग_लिखोl(aewb->isp, start, OMAP3_ISP_IOMEM_H3A,
		       ISPH3A_AEWINSTART);
	isp_reg_ग_लिखोl(aewb->isp, blk, OMAP3_ISP_IOMEM_H3A, ISPH3A_AEWINBLK);
	isp_reg_ग_लिखोl(aewb->isp, subwin, OMAP3_ISP_IOMEM_H3A,
		       ISPH3A_AEWSUBWIN);
	isp_reg_clr_set(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR,
			ISPH3A_PCR_AEW_MASK, pcr);

	aewb->update = 0;
	aewb->config_counter += aewb->inc_config;
	aewb->inc_config = 0;
	aewb->buf_size = conf->buf_size;
पूर्ण

अटल व्योम h3a_aewb_enable(काष्ठा ispstat *aewb, पूर्णांक enable)
अणु
	अगर (enable) अणु
		isp_reg_set(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR,
			    ISPH3A_PCR_AEW_EN);
		omap3isp_subclk_enable(aewb->isp, OMAP3_ISP_SUBCLK_AEWB);
	पूर्ण अन्यथा अणु
		isp_reg_clr(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR,
			    ISPH3A_PCR_AEW_EN);
		omap3isp_subclk_disable(aewb->isp, OMAP3_ISP_SUBCLK_AEWB);
	पूर्ण
पूर्ण

अटल पूर्णांक h3a_aewb_busy(काष्ठा ispstat *aewb)
अणु
	वापस isp_reg_पढ़ोl(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR)
						& ISPH3A_PCR_BUSYAEAWB;
पूर्ण

अटल u32 h3a_aewb_get_buf_size(काष्ठा omap3isp_h3a_aewb_config *conf)
अणु
	/* Number of configured winकरोws + extra row क्रम black data */
	u32 win_count = (conf->ver_win_count + 1) * conf->hor_win_count;

	/*
	 * Unsaturated block counts क्रम each 8 winकरोws.
	 * 1 extra क्रम the last (win_count % 8) winकरोws अगर win_count is not
	 * भागisible by 8.
	 */
	win_count += (win_count + 7) / 8;

	वापस win_count * AEWB_PACKET_SIZE;
पूर्ण

अटल पूर्णांक h3a_aewb_validate_params(काष्ठा ispstat *aewb, व्योम *new_conf)
अणु
	काष्ठा omap3isp_h3a_aewb_config *user_cfg = new_conf;
	u32 buf_size;

	अगर (unlikely(user_cfg->saturation_limit >
		     OMAP3ISP_AEWB_MAX_SATURATION_LIM))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->win_height < OMAP3ISP_AEWB_MIN_WIN_H ||
		     user_cfg->win_height > OMAP3ISP_AEWB_MAX_WIN_H ||
		     user_cfg->win_height & 0x01))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->win_width < OMAP3ISP_AEWB_MIN_WIN_W ||
		     user_cfg->win_width > OMAP3ISP_AEWB_MAX_WIN_W ||
		     user_cfg->win_width & 0x01))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->ver_win_count < OMAP3ISP_AEWB_MIN_WINVC ||
		     user_cfg->ver_win_count > OMAP3ISP_AEWB_MAX_WINVC))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->hor_win_count < OMAP3ISP_AEWB_MIN_WINHC ||
		     user_cfg->hor_win_count > OMAP3ISP_AEWB_MAX_WINHC))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->ver_win_start > OMAP3ISP_AEWB_MAX_WINSTART))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->hor_win_start > OMAP3ISP_AEWB_MAX_WINSTART))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->blk_ver_win_start > OMAP3ISP_AEWB_MAX_WINSTART))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->blk_win_height < OMAP3ISP_AEWB_MIN_WIN_H ||
		     user_cfg->blk_win_height > OMAP3ISP_AEWB_MAX_WIN_H ||
		     user_cfg->blk_win_height & 0x01))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->subsample_ver_inc < OMAP3ISP_AEWB_MIN_SUB_INC ||
		     user_cfg->subsample_ver_inc > OMAP3ISP_AEWB_MAX_SUB_INC ||
		     user_cfg->subsample_ver_inc & 0x01))
		वापस -EINVAL;

	अगर (unlikely(user_cfg->subsample_hor_inc < OMAP3ISP_AEWB_MIN_SUB_INC ||
		     user_cfg->subsample_hor_inc > OMAP3ISP_AEWB_MAX_SUB_INC ||
		     user_cfg->subsample_hor_inc & 0x01))
		वापस -EINVAL;

	buf_size = h3a_aewb_get_buf_size(user_cfg);
	अगर (buf_size > user_cfg->buf_size)
		user_cfg->buf_size = buf_size;
	अन्यथा अगर (user_cfg->buf_size > OMAP3ISP_AEWB_MAX_BUF_SIZE)
		user_cfg->buf_size = OMAP3ISP_AEWB_MAX_BUF_SIZE;

	वापस 0;
पूर्ण

/*
 * h3a_aewb_set_params - Helper function to check & store user given params.
 * @new_conf: Poपूर्णांकer to AE and AWB parameters काष्ठा.
 *
 * As most of them are busy-lock रेजिस्टरs, need to रुको until AEW_BUSY = 0 to
 * program them during ISR.
 */
अटल व्योम h3a_aewb_set_params(काष्ठा ispstat *aewb, व्योम *new_conf)
अणु
	काष्ठा omap3isp_h3a_aewb_config *user_cfg = new_conf;
	काष्ठा omap3isp_h3a_aewb_config *cur_cfg = aewb->priv;
	पूर्णांक update = 0;

	अगर (cur_cfg->saturation_limit != user_cfg->saturation_limit) अणु
		cur_cfg->saturation_limit = user_cfg->saturation_limit;
		update = 1;
	पूर्ण
	अगर (cur_cfg->alaw_enable != user_cfg->alaw_enable) अणु
		cur_cfg->alaw_enable = user_cfg->alaw_enable;
		update = 1;
	पूर्ण
	अगर (cur_cfg->win_height != user_cfg->win_height) अणु
		cur_cfg->win_height = user_cfg->win_height;
		update = 1;
	पूर्ण
	अगर (cur_cfg->win_width != user_cfg->win_width) अणु
		cur_cfg->win_width = user_cfg->win_width;
		update = 1;
	पूर्ण
	अगर (cur_cfg->ver_win_count != user_cfg->ver_win_count) अणु
		cur_cfg->ver_win_count = user_cfg->ver_win_count;
		update = 1;
	पूर्ण
	अगर (cur_cfg->hor_win_count != user_cfg->hor_win_count) अणु
		cur_cfg->hor_win_count = user_cfg->hor_win_count;
		update = 1;
	पूर्ण
	अगर (cur_cfg->ver_win_start != user_cfg->ver_win_start) अणु
		cur_cfg->ver_win_start = user_cfg->ver_win_start;
		update = 1;
	पूर्ण
	अगर (cur_cfg->hor_win_start != user_cfg->hor_win_start) अणु
		cur_cfg->hor_win_start = user_cfg->hor_win_start;
		update = 1;
	पूर्ण
	अगर (cur_cfg->blk_ver_win_start != user_cfg->blk_ver_win_start) अणु
		cur_cfg->blk_ver_win_start = user_cfg->blk_ver_win_start;
		update = 1;
	पूर्ण
	अगर (cur_cfg->blk_win_height != user_cfg->blk_win_height) अणु
		cur_cfg->blk_win_height = user_cfg->blk_win_height;
		update = 1;
	पूर्ण
	अगर (cur_cfg->subsample_ver_inc != user_cfg->subsample_ver_inc) अणु
		cur_cfg->subsample_ver_inc = user_cfg->subsample_ver_inc;
		update = 1;
	पूर्ण
	अगर (cur_cfg->subsample_hor_inc != user_cfg->subsample_hor_inc) अणु
		cur_cfg->subsample_hor_inc = user_cfg->subsample_hor_inc;
		update = 1;
	पूर्ण

	अगर (update || !aewb->configured) अणु
		aewb->inc_config++;
		aewb->update = 1;
		cur_cfg->buf_size = h3a_aewb_get_buf_size(cur_cfg);
	पूर्ण
पूर्ण

अटल दीर्घ h3a_aewb_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा ispstat *stat = v4l2_get_subdevdata(sd);

	चयन (cmd) अणु
	हाल VIDIOC_OMAP3ISP_AEWB_CFG:
		वापस omap3isp_stat_config(stat, arg);
	हाल VIDIOC_OMAP3ISP_STAT_REQ:
		वापस omap3isp_stat_request_statistics(stat, arg);
	हाल VIDIOC_OMAP3ISP_STAT_REQ_TIME32:
		वापस omap3isp_stat_request_statistics_समय32(stat, arg);
	हाल VIDIOC_OMAP3ISP_STAT_EN: अणु
		अचिन्हित दीर्घ *en = arg;
		वापस omap3isp_stat_enable(stat, !!*en);
	पूर्ण
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

अटल स्थिर काष्ठा ispstat_ops h3a_aewb_ops = अणु
	.validate_params	= h3a_aewb_validate_params,
	.set_params		= h3a_aewb_set_params,
	.setup_regs		= h3a_aewb_setup_regs,
	.enable			= h3a_aewb_enable,
	.busy			= h3a_aewb_busy,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops h3a_aewb_subdev_core_ops = अणु
	.ioctl = h3a_aewb_ioctl,
	.subscribe_event = omap3isp_stat_subscribe_event,
	.unsubscribe_event = omap3isp_stat_unsubscribe_event,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops h3a_aewb_subdev_video_ops = अणु
	.s_stream = omap3isp_stat_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops h3a_aewb_subdev_ops = अणु
	.core = &h3a_aewb_subdev_core_ops,
	.video = &h3a_aewb_subdev_video_ops,
पूर्ण;

/*
 * omap3isp_h3a_aewb_init - Module Initialisation.
 */
पूर्णांक omap3isp_h3a_aewb_init(काष्ठा isp_device *isp)
अणु
	काष्ठा ispstat *aewb = &isp->isp_aewb;
	काष्ठा omap3isp_h3a_aewb_config *aewb_cfg;
	काष्ठा omap3isp_h3a_aewb_config *aewb_recover_cfg = शून्य;
	पूर्णांक ret;

	aewb_cfg = kzalloc(माप(*aewb_cfg), GFP_KERNEL);
	अगर (!aewb_cfg)
		वापस -ENOMEM;

	aewb->ops = &h3a_aewb_ops;
	aewb->priv = aewb_cfg;
	aewb->event_type = V4L2_EVENT_OMAP3ISP_AEWB;
	aewb->isp = isp;

	/* Set recover state configuration */
	aewb_recover_cfg = kzalloc(माप(*aewb_recover_cfg), GFP_KERNEL);
	अगर (!aewb_recover_cfg) अणु
		dev_err(aewb->isp->dev,
			"AEWB: cannot allocate memory for recover configuration.\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	aewb_recover_cfg->saturation_limit = OMAP3ISP_AEWB_MAX_SATURATION_LIM;
	aewb_recover_cfg->win_height = OMAP3ISP_AEWB_MIN_WIN_H;
	aewb_recover_cfg->win_width = OMAP3ISP_AEWB_MIN_WIN_W;
	aewb_recover_cfg->ver_win_count = OMAP3ISP_AEWB_MIN_WINVC;
	aewb_recover_cfg->hor_win_count = OMAP3ISP_AEWB_MIN_WINHC;
	aewb_recover_cfg->blk_ver_win_start = aewb_recover_cfg->ver_win_start +
		aewb_recover_cfg->win_height * aewb_recover_cfg->ver_win_count;
	aewb_recover_cfg->blk_win_height = OMAP3ISP_AEWB_MIN_WIN_H;
	aewb_recover_cfg->subsample_ver_inc = OMAP3ISP_AEWB_MIN_SUB_INC;
	aewb_recover_cfg->subsample_hor_inc = OMAP3ISP_AEWB_MIN_SUB_INC;

	अगर (h3a_aewb_validate_params(aewb, aewb_recover_cfg)) अणु
		dev_err(aewb->isp->dev,
			"AEWB: recover configuration is invalid.\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	aewb_recover_cfg->buf_size = h3a_aewb_get_buf_size(aewb_recover_cfg);
	aewb->recover_priv = aewb_recover_cfg;

	ret = omap3isp_stat_init(aewb, "AEWB", &h3a_aewb_subdev_ops);

err:
	अगर (ret) अणु
		kमुक्त(aewb_cfg);
		kमुक्त(aewb_recover_cfg);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * omap3isp_h3a_aewb_cleanup - Module निकास.
 */
व्योम omap3isp_h3a_aewb_cleanup(काष्ठा isp_device *isp)
अणु
	omap3isp_stat_cleanup(&isp->isp_aewb);
पूर्ण
