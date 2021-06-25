<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

#घोषणा SAM9X5_USB_DIV_SHIFT	8
#घोषणा SAM9X5_USB_MAX_DIV	0xf

#घोषणा RM9200_USB_DIV_SHIFT	28
#घोषणा RM9200_USB_DIV_TAB_SIZE	4

#घोषणा SAM9X5_USBS_MASK	GENMASK(0, 0)
#घोषणा SAM9X60_USBS_MASK	GENMASK(1, 0)

काष्ठा at91sam9x5_clk_usb अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u32 usbs_mask;
	u8 num_parents;
पूर्ण;

#घोषणा to_at91sam9x5_clk_usb(hw) \
	container_of(hw, काष्ठा at91sam9x5_clk_usb, hw)

काष्ठा at91rm9200_clk_usb अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u32 भागisors[4];
पूर्ण;

#घोषणा to_at91rm9200_clk_usb(hw) \
	container_of(hw, काष्ठा at91rm9200_clk_usb, hw)

अटल अचिन्हित दीर्घ at91sam9x5_clk_usb_recalc_rate(काष्ठा clk_hw *hw,
						    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा at91sam9x5_clk_usb *usb = to_at91sam9x5_clk_usb(hw);
	अचिन्हित पूर्णांक usbr;
	u8 usbभाग;

	regmap_पढ़ो(usb->regmap, AT91_PMC_USB, &usbr);
	usbभाग = (usbr & AT91_PMC_OHCIUSBDIV) >> SAM9X5_USB_DIV_SHIFT;

	वापस DIV_ROUND_CLOSEST(parent_rate, (usbभाग + 1));
पूर्ण

अटल पूर्णांक at91sam9x5_clk_usb_determine_rate(काष्ठा clk_hw *hw,
					     काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_hw *parent;
	दीर्घ best_rate = -EINVAL;
	अचिन्हित दीर्घ पंचांगp_rate;
	पूर्णांक best_dअगरf = -1;
	पूर्णांक पंचांगp_dअगरf;
	पूर्णांक i;

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		पूर्णांक भाग;

		parent = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent)
			जारी;

		क्रम (भाग = 1; भाग < SAM9X5_USB_MAX_DIV + 2; भाग++) अणु
			अचिन्हित दीर्घ पंचांगp_parent_rate;

			पंचांगp_parent_rate = req->rate * भाग;
			पंचांगp_parent_rate = clk_hw_round_rate(parent,
							   पंचांगp_parent_rate);
			अगर (!पंचांगp_parent_rate)
				जारी;

			पंचांगp_rate = DIV_ROUND_CLOSEST(पंचांगp_parent_rate, भाग);
			अगर (पंचांगp_rate < req->rate)
				पंचांगp_dअगरf = req->rate - पंचांगp_rate;
			अन्यथा
				पंचांगp_dअगरf = पंचांगp_rate - req->rate;

			अगर (best_dअगरf < 0 || best_dअगरf > पंचांगp_dअगरf) अणु
				best_rate = पंचांगp_rate;
				best_dअगरf = पंचांगp_dअगरf;
				req->best_parent_rate = पंचांगp_parent_rate;
				req->best_parent_hw = parent;
			पूर्ण

			अगर (!best_dअगरf || पंचांगp_rate < req->rate)
				अवरोध;
		पूर्ण

		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण

	अगर (best_rate < 0)
		वापस best_rate;

	req->rate = best_rate;
	वापस 0;
पूर्ण

अटल पूर्णांक at91sam9x5_clk_usb_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा at91sam9x5_clk_usb *usb = to_at91sam9x5_clk_usb(hw);

	अगर (index >= usb->num_parents)
		वापस -EINVAL;

	regmap_update_bits(usb->regmap, AT91_PMC_USB, usb->usbs_mask, index);

	वापस 0;
पूर्ण

अटल u8 at91sam9x5_clk_usb_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा at91sam9x5_clk_usb *usb = to_at91sam9x5_clk_usb(hw);
	अचिन्हित पूर्णांक usbr;

	regmap_पढ़ो(usb->regmap, AT91_PMC_USB, &usbr);

	वापस usbr & usb->usbs_mask;
पूर्ण

अटल पूर्णांक at91sam9x5_clk_usb_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा at91sam9x5_clk_usb *usb = to_at91sam9x5_clk_usb(hw);
	अचिन्हित दीर्घ भाग;

	अगर (!rate)
		वापस -EINVAL;

	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर (भाग > SAM9X5_USB_MAX_DIV + 1 || !भाग)
		वापस -EINVAL;

	regmap_update_bits(usb->regmap, AT91_PMC_USB, AT91_PMC_OHCIUSBDIV,
			   (भाग - 1) << SAM9X5_USB_DIV_SHIFT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops at91sam9x5_usb_ops = अणु
	.recalc_rate = at91sam9x5_clk_usb_recalc_rate,
	.determine_rate = at91sam9x5_clk_usb_determine_rate,
	.get_parent = at91sam9x5_clk_usb_get_parent,
	.set_parent = at91sam9x5_clk_usb_set_parent,
	.set_rate = at91sam9x5_clk_usb_set_rate,
पूर्ण;

अटल पूर्णांक at91sam9n12_clk_usb_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा at91sam9x5_clk_usb *usb = to_at91sam9x5_clk_usb(hw);

	regmap_update_bits(usb->regmap, AT91_PMC_USB, AT91_PMC_USBS,
			   AT91_PMC_USBS);

	वापस 0;
पूर्ण

अटल व्योम at91sam9n12_clk_usb_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा at91sam9x5_clk_usb *usb = to_at91sam9x5_clk_usb(hw);

	regmap_update_bits(usb->regmap, AT91_PMC_USB, AT91_PMC_USBS, 0);
पूर्ण

अटल पूर्णांक at91sam9n12_clk_usb_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा at91sam9x5_clk_usb *usb = to_at91sam9x5_clk_usb(hw);
	अचिन्हित पूर्णांक usbr;

	regmap_पढ़ो(usb->regmap, AT91_PMC_USB, &usbr);

	वापस usbr & AT91_PMC_USBS;
पूर्ण

अटल स्थिर काष्ठा clk_ops at91sam9n12_usb_ops = अणु
	.enable = at91sam9n12_clk_usb_enable,
	.disable = at91sam9n12_clk_usb_disable,
	.is_enabled = at91sam9n12_clk_usb_is_enabled,
	.recalc_rate = at91sam9x5_clk_usb_recalc_rate,
	.determine_rate = at91sam9x5_clk_usb_determine_rate,
	.set_rate = at91sam9x5_clk_usb_set_rate,
पूर्ण;

अटल काष्ठा clk_hw * __init
_at91sam9x5_clk_रेजिस्टर_usb(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			     स्थिर अक्षर **parent_names, u8 num_parents,
			     u32 usbs_mask)
अणु
	काष्ठा at91sam9x5_clk_usb *usb;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	usb = kzalloc(माप(*usb), GFP_KERNEL);
	अगर (!usb)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &at91sam9x5_usb_ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE |
		     CLK_SET_RATE_PARENT;

	usb->hw.init = &init;
	usb->regmap = regmap;
	usb->usbs_mask = usbs_mask;
	usb->num_parents = num_parents;

	hw = &usb->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &usb->hw);
	अगर (ret) अणु
		kमुक्त(usb);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

काष्ठा clk_hw * __init
at91sam9x5_clk_रेजिस्टर_usb(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			    स्थिर अक्षर **parent_names, u8 num_parents)
अणु
	वापस _at91sam9x5_clk_रेजिस्टर_usb(regmap, name, parent_names,
					    num_parents, SAM9X5_USBS_MASK);
पूर्ण

काष्ठा clk_hw * __init
sam9x60_clk_रेजिस्टर_usb(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			 स्थिर अक्षर **parent_names, u8 num_parents)
अणु
	वापस _at91sam9x5_clk_रेजिस्टर_usb(regmap, name, parent_names,
					    num_parents, SAM9X60_USBS_MASK);
पूर्ण

काष्ठा clk_hw * __init
at91sam9n12_clk_रेजिस्टर_usb(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			     स्थिर अक्षर *parent_name)
अणु
	काष्ठा at91sam9x5_clk_usb *usb;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	usb = kzalloc(माप(*usb), GFP_KERNEL);
	अगर (!usb)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &at91sam9n12_usb_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_RATE_PARENT;

	usb->hw.init = &init;
	usb->regmap = regmap;

	hw = &usb->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &usb->hw);
	अगर (ret) अणु
		kमुक्त(usb);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल अचिन्हित दीर्घ at91rm9200_clk_usb_recalc_rate(काष्ठा clk_hw *hw,
						    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा at91rm9200_clk_usb *usb = to_at91rm9200_clk_usb(hw);
	अचिन्हित पूर्णांक pllbr;
	u8 usbभाग;

	regmap_पढ़ो(usb->regmap, AT91_CKGR_PLLBR, &pllbr);

	usbभाग = (pllbr & AT91_PMC_USBDIV) >> RM9200_USB_DIV_SHIFT;
	अगर (usb->भागisors[usbभाग])
		वापस parent_rate / usb->भागisors[usbभाग];

	वापस 0;
पूर्ण

अटल दीर्घ at91rm9200_clk_usb_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					  अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा at91rm9200_clk_usb *usb = to_at91rm9200_clk_usb(hw);
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	अचिन्हित दीर्घ bestrate = 0;
	पूर्णांक bestdअगरf = -1;
	अचिन्हित दीर्घ पंचांगprate;
	पूर्णांक पंचांगpdअगरf;
	पूर्णांक i = 0;

	क्रम (i = 0; i < RM9200_USB_DIV_TAB_SIZE; i++) अणु
		अचिन्हित दीर्घ पंचांगp_parent_rate;

		अगर (!usb->भागisors[i])
			जारी;

		पंचांगp_parent_rate = rate * usb->भागisors[i];
		पंचांगp_parent_rate = clk_hw_round_rate(parent, पंचांगp_parent_rate);
		पंचांगprate = DIV_ROUND_CLOSEST(पंचांगp_parent_rate, usb->भागisors[i]);
		अगर (पंचांगprate < rate)
			पंचांगpdअगरf = rate - पंचांगprate;
		अन्यथा
			पंचांगpdअगरf = पंचांगprate - rate;

		अगर (bestdअगरf < 0 || bestdअगरf > पंचांगpdअगरf) अणु
			bestrate = पंचांगprate;
			bestdअगरf = पंचांगpdअगरf;
			*parent_rate = पंचांगp_parent_rate;
		पूर्ण

		अगर (!bestdअगरf)
			अवरोध;
	पूर्ण

	वापस bestrate;
पूर्ण

अटल पूर्णांक at91rm9200_clk_usb_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक i;
	काष्ठा at91rm9200_clk_usb *usb = to_at91rm9200_clk_usb(hw);
	अचिन्हित दीर्घ भाग;

	अगर (!rate)
		वापस -EINVAL;

	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);

	क्रम (i = 0; i < RM9200_USB_DIV_TAB_SIZE; i++) अणु
		अगर (usb->भागisors[i] == भाग) अणु
			regmap_update_bits(usb->regmap, AT91_CKGR_PLLBR,
					   AT91_PMC_USBDIV,
					   i << RM9200_USB_DIV_SHIFT);

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops at91rm9200_usb_ops = अणु
	.recalc_rate = at91rm9200_clk_usb_recalc_rate,
	.round_rate = at91rm9200_clk_usb_round_rate,
	.set_rate = at91rm9200_clk_usb_set_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91rm9200_clk_रेजिस्टर_usb(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			    स्थिर अक्षर *parent_name, स्थिर u32 *भागisors)
अणु
	काष्ठा at91rm9200_clk_usb *usb;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	usb = kzalloc(माप(*usb), GFP_KERNEL);
	अगर (!usb)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &at91rm9200_usb_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_PARENT;

	usb->hw.init = &init;
	usb->regmap = regmap;
	स_नकल(usb->भागisors, भागisors, माप(usb->भागisors));

	hw = &usb->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &usb->hw);
	अगर (ret) अणु
		kमुक्त(usb);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
