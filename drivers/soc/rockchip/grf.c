<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip Generic Register Files setup
 *
 * Copyright (c) 2016 Heiko Stuebner <heiko@sntech.de>
 */

#समावेश <linux/err.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा HIWORD_UPDATE(val, mask, shअगरt) \
		((val) << (shअगरt) | (mask) << ((shअगरt) + 16))

काष्ठा rockchip_grf_value अणु
	स्थिर अक्षर *desc;
	u32 reg;
	u32 val;
पूर्ण;

काष्ठा rockchip_grf_info अणु
	स्थिर काष्ठा rockchip_grf_value *values;
	पूर्णांक num_values;
पूर्ण;

#घोषणा RK3036_GRF_SOC_CON0		0x140

अटल स्थिर काष्ठा rockchip_grf_value rk3036_शेषs[] __initस्थिर = अणु
	/*
	 * Disable स्वतः jtag/sdmmc चयनing that causes issues with the
	 * घड़ी-framework and the mmc controllers making them unreliable.
	 */
	अणु "jtag switching", RK3036_GRF_SOC_CON0, HIWORD_UPDATE(0, 1, 11) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_grf_info rk3036_grf __initस्थिर = अणु
	.values = rk3036_शेषs,
	.num_values = ARRAY_SIZE(rk3036_शेषs),
पूर्ण;

#घोषणा RK3128_GRF_SOC_CON0		0x140

अटल स्थिर काष्ठा rockchip_grf_value rk3128_शेषs[] __initस्थिर = अणु
	अणु "jtag switching", RK3128_GRF_SOC_CON0, HIWORD_UPDATE(0, 1, 8) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_grf_info rk3128_grf __initस्थिर = अणु
	.values = rk3128_शेषs,
	.num_values = ARRAY_SIZE(rk3128_शेषs),
पूर्ण;

#घोषणा RK3228_GRF_SOC_CON6		0x418

अटल स्थिर काष्ठा rockchip_grf_value rk3228_शेषs[] __initस्थिर = अणु
	अणु "jtag switching", RK3228_GRF_SOC_CON6, HIWORD_UPDATE(0, 1, 8) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_grf_info rk3228_grf __initस्थिर = अणु
	.values = rk3228_शेषs,
	.num_values = ARRAY_SIZE(rk3228_शेषs),
पूर्ण;

#घोषणा RK3288_GRF_SOC_CON0		0x244
#घोषणा RK3288_GRF_SOC_CON2		0x24c

अटल स्थिर काष्ठा rockchip_grf_value rk3288_शेषs[] __initस्थिर = अणु
	अणु "jtag switching", RK3288_GRF_SOC_CON0, HIWORD_UPDATE(0, 1, 12) पूर्ण,
	अणु "pwm select", RK3288_GRF_SOC_CON2, HIWORD_UPDATE(1, 1, 0) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_grf_info rk3288_grf __initस्थिर = अणु
	.values = rk3288_शेषs,
	.num_values = ARRAY_SIZE(rk3288_शेषs),
पूर्ण;

#घोषणा RK3328_GRF_SOC_CON4		0x410

अटल स्थिर काष्ठा rockchip_grf_value rk3328_शेषs[] __initस्थिर = अणु
	अणु "jtag switching", RK3328_GRF_SOC_CON4, HIWORD_UPDATE(0, 1, 12) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_grf_info rk3328_grf __initस्थिर = अणु
	.values = rk3328_शेषs,
	.num_values = ARRAY_SIZE(rk3328_शेषs),
पूर्ण;

#घोषणा RK3368_GRF_SOC_CON15		0x43c

अटल स्थिर काष्ठा rockchip_grf_value rk3368_शेषs[] __initस्थिर = अणु
	अणु "jtag switching", RK3368_GRF_SOC_CON15, HIWORD_UPDATE(0, 1, 13) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_grf_info rk3368_grf __initस्थिर = अणु
	.values = rk3368_शेषs,
	.num_values = ARRAY_SIZE(rk3368_शेषs),
पूर्ण;

#घोषणा RK3399_GRF_SOC_CON7		0xe21c

अटल स्थिर काष्ठा rockchip_grf_value rk3399_शेषs[] __initस्थिर = अणु
	अणु "jtag switching", RK3399_GRF_SOC_CON7, HIWORD_UPDATE(0, 1, 12) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_grf_info rk3399_grf __initस्थिर = अणु
	.values = rk3399_शेषs,
	.num_values = ARRAY_SIZE(rk3399_शेषs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_grf_dt_match[] __initस्थिर = अणु
	अणु
		.compatible = "rockchip,rk3036-grf",
		.data = (व्योम *)&rk3036_grf,
	पूर्ण, अणु
		.compatible = "rockchip,rk3128-grf",
		.data = (व्योम *)&rk3128_grf,
	पूर्ण, अणु
		.compatible = "rockchip,rk3228-grf",
		.data = (व्योम *)&rk3228_grf,
	पूर्ण, अणु
		.compatible = "rockchip,rk3288-grf",
		.data = (व्योम *)&rk3288_grf,
	पूर्ण, अणु
		.compatible = "rockchip,rk3328-grf",
		.data = (व्योम *)&rk3328_grf,
	पूर्ण, अणु
		.compatible = "rockchip,rk3368-grf",
		.data = (व्योम *)&rk3368_grf,
	पूर्ण, अणु
		.compatible = "rockchip,rk3399-grf",
		.data = (व्योम *)&rk3399_grf,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक __init rockchip_grf_init(व्योम)
अणु
	स्थिर काष्ठा rockchip_grf_info *grf_info;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;
	काष्ठा regmap *grf;
	पूर्णांक ret, i;

	np = of_find_matching_node_and_match(शून्य, rockchip_grf_dt_match,
					     &match);
	अगर (!np)
		वापस -ENODEV;
	अगर (!match || !match->data) अणु
		pr_err("%s: missing grf data\n", __func__);
		वापस -EINVAL;
	पूर्ण

	grf_info = match->data;

	grf = syscon_node_to_regmap(np);
	अगर (IS_ERR(grf)) अणु
		pr_err("%s: could not get grf syscon\n", __func__);
		वापस PTR_ERR(grf);
	पूर्ण

	क्रम (i = 0; i < grf_info->num_values; i++) अणु
		स्थिर काष्ठा rockchip_grf_value *val = &grf_info->values[i];

		pr_debug("%s: adjusting %s in %#6x to %#10x\n", __func__,
			val->desc, val->reg, val->val);
		ret = regmap_ग_लिखो(grf, val->reg, val->val);
		अगर (ret < 0)
			pr_err("%s: write to %#6x failed with %d\n",
			       __func__, val->reg, ret);
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(rockchip_grf_init);
