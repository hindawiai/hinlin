<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * V4L2 Driver क्रम Renesas Capture Engine Unit (CEU) पूर्णांकerface
 * Copyright (C) 2017-2018 Jacopo Mondi <jacopo+renesas@jmondi.org>
 *
 * Based on soc-camera driver "soc_camera/sh_mobile_ceu_camera.c"
 * Copyright (C) 2008 Magnus Damm
 *
 * Based on V4L2 Driver क्रम PXA camera host - "pxa_camera.c",
 * Copyright (C) 2006, Sascha Hauer, Pengutronix
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश <media/drv-पूर्णांकf/renesas-ceu.h>

#घोषणा DRIVER_NAME	"renesas-ceu"

/* CEU रेजिस्टरs offsets and masks. */
#घोषणा CEU_CAPSR	0x00 /* Capture start रेजिस्टर			*/
#घोषणा CEU_CAPCR	0x04 /* Capture control रेजिस्टर		*/
#घोषणा CEU_CAMCR	0x08 /* Capture पूर्णांकerface control रेजिस्टर	*/
#घोषणा CEU_CAMOR	0x10 /* Capture पूर्णांकerface offset रेजिस्टर	*/
#घोषणा CEU_CAPWR	0x14 /* Capture पूर्णांकerface width रेजिस्टर	*/
#घोषणा CEU_CAIFR	0x18 /* Capture पूर्णांकerface input क्रमmat रेजिस्टर */
#घोषणा CEU_CRCNTR	0x28 /* CEU रेजिस्टर control रेजिस्टर		*/
#घोषणा CEU_CRCMPR	0x2c /* CEU रेजिस्टर क्रमcible control रेजिस्टर	*/
#घोषणा CEU_CFLCR	0x30 /* Capture filter control रेजिस्टर		*/
#घोषणा CEU_CFSZR	0x34 /* Capture filter size clip रेजिस्टर	*/
#घोषणा CEU_CDWDR	0x38 /* Capture destination width रेजिस्टर	*/
#घोषणा CEU_CDAYR	0x3c /* Capture data address Y रेजिस्टर		*/
#घोषणा CEU_CDACR	0x40 /* Capture data address C रेजिस्टर		*/
#घोषणा CEU_CFWCR	0x5c /* Firewall operation control रेजिस्टर	*/
#घोषणा CEU_CDOCR	0x64 /* Capture data output control रेजिस्टर	*/
#घोषणा CEU_CEIER	0x70 /* Capture event पूर्णांकerrupt enable रेजिस्टर	*/
#घोषणा CEU_CETCR	0x74 /* Capture event flag clear रेजिस्टर	*/
#घोषणा CEU_CSTSR	0x7c /* Capture status रेजिस्टर			*/
#घोषणा CEU_CSRTR	0x80 /* Capture software reset रेजिस्टर		*/

/* Data synchronous fetch mode. */
#घोषणा CEU_CAMCR_JPEG			BIT(4)

/* Input components ordering: CEU_CAMCR.DTARY field. */
#घोषणा CEU_CAMCR_DTARY_8_UYVY		(0x00 << 8)
#घोषणा CEU_CAMCR_DTARY_8_VYUY		(0x01 << 8)
#घोषणा CEU_CAMCR_DTARY_8_YUYV		(0x02 << 8)
#घोषणा CEU_CAMCR_DTARY_8_YVYU		(0x03 << 8)
/* TODO: input components ordering क्रम 16 bits input. */

/* Bus transfer MTU. */
#घोषणा CEU_CAPCR_BUS_WIDTH256		(0x3 << 20)

/* Bus width configuration. */
#घोषणा CEU_CAMCR_DTIF_16BITS		BIT(12)

/* No करोwnsampling to planar YUV420 in image fetch mode. */
#घोषणा CEU_CDOCR_NO_DOWSAMPLE		BIT(4)

/* Swap all input data in 8-bit, 16-bits and 32-bits units (Figure 46.45). */
#घोषणा CEU_CDOCR_SWAP_ENDIANNESS	(7)

/* Capture reset and enable bits. */
#घोषणा CEU_CAPSR_CPKIL			BIT(16)
#घोषणा CEU_CAPSR_CE			BIT(0)

/* CEU operating flag bit. */
#घोषणा CEU_CAPCR_CTNCP			BIT(16)
#घोषणा CEU_CSTRST_CPTON		BIT(0)

/* Platक्रमm specअगरic IRQ source flags. */
#घोषणा CEU_CETCR_ALL_IRQS_RZ		0x397f313
#घोषणा CEU_CETCR_ALL_IRQS_SH4		0x3d7f313

/* Prohibited रेजिस्टर access पूर्णांकerrupt bit. */
#घोषणा CEU_CETCR_IGRW			BIT(4)
/* One-frame capture end पूर्णांकerrupt. */
#घोषणा CEU_CEIER_CPE			BIT(0)
/* VBP error. */
#घोषणा CEU_CEIER_VBP			BIT(20)
#घोषणा CEU_CEIER_MASK			(CEU_CEIER_CPE | CEU_CEIER_VBP)

#घोषणा CEU_MAX_WIDTH	2560
#घोषणा CEU_MAX_HEIGHT	1920
#घोषणा CEU_MAX_BPL	8188
#घोषणा CEU_W_MAX(w)	((w) < CEU_MAX_WIDTH ? (w) : CEU_MAX_WIDTH)
#घोषणा CEU_H_MAX(h)	((h) < CEU_MAX_HEIGHT ? (h) : CEU_MAX_HEIGHT)

/*
 * ceu_bus_fmt - describe a 8-bits yuyv क्रमmat the sensor can produce
 *
 * @mbus_code: bus क्रमmat code
 * @fmt_order: CEU_CAMCR.DTARY ordering of input components (Y, Cb, Cr)
 * @fmt_order_swap: swapped CEU_CAMCR.DTARY ordering of input components
 *		    (Y, Cr, Cb)
 * @swapped: करोes Cr appear beक्रमe Cb?
 * @bps: number of bits sent over bus क्रम each sample
 * @bpp: number of bits per pixels unit
 */
काष्ठा ceu_mbus_fmt अणु
	u32	mbus_code;
	u32	fmt_order;
	u32	fmt_order_swap;
	bool	swapped;
	u8	bps;
	u8	bpp;
पूर्ण;

/*
 * ceu_buffer - Link vb2 buffer to the list of available buffers.
 */
काष्ठा ceu_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head queue;
पूर्ण;

अटल अंतरभूत काष्ठा ceu_buffer *vb2_to_ceu(काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	वापस container_of(vbuf, काष्ठा ceu_buffer, vb);
पूर्ण

/*
 * ceu_subdev - Wraps v4l2 sub-device and provides async subdevice.
 */
काष्ठा ceu_subdev अणु
	काष्ठा v4l2_async_subdev asd;
	काष्ठा v4l2_subdev *v4l2_sd;

	/* per-subdevice mbus configuration options */
	अचिन्हित पूर्णांक mbus_flags;
	काष्ठा ceu_mbus_fmt mbus_fmt;
पूर्ण;

अटल काष्ठा ceu_subdev *to_ceu_subdev(काष्ठा v4l2_async_subdev *asd)
अणु
	वापस container_of(asd, काष्ठा ceu_subdev, asd);
पूर्ण

/*
 * ceu_device - CEU device instance
 */
काष्ठा ceu_device अणु
	काष्ठा device		*dev;
	काष्ठा video_device	vdev;
	काष्ठा v4l2_device	v4l2_dev;

	/* subdevices descriptors */
	काष्ठा ceu_subdev	**subdevs;
	/* the subdevice currently in use */
	काष्ठा ceu_subdev	*sd;
	अचिन्हित पूर्णांक		sd_index;
	अचिन्हित पूर्णांक		num_sd;

	/* platक्रमm specअगरic mask with all IRQ sources flagged */
	u32			irq_mask;

	/* currently configured field and pixel क्रमmat */
	क्रमागत v4l2_field	field;
	काष्ठा v4l2_pix_क्रमmat_mplane v4l2_pix;

	/* async subdev notअगरication helpers */
	काष्ठा v4l2_async_notअगरier notअगरier;

	/* vb2 queue, capture buffer list and active buffer poपूर्णांकer */
	काष्ठा vb2_queue	vb2_vq;
	काष्ठा list_head	capture;
	काष्ठा vb2_v4l2_buffer	*active;
	अचिन्हित पूर्णांक		sequence;

	/* mlock - lock access to पूर्णांकerface reset and vb2 queue */
	काष्ठा mutex	mlock;

	/* lock - lock access to capture buffer queue and active buffer */
	spinlock_t	lock;

	/* base - CEU memory base address */
	व्योम __iomem	*base;
पूर्ण;

अटल अंतरभूत काष्ठा ceu_device *v4l2_to_ceu(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा ceu_device, v4l2_dev);
पूर्ण

/* --- CEU memory output क्रमmats --- */

/*
 * ceu_fmt - describe a memory output क्रमmat supported by CEU पूर्णांकerface.
 *
 * @fourcc: memory layout fourcc क्रमmat code
 * @bpp: number of bits क्रम each pixel stored in memory
 */
काष्ठा ceu_fmt अणु
	u32	fourcc;
	u32	bpp;
पूर्ण;

/*
 * ceu_क्रमmat_list - List of supported memory output क्रमmats
 *
 * If sensor provides any YUYV bus क्रमmat, all the following planar memory
 * क्रमmats are available thanks to CEU re-ordering and sub-sampling
 * capabilities.
 */
अटल स्थिर काष्ठा ceu_fmt ceu_fmt_list[] = अणु
	अणु
		.fourcc	= V4L2_PIX_FMT_NV16,
		.bpp	= 16,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_NV61,
		.bpp	= 16,
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_NV12,
		.bpp	= 12,
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_NV21,
		.bpp	= 12,
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_YUYV,
		.bpp	= 16,
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_UYVY,
		.bpp	= 16,
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_YVYU,
		.bpp	= 16,
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_VYUY,
		.bpp	= 16,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ceu_fmt *get_ceu_fmt_from_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	स्थिर काष्ठा ceu_fmt *fmt = &ceu_fmt_list[0];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ceu_fmt_list); i++, fmt++)
		अगर (fmt->fourcc == fourcc)
			वापस fmt;

	वापस शून्य;
पूर्ण

अटल bool ceu_fmt_mplane(काष्ठा v4l2_pix_क्रमmat_mplane *pix)
अणु
	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_VYUY:
		वापस false;
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* --- CEU HW operations --- */

अटल व्योम ceu_ग_लिखो(काष्ठा ceu_device *priv, अचिन्हित पूर्णांक reg_offs, u32 data)
अणु
	ioग_लिखो32(data, priv->base + reg_offs);
पूर्ण

अटल u32 ceu_पढ़ो(काष्ठा ceu_device *priv, अचिन्हित पूर्णांक reg_offs)
अणु
	वापस ioपढ़ो32(priv->base + reg_offs);
पूर्ण

/*
 * ceu_soft_reset() - Software reset the CEU पूर्णांकerface.
 * @ceu_device: CEU device.
 *
 * Returns 0 क्रम success, -EIO क्रम error.
 */
अटल पूर्णांक ceu_soft_reset(काष्ठा ceu_device *ceudev)
अणु
	अचिन्हित पूर्णांक i;

	ceu_ग_लिखो(ceudev, CEU_CAPSR, CEU_CAPSR_CPKIL);

	क्रम (i = 0; i < 100; i++) अणु
		अगर (!(ceu_पढ़ो(ceudev, CEU_CSTSR) & CEU_CSTRST_CPTON))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i == 100) अणु
		dev_err(ceudev->dev, "soft reset time out\n");
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < 100; i++) अणु
		अगर (!(ceu_पढ़ो(ceudev, CEU_CAPSR) & CEU_CAPSR_CPKIL))
			वापस 0;
		udelay(1);
	पूर्ण

	/* If we get here, CEU has not reset properly. */
	वापस -EIO;
पूर्ण

/* --- CEU Capture Operations --- */

/*
 * ceu_hw_config() - Configure CEU पूर्णांकerface रेजिस्टरs.
 */
अटल पूर्णांक ceu_hw_config(काष्ठा ceu_device *ceudev)
अणु
	u32 camcr, cकरोcr, cfzsr, cdwdr, capwr;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &ceudev->v4l2_pix;
	काष्ठा ceu_subdev *ceu_sd = ceudev->sd;
	काष्ठा ceu_mbus_fmt *mbus_fmt = &ceu_sd->mbus_fmt;
	अचिन्हित पूर्णांक mbus_flags = ceu_sd->mbus_flags;

	/* Start configuring CEU रेजिस्टरs */
	ceu_ग_लिखो(ceudev, CEU_CAIFR, 0);
	ceu_ग_लिखो(ceudev, CEU_CFWCR, 0);
	ceu_ग_लिखो(ceudev, CEU_CRCNTR, 0);
	ceu_ग_लिखो(ceudev, CEU_CRCMPR, 0);

	/* Set the frame capture period क्रम both image capture and data sync. */
	capwr = (pix->height << 16) | pix->width * mbus_fmt->bpp / 8;

	/*
	 * Swap input data endianness by शेष.
	 * In data fetch mode bytes are received in chunks of 8 bytes.
	 * D0, D1, D2, D3, D4, D5, D6, D7 (D0 received first)
	 * The data is however by शेष written to memory in reverse order:
	 * D7, D6, D5, D4, D3, D2, D1, D0 (D7 written to lowest byte)
	 *
	 * Use CEU_CDOCR[2:0] to swap data ordering.
	 */
	cकरोcr = CEU_CDOCR_SWAP_ENDIANNESS;

	/*
	 * Configure CAMCR and CDOCR:
	 * match input components ordering with memory output क्रमmat and
	 * handle करोwnsampling to YUV420.
	 *
	 * If the memory output planar क्रमmat is 'swapped' (Cr beक्रमe Cb) and
	 * input क्रमmat is not, use the swapped version of CAMCR.DTARY.
	 *
	 * If the memory output planar क्रमmat is not 'swapped' (Cb beक्रमe Cr)
	 * and input क्रमmat is, use the swapped version of CAMCR.DTARY.
	 *
	 * CEU by शेष करोwnsample to planar YUV420 (CDCOR[4] = 0).
	 * If output is planar YUV422 set CDOCR[4] = 1
	 *
	 * No करोwnsample क्रम data fetch sync mode.
	 */
	चयन (pix->pixelक्रमmat) अणु
	/* Data fetch sync mode */
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_VYUY:
		camcr	= CEU_CAMCR_JPEG;
		cकरोcr	|= CEU_CDOCR_NO_DOWSAMPLE;
		cfzsr	= (pix->height << 16) | pix->width;
		cdwdr	= pix->plane_fmt[0].bytesperline;
		अवरोध;

	/* Non-swapped planar image capture mode. */
	हाल V4L2_PIX_FMT_NV16:
		cकरोcr	|= CEU_CDOCR_NO_DOWSAMPLE;
		fallthrough;
	हाल V4L2_PIX_FMT_NV12:
		अगर (mbus_fmt->swapped)
			camcr = mbus_fmt->fmt_order_swap;
		अन्यथा
			camcr = mbus_fmt->fmt_order;

		cfzsr	= (pix->height << 16) | pix->width;
		cdwdr	= pix->width;
		अवरोध;

	/* Swapped planar image capture mode. */
	हाल V4L2_PIX_FMT_NV61:
		cकरोcr	|= CEU_CDOCR_NO_DOWSAMPLE;
		fallthrough;
	हाल V4L2_PIX_FMT_NV21:
		अगर (mbus_fmt->swapped)
			camcr = mbus_fmt->fmt_order;
		अन्यथा
			camcr = mbus_fmt->fmt_order_swap;

		cfzsr	= (pix->height << 16) | pix->width;
		cdwdr	= pix->width;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	camcr |= mbus_flags & V4L2_MBUS_VSYNC_ACTIVE_LOW ? 1 << 1 : 0;
	camcr |= mbus_flags & V4L2_MBUS_HSYNC_ACTIVE_LOW ? 1 << 0 : 0;

	/* TODO: handle 16 bit bus width with DTIF bit in CAMCR */
	ceu_ग_लिखो(ceudev, CEU_CAMCR, camcr);
	ceu_ग_लिखो(ceudev, CEU_CDOCR, cकरोcr);
	ceu_ग_लिखो(ceudev, CEU_CAPCR, CEU_CAPCR_BUS_WIDTH256);

	/*
	 * TODO: make CAMOR offsets configurable.
	 * CAMOR wants to know the number of blanks between a VS/HS संकेत
	 * and valid data. This value should actually come from the sensor...
	 */
	ceu_ग_लिखो(ceudev, CEU_CAMOR, 0);

	/* TODO: 16 bit bus width require re-calculation of cdwdr and cfzsr */
	ceu_ग_लिखो(ceudev, CEU_CAPWR, capwr);
	ceu_ग_लिखो(ceudev, CEU_CFSZR, cfzsr);
	ceu_ग_लिखो(ceudev, CEU_CDWDR, cdwdr);

	वापस 0;
पूर्ण

/*
 * ceu_capture() - Trigger start of a capture sequence.
 *
 * Program the CEU DMA रेजिस्टरs with addresses where to transfer image data.
 */
अटल पूर्णांक ceu_capture(काष्ठा ceu_device *ceudev)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &ceudev->v4l2_pix;
	dma_addr_t phys_addr_top;

	phys_addr_top =
		vb2_dma_contig_plane_dma_addr(&ceudev->active->vb2_buf, 0);
	ceu_ग_लिखो(ceudev, CEU_CDAYR, phys_addr_top);

	/* Ignore CbCr plane क्रम non multi-planar image क्रमmats. */
	अगर (ceu_fmt_mplane(pix)) अणु
		phys_addr_top =
			vb2_dma_contig_plane_dma_addr(&ceudev->active->vb2_buf,
						      1);
		ceu_ग_लिखो(ceudev, CEU_CDACR, phys_addr_top);
	पूर्ण

	/*
	 * Trigger new capture start: once क्रम each frame, as we work in
	 * one-frame capture mode.
	 */
	ceu_ग_लिखो(ceudev, CEU_CAPSR, CEU_CAPSR_CE);

	वापस 0;
पूर्ण

अटल irqवापस_t ceu_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ceu_device *ceudev = data;
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा ceu_buffer *buf;
	u32 status;

	/* Clean पूर्णांकerrupt status. */
	status = ceu_पढ़ो(ceudev, CEU_CETCR);
	ceu_ग_लिखो(ceudev, CEU_CETCR, ~ceudev->irq_mask);

	/* Unexpected पूर्णांकerrupt. */
	अगर (!(status & CEU_CEIER_MASK))
		वापस IRQ_NONE;

	spin_lock(&ceudev->lock);

	/* Stale पूर्णांकerrupt from a released buffer, ignore it. */
	vbuf = ceudev->active;
	अगर (!vbuf) अणु
		spin_unlock(&ceudev->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * When a VBP पूर्णांकerrupt occurs, no capture end पूर्णांकerrupt will occur
	 * and the image of that frame is not captured correctly.
	 */
	अगर (status & CEU_CEIER_VBP) अणु
		dev_err(ceudev->dev, "VBP interrupt: abort capture\n");
		जाओ error_irq_out;
	पूर्ण

	/* Prepare to वापस the 'previous' buffer. */
	vbuf->vb2_buf.बारtamp = kसमय_get_ns();
	vbuf->sequence = ceudev->sequence++;
	vbuf->field = ceudev->field;

	/* Prepare a new 'active' buffer and trigger a new capture. */
	अगर (!list_empty(&ceudev->capture)) अणु
		buf = list_first_entry(&ceudev->capture, काष्ठा ceu_buffer,
				       queue);
		list_del(&buf->queue);
		ceudev->active = &buf->vb;

		ceu_capture(ceudev);
	पूर्ण

	/* Return the 'previous' buffer. */
	vb2_buffer_करोne(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);

	spin_unlock(&ceudev->lock);

	वापस IRQ_HANDLED;

error_irq_out:
	/* Return the 'previous' buffer and all queued ones. */
	vb2_buffer_करोne(&vbuf->vb2_buf, VB2_BUF_STATE_ERROR);

	list_क्रम_each_entry(buf, &ceudev->capture, queue)
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);

	spin_unlock(&ceudev->lock);

	वापस IRQ_HANDLED;
पूर्ण

/* --- CEU Videobuf2 operations --- */

अटल व्योम ceu_update_plane_sizes(काष्ठा v4l2_plane_pix_क्रमmat *plane,
				   अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक szimage)
अणु
	स_रखो(plane, 0, माप(*plane));

	plane->sizeimage = szimage;
	अगर (plane->bytesperline < bpl || plane->bytesperline > CEU_MAX_BPL)
		plane->bytesperline = bpl;
पूर्ण

/*
 * ceu_calc_plane_sizes() - Fill per-plane 'struct v4l2_plane_pix_format'
 *			    inक्रमmation according to the currently configured
 *			    pixel क्रमmat.
 * @ceu_device: CEU device.
 * @ceu_fmt: Active image क्रमmat.
 * @pix: Pixel क्रमmat inक्रमmation (store line width and image sizes)
 */
अटल व्योम ceu_calc_plane_sizes(काष्ठा ceu_device *ceudev,
				 स्थिर काष्ठा ceu_fmt *ceu_fmt,
				 काष्ठा v4l2_pix_क्रमmat_mplane *pix)
अणु
	अचिन्हित पूर्णांक bpl, szimage;

	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_VYUY:
		pix->num_planes	= 1;
		bpl		= pix->width * ceu_fmt->bpp / 8;
		szimage		= pix->height * bpl;
		ceu_update_plane_sizes(&pix->plane_fmt[0], bpl, szimage);
		अवरोध;

	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		pix->num_planes	= 2;
		bpl		= pix->width;
		szimage		= pix->height * pix->width;
		ceu_update_plane_sizes(&pix->plane_fmt[0], bpl, szimage);
		ceu_update_plane_sizes(&pix->plane_fmt[1], bpl, szimage / 2);
		अवरोध;

	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
	शेष:
		pix->num_planes	= 2;
		bpl		= pix->width;
		szimage		= pix->height * pix->width;
		ceu_update_plane_sizes(&pix->plane_fmt[0], bpl, szimage);
		ceu_update_plane_sizes(&pix->plane_fmt[1], bpl, szimage);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * ceu_vb2_setup() - is called to check whether the driver can accept the
 *		     requested number of buffers and to fill in plane sizes
 *		     क्रम the current frame क्रमmat, अगर required.
 */
अटल पूर्णांक ceu_vb2_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *count,
			 अचिन्हित पूर्णांक *num_planes, अचिन्हित पूर्णांक sizes[],
			 काष्ठा device *alloc_devs[])
अणु
	काष्ठा ceu_device *ceudev = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &ceudev->v4l2_pix;
	अचिन्हित पूर्णांक i;

	/* num_planes is set: just check plane sizes. */
	अगर (*num_planes) अणु
		क्रम (i = 0; i < pix->num_planes; i++)
			अगर (sizes[i] < pix->plane_fmt[i].sizeimage)
				वापस -EINVAL;

		वापस 0;
	पूर्ण

	/* num_planes not set: called from REQBUFS, just set plane sizes. */
	*num_planes = pix->num_planes;
	क्रम (i = 0; i < pix->num_planes; i++)
		sizes[i] = pix->plane_fmt[i].sizeimage;

	वापस 0;
पूर्ण

अटल व्योम ceu_vb2_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा ceu_device *ceudev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा ceu_buffer *buf = vb2_to_ceu(vbuf);
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&ceudev->lock, irqflags);
	list_add_tail(&buf->queue, &ceudev->capture);
	spin_unlock_irqrestore(&ceudev->lock, irqflags);
पूर्ण

अटल पूर्णांक ceu_vb2_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा ceu_device *ceudev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &ceudev->v4l2_pix;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pix->num_planes; i++) अणु
		अगर (vb2_plane_size(vb, i) < pix->plane_fmt[i].sizeimage) अणु
			dev_err(ceudev->dev,
				"Plane size too small (%lu < %u)\n",
				vb2_plane_size(vb, i),
				pix->plane_fmt[i].sizeimage);
			वापस -EINVAL;
		पूर्ण

		vb2_set_plane_payload(vb, i, pix->plane_fmt[i].sizeimage);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा ceu_device *ceudev = vb2_get_drv_priv(vq);
	काष्ठा v4l2_subdev *v4l2_sd = ceudev->sd->v4l2_sd;
	काष्ठा ceu_buffer *buf;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret;

	/* Program the CEU पूर्णांकerface according to the CEU image क्रमmat. */
	ret = ceu_hw_config(ceudev);
	अगर (ret)
		जाओ error_वापस_bufs;

	ret = v4l2_subdev_call(v4l2_sd, video, s_stream, 1);
	अगर (ret && ret != -ENOIOCTLCMD) अणु
		dev_dbg(ceudev->dev,
			"Subdevice failed to start streaming: %d\n", ret);
		जाओ error_वापस_bufs;
	पूर्ण

	spin_lock_irqsave(&ceudev->lock, irqflags);
	ceudev->sequence = 0;

	/* Grab the first available buffer and trigger the first capture. */
	buf = list_first_entry(&ceudev->capture, काष्ठा ceu_buffer,
			       queue);
	अगर (!buf) अणु
		spin_unlock_irqrestore(&ceudev->lock, irqflags);
		dev_dbg(ceudev->dev,
			"No buffer available for capture.\n");
		जाओ error_stop_sensor;
	पूर्ण

	list_del(&buf->queue);
	ceudev->active = &buf->vb;

	/* Clean and program पूर्णांकerrupts क्रम first capture. */
	ceu_ग_लिखो(ceudev, CEU_CETCR, ~ceudev->irq_mask);
	ceu_ग_लिखो(ceudev, CEU_CEIER, CEU_CEIER_MASK);

	ceu_capture(ceudev);

	spin_unlock_irqrestore(&ceudev->lock, irqflags);

	वापस 0;

error_stop_sensor:
	v4l2_subdev_call(v4l2_sd, video, s_stream, 0);

error_वापस_bufs:
	spin_lock_irqsave(&ceudev->lock, irqflags);
	list_क्रम_each_entry(buf, &ceudev->capture, queue)
		vb2_buffer_करोne(&ceudev->active->vb2_buf,
				VB2_BUF_STATE_QUEUED);
	ceudev->active = शून्य;
	spin_unlock_irqrestore(&ceudev->lock, irqflags);

	वापस ret;
पूर्ण

अटल व्योम ceu_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा ceu_device *ceudev = vb2_get_drv_priv(vq);
	काष्ठा v4l2_subdev *v4l2_sd = ceudev->sd->v4l2_sd;
	काष्ठा ceu_buffer *buf;
	अचिन्हित दीर्घ irqflags;

	/* Clean and disable पूर्णांकerrupt sources. */
	ceu_ग_लिखो(ceudev, CEU_CETCR,
		  ceu_पढ़ो(ceudev, CEU_CETCR) & ceudev->irq_mask);
	ceu_ग_लिखो(ceudev, CEU_CEIER, CEU_CEIER_MASK);

	v4l2_subdev_call(v4l2_sd, video, s_stream, 0);

	spin_lock_irqsave(&ceudev->lock, irqflags);
	अगर (ceudev->active) अणु
		vb2_buffer_करोne(&ceudev->active->vb2_buf,
				VB2_BUF_STATE_ERROR);
		ceudev->active = शून्य;
	पूर्ण

	/* Release all queued buffers. */
	list_क्रम_each_entry(buf, &ceudev->capture, queue)
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	INIT_LIST_HEAD(&ceudev->capture);

	spin_unlock_irqrestore(&ceudev->lock, irqflags);

	ceu_soft_reset(ceudev);
पूर्ण

अटल स्थिर काष्ठा vb2_ops ceu_vb2_ops = अणु
	.queue_setup		= ceu_vb2_setup,
	.buf_queue		= ceu_vb2_queue,
	.buf_prepare		= ceu_vb2_prepare,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.start_streaming	= ceu_start_streaming,
	.stop_streaming		= ceu_stop_streaming,
पूर्ण;

/* --- CEU image क्रमmats handling --- */

/*
 * __ceu_try_fmt() - test क्रमmat on CEU and sensor
 * @ceudev: The CEU device.
 * @v4l2_fmt: क्रमmat to test.
 * @sd_mbus_code: the media bus code accepted by the subdevice; output param.
 *
 * Returns 0 क्रम success, < 0 क्रम errors.
 */
अटल पूर्णांक __ceu_try_fmt(काष्ठा ceu_device *ceudev, काष्ठा v4l2_क्रमmat *v4l2_fmt,
			 u32 *sd_mbus_code)
अणु
	काष्ठा ceu_subdev *ceu_sd = ceudev->sd;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &v4l2_fmt->fmt.pix_mp;
	काष्ठा v4l2_subdev *v4l2_sd = ceu_sd->v4l2_sd;
	काष्ठा v4l2_subdev_pad_config pad_cfg;
	स्थिर काष्ठा ceu_fmt *ceu_fmt;
	u32 mbus_code_old;
	u32 mbus_code;
	पूर्णांक ret;

	/*
	 * Set क्रमmat on sensor sub device: bus क्रमmat used to produce memory
	 * क्रमmat is selected depending on YUV component ordering or
	 * at initialization समय.
	 */
	काष्ठा v4l2_subdev_क्रमmat sd_क्रमmat = अणु
		.which	= V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;

	mbus_code_old = ceu_sd->mbus_fmt.mbus_code;

	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
		mbus_code = MEDIA_BUS_FMT_YUYV8_2X8;
		अवरोध;
	हाल V4L2_PIX_FMT_UYVY:
		mbus_code = MEDIA_BUS_FMT_UYVY8_2X8;
		अवरोध;
	हाल V4L2_PIX_FMT_YVYU:
		mbus_code = MEDIA_BUS_FMT_YVYU8_2X8;
		अवरोध;
	हाल V4L2_PIX_FMT_VYUY:
		mbus_code = MEDIA_BUS_FMT_VYUY8_2X8;
		अवरोध;
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		mbus_code = ceu_sd->mbus_fmt.mbus_code;
		अवरोध;

	शेष:
		pix->pixelक्रमmat = V4L2_PIX_FMT_NV16;
		mbus_code = ceu_sd->mbus_fmt.mbus_code;
		अवरोध;
	पूर्ण

	ceu_fmt = get_ceu_fmt_from_fourcc(pix->pixelक्रमmat);

	/* CFSZR requires height and width to be 4-pixel aligned. */
	v4l_bound_align_image(&pix->width, 2, CEU_MAX_WIDTH, 4,
			      &pix->height, 4, CEU_MAX_HEIGHT, 4, 0);

	v4l2_fill_mbus_क्रमmat_mplane(&sd_क्रमmat.क्रमmat, pix);

	/*
	 * Try with the mbus_code matching YUYV components ordering first,
	 * अगर that one fails, fallback to शेष selected at initialization
	 * समय.
	 */
	sd_क्रमmat.क्रमmat.code = mbus_code;
	ret = v4l2_subdev_call(v4l2_sd, pad, set_fmt, &pad_cfg, &sd_क्रमmat);
	अगर (ret) अणु
		अगर (ret == -EINVAL) अणु
			/* fallback */
			sd_क्रमmat.क्रमmat.code = mbus_code_old;
			ret = v4l2_subdev_call(v4l2_sd, pad, set_fmt,
					       &pad_cfg, &sd_क्रमmat);
		पूर्ण

		अगर (ret)
			वापस ret;
	पूर्ण

	/* Apply size वापसed by sensor as the CEU can't scale. */
	v4l2_fill_pix_क्रमmat_mplane(pix, &sd_क्रमmat.क्रमmat);

	/* Calculate per-plane sizes based on image क्रमmat. */
	ceu_calc_plane_sizes(ceudev, ceu_fmt, pix);

	/* Report to caller the configured mbus क्रमmat. */
	*sd_mbus_code = sd_क्रमmat.क्रमmat.code;

	वापस 0;
पूर्ण

/*
 * ceu_try_fmt() - Wrapper क्रम __ceu_try_fmt; discard configured mbus_fmt
 */
अटल पूर्णांक ceu_try_fmt(काष्ठा ceu_device *ceudev, काष्ठा v4l2_क्रमmat *v4l2_fmt)
अणु
	u32 mbus_code;

	वापस __ceu_try_fmt(ceudev, v4l2_fmt, &mbus_code);
पूर्ण

/*
 * ceu_set_fmt() - Apply the supplied क्रमmat to both sensor and CEU
 */
अटल पूर्णांक ceu_set_fmt(काष्ठा ceu_device *ceudev, काष्ठा v4l2_क्रमmat *v4l2_fmt)
अणु
	काष्ठा ceu_subdev *ceu_sd = ceudev->sd;
	काष्ठा v4l2_subdev *v4l2_sd = ceu_sd->v4l2_sd;
	u32 mbus_code;
	पूर्णांक ret;

	/*
	 * Set क्रमmat on sensor sub device: bus क्रमmat used to produce memory
	 * क्रमmat is selected at initialization समय.
	 */
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	ret = __ceu_try_fmt(ceudev, v4l2_fmt, &mbus_code);
	अगर (ret)
		वापस ret;

	क्रमmat.क्रमmat.code = mbus_code;
	v4l2_fill_mbus_क्रमmat_mplane(&क्रमmat.क्रमmat, &v4l2_fmt->fmt.pix_mp);
	ret = v4l2_subdev_call(v4l2_sd, pad, set_fmt, शून्य, &क्रमmat);
	अगर (ret)
		वापस ret;

	ceudev->v4l2_pix = v4l2_fmt->fmt.pix_mp;
	ceudev->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

/*
 * ceu_set_शेष_fmt() - Apply शेष NV16 memory output क्रमmat with VGA
 *			   sizes.
 */
अटल पूर्णांक ceu_set_शेष_fmt(काष्ठा ceu_device *ceudev)
अणु
	पूर्णांक ret;

	काष्ठा v4l2_क्रमmat v4l2_fmt = अणु
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
		.fmt.pix_mp = अणु
			.width		= VGA_WIDTH,
			.height		= VGA_HEIGHT,
			.field		= V4L2_FIELD_NONE,
			.pixelक्रमmat	= V4L2_PIX_FMT_NV16,
			.num_planes	= 2,
			.plane_fmt	= अणु
				[0]	= अणु
					.sizeimage = VGA_WIDTH * VGA_HEIGHT * 2,
					.bytesperline = VGA_WIDTH * 2,
				पूर्ण,
				[1]	= अणु
					.sizeimage = VGA_WIDTH * VGA_HEIGHT * 2,
					.bytesperline = VGA_WIDTH * 2,
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण;

	ret = ceu_try_fmt(ceudev, &v4l2_fmt);
	अगर (ret)
		वापस ret;

	ceudev->v4l2_pix = v4l2_fmt.fmt.pix_mp;
	ceudev->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

/*
 * ceu_init_mbus_fmt() - Query sensor क्रम supported क्रमmats and initialize
 *			 CEU media bus क्रमmat used to produce memory क्रमmats.
 *
 * Find out अगर sensor can produce a permutation of 8-bits YUYV bus क्रमmat.
 * From a single 8-bits YUYV bus क्रमmat the CEU can produce several memory
 * output क्रमmats:
 * - NV[12|21|16|61] through image fetch mode;
 * - YUYV422 अगर sensor provides YUYV422
 *
 * TODO: Other YUYV422 permutations through data fetch sync mode and DTARY
 * TODO: Binary data (eg. JPEG) and raw क्रमmats through data fetch sync mode
 */
अटल पूर्णांक ceu_init_mbus_fmt(काष्ठा ceu_device *ceudev)
अणु
	काष्ठा ceu_subdev *ceu_sd = ceudev->sd;
	काष्ठा ceu_mbus_fmt *mbus_fmt = &ceu_sd->mbus_fmt;
	काष्ठा v4l2_subdev *v4l2_sd = ceu_sd->v4l2_sd;
	bool yuyv_bus_fmt = false;

	काष्ठा v4l2_subdev_mbus_code_क्रमागत sd_mbus_fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.index = 0,
	पूर्ण;

	/* Find out अगर sensor can produce any permutation of 8-bits YUYV422. */
	जबतक (!yuyv_bus_fmt &&
	       !v4l2_subdev_call(v4l2_sd, pad, क्रमागत_mbus_code,
				 शून्य, &sd_mbus_fmt)) अणु
		चयन (sd_mbus_fmt.code) अणु
		हाल MEDIA_BUS_FMT_YUYV8_2X8:
		हाल MEDIA_BUS_FMT_YVYU8_2X8:
		हाल MEDIA_BUS_FMT_UYVY8_2X8:
		हाल MEDIA_BUS_FMT_VYUY8_2X8:
			yuyv_bus_fmt = true;
			अवरोध;
		शेष:
			/*
			 * Only support 8-bits YUYV bus क्रमmats at the moment;
			 *
			 * TODO: add support क्रम binary क्रमmats (data sync
			 * fetch mode).
			 */
			अवरोध;
		पूर्ण

		sd_mbus_fmt.index++;
	पूर्ण

	अगर (!yuyv_bus_fmt)
		वापस -ENXIO;

	/*
	 * Save the first encountered YUYV क्रमmat as "mbus_fmt" and use it
	 * to output all planar YUV422 and YUV420 (NV*) क्रमmats to memory as
	 * well as क्रम data synch fetch mode (YUYV - YVYU etc. ).
	 */
	mbus_fmt->mbus_code	= sd_mbus_fmt.code;
	mbus_fmt->bps		= 8;

	/* Annotate the selected bus क्रमmat components ordering. */
	चयन (sd_mbus_fmt.code) अणु
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		mbus_fmt->fmt_order		= CEU_CAMCR_DTARY_8_YUYV;
		mbus_fmt->fmt_order_swap	= CEU_CAMCR_DTARY_8_YVYU;
		mbus_fmt->swapped		= false;
		mbus_fmt->bpp			= 16;
		अवरोध;

	हाल MEDIA_BUS_FMT_YVYU8_2X8:
		mbus_fmt->fmt_order		= CEU_CAMCR_DTARY_8_YVYU;
		mbus_fmt->fmt_order_swap	= CEU_CAMCR_DTARY_8_YUYV;
		mbus_fmt->swapped		= true;
		mbus_fmt->bpp			= 16;
		अवरोध;

	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		mbus_fmt->fmt_order		= CEU_CAMCR_DTARY_8_UYVY;
		mbus_fmt->fmt_order_swap	= CEU_CAMCR_DTARY_8_VYUY;
		mbus_fmt->swapped		= false;
		mbus_fmt->bpp			= 16;
		अवरोध;

	हाल MEDIA_BUS_FMT_VYUY8_2X8:
		mbus_fmt->fmt_order		= CEU_CAMCR_DTARY_8_VYUY;
		mbus_fmt->fmt_order_swap	= CEU_CAMCR_DTARY_8_UYVY;
		mbus_fmt->swapped		= true;
		mbus_fmt->bpp			= 16;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* --- Runसमय PM Handlers --- */

/*
 * ceu_runसमय_resume() - soft-reset the पूर्णांकerface and turn sensor घातer on.
 */
अटल पूर्णांक __maybe_unused ceu_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा ceu_device *ceudev = dev_get_drvdata(dev);
	काष्ठा v4l2_subdev *v4l2_sd = ceudev->sd->v4l2_sd;

	v4l2_subdev_call(v4l2_sd, core, s_घातer, 1);

	ceu_soft_reset(ceudev);

	वापस 0;
पूर्ण

/*
 * ceu_runसमय_suspend() - disable capture and पूर्णांकerrupts and soft-reset.
 *			   Turn sensor घातer off.
 */
अटल पूर्णांक __maybe_unused ceu_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा ceu_device *ceudev = dev_get_drvdata(dev);
	काष्ठा v4l2_subdev *v4l2_sd = ceudev->sd->v4l2_sd;

	v4l2_subdev_call(v4l2_sd, core, s_घातer, 0);

	ceu_ग_लिखो(ceudev, CEU_CEIER, 0);
	ceu_soft_reset(ceudev);

	वापस 0;
पूर्ण

/* --- File Operations --- */

अटल पूर्णांक ceu_खोलो(काष्ठा file *file)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);
	पूर्णांक ret;

	ret = v4l2_fh_खोलो(file);
	अगर (ret)
		वापस ret;

	mutex_lock(&ceudev->mlock);
	/* Causes soft-reset and sensor घातer on on first खोलो */
	pm_runसमय_get_sync(ceudev->dev);
	mutex_unlock(&ceudev->mlock);

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_release(काष्ठा file *file)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);

	vb2_fop_release(file);

	mutex_lock(&ceudev->mlock);
	/* Causes soft-reset and sensor घातer करोwn on last बंद */
	pm_runसमय_put(ceudev->dev);
	mutex_unlock(&ceudev->mlock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations ceu_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= ceu_खोलो,
	.release		= ceu_release,
	.unlocked_ioctl		= video_ioctl2,
	.mmap			= vb2_fop_mmap,
	.poll			= vb2_fop_poll,
पूर्ण;

/* --- Video Device IOCTLs --- */

अटल पूर्णांक ceu_querycap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_capability *cap)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);

	strscpy(cap->card, "Renesas CEU", माप(cap->card));
	strscpy(cap->driver, DRIVER_NAME, माप(cap->driver));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:renesas-ceu-%s", dev_name(ceudev->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_fmtdesc *f)
अणु
	स्थिर काष्ठा ceu_fmt *fmt;

	अगर (f->index >= ARRAY_SIZE(ceu_fmt_list))
		वापस -EINVAL;

	fmt = &ceu_fmt_list[f->index];
	f->pixelक्रमmat = fmt->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);

	वापस ceu_try_fmt(ceudev, f);
पूर्ण

अटल पूर्णांक ceu_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);

	अगर (vb2_is_streaming(&ceudev->vb2_vq))
		वापस -EBUSY;

	वापस ceu_set_fmt(ceudev, f);
पूर्ण

अटल पूर्णांक ceu_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);

	f->fmt.pix_mp = ceudev->v4l2_pix;

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_input *inp)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);
	काष्ठा ceu_subdev *ceusd;

	अगर (inp->index >= ceudev->num_sd)
		वापस -EINVAL;

	ceusd = ceudev->subdevs[inp->index];

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = 0;
	snम_लिखो(inp->name, माप(inp->name), "Camera%u: %s",
		 inp->index, ceusd->v4l2_sd->name);

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);

	*i = ceudev->sd_index;

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);
	काष्ठा ceu_subdev *ceu_sd_old;
	पूर्णांक ret;

	अगर (i >= ceudev->num_sd)
		वापस -EINVAL;

	अगर (vb2_is_streaming(&ceudev->vb2_vq))
		वापस -EBUSY;

	अगर (i == ceudev->sd_index)
		वापस 0;

	ceu_sd_old = ceudev->sd;
	ceudev->sd = ceudev->subdevs[i];

	/*
	 * Make sure we can generate output image क्रमmats and apply
	 * शेष one.
	 */
	ret = ceu_init_mbus_fmt(ceudev);
	अगर (ret) अणु
		ceudev->sd = ceu_sd_old;
		वापस -EINVAL;
	पूर्ण

	ret = ceu_set_शेष_fmt(ceudev);
	अगर (ret) अणु
		ceudev->sd = ceu_sd_old;
		वापस -EINVAL;
	पूर्ण

	/* Now that we're sure we can use the sensor, घातer off the old one. */
	v4l2_subdev_call(ceu_sd_old->v4l2_sd, core, s_घातer, 0);
	v4l2_subdev_call(ceudev->sd->v4l2_sd, core, s_घातer, 1);

	ceudev->sd_index = i;

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_g_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);

	वापस v4l2_g_parm_cap(video_devdata(file), ceudev->sd->v4l2_sd, a);
पूर्ण

अटल पूर्णांक ceu_s_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);

	वापस v4l2_s_parm_cap(video_devdata(file), ceudev->sd->v4l2_sd, a);
पूर्ण

अटल पूर्णांक ceu_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);
	काष्ठा ceu_subdev *ceu_sd = ceudev->sd;
	स्थिर काष्ठा ceu_fmt *ceu_fmt;
	काष्ठा v4l2_subdev *v4l2_sd = ceu_sd->v4l2_sd;
	पूर्णांक ret;

	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.code	= ceu_sd->mbus_fmt.mbus_code,
		.index	= fsize->index,
		.which	= V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	/* Just check अगर user supplied pixel क्रमmat is supported. */
	ceu_fmt = get_ceu_fmt_from_fourcc(fsize->pixel_क्रमmat);
	अगर (!ceu_fmt)
		वापस -EINVAL;

	ret = v4l2_subdev_call(v4l2_sd, pad, क्रमागत_frame_size,
			       शून्य, &fse);
	अगर (ret)
		वापस ret;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = CEU_W_MAX(fse.max_width);
	fsize->discrete.height = CEU_H_MAX(fse.max_height);

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा ceu_device *ceudev = video_drvdata(file);
	काष्ठा ceu_subdev *ceu_sd = ceudev->sd;
	स्थिर काष्ठा ceu_fmt *ceu_fmt;
	काष्ठा v4l2_subdev *v4l2_sd = ceu_sd->v4l2_sd;
	पूर्णांक ret;

	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत fie = अणु
		.code	= ceu_sd->mbus_fmt.mbus_code,
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	/* Just check अगर user supplied pixel क्रमmat is supported. */
	ceu_fmt = get_ceu_fmt_from_fourcc(fival->pixel_क्रमmat);
	अगर (!ceu_fmt)
		वापस -EINVAL;

	ret = v4l2_subdev_call(v4l2_sd, pad, क्रमागत_frame_पूर्णांकerval, शून्य,
			       &fie);
	अगर (ret)
		वापस ret;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.पूर्णांकerval;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops ceu_ioctl_ops = अणु
	.vidioc_querycap		= ceu_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= ceu_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap_mplane	= ceu_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap_mplane	= ceu_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap_mplane	= ceu_g_fmt_vid_cap,

	.vidioc_क्रमागत_input		= ceu_क्रमागत_input,
	.vidioc_g_input			= ceu_g_input,
	.vidioc_s_input			= ceu_s_input,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_g_parm			= ceu_g_parm,
	.vidioc_s_parm			= ceu_s_parm,
	.vidioc_क्रमागत_framesizes		= ceu_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= ceu_क्रमागत_frameपूर्णांकervals,

	.vidioc_log_status              = v4l2_ctrl_log_status,
	.vidioc_subscribe_event         = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event       = v4l2_event_unsubscribe,
पूर्ण;

/*
 * ceu_vdev_release() - release CEU video device memory when last reference
 *			to this driver is बंदd
 */
अटल व्योम ceu_vdev_release(काष्ठा video_device *vdev)
अणु
	काष्ठा ceu_device *ceudev = video_get_drvdata(vdev);

	kमुक्त(ceudev);
पूर्ण

अटल पूर्णांक ceu_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
			    काष्ठा v4l2_subdev *v4l2_sd,
			    काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा v4l2_device *v4l2_dev = notअगरier->v4l2_dev;
	काष्ठा ceu_device *ceudev = v4l2_to_ceu(v4l2_dev);
	काष्ठा ceu_subdev *ceu_sd = to_ceu_subdev(asd);

	ceu_sd->v4l2_sd = v4l2_sd;
	ceudev->num_sd++;

	वापस 0;
पूर्ण

अटल पूर्णांक ceu_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा v4l2_device *v4l2_dev = notअगरier->v4l2_dev;
	काष्ठा ceu_device *ceudev = v4l2_to_ceu(v4l2_dev);
	काष्ठा video_device *vdev = &ceudev->vdev;
	काष्ठा vb2_queue *q = &ceudev->vb2_vq;
	काष्ठा v4l2_subdev *v4l2_sd;
	पूर्णांक ret;

	/* Initialize vb2 queue. */
	q->type			= V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	q->io_modes		= VB2_MMAP | VB2_DMABUF;
	q->drv_priv		= ceudev;
	q->ops			= &ceu_vb2_ops;
	q->mem_ops		= &vb2_dma_contig_memops;
	q->buf_काष्ठा_size	= माप(काष्ठा ceu_buffer);
	q->बारtamp_flags	= V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed	= 2;
	q->lock			= &ceudev->mlock;
	q->dev			= ceudev->v4l2_dev.dev;

	ret = vb2_queue_init(q);
	अगर (ret)
		वापस ret;

	/*
	 * Make sure at least one sensor is primary and use it to initialize
	 * ceu क्रमmats.
	 */
	अगर (!ceudev->sd) अणु
		ceudev->sd = ceudev->subdevs[0];
		ceudev->sd_index = 0;
	पूर्ण

	v4l2_sd = ceudev->sd->v4l2_sd;

	ret = ceu_init_mbus_fmt(ceudev);
	अगर (ret)
		वापस ret;

	ret = ceu_set_शेष_fmt(ceudev);
	अगर (ret)
		वापस ret;

	/* Register the video device. */
	strscpy(vdev->name, DRIVER_NAME, माप(vdev->name));
	vdev->v4l2_dev		= v4l2_dev;
	vdev->lock		= &ceudev->mlock;
	vdev->queue		= &ceudev->vb2_vq;
	vdev->ctrl_handler	= v4l2_sd->ctrl_handler;
	vdev->fops		= &ceu_fops;
	vdev->ioctl_ops		= &ceu_ioctl_ops;
	vdev->release		= ceu_vdev_release;
	vdev->device_caps	= V4L2_CAP_VIDEO_CAPTURE_MPLANE |
				  V4L2_CAP_STREAMING;
	video_set_drvdata(vdev, ceudev);

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		v4l2_err(vdev->v4l2_dev,
			 "video_register_device failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations ceu_notअगरy_ops = अणु
	.bound		= ceu_notअगरy_bound,
	.complete	= ceu_notअगरy_complete,
पूर्ण;

/*
 * ceu_init_async_subdevs() - Initialize CEU subdevices and async_subdevs in
 *                           ceu device. Both DT and platक्रमm data parsing use
 *                           this routine.
 *
 * Returns 0 क्रम success, -ENOMEM क्रम failure.
 */
अटल पूर्णांक ceu_init_async_subdevs(काष्ठा ceu_device *ceudev, अचिन्हित पूर्णांक n_sd)
अणु
	/* Reserve memory क्रम 'n_sd' ceu_subdev descriptors. */
	ceudev->subdevs = devm_kसुस्मृति(ceudev->dev, n_sd,
				       माप(*ceudev->subdevs), GFP_KERNEL);
	अगर (!ceudev->subdevs)
		वापस -ENOMEM;

	ceudev->sd = शून्य;
	ceudev->sd_index = 0;
	ceudev->num_sd = 0;

	वापस 0;
पूर्ण

/*
 * ceu_parse_platक्रमm_data() - Initialize async_subdevices using platक्रमm
 *			       device provided data.
 */
अटल पूर्णांक ceu_parse_platक्रमm_data(काष्ठा ceu_device *ceudev,
				   स्थिर काष्ठा ceu_platक्रमm_data *pdata)
अणु
	स्थिर काष्ठा ceu_async_subdev *async_sd;
	काष्ठा ceu_subdev *ceu_sd;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (pdata->num_subdevs == 0)
		वापस -ENODEV;

	ret = ceu_init_async_subdevs(ceudev, pdata->num_subdevs);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < pdata->num_subdevs; i++) अणु

		/* Setup the ceu subdevice and the async subdevice. */
		async_sd = &pdata->subdevs[i];
		ceu_sd = v4l2_async_notअगरier_add_i2c_subdev(&ceudev->notअगरier,
				async_sd->i2c_adapter_id,
				async_sd->i2c_address,
				काष्ठा ceu_subdev);
		अगर (IS_ERR(ceu_sd)) अणु
			v4l2_async_notअगरier_cleanup(&ceudev->notअगरier);
			वापस PTR_ERR(ceu_sd);
		पूर्ण
		ceu_sd->mbus_flags = async_sd->flags;
		ceudev->subdevs[i] = ceu_sd;
	पूर्ण

	वापस pdata->num_subdevs;
पूर्ण

/*
 * ceu_parse_dt() - Initialize async_subdevs parsing device tree graph.
 */
अटल पूर्णांक ceu_parse_dt(काष्ठा ceu_device *ceudev)
अणु
	काष्ठा device_node *of = ceudev->dev->of_node;
	काष्ठा device_node *ep;
	काष्ठा ceu_subdev *ceu_sd;
	अचिन्हित पूर्णांक i;
	पूर्णांक num_ep;
	पूर्णांक ret;

	num_ep = of_graph_get_endpoपूर्णांक_count(of);
	अगर (!num_ep)
		वापस -ENODEV;

	ret = ceu_init_async_subdevs(ceudev, num_ep);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < num_ep; i++) अणु
		काष्ठा v4l2_fwnode_endpoपूर्णांक fw_ep = अणु
			.bus_type = V4L2_MBUS_PARALLEL,
			.bus = अणु
				.parallel = अणु
					.flags = V4L2_MBUS_HSYNC_ACTIVE_HIGH |
						 V4L2_MBUS_VSYNC_ACTIVE_HIGH,
					.bus_width = 8,
				पूर्ण,
			पूर्ण,
		पूर्ण;

		ep = of_graph_get_endpoपूर्णांक_by_regs(of, 0, i);
		अगर (!ep) अणु
			dev_err(ceudev->dev,
				"No subdevice connected on endpoint %u.\n", i);
			ret = -ENODEV;
			जाओ error_cleanup;
		पूर्ण

		ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep), &fw_ep);
		अगर (ret) अणु
			dev_err(ceudev->dev,
				"Unable to parse endpoint #%u: %d.\n", i, ret);
			जाओ error_cleanup;
		पूर्ण

		/* Setup the ceu subdevice and the async subdevice. */
		ceu_sd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
				&ceudev->notअगरier, of_fwnode_handle(ep),
				काष्ठा ceu_subdev);
		अगर (IS_ERR(ceu_sd)) अणु
			ret = PTR_ERR(ceu_sd);
			जाओ error_cleanup;
		पूर्ण
		ceu_sd->mbus_flags = fw_ep.bus.parallel.flags;
		ceudev->subdevs[i] = ceu_sd;

		of_node_put(ep);
	पूर्ण

	वापस num_ep;

error_cleanup:
	v4l2_async_notअगरier_cleanup(&ceudev->notअगरier);
	of_node_put(ep);
	वापस ret;
पूर्ण

/*
 * काष्ठा ceu_data - Platक्रमm specअगरic CEU data
 * @irq_mask: CETCR mask with all पूर्णांकerrupt sources enabled. The mask dअगरfers
 *	      between SH4 and RZ platक्रमms.
 */
काष्ठा ceu_data अणु
	u32 irq_mask;
पूर्ण;

अटल स्थिर काष्ठा ceu_data ceu_data_rz = अणु
	.irq_mask = CEU_CETCR_ALL_IRQS_RZ,
पूर्ण;

अटल स्थिर काष्ठा ceu_data ceu_data_sh4 = अणु
	.irq_mask = CEU_CETCR_ALL_IRQS_SH4,
पूर्ण;

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ceu_of_match[] = अणु
	अणु .compatible = "renesas,r7s72100-ceu", .data = &ceu_data_rz पूर्ण,
	अणु .compatible = "renesas,r8a7740-ceu", .data = &ceu_data_rz पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ceu_of_match);
#पूर्ण_अगर

अटल पूर्णांक ceu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा ceu_data *ceu_data;
	काष्ठा ceu_device *ceudev;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक irq;
	पूर्णांक num_subdevs;
	पूर्णांक ret;

	ceudev = kzalloc(माप(*ceudev), GFP_KERNEL);
	अगर (!ceudev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ceudev);
	ceudev->dev = dev;

	INIT_LIST_HEAD(&ceudev->capture);
	spin_lock_init(&ceudev->lock);
	mutex_init(&ceudev->mlock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ceudev->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ceudev->base)) अणु
		ret = PTR_ERR(ceudev->base);
		जाओ error_मुक्त_ceudev;
	पूर्ण

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ error_मुक्त_ceudev;
	irq = ret;

	ret = devm_request_irq(dev, irq, ceu_irq,
			       0, dev_name(dev), ceudev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to request CEU interrupt.\n");
		जाओ error_मुक्त_ceudev;
	पूर्ण

	pm_runसमय_enable(dev);

	ret = v4l2_device_रेजिस्टर(dev, &ceudev->v4l2_dev);
	अगर (ret)
		जाओ error_pm_disable;

	v4l2_async_notअगरier_init(&ceudev->notअगरier);

	अगर (IS_ENABLED(CONFIG_OF) && dev->of_node) अणु
		ceu_data = of_device_get_match_data(dev);
		num_subdevs = ceu_parse_dt(ceudev);
	पूर्ण अन्यथा अगर (dev->platक्रमm_data) अणु
		/* Assume SH4 अगर booting with platक्रमm data. */
		ceu_data = &ceu_data_sh4;
		num_subdevs = ceu_parse_platक्रमm_data(ceudev,
						      dev->platक्रमm_data);
	पूर्ण अन्यथा अणु
		num_subdevs = -EINVAL;
	पूर्ण

	अगर (num_subdevs < 0) अणु
		ret = num_subdevs;
		जाओ error_v4l2_unरेजिस्टर;
	पूर्ण
	ceudev->irq_mask = ceu_data->irq_mask;

	ceudev->notअगरier.v4l2_dev	= &ceudev->v4l2_dev;
	ceudev->notअगरier.ops		= &ceu_notअगरy_ops;
	ret = v4l2_async_notअगरier_रेजिस्टर(&ceudev->v4l2_dev,
					   &ceudev->notअगरier);
	अगर (ret)
		जाओ error_cleanup;

	dev_info(dev, "Renesas Capture Engine Unit %s\n", dev_name(dev));

	वापस 0;

error_cleanup:
	v4l2_async_notअगरier_cleanup(&ceudev->notअगरier);
error_v4l2_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&ceudev->v4l2_dev);
error_pm_disable:
	pm_runसमय_disable(dev);
error_मुक्त_ceudev:
	kमुक्त(ceudev);

	वापस ret;
पूर्ण

अटल पूर्णांक ceu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ceu_device *ceudev = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(ceudev->dev);

	v4l2_async_notअगरier_unरेजिस्टर(&ceudev->notअगरier);

	v4l2_async_notअगरier_cleanup(&ceudev->notअगरier);

	v4l2_device_unरेजिस्टर(&ceudev->v4l2_dev);

	video_unरेजिस्टर_device(&ceudev->vdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ceu_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ceu_runसमय_suspend,
			   ceu_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver ceu_driver = अणु
	.driver		= अणु
		.name	= DRIVER_NAME,
		.pm	= &ceu_pm_ops,
		.of_match_table = of_match_ptr(ceu_of_match),
	पूर्ण,
	.probe		= ceu_probe,
	.हटाओ		= ceu_हटाओ,
पूर्ण;

module_platक्रमm_driver(ceu_driver);

MODULE_DESCRIPTION("Renesas CEU camera driver");
MODULE_AUTHOR("Jacopo Mondi <jacopo+renesas@jmondi.org>");
MODULE_LICENSE("GPL v2");
