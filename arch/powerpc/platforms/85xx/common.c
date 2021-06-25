<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Routines common to most mpc85xx-based boards.
 */

#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/fsl_pm.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <sysdev/cpm2_pic.h>

#समावेश "mpc85xx.h"

स्थिर काष्ठा fsl_pm_ops *qoriq_pm_ops;

अटल स्थिर काष्ठा of_device_id mpc85xx_common_ids[] __initस्थिर = अणु
	अणु .type = "soc", पूर्ण,
	अणु .compatible = "soc", पूर्ण,
	अणु .compatible = "simple-bus", पूर्ण,
	अणु .name = "cpm", पूर्ण,
	अणु .name = "localbus", पूर्ण,
	अणु .compatible = "gianfar", पूर्ण,
	अणु .compatible = "fsl,qe", पूर्ण,
	अणु .compatible = "fsl,cpm2", पूर्ण,
	अणु .compatible = "fsl,srio", पूर्ण,
	/* So that the DMA channel nodes can be probed inभागidually: */
	अणु .compatible = "fsl,eloplus-dma", पूर्ण,
	/* For the PMC driver */
	अणु .compatible = "fsl,mpc8548-guts", पूर्ण,
	/* Probably unnecessary? */
	अणु .compatible = "gpio-leds", पूर्ण,
	/* For all PCI controllers */
	अणु .compatible = "fsl,mpc8540-pci", पूर्ण,
	अणु .compatible = "fsl,mpc8548-pcie", पूर्ण,
	अणु .compatible = "fsl,p1022-pcie", पूर्ण,
	अणु .compatible = "fsl,p1010-pcie", पूर्ण,
	अणु .compatible = "fsl,p1023-pcie", पूर्ण,
	अणु .compatible = "fsl,p4080-pcie", पूर्ण,
	अणु .compatible = "fsl,qoriq-pcie-v2.4", पूर्ण,
	अणु .compatible = "fsl,qoriq-pcie-v2.3", पूर्ण,
	अणु .compatible = "fsl,qoriq-pcie-v2.2", पूर्ण,
	अणु .compatible = "fsl,fman", पूर्ण,
	अणुपूर्ण,
पूर्ण;

पूर्णांक __init mpc85xx_common_publish_devices(व्योम)
अणु
	वापस of_platक्रमm_bus_probe(शून्य, mpc85xx_common_ids, शून्य);
पूर्ण
#अगर_घोषित CONFIG_CPM2
अटल व्योम cpm2_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक cascade_irq;

	जबतक ((cascade_irq = cpm2_get_irq()) >= 0)
		generic_handle_irq(cascade_irq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण


व्योम __init mpc85xx_cpm2_pic_init(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक irq;

	/* Setup CPM2 PIC */
	np = of_find_compatible_node(शून्य, शून्य, "fsl,cpm2-pic");
	अगर (np == शून्य) अणु
		prपूर्णांकk(KERN_ERR "PIC init: can not find fsl,cpm2-pic node\n");
		वापस;
	पूर्ण
	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		of_node_put(np);
		prपूर्णांकk(KERN_ERR "PIC init: got no IRQ for cpm cascade\n");
		वापस;
	पूर्ण

	cpm2_pic_init(np);
	of_node_put(np);
	irq_set_chained_handler(irq, cpm2_cascade);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_QUICC_ENGINE
व्योम __init mpc85xx_qe_par_io_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_node_by_name(शून्य, "par_io");
	अगर (np) अणु
		काष्ठा device_node *ucc;

		par_io_init(np);
		of_node_put(np);

		क्रम_each_node_by_name(ucc, "ucc")
			par_io_of_config(ucc);

	पूर्ण
पूर्ण
#पूर्ण_अगर
