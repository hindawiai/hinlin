<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2020, Jordan Niethe, IBM Corporation.
 *
 * This file contains low level CPU setup functions.
 * Originally written in assembly by Benjamin Herrenschmidt & various other
 * authors.
 */

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/synch.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cpu_setup_घातer.h>

/* Disable CPU_FTR_HVMODE and वापस false अगर MSR:HV is not set */
अटल bool init_hvmode_206(काष्ठा cpu_spec *t)
अणु
	u64 msr;

	msr = mfmsr();
	अगर (msr & MSR_HV)
		वापस true;

	t->cpu_features &= ~(CPU_FTR_HVMODE | CPU_FTR_P9_TM_HV_ASSIST);
	वापस false;
पूर्ण

अटल व्योम init_LPCR_ISA300(u64 lpcr, u64 lpes)
अणु
	/* POWER9 has no VRMASD */
	lpcr |= (lpes << LPCR_LPES_SH) & LPCR_LPES;
	lpcr |= LPCR_PECE0|LPCR_PECE1|LPCR_PECE2;
	lpcr |= (4ull << LPCR_DPFD_SH) & LPCR_DPFD;
	lpcr &= ~LPCR_HDICE;	/* clear HDICE */
	lpcr |= (4ull << LPCR_VC_SH);
	mtspr(SPRN_LPCR, lpcr);
	isync();
पूर्ण

/*
 * Setup a sane LPCR:
 *   Called with initial LPCR and desired LPES 2-bit value
 *
 *   LPES = 0b01 (HSRR0/1 used क्रम 0x500)
 *   PECE = 0b111
 *   DPFD = 4
 *   HDICE = 0
 *   VC = 0b100 (VPM0=1, VPM1=0, ISL=0)
 *   VRMASD = 0b10000 (L=1, LP=00)
 *
 * Other bits untouched क्रम now
 */
अटल व्योम init_LPCR_ISA206(u64 lpcr, u64 lpes)
अणु
	lpcr |= (0x10ull << LPCR_VRMASD_SH) & LPCR_VRMASD;
	init_LPCR_ISA300(lpcr, lpes);
पूर्ण

अटल व्योम init_FSCR(व्योम)
अणु
	u64 fscr;

	fscr = mfspr(SPRN_FSCR);
	fscr |= FSCR_TAR|FSCR_EBB;
	mtspr(SPRN_FSCR, fscr);
पूर्ण

अटल व्योम init_FSCR_घातer9(व्योम)
अणु
	u64 fscr;

	fscr = mfspr(SPRN_FSCR);
	fscr |= FSCR_SCV;
	mtspr(SPRN_FSCR, fscr);
	init_FSCR();
पूर्ण

अटल व्योम init_FSCR_घातer10(व्योम)
अणु
	u64 fscr;

	fscr = mfspr(SPRN_FSCR);
	fscr |= FSCR_PREFIX;
	mtspr(SPRN_FSCR, fscr);
	init_FSCR_घातer9();
पूर्ण

अटल व्योम init_HFSCR(व्योम)
अणु
	u64 hfscr;

	hfscr = mfspr(SPRN_HFSCR);
	hfscr |= HFSCR_TAR|HFSCR_TM|HFSCR_BHRB|HFSCR_PM|HFSCR_DSCR|\
		 HFSCR_VECVSX|HFSCR_FP|HFSCR_EBB|HFSCR_MSGP;
	mtspr(SPRN_HFSCR, hfscr);
पूर्ण

अटल व्योम init_PMU_HV(व्योम)
अणु
	mtspr(SPRN_MMCRC, 0);
पूर्ण

अटल व्योम init_PMU_HV_ISA207(व्योम)
अणु
	mtspr(SPRN_MMCRH, 0);
पूर्ण

अटल व्योम init_PMU(व्योम)
अणु
	mtspr(SPRN_MMCRA, 0);
	mtspr(SPRN_MMCR0, 0);
	mtspr(SPRN_MMCR1, 0);
	mtspr(SPRN_MMCR2, 0);
पूर्ण

अटल व्योम init_PMU_ISA207(व्योम)
अणु
	mtspr(SPRN_MMCRS, 0);
पूर्ण

अटल व्योम init_PMU_ISA31(व्योम)
अणु
	mtspr(SPRN_MMCR3, 0);
	mtspr(SPRN_MMCRA, MMCRA_BHRB_DISABLE);
	mtspr(SPRN_MMCR0, MMCR0_PMCCEXT);
पूर्ण

/*
 * Note that we can be called twice of pseuकरो-PVRs.
 * The parameter offset is not used.
 */

व्योम __setup_cpu_घातer7(अचिन्हित दीर्घ offset, काष्ठा cpu_spec *t)
अणु
	अगर (!init_hvmode_206(t))
		वापस;

	mtspr(SPRN_LPID, 0);
	mtspr(SPRN_PCR, PCR_MASK);
	init_LPCR_ISA206(mfspr(SPRN_LPCR), LPCR_LPES1 >> LPCR_LPES_SH);
पूर्ण

व्योम __restore_cpu_घातer7(व्योम)
अणु
	u64 msr;

	msr = mfmsr();
	अगर (!(msr & MSR_HV))
		वापस;

	mtspr(SPRN_LPID, 0);
	mtspr(SPRN_PCR, PCR_MASK);
	init_LPCR_ISA206(mfspr(SPRN_LPCR), LPCR_LPES1 >> LPCR_LPES_SH);
पूर्ण

व्योम __setup_cpu_घातer8(अचिन्हित दीर्घ offset, काष्ठा cpu_spec *t)
अणु
	init_FSCR();
	init_PMU();
	init_PMU_ISA207();

	अगर (!init_hvmode_206(t))
		वापस;

	mtspr(SPRN_LPID, 0);
	mtspr(SPRN_PCR, PCR_MASK);
	init_LPCR_ISA206(mfspr(SPRN_LPCR) | LPCR_PECEDH, 0); /* LPES = 0 */
	init_HFSCR();
	init_PMU_HV();
	init_PMU_HV_ISA207();
पूर्ण

व्योम __restore_cpu_घातer8(व्योम)
अणु
	u64 msr;

	init_FSCR();
	init_PMU();
	init_PMU_ISA207();

	msr = mfmsr();
	अगर (!(msr & MSR_HV))
		वापस;

	mtspr(SPRN_LPID, 0);
	mtspr(SPRN_PCR, PCR_MASK);
	init_LPCR_ISA206(mfspr(SPRN_LPCR) | LPCR_PECEDH, 0); /* LPES = 0 */
	init_HFSCR();
	init_PMU_HV();
	init_PMU_HV_ISA207();
पूर्ण

व्योम __setup_cpu_घातer9(अचिन्हित दीर्घ offset, काष्ठा cpu_spec *t)
अणु
	init_FSCR_घातer9();
	init_PMU();

	अगर (!init_hvmode_206(t))
		वापस;

	mtspr(SPRN_PSSCR, 0);
	mtspr(SPRN_LPID, 0);
	mtspr(SPRN_PID, 0);
	mtspr(SPRN_PCR, PCR_MASK);
	init_LPCR_ISA300((mfspr(SPRN_LPCR) | LPCR_PECEDH | LPCR_PECE_HVEE |\
			 LPCR_HVICE | LPCR_HEIC) & ~(LPCR_UPRT | LPCR_HR), 0);
	init_HFSCR();
	init_PMU_HV();
पूर्ण

व्योम __restore_cpu_घातer9(व्योम)
अणु
	u64 msr;

	init_FSCR_घातer9();
	init_PMU();

	msr = mfmsr();
	अगर (!(msr & MSR_HV))
		वापस;

	mtspr(SPRN_PSSCR, 0);
	mtspr(SPRN_LPID, 0);
	mtspr(SPRN_PID, 0);
	mtspr(SPRN_PCR, PCR_MASK);
	init_LPCR_ISA300((mfspr(SPRN_LPCR) | LPCR_PECEDH | LPCR_PECE_HVEE |\
			 LPCR_HVICE | LPCR_HEIC) & ~(LPCR_UPRT | LPCR_HR), 0);
	init_HFSCR();
	init_PMU_HV();
पूर्ण

व्योम __setup_cpu_घातer10(अचिन्हित दीर्घ offset, काष्ठा cpu_spec *t)
अणु
	init_FSCR_घातer10();
	init_PMU();
	init_PMU_ISA31();

	अगर (!init_hvmode_206(t))
		वापस;

	mtspr(SPRN_PSSCR, 0);
	mtspr(SPRN_LPID, 0);
	mtspr(SPRN_PID, 0);
	mtspr(SPRN_PCR, PCR_MASK);
	init_LPCR_ISA300((mfspr(SPRN_LPCR) | LPCR_PECEDH | LPCR_PECE_HVEE |\
			 LPCR_HVICE | LPCR_HEIC) & ~(LPCR_UPRT | LPCR_HR), 0);
	init_HFSCR();
	init_PMU_HV();
पूर्ण

व्योम __restore_cpu_घातer10(व्योम)
अणु
	u64 msr;

	init_FSCR_घातer10();
	init_PMU();
	init_PMU_ISA31();

	msr = mfmsr();
	अगर (!(msr & MSR_HV))
		वापस;

	mtspr(SPRN_PSSCR, 0);
	mtspr(SPRN_LPID, 0);
	mtspr(SPRN_PID, 0);
	mtspr(SPRN_PCR, PCR_MASK);
	init_LPCR_ISA300((mfspr(SPRN_LPCR) | LPCR_PECEDH | LPCR_PECE_HVEE |\
			 LPCR_HVICE | LPCR_HEIC) & ~(LPCR_UPRT | LPCR_HR), 0);
	init_HFSCR();
	init_PMU_HV();
पूर्ण
