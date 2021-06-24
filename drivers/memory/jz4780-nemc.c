<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * JZ4780 न_अंकD/बाह्यal memory controller (NEMC)
 *
 * Copyright (c) 2015 Imagination Technologies
 * Author: Alex Smith <alex@alex-smith.me.uk>
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/math64.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/jz4780-nemc.h>

#घोषणा NEMC_SMCRn(n)		(0x14 + (((n) - 1) * 4))
#घोषणा NEMC_NFCSR		0x50

#घोषणा NEMC_REG_LEN		0x54

#घोषणा NEMC_SMCR_SMT		BIT(0)
#घोषणा NEMC_SMCR_BW_SHIFT	6
#घोषणा NEMC_SMCR_BW_MASK	(0x3 << NEMC_SMCR_BW_SHIFT)
#घोषणा NEMC_SMCR_BW_8		(0 << 6)
#घोषणा NEMC_SMCR_TAS_SHIFT	8
#घोषणा NEMC_SMCR_TAS_MASK	(0xf << NEMC_SMCR_TAS_SHIFT)
#घोषणा NEMC_SMCR_TAH_SHIFT	12
#घोषणा NEMC_SMCR_TAH_MASK	(0xf << NEMC_SMCR_TAH_SHIFT)
#घोषणा NEMC_SMCR_TBP_SHIFT	16
#घोषणा NEMC_SMCR_TBP_MASK	(0xf << NEMC_SMCR_TBP_SHIFT)
#घोषणा NEMC_SMCR_TAW_SHIFT	20
#घोषणा NEMC_SMCR_TAW_MASK	(0xf << NEMC_SMCR_TAW_SHIFT)
#घोषणा NEMC_SMCR_TSTRV_SHIFT	24
#घोषणा NEMC_SMCR_TSTRV_MASK	(0x3f << NEMC_SMCR_TSTRV_SHIFT)

#घोषणा NEMC_NFCSR_NFEn(n)	BIT(((n) - 1) << 1)
#घोषणा NEMC_NFCSR_NFCEn(n)	BIT((((n) - 1) << 1) + 1)
#घोषणा NEMC_NFCSR_TNFEn(n)	BIT(16 + (n) - 1)

काष्ठा jz_soc_info अणु
	u8 tas_tah_cycles_max;
पूर्ण;

काष्ठा jz4780_nemc अणु
	spinlock_t lock;
	काष्ठा device *dev;
	स्थिर काष्ठा jz_soc_info *soc_info;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	uपूर्णांक32_t clk_period;
	अचिन्हित दीर्घ banks_present;
पूर्ण;

/**
 * jz4780_nemc_num_banks() - count the number of banks referenced by a device
 * @dev: device to count banks क्रम, must be a child of the NEMC.
 *
 * Return: The number of unique NEMC banks referred to by the specअगरied NEMC
 * child device. Unique here means that a device that references the same bank
 * multiple बार in its "reg" property will only count once.
 */
अचिन्हित पूर्णांक jz4780_nemc_num_banks(काष्ठा device *dev)
अणु
	स्थिर __be32 *prop;
	अचिन्हित पूर्णांक bank, count = 0;
	अचिन्हित दीर्घ referenced = 0;
	पूर्णांक i = 0;

	जबतक ((prop = of_get_address(dev->of_node, i++, शून्य, शून्य))) अणु
		bank = of_पढ़ो_number(prop, 1);
		अगर (!(referenced & BIT(bank))) अणु
			referenced |= BIT(bank);
			count++;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL(jz4780_nemc_num_banks);

/**
 * jz4780_nemc_set_type() - set the type of device connected to a bank
 * @dev: child device of the NEMC.
 * @bank: bank number to configure.
 * @type: type of device connected to the bank.
 */
व्योम jz4780_nemc_set_type(काष्ठा device *dev, अचिन्हित पूर्णांक bank,
			  क्रमागत jz4780_nemc_bank_type type)
अणु
	काष्ठा jz4780_nemc *nemc = dev_get_drvdata(dev->parent);
	uपूर्णांक32_t nfcsr;

	nfcsr = पढ़ोl(nemc->base + NEMC_NFCSR);

	/* TODO: Support toggle न_अंकD devices. */
	चयन (type) अणु
	हाल JZ4780_NEMC_BANK_SRAM:
		nfcsr &= ~(NEMC_NFCSR_TNFEn(bank) | NEMC_NFCSR_NFEn(bank));
		अवरोध;
	हाल JZ4780_NEMC_BANK_न_अंकD:
		nfcsr &= ~NEMC_NFCSR_TNFEn(bank);
		nfcsr |= NEMC_NFCSR_NFEn(bank);
		अवरोध;
	पूर्ण

	ग_लिखोl(nfcsr, nemc->base + NEMC_NFCSR);
पूर्ण
EXPORT_SYMBOL(jz4780_nemc_set_type);

/**
 * jz4780_nemc_निश्चित() - (de-)निश्चित a न_अंकD device's chip enable pin
 * @dev: child device of the NEMC.
 * @bank: bank number of device.
 * @निश्चित: whether the chip enable pin should be निश्चितed.
 *
 * (De-)निश्चितs the chip enable pin क्रम the न_अंकD device connected to the
 * specअगरied bank.
 */
व्योम jz4780_nemc_निश्चित(काष्ठा device *dev, अचिन्हित पूर्णांक bank, bool निश्चित)
अणु
	काष्ठा jz4780_nemc *nemc = dev_get_drvdata(dev->parent);
	uपूर्णांक32_t nfcsr;

	nfcsr = पढ़ोl(nemc->base + NEMC_NFCSR);

	अगर (निश्चित)
		nfcsr |= NEMC_NFCSR_NFCEn(bank);
	अन्यथा
		nfcsr &= ~NEMC_NFCSR_NFCEn(bank);

	ग_लिखोl(nfcsr, nemc->base + NEMC_NFCSR);
पूर्ण
EXPORT_SYMBOL(jz4780_nemc_निश्चित);

अटल uपूर्णांक32_t jz4780_nemc_clk_period(काष्ठा jz4780_nemc *nemc)
अणु
	अचिन्हित दीर्घ rate;

	rate = clk_get_rate(nemc->clk);
	अगर (!rate)
		वापस 0;

	/* Return in picoseconds. */
	वापस भाग64_ul(1000000000000ull, rate);
पूर्ण

अटल uपूर्णांक32_t jz4780_nemc_ns_to_cycles(काष्ठा jz4780_nemc *nemc, uपूर्णांक32_t ns)
अणु
	वापस ((ns * 1000) + nemc->clk_period - 1) / nemc->clk_period;
पूर्ण

अटल bool jz4780_nemc_configure_bank(काष्ठा jz4780_nemc *nemc,
				       अचिन्हित पूर्णांक bank,
				       काष्ठा device_node *node)
अणु
	uपूर्णांक32_t smcr, val, cycles;

	/*
	 * Conversion of tBP and tAW cycle counts to values supported by the
	 * hardware (round up to the next supported value).
	 */
	अटल स्थिर u8 convert_tBP_tAW[] = अणु
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,

		/* 11 - 12 -> 12 cycles */
		11, 11,

		/* 13 - 15 -> 15 cycles */
		12, 12, 12,

		/* 16 - 20 -> 20 cycles */
		13, 13, 13, 13, 13,

		/* 21 - 25 -> 25 cycles */
		14, 14, 14, 14, 14,

		/* 26 - 31 -> 31 cycles */
		15, 15, 15, 15, 15, 15
	पूर्ण;

	smcr = पढ़ोl(nemc->base + NEMC_SMCRn(bank));
	smcr &= ~NEMC_SMCR_SMT;

	अगर (!of_property_पढ़ो_u32(node, "ingenic,nemc-bus-width", &val)) अणु
		smcr &= ~NEMC_SMCR_BW_MASK;
		चयन (val) अणु
		हाल 8:
			smcr |= NEMC_SMCR_BW_8;
			अवरोध;
		शेष:
			/*
			 * Earlier SoCs support a 16 bit bus width (the 4780
			 * करोes not), until those are properly supported, error.
			 */
			dev_err(nemc->dev, "unsupported bus width: %u\n", val);
			वापस false;
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "ingenic,nemc-tAS", &val) == 0) अणु
		smcr &= ~NEMC_SMCR_TAS_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		अगर (cycles > nemc->soc_info->tas_tah_cycles_max) अणु
			dev_err(nemc->dev, "tAS %u is too high (%u cycles)\n",
				val, cycles);
			वापस false;
		पूर्ण

		smcr |= cycles << NEMC_SMCR_TAS_SHIFT;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "ingenic,nemc-tAH", &val) == 0) अणु
		smcr &= ~NEMC_SMCR_TAH_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		अगर (cycles > nemc->soc_info->tas_tah_cycles_max) अणु
			dev_err(nemc->dev, "tAH %u is too high (%u cycles)\n",
				val, cycles);
			वापस false;
		पूर्ण

		smcr |= cycles << NEMC_SMCR_TAH_SHIFT;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "ingenic,nemc-tBP", &val) == 0) अणु
		smcr &= ~NEMC_SMCR_TBP_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		अगर (cycles > 31) अणु
			dev_err(nemc->dev, "tBP %u is too high (%u cycles)\n",
				val, cycles);
			वापस false;
		पूर्ण

		smcr |= convert_tBP_tAW[cycles] << NEMC_SMCR_TBP_SHIFT;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "ingenic,nemc-tAW", &val) == 0) अणु
		smcr &= ~NEMC_SMCR_TAW_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		अगर (cycles > 31) अणु
			dev_err(nemc->dev, "tAW %u is too high (%u cycles)\n",
				val, cycles);
			वापस false;
		पूर्ण

		smcr |= convert_tBP_tAW[cycles] << NEMC_SMCR_TAW_SHIFT;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "ingenic,nemc-tSTRV", &val) == 0) अणु
		smcr &= ~NEMC_SMCR_TSTRV_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		अगर (cycles > 63) अणु
			dev_err(nemc->dev, "tSTRV %u is too high (%u cycles)\n",
				val, cycles);
			वापस false;
		पूर्ण

		smcr |= cycles << NEMC_SMCR_TSTRV_SHIFT;
	पूर्ण

	ग_लिखोl(smcr, nemc->base + NEMC_SMCRn(bank));
	वापस true;
पूर्ण

अटल पूर्णांक jz4780_nemc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा jz4780_nemc *nemc;
	काष्ठा resource *res;
	काष्ठा device_node *child;
	स्थिर __be32 *prop;
	अचिन्हित पूर्णांक bank;
	अचिन्हित दीर्घ referenced;
	पूर्णांक i, ret;

	nemc = devm_kzalloc(dev, माप(*nemc), GFP_KERNEL);
	अगर (!nemc)
		वापस -ENOMEM;

	nemc->soc_info = device_get_match_data(dev);
	अगर (!nemc->soc_info)
		वापस -EINVAL;

	spin_lock_init(&nemc->lock);
	nemc->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	/*
	 * The driver currently only uses the रेजिस्टरs up to offset
	 * NEMC_REG_LEN. Since the EFUSE रेजिस्टरs are in the middle of the
	 * NEMC रेजिस्टरs, we only request the रेजिस्टरs we will use क्रम now;
	 * that way the EFUSE driver can probe too.
	 */
	अगर (!devm_request_mem_region(dev, res->start, NEMC_REG_LEN, dev_name(dev))) अणु
		dev_err(dev, "unable to request I/O memory region\n");
		वापस -EBUSY;
	पूर्ण

	nemc->base = devm_ioremap(dev, res->start, NEMC_REG_LEN);
	अगर (!nemc->base) अणु
		dev_err(dev, "failed to get I/O memory\n");
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोl(0, nemc->base + NEMC_NFCSR);

	nemc->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(nemc->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(nemc->clk);
	पूर्ण

	ret = clk_prepare_enable(nemc->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	nemc->clk_period = jz4780_nemc_clk_period(nemc);
	अगर (!nemc->clk_period) अणु
		dev_err(dev, "failed to calculate clock period\n");
		clk_disable_unprepare(nemc->clk);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Iterate over child devices, check that they करो not conflict with
	 * each other, and रेजिस्टर child devices क्रम them. If a child device
	 * has invalid properties, it is ignored and no platक्रमm device is
	 * रेजिस्टरed क्रम it.
	 */
	क्रम_each_child_of_node(nemc->dev->of_node, child) अणु
		referenced = 0;
		i = 0;
		जबतक ((prop = of_get_address(child, i++, शून्य, शून्य))) अणु
			bank = of_पढ़ो_number(prop, 1);
			अगर (bank < 1 || bank >= JZ4780_NEMC_NUM_BANKS) अणु
				dev_err(nemc->dev,
					"%pOF requests invalid bank %u\n",
					child, bank);

				/* Will जारी the outer loop below. */
				referenced = 0;
				अवरोध;
			पूर्ण

			referenced |= BIT(bank);
		पूर्ण

		अगर (!referenced) अणु
			dev_err(nemc->dev, "%pOF has no addresses\n",
				child);
			जारी;
		पूर्ण अन्यथा अगर (nemc->banks_present & referenced) अणु
			dev_err(nemc->dev, "%pOF conflicts with another node\n",
				child);
			जारी;
		पूर्ण

		/* Configure bank parameters. */
		क्रम_each_set_bit(bank, &referenced, JZ4780_NEMC_NUM_BANKS) अणु
			अगर (!jz4780_nemc_configure_bank(nemc, bank, child)) अणु
				referenced = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (referenced) अणु
			अगर (of_platक्रमm_device_create(child, शून्य, nemc->dev))
				nemc->banks_present |= referenced;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, nemc);
	dev_info(dev, "JZ4780 NEMC initialised\n");
	वापस 0;
पूर्ण

अटल पूर्णांक jz4780_nemc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jz4780_nemc *nemc = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(nemc->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा jz_soc_info jz4740_soc_info = अणु
	.tas_tah_cycles_max = 7,
पूर्ण;

अटल स्थिर काष्ठा jz_soc_info jz4780_soc_info = अणु
	.tas_tah_cycles_max = 15,
पूर्ण;

अटल स्थिर काष्ठा of_device_id jz4780_nemc_dt_match[] = अणु
	अणु .compatible = "ingenic,jz4740-nemc", .data = &jz4740_soc_info, पूर्ण,
	अणु .compatible = "ingenic,jz4780-nemc", .data = &jz4780_soc_info, पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver jz4780_nemc_driver = अणु
	.probe		= jz4780_nemc_probe,
	.हटाओ		= jz4780_nemc_हटाओ,
	.driver	= अणु
		.name	= "jz4780-nemc",
		.of_match_table = of_match_ptr(jz4780_nemc_dt_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init jz4780_nemc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&jz4780_nemc_driver);
पूर्ण
subsys_initcall(jz4780_nemc_init);
