<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright 2002 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * raid6/algos.c
 *
 * Algorithm list and algorithm selection क्रम RAID-6
 */

#समावेश <linux/raid/pq.h>
#अगर_अघोषित __KERNEL__
#समावेश <sys/mman.h>
#समावेश <मानकपन.स>
#अन्यथा
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#अगर !RAID6_USE_EMPTY_ZERO_PAGE
/* In .bss so it's zeroed */
स्थिर अक्षर raid6_empty_zero_page[PAGE_SIZE] __attribute__((aligned(256)));
EXPORT_SYMBOL(raid6_empty_zero_page);
#पूर्ण_अगर
#पूर्ण_अगर

काष्ठा raid6_calls raid6_call;
EXPORT_SYMBOL_GPL(raid6_call);

स्थिर काष्ठा raid6_calls * स्थिर raid6_algos[] = अणु
#अगर defined(__i386__) && !defined(__arch_um__)
#अगर_घोषित CONFIG_AS_AVX512
	&raid6_avx512x2,
	&raid6_avx512x1,
#पूर्ण_अगर
	&raid6_avx2x2,
	&raid6_avx2x1,
	&raid6_sse2x2,
	&raid6_sse2x1,
	&raid6_sse1x2,
	&raid6_sse1x1,
	&raid6_mmxx2,
	&raid6_mmxx1,
#पूर्ण_अगर
#अगर defined(__x86_64__) && !defined(__arch_um__)
#अगर_घोषित CONFIG_AS_AVX512
	&raid6_avx512x4,
	&raid6_avx512x2,
	&raid6_avx512x1,
#पूर्ण_अगर
	&raid6_avx2x4,
	&raid6_avx2x2,
	&raid6_avx2x1,
	&raid6_sse2x4,
	&raid6_sse2x2,
	&raid6_sse2x1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	&raid6_vpermxor8,
	&raid6_vpermxor4,
	&raid6_vpermxor2,
	&raid6_vpermxor1,
	&raid6_altivec8,
	&raid6_altivec4,
	&raid6_altivec2,
	&raid6_altivec1,
#पूर्ण_अगर
#अगर defined(CONFIG_S390)
	&raid6_s390vx8,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KERNEL_MODE_NEON
	&raid6_neonx8,
	&raid6_neonx4,
	&raid6_neonx2,
	&raid6_neonx1,
#पूर्ण_अगर
#अगर defined(__ia64__)
	&raid6_पूर्णांकx32,
	&raid6_पूर्णांकx16,
#पूर्ण_अगर
	&raid6_पूर्णांकx8,
	&raid6_पूर्णांकx4,
	&raid6_पूर्णांकx2,
	&raid6_पूर्णांकx1,
	शून्य
पूर्ण;

व्योम (*raid6_2data_recov)(पूर्णांक, माप_प्रकार, पूर्णांक, पूर्णांक, व्योम **);
EXPORT_SYMBOL_GPL(raid6_2data_recov);

व्योम (*raid6_datap_recov)(पूर्णांक, माप_प्रकार, पूर्णांक, व्योम **);
EXPORT_SYMBOL_GPL(raid6_datap_recov);

स्थिर काष्ठा raid6_recov_calls *स्थिर raid6_recov_algos[] = अणु
#अगर_घोषित CONFIG_X86
#अगर_घोषित CONFIG_AS_AVX512
	&raid6_recov_avx512,
#पूर्ण_अगर
	&raid6_recov_avx2,
	&raid6_recov_ssse3,
#पूर्ण_अगर
#अगर_घोषित CONFIG_S390
	&raid6_recov_s390xc,
#पूर्ण_अगर
#अगर defined(CONFIG_KERNEL_MODE_NEON)
	&raid6_recov_neon,
#पूर्ण_अगर
	&raid6_recov_पूर्णांकx1,
	शून्य
पूर्ण;

#अगर_घोषित __KERNEL__
#घोषणा RAID6_TIME_JIFFIES_LG2	4
#अन्यथा
/* Need more समय to be stable in userspace */
#घोषणा RAID6_TIME_JIFFIES_LG2	9
#घोषणा समय_beक्रमe(x, y) ((x) < (y))
#पूर्ण_अगर

#घोषणा RAID6_TEST_DISKS	8
#घोषणा RAID6_TEST_DISKS_ORDER	3

अटल अंतरभूत स्थिर काष्ठा raid6_recov_calls *raid6_choose_recov(व्योम)
अणु
	स्थिर काष्ठा raid6_recov_calls *स्थिर *algo;
	स्थिर काष्ठा raid6_recov_calls *best;

	क्रम (best = शून्य, algo = raid6_recov_algos; *algo; algo++)
		अगर (!best || (*algo)->priority > best->priority)
			अगर (!(*algo)->valid || (*algo)->valid())
				best = *algo;

	अगर (best) अणु
		raid6_2data_recov = best->data2;
		raid6_datap_recov = best->datap;

		pr_info("raid6: using %s recovery algorithm\n", best->name);
	पूर्ण अन्यथा
		pr_err("raid6: Yikes! No recovery algorithm found!\n");

	वापस best;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा raid6_calls *raid6_choose_gen(
	व्योम *(*स्थिर dptrs)[RAID6_TEST_DISKS], स्थिर पूर्णांक disks)
अणु
	अचिन्हित दीर्घ perf, bestgenperf, bestxorperf, j0, j1;
	पूर्णांक start = (disks>>1)-1, stop = disks-3;	/* work on the second half of the disks */
	स्थिर काष्ठा raid6_calls *स्थिर *algo;
	स्थिर काष्ठा raid6_calls *best;

	क्रम (bestgenperf = 0, bestxorperf = 0, best = शून्य, algo = raid6_algos; *algo; algo++) अणु
		अगर (!best || (*algo)->prefer >= best->prefer) अणु
			अगर ((*algo)->valid && !(*algo)->valid())
				जारी;

			अगर (!IS_ENABLED(CONFIG_RAID6_PQ_BENCHMARK)) अणु
				best = *algo;
				अवरोध;
			पूर्ण

			perf = 0;

			preempt_disable();
			j0 = jअगरfies;
			जबतक ((j1 = jअगरfies) == j0)
				cpu_relax();
			जबतक (समय_beक्रमe(jअगरfies,
					    j1 + (1<<RAID6_TIME_JIFFIES_LG2))) अणु
				(*algo)->gen_syndrome(disks, PAGE_SIZE, *dptrs);
				perf++;
			पूर्ण
			preempt_enable();

			अगर (perf > bestgenperf) अणु
				bestgenperf = perf;
				best = *algo;
			पूर्ण
			pr_info("raid6: %-8s gen() %5ld MB/s\n", (*algo)->name,
				(perf * HZ * (disks-2)) >>
				(20 - PAGE_SHIFT + RAID6_TIME_JIFFIES_LG2));

			अगर (!(*algo)->xor_syndrome)
				जारी;

			perf = 0;

			preempt_disable();
			j0 = jअगरfies;
			जबतक ((j1 = jअगरfies) == j0)
				cpu_relax();
			जबतक (समय_beक्रमe(jअगरfies,
					    j1 + (1<<RAID6_TIME_JIFFIES_LG2))) अणु
				(*algo)->xor_syndrome(disks, start, stop,
						      PAGE_SIZE, *dptrs);
				perf++;
			पूर्ण
			preempt_enable();

			अगर (best == *algo)
				bestxorperf = perf;

			pr_info("raid6: %-8s xor() %5ld MB/s\n", (*algo)->name,
				(perf * HZ * (disks-2)) >>
				(20 - PAGE_SHIFT + RAID6_TIME_JIFFIES_LG2 + 1));
		पूर्ण
	पूर्ण

	अगर (best) अणु
		अगर (IS_ENABLED(CONFIG_RAID6_PQ_BENCHMARK)) अणु
			pr_info("raid6: using algorithm %s gen() %ld MB/s\n",
				best->name,
				(bestgenperf * HZ * (disks-2)) >>
				(20 - PAGE_SHIFT+RAID6_TIME_JIFFIES_LG2));
			अगर (best->xor_syndrome)
				pr_info("raid6: .... xor() %ld MB/s, rmw enabled\n",
					(bestxorperf * HZ * (disks-2)) >>
					(20 - PAGE_SHIFT + RAID6_TIME_JIFFIES_LG2 + 1));
		पूर्ण अन्यथा
			pr_info("raid6: skip pq benchmark and using algorithm %s\n",
				best->name);
		raid6_call = *best;
	पूर्ण अन्यथा
		pr_err("raid6: Yikes!  No algorithm found!\n");

	वापस best;
पूर्ण


/* Try to pick the best algorithm */
/* This code uses the gfmul table as convenient data set to abuse */

पूर्णांक __init raid6_select_algo(व्योम)
अणु
	स्थिर पूर्णांक disks = RAID6_TEST_DISKS;

	स्थिर काष्ठा raid6_calls *gen_best;
	स्थिर काष्ठा raid6_recov_calls *rec_best;
	अक्षर *disk_ptr, *p;
	व्योम *dptrs[RAID6_TEST_DISKS];
	पूर्णांक i, cycle;

	/* prepare the buffer and fill it circularly with gfmul table */
	disk_ptr = (अक्षर *)__get_मुक्त_pages(GFP_KERNEL, RAID6_TEST_DISKS_ORDER);
	अगर (!disk_ptr) अणु
		pr_err("raid6: Yikes!  No memory available.\n");
		वापस -ENOMEM;
	पूर्ण

	p = disk_ptr;
	क्रम (i = 0; i < disks; i++)
		dptrs[i] = p + PAGE_SIZE * i;

	cycle = ((disks - 2) * PAGE_SIZE) / 65536;
	क्रम (i = 0; i < cycle; i++) अणु
		स_नकल(p, raid6_gfmul, 65536);
		p += 65536;
	पूर्ण

	अगर ((disks - 2) * PAGE_SIZE % 65536)
		स_नकल(p, raid6_gfmul, (disks - 2) * PAGE_SIZE % 65536);

	/* select raid gen_syndrome function */
	gen_best = raid6_choose_gen(&dptrs, disks);

	/* select raid recover functions */
	rec_best = raid6_choose_recov();

	मुक्त_pages((अचिन्हित दीर्घ)disk_ptr, RAID6_TEST_DISKS_ORDER);

	वापस gen_best && rec_best ? 0 : -EINVAL;
पूर्ण

अटल व्योम raid6_निकास(व्योम)
अणु
	करो अणु पूर्ण जबतक (0);
पूर्ण

subsys_initcall(raid6_select_algo);
module_निकास(raid6_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RAID6 Q-syndrome calculations");
