<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP IOMMU quirks क्रम various TI SoCs
 *
 * Copyright (C) 2015-2019 Texas Instruments Incorporated - https://www.ti.com/
 *      Suman Anna <s-anna@ti.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/list.h>

#समावेश "clockdomain.h"
#समावेश "powerdomain.h"

काष्ठा pwrdm_link अणु
	काष्ठा device *dev;
	काष्ठा घातerकरोमुख्य *pwrdm;
	काष्ठा list_head node;
पूर्ण;

अटल DEFINE_SPINLOCK(iommu_lock);
अटल काष्ठा घड़ीकरोमुख्य *emu_clkdm;
अटल atomic_t emu_count;

अटल व्योम omap_iommu_dra7_emu_swsup_config(काष्ठा platक्रमm_device *pdev,
					     bool enable)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	अचिन्हित दीर्घ flags;

	अगर (!of_device_is_compatible(np, "ti,dra7-dsp-iommu"))
		वापस;

	अगर (!emu_clkdm) अणु
		emu_clkdm = clkdm_lookup("emu_clkdm");
		अगर (WARN_ON_ONCE(!emu_clkdm))
			वापस;
	पूर्ण

	spin_lock_irqsave(&iommu_lock, flags);

	अगर (enable && (atomic_inc_वापस(&emu_count) == 1))
		clkdm_deny_idle(emu_clkdm);
	अन्यथा अगर (!enable && (atomic_dec_वापस(&emu_count) == 0))
		clkdm_allow_idle(emu_clkdm);

	spin_unlock_irqrestore(&iommu_lock, flags);
पूर्ण

अटल काष्ठा घातerकरोमुख्य *_get_pwrdm(काष्ठा device *dev)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_hw_omap *hwclk;
	काष्ठा घड़ीकरोमुख्य *clkdm;
	काष्ठा घातerकरोमुख्य *pwrdm = शून्य;
	काष्ठा pwrdm_link *entry;
	अचिन्हित दीर्घ flags;
	अटल LIST_HEAD(cache);

	spin_lock_irqsave(&iommu_lock, flags);

	list_क्रम_each_entry(entry, &cache, node) अणु
		अगर (entry->dev == dev) अणु
			pwrdm = entry->pwrdm;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&iommu_lock, flags);

	अगर (pwrdm)
		वापस pwrdm;

	clk = of_clk_get(dev->of_node->parent, 0);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "no fck found\n");
		वापस शून्य;
	पूर्ण

	hwclk = to_clk_hw_omap(__clk_get_hw(clk));
	clk_put(clk);
	अगर (!hwclk || !hwclk->clkdm_name) अणु
		dev_err(dev, "no hwclk data\n");
		वापस शून्य;
	पूर्ण

	clkdm = clkdm_lookup(hwclk->clkdm_name);
	अगर (!clkdm) अणु
		dev_err(dev, "clkdm not found: %s\n", hwclk->clkdm_name);
		वापस शून्य;
	पूर्ण

	pwrdm = clkdm_get_pwrdm(clkdm);
	अगर (!pwrdm) अणु
		dev_err(dev, "pwrdm not found: %s\n", clkdm->name);
		वापस शून्य;
	पूर्ण

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (entry) अणु
		entry->dev = dev;
		entry->pwrdm = pwrdm;
		spin_lock_irqsave(&iommu_lock, flags);
		list_add(&entry->node, &cache);
		spin_unlock_irqrestore(&iommu_lock, flags);
	पूर्ण

	वापस pwrdm;
पूर्ण

पूर्णांक omap_iommu_set_pwrdm_स्थिरraपूर्णांक(काष्ठा platक्रमm_device *pdev, bool request,
				    u8 *pwrst)
अणु
	काष्ठा घातerकरोमुख्य *pwrdm;
	u8 next_pwrst;
	पूर्णांक ret = 0;

	pwrdm = _get_pwrdm(&pdev->dev);
	अगर (!pwrdm)
		वापस -ENODEV;

	अगर (request) अणु
		*pwrst = pwrdm_पढ़ो_next_pwrst(pwrdm);
		omap_iommu_dra7_emu_swsup_config(pdev, true);
	पूर्ण

	अगर (*pwrst > PWRDM_POWER_RET)
		जाओ out;

	next_pwrst = request ? PWRDM_POWER_ON : *pwrst;

	ret = pwrdm_set_next_pwrst(pwrdm, next_pwrst);

out:
	अगर (!request)
		omap_iommu_dra7_emu_swsup_config(pdev, false);

	वापस ret;
पूर्ण
