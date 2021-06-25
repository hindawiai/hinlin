<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI OMAP4 ISS V4L2 Driver - ISP RESIZER module
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
#समावेश "iss_resizer.h"

अटल स्थिर अचिन्हित पूर्णांक resizer_fmts[] = अणु
	MEDIA_BUS_FMT_UYVY8_1X16,
	MEDIA_BUS_FMT_YUYV8_1X16,
पूर्ण;

/*
 * resizer_prपूर्णांक_status - Prपूर्णांक current RESIZER Module रेजिस्टर values.
 * @resizer: Poपूर्णांकer to ISS ISP RESIZER device.
 *
 * Also prपूर्णांकs other debug inक्रमmation stored in the RESIZER module.
 */
#घोषणा RSZ_PRINT_REGISTER(iss, name)\
	dev_dbg(iss->dev, "###RSZ " #name "=0x%08x\n", \
		iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_##name))

#घोषणा RZA_PRINT_REGISTER(iss, name)\
	dev_dbg(iss->dev, "###RZA " #name "=0x%08x\n", \
		iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_##name))

अटल व्योम resizer_prपूर्णांक_status(काष्ठा iss_resizer_device *resizer)
अणु
	काष्ठा iss_device *iss = to_iss_device(resizer);

	dev_dbg(iss->dev, "-------------RESIZER Register dump-------------\n");

	RSZ_PRINT_REGISTER(iss, SYSCONFIG);
	RSZ_PRINT_REGISTER(iss, IN_FIFO_CTRL);
	RSZ_PRINT_REGISTER(iss, FRACDIV);
	RSZ_PRINT_REGISTER(iss, SRC_EN);
	RSZ_PRINT_REGISTER(iss, SRC_MODE);
	RSZ_PRINT_REGISTER(iss, SRC_FMT0);
	RSZ_PRINT_REGISTER(iss, SRC_FMT1);
	RSZ_PRINT_REGISTER(iss, SRC_VPS);
	RSZ_PRINT_REGISTER(iss, SRC_VSZ);
	RSZ_PRINT_REGISTER(iss, SRC_HPS);
	RSZ_PRINT_REGISTER(iss, SRC_HSZ);
	RSZ_PRINT_REGISTER(iss, DMA_RZA);
	RSZ_PRINT_REGISTER(iss, DMA_RZB);
	RSZ_PRINT_REGISTER(iss, DMA_STA);
	RSZ_PRINT_REGISTER(iss, GCK_MMR);
	RSZ_PRINT_REGISTER(iss, GCK_SDR);
	RSZ_PRINT_REGISTER(iss, IRQ_RZA);
	RSZ_PRINT_REGISTER(iss, IRQ_RZB);
	RSZ_PRINT_REGISTER(iss, YUV_Y_MIN);
	RSZ_PRINT_REGISTER(iss, YUV_Y_MAX);
	RSZ_PRINT_REGISTER(iss, YUV_C_MIN);
	RSZ_PRINT_REGISTER(iss, YUV_C_MAX);
	RSZ_PRINT_REGISTER(iss, SEQ);

	RZA_PRINT_REGISTER(iss, EN);
	RZA_PRINT_REGISTER(iss, MODE);
	RZA_PRINT_REGISTER(iss, 420);
	RZA_PRINT_REGISTER(iss, I_VPS);
	RZA_PRINT_REGISTER(iss, I_HPS);
	RZA_PRINT_REGISTER(iss, O_VSZ);
	RZA_PRINT_REGISTER(iss, O_HSZ);
	RZA_PRINT_REGISTER(iss, V_PHS_Y);
	RZA_PRINT_REGISTER(iss, V_PHS_C);
	RZA_PRINT_REGISTER(iss, V_DIF);
	RZA_PRINT_REGISTER(iss, V_TYP);
	RZA_PRINT_REGISTER(iss, V_LPF);
	RZA_PRINT_REGISTER(iss, H_PHS);
	RZA_PRINT_REGISTER(iss, H_DIF);
	RZA_PRINT_REGISTER(iss, H_TYP);
	RZA_PRINT_REGISTER(iss, H_LPF);
	RZA_PRINT_REGISTER(iss, DWN_EN);
	RZA_PRINT_REGISTER(iss, SDR_Y_BAD_H);
	RZA_PRINT_REGISTER(iss, SDR_Y_BAD_L);
	RZA_PRINT_REGISTER(iss, SDR_Y_SAD_H);
	RZA_PRINT_REGISTER(iss, SDR_Y_SAD_L);
	RZA_PRINT_REGISTER(iss, SDR_Y_OFT);
	RZA_PRINT_REGISTER(iss, SDR_Y_PTR_S);
	RZA_PRINT_REGISTER(iss, SDR_Y_PTR_E);
	RZA_PRINT_REGISTER(iss, SDR_C_BAD_H);
	RZA_PRINT_REGISTER(iss, SDR_C_BAD_L);
	RZA_PRINT_REGISTER(iss, SDR_C_SAD_H);
	RZA_PRINT_REGISTER(iss, SDR_C_SAD_L);
	RZA_PRINT_REGISTER(iss, SDR_C_OFT);
	RZA_PRINT_REGISTER(iss, SDR_C_PTR_S);
	RZA_PRINT_REGISTER(iss, SDR_C_PTR_E);

	dev_dbg(iss->dev, "-----------------------------------------------\n");
पूर्ण

/*
 * resizer_enable - Enable/Disable RESIZER.
 * @enable: enable flag
 *
 */
अटल व्योम resizer_enable(काष्ठा iss_resizer_device *resizer, u8 enable)
अणु
	काष्ठा iss_device *iss = to_iss_device(resizer);

	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_EN,
		       RSZ_SRC_EN_SRC_EN, enable ? RSZ_SRC_EN_SRC_EN : 0);

	/* TODO: Enable RSZB */
	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_EN, RSZ_EN_EN,
		       enable ? RSZ_EN_EN : 0);
पूर्ण

/* -----------------------------------------------------------------------------
 * Format- and pipeline-related configuration helpers
 */

/*
 * resizer_set_outaddr - Set memory address to save output image
 * @resizer: Poपूर्णांकer to ISP RESIZER device.
 * @addr: 32-bit memory address aligned on 32 byte boundary.
 *
 * Sets the memory address where the output will be saved.
 */
अटल व्योम resizer_set_outaddr(काष्ठा iss_resizer_device *resizer, u32 addr)
अणु
	काष्ठा iss_device *iss = to_iss_device(resizer);
	काष्ठा v4l2_mbus_framefmt *inक्रमmat, *outक्रमmat;

	inक्रमmat = &resizer->क्रमmats[RESIZER_PAD_SINK];
	outक्रमmat = &resizer->क्रमmats[RESIZER_PAD_SOURCE_MEM];

	/* Save address split in Base Address H & L */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_BAD_H,
		      (addr >> 16) & 0xffff);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_BAD_L,
		      addr & 0xffff);

	/* SAD = BAD */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_SAD_H,
		      (addr >> 16) & 0xffff);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_SAD_L,
		      addr & 0xffff);

	/* Program UV buffer address... Hardcoded to be contiguous! */
	अगर ((inक्रमmat->code == MEDIA_BUS_FMT_UYVY8_1X16) &&
	    (outक्रमmat->code == MEDIA_BUS_FMT_YUYV8_1_5X8)) अणु
		u32 c_addr = addr + resizer->video_out.bpl_value
			   * outक्रमmat->height;

		/* Ensure Y_BAD_L[6:0] = C_BAD_L[6:0]*/
		अगर ((c_addr ^ addr) & 0x7f) अणु
			c_addr &= ~0x7f;
			c_addr += 0x80;
			c_addr |= addr & 0x7f;
		पूर्ण

		/* Save address split in Base Address H & L */
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_BAD_H,
			      (c_addr >> 16) & 0xffff);
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_BAD_L,
			      c_addr & 0xffff);

		/* SAD = BAD */
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_SAD_H,
			      (c_addr >> 16) & 0xffff);
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_SAD_L,
			      c_addr & 0xffff);
	पूर्ण
पूर्ण

अटल व्योम resizer_configure(काष्ठा iss_resizer_device *resizer)
अणु
	काष्ठा iss_device *iss = to_iss_device(resizer);
	काष्ठा v4l2_mbus_framefmt *inक्रमmat, *outक्रमmat;

	inक्रमmat = &resizer->क्रमmats[RESIZER_PAD_SINK];
	outक्रमmat = &resizer->क्रमmats[RESIZER_PAD_SOURCE_MEM];

	/* Disable pass-through more. Despite its name, the BYPASS bit controls
	 * pass-through mode, not bypass mode.
	 */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_FMT0,
		    RSZ_SRC_FMT0_BYPASS);

	/* Select RSZ input */
	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_FMT0,
		       RSZ_SRC_FMT0_SEL,
		       resizer->input == RESIZER_INPUT_IPIPEIF ?
		       RSZ_SRC_FMT0_SEL : 0);

	/* RSZ ignores WEN संकेत from IPIPE/IPIPEIF */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_MODE,
		    RSZ_SRC_MODE_WRT);

	/* Set Resizer in मुक्त-running mode */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_MODE,
		    RSZ_SRC_MODE_OST);

	/* Init Resizer A */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_MODE,
		    RZA_MODE_ONE_SHOT);

	/* Set size related things now */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_VPS, 0);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_HPS, 0);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_VSZ,
		      inक्रमmat->height - 2);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_HSZ,
		      inक्रमmat->width - 1);

	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_I_VPS, 0);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_I_HPS, 0);

	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_O_VSZ,
		      outक्रमmat->height - 2);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_O_HSZ,
		      outक्रमmat->width - 1);

	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_V_DIF, 0x100);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_H_DIF, 0x100);

	/* Buffer output settings */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_PTR_S, 0);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_PTR_E,
		      outक्रमmat->height - 1);

	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_OFT,
		      resizer->video_out.bpl_value);

	/* UYVY -> NV12 conversion */
	अगर ((inक्रमmat->code == MEDIA_BUS_FMT_UYVY8_1X16) &&
	    (outक्रमmat->code == MEDIA_BUS_FMT_YUYV8_1_5X8)) अणु
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_420,
			      RSZ_420_CEN | RSZ_420_YEN);

		/* UV Buffer output settings */
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_PTR_S,
			      0);
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_PTR_E,
			      outक्रमmat->height - 1);

		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_OFT,
			      resizer->video_out.bpl_value);
	पूर्ण अन्यथा अणु
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_420, 0);
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt handling
 */

अटल व्योम resizer_isr_buffer(काष्ठा iss_resizer_device *resizer)
अणु
	काष्ठा iss_buffer *buffer;

	/* The whole resizer needs to be stopped. Disabling RZA only produces
	 * input FIFO overflows, most probably when the next frame is received.
	 */
	resizer_enable(resizer, 0);

	buffer = omap4iss_video_buffer_next(&resizer->video_out);
	अगर (!buffer)
		वापस;

	resizer_set_outaddr(resizer, buffer->iss_addr);

	resizer_enable(resizer, 1);
पूर्ण

/*
 * omap4iss_resizer_isr - Configure resizer during पूर्णांकerframe समय.
 * @resizer: Poपूर्णांकer to ISP RESIZER device.
 * @events: RESIZER events
 */
व्योम omap4iss_resizer_isr(काष्ठा iss_resizer_device *resizer, u32 events)
अणु
	काष्ठा iss_device *iss = to_iss_device(resizer);
	काष्ठा iss_pipeline *pipe =
			     to_iss_pipeline(&resizer->subdev.entity);

	अगर (events & (ISP5_IRQ_RSZ_FIFO_IN_BLK_ERR |
		      ISP5_IRQ_RSZ_FIFO_OVF)) अणु
		dev_dbg(iss->dev, "RSZ Err: FIFO_IN_BLK:%d, FIFO_OVF:%d\n",
			events & ISP5_IRQ_RSZ_FIFO_IN_BLK_ERR ? 1 : 0,
			events & ISP5_IRQ_RSZ_FIFO_OVF ? 1 : 0);
		omap4iss_pipeline_cancel_stream(pipe);
	पूर्ण

	अगर (omap4iss_module_sync_is_stopping(&resizer->रुको,
					     &resizer->stopping))
		वापस;

	अगर (events & ISP5_IRQ_RSZ_INT_DMA)
		resizer_isr_buffer(resizer);
पूर्ण

/* -----------------------------------------------------------------------------
 * ISS video operations
 */

अटल पूर्णांक resizer_video_queue(काष्ठा iss_video *video,
			       काष्ठा iss_buffer *buffer)
अणु
	काष्ठा iss_resizer_device *resizer = container_of(video,
				काष्ठा iss_resizer_device, video_out);

	अगर (!(resizer->output & RESIZER_OUTPUT_MEMORY))
		वापस -ENODEV;

	resizer_set_outaddr(resizer, buffer->iss_addr);

	/*
	 * If streaming was enabled beक्रमe there was a buffer queued
	 * or underrun happened in the ISR, the hardware was not enabled
	 * and DMA queue flag ISS_VIDEO_DMAQUEUE_UNDERRUN is still set.
	 * Enable it now.
	 */
	अगर (video->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_UNDERRUN) अणु
		resizer_enable(resizer, 1);
		iss_video_dmaqueue_flags_clr(video);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iss_video_operations resizer_video_ops = अणु
	.queue = resizer_video_queue,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 */

/*
 * resizer_set_stream - Enable/Disable streaming on the RESIZER module
 * @sd: ISP RESIZER V4L2 subdevice
 * @enable: Enable/disable stream
 */
अटल पूर्णांक resizer_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा iss_resizer_device *resizer = v4l2_get_subdevdata(sd);
	काष्ठा iss_device *iss = to_iss_device(resizer);
	काष्ठा iss_video *video_out = &resizer->video_out;
	पूर्णांक ret = 0;

	अगर (resizer->state == ISS_PIPELINE_STREAM_STOPPED) अणु
		अगर (enable == ISS_PIPELINE_STREAM_STOPPED)
			वापस 0;

		omap4iss_isp_subclk_enable(iss, OMAP4_ISS_ISP_SUBCLK_RSZ);

		iss_reg_set(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_GCK_MMR,
			    RSZ_GCK_MMR_MMR);
		iss_reg_set(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_GCK_SDR,
			    RSZ_GCK_SDR_CORE);

		/* FIXME: Enable RSZB also */
		iss_reg_set(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SYSCONFIG,
			    RSZ_SYSCONFIG_RSZA_CLK_EN);
	पूर्ण

	चयन (enable) अणु
	हाल ISS_PIPELINE_STREAM_CONTINUOUS:

		resizer_configure(resizer);
		resizer_prपूर्णांक_status(resizer);

		/*
		 * When outputting to memory with no buffer available, let the
		 * buffer queue handler start the hardware. A DMA queue flag
		 * ISS_VIDEO_DMAQUEUE_QUEUED will be set as soon as there is
		 * a buffer available.
		 */
		अगर (resizer->output & RESIZER_OUTPUT_MEMORY &&
		    !(video_out->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_QUEUED))
			अवरोध;

		atomic_set(&resizer->stopping, 0);
		resizer_enable(resizer, 1);
		iss_video_dmaqueue_flags_clr(video_out);
		अवरोध;

	हाल ISS_PIPELINE_STREAM_STOPPED:
		अगर (resizer->state == ISS_PIPELINE_STREAM_STOPPED)
			वापस 0;
		अगर (omap4iss_module_sync_idle(&sd->entity, &resizer->रुको,
					      &resizer->stopping))
			ret = -ETIMEDOUT;

		resizer_enable(resizer, 0);
		iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SYSCONFIG,
			    RSZ_SYSCONFIG_RSZA_CLK_EN);
		iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_GCK_SDR,
			    RSZ_GCK_SDR_CORE);
		iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_GCK_MMR,
			    RSZ_GCK_MMR_MMR);
		omap4iss_isp_subclk_disable(iss, OMAP4_ISS_ISP_SUBCLK_RSZ);
		iss_video_dmaqueue_flags_clr(video_out);
		अवरोध;
	पूर्ण

	resizer->state = enable;
	वापस ret;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__resizer_get_क्रमmat(काष्ठा iss_resizer_device *resizer,
		     काष्ठा v4l2_subdev_pad_config *cfg, अचिन्हित पूर्णांक pad,
		     क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&resizer->subdev, cfg, pad);
	वापस &resizer->क्रमmats[pad];
पूर्ण

/*
 * resizer_try_क्रमmat - Try video क्रमmat on a pad
 * @resizer: ISS RESIZER device
 * @cfg: V4L2 subdev pad config
 * @pad: Pad number
 * @fmt: Format
 */
अटल व्योम
resizer_try_क्रमmat(काष्ठा iss_resizer_device *resizer,
		   काष्ठा v4l2_subdev_pad_config *cfg, अचिन्हित पूर्णांक pad,
		   काष्ठा v4l2_mbus_framefmt *fmt,
		   क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	u32 pixelcode;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक width = fmt->width;
	अचिन्हित पूर्णांक height = fmt->height;
	अचिन्हित पूर्णांक i;

	चयन (pad) अणु
	हाल RESIZER_PAD_SINK:
		क्रम (i = 0; i < ARRAY_SIZE(resizer_fmts); i++) अणु
			अगर (fmt->code == resizer_fmts[i])
				अवरोध;
		पूर्ण

		/* If not found, use UYVY as शेष */
		अगर (i >= ARRAY_SIZE(resizer_fmts))
			fmt->code = MEDIA_BUS_FMT_UYVY8_1X16;

		/* Clamp the input size. */
		fmt->width = clamp_t(u32, width, 1, 8192);
		fmt->height = clamp_t(u32, height, 1, 8192);
		अवरोध;

	हाल RESIZER_PAD_SOURCE_MEM:
		pixelcode = fmt->code;
		क्रमmat = __resizer_get_क्रमmat(resizer, cfg, RESIZER_PAD_SINK,
					      which);
		स_नकल(fmt, क्रमmat, माप(*fmt));

		अगर ((pixelcode == MEDIA_BUS_FMT_YUYV8_1_5X8) &&
		    (fmt->code == MEDIA_BUS_FMT_UYVY8_1X16))
			fmt->code = pixelcode;

		/* The data क्रमmatter truncates the number of horizontal output
		 * pixels to a multiple of 16. To aव्योम clipping data, allow
		 * callers to request an output size bigger than the input size
		 * up to the nearest multiple of 16.
		 */
		fmt->width = clamp_t(u32, width, 32, (fmt->width + 15) & ~15);
		fmt->width &= ~15;
		fmt->height = clamp_t(u32, height, 32, fmt->height);
		अवरोध;
	पूर्ण

	fmt->colorspace = V4L2_COLORSPACE_JPEG;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

/*
 * resizer_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd     : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad config
 * @code   : poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक resizer_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा iss_resizer_device *resizer = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	चयन (code->pad) अणु
	हाल RESIZER_PAD_SINK:
		अगर (code->index >= ARRAY_SIZE(resizer_fmts))
			वापस -EINVAL;

		code->code = resizer_fmts[code->index];
		अवरोध;

	हाल RESIZER_PAD_SOURCE_MEM:
		क्रमmat = __resizer_get_क्रमmat(resizer, cfg, RESIZER_PAD_SINK,
					      code->which);

		अगर (code->index == 0) अणु
			code->code = क्रमmat->code;
			अवरोध;
		पूर्ण

		चयन (क्रमmat->code) अणु
		हाल MEDIA_BUS_FMT_UYVY8_1X16:
			अगर (code->index == 1)
				code->code = MEDIA_BUS_FMT_YUYV8_1_5X8;
			अन्यथा
				वापस -EINVAL;
			अवरोध;
		शेष:
			अगर (code->index != 0)
				वापस -EINVAL;
		पूर्ण

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक resizer_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा iss_resizer_device *resizer = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	resizer_try_क्रमmat(resizer, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	resizer_try_क्रमmat(resizer, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * resizer_get_क्रमmat - Retrieve the video क्रमmat on a pad
 * @sd : ISP RESIZER V4L2 subdevice
 * @cfg: V4L2 subdev pad config
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक resizer_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा iss_resizer_device *resizer = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __resizer_get_क्रमmat(resizer, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;
	वापस 0;
पूर्ण

/*
 * resizer_set_क्रमmat - Set the video क्रमmat on a pad
 * @sd : ISP RESIZER V4L2 subdevice
 * @cfg: V4L2 subdev pad config
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक resizer_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा iss_resizer_device *resizer = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __resizer_get_क्रमmat(resizer, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	resizer_try_क्रमmat(resizer, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == RESIZER_PAD_SINK) अणु
		क्रमmat = __resizer_get_क्रमmat(resizer, cfg,
					      RESIZER_PAD_SOURCE_MEM,
					      fmt->which);
		*क्रमmat = fmt->क्रमmat;
		resizer_try_क्रमmat(resizer, cfg, RESIZER_PAD_SOURCE_MEM, क्रमmat,
				   fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक resizer_link_validate(काष्ठा v4l2_subdev *sd,
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
 * resizer_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISP RESIZER V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values. If fh is not शून्य, try
 * क्रमmats are initialized on the file handle. Otherwise active क्रमmats are
 * initialized on the device.
 */
अटल पूर्णांक resizer_init_क्रमmats(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.pad = RESIZER_PAD_SINK;
	क्रमmat.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_UYVY8_1X16;
	क्रमmat.क्रमmat.width = 4096;
	क्रमmat.क्रमmat.height = 4096;
	resizer_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);

	वापस 0;
पूर्ण

/* V4L2 subdev video operations */
अटल स्थिर काष्ठा v4l2_subdev_video_ops resizer_v4l2_video_ops = अणु
	.s_stream = resizer_set_stream,
पूर्ण;

/* V4L2 subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops resizer_v4l2_pad_ops = अणु
	.क्रमागत_mbus_code = resizer_क्रमागत_mbus_code,
	.क्रमागत_frame_size = resizer_क्रमागत_frame_size,
	.get_fmt = resizer_get_क्रमmat,
	.set_fmt = resizer_set_क्रमmat,
	.link_validate = resizer_link_validate,
पूर्ण;

/* V4L2 subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops resizer_v4l2_ops = अणु
	.video = &resizer_v4l2_video_ops,
	.pad = &resizer_v4l2_pad_ops,
पूर्ण;

/* V4L2 subdev पूर्णांकernal operations */
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops resizer_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = resizer_init_क्रमmats,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media entity operations
 */

/*
 * resizer_link_setup - Setup RESIZER connections
 * @entity: RESIZER media entity
 * @local: Pad at the local end of the link
 * @remote: Pad at the remote end of the link
 * @flags: Link flags
 *
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक resizer_link_setup(काष्ठा media_entity *entity,
			      स्थिर काष्ठा media_pad *local,
			      स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा iss_resizer_device *resizer = v4l2_get_subdevdata(sd);
	काष्ठा iss_device *iss = to_iss_device(resizer);
	अचिन्हित पूर्णांक index = local->index;

	/* FIXME: this is actually a hack! */
	अगर (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	चयन (index) अणु
	हाल RESIZER_PAD_SINK | 2 << 16:
		/* Read from IPIPE or IPIPEIF. */
		अगर (!(flags & MEDIA_LNK_FL_ENABLED)) अणु
			resizer->input = RESIZER_INPUT_NONE;
			अवरोध;
		पूर्ण

		अगर (resizer->input != RESIZER_INPUT_NONE)
			वापस -EBUSY;

		अगर (remote->entity == &iss->ipipeअगर.subdev.entity)
			resizer->input = RESIZER_INPUT_IPIPEIF;
		अन्यथा अगर (remote->entity == &iss->ipipe.subdev.entity)
			resizer->input = RESIZER_INPUT_IPIPE;

		अवरोध;

	हाल RESIZER_PAD_SOURCE_MEM:
		/* Write to memory */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (resizer->output & ~RESIZER_OUTPUT_MEMORY)
				वापस -EBUSY;
			resizer->output |= RESIZER_OUTPUT_MEMORY;
		पूर्ण अन्यथा अणु
			resizer->output &= ~RESIZER_OUTPUT_MEMORY;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations resizer_media_ops = अणु
	.link_setup = resizer_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
 * resizer_init_entities - Initialize V4L2 subdev and media entity
 * @resizer: ISS ISP RESIZER module
 *
 * Return 0 on success and a negative error code on failure.
 */
अटल पूर्णांक resizer_init_entities(काष्ठा iss_resizer_device *resizer)
अणु
	काष्ठा v4l2_subdev *sd = &resizer->subdev;
	काष्ठा media_pad *pads = resizer->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	resizer->input = RESIZER_INPUT_NONE;

	v4l2_subdev_init(sd, &resizer_v4l2_ops);
	sd->पूर्णांकernal_ops = &resizer_v4l2_पूर्णांकernal_ops;
	strscpy(sd->name, "OMAP4 ISS ISP resizer", माप(sd->name));
	sd->grp_id = BIT(16);	/* group ID क्रम iss subdevs */
	v4l2_set_subdevdata(sd, resizer);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[RESIZER_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[RESIZER_PAD_SOURCE_MEM].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &resizer_media_ops;
	ret = media_entity_pads_init(me, RESIZER_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	resizer_init_क्रमmats(sd, शून्य);

	resizer->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	resizer->video_out.ops = &resizer_video_ops;
	resizer->video_out.iss = to_iss_device(resizer);
	resizer->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;
	resizer->video_out.bpl_alignment = 32;
	resizer->video_out.bpl_zero_padding = 1;
	resizer->video_out.bpl_max = 0x1ffe0;

	वापस omap4iss_video_init(&resizer->video_out, "ISP resizer a");
पूर्ण

व्योम omap4iss_resizer_unरेजिस्टर_entities(काष्ठा iss_resizer_device *resizer)
अणु
	v4l2_device_unरेजिस्टर_subdev(&resizer->subdev);
	omap4iss_video_unरेजिस्टर(&resizer->video_out);
पूर्ण

पूर्णांक omap4iss_resizer_रेजिस्टर_entities(काष्ठा iss_resizer_device *resizer,
				       काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video node. */
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &resizer->subdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap4iss_video_रेजिस्टर(&resizer->video_out, vdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	omap4iss_resizer_unरेजिस्टर_entities(resizer);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP RESIZER initialisation and cleanup
 */

/*
 * omap4iss_resizer_init - RESIZER module initialization.
 * @iss: Device poपूर्णांकer specअगरic to the OMAP4 ISS.
 *
 * TODO: Get the initialisation values from platक्रमm data.
 *
 * Return 0 on success or a negative error code otherwise.
 */
पूर्णांक omap4iss_resizer_init(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_resizer_device *resizer = &iss->resizer;

	resizer->state = ISS_PIPELINE_STREAM_STOPPED;
	init_रुकोqueue_head(&resizer->रुको);

	वापस resizer_init_entities(resizer);
पूर्ण

/*
 * omap4iss_resizer_create_links() - RESIZER pads links creation
 * @iss: Poपूर्णांकer to ISS device
 *
 * वापस negative error code or zero on success
 */
पूर्णांक omap4iss_resizer_create_links(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_resizer_device *resizer = &iss->resizer;

	/* Connect the RESIZER subdev to the video node. */
	वापस media_create_pad_link(&resizer->subdev.entity,
				     RESIZER_PAD_SOURCE_MEM,
				     &resizer->video_out.video.entity, 0, 0);
पूर्ण

/*
 * omap4iss_resizer_cleanup - RESIZER module cleanup.
 * @iss: Device poपूर्णांकer specअगरic to the OMAP4 ISS.
 */
व्योम omap4iss_resizer_cleanup(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_resizer_device *resizer = &iss->resizer;

	media_entity_cleanup(&resizer->subdev.entity);
पूर्ण
