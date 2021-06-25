<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* cpudata.h: Per-cpu parameters.
 *
 * Copyright (C) 2004 Keith M Wesolowski (wesolows@foobazco.org)
 *
 * Based on include/यंत्र/cpudata.h and Linux 2.4 smp.h
 * both (C) David S. Miller.
 */

#अगर_अघोषित _SPARC_CPUDATA_H
#घोषणा _SPARC_CPUDATA_H

#समावेश <linux/percpu.h>

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ udelay_val;
	अचिन्हित दीर्घ घड़ी_प्रकारick;
	अचिन्हित पूर्णांक counter;
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक irq_resched_count;
	अचिन्हित पूर्णांक irq_call_count;
#पूर्ण_अगर
	पूर्णांक prom_node;
	पूर्णांक mid;
	पूर्णांक next;
पूर्ण cpuinfo_sparc;

DECLARE_PER_CPU(cpuinfo_sparc, __cpu_data);
#घोषणा cpu_data(__cpu) per_cpu(__cpu_data, (__cpu))
#घोषणा local_cpu_data() (*this_cpu_ptr(&__cpu_data))

#पूर्ण_अगर /* _SPARC_CPUDATA_H */
