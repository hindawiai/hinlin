<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI VPFE capture Driver
 *
 * Copyright (C) 2013 - 2014 Texas Instruments, Inc.
 *
 * Benoit Parrot <bparrot@ti.com>
 * Lad, Prabhakar <prabhakar.csengg@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-rect.h>

#समावेश "am437x-vpfe.h"

#घोषणा VPFE_MODULE_NAME	"vpfe"
#घोषणा VPFE_VERSION		"0.1.0"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level 0-8");

#घोषणा vpfe_dbg(level, dev, fmt, arg...)	\
		v4l2_dbg(level, debug, &dev->v4l2_dev, fmt, ##arg)
#घोषणा vpfe_info(dev, fmt, arg...)	\
		v4l2_info(&dev->v4l2_dev, fmt, ##arg)
#घोषणा vpfe_err(dev, fmt, arg...)	\
		v4l2_err(&dev->v4l2_dev, fmt, ##arg)

/* standard inक्रमmation */
काष्ठा vpfe_standard अणु
	v4l2_std_id std_id;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	काष्ठा v4l2_fract pixelaspect;
	पूर्णांक frame_क्रमmat;
पूर्ण;

अटल स्थिर काष्ठा vpfe_standard vpfe_standards[] = अणु
	अणुV4L2_STD_525_60, 720, 480, अणु11, 10पूर्ण, 1पूर्ण,
	अणुV4L2_STD_625_50, 720, 576, अणु54, 59पूर्ण, 1पूर्ण,
पूर्ण;

अटल काष्ठा vpfe_fmt क्रमmats[VPFE_NUM_FORMATS] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.bitsperpixel	= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_UYVY,
		.code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.bitsperpixel	= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YVYU,
		.code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.bitsperpixel	= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_VYUY,
		.code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.bitsperpixel	= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SBGGR8,
		.code		= MEDIA_BUS_FMT_SBGGR8_1X8,
		.bitsperpixel	= 8,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGBRG8,
		.code		= MEDIA_BUS_FMT_SGBRG8_1X8,
		.bitsperpixel	= 8,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG8,
		.code		= MEDIA_BUS_FMT_SGRBG8_1X8,
		.bitsperpixel	= 8,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SRGGB8,
		.code		= MEDIA_BUS_FMT_SRGGB8_1X8,
		.bitsperpixel	= 8,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.code		= MEDIA_BUS_FMT_RGB565_2X8_LE,
		.bitsperpixel	= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB565X,
		.code		= MEDIA_BUS_FMT_RGB565_2X8_BE,
		.bitsperpixel	= 16,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __subdev_get_क्रमmat(काष्ठा vpfe_device *vpfe,
			       काष्ठा v4l2_mbus_framefmt *fmt);
अटल पूर्णांक vpfe_calc_क्रमmat_size(काष्ठा vpfe_device *vpfe,
				 स्थिर काष्ठा vpfe_fmt *fmt,
				 काष्ठा v4l2_क्रमmat *f);

अटल काष्ठा vpfe_fmt *find_क्रमmat_by_code(काष्ठा vpfe_device *vpfe,
					    अचिन्हित पूर्णांक code)
अणु
	काष्ठा vpfe_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < vpfe->num_active_fmt; k++) अणु
		fmt = vpfe->active_fmt[k];
		अगर (fmt->code == code)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा vpfe_fmt *find_क्रमmat_by_pix(काष्ठा vpfe_device *vpfe,
					   अचिन्हित पूर्णांक pixelक्रमmat)
अणु
	काष्ठा vpfe_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < vpfe->num_active_fmt; k++) अणु
		fmt = vpfe->active_fmt[k];
		अगर (fmt->fourcc == pixelक्रमmat)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक __get_bytesperpixel(काष्ठा vpfe_device *vpfe,
					स्थिर काष्ठा vpfe_fmt *fmt)
अणु
	काष्ठा vpfe_subdev_info *sdinfo = vpfe->current_subdev;
	अचिन्हित पूर्णांक bus_width = sdinfo->vpfe_param.bus_width;
	u32 bpp, bus_width_bytes, घड़ीsperpixel;

	bus_width_bytes = ALIGN(bus_width, 8) >> 3;
	घड़ीsperpixel = DIV_ROUND_UP(fmt->bitsperpixel, bus_width);
	bpp = घड़ीsperpixel * bus_width_bytes;

	वापस bpp;
पूर्ण

/*  Prपूर्णांक Four-अक्षरacter-code (FOURCC) */
अटल अक्षर *prपूर्णांक_fourcc(u32 fmt)
अणु
	अटल अक्षर code[5];

	code[0] = (अचिन्हित अक्षर)(fmt & 0xff);
	code[1] = (अचिन्हित अक्षर)((fmt >> 8) & 0xff);
	code[2] = (अचिन्हित अक्षर)((fmt >> 16) & 0xff);
	code[3] = (अचिन्हित अक्षर)((fmt >> 24) & 0xff);
	code[4] = '\0';

	वापस code;
पूर्ण

अटल अंतरभूत u32 vpfe_reg_पढ़ो(काष्ठा vpfe_ccdc *ccdc, u32 offset)
अणु
	वापस ioपढ़ो32(ccdc->ccdc_cfg.base_addr + offset);
पूर्ण

अटल अंतरभूत व्योम vpfe_reg_ग_लिखो(काष्ठा vpfe_ccdc *ccdc, u32 val, u32 offset)
अणु
	ioग_लिखो32(val, ccdc->ccdc_cfg.base_addr + offset);
पूर्ण

अटल अंतरभूत काष्ठा vpfe_device *to_vpfe(काष्ठा vpfe_ccdc *ccdc)
अणु
	वापस container_of(ccdc, काष्ठा vpfe_device, ccdc);
पूर्ण

अटल अंतरभूत
काष्ठा vpfe_cap_buffer *to_vpfe_buffer(काष्ठा vb2_v4l2_buffer *vb)
अणु
	वापस container_of(vb, काष्ठा vpfe_cap_buffer, vb);
पूर्ण

अटल अंतरभूत व्योम vpfe_pcr_enable(काष्ठा vpfe_ccdc *ccdc, पूर्णांक flag)
अणु
	vpfe_reg_ग_लिखो(ccdc, !!flag, VPFE_PCR);
पूर्ण

अटल व्योम vpfe_config_enable(काष्ठा vpfe_ccdc *ccdc, पूर्णांक flag)
अणु
	अचिन्हित पूर्णांक cfg;

	अगर (!flag) अणु
		cfg = vpfe_reg_पढ़ो(ccdc, VPFE_CONFIG);
		cfg &= ~(VPFE_CONFIG_EN_ENABLE << VPFE_CONFIG_EN_SHIFT);
	पूर्ण अन्यथा अणु
		cfg = VPFE_CONFIG_EN_ENABLE << VPFE_CONFIG_EN_SHIFT;
	पूर्ण

	vpfe_reg_ग_लिखो(ccdc, cfg, VPFE_CONFIG);
पूर्ण

अटल व्योम vpfe_ccdc_setwin(काष्ठा vpfe_ccdc *ccdc,
			     काष्ठा v4l2_rect *image_win,
			     क्रमागत ccdc_frmfmt frm_fmt,
			     पूर्णांक bpp)
अणु
	पूर्णांक horz_start, horz_nr_pixels;
	पूर्णांक vert_start, vert_nr_lines;
	पूर्णांक val, mid_img;

	/*
	 * ppc - per pixel count. indicates how many pixels per cell
	 * output to SDRAM. example, क्रम ycbcr, it is one y and one c, so 2.
	 * raw capture this is 1
	 */
	horz_start = image_win->left * bpp;
	horz_nr_pixels = (image_win->width * bpp) - 1;
	vpfe_reg_ग_लिखो(ccdc, (horz_start << VPFE_HORZ_INFO_SPH_SHIFT) |
				horz_nr_pixels, VPFE_HORZ_INFO);

	vert_start = image_win->top;

	अगर (frm_fmt == CCDC_FRMFMT_INTERLACED) अणु
		vert_nr_lines = (image_win->height >> 1) - 1;
		vert_start >>= 1;
		/* configure VDINT0 */
		val = (vert_start << VPFE_VDINT_VDINT0_SHIFT);
	पूर्ण अन्यथा अणु
		vert_nr_lines = image_win->height - 1;
		/*
		 * configure VDINT0 and VDINT1. VDINT1 will be at half
		 * of image height
		 */
		mid_img = vert_start + (image_win->height / 2);
		val = (vert_start << VPFE_VDINT_VDINT0_SHIFT) |
				(mid_img & VPFE_VDINT_VDINT1_MASK);
	पूर्ण

	vpfe_reg_ग_लिखो(ccdc, val, VPFE_VDINT);

	vpfe_reg_ग_लिखो(ccdc, (vert_start << VPFE_VERT_START_SLV0_SHIFT) |
				vert_start, VPFE_VERT_START);
	vpfe_reg_ग_लिखो(ccdc, vert_nr_lines, VPFE_VERT_LINES);
पूर्ण

अटल व्योम vpfe_reg_dump(काष्ठा vpfe_ccdc *ccdc)
अणु
	काष्ठा vpfe_device *vpfe = to_vpfe(ccdc);

	vpfe_dbg(3, vpfe, "ALAW: 0x%x\n", vpfe_reg_पढ़ो(ccdc, VPFE_ALAW));
	vpfe_dbg(3, vpfe, "CLAMP: 0x%x\n", vpfe_reg_पढ़ो(ccdc, VPFE_CLAMP));
	vpfe_dbg(3, vpfe, "DCSUB: 0x%x\n", vpfe_reg_पढ़ो(ccdc, VPFE_DCSUB));
	vpfe_dbg(3, vpfe, "BLKCMP: 0x%x\n", vpfe_reg_पढ़ो(ccdc, VPFE_BLKCMP));
	vpfe_dbg(3, vpfe, "COLPTN: 0x%x\n", vpfe_reg_पढ़ो(ccdc, VPFE_COLPTN));
	vpfe_dbg(3, vpfe, "SDOFST: 0x%x\n", vpfe_reg_पढ़ो(ccdc, VPFE_SDOFST));
	vpfe_dbg(3, vpfe, "SYN_MODE: 0x%x\n",
		 vpfe_reg_पढ़ो(ccdc, VPFE_SYNMODE));
	vpfe_dbg(3, vpfe, "HSIZE_OFF: 0x%x\n",
		 vpfe_reg_पढ़ो(ccdc, VPFE_HSIZE_OFF));
	vpfe_dbg(3, vpfe, "HORZ_INFO: 0x%x\n",
		 vpfe_reg_पढ़ो(ccdc, VPFE_HORZ_INFO));
	vpfe_dbg(3, vpfe, "VERT_START: 0x%x\n",
		 vpfe_reg_पढ़ो(ccdc, VPFE_VERT_START));
	vpfe_dbg(3, vpfe, "VERT_LINES: 0x%x\n",
		 vpfe_reg_पढ़ो(ccdc, VPFE_VERT_LINES));
पूर्ण

अटल पूर्णांक
vpfe_ccdc_validate_param(काष्ठा vpfe_ccdc *ccdc,
			 काष्ठा vpfe_ccdc_config_params_raw *ccdcparam)
अणु
	काष्ठा vpfe_device *vpfe = to_vpfe(ccdc);
	u8 max_gamma, max_data;

	अगर (!ccdcparam->alaw.enable)
		वापस 0;

	max_gamma = ccdc_gamma_width_max_bit(ccdcparam->alaw.gamma_wd);
	max_data = ccdc_data_size_max_bit(ccdcparam->data_sz);

	अगर (ccdcparam->alaw.gamma_wd > VPFE_CCDC_GAMMA_BITS_09_0 ||
	    ccdcparam->data_sz > VPFE_CCDC_DATA_8BITS ||
	    max_gamma > max_data) अणु
		vpfe_dbg(1, vpfe, "Invalid data line select\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
vpfe_ccdc_update_raw_params(काष्ठा vpfe_ccdc *ccdc,
			    काष्ठा vpfe_ccdc_config_params_raw *raw_params)
अणु
	काष्ठा vpfe_ccdc_config_params_raw *config_params =
				&ccdc->ccdc_cfg.bayer.config_params;

	*config_params = *raw_params;
पूर्ण

/*
 * vpfe_ccdc_restore_शेषs()
 * This function will ग_लिखो शेषs to all CCDC रेजिस्टरs
 */
अटल व्योम vpfe_ccdc_restore_शेषs(काष्ठा vpfe_ccdc *ccdc)
अणु
	पूर्णांक i;

	/* Disable CCDC */
	vpfe_pcr_enable(ccdc, 0);

	/* set all रेजिस्टरs to शेष value */
	क्रम (i = 4; i <= 0x94; i += 4)
		vpfe_reg_ग_लिखो(ccdc, 0,  i);

	vpfe_reg_ग_लिखो(ccdc, VPFE_NO_CULLING, VPFE_CULLING);
	vpfe_reg_ग_लिखो(ccdc, VPFE_CCDC_GAMMA_BITS_11_2, VPFE_ALAW);
पूर्ण

अटल पूर्णांक vpfe_ccdc_बंद(काष्ठा vpfe_ccdc *ccdc, काष्ठा device *dev)
अणु
	काष्ठा vpfe_device *vpfe = to_vpfe(ccdc);
	u32 dma_cntl, pcr;

	pcr = vpfe_reg_पढ़ो(ccdc, VPFE_PCR);
	अगर (pcr)
		vpfe_dbg(1, vpfe, "VPFE_PCR is still set (%x)", pcr);

	dma_cntl = vpfe_reg_पढ़ो(ccdc, VPFE_DMA_CNTL);
	अगर ((dma_cntl & VPFE_DMA_CNTL_OVERFLOW))
		vpfe_dbg(1, vpfe, "VPFE_DMA_CNTL_OVERFLOW is still set (%x)",
			 dma_cntl);

	/* Disable CCDC by resetting all रेजिस्टर to शेष POR values */
	vpfe_ccdc_restore_शेषs(ccdc);

	/* Disabled the module at the CONFIG level */
	vpfe_config_enable(ccdc, 0);

	pm_runसमय_put_sync(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_ccdc_set_params(काष्ठा vpfe_ccdc *ccdc, व्योम __user *params)
अणु
	काष्ठा vpfe_device *vpfe = to_vpfe(ccdc);
	काष्ठा vpfe_ccdc_config_params_raw raw_params;
	पूर्णांक x;

	अगर (ccdc->ccdc_cfg.अगर_type != VPFE_RAW_BAYER)
		वापस -EINVAL;

	x = copy_from_user(&raw_params, params, माप(raw_params));
	अगर (x) अणु
		vpfe_dbg(1, vpfe,
			 "%s: error in copying ccdc params, %d\n",
			 __func__, x);
		वापस -EFAULT;
	पूर्ण

	अगर (!vpfe_ccdc_validate_param(ccdc, &raw_params)) अणु
		vpfe_ccdc_update_raw_params(ccdc, &raw_params);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * vpfe_ccdc_config_ycbcr()
 * This function will configure CCDC क्रम YCbCr video capture
 */
अटल व्योम vpfe_ccdc_config_ycbcr(काष्ठा vpfe_ccdc *ccdc)
अणु
	काष्ठा ccdc_params_ycbcr *params = &ccdc->ccdc_cfg.ycbcr;
	u32 syn_mode;

	/*
	 * first restore the CCDC रेजिस्टरs to शेष values
	 * This is important since we assume शेष values to be set in
	 * a lot of रेजिस्टरs that we didn't touch
	 */
	vpfe_ccdc_restore_शेषs(ccdc);

	/*
	 * configure pixel क्रमmat, frame क्रमmat, configure video frame
	 * क्रमmat, enable output to SDRAM, enable पूर्णांकernal timing generator
	 * and 8bit pack mode
	 */
	syn_mode = (((params->pix_fmt & VPFE_SYN_MODE_INPMOD_MASK) <<
		    VPFE_SYN_MODE_INPMOD_SHIFT) |
		    ((params->frm_fmt & VPFE_SYN_FLDMODE_MASK) <<
		    VPFE_SYN_FLDMODE_SHIFT) | VPFE_VDHDEN_ENABLE |
		    VPFE_WEN_ENABLE | VPFE_DATA_PACK_ENABLE);

	/* setup BT.656 sync mode */
	अगर (params->bt656_enable) अणु
		vpfe_reg_ग_लिखो(ccdc, VPFE_REC656IF_BT656_EN, VPFE_REC656IF);

		/*
		 * configure the FID, VD, HD pin polarity,
		 * fld,hd pol positive, vd negative, 8-bit data
		 */
		syn_mode |= VPFE_SYN_MODE_VD_POL_NEGATIVE;
		अगर (ccdc->ccdc_cfg.अगर_type == VPFE_BT656_10BIT)
			syn_mode |= VPFE_SYN_MODE_10BITS;
		अन्यथा
			syn_mode |= VPFE_SYN_MODE_8BITS;
	पूर्ण अन्यथा अणु
		/* y/c बाह्यal sync mode */
		syn_mode |= (((params->fid_pol & VPFE_FID_POL_MASK) <<
			     VPFE_FID_POL_SHIFT) |
			     ((params->hd_pol & VPFE_HD_POL_MASK) <<
			     VPFE_HD_POL_SHIFT) |
			     ((params->vd_pol & VPFE_VD_POL_MASK) <<
			     VPFE_VD_POL_SHIFT));
	पूर्ण
	vpfe_reg_ग_लिखो(ccdc, syn_mode, VPFE_SYNMODE);

	/* configure video winकरोw */
	vpfe_ccdc_setwin(ccdc, &params->win,
			 params->frm_fmt, params->bytesperpixel);

	/*
	 * configure the order of y cb cr in SDRAM, and disable latch
	 * पूर्णांकernal रेजिस्टर on vsync
	 */
	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_BT656_10BIT)
		vpfe_reg_ग_लिखो(ccdc,
			       (params->pix_order << VPFE_CCDCFG_Y8POS_SHIFT) |
			       VPFE_LATCH_ON_VSYNC_DISABLE |
			       VPFE_CCDCFG_BW656_10BIT, VPFE_CCDCFG);
	अन्यथा
		vpfe_reg_ग_लिखो(ccdc,
			       (params->pix_order << VPFE_CCDCFG_Y8POS_SHIFT) |
			       VPFE_LATCH_ON_VSYNC_DISABLE, VPFE_CCDCFG);

	/*
	 * configure the horizontal line offset. This should be a
	 * on 32 byte boundary. So clear LSB 5 bits
	 */
	vpfe_reg_ग_लिखो(ccdc, params->bytesperline, VPFE_HSIZE_OFF);

	/* configure the memory line offset */
	अगर (params->buf_type == CCDC_BUFTYPE_FLD_INTERLEAVED)
		/* two fields are पूर्णांकerleaved in memory */
		vpfe_reg_ग_लिखो(ccdc, VPFE_SDOFST_FIELD_INTERLEAVED,
			       VPFE_SDOFST);
पूर्ण

अटल व्योम
vpfe_ccdc_config_black_clamp(काष्ठा vpfe_ccdc *ccdc,
			     काष्ठा vpfe_ccdc_black_clamp *bclamp)
अणु
	u32 val;

	अगर (!bclamp->enable) अणु
		/* configure DCSub */
		val = (bclamp->dc_sub) & VPFE_BLK_DC_SUB_MASK;
		vpfe_reg_ग_लिखो(ccdc, val, VPFE_DCSUB);
		vpfe_reg_ग_लिखो(ccdc, VPFE_CLAMP_DEFAULT_VAL, VPFE_CLAMP);
		वापस;
	पूर्ण
	/*
	 * Configure gain,  Start pixel, No of line to be avg,
	 * No of pixel/line to be avg, & Enable the Black clamping
	 */
	val = ((bclamp->sgain & VPFE_BLK_SGAIN_MASK) |
	       ((bclamp->start_pixel & VPFE_BLK_ST_PXL_MASK) <<
		VPFE_BLK_ST_PXL_SHIFT) |
	       ((bclamp->sample_ln & VPFE_BLK_SAMPLE_LINE_MASK) <<
		VPFE_BLK_SAMPLE_LINE_SHIFT) |
	       ((bclamp->sample_pixel & VPFE_BLK_SAMPLE_LN_MASK) <<
		VPFE_BLK_SAMPLE_LN_SHIFT) | VPFE_BLK_CLAMP_ENABLE);
	vpfe_reg_ग_लिखो(ccdc, val, VPFE_CLAMP);
	/* If Black clamping is enable then make dcsub 0 */
	vpfe_reg_ग_लिखो(ccdc, VPFE_DCSUB_DEFAULT_VAL, VPFE_DCSUB);
पूर्ण

अटल व्योम
vpfe_ccdc_config_black_compense(काष्ठा vpfe_ccdc *ccdc,
				काष्ठा vpfe_ccdc_black_compensation *bcomp)
अणु
	u32 val;

	val = ((bcomp->b & VPFE_BLK_COMP_MASK) |
	      ((bcomp->gb & VPFE_BLK_COMP_MASK) <<
	       VPFE_BLK_COMP_GB_COMP_SHIFT) |
	      ((bcomp->gr & VPFE_BLK_COMP_MASK) <<
	       VPFE_BLK_COMP_GR_COMP_SHIFT) |
	      ((bcomp->r & VPFE_BLK_COMP_MASK) <<
	       VPFE_BLK_COMP_R_COMP_SHIFT));
	vpfe_reg_ग_लिखो(ccdc, val, VPFE_BLKCMP);
पूर्ण

/*
 * vpfe_ccdc_config_raw()
 * This function will configure CCDC क्रम Raw capture mode
 */
अटल व्योम vpfe_ccdc_config_raw(काष्ठा vpfe_ccdc *ccdc)
अणु
	काष्ठा vpfe_device *vpfe = to_vpfe(ccdc);
	काष्ठा vpfe_ccdc_config_params_raw *config_params =
				&ccdc->ccdc_cfg.bayer.config_params;
	काष्ठा ccdc_params_raw *params = &ccdc->ccdc_cfg.bayer;
	अचिन्हित पूर्णांक syn_mode;
	अचिन्हित पूर्णांक val;

	/* Reset CCDC */
	vpfe_ccdc_restore_शेषs(ccdc);

	/* Disable latching function रेजिस्टरs on VSYNC  */
	vpfe_reg_ग_लिखो(ccdc, VPFE_LATCH_ON_VSYNC_DISABLE, VPFE_CCDCFG);

	/*
	 * Configure the vertical sync polarity(SYN_MODE.VDPOL),
	 * horizontal sync polarity (SYN_MODE.HDPOL), frame id polarity
	 * (SYN_MODE.FLDPOL), frame क्रमmat(progressive or पूर्णांकerlace),
	 * data size(SYNMODE.DATSIZ), &pixel क्रमmat (Input mode), output
	 * SDRAM, enable पूर्णांकernal timing generator
	 */
	syn_mode = (((params->vd_pol & VPFE_VD_POL_MASK) << VPFE_VD_POL_SHIFT) |
		   ((params->hd_pol & VPFE_HD_POL_MASK) << VPFE_HD_POL_SHIFT) |
		   ((params->fid_pol & VPFE_FID_POL_MASK) <<
		   VPFE_FID_POL_SHIFT) | ((params->frm_fmt &
		   VPFE_FRM_FMT_MASK) << VPFE_FRM_FMT_SHIFT) |
		   ((config_params->data_sz & VPFE_DATA_SZ_MASK) <<
		   VPFE_DATA_SZ_SHIFT) | ((params->pix_fmt &
		   VPFE_PIX_FMT_MASK) << VPFE_PIX_FMT_SHIFT) |
		   VPFE_WEN_ENABLE | VPFE_VDHDEN_ENABLE);

	/* Enable and configure aLaw रेजिस्टर अगर needed */
	अगर (config_params->alaw.enable) अणु
		val = ((config_params->alaw.gamma_wd &
		      VPFE_ALAW_GAMMA_WD_MASK) | VPFE_ALAW_ENABLE);
		vpfe_reg_ग_लिखो(ccdc, val, VPFE_ALAW);
		vpfe_dbg(3, vpfe, "\nWriting 0x%x to ALAW...\n", val);
	पूर्ण

	/* Configure video winकरोw */
	vpfe_ccdc_setwin(ccdc, &params->win, params->frm_fmt,
			 params->bytesperpixel);

	/* Configure Black Clamp */
	vpfe_ccdc_config_black_clamp(ccdc, &config_params->blk_clamp);

	/* Configure Black level compensation */
	vpfe_ccdc_config_black_compense(ccdc, &config_params->blk_comp);

	/* If data size is 8 bit then pack the data */
	अगर ((config_params->data_sz == VPFE_CCDC_DATA_8BITS) ||
	    config_params->alaw.enable)
		syn_mode |= VPFE_DATA_PACK_ENABLE;

	/*
	 * Configure Horizontal offset रेजिस्टर. If pack 8 is enabled then
	 * 1 pixel will take 1 byte
	 */
	vpfe_reg_ग_लिखो(ccdc, params->bytesperline, VPFE_HSIZE_OFF);

	vpfe_dbg(3, vpfe, "Writing %d (%x) to HSIZE_OFF\n",
		params->bytesperline, params->bytesperline);

	/* Set value क्रम SDOFST */
	अगर (params->frm_fmt == CCDC_FRMFMT_INTERLACED) अणु
		अगर (params->image_invert_enable) अणु
			/* For पूर्णांकerlace inverse mode */
			vpfe_reg_ग_लिखो(ccdc, VPFE_INTERLACED_IMAGE_INVERT,
				   VPFE_SDOFST);
		पूर्ण अन्यथा अणु
			/* For पूर्णांकerlace non inverse mode */
			vpfe_reg_ग_लिखो(ccdc, VPFE_INTERLACED_NO_IMAGE_INVERT,
				   VPFE_SDOFST);
		पूर्ण
	पूर्ण अन्यथा अगर (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE) अणु
		vpfe_reg_ग_लिखो(ccdc, VPFE_PROGRESSIVE_NO_IMAGE_INVERT,
			   VPFE_SDOFST);
	पूर्ण

	vpfe_reg_ग_लिखो(ccdc, syn_mode, VPFE_SYNMODE);

	vpfe_reg_dump(ccdc);
पूर्ण

अटल अंतरभूत पूर्णांक
vpfe_ccdc_set_buftype(काष्ठा vpfe_ccdc *ccdc,
		      क्रमागत ccdc_buftype buf_type)
अणु
	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		ccdc->ccdc_cfg.bayer.buf_type = buf_type;
	अन्यथा
		ccdc->ccdc_cfg.ycbcr.buf_type = buf_type;

	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत ccdc_buftype vpfe_ccdc_get_buftype(काष्ठा vpfe_ccdc *ccdc)
अणु
	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		वापस ccdc->ccdc_cfg.bayer.buf_type;

	वापस ccdc->ccdc_cfg.ycbcr.buf_type;
पूर्ण

अटल पूर्णांक vpfe_ccdc_set_pixel_क्रमmat(काष्ठा vpfe_ccdc *ccdc, u32 pixfmt)
अणु
	काष्ठा vpfe_device *vpfe = to_vpfe(ccdc);

	vpfe_dbg(1, vpfe, "%s: if_type: %d, pixfmt:%s\n",
		 __func__, ccdc->ccdc_cfg.अगर_type, prपूर्णांक_fourcc(pixfmt));

	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		ccdc->ccdc_cfg.bayer.pix_fmt = CCDC_PIXFMT_RAW;
		/*
		 * Need to clear it in हाल it was left on
		 * after the last capture.
		 */
		ccdc->ccdc_cfg.bayer.config_params.alaw.enable = 0;

		चयन (pixfmt) अणु
		हाल V4L2_PIX_FMT_SBGGR8:
			ccdc->ccdc_cfg.bayer.config_params.alaw.enable = 1;
			अवरोध;

		हाल V4L2_PIX_FMT_YUYV:
		हाल V4L2_PIX_FMT_UYVY:
		हाल V4L2_PIX_FMT_YUV420:
		हाल V4L2_PIX_FMT_NV12:
		हाल V4L2_PIX_FMT_RGB565X:
			अवरोध;

		हाल V4L2_PIX_FMT_SBGGR16:
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (pixfmt) अणु
		हाल V4L2_PIX_FMT_YUYV:
			ccdc->ccdc_cfg.ycbcr.pix_order = CCDC_PIXORDER_YCBYCR;
			अवरोध;

		हाल V4L2_PIX_FMT_UYVY:
			ccdc->ccdc_cfg.ycbcr.pix_order = CCDC_PIXORDER_CBYCRY;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 vpfe_ccdc_get_pixel_क्रमmat(काष्ठा vpfe_ccdc *ccdc)
अणु
	u32 pixfmt;

	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		pixfmt = V4L2_PIX_FMT_YUYV;
	पूर्ण अन्यथा अणु
		अगर (ccdc->ccdc_cfg.ycbcr.pix_order == CCDC_PIXORDER_YCBYCR)
			pixfmt = V4L2_PIX_FMT_YUYV;
		अन्यथा
			pixfmt = V4L2_PIX_FMT_UYVY;
	पूर्ण

	वापस pixfmt;
पूर्ण

अटल पूर्णांक
vpfe_ccdc_set_image_winकरोw(काष्ठा vpfe_ccdc *ccdc,
			   काष्ठा v4l2_rect *win, अचिन्हित पूर्णांक bpp)
अणु
	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		ccdc->ccdc_cfg.bayer.win = *win;
		ccdc->ccdc_cfg.bayer.bytesperpixel = bpp;
		ccdc->ccdc_cfg.bayer.bytesperline = ALIGN(win->width * bpp, 32);
	पूर्ण अन्यथा अणु
		ccdc->ccdc_cfg.ycbcr.win = *win;
		ccdc->ccdc_cfg.ycbcr.bytesperpixel = bpp;
		ccdc->ccdc_cfg.ycbcr.bytesperline = ALIGN(win->width * bpp, 32);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
vpfe_ccdc_get_image_winकरोw(काष्ठा vpfe_ccdc *ccdc,
			   काष्ठा v4l2_rect *win)
अणु
	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		*win = ccdc->ccdc_cfg.bayer.win;
	अन्यथा
		*win = ccdc->ccdc_cfg.ycbcr.win;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vpfe_ccdc_get_line_length(काष्ठा vpfe_ccdc *ccdc)
अणु
	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		वापस ccdc->ccdc_cfg.bayer.bytesperline;

	वापस ccdc->ccdc_cfg.ycbcr.bytesperline;
पूर्ण

अटल अंतरभूत पूर्णांक
vpfe_ccdc_set_frame_क्रमmat(काष्ठा vpfe_ccdc *ccdc,
			   क्रमागत ccdc_frmfmt frm_fmt)
अणु
	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		ccdc->ccdc_cfg.bayer.frm_fmt = frm_fmt;
	अन्यथा
		ccdc->ccdc_cfg.ycbcr.frm_fmt = frm_fmt;

	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत ccdc_frmfmt
vpfe_ccdc_get_frame_क्रमmat(काष्ठा vpfe_ccdc *ccdc)
अणु
	अगर (ccdc->ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		वापस ccdc->ccdc_cfg.bayer.frm_fmt;

	वापस ccdc->ccdc_cfg.ycbcr.frm_fmt;
पूर्ण

अटल अंतरभूत पूर्णांक vpfe_ccdc_getfid(काष्ठा vpfe_ccdc *ccdc)
अणु
	वापस (vpfe_reg_पढ़ो(ccdc, VPFE_SYNMODE) >> 15) & 1;
पूर्ण

अटल अंतरभूत व्योम vpfe_set_sdr_addr(काष्ठा vpfe_ccdc *ccdc, अचिन्हित दीर्घ addr)
अणु
	vpfe_reg_ग_लिखो(ccdc, addr & 0xffffffe0, VPFE_SDR_ADDR);
पूर्ण

अटल पूर्णांक vpfe_ccdc_set_hw_अगर_params(काष्ठा vpfe_ccdc *ccdc,
				      काष्ठा vpfe_hw_अगर_param *params)
अणु
	काष्ठा vpfe_device *vpfe = to_vpfe(ccdc);

	ccdc->ccdc_cfg.अगर_type = params->अगर_type;

	चयन (params->अगर_type) अणु
	हाल VPFE_BT656:
	हाल VPFE_YCBCR_SYNC_16:
	हाल VPFE_YCBCR_SYNC_8:
	हाल VPFE_BT656_10BIT:
		ccdc->ccdc_cfg.ycbcr.vd_pol = params->vdpol;
		ccdc->ccdc_cfg.ycbcr.hd_pol = params->hdpol;
		अवरोध;

	हाल VPFE_RAW_BAYER:
		ccdc->ccdc_cfg.bayer.vd_pol = params->vdpol;
		ccdc->ccdc_cfg.bayer.hd_pol = params->hdpol;
		अगर (params->bus_width == 10)
			ccdc->ccdc_cfg.bayer.config_params.data_sz =
				VPFE_CCDC_DATA_10BITS;
		अन्यथा
			ccdc->ccdc_cfg.bayer.config_params.data_sz =
				VPFE_CCDC_DATA_8BITS;
		vpfe_dbg(1, vpfe, "params.bus_width: %d\n",
			params->bus_width);
		vpfe_dbg(1, vpfe, "config_params.data_sz: %d\n",
			ccdc->ccdc_cfg.bayer.config_params.data_sz);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vpfe_clear_पूर्णांकr(काष्ठा vpfe_ccdc *ccdc, पूर्णांक vdपूर्णांक)
अणु
	अचिन्हित पूर्णांक vpfe_पूर्णांक_status;

	vpfe_पूर्णांक_status = vpfe_reg_पढ़ो(ccdc, VPFE_IRQ_STS);

	चयन (vdपूर्णांक) अणु
	/* VD0 पूर्णांकerrupt */
	हाल VPFE_VDINT0:
		vpfe_पूर्णांक_status &= ~VPFE_VDINT0;
		vpfe_पूर्णांक_status |= VPFE_VDINT0;
		अवरोध;

	/* VD1 पूर्णांकerrupt */
	हाल VPFE_VDINT1:
		vpfe_पूर्णांक_status &= ~VPFE_VDINT1;
		vpfe_पूर्णांक_status |= VPFE_VDINT1;
		अवरोध;

	/* VD2 पूर्णांकerrupt */
	हाल VPFE_VDINT2:
		vpfe_पूर्णांक_status &= ~VPFE_VDINT2;
		vpfe_पूर्णांक_status |= VPFE_VDINT2;
		अवरोध;

	/* Clear all पूर्णांकerrupts */
	शेष:
		vpfe_पूर्णांक_status &= ~(VPFE_VDINT0 |
				VPFE_VDINT1 |
				VPFE_VDINT2);
		vpfe_पूर्णांक_status |= (VPFE_VDINT0 |
				VPFE_VDINT1 |
				VPFE_VDINT2);
		अवरोध;
	पूर्ण
	/* Clear specअगरic VDINT from the status रेजिस्टर */
	vpfe_reg_ग_लिखो(ccdc, vpfe_पूर्णांक_status, VPFE_IRQ_STS);

	vpfe_पूर्णांक_status = vpfe_reg_पढ़ो(ccdc, VPFE_IRQ_STS);

	/* Acknowledge that we are करोne with all पूर्णांकerrupts */
	vpfe_reg_ग_लिखो(ccdc, 1, VPFE_IRQ_EOI);
पूर्ण

अटल व्योम vpfe_ccdc_config_शेषs(काष्ठा vpfe_ccdc *ccdc)
अणु
	ccdc->ccdc_cfg.अगर_type = VPFE_RAW_BAYER;

	ccdc->ccdc_cfg.ycbcr.pix_fmt = CCDC_PIXFMT_YCBCR_8BIT;
	ccdc->ccdc_cfg.ycbcr.frm_fmt = CCDC_FRMFMT_INTERLACED;
	ccdc->ccdc_cfg.ycbcr.fid_pol = VPFE_PINPOL_POSITIVE;
	ccdc->ccdc_cfg.ycbcr.vd_pol = VPFE_PINPOL_POSITIVE;
	ccdc->ccdc_cfg.ycbcr.hd_pol = VPFE_PINPOL_POSITIVE;
	ccdc->ccdc_cfg.ycbcr.pix_order = CCDC_PIXORDER_CBYCRY;
	ccdc->ccdc_cfg.ycbcr.buf_type = CCDC_BUFTYPE_FLD_INTERLEAVED;

	ccdc->ccdc_cfg.ycbcr.win.left = 0;
	ccdc->ccdc_cfg.ycbcr.win.top = 0;
	ccdc->ccdc_cfg.ycbcr.win.width = 720;
	ccdc->ccdc_cfg.ycbcr.win.height = 576;
	ccdc->ccdc_cfg.ycbcr.bt656_enable = 1;

	ccdc->ccdc_cfg.bayer.pix_fmt = CCDC_PIXFMT_RAW;
	ccdc->ccdc_cfg.bayer.frm_fmt = CCDC_FRMFMT_PROGRESSIVE;
	ccdc->ccdc_cfg.bayer.fid_pol = VPFE_PINPOL_POSITIVE;
	ccdc->ccdc_cfg.bayer.vd_pol = VPFE_PINPOL_POSITIVE;
	ccdc->ccdc_cfg.bayer.hd_pol = VPFE_PINPOL_POSITIVE;

	ccdc->ccdc_cfg.bayer.win.left = 0;
	ccdc->ccdc_cfg.bayer.win.top = 0;
	ccdc->ccdc_cfg.bayer.win.width = 800;
	ccdc->ccdc_cfg.bayer.win.height = 600;
	ccdc->ccdc_cfg.bayer.config_params.data_sz = VPFE_CCDC_DATA_8BITS;
	ccdc->ccdc_cfg.bayer.config_params.alaw.gamma_wd =
						VPFE_CCDC_GAMMA_BITS_09_0;
पूर्ण

/*
 * vpfe_get_ccdc_image_क्रमmat - Get image parameters based on CCDC settings
 */
अटल पूर्णांक vpfe_get_ccdc_image_क्रमmat(काष्ठा vpfe_device *vpfe,
				      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_rect image_win;
	क्रमागत ccdc_buftype buf_type;
	क्रमागत ccdc_frmfmt frm_fmt;

	स_रखो(f, 0, माप(*f));
	f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vpfe_ccdc_get_image_winकरोw(&vpfe->ccdc, &image_win);
	f->fmt.pix.width = image_win.width;
	f->fmt.pix.height = image_win.height;
	f->fmt.pix.bytesperline = vpfe_ccdc_get_line_length(&vpfe->ccdc);
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
				f->fmt.pix.height;
	buf_type = vpfe_ccdc_get_buftype(&vpfe->ccdc);
	f->fmt.pix.pixelक्रमmat = vpfe_ccdc_get_pixel_क्रमmat(&vpfe->ccdc);
	frm_fmt = vpfe_ccdc_get_frame_क्रमmat(&vpfe->ccdc);

	अगर (frm_fmt == CCDC_FRMFMT_PROGRESSIVE) अणु
		f->fmt.pix.field = V4L2_FIELD_NONE;
	पूर्ण अन्यथा अगर (frm_fmt == CCDC_FRMFMT_INTERLACED) अणु
		अगर (buf_type == CCDC_BUFTYPE_FLD_INTERLEAVED) अणु
			f->fmt.pix.field = V4L2_FIELD_INTERLACED;
		 पूर्ण अन्यथा अगर (buf_type == CCDC_BUFTYPE_FLD_SEPARATED) अणु
			f->fmt.pix.field = V4L2_FIELD_SEQ_TB;
		पूर्ण अन्यथा अणु
			vpfe_err(vpfe, "Invalid buf_type\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		vpfe_err(vpfe, "Invalid frm_fmt\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_config_ccdc_image_क्रमmat(काष्ठा vpfe_device *vpfe)
अणु
	क्रमागत ccdc_frmfmt frm_fmt = CCDC_FRMFMT_INTERLACED;
	u32 bpp;
	पूर्णांक ret = 0;

	vpfe_dbg(1, vpfe, "pixelformat: %s\n",
		prपूर्णांक_fourcc(vpfe->fmt.fmt.pix.pixelक्रमmat));

	अगर (vpfe_ccdc_set_pixel_क्रमmat(&vpfe->ccdc,
			vpfe->fmt.fmt.pix.pixelक्रमmat) < 0) अणु
		vpfe_err(vpfe, "couldn't set pix format in ccdc\n");
		वापस -EINVAL;
	पूर्ण

	/* configure the image winकरोw */
	bpp = __get_bytesperpixel(vpfe, vpfe->current_vpfe_fmt);
	vpfe_ccdc_set_image_winकरोw(&vpfe->ccdc, &vpfe->crop, bpp);

	चयन (vpfe->fmt.fmt.pix.field) अणु
	हाल V4L2_FIELD_INTERLACED:
		/* करो nothing, since it is शेष */
		ret = vpfe_ccdc_set_buftype(
				&vpfe->ccdc,
				CCDC_BUFTYPE_FLD_INTERLEAVED);
		अवरोध;

	हाल V4L2_FIELD_NONE:
		frm_fmt = CCDC_FRMFMT_PROGRESSIVE;
		/* buffer type only applicable क्रम पूर्णांकerlaced scan */
		अवरोध;

	हाल V4L2_FIELD_SEQ_TB:
		ret = vpfe_ccdc_set_buftype(
				&vpfe->ccdc,
				CCDC_BUFTYPE_FLD_SEPARATED);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	वापस vpfe_ccdc_set_frame_क्रमmat(&vpfe->ccdc, frm_fmt);
पूर्ण

/*
 * vpfe_config_image_क्रमmat()
 * For a given standard, this functions sets up the शेष
 * pix क्रमmat & crop values in the vpfe device and ccdc.  It first
 * starts with शेषs based values from the standard table.
 * It then checks अगर sub device supports get_fmt and then override the
 * values based on that.Sets crop values to match with scan resolution
 * starting at 0,0. It calls vpfe_config_ccdc_image_क्रमmat() set the
 * values in ccdc
 */
अटल पूर्णांक vpfe_config_image_क्रमmat(काष्ठा vpfe_device *vpfe,
				    v4l2_std_id std_id)
अणु
	काष्ठा vpfe_fmt *fmt;
	काष्ठा v4l2_mbus_framefmt mbus_fmt;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(vpfe_standards); i++) अणु
		अगर (vpfe_standards[i].std_id & std_id) अणु
			vpfe->std_info.active_pixels =
					vpfe_standards[i].width;
			vpfe->std_info.active_lines =
					vpfe_standards[i].height;
			vpfe->std_info.frame_क्रमmat =
					vpfe_standards[i].frame_क्रमmat;
			vpfe->std_index = i;

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i ==  ARRAY_SIZE(vpfe_standards)) अणु
		vpfe_err(vpfe, "standard not supported\n");
		वापस -EINVAL;
	पूर्ण

	ret = __subdev_get_क्रमmat(vpfe, &mbus_fmt);
	अगर (ret)
		वापस ret;

	fmt = find_क्रमmat_by_code(vpfe, mbus_fmt.code);
	अगर (!fmt) अणु
		vpfe_dbg(3, vpfe, "mbus code format (0x%08x) not found.\n",
			 mbus_fmt.code);
		वापस -EINVAL;
	पूर्ण

	/* Save current subdev क्रमmat */
	v4l2_fill_pix_क्रमmat(&vpfe->fmt.fmt.pix, &mbus_fmt);
	vpfe->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vpfe->fmt.fmt.pix.pixelक्रमmat = fmt->fourcc;
	vpfe_calc_क्रमmat_size(vpfe, fmt, &vpfe->fmt);
	vpfe->current_vpfe_fmt = fmt;

	/* Update the crop winकरोw based on found values */
	vpfe->crop.top = 0;
	vpfe->crop.left = 0;
	vpfe->crop.width = mbus_fmt.width;
	vpfe->crop.height = mbus_fmt.height;

	वापस vpfe_config_ccdc_image_क्रमmat(vpfe);
पूर्ण

अटल पूर्णांक vpfe_initialize_device(काष्ठा vpfe_device *vpfe)
अणु
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक ret;

	sdinfo = &vpfe->cfg->sub_devs[0];
	sdinfo->sd = vpfe->sd[0];
	vpfe->current_input = 0;
	vpfe->std_index = 0;
	/* Configure the शेष क्रमmat inक्रमmation */
	ret = vpfe_config_image_क्रमmat(vpfe,
				       vpfe_standards[vpfe->std_index].std_id);
	अगर (ret)
		वापस ret;

	pm_runसमय_get_sync(vpfe->pdev);

	vpfe_config_enable(&vpfe->ccdc, 1);

	vpfe_ccdc_restore_शेषs(&vpfe->ccdc);

	/* Clear all VPFE पूर्णांकerrupts */
	vpfe_clear_पूर्णांकr(&vpfe->ccdc, -1);

	वापस ret;
पूर्ण

/*
 * vpfe_release : This function is based on the vb2_fop_release
 * helper function.
 * It has been augmented to handle module घातer management,
 * by disabling/enabling h/w module fcntl घड़ी when necessary.
 */
अटल पूर्णांक vpfe_release(काष्ठा file *file)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	bool fh_singular;
	पूर्णांक ret;

	mutex_lock(&vpfe->lock);

	/* Save the singular status beक्रमe we call the clean-up helper */
	fh_singular = v4l2_fh_is_singular_file(file);

	/* the release helper will cleanup any on-going streaming */
	ret = _vb2_fop_release(file, शून्य);

	/*
	 * If this was the last खोलो file.
	 * Then de-initialize hw module.
	 */
	अगर (fh_singular)
		vpfe_ccdc_बंद(&vpfe->ccdc, vpfe->pdev);

	mutex_unlock(&vpfe->lock);

	वापस ret;
पूर्ण

/*
 * vpfe_खोलो : This function is based on the v4l2_fh_खोलो helper function.
 * It has been augmented to handle module घातer management,
 * by disabling/enabling h/w module fcntl घड़ी when necessary.
 */
अटल पूर्णांक vpfe_खोलो(काष्ठा file *file)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	पूर्णांक ret;

	mutex_lock(&vpfe->lock);

	ret = v4l2_fh_खोलो(file);
	अगर (ret) अणु
		vpfe_err(vpfe, "v4l2_fh_open failed\n");
		जाओ unlock;
	पूर्ण

	अगर (!v4l2_fh_is_singular_file(file))
		जाओ unlock;

	अगर (vpfe_initialize_device(vpfe)) अणु
		v4l2_fh_release(file);
		ret = -ENODEV;
	पूर्ण

unlock:
	mutex_unlock(&vpfe->lock);
	वापस ret;
पूर्ण

/**
 * vpfe_schedule_next_buffer: set next buffer address क्रम capture
 * @vpfe : ptr to vpfe device
 *
 * This function will get next buffer from the dma queue and
 * set the buffer address in the vpfe रेजिस्टर क्रम capture.
 * the buffer is marked active
 */
अटल व्योम vpfe_schedule_next_buffer(काष्ठा vpfe_device *vpfe)
अणु
	dma_addr_t addr;

	spin_lock(&vpfe->dma_queue_lock);
	अगर (list_empty(&vpfe->dma_queue)) अणु
		spin_unlock(&vpfe->dma_queue_lock);
		वापस;
	पूर्ण

	vpfe->next_frm = list_entry(vpfe->dma_queue.next,
				    काष्ठा vpfe_cap_buffer, list);
	list_del(&vpfe->next_frm->list);
	spin_unlock(&vpfe->dma_queue_lock);

	addr = vb2_dma_contig_plane_dma_addr(&vpfe->next_frm->vb.vb2_buf, 0);
	vpfe_set_sdr_addr(&vpfe->ccdc, addr);
पूर्ण

अटल अंतरभूत व्योम vpfe_schedule_bottom_field(काष्ठा vpfe_device *vpfe)
अणु
	dma_addr_t addr;

	addr = vb2_dma_contig_plane_dma_addr(&vpfe->next_frm->vb.vb2_buf, 0) +
					vpfe->field_off;

	vpfe_set_sdr_addr(&vpfe->ccdc, addr);
पूर्ण

/*
 * vpfe_process_buffer_complete: process a completed buffer
 * @vpfe : ptr to vpfe device
 *
 * This function समय stamp the buffer and mark it as DONE. It also
 * wake up any process रुकोing on the QUEUE and set the next buffer
 * as current
 */
अटल अंतरभूत व्योम vpfe_process_buffer_complete(काष्ठा vpfe_device *vpfe)
अणु
	vpfe->cur_frm->vb.vb2_buf.बारtamp = kसमय_get_ns();
	vpfe->cur_frm->vb.field = vpfe->fmt.fmt.pix.field;
	vpfe->cur_frm->vb.sequence = vpfe->sequence++;
	vb2_buffer_करोne(&vpfe->cur_frm->vb.vb2_buf, VB2_BUF_STATE_DONE);
	vpfe->cur_frm = vpfe->next_frm;
पूर्ण

अटल व्योम vpfe_handle_पूर्णांकerlaced_irq(काष्ठा vpfe_device *vpfe,
				       क्रमागत v4l2_field field)
अणु
	पूर्णांक fid;

	/* पूर्णांकerlaced or TB capture check which field
	 * we are in hardware
	 */
	fid = vpfe_ccdc_getfid(&vpfe->ccdc);

	/* चयन the software मुख्यtained field id */
	vpfe->field ^= 1;
	अगर (fid == vpfe->field) अणु
		/* we are in-sync here,जारी */
		अगर (fid == 0) अणु
			/*
			 * One frame is just being captured. If the
			 * next frame is available, release the
			 * current frame and move on
			 */
			अगर (vpfe->cur_frm != vpfe->next_frm)
				vpfe_process_buffer_complete(vpfe);

			अगर (vpfe->stopping)
				वापस;

			/*
			 * based on whether the two fields are stored
			 * पूर्णांकerleave or separately in memory,
			 * reconfigure the CCDC memory address
			 */
			अगर (field == V4L2_FIELD_SEQ_TB)
				vpfe_schedule_bottom_field(vpfe);
		पूर्ण अन्यथा अणु
			/*
			 * अगर one field is just being captured configure
			 * the next frame get the next frame from the empty
			 * queue अगर no frame is available hold on to the
			 * current buffer
			 */
			अगर (vpfe->cur_frm == vpfe->next_frm)
				vpfe_schedule_next_buffer(vpfe);
		पूर्ण
	पूर्ण अन्यथा अगर (fid == 0) अणु
		/*
		 * out of sync. Recover from any hardware out-of-sync.
		 * May loose one frame
		 */
		vpfe->field = fid;
	पूर्ण
पूर्ण

/*
 * vpfe_isr : ISR handler क्रम vpfe capture (VINT0)
 * @irq: irq number
 * @dev_id: dev_id ptr
 *
 * It changes status of the captured buffer, takes next buffer from the queue
 * and sets its address in VPFE रेजिस्टरs
 */
अटल irqवापस_t vpfe_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा vpfe_device *vpfe = (काष्ठा vpfe_device *)dev;
	क्रमागत v4l2_field field = vpfe->fmt.fmt.pix.field;
	पूर्णांक पूर्णांकr_status, stopping = vpfe->stopping;

	पूर्णांकr_status = vpfe_reg_पढ़ो(&vpfe->ccdc, VPFE_IRQ_STS);

	अगर (पूर्णांकr_status & VPFE_VDINT0) अणु
		अगर (field == V4L2_FIELD_NONE) अणु
			अगर (vpfe->cur_frm != vpfe->next_frm)
				vpfe_process_buffer_complete(vpfe);
		पूर्ण अन्यथा अणु
			vpfe_handle_पूर्णांकerlaced_irq(vpfe, field);
		पूर्ण
		अगर (stopping) अणु
			vpfe->stopping = false;
			complete(&vpfe->capture_stop);
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr_status & VPFE_VDINT1 && !stopping) अणु
		अगर (field == V4L2_FIELD_NONE &&
		    vpfe->cur_frm == vpfe->next_frm)
			vpfe_schedule_next_buffer(vpfe);
	पूर्ण

	vpfe_clear_पूर्णांकr(&vpfe->ccdc, पूर्णांकr_status);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम vpfe_detach_irq(काष्ठा vpfe_device *vpfe)
अणु
	अचिन्हित पूर्णांक पूर्णांकr = VPFE_VDINT0;
	क्रमागत ccdc_frmfmt frame_क्रमmat;

	frame_क्रमmat = vpfe_ccdc_get_frame_क्रमmat(&vpfe->ccdc);
	अगर (frame_क्रमmat == CCDC_FRMFMT_PROGRESSIVE)
		पूर्णांकr |= VPFE_VDINT1;

	vpfe_reg_ग_लिखो(&vpfe->ccdc, पूर्णांकr, VPFE_IRQ_EN_CLR);
पूर्ण

अटल अंतरभूत व्योम vpfe_attach_irq(काष्ठा vpfe_device *vpfe)
अणु
	अचिन्हित पूर्णांक पूर्णांकr = VPFE_VDINT0;
	क्रमागत ccdc_frmfmt frame_क्रमmat;

	frame_क्रमmat = vpfe_ccdc_get_frame_क्रमmat(&vpfe->ccdc);
	अगर (frame_क्रमmat == CCDC_FRMFMT_PROGRESSIVE)
		पूर्णांकr |= VPFE_VDINT1;

	vpfe_reg_ग_लिखो(&vpfe->ccdc, पूर्णांकr, VPFE_IRQ_EN_SET);
पूर्ण

अटल पूर्णांक vpfe_querycap(काष्ठा file *file, व्योम  *priv,
			 काष्ठा v4l2_capability *cap)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);

	strscpy(cap->driver, VPFE_MODULE_NAME, माप(cap->driver));
	strscpy(cap->card, "TI AM437x VPFE", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
			"platform:%s", vpfe->v4l2_dev.name);
	वापस 0;
पूर्ण

/* get the क्रमmat set at output pad of the adjacent subdev */
अटल पूर्णांक __subdev_get_क्रमmat(काष्ठा vpfe_device *vpfe,
			       काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	काष्ठा v4l2_subdev *sd = vpfe->current_subdev->sd;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt;
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &sd_fmt.क्रमmat;
	पूर्णांक ret;

	sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	sd_fmt.pad = 0;

	ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य, &sd_fmt);
	अगर (ret)
		वापस ret;

	*fmt = *mbus_fmt;

	vpfe_dbg(1, vpfe, "%s: %dx%d code:%04X\n", __func__,
		 fmt->width, fmt->height, fmt->code);

	वापस 0;
पूर्ण

/* set the क्रमmat at output pad of the adjacent subdev */
अटल पूर्णांक __subdev_set_क्रमmat(काष्ठा vpfe_device *vpfe,
			       काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	काष्ठा v4l2_subdev *sd = vpfe->current_subdev->sd;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt;
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &sd_fmt.क्रमmat;
	पूर्णांक ret;

	sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	sd_fmt.pad = 0;
	*mbus_fmt = *fmt;

	ret = v4l2_subdev_call(sd, pad, set_fmt, शून्य, &sd_fmt);
	अगर (ret)
		वापस ret;

	vpfe_dbg(1, vpfe, "%s %dx%d code:%04X\n", __func__,
		 fmt->width, fmt->height, fmt->code);

	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_calc_क्रमmat_size(काष्ठा vpfe_device *vpfe,
				 स्थिर काष्ठा vpfe_fmt *fmt,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	u32 bpp;

	अगर (!fmt) अणु
		vpfe_dbg(3, vpfe, "No vpfe_fmt provided!\n");
		वापस -EINVAL;
	पूर्ण

	bpp = __get_bytesperpixel(vpfe, fmt);

	/* pitch should be 32 bytes aligned */
	f->fmt.pix.bytesperline = ALIGN(f->fmt.pix.width * bpp, 32);
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
			       f->fmt.pix.height;

	vpfe_dbg(3, vpfe, "%s: fourcc: %s size: %dx%d bpl:%d img_size:%d\n",
		 __func__, prपूर्णांक_fourcc(f->fmt.pix.pixelक्रमmat),
		 f->fmt.pix.width, f->fmt.pix.height,
		 f->fmt.pix.bytesperline, f->fmt.pix.sizeimage);

	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_g_fmt(काष्ठा file *file, व्योम *priv,
		      काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);

	*fmt = vpfe->fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_क्रमागत_fmt(काष्ठा file *file, व्योम  *priv,
			 काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	काष्ठा vpfe_subdev_info *sdinfo;
	काष्ठा vpfe_fmt *fmt;

	sdinfo = vpfe->current_subdev;
	अगर (!sdinfo->sd)
		वापस -EINVAL;

	अगर (f->index >= vpfe->num_active_fmt)
		वापस -EINVAL;

	fmt = vpfe->active_fmt[f->index];

	f->pixelक्रमmat = fmt->fourcc;

	vpfe_dbg(1, vpfe, "%s: mbus index: %d code: %x pixelformat: %s\n",
		 __func__, f->index, fmt->code, prपूर्णांक_fourcc(fmt->fourcc));

	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_try_fmt(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vpfe->current_subdev->sd;
	स्थिर काष्ठा vpfe_fmt *fmt;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse;
	पूर्णांक ret, found;

	fmt = find_क्रमmat_by_pix(vpfe, f->fmt.pix.pixelक्रमmat);
	अगर (!fmt) अणु
		/* शेष to first entry */
		vpfe_dbg(3, vpfe, "Invalid pixel code: %x, default used instead\n",
			 f->fmt.pix.pixelक्रमmat);
		fmt = vpfe->active_fmt[0];
		f->fmt.pix.pixelक्रमmat = fmt->fourcc;
	पूर्ण

	f->fmt.pix.field = vpfe->fmt.fmt.pix.field;

	/* check क्रम/find a valid width/height */
	ret = 0;
	found = false;
	fse.pad = 0;
	fse.code = fmt->code;
	fse.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रम (fse.index = 0; ; fse.index++) अणु
		ret = v4l2_subdev_call(sd, pad, क्रमागत_frame_size,
				       शून्य, &fse);
		अगर (ret)
			अवरोध;

		अगर (f->fmt.pix.width == fse.max_width &&
		    f->fmt.pix.height == fse.max_height) अणु
			found = true;
			अवरोध;
		पूर्ण अन्यथा अगर (f->fmt.pix.width >= fse.min_width &&
			   f->fmt.pix.width <= fse.max_width &&
			   f->fmt.pix.height >= fse.min_height &&
			   f->fmt.pix.height <= fse.max_height) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		/* use existing values as शेष */
		f->fmt.pix.width = vpfe->fmt.fmt.pix.width;
		f->fmt.pix.height =  vpfe->fmt.fmt.pix.height;
	पूर्ण

	/*
	 * Use current colorspace क्रम now, it will get
	 * updated properly during s_fmt
	 */
	f->fmt.pix.colorspace = vpfe->fmt.fmt.pix.colorspace;
	वापस vpfe_calc_क्रमmat_size(vpfe, fmt, f);
पूर्ण

अटल पूर्णांक vpfe_s_fmt(काष्ठा file *file, व्योम *priv,
		      काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	काष्ठा vpfe_fmt *f;
	काष्ठा v4l2_mbus_framefmt mbus_fmt;
	पूर्णांक ret;

	/* If streaming is started, वापस error */
	अगर (vb2_is_busy(&vpfe->buffer_queue)) अणु
		vpfe_err(vpfe, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	ret = vpfe_try_fmt(file, priv, fmt);
	अगर (ret < 0)
		वापस ret;

	f = find_क्रमmat_by_pix(vpfe, fmt->fmt.pix.pixelक्रमmat);

	v4l2_fill_mbus_क्रमmat(&mbus_fmt, &fmt->fmt.pix, f->code);

	ret = __subdev_set_क्रमmat(vpfe, &mbus_fmt);
	अगर (ret)
		वापस ret;

	/* Just द्विगुन check nothing has gone wrong */
	अगर (mbus_fmt.code != f->code) अणु
		vpfe_dbg(3, vpfe,
			 "%s subdev changed format on us, this should not happen\n",
			 __func__);
		वापस -EINVAL;
	पूर्ण

	v4l2_fill_pix_क्रमmat(&vpfe->fmt.fmt.pix, &mbus_fmt);
	vpfe->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vpfe->fmt.fmt.pix.pixelक्रमmat  = f->fourcc;
	vpfe_calc_क्रमmat_size(vpfe, f, &vpfe->fmt);
	*fmt = vpfe->fmt;
	vpfe->current_vpfe_fmt = f;

	/* Update the crop winकरोw based on found values */
	vpfe->crop.width = fmt->fmt.pix.width;
	vpfe->crop.height = fmt->fmt.pix.height;

	/* set image capture parameters in the ccdc */
	वापस vpfe_config_ccdc_image_क्रमmat(vpfe);
पूर्ण

अटल पूर्णांक vpfe_क्रमागत_size(काष्ठा file *file, व्योम  *priv,
			  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse;
	काष्ठा v4l2_subdev *sd = vpfe->current_subdev->sd;
	काष्ठा vpfe_fmt *fmt;
	पूर्णांक ret;

	/* check क्रम valid क्रमmat */
	fmt = find_क्रमmat_by_pix(vpfe, fsize->pixel_क्रमmat);
	अगर (!fmt) अणु
		vpfe_dbg(3, vpfe, "Invalid pixel code: %x\n",
			 fsize->pixel_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	स_रखो(fsize->reserved, 0x0, माप(fsize->reserved));

	स_रखो(&fse, 0x0, माप(fse));
	fse.index = fsize->index;
	fse.pad = 0;
	fse.code = fmt->code;
	fse.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(sd, pad, क्रमागत_frame_size, शून्य, &fse);
	अगर (ret)
		वापस ret;

	vpfe_dbg(1, vpfe, "%s: index: %d code: %x W:[%d,%d] H:[%d,%d]\n",
		 __func__, fse.index, fse.code, fse.min_width, fse.max_width,
		 fse.min_height, fse.max_height);

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = fse.max_width;
	fsize->discrete.height = fse.max_height;

	vpfe_dbg(1, vpfe, "%s: index: %d pixformat: %s size: %dx%d\n",
		 __func__, fsize->index, prपूर्णांक_fourcc(fsize->pixel_क्रमmat),
		 fsize->discrete.width, fsize->discrete.height);

	वापस 0;
पूर्ण

/*
 * vpfe_get_subdev_input_index - Get subdev index and subdev input index क्रम a
 * given app input index
 */
अटल पूर्णांक
vpfe_get_subdev_input_index(काष्ठा vpfe_device *vpfe,
			    पूर्णांक *subdev_index,
			    पूर्णांक *subdev_input_index,
			    पूर्णांक app_input_index)
अणु
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < ARRAY_SIZE(vpfe->cfg->asd); i++) अणु
		अगर (app_input_index < (j + 1)) अणु
			*subdev_index = i;
			*subdev_input_index = app_input_index - j;
			वापस 0;
		पूर्ण
		j++;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * vpfe_get_app_input - Get app input index क्रम a given subdev input index
 * driver stores the input index of the current sub device and translate it
 * when application request the current input
 */
अटल पूर्णांक vpfe_get_app_input_index(काष्ठा vpfe_device *vpfe,
				    पूर्णांक *app_input_index)
अणु
	काष्ठा vpfe_config *cfg = vpfe->cfg;
	काष्ठा vpfe_subdev_info *sdinfo;
	काष्ठा i2c_client *client;
	काष्ठा i2c_client *curr_client;
	पूर्णांक i, j = 0;

	curr_client = v4l2_get_subdevdata(vpfe->current_subdev->sd);
	क्रम (i = 0; i < ARRAY_SIZE(vpfe->cfg->asd); i++) अणु
		sdinfo = &cfg->sub_devs[i];
		client = v4l2_get_subdevdata(sdinfo->sd);
		अगर (client->addr == curr_client->addr &&
		    client->adapter->nr == curr_client->adapter->nr) अणु
			अगर (vpfe->current_input >= 1)
				वापस -1;
			*app_input_index = j + vpfe->current_input;
			वापस 0;
		पूर्ण
		j++;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vpfe_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_input *inp)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक subdev, index;

	अगर (vpfe_get_subdev_input_index(vpfe, &subdev, &index,
					inp->index) < 0) अणु
		vpfe_dbg(1, vpfe,
			"input information not found for the subdev\n");
		वापस -EINVAL;
	पूर्ण
	sdinfo = &vpfe->cfg->sub_devs[subdev];
	*inp = sdinfo->inमाला_दो[index];

	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *index)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);

	वापस vpfe_get_app_input_index(vpfe, index);
पूर्ण

/* Assumes caller is holding vpfe_dev->lock */
अटल पूर्णांक vpfe_set_input(काष्ठा vpfe_device *vpfe, अचिन्हित पूर्णांक index)
अणु
	पूर्णांक subdev_index = 0, inp_index = 0;
	काष्ठा vpfe_subdev_info *sdinfo;
	काष्ठा vpfe_route *route;
	u32 input, output;
	पूर्णांक ret;

	/* If streaming is started, वापस error */
	अगर (vb2_is_busy(&vpfe->buffer_queue)) अणु
		vpfe_err(vpfe, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण
	ret = vpfe_get_subdev_input_index(vpfe,
					  &subdev_index,
					  &inp_index,
					  index);
	अगर (ret < 0) अणु
		vpfe_err(vpfe, "invalid input index: %d\n", index);
		जाओ get_out;
	पूर्ण

	sdinfo = &vpfe->cfg->sub_devs[subdev_index];
	sdinfo->sd = vpfe->sd[subdev_index];
	route = &sdinfo->routes[inp_index];
	अगर (route && sdinfo->can_route) अणु
		input = route->input;
		output = route->output;
		अगर (sdinfo->sd) अणु
			ret = v4l2_subdev_call(sdinfo->sd, video,
					s_routing, input, output, 0);
			अगर (ret) अणु
				vpfe_err(vpfe, "s_routing failed\n");
				ret = -EINVAL;
				जाओ get_out;
			पूर्ण
		पूर्ण

	पूर्ण

	vpfe->current_subdev = sdinfo;
	अगर (sdinfo->sd)
		vpfe->v4l2_dev.ctrl_handler = sdinfo->sd->ctrl_handler;
	vpfe->current_input = index;
	vpfe->std_index = 0;

	/* set the bus/पूर्णांकerface parameter क्रम the sub device in ccdc */
	ret = vpfe_ccdc_set_hw_अगर_params(&vpfe->ccdc, &sdinfo->vpfe_param);
	अगर (ret)
		वापस ret;

	/* set the शेष image parameters in the device */
	वापस vpfe_config_image_क्रमmat(vpfe,
					vpfe_standards[vpfe->std_index].std_id);

get_out:
	वापस ret;
पूर्ण

अटल पूर्णांक vpfe_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक index)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);

	वापस vpfe_set_input(vpfe, index);
पूर्ण

अटल पूर्णांक vpfe_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std_id)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	काष्ठा vpfe_subdev_info *sdinfo;

	sdinfo = vpfe->current_subdev;
	अगर (!(sdinfo->inमाला_दो[0].capabilities & V4L2_IN_CAP_STD))
		वापस -ENODATA;

	/* Call querystd function of decoder device */
	वापस v4l2_device_call_until_err(&vpfe->v4l2_dev, sdinfo->grp_id,
					 video, querystd, std_id);
पूर्ण

अटल पूर्णांक vpfe_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std_id)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक ret;

	sdinfo = vpfe->current_subdev;
	अगर (!(sdinfo->inमाला_दो[0].capabilities & V4L2_IN_CAP_STD))
		वापस -ENODATA;

	/* अगर trying to set the same std then nothing to करो */
	अगर (vpfe_standards[vpfe->std_index].std_id == std_id)
		वापस 0;

	/* If streaming is started, वापस error */
	अगर (vb2_is_busy(&vpfe->buffer_queue)) अणु
		vpfe_err(vpfe, "%s device busy\n", __func__);
		ret = -EBUSY;
		वापस ret;
	पूर्ण

	ret = v4l2_device_call_until_err(&vpfe->v4l2_dev, sdinfo->grp_id,
					 video, s_std, std_id);
	अगर (ret < 0) अणु
		vpfe_err(vpfe, "Failed to set standard\n");
		वापस ret;
	पूर्ण
	ret = vpfe_config_image_क्रमmat(vpfe, std_id);

	वापस ret;
पूर्ण

अटल पूर्णांक vpfe_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std_id)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	काष्ठा vpfe_subdev_info *sdinfo;

	sdinfo = vpfe->current_subdev;
	अगर (sdinfo->inमाला_दो[0].capabilities != V4L2_IN_CAP_STD)
		वापस -ENODATA;

	*std_id = vpfe_standards[vpfe->std_index].std_id;

	वापस 0;
पूर्ण

/*
 * vpfe_calculate_offsets : This function calculates buffers offset
 * क्रम top and bottom field
 */
अटल व्योम vpfe_calculate_offsets(काष्ठा vpfe_device *vpfe)
अणु
	काष्ठा v4l2_rect image_win;

	vpfe_ccdc_get_image_winकरोw(&vpfe->ccdc, &image_win);
	vpfe->field_off = image_win.height * image_win.width;
पूर्ण

/*
 * vpfe_queue_setup - Callback function क्रम buffer setup.
 * @vq: vb2_queue ptr
 * @nbuffers: ptr to number of buffers requested by application
 * @nplanes:: contains number of distinct video planes needed to hold a frame
 * @sizes[]: contains the size (in bytes) of each plane.
 * @alloc_devs: ptr to allocation context
 *
 * This callback function is called when reqbuf() is called to adjust
 * the buffer count and buffer size
 */
अटल पूर्णांक vpfe_queue_setup(काष्ठा vb2_queue *vq,
			    अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			    अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा vpfe_device *vpfe = vb2_get_drv_priv(vq);
	अचिन्हित size = vpfe->fmt.fmt.pix.sizeimage;

	अगर (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	अगर (*nplanes) अणु
		अगर (sizes[0] < size)
			वापस -EINVAL;
		size = sizes[0];
	पूर्ण

	*nplanes = 1;
	sizes[0] = size;

	vpfe_dbg(1, vpfe,
		"nbuffers=%d, size=%u\n", *nbuffers, sizes[0]);

	/* Calculate field offset */
	vpfe_calculate_offsets(vpfe);

	वापस 0;
पूर्ण

/*
 * vpfe_buffer_prepare :  callback function क्रम buffer prepare
 * @vb: ptr to vb2_buffer
 *
 * This is the callback function क्रम buffer prepare when vb2_qbuf()
 * function is called. The buffer is prepared and user space भव address
 * or user address is converted पूर्णांकo  physical address
 */
अटल पूर्णांक vpfe_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vpfe_device *vpfe = vb2_get_drv_priv(vb->vb2_queue);

	vb2_set_plane_payload(vb, 0, vpfe->fmt.fmt.pix.sizeimage);

	अगर (vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0))
		वापस -EINVAL;

	vbuf->field = vpfe->fmt.fmt.pix.field;

	वापस 0;
पूर्ण

/*
 * vpfe_buffer_queue : Callback function to add buffer to DMA queue
 * @vb: ptr to vb2_buffer
 */
अटल व्योम vpfe_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vpfe_device *vpfe = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vpfe_cap_buffer *buf = to_vpfe_buffer(vbuf);
	अचिन्हित दीर्घ flags = 0;

	/* add the buffer to the DMA queue */
	spin_lock_irqsave(&vpfe->dma_queue_lock, flags);
	list_add_tail(&buf->list, &vpfe->dma_queue);
	spin_unlock_irqrestore(&vpfe->dma_queue_lock, flags);
पूर्ण

अटल व्योम vpfe_वापस_all_buffers(काष्ठा vpfe_device *vpfe,
				    क्रमागत vb2_buffer_state state)
अणु
	काष्ठा vpfe_cap_buffer *buf, *node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vpfe->dma_queue_lock, flags);
	list_क्रम_each_entry_safe(buf, node, &vpfe->dma_queue, list) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
		list_del(&buf->list);
	पूर्ण

	अगर (vpfe->cur_frm)
		vb2_buffer_करोne(&vpfe->cur_frm->vb.vb2_buf, state);

	अगर (vpfe->next_frm && vpfe->next_frm != vpfe->cur_frm)
		vb2_buffer_करोne(&vpfe->next_frm->vb.vb2_buf, state);

	vpfe->cur_frm = शून्य;
	vpfe->next_frm = शून्य;
	spin_unlock_irqrestore(&vpfe->dma_queue_lock, flags);
पूर्ण

/*
 * vpfe_start_streaming : Starts the DMA engine क्रम streaming
 * @vb: ptr to vb2_buffer
 * @count: number of buffers
 */
अटल पूर्णांक vpfe_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vpfe_device *vpfe = vb2_get_drv_priv(vq);
	काष्ठा vpfe_subdev_info *sdinfo;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ addr;
	पूर्णांक ret;

	spin_lock_irqsave(&vpfe->dma_queue_lock, flags);

	vpfe->field = 0;
	vpfe->sequence = 0;

	sdinfo = vpfe->current_subdev;

	vpfe_attach_irq(vpfe);

	vpfe->stopping = false;
	init_completion(&vpfe->capture_stop);

	अगर (vpfe->ccdc.ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		vpfe_ccdc_config_raw(&vpfe->ccdc);
	अन्यथा
		vpfe_ccdc_config_ycbcr(&vpfe->ccdc);

	/* Get the next frame from the buffer queue */
	vpfe->next_frm = list_entry(vpfe->dma_queue.next,
				    काष्ठा vpfe_cap_buffer, list);
	vpfe->cur_frm = vpfe->next_frm;
	/* Remove buffer from the buffer queue */
	list_del(&vpfe->cur_frm->list);
	spin_unlock_irqrestore(&vpfe->dma_queue_lock, flags);

	addr = vb2_dma_contig_plane_dma_addr(&vpfe->cur_frm->vb.vb2_buf, 0);

	vpfe_set_sdr_addr(&vpfe->ccdc, (अचिन्हित दीर्घ)(addr));

	vpfe_pcr_enable(&vpfe->ccdc, 1);

	ret = v4l2_subdev_call(sdinfo->sd, video, s_stream, 1);
	अगर (ret < 0) अणु
		vpfe_err(vpfe, "Error in attaching interrupt handle\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	vpfe_वापस_all_buffers(vpfe, VB2_BUF_STATE_QUEUED);
	vpfe_pcr_enable(&vpfe->ccdc, 0);
	वापस ret;
पूर्ण

/*
 * vpfe_stop_streaming : Stop the DMA engine
 * @vq: ptr to vb2_queue
 *
 * This callback stops the DMA engine and any reमुख्यing buffers
 * in the DMA queue are released.
 */
अटल व्योम vpfe_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vpfe_device *vpfe = vb2_get_drv_priv(vq);
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक ret;

	vpfe_pcr_enable(&vpfe->ccdc, 0);

	/* Wait क्रम the last frame to be captured */
	vpfe->stopping = true;
	रुको_क्रम_completion_समयout(&vpfe->capture_stop,
				    msecs_to_jअगरfies(250));

	vpfe_detach_irq(vpfe);

	sdinfo = vpfe->current_subdev;
	ret = v4l2_subdev_call(sdinfo->sd, video, s_stream, 0);
	अगर (ret && ret != -ENOIOCTLCMD && ret != -ENODEV)
		vpfe_dbg(1, vpfe, "stream off failed in subdev\n");

	/* release all active buffers */
	vpfe_वापस_all_buffers(vpfe, VB2_BUF_STATE_ERROR);
पूर्ण

अटल पूर्णांक vpfe_g_pixelaspect(काष्ठा file *file, व्योम *priv,
			      पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    vpfe->std_index >= ARRAY_SIZE(vpfe_standards))
		वापस -EINVAL;

	*f = vpfe_standards[vpfe->std_index].pixelaspect;

	वापस 0;
पूर्ण

अटल पूर्णांक
vpfe_g_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *s)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    vpfe->std_index >= ARRAY_SIZE(vpfe_standards))
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = vpfe_standards[vpfe->std_index].width;
		s->r.height = vpfe_standards[vpfe->std_index].height;
		अवरोध;

	हाल V4L2_SEL_TGT_CROP:
		s->r = vpfe->crop;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vpfe_s_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *s)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	काष्ठा v4l2_rect cr = vpfe->crop;
	काष्ठा v4l2_rect r = s->r;
	u32 bpp;

	/* If streaming is started, वापस error */
	अगर (vb2_is_busy(&vpfe->buffer_queue)) अणु
		vpfe_err(vpfe, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
			s->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	v4l_bound_align_image(&r.width, 0, cr.width, 0,
			      &r.height, 0, cr.height, 0, 0);

	r.left = clamp_t(अचिन्हित पूर्णांक, r.left, 0, cr.width - r.width);
	r.top  = clamp_t(अचिन्हित पूर्णांक, r.top, 0, cr.height - r.height);

	अगर (s->flags & V4L2_SEL_FLAG_LE && !v4l2_rect_enबंदd(&r, &s->r))
		वापस -दुस्फल;

	अगर (s->flags & V4L2_SEL_FLAG_GE && !v4l2_rect_enबंदd(&s->r, &r))
		वापस -दुस्फल;

	s->r = vpfe->crop = r;

	bpp = __get_bytesperpixel(vpfe, vpfe->current_vpfe_fmt);
	vpfe_ccdc_set_image_winकरोw(&vpfe->ccdc, &r, bpp);
	vpfe->fmt.fmt.pix.width = r.width;
	vpfe->fmt.fmt.pix.height = r.height;
	vpfe->fmt.fmt.pix.bytesperline =
		vpfe_ccdc_get_line_length(&vpfe->ccdc);
	vpfe->fmt.fmt.pix.sizeimage = vpfe->fmt.fmt.pix.bytesperline *
						vpfe->fmt.fmt.pix.height;

	vpfe_dbg(1, vpfe, "cropped (%d,%d)/%dx%d of %dx%d\n",
		 r.left, r.top, r.width, r.height, cr.width, cr.height);

	वापस 0;
पूर्ण

अटल दीर्घ vpfe_ioctl_शेष(काष्ठा file *file, व्योम *priv,
			       bool valid_prio, अचिन्हित पूर्णांक cmd, व्योम *param)
अणु
	काष्ठा vpfe_device *vpfe = video_drvdata(file);
	पूर्णांक ret;

	अगर (!valid_prio) अणु
		vpfe_err(vpfe, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	/* If streaming is started, वापस error */
	अगर (vb2_is_busy(&vpfe->buffer_queue)) अणु
		vpfe_err(vpfe, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	चयन (cmd) अणु
	हाल VIDIOC_AM437X_CCDC_CFG:
		ret = vpfe_ccdc_set_params(&vpfe->ccdc, (व्योम __user *)param);
		अगर (ret) अणु
			vpfe_dbg(2, vpfe,
				"Error setting parameters in CCDC\n");
			वापस ret;
		पूर्ण
		ret = vpfe_get_ccdc_image_क्रमmat(vpfe,
						 &vpfe->fmt);
		अगर (ret < 0) अणु
			vpfe_dbg(2, vpfe,
				"Invalid image format at CCDC\n");
			वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vb2_ops vpfe_video_qops = अणु
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.queue_setup		= vpfe_queue_setup,
	.buf_prepare		= vpfe_buffer_prepare,
	.buf_queue		= vpfe_buffer_queue,
	.start_streaming	= vpfe_start_streaming,
	.stop_streaming		= vpfe_stop_streaming,
पूर्ण;

/* vpfe capture driver file operations */
अटल स्थिर काष्ठा v4l2_file_operations vpfe_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= vpfe_खोलो,
	.release	= vpfe_release,
	.पढ़ो		= vb2_fop_पढ़ो,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= vb2_fop_mmap,
पूर्ण;

/* vpfe capture ioctl operations */
अटल स्थिर काष्ठा v4l2_ioctl_ops vpfe_ioctl_ops = अणु
	.vidioc_querycap		= vpfe_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= vpfe_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap		= vpfe_g_fmt,
	.vidioc_s_fmt_vid_cap		= vpfe_s_fmt,
	.vidioc_try_fmt_vid_cap		= vpfe_try_fmt,

	.vidioc_क्रमागत_framesizes		= vpfe_क्रमागत_size,

	.vidioc_क्रमागत_input		= vpfe_क्रमागत_input,
	.vidioc_g_input			= vpfe_g_input,
	.vidioc_s_input			= vpfe_s_input,

	.vidioc_querystd		= vpfe_querystd,
	.vidioc_s_std			= vpfe_s_std,
	.vidioc_g_std			= vpfe_g_std,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,

	.vidioc_g_pixelaspect		= vpfe_g_pixelaspect,
	.vidioc_g_selection		= vpfe_g_selection,
	.vidioc_s_selection		= vpfe_s_selection,

	.vidioc_शेष			= vpfe_ioctl_शेष,
पूर्ण;

अटल पूर्णांक
vpfe_async_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
		 काष्ठा v4l2_subdev *subdev,
		 काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा vpfe_device *vpfe = container_of(notअगरier->v4l2_dev,
					       काष्ठा vpfe_device, v4l2_dev);
	काष्ठा v4l2_subdev_mbus_code_क्रमागत mbus_code;
	काष्ठा vpfe_subdev_info *sdinfo;
	काष्ठा vpfe_fmt *fmt;
	पूर्णांक ret = 0;
	bool found = false;
	पूर्णांक i, j, k;

	क्रम (i = 0; i < ARRAY_SIZE(vpfe->cfg->asd); i++) अणु
		अगर (vpfe->cfg->asd[i]->match.fwnode ==
		    asd[i].match.fwnode) अणु
			sdinfo = &vpfe->cfg->sub_devs[i];
			vpfe->sd[i] = subdev;
			vpfe->sd[i]->grp_id = sdinfo->grp_id;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		vpfe_info(vpfe, "sub device (%s) not matched\n", subdev->name);
		वापस -EINVAL;
	पूर्ण

	vpfe->video_dev.tvnorms |= sdinfo->inमाला_दो[0].std;

	vpfe->num_active_fmt = 0;
	क्रम (j = 0, i = 0; (ret != -EINVAL); ++j) अणु
		स_रखो(&mbus_code, 0, माप(mbus_code));
		mbus_code.index = j;
		mbus_code.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(subdev, pad, क्रमागत_mbus_code,
				       शून्य, &mbus_code);
		अगर (ret)
			जारी;

		vpfe_dbg(3, vpfe,
			 "subdev %s: code: %04x idx: %d\n",
			 subdev->name, mbus_code.code, j);

		क्रम (k = 0; k < ARRAY_SIZE(क्रमmats); k++) अणु
			fmt = &क्रमmats[k];
			अगर (mbus_code.code != fmt->code)
				जारी;
			vpfe->active_fmt[i] = fmt;
			vpfe_dbg(3, vpfe,
				 "matched fourcc: %s code: %04x idx: %d\n",
				 prपूर्णांक_fourcc(fmt->fourcc), mbus_code.code, i);
			vpfe->num_active_fmt = ++i;
		पूर्ण
	पूर्ण

	अगर (!i) अणु
		vpfe_err(vpfe, "No suitable format reported by subdev %s\n",
			 subdev->name);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_probe_complete(काष्ठा vpfe_device *vpfe)
अणु
	काष्ठा video_device *vdev;
	काष्ठा vb2_queue *q;
	पूर्णांक err;

	spin_lock_init(&vpfe->dma_queue_lock);
	mutex_init(&vpfe->lock);

	vpfe->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	/* set first sub device as current one */
	vpfe->current_subdev = &vpfe->cfg->sub_devs[0];
	vpfe->v4l2_dev.ctrl_handler = vpfe->sd[0]->ctrl_handler;

	err = vpfe_set_input(vpfe, 0);
	अगर (err)
		जाओ probe_out;

	/* Initialize videobuf2 queue as per the buffer type */
	q = &vpfe->buffer_queue;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_READ;
	q->drv_priv = vpfe;
	q->ops = &vpfe_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_काष्ठा_size = माप(काष्ठा vpfe_cap_buffer);
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &vpfe->lock;
	q->min_buffers_needed = 1;
	q->dev = vpfe->pdev;

	err = vb2_queue_init(q);
	अगर (err) अणु
		vpfe_err(vpfe, "vb2_queue_init() failed\n");
		जाओ probe_out;
	पूर्ण

	INIT_LIST_HEAD(&vpfe->dma_queue);

	vdev = &vpfe->video_dev;
	strscpy(vdev->name, VPFE_MODULE_NAME, माप(vdev->name));
	vdev->release = video_device_release_empty;
	vdev->fops = &vpfe_fops;
	vdev->ioctl_ops = &vpfe_ioctl_ops;
	vdev->v4l2_dev = &vpfe->v4l2_dev;
	vdev->vfl_dir = VFL_सूची_RX;
	vdev->queue = q;
	vdev->lock = &vpfe->lock;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
			    V4L2_CAP_READWRITE;
	video_set_drvdata(vdev, vpfe);
	err = video_रेजिस्टर_device(&vpfe->video_dev, VFL_TYPE_VIDEO, -1);
	अगर (err) अणु
		vpfe_err(vpfe,
			"Unable to register video device.\n");
		जाओ probe_out;
	पूर्ण

	वापस 0;

probe_out:
	v4l2_device_unरेजिस्टर(&vpfe->v4l2_dev);
	वापस err;
पूर्ण

अटल पूर्णांक vpfe_async_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा vpfe_device *vpfe = container_of(notअगरier->v4l2_dev,
					काष्ठा vpfe_device, v4l2_dev);

	वापस vpfe_probe_complete(vpfe);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations vpfe_async_ops = अणु
	.bound = vpfe_async_bound,
	.complete = vpfe_async_complete,
पूर्ण;

अटल काष्ठा vpfe_config *
vpfe_get_pdata(काष्ठा vpfe_device *vpfe)
अणु
	काष्ठा device_node *endpoपूर्णांक = शून्य;
	काष्ठा device *dev = vpfe->pdev;
	काष्ठा vpfe_subdev_info *sdinfo;
	काष्ठा vpfe_config *pdata;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	dev_dbg(dev, "vpfe_get_pdata\n");

	v4l2_async_notअगरier_init(&vpfe->notअगरier);

	अगर (!IS_ENABLED(CONFIG_OF) || !dev->of_node)
		वापस dev->platक्रमm_data;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	क्रम (i = 0; ; i++) अणु
		काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु .bus_type = 0 पूर्ण;
		काष्ठा device_node *rem;

		endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(dev->of_node, endpoपूर्णांक);
		अगर (!endpoपूर्णांक)
			अवरोध;

		sdinfo = &pdata->sub_devs[i];
		sdinfo->grp_id = 0;

		/* we only support camera */
		sdinfo->inमाला_दो[0].index = i;
		strscpy(sdinfo->inमाला_दो[0].name, "Camera",
			माप(sdinfo->inमाला_दो[0].name));
		sdinfo->inमाला_दो[0].type = V4L2_INPUT_TYPE_CAMERA;
		sdinfo->inमाला_दो[0].std = V4L2_STD_ALL;
		sdinfo->inमाला_दो[0].capabilities = V4L2_IN_CAP_STD;

		sdinfo->can_route = 0;
		sdinfo->routes = शून्य;

		of_property_पढ़ो_u32(endpoपूर्णांक, "ti,am437x-vpfe-interface",
				     &sdinfo->vpfe_param.अगर_type);
		अगर (sdinfo->vpfe_param.अगर_type < 0 ||
			sdinfo->vpfe_param.अगर_type > 4) अणु
			sdinfo->vpfe_param.अगर_type = VPFE_RAW_BAYER;
		पूर्ण

		err = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(endpoपूर्णांक),
						 &bus_cfg);
		अगर (err) अणु
			dev_err(dev, "Could not parse the endpoint\n");
			जाओ cleanup;
		पूर्ण

		sdinfo->vpfe_param.bus_width = bus_cfg.bus.parallel.bus_width;

		अगर (sdinfo->vpfe_param.bus_width < 8 ||
			sdinfo->vpfe_param.bus_width > 16) अणु
			dev_err(dev, "Invalid bus width.\n");
			जाओ cleanup;
		पूर्ण

		flags = bus_cfg.bus.parallel.flags;

		अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
			sdinfo->vpfe_param.hdpol = 1;

		अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
			sdinfo->vpfe_param.vdpol = 1;

		rem = of_graph_get_remote_port_parent(endpoपूर्णांक);
		अगर (!rem) अणु
			dev_err(dev, "Remote device at %pOF not found\n",
				endpoपूर्णांक);
			जाओ cleanup;
		पूर्ण

		pdata->asd[i] = v4l2_async_notअगरier_add_fwnode_subdev(
			&vpfe->notअगरier, of_fwnode_handle(rem),
			काष्ठा v4l2_async_subdev);
		of_node_put(rem);
		अगर (IS_ERR(pdata->asd[i]))
			जाओ cleanup;
	पूर्ण

	of_node_put(endpoपूर्णांक);
	वापस pdata;

cleanup:
	v4l2_async_notअगरier_cleanup(&vpfe->notअगरier);
	of_node_put(endpoपूर्णांक);
	वापस शून्य;
पूर्ण

/*
 * vpfe_probe : This function creates device entries by रेजिस्टर
 * itself to the V4L2 driver and initializes fields of each
 * device objects
 */
अटल पूर्णांक vpfe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpfe_config *vpfe_cfg;
	काष्ठा vpfe_device *vpfe;
	काष्ठा vpfe_ccdc *ccdc;
	काष्ठा resource	*res;
	पूर्णांक ret;

	vpfe = devm_kzalloc(&pdev->dev, माप(*vpfe), GFP_KERNEL);
	अगर (!vpfe)
		वापस -ENOMEM;

	vpfe->pdev = &pdev->dev;

	vpfe_cfg = vpfe_get_pdata(vpfe);
	अगर (!vpfe_cfg) अणु
		dev_err(&pdev->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	vpfe->cfg = vpfe_cfg;
	ccdc = &vpfe->ccdc;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ccdc->ccdc_cfg.base_addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ccdc->ccdc_cfg.base_addr)) अणु
		ret = PTR_ERR(ccdc->ccdc_cfg.base_addr);
		जाओ probe_out_cleanup;
	पूर्ण

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret <= 0) अणु
		ret = -ENODEV;
		जाओ probe_out_cleanup;
	पूर्ण
	vpfe->irq = ret;

	ret = devm_request_irq(vpfe->pdev, vpfe->irq, vpfe_isr, 0,
			       "vpfe_capture0", vpfe);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to request interrupt\n");
		ret = -EINVAL;
		जाओ probe_out_cleanup;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &vpfe->v4l2_dev);
	अगर (ret) अणु
		vpfe_err(vpfe,
			"Unable to register v4l2 device.\n");
		जाओ probe_out_cleanup;
	पूर्ण

	/* set the driver data in platक्रमm device */
	platक्रमm_set_drvdata(pdev, vpfe);
	/* Enabling module functional घड़ी */
	pm_runसमय_enable(&pdev->dev);

	/* क्रम now just enable it here instead of रुकोing क्रम the खोलो */
	pm_runसमय_get_sync(&pdev->dev);

	vpfe_ccdc_config_शेषs(ccdc);

	pm_runसमय_put_sync(&pdev->dev);

	vpfe->sd = devm_kसुस्मृति(&pdev->dev,
				ARRAY_SIZE(vpfe->cfg->asd),
				माप(काष्ठा v4l2_subdev *),
				GFP_KERNEL);
	अगर (!vpfe->sd) अणु
		ret = -ENOMEM;
		जाओ probe_out_v4l2_unरेजिस्टर;
	पूर्ण

	vpfe->notअगरier.ops = &vpfe_async_ops;
	ret = v4l2_async_notअगरier_रेजिस्टर(&vpfe->v4l2_dev, &vpfe->notअगरier);
	अगर (ret) अणु
		vpfe_err(vpfe, "Error registering async notifier\n");
		ret = -EINVAL;
		जाओ probe_out_v4l2_unरेजिस्टर;
	पूर्ण

	वापस 0;

probe_out_v4l2_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&vpfe->v4l2_dev);
probe_out_cleanup:
	v4l2_async_notअगरier_cleanup(&vpfe->notअगरier);
	वापस ret;
पूर्ण

/*
 * vpfe_हटाओ : It un-रेजिस्टर device from V4L2 driver
 */
अटल पूर्णांक vpfe_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpfe_device *vpfe = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	v4l2_async_notअगरier_unरेजिस्टर(&vpfe->notअगरier);
	v4l2_async_notअगरier_cleanup(&vpfe->notअगरier);
	v4l2_device_unरेजिस्टर(&vpfe->v4l2_dev);
	video_unरेजिस्टर_device(&vpfe->video_dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल व्योम vpfe_save_context(काष्ठा vpfe_ccdc *ccdc)
अणु
	ccdc->ccdc_ctx[VPFE_PCR >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_PCR);
	ccdc->ccdc_ctx[VPFE_SYNMODE >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_SYNMODE);
	ccdc->ccdc_ctx[VPFE_SDOFST >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_SDOFST);
	ccdc->ccdc_ctx[VPFE_SDR_ADDR >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_SDR_ADDR);
	ccdc->ccdc_ctx[VPFE_CLAMP >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_CLAMP);
	ccdc->ccdc_ctx[VPFE_DCSUB >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_DCSUB);
	ccdc->ccdc_ctx[VPFE_COLPTN >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_COLPTN);
	ccdc->ccdc_ctx[VPFE_BLKCMP >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_BLKCMP);
	ccdc->ccdc_ctx[VPFE_VDINT >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_VDINT);
	ccdc->ccdc_ctx[VPFE_ALAW >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_ALAW);
	ccdc->ccdc_ctx[VPFE_REC656IF >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_REC656IF);
	ccdc->ccdc_ctx[VPFE_CCDCFG >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_CCDCFG);
	ccdc->ccdc_ctx[VPFE_CULLING >> 2] = vpfe_reg_पढ़ो(ccdc, VPFE_CULLING);
	ccdc->ccdc_ctx[VPFE_HD_VD_WID >> 2] = vpfe_reg_पढ़ो(ccdc,
							    VPFE_HD_VD_WID);
	ccdc->ccdc_ctx[VPFE_PIX_LINES >> 2] = vpfe_reg_पढ़ो(ccdc,
							    VPFE_PIX_LINES);
	ccdc->ccdc_ctx[VPFE_HORZ_INFO >> 2] = vpfe_reg_पढ़ो(ccdc,
							    VPFE_HORZ_INFO);
	ccdc->ccdc_ctx[VPFE_VERT_START >> 2] = vpfe_reg_पढ़ो(ccdc,
							     VPFE_VERT_START);
	ccdc->ccdc_ctx[VPFE_VERT_LINES >> 2] = vpfe_reg_पढ़ो(ccdc,
							     VPFE_VERT_LINES);
	ccdc->ccdc_ctx[VPFE_HSIZE_OFF >> 2] = vpfe_reg_पढ़ो(ccdc,
							    VPFE_HSIZE_OFF);
पूर्ण

अटल पूर्णांक vpfe_suspend(काष्ठा device *dev)
अणु
	काष्ठा vpfe_device *vpfe = dev_get_drvdata(dev);
	काष्ठा vpfe_ccdc *ccdc = &vpfe->ccdc;

	/* only करो full suspend अगर streaming has started */
	अगर (vb2_start_streaming_called(&vpfe->buffer_queue)) अणु
		pm_runसमय_get_sync(dev);
		vpfe_config_enable(ccdc, 1);

		/* Save VPFE context */
		vpfe_save_context(ccdc);

		/* Disable CCDC */
		vpfe_pcr_enable(ccdc, 0);
		vpfe_config_enable(ccdc, 0);

		/* Disable both master and slave घड़ी */
		pm_runसमय_put_sync(dev);
	पूर्ण

	/* Select sleep pin state */
	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल व्योम vpfe_restore_context(काष्ठा vpfe_ccdc *ccdc)
अणु
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_SYNMODE >> 2], VPFE_SYNMODE);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_CULLING >> 2], VPFE_CULLING);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_SDOFST >> 2], VPFE_SDOFST);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_SDR_ADDR >> 2], VPFE_SDR_ADDR);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_CLAMP >> 2], VPFE_CLAMP);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_DCSUB >> 2], VPFE_DCSUB);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_COLPTN >> 2], VPFE_COLPTN);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_BLKCMP >> 2], VPFE_BLKCMP);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_VDINT >> 2], VPFE_VDINT);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_ALAW >> 2], VPFE_ALAW);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_REC656IF >> 2], VPFE_REC656IF);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_CCDCFG >> 2], VPFE_CCDCFG);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_PCR >> 2], VPFE_PCR);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_HD_VD_WID >> 2],
						VPFE_HD_VD_WID);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_PIX_LINES >> 2],
						VPFE_PIX_LINES);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_HORZ_INFO >> 2],
						VPFE_HORZ_INFO);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_VERT_START >> 2],
						VPFE_VERT_START);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_VERT_LINES >> 2],
						VPFE_VERT_LINES);
	vpfe_reg_ग_लिखो(ccdc, ccdc->ccdc_ctx[VPFE_HSIZE_OFF >> 2],
						VPFE_HSIZE_OFF);
पूर्ण

अटल पूर्णांक vpfe_resume(काष्ठा device *dev)
अणु
	काष्ठा vpfe_device *vpfe = dev_get_drvdata(dev);
	काष्ठा vpfe_ccdc *ccdc = &vpfe->ccdc;

	/* only करो full resume अगर streaming has started */
	अगर (vb2_start_streaming_called(&vpfe->buffer_queue)) अणु
		/* Enable both master and slave घड़ी */
		pm_runसमय_get_sync(dev);
		vpfe_config_enable(ccdc, 1);

		/* Restore VPFE context */
		vpfe_restore_context(ccdc);

		vpfe_config_enable(ccdc, 0);
		pm_runसमय_put_sync(dev);
	पूर्ण

	/* Select शेष pin state */
	pinctrl_pm_select_शेष_state(dev);

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(vpfe_pm_ops, vpfe_suspend, vpfe_resume);

अटल स्थिर काष्ठा of_device_id vpfe_of_match[] = अणु
	अणु .compatible = "ti,am437x-vpfe", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vpfe_of_match);

अटल काष्ठा platक्रमm_driver vpfe_driver = अणु
	.probe		= vpfe_probe,
	.हटाओ		= vpfe_हटाओ,
	.driver = अणु
		.name	= VPFE_MODULE_NAME,
		.pm	= &vpfe_pm_ops,
		.of_match_table = of_match_ptr(vpfe_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vpfe_driver);

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("TI AM437x VPFE driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(VPFE_VERSION);
