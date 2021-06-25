<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Linaro.
 * Viresh Kumar <viresh.kumar@linaro.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "cpufreq-dt.h"

/*
 * Machines क्रम which the cpufreq device is *always* created, mostly used क्रम
 * platक्रमms using "operating-points" (V1) property.
 */
अटल स्थिर काष्ठा of_device_id whitelist[] __initस्थिर = अणु
	अणु .compatible = "allwinner,sun4i-a10", पूर्ण,
	अणु .compatible = "allwinner,sun5i-a10s", पूर्ण,
	अणु .compatible = "allwinner,sun5i-a13", पूर्ण,
	अणु .compatible = "allwinner,sun5i-r8", पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31", पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31s", पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20", पूर्ण,
	अणु .compatible = "allwinner,sun8i-a23", पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t", पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3", पूर्ण,

	अणु .compatible = "apm,xgene-shadowcat", पूर्ण,

	अणु .compatible = "arm,integrator-ap", पूर्ण,
	अणु .compatible = "arm,integrator-cp", पूर्ण,

	अणु .compatible = "hisilicon,hi3660", पूर्ण,

	अणु .compatible = "fsl,imx27", पूर्ण,
	अणु .compatible = "fsl,imx51", पूर्ण,
	अणु .compatible = "fsl,imx53", पूर्ण,

	अणु .compatible = "marvell,berlin", पूर्ण,
	अणु .compatible = "marvell,pxa250", पूर्ण,
	अणु .compatible = "marvell,pxa270", पूर्ण,

	अणु .compatible = "samsung,exynos3250", पूर्ण,
	अणु .compatible = "samsung,exynos4210", पूर्ण,
	अणु .compatible = "samsung,exynos5250", पूर्ण,
#अगर_अघोषित CONFIG_BL_SWITCHER
	अणु .compatible = "samsung,exynos5800", पूर्ण,
#पूर्ण_अगर

	अणु .compatible = "renesas,emev2", पूर्ण,
	अणु .compatible = "renesas,r7s72100", पूर्ण,
	अणु .compatible = "renesas,r8a73a4", पूर्ण,
	अणु .compatible = "renesas,r8a7740", पूर्ण,
	अणु .compatible = "renesas,r8a7742", पूर्ण,
	अणु .compatible = "renesas,r8a7743", पूर्ण,
	अणु .compatible = "renesas,r8a7744", पूर्ण,
	अणु .compatible = "renesas,r8a7745", पूर्ण,
	अणु .compatible = "renesas,r8a7778", पूर्ण,
	अणु .compatible = "renesas,r8a7779", पूर्ण,
	अणु .compatible = "renesas,r8a7790", पूर्ण,
	अणु .compatible = "renesas,r8a7791", पूर्ण,
	अणु .compatible = "renesas,r8a7792", पूर्ण,
	अणु .compatible = "renesas,r8a7793", पूर्ण,
	अणु .compatible = "renesas,r8a7794", पूर्ण,
	अणु .compatible = "renesas,sh73a0", पूर्ण,

	अणु .compatible = "rockchip,rk2928", पूर्ण,
	अणु .compatible = "rockchip,rk3036", पूर्ण,
	अणु .compatible = "rockchip,rk3066a", पूर्ण,
	अणु .compatible = "rockchip,rk3066b", पूर्ण,
	अणु .compatible = "rockchip,rk3188", पूर्ण,
	अणु .compatible = "rockchip,rk3228", पूर्ण,
	अणु .compatible = "rockchip,rk3288", पूर्ण,
	अणु .compatible = "rockchip,rk3328", पूर्ण,
	अणु .compatible = "rockchip,rk3366", पूर्ण,
	अणु .compatible = "rockchip,rk3368", पूर्ण,
	अणु .compatible = "rockchip,rk3399",
	  .data = &(काष्ठा cpufreq_dt_platक्रमm_data)
		अणु .have_governor_per_policy = true, पूर्ण,
	पूर्ण,

	अणु .compatible = "st-ericsson,u8500", पूर्ण,
	अणु .compatible = "st-ericsson,u8540", पूर्ण,
	अणु .compatible = "st-ericsson,u9500", पूर्ण,
	अणु .compatible = "st-ericsson,u9540", पूर्ण,

	अणु .compatible = "ti,omap2", पूर्ण,
	अणु .compatible = "ti,omap4", पूर्ण,
	अणु .compatible = "ti,omap5", पूर्ण,

	अणु .compatible = "xlnx,zynq-7000", पूर्ण,
	अणु .compatible = "xlnx,zynqmp", पूर्ण,

	अणु पूर्ण
पूर्ण;

/*
 * Machines क्रम which the cpufreq device is *not* created, mostly used क्रम
 * platक्रमms using "operating-points-v2" property.
 */
अटल स्थिर काष्ठा of_device_id blacklist[] __initस्थिर = अणु
	अणु .compatible = "allwinner,sun50i-h6", पूर्ण,

	अणु .compatible = "arm,vexpress", पूर्ण,

	अणु .compatible = "calxeda,highbank", पूर्ण,
	अणु .compatible = "calxeda,ecx-2000", पूर्ण,

	अणु .compatible = "fsl,imx7ulp", पूर्ण,
	अणु .compatible = "fsl,imx7d", पूर्ण,
	अणु .compatible = "fsl,imx8mq", पूर्ण,
	अणु .compatible = "fsl,imx8mm", पूर्ण,
	अणु .compatible = "fsl,imx8mn", पूर्ण,
	अणु .compatible = "fsl,imx8mp", पूर्ण,

	अणु .compatible = "marvell,armadaxp", पूर्ण,

	अणु .compatible = "mediatek,mt2701", पूर्ण,
	अणु .compatible = "mediatek,mt2712", पूर्ण,
	अणु .compatible = "mediatek,mt7622", पूर्ण,
	अणु .compatible = "mediatek,mt7623", पूर्ण,
	अणु .compatible = "mediatek,mt8167", पूर्ण,
	अणु .compatible = "mediatek,mt817x", पूर्ण,
	अणु .compatible = "mediatek,mt8173", पूर्ण,
	अणु .compatible = "mediatek,mt8176", पूर्ण,
	अणु .compatible = "mediatek,mt8183", पूर्ण,
	अणु .compatible = "mediatek,mt8516", पूर्ण,

	अणु .compatible = "nvidia,tegra20", पूर्ण,
	अणु .compatible = "nvidia,tegra30", पूर्ण,
	अणु .compatible = "nvidia,tegra124", पूर्ण,
	अणु .compatible = "nvidia,tegra210", पूर्ण,

	अणु .compatible = "qcom,apq8096", पूर्ण,
	अणु .compatible = "qcom,msm8996", पूर्ण,
	अणु .compatible = "qcom,qcs404", पूर्ण,
	अणु .compatible = "qcom,sc7180", पूर्ण,
	अणु .compatible = "qcom,sdm845", पूर्ण,

	अणु .compatible = "st,stih407", पूर्ण,
	अणु .compatible = "st,stih410", पूर्ण,
	अणु .compatible = "st,stih418", पूर्ण,

	अणु .compatible = "ti,am33xx", पूर्ण,
	अणु .compatible = "ti,am43", पूर्ण,
	अणु .compatible = "ti,dra7", पूर्ण,
	अणु .compatible = "ti,omap3", पूर्ण,

	अणु .compatible = "qcom,ipq8064", पूर्ण,
	अणु .compatible = "qcom,apq8064", पूर्ण,
	अणु .compatible = "qcom,msm8974", पूर्ण,
	अणु .compatible = "qcom,msm8960", पूर्ण,

	अणु पूर्ण
पूर्ण;

अटल bool __init cpu0_node_has_opp_v2_prop(व्योम)
अणु
	काष्ठा device_node *np = of_cpu_device_node_get(0);
	bool ret = false;

	अगर (of_get_property(np, "operating-points-v2", शून्य))
		ret = true;

	of_node_put(np);
	वापस ret;
पूर्ण

अटल पूर्णांक __init cpufreq_dt_platdev_init(व्योम)
अणु
	काष्ठा device_node *np = of_find_node_by_path("/");
	स्थिर काष्ठा of_device_id *match;
	स्थिर व्योम *data = शून्य;

	अगर (!np)
		वापस -ENODEV;

	match = of_match_node(whitelist, np);
	अगर (match) अणु
		data = match->data;
		जाओ create_pdev;
	पूर्ण

	अगर (cpu0_node_has_opp_v2_prop() && !of_match_node(blacklist, np))
		जाओ create_pdev;

	of_node_put(np);
	वापस -ENODEV;

create_pdev:
	of_node_put(np);
	वापस PTR_ERR_OR_ZERO(platक्रमm_device_रेजिस्टर_data(शून्य, "cpufreq-dt",
			       -1, data,
			       माप(काष्ठा cpufreq_dt_platक्रमm_data)));
पूर्ण
core_initcall(cpufreq_dt_platdev_init);
