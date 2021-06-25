<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/at91.h>

#समावेश "pmc.h"

अटल DEFINE_SPINLOCK(at91sam9g45_mck_lock);

अटल स्थिर काष्ठा clk_master_अक्षरacteristics mck_अक्षरacteristics = अणु
	.output = अणु .min = 0, .max = 133333333 पूर्ण,
	.भागisors = अणु 1, 2, 4, 3 पूर्ण,
पूर्ण;

अटल u8 plla_out[] = अणु 0, 1, 2, 3, 0, 1, 2, 3 पूर्ण;

अटल u16 plla_icpll[] = अणु 0, 0, 0, 0, 1, 1, 1, 1 पूर्ण;

अटल स्थिर काष्ठा clk_range plla_outमाला_दो[] = अणु
	अणु .min = 745000000, .max = 800000000 पूर्ण,
	अणु .min = 695000000, .max = 750000000 पूर्ण,
	अणु .min = 645000000, .max = 700000000 पूर्ण,
	अणु .min = 595000000, .max = 650000000 पूर्ण,
	अणु .min = 545000000, .max = 600000000 पूर्ण,
	अणु .min = 495000000, .max = 555000000 पूर्ण,
	अणु .min = 445000000, .max = 500000000 पूर्ण,
	अणु .min = 400000000, .max = 450000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics plla_अक्षरacteristics = अणु
	.input = अणु .min = 2000000, .max = 32000000 पूर्ण,
	.num_output = ARRAY_SIZE(plla_outमाला_दो),
	.output = plla_outमाला_दो,
	.icpll = plla_icpll,
	.out = plla_out,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *n;
	अक्षर *p;
	u8 id;
पूर्ण at91sam9g45_प्रणालीck[] = अणु
	अणु .n = "ddrck", .p = "masterck_div", .id = 2 पूर्ण,
	अणु .n = "uhpck", .p = "usbck",        .id = 6 पूर्ण,
	अणु .n = "pck0",  .p = "prog0",        .id = 8 पूर्ण,
	अणु .n = "pck1",  .p = "prog1",        .id = 9 पूर्ण,
पूर्ण;

काष्ठा pck अणु
	अक्षर *n;
	u8 id;
पूर्ण;

अटल स्थिर काष्ठा pck at91sam9g45_periphck[] = अणु
	अणु .n = "pioA_clk",       .id = 2, पूर्ण,
	अणु .n = "pioB_clk",       .id = 3, पूर्ण,
	अणु .n = "pioC_clk",       .id = 4, पूर्ण,
	अणु .n = "pioDE_clk",      .id = 5, पूर्ण,
	अणु .n = "trng_clk",       .id = 6, पूर्ण,
	अणु .n = "usart0_clk",     .id = 7, पूर्ण,
	अणु .n = "usart1_clk",     .id = 8, पूर्ण,
	अणु .n = "usart2_clk",     .id = 9, पूर्ण,
	अणु .n = "usart3_clk",     .id = 10, पूर्ण,
	अणु .n = "mci0_clk",       .id = 11, पूर्ण,
	अणु .n = "twi0_clk",       .id = 12, पूर्ण,
	अणु .n = "twi1_clk",       .id = 13, पूर्ण,
	अणु .n = "spi0_clk",       .id = 14, पूर्ण,
	अणु .n = "spi1_clk",       .id = 15, पूर्ण,
	अणु .n = "ssc0_clk",       .id = 16, पूर्ण,
	अणु .n = "ssc1_clk",       .id = 17, पूर्ण,
	अणु .n = "tcb0_clk",       .id = 18, पूर्ण,
	अणु .n = "pwm_clk",        .id = 19, पूर्ण,
	अणु .n = "adc_clk",        .id = 20, पूर्ण,
	अणु .n = "dma0_clk",       .id = 21, पूर्ण,
	अणु .n = "uhphs_clk",      .id = 22, पूर्ण,
	अणु .n = "lcd_clk",        .id = 23, पूर्ण,
	अणु .n = "ac97_clk",       .id = 24, पूर्ण,
	अणु .n = "macb0_clk",      .id = 25, पूर्ण,
	अणु .n = "isi_clk",        .id = 26, पूर्ण,
	अणु .n = "udphs_clk",      .id = 27, पूर्ण,
	अणु .n = "aestdessha_clk", .id = 28, पूर्ण,
	अणु .n = "mci1_clk",       .id = 29, पूर्ण,
	अणु .n = "vdec_clk",       .id = 30, पूर्ण,
पूर्ण;

अटल व्योम __init at91sam9g45_pmc_setup(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *slck_name, *मुख्यxtal_name;
	काष्ठा pmc_data *at91sam9g45_pmc;
	स्थिर अक्षर *parent_names[6];
	काष्ठा regmap *regmap;
	काष्ठा clk_hw *hw;
	पूर्णांक i;
	bool bypass;

	i = of_property_match_string(np, "clock-names", "slow_clk");
	अगर (i < 0)
		वापस;

	slck_name = of_clk_get_parent_name(np, i);

	i = of_property_match_string(np, "clock-names", "main_xtal");
	अगर (i < 0)
		वापस;
	मुख्यxtal_name = of_clk_get_parent_name(np, i);

	regmap = device_node_to_regmap(np);
	अगर (IS_ERR(regmap))
		वापस;

	at91sam9g45_pmc = pmc_data_allocate(PMC_PLLACK + 1,
					    nck(at91sam9g45_प्रणालीck),
					    nck(at91sam9g45_periphck), 0, 2);
	अगर (!at91sam9g45_pmc)
		वापस;

	bypass = of_property_पढ़ो_bool(np, "atmel,osc-bypass");

	hw = at91_clk_रेजिस्टर_मुख्य_osc(regmap, "main_osc", मुख्यxtal_name,
					bypass);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_rm9200_मुख्य(regmap, "mainck", "main_osc");
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9g45_pmc->chws[PMC_MAIN] = hw;

	hw = at91_clk_रेजिस्टर_pll(regmap, "pllack", "mainck", 0,
				   &at91rm9200_pll_layout, &plla_अक्षरacteristics);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_plद_भाग(regmap, "plladivck", "pllack");
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9g45_pmc->chws[PMC_PLLACK] = hw;

	hw = at91_clk_रेजिस्टर_uपंचांगi(regmap, शून्य, "utmick", "mainck");
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9g45_pmc->chws[PMC_UTMI] = hw;

	parent_names[0] = slck_name;
	parent_names[1] = "mainck";
	parent_names[2] = "plladivck";
	parent_names[3] = "utmick";
	hw = at91_clk_रेजिस्टर_master_pres(regmap, "masterck_pres", 4,
					   parent_names,
					   &at91rm9200_master_layout,
					   &mck_अक्षरacteristics,
					   &at91sam9g45_mck_lock,
					   CLK_SET_RATE_GATE, पूर्णांक_न्यून);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_master_भाग(regmap, "masterck_div",
					  "masterck_pres",
					  &at91rm9200_master_layout,
					  &mck_अक्षरacteristics,
					  &at91sam9g45_mck_lock,
					  CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9g45_pmc->chws[PMC_MCK] = hw;

	parent_names[0] = "plladivck";
	parent_names[1] = "utmick";
	hw = at91sam9x5_clk_रेजिस्टर_usb(regmap, "usbck", parent_names, 2);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	parent_names[0] = slck_name;
	parent_names[1] = "mainck";
	parent_names[2] = "plladivck";
	parent_names[3] = "utmick";
	parent_names[4] = "masterck_div";
	क्रम (i = 0; i < 2; i++) अणु
		अक्षर name[6];

		snम_लिखो(name, माप(name), "prog%d", i);

		hw = at91_clk_रेजिस्टर_programmable(regmap, name,
						    parent_names, 5, i,
						    &at91sam9g45_programmable_layout,
						    शून्य);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9g45_pmc->pchws[i] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(at91sam9g45_प्रणालीck); i++) अणु
		hw = at91_clk_रेजिस्टर_प्रणाली(regmap, at91sam9g45_प्रणालीck[i].n,
					      at91sam9g45_प्रणालीck[i].p,
					      at91sam9g45_प्रणालीck[i].id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9g45_pmc->shws[at91sam9g45_प्रणालीck[i].id] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(at91sam9g45_periphck); i++) अणु
		hw = at91_clk_रेजिस्टर_peripheral(regmap,
						  at91sam9g45_periphck[i].n,
						  "masterck_div",
						  at91sam9g45_periphck[i].id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9g45_pmc->phws[at91sam9g45_periphck[i].id] = hw;
	पूर्ण

	of_clk_add_hw_provider(np, of_clk_hw_pmc_get, at91sam9g45_pmc);

	वापस;

err_मुक्त:
	kमुक्त(at91sam9g45_pmc);
पूर्ण
/*
 * The TCB is used as the घड़ीsource so its घड़ी is needed early. This means
 * this can't be a platक्रमm driver.
 */
CLK_OF_DECLARE(at91sam9g45_pmc, "atmel,at91sam9g45-pmc", at91sam9g45_pmc_setup);
