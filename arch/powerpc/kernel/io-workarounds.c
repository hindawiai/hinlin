<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support PCI IO workaround
 *
 *  Copyright (C) 2006 Benjamin Herrenschmidt <benh@kernel.crashing.org>
 *		       IBM, Corp.
 *  (C) Copyright 2007-2008 TOSHIBA CORPORATION
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/sched/mm.h>	/* क्रम init_mm */
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/io-workarounds.h>
#समावेश <यंत्र/pte-walk.h>


#घोषणा IOWA_MAX_BUS	8

अटल काष्ठा iowa_bus iowa_busses[IOWA_MAX_BUS];
अटल अचिन्हित पूर्णांक iowa_bus_count;

अटल काष्ठा iowa_bus *iowa_pci_find(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ paddr)
अणु
	पूर्णांक i, j;
	काष्ठा resource *res;
	अचिन्हित दीर्घ vstart, vend;

	क्रम (i = 0; i < iowa_bus_count; i++) अणु
		काष्ठा iowa_bus *bus = &iowa_busses[i];
		काष्ठा pci_controller *phb = bus->phb;

		अगर (vaddr) अणु
			vstart = (अचिन्हित दीर्घ)phb->io_base_virt;
			vend = vstart + phb->pci_io_size - 1;
			अगर ((vaddr >= vstart) && (vaddr <= vend))
				वापस bus;
		पूर्ण

		अगर (paddr)
			क्रम (j = 0; j < 3; j++) अणु
				res = &phb->mem_resources[j];
				अगर (paddr >= res->start && paddr <= res->end)
					वापस bus;
			पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_PPC_INसूचीECT_MMIO
काष्ठा iowa_bus *iowa_mem_find_bus(स्थिर PCI_IO_ADDR addr)
अणु
	काष्ठा iowa_bus *bus;
	पूर्णांक token;

	token = PCI_GET_ADDR_TOKEN(addr);

	अगर (token && token <= iowa_bus_count)
		bus = &iowa_busses[token - 1];
	अन्यथा अणु
		अचिन्हित दीर्घ vaddr, paddr;

		vaddr = (अचिन्हित दीर्घ)PCI_FIX_ADDR(addr);
		अगर (vaddr < PHB_IO_BASE || vaddr >= PHB_IO_END)
			वापस शून्य;

		paddr = ppc_find_vmap_phys(vaddr);

		bus = iowa_pci_find(vaddr, paddr);

		अगर (bus == शून्य)
			वापस शून्य;
	पूर्ण

	वापस bus;
पूर्ण
#अन्यथा /* CONFIG_PPC_INसूचीECT_MMIO */
काष्ठा iowa_bus *iowa_mem_find_bus(स्थिर PCI_IO_ADDR addr)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* !CONFIG_PPC_INसूचीECT_MMIO */

#अगर_घोषित CONFIG_PPC_INसूचीECT_PIO
काष्ठा iowa_bus *iowa_pio_find_bus(अचिन्हित दीर्घ port)
अणु
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)pci_io_base + port;
	वापस iowa_pci_find(vaddr, 0);
पूर्ण
#अन्यथा
काष्ठा iowa_bus *iowa_pio_find_bus(अचिन्हित दीर्घ port)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#घोषणा DEF_PCI_AC_RET(name, ret, at, al, space, aa)		\
अटल ret iowa_##name at					\
अणु								\
	काष्ठा iowa_bus *bus;					\
	bus = iowa_##space##_find_bus(aa);			\
	अगर (bus && bus->ops && bus->ops->name)			\
		वापस bus->ops->name al;			\
	वापस __करो_##name al;					\
पूर्ण

#घोषणा DEF_PCI_AC_NORET(name, at, al, space, aa)		\
अटल व्योम iowa_##name at					\
अणु								\
	काष्ठा iowa_bus *bus;					\
	bus = iowa_##space##_find_bus(aa);			\
	अगर (bus && bus->ops && bus->ops->name) अणु		\
		bus->ops->name al;				\
		वापस;						\
	पूर्ण							\
	__करो_##name al;						\
पूर्ण

#समावेश <यंत्र/io-defs.h>

#अघोषित DEF_PCI_AC_RET
#अघोषित DEF_PCI_AC_NORET

अटल स्थिर काष्ठा ppc_pci_io iowa_pci_io = अणु

#घोषणा DEF_PCI_AC_RET(name, ret, at, al, space, aa)	.name = iowa_##name,
#घोषणा DEF_PCI_AC_NORET(name, at, al, space, aa)	.name = iowa_##name,

#समावेश <यंत्र/io-defs.h>

#अघोषित DEF_PCI_AC_RET
#अघोषित DEF_PCI_AC_NORET

पूर्ण;

#अगर_घोषित CONFIG_PPC_INसूचीECT_MMIO
व्योम __iomem *iowa_ioremap(phys_addr_t addr, अचिन्हित दीर्घ size,
			   pgprot_t prot, व्योम *caller)
अणु
	काष्ठा iowa_bus *bus;
	व्योम __iomem *res = __ioremap_caller(addr, size, prot, caller);
	पूर्णांक busno;

	bus = iowa_pci_find(0, (अचिन्हित दीर्घ)addr);
	अगर (bus != शून्य) अणु
		busno = bus - iowa_busses;
		PCI_SET_ADDR_TOKEN(res, busno + 1);
	पूर्ण
	वापस res;
पूर्ण
#पूर्ण_अगर /* !CONFIG_PPC_INसूचीECT_MMIO */

bool io_workaround_inited;

/* Enable IO workaround */
अटल व्योम io_workaround_init(व्योम)
अणु
	अगर (io_workaround_inited)
		वापस;
	ppc_pci_io = iowa_pci_io;
	io_workaround_inited = true;
पूर्ण

/* Register new bus to support workaround */
व्योम iowa_रेजिस्टर_bus(काष्ठा pci_controller *phb, काष्ठा ppc_pci_io *ops,
		       पूर्णांक (*initfunc)(काष्ठा iowa_bus *, व्योम *), व्योम *data)
अणु
	काष्ठा iowa_bus *bus;
	काष्ठा device_node *np = phb->dn;

	io_workaround_init();

	अगर (iowa_bus_count >= IOWA_MAX_BUS) अणु
		pr_err("IOWA:Too many pci bridges, "
		       "workarounds disabled for %pOF\n", np);
		वापस;
	पूर्ण

	bus = &iowa_busses[iowa_bus_count];
	bus->phb = phb;
	bus->ops = ops;
	bus->निजी = data;

	अगर (initfunc)
		अगर ((*initfunc)(bus, data))
			वापस;

	iowa_bus_count++;

	pr_debug("IOWA:[%d]Add bus, %pOF.\n", iowa_bus_count-1, np);
पूर्ण

