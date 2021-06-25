<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/core_mcpcia.c
 *
 * Based on code written by David A Rusling (david.rusling@reo.mts.dec.com).
 *
 * Code common to all MCbus-PCI Adaptor core logic chipsets
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_mcpcia.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/ptrace.h>

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

#घोषणा DEBUG_CFG 0

#अगर DEBUG_CFG
# define DBG_CFG(args)	prपूर्णांकk args
#अन्यथा
# define DBG_CFG(args)
#पूर्ण_अगर

/*
 * Given a bus, device, and function number, compute resulting
 * configuration space address and setup the MCPCIA_HAXR2 रेजिस्टर
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

अटल अचिन्हित पूर्णांक
conf_पढ़ो(अचिन्हित दीर्घ addr, अचिन्हित अक्षर type1,
	  काष्ठा pci_controller *hose)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mid = MCPCIA_HOSE2MID(hose->index);
	अचिन्हित पूर्णांक stat0, value, cpu;

	cpu = smp_processor_id();

	local_irq_save(flags);

	DBG_CFG(("conf_read(addr=0x%lx, type1=%d, hose=%d)\n",
		 addr, type1, mid));

	/* Reset status रेजिस्टर to aव्योम losing errors.  */
	stat0 = *(vuip)MCPCIA_CAP_ERR(mid);
	*(vuip)MCPCIA_CAP_ERR(mid) = stat0;
	mb();
	*(vuip)MCPCIA_CAP_ERR(mid);
	DBG_CFG(("conf_read: MCPCIA_CAP_ERR(%d) was 0x%x\n", mid, stat0));

	mb();
	draina();
	mcheck_expected(cpu) = 1;
	mcheck_taken(cpu) = 0;
	mcheck_extra(cpu) = mid;
	mb();

	/* Access configuration space.  */
	value = *((vuip)addr);
	mb();
	mb();  /* magic */

	अगर (mcheck_taken(cpu)) अणु
		mcheck_taken(cpu) = 0;
		value = 0xffffffffU;
		mb();
	पूर्ण
	mcheck_expected(cpu) = 0;
	mb();

	DBG_CFG(("conf_read(): finished\n"));

	local_irq_restore(flags);
	वापस value;
पूर्ण

अटल व्योम
conf_ग_लिखो(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक value, अचिन्हित अक्षर type1,
	   काष्ठा pci_controller *hose)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mid = MCPCIA_HOSE2MID(hose->index);
	अचिन्हित पूर्णांक stat0, cpu;

	cpu = smp_processor_id();

	local_irq_save(flags);	/* aव्योम getting hit by machine check */

	/* Reset status रेजिस्टर to aव्योम losing errors.  */
	stat0 = *(vuip)MCPCIA_CAP_ERR(mid);
	*(vuip)MCPCIA_CAP_ERR(mid) = stat0; mb();
	*(vuip)MCPCIA_CAP_ERR(mid);
	DBG_CFG(("conf_write: MCPCIA CAP_ERR(%d) was 0x%x\n", mid, stat0));

	draina();
	mcheck_expected(cpu) = 1;
	mcheck_extra(cpu) = mid;
	mb();

	/* Access configuration space.  */
	*((vuip)addr) = value;
	mb();
	mb();  /* magic */
	*(vuip)MCPCIA_CAP_ERR(mid); /* पढ़ो to क्रमce the ग_लिखो */
	mcheck_expected(cpu) = 0;
	mb();

	DBG_CFG(("conf_write(): finished\n"));
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक
mk_conf_addr(काष्ठा pci_bus *pbus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
	     काष्ठा pci_controller *hose, अचिन्हित दीर्घ *pci_addr,
	     अचिन्हित अक्षर *type1)
अणु
	u8 bus = pbus->number;
	अचिन्हित दीर्घ addr;

	DBG_CFG(("mk_conf_addr(bus=%d,devfn=0x%x,hose=%d,where=0x%x,"
		 " pci_addr=0x%p, type1=0x%p)\n",
		 bus, devfn, hose->index, where, pci_addr, type1));

	/* Type 1 configuration cycle क्रम *ALL* busses.  */
	*type1 = 1;

	अगर (!pbus->parent) /* No parent means peer PCI bus. */
		bus = 0;
	addr = (bus << 16) | (devfn << 8) | (where);
	addr <<= 5; /* swizzle क्रम SPARSE */
	addr |= hose->config_space_base;

	*pci_addr = addr;
	DBG_CFG(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	वापस 0;
पूर्ण

अटल पूर्णांक
mcpcia_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		   पूर्णांक size, u32 *value)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;
	अचिन्हित दीर्घ addr, w;
	अचिन्हित अक्षर type1;

	अगर (mk_conf_addr(bus, devfn, where, hose, &addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	addr |= (size - 1) * 8;
	w = conf_पढ़ो(addr, type1, hose);
	चयन (size) अणु
	हाल 1:
		*value = __kernel_extbl(w, where & 3);
		अवरोध;
	हाल 2:
		*value = __kernel_extwl(w, where & 3);
		अवरोध;
	हाल 4:
		*value = w;
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक
mcpcia_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		    पूर्णांक size, u32 value)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;
	अचिन्हित दीर्घ addr;
	अचिन्हित अक्षर type1;

	अगर (mk_conf_addr(bus, devfn, where, hose, &addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	addr |= (size - 1) * 8;
	value = __kernel_insql(value, where & 3);
	conf_ग_लिखो(addr, value, type1, hose);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops mcpcia_pci_ops = 
अणु
	.पढ़ो =		mcpcia_पढ़ो_config,
	.ग_लिखो =	mcpcia_ग_लिखो_config,
पूर्ण;

व्योम
mcpcia_pci_tbi(काष्ठा pci_controller *hose, dma_addr_t start, dma_addr_t end)
अणु
	wmb();
	*(vuip)MCPCIA_SG_TBIA(MCPCIA_HOSE2MID(hose->index)) = 0;
	mb();
पूर्ण

अटल पूर्णांक __init
mcpcia_probe_hose(पूर्णांक h)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक mid = MCPCIA_HOSE2MID(h);
	अचिन्हित पूर्णांक pci_rev;

	/* Gotta be REAL careful.  If hose is असलent, we get an mcheck.  */

	mb();
	mb();
	draina();
	wrmces(7);

	mcheck_expected(cpu) = 2;	/* indicates probing */
	mcheck_taken(cpu) = 0;
	mcheck_extra(cpu) = mid;
	mb();

	/* Access the bus revision word. */
	pci_rev = *(vuip)MCPCIA_REV(mid);

	mb();
	mb();  /* magic */
	अगर (mcheck_taken(cpu)) अणु
		mcheck_taken(cpu) = 0;
		pci_rev = 0xffffffff;
		mb();
	पूर्ण
	mcheck_expected(cpu) = 0;
	mb();

	वापस (pci_rev >> 16) == PCI_CLASS_BRIDGE_HOST;
पूर्ण

अटल व्योम __init
mcpcia_new_hose(पूर्णांक h)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा resource *io, *mem, *hae_mem;
	पूर्णांक mid = MCPCIA_HOSE2MID(h);

	hose = alloc_pci_controller();
	अगर (h == 0)
		pci_isa_hose = hose;
	io = alloc_resource();
	mem = alloc_resource();
	hae_mem = alloc_resource();
			
	hose->io_space = io;
	hose->mem_space = hae_mem;
	hose->sparse_mem_base = MCPCIA_SPARSE(mid) - IDENT_ADDR;
	hose->dense_mem_base = MCPCIA_DENSE(mid) - IDENT_ADDR;
	hose->sparse_io_base = MCPCIA_IO(mid) - IDENT_ADDR;
	hose->dense_io_base = 0;
	hose->config_space_base = MCPCIA_CONF(mid);
	hose->index = h;

	io->start = MCPCIA_IO(mid) - MCPCIA_IO_BIAS;
	io->end = io->start + 0xffff;
	io->name = pci_io_names[h];
	io->flags = IORESOURCE_IO;

	mem->start = MCPCIA_DENSE(mid) - MCPCIA_MEM_BIAS;
	mem->end = mem->start + 0xffffffff;
	mem->name = pci_mem_names[h];
	mem->flags = IORESOURCE_MEM;

	hae_mem->start = mem->start;
	hae_mem->end = mem->start + MCPCIA_MEM_MASK;
	hae_mem->name = pci_hae0_name;
	hae_mem->flags = IORESOURCE_MEM;

	अगर (request_resource(&ioport_resource, io) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request IO on hose %d\n", h);
	अगर (request_resource(&iomem_resource, mem) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request MEM on hose %d\n", h);
	अगर (request_resource(mem, hae_mem) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request HAE_MEM on hose %d\n", h);
पूर्ण

अटल व्योम
mcpcia_pci_clr_err(पूर्णांक mid)
अणु
	*(vuip)MCPCIA_CAP_ERR(mid);
	*(vuip)MCPCIA_CAP_ERR(mid) = 0xffffffff;   /* Clear them all.  */
	mb();
	*(vuip)MCPCIA_CAP_ERR(mid);  /* Re-पढ़ो क्रम क्रमce ग_लिखो.  */
पूर्ण

अटल व्योम __init
mcpcia_startup_hose(काष्ठा pci_controller *hose)
अणु
	पूर्णांक mid = MCPCIA_HOSE2MID(hose->index);
	अचिन्हित पूर्णांक पंचांगp;

	mcpcia_pci_clr_err(mid);

	/* 
	 * Set up error reporting.
	 */
	पंचांगp = *(vuip)MCPCIA_CAP_ERR(mid);
	पंचांगp |= 0x0006;		/* master/target पात */
	*(vuip)MCPCIA_CAP_ERR(mid) = पंचांगp;
	mb();
	पंचांगp = *(vuip)MCPCIA_CAP_ERR(mid);

	/*
	 * Set up the PCI->physical memory translation winकरोws.
	 *
	 * Winकरोw 0 is scatter-gather 8MB at 8MB (क्रम isa)
	 * Winकरोw 1 is scatter-gather (up to) 1GB at 1GB (क्रम pci)
	 * Winकरोw 2 is direct access 2GB at 2GB
	 */
	hose->sg_isa = iommu_arena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	hose->sg_pci = iommu_arena_new(hose, 0x40000000,
				       size_क्रम_memory(0x40000000),
				       SMP_CACHE_BYTES);

	__direct_map_base = 0x80000000;
	__direct_map_size = 0x80000000;

	*(vuip)MCPCIA_W0_BASE(mid) = hose->sg_isa->dma_base | 3;
	*(vuip)MCPCIA_W0_MASK(mid) = (hose->sg_isa->size - 1) & 0xfff00000;
	*(vuip)MCPCIA_T0_BASE(mid) = virt_to_phys(hose->sg_isa->ptes) >> 8;

	*(vuip)MCPCIA_W1_BASE(mid) = hose->sg_pci->dma_base | 3;
	*(vuip)MCPCIA_W1_MASK(mid) = (hose->sg_pci->size - 1) & 0xfff00000;
	*(vuip)MCPCIA_T1_BASE(mid) = virt_to_phys(hose->sg_pci->ptes) >> 8;

	*(vuip)MCPCIA_W2_BASE(mid) = __direct_map_base | 1;
	*(vuip)MCPCIA_W2_MASK(mid) = (__direct_map_size - 1) & 0xfff00000;
	*(vuip)MCPCIA_T2_BASE(mid) = 0;

	*(vuip)MCPCIA_W3_BASE(mid) = 0x0;

	mcpcia_pci_tbi(hose, 0, -1);

	*(vuip)MCPCIA_HBASE(mid) = 0x0;
	mb();

	*(vuip)MCPCIA_HAE_MEM(mid) = 0U;
	mb();
	*(vuip)MCPCIA_HAE_MEM(mid); /* पढ़ो it back. */
	*(vuip)MCPCIA_HAE_IO(mid) = 0;
	mb();
	*(vuip)MCPCIA_HAE_IO(mid);  /* पढ़ो it back. */
पूर्ण

व्योम __init
mcpcia_init_arch(व्योम)
अणु
	/* With multiple PCI busses, we play with I/O as physical addrs.  */
	ioport_resource.end = ~0UL;

	/* Allocate hose 0.  That's the one that all the ISA junk hangs
	   off of, from which we'll be रेजिस्टरing stuff here in a bit.
	   Other hose detection is करोne in mcpcia_init_hoses, which is
	   called from init_IRQ.  */

	mcpcia_new_hose(0);
पूर्ण

/* This is called from init_IRQ, since we cannot take पूर्णांकerrupts
   beक्रमe then.  Which means we cannot करो this in init_arch.  */

व्योम __init
mcpcia_init_hoses(व्योम)
अणु
	काष्ठा pci_controller *hose;
	पूर्णांक hose_count;
	पूर्णांक h;

	/* First, find how many hoses we have.  */
	hose_count = 0;
	क्रम (h = 0; h < MCPCIA_MAX_HOSES; ++h) अणु
		अगर (mcpcia_probe_hose(h)) अणु
			अगर (h != 0)
				mcpcia_new_hose(h);
			hose_count++;
		पूर्ण
	पूर्ण

	prपूर्णांकk("mcpcia_init_hoses: found %d hoses\n", hose_count);

	/* Now करो init क्रम each hose.  */
	क्रम (hose = hose_head; hose; hose = hose->next)
		mcpcia_startup_hose(hose);
पूर्ण

अटल व्योम
mcpcia_prपूर्णांक_uncorrectable(काष्ठा el_MCPCIA_uncorrected_frame_mcheck *logout)
अणु
	काष्ठा el_common_EV5_uncorrectable_mcheck *frame;
	पूर्णांक i;

	frame = &logout->procdata;

	/* Prपूर्णांक PAL fields */
	क्रम (i = 0; i < 24; i += 2) अणु
		prपूर्णांकk("  paltmp[%d-%d] = %16lx %16lx\n",
		       i, i+1, frame->paltemp[i], frame->paltemp[i+1]);
	पूर्ण
	क्रम (i = 0; i < 8; i += 2) अणु
		prपूर्णांकk("  shadow[%d-%d] = %16lx %16lx\n",
		       i, i+1, frame->shaकरोw[i], 
		       frame->shaकरोw[i+1]);
	पूर्ण
	prपूर्णांकk("  Addr of excepting instruction  = %16lx\n",
	       frame->exc_addr);
	prपूर्णांकk("  Summary of arithmetic traps    = %16lx\n",
	       frame->exc_sum);
	prपूर्णांकk("  Exception mask                 = %16lx\n",
	       frame->exc_mask);
	prपूर्णांकk("  Base address for PALcode       = %16lx\n",
	       frame->pal_base);
	prपूर्णांकk("  Interrupt Status Reg           = %16lx\n",
	       frame->isr);
	prपूर्णांकk("  CURRENT SETUP OF EV5 IBOX      = %16lx\n",
	       frame->icsr);
	prपूर्णांकk("  I-CACHE Reg %s parity error   = %16lx\n",
	       (frame->ic_perr_stat & 0x800L) ? 
	       "Data" : "Tag", 
	       frame->ic_perr_stat); 
	prपूर्णांकk("  D-CACHE error Reg              = %16lx\n",
	       frame->dc_perr_stat);
	अगर (frame->dc_perr_stat & 0x2) अणु
		चयन (frame->dc_perr_stat & 0x03c) अणु
		हाल 8:
			prपूर्णांकk("    Data error in bank 1\n");
			अवरोध;
		हाल 4:
			prपूर्णांकk("    Data error in bank 0\n");
			अवरोध;
		हाल 20:
			prपूर्णांकk("    Tag error in bank 1\n");
			अवरोध;
		हाल 10:
			prपूर्णांकk("    Tag error in bank 0\n");
			अवरोध;
		पूर्ण
	पूर्ण
	prपूर्णांकk("  Effective VA                   = %16lx\n",
	       frame->va);
	prपूर्णांकk("  Reason for D-stream            = %16lx\n",
	       frame->mm_stat);
	prपूर्णांकk("  EV5 SCache address             = %16lx\n",
	       frame->sc_addr);
	prपूर्णांकk("  EV5 SCache TAG/Data parity     = %16lx\n",
	       frame->sc_stat);
	prपूर्णांकk("  EV5 BC_TAG_ADDR                = %16lx\n",
	       frame->bc_tag_addr);
	prपूर्णांकk("  EV5 EI_ADDR: Phys addr of Xfer = %16lx\n",
	       frame->ei_addr);
	prपूर्णांकk("  Fill Syndrome                  = %16lx\n",
	       frame->fill_syndrome);
	prपूर्णांकk("  EI_STAT reg                    = %16lx\n",
	       frame->ei_stat);
	prपूर्णांकk("  LD_LOCK                        = %16lx\n",
	       frame->ld_lock);
पूर्ण

अटल व्योम
mcpcia_prपूर्णांक_प्रणाली_area(अचिन्हित दीर्घ la_ptr)
अणु
	काष्ठा el_common *frame;
	काष्ठा pci_controller *hose;

	काष्ठा IOD_subpacket अणु
	  अचिन्हित दीर्घ base;
	  अचिन्हित पूर्णांक whoami;
	  अचिन्हित पूर्णांक rsvd1;
	  अचिन्हित पूर्णांक pci_rev;
	  अचिन्हित पूर्णांक cap_ctrl;
	  अचिन्हित पूर्णांक hae_mem;
	  अचिन्हित पूर्णांक hae_io;
	  अचिन्हित पूर्णांक पूर्णांक_ctl;
	  अचिन्हित पूर्णांक पूर्णांक_reg;
	  अचिन्हित पूर्णांक पूर्णांक_mask0;
	  अचिन्हित पूर्णांक पूर्णांक_mask1;
	  अचिन्हित पूर्णांक mc_err0;
	  अचिन्हित पूर्णांक mc_err1;
	  अचिन्हित पूर्णांक cap_err;
	  अचिन्हित पूर्णांक rsvd2;
	  अचिन्हित पूर्णांक pci_err1;
	  अचिन्हित पूर्णांक mdpa_stat;
	  अचिन्हित पूर्णांक mdpa_syn;
	  अचिन्हित पूर्णांक mdpb_stat;
	  अचिन्हित पूर्णांक mdpb_syn;
	  अचिन्हित पूर्णांक rsvd3;
	  अचिन्हित पूर्णांक rsvd4;
	  अचिन्हित पूर्णांक rsvd5;
	पूर्ण *iodpp;

	frame = (काष्ठा el_common *)la_ptr;
	iodpp = (काष्ठा IOD_subpacket *) (la_ptr + frame->sys_offset);

	क्रम (hose = hose_head; hose; hose = hose->next, iodpp++) अणु

	  prपूर्णांकk("IOD %d Register Subpacket - Bridge Base Address %16lx\n",
		 hose->index, iodpp->base);
	  prपूर्णांकk("  WHOAMI      = %8x\n", iodpp->whoami);
	  prपूर्णांकk("  PCI_REV     = %8x\n", iodpp->pci_rev);
	  prपूर्णांकk("  CAP_CTRL    = %8x\n", iodpp->cap_ctrl);
	  prपूर्णांकk("  HAE_MEM     = %8x\n", iodpp->hae_mem);
	  prपूर्णांकk("  HAE_IO      = %8x\n", iodpp->hae_io);
	  prपूर्णांकk("  INT_CTL     = %8x\n", iodpp->पूर्णांक_ctl);
	  prपूर्णांकk("  INT_REG     = %8x\n", iodpp->पूर्णांक_reg);
	  prपूर्णांकk("  INT_MASK0   = %8x\n", iodpp->पूर्णांक_mask0);
	  prपूर्णांकk("  INT_MASK1   = %8x\n", iodpp->पूर्णांक_mask1);
	  prपूर्णांकk("  MC_ERR0     = %8x\n", iodpp->mc_err0);
	  prपूर्णांकk("  MC_ERR1     = %8x\n", iodpp->mc_err1);
	  prपूर्णांकk("  CAP_ERR     = %8x\n", iodpp->cap_err);
	  prपूर्णांकk("  PCI_ERR1    = %8x\n", iodpp->pci_err1);
	  prपूर्णांकk("  MDPA_STAT   = %8x\n", iodpp->mdpa_stat);
	  prपूर्णांकk("  MDPA_SYN    = %8x\n", iodpp->mdpa_syn);
	  prपूर्णांकk("  MDPB_STAT   = %8x\n", iodpp->mdpb_stat);
	  prपूर्णांकk("  MDPB_SYN    = %8x\n", iodpp->mdpb_syn);
	पूर्ण
पूर्ण

व्योम
mcpcia_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	काष्ठा el_MCPCIA_uncorrected_frame_mcheck *mchk_logout;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक expected;

	mchk_logout = (काष्ठा el_MCPCIA_uncorrected_frame_mcheck *)la_ptr;
	expected = mcheck_expected(cpu);

	mb();
	mb();  /* magic */
	draina();

	चयन (expected) अणु
	हाल 0:
	    अणु
		/* FIXME: how करो we figure out which hose the
		   error was on?  */	
		काष्ठा pci_controller *hose;
		क्रम (hose = hose_head; hose; hose = hose->next)
			mcpcia_pci_clr_err(MCPCIA_HOSE2MID(hose->index));
		अवरोध;
	    पूर्ण
	हाल 1:
		mcpcia_pci_clr_err(mcheck_extra(cpu));
		अवरोध;
	शेष:
		/* Otherwise, we're being called from mcpcia_probe_hose
		   and there's no hose clear an error from.  */
		अवरोध;
	पूर्ण

	wrmces(0x7);
	mb();

	process_mcheck_info(vector, la_ptr, "MCPCIA", expected != 0);
	अगर (!expected && vector != 0x620 && vector != 0x630) अणु
		mcpcia_prपूर्णांक_uncorrectable(mchk_logout);
		mcpcia_prपूर्णांक_प्रणाली_area(la_ptr);
	पूर्ण
पूर्ण
