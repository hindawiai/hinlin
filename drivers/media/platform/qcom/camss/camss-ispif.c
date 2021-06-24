<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-ispअगर.c
 *
 * Qualcomm MSM Camera Subप्रणाली - ISPIF (ISP Interface) Module
 *
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "camss-ispif.h"
#समावेश "camss.h"

#घोषणा MSM_ISPIF_NAME "msm_ispif"

#घोषणा ISPIF_RST_CMD_0			0x008
#घोषणा ISPIF_RST_CMD_1			0x00c
#घोषणा ISPIF_RST_CMD_0_STROBED_RST_EN		(1 << 0)
#घोषणा ISPIF_RST_CMD_0_MISC_LOGIC_RST		(1 << 1)
#घोषणा ISPIF_RST_CMD_0_SW_REG_RST		(1 << 2)
#घोषणा ISPIF_RST_CMD_0_PIX_INTF_0_CSID_RST	(1 << 3)
#घोषणा ISPIF_RST_CMD_0_PIX_INTF_0_VFE_RST	(1 << 4)
#घोषणा ISPIF_RST_CMD_0_PIX_INTF_1_CSID_RST	(1 << 5)
#घोषणा ISPIF_RST_CMD_0_PIX_INTF_1_VFE_RST	(1 << 6)
#घोषणा ISPIF_RST_CMD_0_RDI_INTF_0_CSID_RST	(1 << 7)
#घोषणा ISPIF_RST_CMD_0_RDI_INTF_0_VFE_RST	(1 << 8)
#घोषणा ISPIF_RST_CMD_0_RDI_INTF_1_CSID_RST	(1 << 9)
#घोषणा ISPIF_RST_CMD_0_RDI_INTF_1_VFE_RST	(1 << 10)
#घोषणा ISPIF_RST_CMD_0_RDI_INTF_2_CSID_RST	(1 << 11)
#घोषणा ISPIF_RST_CMD_0_RDI_INTF_2_VFE_RST	(1 << 12)
#घोषणा ISPIF_RST_CMD_0_PIX_OUTPUT_0_MISR_RST	(1 << 16)
#घोषणा ISPIF_RST_CMD_0_RDI_OUTPUT_0_MISR_RST	(1 << 17)
#घोषणा ISPIF_RST_CMD_0_RDI_OUTPUT_1_MISR_RST	(1 << 18)
#घोषणा ISPIF_RST_CMD_0_RDI_OUTPUT_2_MISR_RST	(1 << 19)
#घोषणा ISPIF_IRQ_GLOBAL_CLEAR_CMD	0x01c
#घोषणा ISPIF_VFE_m_CTRL_0(m)		(0x200 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_CTRL_0_PIX0_LINE_BUF_EN	(1 << 6)
#घोषणा ISPIF_VFE_m_IRQ_MASK_0(m)	(0x208 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_IRQ_MASK_0_PIX0_ENABLE	0x00001249
#घोषणा ISPIF_VFE_m_IRQ_MASK_0_PIX0_MASK	0x00001fff
#घोषणा ISPIF_VFE_m_IRQ_MASK_0_RDI0_ENABLE	0x02492000
#घोषणा ISPIF_VFE_m_IRQ_MASK_0_RDI0_MASK	0x03ffe000
#घोषणा ISPIF_VFE_m_IRQ_MASK_1(m)	(0x20c + 0x200 * (m))
#घोषणा ISPIF_VFE_m_IRQ_MASK_1_PIX1_ENABLE	0x00001249
#घोषणा ISPIF_VFE_m_IRQ_MASK_1_PIX1_MASK	0x00001fff
#घोषणा ISPIF_VFE_m_IRQ_MASK_1_RDI1_ENABLE	0x02492000
#घोषणा ISPIF_VFE_m_IRQ_MASK_1_RDI1_MASK	0x03ffe000
#घोषणा ISPIF_VFE_m_IRQ_MASK_2(m)	(0x210 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_IRQ_MASK_2_RDI2_ENABLE	0x00001249
#घोषणा ISPIF_VFE_m_IRQ_MASK_2_RDI2_MASK	0x00001fff
#घोषणा ISPIF_VFE_m_IRQ_STATUS_0(m)	(0x21c + 0x200 * (m))
#घोषणा ISPIF_VFE_m_IRQ_STATUS_0_PIX0_OVERFLOW	(1 << 12)
#घोषणा ISPIF_VFE_m_IRQ_STATUS_0_RDI0_OVERFLOW	(1 << 25)
#घोषणा ISPIF_VFE_m_IRQ_STATUS_1(m)	(0x220 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_IRQ_STATUS_1_PIX1_OVERFLOW	(1 << 12)
#घोषणा ISPIF_VFE_m_IRQ_STATUS_1_RDI1_OVERFLOW	(1 << 25)
#घोषणा ISPIF_VFE_m_IRQ_STATUS_2(m)	(0x224 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_IRQ_STATUS_2_RDI2_OVERFLOW	(1 << 12)
#घोषणा ISPIF_VFE_m_IRQ_CLEAR_0(m)	(0x230 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_IRQ_CLEAR_1(m)	(0x234 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_IRQ_CLEAR_2(m)	(0x238 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_INTF_INPUT_SEL(m)	(0x244 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_INTF_CMD_0(m)	(0x248 + 0x200 * (m))
#घोषणा ISPIF_VFE_m_INTF_CMD_1(m)	(0x24c + 0x200 * (m))
#घोषणा ISPIF_VFE_m_PIX_INTF_n_CID_MASK(m, n)	\
					(0x254 + 0x200 * (m) + 0x4 * (n))
#घोषणा ISPIF_VFE_m_RDI_INTF_n_CID_MASK(m, n)	\
					(0x264 + 0x200 * (m) + 0x4 * (n))
/* PACK_CFG रेजिस्टरs are 8x96 only */
#घोषणा ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_0(m, n)	\
					(0x270 + 0x200 * (m) + 0x4 * (n))
#घोषणा ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_1(m, n)	\
					(0x27c + 0x200 * (m) + 0x4 * (n))
#घोषणा ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_0_CID_c_PLAIN(c)	\
					(1 << ((cid % 8) * 4))
#घोषणा ISPIF_VFE_m_PIX_INTF_n_STATUS(m, n)	\
					(0x2c0 + 0x200 * (m) + 0x4 * (n))
#घोषणा ISPIF_VFE_m_RDI_INTF_n_STATUS(m, n)	\
					(0x2d0 + 0x200 * (m) + 0x4 * (n))

#घोषणा CSI_PIX_CLK_MUX_SEL		0x000
#घोषणा CSI_RDI_CLK_MUX_SEL		0x008

#घोषणा ISPIF_TIMEOUT_SLEEP_US		1000
#घोषणा ISPIF_TIMEOUT_ALL_US		1000000
#घोषणा ISPIF_RESET_TIMEOUT_MS		500

क्रमागत ispअगर_पूर्णांकf_cmd अणु
	CMD_DISABLE_FRAME_BOUNDARY = 0x0,
	CMD_ENABLE_FRAME_BOUNDARY = 0x1,
	CMD_DISABLE_IMMEDIATELY = 0x2,
	CMD_ALL_DISABLE_IMMEDIATELY = 0xaaaaaaaa,
	CMD_ALL_NO_CHANGE = 0xffffffff,
पूर्ण;

अटल स्थिर u32 ispअगर_क्रमmats_8x16[] = अणु
	MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_VYUY8_2X8,
	MEDIA_BUS_FMT_YUYV8_2X8,
	MEDIA_BUS_FMT_YVYU8_2X8,
	MEDIA_BUS_FMT_SBGGR8_1X8,
	MEDIA_BUS_FMT_SGBRG8_1X8,
	MEDIA_BUS_FMT_SGRBG8_1X8,
	MEDIA_BUS_FMT_SRGGB8_1X8,
	MEDIA_BUS_FMT_SBGGR10_1X10,
	MEDIA_BUS_FMT_SGBRG10_1X10,
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SRGGB10_1X10,
	MEDIA_BUS_FMT_SBGGR12_1X12,
	MEDIA_BUS_FMT_SGBRG12_1X12,
	MEDIA_BUS_FMT_SGRBG12_1X12,
	MEDIA_BUS_FMT_SRGGB12_1X12,
	MEDIA_BUS_FMT_Y10_1X10,
पूर्ण;

अटल स्थिर u32 ispअगर_क्रमmats_8x96[] = अणु
	MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_VYUY8_2X8,
	MEDIA_BUS_FMT_YUYV8_2X8,
	MEDIA_BUS_FMT_YVYU8_2X8,
	MEDIA_BUS_FMT_SBGGR8_1X8,
	MEDIA_BUS_FMT_SGBRG8_1X8,
	MEDIA_BUS_FMT_SGRBG8_1X8,
	MEDIA_BUS_FMT_SRGGB8_1X8,
	MEDIA_BUS_FMT_SBGGR10_1X10,
	MEDIA_BUS_FMT_SGBRG10_1X10,
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SRGGB10_1X10,
	MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE,
	MEDIA_BUS_FMT_SBGGR12_1X12,
	MEDIA_BUS_FMT_SGBRG12_1X12,
	MEDIA_BUS_FMT_SGRBG12_1X12,
	MEDIA_BUS_FMT_SRGGB12_1X12,
	MEDIA_BUS_FMT_SBGGR14_1X14,
	MEDIA_BUS_FMT_SGBRG14_1X14,
	MEDIA_BUS_FMT_SGRBG14_1X14,
	MEDIA_BUS_FMT_SRGGB14_1X14,
	MEDIA_BUS_FMT_Y10_1X10,
	MEDIA_BUS_FMT_Y10_2X8_PADHI_LE,
पूर्ण;

/*
 * ispअगर_isr_8x96 - ISPIF module पूर्णांकerrupt handler क्रम 8x96
 * @irq: Interrupt line
 * @dev: ISPIF device
 *
 * Return IRQ_HANDLED on success
 */
अटल irqवापस_t ispअगर_isr_8x96(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा ispअगर_device *ispअगर = dev;
	काष्ठा camss *camss = ispअगर->camss;
	u32 value0, value1, value2, value3, value4, value5;

	value0 = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_STATUS_0(0));
	value1 = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_STATUS_1(0));
	value2 = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_STATUS_2(0));
	value3 = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_STATUS_0(1));
	value4 = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_STATUS_1(1));
	value5 = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_STATUS_2(1));

	ग_लिखोl_relaxed(value0, ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_0(0));
	ग_लिखोl_relaxed(value1, ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_1(0));
	ग_लिखोl_relaxed(value2, ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_2(0));
	ग_लिखोl_relaxed(value3, ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_0(1));
	ग_लिखोl_relaxed(value4, ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_1(1));
	ग_लिखोl_relaxed(value5, ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_2(1));

	ग_लिखोl(0x1, ispअगर->base + ISPIF_IRQ_GLOBAL_CLEAR_CMD);

	अगर ((value0 >> 27) & 0x1)
		complete(&ispअगर->reset_complete[0]);

	अगर ((value3 >> 27) & 0x1)
		complete(&ispअगर->reset_complete[1]);

	अगर (unlikely(value0 & ISPIF_VFE_m_IRQ_STATUS_0_PIX0_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 pix0 overflow\n");

	अगर (unlikely(value0 & ISPIF_VFE_m_IRQ_STATUS_0_RDI0_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 rdi0 overflow\n");

	अगर (unlikely(value1 & ISPIF_VFE_m_IRQ_STATUS_1_PIX1_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 pix1 overflow\n");

	अगर (unlikely(value1 & ISPIF_VFE_m_IRQ_STATUS_1_RDI1_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 rdi1 overflow\n");

	अगर (unlikely(value2 & ISPIF_VFE_m_IRQ_STATUS_2_RDI2_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 rdi2 overflow\n");

	अगर (unlikely(value3 & ISPIF_VFE_m_IRQ_STATUS_0_PIX0_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE1 pix0 overflow\n");

	अगर (unlikely(value3 & ISPIF_VFE_m_IRQ_STATUS_0_RDI0_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE1 rdi0 overflow\n");

	अगर (unlikely(value4 & ISPIF_VFE_m_IRQ_STATUS_1_PIX1_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE1 pix1 overflow\n");

	अगर (unlikely(value4 & ISPIF_VFE_m_IRQ_STATUS_1_RDI1_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE1 rdi1 overflow\n");

	अगर (unlikely(value5 & ISPIF_VFE_m_IRQ_STATUS_2_RDI2_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE1 rdi2 overflow\n");

	वापस IRQ_HANDLED;
पूर्ण

/*
 * ispअगर_isr_8x16 - ISPIF module पूर्णांकerrupt handler क्रम 8x16
 * @irq: Interrupt line
 * @dev: ISPIF device
 *
 * Return IRQ_HANDLED on success
 */
अटल irqवापस_t ispअगर_isr_8x16(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा ispअगर_device *ispअगर = dev;
	काष्ठा camss *camss = ispअगर->camss;
	u32 value0, value1, value2;

	value0 = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_STATUS_0(0));
	value1 = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_STATUS_1(0));
	value2 = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_STATUS_2(0));

	ग_लिखोl_relaxed(value0, ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_0(0));
	ग_लिखोl_relaxed(value1, ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_1(0));
	ग_लिखोl_relaxed(value2, ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_2(0));

	ग_लिखोl(0x1, ispअगर->base + ISPIF_IRQ_GLOBAL_CLEAR_CMD);

	अगर ((value0 >> 27) & 0x1)
		complete(&ispअगर->reset_complete[0]);

	अगर (unlikely(value0 & ISPIF_VFE_m_IRQ_STATUS_0_PIX0_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 pix0 overflow\n");

	अगर (unlikely(value0 & ISPIF_VFE_m_IRQ_STATUS_0_RDI0_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 rdi0 overflow\n");

	अगर (unlikely(value1 & ISPIF_VFE_m_IRQ_STATUS_1_PIX1_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 pix1 overflow\n");

	अगर (unlikely(value1 & ISPIF_VFE_m_IRQ_STATUS_1_RDI1_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 rdi1 overflow\n");

	अगर (unlikely(value2 & ISPIF_VFE_m_IRQ_STATUS_2_RDI2_OVERFLOW))
		dev_err_ratelimited(camss->dev, "VFE0 rdi2 overflow\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ispअगर_vfe_reset(काष्ठा ispअगर_device *ispअगर, u8 vfe_id)
अणु
	काष्ठा camss *camss = ispअगर->camss;

	अचिन्हित दीर्घ समय;
	u32 val;

	अगर (vfe_id > (camss->vfe_num - 1)) अणु
		dev_err(camss->dev,
			"Error: asked reset for invalid VFE%d\n", vfe_id);
		वापस -ENOENT;
	पूर्ण

	reinit_completion(&ispअगर->reset_complete[vfe_id]);

	val = ISPIF_RST_CMD_0_STROBED_RST_EN |
		ISPIF_RST_CMD_0_MISC_LOGIC_RST |
		ISPIF_RST_CMD_0_SW_REG_RST |
		ISPIF_RST_CMD_0_PIX_INTF_0_CSID_RST |
		ISPIF_RST_CMD_0_PIX_INTF_0_VFE_RST |
		ISPIF_RST_CMD_0_PIX_INTF_1_CSID_RST |
		ISPIF_RST_CMD_0_PIX_INTF_1_VFE_RST |
		ISPIF_RST_CMD_0_RDI_INTF_0_CSID_RST |
		ISPIF_RST_CMD_0_RDI_INTF_0_VFE_RST |
		ISPIF_RST_CMD_0_RDI_INTF_1_CSID_RST |
		ISPIF_RST_CMD_0_RDI_INTF_1_VFE_RST |
		ISPIF_RST_CMD_0_RDI_INTF_2_CSID_RST |
		ISPIF_RST_CMD_0_RDI_INTF_2_VFE_RST |
		ISPIF_RST_CMD_0_PIX_OUTPUT_0_MISR_RST |
		ISPIF_RST_CMD_0_RDI_OUTPUT_0_MISR_RST |
		ISPIF_RST_CMD_0_RDI_OUTPUT_1_MISR_RST |
		ISPIF_RST_CMD_0_RDI_OUTPUT_2_MISR_RST;

	अगर (vfe_id == 1)
		ग_लिखोl_relaxed(val, ispअगर->base + ISPIF_RST_CMD_1);
	अन्यथा
		ग_लिखोl_relaxed(val, ispअगर->base + ISPIF_RST_CMD_0);

	समय = रुको_क्रम_completion_समयout(&ispअगर->reset_complete[vfe_id],
		msecs_to_jअगरfies(ISPIF_RESET_TIMEOUT_MS));
	अगर (!समय) अणु
		dev_err(camss->dev,
			"ISPIF for VFE%d reset timeout\n", vfe_id);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ispअगर_reset - Trigger reset on ISPIF module and रुको to complete
 * @ispअगर: ISPIF device
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक ispअगर_reset(काष्ठा ispअगर_device *ispअगर, u8 vfe_id)
अणु
	काष्ठा camss *camss = ispअगर->camss;
	पूर्णांक ret;

	ret = camss_pm_करोमुख्य_on(camss, PM_DOMAIN_VFE0);
	अगर (ret < 0)
		वापस ret;

	ret = camss_pm_करोमुख्य_on(camss, PM_DOMAIN_VFE1);
	अगर (ret < 0)
		वापस ret;

	ret = camss_enable_घड़ीs(ispअगर->nघड़ीs_क्रम_reset,
				  ispअगर->घड़ी_क्रम_reset,
				  camss->dev);
	अगर (ret < 0)
		वापस ret;

	ret = ispअगर_vfe_reset(ispअगर, vfe_id);
	अगर (ret)
		dev_dbg(camss->dev, "ISPIF Reset failed\n");

	camss_disable_घड़ीs(ispअगर->nघड़ीs_क्रम_reset, ispअगर->घड़ी_क्रम_reset);

	camss_pm_करोमुख्य_off(camss, PM_DOMAIN_VFE0);
	camss_pm_करोमुख्य_off(camss, PM_DOMAIN_VFE1);

	वापस ret;
पूर्ण

/*
 * ispअगर_set_घातer - Power on/off ISPIF module
 * @sd: ISPIF V4L2 subdevice
 * @on: Requested घातer state
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक ispअगर_set_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ispअगर_line *line = v4l2_get_subdevdata(sd);
	काष्ठा ispअगर_device *ispअगर = line->ispअगर;
	काष्ठा device *dev = ispअगर->camss->dev;
	पूर्णांक ret = 0;

	mutex_lock(&ispअगर->घातer_lock);

	अगर (on) अणु
		अगर (ispअगर->घातer_count) अणु
			/* Power is alपढ़ोy on */
			ispअगर->घातer_count++;
			जाओ निकास;
		पूर्ण

		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(dev);
			जाओ निकास;
		पूर्ण

		ret = camss_enable_घड़ीs(ispअगर->nघड़ीs, ispअगर->घड़ी, dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(dev);
			जाओ निकास;
		पूर्ण

		ret = ispअगर_reset(ispअगर, line->vfe_id);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(dev);
			camss_disable_घड़ीs(ispअगर->nघड़ीs, ispअगर->घड़ी);
			जाओ निकास;
		पूर्ण

		ispअगर->पूर्णांकf_cmd[line->vfe_id].cmd_0 = CMD_ALL_NO_CHANGE;
		ispअगर->पूर्णांकf_cmd[line->vfe_id].cmd_1 = CMD_ALL_NO_CHANGE;

		ispअगर->घातer_count++;
	पूर्ण अन्यथा अणु
		अगर (ispअगर->घातer_count == 0) अणु
			dev_err(dev, "ispif power off on power_count == 0\n");
			जाओ निकास;
		पूर्ण अन्यथा अगर (ispअगर->घातer_count == 1) अणु
			camss_disable_घड़ीs(ispअगर->nघड़ीs, ispअगर->घड़ी);
			pm_runसमय_put_sync(dev);
		पूर्ण

		ispअगर->घातer_count--;
	पूर्ण

निकास:
	mutex_unlock(&ispअगर->घातer_lock);

	वापस ret;
पूर्ण

/*
 * ispअगर_select_clk_mux - Select घड़ी क्रम PIX/RDI पूर्णांकerface
 * @ispअगर: ISPIF device
 * @पूर्णांकf: VFE पूर्णांकerface
 * @csid: CSID HW module id
 * @vfe: VFE HW module id
 * @enable: enable or disable the selected घड़ी
 */
अटल व्योम ispअगर_select_clk_mux(काष्ठा ispअगर_device *ispअगर,
				 क्रमागत ispअगर_पूर्णांकf पूर्णांकf, u8 csid,
				 u8 vfe, u8 enable)
अणु
	u32 val;

	चयन (पूर्णांकf) अणु
	हाल PIX0:
		val = पढ़ोl_relaxed(ispअगर->base_clk_mux + CSI_PIX_CLK_MUX_SEL);
		val &= ~(0xf << (vfe * 8));
		अगर (enable)
			val |= (csid << (vfe * 8));
		ग_लिखोl_relaxed(val, ispअगर->base_clk_mux + CSI_PIX_CLK_MUX_SEL);
		अवरोध;

	हाल RDI0:
		val = पढ़ोl_relaxed(ispअगर->base_clk_mux + CSI_RDI_CLK_MUX_SEL);
		val &= ~(0xf << (vfe * 12));
		अगर (enable)
			val |= (csid << (vfe * 12));
		ग_लिखोl_relaxed(val, ispअगर->base_clk_mux + CSI_RDI_CLK_MUX_SEL);
		अवरोध;

	हाल PIX1:
		val = पढ़ोl_relaxed(ispअगर->base_clk_mux + CSI_PIX_CLK_MUX_SEL);
		val &= ~(0xf << (4 + (vfe * 8)));
		अगर (enable)
			val |= (csid << (4 + (vfe * 8)));
		ग_लिखोl_relaxed(val, ispअगर->base_clk_mux + CSI_PIX_CLK_MUX_SEL);
		अवरोध;

	हाल RDI1:
		val = पढ़ोl_relaxed(ispअगर->base_clk_mux + CSI_RDI_CLK_MUX_SEL);
		val &= ~(0xf << (4 + (vfe * 12)));
		अगर (enable)
			val |= (csid << (4 + (vfe * 12)));
		ग_लिखोl_relaxed(val, ispअगर->base_clk_mux + CSI_RDI_CLK_MUX_SEL);
		अवरोध;

	हाल RDI2:
		val = पढ़ोl_relaxed(ispअगर->base_clk_mux + CSI_RDI_CLK_MUX_SEL);
		val &= ~(0xf << (8 + (vfe * 12)));
		अगर (enable)
			val |= (csid << (8 + (vfe * 12)));
		ग_लिखोl_relaxed(val, ispअगर->base_clk_mux + CSI_RDI_CLK_MUX_SEL);
		अवरोध;
	पूर्ण

	mb();
पूर्ण

/*
 * ispअगर_validate_पूर्णांकf_status - Validate current status of PIX/RDI पूर्णांकerface
 * @ispअगर: ISPIF device
 * @पूर्णांकf: VFE पूर्णांकerface
 * @vfe: VFE HW module id
 *
 * Return 0 when पूर्णांकerface is idle or -EBUSY otherwise
 */
अटल पूर्णांक ispअगर_validate_पूर्णांकf_status(काष्ठा ispअगर_device *ispअगर,
				      क्रमागत ispअगर_पूर्णांकf पूर्णांकf, u8 vfe)
अणु
	पूर्णांक ret = 0;
	u32 val = 0;

	चयन (पूर्णांकf) अणु
	हाल PIX0:
		val = पढ़ोl_relaxed(ispअगर->base +
			ISPIF_VFE_m_PIX_INTF_n_STATUS(vfe, 0));
		अवरोध;
	हाल RDI0:
		val = पढ़ोl_relaxed(ispअगर->base +
			ISPIF_VFE_m_RDI_INTF_n_STATUS(vfe, 0));
		अवरोध;
	हाल PIX1:
		val = पढ़ोl_relaxed(ispअगर->base +
			ISPIF_VFE_m_PIX_INTF_n_STATUS(vfe, 1));
		अवरोध;
	हाल RDI1:
		val = पढ़ोl_relaxed(ispअगर->base +
			ISPIF_VFE_m_RDI_INTF_n_STATUS(vfe, 1));
		अवरोध;
	हाल RDI2:
		val = पढ़ोl_relaxed(ispअगर->base +
			ISPIF_VFE_m_RDI_INTF_n_STATUS(vfe, 2));
		अवरोध;
	पूर्ण

	अगर ((val & 0xf) != 0xf) अणु
		dev_err(ispअगर->camss->dev, "%s: ispif is busy: 0x%x\n",
			__func__, val);
		ret = -EBUSY;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * ispअगर_रुको_क्रम_stop - Wait क्रम PIX/RDI पूर्णांकerface to stop
 * @ispअगर: ISPIF device
 * @पूर्णांकf: VFE पूर्णांकerface
 * @vfe: VFE HW module id
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक ispअगर_रुको_क्रम_stop(काष्ठा ispअगर_device *ispअगर,
			       क्रमागत ispअगर_पूर्णांकf पूर्णांकf, u8 vfe)
अणु
	u32 addr = 0;
	u32 stop_flag = 0;
	पूर्णांक ret;

	चयन (पूर्णांकf) अणु
	हाल PIX0:
		addr = ISPIF_VFE_m_PIX_INTF_n_STATUS(vfe, 0);
		अवरोध;
	हाल RDI0:
		addr = ISPIF_VFE_m_RDI_INTF_n_STATUS(vfe, 0);
		अवरोध;
	हाल PIX1:
		addr = ISPIF_VFE_m_PIX_INTF_n_STATUS(vfe, 1);
		अवरोध;
	हाल RDI1:
		addr = ISPIF_VFE_m_RDI_INTF_n_STATUS(vfe, 1);
		अवरोध;
	हाल RDI2:
		addr = ISPIF_VFE_m_RDI_INTF_n_STATUS(vfe, 2);
		अवरोध;
	पूर्ण

	ret = पढ़ोl_poll_समयout(ispअगर->base + addr,
				 stop_flag,
				 (stop_flag & 0xf) == 0xf,
				 ISPIF_TIMEOUT_SLEEP_US,
				 ISPIF_TIMEOUT_ALL_US);
	अगर (ret < 0)
		dev_err(ispअगर->camss->dev, "%s: ispif stop timeout\n",
			__func__);

	वापस ret;
पूर्ण

/*
 * ispअगर_select_csid - Select CSID HW module क्रम input from
 * @ispअगर: ISPIF device
 * @पूर्णांकf: VFE पूर्णांकerface
 * @csid: CSID HW module id
 * @vfe: VFE HW module id
 * @enable: enable or disable the selected input
 */
अटल व्योम ispअगर_select_csid(काष्ठा ispअगर_device *ispअगर, क्रमागत ispअगर_पूर्णांकf पूर्णांकf,
			      u8 csid, u8 vfe, u8 enable)
अणु
	u32 val;

	val = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_INTF_INPUT_SEL(vfe));
	चयन (पूर्णांकf) अणु
	हाल PIX0:
		val &= ~(BIT(1) | BIT(0));
		अगर (enable)
			val |= csid;
		अवरोध;
	हाल RDI0:
		val &= ~(BIT(5) | BIT(4));
		अगर (enable)
			val |= (csid << 4);
		अवरोध;
	हाल PIX1:
		val &= ~(BIT(9) | BIT(8));
		अगर (enable)
			val |= (csid << 8);
		अवरोध;
	हाल RDI1:
		val &= ~(BIT(13) | BIT(12));
		अगर (enable)
			val |= (csid << 12);
		अवरोध;
	हाल RDI2:
		val &= ~(BIT(21) | BIT(20));
		अगर (enable)
			val |= (csid << 20);
		अवरोध;
	पूर्ण

	ग_लिखोl(val, ispअगर->base + ISPIF_VFE_m_INTF_INPUT_SEL(vfe));
पूर्ण

/*
 * ispअगर_select_cid - Enable/disable desired CID
 * @ispअगर: ISPIF device
 * @पूर्णांकf: VFE पूर्णांकerface
 * @cid: desired CID to enable/disable
 * @vfe: VFE HW module id
 * @enable: enable or disable the desired CID
 */
अटल व्योम ispअगर_select_cid(काष्ठा ispअगर_device *ispअगर, क्रमागत ispअगर_पूर्णांकf पूर्णांकf,
			     u8 cid, u8 vfe, u8 enable)
अणु
	u32 cid_mask = 1 << cid;
	u32 addr = 0;
	u32 val;

	चयन (पूर्णांकf) अणु
	हाल PIX0:
		addr = ISPIF_VFE_m_PIX_INTF_n_CID_MASK(vfe, 0);
		अवरोध;
	हाल RDI0:
		addr = ISPIF_VFE_m_RDI_INTF_n_CID_MASK(vfe, 0);
		अवरोध;
	हाल PIX1:
		addr = ISPIF_VFE_m_PIX_INTF_n_CID_MASK(vfe, 1);
		अवरोध;
	हाल RDI1:
		addr = ISPIF_VFE_m_RDI_INTF_n_CID_MASK(vfe, 1);
		अवरोध;
	हाल RDI2:
		addr = ISPIF_VFE_m_RDI_INTF_n_CID_MASK(vfe, 2);
		अवरोध;
	पूर्ण

	val = पढ़ोl_relaxed(ispअगर->base + addr);
	अगर (enable)
		val |= cid_mask;
	अन्यथा
		val &= ~cid_mask;

	ग_लिखोl(val, ispअगर->base + addr);
पूर्ण

/*
 * ispअगर_config_irq - Enable/disable पूर्णांकerrupts क्रम PIX/RDI पूर्णांकerface
 * @ispअगर: ISPIF device
 * @पूर्णांकf: VFE पूर्णांकerface
 * @vfe: VFE HW module id
 * @enable: enable or disable
 */
अटल व्योम ispअगर_config_irq(काष्ठा ispअगर_device *ispअगर, क्रमागत ispअगर_पूर्णांकf पूर्णांकf,
			     u8 vfe, u8 enable)
अणु
	u32 val;

	चयन (पूर्णांकf) अणु
	हाल PIX0:
		val = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_MASK_0(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_0_PIX0_MASK;
		अगर (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_0_PIX0_ENABLE;
		ग_लिखोl_relaxed(val, ispअगर->base + ISPIF_VFE_m_IRQ_MASK_0(vfe));
		ग_लिखोl_relaxed(ISPIF_VFE_m_IRQ_MASK_0_PIX0_ENABLE,
			       ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_0(vfe));
		अवरोध;
	हाल RDI0:
		val = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_MASK_0(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_0_RDI0_MASK;
		अगर (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_0_RDI0_ENABLE;
		ग_लिखोl_relaxed(val, ispअगर->base + ISPIF_VFE_m_IRQ_MASK_0(vfe));
		ग_लिखोl_relaxed(ISPIF_VFE_m_IRQ_MASK_0_RDI0_ENABLE,
			       ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_0(vfe));
		अवरोध;
	हाल PIX1:
		val = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_MASK_1(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_1_PIX1_MASK;
		अगर (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_1_PIX1_ENABLE;
		ग_लिखोl_relaxed(val, ispअगर->base + ISPIF_VFE_m_IRQ_MASK_1(vfe));
		ग_लिखोl_relaxed(ISPIF_VFE_m_IRQ_MASK_1_PIX1_ENABLE,
			       ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_1(vfe));
		अवरोध;
	हाल RDI1:
		val = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_MASK_1(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_1_RDI1_MASK;
		अगर (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_1_RDI1_ENABLE;
		ग_लिखोl_relaxed(val, ispअगर->base + ISPIF_VFE_m_IRQ_MASK_1(vfe));
		ग_लिखोl_relaxed(ISPIF_VFE_m_IRQ_MASK_1_RDI1_ENABLE,
			       ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_1(vfe));
		अवरोध;
	हाल RDI2:
		val = पढ़ोl_relaxed(ispअगर->base + ISPIF_VFE_m_IRQ_MASK_2(vfe));
		val &= ~ISPIF_VFE_m_IRQ_MASK_2_RDI2_MASK;
		अगर (enable)
			val |= ISPIF_VFE_m_IRQ_MASK_2_RDI2_ENABLE;
		ग_लिखोl_relaxed(val, ispअगर->base + ISPIF_VFE_m_IRQ_MASK_2(vfe));
		ग_लिखोl_relaxed(ISPIF_VFE_m_IRQ_MASK_2_RDI2_ENABLE,
			       ispअगर->base + ISPIF_VFE_m_IRQ_CLEAR_2(vfe));
		अवरोध;
	पूर्ण

	ग_लिखोl(0x1, ispअगर->base + ISPIF_IRQ_GLOBAL_CLEAR_CMD);
पूर्ण

/*
 * ispअगर_config_pack - Config packing क्रम PRDI mode
 * @ispअगर: ISPIF device
 * @code: media bus क्रमmat code
 * @पूर्णांकf: VFE पूर्णांकerface
 * @cid: desired CID to handle
 * @vfe: VFE HW module id
 * @enable: enable or disable
 */
अटल व्योम ispअगर_config_pack(काष्ठा ispअगर_device *ispअगर, u32 code,
			      क्रमागत ispअगर_पूर्णांकf पूर्णांकf, u8 cid, u8 vfe, u8 enable)
अणु
	u32 addr, val;

	अगर (code != MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE &&
	    code != MEDIA_BUS_FMT_Y10_2X8_PADHI_LE)
		वापस;

	चयन (पूर्णांकf) अणु
	हाल RDI0:
		अगर (cid < 8)
			addr = ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_0(vfe, 0);
		अन्यथा
			addr = ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_1(vfe, 0);
		अवरोध;
	हाल RDI1:
		अगर (cid < 8)
			addr = ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_0(vfe, 1);
		अन्यथा
			addr = ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_1(vfe, 1);
		अवरोध;
	हाल RDI2:
		अगर (cid < 8)
			addr = ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_0(vfe, 2);
		अन्यथा
			addr = ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_1(vfe, 2);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (enable)
		val = ISPIF_VFE_m_RDI_INTF_n_PACK_CFG_0_CID_c_PLAIN(cid);
	अन्यथा
		val = 0;

	ग_लिखोl_relaxed(val, ispअगर->base + addr);
पूर्ण

/*
 * ispअगर_set_पूर्णांकf_cmd - Set command to enable/disable पूर्णांकerface
 * @ispअगर: ISPIF device
 * @cmd: पूर्णांकerface command
 * @पूर्णांकf: VFE पूर्णांकerface
 * @vfe: VFE HW module id
 * @vc: भव channel
 */
अटल व्योम ispअगर_set_पूर्णांकf_cmd(काष्ठा ispअगर_device *ispअगर, u8 cmd,
			       क्रमागत ispअगर_पूर्णांकf पूर्णांकf, u8 vfe, u8 vc)
अणु
	u32 *val;

	अगर (पूर्णांकf == RDI2) अणु
		val = &ispअगर->पूर्णांकf_cmd[vfe].cmd_1;
		*val &= ~(0x3 << (vc * 2 + 8));
		*val |= (cmd << (vc * 2 + 8));
		wmb();
		ग_लिखोl_relaxed(*val, ispअगर->base + ISPIF_VFE_m_INTF_CMD_1(vfe));
		wmb();
	पूर्ण अन्यथा अणु
		val = &ispअगर->पूर्णांकf_cmd[vfe].cmd_0;
		*val &= ~(0x3 << (vc * 2 + पूर्णांकf * 8));
		*val |= (cmd << (vc * 2 + पूर्णांकf * 8));
		wmb();
		ग_लिखोl_relaxed(*val, ispअगर->base + ISPIF_VFE_m_INTF_CMD_0(vfe));
		wmb();
	पूर्ण
पूर्ण

/*
 * ispअगर_set_stream - Enable/disable streaming on ISPIF module
 * @sd: ISPIF V4L2 subdevice
 * @enable: Requested streaming state
 *
 * Main configuration of ISPIF module is also करोne here.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक ispअगर_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ispअगर_line *line = v4l2_get_subdevdata(sd);
	काष्ठा ispअगर_device *ispअगर = line->ispअगर;
	काष्ठा camss *camss = ispअगर->camss;
	क्रमागत ispअगर_पूर्णांकf पूर्णांकf = line->पूर्णांकerface;
	u8 csid = line->csid_id;
	u8 vfe = line->vfe_id;
	u8 vc = 0; /* Virtual Channel 0 */
	u8 cid = vc * 4; /* id of Virtual Channel and Data Type set */
	पूर्णांक ret;

	अगर (enable) अणु
		अगर (!media_entity_remote_pad(&line->pads[MSM_ISPIF_PAD_SINK]))
			वापस -ENOLINK;

		/* Config */

		mutex_lock(&ispअगर->config_lock);
		ispअगर_select_clk_mux(ispअगर, पूर्णांकf, csid, vfe, 1);

		ret = ispअगर_validate_पूर्णांकf_status(ispअगर, पूर्णांकf, vfe);
		अगर (ret < 0) अणु
			mutex_unlock(&ispअगर->config_lock);
			वापस ret;
		पूर्ण

		ispअगर_select_csid(ispअगर, पूर्णांकf, csid, vfe, 1);
		ispअगर_select_cid(ispअगर, पूर्णांकf, cid, vfe, 1);
		ispअगर_config_irq(ispअगर, पूर्णांकf, vfe, 1);
		अगर (camss->version == CAMSS_8x96 ||
		    camss->version == CAMSS_660)
			ispअगर_config_pack(ispअगर,
					  line->fmt[MSM_ISPIF_PAD_SINK].code,
					  पूर्णांकf, cid, vfe, 1);
		ispअगर_set_पूर्णांकf_cmd(ispअगर, CMD_ENABLE_FRAME_BOUNDARY,
				   पूर्णांकf, vfe, vc);
	पूर्ण अन्यथा अणु
		mutex_lock(&ispअगर->config_lock);
		ispअगर_set_पूर्णांकf_cmd(ispअगर, CMD_DISABLE_FRAME_BOUNDARY,
				   पूर्णांकf, vfe, vc);
		mutex_unlock(&ispअगर->config_lock);

		ret = ispअगर_रुको_क्रम_stop(ispअगर, पूर्णांकf, vfe);
		अगर (ret < 0)
			वापस ret;

		mutex_lock(&ispअगर->config_lock);
		अगर (camss->version == CAMSS_8x96 ||
		    camss->version == CAMSS_660)
			ispअगर_config_pack(ispअगर,
					  line->fmt[MSM_ISPIF_PAD_SINK].code,
					  पूर्णांकf, cid, vfe, 0);
		ispअगर_config_irq(ispअगर, पूर्णांकf, vfe, 0);
		ispअगर_select_cid(ispअगर, पूर्णांकf, cid, vfe, 0);
		ispअगर_select_csid(ispअगर, पूर्णांकf, csid, vfe, 0);
		ispअगर_select_clk_mux(ispअगर, पूर्णांकf, csid, vfe, 0);
	पूर्ण

	mutex_unlock(&ispअगर->config_lock);

	वापस 0;
पूर्ण

/*
 * __ispअगर_get_क्रमmat - Get poपूर्णांकer to क्रमmat काष्ठाure
 * @ispअगर: ISPIF line
 * @cfg: V4L2 subdev pad configuration
 * @pad: pad from which क्रमmat is requested
 * @which: TRY or ACTIVE क्रमmat
 *
 * Return poपूर्णांकer to TRY or ACTIVE क्रमmat काष्ठाure
 */
अटल काष्ठा v4l2_mbus_framefmt *
__ispअगर_get_क्रमmat(काष्ठा ispअगर_line *line,
		   काष्ठा v4l2_subdev_pad_config *cfg,
		   अचिन्हित पूर्णांक pad,
		   क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&line->subdev, cfg, pad);

	वापस &line->fmt[pad];
पूर्ण

/*
 * ispअगर_try_क्रमmat - Handle try क्रमmat by pad subdev method
 * @ispअगर: ISPIF line
 * @cfg: V4L2 subdev pad configuration
 * @pad: pad on which क्रमmat is requested
 * @fmt: poपूर्णांकer to v4l2 क्रमmat काष्ठाure
 * @which: wanted subdev क्रमmat
 */
अटल व्योम ispअगर_try_क्रमmat(काष्ठा ispअगर_line *line,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     अचिन्हित पूर्णांक pad,
			     काष्ठा v4l2_mbus_framefmt *fmt,
			     क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अचिन्हित पूर्णांक i;

	चयन (pad) अणु
	हाल MSM_ISPIF_PAD_SINK:
		/* Set क्रमmat on sink pad */

		क्रम (i = 0; i < line->nक्रमmats; i++)
			अगर (fmt->code == line->क्रमmats[i])
				अवरोध;

		/* If not found, use UYVY as शेष */
		अगर (i >= line->nक्रमmats)
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

		fmt->width = clamp_t(u32, fmt->width, 1, 8191);
		fmt->height = clamp_t(u32, fmt->height, 1, 8191);

		fmt->field = V4L2_FIELD_NONE;
		fmt->colorspace = V4L2_COLORSPACE_SRGB;

		अवरोध;

	हाल MSM_ISPIF_PAD_SRC:
		/* Set and वापस a क्रमmat same as sink pad */

		*fmt = *__ispअगर_get_क्रमmat(line, cfg, MSM_ISPIF_PAD_SINK,
					   which);

		अवरोध;
	पूर्ण

	fmt->colorspace = V4L2_COLORSPACE_SRGB;
पूर्ण

/*
 * ispअगर_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd: ISPIF V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @code: poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ispअगर_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा ispअगर_line *line = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	अगर (code->pad == MSM_ISPIF_PAD_SINK) अणु
		अगर (code->index >= line->nक्रमmats)
			वापस -EINVAL;

		code->code = line->क्रमmats[code->index];
	पूर्ण अन्यथा अणु
		अगर (code->index > 0)
			वापस -EINVAL;

		क्रमmat = __ispअगर_get_क्रमmat(line, cfg, MSM_ISPIF_PAD_SINK,
					    code->which);

		code->code = क्रमmat->code;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ispअगर_क्रमागत_frame_size - Handle frame size क्रमागतeration
 * @sd: ISPIF V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fse: poपूर्णांकer to v4l2_subdev_frame_size_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ispअगर_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा ispअगर_line *line = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	ispअगर_try_क्रमmat(line, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	ispअगर_try_क्रमmat(line, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * ispअगर_get_क्रमmat - Handle get क्रमmat by pads subdev method
 * @sd: ISPIF V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक ispअगर_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ispअगर_line *line = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __ispअगर_get_क्रमmat(line, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;

	वापस 0;
पूर्ण

/*
 * ispअगर_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd: ISPIF V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक ispअगर_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ispअगर_line *line = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __ispअगर_get_क्रमmat(line, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	ispअगर_try_क्रमmat(line, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == MSM_ISPIF_PAD_SINK) अणु
		क्रमmat = __ispअगर_get_क्रमmat(line, cfg, MSM_ISPIF_PAD_SRC,
					    fmt->which);

		*क्रमmat = fmt->क्रमmat;
		ispअगर_try_क्रमmat(line, cfg, MSM_ISPIF_PAD_SRC, क्रमmat,
				 fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ispअगर_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISPIF V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक ispअगर_init_क्रमmats(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.pad = MSM_ISPIF_PAD_SINK,
		.which = fh ? V4L2_SUBDEV_FORMAT_TRY :
			      V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat = अणु
			.code = MEDIA_BUS_FMT_UYVY8_2X8,
			.width = 1920,
			.height = 1080
		पूर्ण
	पूर्ण;

	वापस ispअगर_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);
पूर्ण

/*
 * msm_ispअगर_subdev_init - Initialize ISPIF device काष्ठाure and resources
 * @ispअगर: ISPIF device
 * @res: ISPIF module resources table
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक msm_ispअगर_subdev_init(काष्ठा camss *camss,
			  स्थिर काष्ठा resources_ispअगर *res)
अणु
	काष्ठा device *dev = camss->dev;
	काष्ठा ispअगर_device *ispअगर = camss->ispअगर;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *r;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (!camss->ispअगर)
		वापस 0;

	ispअगर->camss = camss;

	/* Number of ISPIF lines - same as number of CSID hardware modules */
	अगर (camss->version == CAMSS_8x16)
		ispअगर->line_num = 2;
	अन्यथा अगर (camss->version == CAMSS_8x96 ||
		 camss->version == CAMSS_660)
		ispअगर->line_num = 4;
	अन्यथा
		वापस -EINVAL;

	ispअगर->line = devm_kसुस्मृति(dev, ispअगर->line_num,
				   माप(*ispअगर->line), GFP_KERNEL);
	अगर (!ispअगर->line)
		वापस -ENOMEM;

	क्रम (i = 0; i < ispअगर->line_num; i++) अणु
		ispअगर->line[i].ispअगर = ispअगर;
		ispअगर->line[i].id = i;

		अगर (camss->version == CAMSS_8x16) अणु
			ispअगर->line[i].क्रमmats = ispअगर_क्रमmats_8x16;
			ispअगर->line[i].nक्रमmats =
					ARRAY_SIZE(ispअगर_क्रमmats_8x16);
		पूर्ण अन्यथा अगर (camss->version == CAMSS_8x96 ||
			   camss->version == CAMSS_660) अणु
			ispअगर->line[i].क्रमmats = ispअगर_क्रमmats_8x96;
			ispअगर->line[i].nक्रमmats =
					ARRAY_SIZE(ispअगर_क्रमmats_8x96);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Memory */

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, res->reg[0]);
	ispअगर->base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(ispअगर->base))
		वापस PTR_ERR(ispअगर->base);

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, res->reg[1]);
	ispअगर->base_clk_mux = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(ispअगर->base_clk_mux))
		वापस PTR_ERR(ispअगर->base_clk_mux);

	/* Interrupt */

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, res->पूर्णांकerrupt);

	अगर (!r) अणु
		dev_err(dev, "missing IRQ\n");
		वापस -EINVAL;
	पूर्ण

	ispअगर->irq = r->start;
	snम_लिखो(ispअगर->irq_name, माप(ispअगर->irq_name), "%s_%s",
		 dev_name(dev), MSM_ISPIF_NAME);
	अगर (camss->version == CAMSS_8x16)
		ret = devm_request_irq(dev, ispअगर->irq, ispअगर_isr_8x16,
			       IRQF_TRIGGER_RISING, ispअगर->irq_name, ispअगर);
	अन्यथा अगर (camss->version == CAMSS_8x96 ||
		 camss->version == CAMSS_660)
		ret = devm_request_irq(dev, ispअगर->irq, ispअगर_isr_8x96,
			       IRQF_TRIGGER_RISING, ispअगर->irq_name, ispअगर);
	अन्यथा
		ret = -EINVAL;

	अगर (ret < 0) अणु
		dev_err(dev, "request_irq failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Clocks */

	ispअगर->nघड़ीs = 0;
	जबतक (res->घड़ी[ispअगर->nघड़ीs])
		ispअगर->nघड़ीs++;

	ispअगर->घड़ी = devm_kसुस्मृति(dev,
				    ispअगर->nघड़ीs, माप(*ispअगर->घड़ी),
				    GFP_KERNEL);
	अगर (!ispअगर->घड़ी)
		वापस -ENOMEM;

	क्रम (i = 0; i < ispअगर->nघड़ीs; i++) अणु
		काष्ठा camss_घड़ी *घड़ी = &ispअगर->घड़ी[i];

		घड़ी->clk = devm_clk_get(dev, res->घड़ी[i]);
		अगर (IS_ERR(घड़ी->clk))
			वापस PTR_ERR(घड़ी->clk);

		घड़ी->freq = शून्य;
		घड़ी->nfreqs = 0;
	पूर्ण

	ispअगर->nघड़ीs_क्रम_reset = 0;
	जबतक (res->घड़ी_क्रम_reset[ispअगर->nघड़ीs_क्रम_reset])
		ispअगर->nघड़ीs_क्रम_reset++;

	ispअगर->घड़ी_क्रम_reset = devm_kसुस्मृति(dev,
					      ispअगर->nघड़ीs_क्रम_reset,
					      माप(*ispअगर->घड़ी_क्रम_reset),
					      GFP_KERNEL);
	अगर (!ispअगर->घड़ी_क्रम_reset)
		वापस -ENOMEM;

	क्रम (i = 0; i < ispअगर->nघड़ीs_क्रम_reset; i++) अणु
		काष्ठा camss_घड़ी *घड़ी = &ispअगर->घड़ी_क्रम_reset[i];

		घड़ी->clk = devm_clk_get(dev, res->घड़ी_क्रम_reset[i]);
		अगर (IS_ERR(घड़ी->clk))
			वापस PTR_ERR(घड़ी->clk);

		घड़ी->freq = शून्य;
		घड़ी->nfreqs = 0;
	पूर्ण

	mutex_init(&ispअगर->घातer_lock);
	ispअगर->घातer_count = 0;

	mutex_init(&ispअगर->config_lock);

	क्रम (i = 0; i < MSM_ISPIF_VFE_NUM; i++)
		init_completion(&ispअगर->reset_complete[i]);

	वापस 0;
पूर्ण

/*
 * ispअगर_get_पूर्णांकf - Get ISPIF पूर्णांकerface to use by VFE line id
 * @line_id: VFE line id that the ISPIF line is connected to
 *
 * Return ISPIF पूर्णांकerface to use
 */
अटल क्रमागत ispअगर_पूर्णांकf ispअगर_get_पूर्णांकf(क्रमागत vfe_line_id line_id)
अणु
	चयन (line_id) अणु
	हाल (VFE_LINE_RDI0):
		वापस RDI0;
	हाल (VFE_LINE_RDI1):
		वापस RDI1;
	हाल (VFE_LINE_RDI2):
		वापस RDI2;
	हाल (VFE_LINE_PIX):
		वापस PIX0;
	शेष:
		वापस RDI0;
	पूर्ण
पूर्ण

/*
 * ispअगर_link_setup - Setup ISPIF connections
 * @entity: Poपूर्णांकer to media entity काष्ठाure
 * @local: Poपूर्णांकer to local pad
 * @remote: Poपूर्णांकer to remote pad
 * @flags: Link flags
 *
 * Return 0 on success
 */
अटल पूर्णांक ispअगर_link_setup(काष्ठा media_entity *entity,
			    स्थिर काष्ठा media_pad *local,
			    स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		अगर (media_entity_remote_pad(local))
			वापस -EBUSY;

		अगर (local->flags & MEDIA_PAD_FL_SINK) अणु
			काष्ठा v4l2_subdev *sd;
			काष्ठा ispअगर_line *line;

			sd = media_entity_to_v4l2_subdev(entity);
			line = v4l2_get_subdevdata(sd);

			msm_csid_get_csid_id(remote->entity, &line->csid_id);
		पूर्ण अन्यथा अणु /* MEDIA_PAD_FL_SOURCE */
			काष्ठा v4l2_subdev *sd;
			काष्ठा ispअगर_line *line;
			क्रमागत vfe_line_id id;

			sd = media_entity_to_v4l2_subdev(entity);
			line = v4l2_get_subdevdata(sd);

			msm_vfe_get_vfe_id(remote->entity, &line->vfe_id);
			msm_vfe_get_vfe_line_id(remote->entity, &id);
			line->पूर्णांकerface = ispअगर_get_पूर्णांकf(id);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ispअगर_core_ops = अणु
	.s_घातer = ispअगर_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ispअगर_video_ops = अणु
	.s_stream = ispअगर_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ispअगर_pad_ops = अणु
	.क्रमागत_mbus_code = ispअगर_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ispअगर_क्रमागत_frame_size,
	.get_fmt = ispअगर_get_क्रमmat,
	.set_fmt = ispअगर_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ispअगर_v4l2_ops = अणु
	.core = &ispअगर_core_ops,
	.video = &ispअगर_video_ops,
	.pad = &ispअगर_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ispअगर_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = ispअगर_init_क्रमmats,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations ispअगर_media_ops = अणु
	.link_setup = ispअगर_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
 * msm_ispअगर_रेजिस्टर_entities - Register subdev node क्रम ISPIF module
 * @ispअगर: ISPIF device
 * @v4l2_dev: V4L2 device
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक msm_ispअगर_रेजिस्टर_entities(काष्ठा ispअगर_device *ispअगर,
				काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा camss *camss;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!ispअगर)
		वापस 0;

	camss = ispअगर->camss;

	क्रम (i = 0; i < ispअगर->line_num; i++) अणु
		काष्ठा v4l2_subdev *sd = &ispअगर->line[i].subdev;
		काष्ठा media_pad *pads = ispअगर->line[i].pads;

		v4l2_subdev_init(sd, &ispअगर_v4l2_ops);
		sd->पूर्णांकernal_ops = &ispअगर_v4l2_पूर्णांकernal_ops;
		sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
		snम_लिखो(sd->name, ARRAY_SIZE(sd->name), "%s%d",
			 MSM_ISPIF_NAME, i);
		v4l2_set_subdevdata(sd, &ispअगर->line[i]);

		ret = ispअगर_init_क्रमmats(sd, शून्य);
		अगर (ret < 0) अणु
			dev_err(camss->dev, "Failed to init format: %d\n", ret);
			जाओ error;
		पूर्ण

		pads[MSM_ISPIF_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
		pads[MSM_ISPIF_PAD_SRC].flags = MEDIA_PAD_FL_SOURCE;

		sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
		sd->entity.ops = &ispअगर_media_ops;
		ret = media_entity_pads_init(&sd->entity, MSM_ISPIF_PADS_NUM,
					     pads);
		अगर (ret < 0) अणु
			dev_err(camss->dev, "Failed to init media entity: %d\n",
				ret);
			जाओ error;
		पूर्ण

		ret = v4l2_device_रेजिस्टर_subdev(v4l2_dev, sd);
		अगर (ret < 0) अणु
			dev_err(camss->dev, "Failed to register subdev: %d\n",
				ret);
			media_entity_cleanup(&sd->entity);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	क्रम (i--; i >= 0; i--) अणु
		काष्ठा v4l2_subdev *sd = &ispअगर->line[i].subdev;

		v4l2_device_unरेजिस्टर_subdev(sd);
		media_entity_cleanup(&sd->entity);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * msm_ispअगर_unरेजिस्टर_entities - Unरेजिस्टर ISPIF module subdev node
 * @ispअगर: ISPIF device
 */
व्योम msm_ispअगर_unरेजिस्टर_entities(काष्ठा ispअगर_device *ispअगर)
अणु
	पूर्णांक i;

	अगर (!ispअगर)
		वापस;

	mutex_destroy(&ispअगर->घातer_lock);
	mutex_destroy(&ispअगर->config_lock);

	क्रम (i = 0; i < ispअगर->line_num; i++) अणु
		काष्ठा v4l2_subdev *sd = &ispअगर->line[i].subdev;

		v4l2_device_unरेजिस्टर_subdev(sd);
		media_entity_cleanup(&sd->entity);
	पूर्ण
पूर्ण
