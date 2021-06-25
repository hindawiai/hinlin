<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vimc-common.c Virtual Media Controller Driver
 *
 * Copyright (C) 2015-2017 Helen Koike <helen.क्रमnazier@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश "vimc-common.h"

/*
 * NOTE: non-bayer क्रमmats need to come first (necessary क्रम क्रमागत_mbus_code
 * in the scaler)
 */
अटल स्थिर काष्ठा vimc_pix_map vimc_pix_map_list[] = अणु
	/* TODO: add all missing क्रमmats */

	/* RGB क्रमmats */
	अणु
		.code = अणु
			MEDIA_BUS_FMT_BGR888_1X24,
			MEDIA_BUS_FMT_BGR888_3X8
		पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_BGR24,
		.bpp = 3,
		.bayer = false,
	पूर्ण,
	अणु
		.code = अणु
			MEDIA_BUS_FMT_RGB888_1X24,
			MEDIA_BUS_FMT_RGB888_2X12_BE,
			MEDIA_BUS_FMT_RGB888_2X12_LE,
			MEDIA_BUS_FMT_RGB888_3X8,
			MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
			MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA,
			MEDIA_BUS_FMT_RGB888_1X32_PADHI,
			MEDIA_BUS_FMT_GBR888_1X24
		पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_RGB24,
		.bpp = 3,
		.bayer = false,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_ARGB8888_1X32 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_ARGB32,
		.bpp = 4,
		.bayer = false,
	पूर्ण,

	/* Bayer क्रमmats */
	अणु
		.code = अणु MEDIA_BUS_FMT_SBGGR8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGBRG8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGBRG8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGRBG8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGRBG8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SRGGB8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SRGGB8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SBGGR10_1X10 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR10,
		.bpp = 2,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGBRG10_1X10 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGBRG10,
		.bpp = 2,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGRBG10_1X10 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGRBG10,
		.bpp = 2,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SRGGB10_1X10 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SRGGB10,
		.bpp = 2,
		.bayer = true,
	पूर्ण,

	/* 10bit raw bayer a-law compressed to 8 bits */
	अणु
		.code = अणु MEDIA_BUS_FMT_SBGGR10_ALAW8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR10ALAW8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGBRG10_ALAW8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGBRG10ALAW8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGRBG10ALAW8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SRGGB10_ALAW8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SRGGB10ALAW8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,

	/* 10bit raw bayer DPCM compressed to 8 bits */
	अणु
		.code = अणु MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR10DPCM8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGBRG10DPCM8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGRBG10DPCM8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SRGGB10DPCM8,
		.bpp = 1,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SBGGR12_1X12 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR12,
		.bpp = 2,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGBRG12_1X12 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGBRG12,
		.bpp = 2,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SGRBG12_1X12 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SGRBG12,
		.bpp = 2,
		.bayer = true,
	पूर्ण,
	अणु
		.code = अणु MEDIA_BUS_FMT_SRGGB12_1X12 पूर्ण,
		.pixelक्रमmat = V4L2_PIX_FMT_SRGGB12,
		.bpp = 2,
		.bayer = true,
	पूर्ण,
पूर्ण;

bool vimc_is_source(काष्ठा media_entity *ent)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ent->num_pads; i++)
		अगर (ent->pads[i].flags & MEDIA_PAD_FL_SINK)
			वापस false;
	वापस true;
पूर्ण

स्थिर काष्ठा vimc_pix_map *vimc_pix_map_by_index(अचिन्हित पूर्णांक i)
अणु
	अगर (i >= ARRAY_SIZE(vimc_pix_map_list))
		वापस शून्य;

	वापस &vimc_pix_map_list[i];
पूर्ण

u32 vimc_mbus_code_by_index(अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(vimc_pix_map_list); i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(vimc_pix_map_list[i].code); j++) अणु
			अगर (!vimc_pix_map_list[i].code[j])
				अवरोध;

			अगर (!index)
				वापस vimc_pix_map_list[i].code[j];
			index--;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा vimc_pix_map *vimc_pix_map_by_code(u32 code)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(vimc_pix_map_list); i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(vimc_pix_map_list[i].code); j++) अणु
			अगर (vimc_pix_map_list[i].code[j] == code)
				वापस &vimc_pix_map_list[i];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

स्थिर काष्ठा vimc_pix_map *vimc_pix_map_by_pixelक्रमmat(u32 pixelक्रमmat)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vimc_pix_map_list); i++) अणु
		अगर (vimc_pix_map_list[i].pixelक्रमmat == pixelक्रमmat)
			वापस &vimc_pix_map_list[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक vimc_get_pix_क्रमmat(काष्ठा media_pad *pad,
			       काष्ठा v4l2_pix_क्रमmat *fmt)
अणु
	अगर (is_media_entity_v4l2_subdev(pad->entity)) अणु
		काष्ठा v4l2_subdev *sd =
			media_entity_to_v4l2_subdev(pad->entity);
		काष्ठा v4l2_subdev_क्रमmat sd_fmt;
		स्थिर काष्ठा vimc_pix_map *pix_map;
		पूर्णांक ret;

		sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		sd_fmt.pad = pad->index;

		ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य, &sd_fmt);
		अगर (ret)
			वापस ret;

		v4l2_fill_pix_क्रमmat(fmt, &sd_fmt.क्रमmat);
		pix_map = vimc_pix_map_by_code(sd_fmt.क्रमmat.code);
		fmt->pixelक्रमmat = pix_map->pixelक्रमmat;
	पूर्ण अन्यथा अगर (is_media_entity_v4l2_video_device(pad->entity)) अणु
		काष्ठा video_device *vdev = container_of(pad->entity,
							 काष्ठा video_device,
							 entity);
		काष्ठा vimc_ent_device *ved = video_get_drvdata(vdev);

		अगर (!ved->vdev_get_क्रमmat)
			वापस -ENOIOCTLCMD;

		ved->vdev_get_क्रमmat(ved, fmt);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vimc_vdev_link_validate(काष्ठा media_link *link)
अणु
	काष्ठा v4l2_pix_क्रमmat source_fmt, sink_fmt;
	पूर्णांक ret;

	ret = vimc_get_pix_क्रमmat(link->source, &source_fmt);
	अगर (ret)
		वापस ret;

	ret = vimc_get_pix_क्रमmat(link->sink, &sink_fmt);
	अगर (ret)
		वापस ret;

	pr_info("vimc link validate: "
		"%s:src:%dx%d (0x%x, %d, %d, %d, %d) "
		"%s:snk:%dx%d (0x%x, %d, %d, %d, %d)\n",
		/* src */
		link->source->entity->name,
		source_fmt.width, source_fmt.height,
		source_fmt.pixelक्रमmat, source_fmt.colorspace,
		source_fmt.quantization, source_fmt.xfer_func,
		source_fmt.ycbcr_enc,
		/* sink */
		link->sink->entity->name,
		sink_fmt.width, sink_fmt.height,
		sink_fmt.pixelक्रमmat, sink_fmt.colorspace,
		sink_fmt.quantization, sink_fmt.xfer_func,
		sink_fmt.ycbcr_enc);

	/* The width, height and pixelक्रमmat must match. */
	अगर (source_fmt.width != sink_fmt.width ||
	    source_fmt.height != sink_fmt.height ||
	    source_fmt.pixelक्रमmat != sink_fmt.pixelक्रमmat)
		वापस -EPIPE;

	/*
	 * The field order must match, or the sink field order must be NONE
	 * to support पूर्णांकerlaced hardware connected to bridges that support
	 * progressive क्रमmats only.
	 */
	अगर (source_fmt.field != sink_fmt.field &&
	    sink_fmt.field != V4L2_FIELD_NONE)
		वापस -EPIPE;

	/*
	 * If colorspace is DEFAULT, then assume all the colorimetry is also
	 * DEFAULT, वापस 0 to skip comparing the other colorimetry parameters
	 */
	अगर (source_fmt.colorspace == V4L2_COLORSPACE_DEFAULT ||
	    sink_fmt.colorspace == V4L2_COLORSPACE_DEFAULT)
		वापस 0;

	/* Colorspace must match. */
	अगर (source_fmt.colorspace != sink_fmt.colorspace)
		वापस -EPIPE;

	/* Colorimetry must match अगर they are not set to DEFAULT */
	अगर (source_fmt.ycbcr_enc != V4L2_YCBCR_ENC_DEFAULT &&
	    sink_fmt.ycbcr_enc != V4L2_YCBCR_ENC_DEFAULT &&
	    source_fmt.ycbcr_enc != sink_fmt.ycbcr_enc)
		वापस -EPIPE;

	अगर (source_fmt.quantization != V4L2_QUANTIZATION_DEFAULT &&
	    sink_fmt.quantization != V4L2_QUANTIZATION_DEFAULT &&
	    source_fmt.quantization != sink_fmt.quantization)
		वापस -EPIPE;

	अगर (source_fmt.xfer_func != V4L2_XFER_FUNC_DEFAULT &&
	    sink_fmt.xfer_func != V4L2_XFER_FUNC_DEFAULT &&
	    source_fmt.xfer_func != sink_fmt.xfer_func)
		वापस -EPIPE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा media_entity_operations vimc_ent_sd_mops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

पूर्णांक vimc_ent_sd_रेजिस्टर(काष्ठा vimc_ent_device *ved,
			 काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_device *v4l2_dev,
			 स्थिर अक्षर *स्थिर name,
			 u32 function,
			 u16 num_pads,
			 काष्ठा media_pad *pads,
			 स्थिर काष्ठा v4l2_subdev_ops *sd_ops)
अणु
	पूर्णांक ret;

	/* Fill the vimc_ent_device काष्ठा */
	ved->ent = &sd->entity;

	/* Initialize the subdev */
	v4l2_subdev_init(sd, sd_ops);
	sd->entity.function = function;
	sd->entity.ops = &vimc_ent_sd_mops;
	sd->owner = THIS_MODULE;
	strscpy(sd->name, name, माप(sd->name));
	v4l2_set_subdevdata(sd, ved);

	/* Expose this subdev to user space */
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	अगर (sd->ctrl_handler)
		sd->flags |= V4L2_SUBDEV_FL_HAS_EVENTS;

	/* Initialize the media entity */
	ret = media_entity_pads_init(&sd->entity, num_pads, pads);
	अगर (ret)
		वापस ret;

	/* Register the subdev with the v4l2 and the media framework */
	ret = v4l2_device_रेजिस्टर_subdev(v4l2_dev, sd);
	अगर (ret) अणु
		dev_err(v4l2_dev->dev,
			"%s: subdev register failed (err=%d)\n",
			name, ret);
		जाओ err_clean_m_ent;
	पूर्ण

	वापस 0;

err_clean_m_ent:
	media_entity_cleanup(&sd->entity);
	वापस ret;
पूर्ण
