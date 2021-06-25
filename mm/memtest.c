<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>

अटल u64 patterns[] __initdata = अणु
	/* The first entry has to be 0 to leave memtest with zeroed memory */
	0,
	0xffffffffffffffffULL,
	0x5555555555555555ULL,
	0xaaaaaaaaaaaaaaaaULL,
	0x1111111111111111ULL,
	0x2222222222222222ULL,
	0x4444444444444444ULL,
	0x8888888888888888ULL,
	0x3333333333333333ULL,
	0x6666666666666666ULL,
	0x9999999999999999ULL,
	0xccccccccccccccccULL,
	0x7777777777777777ULL,
	0xbbbbbbbbbbbbbbbbULL,
	0xddddddddddddddddULL,
	0xeeeeeeeeeeeeeeeeULL,
	0x7a6c7258554e494cULL, /* yeah ;-) */
पूर्ण;

अटल व्योम __init reserve_bad_mem(u64 pattern, phys_addr_t start_bad, phys_addr_t end_bad)
अणु
	pr_info("  %016llx bad mem addr %pa - %pa reserved\n",
		cpu_to_be64(pattern), &start_bad, &end_bad);
	memblock_reserve(start_bad, end_bad - start_bad);
पूर्ण

अटल व्योम __init memtest(u64 pattern, phys_addr_t start_phys, phys_addr_t size)
अणु
	u64 *p, *start, *end;
	phys_addr_t start_bad, last_bad;
	phys_addr_t start_phys_aligned;
	स्थिर माप_प्रकार incr = माप(pattern);

	start_phys_aligned = ALIGN(start_phys, incr);
	start = __va(start_phys_aligned);
	end = start + (size - (start_phys_aligned - start_phys)) / incr;
	start_bad = 0;
	last_bad = 0;

	क्रम (p = start; p < end; p++)
		*p = pattern;

	क्रम (p = start; p < end; p++, start_phys_aligned += incr) अणु
		अगर (*p == pattern)
			जारी;
		अगर (start_phys_aligned == last_bad + incr) अणु
			last_bad += incr;
			जारी;
		पूर्ण
		अगर (start_bad)
			reserve_bad_mem(pattern, start_bad, last_bad + incr);
		start_bad = last_bad = start_phys_aligned;
	पूर्ण
	अगर (start_bad)
		reserve_bad_mem(pattern, start_bad, last_bad + incr);
पूर्ण

अटल व्योम __init करो_one_pass(u64 pattern, phys_addr_t start, phys_addr_t end)
अणु
	u64 i;
	phys_addr_t this_start, this_end;

	क्रम_each_मुक्त_mem_range(i, NUMA_NO_NODE, MEMBLOCK_NONE, &this_start,
				&this_end, शून्य) अणु
		this_start = clamp(this_start, start, end);
		this_end = clamp(this_end, start, end);
		अगर (this_start < this_end) अणु
			pr_info("  %pa - %pa pattern %016llx\n",
				&this_start, &this_end, cpu_to_be64(pattern));
			memtest(pattern, this_start, this_end - this_start);
		पूर्ण
	पूर्ण
पूर्ण

/* शेष is disabled */
अटल अचिन्हित पूर्णांक memtest_pattern __initdata;

अटल पूर्णांक __init parse_memtest(अक्षर *arg)
अणु
	पूर्णांक ret = 0;

	अगर (arg)
		ret = kstrtouपूर्णांक(arg, 0, &memtest_pattern);
	अन्यथा
		memtest_pattern = ARRAY_SIZE(patterns);

	वापस ret;
पूर्ण

early_param("memtest", parse_memtest);

व्योम __init early_memtest(phys_addr_t start, phys_addr_t end)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक idx = 0;

	अगर (!memtest_pattern)
		वापस;

	pr_info("early_memtest: # of tests: %u\n", memtest_pattern);
	क्रम (i = memtest_pattern-1; i < अच_पूर्णांक_उच्च; --i) अणु
		idx = i % ARRAY_SIZE(patterns);
		करो_one_pass(patterns[idx], start, end);
	पूर्ण
पूर्ण
