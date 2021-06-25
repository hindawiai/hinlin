<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Video IP Core
 *
 * Copyright (C) 2013-2015 Ideas on Board
 * Copyright (C) 2013-2015 Xilinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xilinx.com>
 *           Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/media/xilinx-vip.h>

#समावेश "xilinx-vip.h"

/* -----------------------------------------------------------------------------
 * Helper functions
 */

अटल स्थिर काष्ठा xvip_video_क्रमmat xvip_video_क्रमmats[] = अणु
	अणु XVIP_VF_YUV_422, 8, शून्य, MEDIA_BUS_FMT_UYVY8_1X16,
	  2, V4L2_PIX_FMT_YUYV पूर्ण,
	अणु XVIP_VF_YUV_444, 8, शून्य, MEDIA_BUS_FMT_VUY8_1X24,
	  3, V4L2_PIX_FMT_YUV444 पूर्ण,
	अणु XVIP_VF_RBG, 8, शून्य, MEDIA_BUS_FMT_RBG888_1X24,
	  3, 0 पूर्ण,
	अणु XVIP_VF_MONO_SENSOR, 8, "mono", MEDIA_BUS_FMT_Y8_1X8,
	  1, V4L2_PIX_FMT_GREY पूर्ण,
	अणु XVIP_VF_MONO_SENSOR, 8, "rggb", MEDIA_BUS_FMT_SRGGB8_1X8,
	  1, V4L2_PIX_FMT_SRGGB8 पूर्ण,
	अणु XVIP_VF_MONO_SENSOR, 8, "grbg", MEDIA_BUS_FMT_SGRBG8_1X8,
	  1, V4L2_PIX_FMT_SGRBG8 पूर्ण,
	अणु XVIP_VF_MONO_SENSOR, 8, "gbrg", MEDIA_BUS_FMT_SGBRG8_1X8,
	  1, V4L2_PIX_FMT_SGBRG8 पूर्ण,
	अणु XVIP_VF_MONO_SENSOR, 8, "bggr", MEDIA_BUS_FMT_SBGGR8_1X8,
	  1, V4L2_PIX_FMT_SBGGR8 पूर्ण,
पूर्ण;

/**
 * xvip_get_क्रमmat_by_code - Retrieve क्रमmat inक्रमmation क्रम a media bus code
 * @code: the क्रमmat media bus code
 *
 * Return: a poपूर्णांकer to the क्रमmat inक्रमmation काष्ठाure corresponding to the
 * given V4L2 media bus क्रमmat @code, or ERR_PTR अगर no corresponding क्रमmat can
 * be found.
 */
स्थिर काष्ठा xvip_video_क्रमmat *xvip_get_क्रमmat_by_code(अचिन्हित पूर्णांक code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xvip_video_क्रमmats); ++i) अणु
		स्थिर काष्ठा xvip_video_क्रमmat *क्रमmat = &xvip_video_क्रमmats[i];

		अगर (क्रमmat->code == code)
			वापस क्रमmat;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण
EXPORT_SYMBOL_GPL(xvip_get_क्रमmat_by_code);

/**
 * xvip_get_क्रमmat_by_fourcc - Retrieve क्रमmat inक्रमmation क्रम a 4CC
 * @fourcc: the क्रमmat 4CC
 *
 * Return: a poपूर्णांकer to the क्रमmat inक्रमmation काष्ठाure corresponding to the
 * given V4L2 क्रमmat @fourcc, or ERR_PTR अगर no corresponding क्रमmat can be
 * found.
 */
स्थिर काष्ठा xvip_video_क्रमmat *xvip_get_क्रमmat_by_fourcc(u32 fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xvip_video_क्रमmats); ++i) अणु
		स्थिर काष्ठा xvip_video_क्रमmat *क्रमmat = &xvip_video_क्रमmats[i];

		अगर (क्रमmat->fourcc == fourcc)
			वापस क्रमmat;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण
EXPORT_SYMBOL_GPL(xvip_get_क्रमmat_by_fourcc);

/**
 * xvip_of_get_क्रमmat - Parse a device tree node and वापस क्रमmat inक्रमmation
 * @node: the device tree node
 *
 * Read the xlnx,video-क्रमmat, xlnx,video-width and xlnx,cfa-pattern properties
 * from the device tree @node passed as an argument and वापस the corresponding
 * क्रमmat inक्रमmation.
 *
 * Return: a poपूर्णांकer to the क्रमmat inक्रमmation काष्ठाure corresponding to the
 * क्रमmat name and width, or ERR_PTR अगर no corresponding क्रमmat can be found.
 */
स्थिर काष्ठा xvip_video_क्रमmat *xvip_of_get_क्रमmat(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *pattern = "mono";
	अचिन्हित पूर्णांक vf_code;
	अचिन्हित पूर्णांक i;
	u32 width;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(node, "xlnx,video-format", &vf_code);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	ret = of_property_पढ़ो_u32(node, "xlnx,video-width", &width);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	अगर (vf_code == XVIP_VF_MONO_SENSOR)
		of_property_पढ़ो_string(node, "xlnx,cfa-pattern", &pattern);

	क्रम (i = 0; i < ARRAY_SIZE(xvip_video_क्रमmats); ++i) अणु
		स्थिर काष्ठा xvip_video_क्रमmat *क्रमmat = &xvip_video_क्रमmats[i];

		अगर (क्रमmat->vf_code != vf_code || क्रमmat->width != width)
			जारी;

		अगर (vf_code == XVIP_VF_MONO_SENSOR &&
		    म_भेद(pattern, क्रमmat->pattern))
			जारी;

		वापस क्रमmat;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण
EXPORT_SYMBOL_GPL(xvip_of_get_क्रमmat);

/**
 * xvip_set_क्रमmat_size - Set the media bus frame क्रमmat size
 * @क्रमmat: V4L2 frame क्रमmat on media bus
 * @fmt: media bus क्रमmat
 *
 * Set the media bus frame क्रमmat size. The width / height from the subdevice
 * क्रमmat are set to the given media bus क्रमmat. The new क्रमmat size is stored
 * in @क्रमmat. The width and height are clamped using शेष min / max values.
 */
व्योम xvip_set_क्रमmat_size(काष्ठा v4l2_mbus_framefmt *क्रमmat,
			  स्थिर काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	क्रमmat->width = clamp_t(अचिन्हित पूर्णांक, fmt->क्रमmat.width,
				XVIP_MIN_WIDTH, XVIP_MAX_WIDTH);
	क्रमmat->height = clamp_t(अचिन्हित पूर्णांक, fmt->क्रमmat.height,
			 XVIP_MIN_HEIGHT, XVIP_MAX_HEIGHT);
पूर्ण
EXPORT_SYMBOL_GPL(xvip_set_क्रमmat_size);

/**
 * xvip_clr_or_set - Clear or set the रेजिस्टर with a biपंचांगask
 * @xvip: Xilinx Video IP device
 * @addr: address of रेजिस्टर
 * @mask: biपंचांगask to be set or cleared
 * @set: boolean flag indicating whether to set or clear
 *
 * Clear or set the रेजिस्टर at address @addr with a biपंचांगask @mask depending on
 * the boolean flag @set. When the flag @set is true, the biपंचांगask is set in
 * the रेजिस्टर, otherwise the biपंचांगask is cleared from the रेजिस्टर
 * when the flag @set is false.
 *
 * Fox example, this function can be used to set a control with a boolean value
 * requested by users. If the caller knows whether to set or clear in the first
 * place, the caller should call xvip_clr() or xvip_set() directly instead of
 * using this function.
 */
व्योम xvip_clr_or_set(काष्ठा xvip_device *xvip, u32 addr, u32 mask, bool set)
अणु
	u32 reg;

	reg = xvip_पढ़ो(xvip, addr);
	reg = set ? reg | mask : reg & ~mask;
	xvip_ग_लिखो(xvip, addr, reg);
पूर्ण
EXPORT_SYMBOL_GPL(xvip_clr_or_set);

/**
 * xvip_clr_and_set - Clear and set the रेजिस्टर with a biपंचांगask
 * @xvip: Xilinx Video IP device
 * @addr: address of रेजिस्टर
 * @clr: biपंचांगask to be cleared
 * @set: biपंचांगask to be set
 *
 * Clear a bit(s) of mask @clr in the रेजिस्टर at address @addr, then set
 * a bit(s) of mask @set in the रेजिस्टर after.
 */
व्योम xvip_clr_and_set(काष्ठा xvip_device *xvip, u32 addr, u32 clr, u32 set)
अणु
	u32 reg;

	reg = xvip_पढ़ो(xvip, addr);
	reg &= ~clr;
	reg |= set;
	xvip_ग_लिखो(xvip, addr, reg);
पूर्ण
EXPORT_SYMBOL_GPL(xvip_clr_and_set);

पूर्णांक xvip_init_resources(काष्ठा xvip_device *xvip)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(xvip->dev);
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	xvip->iomem = devm_ioremap_resource(xvip->dev, res);
	अगर (IS_ERR(xvip->iomem))
		वापस PTR_ERR(xvip->iomem);

	xvip->clk = devm_clk_get(xvip->dev, शून्य);
	अगर (IS_ERR(xvip->clk))
		वापस PTR_ERR(xvip->clk);

	clk_prepare_enable(xvip->clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xvip_init_resources);

व्योम xvip_cleanup_resources(काष्ठा xvip_device *xvip)
अणु
	clk_disable_unprepare(xvip->clk);
पूर्ण
EXPORT_SYMBOL_GPL(xvip_cleanup_resources);

/* -----------------------------------------------------------------------------
 * Subdev operations handlers
 */

/**
 * xvip_क्रमागत_mbus_code - Enumerate the media क्रमmat code
 * @subdev: V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @code: वापसing media bus code
 *
 * Enumerate the media bus code of the subdevice. Return the corresponding
 * pad क्रमmat code. This function only works क्रम subdevices with fixed क्रमmat
 * on all pads. Subdevices with multiple क्रमmat should have their own
 * function to क्रमागतerate mbus codes.
 *
 * Return: 0 अगर the media bus code is found, or -EINVAL अगर the क्रमmat index
 * is not valid.
 */
पूर्णांक xvip_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	/* Enumerating frame sizes based on the active configuration isn't
	 * supported yet.
	 */
	अगर (code->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	अगर (code->index)
		वापस -EINVAL;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(subdev, cfg, code->pad);

	code->code = क्रमmat->code;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xvip_क्रमागत_mbus_code);

/**
 * xvip_क्रमागत_frame_size - Enumerate the media bus frame size
 * @subdev: V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fse: वापसing media bus frame size
 *
 * This function is a drop-in implementation of the subdev क्रमागत_frame_size pad
 * operation. It assumes that the subdevice has one sink pad and one source
 * pad, and that the क्रमmat on the source pad is always identical to the
 * क्रमmat on the sink pad. Entities with dअगरferent requirements need to
 * implement their own क्रमागत_frame_size handlers.
 *
 * Return: 0 अगर the media bus frame size is found, or -EINVAL
 * अगर the index or the code is not valid.
 */
पूर्णांक xvip_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
			 काष्ठा v4l2_subdev_pad_config *cfg,
			 काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	/* Enumerating frame sizes based on the active configuration isn't
	 * supported yet.
	 */
	अगर (fse->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(subdev, cfg, fse->pad);

	अगर (fse->index || fse->code != क्रमmat->code)
		वापस -EINVAL;

	अगर (fse->pad == XVIP_PAD_SINK) अणु
		fse->min_width = XVIP_MIN_WIDTH;
		fse->max_width = XVIP_MAX_WIDTH;
		fse->min_height = XVIP_MIN_HEIGHT;
		fse->max_height = XVIP_MAX_HEIGHT;
	पूर्ण अन्यथा अणु
		/* The size on the source pad is fixed and always identical to
		 * the size on the sink pad.
		 */
		fse->min_width = क्रमmat->width;
		fse->max_width = क्रमmat->width;
		fse->min_height = क्रमmat->height;
		fse->max_height = क्रमmat->height;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xvip_क्रमागत_frame_size);
