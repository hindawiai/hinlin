<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Register पूर्णांकerface file क्रम EXYNOS FIMC-LITE (camera पूर्णांकerface) driver
 *
 * Copyright (C) 2012 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
*/

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>

#समावेश "fimc-lite-reg.h"
#समावेश "fimc-lite.h"
#समावेश "fimc-core.h"

#घोषणा FLITE_RESET_TIMEOUT 50 /* in ms */

व्योम flite_hw_reset(काष्ठा fimc_lite *dev)
अणु
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(FLITE_RESET_TIMEOUT);
	u32 cfg;

	cfg = पढ़ोl(dev->regs + FLITE_REG_CIGCTRL);
	cfg |= FLITE_REG_CIGCTRL_SWRST_REQ;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIGCTRL);

	जबतक (समय_is_after_jअगरfies(end)) अणु
		cfg = पढ़ोl(dev->regs + FLITE_REG_CIGCTRL);
		अगर (cfg & FLITE_REG_CIGCTRL_SWRST_RDY)
			अवरोध;
		usleep_range(1000, 5000);
	पूर्ण

	cfg |= FLITE_REG_CIGCTRL_SWRST;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIGCTRL);
पूर्ण

व्योम flite_hw_clear_pending_irq(काष्ठा fimc_lite *dev)
अणु
	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CISTATUS);
	cfg &= ~FLITE_REG_CISTATUS_IRQ_CAM;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CISTATUS);
पूर्ण

u32 flite_hw_get_पूर्णांकerrupt_source(काष्ठा fimc_lite *dev)
अणु
	u32 पूर्णांकsrc = पढ़ोl(dev->regs + FLITE_REG_CISTATUS);
	वापस पूर्णांकsrc & FLITE_REG_CISTATUS_IRQ_MASK;
पूर्ण

व्योम flite_hw_clear_last_capture_end(काष्ठा fimc_lite *dev)
अणु

	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CISTATUS2);
	cfg &= ~FLITE_REG_CISTATUS2_LASTCAPEND;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CISTATUS2);
पूर्ण

व्योम flite_hw_set_पूर्णांकerrupt_mask(काष्ठा fimc_lite *dev)
अणु
	u32 cfg, पूर्णांकsrc;

	/* Select पूर्णांकerrupts to be enabled क्रम each output mode */
	अगर (atomic_पढ़ो(&dev->out_path) == FIMC_IO_DMA) अणु
		पूर्णांकsrc = FLITE_REG_CIGCTRL_IRQ_OVFEN |
			 FLITE_REG_CIGCTRL_IRQ_LASTEN |
			 FLITE_REG_CIGCTRL_IRQ_STARTEN |
			 FLITE_REG_CIGCTRL_IRQ_ENDEN;
	पूर्ण अन्यथा अणु
		/* An output to the FIMC-IS */
		पूर्णांकsrc = FLITE_REG_CIGCTRL_IRQ_OVFEN |
			 FLITE_REG_CIGCTRL_IRQ_LASTEN;
	पूर्ण

	cfg = पढ़ोl(dev->regs + FLITE_REG_CIGCTRL);
	cfg |= FLITE_REG_CIGCTRL_IRQ_DISABLE_MASK;
	cfg &= ~पूर्णांकsrc;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIGCTRL);
पूर्ण

व्योम flite_hw_capture_start(काष्ठा fimc_lite *dev)
अणु
	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CIIMGCPT);
	cfg |= FLITE_REG_CIIMGCPT_IMGCPTEN;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIIMGCPT);
पूर्ण

व्योम flite_hw_capture_stop(काष्ठा fimc_lite *dev)
अणु
	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CIIMGCPT);
	cfg &= ~FLITE_REG_CIIMGCPT_IMGCPTEN;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIIMGCPT);
पूर्ण

/*
 * Test pattern (color bars) enable/disable. External sensor
 * pixel घड़ी must be active क्रम the test pattern to work.
 */
व्योम flite_hw_set_test_pattern(काष्ठा fimc_lite *dev, bool on)
अणु
	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CIGCTRL);
	अगर (on)
		cfg |= FLITE_REG_CIGCTRL_TEST_PATTERN_COLORBAR;
	अन्यथा
		cfg &= ~FLITE_REG_CIGCTRL_TEST_PATTERN_COLORBAR;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIGCTRL);
पूर्ण

अटल स्थिर u32 src_pixfmt_map[8][3] = अणु
	अणु MEDIA_BUS_FMT_YUYV8_2X8, FLITE_REG_CISRCSIZE_ORDER422_IN_YCBYCR,
	  FLITE_REG_CIGCTRL_YUV422_1P पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, FLITE_REG_CISRCSIZE_ORDER422_IN_YCRYCB,
	  FLITE_REG_CIGCTRL_YUV422_1P पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, FLITE_REG_CISRCSIZE_ORDER422_IN_CBYCRY,
	  FLITE_REG_CIGCTRL_YUV422_1P पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, FLITE_REG_CISRCSIZE_ORDER422_IN_CRYCBY,
	  FLITE_REG_CIGCTRL_YUV422_1P पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, 0, FLITE_REG_CIGCTRL_RAW8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, 0, FLITE_REG_CIGCTRL_RAW10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, 0, FLITE_REG_CIGCTRL_RAW12 पूर्ण,
	अणु MEDIA_BUS_FMT_JPEG_1X8, 0, FLITE_REG_CIGCTRL_USER(1) पूर्ण,
पूर्ण;

/* Set camera input pixel क्रमmat and resolution */
व्योम flite_hw_set_source_क्रमmat(काष्ठा fimc_lite *dev, काष्ठा flite_frame *f)
अणु
	u32 pixelcode = f->fmt->mbus_code;
	पूर्णांक i = ARRAY_SIZE(src_pixfmt_map);
	u32 cfg;

	जबतक (--i) अणु
		अगर (src_pixfmt_map[i][0] == pixelcode)
			अवरोध;
	पूर्ण

	अगर (i == 0 && src_pixfmt_map[i][0] != pixelcode) अणु
		v4l2_err(&dev->ve.vdev,
			 "Unsupported pixel code, falling back to %#08x\n",
			 src_pixfmt_map[i][0]);
	पूर्ण

	cfg = पढ़ोl(dev->regs + FLITE_REG_CIGCTRL);
	cfg &= ~FLITE_REG_CIGCTRL_FMT_MASK;
	cfg |= src_pixfmt_map[i][2];
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIGCTRL);

	cfg = पढ़ोl(dev->regs + FLITE_REG_CISRCSIZE);
	cfg &= ~(FLITE_REG_CISRCSIZE_ORDER422_MASK |
		 FLITE_REG_CISRCSIZE_SIZE_CAM_MASK);
	cfg |= (f->f_width << 16) | f->f_height;
	cfg |= src_pixfmt_map[i][1];
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CISRCSIZE);
पूर्ण

/* Set the camera host input winकरोw offsets (cropping) */
व्योम flite_hw_set_winकरोw_offset(काष्ठा fimc_lite *dev, काष्ठा flite_frame *f)
अणु
	u32 hoff2, voff2;
	u32 cfg;

	cfg = पढ़ोl(dev->regs + FLITE_REG_CIWDOFST);
	cfg &= ~FLITE_REG_CIWDOFST_OFST_MASK;
	cfg |= (f->rect.left << 16) | f->rect.top;
	cfg |= FLITE_REG_CIWDOFST_WINOFSEN;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIWDOFST);

	hoff2 = f->f_width - f->rect.width - f->rect.left;
	voff2 = f->f_height - f->rect.height - f->rect.top;

	cfg = (hoff2 << 16) | voff2;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIWDOFST2);
पूर्ण

/* Select camera port (A, B) */
अटल व्योम flite_hw_set_camera_port(काष्ठा fimc_lite *dev, पूर्णांक id)
अणु
	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CIGENERAL);
	अगर (id == 0)
		cfg &= ~FLITE_REG_CIGENERAL_CAM_B;
	अन्यथा
		cfg |= FLITE_REG_CIGENERAL_CAM_B;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIGENERAL);
पूर्ण

/* Select serial or parallel bus, camera port (A,B) and set संकेतs polarity */
व्योम flite_hw_set_camera_bus(काष्ठा fimc_lite *dev,
			     काष्ठा fimc_source_info *si)
अणु
	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CIGCTRL);
	अचिन्हित पूर्णांक flags = si->flags;

	अगर (si->sensor_bus_type != FIMC_BUS_TYPE_MIPI_CSI2) अणु
		cfg &= ~(FLITE_REG_CIGCTRL_SELCAM_MIPI |
			 FLITE_REG_CIGCTRL_INVPOLPCLK |
			 FLITE_REG_CIGCTRL_INVPOLVSYNC |
			 FLITE_REG_CIGCTRL_INVPOLHREF);

		अगर (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
			cfg |= FLITE_REG_CIGCTRL_INVPOLPCLK;

		अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
			cfg |= FLITE_REG_CIGCTRL_INVPOLVSYNC;

		अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
			cfg |= FLITE_REG_CIGCTRL_INVPOLHREF;
	पूर्ण अन्यथा अणु
		cfg |= FLITE_REG_CIGCTRL_SELCAM_MIPI;
	पूर्ण

	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIGCTRL);

	flite_hw_set_camera_port(dev, si->mux_id);
पूर्ण

अटल व्योम flite_hw_set_pack12(काष्ठा fimc_lite *dev, पूर्णांक on)
अणु
	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CIODMAFMT);

	cfg &= ~FLITE_REG_CIODMAFMT_PACK12;

	अगर (on)
		cfg |= FLITE_REG_CIODMAFMT_PACK12;

	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIODMAFMT);
पूर्ण

अटल व्योम flite_hw_set_out_order(काष्ठा fimc_lite *dev, काष्ठा flite_frame *f)
अणु
	अटल स्थिर u32 pixcode[4][2] = अणु
		अणु MEDIA_BUS_FMT_YUYV8_2X8, FLITE_REG_CIODMAFMT_YCBYCR पूर्ण,
		अणु MEDIA_BUS_FMT_YVYU8_2X8, FLITE_REG_CIODMAFMT_YCRYCB पूर्ण,
		अणु MEDIA_BUS_FMT_UYVY8_2X8, FLITE_REG_CIODMAFMT_CBYCRY पूर्ण,
		अणु MEDIA_BUS_FMT_VYUY8_2X8, FLITE_REG_CIODMAFMT_CRYCBY पूर्ण,
	पूर्ण;
	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CIODMAFMT);
	पूर्णांक i = ARRAY_SIZE(pixcode);

	जबतक (--i)
		अगर (pixcode[i][0] == f->fmt->mbus_code)
			अवरोध;
	cfg &= ~FLITE_REG_CIODMAFMT_YCBCR_ORDER_MASK;
	ग_लिखोl(cfg | pixcode[i][1], dev->regs + FLITE_REG_CIODMAFMT);
पूर्ण

व्योम flite_hw_set_dma_winकरोw(काष्ठा fimc_lite *dev, काष्ठा flite_frame *f)
अणु
	u32 cfg;

	/* Maximum output pixel size */
	cfg = पढ़ोl(dev->regs + FLITE_REG_CIOCAN);
	cfg &= ~FLITE_REG_CIOCAN_MASK;
	cfg |= (f->f_height << 16) | f->f_width;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIOCAN);

	/* DMA offsets */
	cfg = पढ़ोl(dev->regs + FLITE_REG_CIOOFF);
	cfg &= ~FLITE_REG_CIOOFF_MASK;
	cfg |= (f->rect.top << 16) | f->rect.left;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIOOFF);
पूर्ण

व्योम flite_hw_set_dma_buffer(काष्ठा fimc_lite *dev, काष्ठा flite_buffer *buf)
अणु
	अचिन्हित पूर्णांक index;
	u32 cfg;

	अगर (dev->dd->max_dma_bufs == 1)
		index = 0;
	अन्यथा
		index = buf->index;

	अगर (index == 0)
		ग_लिखोl(buf->addr, dev->regs + FLITE_REG_CIOSA);
	अन्यथा
		ग_लिखोl(buf->addr, dev->regs + FLITE_REG_CIOSAN(index - 1));

	cfg = पढ़ोl(dev->regs + FLITE_REG_CIFCNTSEQ);
	cfg |= BIT(index);
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIFCNTSEQ);
पूर्ण

व्योम flite_hw_mask_dma_buffer(काष्ठा fimc_lite *dev, u32 index)
अणु
	u32 cfg;

	अगर (dev->dd->max_dma_bufs == 1)
		index = 0;

	cfg = पढ़ोl(dev->regs + FLITE_REG_CIFCNTSEQ);
	cfg &= ~BIT(index);
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIFCNTSEQ);
पूर्ण

/* Enable/disable output DMA, set output pixel size and offsets (composition) */
व्योम flite_hw_set_output_dma(काष्ठा fimc_lite *dev, काष्ठा flite_frame *f,
			     bool enable)
अणु
	u32 cfg = पढ़ोl(dev->regs + FLITE_REG_CIGCTRL);

	अगर (!enable) अणु
		cfg |= FLITE_REG_CIGCTRL_ODMA_DISABLE;
		ग_लिखोl(cfg, dev->regs + FLITE_REG_CIGCTRL);
		वापस;
	पूर्ण

	cfg &= ~FLITE_REG_CIGCTRL_ODMA_DISABLE;
	ग_लिखोl(cfg, dev->regs + FLITE_REG_CIGCTRL);

	flite_hw_set_out_order(dev, f);
	flite_hw_set_dma_winकरोw(dev, f);
	flite_hw_set_pack12(dev, 0);
पूर्ण

व्योम flite_hw_dump_regs(काष्ठा fimc_lite *dev, स्थिर अक्षर *label)
अणु
	काष्ठा अणु
		u32 offset;
		स्थिर अक्षर * स्थिर name;
	पूर्ण रेजिस्टरs[] = अणु
		अणु 0x00, "CISRCSIZE" पूर्ण,
		अणु 0x04, "CIGCTRL" पूर्ण,
		अणु 0x08, "CIIMGCPT" पूर्ण,
		अणु 0x0c, "CICPTSEQ" पूर्ण,
		अणु 0x10, "CIWDOFST" पूर्ण,
		अणु 0x14, "CIWDOFST2" पूर्ण,
		अणु 0x18, "CIODMAFMT" पूर्ण,
		अणु 0x20, "CIOCAN" पूर्ण,
		अणु 0x24, "CIOOFF" पूर्ण,
		अणु 0x30, "CIOSA" पूर्ण,
		अणु 0x40, "CISTATUS" पूर्ण,
		अणु 0x44, "CISTATUS2" पूर्ण,
		अणु 0xf0, "CITHOLD" पूर्ण,
		अणु 0xfc, "CIGENERAL" पूर्ण,
	पूर्ण;
	u32 i;

	v4l2_info(&dev->subdev, "--- %s ---\n", label);

	क्रम (i = 0; i < ARRAY_SIZE(रेजिस्टरs); i++) अणु
		u32 cfg = पढ़ोl(dev->regs + रेजिस्टरs[i].offset);
		v4l2_info(&dev->subdev, "%9s: 0x%08x\n",
			  रेजिस्टरs[i].name, cfg);
	पूर्ण
पूर्ण
