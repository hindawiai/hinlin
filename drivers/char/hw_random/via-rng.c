<शैली गुरु>
/*
 * RNG driver क्रम VIA RNGs
 *
 * Copyright 2005 (c) MontaVista Software, Inc.
 *
 * with the majority of the code coming from:
 *
 * Hardware driver क्रम the Intel/AMD/VIA Ranकरोm Number Generators (RNG)
 * (c) Copyright 2003 Red Hat Inc <jgarzik@redhat.com>
 *
 * derived from
 *
 * Hardware driver क्रम the AMD 768 Ranकरोm Number Generator (RNG)
 * (c) Copyright 2001 Red Hat Inc
 *
 * derived from
 *
 * Hardware driver क्रम Intel i810 Ranकरोm Number Generator (RNG)
 * Copyright 2000,2001 Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2000,2001 Philipp Rumpf <prumpf@mandrakesoft.com>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <crypto/padlock.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/fpu/api.h>




क्रमागत अणु
	VIA_STRFILT_CNT_SHIFT	= 16,
	VIA_STRFILT_FAIL	= (1 << 15),
	VIA_STRFILT_ENABLE	= (1 << 14),
	VIA_RAWBITS_ENABLE	= (1 << 13),
	VIA_RNG_ENABLE		= (1 << 6),
	VIA_NOISESRC1		= (1 << 8),
	VIA_NOISESRC2		= (1 << 9),
	VIA_XSTORE_CNT_MASK	= 0x0F,

	VIA_RNG_CHUNK_8		= 0x00,	/* 64 अक्रम bits, 64 stored bits */
	VIA_RNG_CHUNK_4		= 0x01,	/* 32 अक्रम bits, 32 stored bits */
	VIA_RNG_CHUNK_4_MASK	= 0xFFFFFFFF,
	VIA_RNG_CHUNK_2		= 0x02,	/* 16 अक्रम bits, 32 stored bits */
	VIA_RNG_CHUNK_2_MASK	= 0xFFFF,
	VIA_RNG_CHUNK_1		= 0x03,	/* 8 अक्रम bits, 32 stored bits */
	VIA_RNG_CHUNK_1_MASK	= 0xFF,
पूर्ण;

/*
 * Investigate using the 'rep' prefix to obtain 32 bits of अक्रमom data
 * in one insn.  The upside is potentially better perक्रमmance.  The
 * करोwnside is that the inकाष्ठाion becomes no दीर्घer atomic.  Due to
 * this, just like familiar issues with /dev/अक्रमom itself, the worst
 * हाल of a 'rep xstore' could potentially छोड़ो a cpu क्रम an
 * unreasonably दीर्घ समय.  In practice, this condition would likely
 * only occur when the hardware is failing.  (or so we hope :))
 *
 * Another possible perक्रमmance boost may come from simply buffering
 * until we have 4 bytes, thus वापसing a u32 at a समय,
 * instead of the current u8-at-a-समय.
 *
 * Padlock inकाष्ठाions can generate a spurious DNA fault, but the
 * kernel करोesn't use CR0.TS, so this doesn't matter.
 */

अटल अंतरभूत u32 xstore(u32 *addr, u32 edx_in)
अणु
	u32 eax_out;

	यंत्र(".byte 0x0F,0xA7,0xC0 /* xstore %%edi (addr=%0) */"
		: "=m" (*addr), "=a" (eax_out), "+d" (edx_in), "+D" (addr));

	वापस eax_out;
पूर्ण

अटल पूर्णांक via_rng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	अक्षर buf[16 + PADLOCK_ALIGNMENT - STACK_ALIGN] __attribute__
		((aligned(STACK_ALIGN)));
	u32 *via_rng_datum = (u32 *)PTR_ALIGN(&buf[0], PADLOCK_ALIGNMENT);
	u32 bytes_out;
	पूर्णांक i;

	/* We choose the recommended 1-byte-per-inकाष्ठाion RNG rate,
	 * क्रम greater अक्रमomness at the expense of speed.  Larger
	 * values 2, 4, or 8 bytes-per-inकाष्ठाion yield greater
	 * speed at lesser अक्रमomness.
	 *
	 * If you change this to another VIA_CHUNK_n, you must also
	 * change the ->n_bytes values in rng_venकरोr_ops[] tables.
	 * VIA_CHUNK_8 requires further code changes.
	 *
	 * A copy of MSR_VIA_RNG is placed in eax_out when xstore
	 * completes.
	 */

	क्रम (i = 0; i < 20; i++) अणु
		*via_rng_datum = 0; /* paranoia, not really necessary */
		bytes_out = xstore(via_rng_datum, VIA_RNG_CHUNK_1);
		bytes_out &= VIA_XSTORE_CNT_MASK;
		अगर (bytes_out || !रुको)
			अवरोध;
		udelay(10);
	पूर्ण
	rng->priv = *via_rng_datum;
	वापस bytes_out ? 1 : 0;
पूर्ण

अटल पूर्णांक via_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	u32 via_rng_datum = (u32)rng->priv;

	*data = via_rng_datum;

	वापस 1;
पूर्ण

अटल पूर्णांक via_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	u32 lo, hi, old_lo;

	/* VIA Nano CPUs करोn't have the MSR_VIA_RNG anymore.  The RNG
	 * is always enabled अगर CPUID rng_en is set.  There is no
	 * RNG configuration like it used to be the हाल in this
	 * रेजिस्टर */
	अगर (((c->x86 == 6) && (c->x86_model >= 0x0f))  || (c->x86 > 6))अणु
		अगर (!boot_cpu_has(X86_FEATURE_XSTORE_EN)) अणु
			pr_err(PFX "can't enable hardware RNG "
				"if XSTORE is not enabled\n");
			वापस -ENODEV;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Control the RNG via MSR.  Tपढ़ो lightly and pay very बंद
	 * बंद attention to values written, as the reserved fields
	 * are करोcumented to be "undefined and unpredictable"; but it
	 * करोes not say to ग_लिखो them as zero, so I make a guess that
	 * we restore the values we find in the रेजिस्टर.
	 */
	rdmsr(MSR_VIA_RNG, lo, hi);

	old_lo = lo;
	lo &= ~(0x7f << VIA_STRFILT_CNT_SHIFT);
	lo &= ~VIA_XSTORE_CNT_MASK;
	lo &= ~(VIA_STRFILT_ENABLE | VIA_STRFILT_FAIL | VIA_RAWBITS_ENABLE);
	lo |= VIA_RNG_ENABLE;
	lo |= VIA_NOISESRC1;

	/* Enable secondary noise source on CPUs where it is present. */

	/* Nehemiah stepping 8 and higher */
	अगर ((c->x86_model == 9) && (c->x86_stepping > 7))
		lo |= VIA_NOISESRC2;

	/* Esther */
	अगर (c->x86_model >= 10)
		lo |= VIA_NOISESRC2;

	अगर (lo != old_lo)
		wrmsr(MSR_VIA_RNG, lo, hi);

	/* perhaps-unnecessary sanity check; हटाओ after testing अगर
	   unneeded */
	rdmsr(MSR_VIA_RNG, lo, hi);
	अगर ((lo & VIA_RNG_ENABLE) == 0) अणु
		pr_err(PFX "cannot enable VIA C3 RNG, aborting\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण


अटल काष्ठा hwrng via_rng = अणु
	.name		= "via",
	.init		= via_rng_init,
	.data_present	= via_rng_data_present,
	.data_पढ़ो	= via_rng_data_पढ़ो,
पूर्ण;


अटल पूर्णांक __init mod_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!boot_cpu_has(X86_FEATURE_XSTORE))
		वापस -ENODEV;

	pr_info("VIA RNG detected\n");
	err = hwrng_रेजिस्टर(&via_rng);
	अगर (err) अणु
		pr_err(PFX "RNG registering failed (%d)\n",
		       err);
		जाओ out;
	पूर्ण
out:
	वापस err;
पूर्ण
module_init(mod_init);

अटल व्योम __निकास mod_निकास(व्योम)
अणु
	hwrng_unरेजिस्टर(&via_rng);
पूर्ण
module_निकास(mod_निकास);

अटल काष्ठा x86_cpu_id __maybe_unused via_rng_cpu_id[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_XSTORE, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, via_rng_cpu_id);

MODULE_DESCRIPTION("H/W RNG driver for VIA CPU with PadLock");
MODULE_LICENSE("GPL");
