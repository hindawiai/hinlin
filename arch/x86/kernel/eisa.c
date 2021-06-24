<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EISA specअगरic code
 */
#समावेश <linux/ioport.h>
#समावेश <linux/eisa.h>
#समावेश <linux/पन.स>

#समावेश <xen/xen.h>

अटल __init पूर्णांक eisa_bus_probe(व्योम)
अणु
	व्योम __iomem *p;

	अगर (xen_pv_करोमुख्य() && !xen_initial_करोमुख्य())
		वापस 0;

	p = ioremap(0x0FFFD9, 4);
	अगर (p && पढ़ोl(p) == 'E' + ('I' << 8) + ('S' << 16) + ('A' << 24))
		EISA_bus = 1;
	iounmap(p);
	वापस 0;
पूर्ण
subsys_initcall(eisa_bus_probe);
