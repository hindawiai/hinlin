<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2011-2018 Magewell Electronics Co., Ltd. (Nanjing)
 * All rights reserved.
 * Author: Yong Deng <yong.deng@magewell.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/sched.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>

#समावेश "sun6i_csi.h"
#समावेश "sun6i_csi_reg.h"

#घोषणा MODULE_NAME	"sun6i-csi"

काष्ठा sun6i_csi_dev अणु
	काष्ठा sun6i_csi		csi;
	काष्ठा device			*dev;

	काष्ठा regmap			*regmap;
	काष्ठा clk			*clk_mod;
	काष्ठा clk			*clk_ram;
	काष्ठा reset_control		*rstc_bus;

	पूर्णांक				planar_offset[3];
पूर्ण;

अटल अंतरभूत काष्ठा sun6i_csi_dev *sun6i_csi_to_dev(काष्ठा sun6i_csi *csi)
अणु
	वापस container_of(csi, काष्ठा sun6i_csi_dev, csi);
पूर्ण

/* TODO add 10&12 bit YUV, RGB support */
bool sun6i_csi_is_क्रमmat_supported(काष्ठा sun6i_csi *csi,
				   u32 pixक्रमmat, u32 mbus_code)
अणु
	काष्ठा sun6i_csi_dev *sdev = sun6i_csi_to_dev(csi);

	/*
	 * Some video receivers have the ability to be compatible with
	 * 8bit and 16bit bus width.
	 * Identअगरy the media bus क्रमmat from device tree.
	 */
	अगर ((sdev->csi.v4l2_ep.bus_type == V4L2_MBUS_PARALLEL
	     || sdev->csi.v4l2_ep.bus_type == V4L2_MBUS_BT656)
	     && sdev->csi.v4l2_ep.bus.parallel.bus_width == 16) अणु
		चयन (pixक्रमmat) अणु
		हाल V4L2_PIX_FMT_HM12:
		हाल V4L2_PIX_FMT_NV12:
		हाल V4L2_PIX_FMT_NV21:
		हाल V4L2_PIX_FMT_NV16:
		हाल V4L2_PIX_FMT_NV61:
		हाल V4L2_PIX_FMT_YUV420:
		हाल V4L2_PIX_FMT_YVU420:
		हाल V4L2_PIX_FMT_YUV422P:
			चयन (mbus_code) अणु
			हाल MEDIA_BUS_FMT_UYVY8_1X16:
			हाल MEDIA_BUS_FMT_VYUY8_1X16:
			हाल MEDIA_BUS_FMT_YUYV8_1X16:
			हाल MEDIA_BUS_FMT_YVYU8_1X16:
				वापस true;
			शेष:
				dev_dbg(sdev->dev, "Unsupported mbus code: 0x%x\n",
					mbus_code);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			dev_dbg(sdev->dev, "Unsupported pixformat: 0x%x\n",
				pixक्रमmat);
			अवरोध;
		पूर्ण
		वापस false;
	पूर्ण

	चयन (pixक्रमmat) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
		वापस (mbus_code == MEDIA_BUS_FMT_SBGGR8_1X8);
	हाल V4L2_PIX_FMT_SGBRG8:
		वापस (mbus_code == MEDIA_BUS_FMT_SGBRG8_1X8);
	हाल V4L2_PIX_FMT_SGRBG8:
		वापस (mbus_code == MEDIA_BUS_FMT_SGRBG8_1X8);
	हाल V4L2_PIX_FMT_SRGGB8:
		वापस (mbus_code == MEDIA_BUS_FMT_SRGGB8_1X8);
	हाल V4L2_PIX_FMT_SBGGR10:
		वापस (mbus_code == MEDIA_BUS_FMT_SBGGR10_1X10);
	हाल V4L2_PIX_FMT_SGBRG10:
		वापस (mbus_code == MEDIA_BUS_FMT_SGBRG10_1X10);
	हाल V4L2_PIX_FMT_SGRBG10:
		वापस (mbus_code == MEDIA_BUS_FMT_SGRBG10_1X10);
	हाल V4L2_PIX_FMT_SRGGB10:
		वापस (mbus_code == MEDIA_BUS_FMT_SRGGB10_1X10);
	हाल V4L2_PIX_FMT_SBGGR12:
		वापस (mbus_code == MEDIA_BUS_FMT_SBGGR12_1X12);
	हाल V4L2_PIX_FMT_SGBRG12:
		वापस (mbus_code == MEDIA_BUS_FMT_SGBRG12_1X12);
	हाल V4L2_PIX_FMT_SGRBG12:
		वापस (mbus_code == MEDIA_BUS_FMT_SGRBG12_1X12);
	हाल V4L2_PIX_FMT_SRGGB12:
		वापस (mbus_code == MEDIA_BUS_FMT_SRGGB12_1X12);

	हाल V4L2_PIX_FMT_YUYV:
		वापस (mbus_code == MEDIA_BUS_FMT_YUYV8_2X8);
	हाल V4L2_PIX_FMT_YVYU:
		वापस (mbus_code == MEDIA_BUS_FMT_YVYU8_2X8);
	हाल V4L2_PIX_FMT_UYVY:
		वापस (mbus_code == MEDIA_BUS_FMT_UYVY8_2X8);
	हाल V4L2_PIX_FMT_VYUY:
		वापस (mbus_code == MEDIA_BUS_FMT_VYUY8_2X8);

	हाल V4L2_PIX_FMT_HM12:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
	हाल V4L2_PIX_FMT_YUV422P:
		चयन (mbus_code) अणु
		हाल MEDIA_BUS_FMT_UYVY8_2X8:
		हाल MEDIA_BUS_FMT_VYUY8_2X8:
		हाल MEDIA_BUS_FMT_YUYV8_2X8:
		हाल MEDIA_BUS_FMT_YVYU8_2X8:
			वापस true;
		शेष:
			dev_dbg(sdev->dev, "Unsupported mbus code: 0x%x\n",
				mbus_code);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल V4L2_PIX_FMT_RGB565:
		वापस (mbus_code == MEDIA_BUS_FMT_RGB565_2X8_LE);
	हाल V4L2_PIX_FMT_RGB565X:
		वापस (mbus_code == MEDIA_BUS_FMT_RGB565_2X8_BE);

	हाल V4L2_PIX_FMT_JPEG:
		वापस (mbus_code == MEDIA_BUS_FMT_JPEG_1X8);

	शेष:
		dev_dbg(sdev->dev, "Unsupported pixformat: 0x%x\n", pixक्रमmat);
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक sun6i_csi_set_घातer(काष्ठा sun6i_csi *csi, bool enable)
अणु
	काष्ठा sun6i_csi_dev *sdev = sun6i_csi_to_dev(csi);
	काष्ठा device *dev = sdev->dev;
	काष्ठा regmap *regmap = sdev->regmap;
	पूर्णांक ret;

	अगर (!enable) अणु
		regmap_update_bits(regmap, CSI_EN_REG, CSI_EN_CSI_EN, 0);

		clk_disable_unprepare(sdev->clk_ram);
		अगर (of_device_is_compatible(dev->of_node,
					    "allwinner,sun50i-a64-csi"))
			clk_rate_exclusive_put(sdev->clk_mod);
		clk_disable_unprepare(sdev->clk_mod);
		reset_control_निश्चित(sdev->rstc_bus);
		वापस 0;
	पूर्ण

	ret = clk_prepare_enable(sdev->clk_mod);
	अगर (ret) अणु
		dev_err(sdev->dev, "Enable csi clk err %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (of_device_is_compatible(dev->of_node, "allwinner,sun50i-a64-csi"))
		clk_set_rate_exclusive(sdev->clk_mod, 300000000);

	ret = clk_prepare_enable(sdev->clk_ram);
	अगर (ret) अणु
		dev_err(sdev->dev, "Enable clk_dram_csi clk err %d\n", ret);
		जाओ clk_mod_disable;
	पूर्ण

	ret = reset_control_deनिश्चित(sdev->rstc_bus);
	अगर (ret) अणु
		dev_err(sdev->dev, "reset err %d\n", ret);
		जाओ clk_ram_disable;
	पूर्ण

	regmap_update_bits(regmap, CSI_EN_REG, CSI_EN_CSI_EN, CSI_EN_CSI_EN);

	वापस 0;

clk_ram_disable:
	clk_disable_unprepare(sdev->clk_ram);
clk_mod_disable:
	अगर (of_device_is_compatible(dev->of_node, "allwinner,sun50i-a64-csi"))
		clk_rate_exclusive_put(sdev->clk_mod);
	clk_disable_unprepare(sdev->clk_mod);
	वापस ret;
पूर्ण

अटल क्रमागत csi_input_fmt get_csi_input_क्रमmat(काष्ठा sun6i_csi_dev *sdev,
					       u32 mbus_code, u32 pixक्रमmat)
अणु
	/* non-YUV */
	अगर ((mbus_code & 0xF000) != 0x2000)
		वापस CSI_INPUT_FORMAT_RAW;

	चयन (pixक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_VYUY:
		वापस CSI_INPUT_FORMAT_RAW;
	शेष:
		अवरोध;
	पूर्ण

	/* not support YUV420 input क्रमmat yet */
	dev_dbg(sdev->dev, "Select YUV422 as default input format of CSI.\n");
	वापस CSI_INPUT_FORMAT_YUV422;
पूर्ण

अटल क्रमागत csi_output_fmt get_csi_output_क्रमmat(काष्ठा sun6i_csi_dev *sdev,
						 u32 pixक्रमmat, u32 field)
अणु
	bool buf_पूर्णांकerlaced = false;

	अगर (field == V4L2_FIELD_INTERLACED
	    || field == V4L2_FIELD_INTERLACED_TB
	    || field == V4L2_FIELD_INTERLACED_BT)
		buf_पूर्णांकerlaced = true;

	चयन (pixक्रमmat) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_RAW_8 : CSI_FIELD_RAW_8;
	हाल V4L2_PIX_FMT_SBGGR10:
	हाल V4L2_PIX_FMT_SGBRG10:
	हाल V4L2_PIX_FMT_SGRBG10:
	हाल V4L2_PIX_FMT_SRGGB10:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_RAW_10 : CSI_FIELD_RAW_10;
	हाल V4L2_PIX_FMT_SBGGR12:
	हाल V4L2_PIX_FMT_SGBRG12:
	हाल V4L2_PIX_FMT_SGRBG12:
	हाल V4L2_PIX_FMT_SRGGB12:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_RAW_12 : CSI_FIELD_RAW_12;

	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_VYUY:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_RAW_8 : CSI_FIELD_RAW_8;

	हाल V4L2_PIX_FMT_HM12:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_MB_YUV420 :
					CSI_FIELD_MB_YUV420;
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_UV_CB_YUV420 :
					CSI_FIELD_UV_CB_YUV420;
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_PLANAR_YUV420 :
					CSI_FIELD_PLANAR_YUV420;
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_UV_CB_YUV422 :
					CSI_FIELD_UV_CB_YUV422;
	हाल V4L2_PIX_FMT_YUV422P:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_PLANAR_YUV422 :
					CSI_FIELD_PLANAR_YUV422;

	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_RGB565X:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_RGB565 : CSI_FIELD_RGB565;

	हाल V4L2_PIX_FMT_JPEG:
		वापस buf_पूर्णांकerlaced ? CSI_FRAME_RAW_8 : CSI_FIELD_RAW_8;

	शेष:
		dev_warn(sdev->dev, "Unsupported pixformat: 0x%x\n", pixक्रमmat);
		अवरोध;
	पूर्ण

	वापस CSI_FIELD_RAW_8;
पूर्ण

अटल क्रमागत csi_input_seq get_csi_input_seq(काष्ठा sun6i_csi_dev *sdev,
					    u32 mbus_code, u32 pixक्रमmat)
अणु
	/* Input sequence करोes not apply to non-YUV क्रमmats */
	अगर ((mbus_code & 0xF000) != 0x2000)
		वापस 0;

	चयन (pixक्रमmat) अणु
	हाल V4L2_PIX_FMT_HM12:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YUV422P:
		चयन (mbus_code) अणु
		हाल MEDIA_BUS_FMT_UYVY8_2X8:
		हाल MEDIA_BUS_FMT_UYVY8_1X16:
			वापस CSI_INPUT_SEQ_UYVY;
		हाल MEDIA_BUS_FMT_VYUY8_2X8:
		हाल MEDIA_BUS_FMT_VYUY8_1X16:
			वापस CSI_INPUT_SEQ_VYUY;
		हाल MEDIA_BUS_FMT_YUYV8_2X8:
		हाल MEDIA_BUS_FMT_YUYV8_1X16:
			वापस CSI_INPUT_SEQ_YUYV;
		हाल MEDIA_BUS_FMT_YVYU8_1X16:
		हाल MEDIA_BUS_FMT_YVYU8_2X8:
			वापस CSI_INPUT_SEQ_YVYU;
		शेष:
			dev_warn(sdev->dev, "Unsupported mbus code: 0x%x\n",
				 mbus_code);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_YVU420:
		चयन (mbus_code) अणु
		हाल MEDIA_BUS_FMT_UYVY8_2X8:
		हाल MEDIA_BUS_FMT_UYVY8_1X16:
			वापस CSI_INPUT_SEQ_VYUY;
		हाल MEDIA_BUS_FMT_VYUY8_2X8:
		हाल MEDIA_BUS_FMT_VYUY8_1X16:
			वापस CSI_INPUT_SEQ_UYVY;
		हाल MEDIA_BUS_FMT_YUYV8_2X8:
		हाल MEDIA_BUS_FMT_YUYV8_1X16:
			वापस CSI_INPUT_SEQ_YVYU;
		हाल MEDIA_BUS_FMT_YVYU8_1X16:
		हाल MEDIA_BUS_FMT_YVYU8_2X8:
			वापस CSI_INPUT_SEQ_YUYV;
		शेष:
			dev_warn(sdev->dev, "Unsupported mbus code: 0x%x\n",
				 mbus_code);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल V4L2_PIX_FMT_YUYV:
		वापस CSI_INPUT_SEQ_YUYV;

	शेष:
		dev_warn(sdev->dev, "Unsupported pixformat: 0x%x, defaulting to YUYV\n",
			 pixक्रमmat);
		अवरोध;
	पूर्ण

	वापस CSI_INPUT_SEQ_YUYV;
पूर्ण

अटल व्योम sun6i_csi_setup_bus(काष्ठा sun6i_csi_dev *sdev)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक *endpoपूर्णांक = &sdev->csi.v4l2_ep;
	काष्ठा sun6i_csi *csi = &sdev->csi;
	अचिन्हित अक्षर bus_width;
	u32 flags;
	u32 cfg;
	bool input_पूर्णांकerlaced = false;

	अगर (csi->config.field == V4L2_FIELD_INTERLACED
	    || csi->config.field == V4L2_FIELD_INTERLACED_TB
	    || csi->config.field == V4L2_FIELD_INTERLACED_BT)
		input_पूर्णांकerlaced = true;

	bus_width = endpoपूर्णांक->bus.parallel.bus_width;

	regmap_पढ़ो(sdev->regmap, CSI_IF_CFG_REG, &cfg);

	cfg &= ~(CSI_IF_CFG_CSI_IF_MASK | CSI_IF_CFG_MIPI_IF_MASK |
		 CSI_IF_CFG_IF_DATA_WIDTH_MASK |
		 CSI_IF_CFG_CLK_POL_MASK | CSI_IF_CFG_VREF_POL_MASK |
		 CSI_IF_CFG_HREF_POL_MASK | CSI_IF_CFG_FIELD_MASK |
		 CSI_IF_CFG_SRC_TYPE_MASK);

	अगर (input_पूर्णांकerlaced)
		cfg |= CSI_IF_CFG_SRC_TYPE_INTERLACED;
	अन्यथा
		cfg |= CSI_IF_CFG_SRC_TYPE_PROGRESSED;

	चयन (endpoपूर्णांक->bus_type) अणु
	हाल V4L2_MBUS_PARALLEL:
		cfg |= CSI_IF_CFG_MIPI_IF_CSI;

		flags = endpoपूर्णांक->bus.parallel.flags;

		cfg |= (bus_width == 16) ? CSI_IF_CFG_CSI_IF_YUV422_16BIT :
					   CSI_IF_CFG_CSI_IF_YUV422_INTLV;

		अगर (flags & V4L2_MBUS_FIELD_EVEN_LOW)
			cfg |= CSI_IF_CFG_FIELD_POSITIVE;

		अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
			cfg |= CSI_IF_CFG_VREF_POL_POSITIVE;
		अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
			cfg |= CSI_IF_CFG_HREF_POL_POSITIVE;

		अगर (flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
			cfg |= CSI_IF_CFG_CLK_POL_FALLING_EDGE;
		अवरोध;
	हाल V4L2_MBUS_BT656:
		cfg |= CSI_IF_CFG_MIPI_IF_CSI;

		flags = endpoपूर्णांक->bus.parallel.flags;

		cfg |= (bus_width == 16) ? CSI_IF_CFG_CSI_IF_BT1120 :
					   CSI_IF_CFG_CSI_IF_BT656;

		अगर (flags & V4L2_MBUS_FIELD_EVEN_LOW)
			cfg |= CSI_IF_CFG_FIELD_POSITIVE;

		अगर (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
			cfg |= CSI_IF_CFG_CLK_POL_FALLING_EDGE;
		अवरोध;
	शेष:
		dev_warn(sdev->dev, "Unsupported bus type: %d\n",
			 endpoपूर्णांक->bus_type);
		अवरोध;
	पूर्ण

	चयन (bus_width) अणु
	हाल 8:
		cfg |= CSI_IF_CFG_IF_DATA_WIDTH_8BIT;
		अवरोध;
	हाल 10:
		cfg |= CSI_IF_CFG_IF_DATA_WIDTH_10BIT;
		अवरोध;
	हाल 12:
		cfg |= CSI_IF_CFG_IF_DATA_WIDTH_12BIT;
		अवरोध;
	हाल 16: /* No need to configure DATA_WIDTH क्रम 16bit */
		अवरोध;
	शेष:
		dev_warn(sdev->dev, "Unsupported bus width: %u\n", bus_width);
		अवरोध;
	पूर्ण

	regmap_ग_लिखो(sdev->regmap, CSI_IF_CFG_REG, cfg);
पूर्ण

अटल व्योम sun6i_csi_set_क्रमmat(काष्ठा sun6i_csi_dev *sdev)
अणु
	काष्ठा sun6i_csi *csi = &sdev->csi;
	u32 cfg;
	u32 val;

	regmap_पढ़ो(sdev->regmap, CSI_CH_CFG_REG, &cfg);

	cfg &= ~(CSI_CH_CFG_INPUT_FMT_MASK |
		 CSI_CH_CFG_OUTPUT_FMT_MASK | CSI_CH_CFG_VFLIP_EN |
		 CSI_CH_CFG_HFLIP_EN | CSI_CH_CFG_FIELD_SEL_MASK |
		 CSI_CH_CFG_INPUT_SEQ_MASK);

	val = get_csi_input_क्रमmat(sdev, csi->config.code,
				   csi->config.pixelक्रमmat);
	cfg |= CSI_CH_CFG_INPUT_FMT(val);

	val = get_csi_output_क्रमmat(sdev, csi->config.pixelक्रमmat,
				    csi->config.field);
	cfg |= CSI_CH_CFG_OUTPUT_FMT(val);

	val = get_csi_input_seq(sdev, csi->config.code,
				csi->config.pixelक्रमmat);
	cfg |= CSI_CH_CFG_INPUT_SEQ(val);

	अगर (csi->config.field == V4L2_FIELD_TOP)
		cfg |= CSI_CH_CFG_FIELD_SEL_FIELD0;
	अन्यथा अगर (csi->config.field == V4L2_FIELD_BOTTOM)
		cfg |= CSI_CH_CFG_FIELD_SEL_FIELD1;
	अन्यथा
		cfg |= CSI_CH_CFG_FIELD_SEL_BOTH;

	regmap_ग_लिखो(sdev->regmap, CSI_CH_CFG_REG, cfg);
पूर्ण

अटल व्योम sun6i_csi_set_winकरोw(काष्ठा sun6i_csi_dev *sdev)
अणु
	काष्ठा sun6i_csi_config *config = &sdev->csi.config;
	u32 bytesperline_y;
	u32 bytesperline_c;
	पूर्णांक *planar_offset = sdev->planar_offset;
	u32 width = config->width;
	u32 height = config->height;
	u32 hor_len = width;

	चयन (config->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_VYUY:
		dev_dbg(sdev->dev,
			"Horizontal length should be 2 times of width for packed YUV formats!\n");
		hor_len = width * 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	regmap_ग_लिखो(sdev->regmap, CSI_CH_HSIZE_REG,
		     CSI_CH_HSIZE_HOR_LEN(hor_len) |
		     CSI_CH_HSIZE_HOR_START(0));
	regmap_ग_लिखो(sdev->regmap, CSI_CH_VSIZE_REG,
		     CSI_CH_VSIZE_VER_LEN(height) |
		     CSI_CH_VSIZE_VER_START(0));

	planar_offset[0] = 0;
	चयन (config->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_HM12:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		bytesperline_y = width;
		bytesperline_c = width;
		planar_offset[1] = bytesperline_y * height;
		planar_offset[2] = -1;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
		bytesperline_y = width;
		bytesperline_c = width / 2;
		planar_offset[1] = bytesperline_y * height;
		planar_offset[2] = planar_offset[1] +
				bytesperline_c * height / 2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		bytesperline_y = width;
		bytesperline_c = width / 2;
		planar_offset[1] = bytesperline_y * height;
		planar_offset[2] = planar_offset[1] +
				bytesperline_c * height;
		अवरोध;
	शेष: /* raw */
		dev_dbg(sdev->dev,
			"Calculating pixelformat(0x%x)'s bytesperline as a packed format\n",
			config->pixelक्रमmat);
		bytesperline_y = (sun6i_csi_get_bpp(config->pixelक्रमmat) *
				  config->width) / 8;
		bytesperline_c = 0;
		planar_offset[1] = -1;
		planar_offset[2] = -1;
		अवरोध;
	पूर्ण

	regmap_ग_लिखो(sdev->regmap, CSI_CH_BUF_LEN_REG,
		     CSI_CH_BUF_LEN_BUF_LEN_C(bytesperline_c) |
		     CSI_CH_BUF_LEN_BUF_LEN_Y(bytesperline_y));
पूर्ण

पूर्णांक sun6i_csi_update_config(काष्ठा sun6i_csi *csi,
			    काष्ठा sun6i_csi_config *config)
अणु
	काष्ठा sun6i_csi_dev *sdev = sun6i_csi_to_dev(csi);

	अगर (!config)
		वापस -EINVAL;

	स_नकल(&csi->config, config, माप(csi->config));

	sun6i_csi_setup_bus(sdev);
	sun6i_csi_set_क्रमmat(sdev);
	sun6i_csi_set_winकरोw(sdev);

	वापस 0;
पूर्ण

व्योम sun6i_csi_update_buf_addr(काष्ठा sun6i_csi *csi, dma_addr_t addr)
अणु
	काष्ठा sun6i_csi_dev *sdev = sun6i_csi_to_dev(csi);

	regmap_ग_लिखो(sdev->regmap, CSI_CH_F0_BUFA_REG,
		     (addr + sdev->planar_offset[0]) >> 2);
	अगर (sdev->planar_offset[1] != -1)
		regmap_ग_लिखो(sdev->regmap, CSI_CH_F1_BUFA_REG,
			     (addr + sdev->planar_offset[1]) >> 2);
	अगर (sdev->planar_offset[2] != -1)
		regmap_ग_लिखो(sdev->regmap, CSI_CH_F2_BUFA_REG,
			     (addr + sdev->planar_offset[2]) >> 2);
पूर्ण

व्योम sun6i_csi_set_stream(काष्ठा sun6i_csi *csi, bool enable)
अणु
	काष्ठा sun6i_csi_dev *sdev = sun6i_csi_to_dev(csi);
	काष्ठा regmap *regmap = sdev->regmap;

	अगर (!enable) अणु
		regmap_update_bits(regmap, CSI_CAP_REG, CSI_CAP_CH0_VCAP_ON, 0);
		regmap_ग_लिखो(regmap, CSI_CH_INT_EN_REG, 0);
		वापस;
	पूर्ण

	regmap_ग_लिखो(regmap, CSI_CH_INT_STA_REG, 0xFF);
	regmap_ग_लिखो(regmap, CSI_CH_INT_EN_REG,
		     CSI_CH_INT_EN_HB_OF_INT_EN |
		     CSI_CH_INT_EN_FIFO2_OF_INT_EN |
		     CSI_CH_INT_EN_FIFO1_OF_INT_EN |
		     CSI_CH_INT_EN_FIFO0_OF_INT_EN |
		     CSI_CH_INT_EN_FD_INT_EN |
		     CSI_CH_INT_EN_CD_INT_EN);

	regmap_update_bits(regmap, CSI_CAP_REG, CSI_CAP_CH0_VCAP_ON,
			   CSI_CAP_CH0_VCAP_ON);
पूर्ण

/* -----------------------------------------------------------------------------
 * Media Controller and V4L2
 */
अटल पूर्णांक sun6i_csi_link_entity(काष्ठा sun6i_csi *csi,
				 काष्ठा media_entity *entity,
				 काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा media_entity *sink;
	काष्ठा media_pad *sink_pad;
	पूर्णांक src_pad_index;
	पूर्णांक ret;

	ret = media_entity_get_fwnode_pad(entity, fwnode, MEDIA_PAD_FL_SOURCE);
	अगर (ret < 0) अणु
		dev_err(csi->dev, "%s: no source pad in external entity %s\n",
			__func__, entity->name);
		वापस -EINVAL;
	पूर्ण

	src_pad_index = ret;

	sink = &csi->video.vdev.entity;
	sink_pad = &csi->video.pad;

	dev_dbg(csi->dev, "creating %s:%u -> %s:%u link\n",
		entity->name, src_pad_index, sink->name, sink_pad->index);
	ret = media_create_pad_link(entity, src_pad_index, sink,
				    sink_pad->index,
				    MEDIA_LNK_FL_ENABLED |
				    MEDIA_LNK_FL_IMMUTABLE);
	अगर (ret < 0) अणु
		dev_err(csi->dev, "failed to create %s:%u -> %s:%u link\n",
			entity->name, src_pad_index,
			sink->name, sink_pad->index);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_subdev_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा sun6i_csi *csi = container_of(notअगरier, काष्ठा sun6i_csi,
					     notअगरier);
	काष्ठा v4l2_device *v4l2_dev = &csi->v4l2_dev;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	dev_dbg(csi->dev, "notify complete, all subdevs registered\n");

	sd = list_first_entry(&v4l2_dev->subdevs, काष्ठा v4l2_subdev, list);
	अगर (!sd)
		वापस -EINVAL;

	ret = sun6i_csi_link_entity(csi, &sd->entity, sd->fwnode);
	अगर (ret < 0)
		वापस ret;

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&csi->v4l2_dev);
	अगर (ret < 0)
		वापस ret;

	वापस media_device_रेजिस्टर(&csi->media_dev);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations sun6i_csi_async_ops = अणु
	.complete = sun6i_subdev_notअगरy_complete,
पूर्ण;

अटल पूर्णांक sun6i_csi_fwnode_parse(काष्ठा device *dev,
				  काष्ठा v4l2_fwnode_endpoपूर्णांक *vep,
				  काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा sun6i_csi *csi = dev_get_drvdata(dev);

	अगर (vep->base.port || vep->base.id) अणु
		dev_warn(dev, "Only support a single port with one endpoint\n");
		वापस -ENOTCONN;
	पूर्ण

	चयन (vep->bus_type) अणु
	हाल V4L2_MBUS_PARALLEL:
	हाल V4L2_MBUS_BT656:
		csi->v4l2_ep = *vep;
		वापस 0;
	शेष:
		dev_err(dev, "Unsupported media bus type\n");
		वापस -ENOTCONN;
	पूर्ण
पूर्ण

अटल व्योम sun6i_csi_v4l2_cleanup(काष्ठा sun6i_csi *csi)
अणु
	media_device_unरेजिस्टर(&csi->media_dev);
	v4l2_async_notअगरier_unरेजिस्टर(&csi->notअगरier);
	v4l2_async_notअगरier_cleanup(&csi->notअगरier);
	sun6i_video_cleanup(&csi->video);
	v4l2_device_unरेजिस्टर(&csi->v4l2_dev);
	v4l2_ctrl_handler_मुक्त(&csi->ctrl_handler);
	media_device_cleanup(&csi->media_dev);
पूर्ण

अटल पूर्णांक sun6i_csi_v4l2_init(काष्ठा sun6i_csi *csi)
अणु
	पूर्णांक ret;

	csi->media_dev.dev = csi->dev;
	strscpy(csi->media_dev.model, "Allwinner Video Capture Device",
		माप(csi->media_dev.model));
	csi->media_dev.hw_revision = 0;
	snम_लिखो(csi->media_dev.bus_info, माप(csi->media_dev.bus_info),
		 "platform:%s", dev_name(csi->dev));

	media_device_init(&csi->media_dev);
	v4l2_async_notअगरier_init(&csi->notअगरier);

	ret = v4l2_ctrl_handler_init(&csi->ctrl_handler, 0);
	अगर (ret) अणु
		dev_err(csi->dev, "V4L2 controls handler init failed (%d)\n",
			ret);
		जाओ clean_media;
	पूर्ण

	csi->v4l2_dev.mdev = &csi->media_dev;
	csi->v4l2_dev.ctrl_handler = &csi->ctrl_handler;
	ret = v4l2_device_रेजिस्टर(csi->dev, &csi->v4l2_dev);
	अगर (ret) अणु
		dev_err(csi->dev, "V4L2 device registration failed (%d)\n",
			ret);
		जाओ मुक्त_ctrl;
	पूर्ण

	ret = sun6i_video_init(&csi->video, csi, "sun6i-csi");
	अगर (ret)
		जाओ unreg_v4l2;

	ret = v4l2_async_notअगरier_parse_fwnode_endpoपूर्णांकs(csi->dev,
							 &csi->notअगरier,
							 माप(काष्ठा v4l2_async_subdev),
							 sun6i_csi_fwnode_parse);
	अगर (ret)
		जाओ clean_video;

	csi->notअगरier.ops = &sun6i_csi_async_ops;

	ret = v4l2_async_notअगरier_रेजिस्टर(&csi->v4l2_dev, &csi->notअगरier);
	अगर (ret) अणु
		dev_err(csi->dev, "notifier registration failed\n");
		जाओ clean_video;
	पूर्ण

	वापस 0;

clean_video:
	sun6i_video_cleanup(&csi->video);
unreg_v4l2:
	v4l2_device_unरेजिस्टर(&csi->v4l2_dev);
मुक्त_ctrl:
	v4l2_ctrl_handler_मुक्त(&csi->ctrl_handler);
clean_media:
	v4l2_async_notअगरier_cleanup(&csi->notअगरier);
	media_device_cleanup(&csi->media_dev);

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Resources and IRQ
 */
अटल irqवापस_t sun6i_csi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun6i_csi_dev *sdev = (काष्ठा sun6i_csi_dev *)dev_id;
	काष्ठा regmap *regmap = sdev->regmap;
	u32 status;

	regmap_पढ़ो(regmap, CSI_CH_INT_STA_REG, &status);

	अगर (!(status & 0xFF))
		वापस IRQ_NONE;

	अगर ((status & CSI_CH_INT_STA_FIFO0_OF_PD) ||
	    (status & CSI_CH_INT_STA_FIFO1_OF_PD) ||
	    (status & CSI_CH_INT_STA_FIFO2_OF_PD) ||
	    (status & CSI_CH_INT_STA_HB_OF_PD)) अणु
		regmap_ग_लिखो(regmap, CSI_CH_INT_STA_REG, status);
		regmap_update_bits(regmap, CSI_EN_REG, CSI_EN_CSI_EN, 0);
		regmap_update_bits(regmap, CSI_EN_REG, CSI_EN_CSI_EN,
				   CSI_EN_CSI_EN);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (status & CSI_CH_INT_STA_FD_PD)
		sun6i_video_frame_करोne(&sdev->csi.video);

	regmap_ग_लिखो(regmap, CSI_CH_INT_STA_REG, status);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा regmap_config sun6i_csi_regmap_config = अणु
	.reg_bits       = 32,
	.reg_stride     = 4,
	.val_bits       = 32,
	.max_रेजिस्टर	= 0x9c,
पूर्ण;

अटल पूर्णांक sun6i_csi_resource_request(काष्ठा sun6i_csi_dev *sdev,
				      काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	व्योम __iomem *io_base;
	पूर्णांक ret;
	पूर्णांक irq;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	sdev->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "bus", io_base,
						 &sun6i_csi_regmap_config);
	अगर (IS_ERR(sdev->regmap)) अणु
		dev_err(&pdev->dev, "Failed to init register map\n");
		वापस PTR_ERR(sdev->regmap);
	पूर्ण

	sdev->clk_mod = devm_clk_get(&pdev->dev, "mod");
	अगर (IS_ERR(sdev->clk_mod)) अणु
		dev_err(&pdev->dev, "Unable to acquire csi clock\n");
		वापस PTR_ERR(sdev->clk_mod);
	पूर्ण

	sdev->clk_ram = devm_clk_get(&pdev->dev, "ram");
	अगर (IS_ERR(sdev->clk_ram)) अणु
		dev_err(&pdev->dev, "Unable to acquire dram-csi clock\n");
		वापस PTR_ERR(sdev->clk_ram);
	पूर्ण

	sdev->rstc_bus = devm_reset_control_get_shared(&pdev->dev, शून्य);
	अगर (IS_ERR(sdev->rstc_bus)) अणु
		dev_err(&pdev->dev, "Cannot get reset controller\n");
		वापस PTR_ERR(sdev->rstc_bus);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	ret = devm_request_irq(&pdev->dev, irq, sun6i_csi_isr, 0, MODULE_NAME,
			       sdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot request csi IRQ\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_csi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun6i_csi_dev *sdev;
	पूर्णांक ret;

	sdev = devm_kzalloc(&pdev->dev, माप(*sdev), GFP_KERNEL);
	अगर (!sdev)
		वापस -ENOMEM;

	sdev->dev = &pdev->dev;

	ret = sun6i_csi_resource_request(sdev, pdev);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, sdev);

	sdev->csi.dev = &pdev->dev;
	वापस sun6i_csi_v4l2_init(&sdev->csi);
पूर्ण

अटल पूर्णांक sun6i_csi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun6i_csi_dev *sdev = platक्रमm_get_drvdata(pdev);

	sun6i_csi_v4l2_cleanup(&sdev->csi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun6i_csi_of_match[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-csi", पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-csi", पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3-csi", पूर्ण,
	अणु .compatible = "allwinner,sun8i-v3s-csi", पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-csi", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun6i_csi_of_match);

अटल काष्ठा platक्रमm_driver sun6i_csi_platक्रमm_driver = अणु
	.probe = sun6i_csi_probe,
	.हटाओ = sun6i_csi_हटाओ,
	.driver = अणु
		.name = MODULE_NAME,
		.of_match_table = of_match_ptr(sun6i_csi_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun6i_csi_platक्रमm_driver);

MODULE_DESCRIPTION("Allwinner V3s Camera Sensor Interface driver");
MODULE_AUTHOR("Yong Deng <yong.deng@magewell.com>");
MODULE_LICENSE("GPL");
