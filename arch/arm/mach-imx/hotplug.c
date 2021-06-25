<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/proc-fns.h>

#समावेश "common.h"

/*
 * platक्रमm-specअगरic code to shutकरोwn a CPU
 *
 * Called with IRQs disabled
 */
व्योम imx_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	v7_निकास_coherency_flush(louis);
	/*
	 * We use the cpu jumping argument रेजिस्टर to sync with
	 * imx_cpu_समाप्त() which is running on cpu0 and रुकोing क्रम
	 * the रेजिस्टर being cleared to समाप्त the cpu.
	 */
	imx_set_cpu_arg(cpu, ~0);

	जबतक (1)
		cpu_करो_idle();
पूर्ण

पूर्णांक imx_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(50);

	जबतक (imx_get_cpu_arg(cpu) == 0)
		अगर (समय_after(jअगरfies, समयout))
			वापस 0;
	imx_enable_cpu(cpu, false);
	imx_set_cpu_arg(cpu, 0);
	वापस 1;
पूर्ण
