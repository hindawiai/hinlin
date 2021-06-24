<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2002 - 2003 Dominik Broकरोwski <linux@broकरो.de>
 *
 *  Library क्रम common functions क्रम Intel SpeedStep v.1 and v.2 support
 *
 *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>

#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/tsc.h>
#समावेश "speedstep-lib.h"

#घोषणा PFX "speedstep-lib: "

#अगर_घोषित CONFIG_X86_SPEEDSTEP_RELAXED_CAP_CHECK
अटल पूर्णांक relaxed_check;
#अन्यथा
#घोषणा relaxed_check 0
#पूर्ण_अगर

/*********************************************************************
 *                   GET PROCESSOR CORE SPEED IN KHZ                 *
 *********************************************************************/

अटल अचिन्हित पूर्णांक pentium3_get_frequency(क्रमागत speedstep_processor processor)
अणु
	/* See table 14 of p3_ds.pdf and table 22 of 29834003.pdf */
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक ratio;	/* Frequency Multiplier (x10) */
		u8 biपंचांगap;		/* घातer on configuration bits
					[27, 25:22] (in MSR 0x2a) */
	पूर्ण msr_decode_mult[] = अणु
		अणु 30, 0x01 पूर्ण,
		अणु 35, 0x05 पूर्ण,
		अणु 40, 0x02 पूर्ण,
		अणु 45, 0x06 पूर्ण,
		अणु 50, 0x00 पूर्ण,
		अणु 55, 0x04 पूर्ण,
		अणु 60, 0x0b पूर्ण,
		अणु 65, 0x0f पूर्ण,
		अणु 70, 0x09 पूर्ण,
		अणु 75, 0x0d पूर्ण,
		अणु 80, 0x0a पूर्ण,
		अणु 85, 0x26 पूर्ण,
		अणु 90, 0x20 पूर्ण,
		अणु 100, 0x2b पूर्ण,
		अणु 0, 0xff पूर्ण	/* error or unknown value */
	पूर्ण;

	/* PIII(-M) FSB settings: see table b1-b of 24547206.pdf */
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक value;	/* Front Side Bus speed in MHz */
		u8 biपंचांगap;		/* घातer on configuration bits [18: 19]
					(in MSR 0x2a) */
	पूर्ण msr_decode_fsb[] = अणु
		अणु  66, 0x0 पूर्ण,
		अणु 100, 0x2 पूर्ण,
		अणु 133, 0x1 पूर्ण,
		अणु   0, 0xffपूर्ण
	पूर्ण;

	u32 msr_lo, msr_पंचांगp;
	पूर्णांक i = 0, j = 0;

	/* पढ़ो MSR 0x2a - we only need the low 32 bits */
	rdmsr(MSR_IA32_EBL_CR_POWERON, msr_lo, msr_पंचांगp);
	pr_debug("P3 - MSR_IA32_EBL_CR_POWERON: 0x%x 0x%x\n", msr_lo, msr_पंचांगp);
	msr_पंचांगp = msr_lo;

	/* decode the FSB */
	msr_पंचांगp &= 0x00c0000;
	msr_पंचांगp >>= 18;
	जबतक (msr_पंचांगp != msr_decode_fsb[i].biपंचांगap) अणु
		अगर (msr_decode_fsb[i].biपंचांगap == 0xff)
			वापस 0;
		i++;
	पूर्ण

	/* decode the multiplier */
	अगर (processor == SPEEDSTEP_CPU_PIII_C_EARLY) अणु
		pr_debug("workaround for early PIIIs\n");
		msr_lo &= 0x03c00000;
	पूर्ण अन्यथा
		msr_lo &= 0x0bc00000;
	msr_lo >>= 22;
	जबतक (msr_lo != msr_decode_mult[j].biपंचांगap) अणु
		अगर (msr_decode_mult[j].biपंचांगap == 0xff)
			वापस 0;
		j++;
	पूर्ण

	pr_debug("speed is %u\n",
		(msr_decode_mult[j].ratio * msr_decode_fsb[i].value * 100));

	वापस msr_decode_mult[j].ratio * msr_decode_fsb[i].value * 100;
पूर्ण


अटल अचिन्हित पूर्णांक pentiumM_get_frequency(व्योम)
अणु
	u32 msr_lo, msr_पंचांगp;

	rdmsr(MSR_IA32_EBL_CR_POWERON, msr_lo, msr_पंचांगp);
	pr_debug("PM - MSR_IA32_EBL_CR_POWERON: 0x%x 0x%x\n", msr_lo, msr_पंचांगp);

	/* see table B-2 of 24547212.pdf */
	अगर (msr_lo & 0x00040000) अणु
		prपूर्णांकk(KERN_DEBUG PFX "PM - invalid FSB: 0x%x 0x%x\n",
				msr_lo, msr_पंचांगp);
		वापस 0;
	पूर्ण

	msr_पंचांगp = (msr_lo >> 22) & 0x1f;
	pr_debug("bits 22-26 are 0x%x, speed is %u\n",
			msr_पंचांगp, (msr_पंचांगp * 100 * 1000));

	वापस msr_पंचांगp * 100 * 1000;
पूर्ण

अटल अचिन्हित पूर्णांक pentium_core_get_frequency(व्योम)
अणु
	u32 fsb = 0;
	u32 msr_lo, msr_पंचांगp;
	पूर्णांक ret;

	rdmsr(MSR_FSB_FREQ, msr_lo, msr_पंचांगp);
	/* see table B-2 of 25366920.pdf */
	चयन (msr_lo & 0x07) अणु
	हाल 5:
		fsb = 100000;
		अवरोध;
	हाल 1:
		fsb = 133333;
		अवरोध;
	हाल 3:
		fsb = 166667;
		अवरोध;
	हाल 2:
		fsb = 200000;
		अवरोध;
	हाल 0:
		fsb = 266667;
		अवरोध;
	हाल 4:
		fsb = 333333;
		अवरोध;
	शेष:
		pr_err("PCORE - MSR_FSB_FREQ undefined value\n");
	पूर्ण

	rdmsr(MSR_IA32_EBL_CR_POWERON, msr_lo, msr_पंचांगp);
	pr_debug("PCORE - MSR_IA32_EBL_CR_POWERON: 0x%x 0x%x\n",
			msr_lo, msr_पंचांगp);

	msr_पंचांगp = (msr_lo >> 22) & 0x1f;
	pr_debug("bits 22-26 are 0x%x, speed is %u\n",
			msr_पंचांगp, (msr_पंचांगp * fsb));

	ret = (msr_पंचांगp * fsb);
	वापस ret;
पूर्ण


अटल अचिन्हित पूर्णांक pentium4_get_frequency(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;
	u32 msr_lo, msr_hi, mult;
	अचिन्हित पूर्णांक fsb = 0;
	अचिन्हित पूर्णांक ret;
	u8 fsb_code;

	/* Pentium 4 Model 0 and 1 करो not have the Core Clock Frequency
	 * to System Bus Frequency Ratio Field in the Processor Frequency
	 * Configuration Register of the MSR. Thereक्रमe the current
	 * frequency cannot be calculated and has to be measured.
	 */
	अगर (c->x86_model < 2)
		वापस cpu_khz;

	rdmsr(0x2c, msr_lo, msr_hi);

	pr_debug("P4 - MSR_EBC_FREQUENCY_ID: 0x%x 0x%x\n", msr_lo, msr_hi);

	/* decode the FSB: see IA-32 Intel (C) Architecture Software
	 * Developer's Manual, Volume 3: System Prgramming Guide,
	 * revision #12 in Table B-1: MSRs in the Pentium 4 and
	 * Intel Xeon Processors, on page B-4 and B-5.
	 */
	fsb_code = (msr_lo >> 16) & 0x7;
	चयन (fsb_code) अणु
	हाल 0:
		fsb = 100 * 1000;
		अवरोध;
	हाल 1:
		fsb = 13333 * 10;
		अवरोध;
	हाल 2:
		fsb = 200 * 1000;
		अवरोध;
	पूर्ण

	अगर (!fsb)
		prपूर्णांकk(KERN_DEBUG PFX "couldn't detect FSB speed. "
				"Please send an e-mail to <linux@brodo.de>\n");

	/* Multiplier. */
	mult = msr_lo >> 24;

	pr_debug("P4 - FSB %u kHz; Multiplier %u; Speed %u kHz\n",
			fsb, mult, (fsb * mult));

	ret = (fsb * mult);
	वापस ret;
पूर्ण


/* Warning: may get called from smp_call_function_single. */
अचिन्हित पूर्णांक speedstep_get_frequency(क्रमागत speedstep_processor processor)
अणु
	चयन (processor) अणु
	हाल SPEEDSTEP_CPU_PCORE:
		वापस pentium_core_get_frequency();
	हाल SPEEDSTEP_CPU_PM:
		वापस pentiumM_get_frequency();
	हाल SPEEDSTEP_CPU_P4D:
	हाल SPEEDSTEP_CPU_P4M:
		वापस pentium4_get_frequency();
	हाल SPEEDSTEP_CPU_PIII_T:
	हाल SPEEDSTEP_CPU_PIII_C:
	हाल SPEEDSTEP_CPU_PIII_C_EARLY:
		वापस pentium3_get_frequency(processor);
	शेष:
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(speedstep_get_frequency);


/*********************************************************************
 *                 DETECT SPEEDSTEP-CAPABLE PROCESSOR                *
 *********************************************************************/

/* Keep in sync with the x86_cpu_id tables in the dअगरferent modules */
क्रमागत speedstep_processor speedstep_detect_processor(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	u32 ebx, msr_lo, msr_hi;

	pr_debug("x86: %x, model: %x\n", c->x86, c->x86_model);

	अगर ((c->x86_venकरोr != X86_VENDOR_INTEL) ||
	    ((c->x86 != 6) && (c->x86 != 0xF)))
		वापस 0;

	अगर (c->x86 == 0xF) अणु
		/* Intel Mobile Pentium 4-M
		 * or Intel Mobile Pentium 4 with 533 MHz FSB */
		अगर (c->x86_model != 2)
			वापस 0;

		ebx = cpuid_ebx(0x00000001);
		ebx &= 0x000000FF;

		pr_debug("ebx value is %x, x86_stepping is %x\n", ebx, c->x86_stepping);

		चयन (c->x86_stepping) अणु
		हाल 4:
			/*
			 * B-stepping [M-P4-M]
			 * sample has ebx = 0x0f, production has 0x0e.
			 */
			अगर ((ebx == 0x0e) || (ebx == 0x0f))
				वापस SPEEDSTEP_CPU_P4M;
			अवरोध;
		हाल 7:
			/*
			 * C-stepping [M-P4-M]
			 * needs to have ebx=0x0e, अन्यथा it's a celeron:
			 * cf. 25130917.pdf / page 7, footnote 5 even
			 * though 25072120.pdf / page 7 करोesn't say
			 * samples are only of B-stepping...
			 */
			अगर (ebx == 0x0e)
				वापस SPEEDSTEP_CPU_P4M;
			अवरोध;
		हाल 9:
			/*
			 * D-stepping [M-P4-M or M-P4/533]
			 *
			 * this is totally strange: CPUID 0x0F29 is
			 * used by M-P4-M, M-P4/533 and(!) Celeron CPUs.
			 * The latter need to be sorted out as they करोn't
			 * support speedstep.
			 * Celerons with CPUID 0x0F29 may have either
			 * ebx=0x8 or 0xf -- 25130917.pdf करोesn't say anything
			 * specअगरic.
			 * M-P4-Ms may have either ebx=0xe or 0xf [see above]
			 * M-P4/533 have either ebx=0xe or 0xf. [25317607.pdf]
			 * also, M-P4M HTs have ebx=0x8, too
			 * For now, they are distinguished by the model_id
			 * string
			 */
			अगर ((ebx == 0x0e) ||
				(म_माला(c->x86_model_id,
				    "Mobile Intel(R) Pentium(R) 4") != शून्य))
				वापस SPEEDSTEP_CPU_P4M;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण

	चयन (c->x86_model) अणु
	हाल 0x0B: /* Intel PIII [Tualatin] */
		/* cpuid_ebx(1) is 0x04 क्रम desktop PIII,
		 * 0x06 क्रम mobile PIII-M */
		ebx = cpuid_ebx(0x00000001);
		pr_debug("ebx is %x\n", ebx);

		ebx &= 0x000000FF;

		अगर (ebx != 0x06)
			वापस 0;

		/* So far all PIII-M processors support SpeedStep. See
		 * Intel's 24540640.pdf of June 2003
		 */
		वापस SPEEDSTEP_CPU_PIII_T;

	हाल 0x08: /* Intel PIII [Coppermine] */

		/* all mobile PIII Coppermines have FSB 100 MHz
		 * ==> sort out a few desktop PIIIs. */
		rdmsr(MSR_IA32_EBL_CR_POWERON, msr_lo, msr_hi);
		pr_debug("Coppermine: MSR_IA32_EBL_CR_POWERON is 0x%x, 0x%x\n",
				msr_lo, msr_hi);
		msr_lo &= 0x00c0000;
		अगर (msr_lo != 0x0080000)
			वापस 0;

		/*
		 * If the processor is a mobile version,
		 * platक्रमm ID has bit 50 set
		 * it has SpeedStep technology अगर either
		 * bit 56 or 57 is set
		 */
		rdmsr(MSR_IA32_PLATFORM_ID, msr_lo, msr_hi);
		pr_debug("Coppermine: MSR_IA32_PLATFORM ID is 0x%x, 0x%x\n",
				msr_lo, msr_hi);
		अगर ((msr_hi & (1<<18)) &&
		    (relaxed_check ? 1 : (msr_hi & (3<<24)))) अणु
			अगर (c->x86_stepping == 0x01) अणु
				pr_debug("early PIII version\n");
				वापस SPEEDSTEP_CPU_PIII_C_EARLY;
			पूर्ण अन्यथा
				वापस SPEEDSTEP_CPU_PIII_C;
		पूर्ण
		fallthrough;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(speedstep_detect_processor);


/*********************************************************************
 *                     DETECT SPEEDSTEP SPEEDS                       *
 *********************************************************************/

अचिन्हित पूर्णांक speedstep_get_freqs(क्रमागत speedstep_processor processor,
				  अचिन्हित पूर्णांक *low_speed,
				  अचिन्हित पूर्णांक *high_speed,
				  अचिन्हित पूर्णांक *transition_latency,
				  व्योम (*set_state) (अचिन्हित पूर्णांक state))
अणु
	अचिन्हित पूर्णांक prev_speed;
	अचिन्हित पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार tv1, tv2;

	अगर ((!processor) || (!low_speed) || (!high_speed) || (!set_state))
		वापस -EINVAL;

	pr_debug("trying to determine both speeds\n");

	/* get current speed */
	prev_speed = speedstep_get_frequency(processor);
	अगर (!prev_speed)
		वापस -EIO;

	pr_debug("previous speed is %u\n", prev_speed);

	preempt_disable();
	local_irq_save(flags);

	/* चयन to low state */
	set_state(SPEEDSTEP_LOW);
	*low_speed = speedstep_get_frequency(processor);
	अगर (!*low_speed) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	pr_debug("low speed is %u\n", *low_speed);

	/* start latency measurement */
	अगर (transition_latency)
		tv1 = kसमय_get();

	/* चयन to high state */
	set_state(SPEEDSTEP_HIGH);

	/* end latency measurement */
	अगर (transition_latency)
		tv2 = kसमय_get();

	*high_speed = speedstep_get_frequency(processor);
	अगर (!*high_speed) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	pr_debug("high speed is %u\n", *high_speed);

	अगर (*low_speed == *high_speed) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* चयन to previous state, अगर necessary */
	अगर (*high_speed != prev_speed)
		set_state(SPEEDSTEP_LOW);

	अगर (transition_latency) अणु
		*transition_latency = kसमय_प्रकारo_us(kसमय_sub(tv2, tv1));
		pr_debug("transition latency is %u uSec\n", *transition_latency);

		/* convert uSec to nSec and add 20% क्रम safety reasons */
		*transition_latency *= 1200;

		/* check अगर the latency measurement is too high or too low
		 * and set it to a safe value (500uSec) in that हाल
		 */
		अगर (*transition_latency > 10000000 ||
		    *transition_latency < 50000) अणु
			pr_warn("frequency transition measured seems out of range (%u nSec), falling back to a safe one of %u nSec\n",
				*transition_latency, 500000);
			*transition_latency = 500000;
		पूर्ण
	पूर्ण

out:
	local_irq_restore(flags);
	preempt_enable();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(speedstep_get_freqs);

#अगर_घोषित CONFIG_X86_SPEEDSTEP_RELAXED_CAP_CHECK
module_param(relaxed_check, पूर्णांक, 0444);
MODULE_PARM_DESC(relaxed_check,
		"Don't do all checks for speedstep capability.");
#पूर्ण_अगर

MODULE_AUTHOR("Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("Library for Intel SpeedStep 1 or 2 cpufreq drivers.");
MODULE_LICENSE("GPL");
