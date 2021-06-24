<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Zynq घातer management
 *
 *  Copyright (C) 2012 - 2014 Xilinx
 *
 *  Sथघren Brinkmann <soren.brinkmann@xilinx.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश "common.h"

/* रेजिस्टर offsets */
#घोषणा DDRC_CTRL_REG1_OFFS		0x60
#घोषणा DDRC_DRAM_PARAM_REG3_OFFS	0x20

/* bitfields */
#घोषणा DDRC_CLOCKSTOP_MASK	BIT(23)
#घोषणा DDRC_SELFREFRESH_MASK	BIT(12)

अटल व्योम __iomem *ddrc_base;

/**
 * zynq_pm_ioremap() - Create IO mappings
 * @comp:	DT compatible string
 * Return: Poपूर्णांकer to the mapped memory or शून्य.
 *
 * Remap the memory region क्रम a compatible DT node.
 */
अटल व्योम __iomem *zynq_pm_ioremap(स्थिर अक्षर *comp)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *base = शून्य;

	np = of_find_compatible_node(शून्य, शून्य, comp);
	अगर (np) अणु
		base = of_iomap(np, 0);
		of_node_put(np);
	पूर्ण अन्यथा अणु
		pr_warn("%s: no compatible node found for '%s'\n", __func__,
				comp);
	पूर्ण

	वापस base;
पूर्ण

/**
 * zynq_pm_late_init() - Power management init
 *
 * Initialization of घातer management related features and infraकाष्ठाure.
 */
व्योम __init zynq_pm_late_init(व्योम)
अणु
	u32 reg;

	ddrc_base = zynq_pm_ioremap("xlnx,zynq-ddrc-a05");
	अगर (!ddrc_base) अणु
		pr_warn("%s: Unable to map DDRC IO memory.\n", __func__);
	पूर्ण अन्यथा अणु
		/*
		 * Enable DDRC घड़ी stop feature. The HW takes care of
		 * entering/निकासing the correct mode depending
		 * on activity state.
		 */
		reg = पढ़ोl(ddrc_base + DDRC_DRAM_PARAM_REG3_OFFS);
		reg |= DDRC_CLOCKSTOP_MASK;
		ग_लिखोl(reg, ddrc_base + DDRC_DRAM_PARAM_REG3_OFFS);
	पूर्ण
पूर्ण
