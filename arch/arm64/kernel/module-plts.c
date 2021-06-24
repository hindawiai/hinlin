<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2017 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/elf.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sort.h>

अटल काष्ठा plt_entry __get_adrp_add_pair(u64 dst, u64 pc,
					    क्रमागत aarch64_insn_रेजिस्टर reg)
अणु
	u32 adrp, add;

	adrp = aarch64_insn_gen_adr(pc, dst, reg, AARCH64_INSN_ADR_TYPE_ADRP);
	add = aarch64_insn_gen_add_sub_imm(reg, reg, dst % SZ_4K,
					   AARCH64_INSN_VARIANT_64BIT,
					   AARCH64_INSN_ADSB_ADD);

	वापस (काष्ठा plt_entry)अणु cpu_to_le32(adrp), cpu_to_le32(add) पूर्ण;
पूर्ण

काष्ठा plt_entry get_plt_entry(u64 dst, व्योम *pc)
अणु
	काष्ठा plt_entry plt;
	अटल u32 br;

	अगर (!br)
		br = aarch64_insn_gen_branch_reg(AARCH64_INSN_REG_16,
						 AARCH64_INSN_BRANCH_NOLINK);

	plt = __get_adrp_add_pair(dst, (u64)pc, AARCH64_INSN_REG_16);
	plt.br = cpu_to_le32(br);

	वापस plt;
पूर्ण

bool plt_entries_equal(स्थिर काष्ठा plt_entry *a, स्थिर काष्ठा plt_entry *b)
अणु
	u64 p, q;

	/*
	 * Check whether both entries refer to the same target:
	 * करो the cheapest checks first.
	 * If the 'add' or 'br' opcodes are dअगरferent, then the target
	 * cannot be the same.
	 */
	अगर (a->add != b->add || a->br != b->br)
		वापस false;

	p = ALIGN_DOWN((u64)a, SZ_4K);
	q = ALIGN_DOWN((u64)b, SZ_4K);

	/*
	 * If the 'adrp' opcodes are the same then we just need to check
	 * that they refer to the same 4k region.
	 */
	अगर (a->adrp == b->adrp && p == q)
		वापस true;

	वापस (p + aarch64_insn_adrp_get_offset(le32_to_cpu(a->adrp))) ==
	       (q + aarch64_insn_adrp_get_offset(le32_to_cpu(b->adrp)));
पूर्ण

अटल bool in_init(स्थिर काष्ठा module *mod, व्योम *loc)
अणु
	वापस (u64)loc - (u64)mod->init_layout.base < mod->init_layout.size;
पूर्ण

u64 module_emit_plt_entry(काष्ठा module *mod, Elf64_Shdr *sechdrs,
			  व्योम *loc, स्थिर Elf64_Rela *rela,
			  Elf64_Sym *sym)
अणु
	काष्ठा mod_plt_sec *pltsec = !in_init(mod, loc) ? &mod->arch.core :
							  &mod->arch.init;
	काष्ठा plt_entry *plt = (काष्ठा plt_entry *)sechdrs[pltsec->plt_shndx].sh_addr;
	पूर्णांक i = pltsec->plt_num_entries;
	पूर्णांक j = i - 1;
	u64 val = sym->st_value + rela->r_addend;

	अगर (is_क्रमbidden_offset_क्रम_adrp(&plt[i].adrp))
		i++;

	plt[i] = get_plt_entry(val, &plt[i]);

	/*
	 * Check अगर the entry we just created is a duplicate. Given that the
	 * relocations are sorted, this will be the last entry we allocated.
	 * (अगर one exists).
	 */
	अगर (j >= 0 && plt_entries_equal(plt + i, plt + j))
		वापस (u64)&plt[j];

	pltsec->plt_num_entries += i - j;
	अगर (WARN_ON(pltsec->plt_num_entries > pltsec->plt_max_entries))
		वापस 0;

	वापस (u64)&plt[i];
पूर्ण

#अगर_घोषित CONFIG_ARM64_ERRATUM_843419
u64 module_emit_veneer_क्रम_adrp(काष्ठा module *mod, Elf64_Shdr *sechdrs,
				व्योम *loc, u64 val)
अणु
	काष्ठा mod_plt_sec *pltsec = !in_init(mod, loc) ? &mod->arch.core :
							  &mod->arch.init;
	काष्ठा plt_entry *plt = (काष्ठा plt_entry *)sechdrs[pltsec->plt_shndx].sh_addr;
	पूर्णांक i = pltsec->plt_num_entries++;
	u32 br;
	पूर्णांक rd;

	अगर (WARN_ON(pltsec->plt_num_entries > pltsec->plt_max_entries))
		वापस 0;

	अगर (is_क्रमbidden_offset_क्रम_adrp(&plt[i].adrp))
		i = pltsec->plt_num_entries++;

	/* get the destination रेजिस्टर of the ADRP inकाष्ठाion */
	rd = aarch64_insn_decode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD,
					  le32_to_cpup((__le32 *)loc));

	br = aarch64_insn_gen_branch_imm((u64)&plt[i].br, (u64)loc + 4,
					 AARCH64_INSN_BRANCH_NOLINK);

	plt[i] = __get_adrp_add_pair(val, (u64)&plt[i], rd);
	plt[i].br = cpu_to_le32(br);

	वापस (u64)&plt[i];
पूर्ण
#पूर्ण_अगर

#घोषणा cmp_3way(a, b)	((a) < (b) ? -1 : (a) > (b))

अटल पूर्णांक cmp_rela(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर Elf64_Rela *x = a, *y = b;
	पूर्णांक i;

	/* sort by type, symbol index and addend */
	i = cmp_3way(ELF64_R_TYPE(x->r_info), ELF64_R_TYPE(y->r_info));
	अगर (i == 0)
		i = cmp_3way(ELF64_R_SYM(x->r_info), ELF64_R_SYM(y->r_info));
	अगर (i == 0)
		i = cmp_3way(x->r_addend, y->r_addend);
	वापस i;
पूर्ण

अटल bool duplicate_rel(स्थिर Elf64_Rela *rela, पूर्णांक num)
अणु
	/*
	 * Entries are sorted by type, symbol index and addend. That means
	 * that, अगर a duplicate entry exists, it must be in the preceding
	 * slot.
	 */
	वापस num > 0 && cmp_rela(rela + num, rela + num - 1) == 0;
पूर्ण

अटल अचिन्हित पूर्णांक count_plts(Elf64_Sym *syms, Elf64_Rela *rela, पूर्णांक num,
			       Elf64_Word dstidx, Elf_Shdr *dstsec)
अणु
	अचिन्हित पूर्णांक ret = 0;
	Elf64_Sym *s;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		u64 min_align;

		चयन (ELF64_R_TYPE(rela[i].r_info)) अणु
		हाल R_AARCH64_JUMP26:
		हाल R_AARCH64_CALL26:
			अगर (!IS_ENABLED(CONFIG_RANDOMIZE_BASE))
				अवरोध;

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
			s = syms + ELF64_R_SYM(rela[i].r_info);
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
			 * the addend is zero: this allows us to record the PLT
			 * entry address in the symbol table itself, rather than
			 * having to search the list क्रम duplicates each समय we
			 * emit one.
			 */
			अगर (rela[i].r_addend != 0 || !duplicate_rel(rela, i))
				ret++;
			अवरोध;
		हाल R_AARCH64_ADR_PREL_PG_HI21_NC:
		हाल R_AARCH64_ADR_PREL_PG_HI21:
			अगर (!IS_ENABLED(CONFIG_ARM64_ERRATUM_843419) ||
			    !cpus_have_स्थिर_cap(ARM64_WORKAROUND_843419))
				अवरोध;

			/*
			 * Determine the minimal safe alignment क्रम this ADRP
			 * inकाष्ठाion: the section alignment at which it is
			 * guaranteed not to appear at a vulnerable offset.
			 *
			 * This comes करोwn to finding the least signअगरicant zero
			 * bit in bits [11:3] of the section offset, and
			 * increasing the section's alignment so that the
			 * resulting address of this inकाष्ठाion is guaranteed
			 * to equal the offset in that particular bit (as well
			 * as all less signficant bits). This ensures that the
			 * address modulo 4 KB != 0xfff8 or 0xfffc (which would
			 * have all ones in bits [11:3])
			 */
			min_align = 2ULL << ffz(rela[i].r_offset | 0x7);

			/*
			 * Allocate veneer space क्रम each ADRP that may appear
			 * at a vulnerable offset nonetheless. At relocation
			 * समय, some of these will reमुख्य unused since some
			 * ADRP inकाष्ठाions can be patched to ADR inकाष्ठाions
			 * instead.
			 */
			अगर (min_align > SZ_4K)
				ret++;
			अन्यथा
				dstsec->sh_addralign = max(dstsec->sh_addralign,
							   min_align);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (IS_ENABLED(CONFIG_ARM64_ERRATUM_843419) &&
	    cpus_have_स्थिर_cap(ARM64_WORKAROUND_843419))
		/*
		 * Add some slack so we can skip PLT slots that may trigger
		 * the erratum due to the placement of the ADRP inकाष्ठाion.
		 */
		ret += DIV_ROUND_UP(ret, (SZ_4K / माप(काष्ठा plt_entry)));

	वापस ret;
पूर्ण

अटल bool branch_rela_needs_plt(Elf64_Sym *syms, Elf64_Rela *rela,
				  Elf64_Word dstidx)
अणु

	Elf64_Sym *s = syms + ELF64_R_SYM(rela->r_info);

	अगर (s->st_shndx == dstidx)
		वापस false;

	वापस ELF64_R_TYPE(rela->r_info) == R_AARCH64_JUMP26 ||
	       ELF64_R_TYPE(rela->r_info) == R_AARCH64_CALL26;
पूर्ण

/* Group branch PLT relas at the front end of the array. */
अटल पूर्णांक partition_branch_plt_relas(Elf64_Sym *syms, Elf64_Rela *rela,
				      पूर्णांक numrels, Elf64_Word dstidx)
अणु
	पूर्णांक i = 0, j = numrels - 1;

	अगर (!IS_ENABLED(CONFIG_RANDOMIZE_BASE))
		वापस 0;

	जबतक (i < j) अणु
		अगर (branch_rela_needs_plt(syms, &rela[i], dstidx))
			i++;
		अन्यथा अगर (branch_rela_needs_plt(syms, &rela[j], dstidx))
			swap(rela[i], rela[j]);
		अन्यथा
			j--;
	पूर्ण

	वापस i;
पूर्ण

पूर्णांक module_frob_arch_sections(Elf_Ehdr *ehdr, Elf_Shdr *sechdrs,
			      अक्षर *secstrings, काष्ठा module *mod)
अणु
	अचिन्हित दीर्घ core_plts = 0;
	अचिन्हित दीर्घ init_plts = 0;
	Elf64_Sym *syms = शून्य;
	Elf_Shdr *pltsec, *tramp = शून्य;
	पूर्णांक i;

	/*
	 * Find the empty .plt section so we can expand it to store the PLT
	 * entries. Record the symtab address as well.
	 */
	क्रम (i = 0; i < ehdr->e_shnum; i++) अणु
		अगर (!म_भेद(secstrings + sechdrs[i].sh_name, ".plt"))
			mod->arch.core.plt_shndx = i;
		अन्यथा अगर (!म_भेद(secstrings + sechdrs[i].sh_name, ".init.plt"))
			mod->arch.init.plt_shndx = i;
		अन्यथा अगर (!म_भेद(secstrings + sechdrs[i].sh_name,
				 ".text.ftrace_trampoline"))
			tramp = sechdrs + i;
		अन्यथा अगर (sechdrs[i].sh_type == SHT_SYMTAB)
			syms = (Elf64_Sym *)sechdrs[i].sh_addr;
	पूर्ण

	अगर (!mod->arch.core.plt_shndx || !mod->arch.init.plt_shndx) अणु
		pr_err("%s: module PLT section(s) missing\n", mod->name);
		वापस -ENOEXEC;
	पूर्ण
	अगर (!syms) अणु
		pr_err("%s: module symtab section missing\n", mod->name);
		वापस -ENOEXEC;
	पूर्ण

	क्रम (i = 0; i < ehdr->e_shnum; i++) अणु
		Elf64_Rela *rels = (व्योम *)ehdr + sechdrs[i].sh_offset;
		पूर्णांक nents, numrels = sechdrs[i].sh_size / माप(Elf64_Rela);
		Elf64_Shdr *dstsec = sechdrs + sechdrs[i].sh_info;

		अगर (sechdrs[i].sh_type != SHT_RELA)
			जारी;

		/* ignore relocations that operate on non-exec sections */
		अगर (!(dstsec->sh_flags & SHF_EXECINSTR))
			जारी;

		/*
		 * sort branch relocations requiring a PLT by type, symbol index
		 * and addend
		 */
		nents = partition_branch_plt_relas(syms, rels, numrels,
						   sechdrs[i].sh_info);
		अगर (nents)
			sort(rels, nents, माप(Elf64_Rela), cmp_rela, शून्य);

		अगर (!str_has_prefix(secstrings + dstsec->sh_name, ".init"))
			core_plts += count_plts(syms, rels, numrels,
						sechdrs[i].sh_info, dstsec);
		अन्यथा
			init_plts += count_plts(syms, rels, numrels,
						sechdrs[i].sh_info, dstsec);
	पूर्ण

	pltsec = sechdrs + mod->arch.core.plt_shndx;
	pltsec->sh_type = SHT_NOBITS;
	pltsec->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	pltsec->sh_addralign = L1_CACHE_BYTES;
	pltsec->sh_size = (core_plts  + 1) * माप(काष्ठा plt_entry);
	mod->arch.core.plt_num_entries = 0;
	mod->arch.core.plt_max_entries = core_plts;

	pltsec = sechdrs + mod->arch.init.plt_shndx;
	pltsec->sh_type = SHT_NOBITS;
	pltsec->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	pltsec->sh_addralign = L1_CACHE_BYTES;
	pltsec->sh_size = (init_plts + 1) * माप(काष्ठा plt_entry);
	mod->arch.init.plt_num_entries = 0;
	mod->arch.init.plt_max_entries = init_plts;

	अगर (tramp) अणु
		tramp->sh_type = SHT_NOBITS;
		tramp->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
		tramp->sh_addralign = __alignof__(काष्ठा plt_entry);
		tramp->sh_size = NR_FTRACE_PLTS * माप(काष्ठा plt_entry);
	पूर्ण

	वापस 0;
पूर्ण
