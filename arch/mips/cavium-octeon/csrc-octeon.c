<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007 by Ralf Baechle
 * Copyright (C) 2009, 2012 Cavium, Inc.
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/समय.स>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-ipd-defs.h>
#समावेश <यंत्र/octeon/cvmx-mio-defs.h>
#समावेश <यंत्र/octeon/cvmx-rst-defs.h>
#समावेश <यंत्र/octeon/cvmx-fpa-defs.h>

अटल u64 f;
अटल u64 rभाग;
अटल u64 sभाग;
अटल u64 octeon_udelay_factor;
अटल u64 octeon_ndelay_factor;

व्योम __init octeon_setup_delays(व्योम)
अणु
	octeon_udelay_factor = octeon_get_घड़ी_rate() / 1000000;
	/*
	 * For __ndelay we भागide by 2^16, so the factor is multiplied
	 * by the same amount.
	 */
	octeon_ndelay_factor = (octeon_udelay_factor * 0x10000ull) / 1000ull;

	preset_lpj = octeon_get_घड़ी_rate() / HZ;

	अगर (current_cpu_type() == CPU_CAVIUM_OCTEON2) अणु
		जोड़ cvmx_mio_rst_boot rst_boot;

		rst_boot.u64 = cvmx_पढ़ो_csr(CVMX_MIO_RST_BOOT);
		rभाग = rst_boot.s.c_mul;	/* CPU घड़ी */
		sभाग = rst_boot.s.pnr_mul;	/* I/O घड़ी */
		f = (0x8000000000000000ull / sभाग) * 2;
	पूर्ण अन्यथा अगर (current_cpu_type() == CPU_CAVIUM_OCTEON3) अणु
		जोड़ cvmx_rst_boot rst_boot;

		rst_boot.u64 = cvmx_पढ़ो_csr(CVMX_RST_BOOT);
		rभाग = rst_boot.s.c_mul;	/* CPU घड़ी */
		sभाग = rst_boot.s.pnr_mul;	/* I/O घड़ी */
		f = (0x8000000000000000ull / sभाग) * 2;
	पूर्ण

पूर्ण

/*
 * Set the current core's cvmcount counter to the value of the
 * IPD_CLK_COUNT.  We करो this on all cores as they are brought
 * on-line.  This allows क्रम a पढ़ो from a local cpu रेजिस्टर to
 * access a synchronized counter.
 *
 * On CPU_CAVIUM_OCTEON2 the IPD_CLK_COUNT is scaled by rभाग/sभाग.
 */
व्योम octeon_init_cvmcount(व्योम)
अणु
	u64 clk_reg;
	अचिन्हित दीर्घ flags;
	अचिन्हित loops = 2;

	clk_reg = octeon_has_feature(OCTEON_FEATURE_FPA3) ?
		CVMX_FPA_CLK_COUNT : CVMX_IPD_CLK_COUNT;

	/* Clobber loops so GCC will not unroll the following जबतक loop. */
	यंत्र("" : "+r" (loops));

	local_irq_save(flags);
	/*
	 * Loop several बार so we are executing from the cache,
	 * which should give more deterministic timing.
	 */
	जबतक (loops--) अणु
		u64 clk_count = cvmx_पढ़ो_csr(clk_reg);
		अगर (rभाग != 0) अणु
			clk_count *= rभाग;
			अगर (f != 0) अणु
				यंत्र("dmultu\t%[cnt],%[f]\n\t"
				    "mfhi\t%[cnt]"
				    : [cnt] "+r" (clk_count)
				    : [f] "r" (f)
				    : "hi", "lo");
			पूर्ण
		पूर्ण
		ग_लिखो_c0_cvmcount(clk_count);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल u64 octeon_cvmcount_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस पढ़ो_c0_cvmcount();
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_mips = अणु
	.name		= "OCTEON_CVMCOUNT",
	.पढ़ो		= octeon_cvmcount_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अचिन्हित दीर्घ दीर्घ notrace sched_घड़ी(व्योम)
अणु
	/* 64-bit arithmatic can overflow, so use 128-bit.  */
	u64 t1, t2, t3;
	अचिन्हित दीर्घ दीर्घ rv;
	u64 mult = घड़ीsource_mips.mult;
	u64 shअगरt = घड़ीsource_mips.shअगरt;
	u64 cnt = पढ़ो_c0_cvmcount();

	यंत्र (
		"dmultu\t%[cnt],%[mult]\n\t"
		"nor\t%[t1],$0,%[shift]\n\t"
		"mfhi\t%[t2]\n\t"
		"mflo\t%[t3]\n\t"
		"dsll\t%[t2],%[t2],1\n\t"
		"dsrlv\t%[rv],%[t3],%[shift]\n\t"
		"dsllv\t%[t1],%[t2],%[t1]\n\t"
		"or\t%[rv],%[t1],%[rv]\n\t"
		: [rv] "=&r" (rv), [t1] "=&r" (t1), [t2] "=&r" (t2), [t3] "=&r" (t3)
		: [cnt] "r" (cnt), [mult] "r" (mult), [shअगरt] "r" (shअगरt)
		: "hi", "lo");
	वापस rv;
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	घड़ीsource_mips.rating = 300;
	घड़ीsource_रेजिस्टर_hz(&घड़ीsource_mips, octeon_get_घड़ी_rate());
पूर्ण

व्योम __udelay(अचिन्हित दीर्घ us)
अणु
	u64 cur, end, inc;

	cur = पढ़ो_c0_cvmcount();

	inc = us * octeon_udelay_factor;
	end = cur + inc;

	जबतक (end > cur)
		cur = पढ़ो_c0_cvmcount();
पूर्ण
EXPORT_SYMBOL(__udelay);

व्योम __ndelay(अचिन्हित दीर्घ ns)
अणु
	u64 cur, end, inc;

	cur = पढ़ो_c0_cvmcount();

	inc = ((ns * octeon_ndelay_factor) >> 16);
	end = cur + inc;

	जबतक (end > cur)
		cur = पढ़ो_c0_cvmcount();
पूर्ण
EXPORT_SYMBOL(__ndelay);

व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	u64 cur, end;

	cur = पढ़ो_c0_cvmcount();
	end = cur + loops;

	जबतक (end > cur)
		cur = पढ़ो_c0_cvmcount();
पूर्ण
EXPORT_SYMBOL(__delay);


/**
 * octeon_io_clk_delay - रुको क्रम a given number of io घड़ी cycles to pass.
 *
 * We scale the रुको by the घड़ी ratio, and then रुको क्रम the
 * corresponding number of core घड़ीs.
 *
 * @count: The number of घड़ीs to रुको.
 */
व्योम octeon_io_clk_delay(अचिन्हित दीर्घ count)
अणु
	u64 cur, end;

	cur = पढ़ो_c0_cvmcount();
	अगर (rभाग != 0) अणु
		end = count * rभाग;
		अगर (f != 0) अणु
			यंत्र("dmultu\t%[cnt],%[f]\n\t"
				"mfhi\t%[cnt]"
				: [cnt] "+r" (end)
				: [f] "r" (f)
				: "hi", "lo");
		पूर्ण
		end = cur + end;
	पूर्ण अन्यथा अणु
		end = cur + count;
	पूर्ण
	जबतक (end > cur)
		cur = पढ़ो_c0_cvmcount();
पूर्ण
EXPORT_SYMBOL(octeon_io_clk_delay);
