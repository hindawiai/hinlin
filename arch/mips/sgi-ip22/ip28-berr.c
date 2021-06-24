<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip28-berr.c: Bus error handling.
 *
 * Copyright (C) 2002, 2003 Ladislav Michl (ladis@linux-mips.org)
 * Copyright (C) 2005 Peter Fuerst (pf@net.alphadv.de) - IP28
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/sgi/mc.h>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ioc.h>
#समावेश <यंत्र/sgi/ip22.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/bootinfo.h>

अटल अचिन्हित पूर्णांक count_be_is_fixup;
अटल अचिन्हित पूर्णांक count_be_handler;
अटल अचिन्हित पूर्णांक count_be_पूर्णांकerrupt;
अटल पूर्णांक debug_be_पूर्णांकerrupt;

अटल अचिन्हित पूर्णांक cpu_err_stat;	/* Status reg क्रम CPU */
अटल अचिन्हित पूर्णांक gio_err_stat;	/* Status reg क्रम GIO */
अटल अचिन्हित पूर्णांक cpu_err_addr;	/* Error address reg क्रम CPU */
अटल अचिन्हित पूर्णांक gio_err_addr;	/* Error address reg क्रम GIO */
अटल अचिन्हित पूर्णांक extio_stat;
अटल अचिन्हित पूर्णांक hpc3_berr_stat;	/* Bus error पूर्णांकerrupt status */

काष्ठा hpc3_stat अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक cbp;
	अचिन्हित पूर्णांक ndptr;
पूर्ण;

अटल काष्ठा अणु
	काष्ठा hpc3_stat pbdma[8];
	काष्ठा hpc3_stat scsi[2];
	काष्ठा hpc3_stat ethrx, ethtx;
पूर्ण hpc3;

अटल काष्ठा अणु
	अचिन्हित दीर्घ err_addr;
	काष्ठा अणु
		u32 lo;
		u32 hi;
	पूर्ण tags[1][2], tagd[4][2], tagi[4][2]; /* Way 0/1 */
पूर्ण cache_tags;

अटल अंतरभूत व्योम save_cache_tags(अचिन्हित busaddr)
अणु
	अचिन्हित दीर्घ addr = CAC_BASE | busaddr;
	पूर्णांक i;
	cache_tags.err_addr = addr;

	/*
	 * Starting with a bus-address, save secondary cache (indexed by
	 * PA[23..18:7..6]) tags first.
	 */
	addr &= ~1L;
#घोषणा tag cache_tags.tags[0]
	cache_op(Index_Load_Tag_S, addr);
	tag[0].lo = पढ़ो_c0_taglo();	/* PA[35:18], VA[13:12] */
	tag[0].hi = पढ़ो_c0_taghi();	/* PA[39:36] */
	cache_op(Index_Load_Tag_S, addr | 1L);
	tag[1].lo = पढ़ो_c0_taglo();	/* PA[35:18], VA[13:12] */
	tag[1].hi = पढ़ो_c0_taghi();	/* PA[39:36] */
#अघोषित tag

	/*
	 * Save all primary data cache (indexed by VA[13:5]) tags which
	 * might fit to this bus-address, knowing that VA[11:0] == PA[11:0].
	 * Saving all tags and evaluating them later is easier and safer
	 * than relying on VA[13:12] from the secondary cache tags to pick
	 * matching primary tags here alपढ़ोy.
	 */
	addr &= (0xffL << 56) | ((1 << 12) - 1);
#घोषणा tag cache_tags.tagd[i]
	क्रम (i = 0; i < 4; ++i, addr += (1 << 12)) अणु
		cache_op(Index_Load_Tag_D, addr);
		tag[0].lo = पढ़ो_c0_taglo();	/* PA[35:12] */
		tag[0].hi = पढ़ो_c0_taghi();	/* PA[39:36] */
		cache_op(Index_Load_Tag_D, addr | 1L);
		tag[1].lo = पढ़ो_c0_taglo();	/* PA[35:12] */
		tag[1].hi = पढ़ो_c0_taghi();	/* PA[39:36] */
	पूर्ण
#अघोषित tag

	/*
	 * Save primary inकाष्ठाion cache (indexed by VA[13:6]) tags
	 * the same way.
	 */
	addr &= (0xffL << 56) | ((1 << 12) - 1);
#घोषणा tag cache_tags.tagi[i]
	क्रम (i = 0; i < 4; ++i, addr += (1 << 12)) अणु
		cache_op(Index_Load_Tag_I, addr);
		tag[0].lo = पढ़ो_c0_taglo();	/* PA[35:12] */
		tag[0].hi = पढ़ो_c0_taghi();	/* PA[39:36] */
		cache_op(Index_Load_Tag_I, addr | 1L);
		tag[1].lo = पढ़ो_c0_taglo();	/* PA[35:12] */
		tag[1].hi = पढ़ो_c0_taghi();	/* PA[39:36] */
	पूर्ण
#अघोषित tag
पूर्ण

#घोषणा GIO_ERRMASK	0xff00
#घोषणा CPU_ERRMASK	0x3f00

अटल व्योम save_and_clear_buserr(व्योम)
अणु
	पूर्णांक i;

	/* save status रेजिस्टरs */
	cpu_err_addr = sgimc->cerr;
	cpu_err_stat = sgimc->cstat;
	gio_err_addr = sgimc->gerr;
	gio_err_stat = sgimc->gstat;
	extio_stat = sgioc->extio;
	hpc3_berr_stat = hpc3c0->bestat;

	hpc3.scsi[0].addr  = (अचिन्हित दीर्घ)&hpc3c0->scsi_chan0;
	hpc3.scsi[0].ctrl  = hpc3c0->scsi_chan0.ctrl; /* HPC3_SCTRL_ACTIVE ? */
	hpc3.scsi[0].cbp   = hpc3c0->scsi_chan0.cbptr;
	hpc3.scsi[0].ndptr = hpc3c0->scsi_chan0.ndptr;

	hpc3.scsi[1].addr  = (अचिन्हित दीर्घ)&hpc3c0->scsi_chan1;
	hpc3.scsi[1].ctrl  = hpc3c0->scsi_chan1.ctrl; /* HPC3_SCTRL_ACTIVE ? */
	hpc3.scsi[1].cbp   = hpc3c0->scsi_chan1.cbptr;
	hpc3.scsi[1].ndptr = hpc3c0->scsi_chan1.ndptr;

	hpc3.ethrx.addr	 = (अचिन्हित दीर्घ)&hpc3c0->ethregs.rx_cbptr;
	hpc3.ethrx.ctrl	 = hpc3c0->ethregs.rx_ctrl; /* HPC3_ERXCTRL_ACTIVE ? */
	hpc3.ethrx.cbp	 = hpc3c0->ethregs.rx_cbptr;
	hpc3.ethrx.ndptr = hpc3c0->ethregs.rx_ndptr;

	hpc3.ethtx.addr	 = (अचिन्हित दीर्घ)&hpc3c0->ethregs.tx_cbptr;
	hpc3.ethtx.ctrl	 = hpc3c0->ethregs.tx_ctrl; /* HPC3_ETXCTRL_ACTIVE ? */
	hpc3.ethtx.cbp	 = hpc3c0->ethregs.tx_cbptr;
	hpc3.ethtx.ndptr = hpc3c0->ethregs.tx_ndptr;

	क्रम (i = 0; i < 8; ++i) अणु
		/* HPC3_PDMACTRL_ISACT ? */
		hpc3.pbdma[i].addr  = (अचिन्हित दीर्घ)&hpc3c0->pbdma[i];
		hpc3.pbdma[i].ctrl  = hpc3c0->pbdma[i].pbdma_ctrl;
		hpc3.pbdma[i].cbp   = hpc3c0->pbdma[i].pbdma_bptr;
		hpc3.pbdma[i].ndptr = hpc3c0->pbdma[i].pbdma_dptr;
	पूर्ण
	i = 0;
	अगर (gio_err_stat & CPU_ERRMASK)
		i = gio_err_addr;
	अगर (cpu_err_stat & CPU_ERRMASK)
		i = cpu_err_addr;
	save_cache_tags(i);

	sgimc->cstat = sgimc->gstat = 0;
पूर्ण

अटल व्योम prपूर्णांक_cache_tags(व्योम)
अणु
	u32 scb, scw;
	पूर्णांक i;

	prपूर्णांकk(KERN_ERR "Cache tags @ %08x:\n", (अचिन्हित)cache_tags.err_addr);

	/* PA[31:12] shअगरted to PTag0 (PA[35:12]) क्रमmat */
	scw = (cache_tags.err_addr >> 4) & 0x0fffff00;

	scb = cache_tags.err_addr & ((1 << 12) - 1) & ~((1 << 5) - 1);
	क्रम (i = 0; i < 4; ++i) अणु /* क्रम each possible VA[13:12] value */
		अगर ((cache_tags.tagd[i][0].lo & 0x0fffff00) != scw &&
		    (cache_tags.tagd[i][1].lo & 0x0fffff00) != scw)
		    जारी;
		prपूर्णांकk(KERN_ERR
		       "D: 0: %08x %08x, 1: %08x %08x  (VA[13:5]  %04x)\n",
			cache_tags.tagd[i][0].hi, cache_tags.tagd[i][0].lo,
			cache_tags.tagd[i][1].hi, cache_tags.tagd[i][1].lo,
			scb | (1 << 12)*i);
	पूर्ण
	scb = cache_tags.err_addr & ((1 << 12) - 1) & ~((1 << 6) - 1);
	क्रम (i = 0; i < 4; ++i) अणु /* क्रम each possible VA[13:12] value */
		अगर ((cache_tags.tagi[i][0].lo & 0x0fffff00) != scw &&
		    (cache_tags.tagi[i][1].lo & 0x0fffff00) != scw)
		    जारी;
		prपूर्णांकk(KERN_ERR
		       "I: 0: %08x %08x, 1: %08x %08x  (VA[13:6]  %04x)\n",
			cache_tags.tagi[i][0].hi, cache_tags.tagi[i][0].lo,
			cache_tags.tagi[i][1].hi, cache_tags.tagi[i][1].lo,
			scb | (1 << 12)*i);
	पूर्ण
	i = पढ़ो_c0_config();
	scb = i & (1 << 13) ? 7:6;	/* scblksize = 2^[7..6] */
	scw = ((i >> 16) & 7) + 19 - 1; /* scwaysize = 2^[24..19] / 2 */

	i = ((1 << scw) - 1) & ~((1 << scb) - 1);
	prपूर्णांकk(KERN_ERR "S: 0: %08x %08x, 1: %08x %08x	(PA[%u:%u] %05x)\n",
		cache_tags.tags[0][0].hi, cache_tags.tags[0][0].lo,
		cache_tags.tags[0][1].hi, cache_tags.tags[0][1].lo,
		scw-1, scb, i & (अचिन्हित)cache_tags.err_addr);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cause_excode_text(पूर्णांक cause)
अणु
	अटल स्थिर अक्षर *txt[32] =
	अणु	"Interrupt",
		"TLB modification",
		"TLB (load or instruction fetch)",
		"TLB (store)",
		"Address error (load or instruction fetch)",
		"Address error (store)",
		"Bus error (instruction fetch)",
		"Bus error (data: load or store)",
		"Syscall",
		"Breakpoint",
		"Reserved instruction",
		"Coprocessor unusable",
		"Arithmetic Overflow",
		"Trap",
		"14",
		"Floating-Point",
		"16", "17", "18", "19", "20", "21", "22",
		"Watch Hi/Lo",
		"24", "25", "26", "27", "28", "29", "30", "31",
	पूर्ण;
	वापस txt[(cause & 0x7c) >> 2];
पूर्ण

अटल व्योम prपूर्णांक_buserr(स्थिर काष्ठा pt_regs *regs)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);
	पूर्णांक error = 0;

	अगर (extio_stat & EXTIO_MC_BUSERR) अणु
		prपूर्णांकk(KERN_ERR "MC Bus Error\n");
		error |= 1;
	पूर्ण
	अगर (extio_stat & EXTIO_HPC3_BUSERR) अणु
		prपूर्णांकk(KERN_ERR "HPC3 Bus Error 0x%x:<id=0x%x,%s,lane=0x%x>\n",
			hpc3_berr_stat,
			(hpc3_berr_stat & HPC3_BESTAT_PIDMASK) >>
					  HPC3_BESTAT_PIDSHIFT,
			(hpc3_berr_stat & HPC3_BESTAT_CTYPE) ? "PIO" : "DMA",
			hpc3_berr_stat & HPC3_BESTAT_BLMASK);
		error |= 2;
	पूर्ण
	अगर (extio_stat & EXTIO_EISA_BUSERR) अणु
		prपूर्णांकk(KERN_ERR "EISA Bus Error\n");
		error |= 4;
	पूर्ण
	अगर (cpu_err_stat & CPU_ERRMASK) अणु
		prपूर्णांकk(KERN_ERR "CPU error 0x%x<%s%s%s%s%s%s> @ 0x%08x\n",
			cpu_err_stat,
			cpu_err_stat & SGIMC_CSTAT_RD ? "RD " : "",
			cpu_err_stat & SGIMC_CSTAT_PAR ? "PAR " : "",
			cpu_err_stat & SGIMC_CSTAT_ADDR ? "ADDR " : "",
			cpu_err_stat & SGIMC_CSTAT_SYSAD_PAR ? "SYSAD " : "",
			cpu_err_stat & SGIMC_CSTAT_SYSCMD_PAR ? "SYSCMD " : "",
			cpu_err_stat & SGIMC_CSTAT_BAD_DATA ? "BAD_DATA " : "",
			cpu_err_addr);
		error |= 8;
	पूर्ण
	अगर (gio_err_stat & GIO_ERRMASK) अणु
		prपूर्णांकk(KERN_ERR "GIO error 0x%x:<%s%s%s%s%s%s%s%s> @ 0x%08x\n",
			gio_err_stat,
			gio_err_stat & SGIMC_GSTAT_RD ? "RD " : "",
			gio_err_stat & SGIMC_GSTAT_WR ? "WR " : "",
			gio_err_stat & SGIMC_GSTAT_TIME ? "TIME " : "",
			gio_err_stat & SGIMC_GSTAT_PROM ? "PROM " : "",
			gio_err_stat & SGIMC_GSTAT_ADDR ? "ADDR " : "",
			gio_err_stat & SGIMC_GSTAT_BC ? "BC " : "",
			gio_err_stat & SGIMC_GSTAT_PIO_RD ? "PIO_RD " : "",
			gio_err_stat & SGIMC_GSTAT_PIO_WR ? "PIO_WR " : "",
			gio_err_addr);
		error |= 16;
	पूर्ण
	अगर (!error)
		prपूर्णांकk(KERN_ERR "MC: Hmm, didn't find any error condition.\n");
	अन्यथा अणु
		prपूर्णांकk(KERN_ERR "CP0: config %08x,  "
			"MC: cpuctrl0/1: %08x/%05x, giopar: %04x\n"
			"MC: cpu/gio_memacc: %08x/%05x, memcfg0/1: %08x/%08x\n",
			पढ़ो_c0_config(),
			sgimc->cpuctrl0, sgimc->cpuctrl0, sgimc->giopar,
			sgimc->cmacc, sgimc->gmacc,
			sgimc->mconfig0, sgimc->mconfig1);
		prपूर्णांक_cache_tags();
	पूर्ण
	prपूर्णांकk(KERN_ALERT "%s, epc == %0*lx, ra == %0*lx\n",
	       cause_excode_text(regs->cp0_cause),
	       field, regs->cp0_epc, field, regs->regs[31]);
पूर्ण

अटल पूर्णांक check_microtlb(u32 hi, u32 lo, अचिन्हित दीर्घ vaddr)
अणु
	/* This is likely rather similar to correct code ;-) */

	vaddr &= 0x7fffffff; /* Doc. states that top bit is ignored */

	/* If tlb-entry is valid and VPN-high (bits [30:21] ?) matches... */
	अगर ((lo & 2) && (vaddr >> 21) == ((hi<<1) >> 22)) अणु
		u32 ctl = sgimc->dma_ctrl;
		अगर (ctl & 1) अणु
			अचिन्हित पूर्णांक pgsz = (ctl & 2) ? 14:12; /* 16k:4k */
			/* PTEIndex is VPN-low (bits [22:14]/[20:12] ?) */
			अचिन्हित दीर्घ pte = (lo >> 6) << 12; /* PTEBase */
			pte += 8*((vaddr >> pgsz) & 0x1ff);
			अगर (page_is_ram(PFN_DOWN(pte))) अणु
				/*
				 * Note: Since DMA hardware करोes look up
				 * translation on its own, this PTE *must*
				 * match the TLB/EntryLo-रेजिस्टर क्रमmat !
				 */
				अचिन्हित दीर्घ a = *(अचिन्हित दीर्घ *)
						PHYS_TO_XKSEG_UNCACHED(pte);
				a = (a & 0x3f) << 6; /* PFN */
				a += vaddr & ((1 << pgsz) - 1);
				वापस cpu_err_addr == a;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_vdma_memaddr(व्योम)
अणु
	अगर (cpu_err_stat & CPU_ERRMASK) अणु
		u32 a = sgimc->maddronly;

		अगर (!(sgimc->dma_ctrl & 0x100)) /* Xlate-bit clear ? */
			वापस cpu_err_addr == a;

		अगर (check_microtlb(sgimc->dtlb_hi0, sgimc->dtlb_lo0, a) ||
		    check_microtlb(sgimc->dtlb_hi1, sgimc->dtlb_lo1, a) ||
		    check_microtlb(sgimc->dtlb_hi2, sgimc->dtlb_lo2, a) ||
		    check_microtlb(sgimc->dtlb_hi3, sgimc->dtlb_lo3, a))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_vdma_gioaddr(व्योम)
अणु
	अगर (gio_err_stat & GIO_ERRMASK) अणु
		u32 a = sgimc->gio_dma_trans;
		a = (sgimc->gmaddronly & ~a) | (sgimc->gio_dma_sbits & a);
		वापस gio_err_addr == a;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * MC sends an पूर्णांकerrupt whenever bus or parity errors occur. In addition,
 * अगर the error happened during a CPU पढ़ो, it also निश्चितs the bus error
 * pin on the R4K. Code in bus error handler save the MC bus error रेजिस्टरs
 * and then clear the पूर्णांकerrupt when this happens.
 */

अटल पूर्णांक ip28_be_पूर्णांकerrupt(स्थिर काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;

	save_and_clear_buserr();
	/*
	 * Try to find out, whether we got here by a mispredicted speculative
	 * load/store operation.  If so, it's not fatal, we can go on.
	 */
	/* Any cause other than "Interrupt" (ExcCode 0) is fatal. */
	अगर (regs->cp0_cause & CAUSEF_EXCCODE)
		जाओ mips_be_fatal;

	/* Any cause other than "Bus error interrupt" (IP6) is weird. */
	अगर ((regs->cp0_cause & CAUSEF_IP6) != CAUSEF_IP6)
		जाओ mips_be_fatal;

	अगर (extio_stat & (EXTIO_HPC3_BUSERR | EXTIO_EISA_BUSERR))
		जाओ mips_be_fatal;

	/* Any state other than "Memory bus error" is fatal. */
	अगर (cpu_err_stat & CPU_ERRMASK & ~SGIMC_CSTAT_ADDR)
		जाओ mips_be_fatal;

	/* GIO errors other than समयouts are fatal */
	अगर (gio_err_stat & GIO_ERRMASK & ~SGIMC_GSTAT_TIME)
		जाओ mips_be_fatal;

	/*
	 * Now we have an asynchronous bus error, speculatively or DMA caused.
	 * Need to search all DMA descriptors क्रम the error address.
	 */
	क्रम (i = 0; i < माप(hpc3)/माप(काष्ठा hpc3_stat); ++i) अणु
		काष्ठा hpc3_stat *hp = (काष्ठा hpc3_stat *)&hpc3 + i;
		अगर ((cpu_err_stat & CPU_ERRMASK) &&
		    (cpu_err_addr == hp->ndptr || cpu_err_addr == hp->cbp))
			अवरोध;
		अगर ((gio_err_stat & GIO_ERRMASK) &&
		    (gio_err_addr == hp->ndptr || gio_err_addr == hp->cbp))
			अवरोध;
	पूर्ण
	अगर (i < माप(hpc3)/माप(काष्ठा hpc3_stat)) अणु
		काष्ठा hpc3_stat *hp = (काष्ठा hpc3_stat *)&hpc3 + i;
		prपूर्णांकk(KERN_ERR "at DMA addresses: HPC3 @ %08lx:"
		       " ctl %08x, ndp %08x, cbp %08x\n",
		       CPHYSADDR(hp->addr), hp->ctrl, hp->ndptr, hp->cbp);
		जाओ mips_be_fatal;
	पूर्ण
	/* Check MC's भव DMA stuff. */
	अगर (check_vdma_memaddr()) अणु
		prपूर्णांकk(KERN_ERR "at GIO DMA: mem address 0x%08x.\n",
			sgimc->maddronly);
		जाओ mips_be_fatal;
	पूर्ण
	अगर (check_vdma_gioaddr()) अणु
		prपूर्णांकk(KERN_ERR "at GIO DMA: gio address 0x%08x.\n",
			sgimc->gmaddronly);
		जाओ mips_be_fatal;
	पूर्ण
	/* A speculative bus error... */
	अगर (debug_be_पूर्णांकerrupt) अणु
		prपूर्णांक_buserr(regs);
		prपूर्णांकk(KERN_ERR "discarded!\n");
	पूर्ण
	वापस MIPS_BE_DISCARD;

mips_be_fatal:
	prपूर्णांक_buserr(regs);
	वापस MIPS_BE_FATAL;
पूर्ण

व्योम ip22_be_पूर्णांकerrupt(पूर्णांक irq)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();

	count_be_पूर्णांकerrupt++;

	अगर (ip28_be_पूर्णांकerrupt(regs) != MIPS_BE_DISCARD) अणु
		/* Assume it would be too dangerous to जारी ... */
		die_अगर_kernel("Oops", regs);
		क्रमce_sig(SIGBUS);
	पूर्ण अन्यथा अगर (debug_be_पूर्णांकerrupt)
		show_regs(regs);
पूर्ण

अटल पूर्णांक ip28_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	/*
	 * We arrive here only in the unusual हाल of करो_be() invocation,
	 * i.e. by a bus error exception without a bus error पूर्णांकerrupt.
	 */
	अगर (is_fixup) अणु
		count_be_is_fixup++;
		save_and_clear_buserr();
		वापस MIPS_BE_FIXUP;
	पूर्ण
	count_be_handler++;
	वापस ip28_be_पूर्णांकerrupt(regs);
पूर्ण

व्योम __init ip22_be_init(व्योम)
अणु
	board_be_handler = ip28_be_handler;
पूर्ण

पूर्णांक ip28_show_be_info(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "IP28 be fixups\t\t: %u\n", count_be_is_fixup);
	seq_म_लिखो(m, "IP28 be interrupts\t: %u\n", count_be_पूर्णांकerrupt);
	seq_म_लिखो(m, "IP28 be handler\t\t: %u\n", count_be_handler);

	वापस 0;
पूर्ण

अटल पूर्णांक __init debug_be_setup(अक्षर *str)
अणु
	debug_be_पूर्णांकerrupt++;
	वापस 1;
पूर्ण
__setup("ip28_debug_be", debug_be_setup);
