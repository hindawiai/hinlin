<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Samsung Electronics Co.Ltd
 * Authors:
 *	Hyungwon Hwang <human.hwang@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "exynos_drm_drv.h"

/* Sysreg रेजिस्टरs क्रम MIC */
#घोषणा DSD_CFG_MUX	0x1004
#घोषणा MIC0_RGB_MUX	(1 << 0)
#घोषणा MIC0_I80_MUX	(1 << 1)
#घोषणा MIC0_ON_MUX	(1 << 5)

/* MIC रेजिस्टरs */
#घोषणा MIC_OP				0x0
#घोषणा MIC_IP_VER			0x0004
#घोषणा MIC_V_TIMING_0			0x0008
#घोषणा MIC_V_TIMING_1			0x000C
#घोषणा MIC_IMG_SIZE			0x0010
#घोषणा MIC_INPUT_TIMING_0		0x0014
#घोषणा MIC_INPUT_TIMING_1		0x0018
#घोषणा MIC_2D_OUTPUT_TIMING_0		0x001C
#घोषणा MIC_2D_OUTPUT_TIMING_1		0x0020
#घोषणा MIC_2D_OUTPUT_TIMING_2		0x0024
#घोषणा MIC_3D_OUTPUT_TIMING_0		0x0028
#घोषणा MIC_3D_OUTPUT_TIMING_1		0x002C
#घोषणा MIC_3D_OUTPUT_TIMING_2		0x0030
#घोषणा MIC_CORE_PARA_0			0x0034
#घोषणा MIC_CORE_PARA_1			0x0038
#घोषणा MIC_CTC_CTRL			0x0040
#घोषणा MIC_RD_DATA			0x0044

#घोषणा MIC_UPD_REG			(1 << 31)
#घोषणा MIC_ON_REG			(1 << 30)
#घोषणा MIC_TD_ON_REG			(1 << 29)
#घोषणा MIC_BS_CHG_OUT			(1 << 16)
#घोषणा MIC_VIDEO_TYPE(x)		(((x) & 0xf) << 12)
#घोषणा MIC_PSR_EN			(1 << 5)
#घोषणा MIC_SW_RST			(1 << 4)
#घोषणा MIC_ALL_RST			(1 << 3)
#घोषणा MIC_CORE_VER_CONTROL		(1 << 2)
#घोषणा MIC_MODE_SEL_COMMAND_MODE	(1 << 1)
#घोषणा MIC_MODE_SEL_MASK		(1 << 1)
#घोषणा MIC_CORE_EN			(1 << 0)

#घोषणा MIC_V_PULSE_WIDTH(x)		(((x) & 0x3fff) << 16)
#घोषणा MIC_V_PERIOD_LINE(x)		((x) & 0x3fff)

#घोषणा MIC_VBP_SIZE(x)			(((x) & 0x3fff) << 16)
#घोषणा MIC_VFP_SIZE(x)			((x) & 0x3fff)

#घोषणा MIC_IMG_V_SIZE(x)		(((x) & 0x3fff) << 16)
#घोषणा MIC_IMG_H_SIZE(x)		((x) & 0x3fff)

#घोषणा MIC_H_PULSE_WIDTH_IN(x)		(((x) & 0x3fff) << 16)
#घोषणा MIC_H_PERIOD_PIXEL_IN(x)	((x) & 0x3fff)

#घोषणा MIC_HBP_SIZE_IN(x)		(((x) & 0x3fff) << 16)
#घोषणा MIC_HFP_SIZE_IN(x)		((x) & 0x3fff)

#घोषणा MIC_H_PULSE_WIDTH_2D(x)		(((x) & 0x3fff) << 16)
#घोषणा MIC_H_PERIOD_PIXEL_2D(x)	((x) & 0x3fff)

#घोषणा MIC_HBP_SIZE_2D(x)		(((x) & 0x3fff) << 16)
#घोषणा MIC_HFP_SIZE_2D(x)		((x) & 0x3fff)

#घोषणा MIC_BS_SIZE_2D(x)	((x) & 0x3fff)

अटल स्थिर अक्षर *स्थिर clk_names[] = अणु "pclk_mic0", "sclk_rgb_vclk_to_mic0" पूर्ण;
#घोषणा NUM_CLKS		ARRAY_SIZE(clk_names)
अटल DEFINE_MUTEX(mic_mutex);

काष्ठा exynos_mic अणु
	काष्ठा device *dev;
	व्योम __iomem *reg;
	काष्ठा regmap *sysreg;
	काष्ठा clk *clks[NUM_CLKS];

	bool i80_mode;
	काष्ठा videomode vm;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge bridge;

	bool enabled;
पूर्ण;

अटल व्योम mic_set_path(काष्ठा exynos_mic *mic, bool enable)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(mic->sysreg, DSD_CFG_MUX, &val);
	अगर (ret) अणु
		DRM_DEV_ERROR(mic->dev,
			      "mic: Failed to read system register\n");
		वापस;
	पूर्ण

	अगर (enable) अणु
		अगर (mic->i80_mode)
			val |= MIC0_I80_MUX;
		अन्यथा
			val |= MIC0_RGB_MUX;

		val |=  MIC0_ON_MUX;
	पूर्ण अन्यथा
		val &= ~(MIC0_RGB_MUX | MIC0_I80_MUX | MIC0_ON_MUX);

	ret = regmap_ग_लिखो(mic->sysreg, DSD_CFG_MUX, val);
	अगर (ret)
		DRM_DEV_ERROR(mic->dev,
			      "mic: Failed to read system register\n");
पूर्ण

अटल पूर्णांक mic_sw_reset(काष्ठा exynos_mic *mic)
अणु
	अचिन्हित पूर्णांक retry = 100;
	पूर्णांक ret;

	ग_लिखोl(MIC_SW_RST, mic->reg + MIC_OP);

	जबतक (retry-- > 0) अणु
		ret = पढ़ोl(mic->reg + MIC_OP);
		अगर (!(ret & MIC_SW_RST))
			वापस 0;

		udelay(10);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम mic_set_porch_timing(काष्ठा exynos_mic *mic)
अणु
	काष्ठा videomode vm = mic->vm;
	u32 reg;

	reg = MIC_V_PULSE_WIDTH(vm.vsync_len) +
		MIC_V_PERIOD_LINE(vm.vsync_len + vm.vactive +
				vm.vback_porch + vm.vfront_porch);
	ग_लिखोl(reg, mic->reg + MIC_V_TIMING_0);

	reg = MIC_VBP_SIZE(vm.vback_porch) +
		MIC_VFP_SIZE(vm.vfront_porch);
	ग_लिखोl(reg, mic->reg + MIC_V_TIMING_1);

	reg = MIC_V_PULSE_WIDTH(vm.hsync_len) +
		MIC_V_PERIOD_LINE(vm.hsync_len + vm.hactive +
				vm.hback_porch + vm.hfront_porch);
	ग_लिखोl(reg, mic->reg + MIC_INPUT_TIMING_0);

	reg = MIC_VBP_SIZE(vm.hback_porch) +
		MIC_VFP_SIZE(vm.hfront_porch);
	ग_लिखोl(reg, mic->reg + MIC_INPUT_TIMING_1);
पूर्ण

अटल व्योम mic_set_img_size(काष्ठा exynos_mic *mic)
अणु
	काष्ठा videomode *vm = &mic->vm;
	u32 reg;

	reg = MIC_IMG_H_SIZE(vm->hactive) +
		MIC_IMG_V_SIZE(vm->vactive);

	ग_लिखोl(reg, mic->reg + MIC_IMG_SIZE);
पूर्ण

अटल व्योम mic_set_output_timing(काष्ठा exynos_mic *mic)
अणु
	काष्ठा videomode vm = mic->vm;
	u32 reg, bs_size_2d;

	DRM_DEV_DEBUG(mic->dev, "w: %u, h: %u\n", vm.hactive, vm.vactive);
	bs_size_2d = ((vm.hactive >> 2) << 1) + (vm.vactive % 4);
	reg = MIC_BS_SIZE_2D(bs_size_2d);
	ग_लिखोl(reg, mic->reg + MIC_2D_OUTPUT_TIMING_2);

	अगर (!mic->i80_mode) अणु
		reg = MIC_H_PULSE_WIDTH_2D(vm.hsync_len) +
			MIC_H_PERIOD_PIXEL_2D(vm.hsync_len + bs_size_2d +
					vm.hback_porch + vm.hfront_porch);
		ग_लिखोl(reg, mic->reg + MIC_2D_OUTPUT_TIMING_0);

		reg = MIC_HBP_SIZE_2D(vm.hback_porch) +
			MIC_H_PERIOD_PIXEL_2D(vm.hfront_porch);
		ग_लिखोl(reg, mic->reg + MIC_2D_OUTPUT_TIMING_1);
	पूर्ण
पूर्ण

अटल व्योम mic_set_reg_on(काष्ठा exynos_mic *mic, bool enable)
अणु
	u32 reg = पढ़ोl(mic->reg + MIC_OP);

	अगर (enable) अणु
		reg &= ~(MIC_MODE_SEL_MASK | MIC_CORE_VER_CONTROL | MIC_PSR_EN);
		reg |= (MIC_CORE_EN | MIC_BS_CHG_OUT | MIC_ON_REG);

		reg  &= ~MIC_MODE_SEL_COMMAND_MODE;
		अगर (mic->i80_mode)
			reg |= MIC_MODE_SEL_COMMAND_MODE;
	पूर्ण अन्यथा अणु
		reg &= ~MIC_CORE_EN;
	पूर्ण

	reg |= MIC_UPD_REG;
	ग_लिखोl(reg, mic->reg + MIC_OP);
पूर्ण

अटल व्योम mic_disable(काष्ठा drm_bridge *bridge) अणु पूर्ण

अटल व्योम mic_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा exynos_mic *mic = bridge->driver_निजी;

	mutex_lock(&mic_mutex);
	अगर (!mic->enabled)
		जाओ alपढ़ोy_disabled;

	mic_set_path(mic, 0);

	pm_runसमय_put(mic->dev);
	mic->enabled = 0;

alपढ़ोy_disabled:
	mutex_unlock(&mic_mutex);
पूर्ण

अटल व्योम mic_mode_set(काष्ठा drm_bridge *bridge,
			 स्थिर काष्ठा drm_display_mode *mode,
			 स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा exynos_mic *mic = bridge->driver_निजी;

	mutex_lock(&mic_mutex);
	drm_display_mode_to_videomode(mode, &mic->vm);
	mic->i80_mode = to_exynos_crtc(bridge->encoder->crtc)->i80_mode;
	mutex_unlock(&mic_mutex);
पूर्ण

अटल व्योम mic_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा exynos_mic *mic = bridge->driver_निजी;
	पूर्णांक ret;

	mutex_lock(&mic_mutex);
	अगर (mic->enabled)
		जाओ unlock;

	ret = pm_runसमय_get_sync(mic->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(mic->dev);
		जाओ unlock;
	पूर्ण

	mic_set_path(mic, 1);

	ret = mic_sw_reset(mic);
	अगर (ret) अणु
		DRM_DEV_ERROR(mic->dev, "Failed to reset\n");
		जाओ turn_off;
	पूर्ण

	अगर (!mic->i80_mode)
		mic_set_porch_timing(mic);
	mic_set_img_size(mic);
	mic_set_output_timing(mic);
	mic_set_reg_on(mic, 1);
	mic->enabled = 1;
	mutex_unlock(&mic_mutex);

	वापस;

turn_off:
	pm_runसमय_put(mic->dev);
unlock:
	mutex_unlock(&mic_mutex);
पूर्ण

अटल व्योम mic_enable(काष्ठा drm_bridge *bridge) अणु पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs mic_bridge_funcs = अणु
	.disable = mic_disable,
	.post_disable = mic_post_disable,
	.mode_set = mic_mode_set,
	.pre_enable = mic_pre_enable,
	.enable = mic_enable,
पूर्ण;

अटल पूर्णांक exynos_mic_bind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा exynos_mic *mic = dev_get_drvdata(dev);

	mic->bridge.driver_निजी = mic;

	वापस 0;
पूर्ण

अटल व्योम exynos_mic_unbind(काष्ठा device *dev, काष्ठा device *master,
			      व्योम *data)
अणु
	काष्ठा exynos_mic *mic = dev_get_drvdata(dev);

	mutex_lock(&mic_mutex);
	अगर (!mic->enabled)
		जाओ alपढ़ोy_disabled;

	pm_runसमय_put(mic->dev);

alपढ़ोy_disabled:
	mutex_unlock(&mic_mutex);
पूर्ण

अटल स्थिर काष्ठा component_ops exynos_mic_component_ops = अणु
	.bind	= exynos_mic_bind,
	.unbind	= exynos_mic_unbind,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक exynos_mic_suspend(काष्ठा device *dev)
अणु
	काष्ठा exynos_mic *mic = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = NUM_CLKS - 1; i > -1; i--)
		clk_disable_unprepare(mic->clks[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_mic_resume(काष्ठा device *dev)
अणु
	काष्ठा exynos_mic *mic = dev_get_drvdata(dev);
	पूर्णांक ret, i;

	क्रम (i = 0; i < NUM_CLKS; i++) अणु
		ret = clk_prepare_enable(mic->clks[i]);
		अगर (ret < 0) अणु
			DRM_DEV_ERROR(dev, "Failed to enable clock (%s)\n",
				      clk_names[i]);
			जबतक (--i > -1)
				clk_disable_unprepare(mic->clks[i]);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops exynos_mic_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos_mic_suspend, exynos_mic_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल पूर्णांक exynos_mic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा exynos_mic *mic;
	काष्ठा resource res;
	पूर्णांक ret, i;

	mic = devm_kzalloc(dev, माप(*mic), GFP_KERNEL);
	अगर (!mic) अणु
		DRM_DEV_ERROR(dev,
			      "mic: Failed to allocate memory for MIC object\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	mic->dev = dev;

	ret = of_address_to_resource(dev->of_node, 0, &res);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "mic: Failed to get mem region for MIC\n");
		जाओ err;
	पूर्ण
	mic->reg = devm_ioremap(dev, res.start, resource_size(&res));
	अगर (!mic->reg) अणु
		DRM_DEV_ERROR(dev, "mic: Failed to remap for MIC\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	mic->sysreg = syscon_regmap_lookup_by_phandle(dev->of_node,
							"samsung,disp-syscon");
	अगर (IS_ERR(mic->sysreg)) अणु
		DRM_DEV_ERROR(dev, "mic: Failed to get system register.\n");
		ret = PTR_ERR(mic->sysreg);
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < NUM_CLKS; i++) अणु
		mic->clks[i] = devm_clk_get(dev, clk_names[i]);
		अगर (IS_ERR(mic->clks[i])) अणु
			DRM_DEV_ERROR(dev, "mic: Failed to get clock (%s)\n",
				      clk_names[i]);
			ret = PTR_ERR(mic->clks[i]);
			जाओ err;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, mic);

	mic->bridge.funcs = &mic_bridge_funcs;
	mic->bridge.of_node = dev->of_node;

	drm_bridge_add(&mic->bridge);

	pm_runसमय_enable(dev);

	ret = component_add(dev, &exynos_mic_component_ops);
	अगर (ret)
		जाओ err_pm;

	DRM_DEV_DEBUG_KMS(dev, "MIC has been probed\n");

	वापस 0;

err_pm:
	pm_runसमय_disable(dev);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक exynos_mic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_mic *mic = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &exynos_mic_component_ops);
	pm_runसमय_disable(&pdev->dev);

	drm_bridge_हटाओ(&mic->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id exynos_mic_of_match[] = अणु
	अणु .compatible = "samsung,exynos5433-mic" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_mic_of_match);

काष्ठा platक्रमm_driver mic_driver = अणु
	.probe		= exynos_mic_probe,
	.हटाओ		= exynos_mic_हटाओ,
	.driver		= अणु
		.name	= "exynos-mic",
		.pm	= &exynos_mic_pm_ops,
		.owner	= THIS_MODULE,
		.of_match_table = exynos_mic_of_match,
	पूर्ण,
पूर्ण;
