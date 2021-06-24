<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/at91.h>

#समावेश "pmc.h"

काष्ठा sck अणु
	अक्षर *n;
	अक्षर *p;
	u8 id;
पूर्ण;

काष्ठा pck अणु
	अक्षर *n;
	u8 id;
पूर्ण;

काष्ठा at91sam926x_data अणु
	स्थिर काष्ठा clk_pll_layout *plla_layout;
	स्थिर काष्ठा clk_pll_अक्षरacteristics *plla_अक्षरacteristics;
	स्थिर काष्ठा clk_pll_layout *pllb_layout;
	स्थिर काष्ठा clk_pll_अक्षरacteristics *pllb_अक्षरacteristics;
	स्थिर काष्ठा clk_master_अक्षरacteristics *mck_अक्षरacteristics;
	स्थिर काष्ठा sck *sck;
	स्थिर काष्ठा pck *pck;
	u8 num_sck;
	u8 num_pck;
	u8 num_progck;
	bool has_slck;
पूर्ण;

अटल DEFINE_SPINLOCK(at91sam9260_mck_lock);

अटल स्थिर काष्ठा clk_master_अक्षरacteristics sam9260_mck_अक्षरacteristics = अणु
	.output = अणु .min = 0, .max = 105000000 पूर्ण,
	.भागisors = अणु 1, 2, 4, 0 पूर्ण,
पूर्ण;

अटल u8 sam9260_plla_out[] = अणु 0, 2 पूर्ण;

अटल u16 sam9260_plla_icpll[] = अणु 1, 1 पूर्ण;

अटल स्थिर काष्ठा clk_range sam9260_plla_outमाला_दो[] = अणु
	अणु .min = 80000000, .max = 160000000 पूर्ण,
	अणु .min = 150000000, .max = 240000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics sam9260_plla_अक्षरacteristics = अणु
	.input = अणु .min = 1000000, .max = 32000000 पूर्ण,
	.num_output = ARRAY_SIZE(sam9260_plla_outमाला_दो),
	.output = sam9260_plla_outमाला_दो,
	.icpll = sam9260_plla_icpll,
	.out = sam9260_plla_out,
पूर्ण;

अटल u8 sam9260_pllb_out[] = अणु 1 पूर्ण;

अटल u16 sam9260_pllb_icpll[] = अणु 1 पूर्ण;

अटल स्थिर काष्ठा clk_range sam9260_pllb_outमाला_दो[] = अणु
	अणु .min = 70000000, .max = 130000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics sam9260_pllb_अक्षरacteristics = अणु
	.input = अणु .min = 1000000, .max = 5000000 पूर्ण,
	.num_output = ARRAY_SIZE(sam9260_pllb_outमाला_दो),
	.output = sam9260_pllb_outमाला_दो,
	.icpll = sam9260_pllb_icpll,
	.out = sam9260_pllb_out,
पूर्ण;

अटल स्थिर काष्ठा sck at91sam9260_प्रणालीck[] = अणु
	अणु .n = "uhpck", .p = "usbck",    .id = 6 पूर्ण,
	अणु .n = "udpck", .p = "usbck",    .id = 7 पूर्ण,
	अणु .n = "pck0",  .p = "prog0",    .id = 8 पूर्ण,
	अणु .n = "pck1",  .p = "prog1",    .id = 9 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pck at91sam9260_periphck[] = अणु
	अणु .n = "pioA_clk",   .id = 2 पूर्ण,
	अणु .n = "pioB_clk",   .id = 3 पूर्ण,
	अणु .n = "pioC_clk",   .id = 4 पूर्ण,
	अणु .n = "adc_clk",    .id = 5 पूर्ण,
	अणु .n = "usart0_clk", .id = 6 पूर्ण,
	अणु .n = "usart1_clk", .id = 7 पूर्ण,
	अणु .n = "usart2_clk", .id = 8 पूर्ण,
	अणु .n = "mci0_clk",   .id = 9 पूर्ण,
	अणु .n = "udc_clk",    .id = 10 पूर्ण,
	अणु .n = "twi0_clk",   .id = 11 पूर्ण,
	अणु .n = "spi0_clk",   .id = 12 पूर्ण,
	अणु .n = "spi1_clk",   .id = 13 पूर्ण,
	अणु .n = "ssc0_clk",   .id = 14 पूर्ण,
	अणु .n = "tc0_clk",    .id = 17 पूर्ण,
	अणु .n = "tc1_clk",    .id = 18 पूर्ण,
	अणु .n = "tc2_clk",    .id = 19 पूर्ण,
	अणु .n = "ohci_clk",   .id = 20 पूर्ण,
	अणु .n = "macb0_clk",  .id = 21 पूर्ण,
	अणु .n = "isi_clk",    .id = 22 पूर्ण,
	अणु .n = "usart3_clk", .id = 23 पूर्ण,
	अणु .n = "uart0_clk",  .id = 24 पूर्ण,
	अणु .n = "uart1_clk",  .id = 25 पूर्ण,
	अणु .n = "tc3_clk",    .id = 26 पूर्ण,
	अणु .n = "tc4_clk",    .id = 27 पूर्ण,
	अणु .n = "tc5_clk",    .id = 28 पूर्ण,
पूर्ण;

अटल काष्ठा at91sam926x_data at91sam9260_data = अणु
	.plla_layout = &at91rm9200_pll_layout,
	.plla_अक्षरacteristics = &sam9260_plla_अक्षरacteristics,
	.pllb_layout = &at91rm9200_pll_layout,
	.pllb_अक्षरacteristics = &sam9260_pllb_अक्षरacteristics,
	.mck_अक्षरacteristics = &sam9260_mck_अक्षरacteristics,
	.sck = at91sam9260_प्रणालीck,
	.num_sck = ARRAY_SIZE(at91sam9260_प्रणालीck),
	.pck = at91sam9260_periphck,
	.num_pck = ARRAY_SIZE(at91sam9260_periphck),
	.num_progck = 2,
	.has_slck = true,
पूर्ण;

अटल स्थिर काष्ठा clk_master_अक्षरacteristics sam9g20_mck_अक्षरacteristics = अणु
	.output = अणु .min = 0, .max = 133000000 पूर्ण,
	.भागisors = अणु 1, 2, 4, 6 पूर्ण,
पूर्ण;

अटल u8 sam9g20_plla_out[] = अणु 0, 1, 2, 3, 0, 1, 2, 3 पूर्ण;

अटल u16 sam9g20_plla_icpll[] = अणु 0, 0, 0, 0, 1, 1, 1, 1 पूर्ण;

अटल स्थिर काष्ठा clk_range sam9g20_plla_outमाला_दो[] = अणु
	अणु .min = 745000000, .max = 800000000 पूर्ण,
	अणु .min = 695000000, .max = 750000000 पूर्ण,
	अणु .min = 645000000, .max = 700000000 पूर्ण,
	अणु .min = 595000000, .max = 650000000 पूर्ण,
	अणु .min = 545000000, .max = 600000000 पूर्ण,
	अणु .min = 495000000, .max = 550000000 पूर्ण,
	अणु .min = 445000000, .max = 500000000 पूर्ण,
	अणु .min = 400000000, .max = 450000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics sam9g20_plla_अक्षरacteristics = अणु
	.input = अणु .min = 2000000, .max = 32000000 पूर्ण,
	.num_output = ARRAY_SIZE(sam9g20_plla_outमाला_दो),
	.output = sam9g20_plla_outमाला_दो,
	.icpll = sam9g20_plla_icpll,
	.out = sam9g20_plla_out,
पूर्ण;

अटल u8 sam9g20_pllb_out[] = अणु 0 पूर्ण;

अटल u16 sam9g20_pllb_icpll[] = अणु 0 पूर्ण;

अटल स्थिर काष्ठा clk_range sam9g20_pllb_outमाला_दो[] = अणु
	अणु .min = 30000000, .max = 100000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics sam9g20_pllb_अक्षरacteristics = अणु
	.input = अणु .min = 2000000, .max = 32000000 पूर्ण,
	.num_output = ARRAY_SIZE(sam9g20_pllb_outमाला_दो),
	.output = sam9g20_pllb_outमाला_दो,
	.icpll = sam9g20_pllb_icpll,
	.out = sam9g20_pllb_out,
पूर्ण;

अटल काष्ठा at91sam926x_data at91sam9g20_data = अणु
	.plla_layout = &at91sam9g45_pll_layout,
	.plla_अक्षरacteristics = &sam9g20_plla_अक्षरacteristics,
	.pllb_layout = &at91sam9g20_pllb_layout,
	.pllb_अक्षरacteristics = &sam9g20_pllb_अक्षरacteristics,
	.mck_अक्षरacteristics = &sam9g20_mck_अक्षरacteristics,
	.sck = at91sam9260_प्रणालीck,
	.num_sck = ARRAY_SIZE(at91sam9260_प्रणालीck),
	.pck = at91sam9260_periphck,
	.num_pck = ARRAY_SIZE(at91sam9260_periphck),
	.num_progck = 2,
	.has_slck = true,
पूर्ण;

अटल स्थिर काष्ठा clk_master_अक्षरacteristics sam9261_mck_अक्षरacteristics = अणु
	.output = अणु .min = 0, .max = 94000000 पूर्ण,
	.भागisors = अणु 1, 2, 4, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_range sam9261_plla_outमाला_दो[] = अणु
	अणु .min = 80000000, .max = 200000000 पूर्ण,
	अणु .min = 190000000, .max = 240000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics sam9261_plla_अक्षरacteristics = अणु
	.input = अणु .min = 1000000, .max = 32000000 पूर्ण,
	.num_output = ARRAY_SIZE(sam9261_plla_outमाला_दो),
	.output = sam9261_plla_outमाला_दो,
	.icpll = sam9260_plla_icpll,
	.out = sam9260_plla_out,
पूर्ण;

अटल u8 sam9261_pllb_out[] = अणु 1 पूर्ण;

अटल u16 sam9261_pllb_icpll[] = अणु 1 पूर्ण;

अटल स्थिर काष्ठा clk_range sam9261_pllb_outमाला_दो[] = अणु
	अणु .min = 70000000, .max = 130000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics sam9261_pllb_अक्षरacteristics = अणु
	.input = अणु .min = 1000000, .max = 5000000 पूर्ण,
	.num_output = ARRAY_SIZE(sam9261_pllb_outमाला_दो),
	.output = sam9261_pllb_outमाला_दो,
	.icpll = sam9261_pllb_icpll,
	.out = sam9261_pllb_out,
पूर्ण;

अटल स्थिर काष्ठा sck at91sam9261_प्रणालीck[] = अणु
	अणु .n = "uhpck", .p = "usbck",    .id = 6 पूर्ण,
	अणु .n = "udpck", .p = "usbck",    .id = 7 पूर्ण,
	अणु .n = "pck0",  .p = "prog0",    .id = 8 पूर्ण,
	अणु .n = "pck1",  .p = "prog1",    .id = 9 पूर्ण,
	अणु .n = "pck2",  .p = "prog2",    .id = 10 पूर्ण,
	अणु .n = "pck3",  .p = "prog3",    .id = 11 पूर्ण,
	अणु .n = "hclk0", .p = "masterck_div", .id = 16 पूर्ण,
	अणु .n = "hclk1", .p = "masterck_div", .id = 17 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pck at91sam9261_periphck[] = अणु
	अणु .n = "pioA_clk",   .id = 2, पूर्ण,
	अणु .n = "pioB_clk",   .id = 3, पूर्ण,
	अणु .n = "pioC_clk",   .id = 4, पूर्ण,
	अणु .n = "usart0_clk", .id = 6, पूर्ण,
	अणु .n = "usart1_clk", .id = 7, पूर्ण,
	अणु .n = "usart2_clk", .id = 8, पूर्ण,
	अणु .n = "mci0_clk",   .id = 9, पूर्ण,
	अणु .n = "udc_clk",    .id = 10, पूर्ण,
	अणु .n = "twi0_clk",   .id = 11, पूर्ण,
	अणु .n = "spi0_clk",   .id = 12, पूर्ण,
	अणु .n = "spi1_clk",   .id = 13, पूर्ण,
	अणु .n = "ssc0_clk",   .id = 14, पूर्ण,
	अणु .n = "ssc1_clk",   .id = 15, पूर्ण,
	अणु .n = "ssc2_clk",   .id = 16, पूर्ण,
	अणु .n = "tc0_clk",    .id = 17, पूर्ण,
	अणु .n = "tc1_clk",    .id = 18, पूर्ण,
	अणु .n = "tc2_clk",    .id = 19, पूर्ण,
	अणु .n = "ohci_clk",   .id = 20, पूर्ण,
	अणु .n = "lcd_clk",    .id = 21, पूर्ण,
पूर्ण;

अटल काष्ठा at91sam926x_data at91sam9261_data = अणु
	.plla_layout = &at91rm9200_pll_layout,
	.plla_अक्षरacteristics = &sam9261_plla_अक्षरacteristics,
	.pllb_layout = &at91rm9200_pll_layout,
	.pllb_अक्षरacteristics = &sam9261_pllb_अक्षरacteristics,
	.mck_अक्षरacteristics = &sam9261_mck_अक्षरacteristics,
	.sck = at91sam9261_प्रणालीck,
	.num_sck = ARRAY_SIZE(at91sam9261_प्रणालीck),
	.pck = at91sam9261_periphck,
	.num_pck = ARRAY_SIZE(at91sam9261_periphck),
	.num_progck = 4,
पूर्ण;

अटल स्थिर काष्ठा clk_master_अक्षरacteristics sam9263_mck_अक्षरacteristics = अणु
	.output = अणु .min = 0, .max = 120000000 पूर्ण,
	.भागisors = अणु 1, 2, 4, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_range sam9263_pll_outमाला_दो[] = अणु
	अणु .min = 80000000, .max = 200000000 पूर्ण,
	अणु .min = 190000000, .max = 240000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_pll_अक्षरacteristics sam9263_pll_अक्षरacteristics = अणु
	.input = अणु .min = 1000000, .max = 32000000 पूर्ण,
	.num_output = ARRAY_SIZE(sam9263_pll_outमाला_दो),
	.output = sam9263_pll_outमाला_दो,
	.icpll = sam9260_plla_icpll,
	.out = sam9260_plla_out,
पूर्ण;

अटल स्थिर काष्ठा sck at91sam9263_प्रणालीck[] = अणु
	अणु .n = "uhpck", .p = "usbck",    .id = 6 पूर्ण,
	अणु .n = "udpck", .p = "usbck",    .id = 7 पूर्ण,
	अणु .n = "pck0",  .p = "prog0",    .id = 8 पूर्ण,
	अणु .n = "pck1",  .p = "prog1",    .id = 9 पूर्ण,
	अणु .n = "pck2",  .p = "prog2",    .id = 10 पूर्ण,
	अणु .n = "pck3",  .p = "prog3",    .id = 11 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pck at91sam9263_periphck[] = अणु
	अणु .n = "pioA_clk",   .id = 2, पूर्ण,
	अणु .n = "pioB_clk",   .id = 3, पूर्ण,
	अणु .n = "pioCDE_clk", .id = 4, पूर्ण,
	अणु .n = "usart0_clk", .id = 7, पूर्ण,
	अणु .n = "usart1_clk", .id = 8, पूर्ण,
	अणु .n = "usart2_clk", .id = 9, पूर्ण,
	अणु .n = "mci0_clk",   .id = 10, पूर्ण,
	अणु .n = "mci1_clk",   .id = 11, पूर्ण,
	अणु .n = "can_clk",    .id = 12, पूर्ण,
	अणु .n = "twi0_clk",   .id = 13, पूर्ण,
	अणु .n = "spi0_clk",   .id = 14, पूर्ण,
	अणु .n = "spi1_clk",   .id = 15, पूर्ण,
	अणु .n = "ssc0_clk",   .id = 16, पूर्ण,
	अणु .n = "ssc1_clk",   .id = 17, पूर्ण,
	अणु .n = "ac97_clk",   .id = 18, पूर्ण,
	अणु .n = "tcb_clk",    .id = 19, पूर्ण,
	अणु .n = "pwm_clk",    .id = 20, पूर्ण,
	अणु .n = "macb0_clk",  .id = 21, पूर्ण,
	अणु .n = "g2de_clk",   .id = 23, पूर्ण,
	अणु .n = "udc_clk",    .id = 24, पूर्ण,
	अणु .n = "isi_clk",    .id = 25, पूर्ण,
	अणु .n = "lcd_clk",    .id = 26, पूर्ण,
	अणु .n = "dma_clk",    .id = 27, पूर्ण,
	अणु .n = "ohci_clk",   .id = 29, पूर्ण,
पूर्ण;

अटल काष्ठा at91sam926x_data at91sam9263_data = अणु
	.plla_layout = &at91rm9200_pll_layout,
	.plla_अक्षरacteristics = &sam9263_pll_अक्षरacteristics,
	.pllb_layout = &at91rm9200_pll_layout,
	.pllb_अक्षरacteristics = &sam9263_pll_अक्षरacteristics,
	.mck_अक्षरacteristics = &sam9263_mck_अक्षरacteristics,
	.sck = at91sam9263_प्रणालीck,
	.num_sck = ARRAY_SIZE(at91sam9263_प्रणालीck),
	.pck = at91sam9263_periphck,
	.num_pck = ARRAY_SIZE(at91sam9263_periphck),
	.num_progck = 4,
पूर्ण;

अटल व्योम __init at91sam926x_pmc_setup(काष्ठा device_node *np,
					 काष्ठा at91sam926x_data *data)
अणु
	स्थिर अक्षर *slowxtal_name, *मुख्यxtal_name;
	काष्ठा pmc_data *at91sam9260_pmc;
	u32 usb_भाग[] = अणु 1, 2, 4, 0 पूर्ण;
	स्थिर अक्षर *parent_names[6];
	स्थिर अक्षर *slck_name;
	काष्ठा regmap *regmap;
	काष्ठा clk_hw *hw;
	पूर्णांक i;
	bool bypass;

	i = of_property_match_string(np, "clock-names", "slow_xtal");
	अगर (i < 0)
		वापस;

	slowxtal_name = of_clk_get_parent_name(np, i);

	i = of_property_match_string(np, "clock-names", "main_xtal");
	अगर (i < 0)
		वापस;
	मुख्यxtal_name = of_clk_get_parent_name(np, i);

	regmap = device_node_to_regmap(np);
	अगर (IS_ERR(regmap))
		वापस;

	at91sam9260_pmc = pmc_data_allocate(PMC_PLLBCK + 1,
					    ndck(data->sck, data->num_sck),
					    ndck(data->pck, data->num_pck),
					    0, data->num_progck);
	अगर (!at91sam9260_pmc)
		वापस;

	bypass = of_property_पढ़ो_bool(np, "atmel,osc-bypass");

	hw = at91_clk_रेजिस्टर_मुख्य_osc(regmap, "main_osc", मुख्यxtal_name,
					bypass);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_rm9200_मुख्य(regmap, "mainck", "main_osc");
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9260_pmc->chws[PMC_MAIN] = hw;

	अगर (data->has_slck) अणु
		hw = clk_hw_रेजिस्टर_fixed_rate_with_accuracy(शून्य,
							      "slow_rc_osc",
							      शून्य, 0, 32768,
							      50000000);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		parent_names[0] = "slow_rc_osc";
		parent_names[1] = "slow_xtal";
		hw = at91_clk_रेजिस्टर_sam9260_slow(regmap, "slck",
						    parent_names, 2);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9260_pmc->chws[PMC_SLOW] = hw;
		slck_name = "slck";
	पूर्ण अन्यथा अणु
		slck_name = slowxtal_name;
	पूर्ण

	hw = at91_clk_रेजिस्टर_pll(regmap, "pllack", "mainck", 0,
				   data->plla_layout,
				   data->plla_अक्षरacteristics);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9260_pmc->chws[PMC_PLLACK] = hw;

	hw = at91_clk_रेजिस्टर_pll(regmap, "pllbck", "mainck", 1,
				   data->pllb_layout,
				   data->pllb_अक्षरacteristics);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9260_pmc->chws[PMC_PLLBCK] = hw;

	parent_names[0] = slck_name;
	parent_names[1] = "mainck";
	parent_names[2] = "pllack";
	parent_names[3] = "pllbck";
	hw = at91_clk_रेजिस्टर_master_pres(regmap, "masterck_pres", 4,
					   parent_names,
					   &at91rm9200_master_layout,
					   data->mck_अक्षरacteristics,
					   &at91sam9260_mck_lock,
					   CLK_SET_RATE_GATE, पूर्णांक_न्यून);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	hw = at91_clk_रेजिस्टर_master_भाग(regmap, "masterck_div",
					  "masterck_pres",
					  &at91rm9200_master_layout,
					  data->mck_अक्षरacteristics,
					  &at91sam9260_mck_lock,
					  CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	at91sam9260_pmc->chws[PMC_MCK] = hw;

	hw = at91rm9200_clk_रेजिस्टर_usb(regmap, "usbck", "pllbck", usb_भाग);
	अगर (IS_ERR(hw))
		जाओ err_मुक्त;

	parent_names[0] = slck_name;
	parent_names[1] = "mainck";
	parent_names[2] = "pllack";
	parent_names[3] = "pllbck";
	क्रम (i = 0; i < data->num_progck; i++) अणु
		अक्षर name[6];

		snम_लिखो(name, माप(name), "prog%d", i);

		hw = at91_clk_रेजिस्टर_programmable(regmap, name,
						    parent_names, 4, i,
						    &at91rm9200_programmable_layout,
						    शून्य);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9260_pmc->pchws[i] = hw;
	पूर्ण

	क्रम (i = 0; i < data->num_sck; i++) अणु
		hw = at91_clk_रेजिस्टर_प्रणाली(regmap, data->sck[i].n,
					      data->sck[i].p,
					      data->sck[i].id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9260_pmc->shws[data->sck[i].id] = hw;
	पूर्ण

	क्रम (i = 0; i < data->num_pck; i++) अणु
		hw = at91_clk_रेजिस्टर_peripheral(regmap,
						  data->pck[i].n,
						  "masterck_div",
						  data->pck[i].id);
		अगर (IS_ERR(hw))
			जाओ err_मुक्त;

		at91sam9260_pmc->phws[data->pck[i].id] = hw;
	पूर्ण

	of_clk_add_hw_provider(np, of_clk_hw_pmc_get, at91sam9260_pmc);

	वापस;

err_मुक्त:
	kमुक्त(at91sam9260_pmc);
पूर्ण

अटल व्योम __init at91sam9260_pmc_setup(काष्ठा device_node *np)
अणु
	at91sam926x_pmc_setup(np, &at91sam9260_data);
पूर्ण

CLK_OF_DECLARE(at91sam9260_pmc, "atmel,at91sam9260-pmc", at91sam9260_pmc_setup);

अटल व्योम __init at91sam9261_pmc_setup(काष्ठा device_node *np)
अणु
	at91sam926x_pmc_setup(np, &at91sam9261_data);
पूर्ण

CLK_OF_DECLARE(at91sam9261_pmc, "atmel,at91sam9261-pmc", at91sam9261_pmc_setup);

अटल व्योम __init at91sam9263_pmc_setup(काष्ठा device_node *np)
अणु
	at91sam926x_pmc_setup(np, &at91sam9263_data);
पूर्ण

CLK_OF_DECLARE(at91sam9263_pmc, "atmel,at91sam9263-pmc", at91sam9263_pmc_setup);

अटल व्योम __init at91sam9g20_pmc_setup(काष्ठा device_node *np)
अणु
	at91sam926x_pmc_setup(np, &at91sam9g20_data);
पूर्ण

CLK_OF_DECLARE(at91sam9g20_pmc, "atmel,at91sam9g20-pmc", at91sam9g20_pmc_setup);
