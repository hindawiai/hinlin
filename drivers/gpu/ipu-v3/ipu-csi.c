<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012-2014 Mentor Graphics Inc.
 * Copyright (C) 2005-2009 Freescale Semiconductor, Inc.
 */
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <uapi/linux/v4l2-mediabus.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>

#समावेश "ipu-prv.h"

काष्ठा ipu_csi अणु
	व्योम __iomem *base;
	पूर्णांक id;
	u32 module;
	काष्ठा clk *clk_ipu;	/* IPU bus घड़ी */
	spinlock_t lock;
	bool inuse;
	काष्ठा ipu_soc *ipu;
पूर्ण;

/* CSI Register Offsets */
#घोषणा CSI_SENS_CONF		0x0000
#घोषणा CSI_SENS_FRM_SIZE	0x0004
#घोषणा CSI_ACT_FRM_SIZE	0x0008
#घोषणा CSI_OUT_FRM_CTRL	0x000c
#घोषणा CSI_TST_CTRL		0x0010
#घोषणा CSI_CCIR_CODE_1		0x0014
#घोषणा CSI_CCIR_CODE_2		0x0018
#घोषणा CSI_CCIR_CODE_3		0x001c
#घोषणा CSI_MIPI_DI		0x0020
#घोषणा CSI_SKIP		0x0024
#घोषणा CSI_CPD_CTRL		0x0028
#घोषणा CSI_CPD_RC(n)		(0x002c + ((n)*4))
#घोषणा CSI_CPD_RS(n)		(0x004c + ((n)*4))
#घोषणा CSI_CPD_GRC(n)		(0x005c + ((n)*4))
#घोषणा CSI_CPD_GRS(n)		(0x007c + ((n)*4))
#घोषणा CSI_CPD_GBC(n)		(0x008c + ((n)*4))
#घोषणा CSI_CPD_GBS(n)		(0x00Ac + ((n)*4))
#घोषणा CSI_CPD_BC(n)		(0x00Bc + ((n)*4))
#घोषणा CSI_CPD_BS(n)		(0x00Dc + ((n)*4))
#घोषणा CSI_CPD_OFFSET1		0x00ec
#घोषणा CSI_CPD_OFFSET2		0x00f0

/* CSI Register Fields */
#घोषणा CSI_SENS_CONF_DATA_FMT_SHIFT		8
#घोषणा CSI_SENS_CONF_DATA_FMT_MASK		0x00000700
#घोषणा CSI_SENS_CONF_DATA_FMT_RGB_YUV444	0L
#घोषणा CSI_SENS_CONF_DATA_FMT_YUV422_YUYV	1L
#घोषणा CSI_SENS_CONF_DATA_FMT_YUV422_UYVY	2L
#घोषणा CSI_SENS_CONF_DATA_FMT_BAYER		3L
#घोषणा CSI_SENS_CONF_DATA_FMT_RGB565		4L
#घोषणा CSI_SENS_CONF_DATA_FMT_RGB555		5L
#घोषणा CSI_SENS_CONF_DATA_FMT_RGB444		6L
#घोषणा CSI_SENS_CONF_DATA_FMT_JPEG		7L

#घोषणा CSI_SENS_CONF_VSYNC_POL_SHIFT		0
#घोषणा CSI_SENS_CONF_HSYNC_POL_SHIFT		1
#घोषणा CSI_SENS_CONF_DATA_POL_SHIFT		2
#घोषणा CSI_SENS_CONF_PIX_CLK_POL_SHIFT		3
#घोषणा CSI_SENS_CONF_SENS_PRTCL_MASK		0x00000070
#घोषणा CSI_SENS_CONF_SENS_PRTCL_SHIFT		4
#घोषणा CSI_SENS_CONF_PACK_TIGHT_SHIFT		7
#घोषणा CSI_SENS_CONF_DATA_WIDTH_SHIFT		11
#घोषणा CSI_SENS_CONF_EXT_VSYNC_SHIFT		15
#घोषणा CSI_SENS_CONF_DIVRATIO_SHIFT		16

#घोषणा CSI_SENS_CONF_DIVRATIO_MASK		0x00ff0000
#घोषणा CSI_SENS_CONF_DATA_DEST_SHIFT		24
#घोषणा CSI_SENS_CONF_DATA_DEST_MASK		0x07000000
#घोषणा CSI_SENS_CONF_JPEG8_EN_SHIFT		27
#घोषणा CSI_SENS_CONF_JPEG_EN_SHIFT		28
#घोषणा CSI_SENS_CONF_FORCE_खातापूर्ण_SHIFT		29
#घोषणा CSI_SENS_CONF_DATA_EN_POL_SHIFT		31

#घोषणा CSI_DATA_DEST_IC			2
#घोषणा CSI_DATA_DEST_IDMAC			4

#घोषणा CSI_CCIR_ERR_DET_EN			0x01000000
#घोषणा CSI_HORI_DOWNSIZE_EN			0x80000000
#घोषणा CSI_VERT_DOWNSIZE_EN			0x40000000
#घोषणा CSI_TEST_GEN_MODE_EN			0x01000000

#घोषणा CSI_HSC_MASK				0x1fff0000
#घोषणा CSI_HSC_SHIFT				16
#घोषणा CSI_VSC_MASK				0x00000fff
#घोषणा CSI_VSC_SHIFT				0

#घोषणा CSI_TEST_GEN_R_MASK			0x000000ff
#घोषणा CSI_TEST_GEN_R_SHIFT			0
#घोषणा CSI_TEST_GEN_G_MASK			0x0000ff00
#घोषणा CSI_TEST_GEN_G_SHIFT			8
#घोषणा CSI_TEST_GEN_B_MASK			0x00ff0000
#घोषणा CSI_TEST_GEN_B_SHIFT			16

#घोषणा CSI_MAX_RATIO_SKIP_SMFC_MASK		0x00000007
#घोषणा CSI_MAX_RATIO_SKIP_SMFC_SHIFT		0
#घोषणा CSI_SKIP_SMFC_MASK			0x000000f8
#घोषणा CSI_SKIP_SMFC_SHIFT			3
#घोषणा CSI_ID_2_SKIP_MASK			0x00000300
#घोषणा CSI_ID_2_SKIP_SHIFT			8

#घोषणा CSI_COLOR_FIRST_ROW_MASK		0x00000002
#घोषणा CSI_COLOR_FIRST_COMP_MASK		0x00000001

/* MIPI CSI-2 data types */
#घोषणा MIPI_DT_YUV420		0x18 /* YYY.../UYVY.... */
#घोषणा MIPI_DT_YUV420_LEGACY	0x1a /* UYY.../VYY...   */
#घोषणा MIPI_DT_YUV422		0x1e /* UYVY...         */
#घोषणा MIPI_DT_RGB444		0x20
#घोषणा MIPI_DT_RGB555		0x21
#घोषणा MIPI_DT_RGB565		0x22
#घोषणा MIPI_DT_RGB666		0x23
#घोषणा MIPI_DT_RGB888		0x24
#घोषणा MIPI_DT_RAW6		0x28
#घोषणा MIPI_DT_RAW7		0x29
#घोषणा MIPI_DT_RAW8		0x2a
#घोषणा MIPI_DT_RAW10		0x2b
#घोषणा MIPI_DT_RAW12		0x2c
#घोषणा MIPI_DT_RAW14		0x2d

/*
 * Bitfield of CSI bus संकेत polarities and modes.
 */
काष्ठा ipu_csi_bus_config अणु
	अचिन्हित data_width:4;
	अचिन्हित clk_mode:3;
	अचिन्हित ext_vsync:1;
	अचिन्हित vsync_pol:1;
	अचिन्हित hsync_pol:1;
	अचिन्हित pixclk_pol:1;
	अचिन्हित data_pol:1;
	अचिन्हित sens_clksrc:1;
	अचिन्हित pack_tight:1;
	अचिन्हित क्रमce_eof:1;
	अचिन्हित data_en_pol:1;

	अचिन्हित data_fmt;
	अचिन्हित mipi_dt;
पूर्ण;

/*
 * Enumeration of CSI data bus widths.
 */
क्रमागत ipu_csi_data_width अणु
	IPU_CSI_DATA_WIDTH_4   = 0,
	IPU_CSI_DATA_WIDTH_8   = 1,
	IPU_CSI_DATA_WIDTH_10  = 3,
	IPU_CSI_DATA_WIDTH_12  = 5,
	IPU_CSI_DATA_WIDTH_16  = 9,
पूर्ण;

/*
 * Enumeration of CSI घड़ी modes.
 */
क्रमागत ipu_csi_clk_mode अणु
	IPU_CSI_CLK_MODE_GATED_CLK,
	IPU_CSI_CLK_MODE_NONGATED_CLK,
	IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE,
	IPU_CSI_CLK_MODE_CCIR656_INTERLACED,
	IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_DDR,
	IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_SDR,
	IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_DDR,
	IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_SDR,
पूर्ण;

अटल अंतरभूत u32 ipu_csi_पढ़ो(काष्ठा ipu_csi *csi, अचिन्हित offset)
अणु
	वापस पढ़ोl(csi->base + offset);
पूर्ण

अटल अंतरभूत व्योम ipu_csi_ग_लिखो(काष्ठा ipu_csi *csi, u32 value,
				 अचिन्हित offset)
अणु
	ग_लिखोl(value, csi->base + offset);
पूर्ण

/*
 * Set mclk भागision ratio क्रम generating test mode mclk. Only used
 * क्रम test generator.
 */
अटल पूर्णांक ipu_csi_set_testgen_mclk(काष्ठा ipu_csi *csi, u32 pixel_clk,
					u32 ipu_clk)
अणु
	u32 temp;
	पूर्णांक भाग_ratio;

	भाग_ratio = (ipu_clk / pixel_clk) - 1;

	अगर (भाग_ratio > 0xFF || भाग_ratio < 0) अणु
		dev_err(csi->ipu->dev,
			"value of pixel_clk extends normal range\n");
		वापस -EINVAL;
	पूर्ण

	temp = ipu_csi_पढ़ो(csi, CSI_SENS_CONF);
	temp &= ~CSI_SENS_CONF_DIVRATIO_MASK;
	ipu_csi_ग_लिखो(csi, temp | (भाग_ratio << CSI_SENS_CONF_DIVRATIO_SHIFT),
			  CSI_SENS_CONF);

	वापस 0;
पूर्ण

/*
 * Find the CSI data क्रमmat and data width क्रम the given V4L2 media
 * bus pixel क्रमmat code.
 */
अटल पूर्णांक mbus_code_to_bus_cfg(काष्ठा ipu_csi_bus_config *cfg, u32 mbus_code,
				क्रमागत v4l2_mbus_type mbus_type)
अणु
	चयन (mbus_code) अणु
	हाल MEDIA_BUS_FMT_BGR565_2X8_BE:
	हाल MEDIA_BUS_FMT_BGR565_2X8_LE:
	हाल MEDIA_BUS_FMT_RGB565_2X8_BE:
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
		अगर (mbus_type == V4L2_MBUS_CSI2_DPHY)
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_RGB565;
		अन्यथा
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RGB565;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB444_2X8_PADHI_BE:
	हाल MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_RGB444;
		cfg->mipi_dt = MIPI_DT_RGB444;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE:
	हाल MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_RGB555;
		cfg->mipi_dt = MIPI_DT_RGB555;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X24:
	हाल MEDIA_BUS_FMT_BGR888_1X24:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_RGB_YUV444;
		cfg->mipi_dt = MIPI_DT_RGB888;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_YUV422_UYVY;
		cfg->mipi_dt = MIPI_DT_YUV422;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_YUV422_YUYV;
		cfg->mipi_dt = MIPI_DT_YUV422;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_YUV422;
		cfg->data_width = IPU_CSI_DATA_WIDTH_16;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
	हाल MEDIA_BUS_FMT_Y8_1X8:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RAW8;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8:
	हाल MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8:
	हाल MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
	हाल MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8:
	हाल MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_BE:
	हाल MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE:
	हाल MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_BE:
	हाल MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_LE:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RAW10;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
	हाल MEDIA_BUS_FMT_SGBRG10_1X10:
	हाल MEDIA_BUS_FMT_SGRBG10_1X10:
	हाल MEDIA_BUS_FMT_SRGGB10_1X10:
	हाल MEDIA_BUS_FMT_Y10_1X10:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RAW10;
		cfg->data_width = IPU_CSI_DATA_WIDTH_10;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR12_1X12:
	हाल MEDIA_BUS_FMT_SGBRG12_1X12:
	हाल MEDIA_BUS_FMT_SGRBG12_1X12:
	हाल MEDIA_BUS_FMT_SRGGB12_1X12:
	हाल MEDIA_BUS_FMT_Y12_1X12:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RAW12;
		cfg->data_width = IPU_CSI_DATA_WIDTH_12;
		अवरोध;
	हाल MEDIA_BUS_FMT_JPEG_1X8:
		/* TODO */
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_JPEG;
		cfg->mipi_dt = MIPI_DT_RAW8;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* translate alternate field mode based on given standard */
अटल अंतरभूत क्रमागत v4l2_field
ipu_csi_translate_field(क्रमागत v4l2_field field, v4l2_std_id std)
अणु
	वापस (field != V4L2_FIELD_ALTERNATE) ? field :
		((std & V4L2_STD_525_60) ?
		 V4L2_FIELD_SEQ_BT : V4L2_FIELD_SEQ_TB);
पूर्ण

/*
 * Fill a CSI bus config काष्ठा from mbus_config and mbus_framefmt.
 */
अटल पूर्णांक fill_csi_bus_cfg(काष्ठा ipu_csi_bus_config *csicfg,
			    स्थिर काष्ठा v4l2_mbus_config *mbus_cfg,
			    स्थिर काष्ठा v4l2_mbus_framefmt *mbus_fmt)
अणु
	पूर्णांक ret;

	स_रखो(csicfg, 0, माप(*csicfg));

	ret = mbus_code_to_bus_cfg(csicfg, mbus_fmt->code, mbus_cfg->type);
	अगर (ret < 0)
		वापस ret;

	चयन (mbus_cfg->type) अणु
	हाल V4L2_MBUS_PARALLEL:
		csicfg->ext_vsync = 1;
		csicfg->vsync_pol = (mbus_cfg->flags &
				     V4L2_MBUS_VSYNC_ACTIVE_LOW) ? 1 : 0;
		csicfg->hsync_pol = (mbus_cfg->flags &
				     V4L2_MBUS_HSYNC_ACTIVE_LOW) ? 1 : 0;
		csicfg->pixclk_pol = (mbus_cfg->flags &
				      V4L2_MBUS_PCLK_SAMPLE_FALLING) ? 1 : 0;
		csicfg->clk_mode = IPU_CSI_CLK_MODE_GATED_CLK;
		अवरोध;
	हाल V4L2_MBUS_BT656:
		csicfg->ext_vsync = 0;
		अगर (V4L2_FIELD_HAS_BOTH(mbus_fmt->field) ||
		    mbus_fmt->field == V4L2_FIELD_ALTERNATE)
			csicfg->clk_mode = IPU_CSI_CLK_MODE_CCIR656_INTERLACED;
		अन्यथा
			csicfg->clk_mode = IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE;
		अवरोध;
	हाल V4L2_MBUS_CSI2_DPHY:
		/*
		 * MIPI CSI-2 requires non gated घड़ी mode, all other
		 * parameters are not applicable क्रम MIPI CSI-2 bus.
		 */
		csicfg->clk_mode = IPU_CSI_CLK_MODE_NONGATED_CLK;
		अवरोध;
	शेष:
		/* will never get here, keep compiler quiet */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ipu_csi_set_bt_पूर्णांकerlaced_codes(काष्ठा ipu_csi *csi,
				स्थिर काष्ठा v4l2_mbus_framefmt *infmt,
				स्थिर काष्ठा v4l2_mbus_framefmt *outfmt,
				v4l2_std_id std)
अणु
	क्रमागत v4l2_field infield, outfield;
	bool swap_fields;

	/* get translated field type of input and output */
	infield = ipu_csi_translate_field(infmt->field, std);
	outfield = ipu_csi_translate_field(outfmt->field, std);

	/*
	 * Write the H-V-F codes the CSI will match against the
	 * incoming data क्रम start/end of active and blanking
	 * field पूर्णांकervals. If input and output field types are
	 * sequential but not the same (one is SEQ_BT and the other
	 * is SEQ_TB), swap the F-bit so that the CSI will capture
	 * field 1 lines beक्रमe field 0 lines.
	 */
	swap_fields = (V4L2_FIELD_IS_SEQUENTIAL(infield) &&
		       V4L2_FIELD_IS_SEQUENTIAL(outfield) &&
		       infield != outfield);

	अगर (!swap_fields) अणु
		/*
		 * Field0BlankEnd  = 110, Field0BlankStart  = 010
		 * Field0ActiveEnd = 100, Field0ActiveStart = 000
		 * Field1BlankEnd  = 111, Field1BlankStart  = 011
		 * Field1ActiveEnd = 101, Field1ActiveStart = 001
		 */
		ipu_csi_ग_लिखो(csi, 0x40596 | CSI_CCIR_ERR_DET_EN,
			      CSI_CCIR_CODE_1);
		ipu_csi_ग_लिखो(csi, 0xD07DF, CSI_CCIR_CODE_2);
	पूर्ण अन्यथा अणु
		dev_dbg(csi->ipu->dev, "capture field swap\n");

		/* same as above but with F-bit inverted */
		ipu_csi_ग_लिखो(csi, 0xD07DF | CSI_CCIR_ERR_DET_EN,
			      CSI_CCIR_CODE_1);
		ipu_csi_ग_लिखो(csi, 0x40596, CSI_CCIR_CODE_2);
	पूर्ण

	ipu_csi_ग_लिखो(csi, 0xFF0000, CSI_CCIR_CODE_3);

	वापस 0;
पूर्ण


पूर्णांक ipu_csi_init_पूर्णांकerface(काष्ठा ipu_csi *csi,
			   स्थिर काष्ठा v4l2_mbus_config *mbus_cfg,
			   स्थिर काष्ठा v4l2_mbus_framefmt *infmt,
			   स्थिर काष्ठा v4l2_mbus_framefmt *outfmt)
अणु
	काष्ठा ipu_csi_bus_config cfg;
	अचिन्हित दीर्घ flags;
	u32 width, height, data = 0;
	v4l2_std_id std;
	पूर्णांक ret;

	ret = fill_csi_bus_cfg(&cfg, mbus_cfg, infmt);
	अगर (ret < 0)
		वापस ret;

	/* set शेष sensor frame width and height */
	width = infmt->width;
	height = infmt->height;
	अगर (infmt->field == V4L2_FIELD_ALTERNATE)
		height *= 2;

	/* Set the CSI_SENS_CONF रेजिस्टर reमुख्यing fields */
	data |= cfg.data_width << CSI_SENS_CONF_DATA_WIDTH_SHIFT |
		cfg.data_fmt << CSI_SENS_CONF_DATA_FMT_SHIFT |
		cfg.data_pol << CSI_SENS_CONF_DATA_POL_SHIFT |
		cfg.vsync_pol << CSI_SENS_CONF_VSYNC_POL_SHIFT |
		cfg.hsync_pol << CSI_SENS_CONF_HSYNC_POL_SHIFT |
		cfg.pixclk_pol << CSI_SENS_CONF_PIX_CLK_POL_SHIFT |
		cfg.ext_vsync << CSI_SENS_CONF_EXT_VSYNC_SHIFT |
		cfg.clk_mode << CSI_SENS_CONF_SENS_PRTCL_SHIFT |
		cfg.pack_tight << CSI_SENS_CONF_PACK_TIGHT_SHIFT |
		cfg.क्रमce_eof << CSI_SENS_CONF_FORCE_खातापूर्ण_SHIFT |
		cfg.data_en_pol << CSI_SENS_CONF_DATA_EN_POL_SHIFT;

	spin_lock_irqsave(&csi->lock, flags);

	ipu_csi_ग_लिखो(csi, data, CSI_SENS_CONF);

	/* Set CCIR रेजिस्टरs */

	चयन (cfg.clk_mode) अणु
	हाल IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE:
		ipu_csi_ग_लिखो(csi, 0x40030, CSI_CCIR_CODE_1);
		ipu_csi_ग_लिखो(csi, 0xFF0000, CSI_CCIR_CODE_3);
		अवरोध;
	हाल IPU_CSI_CLK_MODE_CCIR656_INTERLACED:
		अगर (width == 720 && height == 480) अणु
			std = V4L2_STD_NTSC;
			height = 525;
		पूर्ण अन्यथा अगर (width == 720 && height == 576) अणु
			std = V4L2_STD_PAL;
			height = 625;
		पूर्ण अन्यथा अणु
			dev_err(csi->ipu->dev,
				"Unsupported interlaced video mode\n");
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		ret = ipu_csi_set_bt_पूर्णांकerlaced_codes(csi, infmt, outfmt, std);
		अगर (ret)
			जाओ out_unlock;
		अवरोध;
	हाल IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_DDR:
	हाल IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_SDR:
	हाल IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_DDR:
	हाल IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_SDR:
		ipu_csi_ग_लिखो(csi, 0x40030 | CSI_CCIR_ERR_DET_EN,
				   CSI_CCIR_CODE_1);
		ipu_csi_ग_लिखो(csi, 0xFF0000, CSI_CCIR_CODE_3);
		अवरोध;
	हाल IPU_CSI_CLK_MODE_GATED_CLK:
	हाल IPU_CSI_CLK_MODE_NONGATED_CLK:
		ipu_csi_ग_लिखो(csi, 0, CSI_CCIR_CODE_1);
		अवरोध;
	पूर्ण

	/* Setup sensor frame size */
	ipu_csi_ग_लिखो(csi, (width - 1) | ((height - 1) << 16),
		      CSI_SENS_FRM_SIZE);

	dev_dbg(csi->ipu->dev, "CSI_SENS_CONF = 0x%08X\n",
		ipu_csi_पढ़ो(csi, CSI_SENS_CONF));
	dev_dbg(csi->ipu->dev, "CSI_ACT_FRM_SIZE = 0x%08X\n",
		ipu_csi_पढ़ो(csi, CSI_ACT_FRM_SIZE));

out_unlock:
	spin_unlock_irqrestore(&csi->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_init_पूर्णांकerface);

bool ipu_csi_is_पूर्णांकerlaced(काष्ठा ipu_csi *csi)
अणु
	अचिन्हित दीर्घ flags;
	u32 sensor_protocol;

	spin_lock_irqsave(&csi->lock, flags);
	sensor_protocol =
		(ipu_csi_पढ़ो(csi, CSI_SENS_CONF) &
		 CSI_SENS_CONF_SENS_PRTCL_MASK) >>
		CSI_SENS_CONF_SENS_PRTCL_SHIFT;
	spin_unlock_irqrestore(&csi->lock, flags);

	चयन (sensor_protocol) अणु
	हाल IPU_CSI_CLK_MODE_GATED_CLK:
	हाल IPU_CSI_CLK_MODE_NONGATED_CLK:
	हाल IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE:
	हाल IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_DDR:
	हाल IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_SDR:
		वापस false;
	हाल IPU_CSI_CLK_MODE_CCIR656_INTERLACED:
	हाल IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_DDR:
	हाल IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_SDR:
		वापस true;
	शेष:
		dev_err(csi->ipu->dev,
			"CSI %d sensor protocol unsupported\n", csi->id);
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_is_पूर्णांकerlaced);

व्योम ipu_csi_get_winकरोw(काष्ठा ipu_csi *csi, काष्ठा v4l2_rect *w)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&csi->lock, flags);

	reg = ipu_csi_पढ़ो(csi, CSI_ACT_FRM_SIZE);
	w->width = (reg & 0xFFFF) + 1;
	w->height = (reg >> 16 & 0xFFFF) + 1;

	reg = ipu_csi_पढ़ो(csi, CSI_OUT_FRM_CTRL);
	w->left = (reg & CSI_HSC_MASK) >> CSI_HSC_SHIFT;
	w->top = (reg & CSI_VSC_MASK) >> CSI_VSC_SHIFT;

	spin_unlock_irqrestore(&csi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_get_winकरोw);

व्योम ipu_csi_set_winकरोw(काष्ठा ipu_csi *csi, काष्ठा v4l2_rect *w)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&csi->lock, flags);

	ipu_csi_ग_लिखो(csi, (w->width - 1) | ((w->height - 1) << 16),
			  CSI_ACT_FRM_SIZE);

	reg = ipu_csi_पढ़ो(csi, CSI_OUT_FRM_CTRL);
	reg &= ~(CSI_HSC_MASK | CSI_VSC_MASK);
	reg |= ((w->top << CSI_VSC_SHIFT) | (w->left << CSI_HSC_SHIFT));
	ipu_csi_ग_लिखो(csi, reg, CSI_OUT_FRM_CTRL);

	spin_unlock_irqrestore(&csi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_set_winकरोw);

व्योम ipu_csi_set_करोwnsize(काष्ठा ipu_csi *csi, bool horiz, bool vert)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&csi->lock, flags);

	reg = ipu_csi_पढ़ो(csi, CSI_OUT_FRM_CTRL);
	reg &= ~(CSI_HORI_DOWNSIZE_EN | CSI_VERT_DOWNSIZE_EN);
	reg |= (horiz ? CSI_HORI_DOWNSIZE_EN : 0) |
	       (vert ? CSI_VERT_DOWNSIZE_EN : 0);
	ipu_csi_ग_लिखो(csi, reg, CSI_OUT_FRM_CTRL);

	spin_unlock_irqrestore(&csi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_set_करोwnsize);

व्योम ipu_csi_set_test_generator(काष्ठा ipu_csi *csi, bool active,
				u32 r_value, u32 g_value, u32 b_value,
				u32 pix_clk)
अणु
	अचिन्हित दीर्घ flags;
	u32 ipu_clk = clk_get_rate(csi->clk_ipu);
	u32 temp;

	spin_lock_irqsave(&csi->lock, flags);

	temp = ipu_csi_पढ़ो(csi, CSI_TST_CTRL);

	अगर (!active) अणु
		temp &= ~CSI_TEST_GEN_MODE_EN;
		ipu_csi_ग_लिखो(csi, temp, CSI_TST_CTRL);
	पूर्ण अन्यथा अणु
		/* Set sensb_mclk भाग_ratio */
		ipu_csi_set_testgen_mclk(csi, pix_clk, ipu_clk);

		temp &= ~(CSI_TEST_GEN_R_MASK | CSI_TEST_GEN_G_MASK |
			  CSI_TEST_GEN_B_MASK);
		temp |= CSI_TEST_GEN_MODE_EN;
		temp |= (r_value << CSI_TEST_GEN_R_SHIFT) |
			(g_value << CSI_TEST_GEN_G_SHIFT) |
			(b_value << CSI_TEST_GEN_B_SHIFT);
		ipu_csi_ग_लिखो(csi, temp, CSI_TST_CTRL);
	पूर्ण

	spin_unlock_irqrestore(&csi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_set_test_generator);

पूर्णांक ipu_csi_set_mipi_datatype(काष्ठा ipu_csi *csi, u32 vc,
			      काष्ठा v4l2_mbus_framefmt *mbus_fmt)
अणु
	काष्ठा ipu_csi_bus_config cfg;
	अचिन्हित दीर्घ flags;
	u32 temp;
	पूर्णांक ret;

	अगर (vc > 3)
		वापस -EINVAL;

	ret = mbus_code_to_bus_cfg(&cfg, mbus_fmt->code, V4L2_MBUS_CSI2_DPHY);
	अगर (ret < 0)
		वापस ret;

	spin_lock_irqsave(&csi->lock, flags);

	temp = ipu_csi_पढ़ो(csi, CSI_MIPI_DI);
	temp &= ~(0xff << (vc * 8));
	temp |= (cfg.mipi_dt << (vc * 8));
	ipu_csi_ग_लिखो(csi, temp, CSI_MIPI_DI);

	spin_unlock_irqrestore(&csi->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_set_mipi_datatype);

पूर्णांक ipu_csi_set_skip_smfc(काष्ठा ipu_csi *csi, u32 skip,
			  u32 max_ratio, u32 id)
अणु
	अचिन्हित दीर्घ flags;
	u32 temp;

	अगर (max_ratio > 5 || id > 3)
		वापस -EINVAL;

	spin_lock_irqsave(&csi->lock, flags);

	temp = ipu_csi_पढ़ो(csi, CSI_SKIP);
	temp &= ~(CSI_MAX_RATIO_SKIP_SMFC_MASK | CSI_ID_2_SKIP_MASK |
		  CSI_SKIP_SMFC_MASK);
	temp |= (max_ratio << CSI_MAX_RATIO_SKIP_SMFC_SHIFT) |
		(id << CSI_ID_2_SKIP_SHIFT) |
		(skip << CSI_SKIP_SMFC_SHIFT);
	ipu_csi_ग_लिखो(csi, temp, CSI_SKIP);

	spin_unlock_irqrestore(&csi->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_set_skip_smfc);

पूर्णांक ipu_csi_set_dest(काष्ठा ipu_csi *csi, क्रमागत ipu_csi_dest csi_dest)
अणु
	अचिन्हित दीर्घ flags;
	u32 csi_sens_conf, dest;

	अगर (csi_dest == IPU_CSI_DEST_IDMAC)
		dest = CSI_DATA_DEST_IDMAC;
	अन्यथा
		dest = CSI_DATA_DEST_IC; /* IC or VDIC */

	spin_lock_irqsave(&csi->lock, flags);

	csi_sens_conf = ipu_csi_पढ़ो(csi, CSI_SENS_CONF);
	csi_sens_conf &= ~CSI_SENS_CONF_DATA_DEST_MASK;
	csi_sens_conf |= (dest << CSI_SENS_CONF_DATA_DEST_SHIFT);
	ipu_csi_ग_लिखो(csi, csi_sens_conf, CSI_SENS_CONF);

	spin_unlock_irqrestore(&csi->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_set_dest);

पूर्णांक ipu_csi_enable(काष्ठा ipu_csi *csi)
अणु
	ipu_module_enable(csi->ipu, csi->module);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_enable);

पूर्णांक ipu_csi_disable(काष्ठा ipu_csi *csi)
अणु
	ipu_module_disable(csi->ipu, csi->module);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_disable);

काष्ठा ipu_csi *ipu_csi_get(काष्ठा ipu_soc *ipu, पूर्णांक id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ipu_csi *csi, *ret;

	अगर (id > 1)
		वापस ERR_PTR(-EINVAL);

	csi = ipu->csi_priv[id];
	ret = csi;

	spin_lock_irqsave(&csi->lock, flags);

	अगर (csi->inuse) अणु
		ret = ERR_PTR(-EBUSY);
		जाओ unlock;
	पूर्ण

	csi->inuse = true;
unlock:
	spin_unlock_irqrestore(&csi->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_get);

व्योम ipu_csi_put(काष्ठा ipu_csi *csi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&csi->lock, flags);
	csi->inuse = false;
	spin_unlock_irqrestore(&csi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_put);

पूर्णांक ipu_csi_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, पूर्णांक id,
		 अचिन्हित दीर्घ base, u32 module, काष्ठा clk *clk_ipu)
अणु
	काष्ठा ipu_csi *csi;

	अगर (id > 1)
		वापस -ENODEV;

	csi = devm_kzalloc(dev, माप(*csi), GFP_KERNEL);
	अगर (!csi)
		वापस -ENOMEM;

	ipu->csi_priv[id] = csi;

	spin_lock_init(&csi->lock);
	csi->module = module;
	csi->id = id;
	csi->clk_ipu = clk_ipu;
	csi->base = devm_ioremap(dev, base, PAGE_SIZE);
	अगर (!csi->base)
		वापस -ENOMEM;

	dev_dbg(dev, "CSI%d base: 0x%08lx remapped to %p\n",
		id, base, csi->base);
	csi->ipu = ipu;

	वापस 0;
पूर्ण

व्योम ipu_csi_निकास(काष्ठा ipu_soc *ipu, पूर्णांक id)
अणु
पूर्ण

व्योम ipu_csi_dump(काष्ठा ipu_csi *csi)
अणु
	dev_dbg(csi->ipu->dev, "CSI_SENS_CONF:     %08x\n",
		ipu_csi_पढ़ो(csi, CSI_SENS_CONF));
	dev_dbg(csi->ipu->dev, "CSI_SENS_FRM_SIZE: %08x\n",
		ipu_csi_पढ़ो(csi, CSI_SENS_FRM_SIZE));
	dev_dbg(csi->ipu->dev, "CSI_ACT_FRM_SIZE:  %08x\n",
		ipu_csi_पढ़ो(csi, CSI_ACT_FRM_SIZE));
	dev_dbg(csi->ipu->dev, "CSI_OUT_FRM_CTRL:  %08x\n",
		ipu_csi_पढ़ो(csi, CSI_OUT_FRM_CTRL));
	dev_dbg(csi->ipu->dev, "CSI_TST_CTRL:      %08x\n",
		ipu_csi_पढ़ो(csi, CSI_TST_CTRL));
	dev_dbg(csi->ipu->dev, "CSI_CCIR_CODE_1:   %08x\n",
		ipu_csi_पढ़ो(csi, CSI_CCIR_CODE_1));
	dev_dbg(csi->ipu->dev, "CSI_CCIR_CODE_2:   %08x\n",
		ipu_csi_पढ़ो(csi, CSI_CCIR_CODE_2));
	dev_dbg(csi->ipu->dev, "CSI_CCIR_CODE_3:   %08x\n",
		ipu_csi_पढ़ो(csi, CSI_CCIR_CODE_3));
	dev_dbg(csi->ipu->dev, "CSI_MIPI_DI:       %08x\n",
		ipu_csi_पढ़ो(csi, CSI_MIPI_DI));
	dev_dbg(csi->ipu->dev, "CSI_SKIP:          %08x\n",
		ipu_csi_पढ़ो(csi, CSI_SKIP));
पूर्ण
EXPORT_SYMBOL_GPL(ipu_csi_dump);
