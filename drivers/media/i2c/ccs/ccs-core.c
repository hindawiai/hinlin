<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/i2c/ccs/ccs-core.c
 *
 * Generic driver क्रम MIPI CCS/SMIA/SMIA++ compliant camera sensors
 *
 * Copyright (C) 2020 Intel Corporation
 * Copyright (C) 2010--2012 Nokia Corporation
 * Contact: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 *
 * Based on smiapp driver by Vimarsh Zutshi
 * Based on jt8ev1.c by Vimarsh Zutshi
 * Based on smia-sensor.c by Tuukka Toivonen <tuukkat76@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/smiapp.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-device.h>
#समावेश <uapi/linux/ccs.h>

#समावेश "ccs.h"

#घोषणा CCS_ALIGN_DIM(dim, flags)	\
	((flags) & V4L2_SEL_FLAG_GE	\
	 ? ALIGN((dim), 2)		\
	 : (dim) & ~1)

अटल काष्ठा ccs_limit_offset अणु
	u16	lim;
	u16	info;
पूर्ण ccs_limit_offsets[CCS_L_LAST + 1];

/*
 * ccs_module_idents - supported camera modules
 */
अटल स्थिर काष्ठा ccs_module_ident ccs_module_idents[] = अणु
	CCS_IDENT_L(0x01, 0x022b, -1, "vs6555"),
	CCS_IDENT_L(0x01, 0x022e, -1, "vw6558"),
	CCS_IDENT_L(0x07, 0x7698, -1, "ovm7698"),
	CCS_IDENT_L(0x0b, 0x4242, -1, "smiapp-003"),
	CCS_IDENT_L(0x0c, 0x208a, -1, "tcm8330md"),
	CCS_IDENT_LQ(0x0c, 0x2134, -1, "tcm8500md", &smiapp_tcm8500md_quirk),
	CCS_IDENT_L(0x0c, 0x213e, -1, "et8en2"),
	CCS_IDENT_L(0x0c, 0x2184, -1, "tcm8580md"),
	CCS_IDENT_LQ(0x0c, 0x560f, -1, "jt8ew9", &smiapp_jt8ew9_quirk),
	CCS_IDENT_LQ(0x10, 0x4141, -1, "jt8ev1", &smiapp_jt8ev1_quirk),
	CCS_IDENT_LQ(0x10, 0x4241, -1, "imx125es", &smiapp_imx125es_quirk),
पूर्ण;

#घोषणा CCS_DEVICE_FLAG_IS_SMIA		BIT(0)

काष्ठा ccs_device अणु
	अचिन्हित अक्षर flags;
पूर्ण;

अटल स्थिर अक्षर * स्थिर ccs_regulators[] = अणु "vcore", "vio", "vana" पूर्ण;

/*
 *
 * Dynamic Capability Identअगरication
 *
 */

अटल व्योम ccs_assign_limit(व्योम *ptr, अचिन्हित पूर्णांक width, u32 val)
अणु
	चयन (width) अणु
	हाल माप(u8):
		*(u8 *)ptr = val;
		अवरोध;
	हाल माप(u16):
		*(u16 *)ptr = val;
		अवरोध;
	हाल माप(u32):
		*(u32 *)ptr = val;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ccs_limit_ptr(काष्ठा ccs_sensor *sensor, अचिन्हित पूर्णांक limit,
			 अचिन्हित पूर्णांक offset, व्योम **__ptr)
अणु
	स्थिर काष्ठा ccs_limit *linfo;

	अगर (WARN_ON(limit >= CCS_L_LAST))
		वापस -EINVAL;

	linfo = &ccs_limits[ccs_limit_offsets[limit].info];

	अगर (WARN_ON(!sensor->ccs_limits) ||
	    WARN_ON(offset + ccs_reg_width(linfo->reg) >
		    ccs_limit_offsets[limit + 1].lim))
		वापस -EINVAL;

	*__ptr = sensor->ccs_limits + ccs_limit_offsets[limit].lim + offset;

	वापस 0;
पूर्ण

व्योम ccs_replace_limit(काष्ठा ccs_sensor *sensor,
		       अचिन्हित पूर्णांक limit, अचिन्हित पूर्णांक offset, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	स्थिर काष्ठा ccs_limit *linfo;
	व्योम *ptr;
	पूर्णांक ret;

	ret = ccs_limit_ptr(sensor, limit, offset, &ptr);
	अगर (ret)
		वापस;

	linfo = &ccs_limits[ccs_limit_offsets[limit].info];

	dev_dbg(&client->dev, "quirk: 0x%8.8x \"%s\" %u = %d, 0x%x\n",
		linfo->reg, linfo->name, offset, val, val);

	ccs_assign_limit(ptr, ccs_reg_width(linfo->reg), val);
पूर्ण

u32 ccs_get_limit(काष्ठा ccs_sensor *sensor, अचिन्हित पूर्णांक limit,
		  अचिन्हित पूर्णांक offset)
अणु
	व्योम *ptr;
	u32 val;
	पूर्णांक ret;

	ret = ccs_limit_ptr(sensor, limit, offset, &ptr);
	अगर (ret)
		वापस 0;

	चयन (ccs_reg_width(ccs_limits[ccs_limit_offsets[limit].info].reg)) अणु
	हाल माप(u8):
		val = *(u8 *)ptr;
		अवरोध;
	हाल माप(u16):
		val = *(u16 *)ptr;
		अवरोध;
	हाल माप(u32):
		val = *(u32 *)ptr;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण

	वापस ccs_reg_conv(sensor, ccs_limits[limit].reg, val);
पूर्ण

अटल पूर्णांक ccs_पढ़ो_all_limits(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	व्योम *ptr, *alloc, *end;
	अचिन्हित पूर्णांक i, l;
	पूर्णांक ret;

	kमुक्त(sensor->ccs_limits);
	sensor->ccs_limits = शून्य;

	alloc = kzalloc(ccs_limit_offsets[CCS_L_LAST].lim, GFP_KERNEL);
	अगर (!alloc)
		वापस -ENOMEM;

	end = alloc + ccs_limit_offsets[CCS_L_LAST].lim;

	क्रम (i = 0, l = 0, ptr = alloc; ccs_limits[i].size; i++) अणु
		u32 reg = ccs_limits[i].reg;
		अचिन्हित पूर्णांक width = ccs_reg_width(reg);
		अचिन्हित पूर्णांक j;

		अगर (l == CCS_L_LAST) अणु
			dev_err(&client->dev,
				"internal error --- end of limit array\n");
			ret = -EINVAL;
			जाओ out_err;
		पूर्ण

		क्रम (j = 0; j < ccs_limits[i].size / width;
		     j++, reg += width, ptr += width) अणु
			u32 val;

			ret = ccs_पढ़ो_addr_noconv(sensor, reg, &val);
			अगर (ret)
				जाओ out_err;

			अगर (ptr + width > end) अणु
				dev_err(&client->dev,
					"internal error --- no room for regs\n");
				ret = -EINVAL;
				जाओ out_err;
			पूर्ण

			अगर (!val && j)
				अवरोध;

			ccs_assign_limit(ptr, width, val);

			dev_dbg(&client->dev, "0x%8.8x \"%s\" = %u, 0x%x\n",
				reg, ccs_limits[i].name, val, val);
		पूर्ण

		अगर (ccs_limits[i].flags & CCS_L_FL_SAME_REG)
			जारी;

		l++;
		ptr = alloc + ccs_limit_offsets[l].lim;
	पूर्ण

	अगर (l != CCS_L_LAST) अणु
		dev_err(&client->dev,
			"internal error --- insufficient limits\n");
		ret = -EINVAL;
		जाओ out_err;
	पूर्ण

	sensor->ccs_limits = alloc;

	अगर (CCS_LIM(sensor, SCALER_N_MIN) < 16)
		ccs_replace_limit(sensor, CCS_L_SCALER_N_MIN, 0, 16);

	वापस 0;

out_err:
	kमुक्त(alloc);

	वापस ret;
पूर्ण

अटल पूर्णांक ccs_पढ़ो_frame_fmt(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	u8 fmt_model_type, fmt_model_subtype, ncol_desc, nrow_desc;
	अचिन्हित पूर्णांक i;
	पूर्णांक pixel_count = 0;
	पूर्णांक line_count = 0;

	fmt_model_type = CCS_LIM(sensor, FRAME_FORMAT_MODEL_TYPE);
	fmt_model_subtype = CCS_LIM(sensor, FRAME_FORMAT_MODEL_SUBTYPE);

	ncol_desc = (fmt_model_subtype
		     & CCS_FRAME_FORMAT_MODEL_SUBTYPE_COLUMNS_MASK)
		>> CCS_FRAME_FORMAT_MODEL_SUBTYPE_COLUMNS_SHIFT;
	nrow_desc = fmt_model_subtype
		& CCS_FRAME_FORMAT_MODEL_SUBTYPE_ROWS_MASK;

	dev_dbg(&client->dev, "format_model_type %s\n",
		fmt_model_type == CCS_FRAME_FORMAT_MODEL_TYPE_2_BYTE
		? "2 byte" :
		fmt_model_type == CCS_FRAME_FORMAT_MODEL_TYPE_4_BYTE
		? "4 byte" : "is simply bad");

	dev_dbg(&client->dev, "%u column and %u row descriptors\n",
		ncol_desc, nrow_desc);

	क्रम (i = 0; i < ncol_desc + nrow_desc; i++) अणु
		u32 desc;
		u32 pixelcode;
		u32 pixels;
		अक्षर *which;
		अक्षर *what;

		अगर (fmt_model_type == CCS_FRAME_FORMAT_MODEL_TYPE_2_BYTE) अणु
			desc = CCS_LIM_AT(sensor, FRAME_FORMAT_DESCRIPTOR, i);

			pixelcode =
				(desc
				 & CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_MASK)
				>> CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_SHIFT;
			pixels = desc & CCS_FRAME_FORMAT_DESCRIPTOR_PIXELS_MASK;
		पूर्ण अन्यथा अगर (fmt_model_type
			   == CCS_FRAME_FORMAT_MODEL_TYPE_4_BYTE) अणु
			desc = CCS_LIM_AT(sensor, FRAME_FORMAT_DESCRIPTOR_4, i);

			pixelcode =
				(desc
				 & CCS_FRAME_FORMAT_DESCRIPTOR_4_PCODE_MASK)
				>> CCS_FRAME_FORMAT_DESCRIPTOR_4_PCODE_SHIFT;
			pixels = desc &
				CCS_FRAME_FORMAT_DESCRIPTOR_4_PIXELS_MASK;
		पूर्ण अन्यथा अणु
			dev_dbg(&client->dev,
				"invalid frame format model type %d\n",
				fmt_model_type);
			वापस -EINVAL;
		पूर्ण

		अगर (i < ncol_desc)
			which = "columns";
		अन्यथा
			which = "rows";

		चयन (pixelcode) अणु
		हाल CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_EMBEDDED:
			what = "embedded";
			अवरोध;
		हाल CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_DUMMY_PIXEL:
			what = "dummy";
			अवरोध;
		हाल CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_BLACK_PIXEL:
			what = "black";
			अवरोध;
		हाल CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_DARK_PIXEL:
			what = "dark";
			अवरोध;
		हाल CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_VISIBLE_PIXEL:
			what = "visible";
			अवरोध;
		शेष:
			what = "invalid";
			अवरोध;
		पूर्ण

		dev_dbg(&client->dev,
			"%s pixels: %d %s (pixelcode %u)\n",
			what, pixels, which, pixelcode);

		अगर (i < ncol_desc) अणु
			अगर (pixelcode ==
			    CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_VISIBLE_PIXEL)
				sensor->visible_pixel_start = pixel_count;
			pixel_count += pixels;
			जारी;
		पूर्ण

		/* Handle row descriptors */
		चयन (pixelcode) अणु
		हाल CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_EMBEDDED:
			अगर (sensor->embedded_end)
				अवरोध;
			sensor->embedded_start = line_count;
			sensor->embedded_end = line_count + pixels;
			अवरोध;
		हाल CCS_FRAME_FORMAT_DESCRIPTOR_PCODE_VISIBLE_PIXEL:
			sensor->image_start = line_count;
			अवरोध;
		पूर्ण
		line_count += pixels;
	पूर्ण

	अगर (sensor->embedded_end > sensor->image_start) अणु
		dev_dbg(&client->dev,
			"adjusting image start line to %u (was %u)\n",
			sensor->embedded_end, sensor->image_start);
		sensor->image_start = sensor->embedded_end;
	पूर्ण

	dev_dbg(&client->dev, "embedded data from lines %d to %d\n",
		sensor->embedded_start, sensor->embedded_end);
	dev_dbg(&client->dev, "image data starts at line %d\n",
		sensor->image_start);

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_pll_configure(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा ccs_pll *pll = &sensor->pll;
	पूर्णांक rval;

	rval = ccs_ग_लिखो(sensor, VT_PIX_CLK_DIV, pll->vt_bk.pix_clk_भाग);
	अगर (rval < 0)
		वापस rval;

	rval = ccs_ग_लिखो(sensor, VT_SYS_CLK_DIV, pll->vt_bk.sys_clk_भाग);
	अगर (rval < 0)
		वापस rval;

	rval = ccs_ग_लिखो(sensor, PRE_PLL_CLK_DIV, pll->vt_fr.pre_pll_clk_भाग);
	अगर (rval < 0)
		वापस rval;

	rval = ccs_ग_लिखो(sensor, PLL_MULTIPLIER, pll->vt_fr.pll_multiplier);
	अगर (rval < 0)
		वापस rval;

	अगर (!(CCS_LIM(sensor, PHY_CTRL_CAPABILITY) &
	      CCS_PHY_CTRL_CAPABILITY_AUTO_PHY_CTL)) अणु
		/* Lane op घड़ी ratio करोes not apply here. */
		rval = ccs_ग_लिखो(sensor, REQUESTED_LINK_RATE,
				 DIV_ROUND_UP(pll->op_bk.sys_clk_freq_hz,
					      1000000 / 256 / 256) *
				 (pll->flags & CCS_PLL_FLAG_LANE_SPEED_MODEL ?
				  sensor->pll.csi2.lanes : 1) <<
				 (pll->flags & CCS_PLL_FLAG_OP_SYS_DDR ?
				  1 : 0));
		अगर (rval < 0)
			वापस rval;
	पूर्ण

	अगर (sensor->pll.flags & CCS_PLL_FLAG_NO_OP_CLOCKS)
		वापस 0;

	rval = ccs_ग_लिखो(sensor, OP_PIX_CLK_DIV, pll->op_bk.pix_clk_भाग);
	अगर (rval < 0)
		वापस rval;

	rval = ccs_ग_लिखो(sensor, OP_SYS_CLK_DIV, pll->op_bk.sys_clk_भाग);
	अगर (rval < 0)
		वापस rval;

	अगर (!(pll->flags & CCS_PLL_FLAG_DUAL_PLL))
		वापस 0;

	rval = ccs_ग_लिखो(sensor, PLL_MODE, CCS_PLL_MODE_DUAL);
	अगर (rval < 0)
		वापस rval;

	rval = ccs_ग_लिखो(sensor, OP_PRE_PLL_CLK_DIV,
			 pll->op_fr.pre_pll_clk_भाग);
	अगर (rval < 0)
		वापस rval;

	वापस ccs_ग_लिखो(sensor, OP_PLL_MULTIPLIER, pll->op_fr.pll_multiplier);
पूर्ण

अटल पूर्णांक ccs_pll_try(काष्ठा ccs_sensor *sensor, काष्ठा ccs_pll *pll)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	काष्ठा ccs_pll_limits lim = अणु
		.vt_fr = अणु
			.min_pre_pll_clk_भाग = CCS_LIM(sensor, MIN_PRE_PLL_CLK_DIV),
			.max_pre_pll_clk_भाग = CCS_LIM(sensor, MAX_PRE_PLL_CLK_DIV),
			.min_pll_ip_clk_freq_hz = CCS_LIM(sensor, MIN_PLL_IP_CLK_FREQ_MHZ),
			.max_pll_ip_clk_freq_hz = CCS_LIM(sensor, MAX_PLL_IP_CLK_FREQ_MHZ),
			.min_pll_multiplier = CCS_LIM(sensor, MIN_PLL_MULTIPLIER),
			.max_pll_multiplier = CCS_LIM(sensor, MAX_PLL_MULTIPLIER),
			.min_pll_op_clk_freq_hz = CCS_LIM(sensor, MIN_PLL_OP_CLK_FREQ_MHZ),
			.max_pll_op_clk_freq_hz = CCS_LIM(sensor, MAX_PLL_OP_CLK_FREQ_MHZ),
		पूर्ण,
		.op_fr = अणु
			.min_pre_pll_clk_भाग = CCS_LIM(sensor, MIN_OP_PRE_PLL_CLK_DIV),
			.max_pre_pll_clk_भाग = CCS_LIM(sensor, MAX_OP_PRE_PLL_CLK_DIV),
			.min_pll_ip_clk_freq_hz = CCS_LIM(sensor, MIN_OP_PLL_IP_CLK_FREQ_MHZ),
			.max_pll_ip_clk_freq_hz = CCS_LIM(sensor, MAX_OP_PLL_IP_CLK_FREQ_MHZ),
			.min_pll_multiplier = CCS_LIM(sensor, MIN_OP_PLL_MULTIPLIER),
			.max_pll_multiplier = CCS_LIM(sensor, MAX_OP_PLL_MULTIPLIER),
			.min_pll_op_clk_freq_hz = CCS_LIM(sensor, MIN_OP_PLL_OP_CLK_FREQ_MHZ),
			.max_pll_op_clk_freq_hz = CCS_LIM(sensor, MAX_OP_PLL_OP_CLK_FREQ_MHZ),
		पूर्ण,
		.op_bk = अणु
			 .min_sys_clk_भाग = CCS_LIM(sensor, MIN_OP_SYS_CLK_DIV),
			 .max_sys_clk_भाग = CCS_LIM(sensor, MAX_OP_SYS_CLK_DIV),
			 .min_pix_clk_भाग = CCS_LIM(sensor, MIN_OP_PIX_CLK_DIV),
			 .max_pix_clk_भाग = CCS_LIM(sensor, MAX_OP_PIX_CLK_DIV),
			 .min_sys_clk_freq_hz = CCS_LIM(sensor, MIN_OP_SYS_CLK_FREQ_MHZ),
			 .max_sys_clk_freq_hz = CCS_LIM(sensor, MAX_OP_SYS_CLK_FREQ_MHZ),
			 .min_pix_clk_freq_hz = CCS_LIM(sensor, MIN_OP_PIX_CLK_FREQ_MHZ),
			 .max_pix_clk_freq_hz = CCS_LIM(sensor, MAX_OP_PIX_CLK_FREQ_MHZ),
		 पूर्ण,
		.vt_bk = अणु
			 .min_sys_clk_भाग = CCS_LIM(sensor, MIN_VT_SYS_CLK_DIV),
			 .max_sys_clk_भाग = CCS_LIM(sensor, MAX_VT_SYS_CLK_DIV),
			 .min_pix_clk_भाग = CCS_LIM(sensor, MIN_VT_PIX_CLK_DIV),
			 .max_pix_clk_भाग = CCS_LIM(sensor, MAX_VT_PIX_CLK_DIV),
			 .min_sys_clk_freq_hz = CCS_LIM(sensor, MIN_VT_SYS_CLK_FREQ_MHZ),
			 .max_sys_clk_freq_hz = CCS_LIM(sensor, MAX_VT_SYS_CLK_FREQ_MHZ),
			 .min_pix_clk_freq_hz = CCS_LIM(sensor, MIN_VT_PIX_CLK_FREQ_MHZ),
			 .max_pix_clk_freq_hz = CCS_LIM(sensor, MAX_VT_PIX_CLK_FREQ_MHZ),
		 पूर्ण,
		.min_line_length_pck_bin = CCS_LIM(sensor, MIN_LINE_LENGTH_PCK_BIN),
		.min_line_length_pck = CCS_LIM(sensor, MIN_LINE_LENGTH_PCK),
	पूर्ण;

	वापस ccs_pll_calculate(&client->dev, &lim, pll);
पूर्ण

अटल पूर्णांक ccs_pll_update(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा ccs_pll *pll = &sensor->pll;
	पूर्णांक rval;

	pll->binning_horizontal = sensor->binning_horizontal;
	pll->binning_vertical = sensor->binning_vertical;
	pll->link_freq =
		sensor->link_freq->qmenu_पूर्णांक[sensor->link_freq->val];
	pll->scale_m = sensor->scale_m;
	pll->bits_per_pixel = sensor->csi_क्रमmat->compressed;

	rval = ccs_pll_try(sensor, pll);
	अगर (rval < 0)
		वापस rval;

	__v4l2_ctrl_s_ctrl_पूर्णांक64(sensor->pixel_rate_parray,
				 pll->pixel_rate_pixel_array);
	__v4l2_ctrl_s_ctrl_पूर्णांक64(sensor->pixel_rate_csi, pll->pixel_rate_csi);

	वापस 0;
पूर्ण


/*
 *
 * V4L2 Controls handling
 *
 */

अटल व्योम __ccs_update_exposure_limits(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा v4l2_ctrl *ctrl = sensor->exposure;
	पूर्णांक max;

	max = sensor->pixel_array->crop[CCS_PA_PAD_SRC].height
		+ sensor->vblank->val
		- CCS_LIM(sensor, COARSE_INTEGRATION_TIME_MAX_MARGIN);

	__v4l2_ctrl_modअगरy_range(ctrl, ctrl->minimum, max, ctrl->step, max);
पूर्ण

/*
 * Order matters.
 *
 * 1. Bits-per-pixel, descending.
 * 2. Bits-per-pixel compressed, descending.
 * 3. Pixel order, same as in pixel_order_str. Formats क्रम all four pixel
 *    orders must be defined.
 */
अटल स्थिर काष्ठा ccs_csi_data_क्रमmat ccs_csi_data_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_SGRBG16_1X16, 16, 16, CCS_PIXEL_ORDER_GRBG, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB16_1X16, 16, 16, CCS_PIXEL_ORDER_RGGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR16_1X16, 16, 16, CCS_PIXEL_ORDER_BGGR, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG16_1X16, 16, 16, CCS_PIXEL_ORDER_GBRG, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG14_1X14, 14, 14, CCS_PIXEL_ORDER_GRBG, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB14_1X14, 14, 14, CCS_PIXEL_ORDER_RGGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR14_1X14, 14, 14, CCS_PIXEL_ORDER_BGGR, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG14_1X14, 14, 14, CCS_PIXEL_ORDER_GBRG, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, 12, 12, CCS_PIXEL_ORDER_GRBG, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, 12, 12, CCS_PIXEL_ORDER_RGGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, 12, 12, CCS_PIXEL_ORDER_BGGR, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, 12, 12, CCS_PIXEL_ORDER_GBRG, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, 10, 10, CCS_PIXEL_ORDER_GRBG, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, 10, 10, CCS_PIXEL_ORDER_RGGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, 10, 10, CCS_PIXEL_ORDER_BGGR, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, 10, 10, CCS_PIXEL_ORDER_GBRG, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8, 10, 8, CCS_PIXEL_ORDER_GRBG, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8, 10, 8, CCS_PIXEL_ORDER_RGGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8, 10, 8, CCS_PIXEL_ORDER_BGGR, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8, 10, 8, CCS_PIXEL_ORDER_GBRG, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, 8, 8, CCS_PIXEL_ORDER_GRBG, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, 8, 8, CCS_PIXEL_ORDER_RGGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, 8, 8, CCS_PIXEL_ORDER_BGGR, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, 8, 8, CCS_PIXEL_ORDER_GBRG, पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *pixel_order_str[] = अणु "GRBG", "RGGB", "BGGR", "GBRG" पूर्ण;

#घोषणा to_csi_क्रमmat_idx(fmt) (((अचिन्हित दीर्घ)(fmt)			\
				 - (अचिन्हित दीर्घ)ccs_csi_data_क्रमmats) \
				/ माप(*ccs_csi_data_क्रमmats))

अटल u32 ccs_pixel_order(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक flip = 0;

	अगर (sensor->hflip) अणु
		अगर (sensor->hflip->val)
			flip |= CCS_IMAGE_ORIENTATION_HORIZONTAL_MIRROR;

		अगर (sensor->vflip->val)
			flip |= CCS_IMAGE_ORIENTATION_VERTICAL_FLIP;
	पूर्ण

	flip ^= sensor->hvflip_inv_mask;

	dev_dbg(&client->dev, "flip %d\n", flip);
	वापस sensor->शेष_pixel_order ^ flip;
पूर्ण

अटल व्योम ccs_update_mbus_क्रमmats(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	अचिन्हित पूर्णांक csi_क्रमmat_idx =
		to_csi_क्रमmat_idx(sensor->csi_क्रमmat) & ~3;
	अचिन्हित पूर्णांक पूर्णांकernal_csi_क्रमmat_idx =
		to_csi_क्रमmat_idx(sensor->पूर्णांकernal_csi_क्रमmat) & ~3;
	अचिन्हित पूर्णांक pixel_order = ccs_pixel_order(sensor);

	अगर (WARN_ON_ONCE(max(पूर्णांकernal_csi_क्रमmat_idx, csi_क्रमmat_idx) +
			 pixel_order >= ARRAY_SIZE(ccs_csi_data_क्रमmats)))
		वापस;

	sensor->mbus_frame_fmts =
		sensor->शेष_mbus_frame_fmts << pixel_order;
	sensor->csi_क्रमmat =
		&ccs_csi_data_क्रमmats[csi_क्रमmat_idx + pixel_order];
	sensor->पूर्णांकernal_csi_क्रमmat =
		&ccs_csi_data_क्रमmats[पूर्णांकernal_csi_क्रमmat_idx
					 + pixel_order];

	dev_dbg(&client->dev, "new pixel order %s\n",
		pixel_order_str[pixel_order]);
पूर्ण

अटल स्थिर अक्षर * स्थिर ccs_test_patterns[] = अणु
	"Disabled",
	"Solid Colour",
	"Eight Vertical Colour Bars",
	"Colour Bars With Fade to Grey",
	"Pseudorandom Sequence (PN9)",
पूर्ण;

अटल पूर्णांक ccs_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ccs_sensor *sensor =
		container_of(ctrl->handler, काष्ठा ccs_subdev, ctrl_handler)
			->sensor;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक pm_status;
	u32 orient = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक exposure;
	पूर्णांक rval;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
	हाल V4L2_CID_VFLIP:
		अगर (sensor->streaming)
			वापस -EBUSY;

		अगर (sensor->hflip->val)
			orient |= CCS_IMAGE_ORIENTATION_HORIZONTAL_MIRROR;

		अगर (sensor->vflip->val)
			orient |= CCS_IMAGE_ORIENTATION_VERTICAL_FLIP;

		orient ^= sensor->hvflip_inv_mask;

		ccs_update_mbus_क्रमmats(sensor);

		अवरोध;
	हाल V4L2_CID_VBLANK:
		exposure = sensor->exposure->val;

		__ccs_update_exposure_limits(sensor);

		अगर (exposure > sensor->exposure->maximum) अणु
			sensor->exposure->val =	sensor->exposure->maximum;
			rval = ccs_set_ctrl(sensor->exposure);
			अगर (rval < 0)
				वापस rval;
		पूर्ण

		अवरोध;
	हाल V4L2_CID_LINK_FREQ:
		अगर (sensor->streaming)
			वापस -EBUSY;

		rval = ccs_pll_update(sensor);
		अगर (rval)
			वापस rval;

		वापस 0;
	हाल V4L2_CID_TEST_PATTERN:
		क्रम (i = 0; i < ARRAY_SIZE(sensor->test_data); i++)
			v4l2_ctrl_activate(
				sensor->test_data[i],
				ctrl->val ==
				V4L2_SMIAPP_TEST_PATTERN_MODE_SOLID_COLOUR);

		अवरोध;
	पूर्ण

	pm_status = pm_runसमय_get_अगर_active(&client->dev, true);
	अगर (!pm_status)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		rval = ccs_ग_लिखो(sensor, ANALOG_GAIN_CODE_GLOBAL, ctrl->val);

		अवरोध;

	हाल V4L2_CID_CCS_ANALOGUE_LINEAR_GAIN:
		rval = ccs_ग_लिखो(sensor, ANALOG_LINEAR_GAIN_GLOBAL, ctrl->val);

		अवरोध;

	हाल V4L2_CID_CCS_ANALOGUE_EXPONENTIAL_GAIN:
		rval = ccs_ग_लिखो(sensor, ANALOG_EXPONENTIAL_GAIN_GLOBAL,
				 ctrl->val);

		अवरोध;

	हाल V4L2_CID_DIGITAL_GAIN:
		अगर (CCS_LIM(sensor, DIGITAL_GAIN_CAPABILITY) ==
		    CCS_DIGITAL_GAIN_CAPABILITY_GLOBAL) अणु
			rval = ccs_ग_लिखो(sensor, DIGITAL_GAIN_GLOBAL,
					 ctrl->val);
			अवरोध;
		पूर्ण

		rval = ccs_ग_लिखो_addr(sensor,
				      SMIAPP_REG_U16_DIGITAL_GAIN_GREENR,
				      ctrl->val);
		अगर (rval)
			अवरोध;

		rval = ccs_ग_लिखो_addr(sensor,
				      SMIAPP_REG_U16_DIGITAL_GAIN_RED,
				      ctrl->val);
		अगर (rval)
			अवरोध;

		rval = ccs_ग_लिखो_addr(sensor,
				      SMIAPP_REG_U16_DIGITAL_GAIN_BLUE,
				      ctrl->val);
		अगर (rval)
			अवरोध;

		rval = ccs_ग_लिखो_addr(sensor,
				      SMIAPP_REG_U16_DIGITAL_GAIN_GREENB,
				      ctrl->val);

		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		rval = ccs_ग_लिखो(sensor, COARSE_INTEGRATION_TIME, ctrl->val);

		अवरोध;
	हाल V4L2_CID_HFLIP:
	हाल V4L2_CID_VFLIP:
		rval = ccs_ग_लिखो(sensor, IMAGE_ORIENTATION, orient);

		अवरोध;
	हाल V4L2_CID_VBLANK:
		rval = ccs_ग_लिखो(sensor, FRAME_LENGTH_LINES,
				 sensor->pixel_array->crop[
					 CCS_PA_PAD_SRC].height
				 + ctrl->val);

		अवरोध;
	हाल V4L2_CID_HBLANK:
		rval = ccs_ग_लिखो(sensor, LINE_LENGTH_PCK,
				 sensor->pixel_array->crop[CCS_PA_PAD_SRC].width
				 + ctrl->val);

		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		rval = ccs_ग_लिखो(sensor, TEST_PATTERN_MODE, ctrl->val);

		अवरोध;
	हाल V4L2_CID_TEST_PATTERN_RED:
		rval = ccs_ग_लिखो(sensor, TEST_DATA_RED, ctrl->val);

		अवरोध;
	हाल V4L2_CID_TEST_PATTERN_GREENR:
		rval = ccs_ग_लिखो(sensor, TEST_DATA_GREENR, ctrl->val);

		अवरोध;
	हाल V4L2_CID_TEST_PATTERN_BLUE:
		rval = ccs_ग_लिखो(sensor, TEST_DATA_BLUE, ctrl->val);

		अवरोध;
	हाल V4L2_CID_TEST_PATTERN_GREENB:
		rval = ccs_ग_लिखो(sensor, TEST_DATA_GREENB, ctrl->val);

		अवरोध;
	हाल V4L2_CID_CCS_SHADING_CORRECTION:
		rval = ccs_ग_लिखो(sensor, SHADING_CORRECTION_EN,
				 ctrl->val ? CCS_SHADING_CORRECTION_EN_ENABLE :
				 0);

		अगर (!rval && sensor->luminance_level)
			v4l2_ctrl_activate(sensor->luminance_level, ctrl->val);

		अवरोध;
	हाल V4L2_CID_CCS_LUMIन_अंकCE_CORRECTION_LEVEL:
		rval = ccs_ग_लिखो(sensor, LUMIन_अंकCE_CORRECTION_LEVEL, ctrl->val);

		अवरोध;
	हाल V4L2_CID_PIXEL_RATE:
		/* For v4l2_ctrl_s_ctrl_पूर्णांक64() used पूर्णांकernally. */
		rval = 0;

		अवरोध;
	शेष:
		rval = -EINVAL;
	पूर्ण

	अगर (pm_status > 0) अणु
		pm_runसमय_mark_last_busy(&client->dev);
		pm_runसमय_put_स्वतःsuspend(&client->dev);
	पूर्ण

	वापस rval;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ccs_ctrl_ops = अणु
	.s_ctrl = ccs_set_ctrl,
पूर्ण;

अटल पूर्णांक ccs_init_controls(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक rval;

	rval = v4l2_ctrl_handler_init(&sensor->pixel_array->ctrl_handler, 17);
	अगर (rval)
		वापस rval;

	sensor->pixel_array->ctrl_handler.lock = &sensor->mutex;

	चयन (CCS_LIM(sensor, ANALOG_GAIN_CAPABILITY)) अणु
	हाल CCS_ANALOG_GAIN_CAPABILITY_GLOBAL: अणु
		काष्ठा अणु
			स्थिर अक्षर *name;
			u32 id;
			s32 value;
		पूर्ण स्थिर gain_ctrls[] = अणु
			अणु "Analogue Gain m0", V4L2_CID_CCS_ANALOGUE_GAIN_M0,
			  CCS_LIM(sensor, ANALOG_GAIN_M0), पूर्ण,
			अणु "Analogue Gain c0", V4L2_CID_CCS_ANALOGUE_GAIN_C0,
			  CCS_LIM(sensor, ANALOG_GAIN_C0), पूर्ण,
			अणु "Analogue Gain m1", V4L2_CID_CCS_ANALOGUE_GAIN_M1,
			  CCS_LIM(sensor, ANALOG_GAIN_M1), पूर्ण,
			अणु "Analogue Gain c1", V4L2_CID_CCS_ANALOGUE_GAIN_C1,
			  CCS_LIM(sensor, ANALOG_GAIN_C1), पूर्ण,
		पूर्ण;
		काष्ठा v4l2_ctrl_config ctrl_cfg = अणु
			.type = V4L2_CTRL_TYPE_INTEGER,
			.ops = &ccs_ctrl_ops,
			.flags = V4L2_CTRL_FLAG_READ_ONLY,
			.step = 1,
		पूर्ण;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(gain_ctrls); i++) अणु
			ctrl_cfg.name = gain_ctrls[i].name;
			ctrl_cfg.id = gain_ctrls[i].id;
			ctrl_cfg.min = ctrl_cfg.max = ctrl_cfg.def =
				gain_ctrls[i].value;

			v4l2_ctrl_new_custom(&sensor->pixel_array->ctrl_handler,
					     &ctrl_cfg, शून्य);
		पूर्ण

		v4l2_ctrl_new_std(&sensor->pixel_array->ctrl_handler,
				  &ccs_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
				  CCS_LIM(sensor, ANALOG_GAIN_CODE_MIN),
				  CCS_LIM(sensor, ANALOG_GAIN_CODE_MAX),
				  max(CCS_LIM(sensor, ANALOG_GAIN_CODE_STEP),
				      1U),
				  CCS_LIM(sensor, ANALOG_GAIN_CODE_MIN));
	पूर्ण
		अवरोध;

	हाल CCS_ANALOG_GAIN_CAPABILITY_ALTERNATE_GLOBAL: अणु
		काष्ठा अणु
			स्थिर अक्षर *name;
			u32 id;
			u16 min, max, step;
		पूर्ण स्थिर gain_ctrls[] = अणु
			अणु
				"Analogue Linear Gain",
				V4L2_CID_CCS_ANALOGUE_LINEAR_GAIN,
				CCS_LIM(sensor, ANALOG_LINEAR_GAIN_MIN),
				CCS_LIM(sensor, ANALOG_LINEAR_GAIN_MAX),
				max(CCS_LIM(sensor,
					    ANALOG_LINEAR_GAIN_STEP_SIZE),
				    1U),
			पूर्ण,
			अणु
				"Analogue Exponential Gain",
				V4L2_CID_CCS_ANALOGUE_EXPONENTIAL_GAIN,
				CCS_LIM(sensor, ANALOG_EXPONENTIAL_GAIN_MIN),
				CCS_LIM(sensor, ANALOG_EXPONENTIAL_GAIN_MAX),
				max(CCS_LIM(sensor,
					    ANALOG_EXPONENTIAL_GAIN_STEP_SIZE),
				    1U),
			पूर्ण,
		पूर्ण;
		काष्ठा v4l2_ctrl_config ctrl_cfg = अणु
			.type = V4L2_CTRL_TYPE_INTEGER,
			.ops = &ccs_ctrl_ops,
		पूर्ण;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(gain_ctrls); i++) अणु
			ctrl_cfg.name = gain_ctrls[i].name;
			ctrl_cfg.min = ctrl_cfg.def = gain_ctrls[i].min;
			ctrl_cfg.max = gain_ctrls[i].max;
			ctrl_cfg.step = gain_ctrls[i].step;
			ctrl_cfg.id = gain_ctrls[i].id;

			v4l2_ctrl_new_custom(&sensor->pixel_array->ctrl_handler,
					     &ctrl_cfg, शून्य);
		पूर्ण
	पूर्ण
	पूर्ण

	अगर (CCS_LIM(sensor, SHADING_CORRECTION_CAPABILITY) &
	    (CCS_SHADING_CORRECTION_CAPABILITY_COLOR_SHADING |
	     CCS_SHADING_CORRECTION_CAPABILITY_LUMIन_अंकCE_CORRECTION)) अणु
		स्थिर काष्ठा v4l2_ctrl_config ctrl_cfg = अणु
			.name = "Shading Correction",
			.type = V4L2_CTRL_TYPE_BOOLEAN,
			.id = V4L2_CID_CCS_SHADING_CORRECTION,
			.ops = &ccs_ctrl_ops,
			.max = 1,
			.step = 1,
		पूर्ण;

		v4l2_ctrl_new_custom(&sensor->pixel_array->ctrl_handler,
				     &ctrl_cfg, शून्य);
	पूर्ण

	अगर (CCS_LIM(sensor, SHADING_CORRECTION_CAPABILITY) &
	    CCS_SHADING_CORRECTION_CAPABILITY_LUMIन_अंकCE_CORRECTION) अणु
		स्थिर काष्ठा v4l2_ctrl_config ctrl_cfg = अणु
			.name = "Luminance Correction Level",
			.type = V4L2_CTRL_TYPE_BOOLEAN,
			.id = V4L2_CID_CCS_LUMIन_अंकCE_CORRECTION_LEVEL,
			.ops = &ccs_ctrl_ops,
			.max = 255,
			.step = 1,
			.def = 128,
		पूर्ण;

		sensor->luminance_level =
			v4l2_ctrl_new_custom(&sensor->pixel_array->ctrl_handler,
					     &ctrl_cfg, शून्य);
	पूर्ण

	अगर (CCS_LIM(sensor, DIGITAL_GAIN_CAPABILITY) ==
	    CCS_DIGITAL_GAIN_CAPABILITY_GLOBAL ||
	    CCS_LIM(sensor, DIGITAL_GAIN_CAPABILITY) ==
	    SMIAPP_DIGITAL_GAIN_CAPABILITY_PER_CHANNEL)
		v4l2_ctrl_new_std(&sensor->pixel_array->ctrl_handler,
				  &ccs_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
				  CCS_LIM(sensor, DIGITAL_GAIN_MIN),
				  CCS_LIM(sensor, DIGITAL_GAIN_MAX),
				  max(CCS_LIM(sensor, DIGITAL_GAIN_STEP_SIZE),
				      1U),
				  0x100);

	/* Exposure limits will be updated soon, use just something here. */
	sensor->exposure = v4l2_ctrl_new_std(
		&sensor->pixel_array->ctrl_handler, &ccs_ctrl_ops,
		V4L2_CID_EXPOSURE, 0, 0, 1, 0);

	sensor->hflip = v4l2_ctrl_new_std(
		&sensor->pixel_array->ctrl_handler, &ccs_ctrl_ops,
		V4L2_CID_HFLIP, 0, 1, 1, 0);
	sensor->vflip = v4l2_ctrl_new_std(
		&sensor->pixel_array->ctrl_handler, &ccs_ctrl_ops,
		V4L2_CID_VFLIP, 0, 1, 1, 0);

	sensor->vblank = v4l2_ctrl_new_std(
		&sensor->pixel_array->ctrl_handler, &ccs_ctrl_ops,
		V4L2_CID_VBLANK, 0, 1, 1, 0);

	अगर (sensor->vblank)
		sensor->vblank->flags |= V4L2_CTRL_FLAG_UPDATE;

	sensor->hblank = v4l2_ctrl_new_std(
		&sensor->pixel_array->ctrl_handler, &ccs_ctrl_ops,
		V4L2_CID_HBLANK, 0, 1, 1, 0);

	अगर (sensor->hblank)
		sensor->hblank->flags |= V4L2_CTRL_FLAG_UPDATE;

	sensor->pixel_rate_parray = v4l2_ctrl_new_std(
		&sensor->pixel_array->ctrl_handler, &ccs_ctrl_ops,
		V4L2_CID_PIXEL_RATE, 1, पूर्णांक_उच्च, 1, 1);

	v4l2_ctrl_new_std_menu_items(&sensor->pixel_array->ctrl_handler,
				     &ccs_ctrl_ops, V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ccs_test_patterns) - 1,
				     0, 0, ccs_test_patterns);

	अगर (sensor->pixel_array->ctrl_handler.error) अणु
		dev_err(&client->dev,
			"pixel array controls initialization failed (%d)\n",
			sensor->pixel_array->ctrl_handler.error);
		वापस sensor->pixel_array->ctrl_handler.error;
	पूर्ण

	sensor->pixel_array->sd.ctrl_handler =
		&sensor->pixel_array->ctrl_handler;

	v4l2_ctrl_cluster(2, &sensor->hflip);

	rval = v4l2_ctrl_handler_init(&sensor->src->ctrl_handler, 0);
	अगर (rval)
		वापस rval;

	sensor->src->ctrl_handler.lock = &sensor->mutex;

	sensor->pixel_rate_csi = v4l2_ctrl_new_std(
		&sensor->src->ctrl_handler, &ccs_ctrl_ops,
		V4L2_CID_PIXEL_RATE, 1, पूर्णांक_उच्च, 1, 1);

	अगर (sensor->src->ctrl_handler.error) अणु
		dev_err(&client->dev,
			"src controls initialization failed (%d)\n",
			sensor->src->ctrl_handler.error);
		वापस sensor->src->ctrl_handler.error;
	पूर्ण

	sensor->src->sd.ctrl_handler = &sensor->src->ctrl_handler;

	वापस 0;
पूर्ण

/*
 * For controls that require inक्रमmation on available media bus codes
 * and linke frequencies.
 */
अटल पूर्णांक ccs_init_late_controls(काष्ठा ccs_sensor *sensor)
अणु
	अचिन्हित दीर्घ *valid_link_freqs = &sensor->valid_link_freqs[
		sensor->csi_क्रमmat->compressed - sensor->compressed_min_bpp];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sensor->test_data); i++) अणु
		पूर्णांक max_value = (1 << sensor->csi_क्रमmat->width) - 1;

		sensor->test_data[i] = v4l2_ctrl_new_std(
				&sensor->pixel_array->ctrl_handler,
				&ccs_ctrl_ops, V4L2_CID_TEST_PATTERN_RED + i,
				0, max_value, 1, max_value);
	पूर्ण

	sensor->link_freq = v4l2_ctrl_new_पूर्णांक_menu(
		&sensor->src->ctrl_handler, &ccs_ctrl_ops,
		V4L2_CID_LINK_FREQ, __fls(*valid_link_freqs),
		__ffs(*valid_link_freqs), sensor->hwcfg.op_sys_घड़ी);

	वापस sensor->src->ctrl_handler.error;
पूर्ण

अटल व्योम ccs_मुक्त_controls(काष्ठा ccs_sensor *sensor)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sensor->ssds_used; i++)
		v4l2_ctrl_handler_मुक्त(&sensor->ssds[i].ctrl_handler);
पूर्ण

अटल पूर्णांक ccs_get_mbus_क्रमmats(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	काष्ठा ccs_pll *pll = &sensor->pll;
	u8 compressed_max_bpp = 0;
	अचिन्हित पूर्णांक type, n;
	अचिन्हित पूर्णांक i, pixel_order;
	पूर्णांक rval;

	type = CCS_LIM(sensor, DATA_FORMAT_MODEL_TYPE);

	dev_dbg(&client->dev, "data_format_model_type %d\n", type);

	rval = ccs_पढ़ो(sensor, PIXEL_ORDER, &pixel_order);
	अगर (rval)
		वापस rval;

	अगर (pixel_order >= ARRAY_SIZE(pixel_order_str)) अणु
		dev_dbg(&client->dev, "bad pixel order %d\n", pixel_order);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&client->dev, "pixel order %d (%s)\n", pixel_order,
		pixel_order_str[pixel_order]);

	चयन (type) अणु
	हाल CCS_DATA_FORMAT_MODEL_TYPE_NORMAL:
		n = SMIAPP_DATA_FORMAT_MODEL_TYPE_NORMAL_N;
		अवरोध;
	हाल CCS_DATA_FORMAT_MODEL_TYPE_EXTENDED:
		n = CCS_LIM_DATA_FORMAT_DESCRIPTOR_MAX_N + 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sensor->शेष_pixel_order = pixel_order;
	sensor->mbus_frame_fmts = 0;

	क्रम (i = 0; i < n; i++) अणु
		अचिन्हित पूर्णांक fmt, j;

		fmt = CCS_LIM_AT(sensor, DATA_FORMAT_DESCRIPTOR, i);

		dev_dbg(&client->dev, "%u: bpp %u, compressed %u\n",
			i, fmt >> 8, (u8)fmt);

		क्रम (j = 0; j < ARRAY_SIZE(ccs_csi_data_क्रमmats); j++) अणु
			स्थिर काष्ठा ccs_csi_data_क्रमmat *f =
				&ccs_csi_data_क्रमmats[j];

			अगर (f->pixel_order != CCS_PIXEL_ORDER_GRBG)
				जारी;

			अगर (f->width != fmt >>
			    CCS_DATA_FORMAT_DESCRIPTOR_UNCOMPRESSED_SHIFT ||
			    f->compressed !=
			    (fmt & CCS_DATA_FORMAT_DESCRIPTOR_COMPRESSED_MASK))
				जारी;

			dev_dbg(&client->dev, "jolly good! %d\n", j);

			sensor->शेष_mbus_frame_fmts |= 1 << j;
		पूर्ण
	पूर्ण

	/* Figure out which BPP values can be used with which क्रमmats. */
	pll->binning_horizontal = 1;
	pll->binning_vertical = 1;
	pll->scale_m = sensor->scale_m;

	क्रम (i = 0; i < ARRAY_SIZE(ccs_csi_data_क्रमmats); i++) अणु
		sensor->compressed_min_bpp =
			min(ccs_csi_data_क्रमmats[i].compressed,
			    sensor->compressed_min_bpp);
		compressed_max_bpp =
			max(ccs_csi_data_क्रमmats[i].compressed,
			    compressed_max_bpp);
	पूर्ण

	sensor->valid_link_freqs = devm_kसुस्मृति(
		&client->dev,
		compressed_max_bpp - sensor->compressed_min_bpp + 1,
		माप(*sensor->valid_link_freqs), GFP_KERNEL);
	अगर (!sensor->valid_link_freqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(ccs_csi_data_क्रमmats); i++) अणु
		स्थिर काष्ठा ccs_csi_data_क्रमmat *f =
			&ccs_csi_data_क्रमmats[i];
		अचिन्हित दीर्घ *valid_link_freqs =
			&sensor->valid_link_freqs[
				f->compressed - sensor->compressed_min_bpp];
		अचिन्हित पूर्णांक j;

		अगर (!(sensor->शेष_mbus_frame_fmts & 1 << i))
			जारी;

		pll->bits_per_pixel = f->compressed;

		क्रम (j = 0; sensor->hwcfg.op_sys_घड़ी[j]; j++) अणु
			pll->link_freq = sensor->hwcfg.op_sys_घड़ी[j];

			rval = ccs_pll_try(sensor, pll);
			dev_dbg(&client->dev, "link freq %u Hz, bpp %u %s\n",
				pll->link_freq, pll->bits_per_pixel,
				rval ? "not ok" : "ok");
			अगर (rval)
				जारी;

			set_bit(j, valid_link_freqs);
		पूर्ण

		अगर (!*valid_link_freqs) अणु
			dev_info(&client->dev,
				 "no valid link frequencies for %u bpp\n",
				 f->compressed);
			sensor->शेष_mbus_frame_fmts &= ~BIT(i);
			जारी;
		पूर्ण

		अगर (!sensor->csi_क्रमmat
		    || f->width > sensor->csi_क्रमmat->width
		    || (f->width == sensor->csi_क्रमmat->width
			&& f->compressed > sensor->csi_क्रमmat->compressed)) अणु
			sensor->csi_क्रमmat = f;
			sensor->पूर्णांकernal_csi_क्रमmat = f;
		पूर्ण
	पूर्ण

	अगर (!sensor->csi_क्रमmat) अणु
		dev_err(&client->dev, "no supported mbus code found\n");
		वापस -EINVAL;
	पूर्ण

	ccs_update_mbus_क्रमmats(sensor);

	वापस 0;
पूर्ण

अटल व्योम ccs_update_blanking(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा v4l2_ctrl *vblank = sensor->vblank;
	काष्ठा v4l2_ctrl *hblank = sensor->hblank;
	u16 min_fll, max_fll, min_llp, max_llp, min_lbp;
	पूर्णांक min, max;

	अगर (sensor->binning_vertical > 1 || sensor->binning_horizontal > 1) अणु
		min_fll = CCS_LIM(sensor, MIN_FRAME_LENGTH_LINES_BIN);
		max_fll = CCS_LIM(sensor, MAX_FRAME_LENGTH_LINES_BIN);
		min_llp = CCS_LIM(sensor, MIN_LINE_LENGTH_PCK_BIN);
		max_llp = CCS_LIM(sensor, MAX_LINE_LENGTH_PCK_BIN);
		min_lbp = CCS_LIM(sensor, MIN_LINE_BLANKING_PCK_BIN);
	पूर्ण अन्यथा अणु
		min_fll = CCS_LIM(sensor, MIN_FRAME_LENGTH_LINES);
		max_fll = CCS_LIM(sensor, MAX_FRAME_LENGTH_LINES);
		min_llp = CCS_LIM(sensor, MIN_LINE_LENGTH_PCK);
		max_llp = CCS_LIM(sensor, MAX_LINE_LENGTH_PCK);
		min_lbp = CCS_LIM(sensor, MIN_LINE_BLANKING_PCK);
	पूर्ण

	min = max_t(पूर्णांक,
		    CCS_LIM(sensor, MIN_FRAME_BLANKING_LINES),
		    min_fll - sensor->pixel_array->crop[CCS_PA_PAD_SRC].height);
	max = max_fll -	sensor->pixel_array->crop[CCS_PA_PAD_SRC].height;

	__v4l2_ctrl_modअगरy_range(vblank, min, max, vblank->step, min);

	min = max_t(पूर्णांक,
		    min_llp - sensor->pixel_array->crop[CCS_PA_PAD_SRC].width,
		    min_lbp);
	max = max_llp - sensor->pixel_array->crop[CCS_PA_PAD_SRC].width;

	__v4l2_ctrl_modअगरy_range(hblank, min, max, hblank->step, min);

	__ccs_update_exposure_limits(sensor);
पूर्ण

अटल पूर्णांक ccs_pll_blanking_update(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक rval;

	rval = ccs_pll_update(sensor);
	अगर (rval < 0)
		वापस rval;

	/* Output from pixel array, including blanking */
	ccs_update_blanking(sensor);

	dev_dbg(&client->dev, "vblank\t\t%d\n", sensor->vblank->val);
	dev_dbg(&client->dev, "hblank\t\t%d\n", sensor->hblank->val);

	dev_dbg(&client->dev, "real timeperframe\t100/%d\n",
		sensor->pll.pixel_rate_pixel_array /
		((sensor->pixel_array->crop[CCS_PA_PAD_SRC].width
		  + sensor->hblank->val) *
		 (sensor->pixel_array->crop[CCS_PA_PAD_SRC].height
		  + sensor->vblank->val) / 100));

	वापस 0;
पूर्ण

/*
 *
 * SMIA++ NVM handling
 *
 */

अटल पूर्णांक ccs_पढ़ो_nvm_page(काष्ठा ccs_sensor *sensor, u32 p, u8 *nvm,
			     u8 *status)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rval;
	u32 s;

	*status = 0;

	rval = ccs_ग_लिखो(sensor, DATA_TRANSFER_IF_1_PAGE_SELECT, p);
	अगर (rval)
		वापस rval;

	rval = ccs_ग_लिखो(sensor, DATA_TRANSFER_IF_1_CTRL,
			 CCS_DATA_TRANSFER_IF_1_CTRL_ENABLE);
	अगर (rval)
		वापस rval;

	rval = ccs_पढ़ो(sensor, DATA_TRANSFER_IF_1_STATUS, &s);
	अगर (rval)
		वापस rval;

	अगर (s & CCS_DATA_TRANSFER_IF_1_STATUS_IMPROPER_IF_USAGE) अणु
		*status = s;
		वापस -ENODATA;
	पूर्ण

	अगर (CCS_LIM(sensor, DATA_TRANSFER_IF_CAPABILITY) &
	    CCS_DATA_TRANSFER_IF_CAPABILITY_POLLING) अणु
		क्रम (i = 1000; i > 0; i--) अणु
			अगर (s & CCS_DATA_TRANSFER_IF_1_STATUS_READ_IF_READY)
				अवरोध;

			rval = ccs_पढ़ो(sensor, DATA_TRANSFER_IF_1_STATUS, &s);
			अगर (rval)
				वापस rval;
		पूर्ण

		अगर (!i)
			वापस -ETIMEDOUT;
	पूर्ण

	क्रम (i = 0; i <= CCS_LIM_DATA_TRANSFER_IF_1_DATA_MAX_P; i++) अणु
		u32 v;

		rval = ccs_पढ़ो(sensor, DATA_TRANSFER_IF_1_DATA(i), &v);
		अगर (rval)
			वापस rval;

		*nvm++ = v;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_पढ़ो_nvm(काष्ठा ccs_sensor *sensor, अचिन्हित अक्षर *nvm,
			माप_प्रकार nvm_size)
अणु
	u8 status = 0;
	u32 p;
	पूर्णांक rval = 0, rval2;

	क्रम (p = 0; p < nvm_size / (CCS_LIM_DATA_TRANSFER_IF_1_DATA_MAX_P + 1)
		     && !rval; p++) अणु
		rval = ccs_पढ़ो_nvm_page(sensor, p, nvm, &status);
		nvm += CCS_LIM_DATA_TRANSFER_IF_1_DATA_MAX_P + 1;
	पूर्ण

	अगर (rval == -ENODATA &&
	    status & CCS_DATA_TRANSFER_IF_1_STATUS_IMPROPER_IF_USAGE)
		rval = 0;

	rval2 = ccs_ग_लिखो(sensor, DATA_TRANSFER_IF_1_CTRL, 0);
	अगर (rval < 0)
		वापस rval;
	अन्यथा
		वापस rval2 ?: p * (CCS_LIM_DATA_TRANSFER_IF_1_DATA_MAX_P + 1);
पूर्ण

/*
 *
 * SMIA++ CCI address control
 *
 */
अटल पूर्णांक ccs_change_cci_addr(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक rval;
	u32 val;

	client->addr = sensor->hwcfg.i2c_addr_dfl;

	rval = ccs_ग_लिखो(sensor, CCI_ADDRESS_CTRL,
			 sensor->hwcfg.i2c_addr_alt << 1);
	अगर (rval)
		वापस rval;

	client->addr = sensor->hwcfg.i2c_addr_alt;

	/* verअगरy addr change went ok */
	rval = ccs_पढ़ो(sensor, CCI_ADDRESS_CTRL, &val);
	अगर (rval)
		वापस rval;

	अगर (val != sensor->hwcfg.i2c_addr_alt << 1)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 *
 * SMIA++ Mode Control
 *
 */
अटल पूर्णांक ccs_setup_flash_strobe(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा ccs_flash_strobe_parms *strobe_setup;
	अचिन्हित पूर्णांक ext_freq = sensor->hwcfg.ext_clk;
	u32 पंचांगp;
	u32 strobe_adjusपंचांगent;
	u32 strobe_width_high_rs;
	पूर्णांक rval;

	strobe_setup = sensor->hwcfg.strobe_setup;

	/*
	 * How to calculate रेजिस्टरs related to strobe length. Please
	 * करो not change, or अगर you करो at least know what you're
	 * करोing. :-)
	 *
	 * Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com> 2010-10-25
	 *
	 * flash_strobe_length [us] / 10^6 = (tFlash_strobe_width_ctrl
	 *	/ EXTCLK freq [Hz]) * flash_strobe_adjusपंचांगent
	 *
	 * tFlash_strobe_width_ctrl E N, [1 - 0xffff]
	 * flash_strobe_adjusपंचांगent E N, [1 - 0xff]
	 *
	 * The क्रमmula above is written as below to keep it on one
	 * line:
	 *
	 * l / 10^6 = w / e * a
	 *
	 * Let's mark w * a by x:
	 *
	 * x = w * a
	 *
	 * Thus, we get:
	 *
	 * x = l * e / 10^6
	 *
	 * The strobe width must be at least as दीर्घ as requested,
	 * thus rounding upwards is needed.
	 *
	 * x = (l * e + 10^6 - 1) / 10^6
	 * -----------------------------
	 *
	 * Maximum possible accuracy is wanted at all बार. Thus keep
	 * a as small as possible.
	 *
	 * Calculate a, assuming maximum w, with rounding upwards:
	 *
	 * a = (x + (2^16 - 1) - 1) / (2^16 - 1)
	 * -------------------------------------
	 *
	 * Thus, we also get w, with that a, with rounding upwards:
	 *
	 * w = (x + a - 1) / a
	 * -------------------
	 *
	 * To get limits:
	 *
	 * x E [1, (2^16 - 1) * (2^8 - 1)]
	 *
	 * Substituting maximum x to the original क्रमmula (with rounding),
	 * the maximum l is thus
	 *
	 * (2^16 - 1) * (2^8 - 1) * 10^6 = l * e + 10^6 - 1
	 *
	 * l = (10^6 * (2^16 - 1) * (2^8 - 1) - 10^6 + 1) / e
	 * --------------------------------------------------
	 *
	 * flash_strobe_length must be clamped between 1 and
	 * (10^6 * (2^16 - 1) * (2^8 - 1) - 10^6 + 1) / EXTCLK freq.
	 *
	 * Then,
	 *
	 * flash_strobe_adjusपंचांगent = ((flash_strobe_length *
	 *	EXTCLK freq + 10^6 - 1) / 10^6 + (2^16 - 1) - 1) / (2^16 - 1)
	 *
	 * tFlash_strobe_width_ctrl = ((flash_strobe_length *
	 *	EXTCLK freq + 10^6 - 1) / 10^6 +
	 *	flash_strobe_adjusपंचांगent - 1) / flash_strobe_adjusपंचांगent
	 */
	पंचांगp = भाग_u64(1000000ULL * ((1 << 16) - 1) * ((1 << 8) - 1) -
		      1000000 + 1, ext_freq);
	strobe_setup->strobe_width_high_us =
		clamp_t(u32, strobe_setup->strobe_width_high_us, 1, पंचांगp);

	पंचांगp = भाग_u64(((u64)strobe_setup->strobe_width_high_us * (u64)ext_freq +
			1000000 - 1), 1000000ULL);
	strobe_adjusपंचांगent = (पंचांगp + (1 << 16) - 1 - 1) / ((1 << 16) - 1);
	strobe_width_high_rs = (पंचांगp + strobe_adjusपंचांगent - 1) /
				strobe_adjusपंचांगent;

	rval = ccs_ग_लिखो(sensor, FLASH_MODE_RS, strobe_setup->mode);
	अगर (rval < 0)
		जाओ out;

	rval = ccs_ग_लिखो(sensor, FLASH_STROBE_ADJUSTMENT, strobe_adjusपंचांगent);
	अगर (rval < 0)
		जाओ out;

	rval = ccs_ग_लिखो(sensor, TFLASH_STROBE_WIDTH_HIGH_RS_CTRL,
			 strobe_width_high_rs);
	अगर (rval < 0)
		जाओ out;

	rval = ccs_ग_लिखो(sensor, TFLASH_STROBE_DELAY_RS_CTRL,
			 strobe_setup->strobe_delay);
	अगर (rval < 0)
		जाओ out;

	rval = ccs_ग_लिखो(sensor, FLASH_STROBE_START_POINT,
			 strobe_setup->stobe_start_poपूर्णांक);
	अगर (rval < 0)
		जाओ out;

	rval = ccs_ग_लिखो(sensor, FLASH_TRIGGER_RS, strobe_setup->trigger);

out:
	sensor->hwcfg.strobe_setup->trigger = 0;

	वापस rval;
पूर्ण

/* -----------------------------------------------------------------------------
 * Power management
 */

अटल पूर्णांक ccs_ग_लिखो_msr_regs(काष्ठा ccs_sensor *sensor)
अणु
	पूर्णांक rval;

	rval = ccs_ग_लिखो_data_regs(sensor,
				   sensor->sdata.sensor_manufacturer_regs,
				   sensor->sdata.num_sensor_manufacturer_regs);
	अगर (rval)
		वापस rval;

	वापस ccs_ग_लिखो_data_regs(sensor,
				   sensor->mdata.module_manufacturer_regs,
				   sensor->mdata.num_module_manufacturer_regs);
पूर्ण

अटल पूर्णांक ccs_update_phy_ctrl(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	u8 val;

	अगर (!sensor->ccs_limits)
		वापस 0;

	अगर (CCS_LIM(sensor, PHY_CTRL_CAPABILITY) &
	    CCS_PHY_CTRL_CAPABILITY_AUTO_PHY_CTL) अणु
		val = CCS_PHY_CTRL_AUTO;
	पूर्ण अन्यथा अगर (CCS_LIM(sensor, PHY_CTRL_CAPABILITY) &
		   CCS_PHY_CTRL_CAPABILITY_UI_PHY_CTL) अणु
		val = CCS_PHY_CTRL_UI;
	पूर्ण अन्यथा अणु
		dev_err(&client->dev, "manual PHY control not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस ccs_ग_लिखो(sensor, PHY_CTRL, val);
पूर्ण

अटल पूर्णांक ccs_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *subdev = dev_get_drvdata(dev);
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);
	/*
	 * The sub-device related to the I2C device is always the
	 * source one, i.e. ssds[0].
	 */
	काष्ठा ccs_sensor *sensor =
		container_of(ssd, काष्ठा ccs_sensor, ssds[0]);
	स्थिर काष्ठा ccs_device *ccsdev = device_get_match_data(dev);
	पूर्णांक rval;

	rval = regulator_bulk_enable(ARRAY_SIZE(ccs_regulators),
				     sensor->regulators);
	अगर (rval) अणु
		dev_err(dev, "failed to enable vana regulator\n");
		वापस rval;
	पूर्ण

	अगर (sensor->reset || sensor->xshutकरोwn || sensor->ext_clk) अणु
		अचिन्हित पूर्णांक sleep;

		rval = clk_prepare_enable(sensor->ext_clk);
		अगर (rval < 0) अणु
			dev_dbg(dev, "failed to enable xclk\n");
			जाओ out_xclk_fail;
		पूर्ण

		gpiod_set_value(sensor->reset, 0);
		gpiod_set_value(sensor->xshutकरोwn, 1);

		अगर (ccsdev->flags & CCS_DEVICE_FLAG_IS_SMIA)
			sleep = SMIAPP_RESET_DELAY(sensor->hwcfg.ext_clk);
		अन्यथा
			sleep = 5000;

		usleep_range(sleep, sleep);
	पूर्ण

	/*
	 * Failures to respond to the address change command have been noticed.
	 * Those failures seem to be caused by the sensor requiring a दीर्घer
	 * boot समय than advertised. An additional 10ms delay seems to work
	 * around the issue, but the SMIA++ I2C ग_लिखो retry hack makes the delay
	 * unnecessary. The failures need to be investigated to find a proper
	 * fix, and a delay will likely need to be added here अगर the I2C ग_लिखो
	 * retry hack is reverted beक्रमe the root cause of the boot समय issue
	 * is found.
	 */

	अगर (!sensor->reset && !sensor->xshutकरोwn) अणु
		u8 retry = 100;
		u32 reset;

		rval = ccs_ग_लिखो(sensor, SOFTWARE_RESET, CCS_SOFTWARE_RESET_ON);
		अगर (rval < 0) अणु
			dev_err(dev, "software reset failed\n");
			जाओ out_cci_addr_fail;
		पूर्ण

		करो अणु
			rval = ccs_पढ़ो(sensor, SOFTWARE_RESET, &reset);
			reset = !rval && reset == CCS_SOFTWARE_RESET_OFF;
			अगर (reset)
				अवरोध;

			usleep_range(1000, 2000);
		पूर्ण जबतक (--retry);

		अगर (!reset)
			वापस -EIO;
	पूर्ण

	अगर (sensor->hwcfg.i2c_addr_alt) अणु
		rval = ccs_change_cci_addr(sensor);
		अगर (rval) अणु
			dev_err(dev, "cci address change error\n");
			जाओ out_cci_addr_fail;
		पूर्ण
	पूर्ण

	rval = ccs_ग_लिखो(sensor, COMPRESSION_MODE,
			 CCS_COMPRESSION_MODE_DPCM_PCM_SIMPLE);
	अगर (rval) अणु
		dev_err(dev, "compression mode set failed\n");
		जाओ out_cci_addr_fail;
	पूर्ण

	rval = ccs_ग_लिखो(sensor, EXTCLK_FREQUENCY_MHZ,
			 sensor->hwcfg.ext_clk / (1000000 / (1 << 8)));
	अगर (rval) अणु
		dev_err(dev, "extclk frequency set failed\n");
		जाओ out_cci_addr_fail;
	पूर्ण

	rval = ccs_ग_लिखो(sensor, CSI_LANE_MODE, sensor->hwcfg.lanes - 1);
	अगर (rval) अणु
		dev_err(dev, "csi lane mode set failed\n");
		जाओ out_cci_addr_fail;
	पूर्ण

	rval = ccs_ग_लिखो(sensor, FAST_STANDBY_CTRL,
			 CCS_FAST_STANDBY_CTRL_FRAME_TRUNCATION);
	अगर (rval) अणु
		dev_err(dev, "fast standby set failed\n");
		जाओ out_cci_addr_fail;
	पूर्ण

	rval = ccs_ग_लिखो(sensor, CSI_SIGNALING_MODE,
			 sensor->hwcfg.csi_संकेतling_mode);
	अगर (rval) अणु
		dev_err(dev, "csi signalling mode set failed\n");
		जाओ out_cci_addr_fail;
	पूर्ण

	rval = ccs_update_phy_ctrl(sensor);
	अगर (rval < 0)
		जाओ out_cci_addr_fail;

	rval = ccs_ग_लिखो_msr_regs(sensor);
	अगर (rval)
		जाओ out_cci_addr_fail;

	rval = ccs_call_quirk(sensor, post_घातeron);
	अगर (rval) अणु
		dev_err(dev, "post_poweron quirks failed\n");
		जाओ out_cci_addr_fail;
	पूर्ण

	वापस 0;

out_cci_addr_fail:
	gpiod_set_value(sensor->reset, 1);
	gpiod_set_value(sensor->xshutकरोwn, 0);
	clk_disable_unprepare(sensor->ext_clk);

out_xclk_fail:
	regulator_bulk_disable(ARRAY_SIZE(ccs_regulators),
			       sensor->regulators);

	वापस rval;
पूर्ण

अटल पूर्णांक ccs_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *subdev = dev_get_drvdata(dev);
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);
	काष्ठा ccs_sensor *sensor =
		container_of(ssd, काष्ठा ccs_sensor, ssds[0]);

	/*
	 * Currently घातer/घड़ी to lens are enable/disabled separately
	 * but they are essentially the same संकेतs. So अगर the sensor is
	 * घातered off जबतक the lens is घातered on the sensor करोes not
	 * really see a घातer off and next समय the cci address change
	 * will fail. So करो a soft reset explicitly here.
	 */
	अगर (sensor->hwcfg.i2c_addr_alt)
		ccs_ग_लिखो(sensor, SOFTWARE_RESET, CCS_SOFTWARE_RESET_ON);

	gpiod_set_value(sensor->reset, 1);
	gpiod_set_value(sensor->xshutकरोwn, 0);
	clk_disable_unprepare(sensor->ext_clk);
	usleep_range(5000, 5000);
	regulator_bulk_disable(ARRAY_SIZE(ccs_regulators),
			       sensor->regulators);
	sensor->streaming = false;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Video stream management
 */

अटल पूर्णांक ccs_start_streaming(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	अचिन्हित पूर्णांक binning_mode;
	पूर्णांक rval;

	mutex_lock(&sensor->mutex);

	rval = ccs_ग_लिखो(sensor, CSI_DATA_FORMAT,
			 (sensor->csi_क्रमmat->width << 8) |
			 sensor->csi_क्रमmat->compressed);
	अगर (rval)
		जाओ out;

	/* Binning configuration */
	अगर (sensor->binning_horizontal == 1 &&
	    sensor->binning_vertical == 1) अणु
		binning_mode = 0;
	पूर्ण अन्यथा अणु
		u8 binning_type =
			(sensor->binning_horizontal << 4)
			| sensor->binning_vertical;

		rval = ccs_ग_लिखो(sensor, BINNING_TYPE, binning_type);
		अगर (rval < 0)
			जाओ out;

		binning_mode = 1;
	पूर्ण
	rval = ccs_ग_लिखो(sensor, BINNING_MODE, binning_mode);
	अगर (rval < 0)
		जाओ out;

	/* Set up PLL */
	rval = ccs_pll_configure(sensor);
	अगर (rval)
		जाओ out;

	/* Analog crop start coordinates */
	rval = ccs_ग_लिखो(sensor, X_ADDR_START,
			 sensor->pixel_array->crop[CCS_PA_PAD_SRC].left);
	अगर (rval < 0)
		जाओ out;

	rval = ccs_ग_लिखो(sensor, Y_ADDR_START,
			 sensor->pixel_array->crop[CCS_PA_PAD_SRC].top);
	अगर (rval < 0)
		जाओ out;

	/* Analog crop end coordinates */
	rval = ccs_ग_लिखो(
		sensor, X_ADDR_END,
		sensor->pixel_array->crop[CCS_PA_PAD_SRC].left
		+ sensor->pixel_array->crop[CCS_PA_PAD_SRC].width - 1);
	अगर (rval < 0)
		जाओ out;

	rval = ccs_ग_लिखो(
		sensor, Y_ADDR_END,
		sensor->pixel_array->crop[CCS_PA_PAD_SRC].top
		+ sensor->pixel_array->crop[CCS_PA_PAD_SRC].height - 1);
	अगर (rval < 0)
		जाओ out;

	/*
	 * Output from pixel array, including blanking, is set using
	 * controls below. No need to set here.
	 */

	/* Digital crop */
	अगर (CCS_LIM(sensor, DIGITAL_CROP_CAPABILITY)
	    == CCS_DIGITAL_CROP_CAPABILITY_INPUT_CROP) अणु
		rval = ccs_ग_लिखो(
			sensor, DIGITAL_CROP_X_OFFSET,
			sensor->scaler->crop[CCS_PAD_SINK].left);
		अगर (rval < 0)
			जाओ out;

		rval = ccs_ग_लिखो(
			sensor, DIGITAL_CROP_Y_OFFSET,
			sensor->scaler->crop[CCS_PAD_SINK].top);
		अगर (rval < 0)
			जाओ out;

		rval = ccs_ग_लिखो(
			sensor, DIGITAL_CROP_IMAGE_WIDTH,
			sensor->scaler->crop[CCS_PAD_SINK].width);
		अगर (rval < 0)
			जाओ out;

		rval = ccs_ग_लिखो(
			sensor, DIGITAL_CROP_IMAGE_HEIGHT,
			sensor->scaler->crop[CCS_PAD_SINK].height);
		अगर (rval < 0)
			जाओ out;
	पूर्ण

	/* Scaling */
	अगर (CCS_LIM(sensor, SCALING_CAPABILITY)
	    != CCS_SCALING_CAPABILITY_NONE) अणु
		rval = ccs_ग_लिखो(sensor, SCALING_MODE, sensor->scaling_mode);
		अगर (rval < 0)
			जाओ out;

		rval = ccs_ग_लिखो(sensor, SCALE_M, sensor->scale_m);
		अगर (rval < 0)
			जाओ out;
	पूर्ण

	/* Output size from sensor */
	rval = ccs_ग_लिखो(sensor, X_OUTPUT_SIZE,
			 sensor->src->crop[CCS_PAD_SRC].width);
	अगर (rval < 0)
		जाओ out;
	rval = ccs_ग_लिखो(sensor, Y_OUTPUT_SIZE,
			 sensor->src->crop[CCS_PAD_SRC].height);
	अगर (rval < 0)
		जाओ out;

	अगर (CCS_LIM(sensor, FLASH_MODE_CAPABILITY) &
	    (CCS_FLASH_MODE_CAPABILITY_SINGLE_STROBE |
	     SMIAPP_FLASH_MODE_CAPABILITY_MULTIPLE_STROBE) &&
	    sensor->hwcfg.strobe_setup != शून्य &&
	    sensor->hwcfg.strobe_setup->trigger != 0) अणु
		rval = ccs_setup_flash_strobe(sensor);
		अगर (rval)
			जाओ out;
	पूर्ण

	rval = ccs_call_quirk(sensor, pre_streamon);
	अगर (rval) अणु
		dev_err(&client->dev, "pre_streamon quirks failed\n");
		जाओ out;
	पूर्ण

	rval = ccs_ग_लिखो(sensor, MODE_SELECT, CCS_MODE_SELECT_STREAMING);

out:
	mutex_unlock(&sensor->mutex);

	वापस rval;
पूर्ण

अटल पूर्णांक ccs_stop_streaming(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक rval;

	mutex_lock(&sensor->mutex);
	rval = ccs_ग_लिखो(sensor, MODE_SELECT, CCS_MODE_SELECT_SOFTWARE_STANDBY);
	अगर (rval)
		जाओ out;

	rval = ccs_call_quirk(sensor, post_streamoff);
	अगर (rval)
		dev_err(&client->dev, "post_streamoff quirks failed\n");

out:
	mutex_unlock(&sensor->mutex);
	वापस rval;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev video operations
 */

अटल पूर्णांक ccs_pm_get_init(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक rval;

	rval = pm_runसमय_get_sync(&client->dev);
	अगर (rval < 0) अणु
		pm_runसमय_put_noidle(&client->dev);

		वापस rval;
	पूर्ण अन्यथा अगर (!rval) अणु
		rval = v4l2_ctrl_handler_setup(&sensor->pixel_array->
					       ctrl_handler);
		अगर (rval)
			वापस rval;

		वापस v4l2_ctrl_handler_setup(&sensor->src->ctrl_handler);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_set_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक rval;

	अगर (sensor->streaming == enable)
		वापस 0;

	अगर (!enable) अणु
		ccs_stop_streaming(sensor);
		sensor->streaming = false;
		pm_runसमय_mark_last_busy(&client->dev);
		pm_runसमय_put_स्वतःsuspend(&client->dev);

		वापस 0;
	पूर्ण

	rval = ccs_pm_get_init(sensor);
	अगर (rval)
		वापस rval;

	sensor->streaming = true;

	rval = ccs_start_streaming(sensor);
	अगर (rval < 0) अणु
		sensor->streaming = false;
		pm_runसमय_mark_last_busy(&client->dev);
		pm_runसमय_put_स्वतःsuspend(&client->dev);
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक ccs_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	अचिन्हित पूर्णांक i;
	पूर्णांक idx = -1;
	पूर्णांक rval = -EINVAL;

	mutex_lock(&sensor->mutex);

	dev_err(&client->dev, "subdev %s, pad %d, index %d\n",
		subdev->name, code->pad, code->index);

	अगर (subdev != &sensor->src->sd || code->pad != CCS_PAD_SRC) अणु
		अगर (code->index)
			जाओ out;

		code->code = sensor->पूर्णांकernal_csi_क्रमmat->code;
		rval = 0;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ccs_csi_data_क्रमmats); i++) अणु
		अगर (sensor->mbus_frame_fmts & (1 << i))
			idx++;

		अगर (idx == code->index) अणु
			code->code = ccs_csi_data_क्रमmats[i].code;
			dev_err(&client->dev, "found index %d, i %d, code %x\n",
				code->index, i, code->code);
			rval = 0;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&sensor->mutex);

	वापस rval;
पूर्ण

अटल u32 __ccs_get_mbus_code(काष्ठा v4l2_subdev *subdev, अचिन्हित पूर्णांक pad)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);

	अगर (subdev == &sensor->src->sd && pad == CCS_PAD_SRC)
		वापस sensor->csi_क्रमmat->code;
	अन्यथा
		वापस sensor->पूर्णांकernal_csi_क्रमmat->code;
पूर्ण

अटल पूर्णांक __ccs_get_क्रमmat(काष्ठा v4l2_subdev *subdev,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(subdev, cfg,
							  fmt->pad);
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_rect *r;

		अगर (fmt->pad == ssd->source_pad)
			r = &ssd->crop[ssd->source_pad];
		अन्यथा
			r = &ssd->sink_fmt;

		fmt->क्रमmat.code = __ccs_get_mbus_code(subdev, fmt->pad);
		fmt->क्रमmat.width = r->width;
		fmt->क्रमmat.height = r->height;
		fmt->क्रमmat.field = V4L2_FIELD_NONE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_get_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	पूर्णांक rval;

	mutex_lock(&sensor->mutex);
	rval = __ccs_get_क्रमmat(subdev, cfg, fmt);
	mutex_unlock(&sensor->mutex);

	वापस rval;
पूर्ण

अटल व्योम ccs_get_crop_compose(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_rect **crops,
				 काष्ठा v4l2_rect **comps, पूर्णांक which)
अणु
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);
	अचिन्हित पूर्णांक i;

	अगर (which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		अगर (crops)
			क्रम (i = 0; i < subdev->entity.num_pads; i++)
				crops[i] = &ssd->crop[i];
		अगर (comps)
			*comps = &ssd->compose;
	पूर्ण अन्यथा अणु
		अगर (crops) अणु
			क्रम (i = 0; i < subdev->entity.num_pads; i++)
				crops[i] = v4l2_subdev_get_try_crop(subdev,
								    cfg, i);
		पूर्ण
		अगर (comps)
			*comps = v4l2_subdev_get_try_compose(subdev, cfg,
							     CCS_PAD_SINK);
	पूर्ण
पूर्ण

/* Changes require propagation only on sink pad. */
अटल व्योम ccs_propagate(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg, पूर्णांक which,
			  पूर्णांक target)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);
	काष्ठा v4l2_rect *comp, *crops[CCS_PADS];

	ccs_get_crop_compose(subdev, cfg, crops, &comp, which);

	चयन (target) अणु
	हाल V4L2_SEL_TGT_CROP:
		comp->width = crops[CCS_PAD_SINK]->width;
		comp->height = crops[CCS_PAD_SINK]->height;
		अगर (which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
			अगर (ssd == sensor->scaler) अणु
				sensor->scale_m = CCS_LIM(sensor, SCALER_N_MIN);
				sensor->scaling_mode =
					CCS_SCALING_MODE_NO_SCALING;
			पूर्ण अन्यथा अगर (ssd == sensor->binner) अणु
				sensor->binning_horizontal = 1;
				sensor->binning_vertical = 1;
			पूर्ण
		पूर्ण
		fallthrough;
	हाल V4L2_SEL_TGT_COMPOSE:
		*crops[CCS_PAD_SRC] = *comp;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ccs_csi_data_क्रमmat
*ccs_validate_csi_data_क्रमmat(काष्ठा ccs_sensor *sensor, u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ccs_csi_data_क्रमmats); i++) अणु
		अगर (sensor->mbus_frame_fmts & (1 << i) &&
		    ccs_csi_data_क्रमmats[i].code == code)
			वापस &ccs_csi_data_क्रमmats[i];
	पूर्ण

	वापस sensor->csi_क्रमmat;
पूर्ण

अटल पूर्णांक ccs_set_क्रमmat_source(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	स्थिर काष्ठा ccs_csi_data_क्रमmat *csi_क्रमmat,
		*old_csi_क्रमmat = sensor->csi_क्रमmat;
	अचिन्हित दीर्घ *valid_link_freqs;
	u32 code = fmt->क्रमmat.code;
	अचिन्हित पूर्णांक i;
	पूर्णांक rval;

	rval = __ccs_get_क्रमmat(subdev, cfg, fmt);
	अगर (rval)
		वापस rval;

	/*
	 * Media bus code is changeable on src subdev's source pad. On
	 * other source pads we just get क्रमmat here.
	 */
	अगर (subdev != &sensor->src->sd)
		वापस 0;

	csi_क्रमmat = ccs_validate_csi_data_क्रमmat(sensor, code);

	fmt->क्रमmat.code = csi_क्रमmat->code;

	अगर (fmt->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस 0;

	sensor->csi_क्रमmat = csi_क्रमmat;

	अगर (csi_क्रमmat->width != old_csi_क्रमmat->width)
		क्रम (i = 0; i < ARRAY_SIZE(sensor->test_data); i++)
			__v4l2_ctrl_modअगरy_range(
				sensor->test_data[i], 0,
				(1 << csi_क्रमmat->width) - 1, 1, 0);

	अगर (csi_क्रमmat->compressed == old_csi_क्रमmat->compressed)
		वापस 0;

	valid_link_freqs =
		&sensor->valid_link_freqs[sensor->csi_क्रमmat->compressed
					  - sensor->compressed_min_bpp];

	__v4l2_ctrl_modअगरy_range(
		sensor->link_freq, 0,
		__fls(*valid_link_freqs), ~*valid_link_freqs,
		__ffs(*valid_link_freqs));

	वापस ccs_pll_update(sensor);
पूर्ण

अटल पूर्णांक ccs_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);
	काष्ठा v4l2_rect *crops[CCS_PADS];

	mutex_lock(&sensor->mutex);

	अगर (fmt->pad == ssd->source_pad) अणु
		पूर्णांक rval;

		rval = ccs_set_क्रमmat_source(subdev, cfg, fmt);

		mutex_unlock(&sensor->mutex);

		वापस rval;
	पूर्ण

	/* Sink pad. Width and height are changeable here. */
	fmt->क्रमmat.code = __ccs_get_mbus_code(subdev, fmt->pad);
	fmt->क्रमmat.width &= ~1;
	fmt->क्रमmat.height &= ~1;
	fmt->क्रमmat.field = V4L2_FIELD_NONE;

	fmt->क्रमmat.width =
		clamp(fmt->क्रमmat.width,
		      CCS_LIM(sensor, MIN_X_OUTPUT_SIZE),
		      CCS_LIM(sensor, MAX_X_OUTPUT_SIZE));
	fmt->क्रमmat.height =
		clamp(fmt->क्रमmat.height,
		      CCS_LIM(sensor, MIN_Y_OUTPUT_SIZE),
		      CCS_LIM(sensor, MAX_Y_OUTPUT_SIZE));

	ccs_get_crop_compose(subdev, cfg, crops, शून्य, fmt->which);

	crops[ssd->sink_pad]->left = 0;
	crops[ssd->sink_pad]->top = 0;
	crops[ssd->sink_pad]->width = fmt->क्रमmat.width;
	crops[ssd->sink_pad]->height = fmt->क्रमmat.height;
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		ssd->sink_fmt = *crops[ssd->sink_pad];
	ccs_propagate(subdev, cfg, fmt->which, V4L2_SEL_TGT_CROP);

	mutex_unlock(&sensor->mutex);

	वापस 0;
पूर्ण

/*
 * Calculate goodness of scaled image size compared to expected image
 * size and flags provided.
 */
#घोषणा SCALING_GOODNESS		100000
#घोषणा SCALING_GOODNESS_EXTREME	100000000
अटल पूर्णांक scaling_goodness(काष्ठा v4l2_subdev *subdev, पूर्णांक w, पूर्णांक ask_w,
			    पूर्णांक h, पूर्णांक ask_h, u32 flags)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	पूर्णांक val = 0;

	w &= ~1;
	ask_w &= ~1;
	h &= ~1;
	ask_h &= ~1;

	अगर (flags & V4L2_SEL_FLAG_GE) अणु
		अगर (w < ask_w)
			val -= SCALING_GOODNESS;
		अगर (h < ask_h)
			val -= SCALING_GOODNESS;
	पूर्ण

	अगर (flags & V4L2_SEL_FLAG_LE) अणु
		अगर (w > ask_w)
			val -= SCALING_GOODNESS;
		अगर (h > ask_h)
			val -= SCALING_GOODNESS;
	पूर्ण

	val -= असल(w - ask_w);
	val -= असल(h - ask_h);

	अगर (w < CCS_LIM(sensor, MIN_X_OUTPUT_SIZE))
		val -= SCALING_GOODNESS_EXTREME;

	dev_dbg(&client->dev, "w %d ask_w %d h %d ask_h %d goodness %d\n",
		w, ask_w, h, ask_h, val);

	वापस val;
पूर्ण

अटल व्योम ccs_set_compose_binner(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_selection *sel,
				   काष्ठा v4l2_rect **crops,
				   काष्ठा v4l2_rect *comp)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक binh = 1, binv = 1;
	पूर्णांक best = scaling_goodness(
		subdev,
		crops[CCS_PAD_SINK]->width, sel->r.width,
		crops[CCS_PAD_SINK]->height, sel->r.height, sel->flags);

	क्रम (i = 0; i < sensor->nbinning_subtypes; i++) अणु
		पूर्णांक this = scaling_goodness(
			subdev,
			crops[CCS_PAD_SINK]->width
			/ sensor->binning_subtypes[i].horizontal,
			sel->r.width,
			crops[CCS_PAD_SINK]->height
			/ sensor->binning_subtypes[i].vertical,
			sel->r.height, sel->flags);

		अगर (this > best) अणु
			binh = sensor->binning_subtypes[i].horizontal;
			binv = sensor->binning_subtypes[i].vertical;
			best = this;
		पूर्ण
	पूर्ण
	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		sensor->binning_vertical = binv;
		sensor->binning_horizontal = binh;
	पूर्ण

	sel->r.width = (crops[CCS_PAD_SINK]->width / binh) & ~1;
	sel->r.height = (crops[CCS_PAD_SINK]->height / binv) & ~1;
पूर्ण

/*
 * Calculate best scaling ratio and mode क्रम given output resolution.
 *
 * Try all of these: horizontal ratio, vertical ratio and smallest
 * size possible (horizontally).
 *
 * Also try whether horizontal scaler or full scaler gives a better
 * result.
 */
अटल व्योम ccs_set_compose_scaler(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_selection *sel,
				   काष्ठा v4l2_rect **crops,
				   काष्ठा v4l2_rect *comp)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	u32 min, max, a, b, max_m;
	u32 scale_m = CCS_LIM(sensor, SCALER_N_MIN);
	पूर्णांक mode = CCS_SCALING_MODE_HORIZONTAL;
	u32 try[4];
	u32 ntry = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक best = पूर्णांक_न्यून;

	sel->r.width = min_t(अचिन्हित पूर्णांक, sel->r.width,
			     crops[CCS_PAD_SINK]->width);
	sel->r.height = min_t(अचिन्हित पूर्णांक, sel->r.height,
			      crops[CCS_PAD_SINK]->height);

	a = crops[CCS_PAD_SINK]->width
		* CCS_LIM(sensor, SCALER_N_MIN) / sel->r.width;
	b = crops[CCS_PAD_SINK]->height
		* CCS_LIM(sensor, SCALER_N_MIN) / sel->r.height;
	max_m = crops[CCS_PAD_SINK]->width
		* CCS_LIM(sensor, SCALER_N_MIN)
		/ CCS_LIM(sensor, MIN_X_OUTPUT_SIZE);

	a = clamp(a, CCS_LIM(sensor, SCALER_M_MIN),
		  CCS_LIM(sensor, SCALER_M_MAX));
	b = clamp(b, CCS_LIM(sensor, SCALER_M_MIN),
		  CCS_LIM(sensor, SCALER_M_MAX));
	max_m = clamp(max_m, CCS_LIM(sensor, SCALER_M_MIN),
		      CCS_LIM(sensor, SCALER_M_MAX));

	dev_dbg(&client->dev, "scaling: a %d b %d max_m %d\n", a, b, max_m);

	min = min(max_m, min(a, b));
	max = min(max_m, max(a, b));

	try[ntry] = min;
	ntry++;
	अगर (min != max) अणु
		try[ntry] = max;
		ntry++;
	पूर्ण
	अगर (max != max_m) अणु
		try[ntry] = min + 1;
		ntry++;
		अगर (min != max) अणु
			try[ntry] = max + 1;
			ntry++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ntry; i++) अणु
		पूर्णांक this = scaling_goodness(
			subdev,
			crops[CCS_PAD_SINK]->width
			/ try[i] * CCS_LIM(sensor, SCALER_N_MIN),
			sel->r.width,
			crops[CCS_PAD_SINK]->height,
			sel->r.height,
			sel->flags);

		dev_dbg(&client->dev, "trying factor %d (%d)\n", try[i], i);

		अगर (this > best) अणु
			scale_m = try[i];
			mode = CCS_SCALING_MODE_HORIZONTAL;
			best = this;
		पूर्ण

		अगर (CCS_LIM(sensor, SCALING_CAPABILITY)
		    == CCS_SCALING_CAPABILITY_HORIZONTAL)
			जारी;

		this = scaling_goodness(
			subdev, crops[CCS_PAD_SINK]->width
			/ try[i]
			* CCS_LIM(sensor, SCALER_N_MIN),
			sel->r.width,
			crops[CCS_PAD_SINK]->height
			/ try[i]
			* CCS_LIM(sensor, SCALER_N_MIN),
			sel->r.height,
			sel->flags);

		अगर (this > best) अणु
			scale_m = try[i];
			mode = SMIAPP_SCALING_MODE_BOTH;
			best = this;
		पूर्ण
	पूर्ण

	sel->r.width =
		(crops[CCS_PAD_SINK]->width
		 / scale_m
		 * CCS_LIM(sensor, SCALER_N_MIN)) & ~1;
	अगर (mode == SMIAPP_SCALING_MODE_BOTH)
		sel->r.height =
			(crops[CCS_PAD_SINK]->height
			 / scale_m
			 * CCS_LIM(sensor, SCALER_N_MIN))
			& ~1;
	अन्यथा
		sel->r.height = crops[CCS_PAD_SINK]->height;

	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		sensor->scale_m = scale_m;
		sensor->scaling_mode = mode;
	पूर्ण
पूर्ण
/* We're only called on source pads. This function sets scaling. */
अटल पूर्णांक ccs_set_compose(काष्ठा v4l2_subdev *subdev,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);
	काष्ठा v4l2_rect *comp, *crops[CCS_PADS];

	ccs_get_crop_compose(subdev, cfg, crops, &comp, sel->which);

	sel->r.top = 0;
	sel->r.left = 0;

	अगर (ssd == sensor->binner)
		ccs_set_compose_binner(subdev, cfg, sel, crops, comp);
	अन्यथा
		ccs_set_compose_scaler(subdev, cfg, sel, crops, comp);

	*comp = sel->r;
	ccs_propagate(subdev, cfg, sel->which, V4L2_SEL_TGT_COMPOSE);

	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस ccs_pll_blanking_update(sensor);

	वापस 0;
पूर्ण

अटल पूर्णांक __ccs_sel_supported(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);

	/* We only implement crop in three places. */
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		अगर (ssd == sensor->pixel_array && sel->pad == CCS_PA_PAD_SRC)
			वापस 0;
		अगर (ssd == sensor->src && sel->pad == CCS_PAD_SRC)
			वापस 0;
		अगर (ssd == sensor->scaler && sel->pad == CCS_PAD_SINK &&
		    CCS_LIM(sensor, DIGITAL_CROP_CAPABILITY)
		    == CCS_DIGITAL_CROP_CAPABILITY_INPUT_CROP)
			वापस 0;
		वापस -EINVAL;
	हाल V4L2_SEL_TGT_NATIVE_SIZE:
		अगर (ssd == sensor->pixel_array && sel->pad == CCS_PA_PAD_SRC)
			वापस 0;
		वापस -EINVAL;
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		अगर (sel->pad == ssd->source_pad)
			वापस -EINVAL;
		अगर (ssd == sensor->binner)
			वापस 0;
		अगर (ssd == sensor->scaler && CCS_LIM(sensor, SCALING_CAPABILITY)
		    != CCS_SCALING_CAPABILITY_NONE)
			वापस 0;
		fallthrough;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ccs_set_crop(काष्ठा v4l2_subdev *subdev,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);
	काष्ठा v4l2_rect *src_size, *crops[CCS_PADS];
	काष्ठा v4l2_rect _r;

	ccs_get_crop_compose(subdev, cfg, crops, शून्य, sel->which);

	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		अगर (sel->pad == ssd->sink_pad)
			src_size = &ssd->sink_fmt;
		अन्यथा
			src_size = &ssd->compose;
	पूर्ण अन्यथा अणु
		अगर (sel->pad == ssd->sink_pad) अणु
			_r.left = 0;
			_r.top = 0;
			_r.width = v4l2_subdev_get_try_क्रमmat(subdev, cfg,
							      sel->pad)
				->width;
			_r.height = v4l2_subdev_get_try_क्रमmat(subdev, cfg,
							       sel->pad)
				->height;
			src_size = &_r;
		पूर्ण अन्यथा अणु
			src_size = v4l2_subdev_get_try_compose(
				subdev, cfg, ssd->sink_pad);
		पूर्ण
	पूर्ण

	अगर (ssd == sensor->src && sel->pad == CCS_PAD_SRC) अणु
		sel->r.left = 0;
		sel->r.top = 0;
	पूर्ण

	sel->r.width = min(sel->r.width, src_size->width);
	sel->r.height = min(sel->r.height, src_size->height);

	sel->r.left = min_t(पूर्णांक, sel->r.left, src_size->width - sel->r.width);
	sel->r.top = min_t(पूर्णांक, sel->r.top, src_size->height - sel->r.height);

	*crops[sel->pad] = sel->r;

	अगर (ssd != sensor->pixel_array && sel->pad == CCS_PAD_SINK)
		ccs_propagate(subdev, cfg, sel->which, V4L2_SEL_TGT_CROP);

	वापस 0;
पूर्ण

अटल व्योम ccs_get_native_size(काष्ठा ccs_subdev *ssd, काष्ठा v4l2_rect *r)
अणु
	r->top = 0;
	r->left = 0;
	r->width = CCS_LIM(ssd->sensor, X_ADDR_MAX) + 1;
	r->height = CCS_LIM(ssd->sensor, Y_ADDR_MAX) + 1;
पूर्ण

अटल पूर्णांक __ccs_get_selection(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(subdev);
	काष्ठा v4l2_rect *comp, *crops[CCS_PADS];
	काष्ठा v4l2_rect sink_fmt;
	पूर्णांक ret;

	ret = __ccs_sel_supported(subdev, sel);
	अगर (ret)
		वापस ret;

	ccs_get_crop_compose(subdev, cfg, crops, &comp, sel->which);

	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		sink_fmt = ssd->sink_fmt;
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_mbus_framefmt *fmt =
			v4l2_subdev_get_try_क्रमmat(subdev, cfg, ssd->sink_pad);

		sink_fmt.left = 0;
		sink_fmt.top = 0;
		sink_fmt.width = fmt->width;
		sink_fmt.height = fmt->height;
	पूर्ण

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_NATIVE_SIZE:
		अगर (ssd == sensor->pixel_array)
			ccs_get_native_size(ssd, &sel->r);
		अन्यथा अगर (sel->pad == ssd->sink_pad)
			sel->r = sink_fmt;
		अन्यथा
			sel->r = *comp;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		sel->r = *crops[sel->pad];
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		sel->r = *comp;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_get_selection(काष्ठा v4l2_subdev *subdev,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	पूर्णांक rval;

	mutex_lock(&sensor->mutex);
	rval = __ccs_get_selection(subdev, cfg, sel);
	mutex_unlock(&sensor->mutex);

	वापस rval;
पूर्ण

अटल पूर्णांक ccs_set_selection(काष्ठा v4l2_subdev *subdev,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	पूर्णांक ret;

	ret = __ccs_sel_supported(subdev, sel);
	अगर (ret)
		वापस ret;

	mutex_lock(&sensor->mutex);

	sel->r.left = max(0, sel->r.left & ~1);
	sel->r.top = max(0, sel->r.top & ~1);
	sel->r.width = CCS_ALIGN_DIM(sel->r.width, sel->flags);
	sel->r.height =	CCS_ALIGN_DIM(sel->r.height, sel->flags);

	sel->r.width = max_t(अचिन्हित पूर्णांक, CCS_LIM(sensor, MIN_X_OUTPUT_SIZE),
			     sel->r.width);
	sel->r.height = max_t(अचिन्हित पूर्णांक, CCS_LIM(sensor, MIN_Y_OUTPUT_SIZE),
			      sel->r.height);

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		ret = ccs_set_crop(subdev, cfg, sel);
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		ret = ccs_set_compose(subdev, cfg, sel);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&sensor->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ccs_get_skip_frames(काष्ठा v4l2_subdev *subdev, u32 *frames)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);

	*frames = sensor->frame_skip;
	वापस 0;
पूर्ण

अटल पूर्णांक ccs_get_skip_top_lines(काष्ठा v4l2_subdev *subdev, u32 *lines)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);

	*lines = sensor->image_start;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * sysfs attributes
 */

अटल sमाप_प्रकार
ccs_sysfs_nvm_पढ़ो(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   अक्षर *buf)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	पूर्णांक rval;

	अगर (!sensor->dev_init_करोne)
		वापस -EBUSY;

	rval = ccs_pm_get_init(sensor);
	अगर (rval < 0)
		वापस -ENODEV;

	rval = ccs_पढ़ो_nvm(sensor, buf, PAGE_SIZE);
	अगर (rval < 0) अणु
		pm_runसमय_put(&client->dev);
		dev_err(&client->dev, "nvm read failed\n");
		वापस -ENODEV;
	पूर्ण

	pm_runसमय_mark_last_busy(&client->dev);
	pm_runसमय_put_स्वतःsuspend(&client->dev);

	/*
	 * NVM is still way below a PAGE_SIZE, so we can safely
	 * assume this क्रम now.
	 */
	वापस rval;
पूर्ण
अटल DEVICE_ATTR(nvm, S_IRUGO, ccs_sysfs_nvm_पढ़ो, शून्य);

अटल sमाप_प्रकार
ccs_sysfs_ident_पढ़ो(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	काष्ठा ccs_module_info *minfo = &sensor->minfo;

	अगर (minfo->mipi_manufacturer_id)
		वापस snम_लिखो(buf, PAGE_SIZE, "%4.4x%4.4x%2.2x\n",
				minfo->mipi_manufacturer_id, minfo->model_id,
				minfo->revision_number) + 1;
	अन्यथा
		वापस snम_लिखो(buf, PAGE_SIZE, "%2.2x%4.4x%2.2x\n",
				minfo->smia_manufacturer_id, minfo->model_id,
				minfo->revision_number) + 1;
पूर्ण

अटल DEVICE_ATTR(ident, S_IRUGO, ccs_sysfs_ident_पढ़ो, शून्य);

/* -----------------------------------------------------------------------------
 * V4L2 subdev core operations
 */

अटल पूर्णांक ccs_identअगरy_module(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	काष्ठा ccs_module_info *minfo = &sensor->minfo;
	अचिन्हित पूर्णांक i;
	u32 rev;
	पूर्णांक rval = 0;

	/* Module info */
	rval = ccs_पढ़ो(sensor, MODULE_MANUFACTURER_ID,
			&minfo->mipi_manufacturer_id);
	अगर (!rval && !minfo->mipi_manufacturer_id)
		rval = ccs_पढ़ो_addr_8only(sensor,
					   SMIAPP_REG_U8_MANUFACTURER_ID,
					   &minfo->smia_manufacturer_id);
	अगर (!rval)
		rval = ccs_पढ़ो_addr_8only(sensor, CCS_R_MODULE_MODEL_ID,
					   &minfo->model_id);
	अगर (!rval)
		rval = ccs_पढ़ो_addr_8only(sensor,
					   CCS_R_MODULE_REVISION_NUMBER_MAJOR,
					   &rev);
	अगर (!rval) अणु
		rval = ccs_पढ़ो_addr_8only(sensor,
					   CCS_R_MODULE_REVISION_NUMBER_MINOR,
					   &minfo->revision_number);
		minfo->revision_number |= rev << 8;
	पूर्ण
	अगर (!rval)
		rval = ccs_पढ़ो_addr_8only(sensor, CCS_R_MODULE_DATE_YEAR,
					   &minfo->module_year);
	अगर (!rval)
		rval = ccs_पढ़ो_addr_8only(sensor, CCS_R_MODULE_DATE_MONTH,
					   &minfo->module_month);
	अगर (!rval)
		rval = ccs_पढ़ो_addr_8only(sensor, CCS_R_MODULE_DATE_DAY,
					   &minfo->module_day);

	/* Sensor info */
	अगर (!rval)
		rval = ccs_पढ़ो(sensor, SENSOR_MANUFACTURER_ID,
				&minfo->sensor_mipi_manufacturer_id);
	अगर (!rval && !minfo->sensor_mipi_manufacturer_id)
		rval = ccs_पढ़ो_addr_8only(sensor,
					   CCS_R_SENSOR_MANUFACTURER_ID,
					   &minfo->sensor_smia_manufacturer_id);
	अगर (!rval)
		rval = ccs_पढ़ो_addr_8only(sensor,
					   CCS_R_SENSOR_MODEL_ID,
					   &minfo->sensor_model_id);
	अगर (!rval)
		rval = ccs_पढ़ो_addr_8only(sensor,
					   CCS_R_SENSOR_REVISION_NUMBER,
					   &minfo->sensor_revision_number);
	अगर (!rval)
		rval = ccs_पढ़ो_addr_8only(sensor,
					   CCS_R_SENSOR_FIRMWARE_VERSION,
					   &minfo->sensor_firmware_version);

	/* SMIA */
	अगर (!rval)
		rval = ccs_पढ़ो(sensor, MIPI_CCS_VERSION, &minfo->ccs_version);
	अगर (!rval && !minfo->ccs_version)
		rval = ccs_पढ़ो_addr_8only(sensor, SMIAPP_REG_U8_SMIA_VERSION,
					   &minfo->smia_version);
	अगर (!rval && !minfo->ccs_version)
		rval = ccs_पढ़ो_addr_8only(sensor, SMIAPP_REG_U8_SMIAPP_VERSION,
					   &minfo->smiapp_version);

	अगर (rval) अणु
		dev_err(&client->dev, "sensor detection failed\n");
		वापस -ENODEV;
	पूर्ण

	अगर (minfo->mipi_manufacturer_id)
		dev_dbg(&client->dev, "MIPI CCS module 0x%4.4x-0x%4.4x\n",
			minfo->mipi_manufacturer_id, minfo->model_id);
	अन्यथा
		dev_dbg(&client->dev, "SMIA module 0x%2.2x-0x%4.4x\n",
			minfo->smia_manufacturer_id, minfo->model_id);

	dev_dbg(&client->dev,
		"module revision 0x%4.4x date %2.2d-%2.2d-%2.2d\n",
		minfo->revision_number, minfo->module_year, minfo->module_month,
		minfo->module_day);

	अगर (minfo->sensor_mipi_manufacturer_id)
		dev_dbg(&client->dev, "MIPI CCS sensor 0x%4.4x-0x%4.4x\n",
			minfo->sensor_mipi_manufacturer_id,
			minfo->sensor_model_id);
	अन्यथा
		dev_dbg(&client->dev, "SMIA sensor 0x%2.2x-0x%4.4x\n",
			minfo->sensor_smia_manufacturer_id,
			minfo->sensor_model_id);

	dev_dbg(&client->dev,
		"sensor revision 0x%2.2x firmware version 0x%2.2x\n",
		minfo->sensor_revision_number, minfo->sensor_firmware_version);

	अगर (minfo->ccs_version) अणु
		dev_dbg(&client->dev, "MIPI CCS version %u.%u",
			(minfo->ccs_version & CCS_MIPI_CCS_VERSION_MAJOR_MASK)
			>> CCS_MIPI_CCS_VERSION_MAJOR_SHIFT,
			(minfo->ccs_version & CCS_MIPI_CCS_VERSION_MINOR_MASK));
		minfo->name = CCS_NAME;
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev,
			"smia version %2.2d smiapp version %2.2d\n",
			minfo->smia_version, minfo->smiapp_version);
		minfo->name = SMIAPP_NAME;
	पूर्ण

	/*
	 * Some modules have bad data in the lvalues below. Hope the
	 * rvalues have better stuff. The lvalues are module
	 * parameters whereas the rvalues are sensor parameters.
	 */
	अगर (minfo->sensor_smia_manufacturer_id &&
	    !minfo->smia_manufacturer_id && !minfo->model_id) अणु
		minfo->smia_manufacturer_id =
			minfo->sensor_smia_manufacturer_id;
		minfo->model_id = minfo->sensor_model_id;
		minfo->revision_number = minfo->sensor_revision_number;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ccs_module_idents); i++) अणु
		अगर (ccs_module_idents[i].mipi_manufacturer_id &&
		    ccs_module_idents[i].mipi_manufacturer_id
		    != minfo->mipi_manufacturer_id)
			जारी;
		अगर (ccs_module_idents[i].smia_manufacturer_id &&
		    ccs_module_idents[i].smia_manufacturer_id
		    != minfo->smia_manufacturer_id)
			जारी;
		अगर (ccs_module_idents[i].model_id != minfo->model_id)
			जारी;
		अगर (ccs_module_idents[i].flags
		    & CCS_MODULE_IDENT_FLAG_REV_LE) अणु
			अगर (ccs_module_idents[i].revision_number_major
			    < (minfo->revision_number >> 8))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (ccs_module_idents[i].revision_number_major
			    != (minfo->revision_number >> 8))
				जारी;
		पूर्ण

		minfo->name = ccs_module_idents[i].name;
		minfo->quirk = ccs_module_idents[i].quirk;
		अवरोध;
	पूर्ण

	अगर (i >= ARRAY_SIZE(ccs_module_idents))
		dev_warn(&client->dev,
			 "no quirks for this module; let's hope it's fully compliant\n");

	dev_dbg(&client->dev, "the sensor is called %s\n", minfo->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_ops ccs_ops;
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ccs_पूर्णांकernal_ops;
अटल स्थिर काष्ठा media_entity_operations ccs_entity_ops;

अटल पूर्णांक ccs_रेजिस्टर_subdev(काष्ठा ccs_sensor *sensor,
			       काष्ठा ccs_subdev *ssd,
			       काष्ठा ccs_subdev *sink_ssd,
			       u16 source_pad, u16 sink_pad, u32 link_flags)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक rval;

	अगर (!sink_ssd)
		वापस 0;

	rval = media_entity_pads_init(&ssd->sd.entity, ssd->npads, ssd->pads);
	अगर (rval) अणु
		dev_err(&client->dev, "media_entity_pads_init failed\n");
		वापस rval;
	पूर्ण

	rval = v4l2_device_रेजिस्टर_subdev(sensor->src->sd.v4l2_dev, &ssd->sd);
	अगर (rval) अणु
		dev_err(&client->dev, "v4l2_device_register_subdev failed\n");
		वापस rval;
	पूर्ण

	rval = media_create_pad_link(&ssd->sd.entity, source_pad,
				     &sink_ssd->sd.entity, sink_pad,
				     link_flags);
	अगर (rval) अणु
		dev_err(&client->dev, "media_create_pad_link failed\n");
		v4l2_device_unरेजिस्टर_subdev(&ssd->sd);
		वापस rval;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ccs_unरेजिस्टरed(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < sensor->ssds_used; i++)
		v4l2_device_unरेजिस्टर_subdev(&sensor->ssds[i].sd);
पूर्ण

अटल पूर्णांक ccs_रेजिस्टरed(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	पूर्णांक rval;

	अगर (sensor->scaler) अणु
		rval = ccs_रेजिस्टर_subdev(sensor, sensor->binner,
					   sensor->scaler,
					   CCS_PAD_SRC, CCS_PAD_SINK,
					   MEDIA_LNK_FL_ENABLED |
					   MEDIA_LNK_FL_IMMUTABLE);
		अगर (rval < 0)
			वापस rval;
	पूर्ण

	rval = ccs_रेजिस्टर_subdev(sensor, sensor->pixel_array, sensor->binner,
				   CCS_PA_PAD_SRC, CCS_PAD_SINK,
				   MEDIA_LNK_FL_ENABLED |
				   MEDIA_LNK_FL_IMMUTABLE);
	अगर (rval)
		जाओ out_err;

	वापस 0;

out_err:
	ccs_unरेजिस्टरed(subdev);

	वापस rval;
पूर्ण

अटल व्योम ccs_cleanup(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);

	device_हटाओ_file(&client->dev, &dev_attr_nvm);
	device_हटाओ_file(&client->dev, &dev_attr_ident);

	ccs_मुक्त_controls(sensor);
पूर्ण

अटल व्योम ccs_create_subdev(काष्ठा ccs_sensor *sensor,
			      काष्ठा ccs_subdev *ssd, स्थिर अक्षर *name,
			      अचिन्हित लघु num_pads, u32 function)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);

	अगर (!ssd)
		वापस;

	अगर (ssd != sensor->src)
		v4l2_subdev_init(&ssd->sd, &ccs_ops);

	ssd->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ssd->sd.entity.function = function;
	ssd->sensor = sensor;

	ssd->npads = num_pads;
	ssd->source_pad = num_pads - 1;

	v4l2_i2c_subdev_set_name(&ssd->sd, client, sensor->minfo.name, name);

	ccs_get_native_size(ssd, &ssd->sink_fmt);

	ssd->compose.width = ssd->sink_fmt.width;
	ssd->compose.height = ssd->sink_fmt.height;
	ssd->crop[ssd->source_pad] = ssd->compose;
	ssd->pads[ssd->source_pad].flags = MEDIA_PAD_FL_SOURCE;
	अगर (ssd != sensor->pixel_array) अणु
		ssd->crop[ssd->sink_pad] = ssd->compose;
		ssd->pads[ssd->sink_pad].flags = MEDIA_PAD_FL_SINK;
	पूर्ण

	ssd->sd.entity.ops = &ccs_entity_ops;

	अगर (ssd == sensor->src)
		वापस;

	ssd->sd.पूर्णांकernal_ops = &ccs_पूर्णांकernal_ops;
	ssd->sd.owner = THIS_MODULE;
	ssd->sd.dev = &client->dev;
	v4l2_set_subdevdata(&ssd->sd, client);
पूर्ण

अटल पूर्णांक ccs_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा ccs_subdev *ssd = to_ccs_subdev(sd);
	काष्ठा ccs_sensor *sensor = ssd->sensor;
	अचिन्हित पूर्णांक i;

	mutex_lock(&sensor->mutex);

	क्रम (i = 0; i < ssd->npads; i++) अणु
		काष्ठा v4l2_mbus_framefmt *try_fmt =
			v4l2_subdev_get_try_क्रमmat(sd, fh->pad, i);
		काष्ठा v4l2_rect *try_crop =
			v4l2_subdev_get_try_crop(sd, fh->pad, i);
		काष्ठा v4l2_rect *try_comp;

		ccs_get_native_size(ssd, try_crop);

		try_fmt->width = try_crop->width;
		try_fmt->height = try_crop->height;
		try_fmt->code = sensor->पूर्णांकernal_csi_क्रमmat->code;
		try_fmt->field = V4L2_FIELD_NONE;

		अगर (ssd != sensor->pixel_array)
			जारी;

		try_comp = v4l2_subdev_get_try_compose(sd, fh->pad, i);
		*try_comp = *try_crop;
	पूर्ण

	mutex_unlock(&sensor->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ccs_video_ops = अणु
	.s_stream = ccs_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ccs_pad_ops = अणु
	.क्रमागत_mbus_code = ccs_क्रमागत_mbus_code,
	.get_fmt = ccs_get_क्रमmat,
	.set_fmt = ccs_set_क्रमmat,
	.get_selection = ccs_get_selection,
	.set_selection = ccs_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_sensor_ops ccs_sensor_ops = अणु
	.g_skip_frames = ccs_get_skip_frames,
	.g_skip_top_lines = ccs_get_skip_top_lines,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ccs_ops = अणु
	.video = &ccs_video_ops,
	.pad = &ccs_pad_ops,
	.sensor = &ccs_sensor_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations ccs_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ccs_पूर्णांकernal_src_ops = अणु
	.रेजिस्टरed = ccs_रेजिस्टरed,
	.unरेजिस्टरed = ccs_unरेजिस्टरed,
	.खोलो = ccs_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ccs_पूर्णांकernal_ops = अणु
	.खोलो = ccs_खोलो,
पूर्ण;

/* -----------------------------------------------------------------------------
 * I2C Driver
 */

अटल पूर्णांक __maybe_unused ccs_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	bool streaming = sensor->streaming;
	पूर्णांक rval;

	rval = pm_runसमय_get_sync(dev);
	अगर (rval < 0) अणु
		pm_runसमय_put_noidle(dev);

		वापस -EAGAIN;
	पूर्ण

	अगर (sensor->streaming)
		ccs_stop_streaming(sensor);

	/* save state क्रम resume */
	sensor->streaming = streaming;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ccs_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	पूर्णांक rval = 0;

	pm_runसमय_put(dev);

	अगर (sensor->streaming)
		rval = ccs_start_streaming(sensor);

	वापस rval;
पूर्ण

अटल पूर्णांक ccs_get_hwconfig(काष्ठा ccs_sensor *sensor, काष्ठा device *dev)
अणु
	काष्ठा ccs_hwconfig *hwcfg = &sensor->hwcfg;
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु .bus_type = V4L2_MBUS_UNKNOWN पूर्ण;
	काष्ठा fwnode_handle *ep;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	u32 rotation;
	पूर्णांक i;
	पूर्णांक rval;

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(fwnode, 0, 0,
					     FWNODE_GRAPH_ENDPOINT_NEXT);
	अगर (!ep)
		वापस -ENODEV;

	/*
	 * Note that we करो need to rely on detecting the bus type between CSI-2
	 * D-PHY and CCP2 as the old bindings did not require it.
	 */
	rval = v4l2_fwnode_endpoपूर्णांक_alloc_parse(ep, &bus_cfg);
	अगर (rval)
		जाओ out_err;

	चयन (bus_cfg.bus_type) अणु
	हाल V4L2_MBUS_CSI2_DPHY:
		hwcfg->csi_संकेतling_mode = CCS_CSI_SIGNALING_MODE_CSI_2_DPHY;
		hwcfg->lanes = bus_cfg.bus.mipi_csi2.num_data_lanes;
		अवरोध;
	हाल V4L2_MBUS_CSI2_CPHY:
		hwcfg->csi_संकेतling_mode = CCS_CSI_SIGNALING_MODE_CSI_2_CPHY;
		hwcfg->lanes = bus_cfg.bus.mipi_csi2.num_data_lanes;
		अवरोध;
	हाल V4L2_MBUS_CSI1:
	हाल V4L2_MBUS_CCP2:
		hwcfg->csi_संकेतling_mode = (bus_cfg.bus.mipi_csi1.strobe) ?
		SMIAPP_CSI_SIGNALLING_MODE_CCP2_DATA_STROBE :
		SMIAPP_CSI_SIGNALLING_MODE_CCP2_DATA_CLOCK;
		hwcfg->lanes = 1;
		अवरोध;
	शेष:
		dev_err(dev, "unsupported bus %u\n", bus_cfg.bus_type);
		rval = -EINVAL;
		जाओ out_err;
	पूर्ण

	dev_dbg(dev, "lanes %u\n", hwcfg->lanes);

	rval = fwnode_property_पढ़ो_u32(fwnode, "rotation", &rotation);
	अगर (!rval) अणु
		चयन (rotation) अणु
		हाल 180:
			hwcfg->module_board_orient =
				CCS_MODULE_BOARD_ORIENT_180;
			fallthrough;
		हाल 0:
			अवरोध;
		शेष:
			dev_err(dev, "invalid rotation %u\n", rotation);
			rval = -EINVAL;
			जाओ out_err;
		पूर्ण
	पूर्ण

	rval = fwnode_property_पढ़ो_u32(dev_fwnode(dev), "clock-frequency",
					&hwcfg->ext_clk);
	अगर (rval)
		dev_info(dev, "can't get clock-frequency\n");

	dev_dbg(dev, "clk %d, mode %d\n", hwcfg->ext_clk,
		hwcfg->csi_संकेतling_mode);

	अगर (!bus_cfg.nr_of_link_frequencies) अणु
		dev_warn(dev, "no link frequencies defined\n");
		rval = -EINVAL;
		जाओ out_err;
	पूर्ण

	hwcfg->op_sys_घड़ी = devm_kसुस्मृति(
		dev, bus_cfg.nr_of_link_frequencies + 1 /* guardian */,
		माप(*hwcfg->op_sys_घड़ी), GFP_KERNEL);
	अगर (!hwcfg->op_sys_घड़ी) अणु
		rval = -ENOMEM;
		जाओ out_err;
	पूर्ण

	क्रम (i = 0; i < bus_cfg.nr_of_link_frequencies; i++) अणु
		hwcfg->op_sys_घड़ी[i] = bus_cfg.link_frequencies[i];
		dev_dbg(dev, "freq %d: %lld\n", i, hwcfg->op_sys_घड़ी[i]);
	पूर्ण

	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);
	fwnode_handle_put(ep);

	वापस 0;

out_err:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);
	fwnode_handle_put(ep);

	वापस rval;
पूर्ण

अटल पूर्णांक ccs_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ccs_sensor *sensor;
	स्थिर काष्ठा firmware *fw;
	अक्षर filename[40];
	अचिन्हित पूर्णांक i;
	पूर्णांक rval;

	sensor = devm_kzalloc(&client->dev, माप(*sensor), GFP_KERNEL);
	अगर (sensor == शून्य)
		वापस -ENOMEM;

	rval = ccs_get_hwconfig(sensor, &client->dev);
	अगर (rval)
		वापस rval;

	sensor->src = &sensor->ssds[sensor->ssds_used];

	v4l2_i2c_subdev_init(&sensor->src->sd, client, &ccs_ops);
	sensor->src->sd.पूर्णांकernal_ops = &ccs_पूर्णांकernal_src_ops;

	sensor->regulators = devm_kसुस्मृति(&client->dev,
					  ARRAY_SIZE(ccs_regulators),
					  माप(*sensor->regulators),
					  GFP_KERNEL);
	अगर (!sensor->regulators)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(ccs_regulators); i++)
		sensor->regulators[i].supply = ccs_regulators[i];

	rval = devm_regulator_bulk_get(&client->dev, ARRAY_SIZE(ccs_regulators),
				       sensor->regulators);
	अगर (rval) अणु
		dev_err(&client->dev, "could not get regulators\n");
		वापस rval;
	पूर्ण

	sensor->ext_clk = devm_clk_get(&client->dev, शून्य);
	अगर (PTR_ERR(sensor->ext_clk) == -ENOENT) अणु
		dev_info(&client->dev, "no clock defined, continuing...\n");
		sensor->ext_clk = शून्य;
	पूर्ण अन्यथा अगर (IS_ERR(sensor->ext_clk)) अणु
		dev_err(&client->dev, "could not get clock (%ld)\n",
			PTR_ERR(sensor->ext_clk));
		वापस -EPROBE_DEFER;
	पूर्ण

	अगर (sensor->ext_clk) अणु
		अगर (sensor->hwcfg.ext_clk) अणु
			अचिन्हित दीर्घ rate;

			rval = clk_set_rate(sensor->ext_clk,
					    sensor->hwcfg.ext_clk);
			अगर (rval < 0) अणु
				dev_err(&client->dev,
					"unable to set clock freq to %u\n",
					sensor->hwcfg.ext_clk);
				वापस rval;
			पूर्ण

			rate = clk_get_rate(sensor->ext_clk);
			अगर (rate != sensor->hwcfg.ext_clk) अणु
				dev_err(&client->dev,
					"can't set clock freq, asked for %u but got %lu\n",
					sensor->hwcfg.ext_clk, rate);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			sensor->hwcfg.ext_clk = clk_get_rate(sensor->ext_clk);
			dev_dbg(&client->dev, "obtained clock freq %u\n",
				sensor->hwcfg.ext_clk);
		पूर्ण
	पूर्ण अन्यथा अगर (sensor->hwcfg.ext_clk) अणु
		dev_dbg(&client->dev, "assuming clock freq %u\n",
			sensor->hwcfg.ext_clk);
	पूर्ण अन्यथा अणु
		dev_err(&client->dev, "unable to obtain clock freq\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!sensor->hwcfg.ext_clk) अणु
		dev_err(&client->dev, "cannot work with xclk frequency 0\n");
		वापस -EINVAL;
	पूर्ण

	sensor->reset = devm_gpiod_get_optional(&client->dev, "reset",
						GPIOD_OUT_HIGH);
	अगर (IS_ERR(sensor->reset))
		वापस PTR_ERR(sensor->reset);
	/* Support old users that may have used "xshutdown" property. */
	अगर (!sensor->reset)
		sensor->xshutकरोwn = devm_gpiod_get_optional(&client->dev,
							    "xshutdown",
							    GPIOD_OUT_LOW);
	अगर (IS_ERR(sensor->xshutकरोwn))
		वापस PTR_ERR(sensor->xshutकरोwn);

	rval = ccs_घातer_on(&client->dev);
	अगर (rval < 0)
		वापस rval;

	mutex_init(&sensor->mutex);

	rval = ccs_identअगरy_module(sensor);
	अगर (rval) अणु
		rval = -ENODEV;
		जाओ out_घातer_off;
	पूर्ण

	rval = snम_लिखो(filename, माप(filename),
			"ccs/ccs-sensor-%4.4x-%4.4x-%4.4x.fw",
			sensor->minfo.sensor_mipi_manufacturer_id,
			sensor->minfo.sensor_model_id,
			sensor->minfo.sensor_revision_number);
	अगर (rval >= माप(filename)) अणु
		rval = -ENOMEM;
		जाओ out_घातer_off;
	पूर्ण

	rval = request_firmware(&fw, filename, &client->dev);
	अगर (!rval) अणु
		ccs_data_parse(&sensor->sdata, fw->data, fw->size, &client->dev,
			       true);
		release_firmware(fw);
	पूर्ण

	rval = snम_लिखो(filename, माप(filename),
			"ccs/ccs-module-%4.4x-%4.4x-%4.4x.fw",
			sensor->minfo.mipi_manufacturer_id,
			sensor->minfo.model_id,
			sensor->minfo.revision_number);
	अगर (rval >= माप(filename)) अणु
		rval = -ENOMEM;
		जाओ out_release_sdata;
	पूर्ण

	rval = request_firmware(&fw, filename, &client->dev);
	अगर (!rval) अणु
		ccs_data_parse(&sensor->mdata, fw->data, fw->size, &client->dev,
			       true);
		release_firmware(fw);
	पूर्ण

	rval = ccs_पढ़ो_all_limits(sensor);
	अगर (rval)
		जाओ out_release_mdata;

	rval = ccs_पढ़ो_frame_fmt(sensor);
	अगर (rval) अणु
		rval = -ENODEV;
		जाओ out_मुक्त_ccs_limits;
	पूर्ण

	rval = ccs_update_phy_ctrl(sensor);
	अगर (rval < 0)
		जाओ out_मुक्त_ccs_limits;

	/*
	 * Handle Sensor Module orientation on the board.
	 *
	 * The application of H-FLIP and V-FLIP on the sensor is modअगरied by
	 * the sensor orientation on the board.
	 *
	 * For CCS_BOARD_SENSOR_ORIENT_180 the शेष behaviour is to set
	 * both H-FLIP and V-FLIP क्रम normal operation which also implies
	 * that a set/unset operation क्रम user space HFLIP and VFLIP v4l2
	 * controls will need to be पूर्णांकernally inverted.
	 *
	 * Rotation also changes the bayer pattern.
	 */
	अगर (sensor->hwcfg.module_board_orient ==
	    CCS_MODULE_BOARD_ORIENT_180)
		sensor->hvflip_inv_mask =
			CCS_IMAGE_ORIENTATION_HORIZONTAL_MIRROR |
			CCS_IMAGE_ORIENTATION_VERTICAL_FLIP;

	rval = ccs_call_quirk(sensor, limits);
	अगर (rval) अणु
		dev_err(&client->dev, "limits quirks failed\n");
		जाओ out_मुक्त_ccs_limits;
	पूर्ण

	अगर (CCS_LIM(sensor, BINNING_CAPABILITY)) अणु
		sensor->nbinning_subtypes =
			min_t(u8, CCS_LIM(sensor, BINNING_SUB_TYPES),
			      CCS_LIM_BINNING_SUB_TYPE_MAX_N);

		क्रम (i = 0; i < sensor->nbinning_subtypes; i++) अणु
			sensor->binning_subtypes[i].horizontal =
				CCS_LIM_AT(sensor, BINNING_SUB_TYPE, i) >>
				CCS_BINNING_SUB_TYPE_COLUMN_SHIFT;
			sensor->binning_subtypes[i].vertical =
				CCS_LIM_AT(sensor, BINNING_SUB_TYPE, i) &
				CCS_BINNING_SUB_TYPE_ROW_MASK;

			dev_dbg(&client->dev, "binning %xx%x\n",
				sensor->binning_subtypes[i].horizontal,
				sensor->binning_subtypes[i].vertical);
		पूर्ण
	पूर्ण
	sensor->binning_horizontal = 1;
	sensor->binning_vertical = 1;

	अगर (device_create_file(&client->dev, &dev_attr_ident) != 0) अणु
		dev_err(&client->dev, "sysfs ident entry creation failed\n");
		rval = -ENOENT;
		जाओ out_मुक्त_ccs_limits;
	पूर्ण

	अगर (sensor->minfo.smiapp_version &&
	    CCS_LIM(sensor, DATA_TRANSFER_IF_CAPABILITY) &
	    CCS_DATA_TRANSFER_IF_CAPABILITY_SUPPORTED) अणु
		अगर (device_create_file(&client->dev, &dev_attr_nvm) != 0) अणु
			dev_err(&client->dev, "sysfs nvm entry failed\n");
			rval = -EBUSY;
			जाओ out_cleanup;
		पूर्ण
	पूर्ण

	अगर (!CCS_LIM(sensor, MIN_OP_SYS_CLK_DIV) ||
	    !CCS_LIM(sensor, MAX_OP_SYS_CLK_DIV) ||
	    !CCS_LIM(sensor, MIN_OP_PIX_CLK_DIV) ||
	    !CCS_LIM(sensor, MAX_OP_PIX_CLK_DIV)) अणु
		/* No OP घड़ी branch */
		sensor->pll.flags |= CCS_PLL_FLAG_NO_OP_CLOCKS;
	पूर्ण अन्यथा अगर (CCS_LIM(sensor, SCALING_CAPABILITY)
		   != CCS_SCALING_CAPABILITY_NONE ||
		   CCS_LIM(sensor, DIGITAL_CROP_CAPABILITY)
		   == CCS_DIGITAL_CROP_CAPABILITY_INPUT_CROP) अणु
		/* We have a scaler or digital crop. */
		sensor->scaler = &sensor->ssds[sensor->ssds_used];
		sensor->ssds_used++;
	पूर्ण
	sensor->binner = &sensor->ssds[sensor->ssds_used];
	sensor->ssds_used++;
	sensor->pixel_array = &sensor->ssds[sensor->ssds_used];
	sensor->ssds_used++;

	sensor->scale_m = CCS_LIM(sensor, SCALER_N_MIN);

	/* prepare PLL configuration input values */
	sensor->pll.bus_type = CCS_PLL_BUS_TYPE_CSI2_DPHY;
	sensor->pll.csi2.lanes = sensor->hwcfg.lanes;
	अगर (CCS_LIM(sensor, CLOCK_CALCULATION) &
	    CCS_CLOCK_CALCULATION_LANE_SPEED) अणु
		sensor->pll.flags |= CCS_PLL_FLAG_LANE_SPEED_MODEL;
		अगर (CCS_LIM(sensor, CLOCK_CALCULATION) &
		    CCS_CLOCK_CALCULATION_LINK_DECOUPLED) अणु
			sensor->pll.vt_lanes =
				CCS_LIM(sensor, NUM_OF_VT_LANES) + 1;
			sensor->pll.op_lanes =
				CCS_LIM(sensor, NUM_OF_OP_LANES) + 1;
			sensor->pll.flags |= CCS_PLL_FLAG_LINK_DECOUPLED;
		पूर्ण अन्यथा अणु
			sensor->pll.vt_lanes = sensor->pll.csi2.lanes;
			sensor->pll.op_lanes = sensor->pll.csi2.lanes;
		पूर्ण
	पूर्ण
	अगर (CCS_LIM(sensor, CLOCK_TREE_PLL_CAPABILITY) &
	    CCS_CLOCK_TREE_PLL_CAPABILITY_EXT_DIVIDER)
		sensor->pll.flags |= CCS_PLL_FLAG_EXT_IP_PLL_DIVIDER;
	अगर (CCS_LIM(sensor, CLOCK_TREE_PLL_CAPABILITY) &
	    CCS_CLOCK_TREE_PLL_CAPABILITY_FLEXIBLE_OP_PIX_CLK_DIV)
		sensor->pll.flags |= CCS_PLL_FLAG_FLEXIBLE_OP_PIX_CLK_DIV;
	अगर (CCS_LIM(sensor, FIFO_SUPPORT_CAPABILITY) &
	    CCS_FIFO_SUPPORT_CAPABILITY_DERATING)
		sensor->pll.flags |= CCS_PLL_FLAG_FIFO_DERATING;
	अगर (CCS_LIM(sensor, FIFO_SUPPORT_CAPABILITY) &
	    CCS_FIFO_SUPPORT_CAPABILITY_DERATING_OVERRATING)
		sensor->pll.flags |= CCS_PLL_FLAG_FIFO_DERATING |
				     CCS_PLL_FLAG_FIFO_OVERRATING;
	अगर (CCS_LIM(sensor, CLOCK_TREE_PLL_CAPABILITY) &
	    CCS_CLOCK_TREE_PLL_CAPABILITY_DUAL_PLL) अणु
		अगर (CCS_LIM(sensor, CLOCK_TREE_PLL_CAPABILITY) &
		    CCS_CLOCK_TREE_PLL_CAPABILITY_SINGLE_PLL) अणु
			u32 v;

			/* Use sensor शेष in PLL mode selection */
			rval = ccs_पढ़ो(sensor, PLL_MODE, &v);
			अगर (rval)
				जाओ out_cleanup;

			अगर (v == CCS_PLL_MODE_DUAL)
				sensor->pll.flags |= CCS_PLL_FLAG_DUAL_PLL;
		पूर्ण अन्यथा अणु
			sensor->pll.flags |= CCS_PLL_FLAG_DUAL_PLL;
		पूर्ण
		अगर (CCS_LIM(sensor, CLOCK_CALCULATION) &
		    CCS_CLOCK_CALCULATION_DUAL_PLL_OP_SYS_DDR)
			sensor->pll.flags |= CCS_PLL_FLAG_OP_SYS_DDR;
		अगर (CCS_LIM(sensor, CLOCK_CALCULATION) &
		    CCS_CLOCK_CALCULATION_DUAL_PLL_OP_PIX_DDR)
			sensor->pll.flags |= CCS_PLL_FLAG_OP_PIX_DDR;
	पूर्ण
	sensor->pll.op_bits_per_lane = CCS_LIM(sensor, OP_BITS_PER_LANE);
	sensor->pll.ext_clk_freq_hz = sensor->hwcfg.ext_clk;
	sensor->pll.scale_n = CCS_LIM(sensor, SCALER_N_MIN);

	ccs_create_subdev(sensor, sensor->scaler, " scaler", 2,
			  MEDIA_ENT_F_PROC_VIDEO_SCALER);
	ccs_create_subdev(sensor, sensor->binner, " binner", 2,
			  MEDIA_ENT_F_PROC_VIDEO_SCALER);
	ccs_create_subdev(sensor, sensor->pixel_array, " pixel_array", 1,
			  MEDIA_ENT_F_CAM_SENSOR);

	rval = ccs_init_controls(sensor);
	अगर (rval < 0)
		जाओ out_cleanup;

	rval = ccs_call_quirk(sensor, init);
	अगर (rval)
		जाओ out_cleanup;

	rval = ccs_get_mbus_क्रमmats(sensor);
	अगर (rval) अणु
		rval = -ENODEV;
		जाओ out_cleanup;
	पूर्ण

	rval = ccs_init_late_controls(sensor);
	अगर (rval) अणु
		rval = -ENODEV;
		जाओ out_cleanup;
	पूर्ण

	mutex_lock(&sensor->mutex);
	rval = ccs_pll_blanking_update(sensor);
	mutex_unlock(&sensor->mutex);
	अगर (rval) अणु
		dev_err(&client->dev, "update mode failed\n");
		जाओ out_cleanup;
	पूर्ण

	sensor->streaming = false;
	sensor->dev_init_करोne = true;

	rval = media_entity_pads_init(&sensor->src->sd.entity, 2,
				 sensor->src->pads);
	अगर (rval < 0)
		जाओ out_media_entity_cleanup;

	rval = ccs_ग_लिखो_msr_regs(sensor);
	अगर (rval)
		जाओ out_media_entity_cleanup;

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_get_noresume(&client->dev);
	pm_runसमय_enable(&client->dev);

	rval = v4l2_async_रेजिस्टर_subdev_sensor(&sensor->src->sd);
	अगर (rval < 0)
		जाओ out_disable_runसमय_pm;

	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 1000);
	pm_runसमय_use_स्वतःsuspend(&client->dev);
	pm_runसमय_put_स्वतःsuspend(&client->dev);

	वापस 0;

out_disable_runसमय_pm:
	pm_runसमय_put_noidle(&client->dev);
	pm_runसमय_disable(&client->dev);

out_media_entity_cleanup:
	media_entity_cleanup(&sensor->src->sd.entity);

out_cleanup:
	ccs_cleanup(sensor);

out_release_mdata:
	kvमुक्त(sensor->mdata.backing);

out_release_sdata:
	kvमुक्त(sensor->sdata.backing);

out_मुक्त_ccs_limits:
	kमुक्त(sensor->ccs_limits);

out_घातer_off:
	ccs_घातer_off(&client->dev);
	mutex_destroy(&sensor->mutex);

	वापस rval;
पूर्ण

अटल पूर्णांक ccs_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ccs_sensor *sensor = to_ccs_sensor(subdev);
	अचिन्हित पूर्णांक i;

	v4l2_async_unरेजिस्टर_subdev(subdev);

	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		ccs_घातer_off(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	क्रम (i = 0; i < sensor->ssds_used; i++) अणु
		v4l2_device_unरेजिस्टर_subdev(&sensor->ssds[i].sd);
		media_entity_cleanup(&sensor->ssds[i].sd.entity);
	पूर्ण
	ccs_cleanup(sensor);
	mutex_destroy(&sensor->mutex);
	kमुक्त(sensor->ccs_limits);
	kvमुक्त(sensor->sdata.backing);
	kvमुक्त(sensor->mdata.backing);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ccs_device smia_device = अणु
	.flags = CCS_DEVICE_FLAG_IS_SMIA,
पूर्ण;

अटल स्थिर काष्ठा ccs_device ccs_device = अणुपूर्ण;

अटल स्थिर काष्ठा acpi_device_id ccs_acpi_table[] = अणु
	अणु .id = "MIPI0200", .driver_data = (अचिन्हित दीर्घ)&ccs_device पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ccs_acpi_table);

अटल स्थिर काष्ठा of_device_id ccs_of_table[] = अणु
	अणु .compatible = "mipi-ccs-1.1", .data = &ccs_device पूर्ण,
	अणु .compatible = "mipi-ccs-1.0", .data = &ccs_device पूर्ण,
	अणु .compatible = "mipi-ccs", .data = &ccs_device पूर्ण,
	अणु .compatible = "nokia,smia", .data = &smia_device पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ccs_of_table);

अटल स्थिर काष्ठा dev_pm_ops ccs_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ccs_suspend, ccs_resume)
	SET_RUNTIME_PM_OPS(ccs_घातer_off, ccs_घातer_on, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver ccs_i2c_driver = अणु
	.driver	= अणु
		.acpi_match_table = ccs_acpi_table,
		.of_match_table = ccs_of_table,
		.name = CCS_NAME,
		.pm = &ccs_pm_ops,
	पूर्ण,
	.probe_new = ccs_probe,
	.हटाओ	= ccs_हटाओ,
पूर्ण;

अटल पूर्णांक ccs_module_init(व्योम)
अणु
	अचिन्हित पूर्णांक i, l;

	क्रम (i = 0, l = 0; ccs_limits[i].size && l < CCS_L_LAST; i++) अणु
		अगर (!(ccs_limits[i].flags & CCS_L_FL_SAME_REG)) अणु
			ccs_limit_offsets[l + 1].lim =
				ALIGN(ccs_limit_offsets[l].lim +
				      ccs_limits[i].size,
				      ccs_reg_width(ccs_limits[i + 1].reg));
			ccs_limit_offsets[l].info = i;
			l++;
		पूर्ण अन्यथा अणु
			ccs_limit_offsets[l].lim += ccs_limits[i].size;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(ccs_limits[i].size))
		वापस -EINVAL;

	अगर (WARN_ON(l != CCS_L_LAST))
		वापस -EINVAL;

	वापस i2c_रेजिस्टर_driver(THIS_MODULE, &ccs_i2c_driver);
पूर्ण

अटल व्योम ccs_module_cleanup(व्योम)
अणु
	i2c_del_driver(&ccs_i2c_driver);
पूर्ण

module_init(ccs_module_init);
module_निकास(ccs_module_cleanup);

MODULE_AUTHOR("Sakari Ailus <sakari.ailus@linux.intel.com>");
MODULE_DESCRIPTION("Generic MIPI CCS/SMIA/SMIA++ camera sensor driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("smiapp");
