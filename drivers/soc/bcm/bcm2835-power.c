<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Power करोमुख्य driver क्रम Broadcom BCM2835
 *
 * Copyright (C) 2018 Broadcom
 */

#समावेश <dt-bindings/soc/bcm2835-pm.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/bcm2835-pm.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/types.h>

#घोषणा PM_GNRIC                        0x00
#घोषणा PM_AUDIO                        0x04
#घोषणा PM_STATUS                       0x18
#घोषणा PM_RSTC				0x1c
#घोषणा PM_RSTS				0x20
#घोषणा PM_WDOG				0x24
#घोषणा PM_PADS0			0x28
#घोषणा PM_PADS2			0x2c
#घोषणा PM_PADS3			0x30
#घोषणा PM_PADS4			0x34
#घोषणा PM_PADS5			0x38
#घोषणा PM_PADS6			0x3c
#घोषणा PM_CAM0				0x44
#घोषणा PM_CAM0_LDOHPEN			BIT(2)
#घोषणा PM_CAM0_LDOLPEN			BIT(1)
#घोषणा PM_CAM0_CTRLEN			BIT(0)

#घोषणा PM_CAM1				0x48
#घोषणा PM_CAM1_LDOHPEN			BIT(2)
#घोषणा PM_CAM1_LDOLPEN			BIT(1)
#घोषणा PM_CAM1_CTRLEN			BIT(0)

#घोषणा PM_CCP2TX			0x4c
#घोषणा PM_CCP2TX_LDOEN			BIT(1)
#घोषणा PM_CCP2TX_CTRLEN		BIT(0)

#घोषणा PM_DSI0				0x50
#घोषणा PM_DSI0_LDOHPEN			BIT(2)
#घोषणा PM_DSI0_LDOLPEN			BIT(1)
#घोषणा PM_DSI0_CTRLEN			BIT(0)

#घोषणा PM_DSI1				0x54
#घोषणा PM_DSI1_LDOHPEN			BIT(2)
#घोषणा PM_DSI1_LDOLPEN			BIT(1)
#घोषणा PM_DSI1_CTRLEN			BIT(0)

#घोषणा PM_HDMI				0x58
#घोषणा PM_HDMI_RSTDR			BIT(19)
#घोषणा PM_HDMI_LDOPD			BIT(1)
#घोषणा PM_HDMI_CTRLEN			BIT(0)

#घोषणा PM_USB				0x5c
/* The घातer gates must be enabled with this bit beक्रमe enabling the LDO in the
 * USB block.
 */
#घोषणा PM_USB_CTRLEN			BIT(0)

#घोषणा PM_PXLDO			0x60
#घोषणा PM_PXBG				0x64
#घोषणा PM_DFT				0x68
#घोषणा PM_SMPS				0x6c
#घोषणा PM_XOSC				0x70
#घोषणा PM_SPAREW			0x74
#घोषणा PM_SPARER			0x78
#घोषणा PM_AVS_RSTDR			0x7c
#घोषणा PM_AVS_STAT			0x80
#घोषणा PM_AVS_EVENT			0x84
#घोषणा PM_AVS_INTEN			0x88
#घोषणा PM_DUMMY			0xfc

#घोषणा PM_IMAGE			0x108
#घोषणा PM_GRAFX			0x10c
#घोषणा PM_PROC				0x110
#घोषणा PM_ENAB				BIT(12)
#घोषणा PM_ISPRSTN			BIT(8)
#घोषणा PM_H264RSTN			BIT(7)
#घोषणा PM_PERIRSTN			BIT(6)
#घोषणा PM_V3DRSTN			BIT(6)
#घोषणा PM_ISFUNC			BIT(5)
#घोषणा PM_MRDONE			BIT(4)
#घोषणा PM_MEMREP			BIT(3)
#घोषणा PM_ISPOW			BIT(2)
#घोषणा PM_POWOK			BIT(1)
#घोषणा PM_POWUP			BIT(0)
#घोषणा PM_INRUSH_SHIFT			13
#घोषणा PM_INRUSH_3_5_MA		0
#घोषणा PM_INRUSH_5_MA			1
#घोषणा PM_INRUSH_10_MA			2
#घोषणा PM_INRUSH_20_MA			3
#घोषणा PM_INRUSH_MASK			(3 << PM_INRUSH_SHIFT)

#घोषणा PM_PASSWORD			0x5a000000

#घोषणा PM_WDOG_TIME_SET		0x000fffff
#घोषणा PM_RSTC_WRCFG_CLR		0xffffffcf
#घोषणा PM_RSTS_HADWRH_SET		0x00000040
#घोषणा PM_RSTC_WRCFG_SET		0x00000030
#घोषणा PM_RSTC_WRCFG_FULL_RESET	0x00000020
#घोषणा PM_RSTC_RESET			0x00000102

#घोषणा PM_READ(reg) पढ़ोl(घातer->base + (reg))
#घोषणा PM_WRITE(reg, val) ग_लिखोl(PM_PASSWORD | (val), घातer->base + (reg))

#घोषणा ASB_BRDG_VERSION                0x00
#घोषणा ASB_CPR_CTRL                    0x04

#घोषणा ASB_V3D_S_CTRL			0x08
#घोषणा ASB_V3D_M_CTRL			0x0c
#घोषणा ASB_ISP_S_CTRL			0x10
#घोषणा ASB_ISP_M_CTRL			0x14
#घोषणा ASB_H264_S_CTRL			0x18
#घोषणा ASB_H264_M_CTRL			0x1c

#घोषणा ASB_REQ_STOP                    BIT(0)
#घोषणा ASB_ACK                         BIT(1)
#घोषणा ASB_EMPTY                       BIT(2)
#घोषणा ASB_FULL                        BIT(3)

#घोषणा ASB_AXI_BRDG_ID			0x20

#घोषणा ASB_READ(reg) पढ़ोl(घातer->asb + (reg))
#घोषणा ASB_WRITE(reg, val) ग_लिखोl(PM_PASSWORD | (val), घातer->asb + (reg))

काष्ठा bcm2835_घातer_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य base;
	काष्ठा bcm2835_घातer *घातer;
	u32 करोमुख्य;
	काष्ठा clk *clk;
पूर्ण;

काष्ठा bcm2835_घातer अणु
	काष्ठा device		*dev;
	/* PM रेजिस्टरs. */
	व्योम __iomem		*base;
	/* AXI Async bridge रेजिस्टरs. */
	व्योम __iomem		*asb;

	काष्ठा genpd_onecell_data pd_xlate;
	काष्ठा bcm2835_घातer_करोमुख्य करोमुख्यs[BCM2835_POWER_DOMAIN_COUNT];
	काष्ठा reset_controller_dev reset;
पूर्ण;

अटल पूर्णांक bcm2835_asb_enable(काष्ठा bcm2835_घातer *घातer, u32 reg)
अणु
	u64 start;

	अगर (!reg)
		वापस 0;

	start = kसमय_get_ns();

	/* Enable the module's async AXI bridges. */
	ASB_WRITE(reg, ASB_READ(reg) & ~ASB_REQ_STOP);
	जबतक (ASB_READ(reg) & ASB_ACK) अणु
		cpu_relax();
		अगर (kसमय_get_ns() - start >= 1000)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_asb_disable(काष्ठा bcm2835_घातer *घातer, u32 reg)
अणु
	u64 start;

	अगर (!reg)
		वापस 0;

	start = kसमय_get_ns();

	/* Enable the module's async AXI bridges. */
	ASB_WRITE(reg, ASB_READ(reg) | ASB_REQ_STOP);
	जबतक (!(ASB_READ(reg) & ASB_ACK)) अणु
		cpu_relax();
		अगर (kसमय_get_ns() - start >= 1000)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_घातer_घातer_off(काष्ठा bcm2835_घातer_करोमुख्य *pd, u32 pm_reg)
अणु
	काष्ठा bcm2835_घातer *घातer = pd->घातer;

	/* Enable functional isolation */
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~PM_ISFUNC);

	/* Enable electrical isolation */
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~PM_ISPOW);

	/* Open the घातer चयनes. */
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~PM_POWUP);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_घातer_घातer_on(काष्ठा bcm2835_घातer_करोमुख्य *pd, u32 pm_reg)
अणु
	काष्ठा bcm2835_घातer *घातer = pd->घातer;
	काष्ठा device *dev = घातer->dev;
	u64 start;
	पूर्णांक ret;
	पूर्णांक inrush;
	bool घातok;

	/* If it was alपढ़ोy घातered on by the fw, leave it that way. */
	अगर (PM_READ(pm_reg) & PM_POWUP)
		वापस 0;

	/* Enable घातer.  Allowing too much current at once may result
	 * in POWOK never getting set, so start low and ramp it up as
	 * necessary to succeed.
	 */
	घातok = false;
	क्रम (inrush = PM_INRUSH_3_5_MA; inrush <= PM_INRUSH_20_MA; inrush++) अणु
		PM_WRITE(pm_reg,
			 (PM_READ(pm_reg) & ~PM_INRUSH_MASK) |
			 (inrush << PM_INRUSH_SHIFT) |
			 PM_POWUP);

		start = kसमय_get_ns();
		जबतक (!(घातok = !!(PM_READ(pm_reg) & PM_POWOK))) अणु
			cpu_relax();
			अगर (kसमय_get_ns() - start >= 3000)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (!घातok) अणु
		dev_err(dev, "Timeout waiting for %s power OK\n",
			pd->base.name);
		ret = -ETIMEDOUT;
		जाओ err_disable_घातup;
	पूर्ण

	/* Disable electrical isolation */
	PM_WRITE(pm_reg, PM_READ(pm_reg) | PM_ISPOW);

	/* Repair memory */
	PM_WRITE(pm_reg, PM_READ(pm_reg) | PM_MEMREP);
	start = kसमय_get_ns();
	जबतक (!(PM_READ(pm_reg) & PM_MRDONE)) अणु
		cpu_relax();
		अगर (kसमय_get_ns() - start >= 1000) अणु
			dev_err(dev, "Timeout waiting for %s memory repair\n",
				pd->base.name);
			ret = -ETIMEDOUT;
			जाओ err_disable_isघात;
		पूर्ण
	पूर्ण

	/* Disable functional isolation */
	PM_WRITE(pm_reg, PM_READ(pm_reg) | PM_ISFUNC);

	वापस 0;

err_disable_isघात:
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~PM_ISPOW);
err_disable_घातup:
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~(PM_POWUP | PM_INRUSH_MASK));
	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835_asb_घातer_on(काष्ठा bcm2835_घातer_करोमुख्य *pd,
				u32 pm_reg,
				u32 asb_m_reg,
				u32 asb_s_reg,
				u32 reset_flags)
अणु
	काष्ठा bcm2835_घातer *घातer = pd->घातer;
	पूर्णांक ret;

	ret = clk_prepare_enable(pd->clk);
	अगर (ret) अणु
		dev_err(घातer->dev, "Failed to enable clock for %s\n",
			pd->base.name);
		वापस ret;
	पूर्ण

	/* Wait 32 घड़ीs क्रम reset to propagate, 1 us will be enough */
	udelay(1);

	clk_disable_unprepare(pd->clk);

	/* Deनिश्चित the resets. */
	PM_WRITE(pm_reg, PM_READ(pm_reg) | reset_flags);

	ret = clk_prepare_enable(pd->clk);
	अगर (ret) अणु
		dev_err(घातer->dev, "Failed to enable clock for %s\n",
			pd->base.name);
		जाओ err_enable_resets;
	पूर्ण

	ret = bcm2835_asb_enable(घातer, asb_m_reg);
	अगर (ret) अणु
		dev_err(घातer->dev, "Failed to enable ASB master for %s\n",
			pd->base.name);
		जाओ err_disable_clk;
	पूर्ण
	ret = bcm2835_asb_enable(घातer, asb_s_reg);
	अगर (ret) अणु
		dev_err(घातer->dev, "Failed to enable ASB slave for %s\n",
			pd->base.name);
		जाओ err_disable_asb_master;
	पूर्ण

	वापस 0;

err_disable_asb_master:
	bcm2835_asb_disable(घातer, asb_m_reg);
err_disable_clk:
	clk_disable_unprepare(pd->clk);
err_enable_resets:
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~reset_flags);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835_asb_घातer_off(काष्ठा bcm2835_घातer_करोमुख्य *pd,
				 u32 pm_reg,
				 u32 asb_m_reg,
				 u32 asb_s_reg,
				 u32 reset_flags)
अणु
	काष्ठा bcm2835_घातer *घातer = pd->घातer;
	पूर्णांक ret;

	ret = bcm2835_asb_disable(घातer, asb_s_reg);
	अगर (ret) अणु
		dev_warn(घातer->dev, "Failed to disable ASB slave for %s\n",
			 pd->base.name);
		वापस ret;
	पूर्ण
	ret = bcm2835_asb_disable(घातer, asb_m_reg);
	अगर (ret) अणु
		dev_warn(घातer->dev, "Failed to disable ASB master for %s\n",
			 pd->base.name);
		bcm2835_asb_enable(घातer, asb_s_reg);
		वापस ret;
	पूर्ण

	clk_disable_unprepare(pd->clk);

	/* Assert the resets. */
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~reset_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_घातer_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा bcm2835_घातer_करोमुख्य *pd =
		container_of(करोमुख्य, काष्ठा bcm2835_घातer_करोमुख्य, base);
	काष्ठा bcm2835_घातer *घातer = pd->घातer;

	चयन (pd->करोमुख्य) अणु
	हाल BCM2835_POWER_DOMAIN_GRAFX:
		वापस bcm2835_घातer_घातer_on(pd, PM_GRAFX);

	हाल BCM2835_POWER_DOMAIN_GRAFX_V3D:
		वापस bcm2835_asb_घातer_on(pd, PM_GRAFX,
					    ASB_V3D_M_CTRL, ASB_V3D_S_CTRL,
					    PM_V3DRSTN);

	हाल BCM2835_POWER_DOMAIN_IMAGE:
		वापस bcm2835_घातer_घातer_on(pd, PM_IMAGE);

	हाल BCM2835_POWER_DOMAIN_IMAGE_PERI:
		वापस bcm2835_asb_घातer_on(pd, PM_IMAGE,
					    0, 0,
					    PM_PERIRSTN);

	हाल BCM2835_POWER_DOMAIN_IMAGE_ISP:
		वापस bcm2835_asb_घातer_on(pd, PM_IMAGE,
					    ASB_ISP_M_CTRL, ASB_ISP_S_CTRL,
					    PM_ISPRSTN);

	हाल BCM2835_POWER_DOMAIN_IMAGE_H264:
		वापस bcm2835_asb_घातer_on(pd, PM_IMAGE,
					    ASB_H264_M_CTRL, ASB_H264_S_CTRL,
					    PM_H264RSTN);

	हाल BCM2835_POWER_DOMAIN_USB:
		PM_WRITE(PM_USB, PM_USB_CTRLEN);
		वापस 0;

	हाल BCM2835_POWER_DOMAIN_DSI0:
		PM_WRITE(PM_DSI0, PM_DSI0_CTRLEN);
		PM_WRITE(PM_DSI0, PM_DSI0_CTRLEN | PM_DSI0_LDOHPEN);
		वापस 0;

	हाल BCM2835_POWER_DOMAIN_DSI1:
		PM_WRITE(PM_DSI1, PM_DSI1_CTRLEN);
		PM_WRITE(PM_DSI1, PM_DSI1_CTRLEN | PM_DSI1_LDOHPEN);
		वापस 0;

	हाल BCM2835_POWER_DOMAIN_CCP2TX:
		PM_WRITE(PM_CCP2TX, PM_CCP2TX_CTRLEN);
		PM_WRITE(PM_CCP2TX, PM_CCP2TX_CTRLEN | PM_CCP2TX_LDOEN);
		वापस 0;

	हाल BCM2835_POWER_DOMAIN_HDMI:
		PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) | PM_HDMI_RSTDR);
		PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) | PM_HDMI_CTRLEN);
		PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) & ~PM_HDMI_LDOPD);
		usleep_range(100, 200);
		PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) & ~PM_HDMI_RSTDR);
		वापस 0;

	शेष:
		dev_err(घातer->dev, "Invalid domain %d\n", pd->करोमुख्य);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm2835_घातer_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा bcm2835_घातer_करोमुख्य *pd =
		container_of(करोमुख्य, काष्ठा bcm2835_घातer_करोमुख्य, base);
	काष्ठा bcm2835_घातer *घातer = pd->घातer;

	चयन (pd->करोमुख्य) अणु
	हाल BCM2835_POWER_DOMAIN_GRAFX:
		वापस bcm2835_घातer_घातer_off(pd, PM_GRAFX);

	हाल BCM2835_POWER_DOMAIN_GRAFX_V3D:
		वापस bcm2835_asb_घातer_off(pd, PM_GRAFX,
					     ASB_V3D_M_CTRL, ASB_V3D_S_CTRL,
					     PM_V3DRSTN);

	हाल BCM2835_POWER_DOMAIN_IMAGE:
		वापस bcm2835_घातer_घातer_off(pd, PM_IMAGE);

	हाल BCM2835_POWER_DOMAIN_IMAGE_PERI:
		वापस bcm2835_asb_घातer_off(pd, PM_IMAGE,
					     0, 0,
					     PM_PERIRSTN);

	हाल BCM2835_POWER_DOMAIN_IMAGE_ISP:
		वापस bcm2835_asb_घातer_off(pd, PM_IMAGE,
					     ASB_ISP_M_CTRL, ASB_ISP_S_CTRL,
					     PM_ISPRSTN);

	हाल BCM2835_POWER_DOMAIN_IMAGE_H264:
		वापस bcm2835_asb_घातer_off(pd, PM_IMAGE,
					     ASB_H264_M_CTRL, ASB_H264_S_CTRL,
					     PM_H264RSTN);

	हाल BCM2835_POWER_DOMAIN_USB:
		PM_WRITE(PM_USB, 0);
		वापस 0;

	हाल BCM2835_POWER_DOMAIN_DSI0:
		PM_WRITE(PM_DSI0, PM_DSI0_CTRLEN);
		PM_WRITE(PM_DSI0, 0);
		वापस 0;

	हाल BCM2835_POWER_DOMAIN_DSI1:
		PM_WRITE(PM_DSI1, PM_DSI1_CTRLEN);
		PM_WRITE(PM_DSI1, 0);
		वापस 0;

	हाल BCM2835_POWER_DOMAIN_CCP2TX:
		PM_WRITE(PM_CCP2TX, PM_CCP2TX_CTRLEN);
		PM_WRITE(PM_CCP2TX, 0);
		वापस 0;

	हाल BCM2835_POWER_DOMAIN_HDMI:
		PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) | PM_HDMI_LDOPD);
		PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) & ~PM_HDMI_CTRLEN);
		वापस 0;

	शेष:
		dev_err(घातer->dev, "Invalid domain %d\n", pd->करोमुख्य);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
bcm2835_init_घातer_करोमुख्य(काष्ठा bcm2835_घातer *घातer,
			  पूर्णांक pd_xlate_index, स्थिर अक्षर *name)
अणु
	काष्ठा device *dev = घातer->dev;
	काष्ठा bcm2835_घातer_करोमुख्य *करोm = &घातer->करोमुख्यs[pd_xlate_index];

	करोm->clk = devm_clk_get(dev->parent, name);
	अगर (IS_ERR(करोm->clk)) अणु
		पूर्णांक ret = PTR_ERR(करोm->clk);

		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		/* Some करोमुख्यs करोn't have a clk, so make sure that we
		 * करोn't deref an error poपूर्णांकer later.
		 */
		करोm->clk = शून्य;
	पूर्ण

	करोm->base.name = name;
	करोm->base.घातer_on = bcm2835_घातer_pd_घातer_on;
	करोm->base.घातer_off = bcm2835_घातer_pd_घातer_off;

	करोm->करोमुख्य = pd_xlate_index;
	करोm->घातer = घातer;

	/* XXX: on/off at boot? */
	pm_genpd_init(&करोm->base, शून्य, true);

	घातer->pd_xlate.करोमुख्यs[pd_xlate_index] = &करोm->base;

	वापस 0;
पूर्ण

/** bcm2835_reset_reset - Resets a block that has a reset line in the
 * PM block.
 *
 * The consumer of the reset controller must have the घातer करोमुख्य up
 * -- there's no reset ability with the घातer करोमुख्य करोwn.  To reset
 * the sub-block, we just disable its access to memory through the
 * ASB, reset, and re-enable.
 */
अटल पूर्णांक bcm2835_reset_reset(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा bcm2835_घातer *घातer = container_of(rcdev, काष्ठा bcm2835_घातer,
						   reset);
	काष्ठा bcm2835_घातer_करोमुख्य *pd;
	पूर्णांक ret;

	चयन (id) अणु
	हाल BCM2835_RESET_V3D:
		pd = &घातer->करोमुख्यs[BCM2835_POWER_DOMAIN_GRAFX_V3D];
		अवरोध;
	हाल BCM2835_RESET_H264:
		pd = &घातer->करोमुख्यs[BCM2835_POWER_DOMAIN_IMAGE_H264];
		अवरोध;
	हाल BCM2835_RESET_ISP:
		pd = &घातer->करोमुख्यs[BCM2835_POWER_DOMAIN_IMAGE_ISP];
		अवरोध;
	शेष:
		dev_err(घातer->dev, "Bad reset id %ld\n", id);
		वापस -EINVAL;
	पूर्ण

	ret = bcm2835_घातer_pd_घातer_off(&pd->base);
	अगर (ret)
		वापस ret;

	वापस bcm2835_घातer_pd_घातer_on(&pd->base);
पूर्ण

अटल पूर्णांक bcm2835_reset_status(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा bcm2835_घातer *घातer = container_of(rcdev, काष्ठा bcm2835_घातer,
						   reset);

	चयन (id) अणु
	हाल BCM2835_RESET_V3D:
		वापस !PM_READ(PM_GRAFX & PM_V3DRSTN);
	हाल BCM2835_RESET_H264:
		वापस !PM_READ(PM_IMAGE & PM_H264RSTN);
	हाल BCM2835_RESET_ISP:
		वापस !PM_READ(PM_IMAGE & PM_ISPRSTN);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reset_control_ops bcm2835_reset_ops = अणु
	.reset = bcm2835_reset_reset,
	.status = bcm2835_reset_status,
पूर्ण;

अटल स्थिर अक्षर *स्थिर घातer_करोमुख्य_names[] = अणु
	[BCM2835_POWER_DOMAIN_GRAFX] = "grafx",
	[BCM2835_POWER_DOMAIN_GRAFX_V3D] = "v3d",

	[BCM2835_POWER_DOMAIN_IMAGE] = "image",
	[BCM2835_POWER_DOMAIN_IMAGE_PERI] = "peri_image",
	[BCM2835_POWER_DOMAIN_IMAGE_H264] = "h264",
	[BCM2835_POWER_DOMAIN_IMAGE_ISP] = "isp",

	[BCM2835_POWER_DOMAIN_USB] = "usb",
	[BCM2835_POWER_DOMAIN_DSI0] = "dsi0",
	[BCM2835_POWER_DOMAIN_DSI1] = "dsi1",
	[BCM2835_POWER_DOMAIN_CAM0] = "cam0",
	[BCM2835_POWER_DOMAIN_CAM1] = "cam1",
	[BCM2835_POWER_DOMAIN_CCP2TX] = "ccp2tx",
	[BCM2835_POWER_DOMAIN_HDMI] = "hdmi",
पूर्ण;

अटल पूर्णांक bcm2835_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_pm *pm = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm2835_घातer *घातer;
	अटल स्थिर काष्ठा अणु
		पूर्णांक parent, child;
	पूर्ण करोमुख्य_deps[] = अणु
		अणु BCM2835_POWER_DOMAIN_GRAFX, BCM2835_POWER_DOMAIN_GRAFX_V3D पूर्ण,
		अणु BCM2835_POWER_DOMAIN_IMAGE, BCM2835_POWER_DOMAIN_IMAGE_PERI पूर्ण,
		अणु BCM2835_POWER_DOMAIN_IMAGE, BCM2835_POWER_DOMAIN_IMAGE_H264 पूर्ण,
		अणु BCM2835_POWER_DOMAIN_IMAGE, BCM2835_POWER_DOMAIN_IMAGE_ISP पूर्ण,
		अणु BCM2835_POWER_DOMAIN_IMAGE_PERI, BCM2835_POWER_DOMAIN_USB पूर्ण,
		अणु BCM2835_POWER_DOMAIN_IMAGE_PERI, BCM2835_POWER_DOMAIN_CAM0 पूर्ण,
		अणु BCM2835_POWER_DOMAIN_IMAGE_PERI, BCM2835_POWER_DOMAIN_CAM1 पूर्ण,
	पूर्ण;
	पूर्णांक ret = 0, i;
	u32 id;

	घातer = devm_kzalloc(dev, माप(*घातer), GFP_KERNEL);
	अगर (!घातer)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, घातer);

	घातer->dev = dev;
	घातer->base = pm->base;
	घातer->asb = pm->asb;

	id = ASB_READ(ASB_AXI_BRDG_ID);
	अगर (id != 0x62726467 /* "BRDG" */) अणु
		dev_err(dev, "ASB register ID returned 0x%08x\n", id);
		वापस -ENODEV;
	पूर्ण

	घातer->pd_xlate.करोमुख्यs = devm_kसुस्मृति(dev,
					       ARRAY_SIZE(घातer_करोमुख्य_names),
					       माप(*घातer->pd_xlate.करोमुख्यs),
					       GFP_KERNEL);
	अगर (!घातer->pd_xlate.करोमुख्यs)
		वापस -ENOMEM;

	घातer->pd_xlate.num_करोमुख्यs = ARRAY_SIZE(घातer_करोमुख्य_names);

	क्रम (i = 0; i < ARRAY_SIZE(घातer_करोमुख्य_names); i++) अणु
		ret = bcm2835_init_घातer_करोमुख्य(घातer, i, घातer_करोमुख्य_names[i]);
		अगर (ret)
			जाओ fail;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(करोमुख्य_deps); i++) अणु
		pm_genpd_add_subकरोमुख्य(&घातer->करोमुख्यs[करोमुख्य_deps[i].parent].base,
				       &घातer->करोमुख्यs[करोमुख्य_deps[i].child].base);
	पूर्ण

	घातer->reset.owner = THIS_MODULE;
	घातer->reset.nr_resets = BCM2835_RESET_COUNT;
	घातer->reset.ops = &bcm2835_reset_ops;
	घातer->reset.of_node = dev->parent->of_node;

	ret = devm_reset_controller_रेजिस्टर(dev, &घातer->reset);
	अगर (ret)
		जाओ fail;

	of_genpd_add_provider_onecell(dev->parent->of_node, &घातer->pd_xlate);

	dev_info(dev, "Broadcom BCM2835 power domains driver");
	वापस 0;

fail:
	क्रम (i = 0; i < ARRAY_SIZE(घातer_करोमुख्य_names); i++) अणु
		काष्ठा generic_pm_करोमुख्य *करोm = &घातer->करोमुख्यs[i].base;

		अगर (करोm->name)
			pm_genpd_हटाओ(करोm);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835_घातer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm2835_घातer_driver = अणु
	.probe		= bcm2835_घातer_probe,
	.हटाओ		= bcm2835_घातer_हटाओ,
	.driver = अणु
		.name =	"bcm2835-power",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm2835_घातer_driver);

MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_DESCRIPTION("Driver for Broadcom BCM2835 PM power domains and reset");
MODULE_LICENSE("GPL");
