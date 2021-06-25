<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम SiliconFile SR030PC30 VGA (1/10-Inch) Image Sensor with ISP
 *
 * Copyright (C) 2010 Samsung Electronics Co., Ltd
 * Author: Sylwester Nawrocki, s.nawrocki@samsung.com
 *
 * Based on original driver authored by Dongsoo Nathaniel Kim
 * and HeungJun Kim <riverful.kim@samsung.com>.
 *
 * Based on mt9v011 Micron Digital Image Sensor driver
 * Copyright (c) 2009 Mauro Carvalho Chehab
 */

#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/i2c/sr030pc30.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

#घोषणा MODULE_NAME	"SR030PC30"

/*
 * Register offsets within a page
 * b15..b8 - page id, b7..b0 - रेजिस्टर address
 */
#घोषणा POWER_CTRL_REG		0x0001
#घोषणा PAGEMODE_REG		0x03
#घोषणा DEVICE_ID_REG		0x0004
#घोषणा NOON010PC30_ID		0x86
#घोषणा SR030PC30_ID		0x8C
#घोषणा VDO_CTL1_REG		0x0010
#घोषणा SUBSAMPL_NONE_VGA	0
#घोषणा SUBSAMPL_QVGA		0x10
#घोषणा SUBSAMPL_QQVGA		0x20
#घोषणा VDO_CTL2_REG		0x0011
#घोषणा SYNC_CTL_REG		0x0012
#घोषणा WIN_ROWH_REG		0x0020
#घोषणा WIN_ROWL_REG		0x0021
#घोषणा WIN_COLH_REG		0x0022
#घोषणा WIN_COLL_REG		0x0023
#घोषणा WIN_HEIGHTH_REG		0x0024
#घोषणा WIN_HEIGHTL_REG		0x0025
#घोषणा WIN_WIDTHH_REG		0x0026
#घोषणा WIN_WIDTHL_REG		0x0027
#घोषणा HBLANKH_REG		0x0040
#घोषणा HBLANKL_REG		0x0041
#घोषणा VSYNCH_REG		0x0042
#घोषणा VSYNCL_REG		0x0043
/* page 10 */
#घोषणा ISP_CTL_REG(n)		(0x1010 + (n))
#घोषणा YOFS_REG		0x1040
#घोषणा DARK_YOFS_REG		0x1041
#घोषणा AG_ABRTH_REG		0x1050
#घोषणा SAT_CTL_REG		0x1060
#घोषणा BSAT_REG		0x1061
#घोषणा RSAT_REG		0x1062
#घोषणा AG_SAT_TH_REG		0x1063
/* page 11 */
#घोषणा ZLPF_CTRL_REG		0x1110
#घोषणा ZLPF_CTRL2_REG		0x1112
#घोषणा ZLPF_AGH_THR_REG	0x1121
#घोषणा ZLPF_THR_REG		0x1160
#घोषणा ZLPF_DYN_THR_REG	0x1160
/* page 12 */
#घोषणा YCLPF_CTL1_REG		0x1240
#घोषणा YCLPF_CTL2_REG		0x1241
#घोषणा YCLPF_THR_REG		0x1250
#घोषणा BLPF_CTL_REG		0x1270
#घोषणा BLPF_THR1_REG		0x1274
#घोषणा BLPF_THR2_REG		0x1275
/* page 14 - Lens Shading Compensation */
#घोषणा LENS_CTRL_REG		0x1410
#घोषणा LENS_XCEN_REG		0x1420
#घोषणा LENS_YCEN_REG		0x1421
#घोषणा LENS_R_COMP_REG		0x1422
#घोषणा LENS_G_COMP_REG		0x1423
#घोषणा LENS_B_COMP_REG		0x1424
/* page 15 - Color correction */
#घोषणा CMC_CTL_REG		0x1510
#घोषणा CMC_OFSGH_REG		0x1514
#घोषणा CMC_OFSGL_REG		0x1516
#घोषणा CMC_SIGN_REG		0x1517
/* Color correction coefficients */
#घोषणा CMC_COEF_REG(n)		(0x1530 + (n))
/* Color correction offset coefficients */
#घोषणा CMC_OFS_REG(n)		(0x1540 + (n))
/* page 16 - Gamma correction */
#घोषणा GMA_CTL_REG		0x1610
/* Gamma correction coefficients 0.14 */
#घोषणा GMA_COEF_REG(n)		(0x1630 + (n))
/* page 20 - Auto Exposure */
#घोषणा AE_CTL1_REG		0x2010
#घोषणा AE_CTL2_REG		0x2011
#घोषणा AE_FRM_CTL_REG		0x2020
#घोषणा AE_FINE_CTL_REG(n)	(0x2028 + (n))
#घोषणा EXP_TIMEH_REG		0x2083
#घोषणा EXP_TIMEM_REG		0x2084
#घोषणा EXP_TIMEL_REG		0x2085
#घोषणा EXP_MMINH_REG		0x2086
#घोषणा EXP_MMINL_REG		0x2087
#घोषणा EXP_MMAXH_REG		0x2088
#घोषणा EXP_MMAXM_REG		0x2089
#घोषणा EXP_MMAXL_REG		0x208A
/* page 22 - Auto White Balance */
#घोषणा AWB_CTL1_REG		0x2210
#घोषणा AWB_ENABLE		0x80
#घोषणा AWB_CTL2_REG		0x2211
#घोषणा MWB_ENABLE		0x01
/* RGB gain control (manual WB) when AWB_CTL1[7]=0 */
#घोषणा AWB_RGAIN_REG		0x2280
#घोषणा AWB_GGAIN_REG		0x2281
#घोषणा AWB_BGAIN_REG		0x2282
#घोषणा AWB_RMAX_REG		0x2283
#घोषणा AWB_RMIN_REG		0x2284
#घोषणा AWB_BMAX_REG		0x2285
#घोषणा AWB_BMIN_REG		0x2286
/* R, B gain range in bright light conditions */
#घोषणा AWB_RMAXB_REG		0x2287
#घोषणा AWB_RMINB_REG		0x2288
#घोषणा AWB_BMAXB_REG		0x2289
#घोषणा AWB_BMINB_REG		0x228A
/* manual white balance, when AWB_CTL2[0]=1 */
#घोषणा MWB_RGAIN_REG		0x22B2
#घोषणा MWB_BGAIN_REG		0x22B3
/* the token to mark an array end */
#घोषणा REG_TERM		0xFFFF

/* Minimum and maximum exposure समय in ms */
#घोषणा EXPOS_MIN_MS		1
#घोषणा EXPOS_MAX_MS		125

काष्ठा sr030pc30_info अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	स्थिर काष्ठा sr030pc30_platक्रमm_data *pdata;
	स्थिर काष्ठा sr030pc30_क्रमmat *curr_fmt;
	स्थिर काष्ठा sr030pc30_frmsize *curr_win;
	अचिन्हित पूर्णांक hflip:1;
	अचिन्हित पूर्णांक vflip:1;
	अचिन्हित पूर्णांक sleep:1;
	काष्ठा अणु
		/* स्वतः whitebalance control cluster */
		काष्ठा v4l2_ctrl *awb;
		काष्ठा v4l2_ctrl *red;
		काष्ठा v4l2_ctrl *blue;
	पूर्ण;
	काष्ठा अणु
		/* स्वतः exposure control cluster */
		काष्ठा v4l2_ctrl *स्वतःexp;
		काष्ठा v4l2_ctrl *exp;
	पूर्ण;
	u8 i2c_reg_page;
पूर्ण;

काष्ठा sr030pc30_क्रमmat अणु
	u32 code;
	क्रमागत v4l2_colorspace colorspace;
	u16 ispctl1_reg;
पूर्ण;

काष्ठा sr030pc30_frmsize अणु
	u16 width;
	u16 height;
	पूर्णांक vid_ctl1;
पूर्ण;

काष्ठा i2c_regval अणु
	u16 addr;
	u16 val;
पूर्ण;

/* supported resolutions */
अटल स्थिर काष्ठा sr030pc30_frmsize sr030pc30_sizes[] = अणु
	अणु
		.width		= 640,
		.height		= 480,
		.vid_ctl1	= SUBSAMPL_NONE_VGA,
	पूर्ण, अणु
		.width		= 320,
		.height		= 240,
		.vid_ctl1	= SUBSAMPL_QVGA,
	पूर्ण, अणु
		.width		= 160,
		.height		= 120,
		.vid_ctl1	= SUBSAMPL_QQVGA,
	पूर्ण,
पूर्ण;

/* supported pixel क्रमmats */
अटल स्थिर काष्ठा sr030pc30_क्रमmat sr030pc30_क्रमmats[] = अणु
	अणु
		.code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0x03,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0x02,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0x01,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_RGB565_2X8_BE,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0x40,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_regval sr030pc30_base_regs[] = अणु
	/* Winकरोw size and position within pixel matrix */
	अणु WIN_ROWH_REG,		0x00 पूर्ण, अणु WIN_ROWL_REG,		0x06 पूर्ण,
	अणु WIN_COLH_REG,		0x00 पूर्ण,	अणु WIN_COLL_REG,		0x06 पूर्ण,
	अणु WIN_HEIGHTH_REG,	0x01 पूर्ण, अणु WIN_HEIGHTL_REG,	0xE0 पूर्ण,
	अणु WIN_WIDTHH_REG,	0x02 पूर्ण, अणु WIN_WIDTHL_REG,	0x80 पूर्ण,
	अणु HBLANKH_REG,		0x01 पूर्ण, अणु HBLANKL_REG,		0x50 पूर्ण,
	अणु VSYNCH_REG,		0x00 पूर्ण, अणु VSYNCL_REG,		0x14 पूर्ण,
	अणु SYNC_CTL_REG,		0 पूर्ण,
	/* Color corection and saturation */
	अणु ISP_CTL_REG(0),	0x30 पूर्ण, अणु YOFS_REG,		0x80 पूर्ण,
	अणु DARK_YOFS_REG,	0x04 पूर्ण, अणु AG_ABRTH_REG,		0x78 पूर्ण,
	अणु SAT_CTL_REG,		0x1F पूर्ण, अणु BSAT_REG,		0x90 पूर्ण,
	अणु AG_SAT_TH_REG,	0xF0 पूर्ण, अणु 0x1064,		0x80 पूर्ण,
	अणु CMC_CTL_REG,		0x03 पूर्ण, अणु CMC_OFSGH_REG,	0x3C पूर्ण,
	अणु CMC_OFSGL_REG,	0x2C पूर्ण, अणु CMC_SIGN_REG,		0x2F पूर्ण,
	अणु CMC_COEF_REG(0),	0xCB पूर्ण, अणु CMC_OFS_REG(0),	0x87 पूर्ण,
	अणु CMC_COEF_REG(1),	0x61 पूर्ण, अणु CMC_OFS_REG(1),	0x18 पूर्ण,
	अणु CMC_COEF_REG(2),	0x16 पूर्ण, अणु CMC_OFS_REG(2),	0x91 पूर्ण,
	अणु CMC_COEF_REG(3),	0x23 पूर्ण, अणु CMC_OFS_REG(3),	0x94 पूर्ण,
	अणु CMC_COEF_REG(4),	0xCE पूर्ण, अणु CMC_OFS_REG(4),	0x9f पूर्ण,
	अणु CMC_COEF_REG(5),	0x2B पूर्ण, अणु CMC_OFS_REG(5),	0x33 पूर्ण,
	अणु CMC_COEF_REG(6),	0x01 पूर्ण, अणु CMC_OFS_REG(6),	0x00 पूर्ण,
	अणु CMC_COEF_REG(7),	0x34 पूर्ण, अणु CMC_OFS_REG(7),	0x94 पूर्ण,
	अणु CMC_COEF_REG(8),	0x75 पूर्ण, अणु CMC_OFS_REG(8),	0x14 पूर्ण,
	/* Color corection coefficients */
	अणु GMA_CTL_REG,		0x03 पूर्ण,	अणु GMA_COEF_REG(0),	0x00 पूर्ण,
	अणु GMA_COEF_REG(1),	0x19 पूर्ण,	अणु GMA_COEF_REG(2),	0x26 पूर्ण,
	अणु GMA_COEF_REG(3),	0x3B पूर्ण,	अणु GMA_COEF_REG(4),	0x5D पूर्ण,
	अणु GMA_COEF_REG(5),	0x79 पूर्ण, अणु GMA_COEF_REG(6),	0x8E पूर्ण,
	अणु GMA_COEF_REG(7),	0x9F पूर्ण,	अणु GMA_COEF_REG(8),	0xAF पूर्ण,
	अणु GMA_COEF_REG(9),	0xBD पूर्ण,	अणु GMA_COEF_REG(10),	0xCA पूर्ण,
	अणु GMA_COEF_REG(11),	0xDD पूर्ण, अणु GMA_COEF_REG(12),	0xEC पूर्ण,
	अणु GMA_COEF_REG(13),	0xF7 पूर्ण,	अणु GMA_COEF_REG(14),	0xFF पूर्ण,
	/* Noise reduction, Z-LPF, YC-LPF and BLPF filters setup */
	अणु ZLPF_CTRL_REG,	0x99 पूर्ण, अणु ZLPF_CTRL2_REG,	0x0E पूर्ण,
	अणु ZLPF_AGH_THR_REG,	0x29 पूर्ण, अणु ZLPF_THR_REG,		0x0F पूर्ण,
	अणु ZLPF_DYN_THR_REG,	0x63 पूर्ण, अणु YCLPF_CTL1_REG,	0x23 पूर्ण,
	अणु YCLPF_CTL2_REG,	0x3B पूर्ण, अणु YCLPF_THR_REG,	0x05 पूर्ण,
	अणु BLPF_CTL_REG,		0x1D पूर्ण, अणु BLPF_THR1_REG,	0x05 पूर्ण,
	अणु BLPF_THR2_REG,	0x04 पूर्ण,
	/* Automatic white balance */
	अणु AWB_CTL1_REG,		0xFB पूर्ण, अणु AWB_CTL2_REG,		0x26 पूर्ण,
	अणु AWB_RMAX_REG,		0x54 पूर्ण, अणु AWB_RMIN_REG,		0x2B पूर्ण,
	अणु AWB_BMAX_REG,		0x57 पूर्ण, अणु AWB_BMIN_REG,		0x29 पूर्ण,
	अणु AWB_RMAXB_REG,	0x50 पूर्ण, अणु AWB_RMINB_REG,	0x43 पूर्ण,
	अणु AWB_BMAXB_REG,	0x30 पूर्ण, अणु AWB_BMINB_REG,	0x22 पूर्ण,
	/* Auto exposure */
	अणु AE_CTL1_REG,		0x8C पूर्ण, अणु AE_CTL2_REG,		0x04 पूर्ण,
	अणु AE_FRM_CTL_REG,	0x01 पूर्ण, अणु AE_FINE_CTL_REG(0),	0x3F पूर्ण,
	अणु AE_FINE_CTL_REG(1),	0xA3 पूर्ण, अणु AE_FINE_CTL_REG(3),	0x34 पूर्ण,
	/* Lens shading compensation */
	अणु LENS_CTRL_REG,	0x01 पूर्ण, अणु LENS_XCEN_REG,	0x80 पूर्ण,
	अणु LENS_YCEN_REG,	0x70 पूर्ण, अणु LENS_R_COMP_REG,	0x53 पूर्ण,
	अणु LENS_G_COMP_REG,	0x40 पूर्ण, अणु LENS_B_COMP_REG,	0x3e पूर्ण,
	अणु REG_TERM,		0 पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा sr030pc30_info *to_sr030pc30(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा sr030pc30_info, sd);
पूर्ण

अटल अंतरभूत पूर्णांक set_i2c_page(काष्ठा sr030pc30_info *info,
			       काष्ठा i2c_client *client, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक ret = 0;
	u32 page = reg >> 8 & 0xFF;

	अगर (info->i2c_reg_page != page && (reg & 0xFF) != 0x03) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, PAGEMODE_REG, page);
		अगर (!ret)
			info->i2c_reg_page = page;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cam_i2c_पढ़ो(काष्ठा v4l2_subdev *sd, u32 reg_addr)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा sr030pc30_info *info = to_sr030pc30(sd);

	पूर्णांक ret = set_i2c_page(info, client, reg_addr);
	अगर (!ret)
		ret = i2c_smbus_पढ़ो_byte_data(client, reg_addr & 0xFF);
	वापस ret;
पूर्ण

अटल पूर्णांक cam_i2c_ग_लिखो(काष्ठा v4l2_subdev *sd, u32 reg_addr, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा sr030pc30_info *info = to_sr030pc30(sd);

	पूर्णांक ret = set_i2c_page(info, client, reg_addr);
	अगर (!ret)
		ret = i2c_smbus_ग_लिखो_byte_data(
			client, reg_addr & 0xFF, val);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक sr030pc30_bulk_ग_लिखो_reg(काष्ठा v4l2_subdev *sd,
				स्थिर काष्ठा i2c_regval *msg)
अणु
	जबतक (msg->addr != REG_TERM) अणु
		पूर्णांक ret = cam_i2c_ग_लिखो(sd, msg->addr, msg->val);
		अगर (ret)
			वापस ret;
		msg++;
	पूर्ण
	वापस 0;
पूर्ण

/* Device reset and sleep mode control */
अटल पूर्णांक sr030pc30_pwr_ctrl(काष्ठा v4l2_subdev *sd,
				     bool reset, bool sleep)
अणु
	काष्ठा sr030pc30_info *info = to_sr030pc30(sd);
	u8 reg = sleep ? 0xF1 : 0xF0;
	पूर्णांक ret = 0;

	अगर (reset)
		ret = cam_i2c_ग_लिखो(sd, POWER_CTRL_REG, reg | 0x02);
	अगर (!ret) अणु
		ret = cam_i2c_ग_लिखो(sd, POWER_CTRL_REG, reg);
		अगर (!ret) अणु
			info->sleep = sleep;
			अगर (reset)
				info->i2c_reg_page = -1;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sr030pc30_set_flip(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा sr030pc30_info *info = to_sr030pc30(sd);

	s32 reg = cam_i2c_पढ़ो(sd, VDO_CTL2_REG);
	अगर (reg < 0)
		वापस reg;

	reg &= 0x7C;
	अगर (info->hflip)
		reg |= 0x01;
	अगर (info->vflip)
		reg |= 0x02;
	वापस cam_i2c_ग_लिखो(sd, VDO_CTL2_REG, reg | 0x80);
पूर्ण

/* Configure resolution, color क्रमmat and image flip */
अटल पूर्णांक sr030pc30_set_params(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा sr030pc30_info *info = to_sr030pc30(sd);
	पूर्णांक ret;

	अगर (!info->curr_win)
		वापस -EINVAL;

	/* Configure the resolution through subsampling */
	ret = cam_i2c_ग_लिखो(sd, VDO_CTL1_REG,
			    info->curr_win->vid_ctl1);

	अगर (!ret && info->curr_fmt)
		ret = cam_i2c_ग_लिखो(sd, ISP_CTL_REG(0),
				info->curr_fmt->ispctl1_reg);
	अगर (!ret)
		ret = sr030pc30_set_flip(sd);

	वापस ret;
पूर्ण

/* Find nearest matching image pixel size. */
अटल पूर्णांक sr030pc30_try_frame_size(काष्ठा v4l2_mbus_framefmt *mf)
अणु
	अचिन्हित पूर्णांक min_err = ~0;
	पूर्णांक i = ARRAY_SIZE(sr030pc30_sizes);
	स्थिर काष्ठा sr030pc30_frmsize *fsize = &sr030pc30_sizes[0],
					*match = शून्य;
	जबतक (i--) अणु
		पूर्णांक err = असल(fsize->width - mf->width)
				+ असल(fsize->height - mf->height);
		अगर (err < min_err) अणु
			min_err = err;
			match = fsize;
		पूर्ण
		fsize++;
	पूर्ण
	अगर (match) अणु
		mf->width  = match->width;
		mf->height = match->height;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sr030pc30_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा sr030pc30_info *info =
		container_of(ctrl->handler, काष्ठा sr030pc30_info, hdl);
	काष्ठा v4l2_subdev *sd = &info->sd;
	पूर्णांक ret = 0;

	v4l2_dbg(1, debug, sd, "%s: ctrl_id: %d, value: %d\n",
			 __func__, ctrl->id, ctrl->val);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		अगर (ctrl->is_new) अणु
			ret = cam_i2c_ग_लिखो(sd, AWB_CTL2_REG,
					ctrl->val ? 0x2E : 0x2F);
			अगर (!ret)
				ret = cam_i2c_ग_लिखो(sd, AWB_CTL1_REG,
						ctrl->val ? 0xFB : 0x7B);
		पूर्ण
		अगर (!ret && info->blue->is_new)
			ret = cam_i2c_ग_लिखो(sd, MWB_BGAIN_REG, info->blue->val);
		अगर (!ret && info->red->is_new)
			ret = cam_i2c_ग_लिखो(sd, MWB_RGAIN_REG, info->red->val);
		वापस ret;

	हाल V4L2_CID_EXPOSURE_AUTO:
		/* स्वतः anti-flicker is also enabled here */
		अगर (ctrl->is_new)
			ret = cam_i2c_ग_लिखो(sd, AE_CTL1_REG,
				ctrl->val == V4L2_EXPOSURE_AUTO ? 0xDC : 0x0C);
		अगर (info->exp->is_new) अणु
			अचिन्हित दीर्घ expos = info->exp->val;

			expos = expos * info->pdata->clk_rate / (8 * 1000);

			अगर (!ret)
				ret = cam_i2c_ग_लिखो(sd, EXP_TIMEH_REG,
						expos >> 16 & 0xFF);
			अगर (!ret)
				ret = cam_i2c_ग_लिखो(sd, EXP_TIMEM_REG,
						expos >> 8 & 0xFF);
			अगर (!ret)
				ret = cam_i2c_ग_लिखो(sd, EXP_TIMEL_REG,
						expos & 0xFF);
		पूर्ण
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sr030pc30_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (!code || code->pad ||
	    code->index >= ARRAY_SIZE(sr030pc30_क्रमmats))
		वापस -EINVAL;

	code->code = sr030pc30_क्रमmats[code->index].code;
	वापस 0;
पूर्ण

अटल पूर्णांक sr030pc30_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf;
	काष्ठा sr030pc30_info *info = to_sr030pc30(sd);

	अगर (!क्रमmat || क्रमmat->pad)
		वापस -EINVAL;

	mf = &क्रमmat->क्रमmat;

	अगर (!info->curr_win || !info->curr_fmt)
		वापस -EINVAL;

	mf->width	= info->curr_win->width;
	mf->height	= info->curr_win->height;
	mf->code	= info->curr_fmt->code;
	mf->colorspace	= info->curr_fmt->colorspace;
	mf->field	= V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

/* Return nearest media bus frame क्रमmat. */
अटल स्थिर काष्ठा sr030pc30_क्रमmat *try_fmt(काष्ठा v4l2_subdev *sd,
					      काष्ठा v4l2_mbus_framefmt *mf)
अणु
	पूर्णांक i;

	sr030pc30_try_frame_size(mf);

	क्रम (i = 0; i < ARRAY_SIZE(sr030pc30_क्रमmats); i++) अणु
		अगर (mf->code == sr030pc30_क्रमmats[i].code)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(sr030pc30_क्रमmats))
		i = 0;

	mf->code = sr030pc30_क्रमmats[i].code;

	वापस &sr030pc30_क्रमmats[i];
पूर्ण

/* Return nearest media bus frame क्रमmat. */
अटल पूर्णांक sr030pc30_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा sr030pc30_info *info = sd ? to_sr030pc30(sd) : शून्य;
	स्थिर काष्ठा sr030pc30_क्रमmat *fmt;
	काष्ठा v4l2_mbus_framefmt *mf;

	अगर (!sd || !क्रमmat)
		वापस -EINVAL;

	mf = &क्रमmat->क्रमmat;
	अगर (क्रमmat->pad)
		वापस -EINVAL;

	fmt = try_fmt(sd, mf);
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cfg->try_fmt = *mf;
		वापस 0;
	पूर्ण

	info->curr_fmt = fmt;

	वापस sr030pc30_set_params(sd);
पूर्ण

अटल पूर्णांक sr030pc30_base_config(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा sr030pc30_info *info = to_sr030pc30(sd);
	पूर्णांक ret;
	अचिन्हित दीर्घ expmin, expmax;

	ret = sr030pc30_bulk_ग_लिखो_reg(sd, sr030pc30_base_regs);
	अगर (!ret) अणु
		info->curr_fmt = &sr030pc30_क्रमmats[0];
		info->curr_win = &sr030pc30_sizes[0];
		ret = sr030pc30_set_params(sd);
	पूर्ण
	अगर (!ret)
		ret = sr030pc30_pwr_ctrl(sd, false, false);

	अगर (ret)
		वापस ret;

	expmin = EXPOS_MIN_MS * info->pdata->clk_rate / (8 * 1000);
	expmax = EXPOS_MAX_MS * info->pdata->clk_rate / (8 * 1000);

	v4l2_dbg(1, debug, sd, "%s: expmin= %lx, expmax= %lx", __func__,
		 expmin, expmax);

	/* Setting up manual exposure समय range */
	ret = cam_i2c_ग_लिखो(sd, EXP_MMINH_REG, expmin >> 8 & 0xFF);
	अगर (!ret)
		ret = cam_i2c_ग_लिखो(sd, EXP_MMINL_REG, expmin & 0xFF);
	अगर (!ret)
		ret = cam_i2c_ग_लिखो(sd, EXP_MMAXH_REG, expmax >> 16 & 0xFF);
	अगर (!ret)
		ret = cam_i2c_ग_लिखो(sd, EXP_MMAXM_REG, expmax >> 8 & 0xFF);
	अगर (!ret)
		ret = cam_i2c_ग_लिखो(sd, EXP_MMAXL_REG, expmax & 0xFF);

	वापस ret;
पूर्ण

अटल पूर्णांक sr030pc30_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा sr030pc30_info *info = to_sr030pc30(sd);
	स्थिर काष्ठा sr030pc30_platक्रमm_data *pdata = info->pdata;
	पूर्णांक ret;

	अगर (pdata == शून्य) अणु
		WARN(1, "No platform data!\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Put sensor पूर्णांकo घातer sleep mode beक्रमe चयनing off
	 * घातer and disabling MCLK.
	 */
	अगर (!on)
		sr030pc30_pwr_ctrl(sd, false, true);

	/* set_घातer controls sensor's घातer and घड़ी */
	अगर (pdata->set_घातer) अणु
		ret = pdata->set_घातer(&client->dev, on);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (on) अणु
		ret = sr030pc30_base_config(sd);
	पूर्ण अन्यथा अणु
		ret = 0;
		info->curr_win = शून्य;
		info->curr_fmt = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sr030pc30_ctrl_ops = अणु
	.s_ctrl = sr030pc30_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops sr030pc30_core_ops = अणु
	.s_घातer	= sr030pc30_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops sr030pc30_pad_ops = अणु
	.क्रमागत_mbus_code = sr030pc30_क्रमागत_mbus_code,
	.get_fmt	= sr030pc30_get_fmt,
	.set_fmt	= sr030pc30_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops sr030pc30_ops = अणु
	.core	= &sr030pc30_core_ops,
	.pad	= &sr030pc30_pad_ops,
पूर्ण;

/*
 * Detect sensor type. Return 0 अगर SR030PC30 was detected
 * or -ENODEV otherwise.
 */
अटल पूर्णांक sr030pc30_detect(काष्ठा i2c_client *client)
अणु
	स्थिर काष्ठा sr030pc30_platक्रमm_data *pdata
		= client->dev.platक्रमm_data;
	पूर्णांक ret;

	/* Enable sensor's घातer and घड़ी */
	अगर (pdata->set_घातer) अणु
		ret = pdata->set_घातer(&client->dev, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, DEVICE_ID_REG);

	अगर (pdata->set_घातer)
		pdata->set_घातer(&client->dev, 0);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "%s: I2C read failed\n", __func__);
		वापस ret;
	पूर्ण

	वापस ret == SR030PC30_ID ? 0 : -ENODEV;
पूर्ण


अटल पूर्णांक sr030pc30_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा sr030pc30_info *info;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_ctrl_handler *hdl;
	स्थिर काष्ठा sr030pc30_platक्रमm_data *pdata
		= client->dev.platक्रमm_data;
	पूर्णांक ret;

	अगर (!pdata) अणु
		dev_err(&client->dev, "No platform data!");
		वापस -EIO;
	पूर्ण

	ret = sr030pc30_detect(client);
	अगर (ret)
		वापस ret;

	info = devm_kzalloc(&client->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	sd = &info->sd;
	info->pdata = client->dev.platक्रमm_data;

	v4l2_i2c_subdev_init(sd, client, &sr030pc30_ops);

	hdl = &info->hdl;
	v4l2_ctrl_handler_init(hdl, 6);
	info->awb = v4l2_ctrl_new_std(hdl, &sr030pc30_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	info->red = v4l2_ctrl_new_std(hdl, &sr030pc30_ctrl_ops,
			V4L2_CID_RED_BALANCE, 0, 127, 1, 64);
	info->blue = v4l2_ctrl_new_std(hdl, &sr030pc30_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, 0, 127, 1, 64);
	info->स्वतःexp = v4l2_ctrl_new_std(hdl, &sr030pc30_ctrl_ops,
			V4L2_CID_EXPOSURE_AUTO, 0, 1, 1, 1);
	info->exp = v4l2_ctrl_new_std(hdl, &sr030pc30_ctrl_ops,
			V4L2_CID_EXPOSURE, EXPOS_MIN_MS, EXPOS_MAX_MS, 1, 30);
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		पूर्णांक err = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_स्वतः_cluster(3, &info->awb, 0, false);
	v4l2_ctrl_स्वतः_cluster(2, &info->स्वतःexp, V4L2_EXPOSURE_MANUAL, false);
	v4l2_ctrl_handler_setup(hdl);

	info->i2c_reg_page	= -1;
	info->hflip		= 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sr030pc30_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sr030pc30_id[] = अणु
	अणु MODULE_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sr030pc30_id);


अटल काष्ठा i2c_driver sr030pc30_i2c_driver = अणु
	.driver = अणु
		.name = MODULE_NAME
	पूर्ण,
	.probe		= sr030pc30_probe,
	.हटाओ		= sr030pc30_हटाओ,
	.id_table	= sr030pc30_id,
पूर्ण;

module_i2c_driver(sr030pc30_i2c_driver);

MODULE_DESCRIPTION("Siliconfile SR030PC30 camera driver");
MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_LICENSE("GPL");
