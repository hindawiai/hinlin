<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/at91.h>

#समावेश "pmc.h"

अटल DEFINE_SPINLOCK(pmc_pll_lock);
अटल DEFINE_SPINLOCK(mck_lock);

अटल स्थिर काष्ठा clk_master_अक्षरacteristics mck_अक्षरacteristics = अणु
	.output = अणु .min = 140000000, .max = 200000000 पूर्ण,
	.भागisors = अणु 1, 2, 4, 3 पूर्ण,
	.have_भाग3_pres = 1,
पूर्ण;

अटल स्थिर काष्ठा clk_master_layout sam9x60_master_layout = अणु
	.mask = 0x373,
	.pres_shअगरt = 4,
	.offset = 0x28,
पूर्ण;

अटल स्थिर काष्ठा clk_range plla_outमाला_दो[] = अणु
	अणु .min = 2343750, .max = 1200000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics plla_अक्षरacteristics = अणु
	.input = अणु .min = 12000000, .max = 48000000 पूर्ण,
	.num_output = ARRAY_SIZE(plla_outमाला_दो),
	.output = plla_outमाला_दो,
पूर्ण;

अटल स्थिर काष्ठा clk_range upll_outमाला_दो[] = अणु
	अणु .min = 300000000, .max = 500000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics upll_अक्षरacteristics = अणु
	.input = अणु .min = 12000000, .max = 48000000 पूर्ण,
	.num_output = ARRAY_SIZE(upll_outमाला_दो),
	.output = upll_outमाला_दो,
	.upll = true,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_layout pll_frac_layout = अणु
	.mul_mask = GENMASK(31, 24),
	.frac_mask = GENMASK(21, 0),
	.mul_shअगरt = 24,
	.frac_shअगरt = 0,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_layout pll_भाग_layout = अणु
	.भाग_mask = GENMASK(7, 0),
	.enभाग_mask = BIT(29),
	.भाग_shअगरt = 0,
	.enभाग_shअगरt = 29,
पूर्ण;

अटल स्थिर काष्ठा clk_programmable_layout sam9x60_programmable_layout = अणु
	.pres_mask = 0xff,
	.pres_shअगरt = 8,
	.css_mask = 0x1f,
	.have_slck_mck = 0,
	.is_pres_direct = 1,
पूर्ण;

अटल स्थिर काष्ठा clk_pcr_layout sam9x60_pcr_layout = अणु
	.offset = 0x88,
	.cmd = BIT(31),
	.gckcss_mask = GENMASK(12, 8),
	.pid_mask = GENMASK(6, 0),
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *n;
	अक्षर *p;
	u8 id;
पूर्ण sam9x60_प्रणालीck[] = अणु
	अणु .n = "ddrck",  .p = "masterck_div", .id = 2 पूर्ण,
	अणु .n = "uhpck",  .p = "usbck",    .id = 6 पूर्ण,
	अणु .n = "pck0",   .p = "prog0",    .id = 8 पूर्ण,
	अणु .n = "pck1",   .p = "prog1",    .id = 9 पूर्ण,
	अणु .n = "qspick", .p = "masterck_div", .id = 19 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *n;
	u8 id;
पूर्ण sam9x60_periphck[] = अणु
	अणु .n = "pioA_clk",   .id = 2, पूर्ण,
	अणु .n = "pioB_clk",   .id = 3, पूर्ण,
	अणु .n = "pioC_clk",   .id = 4, पूर्ण,
	अणु .n = "flex0_clk",  .id = 5, पूर्ण,
	अणु .n = "flex1_clk",  .id = 6, पूर्ण,
	अणु .n = "flex2_clk",  .id = 7, पूर्ण,
	अणु .n = "flex3_clk",  .id = 8, पूर्ण,
	अणु .n = "flex6_clk",  .id = 9, पूर्ण,
	अणु .n = "flex7_clk",  .id = 10, पूर्ण,
	अणु .n = "flex8_clk",  .id = 11, पूर्ण,
	अणु .n = "sdmmc0_clk", .id = 12, पूर्ण,
	अणु .n = "flex4_clk",  .id = 13, पूर्ण,
	अणु .n = "flex5_clk",  .id = 14, पूर्ण,
	अणु .n = "flex9_clk",  .id = 15, पूर्ण,
	अणु .n = "flex10_clk", .id = 16, पूर्ण,
	अणु .n = "tcb0_clk",   .id = 17, पूर्ण,
	अणु .n = "pwm_clk",    .id = 18, पूर्ण,
	अणु .n = "adc_clk",    .id = 19, पूर्ण,
	अणु .n = "dma0_clk",   .id = 20, पूर्ण,
	अणु .n = "matrix_clk", .id = 21, पूर्ण,
	अणु .n = "uhphs_clk",  .id = 22, पूर्ण,
	अणु .n = "udphs_clk",  .id = 23, पूर्ण,
	अणु .n = "macb0_clk",  .id = 24, पूर्ण,
	अणु .n = "lcd_clk",    .id = 25, पूर्ण,
	अणु .n = "sdmmc1_clk", .id = 26, पूर्ण,
	अणु .n = "macb1_clk",  .id = 27, पूर्ण,
	अणु .n = "ssc_clk",    .id = 28, पूर्ण,
	अणु .n = "can0_clk",   .id = 29, पूर्ण,
	अणु .n = "can1_clk",   .id = 30, पूर्ण,
	अणु .n = "flex11_clk", .id = 32, पूर्ण,
	अणु .n = "flex12_clk", .id = 33, पूर्ण,
	अणु .n = "i2s_clk",    .id = 34, पूर्ण,
	अणु .n = "qspi_clk",   .id = 35, पूर्ण,
	अणु .n = "gfx2d_clk",  .id = 36, पूर्ण,
	अणु .n = "pit64b_clk", .id = 37, पूर्ण,
	अणु .n = "trng_clk",   .id = 38, पूर्ण,
	अणु .n = "aes_clk",    .id = 39, पूर्ण,
	अणु .n = "tdes_clk",   .id = 40, पूर्ण,
	अणु .n = "sha_clk",    .id = 41, पूर्ण,
	अणु .n = "classd_clk", .id = 42, पूर्ण,
	अणु .n = "isi_clk",    .id = 43, पूर्ण,
	अणु .n = "pioD_clk",   .id = 44, पूर्ण,
	अणु .n = "tcb1_clk",   .id = 45, पूर्ण,
	अणु .n = "dbgu_clk",   .id = 47, पूर्ण,
	अणु .n = "mpddr_clk",  .id = 49, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *n;
	u8 id;
	काष्ठा clk_range r;
पूर्ण sam9x60_gck[] = अणु
	अणु .n = "flex0_gclk",  .id = 5, पूर्ण,
	अणु .n = "flex1_gclk",  .id = 6, पूर्ण,
	अणु .n = "flex2_gclk",  .id = 7, पूर्ण,
	अणु .n = "flex3_gclk",  .id = 8, पूर्ण,
	अणु .n = "flex6_gclk",  .id = 9, पूर्ण,
	अणु .n = "flex7_gclk",  .id = 10, पूर्ण,
	अणु .n = "flex8_gclk",  .id = 11, पूर्ण,
	अणु .n = "sdmmc0_gclk", .id = 12, .r = अणु .min = 0, .max = 105000000 पूर्ण, पूर्ण,
	अणु .n = "flex4_gclk",  .id = 13, पूर्ण,
	अणु .n = "flex5_gclk",  .id = 14, पूर्ण,
	अणु .n = "flex9_gclk",  .id = 15, पूर्ण,
	अणु .n = "flex10_gclk", .id = 16, पूर्ण,
	अणु .n = "tcb0_gclk",   .id = 17, पूर्ण,
	अणु .n = "adc_gclk",    .id = 19, पूर्ण,
	अणु .n = "lcd_gclk",    .id = 25, .r = अणु .min = 0, .max = 140000000 पूर्ण, पूर्ण,
	अणु .n = "sdmmc1_gclk", .id = 26, .r = अणु .min = 0, .max = 105000000 पूर्ण, पूर्ण,
	अणु .n = "flex11_gclk", .id = 32, पूर्ण,
	अणु .n = "flex12_gclk", .id = 33, पूर्ण,
	अणु .n = "i2s_gclk",    .id = 34, .r = अणु .min = 0, .max = 105000000 पूर्ण, पूर्ण,
	अणु .n = "pit64b_gclk", .id = 37, पूर्ण,
	अणु .n = "classd_gclk", .id = 42, .r = अणु .min = 0, .max = 100000000 पूर्ण, पूर्ण,
	अणु .n = "tcb1_gclk",   .id = 45, पूर्ण,
	अणु .n = "dbgu_gclk",   .id = 47, पूर्ण,
पूर्ण;

अटल व्योम __init sam9x60_pmc_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_range range = CLK_RANGE(0, 0);
	स्थिर अक्षर *td_slck_name, *md_slck_name, *मुख्यxtal_name;
	काष्ठा pmc_data *sam9x60_pmc;
	स्थिर अक्षर *parent_names[6];
	काष्ठा clk_hw *मुख्य_osc_hw;
	काष्ठा regmap *regmap;
	काष्ठा clk_hw *hw;
	पूर्णांक i;

	i = of_property_match_string(np, "clock-names", "td_slck");
	अगर (i < 0)
		वापस;

	td_slck_name = of_clk_get_parent_name(np, i);

	i = of_property_match_string(np, "clock-names", "md_slck");
	अगर (i < 0)
		वापस;

	md_slck_name = of_clk_get_parent_name(np, i);

	i = of_property_match_string(np, "clock-names", "main_xtal");
	अगर (i < 0)
		वापस;
	मुख्यxtal_name = of_clk_get_parent_name(np, i);

	regmap = device_node_to_regmap(np);
	अगर (IS_ERR(regmap))
		वापस;

	sam9x60_pmc = pmc_data_allocate(PMC_PLLACK + 1,
					nck(sam9x60_प्रणालीck),
					nck(sam9x60_periphck),
					nck(sam9x60_gck), 8);
	अगर (!sam9x60_pmc)
		वापस;

	hw = at91_clk_रेजिस्टर_मुख्य_rc_osc(regmap, "main_rc_osc", 12000000,
					   50000000);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_मुख्य_osc(regmap, "main_osc", मुख्यxtal_name, 0);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;
	मुख्य_osc_hw = hw;

	parent_names[0] = "main_rc_osc";
	parent_names[1] = "main_osc";
	hw = at91_clk_रेजिस्टर_sam9x5_मुख्य(regmap, "mainck", parent_names, 2);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sam9x60_pmc->chws[PMC_MAIN] = hw;

	hw = sam9x60_clk_रेजिस्टर_frac_pll(regmap, &pmc_pll_lock, "pllack_fracck",
					   "mainck", sam9x60_pmc->chws[PMC_MAIN],
					   0, &plla_अक्षरacteristics,
					   &pll_frac_layout,
					   /*
					    * This feeds pllack_भागck which
					    * feeds CPU. It should not be
					    * disabled.
					    */
					   CLK_IS_CRITICAL | CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = sam9x60_clk_रेजिस्टर_भाग_pll(regmap, &pmc_pll_lock, "pllack_divck",
					  "pllack_fracck", 0, &plla_अक्षरacteristics,
					  &pll_भाग_layout,
					   /*
					    * This feeds CPU. It should not
					    * be disabled.
					    */
					  CLK_IS_CRITICAL | CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sam9x60_pmc->chws[PMC_PLLACK] = hw;

	hw = sam9x60_clk_रेजिस्टर_frac_pll(regmap, &pmc_pll_lock, "upllck_fracck",
					   "main_osc", मुख्य_osc_hw, 1,
					   &upll_अक्षरacteristics,
					   &pll_frac_layout, CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = sam9x60_clk_रेजिस्टर_भाग_pll(regmap, &pmc_pll_lock, "upllck_divck",
					  "upllck_fracck", 1, &upll_अक्षरacteristics,
					  &pll_भाग_layout,
					  CLK_SET_RATE_GATE |
					  CLK_SET_PARENT_GATE |
					  CLK_SET_RATE_PARENT);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sam9x60_pmc->chws[PMC_UTMI] = hw;

	parent_names[0] = md_slck_name;
	parent_names[1] = "mainck";
	parent_names[2] = "pllack_divck";
	hw = at91_clk_रेजिस्टर_master_pres(regmap, "masterck_pres", 3,
					   parent_names, &sam9x60_master_layout,
					   &mck_अक्षरacteristics, &mck_lock,
					   CLK_SET_RATE_GATE, पूर्णांक_न्यून);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_master_भाग(regmap, "masterck_div",
					  "masterck_pres", &sam9x60_master_layout,
					  &mck_अक्षरacteristics, &mck_lock,
					  CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sam9x60_pmc->chws[PMC_MCK] = hw;

	parent_names[0] = "pllack_divck";
	parent_names[1] = "upllck_divck";
	parent_names[2] = "main_osc";
	hw = sam9x60_clk_रेजिस्टर_usb(regmap, "usbck", parent_names, 3);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	parent_names[0] = md_slck_name;
	parent_names[1] = td_slck_name;
	parent_names[2] = "mainck";
	parent_names[3] = "masterck_div";
	parent_names[4] = "pllack_divck";
	parent_names[5] = "upllck_divck";
	क्रम (i = 0; i < 2; i++) अणु
		अक्षर name[6];

		snम_लिखो(name, माप(name), "prog%d", i);

		hw = at91_clk_रेजिस्टर_programmable(regmap, name,
						    parent_names, 6, i,
						    &sam9x60_programmable_layout,
						    शून्य);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sam9x60_pmc->pchws[i] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sam9x60_प्रणालीck); i++) अणु
		hw = at91_clk_रेजिस्टर_प्रणाली(regmap, sam9x60_प्रणालीck[i].n,
					      sam9x60_प्रणालीck[i].p,
					      sam9x60_प्रणालीck[i].id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sam9x60_pmc->shws[sam9x60_प्रणालीck[i].id] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sam9x60_periphck); i++) अणु
		hw = at91_clk_रेजिस्टर_sam9x5_peripheral(regmap, &pmc_pcr_lock,
							 &sam9x60_pcr_layout,
							 sam9x60_periphck[i].n,
							 "masterck_div",
							 sam9x60_periphck[i].id,
							 &range, पूर्णांक_न्यून);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sam9x60_pmc->phws[sam9x60_periphck[i].id] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sam9x60_gck); i++) अणु
		hw = at91_clk_रेजिस्टर_generated(regmap, &pmc_pcr_lock,
						 &sam9x60_pcr_layout,
						 sam9x60_gck[i].n,
						 parent_names, शून्य, 6,
						 sam9x60_gck[i].id,
						 &sam9x60_gck[i].r, पूर्णांक_न्यून);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sam9x60_pmc->ghws[sam9x60_gck[i].id] = hw;
	पूर्ण

	of_clk_add_hw_provider(np, of_clk_hw_pmc_get, sam9x60_pmc);

	वापस;

err_मुक्त:
	kमुक्त(sam9x60_pmc);
पूर्ण
/* Some clks are used क्रम a घड़ीsource */
CLK_OF_DECLARE(sam9x60_pmc, "microchip,sam9x60-pmc", sam9x60_pmc_setup);
