<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (C) 2014-2017 Linaro Ltd. <ard.biesheuvel@linaro.org>
 *
 * Copyright (C) 2018 Andes Technology Corporation <zong@andestech.com>
 */

#समावेश <linux/elf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleloader.h>

अचिन्हित दीर्घ module_emit_got_entry(काष्ठा module *mod, अचिन्हित दीर्घ val)
अणु
	काष्ठा mod_section *got_sec = &mod->arch.got;
	पूर्णांक i = got_sec->num_entries;
	काष्ठा got_entry *got = get_got_entry(val, got_sec);

	अगर (got)
		वापस (अचिन्हित दीर्घ)got;

	/* There is no duplicate entry, create a new one */
	got = (काष्ठा got_entry *)got_sec->shdr->sh_addr;
	got[i] = emit_got_entry(val);

	got_sec->num_entries++;
	BUG_ON(got_sec->num_entries > got_sec->max_entries);

	वापस (अचिन्हित दीर्घ)&got[i];
पूर्ण

अचिन्हित दीर्घ module_emit_plt_entry(काष्ठा module *mod, अचिन्हित दीर्घ val)
अणु
	काष्ठा mod_section *got_plt_sec = &mod->arch.got_plt;
	काष्ठा got_entry *got_plt;
	काष्ठा mod_section *plt_sec = &mod->arch.plt;
	काष्ठा plt_entry *plt = get_plt_entry(val, plt_sec, got_plt_sec);
	पूर्णांक i = plt_sec->num_entries;

	अगर (plt)
		वापस (अचिन्हित दीर्घ)plt;

	/* There is no duplicate entry, create a new one */
	got_plt = (काष्ठा got_entry *)got_plt_sec->shdr->sh_addr;
	got_plt[i] = emit_got_entry(val);
	plt = (काष्ठा plt_entry *)plt_sec->shdr->sh_addr;
	plt[i] = emit_plt_entry(val,
				(अचिन्हित दीर्घ)&plt[i],
				(अचिन्हित दीर्घ)&got_plt[i]);

	plt_sec->num_entries++;
	got_plt_sec->num_entries++;
	BUG_ON(plt_sec->num_entries > plt_sec->max_entries);

	वापस (अचिन्हित दीर्घ)&plt[i];
पूर्ण

अटल पूर्णांक is_rela_equal(स्थिर Elf_Rela *x, स्थिर Elf_Rela *y)
अणु
	वापस x->r_info == y->r_info && x->r_addend == y->r_addend;
पूर्ण

अटल bool duplicate_rela(स्थिर Elf_Rela *rela, पूर्णांक idx)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < idx; i++) अणु
		अगर (is_rela_equal(&rela[i], &rela[idx]))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम count_max_entries(Elf_Rela *relas, पूर्णांक num,
			      अचिन्हित पूर्णांक *plts, अचिन्हित पूर्णांक *gots)
अणु
	अचिन्हित पूर्णांक type, i;

	क्रम (i = 0; i < num; i++) अणु
		type = ELF_RISCV_R_TYPE(relas[i].r_info);
		अगर (type == R_RISCV_CALL_PLT) अणु
			अगर (!duplicate_rela(relas, i))
				(*plts)++;
		पूर्ण अन्यथा अगर (type == R_RISCV_GOT_HI20) अणु
			अगर (!duplicate_rela(relas, i))
				(*gots)++;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक module_frob_arch_sections(Elf_Ehdr *ehdr, Elf_Shdr *sechdrs,
			      अक्षर *secstrings, काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक num_plts = 0;
	अचिन्हित पूर्णांक num_gots = 0;
	पूर्णांक i;

	/*
	 * Find the empty .got and .plt sections.
	 */
	क्रम (i = 0; i < ehdr->e_shnum; i++) अणु
		अगर (!म_भेद(secstrings + sechdrs[i].sh_name, ".plt"))
			mod->arch.plt.shdr = sechdrs + i;
		अन्यथा अगर (!म_भेद(secstrings + sechdrs[i].sh_name, ".got"))
			mod->arch.got.shdr = sechdrs + i;
		अन्यथा अगर (!म_भेद(secstrings + sechdrs[i].sh_name, ".got.plt"))
			mod->arch.got_plt.shdr = sechdrs + i;
	पूर्ण

	अगर (!mod->arch.plt.shdr) अणु
		pr_err("%s: module PLT section(s) missing\n", mod->name);
		वापस -ENOEXEC;
	पूर्ण
	अगर (!mod->arch.got.shdr) अणु
		pr_err("%s: module GOT section(s) missing\n", mod->name);
		वापस -ENOEXEC;
	पूर्ण
	अगर (!mod->arch.got_plt.shdr) अणु
		pr_err("%s: module GOT.PLT section(s) missing\n", mod->name);
		वापस -ENOEXEC;
	पूर्ण

	/* Calculate the maxinum number of entries */
	क्रम (i = 0; i < ehdr->e_shnum; i++) अणु
		Elf_Rela *relas = (व्योम *)ehdr + sechdrs[i].sh_offset;
		पूर्णांक num_rela = sechdrs[i].sh_size / माप(Elf_Rela);
		Elf_Shdr *dst_sec = sechdrs + sechdrs[i].sh_info;

		अगर (sechdrs[i].sh_type != SHT_RELA)
			जारी;

		/* ignore relocations that operate on non-exec sections */
		अगर (!(dst_sec->sh_flags & SHF_EXECINSTR))
			जारी;

		count_max_entries(relas, num_rela, &num_plts, &num_gots);
	पूर्ण

	mod->arch.plt.shdr->sh_type = SHT_NOBITS;
	mod->arch.plt.shdr->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	mod->arch.plt.shdr->sh_addralign = L1_CACHE_BYTES;
	mod->arch.plt.shdr->sh_size = (num_plts + 1) * माप(काष्ठा plt_entry);
	mod->arch.plt.num_entries = 0;
	mod->arch.plt.max_entries = num_plts;

	mod->arch.got.shdr->sh_type = SHT_NOBITS;
	mod->arch.got.shdr->sh_flags = SHF_ALLOC;
	mod->arch.got.shdr->sh_addralign = L1_CACHE_BYTES;
	mod->arch.got.shdr->sh_size = (num_gots + 1) * माप(काष्ठा got_entry);
	mod->arch.got.num_entries = 0;
	mod->arch.got.max_entries = num_gots;

	mod->arch.got_plt.shdr->sh_type = SHT_NOBITS;
	mod->arch.got_plt.shdr->sh_flags = SHF_ALLOC;
	mod->arch.got_plt.shdr->sh_addralign = L1_CACHE_BYTES;
	mod->arch.got_plt.shdr->sh_size = (num_plts + 1) * माप(काष्ठा got_entry);
	mod->arch.got_plt.num_entries = 0;
	mod->arch.got_plt.max_entries = num_plts;
	वापस 0;
पूर्ण
