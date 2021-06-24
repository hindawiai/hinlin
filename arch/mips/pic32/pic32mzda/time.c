<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/समय.स>

#समावेश "pic32mzda.h"

अटल स्थिर काष्ठा of_device_id pic32_infra_match[] = अणु
	अणु .compatible = "microchip,pic32mzda-infra", पूर्ण,
	अणु पूर्ण,
पूर्ण;

#घोषणा DEFAULT_CORE_TIMER_INTERRUPT 0

अटल अचिन्हित पूर्णांक pic32_xlate_core_समयr_irq(व्योम)
अणु
	काष्ठा device_node *node;
	अचिन्हित पूर्णांक irq;

	node = of_find_matching_node(शून्य, pic32_infra_match);

	अगर (WARN_ON(!node))
		जाओ शेष_map;

	irq = irq_of_parse_and_map(node, 0);
	अगर (!irq)
		जाओ शेष_map;

	वापस irq;

शेष_map:

	वापस irq_create_mapping(शून्य, DEFAULT_CORE_TIMER_INTERRUPT);
पूर्ण

अचिन्हित पूर्णांक get_c0_compare_पूर्णांक(व्योम)
अणु
	वापस pic32_xlate_core_समयr_irq();
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	अचिन्हित दीर्घ rate = pic32_get_pbclk(7);

	of_clk_init(शून्य);

	pr_info("CPU Clock: %ldMHz\n", rate / 1000000);
	mips_hpt_frequency = rate / 2;

	समयr_probe();
पूर्ण
