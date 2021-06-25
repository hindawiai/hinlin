<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश "atomisp_cmd.h"
#समावेश "atomisp_common.h"
#समावेश "atomisp_compat.h"
#समावेश "atomisp_internal.h"

स्थिर काष्ठा atomisp_in_fmt_conv atomisp_in_fmt_conv[] = अणु
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, 8, 8, ATOMISP_INPUT_FORMAT_RAW_8, IA_CSS_BAYER_ORDER_BGGR पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, 8, 8, ATOMISP_INPUT_FORMAT_RAW_8, IA_CSS_BAYER_ORDER_GBRG पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, 8, 8, ATOMISP_INPUT_FORMAT_RAW_8, IA_CSS_BAYER_ORDER_GRBG पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, 8, 8, ATOMISP_INPUT_FORMAT_RAW_8, IA_CSS_BAYER_ORDER_RGGB पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, 10, 10, ATOMISP_INPUT_FORMAT_RAW_10, IA_CSS_BAYER_ORDER_BGGR पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, 10, 10, ATOMISP_INPUT_FORMAT_RAW_10, IA_CSS_BAYER_ORDER_GBRG पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, 10, 10, ATOMISP_INPUT_FORMAT_RAW_10, IA_CSS_BAYER_ORDER_GRBG पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, 10, 10, ATOMISP_INPUT_FORMAT_RAW_10, IA_CSS_BAYER_ORDER_RGGB पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, 12, 12, ATOMISP_INPUT_FORMAT_RAW_12, IA_CSS_BAYER_ORDER_BGGR पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, 12, 12, ATOMISP_INPUT_FORMAT_RAW_12, IA_CSS_BAYER_ORDER_GBRG पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, 12, 12, ATOMISP_INPUT_FORMAT_RAW_12, IA_CSS_BAYER_ORDER_GRBG पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, 12, 12, ATOMISP_INPUT_FORMAT_RAW_12, IA_CSS_BAYER_ORDER_RGGB पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1X16, 8, 8, ATOMISP_INPUT_FORMAT_YUV422_8, 0 पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1X16, 8, 8, ATOMISP_INPUT_FORMAT_YUV422_8, 0 पूर्ण,
#अगर 0 // disabled due to clang warnings
	अणु MEDIA_BUS_FMT_JPEG_1X8, 8, 8, IA_CSS_FRAME_FORMAT_BINARY_8, 0 पूर्ण,
	अणु V4L2_MBUS_FMT_CUSTOM_NV12, 12, 12, IA_CSS_FRAME_FORMAT_NV12, 0 पूर्ण,
	अणु V4L2_MBUS_FMT_CUSTOM_NV21, 12, 12, IA_CSS_FRAME_FORMAT_NV21, 0 पूर्ण,
#पूर्ण_अगर
	अणु V4L2_MBUS_FMT_CUSTOM_YUV420, 12, 12, ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY, 0 पूर्ण,
#अगर 0
	अणु V4L2_MBUS_FMT_CUSTOM_M10MO_RAW, 8, 8, IA_CSS_FRAME_FORMAT_BINARY_8, 0 पूर्ण,
#पूर्ण_अगर
	/* no valid V4L2 MBUS code क्रम metadata क्रमmat, so leave it 0. */
	अणु 0, 0, 0, ATOMISP_INPUT_FORMAT_EMBEDDED, 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा अणु
	u32 code;
	u32 compressed;
पूर्ण compressed_codes[] = अणु
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8 पूर्ण,
पूर्ण;

u32 atomisp_subdev_uncompressed_code(u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(compressed_codes); i++)
		अगर (code == compressed_codes[i].compressed)
			वापस compressed_codes[i].code;

	वापस code;
पूर्ण

bool atomisp_subdev_is_compressed(u32 code)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(atomisp_in_fmt_conv) - 1; i++)
		अगर (code == atomisp_in_fmt_conv[i].code)
			वापस atomisp_in_fmt_conv[i].bpp !=
			       atomisp_in_fmt_conv[i].depth;

	वापस false;
पूर्ण

स्थिर काष्ठा atomisp_in_fmt_conv *atomisp_find_in_fmt_conv(u32 code)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(atomisp_in_fmt_conv) - 1; i++)
		अगर (code == atomisp_in_fmt_conv[i].code)
			वापस atomisp_in_fmt_conv + i;

	वापस शून्य;
पूर्ण

स्थिर काष्ठा atomisp_in_fmt_conv *atomisp_find_in_fmt_conv_by_atomisp_in_fmt(
    क्रमागत atomisp_input_क्रमmat atomisp_in_fmt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(atomisp_in_fmt_conv) - 1; i++)
		अगर (atomisp_in_fmt_conv[i].atomisp_in_fmt == atomisp_in_fmt)
			वापस atomisp_in_fmt_conv + i;

	वापस शून्य;
पूर्ण

bool atomisp_subdev_क्रमmat_conversion(काष्ठा atomisp_sub_device *asd,
				      अचिन्हित पूर्णांक source_pad)
अणु
	काष्ठा v4l2_mbus_framefmt *sink, *src;

	sink = atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
				       V4L2_SUBDEV_FORMAT_ACTIVE,
				       ATOMISP_SUBDEV_PAD_SINK);
	src = atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
				      V4L2_SUBDEV_FORMAT_ACTIVE, source_pad);

	वापस atomisp_is_mbuscode_raw(sink->code)
	       && !atomisp_is_mbuscode_raw(src->code);
पूर्ण

uपूर्णांक16_t atomisp_subdev_source_pad(काष्ठा video_device *vdev)
अणु
	काष्ठा media_link *link;
	u16 ret = 0;

	list_क्रम_each_entry(link, &vdev->entity.links, list) अणु
		अगर (link->source) अणु
			ret = link->source->index;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * V4L2 subdev operations
 */

/*
 * isp_subdev_ioctl - CCDC module निजी ioctl's
 * @sd: ISP V4L2 subdevice
 * @cmd: ioctl command
 * @arg: ioctl argument
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल दीर्घ isp_subdev_ioctl(काष्ठा v4l2_subdev *sd,
			     अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	वापस 0;
पूर्ण

/*
 * isp_subdev_set_घातer - Power on/off the CCDC module
 * @sd: ISP V4L2 subdevice
 * @on: घातer on/off
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल पूर्णांक isp_subdev_set_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक isp_subdev_subscribe_event(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_fh *fh,
				      काष्ठा v4l2_event_subscription *sub)
अणु
	काष्ठा atomisp_sub_device *isp_sd = v4l2_get_subdevdata(sd);
	काष्ठा atomisp_device *isp = isp_sd->isp;

	अगर (sub->type != V4L2_EVENT_FRAME_SYNC &&
	    sub->type != V4L2_EVENT_FRAME_END &&
	    sub->type != V4L2_EVENT_ATOMISP_3A_STATS_READY &&
	    sub->type != V4L2_EVENT_ATOMISP_METADATA_READY &&
	    sub->type != V4L2_EVENT_ATOMISP_PAUSE_BUFFER &&
	    sub->type != V4L2_EVENT_ATOMISP_CSS_RESET &&
	    sub->type != V4L2_EVENT_ATOMISP_RAW_BUFFERS_ALLOC_DONE &&
	    sub->type != V4L2_EVENT_ATOMISP_ACC_COMPLETE)
		वापस -EINVAL;

	अगर (sub->type == V4L2_EVENT_FRAME_SYNC &&
	    !atomisp_css_valid_sof(isp))
		वापस -EINVAL;

	वापस v4l2_event_subscribe(fh, sub, 16, शून्य);
पूर्ण

अटल पूर्णांक isp_subdev_unsubscribe_event(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_fh *fh,
					काष्ठा v4l2_event_subscription *sub)
अणु
	वापस v4l2_event_unsubscribe(fh, sub);
पूर्ण

/*
 * isp_subdev_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd: poपूर्णांकer to v4l2 subdev काष्ठाure
 * @fh : V4L2 subdev file handle
 * @code: poपूर्णांकer to v4l2_subdev_pad_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक isp_subdev_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(atomisp_in_fmt_conv) - 1)
		वापस -EINVAL;

	code->code = atomisp_in_fmt_conv[code->index].code;

	वापस 0;
पूर्ण

अटल पूर्णांक isp_subdev_validate_rect(काष्ठा v4l2_subdev *sd, uपूर्णांक32_t pad,
				    uपूर्णांक32_t target)
अणु
	चयन (pad) अणु
	हाल ATOMISP_SUBDEV_PAD_SINK:
		चयन (target) अणु
		हाल V4L2_SEL_TGT_CROP:
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		चयन (target) अणु
		हाल V4L2_SEL_TGT_COMPOSE:
			वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

काष्ठा v4l2_rect *atomisp_subdev_get_rect(काष्ठा v4l2_subdev *sd,
	काष्ठा v4l2_subdev_pad_config *cfg,
	u32 which, uपूर्णांक32_t pad,
	uपूर्णांक32_t target)
अणु
	काष्ठा atomisp_sub_device *isp_sd = v4l2_get_subdevdata(sd);

	अगर (which == V4L2_SUBDEV_FORMAT_TRY) अणु
		चयन (target) अणु
		हाल V4L2_SEL_TGT_CROP:
			वापस v4l2_subdev_get_try_crop(sd, cfg, pad);
		हाल V4L2_SEL_TGT_COMPOSE:
			वापस v4l2_subdev_get_try_compose(sd, cfg, pad);
		पूर्ण
	पूर्ण

	चयन (target) अणु
	हाल V4L2_SEL_TGT_CROP:
		वापस &isp_sd->fmt[pad].crop;
	हाल V4L2_SEL_TGT_COMPOSE:
		वापस &isp_sd->fmt[pad].compose;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा v4l2_mbus_framefmt
*atomisp_subdev_get_ffmt(काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_subdev_pad_config *cfg, uपूर्णांक32_t which,
			 uपूर्णांक32_t pad)
अणु
	काष्ठा atomisp_sub_device *isp_sd = v4l2_get_subdevdata(sd);

	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(sd, cfg, pad);

	वापस &isp_sd->fmt[pad].fmt;
पूर्ण

अटल व्योम isp_get_fmt_rect(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg, uपूर्णांक32_t which,
			     काष्ठा v4l2_mbus_framefmt **ffmt,
			     काष्ठा v4l2_rect *crop[ATOMISP_SUBDEV_PADS_NUM],
			     काष्ठा v4l2_rect *comp[ATOMISP_SUBDEV_PADS_NUM])
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ATOMISP_SUBDEV_PADS_NUM; i++) अणु
		ffmt[i] = atomisp_subdev_get_ffmt(sd, cfg, which, i);
		crop[i] = atomisp_subdev_get_rect(sd, cfg, which, i,
						  V4L2_SEL_TGT_CROP);
		comp[i] = atomisp_subdev_get_rect(sd, cfg, which, i,
						  V4L2_SEL_TGT_COMPOSE);
	पूर्ण
पूर्ण

अटल व्योम isp_subdev_propagate(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 u32 which, uपूर्णांक32_t pad, uपूर्णांक32_t target,
				 uपूर्णांक32_t flags)
अणु
	काष्ठा v4l2_mbus_framefmt *ffmt[ATOMISP_SUBDEV_PADS_NUM];
	काष्ठा v4l2_rect *crop[ATOMISP_SUBDEV_PADS_NUM],
		       *comp[ATOMISP_SUBDEV_PADS_NUM];

	अगर (flags & V4L2_SEL_FLAG_KEEP_CONFIG)
		वापस;

	isp_get_fmt_rect(sd, cfg, which, ffmt, crop, comp);

	चयन (pad) अणु
	हाल ATOMISP_SUBDEV_PAD_SINK: अणु
		काष्ठा v4l2_rect r = अणु0पूर्ण;

		/* Only crop target supported on sink pad. */
		r.width = ffmt[pad]->width;
		r.height = ffmt[pad]->height;

		atomisp_subdev_set_selection(sd, cfg, which, pad,
					     target, flags, &r);
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक isp_subdev_get_selection(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा v4l2_rect *rec;
	पूर्णांक rval = isp_subdev_validate_rect(sd, sel->pad, sel->target);

	अगर (rval)
		वापस rval;

	rec = atomisp_subdev_get_rect(sd, cfg, sel->which, sel->pad,
				      sel->target);
	अगर (!rec)
		वापस -EINVAL;

	sel->r = *rec;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *atomisp_pad_str(अचिन्हित पूर्णांक pad)
अणु
	अटल स्थिर अक्षर *स्थिर pad_str[] = अणु
		"ATOMISP_SUBDEV_PAD_SINK",
		"ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE",
		"ATOMISP_SUBDEV_PAD_SOURCE_VF",
		"ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW",
		"ATOMISP_SUBDEV_PAD_SOURCE_VIDEO",
	पूर्ण;

	अगर (pad >= ARRAY_SIZE(pad_str))
		वापस "ATOMISP_INVALID_PAD";
	वापस pad_str[pad];
पूर्ण

पूर्णांक atomisp_subdev_set_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 u32 which, uपूर्णांक32_t pad, uपूर्णांक32_t target,
				 u32 flags, काष्ठा v4l2_rect *r)
अणु
	काष्ठा atomisp_sub_device *isp_sd = v4l2_get_subdevdata(sd);
	काष्ठा atomisp_device *isp = isp_sd->isp;
	काष्ठा v4l2_mbus_framefmt *ffmt[ATOMISP_SUBDEV_PADS_NUM];
	u16 vdev_pad = atomisp_subdev_source_pad(sd->devnode);
	काष्ठा v4l2_rect *crop[ATOMISP_SUBDEV_PADS_NUM],
		       *comp[ATOMISP_SUBDEV_PADS_NUM];
	क्रमागत atomisp_input_stream_id stream_id;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक padding_w = pad_w;
	अचिन्हित पूर्णांक padding_h = pad_h;

	stream_id = atomisp_source_pad_to_stream_id(isp_sd, vdev_pad);

	isp_get_fmt_rect(sd, cfg, which, ffmt, crop, comp);

	dev_dbg(isp->dev,
		"sel: pad %s tgt %s l %d t %d w %d h %d which %s f 0x%8.8x\n",
		atomisp_pad_str(pad), target == V4L2_SEL_TGT_CROP
		? "V4L2_SEL_TGT_CROP" : "V4L2_SEL_TGT_COMPOSE",
		r->left, r->top, r->width, r->height,
		which == V4L2_SUBDEV_FORMAT_TRY ? "V4L2_SUBDEV_FORMAT_TRY"
		: "V4L2_SUBDEV_FORMAT_ACTIVE", flags);

	r->width = roundकरोwn(r->width, ATOM_ISP_STEP_WIDTH);
	r->height = roundकरोwn(r->height, ATOM_ISP_STEP_HEIGHT);

	चयन (pad) अणु
	हाल ATOMISP_SUBDEV_PAD_SINK: अणु
		/* Only crop target supported on sink pad. */
		अचिन्हित पूर्णांक dvs_w, dvs_h;

		crop[pad]->width = ffmt[pad]->width;
		crop[pad]->height = ffmt[pad]->height;

		/* Workaround क्रम BYT 1080p perfectshot since the maxinum resolution of
		 * front camera ov2722 is 1932x1092 and cannot use pad_w > 12*/
		अगर (!म_भेदन(isp->inमाला_दो[isp_sd->input_curr].camera->name,
			     "ov2722", 6) && crop[pad]->height == 1092) अणु
			padding_w = 12;
			padding_h = 12;
		पूर्ण

		अगर (isp->inमाला_दो[isp_sd->input_curr].type == SOC_CAMERA) अणु
			padding_w = 0;
			padding_h = 0;
		पूर्ण

		अगर (atomisp_subdev_क्रमmat_conversion(isp_sd,
						     isp_sd->capture_pad)
		    && crop[pad]->width && crop[pad]->height) अणु
			crop[pad]->width -= padding_w;
			crop[pad]->height -= padding_h;
		पूर्ण

		/* अगर subdev type is SOC camera,we करो not need to set DVS */
		अगर (isp->inमाला_दो[isp_sd->input_curr].type == SOC_CAMERA)
			isp_sd->params.video_dis_en = 0;

		अगर (isp_sd->params.video_dis_en &&
		    isp_sd->run_mode->val == ATOMISP_RUN_MODE_VIDEO &&
		    !isp_sd->continuous_mode->val) अणु
			/* This resolution contains 20 % of DVS slack
			 * (of the desired captured image beक्रमe
			 * scaling, or 1 / 6 of what we get from the
			 * sensor) in both width and height. Remove
			 * it. */
			crop[pad]->width = roundup(crop[pad]->width * 5 / 6,
						   ATOM_ISP_STEP_WIDTH);
			crop[pad]->height = roundup(crop[pad]->height * 5 / 6,
						    ATOM_ISP_STEP_HEIGHT);
		पूर्ण

		crop[pad]->width = min(crop[pad]->width, r->width);
		crop[pad]->height = min(crop[pad]->height, r->height);

		अगर (!(flags & V4L2_SEL_FLAG_KEEP_CONFIG)) अणु
			क्रम (i = ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE;
			     i < ATOMISP_SUBDEV_PADS_NUM; i++) अणु
				काष्ठा v4l2_rect पंचांगp = *crop[pad];

				atomisp_subdev_set_selection(
				    sd, cfg, which, i, V4L2_SEL_TGT_COMPOSE,
				    flags, &पंचांगp);
			पूर्ण
		पूर्ण

		अगर (which == V4L2_SUBDEV_FORMAT_TRY)
			अवरोध;

		अगर (isp_sd->params.video_dis_en &&
		    isp_sd->run_mode->val == ATOMISP_RUN_MODE_VIDEO &&
		    !isp_sd->continuous_mode->val) अणु
			dvs_w = roundकरोwn(crop[pad]->width / 5,
					  ATOM_ISP_STEP_WIDTH);
			dvs_h = roundकरोwn(crop[pad]->height / 5,
					  ATOM_ISP_STEP_HEIGHT);
		पूर्ण अन्यथा अगर (!isp_sd->params.video_dis_en &&
			   isp_sd->run_mode->val == ATOMISP_RUN_MODE_VIDEO) अणु
			/*
			 * For CSS2.0, digital zoom needs to set dvs envelope to 12
			 * when dvs is disabled.
			 */
			dvs_w = dvs_h = 12;
		पूर्ण अन्यथा
			dvs_w = dvs_h = 0;

		atomisp_css_video_set_dis_envelope(isp_sd, dvs_w, dvs_h);
		atomisp_css_input_set_effective_resolution(isp_sd, stream_id,
			crop[pad]->width, crop[pad]->height);

		अवरोध;
	पूर्ण
	हाल ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE:
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VIDEO: अणु
		/* Only compose target is supported on source pads. */

		अगर (isp_sd->vfpp->val == ATOMISP_VFPP_DISABLE_LOWLAT) अणु
			/* Scaling is disabled in this mode */
			r->width = crop[ATOMISP_SUBDEV_PAD_SINK]->width;
			r->height = crop[ATOMISP_SUBDEV_PAD_SINK]->height;
		पूर्ण

		अगर (crop[ATOMISP_SUBDEV_PAD_SINK]->width == r->width
		    && crop[ATOMISP_SUBDEV_PAD_SINK]->height == r->height)
			isp_sd->params.yuv_ds_en = false;
		अन्यथा
			isp_sd->params.yuv_ds_en = true;

		comp[pad]->width = r->width;
		comp[pad]->height = r->height;

		अगर (r->width == 0 || r->height == 0 ||
		    crop[ATOMISP_SUBDEV_PAD_SINK]->width == 0 ||
		    crop[ATOMISP_SUBDEV_PAD_SINK]->height == 0)
			अवरोध;
		/*
		 * करो cropping on sensor input अगर ratio of required resolution
		 * is dअगरferent with sensor output resolution ratio:
		 *
		 * ratio = width / height
		 *
		 * अगर ratio_output < ratio_sensor:
		 *	effect_width = sensor_height * out_width / out_height;
		 *	effect_height = sensor_height;
		 * अन्यथा
		 *	effect_width = sensor_width;
		 *	effect_height = sensor_width * out_height / out_width;
		 *
		 */
		अगर (r->width * crop[ATOMISP_SUBDEV_PAD_SINK]->height <
		    crop[ATOMISP_SUBDEV_PAD_SINK]->width * r->height)
			atomisp_css_input_set_effective_resolution(isp_sd,
				stream_id,
				roundकरोwn(crop[ATOMISP_SUBDEV_PAD_SINK]->
					  height * r->width / r->height,
					  ATOM_ISP_STEP_WIDTH),
				crop[ATOMISP_SUBDEV_PAD_SINK]->height);
		अन्यथा
			atomisp_css_input_set_effective_resolution(isp_sd,
				stream_id,
				crop[ATOMISP_SUBDEV_PAD_SINK]->width,
				roundकरोwn(crop[ATOMISP_SUBDEV_PAD_SINK]->
					  width * r->height / r->width,
					  ATOM_ISP_STEP_WIDTH));

		अवरोध;
	पूर्ण
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VF:
	हाल ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW:
		comp[pad]->width = r->width;
		comp[pad]->height = r->height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Set क्रमmat dimensions on non-sink pads as well. */
	अगर (pad != ATOMISP_SUBDEV_PAD_SINK) अणु
		ffmt[pad]->width = comp[pad]->width;
		ffmt[pad]->height = comp[pad]->height;
	पूर्ण

	अगर (!atomisp_subdev_get_rect(sd, cfg, which, pad, target))
		वापस -EINVAL;
	*r = *atomisp_subdev_get_rect(sd, cfg, which, pad, target);

	dev_dbg(isp->dev, "sel actual: l %d t %d w %d h %d\n",
		r->left, r->top, r->width, r->height);

	वापस 0;
पूर्ण

अटल पूर्णांक isp_subdev_set_selection(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_selection *sel)
अणु
	पूर्णांक rval = isp_subdev_validate_rect(sd, sel->pad, sel->target);

	अगर (rval)
		वापस rval;

	वापस atomisp_subdev_set_selection(sd, cfg, sel->which, sel->pad,
					    sel->target, sel->flags, &sel->r);
पूर्ण

अटल पूर्णांक atomisp_get_sensor_bin_factor(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा v4l2_control ctrl = अणु0पूर्ण;
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक hbin, vbin;
	पूर्णांक ret;

	अगर (isp->inमाला_दो[asd->input_curr].type == खाता_INPUT ||
	    isp->inमाला_दो[asd->input_curr].type == TEST_PATTERN)
		वापस 0;

	ctrl.id = V4L2_CID_BIN_FACTOR_HORZ;
	ret =
	    v4l2_g_ctrl(isp->inमाला_दो[asd->input_curr].camera->ctrl_handler,
			&ctrl);
	hbin = ctrl.value;
	ctrl.id = V4L2_CID_BIN_FACTOR_VERT;
	ret |=
	    v4l2_g_ctrl(isp->inमाला_दो[asd->input_curr].camera->ctrl_handler,
			&ctrl);
	vbin = ctrl.value;

	/*
	 * ISP needs to know binning factor from sensor.
	 * In हाल horizontal and vertical sensor's binning factors
	 * are dअगरferent or sensor करोes not support binning factor CID,
	 * ISP will apply शेष 0 value.
	 */
	अगर (ret || hbin != vbin)
		hbin = 0;

	वापस hbin;
पूर्ण

व्योम atomisp_subdev_set_ffmt(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg, uपूर्णांक32_t which,
			     u32 pad, काष्ठा v4l2_mbus_framefmt *ffmt)
अणु
	काष्ठा atomisp_sub_device *isp_sd = v4l2_get_subdevdata(sd);
	काष्ठा atomisp_device *isp = isp_sd->isp;
	काष्ठा v4l2_mbus_framefmt *__ffmt =
	    atomisp_subdev_get_ffmt(sd, cfg, which, pad);
	u16 vdev_pad = atomisp_subdev_source_pad(sd->devnode);
	क्रमागत atomisp_input_stream_id stream_id;

	dev_dbg(isp->dev, "ffmt: pad %s w %d h %d code 0x%8.8x which %s\n",
		atomisp_pad_str(pad), ffmt->width, ffmt->height, ffmt->code,
		which == V4L2_SUBDEV_FORMAT_TRY ? "V4L2_SUBDEV_FORMAT_TRY"
		: "V4L2_SUBDEV_FORMAT_ACTIVE");

	stream_id = atomisp_source_pad_to_stream_id(isp_sd, vdev_pad);

	चयन (pad) अणु
	हाल ATOMISP_SUBDEV_PAD_SINK: अणु
		स्थिर काष्ठा atomisp_in_fmt_conv *fc =
		    atomisp_find_in_fmt_conv(ffmt->code);

		अगर (!fc) अणु
			fc = atomisp_in_fmt_conv;
			ffmt->code = fc->code;
			dev_dbg(isp->dev, "using 0x%8.8x instead\n",
				ffmt->code);
		पूर्ण

		*__ffmt = *ffmt;

		isp_subdev_propagate(sd, cfg, which, pad,
				     V4L2_SEL_TGT_CROP, 0);

		अगर (which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
			atomisp_css_input_set_resolution(isp_sd,
							 stream_id, ffmt);
			atomisp_css_input_set_binning_factor(isp_sd,
							     stream_id,
							     atomisp_get_sensor_bin_factor(isp_sd));
			atomisp_css_input_set_bayer_order(isp_sd, stream_id,
							  fc->bayer_order);
			atomisp_css_input_set_क्रमmat(isp_sd, stream_id,
						     fc->atomisp_in_fmt);
			atomisp_css_set_शेष_isys_config(isp_sd, stream_id,
							    ffmt);
		पूर्ण

		अवरोध;
	पूर्ण
	हाल ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE:
	हाल ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW:
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VF:
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VIDEO:
		__ffmt->code = ffmt->code;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * isp_subdev_get_क्रमmat - Retrieve the video क्रमmat on a pad
 * @sd : ISP V4L2 subdevice
 * @fh : V4L2 subdev file handle
 * @pad: Pad number
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक isp_subdev_get_क्रमmat(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	fmt->क्रमmat = *atomisp_subdev_get_ffmt(sd, cfg, fmt->which, fmt->pad);

	वापस 0;
पूर्ण

/*
 * isp_subdev_set_क्रमmat - Set the video क्रमmat on a pad
 * @sd : ISP subdev V4L2 subdevice
 * @fh : V4L2 subdev file handle
 * @pad: Pad number
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक isp_subdev_set_क्रमmat(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	atomisp_subdev_set_ffmt(sd, cfg, fmt->which, fmt->pad, &fmt->क्रमmat);

	वापस 0;
पूर्ण

/* V4L2 subdev core operations */
अटल स्थिर काष्ठा v4l2_subdev_core_ops isp_subdev_v4l2_core_ops = अणु
	.ioctl = isp_subdev_ioctl, .s_घातer = isp_subdev_set_घातer,
	.subscribe_event = isp_subdev_subscribe_event,
	.unsubscribe_event = isp_subdev_unsubscribe_event,
पूर्ण;

/* V4L2 subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops isp_subdev_v4l2_pad_ops = अणु
	.क्रमागत_mbus_code = isp_subdev_क्रमागत_mbus_code,
	.get_fmt = isp_subdev_get_क्रमmat,
	.set_fmt = isp_subdev_set_क्रमmat,
	.get_selection = isp_subdev_get_selection,
	.set_selection = isp_subdev_set_selection,
	.link_validate = v4l2_subdev_link_validate_शेष,
पूर्ण;

/* V4L2 subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops isp_subdev_v4l2_ops = अणु
	.core = &isp_subdev_v4l2_core_ops,
	.pad = &isp_subdev_v4l2_pad_ops,
पूर्ण;

अटल व्योम isp_subdev_init_params(काष्ठा atomisp_sub_device *asd)
अणु
	अचिन्हित पूर्णांक i;

	/* parameters initialization */
	INIT_LIST_HEAD(&asd->s3a_stats);
	INIT_LIST_HEAD(&asd->s3a_stats_in_css);
	INIT_LIST_HEAD(&asd->s3a_stats_पढ़ोy);
	INIT_LIST_HEAD(&asd->dis_stats);
	INIT_LIST_HEAD(&asd->dis_stats_in_css);
	spin_lock_init(&asd->dis_stats_lock);
	क्रम (i = 0; i < ATOMISP_METADATA_TYPE_NUM; i++) अणु
		INIT_LIST_HEAD(&asd->metadata[i]);
		INIT_LIST_HEAD(&asd->metadata_in_css[i]);
		INIT_LIST_HEAD(&asd->metadata_पढ़ोy[i]);
	पूर्ण
पूर्ण

/*
* isp_subdev_link_setup - Setup isp subdev connections
* @entity: ispsubdev media entity
* @local: Pad at the local end of the link
* @remote: Pad at the remote end of the link
* @flags: Link flags
*
* वापस -EINVAL or zero on success
*/
अटल पूर्णांक isp_subdev_link_setup(काष्ठा media_entity *entity,
				 स्थिर काष्ठा media_pad *local,
				 स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा atomisp_sub_device *isp_sd = v4l2_get_subdevdata(sd);
	काष्ठा atomisp_device *isp = isp_sd->isp;
	अचिन्हित पूर्णांक i;

	चयन (local->index | is_media_entity_v4l2_subdev(remote->entity)) अणु
	हाल ATOMISP_SUBDEV_PAD_SINK | MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN:
		/* Read from the sensor CSI2-ports. */
		अगर (!(flags & MEDIA_LNK_FL_ENABLED)) अणु
			isp_sd->input = ATOMISP_SUBDEV_INPUT_NONE;
			अवरोध;
		पूर्ण

		अगर (isp_sd->input != ATOMISP_SUBDEV_INPUT_NONE)
			वापस -EBUSY;

		क्रम (i = 0; i < ATOMISP_CAMERA_NR_PORTS; i++) अणु
			अगर (remote->entity != &isp->csi2_port[i].subdev.entity)
				जारी;

			isp_sd->input = ATOMISP_SUBDEV_INPUT_CSI2_PORT1 + i;
			वापस 0;
		पूर्ण

		वापस -EINVAL;

	हाल ATOMISP_SUBDEV_PAD_SINK | MEDIA_ENT_F_OLD_BASE:
		/* पढ़ो from memory */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (isp_sd->input >= ATOMISP_SUBDEV_INPUT_CSI2_PORT1 &&
			    isp_sd->input < (ATOMISP_SUBDEV_INPUT_CSI2_PORT1
					     + ATOMISP_CAMERA_NR_PORTS))
				वापस -EBUSY;
			isp_sd->input = ATOMISP_SUBDEV_INPUT_MEMORY;
		पूर्ण अन्यथा अणु
			अगर (isp_sd->input == ATOMISP_SUBDEV_INPUT_MEMORY)
				isp_sd->input = ATOMISP_SUBDEV_INPUT_NONE;
		पूर्ण
		अवरोध;

	हाल ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW | MEDIA_ENT_F_OLD_BASE:
		/* always ग_लिखो to memory */
		अवरोध;

	हाल ATOMISP_SUBDEV_PAD_SOURCE_VF | MEDIA_ENT_F_OLD_BASE:
		/* always ग_लिखो to memory */
		अवरोध;

	हाल ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE | MEDIA_ENT_F_OLD_BASE:
		/* always ग_लिखो to memory */
		अवरोध;

	हाल ATOMISP_SUBDEV_PAD_SOURCE_VIDEO | MEDIA_ENT_F_OLD_BASE:
		/* always ग_लिखो to memory */
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations isp_subdev_media_ops = अणु
	.link_setup = isp_subdev_link_setup,
	.link_validate = v4l2_subdev_link_validate,
	/*	 .set_घातer = v4l2_subdev_set_घातer,	*/
पूर्ण;

अटल पूर्णांक __atomisp_update_run_mode(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा v4l2_ctrl *ctrl = asd->run_mode;
	काष्ठा v4l2_ctrl *c;
	s32 mode;

	अगर (ctrl->val != ATOMISP_RUN_MODE_VIDEO &&
	    asd->continuous_mode->val)
		mode = ATOMISP_RUN_MODE_PREVIEW;
	अन्यथा
		mode = ctrl->val;

	c = v4l2_ctrl_find(
		isp->inमाला_दो[asd->input_curr].camera->ctrl_handler,
		V4L2_CID_RUN_MODE);

	अगर (c)
		वापस v4l2_ctrl_s_ctrl(c, mode);

	वापस 0;
पूर्ण

पूर्णांक atomisp_update_run_mode(काष्ठा atomisp_sub_device *asd)
अणु
	पूर्णांक rval;

	mutex_lock(asd->ctrl_handler.lock);
	rval = __atomisp_update_run_mode(asd);
	mutex_unlock(asd->ctrl_handler.lock);

	वापस rval;
पूर्ण

अटल पूर्णांक s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा atomisp_sub_device *asd = container_of(
					     ctrl->handler, काष्ठा atomisp_sub_device, ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_RUN_MODE:
		वापस __atomisp_update_run_mode(asd);
	हाल V4L2_CID_DEPTH_MODE:
		अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_DISABLED) अणु
			dev_err(asd->isp->dev,
				"ISP is streaming, it is not supported to change the depth mode\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ctrl_ops = अणु
	.s_ctrl = &s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_fmt_स्वतः = अणु
	.ops = &ctrl_ops,
	.id = V4L2_CID_FMT_AUTO,
	.name = "Automatic format guessing",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

अटल स्थिर अक्षर *स्थिर ctrl_run_mode_menu[] = अणु
	शून्य,
	"Video",
	"Still capture",
	"Continuous capture",
	"Preview",
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_run_mode = अणु
	.ops = &ctrl_ops,
	.id = V4L2_CID_RUN_MODE,
	.name = "Atomisp run mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.min = 1,
	.def = 1,
	.max = 4,
	.qmenu = ctrl_run_mode_menu,
पूर्ण;

अटल स्थिर अक्षर *स्थिर ctrl_vfpp_mode_menu[] = अणु
	"Enable",			/* vfpp always enabled */
	"Disable to scaler mode",	/* CSS पूर्णांकo video mode and disable */
	"Disable to low latency mode",	/* CSS पूर्णांकo still mode and disable */
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_vfpp = अणु
	.id = V4L2_CID_VFPP,
	.name = "Atomisp vf postprocess",
	.type = V4L2_CTRL_TYPE_MENU,
	.min = 0,
	.def = 0,
	.max = 2,
	.qmenu = ctrl_vfpp_mode_menu,
पूर्ण;

/*
 * Control क्रम ISP continuous mode
 *
 * When enabled, capture processing is possible without
 * stopping the preview pipeline. When disabled, ISP needs
 * to be restarted between preview and capture.
 */
अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_continuous_mode = अणु
	.ops = &ctrl_ops,
	.id = V4L2_CID_ATOMISP_CONTINUOUS_MODE,
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.name = "Continuous mode",
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
पूर्ण;

/*
 * Control क्रम continuous mode raw buffer size
 *
 * The size of the RAW ringbuffer sets limit on how much
 * back in समय application can go when requesting capture
 * frames to be rendered, and how many frames can be rendered
 * in a burst at full sensor rate.
 *
 * Note: this setting has a big impact on memory consumption of
 * the CSS subप्रणाली.
 */
अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_continuous_raw_buffer_size = अणु
	.ops = &ctrl_ops,
	.id = V4L2_CID_ATOMISP_CONTINUOUS_RAW_BUFFER_SIZE,
	.type = V4L2_CTRL_TYPE_INTEGER,
	.name = "Continuous raw ringbuffer size",
	.min = 1,
	.max = 100, /* depends on CSS version, runसमय checked */
	.step = 1,
	.def = 3,
पूर्ण;

/*
 * Control क्रम enabling continuous viewfinder
 *
 * When enabled, and ISP is in continuous mode (see ctrl_continuous_mode ),
 * preview pipeline जारीs concurrently with capture
 * processing. When disabled, and continuous mode is used,
 * preview is छोड़ोd जबतक captures are processed, but
 * full pipeline restart is not needed.
 *
 * By setting this to disabled, capture processing is
 * essentially given priority over preview, and the effective
 * capture output rate may be higher than with continuous
 * viewfinder enabled.
 */
अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_continuous_viewfinder = अणु
	.id = V4L2_CID_ATOMISP_CONTINUOUS_VIEWFINDER,
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.name = "Continuous viewfinder",
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
पूर्ण;

/*
 * Control क्रम enabling Lock&Unlock Raw Buffer mechanism
 *
 * When enabled, Raw Buffer can be locked and unlocked.
 * Application can hold the exp_id of Raw Buffer
 * and unlock it when no दीर्घer needed.
 * Note: Make sure set this configuration beक्रमe creating stream.
 */
अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_enable_raw_buffer_lock = अणु
	.id = V4L2_CID_ENABLE_RAW_BUFFER_LOCK,
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.name = "Lock Unlock Raw Buffer",
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
पूर्ण;

/*
 * Control to disable digital zoom of the whole stream
 *
 * When it is true, pipe configuration enable_dz will be set to false.
 * This can help get a better perक्रमmance by disabling pp binary.
 *
 * Note: Make sure set this configuration beक्रमe creating stream.
 */
अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_disable_dz = अणु
	.id = V4L2_CID_DISABLE_DZ,
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.name = "Disable digital zoom",
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
पूर्ण;

/*
 * Control क्रम ISP depth mode
 *
 * When enabled, that means ISP will deal with dual streams and sensors will be
 * in slave/master mode.
 * slave sensor will have no output until master sensor is streamed on.
 */
अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_depth_mode = अणु
	.ops = &ctrl_ops,
	.id = V4L2_CID_DEPTH_MODE,
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.name = "Depth mode",
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
पूर्ण;

/*
 * Control क्रम selectting ISP version
 *
 * When enabled, that means ISP version will be used ISP2.7. when disable, the
 * isp will शेष to use ISP2.2.
 * Note: Make sure set this configuration beक्रमe creating stream.
 */
अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_select_isp_version = अणु
	.ops = &ctrl_ops,
	.id = V4L2_CID_ATOMISP_SELECT_ISP_VERSION,
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.name = "Select Isp version",
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
पूर्ण;

अटल व्योम atomisp_init_subdev_pipe(काष्ठा atomisp_sub_device *asd,
				     काष्ठा atomisp_video_pipe *pipe, क्रमागत v4l2_buf_type buf_type)
अणु
	pipe->type = buf_type;
	pipe->asd = asd;
	pipe->isp = asd->isp;
	spin_lock_init(&pipe->irq_lock);
	INIT_LIST_HEAD(&pipe->activeq);
	INIT_LIST_HEAD(&pipe->activeq_out);
	INIT_LIST_HEAD(&pipe->buffers_रुकोing_क्रम_param);
	INIT_LIST_HEAD(&pipe->per_frame_params);
	स_रखो(pipe->frame_request_config_id,
	       0, VIDEO_MAX_FRAME * माप(अचिन्हित पूर्णांक));
	स_रखो(pipe->frame_params,
	       0, VIDEO_MAX_FRAME *
	       माप(काष्ठा atomisp_css_params_with_list *));
पूर्ण

अटल व्योम atomisp_init_acc_pipe(काष्ठा atomisp_sub_device *asd,
				  काष्ठा atomisp_acc_pipe *pipe)
अणु
	pipe->asd = asd;
	pipe->isp = asd->isp;
	INIT_LIST_HEAD(&asd->acc.fw);
	INIT_LIST_HEAD(&asd->acc.memory_maps);
	ida_init(&asd->acc.ida);
पूर्ण

/*
 * isp_subdev_init_entities - Initialize V4L2 subdev and media entity
 * @asd: ISP CCDC module
 *
 * Return 0 on success and a negative error code on failure.
 */
अटल पूर्णांक isp_subdev_init_entities(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा v4l2_subdev *sd = &asd->subdev;
	काष्ठा media_pad *pads = asd->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	asd->input = ATOMISP_SUBDEV_INPUT_NONE;

	v4l2_subdev_init(sd, &isp_subdev_v4l2_ops);
	प्र_लिखो(sd->name, "ATOMISP_SUBDEV_%d", asd->index);
	v4l2_set_subdevdata(sd, asd);
	sd->flags |= V4L2_SUBDEV_FL_HAS_EVENTS | V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[ATOMISP_SUBDEV_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW].flags = MEDIA_PAD_FL_SOURCE;
	pads[ATOMISP_SUBDEV_PAD_SOURCE_VF].flags = MEDIA_PAD_FL_SOURCE;
	pads[ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE].flags = MEDIA_PAD_FL_SOURCE;
	pads[ATOMISP_SUBDEV_PAD_SOURCE_VIDEO].flags = MEDIA_PAD_FL_SOURCE;

	asd->fmt[ATOMISP_SUBDEV_PAD_SINK].fmt.code =
	    MEDIA_BUS_FMT_SBGGR10_1X10;
	asd->fmt[ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW].fmt.code =
	    MEDIA_BUS_FMT_SBGGR10_1X10;
	asd->fmt[ATOMISP_SUBDEV_PAD_SOURCE_VF].fmt.code =
	    MEDIA_BUS_FMT_SBGGR10_1X10;
	asd->fmt[ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE].fmt.code =
	    MEDIA_BUS_FMT_SBGGR10_1X10;
	asd->fmt[ATOMISP_SUBDEV_PAD_SOURCE_VIDEO].fmt.code =
	    MEDIA_BUS_FMT_SBGGR10_1X10;

	me->ops = &isp_subdev_media_ops;
	me->function = MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN;
	ret = media_entity_pads_init(me, ATOMISP_SUBDEV_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	atomisp_init_subdev_pipe(asd, &asd->video_in,
				 V4L2_BUF_TYPE_VIDEO_OUTPUT);

	atomisp_init_subdev_pipe(asd, &asd->video_out_preview,
				 V4L2_BUF_TYPE_VIDEO_CAPTURE);

	atomisp_init_subdev_pipe(asd, &asd->video_out_vf,
				 V4L2_BUF_TYPE_VIDEO_CAPTURE);

	atomisp_init_subdev_pipe(asd, &asd->video_out_capture,
				 V4L2_BUF_TYPE_VIDEO_CAPTURE);

	atomisp_init_subdev_pipe(asd, &asd->video_out_video_capture,
				 V4L2_BUF_TYPE_VIDEO_CAPTURE);

	atomisp_init_acc_pipe(asd, &asd->video_acc);

	ret = atomisp_video_init(&asd->video_in, "MEMORY");
	अगर (ret < 0)
		वापस ret;

	ret = atomisp_video_init(&asd->video_out_capture, "CAPTURE");
	अगर (ret < 0)
		वापस ret;

	ret = atomisp_video_init(&asd->video_out_vf, "VIEWFINDER");
	अगर (ret < 0)
		वापस ret;

	ret = atomisp_video_init(&asd->video_out_preview, "PREVIEW");
	अगर (ret < 0)
		वापस ret;

	ret = atomisp_video_init(&asd->video_out_video_capture, "VIDEO");
	अगर (ret < 0)
		वापस ret;

	atomisp_acc_init(&asd->video_acc, "ACC");

	ret = v4l2_ctrl_handler_init(&asd->ctrl_handler, 1);
	अगर (ret)
		वापस ret;

	asd->fmt_स्वतः = v4l2_ctrl_new_custom(&asd->ctrl_handler,
					     &ctrl_fmt_स्वतः, शून्य);
	asd->run_mode = v4l2_ctrl_new_custom(&asd->ctrl_handler,
					     &ctrl_run_mode, शून्य);
	asd->vfpp = v4l2_ctrl_new_custom(&asd->ctrl_handler,
					 &ctrl_vfpp, शून्य);
	asd->continuous_mode = v4l2_ctrl_new_custom(&asd->ctrl_handler,
			       &ctrl_continuous_mode, शून्य);
	asd->continuous_viewfinder = v4l2_ctrl_new_custom(&asd->ctrl_handler,
				     &ctrl_continuous_viewfinder,
				     शून्य);
	asd->continuous_raw_buffer_size =
	    v4l2_ctrl_new_custom(&asd->ctrl_handler,
				 &ctrl_continuous_raw_buffer_size,
				 शून्य);

	asd->enable_raw_buffer_lock =
	    v4l2_ctrl_new_custom(&asd->ctrl_handler,
				 &ctrl_enable_raw_buffer_lock,
				 शून्य);
	asd->depth_mode =
	    v4l2_ctrl_new_custom(&asd->ctrl_handler,
				 &ctrl_depth_mode,
				 शून्य);
	asd->disable_dz =
	    v4l2_ctrl_new_custom(&asd->ctrl_handler,
				 &ctrl_disable_dz,
				 शून्य);
	अगर (IS_ISP2401) अणु
		asd->select_isp_version = v4l2_ctrl_new_custom(&asd->ctrl_handler,
							       &ctrl_select_isp_version,
							       शून्य);
	पूर्ण

	/* Make controls visible on subdev as well. */
	asd->subdev.ctrl_handler = &asd->ctrl_handler;
	spin_lock_init(&asd->raw_buffer_biपंचांगap_lock);
	वापस asd->ctrl_handler.error;
पूर्ण

पूर्णांक atomisp_create_pads_links(काष्ठा atomisp_device *isp)
अणु
	काष्ठा atomisp_sub_device *asd;
	पूर्णांक i, j, ret = 0;

	isp->num_of_streams = 2;
	क्रम (i = 0; i < ATOMISP_CAMERA_NR_PORTS; i++) अणु
		क्रम (j = 0; j < isp->num_of_streams; j++) अणु
			ret =
			    media_create_pad_link(&isp->csi2_port[i].subdev.
						  entity, CSI2_PAD_SOURCE,
						  &isp->asd[j].subdev.entity,
						  ATOMISP_SUBDEV_PAD_SINK, 0);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < isp->input_cnt - 2; i++) अणु
		ret = media_create_pad_link(&isp->inमाला_दो[i].camera->entity, 0,
					    &isp->csi2_port[isp->inमाला_दो[i].
						    port].subdev.entity,
					    CSI2_PAD_SINK,
					    MEDIA_LNK_FL_ENABLED |
					    MEDIA_LNK_FL_IMMUTABLE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		asd = &isp->asd[i];
		ret = media_create_pad_link(&asd->subdev.entity,
					    ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW,
					    &asd->video_out_preview.vdev.entity,
					    0, 0);
		अगर (ret < 0)
			वापस ret;
		ret = media_create_pad_link(&asd->subdev.entity,
					    ATOMISP_SUBDEV_PAD_SOURCE_VF,
					    &asd->video_out_vf.vdev.entity, 0,
					    0);
		अगर (ret < 0)
			वापस ret;
		ret = media_create_pad_link(&asd->subdev.entity,
					    ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE,
					    &asd->video_out_capture.vdev.entity,
					    0, 0);
		अगर (ret < 0)
			वापस ret;
		ret = media_create_pad_link(&asd->subdev.entity,
					    ATOMISP_SUBDEV_PAD_SOURCE_VIDEO,
					    &asd->video_out_video_capture.vdev.
					    entity, 0, 0);
		अगर (ret < 0)
			वापस ret;
		/*
		 * file input only supported on subdev0
		 * so करो not create pad link क्रम subdevs other then subdev0
		 */
		अगर (asd->index)
			वापस 0;
		ret = media_create_pad_link(&asd->video_in.vdev.entity,
					    0, &asd->subdev.entity,
					    ATOMISP_SUBDEV_PAD_SINK, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम atomisp_subdev_cleanup_entities(काष्ठा atomisp_sub_device *asd)
अणु
	v4l2_ctrl_handler_मुक्त(&asd->ctrl_handler);

	media_entity_cleanup(&asd->subdev.entity);
पूर्ण

व्योम atomisp_subdev_cleanup_pending_events(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा v4l2_fh *fh, *fh_पंचांगp;
	काष्ठा v4l2_event event;
	अचिन्हित पूर्णांक i, pending_event;

	list_क्रम_each_entry_safe(fh, fh_पंचांगp,
				 &asd->subdev.devnode->fh_list, list) अणु
		pending_event = v4l2_event_pending(fh);
		क्रम (i = 0; i < pending_event; i++)
			v4l2_event_dequeue(fh, &event, 1);
	पूर्ण
पूर्ण

व्योम atomisp_subdev_unरेजिस्टर_entities(काष्ठा atomisp_sub_device *asd)
अणु
	atomisp_subdev_cleanup_entities(asd);
	v4l2_device_unरेजिस्टर_subdev(&asd->subdev);
	atomisp_video_unरेजिस्टर(&asd->video_in);
	atomisp_video_unरेजिस्टर(&asd->video_out_preview);
	atomisp_video_unरेजिस्टर(&asd->video_out_vf);
	atomisp_video_unरेजिस्टर(&asd->video_out_capture);
	atomisp_video_unरेजिस्टर(&asd->video_out_video_capture);
	atomisp_acc_unरेजिस्टर(&asd->video_acc);
पूर्ण

पूर्णांक atomisp_subdev_रेजिस्टर_entities(काष्ठा atomisp_sub_device *asd,
				     काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;
	u32 device_caps;

	/*
	 * FIXME: check अगर all device caps are properly initialized.
	 * Should any of those use V4L2_CAP_META_OUTPUT? Probably yes.
	 */

	device_caps = V4L2_CAP_VIDEO_CAPTURE |
		      V4L2_CAP_STREAMING;

	/* Register the subdev and video node. */

	ret = v4l2_device_रेजिस्टर_subdev(vdev, &asd->subdev);
	अगर (ret < 0)
		जाओ error;

	asd->video_out_capture.vdev.v4l2_dev = vdev;
	asd->video_out_capture.vdev.device_caps = device_caps |
						  V4L2_CAP_VIDEO_OUTPUT;
	ret = video_रेजिस्टर_device(&asd->video_out_capture.vdev,
				    VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		जाओ error;

	asd->video_out_vf.vdev.v4l2_dev = vdev;
	asd->video_out_vf.vdev.device_caps = device_caps |
					     V4L2_CAP_VIDEO_OUTPUT;
	ret = video_रेजिस्टर_device(&asd->video_out_vf.vdev,
				    VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		जाओ error;
	asd->video_out_preview.vdev.v4l2_dev = vdev;
	asd->video_out_preview.vdev.device_caps = device_caps |
						  V4L2_CAP_VIDEO_OUTPUT;
	ret = video_रेजिस्टर_device(&asd->video_out_preview.vdev,
				    VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		जाओ error;
	asd->video_out_video_capture.vdev.v4l2_dev = vdev;
	asd->video_out_video_capture.vdev.device_caps = device_caps |
							V4L2_CAP_VIDEO_OUTPUT;
	ret = video_रेजिस्टर_device(&asd->video_out_video_capture.vdev,
				    VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		जाओ error;
	asd->video_acc.vdev.v4l2_dev = vdev;
	asd->video_acc.vdev.device_caps = device_caps |
					  V4L2_CAP_VIDEO_OUTPUT;
	ret = video_रेजिस्टर_device(&asd->video_acc.vdev,
				    VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		जाओ error;

	/*
	 * file input only supported on subdev0
	 * so करो not create video node क्रम subdevs other then subdev0
	 */
	अगर (asd->index)
		वापस 0;

	asd->video_in.vdev.v4l2_dev = vdev;
	asd->video_in.vdev.device_caps = device_caps |
					  V4L2_CAP_VIDEO_CAPTURE;
	ret = video_रेजिस्टर_device(&asd->video_in.vdev,
				    VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	atomisp_subdev_unरेजिस्टर_entities(asd);
	वापस ret;
पूर्ण

/*
 * atomisp_subdev_init - ISP Subdevice  initialization.
 * @dev: Device poपूर्णांकer specअगरic to the ATOM ISP.
 *
 * TODO: Get the initialisation values from platक्रमm data.
 *
 * Return 0 on success or a negative error code otherwise.
 */
पूर्णांक atomisp_subdev_init(काष्ठा atomisp_device *isp)
अणु
	काष्ठा atomisp_sub_device *asd;
	पूर्णांक i, ret = 0;

	/*
	 * CSS2.0 running ISP2400 support
	 * multiple streams
	 */
	isp->num_of_streams = 2;
	isp->asd = devm_kzalloc(isp->dev, माप(काष्ठा atomisp_sub_device) *
				isp->num_of_streams, GFP_KERNEL);
	अगर (!isp->asd)
		वापस -ENOMEM;
	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		asd = &isp->asd[i];
		spin_lock_init(&asd->lock);
		asd->isp = isp;
		isp_subdev_init_params(asd);
		asd->index = i;
		ret = isp_subdev_init_entities(asd);
		अगर (ret < 0) अणु
			atomisp_subdev_cleanup_entities(asd);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
