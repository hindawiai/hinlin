<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI OMAP4 ISS V4L2 Driver - ISP IPIPE module
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>

#समावेश "iss.h"
#समावेश "iss_regs.h"
#समावेश "iss_ipipe.h"

अटल काष्ठा v4l2_mbus_framefmt *
__ipipe_get_क्रमmat(काष्ठा iss_ipipe_device *ipipe,
		   काष्ठा v4l2_subdev_pad_config *cfg,
		   अचिन्हित पूर्णांक pad,
		   क्रमागत v4l2_subdev_क्रमmat_whence which);

अटल स्थिर अचिन्हित पूर्णांक ipipe_fmts[] = अणु
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SRGGB10_1X10,
	MEDIA_BUS_FMT_SBGGR10_1X10,
	MEDIA_BUS_FMT_SGBRG10_1X10,
पूर्ण;

/*
 * ipipe_prपूर्णांक_status - Prपूर्णांक current IPIPE Module रेजिस्टर values.
 * @ipipe: Poपूर्णांकer to ISS ISP IPIPE device.
 *
 * Also prपूर्णांकs other debug inक्रमmation stored in the IPIPE module.
 */
#घोषणा IPIPE_PRINT_REGISTER(iss, name)\
	dev_dbg(iss->dev, "###IPIPE " #name "=0x%08x\n", \
		iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_##name))

अटल व्योम ipipe_prपूर्णांक_status(काष्ठा iss_ipipe_device *ipipe)
अणु
	काष्ठा iss_device *iss = to_iss_device(ipipe);

	dev_dbg(iss->dev, "-------------IPIPE Register dump-------------\n");

	IPIPE_PRINT_REGISTER(iss, SRC_EN);
	IPIPE_PRINT_REGISTER(iss, SRC_MODE);
	IPIPE_PRINT_REGISTER(iss, SRC_FMT);
	IPIPE_PRINT_REGISTER(iss, SRC_COL);
	IPIPE_PRINT_REGISTER(iss, SRC_VPS);
	IPIPE_PRINT_REGISTER(iss, SRC_VSZ);
	IPIPE_PRINT_REGISTER(iss, SRC_HPS);
	IPIPE_PRINT_REGISTER(iss, SRC_HSZ);
	IPIPE_PRINT_REGISTER(iss, GCK_MMR);
	IPIPE_PRINT_REGISTER(iss, YUV_PHS);

	dev_dbg(iss->dev, "-----------------------------------------------\n");
पूर्ण

/*
 * ipipe_enable - Enable/Disable IPIPE.
 * @enable: enable flag
 *
 */
अटल व्योम ipipe_enable(काष्ठा iss_ipipe_device *ipipe, u8 enable)
अणु
	काष्ठा iss_device *iss = to_iss_device(ipipe);

	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_SRC_EN,
		       IPIPE_SRC_EN_EN, enable ? IPIPE_SRC_EN_EN : 0);
पूर्ण

/* -----------------------------------------------------------------------------
 * Format- and pipeline-related configuration helpers
 */

अटल व्योम ipipe_configure(काष्ठा iss_ipipe_device *ipipe)
अणु
	काष्ठा iss_device *iss = to_iss_device(ipipe);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	/* IPIPE_PAD_SINK */
	क्रमmat = &ipipe->क्रमmats[IPIPE_PAD_SINK];

	/* NOTE: Currently just supporting pipeline IN: RGB, OUT: YUV422 */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_SRC_FMT,
		      IPIPE_SRC_FMT_RAW2YUV);

	/* Enable YUV444 -> YUV422 conversion */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_YUV_PHS,
		      IPIPE_YUV_PHS_LPF);

	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_SRC_VPS, 0);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_SRC_HPS, 0);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_SRC_VSZ,
		      (क्रमmat->height - 2) & IPIPE_SRC_VSZ_MASK);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_SRC_HSZ,
		      (क्रमmat->width - 1) & IPIPE_SRC_HSZ_MASK);

	/* Ignore ipipeअगर_wrt संकेत, and operate on-the-fly.  */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_SRC_MODE,
		    IPIPE_SRC_MODE_WRT | IPIPE_SRC_MODE_OST);

	/* HACK: Values tuned क्रम Ducati SW (OV) */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_SRC_COL,
		      IPIPE_SRC_COL_EE_B | IPIPE_SRC_COL_EO_GB |
		      IPIPE_SRC_COL_OE_GR | IPIPE_SRC_COL_OO_R);

	/* IPIPE_PAD_SOURCE_VP */
	क्रमmat = &ipipe->क्रमmats[IPIPE_PAD_SOURCE_VP];
	/* Do nothing? */
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 */

/*
 * ipipe_set_stream - Enable/Disable streaming on the IPIPE module
 * @sd: ISP IPIPE V4L2 subdevice
 * @enable: Enable/disable stream
 */
अटल पूर्णांक ipipe_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा iss_ipipe_device *ipipe = v4l2_get_subdevdata(sd);
	काष्ठा iss_device *iss = to_iss_device(ipipe);
	पूर्णांक ret = 0;

	अगर (ipipe->state == ISS_PIPELINE_STREAM_STOPPED) अणु
		अगर (enable == ISS_PIPELINE_STREAM_STOPPED)
			वापस 0;

		omap4iss_isp_subclk_enable(iss, OMAP4_ISS_ISP_SUBCLK_IPIPE);

		/* Enable clk_arm_g0 */
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_GCK_MMR,
			      IPIPE_GCK_MMR_REG);

		/* Enable clk_pix_g[3:0] */
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_GCK_PIX,
			      IPIPE_GCK_PIX_G3 | IPIPE_GCK_PIX_G2 |
			      IPIPE_GCK_PIX_G1 | IPIPE_GCK_PIX_G0);
	पूर्ण

	चयन (enable) अणु
	हाल ISS_PIPELINE_STREAM_CONTINUOUS:

		ipipe_configure(ipipe);
		ipipe_prपूर्णांक_status(ipipe);

		atomic_set(&ipipe->stopping, 0);
		ipipe_enable(ipipe, 1);
		अवरोध;

	हाल ISS_PIPELINE_STREAM_STOPPED:
		अगर (ipipe->state == ISS_PIPELINE_STREAM_STOPPED)
			वापस 0;
		अगर (omap4iss_module_sync_idle(&sd->entity, &ipipe->रुको,
					      &ipipe->stopping))
			ret = -ETIMEDOUT;

		ipipe_enable(ipipe, 0);
		omap4iss_isp_subclk_disable(iss, OMAP4_ISS_ISP_SUBCLK_IPIPE);
		अवरोध;
	पूर्ण

	ipipe->state = enable;
	वापस ret;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__ipipe_get_क्रमmat(काष्ठा iss_ipipe_device *ipipe,
		   काष्ठा v4l2_subdev_pad_config *cfg,
		   अचिन्हित पूर्णांक pad,
		   क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&ipipe->subdev, cfg, pad);

	वापस &ipipe->क्रमmats[pad];
पूर्ण

/*
 * ipipe_try_क्रमmat - Try video क्रमmat on a pad
 * @ipipe: ISS IPIPE device
 * @cfg: V4L2 subdev pad config
 * @pad: Pad number
 * @fmt: Format
 */
अटल व्योम
ipipe_try_क्रमmat(काष्ठा iss_ipipe_device *ipipe,
		 काष्ठा v4l2_subdev_pad_config *cfg,
		 अचिन्हित पूर्णांक pad,
		 काष्ठा v4l2_mbus_framefmt *fmt,
		 क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक width = fmt->width;
	अचिन्हित पूर्णांक height = fmt->height;
	अचिन्हित पूर्णांक i;

	चयन (pad) अणु
	हाल IPIPE_PAD_SINK:
		क्रम (i = 0; i < ARRAY_SIZE(ipipe_fmts); i++) अणु
			अगर (fmt->code == ipipe_fmts[i])
				अवरोध;
		पूर्ण

		/* If not found, use SGRBG10 as शेष */
		अगर (i >= ARRAY_SIZE(ipipe_fmts))
			fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

		/* Clamp the input size. */
		fmt->width = clamp_t(u32, width, 1, 8192);
		fmt->height = clamp_t(u32, height, 1, 8192);
		fmt->colorspace = V4L2_COLORSPACE_SRGB;
		अवरोध;

	हाल IPIPE_PAD_SOURCE_VP:
		क्रमmat = __ipipe_get_क्रमmat(ipipe, cfg, IPIPE_PAD_SINK, which);
		स_नकल(fmt, क्रमmat, माप(*fmt));

		fmt->code = MEDIA_BUS_FMT_UYVY8_1X16;
		fmt->width = clamp_t(u32, width, 32, fmt->width);
		fmt->height = clamp_t(u32, height, 32, fmt->height);
		fmt->colorspace = V4L2_COLORSPACE_JPEG;
		अवरोध;
	पूर्ण

	fmt->field = V4L2_FIELD_NONE;
पूर्ण

/*
 * ipipe_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd     : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg    : V4L2 subdev pad config
 * @code   : poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ipipe_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	चयन (code->pad) अणु
	हाल IPIPE_PAD_SINK:
		अगर (code->index >= ARRAY_SIZE(ipipe_fmts))
			वापस -EINVAL;

		code->code = ipipe_fmts[code->index];
		अवरोध;

	हाल IPIPE_PAD_SOURCE_VP:
		/* FIXME: Forced क्रमmat conversion inside IPIPE ? */
		अगर (code->index != 0)
			वापस -EINVAL;

		code->code = MEDIA_BUS_FMT_UYVY8_1X16;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipipe_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा iss_ipipe_device *ipipe = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	ipipe_try_क्रमmat(ipipe, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	ipipe_try_क्रमmat(ipipe, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * ipipe_get_क्रमmat - Retrieve the video क्रमmat on a pad
 * @sd : ISP IPIPE V4L2 subdevice
 * @cfg: V4L2 subdev pad config
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक ipipe_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा iss_ipipe_device *ipipe = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __ipipe_get_क्रमmat(ipipe, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;
	वापस 0;
पूर्ण

/*
 * ipipe_set_क्रमmat - Set the video क्रमmat on a pad
 * @sd : ISP IPIPE V4L2 subdevice
 * @cfg: V4L2 subdev pad config
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक ipipe_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा iss_ipipe_device *ipipe = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __ipipe_get_क्रमmat(ipipe, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	ipipe_try_क्रमmat(ipipe, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == IPIPE_PAD_SINK) अणु
		क्रमmat = __ipipe_get_क्रमmat(ipipe, cfg, IPIPE_PAD_SOURCE_VP,
					    fmt->which);
		*क्रमmat = fmt->क्रमmat;
		ipipe_try_क्रमmat(ipipe, cfg, IPIPE_PAD_SOURCE_VP, क्रमmat,
				 fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipipe_link_validate(काष्ठा v4l2_subdev *sd, काष्ठा media_link *link,
			       काष्ठा v4l2_subdev_क्रमmat *source_fmt,
			       काष्ठा v4l2_subdev_क्रमmat *sink_fmt)
अणु
	/* Check अगर the two ends match */
	अगर (source_fmt->क्रमmat.width != sink_fmt->क्रमmat.width ||
	    source_fmt->क्रमmat.height != sink_fmt->क्रमmat.height)
		वापस -EPIPE;

	अगर (source_fmt->क्रमmat.code != sink_fmt->क्रमmat.code)
		वापस -EPIPE;

	वापस 0;
पूर्ण

/*
 * ipipe_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISP IPIPE V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values. If fh is not शून्य, try
 * क्रमmats are initialized on the file handle. Otherwise active क्रमmats are
 * initialized on the device.
 */
अटल पूर्णांक ipipe_init_क्रमmats(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.pad = IPIPE_PAD_SINK;
	क्रमmat.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	क्रमmat.क्रमmat.width = 4096;
	क्रमmat.क्रमmat.height = 4096;
	ipipe_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);

	वापस 0;
पूर्ण

/* V4L2 subdev video operations */
अटल स्थिर काष्ठा v4l2_subdev_video_ops ipipe_v4l2_video_ops = अणु
	.s_stream = ipipe_set_stream,
पूर्ण;

/* V4L2 subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops ipipe_v4l2_pad_ops = अणु
	.क्रमागत_mbus_code = ipipe_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ipipe_क्रमागत_frame_size,
	.get_fmt = ipipe_get_क्रमmat,
	.set_fmt = ipipe_set_क्रमmat,
	.link_validate = ipipe_link_validate,
पूर्ण;

/* V4L2 subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops ipipe_v4l2_ops = अणु
	.video = &ipipe_v4l2_video_ops,
	.pad = &ipipe_v4l2_pad_ops,
पूर्ण;

/* V4L2 subdev पूर्णांकernal operations */
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ipipe_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = ipipe_init_क्रमmats,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media entity operations
 */

/*
 * ipipe_link_setup - Setup IPIPE connections
 * @entity: IPIPE media entity
 * @local: Pad at the local end of the link
 * @remote: Pad at the remote end of the link
 * @flags: Link flags
 *
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ipipe_link_setup(काष्ठा media_entity *entity,
			    स्थिर काष्ठा media_pad *local,
			    स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा iss_ipipe_device *ipipe = v4l2_get_subdevdata(sd);
	काष्ठा iss_device *iss = to_iss_device(ipipe);

	अगर (!is_media_entity_v4l2_subdev(remote->entity))
		वापस -EINVAL;

	चयन (local->index) अणु
	हाल IPIPE_PAD_SINK:
		/* Read from IPIPEIF. */
		अगर (!(flags & MEDIA_LNK_FL_ENABLED)) अणु
			ipipe->input = IPIPE_INPUT_NONE;
			अवरोध;
		पूर्ण

		अगर (ipipe->input != IPIPE_INPUT_NONE)
			वापस -EBUSY;

		अगर (remote->entity == &iss->ipipeअगर.subdev.entity)
			ipipe->input = IPIPE_INPUT_IPIPEIF;

		अवरोध;

	हाल IPIPE_PAD_SOURCE_VP:
		/* Send to RESIZER */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (ipipe->output & ~IPIPE_OUTPUT_VP)
				वापस -EBUSY;
			ipipe->output |= IPIPE_OUTPUT_VP;
		पूर्ण अन्यथा अणु
			ipipe->output &= ~IPIPE_OUTPUT_VP;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations ipipe_media_ops = अणु
	.link_setup = ipipe_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
 * ipipe_init_entities - Initialize V4L2 subdev and media entity
 * @ipipe: ISS ISP IPIPE module
 *
 * Return 0 on success and a negative error code on failure.
 */
अटल पूर्णांक ipipe_init_entities(काष्ठा iss_ipipe_device *ipipe)
अणु
	काष्ठा v4l2_subdev *sd = &ipipe->subdev;
	काष्ठा media_pad *pads = ipipe->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	ipipe->input = IPIPE_INPUT_NONE;

	v4l2_subdev_init(sd, &ipipe_v4l2_ops);
	sd->पूर्णांकernal_ops = &ipipe_v4l2_पूर्णांकernal_ops;
	strscpy(sd->name, "OMAP4 ISS ISP IPIPE", माप(sd->name));
	sd->grp_id = BIT(16);	/* group ID क्रम iss subdevs */
	v4l2_set_subdevdata(sd, ipipe);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[IPIPE_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[IPIPE_PAD_SOURCE_VP].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &ipipe_media_ops;
	ret = media_entity_pads_init(me, IPIPE_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	ipipe_init_क्रमmats(sd, शून्य);

	वापस 0;
पूर्ण

व्योम omap4iss_ipipe_unरेजिस्टर_entities(काष्ठा iss_ipipe_device *ipipe)
अणु
	v4l2_device_unरेजिस्टर_subdev(&ipipe->subdev);
पूर्ण

पूर्णांक omap4iss_ipipe_रेजिस्टर_entities(काष्ठा iss_ipipe_device *ipipe,
				     काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video node. */
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &ipipe->subdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	omap4iss_ipipe_unरेजिस्टर_entities(ipipe);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP IPIPE initialisation and cleanup
 */

/*
 * omap4iss_ipipe_init - IPIPE module initialization.
 * @iss: Device poपूर्णांकer specअगरic to the OMAP4 ISS.
 *
 * TODO: Get the initialisation values from platक्रमm data.
 *
 * Return 0 on success or a negative error code otherwise.
 */
पूर्णांक omap4iss_ipipe_init(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_ipipe_device *ipipe = &iss->ipipe;

	ipipe->state = ISS_PIPELINE_STREAM_STOPPED;
	init_रुकोqueue_head(&ipipe->रुको);

	वापस ipipe_init_entities(ipipe);
पूर्ण

/*
 * omap4iss_ipipe_cleanup - IPIPE module cleanup.
 * @iss: Device poपूर्णांकer specअगरic to the OMAP4 ISS.
 */
व्योम omap4iss_ipipe_cleanup(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_ipipe_device *ipipe = &iss->ipipe;

	media_entity_cleanup(&ipipe->subdev.entity);
पूर्ण
