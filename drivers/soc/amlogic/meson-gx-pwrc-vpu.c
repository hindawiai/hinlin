<शैली गुरु>
/*
 * Copyright (c) 2017 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * SPDX-License-Identअगरier: GPL-2.0+
 */

#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>

/* AO Offsets */

#घोषणा AO_RTI_GEN_PWR_SLEEP0		(0x3a << 2)

#घोषणा GEN_PWR_VPU_HDMI		BIT(8)
#घोषणा GEN_PWR_VPU_HDMI_ISO		BIT(9)

/* HHI Offsets */

#घोषणा HHI_MEM_PD_REG0			(0x40 << 2)
#घोषणा HHI_VPU_MEM_PD_REG0		(0x41 << 2)
#घोषणा HHI_VPU_MEM_PD_REG1		(0x42 << 2)
#घोषणा HHI_VPU_MEM_PD_REG2		(0x4d << 2)

काष्ठा meson_gx_pwrc_vpu अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	काष्ठा regmap *regmap_ao;
	काष्ठा regmap *regmap_hhi;
	काष्ठा reset_control *rstc;
	काष्ठा clk *vpu_clk;
	काष्ठा clk *vapb_clk;
पूर्ण;

अटल अंतरभूत
काष्ठा meson_gx_pwrc_vpu *genpd_to_pd(काष्ठा generic_pm_करोमुख्य *d)
अणु
	वापस container_of(d, काष्ठा meson_gx_pwrc_vpu, genpd);
पूर्ण

अटल पूर्णांक meson_gx_pwrc_vpu_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा meson_gx_pwrc_vpu *pd = genpd_to_pd(genpd);
	पूर्णांक i;

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI_ISO, GEN_PWR_VPU_HDMI_ISO);
	udelay(20);

	/* Power Down Memories */
	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG0,
				   0x3 << i, 0x3 << i);
		udelay(5);
	पूर्ण
	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG1,
				   0x3 << i, 0x3 << i);
		udelay(5);
	पूर्ण
	क्रम (i = 8; i < 16; i++) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_MEM_PD_REG0,
				   BIT(i), BIT(i));
		udelay(5);
	पूर्ण
	udelay(20);

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI, GEN_PWR_VPU_HDMI);

	msleep(20);

	clk_disable_unprepare(pd->vpu_clk);
	clk_disable_unprepare(pd->vapb_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_g12a_pwrc_vpu_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा meson_gx_pwrc_vpu *pd = genpd_to_pd(genpd);
	पूर्णांक i;

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI_ISO, GEN_PWR_VPU_HDMI_ISO);
	udelay(20);

	/* Power Down Memories */
	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG0,
				   0x3 << i, 0x3 << i);
		udelay(5);
	पूर्ण
	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG1,
				   0x3 << i, 0x3 << i);
		udelay(5);
	पूर्ण
	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG2,
				   0x3 << i, 0x3 << i);
		udelay(5);
	पूर्ण
	क्रम (i = 8; i < 16; i++) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_MEM_PD_REG0,
				   BIT(i), BIT(i));
		udelay(5);
	पूर्ण
	udelay(20);

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI, GEN_PWR_VPU_HDMI);

	msleep(20);

	clk_disable_unprepare(pd->vpu_clk);
	clk_disable_unprepare(pd->vapb_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_gx_pwrc_vpu_setup_clk(काष्ठा meson_gx_pwrc_vpu *pd)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(pd->vpu_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(pd->vapb_clk);
	अगर (ret)
		clk_disable_unprepare(pd->vpu_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_gx_pwrc_vpu_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा meson_gx_pwrc_vpu *pd = genpd_to_pd(genpd);
	पूर्णांक ret;
	पूर्णांक i;

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI, 0);
	udelay(20);

	/* Power Up Memories */
	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG0,
				   0x3 << i, 0);
		udelay(5);
	पूर्ण

	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG1,
				   0x3 << i, 0);
		udelay(5);
	पूर्ण

	क्रम (i = 8; i < 16; i++) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_MEM_PD_REG0,
				   BIT(i), 0);
		udelay(5);
	पूर्ण
	udelay(20);

	ret = reset_control_निश्चित(pd->rstc);
	अगर (ret)
		वापस ret;

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI_ISO, 0);

	ret = reset_control_deनिश्चित(pd->rstc);
	अगर (ret)
		वापस ret;

	ret = meson_gx_pwrc_vpu_setup_clk(pd);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_g12a_pwrc_vpu_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा meson_gx_pwrc_vpu *pd = genpd_to_pd(genpd);
	पूर्णांक ret;
	पूर्णांक i;

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI, 0);
	udelay(20);

	/* Power Up Memories */
	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG0,
				   0x3 << i, 0);
		udelay(5);
	पूर्ण

	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG1,
				   0x3 << i, 0);
		udelay(5);
	पूर्ण

	क्रम (i = 0; i < 32; i += 2) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG2,
				   0x3 << i, 0);
		udelay(5);
	पूर्ण

	क्रम (i = 8; i < 16; i++) अणु
		regmap_update_bits(pd->regmap_hhi, HHI_MEM_PD_REG0,
				   BIT(i), 0);
		udelay(5);
	पूर्ण
	udelay(20);

	ret = reset_control_निश्चित(pd->rstc);
	अगर (ret)
		वापस ret;

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI_ISO, 0);

	ret = reset_control_deनिश्चित(pd->rstc);
	अगर (ret)
		वापस ret;

	ret = meson_gx_pwrc_vpu_setup_clk(pd);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल bool meson_gx_pwrc_vpu_get_घातer(काष्ठा meson_gx_pwrc_vpu *pd)
अणु
	u32 reg;

	regmap_पढ़ो(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0, &reg);

	वापस (reg & GEN_PWR_VPU_HDMI);
पूर्ण

अटल काष्ठा meson_gx_pwrc_vpu vpu_hdmi_pd = अणु
	.genpd = अणु
		.name = "vpu_hdmi",
		.घातer_off = meson_gx_pwrc_vpu_घातer_off,
		.घातer_on = meson_gx_pwrc_vpu_घातer_on,
	पूर्ण,
पूर्ण;

अटल काष्ठा meson_gx_pwrc_vpu vpu_hdmi_pd_g12a = अणु
	.genpd = अणु
		.name = "vpu_hdmi",
		.घातer_off = meson_g12a_pwrc_vpu_घातer_off,
		.घातer_on = meson_g12a_pwrc_vpu_घातer_on,
	पूर्ण,
पूर्ण;

अटल पूर्णांक meson_gx_pwrc_vpu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा meson_gx_pwrc_vpu *vpu_pd_match;
	काष्ठा regmap *regmap_ao, *regmap_hhi;
	काष्ठा meson_gx_pwrc_vpu *vpu_pd;
	काष्ठा reset_control *rstc;
	काष्ठा clk *vpu_clk;
	काष्ठा clk *vapb_clk;
	bool घातered_off;
	पूर्णांक ret;

	vpu_pd_match = of_device_get_match_data(&pdev->dev);
	अगर (!vpu_pd_match) अणु
		dev_err(&pdev->dev, "failed to get match data\n");
		वापस -ENODEV;
	पूर्ण

	vpu_pd = devm_kzalloc(&pdev->dev, माप(*vpu_pd), GFP_KERNEL);
	अगर (!vpu_pd)
		वापस -ENOMEM;

	स_नकल(vpu_pd, vpu_pd_match, माप(*vpu_pd));

	regmap_ao = syscon_node_to_regmap(of_get_parent(pdev->dev.of_node));
	अगर (IS_ERR(regmap_ao)) अणु
		dev_err(&pdev->dev, "failed to get regmap\n");
		वापस PTR_ERR(regmap_ao);
	पूर्ण

	regmap_hhi = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						     "amlogic,hhi-sysctrl");
	अगर (IS_ERR(regmap_hhi)) अणु
		dev_err(&pdev->dev, "failed to get HHI regmap\n");
		वापस PTR_ERR(regmap_hhi);
	पूर्ण

	rstc = devm_reset_control_array_get_exclusive(&pdev->dev);
	अगर (IS_ERR(rstc)) अणु
		अगर (PTR_ERR(rstc) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to get reset lines\n");
		वापस PTR_ERR(rstc);
	पूर्ण

	vpu_clk = devm_clk_get(&pdev->dev, "vpu");
	अगर (IS_ERR(vpu_clk)) अणु
		dev_err(&pdev->dev, "vpu clock request failed\n");
		वापस PTR_ERR(vpu_clk);
	पूर्ण

	vapb_clk = devm_clk_get(&pdev->dev, "vapb");
	अगर (IS_ERR(vapb_clk)) अणु
		dev_err(&pdev->dev, "vapb clock request failed\n");
		वापस PTR_ERR(vapb_clk);
	पूर्ण

	vpu_pd->regmap_ao = regmap_ao;
	vpu_pd->regmap_hhi = regmap_hhi;
	vpu_pd->rstc = rstc;
	vpu_pd->vpu_clk = vpu_clk;
	vpu_pd->vapb_clk = vapb_clk;

	platक्रमm_set_drvdata(pdev, vpu_pd);

	घातered_off = meson_gx_pwrc_vpu_get_घातer(vpu_pd);

	/* If alपढ़ोy घातered, sync the घड़ी states */
	अगर (!घातered_off) अणु
		ret = meson_gx_pwrc_vpu_setup_clk(vpu_pd);
		अगर (ret)
			वापस ret;
	पूर्ण

	vpu_pd->genpd.flags = GENPD_FLAG_ALWAYS_ON;
	pm_genpd_init(&vpu_pd->genpd, शून्य, घातered_off);

	वापस of_genpd_add_provider_simple(pdev->dev.of_node,
					    &vpu_pd->genpd);
पूर्ण

अटल व्योम meson_gx_pwrc_vpu_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_gx_pwrc_vpu *vpu_pd = platक्रमm_get_drvdata(pdev);
	bool घातered_off;

	घातered_off = meson_gx_pwrc_vpu_get_घातer(vpu_pd);
	अगर (!घातered_off)
		vpu_pd->genpd.घातer_off(&vpu_pd->genpd);
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_gx_pwrc_vpu_match_table[] = अणु
	अणु .compatible = "amlogic,meson-gx-pwrc-vpu", .data = &vpu_hdmi_pd पूर्ण,
	अणु
	  .compatible = "amlogic,meson-g12a-pwrc-vpu",
	  .data = &vpu_hdmi_pd_g12a
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_gx_pwrc_vpu_match_table);

अटल काष्ठा platक्रमm_driver meson_gx_pwrc_vpu_driver = अणु
	.probe	= meson_gx_pwrc_vpu_probe,
	.shutकरोwn = meson_gx_pwrc_vpu_shutकरोwn,
	.driver = अणु
		.name		= "meson_gx_pwrc_vpu",
		.of_match_table	= meson_gx_pwrc_vpu_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_gx_pwrc_vpu_driver);
MODULE_LICENSE("GPL v2");
