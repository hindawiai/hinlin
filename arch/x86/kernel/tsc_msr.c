<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TSC frequency क्रमागतeration via MSR
 *
 * Copyright (C) 2013, 2018 Intel Corporation
 * Author: Bin Gao <bin.gao@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/tsc.h>

#घोषणा MAX_NUM_FREQS	16 /* 4 bits to select the frequency */

/*
 * The frequency numbers in the SDM are e.g. 83.3 MHz, which करोes not contain a
 * lot of accuracy which leads to घड़ी drअगरt. As far as we know Bay Trail SoCs
 * use a 25 MHz crystal and Cherry Trail uses a 19.2 MHz crystal, the crystal
 * is the source clk क्रम a root PLL which outमाला_दो 1600 and 100 MHz. It is
 * unclear अगर the root PLL outमाला_दो are used directly by the CPU घड़ी PLL or
 * अगर there is another PLL in between.
 * This करोes not matter though, we can model the chain of PLLs as a single PLL
 * with a quotient equal to the quotients of all PLLs in the chain multiplied.
 * So we can create a simplअगरied model of the CPU घड़ी setup using a reference
 * घड़ी of 100 MHz plus a quotient which माला_लो us as बंद to the frequency
 * from the SDM as possible.
 * For the 83.3 MHz example from above this would give us 100 MHz * 5 / 6 =
 * 83 and 1/3 MHz, which matches exactly what has been measured on actual hw.
 */
#घोषणा TSC_REFERENCE_KHZ 100000

काष्ठा muद_भाग अणु
	u32 multiplier;
	u32 भागider;
पूर्ण;

/*
 * If MSR_PERF_STAT[31] is set, the maximum resolved bus ratio can be
 * पढ़ो in MSR_PLATFORM_ID[12:8], otherwise in MSR_PERF_STAT[44:40].
 * Unक्रमtunately some Intel Atom SoCs aren't quite compliant to this,
 * so we need manually dअगरferentiate SoC families. This is what the
 * field use_msr_plat करोes.
 */
काष्ठा freq_desc अणु
	bool use_msr_plat;
	काष्ठा muद_भाग muद_भाग[MAX_NUM_FREQS];
	/*
	 * Some CPU frequencies in the SDM करो not map to known PLL freqs, in
	 * that हाल the muद_भाग array is empty and the freqs array is used.
	 */
	u32 freqs[MAX_NUM_FREQS];
	u32 mask;
पूर्ण;

/*
 * Penwell and Clovertrail use spपढ़ो spectrum घड़ी,
 * so the freq number is not exactly the same as reported
 * by MSR based on SDM.
 */
अटल स्थिर काष्ठा freq_desc freq_desc_pnw = अणु
	.use_msr_plat = false,
	.freqs = अणु 0, 0, 0, 0, 0, 99840, 0, 83200 पूर्ण,
	.mask = 0x07,
पूर्ण;

अटल स्थिर काष्ठा freq_desc freq_desc_clv = अणु
	.use_msr_plat = false,
	.freqs = अणु 0, 133200, 0, 0, 0, 99840, 0, 83200 पूर्ण,
	.mask = 0x07,
पूर्ण;

/*
 * Bay Trail SDM MSR_FSB_FREQ frequencies simplअगरied PLL model:
 *  000:   100 *  5 /  6  =  83.3333 MHz
 *  001:   100 *  1 /  1  = 100.0000 MHz
 *  010:   100 *  4 /  3  = 133.3333 MHz
 *  011:   100 *  7 /  6  = 116.6667 MHz
 *  100:   100 *  4 /  5  =  80.0000 MHz
 */
अटल स्थिर काष्ठा freq_desc freq_desc_byt = अणु
	.use_msr_plat = true,
	.muद_भाग = अणु अणु 5, 6 पूर्ण, अणु 1, 1 पूर्ण, अणु 4, 3 पूर्ण, अणु 7, 6 पूर्ण,
		    अणु 4, 5 पूर्ण पूर्ण,
	.mask = 0x07,
पूर्ण;

/*
 * Cherry Trail SDM MSR_FSB_FREQ frequencies simplअगरied PLL model:
 * 0000:   100 *  5 /  6  =  83.3333 MHz
 * 0001:   100 *  1 /  1  = 100.0000 MHz
 * 0010:   100 *  4 /  3  = 133.3333 MHz
 * 0011:   100 *  7 /  6  = 116.6667 MHz
 * 0100:   100 *  4 /  5  =  80.0000 MHz
 * 0101:   100 * 14 / 15  =  93.3333 MHz
 * 0110:   100 *  9 / 10  =  90.0000 MHz
 * 0111:   100 *  8 /  9  =  88.8889 MHz
 * 1000:   100 *  7 /  8  =  87.5000 MHz
 */
अटल स्थिर काष्ठा freq_desc freq_desc_cht = अणु
	.use_msr_plat = true,
	.muद_भाग = अणु अणु 5, 6 पूर्ण, अणु  1,  1 पूर्ण, अणु 4,  3 पूर्ण, अणु 7, 6 पूर्ण,
		    अणु 4, 5 पूर्ण, अणु 14, 15 पूर्ण, अणु 9, 10 पूर्ण, अणु 8, 9 पूर्ण,
		    अणु 7, 8 पूर्ण पूर्ण,
	.mask = 0x0f,
पूर्ण;

/*
 * Merriefield SDM MSR_FSB_FREQ frequencies simplअगरied PLL model:
 * 0001:   100 *  1 /  1  = 100.0000 MHz
 * 0010:   100 *  4 /  3  = 133.3333 MHz
 */
अटल स्थिर काष्ठा freq_desc freq_desc_tng = अणु
	.use_msr_plat = true,
	.muद_भाग = अणु अणु 0, 0 पूर्ण, अणु 1, 1 पूर्ण, अणु 4, 3 पूर्ण पूर्ण,
	.mask = 0x07,
पूर्ण;

/*
 * Moorefield SDM MSR_FSB_FREQ frequencies simplअगरied PLL model:
 * 0000:   100 *  5 /  6  =  83.3333 MHz
 * 0001:   100 *  1 /  1  = 100.0000 MHz
 * 0010:   100 *  4 /  3  = 133.3333 MHz
 * 0011:   100 *  1 /  1  = 100.0000 MHz
 */
अटल स्थिर काष्ठा freq_desc freq_desc_ann = अणु
	.use_msr_plat = true,
	.muद_भाग = अणु अणु 5, 6 पूर्ण, अणु 1, 1 पूर्ण, अणु 4, 3 पूर्ण, अणु 1, 1 पूर्ण पूर्ण,
	.mask = 0x0f,
पूर्ण;

/*
 * 24 MHz crystal? : 24 * 13 / 4 = 78 MHz
 * Frequency step क्रम Lightning Mountain SoC is fixed to 78 MHz,
 * so all the frequency entries are 78000.
 */
अटल स्थिर काष्ठा freq_desc freq_desc_lgm = अणु
	.use_msr_plat = true,
	.freqs = अणु 78000, 78000, 78000, 78000, 78000, 78000, 78000, 78000,
		   78000, 78000, 78000, 78000, 78000, 78000, 78000, 78000 पूर्ण,
	.mask = 0x0f,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id tsc_msr_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SALTWELL_MID,	&freq_desc_pnw),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SALTWELL_TABLET,&freq_desc_clv),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT,	&freq_desc_byt),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT_MID,	&freq_desc_tng),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT,	&freq_desc_cht),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT_MID,	&freq_desc_ann),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT_NP,	&freq_desc_lgm),
	अणुपूर्ण
पूर्ण;

/*
 * MSR-based CPU/TSC frequency discovery क्रम certain CPUs.
 *
 * Set global "lapic_timer_period" to bus_घड़ी_cycles/jअगरfy
 * Return processor base frequency in KHz, or 0 on failure.
 */
अचिन्हित दीर्घ cpu_khz_from_msr(व्योम)
अणु
	u32 lo, hi, ratio, freq, tscref;
	स्थिर काष्ठा freq_desc *freq_desc;
	स्थिर काष्ठा x86_cpu_id *id;
	स्थिर काष्ठा muद_भाग *md;
	अचिन्हित दीर्घ res;
	पूर्णांक index;

	id = x86_match_cpu(tsc_msr_cpu_ids);
	अगर (!id)
		वापस 0;

	freq_desc = (काष्ठा freq_desc *)id->driver_data;
	अगर (freq_desc->use_msr_plat) अणु
		rdmsr(MSR_PLATFORM_INFO, lo, hi);
		ratio = (lo >> 8) & 0xff;
	पूर्ण अन्यथा अणु
		rdmsr(MSR_IA32_PERF_STATUS, lo, hi);
		ratio = (hi >> 8) & 0x1f;
	पूर्ण

	/* Get FSB FREQ ID */
	rdmsr(MSR_FSB_FREQ, lo, hi);
	index = lo & freq_desc->mask;
	md = &freq_desc->muद_भाग[index];

	/*
	 * Note this also catches हालs where the index poपूर्णांकs to an unpopulated
	 * part of muद_भाग, in that हाल the अन्यथा will set freq and res to 0.
	 */
	अगर (md->भागider) अणु
		tscref = TSC_REFERENCE_KHZ * md->multiplier;
		freq = DIV_ROUND_CLOSEST(tscref, md->भागider);
		/*
		 * Multiplying by ratio beक्रमe the भागision has better
		 * accuracy than just calculating freq * ratio.
		 */
		res = DIV_ROUND_CLOSEST(tscref * ratio, md->भागider);
	पूर्ण अन्यथा अणु
		freq = freq_desc->freqs[index];
		res = freq * ratio;
	पूर्ण

	अगर (freq == 0)
		pr_err("Error MSR_FSB_FREQ index %d is unknown\n", index);

#अगर_घोषित CONFIG_X86_LOCAL_APIC
	lapic_समयr_period = (freq * 1000) / HZ;
#पूर्ण_अगर

	/*
	 * TSC frequency determined by MSR is always considered "known"
	 * because it is reported by HW.
	 * Another fact is that on MSR capable platक्रमms, PIT/HPET is
	 * generally not available so calibration won't work at all.
	 */
	setup_क्रमce_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);

	/*
	 * Unक्रमtunately there is no way क्रम hardware to tell whether the
	 * TSC is reliable.  We were told by silicon design team that TSC
	 * on Atom SoCs are always "reliable". TSC is also the only
	 * reliable घड़ीsource on these SoCs (HPET is either not present
	 * or not functional) so mark TSC reliable which हटाओs the
	 * requirement क्रम a watchकरोg घड़ीsource.
	 */
	setup_क्रमce_cpu_cap(X86_FEATURE_TSC_RELIABLE);

	वापस res;
पूर्ण
