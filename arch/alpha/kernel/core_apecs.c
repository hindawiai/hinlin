<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/core_apecs.c
 *
 * Rewritten क्रम Apecs from the lca.c from:
 *
 * Written by David Mosberger (davidm@cs.arizona.edu) with some code
 * taken from Dave Rusling's (david.rusling@reo.mts.dec.com) 32-bit
 * bios code.
 *
 * Code common to all APECS core logic chips.
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_apecs.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/mce.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"

/*
 * NOTE: Herein lie back-to-back mb inकाष्ठाions.  They are magic. 
 * One plausible explanation is that the i/o controller करोes not properly
 * handle the प्रणाली transaction.  Another involves timing.  Ho hum.
 */

/*
 * BIOS32-style PCI पूर्णांकerface:
 */

#घोषणा DEBUG_CONFIG 0

#अगर DEBUG_CONFIG
# define DBGC(args)	prपूर्णांकk args
#अन्यथा
# define DBGC(args)
#पूर्ण_अगर

#घोषणा vuip	अस्थिर अचिन्हित पूर्णांक  *

/*
 * Given a bus, device, and function number, compute resulting
 * configuration space address and setup the APECS_HAXR2 रेजिस्टर
 * accordingly.  It is thereक्रमe not safe to have concurrent
 * invocations to configuration space access routines, but there
 * really shouldn't be any need क्रम this.
 *
 * Type 0:
 *
 *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | | | | | | | | | | | | | | | | | | | | | | |F|F|F|R|R|R|R|R|R|0|0|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	31:11	Device select bit.
 * 	10:8	Function number
 * 	 7:2	Register number
 *
 * Type 1:
 *
 *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|1|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	31:24	reserved
 *	23:16	bus number (8 bits = 128 possible buses)
 *	15:11	Device number (5 bits)
 *	10:8	function number
 *	 7:2	रेजिस्टर number
 *  
 * Notes:
 *	The function number selects which function of a multi-function device 
 *	(e.g., SCSI and Ethernet).
 * 
 *	The रेजिस्टर selects a DWORD (32 bit) रेजिस्टर offset.  Hence it
 *	करोesn't get shअगरted by 2 bits as we want to "drop" the bottom two
 *	bits.
 */

अटल पूर्णांक
mk_conf_addr(काष्ठा pci_bus *pbus, अचिन्हित पूर्णांक device_fn, पूर्णांक where,
	     अचिन्हित दीर्घ *pci_addr, अचिन्हित अक्षर *type1)
अणु
	अचिन्हित दीर्घ addr;
	u8 bus = pbus->number;

	DBGC(("mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x,"
	      " pci_addr=0x%p, type1=0x%p)\n",
	      bus, device_fn, where, pci_addr, type1));

	अगर (bus == 0) अणु
		पूर्णांक device = device_fn >> 3;

		/* type 0 configuration cycle: */

		अगर (device > 20) अणु
			DBGC(("mk_conf_addr: device (%d) > 20, returning -1\n",
			      device));
			वापस -1;
		पूर्ण

		*type1 = 0;
		addr = (device_fn << 8) | (where);
	पूर्ण अन्यथा अणु
		/* type 1 configuration cycle: */
		*type1 = 1;
		addr = (bus << 16) | (device_fn << 8) | (where);
	पूर्ण
	*pci_addr = addr;
	DBGC(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
conf_पढ़ो(अचिन्हित दीर्घ addr, अचिन्हित अक्षर type1)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक stat0, value;
	अचिन्हित पूर्णांक haxr2 = 0;

	local_irq_save(flags);	/* aव्योम getting hit by machine check */

	DBGC(("conf_read(addr=0x%lx, type1=%d)\n", addr, type1));

	/* Reset status रेजिस्टर to aव्योम losing errors.  */
	stat0 = *(vuip)APECS_IOC_DCSR;
	*(vuip)APECS_IOC_DCSR = stat0;
	mb();
	DBGC(("conf_read: APECS DCSR was 0x%x\n", stat0));

	/* If Type1 access, must set HAE #2. */
	अगर (type1) अणु
		haxr2 = *(vuip)APECS_IOC_HAXR2;
		mb();
		*(vuip)APECS_IOC_HAXR2 = haxr2 | 1;
		DBGC(("conf_read: TYPE1 access\n"));
	पूर्ण

	draina();
	mcheck_expected(0) = 1;
	mcheck_taken(0) = 0;
	mb();

	/* Access configuration space.  */

	/* Some SRMs step on these रेजिस्टरs during a machine check.  */
	यंत्र अस्थिर("ldl %0,%1; mb; mb" : "=r"(value) : "m"(*(vuip)addr)
		     : "$9", "$10", "$11", "$12", "$13", "$14", "memory");

	अगर (mcheck_taken(0)) अणु
		mcheck_taken(0) = 0;
		value = 0xffffffffU;
		mb();
	पूर्ण
	mcheck_expected(0) = 0;
	mb();

#अगर 1
	/*
	 * david.rusling@reo.mts.dec.com.  This code is needed क्रम the
	 * EB64+ as it करोes not generate a machine check (why I करोn't
	 * know).  When we build kernels क्रम one particular platक्रमm
	 * then we can make this conditional on the type.
	 */
	draina();

	/* Now look क्रम any errors.  */
	stat0 = *(vuip)APECS_IOC_DCSR;
	DBGC(("conf_read: APECS DCSR after read 0x%x\n", stat0));

	/* Is any error bit set? */
	अगर (stat0 & 0xffe0U) अणु
		/* If not NDEV, prपूर्णांक status.  */
		अगर (!(stat0 & 0x0800)) अणु
			prपूर्णांकk("apecs.c:conf_read: got stat0=%x\n", stat0);
		पूर्ण

		/* Reset error status.  */
		*(vuip)APECS_IOC_DCSR = stat0;
		mb();
		wrmces(0x7);			/* reset machine check */
		value = 0xffffffff;
	पूर्ण
#पूर्ण_अगर

	/* If Type1 access, must reset HAE #2 so normal IO space ops work.  */
	अगर (type1) अणु
		*(vuip)APECS_IOC_HAXR2 = haxr2 & ~1;
		mb();
	पूर्ण
	local_irq_restore(flags);

	वापस value;
पूर्ण

अटल व्योम
conf_ग_लिखो(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक value, अचिन्हित अक्षर type1)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक stat0;
	अचिन्हित पूर्णांक haxr2 = 0;

	local_irq_save(flags);	/* aव्योम getting hit by machine check */

	/* Reset status रेजिस्टर to aव्योम losing errors.  */
	stat0 = *(vuip)APECS_IOC_DCSR;
	*(vuip)APECS_IOC_DCSR = stat0;
	mb();

	/* If Type1 access, must set HAE #2. */
	अगर (type1) अणु
		haxr2 = *(vuip)APECS_IOC_HAXR2;
		mb();
		*(vuip)APECS_IOC_HAXR2 = haxr2 | 1;
	पूर्ण

	draina();
	mcheck_expected(0) = 1;
	mb();

	/* Access configuration space.  */
	*(vuip)addr = value;
	mb();
	mb();  /* magic */
	mcheck_expected(0) = 0;
	mb();

#अगर 1
	/*
	 * david.rusling@reo.mts.dec.com.  This code is needed क्रम the
	 * EB64+ as it करोes not generate a machine check (why I करोn't
	 * know).  When we build kernels क्रम one particular platक्रमm
	 * then we can make this conditional on the type.
	 */
	draina();

	/* Now look क्रम any errors.  */
	stat0 = *(vuip)APECS_IOC_DCSR;

	/* Is any error bit set? */
	अगर (stat0 & 0xffe0U) अणु
		/* If not NDEV, prपूर्णांक status.  */
		अगर (!(stat0 & 0x0800)) अणु
			prपूर्णांकk("apecs.c:conf_write: got stat0=%x\n", stat0);
		पूर्ण

		/* Reset error status.  */
		*(vuip)APECS_IOC_DCSR = stat0;
		mb();
		wrmces(0x7);			/* reset machine check */
	पूर्ण
#पूर्ण_अगर

	/* If Type1 access, must reset HAE #2 so normal IO space ops work.  */
	अगर (type1) अणु
		*(vuip)APECS_IOC_HAXR2 = haxr2 & ~1;
		mb();
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक
apecs_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		  पूर्णांक size, u32 *value)
अणु
	अचिन्हित दीर्घ addr, pci_addr;
	अचिन्हित अक्षर type1;
	दीर्घ mask;
	पूर्णांक shअगरt;

	अगर (mk_conf_addr(bus, devfn, where, &pci_addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	shअगरt = (where & 3) * 8;
	addr = (pci_addr << 5) + mask + APECS_CONF;
	*value = conf_पढ़ो(addr, type1) >> (shअगरt);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक
apecs_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		   पूर्णांक size, u32 value)
अणु
	अचिन्हित दीर्घ addr, pci_addr;
	अचिन्हित अक्षर type1;
	दीर्घ mask;

	अगर (mk_conf_addr(bus, devfn, where, &pci_addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	addr = (pci_addr << 5) + mask + APECS_CONF;
	conf_ग_लिखो(addr, value << ((where & 3) * 8), type1);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops apecs_pci_ops = 
अणु
	.पढ़ो =		apecs_पढ़ो_config,
	.ग_लिखो =	apecs_ग_लिखो_config,
पूर्ण;

व्योम
apecs_pci_tbi(काष्ठा pci_controller *hose, dma_addr_t start, dma_addr_t end)
अणु
	wmb();
	*(vip)APECS_IOC_TBIA = 0;
	mb();
पूर्ण

व्योम __init
apecs_init_arch(व्योम)
अणु
	काष्ठा pci_controller *hose;

	/*
	 * Create our single hose.
	 */

	pci_isa_hose = hose = alloc_pci_controller();
	hose->io_space = &ioport_resource;
	hose->mem_space = &iomem_resource;
	hose->index = 0;

	hose->sparse_mem_base = APECS_SPARSE_MEM - IDENT_ADDR;
	hose->dense_mem_base = APECS_DENSE_MEM - IDENT_ADDR;
	hose->sparse_io_base = APECS_IO - IDENT_ADDR;
	hose->dense_io_base = 0;

	/*
	 * Set up the PCI to मुख्य memory translation winकरोws.
	 *
	 * Winकरोw 1 is direct access 1GB at 1GB
	 * Winकरोw 2 is scatter-gather 8MB at 8MB (क्रम isa)
	 */
	hose->sg_isa = iommu_arena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	hose->sg_pci = शून्य;
	__direct_map_base = 0x40000000;
	__direct_map_size = 0x40000000;

	*(vuip)APECS_IOC_PB1R = __direct_map_base | 0x00080000;
	*(vuip)APECS_IOC_PM1R = (__direct_map_size - 1) & 0xfff00000U;
	*(vuip)APECS_IOC_TB1R = 0;

	*(vuip)APECS_IOC_PB2R = hose->sg_isa->dma_base | 0x000c0000;
	*(vuip)APECS_IOC_PM2R = (hose->sg_isa->size - 1) & 0xfff00000;
	*(vuip)APECS_IOC_TB2R = virt_to_phys(hose->sg_isa->ptes) >> 1;

	apecs_pci_tbi(hose, 0, -1);

	/*
	 * Finally, clear the HAXR2 रेजिस्टर, which माला_लो used
	 * क्रम PCI Config Space accesses. That is the way
	 * we want to use it, and we करो not want to depend on
	 * what ARC or SRM might have left behind...
	 */
	*(vuip)APECS_IOC_HAXR2 = 0;
	mb();
पूर्ण

व्योम
apecs_pci_clr_err(व्योम)
अणु
	अचिन्हित पूर्णांक jd;

	jd = *(vuip)APECS_IOC_DCSR;
	अगर (jd & 0xffe0L) अणु
		*(vuip)APECS_IOC_SEAR;
		*(vuip)APECS_IOC_DCSR = jd | 0xffe1L;
		mb();
		*(vuip)APECS_IOC_DCSR;
	पूर्ण
	*(vuip)APECS_IOC_TBIA = (अचिन्हित पूर्णांक)APECS_IOC_TBIA;
	mb();
	*(vuip)APECS_IOC_TBIA;
पूर्ण

व्योम
apecs_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	काष्ठा el_common *mchk_header;
	काष्ठा el_apecs_procdata *mchk_procdata;
	काष्ठा el_apecs_sysdata_mcheck *mchk_sysdata;

	mchk_header = (काष्ठा el_common *)la_ptr;

	mchk_procdata = (काष्ठा el_apecs_procdata *)
		(la_ptr + mchk_header->proc_offset
		 - माप(mchk_procdata->paltemp));

	mchk_sysdata = (काष्ठा el_apecs_sysdata_mcheck *)
		(la_ptr + mchk_header->sys_offset);


	/* Clear the error beक्रमe any reporting.  */
	mb();
	mb(); /* magic */
	draina();
	apecs_pci_clr_err();
	wrmces(0x7);		/* reset machine check pending flag */
	mb();

	process_mcheck_info(vector, la_ptr, "APECS",
			    (mcheck_expected(0)
			     && (mchk_sysdata->epic_dcsr & 0x0c00UL)));
पूर्ण
