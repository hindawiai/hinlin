<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/pagewalk.h>
#समावेश <linux/ptdump.h>
#समावेश <linux/kasan.h>

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
/*
 * This is an optimization क्रम KASAN=y हाल. Since all kasan page tables
 * eventually poपूर्णांक to the kasan_early_shaकरोw_page we could call note_page()
 * right away without walking through lower level page tables. This saves
 * us करोzens of seconds (minutes क्रम 5-level config) जबतक checking क्रम
 * W+X mapping or पढ़ोing kernel_page_tables debugfs file.
 */
अटल अंतरभूत पूर्णांक note_kasan_page_table(काष्ठा mm_walk *walk,
					अचिन्हित दीर्घ addr)
अणु
	काष्ठा ptdump_state *st = walk->निजी;

	st->note_page(st, addr, 4, pte_val(kasan_early_shaकरोw_pte[0]));

	walk->action = ACTION_CONTINUE;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ptdump_pgd_entry(pgd_t *pgd, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	काष्ठा ptdump_state *st = walk->निजी;
	pgd_t val = READ_ONCE(*pgd);

#अगर CONFIG_PGTABLE_LEVELS > 4 && \
		(defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS))
	अगर (pgd_page(val) == virt_to_page(lm_alias(kasan_early_shaकरोw_p4d)))
		वापस note_kasan_page_table(walk, addr);
#पूर्ण_अगर

	अगर (st->effective_prot)
		st->effective_prot(st, 0, pgd_val(val));

	अगर (pgd_leaf(val))
		st->note_page(st, addr, 0, pgd_val(val));

	वापस 0;
पूर्ण

अटल पूर्णांक ptdump_p4d_entry(p4d_t *p4d, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	काष्ठा ptdump_state *st = walk->निजी;
	p4d_t val = READ_ONCE(*p4d);

#अगर CONFIG_PGTABLE_LEVELS > 3 && \
		(defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS))
	अगर (p4d_page(val) == virt_to_page(lm_alias(kasan_early_shaकरोw_pud)))
		वापस note_kasan_page_table(walk, addr);
#पूर्ण_अगर

	अगर (st->effective_prot)
		st->effective_prot(st, 1, p4d_val(val));

	अगर (p4d_leaf(val))
		st->note_page(st, addr, 1, p4d_val(val));

	वापस 0;
पूर्ण

अटल पूर्णांक ptdump_pud_entry(pud_t *pud, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	काष्ठा ptdump_state *st = walk->निजी;
	pud_t val = READ_ONCE(*pud);

#अगर CONFIG_PGTABLE_LEVELS > 2 && \
		(defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS))
	अगर (pud_page(val) == virt_to_page(lm_alias(kasan_early_shaकरोw_pmd)))
		वापस note_kasan_page_table(walk, addr);
#पूर्ण_अगर

	अगर (st->effective_prot)
		st->effective_prot(st, 2, pud_val(val));

	अगर (pud_leaf(val))
		st->note_page(st, addr, 2, pud_val(val));

	वापस 0;
पूर्ण

अटल पूर्णांक ptdump_pmd_entry(pmd_t *pmd, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	काष्ठा ptdump_state *st = walk->निजी;
	pmd_t val = READ_ONCE(*pmd);

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
	अगर (pmd_page(val) == virt_to_page(lm_alias(kasan_early_shaकरोw_pte)))
		वापस note_kasan_page_table(walk, addr);
#पूर्ण_अगर

	अगर (st->effective_prot)
		st->effective_prot(st, 3, pmd_val(val));
	अगर (pmd_leaf(val))
		st->note_page(st, addr, 3, pmd_val(val));

	वापस 0;
पूर्ण

अटल पूर्णांक ptdump_pte_entry(pte_t *pte, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	काष्ठा ptdump_state *st = walk->निजी;
	pte_t val = ptep_get(pte);

	अगर (st->effective_prot)
		st->effective_prot(st, 4, pte_val(val));

	st->note_page(st, addr, 4, pte_val(val));

	वापस 0;
पूर्ण

अटल पूर्णांक ptdump_hole(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next,
		       पूर्णांक depth, काष्ठा mm_walk *walk)
अणु
	काष्ठा ptdump_state *st = walk->निजी;

	st->note_page(st, addr, depth, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops ptdump_ops = अणु
	.pgd_entry	= ptdump_pgd_entry,
	.p4d_entry	= ptdump_p4d_entry,
	.pud_entry	= ptdump_pud_entry,
	.pmd_entry	= ptdump_pmd_entry,
	.pte_entry	= ptdump_pte_entry,
	.pte_hole	= ptdump_hole,
पूर्ण;

व्योम ptdump_walk_pgd(काष्ठा ptdump_state *st, काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	स्थिर काष्ठा ptdump_range *range = st->range;

	mmap_पढ़ो_lock(mm);
	जबतक (range->start != range->end) अणु
		walk_page_range_novma(mm, range->start, range->end,
				      &ptdump_ops, pgd, st);
		range++;
	पूर्ण
	mmap_पढ़ो_unlock(mm);

	/* Flush out the last page */
	st->note_page(st, 0, -1, 0);
पूर्ण
