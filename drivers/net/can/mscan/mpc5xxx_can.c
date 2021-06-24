<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAN bus driver क्रम the Freescale MPC5xxx embedded CPU.
 *
 * Copyright (C) 2004-2005 Andrey Volkov <avolkov@varma-el.com>,
 *                         Varma Electronics Oy
 * Copyright (C) 2008-2009 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 * Copyright (C) 2009 Wolfram Sang, Pengutronix <kernel@pengutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mpc52xx.h>

#समावेश "mscan.h"

#घोषणा DRV_NAME "mpc5xxx_can"

काष्ठा mpc5xxx_can_data अणु
	अचिन्हित पूर्णांक type;
	u32 (*get_घड़ी)(काष्ठा platक्रमm_device *ofdev, स्थिर अक्षर *घड़ी_name,
			 पूर्णांक *mscan_clksrc);
	व्योम (*put_घड़ी)(काष्ठा platक्रमm_device *ofdev);
पूर्ण;

#अगर_घोषित CONFIG_PPC_MPC52xx
अटल स्थिर काष्ठा of_device_id mpc52xx_cdm_ids[] = अणु
	अणु .compatible = "fsl,mpc5200-cdm", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल u32 mpc52xx_can_get_घड़ी(काष्ठा platक्रमm_device *ofdev,
				 स्थिर अक्षर *घड़ी_name, पूर्णांक *mscan_clksrc)
अणु
	अचिन्हित पूर्णांक pvr;
	काष्ठा mpc52xx_cdm  __iomem *cdm;
	काष्ठा device_node *np_cdm;
	अचिन्हित पूर्णांक freq;
	u32 val;

	pvr = mfspr(SPRN_PVR);

	/*
	 * Either the oscillator घड़ी (SYS_XTAL_IN) or the IP bus घड़ी
	 * (IP_CLK) can be selected as MSCAN घड़ी source. According to
	 * the MPC5200 user's manual, the oscillator घड़ी is the better
	 * choice as it has less jitter. For this reason, it is selected
	 * by शेष. Unक्रमtunately, it can not be selected क्रम the old
	 * MPC5200 Rev. A chips due to a hardware bug (check errata).
	 */
	अगर (घड़ी_name && म_भेद(घड़ी_name, "ip") == 0)
		*mscan_clksrc = MSCAN_CLKSRC_BUS;
	अन्यथा
		*mscan_clksrc = MSCAN_CLKSRC_XTAL;

	freq = mpc5xxx_get_bus_frequency(ofdev->dev.of_node);
	अगर (!freq)
		वापस 0;

	अगर (*mscan_clksrc == MSCAN_CLKSRC_BUS || pvr == 0x80822011)
		वापस freq;

	/* Determine SYS_XTAL_IN frequency from the घड़ी करोमुख्य settings */
	np_cdm = of_find_matching_node(शून्य, mpc52xx_cdm_ids);
	अगर (!np_cdm) अणु
		dev_err(&ofdev->dev, "can't get clock node!\n");
		वापस 0;
	पूर्ण
	cdm = of_iomap(np_cdm, 0);
	अगर (!cdm) अणु
		of_node_put(np_cdm);
		dev_err(&ofdev->dev, "can't map clock node!\n");
		वापस 0;
	पूर्ण

	अगर (in_8(&cdm->ipb_clk_sel) & 0x1)
		freq *= 2;
	val = in_be32(&cdm->rstcfg);

	freq *= (val & (1 << 5)) ? 8 : 4;
	freq /= (val & (1 << 6)) ? 12 : 16;

	of_node_put(np_cdm);
	iounmap(cdm);

	वापस freq;
पूर्ण
#अन्यथा /* !CONFIG_PPC_MPC52xx */
अटल u32 mpc52xx_can_get_घड़ी(काष्ठा platक्रमm_device *ofdev,
				 स्थिर अक्षर *घड़ी_name, पूर्णांक *mscan_clksrc)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_MPC52xx */

#अगर_घोषित CONFIG_PPC_MPC512x
अटल u32 mpc512x_can_get_घड़ी(काष्ठा platक्रमm_device *ofdev,
				 स्थिर अक्षर *घड़ी_source, पूर्णांक *mscan_clksrc)
अणु
	काष्ठा device_node *np;
	u32 घड़ीभाग;
	क्रमागत अणु
		CLK_FROM_AUTO,
		CLK_FROM_IPS,
		CLK_FROM_SYS,
		CLK_FROM_REF,
	पूर्ण clk_from;
	काष्ठा clk *clk_in, *clk_can;
	अचिन्हित दीर्घ freq_calc;
	काष्ठा mscan_priv *priv;
	काष्ठा clk *clk_ipg;

	/* the caller passed in the घड़ी source spec that was पढ़ो from
	 * the device tree, get the optional घड़ी भागider as well
	 */
	np = ofdev->dev.of_node;
	घड़ीभाग = 1;
	of_property_पढ़ो_u32(np, "fsl,mscan-clock-divider", &घड़ीभाग);
	dev_dbg(&ofdev->dev, "device tree specs: clk src[%s] div[%d]\n",
		घड़ी_source ? घड़ी_source : "<NULL>", घड़ीभाग);

	/* when घड़ी-source is 'ip', the CANCTL1[CLKSRC] bit needs to
	 * get set, and the 'ips' घड़ी is the input to the MSCAN
	 * component
	 *
	 * क्रम घड़ी-source values of 'ref' or 'sys' the CANCTL1[CLKSRC]
	 * bit needs to get cleared, an optional घड़ी-भागider may have
	 * been specअगरied (the शेष value is 1), the appropriate
	 * MSCAN related MCLK is the input to the MSCAN component
	 *
	 * in the असलence of a घड़ी-source spec, first an optimal घड़ी
	 * माला_लो determined based on the 'sys' घड़ी, अगर that fails the
	 * 'ref' घड़ी is used
	 */
	clk_from = CLK_FROM_AUTO;
	अगर (घड़ी_source) अणु
		/* पूर्णांकerpret the device tree's spec क्रम the घड़ी source */
		अगर (!म_भेद(घड़ी_source, "ip"))
			clk_from = CLK_FROM_IPS;
		अन्यथा अगर (!म_भेद(घड़ी_source, "sys"))
			clk_from = CLK_FROM_SYS;
		अन्यथा अगर (!म_भेद(घड़ी_source, "ref"))
			clk_from = CLK_FROM_REF;
		अन्यथा
			जाओ err_invalid;
		dev_dbg(&ofdev->dev, "got a clk source spec[%d]\n", clk_from);
	पूर्ण
	अगर (clk_from == CLK_FROM_AUTO) अणु
		/* no spec so far, try the 'sys' घड़ी; round to the
		 * next MHz and see अगर we can get a multiple of 16MHz
		 */
		dev_dbg(&ofdev->dev, "no clk source spec, trying SYS\n");
		clk_in = devm_clk_get(&ofdev->dev, "sys");
		अगर (IS_ERR(clk_in))
			जाओ err_notavail;
		freq_calc = clk_get_rate(clk_in);
		freq_calc +=  499999;
		freq_calc /= 1000000;
		freq_calc *= 1000000;
		अगर ((freq_calc % 16000000) == 0) अणु
			clk_from = CLK_FROM_SYS;
			घड़ीभाग = freq_calc / 16000000;
			dev_dbg(&ofdev->dev,
				"clk fit, sys[%lu] div[%d] freq[%lu]\n",
				freq_calc, घड़ीभाग, freq_calc / घड़ीभाग);
		पूर्ण
	पूर्ण
	अगर (clk_from == CLK_FROM_AUTO) अणु
		/* no spec so far, use the 'ref' घड़ी */
		dev_dbg(&ofdev->dev, "no clk source spec, trying REF\n");
		clk_in = devm_clk_get(&ofdev->dev, "ref");
		अगर (IS_ERR(clk_in))
			जाओ err_notavail;
		clk_from = CLK_FROM_REF;
		freq_calc = clk_get_rate(clk_in);
		dev_dbg(&ofdev->dev,
			"clk fit, ref[%lu] (no div) freq[%lu]\n",
			freq_calc, freq_calc);
	पूर्ण

	/* select IPS or MCLK as the MSCAN input (वापसed to the caller),
	 * setup the MCLK mux source and rate अगर applicable, apply the
	 * optionally specअगरied or derived above भागider, and determine
	 * the actual resulting घड़ी rate to वापस to the caller
	 */
	चयन (clk_from) अणु
	हाल CLK_FROM_IPS:
		clk_can = devm_clk_get(&ofdev->dev, "ips");
		अगर (IS_ERR(clk_can))
			जाओ err_notavail;
		priv = netdev_priv(dev_get_drvdata(&ofdev->dev));
		priv->clk_can = clk_can;
		freq_calc = clk_get_rate(clk_can);
		*mscan_clksrc = MSCAN_CLKSRC_IPS;
		dev_dbg(&ofdev->dev, "clk from IPS, clksrc[%d] freq[%lu]\n",
			*mscan_clksrc, freq_calc);
		अवरोध;
	हाल CLK_FROM_SYS:
	हाल CLK_FROM_REF:
		clk_can = devm_clk_get(&ofdev->dev, "mclk");
		अगर (IS_ERR(clk_can))
			जाओ err_notavail;
		priv = netdev_priv(dev_get_drvdata(&ofdev->dev));
		priv->clk_can = clk_can;
		अगर (clk_from == CLK_FROM_SYS)
			clk_in = devm_clk_get(&ofdev->dev, "sys");
		अगर (clk_from == CLK_FROM_REF)
			clk_in = devm_clk_get(&ofdev->dev, "ref");
		अगर (IS_ERR(clk_in))
			जाओ err_notavail;
		clk_set_parent(clk_can, clk_in);
		freq_calc = clk_get_rate(clk_in);
		freq_calc /= घड़ीभाग;
		clk_set_rate(clk_can, freq_calc);
		freq_calc = clk_get_rate(clk_can);
		*mscan_clksrc = MSCAN_CLKSRC_BUS;
		dev_dbg(&ofdev->dev, "clk from MCLK, clksrc[%d] freq[%lu]\n",
			*mscan_clksrc, freq_calc);
		अवरोध;
	शेष:
		जाओ err_invalid;
	पूर्ण

	/* the above clk_can item is used क्रम the bitrate, access to
	 * the peripheral's रेजिस्टर set needs the clk_ipg item
	 */
	clk_ipg = devm_clk_get(&ofdev->dev, "ipg");
	अगर (IS_ERR(clk_ipg))
		जाओ err_notavail_ipg;
	अगर (clk_prepare_enable(clk_ipg))
		जाओ err_notavail_ipg;
	priv = netdev_priv(dev_get_drvdata(&ofdev->dev));
	priv->clk_ipg = clk_ipg;

	/* वापस the determined घड़ी source rate */
	वापस freq_calc;

err_invalid:
	dev_err(&ofdev->dev, "invalid clock source specification\n");
	/* घड़ी source rate could not get determined */
	वापस 0;

err_notavail:
	dev_err(&ofdev->dev, "cannot acquire or setup bitrate clock source\n");
	/* घड़ी source rate could not get determined */
	वापस 0;

err_notavail_ipg:
	dev_err(&ofdev->dev, "cannot acquire or setup register clock\n");
	/* घड़ी source rate could not get determined */
	वापस 0;
पूर्ण

अटल व्योम mpc512x_can_put_घड़ी(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mscan_priv *priv;

	priv = netdev_priv(dev_get_drvdata(&ofdev->dev));
	अगर (priv->clk_ipg)
		clk_disable_unprepare(priv->clk_ipg);
पूर्ण
#अन्यथा /* !CONFIG_PPC_MPC512x */
अटल u32 mpc512x_can_get_घड़ी(काष्ठा platक्रमm_device *ofdev,
				 स्थिर अक्षर *घड़ी_name, पूर्णांक *mscan_clksrc)
अणु
	वापस 0;
पूर्ण
#घोषणा mpc512x_can_put_घड़ी शून्य
#पूर्ण_अगर /* CONFIG_PPC_MPC512x */

अटल स्थिर काष्ठा of_device_id mpc5xxx_can_table[];
अटल पूर्णांक mpc5xxx_can_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा mpc5xxx_can_data *data;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा net_device *dev;
	काष्ठा mscan_priv *priv;
	व्योम __iomem *base;
	स्थिर अक्षर *घड़ी_name = शून्य;
	पूर्णांक irq, mscan_clksrc = 0;
	पूर्णांक err = -ENOMEM;

	match = of_match_device(mpc5xxx_can_table, &ofdev->dev);
	अगर (!match)
		वापस -EINVAL;
	data = match->data;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		dev_err(&ofdev->dev, "couldn't ioremap\n");
		वापस err;
	पूर्ण

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		dev_err(&ofdev->dev, "no irq found\n");
		err = -ENODEV;
		जाओ निकास_unmap_mem;
	पूर्ण

	dev = alloc_mscandev();
	अगर (!dev)
		जाओ निकास_dispose_irq;
	platक्रमm_set_drvdata(ofdev, dev);
	SET_NETDEV_DEV(dev, &ofdev->dev);

	priv = netdev_priv(dev);
	priv->reg_base = base;
	dev->irq = irq;

	घड़ी_name = of_get_property(np, "fsl,mscan-clock-source", शून्य);

	BUG_ON(!data);
	priv->type = data->type;
	priv->can.घड़ी.freq = data->get_घड़ी(ofdev, घड़ी_name,
					       &mscan_clksrc);
	अगर (!priv->can.घड़ी.freq) अणु
		dev_err(&ofdev->dev, "couldn't get MSCAN clock properties\n");
		जाओ निकास_मुक्त_mscan;
	पूर्ण

	err = रेजिस्टर_mscandev(dev, mscan_clksrc);
	अगर (err) अणु
		dev_err(&ofdev->dev, "registering %s failed (err=%d)\n",
			DRV_NAME, err);
		जाओ निकास_मुक्त_mscan;
	पूर्ण

	dev_info(&ofdev->dev, "MSCAN at 0x%p, irq %d, clock %d Hz\n",
		 priv->reg_base, dev->irq, priv->can.घड़ी.freq);

	वापस 0;

निकास_मुक्त_mscan:
	मुक्त_candev(dev);
निकास_dispose_irq:
	irq_dispose_mapping(irq);
निकास_unmap_mem:
	iounmap(base);

	वापस err;
पूर्ण

अटल पूर्णांक mpc5xxx_can_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा mpc5xxx_can_data *data;
	काष्ठा net_device *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा mscan_priv *priv = netdev_priv(dev);

	match = of_match_device(mpc5xxx_can_table, &ofdev->dev);
	data = match ? match->data : शून्य;

	unरेजिस्टर_mscandev(dev);
	अगर (data && data->put_घड़ी)
		data->put_घड़ी(ofdev);
	iounmap(priv->reg_base);
	irq_dispose_mapping(dev->irq);
	मुक्त_candev(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल काष्ठा mscan_regs saved_regs;
अटल पूर्णांक mpc5xxx_can_suspend(काष्ठा platक्रमm_device *ofdev, pm_message_t state)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs *regs = (काष्ठा mscan_regs *)priv->reg_base;

	_स_नकल_fromio(&saved_regs, regs, माप(*regs));

	वापस 0;
पूर्ण

अटल पूर्णांक mpc5xxx_can_resume(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs *regs = (काष्ठा mscan_regs *)priv->reg_base;

	regs->canctl0 |= MSCAN_INITRQ;
	जबतक (!(regs->canctl1 & MSCAN_INITAK))
		udelay(10);

	regs->canctl1 = saved_regs.canctl1;
	regs->canbtr0 = saved_regs.canbtr0;
	regs->canbtr1 = saved_regs.canbtr1;
	regs->canidac = saved_regs.canidac;

	/* restore masks, buffers etc. */
	_स_नकल_toio(&regs->canidar1_0, (व्योम *)&saved_regs.canidar1_0,
		     माप(*regs) - दुरत्व(काष्ठा mscan_regs, canidar1_0));

	regs->canctl0 &= ~MSCAN_INITRQ;
	regs->cantbsel = saved_regs.cantbsel;
	regs->canrier = saved_regs.canrier;
	regs->cantier = saved_regs.cantier;
	regs->canctl0 = saved_regs.canctl0;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा mpc5xxx_can_data mpc5200_can_data = अणु
	.type = MSCAN_TYPE_MPC5200,
	.get_घड़ी = mpc52xx_can_get_घड़ी,
	/* .put_घड़ी not applicable */
पूर्ण;

अटल स्थिर काष्ठा mpc5xxx_can_data mpc5121_can_data = अणु
	.type = MSCAN_TYPE_MPC5121,
	.get_घड़ी = mpc512x_can_get_घड़ी,
	.put_घड़ी = mpc512x_can_put_घड़ी,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mpc5xxx_can_table[] = अणु
	अणु .compatible = "fsl,mpc5200-mscan", .data = &mpc5200_can_data, पूर्ण,
	/* Note that only MPC5121 Rev. 2 (and later) is supported */
	अणु .compatible = "fsl,mpc5121-mscan", .data = &mpc5121_can_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc5xxx_can_table);

अटल काष्ठा platक्रमm_driver mpc5xxx_can_driver = अणु
	.driver = अणु
		.name = "mpc5xxx_can",
		.of_match_table = mpc5xxx_can_table,
	पूर्ण,
	.probe = mpc5xxx_can_probe,
	.हटाओ = mpc5xxx_can_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = mpc5xxx_can_suspend,
	.resume = mpc5xxx_can_resume,
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(mpc5xxx_can_driver);

MODULE_AUTHOR("Wolfgang Grandegger <wg@grandegger.com>");
MODULE_DESCRIPTION("Freescale MPC5xxx CAN driver");
MODULE_LICENSE("GPL v2");
