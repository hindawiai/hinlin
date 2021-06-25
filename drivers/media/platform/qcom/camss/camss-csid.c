<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-csid.c
 *
 * Qualcomm MSM Camera Subप्रणाली - CSID (CSI Decoder) Module
 *
 * Copyright (c) 2011-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "camss-csid.h"
#समावेश "camss-csid-gen1.h"
#समावेश "camss.h"

#घोषणा MSM_CSID_NAME "msm_csid"

स्थिर अक्षर * स्थिर csid_testgen_modes[] = अणु
	"Disabled",
	"Incrementing",
	"Alternating 0x55/0xAA",
	"All Zeros 0x00",
	"All Ones 0xFF",
	"Pseudo-random Data",
	"User Specified",
	"Complex pattern",
	"Color box",
	"Color bars",
	शून्य
पूर्ण;

u32 csid_find_code(u32 *codes, अचिन्हित पूर्णांक ncodes,
		   अचिन्हित पूर्णांक match_क्रमmat_idx, u32 match_code)
अणु
	पूर्णांक i;

	अगर (!match_code && (match_क्रमmat_idx >= ncodes))
		वापस 0;

	क्रम (i = 0; i < ncodes; i++)
		अगर (match_code) अणु
			अगर (codes[i] == match_code)
				वापस match_code;
		पूर्ण अन्यथा अणु
			अगर (i == match_क्रमmat_idx)
				वापस codes[i];
		पूर्ण

	वापस codes[0];
पूर्ण

स्थिर काष्ठा csid_क्रमmat *csid_get_fmt_entry(स्थिर काष्ठा csid_क्रमmat *क्रमmats,
					     अचिन्हित पूर्णांक nक्रमmats,
					     u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nक्रमmats; i++)
		अगर (code == क्रमmats[i].code)
			वापस &क्रमmats[i];

	WARN(1, "Unknown format\n");

	वापस &क्रमmats[0];
पूर्ण

/*
 * csid_set_घड़ी_rates - Calculate and set घड़ी rates on CSID module
 * @csiphy: CSID device
 */
अटल पूर्णांक csid_set_घड़ी_rates(काष्ठा csid_device *csid)
अणु
	काष्ठा device *dev = csid->camss->dev;
	स्थिर काष्ठा csid_क्रमmat *fmt;
	s64 link_freq;
	पूर्णांक i, j;
	पूर्णांक ret;

	fmt = csid_get_fmt_entry(csid->क्रमmats, csid->nक्रमmats,
				 csid->fmt[MSM_CSIPHY_PAD_SINK].code);
	link_freq = camss_get_link_freq(&csid->subdev.entity, fmt->bpp,
					csid->phy.lane_cnt);
	अगर (link_freq < 0)
		link_freq = 0;

	क्रम (i = 0; i < csid->nघड़ीs; i++) अणु
		काष्ठा camss_घड़ी *घड़ी = &csid->घड़ी[i];

		अगर (!म_भेद(घड़ी->name, "csi0") ||
		    !म_भेद(घड़ी->name, "csi1") ||
		    !म_भेद(घड़ी->name, "csi2") ||
		    !म_भेद(घड़ी->name, "csi3")) अणु
			u64 min_rate = link_freq / 4;
			दीर्घ rate;

			camss_add_घड़ी_margin(&min_rate);

			क्रम (j = 0; j < घड़ी->nfreqs; j++)
				अगर (min_rate < घड़ी->freq[j])
					अवरोध;

			अगर (j == घड़ी->nfreqs) अणु
				dev_err(dev,
					"Pixel clock is too high for CSID\n");
				वापस -EINVAL;
			पूर्ण

			/* अगर sensor pixel घड़ी is not available */
			/* set highest possible CSID घड़ी rate */
			अगर (min_rate == 0)
				j = घड़ी->nfreqs - 1;

			rate = clk_round_rate(घड़ी->clk, घड़ी->freq[j]);
			अगर (rate < 0) अणु
				dev_err(dev, "clk round rate failed: %ld\n",
					rate);
				वापस -EINVAL;
			पूर्ण

			ret = clk_set_rate(घड़ी->clk, rate);
			अगर (ret < 0) अणु
				dev_err(dev, "clk set rate failed: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अगर (घड़ी->nfreqs) अणु
			clk_set_rate(घड़ी->clk, घड़ी->freq[0]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csid_set_घातer - Power on/off CSID module
 * @sd: CSID V4L2 subdevice
 * @on: Requested घातer state
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csid_set_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा csid_device *csid = v4l2_get_subdevdata(sd);
	काष्ठा device *dev = csid->camss->dev;
	पूर्णांक ret;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(dev);
			वापस ret;
		पूर्ण

		ret = regulator_enable(csid->vdda);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(dev);
			वापस ret;
		पूर्ण

		ret = csid_set_घड़ी_rates(csid);
		अगर (ret < 0) अणु
			regulator_disable(csid->vdda);
			pm_runसमय_put_sync(dev);
			वापस ret;
		पूर्ण

		ret = camss_enable_घड़ीs(csid->nघड़ीs, csid->घड़ी, dev);
		अगर (ret < 0) अणु
			regulator_disable(csid->vdda);
			pm_runसमय_put_sync(dev);
			वापस ret;
		पूर्ण

		enable_irq(csid->irq);

		ret = csid->ops->reset(csid);
		अगर (ret < 0) अणु
			disable_irq(csid->irq);
			camss_disable_घड़ीs(csid->nघड़ीs, csid->घड़ी);
			regulator_disable(csid->vdda);
			pm_runसमय_put_sync(dev);
			वापस ret;
		पूर्ण

		csid->ops->hw_version(csid);
	पूर्ण अन्यथा अणु
		disable_irq(csid->irq);
		camss_disable_घड़ीs(csid->nघड़ीs, csid->घड़ी);
		ret = regulator_disable(csid->vdda);
		pm_runसमय_put_sync(dev);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * csid_set_stream - Enable/disable streaming on CSID module
 * @sd: CSID V4L2 subdevice
 * @enable: Requested streaming state
 *
 * Main configuration of CSID module is also करोne here.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csid_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा csid_device *csid = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	अगर (enable) अणु
		ret = v4l2_ctrl_handler_setup(&csid->ctrls);
		अगर (ret < 0) अणु
			dev_err(csid->camss->dev,
				"could not sync v4l2 controls: %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (!csid->testgen.enabled &&
		    !media_entity_remote_pad(&csid->pads[MSM_CSID_PAD_SINK]))
			वापस -ENOLINK;
	पूर्ण

	csid->ops->configure_stream(csid, enable);

	वापस 0;
पूर्ण

/*
 * __csid_get_क्रमmat - Get poपूर्णांकer to क्रमmat काष्ठाure
 * @csid: CSID device
 * @cfg: V4L2 subdev pad configuration
 * @pad: pad from which क्रमmat is requested
 * @which: TRY or ACTIVE क्रमmat
 *
 * Return poपूर्णांकer to TRY or ACTIVE क्रमmat काष्ठाure
 */
अटल काष्ठा v4l2_mbus_framefmt *
__csid_get_क्रमmat(काष्ठा csid_device *csid,
		  काष्ठा v4l2_subdev_pad_config *cfg,
		  अचिन्हित पूर्णांक pad,
		  क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&csid->subdev, cfg, pad);

	वापस &csid->fmt[pad];
पूर्ण

/*
 * csid_try_क्रमmat - Handle try क्रमmat by pad subdev method
 * @csid: CSID device
 * @cfg: V4L2 subdev pad configuration
 * @pad: pad on which क्रमmat is requested
 * @fmt: poपूर्णांकer to v4l2 क्रमmat काष्ठाure
 * @which: wanted subdev क्रमmat
 */
अटल व्योम csid_try_क्रमmat(काष्ठा csid_device *csid,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    अचिन्हित पूर्णांक pad,
			    काष्ठा v4l2_mbus_framefmt *fmt,
			    क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अचिन्हित पूर्णांक i;

	चयन (pad) अणु
	हाल MSM_CSID_PAD_SINK:
		/* Set क्रमmat on sink pad */

		क्रम (i = 0; i < csid->nक्रमmats; i++)
			अगर (fmt->code == csid->क्रमmats[i].code)
				अवरोध;

		/* If not found, use UYVY as शेष */
		अगर (i >= csid->nक्रमmats)
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

		fmt->width = clamp_t(u32, fmt->width, 1, 8191);
		fmt->height = clamp_t(u32, fmt->height, 1, 8191);

		fmt->field = V4L2_FIELD_NONE;
		fmt->colorspace = V4L2_COLORSPACE_SRGB;

		अवरोध;

	हाल MSM_CSID_PAD_SRC:
		अगर (csid->testgen_mode->cur.val == 0) अणु
			/* Test generator is disabled, */
			/* keep pad क्रमmats in sync */
			u32 code = fmt->code;

			*fmt = *__csid_get_क्रमmat(csid, cfg,
						      MSM_CSID_PAD_SINK, which);
			fmt->code = csid->ops->src_pad_code(csid, fmt->code, 0, code);
		पूर्ण अन्यथा अणु
			/* Test generator is enabled, set क्रमmat on source */
			/* pad to allow test generator usage */

			क्रम (i = 0; i < csid->nक्रमmats; i++)
				अगर (csid->क्रमmats[i].code == fmt->code)
					अवरोध;

			/* If not found, use UYVY as शेष */
			अगर (i >= csid->nक्रमmats)
				fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

			fmt->width = clamp_t(u32, fmt->width, 1, 8191);
			fmt->height = clamp_t(u32, fmt->height, 1, 8191);

			fmt->field = V4L2_FIELD_NONE;
		पूर्ण
		अवरोध;
	पूर्ण

	fmt->colorspace = V4L2_COLORSPACE_SRGB;
पूर्ण

/*
 * csid_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd: CSID V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @code: poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csid_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा csid_device *csid = v4l2_get_subdevdata(sd);

	अगर (code->pad == MSM_CSID_PAD_SINK) अणु
		अगर (code->index >= csid->nक्रमmats)
			वापस -EINVAL;

		code->code = csid->क्रमmats[code->index].code;
	पूर्ण अन्यथा अणु
		अगर (csid->testgen_mode->cur.val == 0) अणु
			काष्ठा v4l2_mbus_framefmt *sink_fmt;

			sink_fmt = __csid_get_क्रमmat(csid, cfg,
						     MSM_CSID_PAD_SINK,
						     code->which);

			code->code = csid->ops->src_pad_code(csid, sink_fmt->code,
						       code->index, 0);
			अगर (!code->code)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (code->index >= csid->nक्रमmats)
				वापस -EINVAL;

			code->code = csid->क्रमmats[code->index].code;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csid_क्रमागत_frame_size - Handle frame size क्रमागतeration
 * @sd: CSID V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fse: poपूर्णांकer to v4l2_subdev_frame_size_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csid_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा csid_device *csid = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	csid_try_क्रमmat(csid, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	csid_try_क्रमmat(csid, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * csid_get_क्रमmat - Handle get क्रमmat by pads subdev method
 * @sd: CSID V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक csid_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा csid_device *csid = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __csid_get_क्रमmat(csid, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;

	वापस 0;
पूर्ण

/*
 * csid_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd: CSID V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक csid_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा csid_device *csid = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __csid_get_क्रमmat(csid, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	csid_try_क्रमmat(csid, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == MSM_CSID_PAD_SINK) अणु
		क्रमmat = __csid_get_क्रमmat(csid, cfg, MSM_CSID_PAD_SRC,
					   fmt->which);

		*क्रमmat = fmt->क्रमmat;
		csid_try_क्रमmat(csid, cfg, MSM_CSID_PAD_SRC, क्रमmat,
				fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csid_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: CSID V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csid_init_क्रमmats(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.pad = MSM_CSID_PAD_SINK,
		.which = fh ? V4L2_SUBDEV_FORMAT_TRY :
			      V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat = अणु
			.code = MEDIA_BUS_FMT_UYVY8_2X8,
			.width = 1920,
			.height = 1080
		पूर्ण
	पूर्ण;

	वापस csid_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);
पूर्ण

/*
 * csid_set_test_pattern - Set test generator's pattern mode
 * @csid: CSID device
 * @value: desired test pattern mode
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csid_set_test_pattern(काष्ठा csid_device *csid, s32 value)
अणु
	काष्ठा csid_testgen_config *tg = &csid->testgen;

	/* If CSID is linked to CSIPHY, करो not allow to enable test generator */
	अगर (value && media_entity_remote_pad(&csid->pads[MSM_CSID_PAD_SINK]))
		वापस -EBUSY;

	tg->enabled = !!value;

	वापस csid->ops->configure_testgen_pattern(csid, value);
पूर्ण

/*
 * csid_s_ctrl - Handle set control subdev method
 * @ctrl: poपूर्णांकer to v4l2 control काष्ठाure
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csid_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा csid_device *csid = container_of(ctrl->handler,
						काष्ठा csid_device, ctrls);
	पूर्णांक ret = -EINVAL;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_TEST_PATTERN:
		ret = csid_set_test_pattern(csid, ctrl->val);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops csid_ctrl_ops = अणु
	.s_ctrl = csid_s_ctrl,
पूर्ण;

/*
 * msm_csid_subdev_init - Initialize CSID device काष्ठाure and resources
 * @csid: CSID device
 * @res: CSID module resources table
 * @id: CSID module id
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक msm_csid_subdev_init(काष्ठा camss *camss, काष्ठा csid_device *csid,
			 स्थिर काष्ठा resources *res, u8 id)
अणु
	काष्ठा device *dev = camss->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *r;
	पूर्णांक i, j;
	पूर्णांक ret;

	csid->camss = camss;
	csid->id = id;

	अगर (camss->version == CAMSS_8x16) अणु
		csid->ops = &csid_ops_4_1;
	पूर्ण अन्यथा अगर (camss->version == CAMSS_8x96 ||
		   camss->version == CAMSS_660) अणु
		csid->ops = &csid_ops_4_7;
	पूर्ण अन्यथा अगर (camss->version == CAMSS_845) अणु
		csid->ops = &csid_ops_170;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	csid->ops->subdev_init(csid);

	/* Memory */

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, res->reg[0]);
	csid->base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(csid->base))
		वापस PTR_ERR(csid->base);

	/* Interrupt */

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ,
					 res->पूर्णांकerrupt[0]);
	अगर (!r) अणु
		dev_err(dev, "missing IRQ\n");
		वापस -EINVAL;
	पूर्ण

	csid->irq = r->start;
	snम_लिखो(csid->irq_name, माप(csid->irq_name), "%s_%s%d",
		 dev_name(dev), MSM_CSID_NAME, csid->id);
	ret = devm_request_irq(dev, csid->irq, csid->ops->isr,
			       IRQF_TRIGGER_RISING, csid->irq_name, csid);
	अगर (ret < 0) अणु
		dev_err(dev, "request_irq failed: %d\n", ret);
		वापस ret;
	पूर्ण

	disable_irq(csid->irq);

	/* Clocks */

	csid->nघड़ीs = 0;
	जबतक (res->घड़ी[csid->nघड़ीs])
		csid->nघड़ीs++;

	csid->घड़ी = devm_kसुस्मृति(dev, csid->nघड़ीs, माप(*csid->घड़ी),
				    GFP_KERNEL);
	अगर (!csid->घड़ी)
		वापस -ENOMEM;

	क्रम (i = 0; i < csid->nघड़ीs; i++) अणु
		काष्ठा camss_घड़ी *घड़ी = &csid->घड़ी[i];

		घड़ी->clk = devm_clk_get(dev, res->घड़ी[i]);
		अगर (IS_ERR(घड़ी->clk))
			वापस PTR_ERR(घड़ी->clk);

		घड़ी->name = res->घड़ी[i];

		घड़ी->nfreqs = 0;
		जबतक (res->घड़ी_rate[i][घड़ी->nfreqs])
			घड़ी->nfreqs++;

		अगर (!घड़ी->nfreqs) अणु
			घड़ी->freq = शून्य;
			जारी;
		पूर्ण

		घड़ी->freq = devm_kसुस्मृति(dev,
					   घड़ी->nfreqs,
					   माप(*घड़ी->freq),
					   GFP_KERNEL);
		अगर (!घड़ी->freq)
			वापस -ENOMEM;

		क्रम (j = 0; j < घड़ी->nfreqs; j++)
			घड़ी->freq[j] = res->घड़ी_rate[i][j];
	पूर्ण

	/* Regulator */

	csid->vdda = devm_regulator_get(dev, res->regulator[0]);
	अगर (IS_ERR(csid->vdda)) अणु
		dev_err(dev, "could not get regulator\n");
		वापस PTR_ERR(csid->vdda);
	पूर्ण

	init_completion(&csid->reset_complete);

	वापस 0;
पूर्ण

/*
 * msm_csid_get_csid_id - Get CSID HW module id
 * @entity: Poपूर्णांकer to CSID media entity काष्ठाure
 * @id: Return CSID HW module id here
 */
व्योम msm_csid_get_csid_id(काष्ठा media_entity *entity, u8 *id)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा csid_device *csid = v4l2_get_subdevdata(sd);

	*id = csid->id;
पूर्ण

/*
 * csid_get_lane_assign - Calculate CSI2 lane assign configuration parameter
 * @lane_cfg - CSI2 lane configuration
 *
 * Return lane assign
 */
अटल u32 csid_get_lane_assign(काष्ठा csiphy_lanes_cfg *lane_cfg)
अणु
	u32 lane_assign = 0;
	पूर्णांक i;

	क्रम (i = 0; i < lane_cfg->num_data; i++)
		lane_assign |= lane_cfg->data[i].pos << (i * 4);

	वापस lane_assign;
पूर्ण

/*
 * csid_link_setup - Setup CSID connections
 * @entity: Poपूर्णांकer to media entity काष्ठाure
 * @local: Poपूर्णांकer to local pad
 * @remote: Poपूर्णांकer to remote pad
 * @flags: Link flags
 *
 * Return 0 on success
 */
अटल पूर्णांक csid_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	अगर (flags & MEDIA_LNK_FL_ENABLED)
		अगर (media_entity_remote_pad(local))
			वापस -EBUSY;

	अगर ((local->flags & MEDIA_PAD_FL_SINK) &&
	    (flags & MEDIA_LNK_FL_ENABLED)) अणु
		काष्ठा v4l2_subdev *sd;
		काष्ठा csid_device *csid;
		काष्ठा csiphy_device *csiphy;
		काष्ठा csiphy_lanes_cfg *lane_cfg;
		काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु 0 पूर्ण;

		sd = media_entity_to_v4l2_subdev(entity);
		csid = v4l2_get_subdevdata(sd);

		/* If test generator is enabled */
		/* करो not allow a link from CSIPHY to CSID */
		अगर (csid->testgen_mode->cur.val != 0)
			वापस -EBUSY;

		sd = media_entity_to_v4l2_subdev(remote->entity);
		csiphy = v4l2_get_subdevdata(sd);

		/* If a sensor is not linked to CSIPHY */
		/* करो no allow a link from CSIPHY to CSID */
		अगर (!csiphy->cfg.csi2)
			वापस -EPERM;

		csid->phy.csiphy_id = csiphy->id;

		lane_cfg = &csiphy->cfg.csi2->lane_cfg;
		csid->phy.lane_cnt = lane_cfg->num_data;
		csid->phy.lane_assign = csid_get_lane_assign(lane_cfg);

		/* Reset क्रमmat on source pad to sink pad क्रमmat */
		क्रमmat.pad = MSM_CSID_PAD_SRC;
		क्रमmat.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		csid_set_क्रमmat(&csid->subdev, शून्य, &क्रमmat);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops csid_core_ops = अणु
	.s_घातer = csid_set_घातer,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops csid_video_ops = अणु
	.s_stream = csid_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops csid_pad_ops = अणु
	.क्रमागत_mbus_code = csid_क्रमागत_mbus_code,
	.क्रमागत_frame_size = csid_क्रमागत_frame_size,
	.get_fmt = csid_get_क्रमmat,
	.set_fmt = csid_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops csid_v4l2_ops = अणु
	.core = &csid_core_ops,
	.video = &csid_video_ops,
	.pad = &csid_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops csid_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = csid_init_क्रमmats,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations csid_media_ops = अणु
	.link_setup = csid_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
 * msm_csid_रेजिस्टर_entity - Register subdev node क्रम CSID module
 * @csid: CSID device
 * @v4l2_dev: V4L2 device
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक msm_csid_रेजिस्टर_entity(काष्ठा csid_device *csid,
			     काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा v4l2_subdev *sd = &csid->subdev;
	काष्ठा media_pad *pads = csid->pads;
	काष्ठा device *dev = csid->camss->dev;
	पूर्णांक ret;

	v4l2_subdev_init(sd, &csid_v4l2_ops);
	sd->पूर्णांकernal_ops = &csid_v4l2_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
		     V4L2_SUBDEV_FL_HAS_EVENTS;
	snम_लिखो(sd->name, ARRAY_SIZE(sd->name), "%s%d",
		 MSM_CSID_NAME, csid->id);
	v4l2_set_subdevdata(sd, csid);

	ret = v4l2_ctrl_handler_init(&csid->ctrls, 1);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to init ctrl handler: %d\n", ret);
		वापस ret;
	पूर्ण

	csid->testgen_mode = v4l2_ctrl_new_std_menu_items(&csid->ctrls,
				&csid_ctrl_ops, V4L2_CID_TEST_PATTERN,
				csid->testgen.nmodes, 0, 0,
				csid->testgen.modes);

	अगर (csid->ctrls.error) अणु
		dev_err(dev, "Failed to init ctrl: %d\n", csid->ctrls.error);
		ret = csid->ctrls.error;
		जाओ मुक्त_ctrl;
	पूर्ण

	csid->subdev.ctrl_handler = &csid->ctrls;

	ret = csid_init_क्रमmats(sd, शून्य);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to init format: %d\n", ret);
		जाओ मुक्त_ctrl;
	पूर्ण

	pads[MSM_CSID_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[MSM_CSID_PAD_SRC].flags = MEDIA_PAD_FL_SOURCE;

	sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	sd->entity.ops = &csid_media_ops;
	ret = media_entity_pads_init(&sd->entity, MSM_CSID_PADS_NUM, pads);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to init media entity: %d\n", ret);
		जाओ मुक्त_ctrl;
	पूर्ण

	ret = v4l2_device_रेजिस्टर_subdev(v4l2_dev, sd);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register subdev: %d\n", ret);
		जाओ media_cleanup;
	पूर्ण

	वापस 0;

media_cleanup:
	media_entity_cleanup(&sd->entity);
मुक्त_ctrl:
	v4l2_ctrl_handler_मुक्त(&csid->ctrls);

	वापस ret;
पूर्ण

/*
 * msm_csid_unरेजिस्टर_entity - Unरेजिस्टर CSID module subdev node
 * @csid: CSID device
 */
व्योम msm_csid_unरेजिस्टर_entity(काष्ठा csid_device *csid)
अणु
	v4l2_device_unरेजिस्टर_subdev(&csid->subdev);
	media_entity_cleanup(&csid->subdev.entity);
	v4l2_ctrl_handler_मुक्त(&csid->ctrls);
पूर्ण
