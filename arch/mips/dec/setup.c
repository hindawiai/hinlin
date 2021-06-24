<शैली गुरु>
/*
 * System-specअगरic setup, especially पूर्णांकerrupts.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998 Harald Koerfgen
 * Copyright (C) 2000, 2001, 2002, 2003, 2005, 2020  Maciej W. Rozycki
 */
#समावेश <linux/console.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqnr.h>
#समावेश <linux/memblock.h>
#समावेश <linux/param.h>
#समावेश <linux/percpu-defs.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/wbflush.h>

#समावेश <यंत्र/dec/पूर्णांकerrupts.h>
#समावेश <यंत्र/dec/ioasic.h>
#समावेश <यंत्र/dec/ioasic_addrs.h>
#समावेश <यंत्र/dec/ioasic_पूर्णांकs.h>
#समावेश <यंत्र/dec/kn01.h>
#समावेश <यंत्र/dec/kn02.h>
#समावेश <यंत्र/dec/kn02ba.h>
#समावेश <यंत्र/dec/kn02ca.h>
#समावेश <यंत्र/dec/kn03.h>
#समावेश <यंत्र/dec/kn230.h>
#समावेश <यंत्र/dec/प्रणाली.h>


बाह्य व्योम dec_machine_restart(अक्षर *command);
बाह्य व्योम dec_machine_halt(व्योम);
बाह्य व्योम dec_machine_घातer_off(व्योम);
बाह्य irqवापस_t dec_पूर्णांकr_halt(पूर्णांक irq, व्योम *dev_id);

अचिन्हित दीर्घ dec_kn_slot_base, dec_kn_slot_size;

EXPORT_SYMBOL(dec_kn_slot_base);
EXPORT_SYMBOL(dec_kn_slot_size);

पूर्णांक dec_tc_bus;

DEFINE_SPINLOCK(ioasic_ssr_lock);
EXPORT_SYMBOL(ioasic_ssr_lock);

अस्थिर u32 *ioasic_base;

EXPORT_SYMBOL(ioasic_base);

/*
 * IRQ routing and priority tables.  Priorites are set as follows:
 *
 *		KN01	KN230	KN02	KN02-BA	KN02-CA	KN03
 *
 * MEMORY	CPU	CPU	CPU	ASIC	CPU	CPU
 * RTC		CPU	CPU	CPU	ASIC	CPU	CPU
 * DMA		-	-	-	ASIC	ASIC	ASIC
 * SERIAL0	CPU	CPU	CSR	ASIC	ASIC	ASIC
 * SERIAL1	-	-	-	ASIC	-	ASIC
 * SCSI		CPU	CPU	CSR	ASIC	ASIC	ASIC
 * ETHERNET	CPU	*	CSR	ASIC	ASIC	ASIC
 * other	-	-	-	ASIC	-	-
 * TC2		-	-	CSR	CPU	ASIC	ASIC
 * TC1		-	-	CSR	CPU	ASIC	ASIC
 * TC0		-	-	CSR	CPU	ASIC	ASIC
 * other	-	CPU	-	CPU	ASIC	ASIC
 * other	-	-	-	-	CPU	CPU
 *
 * * -- shared with SCSI
 */

पूर्णांक dec_पूर्णांकerrupt[DEC_NR_INTS] = अणु
	[0 ... DEC_NR_INTS - 1] = -1
पूर्ण;

EXPORT_SYMBOL(dec_पूर्णांकerrupt);

पूर्णांक_ptr cpu_mask_nr_tbl[DEC_MAX_CPU_INTS][2] = अणु
	अणु अणु .i = ~0 पूर्ण, अणु .p = dec_पूर्णांकr_unimplemented पूर्ण पूर्ण,
पूर्ण;
पूर्णांक_ptr asic_mask_nr_tbl[DEC_MAX_ASIC_INTS][2] = अणु
	अणु अणु .i = ~0 पूर्ण, अणु .p = asic_पूर्णांकr_unimplemented पूर्ण पूर्ण,
पूर्ण;
पूर्णांक cpu_fpu_mask = DEC_CPU_IRQ_MASK(DEC_CPU_INR_FPU);
पूर्णांक *fpu_kstat_irq;

अटल irq_handler_t busirq_handler;
अटल अचिन्हित पूर्णांक busirq_flags = IRQF_NO_THREAD;

/*
 * Bus error (DBE/IBE exceptions and bus पूर्णांकerrupts) handling setup.
 */
अटल व्योम __init dec_be_init(व्योम)
अणु
	चयन (mips_machtype) अणु
	हाल MACH_DS23100:	/* DS2100/DS3100 Pmin/Pmax */
		board_be_handler = dec_kn01_be_handler;
		busirq_handler = dec_kn01_be_पूर्णांकerrupt;
		busirq_flags |= IRQF_SHARED;
		dec_kn01_be_init();
		अवरोध;
	हाल MACH_DS5000_1XX:	/* DS5000/1xx 3min */
	हाल MACH_DS5000_XX:	/* DS5000/xx Maxine */
		board_be_handler = dec_kn02xa_be_handler;
		busirq_handler = dec_kn02xa_be_पूर्णांकerrupt;
		dec_kn02xa_be_init();
		अवरोध;
	हाल MACH_DS5000_200:	/* DS5000/200 3max */
	हाल MACH_DS5000_2X0:	/* DS5000/240 3max+ */
	हाल MACH_DS5900:	/* DS5900 bigmax */
		board_be_handler = dec_ecc_be_handler;
		busirq_handler = dec_ecc_be_पूर्णांकerrupt;
		dec_ecc_be_init();
		अवरोध;
	पूर्ण
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	board_be_init = dec_be_init;

	wbflush_setup();

	_machine_restart = dec_machine_restart;
	_machine_halt = dec_machine_halt;
	pm_घातer_off = dec_machine_घातer_off;

	ioport_resource.start = ~0UL;
	ioport_resource.end = 0UL;

	/* Stay away from the firmware working memory area क्रम now. */
	memblock_reserve(PHYS_OFFSET, __pa_symbol(&_text) - PHYS_OFFSET);
पूर्ण

/*
 * Machine-specअगरic initialisation क्रम KN01, aka DS2100 (aka Pmin)
 * or DS3100 (aka Pmax).
 */
अटल पूर्णांक kn01_पूर्णांकerrupt[DEC_NR_INTS] __initdata = अणु
	[DEC_IRQ_CASCADE]	= -1,
	[DEC_IRQ_AB_RECV]	= -1,
	[DEC_IRQ_AB_XMIT]	= -1,
	[DEC_IRQ_DZ11]		= DEC_CPU_IRQ_NR(KN01_CPU_INR_DZ11),
	[DEC_IRQ_ASC]		= -1,
	[DEC_IRQ_FLOPPY]	= -1,
	[DEC_IRQ_FPU]		= DEC_CPU_IRQ_NR(DEC_CPU_INR_FPU),
	[DEC_IRQ_HALT]		= -1,
	[DEC_IRQ_ISDN]		= -1,
	[DEC_IRQ_LANCE]		= DEC_CPU_IRQ_NR(KN01_CPU_INR_LANCE),
	[DEC_IRQ_BUS]		= DEC_CPU_IRQ_NR(KN01_CPU_INR_BUS),
	[DEC_IRQ_PSU]		= -1,
	[DEC_IRQ_RTC]		= DEC_CPU_IRQ_NR(KN01_CPU_INR_RTC),
	[DEC_IRQ_SCC0]		= -1,
	[DEC_IRQ_SCC1]		= -1,
	[DEC_IRQ_SII]		= DEC_CPU_IRQ_NR(KN01_CPU_INR_SII),
	[DEC_IRQ_TC0]		= -1,
	[DEC_IRQ_TC1]		= -1,
	[DEC_IRQ_TC2]		= -1,
	[DEC_IRQ_TIMER]		= -1,
	[DEC_IRQ_VIDEO]		= DEC_CPU_IRQ_NR(KN01_CPU_INR_VIDEO),
	[DEC_IRQ_ASC_MERR]	= -1,
	[DEC_IRQ_ASC_ERR]	= -1,
	[DEC_IRQ_ASC_DMA]	= -1,
	[DEC_IRQ_FLOPPY_ERR]	= -1,
	[DEC_IRQ_ISDN_ERR]	= -1,
	[DEC_IRQ_ISDN_RXDMA]	= -1,
	[DEC_IRQ_ISDN_TXDMA]	= -1,
	[DEC_IRQ_LANCE_MERR]	= -1,
	[DEC_IRQ_SCC0A_RXERR]	= -1,
	[DEC_IRQ_SCC0A_RXDMA]	= -1,
	[DEC_IRQ_SCC0A_TXERR]	= -1,
	[DEC_IRQ_SCC0A_TXDMA]	= -1,
	[DEC_IRQ_AB_RXERR]	= -1,
	[DEC_IRQ_AB_RXDMA]	= -1,
	[DEC_IRQ_AB_TXERR]	= -1,
	[DEC_IRQ_AB_TXDMA]	= -1,
	[DEC_IRQ_SCC1A_RXERR]	= -1,
	[DEC_IRQ_SCC1A_RXDMA]	= -1,
	[DEC_IRQ_SCC1A_TXERR]	= -1,
	[DEC_IRQ_SCC1A_TXDMA]	= -1,
पूर्ण;

अटल पूर्णांक_ptr kn01_cpu_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN01_CPU_INR_BUS) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN01_CPU_INR_BUS) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN01_CPU_INR_RTC) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN01_CPU_INR_RTC) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN01_CPU_INR_DZ11) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN01_CPU_INR_DZ11) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN01_CPU_INR_SII) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN01_CPU_INR_SII) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN01_CPU_INR_LANCE) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN01_CPU_INR_LANCE) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_ALL पूर्ण,
		अणु .p = cpu_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल व्योम __init dec_init_kn01(व्योम)
अणु
	/* IRQ routing. */
	स_नकल(&dec_पूर्णांकerrupt, &kn01_पूर्णांकerrupt,
		माप(kn01_पूर्णांकerrupt));

	/* CPU IRQ priorities. */
	स_नकल(&cpu_mask_nr_tbl, &kn01_cpu_mask_nr_tbl,
		माप(kn01_cpu_mask_nr_tbl));

	mips_cpu_irq_init();

पूर्ण				/* dec_init_kn01 */


/*
 * Machine-specअगरic initialisation क्रम KN230, aka DS5100, aka MIPSmate.
 */
अटल पूर्णांक kn230_पूर्णांकerrupt[DEC_NR_INTS] __initdata = अणु
	[DEC_IRQ_CASCADE]	= -1,
	[DEC_IRQ_AB_RECV]	= -1,
	[DEC_IRQ_AB_XMIT]	= -1,
	[DEC_IRQ_DZ11]		= DEC_CPU_IRQ_NR(KN230_CPU_INR_DZ11),
	[DEC_IRQ_ASC]		= -1,
	[DEC_IRQ_FLOPPY]	= -1,
	[DEC_IRQ_FPU]		= DEC_CPU_IRQ_NR(DEC_CPU_INR_FPU),
	[DEC_IRQ_HALT]		= DEC_CPU_IRQ_NR(KN230_CPU_INR_HALT),
	[DEC_IRQ_ISDN]		= -1,
	[DEC_IRQ_LANCE]		= DEC_CPU_IRQ_NR(KN230_CPU_INR_LANCE),
	[DEC_IRQ_BUS]		= DEC_CPU_IRQ_NR(KN230_CPU_INR_BUS),
	[DEC_IRQ_PSU]		= -1,
	[DEC_IRQ_RTC]		= DEC_CPU_IRQ_NR(KN230_CPU_INR_RTC),
	[DEC_IRQ_SCC0]		= -1,
	[DEC_IRQ_SCC1]		= -1,
	[DEC_IRQ_SII]		= DEC_CPU_IRQ_NR(KN230_CPU_INR_SII),
	[DEC_IRQ_TC0]		= -1,
	[DEC_IRQ_TC1]		= -1,
	[DEC_IRQ_TC2]		= -1,
	[DEC_IRQ_TIMER]		= -1,
	[DEC_IRQ_VIDEO]		= -1,
	[DEC_IRQ_ASC_MERR]	= -1,
	[DEC_IRQ_ASC_ERR]	= -1,
	[DEC_IRQ_ASC_DMA]	= -1,
	[DEC_IRQ_FLOPPY_ERR]	= -1,
	[DEC_IRQ_ISDN_ERR]	= -1,
	[DEC_IRQ_ISDN_RXDMA]	= -1,
	[DEC_IRQ_ISDN_TXDMA]	= -1,
	[DEC_IRQ_LANCE_MERR]	= -1,
	[DEC_IRQ_SCC0A_RXERR]	= -1,
	[DEC_IRQ_SCC0A_RXDMA]	= -1,
	[DEC_IRQ_SCC0A_TXERR]	= -1,
	[DEC_IRQ_SCC0A_TXDMA]	= -1,
	[DEC_IRQ_AB_RXERR]	= -1,
	[DEC_IRQ_AB_RXDMA]	= -1,
	[DEC_IRQ_AB_TXERR]	= -1,
	[DEC_IRQ_AB_TXDMA]	= -1,
	[DEC_IRQ_SCC1A_RXERR]	= -1,
	[DEC_IRQ_SCC1A_RXDMA]	= -1,
	[DEC_IRQ_SCC1A_TXERR]	= -1,
	[DEC_IRQ_SCC1A_TXDMA]	= -1,
पूर्ण;

अटल पूर्णांक_ptr kn230_cpu_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN230_CPU_INR_BUS) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN230_CPU_INR_BUS) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN230_CPU_INR_RTC) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN230_CPU_INR_RTC) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN230_CPU_INR_DZ11) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN230_CPU_INR_DZ11) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN230_CPU_INR_SII) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN230_CPU_INR_SII) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_ALL पूर्ण,
		अणु .p = cpu_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल व्योम __init dec_init_kn230(व्योम)
अणु
	/* IRQ routing. */
	स_नकल(&dec_पूर्णांकerrupt, &kn230_पूर्णांकerrupt,
		माप(kn230_पूर्णांकerrupt));

	/* CPU IRQ priorities. */
	स_नकल(&cpu_mask_nr_tbl, &kn230_cpu_mask_nr_tbl,
		माप(kn230_cpu_mask_nr_tbl));

	mips_cpu_irq_init();

पूर्ण				/* dec_init_kn230 */


/*
 * Machine-specअगरic initialisation क्रम KN02, aka DS5000/200, aka 3max.
 */
अटल पूर्णांक kn02_पूर्णांकerrupt[DEC_NR_INTS] __initdata = अणु
	[DEC_IRQ_CASCADE]	= DEC_CPU_IRQ_NR(KN02_CPU_INR_CASCADE),
	[DEC_IRQ_AB_RECV]	= -1,
	[DEC_IRQ_AB_XMIT]	= -1,
	[DEC_IRQ_DZ11]		= KN02_IRQ_NR(KN02_CSR_INR_DZ11),
	[DEC_IRQ_ASC]		= KN02_IRQ_NR(KN02_CSR_INR_ASC),
	[DEC_IRQ_FLOPPY]	= -1,
	[DEC_IRQ_FPU]		= DEC_CPU_IRQ_NR(DEC_CPU_INR_FPU),
	[DEC_IRQ_HALT]		= -1,
	[DEC_IRQ_ISDN]		= -1,
	[DEC_IRQ_LANCE]		= KN02_IRQ_NR(KN02_CSR_INR_LANCE),
	[DEC_IRQ_BUS]		= DEC_CPU_IRQ_NR(KN02_CPU_INR_BUS),
	[DEC_IRQ_PSU]		= -1,
	[DEC_IRQ_RTC]		= DEC_CPU_IRQ_NR(KN02_CPU_INR_RTC),
	[DEC_IRQ_SCC0]		= -1,
	[DEC_IRQ_SCC1]		= -1,
	[DEC_IRQ_SII]		= -1,
	[DEC_IRQ_TC0]		= KN02_IRQ_NR(KN02_CSR_INR_TC0),
	[DEC_IRQ_TC1]		= KN02_IRQ_NR(KN02_CSR_INR_TC1),
	[DEC_IRQ_TC2]		= KN02_IRQ_NR(KN02_CSR_INR_TC2),
	[DEC_IRQ_TIMER]		= -1,
	[DEC_IRQ_VIDEO]		= -1,
	[DEC_IRQ_ASC_MERR]	= -1,
	[DEC_IRQ_ASC_ERR]	= -1,
	[DEC_IRQ_ASC_DMA]	= -1,
	[DEC_IRQ_FLOPPY_ERR]	= -1,
	[DEC_IRQ_ISDN_ERR]	= -1,
	[DEC_IRQ_ISDN_RXDMA]	= -1,
	[DEC_IRQ_ISDN_TXDMA]	= -1,
	[DEC_IRQ_LANCE_MERR]	= -1,
	[DEC_IRQ_SCC0A_RXERR]	= -1,
	[DEC_IRQ_SCC0A_RXDMA]	= -1,
	[DEC_IRQ_SCC0A_TXERR]	= -1,
	[DEC_IRQ_SCC0A_TXDMA]	= -1,
	[DEC_IRQ_AB_RXERR]	= -1,
	[DEC_IRQ_AB_RXDMA]	= -1,
	[DEC_IRQ_AB_TXERR]	= -1,
	[DEC_IRQ_AB_TXDMA]	= -1,
	[DEC_IRQ_SCC1A_RXERR]	= -1,
	[DEC_IRQ_SCC1A_RXDMA]	= -1,
	[DEC_IRQ_SCC1A_TXERR]	= -1,
	[DEC_IRQ_SCC1A_TXDMA]	= -1,
पूर्ण;

अटल पूर्णांक_ptr kn02_cpu_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02_CPU_INR_BUS) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN02_CPU_INR_BUS) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02_CPU_INR_RTC) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN02_CPU_INR_RTC) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02_CPU_INR_CASCADE) पूर्ण,
		अणु .p = kn02_io_पूर्णांक पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_ALL पूर्ण,
		अणु .p = cpu_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक_ptr kn02_asic_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = KN02_IRQ_MASK(KN02_CSR_INR_DZ11) पूर्ण,
		अणु .i = KN02_IRQ_NR(KN02_CSR_INR_DZ11) पूर्ण पूर्ण,
	अणु अणु .i = KN02_IRQ_MASK(KN02_CSR_INR_ASC) पूर्ण,
		अणु .i = KN02_IRQ_NR(KN02_CSR_INR_ASC) पूर्ण पूर्ण,
	अणु अणु .i = KN02_IRQ_MASK(KN02_CSR_INR_LANCE) पूर्ण,
		अणु .i = KN02_IRQ_NR(KN02_CSR_INR_LANCE) पूर्ण पूर्ण,
	अणु अणु .i = KN02_IRQ_MASK(KN02_CSR_INR_TC2) पूर्ण,
		अणु .i = KN02_IRQ_NR(KN02_CSR_INR_TC2) पूर्ण पूर्ण,
	अणु अणु .i = KN02_IRQ_MASK(KN02_CSR_INR_TC1) पूर्ण,
		अणु .i = KN02_IRQ_NR(KN02_CSR_INR_TC1) पूर्ण पूर्ण,
	अणु अणु .i = KN02_IRQ_MASK(KN02_CSR_INR_TC0) पूर्ण,
		अणु .i = KN02_IRQ_NR(KN02_CSR_INR_TC0) पूर्ण पूर्ण,
	अणु अणु .i = KN02_IRQ_ALL पूर्ण,
		अणु .p = kn02_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल व्योम __init dec_init_kn02(व्योम)
अणु
	/* IRQ routing. */
	स_नकल(&dec_पूर्णांकerrupt, &kn02_पूर्णांकerrupt,
		माप(kn02_पूर्णांकerrupt));

	/* CPU IRQ priorities. */
	स_नकल(&cpu_mask_nr_tbl, &kn02_cpu_mask_nr_tbl,
		माप(kn02_cpu_mask_nr_tbl));

	/* KN02 CSR IRQ priorities. */
	स_नकल(&asic_mask_nr_tbl, &kn02_asic_mask_nr_tbl,
		माप(kn02_asic_mask_nr_tbl));

	mips_cpu_irq_init();
	init_kn02_irqs(KN02_IRQ_BASE);

पूर्ण				/* dec_init_kn02 */


/*
 * Machine-specअगरic initialisation क्रम KN02-BA, aka DS5000/1xx
 * (xx = 20, 25, 33), aka 3min.  Also applies to KN04(-BA), aka
 * DS5000/150, aka 4min.
 */
अटल पूर्णांक kn02ba_पूर्णांकerrupt[DEC_NR_INTS] __initdata = अणु
	[DEC_IRQ_CASCADE]	= DEC_CPU_IRQ_NR(KN02BA_CPU_INR_CASCADE),
	[DEC_IRQ_AB_RECV]	= -1,
	[DEC_IRQ_AB_XMIT]	= -1,
	[DEC_IRQ_DZ11]		= -1,
	[DEC_IRQ_ASC]		= IO_IRQ_NR(KN02BA_IO_INR_ASC),
	[DEC_IRQ_FLOPPY]	= -1,
	[DEC_IRQ_FPU]		= DEC_CPU_IRQ_NR(DEC_CPU_INR_FPU),
	[DEC_IRQ_HALT]		= DEC_CPU_IRQ_NR(KN02BA_CPU_INR_HALT),
	[DEC_IRQ_ISDN]		= -1,
	[DEC_IRQ_LANCE]		= IO_IRQ_NR(KN02BA_IO_INR_LANCE),
	[DEC_IRQ_BUS]		= IO_IRQ_NR(KN02BA_IO_INR_BUS),
	[DEC_IRQ_PSU]		= IO_IRQ_NR(KN02BA_IO_INR_PSU),
	[DEC_IRQ_RTC]		= IO_IRQ_NR(KN02BA_IO_INR_RTC),
	[DEC_IRQ_SCC0]		= IO_IRQ_NR(KN02BA_IO_INR_SCC0),
	[DEC_IRQ_SCC1]		= IO_IRQ_NR(KN02BA_IO_INR_SCC1),
	[DEC_IRQ_SII]		= -1,
	[DEC_IRQ_TC0]		= DEC_CPU_IRQ_NR(KN02BA_CPU_INR_TC0),
	[DEC_IRQ_TC1]		= DEC_CPU_IRQ_NR(KN02BA_CPU_INR_TC1),
	[DEC_IRQ_TC2]		= DEC_CPU_IRQ_NR(KN02BA_CPU_INR_TC2),
	[DEC_IRQ_TIMER]		= -1,
	[DEC_IRQ_VIDEO]		= -1,
	[DEC_IRQ_ASC_MERR]	= IO_IRQ_NR(IO_INR_ASC_MERR),
	[DEC_IRQ_ASC_ERR]	= IO_IRQ_NR(IO_INR_ASC_ERR),
	[DEC_IRQ_ASC_DMA]	= IO_IRQ_NR(IO_INR_ASC_DMA),
	[DEC_IRQ_FLOPPY_ERR]	= -1,
	[DEC_IRQ_ISDN_ERR]	= -1,
	[DEC_IRQ_ISDN_RXDMA]	= -1,
	[DEC_IRQ_ISDN_TXDMA]	= -1,
	[DEC_IRQ_LANCE_MERR]	= IO_IRQ_NR(IO_INR_LANCE_MERR),
	[DEC_IRQ_SCC0A_RXERR]	= IO_IRQ_NR(IO_INR_SCC0A_RXERR),
	[DEC_IRQ_SCC0A_RXDMA]	= IO_IRQ_NR(IO_INR_SCC0A_RXDMA),
	[DEC_IRQ_SCC0A_TXERR]	= IO_IRQ_NR(IO_INR_SCC0A_TXERR),
	[DEC_IRQ_SCC0A_TXDMA]	= IO_IRQ_NR(IO_INR_SCC0A_TXDMA),
	[DEC_IRQ_AB_RXERR]	= -1,
	[DEC_IRQ_AB_RXDMA]	= -1,
	[DEC_IRQ_AB_TXERR]	= -1,
	[DEC_IRQ_AB_TXDMA]	= -1,
	[DEC_IRQ_SCC1A_RXERR]	= IO_IRQ_NR(IO_INR_SCC1A_RXERR),
	[DEC_IRQ_SCC1A_RXDMA]	= IO_IRQ_NR(IO_INR_SCC1A_RXDMA),
	[DEC_IRQ_SCC1A_TXERR]	= IO_IRQ_NR(IO_INR_SCC1A_TXERR),
	[DEC_IRQ_SCC1A_TXDMA]	= IO_IRQ_NR(IO_INR_SCC1A_TXDMA),
पूर्ण;

अटल पूर्णांक_ptr kn02ba_cpu_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02BA_CPU_INR_CASCADE) पूर्ण,
		अणु .p = kn02xa_io_पूर्णांक पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02BA_CPU_INR_TC2) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN02BA_CPU_INR_TC2) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02BA_CPU_INR_TC1) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN02BA_CPU_INR_TC1) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02BA_CPU_INR_TC0) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN02BA_CPU_INR_TC0) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_ALL पूर्ण,
		अणु .p = cpu_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक_ptr kn02ba_asic_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = IO_IRQ_MASK(KN02BA_IO_INR_BUS) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02BA_IO_INR_BUS) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02BA_IO_INR_RTC) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02BA_IO_INR_RTC) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_DMA पूर्ण,
		अणु .p = asic_dma_पूर्णांक पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02BA_IO_INR_SCC0) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02BA_IO_INR_SCC0) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02BA_IO_INR_SCC1) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02BA_IO_INR_SCC1) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02BA_IO_INR_ASC) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02BA_IO_INR_ASC) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02BA_IO_INR_LANCE) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02BA_IO_INR_LANCE) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_ALL पूर्ण,
		अणु .p = asic_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल व्योम __init dec_init_kn02ba(व्योम)
अणु
	/* IRQ routing. */
	स_नकल(&dec_पूर्णांकerrupt, &kn02ba_पूर्णांकerrupt,
		माप(kn02ba_पूर्णांकerrupt));

	/* CPU IRQ priorities. */
	स_नकल(&cpu_mask_nr_tbl, &kn02ba_cpu_mask_nr_tbl,
		माप(kn02ba_cpu_mask_nr_tbl));

	/* I/O ASIC IRQ priorities. */
	स_नकल(&asic_mask_nr_tbl, &kn02ba_asic_mask_nr_tbl,
		माप(kn02ba_asic_mask_nr_tbl));

	mips_cpu_irq_init();
	init_ioasic_irqs(IO_IRQ_BASE);

पूर्ण				/* dec_init_kn02ba */


/*
 * Machine-specअगरic initialisation क्रम KN02-CA, aka DS5000/xx,
 * (xx = 20, 25, 33), aka MAXine.  Also applies to KN04(-CA), aka
 * DS5000/50, aka 4MAXine.
 */
अटल पूर्णांक kn02ca_पूर्णांकerrupt[DEC_NR_INTS] __initdata = अणु
	[DEC_IRQ_CASCADE]	= DEC_CPU_IRQ_NR(KN02CA_CPU_INR_CASCADE),
	[DEC_IRQ_AB_RECV]	= IO_IRQ_NR(KN02CA_IO_INR_AB_RECV),
	[DEC_IRQ_AB_XMIT]	= IO_IRQ_NR(KN02CA_IO_INR_AB_XMIT),
	[DEC_IRQ_DZ11]		= -1,
	[DEC_IRQ_ASC]		= IO_IRQ_NR(KN02CA_IO_INR_ASC),
	[DEC_IRQ_FLOPPY]	= IO_IRQ_NR(KN02CA_IO_INR_FLOPPY),
	[DEC_IRQ_FPU]		= DEC_CPU_IRQ_NR(DEC_CPU_INR_FPU),
	[DEC_IRQ_HALT]		= DEC_CPU_IRQ_NR(KN02CA_CPU_INR_HALT),
	[DEC_IRQ_ISDN]		= IO_IRQ_NR(KN02CA_IO_INR_ISDN),
	[DEC_IRQ_LANCE]		= IO_IRQ_NR(KN02CA_IO_INR_LANCE),
	[DEC_IRQ_BUS]		= DEC_CPU_IRQ_NR(KN02CA_CPU_INR_BUS),
	[DEC_IRQ_PSU]		= -1,
	[DEC_IRQ_RTC]		= DEC_CPU_IRQ_NR(KN02CA_CPU_INR_RTC),
	[DEC_IRQ_SCC0]		= IO_IRQ_NR(KN02CA_IO_INR_SCC0),
	[DEC_IRQ_SCC1]		= -1,
	[DEC_IRQ_SII]		= -1,
	[DEC_IRQ_TC0]		= IO_IRQ_NR(KN02CA_IO_INR_TC0),
	[DEC_IRQ_TC1]		= IO_IRQ_NR(KN02CA_IO_INR_TC1),
	[DEC_IRQ_TC2]		= -1,
	[DEC_IRQ_TIMER]		= DEC_CPU_IRQ_NR(KN02CA_CPU_INR_TIMER),
	[DEC_IRQ_VIDEO]		= IO_IRQ_NR(KN02CA_IO_INR_VIDEO),
	[DEC_IRQ_ASC_MERR]	= IO_IRQ_NR(IO_INR_ASC_MERR),
	[DEC_IRQ_ASC_ERR]	= IO_IRQ_NR(IO_INR_ASC_ERR),
	[DEC_IRQ_ASC_DMA]	= IO_IRQ_NR(IO_INR_ASC_DMA),
	[DEC_IRQ_FLOPPY_ERR]	= IO_IRQ_NR(IO_INR_FLOPPY_ERR),
	[DEC_IRQ_ISDN_ERR]	= IO_IRQ_NR(IO_INR_ISDN_ERR),
	[DEC_IRQ_ISDN_RXDMA]	= IO_IRQ_NR(IO_INR_ISDN_RXDMA),
	[DEC_IRQ_ISDN_TXDMA]	= IO_IRQ_NR(IO_INR_ISDN_TXDMA),
	[DEC_IRQ_LANCE_MERR]	= IO_IRQ_NR(IO_INR_LANCE_MERR),
	[DEC_IRQ_SCC0A_RXERR]	= IO_IRQ_NR(IO_INR_SCC0A_RXERR),
	[DEC_IRQ_SCC0A_RXDMA]	= IO_IRQ_NR(IO_INR_SCC0A_RXDMA),
	[DEC_IRQ_SCC0A_TXERR]	= IO_IRQ_NR(IO_INR_SCC0A_TXERR),
	[DEC_IRQ_SCC0A_TXDMA]	= IO_IRQ_NR(IO_INR_SCC0A_TXDMA),
	[DEC_IRQ_AB_RXERR]	= IO_IRQ_NR(IO_INR_AB_RXERR),
	[DEC_IRQ_AB_RXDMA]	= IO_IRQ_NR(IO_INR_AB_RXDMA),
	[DEC_IRQ_AB_TXERR]	= IO_IRQ_NR(IO_INR_AB_TXERR),
	[DEC_IRQ_AB_TXDMA]	= IO_IRQ_NR(IO_INR_AB_TXDMA),
	[DEC_IRQ_SCC1A_RXERR]	= -1,
	[DEC_IRQ_SCC1A_RXDMA]	= -1,
	[DEC_IRQ_SCC1A_TXERR]	= -1,
	[DEC_IRQ_SCC1A_TXDMA]	= -1,
पूर्ण;

अटल पूर्णांक_ptr kn02ca_cpu_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02CA_CPU_INR_BUS) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN02CA_CPU_INR_BUS) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02CA_CPU_INR_RTC) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN02CA_CPU_INR_RTC) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN02CA_CPU_INR_CASCADE) पूर्ण,
		अणु .p = kn02xa_io_पूर्णांक पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_ALL पूर्ण,
		अणु .p = cpu_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक_ptr kn02ca_asic_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = IO_IRQ_DMA पूर्ण,
		अणु .p = asic_dma_पूर्णांक पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02CA_IO_INR_SCC0) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02CA_IO_INR_SCC0) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02CA_IO_INR_ASC) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02CA_IO_INR_ASC) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02CA_IO_INR_LANCE) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02CA_IO_INR_LANCE) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02CA_IO_INR_TC1) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02CA_IO_INR_TC1) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN02CA_IO_INR_TC0) पूर्ण,
		अणु .i = IO_IRQ_NR(KN02CA_IO_INR_TC0) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_ALL पूर्ण,
		अणु .p = asic_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल व्योम __init dec_init_kn02ca(व्योम)
अणु
	/* IRQ routing. */
	स_नकल(&dec_पूर्णांकerrupt, &kn02ca_पूर्णांकerrupt,
		माप(kn02ca_पूर्णांकerrupt));

	/* CPU IRQ priorities. */
	स_नकल(&cpu_mask_nr_tbl, &kn02ca_cpu_mask_nr_tbl,
		माप(kn02ca_cpu_mask_nr_tbl));

	/* I/O ASIC IRQ priorities. */
	स_नकल(&asic_mask_nr_tbl, &kn02ca_asic_mask_nr_tbl,
		माप(kn02ca_asic_mask_nr_tbl));

	mips_cpu_irq_init();
	init_ioasic_irqs(IO_IRQ_BASE);

पूर्ण				/* dec_init_kn02ca */


/*
 * Machine-specअगरic initialisation क्रम KN03, aka DS5000/240,
 * aka 3max+ and DS5900, aka BIGmax.  Also applies to KN05, aka
 * DS5000/260, aka 4max+ and DS5900/260.
 */
अटल पूर्णांक kn03_पूर्णांकerrupt[DEC_NR_INTS] __initdata = अणु
	[DEC_IRQ_CASCADE]	= DEC_CPU_IRQ_NR(KN03_CPU_INR_CASCADE),
	[DEC_IRQ_AB_RECV]	= -1,
	[DEC_IRQ_AB_XMIT]	= -1,
	[DEC_IRQ_DZ11]		= -1,
	[DEC_IRQ_ASC]		= IO_IRQ_NR(KN03_IO_INR_ASC),
	[DEC_IRQ_FLOPPY]	= -1,
	[DEC_IRQ_FPU]		= DEC_CPU_IRQ_NR(DEC_CPU_INR_FPU),
	[DEC_IRQ_HALT]		= DEC_CPU_IRQ_NR(KN03_CPU_INR_HALT),
	[DEC_IRQ_ISDN]		= -1,
	[DEC_IRQ_LANCE]		= IO_IRQ_NR(KN03_IO_INR_LANCE),
	[DEC_IRQ_BUS]		= DEC_CPU_IRQ_NR(KN03_CPU_INR_BUS),
	[DEC_IRQ_PSU]		= IO_IRQ_NR(KN03_IO_INR_PSU),
	[DEC_IRQ_RTC]		= DEC_CPU_IRQ_NR(KN03_CPU_INR_RTC),
	[DEC_IRQ_SCC0]		= IO_IRQ_NR(KN03_IO_INR_SCC0),
	[DEC_IRQ_SCC1]		= IO_IRQ_NR(KN03_IO_INR_SCC1),
	[DEC_IRQ_SII]		= -1,
	[DEC_IRQ_TC0]		= IO_IRQ_NR(KN03_IO_INR_TC0),
	[DEC_IRQ_TC1]		= IO_IRQ_NR(KN03_IO_INR_TC1),
	[DEC_IRQ_TC2]		= IO_IRQ_NR(KN03_IO_INR_TC2),
	[DEC_IRQ_TIMER]		= -1,
	[DEC_IRQ_VIDEO]		= -1,
	[DEC_IRQ_ASC_MERR]	= IO_IRQ_NR(IO_INR_ASC_MERR),
	[DEC_IRQ_ASC_ERR]	= IO_IRQ_NR(IO_INR_ASC_ERR),
	[DEC_IRQ_ASC_DMA]	= IO_IRQ_NR(IO_INR_ASC_DMA),
	[DEC_IRQ_FLOPPY_ERR]	= -1,
	[DEC_IRQ_ISDN_ERR]	= -1,
	[DEC_IRQ_ISDN_RXDMA]	= -1,
	[DEC_IRQ_ISDN_TXDMA]	= -1,
	[DEC_IRQ_LANCE_MERR]	= IO_IRQ_NR(IO_INR_LANCE_MERR),
	[DEC_IRQ_SCC0A_RXERR]	= IO_IRQ_NR(IO_INR_SCC0A_RXERR),
	[DEC_IRQ_SCC0A_RXDMA]	= IO_IRQ_NR(IO_INR_SCC0A_RXDMA),
	[DEC_IRQ_SCC0A_TXERR]	= IO_IRQ_NR(IO_INR_SCC0A_TXERR),
	[DEC_IRQ_SCC0A_TXDMA]	= IO_IRQ_NR(IO_INR_SCC0A_TXDMA),
	[DEC_IRQ_AB_RXERR]	= -1,
	[DEC_IRQ_AB_RXDMA]	= -1,
	[DEC_IRQ_AB_TXERR]	= -1,
	[DEC_IRQ_AB_TXDMA]	= -1,
	[DEC_IRQ_SCC1A_RXERR]	= IO_IRQ_NR(IO_INR_SCC1A_RXERR),
	[DEC_IRQ_SCC1A_RXDMA]	= IO_IRQ_NR(IO_INR_SCC1A_RXDMA),
	[DEC_IRQ_SCC1A_TXERR]	= IO_IRQ_NR(IO_INR_SCC1A_TXERR),
	[DEC_IRQ_SCC1A_TXDMA]	= IO_IRQ_NR(IO_INR_SCC1A_TXDMA),
पूर्ण;

अटल पूर्णांक_ptr kn03_cpu_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN03_CPU_INR_BUS) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN03_CPU_INR_BUS) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN03_CPU_INR_RTC) पूर्ण,
		अणु .i = DEC_CPU_IRQ_NR(KN03_CPU_INR_RTC) पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_MASK(KN03_CPU_INR_CASCADE) पूर्ण,
		अणु .p = kn03_io_पूर्णांक पूर्ण पूर्ण,
	अणु अणु .i = DEC_CPU_IRQ_ALL पूर्ण,
		अणु .p = cpu_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक_ptr kn03_asic_mask_nr_tbl[][2] __initdata = अणु
	अणु अणु .i = IO_IRQ_DMA पूर्ण,
		अणु .p = asic_dma_पूर्णांक पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN03_IO_INR_SCC0) पूर्ण,
		अणु .i = IO_IRQ_NR(KN03_IO_INR_SCC0) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN03_IO_INR_SCC1) पूर्ण,
		अणु .i = IO_IRQ_NR(KN03_IO_INR_SCC1) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN03_IO_INR_ASC) पूर्ण,
		अणु .i = IO_IRQ_NR(KN03_IO_INR_ASC) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN03_IO_INR_LANCE) पूर्ण,
		अणु .i = IO_IRQ_NR(KN03_IO_INR_LANCE) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN03_IO_INR_TC2) पूर्ण,
		अणु .i = IO_IRQ_NR(KN03_IO_INR_TC2) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN03_IO_INR_TC1) पूर्ण,
		अणु .i = IO_IRQ_NR(KN03_IO_INR_TC1) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_MASK(KN03_IO_INR_TC0) पूर्ण,
		अणु .i = IO_IRQ_NR(KN03_IO_INR_TC0) पूर्ण पूर्ण,
	अणु अणु .i = IO_IRQ_ALL पूर्ण,
		अणु .p = asic_all_पूर्णांक पूर्ण पूर्ण,
पूर्ण;

अटल व्योम __init dec_init_kn03(व्योम)
अणु
	/* IRQ routing. */
	स_नकल(&dec_पूर्णांकerrupt, &kn03_पूर्णांकerrupt,
		माप(kn03_पूर्णांकerrupt));

	/* CPU IRQ priorities. */
	स_नकल(&cpu_mask_nr_tbl, &kn03_cpu_mask_nr_tbl,
		माप(kn03_cpu_mask_nr_tbl));

	/* I/O ASIC IRQ priorities. */
	स_नकल(&asic_mask_nr_tbl, &kn03_asic_mask_nr_tbl,
		माप(kn03_asic_mask_nr_tbl));

	mips_cpu_irq_init();
	init_ioasic_irqs(IO_IRQ_BASE);

पूर्ण				/* dec_init_kn03 */


व्योम __init arch_init_irq(व्योम)
अणु
	चयन (mips_machtype) अणु
	हाल MACH_DS23100:	/* DS2100/DS3100 Pmin/Pmax */
		dec_init_kn01();
		अवरोध;
	हाल MACH_DS5100:	/* DS5100 MIPSmate */
		dec_init_kn230();
		अवरोध;
	हाल MACH_DS5000_200:	/* DS5000/200 3max */
		dec_init_kn02();
		अवरोध;
	हाल MACH_DS5000_1XX:	/* DS5000/1xx 3min */
		dec_init_kn02ba();
		अवरोध;
	हाल MACH_DS5000_2X0:	/* DS5000/240 3max+ */
	हाल MACH_DS5900:	/* DS5900 bigmax */
		dec_init_kn03();
		अवरोध;
	हाल MACH_DS5000_XX:	/* Personal DS5000/xx */
		dec_init_kn02ca();
		अवरोध;
	हाल MACH_DS5800:	/* DS5800 Isis */
		panic("Don't know how to set this up!");
		अवरोध;
	हाल MACH_DS5400:	/* DS5400 MIPSfair */
		panic("Don't know how to set this up!");
		अवरोध;
	हाल MACH_DS5500:	/* DS5500 MIPSfair-2 */
		panic("Don't know how to set this up!");
		अवरोध;
	पूर्ण

	/* Free the FPU पूर्णांकerrupt अगर the exception is present. */
	अगर (!cpu_has_nofpuex) अणु
		cpu_fpu_mask = 0;
		dec_पूर्णांकerrupt[DEC_IRQ_FPU] = -1;
	पूर्ण
	/* Free the halt पूर्णांकerrupt unused on R4k प्रणालीs.  */
	अगर (current_cpu_type() == CPU_R4000SC ||
	    current_cpu_type() == CPU_R4400SC)
		dec_पूर्णांकerrupt[DEC_IRQ_HALT] = -1;

	/* Register board पूर्णांकerrupts: FPU and cascade. */
	अगर (dec_पूर्णांकerrupt[DEC_IRQ_FPU] >= 0 && cpu_has_fpu) अणु
		काष्ठा irq_desc *desc_fpu;
		पूर्णांक irq_fpu;

		irq_fpu = dec_पूर्णांकerrupt[DEC_IRQ_FPU];
		अगर (request_irq(irq_fpu, no_action, IRQF_NO_THREAD, "fpu",
				शून्य))
			pr_err("Failed to register fpu interrupt\n");
		desc_fpu = irq_to_desc(irq_fpu);
		fpu_kstat_irq = this_cpu_ptr(desc_fpu->kstat_irqs);
	पूर्ण
	अगर (dec_पूर्णांकerrupt[DEC_IRQ_CASCADE] >= 0) अणु
		अगर (request_irq(dec_पूर्णांकerrupt[DEC_IRQ_CASCADE], no_action,
				IRQF_NO_THREAD, "cascade", शून्य))
			pr_err("Failed to register cascade interrupt\n");
	पूर्ण
	/* Register the bus error पूर्णांकerrupt. */
	अगर (dec_पूर्णांकerrupt[DEC_IRQ_BUS] >= 0 && busirq_handler) अणु
		अगर (request_irq(dec_पूर्णांकerrupt[DEC_IRQ_BUS], busirq_handler,
				busirq_flags, "bus error", busirq_handler))
			pr_err("Failed to register bus error interrupt\n");
	पूर्ण
	/* Register the HALT पूर्णांकerrupt. */
	अगर (dec_पूर्णांकerrupt[DEC_IRQ_HALT] >= 0) अणु
		अगर (request_irq(dec_पूर्णांकerrupt[DEC_IRQ_HALT], dec_पूर्णांकr_halt,
				IRQF_NO_THREAD, "halt", शून्य))
			pr_err("Failed to register halt interrupt\n");
	पूर्ण
पूर्ण

यंत्रlinkage अचिन्हित पूर्णांक dec_irq_dispatch(अचिन्हित पूर्णांक irq)
अणु
	करो_IRQ(irq);
	वापस 0;
पूर्ण
