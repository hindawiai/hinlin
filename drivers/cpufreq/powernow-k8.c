<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *   (c) 2003-2012 Advanced Micro Devices, Inc.
 *
 *  Maपूर्णांकainer:
 *  Andreas Herrmann <herrmann.der.user@googlemail.com>
 *
 *  Based on the घातernow-k7.c module written by Dave Jones.
 *  (C) 2003 Dave Jones on behalf of SuSE Lअसल
 *  (C) 2004 Dominik Broकरोwski <linux@broकरो.de>
 *  (C) 2004 Pavel Machek <pavel@ucw.cz>
 *  Based upon datasheets & sample CPUs kindly provided by AMD.
 *
 *  Valuable input gratefully received from Dave Jones, Pavel Machek,
 *  Dominik Broकरोwski, Jacob Shin, and others.
 *  Originally developed by Paul Devriendt.
 *
 *  Processor inक्रमmation obtained from Chapter 9 (Power and Thermal
 *  Management) of the "BIOS and Kernel Developer's Guide (BKDG) क्रम
 *  the AMD Athlon 64 and AMD Opteron Processors" and section "2.x
 *  Power Management" in BKDGs क्रम newer AMD CPU families.
 *
 *  Tables क्रम specअगरic CPUs can be inferred from AMD's processor
 *  घातer and thermal data sheets, (e.g. 30417.pdf, 30430.pdf, 43375.pdf)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/cpumask.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>

#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/cpu_device_id.h>

#समावेश <linux/acpi.h>
#समावेश <linux/mutex.h>
#समावेश <acpi/processor.h>

#घोषणा VERSION "version 2.20.00"
#समावेश "powernow-k8.h"

/* serialize freq changes  */
अटल DEFINE_MUTEX(fidvid_mutex);

अटल DEFINE_PER_CPU(काष्ठा घातernow_k8_data *, घातernow_data);

अटल काष्ठा cpufreq_driver cpufreq_amd64_driver;

/* Return a frequency in MHz, given an input fid */
अटल u32 find_freq_from_fid(u32 fid)
अणु
	वापस 800 + (fid * 100);
पूर्ण

/* Return a frequency in KHz, given an input fid */
अटल u32 find_khz_freq_from_fid(u32 fid)
अणु
	वापस 1000 * find_freq_from_fid(fid);
पूर्ण

/* Return the vco fid क्रम an input fid
 *
 * Each "low" fid has corresponding "high" fid, and you can get to "low" fids
 * only from corresponding high fids. This वापसs "high" fid corresponding to
 * "low" one.
 */
अटल u32 convert_fid_to_vco_fid(u32 fid)
अणु
	अगर (fid < HI_FID_TABLE_BOTTOM)
		वापस 8 + (2 * fid);
	अन्यथा
		वापस fid;
पूर्ण

/*
 * Return 1 अगर the pending bit is set. Unless we just inकाष्ठाed the processor
 * to transition to a new state, seeing this bit set is really bad news.
 */
अटल पूर्णांक pending_bit_stuck(व्योम)
अणु
	u32 lo, hi __always_unused;

	rdmsr(MSR_FIDVID_STATUS, lo, hi);
	वापस lo & MSR_S_LO_CHANGE_PENDING ? 1 : 0;
पूर्ण

/*
 * Update the global current fid / vid values from the status msr.
 * Returns 1 on error.
 */
अटल पूर्णांक query_current_values_with_pending_रुको(काष्ठा घातernow_k8_data *data)
अणु
	u32 lo, hi;
	u32 i = 0;

	करो अणु
		अगर (i++ > 10000) अणु
			pr_debug("detected change pending stuck\n");
			वापस 1;
		पूर्ण
		rdmsr(MSR_FIDVID_STATUS, lo, hi);
	पूर्ण जबतक (lo & MSR_S_LO_CHANGE_PENDING);

	data->currvid = hi & MSR_S_HI_CURRENT_VID;
	data->currfid = lo & MSR_S_LO_CURRENT_FID;

	वापस 0;
पूर्ण

/* the isochronous relief समय */
अटल व्योम count_off_irt(काष्ठा घातernow_k8_data *data)
अणु
	udelay((1 << data->irt) * 10);
पूर्ण

/* the voltage stabilization समय */
अटल व्योम count_off_vst(काष्ठा घातernow_k8_data *data)
अणु
	udelay(data->vstable * VST_UNITS_20US);
पूर्ण

/* need to init the control msr to a safe value (क्रम each cpu) */
अटल व्योम fidvid_msr_init(व्योम)
अणु
	u32 lo, hi;
	u8 fid, vid;

	rdmsr(MSR_FIDVID_STATUS, lo, hi);
	vid = hi & MSR_S_HI_CURRENT_VID;
	fid = lo & MSR_S_LO_CURRENT_FID;
	lo = fid | (vid << MSR_C_LO_VID_SHIFT);
	hi = MSR_C_HI_STP_GNT_BENIGN;
	pr_debug("cpu%d, init lo 0x%x, hi 0x%x\n", smp_processor_id(), lo, hi);
	wrmsr(MSR_FIDVID_CTL, lo, hi);
पूर्ण

/* ग_लिखो the new fid value aदीर्घ with the other control fields to the msr */
अटल पूर्णांक ग_लिखो_new_fid(काष्ठा घातernow_k8_data *data, u32 fid)
अणु
	u32 lo;
	u32 savevid = data->currvid;
	u32 i = 0;

	अगर ((fid & INVALID_FID_MASK) || (data->currvid & INVALID_VID_MASK)) अणु
		pr_err("internal error - overflow on fid write\n");
		वापस 1;
	पूर्ण

	lo = fid;
	lo |= (data->currvid << MSR_C_LO_VID_SHIFT);
	lo |= MSR_C_LO_INIT_FID_VID;

	pr_debug("writing fid 0x%x, lo 0x%x, hi 0x%x\n",
		fid, lo, data->plllock * PLL_LOCK_CONVERSION);

	करो अणु
		wrmsr(MSR_FIDVID_CTL, lo, data->plllock * PLL_LOCK_CONVERSION);
		अगर (i++ > 100) अणु
			pr_err("Hardware error - pending bit very stuck - no further pstate changes possible\n");
			वापस 1;
		पूर्ण
	पूर्ण जबतक (query_current_values_with_pending_रुको(data));

	count_off_irt(data);

	अगर (savevid != data->currvid) अणु
		pr_err("vid change on fid trans, old 0x%x, new 0x%x\n",
		       savevid, data->currvid);
		वापस 1;
	पूर्ण

	अगर (fid != data->currfid) अणु
		pr_err("fid trans failed, fid 0x%x, curr 0x%x\n", fid,
			data->currfid);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* Write a new vid to the hardware */
अटल पूर्णांक ग_लिखो_new_vid(काष्ठा घातernow_k8_data *data, u32 vid)
अणु
	u32 lo;
	u32 savefid = data->currfid;
	पूर्णांक i = 0;

	अगर ((data->currfid & INVALID_FID_MASK) || (vid & INVALID_VID_MASK)) अणु
		pr_err("internal error - overflow on vid write\n");
		वापस 1;
	पूर्ण

	lo = data->currfid;
	lo |= (vid << MSR_C_LO_VID_SHIFT);
	lo |= MSR_C_LO_INIT_FID_VID;

	pr_debug("writing vid 0x%x, lo 0x%x, hi 0x%x\n",
		vid, lo, STOP_GRANT_5NS);

	करो अणु
		wrmsr(MSR_FIDVID_CTL, lo, STOP_GRANT_5NS);
		अगर (i++ > 100) अणु
			pr_err("internal error - pending bit very stuck - no further pstate changes possible\n");
			वापस 1;
		पूर्ण
	पूर्ण जबतक (query_current_values_with_pending_रुको(data));

	अगर (savefid != data->currfid) अणु
		pr_err("fid changed on vid trans, old 0x%x new 0x%x\n",
			savefid, data->currfid);
		वापस 1;
	पूर्ण

	अगर (vid != data->currvid) अणु
		pr_err("vid trans failed, vid 0x%x, curr 0x%x\n",
				vid, data->currvid);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Reduce the vid by the max of step or reqvid.
 * Decreasing vid codes represent increasing voltages:
 * vid of 0 is 1.550V, vid of 0x1e is 0.800V, vid of VID_OFF is off.
 */
अटल पूर्णांक decrease_vid_code_by_step(काष्ठा घातernow_k8_data *data,
		u32 reqvid, u32 step)
अणु
	अगर ((data->currvid - reqvid) > step)
		reqvid = data->currvid - step;

	अगर (ग_लिखो_new_vid(data, reqvid))
		वापस 1;

	count_off_vst(data);

	वापस 0;
पूर्ण

/* Change Opteron/Athlon64 fid and vid, by the 3 phases. */
अटल पूर्णांक transition_fid_vid(काष्ठा घातernow_k8_data *data,
		u32 reqfid, u32 reqvid)
अणु
	अगर (core_voltage_pre_transition(data, reqvid, reqfid))
		वापस 1;

	अगर (core_frequency_transition(data, reqfid))
		वापस 1;

	अगर (core_voltage_post_transition(data, reqvid))
		वापस 1;

	अगर (query_current_values_with_pending_रुको(data))
		वापस 1;

	अगर ((reqfid != data->currfid) || (reqvid != data->currvid)) अणु
		pr_err("failed (cpu%d): req 0x%x 0x%x, curr 0x%x 0x%x\n",
				smp_processor_id(),
				reqfid, reqvid, data->currfid, data->currvid);
		वापस 1;
	पूर्ण

	pr_debug("transitioned (cpu%d): new fid 0x%x, vid 0x%x\n",
		smp_processor_id(), data->currfid, data->currvid);

	वापस 0;
पूर्ण

/* Phase 1 - core voltage transition ... setup voltage */
अटल पूर्णांक core_voltage_pre_transition(काष्ठा घातernow_k8_data *data,
		u32 reqvid, u32 reqfid)
अणु
	u32 rvosteps = data->rvo;
	u32 savefid = data->currfid;
	u32 maxvid, lo __always_unused, rvomult = 1;

	pr_debug("ph1 (cpu%d): start, currfid 0x%x, currvid 0x%x, reqvid 0x%x, rvo 0x%x\n",
		smp_processor_id(),
		data->currfid, data->currvid, reqvid, data->rvo);

	अगर ((savefid < LO_FID_TABLE_TOP) && (reqfid < LO_FID_TABLE_TOP))
		rvomult = 2;
	rvosteps *= rvomult;
	rdmsr(MSR_FIDVID_STATUS, lo, maxvid);
	maxvid = 0x1f & (maxvid >> 16);
	pr_debug("ph1 maxvid=0x%x\n", maxvid);
	अगर (reqvid < maxvid) /* lower numbers are higher voltages */
		reqvid = maxvid;

	जबतक (data->currvid > reqvid) अणु
		pr_debug("ph1: curr 0x%x, req vid 0x%x\n",
			data->currvid, reqvid);
		अगर (decrease_vid_code_by_step(data, reqvid, data->vidmvs))
			वापस 1;
	पूर्ण

	जबतक ((rvosteps > 0) &&
			((rvomult * data->rvo + data->currvid) > reqvid)) अणु
		अगर (data->currvid == maxvid) अणु
			rvosteps = 0;
		पूर्ण अन्यथा अणु
			pr_debug("ph1: changing vid for rvo, req 0x%x\n",
				data->currvid - 1);
			अगर (decrease_vid_code_by_step(data, data->currvid-1, 1))
				वापस 1;
			rvosteps--;
		पूर्ण
	पूर्ण

	अगर (query_current_values_with_pending_रुको(data))
		वापस 1;

	अगर (savefid != data->currfid) अणु
		pr_err("ph1 err, currfid changed 0x%x\n", data->currfid);
		वापस 1;
	पूर्ण

	pr_debug("ph1 complete, currfid 0x%x, currvid 0x%x\n",
		data->currfid, data->currvid);

	वापस 0;
पूर्ण

/* Phase 2 - core frequency transition */
अटल पूर्णांक core_frequency_transition(काष्ठा घातernow_k8_data *data, u32 reqfid)
अणु
	u32 vcoreqfid, vcocurrfid, vcofiddअगरf;
	u32 fid_पूर्णांकerval, savevid = data->currvid;

	अगर (data->currfid == reqfid) अणु
		pr_err("ph2 null fid transition 0x%x\n", data->currfid);
		वापस 0;
	पूर्ण

	pr_debug("ph2 (cpu%d): starting, currfid 0x%x, currvid 0x%x, reqfid 0x%x\n",
		smp_processor_id(),
		data->currfid, data->currvid, reqfid);

	vcoreqfid = convert_fid_to_vco_fid(reqfid);
	vcocurrfid = convert_fid_to_vco_fid(data->currfid);
	vcofiddअगरf = vcocurrfid > vcoreqfid ? vcocurrfid - vcoreqfid
	    : vcoreqfid - vcocurrfid;

	अगर ((reqfid <= LO_FID_TABLE_TOP) && (data->currfid <= LO_FID_TABLE_TOP))
		vcofiddअगरf = 0;

	जबतक (vcofiddअगरf > 2) अणु
		(data->currfid & 1) ? (fid_पूर्णांकerval = 1) : (fid_पूर्णांकerval = 2);

		अगर (reqfid > data->currfid) अणु
			अगर (data->currfid > LO_FID_TABLE_TOP) अणु
				अगर (ग_लिखो_new_fid(data,
						data->currfid + fid_पूर्णांकerval))
					वापस 1;
			पूर्ण अन्यथा अणु
				अगर (ग_लिखो_new_fid
				    (data,
				     2 + convert_fid_to_vco_fid(data->currfid)))
					वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ग_लिखो_new_fid(data, data->currfid - fid_पूर्णांकerval))
				वापस 1;
		पूर्ण

		vcocurrfid = convert_fid_to_vco_fid(data->currfid);
		vcofiddअगरf = vcocurrfid > vcoreqfid ? vcocurrfid - vcoreqfid
		    : vcoreqfid - vcocurrfid;
	पूर्ण

	अगर (ग_लिखो_new_fid(data, reqfid))
		वापस 1;

	अगर (query_current_values_with_pending_रुको(data))
		वापस 1;

	अगर (data->currfid != reqfid) अणु
		pr_err("ph2: mismatch, failed fid transition, curr 0x%x, req 0x%x\n",
			data->currfid, reqfid);
		वापस 1;
	पूर्ण

	अगर (savevid != data->currvid) अणु
		pr_err("ph2: vid changed, save 0x%x, curr 0x%x\n",
			savevid, data->currvid);
		वापस 1;
	पूर्ण

	pr_debug("ph2 complete, currfid 0x%x, currvid 0x%x\n",
		data->currfid, data->currvid);

	वापस 0;
पूर्ण

/* Phase 3 - core voltage transition flow ... jump to the final vid. */
अटल पूर्णांक core_voltage_post_transition(काष्ठा घातernow_k8_data *data,
		u32 reqvid)
अणु
	u32 savefid = data->currfid;
	u32 savereqvid = reqvid;

	pr_debug("ph3 (cpu%d): starting, currfid 0x%x, currvid 0x%x\n",
		smp_processor_id(),
		data->currfid, data->currvid);

	अगर (reqvid != data->currvid) अणु
		अगर (ग_लिखो_new_vid(data, reqvid))
			वापस 1;

		अगर (savefid != data->currfid) अणु
			pr_err("ph3: bad fid change, save 0x%x, curr 0x%x\n",
				savefid, data->currfid);
			वापस 1;
		पूर्ण

		अगर (data->currvid != reqvid) अणु
			pr_err("ph3: failed vid transition\n, req 0x%x, curr 0x%x",
				reqvid, data->currvid);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (query_current_values_with_pending_रुको(data))
		वापस 1;

	अगर (savereqvid != data->currvid) अणु
		pr_debug("ph3 failed, currvid 0x%x\n", data->currvid);
		वापस 1;
	पूर्ण

	अगर (savefid != data->currfid) अणु
		pr_debug("ph3 failed, currfid changed 0x%x\n",
			data->currfid);
		वापस 1;
	पूर्ण

	pr_debug("ph3 complete, currfid 0x%x, currvid 0x%x\n",
		data->currfid, data->currvid);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id घातernow_k8_ids[] = अणु
	/* IO based frequency चयनing */
	X86_MATCH_VENDOR_FAM(AMD, 0xf, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, घातernow_k8_ids);

अटल व्योम check_supported_cpu(व्योम *_rc)
अणु
	u32 eax, ebx, ecx, edx;
	पूर्णांक *rc = _rc;

	*rc = -ENODEV;

	eax = cpuid_eax(CPUID_PROCESSOR_SIGNATURE);

	अगर ((eax & CPUID_XFAM) == CPUID_XFAM_K8) अणु
		अगर (((eax & CPUID_USE_XFAM_XMOD) != CPUID_USE_XFAM_XMOD) ||
		    ((eax & CPUID_XMOD) > CPUID_XMOD_REV_MASK)) अणु
			pr_info("Processor cpuid %x not supported\n", eax);
			वापस;
		पूर्ण

		eax = cpuid_eax(CPUID_GET_MAX_CAPABILITIES);
		अगर (eax < CPUID_FREQ_VOLT_CAPABILITIES) अणु
			pr_info("No frequency change capabilities detected\n");
			वापस;
		पूर्ण

		cpuid(CPUID_FREQ_VOLT_CAPABILITIES, &eax, &ebx, &ecx, &edx);
		अगर ((edx & P_STATE_TRANSITION_CAPABLE)
			!= P_STATE_TRANSITION_CAPABLE) अणु
			pr_info("Power state transitions not supported\n");
			वापस;
		पूर्ण
		*rc = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक check_pst_table(काष्ठा घातernow_k8_data *data, काष्ठा pst_s *pst,
		u8 maxvid)
अणु
	अचिन्हित पूर्णांक j;
	u8 lastfid = 0xff;

	क्रम (j = 0; j < data->numps; j++) अणु
		अगर (pst[j].vid > LEAST_VID) अणु
			pr_err(FW_BUG "vid %d invalid : 0x%x\n", j,
				pst[j].vid);
			वापस -EINVAL;
		पूर्ण
		अगर (pst[j].vid < data->rvo) अणु
			/* vid + rvo >= 0 */
			pr_err(FW_BUG "0 vid exceeded with pstate %d\n", j);
			वापस -ENODEV;
		पूर्ण
		अगर (pst[j].vid < maxvid + data->rvo) अणु
			/* vid + rvo >= maxvid */
			pr_err(FW_BUG "maxvid exceeded with pstate %d\n", j);
			वापस -ENODEV;
		पूर्ण
		अगर (pst[j].fid > MAX_FID) अणु
			pr_err(FW_BUG "maxfid exceeded with pstate %d\n", j);
			वापस -ENODEV;
		पूर्ण
		अगर (j && (pst[j].fid < HI_FID_TABLE_BOTTOM)) अणु
			/* Only first fid is allowed to be in "low" range */
			pr_err(FW_BUG "two low fids - %d : 0x%x\n", j,
				pst[j].fid);
			वापस -EINVAL;
		पूर्ण
		अगर (pst[j].fid < lastfid)
			lastfid = pst[j].fid;
	पूर्ण
	अगर (lastfid & 1) अणु
		pr_err(FW_BUG "lastfid invalid\n");
		वापस -EINVAL;
	पूर्ण
	अगर (lastfid > LO_FID_TABLE_TOP)
		pr_info(FW_BUG "first fid not from lo freq table\n");

	वापस 0;
पूर्ण

अटल व्योम invalidate_entry(काष्ठा cpufreq_frequency_table *घातernow_table,
		अचिन्हित पूर्णांक entry)
अणु
	घातernow_table[entry].frequency = CPUFREQ_ENTRY_INVALID;
पूर्ण

अटल व्योम prपूर्णांक_basics(काष्ठा घातernow_k8_data *data)
अणु
	पूर्णांक j;
	क्रम (j = 0; j < data->numps; j++) अणु
		अगर (data->घातernow_table[j].frequency !=
				CPUFREQ_ENTRY_INVALID) अणु
			pr_info("fid 0x%x (%d MHz), vid 0x%x\n",
				data->घातernow_table[j].driver_data & 0xff,
				data->घातernow_table[j].frequency/1000,
				data->घातernow_table[j].driver_data >> 8);
		पूर्ण
	पूर्ण
	अगर (data->batps)
		pr_info("Only %d pstates on battery\n", data->batps);
पूर्ण

अटल पूर्णांक fill_घातernow_table(काष्ठा घातernow_k8_data *data,
		काष्ठा pst_s *pst, u8 maxvid)
अणु
	काष्ठा cpufreq_frequency_table *घातernow_table;
	अचिन्हित पूर्णांक j;

	अगर (data->batps) अणु
		/* use ACPI support to get full speed on मुख्यs घातer */
		pr_warn("Only %d pstates usable (use ACPI driver for full range\n",
			data->batps);
		data->numps = data->batps;
	पूर्ण

	क्रम (j = 1; j < data->numps; j++) अणु
		अगर (pst[j-1].fid >= pst[j].fid) अणु
			pr_err("PST out of sequence\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (data->numps < 2) अणु
		pr_err("no p states to transition\n");
		वापस -ENODEV;
	पूर्ण

	अगर (check_pst_table(data, pst, maxvid))
		वापस -EINVAL;

	घातernow_table = kzalloc((माप(*घातernow_table)
		* (data->numps + 1)), GFP_KERNEL);
	अगर (!घातernow_table)
		वापस -ENOMEM;

	क्रम (j = 0; j < data->numps; j++) अणु
		पूर्णांक freq;
		घातernow_table[j].driver_data = pst[j].fid; /* lower 8 bits */
		घातernow_table[j].driver_data |= (pst[j].vid << 8); /* upper 8 bits */
		freq = find_khz_freq_from_fid(pst[j].fid);
		घातernow_table[j].frequency = freq;
	पूर्ण
	घातernow_table[data->numps].frequency = CPUFREQ_TABLE_END;
	घातernow_table[data->numps].driver_data = 0;

	अगर (query_current_values_with_pending_रुको(data)) अणु
		kमुक्त(घातernow_table);
		वापस -EIO;
	पूर्ण

	pr_debug("cfid 0x%x, cvid 0x%x\n", data->currfid, data->currvid);
	data->घातernow_table = घातernow_table;
	अगर (cpumask_first(topology_core_cpumask(data->cpu)) == data->cpu)
		prपूर्णांक_basics(data);

	क्रम (j = 0; j < data->numps; j++)
		अगर ((pst[j].fid == data->currfid) &&
		    (pst[j].vid == data->currvid))
			वापस 0;

	pr_debug("currfid/vid do not match PST, ignoring\n");
	वापस 0;
पूर्ण

/* Find and validate the PSB/PST table in BIOS. */
अटल पूर्णांक find_psb_table(काष्ठा घातernow_k8_data *data)
अणु
	काष्ठा psb_s *psb;
	अचिन्हित पूर्णांक i;
	u32 mvs;
	u8 maxvid;
	u32 cpst = 0;
	u32 thiscpuid;

	क्रम (i = 0xc0000; i < 0xffff0; i += 0x10) अणु
		/* Scan BIOS looking क्रम the signature. */
		/* It can not be at ffff0 - it is too big. */

		psb = phys_to_virt(i);
		अगर (स_भेद(psb, PSB_ID_STRING, PSB_ID_STRING_LEN) != 0)
			जारी;

		pr_debug("found PSB header at 0x%p\n", psb);

		pr_debug("table vers: 0x%x\n", psb->tableversion);
		अगर (psb->tableversion != PSB_VERSION_1_4) अणु
			pr_err(FW_BUG "PSB table is not v1.4\n");
			वापस -ENODEV;
		पूर्ण

		pr_debug("flags: 0x%x\n", psb->flags1);
		अगर (psb->flags1) अणु
			pr_err(FW_BUG "unknown flags\n");
			वापस -ENODEV;
		पूर्ण

		data->vstable = psb->vstable;
		pr_debug("voltage stabilization time: %d(*20us)\n",
				data->vstable);

		pr_debug("flags2: 0x%x\n", psb->flags2);
		data->rvo = psb->flags2 & 3;
		data->irt = ((psb->flags2) >> 2) & 3;
		mvs = ((psb->flags2) >> 4) & 3;
		data->vidmvs = 1 << mvs;
		data->batps = ((psb->flags2) >> 6) & 3;

		pr_debug("ramp voltage offset: %d\n", data->rvo);
		pr_debug("isochronous relief time: %d\n", data->irt);
		pr_debug("maximum voltage step: %d - 0x%x\n", mvs, data->vidmvs);

		pr_debug("numpst: 0x%x\n", psb->num_tables);
		cpst = psb->num_tables;
		अगर ((psb->cpuid == 0x00000fc0) ||
		    (psb->cpuid == 0x00000fe0)) अणु
			thiscpuid = cpuid_eax(CPUID_PROCESSOR_SIGNATURE);
			अगर ((thiscpuid == 0x00000fc0) ||
			    (thiscpuid == 0x00000fe0))
				cpst = 1;
		पूर्ण
		अगर (cpst != 1) अणु
			pr_err(FW_BUG "numpst must be 1\n");
			वापस -ENODEV;
		पूर्ण

		data->plllock = psb->plllockसमय;
		pr_debug("plllocktime: 0x%x (units 1us)\n", psb->plllockसमय);
		pr_debug("maxfid: 0x%x\n", psb->maxfid);
		pr_debug("maxvid: 0x%x\n", psb->maxvid);
		maxvid = psb->maxvid;

		data->numps = psb->numps;
		pr_debug("numpstates: 0x%x\n", data->numps);
		वापस fill_घातernow_table(data,
				(काष्ठा pst_s *)(psb+1), maxvid);
	पूर्ण
	/*
	 * If you see this message, complain to BIOS manufacturer. If
	 * he tells you "we do not support Linux" or some similar
	 * nonsense, remember that Winकरोws 2000 uses the same legacy
	 * mechanism that the old Linux PSB driver uses. Tell them it
	 * is broken with Winकरोws 2000.
	 *
	 * The reference to the AMD करोcumentation is chapter 9 in the
	 * BIOS and Kernel Developer's Guide, which is available on
	 * www.amd.com
	 */
	pr_err(FW_BUG "No PSB or ACPI _PSS objects\n");
	pr_err("Make sure that your BIOS is up to date and Cool'N'Quiet support is enabled in BIOS setup\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम घातernow_k8_acpi_pst_values(काष्ठा घातernow_k8_data *data,
		अचिन्हित पूर्णांक index)
अणु
	u64 control;

	अगर (!data->acpi_data.state_count)
		वापस;

	control = data->acpi_data.states[index].control;
	data->irt = (control >> IRT_SHIFT) & IRT_MASK;
	data->rvo = (control >> RVO_SHIFT) & RVO_MASK;
	data->exttype = (control >> EXT_TYPE_SHIFT) & EXT_TYPE_MASK;
	data->plllock = (control >> PLL_L_SHIFT) & PLL_L_MASK;
	data->vidmvs = 1 << ((control >> MVS_SHIFT) & MVS_MASK);
	data->vstable = (control >> VST_SHIFT) & VST_MASK;
पूर्ण

अटल पूर्णांक घातernow_k8_cpu_init_acpi(काष्ठा घातernow_k8_data *data)
अणु
	काष्ठा cpufreq_frequency_table *घातernow_table;
	पूर्णांक ret_val = -ENODEV;
	u64 control, status;

	अगर (acpi_processor_रेजिस्टर_perक्रमmance(&data->acpi_data, data->cpu)) अणु
		pr_debug("register performance failed: bad ACPI data\n");
		वापस -EIO;
	पूर्ण

	/* verअगरy the data contained in the ACPI काष्ठाures */
	अगर (data->acpi_data.state_count <= 1) अणु
		pr_debug("No ACPI P-States\n");
		जाओ err_out;
	पूर्ण

	control = data->acpi_data.control_रेजिस्टर.space_id;
	status = data->acpi_data.status_रेजिस्टर.space_id;

	अगर ((control != ACPI_ADR_SPACE_FIXED_HARDWARE) ||
	    (status != ACPI_ADR_SPACE_FIXED_HARDWARE)) अणु
		pr_debug("Invalid control/status registers (%llx - %llx)\n",
			control, status);
		जाओ err_out;
	पूर्ण

	/* fill in data->घातernow_table */
	घातernow_table = kzalloc((माप(*घातernow_table)
		* (data->acpi_data.state_count + 1)), GFP_KERNEL);
	अगर (!घातernow_table)
		जाओ err_out;

	/* fill in data */
	data->numps = data->acpi_data.state_count;
	घातernow_k8_acpi_pst_values(data, 0);

	ret_val = fill_घातernow_table_fidvid(data, घातernow_table);
	अगर (ret_val)
		जाओ err_out_mem;

	घातernow_table[data->acpi_data.state_count].frequency =
		CPUFREQ_TABLE_END;
	data->घातernow_table = घातernow_table;

	अगर (cpumask_first(topology_core_cpumask(data->cpu)) == data->cpu)
		prपूर्णांक_basics(data);

	/* notअगरy BIOS that we exist */
	acpi_processor_notअगरy_smm(THIS_MODULE);

	अगर (!zalloc_cpumask_var(&data->acpi_data.shared_cpu_map, GFP_KERNEL)) अणु
		pr_err("unable to alloc powernow_k8_data cpumask\n");
		ret_val = -ENOMEM;
		जाओ err_out_mem;
	पूर्ण

	वापस 0;

err_out_mem:
	kमुक्त(घातernow_table);

err_out:
	acpi_processor_unरेजिस्टर_perक्रमmance(data->cpu);

	/* data->acpi_data.state_count inक्रमms us at ->निकास()
	 * whether ACPI was used */
	data->acpi_data.state_count = 0;

	वापस ret_val;
पूर्ण

अटल पूर्णांक fill_घातernow_table_fidvid(काष्ठा घातernow_k8_data *data,
		काष्ठा cpufreq_frequency_table *घातernow_table)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < data->acpi_data.state_count; i++) अणु
		u32 fid;
		u32 vid;
		u32 freq, index;
		u64 status, control;

		अगर (data->exttype) अणु
			status =  data->acpi_data.states[i].status;
			fid = status & EXT_FID_MASK;
			vid = (status >> VID_SHIFT) & EXT_VID_MASK;
		पूर्ण अन्यथा अणु
			control =  data->acpi_data.states[i].control;
			fid = control & FID_MASK;
			vid = (control >> VID_SHIFT) & VID_MASK;
		पूर्ण

		pr_debug("   %d : fid 0x%x, vid 0x%x\n", i, fid, vid);

		index = fid | (vid<<8);
		घातernow_table[i].driver_data = index;

		freq = find_khz_freq_from_fid(fid);
		घातernow_table[i].frequency = freq;

		/* verअगरy frequency is OK */
		अगर ((freq > (MAX_FREQ * 1000)) || (freq < (MIN_FREQ * 1000))) अणु
			pr_debug("invalid freq %u kHz, ignoring\n", freq);
			invalidate_entry(घातernow_table, i);
			जारी;
		पूर्ण

		/* verअगरy voltage is OK -
		 * BIOSs are using "off" to indicate invalid */
		अगर (vid == VID_OFF) अणु
			pr_debug("invalid vid %u, ignoring\n", vid);
			invalidate_entry(घातernow_table, i);
			जारी;
		पूर्ण

		अगर (freq != (data->acpi_data.states[i].core_frequency * 1000)) अणु
			pr_info("invalid freq entries %u kHz vs. %u kHz\n",
				freq, (अचिन्हित पूर्णांक)
				(data->acpi_data.states[i].core_frequency
				 * 1000));
			invalidate_entry(घातernow_table, i);
			जारी;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम घातernow_k8_cpu_निकास_acpi(काष्ठा घातernow_k8_data *data)
अणु
	अगर (data->acpi_data.state_count)
		acpi_processor_unरेजिस्टर_perक्रमmance(data->cpu);
	मुक्त_cpumask_var(data->acpi_data.shared_cpu_map);
पूर्ण

अटल पूर्णांक get_transition_latency(काष्ठा घातernow_k8_data *data)
अणु
	पूर्णांक max_latency = 0;
	पूर्णांक i;
	क्रम (i = 0; i < data->acpi_data.state_count; i++) अणु
		पूर्णांक cur_latency = data->acpi_data.states[i].transition_latency
			+ data->acpi_data.states[i].bus_master_latency;
		अगर (cur_latency > max_latency)
			max_latency = cur_latency;
	पूर्ण
	अगर (max_latency == 0) अणु
		pr_err(FW_WARN "Invalid zero transition latency\n");
		max_latency = 1;
	पूर्ण
	/* value in usecs, needs to be in nanoseconds */
	वापस 1000 * max_latency;
पूर्ण

/* Take a frequency, and issue the fid/vid transition command */
अटल पूर्णांक transition_frequency_fidvid(काष्ठा घातernow_k8_data *data,
		अचिन्हित पूर्णांक index,
		काष्ठा cpufreq_policy *policy)
अणु
	u32 fid = 0;
	u32 vid = 0;
	पूर्णांक res;
	काष्ठा cpufreq_freqs freqs;

	pr_debug("cpu %d transition to index %u\n", smp_processor_id(), index);

	/* fid/vid correctness check क्रम k8 */
	/* fid are the lower 8 bits of the index we stored पूर्णांकo
	 * the cpufreq frequency table in find_psb_table, vid
	 * are the upper 8 bits.
	 */
	fid = data->घातernow_table[index].driver_data & 0xFF;
	vid = (data->घातernow_table[index].driver_data & 0xFF00) >> 8;

	pr_debug("table matched fid 0x%x, giving vid 0x%x\n", fid, vid);

	अगर (query_current_values_with_pending_रुको(data))
		वापस 1;

	अगर ((data->currvid == vid) && (data->currfid == fid)) अणु
		pr_debug("target matches current values (fid 0x%x, vid 0x%x)\n",
			fid, vid);
		वापस 0;
	पूर्ण

	pr_debug("cpu %d, changing to fid 0x%x, vid 0x%x\n",
		smp_processor_id(), fid, vid);
	freqs.old = find_khz_freq_from_fid(data->currfid);
	freqs.new = find_khz_freq_from_fid(fid);

	cpufreq_freq_transition_begin(policy, &freqs);
	res = transition_fid_vid(data, fid, vid);
	cpufreq_freq_transition_end(policy, &freqs, res);

	वापस res;
पूर्ण

काष्ठा घातernowk8_target_arg अणु
	काष्ठा cpufreq_policy		*pol;
	अचिन्हित			newstate;
पूर्ण;

अटल दीर्घ घातernowk8_target_fn(व्योम *arg)
अणु
	काष्ठा घातernowk8_target_arg *pta = arg;
	काष्ठा cpufreq_policy *pol = pta->pol;
	अचिन्हित newstate = pta->newstate;
	काष्ठा घातernow_k8_data *data = per_cpu(घातernow_data, pol->cpu);
	u32 checkfid;
	u32 checkvid;
	पूर्णांक ret;

	अगर (!data)
		वापस -EINVAL;

	checkfid = data->currfid;
	checkvid = data->currvid;

	अगर (pending_bit_stuck()) अणु
		pr_err("failing targ, change pending bit set\n");
		वापस -EIO;
	पूर्ण

	pr_debug("targ: cpu %d, %d kHz, min %d, max %d\n",
		pol->cpu, data->घातernow_table[newstate].frequency, pol->min,
		pol->max);

	अगर (query_current_values_with_pending_रुको(data))
		वापस -EIO;

	pr_debug("targ: curr fid 0x%x, vid 0x%x\n",
		data->currfid, data->currvid);

	अगर ((checkvid != data->currvid) ||
	    (checkfid != data->currfid)) अणु
		pr_info("error - out of sync, fix 0x%x 0x%x, vid 0x%x 0x%x\n",
		       checkfid, data->currfid,
		       checkvid, data->currvid);
	पूर्ण

	mutex_lock(&fidvid_mutex);

	घातernow_k8_acpi_pst_values(data, newstate);

	ret = transition_frequency_fidvid(data, newstate, pol);

	अगर (ret) अणु
		pr_err("transition frequency failed\n");
		mutex_unlock(&fidvid_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&fidvid_mutex);

	pol->cur = find_khz_freq_from_fid(data->currfid);

	वापस 0;
पूर्ण

/* Driver entry poपूर्णांक to चयन to the target frequency */
अटल पूर्णांक घातernowk8_target(काष्ठा cpufreq_policy *pol, अचिन्हित index)
अणु
	काष्ठा घातernowk8_target_arg pta = अणु .pol = pol, .newstate = index पूर्ण;

	वापस work_on_cpu(pol->cpu, घातernowk8_target_fn, &pta);
पूर्ण

काष्ठा init_on_cpu अणु
	काष्ठा घातernow_k8_data *data;
	पूर्णांक rc;
पूर्ण;

अटल व्योम घातernowk8_cpu_init_on_cpu(व्योम *_init_on_cpu)
अणु
	काष्ठा init_on_cpu *init_on_cpu = _init_on_cpu;

	अगर (pending_bit_stuck()) अणु
		pr_err("failing init, change pending bit set\n");
		init_on_cpu->rc = -ENODEV;
		वापस;
	पूर्ण

	अगर (query_current_values_with_pending_रुको(init_on_cpu->data)) अणु
		init_on_cpu->rc = -ENODEV;
		वापस;
	पूर्ण

	fidvid_msr_init();

	init_on_cpu->rc = 0;
पूर्ण

#घोषणा MISSING_PSS_MSG \
	FW_BUG "No compatible ACPI _PSS objects found.\n" \
	FW_BUG "First, make sure Cool'N'Quiet is enabled in the BIOS.\n" \
	FW_BUG "If that doesn't help, try upgrading your BIOS.\n"

/* per CPU init entry poपूर्णांक to the driver */
अटल पूर्णांक घातernowk8_cpu_init(काष्ठा cpufreq_policy *pol)
अणु
	काष्ठा घातernow_k8_data *data;
	काष्ठा init_on_cpu init_on_cpu;
	पूर्णांक rc, cpu;

	smp_call_function_single(pol->cpu, check_supported_cpu, &rc, 1);
	अगर (rc)
		वापस -ENODEV;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->cpu = pol->cpu;

	अगर (घातernow_k8_cpu_init_acpi(data)) अणु
		/*
		 * Use the PSB BIOS काष्ठाure. This is only available on
		 * an UP version, and is deprecated by AMD.
		 */
		अगर (num_online_cpus() != 1) अणु
			pr_err_once(MISSING_PSS_MSG);
			जाओ err_out;
		पूर्ण
		अगर (pol->cpu != 0) अणु
			pr_err(FW_BUG "No ACPI _PSS objects for CPU other than CPU0. Complain to your BIOS vendor.\n");
			जाओ err_out;
		पूर्ण
		rc = find_psb_table(data);
		अगर (rc)
			जाओ err_out;

		/* Take a crude guess here.
		 * That guess was in microseconds, so multiply with 1000 */
		pol->cpuinfo.transition_latency = (
			 ((data->rvo + 8) * data->vstable * VST_UNITS_20US) +
			 ((1 << data->irt) * 30)) * 1000;
	पूर्ण अन्यथा /* ACPI _PSS objects available */
		pol->cpuinfo.transition_latency = get_transition_latency(data);

	/* only run on specअगरic CPU from here on */
	init_on_cpu.data = data;
	smp_call_function_single(data->cpu, घातernowk8_cpu_init_on_cpu,
				 &init_on_cpu, 1);
	rc = init_on_cpu.rc;
	अगर (rc != 0)
		जाओ err_out_निकास_acpi;

	cpumask_copy(pol->cpus, topology_core_cpumask(pol->cpu));
	data->available_cores = pol->cpus;
	pol->freq_table = data->घातernow_table;

	pr_debug("cpu_init done, current fid 0x%x, vid 0x%x\n",
		data->currfid, data->currvid);

	/* Poपूर्णांक all the CPUs in this policy to the same data */
	क्रम_each_cpu(cpu, pol->cpus)
		per_cpu(घातernow_data, cpu) = data;

	वापस 0;

err_out_निकास_acpi:
	घातernow_k8_cpu_निकास_acpi(data);

err_out:
	kमुक्त(data);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक घातernowk8_cpu_निकास(काष्ठा cpufreq_policy *pol)
अणु
	काष्ठा घातernow_k8_data *data = per_cpu(घातernow_data, pol->cpu);
	पूर्णांक cpu;

	अगर (!data)
		वापस -EINVAL;

	घातernow_k8_cpu_निकास_acpi(data);

	kमुक्त(data->घातernow_table);
	kमुक्त(data);
	क्रम_each_cpu(cpu, pol->cpus)
		per_cpu(घातernow_data, cpu) = शून्य;

	वापस 0;
पूर्ण

अटल व्योम query_values_on_cpu(व्योम *_err)
अणु
	पूर्णांक *err = _err;
	काष्ठा घातernow_k8_data *data = __this_cpu_पढ़ो(घातernow_data);

	*err = query_current_values_with_pending_रुको(data);
पूर्ण

अटल अचिन्हित पूर्णांक घातernowk8_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घातernow_k8_data *data = per_cpu(घातernow_data, cpu);
	अचिन्हित पूर्णांक khz = 0;
	पूर्णांक err;

	अगर (!data)
		वापस 0;

	smp_call_function_single(cpu, query_values_on_cpu, &err, true);
	अगर (err)
		जाओ out;

	khz = find_khz_freq_from_fid(data->currfid);


out:
	वापस khz;
पूर्ण

अटल काष्ठा cpufreq_driver cpufreq_amd64_driver = अणु
	.flags		= CPUFREQ_ASYNC_NOTIFICATION,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= घातernowk8_target,
	.bios_limit	= acpi_processor_get_bios_limit,
	.init		= घातernowk8_cpu_init,
	.निकास		= घातernowk8_cpu_निकास,
	.get		= घातernowk8_get,
	.name		= "powernow-k8",
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल व्योम __request_acpi_cpufreq(व्योम)
अणु
	स्थिर अक्षर drv[] = "acpi-cpufreq";
	स्थिर अक्षर *cur_drv;

	cur_drv = cpufreq_get_current_driver();
	अगर (!cur_drv)
		जाओ request;

	अगर (म_भेदन(cur_drv, drv, min_t(माप_प्रकार, म_माप(cur_drv), म_माप(drv))))
		pr_warn("WTF driver: %s\n", cur_drv);

	वापस;

 request:
	pr_warn("This CPU is not supported anymore, using acpi-cpufreq instead.\n");
	request_module(drv);
पूर्ण

/* driver entry poपूर्णांक क्रम init */
अटल पूर्णांक घातernowk8_init(व्योम)
अणु
	अचिन्हित पूर्णांक i, supported_cpus = 0;
	पूर्णांक ret;

	अगर (boot_cpu_has(X86_FEATURE_HW_PSTATE)) अणु
		__request_acpi_cpufreq();
		वापस -ENODEV;
	पूर्ण

	अगर (!x86_match_cpu(घातernow_k8_ids))
		वापस -ENODEV;

	get_online_cpus();
	क्रम_each_online_cpu(i) अणु
		smp_call_function_single(i, check_supported_cpu, &ret, 1);
		अगर (!ret)
			supported_cpus++;
	पूर्ण

	अगर (supported_cpus != num_online_cpus()) अणु
		put_online_cpus();
		वापस -ENODEV;
	पूर्ण
	put_online_cpus();

	ret = cpufreq_रेजिस्टर_driver(&cpufreq_amd64_driver);
	अगर (ret)
		वापस ret;

	pr_info("Found %d %s (%d cpu cores) (" VERSION ")\n",
		num_online_nodes(), boot_cpu_data.x86_model_id, supported_cpus);

	वापस ret;
पूर्ण

/* driver entry poपूर्णांक क्रम term */
अटल व्योम __निकास घातernowk8_निकास(व्योम)
अणु
	pr_debug("exit\n");

	cpufreq_unरेजिस्टर_driver(&cpufreq_amd64_driver);
पूर्ण

MODULE_AUTHOR("Paul Devriendt <paul.devriendt@amd.com>");
MODULE_AUTHOR("Mark Langsdorf <mark.langsdorf@amd.com>");
MODULE_DESCRIPTION("AMD Athlon 64 and Opteron processor frequency driver.");
MODULE_LICENSE("GPL");

late_initcall(घातernowk8_init);
module_निकास(घातernowk8_निकास);
