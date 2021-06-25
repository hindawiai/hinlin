<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * self test क्रम change_page_attr.
 *
 * Clears the a test pte bit on अक्रमom pages in the direct mapping,
 * then reverts and compares page tables क्रमwards and afterwards.
 */
#समावेश <linux/memblock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/kdebug.h>

/*
 * Only prपूर्णांक the results of the first pass:
 */
अटल __पढ़ो_mostly पूर्णांक prपूर्णांक = 1;

क्रमागत अणु
	NTEST			= 3 * 100,
	NPAGES			= 100,
#अगर_घोषित CONFIG_X86_64
	LPS			= (1 << PMD_SHIFT),
#या_अगर defined(CONFIG_X86_PAE)
	LPS			= (1 << PMD_SHIFT),
#अन्यथा
	LPS			= (1 << 22),
#पूर्ण_अगर
	GPS			= (1<<30)
पूर्ण;

#घोषणा PAGE_CPA_TEST	__pgprot(_PAGE_CPA_TEST)

अटल पूर्णांक pte_testbit(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_SOFTW1;
पूर्ण

काष्ठा split_state अणु
	दीर्घ lpg, gpg, spg, exec;
	दीर्घ min_exec, max_exec;
पूर्ण;

अटल पूर्णांक prपूर्णांक_split(काष्ठा split_state *s)
अणु
	दीर्घ i, expected, missed = 0;
	पूर्णांक err = 0;

	s->lpg = s->gpg = s->spg = s->exec = 0;
	s->min_exec = ~0UL;
	s->max_exec = 0;
	क्रम (i = 0; i < max_pfn_mapped; ) अणु
		अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)__va(i << PAGE_SHIFT);
		अचिन्हित पूर्णांक level;
		pte_t *pte;

		pte = lookup_address(addr, &level);
		अगर (!pte) अणु
			missed++;
			i++;
			जारी;
		पूर्ण

		अगर (level == PG_LEVEL_1G && माप(दीर्घ) == 8) अणु
			s->gpg++;
			i += GPS/PAGE_SIZE;
		पूर्ण अन्यथा अगर (level == PG_LEVEL_2M) अणु
			अगर ((pte_val(*pte) & _PAGE_PRESENT) && !(pte_val(*pte) & _PAGE_PSE)) अणु
				prपूर्णांकk(KERN_ERR
					"%lx level %d but not PSE %Lx\n",
					addr, level, (u64)pte_val(*pte));
				err = 1;
			पूर्ण
			s->lpg++;
			i += LPS/PAGE_SIZE;
		पूर्ण अन्यथा अणु
			s->spg++;
			i++;
		पूर्ण
		अगर (!(pte_val(*pte) & _PAGE_NX)) अणु
			s->exec++;
			अगर (addr < s->min_exec)
				s->min_exec = addr;
			अगर (addr > s->max_exec)
				s->max_exec = addr;
		पूर्ण
	पूर्ण
	अगर (prपूर्णांक) अणु
		prपूर्णांकk(KERN_INFO
			" 4k %lu large %lu gb %lu x %lu[%lx-%lx] miss %lu\n",
			s->spg, s->lpg, s->gpg, s->exec,
			s->min_exec != ~0UL ? s->min_exec : 0,
			s->max_exec, missed);
	पूर्ण

	expected = (s->gpg*GPS + s->lpg*LPS)/PAGE_SIZE + s->spg + missed;
	अगर (expected != i) अणु
		prपूर्णांकk(KERN_ERR "CPA max_pfn_mapped %lu but expected %lu\n",
			max_pfn_mapped, expected);
		वापस 1;
	पूर्ण
	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ addr[NTEST];
अटल अचिन्हित पूर्णांक len[NTEST];

अटल काष्ठा page *pages[NPAGES];
अटल अचिन्हित दीर्घ addrs[NPAGES];

/* Change the global bit on अक्रमom pages in the direct mapping */
अटल पूर्णांक pageattr_test(व्योम)
अणु
	काष्ठा split_state sa, sb, sc;
	अचिन्हित दीर्घ *bm;
	pte_t *pte, pte0;
	पूर्णांक failed = 0;
	अचिन्हित पूर्णांक level;
	पूर्णांक i, k;
	पूर्णांक err;

	अगर (prपूर्णांक)
		prपूर्णांकk(KERN_INFO "CPA self-test:\n");

	bm = vzalloc((max_pfn_mapped + 7) / 8);
	अगर (!bm) अणु
		prपूर्णांकk(KERN_ERR "CPA Cannot vmalloc bitmap\n");
		वापस -ENOMEM;
	पूर्ण

	failed += prपूर्णांक_split(&sa);

	क्रम (i = 0; i < NTEST; i++) अणु
		अचिन्हित दीर्घ pfn = pअक्रमom_u32() % max_pfn_mapped;

		addr[i] = (अचिन्हित दीर्घ)__va(pfn << PAGE_SHIFT);
		len[i] = pअक्रमom_u32() % NPAGES;
		len[i] = min_t(अचिन्हित दीर्घ, len[i], max_pfn_mapped - pfn - 1);

		अगर (len[i] == 0)
			len[i] = 1;

		pte = शून्य;
		pte0 = pfn_pte(0, __pgprot(0)); /* shut gcc up */

		क्रम (k = 0; k < len[i]; k++) अणु
			pte = lookup_address(addr[i] + k*PAGE_SIZE, &level);
			अगर (!pte || pgprot_val(pte_pgprot(*pte)) == 0 ||
			    !(pte_val(*pte) & _PAGE_PRESENT)) अणु
				addr[i] = 0;
				अवरोध;
			पूर्ण
			अगर (k == 0) अणु
				pte0 = *pte;
			पूर्ण अन्यथा अणु
				अगर (pgprot_val(pte_pgprot(*pte)) !=
					pgprot_val(pte_pgprot(pte0))) अणु
					len[i] = k;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (test_bit(pfn + k, bm)) अणु
				len[i] = k;
				अवरोध;
			पूर्ण
			__set_bit(pfn + k, bm);
			addrs[k] = addr[i] + k*PAGE_SIZE;
			pages[k] = pfn_to_page(pfn + k);
		पूर्ण
		अगर (!addr[i] || !pte || !k) अणु
			addr[i] = 0;
			जारी;
		पूर्ण

		चयन (i % 3) अणु
		हाल 0:
			err = change_page_attr_set(&addr[i], len[i], PAGE_CPA_TEST, 0);
			अवरोध;

		हाल 1:
			err = change_page_attr_set(addrs, len[1], PAGE_CPA_TEST, 1);
			अवरोध;

		हाल 2:
			err = cpa_set_pages_array(pages, len[i], PAGE_CPA_TEST);
			अवरोध;
		पूर्ण


		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR "CPA %d failed %d\n", i, err);
			failed++;
		पूर्ण

		pte = lookup_address(addr[i], &level);
		अगर (!pte || !pte_testbit(*pte) || pte_huge(*pte)) अणु
			prपूर्णांकk(KERN_ERR "CPA %lx: bad pte %Lx\n", addr[i],
				pte ? (u64)pte_val(*pte) : 0ULL);
			failed++;
		पूर्ण
		अगर (level != PG_LEVEL_4K) अणु
			prपूर्णांकk(KERN_ERR "CPA %lx: unexpected level %d\n",
				addr[i], level);
			failed++;
		पूर्ण

	पूर्ण
	vमुक्त(bm);

	failed += prपूर्णांक_split(&sb);

	क्रम (i = 0; i < NTEST; i++) अणु
		अगर (!addr[i])
			जारी;
		pte = lookup_address(addr[i], &level);
		अगर (!pte) अणु
			prपूर्णांकk(KERN_ERR "CPA lookup of %lx failed\n", addr[i]);
			failed++;
			जारी;
		पूर्ण
		err = change_page_attr_clear(&addr[i], len[i], PAGE_CPA_TEST, 0);
		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR "CPA reverting failed: %d\n", err);
			failed++;
		पूर्ण
		pte = lookup_address(addr[i], &level);
		अगर (!pte || pte_testbit(*pte)) अणु
			prपूर्णांकk(KERN_ERR "CPA %lx: bad pte after revert %Lx\n",
				addr[i], pte ? (u64)pte_val(*pte) : 0ULL);
			failed++;
		पूर्ण

	पूर्ण

	failed += prपूर्णांक_split(&sc);

	अगर (failed) अणु
		WARN(1, KERN_ERR "NOT PASSED. Please report.\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (prपूर्णांक)
			prपूर्णांकk(KERN_INFO "ok.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_pageattr_test(व्योम *__unused)
अणु
	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule_समयout_पूर्णांकerruptible(HZ*30);
		अगर (pageattr_test() < 0)
			अवरोध;
		अगर (prपूर्णांक)
			prपूर्णांक--;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक start_pageattr_test(व्योम)
अणु
	काष्ठा task_काष्ठा *p;

	p = kthपढ़ो_create(करो_pageattr_test, शून्य, "pageattr-test");
	अगर (!IS_ERR(p))
		wake_up_process(p);
	अन्यथा
		WARN_ON(1);

	वापस 0;
पूर्ण
device_initcall(start_pageattr_test);
