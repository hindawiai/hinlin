<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *      linux/arch/alpha/kernel/core_polaris.c
 *
 * POLARIS chip-specअगरic code
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_polaris.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ptrace.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"

/*
 * BIOS32-style PCI पूर्णांकerface:
 */

#घोषणा DEBUG_CONFIG 0

#अगर DEBUG_CONFIG
# define DBG_CFG(args)	prपूर्णांकk args
#अन्यथा
# define DBG_CFG(args)
#पूर्ण_अगर


/*
 * Given a bus, device, and function number, compute resulting
 * configuration space address.  This is fairly straightक्रमward
 * on POLARIS, since the chip itself generates Type 0 or Type 1
 * cycles स्वतःmatically depending on the bus number (Bus 0 is
 * hardwired to Type 0, all others are Type 1.  Peer bridges
 * are not supported).
 *
 * All types:
 *
 *  3 3 3 3|3 3 3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1|1|1|1|1|0|0|1|1|1|1|1|1|1|1|0|B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|x|x|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	23:16	bus number (8 bits = 128 possible buses)
 *	15:11	Device number (5 bits)
 *	10:8	function number
 *	 7:2	रेजिस्टर number
 *  
 * Notes:
 *	The function number selects which function of a multi-function device 
 *	(e.g., scsi and ethernet).
 * 
 *	The रेजिस्टर selects a DWORD (32 bit) रेजिस्टर offset.  Hence it
 *	करोesn't get shअगरted by 2 bits as we want to "drop" the bottom two
 *	bits.
 */

अटल पूर्णांक
mk_conf_addr(काष्ठा pci_bus *pbus, अचिन्हित पूर्णांक device_fn, पूर्णांक where,
	     अचिन्हित दीर्घ *pci_addr, u8 *type1)
अणु
	u8 bus = pbus->number;

	*type1 = (bus == 0) ? 0 : 1;
	*pci_addr = (bus << 16) | (device_fn << 8) | (where) |
		    POLARIS_DENSE_CONFIG_BASE;

        DBG_CFG(("mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x,"
                 " returning address 0x%p\n"
                 bus, device_fn, where, *pci_addr));

	वापस 0;
पूर्ण

अटल पूर्णांक
polaris_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		    पूर्णांक size, u32 *value)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित अक्षर type1;

	अगर (mk_conf_addr(bus, devfn, where, &addr, &type1))
                वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन (size) अणु
	हाल 1:
		*value = __kernel_ldbu(*(vucp)addr);
		अवरोध;
	हाल 2:
		*value = __kernel_ldwu(*(vusp)addr);
		अवरोध;
	हाल 4:
		*value = *(vuip)addr;
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण


अटल पूर्णांक 
polaris_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		     पूर्णांक size, u32 value)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित अक्षर type1;

	अगर (mk_conf_addr(bus, devfn, where, &addr, &type1))
                वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन (size) अणु
	हाल 1:
		__kernel_stb(value, *(vucp)addr);
		mb();
		__kernel_ldbu(*(vucp)addr);
		अवरोध;
	हाल 2:
		__kernel_stw(value, *(vusp)addr);
		mb();
		__kernel_ldwu(*(vusp)addr);
		अवरोध;
	हाल 4:
		*(vuip)addr = value;
		mb();
		*(vuip)addr;
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops polaris_pci_ops = 
अणु
	.पढ़ो =		polaris_पढ़ो_config,
	.ग_लिखो =	polaris_ग_लिखो_config,
पूर्ण;

व्योम __init
polaris_init_arch(व्योम)
अणु
	काष्ठा pci_controller *hose;

	/* May need to initialize error reporting (see PCICTL0/1), but
	 * क्रम now assume that the firmware has करोne the right thing
	 * alपढ़ोy.
	 */
#अगर 0
	prपूर्णांकk("polaris_init_arch(): trusting firmware for setup\n");
#पूर्ण_अगर

	/*
	 * Create our single hose.
	 */

	pci_isa_hose = hose = alloc_pci_controller();
	hose->io_space = &ioport_resource;
	hose->mem_space = &iomem_resource;
	hose->index = 0;

	hose->sparse_mem_base = 0;
	hose->dense_mem_base = POLARIS_DENSE_MEM_BASE - IDENT_ADDR;
	hose->sparse_io_base = 0;
	hose->dense_io_base = POLARIS_DENSE_IO_BASE - IDENT_ADDR;

	hose->sg_isa = hose->sg_pci = शून्य;

	/* The I/O winकरोw is fixed at 2G @ 2G.  */
	__direct_map_base = 0x80000000;
	__direct_map_size = 0x80000000;
पूर्ण

अटल अंतरभूत व्योम
polaris_pci_clr_err(व्योम)
अणु
	*(vusp)POLARIS_W_STATUS;
	/* Write 1's to settable bits to clear errors */
	*(vusp)POLARIS_W_STATUS = 0x7800;
	mb();
	*(vusp)POLARIS_W_STATUS;
पूर्ण

व्योम
polaris_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	/* Clear the error beक्रमe any reporting.  */
	mb();
	mb();
	draina();
	polaris_pci_clr_err();
	wrmces(0x7);
	mb();

	process_mcheck_info(vector, la_ptr, "POLARIS",
			    mcheck_expected(0));
पूर्ण
