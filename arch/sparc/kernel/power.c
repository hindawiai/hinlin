<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* घातer.c: Power management driver.
 *
 * Copyright (C) 1999, 2007, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reboot.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>

अटल व्योम __iomem *घातer_reg;

अटल irqवापस_t घातer_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	orderly_घातeroff(true);

	/* FIXME: Check रेजिस्टरs क्रम status... */
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक has_button_पूर्णांकerrupt(अचिन्हित पूर्णांक irq, काष्ठा device_node *dp)
अणु
	अगर (irq == 0xffffffff)
		वापस 0;
	अगर (!of_find_property(dp, "button", शून्य))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक घातer_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा resource *res = &op->resource[0];
	अचिन्हित पूर्णांक irq = op->archdata.irqs[0];

	घातer_reg = of_ioremap(res, 0, 0x4, "power");

	prपूर्णांकk(KERN_INFO "%pOFn: Control reg at %llx\n",
	       op->dev.of_node, res->start);

	अगर (has_button_पूर्णांकerrupt(irq, op->dev.of_node)) अणु
		अगर (request_irq(irq,
				घातer_handler, 0, "power", शून्य) < 0)
			prपूर्णांकk(KERN_ERR "power: Cannot setup IRQ handler.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id घातer_match[] = अणु
	अणु
		.name = "power",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver घातer_driver = अणु
	.probe		= घातer_probe,
	.driver = अणु
		.name = "power",
		.of_match_table = घातer_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(घातer_driver);
