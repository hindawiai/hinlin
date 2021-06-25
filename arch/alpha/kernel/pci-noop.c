<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/pci-noop.c
 *
 * Stub PCI पूर्णांकerfaces क्रम Jensen-specअगरic kernels.
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/capability.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/syscalls.h>

#समावेश "proto.h"


/*
 * The PCI controller list.
 */

काष्ठा pci_controller *hose_head, **hose_tail = &hose_head;
काष्ठा pci_controller *pci_isa_hose;


काष्ठा pci_controller * __init
alloc_pci_controller(व्योम)
अणु
	काष्ठा pci_controller *hose;

	hose = memblock_alloc(माप(*hose), SMP_CACHE_BYTES);
	अगर (!hose)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*hose));

	*hose_tail = hose;
	hose_tail = &hose->next;

	वापस hose;
पूर्ण

काष्ठा resource * __init
alloc_resource(व्योम)
अणु
	व्योम *ptr = memblock_alloc(माप(काष्ठा resource), SMP_CACHE_BYTES);

	अगर (!ptr)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(काष्ठा resource));

	वापस ptr;
पूर्ण

SYSCALL_DEFINE3(pciconfig_iobase, दीर्घ, which, अचिन्हित दीर्घ, bus,
		अचिन्हित दीर्घ, dfn)
अणु
	काष्ठा pci_controller *hose;

	/* from hose or from bus.devfn */
	अगर (which & IOBASE_FROM_HOSE) अणु
		क्रम (hose = hose_head; hose; hose = hose->next)
			अगर (hose->index == bus)
				अवरोध;
		अगर (!hose)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		/* Special hook क्रम ISA access.  */
		अगर (bus == 0 && dfn == 0)
			hose = pci_isa_hose;
		अन्यथा
			वापस -ENODEV;
	पूर्ण

	चयन (which & ~IOBASE_FROM_HOSE) अणु
	हाल IOBASE_HOSE:
		वापस hose->index;
	हाल IOBASE_SPARSE_MEM:
		वापस hose->sparse_mem_base;
	हाल IOBASE_DENSE_MEM:
		वापस hose->dense_mem_base;
	हाल IOBASE_SPARSE_IO:
		वापस hose->sparse_io_base;
	हाल IOBASE_DENSE_IO:
		वापस hose->dense_io_base;
	हाल IOBASE_ROOT_BUS:
		वापस hose->bus->number;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

SYSCALL_DEFINE5(pciconfig_पढ़ो, अचिन्हित दीर्घ, bus, अचिन्हित दीर्घ, dfn,
		अचिन्हित दीर्घ, off, अचिन्हित दीर्घ, len, व्योम __user *, buf)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अन्यथा
		वापस -ENODEV;
पूर्ण

SYSCALL_DEFINE5(pciconfig_ग_लिखो, अचिन्हित दीर्घ, bus, अचिन्हित दीर्घ, dfn,
		अचिन्हित दीर्घ, off, अचिन्हित दीर्घ, len, व्योम __user *, buf)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अन्यथा
		वापस -ENODEV;
पूर्ण
