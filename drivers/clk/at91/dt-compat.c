<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "pmc.h"

#घोषणा MASTER_SOURCE_MAX	4

#घोषणा PERIPHERAL_AT91RM9200	0
#घोषणा PERIPHERAL_AT91SAM9X5	1

#घोषणा PERIPHERAL_MAX		64

#घोषणा PERIPHERAL_ID_MIN	2

#घोषणा PROG_SOURCE_MAX		5
#घोषणा PROG_ID_MAX		7

#घोषणा SYSTEM_MAX_ID		31

#घोषणा GCK_INDEX_DT_AUDIO_PLL	5

अटल DEFINE_SPINLOCK(mck_lock);

#अगर_घोषित CONFIG_HAVE_AT91_AUDIO_PLL
अटल व्योम __init of_sama5d2_clk_audio_pll_frac_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *name = np->name;
	स्थिर अक्षर *parent_name;
	काष्ठा regmap *regmap;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	parent_name = of_clk_get_parent_name(np, 0);

	hw = at91_clk_रेजिस्टर_audio_pll_frac(regmap, name, parent_name);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(of_sama5d2_clk_audio_pll_frac_setup,
	       "atmel,sama5d2-clk-audio-pll-frac",
	       of_sama5d2_clk_audio_pll_frac_setup);

अटल व्योम __init of_sama5d2_clk_audio_pll_pad_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *name = np->name;
	स्थिर अक्षर *parent_name;
	काष्ठा regmap *regmap;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	parent_name = of_clk_get_parent_name(np, 0);

	hw = at91_clk_रेजिस्टर_audio_pll_pad(regmap, name, parent_name);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(of_sama5d2_clk_audio_pll_pad_setup,
	       "atmel,sama5d2-clk-audio-pll-pad",
	       of_sama5d2_clk_audio_pll_pad_setup);

अटल व्योम __init of_sama5d2_clk_audio_pll_pmc_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *name = np->name;
	स्थिर अक्षर *parent_name;
	काष्ठा regmap *regmap;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	parent_name = of_clk_get_parent_name(np, 0);

	hw = at91_clk_रेजिस्टर_audio_pll_pmc(regmap, name, parent_name);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(of_sama5d2_clk_audio_pll_pmc_setup,
	       "atmel,sama5d2-clk-audio-pll-pmc",
	       of_sama5d2_clk_audio_pll_pmc_setup);
#पूर्ण_अगर /* CONFIG_HAVE_AT91_AUDIO_PLL */

अटल स्थिर काष्ठा clk_pcr_layout dt_pcr_layout = अणु
	.offset = 0x10c,
	.cmd = BIT(12),
	.pid_mask = GENMASK(5, 0),
	.भाग_mask = GENMASK(17, 16),
	.gckcss_mask = GENMASK(10, 8),
पूर्ण;

#अगर_घोषित CONFIG_HAVE_AT91_GENERATED_CLK
#घोषणा GENERATED_SOURCE_MAX	6

#घोषणा GCK_ID_I2S0		54
#घोषणा GCK_ID_I2S1		55
#घोषणा GCK_ID_CLASSD		59

अटल व्योम __init of_sama5d2_clk_generated_setup(काष्ठा device_node *np)
अणु
	पूर्णांक num;
	u32 id;
	स्थिर अक्षर *name;
	काष्ठा clk_hw *hw;
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर *parent_names[GENERATED_SOURCE_MAX];
	काष्ठा device_node *gcknp;
	काष्ठा clk_range range = CLK_RANGE(0, 0);
	काष्ठा regmap *regmap;

	num_parents = of_clk_get_parent_count(np);
	अगर (num_parents == 0 || num_parents > GENERATED_SOURCE_MAX)
		वापस;

	of_clk_parent_fill(np, parent_names, num_parents);

	num = of_get_child_count(np);
	अगर (!num || num > PERIPHERAL_MAX)
		वापस;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	क्रम_each_child_of_node(np, gcknp) अणु
		पूर्णांक chg_pid = पूर्णांक_न्यून;

		अगर (of_property_पढ़ो_u32(gcknp, "reg", &id))
			जारी;

		अगर (id < PERIPHERAL_ID_MIN || id >= PERIPHERAL_MAX)
			जारी;

		अगर (of_property_पढ़ो_string(np, "clock-output-names", &name))
			name = gcknp->name;

		of_at91_get_clk_range(gcknp, "atmel,clk-output-range",
				      &range);

		अगर (of_device_is_compatible(np, "atmel,sama5d2-clk-generated") &&
		    (id == GCK_ID_I2S0 || id == GCK_ID_I2S1 ||
		     id == GCK_ID_CLASSD))
			chg_pid = GCK_INDEX_DT_AUDIO_PLL;

		hw = at91_clk_रेजिस्टर_generated(regmap, &pmc_pcr_lock,
						 &dt_pcr_layout, name,
						 parent_names, शून्य,
						 num_parents, id, &range,
						 chg_pid);
		अगर (IS_ERR(hw))
			जारी;

		of_clk_add_hw_provider(gcknp, of_clk_hw_simple_get, hw);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(of_sama5d2_clk_generated_setup, "atmel,sama5d2-clk-generated",
	       of_sama5d2_clk_generated_setup);
#पूर्ण_अगर /* CONFIG_HAVE_AT91_GENERATED_CLK */

#अगर_घोषित CONFIG_HAVE_AT91_H32MX
अटल व्योम __init of_sama5d4_clk_h32mx_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *name = np->name;
	स्थिर अक्षर *parent_name;
	काष्ठा regmap *regmap;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	parent_name = of_clk_get_parent_name(np, 0);

	hw = at91_clk_रेजिस्टर_h32mx(regmap, name, parent_name);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(of_sama5d4_clk_h32mx_setup, "atmel,sama5d4-clk-h32mx",
	       of_sama5d4_clk_h32mx_setup);
#पूर्ण_अगर /* CONFIG_HAVE_AT91_H32MX */

#अगर_घोषित CONFIG_HAVE_AT91_I2S_MUX_CLK
#घोषणा	I2S_BUS_NR	2

अटल व्योम __init of_sama5d2_clk_i2s_mux_setup(काष्ठा device_node *np)
अणु
	काष्ठा regmap *regmap_sfr;
	u8 bus_id;
	स्थिर अक्षर *parent_names[2];
	काष्ठा device_node *i2s_mux_np;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	regmap_sfr = syscon_regmap_lookup_by_compatible("atmel,sama5d2-sfr");
	अगर (IS_ERR(regmap_sfr))
		वापस;

	क्रम_each_child_of_node(np, i2s_mux_np) अणु
		अगर (of_property_पढ़ो_u8(i2s_mux_np, "reg", &bus_id))
			जारी;

		अगर (bus_id > I2S_BUS_NR)
			जारी;

		ret = of_clk_parent_fill(i2s_mux_np, parent_names, 2);
		अगर (ret != 2)
			जारी;

		hw = at91_clk_i2s_mux_रेजिस्टर(regmap_sfr, i2s_mux_np->name,
					       parent_names, 2, bus_id);
		अगर (IS_ERR(hw))
			जारी;

		of_clk_add_hw_provider(i2s_mux_np, of_clk_hw_simple_get, hw);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(sama5d2_clk_i2s_mux, "atmel,sama5d2-clk-i2s-mux",
	       of_sama5d2_clk_i2s_mux_setup);
#पूर्ण_अगर /* CONFIG_HAVE_AT91_I2S_MUX_CLK */

अटल व्योम __init of_at91rm9200_clk_मुख्य_osc_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *name = np->name;
	स्थिर अक्षर *parent_name;
	काष्ठा regmap *regmap;
	bool bypass;

	of_property_पढ़ो_string(np, "clock-output-names", &name);
	bypass = of_property_पढ़ो_bool(np, "atmel,osc-bypass");
	parent_name = of_clk_get_parent_name(np, 0);

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	hw = at91_clk_रेजिस्टर_मुख्य_osc(regmap, name, parent_name, bypass);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91rm9200_clk_मुख्य_osc, "atmel,at91rm9200-clk-main-osc",
	       of_at91rm9200_clk_मुख्य_osc_setup);

अटल व्योम __init of_at91sam9x5_clk_मुख्य_rc_osc_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	u32 frequency = 0;
	u32 accuracy = 0;
	स्थिर अक्षर *name = np->name;
	काष्ठा regmap *regmap;

	of_property_पढ़ो_string(np, "clock-output-names", &name);
	of_property_पढ़ो_u32(np, "clock-frequency", &frequency);
	of_property_पढ़ो_u32(np, "clock-accuracy", &accuracy);

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	hw = at91_clk_रेजिस्टर_मुख्य_rc_osc(regmap, name, frequency, accuracy);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_मुख्य_rc_osc, "atmel,at91sam9x5-clk-main-rc-osc",
	       of_at91sam9x5_clk_मुख्य_rc_osc_setup);

अटल व्योम __init of_at91rm9200_clk_मुख्य_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर *name = np->name;
	काष्ठा regmap *regmap;

	parent_name = of_clk_get_parent_name(np, 0);
	of_property_पढ़ो_string(np, "clock-output-names", &name);

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	hw = at91_clk_रेजिस्टर_rm9200_मुख्य(regmap, name, parent_name);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91rm9200_clk_मुख्य, "atmel,at91rm9200-clk-main",
	       of_at91rm9200_clk_मुख्य_setup);

अटल व्योम __init of_at91sam9x5_clk_मुख्य_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *parent_names[2];
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर *name = np->name;
	काष्ठा regmap *regmap;

	num_parents = of_clk_get_parent_count(np);
	अगर (num_parents == 0 || num_parents > 2)
		वापस;

	of_clk_parent_fill(np, parent_names, num_parents);
	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	hw = at91_clk_रेजिस्टर_sam9x5_मुख्य(regmap, name, parent_names,
					   num_parents);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_मुख्य, "atmel,at91sam9x5-clk-main",
	       of_at91sam9x5_clk_मुख्य_setup);

अटल काष्ठा clk_master_अक्षरacteristics * __init
of_at91_clk_master_get_अक्षरacteristics(काष्ठा device_node *np)
अणु
	काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics;

	अक्षरacteristics = kzalloc(माप(*अक्षरacteristics), GFP_KERNEL);
	अगर (!अक्षरacteristics)
		वापस शून्य;

	अगर (of_at91_get_clk_range(np, "atmel,clk-output-range", &अक्षरacteristics->output))
		जाओ out_मुक्त_अक्षरacteristics;

	of_property_पढ़ो_u32_array(np, "atmel,clk-divisors",
				   अक्षरacteristics->भागisors, 4);

	अक्षरacteristics->have_भाग3_pres =
		of_property_पढ़ो_bool(np, "atmel,master-clk-have-div3-pres");

	वापस अक्षरacteristics;

out_मुक्त_अक्षरacteristics:
	kमुक्त(अक्षरacteristics);
	वापस शून्य;
पूर्ण

अटल व्योम __init
of_at91_clk_master_setup(काष्ठा device_node *np,
			 स्थिर काष्ठा clk_master_layout *layout)
अणु
	काष्ठा clk_hw *hw;
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर *parent_names[MASTER_SOURCE_MAX];
	स्थिर अक्षर *name = np->name;
	काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics;
	काष्ठा regmap *regmap;

	num_parents = of_clk_get_parent_count(np);
	अगर (num_parents == 0 || num_parents > MASTER_SOURCE_MAX)
		वापस;

	of_clk_parent_fill(np, parent_names, num_parents);

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	अक्षरacteristics = of_at91_clk_master_get_अक्षरacteristics(np);
	अगर (!अक्षरacteristics)
		वापस;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	hw = at91_clk_रेजिस्टर_master_pres(regmap, "masterck_pres", num_parents,
					   parent_names, layout,
					   अक्षरacteristics, &mck_lock,
					   CLK_SET_RATE_GATE, पूर्णांक_न्यून);
	अगर (IS_ERR(hw))
		जाओ out_मुक्त_अक्षरacteristics;

	hw = at91_clk_रेजिस्टर_master_भाग(regmap, name, "masterck_pres",
					  layout, अक्षरacteristics,
					  &mck_lock, CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		जाओ out_मुक्त_अक्षरacteristics;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
	वापस;

out_मुक्त_अक्षरacteristics:
	kमुक्त(अक्षरacteristics);
पूर्ण

अटल व्योम __init of_at91rm9200_clk_master_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_master_setup(np, &at91rm9200_master_layout);
पूर्ण
CLK_OF_DECLARE(at91rm9200_clk_master, "atmel,at91rm9200-clk-master",
	       of_at91rm9200_clk_master_setup);

अटल व्योम __init of_at91sam9x5_clk_master_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_master_setup(np, &at91sam9x5_master_layout);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_master, "atmel,at91sam9x5-clk-master",
	       of_at91sam9x5_clk_master_setup);

अटल व्योम __init
of_at91_clk_periph_setup(काष्ठा device_node *np, u8 type)
अणु
	पूर्णांक num;
	u32 id;
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर *name;
	काष्ठा device_node *periphclknp;
	काष्ठा regmap *regmap;

	parent_name = of_clk_get_parent_name(np, 0);
	अगर (!parent_name)
		वापस;

	num = of_get_child_count(np);
	अगर (!num || num > PERIPHERAL_MAX)
		वापस;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	क्रम_each_child_of_node(np, periphclknp) अणु
		अगर (of_property_पढ़ो_u32(periphclknp, "reg", &id))
			जारी;

		अगर (id >= PERIPHERAL_MAX)
			जारी;

		अगर (of_property_पढ़ो_string(np, "clock-output-names", &name))
			name = periphclknp->name;

		अगर (type == PERIPHERAL_AT91RM9200) अणु
			hw = at91_clk_रेजिस्टर_peripheral(regmap, name,
							  parent_name, id);
		पूर्ण अन्यथा अणु
			काष्ठा clk_range range = CLK_RANGE(0, 0);

			of_at91_get_clk_range(periphclknp,
					      "atmel,clk-output-range",
					      &range);

			hw = at91_clk_रेजिस्टर_sam9x5_peripheral(regmap,
								 &pmc_pcr_lock,
								 &dt_pcr_layout,
								 name,
								 parent_name,
								 id, &range,
								 पूर्णांक_न्यून);
		पूर्ण

		अगर (IS_ERR(hw))
			जारी;

		of_clk_add_hw_provider(periphclknp, of_clk_hw_simple_get, hw);
	पूर्ण
पूर्ण

अटल व्योम __init of_at91rm9200_clk_periph_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_periph_setup(np, PERIPHERAL_AT91RM9200);
पूर्ण
CLK_OF_DECLARE(at91rm9200_clk_periph, "atmel,at91rm9200-clk-peripheral",
	       of_at91rm9200_clk_periph_setup);

अटल व्योम __init of_at91sam9x5_clk_periph_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_periph_setup(np, PERIPHERAL_AT91SAM9X5);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_periph, "atmel,at91sam9x5-clk-peripheral",
	       of_at91sam9x5_clk_periph_setup);

अटल काष्ठा clk_pll_अक्षरacteristics * __init
of_at91_clk_pll_get_अक्षरacteristics(काष्ठा device_node *np)
अणु
	पूर्णांक i;
	पूर्णांक offset;
	u32 पंचांगp;
	पूर्णांक num_output;
	u32 num_cells;
	काष्ठा clk_range input;
	काष्ठा clk_range *output;
	u8 *out = शून्य;
	u16 *icpll = शून्य;
	काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics;

	अगर (of_at91_get_clk_range(np, "atmel,clk-input-range", &input))
		वापस शून्य;

	अगर (of_property_पढ़ो_u32(np, "#atmel,pll-clk-output-range-cells",
				 &num_cells))
		वापस शून्य;

	अगर (num_cells < 2 || num_cells > 4)
		वापस शून्य;

	अगर (!of_get_property(np, "atmel,pll-clk-output-ranges", &पंचांगp))
		वापस शून्य;
	num_output = पंचांगp / (माप(u32) * num_cells);

	अक्षरacteristics = kzalloc(माप(*अक्षरacteristics), GFP_KERNEL);
	अगर (!अक्षरacteristics)
		वापस शून्य;

	output = kसुस्मृति(num_output, माप(*output), GFP_KERNEL);
	अगर (!output)
		जाओ out_मुक्त_अक्षरacteristics;

	अगर (num_cells > 2) अणु
		out = kसुस्मृति(num_output, माप(*out), GFP_KERNEL);
		अगर (!out)
			जाओ out_मुक्त_output;
	पूर्ण

	अगर (num_cells > 3) अणु
		icpll = kसुस्मृति(num_output, माप(*icpll), GFP_KERNEL);
		अगर (!icpll)
			जाओ out_मुक्त_output;
	पूर्ण

	क्रम (i = 0; i < num_output; i++) अणु
		offset = i * num_cells;
		अगर (of_property_पढ़ो_u32_index(np,
					       "atmel,pll-clk-output-ranges",
					       offset, &पंचांगp))
			जाओ out_मुक्त_output;
		output[i].min = पंचांगp;
		अगर (of_property_पढ़ो_u32_index(np,
					       "atmel,pll-clk-output-ranges",
					       offset + 1, &पंचांगp))
			जाओ out_मुक्त_output;
		output[i].max = पंचांगp;

		अगर (num_cells == 2)
			जारी;

		अगर (of_property_पढ़ो_u32_index(np,
					       "atmel,pll-clk-output-ranges",
					       offset + 2, &पंचांगp))
			जाओ out_मुक्त_output;
		out[i] = पंचांगp;

		अगर (num_cells == 3)
			जारी;

		अगर (of_property_पढ़ो_u32_index(np,
					       "atmel,pll-clk-output-ranges",
					       offset + 3, &पंचांगp))
			जाओ out_मुक्त_output;
		icpll[i] = पंचांगp;
	पूर्ण

	अक्षरacteristics->input = input;
	अक्षरacteristics->num_output = num_output;
	अक्षरacteristics->output = output;
	अक्षरacteristics->out = out;
	अक्षरacteristics->icpll = icpll;
	वापस अक्षरacteristics;

out_मुक्त_output:
	kमुक्त(icpll);
	kमुक्त(out);
	kमुक्त(output);
out_मुक्त_अक्षरacteristics:
	kमुक्त(अक्षरacteristics);
	वापस शून्य;
पूर्ण

अटल व्योम __init
of_at91_clk_pll_setup(काष्ठा device_node *np,
		      स्थिर काष्ठा clk_pll_layout *layout)
अणु
	u32 id;
	काष्ठा clk_hw *hw;
	काष्ठा regmap *regmap;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर *name = np->name;
	काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics;

	अगर (of_property_पढ़ो_u32(np, "reg", &id))
		वापस;

	parent_name = of_clk_get_parent_name(np, 0);

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	अक्षरacteristics = of_at91_clk_pll_get_अक्षरacteristics(np);
	अगर (!अक्षरacteristics)
		वापस;

	hw = at91_clk_रेजिस्टर_pll(regmap, name, parent_name, id, layout,
				   अक्षरacteristics);
	अगर (IS_ERR(hw))
		जाओ out_मुक्त_अक्षरacteristics;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
	वापस;

out_मुक्त_अक्षरacteristics:
	kमुक्त(अक्षरacteristics);
पूर्ण

अटल व्योम __init of_at91rm9200_clk_pll_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_pll_setup(np, &at91rm9200_pll_layout);
पूर्ण
CLK_OF_DECLARE(at91rm9200_clk_pll, "atmel,at91rm9200-clk-pll",
	       of_at91rm9200_clk_pll_setup);

अटल व्योम __init of_at91sam9g45_clk_pll_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_pll_setup(np, &at91sam9g45_pll_layout);
पूर्ण
CLK_OF_DECLARE(at91sam9g45_clk_pll, "atmel,at91sam9g45-clk-pll",
	       of_at91sam9g45_clk_pll_setup);

अटल व्योम __init of_at91sam9g20_clk_pllb_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_pll_setup(np, &at91sam9g20_pllb_layout);
पूर्ण
CLK_OF_DECLARE(at91sam9g20_clk_pllb, "atmel,at91sam9g20-clk-pllb",
	       of_at91sam9g20_clk_pllb_setup);

अटल व्योम __init of_sama5d3_clk_pll_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_pll_setup(np, &sama5d3_pll_layout);
पूर्ण
CLK_OF_DECLARE(sama5d3_clk_pll, "atmel,sama5d3-clk-pll",
	       of_sama5d3_clk_pll_setup);

अटल व्योम __init
of_at91sam9x5_clk_plद_भाग_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर *name = np->name;
	काष्ठा regmap *regmap;

	parent_name = of_clk_get_parent_name(np, 0);

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	hw = at91_clk_रेजिस्टर_plद_भाग(regmap, name, parent_name);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_plद_भाग, "atmel,at91sam9x5-clk-plldiv",
	       of_at91sam9x5_clk_plद_भाग_setup);

अटल व्योम __init
of_at91_clk_prog_setup(काष्ठा device_node *np,
		       स्थिर काष्ठा clk_programmable_layout *layout,
		       u32 *mux_table)
अणु
	पूर्णांक num;
	u32 id;
	काष्ठा clk_hw *hw;
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर *parent_names[PROG_SOURCE_MAX];
	स्थिर अक्षर *name;
	काष्ठा device_node *progclknp;
	काष्ठा regmap *regmap;

	num_parents = of_clk_get_parent_count(np);
	अगर (num_parents == 0 || num_parents > PROG_SOURCE_MAX)
		वापस;

	of_clk_parent_fill(np, parent_names, num_parents);

	num = of_get_child_count(np);
	अगर (!num || num > (PROG_ID_MAX + 1))
		वापस;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	क्रम_each_child_of_node(np, progclknp) अणु
		अगर (of_property_पढ़ो_u32(progclknp, "reg", &id))
			जारी;

		अगर (of_property_पढ़ो_string(np, "clock-output-names", &name))
			name = progclknp->name;

		hw = at91_clk_रेजिस्टर_programmable(regmap, name,
						    parent_names, num_parents,
						    id, layout, mux_table);
		अगर (IS_ERR(hw))
			जारी;

		of_clk_add_hw_provider(progclknp, of_clk_hw_simple_get, hw);
	पूर्ण
पूर्ण

अटल व्योम __init of_at91rm9200_clk_prog_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_prog_setup(np, &at91rm9200_programmable_layout, शून्य);
पूर्ण
CLK_OF_DECLARE(at91rm9200_clk_prog, "atmel,at91rm9200-clk-programmable",
	       of_at91rm9200_clk_prog_setup);

अटल व्योम __init of_at91sam9g45_clk_prog_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_prog_setup(np, &at91sam9g45_programmable_layout, शून्य);
पूर्ण
CLK_OF_DECLARE(at91sam9g45_clk_prog, "atmel,at91sam9g45-clk-programmable",
	       of_at91sam9g45_clk_prog_setup);

अटल व्योम __init of_at91sam9x5_clk_prog_setup(काष्ठा device_node *np)
अणु
	of_at91_clk_prog_setup(np, &at91sam9x5_programmable_layout, शून्य);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_prog, "atmel,at91sam9x5-clk-programmable",
	       of_at91sam9x5_clk_prog_setup);

अटल व्योम __init of_at91sam9260_clk_slow_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *parent_names[2];
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर *name = np->name;
	काष्ठा regmap *regmap;

	num_parents = of_clk_get_parent_count(np);
	अगर (num_parents != 2)
		वापस;

	of_clk_parent_fill(np, parent_names, num_parents);
	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	hw = at91_clk_रेजिस्टर_sam9260_slow(regmap, name, parent_names,
					    num_parents);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91sam9260_clk_slow, "atmel,at91sam9260-clk-slow",
	       of_at91sam9260_clk_slow_setup);

#अगर_घोषित CONFIG_HAVE_AT91_SMD
#घोषणा SMD_SOURCE_MAX		2

अटल व्योम __init of_at91sam9x5_clk_smd_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर *parent_names[SMD_SOURCE_MAX];
	स्थिर अक्षर *name = np->name;
	काष्ठा regmap *regmap;

	num_parents = of_clk_get_parent_count(np);
	अगर (num_parents == 0 || num_parents > SMD_SOURCE_MAX)
		वापस;

	of_clk_parent_fill(np, parent_names, num_parents);

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	hw = at91sam9x5_clk_रेजिस्टर_smd(regmap, name, parent_names,
					 num_parents);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_smd, "atmel,at91sam9x5-clk-smd",
	       of_at91sam9x5_clk_smd_setup);
#पूर्ण_अगर /* CONFIG_HAVE_AT91_SMD */

अटल व्योम __init of_at91rm9200_clk_sys_setup(काष्ठा device_node *np)
अणु
	पूर्णांक num;
	u32 id;
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *name;
	काष्ठा device_node *sysclknp;
	स्थिर अक्षर *parent_name;
	काष्ठा regmap *regmap;

	num = of_get_child_count(np);
	अगर (num > (SYSTEM_MAX_ID + 1))
		वापस;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	क्रम_each_child_of_node(np, sysclknp) अणु
		अगर (of_property_पढ़ो_u32(sysclknp, "reg", &id))
			जारी;

		अगर (of_property_पढ़ो_string(np, "clock-output-names", &name))
			name = sysclknp->name;

		parent_name = of_clk_get_parent_name(sysclknp, 0);

		hw = at91_clk_रेजिस्टर_प्रणाली(regmap, name, parent_name, id);
		अगर (IS_ERR(hw))
			जारी;

		of_clk_add_hw_provider(sysclknp, of_clk_hw_simple_get, hw);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(at91rm9200_clk_sys, "atmel,at91rm9200-clk-system",
	       of_at91rm9200_clk_sys_setup);

#अगर_घोषित CONFIG_HAVE_AT91_USB_CLK
#घोषणा USB_SOURCE_MAX		2

अटल व्योम __init of_at91sam9x5_clk_usb_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर *parent_names[USB_SOURCE_MAX];
	स्थिर अक्षर *name = np->name;
	काष्ठा regmap *regmap;

	num_parents = of_clk_get_parent_count(np);
	अगर (num_parents == 0 || num_parents > USB_SOURCE_MAX)
		वापस;

	of_clk_parent_fill(np, parent_names, num_parents);

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	hw = at91sam9x5_clk_रेजिस्टर_usb(regmap, name, parent_names,
					 num_parents);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_usb, "atmel,at91sam9x5-clk-usb",
	       of_at91sam9x5_clk_usb_setup);

अटल व्योम __init of_at91sam9n12_clk_usb_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर *name = np->name;
	काष्ठा regmap *regmap;

	parent_name = of_clk_get_parent_name(np, 0);
	अगर (!parent_name)
		वापस;

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;

	hw = at91sam9n12_clk_रेजिस्टर_usb(regmap, name, parent_name);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91sam9n12_clk_usb, "atmel,at91sam9n12-clk-usb",
	       of_at91sam9n12_clk_usb_setup);

अटल व्योम __init of_at91rm9200_clk_usb_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर *name = np->name;
	u32 भागisors[4] = अणु0, 0, 0, 0पूर्ण;
	काष्ठा regmap *regmap;

	parent_name = of_clk_get_parent_name(np, 0);
	अगर (!parent_name)
		वापस;

	of_property_पढ़ो_u32_array(np, "atmel,clk-divisors", भागisors, 4);
	अगर (!भागisors[0])
		वापस;

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap))
		वापस;
	hw = at91rm9200_clk_रेजिस्टर_usb(regmap, name, parent_name, भागisors);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91rm9200_clk_usb, "atmel,at91rm9200-clk-usb",
	       of_at91rm9200_clk_usb_setup);
#पूर्ण_अगर /* CONFIG_HAVE_AT91_USB_CLK */

#अगर_घोषित CONFIG_HAVE_AT91_UTMI
अटल व्योम __init of_at91sam9x5_clk_uपंचांगi_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर *name = np->name;
	काष्ठा regmap *regmap_pmc, *regmap_sfr;

	parent_name = of_clk_get_parent_name(np, 0);

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	regmap_pmc = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap_pmc))
		वापस;

	/*
	 * If the device supports dअगरferent मुख्यck rates, this value has to be
	 * set in the UTMI Clock Trimming रेजिस्टर.
	 * - 9x5: मुख्यck supports several rates but it is indicated that a
	 *   12 MHz is needed in हाल of USB.
	 * - sama5d3 and sama5d2: मुख्यck supports several rates. Configuring
	 *   the FREQ field of the UTMI Clock Trimming रेजिस्टर is mandatory.
	 * - sama5d4: मुख्यck is at 12 MHz.
	 *
	 * We only need to retrieve sama5d3 or sama5d2 sfr regmap.
	 */
	regmap_sfr = syscon_regmap_lookup_by_compatible("atmel,sama5d3-sfr");
	अगर (IS_ERR(regmap_sfr)) अणु
		regmap_sfr = syscon_regmap_lookup_by_compatible("atmel,sama5d2-sfr");
		अगर (IS_ERR(regmap_sfr))
			regmap_sfr = शून्य;
	पूर्ण

	hw = at91_clk_रेजिस्टर_uपंचांगi(regmap_pmc, regmap_sfr, name, parent_name);
	अगर (IS_ERR(hw))
		वापस;

	of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_uपंचांगi, "atmel,at91sam9x5-clk-utmi",
	       of_at91sam9x5_clk_uपंचांगi_setup);
#पूर्ण_अगर /* CONFIG_HAVE_AT91_UTMI */
