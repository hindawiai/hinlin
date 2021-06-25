<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2001 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 * Copyright (C) 2000, 2001 Ralf Baechle (ralf@gnu.org)
 *
 * Copyright (C) 2007 Lemote Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/compiler.h>

#समावेश <loongson.h>

अटल अंतरभूत व्योम bonito_irq_enable(काष्ठा irq_data *d)
अणु
	LOONGSON_INTENSET = (1 << (d->irq - LOONGSON_IRQ_BASE));
	mmiowb();
पूर्ण

अटल अंतरभूत व्योम bonito_irq_disable(काष्ठा irq_data *d)
अणु
	LOONGSON_INTENCLR = (1 << (d->irq - LOONGSON_IRQ_BASE));
	mmiowb();
पूर्ण

अटल काष्ठा irq_chip bonito_irq_type = अणु
	.name		= "bonito_irq",
	.irq_mask	= bonito_irq_disable,
	.irq_unmask	= bonito_irq_enable,
पूर्ण;

व्योम bonito_irq_init(व्योम)
अणु
	u32 i;

	क्रम (i = LOONGSON_IRQ_BASE; i < LOONGSON_IRQ_BASE + 32; i++)
		irq_set_chip_and_handler(i, &bonito_irq_type,
					 handle_level_irq);

#अगर_घोषित CONFIG_CPU_LOONGSON2E
	i = LOONGSON_IRQ_BASE + 10;
	अगर (request_irq(i, no_action, 0, "dma_timeout", शून्य))
		pr_err("Failed to request irq %d (dma_timeout)\n", i);
#पूर्ण_अगर
पूर्ण
