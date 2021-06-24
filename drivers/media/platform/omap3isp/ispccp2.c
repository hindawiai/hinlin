<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ispccp2.c
 *
 * TI OMAP3 ISP - CCP2 module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2010 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "isp.h"
#समावेश "ispreg.h"
#समावेश "ispccp2.h"

/* Number of LCX channels */
#घोषणा CCP2_LCx_CHANS_NUM			3
/* Max/Min size क्रम CCP2 video port */
#घोषणा ISPCCP2_DAT_START_MIN			0
#घोषणा ISPCCP2_DAT_START_MAX			4095
#घोषणा ISPCCP2_DAT_SIZE_MIN			0
#घोषणा ISPCCP2_DAT_SIZE_MAX			4095
#घोषणा ISPCCP2_VPCLK_FRACDIV			65536
#घोषणा ISPCCP2_LCx_CTRL_FORMAT_RAW8_DPCM10_VP	0x12
#घोषणा ISPCCP2_LCx_CTRL_FORMAT_RAW10_VP	0x16
/* Max/Min size क्रम CCP2 memory channel */
#घोषणा ISPCCP2_LCM_HSIZE_COUNT_MIN		16
#घोषणा ISPCCP2_LCM_HSIZE_COUNT_MAX		8191
#घोषणा ISPCCP2_LCM_HSIZE_SKIP_MIN		0
#घोषणा ISPCCP2_LCM_HSIZE_SKIP_MAX		8191
#घोषणा ISPCCP2_LCM_VSIZE_MIN			1
#घोषणा ISPCCP2_LCM_VSIZE_MAX			8191
#घोषणा ISPCCP2_LCM_HWORDS_MIN			1
#घोषणा ISPCCP2_LCM_HWORDS_MAX			4095
#घोषणा ISPCCP2_LCM_CTRL_BURST_SIZE_32X		5
#घोषणा ISPCCP2_LCM_CTRL_READ_THROTTLE_FULL	0
#घोषणा ISPCCP2_LCM_CTRL_SRC_DECOMPR_DPCM10	2
#घोषणा ISPCCP2_LCM_CTRL_SRC_FORMAT_RAW8	2
#घोषणा ISPCCP2_LCM_CTRL_SRC_FORMAT_RAW10	3
#घोषणा ISPCCP2_LCM_CTRL_DST_FORMAT_RAW10	3
#घोषणा ISPCCP2_LCM_CTRL_DST_PORT_VP		0
#घोषणा ISPCCP2_LCM_CTRL_DST_PORT_MEM		1

/* Set only the required bits */
#घोषणा BIT_SET(var, shअगरt, mask, val)			\
	करो अणु						\
		var = ((var) & ~((mask) << (shअगरt)))	\
			| ((val) << (shअगरt));		\
	पूर्ण जबतक (0)

/*
 * ccp2_prपूर्णांक_status - Prपूर्णांक current CCP2 module रेजिस्टर values.
 */
#घोषणा CCP2_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev, "###CCP2 " #name "=0x%08x\n", \
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_##name))

अटल व्योम ccp2_prपूर्णांक_status(काष्ठा isp_ccp2_device *ccp2)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);

	dev_dbg(isp->dev, "-------------CCP2 Register dump-------------\n");

	CCP2_PRINT_REGISTER(isp, SYSCONFIG);
	CCP2_PRINT_REGISTER(isp, SYSSTATUS);
	CCP2_PRINT_REGISTER(isp, LC01_IRQENABLE);
	CCP2_PRINT_REGISTER(isp, LC01_IRQSTATUS);
	CCP2_PRINT_REGISTER(isp, LC23_IRQENABLE);
	CCP2_PRINT_REGISTER(isp, LC23_IRQSTATUS);
	CCP2_PRINT_REGISTER(isp, LCM_IRQENABLE);
	CCP2_PRINT_REGISTER(isp, LCM_IRQSTATUS);
	CCP2_PRINT_REGISTER(isp, CTRL);
	CCP2_PRINT_REGISTER(isp, LCx_CTRL(0));
	CCP2_PRINT_REGISTER(isp, LCx_CODE(0));
	CCP2_PRINT_REGISTER(isp, LCx_STAT_START(0));
	CCP2_PRINT_REGISTER(isp, LCx_STAT_SIZE(0));
	CCP2_PRINT_REGISTER(isp, LCx_SOF_ADDR(0));
	CCP2_PRINT_REGISTER(isp, LCx_खातापूर्ण_ADDR(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_START(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_SIZE(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_PING_ADDR(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_PONG_ADDR(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_OFST(0));
	CCP2_PRINT_REGISTER(isp, LCM_CTRL);
	CCP2_PRINT_REGISTER(isp, LCM_VSIZE);
	CCP2_PRINT_REGISTER(isp, LCM_HSIZE);
	CCP2_PRINT_REGISTER(isp, LCM_PREFETCH);
	CCP2_PRINT_REGISTER(isp, LCM_SRC_ADDR);
	CCP2_PRINT_REGISTER(isp, LCM_SRC_OFST);
	CCP2_PRINT_REGISTER(isp, LCM_DST_ADDR);
	CCP2_PRINT_REGISTER(isp, LCM_DST_OFST);

	dev_dbg(isp->dev, "--------------------------------------------\n");
पूर्ण

/*
 * ccp2_reset - Reset the CCP2
 * @ccp2: poपूर्णांकer to ISP CCP2 device
 */
अटल व्योम ccp2_reset(काष्ठा isp_ccp2_device *ccp2)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);
	पूर्णांक i = 0;

	/* Reset the CSI1/CCP2B and रुको क्रम reset to complete */
	isp_reg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_SYSCONFIG,
		    ISPCCP2_SYSCONFIG_SOFT_RESET);
	जबतक (!(isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_SYSSTATUS) &
		 ISPCCP2_SYSSTATUS_RESET_DONE)) अणु
		udelay(10);
		अगर (i++ > 10) अणु  /* try पढ़ो 10 बार */
			dev_warn(isp->dev,
				"omap3_isp: timeout waiting for ccp2 reset\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * ccp2_pwr_cfg - Configure the घातer mode settings
 * @ccp2: poपूर्णांकer to ISP CCP2 device
 */
अटल व्योम ccp2_pwr_cfg(काष्ठा isp_ccp2_device *ccp2)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);

	isp_reg_ग_लिखोl(isp, ISPCCP2_SYSCONFIG_MSTANDBY_MODE_SMART |
			((isp->revision == ISP_REVISION_15_0 && isp->स्वतःidle) ?
			  ISPCCP2_SYSCONFIG_AUTO_IDLE : 0),
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_SYSCONFIG);
पूर्ण

/*
 * ccp2_अगर_enable - Enable CCP2 पूर्णांकerface.
 * @ccp2: poपूर्णांकer to ISP CCP2 device
 * @enable: enable/disable flag
 */
अटल पूर्णांक ccp2_अगर_enable(काष्ठा isp_ccp2_device *ccp2, u8 enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);
	पूर्णांक ret;
	पूर्णांक i;

	अगर (enable && ccp2->vdds_csib) अणु
		ret = regulator_enable(ccp2->vdds_csib);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Enable/Disable all the LCx channels */
	क्रम (i = 0; i < CCP2_LCx_CHANS_NUM; i++)
		isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_CTRL(i),
				ISPCCP2_LCx_CTRL_CHAN_EN,
				enable ? ISPCCP2_LCx_CTRL_CHAN_EN : 0);

	/* Enable/Disable ccp2 पूर्णांकerface in ccp2 mode */
	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL,
			ISPCCP2_CTRL_MODE | ISPCCP2_CTRL_IF_EN,
			enable ? (ISPCCP2_CTRL_MODE | ISPCCP2_CTRL_IF_EN) : 0);

	अगर (!enable && ccp2->vdds_csib)
		regulator_disable(ccp2->vdds_csib);

	वापस 0;
पूर्ण

/*
 * ccp2_mem_enable - Enable CCP2 memory पूर्णांकerface.
 * @ccp2: poपूर्णांकer to ISP CCP2 device
 * @enable: enable/disable flag
 */
अटल व्योम ccp2_mem_enable(काष्ठा isp_ccp2_device *ccp2, u8 enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);

	अगर (enable)
		ccp2_अगर_enable(ccp2, 0);

	/* Enable/Disable ccp2 पूर्णांकerface in ccp2 mode */
	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL,
			ISPCCP2_CTRL_MODE, enable ? ISPCCP2_CTRL_MODE : 0);

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_CTRL,
			ISPCCP2_LCM_CTRL_CHAN_EN,
			enable ? ISPCCP2_LCM_CTRL_CHAN_EN : 0);
पूर्ण

/*
 * ccp2_phyअगर_config - Initialize CCP2 phy पूर्णांकerface config
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 * @buscfg: CCP2 platक्रमm data
 *
 * Configure the CCP2 physical पूर्णांकerface module from platक्रमm data.
 *
 * Returns -EIO अगर strobe is chosen in CSI1 mode, or 0 on success.
 */
अटल पूर्णांक ccp2_phyअगर_config(काष्ठा isp_ccp2_device *ccp2,
			     स्थिर काष्ठा isp_ccp2_cfg *buscfg)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);
	u32 val;

	val = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL) |
			    ISPCCP2_CTRL_MODE;
	/* Data/strobe physical layer */
	BIT_SET(val, ISPCCP2_CTRL_PHY_SEL_SHIFT, ISPCCP2_CTRL_PHY_SEL_MASK,
		buscfg->phy_layer);
	BIT_SET(val, ISPCCP2_CTRL_IO_OUT_SEL_SHIFT,
		ISPCCP2_CTRL_IO_OUT_SEL_MASK, buscfg->ccp2_mode);
	BIT_SET(val, ISPCCP2_CTRL_INV_SHIFT, ISPCCP2_CTRL_INV_MASK,
		buscfg->strobe_clk_pol);
	BIT_SET(val, ISPCCP2_CTRL_VP_CLK_POL_SHIFT,
		ISPCCP2_CTRL_VP_CLK_POL_MASK, buscfg->vp_clk_pol);
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL);

	val = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL);
	अगर (!(val & ISPCCP2_CTRL_MODE)) अणु
		अगर (buscfg->ccp2_mode == ISP_CCP2_MODE_CCP2)
			dev_warn(isp->dev, "OMAP3 CCP2 bus not available\n");
		अगर (buscfg->phy_layer == ISP_CCP2_PHY_DATA_STROBE)
			/* Strobe mode requires CCP2 */
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ccp2_vp_config - Initialize CCP2 video port पूर्णांकerface.
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 * @vpclk_भाग: Video port भागisor
 *
 * Configure the CCP2 video port with the given घड़ी भागisor. The valid भागisor
 * values depend on the ISP revision:
 *
 * - revision 1.0 and 2.0	1 to 4
 * - revision 15.0		1 to 65536
 *
 * The exact भागisor value used might dअगरfer from the requested value, as ISP
 * revision 15.0 represent the भागisor by 65536 भागided by an पूर्णांकeger.
 */
अटल व्योम ccp2_vp_config(काष्ठा isp_ccp2_device *ccp2,
			   अचिन्हित पूर्णांक vpclk_भाग)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);
	u32 val;

	/* ISPCCP2_CTRL Video port */
	val = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL);
	val |= ISPCCP2_CTRL_VP_ONLY_EN;	/* Disable the memory ग_लिखो port */

	अगर (isp->revision == ISP_REVISION_15_0) अणु
		vpclk_भाग = clamp_t(अचिन्हित पूर्णांक, vpclk_भाग, 1, 65536);
		vpclk_भाग = min(ISPCCP2_VPCLK_FRACDIV / vpclk_भाग, 65535U);
		BIT_SET(val, ISPCCP2_CTRL_VPCLK_DIV_SHIFT,
			ISPCCP2_CTRL_VPCLK_DIV_MASK, vpclk_भाग);
	पूर्ण अन्यथा अणु
		vpclk_भाग = clamp_t(अचिन्हित पूर्णांक, vpclk_भाग, 1, 4);
		BIT_SET(val, ISPCCP2_CTRL_VP_OUT_CTRL_SHIFT,
			ISPCCP2_CTRL_VP_OUT_CTRL_MASK, vpclk_भाग - 1);
	पूर्ण

	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL);
पूर्ण

/*
 * ccp2_lcx_config - Initialize CCP2 logical channel पूर्णांकerface.
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 * @config: Poपूर्णांकer to ISP LCx config काष्ठाure.
 *
 * This will analyze the parameters passed by the पूर्णांकerface config
 * and configure CSI1/CCP2 logical channel
 *
 */
अटल व्योम ccp2_lcx_config(काष्ठा isp_ccp2_device *ccp2,
			    काष्ठा isp_पूर्णांकerface_lcx_config *config)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);
	u32 val, क्रमmat;

	चयन (config->क्रमmat) अणु
	हाल MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
		क्रमmat = ISPCCP2_LCx_CTRL_FORMAT_RAW8_DPCM10_VP;
		अवरोध;
	हाल MEDIA_BUS_FMT_SGRBG10_1X10:
	शेष:
		क्रमmat = ISPCCP2_LCx_CTRL_FORMAT_RAW10_VP;	/* RAW10+VP */
		अवरोध;
	पूर्ण
	/* ISPCCP2_LCx_CTRL logical channel #0 */
	val = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_CTRL(0))
			    | (ISPCCP2_LCx_CTRL_REGION_EN); /* Region */

	अगर (isp->revision == ISP_REVISION_15_0) अणु
		/* CRC */
		BIT_SET(val, ISPCCP2_LCx_CTRL_CRC_SHIFT_15_0,
			ISPCCP2_LCx_CTRL_CRC_MASK,
			config->crc);
		/* Format = RAW10+VP or RAW8+DPCM10+VP*/
		BIT_SET(val, ISPCCP2_LCx_CTRL_FORMAT_SHIFT_15_0,
			ISPCCP2_LCx_CTRL_FORMAT_MASK_15_0, क्रमmat);
	पूर्ण अन्यथा अणु
		BIT_SET(val, ISPCCP2_LCx_CTRL_CRC_SHIFT,
			ISPCCP2_LCx_CTRL_CRC_MASK,
			config->crc);

		BIT_SET(val, ISPCCP2_LCx_CTRL_FORMAT_SHIFT,
			ISPCCP2_LCx_CTRL_FORMAT_MASK, क्रमmat);
	पूर्ण
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_CTRL(0));

	/* ISPCCP2_DAT_START क्रम logical channel #0 */
	isp_reg_ग_लिखोl(isp, config->data_start << ISPCCP2_LCx_DAT_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_DAT_START(0));

	/* ISPCCP2_DAT_SIZE क्रम logical channel #0 */
	isp_reg_ग_लिखोl(isp, config->data_size << ISPCCP2_LCx_DAT_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_DAT_SIZE(0));

	/* Enable error IRQs क्रम logical channel #0 */
	val = ISPCCP2_LC01_IRQSTATUS_LC0_FIFO_OVF_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_CRC_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_FSP_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_FW_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_FSC_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_SSC_IRQ;

	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LC01_IRQSTATUS);
	isp_reg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LC01_IRQENABLE, val);
पूर्ण

/*
 * ccp2_अगर_configure - Configure ccp2 with data from sensor
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 *
 * Return 0 on success or a negative error code
 */
अटल पूर्णांक ccp2_अगर_configure(काष्ठा isp_ccp2_device *ccp2)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&ccp2->subdev.entity);
	स्थिर काष्ठा isp_bus_cfg *buscfg;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा media_pad *pad;
	काष्ठा v4l2_subdev *sensor;
	u32 lines = 0;
	पूर्णांक ret;

	ccp2_pwr_cfg(ccp2);

	pad = media_entity_remote_pad(&ccp2->pads[CCP2_PAD_SINK]);
	sensor = media_entity_to_v4l2_subdev(pad->entity);
	buscfg = v4l2_subdev_to_bus_cfg(pipe->बाह्यal);

	ret = ccp2_phyअगर_config(ccp2, &buscfg->bus.ccp2);
	अगर (ret < 0)
		वापस ret;

	ccp2_vp_config(ccp2, buscfg->bus.ccp2.vpclk_भाग + 1);

	v4l2_subdev_call(sensor, sensor, g_skip_top_lines, &lines);

	क्रमmat = &ccp2->क्रमmats[CCP2_PAD_SINK];

	ccp2->अगर_cfg.data_start = lines;
	ccp2->अगर_cfg.crc = buscfg->bus.ccp2.crc;
	ccp2->अगर_cfg.क्रमmat = क्रमmat->code;
	ccp2->अगर_cfg.data_size = क्रमmat->height;

	ccp2_lcx_config(ccp2, &ccp2->अगर_cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक ccp2_adjust_bandwidth(काष्ठा isp_ccp2_device *ccp2)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&ccp2->subdev.entity);
	काष्ठा isp_device *isp = to_isp_device(ccp2);
	स्थिर काष्ठा v4l2_mbus_framefmt *ofmt = &ccp2->क्रमmats[CCP2_PAD_SOURCE];
	अचिन्हित दीर्घ l3_ick = pipe->l3_ick;
	काष्ठा v4l2_fract *समयperframe;
	अचिन्हित पूर्णांक vpclk_भाग = 2;
	अचिन्हित पूर्णांक value;
	u64 bound;
	u64 area;

	/* Compute the minimum घड़ी भागisor, based on the pipeline maximum
	 * data rate. This is an असलolute lower bound अगर we करोn't want SBL
	 * overflows, so round the value up.
	 */
	vpclk_भाग = max_t(अचिन्हित पूर्णांक, DIV_ROUND_UP(l3_ick, pipe->max_rate),
			  vpclk_भाग);

	/* Compute the maximum घड़ी भागisor, based on the requested frame rate.
	 * This is a soft lower bound to achieve a frame rate equal or higher
	 * than the requested value, so round the value करोwn.
	 */
	समयperframe = &pipe->max_समयperframe;

	अगर (समयperframe->numerator) अणु
		area = ofmt->width * ofmt->height;
		bound = भाग_u64(area * समयperframe->denominator,
				समयperframe->numerator);
		value = min_t(u64, bound, l3_ick);
		vpclk_भाग = max_t(अचिन्हित पूर्णांक, l3_ick / value, vpclk_भाग);
	पूर्ण

	dev_dbg(isp->dev, "%s: minimum clock divisor = %u\n", __func__,
		vpclk_भाग);

	वापस vpclk_भाग;
पूर्ण

/*
 * ccp2_mem_configure - Initialize CCP2 memory input/output पूर्णांकerface
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 * @config: Poपूर्णांकer to ISP mem पूर्णांकerface config काष्ठाure
 *
 * This will analyze the parameters passed by the पूर्णांकerface config
 * काष्ठाure, and configure the respective रेजिस्टरs क्रम proper
 * CSI1/CCP2 memory input.
 */
अटल व्योम ccp2_mem_configure(काष्ठा isp_ccp2_device *ccp2,
			       काष्ठा isp_पूर्णांकerface_mem_config *config)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);
	u32 sink_pixcode = ccp2->क्रमmats[CCP2_PAD_SINK].code;
	u32 source_pixcode = ccp2->क्रमmats[CCP2_PAD_SOURCE].code;
	अचिन्हित पूर्णांक dpcm_decompress = 0;
	u32 val, hwords;

	अगर (sink_pixcode != source_pixcode &&
	    sink_pixcode == MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8)
		dpcm_decompress = 1;

	ccp2_pwr_cfg(ccp2);

	/* Hsize, Skip */
	isp_reg_ग_लिखोl(isp, ISPCCP2_LCM_HSIZE_SKIP_MIN |
		       (config->hsize_count << ISPCCP2_LCM_HSIZE_SHIFT),
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_HSIZE);

	/* Vsize, no. of lines */
	isp_reg_ग_लिखोl(isp, config->vsize_count << ISPCCP2_LCM_VSIZE_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_VSIZE);

	अगर (ccp2->video_in.bpl_padding == 0)
		config->src_ofst = 0;
	अन्यथा
		config->src_ofst = ccp2->video_in.bpl_value;

	isp_reg_ग_लिखोl(isp, config->src_ofst, OMAP3_ISP_IOMEM_CCP2,
		       ISPCCP2_LCM_SRC_OFST);

	/* Source and Destination क्रमmats */
	val = ISPCCP2_LCM_CTRL_DST_FORMAT_RAW10 <<
	      ISPCCP2_LCM_CTRL_DST_FORMAT_SHIFT;

	अगर (dpcm_decompress) अणु
		/* source क्रमmat is RAW8 */
		val |= ISPCCP2_LCM_CTRL_SRC_FORMAT_RAW8 <<
		       ISPCCP2_LCM_CTRL_SRC_FORMAT_SHIFT;

		/* RAW8 + DPCM10 - simple predictor */
		val |= ISPCCP2_LCM_CTRL_SRC_DPCM_PRED;

		/* enable source DPCM decompression */
		val |= ISPCCP2_LCM_CTRL_SRC_DECOMPR_DPCM10 <<
		       ISPCCP2_LCM_CTRL_SRC_DECOMPR_SHIFT;
	पूर्ण अन्यथा अणु
		/* source क्रमmat is RAW10 */
		val |= ISPCCP2_LCM_CTRL_SRC_FORMAT_RAW10 <<
		       ISPCCP2_LCM_CTRL_SRC_FORMAT_SHIFT;
	पूर्ण

	/* Burst size to 32x64 */
	val |= ISPCCP2_LCM_CTRL_BURST_SIZE_32X <<
	       ISPCCP2_LCM_CTRL_BURST_SIZE_SHIFT;

	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_CTRL);

	/* Prefetch setup */
	अगर (dpcm_decompress)
		hwords = (ISPCCP2_LCM_HSIZE_SKIP_MIN +
			  config->hsize_count) >> 3;
	अन्यथा
		hwords = (ISPCCP2_LCM_HSIZE_SKIP_MIN +
			  config->hsize_count) >> 2;

	isp_reg_ग_लिखोl(isp, hwords << ISPCCP2_LCM_PREFETCH_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_PREFETCH);

	/* Video port */
	isp_reg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL,
		    ISPCCP2_CTRL_IO_OUT_SEL | ISPCCP2_CTRL_MODE);
	ccp2_vp_config(ccp2, ccp2_adjust_bandwidth(ccp2));

	/* Clear LCM पूर्णांकerrupts */
	isp_reg_ग_लिखोl(isp, ISPCCP2_LCM_IRQSTATUS_OCPERROR_IRQ |
		       ISPCCP2_LCM_IRQSTATUS_खातापूर्ण_IRQ,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_IRQSTATUS);

	/* Enable LCM पूर्णांकerrupts */
	isp_reg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_IRQENABLE,
		    ISPCCP2_LCM_IRQSTATUS_खातापूर्ण_IRQ |
		    ISPCCP2_LCM_IRQSTATUS_OCPERROR_IRQ);
पूर्ण

/*
 * ccp2_set_inaddr - Sets memory address of input frame.
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 * @addr: 32bit memory address aligned on 32byte boundary.
 *
 * Configures the memory address from which the input frame is to be पढ़ो.
 */
अटल व्योम ccp2_set_inaddr(काष्ठा isp_ccp2_device *ccp2, u32 addr)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccp2);

	isp_reg_ग_लिखोl(isp, addr, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_SRC_ADDR);
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt handling
 */

अटल व्योम ccp2_isr_buffer(काष्ठा isp_ccp2_device *ccp2)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&ccp2->subdev.entity);
	काष्ठा isp_buffer *buffer;

	buffer = omap3isp_video_buffer_next(&ccp2->video_in);
	अगर (buffer != शून्य)
		ccp2_set_inaddr(ccp2, buffer->dma);

	pipe->state |= ISP_PIPELINE_IDLE_INPUT;

	अगर (ccp2->state == ISP_PIPELINE_STREAM_SINGLESHOT) अणु
		अगर (isp_pipeline_पढ़ोy(pipe))
			omap3isp_pipeline_set_stream(pipe,
						ISP_PIPELINE_STREAM_SINGLESHOT);
	पूर्ण
पूर्ण

/*
 * omap3isp_ccp2_isr - Handle ISP CCP2 पूर्णांकerrupts
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 *
 * This will handle the CCP2 पूर्णांकerrupts
 */
व्योम omap3isp_ccp2_isr(काष्ठा isp_ccp2_device *ccp2)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&ccp2->subdev.entity);
	काष्ठा isp_device *isp = to_isp_device(ccp2);
	अटल स्थिर u32 ISPCCP2_LC01_ERROR =
		ISPCCP2_LC01_IRQSTATUS_LC0_FIFO_OVF_IRQ |
		ISPCCP2_LC01_IRQSTATUS_LC0_CRC_IRQ |
		ISPCCP2_LC01_IRQSTATUS_LC0_FSP_IRQ |
		ISPCCP2_LC01_IRQSTATUS_LC0_FW_IRQ |
		ISPCCP2_LC01_IRQSTATUS_LC0_FSC_IRQ |
		ISPCCP2_LC01_IRQSTATUS_LC0_SSC_IRQ;
	u32 lcx_irqstatus, lcm_irqstatus;

	/* First clear the पूर्णांकerrupts */
	lcx_irqstatus = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCP2,
				      ISPCCP2_LC01_IRQSTATUS);
	isp_reg_ग_लिखोl(isp, lcx_irqstatus, OMAP3_ISP_IOMEM_CCP2,
		       ISPCCP2_LC01_IRQSTATUS);

	lcm_irqstatus = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCP2,
				      ISPCCP2_LCM_IRQSTATUS);
	isp_reg_ग_लिखोl(isp, lcm_irqstatus, OMAP3_ISP_IOMEM_CCP2,
		       ISPCCP2_LCM_IRQSTATUS);
	/* Errors */
	अगर (lcx_irqstatus & ISPCCP2_LC01_ERROR) अणु
		pipe->error = true;
		dev_dbg(isp->dev, "CCP2 err:%x\n", lcx_irqstatus);
		वापस;
	पूर्ण

	अगर (lcm_irqstatus & ISPCCP2_LCM_IRQSTATUS_OCPERROR_IRQ) अणु
		pipe->error = true;
		dev_dbg(isp->dev, "CCP2 OCP err:%x\n", lcm_irqstatus);
	पूर्ण

	अगर (omap3isp_module_sync_is_stopping(&ccp2->रुको, &ccp2->stopping))
		वापस;

	/* Handle queued buffers on frame end पूर्णांकerrupts */
	अगर (lcm_irqstatus & ISPCCP2_LCM_IRQSTATUS_खातापूर्ण_IRQ)
		ccp2_isr_buffer(ccp2);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 */

अटल स्थिर अचिन्हित पूर्णांक ccp2_fmts[] = अणु
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8,
पूर्ण;

/*
 * __ccp2_get_क्रमmat - helper function क्रम getting ccp2 क्रमmat
 * @ccp2  : Poपूर्णांकer to ISP CCP2 device
 * @cfg: V4L2 subdev pad configuration
 * @pad   : pad number
 * @which : wanted subdev क्रमmat
 * वापस क्रमmat काष्ठाure or शून्य on error
 */
अटल काष्ठा v4l2_mbus_framefmt *
__ccp2_get_क्रमmat(काष्ठा isp_ccp2_device *ccp2, काष्ठा v4l2_subdev_pad_config *cfg,
		     अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&ccp2->subdev, cfg, pad);
	अन्यथा
		वापस &ccp2->क्रमmats[pad];
पूर्ण

/*
 * ccp2_try_क्रमmat - Handle try क्रमmat by pad subdev method
 * @ccp2  : Poपूर्णांकer to ISP CCP2 device
 * @cfg: V4L2 subdev pad configuration
 * @pad   : pad num
 * @fmt   : poपूर्णांकer to v4l2 mbus क्रमmat काष्ठाure
 * @which : wanted subdev क्रमmat
 */
अटल व्योम ccp2_try_क्रमmat(काष्ठा isp_ccp2_device *ccp2,
			       काष्ठा v4l2_subdev_pad_config *cfg, अचिन्हित पूर्णांक pad,
			       काष्ठा v4l2_mbus_framefmt *fmt,
			       क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	चयन (pad) अणु
	हाल CCP2_PAD_SINK:
		अगर (fmt->code != MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8)
			fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

		अगर (ccp2->input == CCP2_INPUT_SENSOR) अणु
			fmt->width = clamp_t(u32, fmt->width,
					     ISPCCP2_DAT_START_MIN,
					     ISPCCP2_DAT_START_MAX);
			fmt->height = clamp_t(u32, fmt->height,
					      ISPCCP2_DAT_SIZE_MIN,
					      ISPCCP2_DAT_SIZE_MAX);
		पूर्ण अन्यथा अगर (ccp2->input == CCP2_INPUT_MEMORY) अणु
			fmt->width = clamp_t(u32, fmt->width,
					     ISPCCP2_LCM_HSIZE_COUNT_MIN,
					     ISPCCP2_LCM_HSIZE_COUNT_MAX);
			fmt->height = clamp_t(u32, fmt->height,
					      ISPCCP2_LCM_VSIZE_MIN,
					      ISPCCP2_LCM_VSIZE_MAX);
		पूर्ण
		अवरोध;

	हाल CCP2_PAD_SOURCE:
		/* Source क्रमmat - copy sink क्रमmat and change pixel code
		 * to SGRBG10_1X10 as we करोn't support CCP2 ग_लिखो to memory.
		 * When CCP2 ग_लिखो to memory feature will be added this
		 * should be changed properly.
		 */
		क्रमmat = __ccp2_get_क्रमmat(ccp2, cfg, CCP2_PAD_SINK, which);
		स_नकल(fmt, क्रमmat, माप(*fmt));
		fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
		अवरोध;
	पूर्ण

	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
पूर्ण

/*
 * ccp2_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd     : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @code   : poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ccp2_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा isp_ccp2_device *ccp2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	अगर (code->pad == CCP2_PAD_SINK) अणु
		अगर (code->index >= ARRAY_SIZE(ccp2_fmts))
			वापस -EINVAL;

		code->code = ccp2_fmts[code->index];
	पूर्ण अन्यथा अणु
		अगर (code->index != 0)
			वापस -EINVAL;

		क्रमmat = __ccp2_get_क्रमmat(ccp2, cfg, CCP2_PAD_SINK,
					      code->which);
		code->code = क्रमmat->code;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccp2_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा isp_ccp2_device *ccp2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	ccp2_try_क्रमmat(ccp2, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	ccp2_try_क्रमmat(ccp2, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * ccp2_get_क्रमmat - Handle get क्रमmat by pads subdev method
 * @sd    : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @fmt   : poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ccp2_get_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_ccp2_device *ccp2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __ccp2_get_क्रमmat(ccp2, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;
	वापस 0;
पूर्ण

/*
 * ccp2_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd    : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @fmt   : poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापसs zero
 */
अटल पूर्णांक ccp2_set_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_ccp2_device *ccp2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __ccp2_get_क्रमmat(ccp2, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	ccp2_try_क्रमmat(ccp2, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == CCP2_PAD_SINK) अणु
		क्रमmat = __ccp2_get_क्रमmat(ccp2, cfg, CCP2_PAD_SOURCE,
					   fmt->which);
		*क्रमmat = fmt->क्रमmat;
		ccp2_try_क्रमmat(ccp2, cfg, CCP2_PAD_SOURCE, क्रमmat, fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ccp2_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISP CCP2 V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values. If fh is not शून्य, try
 * क्रमmats are initialized on the file handle. Otherwise active क्रमmats are
 * initialized on the device.
 */
अटल पूर्णांक ccp2_init_क्रमmats(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.pad = CCP2_PAD_SINK;
	क्रमmat.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	क्रमmat.क्रमmat.width = 4096;
	क्रमmat.क्रमmat.height = 4096;
	ccp2_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);

	वापस 0;
पूर्ण

/*
 * ccp2_s_stream - Enable/Disable streaming on ccp2 subdev
 * @sd    : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @enable: 1 == Enable, 0 == Disable
 * वापस zero
 */
अटल पूर्णांक ccp2_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा isp_ccp2_device *ccp2 = v4l2_get_subdevdata(sd);
	काष्ठा isp_device *isp = to_isp_device(ccp2);
	काष्ठा device *dev = to_device(ccp2);
	पूर्णांक ret;

	अगर (ccp2->state == ISP_PIPELINE_STREAM_STOPPED) अणु
		अगर (enable == ISP_PIPELINE_STREAM_STOPPED)
			वापस 0;
		atomic_set(&ccp2->stopping, 0);
	पूर्ण

	चयन (enable) अणु
	हाल ISP_PIPELINE_STREAM_CONTINUOUS:
		अगर (ccp2->phy) अणु
			ret = omap3isp_csiphy_acquire(ccp2->phy, &sd->entity);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		ccp2_अगर_configure(ccp2);
		ccp2_prपूर्णांक_status(ccp2);

		/* Enable CSI1/CCP2 पूर्णांकerface */
		ret = ccp2_अगर_enable(ccp2, 1);
		अगर (ret < 0) अणु
			अगर (ccp2->phy)
				omap3isp_csiphy_release(ccp2->phy);
			वापस ret;
		पूर्ण
		अवरोध;

	हाल ISP_PIPELINE_STREAM_SINGLESHOT:
		अगर (ccp2->state != ISP_PIPELINE_STREAM_SINGLESHOT) अणु
			काष्ठा v4l2_mbus_framefmt *क्रमmat;

			क्रमmat = &ccp2->क्रमmats[CCP2_PAD_SINK];

			ccp2->mem_cfg.hsize_count = क्रमmat->width;
			ccp2->mem_cfg.vsize_count = क्रमmat->height;
			ccp2->mem_cfg.src_ofst = 0;

			ccp2_mem_configure(ccp2, &ccp2->mem_cfg);
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_CSI1_READ);
			ccp2_prपूर्णांक_status(ccp2);
		पूर्ण
		ccp2_mem_enable(ccp2, 1);
		अवरोध;

	हाल ISP_PIPELINE_STREAM_STOPPED:
		अगर (omap3isp_module_sync_idle(&sd->entity, &ccp2->रुको,
					      &ccp2->stopping))
			dev_dbg(dev, "%s: module stop timeout.\n", sd->name);
		अगर (ccp2->input == CCP2_INPUT_MEMORY) अणु
			ccp2_mem_enable(ccp2, 0);
			omap3isp_sbl_disable(isp, OMAP3_ISP_SBL_CSI1_READ);
		पूर्ण अन्यथा अगर (ccp2->input == CCP2_INPUT_SENSOR) अणु
			/* Disable CSI1/CCP2 पूर्णांकerface */
			ccp2_अगर_enable(ccp2, 0);
			अगर (ccp2->phy)
				omap3isp_csiphy_release(ccp2->phy);
		पूर्ण
		अवरोध;
	पूर्ण

	ccp2->state = enable;
	वापस 0;
पूर्ण

/* subdev video operations */
अटल स्थिर काष्ठा v4l2_subdev_video_ops ccp2_sd_video_ops = अणु
	.s_stream = ccp2_s_stream,
पूर्ण;

/* subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops ccp2_sd_pad_ops = अणु
	.क्रमागत_mbus_code = ccp2_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ccp2_क्रमागत_frame_size,
	.get_fmt = ccp2_get_क्रमmat,
	.set_fmt = ccp2_set_क्रमmat,
पूर्ण;

/* subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops ccp2_sd_ops = अणु
	.video = &ccp2_sd_video_ops,
	.pad = &ccp2_sd_pad_ops,
पूर्ण;

/* subdev पूर्णांकernal operations */
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ccp2_sd_पूर्णांकernal_ops = अणु
	.खोलो = ccp2_init_क्रमmats,
पूर्ण;

/* --------------------------------------------------------------------------
 * ISP ccp2 video device node
 */

/*
 * ccp2_video_queue - Queue video buffer.
 * @video : Poपूर्णांकer to isp video काष्ठाure
 * @buffer: Poपूर्णांकer to isp_buffer काष्ठाure
 * वापस -EIO or zero on success
 */
अटल पूर्णांक ccp2_video_queue(काष्ठा isp_video *video, काष्ठा isp_buffer *buffer)
अणु
	काष्ठा isp_ccp2_device *ccp2 = &video->isp->isp_ccp2;

	ccp2_set_inaddr(ccp2, buffer->dma);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा isp_video_operations ccp2_video_ops = अणु
	.queue = ccp2_video_queue,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media entity operations
 */

/*
 * ccp2_link_setup - Setup ccp2 connections.
 * @entity : Poपूर्णांकer to media entity काष्ठाure
 * @local  : Poपूर्णांकer to local pad array
 * @remote : Poपूर्णांकer to remote pad array
 * @flags  : Link flags
 * वापस -EINVAL on error or zero on success
 */
अटल पूर्णांक ccp2_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा isp_ccp2_device *ccp2 = v4l2_get_subdevdata(sd);
	अचिन्हित पूर्णांक index = local->index;

	/* FIXME: this is actually a hack! */
	अगर (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	चयन (index) अणु
	हाल CCP2_PAD_SINK:
		/* पढ़ो from memory */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (ccp2->input == CCP2_INPUT_SENSOR)
				वापस -EBUSY;
			ccp2->input = CCP2_INPUT_MEMORY;
		पूर्ण अन्यथा अणु
			अगर (ccp2->input == CCP2_INPUT_MEMORY)
				ccp2->input = CCP2_INPUT_NONE;
		पूर्ण
		अवरोध;

	हाल CCP2_PAD_SINK | 2 << 16:
		/* पढ़ो from sensor/phy */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (ccp2->input == CCP2_INPUT_MEMORY)
				वापस -EBUSY;
			ccp2->input = CCP2_INPUT_SENSOR;
		पूर्ण अन्यथा अणु
			अगर (ccp2->input == CCP2_INPUT_SENSOR)
				ccp2->input = CCP2_INPUT_NONE;
		पूर्ण अवरोध;

	हाल CCP2_PAD_SOURCE | 2 << 16:
		/* ग_लिखो to video port/ccdc */
		अगर (flags & MEDIA_LNK_FL_ENABLED)
			ccp2->output = CCP2_OUTPUT_CCDC;
		अन्यथा
			ccp2->output = CCP2_OUTPUT_NONE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations ccp2_media_ops = अणु
	.link_setup = ccp2_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
 * omap3isp_ccp2_unरेजिस्टर_entities - Unरेजिस्टर media entities: subdev
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 */
व्योम omap3isp_ccp2_unरेजिस्टर_entities(काष्ठा isp_ccp2_device *ccp2)
अणु
	v4l2_device_unरेजिस्टर_subdev(&ccp2->subdev);
	omap3isp_video_unरेजिस्टर(&ccp2->video_in);
पूर्ण

/*
 * omap3isp_ccp2_रेजिस्टर_entities - Register the subdev media entity
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 * @vdev: Poपूर्णांकer to v4l device
 * वापस negative error code or zero on success
 */

पूर्णांक omap3isp_ccp2_रेजिस्टर_entities(काष्ठा isp_ccp2_device *ccp2,
				    काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video nodes. */
	ccp2->subdev.dev = vdev->mdev->dev;
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &ccp2->subdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap3isp_video_रेजिस्टर(&ccp2->video_in, vdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	omap3isp_ccp2_unरेजिस्टर_entities(ccp2);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP ccp2 initialisation and cleanup
 */

/*
 * ccp2_init_entities - Initialize ccp2 subdev and media entity.
 * @ccp2: Poपूर्णांकer to ISP CCP2 device
 * वापस negative error code or zero on success
 */
अटल पूर्णांक ccp2_init_entities(काष्ठा isp_ccp2_device *ccp2)
अणु
	काष्ठा v4l2_subdev *sd = &ccp2->subdev;
	काष्ठा media_pad *pads = ccp2->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	ccp2->input = CCP2_INPUT_NONE;
	ccp2->output = CCP2_OUTPUT_NONE;

	v4l2_subdev_init(sd, &ccp2_sd_ops);
	sd->पूर्णांकernal_ops = &ccp2_sd_पूर्णांकernal_ops;
	strscpy(sd->name, "OMAP3 ISP CCP2", माप(sd->name));
	sd->grp_id = 1 << 16;   /* group ID क्रम isp subdevs */
	v4l2_set_subdevdata(sd, ccp2);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[CCP2_PAD_SINK].flags = MEDIA_PAD_FL_SINK
				    | MEDIA_PAD_FL_MUST_CONNECT;
	pads[CCP2_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &ccp2_media_ops;
	ret = media_entity_pads_init(me, CCP2_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	ccp2_init_क्रमmats(sd, शून्य);

	/*
	 * The CCP2 has weird line alignment requirements, possibly caused by
	 * DPCM8 decompression. Line length क्रम data पढ़ो from memory must be a
	 * multiple of 128 bits (16 bytes) in continuous mode (when no padding
	 * is present at end of lines). Additionally, अगर padding is used, the
	 * padded line length must be a multiple of 32 bytes. To simplअगरy the
	 * implementation we use a fixed 32 bytes alignment regardless of the
	 * input क्रमmat and width. If strict 128 bits alignment support is
	 * required ispvideo will need to be made aware of this special dual
	 * alignment requirements.
	 */
	ccp2->video_in.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ccp2->video_in.bpl_alignment = 32;
	ccp2->video_in.bpl_max = 0xffffffe0;
	ccp2->video_in.isp = to_isp_device(ccp2);
	ccp2->video_in.ops = &ccp2_video_ops;
	ccp2->video_in.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;

	ret = omap3isp_video_init(&ccp2->video_in, "CCP2");
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	media_entity_cleanup(&ccp2->subdev.entity);
	वापस ret;
पूर्ण

/*
 * omap3isp_ccp2_init - CCP2 initialization.
 * @isp : Poपूर्णांकer to ISP device
 * वापस negative error code or zero on success
 */
पूर्णांक omap3isp_ccp2_init(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_ccp2_device *ccp2 = &isp->isp_ccp2;
	पूर्णांक ret;

	init_रुकोqueue_head(&ccp2->रुको);

	/*
	 * On the OMAP34xx the CSI1 receiver is operated in the CSIb IO
	 * complex, which is घातered by vdds_csib घातer rail. Hence the
	 * request क्रम the regulator.
	 *
	 * On the OMAP36xx, the CCP2 uses the CSI PHY1 or PHY2, shared with
	 * the CSI2c or CSI2a receivers. The PHY then needs to be explicitly
	 * configured.
	 *
	 * TODO: Don't hardcode the usage of PHY1 (shared with CSI2c).
	 */
	अगर (isp->revision == ISP_REVISION_2_0) अणु
		ccp2->vdds_csib = devm_regulator_get(isp->dev, "vdds_csib");
		अगर (IS_ERR(ccp2->vdds_csib)) अणु
			अगर (PTR_ERR(ccp2->vdds_csib) == -EPROBE_DEFER) अणु
				dev_dbg(isp->dev,
					"Can't get regulator vdds_csib, deferring probing\n");
				वापस -EPROBE_DEFER;
			पूर्ण
			dev_dbg(isp->dev,
				"Could not get regulator vdds_csib\n");
			ccp2->vdds_csib = शून्य;
		पूर्ण
		ccp2->phy = &isp->isp_csiphy2;
	पूर्ण अन्यथा अगर (isp->revision == ISP_REVISION_15_0) अणु
		ccp2->phy = &isp->isp_csiphy1;
	पूर्ण

	ret = ccp2_init_entities(ccp2);
	अगर (ret < 0)
		वापस ret;

	ccp2_reset(ccp2);
	वापस 0;
पूर्ण

/*
 * omap3isp_ccp2_cleanup - CCP2 un-initialization
 * @isp : Poपूर्णांकer to ISP device
 */
व्योम omap3isp_ccp2_cleanup(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_ccp2_device *ccp2 = &isp->isp_ccp2;

	omap3isp_video_cleanup(&ccp2->video_in);
	media_entity_cleanup(&ccp2->subdev.entity);
पूर्ण
