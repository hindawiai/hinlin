<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/at91.h>

#समावेश "pmc.h"

अटल DEFINE_SPINLOCK(sam9rl_mck_lock);

अटल स्थिर काष्ठा clk_master_अक्षरacteristics sam9rl_mck_अक्षरacteristics = अणु
	.output = अणु .min = 0, .max = 94000000 पूर्ण,
	.भागisors = अणु 1, 2, 4, 0 पूर्ण,
पूर्ण;

अटल u8 sam9rl_plla_out[] = अणु 0, 2 पूर्ण;

अटल स्थिर काष्ठा clk_range sam9rl_plla_outमाला_दो[] = अणु
	अणु .min = 80000000, .max = 200000000 पूर्ण,
	अणु .min = 190000000, .max = 240000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics sam9rl_plla_अक्षरacteristics = अणु
	.input = अणु .min = 1000000, .max = 32000000 पूर्ण,
	.num_output = ARRAY_SIZE(sam9rl_plla_outमाला_दो),
	.output = sam9rl_plla_outमाला_दो,
	.out = sam9rl_plla_out,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *n;
	अक्षर *p;
	u8 id;
पूर्ण at91sam9rl_प्रणालीck[] = अणु
	अणु .n = "pck0",  .p = "prog0",    .id = 8 पूर्ण,
	अणु .n = "pck1",  .p = "prog1",    .id = 9 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *n;
	u8 id;
पूर्ण at91sam9rl_periphck[] = अणु
	अणु .n = "pioA_clk",   .id = 2, पूर्ण,
	अणु .n = "pioB_clk",   .id = 3, पूर्ण,
	अणु .n = "pioC_clk",   .id = 4, पूर्ण,
	अणु .n = "pioD_clk",   .id = 5, पूर्ण,
	अणु .n = "usart0_clk", .id = 6, पूर्ण,
	अणु .n = "usart1_clk", .id = 7, पूर्ण,
	अणु .n = "usart2_clk", .id = 8, पूर्ण,
	अणु .n = "usart3_clk", .id = 9, पूर्ण,
	अणु .n = "mci0_clk",   .id = 10, पूर्ण,
	अणु .n = "twi0_clk",   .id = 11, पूर्ण,
	अणु .n = "twi1_clk",   .id = 12, पूर्ण,
	अणु .n = "spi0_clk",   .id = 13, पूर्ण,
	अणु .n = "ssc0_clk",   .id = 14, पूर्ण,
	अणु .n = "ssc1_clk",   .id = 15, पूर्ण,
	अणु .n = "tc0_clk",    .id = 16, पूर्ण,
	अणु .n = "tc1_clk",    .id = 17, पूर्ण,
	अणु .n = "tc2_clk",    .id = 18, पूर्ण,
	अणु .n = "pwm_clk",    .id = 19, पूर्ण,
	अणु .n = "adc_clk",    .id = 20, पूर्ण,
	अणु .n = "dma0_clk",   .id = 21, पूर्ण,
	अणु .n = "udphs_clk",  .id = 22, पूर्ण,
	अणु .n = "lcd_clk",    .id = 23, पूर्ण,
पूर्ण;

अटल व्योम __init at91sam9rl_pmc_setup(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *slck_name, *मुख्यxtal_name;
	काष्ठा pmc_data *at91sam9rl_pmc;
	स्थिर अक्षर *parent_names[6];
	काष्ठा regmap *regmap;
	काष्ठा clk_hw *hw;
	पूर्णांक i;

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

	at91sam9rl_pmc = pmc_data_allocate(PMC_PLLACK + 1,
					   nck(at91sam9rl_प्रणालीck),
					   nck(at91sam9rl_periphck), 0, 2);
	अगर (!at91sam9rl_pmc)
		वापस;

	hw = at91_clk_रेजिस्टर_rm9200_मुख्य(regmap, "mainck", मुख्यxtal_name);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9rl_pmc->chws[PMC_MAIN] = hw;

	hw = at91_clk_रेजिस्टर_pll(regmap, "pllack", "mainck", 0,
				   &at91rm9200_pll_layout,
				   &sam9rl_plla_अक्षरacteristics);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9rl_pmc->chws[PMC_PLLACK] = hw;

	hw = at91_clk_रेजिस्टर_uपंचांगi(regmap, शून्य, "utmick", "mainck");
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9rl_pmc->chws[PMC_UTMI] = hw;

	parent_names[0] = slck_name;
	parent_names[1] = "mainck";
	parent_names[2] = "pllack";
	parent_names[3] = "utmick";
	hw = at91_clk_रेजिस्टर_master_pres(regmap, "masterck_pres", 4,
					   parent_names,
					   &at91rm9200_master_layout,
					   &sam9rl_mck_अक्षरacteristics,
					   &sam9rl_mck_lock, CLK_SET_RATE_GATE,
					   पूर्णांक_न्यून);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_master_भाग(regmap, "masterck_div",
					  "masterck_pres",
					  &at91rm9200_master_layout,
					  &sam9rl_mck_अक्षरacteristics,
					  &sam9rl_mck_lock, CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9rl_pmc->chws[PMC_MCK] = hw;

	parent_names[0] = slck_name;
	parent_names[1] = "mainck";
	parent_names[2] = "pllack";
	parent_names[3] = "utmick";
	parent_names[4] = "masterck_div";
	क्रम (i = 0; i < 2; i++) अणु
		अक्षर name[6];

		snम_लिखो(name, माप(name), "prog%d", i);

		hw = at91_clk_रेजिस्टर_programmable(regmap, name,
						    parent_names, 5, i,
						    &at91rm9200_programmable_layout,
						    शून्य);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9rl_pmc->pchws[i] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(at91sam9rl_प्रणालीck); i++) अणु
		hw = at91_clk_रेजिस्टर_प्रणाली(regmap, at91sam9rl_प्रणालीck[i].n,
					      at91sam9rl_प्रणालीck[i].p,
					      at91sam9rl_प्रणालीck[i].id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9rl_pmc->shws[at91sam9rl_प्रणालीck[i].id] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(at91sam9rl_periphck); i++) अणु
		hw = at91_clk_रेजिस्टर_peripheral(regmap,
						  at91sam9rl_periphck[i].n,
						  "masterck_div",
						  at91sam9rl_periphck[i].id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9rl_pmc->phws[at91sam9rl_periphck[i].id] = hw;
	पूर्ण

	of_clk_add_hw_provider(np, of_clk_hw_pmc_get, at91sam9rl_pmc);

	वापस;

err_मुक्त:
	kमुक्त(at91sam9rl_pmc);
पूर्ण

CLK_OF_DECLARE(at91sam9rl_pmc, "atmel,at91sam9rl-pmc", at91sam9rl_pmc_setup);
