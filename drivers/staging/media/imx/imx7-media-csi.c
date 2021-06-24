<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * V4L2 Capture CSI Subdev क्रम Freescale i.MX6UL/L / i.MX7 SOC
 *
 * Copyright (c) 2019 Linaro Ltd
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gcd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश <media/imx.h>
#समावेश "imx-media.h"

#घोषणा IMX7_CSI_PAD_SINK		0
#घोषणा IMX7_CSI_PAD_SRC		1
#घोषणा IMX7_CSI_PADS_NUM		2

/* csi control reg 1 */
#घोषणा BIT_SWAP16_EN			BIT(31)
#घोषणा BIT_EXT_VSYNC			BIT(30)
#घोषणा BIT_खातापूर्ण_INT_EN			BIT(29)
#घोषणा BIT_PRP_IF_EN			BIT(28)
#घोषणा BIT_CCIR_MODE			BIT(27)
#घोषणा BIT_COF_INT_EN			BIT(26)
#घोषणा BIT_SF_OR_INTEN			BIT(25)
#घोषणा BIT_RF_OR_INTEN			BIT(24)
#घोषणा BIT_SFF_DMA_DONE_INTEN		BIT(22)
#घोषणा BIT_STATFF_INTEN		BIT(21)
#घोषणा BIT_FB2_DMA_DONE_INTEN		BIT(20)
#घोषणा BIT_FB1_DMA_DONE_INTEN		BIT(19)
#घोषणा BIT_RXFF_INTEN			BIT(18)
#घोषणा BIT_SOF_POL			BIT(17)
#घोषणा BIT_SOF_INTEN			BIT(16)
#घोषणा BIT_MCLKDIV(n)			((n) << 12)
#घोषणा BIT_MCLKDIV_MASK		(0xf << 12)
#घोषणा BIT_HSYNC_POL			BIT(11)
#घोषणा BIT_CCIR_EN			BIT(10)
#घोषणा BIT_MCLKEN			BIT(9)
#घोषणा BIT_FCC				BIT(8)
#घोषणा BIT_PACK_सूची			BIT(7)
#घोषणा BIT_CLR_STATFIFO		BIT(6)
#घोषणा BIT_CLR_RXFIFO			BIT(5)
#घोषणा BIT_GCLK_MODE			BIT(4)
#घोषणा BIT_INV_DATA			BIT(3)
#घोषणा BIT_INV_PCLK			BIT(2)
#घोषणा BIT_REDGE			BIT(1)
#घोषणा BIT_PIXEL_BIT			BIT(0)

/* control reg 2 */
#घोषणा BIT_DMA_BURST_TYPE_RFF_INCR4	(1 << 30)
#घोषणा BIT_DMA_BURST_TYPE_RFF_INCR8	(2 << 30)
#घोषणा BIT_DMA_BURST_TYPE_RFF_INCR16	(3 << 30)
#घोषणा BIT_DMA_BURST_TYPE_RFF_MASK	(3 << 30)

/* control reg 3 */
#घोषणा BIT_FRMCNT(n)			((n) << 16)
#घोषणा BIT_FRMCNT_MASK			(0xffff << 16)
#घोषणा BIT_FRMCNT_RST			BIT(15)
#घोषणा BIT_DMA_REFLASH_RFF		BIT(14)
#घोषणा BIT_DMA_REFLASH_SFF		BIT(13)
#घोषणा BIT_DMA_REQ_EN_RFF		BIT(12)
#घोषणा BIT_DMA_REQ_EN_SFF		BIT(11)
#घोषणा BIT_STATFF_LEVEL(n)		((n) << 8)
#घोषणा BIT_STATFF_LEVEL_MASK		(0x7 << 8)
#घोषणा BIT_HRESP_ERR_EN		BIT(7)
#घोषणा BIT_RXFF_LEVEL(n)		((n) << 4)
#घोषणा BIT_RXFF_LEVEL_MASK		(0x7 << 4)
#घोषणा BIT_TWO_8BIT_SENSOR		BIT(3)
#घोषणा BIT_ZERO_PACK_EN		BIT(2)
#घोषणा BIT_ECC_INT_EN			BIT(1)
#घोषणा BIT_ECC_AUTO_EN			BIT(0)

/* csi status reg */
#घोषणा BIT_ADDR_CH_ERR_INT		BIT(28)
#घोषणा BIT_FIELD0_INT			BIT(27)
#घोषणा BIT_FIELD1_INT			BIT(26)
#घोषणा BIT_SFF_OR_INT			BIT(25)
#घोषणा BIT_RFF_OR_INT			BIT(24)
#घोषणा BIT_DMA_TSF_DONE_SFF		BIT(22)
#घोषणा BIT_STATFF_INT			BIT(21)
#घोषणा BIT_DMA_TSF_DONE_FB2		BIT(20)
#घोषणा BIT_DMA_TSF_DONE_FB1		BIT(19)
#घोषणा BIT_RXFF_INT			BIT(18)
#घोषणा BIT_खातापूर्ण_INT			BIT(17)
#घोषणा BIT_SOF_INT			BIT(16)
#घोषणा BIT_F2_INT			BIT(15)
#घोषणा BIT_F1_INT			BIT(14)
#घोषणा BIT_COF_INT			BIT(13)
#घोषणा BIT_HRESP_ERR_INT		BIT(7)
#घोषणा BIT_ECC_INT			BIT(1)
#घोषणा BIT_DRDY			BIT(0)

/* csi image parameter reg */
#घोषणा BIT_IMAGE_WIDTH(n)		((n) << 16)
#घोषणा BIT_IMAGE_HEIGHT(n)		(n)

/* csi control reg 18 */
#घोषणा BIT_CSI_HW_ENABLE		BIT(31)
#घोषणा BIT_MIPI_DATA_FORMAT_RAW8	(0x2a << 25)
#घोषणा BIT_MIPI_DATA_FORMAT_RAW10	(0x2b << 25)
#घोषणा BIT_MIPI_DATA_FORMAT_RAW12	(0x2c << 25)
#घोषणा BIT_MIPI_DATA_FORMAT_RAW14	(0x2d << 25)
#घोषणा BIT_MIPI_DATA_FORMAT_YUV422_8B	(0x1e << 25)
#घोषणा BIT_MIPI_DATA_FORMAT_MASK	(0x3f << 25)
#घोषणा BIT_DATA_FROM_MIPI		BIT(22)
#घोषणा BIT_MIPI_YU_SWAP		BIT(21)
#घोषणा BIT_MIPI_DOUBLE_CMPNT		BIT(20)
#घोषणा BIT_BASEADDR_CHG_ERR_EN		BIT(9)
#घोषणा BIT_BASEADDR_SWITCH_SEL		BIT(5)
#घोषणा BIT_BASEADDR_SWITCH_EN		BIT(4)
#घोषणा BIT_PARALLEL24_EN		BIT(3)
#घोषणा BIT_DEINTERLACE_EN		BIT(2)
#घोषणा BIT_TVDECODER_IN_EN		BIT(1)
#घोषणा BIT_NTSC_EN			BIT(0)

#घोषणा CSI_MCLK_VF			1
#घोषणा CSI_MCLK_ENC			2
#घोषणा CSI_MCLK_RAW			4
#घोषणा CSI_MCLK_I2C			8

#घोषणा CSI_CSICR1			0x00
#घोषणा CSI_CSICR2			0x04
#घोषणा CSI_CSICR3			0x08
#घोषणा CSI_STATFIFO			0x0c
#घोषणा CSI_CSIRXFIFO			0x10
#घोषणा CSI_CSIRXCNT			0x14
#घोषणा CSI_CSISR			0x18

#घोषणा CSI_CSIDBG			0x1c
#घोषणा CSI_CSIDMASA_STATFIFO		0x20
#घोषणा CSI_CSIDMATS_STATFIFO		0x24
#घोषणा CSI_CSIDMASA_FB1		0x28
#घोषणा CSI_CSIDMASA_FB2		0x2c
#घोषणा CSI_CSIFBUF_PARA		0x30
#घोषणा CSI_CSIIMAG_PARA		0x34

#घोषणा CSI_CSICR18			0x48
#घोषणा CSI_CSICR19			0x4c

काष्ठा imx7_csi अणु
	काष्ठा device *dev;
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा imx_media_video_dev *vdev;
	काष्ठा imx_media_dev *imxmd;
	काष्ठा media_pad pad[IMX7_CSI_PADS_NUM];

	/* lock to protect members below */
	काष्ठा mutex lock;
	/* lock to protect irq handler when stop streaming */
	spinlock_t irqlock;

	काष्ठा v4l2_subdev *src_sd;

	काष्ठा v4l2_mbus_framefmt क्रमmat_mbus[IMX7_CSI_PADS_NUM];
	स्थिर काष्ठा imx_media_pixfmt *cc[IMX7_CSI_PADS_NUM];
	काष्ठा v4l2_fract frame_पूर्णांकerval[IMX7_CSI_PADS_NUM];

	व्योम __iomem *regbase;
	पूर्णांक irq;
	काष्ठा clk *mclk;

	/* active vb2 buffers to send to video dev sink */
	काष्ठा imx_media_buffer *active_vb2_buf[2];
	काष्ठा imx_media_dma_buf underrun_buf;

	पूर्णांक buf_num;
	u32 frame_sequence;

	bool last_eof;
	bool is_streaming;
	bool is_csi2;

	काष्ठा completion last_eof_completion;
पूर्ण;

अटल काष्ठा imx7_csi *
imx7_csi_notअगरier_to_dev(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा imx7_csi, notअगरier);
पूर्ण

/* -----------------------------------------------------------------------------
 * Hardware Configuration
 */

अटल u32 imx7_csi_reg_पढ़ो(काष्ठा imx7_csi *csi, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(csi->regbase + offset);
पूर्ण

अटल व्योम imx7_csi_reg_ग_लिखो(काष्ठा imx7_csi *csi, अचिन्हित पूर्णांक value,
			       अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(value, csi->regbase + offset);
पूर्ण

अटल u32 imx7_csi_irq_clear(काष्ठा imx7_csi *csi)
अणु
	u32 isr;

	isr = imx7_csi_reg_पढ़ो(csi, CSI_CSISR);
	imx7_csi_reg_ग_लिखो(csi, isr, CSI_CSISR);

	वापस isr;
पूर्ण

अटल व्योम imx7_csi_init_शेष(काष्ठा imx7_csi *csi)
अणु
	imx7_csi_reg_ग_लिखो(csi, BIT_SOF_POL | BIT_REDGE | BIT_GCLK_MODE |
			   BIT_HSYNC_POL | BIT_FCC | BIT_MCLKDIV(1) |
			   BIT_MCLKEN, CSI_CSICR1);
	imx7_csi_reg_ग_लिखो(csi, 0, CSI_CSICR2);
	imx7_csi_reg_ग_लिखो(csi, BIT_FRMCNT_RST, CSI_CSICR3);

	imx7_csi_reg_ग_लिखो(csi, BIT_IMAGE_WIDTH(800) | BIT_IMAGE_HEIGHT(600),
			   CSI_CSIIMAG_PARA);

	imx7_csi_reg_ग_लिखो(csi, BIT_DMA_REFLASH_RFF, CSI_CSICR3);
पूर्ण

अटल व्योम imx7_csi_hw_enable_irq(काष्ठा imx7_csi *csi)
अणु
	u32 cr1 = imx7_csi_reg_पढ़ो(csi, CSI_CSICR1);

	cr1 |= BIT_RFF_OR_INT;
	cr1 |= BIT_FB1_DMA_DONE_INTEN;
	cr1 |= BIT_FB2_DMA_DONE_INTEN;

	imx7_csi_reg_ग_लिखो(csi, cr1, CSI_CSICR1);
पूर्ण

अटल व्योम imx7_csi_hw_disable_irq(काष्ठा imx7_csi *csi)
अणु
	u32 cr1 = imx7_csi_reg_पढ़ो(csi, CSI_CSICR1);

	cr1 &= ~BIT_RFF_OR_INT;
	cr1 &= ~BIT_FB1_DMA_DONE_INTEN;
	cr1 &= ~BIT_FB2_DMA_DONE_INTEN;

	imx7_csi_reg_ग_लिखो(csi, cr1, CSI_CSICR1);
पूर्ण

अटल व्योम imx7_csi_hw_enable(काष्ठा imx7_csi *csi)
अणु
	u32 cr = imx7_csi_reg_पढ़ो(csi, CSI_CSICR18);

	cr |= BIT_CSI_HW_ENABLE;

	imx7_csi_reg_ग_लिखो(csi, cr, CSI_CSICR18);
पूर्ण

अटल व्योम imx7_csi_hw_disable(काष्ठा imx7_csi *csi)
अणु
	u32 cr = imx7_csi_reg_पढ़ो(csi, CSI_CSICR18);

	cr &= ~BIT_CSI_HW_ENABLE;

	imx7_csi_reg_ग_लिखो(csi, cr, CSI_CSICR18);
पूर्ण

अटल व्योम imx7_csi_dma_reflash(काष्ठा imx7_csi *csi)
अणु
	u32 cr3;

	cr3 = imx7_csi_reg_पढ़ो(csi, CSI_CSICR3);
	cr3 |= BIT_DMA_REFLASH_RFF;
	imx7_csi_reg_ग_लिखो(csi, cr3, CSI_CSICR3);
पूर्ण

अटल व्योम imx7_csi_rx_fअगरo_clear(काष्ठा imx7_csi *csi)
अणु
	u32 cr1 = imx7_csi_reg_पढ़ो(csi, CSI_CSICR1) & ~BIT_FCC;

	imx7_csi_reg_ग_लिखो(csi, cr1, CSI_CSICR1);
	imx7_csi_reg_ग_लिखो(csi, cr1 | BIT_CLR_RXFIFO, CSI_CSICR1);
	imx7_csi_reg_ग_लिखो(csi, cr1 | BIT_FCC, CSI_CSICR1);
पूर्ण

अटल व्योम imx7_csi_dmareq_rff_enable(काष्ठा imx7_csi *csi)
अणु
	u32 cr3 = imx7_csi_reg_पढ़ो(csi, CSI_CSICR3);

	cr3 |= BIT_DMA_REQ_EN_RFF;
	cr3 |= BIT_HRESP_ERR_EN;
	cr3 &= ~BIT_RXFF_LEVEL_MASK;
	cr3 |= BIT_RXFF_LEVEL(2);

	imx7_csi_reg_ग_लिखो(csi, cr3, CSI_CSICR3);
पूर्ण

अटल व्योम imx7_csi_dmareq_rff_disable(काष्ठा imx7_csi *csi)
अणु
	u32 cr3 = imx7_csi_reg_पढ़ो(csi, CSI_CSICR3);

	cr3 &= ~BIT_DMA_REQ_EN_RFF;
	cr3 &= ~BIT_HRESP_ERR_EN;
	imx7_csi_reg_ग_लिखो(csi, cr3, CSI_CSICR3);
पूर्ण

अटल व्योम imx7_csi_update_buf(काष्ठा imx7_csi *csi, dma_addr_t phys,
				पूर्णांक buf_num)
अणु
	अगर (buf_num == 1)
		imx7_csi_reg_ग_लिखो(csi, phys, CSI_CSIDMASA_FB2);
	अन्यथा
		imx7_csi_reg_ग_लिखो(csi, phys, CSI_CSIDMASA_FB1);
पूर्ण

अटल व्योम imx7_csi_setup_vb2_buf(काष्ठा imx7_csi *csi)
अणु
	काष्ठा imx_media_video_dev *vdev = csi->vdev;
	काष्ठा imx_media_buffer *buf;
	काष्ठा vb2_buffer *vb2_buf;
	dma_addr_t phys[2];
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		buf = imx_media_capture_device_next_buf(vdev);
		अगर (buf) अणु
			csi->active_vb2_buf[i] = buf;
			vb2_buf = &buf->vbuf.vb2_buf;
			phys[i] = vb2_dma_contig_plane_dma_addr(vb2_buf, 0);
		पूर्ण अन्यथा अणु
			csi->active_vb2_buf[i] = शून्य;
			phys[i] = csi->underrun_buf.phys;
		पूर्ण

		imx7_csi_update_buf(csi, phys[i], i);
	पूर्ण
पूर्ण

अटल व्योम imx7_csi_dma_unsetup_vb2_buf(काष्ठा imx7_csi *csi,
					 क्रमागत vb2_buffer_state वापस_status)
अणु
	काष्ठा imx_media_buffer *buf;
	पूर्णांक i;

	/* वापस any reमुख्यing active frames with वापस_status */
	क्रम (i = 0; i < 2; i++) अणु
		buf = csi->active_vb2_buf[i];
		अगर (buf) अणु
			काष्ठा vb2_buffer *vb = &buf->vbuf.vb2_buf;

			vb->बारtamp = kसमय_get_ns();
			vb2_buffer_करोne(vb, वापस_status);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक imx7_csi_dma_setup(काष्ठा imx7_csi *csi)
अणु
	काष्ठा imx_media_video_dev *vdev = csi->vdev;
	पूर्णांक ret;

	ret = imx_media_alloc_dma_buf(csi->dev, &csi->underrun_buf,
				      vdev->fmt.sizeimage);
	अगर (ret < 0) अणु
		v4l2_warn(&csi->sd, "consider increasing the CMA area\n");
		वापस ret;
	पूर्ण

	csi->frame_sequence = 0;
	csi->last_eof = false;
	init_completion(&csi->last_eof_completion);

	imx7_csi_setup_vb2_buf(csi);

	वापस 0;
पूर्ण

अटल व्योम imx7_csi_dma_cleanup(काष्ठा imx7_csi *csi)
अणु
	imx7_csi_dma_unsetup_vb2_buf(csi, VB2_BUF_STATE_ERROR);
	imx_media_मुक्त_dma_buf(csi->dev, &csi->underrun_buf);
पूर्ण

अटल व्योम imx7_csi_dma_stop(काष्ठा imx7_csi *csi)
अणु
	अचिन्हित दीर्घ समयout_jअगरfies;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* mark next खातापूर्ण पूर्णांकerrupt as the last beक्रमe stream off */
	spin_lock_irqsave(&csi->irqlock, flags);
	csi->last_eof = true;
	spin_unlock_irqrestore(&csi->irqlock, flags);

	/*
	 * and then रुको क्रम पूर्णांकerrupt handler to mark completion.
	 */
	समयout_jअगरfies = msecs_to_jअगरfies(IMX_MEDIA_खातापूर्ण_TIMEOUT);
	ret = रुको_क्रम_completion_समयout(&csi->last_eof_completion,
					  समयout_jअगरfies);
	अगर (ret == 0)
		v4l2_warn(&csi->sd, "wait last EOF timeout\n");

	imx7_csi_hw_disable_irq(csi);
पूर्ण

अटल व्योम imx7_csi_configure(काष्ठा imx7_csi *csi)
अणु
	काष्ठा imx_media_video_dev *vdev = csi->vdev;
	काष्ठा v4l2_pix_क्रमmat *out_pix = &vdev->fmt;
	पूर्णांक width = out_pix->width;
	u32 stride = 0;
	u32 cr1, cr18;

	cr18 = imx7_csi_reg_पढ़ो(csi, CSI_CSICR18);

	cr18 &= ~(BIT_CSI_HW_ENABLE | BIT_MIPI_DATA_FORMAT_MASK |
		  BIT_DATA_FROM_MIPI | BIT_BASEADDR_CHG_ERR_EN |
		  BIT_BASEADDR_SWITCH_EN | BIT_BASEADDR_SWITCH_SEL |
		  BIT_DEINTERLACE_EN);

	अगर (out_pix->field == V4L2_FIELD_INTERLACED) अणु
		cr18 |= BIT_DEINTERLACE_EN;
		stride = out_pix->width;
	पूर्ण

	अगर (!csi->is_csi2) अणु
		cr1 = BIT_SOF_POL | BIT_REDGE | BIT_GCLK_MODE | BIT_HSYNC_POL
		    | BIT_FCC | BIT_MCLKDIV(1) | BIT_MCLKEN;

		cr18 |= BIT_BASEADDR_SWITCH_EN | BIT_BASEADDR_SWITCH_SEL |
			BIT_BASEADDR_CHG_ERR_EN;

		अगर (out_pix->pixelक्रमmat == V4L2_PIX_FMT_UYVY ||
		    out_pix->pixelक्रमmat == V4L2_PIX_FMT_YUYV)
			width *= 2;
	पूर्ण अन्यथा अणु
		cr1 = BIT_SOF_POL | BIT_REDGE | BIT_HSYNC_POL | BIT_FCC
		    | BIT_MCLKDIV(1) | BIT_MCLKEN;

		cr18 |= BIT_DATA_FROM_MIPI;

		चयन (csi->क्रमmat_mbus[IMX7_CSI_PAD_SINK].code) अणु
		हाल MEDIA_BUS_FMT_Y8_1X8:
		हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		हाल MEDIA_BUS_FMT_SGBRG8_1X8:
		हाल MEDIA_BUS_FMT_SGRBG8_1X8:
		हाल MEDIA_BUS_FMT_SRGGB8_1X8:
			cr18 |= BIT_MIPI_DATA_FORMAT_RAW8;
			अवरोध;
		हाल MEDIA_BUS_FMT_Y10_1X10:
		हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		हाल MEDIA_BUS_FMT_SGBRG10_1X10:
		हाल MEDIA_BUS_FMT_SGRBG10_1X10:
		हाल MEDIA_BUS_FMT_SRGGB10_1X10:
			cr18 |= BIT_MIPI_DATA_FORMAT_RAW10;
			अवरोध;
		हाल MEDIA_BUS_FMT_Y12_1X12:
		हाल MEDIA_BUS_FMT_SBGGR12_1X12:
		हाल MEDIA_BUS_FMT_SGBRG12_1X12:
		हाल MEDIA_BUS_FMT_SGRBG12_1X12:
		हाल MEDIA_BUS_FMT_SRGGB12_1X12:
			cr18 |= BIT_MIPI_DATA_FORMAT_RAW12;
			अवरोध;
		हाल MEDIA_BUS_FMT_Y14_1X14:
		हाल MEDIA_BUS_FMT_SBGGR14_1X14:
		हाल MEDIA_BUS_FMT_SGBRG14_1X14:
		हाल MEDIA_BUS_FMT_SGRBG14_1X14:
		हाल MEDIA_BUS_FMT_SRGGB14_1X14:
			cr18 |= BIT_MIPI_DATA_FORMAT_RAW14;
			अवरोध;
		/*
		 * CSI-2 sources are supposed to use the 1X16 क्रमmats, but not
		 * all of them comply. Support both variants.
		 */
		हाल MEDIA_BUS_FMT_UYVY8_2X8:
		हाल MEDIA_BUS_FMT_UYVY8_1X16:
		हाल MEDIA_BUS_FMT_YUYV8_2X8:
		हाल MEDIA_BUS_FMT_YUYV8_1X16:
			cr18 |= BIT_MIPI_DATA_FORMAT_YUV422_8B;
			अवरोध;
		पूर्ण

		चयन (out_pix->pixelक्रमmat) अणु
		हाल V4L2_PIX_FMT_Y10:
		हाल V4L2_PIX_FMT_Y12:
		हाल V4L2_PIX_FMT_SBGGR8:
		हाल V4L2_PIX_FMT_SGBRG8:
		हाल V4L2_PIX_FMT_SGRBG8:
		हाल V4L2_PIX_FMT_SRGGB8:
		हाल V4L2_PIX_FMT_SBGGR16:
		हाल V4L2_PIX_FMT_SGBRG16:
		हाल V4L2_PIX_FMT_SGRBG16:
		हाल V4L2_PIX_FMT_SRGGB16:
			cr1 |= BIT_PIXEL_BIT;
			अवरोध;
		पूर्ण
	पूर्ण

	imx7_csi_reg_ग_लिखो(csi, cr1, CSI_CSICR1);
	imx7_csi_reg_ग_लिखो(csi, BIT_DMA_BURST_TYPE_RFF_INCR16, CSI_CSICR2);
	imx7_csi_reg_ग_लिखो(csi, BIT_FRMCNT_RST, CSI_CSICR3);
	imx7_csi_reg_ग_लिखो(csi, cr18, CSI_CSICR18);

	imx7_csi_reg_ग_लिखो(csi, (width * out_pix->height) >> 2, CSI_CSIRXCNT);
	imx7_csi_reg_ग_लिखो(csi, BIT_IMAGE_WIDTH(width) |
			   BIT_IMAGE_HEIGHT(out_pix->height),
			   CSI_CSIIMAG_PARA);
	imx7_csi_reg_ग_लिखो(csi, stride, CSI_CSIFBUF_PARA);
पूर्ण

अटल पूर्णांक imx7_csi_init(काष्ठा imx7_csi *csi)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(csi->mclk);
	अगर (ret < 0)
		वापस ret;

	imx7_csi_configure(csi);

	ret = imx7_csi_dma_setup(csi);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम imx7_csi_deinit(काष्ठा imx7_csi *csi)
अणु
	imx7_csi_dma_cleanup(csi);
	imx7_csi_init_शेष(csi);
	imx7_csi_dmareq_rff_disable(csi);
	clk_disable_unprepare(csi->mclk);
पूर्ण

अटल व्योम imx7_csi_enable(काष्ठा imx7_csi *csi)
अणु
	/* Clear the Rx FIFO and reflash the DMA controller. */
	imx7_csi_rx_fअगरo_clear(csi);
	imx7_csi_dma_reflash(csi);

	usleep_range(2000, 3000);

	/* Clear and enable the पूर्णांकerrupts. */
	imx7_csi_irq_clear(csi);
	imx7_csi_hw_enable_irq(csi);

	/* Enable the RxFIFO DMA and the CSI. */
	imx7_csi_dmareq_rff_enable(csi);
	imx7_csi_hw_enable(csi);
पूर्ण

अटल व्योम imx7_csi_disable(काष्ठा imx7_csi *csi)
अणु
	imx7_csi_dma_stop(csi);

	imx7_csi_dmareq_rff_disable(csi);

	imx7_csi_hw_disable_irq(csi);

	imx7_csi_hw_disable(csi);
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt Handling
 */

अटल व्योम imx7_csi_error_recovery(काष्ठा imx7_csi *csi)
अणु
	imx7_csi_hw_disable(csi);

	imx7_csi_rx_fअगरo_clear(csi);

	imx7_csi_dma_reflash(csi);

	imx7_csi_hw_enable(csi);
पूर्ण

अटल व्योम imx7_csi_vb2_buf_करोne(काष्ठा imx7_csi *csi)
अणु
	काष्ठा imx_media_video_dev *vdev = csi->vdev;
	काष्ठा imx_media_buffer *करोne, *next;
	काष्ठा vb2_buffer *vb;
	dma_addr_t phys;

	करोne = csi->active_vb2_buf[csi->buf_num];
	अगर (करोne) अणु
		करोne->vbuf.field = vdev->fmt.field;
		करोne->vbuf.sequence = csi->frame_sequence;
		vb = &करोne->vbuf.vb2_buf;
		vb->बारtamp = kसमय_get_ns();
		vb2_buffer_करोne(vb, VB2_BUF_STATE_DONE);
	पूर्ण
	csi->frame_sequence++;

	/* get next queued buffer */
	next = imx_media_capture_device_next_buf(vdev);
	अगर (next) अणु
		phys = vb2_dma_contig_plane_dma_addr(&next->vbuf.vb2_buf, 0);
		csi->active_vb2_buf[csi->buf_num] = next;
	पूर्ण अन्यथा अणु
		phys = csi->underrun_buf.phys;
		csi->active_vb2_buf[csi->buf_num] = शून्य;
	पूर्ण

	imx7_csi_update_buf(csi, phys, csi->buf_num);
पूर्ण

अटल irqवापस_t imx7_csi_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा imx7_csi *csi =  data;
	u32 status;

	spin_lock(&csi->irqlock);

	status = imx7_csi_irq_clear(csi);

	अगर (status & BIT_RFF_OR_INT) अणु
		dev_warn(csi->dev, "Rx fifo overflow\n");
		imx7_csi_error_recovery(csi);
	पूर्ण

	अगर (status & BIT_HRESP_ERR_INT) अणु
		dev_warn(csi->dev, "Hresponse error detected\n");
		imx7_csi_error_recovery(csi);
	पूर्ण

	अगर (status & BIT_ADDR_CH_ERR_INT) अणु
		imx7_csi_hw_disable(csi);

		imx7_csi_dma_reflash(csi);

		imx7_csi_hw_enable(csi);
	पूर्ण

	अगर ((status & BIT_DMA_TSF_DONE_FB1) &&
	    (status & BIT_DMA_TSF_DONE_FB2)) अणु
		/*
		 * For both FB1 and FB2 पूर्णांकerrupter bits set हाल,
		 * CSI DMA is work in one of FB1 and FB2 buffer,
		 * but software can not know the state.
		 * Skip it to aव्योम base address updated
		 * when csi work in field0 and field1 will ग_लिखो to
		 * new base address.
		 */
	पूर्ण अन्यथा अगर (status & BIT_DMA_TSF_DONE_FB1) अणु
		csi->buf_num = 0;
	पूर्ण अन्यथा अगर (status & BIT_DMA_TSF_DONE_FB2) अणु
		csi->buf_num = 1;
	पूर्ण

	अगर ((status & BIT_DMA_TSF_DONE_FB1) ||
	    (status & BIT_DMA_TSF_DONE_FB2)) अणु
		imx7_csi_vb2_buf_करोne(csi);

		अगर (csi->last_eof) अणु
			complete(&csi->last_eof_completion);
			csi->last_eof = false;
		पूर्ण
	पूर्ण

	spin_unlock(&csi->irqlock);

	वापस IRQ_HANDLED;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdev Operations
 */

अटल पूर्णांक imx7_csi_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा imx7_csi *csi = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	mutex_lock(&csi->lock);

	अगर (!csi->src_sd) अणु
		ret = -EPIPE;
		जाओ out_unlock;
	पूर्ण

	अगर (csi->is_streaming == !!enable)
		जाओ out_unlock;

	अगर (enable) अणु
		ret = imx7_csi_init(csi);
		अगर (ret < 0)
			जाओ out_unlock;

		ret = v4l2_subdev_call(csi->src_sd, video, s_stream, 1);
		अगर (ret < 0) अणु
			imx7_csi_deinit(csi);
			जाओ out_unlock;
		पूर्ण

		imx7_csi_enable(csi);
	पूर्ण अन्यथा अणु
		imx7_csi_disable(csi);

		v4l2_subdev_call(csi->src_sd, video, s_stream, 0);

		imx7_csi_deinit(csi);
	पूर्ण

	csi->is_streaming = !!enable;

out_unlock:
	mutex_unlock(&csi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक imx7_csi_init_cfg(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा imx7_csi *csi = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < IMX7_CSI_PADS_NUM; i++) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, i);

		ret = imx_media_init_mbus_fmt(mf, 800, 600, 0, V4L2_FIELD_NONE,
					      &csi->cc[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
imx7_csi_get_क्रमmat(काष्ठा imx7_csi *csi,
		    काष्ठा v4l2_subdev_pad_config *cfg,
		    अचिन्हित पूर्णांक pad,
		    क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&csi->sd, cfg, pad);

	वापस &csi->क्रमmat_mbus[pad];
पूर्ण

अटल पूर्णांक imx7_csi_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा imx7_csi *csi = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *in_fmt;
	पूर्णांक ret = 0;

	mutex_lock(&csi->lock);

	in_fmt = imx7_csi_get_क्रमmat(csi, cfg, IMX7_CSI_PAD_SINK, code->which);

	चयन (code->pad) अणु
	हाल IMX7_CSI_PAD_SINK:
		ret = imx_media_क्रमागत_mbus_क्रमmats(&code->code, code->index,
						  PIXFMT_SEL_ANY);
		अवरोध;
	हाल IMX7_CSI_PAD_SRC:
		अगर (code->index != 0) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		code->code = in_fmt->code;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

out_unlock:
	mutex_unlock(&csi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक imx7_csi_get_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा imx7_csi *csi = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक ret = 0;

	mutex_lock(&csi->lock);

	fmt = imx7_csi_get_क्रमmat(csi, cfg, sdक्रमmat->pad, sdक्रमmat->which);
	अगर (!fmt) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	sdक्रमmat->क्रमmat = *fmt;

out_unlock:
	mutex_unlock(&csi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक imx7_csi_try_fmt(काष्ठा imx7_csi *csi,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat,
			    स्थिर काष्ठा imx_media_pixfmt **cc)
अणु
	स्थिर काष्ठा imx_media_pixfmt *in_cc;
	काष्ठा v4l2_mbus_framefmt *in_fmt;
	u32 code;

	in_fmt = imx7_csi_get_क्रमmat(csi, cfg, IMX7_CSI_PAD_SINK,
				     sdक्रमmat->which);
	अगर (!in_fmt)
		वापस -EINVAL;

	चयन (sdक्रमmat->pad) अणु
	हाल IMX7_CSI_PAD_SRC:
		in_cc = imx_media_find_mbus_क्रमmat(in_fmt->code,
						   PIXFMT_SEL_ANY);

		sdक्रमmat->क्रमmat.width = in_fmt->width;
		sdक्रमmat->क्रमmat.height = in_fmt->height;
		sdक्रमmat->क्रमmat.code = in_fmt->code;
		sdक्रमmat->क्रमmat.field = in_fmt->field;
		*cc = in_cc;

		sdक्रमmat->क्रमmat.colorspace = in_fmt->colorspace;
		sdक्रमmat->क्रमmat.xfer_func = in_fmt->xfer_func;
		sdक्रमmat->क्रमmat.quantization = in_fmt->quantization;
		sdक्रमmat->क्रमmat.ycbcr_enc = in_fmt->ycbcr_enc;
		अवरोध;
	हाल IMX7_CSI_PAD_SINK:
		*cc = imx_media_find_mbus_क्रमmat(sdक्रमmat->क्रमmat.code,
						 PIXFMT_SEL_ANY);
		अगर (!*cc) अणु
			imx_media_क्रमागत_mbus_क्रमmats(&code, 0,
						    PIXFMT_SEL_YUV_RGB);
			*cc = imx_media_find_mbus_क्रमmat(code,
							 PIXFMT_SEL_YUV_RGB);
			sdक्रमmat->क्रमmat.code = (*cc)->codes[0];
		पूर्ण

		अगर (sdक्रमmat->क्रमmat.field != V4L2_FIELD_INTERLACED)
			sdक्रमmat->क्रमmat.field = V4L2_FIELD_NONE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	imx_media_try_colorimetry(&sdक्रमmat->क्रमmat, false);

	वापस 0;
पूर्ण

अटल पूर्णांक imx7_csi_set_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा imx7_csi *csi = v4l2_get_subdevdata(sd);
	स्थिर काष्ठा imx_media_pixfmt *outcc;
	काष्ठा v4l2_mbus_framefmt *outfmt;
	स्थिर काष्ठा imx_media_pixfmt *cc;
	काष्ठा v4l2_mbus_framefmt *fmt;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;
	पूर्णांक ret = 0;

	अगर (sdक्रमmat->pad >= IMX7_CSI_PADS_NUM)
		वापस -EINVAL;

	mutex_lock(&csi->lock);

	अगर (csi->is_streaming) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	ret = imx7_csi_try_fmt(csi, cfg, sdक्रमmat, &cc);
	अगर (ret < 0)
		जाओ out_unlock;

	fmt = imx7_csi_get_क्रमmat(csi, cfg, sdक्रमmat->pad, sdक्रमmat->which);
	अगर (!fmt) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	*fmt = sdक्रमmat->क्रमmat;

	अगर (sdक्रमmat->pad == IMX7_CSI_PAD_SINK) अणु
		/* propagate क्रमmat to source pads */
		क्रमmat.pad = IMX7_CSI_PAD_SRC;
		क्रमmat.which = sdक्रमmat->which;
		क्रमmat.क्रमmat = sdक्रमmat->क्रमmat;
		अगर (imx7_csi_try_fmt(csi, cfg, &क्रमmat, &outcc)) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		outfmt = imx7_csi_get_क्रमmat(csi, cfg, IMX7_CSI_PAD_SRC,
					     sdक्रमmat->which);
		*outfmt = क्रमmat.क्रमmat;

		अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
			csi->cc[IMX7_CSI_PAD_SRC] = outcc;
	पूर्ण

	अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		csi->cc[sdक्रमmat->pad] = cc;

out_unlock:
	mutex_unlock(&csi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक imx7_csi_pad_link_validate(काष्ठा v4l2_subdev *sd,
				      काष्ठा media_link *link,
				      काष्ठा v4l2_subdev_क्रमmat *source_fmt,
				      काष्ठा v4l2_subdev_क्रमmat *sink_fmt)
अणु
	काष्ठा imx7_csi *csi = v4l2_get_subdevdata(sd);
	काष्ठा imx_media_video_dev *vdev = csi->vdev;
	स्थिर काष्ठा v4l2_pix_क्रमmat *out_pix = &vdev->fmt;
	काष्ठा media_pad *pad;
	पूर्णांक ret;

	अगर (!csi->src_sd)
		वापस -EPIPE;

	/*
	 * Validate the source link, and record whether the source uses the
	 * parallel input or the CSI-2 receiver.
	 */
	ret = v4l2_subdev_link_validate_शेष(sd, link, source_fmt, sink_fmt);
	अगर (ret)
		वापस ret;

	चयन (csi->src_sd->entity.function) अणु
	हाल MEDIA_ENT_F_VID_IF_BRIDGE:
		/* The input is the CSI-2 receiver. */
		csi->is_csi2 = true;
		अवरोध;

	हाल MEDIA_ENT_F_VID_MUX:
		/* The input is the mux, check its input. */
		pad = imx_media_pipeline_pad(&csi->src_sd->entity, 0, 0, true);
		अगर (!pad)
			वापस -ENODEV;

		csi->is_csi2 = pad->entity->function == MEDIA_ENT_F_VID_IF_BRIDGE;
		अवरोध;

	शेष:
		/*
		 * The input is an बाह्यal entity, it must use the parallel
		 * bus.
		 */
		csi->is_csi2 = false;
		अवरोध;
	पूर्ण

	/* Validate the sink link, ensure the pixel क्रमmat is supported. */
	चयन (out_pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_GREY:
	हाल V4L2_PIX_FMT_Y10:
	हाल V4L2_PIX_FMT_Y12:
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
	हाल V4L2_PIX_FMT_SBGGR16:
	हाल V4L2_PIX_FMT_SGBRG16:
	हाल V4L2_PIX_FMT_SGRBG16:
	हाल V4L2_PIX_FMT_SRGGB16:
		अवरोध;

	शेष:
		dev_dbg(csi->dev, "Invalid capture pixel format 0x%08x\n",
			out_pix->pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx7_csi_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा imx7_csi *csi = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < IMX7_CSI_PADS_NUM; i++) अणु
		/* set a शेष mbus क्रमmat  */
		ret = imx_media_init_mbus_fmt(&csi->क्रमmat_mbus[i],
					      800, 600, 0, V4L2_FIELD_NONE,
					      &csi->cc[i]);
		अगर (ret < 0)
			वापस ret;

		/* init शेष frame पूर्णांकerval */
		csi->frame_पूर्णांकerval[i].numerator = 1;
		csi->frame_पूर्णांकerval[i].denominator = 30;
	पूर्ण

	csi->vdev = imx_media_capture_device_init(csi->sd.dev, &csi->sd,
						  IMX7_CSI_PAD_SRC, false);
	अगर (IS_ERR(csi->vdev))
		वापस PTR_ERR(csi->vdev);

	ret = imx_media_capture_device_रेजिस्टर(csi->vdev,
						MEDIA_LNK_FL_IMMUTABLE);
	अगर (ret)
		imx_media_capture_device_हटाओ(csi->vdev);

	वापस ret;
पूर्ण

अटल व्योम imx7_csi_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा imx7_csi *csi = v4l2_get_subdevdata(sd);

	imx_media_capture_device_unरेजिस्टर(csi->vdev);
	imx_media_capture_device_हटाओ(csi->vdev);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops imx7_csi_video_ops = अणु
	.s_stream	= imx7_csi_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops imx7_csi_pad_ops = अणु
	.init_cfg	= imx7_csi_init_cfg,
	.क्रमागत_mbus_code	= imx7_csi_क्रमागत_mbus_code,
	.get_fmt	= imx7_csi_get_fmt,
	.set_fmt	= imx7_csi_set_fmt,
	.link_validate	= imx7_csi_pad_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops imx7_csi_subdev_ops = अणु
	.video		= &imx7_csi_video_ops,
	.pad		= &imx7_csi_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops imx7_csi_पूर्णांकernal_ops = अणु
	.रेजिस्टरed	= imx7_csi_रेजिस्टरed,
	.unरेजिस्टरed	= imx7_csi_unरेजिस्टरed,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media Entity Operations
 */

अटल स्थिर काष्ठा media_entity_operations imx7_csi_entity_ops = अणु
	.link_validate	= v4l2_subdev_link_validate,
	.get_fwnode_pad = v4l2_subdev_get_fwnode_pad_1_to_1,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe & Remove
 */

अटल पूर्णांक imx7_csi_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				 काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा imx7_csi *csi = imx7_csi_notअगरier_to_dev(notअगरier);
	काष्ठा media_pad *sink = &csi->sd.entity.pads[IMX7_CSI_PAD_SINK];

	/*
	 * If the subdev is a video mux, it must be one of the CSI
	 * muxes. Mark it as such via its group id.
	 */
	अगर (sd->entity.function == MEDIA_ENT_F_VID_MUX)
		sd->grp_id = IMX_MEDIA_GRP_ID_CSI_MUX;

	csi->src_sd = sd;

	वापस v4l2_create_fwnode_links_to_pad(sd, sink, MEDIA_LNK_FL_ENABLED |
					       MEDIA_LNK_FL_IMMUTABLE);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations imx7_csi_notअगरy_ops = अणु
	.bound = imx7_csi_notअगरy_bound,
पूर्ण;

अटल पूर्णांक imx7_csi_async_रेजिस्टर(काष्ठा imx7_csi *csi)
अणु
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा fwnode_handle *ep;
	पूर्णांक ret;

	v4l2_async_notअगरier_init(&csi->notअगरier);

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(csi->dev), 0, 0,
					     FWNODE_GRAPH_ENDPOINT_NEXT);
	अगर (ep) अणु
		asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
			&csi->notअगरier, ep, काष्ठा v4l2_async_subdev);

		fwnode_handle_put(ep);

		अगर (IS_ERR(asd)) अणु
			ret = PTR_ERR(asd);
			/* OK अगर asd alपढ़ोy exists */
			अगर (ret != -EEXIST)
				वापस ret;
		पूर्ण
	पूर्ण

	csi->notअगरier.ops = &imx7_csi_notअगरy_ops;

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(&csi->sd, &csi->notअगरier);
	अगर (ret)
		वापस ret;

	वापस v4l2_async_रेजिस्टर_subdev(&csi->sd);
पूर्ण

अटल पूर्णांक imx7_csi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा imx_media_dev *imxmd;
	काष्ठा imx7_csi *csi;
	पूर्णांक i, ret;

	csi = devm_kzalloc(&pdev->dev, माप(*csi), GFP_KERNEL);
	अगर (!csi)
		वापस -ENOMEM;

	csi->dev = dev;

	csi->mclk = devm_clk_get(&pdev->dev, "mclk");
	अगर (IS_ERR(csi->mclk)) अणु
		ret = PTR_ERR(csi->mclk);
		dev_err(dev, "Failed to get mclk: %d", ret);
		वापस ret;
	पूर्ण

	csi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (csi->irq < 0)
		वापस csi->irq;

	csi->regbase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(csi->regbase))
		वापस PTR_ERR(csi->regbase);

	spin_lock_init(&csi->irqlock);
	mutex_init(&csi->lock);

	/* install पूर्णांकerrupt handler */
	ret = devm_request_irq(dev, csi->irq, imx7_csi_irq_handler, 0, "csi",
			       (व्योम *)csi);
	अगर (ret < 0) अणु
		dev_err(dev, "Request CSI IRQ failed.\n");
		जाओ destroy_mutex;
	पूर्ण

	/* add media device */
	imxmd = imx_media_dev_init(dev, शून्य);
	अगर (IS_ERR(imxmd)) अणु
		ret = PTR_ERR(imxmd);
		जाओ destroy_mutex;
	पूर्ण
	platक्रमm_set_drvdata(pdev, &csi->sd);

	ret = imx_media_of_add_csi(imxmd, node);
	अगर (ret < 0 && ret != -ENODEV && ret != -EEXIST)
		जाओ cleanup;

	ret = imx_media_dev_notअगरier_रेजिस्टर(imxmd, शून्य);
	अगर (ret < 0)
		जाओ cleanup;

	csi->imxmd = imxmd;
	v4l2_subdev_init(&csi->sd, &imx7_csi_subdev_ops);
	v4l2_set_subdevdata(&csi->sd, csi);
	csi->sd.पूर्णांकernal_ops = &imx7_csi_पूर्णांकernal_ops;
	csi->sd.entity.ops = &imx7_csi_entity_ops;
	csi->sd.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	csi->sd.dev = &pdev->dev;
	csi->sd.owner = THIS_MODULE;
	csi->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE;
	csi->sd.grp_id = IMX_MEDIA_GRP_ID_CSI;
	snम_लिखो(csi->sd.name, माप(csi->sd.name), "csi");

	क्रम (i = 0; i < IMX7_CSI_PADS_NUM; i++)
		csi->pad[i].flags = (i == IMX7_CSI_PAD_SINK) ?
			MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&csi->sd.entity, IMX7_CSI_PADS_NUM,
				     csi->pad);
	अगर (ret < 0)
		जाओ cleanup;

	ret = imx7_csi_async_रेजिस्टर(csi);
	अगर (ret)
		जाओ subdev_notअगरier_cleanup;

	वापस 0;

subdev_notअगरier_cleanup:
	v4l2_async_notअगरier_unरेजिस्टर(&csi->notअगरier);
	v4l2_async_notअगरier_cleanup(&csi->notअगरier);

cleanup:
	v4l2_async_notअगरier_unरेजिस्टर(&imxmd->notअगरier);
	v4l2_async_notअगरier_cleanup(&imxmd->notअगरier);
	v4l2_device_unरेजिस्टर(&imxmd->v4l2_dev);
	media_device_unरेजिस्टर(&imxmd->md);
	media_device_cleanup(&imxmd->md);

destroy_mutex:
	mutex_destroy(&csi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक imx7_csi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_subdev *sd = platक्रमm_get_drvdata(pdev);
	काष्ठा imx7_csi *csi = v4l2_get_subdevdata(sd);
	काष्ठा imx_media_dev *imxmd = csi->imxmd;

	v4l2_async_notअगरier_unरेजिस्टर(&imxmd->notअगरier);
	v4l2_async_notअगरier_cleanup(&imxmd->notअगरier);

	media_device_unरेजिस्टर(&imxmd->md);
	v4l2_device_unरेजिस्टर(&imxmd->v4l2_dev);
	media_device_cleanup(&imxmd->md);

	v4l2_async_notअगरier_unरेजिस्टर(&csi->notअगरier);
	v4l2_async_notअगरier_cleanup(&csi->notअगरier);
	v4l2_async_unरेजिस्टर_subdev(sd);

	mutex_destroy(&csi->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx7_csi_of_match[] = अणु
	अणु .compatible = "fsl,imx7-csi" पूर्ण,
	अणु .compatible = "fsl,imx6ul-csi" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx7_csi_of_match);

अटल काष्ठा platक्रमm_driver imx7_csi_driver = अणु
	.probe = imx7_csi_probe,
	.हटाओ = imx7_csi_हटाओ,
	.driver = अणु
		.of_match_table = imx7_csi_of_match,
		.name = "imx7-csi",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx7_csi_driver);

MODULE_DESCRIPTION("i.MX7 CSI subdev driver");
MODULE_AUTHOR("Rui Miguel Silva <rui.silva@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx7-csi");
