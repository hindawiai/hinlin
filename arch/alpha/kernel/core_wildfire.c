<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/kernel/core_wildfire.c
 *
 *  Wildfire support.
 *
 *  Copyright (C) 2000 Andrea Arcangeli <andrea@suse.de> SuSE
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_wildfire.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"

#घोषणा DEBUG_CONFIG 0
#घोषणा DEBUG_DUMP_REGS 0
#घोषणा DEBUG_DUMP_CONFIG 1

#अगर DEBUG_CONFIG
# define DBG_CFG(args)	prपूर्णांकk args
#अन्यथा
# define DBG_CFG(args)
#पूर्ण_अगर

#अगर DEBUG_DUMP_REGS
अटल व्योम wildfire_dump_pci_regs(पूर्णांक qbbno, पूर्णांक hoseno);
अटल व्योम wildfire_dump_pca_regs(पूर्णांक qbbno, पूर्णांक pcano);
अटल व्योम wildfire_dump_qsa_regs(पूर्णांक qbbno);
अटल व्योम wildfire_dump_qsd_regs(पूर्णांक qbbno);
अटल व्योम wildfire_dump_iop_regs(पूर्णांक qbbno);
अटल व्योम wildfire_dump_gp_regs(पूर्णांक qbbno);
#पूर्ण_अगर
#अगर DEBUG_DUMP_CONFIG
अटल व्योम wildfire_dump_hardware_config(व्योम);
#पूर्ण_अगर

अचिन्हित अक्षर wildfire_hard_qbb_map[WILDFIRE_MAX_QBB];
अचिन्हित अक्षर wildfire_soft_qbb_map[WILDFIRE_MAX_QBB];
#घोषणा QBB_MAP_EMPTY	0xff

अचिन्हित दीर्घ wildfire_hard_qbb_mask;
अचिन्हित दीर्घ wildfire_soft_qbb_mask;
अचिन्हित दीर्घ wildfire_gp_mask;
अचिन्हित दीर्घ wildfire_hs_mask;
अचिन्हित दीर्घ wildfire_iop_mask;
अचिन्हित दीर्घ wildfire_ior_mask;
अचिन्हित दीर्घ wildfire_pca_mask;
अचिन्हित दीर्घ wildfire_cpu_mask;
अचिन्हित दीर्घ wildfire_mem_mask;

व्योम __init
wildfire_init_hose(पूर्णांक qbbno, पूर्णांक hoseno)
अणु
	काष्ठा pci_controller *hose;
	wildfire_pci *pci;

	hose = alloc_pci_controller();
	hose->io_space = alloc_resource();
	hose->mem_space = alloc_resource();

        /* This is क्रम userland consumption. */
        hose->sparse_mem_base = 0;
        hose->sparse_io_base  = 0;
        hose->dense_mem_base  = WILDFIRE_MEM(qbbno, hoseno);
        hose->dense_io_base   = WILDFIRE_IO(qbbno, hoseno);

	hose->config_space_base = WILDFIRE_CONF(qbbno, hoseno);
	hose->index = (qbbno << 3) + hoseno;

	hose->io_space->start = WILDFIRE_IO(qbbno, hoseno) - WILDFIRE_IO_BIAS;
	hose->io_space->end = hose->io_space->start + WILDFIRE_IO_SPACE - 1;
	hose->io_space->name = pci_io_names[hoseno];
	hose->io_space->flags = IORESOURCE_IO;

	hose->mem_space->start = WILDFIRE_MEM(qbbno, hoseno)-WILDFIRE_MEM_BIAS;
	hose->mem_space->end = hose->mem_space->start + 0xffffffff;
	hose->mem_space->name = pci_mem_names[hoseno];
	hose->mem_space->flags = IORESOURCE_MEM;

	अगर (request_resource(&ioport_resource, hose->io_space) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request IO on qbb %d hose %d\n",
		       qbbno, hoseno);
	अगर (request_resource(&iomem_resource, hose->mem_space) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request MEM on qbb %d hose %d\n",
		       qbbno, hoseno);

#अगर DEBUG_DUMP_REGS
	wildfire_dump_pci_regs(qbbno, hoseno);
#पूर्ण_अगर

        /*
         * Set up the PCI to मुख्य memory translation winकरोws.
         *
         * Note: Winकरोw 3 is scatter-gather only
         * 
         * Winकरोw 0 is scatter-gather 8MB at 8MB (क्रम isa)
	 * Winकरोw 1 is direct access 1GB at 1GB
	 * Winकरोw 2 is direct access 1GB at 2GB
         * Winकरोw 3 is scatter-gather 128MB at 3GB
         * ??? We ought to scale winकरोw 3 memory.
         *
         */
	hose->sg_isa = iommu_arena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	hose->sg_pci = iommu_arena_new(hose, 0xc0000000, 0x08000000,
				       SMP_CACHE_BYTES);

	pci = WILDFIRE_pci(qbbno, hoseno);

	pci->pci_winकरोw[0].wbase.csr = hose->sg_isa->dma_base | 3;
	pci->pci_winकरोw[0].wmask.csr = (hose->sg_isa->size - 1) & 0xfff00000;
	pci->pci_winकरोw[0].tbase.csr = virt_to_phys(hose->sg_isa->ptes);

	pci->pci_winकरोw[1].wbase.csr = 0x40000000 | 1;
	pci->pci_winकरोw[1].wmask.csr = (0x40000000 -1) & 0xfff00000;
	pci->pci_winकरोw[1].tbase.csr = 0;

	pci->pci_winकरोw[2].wbase.csr = 0x80000000 | 1;
	pci->pci_winकरोw[2].wmask.csr = (0x40000000 -1) & 0xfff00000;
	pci->pci_winकरोw[2].tbase.csr = 0x40000000;

	pci->pci_winकरोw[3].wbase.csr = hose->sg_pci->dma_base | 3;
	pci->pci_winकरोw[3].wmask.csr = (hose->sg_pci->size - 1) & 0xfff00000;
	pci->pci_winकरोw[3].tbase.csr = virt_to_phys(hose->sg_pci->ptes);

	wildfire_pci_tbi(hose, 0, 0); /* Flush TLB at the end. */
पूर्ण

व्योम __init
wildfire_init_pca(पूर्णांक qbbno, पूर्णांक pcano)
अणु

	/* Test क्रम PCA existence first. */
	अगर (!WILDFIRE_PCA_EXISTS(qbbno, pcano))
	    वापस;

#अगर DEBUG_DUMP_REGS
	wildfire_dump_pca_regs(qbbno, pcano);
#पूर्ण_अगर

	/* Do both hoses of the PCA. */
	wildfire_init_hose(qbbno, (pcano << 1) + 0);
	wildfire_init_hose(qbbno, (pcano << 1) + 1);
पूर्ण

व्योम __init
wildfire_init_qbb(पूर्णांक qbbno)
अणु
	पूर्णांक pcano;

	/* Test क्रम QBB existence first. */
	अगर (!WILDFIRE_QBB_EXISTS(qbbno))
		वापस;

#अगर DEBUG_DUMP_REGS
	wildfire_dump_qsa_regs(qbbno);
	wildfire_dump_qsd_regs(qbbno);
	wildfire_dump_iop_regs(qbbno);
	wildfire_dump_gp_regs(qbbno);
#पूर्ण_अगर

	/* Init all PCAs here. */
	क्रम (pcano = 0; pcano < WILDFIRE_PCA_PER_QBB; pcano++) अणु
		wildfire_init_pca(qbbno, pcano);
	पूर्ण
पूर्ण

व्योम __init
wildfire_hardware_probe(व्योम)
अणु
	अचिन्हित दीर्घ temp;
	अचिन्हित पूर्णांक hard_qbb, soft_qbb;
	wildfire_fast_qsd *fast = WILDFIRE_fast_qsd();
	wildfire_qsd *qsd;
	wildfire_qsa *qsa;
	wildfire_iop *iop;
	wildfire_gp *gp;
	wildfire_ne *ne;
	wildfire_fe *fe;
	पूर्णांक i;

	temp = fast->qsd_whami.csr;
#अगर 0
	prपूर्णांकk(KERN_ERR "fast QSD_WHAMI at base %p is 0x%lx\n", fast, temp);
#पूर्ण_अगर

	hard_qbb = (temp >> 8) & 7;
	soft_qbb = (temp >> 4) & 7;

	/* Init the HW configuration variables. */
	wildfire_hard_qbb_mask = (1 << hard_qbb);
	wildfire_soft_qbb_mask = (1 << soft_qbb);

	wildfire_gp_mask = 0;
	wildfire_hs_mask = 0;
	wildfire_iop_mask = 0;
	wildfire_ior_mask = 0;
	wildfire_pca_mask = 0;

	wildfire_cpu_mask = 0;
	wildfire_mem_mask = 0;

	स_रखो(wildfire_hard_qbb_map, QBB_MAP_EMPTY, WILDFIRE_MAX_QBB);
	स_रखो(wildfire_soft_qbb_map, QBB_MAP_EMPTY, WILDFIRE_MAX_QBB);

	/* First, determine which QBBs are present. */
	qsa = WILDFIRE_qsa(soft_qbb);

	temp = qsa->qsa_qbb_id.csr;
#अगर 0
	prपूर्णांकk(KERN_ERR "QSA_QBB_ID at base %p is 0x%lx\n", qsa, temp);
#पूर्ण_अगर

	अगर (temp & 0x40) /* Is there an HS? */
		wildfire_hs_mask = 1;

	अगर (temp & 0x20) अणु /* Is there a GP? */
		gp = WILDFIRE_gp(soft_qbb);
		temp = 0;
		क्रम (i = 0; i < 4; i++) अणु
			temp |= gp->gpa_qbb_map[i].csr << (i * 8);
#अगर 0
			prपूर्णांकk(KERN_ERR "GPA_QBB_MAP[%d] at base %p is 0x%lx\n",
			       i, gp, temp);
#पूर्ण_अगर
		पूर्ण

		क्रम (hard_qbb = 0; hard_qbb < WILDFIRE_MAX_QBB; hard_qbb++) अणु
			अगर (temp & 8) अणु /* Is there a QBB? */
				soft_qbb = temp & 7;
				wildfire_hard_qbb_mask |= (1 << hard_qbb);
				wildfire_soft_qbb_mask |= (1 << soft_qbb);
			पूर्ण
			temp >>= 4;
		पूर्ण
		wildfire_gp_mask = wildfire_soft_qbb_mask;
        पूर्ण

	/* Next determine each QBBs resources. */
	क्रम (soft_qbb = 0; soft_qbb < WILDFIRE_MAX_QBB; soft_qbb++) अणु
	    अगर (WILDFIRE_QBB_EXISTS(soft_qbb)) अणु
	        qsd = WILDFIRE_qsd(soft_qbb);
		temp = qsd->qsd_whami.csr;
#अगर 0
	prपूर्णांकk(KERN_ERR "QSD_WHAMI at base %p is 0x%lx\n", qsd, temp);
#पूर्ण_अगर
		hard_qbb = (temp >> 8) & 7;
		wildfire_hard_qbb_map[hard_qbb] = soft_qbb;
		wildfire_soft_qbb_map[soft_qbb] = hard_qbb;

		qsa = WILDFIRE_qsa(soft_qbb);
		temp = qsa->qsa_qbb_pop[0].csr;
#अगर 0
	prपूर्णांकk(KERN_ERR "QSA_QBB_POP_0 at base %p is 0x%lx\n", qsa, temp);
#पूर्ण_अगर
		wildfire_cpu_mask |= ((temp >> 0) & 0xf) << (soft_qbb << 2);
		wildfire_mem_mask |= ((temp >> 4) & 0xf) << (soft_qbb << 2);

		temp = qsa->qsa_qbb_pop[1].csr;
#अगर 0
	prपूर्णांकk(KERN_ERR "QSA_QBB_POP_1 at base %p is 0x%lx\n", qsa, temp);
#पूर्ण_अगर
		wildfire_iop_mask |= (1 << soft_qbb);
		wildfire_ior_mask |= ((temp >> 4) & 0xf) << (soft_qbb << 2);

		temp = qsa->qsa_qbb_id.csr;
#अगर 0
	prपूर्णांकk(KERN_ERR "QSA_QBB_ID at %p is 0x%lx\n", qsa, temp);
#पूर्ण_अगर
		अगर (temp & 0x20)
		    wildfire_gp_mask |= (1 << soft_qbb);

		/* Probe क्रम PCA existence here. */
		क्रम (i = 0; i < WILDFIRE_PCA_PER_QBB; i++) अणु
		    iop = WILDFIRE_iop(soft_qbb);
		    ne = WILDFIRE_ne(soft_qbb, i);
		    fe = WILDFIRE_fe(soft_qbb, i);

		    अगर ((iop->iop_hose[i].init.csr & 1) == 1 &&
			((ne->ne_what_am_i.csr & 0xf00000300UL) == 0x100000300UL) &&
			((fe->fe_what_am_i.csr & 0xf00000300UL) == 0x100000200UL))
		    अणु
		        wildfire_pca_mask |= 1 << ((soft_qbb << 2) + i);
		    पूर्ण
		पूर्ण

	    पूर्ण
	पूर्ण
#अगर DEBUG_DUMP_CONFIG
	wildfire_dump_hardware_config();
#पूर्ण_अगर
पूर्ण

व्योम __init
wildfire_init_arch(व्योम)
अणु
	पूर्णांक qbbno;

	/* With multiple PCI buses, we play with I/O as physical addrs.  */
	ioport_resource.end = ~0UL;


	/* Probe the hardware क्रम info about configuration. */
	wildfire_hardware_probe();

	/* Now init all the found QBBs. */
	क्रम (qbbno = 0; qbbno < WILDFIRE_MAX_QBB; qbbno++) अणु
		wildfire_init_qbb(qbbno);
	पूर्ण

	/* Normal direct PCI DMA mapping. */ 
	__direct_map_base = 0x40000000UL;
	__direct_map_size = 0x80000000UL;
पूर्ण

व्योम
wildfire_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	mb();
	mb();  /* magic */
	draina();
	/* FIXME: clear pci errors */
	wrmces(0x7);
	mb();

	process_mcheck_info(vector, la_ptr, "WILDFIRE",
			    mcheck_expected(smp_processor_id()));
पूर्ण

व्योम
wildfire_समाप्त_arch(पूर्णांक mode)
अणु
पूर्ण

व्योम
wildfire_pci_tbi(काष्ठा pci_controller *hose, dma_addr_t start, dma_addr_t end)
अणु
	पूर्णांक qbbno = hose->index >> 3;
	पूर्णांक hoseno = hose->index & 7;
	wildfire_pci *pci = WILDFIRE_pci(qbbno, hoseno);

	mb();
	pci->pci_flush_tlb.csr; /* पढ़ोing करोes the trick */
पूर्ण

अटल पूर्णांक
mk_conf_addr(काष्ठा pci_bus *pbus, अचिन्हित पूर्णांक device_fn, पूर्णांक where,
	     अचिन्हित दीर्घ *pci_addr, अचिन्हित अक्षर *type1)
अणु
	काष्ठा pci_controller *hose = pbus->sysdata;
	अचिन्हित दीर्घ addr;
	u8 bus = pbus->number;

	DBG_CFG(("mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x, "
		 "pci_addr=0x%p, type1=0x%p)\n",
		 bus, device_fn, where, pci_addr, type1));

	अगर (!pbus->parent) /* No parent means peer PCI bus. */
		bus = 0;
	*type1 = (bus != 0);

	addr = (bus << 16) | (device_fn << 8) | where;
	addr |= hose->config_space_base;
		
	*pci_addr = addr;
	DBG_CFG(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	वापस 0;
पूर्ण

अटल पूर्णांक 
wildfire_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
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
wildfire_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
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

काष्ठा pci_ops wildfire_pci_ops = 
अणु
	.पढ़ो =		wildfire_पढ़ो_config,
	.ग_लिखो =	wildfire_ग_लिखो_config,
पूर्ण;


/*
 * NUMA Support
 */
पूर्णांक wildfire_pa_to_nid(अचिन्हित दीर्घ pa)
अणु
	वापस pa >> 36;
पूर्ण

पूर्णांक wildfire_cpuid_to_nid(पूर्णांक cpuid)
अणु
	/* assume 4 CPUs per node */
	वापस cpuid >> 2;
पूर्ण

अचिन्हित दीर्घ wildfire_node_mem_start(पूर्णांक nid)
अणु
	/* 64GB per node */
	वापस (अचिन्हित दीर्घ)nid * (64UL * 1024 * 1024 * 1024);
पूर्ण

अचिन्हित दीर्घ wildfire_node_mem_size(पूर्णांक nid)
अणु
	/* 64GB per node */
	वापस 64UL * 1024 * 1024 * 1024;
पूर्ण

#अगर DEBUG_DUMP_REGS

अटल व्योम __init
wildfire_dump_pci_regs(पूर्णांक qbbno, पूर्णांक hoseno)
अणु
	wildfire_pci *pci = WILDFIRE_pci(qbbno, hoseno);
	पूर्णांक i;

	prपूर्णांकk(KERN_ERR "PCI registers for QBB %d hose %d (%p)\n",
	       qbbno, hoseno, pci);

	prपूर्णांकk(KERN_ERR " PCI_IO_ADDR_EXT: 0x%16lx\n",
	       pci->pci_io_addr_ext.csr);
	prपूर्णांकk(KERN_ERR " PCI_CTRL:        0x%16lx\n", pci->pci_ctrl.csr);
	prपूर्णांकk(KERN_ERR " PCI_ERR_SUM:     0x%16lx\n", pci->pci_err_sum.csr);
	prपूर्णांकk(KERN_ERR " PCI_ERR_ADDR:    0x%16lx\n", pci->pci_err_addr.csr);
	prपूर्णांकk(KERN_ERR " PCI_STALL_CNT:   0x%16lx\n", pci->pci_stall_cnt.csr);
	prपूर्णांकk(KERN_ERR " PCI_PEND_INT:    0x%16lx\n", pci->pci_pend_पूर्णांक.csr);
	prपूर्णांकk(KERN_ERR " PCI_SENT_INT:    0x%16lx\n", pci->pci_sent_पूर्णांक.csr);

	prपूर्णांकk(KERN_ERR " DMA window registers for QBB %d hose %d (%p)\n",
	       qbbno, hoseno, pci);
	क्रम (i = 0; i < 4; i++) अणु
		prपूर्णांकk(KERN_ERR "  window %d: 0x%16lx 0x%16lx 0x%16lx\n", i,
		       pci->pci_winकरोw[i].wbase.csr,
		       pci->pci_winकरोw[i].wmask.csr,
		       pci->pci_winकरोw[i].tbase.csr);
	पूर्ण
	prपूर्णांकk(KERN_ERR "\n");
पूर्ण

अटल व्योम __init
wildfire_dump_pca_regs(पूर्णांक qbbno, पूर्णांक pcano)
अणु
	wildfire_pca *pca = WILDFIRE_pca(qbbno, pcano);
	पूर्णांक i;

	prपूर्णांकk(KERN_ERR "PCA registers for QBB %d PCA %d (%p)\n",
	       qbbno, pcano, pca);

	prपूर्णांकk(KERN_ERR " PCA_WHAT_AM_I: 0x%16lx\n", pca->pca_what_am_i.csr);
	prपूर्णांकk(KERN_ERR " PCA_ERR_SUM:   0x%16lx\n", pca->pca_err_sum.csr);
	prपूर्णांकk(KERN_ERR " PCA_PEND_INT:  0x%16lx\n", pca->pca_pend_पूर्णांक.csr);
	prपूर्णांकk(KERN_ERR " PCA_SENT_INT:  0x%16lx\n", pca->pca_sent_पूर्णांक.csr);
	prपूर्णांकk(KERN_ERR " PCA_STDIO_EL:  0x%16lx\n",
	       pca->pca_stdio_edge_level.csr);

	prपूर्णांकk(KERN_ERR " PCA target registers for QBB %d PCA %d (%p)\n",
	       qbbno, pcano, pca);
	क्रम (i = 0; i < 4; i++) अणु
	  prपूर्णांकk(KERN_ERR "  target %d: 0x%16lx 0x%16lx\n", i,
		       pca->pca_पूर्णांक[i].target.csr,
		       pca->pca_पूर्णांक[i].enable.csr);
	पूर्ण

	prपूर्णांकk(KERN_ERR "\n");
पूर्ण

अटल व्योम __init
wildfire_dump_qsa_regs(पूर्णांक qbbno)
अणु
	wildfire_qsa *qsa = WILDFIRE_qsa(qbbno);
	पूर्णांक i;

	prपूर्णांकk(KERN_ERR "QSA registers for QBB %d (%p)\n", qbbno, qsa);

	prपूर्णांकk(KERN_ERR " QSA_QBB_ID:      0x%16lx\n", qsa->qsa_qbb_id.csr);
	prपूर्णांकk(KERN_ERR " QSA_PORT_ENA:    0x%16lx\n", qsa->qsa_port_ena.csr);
	prपूर्णांकk(KERN_ERR " QSA_REF_INT:     0x%16lx\n", qsa->qsa_ref_पूर्णांक.csr);

	क्रम (i = 0; i < 5; i++)
		prपूर्णांकk(KERN_ERR " QSA_CONFIG_%d:    0x%16lx\n",
		       i, qsa->qsa_config[i].csr);

	क्रम (i = 0; i < 2; i++)
		prपूर्णांकk(KERN_ERR " QSA_QBB_POP_%d:   0x%16lx\n",
		       i, qsa->qsa_qbb_pop[0].csr);

	prपूर्णांकk(KERN_ERR "\n");
पूर्ण

अटल व्योम __init
wildfire_dump_qsd_regs(पूर्णांक qbbno)
अणु
	wildfire_qsd *qsd = WILDFIRE_qsd(qbbno);

	prपूर्णांकk(KERN_ERR "QSD registers for QBB %d (%p)\n", qbbno, qsd);

	prपूर्णांकk(KERN_ERR " QSD_WHAMI:         0x%16lx\n", qsd->qsd_whami.csr);
	prपूर्णांकk(KERN_ERR " QSD_REV:           0x%16lx\n", qsd->qsd_rev.csr);
	prपूर्णांकk(KERN_ERR " QSD_PORT_PRESENT:  0x%16lx\n",
	       qsd->qsd_port_present.csr);
	prपूर्णांकk(KERN_ERR " QSD_PORT_ACTIVE:   0x%16lx\n",
	       qsd->qsd_port_active.csr);
	prपूर्णांकk(KERN_ERR " QSD_FAULT_ENA:     0x%16lx\n",
	       qsd->qsd_fault_ena.csr);
	prपूर्णांकk(KERN_ERR " QSD_CPU_INT_ENA:   0x%16lx\n",
	       qsd->qsd_cpu_पूर्णांक_ena.csr);
	prपूर्णांकk(KERN_ERR " QSD_MEM_CONFIG:    0x%16lx\n",
	       qsd->qsd_mem_config.csr);
	prपूर्णांकk(KERN_ERR " QSD_ERR_SUM:       0x%16lx\n",
	       qsd->qsd_err_sum.csr);

	prपूर्णांकk(KERN_ERR "\n");
पूर्ण

अटल व्योम __init
wildfire_dump_iop_regs(पूर्णांक qbbno)
अणु
	wildfire_iop *iop = WILDFIRE_iop(qbbno);
	पूर्णांक i;

	prपूर्णांकk(KERN_ERR "IOP registers for QBB %d (%p)\n", qbbno, iop);

	prपूर्णांकk(KERN_ERR " IOA_CONFIG:          0x%16lx\n", iop->ioa_config.csr);
	prपूर्णांकk(KERN_ERR " IOD_CONFIG:          0x%16lx\n", iop->iod_config.csr);
	prपूर्णांकk(KERN_ERR " IOP_SWITCH_CREDITS:  0x%16lx\n",
	       iop->iop_चयन_credits.csr);
	prपूर्णांकk(KERN_ERR " IOP_HOSE_CREDITS:    0x%16lx\n",
	       iop->iop_hose_credits.csr);

	क्रम (i = 0; i < 4; i++) 
		prपूर्णांकk(KERN_ERR " IOP_HOSE_%d_INIT:     0x%16lx\n",
		       i, iop->iop_hose[i].init.csr);
	क्रम (i = 0; i < 4; i++) 
		prपूर्णांकk(KERN_ERR " IOP_DEV_INT_TARGET_%d: 0x%16lx\n",
		       i, iop->iop_dev_पूर्णांक[i].target.csr);

	prपूर्णांकk(KERN_ERR "\n");
पूर्ण

अटल व्योम __init
wildfire_dump_gp_regs(पूर्णांक qbbno)
अणु
	wildfire_gp *gp = WILDFIRE_gp(qbbno);
	पूर्णांक i;

	prपूर्णांकk(KERN_ERR "GP registers for QBB %d (%p)\n", qbbno, gp);
	क्रम (i = 0; i < 4; i++) 
		prपूर्णांकk(KERN_ERR " GPA_QBB_MAP_%d:     0x%16lx\n",
		       i, gp->gpa_qbb_map[i].csr);

	prपूर्णांकk(KERN_ERR " GPA_MEM_POP_MAP:   0x%16lx\n",
	       gp->gpa_mem_pop_map.csr);
	prपूर्णांकk(KERN_ERR " GPA_SCRATCH:       0x%16lx\n", gp->gpa_scratch.csr);
	prपूर्णांकk(KERN_ERR " GPA_DIAG:          0x%16lx\n", gp->gpa_diag.csr);
	prपूर्णांकk(KERN_ERR " GPA_CONFIG_0:      0x%16lx\n", gp->gpa_config_0.csr);
	prपूर्णांकk(KERN_ERR " GPA_INIT_ID:       0x%16lx\n", gp->gpa_init_id.csr);
	prपूर्णांकk(KERN_ERR " GPA_CONFIG_2:      0x%16lx\n", gp->gpa_config_2.csr);

	prपूर्णांकk(KERN_ERR "\n");
पूर्ण
#पूर्ण_अगर /* DUMP_REGS */

#अगर DEBUG_DUMP_CONFIG
अटल व्योम __init
wildfire_dump_hardware_config(व्योम)
अणु
	पूर्णांक i;

	prपूर्णांकk(KERN_ERR "Probed Hardware Configuration\n");

	prपूर्णांकk(KERN_ERR " hard_qbb_mask:  0x%16lx\n", wildfire_hard_qbb_mask);
	prपूर्णांकk(KERN_ERR " soft_qbb_mask:  0x%16lx\n", wildfire_soft_qbb_mask);

	prपूर्णांकk(KERN_ERR " gp_mask:        0x%16lx\n", wildfire_gp_mask);
	prपूर्णांकk(KERN_ERR " hs_mask:        0x%16lx\n", wildfire_hs_mask);
	prपूर्णांकk(KERN_ERR " iop_mask:       0x%16lx\n", wildfire_iop_mask);
	prपूर्णांकk(KERN_ERR " ior_mask:       0x%16lx\n", wildfire_ior_mask);
	prपूर्णांकk(KERN_ERR " pca_mask:       0x%16lx\n", wildfire_pca_mask);

	prपूर्णांकk(KERN_ERR " cpu_mask:       0x%16lx\n", wildfire_cpu_mask);
	prपूर्णांकk(KERN_ERR " mem_mask:       0x%16lx\n", wildfire_mem_mask);

	prपूर्णांकk(" hard_qbb_map: ");
	क्रम (i = 0; i < WILDFIRE_MAX_QBB; i++)
	    अगर (wildfire_hard_qbb_map[i] == QBB_MAP_EMPTY)
		prपूर्णांकk("--- ");
	    अन्यथा
		prपूर्णांकk("%3d ", wildfire_hard_qbb_map[i]);
	prपूर्णांकk("\n");

	prपूर्णांकk(" soft_qbb_map: ");
	क्रम (i = 0; i < WILDFIRE_MAX_QBB; i++)
	    अगर (wildfire_soft_qbb_map[i] == QBB_MAP_EMPTY)
		prपूर्णांकk("--- ");
	    अन्यथा
		prपूर्णांकk("%3d ", wildfire_soft_qbb_map[i]);
	prपूर्णांकk("\n");
पूर्ण
#पूर्ण_अगर /* DUMP_CONFIG */
