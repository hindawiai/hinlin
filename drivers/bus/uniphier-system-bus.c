<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

/* System Bus Controller रेजिस्टरs */
#घोषणा UNIPHIER_SBC_BASE	0x100	/* base address of bank0 space */
#घोषणा    UNIPHIER_SBC_BASE_BE		BIT(0)	/* bank_enable */
#घोषणा UNIPHIER_SBC_CTRL0	0x200	/* timing parameter 0 of bank0 */
#घोषणा UNIPHIER_SBC_CTRL1	0x204	/* timing parameter 1 of bank0 */
#घोषणा UNIPHIER_SBC_CTRL2	0x208	/* timing parameter 2 of bank0 */
#घोषणा UNIPHIER_SBC_CTRL3	0x20c	/* timing parameter 3 of bank0 */
#घोषणा UNIPHIER_SBC_CTRL4	0x300	/* timing parameter 4 of bank0 */

#घोषणा UNIPHIER_SBC_STRIDE	0x10	/* रेजिस्टर stride to next bank */
#घोषणा UNIPHIER_SBC_NR_BANKS	8	/* number of banks (chip select) */
#घोषणा UNIPHIER_SBC_BASE_DUMMY	0xffffffff	/* data to squash bank 0, 1 */

काष्ठा uniphier_प्रणाली_bus_bank अणु
	u32 base;
	u32 end;
पूर्ण;

काष्ठा uniphier_प्रणाली_bus_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *membase;
	काष्ठा uniphier_प्रणाली_bus_bank bank[UNIPHIER_SBC_NR_BANKS];
पूर्ण;

अटल पूर्णांक uniphier_प्रणाली_bus_add_bank(काष्ठा uniphier_प्रणाली_bus_priv *priv,
					पूर्णांक bank, u32 addr, u64 paddr, u32 size)
अणु
	u64 end, mask;

	dev_dbg(priv->dev,
		"range found: bank = %d, addr = %08x, paddr = %08llx, size = %08x\n",
		bank, addr, paddr, size);

	अगर (bank >= ARRAY_SIZE(priv->bank)) अणु
		dev_err(priv->dev, "unsupported bank number %d\n", bank);
		वापस -EINVAL;
	पूर्ण

	अगर (priv->bank[bank].base || priv->bank[bank].end) अणु
		dev_err(priv->dev,
			"range for bank %d has already been specified\n", bank);
		वापस -EINVAL;
	पूर्ण

	अगर (paddr > U32_MAX) अणु
		dev_err(priv->dev, "base address %llx is too high\n", paddr);
		वापस -EINVAL;
	पूर्ण

	end = paddr + size;

	अगर (addr > paddr) अणु
		dev_err(priv->dev,
			"base %08x cannot be mapped to %08llx of parent\n",
			addr, paddr);
		वापस -EINVAL;
	पूर्ण
	paddr -= addr;

	paddr = round_करोwn(paddr, 0x00020000);
	end = round_up(end, 0x00020000);

	अगर (end > U32_MAX) अणु
		dev_err(priv->dev, "end address %08llx is too high\n", end);
		वापस -EINVAL;
	पूर्ण
	mask = paddr ^ (end - 1);
	mask = roundup_घात_of_two(mask);

	paddr = round_करोwn(paddr, mask);
	end = round_up(end, mask);

	priv->bank[bank].base = paddr;
	priv->bank[bank].end = end;

	dev_dbg(priv->dev, "range added: bank = %d, addr = %08x, end = %08x\n",
		bank, priv->bank[bank].base, priv->bank[bank].end);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_प्रणाली_bus_check_overlap(
				स्थिर काष्ठा uniphier_प्रणाली_bus_priv *priv)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(priv->bank); i++) अणु
		क्रम (j = i + 1; j < ARRAY_SIZE(priv->bank); j++) अणु
			अगर (priv->bank[i].end > priv->bank[j].base &&
			    priv->bank[i].base < priv->bank[j].end) अणु
				dev_err(priv->dev,
					"region overlap between bank%d and bank%d\n",
					i, j);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uniphier_प्रणाली_bus_check_boot_swap(
					काष्ठा uniphier_प्रणाली_bus_priv *priv)
अणु
	व्योम __iomem *base_reg = priv->membase + UNIPHIER_SBC_BASE;
	पूर्णांक is_swapped;

	is_swapped = !(पढ़ोl(base_reg) & UNIPHIER_SBC_BASE_BE);

	dev_dbg(priv->dev, "Boot Swap: %s\n", is_swapped ? "on" : "off");

	/*
	 * If BOOT_SWAP was निश्चितed on घातer-on-reset, the CS0 and CS1 are
	 * swapped.  In this हाल, bank0 and bank1 should be swapped as well.
	 */
	अगर (is_swapped)
		swap(priv->bank[0], priv->bank[1]);
पूर्ण

अटल व्योम uniphier_प्रणाली_bus_set_reg(
				स्थिर काष्ठा uniphier_प्रणाली_bus_priv *priv)
अणु
	व्योम __iomem *base_reg = priv->membase + UNIPHIER_SBC_BASE;
	u32 base, end, mask, val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->bank); i++) अणु
		base = priv->bank[i].base;
		end = priv->bank[i].end;

		अगर (base == end) अणु
			/*
			 * If SBC_BASE0 or SBC_BASE1 is set to zero, the access
			 * to anywhere in the प्रणाली bus space is routed to
			 * bank 0 (अगर boot swap अगर off) or bank 1 (अगर boot swap
			 * अगर on).  It means that CPUs cannot get access to
			 * bank 2 or later.  In other words, bank 0/1 cannot
			 * be disabled even अगर its bank_enable bits is cleared.
			 * This seems odd, but it is how this hardware goes.
			 * As a workaround, dummy data (0xffffffff) should be
			 * set when the bank 0/1 is unused.  As क्रम bank 2 and
			 * later, they can be simply disable by clearing the
			 * bank_enable bit.
			 */
			अगर (i < 2)
				val = UNIPHIER_SBC_BASE_DUMMY;
			अन्यथा
				val = 0;
		पूर्ण अन्यथा अणु
			mask = base ^ (end - 1);

			val = base & 0xfffe0000;
			val |= (~mask >> 16) & 0xfffe;
			val |= UNIPHIER_SBC_BASE_BE;
		पूर्ण
		dev_dbg(priv->dev, "SBC_BASE[%d] = 0x%08x\n", i, val);

		ग_लिखोl(val, base_reg + UNIPHIER_SBC_STRIDE * i);
	पूर्ण
पूर्ण

अटल पूर्णांक uniphier_प्रणाली_bus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_प्रणाली_bus_priv *priv;
	स्थिर __be32 *ranges;
	u32 cells, addr, size;
	u64 paddr;
	पूर्णांक pna, bank, rlen, rone, ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->membase))
		वापस PTR_ERR(priv->membase);

	priv->dev = dev;

	pna = of_n_addr_cells(dev->of_node);

	ret = of_property_पढ़ो_u32(dev->of_node, "#address-cells", &cells);
	अगर (ret) अणु
		dev_err(dev, "failed to get #address-cells\n");
		वापस ret;
	पूर्ण
	अगर (cells != 2) अणु
		dev_err(dev, "#address-cells must be 2\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "#size-cells", &cells);
	अगर (ret) अणु
		dev_err(dev, "failed to get #size-cells\n");
		वापस ret;
	पूर्ण
	अगर (cells != 1) अणु
		dev_err(dev, "#size-cells must be 1\n");
		वापस -EINVAL;
	पूर्ण

	ranges = of_get_property(dev->of_node, "ranges", &rlen);
	अगर (!ranges) अणु
		dev_err(dev, "failed to get ranges property\n");
		वापस -ENOENT;
	पूर्ण

	rlen /= माप(*ranges);
	rone = pna + 2;

	क्रम (; rlen >= rone; rlen -= rone) अणु
		bank = be32_to_cpup(ranges++);
		addr = be32_to_cpup(ranges++);
		paddr = of_translate_address(dev->of_node, ranges);
		अगर (paddr == OF_BAD_ADDR)
			वापस -EINVAL;
		ranges += pna;
		size = be32_to_cpup(ranges++);

		ret = uniphier_प्रणाली_bus_add_bank(priv, bank, addr,
						   paddr, size);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = uniphier_प्रणाली_bus_check_overlap(priv);
	अगर (ret)
		वापस ret;

	uniphier_प्रणाली_bus_check_boot_swap(priv);

	uniphier_प्रणाली_bus_set_reg(priv);

	platक्रमm_set_drvdata(pdev, priv);

	/* Now, the bus is configured.  Populate platक्रमm_devices below it */
	वापस of_platक्रमm_शेष_populate(dev->of_node, शून्य, dev);
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_प्रणाली_bus_resume(काष्ठा device *dev)
अणु
	uniphier_प्रणाली_bus_set_reg(dev_get_drvdata(dev));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops uniphier_प्रणाली_bus_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(शून्य, uniphier_प्रणाली_bus_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_प्रणाली_bus_match[] = अणु
	अणु .compatible = "socionext,uniphier-system-bus" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_प्रणाली_bus_match);

अटल काष्ठा platक्रमm_driver uniphier_प्रणाली_bus_driver = अणु
	.probe		= uniphier_प्रणाली_bus_probe,
	.driver = अणु
		.name	= "uniphier-system-bus",
		.of_match_table = uniphier_प्रणाली_bus_match,
		.pm = &uniphier_प्रणाली_bus_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_प्रणाली_bus_driver);

MODULE_AUTHOR("Masahiro Yamada <yamada.masahiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier System Bus driver");
MODULE_LICENSE("GPL");
