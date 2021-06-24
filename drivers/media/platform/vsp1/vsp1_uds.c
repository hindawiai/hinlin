<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_uds.c  --  R-Car VSP1 Up and Down Scaler
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>

#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_pipe.h"
#समावेश "vsp1_uds.h"

#घोषणा UDS_MIN_SIZE				4U
#घोषणा UDS_MAX_SIZE				8190U

#घोषणा UDS_MIN_FACTOR				0x0100
#घोषणा UDS_MAX_FACTOR				0xffff

/* -----------------------------------------------------------------------------
 * Device Access
 */

अटल अंतरभूत व्योम vsp1_uds_ग_लिखो(काष्ठा vsp1_uds *uds,
				  काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	vsp1_dl_body_ग_लिखो(dlb, reg + uds->entity.index * VI6_UDS_OFFSET, data);
पूर्ण

/* -----------------------------------------------------------------------------
 * Scaling Computation
 */

व्योम vsp1_uds_set_alpha(काष्ठा vsp1_entity *entity, काष्ठा vsp1_dl_body *dlb,
			अचिन्हित पूर्णांक alpha)
अणु
	काष्ठा vsp1_uds *uds = to_uds(&entity->subdev);

	vsp1_uds_ग_लिखो(uds, dlb, VI6_UDS_ALPVAL,
		       alpha << VI6_UDS_ALPVAL_VAL0_SHIFT);
पूर्ण

/*
 * uds_output_size - Return the output size क्रम an input size and scaling ratio
 * @input: input size in pixels
 * @ratio: scaling ratio in U4.12 fixed-poपूर्णांक क्रमmat
 */
अटल अचिन्हित पूर्णांक uds_output_size(अचिन्हित पूर्णांक input, अचिन्हित पूर्णांक ratio)
अणु
	अगर (ratio > 4096) अणु
		/* Down-scaling */
		अचिन्हित पूर्णांक mp;

		mp = ratio / 4096;
		mp = mp < 4 ? 1 : (mp < 8 ? 2 : 4);

		वापस (input - 1) / mp * mp * 4096 / ratio + 1;
	पूर्ण अन्यथा अणु
		/* Up-scaling */
		वापस (input - 1) * 4096 / ratio + 1;
	पूर्ण
पूर्ण

/*
 * uds_output_limits - Return the min and max output sizes क्रम an input size
 * @input: input size in pixels
 * @minimum: minimum output size (वापसed)
 * @maximum: maximum output size (वापसed)
 */
अटल व्योम uds_output_limits(अचिन्हित पूर्णांक input,
			      अचिन्हित पूर्णांक *minimum, अचिन्हित पूर्णांक *maximum)
अणु
	*minimum = max(uds_output_size(input, UDS_MAX_FACTOR), UDS_MIN_SIZE);
	*maximum = min(uds_output_size(input, UDS_MIN_FACTOR), UDS_MAX_SIZE);
पूर्ण

/*
 * uds_passband_width - Return the passband filter width क्रम a scaling ratio
 * @ratio: scaling ratio in U4.12 fixed-poपूर्णांक क्रमmat
 */
अटल अचिन्हित पूर्णांक uds_passband_width(अचिन्हित पूर्णांक ratio)
अणु
	अगर (ratio >= 4096) अणु
		/* Down-scaling */
		अचिन्हित पूर्णांक mp;

		mp = ratio / 4096;
		mp = mp < 4 ? 1 : (mp < 8 ? 2 : 4);

		वापस 64 * 4096 * mp / ratio;
	पूर्ण अन्यथा अणु
		/* Up-scaling */
		वापस 64;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक uds_compute_ratio(अचिन्हित पूर्णांक input, अचिन्हित पूर्णांक output)
अणु
	/* TODO: This is an approximation that will need to be refined. */
	वापस (input - 1) * 4096 / (output - 1);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Pad Operations
 */

अटल पूर्णांक uds_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अटल स्थिर अचिन्हित पूर्णांक codes[] = अणु
		MEDIA_BUS_FMT_ARGB8888_1X32,
		MEDIA_BUS_FMT_AYUV8_1X32,
	पूर्ण;

	वापस vsp1_subdev_क्रमागत_mbus_code(subdev, cfg, code, codes,
					  ARRAY_SIZE(codes));
पूर्ण

अटल पूर्णांक uds_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा vsp1_uds *uds = to_uds(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	config = vsp1_entity_get_pad_config(&uds->entity, cfg, fse->which);
	अगर (!config)
		वापस -EINVAL;

	क्रमmat = vsp1_entity_get_pad_क्रमmat(&uds->entity, config,
					    UDS_PAD_SINK);

	mutex_lock(&uds->entity.lock);

	अगर (fse->index || fse->code != क्रमmat->code) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (fse->pad == UDS_PAD_SINK) अणु
		fse->min_width = UDS_MIN_SIZE;
		fse->max_width = UDS_MAX_SIZE;
		fse->min_height = UDS_MIN_SIZE;
		fse->max_height = UDS_MAX_SIZE;
	पूर्ण अन्यथा अणु
		uds_output_limits(क्रमmat->width, &fse->min_width,
				  &fse->max_width);
		uds_output_limits(क्रमmat->height, &fse->min_height,
				  &fse->max_height);
	पूर्ण

करोne:
	mutex_unlock(&uds->entity.lock);
	वापस ret;
पूर्ण

अटल व्योम uds_try_क्रमmat(काष्ठा vsp1_uds *uds,
			   काष्ठा v4l2_subdev_pad_config *config,
			   अचिन्हित पूर्णांक pad, काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक minimum;
	अचिन्हित पूर्णांक maximum;

	चयन (pad) अणु
	हाल UDS_PAD_SINK:
		/* Default to YUV अगर the requested क्रमmat is not supported. */
		अगर (fmt->code != MEDIA_BUS_FMT_ARGB8888_1X32 &&
		    fmt->code != MEDIA_BUS_FMT_AYUV8_1X32)
			fmt->code = MEDIA_BUS_FMT_AYUV8_1X32;

		fmt->width = clamp(fmt->width, UDS_MIN_SIZE, UDS_MAX_SIZE);
		fmt->height = clamp(fmt->height, UDS_MIN_SIZE, UDS_MAX_SIZE);
		अवरोध;

	हाल UDS_PAD_SOURCE:
		/* The UDS scales but can't perक्रमm क्रमmat conversion. */
		क्रमmat = vsp1_entity_get_pad_क्रमmat(&uds->entity, config,
						    UDS_PAD_SINK);
		fmt->code = क्रमmat->code;

		uds_output_limits(क्रमmat->width, &minimum, &maximum);
		fmt->width = clamp(fmt->width, minimum, maximum);
		uds_output_limits(क्रमmat->height, &minimum, &maximum);
		fmt->height = clamp(fmt->height, minimum, maximum);
		अवरोध;
	पूर्ण

	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
पूर्ण

अटल पूर्णांक uds_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vsp1_uds *uds = to_uds(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	mutex_lock(&uds->entity.lock);

	config = vsp1_entity_get_pad_config(&uds->entity, cfg, fmt->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	uds_try_क्रमmat(uds, config, fmt->pad, &fmt->क्रमmat);

	क्रमmat = vsp1_entity_get_pad_क्रमmat(&uds->entity, config, fmt->pad);
	*क्रमmat = fmt->क्रमmat;

	अगर (fmt->pad == UDS_PAD_SINK) अणु
		/* Propagate the क्रमmat to the source pad. */
		क्रमmat = vsp1_entity_get_pad_क्रमmat(&uds->entity, config,
						    UDS_PAD_SOURCE);
		*क्रमmat = fmt->क्रमmat;

		uds_try_क्रमmat(uds, config, UDS_PAD_SOURCE, क्रमmat);
	पूर्ण

करोne:
	mutex_unlock(&uds->entity.lock);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल स्थिर काष्ठा v4l2_subdev_pad_ops uds_pad_ops = अणु
	.init_cfg = vsp1_entity_init_cfg,
	.क्रमागत_mbus_code = uds_क्रमागत_mbus_code,
	.क्रमागत_frame_size = uds_क्रमागत_frame_size,
	.get_fmt = vsp1_subdev_get_pad_क्रमmat,
	.set_fmt = uds_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops uds_ops = अणु
	.pad    = &uds_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

अटल व्योम uds_configure_stream(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_uds *uds = to_uds(&entity->subdev);
	स्थिर काष्ठा v4l2_mbus_framefmt *output;
	स्थिर काष्ठा v4l2_mbus_framefmt *input;
	अचिन्हित पूर्णांक hscale;
	अचिन्हित पूर्णांक vscale;
	bool multitap;

	input = vsp1_entity_get_pad_क्रमmat(&uds->entity, uds->entity.config,
					   UDS_PAD_SINK);
	output = vsp1_entity_get_pad_क्रमmat(&uds->entity, uds->entity.config,
					    UDS_PAD_SOURCE);

	hscale = uds_compute_ratio(input->width, output->width);
	vscale = uds_compute_ratio(input->height, output->height);

	dev_dbg(uds->entity.vsp1->dev, "hscale %u vscale %u\n", hscale, vscale);

	/*
	 * Multi-tap scaling can't be enabled aदीर्घ with alpha scaling when
	 * scaling करोwn with a factor lower than or equal to 1/2 in either
	 * direction.
	 */
	अगर (uds->scale_alpha && (hscale >= 8192 || vscale >= 8192))
		multitap = false;
	अन्यथा
		multitap = true;

	vsp1_uds_ग_लिखो(uds, dlb, VI6_UDS_CTRL,
		       (uds->scale_alpha ? VI6_UDS_CTRL_AON : 0) |
		       (multitap ? VI6_UDS_CTRL_BC : 0));

	vsp1_uds_ग_लिखो(uds, dlb, VI6_UDS_PASS_BWIDTH,
		       (uds_passband_width(hscale)
				<< VI6_UDS_PASS_BWIDTH_H_SHIFT) |
		       (uds_passband_width(vscale)
				<< VI6_UDS_PASS_BWIDTH_V_SHIFT));

	/* Set the scaling ratios. */
	vsp1_uds_ग_लिखो(uds, dlb, VI6_UDS_SCALE,
		       (hscale << VI6_UDS_SCALE_HFRAC_SHIFT) |
		       (vscale << VI6_UDS_SCALE_VFRAC_SHIFT));
पूर्ण

अटल व्योम uds_configure_partition(काष्ठा vsp1_entity *entity,
				    काष्ठा vsp1_pipeline *pipe,
				    काष्ठा vsp1_dl_list *dl,
				    काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_uds *uds = to_uds(&entity->subdev);
	काष्ठा vsp1_partition *partition = pipe->partition;
	स्थिर काष्ठा v4l2_mbus_framefmt *output;

	output = vsp1_entity_get_pad_क्रमmat(&uds->entity, uds->entity.config,
					    UDS_PAD_SOURCE);

	/* Input size clipping. */
	vsp1_uds_ग_लिखो(uds, dlb, VI6_UDS_HSZCLIP, VI6_UDS_HSZCLIP_HCEN |
		       (0 << VI6_UDS_HSZCLIP_HCL_OFST_SHIFT) |
		       (partition->uds_sink.width
				<< VI6_UDS_HSZCLIP_HCL_SIZE_SHIFT));

	/* Output size clipping. */
	vsp1_uds_ग_लिखो(uds, dlb, VI6_UDS_CLIP_SIZE,
		       (partition->uds_source.width
				<< VI6_UDS_CLIP_SIZE_HSIZE_SHIFT) |
		       (output->height
				<< VI6_UDS_CLIP_SIZE_VSIZE_SHIFT));
पूर्ण

अटल अचिन्हित पूर्णांक uds_max_width(काष्ठा vsp1_entity *entity,
				  काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_uds *uds = to_uds(&entity->subdev);
	स्थिर काष्ठा v4l2_mbus_framefmt *output;
	स्थिर काष्ठा v4l2_mbus_framefmt *input;
	अचिन्हित पूर्णांक hscale;

	input = vsp1_entity_get_pad_क्रमmat(&uds->entity, uds->entity.config,
					   UDS_PAD_SINK);
	output = vsp1_entity_get_pad_क्रमmat(&uds->entity, uds->entity.config,
					    UDS_PAD_SOURCE);
	hscale = output->width / input->width;

	/*
	 * The maximum width of the UDS is 304 pixels. These are input pixels
	 * in the event of up-scaling, and output pixels in the event of
	 * करोwnscaling.
	 *
	 * To support overlapping partition winकरोws we clamp at units of 256 and
	 * the reमुख्यing pixels are reserved.
	 */
	अगर (hscale <= 2)
		वापस 256;
	अन्यथा अगर (hscale <= 4)
		वापस 512;
	अन्यथा अगर (hscale <= 8)
		वापस 1024;
	अन्यथा
		वापस 2048;
पूर्ण

/* -----------------------------------------------------------------------------
 * Partition Algorithm Support
 */

अटल व्योम uds_partition(काष्ठा vsp1_entity *entity,
			  काष्ठा vsp1_pipeline *pipe,
			  काष्ठा vsp1_partition *partition,
			  अचिन्हित पूर्णांक partition_idx,
			  काष्ठा vsp1_partition_winकरोw *winकरोw)
अणु
	काष्ठा vsp1_uds *uds = to_uds(&entity->subdev);
	स्थिर काष्ठा v4l2_mbus_framefmt *output;
	स्थिर काष्ठा v4l2_mbus_framefmt *input;

	/* Initialise the partition state. */
	partition->uds_sink = *winकरोw;
	partition->uds_source = *winकरोw;

	input = vsp1_entity_get_pad_क्रमmat(&uds->entity, uds->entity.config,
					   UDS_PAD_SINK);
	output = vsp1_entity_get_pad_क्रमmat(&uds->entity, uds->entity.config,
					    UDS_PAD_SOURCE);

	partition->uds_sink.width = winकरोw->width * input->width
				  / output->width;
	partition->uds_sink.left = winकरोw->left * input->width
				 / output->width;

	*winकरोw = partition->uds_sink;
पूर्ण

अटल स्थिर काष्ठा vsp1_entity_operations uds_entity_ops = अणु
	.configure_stream = uds_configure_stream,
	.configure_partition = uds_configure_partition,
	.max_width = uds_max_width,
	.partition = uds_partition,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_uds *vsp1_uds_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index)
अणु
	काष्ठा vsp1_uds *uds;
	अक्षर name[6];
	पूर्णांक ret;

	uds = devm_kzalloc(vsp1->dev, माप(*uds), GFP_KERNEL);
	अगर (uds == शून्य)
		वापस ERR_PTR(-ENOMEM);

	uds->entity.ops = &uds_entity_ops;
	uds->entity.type = VSP1_ENTITY_UDS;
	uds->entity.index = index;

	प्र_लिखो(name, "uds.%u", index);
	ret = vsp1_entity_init(vsp1, &uds->entity, name, 2, &uds_ops,
			       MEDIA_ENT_F_PROC_VIDEO_SCALER);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस uds;
पूर्ण
