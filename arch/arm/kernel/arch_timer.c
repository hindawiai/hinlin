<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/arch_समयr.c
 *
 *  Copyright (C) 2011 ARM Ltd.
 *  All Rights Reserved
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/arch_समयr.h>

#समावेश <घड़ीsource/arm_arch_समयr.h>

अटल अचिन्हित दीर्घ arch_समयr_पढ़ो_counter_दीर्घ(व्योम)
अणु
	वापस arch_समयr_पढ़ो_counter();
पूर्ण

अटल काष्ठा delay_समयr arch_delay_समयr;

अटल व्योम __init arch_समयr_delay_समयr_रेजिस्टर(व्योम)
अणु
	/* Use the architected समयr क्रम the delay loop. */
	arch_delay_समयr.पढ़ो_current_समयr = arch_समयr_पढ़ो_counter_दीर्घ;
	arch_delay_समयr.freq = arch_समयr_get_rate();
	रेजिस्टर_current_समयr_delay(&arch_delay_समयr);
पूर्ण

पूर्णांक __init arch_समयr_arch_init(व्योम)
अणु
        u32 arch_समयr_rate = arch_समयr_get_rate();

	अगर (arch_समयr_rate == 0)
		वापस -ENXIO;

	arch_समयr_delay_समयr_रेजिस्टर();

	वापस 0;
पूर्ण
