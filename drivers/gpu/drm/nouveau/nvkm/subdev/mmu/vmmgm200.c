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
#समावेश "vmm.h"

#समावेश <nvअगर/अगरb00d.h>
#समावेश <nvअगर/unpack.h>

अटल व्योम
gm200_vmm_pgt_sparse(काष्ठा nvkm_vmm *vmm,
		     काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	/* VALID_FALSE + VOL tells the MMU to treat the PTE as sparse. */
	VMM_FO064(pt, vmm, ptei * 8, BIT_ULL(32) /* VOL. */, ptes);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
gm200_vmm_spt = अणु
	.unmap = gf100_vmm_pgt_unmap,
	.sparse = gm200_vmm_pgt_sparse,
	.mem = gf100_vmm_pgt_mem,
	.dma = gf100_vmm_pgt_dma,
	.sgl = gf100_vmm_pgt_sgl,
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_desc_func
gm200_vmm_lpt = अणु
	.invalid = gk104_vmm_lpt_invalid,
	.unmap = gf100_vmm_pgt_unmap,
	.sparse = gm200_vmm_pgt_sparse,
	.mem = gf100_vmm_pgt_mem,
पूर्ण;

अटल व्योम
gm200_vmm_pgd_sparse(काष्ठा nvkm_vmm *vmm,
		     काष्ठा nvkm_mmu_pt *pt, u32 pdei, u32 pdes)
अणु
	/* VALID_FALSE + VOL_BIG tells the MMU to treat the PDE as sparse. */
	VMM_FO064(pt, vmm, pdei * 8, BIT_ULL(35) /* VOL_BIG. */, pdes);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
gm200_vmm_pgd = अणु
	.unmap = gf100_vmm_pgt_unmap,
	.sparse = gm200_vmm_pgd_sparse,
	.pde = gf100_vmm_pgd_pde,
पूर्ण;

स्थिर काष्ठा nvkm_vmm_desc
gm200_vmm_desc_17_12[] = अणु
	अणु SPT, 15, 8, 0x1000, &gm200_vmm_spt पूर्ण,
	अणु PGD, 13, 8, 0x1000, &gm200_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_vmm_desc
gm200_vmm_desc_17_17[] = अणु
	अणु LPT, 10, 8, 0x1000, &gm200_vmm_lpt पूर्ण,
	अणु PGD, 13, 8, 0x1000, &gm200_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_vmm_desc
gm200_vmm_desc_16_12[] = अणु
	अणु SPT, 14, 8, 0x1000, &gm200_vmm_spt पूर्ण,
	अणु PGD, 14, 8, 0x1000, &gm200_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_vmm_desc
gm200_vmm_desc_16_16[] = अणु
	अणु LPT, 10, 8, 0x1000, &gm200_vmm_lpt पूर्ण,
	अणु PGD, 14, 8, 0x1000, &gm200_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gm200_vmm_join_(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst, u64 base)
अणु
	अगर (vmm->func->page[1].shअगरt == 16)
		base |= BIT_ULL(11);
	वापस gf100_vmm_join_(vmm, inst, base);
पूर्ण

पूर्णांक
gm200_vmm_join(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst)
अणु
	वापस gm200_vmm_join_(vmm, inst, 0);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
gm200_vmm_17 = अणु
	.join = gm200_vmm_join,
	.part = gf100_vmm_part,
	.aper = gf100_vmm_aper,
	.valid = gf100_vmm_valid,
	.flush = gf100_vmm_flush,
	.invalidate_pdb = gf100_vmm_invalidate_pdb,
	.page = अणु
		अणु 27, &gm200_vmm_desc_17_17[1], NVKM_VMM_PAGE_Sxxx पूर्ण,
		अणु 17, &gm200_vmm_desc_17_17[0], NVKM_VMM_PAGE_SVxC पूर्ण,
		अणु 12, &gm200_vmm_desc_17_12[0], NVKM_VMM_PAGE_SVHx पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_func
gm200_vmm_16 = अणु
	.join = gm200_vmm_join,
	.part = gf100_vmm_part,
	.aper = gf100_vmm_aper,
	.valid = gf100_vmm_valid,
	.flush = gf100_vmm_flush,
	.invalidate_pdb = gf100_vmm_invalidate_pdb,
	.page = अणु
		अणु 27, &gm200_vmm_desc_16_16[1], NVKM_VMM_PAGE_Sxxx पूर्ण,
		अणु 16, &gm200_vmm_desc_16_16[0], NVKM_VMM_PAGE_SVxC पूर्ण,
		अणु 12, &gm200_vmm_desc_16_12[0], NVKM_VMM_PAGE_SVHx पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gm200_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *func_16,
	       स्थिर काष्ठा nvkm_vmm_func *func_17,
	       काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	       व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	       स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	स्थिर काष्ठा nvkm_vmm_func *func;
	जोड़ अणु
		काष्ठा gm200_vmm_vn vn;
		काष्ठा gm200_vmm_v0 v0;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		चयन (args->v0.bigpage) अणु
		हाल 16: func = func_16; अवरोध;
		हाल 17: func = func_17; अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
	अगर (!(ret = nvअगर_unvers(ret, &argv, &argc, args->vn))) अणु
		func = func_17;
	पूर्ण अन्यथा
		वापस ret;

	वापस nvkm_vmm_new_(func, mmu, 0, managed, addr, size, key, name, pvmm);
पूर्ण

पूर्णांक
gm200_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	      व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	      स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	वापस gm200_vmm_new_(&gm200_vmm_16, &gm200_vmm_17, mmu, managed, addr,
			      size, argv, argc, key, name, pvmm);
पूर्ण

पूर्णांक
gm200_vmm_new_fixed(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
		    व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
		    स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	वापस gf100_vmm_new_(&gm200_vmm_16, &gm200_vmm_17, mmu, managed, addr,
			      size, argv, argc, key, name, pvmm);
पूर्ण
