<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isph3a_af.c
 *
 * TI OMAP3 ISP - H3A AF module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: David Cohen <dacohen@gmail.com>
 *	     Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

/* Linux specअगरic include files */
#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश "isp.h"
#समावेश "isph3a.h"
#समावेश "ispstat.h"

#घोषणा IS_OUT_OF_BOUNDS(value, min, max)		\
	(((value) < (min)) || ((value) > (max)))

अटल व्योम h3a_af_setup_regs(काष्ठा ispstat *af, व्योम *priv)
अणु
	काष्ठा omap3isp_h3a_af_config *conf = priv;
	u32 pcr;
	u32 pax1;
	u32 pax2;
	u32 paxstart;
	u32 coef;
	u32 base_coef_set0;
	u32 base_coef_set1;
	पूर्णांक index;

	अगर (af->state == ISPSTAT_DISABLED)
		वापस;

	isp_reg_ग_लिखोl(af->isp, af->active_buf->dma_addr, OMAP3_ISP_IOMEM_H3A,
		       ISPH3A_AFBUFST);

	अगर (!af->update)
		वापस;

	/* Configure Hardware Registers */
	pax1 = ((conf->paxel.width >> 1) - 1) << AF_PAXW_SHIFT;
	/* Set height in AFPAX1 */
	pax1 |= (conf->paxel.height >> 1) - 1;
	isp_reg_ग_लिखोl(af->isp, pax1, OMAP3_ISP_IOMEM_H3A, ISPH3A_AFPAX1);

	/* Configure AFPAX2 Register */
	/* Set Line Increment in AFPAX2 Register */
	pax2 = ((conf->paxel.line_inc >> 1) - 1) << AF_LINE_INCR_SHIFT;
	/* Set Vertical Count */
	pax2 |= (conf->paxel.v_cnt - 1) << AF_VT_COUNT_SHIFT;
	/* Set Horizontal Count */
	pax2 |= (conf->paxel.h_cnt - 1);
	isp_reg_ग_लिखोl(af->isp, pax2, OMAP3_ISP_IOMEM_H3A, ISPH3A_AFPAX2);

	/* Configure PAXSTART Register */
	/*Configure Horizontal Start */
	paxstart = conf->paxel.h_start << AF_HZ_START_SHIFT;
	/* Configure Vertical Start */
	paxstart |= conf->paxel.v_start;
	isp_reg_ग_लिखोl(af->isp, paxstart, OMAP3_ISP_IOMEM_H3A,
		       ISPH3A_AFPAXSTART);

	/*SetIIRSH Register */
	isp_reg_ग_लिखोl(af->isp, conf->iir.h_start,
		       OMAP3_ISP_IOMEM_H3A, ISPH3A_AFIIRSH);

	base_coef_set0 = ISPH3A_AFCOEF010;
	base_coef_set1 = ISPH3A_AFCOEF110;
	क्रम (index = 0; index <= 8; index += 2) अणु
		/*Set IIR Filter0 Coefficients */
		coef = 0;
		coef |= conf->iir.coeff_set0[index];
		coef |= conf->iir.coeff_set0[index + 1] <<
			AF_COEF_SHIFT;
		isp_reg_ग_लिखोl(af->isp, coef, OMAP3_ISP_IOMEM_H3A,
			       base_coef_set0);
		base_coef_set0 += AFCOEF_OFFSET;

		/*Set IIR Filter1 Coefficients */
		coef = 0;
		coef |= conf->iir.coeff_set1[index];
		coef |= conf->iir.coeff_set1[index + 1] <<
			AF_COEF_SHIFT;
		isp_reg_ग_लिखोl(af->isp, coef, OMAP3_ISP_IOMEM_H3A,
			       base_coef_set1);
		base_coef_set1 += AFCOEF_OFFSET;
	पूर्ण
	/* set AFCOEF0010 Register */
	isp_reg_ग_लिखोl(af->isp, conf->iir.coeff_set0[10],
		       OMAP3_ISP_IOMEM_H3A, ISPH3A_AFCOEF0010);
	/* set AFCOEF1010 Register */
	isp_reg_ग_लिखोl(af->isp, conf->iir.coeff_set1[10],
		       OMAP3_ISP_IOMEM_H3A, ISPH3A_AFCOEF1010);

	/* PCR Register */
	/* Set RGB Position */
	pcr = conf->rgb_pos << AF_RGBPOS_SHIFT;
	/* Set Accumulator Mode */
	अगर (conf->fvmode == OMAP3ISP_AF_MODE_PEAK)
		pcr |= AF_FVMODE;
	/* Set A-law */
	अगर (conf->alaw_enable)
		pcr |= AF_ALAW_EN;
	/* HMF Configurations */
	अगर (conf->hmf.enable) अणु
		/* Enable HMF */
		pcr |= AF_MED_EN;
		/* Set Median Threshold */
		pcr |= conf->hmf.threshold << AF_MED_TH_SHIFT;
	पूर्ण
	/* Set PCR Register */
	isp_reg_clr_set(af->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR,
			AF_PCR_MASK, pcr);

	af->update = 0;
	af->config_counter += af->inc_config;
	af->inc_config = 0;
	af->buf_size = conf->buf_size;
पूर्ण

अटल व्योम h3a_af_enable(काष्ठा ispstat *af, पूर्णांक enable)
अणु
	अगर (enable) अणु
		isp_reg_set(af->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR,
			    ISPH3A_PCR_AF_EN);
		omap3isp_subclk_enable(af->isp, OMAP3_ISP_SUBCLK_AF);
	पूर्ण अन्यथा अणु
		isp_reg_clr(af->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR,
			    ISPH3A_PCR_AF_EN);
		omap3isp_subclk_disable(af->isp, OMAP3_ISP_SUBCLK_AF);
	पूर्ण
पूर्ण

अटल पूर्णांक h3a_af_busy(काष्ठा ispstat *af)
अणु
	वापस isp_reg_पढ़ोl(af->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR)
						& ISPH3A_PCR_BUSYAF;
पूर्ण

अटल u32 h3a_af_get_buf_size(काष्ठा omap3isp_h3a_af_config *conf)
अणु
	वापस conf->paxel.h_cnt * conf->paxel.v_cnt * OMAP3ISP_AF_PAXEL_SIZE;
पूर्ण

/* Function to check paxel parameters */
अटल पूर्णांक h3a_af_validate_params(काष्ठा ispstat *af, व्योम *new_conf)
अणु
	काष्ठा omap3isp_h3a_af_config *user_cfg = new_conf;
	काष्ठा omap3isp_h3a_af_paxel *paxel_cfg = &user_cfg->paxel;
	काष्ठा omap3isp_h3a_af_iir *iir_cfg = &user_cfg->iir;
	पूर्णांक index;
	u32 buf_size;

	/* Check horizontal Count */
	अगर (IS_OUT_OF_BOUNDS(paxel_cfg->h_cnt,
			     OMAP3ISP_AF_PAXEL_HORIZONTAL_COUNT_MIN,
			     OMAP3ISP_AF_PAXEL_HORIZONTAL_COUNT_MAX))
		वापस -EINVAL;

	/* Check Vertical Count */
	अगर (IS_OUT_OF_BOUNDS(paxel_cfg->v_cnt,
			     OMAP3ISP_AF_PAXEL_VERTICAL_COUNT_MIN,
			     OMAP3ISP_AF_PAXEL_VERTICAL_COUNT_MAX))
		वापस -EINVAL;

	अगर (IS_OUT_OF_BOUNDS(paxel_cfg->height, OMAP3ISP_AF_PAXEL_HEIGHT_MIN,
			     OMAP3ISP_AF_PAXEL_HEIGHT_MAX) ||
	    paxel_cfg->height % 2)
		वापस -EINVAL;

	/* Check width */
	अगर (IS_OUT_OF_BOUNDS(paxel_cfg->width, OMAP3ISP_AF_PAXEL_WIDTH_MIN,
			     OMAP3ISP_AF_PAXEL_WIDTH_MAX) ||
	    paxel_cfg->width % 2)
		वापस -EINVAL;

	/* Check Line Increment */
	अगर (IS_OUT_OF_BOUNDS(paxel_cfg->line_inc,
			     OMAP3ISP_AF_PAXEL_INCREMENT_MIN,
			     OMAP3ISP_AF_PAXEL_INCREMENT_MAX) ||
	    paxel_cfg->line_inc % 2)
		वापस -EINVAL;

	/* Check Horizontal Start */
	अगर ((paxel_cfg->h_start < iir_cfg->h_start) ||
	    IS_OUT_OF_BOUNDS(paxel_cfg->h_start,
			     OMAP3ISP_AF_PAXEL_HZSTART_MIN,
			     OMAP3ISP_AF_PAXEL_HZSTART_MAX))
		वापस -EINVAL;

	/* Check IIR */
	क्रम (index = 0; index < OMAP3ISP_AF_NUM_COEF; index++) अणु
		अगर ((iir_cfg->coeff_set0[index]) > OMAP3ISP_AF_COEF_MAX)
			वापस -EINVAL;

		अगर ((iir_cfg->coeff_set1[index]) > OMAP3ISP_AF_COEF_MAX)
			वापस -EINVAL;
	पूर्ण

	अगर (IS_OUT_OF_BOUNDS(iir_cfg->h_start, OMAP3ISP_AF_IIRSH_MIN,
			     OMAP3ISP_AF_IIRSH_MAX))
		वापस -EINVAL;

	/* Hack: If paxel size is 12, the 10th AF winकरोw may be corrupted */
	अगर ((paxel_cfg->h_cnt * paxel_cfg->v_cnt > 9) &&
	    (paxel_cfg->width * paxel_cfg->height == 12))
		वापस -EINVAL;

	buf_size = h3a_af_get_buf_size(user_cfg);
	अगर (buf_size > user_cfg->buf_size)
		/* User buf_size request wasn't enough */
		user_cfg->buf_size = buf_size;
	अन्यथा अगर (user_cfg->buf_size > OMAP3ISP_AF_MAX_BUF_SIZE)
		user_cfg->buf_size = OMAP3ISP_AF_MAX_BUF_SIZE;

	वापस 0;
पूर्ण

/* Update local parameters */
अटल व्योम h3a_af_set_params(काष्ठा ispstat *af, व्योम *new_conf)
अणु
	काष्ठा omap3isp_h3a_af_config *user_cfg = new_conf;
	काष्ठा omap3isp_h3a_af_config *cur_cfg = af->priv;
	पूर्णांक update = 0;
	पूर्णांक index;

	/* alaw */
	अगर (cur_cfg->alaw_enable != user_cfg->alaw_enable) अणु
		update = 1;
		जाओ out;
	पूर्ण

	/* hmf */
	अगर (cur_cfg->hmf.enable != user_cfg->hmf.enable) अणु
		update = 1;
		जाओ out;
	पूर्ण
	अगर (cur_cfg->hmf.threshold != user_cfg->hmf.threshold) अणु
		update = 1;
		जाओ out;
	पूर्ण

	/* rgbpos */
	अगर (cur_cfg->rgb_pos != user_cfg->rgb_pos) अणु
		update = 1;
		जाओ out;
	पूर्ण

	/* iir */
	अगर (cur_cfg->iir.h_start != user_cfg->iir.h_start) अणु
		update = 1;
		जाओ out;
	पूर्ण
	क्रम (index = 0; index < OMAP3ISP_AF_NUM_COEF; index++) अणु
		अगर (cur_cfg->iir.coeff_set0[index] !=
				user_cfg->iir.coeff_set0[index]) अणु
			update = 1;
			जाओ out;
		पूर्ण
		अगर (cur_cfg->iir.coeff_set1[index] !=
				user_cfg->iir.coeff_set1[index]) अणु
			update = 1;
			जाओ out;
		पूर्ण
	पूर्ण

	/* paxel */
	अगर ((cur_cfg->paxel.width != user_cfg->paxel.width) ||
	    (cur_cfg->paxel.height != user_cfg->paxel.height) ||
	    (cur_cfg->paxel.h_start != user_cfg->paxel.h_start) ||
	    (cur_cfg->paxel.v_start != user_cfg->paxel.v_start) ||
	    (cur_cfg->paxel.h_cnt != user_cfg->paxel.h_cnt) ||
	    (cur_cfg->paxel.v_cnt != user_cfg->paxel.v_cnt) ||
	    (cur_cfg->paxel.line_inc != user_cfg->paxel.line_inc)) अणु
		update = 1;
		जाओ out;
	पूर्ण

	/* af_mode */
	अगर (cur_cfg->fvmode != user_cfg->fvmode)
		update = 1;

out:
	अगर (update || !af->configured) अणु
		स_नकल(cur_cfg, user_cfg, माप(*cur_cfg));
		af->inc_config++;
		af->update = 1;
		/*
		 * User might be asked क्रम a bigger buffer than necessary क्रम
		 * this configuration. In order to वापस the right amount of
		 * data during buffer request, let's calculate the size here
		 * instead of stick with user_cfg->buf_size.
		 */
		cur_cfg->buf_size = h3a_af_get_buf_size(cur_cfg);
	पूर्ण
पूर्ण

अटल दीर्घ h3a_af_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा ispstat *stat = v4l2_get_subdevdata(sd);

	चयन (cmd) अणु
	हाल VIDIOC_OMAP3ISP_AF_CFG:
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

अटल स्थिर काष्ठा ispstat_ops h3a_af_ops = अणु
	.validate_params	= h3a_af_validate_params,
	.set_params		= h3a_af_set_params,
	.setup_regs		= h3a_af_setup_regs,
	.enable			= h3a_af_enable,
	.busy			= h3a_af_busy,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops h3a_af_subdev_core_ops = अणु
	.ioctl = h3a_af_ioctl,
	.subscribe_event = omap3isp_stat_subscribe_event,
	.unsubscribe_event = omap3isp_stat_unsubscribe_event,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops h3a_af_subdev_video_ops = अणु
	.s_stream = omap3isp_stat_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops h3a_af_subdev_ops = अणु
	.core = &h3a_af_subdev_core_ops,
	.video = &h3a_af_subdev_video_ops,
पूर्ण;

/* Function to रेजिस्टर the AF अक्षरacter device driver. */
पूर्णांक omap3isp_h3a_af_init(काष्ठा isp_device *isp)
अणु
	काष्ठा ispstat *af = &isp->isp_af;
	काष्ठा omap3isp_h3a_af_config *af_cfg;
	काष्ठा omap3isp_h3a_af_config *af_recover_cfg = शून्य;
	पूर्णांक ret;

	af_cfg = kzalloc(माप(*af_cfg), GFP_KERNEL);
	अगर (af_cfg == शून्य)
		वापस -ENOMEM;

	af->ops = &h3a_af_ops;
	af->priv = af_cfg;
	af->event_type = V4L2_EVENT_OMAP3ISP_AF;
	af->isp = isp;

	/* Set recover state configuration */
	af_recover_cfg = kzalloc(माप(*af_recover_cfg), GFP_KERNEL);
	अगर (!af_recover_cfg) अणु
		dev_err(af->isp->dev,
			"AF: cannot allocate memory for recover configuration.\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	af_recover_cfg->paxel.h_start = OMAP3ISP_AF_PAXEL_HZSTART_MIN;
	af_recover_cfg->paxel.width = OMAP3ISP_AF_PAXEL_WIDTH_MIN;
	af_recover_cfg->paxel.height = OMAP3ISP_AF_PAXEL_HEIGHT_MIN;
	af_recover_cfg->paxel.h_cnt = OMAP3ISP_AF_PAXEL_HORIZONTAL_COUNT_MIN;
	af_recover_cfg->paxel.v_cnt = OMAP3ISP_AF_PAXEL_VERTICAL_COUNT_MIN;
	af_recover_cfg->paxel.line_inc = OMAP3ISP_AF_PAXEL_INCREMENT_MIN;
	अगर (h3a_af_validate_params(af, af_recover_cfg)) अणु
		dev_err(af->isp->dev,
			"AF: recover configuration is invalid.\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	af_recover_cfg->buf_size = h3a_af_get_buf_size(af_recover_cfg);
	af->recover_priv = af_recover_cfg;

	ret = omap3isp_stat_init(af, "AF", &h3a_af_subdev_ops);

err:
	अगर (ret) अणु
		kमुक्त(af_cfg);
		kमुक्त(af_recover_cfg);
	पूर्ण

	वापस ret;
पूर्ण

व्योम omap3isp_h3a_af_cleanup(काष्ठा isp_device *isp)
अणु
	omap3isp_stat_cleanup(&isp->isp_af);
पूर्ण
