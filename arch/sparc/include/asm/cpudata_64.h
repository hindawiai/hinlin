<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* cpudata.h: Per-cpu parameters.
 *
 * Copyright (C) 2003, 2005, 2006 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित _SPARC64_CPUDATA_H
#घोषणा _SPARC64_CPUDATA_H

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	/* Dcache line 1 */
	अचिन्हित पूर्णांक	__softirq_pending; /* must be 1st, see rtrap.S */
	अचिन्हित पूर्णांक	__nmi_count;
	अचिन्हित दीर्घ	घड़ी_प्रकारick;	/* %tick's per second */
	अचिन्हित दीर्घ	__pad;
	अचिन्हित पूर्णांक	irq0_irqs;
	अचिन्हित पूर्णांक	__pad2;

	/* Dcache line 2, rarely used */
	अचिन्हित पूर्णांक	dcache_size;
	अचिन्हित पूर्णांक	dcache_line_size;
	अचिन्हित पूर्णांक	icache_size;
	अचिन्हित पूर्णांक	icache_line_size;
	अचिन्हित पूर्णांक	ecache_size;
	अचिन्हित पूर्णांक	ecache_line_size;
	अचिन्हित लघु	sock_id;	/* physical package */
	अचिन्हित लघु	core_id;
	अचिन्हित लघु  max_cache_id;	/* groupings of highest shared cache */
	चिन्हित लघु	proc_id;	/* stअक्रम (aka HW thपढ़ो) id */
पूर्ण cpuinfo_sparc;

DECLARE_PER_CPU(cpuinfo_sparc, __cpu_data);
#घोषणा cpu_data(__cpu)		per_cpu(__cpu_data, (__cpu))
#घोषणा local_cpu_data()	(*this_cpu_ptr(&__cpu_data))

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#समावेश <यंत्र/trap_block.h>

#पूर्ण_अगर /* _SPARC64_CPUDATA_H */
