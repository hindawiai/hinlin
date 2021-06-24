<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car Generation 2 da9063(L)/da9210 regulator quirk
 *
 * Certain Gen2 development boards have an da9063 and one or more da9210
 * regulators. All of these regulators have their पूर्णांकerrupt request lines
 * tied to the same पूर्णांकerrupt pin (IRQ2) on the SoC.
 *
 * After cold boot or da9063-induced restart, both the da9063 and da9210 seem
 * to निश्चित their पूर्णांकerrupt request lines.  Hence as soon as one driver
 * requests this irq, it माला_लो stuck in an पूर्णांकerrupt storm, as it only manages
 * to deनिश्चित its own पूर्णांकerrupt request line, and the other driver hasn't
 * installed an पूर्णांकerrupt handler yet.
 *
 * To handle this, install a quirk that masks the पूर्णांकerrupts in both the
 * da9063 and da9210.  This quirk has to run after the i2c master driver has
 * been initialized, but beक्रमe the i2c slave drivers are initialized.
 *
 * Copyright (C) 2015 Glider bvba
 */

#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/mfd/da9063/रेजिस्टरs.h>

#घोषणा IRQC_BASE		0xe61c0000
#घोषणा IRQC_MONITOR		0x104	/* IRQn Signal Level Monitor Register */

#घोषणा REGULATOR_IRQ_MASK	BIT(2)	/* IRQ2, active low */

/* start of DA9210 System Control and Event Registers */
#घोषणा DA9210_REG_MASK_A		0x54

काष्ठा regulator_quirk अणु
	काष्ठा list_head		list;
	स्थिर काष्ठा of_device_id	*id;
	काष्ठा device_node		*np;
	काष्ठा of_phandle_args		irq_args;
	काष्ठा i2c_msg			i2c_msg;
	bool				shared;	/* IRQ line is shared */
पूर्ण;

अटल LIST_HEAD(quirk_list);
अटल व्योम __iomem *irqc;

/* first byte sets the memory poपूर्णांकer, following are consecutive reg values */
अटल u8 da9063_irq_clr[] = अणु DA9063_REG_IRQ_MASK_A, 0xff, 0xff, 0xff, 0xff पूर्ण;
अटल u8 da9210_irq_clr[] = अणु DA9210_REG_MASK_A, 0xff, 0xff पूर्ण;

अटल काष्ठा i2c_msg da9063_msg = अणु
	.len = ARRAY_SIZE(da9063_irq_clr),
	.buf = da9063_irq_clr,
पूर्ण;

अटल काष्ठा i2c_msg da9210_msg = अणु
	.len = ARRAY_SIZE(da9210_irq_clr),
	.buf = da9210_irq_clr,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_gen2_quirk_match[] = अणु
	अणु .compatible = "dlg,da9063", .data = &da9063_msg पूर्ण,
	अणु .compatible = "dlg,da9063l", .data = &da9063_msg पूर्ण,
	अणु .compatible = "dlg,da9210", .data = &da9210_msg पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक regulator_quirk_notअगरy(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा regulator_quirk *pos, *पंचांगp;
	काष्ठा device *dev = data;
	काष्ठा i2c_client *client;
	अटल bool करोne;
	पूर्णांक ret;
	u32 mon;

	अगर (करोne)
		वापस 0;

	mon = ioपढ़ो32(irqc + IRQC_MONITOR);
	dev_dbg(dev, "%s: %ld, IRQC_MONITOR = 0x%x\n", __func__, action, mon);
	अगर (mon & REGULATOR_IRQ_MASK)
		जाओ हटाओ;

	अगर (action != BUS_NOTIFY_ADD_DEVICE || dev->type == &i2c_adapter_type)
		वापस 0;

	client = to_i2c_client(dev);
	dev_dbg(dev, "Detected %s\n", client->name);

	/*
	 * Send message to all PMICs that share an IRQ line to deनिश्चित it.
	 *
	 * WARNING: This works only अगर all the PMICs are on the same I2C bus.
	 */
	list_क्रम_each_entry(pos, &quirk_list, list) अणु
		अगर (!pos->shared)
			जारी;

		अगर (pos->np->parent != client->dev.parent->of_node)
			जारी;

		dev_info(&client->dev, "clearing %s@0x%02x interrupts\n",
			 pos->id->compatible, pos->i2c_msg.addr);

		ret = i2c_transfer(client->adapter, &pos->i2c_msg, 1);
		अगर (ret != 1)
			dev_err(&client->dev, "i2c error %d\n", ret);
	पूर्ण

	mon = ioपढ़ो32(irqc + IRQC_MONITOR);
	अगर (mon & REGULATOR_IRQ_MASK)
		जाओ हटाओ;

	वापस 0;

हटाओ:
	dev_info(dev, "IRQ2 is not asserted, removing quirk\n");

	list_क्रम_each_entry_safe(pos, पंचांगp, &quirk_list, list) अणु
		list_del(&pos->list);
		kमुक्त(pos);
	पूर्ण

	करोne = true;
	iounmap(irqc);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block regulator_quirk_nb = अणु
	.notअगरier_call = regulator_quirk_notअगरy
पूर्ण;

अटल पूर्णांक __init rcar_gen2_regulator_quirk(व्योम)
अणु
	काष्ठा regulator_quirk *quirk, *pos, *पंचांगp;
	काष्ठा of_phandle_args *argsa, *argsb;
	स्थिर काष्ठा of_device_id *id;
	काष्ठा device_node *np;
	u32 mon, addr;
	पूर्णांक ret;

	अगर (!of_machine_is_compatible("renesas,koelsch") &&
	    !of_machine_is_compatible("renesas,lager") &&
	    !of_machine_is_compatible("renesas,porter") &&
	    !of_machine_is_compatible("renesas,stout") &&
	    !of_machine_is_compatible("renesas,gose"))
		वापस -ENODEV;

	क्रम_each_matching_node_and_match(np, rcar_gen2_quirk_match, &id) अणु
		अगर (!of_device_is_available(np))
			अवरोध;

		ret = of_property_पढ़ो_u32(np, "reg", &addr);
		अगर (ret)	/* Skip invalid entry and जारी */
			जारी;

		quirk = kzalloc(माप(*quirk), GFP_KERNEL);
		अगर (!quirk) अणु
			ret = -ENOMEM;
			जाओ err_mem;
		पूर्ण

		argsa = &quirk->irq_args;
		स_नकल(&quirk->i2c_msg, id->data, माप(quirk->i2c_msg));

		quirk->id = id;
		quirk->np = np;
		quirk->i2c_msg.addr = addr;

		ret = of_irq_parse_one(np, 0, argsa);
		अगर (ret) अणु	/* Skip invalid entry and जारी */
			kमुक्त(quirk);
			जारी;
		पूर्ण

		list_क्रम_each_entry(pos, &quirk_list, list) अणु
			argsb = &pos->irq_args;

			अगर (argsa->args_count != argsb->args_count)
				जारी;

			ret = स_भेद(argsa->args, argsb->args,
				     argsa->args_count *
				     माप(argsa->args[0]));
			अगर (!ret) अणु
				pos->shared = true;
				quirk->shared = true;
			पूर्ण
		पूर्ण

		list_add_tail(&quirk->list, &quirk_list);
	पूर्ण

	irqc = ioremap(IRQC_BASE, PAGE_SIZE);
	अगर (!irqc) अणु
		ret = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	mon = ioपढ़ो32(irqc + IRQC_MONITOR);
	अगर (mon & REGULATOR_IRQ_MASK) अणु
		pr_debug("%s: IRQ2 is not asserted, not installing quirk\n",
			 __func__);
		ret = 0;
		जाओ err_मुक्त;
	पूर्ण

	pr_info("IRQ2 is asserted, installing regulator quirk\n");

	bus_रेजिस्टर_notअगरier(&i2c_bus_type, &regulator_quirk_nb);
	वापस 0;

err_मुक्त:
	iounmap(irqc);
err_mem:
	list_क्रम_each_entry_safe(pos, पंचांगp, &quirk_list, list) अणु
		list_del(&pos->list);
		kमुक्त(pos);
	पूर्ण

	वापस ret;
पूर्ण

arch_initcall(rcar_gen2_regulator_quirk);
