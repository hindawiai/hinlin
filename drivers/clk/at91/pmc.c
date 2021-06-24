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
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/syscore_ops.h>

#समावेश <यंत्र/proc-fns.h>

#समावेश <dt-bindings/घड़ी/at91.h>

#समावेश "pmc.h"

#घोषणा PMC_MAX_IDS 128
#घोषणा PMC_MAX_PCKS 8

पूर्णांक of_at91_get_clk_range(काष्ठा device_node *np, स्थिर अक्षर *propname,
			  काष्ठा clk_range *range)
अणु
	u32 min, max;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32_index(np, propname, 0, &min);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u32_index(np, propname, 1, &max);
	अगर (ret)
		वापस ret;

	अगर (range) अणु
		range->min = min;
		range->max = max;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_at91_get_clk_range);

काष्ठा clk_hw *of_clk_hw_pmc_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	अचिन्हित पूर्णांक type = clkspec->args[0];
	अचिन्हित पूर्णांक idx = clkspec->args[1];
	काष्ठा pmc_data *pmc_data = data;

	चयन (type) अणु
	हाल PMC_TYPE_CORE:
		अगर (idx < pmc_data->ncore)
			वापस pmc_data->chws[idx];
		अवरोध;
	हाल PMC_TYPE_SYSTEM:
		अगर (idx < pmc_data->nप्रणाली)
			वापस pmc_data->shws[idx];
		अवरोध;
	हाल PMC_TYPE_PERIPHERAL:
		अगर (idx < pmc_data->nperiph)
			वापस pmc_data->phws[idx];
		अवरोध;
	हाल PMC_TYPE_GCK:
		अगर (idx < pmc_data->ngck)
			वापस pmc_data->ghws[idx];
		अवरोध;
	हाल PMC_TYPE_PROGRAMMABLE:
		अगर (idx < pmc_data->npck)
			वापस pmc_data->pchws[idx];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	pr_err("%s: invalid type (%u) or index (%u)\n", __func__, type, idx);

	वापस ERR_PTR(-EINVAL);
पूर्ण

काष्ठा pmc_data *pmc_data_allocate(अचिन्हित पूर्णांक ncore, अचिन्हित पूर्णांक nप्रणाली,
				   अचिन्हित पूर्णांक nperiph, अचिन्हित पूर्णांक ngck,
				   अचिन्हित पूर्णांक npck)
अणु
	अचिन्हित पूर्णांक num_clks = ncore + nप्रणाली + nperiph + ngck + npck;
	काष्ठा pmc_data *pmc_data;

	pmc_data = kzalloc(काष्ठा_size(pmc_data, hwtable, num_clks),
			   GFP_KERNEL);
	अगर (!pmc_data)
		वापस शून्य;

	pmc_data->ncore = ncore;
	pmc_data->chws = pmc_data->hwtable;

	pmc_data->nप्रणाली = nप्रणाली;
	pmc_data->shws = pmc_data->chws + ncore;

	pmc_data->nperiph = nperiph;
	pmc_data->phws = pmc_data->shws + nप्रणाली;

	pmc_data->ngck = ngck;
	pmc_data->ghws = pmc_data->phws + nperiph;

	pmc_data->npck = npck;
	pmc_data->pchws = pmc_data->ghws + ngck;

	वापस pmc_data;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल काष्ठा regmap *pmcreg;

अटल u8 रेजिस्टरed_ids[PMC_MAX_IDS];
अटल u8 रेजिस्टरed_pcks[PMC_MAX_PCKS];

अटल काष्ठा
अणु
	u32 scsr;
	u32 pcsr0;
	u32 uckr;
	u32 mor;
	u32 mcfr;
	u32 pllar;
	u32 mckr;
	u32 usb;
	u32 imr;
	u32 pcsr1;
	u32 pcr[PMC_MAX_IDS];
	u32 audio_pll0;
	u32 audio_pll1;
	u32 pckr[PMC_MAX_PCKS];
पूर्ण pmc_cache;

/*
 * As Peripheral ID 0 is invalid on AT91 chips, the identअगरier is stored
 * without alteration in the table, and 0 is क्रम unused घड़ीs.
 */
व्योम pmc_रेजिस्टर_id(u8 id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PMC_MAX_IDS; i++) अणु
		अगर (रेजिस्टरed_ids[i] == 0) अणु
			रेजिस्टरed_ids[i] = id;
			अवरोध;
		पूर्ण
		अगर (रेजिस्टरed_ids[i] == id)
			अवरोध;
	पूर्ण
पूर्ण

/*
 * As Programmable Clock 0 is valid on AT91 chips, there is an offset
 * of 1 between the stored value and the real घड़ी ID.
 */
व्योम pmc_रेजिस्टर_pck(u8 pck)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PMC_MAX_PCKS; i++) अणु
		अगर (रेजिस्टरed_pcks[i] == 0) अणु
			रेजिस्टरed_pcks[i] = pck + 1;
			अवरोध;
		पूर्ण
		अगर (रेजिस्टरed_pcks[i] == (pck + 1))
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pmc_suspend(व्योम)
अणु
	पूर्णांक i;
	u8 num;

	regmap_पढ़ो(pmcreg, AT91_PMC_SCSR, &pmc_cache.scsr);
	regmap_पढ़ो(pmcreg, AT91_PMC_PCSR, &pmc_cache.pcsr0);
	regmap_पढ़ो(pmcreg, AT91_CKGR_UCKR, &pmc_cache.uckr);
	regmap_पढ़ो(pmcreg, AT91_CKGR_MOR, &pmc_cache.mor);
	regmap_पढ़ो(pmcreg, AT91_CKGR_MCFR, &pmc_cache.mcfr);
	regmap_पढ़ो(pmcreg, AT91_CKGR_PLLAR, &pmc_cache.pllar);
	regmap_पढ़ो(pmcreg, AT91_PMC_MCKR, &pmc_cache.mckr);
	regmap_पढ़ो(pmcreg, AT91_PMC_USB, &pmc_cache.usb);
	regmap_पढ़ो(pmcreg, AT91_PMC_IMR, &pmc_cache.imr);
	regmap_पढ़ो(pmcreg, AT91_PMC_PCSR1, &pmc_cache.pcsr1);

	क्रम (i = 0; रेजिस्टरed_ids[i]; i++) अणु
		regmap_ग_लिखो(pmcreg, AT91_PMC_PCR,
			     (रेजिस्टरed_ids[i] & AT91_PMC_PCR_PID_MASK));
		regmap_पढ़ो(pmcreg, AT91_PMC_PCR,
			    &pmc_cache.pcr[रेजिस्टरed_ids[i]]);
	पूर्ण
	क्रम (i = 0; रेजिस्टरed_pcks[i]; i++) अणु
		num = रेजिस्टरed_pcks[i] - 1;
		regmap_पढ़ो(pmcreg, AT91_PMC_PCKR(num), &pmc_cache.pckr[num]);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool pmc_पढ़ोy(अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(pmcreg, AT91_PMC_SR, &status);

	वापस ((status & mask) == mask) ? 1 : 0;
पूर्ण

अटल व्योम pmc_resume(व्योम)
अणु
	पूर्णांक i;
	u8 num;
	u32 पंचांगp;
	u32 mask = AT91_PMC_MCKRDY | AT91_PMC_LOCKA;

	regmap_पढ़ो(pmcreg, AT91_PMC_MCKR, &पंचांगp);
	अगर (pmc_cache.mckr != पंचांगp)
		pr_warn("MCKR was not configured properly by the firmware\n");
	regmap_पढ़ो(pmcreg, AT91_CKGR_PLLAR, &पंचांगp);
	अगर (pmc_cache.pllar != पंचांगp)
		pr_warn("PLLAR was not configured properly by the firmware\n");

	regmap_ग_लिखो(pmcreg, AT91_PMC_SCER, pmc_cache.scsr);
	regmap_ग_लिखो(pmcreg, AT91_PMC_PCER, pmc_cache.pcsr0);
	regmap_ग_लिखो(pmcreg, AT91_CKGR_UCKR, pmc_cache.uckr);
	regmap_ग_लिखो(pmcreg, AT91_CKGR_MOR, pmc_cache.mor);
	regmap_ग_लिखो(pmcreg, AT91_CKGR_MCFR, pmc_cache.mcfr);
	regmap_ग_लिखो(pmcreg, AT91_PMC_USB, pmc_cache.usb);
	regmap_ग_लिखो(pmcreg, AT91_PMC_IMR, pmc_cache.imr);
	regmap_ग_लिखो(pmcreg, AT91_PMC_PCER1, pmc_cache.pcsr1);

	क्रम (i = 0; रेजिस्टरed_ids[i]; i++) अणु
		regmap_ग_लिखो(pmcreg, AT91_PMC_PCR,
			     pmc_cache.pcr[रेजिस्टरed_ids[i]] |
			     AT91_PMC_PCR_CMD);
	पूर्ण
	क्रम (i = 0; रेजिस्टरed_pcks[i]; i++) अणु
		num = रेजिस्टरed_pcks[i] - 1;
		regmap_ग_लिखो(pmcreg, AT91_PMC_PCKR(num), pmc_cache.pckr[num]);
	पूर्ण

	अगर (pmc_cache.uckr & AT91_PMC_UPLLEN)
		mask |= AT91_PMC_LOCKU;

	जबतक (!pmc_पढ़ोy(mask))
		cpu_relax();
पूर्ण

अटल काष्ठा syscore_ops pmc_syscore_ops = अणु
	.suspend = pmc_suspend,
	.resume = pmc_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sama5d2_pmc_dt_ids[] = अणु
	अणु .compatible = "atmel,sama5d2-pmc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init pmc_रेजिस्टर_ops(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_matching_node(शून्य, sama5d2_pmc_dt_ids);
	अगर (!np)
		वापस -ENODEV;

	pmcreg = device_node_to_regmap(np);
	of_node_put(np);
	अगर (IS_ERR(pmcreg))
		वापस PTR_ERR(pmcreg);

	रेजिस्टर_syscore_ops(&pmc_syscore_ops);

	वापस 0;
पूर्ण
/* This has to happen beक्रमe arch_initcall because of the tcb_clksrc driver */
postcore_initcall(pmc_रेजिस्टर_ops);
#पूर्ण_अगर
