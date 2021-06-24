<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015-2018, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "aspeed-kcs-bmc: " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

#समावेश "kcs_bmc.h"


#घोषणा DEVICE_NAME     "ast-kcs-bmc"

#घोषणा KCS_CHANNEL_MAX     4

#घोषणा LPC_HICR0            0x000
#घोषणा     LPC_HICR0_LPC3E          BIT(7)
#घोषणा     LPC_HICR0_LPC2E          BIT(6)
#घोषणा     LPC_HICR0_LPC1E          BIT(5)
#घोषणा LPC_HICR2            0x008
#घोषणा     LPC_HICR2_IBFIF3         BIT(3)
#घोषणा     LPC_HICR2_IBFIF2         BIT(2)
#घोषणा     LPC_HICR2_IBFIF1         BIT(1)
#घोषणा LPC_HICR4            0x010
#घोषणा     LPC_HICR4_LADR12AS       BIT(7)
#घोषणा     LPC_HICR4_KCSENBL        BIT(2)
#घोषणा LPC_LADR3H           0x014
#घोषणा LPC_LADR3L           0x018
#घोषणा LPC_LADR12H          0x01C
#घोषणा LPC_LADR12L          0x020
#घोषणा LPC_IDR1             0x024
#घोषणा LPC_IDR2             0x028
#घोषणा LPC_IDR3             0x02C
#घोषणा LPC_ODR1             0x030
#घोषणा LPC_ODR2             0x034
#घोषणा LPC_ODR3             0x038
#घोषणा LPC_STR1             0x03C
#घोषणा LPC_STR2             0x040
#घोषणा LPC_STR3             0x044
#घोषणा LPC_HICRB            0x100
#घोषणा     LPC_HICRB_IBFIF4         BIT(1)
#घोषणा     LPC_HICRB_LPC4E          BIT(0)
#घोषणा LPC_LADR4            0x110
#घोषणा LPC_IDR4             0x114
#घोषणा LPC_ODR4             0x118
#घोषणा LPC_STR4             0x11C

काष्ठा aspeed_kcs_bmc अणु
	काष्ठा regmap *map;
पूर्ण;


अटल u8 aspeed_kcs_inb(काष्ठा kcs_bmc *kcs_bmc, u32 reg)
अणु
	काष्ठा aspeed_kcs_bmc *priv = kcs_bmc_priv(kcs_bmc);
	u32 val = 0;
	पूर्णांक rc;

	rc = regmap_पढ़ो(priv->map, reg, &val);
	WARN(rc != 0, "regmap_read() failed: %d\n", rc);

	वापस rc == 0 ? (u8) val : 0;
पूर्ण

अटल व्योम aspeed_kcs_outb(काष्ठा kcs_bmc *kcs_bmc, u32 reg, u8 data)
अणु
	काष्ठा aspeed_kcs_bmc *priv = kcs_bmc_priv(kcs_bmc);
	पूर्णांक rc;

	rc = regmap_ग_लिखो(priv->map, reg, data);
	WARN(rc != 0, "regmap_write() failed: %d\n", rc);
पूर्ण


/*
 * AST_usrGuide_KCS.pdf
 * 2. Background:
 *   we note D क्रम Data, and C क्रम Cmd/Status, शेष rules are
 *     A. KCS1 / KCS2 ( D / C:X / X+4 )
 *        D / C : CA0h / CA4h
 *        D / C : CA8h / CACh
 *     B. KCS3 ( D / C:XX2h / XX3h )
 *        D / C : CA2h / CA3h
 *        D / C : CB2h / CB3h
 *     C. KCS4
 *        D / C : CA4h / CA5h
 */
अटल व्योम aspeed_kcs_set_address(काष्ठा kcs_bmc *kcs_bmc, u16 addr)
अणु
	काष्ठा aspeed_kcs_bmc *priv = kcs_bmc_priv(kcs_bmc);

	चयन (kcs_bmc->channel) अणु
	हाल 1:
		regmap_update_bits(priv->map, LPC_HICR4,
				LPC_HICR4_LADR12AS, 0);
		regmap_ग_लिखो(priv->map, LPC_LADR12H, addr >> 8);
		regmap_ग_लिखो(priv->map, LPC_LADR12L, addr & 0xFF);
		अवरोध;

	हाल 2:
		regmap_update_bits(priv->map, LPC_HICR4,
				LPC_HICR4_LADR12AS, LPC_HICR4_LADR12AS);
		regmap_ग_लिखो(priv->map, LPC_LADR12H, addr >> 8);
		regmap_ग_लिखो(priv->map, LPC_LADR12L, addr & 0xFF);
		अवरोध;

	हाल 3:
		regmap_ग_लिखो(priv->map, LPC_LADR3H, addr >> 8);
		regmap_ग_लिखो(priv->map, LPC_LADR3L, addr & 0xFF);
		अवरोध;

	हाल 4:
		regmap_ग_लिखो(priv->map, LPC_LADR4, ((addr + 1) << 16) |
			addr);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम aspeed_kcs_enable_channel(काष्ठा kcs_bmc *kcs_bmc, bool enable)
अणु
	काष्ठा aspeed_kcs_bmc *priv = kcs_bmc_priv(kcs_bmc);

	चयन (kcs_bmc->channel) अणु
	हाल 1:
		अगर (enable) अणु
			regmap_update_bits(priv->map, LPC_HICR2,
					LPC_HICR2_IBFIF1, LPC_HICR2_IBFIF1);
			regmap_update_bits(priv->map, LPC_HICR0,
					LPC_HICR0_LPC1E, LPC_HICR0_LPC1E);
		पूर्ण अन्यथा अणु
			regmap_update_bits(priv->map, LPC_HICR0,
					LPC_HICR0_LPC1E, 0);
			regmap_update_bits(priv->map, LPC_HICR2,
					LPC_HICR2_IBFIF1, 0);
		पूर्ण
		अवरोध;

	हाल 2:
		अगर (enable) अणु
			regmap_update_bits(priv->map, LPC_HICR2,
					LPC_HICR2_IBFIF2, LPC_HICR2_IBFIF2);
			regmap_update_bits(priv->map, LPC_HICR0,
					LPC_HICR0_LPC2E, LPC_HICR0_LPC2E);
		पूर्ण अन्यथा अणु
			regmap_update_bits(priv->map, LPC_HICR0,
					LPC_HICR0_LPC2E, 0);
			regmap_update_bits(priv->map, LPC_HICR2,
					LPC_HICR2_IBFIF2, 0);
		पूर्ण
		अवरोध;

	हाल 3:
		अगर (enable) अणु
			regmap_update_bits(priv->map, LPC_HICR2,
					LPC_HICR2_IBFIF3, LPC_HICR2_IBFIF3);
			regmap_update_bits(priv->map, LPC_HICR0,
					LPC_HICR0_LPC3E, LPC_HICR0_LPC3E);
			regmap_update_bits(priv->map, LPC_HICR4,
					LPC_HICR4_KCSENBL, LPC_HICR4_KCSENBL);
		पूर्ण अन्यथा अणु
			regmap_update_bits(priv->map, LPC_HICR0,
					LPC_HICR0_LPC3E, 0);
			regmap_update_bits(priv->map, LPC_HICR4,
					LPC_HICR4_KCSENBL, 0);
			regmap_update_bits(priv->map, LPC_HICR2,
					LPC_HICR2_IBFIF3, 0);
		पूर्ण
		अवरोध;

	हाल 4:
		अगर (enable)
			regmap_update_bits(priv->map, LPC_HICRB,
					LPC_HICRB_IBFIF4 | LPC_HICRB_LPC4E,
					LPC_HICRB_IBFIF4 | LPC_HICRB_LPC4E);
		अन्यथा
			regmap_update_bits(priv->map, LPC_HICRB,
					LPC_HICRB_IBFIF4 | LPC_HICRB_LPC4E,
					0);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t aspeed_kcs_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा kcs_bmc *kcs_bmc = arg;

	अगर (!kcs_bmc_handle_event(kcs_bmc))
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक aspeed_kcs_config_irq(काष्ठा kcs_bmc *kcs_bmc,
			काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	वापस devm_request_irq(dev, irq, aspeed_kcs_irq, IRQF_SHARED,
				dev_name(dev), kcs_bmc);
पूर्ण

अटल स्थिर काष्ठा kcs_ioreg ast_kcs_bmc_ioregs[KCS_CHANNEL_MAX] = अणु
	अणु .idr = LPC_IDR1, .odr = LPC_ODR1, .str = LPC_STR1 पूर्ण,
	अणु .idr = LPC_IDR2, .odr = LPC_ODR2, .str = LPC_STR2 पूर्ण,
	अणु .idr = LPC_IDR3, .odr = LPC_ODR3, .str = LPC_STR3 पूर्ण,
	अणु .idr = LPC_IDR4, .odr = LPC_ODR4, .str = LPC_STR4 पूर्ण,
पूर्ण;

अटल काष्ठा kcs_bmc *aspeed_kcs_probe_of_v1(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_kcs_bmc *priv;
	काष्ठा device_node *np;
	काष्ठा kcs_bmc *kcs;
	u32 channel;
	u32 slave;
	पूर्णांक rc;

	np = pdev->dev.of_node;

	rc = of_property_पढ़ो_u32(np, "kcs_chan", &channel);
	अगर ((rc != 0) || (channel == 0 || channel > KCS_CHANNEL_MAX)) अणु
		dev_err(&pdev->dev, "no valid 'kcs_chan' configured\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	kcs = kcs_bmc_alloc(&pdev->dev, माप(काष्ठा aspeed_kcs_bmc), channel);
	अगर (!kcs)
		वापस ERR_PTR(-ENOMEM);

	priv = kcs_bmc_priv(kcs);
	priv->map = syscon_node_to_regmap(pdev->dev.parent->of_node);
	अगर (IS_ERR(priv->map)) अणु
		dev_err(&pdev->dev, "Couldn't get regmap\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	rc = of_property_पढ़ो_u32(np, "kcs_addr", &slave);
	अगर (rc) अणु
		dev_err(&pdev->dev, "no valid 'kcs_addr' configured\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	kcs->ioreg = ast_kcs_bmc_ioregs[channel - 1];
	aspeed_kcs_set_address(kcs, slave);

	वापस kcs;
पूर्ण

अटल पूर्णांक aspeed_kcs_calculate_channel(स्थिर काष्ठा kcs_ioreg *regs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ast_kcs_bmc_ioregs); i++) अणु
		अगर (!स_भेद(&ast_kcs_bmc_ioregs[i], regs, माप(*regs)))
			वापस i + 1;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा kcs_bmc *aspeed_kcs_probe_of_v2(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_kcs_bmc *priv;
	काष्ठा device_node *np;
	काष्ठा kcs_ioreg ioreg;
	काष्ठा kcs_bmc *kcs;
	स्थिर __be32 *reg;
	पूर्णांक channel;
	u32 slave;
	पूर्णांक rc;

	np = pdev->dev.of_node;

	/* Don't translate addresses, we want offsets क्रम the regmaps */
	reg = of_get_address(np, 0, शून्य, शून्य);
	अगर (!reg)
		वापस ERR_PTR(-EINVAL);
	ioreg.idr = be32_to_cpup(reg);

	reg = of_get_address(np, 1, शून्य, शून्य);
	अगर (!reg)
		वापस ERR_PTR(-EINVAL);
	ioreg.odr = be32_to_cpup(reg);

	reg = of_get_address(np, 2, शून्य, शून्य);
	अगर (!reg)
		वापस ERR_PTR(-EINVAL);
	ioreg.str = be32_to_cpup(reg);

	channel = aspeed_kcs_calculate_channel(&ioreg);
	अगर (channel < 0)
		वापस ERR_PTR(channel);

	kcs = kcs_bmc_alloc(&pdev->dev, माप(काष्ठा aspeed_kcs_bmc), channel);
	अगर (!kcs)
		वापस ERR_PTR(-ENOMEM);

	kcs->ioreg = ioreg;

	priv = kcs_bmc_priv(kcs);
	priv->map = syscon_node_to_regmap(pdev->dev.parent->of_node);
	अगर (IS_ERR(priv->map)) अणु
		dev_err(&pdev->dev, "Couldn't get regmap\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	rc = of_property_पढ़ो_u32(np, "aspeed,lpc-io-reg", &slave);
	अगर (rc)
		वापस ERR_PTR(rc);

	aspeed_kcs_set_address(kcs, slave);

	वापस kcs;
पूर्ण

अटल पूर्णांक aspeed_kcs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा kcs_bmc *kcs_bmc;
	काष्ठा device_node *np;
	पूर्णांक rc;

	np = dev->of_node->parent;
	अगर (!of_device_is_compatible(np, "aspeed,ast2400-lpc-v2") &&
	    !of_device_is_compatible(np, "aspeed,ast2500-lpc-v2") &&
	    !of_device_is_compatible(np, "aspeed,ast2600-lpc-v2")) अणु
		dev_err(dev, "unsupported LPC device binding\n");
		वापस -ENODEV;
	पूर्ण

	np = dev->of_node;
	अगर (of_device_is_compatible(np, "aspeed,ast2400-kcs-bmc") ||
	    of_device_is_compatible(np, "aspeed,ast2500-kcs-bmc"))
		kcs_bmc = aspeed_kcs_probe_of_v1(pdev);
	अन्यथा अगर (of_device_is_compatible(np, "aspeed,ast2400-kcs-bmc-v2") ||
		 of_device_is_compatible(np, "aspeed,ast2500-kcs-bmc-v2"))
		kcs_bmc = aspeed_kcs_probe_of_v2(pdev);
	अन्यथा
		वापस -EINVAL;

	अगर (IS_ERR(kcs_bmc))
		वापस PTR_ERR(kcs_bmc);

	kcs_bmc->io_inputb = aspeed_kcs_inb;
	kcs_bmc->io_outputb = aspeed_kcs_outb;

	rc = aspeed_kcs_config_irq(kcs_bmc, pdev);
	अगर (rc)
		वापस rc;

	dev_set_drvdata(dev, kcs_bmc);

	aspeed_kcs_enable_channel(kcs_bmc, true);

	rc = misc_रेजिस्टर(&kcs_bmc->miscdev);
	अगर (rc) अणु
		dev_err(dev, "Unable to register device\n");
		वापस rc;
	पूर्ण

	dev_dbg(&pdev->dev,
		"Probed KCS device %d (IDR=0x%x, ODR=0x%x, STR=0x%x)\n",
		kcs_bmc->channel, kcs_bmc->ioreg.idr, kcs_bmc->ioreg.odr,
		kcs_bmc->ioreg.str);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_kcs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kcs_bmc *kcs_bmc = dev_get_drvdata(&pdev->dev);

	misc_deरेजिस्टर(&kcs_bmc->miscdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ast_kcs_bmc_match[] = अणु
	अणु .compatible = "aspeed,ast2400-kcs-bmc" पूर्ण,
	अणु .compatible = "aspeed,ast2500-kcs-bmc" पूर्ण,
	अणु .compatible = "aspeed,ast2400-kcs-bmc-v2" पूर्ण,
	अणु .compatible = "aspeed,ast2500-kcs-bmc-v2" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ast_kcs_bmc_match);

अटल काष्ठा platक्रमm_driver ast_kcs_bmc_driver = अणु
	.driver = अणु
		.name           = DEVICE_NAME,
		.of_match_table = ast_kcs_bmc_match,
	पूर्ण,
	.probe  = aspeed_kcs_probe,
	.हटाओ = aspeed_kcs_हटाओ,
पूर्ण;
module_platक्रमm_driver(ast_kcs_bmc_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Haiyue Wang <haiyue.wang@linux.intel.com>");
MODULE_DESCRIPTION("Aspeed device interface to the KCS BMC device");
