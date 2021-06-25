<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2019 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/reset.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <dt-bindings/घातer/meson8-घातer.h>
#समावेश <dt-bindings/घातer/meson-axg-घातer.h>
#समावेश <dt-bindings/घातer/meson-g12a-घातer.h>
#समावेश <dt-bindings/घातer/meson-gxbb-घातer.h>
#समावेश <dt-bindings/घातer/meson-sm1-घातer.h>

/* AO Offsets */

#घोषणा GX_AO_RTI_GEN_PWR_SLEEP0	(0x3a << 2)
#घोषणा GX_AO_RTI_GEN_PWR_ISO0		(0x3b << 2)

/*
 * Meson8/Meson8b/Meson8m2 only expose the घातer management रेजिस्टरs of the
 * AO-bus as syscon. 0x3a from GX translates to 0x02, 0x3b translates to 0x03
 * and so on.
 */
#घोषणा MESON8_AO_RTI_GEN_PWR_SLEEP0	(0x02 << 2)
#घोषणा MESON8_AO_RTI_GEN_PWR_ISO0	(0x03 << 2)

/* HHI Offsets */

#घोषणा HHI_MEM_PD_REG0			(0x40 << 2)
#घोषणा HHI_VPU_MEM_PD_REG0		(0x41 << 2)
#घोषणा HHI_VPU_MEM_PD_REG1		(0x42 << 2)
#घोषणा HHI_VPU_MEM_PD_REG3		(0x43 << 2)
#घोषणा HHI_VPU_MEM_PD_REG4		(0x44 << 2)
#घोषणा HHI_AUDIO_MEM_PD_REG0		(0x45 << 2)
#घोषणा HHI_न_अंकOQ_MEM_PD_REG0		(0x46 << 2)
#घोषणा HHI_न_अंकOQ_MEM_PD_REG1		(0x47 << 2)
#घोषणा HHI_VPU_MEM_PD_REG2		(0x4d << 2)

काष्ठा meson_ee_pwrc;
काष्ठा meson_ee_pwrc_करोमुख्य;

काष्ठा meson_ee_pwrc_mem_करोमुख्य अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक mask;
पूर्ण;

काष्ठा meson_ee_pwrc_top_करोमुख्य अणु
	अचिन्हित पूर्णांक sleep_reg;
	अचिन्हित पूर्णांक sleep_mask;
	अचिन्हित पूर्णांक iso_reg;
	अचिन्हित पूर्णांक iso_mask;
पूर्ण;

काष्ठा meson_ee_pwrc_करोमुख्य_desc अणु
	अक्षर *name;
	अचिन्हित पूर्णांक reset_names_count;
	अचिन्हित पूर्णांक clk_names_count;
	काष्ठा meson_ee_pwrc_top_करोमुख्य *top_pd;
	अचिन्हित पूर्णांक mem_pd_count;
	काष्ठा meson_ee_pwrc_mem_करोमुख्य *mem_pd;
	bool (*get_घातer)(काष्ठा meson_ee_pwrc_करोमुख्य *pwrc_करोमुख्य);
पूर्ण;

काष्ठा meson_ee_pwrc_करोमुख्य_data अणु
	अचिन्हित पूर्णांक count;
	काष्ठा meson_ee_pwrc_करोमुख्य_desc *करोमुख्यs;
पूर्ण;

/* TOP Power Doमुख्यs */

अटल काष्ठा meson_ee_pwrc_top_करोमुख्य gx_pwrc_vpu = अणु
	.sleep_reg = GX_AO_RTI_GEN_PWR_SLEEP0,
	.sleep_mask = BIT(8),
	.iso_reg = GX_AO_RTI_GEN_PWR_SLEEP0,
	.iso_mask = BIT(9),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_top_करोमुख्य meson8_pwrc_vpu = अणु
	.sleep_reg = MESON8_AO_RTI_GEN_PWR_SLEEP0,
	.sleep_mask = BIT(8),
	.iso_reg = MESON8_AO_RTI_GEN_PWR_SLEEP0,
	.iso_mask = BIT(9),
पूर्ण;

#घोषणा SM1_EE_PD(__bit)					\
	अणु							\
		.sleep_reg = GX_AO_RTI_GEN_PWR_SLEEP0, 		\
		.sleep_mask = BIT(__bit), 			\
		.iso_reg = GX_AO_RTI_GEN_PWR_ISO0, 		\
		.iso_mask = BIT(__bit), 			\
	पूर्ण

अटल काष्ठा meson_ee_pwrc_top_करोमुख्य sm1_pwrc_vpu = SM1_EE_PD(8);
अटल काष्ठा meson_ee_pwrc_top_करोमुख्य sm1_pwrc_nna = SM1_EE_PD(16);
अटल काष्ठा meson_ee_pwrc_top_करोमुख्य sm1_pwrc_usb = SM1_EE_PD(17);
अटल काष्ठा meson_ee_pwrc_top_करोमुख्य sm1_pwrc_pci = SM1_EE_PD(18);
अटल काष्ठा meson_ee_pwrc_top_करोमुख्य sm1_pwrc_ge2d = SM1_EE_PD(19);

/* Memory PD Doमुख्यs */

#घोषणा VPU_MEMPD(__reg)					\
	अणु __reg, GENMASK(1, 0) पूर्ण,				\
	अणु __reg, GENMASK(3, 2) पूर्ण,				\
	अणु __reg, GENMASK(5, 4) पूर्ण,				\
	अणु __reg, GENMASK(7, 6) पूर्ण,				\
	अणु __reg, GENMASK(9, 8) पूर्ण,				\
	अणु __reg, GENMASK(11, 10) पूर्ण,				\
	अणु __reg, GENMASK(13, 12) पूर्ण,				\
	अणु __reg, GENMASK(15, 14) पूर्ण,				\
	अणु __reg, GENMASK(17, 16) पूर्ण,				\
	अणु __reg, GENMASK(19, 18) पूर्ण,				\
	अणु __reg, GENMASK(21, 20) पूर्ण,				\
	अणु __reg, GENMASK(23, 22) पूर्ण,				\
	अणु __reg, GENMASK(25, 24) पूर्ण,				\
	अणु __reg, GENMASK(27, 26) पूर्ण,				\
	अणु __reg, GENMASK(29, 28) पूर्ण,				\
	अणु __reg, GENMASK(31, 30) पूर्ण

#घोषणा VPU_HHI_MEMPD(__reg)					\
	अणु __reg, BIT(8) पूर्ण,					\
	अणु __reg, BIT(9) पूर्ण,					\
	अणु __reg, BIT(10) पूर्ण,					\
	अणु __reg, BIT(11) पूर्ण,					\
	अणु __reg, BIT(12) पूर्ण,					\
	अणु __reg, BIT(13) पूर्ण,					\
	अणु __reg, BIT(14) पूर्ण,					\
	अणु __reg, BIT(15) पूर्ण

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य axg_pwrc_mem_vpu[] = अणु
	VPU_MEMPD(HHI_VPU_MEM_PD_REG0),
	VPU_HHI_MEMPD(HHI_MEM_PD_REG0),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य g12a_pwrc_mem_vpu[] = अणु
	VPU_MEMPD(HHI_VPU_MEM_PD_REG0),
	VPU_MEMPD(HHI_VPU_MEM_PD_REG1),
	VPU_MEMPD(HHI_VPU_MEM_PD_REG2),
	VPU_HHI_MEMPD(HHI_MEM_PD_REG0),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य gxbb_pwrc_mem_vpu[] = अणु
	VPU_MEMPD(HHI_VPU_MEM_PD_REG0),
	VPU_MEMPD(HHI_VPU_MEM_PD_REG1),
	VPU_HHI_MEMPD(HHI_MEM_PD_REG0),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य meson_pwrc_mem_eth[] = अणु
	अणु HHI_MEM_PD_REG0, GENMASK(3, 2) पूर्ण,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य meson8_pwrc_audio_dsp_mem[] = अणु
	अणु HHI_MEM_PD_REG0, GENMASK(1, 0) पूर्ण,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य meson8_pwrc_mem_vpu[] = अणु
	VPU_MEMPD(HHI_VPU_MEM_PD_REG0),
	VPU_MEMPD(HHI_VPU_MEM_PD_REG1),
	VPU_HHI_MEMPD(HHI_MEM_PD_REG0),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य sm1_pwrc_mem_vpu[] = अणु
	VPU_MEMPD(HHI_VPU_MEM_PD_REG0),
	VPU_MEMPD(HHI_VPU_MEM_PD_REG1),
	VPU_MEMPD(HHI_VPU_MEM_PD_REG2),
	VPU_MEMPD(HHI_VPU_MEM_PD_REG3),
	अणु HHI_VPU_MEM_PD_REG4, GENMASK(1, 0) पूर्ण,
	अणु HHI_VPU_MEM_PD_REG4, GENMASK(3, 2) पूर्ण,
	अणु HHI_VPU_MEM_PD_REG4, GENMASK(5, 4) पूर्ण,
	अणु HHI_VPU_MEM_PD_REG4, GENMASK(7, 6) पूर्ण,
	VPU_HHI_MEMPD(HHI_MEM_PD_REG0),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य sm1_pwrc_mem_nna[] = अणु
	अणु HHI_न_अंकOQ_MEM_PD_REG0, 0xff पूर्ण,
	अणु HHI_न_अंकOQ_MEM_PD_REG1, 0xff पूर्ण,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य sm1_pwrc_mem_usb[] = अणु
	अणु HHI_MEM_PD_REG0, GENMASK(31, 30) पूर्ण,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य sm1_pwrc_mem_pcie[] = अणु
	अणु HHI_MEM_PD_REG0, GENMASK(29, 26) पूर्ण,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य sm1_pwrc_mem_ge2d[] = अणु
	अणु HHI_MEM_PD_REG0, GENMASK(25, 18) पूर्ण,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य axg_pwrc_mem_audio[] = अणु
	अणु HHI_MEM_PD_REG0, GENMASK(5, 4) पूर्ण,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_mem_करोमुख्य sm1_pwrc_mem_audio[] = अणु
	अणु HHI_MEM_PD_REG0, GENMASK(5, 4) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(1, 0) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(3, 2) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(5, 4) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(7, 6) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(13, 12) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(15, 14) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(17, 16) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(19, 18) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(21, 20) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(23, 22) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(25, 24) पूर्ण,
	अणु HHI_AUDIO_MEM_PD_REG0, GENMASK(27, 26) पूर्ण,
पूर्ण;

#घोषणा VPU_PD(__name, __top_pd, __mem, __get_घातer, __resets, __clks)	\
	अणु								\
		.name = __name,						\
		.reset_names_count = __resets,				\
		.clk_names_count = __clks,				\
		.top_pd = __top_pd,					\
		.mem_pd_count = ARRAY_SIZE(__mem),			\
		.mem_pd = __mem,					\
		.get_घातer = __get_घातer,				\
	पूर्ण

#घोषणा TOP_PD(__name, __top_pd, __mem, __get_घातer)			\
	अणु								\
		.name = __name,						\
		.top_pd = __top_pd,					\
		.mem_pd_count = ARRAY_SIZE(__mem),			\
		.mem_pd = __mem,					\
		.get_घातer = __get_घातer,				\
	पूर्ण

#घोषणा MEM_PD(__name, __mem)						\
	TOP_PD(__name, शून्य, __mem, शून्य)

अटल bool pwrc_ee_get_घातer(काष्ठा meson_ee_pwrc_करोमुख्य *pwrc_करोमुख्य);

अटल काष्ठा meson_ee_pwrc_करोमुख्य_desc axg_pwrc_करोमुख्यs[] = अणु
	[PWRC_AXG_VPU_ID]  = VPU_PD("VPU", &gx_pwrc_vpu, axg_pwrc_mem_vpu,
				     pwrc_ee_get_घातer, 5, 2),
	[PWRC_AXG_ETHERNET_MEM_ID] = MEM_PD("ETH", meson_pwrc_mem_eth),
	[PWRC_AXG_AUDIO_ID] = MEM_PD("AUDIO", axg_pwrc_mem_audio),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_desc g12a_pwrc_करोमुख्यs[] = अणु
	[PWRC_G12A_VPU_ID]  = VPU_PD("VPU", &gx_pwrc_vpu, g12a_pwrc_mem_vpu,
				     pwrc_ee_get_घातer, 11, 2),
	[PWRC_G12A_ETH_ID] = MEM_PD("ETH", meson_pwrc_mem_eth),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_desc gxbb_pwrc_करोमुख्यs[] = अणु
	[PWRC_GXBB_VPU_ID]  = VPU_PD("VPU", &gx_pwrc_vpu, gxbb_pwrc_mem_vpu,
				     pwrc_ee_get_घातer, 12, 2),
	[PWRC_GXBB_ETHERNET_MEM_ID] = MEM_PD("ETH", meson_pwrc_mem_eth),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_desc meson8_pwrc_करोमुख्यs[] = अणु
	[PWRC_MESON8_VPU_ID]  = VPU_PD("VPU", &meson8_pwrc_vpu,
				       meson8_pwrc_mem_vpu, pwrc_ee_get_घातer,
				       0, 1),
	[PWRC_MESON8_ETHERNET_MEM_ID] = MEM_PD("ETHERNET_MEM",
					       meson_pwrc_mem_eth),
	[PWRC_MESON8_AUDIO_DSP_MEM_ID] = MEM_PD("AUDIO_DSP_MEM",
						meson8_pwrc_audio_dsp_mem),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_desc meson8b_pwrc_करोमुख्यs[] = अणु
	[PWRC_MESON8_VPU_ID]  = VPU_PD("VPU", &meson8_pwrc_vpu,
				       meson8_pwrc_mem_vpu, pwrc_ee_get_घातer,
				       11, 1),
	[PWRC_MESON8_ETHERNET_MEM_ID] = MEM_PD("ETHERNET_MEM",
					       meson_pwrc_mem_eth),
	[PWRC_MESON8_AUDIO_DSP_MEM_ID] = MEM_PD("AUDIO_DSP_MEM",
						meson8_pwrc_audio_dsp_mem),
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_desc sm1_pwrc_करोमुख्यs[] = अणु
	[PWRC_SM1_VPU_ID]  = VPU_PD("VPU", &sm1_pwrc_vpu, sm1_pwrc_mem_vpu,
				    pwrc_ee_get_घातer, 11, 2),
	[PWRC_SM1_NNA_ID]  = TOP_PD("NNA", &sm1_pwrc_nna, sm1_pwrc_mem_nna,
				    pwrc_ee_get_घातer),
	[PWRC_SM1_USB_ID]  = TOP_PD("USB", &sm1_pwrc_usb, sm1_pwrc_mem_usb,
				    pwrc_ee_get_घातer),
	[PWRC_SM1_PCIE_ID] = TOP_PD("PCI", &sm1_pwrc_pci, sm1_pwrc_mem_pcie,
				    pwrc_ee_get_घातer),
	[PWRC_SM1_GE2D_ID] = TOP_PD("GE2D", &sm1_pwrc_ge2d, sm1_pwrc_mem_ge2d,
				    pwrc_ee_get_घातer),
	[PWRC_SM1_AUDIO_ID] = MEM_PD("AUDIO", sm1_pwrc_mem_audio),
	[PWRC_SM1_ETH_ID] = MEM_PD("ETH", meson_pwrc_mem_eth),
पूर्ण;

काष्ठा meson_ee_pwrc_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य base;
	bool enabled;
	काष्ठा meson_ee_pwrc *pwrc;
	काष्ठा meson_ee_pwrc_करोमुख्य_desc desc;
	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;
	काष्ठा reset_control *rstc;
	पूर्णांक num_rstc;
पूर्ण;

काष्ठा meson_ee_pwrc अणु
	काष्ठा regmap *regmap_ao;
	काष्ठा regmap *regmap_hhi;
	काष्ठा meson_ee_pwrc_करोमुख्य *करोमुख्यs;
	काष्ठा genpd_onecell_data xlate;
पूर्ण;

अटल bool pwrc_ee_get_घातer(काष्ठा meson_ee_pwrc_करोमुख्य *pwrc_करोमुख्य)
अणु
	u32 reg;

	regmap_पढ़ो(pwrc_करोमुख्य->pwrc->regmap_ao,
		    pwrc_करोमुख्य->desc.top_pd->sleep_reg, &reg);

	वापस (reg & pwrc_करोमुख्य->desc.top_pd->sleep_mask);
पूर्ण

अटल पूर्णांक meson_ee_pwrc_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा meson_ee_pwrc_करोमुख्य *pwrc_करोमुख्य =
		container_of(करोमुख्य, काष्ठा meson_ee_pwrc_करोमुख्य, base);
	पूर्णांक i;

	अगर (pwrc_करोमुख्य->desc.top_pd)
		regmap_update_bits(pwrc_करोमुख्य->pwrc->regmap_ao,
				   pwrc_करोमुख्य->desc.top_pd->sleep_reg,
				   pwrc_करोमुख्य->desc.top_pd->sleep_mask,
				   pwrc_करोमुख्य->desc.top_pd->sleep_mask);
	udelay(20);

	क्रम (i = 0 ; i < pwrc_करोमुख्य->desc.mem_pd_count ; ++i)
		regmap_update_bits(pwrc_करोमुख्य->pwrc->regmap_hhi,
				   pwrc_करोमुख्य->desc.mem_pd[i].reg,
				   pwrc_करोमुख्य->desc.mem_pd[i].mask,
				   pwrc_करोमुख्य->desc.mem_pd[i].mask);

	udelay(20);

	अगर (pwrc_करोमुख्य->desc.top_pd)
		regmap_update_bits(pwrc_करोमुख्य->pwrc->regmap_ao,
				   pwrc_करोमुख्य->desc.top_pd->iso_reg,
				   pwrc_करोमुख्य->desc.top_pd->iso_mask,
				   pwrc_करोमुख्य->desc.top_pd->iso_mask);

	अगर (pwrc_करोमुख्य->num_clks) अणु
		msleep(20);
		clk_bulk_disable_unprepare(pwrc_करोमुख्य->num_clks,
					   pwrc_करोमुख्य->clks);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_ee_pwrc_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा meson_ee_pwrc_करोमुख्य *pwrc_करोमुख्य =
		container_of(करोमुख्य, काष्ठा meson_ee_pwrc_करोमुख्य, base);
	पूर्णांक i, ret;

	अगर (pwrc_करोमुख्य->desc.top_pd)
		regmap_update_bits(pwrc_करोमुख्य->pwrc->regmap_ao,
				   pwrc_करोमुख्य->desc.top_pd->sleep_reg,
				   pwrc_करोमुख्य->desc.top_pd->sleep_mask, 0);
	udelay(20);

	क्रम (i = 0 ; i < pwrc_करोमुख्य->desc.mem_pd_count ; ++i)
		regmap_update_bits(pwrc_करोमुख्य->pwrc->regmap_hhi,
				   pwrc_करोमुख्य->desc.mem_pd[i].reg,
				   pwrc_करोमुख्य->desc.mem_pd[i].mask, 0);

	udelay(20);

	ret = reset_control_निश्चित(pwrc_करोमुख्य->rstc);
	अगर (ret)
		वापस ret;

	अगर (pwrc_करोमुख्य->desc.top_pd)
		regmap_update_bits(pwrc_करोमुख्य->pwrc->regmap_ao,
				   pwrc_करोमुख्य->desc.top_pd->iso_reg,
				   pwrc_करोमुख्य->desc.top_pd->iso_mask, 0);

	ret = reset_control_deनिश्चित(pwrc_करोमुख्य->rstc);
	अगर (ret)
		वापस ret;

	वापस clk_bulk_prepare_enable(pwrc_करोमुख्य->num_clks,
				       pwrc_करोमुख्य->clks);
पूर्ण

अटल पूर्णांक meson_ee_pwrc_init_करोमुख्य(काष्ठा platक्रमm_device *pdev,
				     काष्ठा meson_ee_pwrc *pwrc,
				     काष्ठा meson_ee_pwrc_करोमुख्य *करोm)
अणु
	पूर्णांक ret;

	करोm->pwrc = pwrc;
	करोm->num_rstc = करोm->desc.reset_names_count;
	करोm->num_clks = करोm->desc.clk_names_count;

	अगर (करोm->num_rstc) अणु
		पूर्णांक count = reset_control_get_count(&pdev->dev);

		अगर (count != करोm->num_rstc)
			dev_warn(&pdev->dev, "Invalid resets count %d for domain %s\n",
				 count, करोm->desc.name);

		करोm->rstc = devm_reset_control_array_get_exclusive(&pdev->dev);
		अगर (IS_ERR(करोm->rstc))
			वापस PTR_ERR(करोm->rstc);
	पूर्ण

	अगर (करोm->num_clks) अणु
		पूर्णांक ret = devm_clk_bulk_get_all(&pdev->dev, &करोm->clks);
		अगर (ret < 0)
			वापस ret;

		अगर (करोm->num_clks != ret) अणु
			dev_warn(&pdev->dev, "Invalid clocks count %d for domain %s\n",
				 ret, करोm->desc.name);
			करोm->num_clks = ret;
		पूर्ण
	पूर्ण

	करोm->base.name = करोm->desc.name;
	करोm->base.घातer_on = meson_ee_pwrc_on;
	करोm->base.घातer_off = meson_ee_pwrc_off;

	/*
         * TOFIX: This is a special हाल क्रम the VPU घातer करोमुख्य, which can
	 * be enabled previously by the bootloader. In this हाल the VPU
         * pipeline may be functional but no driver maybe never attach
         * to this घातer करोमुख्य, and अगर the करोमुख्य is disabled it could
         * cause प्रणाली errors. This is why the pm_करोमुख्य_always_on_gov
         * is used here.
         * For the same reason, the घड़ीs should be enabled in हाल
         * we need to घातer the करोमुख्य off, otherwise the पूर्णांकernal घड़ीs
         * prepare/enable counters won't be in sync.
         */
	अगर (करोm->num_clks && करोm->desc.get_घातer && !करोm->desc.get_घातer(करोm)) अणु
		ret = clk_bulk_prepare_enable(करोm->num_clks, करोm->clks);
		अगर (ret)
			वापस ret;

		करोm->base.flags = GENPD_FLAG_ALWAYS_ON;
		ret = pm_genpd_init(&करोm->base, शून्य, false);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = pm_genpd_init(&करोm->base, शून्य,
				    (करोm->desc.get_घातer ?
				     करोm->desc.get_घातer(करोm) : true));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_ee_pwrc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा meson_ee_pwrc_करोमुख्य_data *match;
	काष्ठा regmap *regmap_ao, *regmap_hhi;
	काष्ठा meson_ee_pwrc *pwrc;
	पूर्णांक i, ret;

	match = of_device_get_match_data(&pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "failed to get match data\n");
		वापस -ENODEV;
	पूर्ण

	pwrc = devm_kzalloc(&pdev->dev, माप(*pwrc), GFP_KERNEL);
	अगर (!pwrc)
		वापस -ENOMEM;

	pwrc->xlate.करोमुख्यs = devm_kसुस्मृति(&pdev->dev, match->count,
					   माप(*pwrc->xlate.करोमुख्यs),
					   GFP_KERNEL);
	अगर (!pwrc->xlate.करोमुख्यs)
		वापस -ENOMEM;

	pwrc->करोमुख्यs = devm_kसुस्मृति(&pdev->dev, match->count,
				     माप(*pwrc->करोमुख्यs), GFP_KERNEL);
	अगर (!pwrc->करोमुख्यs)
		वापस -ENOMEM;

	pwrc->xlate.num_करोमुख्यs = match->count;

	regmap_hhi = syscon_node_to_regmap(of_get_parent(pdev->dev.of_node));
	अगर (IS_ERR(regmap_hhi)) अणु
		dev_err(&pdev->dev, "failed to get HHI regmap\n");
		वापस PTR_ERR(regmap_hhi);
	पूर्ण

	regmap_ao = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						    "amlogic,ao-sysctrl");
	अगर (IS_ERR(regmap_ao)) अणु
		dev_err(&pdev->dev, "failed to get AO regmap\n");
		वापस PTR_ERR(regmap_ao);
	पूर्ण

	pwrc->regmap_ao = regmap_ao;
	pwrc->regmap_hhi = regmap_hhi;

	platक्रमm_set_drvdata(pdev, pwrc);

	क्रम (i = 0 ; i < match->count ; ++i) अणु
		काष्ठा meson_ee_pwrc_करोमुख्य *करोm = &pwrc->करोमुख्यs[i];

		स_नकल(&करोm->desc, &match->करोमुख्यs[i], माप(करोm->desc));

		ret = meson_ee_pwrc_init_करोमुख्य(pdev, pwrc, करोm);
		अगर (ret)
			वापस ret;

		pwrc->xlate.करोमुख्यs[i] = &करोm->base;
	पूर्ण

	वापस of_genpd_add_provider_onecell(pdev->dev.of_node, &pwrc->xlate);
पूर्ण

अटल व्योम meson_ee_pwrc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_ee_pwrc *pwrc = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0 ; i < pwrc->xlate.num_करोमुख्यs ; ++i) अणु
		काष्ठा meson_ee_pwrc_करोमुख्य *करोm = &pwrc->करोमुख्यs[i];

		अगर (करोm->desc.get_घातer && !करोm->desc.get_घातer(करोm))
			meson_ee_pwrc_off(&करोm->base);
	पूर्ण
पूर्ण

अटल काष्ठा meson_ee_pwrc_करोमुख्य_data meson_ee_g12a_pwrc_data = अणु
	.count = ARRAY_SIZE(g12a_pwrc_करोमुख्यs),
	.करोमुख्यs = g12a_pwrc_करोमुख्यs,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_data meson_ee_axg_pwrc_data = अणु
	.count = ARRAY_SIZE(axg_pwrc_करोमुख्यs),
	.करोमुख्यs = axg_pwrc_करोमुख्यs,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_data meson_ee_gxbb_pwrc_data = अणु
	.count = ARRAY_SIZE(gxbb_pwrc_करोमुख्यs),
	.करोमुख्यs = gxbb_pwrc_करोमुख्यs,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_data meson_ee_m8_pwrc_data = अणु
	.count = ARRAY_SIZE(meson8_pwrc_करोमुख्यs),
	.करोमुख्यs = meson8_pwrc_करोमुख्यs,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_data meson_ee_m8b_pwrc_data = अणु
	.count = ARRAY_SIZE(meson8b_pwrc_करोमुख्यs),
	.करोमुख्यs = meson8b_pwrc_करोमुख्यs,
पूर्ण;

अटल काष्ठा meson_ee_pwrc_करोमुख्य_data meson_ee_sm1_pwrc_data = अणु
	.count = ARRAY_SIZE(sm1_pwrc_करोमुख्यs),
	.करोमुख्यs = sm1_pwrc_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_ee_pwrc_match_table[] = अणु
	अणु
		.compatible = "amlogic,meson8-pwrc",
		.data = &meson_ee_m8_pwrc_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8b-pwrc",
		.data = &meson_ee_m8b_pwrc_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8m2-pwrc",
		.data = &meson_ee_m8b_pwrc_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-axg-pwrc",
		.data = &meson_ee_axg_pwrc_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-gxbb-pwrc",
		.data = &meson_ee_gxbb_pwrc_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-g12a-pwrc",
		.data = &meson_ee_g12a_pwrc_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-sm1-pwrc",
		.data = &meson_ee_sm1_pwrc_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_ee_pwrc_match_table);

अटल काष्ठा platक्रमm_driver meson_ee_pwrc_driver = अणु
	.probe = meson_ee_pwrc_probe,
	.shutकरोwn = meson_ee_pwrc_shutकरोwn,
	.driver = अणु
		.name		= "meson_ee_pwrc",
		.of_match_table	= meson_ee_pwrc_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_ee_pwrc_driver);
MODULE_LICENSE("GPL v2");
