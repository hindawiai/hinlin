<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  AMD K7 Powernow driver.
 *  (C) 2003 Dave Jones on behalf of SuSE Lअसल.
 *
 *  Based upon datasheets & sample CPUs kindly provided by AMD.
 *
 * Errata 5:
 *  CPU may fail to execute a FID/VID change in presence of पूर्णांकerrupt.
 *  - We cli/sti on stepping A0 CPUs around the FID/VID transition.
 * Errata 15:
 *  CPU with half frequency multipliers may hang upon wakeup from disconnect.
 *  - We disable half multipliers अगर ACPI is used on A0 stepping CPUs.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/dmi.h>
#समावेश <linux/समयx.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/समयr.h>		/* Needed क्रम recalibrate_cpu_khz() */
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/cpu_device_id.h>

#अगर_घोषित CONFIG_X86_POWERNOW_K7_ACPI
#समावेश <linux/acpi.h>
#समावेश <acpi/processor.h>
#पूर्ण_अगर

#समावेश "powernow-k7.h"

काष्ठा psb_s अणु
	u8 signature[10];
	u8 tableversion;
	u8 flags;
	u16 settlingसमय;
	u8 reserved1;
	u8 numpst;
पूर्ण;

काष्ठा pst_s अणु
	u32 cpuid;
	u8 fsbspeed;
	u8 maxfid;
	u8 startvid;
	u8 numpstates;
पूर्ण;

#अगर_घोषित CONFIG_X86_POWERNOW_K7_ACPI
जोड़ घातernow_acpi_control_t अणु
	काष्ठा अणु
		अचिन्हित दीर्घ fid:5,
			vid:5,
			sgtc:20,
			res1:2;
	पूर्ण bits;
	अचिन्हित दीर्घ val;
पूर्ण;
#पूर्ण_अगर

/* भागide by 1000 to get VCore voltage in V. */
अटल स्थिर पूर्णांक mobile_vid_table[32] = अणु
    2000, 1950, 1900, 1850, 1800, 1750, 1700, 1650,
    1600, 1550, 1500, 1450, 1400, 1350, 1300, 0,
    1275, 1250, 1225, 1200, 1175, 1150, 1125, 1100,
    1075, 1050, 1025, 1000, 975, 950, 925, 0,
पूर्ण;

/* भागide by 10 to get FID. */
अटल स्थिर पूर्णांक fid_codes[32] = अणु
    110, 115, 120, 125, 50, 55, 60, 65,
    70, 75, 80, 85, 90, 95, 100, 105,
    30, 190, 40, 200, 130, 135, 140, 210,
    150, 225, 160, 165, 170, 180, -1, -1,
पूर्ण;

/* This parameter is used in order to क्रमce ACPI instead of legacy method क्रम
 * configuration purpose.
 */

अटल पूर्णांक acpi_क्रमce;

अटल काष्ठा cpufreq_frequency_table *घातernow_table;

अटल अचिन्हित पूर्णांक can_scale_bus;
अटल अचिन्हित पूर्णांक can_scale_vid;
अटल अचिन्हित पूर्णांक minimum_speed = -1;
अटल अचिन्हित पूर्णांक maximum_speed;
अटल अचिन्हित पूर्णांक number_scales;
अटल अचिन्हित पूर्णांक fsb;
अटल अचिन्हित पूर्णांक latency;
अटल अक्षर have_a0;

अटल पूर्णांक check_fsb(अचिन्हित पूर्णांक fsbspeed)
अणु
	पूर्णांक delta;
	अचिन्हित पूर्णांक f = fsb / 1000;

	delta = (fsbspeed > f) ? fsbspeed - f : f - fsbspeed;
	वापस delta < 5;
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id घातernow_k7_cpuids[] = अणु
	X86_MATCH_VENDOR_FAM(AMD, 6, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, घातernow_k7_cpuids);

अटल पूर्णांक check_घातernow(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	अचिन्हित पूर्णांक maxei, eax, ebx, ecx, edx;

	अगर (!x86_match_cpu(घातernow_k7_cpuids))
		वापस 0;

	/* Get maximum capabilities */
	maxei = cpuid_eax(0x80000000);
	अगर (maxei < 0x80000007) अणु	/* Any घातernow info ? */
#अगर_घोषित MODULE
		pr_info("No powernow capabilities detected\n");
#पूर्ण_अगर
		वापस 0;
	पूर्ण

	अगर ((c->x86_model == 6) && (c->x86_stepping == 0)) अणु
		pr_info("K7 660[A0] core detected, enabling errata workarounds\n");
		have_a0 = 1;
	पूर्ण

	cpuid(0x80000007, &eax, &ebx, &ecx, &edx);

	/* Check we can actually करो something beक्रमe we say anything.*/
	अगर (!(edx & (1 << 1 | 1 << 2)))
		वापस 0;

	pr_info("PowerNOW! Technology present. Can scale: ");

	अगर (edx & 1 << 1) अणु
		pr_cont("frequency");
		can_scale_bus = 1;
	पूर्ण

	अगर ((edx & (1 << 1 | 1 << 2)) == 0x6)
		pr_cont(" and ");

	अगर (edx & 1 << 2) अणु
		pr_cont("voltage");
		can_scale_vid = 1;
	पूर्ण

	pr_cont("\n");
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_X86_POWERNOW_K7_ACPI
अटल व्योम invalidate_entry(अचिन्हित पूर्णांक entry)
अणु
	घातernow_table[entry].frequency = CPUFREQ_ENTRY_INVALID;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक get_ranges(अचिन्हित अक्षर *pst)
अणु
	अचिन्हित पूर्णांक j;
	अचिन्हित पूर्णांक speed;
	u8 fid, vid;

	घातernow_table = kzalloc((माप(*घातernow_table) *
				(number_scales + 1)), GFP_KERNEL);
	अगर (!घातernow_table)
		वापस -ENOMEM;

	क्रम (j = 0 ; j < number_scales; j++) अणु
		fid = *pst++;

		घातernow_table[j].frequency = (fsb * fid_codes[fid]) / 10;
		घातernow_table[j].driver_data = fid; /* lower 8 bits */

		speed = घातernow_table[j].frequency;

		अगर ((fid_codes[fid] % 10) == 5) अणु
#अगर_घोषित CONFIG_X86_POWERNOW_K7_ACPI
			अगर (have_a0 == 1)
				invalidate_entry(j);
#पूर्ण_अगर
		पूर्ण

		अगर (speed < minimum_speed)
			minimum_speed = speed;
		अगर (speed > maximum_speed)
			maximum_speed = speed;

		vid = *pst++;
		घातernow_table[j].driver_data |= (vid << 8); /* upper 8 bits */

		pr_debug("   FID: 0x%x (%d.%dx [%dMHz])  "
			 "VID: 0x%x (%d.%03dV)\n", fid, fid_codes[fid] / 10,
			 fid_codes[fid] % 10, speed/1000, vid,
			 mobile_vid_table[vid]/1000,
			 mobile_vid_table[vid]%1000);
	पूर्ण
	घातernow_table[number_scales].frequency = CPUFREQ_TABLE_END;
	घातernow_table[number_scales].driver_data = 0;

	वापस 0;
पूर्ण


अटल व्योम change_FID(पूर्णांक fid)
अणु
	जोड़ msr_fidvidctl fidvidctl;

	rdmsrl(MSR_K7_FID_VID_CTL, fidvidctl.val);
	अगर (fidvidctl.bits.FID != fid) अणु
		fidvidctl.bits.SGTC = latency;
		fidvidctl.bits.FID = fid;
		fidvidctl.bits.VIDC = 0;
		fidvidctl.bits.FIDC = 1;
		wrmsrl(MSR_K7_FID_VID_CTL, fidvidctl.val);
	पूर्ण
पूर्ण


अटल व्योम change_VID(पूर्णांक vid)
अणु
	जोड़ msr_fidvidctl fidvidctl;

	rdmsrl(MSR_K7_FID_VID_CTL, fidvidctl.val);
	अगर (fidvidctl.bits.VID != vid) अणु
		fidvidctl.bits.SGTC = latency;
		fidvidctl.bits.VID = vid;
		fidvidctl.bits.FIDC = 0;
		fidvidctl.bits.VIDC = 1;
		wrmsrl(MSR_K7_FID_VID_CTL, fidvidctl.val);
	पूर्ण
पूर्ण


अटल पूर्णांक घातernow_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	u8 fid, vid;
	काष्ठा cpufreq_freqs freqs;
	जोड़ msr_fidvidstatus fidvidstatus;
	पूर्णांक cfid;

	/* fid are the lower 8 bits of the index we stored पूर्णांकo
	 * the cpufreq frequency table in घातernow_decode_bios,
	 * vid are the upper 8 bits.
	 */

	fid = घातernow_table[index].driver_data & 0xFF;
	vid = (घातernow_table[index].driver_data & 0xFF00) >> 8;

	rdmsrl(MSR_K7_FID_VID_STATUS, fidvidstatus.val);
	cfid = fidvidstatus.bits.CFID;
	freqs.old = fsb * fid_codes[cfid] / 10;

	freqs.new = घातernow_table[index].frequency;

	/* Now करो the magic poking पूर्णांकo the MSRs.  */

	अगर (have_a0 == 1)	/* A0 errata 5 */
		local_irq_disable();

	अगर (freqs.old > freqs.new) अणु
		/* Going करोwn, so change FID first */
		change_FID(fid);
		change_VID(vid);
	पूर्ण अन्यथा अणु
		/* Going up, so change VID first */
		change_VID(vid);
		change_FID(fid);
	पूर्ण


	अगर (have_a0 == 1)
		local_irq_enable();

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_X86_POWERNOW_K7_ACPI

अटल काष्ठा acpi_processor_perक्रमmance *acpi_processor_perf;

अटल पूर्णांक घातernow_acpi_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक retval = 0;
	जोड़ घातernow_acpi_control_t pc;

	अगर (acpi_processor_perf != शून्य && घातernow_table != शून्य) अणु
		retval = -EINVAL;
		जाओ err0;
	पूर्ण

	acpi_processor_perf = kzalloc(माप(*acpi_processor_perf), GFP_KERNEL);
	अगर (!acpi_processor_perf) अणु
		retval = -ENOMEM;
		जाओ err0;
	पूर्ण

	अगर (!zalloc_cpumask_var(&acpi_processor_perf->shared_cpu_map,
								GFP_KERNEL)) अणु
		retval = -ENOMEM;
		जाओ err05;
	पूर्ण

	अगर (acpi_processor_रेजिस्टर_perक्रमmance(acpi_processor_perf, 0)) अणु
		retval = -EIO;
		जाओ err1;
	पूर्ण

	अगर (acpi_processor_perf->control_रेजिस्टर.space_id !=
			ACPI_ADR_SPACE_FIXED_HARDWARE) अणु
		retval = -ENODEV;
		जाओ err2;
	पूर्ण

	अगर (acpi_processor_perf->status_रेजिस्टर.space_id !=
			ACPI_ADR_SPACE_FIXED_HARDWARE) अणु
		retval = -ENODEV;
		जाओ err2;
	पूर्ण

	number_scales = acpi_processor_perf->state_count;

	अगर (number_scales < 2) अणु
		retval = -ENODEV;
		जाओ err2;
	पूर्ण

	घातernow_table = kzalloc((माप(*घातernow_table) *
				(number_scales + 1)), GFP_KERNEL);
	अगर (!घातernow_table) अणु
		retval = -ENOMEM;
		जाओ err2;
	पूर्ण

	pc.val = (अचिन्हित दीर्घ) acpi_processor_perf->states[0].control;
	क्रम (i = 0; i < number_scales; i++) अणु
		u8 fid, vid;
		काष्ठा acpi_processor_px *state =
			&acpi_processor_perf->states[i];
		अचिन्हित पूर्णांक speed, speed_mhz;

		pc.val = (अचिन्हित दीर्घ) state->control;
		pr_debug("acpi:  P%d: %d MHz %d mW %d uS control %08x SGTC %d\n",
			 i,
			 (u32) state->core_frequency,
			 (u32) state->घातer,
			 (u32) state->transition_latency,
			 (u32) state->control,
			 pc.bits.sgtc);

		vid = pc.bits.vid;
		fid = pc.bits.fid;

		घातernow_table[i].frequency = fsb * fid_codes[fid] / 10;
		घातernow_table[i].driver_data = fid; /* lower 8 bits */
		घातernow_table[i].driver_data |= (vid << 8); /* upper 8 bits */

		speed = घातernow_table[i].frequency;
		speed_mhz = speed / 1000;

		/* processor_perflib will multiply the MHz value by 1000 to
		 * get a KHz value (e.g. 1266000). However, घातernow-k7 works
		 * with true KHz values (e.g. 1266768). To ensure that all
		 * घातernow frequencies are available, we must ensure that
		 * ACPI करोesn't restrict them, so we round up the MHz value
		 * to ensure that perflib's computed KHz value is greater than
		 * or equal to घातernow's KHz value.
		 */
		अगर (speed % 1000 > 0)
			speed_mhz++;

		अगर ((fid_codes[fid] % 10) == 5) अणु
			अगर (have_a0 == 1)
				invalidate_entry(i);
		पूर्ण

		pr_debug("   FID: 0x%x (%d.%dx [%dMHz])  "
			 "VID: 0x%x (%d.%03dV)\n", fid, fid_codes[fid] / 10,
			 fid_codes[fid] % 10, speed_mhz, vid,
			 mobile_vid_table[vid]/1000,
			 mobile_vid_table[vid]%1000);

		अगर (state->core_frequency != speed_mhz) अणु
			state->core_frequency = speed_mhz;
			pr_debug("   Corrected ACPI frequency to %d\n",
				speed_mhz);
		पूर्ण

		अगर (latency < pc.bits.sgtc)
			latency = pc.bits.sgtc;

		अगर (speed < minimum_speed)
			minimum_speed = speed;
		अगर (speed > maximum_speed)
			maximum_speed = speed;
	पूर्ण

	घातernow_table[i].frequency = CPUFREQ_TABLE_END;
	घातernow_table[i].driver_data = 0;

	/* notअगरy BIOS that we exist */
	acpi_processor_notअगरy_smm(THIS_MODULE);

	वापस 0;

err2:
	acpi_processor_unरेजिस्टर_perक्रमmance(0);
err1:
	मुक्त_cpumask_var(acpi_processor_perf->shared_cpu_map);
err05:
	kमुक्त(acpi_processor_perf);
err0:
	pr_warn("ACPI perflib can not be used on this platform\n");
	acpi_processor_perf = शून्य;
	वापस retval;
पूर्ण
#अन्यथा
अटल पूर्णांक घातernow_acpi_init(व्योम)
अणु
	pr_info("no support for ACPI processor found - please recompile your kernel with ACPI processor\n");
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल व्योम prपूर्णांक_pst_entry(काष्ठा pst_s *pst, अचिन्हित पूर्णांक j)
अणु
	pr_debug("PST:%d (@%p)\n", j, pst);
	pr_debug(" cpuid: 0x%x  fsb: %d  maxFID: 0x%x  startvid: 0x%x\n",
		pst->cpuid, pst->fsbspeed, pst->maxfid, pst->startvid);
पूर्ण

अटल पूर्णांक घातernow_decode_bios(पूर्णांक maxfid, पूर्णांक startvid)
अणु
	काष्ठा psb_s *psb;
	काष्ठा pst_s *pst;
	अचिन्हित पूर्णांक i, j;
	अचिन्हित अक्षर *p;
	अचिन्हित पूर्णांक etuple;
	अचिन्हित पूर्णांक ret;

	etuple = cpuid_eax(0x80000001);

	क्रम (i = 0xC0000; i < 0xffff0 ; i += 16) अणु

		p = phys_to_virt(i);

		अगर (स_भेद(p, "AMDK7PNOW!",  10) == 0) अणु
			pr_debug("Found PSB header at %p\n", p);
			psb = (काष्ठा psb_s *) p;
			pr_debug("Table version: 0x%x\n", psb->tableversion);
			अगर (psb->tableversion != 0x12) अणु
				pr_info("Sorry, only v1.2 tables supported right now\n");
				वापस -ENODEV;
			पूर्ण

			pr_debug("Flags: 0x%x\n", psb->flags);
			अगर ((psb->flags & 1) == 0)
				pr_debug("Mobile voltage regulator\n");
			अन्यथा
				pr_debug("Desktop voltage regulator\n");

			latency = psb->settlingसमय;
			अगर (latency < 100) अणु
				pr_info("BIOS set settling time to %d microseconds. Should be at least 100. Correcting.\n",
					latency);
				latency = 100;
			पूर्ण
			pr_debug("Settling Time: %d microseconds.\n",
					psb->settlingसमय);
			pr_debug("Has %d PST tables. (Only dumping ones "
					"relevant to this CPU).\n",
					psb->numpst);

			p += माप(*psb);

			pst = (काष्ठा pst_s *) p;

			क्रम (j = 0; j < psb->numpst; j++) अणु
				pst = (काष्ठा pst_s *) p;
				number_scales = pst->numpstates;

				अगर ((etuple == pst->cpuid) &&
				    check_fsb(pst->fsbspeed) &&
				    (maxfid == pst->maxfid) &&
				    (startvid == pst->startvid)) अणु
					prपूर्णांक_pst_entry(pst, j);
					p = (अक्षर *)pst + माप(*pst);
					ret = get_ranges(p);
					वापस ret;
				पूर्ण अन्यथा अणु
					अचिन्हित पूर्णांक k;
					p = (अक्षर *)pst + माप(*pst);
					क्रम (k = 0; k < number_scales; k++)
						p += 2;
				पूर्ण
			पूर्ण
			pr_info("No PST tables match this cpuid (0x%x)\n",
				etuple);
			pr_info("This is indicative of a broken BIOS\n");

			वापस -EINVAL;
		पूर्ण
		p++;
	पूर्ण

	वापस -ENODEV;
पूर्ण


/*
 * We use the fact that the bus frequency is somehow
 * a multiple of 100000/3 khz, then we compute sgtc according
 * to this multiple.
 * That way, we match more how AMD thinks all of that work.
 * We will then get the same kind of behaviour alपढ़ोy tested under
 * the "well-known" other OS.
 */
अटल पूर्णांक fixup_sgtc(व्योम)
अणु
	अचिन्हित पूर्णांक sgtc;
	अचिन्हित पूर्णांक m;

	m = fsb / 3333;
	अगर ((m % 10) >= 5)
		m += 5;

	m /= 10;

	sgtc = 100 * m * latency;
	sgtc = sgtc / 3;
	अगर (sgtc > 0xfffff) अणु
		pr_warn("SGTC too large %d\n", sgtc);
		sgtc = 0xfffff;
	पूर्ण
	वापस sgtc;
पूर्ण

अटल अचिन्हित पूर्णांक घातernow_get(अचिन्हित पूर्णांक cpu)
अणु
	जोड़ msr_fidvidstatus fidvidstatus;
	अचिन्हित पूर्णांक cfid;

	अगर (cpu)
		वापस 0;
	rdmsrl(MSR_K7_FID_VID_STATUS, fidvidstatus.val);
	cfid = fidvidstatus.bits.CFID;

	वापस fsb * fid_codes[cfid] / 10;
पूर्ण


अटल पूर्णांक acer_cpufreq_pst(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	pr_warn("%s laptop with broken PST tables in BIOS detected\n",
		d->ident);
	pr_warn("You need to downgrade to 3A21 (09/09/2002), or try a newer BIOS than 3A71 (01/20/2003)\n");
	pr_warn("cpufreq scaling has been disabled as a result of this\n");
	वापस 0;
पूर्ण

/*
 * Some Athlon laptops have really fucked PST tables.
 * A BIOS update is all that can save them.
 * Mention this, and disable cpufreq.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id घातernow_dmi_table[] = अणु
	अणु
		.callback = acer_cpufreq_pst,
		.ident = "Acer Aspire",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde Software"),
			DMI_MATCH(DMI_BIOS_VERSION, "3A71"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक घातernow_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	जोड़ msr_fidvidstatus fidvidstatus;
	पूर्णांक result;

	अगर (policy->cpu != 0)
		वापस -ENODEV;

	rdmsrl(MSR_K7_FID_VID_STATUS, fidvidstatus.val);

	recalibrate_cpu_khz();

	fsb = (10 * cpu_khz) / fid_codes[fidvidstatus.bits.CFID];
	अगर (!fsb) अणु
		pr_warn("can not determine bus frequency\n");
		वापस -EINVAL;
	पूर्ण
	pr_debug("FSB: %3dMHz\n", fsb/1000);

	अगर (dmi_check_प्रणाली(घातernow_dmi_table) || acpi_क्रमce) अणु
		pr_info("PSB/PST known to be broken - trying ACPI instead\n");
		result = घातernow_acpi_init();
	पूर्ण अन्यथा अणु
		result = घातernow_decode_bios(fidvidstatus.bits.MFID,
				fidvidstatus.bits.SVID);
		अगर (result) अणु
			pr_info("Trying ACPI perflib\n");
			maximum_speed = 0;
			minimum_speed = -1;
			latency = 0;
			result = घातernow_acpi_init();
			अगर (result) अणु
				pr_info("ACPI and legacy methods failed\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			/* SGTC use the bus घड़ी as समयr */
			latency = fixup_sgtc();
			pr_info("SGTC: %d\n", latency);
		पूर्ण
	पूर्ण

	अगर (result)
		वापस result;

	pr_info("Minimum speed %d MHz - Maximum speed %d MHz\n",
		minimum_speed/1000, maximum_speed/1000);

	policy->cpuinfo.transition_latency =
		cpufreq_scale(2000000UL, fsb, latency);
	policy->freq_table = घातernow_table;

	वापस 0;
पूर्ण

अटल पूर्णांक घातernow_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
#अगर_घोषित CONFIG_X86_POWERNOW_K7_ACPI
	अगर (acpi_processor_perf) अणु
		acpi_processor_unरेजिस्टर_perक्रमmance(0);
		मुक्त_cpumask_var(acpi_processor_perf->shared_cpu_map);
		kमुक्त(acpi_processor_perf);
	पूर्ण
#पूर्ण_अगर

	kमुक्त(घातernow_table);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver घातernow_driver = अणु
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= घातernow_target,
	.get		= घातernow_get,
#अगर_घोषित CONFIG_X86_POWERNOW_K7_ACPI
	.bios_limit	= acpi_processor_get_bios_limit,
#पूर्ण_अगर
	.init		= घातernow_cpu_init,
	.निकास		= घातernow_cpu_निकास,
	.name		= "powernow-k7",
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक __init घातernow_init(व्योम)
अणु
	अगर (check_घातernow() == 0)
		वापस -ENODEV;
	वापस cpufreq_रेजिस्टर_driver(&घातernow_driver);
पूर्ण


अटल व्योम __निकास घातernow_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&घातernow_driver);
पूर्ण

module_param(acpi_क्रमce,  पूर्णांक, 0444);
MODULE_PARM_DESC(acpi_क्रमce, "Force ACPI to be used.");

MODULE_AUTHOR("Dave Jones");
MODULE_DESCRIPTION("Powernow driver for AMD K7 processors.");
MODULE_LICENSE("GPL");

late_initcall(घातernow_init);
module_निकास(घातernow_निकास);

