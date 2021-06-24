<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip22-berr.c: Bus error handling.
 *
 * Copyright (C) 2002, 2003 Ladislav Michl (ladis@linux-mips.org)
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/sgi/mc.h>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ioc.h>
#समावेश <यंत्र/sgi/ip22.h>


अटल अचिन्हित पूर्णांक cpu_err_stat;	/* Status reg क्रम CPU */
अटल अचिन्हित पूर्णांक gio_err_stat;	/* Status reg क्रम GIO */
अटल अचिन्हित पूर्णांक cpu_err_addr;	/* Error address reg क्रम CPU */
अटल अचिन्हित पूर्णांक gio_err_addr;	/* Error address reg क्रम GIO */
अटल अचिन्हित पूर्णांक extio_stat;
अटल अचिन्हित पूर्णांक hpc3_berr_stat;	/* Bus error पूर्णांकerrupt status */

अटल व्योम save_and_clear_buserr(व्योम)
अणु
	/* save status रेजिस्टरs */
	cpu_err_addr = sgimc->cerr;
	cpu_err_stat = sgimc->cstat;
	gio_err_addr = sgimc->gerr;
	gio_err_stat = sgimc->gstat;
	extio_stat = ip22_is_fullhouse() ? sgioc->extio : (sgपूर्णांक->errstat << 4);
	hpc3_berr_stat = hpc3c0->bestat;

	sgimc->cstat = sgimc->gstat = 0;
पूर्ण

#घोषणा GIO_ERRMASK	0xff00
#घोषणा CPU_ERRMASK	0x3f00

अटल व्योम prपूर्णांक_buserr(व्योम)
अणु
	अगर (extio_stat & EXTIO_MC_BUSERR)
		prपूर्णांकk(KERN_ERR "MC Bus Error\n");
	अगर (extio_stat & EXTIO_HPC3_BUSERR)
		prपूर्णांकk(KERN_ERR "HPC3 Bus Error 0x%x:<id=0x%x,%s,lane=0x%x>\n",
			hpc3_berr_stat,
			(hpc3_berr_stat & HPC3_BESTAT_PIDMASK) >>
					  HPC3_BESTAT_PIDSHIFT,
			(hpc3_berr_stat & HPC3_BESTAT_CTYPE) ? "PIO" : "DMA",
			hpc3_berr_stat & HPC3_BESTAT_BLMASK);
	अगर (extio_stat & EXTIO_EISA_BUSERR)
		prपूर्णांकk(KERN_ERR "EISA Bus Error\n");
	अगर (cpu_err_stat & CPU_ERRMASK)
		prपूर्णांकk(KERN_ERR "CPU error 0x%x<%s%s%s%s%s%s> @ 0x%08x\n",
			cpu_err_stat,
			cpu_err_stat & SGIMC_CSTAT_RD ? "RD " : "",
			cpu_err_stat & SGIMC_CSTAT_PAR ? "PAR " : "",
			cpu_err_stat & SGIMC_CSTAT_ADDR ? "ADDR " : "",
			cpu_err_stat & SGIMC_CSTAT_SYSAD_PAR ? "SYSAD " : "",
			cpu_err_stat & SGIMC_CSTAT_SYSCMD_PAR ? "SYSCMD " : "",
			cpu_err_stat & SGIMC_CSTAT_BAD_DATA ? "BAD_DATA " : "",
			cpu_err_addr);
	अगर (gio_err_stat & GIO_ERRMASK)
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
पूर्ण

/*
 * MC sends an पूर्णांकerrupt whenever bus or parity errors occur. In addition,
 * अगर the error happened during a CPU पढ़ो, it also निश्चितs the bus error
 * pin on the R4K. Code in bus error handler save the MC bus error रेजिस्टरs
 * and then clear the पूर्णांकerrupt when this happens.
 */

व्योम ip22_be_पूर्णांकerrupt(पूर्णांक irq)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);
	काष्ठा pt_regs *regs = get_irq_regs();

	save_and_clear_buserr();
	prपूर्णांक_buserr();
	prपूर्णांकk(KERN_ALERT "%s bus error, epc == %0*lx, ra == %0*lx\n",
	       (regs->cp0_cause & 4) ? "Data" : "Instruction",
	       field, regs->cp0_epc, field, regs->regs[31]);
	/* Assume it would be too dangerous to जारी ... */
	die_अगर_kernel("Oops", regs);
	क्रमce_sig(SIGBUS);
पूर्ण

अटल पूर्णांक ip22_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	save_and_clear_buserr();
	अगर (is_fixup)
		वापस MIPS_BE_FIXUP;
	prपूर्णांक_buserr();
	वापस MIPS_BE_FATAL;
पूर्ण

व्योम __init ip22_be_init(व्योम)
अणु
	board_be_handler = ip22_be_handler;
पूर्ण
