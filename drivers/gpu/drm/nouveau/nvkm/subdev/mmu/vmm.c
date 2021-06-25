<शैली गुरु>
/*
 * Copyright 2017 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#घोषणा NVKM_VMM_LEVELS_MAX 5
#समावेश "vmm.h"

#समावेश <subdev/fb.h>

अटल व्योम
nvkm_vmm_pt_del(काष्ठा nvkm_vmm_pt **ppgt)
अणु
	काष्ठा nvkm_vmm_pt *pgt = *ppgt;
	अगर (pgt) अणु
		kvमुक्त(pgt->pde);
		kमुक्त(pgt);
		*ppgt = शून्य;
	पूर्ण
पूर्ण


अटल काष्ठा nvkm_vmm_pt *
nvkm_vmm_pt_new(स्थिर काष्ठा nvkm_vmm_desc *desc, bool sparse,
		स्थिर काष्ठा nvkm_vmm_page *page)
अणु
	स्थिर u32 pten = 1 << desc->bits;
	काष्ठा nvkm_vmm_pt *pgt;
	u32 lpte = 0;

	अगर (desc->type > PGT) अणु
		अगर (desc->type == SPT) अणु
			स्थिर काष्ठा nvkm_vmm_desc *pair = page[-1].desc;
			lpte = pten >> (desc->bits - pair->bits);
		पूर्ण अन्यथा अणु
			lpte = pten;
		पूर्ण
	पूर्ण

	अगर (!(pgt = kzalloc(माप(*pgt) + lpte, GFP_KERNEL)))
		वापस शून्य;
	pgt->page = page ? page->shअगरt : 0;
	pgt->sparse = sparse;

	अगर (desc->type == PGD) अणु
		pgt->pde = kvसुस्मृति(pten, माप(*pgt->pde), GFP_KERNEL);
		अगर (!pgt->pde) अणु
			kमुक्त(pgt);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस pgt;
पूर्ण

काष्ठा nvkm_vmm_iter अणु
	स्थिर काष्ठा nvkm_vmm_page *page;
	स्थिर काष्ठा nvkm_vmm_desc *desc;
	काष्ठा nvkm_vmm *vmm;
	u64 cnt;
	u16 max, lvl;
	u32 pte[NVKM_VMM_LEVELS_MAX];
	काष्ठा nvkm_vmm_pt *pt[NVKM_VMM_LEVELS_MAX];
	पूर्णांक flush;
पूर्ण;

#अगर_घोषित CONFIG_NOUVEAU_DEBUG_MMU
अटल स्थिर अक्षर *
nvkm_vmm_desc_type(स्थिर काष्ठा nvkm_vmm_desc *desc)
अणु
	चयन (desc->type) अणु
	हाल PGD: वापस "PGD";
	हाल PGT: वापस "PGT";
	हाल SPT: वापस "SPT";
	हाल LPT: वापस "LPT";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल व्योम
nvkm_vmm_trace(काष्ठा nvkm_vmm_iter *it, अक्षर *buf)
अणु
	पूर्णांक lvl;
	क्रम (lvl = it->max; lvl >= 0; lvl--) अणु
		अगर (lvl >= it->lvl)
			buf += प्र_लिखो(buf,  "%05x:", it->pte[lvl]);
		अन्यथा
			buf += प्र_लिखो(buf, "xxxxx:");
	पूर्ण
पूर्ण

#घोषणा TRA(i,f,a...) करो अणु                                                     \
	अक्षर _buf[NVKM_VMM_LEVELS_MAX * 7];                                    \
	काष्ठा nvkm_vmm_iter *_it = (i);                                       \
	nvkm_vmm_trace(_it, _buf);                                             \
	VMM_TRACE(_it->vmm, "%s "f, _buf, ##a);                                \
पूर्ण जबतक(0)
#अन्यथा
#घोषणा TRA(i,f,a...)
#पूर्ण_अगर

अटल अंतरभूत व्योम
nvkm_vmm_flush_mark(काष्ठा nvkm_vmm_iter *it)
अणु
	it->flush = min(it->flush, it->max - it->lvl);
पूर्ण

अटल अंतरभूत व्योम
nvkm_vmm_flush(काष्ठा nvkm_vmm_iter *it)
अणु
	अगर (it->flush != NVKM_VMM_LEVELS_MAX) अणु
		अगर (it->vmm->func->flush) अणु
			TRA(it, "flush: %d", it->flush);
			it->vmm->func->flush(it->vmm, it->flush);
		पूर्ण
		it->flush = NVKM_VMM_LEVELS_MAX;
	पूर्ण
पूर्ण

अटल व्योम
nvkm_vmm_unref_pdes(काष्ठा nvkm_vmm_iter *it)
अणु
	स्थिर काष्ठा nvkm_vmm_desc *desc = it->desc;
	स्थिर पूर्णांक type = desc[it->lvl].type == SPT;
	काष्ठा nvkm_vmm_pt *pgd = it->pt[it->lvl + 1];
	काष्ठा nvkm_vmm_pt *pgt = it->pt[it->lvl];
	काष्ठा nvkm_mmu_pt *pt = pgt->pt[type];
	काष्ठा nvkm_vmm *vmm = it->vmm;
	u32 pdei = it->pte[it->lvl + 1];

	/* Recurse up the tree, unreferencing/destroying unneeded PDs. */
	it->lvl++;
	अगर (--pgd->refs[0]) अणु
		स्थिर काष्ठा nvkm_vmm_desc_func *func = desc[it->lvl].func;
		/* PD has other valid PDEs, so we need a proper update. */
		TRA(it, "PDE unmap %s", nvkm_vmm_desc_type(&desc[it->lvl - 1]));
		pgt->pt[type] = शून्य;
		अगर (!pgt->refs[!type]) अणु
			/* PDE no दीर्घer required. */
			अगर (pgd->pt[0]) अणु
				अगर (pgt->sparse) अणु
					func->sparse(vmm, pgd->pt[0], pdei, 1);
					pgd->pde[pdei] = NVKM_VMM_PDE_SPARSE;
				पूर्ण अन्यथा अणु
					func->unmap(vmm, pgd->pt[0], pdei, 1);
					pgd->pde[pdei] = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Special handling क्रम Tesla-class GPUs,
				 * where there's no central PD, but each
				 * instance has its own embedded PD.
				 */
				func->pde(vmm, pgd, pdei);
				pgd->pde[pdei] = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* PDE was poपूर्णांकing at dual-PTs and we're removing
			 * one of them, leaving the other in place.
			 */
			func->pde(vmm, pgd, pdei);
		पूर्ण

		/* GPU may have cached the PTs, flush beक्रमe मुक्तing. */
		nvkm_vmm_flush_mark(it);
		nvkm_vmm_flush(it);
	पूर्ण अन्यथा अणु
		/* PD has no valid PDEs left, so we can just destroy it. */
		nvkm_vmm_unref_pdes(it);
	पूर्ण

	/* Destroy PD/PT. */
	TRA(it, "PDE free %s", nvkm_vmm_desc_type(&desc[it->lvl - 1]));
	nvkm_mmu_ptc_put(vmm->mmu, vmm->bootstrapped, &pt);
	अगर (!pgt->refs[!type])
		nvkm_vmm_pt_del(&pgt);
	it->lvl--;
पूर्ण

अटल व्योम
nvkm_vmm_unref_sptes(काष्ठा nvkm_vmm_iter *it, काष्ठा nvkm_vmm_pt *pgt,
		     स्थिर काष्ठा nvkm_vmm_desc *desc, u32 ptei, u32 ptes)
अणु
	स्थिर काष्ठा nvkm_vmm_desc *pair = it->page[-1].desc;
	स्थिर u32 sptb = desc->bits - pair->bits;
	स्थिर u32 sptn = 1 << sptb;
	काष्ठा nvkm_vmm *vmm = it->vmm;
	u32 spti = ptei & (sptn - 1), lpti, pteb;

	/* Determine how many SPTEs are being touched under each LPTE,
	 * and drop reference counts.
	 */
	क्रम (lpti = ptei >> sptb; ptes; spti = 0, lpti++) अणु
		स्थिर u32 pten = min(sptn - spti, ptes);
		pgt->pte[lpti] -= pten;
		ptes -= pten;
	पूर्ण

	/* We're done here if there's no corresponding LPT. */
	अगर (!pgt->refs[0])
		वापस;

	क्रम (ptei = pteb = ptei >> sptb; ptei < lpti; pteb = ptei) अणु
		/* Skip over any LPTEs that still have valid SPTEs. */
		अगर (pgt->pte[pteb] & NVKM_VMM_PTE_SPTES) अणु
			क्रम (ptes = 1, ptei++; ptei < lpti; ptes++, ptei++) अणु
				अगर (!(pgt->pte[ptei] & NVKM_VMM_PTE_SPTES))
					अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		/* As there's no more non-UNMAPPED SPTEs left in the range
		 * covered by a number of LPTEs, the LPTEs once again take
		 * control over their address range.
		 *
		 * Determine how many LPTEs need to transition state.
		 */
		pgt->pte[ptei] &= ~NVKM_VMM_PTE_VALID;
		क्रम (ptes = 1, ptei++; ptei < lpti; ptes++, ptei++) अणु
			अगर (pgt->pte[ptei] & NVKM_VMM_PTE_SPTES)
				अवरोध;
			pgt->pte[ptei] &= ~NVKM_VMM_PTE_VALID;
		पूर्ण

		अगर (pgt->pte[pteb] & NVKM_VMM_PTE_SPARSE) अणु
			TRA(it, "LPTE %05x: U -> S %d PTEs", pteb, ptes);
			pair->func->sparse(vmm, pgt->pt[0], pteb, ptes);
		पूर्ण अन्यथा
		अगर (pair->func->invalid) अणु
			/* If the MMU supports it, restore the LPTE to the
			 * INVALID state to tell the MMU there is no poपूर्णांक
			 * trying to fetch the corresponding SPTEs.
			 */
			TRA(it, "LPTE %05x: U -> I %d PTEs", pteb, ptes);
			pair->func->invalid(vmm, pgt->pt[0], pteb, ptes);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool
nvkm_vmm_unref_ptes(काष्ठा nvkm_vmm_iter *it, bool pfn, u32 ptei, u32 ptes)
अणु
	स्थिर काष्ठा nvkm_vmm_desc *desc = it->desc;
	स्थिर पूर्णांक type = desc->type == SPT;
	काष्ठा nvkm_vmm_pt *pgt = it->pt[0];
	bool dma;

	अगर (pfn) अणु
		/* Need to clear PTE valid bits beक्रमe we dma_unmap_page(). */
		dma = desc->func->pfn_clear(it->vmm, pgt->pt[type], ptei, ptes);
		अगर (dma) अणु
			/* GPU may have cached the PT, flush beक्रमe unmap. */
			nvkm_vmm_flush_mark(it);
			nvkm_vmm_flush(it);
			desc->func->pfn_unmap(it->vmm, pgt->pt[type], ptei, ptes);
		पूर्ण
	पूर्ण

	/* Drop PTE references. */
	pgt->refs[type] -= ptes;

	/* Dual-PTs need special handling, unless PDE becoming invalid. */
	अगर (desc->type == SPT && (pgt->refs[0] || pgt->refs[1]))
		nvkm_vmm_unref_sptes(it, pgt, desc, ptei, ptes);

	/* PT no दीर्घer neeed?  Destroy it. */
	अगर (!pgt->refs[type]) अणु
		it->lvl++;
		TRA(it, "%s empty", nvkm_vmm_desc_type(desc));
		it->lvl--;
		nvkm_vmm_unref_pdes(it);
		वापस false; /* PTE ग_लिखोs क्रम unmap() not necessary. */
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
nvkm_vmm_ref_sptes(काष्ठा nvkm_vmm_iter *it, काष्ठा nvkm_vmm_pt *pgt,
		   स्थिर काष्ठा nvkm_vmm_desc *desc, u32 ptei, u32 ptes)
अणु
	स्थिर काष्ठा nvkm_vmm_desc *pair = it->page[-1].desc;
	स्थिर u32 sptb = desc->bits - pair->bits;
	स्थिर u32 sptn = 1 << sptb;
	काष्ठा nvkm_vmm *vmm = it->vmm;
	u32 spti = ptei & (sptn - 1), lpti, pteb;

	/* Determine how many SPTEs are being touched under each LPTE,
	 * and increase reference counts.
	 */
	क्रम (lpti = ptei >> sptb; ptes; spti = 0, lpti++) अणु
		स्थिर u32 pten = min(sptn - spti, ptes);
		pgt->pte[lpti] += pten;
		ptes -= pten;
	पूर्ण

	/* We're done here if there's no corresponding LPT. */
	अगर (!pgt->refs[0])
		वापस;

	क्रम (ptei = pteb = ptei >> sptb; ptei < lpti; pteb = ptei) अणु
		/* Skip over any LPTEs that alपढ़ोy have valid SPTEs. */
		अगर (pgt->pte[pteb] & NVKM_VMM_PTE_VALID) अणु
			क्रम (ptes = 1, ptei++; ptei < lpti; ptes++, ptei++) अणु
				अगर (!(pgt->pte[ptei] & NVKM_VMM_PTE_VALID))
					अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		/* As there are now non-UNMAPPED SPTEs in the range covered
		 * by a number of LPTEs, we need to transfer control of the
		 * address range to the SPTEs.
		 *
		 * Determine how many LPTEs need to transition state.
		 */
		pgt->pte[ptei] |= NVKM_VMM_PTE_VALID;
		क्रम (ptes = 1, ptei++; ptei < lpti; ptes++, ptei++) अणु
			अगर (pgt->pte[ptei] & NVKM_VMM_PTE_VALID)
				अवरोध;
			pgt->pte[ptei] |= NVKM_VMM_PTE_VALID;
		पूर्ण

		अगर (pgt->pte[pteb] & NVKM_VMM_PTE_SPARSE) अणु
			स्थिर u32 spti = pteb * sptn;
			स्थिर u32 sptc = ptes * sptn;
			/* The entire LPTE is marked as sparse, we need
			 * to make sure that the SPTEs are too.
			 */
			TRA(it, "SPTE %05x: U -> S %d PTEs", spti, sptc);
			desc->func->sparse(vmm, pgt->pt[1], spti, sptc);
			/* Sparse LPTEs prevent SPTEs from being accessed. */
			TRA(it, "LPTE %05x: S -> U %d PTEs", pteb, ptes);
			pair->func->unmap(vmm, pgt->pt[0], pteb, ptes);
		पूर्ण अन्यथा
		अगर (pair->func->invalid) अणु
			/* MMU supports blocking SPTEs by marking an LPTE
			 * as INVALID.  We need to reverse that here.
			 */
			TRA(it, "LPTE %05x: I -> U %d PTEs", pteb, ptes);
			pair->func->unmap(vmm, pgt->pt[0], pteb, ptes);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool
nvkm_vmm_ref_ptes(काष्ठा nvkm_vmm_iter *it, bool pfn, u32 ptei, u32 ptes)
अणु
	स्थिर काष्ठा nvkm_vmm_desc *desc = it->desc;
	स्थिर पूर्णांक type = desc->type == SPT;
	काष्ठा nvkm_vmm_pt *pgt = it->pt[0];

	/* Take PTE references. */
	pgt->refs[type] += ptes;

	/* Dual-PTs need special handling. */
	अगर (desc->type == SPT)
		nvkm_vmm_ref_sptes(it, pgt, desc, ptei, ptes);

	वापस true;
पूर्ण

अटल व्योम
nvkm_vmm_sparse_ptes(स्थिर काष्ठा nvkm_vmm_desc *desc,
		     काष्ठा nvkm_vmm_pt *pgt, u32 ptei, u32 ptes)
अणु
	अगर (desc->type == PGD) अणु
		जबतक (ptes--)
			pgt->pde[ptei++] = NVKM_VMM_PDE_SPARSE;
	पूर्ण अन्यथा
	अगर (desc->type == LPT) अणु
		स_रखो(&pgt->pte[ptei], NVKM_VMM_PTE_SPARSE, ptes);
	पूर्ण
पूर्ण

अटल bool
nvkm_vmm_sparse_unref_ptes(काष्ठा nvkm_vmm_iter *it, bool pfn, u32 ptei, u32 ptes)
अणु
	काष्ठा nvkm_vmm_pt *pt = it->pt[0];
	अगर (it->desc->type == PGD)
		स_रखो(&pt->pde[ptei], 0x00, माप(pt->pde[0]) * ptes);
	अन्यथा
	अगर (it->desc->type == LPT)
		स_रखो(&pt->pte[ptei], 0x00, माप(pt->pte[0]) * ptes);
	वापस nvkm_vmm_unref_ptes(it, pfn, ptei, ptes);
पूर्ण

अटल bool
nvkm_vmm_sparse_ref_ptes(काष्ठा nvkm_vmm_iter *it, bool pfn, u32 ptei, u32 ptes)
अणु
	nvkm_vmm_sparse_ptes(it->desc, it->pt[0], ptei, ptes);
	वापस nvkm_vmm_ref_ptes(it, pfn, ptei, ptes);
पूर्ण

अटल bool
nvkm_vmm_ref_hwpt(काष्ठा nvkm_vmm_iter *it, काष्ठा nvkm_vmm_pt *pgd, u32 pdei)
अणु
	स्थिर काष्ठा nvkm_vmm_desc *desc = &it->desc[it->lvl - 1];
	स्थिर पूर्णांक type = desc->type == SPT;
	काष्ठा nvkm_vmm_pt *pgt = pgd->pde[pdei];
	स्थिर bool zero = !pgt->sparse && !desc->func->invalid;
	काष्ठा nvkm_vmm *vmm = it->vmm;
	काष्ठा nvkm_mmu *mmu = vmm->mmu;
	काष्ठा nvkm_mmu_pt *pt;
	u32 pten = 1 << desc->bits;
	u32 pteb, ptei, ptes;
	u32 size = desc->size * pten;

	pgd->refs[0]++;

	pgt->pt[type] = nvkm_mmu_ptc_get(mmu, size, desc->align, zero);
	अगर (!pgt->pt[type]) अणु
		it->lvl--;
		nvkm_vmm_unref_pdes(it);
		वापस false;
	पूर्ण

	अगर (zero)
		जाओ करोne;

	pt = pgt->pt[type];

	अगर (desc->type == LPT && pgt->refs[1]) अणु
		/* SPT alपढ़ोy exists covering the same range as this LPT,
		 * which means we need to be careful that any LPTEs which
		 * overlap valid SPTEs are unmapped as opposed to invalid
		 * or sparse, which would prevent the MMU from looking at
		 * the SPTEs on some GPUs.
		 */
		क्रम (ptei = pteb = 0; ptei < pten; pteb = ptei) अणु
			bool spte = pgt->pte[ptei] & NVKM_VMM_PTE_SPTES;
			क्रम (ptes = 1, ptei++; ptei < pten; ptes++, ptei++) अणु
				bool next = pgt->pte[ptei] & NVKM_VMM_PTE_SPTES;
				अगर (spte != next)
					अवरोध;
			पूर्ण

			अगर (!spte) अणु
				अगर (pgt->sparse)
					desc->func->sparse(vmm, pt, pteb, ptes);
				अन्यथा
					desc->func->invalid(vmm, pt, pteb, ptes);
				स_रखो(&pgt->pte[pteb], 0x00, ptes);
			पूर्ण अन्यथा अणु
				desc->func->unmap(vmm, pt, pteb, ptes);
				जबतक (ptes--)
					pgt->pte[pteb++] |= NVKM_VMM_PTE_VALID;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pgt->sparse) अणु
			nvkm_vmm_sparse_ptes(desc, pgt, 0, pten);
			desc->func->sparse(vmm, pt, 0, pten);
		पूर्ण अन्यथा अणु
			desc->func->invalid(vmm, pt, 0, pten);
		पूर्ण
	पूर्ण

करोne:
	TRA(it, "PDE write %s", nvkm_vmm_desc_type(desc));
	it->desc[it->lvl].func->pde(it->vmm, pgd, pdei);
	nvkm_vmm_flush_mark(it);
	वापस true;
पूर्ण

अटल bool
nvkm_vmm_ref_swpt(काष्ठा nvkm_vmm_iter *it, काष्ठा nvkm_vmm_pt *pgd, u32 pdei)
अणु
	स्थिर काष्ठा nvkm_vmm_desc *desc = &it->desc[it->lvl - 1];
	काष्ठा nvkm_vmm_pt *pgt = pgd->pde[pdei];

	pgt = nvkm_vmm_pt_new(desc, NVKM_VMM_PDE_SPARSED(pgt), it->page);
	अगर (!pgt) अणु
		अगर (!pgd->refs[0])
			nvkm_vmm_unref_pdes(it);
		वापस false;
	पूर्ण

	pgd->pde[pdei] = pgt;
	वापस true;
पूर्ण

अटल अंतरभूत u64
nvkm_vmm_iter(काष्ठा nvkm_vmm *vmm, स्थिर काष्ठा nvkm_vmm_page *page,
	      u64 addr, u64 size, स्थिर अक्षर *name, bool ref, bool pfn,
	      bool (*REF_PTES)(काष्ठा nvkm_vmm_iter *, bool pfn, u32, u32),
	      nvkm_vmm_pte_func MAP_PTES, काष्ठा nvkm_vmm_map *map,
	      nvkm_vmm_pxe_func CLR_PTES)
अणु
	स्थिर काष्ठा nvkm_vmm_desc *desc = page->desc;
	काष्ठा nvkm_vmm_iter it;
	u64 bits = addr >> page->shअगरt;

	it.page = page;
	it.desc = desc;
	it.vmm = vmm;
	it.cnt = size >> page->shअगरt;
	it.flush = NVKM_VMM_LEVELS_MAX;

	/* Deस्थिरruct address पूर्णांकo PTE indices क्रम each mapping level. */
	क्रम (it.lvl = 0; desc[it.lvl].bits; it.lvl++) अणु
		it.pte[it.lvl] = bits & ((1 << desc[it.lvl].bits) - 1);
		bits >>= desc[it.lvl].bits;
	पूर्ण
	it.max = --it.lvl;
	it.pt[it.max] = vmm->pd;

	it.lvl = 0;
	TRA(&it, "%s: %016llx %016llx %d %lld PTEs", name,
	         addr, size, page->shअगरt, it.cnt);
	it.lvl = it.max;

	/* Depth-first traversal of page tables. */
	जबतक (it.cnt) अणु
		काष्ठा nvkm_vmm_pt *pgt = it.pt[it.lvl];
		स्थिर पूर्णांक type = desc->type == SPT;
		स्थिर u32 pten = 1 << desc->bits;
		स्थिर u32 ptei = it.pte[0];
		स्थिर u32 ptes = min_t(u64, it.cnt, pten - ptei);

		/* Walk करोwn the tree, finding page tables क्रम each level. */
		क्रम (; it.lvl; it.lvl--) अणु
			स्थिर u32 pdei = it.pte[it.lvl];
			काष्ठा nvkm_vmm_pt *pgd = pgt;

			/* Software PT. */
			अगर (ref && NVKM_VMM_PDE_INVALID(pgd->pde[pdei])) अणु
				अगर (!nvkm_vmm_ref_swpt(&it, pgd, pdei))
					जाओ fail;
			पूर्ण
			it.pt[it.lvl - 1] = pgt = pgd->pde[pdei];

			/* Hardware PT.
			 *
			 * This is a separate step from above due to GF100 and
			 * newer having dual page tables at some levels, which
			 * are refcounted independently.
			 */
			अगर (ref && !pgt->refs[desc[it.lvl - 1].type == SPT]) अणु
				अगर (!nvkm_vmm_ref_hwpt(&it, pgd, pdei))
					जाओ fail;
			पूर्ण
		पूर्ण

		/* Handle PTE updates. */
		अगर (!REF_PTES || REF_PTES(&it, pfn, ptei, ptes)) अणु
			काष्ठा nvkm_mmu_pt *pt = pgt->pt[type];
			अगर (MAP_PTES || CLR_PTES) अणु
				अगर (MAP_PTES)
					MAP_PTES(vmm, pt, ptei, ptes, map);
				अन्यथा
					CLR_PTES(vmm, pt, ptei, ptes);
				nvkm_vmm_flush_mark(&it);
			पूर्ण
		पूर्ण

		/* Walk back up the tree to the next position. */
		it.pte[it.lvl] += ptes;
		it.cnt -= ptes;
		अगर (it.cnt) अणु
			जबतक (it.pte[it.lvl] == (1 << desc[it.lvl].bits)) अणु
				it.pte[it.lvl++] = 0;
				it.pte[it.lvl]++;
			पूर्ण
		पूर्ण
	पूर्ण

	nvkm_vmm_flush(&it);
	वापस ~0ULL;

fail:
	/* Reस्थिरruct the failure address so the caller is able to
	 * reverse any partially completed operations.
	 */
	addr = it.pte[it.max--];
	करो अणु
		addr  = addr << desc[it.max].bits;
		addr |= it.pte[it.max];
	पूर्ण जबतक (it.max--);

	वापस addr << page->shअगरt;
पूर्ण

अटल व्योम
nvkm_vmm_ptes_sparse_put(काष्ठा nvkm_vmm *vmm, स्थिर काष्ठा nvkm_vmm_page *page,
			 u64 addr, u64 size)
अणु
	nvkm_vmm_iter(vmm, page, addr, size, "sparse unref", false, false,
		      nvkm_vmm_sparse_unref_ptes, शून्य, शून्य,
		      page->desc->func->invalid ?
		      page->desc->func->invalid : page->desc->func->unmap);
पूर्ण

अटल पूर्णांक
nvkm_vmm_ptes_sparse_get(काष्ठा nvkm_vmm *vmm, स्थिर काष्ठा nvkm_vmm_page *page,
			 u64 addr, u64 size)
अणु
	अगर ((page->type & NVKM_VMM_PAGE_SPARSE)) अणु
		u64 fail = nvkm_vmm_iter(vmm, page, addr, size, "sparse ref",
					 true, false, nvkm_vmm_sparse_ref_ptes,
					 शून्य, शून्य, page->desc->func->sparse);
		अगर (fail != ~0ULL) अणु
			अगर ((size = fail - addr))
				nvkm_vmm_ptes_sparse_put(vmm, page, addr, size);
			वापस -ENOMEM;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_vmm_ptes_sparse(काष्ठा nvkm_vmm *vmm, u64 addr, u64 size, bool ref)
अणु
	स्थिर काष्ठा nvkm_vmm_page *page = vmm->func->page;
	पूर्णांक m = 0, i;
	u64 start = addr;
	u64 block;

	जबतक (size) अणु
		/* Limit maximum page size based on reमुख्यing size. */
		जबतक (size < (1ULL << page[m].shअगरt))
			m++;
		i = m;

		/* Find largest page size suitable क्रम alignment. */
		जबतक (!IS_ALIGNED(addr, 1ULL << page[i].shअगरt))
			i++;

		/* Determine number of PTEs at this page size. */
		अगर (i != m) अणु
			/* Limited to alignment boundary of next page size. */
			u64 next = 1ULL << page[i - 1].shअगरt;
			u64 part = ALIGN(addr, next) - addr;
			अगर (size - part >= next)
				block = (part >> page[i].shअगरt) << page[i].shअगरt;
			अन्यथा
				block = (size >> page[i].shअगरt) << page[i].shअगरt;
		पूर्ण अन्यथा अणु
			block = (size >> page[i].shअगरt) << page[i].shअगरt;
		पूर्ण

		/* Perक्रमm operation. */
		अगर (ref) अणु
			पूर्णांक ret = nvkm_vmm_ptes_sparse_get(vmm, &page[i], addr, block);
			अगर (ret) अणु
				अगर ((size = addr - start))
					nvkm_vmm_ptes_sparse(vmm, start, size, false);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			nvkm_vmm_ptes_sparse_put(vmm, &page[i], addr, block);
		पूर्ण

		size -= block;
		addr += block;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nvkm_vmm_ptes_unmap_put(काष्ठा nvkm_vmm *vmm, स्थिर काष्ठा nvkm_vmm_page *page,
			u64 addr, u64 size, bool sparse, bool pfn)
अणु
	स्थिर काष्ठा nvkm_vmm_desc_func *func = page->desc->func;
	nvkm_vmm_iter(vmm, page, addr, size, "unmap + unref",
		      false, pfn, nvkm_vmm_unref_ptes, शून्य, शून्य,
		      sparse ? func->sparse : func->invalid ? func->invalid :
							      func->unmap);
पूर्ण

अटल पूर्णांक
nvkm_vmm_ptes_get_map(काष्ठा nvkm_vmm *vmm, स्थिर काष्ठा nvkm_vmm_page *page,
		      u64 addr, u64 size, काष्ठा nvkm_vmm_map *map,
		      nvkm_vmm_pte_func func)
अणु
	u64 fail = nvkm_vmm_iter(vmm, page, addr, size, "ref + map", true,
				 false, nvkm_vmm_ref_ptes, func, map, शून्य);
	अगर (fail != ~0ULL) अणु
		अगर ((size = fail - addr))
			nvkm_vmm_ptes_unmap_put(vmm, page, addr, size, false, false);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
nvkm_vmm_ptes_unmap(काष्ठा nvkm_vmm *vmm, स्थिर काष्ठा nvkm_vmm_page *page,
		    u64 addr, u64 size, bool sparse, bool pfn)
अणु
	स्थिर काष्ठा nvkm_vmm_desc_func *func = page->desc->func;
	nvkm_vmm_iter(vmm, page, addr, size, "unmap", false, pfn,
		      शून्य, शून्य, शून्य,
		      sparse ? func->sparse : func->invalid ? func->invalid :
							      func->unmap);
पूर्ण

अटल व्योम
nvkm_vmm_ptes_map(काष्ठा nvkm_vmm *vmm, स्थिर काष्ठा nvkm_vmm_page *page,
		  u64 addr, u64 size, काष्ठा nvkm_vmm_map *map,
		  nvkm_vmm_pte_func func)
अणु
	nvkm_vmm_iter(vmm, page, addr, size, "map", false, false,
		      शून्य, func, map, शून्य);
पूर्ण

अटल व्योम
nvkm_vmm_ptes_put(काष्ठा nvkm_vmm *vmm, स्थिर काष्ठा nvkm_vmm_page *page,
		  u64 addr, u64 size)
अणु
	nvkm_vmm_iter(vmm, page, addr, size, "unref", false, false,
		      nvkm_vmm_unref_ptes, शून्य, शून्य, शून्य);
पूर्ण

अटल पूर्णांक
nvkm_vmm_ptes_get(काष्ठा nvkm_vmm *vmm, स्थिर काष्ठा nvkm_vmm_page *page,
		  u64 addr, u64 size)
अणु
	u64 fail = nvkm_vmm_iter(vmm, page, addr, size, "ref", true, false,
				 nvkm_vmm_ref_ptes, शून्य, शून्य, शून्य);
	अगर (fail != ~0ULL) अणु
		अगर (fail != addr)
			nvkm_vmm_ptes_put(vmm, page, addr, fail - addr);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा nvkm_vma *
nvkm_vma_new(u64 addr, u64 size)
अणु
	काष्ठा nvkm_vma *vma = kzalloc(माप(*vma), GFP_KERNEL);
	अगर (vma) अणु
		vma->addr = addr;
		vma->size = size;
		vma->page = NVKM_VMA_PAGE_NONE;
		vma->refd = NVKM_VMA_PAGE_NONE;
	पूर्ण
	वापस vma;
पूर्ण

काष्ठा nvkm_vma *
nvkm_vma_tail(काष्ठा nvkm_vma *vma, u64 tail)
अणु
	काष्ठा nvkm_vma *new;

	BUG_ON(vma->size == tail);

	अगर (!(new = nvkm_vma_new(vma->addr + (vma->size - tail), tail)))
		वापस शून्य;
	vma->size -= tail;

	new->mapref = vma->mapref;
	new->sparse = vma->sparse;
	new->page = vma->page;
	new->refd = vma->refd;
	new->used = vma->used;
	new->part = vma->part;
	new->user = vma->user;
	new->busy = vma->busy;
	new->mapped = vma->mapped;
	list_add(&new->head, &vma->head);
	वापस new;
पूर्ण

अटल अंतरभूत व्योम
nvkm_vmm_मुक्त_हटाओ(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	rb_erase(&vma->tree, &vmm->मुक्त);
पूर्ण

अटल अंतरभूत व्योम
nvkm_vmm_मुक्त_delete(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	nvkm_vmm_मुक्त_हटाओ(vmm, vma);
	list_del(&vma->head);
	kमुक्त(vma);
पूर्ण

अटल व्योम
nvkm_vmm_मुक्त_insert(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	काष्ठा rb_node **ptr = &vmm->मुक्त.rb_node;
	काष्ठा rb_node *parent = शून्य;

	जबतक (*ptr) अणु
		काष्ठा nvkm_vma *this = rb_entry(*ptr, typeof(*this), tree);
		parent = *ptr;
		अगर (vma->size < this->size)
			ptr = &parent->rb_left;
		अन्यथा
		अगर (vma->size > this->size)
			ptr = &parent->rb_right;
		अन्यथा
		अगर (vma->addr < this->addr)
			ptr = &parent->rb_left;
		अन्यथा
		अगर (vma->addr > this->addr)
			ptr = &parent->rb_right;
		अन्यथा
			BUG();
	पूर्ण

	rb_link_node(&vma->tree, parent, ptr);
	rb_insert_color(&vma->tree, &vmm->मुक्त);
पूर्ण

अटल अंतरभूत व्योम
nvkm_vmm_node_हटाओ(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	rb_erase(&vma->tree, &vmm->root);
पूर्ण

अटल अंतरभूत व्योम
nvkm_vmm_node_delete(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	nvkm_vmm_node_हटाओ(vmm, vma);
	list_del(&vma->head);
	kमुक्त(vma);
पूर्ण

अटल व्योम
nvkm_vmm_node_insert(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	काष्ठा rb_node **ptr = &vmm->root.rb_node;
	काष्ठा rb_node *parent = शून्य;

	जबतक (*ptr) अणु
		काष्ठा nvkm_vma *this = rb_entry(*ptr, typeof(*this), tree);
		parent = *ptr;
		अगर (vma->addr < this->addr)
			ptr = &parent->rb_left;
		अन्यथा
		अगर (vma->addr > this->addr)
			ptr = &parent->rb_right;
		अन्यथा
			BUG();
	पूर्ण

	rb_link_node(&vma->tree, parent, ptr);
	rb_insert_color(&vma->tree, &vmm->root);
पूर्ण

काष्ठा nvkm_vma *
nvkm_vmm_node_search(काष्ठा nvkm_vmm *vmm, u64 addr)
अणु
	काष्ठा rb_node *node = vmm->root.rb_node;
	जबतक (node) अणु
		काष्ठा nvkm_vma *vma = rb_entry(node, typeof(*vma), tree);
		अगर (addr < vma->addr)
			node = node->rb_left;
		अन्यथा
		अगर (addr >= vma->addr + vma->size)
			node = node->rb_right;
		अन्यथा
			वापस vma;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा node(root, dir) (((root)->head.dir == &vmm->list) ? शून्य :             \
	list_entry((root)->head.dir, काष्ठा nvkm_vma, head))

अटल काष्ठा nvkm_vma *
nvkm_vmm_node_merge(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *prev,
		    काष्ठा nvkm_vma *vma, काष्ठा nvkm_vma *next, u64 size)
अणु
	अगर (next) अणु
		अगर (vma->size == size) अणु
			vma->size += next->size;
			nvkm_vmm_node_delete(vmm, next);
			अगर (prev) अणु
				prev->size += vma->size;
				nvkm_vmm_node_delete(vmm, vma);
				वापस prev;
			पूर्ण
			वापस vma;
		पूर्ण
		BUG_ON(prev);

		nvkm_vmm_node_हटाओ(vmm, next);
		vma->size -= size;
		next->addr -= size;
		next->size += size;
		nvkm_vmm_node_insert(vmm, next);
		वापस next;
	पूर्ण

	अगर (prev) अणु
		अगर (vma->size != size) अणु
			nvkm_vmm_node_हटाओ(vmm, vma);
			prev->size += size;
			vma->addr += size;
			vma->size -= size;
			nvkm_vmm_node_insert(vmm, vma);
		पूर्ण अन्यथा अणु
			prev->size += vma->size;
			nvkm_vmm_node_delete(vmm, vma);
		पूर्ण
		वापस prev;
	पूर्ण

	वापस vma;
पूर्ण

काष्ठा nvkm_vma *
nvkm_vmm_node_split(काष्ठा nvkm_vmm *vmm,
		    काष्ठा nvkm_vma *vma, u64 addr, u64 size)
अणु
	काष्ठा nvkm_vma *prev = शून्य;

	अगर (vma->addr != addr) अणु
		prev = vma;
		अगर (!(vma = nvkm_vma_tail(vma, vma->size + vma->addr - addr)))
			वापस शून्य;
		vma->part = true;
		nvkm_vmm_node_insert(vmm, vma);
	पूर्ण

	अगर (vma->size != size) अणु
		काष्ठा nvkm_vma *पंचांगp;
		अगर (!(पंचांगp = nvkm_vma_tail(vma, vma->size - size))) अणु
			nvkm_vmm_node_merge(vmm, prev, vma, शून्य, vma->size);
			वापस शून्य;
		पूर्ण
		पंचांगp->part = true;
		nvkm_vmm_node_insert(vmm, पंचांगp);
	पूर्ण

	वापस vma;
पूर्ण

अटल व्योम
nvkm_vma_dump(काष्ठा nvkm_vma *vma)
अणु
	prपूर्णांकk(KERN_ERR "%016llx %016llx %c%c%c%c%c%c%c%c%c %p\n",
	       vma->addr, (u64)vma->size,
	       vma->used ? '-' : 'F',
	       vma->mapref ? 'R' : '-',
	       vma->sparse ? 'S' : '-',
	       vma->page != NVKM_VMA_PAGE_NONE ? '0' + vma->page : '-',
	       vma->refd != NVKM_VMA_PAGE_NONE ? '0' + vma->refd : '-',
	       vma->part ? 'P' : '-',
	       vma->user ? 'U' : '-',
	       vma->busy ? 'B' : '-',
	       vma->mapped ? 'M' : '-',
	       vma->memory);
पूर्ण

अटल व्योम
nvkm_vmm_dump(काष्ठा nvkm_vmm *vmm)
अणु
	काष्ठा nvkm_vma *vma;
	list_क्रम_each_entry(vma, &vmm->list, head) अणु
		nvkm_vma_dump(vma);
	पूर्ण
पूर्ण

अटल व्योम
nvkm_vmm_dtor(काष्ठा nvkm_vmm *vmm)
अणु
	काष्ठा nvkm_vma *vma;
	काष्ठा rb_node *node;

	अगर (0)
		nvkm_vmm_dump(vmm);

	जबतक ((node = rb_first(&vmm->root))) अणु
		काष्ठा nvkm_vma *vma = rb_entry(node, typeof(*vma), tree);
		nvkm_vmm_put(vmm, &vma);
	पूर्ण

	अगर (vmm->bootstrapped) अणु
		स्थिर काष्ठा nvkm_vmm_page *page = vmm->func->page;
		स्थिर u64 limit = vmm->limit - vmm->start;

		जबतक (page[1].shअगरt)
			page++;

		nvkm_mmu_ptc_dump(vmm->mmu);
		nvkm_vmm_ptes_put(vmm, page, vmm->start, limit);
	पूर्ण

	vma = list_first_entry(&vmm->list, typeof(*vma), head);
	list_del(&vma->head);
	kमुक्त(vma);
	WARN_ON(!list_empty(&vmm->list));

	अगर (vmm->nullp) अणु
		dma_मुक्त_coherent(vmm->mmu->subdev.device->dev, 16 * 1024,
				  vmm->nullp, vmm->null);
	पूर्ण

	अगर (vmm->pd) अणु
		nvkm_mmu_ptc_put(vmm->mmu, true, &vmm->pd->pt[0]);
		nvkm_vmm_pt_del(&vmm->pd);
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_vmm_ctor_managed(काष्ठा nvkm_vmm *vmm, u64 addr, u64 size)
अणु
	काष्ठा nvkm_vma *vma;
	अगर (!(vma = nvkm_vma_new(addr, size)))
		वापस -ENOMEM;
	vma->mapref = true;
	vma->sparse = false;
	vma->used = true;
	vma->user = true;
	nvkm_vmm_node_insert(vmm, vma);
	list_add_tail(&vma->head, &vmm->list);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_vmm_ctor(स्थिर काष्ठा nvkm_vmm_func *func, काष्ठा nvkm_mmu *mmu,
	      u32 pd_header, bool managed, u64 addr, u64 size,
	      काष्ठा lock_class_key *key, स्थिर अक्षर *name,
	      काष्ठा nvkm_vmm *vmm)
अणु
	अटल काष्ठा lock_class_key _key;
	स्थिर काष्ठा nvkm_vmm_page *page = func->page;
	स्थिर काष्ठा nvkm_vmm_desc *desc;
	काष्ठा nvkm_vma *vma;
	पूर्णांक levels, bits = 0, ret;

	vmm->func = func;
	vmm->mmu = mmu;
	vmm->name = name;
	vmm->debug = mmu->subdev.debug;
	kref_init(&vmm->kref);

	__mutex_init(&vmm->mutex, "&vmm->mutex", key ? key : &_key);

	/* Locate the smallest page size supported by the backend, it will
	 * have the the deepest nesting of page tables.
	 */
	जबतक (page[1].shअगरt)
		page++;

	/* Locate the काष्ठाure that describes the layout of the top-level
	 * page table, and determine the number of valid bits in a भव
	 * address.
	 */
	क्रम (levels = 0, desc = page->desc; desc->bits; desc++, levels++)
		bits += desc->bits;
	bits += page->shअगरt;
	desc--;

	अगर (WARN_ON(levels > NVKM_VMM_LEVELS_MAX))
		वापस -EINVAL;

	/* Allocate top-level page table. */
	vmm->pd = nvkm_vmm_pt_new(desc, false, शून्य);
	अगर (!vmm->pd)
		वापस -ENOMEM;
	vmm->pd->refs[0] = 1;
	INIT_LIST_HEAD(&vmm->join);

	/* ... and the GPU storage क्रम it, except on Tesla-class GPUs that
	 * have the PD embedded in the instance काष्ठाure.
	 */
	अगर (desc->size) अणु
		स्थिर u32 size = pd_header + desc->size * (1 << desc->bits);
		vmm->pd->pt[0] = nvkm_mmu_ptc_get(mmu, size, desc->align, true);
		अगर (!vmm->pd->pt[0])
			वापस -ENOMEM;
	पूर्ण

	/* Initialise address-space MM. */
	INIT_LIST_HEAD(&vmm->list);
	vmm->मुक्त = RB_ROOT;
	vmm->root = RB_ROOT;

	अगर (managed) अणु
		/* Address-space will be managed by the client क्रम the most
		 * part, except क्रम a specअगरied area where NVKM allocations
		 * are allowed to be placed.
		 */
		vmm->start = 0;
		vmm->limit = 1ULL << bits;
		अगर (addr + size < addr || addr + size > vmm->limit)
			वापस -EINVAL;

		/* Client-managed area beक्रमe the NVKM-managed area. */
		अगर (addr && (ret = nvkm_vmm_ctor_managed(vmm, 0, addr)))
			वापस ret;

		/* NVKM-managed area. */
		अगर (size) अणु
			अगर (!(vma = nvkm_vma_new(addr, size)))
				वापस -ENOMEM;
			nvkm_vmm_मुक्त_insert(vmm, vma);
			list_add_tail(&vma->head, &vmm->list);
		पूर्ण

		/* Client-managed area after the NVKM-managed area. */
		addr = addr + size;
		size = vmm->limit - addr;
		अगर (size && (ret = nvkm_vmm_ctor_managed(vmm, addr, size)))
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Address-space fully managed by NVKM, requiring calls to
		 * nvkm_vmm_get()/nvkm_vmm_put() to allocate address-space.
		 */
		vmm->start = addr;
		vmm->limit = size ? (addr + size) : (1ULL << bits);
		अगर (vmm->start > vmm->limit || vmm->limit > (1ULL << bits))
			वापस -EINVAL;

		अगर (!(vma = nvkm_vma_new(vmm->start, vmm->limit - vmm->start)))
			वापस -ENOMEM;

		nvkm_vmm_मुक्त_insert(vmm, vma);
		list_add(&vma->head, &vmm->list);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvkm_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *func, काष्ठा nvkm_mmu *mmu,
	      u32 hdr, bool managed, u64 addr, u64 size,
	      काष्ठा lock_class_key *key, स्थिर अक्षर *name,
	      काष्ठा nvkm_vmm **pvmm)
अणु
	अगर (!(*pvmm = kzalloc(माप(**pvmm), GFP_KERNEL)))
		वापस -ENOMEM;
	वापस nvkm_vmm_ctor(func, mmu, hdr, managed, addr, size, key, name, *pvmm);
पूर्ण

अटल काष्ठा nvkm_vma *
nvkm_vmm_pfn_split_merge(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma,
			 u64 addr, u64 size, u8 page, bool map)
अणु
	काष्ठा nvkm_vma *prev = शून्य;
	काष्ठा nvkm_vma *next = शून्य;

	अगर (vma->addr == addr && vma->part && (prev = node(vma, prev))) अणु
		अगर (prev->memory || prev->mapped != map)
			prev = शून्य;
	पूर्ण

	अगर (vma->addr + vma->size == addr + size && (next = node(vma, next))) अणु
		अगर (!next->part ||
		    next->memory || next->mapped != map)
			next = शून्य;
	पूर्ण

	अगर (prev || next)
		वापस nvkm_vmm_node_merge(vmm, prev, vma, next, size);
	वापस nvkm_vmm_node_split(vmm, vma, addr, size);
पूर्ण

पूर्णांक
nvkm_vmm_pfn_unmap(काष्ठा nvkm_vmm *vmm, u64 addr, u64 size)
अणु
	काष्ठा nvkm_vma *vma = nvkm_vmm_node_search(vmm, addr);
	काष्ठा nvkm_vma *next;
	u64 limit = addr + size;
	u64 start = addr;

	अगर (!vma)
		वापस -EINVAL;

	करो अणु
		अगर (!vma->mapped || vma->memory)
			जारी;

		size = min(limit - start, vma->size - (start - vma->addr));

		nvkm_vmm_ptes_unmap_put(vmm, &vmm->func->page[vma->refd],
					start, size, false, true);

		next = nvkm_vmm_pfn_split_merge(vmm, vma, start, size, 0, false);
		अगर (!WARN_ON(!next)) अणु
			vma = next;
			vma->refd = NVKM_VMA_PAGE_NONE;
			vma->mapped = false;
		पूर्ण
	पूर्ण जबतक ((vma = node(vma, next)) && (start = vma->addr) < limit);

	वापस 0;
पूर्ण

/*TODO:
 * - Aव्योम PT पढ़ोback (क्रम dma_unmap etc), this might end up being dealt
 *   with inside HMM, which would be a lot nicer क्रम us to deal with.
 * - Support क्रम प्रणालीs without a 4KiB page size.
 */
पूर्णांक
nvkm_vmm_pfn_map(काष्ठा nvkm_vmm *vmm, u8 shअगरt, u64 addr, u64 size, u64 *pfn)
अणु
	स्थिर काष्ठा nvkm_vmm_page *page = vmm->func->page;
	काष्ठा nvkm_vma *vma, *पंचांगp;
	u64 limit = addr + size;
	u64 start = addr;
	पूर्णांक pm = size >> shअगरt;
	पूर्णांक pi = 0;

	/* Only support mapping where the page size of the incoming page
	 * array matches a page size available क्रम direct mapping.
	 */
	जबतक (page->shअगरt && (page->shअगरt != shअगरt ||
	       page->desc->func->pfn == शून्य))
		page++;

	अगर (!page->shअगरt || !IS_ALIGNED(addr, 1ULL << shअगरt) ||
			    !IS_ALIGNED(size, 1ULL << shअगरt) ||
	    addr + size < addr || addr + size > vmm->limit) अणु
		VMM_DEBUG(vmm, "paged map %d %d %016llx %016llx\n",
			  shअगरt, page->shअगरt, addr, size);
		वापस -EINVAL;
	पूर्ण

	अगर (!(vma = nvkm_vmm_node_search(vmm, addr)))
		वापस -ENOENT;

	करो अणु
		bool map = !!(pfn[pi] & NVKM_VMM_PFN_V);
		bool mapped = vma->mapped;
		u64 size = limit - start;
		u64 addr = start;
		पूर्णांक pn, ret = 0;

		/* Narrow the operation winकरोw to cover a single action (page
		 * should be mapped or not) within a single VMA.
		 */
		क्रम (pn = 0; pi + pn < pm; pn++) अणु
			अगर (map != !!(pfn[pi + pn] & NVKM_VMM_PFN_V))
				अवरोध;
		पूर्ण
		size = min_t(u64, size, pn << page->shअगरt);
		size = min_t(u64, size, vma->size + vma->addr - addr);

		/* Reject any operation to unmanaged regions, and areas that
		 * have nvkm_memory objects mapped in them alपढ़ोy.
		 */
		अगर (!vma->mapref || vma->memory) अणु
			ret = -EINVAL;
			जाओ next;
		पूर्ण

		/* In order to both properly refcount GPU page tables, and
		 * prevent "normal" mappings and these direct mappings from
		 * पूर्णांकerfering with each other, we need to track contiguous
		 * ranges that have been mapped with this पूर्णांकerface.
		 *
		 * Here we attempt to either split an existing VMA so we're
		 * able to flag the region as either unmapped/mapped, or to
		 * merge with adjacent VMAs that are alपढ़ोy compatible.
		 *
		 * If the region is alपढ़ोy compatible, nothing is required.
		 */
		अगर (map != mapped) अणु
			पंचांगp = nvkm_vmm_pfn_split_merge(vmm, vma, addr, size,
						       page -
						       vmm->func->page, map);
			अगर (WARN_ON(!पंचांगp)) अणु
				ret = -ENOMEM;
				जाओ next;
			पूर्ण

			अगर ((पंचांगp->mapped = map))
				पंचांगp->refd = page - vmm->func->page;
			अन्यथा
				पंचांगp->refd = NVKM_VMA_PAGE_NONE;
			vma = पंचांगp;
		पूर्ण

		/* Update HW page tables. */
		अगर (map) अणु
			काष्ठा nvkm_vmm_map args;
			args.page = page;
			args.pfn = &pfn[pi];

			अगर (!mapped) अणु
				ret = nvkm_vmm_ptes_get_map(vmm, page, addr,
							    size, &args, page->
							    desc->func->pfn);
			पूर्ण अन्यथा अणु
				nvkm_vmm_ptes_map(vmm, page, addr, size, &args,
						  page->desc->func->pfn);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (mapped) अणु
				nvkm_vmm_ptes_unmap_put(vmm, page, addr, size,
							false, true);
			पूर्ण
		पूर्ण

next:
		/* Iterate to next operation. */
		अगर (vma->addr + vma->size == addr + size)
			vma = node(vma, next);
		start += size;

		अगर (ret) अणु
			/* Failure is संकेतled by clearing the valid bit on
			 * any PFN that couldn't be modअगरied as requested.
			 */
			जबतक (size) अणु
				pfn[pi++] = NVKM_VMM_PFN_NONE;
				size -= 1 << page->shअगरt;
			पूर्ण
		पूर्ण अन्यथा अणु
			pi += size >> page->shअगरt;
		पूर्ण
	पूर्ण जबतक (vma && start < limit);

	वापस 0;
पूर्ण

व्योम
nvkm_vmm_unmap_region(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	काष्ठा nvkm_vma *prev = शून्य;
	काष्ठा nvkm_vma *next;

	nvkm_memory_tags_put(vma->memory, vmm->mmu->subdev.device, &vma->tags);
	nvkm_memory_unref(&vma->memory);
	vma->mapped = false;

	अगर (vma->part && (prev = node(vma, prev)) && prev->mapped)
		prev = शून्य;
	अगर ((next = node(vma, next)) && (!next->part || next->mapped))
		next = शून्य;
	nvkm_vmm_node_merge(vmm, prev, vma, next, vma->size);
पूर्ण

व्योम
nvkm_vmm_unmap_locked(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma, bool pfn)
अणु
	स्थिर काष्ठा nvkm_vmm_page *page = &vmm->func->page[vma->refd];

	अगर (vma->mapref) अणु
		nvkm_vmm_ptes_unmap_put(vmm, page, vma->addr, vma->size, vma->sparse, pfn);
		vma->refd = NVKM_VMA_PAGE_NONE;
	पूर्ण अन्यथा अणु
		nvkm_vmm_ptes_unmap(vmm, page, vma->addr, vma->size, vma->sparse, pfn);
	पूर्ण

	nvkm_vmm_unmap_region(vmm, vma);
पूर्ण

व्योम
nvkm_vmm_unmap(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	अगर (vma->memory) अणु
		mutex_lock(&vmm->mutex);
		nvkm_vmm_unmap_locked(vmm, vma, false);
		mutex_unlock(&vmm->mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_vmm_map_valid(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma,
		   व्योम *argv, u32 argc, काष्ठा nvkm_vmm_map *map)
अणु
	चयन (nvkm_memory_target(map->memory)) अणु
	हाल NVKM_MEM_TARGET_VRAM:
		अगर (!(map->page->type & NVKM_VMM_PAGE_VRAM)) अणु
			VMM_DEBUG(vmm, "%d !VRAM", map->page->shअगरt);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल NVKM_MEM_TARGET_HOST:
	हाल NVKM_MEM_TARGET_NCOH:
		अगर (!(map->page->type & NVKM_VMM_PAGE_HOST)) अणु
			VMM_DEBUG(vmm, "%d !HOST", map->page->shअगरt);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -ENOSYS;
	पूर्ण

	अगर (!IS_ALIGNED(     vma->addr, 1ULL << map->page->shअगरt) ||
	    !IS_ALIGNED((u64)vma->size, 1ULL << map->page->shअगरt) ||
	    !IS_ALIGNED(   map->offset, 1ULL << map->page->shअगरt) ||
	    nvkm_memory_page(map->memory) < map->page->shअगरt) अणु
		VMM_DEBUG(vmm, "alignment %016llx %016llx %016llx %d %d",
		    vma->addr, (u64)vma->size, map->offset, map->page->shअगरt,
		    nvkm_memory_page(map->memory));
		वापस -EINVAL;
	पूर्ण

	वापस vmm->func->valid(vmm, argv, argc, map);
पूर्ण

अटल पूर्णांक
nvkm_vmm_map_choose(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma,
		    व्योम *argv, u32 argc, काष्ठा nvkm_vmm_map *map)
अणु
	क्रम (map->page = vmm->func->page; map->page->shअगरt; map->page++) अणु
		VMM_DEBUG(vmm, "trying %d", map->page->shअगरt);
		अगर (!nvkm_vmm_map_valid(vmm, vma, argv, argc, map))
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_vmm_map_locked(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma,
		    व्योम *argv, u32 argc, काष्ठा nvkm_vmm_map *map)
अणु
	nvkm_vmm_pte_func func;
	पूर्णांक ret;

	/* Make sure we won't overrun the end of the memory object. */
	अगर (unlikely(nvkm_memory_size(map->memory) < map->offset + vma->size)) अणु
		VMM_DEBUG(vmm, "overrun %016llx %016llx %016llx",
			  nvkm_memory_size(map->memory),
			  map->offset, (u64)vma->size);
		वापस -EINVAL;
	पूर्ण

	/* Check reमुख्यing arguments क्रम validity. */
	अगर (vma->page == NVKM_VMA_PAGE_NONE &&
	    vma->refd == NVKM_VMA_PAGE_NONE) अणु
		/* Find the largest page size we can perक्रमm the mapping at. */
		स्थिर u32 debug = vmm->debug;
		vmm->debug = 0;
		ret = nvkm_vmm_map_choose(vmm, vma, argv, argc, map);
		vmm->debug = debug;
		अगर (ret) अणु
			VMM_DEBUG(vmm, "invalid at any page size");
			nvkm_vmm_map_choose(vmm, vma, argv, argc, map);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Page size of the VMA is alपढ़ोy pre-determined. */
		अगर (vma->refd != NVKM_VMA_PAGE_NONE)
			map->page = &vmm->func->page[vma->refd];
		अन्यथा
			map->page = &vmm->func->page[vma->page];

		ret = nvkm_vmm_map_valid(vmm, vma, argv, argc, map);
		अगर (ret) अणु
			VMM_DEBUG(vmm, "invalid %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Deal with the 'offset' argument, and fetch the backend function. */
	map->off = map->offset;
	अगर (map->mem) अणु
		क्रम (; map->off; map->mem = map->mem->next) अणु
			u64 size = (u64)map->mem->length << NVKM_RAM_MM_SHIFT;
			अगर (size > map->off)
				अवरोध;
			map->off -= size;
		पूर्ण
		func = map->page->desc->func->mem;
	पूर्ण अन्यथा
	अगर (map->sgl) अणु
		क्रम (; map->off; map->sgl = sg_next(map->sgl)) अणु
			u64 size = sg_dma_len(map->sgl);
			अगर (size > map->off)
				अवरोध;
			map->off -= size;
		पूर्ण
		func = map->page->desc->func->sgl;
	पूर्ण अन्यथा अणु
		map->dma += map->offset >> PAGE_SHIFT;
		map->off  = map->offset & PAGE_MASK;
		func = map->page->desc->func->dma;
	पूर्ण

	/* Perक्रमm the map. */
	अगर (vma->refd == NVKM_VMA_PAGE_NONE) अणु
		ret = nvkm_vmm_ptes_get_map(vmm, map->page, vma->addr, vma->size, map, func);
		अगर (ret)
			वापस ret;

		vma->refd = map->page - vmm->func->page;
	पूर्ण अन्यथा अणु
		nvkm_vmm_ptes_map(vmm, map->page, vma->addr, vma->size, map, func);
	पूर्ण

	nvkm_memory_tags_put(vma->memory, vmm->mmu->subdev.device, &vma->tags);
	nvkm_memory_unref(&vma->memory);
	vma->memory = nvkm_memory_ref(map->memory);
	vma->mapped = true;
	vma->tags = map->tags;
	वापस 0;
पूर्ण

पूर्णांक
nvkm_vmm_map(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma, व्योम *argv, u32 argc,
	     काष्ठा nvkm_vmm_map *map)
अणु
	पूर्णांक ret;
	mutex_lock(&vmm->mutex);
	ret = nvkm_vmm_map_locked(vmm, vma, argv, argc, map);
	vma->busy = false;
	mutex_unlock(&vmm->mutex);
	वापस ret;
पूर्ण

अटल व्योम
nvkm_vmm_put_region(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	काष्ठा nvkm_vma *prev, *next;

	अगर ((prev = node(vma, prev)) && !prev->used) अणु
		vma->addr  = prev->addr;
		vma->size += prev->size;
		nvkm_vmm_मुक्त_delete(vmm, prev);
	पूर्ण

	अगर ((next = node(vma, next)) && !next->used) अणु
		vma->size += next->size;
		nvkm_vmm_मुक्त_delete(vmm, next);
	पूर्ण

	nvkm_vmm_मुक्त_insert(vmm, vma);
पूर्ण

व्योम
nvkm_vmm_put_locked(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma)
अणु
	स्थिर काष्ठा nvkm_vmm_page *page = vmm->func->page;
	काष्ठा nvkm_vma *next = vma;

	BUG_ON(vma->part);

	अगर (vma->mapref || !vma->sparse) अणु
		करो अणु
			स्थिर bool mem = next->memory != शून्य;
			स्थिर bool map = next->mapped;
			स्थिर u8  refd = next->refd;
			स्थिर u64 addr = next->addr;
			u64 size = next->size;

			/* Merge regions that are in the same state. */
			जबतक ((next = node(next, next)) && next->part &&
			       (next->mapped == map) &&
			       (next->memory != शून्य) == mem &&
			       (next->refd == refd))
				size += next->size;

			अगर (map) अणु
				/* Region(s) are mapped, merge the unmap
				 * and dereference पूर्णांकo a single walk of
				 * the page tree.
				 */
				nvkm_vmm_ptes_unmap_put(vmm, &page[refd], addr,
							size, vma->sparse,
							!mem);
			पूर्ण अन्यथा
			अगर (refd != NVKM_VMA_PAGE_NONE) अणु
				/* Drop allocation-समय PTE references. */
				nvkm_vmm_ptes_put(vmm, &page[refd], addr, size);
			पूर्ण
		पूर्ण जबतक (next && next->part);
	पूर्ण

	/* Merge any mapped regions that were split from the initial
	 * address-space allocation back पूर्णांकo the allocated VMA, and
	 * release memory/compression resources.
	 */
	next = vma;
	करो अणु
		अगर (next->mapped)
			nvkm_vmm_unmap_region(vmm, next);
	पूर्ण जबतक ((next = node(vma, next)) && next->part);

	अगर (vma->sparse && !vma->mapref) अणु
		/* Sparse region that was allocated with a fixed page size,
		 * meaning all relevant PTEs were referenced once when the
		 * region was allocated, and reमुख्यed that way, regardless
		 * of whether memory was mapped पूर्णांकo it afterwards.
		 *
		 * The process of unmapping, unsparsing, and dereferencing
		 * PTEs can be करोne in a single page tree walk.
		 */
		nvkm_vmm_ptes_sparse_put(vmm, &page[vma->refd], vma->addr, vma->size);
	पूर्ण अन्यथा
	अगर (vma->sparse) अणु
		/* Sparse region that wasn't allocated with a fixed page size,
		 * PTE references were taken both at allocation समय (to make
		 * the GPU see the region as sparse), and when mapping memory
		 * पूर्णांकo the region.
		 *
		 * The latter was handled above, and the reमुख्यing references
		 * are dealt with here.
		 */
		nvkm_vmm_ptes_sparse(vmm, vma->addr, vma->size, false);
	पूर्ण

	/* Remove VMA from the list of allocated nodes. */
	nvkm_vmm_node_हटाओ(vmm, vma);

	/* Merge VMA back पूर्णांकo the मुक्त list. */
	vma->page = NVKM_VMA_PAGE_NONE;
	vma->refd = NVKM_VMA_PAGE_NONE;
	vma->used = false;
	vma->user = false;
	nvkm_vmm_put_region(vmm, vma);
पूर्ण

व्योम
nvkm_vmm_put(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma **pvma)
अणु
	काष्ठा nvkm_vma *vma = *pvma;
	अगर (vma) अणु
		mutex_lock(&vmm->mutex);
		nvkm_vmm_put_locked(vmm, vma);
		mutex_unlock(&vmm->mutex);
		*pvma = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_vmm_get_locked(काष्ठा nvkm_vmm *vmm, bool getref, bool mapref, bool sparse,
		    u8 shअगरt, u8 align, u64 size, काष्ठा nvkm_vma **pvma)
अणु
	स्थिर काष्ठा nvkm_vmm_page *page = &vmm->func->page[NVKM_VMA_PAGE_NONE];
	काष्ठा rb_node *node = शून्य, *temp;
	काष्ठा nvkm_vma *vma = शून्य, *पंचांगp;
	u64 addr, tail;
	पूर्णांक ret;

	VMM_TRACE(vmm, "getref %d mapref %d sparse %d "
		       "shift: %d align: %d size: %016llx",
		  getref, mapref, sparse, shअगरt, align, size);

	/* Zero-sized, or lazily-allocated sparse VMAs, make no sense. */
	अगर (unlikely(!size || (!getref && !mapref && sparse))) अणु
		VMM_DEBUG(vmm, "args %016llx %d %d %d",
			  size, getref, mapref, sparse);
		वापस -EINVAL;
	पूर्ण

	/* Tesla-class GPUs can only select page size per-PDE, which means
	 * we're required to know the mapping granularity up-front to find
	 * a suitable region of address-space.
	 *
	 * The same goes अगर we're requesting up-front allocation of PTES.
	 */
	अगर (unlikely((getref || vmm->func->page_block) && !shअगरt)) अणु
		VMM_DEBUG(vmm, "page size required: %d %016llx",
			  getref, vmm->func->page_block);
		वापस -EINVAL;
	पूर्ण

	/* If a specअगरic page size was requested, determine its index and
	 * make sure the requested size is a multiple of the page size.
	 */
	अगर (shअगरt) अणु
		क्रम (page = vmm->func->page; page->shअगरt; page++) अणु
			अगर (shअगरt == page->shअगरt)
				अवरोध;
		पूर्ण

		अगर (!page->shअगरt || !IS_ALIGNED(size, 1ULL << page->shअगरt)) अणु
			VMM_DEBUG(vmm, "page %d %016llx", shअगरt, size);
			वापस -EINVAL;
		पूर्ण
		align = max_t(u8, align, shअगरt);
	पूर्ण अन्यथा अणु
		align = max_t(u8, align, 12);
	पूर्ण

	/* Locate smallest block that can possibly satisfy the allocation. */
	temp = vmm->मुक्त.rb_node;
	जबतक (temp) अणु
		काष्ठा nvkm_vma *this = rb_entry(temp, typeof(*this), tree);
		अगर (this->size < size) अणु
			temp = temp->rb_right;
		पूर्ण अन्यथा अणु
			node = temp;
			temp = temp->rb_left;
		पूर्ण
	पूर्ण

	अगर (unlikely(!node))
		वापस -ENOSPC;

	/* Take पूर्णांकo account alignment restrictions, trying larger blocks
	 * in turn until we find a suitable मुक्त block.
	 */
	करो अणु
		काष्ठा nvkm_vma *this = rb_entry(node, typeof(*this), tree);
		काष्ठा nvkm_vma *prev = node(this, prev);
		काष्ठा nvkm_vma *next = node(this, next);
		स्थिर पूर्णांक p = page - vmm->func->page;

		addr = this->addr;
		अगर (vmm->func->page_block && prev && prev->page != p)
			addr = ALIGN(addr, vmm->func->page_block);
		addr = ALIGN(addr, 1ULL << align);

		tail = this->addr + this->size;
		अगर (vmm->func->page_block && next && next->page != p)
			tail = ALIGN_DOWN(tail, vmm->func->page_block);

		अगर (addr <= tail && tail - addr >= size) अणु
			nvkm_vmm_मुक्त_हटाओ(vmm, this);
			vma = this;
			अवरोध;
		पूर्ण
	पूर्ण जबतक ((node = rb_next(node)));

	अगर (unlikely(!vma))
		वापस -ENOSPC;

	/* If the VMA we found isn't alपढ़ोy exactly the requested size,
	 * it needs to be split, and the reमुख्यing मुक्त blocks वापसed.
	 */
	अगर (addr != vma->addr) अणु
		अगर (!(पंचांगp = nvkm_vma_tail(vma, vma->size + vma->addr - addr))) अणु
			nvkm_vmm_put_region(vmm, vma);
			वापस -ENOMEM;
		पूर्ण
		nvkm_vmm_मुक्त_insert(vmm, vma);
		vma = पंचांगp;
	पूर्ण

	अगर (size != vma->size) अणु
		अगर (!(पंचांगp = nvkm_vma_tail(vma, vma->size - size))) अणु
			nvkm_vmm_put_region(vmm, vma);
			वापस -ENOMEM;
		पूर्ण
		nvkm_vmm_मुक्त_insert(vmm, पंचांगp);
	पूर्ण

	/* Pre-allocate page tables and/or setup sparse mappings. */
	अगर (sparse && getref)
		ret = nvkm_vmm_ptes_sparse_get(vmm, page, vma->addr, vma->size);
	अन्यथा अगर (sparse)
		ret = nvkm_vmm_ptes_sparse(vmm, vma->addr, vma->size, true);
	अन्यथा अगर (getref)
		ret = nvkm_vmm_ptes_get(vmm, page, vma->addr, vma->size);
	अन्यथा
		ret = 0;
	अगर (ret) अणु
		nvkm_vmm_put_region(vmm, vma);
		वापस ret;
	पूर्ण

	vma->mapref = mapref && !getref;
	vma->sparse = sparse;
	vma->page = page - vmm->func->page;
	vma->refd = getref ? vma->page : NVKM_VMA_PAGE_NONE;
	vma->used = true;
	nvkm_vmm_node_insert(vmm, vma);
	*pvma = vma;
	वापस 0;
पूर्ण

पूर्णांक
nvkm_vmm_get(काष्ठा nvkm_vmm *vmm, u8 page, u64 size, काष्ठा nvkm_vma **pvma)
अणु
	पूर्णांक ret;
	mutex_lock(&vmm->mutex);
	ret = nvkm_vmm_get_locked(vmm, false, true, false, page, 0, size, pvma);
	mutex_unlock(&vmm->mutex);
	वापस ret;
पूर्ण

व्योम
nvkm_vmm_part(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst)
अणु
	अगर (inst && vmm && vmm->func->part) अणु
		mutex_lock(&vmm->mutex);
		vmm->func->part(vmm, inst);
		mutex_unlock(&vmm->mutex);
	पूर्ण
पूर्ण

पूर्णांक
nvkm_vmm_join(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst)
अणु
	पूर्णांक ret = 0;
	अगर (vmm->func->join) अणु
		mutex_lock(&vmm->mutex);
		ret = vmm->func->join(vmm, inst);
		mutex_unlock(&vmm->mutex);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool
nvkm_vmm_boot_ptes(काष्ठा nvkm_vmm_iter *it, bool pfn, u32 ptei, u32 ptes)
अणु
	स्थिर काष्ठा nvkm_vmm_desc *desc = it->desc;
	स्थिर पूर्णांक type = desc->type == SPT;
	nvkm_memory_boot(it->pt[0]->pt[type]->memory, it->vmm);
	वापस false;
पूर्ण

पूर्णांक
nvkm_vmm_boot(काष्ठा nvkm_vmm *vmm)
अणु
	स्थिर काष्ठा nvkm_vmm_page *page = vmm->func->page;
	स्थिर u64 limit = vmm->limit - vmm->start;
	पूर्णांक ret;

	जबतक (page[1].shअगरt)
		page++;

	ret = nvkm_vmm_ptes_get(vmm, page, vmm->start, limit);
	अगर (ret)
		वापस ret;

	nvkm_vmm_iter(vmm, page, vmm->start, limit, "bootstrap", false, false,
		      nvkm_vmm_boot_ptes, शून्य, शून्य, शून्य);
	vmm->bootstrapped = true;
	वापस 0;
पूर्ण

अटल व्योम
nvkm_vmm_del(काष्ठा kref *kref)
अणु
	काष्ठा nvkm_vmm *vmm = container_of(kref, typeof(*vmm), kref);
	nvkm_vmm_dtor(vmm);
	kमुक्त(vmm);
पूर्ण

व्योम
nvkm_vmm_unref(काष्ठा nvkm_vmm **pvmm)
अणु
	काष्ठा nvkm_vmm *vmm = *pvmm;
	अगर (vmm) अणु
		kref_put(&vmm->kref, nvkm_vmm_del);
		*pvmm = शून्य;
	पूर्ण
पूर्ण

काष्ठा nvkm_vmm *
nvkm_vmm_ref(काष्ठा nvkm_vmm *vmm)
अणु
	अगर (vmm)
		kref_get(&vmm->kref);
	वापस vmm;
पूर्ण

पूर्णांक
nvkm_vmm_new(काष्ठा nvkm_device *device, u64 addr, u64 size, व्योम *argv,
	     u32 argc, काष्ठा lock_class_key *key, स्थिर अक्षर *name,
	     काष्ठा nvkm_vmm **pvmm)
अणु
	काष्ठा nvkm_mmu *mmu = device->mmu;
	काष्ठा nvkm_vmm *vmm = शून्य;
	पूर्णांक ret;
	ret = mmu->func->vmm.ctor(mmu, false, addr, size, argv, argc,
				  key, name, &vmm);
	अगर (ret)
		nvkm_vmm_unref(&vmm);
	*pvmm = vmm;
	वापस ret;
पूर्ण
