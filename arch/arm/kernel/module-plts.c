<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2017 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/elf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sort.h>
#समावेश <linux/moduleloader.h>

#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/opcodes.h>

#घोषणा PLT_ENT_STRIDE		L1_CACHE_BYTES
#घोषणा PLT_ENT_COUNT		(PLT_ENT_STRIDE / माप(u32))
#घोषणा PLT_ENT_SIZE		(माप(काष्ठा plt_entries) / PLT_ENT_COUNT)

#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा PLT_ENT_LDR		__opcode_to_mem_thumb32(0xf8dff000 | \
							(PLT_ENT_STRIDE - 4))
#अन्यथा
#घोषणा PLT_ENT_LDR		__opcode_to_mem_arm(0xe59ff000 | \
						    (PLT_ENT_STRIDE - 8))
#पूर्ण_अगर

काष्ठा plt_entries अणु
	u32	ldr[PLT_ENT_COUNT];
	u32	lit[PLT_ENT_COUNT];
पूर्ण;

अटल bool in_init(स्थिर काष्ठा module *mod, अचिन्हित दीर्घ loc)
अणु
	वापस loc - (u32)mod->init_layout.base < mod->init_layout.size;
पूर्ण

u32 get_module_plt(काष्ठा module *mod, अचिन्हित दीर्घ loc, Elf32_Addr val)
अणु
	काष्ठा mod_plt_sec *pltsec = !in_init(mod, loc) ? &mod->arch.core :
							  &mod->arch.init;

	काष्ठा plt_entries *plt = (काष्ठा plt_entries *)pltsec->plt->sh_addr;
	पूर्णांक idx = 0;

	/*
	 * Look क्रम an existing entry poपूर्णांकing to 'val'. Given that the
	 * relocations are sorted, this will be the last entry we allocated.
	 * (अगर one exists).
	 */
	अगर (pltsec->plt_count > 0) अणु
		plt += (pltsec->plt_count - 1) / PLT_ENT_COUNT;
		idx = (pltsec->plt_count - 1) % PLT_ENT_COUNT;

		अगर (plt->lit[idx] == val)
			वापस (u32)&plt->ldr[idx];

		idx = (idx + 1) % PLT_ENT_COUNT;
		अगर (!idx)
			plt++;
	पूर्ण

	pltsec->plt_count++;
	BUG_ON(pltsec->plt_count * PLT_ENT_SIZE > pltsec->plt->sh_size);

	अगर (!idx)
		/* Populate a new set of entries */
		*plt = (काष्ठा plt_entries)अणु
			अणु [0 ... PLT_ENT_COUNT - 1] = PLT_ENT_LDR, पूर्ण,
			अणु val, पूर्ण
		पूर्ण;
	अन्यथा
		plt->lit[idx] = val;

	वापस (u32)&plt->ldr[idx];
पूर्ण

#घोषणा cmp_3way(a,b)	((a) < (b) ? -1 : (a) > (b))

अटल पूर्णांक cmp_rel(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर Elf32_Rel *x = a, *y = b;
	पूर्णांक i;

	/* sort by type and symbol index */
	i = cmp_3way(ELF32_R_TYPE(x->r_info), ELF32_R_TYPE(y->r_info));
	अगर (i == 0)
		i = cmp_3way(ELF32_R_SYM(x->r_info), ELF32_R_SYM(y->r_info));
	वापस i;
पूर्ण

अटल bool is_zero_addend_relocation(Elf32_Addr base, स्थिर Elf32_Rel *rel)
अणु
	u32 *tval = (u32 *)(base + rel->r_offset);

	/*
	 * Do a bitwise compare on the raw addend rather than fully decoding
	 * the offset and करोing an arithmetic comparison.
	 * Note that a zero-addend jump/call relocation is encoded taking the
	 * PC bias पूर्णांकo account, i.e., -8 क्रम ARM and -4 क्रम Thumb2.
	 */
	चयन (ELF32_R_TYPE(rel->r_info)) अणु
		u16 upper, lower;

	हाल R_ARM_THM_CALL:
	हाल R_ARM_THM_JUMP24:
		upper = __mem_to_opcode_thumb16(((u16 *)tval)[0]);
		lower = __mem_to_opcode_thumb16(((u16 *)tval)[1]);

		वापस (upper & 0x7ff) == 0x7ff && (lower & 0x2fff) == 0x2ffe;

	हाल R_ARM_CALL:
	हाल R_ARM_PC24:
	हाल R_ARM_JUMP24:
		वापस (__mem_to_opcode_arm(*tval) & 0xffffff) == 0xfffffe;
	पूर्ण
	BUG();
पूर्ण

अटल bool duplicate_rel(Elf32_Addr base, स्थिर Elf32_Rel *rel, पूर्णांक num)
अणु
	स्थिर Elf32_Rel *prev;

	/*
	 * Entries are sorted by type and symbol index. That means that,
	 * अगर a duplicate entry exists, it must be in the preceding
	 * slot.
	 */
	अगर (!num)
		वापस false;

	prev = rel + num - 1;
	वापस cmp_rel(rel + num, prev) == 0 &&
	       is_zero_addend_relocation(base, prev);
पूर्ण

/* Count how many PLT entries we may need */
अटल अचिन्हित पूर्णांक count_plts(स्थिर Elf32_Sym *syms, Elf32_Addr base,
			       स्थिर Elf32_Rel *rel, पूर्णांक num, Elf32_Word dstidx)
अणु
	अचिन्हित पूर्णांक ret = 0;
	स्थिर Elf32_Sym *s;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		चयन (ELF32_R_TYPE(rel[i].r_info)) अणु
		हाल R_ARM_CALL:
		हाल R_ARM_PC24:
		हाल R_ARM_JUMP24:
		हाल R_ARM_THM_CALL:
		हाल R_ARM_THM_JUMP24:
			/*
			 * We only have to consider branch tarमाला_लो that resolve
			 * to symbols that are defined in a dअगरferent section.
			 * This is not simply a heuristic, it is a fundamental
			 * limitation, since there is no guaranteed way to emit
			 * PLT entries sufficiently बंद to the branch अगर the
			 * section size exceeds the range of a branch
			 * inकाष्ठाion. So ignore relocations against defined
			 * symbols अगर they live in the same section as the
			 * relocation target.
			 */
			s = syms + ELF32_R_SYM(rel[i].r_info);
			अगर (s->st_shndx == dstidx)
				अवरोध;

			/*
			 * Jump relocations with non-zero addends against
			 * undefined symbols are supported by the ELF spec, but
			 * करो not occur in practice (e.g., 'jump n bytes past
			 * the entry poपूर्णांक of undefined function symbol f').
			 * So we need to support them, but there is no need to
			 * take them पूर्णांकo consideration when trying to optimize
			 * this code. So let's only check क्रम duplicates when
			 * the addend is zero. (Note that calls पूर्णांकo the core
			 * module via init PLT entries could involve section
			 * relative symbol references with non-zero addends, क्रम
			 * which we may end up emitting duplicates, but the init
			 * PLT is released aदीर्घ with the rest of the .init
			 * region as soon as module loading completes.)
			 */
			अगर (!is_zero_addend_relocation(base, rel + i) ||
			    !duplicate_rel(base, rel, i))
				ret++;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक module_frob_arch_sections(Elf_Ehdr *ehdr, Elf_Shdr *sechdrs,
			      अक्षर *secstrings, काष्ठा module *mod)
अणु
	अचिन्हित दीर्घ core_plts = 0;
	अचिन्हित दीर्घ init_plts = 0;
	Elf32_Shdr *s, *sechdrs_end = sechdrs + ehdr->e_shnum;
	Elf32_Sym *syms = शून्य;

	/*
	 * To store the PLTs, we expand the .text section क्रम core module code
	 * and क्रम initialization code.
	 */
	क्रम (s = sechdrs; s < sechdrs_end; ++s) अणु
		अगर (म_भेद(".plt", secstrings + s->sh_name) == 0)
			mod->arch.core.plt = s;
		अन्यथा अगर (म_भेद(".init.plt", secstrings + s->sh_name) == 0)
			mod->arch.init.plt = s;
		अन्यथा अगर (s->sh_type == SHT_SYMTAB)
			syms = (Elf32_Sym *)s->sh_addr;
	पूर्ण

	अगर (!mod->arch.core.plt || !mod->arch.init.plt) अणु
		pr_err("%s: module PLT section(s) missing\n", mod->name);
		वापस -ENOEXEC;
	पूर्ण
	अगर (!syms) अणु
		pr_err("%s: module symtab section missing\n", mod->name);
		वापस -ENOEXEC;
	पूर्ण

	क्रम (s = sechdrs + 1; s < sechdrs_end; ++s) अणु
		Elf32_Rel *rels = (व्योम *)ehdr + s->sh_offset;
		पूर्णांक numrels = s->sh_size / माप(Elf32_Rel);
		Elf32_Shdr *dstsec = sechdrs + s->sh_info;

		अगर (s->sh_type != SHT_REL)
			जारी;

		/* ignore relocations that operate on non-exec sections */
		अगर (!(dstsec->sh_flags & SHF_EXECINSTR))
			जारी;

		/* sort by type and symbol index */
		sort(rels, numrels, माप(Elf32_Rel), cmp_rel, शून्य);

		अगर (म_भेदन(secstrings + dstsec->sh_name, ".init", 5) != 0)
			core_plts += count_plts(syms, dstsec->sh_addr, rels,
						numrels, s->sh_info);
		अन्यथा
			init_plts += count_plts(syms, dstsec->sh_addr, rels,
						numrels, s->sh_info);
	पूर्ण

	mod->arch.core.plt->sh_type = SHT_NOBITS;
	mod->arch.core.plt->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	mod->arch.core.plt->sh_addralign = L1_CACHE_BYTES;
	mod->arch.core.plt->sh_size = round_up(core_plts * PLT_ENT_SIZE,
					       माप(काष्ठा plt_entries));
	mod->arch.core.plt_count = 0;

	mod->arch.init.plt->sh_type = SHT_NOBITS;
	mod->arch.init.plt->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	mod->arch.init.plt->sh_addralign = L1_CACHE_BYTES;
	mod->arch.init.plt->sh_size = round_up(init_plts * PLT_ENT_SIZE,
					       माप(काष्ठा plt_entries));
	mod->arch.init.plt_count = 0;

	pr_debug("%s: plt=%x, init.plt=%x\n", __func__,
		 mod->arch.core.plt->sh_size, mod->arch.init.plt->sh_size);
	वापस 0;
पूर्ण
