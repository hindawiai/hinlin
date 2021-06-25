<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isp.c
 *
 * TI OMAP3 ISP - Core
 *
 * Copyright (C) 2006-2010 Nokia Corporation
 * Copyright (C) 2007-2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 *
 * Contributors:
 *	Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	Sakari Ailus <sakari.ailus@iki.fi>
 *	David Cohen <dacohen@gmail.com>
 *	Stanimir Varbanov <svarbanov@mm-sol.com>
 *	Vimarsh Zutshi <vimarsh.zutshi@gmail.com>
 *	Tuukka Toivonen <tuukkat76@gmail.com>
 *	Sergio Aguirre <saaguirre@ti.com>
 *	Antti Koskipaa <akoskipa@gmail.com>
 *	Ivan T. Ivanov <iivanov@mm-sol.com>
 *	RaniSuneela <r-m@ti.com>
 *	Atanas Filipov <afilipov@mm-sol.com>
 *	Gjorgji Rosikopulos <grosikopulos@mm-sol.com>
 *	Hiroshi DOYU <hiroshi.करोyu@nokia.com>
 *	Nayden Kanchev <nkanchev@mm-sol.com>
 *	Phil Carmody <ext-phil.2.carmody@nokia.com>
 *	Artem Bityutskiy <artem.bityutskiy@nokia.com>
 *	Dominic Curran <dcurran@ti.com>
 *	Ilkka Myllyperkio <ilkka.myllyperkio@sofica.fi>
 *	Pallavi Kulkarni <p-kulkarni@ti.com>
 *	Vaibhav Hiremath <hvaibhav@ti.com>
 *	Mohit Jalori <mjalori@ti.com>
 *	Sameer Venkatraman <sameerv@ti.com>
 *	Senthilvaभागu Guruswamy <svaभागu@ti.com>
 *	Thara Gopinath <thara@ti.com>
 *	Toni Leinonen <toni.leinonen@nokia.com>
 *	Troy Laramy <t-laramy@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/omap-iommu.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>

#अगर_घोषित CONFIG_ARM_DMA_USE_IOMMU
#समावेश <यंत्र/dma-iommu.h>
#पूर्ण_अगर

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mc.h>

#समावेश "isp.h"
#समावेश "ispreg.h"
#समावेश "ispccdc.h"
#समावेश "isppreview.h"
#समावेश "ispresizer.h"
#समावेश "ispcsi2.h"
#समावेश "ispccp2.h"
#समावेश "isph3a.h"
#समावेश "isphist.h"

अटल अचिन्हित पूर्णांक स्वतःidle;
module_param(स्वतःidle, पूर्णांक, 0444);
MODULE_PARM_DESC(स्वतःidle, "Enable OMAP3ISP AUTOIDLE support");

अटल व्योम isp_save_ctx(काष्ठा isp_device *isp);

अटल व्योम isp_restore_ctx(काष्ठा isp_device *isp);

अटल स्थिर काष्ठा isp_res_mapping isp_res_maps[] = अणु
	अणु
		.isp_rev = ISP_REVISION_2_0,
		.offset = अणु
			/* first MMIO area */
			0x0000, /* base, len 0x0070 */
			0x0400, /* ccp2, len 0x01f0 */
			0x0600, /* ccdc, len 0x00a8 */
			0x0a00, /* hist, len 0x0048 */
			0x0c00, /* h3a, len 0x0060 */
			0x0e00, /* preview, len 0x00a0 */
			0x1000, /* resizer, len 0x00ac */
			0x1200, /* sbl, len 0x00fc */
			/* second MMIO area */
			0x0000, /* csi2a, len 0x0170 */
			0x0170, /* csiphy2, len 0x000c */
		पूर्ण,
		.phy_type = ISP_PHY_TYPE_3430,
	पूर्ण,
	अणु
		.isp_rev = ISP_REVISION_15_0,
		.offset = अणु
			/* first MMIO area */
			0x0000, /* base, len 0x0070 */
			0x0400, /* ccp2, len 0x01f0 */
			0x0600, /* ccdc, len 0x00a8 */
			0x0a00, /* hist, len 0x0048 */
			0x0c00, /* h3a, len 0x0060 */
			0x0e00, /* preview, len 0x00a0 */
			0x1000, /* resizer, len 0x00ac */
			0x1200, /* sbl, len 0x00fc */
			/* second MMIO area */
			0x0000, /* csi2a, len 0x0170 (1st area) */
			0x0170, /* csiphy2, len 0x000c */
			0x01c0, /* csi2a, len 0x0040 (2nd area) */
			0x0400, /* csi2c, len 0x0170 (1st area) */
			0x0570, /* csiphy1, len 0x000c */
			0x05c0, /* csi2c, len 0x0040 (2nd area) */
		पूर्ण,
		.phy_type = ISP_PHY_TYPE_3630,
	पूर्ण,
पूर्ण;

/* Structure क्रम saving/restoring ISP module रेजिस्टरs */
अटल काष्ठा isp_reg isp_reg_list[] = अणु
	अणुOMAP3_ISP_IOMEM_MAIN, ISP_SYSCONFIG, 0पूर्ण,
	अणुOMAP3_ISP_IOMEM_MAIN, ISP_CTRL, 0पूर्ण,
	अणुOMAP3_ISP_IOMEM_MAIN, ISP_TCTRL_CTRL, 0पूर्ण,
	अणु0, ISP_TOK_TERM, 0पूर्ण
पूर्ण;

/*
 * omap3isp_flush - Post pending L3 bus ग_लिखोs by करोing a रेजिस्टर पढ़ोback
 * @isp: OMAP3 ISP device
 *
 * In order to क्रमce posting of pending ग_लिखोs, we need to ग_लिखो and
 * पढ़ोback the same रेजिस्टर, in this हाल the revision रेजिस्टर.
 *
 * See this link क्रम reference:
 *   https://www.mail-archive.com/linux-omap@vger.kernel.org/msg08149.hपंचांगl
 */
व्योम omap3isp_flush(काष्ठा isp_device *isp)
अणु
	isp_reg_ग_लिखोl(isp, 0, OMAP3_ISP_IOMEM_MAIN, ISP_REVISION);
	isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_MAIN, ISP_REVISION);
पूर्ण

/* -----------------------------------------------------------------------------
 * XCLK
 */

#घोषणा to_isp_xclk(_hw)	container_of(_hw, काष्ठा isp_xclk, hw)

अटल व्योम isp_xclk_update(काष्ठा isp_xclk *xclk, u32 भागider)
अणु
	चयन (xclk->id) अणु
	हाल ISP_XCLK_A:
		isp_reg_clr_set(xclk->isp, OMAP3_ISP_IOMEM_MAIN, ISP_TCTRL_CTRL,
				ISPTCTRL_CTRL_DIVA_MASK,
				भागider << ISPTCTRL_CTRL_DIVA_SHIFT);
		अवरोध;
	हाल ISP_XCLK_B:
		isp_reg_clr_set(xclk->isp, OMAP3_ISP_IOMEM_MAIN, ISP_TCTRL_CTRL,
				ISPTCTRL_CTRL_DIVB_MASK,
				भागider << ISPTCTRL_CTRL_DIVB_SHIFT);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक isp_xclk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा isp_xclk *xclk = to_isp_xclk(hw);

	omap3isp_get(xclk->isp);

	वापस 0;
पूर्ण

अटल व्योम isp_xclk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा isp_xclk *xclk = to_isp_xclk(hw);

	omap3isp_put(xclk->isp);
पूर्ण

अटल पूर्णांक isp_xclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा isp_xclk *xclk = to_isp_xclk(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&xclk->lock, flags);
	isp_xclk_update(xclk, xclk->भागider);
	xclk->enabled = true;
	spin_unlock_irqrestore(&xclk->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम isp_xclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा isp_xclk *xclk = to_isp_xclk(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&xclk->lock, flags);
	isp_xclk_update(xclk, 0);
	xclk->enabled = false;
	spin_unlock_irqrestore(&xclk->lock, flags);
पूर्ण

अटल अचिन्हित दीर्घ isp_xclk_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा isp_xclk *xclk = to_isp_xclk(hw);

	वापस parent_rate / xclk->भागider;
पूर्ण

अटल u32 isp_xclk_calc_भागider(अचिन्हित दीर्घ *rate, अचिन्हित दीर्घ parent_rate)
अणु
	u32 भागider;

	अगर (*rate >= parent_rate) अणु
		*rate = parent_rate;
		वापस ISPTCTRL_CTRL_DIV_BYPASS;
	पूर्ण

	अगर (*rate == 0)
		*rate = 1;

	भागider = DIV_ROUND_CLOSEST(parent_rate, *rate);
	अगर (भागider >= ISPTCTRL_CTRL_DIV_BYPASS)
		भागider = ISPTCTRL_CTRL_DIV_BYPASS - 1;

	*rate = parent_rate / भागider;
	वापस भागider;
पूर्ण

अटल दीर्घ isp_xclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	isp_xclk_calc_भागider(&rate, *parent_rate);
	वापस rate;
पूर्ण

अटल पूर्णांक isp_xclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा isp_xclk *xclk = to_isp_xclk(hw);
	अचिन्हित दीर्घ flags;
	u32 भागider;

	भागider = isp_xclk_calc_भागider(&rate, parent_rate);

	spin_lock_irqsave(&xclk->lock, flags);

	xclk->भागider = भागider;
	अगर (xclk->enabled)
		isp_xclk_update(xclk, भागider);

	spin_unlock_irqrestore(&xclk->lock, flags);

	dev_dbg(xclk->isp->dev, "%s: cam_xclk%c set to %lu Hz (div %u)\n",
		__func__, xclk->id == ISP_XCLK_A ? 'a' : 'b', rate, भागider);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops isp_xclk_ops = अणु
	.prepare = isp_xclk_prepare,
	.unprepare = isp_xclk_unprepare,
	.enable = isp_xclk_enable,
	.disable = isp_xclk_disable,
	.recalc_rate = isp_xclk_recalc_rate,
	.round_rate = isp_xclk_round_rate,
	.set_rate = isp_xclk_set_rate,
पूर्ण;

अटल स्थिर अक्षर *isp_xclk_parent_name = "cam_mclk";

अटल काष्ठा clk *isp_xclk_src_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	अचिन्हित पूर्णांक idx = clkspec->args[0];
	काष्ठा isp_device *isp = data;

	अगर (idx >= ARRAY_SIZE(isp->xclks))
		वापस ERR_PTR(-ENOENT);

	वापस isp->xclks[idx].clk;
पूर्ण

अटल पूर्णांक isp_xclk_init(काष्ठा isp_device *isp)
अणु
	काष्ठा device_node *np = isp->dev->of_node;
	काष्ठा clk_init_data init = अणुपूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(isp->xclks); ++i)
		isp->xclks[i].clk = ERR_PTR(-EINVAL);

	क्रम (i = 0; i < ARRAY_SIZE(isp->xclks); ++i) अणु
		काष्ठा isp_xclk *xclk = &isp->xclks[i];

		xclk->isp = isp;
		xclk->id = i == 0 ? ISP_XCLK_A : ISP_XCLK_B;
		xclk->भागider = 1;
		spin_lock_init(&xclk->lock);

		init.name = i == 0 ? "cam_xclka" : "cam_xclkb";
		init.ops = &isp_xclk_ops;
		init.parent_names = &isp_xclk_parent_name;
		init.num_parents = 1;

		xclk->hw.init = &init;
		/*
		 * The first argument is शून्य in order to aव्योम circular
		 * reference, as this driver takes reference on the
		 * sensor subdevice modules and the sensors would take
		 * reference on this module through clk_get().
		 */
		xclk->clk = clk_रेजिस्टर(शून्य, &xclk->hw);
		अगर (IS_ERR(xclk->clk))
			वापस PTR_ERR(xclk->clk);
	पूर्ण

	अगर (np)
		of_clk_add_provider(np, isp_xclk_src_get, isp);

	वापस 0;
पूर्ण

अटल व्योम isp_xclk_cleanup(काष्ठा isp_device *isp)
अणु
	काष्ठा device_node *np = isp->dev->of_node;
	अचिन्हित पूर्णांक i;

	अगर (np)
		of_clk_del_provider(np);

	क्रम (i = 0; i < ARRAY_SIZE(isp->xclks); ++i) अणु
		काष्ठा isp_xclk *xclk = &isp->xclks[i];

		अगर (!IS_ERR(xclk->clk))
			clk_unरेजिस्टर(xclk->clk);
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupts
 */

/*
 * isp_enable_पूर्णांकerrupts - Enable ISP पूर्णांकerrupts.
 * @isp: OMAP3 ISP device
 */
अटल व्योम isp_enable_पूर्णांकerrupts(काष्ठा isp_device *isp)
अणु
	अटल स्थिर u32 irq = IRQ0ENABLE_CSIA_IRQ
			     | IRQ0ENABLE_CSIB_IRQ
			     | IRQ0ENABLE_CCDC_LSC_PREF_ERR_IRQ
			     | IRQ0ENABLE_CCDC_LSC_DONE_IRQ
			     | IRQ0ENABLE_CCDC_VD0_IRQ
			     | IRQ0ENABLE_CCDC_VD1_IRQ
			     | IRQ0ENABLE_HS_VS_IRQ
			     | IRQ0ENABLE_HIST_DONE_IRQ
			     | IRQ0ENABLE_H3A_AWB_DONE_IRQ
			     | IRQ0ENABLE_H3A_AF_DONE_IRQ
			     | IRQ0ENABLE_PRV_DONE_IRQ
			     | IRQ0ENABLE_RSZ_DONE_IRQ;

	isp_reg_ग_लिखोl(isp, irq, OMAP3_ISP_IOMEM_MAIN, ISP_IRQ0STATUS);
	isp_reg_ग_लिखोl(isp, irq, OMAP3_ISP_IOMEM_MAIN, ISP_IRQ0ENABLE);
पूर्ण

/*
 * isp_disable_पूर्णांकerrupts - Disable ISP पूर्णांकerrupts.
 * @isp: OMAP3 ISP device
 */
अटल व्योम isp_disable_पूर्णांकerrupts(काष्ठा isp_device *isp)
अणु
	isp_reg_ग_लिखोl(isp, 0, OMAP3_ISP_IOMEM_MAIN, ISP_IRQ0ENABLE);
पूर्ण

/*
 * isp_core_init - ISP core settings
 * @isp: OMAP3 ISP device
 * @idle: Consider idle state.
 *
 * Set the घातer settings क्रम the ISP and SBL bus and configure the HS/VS
 * पूर्णांकerrupt source.
 *
 * We need to configure the HS/VS पूर्णांकerrupt source beक्रमe पूर्णांकerrupts get
 * enabled, as the sensor might be मुक्त-running and the ISP शेष setting
 * (HS edge) would put an unnecessary burden on the CPU.
 */
अटल व्योम isp_core_init(काष्ठा isp_device *isp, पूर्णांक idle)
अणु
	isp_reg_ग_लिखोl(isp,
		       ((idle ? ISP_SYSCONFIG_MIDLEMODE_SMARTSTANDBY :
				ISP_SYSCONFIG_MIDLEMODE_FORCESTANDBY) <<
			ISP_SYSCONFIG_MIDLEMODE_SHIFT) |
			((isp->revision == ISP_REVISION_15_0) ?
			  ISP_SYSCONFIG_AUTOIDLE : 0),
		       OMAP3_ISP_IOMEM_MAIN, ISP_SYSCONFIG);

	isp_reg_ग_लिखोl(isp,
		       (isp->स्वतःidle ? ISPCTRL_SBL_AUTOIDLE : 0) |
		       ISPCTRL_SYNC_DETECT_VSRISE,
		       OMAP3_ISP_IOMEM_MAIN, ISP_CTRL);
पूर्ण

/*
 * Configure the bridge and lane shअगरter. Valid inमाला_दो are
 *
 * CCDC_INPUT_PARALLEL: Parallel पूर्णांकerface
 * CCDC_INPUT_CSI2A: CSI2a receiver
 * CCDC_INPUT_CCP2B: CCP2b receiver
 * CCDC_INPUT_CSI2C: CSI2c receiver
 *
 * The bridge and lane shअगरter are configured according to the selected input
 * and the ISP platक्रमm data.
 */
व्योम omap3isp_configure_bridge(काष्ठा isp_device *isp,
			       क्रमागत ccdc_input_entity input,
			       स्थिर काष्ठा isp_parallel_cfg *parcfg,
			       अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक bridge)
अणु
	u32 ispctrl_val;

	ispctrl_val  = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_MAIN, ISP_CTRL);
	ispctrl_val &= ~ISPCTRL_SHIFT_MASK;
	ispctrl_val &= ~ISPCTRL_PAR_CLK_POL_INV;
	ispctrl_val &= ~ISPCTRL_PAR_SER_CLK_SEL_MASK;
	ispctrl_val &= ~ISPCTRL_PAR_BRIDGE_MASK;
	ispctrl_val |= bridge;

	चयन (input) अणु
	हाल CCDC_INPUT_PARALLEL:
		ispctrl_val |= ISPCTRL_PAR_SER_CLK_SEL_PARALLEL;
		ispctrl_val |= parcfg->clk_pol << ISPCTRL_PAR_CLK_POL_SHIFT;
		shअगरt += parcfg->data_lane_shअगरt;
		अवरोध;

	हाल CCDC_INPUT_CSI2A:
		ispctrl_val |= ISPCTRL_PAR_SER_CLK_SEL_CSIA;
		अवरोध;

	हाल CCDC_INPUT_CCP2B:
		ispctrl_val |= ISPCTRL_PAR_SER_CLK_SEL_CSIB;
		अवरोध;

	हाल CCDC_INPUT_CSI2C:
		ispctrl_val |= ISPCTRL_PAR_SER_CLK_SEL_CSIC;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	ispctrl_val |= ((shअगरt/2) << ISPCTRL_SHIFT_SHIFT) & ISPCTRL_SHIFT_MASK;

	isp_reg_ग_लिखोl(isp, ispctrl_val, OMAP3_ISP_IOMEM_MAIN, ISP_CTRL);
पूर्ण

व्योम omap3isp_hist_dma_करोne(काष्ठा isp_device *isp)
अणु
	अगर (omap3isp_ccdc_busy(&isp->isp_ccdc) ||
	    omap3isp_stat_pcr_busy(&isp->isp_hist)) अणु
		/* Histogram cannot be enabled in this frame anymore */
		atomic_set(&isp->isp_hist.buf_err, 1);
		dev_dbg(isp->dev,
			"hist: Out of synchronization with CCDC. Ignoring next buffer.\n");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम isp_isr_dbg(काष्ठा isp_device *isp, u32 irqstatus)
अणु
	अटल स्थिर अक्षर *name[] = अणु
		"CSIA_IRQ",
		"res1",
		"res2",
		"CSIB_LCM_IRQ",
		"CSIB_IRQ",
		"res5",
		"res6",
		"res7",
		"CCDC_VD0_IRQ",
		"CCDC_VD1_IRQ",
		"CCDC_VD2_IRQ",
		"CCDC_ERR_IRQ",
		"H3A_AF_DONE_IRQ",
		"H3A_AWB_DONE_IRQ",
		"res14",
		"res15",
		"HIST_DONE_IRQ",
		"CCDC_LSC_DONE",
		"CCDC_LSC_PREFETCH_COMPLETED",
		"CCDC_LSC_PREFETCH_ERROR",
		"PRV_DONE_IRQ",
		"CBUFF_IRQ",
		"res22",
		"res23",
		"RSZ_DONE_IRQ",
		"OVF_IRQ",
		"res26",
		"res27",
		"MMU_ERR_IRQ",
		"OCP_ERR_IRQ",
		"SEC_ERR_IRQ",
		"HS_VS_IRQ",
	पूर्ण;
	पूर्णांक i;

	dev_dbg(isp->dev, "ISP IRQ: ");

	क्रम (i = 0; i < ARRAY_SIZE(name); i++) अणु
		अगर ((1 << i) & irqstatus)
			prपूर्णांकk(KERN_CONT "%s ", name[i]);
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल व्योम isp_isr_sbl(काष्ठा isp_device *isp)
अणु
	काष्ठा device *dev = isp->dev;
	काष्ठा isp_pipeline *pipe;
	u32 sbl_pcr;

	/*
	 * Handle shared buffer logic overflows क्रम video buffers.
	 * ISPSBL_PCR_CCDCPRV_2_RSZ_OVF can be safely ignored.
	 */
	sbl_pcr = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_PCR);
	isp_reg_ग_लिखोl(isp, sbl_pcr, OMAP3_ISP_IOMEM_SBL, ISPSBL_PCR);
	sbl_pcr &= ~ISPSBL_PCR_CCDCPRV_2_RSZ_OVF;

	अगर (sbl_pcr)
		dev_dbg(dev, "SBL overflow (PCR = 0x%08x)\n", sbl_pcr);

	अगर (sbl_pcr & ISPSBL_PCR_CSIB_WBL_OVF) अणु
		pipe = to_isp_pipeline(&isp->isp_ccp2.subdev.entity);
		अगर (pipe != शून्य)
			pipe->error = true;
	पूर्ण

	अगर (sbl_pcr & ISPSBL_PCR_CSIA_WBL_OVF) अणु
		pipe = to_isp_pipeline(&isp->isp_csi2a.subdev.entity);
		अगर (pipe != शून्य)
			pipe->error = true;
	पूर्ण

	अगर (sbl_pcr & ISPSBL_PCR_CCDC_WBL_OVF) अणु
		pipe = to_isp_pipeline(&isp->isp_ccdc.subdev.entity);
		अगर (pipe != शून्य)
			pipe->error = true;
	पूर्ण

	अगर (sbl_pcr & ISPSBL_PCR_PRV_WBL_OVF) अणु
		pipe = to_isp_pipeline(&isp->isp_prev.subdev.entity);
		अगर (pipe != शून्य)
			pipe->error = true;
	पूर्ण

	अगर (sbl_pcr & (ISPSBL_PCR_RSZ1_WBL_OVF
		       | ISPSBL_PCR_RSZ2_WBL_OVF
		       | ISPSBL_PCR_RSZ3_WBL_OVF
		       | ISPSBL_PCR_RSZ4_WBL_OVF)) अणु
		pipe = to_isp_pipeline(&isp->isp_res.subdev.entity);
		अगर (pipe != शून्य)
			pipe->error = true;
	पूर्ण

	अगर (sbl_pcr & ISPSBL_PCR_H3A_AF_WBL_OVF)
		omap3isp_stat_sbl_overflow(&isp->isp_af);

	अगर (sbl_pcr & ISPSBL_PCR_H3A_AEAWB_WBL_OVF)
		omap3isp_stat_sbl_overflow(&isp->isp_aewb);
पूर्ण

/*
 * isp_isr - Interrupt Service Routine क्रम Camera ISP module.
 * @irq: Not used currently.
 * @_isp: Poपूर्णांकer to the OMAP3 ISP device
 *
 * Handles the corresponding callback अगर plugged in.
 */
अटल irqवापस_t isp_isr(पूर्णांक irq, व्योम *_isp)
अणु
	अटल स्थिर u32 ccdc_events = IRQ0STATUS_CCDC_LSC_PREF_ERR_IRQ |
				       IRQ0STATUS_CCDC_LSC_DONE_IRQ |
				       IRQ0STATUS_CCDC_VD0_IRQ |
				       IRQ0STATUS_CCDC_VD1_IRQ |
				       IRQ0STATUS_HS_VS_IRQ;
	काष्ठा isp_device *isp = _isp;
	u32 irqstatus;

	irqstatus = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_MAIN, ISP_IRQ0STATUS);
	isp_reg_ग_लिखोl(isp, irqstatus, OMAP3_ISP_IOMEM_MAIN, ISP_IRQ0STATUS);

	isp_isr_sbl(isp);

	अगर (irqstatus & IRQ0STATUS_CSIA_IRQ)
		omap3isp_csi2_isr(&isp->isp_csi2a);

	अगर (irqstatus & IRQ0STATUS_CSIB_IRQ)
		omap3isp_ccp2_isr(&isp->isp_ccp2);

	अगर (irqstatus & IRQ0STATUS_CCDC_VD0_IRQ) अणु
		अगर (isp->isp_ccdc.output & CCDC_OUTPUT_PREVIEW)
			omap3isp_preview_isr_frame_sync(&isp->isp_prev);
		अगर (isp->isp_ccdc.output & CCDC_OUTPUT_RESIZER)
			omap3isp_resizer_isr_frame_sync(&isp->isp_res);
		omap3isp_stat_isr_frame_sync(&isp->isp_aewb);
		omap3isp_stat_isr_frame_sync(&isp->isp_af);
		omap3isp_stat_isr_frame_sync(&isp->isp_hist);
	पूर्ण

	अगर (irqstatus & ccdc_events)
		omap3isp_ccdc_isr(&isp->isp_ccdc, irqstatus & ccdc_events);

	अगर (irqstatus & IRQ0STATUS_PRV_DONE_IRQ) अणु
		अगर (isp->isp_prev.output & PREVIEW_OUTPUT_RESIZER)
			omap3isp_resizer_isr_frame_sync(&isp->isp_res);
		omap3isp_preview_isr(&isp->isp_prev);
	पूर्ण

	अगर (irqstatus & IRQ0STATUS_RSZ_DONE_IRQ)
		omap3isp_resizer_isr(&isp->isp_res);

	अगर (irqstatus & IRQ0STATUS_H3A_AWB_DONE_IRQ)
		omap3isp_stat_isr(&isp->isp_aewb);

	अगर (irqstatus & IRQ0STATUS_H3A_AF_DONE_IRQ)
		omap3isp_stat_isr(&isp->isp_af);

	अगर (irqstatus & IRQ0STATUS_HIST_DONE_IRQ)
		omap3isp_stat_isr(&isp->isp_hist);

	omap3isp_flush(isp);

#अगर defined(DEBUG) && defined(ISP_ISR_DEBUG)
	isp_isr_dbg(isp, irqstatus);
#पूर्ण_अगर

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा media_device_ops isp_media_ops = अणु
	.link_notअगरy = v4l2_pipeline_link_notअगरy,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Pipeline stream management
 */

/*
 * isp_pipeline_enable - Enable streaming on a pipeline
 * @pipe: ISP pipeline
 * @mode: Stream mode (single shot or continuous)
 *
 * Walk the entities chain starting at the pipeline output video node and start
 * all modules in the chain in the given mode.
 *
 * Return 0 अगर successful, or the वापस value of the failed video::s_stream
 * operation otherwise.
 */
अटल पूर्णांक isp_pipeline_enable(काष्ठा isp_pipeline *pipe,
			       क्रमागत isp_pipeline_stream_state mode)
अणु
	काष्ठा isp_device *isp = pipe->output->isp;
	काष्ठा media_entity *entity;
	काष्ठा media_pad *pad;
	काष्ठा v4l2_subdev *subdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Refuse to start streaming अगर an entity included in the pipeline has
	 * crashed. This check must be perक्रमmed beक्रमe the loop below to aव्योम
	 * starting entities अगर the pipeline won't start anyway (those entities
	 * would then likely fail to stop, making the problem worse).
	 */
	अगर (media_entity_क्रमागत_पूर्णांकersects(&pipe->ent_क्रमागत, &isp->crashed))
		वापस -EIO;

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~(ISP_PIPELINE_IDLE_INPUT | ISP_PIPELINE_IDLE_OUTPUT);
	spin_unlock_irqrestore(&pipe->lock, flags);

	pipe->करो_propagation = false;

	mutex_lock(&isp->media_dev.graph_mutex);

	entity = &pipe->output->video.entity;
	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		ret = v4l2_subdev_call(subdev, video, s_stream, mode);
		अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
			mutex_unlock(&isp->media_dev.graph_mutex);
			वापस ret;
		पूर्ण

		अगर (subdev == &isp->isp_ccdc.subdev) अणु
			v4l2_subdev_call(&isp->isp_aewb.subdev, video,
					s_stream, mode);
			v4l2_subdev_call(&isp->isp_af.subdev, video,
					s_stream, mode);
			v4l2_subdev_call(&isp->isp_hist.subdev, video,
					s_stream, mode);
			pipe->करो_propagation = true;
		पूर्ण

		/* Stop at the first बाह्यal sub-device. */
		अगर (subdev->dev != isp->dev)
			अवरोध;
	पूर्ण

	mutex_unlock(&isp->media_dev.graph_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक isp_pipeline_रुको_resizer(काष्ठा isp_device *isp)
अणु
	वापस omap3isp_resizer_busy(&isp->isp_res);
पूर्ण

अटल पूर्णांक isp_pipeline_रुको_preview(काष्ठा isp_device *isp)
अणु
	वापस omap3isp_preview_busy(&isp->isp_prev);
पूर्ण

अटल पूर्णांक isp_pipeline_रुको_ccdc(काष्ठा isp_device *isp)
अणु
	वापस omap3isp_stat_busy(&isp->isp_af)
	    || omap3isp_stat_busy(&isp->isp_aewb)
	    || omap3isp_stat_busy(&isp->isp_hist)
	    || omap3isp_ccdc_busy(&isp->isp_ccdc);
पूर्ण

#घोषणा ISP_STOP_TIMEOUT	msecs_to_jअगरfies(1000)

अटल पूर्णांक isp_pipeline_रुको(काष्ठा isp_device *isp,
			     पूर्णांक(*busy)(काष्ठा isp_device *isp))
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + ISP_STOP_TIMEOUT;

	जबतक (!समय_after(jअगरfies, समयout)) अणु
		अगर (!busy(isp))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * isp_pipeline_disable - Disable streaming on a pipeline
 * @pipe: ISP pipeline
 *
 * Walk the entities chain starting at the pipeline output video node and stop
 * all modules in the chain. Wait synchronously क्रम the modules to be stopped अगर
 * necessary.
 *
 * Return 0 अगर all modules have been properly stopped, or -ETIMEDOUT अगर a module
 * can't be stopped (in which हाल a software reset of the ISP is probably
 * necessary).
 */
अटल पूर्णांक isp_pipeline_disable(काष्ठा isp_pipeline *pipe)
अणु
	काष्ठा isp_device *isp = pipe->output->isp;
	काष्ठा media_entity *entity;
	काष्ठा media_pad *pad;
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक failure = 0;
	पूर्णांक ret;

	/*
	 * We need to stop all the modules after CCDC first or they'll
	 * never stop since they may not get a full frame from CCDC.
	 */
	entity = &pipe->output->video.entity;
	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		अगर (subdev == &isp->isp_ccdc.subdev) अणु
			v4l2_subdev_call(&isp->isp_aewb.subdev,
					 video, s_stream, 0);
			v4l2_subdev_call(&isp->isp_af.subdev,
					 video, s_stream, 0);
			v4l2_subdev_call(&isp->isp_hist.subdev,
					 video, s_stream, 0);
		पूर्ण

		ret = v4l2_subdev_call(subdev, video, s_stream, 0);

		/* Stop at the first बाह्यal sub-device. */
		अगर (subdev->dev != isp->dev)
			अवरोध;

		अगर (subdev == &isp->isp_res.subdev)
			ret |= isp_pipeline_रुको(isp, isp_pipeline_रुको_resizer);
		अन्यथा अगर (subdev == &isp->isp_prev.subdev)
			ret |= isp_pipeline_रुको(isp, isp_pipeline_रुको_preview);
		अन्यथा अगर (subdev == &isp->isp_ccdc.subdev)
			ret |= isp_pipeline_रुको(isp, isp_pipeline_रुको_ccdc);

		/* Handle stop failures. An entity that fails to stop can
		 * usually just be restarted. Flag the stop failure nonetheless
		 * to trigger an ISP reset the next समय the device is released,
		 * just in हाल.
		 *
		 * The preview engine is a special हाल. A failure to stop can
		 * mean a hardware crash. When that happens the preview engine
		 * won't respond to पढ़ो/ग_लिखो operations on the L4 bus anymore,
		 * resulting in a bus fault and a kernel oops next समय it माला_लो
		 * accessed. Mark it as crashed to prevent pipelines including
		 * it from being started.
		 */
		अगर (ret) अणु
			dev_info(isp->dev, "Unable to stop %s\n", subdev->name);
			isp->stop_failure = true;
			अगर (subdev == &isp->isp_prev.subdev)
				media_entity_क्रमागत_set(&isp->crashed,
						      &subdev->entity);
			failure = -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस failure;
पूर्ण

/*
 * omap3isp_pipeline_set_stream - Enable/disable streaming on a pipeline
 * @pipe: ISP pipeline
 * @state: Stream state (stopped, single shot or continuous)
 *
 * Set the pipeline to the given stream state. Pipelines can be started in
 * single-shot or continuous mode.
 *
 * Return 0 अगर successful, or the वापस value of the failed video::s_stream
 * operation otherwise. The pipeline state is not updated when the operation
 * fails, except when stopping the pipeline.
 */
पूर्णांक omap3isp_pipeline_set_stream(काष्ठा isp_pipeline *pipe,
				 क्रमागत isp_pipeline_stream_state state)
अणु
	पूर्णांक ret;

	अगर (state == ISP_PIPELINE_STREAM_STOPPED)
		ret = isp_pipeline_disable(pipe);
	अन्यथा
		ret = isp_pipeline_enable(pipe, state);

	अगर (ret == 0 || state == ISP_PIPELINE_STREAM_STOPPED)
		pipe->stream_state = state;

	वापस ret;
पूर्ण

/*
 * omap3isp_pipeline_cancel_stream - Cancel stream on a pipeline
 * @pipe: ISP pipeline
 *
 * Cancelling a stream mark all buffers on all video nodes in the pipeline as
 * erroneous and makes sure no new buffer can be queued. This function is called
 * when a fatal error that prevents any further operation on the pipeline
 * occurs.
 */
व्योम omap3isp_pipeline_cancel_stream(काष्ठा isp_pipeline *pipe)
अणु
	अगर (pipe->input)
		omap3isp_video_cancel_stream(pipe->input);
	अगर (pipe->output)
		omap3isp_video_cancel_stream(pipe->output);
पूर्ण

/*
 * isp_pipeline_resume - Resume streaming on a pipeline
 * @pipe: ISP pipeline
 *
 * Resume video output and input and re-enable pipeline.
 */
अटल व्योम isp_pipeline_resume(काष्ठा isp_pipeline *pipe)
अणु
	पूर्णांक singleshot = pipe->stream_state == ISP_PIPELINE_STREAM_SINGLESHOT;

	omap3isp_video_resume(pipe->output, !singleshot);
	अगर (singleshot)
		omap3isp_video_resume(pipe->input, 0);
	isp_pipeline_enable(pipe, pipe->stream_state);
पूर्ण

/*
 * isp_pipeline_suspend - Suspend streaming on a pipeline
 * @pipe: ISP pipeline
 *
 * Suspend pipeline.
 */
अटल व्योम isp_pipeline_suspend(काष्ठा isp_pipeline *pipe)
अणु
	isp_pipeline_disable(pipe);
पूर्ण

/*
 * isp_pipeline_is_last - Verअगरy अगर entity has an enabled link to the output
 *			  video node
 * @me: ISP module's media entity
 *
 * Returns 1 अगर the entity has an enabled link to the output video node or 0
 * otherwise. It's true only जबतक pipeline can have no more than one output
 * node.
 */
अटल पूर्णांक isp_pipeline_is_last(काष्ठा media_entity *me)
अणु
	काष्ठा isp_pipeline *pipe;
	काष्ठा media_pad *pad;

	अगर (!me->pipe)
		वापस 0;
	pipe = to_isp_pipeline(me);
	अगर (pipe->stream_state == ISP_PIPELINE_STREAM_STOPPED)
		वापस 0;
	pad = media_entity_remote_pad(&pipe->output->pad);
	वापस pad->entity == me;
पूर्ण

/*
 * isp_suspend_module_pipeline - Suspend pipeline to which beदीर्घs the module
 * @me: ISP module's media entity
 *
 * Suspend the whole pipeline अगर module's entity has an enabled link to the
 * output video node. It works only जबतक pipeline can have no more than one
 * output node.
 */
अटल व्योम isp_suspend_module_pipeline(काष्ठा media_entity *me)
अणु
	अगर (isp_pipeline_is_last(me))
		isp_pipeline_suspend(to_isp_pipeline(me));
पूर्ण

/*
 * isp_resume_module_pipeline - Resume pipeline to which beदीर्घs the module
 * @me: ISP module's media entity
 *
 * Resume the whole pipeline अगर module's entity has an enabled link to the
 * output video node. It works only जबतक pipeline can have no more than one
 * output node.
 */
अटल व्योम isp_resume_module_pipeline(काष्ठा media_entity *me)
अणु
	अगर (isp_pipeline_is_last(me))
		isp_pipeline_resume(to_isp_pipeline(me));
पूर्ण

/*
 * isp_suspend_modules - Suspend ISP submodules.
 * @isp: OMAP3 ISP device
 *
 * Returns 0 अगर suspend left in idle state all the submodules properly,
 * or वापसs 1 अगर a general Reset is required to suspend the submodules.
 */
अटल पूर्णांक __maybe_unused isp_suspend_modules(काष्ठा isp_device *isp)
अणु
	अचिन्हित दीर्घ समयout;

	omap3isp_stat_suspend(&isp->isp_aewb);
	omap3isp_stat_suspend(&isp->isp_af);
	omap3isp_stat_suspend(&isp->isp_hist);
	isp_suspend_module_pipeline(&isp->isp_res.subdev.entity);
	isp_suspend_module_pipeline(&isp->isp_prev.subdev.entity);
	isp_suspend_module_pipeline(&isp->isp_ccdc.subdev.entity);
	isp_suspend_module_pipeline(&isp->isp_csi2a.subdev.entity);
	isp_suspend_module_pipeline(&isp->isp_ccp2.subdev.entity);

	समयout = jअगरfies + ISP_STOP_TIMEOUT;
	जबतक (omap3isp_stat_busy(&isp->isp_af)
	    || omap3isp_stat_busy(&isp->isp_aewb)
	    || omap3isp_stat_busy(&isp->isp_hist)
	    || omap3isp_preview_busy(&isp->isp_prev)
	    || omap3isp_resizer_busy(&isp->isp_res)
	    || omap3isp_ccdc_busy(&isp->isp_ccdc)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_info(isp->dev, "can't stop modules.\n");
			वापस 1;
		पूर्ण
		msleep(1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * isp_resume_modules - Resume ISP submodules.
 * @isp: OMAP3 ISP device
 */
अटल व्योम __maybe_unused isp_resume_modules(काष्ठा isp_device *isp)
अणु
	omap3isp_stat_resume(&isp->isp_aewb);
	omap3isp_stat_resume(&isp->isp_af);
	omap3isp_stat_resume(&isp->isp_hist);
	isp_resume_module_pipeline(&isp->isp_res.subdev.entity);
	isp_resume_module_pipeline(&isp->isp_prev.subdev.entity);
	isp_resume_module_pipeline(&isp->isp_ccdc.subdev.entity);
	isp_resume_module_pipeline(&isp->isp_csi2a.subdev.entity);
	isp_resume_module_pipeline(&isp->isp_ccp2.subdev.entity);
पूर्ण

/*
 * isp_reset - Reset ISP with a समयout रुको क्रम idle.
 * @isp: OMAP3 ISP device
 */
अटल पूर्णांक isp_reset(काष्ठा isp_device *isp)
अणु
	अचिन्हित दीर्घ समयout = 0;

	isp_reg_ग_लिखोl(isp,
		       isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_MAIN, ISP_SYSCONFIG)
		       | ISP_SYSCONFIG_SOFTRESET,
		       OMAP3_ISP_IOMEM_MAIN, ISP_SYSCONFIG);
	जबतक (!(isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_MAIN,
			       ISP_SYSSTATUS) & 0x1)) अणु
		अगर (समयout++ > 10000) अणु
			dev_alert(isp->dev, "cannot reset ISP\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(1);
	पूर्ण

	isp->stop_failure = false;
	media_entity_क्रमागत_zero(&isp->crashed);
	वापस 0;
पूर्ण

/*
 * isp_save_context - Saves the values of the ISP module रेजिस्टरs.
 * @isp: OMAP3 ISP device
 * @reg_list: Structure containing pairs of रेजिस्टर address and value to
 *            modअगरy on OMAP.
 */
अटल व्योम
isp_save_context(काष्ठा isp_device *isp, काष्ठा isp_reg *reg_list)
अणु
	काष्ठा isp_reg *next = reg_list;

	क्रम (; next->reg != ISP_TOK_TERM; next++)
		next->val = isp_reg_पढ़ोl(isp, next->mmio_range, next->reg);
पूर्ण

/*
 * isp_restore_context - Restores the values of the ISP module रेजिस्टरs.
 * @isp: OMAP3 ISP device
 * @reg_list: Structure containing pairs of रेजिस्टर address and value to
 *            modअगरy on OMAP.
 */
अटल व्योम
isp_restore_context(काष्ठा isp_device *isp, काष्ठा isp_reg *reg_list)
अणु
	काष्ठा isp_reg *next = reg_list;

	क्रम (; next->reg != ISP_TOK_TERM; next++)
		isp_reg_ग_लिखोl(isp, next->val, next->mmio_range, next->reg);
पूर्ण

/*
 * isp_save_ctx - Saves ISP, CCDC, HIST, H3A, PREV, RESZ & MMU context.
 * @isp: OMAP3 ISP device
 *
 * Routine क्रम saving the context of each module in the ISP.
 * CCDC, HIST, H3A, PREV, RESZ and MMU.
 */
अटल व्योम isp_save_ctx(काष्ठा isp_device *isp)
अणु
	isp_save_context(isp, isp_reg_list);
	omap_iommu_save_ctx(isp->dev);
पूर्ण

/*
 * isp_restore_ctx - Restores ISP, CCDC, HIST, H3A, PREV, RESZ & MMU context.
 * @isp: OMAP3 ISP device
 *
 * Routine क्रम restoring the context of each module in the ISP.
 * CCDC, HIST, H3A, PREV, RESZ and MMU.
 */
अटल व्योम isp_restore_ctx(काष्ठा isp_device *isp)
अणु
	isp_restore_context(isp, isp_reg_list);
	omap_iommu_restore_ctx(isp->dev);
	omap3isp_ccdc_restore_context(isp);
	omap3isp_preview_restore_context(isp);
पूर्ण

/* -----------------------------------------------------------------------------
 * SBL resources management
 */
#घोषणा OMAP3_ISP_SBL_READ	(OMAP3_ISP_SBL_CSI1_READ | \
				 OMAP3_ISP_SBL_CCDC_LSC_READ | \
				 OMAP3_ISP_SBL_PREVIEW_READ | \
				 OMAP3_ISP_SBL_RESIZER_READ)
#घोषणा OMAP3_ISP_SBL_WRITE	(OMAP3_ISP_SBL_CSI1_WRITE | \
				 OMAP3_ISP_SBL_CSI2A_WRITE | \
				 OMAP3_ISP_SBL_CSI2C_WRITE | \
				 OMAP3_ISP_SBL_CCDC_WRITE | \
				 OMAP3_ISP_SBL_PREVIEW_WRITE)

व्योम omap3isp_sbl_enable(काष्ठा isp_device *isp, क्रमागत isp_sbl_resource res)
अणु
	u32 sbl = 0;

	isp->sbl_resources |= res;

	अगर (isp->sbl_resources & OMAP3_ISP_SBL_CSI1_READ)
		sbl |= ISPCTRL_SBL_SHARED_RPORTA;

	अगर (isp->sbl_resources & OMAP3_ISP_SBL_CCDC_LSC_READ)
		sbl |= ISPCTRL_SBL_SHARED_RPORTB;

	अगर (isp->sbl_resources & OMAP3_ISP_SBL_CSI2C_WRITE)
		sbl |= ISPCTRL_SBL_SHARED_WPORTC;

	अगर (isp->sbl_resources & OMAP3_ISP_SBL_RESIZER_WRITE)
		sbl |= ISPCTRL_SBL_WR0_RAM_EN;

	अगर (isp->sbl_resources & OMAP3_ISP_SBL_WRITE)
		sbl |= ISPCTRL_SBL_WR1_RAM_EN;

	अगर (isp->sbl_resources & OMAP3_ISP_SBL_READ)
		sbl |= ISPCTRL_SBL_RD_RAM_EN;

	isp_reg_set(isp, OMAP3_ISP_IOMEM_MAIN, ISP_CTRL, sbl);
पूर्ण

व्योम omap3isp_sbl_disable(काष्ठा isp_device *isp, क्रमागत isp_sbl_resource res)
अणु
	u32 sbl = 0;

	isp->sbl_resources &= ~res;

	अगर (!(isp->sbl_resources & OMAP3_ISP_SBL_CSI1_READ))
		sbl |= ISPCTRL_SBL_SHARED_RPORTA;

	अगर (!(isp->sbl_resources & OMAP3_ISP_SBL_CCDC_LSC_READ))
		sbl |= ISPCTRL_SBL_SHARED_RPORTB;

	अगर (!(isp->sbl_resources & OMAP3_ISP_SBL_CSI2C_WRITE))
		sbl |= ISPCTRL_SBL_SHARED_WPORTC;

	अगर (!(isp->sbl_resources & OMAP3_ISP_SBL_RESIZER_WRITE))
		sbl |= ISPCTRL_SBL_WR0_RAM_EN;

	अगर (!(isp->sbl_resources & OMAP3_ISP_SBL_WRITE))
		sbl |= ISPCTRL_SBL_WR1_RAM_EN;

	अगर (!(isp->sbl_resources & OMAP3_ISP_SBL_READ))
		sbl |= ISPCTRL_SBL_RD_RAM_EN;

	isp_reg_clr(isp, OMAP3_ISP_IOMEM_MAIN, ISP_CTRL, sbl);
पूर्ण

/*
 * isp_module_sync_idle - Helper to sync module with its idle state
 * @me: ISP submodule's media entity
 * @रुको: ISP submodule's रुको queue क्रम streamoff/पूर्णांकerrupt synchronization
 * @stopping: flag which tells module wants to stop
 *
 * This function checks अगर ISP submodule needs to रुको क्रम next पूर्णांकerrupt. If
 * yes, makes the caller to sleep जबतक रुकोing क्रम such event.
 */
पूर्णांक omap3isp_module_sync_idle(काष्ठा media_entity *me, रुको_queue_head_t *रुको,
			      atomic_t *stopping)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(me);

	अगर (pipe->stream_state == ISP_PIPELINE_STREAM_STOPPED ||
	    (pipe->stream_state == ISP_PIPELINE_STREAM_SINGLESHOT &&
	     !isp_pipeline_पढ़ोy(pipe)))
		वापस 0;

	/*
	 * atomic_set() करोesn't include memory barrier on ARM platक्रमm क्रम SMP
	 * scenario. We'll call it here to aव्योम race conditions.
	 */
	atomic_set(stopping, 1);
	smp_mb();

	/*
	 * If module is the last one, it's writing to memory. In this हाल,
	 * it's necessary to check अगर the module is alपढ़ोy छोड़ोd due to
	 * DMA queue underrun or अगर it has to रुको क्रम next पूर्णांकerrupt to be
	 * idle.
	 * If it isn't the last one, the function won't sleep but *stopping
	 * will still be set to warn next submodule caller's पूर्णांकerrupt the
	 * module wants to be idle.
	 */
	अगर (isp_pipeline_is_last(me)) अणु
		काष्ठा isp_video *video = pipe->output;
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&video->irqlock, flags);
		अगर (video->dmaqueue_flags & ISP_VIDEO_DMAQUEUE_UNDERRUN) अणु
			spin_unlock_irqrestore(&video->irqlock, flags);
			atomic_set(stopping, 0);
			smp_mb();
			वापस 0;
		पूर्ण
		spin_unlock_irqrestore(&video->irqlock, flags);
		अगर (!रुको_event_समयout(*रुको, !atomic_पढ़ो(stopping),
					msecs_to_jअगरfies(1000))) अणु
			atomic_set(stopping, 0);
			smp_mb();
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * omap3isp_module_sync_is_stopping - Helper to verअगरy अगर module was stopping
 * @रुको: ISP submodule's रुको queue क्रम streamoff/पूर्णांकerrupt synchronization
 * @stopping: flag which tells module wants to stop
 *
 * This function checks अगर ISP submodule was stopping. In हाल of yes, it
 * notices the caller by setting stopping to 0 and waking up the रुको queue.
 * Returns 1 अगर it was stopping or 0 otherwise.
 */
पूर्णांक omap3isp_module_sync_is_stopping(रुको_queue_head_t *रुको,
				     atomic_t *stopping)
अणु
	अगर (atomic_cmpxchg(stopping, 1, 0)) अणु
		wake_up(रुको);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
 * Clock management
 */

#घोषणा ISPCTRL_CLKS_MASK	(ISPCTRL_H3A_CLK_EN | \
				 ISPCTRL_HIST_CLK_EN | \
				 ISPCTRL_RSZ_CLK_EN | \
				 (ISPCTRL_CCDC_CLK_EN | ISPCTRL_CCDC_RAM_EN) | \
				 (ISPCTRL_PREV_CLK_EN | ISPCTRL_PREV_RAM_EN))

अटल व्योम __isp_subclk_update(काष्ठा isp_device *isp)
अणु
	u32 clk = 0;

	/* AEWB and AF share the same घड़ी. */
	अगर (isp->subclk_resources &
	    (OMAP3_ISP_SUBCLK_AEWB | OMAP3_ISP_SUBCLK_AF))
		clk |= ISPCTRL_H3A_CLK_EN;

	अगर (isp->subclk_resources & OMAP3_ISP_SUBCLK_HIST)
		clk |= ISPCTRL_HIST_CLK_EN;

	अगर (isp->subclk_resources & OMAP3_ISP_SUBCLK_RESIZER)
		clk |= ISPCTRL_RSZ_CLK_EN;

	/* NOTE: For CCDC & Preview submodules, we need to affect पूर्णांकernal
	 *       RAM as well.
	 */
	अगर (isp->subclk_resources & OMAP3_ISP_SUBCLK_CCDC)
		clk |= ISPCTRL_CCDC_CLK_EN | ISPCTRL_CCDC_RAM_EN;

	अगर (isp->subclk_resources & OMAP3_ISP_SUBCLK_PREVIEW)
		clk |= ISPCTRL_PREV_CLK_EN | ISPCTRL_PREV_RAM_EN;

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_MAIN, ISP_CTRL,
			ISPCTRL_CLKS_MASK, clk);
पूर्ण

व्योम omap3isp_subclk_enable(काष्ठा isp_device *isp,
			    क्रमागत isp_subclk_resource res)
अणु
	isp->subclk_resources |= res;

	__isp_subclk_update(isp);
पूर्ण

व्योम omap3isp_subclk_disable(काष्ठा isp_device *isp,
			     क्रमागत isp_subclk_resource res)
अणु
	isp->subclk_resources &= ~res;

	__isp_subclk_update(isp);
पूर्ण

/*
 * isp_enable_घड़ीs - Enable ISP घड़ीs
 * @isp: OMAP3 ISP device
 *
 * Return 0 अगर successful, or clk_prepare_enable वापस value अगर any of them
 * fails.
 */
अटल पूर्णांक isp_enable_घड़ीs(काष्ठा isp_device *isp)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ rate;

	r = clk_prepare_enable(isp->घड़ी[ISP_CLK_CAM_ICK]);
	अगर (r) अणु
		dev_err(isp->dev, "failed to enable cam_ick clock\n");
		जाओ out_clk_enable_ick;
	पूर्ण
	r = clk_set_rate(isp->घड़ी[ISP_CLK_CAM_MCLK], CM_CAM_MCLK_HZ);
	अगर (r) अणु
		dev_err(isp->dev, "clk_set_rate for cam_mclk failed\n");
		जाओ out_clk_enable_mclk;
	पूर्ण
	r = clk_prepare_enable(isp->घड़ी[ISP_CLK_CAM_MCLK]);
	अगर (r) अणु
		dev_err(isp->dev, "failed to enable cam_mclk clock\n");
		जाओ out_clk_enable_mclk;
	पूर्ण
	rate = clk_get_rate(isp->घड़ी[ISP_CLK_CAM_MCLK]);
	अगर (rate != CM_CAM_MCLK_HZ)
		dev_warn(isp->dev, "unexpected cam_mclk rate:\n"
				   " expected : %d\n"
				   " actual   : %ld\n", CM_CAM_MCLK_HZ, rate);
	r = clk_prepare_enable(isp->घड़ी[ISP_CLK_CSI2_FCK]);
	अगर (r) अणु
		dev_err(isp->dev, "failed to enable csi2_fck clock\n");
		जाओ out_clk_enable_csi2_fclk;
	पूर्ण
	वापस 0;

out_clk_enable_csi2_fclk:
	clk_disable_unprepare(isp->घड़ी[ISP_CLK_CAM_MCLK]);
out_clk_enable_mclk:
	clk_disable_unprepare(isp->घड़ी[ISP_CLK_CAM_ICK]);
out_clk_enable_ick:
	वापस r;
पूर्ण

/*
 * isp_disable_घड़ीs - Disable ISP घड़ीs
 * @isp: OMAP3 ISP device
 */
अटल व्योम isp_disable_घड़ीs(काष्ठा isp_device *isp)
अणु
	clk_disable_unprepare(isp->घड़ी[ISP_CLK_CAM_ICK]);
	clk_disable_unprepare(isp->घड़ी[ISP_CLK_CAM_MCLK]);
	clk_disable_unprepare(isp->घड़ी[ISP_CLK_CSI2_FCK]);
पूर्ण

अटल स्थिर अक्षर *isp_घड़ीs[] = अणु
	"cam_ick",
	"cam_mclk",
	"csi2_96m_fck",
	"l3_ick",
पूर्ण;

अटल पूर्णांक isp_get_घड़ीs(काष्ठा isp_device *isp)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(isp_घड़ीs); ++i) अणु
		clk = devm_clk_get(isp->dev, isp_घड़ीs[i]);
		अगर (IS_ERR(clk)) अणु
			dev_err(isp->dev, "clk_get %s failed\n", isp_घड़ीs[i]);
			वापस PTR_ERR(clk);
		पूर्ण

		isp->घड़ी[i] = clk;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * omap3isp_get - Acquire the ISP resource.
 *
 * Initializes the घड़ीs क्रम the first acquire.
 *
 * Increment the reference count on the ISP. If the first reference is taken,
 * enable घड़ीs and घातer-up all submodules.
 *
 * Return a poपूर्णांकer to the ISP device काष्ठाure, or शून्य अगर an error occurred.
 */
अटल काष्ठा isp_device *__omap3isp_get(काष्ठा isp_device *isp, bool irq)
अणु
	काष्ठा isp_device *__isp = isp;

	अगर (isp == शून्य)
		वापस शून्य;

	mutex_lock(&isp->isp_mutex);
	अगर (isp->ref_count > 0)
		जाओ out;

	अगर (isp_enable_घड़ीs(isp) < 0) अणु
		__isp = शून्य;
		जाओ out;
	पूर्ण

	/* We करोn't want to restore context beक्रमe saving it! */
	अगर (isp->has_context)
		isp_restore_ctx(isp);

	अगर (irq)
		isp_enable_पूर्णांकerrupts(isp);

out:
	अगर (__isp != शून्य)
		isp->ref_count++;
	mutex_unlock(&isp->isp_mutex);

	वापस __isp;
पूर्ण

काष्ठा isp_device *omap3isp_get(काष्ठा isp_device *isp)
अणु
	वापस __omap3isp_get(isp, true);
पूर्ण

/*
 * omap3isp_put - Release the ISP
 *
 * Decrement the reference count on the ISP. If the last reference is released,
 * घातer-करोwn all submodules, disable घड़ीs and मुक्त temporary buffers.
 */
अटल व्योम __omap3isp_put(काष्ठा isp_device *isp, bool save_ctx)
अणु
	अगर (isp == शून्य)
		वापस;

	mutex_lock(&isp->isp_mutex);
	BUG_ON(isp->ref_count == 0);
	अगर (--isp->ref_count == 0) अणु
		isp_disable_पूर्णांकerrupts(isp);
		अगर (save_ctx) अणु
			isp_save_ctx(isp);
			isp->has_context = 1;
		पूर्ण
		/* Reset the ISP अगर an entity has failed to stop. This is the
		 * only way to recover from such conditions.
		 */
		अगर (!media_entity_क्रमागत_empty(&isp->crashed) ||
		    isp->stop_failure)
			isp_reset(isp);
		isp_disable_घड़ीs(isp);
	पूर्ण
	mutex_unlock(&isp->isp_mutex);
पूर्ण

व्योम omap3isp_put(काष्ठा isp_device *isp)
अणु
	__omap3isp_put(isp, true);
पूर्ण

/* --------------------------------------------------------------------------
 * Platक्रमm device driver
 */

/*
 * omap3isp_prपूर्णांक_status - Prपूर्णांकs the values of the ISP Control Module रेजिस्टरs
 * @isp: OMAP3 ISP device
 */
#घोषणा ISP_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev, "###ISP " #name "=0x%08x\n", \
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_MAIN, ISP_##name))
#घोषणा SBL_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev, "###SBL " #name "=0x%08x\n", \
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_##name))

व्योम omap3isp_prपूर्णांक_status(काष्ठा isp_device *isp)
अणु
	dev_dbg(isp->dev, "-------------ISP Register dump--------------\n");

	ISP_PRINT_REGISTER(isp, SYSCONFIG);
	ISP_PRINT_REGISTER(isp, SYSSTATUS);
	ISP_PRINT_REGISTER(isp, IRQ0ENABLE);
	ISP_PRINT_REGISTER(isp, IRQ0STATUS);
	ISP_PRINT_REGISTER(isp, TCTRL_GRESET_LENGTH);
	ISP_PRINT_REGISTER(isp, TCTRL_PSTRB_REPLAY);
	ISP_PRINT_REGISTER(isp, CTRL);
	ISP_PRINT_REGISTER(isp, TCTRL_CTRL);
	ISP_PRINT_REGISTER(isp, TCTRL_FRAME);
	ISP_PRINT_REGISTER(isp, TCTRL_PSTRB_DELAY);
	ISP_PRINT_REGISTER(isp, TCTRL_STRB_DELAY);
	ISP_PRINT_REGISTER(isp, TCTRL_SHUT_DELAY);
	ISP_PRINT_REGISTER(isp, TCTRL_PSTRB_LENGTH);
	ISP_PRINT_REGISTER(isp, TCTRL_STRB_LENGTH);
	ISP_PRINT_REGISTER(isp, TCTRL_SHUT_LENGTH);

	SBL_PRINT_REGISTER(isp, PCR);
	SBL_PRINT_REGISTER(isp, SDR_REQ_EXP);

	dev_dbg(isp->dev, "--------------------------------------------\n");
पूर्ण

#अगर_घोषित CONFIG_PM

/*
 * Power management support.
 *
 * As the ISP can't properly handle an input video stream पूर्णांकerruption on a non
 * frame boundary, the ISP pipelines need to be stopped beक्रमe sensors get
 * suspended. However, as suspending the sensors can require a running घड़ी,
 * which can be provided by the ISP, the ISP can't be completely suspended
 * beक्रमe the sensor.
 *
 * To solve this problem घातer management support is split पूर्णांकo prepare/complete
 * and suspend/resume operations. The pipelines are stopped in prepare() and the
 * ISP घड़ीs get disabled in suspend(). Similarly, the घड़ीs are re-enabled in
 * resume(), and the the pipelines are restarted in complete().
 *
 * TODO: PM dependencies between the ISP and sensors are not modelled explicitly
 * yet.
 */
अटल पूर्णांक isp_pm_prepare(काष्ठा device *dev)
अणु
	काष्ठा isp_device *isp = dev_get_drvdata(dev);
	पूर्णांक reset;

	WARN_ON(mutex_is_locked(&isp->isp_mutex));

	अगर (isp->ref_count == 0)
		वापस 0;

	reset = isp_suspend_modules(isp);
	isp_disable_पूर्णांकerrupts(isp);
	isp_save_ctx(isp);
	अगर (reset)
		isp_reset(isp);

	वापस 0;
पूर्ण

अटल पूर्णांक isp_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा isp_device *isp = dev_get_drvdata(dev);

	WARN_ON(mutex_is_locked(&isp->isp_mutex));

	अगर (isp->ref_count)
		isp_disable_घड़ीs(isp);

	वापस 0;
पूर्ण

अटल पूर्णांक isp_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा isp_device *isp = dev_get_drvdata(dev);

	अगर (isp->ref_count == 0)
		वापस 0;

	वापस isp_enable_घड़ीs(isp);
पूर्ण

अटल व्योम isp_pm_complete(काष्ठा device *dev)
अणु
	काष्ठा isp_device *isp = dev_get_drvdata(dev);

	अगर (isp->ref_count == 0)
		वापस;

	isp_restore_ctx(isp);
	isp_enable_पूर्णांकerrupts(isp);
	isp_resume_modules(isp);
पूर्ण

#अन्यथा

#घोषणा isp_pm_prepare	शून्य
#घोषणा isp_pm_suspend	शून्य
#घोषणा isp_pm_resume	शून्य
#घोषणा isp_pm_complete	शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम isp_unरेजिस्टर_entities(काष्ठा isp_device *isp)
अणु
	media_device_unरेजिस्टर(&isp->media_dev);

	omap3isp_csi2_unरेजिस्टर_entities(&isp->isp_csi2a);
	omap3isp_ccp2_unरेजिस्टर_entities(&isp->isp_ccp2);
	omap3isp_ccdc_unरेजिस्टर_entities(&isp->isp_ccdc);
	omap3isp_preview_unरेजिस्टर_entities(&isp->isp_prev);
	omap3isp_resizer_unरेजिस्टर_entities(&isp->isp_res);
	omap3isp_stat_unरेजिस्टर_entities(&isp->isp_aewb);
	omap3isp_stat_unरेजिस्टर_entities(&isp->isp_af);
	omap3isp_stat_unरेजिस्टर_entities(&isp->isp_hist);

	v4l2_device_unरेजिस्टर(&isp->v4l2_dev);
	media_device_cleanup(&isp->media_dev);
पूर्ण

अटल पूर्णांक isp_link_entity(
	काष्ठा isp_device *isp, काष्ठा media_entity *entity,
	क्रमागत isp_पूर्णांकerface_type पूर्णांकerface)
अणु
	काष्ठा media_entity *input;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक pad;
	अचिन्हित पूर्णांक i;

	/* Connect the sensor to the correct पूर्णांकerface module.
	 * Parallel sensors are connected directly to the CCDC, जबतक
	 * serial sensors are connected to the CSI2a, CCP2b or CSI2c
	 * receiver through CSIPHY1 or CSIPHY2.
	 */
	चयन (पूर्णांकerface) अणु
	हाल ISP_INTERFACE_PARALLEL:
		input = &isp->isp_ccdc.subdev.entity;
		pad = CCDC_PAD_SINK;
		flags = 0;
		अवरोध;

	हाल ISP_INTERFACE_CSI2A_PHY2:
		input = &isp->isp_csi2a.subdev.entity;
		pad = CSI2_PAD_SINK;
		flags = MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED;
		अवरोध;

	हाल ISP_INTERFACE_CCP2B_PHY1:
	हाल ISP_INTERFACE_CCP2B_PHY2:
		input = &isp->isp_ccp2.subdev.entity;
		pad = CCP2_PAD_SINK;
		flags = 0;
		अवरोध;

	हाल ISP_INTERFACE_CSI2C_PHY1:
		input = &isp->isp_csi2c.subdev.entity;
		pad = CSI2_PAD_SINK;
		flags = MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED;
		अवरोध;

	शेष:
		dev_err(isp->dev, "%s: invalid interface type %u\n", __func__,
			पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Not all पूर्णांकerfaces are available on all revisions of the
	 * ISP. The sub-devices of those पूर्णांकerfaces aren't initialised
	 * in such a हाल. Check this by ensuring the num_pads is
	 * non-zero.
	 */
	अगर (!input->num_pads) अणु
		dev_err(isp->dev, "%s: invalid input %u\n", entity->name,
			पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < entity->num_pads; i++) अणु
		अगर (entity->pads[i].flags & MEDIA_PAD_FL_SOURCE)
			अवरोध;
	पूर्ण
	अगर (i == entity->num_pads) अणु
		dev_err(isp->dev, "%s: no source pad in external entity %s\n",
			__func__, entity->name);
		वापस -EINVAL;
	पूर्ण

	वापस media_create_pad_link(entity, i, input, pad, flags);
पूर्ण

अटल पूर्णांक isp_रेजिस्टर_entities(काष्ठा isp_device *isp)
अणु
	पूर्णांक ret;

	isp->media_dev.dev = isp->dev;
	strscpy(isp->media_dev.model, "TI OMAP3 ISP",
		माप(isp->media_dev.model));
	isp->media_dev.hw_revision = isp->revision;
	isp->media_dev.ops = &isp_media_ops;
	media_device_init(&isp->media_dev);

	isp->v4l2_dev.mdev = &isp->media_dev;
	ret = v4l2_device_रेजिस्टर(isp->dev, &isp->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "%s: V4L2 device registration failed (%d)\n",
			__func__, ret);
		जाओ करोne;
	पूर्ण

	/* Register पूर्णांकernal entities */
	ret = omap3isp_ccp2_रेजिस्टर_entities(&isp->isp_ccp2, &isp->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap3isp_csi2_रेजिस्टर_entities(&isp->isp_csi2a, &isp->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap3isp_ccdc_रेजिस्टर_entities(&isp->isp_ccdc, &isp->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap3isp_preview_रेजिस्टर_entities(&isp->isp_prev,
						 &isp->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap3isp_resizer_रेजिस्टर_entities(&isp->isp_res, &isp->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap3isp_stat_रेजिस्टर_entities(&isp->isp_aewb, &isp->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap3isp_stat_रेजिस्टर_entities(&isp->isp_af, &isp->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap3isp_stat_रेजिस्टर_entities(&isp->isp_hist, &isp->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

करोne:
	अगर (ret < 0)
		isp_unरेजिस्टर_entities(isp);

	वापस ret;
पूर्ण

/*
 * isp_create_links() - Create links क्रम पूर्णांकernal and बाह्यal ISP entities
 * @isp : Poपूर्णांकer to ISP device
 *
 * This function creates all links between ISP पूर्णांकernal and बाह्यal entities.
 *
 * Return: A negative error code on failure or zero on success. Possible error
 * codes are those वापसed by media_create_pad_link().
 */
अटल पूर्णांक isp_create_links(काष्ठा isp_device *isp)
अणु
	पूर्णांक ret;

	/* Create links between entities and video nodes. */
	ret = media_create_pad_link(
			&isp->isp_csi2a.subdev.entity, CSI2_PAD_SOURCE,
			&isp->isp_csi2a.video_out.video.entity, 0, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_ccp2.video_in.video.entity, 0,
			&isp->isp_ccp2.subdev.entity, CCP2_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOURCE_OF,
			&isp->isp_ccdc.video_out.video.entity, 0, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_prev.video_in.video.entity, 0,
			&isp->isp_prev.subdev.entity, PREV_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_prev.subdev.entity, PREV_PAD_SOURCE,
			&isp->isp_prev.video_out.video.entity, 0, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_res.video_in.video.entity, 0,
			&isp->isp_res.subdev.entity, RESZ_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_res.subdev.entity, RESZ_PAD_SOURCE,
			&isp->isp_res.video_out.video.entity, 0, 0);

	अगर (ret < 0)
		वापस ret;

	/* Create links between entities. */
	ret = media_create_pad_link(
			&isp->isp_csi2a.subdev.entity, CSI2_PAD_SOURCE,
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_ccp2.subdev.entity, CCP2_PAD_SOURCE,
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOURCE_VP,
			&isp->isp_prev.subdev.entity, PREV_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOURCE_OF,
			&isp->isp_res.subdev.entity, RESZ_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_prev.subdev.entity, PREV_PAD_SOURCE,
			&isp->isp_res.subdev.entity, RESZ_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOURCE_VP,
			&isp->isp_aewb.subdev.entity, 0,
			MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOURCE_VP,
			&isp->isp_af.subdev.entity, 0,
			MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOURCE_VP,
			&isp->isp_hist.subdev.entity, 0,
			MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम isp_cleanup_modules(काष्ठा isp_device *isp)
अणु
	omap3isp_h3a_aewb_cleanup(isp);
	omap3isp_h3a_af_cleanup(isp);
	omap3isp_hist_cleanup(isp);
	omap3isp_resizer_cleanup(isp);
	omap3isp_preview_cleanup(isp);
	omap3isp_ccdc_cleanup(isp);
	omap3isp_ccp2_cleanup(isp);
	omap3isp_csi2_cleanup(isp);
	omap3isp_csiphy_cleanup(isp);
पूर्ण

अटल पूर्णांक isp_initialize_modules(काष्ठा isp_device *isp)
अणु
	पूर्णांक ret;

	ret = omap3isp_csiphy_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "CSI PHY initialization failed\n");
		वापस ret;
	पूर्ण

	ret = omap3isp_csi2_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "CSI2 initialization failed\n");
		जाओ error_csi2;
	पूर्ण

	ret = omap3isp_ccp2_init(isp);
	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(isp->dev, "CCP2 initialization failed\n");
		जाओ error_ccp2;
	पूर्ण

	ret = omap3isp_ccdc_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "CCDC initialization failed\n");
		जाओ error_ccdc;
	पूर्ण

	ret = omap3isp_preview_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "Preview initialization failed\n");
		जाओ error_preview;
	पूर्ण

	ret = omap3isp_resizer_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "Resizer initialization failed\n");
		जाओ error_resizer;
	पूर्ण

	ret = omap3isp_hist_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "Histogram initialization failed\n");
		जाओ error_hist;
	पूर्ण

	ret = omap3isp_h3a_aewb_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "H3A AEWB initialization failed\n");
		जाओ error_h3a_aewb;
	पूर्ण

	ret = omap3isp_h3a_af_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "H3A AF initialization failed\n");
		जाओ error_h3a_af;
	पूर्ण

	वापस 0;

error_h3a_af:
	omap3isp_h3a_aewb_cleanup(isp);
error_h3a_aewb:
	omap3isp_hist_cleanup(isp);
error_hist:
	omap3isp_resizer_cleanup(isp);
error_resizer:
	omap3isp_preview_cleanup(isp);
error_preview:
	omap3isp_ccdc_cleanup(isp);
error_ccdc:
	omap3isp_ccp2_cleanup(isp);
error_ccp2:
	omap3isp_csi2_cleanup(isp);
error_csi2:
	omap3isp_csiphy_cleanup(isp);

	वापस ret;
पूर्ण

अटल व्योम isp_detach_iommu(काष्ठा isp_device *isp)
अणु
#अगर_घोषित CONFIG_ARM_DMA_USE_IOMMU
	arm_iommu_detach_device(isp->dev);
	arm_iommu_release_mapping(isp->mapping);
	isp->mapping = शून्य;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक isp_attach_iommu(काष्ठा isp_device *isp)
अणु
#अगर_घोषित CONFIG_ARM_DMA_USE_IOMMU
	काष्ठा dma_iommu_mapping *mapping;
	पूर्णांक ret;

	/*
	 * Create the ARM mapping, used by the ARM DMA mapping core to allocate
	 * VAs. This will allocate a corresponding IOMMU करोमुख्य.
	 */
	mapping = arm_iommu_create_mapping(&platक्रमm_bus_type, SZ_1G, SZ_2G);
	अगर (IS_ERR(mapping)) अणु
		dev_err(isp->dev, "failed to create ARM IOMMU mapping\n");
		वापस PTR_ERR(mapping);
	पूर्ण

	isp->mapping = mapping;

	/* Attach the ARM VA mapping to the device. */
	ret = arm_iommu_attach_device(isp->dev, mapping);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "failed to attach device to VA mapping\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	arm_iommu_release_mapping(isp->mapping);
	isp->mapping = शून्य;
	वापस ret;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

/*
 * isp_हटाओ - Remove ISP platक्रमm device
 * @pdev: Poपूर्णांकer to ISP platक्रमm device
 *
 * Always वापसs 0.
 */
अटल पूर्णांक isp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा isp_device *isp = platक्रमm_get_drvdata(pdev);

	v4l2_async_notअगरier_unरेजिस्टर(&isp->notअगरier);
	isp_unरेजिस्टर_entities(isp);
	isp_cleanup_modules(isp);
	isp_xclk_cleanup(isp);

	__omap3isp_get(isp, false);
	isp_detach_iommu(isp);
	__omap3isp_put(isp, false);

	media_entity_क्रमागत_cleanup(&isp->crashed);
	v4l2_async_notअगरier_cleanup(&isp->notअगरier);

	kमुक्त(isp);

	वापस 0;
पूर्ण

क्रमागत isp_of_phy अणु
	ISP_OF_PHY_PARALLEL = 0,
	ISP_OF_PHY_CSIPHY1,
	ISP_OF_PHY_CSIPHY2,
पूर्ण;

अटल पूर्णांक isp_subdev_notअगरier_complete(काष्ठा v4l2_async_notअगरier *async)
अणु
	काष्ठा isp_device *isp = container_of(async, काष्ठा isp_device,
					      notअगरier);
	काष्ठा v4l2_device *v4l2_dev = &isp->v4l2_dev;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	mutex_lock(&isp->media_dev.graph_mutex);

	ret = media_entity_क्रमागत_init(&isp->crashed, &isp->media_dev);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(sd, &v4l2_dev->subdevs, list) अणु
		अगर (sd->notअगरier != &isp->notअगरier)
			जारी;

		ret = isp_link_entity(isp, &sd->entity,
				      v4l2_subdev_to_bus_cfg(sd)->पूर्णांकerface);
		अगर (ret < 0) अणु
			mutex_unlock(&isp->media_dev.graph_mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&isp->media_dev.graph_mutex);

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&isp->v4l2_dev);
	अगर (ret < 0)
		वापस ret;

	वापस media_device_रेजिस्टर(&isp->media_dev);
पूर्ण

अटल व्योम isp_parse_of_parallel_endpoपूर्णांक(काष्ठा device *dev,
					   काष्ठा v4l2_fwnode_endpoपूर्णांक *vep,
					   काष्ठा isp_bus_cfg *buscfg)
अणु
	buscfg->पूर्णांकerface = ISP_INTERFACE_PARALLEL;
	buscfg->bus.parallel.data_lane_shअगरt = vep->bus.parallel.data_shअगरt;
	buscfg->bus.parallel.clk_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_PCLK_SAMPLE_FALLING);
	buscfg->bus.parallel.hs_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_VSYNC_ACTIVE_LOW);
	buscfg->bus.parallel.vs_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_HSYNC_ACTIVE_LOW);
	buscfg->bus.parallel.fld_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_FIELD_EVEN_LOW);
	buscfg->bus.parallel.data_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_DATA_ACTIVE_LOW);
	buscfg->bus.parallel.bt656 = vep->bus_type == V4L2_MBUS_BT656;
पूर्ण

अटल व्योम isp_parse_of_csi2_endpoपूर्णांक(काष्ठा device *dev,
				       काष्ठा v4l2_fwnode_endpoपूर्णांक *vep,
				       काष्ठा isp_bus_cfg *buscfg)
अणु
	अचिन्हित पूर्णांक i;

	buscfg->bus.csi2.lanecfg.clk.pos = vep->bus.mipi_csi2.घड़ी_lane;
	buscfg->bus.csi2.lanecfg.clk.pol =
		vep->bus.mipi_csi2.lane_polarities[0];
	dev_dbg(dev, "clock lane polarity %u, pos %u\n",
		buscfg->bus.csi2.lanecfg.clk.pol,
		buscfg->bus.csi2.lanecfg.clk.pos);

	buscfg->bus.csi2.num_data_lanes = vep->bus.mipi_csi2.num_data_lanes;

	क्रम (i = 0; i < buscfg->bus.csi2.num_data_lanes; i++) अणु
		buscfg->bus.csi2.lanecfg.data[i].pos =
			vep->bus.mipi_csi2.data_lanes[i];
		buscfg->bus.csi2.lanecfg.data[i].pol =
			vep->bus.mipi_csi2.lane_polarities[i + 1];
		dev_dbg(dev,
			"data lane %u polarity %u, pos %u\n", i,
			buscfg->bus.csi2.lanecfg.data[i].pol,
			buscfg->bus.csi2.lanecfg.data[i].pos);
	पूर्ण
	/*
	 * FIXME: now we assume the CRC is always there. Implement a way to
	 * obtain this inक्रमmation from the sensor. Frame descriptors, perhaps?
	 */
	buscfg->bus.csi2.crc = 1;
पूर्ण

अटल व्योम isp_parse_of_csi1_endpoपूर्णांक(काष्ठा device *dev,
				       काष्ठा v4l2_fwnode_endpoपूर्णांक *vep,
				       काष्ठा isp_bus_cfg *buscfg)
अणु
	buscfg->bus.ccp2.lanecfg.clk.pos = vep->bus.mipi_csi1.घड़ी_lane;
	buscfg->bus.ccp2.lanecfg.clk.pol = vep->bus.mipi_csi1.lane_polarity[0];
	dev_dbg(dev, "clock lane polarity %u, pos %u\n",
		buscfg->bus.ccp2.lanecfg.clk.pol,
	buscfg->bus.ccp2.lanecfg.clk.pos);

	buscfg->bus.ccp2.lanecfg.data[0].pos = vep->bus.mipi_csi1.data_lane;
	buscfg->bus.ccp2.lanecfg.data[0].pol =
		vep->bus.mipi_csi1.lane_polarity[1];

	dev_dbg(dev, "data lane polarity %u, pos %u\n",
		buscfg->bus.ccp2.lanecfg.data[0].pol,
		buscfg->bus.ccp2.lanecfg.data[0].pos);

	buscfg->bus.ccp2.strobe_clk_pol = vep->bus.mipi_csi1.घड़ी_inv;
	buscfg->bus.ccp2.phy_layer = vep->bus.mipi_csi1.strobe;
	buscfg->bus.ccp2.ccp2_mode = vep->bus_type == V4L2_MBUS_CCP2;
	buscfg->bus.ccp2.vp_clk_pol = 1;

	buscfg->bus.ccp2.crc = 1;
पूर्ण

अटल काष्ठा अणु
	u32 phy;
	u32 csi2_अगर;
	u32 csi1_अगर;
पूर्ण isp_bus_पूर्णांकerfaces[2] = अणु
	अणु ISP_OF_PHY_CSIPHY1,
	  ISP_INTERFACE_CSI2C_PHY1, ISP_INTERFACE_CCP2B_PHY1 पूर्ण,
	अणु ISP_OF_PHY_CSIPHY2,
	  ISP_INTERFACE_CSI2A_PHY2, ISP_INTERFACE_CCP2B_PHY2 पूर्ण,
पूर्ण;

अटल पूर्णांक isp_parse_of_endpoपूर्णांकs(काष्ठा isp_device *isp)
अणु
	काष्ठा fwnode_handle *ep;
	काष्ठा isp_async_subdev *isd = शून्य;
	अचिन्हित पूर्णांक i;

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(
		dev_fwnode(isp->dev), ISP_OF_PHY_PARALLEL, 0,
		FWNODE_GRAPH_ENDPOINT_NEXT);

	अगर (ep) अणु
		काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
			.bus_type = V4L2_MBUS_PARALLEL
		पूर्ण;
		पूर्णांक ret;

		dev_dbg(isp->dev, "parsing parallel interface\n");

		ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);

		अगर (!ret) अणु
			isd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
				&isp->notअगरier, ep, काष्ठा isp_async_subdev);
			अगर (!IS_ERR(isd))
				isp_parse_of_parallel_endpoपूर्णांक(isp->dev, &vep, &isd->bus);
		पूर्ण

		fwnode_handle_put(ep);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(isp_bus_पूर्णांकerfaces); i++) अणु
		काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
			.bus_type = V4L2_MBUS_CSI2_DPHY
		पूर्ण;
		पूर्णांक ret;

		ep = fwnode_graph_get_endpoपूर्णांक_by_id(
			dev_fwnode(isp->dev), isp_bus_पूर्णांकerfaces[i].phy, 0,
			FWNODE_GRAPH_ENDPOINT_NEXT);

		अगर (!ep)
			जारी;

		dev_dbg(isp->dev, "parsing serial interface %u, node %pOF\n", i,
			to_of_node(ep));

		ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
		अगर (ret == -ENXIO) अणु
			vep = (काष्ठा v4l2_fwnode_endpoपूर्णांक)
				अणु .bus_type = V4L2_MBUS_CSI1 पूर्ण;
			ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);

			अगर (ret == -ENXIO) अणु
				vep = (काष्ठा v4l2_fwnode_endpoपूर्णांक)
					अणु .bus_type = V4L2_MBUS_CCP2 पूर्ण;
				ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
			पूर्ण
		पूर्ण

		अगर (!ret) अणु
			isd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
				&isp->notअगरier, ep, काष्ठा isp_async_subdev);

			अगर (!IS_ERR(isd)) अणु
				चयन (vep.bus_type) अणु
				हाल V4L2_MBUS_CSI2_DPHY:
					isd->bus.पूर्णांकerface =
						isp_bus_पूर्णांकerfaces[i].csi2_अगर;
					isp_parse_of_csi2_endpoपूर्णांक(isp->dev, &vep, &isd->bus);
					अवरोध;
				हाल V4L2_MBUS_CSI1:
				हाल V4L2_MBUS_CCP2:
					isd->bus.पूर्णांकerface =
						isp_bus_पूर्णांकerfaces[i].csi1_अगर;
					isp_parse_of_csi1_endpoपूर्णांक(isp->dev, &vep,
								   &isd->bus);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		fwnode_handle_put(ep);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations isp_subdev_notअगरier_ops = अणु
	.complete = isp_subdev_notअगरier_complete,
पूर्ण;

/*
 * isp_probe - Probe ISP platक्रमm device
 * @pdev: Poपूर्णांकer to ISP platक्रमm device
 *
 * Returns 0 अगर successful,
 *   -ENOMEM अगर no memory available,
 *   -ENODEV अगर no platक्रमm device resources found
 *     or no space क्रम remapping रेजिस्टरs,
 *   -EINVAL अगर couldn't install ISR,
 *   or clk_get वापस error value.
 */
अटल पूर्णांक isp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा isp_device *isp;
	काष्ठा resource *mem;
	पूर्णांक ret;
	पूर्णांक i, m;

	isp = kzalloc(माप(*isp), GFP_KERNEL);
	अगर (!isp) अणु
		dev_err(&pdev->dev, "could not allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(of_fwnode_handle(pdev->dev.of_node),
				       "ti,phy-type", &isp->phy_type);
	अगर (ret)
		जाओ error_release_isp;

	isp->syscon = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						      "syscon");
	अगर (IS_ERR(isp->syscon)) अणु
		ret = PTR_ERR(isp->syscon);
		जाओ error_release_isp;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(pdev->dev.of_node,
					 "syscon", 1, &isp->syscon_offset);
	अगर (ret)
		जाओ error_release_isp;

	isp->स्वतःidle = स्वतःidle;

	mutex_init(&isp->isp_mutex);
	spin_lock_init(&isp->stat_lock);
	v4l2_async_notअगरier_init(&isp->notअगरier);
	isp->dev = &pdev->dev;

	ret = isp_parse_of_endpoपूर्णांकs(isp);
	अगर (ret < 0)
		जाओ error;

	isp->ref_count = 0;

	ret = dma_coerce_mask_and_coherent(isp->dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ error;

	platक्रमm_set_drvdata(pdev, isp);

	/* Regulators */
	isp->isp_csiphy1.vdd = devm_regulator_get(&pdev->dev, "vdd-csiphy1");
	isp->isp_csiphy2.vdd = devm_regulator_get(&pdev->dev, "vdd-csiphy2");

	/* Clocks
	 *
	 * The ISP घड़ी tree is revision-dependent. We thus need to enable ICLK
	 * manually to पढ़ो the revision beक्रमe calling __omap3isp_get().
	 *
	 * Start by mapping the ISP MMIO area, which is in two pieces.
	 * The ISP IOMMU is in between. Map both now, and fill in the
	 * ISP revision specअगरic portions a little later in the
	 * function.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		अचिन्हित पूर्णांक map_idx = i ? OMAP3_ISP_IOMEM_CSI2A_REGS1 : 0;

		mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		isp->mmio_base[map_idx] =
			devm_ioremap_resource(isp->dev, mem);
		अगर (IS_ERR(isp->mmio_base[map_idx])) अणु
			ret = PTR_ERR(isp->mmio_base[map_idx]);
			जाओ error;
		पूर्ण
	पूर्ण

	ret = isp_get_घड़ीs(isp);
	अगर (ret < 0)
		जाओ error;

	ret = clk_enable(isp->घड़ी[ISP_CLK_CAM_ICK]);
	अगर (ret < 0)
		जाओ error;

	isp->revision = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_MAIN, ISP_REVISION);
	dev_info(isp->dev, "Revision %d.%d found\n",
		 (isp->revision & 0xf0) >> 4, isp->revision & 0x0f);

	clk_disable(isp->घड़ी[ISP_CLK_CAM_ICK]);

	अगर (__omap3isp_get(isp, false) == शून्य) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	ret = isp_reset(isp);
	अगर (ret < 0)
		जाओ error_isp;

	ret = isp_xclk_init(isp);
	अगर (ret < 0)
		जाओ error_isp;

	/* Memory resources */
	क्रम (m = 0; m < ARRAY_SIZE(isp_res_maps); m++)
		अगर (isp->revision == isp_res_maps[m].isp_rev)
			अवरोध;

	अगर (m == ARRAY_SIZE(isp_res_maps)) अणु
		dev_err(isp->dev, "No resource map found for ISP rev %d.%d\n",
			(isp->revision & 0xf0) >> 4, isp->revision & 0xf);
		ret = -ENODEV;
		जाओ error_isp;
	पूर्ण

	क्रम (i = 1; i < OMAP3_ISP_IOMEM_CSI2A_REGS1; i++)
		isp->mmio_base[i] =
			isp->mmio_base[0] + isp_res_maps[m].offset[i];

	क्रम (i = OMAP3_ISP_IOMEM_CSIPHY2; i < OMAP3_ISP_IOMEM_LAST; i++)
		isp->mmio_base[i] =
			isp->mmio_base[OMAP3_ISP_IOMEM_CSI2A_REGS1]
			+ isp_res_maps[m].offset[i];

	isp->mmio_hist_base_phys =
		mem->start + isp_res_maps[m].offset[OMAP3_ISP_IOMEM_HIST];

	/* IOMMU */
	ret = isp_attach_iommu(isp);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "unable to attach to IOMMU\n");
		जाओ error_isp;
	पूर्ण

	/* Interrupt */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret <= 0) अणु
		ret = -ENODEV;
		जाओ error_iommu;
	पूर्ण
	isp->irq_num = ret;

	अगर (devm_request_irq(isp->dev, isp->irq_num, isp_isr, IRQF_SHARED,
			     "OMAP3 ISP", isp)) अणु
		dev_err(isp->dev, "Unable to request IRQ\n");
		ret = -EINVAL;
		जाओ error_iommu;
	पूर्ण

	/* Entities */
	ret = isp_initialize_modules(isp);
	अगर (ret < 0)
		जाओ error_iommu;

	ret = isp_रेजिस्टर_entities(isp);
	अगर (ret < 0)
		जाओ error_modules;

	ret = isp_create_links(isp);
	अगर (ret < 0)
		जाओ error_रेजिस्टर_entities;

	isp->notअगरier.ops = &isp_subdev_notअगरier_ops;

	ret = v4l2_async_notअगरier_रेजिस्टर(&isp->v4l2_dev, &isp->notअगरier);
	अगर (ret)
		जाओ error_रेजिस्टर_entities;

	isp_core_init(isp, 1);
	omap3isp_put(isp);

	वापस 0;

error_रेजिस्टर_entities:
	isp_unरेजिस्टर_entities(isp);
error_modules:
	isp_cleanup_modules(isp);
error_iommu:
	isp_detach_iommu(isp);
error_isp:
	isp_xclk_cleanup(isp);
	__omap3isp_put(isp, false);
error:
	v4l2_async_notअगरier_cleanup(&isp->notअगरier);
	mutex_destroy(&isp->isp_mutex);
error_release_isp:
	kमुक्त(isp);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap3isp_pm_ops = अणु
	.prepare = isp_pm_prepare,
	.suspend = isp_pm_suspend,
	.resume = isp_pm_resume,
	.complete = isp_pm_complete,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id omap3isp_id_table[] = अणु
	अणु "omap3isp", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, omap3isp_id_table);

अटल स्थिर काष्ठा of_device_id omap3isp_of_table[] = अणु
	अणु .compatible = "ti,omap3-isp" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap3isp_of_table);

अटल काष्ठा platक्रमm_driver omap3isp_driver = अणु
	.probe = isp_probe,
	.हटाओ = isp_हटाओ,
	.id_table = omap3isp_id_table,
	.driver = अणु
		.name = "omap3isp",
		.pm	= &omap3isp_pm_ops,
		.of_match_table = omap3isp_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap3isp_driver);

MODULE_AUTHOR("Nokia Corporation");
MODULE_DESCRIPTION("TI OMAP3 ISP driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(ISP_VIDEO_DRIVER_VERSION);
