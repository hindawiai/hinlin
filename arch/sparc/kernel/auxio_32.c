<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* auxio.c: Probing क्रम the Sparc AUXIO रेजिस्टर at boot समय.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/auxपन.स>
#समावेश <यंत्र/माला.स>		/* स_रखो(), Linux has no bzero() */
#समावेश <यंत्र/cpu_type.h>

#समावेश "kernel.h"

/* Probe and map in the Auxiliary I/O रेजिस्टर */

/* auxio_रेजिस्टर is not अटल because it is referenced 
 * in entry.S::floppy_tकरोne
 */
व्योम __iomem *auxio_रेजिस्टर = शून्य;
अटल DEFINE_SPINLOCK(auxio_lock);

व्योम __init auxio_probe(व्योम)
अणु
	phandle node, auxio_nd;
	काष्ठा linux_prom_रेजिस्टरs auxregs[1];
	काष्ठा resource r;

	चयन (sparc_cpu_model) अणु
	हाल sparc_leon:
	हाल sun4d:
		वापस;
	शेष:
		अवरोध;
	पूर्ण
	node = prom_अ_लोhild(prom_root_node);
	auxio_nd = prom_searchsiblings(node, "auxiliary-io");
	अगर(!auxio_nd) अणु
		node = prom_searchsiblings(node, "obio");
		node = prom_अ_लोhild(node);
		auxio_nd = prom_searchsiblings(node, "auxio");
		अगर(!auxio_nd) अणु
#अगर_घोषित CONFIG_PCI
			/* There may be auxio on Ebus */
			वापस;
#अन्यथा
			अगर(prom_searchsiblings(node, "leds")) अणु
				/* VME chassis sun4m machine, no auxio exists. */
				वापस;
			पूर्ण
			prom_म_लिखो("Cannot find auxio node, cannot continue...\n");
			prom_halt();
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	अगर(prom_getproperty(auxio_nd, "reg", (अक्षर *) auxregs, माप(auxregs)) <= 0)
		वापस;
	prom_apply_obio_ranges(auxregs, 0x1);
	/* Map the रेजिस्टर both पढ़ो and ग_लिखो */
	r.flags = auxregs[0].which_io & 0xF;
	r.start = auxregs[0].phys_addr;
	r.end = auxregs[0].phys_addr + auxregs[0].reg_size - 1;
	auxio_रेजिस्टर = of_ioremap(&r, 0, auxregs[0].reg_size, "auxio");
	/* Fix the address on sun4m. */
	अगर ((((अचिन्हित दीर्घ) auxregs[0].phys_addr) & 3) == 3)
		auxio_रेजिस्टर += (3 - ((अचिन्हित दीर्घ)auxio_रेजिस्टर & 3));

	set_auxio(AUXIO_LED, 0);
पूर्ण

अचिन्हित अक्षर get_auxio(व्योम)
अणु
	अगर(auxio_रेजिस्टर) 
		वापस sbus_पढ़ोb(auxio_रेजिस्टर);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_auxio);

व्योम set_auxio(अचिन्हित अक्षर bits_on, अचिन्हित अक्षर bits_off)
अणु
	अचिन्हित अक्षर regval;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&auxio_lock, flags);
	चयन (sparc_cpu_model) अणु
	हाल sun4m:
		अगर(!auxio_रेजिस्टर)
			अवरोध;     /* VME chassis sun4m, no auxio. */
		regval = sbus_पढ़ोb(auxio_रेजिस्टर);
		sbus_ग_लिखोb(((regval | bits_on) & ~bits_off) | AUXIO_ORMEIN4M,
			auxio_रेजिस्टर);
		अवरोध;
	हाल sun4d:
		अवरोध;
	शेष:
		panic("Can't set AUXIO register on this machine.");
	पूर्ण
	spin_unlock_irqrestore(&auxio_lock, flags);
पूर्ण
EXPORT_SYMBOL(set_auxio);

/* sun4m घातer control रेजिस्टर (AUXIO2) */

अस्थिर u8 __iomem *auxio_घातer_रेजिस्टर = शून्य;

व्योम __init auxio_घातer_probe(व्योम)
अणु
	काष्ठा linux_prom_रेजिस्टरs regs;
	phandle node;
	काष्ठा resource r;

	/* Attempt to find the sun4m घातer control node. */
	node = prom_अ_लोhild(prom_root_node);
	node = prom_searchsiblings(node, "obio");
	node = prom_अ_लोhild(node);
	node = prom_searchsiblings(node, "power");
	अगर (node == 0 || (s32)node == -1)
		वापस;

	/* Map the घातer control रेजिस्टर. */
	अगर (prom_getproperty(node, "reg", (अक्षर *)&regs, माप(regs)) <= 0)
		वापस;
	prom_apply_obio_ranges(&regs, 1);
	स_रखो(&r, 0, माप(r));
	r.flags = regs.which_io & 0xF;
	r.start = regs.phys_addr;
	r.end = regs.phys_addr + regs.reg_size - 1;
	auxio_घातer_रेजिस्टर =
		(u8 __iomem *)of_ioremap(&r, 0, regs.reg_size, "auxpower");

	/* Display a quick message on the console. */
	अगर (auxio_घातer_रेजिस्टर)
		prपूर्णांकk(KERN_INFO "Power off control detected.\n");
पूर्ण
