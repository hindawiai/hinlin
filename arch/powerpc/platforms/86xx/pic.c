<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2008 Freescale Semiconductor, Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/i8259.h>

#अगर_घोषित CONFIG_PPC_I8259
अटल व्योम mpc86xx_8259_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq = i8259_irq();

	अगर (cascade_irq)
		generic_handle_irq(cascade_irq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण
#पूर्ण_अगर	/* CONFIG_PPC_I8259 */

व्योम __init mpc86xx_init_irq(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_I8259
	काष्ठा device_node *np;
	काष्ठा device_node *cascade_node = शून्य;
	पूर्णांक cascade_irq;
#पूर्ण_अगर

	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
			MPIC_SINGLE_DEST_CPU,
			0, 256, " MPIC     ");
	BUG_ON(mpic == शून्य);

	mpic_init(mpic);

#अगर_घोषित CONFIG_PPC_I8259
	/* Initialize i8259 controller */
	क्रम_each_node_by_type(np, "interrupt-controller")
		अगर (of_device_is_compatible(np, "chrp,iic")) अणु
			cascade_node = np;
			अवरोध;
		पूर्ण

	अगर (cascade_node == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "Could not find i8259 PIC\n");
		वापस;
	पूर्ण

	cascade_irq = irq_of_parse_and_map(cascade_node, 0);
	अगर (!cascade_irq) अणु
		prपूर्णांकk(KERN_ERR "Failed to map cascade interrupt\n");
		वापस;
	पूर्ण

	i8259_init(cascade_node, 0);
	of_node_put(cascade_node);

	irq_set_chained_handler(cascade_irq, mpc86xx_8259_cascade);
#पूर्ण_अगर
पूर्ण
