<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI OMAP4 ISS V4L2 Driver - ISP IPIPEIF module
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
#समावेश "iss_ipipeif.h"

अटल स्थिर अचिन्हित पूर्णांक ipipeअगर_fmts[] = अणु
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SRGGB10_1X10,
	MEDIA_BUS_FMT_SBGGR10_1X10,
	MEDIA_BUS_FMT_SGBRG10_1X10,
	MEDIA_BUS_FMT_UYVY8_1X16,
	MEDIA_BUS_FMT_YUYV8_1X16,
पूर्ण;

/*
 * ipipeअगर_prपूर्णांक_status - Prपूर्णांक current IPIPEIF Module रेजिस्टर values.
 * @ipipeअगर: Poपूर्णांकer to ISS ISP IPIPEIF device.
 *
 * Also prपूर्णांकs other debug inक्रमmation stored in the IPIPEIF module.
 */
#घोषणा IPIPEIF_PRINT_REGISTER(iss, name)\
	dev_dbg(iss->dev, "###IPIPEIF " #name "=0x%08x\n", \
		iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_##name))

#घोषणा ISIF_PRINT_REGISTER(iss, name)\
	dev_dbg(iss->dev, "###ISIF " #name "=0x%08x\n", \
		iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_##name))

#घोषणा ISP5_PRINT_REGISTER(iss, name)\
	dev_dbg(iss->dev, "###ISP5 " #name "=0x%08x\n", \
		iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_##name))

अटल व्योम ipipeअगर_prपूर्णांक_status(काष्ठा iss_ipipeअगर_device *ipipeअगर)
अणु
	काष्ठा iss_device *iss = to_iss_device(ipipeअगर);

	dev_dbg(iss->dev, "-------------IPIPEIF Register dump-------------\n");

	IPIPEIF_PRINT_REGISTER(iss, CFG1);
	IPIPEIF_PRINT_REGISTER(iss, CFG2);

	ISIF_PRINT_REGISTER(iss, SYNCEN);
	ISIF_PRINT_REGISTER(iss, CADU);
	ISIF_PRINT_REGISTER(iss, CADL);
	ISIF_PRINT_REGISTER(iss, MODESET);
	ISIF_PRINT_REGISTER(iss, CCOLP);
	ISIF_PRINT_REGISTER(iss, SPH);
	ISIF_PRINT_REGISTER(iss, LNH);
	ISIF_PRINT_REGISTER(iss, LNV);
	ISIF_PRINT_REGISTER(iss, VDINT(0));
	ISIF_PRINT_REGISTER(iss, HSIZE);

	ISP5_PRINT_REGISTER(iss, SYSCONFIG);
	ISP5_PRINT_REGISTER(iss, CTRL);
	ISP5_PRINT_REGISTER(iss, IRQSTATUS(0));
	ISP5_PRINT_REGISTER(iss, IRQENABLE_SET(0));
	ISP5_PRINT_REGISTER(iss, IRQENABLE_CLR(0));

	dev_dbg(iss->dev, "-----------------------------------------------\n");
पूर्ण

अटल व्योम ipipeअगर_ग_लिखो_enable(काष्ठा iss_ipipeअगर_device *ipipeअगर, u8 enable)
अणु
	काष्ठा iss_device *iss = to_iss_device(ipipeअगर);

	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_SYNCEN,
		       ISIF_SYNCEN_DWEN, enable ? ISIF_SYNCEN_DWEN : 0);
पूर्ण

/*
 * ipipeअगर_enable - Enable/Disable IPIPEIF.
 * @enable: enable flag
 *
 */
अटल व्योम ipipeअगर_enable(काष्ठा iss_ipipeअगर_device *ipipeअगर, u8 enable)
अणु
	काष्ठा iss_device *iss = to_iss_device(ipipeअगर);

	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_SYNCEN,
		       ISIF_SYNCEN_SYEN, enable ? ISIF_SYNCEN_SYEN : 0);
पूर्ण

/* -----------------------------------------------------------------------------
 * Format- and pipeline-related configuration helpers
 */

/*
 * ipipeअगर_set_outaddr - Set memory address to save output image
 * @ipipeअगर: Poपूर्णांकer to ISP IPIPEIF device.
 * @addr: 32-bit memory address aligned on 32 byte boundary.
 *
 * Sets the memory address where the output will be saved.
 */
अटल व्योम ipipeअगर_set_outaddr(काष्ठा iss_ipipeअगर_device *ipipeअगर, u32 addr)
अणु
	काष्ठा iss_device *iss = to_iss_device(ipipeअगर);

	/* Save address split in Base Address H & L */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CADU,
		      (addr >> (16 + 5)) & ISIF_CADU_MASK);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CADL,
		      (addr >> 5) & ISIF_CADL_MASK);
पूर्ण

अटल व्योम ipipeअगर_configure(काष्ठा iss_ipipeअगर_device *ipipeअगर)
अणु
	काष्ठा iss_device *iss = to_iss_device(ipipeअगर);
	स्थिर काष्ठा iss_क्रमmat_info *info;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	u32 isअगर_ccolp = 0;

	omap4iss_configure_bridge(iss, ipipeअगर->input);

	/* IPIPEIF_PAD_SINK */
	क्रमmat = &ipipeअगर->क्रमmats[IPIPEIF_PAD_SINK];

	/* IPIPEIF with YUV422 input from ISIF */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_CFG1,
		    IPIPEIF_CFG1_INPSRC1_MASK | IPIPEIF_CFG1_INPSRC2_MASK);

	/* Select ISIF/IPIPEIF input क्रमmat */
	चयन (क्रमmat->code) अणु
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
		iss_reg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_MODESET,
			       ISIF_MODESET_CCDMD | ISIF_MODESET_INPMOD_MASK |
			       ISIF_MODESET_CCDW_MASK,
			       ISIF_MODESET_INPMOD_YCBCR16);

		iss_reg_update(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_CFG2,
			       IPIPEIF_CFG2_YUV8, IPIPEIF_CFG2_YUV16);

		अवरोध;
	हाल MEDIA_BUS_FMT_SGRBG10_1X10:
		isअगर_ccolp = ISIF_CCOLP_CP0_F0_GR |
			ISIF_CCOLP_CP1_F0_R |
			ISIF_CCOLP_CP2_F0_B |
			ISIF_CCOLP_CP3_F0_GB;
		जाओ cont_raw;
	हाल MEDIA_BUS_FMT_SRGGB10_1X10:
		isअगर_ccolp = ISIF_CCOLP_CP0_F0_R |
			ISIF_CCOLP_CP1_F0_GR |
			ISIF_CCOLP_CP2_F0_GB |
			ISIF_CCOLP_CP3_F0_B;
		जाओ cont_raw;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		isअगर_ccolp = ISIF_CCOLP_CP0_F0_B |
			ISIF_CCOLP_CP1_F0_GB |
			ISIF_CCOLP_CP2_F0_GR |
			ISIF_CCOLP_CP3_F0_R;
		जाओ cont_raw;
	हाल MEDIA_BUS_FMT_SGBRG10_1X10:
		isअगर_ccolp = ISIF_CCOLP_CP0_F0_GB |
			ISIF_CCOLP_CP1_F0_B |
			ISIF_CCOLP_CP2_F0_R |
			ISIF_CCOLP_CP3_F0_GR;
cont_raw:
		iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_CFG2,
			    IPIPEIF_CFG2_YUV16);

		iss_reg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_MODESET,
			       ISIF_MODESET_CCDMD | ISIF_MODESET_INPMOD_MASK |
			       ISIF_MODESET_CCDW_MASK, ISIF_MODESET_INPMOD_RAW |
			       ISIF_MODESET_CCDW_2BIT);

		info = omap4iss_video_क्रमmat_info(क्रमmat->code);
		iss_reg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CGAMMAWD,
			       ISIF_CGAMMAWD_GWDI_MASK,
			       ISIF_CGAMMAWD_GWDI(info->bpp));

		/* Set RAW Bayer pattern */
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CCOLP,
			      isअगर_ccolp);
		अवरोध;
	पूर्ण

	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_SPH, 0 & ISIF_SPH_MASK);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_LNH,
		      (क्रमmat->width - 1) & ISIF_LNH_MASK);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_LNV,
		      (क्रमmat->height - 1) & ISIF_LNV_MASK);

	/* Generate ISIF0 on the last line of the image */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_VDINT(0),
		      क्रमmat->height - 1);

	/* IPIPEIF_PAD_SOURCE_ISIF_SF */
	क्रमmat = &ipipeअगर->क्रमmats[IPIPEIF_PAD_SOURCE_ISIF_SF];

	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_HSIZE,
		      (ipipeअगर->video_out.bpl_value >> 5) &
		      ISIF_HSIZE_HSIZE_MASK);

	/* IPIPEIF_PAD_SOURCE_VP */
	/* Do nothing? */
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt handling
 */

अटल व्योम ipipeअगर_isr_buffer(काष्ठा iss_ipipeअगर_device *ipipeअगर)
अणु
	काष्ठा iss_buffer *buffer;

	/* The ISIF generates VD0 पूर्णांकerrupts even when ग_लिखोs are disabled.
	 * deal with it anyway). Disabling the ISIF when no buffer is available
	 * is thus not be enough, we need to handle the situation explicitly.
	 */
	अगर (list_empty(&ipipeअगर->video_out.dmaqueue))
		वापस;

	ipipeअगर_ग_लिखो_enable(ipipeअगर, 0);

	buffer = omap4iss_video_buffer_next(&ipipeअगर->video_out);
	अगर (!buffer)
		वापस;

	ipipeअगर_set_outaddr(ipipeअगर, buffer->iss_addr);

	ipipeअगर_ग_लिखो_enable(ipipeअगर, 1);
पूर्ण

/*
 * omap4iss_ipipeअगर_isr - Configure ipipeअगर during पूर्णांकerframe समय.
 * @ipipeअगर: Poपूर्णांकer to ISP IPIPEIF device.
 * @events: IPIPEIF events
 */
व्योम omap4iss_ipipeअगर_isr(काष्ठा iss_ipipeअगर_device *ipipeअगर, u32 events)
अणु
	अगर (omap4iss_module_sync_is_stopping(&ipipeअगर->रुको,
					     &ipipeअगर->stopping))
		वापस;

	अगर ((events & ISP5_IRQ_ISIF_INT(0)) &&
	    (ipipeअगर->output & IPIPEIF_OUTPUT_MEMORY))
		ipipeअगर_isr_buffer(ipipeअगर);
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP video operations
 */

अटल पूर्णांक ipipeअगर_video_queue(काष्ठा iss_video *video,
			       काष्ठा iss_buffer *buffer)
अणु
	काष्ठा iss_ipipeअगर_device *ipipeअगर = container_of(video,
				काष्ठा iss_ipipeअगर_device, video_out);

	अगर (!(ipipeअगर->output & IPIPEIF_OUTPUT_MEMORY))
		वापस -ENODEV;

	ipipeअगर_set_outaddr(ipipeअगर, buffer->iss_addr);

	/*
	 * If streaming was enabled beक्रमe there was a buffer queued
	 * or underrun happened in the ISR, the hardware was not enabled
	 * and DMA queue flag ISS_VIDEO_DMAQUEUE_UNDERRUN is still set.
	 * Enable it now.
	 */
	अगर (video->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_UNDERRUN) अणु
		अगर (ipipeअगर->output & IPIPEIF_OUTPUT_MEMORY)
			ipipeअगर_ग_लिखो_enable(ipipeअगर, 1);
		ipipeअगर_enable(ipipeअगर, 1);
		iss_video_dmaqueue_flags_clr(video);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iss_video_operations ipipeअगर_video_ops = अणु
	.queue = ipipeअगर_video_queue,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 */

#घोषणा IPIPEIF_DRV_SUBCLK_MASK	(OMAP4_ISS_ISP_SUBCLK_IPIPEIF |\
				 OMAP4_ISS_ISP_SUBCLK_ISIF)
/*
 * ipipeअगर_set_stream - Enable/Disable streaming on the IPIPEIF module
 * @sd: ISP IPIPEIF V4L2 subdevice
 * @enable: Enable/disable stream
 */
अटल पूर्णांक ipipeअगर_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा iss_ipipeअगर_device *ipipeअगर = v4l2_get_subdevdata(sd);
	काष्ठा iss_device *iss = to_iss_device(ipipeअगर);
	काष्ठा iss_video *video_out = &ipipeअगर->video_out;
	पूर्णांक ret = 0;

	अगर (ipipeअगर->state == ISS_PIPELINE_STREAM_STOPPED) अणु
		अगर (enable == ISS_PIPELINE_STREAM_STOPPED)
			वापस 0;

		omap4iss_isp_subclk_enable(iss, IPIPEIF_DRV_SUBCLK_MASK);
	पूर्ण

	चयन (enable) अणु
	हाल ISS_PIPELINE_STREAM_CONTINUOUS:

		ipipeअगर_configure(ipipeअगर);
		ipipeअगर_prपूर्णांक_status(ipipeअगर);

		/*
		 * When outputting to memory with no buffer available, let the
		 * buffer queue handler start the hardware. A DMA queue flag
		 * ISS_VIDEO_DMAQUEUE_QUEUED will be set as soon as there is
		 * a buffer available.
		 */
		अगर (ipipeअगर->output & IPIPEIF_OUTPUT_MEMORY &&
		    !(video_out->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_QUEUED))
			अवरोध;

		atomic_set(&ipipeअगर->stopping, 0);
		अगर (ipipeअगर->output & IPIPEIF_OUTPUT_MEMORY)
			ipipeअगर_ग_लिखो_enable(ipipeअगर, 1);
		ipipeअगर_enable(ipipeअगर, 1);
		iss_video_dmaqueue_flags_clr(video_out);
		अवरोध;

	हाल ISS_PIPELINE_STREAM_STOPPED:
		अगर (ipipeअगर->state == ISS_PIPELINE_STREAM_STOPPED)
			वापस 0;
		अगर (omap4iss_module_sync_idle(&sd->entity, &ipipeअगर->रुको,
					      &ipipeअगर->stopping))
			ret = -ETIMEDOUT;

		अगर (ipipeअगर->output & IPIPEIF_OUTPUT_MEMORY)
			ipipeअगर_ग_लिखो_enable(ipipeअगर, 0);
		ipipeअगर_enable(ipipeअगर, 0);
		omap4iss_isp_subclk_disable(iss, IPIPEIF_DRV_SUBCLK_MASK);
		iss_video_dmaqueue_flags_clr(video_out);
		अवरोध;
	पूर्ण

	ipipeअगर->state = enable;
	वापस ret;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__ipipeअगर_get_क्रमmat(काष्ठा iss_ipipeअगर_device *ipipeअगर,
		     काष्ठा v4l2_subdev_pad_config *cfg, अचिन्हित पूर्णांक pad,
		     क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&ipipeअगर->subdev, cfg, pad);
	वापस &ipipeअगर->क्रमmats[pad];
पूर्ण

/*
 * ipipeअगर_try_क्रमmat - Try video क्रमmat on a pad
 * @ipipeअगर: ISS IPIPEIF device
 * @cfg: V4L2 subdev pad config
 * @pad: Pad number
 * @fmt: Format
 */
अटल व्योम
ipipeअगर_try_क्रमmat(काष्ठा iss_ipipeअगर_device *ipipeअगर,
		   काष्ठा v4l2_subdev_pad_config *cfg, अचिन्हित पूर्णांक pad,
		   काष्ठा v4l2_mbus_framefmt *fmt,
		   क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक width = fmt->width;
	अचिन्हित पूर्णांक height = fmt->height;
	अचिन्हित पूर्णांक i;

	चयन (pad) अणु
	हाल IPIPEIF_PAD_SINK:
		/* TODO: If the IPIPEIF output क्रमmatter pad is connected
		 * directly to the resizer, only YUV क्रमmats can be used.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(ipipeअगर_fmts); i++) अणु
			अगर (fmt->code == ipipeअगर_fmts[i])
				अवरोध;
		पूर्ण

		/* If not found, use SGRBG10 as शेष */
		अगर (i >= ARRAY_SIZE(ipipeअगर_fmts))
			fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

		/* Clamp the input size. */
		fmt->width = clamp_t(u32, width, 1, 8192);
		fmt->height = clamp_t(u32, height, 1, 8192);
		अवरोध;

	हाल IPIPEIF_PAD_SOURCE_ISIF_SF:
		क्रमmat = __ipipeअगर_get_क्रमmat(ipipeअगर, cfg, IPIPEIF_PAD_SINK,
					      which);
		स_नकल(fmt, क्रमmat, माप(*fmt));

		/* The data क्रमmatter truncates the number of horizontal output
		 * pixels to a multiple of 16. To aव्योम clipping data, allow
		 * callers to request an output size bigger than the input size
		 * up to the nearest multiple of 16.
		 */
		fmt->width = clamp_t(u32, width, 32, (fmt->width + 15) & ~15);
		fmt->width &= ~15;
		fmt->height = clamp_t(u32, height, 32, fmt->height);
		अवरोध;

	हाल IPIPEIF_PAD_SOURCE_VP:
		क्रमmat = __ipipeअगर_get_क्रमmat(ipipeअगर, cfg, IPIPEIF_PAD_SINK,
					      which);
		स_नकल(fmt, क्रमmat, माप(*fmt));

		fmt->width = clamp_t(u32, width, 32, fmt->width);
		fmt->height = clamp_t(u32, height, 32, fmt->height);
		अवरोध;
	पूर्ण

	/* Data is written to memory unpacked, each 10-bit or 12-bit pixel is
	 * stored on 2 bytes.
	 */
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

/*
 * ipipeअगर_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd     : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg    : V4L2 subdev pad config
 * @code   : poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ipipeअगर_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा iss_ipipeअगर_device *ipipeअगर = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	चयन (code->pad) अणु
	हाल IPIPEIF_PAD_SINK:
		अगर (code->index >= ARRAY_SIZE(ipipeअगर_fmts))
			वापस -EINVAL;

		code->code = ipipeअगर_fmts[code->index];
		अवरोध;

	हाल IPIPEIF_PAD_SOURCE_ISIF_SF:
	हाल IPIPEIF_PAD_SOURCE_VP:
		/* No क्रमmat conversion inside IPIPEIF */
		अगर (code->index != 0)
			वापस -EINVAL;

		क्रमmat = __ipipeअगर_get_क्रमmat(ipipeअगर, cfg, IPIPEIF_PAD_SINK,
					      code->which);

		code->code = क्रमmat->code;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipipeअगर_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा iss_ipipeअगर_device *ipipeअगर = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	ipipeअगर_try_क्रमmat(ipipeअगर, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	ipipeअगर_try_क्रमmat(ipipeअगर, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * ipipeअगर_get_क्रमmat - Retrieve the video क्रमmat on a pad
 * @sd : ISP IPIPEIF V4L2 subdevice
 * @cfg: V4L2 subdev pad config
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक ipipeअगर_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा iss_ipipeअगर_device *ipipeअगर = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __ipipeअगर_get_क्रमmat(ipipeअगर, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;
	वापस 0;
पूर्ण

/*
 * ipipeअगर_set_क्रमmat - Set the video क्रमmat on a pad
 * @sd : ISP IPIPEIF V4L2 subdevice
 * @cfg: V4L2 subdev pad config
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक ipipeअगर_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा iss_ipipeअगर_device *ipipeअगर = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __ipipeअगर_get_क्रमmat(ipipeअगर, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	ipipeअगर_try_क्रमmat(ipipeअगर, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == IPIPEIF_PAD_SINK) अणु
		क्रमmat = __ipipeअगर_get_क्रमmat(ipipeअगर, cfg,
					      IPIPEIF_PAD_SOURCE_ISIF_SF,
					      fmt->which);
		*क्रमmat = fmt->क्रमmat;
		ipipeअगर_try_क्रमmat(ipipeअगर, cfg, IPIPEIF_PAD_SOURCE_ISIF_SF,
				   क्रमmat, fmt->which);

		क्रमmat = __ipipeअगर_get_क्रमmat(ipipeअगर, cfg,
					      IPIPEIF_PAD_SOURCE_VP,
					      fmt->which);
		*क्रमmat = fmt->क्रमmat;
		ipipeअगर_try_क्रमmat(ipipeअगर, cfg, IPIPEIF_PAD_SOURCE_VP, क्रमmat,
				   fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipipeअगर_link_validate(काष्ठा v4l2_subdev *sd,
				 काष्ठा media_link *link,
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
 * ipipeअगर_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISP IPIPEIF V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values. If fh is not शून्य, try
 * क्रमmats are initialized on the file handle. Otherwise active क्रमmats are
 * initialized on the device.
 */
अटल पूर्णांक ipipeअगर_init_क्रमmats(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.pad = IPIPEIF_PAD_SINK;
	क्रमmat.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	क्रमmat.क्रमmat.width = 4096;
	क्रमmat.क्रमmat.height = 4096;
	ipipeअगर_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);

	वापस 0;
पूर्ण

/* V4L2 subdev video operations */
अटल स्थिर काष्ठा v4l2_subdev_video_ops ipipeअगर_v4l2_video_ops = अणु
	.s_stream = ipipeअगर_set_stream,
पूर्ण;

/* V4L2 subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops ipipeअगर_v4l2_pad_ops = अणु
	.क्रमागत_mbus_code = ipipeअगर_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ipipeअगर_क्रमागत_frame_size,
	.get_fmt = ipipeअगर_get_क्रमmat,
	.set_fmt = ipipeअगर_set_क्रमmat,
	.link_validate = ipipeअगर_link_validate,
पूर्ण;

/* V4L2 subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops ipipeअगर_v4l2_ops = अणु
	.video = &ipipeअगर_v4l2_video_ops,
	.pad = &ipipeअगर_v4l2_pad_ops,
पूर्ण;

/* V4L2 subdev पूर्णांकernal operations */
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ipipeअगर_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = ipipeअगर_init_क्रमmats,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media entity operations
 */

/*
 * ipipeअगर_link_setup - Setup IPIPEIF connections
 * @entity: IPIPEIF media entity
 * @local: Pad at the local end of the link
 * @remote: Pad at the remote end of the link
 * @flags: Link flags
 *
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ipipeअगर_link_setup(काष्ठा media_entity *entity,
			      स्थिर काष्ठा media_pad *local,
			      स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा iss_ipipeअगर_device *ipipeअगर = v4l2_get_subdevdata(sd);
	काष्ठा iss_device *iss = to_iss_device(ipipeअगर);
	अचिन्हित पूर्णांक index = local->index;

	/* FIXME: this is actually a hack! */
	अगर (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	चयन (index) अणु
	हाल IPIPEIF_PAD_SINK | 2 << 16:
		/* Read from the sensor CSI2a or CSI2b. */
		अगर (!(flags & MEDIA_LNK_FL_ENABLED)) अणु
			ipipeअगर->input = IPIPEIF_INPUT_NONE;
			अवरोध;
		पूर्ण

		अगर (ipipeअगर->input != IPIPEIF_INPUT_NONE)
			वापस -EBUSY;

		अगर (remote->entity == &iss->csi2a.subdev.entity)
			ipipeअगर->input = IPIPEIF_INPUT_CSI2A;
		अन्यथा अगर (remote->entity == &iss->csi2b.subdev.entity)
			ipipeअगर->input = IPIPEIF_INPUT_CSI2B;

		अवरोध;

	हाल IPIPEIF_PAD_SOURCE_ISIF_SF:
		/* Write to memory */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (ipipeअगर->output & ~IPIPEIF_OUTPUT_MEMORY)
				वापस -EBUSY;
			ipipeअगर->output |= IPIPEIF_OUTPUT_MEMORY;
		पूर्ण अन्यथा अणु
			ipipeअगर->output &= ~IPIPEIF_OUTPUT_MEMORY;
		पूर्ण
		अवरोध;

	हाल IPIPEIF_PAD_SOURCE_VP | 2 << 16:
		/* Send to IPIPE/RESIZER */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (ipipeअगर->output & ~IPIPEIF_OUTPUT_VP)
				वापस -EBUSY;
			ipipeअगर->output |= IPIPEIF_OUTPUT_VP;
		पूर्ण अन्यथा अणु
			ipipeअगर->output &= ~IPIPEIF_OUTPUT_VP;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations ipipeअगर_media_ops = अणु
	.link_setup = ipipeअगर_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
 * ipipeअगर_init_entities - Initialize V4L2 subdev and media entity
 * @ipipeअगर: ISS ISP IPIPEIF module
 *
 * Return 0 on success and a negative error code on failure.
 */
अटल पूर्णांक ipipeअगर_init_entities(काष्ठा iss_ipipeअगर_device *ipipeअगर)
अणु
	काष्ठा v4l2_subdev *sd = &ipipeअगर->subdev;
	काष्ठा media_pad *pads = ipipeअगर->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	ipipeअगर->input = IPIPEIF_INPUT_NONE;

	v4l2_subdev_init(sd, &ipipeअगर_v4l2_ops);
	sd->पूर्णांकernal_ops = &ipipeअगर_v4l2_पूर्णांकernal_ops;
	strscpy(sd->name, "OMAP4 ISS ISP IPIPEIF", माप(sd->name));
	sd->grp_id = BIT(16);	/* group ID क्रम iss subdevs */
	v4l2_set_subdevdata(sd, ipipeअगर);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[IPIPEIF_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[IPIPEIF_PAD_SOURCE_ISIF_SF].flags = MEDIA_PAD_FL_SOURCE;
	pads[IPIPEIF_PAD_SOURCE_VP].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &ipipeअगर_media_ops;
	ret = media_entity_pads_init(me, IPIPEIF_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	ipipeअगर_init_क्रमmats(sd, शून्य);

	ipipeअगर->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ipipeअगर->video_out.ops = &ipipeअगर_video_ops;
	ipipeअगर->video_out.iss = to_iss_device(ipipeअगर);
	ipipeअगर->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;
	ipipeअगर->video_out.bpl_alignment = 32;
	ipipeअगर->video_out.bpl_zero_padding = 1;
	ipipeअगर->video_out.bpl_max = 0x1ffe0;

	वापस omap4iss_video_init(&ipipeअगर->video_out, "ISP IPIPEIF");
पूर्ण

व्योम omap4iss_ipipeअगर_unरेजिस्टर_entities(काष्ठा iss_ipipeअगर_device *ipipeअगर)
अणु
	v4l2_device_unरेजिस्टर_subdev(&ipipeअगर->subdev);
	omap4iss_video_unरेजिस्टर(&ipipeअगर->video_out);
पूर्ण

पूर्णांक omap4iss_ipipeअगर_रेजिस्टर_entities(काष्ठा iss_ipipeअगर_device *ipipeअगर,
				       काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video node. */
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &ipipeअगर->subdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap4iss_video_रेजिस्टर(&ipipeअगर->video_out, vdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	omap4iss_ipipeअगर_unरेजिस्टर_entities(ipipeअगर);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP IPIPEIF initialisation and cleanup
 */

/*
 * omap4iss_ipipeअगर_init - IPIPEIF module initialization.
 * @iss: Device poपूर्णांकer specअगरic to the OMAP4 ISS.
 *
 * TODO: Get the initialisation values from platक्रमm data.
 *
 * Return 0 on success or a negative error code otherwise.
 */
पूर्णांक omap4iss_ipipeअगर_init(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_ipipeअगर_device *ipipeअगर = &iss->ipipeअगर;

	ipipeअगर->state = ISS_PIPELINE_STREAM_STOPPED;
	init_रुकोqueue_head(&ipipeअगर->रुको);

	वापस ipipeअगर_init_entities(ipipeअगर);
पूर्ण

/*
 * omap4iss_ipipeअगर_create_links() - IPIPEIF pads links creation
 * @iss: Poपूर्णांकer to ISS device
 *
 * वापस negative error code or zero on success
 */
पूर्णांक omap4iss_ipipeअगर_create_links(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_ipipeअगर_device *ipipeअगर = &iss->ipipeअगर;

	/* Connect the IPIPEIF subdev to the video node. */
	वापस media_create_pad_link(&ipipeअगर->subdev.entity,
				     IPIPEIF_PAD_SOURCE_ISIF_SF,
				     &ipipeअगर->video_out.video.entity, 0, 0);
पूर्ण

/*
 * omap4iss_ipipeअगर_cleanup - IPIPEIF module cleanup.
 * @iss: Device poपूर्णांकer specअगरic to the OMAP4 ISS.
 */
व्योम omap4iss_ipipeअगर_cleanup(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_ipipeअगर_device *ipipeअगर = &iss->ipipeअगर;

	media_entity_cleanup(&ipipeअगर->subdev.entity);
पूर्ण
