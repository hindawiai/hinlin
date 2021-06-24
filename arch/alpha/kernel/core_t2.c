<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/core_t2.c
 *
 * Written by Jay A Estabrook (jestabro@amt.tay1.dec.com).
 * December 1996.
 *
 * based on CIA code by David A Rusling (david.rusling@reo.mts.dec.com)
 *
 * Code common to all T2 core logic chips.
 */

#घोषणा __EXTERN_INLINE
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_t2.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/mce.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"

/* For dumping initial DMA winकरोw settings. */
#घोषणा DEBUG_PRINT_INITIAL_SETTINGS 0

/* For dumping final DMA winकरोw settings. */
#घोषणा DEBUG_PRINT_FINAL_SETTINGS 0

/*
 * By शेष, we direct-map starting at 2GB, in order to allow the
 * maximum size direct-map winकरोw (2GB) to match the maximum amount of
 * memory (2GB) that can be present on SABLEs. But that limits the
 * floppy to DMA only via the scatter/gather winकरोw set up क्रम 8MB
 * ISA DMA, since the maximum ISA DMA address is 2GB-1.
 *
 * For now, this seems a reasonable trade-off: even though most SABLEs
 * have less than 1GB of memory, floppy usage/perक्रमmance will not
 * really be affected by क्रमcing it to go via scatter/gather...
 */
#घोषणा T2_सूचीECTMAP_2G 1

#अगर T2_सूचीECTMAP_2G
# define T2_सूचीECTMAP_START	0x80000000UL
# define T2_सूचीECTMAP_LENGTH	0x80000000UL
#अन्यथा
# define T2_सूचीECTMAP_START	0x40000000UL
# define T2_सूचीECTMAP_LENGTH	0x40000000UL
#पूर्ण_अगर

/* The ISA scatter/gather winकरोw settings. */
#घोषणा T2_ISA_SG_START		0x00800000UL
#घोषणा T2_ISA_SG_LENGTH	0x00800000UL

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
# define DBG(args)	prपूर्णांकk args
#अन्यथा
# define DBG(args)
#पूर्ण_अगर

अटल अस्थिर अचिन्हित पूर्णांक t2_mcheck_any_expected;
अटल अस्थिर अचिन्हित पूर्णांक t2_mcheck_last_taken;

/* Place to save the DMA Winकरोw रेजिस्टरs as set up by SRM
   क्रम restoration during shutकरोwn. */
अटल काष्ठा
अणु
	काष्ठा अणु
		अचिन्हित दीर्घ wbase;
		अचिन्हित दीर्घ wmask;
		अचिन्हित दीर्घ tbase;
	पूर्ण winकरोw[2];
	अचिन्हित दीर्घ hae_1;
  	अचिन्हित दीर्घ hae_2;
	अचिन्हित दीर्घ hae_3;
	अचिन्हित दीर्घ hae_4;
	अचिन्हित दीर्घ hbase;
पूर्ण t2_saved_config __attribute((common));

/*
 * Given a bus, device, and function number, compute resulting
 * configuration space address and setup the T2_HAXR2 रेजिस्टर
 * accordingly.  It is thereक्रमe not safe to have concurrent
 * invocations to configuration space access routines, but there
 * really shouldn't be any need क्रम this.
 *
 * Type 0:
 *
 *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | |D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|0|
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

	DBG(("mk_conf_addr(bus=%d, dfn=0x%x, where=0x%x,"
	     " addr=0x%lx, type1=0x%x)\n",
	     bus, device_fn, where, pci_addr, type1));

	अगर (bus == 0) अणु
		पूर्णांक device = device_fn >> 3;

		/* Type 0 configuration cycle.  */

		अगर (device > 8) अणु
			DBG(("mk_conf_addr: device (%d)>20, returning -1\n",
			     device));
			वापस -1;
		पूर्ण

		*type1 = 0;
		addr = (0x0800L << device) | ((device_fn & 7) << 8) | (where);
	पूर्ण अन्यथा अणु
		/* Type 1 configuration cycle.  */
		*type1 = 1;
		addr = (bus << 16) | (device_fn << 8) | (where);
	पूर्ण
	*pci_addr = addr;
	DBG(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	वापस 0;
पूर्ण

/*
 * NOTE: both conf_पढ़ो() and conf_ग_लिखो() may set HAE_3 when needing
 *       to करो type1 access. This is रक्षित by the use of spinlock IRQ
 *       primitives in the wrapper functions pci_अणुपढ़ो,ग_लिखोपूर्ण_config_*()
 *       defined in drivers/pci/pci.c.
 */
अटल अचिन्हित पूर्णांक
conf_पढ़ो(अचिन्हित दीर्घ addr, अचिन्हित अक्षर type1)
अणु
	अचिन्हित पूर्णांक value, cpu, taken;
	अचिन्हित दीर्घ t2_cfg = 0;

	cpu = smp_processor_id();

	DBG(("conf_read(addr=0x%lx, type1=%d)\n", addr, type1));

	/* If Type1 access, must set T2 CFG.  */
	अगर (type1) अणु
		t2_cfg = *(vulp)T2_HAE_3 & ~0xc0000000UL;
		*(vulp)T2_HAE_3 = 0x40000000UL | t2_cfg;
		mb();
	पूर्ण
	mb();
	draina();

	mcheck_expected(cpu) = 1;
	mcheck_taken(cpu) = 0;
	t2_mcheck_any_expected |= (1 << cpu);
	mb();

	/* Access configuration space. */
	value = *(vuip)addr;
	mb();
	mb();  /* magic */

	/* Wait क्रम possible mcheck. Also, this lets other CPUs clear
	   their mchecks as well, as they can reliably tell when
	   another CPU is in the midst of handling a real mcheck via
	   the "taken" function. */
	udelay(100);

	अगर ((taken = mcheck_taken(cpu))) अणु
		mcheck_taken(cpu) = 0;
		t2_mcheck_last_taken |= (1 << cpu);
		value = 0xffffffffU;
		mb();
	पूर्ण
	mcheck_expected(cpu) = 0;
	t2_mcheck_any_expected = 0;
	mb();

	/* If Type1 access, must reset T2 CFG so normal IO space ops work.  */
	अगर (type1) अणु
		*(vulp)T2_HAE_3 = t2_cfg;
		mb();
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम
conf_ग_लिखो(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक value, अचिन्हित अक्षर type1)
अणु
	अचिन्हित पूर्णांक cpu, taken;
	अचिन्हित दीर्घ t2_cfg = 0;

	cpu = smp_processor_id();

	/* If Type1 access, must set T2 CFG.  */
	अगर (type1) अणु
		t2_cfg = *(vulp)T2_HAE_3 & ~0xc0000000UL;
		*(vulp)T2_HAE_3 = t2_cfg | 0x40000000UL;
		mb();
	पूर्ण
	mb();
	draina();

	mcheck_expected(cpu) = 1;
	mcheck_taken(cpu) = 0;
	t2_mcheck_any_expected |= (1 << cpu);
	mb();

	/* Access configuration space.  */
	*(vuip)addr = value;
	mb();
	mb();  /* magic */

	/* Wait क्रम possible mcheck. Also, this lets other CPUs clear
	   their mchecks as well, as they can reliably tell when
	   this CPU is in the midst of handling a real mcheck via
	   the "taken" function. */
	udelay(100);

	अगर ((taken = mcheck_taken(cpu))) अणु
		mcheck_taken(cpu) = 0;
		t2_mcheck_last_taken |= (1 << cpu);
		mb();
	पूर्ण
	mcheck_expected(cpu) = 0;
	t2_mcheck_any_expected = 0;
	mb();

	/* If Type1 access, must reset T2 CFG so normal IO space ops work.  */
	अगर (type1) अणु
		*(vulp)T2_HAE_3 = t2_cfg;
		mb();
	पूर्ण
पूर्ण

अटल पूर्णांक
t2_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
	       पूर्णांक size, u32 *value)
अणु
	अचिन्हित दीर्घ addr, pci_addr;
	अचिन्हित अक्षर type1;
	पूर्णांक shअगरt;
	दीर्घ mask;

	अगर (mk_conf_addr(bus, devfn, where, &pci_addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	shअगरt = (where & 3) * 8;
	addr = (pci_addr << 5) + mask + T2_CONF;
	*value = conf_पढ़ो(addr, type1) >> (shअगरt);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक 
t2_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size,
		u32 value)
अणु
	अचिन्हित दीर्घ addr, pci_addr;
	अचिन्हित अक्षर type1;
	दीर्घ mask;

	अगर (mk_conf_addr(bus, devfn, where, &pci_addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	addr = (pci_addr << 5) + mask + T2_CONF;
	conf_ग_लिखो(addr, value << ((where & 3) * 8), type1);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops t2_pci_ops = 
अणु
	.पढ़ो =		t2_पढ़ो_config,
	.ग_लिखो =	t2_ग_लिखो_config,
पूर्ण;

अटल व्योम __init
t2_direct_map_winकरोw1(अचिन्हित दीर्घ base, अचिन्हित दीर्घ length)
अणु
	अचिन्हित दीर्घ temp;

	__direct_map_base = base;
	__direct_map_size = length;

	temp = (base & 0xfff00000UL) | ((base + length - 1) >> 20);
	*(vulp)T2_WBASE1 = temp | 0x80000UL; /* OR in ENABLE bit */
	temp = (length - 1) & 0xfff00000UL;
	*(vulp)T2_WMASK1 = temp;
	*(vulp)T2_TBASE1 = 0;

#अगर DEBUG_PRINT_FINAL_SETTINGS
	prपूर्णांकk("%s: setting WBASE1=0x%lx WMASK1=0x%lx TBASE1=0x%lx\n",
	       __func__, *(vulp)T2_WBASE1, *(vulp)T2_WMASK1, *(vulp)T2_TBASE1);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init
t2_sg_map_winकरोw2(काष्ठा pci_controller *hose,
		  अचिन्हित दीर्घ base,
		  अचिन्हित दीर्घ length)
अणु
	अचिन्हित दीर्घ temp;

	/* Note we can only करो 1 SG winकरोw, as the other is क्रम direct, so
	   करो an ISA SG area, especially क्रम the floppy. */
	hose->sg_isa = iommu_arena_new(hose, base, length, SMP_CACHE_BYTES);
	hose->sg_pci = शून्य;

	temp = (base & 0xfff00000UL) | ((base + length - 1) >> 20);
	*(vulp)T2_WBASE2 = temp | 0xc0000UL; /* OR in ENABLE/SG bits */
	temp = (length - 1) & 0xfff00000UL;
	*(vulp)T2_WMASK2 = temp;
	*(vulp)T2_TBASE2 = virt_to_phys(hose->sg_isa->ptes) >> 1;
	mb();

	t2_pci_tbi(hose, 0, -1); /* flush TLB all */

#अगर DEBUG_PRINT_FINAL_SETTINGS
	prपूर्णांकk("%s: setting WBASE2=0x%lx WMASK2=0x%lx TBASE2=0x%lx\n",
	       __func__, *(vulp)T2_WBASE2, *(vulp)T2_WMASK2, *(vulp)T2_TBASE2);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init
t2_save_configuration(व्योम)
अणु
#अगर DEBUG_PRINT_INITIAL_SETTINGS
	prपूर्णांकk("%s: HAE_1 was 0x%lx\n", __func__, srm_hae); /* HW is 0 */
	prपूर्णांकk("%s: HAE_2 was 0x%lx\n", __func__, *(vulp)T2_HAE_2);
	prपूर्णांकk("%s: HAE_3 was 0x%lx\n", __func__, *(vulp)T2_HAE_3);
	prपूर्णांकk("%s: HAE_4 was 0x%lx\n", __func__, *(vulp)T2_HAE_4);
	prपूर्णांकk("%s: HBASE was 0x%lx\n", __func__, *(vulp)T2_HBASE);

	prपूर्णांकk("%s: WBASE1=0x%lx WMASK1=0x%lx TBASE1=0x%lx\n", __func__,
	       *(vulp)T2_WBASE1, *(vulp)T2_WMASK1, *(vulp)T2_TBASE1);
	prपूर्णांकk("%s: WBASE2=0x%lx WMASK2=0x%lx TBASE2=0x%lx\n", __func__,
	       *(vulp)T2_WBASE2, *(vulp)T2_WMASK2, *(vulp)T2_TBASE2);
#पूर्ण_अगर

	/*
	 * Save the DMA Winकरोw रेजिस्टरs.
	 */
	t2_saved_config.winकरोw[0].wbase = *(vulp)T2_WBASE1;
	t2_saved_config.winकरोw[0].wmask = *(vulp)T2_WMASK1;
	t2_saved_config.winकरोw[0].tbase = *(vulp)T2_TBASE1;
	t2_saved_config.winकरोw[1].wbase = *(vulp)T2_WBASE2;
	t2_saved_config.winकरोw[1].wmask = *(vulp)T2_WMASK2;
	t2_saved_config.winकरोw[1].tbase = *(vulp)T2_TBASE2;

	t2_saved_config.hae_1 = srm_hae; /* HW is alपढ़ोy set to 0 */
	t2_saved_config.hae_2 = *(vulp)T2_HAE_2;
	t2_saved_config.hae_3 = *(vulp)T2_HAE_3;
	t2_saved_config.hae_4 = *(vulp)T2_HAE_4;
	t2_saved_config.hbase = *(vulp)T2_HBASE;
पूर्ण

व्योम __init
t2_init_arch(व्योम)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा resource *hae_mem;
	अचिन्हित दीर्घ temp;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NR_CPUS; i++) अणु
		mcheck_expected(i) = 0;
		mcheck_taken(i) = 0;
	पूर्ण
	t2_mcheck_any_expected = 0;
	t2_mcheck_last_taken = 0;

	/* Enable scatter/gather TLB use.  */
	temp = *(vulp)T2_IOCSR;
	अगर (!(temp & (0x1UL << 26))) अणु
		prपूर्णांकk("t2_init_arch: enabling SG TLB, IOCSR was 0x%lx\n",
		       temp);
		*(vulp)T2_IOCSR = temp | (0x1UL << 26);
		mb();	
		*(vulp)T2_IOCSR; /* पढ़ो it back to make sure */
	पूर्ण

	t2_save_configuration();

	/*
	 * Create our single hose.
	 */
	pci_isa_hose = hose = alloc_pci_controller();
	hose->io_space = &ioport_resource;
	hae_mem = alloc_resource();
	hae_mem->start = 0;
	hae_mem->end = T2_MEM_R1_MASK;
	hae_mem->name = pci_hae0_name;
	अगर (request_resource(&iomem_resource, hae_mem) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request HAE_MEM\n");
	hose->mem_space = hae_mem;
	hose->index = 0;

	hose->sparse_mem_base = T2_SPARSE_MEM - IDENT_ADDR;
	hose->dense_mem_base = T2_DENSE_MEM - IDENT_ADDR;
	hose->sparse_io_base = T2_IO - IDENT_ADDR;
	hose->dense_io_base = 0;

	/*
	 * Set up the PCI->physical memory translation winकरोws.
	 *
	 * Winकरोw 1 is direct mapped.
	 * Winकरोw 2 is scatter/gather (क्रम ISA).
	 */

	t2_direct_map_winकरोw1(T2_सूचीECTMAP_START, T2_सूचीECTMAP_LENGTH);

	/* Always make an ISA DMA winकरोw. */
	t2_sg_map_winकरोw2(hose, T2_ISA_SG_START, T2_ISA_SG_LENGTH);

	*(vulp)T2_HBASE = 0x0; /* Disable HOLES. */

	/* Zero HAE.  */
	*(vulp)T2_HAE_1 = 0; mb(); /* Sparse MEM HAE */
	*(vulp)T2_HAE_2 = 0; mb(); /* Sparse I/O HAE */
	*(vulp)T2_HAE_3 = 0; mb(); /* Config Space HAE */

	/*
	 * We also now zero out HAE_4, the dense memory HAE, so that
	 * we need not account क्रम its "offset" when accessing dense
	 * memory resources which we allocated in our normal way. This
	 * HAE would need to stay untouched were we to keep the SRM
	 * resource settings.
	 *
	 * Thus we can now run standard X servers on SABLE/LYNX. :-)
	 */
	*(vulp)T2_HAE_4 = 0; mb();
पूर्ण

व्योम
t2_समाप्त_arch(पूर्णांक mode)
अणु
	/*
	 * Restore the DMA Winकरोw रेजिस्टरs.
	 */
	*(vulp)T2_WBASE1 = t2_saved_config.winकरोw[0].wbase;
	*(vulp)T2_WMASK1 = t2_saved_config.winकरोw[0].wmask;
	*(vulp)T2_TBASE1 = t2_saved_config.winकरोw[0].tbase;
	*(vulp)T2_WBASE2 = t2_saved_config.winकरोw[1].wbase;
	*(vulp)T2_WMASK2 = t2_saved_config.winकरोw[1].wmask;
	*(vulp)T2_TBASE2 = t2_saved_config.winकरोw[1].tbase;
	mb();

	*(vulp)T2_HAE_1 = srm_hae;
	*(vulp)T2_HAE_2 = t2_saved_config.hae_2;
	*(vulp)T2_HAE_3 = t2_saved_config.hae_3;
	*(vulp)T2_HAE_4 = t2_saved_config.hae_4;
	*(vulp)T2_HBASE = t2_saved_config.hbase;
	mb();
	*(vulp)T2_HBASE; /* READ it back to ensure WRITE occurred. */
पूर्ण

व्योम
t2_pci_tbi(काष्ठा pci_controller *hose, dma_addr_t start, dma_addr_t end)
अणु
	अचिन्हित दीर्घ t2_iocsr;

	t2_iocsr = *(vulp)T2_IOCSR;

	/* set the TLB Clear bit */
	*(vulp)T2_IOCSR = t2_iocsr | (0x1UL << 28);
	mb();
	*(vulp)T2_IOCSR; /* पढ़ो it back to make sure */

	/* clear the TLB Clear bit */
	*(vulp)T2_IOCSR = t2_iocsr & ~(0x1UL << 28);
	mb();
	*(vulp)T2_IOCSR; /* पढ़ो it back to make sure */
पूर्ण

#घोषणा SIC_SEIC (1UL << 33)    /* System Event Clear */

अटल व्योम
t2_clear_errors(पूर्णांक cpu)
अणु
	काष्ठा sable_cpu_csr *cpu_regs;

	cpu_regs = (काष्ठा sable_cpu_csr *)T2_CPUn_BASE(cpu);
		
	cpu_regs->sic &= ~SIC_SEIC;

	/* Clear CPU errors.  */
	cpu_regs->bcce |= cpu_regs->bcce;
	cpu_regs->cbe  |= cpu_regs->cbe;
	cpu_regs->bcue |= cpu_regs->bcue;
	cpu_regs->dter |= cpu_regs->dter;

	*(vulp)T2_CERR1 |= *(vulp)T2_CERR1;
	*(vulp)T2_PERR1 |= *(vulp)T2_PERR1;

	mb();
	mb();  /* magic */
पूर्ण

/*
 * SABLE seems to have a "broadcast" style machine check, in that all
 * CPUs receive it. And, the issuing CPU, in the हाल of PCI Config
 * space पढ़ो/ग_लिखो faults, will also receive a second mcheck, upon
 * lowering IPL during completion processing in pci_पढ़ो_config_byte()
 * et al.
 *
 * Hence all the taken/expected/any_expected/last_taken stuff...
 */
व्योम
t2_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	पूर्णांक cpu = smp_processor_id();
#अगर_घोषित CONFIG_VERBOSE_MCHECK
	काष्ठा el_common *mchk_header = (काष्ठा el_common *)la_ptr;
#पूर्ण_अगर

	/* Clear the error beक्रमe any reporting.  */
	mb();
	mb();  /* magic */
	draina();
	t2_clear_errors(cpu);

	/* This should not actually be करोne until the logout frame is
	   examined, but, since we करोn't करो that, go on and करो this... */
	wrmces(0x7);
	mb();

	/* Now, करो testing क्रम the anomalous conditions. */
	अगर (!mcheck_expected(cpu) && t2_mcheck_any_expected) अणु
		/*
		 * FUNKY: Received mcheck on a CPU and not
		 * expecting it, but another CPU is expecting one.
		 *
		 * Just dismiss it क्रम now on this CPU...
		 */
#अगर_घोषित CONFIG_VERBOSE_MCHECK
		अगर (alpha_verbose_mcheck > 1) अणु
			prपूर्णांकk("t2_machine_check(cpu%d): any_expected 0x%x -"
			       " (assumed) spurious -"
			       " code 0x%x\n", cpu, t2_mcheck_any_expected,
			       (अचिन्हित पूर्णांक)mchk_header->code);
		पूर्ण
#पूर्ण_अगर
		वापस;
	पूर्ण

	अगर (!mcheck_expected(cpu) && !t2_mcheck_any_expected) अणु
		अगर (t2_mcheck_last_taken & (1 << cpu)) अणु
#अगर_घोषित CONFIG_VERBOSE_MCHECK
		    अगर (alpha_verbose_mcheck > 1) अणु
			prपूर्णांकk("t2_machine_check(cpu%d): last_taken 0x%x - "
			       "unexpected mcheck - code 0x%x\n",
			       cpu, t2_mcheck_last_taken,
			       (अचिन्हित पूर्णांक)mchk_header->code);
		    पूर्ण
#पूर्ण_अगर
		    t2_mcheck_last_taken = 0;
		    mb();
		    वापस;
		पूर्ण अन्यथा अणु
			t2_mcheck_last_taken = 0;
			mb();
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अगर (alpha_verbose_mcheck > 1) अणु
		prपूर्णांकk("%s t2_mcheck(cpu%d): last_taken 0x%x - "
		       "any_expected 0x%x - code 0x%x\n",
		       (mcheck_expected(cpu) ? "EX" : "UN"), cpu,
		       t2_mcheck_last_taken, t2_mcheck_any_expected,
		       (अचिन्हित पूर्णांक)mchk_header->code);
	पूर्ण
#पूर्ण_अगर

	process_mcheck_info(vector, la_ptr, "T2", mcheck_expected(cpu));
पूर्ण
