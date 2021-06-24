<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/at91.h>

#समावेश "pmc.h"

अटल DEFINE_SPINLOCK(mck_lock);

अटल स्थिर काष्ठा clk_master_अक्षरacteristics mck_अक्षरacteristics = अणु
	.output = अणु .min = 125000000, .max = 200000000 पूर्ण,
	.भागisors = अणु 1, 2, 4, 3 पूर्ण,
पूर्ण;

अटल u8 plla_out[] = अणु 0 पूर्ण;

अटल u16 plla_icpll[] = अणु 0 पूर्ण;

अटल स्थिर काष्ठा clk_range plla_outमाला_दो[] = अणु
	अणु .min = 600000000, .max = 1200000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics plla_अक्षरacteristics = अणु
	.input = अणु .min = 12000000, .max = 12000000 पूर्ण,
	.num_output = ARRAY_SIZE(plla_outमाला_दो),
	.output = plla_outमाला_दो,
	.icpll = plla_icpll,
	.out = plla_out,
पूर्ण;

अटल स्थिर काष्ठा clk_pcr_layout sama5d4_pcr_layout = अणु
	.offset = 0x10c,
	.cmd = BIT(12),
	.pid_mask = GENMASK(6, 0),
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *n;
	अक्षर *p;
	u8 id;
पूर्ण sama5d4_प्रणालीck[] = अणु
	अणु .n = "ddrck", .p = "masterck_div", .id = 2 पूर्ण,
	अणु .n = "lcdck", .p = "masterck_div", .id = 3 पूर्ण,
	अणु .n = "smdck", .p = "smdclk",       .id = 4 पूर्ण,
	अणु .n = "uhpck", .p = "usbck",        .id = 6 पूर्ण,
	अणु .n = "udpck", .p = "usbck",        .id = 7 पूर्ण,
	अणु .n = "pck0",  .p = "prog0",        .id = 8 पूर्ण,
	अणु .n = "pck1",  .p = "prog1",        .id = 9 पूर्ण,
	अणु .n = "pck2",  .p = "prog2",        .id = 10 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *n;
	u8 id;
पूर्ण sama5d4_periph32ck[] = अणु
	अणु .n = "pioD_clk", .id = 5 पूर्ण,
	अणु .n = "usart0_clk", .id = 6 पूर्ण,
	अणु .n = "usart1_clk", .id = 7 पूर्ण,
	अणु .n = "icm_clk", .id = 9 पूर्ण,
	अणु .n = "aes_clk", .id = 12 पूर्ण,
	अणु .n = "tdes_clk", .id = 14 पूर्ण,
	अणु .n = "sha_clk", .id = 15 पूर्ण,
	अणु .n = "matrix1_clk", .id = 17 पूर्ण,
	अणु .n = "hsmc_clk", .id = 22 पूर्ण,
	अणु .n = "pioA_clk", .id = 23 पूर्ण,
	अणु .n = "pioB_clk", .id = 24 पूर्ण,
	अणु .n = "pioC_clk", .id = 25 पूर्ण,
	अणु .n = "pioE_clk", .id = 26 पूर्ण,
	अणु .n = "uart0_clk", .id = 27 पूर्ण,
	अणु .n = "uart1_clk", .id = 28 पूर्ण,
	अणु .n = "usart2_clk", .id = 29 पूर्ण,
	अणु .n = "usart3_clk", .id = 30 पूर्ण,
	अणु .n = "usart4_clk", .id = 31 पूर्ण,
	अणु .n = "twi0_clk", .id = 32 पूर्ण,
	अणु .n = "twi1_clk", .id = 33 पूर्ण,
	अणु .n = "twi2_clk", .id = 34 पूर्ण,
	अणु .n = "mci0_clk", .id = 35 पूर्ण,
	अणु .n = "mci1_clk", .id = 36 पूर्ण,
	अणु .n = "spi0_clk", .id = 37 पूर्ण,
	अणु .n = "spi1_clk", .id = 38 पूर्ण,
	अणु .n = "spi2_clk", .id = 39 पूर्ण,
	अणु .n = "tcb0_clk", .id = 40 पूर्ण,
	अणु .n = "tcb1_clk", .id = 41 पूर्ण,
	अणु .n = "tcb2_clk", .id = 42 पूर्ण,
	अणु .n = "pwm_clk", .id = 43 पूर्ण,
	अणु .n = "adc_clk", .id = 44 पूर्ण,
	अणु .n = "dbgu_clk", .id = 45 पूर्ण,
	अणु .n = "uhphs_clk", .id = 46 पूर्ण,
	अणु .n = "udphs_clk", .id = 47 पूर्ण,
	अणु .n = "ssc0_clk", .id = 48 पूर्ण,
	अणु .n = "ssc1_clk", .id = 49 पूर्ण,
	अणु .n = "trng_clk", .id = 53 पूर्ण,
	अणु .n = "macb0_clk", .id = 54 पूर्ण,
	अणु .n = "macb1_clk", .id = 55 पूर्ण,
	अणु .n = "fuse_clk", .id = 57 पूर्ण,
	अणु .n = "securam_clk", .id = 59 पूर्ण,
	अणु .n = "smd_clk", .id = 61 पूर्ण,
	अणु .n = "twi3_clk", .id = 62 पूर्ण,
	अणु .n = "catb_clk", .id = 63 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *n;
	u8 id;
पूर्ण sama5d4_periphck[] = अणु
	अणु .n = "dma0_clk", .id = 8 पूर्ण,
	अणु .n = "cpkcc_clk", .id = 10 पूर्ण,
	अणु .n = "aesb_clk", .id = 13 पूर्ण,
	अणु .n = "mpddr_clk", .id = 16 पूर्ण,
	अणु .n = "matrix0_clk", .id = 18 पूर्ण,
	अणु .n = "vdec_clk", .id = 19 पूर्ण,
	अणु .n = "dma1_clk", .id = 50 पूर्ण,
	अणु .n = "lcdc_clk", .id = 51 पूर्ण,
	अणु .n = "isi_clk", .id = 52 पूर्ण,
पूर्ण;

अटल व्योम __init sama5d4_pmc_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_range range = CLK_RANGE(0, 0);
	स्थिर अक्षर *slck_name, *मुख्यxtal_name;
	काष्ठा pmc_data *sama5d4_pmc;
	स्थिर अक्षर *parent_names[5];
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

	sama5d4_pmc = pmc_data_allocate(PMC_PLLACK + 1,
					nck(sama5d4_प्रणालीck),
					nck(sama5d4_periph32ck), 0, 3);
	अगर (!sama5d4_pmc)
		वापस;

	hw = at91_clk_रेजिस्टर_मुख्य_rc_osc(regmap, "main_rc_osc", 12000000,
					   100000000);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	bypass = of_property_पढ़ो_bool(np, "atmel,osc-bypass");

	hw = at91_clk_रेजिस्टर_मुख्य_osc(regmap, "main_osc", मुख्यxtal_name,
					bypass);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	parent_names[0] = "main_rc_osc";
	parent_names[1] = "main_osc";
	hw = at91_clk_रेजिस्टर_sam9x5_मुख्य(regmap, "mainck", parent_names, 2);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_pll(regmap, "pllack", "mainck", 0,
				   &sama5d3_pll_layout, &plla_अक्षरacteristics);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_plद_भाग(regmap, "plladivck", "pllack");
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sama5d4_pmc->chws[PMC_PLLACK] = hw;

	hw = at91_clk_रेजिस्टर_uपंचांगi(regmap, शून्य, "utmick", "mainck");
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sama5d4_pmc->chws[PMC_UTMI] = hw;

	parent_names[0] = slck_name;
	parent_names[1] = "mainck";
	parent_names[2] = "plladivck";
	parent_names[3] = "utmick";
	hw = at91_clk_रेजिस्टर_master_pres(regmap, "masterck_pres", 4,
					   parent_names,
					   &at91sam9x5_master_layout,
					   &mck_अक्षरacteristics, &mck_lock,
					   CLK_SET_RATE_GATE, पूर्णांक_न्यून);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_master_भाग(regmap, "masterck_div",
					  "masterck_pres",
					  &at91sam9x5_master_layout,
					  &mck_अक्षरacteristics, &mck_lock,
					  CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sama5d4_pmc->chws[PMC_MCK] = hw;

	hw = at91_clk_रेजिस्टर_h32mx(regmap, "h32mxck", "masterck_div");
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	sama5d4_pmc->chws[PMC_MCK2] = hw;

	parent_names[0] = "plladivck";
	parent_names[1] = "utmick";
	hw = at91sam9x5_clk_रेजिस्टर_usb(regmap, "usbck", parent_names, 2);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	parent_names[0] = "plladivck";
	parent_names[1] = "utmick";
	hw = at91sam9x5_clk_रेजिस्टर_smd(regmap, "smdclk", parent_names, 2);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	parent_names[0] = slck_name;
	parent_names[1] = "mainck";
	parent_names[2] = "plladivck";
	parent_names[3] = "utmick";
	parent_names[4] = "masterck_div";
	क्रम (i = 0; i < 3; i++) अणु
		अक्षर name[6];

		snम_लिखो(name, माप(name), "prog%d", i);

		hw = at91_clk_रेजिस्टर_programmable(regmap, name,
						    parent_names, 5, i,
						    &at91sam9x5_programmable_layout,
						    शून्य);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sama5d4_pmc->pchws[i] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sama5d4_प्रणालीck); i++) अणु
		hw = at91_clk_रेजिस्टर_प्रणाली(regmap, sama5d4_प्रणालीck[i].n,
					      sama5d4_प्रणालीck[i].p,
					      sama5d4_प्रणालीck[i].id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sama5d4_pmc->shws[sama5d4_प्रणालीck[i].id] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sama5d4_periphck); i++) अणु
		hw = at91_clk_रेजिस्टर_sam9x5_peripheral(regmap, &pmc_pcr_lock,
							 &sama5d4_pcr_layout,
							 sama5d4_periphck[i].n,
							 "masterck_div",
							 sama5d4_periphck[i].id,
							 &range, पूर्णांक_न्यून);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sama5d4_pmc->phws[sama5d4_periphck[i].id] = hw;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sama5d4_periph32ck); i++) अणु
		hw = at91_clk_रेजिस्टर_sam9x5_peripheral(regmap, &pmc_pcr_lock,
							 &sama5d4_pcr_layout,
							 sama5d4_periph32ck[i].n,
							 "h32mxck",
							 sama5d4_periph32ck[i].id,
							 &range, पूर्णांक_न्यून);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		sama5d4_pmc->phws[sama5d4_periph32ck[i].id] = hw;
	पूर्ण

	of_clk_add_hw_provider(np, of_clk_hw_pmc_get, sama5d4_pmc);

	वापस;

err_मुक्त:
	kमुक्त(sama5d4_pmc);
पूर्ण

CLK_OF_DECLARE(sama5d4_pmc, "atmel,sama5d4-pmc", sama5d4_pmc_setup);
