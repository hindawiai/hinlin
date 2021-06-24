<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2001-2004  Dave Jones.
 *  (C) 2002  Padraig Brady. <padraig@antefacto.com>
 *
 *  Based upon datasheets & sample CPUs kindly provided by VIA.
 *
 *  VIA have currently 3 dअगरferent versions of Longhaul.
 *  Version 1 (Longhaul) uses the BCR2 MSR at 0x1147.
 *   It is present only in Samuel 1 (C5A), Samuel 2 (C5B) stepping 0.
 *  Version 2 of दीर्घhaul is backward compatible with v1, but adds
 *   LONGHAUL MSR क्रम purpose of both frequency and voltage scaling.
 *   Present in Samuel 2 (steppings 1-7 only) (C5B), and Ezra (C5C).
 *  Version 3 of दीर्घhaul got नामd to Powersaver and redeचिन्हित
 *   to use only the POWERSAVER MSR at 0x110a.
 *   It is present in Ezra-T (C5M), Nehemiah (C5X) and above.
 *   It's pretty much the same feature wise to दीर्घhaul v2, though
 *   there is provision क्रम scaling FSB too, but this करोesn't work
 *   too well in practice so we करोn't even try to use this.
 *
 *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/समयx.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>

#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <acpi/processor.h>

#समावेश "longhaul.h"

#घोषणा TYPE_LONGHAUL_V1	1
#घोषणा TYPE_LONGHAUL_V2	2
#घोषणा TYPE_POWERSAVER		3

#घोषणा	CPU_SAMUEL	1
#घोषणा	CPU_SAMUEL2	2
#घोषणा	CPU_EZRA	3
#घोषणा	CPU_EZRA_T	4
#घोषणा	CPU_NEHEMIAH	5
#घोषणा	CPU_NEHEMIAH_C	6

/* Flags */
#घोषणा USE_ACPI_C3		(1 << 1)
#घोषणा USE_NORTHBRIDGE		(1 << 2)

अटल पूर्णांक cpu_model;
अटल अचिन्हित पूर्णांक numscales = 16;
अटल अचिन्हित पूर्णांक fsb;

अटल स्थिर काष्ठा mV_pos *vrm_mV_table;
अटल स्थिर अचिन्हित अक्षर *mV_vrm_table;

अटल अचिन्हित पूर्णांक highest_speed, lowest_speed; /* kHz */
अटल अचिन्हित पूर्णांक minmult, maxmult;
अटल पूर्णांक can_scale_voltage;
अटल काष्ठा acpi_processor *pr;
अटल काष्ठा acpi_processor_cx *cx;
अटल u32 acpi_regs_addr;
अटल u8 दीर्घhaul_flags;
अटल अचिन्हित पूर्णांक दीर्घhaul_index;

/* Module parameters */
अटल पूर्णांक scale_voltage;
अटल पूर्णांक disable_acpi_c3;
अटल पूर्णांक revid_errata;
अटल पूर्णांक enable;

/* Clock ratios multiplied by 10 */
अटल पूर्णांक mults[32];
अटल पूर्णांक eblcr[32];
अटल पूर्णांक दीर्घhaul_version;
अटल काष्ठा cpufreq_frequency_table *दीर्घhaul_table;

अटल अक्षर speedbuffer[8];

अटल अक्षर *prपूर्णांक_speed(पूर्णांक speed)
अणु
	अगर (speed < 1000) अणु
		snम_लिखो(speedbuffer, माप(speedbuffer), "%dMHz", speed);
		वापस speedbuffer;
	पूर्ण

	अगर (speed%1000 == 0)
		snम_लिखो(speedbuffer, माप(speedbuffer),
			"%dGHz", speed/1000);
	अन्यथा
		snम_लिखो(speedbuffer, माप(speedbuffer),
			"%d.%dGHz", speed/1000, (speed%1000)/100);

	वापस speedbuffer;
पूर्ण


अटल अचिन्हित पूर्णांक calc_speed(पूर्णांक mult)
अणु
	पूर्णांक khz;
	khz = (mult/10)*fsb;
	अगर (mult%10)
		khz += fsb/2;
	khz *= 1000;
	वापस khz;
पूर्ण


अटल पूर्णांक दीर्घhaul_get_cpu_mult(व्योम)
अणु
	अचिन्हित दीर्घ invalue = 0, lo, hi;

	rdmsr(MSR_IA32_EBL_CR_POWERON, lo, hi);
	invalue = (lo & (1<<22|1<<23|1<<24|1<<25))>>22;
	अगर (दीर्घhaul_version == TYPE_LONGHAUL_V2 ||
	    दीर्घhaul_version == TYPE_POWERSAVER) अणु
		अगर (lo & (1<<27))
			invalue += 16;
	पूर्ण
	वापस eblcr[invalue];
पूर्ण

/* For processor with BCR2 MSR */

अटल व्योम करो_दीर्घhaul1(अचिन्हित पूर्णांक mults_index)
अणु
	जोड़ msr_bcr2 bcr2;

	rdmsrl(MSR_VIA_BCR2, bcr2.val);
	/* Enable software घड़ी multiplier */
	bcr2.bits.ESOFTBF = 1;
	bcr2.bits.CLOCKMUL = mults_index & 0xff;

	/* Sync to समयr tick */
	safe_halt();
	/* Change frequency on next halt or sleep */
	wrmsrl(MSR_VIA_BCR2, bcr2.val);
	/* Invoke transition */
	ACPI_FLUSH_CPU_CACHE();
	halt();

	/* Disable software घड़ी multiplier */
	local_irq_disable();
	rdmsrl(MSR_VIA_BCR2, bcr2.val);
	bcr2.bits.ESOFTBF = 0;
	wrmsrl(MSR_VIA_BCR2, bcr2.val);
पूर्ण

/* For processor with Longhaul MSR */

अटल व्योम करो_घातersaver(पूर्णांक cx_address, अचिन्हित पूर्णांक mults_index,
			  अचिन्हित पूर्णांक dir)
अणु
	जोड़ msr_दीर्घhaul दीर्घhaul;
	u32 t;

	rdmsrl(MSR_VIA_LONGHAUL, दीर्घhaul.val);
	/* Setup new frequency */
	अगर (!revid_errata)
		दीर्घhaul.bits.RevisionKey = दीर्घhaul.bits.RevisionID;
	अन्यथा
		दीर्घhaul.bits.RevisionKey = 0;
	दीर्घhaul.bits.SoftBusRatio = mults_index & 0xf;
	दीर्घhaul.bits.SoftBusRatio4 = (mults_index & 0x10) >> 4;
	/* Setup new voltage */
	अगर (can_scale_voltage)
		दीर्घhaul.bits.SoftVID = (mults_index >> 8) & 0x1f;
	/* Sync to समयr tick */
	safe_halt();
	/* Raise voltage अगर necessary */
	अगर (can_scale_voltage && dir) अणु
		दीर्घhaul.bits.EnableSoftVID = 1;
		wrmsrl(MSR_VIA_LONGHAUL, दीर्घhaul.val);
		/* Change voltage */
		अगर (!cx_address) अणु
			ACPI_FLUSH_CPU_CACHE();
			halt();
		पूर्ण अन्यथा अणु
			ACPI_FLUSH_CPU_CACHE();
			/* Invoke C3 */
			inb(cx_address);
			/* Dummy op - must करो something useless after P_LVL3
			 * पढ़ो */
			t = inl(acpi_gbl_FADT.xpm_समयr_block.address);
		पूर्ण
		दीर्घhaul.bits.EnableSoftVID = 0;
		wrmsrl(MSR_VIA_LONGHAUL, दीर्घhaul.val);
	पूर्ण

	/* Change frequency on next halt or sleep */
	दीर्घhaul.bits.EnableSoftBusRatio = 1;
	wrmsrl(MSR_VIA_LONGHAUL, दीर्घhaul.val);
	अगर (!cx_address) अणु
		ACPI_FLUSH_CPU_CACHE();
		halt();
	पूर्ण अन्यथा अणु
		ACPI_FLUSH_CPU_CACHE();
		/* Invoke C3 */
		inb(cx_address);
		/* Dummy op - must करो something useless after P_LVL3 पढ़ो */
		t = inl(acpi_gbl_FADT.xpm_समयr_block.address);
	पूर्ण
	/* Disable bus ratio bit */
	दीर्घhaul.bits.EnableSoftBusRatio = 0;
	wrmsrl(MSR_VIA_LONGHAUL, दीर्घhaul.val);

	/* Reduce voltage अगर necessary */
	अगर (can_scale_voltage && !dir) अणु
		दीर्घhaul.bits.EnableSoftVID = 1;
		wrmsrl(MSR_VIA_LONGHAUL, दीर्घhaul.val);
		/* Change voltage */
		अगर (!cx_address) अणु
			ACPI_FLUSH_CPU_CACHE();
			halt();
		पूर्ण अन्यथा अणु
			ACPI_FLUSH_CPU_CACHE();
			/* Invoke C3 */
			inb(cx_address);
			/* Dummy op - must करो something useless after P_LVL3
			 * पढ़ो */
			t = inl(acpi_gbl_FADT.xpm_समयr_block.address);
		पूर्ण
		दीर्घhaul.bits.EnableSoftVID = 0;
		wrmsrl(MSR_VIA_LONGHAUL, दीर्घhaul.val);
	पूर्ण
पूर्ण

/**
 * दीर्घhaul_set_cpu_frequency()
 * @mults_index : bitpattern of the new multiplier.
 *
 * Sets a new घड़ी ratio.
 */

अटल पूर्णांक दीर्घhaul_setstate(काष्ठा cpufreq_policy *policy,
		अचिन्हित पूर्णांक table_index)
अणु
	अचिन्हित पूर्णांक mults_index;
	पूर्णांक speed, mult;
	काष्ठा cpufreq_freqs freqs;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pic1_mask, pic2_mask;
	u16 bm_status = 0;
	u32 bm_समयout = 1000;
	अचिन्हित पूर्णांक dir = 0;

	mults_index = दीर्घhaul_table[table_index].driver_data;
	/* Safety precautions */
	mult = mults[mults_index & 0x1f];
	अगर (mult == -1)
		वापस -EINVAL;

	speed = calc_speed(mult);
	अगर ((speed > highest_speed) || (speed < lowest_speed))
		वापस -EINVAL;

	/* Voltage transition beक्रमe frequency transition? */
	अगर (can_scale_voltage && दीर्घhaul_index < table_index)
		dir = 1;

	freqs.old = calc_speed(दीर्घhaul_get_cpu_mult());
	freqs.new = speed;

	pr_debug("Setting to FSB:%dMHz Mult:%d.%dx (%s)\n",
			fsb, mult/10, mult%10, prपूर्णांक_speed(speed/1000));
retry_loop:
	preempt_disable();
	local_irq_save(flags);

	pic2_mask = inb(0xA1);
	pic1_mask = inb(0x21);	/* works on C3. save mask. */
	outb(0xFF, 0xA1);	/* Overसमाप्त */
	outb(0xFE, 0x21);	/* TMR0 only */

	/* Wait जबतक PCI bus is busy. */
	अगर (acpi_regs_addr && (दीर्घhaul_flags & USE_NORTHBRIDGE
	    || ((pr != शून्य) && pr->flags.bm_control))) अणु
		bm_status = inw(acpi_regs_addr);
		bm_status &= 1 << 4;
		जबतक (bm_status && bm_समयout) अणु
			outw(1 << 4, acpi_regs_addr);
			bm_समयout--;
			bm_status = inw(acpi_regs_addr);
			bm_status &= 1 << 4;
		पूर्ण
	पूर्ण

	अगर (दीर्घhaul_flags & USE_NORTHBRIDGE) अणु
		/* Disable AGP and PCI arbiters */
		outb(3, 0x22);
	पूर्ण अन्यथा अगर ((pr != शून्य) && pr->flags.bm_control) अणु
		/* Disable bus master arbitration */
		acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_ARB_DISABLE, 1);
	पूर्ण
	चयन (दीर्घhaul_version) अणु

	/*
	 * Longhaul v1. (Samuel[C5A] and Samuel2 stepping 0[C5B])
	 * Software controlled multipliers only.
	 */
	हाल TYPE_LONGHAUL_V1:
		करो_दीर्घhaul1(mults_index);
		अवरोध;

	/*
	 * Longhaul v2 appears in Samuel2 Steppings 1->7 [C5B] and Ezra [C5C]
	 *
	 * Longhaul v3 (aka Powersaver). (Ezra-T [C5M] & Nehemiah [C5N])
	 * Nehemiah can करो FSB scaling too, but this has never been proven
	 * to work in practice.
	 */
	हाल TYPE_LONGHAUL_V2:
	हाल TYPE_POWERSAVER:
		अगर (दीर्घhaul_flags & USE_ACPI_C3) अणु
			/* Don't allow wakeup */
			acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_BUS_MASTER_RLD, 0);
			करो_घातersaver(cx->address, mults_index, dir);
		पूर्ण अन्यथा अणु
			करो_घातersaver(0, mults_index, dir);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (दीर्घhaul_flags & USE_NORTHBRIDGE) अणु
		/* Enable arbiters */
		outb(0, 0x22);
	पूर्ण अन्यथा अगर ((pr != शून्य) && pr->flags.bm_control) अणु
		/* Enable bus master arbitration */
		acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_ARB_DISABLE, 0);
	पूर्ण
	outb(pic2_mask, 0xA1);	/* restore mask */
	outb(pic1_mask, 0x21);

	local_irq_restore(flags);
	preempt_enable();

	freqs.new = calc_speed(दीर्घhaul_get_cpu_mult());
	/* Check अगर requested frequency is set. */
	अगर (unlikely(freqs.new != speed)) अणु
		pr_info("Failed to set requested frequency!\n");
		/* Revision ID = 1 but processor is expecting revision key
		 * equal to 0. Jumpers at the bottom of processor will change
		 * multiplier and FSB, but will not change bits in Longhaul
		 * MSR nor enable voltage scaling. */
		अगर (!revid_errata) अणु
			pr_info("Enabling \"Ignore Revision ID\" option\n");
			revid_errata = 1;
			msleep(200);
			जाओ retry_loop;
		पूर्ण
		/* Why ACPI C3 someबार करोesn't work is a mystery क्रम me.
		 * But it करोes happen. Processor is entering ACPI C3 state,
		 * but it करोesn't change frequency. I tried poking various
		 * bits in northbridge रेजिस्टरs, but without success. */
		अगर (दीर्घhaul_flags & USE_ACPI_C3) अणु
			pr_info("Disabling ACPI C3 support\n");
			दीर्घhaul_flags &= ~USE_ACPI_C3;
			अगर (revid_errata) अणु
				pr_info("Disabling \"Ignore Revision ID\" option\n");
				revid_errata = 0;
			पूर्ण
			msleep(200);
			जाओ retry_loop;
		पूर्ण
		/* This shouldn't happen. Longhaul ver. 2 was reported not
		 * working on processors without voltage scaling, but with
		 * RevID = 1. RevID errata will make things right. Just
		 * to be 100% sure. */
		अगर (दीर्घhaul_version == TYPE_LONGHAUL_V2) अणु
			pr_info("Switching to Longhaul ver. 1\n");
			दीर्घhaul_version = TYPE_LONGHAUL_V1;
			msleep(200);
			जाओ retry_loop;
		पूर्ण
	पूर्ण

	अगर (!bm_समयout) अणु
		pr_info("Warning: Timeout while waiting for idle PCI bus\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Centaur decided to make lअगरe a little more tricky.
 * Only दीर्घhaul v1 is allowed to पढ़ो EBLCR BSEL[0:1].
 * Samuel2 and above have to try and guess what the FSB is.
 * We करो this by assuming we booted at maximum multiplier, and पूर्णांकerpolate
 * between that value multiplied by possible FSBs and cpu_mhz which
 * was calculated at boot समय. Really ugly, but no other way to करो this.
 */

#घोषणा ROUNDING	0xf

अटल पूर्णांक guess_fsb(पूर्णांक mult)
अणु
	पूर्णांक speed = cpu_khz / 1000;
	पूर्णांक i;
	पूर्णांक speeds[] = अणु 666, 1000, 1333, 2000 पूर्ण;
	पूर्णांक f_max, f_min;

	क्रम (i = 0; i < 4; i++) अणु
		f_max = ((speeds[i] * mult) + 50) / 100;
		f_max += (ROUNDING / 2);
		f_min = f_max - ROUNDING;
		अगर ((speed <= f_max) && (speed >= f_min))
			वापस speeds[i] / 10;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक दीर्घhaul_get_ranges(व्योम)
अणु
	अचिन्हित पूर्णांक i, j, k = 0;
	अचिन्हित पूर्णांक ratio;
	पूर्णांक mult;

	/* Get current frequency */
	mult = दीर्घhaul_get_cpu_mult();
	अगर (mult == -1) अणु
		pr_info("Invalid (reserved) multiplier!\n");
		वापस -EINVAL;
	पूर्ण
	fsb = guess_fsb(mult);
	अगर (fsb == 0) अणु
		pr_info("Invalid (reserved) FSB!\n");
		वापस -EINVAL;
	पूर्ण
	/* Get max multiplier - as we always did.
	 * Longhaul MSR is useful only when voltage scaling is enabled.
	 * C3 is booting at max anyway. */
	maxmult = mult;
	/* Get min multiplier */
	चयन (cpu_model) अणु
	हाल CPU_NEHEMIAH:
		minmult = 50;
		अवरोध;
	हाल CPU_NEHEMIAH_C:
		minmult = 40;
		अवरोध;
	शेष:
		minmult = 30;
		अवरोध;
	पूर्ण

	pr_debug("MinMult:%d.%dx MaxMult:%d.%dx\n",
		 minmult/10, minmult%10, maxmult/10, maxmult%10);

	highest_speed = calc_speed(maxmult);
	lowest_speed = calc_speed(minmult);
	pr_debug("FSB:%dMHz  Lowest speed: %s   Highest speed:%s\n", fsb,
		 prपूर्णांक_speed(lowest_speed/1000),
		 prपूर्णांक_speed(highest_speed/1000));

	अगर (lowest_speed == highest_speed) अणु
		pr_info("highestspeed == lowest, aborting\n");
		वापस -EINVAL;
	पूर्ण
	अगर (lowest_speed > highest_speed) अणु
		pr_info("nonsense! lowest (%d > %d) !\n",
			lowest_speed, highest_speed);
		वापस -EINVAL;
	पूर्ण

	दीर्घhaul_table = kसुस्मृति(numscales + 1, माप(*दीर्घhaul_table),
				 GFP_KERNEL);
	अगर (!दीर्घhaul_table)
		वापस -ENOMEM;

	क्रम (j = 0; j < numscales; j++) अणु
		ratio = mults[j];
		अगर (ratio == -1)
			जारी;
		अगर (ratio > maxmult || ratio < minmult)
			जारी;
		दीर्घhaul_table[k].frequency = calc_speed(ratio);
		दीर्घhaul_table[k].driver_data	= j;
		k++;
	पूर्ण
	अगर (k <= 1) अणु
		kमुक्त(दीर्घhaul_table);
		वापस -ENODEV;
	पूर्ण
	/* Sort */
	क्रम (j = 0; j < k - 1; j++) अणु
		अचिन्हित पूर्णांक min_f, min_i;
		min_f = दीर्घhaul_table[j].frequency;
		min_i = j;
		क्रम (i = j + 1; i < k; i++) अणु
			अगर (दीर्घhaul_table[i].frequency < min_f) अणु
				min_f = दीर्घhaul_table[i].frequency;
				min_i = i;
			पूर्ण
		पूर्ण
		अगर (min_i != j) अणु
			swap(दीर्घhaul_table[j].frequency,
			     दीर्घhaul_table[min_i].frequency);
			swap(दीर्घhaul_table[j].driver_data,
			     दीर्घhaul_table[min_i].driver_data);
		पूर्ण
	पूर्ण

	दीर्घhaul_table[k].frequency = CPUFREQ_TABLE_END;

	/* Find index we are running on */
	क्रम (j = 0; j < k; j++) अणु
		अगर (mults[दीर्घhaul_table[j].driver_data & 0x1f] == mult) अणु
			दीर्घhaul_index = j;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम दीर्घhaul_setup_voltagescaling(व्योम)
अणु
	काष्ठा cpufreq_frequency_table *freq_pos;
	जोड़ msr_दीर्घhaul दीर्घhaul;
	काष्ठा mV_pos minvid, maxvid, vid;
	अचिन्हित पूर्णांक j, speed, pos, kHz_step, numvscales;
	पूर्णांक min_vid_speed;

	rdmsrl(MSR_VIA_LONGHAUL, दीर्घhaul.val);
	अगर (!(दीर्घhaul.bits.RevisionID & 1)) अणु
		pr_info("Voltage scaling not supported by CPU\n");
		वापस;
	पूर्ण

	अगर (!दीर्घhaul.bits.VRMRev) अणु
		pr_info("VRM 8.5\n");
		vrm_mV_table = &vrm85_mV[0];
		mV_vrm_table = &mV_vrm85[0];
	पूर्ण अन्यथा अणु
		pr_info("Mobile VRM\n");
		अगर (cpu_model < CPU_NEHEMIAH)
			वापस;
		vrm_mV_table = &mobilevrm_mV[0];
		mV_vrm_table = &mV_mobilevrm[0];
	पूर्ण

	minvid = vrm_mV_table[दीर्घhaul.bits.MinimumVID];
	maxvid = vrm_mV_table[दीर्घhaul.bits.MaximumVID];

	अगर (minvid.mV == 0 || maxvid.mV == 0 || minvid.mV > maxvid.mV) अणु
		pr_info("Bogus values Min:%d.%03d Max:%d.%03d - Voltage scaling disabled\n",
			minvid.mV/1000, minvid.mV%1000,
			maxvid.mV/1000, maxvid.mV%1000);
		वापस;
	पूर्ण

	अगर (minvid.mV == maxvid.mV) अणु
		pr_info("Claims to support voltage scaling but min & max are both %d.%03d - Voltage scaling disabled\n",
			maxvid.mV/1000, maxvid.mV%1000);
		वापस;
	पूर्ण

	/* How many voltage steps*/
	numvscales = maxvid.pos - minvid.pos + 1;
	pr_info("Max VID=%d.%03d  Min VID=%d.%03d, %d possible voltage scales\n",
		maxvid.mV/1000, maxvid.mV%1000,
		minvid.mV/1000, minvid.mV%1000,
		numvscales);

	/* Calculate max frequency at min voltage */
	j = दीर्घhaul.bits.MinMHzBR;
	अगर (दीर्घhaul.bits.MinMHzBR4)
		j += 16;
	min_vid_speed = eblcr[j];
	अगर (min_vid_speed == -1)
		वापस;
	चयन (दीर्घhaul.bits.MinMHzFSB) अणु
	हाल 0:
		min_vid_speed *= 13333;
		अवरोध;
	हाल 1:
		min_vid_speed *= 10000;
		अवरोध;
	हाल 3:
		min_vid_speed *= 6666;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	अगर (min_vid_speed >= highest_speed)
		वापस;
	/* Calculate kHz क्रम one voltage step */
	kHz_step = (highest_speed - min_vid_speed) / numvscales;

	cpufreq_क्रम_each_entry_idx(freq_pos, दीर्घhaul_table, j) अणु
		speed = freq_pos->frequency;
		अगर (speed > min_vid_speed)
			pos = (speed - min_vid_speed) / kHz_step + minvid.pos;
		अन्यथा
			pos = minvid.pos;
		freq_pos->driver_data |= mV_vrm_table[pos] << 8;
		vid = vrm_mV_table[mV_vrm_table[pos]];
		pr_info("f: %d kHz, index: %d, vid: %d mV\n",
			speed, j, vid.mV);
	पूर्ण

	can_scale_voltage = 1;
	pr_info("Voltage scaling enabled\n");
पूर्ण


अटल पूर्णांक दीर्घhaul_target(काष्ठा cpufreq_policy *policy,
			    अचिन्हित पूर्णांक table_index)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक dir = 0;
	u8 vid, current_vid;
	पूर्णांक retval = 0;

	अगर (!can_scale_voltage)
		retval = दीर्घhaul_setstate(policy, table_index);
	अन्यथा अणु
		/* On test प्रणाली voltage transitions exceeding single
		 * step up or करोwn were turning motherboard off. Both
		 * "ondemand" and "userspace" are unsafe. C7 is करोing
		 * this in hardware, C3 is old and we need to करो this
		 * in software. */
		i = दीर्घhaul_index;
		current_vid = (दीर्घhaul_table[दीर्घhaul_index].driver_data >> 8);
		current_vid &= 0x1f;
		अगर (table_index > दीर्घhaul_index)
			dir = 1;
		जबतक (i != table_index) अणु
			vid = (दीर्घhaul_table[i].driver_data >> 8) & 0x1f;
			अगर (vid != current_vid) अणु
				retval = दीर्घhaul_setstate(policy, i);
				current_vid = vid;
				msleep(200);
			पूर्ण
			अगर (dir)
				i++;
			अन्यथा
				i--;
		पूर्ण
		retval = दीर्घhaul_setstate(policy, table_index);
	पूर्ण

	दीर्घhaul_index = table_index;
	वापस retval;
पूर्ण


अटल अचिन्हित पूर्णांक दीर्घhaul_get(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpu)
		वापस 0;
	वापस calc_speed(दीर्घhaul_get_cpu_mult());
पूर्ण

अटल acpi_status दीर्घhaul_walk_callback(acpi_handle obj_handle,
					  u32 nesting_level,
					  व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_device *d;

	अगर (acpi_bus_get_device(obj_handle, &d))
		वापस 0;

	*वापस_value = acpi_driver_data(d);
	वापस 1;
पूर्ण

/* VIA करोn't support PM2 reg, but have something similar */
अटल पूर्णांक enable_arbiter_disable(व्योम)
अणु
	काष्ठा pci_dev *dev;
	पूर्णांक status = 1;
	पूर्णांक reg;
	u8 pci_cmd;

	/* Find PLE133 host bridge */
	reg = 0x78;
	dev = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8601_0,
			     शून्य);
	/* Find PM133/VT8605 host bridge */
	अगर (dev == शून्य)
		dev = pci_get_device(PCI_VENDOR_ID_VIA,
				     PCI_DEVICE_ID_VIA_8605_0, शून्य);
	/* Find CLE266 host bridge */
	अगर (dev == शून्य) अणु
		reg = 0x76;
		dev = pci_get_device(PCI_VENDOR_ID_VIA,
				     PCI_DEVICE_ID_VIA_862X_0, शून्य);
		/* Find CN400 V-Link host bridge */
		अगर (dev == शून्य)
			dev = pci_get_device(PCI_VENDOR_ID_VIA, 0x7259, शून्य);
	पूर्ण
	अगर (dev != शून्य) अणु
		/* Enable access to port 0x22 */
		pci_पढ़ो_config_byte(dev, reg, &pci_cmd);
		अगर (!(pci_cmd & 1<<7)) अणु
			pci_cmd |= 1<<7;
			pci_ग_लिखो_config_byte(dev, reg, pci_cmd);
			pci_पढ़ो_config_byte(dev, reg, &pci_cmd);
			अगर (!(pci_cmd & 1<<7)) अणु
				pr_err("Can't enable access to port 0x22\n");
				status = 0;
			पूर्ण
		पूर्ण
		pci_dev_put(dev);
		वापस status;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक दीर्घhaul_setup_southbridge(व्योम)
अणु
	काष्ठा pci_dev *dev;
	u8 pci_cmd;

	/* Find VT8235 southbridge */
	dev = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8235, शून्य);
	अगर (dev == शून्य)
		/* Find VT8237 southbridge */
		dev = pci_get_device(PCI_VENDOR_ID_VIA,
				     PCI_DEVICE_ID_VIA_8237, शून्य);
	अगर (dev != शून्य) अणु
		/* Set transition समय to max */
		pci_पढ़ो_config_byte(dev, 0xec, &pci_cmd);
		pci_cmd &= ~(1 << 2);
		pci_ग_लिखो_config_byte(dev, 0xec, pci_cmd);
		pci_पढ़ो_config_byte(dev, 0xe4, &pci_cmd);
		pci_cmd &= ~(1 << 7);
		pci_ग_लिखो_config_byte(dev, 0xe4, pci_cmd);
		pci_पढ़ो_config_byte(dev, 0xe5, &pci_cmd);
		pci_cmd |= 1 << 7;
		pci_ग_लिखो_config_byte(dev, 0xe5, pci_cmd);
		/* Get address of ACPI रेजिस्टरs block*/
		pci_पढ़ो_config_byte(dev, 0x81, &pci_cmd);
		अगर (pci_cmd & 1 << 7) अणु
			pci_पढ़ो_config_dword(dev, 0x88, &acpi_regs_addr);
			acpi_regs_addr &= 0xff00;
			pr_info("ACPI I/O at 0x%x\n", acpi_regs_addr);
		पूर्ण

		pci_dev_put(dev);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक दीर्घhaul_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	अक्षर *cpuname = शून्य;
	पूर्णांक ret;
	u32 lo, hi;

	/* Check what we have on this motherboard */
	चयन (c->x86_model) अणु
	हाल 6:
		cpu_model = CPU_SAMUEL;
		cpuname = "C3 'Samuel' [C5A]";
		दीर्घhaul_version = TYPE_LONGHAUL_V1;
		स_नकल(mults, samuel1_mults, माप(samuel1_mults));
		स_नकल(eblcr, samuel1_eblcr, माप(samuel1_eblcr));
		अवरोध;

	हाल 7:
		चयन (c->x86_stepping) अणु
		हाल 0:
			दीर्घhaul_version = TYPE_LONGHAUL_V1;
			cpu_model = CPU_SAMUEL2;
			cpuname = "C3 'Samuel 2' [C5B]";
			/* Note, this is not a typo, early Samuel2's had
			 * Samuel1 ratios. */
			स_नकल(mults, samuel1_mults, माप(samuel1_mults));
			स_नकल(eblcr, samuel2_eblcr, माप(samuel2_eblcr));
			अवरोध;
		हाल 1 ... 15:
			दीर्घhaul_version = TYPE_LONGHAUL_V2;
			अगर (c->x86_stepping < 8) अणु
				cpu_model = CPU_SAMUEL2;
				cpuname = "C3 'Samuel 2' [C5B]";
			पूर्ण अन्यथा अणु
				cpu_model = CPU_EZRA;
				cpuname = "C3 'Ezra' [C5C]";
			पूर्ण
			स_नकल(mults, ezra_mults, माप(ezra_mults));
			स_नकल(eblcr, ezra_eblcr, माप(ezra_eblcr));
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 8:
		cpu_model = CPU_EZRA_T;
		cpuname = "C3 'Ezra-T' [C5M]";
		दीर्घhaul_version = TYPE_POWERSAVER;
		numscales = 32;
		स_नकल(mults, ezrat_mults, माप(ezrat_mults));
		स_नकल(eblcr, ezrat_eblcr, माप(ezrat_eblcr));
		अवरोध;

	हाल 9:
		दीर्घhaul_version = TYPE_POWERSAVER;
		numscales = 32;
		स_नकल(mults, nehemiah_mults, माप(nehemiah_mults));
		स_नकल(eblcr, nehemiah_eblcr, माप(nehemiah_eblcr));
		चयन (c->x86_stepping) अणु
		हाल 0 ... 1:
			cpu_model = CPU_NEHEMIAH;
			cpuname = "C3 'Nehemiah A' [C5XLOE]";
			अवरोध;
		हाल 2 ... 4:
			cpu_model = CPU_NEHEMIAH;
			cpuname = "C3 'Nehemiah B' [C5XLOH]";
			अवरोध;
		हाल 5 ... 15:
			cpu_model = CPU_NEHEMIAH_C;
			cpuname = "C3 'Nehemiah C' [C5P]";
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		cpuname = "Unknown";
		अवरोध;
	पूर्ण
	/* Check Longhaul ver. 2 */
	अगर (दीर्घhaul_version == TYPE_LONGHAUL_V2) अणु
		rdmsr(MSR_VIA_LONGHAUL, lo, hi);
		अगर (lo == 0 && hi == 0)
			/* Looks like MSR isn't present */
			दीर्घhaul_version = TYPE_LONGHAUL_V1;
	पूर्ण

	pr_info("VIA %s CPU detected.  ", cpuname);
	चयन (दीर्घhaul_version) अणु
	हाल TYPE_LONGHAUL_V1:
	हाल TYPE_LONGHAUL_V2:
		pr_cont("Longhaul v%d supported\n", दीर्घhaul_version);
		अवरोध;
	हाल TYPE_POWERSAVER:
		pr_cont("Powersaver supported\n");
		अवरोध;
	पूर्ण

	/* Doesn't hurt */
	दीर्घhaul_setup_southbridge();

	/* Find ACPI data क्रम processor */
	acpi_walk_namespace(ACPI_TYPE_PROCESSOR, ACPI_ROOT_OBJECT,
				ACPI_UINT32_MAX, &दीर्घhaul_walk_callback, शून्य,
				शून्य, (व्योम *)&pr);

	/* Check ACPI support क्रम C3 state */
	अगर (pr != शून्य && दीर्घhaul_version == TYPE_POWERSAVER) अणु
		cx = &pr->घातer.states[ACPI_STATE_C3];
		अगर (cx->address > 0 && cx->latency <= 1000)
			दीर्घhaul_flags |= USE_ACPI_C3;
	पूर्ण
	/* Disable अगर it isn't working */
	अगर (disable_acpi_c3)
		दीर्घhaul_flags &= ~USE_ACPI_C3;
	/* Check अगर northbridge is मित्रly */
	अगर (enable_arbiter_disable())
		दीर्घhaul_flags |= USE_NORTHBRIDGE;

	/* Check ACPI support क्रम bus master arbiter disable */
	अगर (!(दीर्घhaul_flags & USE_ACPI_C3
	     || दीर्घhaul_flags & USE_NORTHBRIDGE)
	    && ((pr == शून्य) || !(pr->flags.bm_control))) अणु
		pr_err("No ACPI support: Unsupported northbridge\n");
		वापस -ENODEV;
	पूर्ण

	अगर (दीर्घhaul_flags & USE_NORTHBRIDGE)
		pr_info("Using northbridge support\n");
	अगर (दीर्घhaul_flags & USE_ACPI_C3)
		pr_info("Using ACPI support\n");

	ret = दीर्घhaul_get_ranges();
	अगर (ret != 0)
		वापस ret;

	अगर ((दीर्घhaul_version != TYPE_LONGHAUL_V1) && (scale_voltage != 0))
		दीर्घhaul_setup_voltagescaling();

	policy->transition_delay_us = 200000;	/* usec */
	policy->freq_table = दीर्घhaul_table;

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver दीर्घhaul_driver = अणु
	.verअगरy	= cpufreq_generic_frequency_table_verअगरy,
	.target_index = दीर्घhaul_target,
	.get	= दीर्घhaul_get,
	.init	= दीर्घhaul_cpu_init,
	.name	= "longhaul",
	.attr	= cpufreq_generic_attr,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id दीर्घhaul_id[] = अणु
	X86_MATCH_VENDOR_FAM(CENTAUR, 6, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, दीर्घhaul_id);

अटल पूर्णांक __init दीर्घhaul_init(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);

	अगर (!x86_match_cpu(दीर्घhaul_id))
		वापस -ENODEV;

	अगर (!enable) अणु
		pr_err("Option \"enable\" not set - Aborting\n");
		वापस -ENODEV;
	पूर्ण
#अगर_घोषित CONFIG_SMP
	अगर (num_online_cpus() > 1) अणु
		pr_err("More than 1 CPU detected, longhaul disabled\n");
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_IO_APIC
	अगर (boot_cpu_has(X86_FEATURE_APIC)) अणु
		pr_err("APIC detected. Longhaul is currently broken in this configuration.\n");
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर
	चयन (c->x86_model) अणु
	हाल 6 ... 9:
		वापस cpufreq_रेजिस्टर_driver(&दीर्घhaul_driver);
	हाल 10:
		pr_err("Use acpi-cpufreq driver for VIA C7\n");
	शेष:
		;
	पूर्ण

	वापस -ENODEV;
पूर्ण


अटल व्योम __निकास दीर्घhaul_निकास(व्योम)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get(0);
	पूर्णांक i;

	क्रम (i = 0; i < numscales; i++) अणु
		अगर (mults[i] == maxmult) अणु
			काष्ठा cpufreq_freqs freqs;

			freqs.old = policy->cur;
			freqs.new = दीर्घhaul_table[i].frequency;
			freqs.flags = 0;

			cpufreq_freq_transition_begin(policy, &freqs);
			दीर्घhaul_setstate(policy, i);
			cpufreq_freq_transition_end(policy, &freqs, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	cpufreq_cpu_put(policy);
	cpufreq_unरेजिस्टर_driver(&दीर्घhaul_driver);
	kमुक्त(दीर्घhaul_table);
पूर्ण

/* Even अगर BIOS is exporting ACPI C3 state, and it is used
 * with success when CPU is idle, this state करोesn't
 * trigger frequency transition in some हालs. */
module_param(disable_acpi_c3, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_acpi_c3, "Don't use ACPI C3 support");
/* Change CPU voltage with frequency. Very useful to save
 * घातer, but most VIA C3 processors aren't supporting it. */
module_param(scale_voltage, पूर्णांक, 0644);
MODULE_PARM_DESC(scale_voltage, "Scale voltage of processor");
/* Force revision key to 0 क्रम processors which करोesn't
 * support voltage scaling, but are पूर्णांकroducing itself as
 * such. */
module_param(revid_errata, पूर्णांक, 0644);
MODULE_PARM_DESC(revid_errata, "Ignore CPU Revision ID");
/* By शेष driver is disabled to prevent incompatible
 * प्रणाली मुक्तze. */
module_param(enable, पूर्णांक, 0644);
MODULE_PARM_DESC(enable, "Enable driver");

MODULE_AUTHOR("Dave Jones");
MODULE_DESCRIPTION("Longhaul driver for VIA Cyrix processors.");
MODULE_LICENSE("GPL");

late_initcall(दीर्घhaul_init);
module_निकास(दीर्घhaul_निकास);
