<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/clk/at91/pmc.h
 *
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#अगर_अघोषित __PMC_H_
#घोषणा __PMC_H_

#समावेश <linux/पन.स>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>

बाह्य spinlock_t pmc_pcr_lock;

काष्ठा pmc_data अणु
	अचिन्हित पूर्णांक ncore;
	काष्ठा clk_hw **chws;
	अचिन्हित पूर्णांक nप्रणाली;
	काष्ठा clk_hw **shws;
	अचिन्हित पूर्णांक nperiph;
	काष्ठा clk_hw **phws;
	अचिन्हित पूर्णांक ngck;
	काष्ठा clk_hw **ghws;
	अचिन्हित पूर्णांक npck;
	काष्ठा clk_hw **pchws;

	काष्ठा clk_hw *hwtable[];
पूर्ण;

काष्ठा clk_range अणु
	अचिन्हित दीर्घ min;
	अचिन्हित दीर्घ max;
पूर्ण;

#घोषणा CLK_RANGE(MIN, MAX) अणु.min = MIN, .max = MAX,पूर्ण

काष्ठा clk_master_layout अणु
	u32 offset;
	u32 mask;
	u8 pres_shअगरt;
पूर्ण;

बाह्य स्थिर काष्ठा clk_master_layout at91rm9200_master_layout;
बाह्य स्थिर काष्ठा clk_master_layout at91sam9x5_master_layout;

काष्ठा clk_master_अक्षरacteristics अणु
	काष्ठा clk_range output;
	u32 भागisors[5];
	u8 have_भाग3_pres;
पूर्ण;

काष्ठा clk_pll_layout अणु
	u32 pllr_mask;
	u32 mul_mask;
	u32 frac_mask;
	u32 भाग_mask;
	u32 enभाग_mask;
	u8 mul_shअगरt;
	u8 frac_shअगरt;
	u8 भाग_shअगरt;
	u8 enभाग_shअगरt;
पूर्ण;

बाह्य स्थिर काष्ठा clk_pll_layout at91rm9200_pll_layout;
बाह्य स्थिर काष्ठा clk_pll_layout at91sam9g45_pll_layout;
बाह्य स्थिर काष्ठा clk_pll_layout at91sam9g20_pllb_layout;
बाह्य स्थिर काष्ठा clk_pll_layout sama5d3_pll_layout;

काष्ठा clk_pll_अक्षरacteristics अणु
	काष्ठा clk_range input;
	पूर्णांक num_output;
	स्थिर काष्ठा clk_range *output;
	u16 *icpll;
	u8 *out;
	u8 upll : 1;
पूर्ण;

काष्ठा clk_programmable_layout अणु
	u8 pres_mask;
	u8 pres_shअगरt;
	u8 css_mask;
	u8 have_slck_mck;
	u8 is_pres_direct;
पूर्ण;

बाह्य स्थिर काष्ठा clk_programmable_layout at91rm9200_programmable_layout;
बाह्य स्थिर काष्ठा clk_programmable_layout at91sam9g45_programmable_layout;
बाह्य स्थिर काष्ठा clk_programmable_layout at91sam9x5_programmable_layout;

काष्ठा clk_pcr_layout अणु
	u32 offset;
	u32 cmd;
	u32 भाग_mask;
	u32 gckcss_mask;
	u32 pid_mask;
पूर्ण;

#घोषणा field_get(_mask, _reg) (((_reg) & (_mask)) >> (ffs(_mask) - 1))
#घोषणा field_prep(_mask, _val) (((_val) << (ffs(_mask) - 1)) & (_mask))

#घोषणा ndck(a, s) (a[s - 1].id + 1)
#घोषणा nck(a) (a[ARRAY_SIZE(a) - 1].id + 1)
काष्ठा pmc_data *pmc_data_allocate(अचिन्हित पूर्णांक ncore, अचिन्हित पूर्णांक nप्रणाली,
				   अचिन्हित पूर्णांक nperiph, अचिन्हित पूर्णांक ngck,
				   अचिन्हित पूर्णांक npck);

पूर्णांक of_at91_get_clk_range(काष्ठा device_node *np, स्थिर अक्षर *propname,
			  काष्ठा clk_range *range);

काष्ठा clk_hw *of_clk_hw_pmc_get(काष्ठा of_phandle_args *clkspec, व्योम *data);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_audio_pll_frac(काष्ठा regmap *regmap, स्थिर अक्षर *name,
				 स्थिर अक्षर *parent_name);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_audio_pll_pad(काष्ठा regmap *regmap, स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_audio_pll_pmc(काष्ठा regmap *regmap, स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_generated(काष्ठा regmap *regmap, spinlock_t *lock,
			    स्थिर काष्ठा clk_pcr_layout *layout,
			    स्थिर अक्षर *name, स्थिर अक्षर **parent_names,
			    u32 *mux_table, u8 num_parents, u8 id,
			    स्थिर काष्ठा clk_range *range, पूर्णांक chg_pid);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_h32mx(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name);

काष्ठा clk_hw * __init
at91_clk_i2s_mux_रेजिस्टर(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			  स्थिर अक्षर * स्थिर *parent_names,
			  अचिन्हित पूर्णांक num_parents, u8 bus_id);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_मुख्य_rc_osc(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			      u32 frequency, u32 accuracy);
काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_मुख्य_osc(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			   स्थिर अक्षर *parent_name, bool bypass);
काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_rm9200_मुख्य(काष्ठा regmap *regmap,
			      स्थिर अक्षर *name,
			      स्थिर अक्षर *parent_name);
काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_sam9x5_मुख्य(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			      स्थिर अक्षर **parent_names, पूर्णांक num_parents);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_master_pres(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			      पूर्णांक num_parents, स्थिर अक्षर **parent_names,
			      स्थिर काष्ठा clk_master_layout *layout,
			      स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics,
			      spinlock_t *lock, u32 flags, पूर्णांक chg_pid);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_master_भाग(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			     स्थिर अक्षर *parent_names,
			     स्थिर काष्ठा clk_master_layout *layout,
			     स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics,
			     spinlock_t *lock, u32 flags);

काष्ठा clk_hw * __init
at91_clk_sama7g5_रेजिस्टर_master(काष्ठा regmap *regmap,
				 स्थिर अक्षर *name, पूर्णांक num_parents,
				 स्थिर अक्षर **parent_names, u32 *mux_table,
				 spinlock_t *lock, u8 id, bool critical,
				 पूर्णांक chg_pid);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_peripheral(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			     स्थिर अक्षर *parent_name, u32 id);
काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_sam9x5_peripheral(काष्ठा regmap *regmap, spinlock_t *lock,
				    स्थिर काष्ठा clk_pcr_layout *layout,
				    स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				    u32 id, स्थिर काष्ठा clk_range *range,
				    पूर्णांक chg_pid);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_pll(काष्ठा regmap *regmap, स्थिर अक्षर *name,
		      स्थिर अक्षर *parent_name, u8 id,
		      स्थिर काष्ठा clk_pll_layout *layout,
		      स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics);
काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_plद_भाग(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			 स्थिर अक्षर *parent_name);

काष्ठा clk_hw * __init
sam9x60_clk_रेजिस्टर_भाग_pll(काष्ठा regmap *regmap, spinlock_t *lock,
			     स्थिर अक्षर *name, स्थिर अक्षर *parent_name, u8 id,
			     स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics,
			     स्थिर काष्ठा clk_pll_layout *layout, u32 flags);

काष्ठा clk_hw * __init
sam9x60_clk_रेजिस्टर_frac_pll(काष्ठा regmap *regmap, spinlock_t *lock,
			      स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			      काष्ठा clk_hw *parent_hw, u8 id,
			      स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics,
			      स्थिर काष्ठा clk_pll_layout *layout, u32 flags);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_programmable(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			       स्थिर अक्षर **parent_names, u8 num_parents, u8 id,
			       स्थिर काष्ठा clk_programmable_layout *layout,
			       u32 *mux_table);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_sam9260_slow(काष्ठा regmap *regmap,
			       स्थिर अक्षर *name,
			       स्थिर अक्षर **parent_names,
			       पूर्णांक num_parents);

काष्ठा clk_hw * __init
at91sam9x5_clk_रेजिस्टर_smd(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			    स्थिर अक्षर **parent_names, u8 num_parents);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_प्रणाली(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			 स्थिर अक्षर *parent_name, u8 id);

काष्ठा clk_hw * __init
at91sam9x5_clk_रेजिस्टर_usb(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			    स्थिर अक्षर **parent_names, u8 num_parents);
काष्ठा clk_hw * __init
at91sam9n12_clk_रेजिस्टर_usb(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			     स्थिर अक्षर *parent_name);
काष्ठा clk_hw * __init
sam9x60_clk_रेजिस्टर_usb(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			 स्थिर अक्षर **parent_names, u8 num_parents);
काष्ठा clk_hw * __init
at91rm9200_clk_रेजिस्टर_usb(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			    स्थिर अक्षर *parent_name, स्थिर u32 *भागisors);

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_uपंचांगi(काष्ठा regmap *regmap_pmc, काष्ठा regmap *regmap_sfr,
		       स्थिर अक्षर *name, स्थिर अक्षर *parent_name);

काष्ठा clk_hw * __init
at91_clk_sama7g5_रेजिस्टर_uपंचांगi(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			       स्थिर अक्षर *parent_name);

#अगर_घोषित CONFIG_PM
व्योम pmc_रेजिस्टर_id(u8 id);
व्योम pmc_रेजिस्टर_pck(u8 pck);
#अन्यथा
अटल अंतरभूत व्योम pmc_रेजिस्टर_id(u8 id) अणुपूर्ण
अटल अंतरभूत व्योम pmc_रेजिस्टर_pck(u8 pck) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __PMC_H_ */
