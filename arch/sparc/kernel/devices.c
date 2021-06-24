<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* devices.c: Initial scan of the prom device tree क्रम important
 *	      Sparc device nodes which we need to find.
 *
 * This is based on the sparc64 version, but sun4m करोesn't always use
 * the hardware MIDs, so be careful.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/cpu_type.h>
#समावेश <यंत्र/setup.h>

#समावेश "kernel.h"

अटल अक्षर *cpu_mid_prop(व्योम)
अणु
	अगर (sparc_cpu_model == sun4d)
		वापस "cpu-id";
	वापस "mid";
पूर्ण

अटल पूर्णांक check_cpu_node(phandle nd, पूर्णांक *cur_inst,
		पूर्णांक (*compare)(phandle, पूर्णांक, व्योम *), व्योम *compare_arg,
		phandle *prom_node, पूर्णांक *mid)
अणु
	अगर (!compare(nd, *cur_inst, compare_arg)) अणु
		अगर (prom_node)
			*prom_node = nd;
		अगर (mid) अणु
			*mid = prom_getपूर्णांकशेष(nd, cpu_mid_prop(), 0);
			अगर (sparc_cpu_model == sun4m)
				*mid &= 3;
		पूर्ण
		वापस 0;
	पूर्ण

	(*cur_inst)++;

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __cpu_find_by(पूर्णांक (*compare)(phandle, पूर्णांक, व्योम *),
		व्योम *compare_arg, phandle *prom_node, पूर्णांक *mid)
अणु
	काष्ठा device_node *dp;
	पूर्णांक cur_inst;

	cur_inst = 0;
	क्रम_each_node_by_type(dp, "cpu") अणु
		पूर्णांक err = check_cpu_node(dp->phandle, &cur_inst,
					 compare, compare_arg,
					 prom_node, mid);
		अगर (!err) अणु
			of_node_put(dp);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक cpu_instance_compare(phandle nd, पूर्णांक instance, व्योम *_arg)
अणु
	पूर्णांक desired_instance = (पूर्णांक) _arg;

	अगर (instance == desired_instance)
		वापस 0;
	वापस -ENODEV;
पूर्ण

पूर्णांक cpu_find_by_instance(पूर्णांक instance, phandle *prom_node, पूर्णांक *mid)
अणु
	वापस __cpu_find_by(cpu_instance_compare, (व्योम *)instance,
			     prom_node, mid);
पूर्ण

अटल पूर्णांक cpu_mid_compare(phandle nd, पूर्णांक instance, व्योम *_arg)
अणु
	पूर्णांक desired_mid = (पूर्णांक) _arg;
	पूर्णांक this_mid;

	this_mid = prom_getपूर्णांकशेष(nd, cpu_mid_prop(), 0);
	अगर (this_mid == desired_mid
	    || (sparc_cpu_model == sun4m && (this_mid & 3) == desired_mid))
		वापस 0;
	वापस -ENODEV;
पूर्ण

पूर्णांक cpu_find_by_mid(पूर्णांक mid, phandle *prom_node)
अणु
	वापस __cpu_find_by(cpu_mid_compare, (व्योम *)mid,
			     prom_node, शून्य);
पूर्ण

/* sun4m uses truncated mids since we base the cpuid on the ttable/irqset
 * address (0-3).  This gives us the true hardware mid, which might have
 * some other bits set.  On 4d hardware and software mids are the same.
 */
पूर्णांक cpu_get_hwmid(phandle prom_node)
अणु
	वापस prom_getपूर्णांकशेष(prom_node, cpu_mid_prop(), -ENODEV);
पूर्ण

व्योम __init device_scan(व्योम)
अणु
	prपूर्णांकk(KERN_NOTICE "Booting Linux...\n");

#अगर_अघोषित CONFIG_SMP
	अणु
		phandle cpu_node;
		पूर्णांक err;
		err = cpu_find_by_instance(0, &cpu_node, शून्य);
		अगर (err) अणु
			/* Probably a sun4e, Sun is trying to trick us ;-) */
			prom_म_लिखो("No cpu nodes, cannot continue\n");
			prom_halt();
		पूर्ण
		cpu_data(0).घड़ी_प्रकारick = prom_getपूर्णांकशेष(cpu_node,
							    "clock-frequency",
							    0);
	पूर्ण
#पूर्ण_अगर /* !CONFIG_SMP */

	auxio_probe();
	auxio_घातer_probe();
पूर्ण
