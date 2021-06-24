<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Copyright (C) 2017 Zihao Yu
 */

#समावेश <linux/elf.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/moduleloader.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sizes.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/sections.h>

अटल पूर्णांक apply_r_riscv_32_rela(काष्ठा module *me, u32 *location, Elf_Addr v)
अणु
	अगर (v != (u32)v) अणु
		pr_err("%s: value %016llx out of range for 32-bit field\n",
		       me->name, (दीर्घ दीर्घ)v);
		वापस -EINVAL;
	पूर्ण
	*location = v;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_64_rela(काष्ठा module *me, u32 *location, Elf_Addr v)
अणु
	*(u64 *)location = v;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_branch_rela(काष्ठा module *me, u32 *location,
				     Elf_Addr v)
अणु
	सूचक_भेद_प्रकार offset = (व्योम *)v - (व्योम *)location;
	u32 imm12 = (offset & 0x1000) << (31 - 12);
	u32 imm11 = (offset & 0x800) >> (11 - 7);
	u32 imm10_5 = (offset & 0x7e0) << (30 - 10);
	u32 imm4_1 = (offset & 0x1e) << (11 - 4);

	*location = (*location & 0x1fff07f) | imm12 | imm11 | imm10_5 | imm4_1;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_jal_rela(काष्ठा module *me, u32 *location,
				  Elf_Addr v)
अणु
	सूचक_भेद_प्रकार offset = (व्योम *)v - (व्योम *)location;
	u32 imm20 = (offset & 0x100000) << (31 - 20);
	u32 imm19_12 = (offset & 0xff000);
	u32 imm11 = (offset & 0x800) << (20 - 11);
	u32 imm10_1 = (offset & 0x7fe) << (30 - 10);

	*location = (*location & 0xfff) | imm20 | imm19_12 | imm11 | imm10_1;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_rcv_branch_rela(काष्ठा module *me, u32 *location,
					 Elf_Addr v)
अणु
	सूचक_भेद_प्रकार offset = (व्योम *)v - (व्योम *)location;
	u16 imm8 = (offset & 0x100) << (12 - 8);
	u16 imm7_6 = (offset & 0xc0) >> (6 - 5);
	u16 imm5 = (offset & 0x20) >> (5 - 2);
	u16 imm4_3 = (offset & 0x18) << (12 - 5);
	u16 imm2_1 = (offset & 0x6) << (12 - 10);

	*(u16 *)location = (*(u16 *)location & 0xe383) |
		    imm8 | imm7_6 | imm5 | imm4_3 | imm2_1;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_rvc_jump_rela(काष्ठा module *me, u32 *location,
				       Elf_Addr v)
अणु
	सूचक_भेद_प्रकार offset = (व्योम *)v - (व्योम *)location;
	u16 imm11 = (offset & 0x800) << (12 - 11);
	u16 imm10 = (offset & 0x400) >> (10 - 8);
	u16 imm9_8 = (offset & 0x300) << (12 - 11);
	u16 imm7 = (offset & 0x80) >> (7 - 6);
	u16 imm6 = (offset & 0x40) << (12 - 11);
	u16 imm5 = (offset & 0x20) >> (5 - 2);
	u16 imm4 = (offset & 0x10) << (12 - 5);
	u16 imm3_1 = (offset & 0xe) << (12 - 10);

	*(u16 *)location = (*(u16 *)location & 0xe003) |
		    imm11 | imm10 | imm9_8 | imm7 | imm6 | imm5 | imm4 | imm3_1;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_pcrel_hi20_rela(काष्ठा module *me, u32 *location,
					 Elf_Addr v)
अणु
	सूचक_भेद_प्रकार offset = (व्योम *)v - (व्योम *)location;
	s32 hi20;

	अगर (offset != (s32)offset) अणु
		pr_err(
		  "%s: target %016llx can not be addressed by the 32-bit offset from PC = %p\n",
		  me->name, (दीर्घ दीर्घ)v, location);
		वापस -EINVAL;
	पूर्ण

	hi20 = (offset + 0x800) & 0xfffff000;
	*location = (*location & 0xfff) | hi20;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_pcrel_lo12_i_rela(काष्ठा module *me, u32 *location,
					   Elf_Addr v)
अणु
	/*
	 * v is the lo12 value to fill. It is calculated beक्रमe calling this
	 * handler.
	 */
	*location = (*location & 0xfffff) | ((v & 0xfff) << 20);
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_pcrel_lo12_s_rela(काष्ठा module *me, u32 *location,
					   Elf_Addr v)
अणु
	/*
	 * v is the lo12 value to fill. It is calculated beक्रमe calling this
	 * handler.
	 */
	u32 imm11_5 = (v & 0xfe0) << (31 - 11);
	u32 imm4_0 = (v & 0x1f) << (11 - 4);

	*location = (*location & 0x1fff07f) | imm11_5 | imm4_0;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_hi20_rela(काष्ठा module *me, u32 *location,
				   Elf_Addr v)
अणु
	s32 hi20;

	अगर (IS_ENABLED(CONFIG_CMODEL_MEDLOW)) अणु
		pr_err(
		  "%s: target %016llx can not be addressed by the 32-bit offset from PC = %p\n",
		  me->name, (दीर्घ दीर्घ)v, location);
		वापस -EINVAL;
	पूर्ण

	hi20 = ((s32)v + 0x800) & 0xfffff000;
	*location = (*location & 0xfff) | hi20;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_lo12_i_rela(काष्ठा module *me, u32 *location,
				     Elf_Addr v)
अणु
	/* Skip medlow checking because of filtering by HI20 alपढ़ोy */
	s32 hi20 = ((s32)v + 0x800) & 0xfffff000;
	s32 lo12 = ((s32)v - hi20);
	*location = (*location & 0xfffff) | ((lo12 & 0xfff) << 20);
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_lo12_s_rela(काष्ठा module *me, u32 *location,
				     Elf_Addr v)
अणु
	/* Skip medlow checking because of filtering by HI20 alपढ़ोy */
	s32 hi20 = ((s32)v + 0x800) & 0xfffff000;
	s32 lo12 = ((s32)v - hi20);
	u32 imm11_5 = (lo12 & 0xfe0) << (31 - 11);
	u32 imm4_0 = (lo12 & 0x1f) << (11 - 4);
	*location = (*location & 0x1fff07f) | imm11_5 | imm4_0;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_got_hi20_rela(काष्ठा module *me, u32 *location,
				       Elf_Addr v)
अणु
	सूचक_भेद_प्रकार offset = (व्योम *)v - (व्योम *)location;
	s32 hi20;

	/* Always emit the got entry */
	अगर (IS_ENABLED(CONFIG_MODULE_SECTIONS)) अणु
		offset = module_emit_got_entry(me, v);
		offset = (व्योम *)offset - (व्योम *)location;
	पूर्ण अन्यथा अणु
		pr_err(
		  "%s: can not generate the GOT entry for symbol = %016llx from PC = %p\n",
		  me->name, (दीर्घ दीर्घ)v, location);
		वापस -EINVAL;
	पूर्ण

	hi20 = (offset + 0x800) & 0xfffff000;
	*location = (*location & 0xfff) | hi20;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_call_plt_rela(काष्ठा module *me, u32 *location,
				       Elf_Addr v)
अणु
	सूचक_भेद_प्रकार offset = (व्योम *)v - (व्योम *)location;
	s32 fill_v = offset;
	u32 hi20, lo12;

	अगर (offset != fill_v) अणु
		/* Only emit the plt entry अगर offset over 32-bit range */
		अगर (IS_ENABLED(CONFIG_MODULE_SECTIONS)) अणु
			offset = module_emit_plt_entry(me, v);
			offset = (व्योम *)offset - (व्योम *)location;
		पूर्ण अन्यथा अणु
			pr_err(
			  "%s: target %016llx can not be addressed by the 32-bit offset from PC = %p\n",
			  me->name, (दीर्घ दीर्घ)v, location);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	hi20 = (offset + 0x800) & 0xfffff000;
	lo12 = (offset - hi20) & 0xfff;
	*location = (*location & 0xfff) | hi20;
	*(location + 1) = (*(location + 1) & 0xfffff) | (lo12 << 20);
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_call_rela(काष्ठा module *me, u32 *location,
				   Elf_Addr v)
अणु
	सूचक_भेद_प्रकार offset = (व्योम *)v - (व्योम *)location;
	s32 fill_v = offset;
	u32 hi20, lo12;

	अगर (offset != fill_v) अणु
		pr_err(
		  "%s: target %016llx can not be addressed by the 32-bit offset from PC = %p\n",
		  me->name, (दीर्घ दीर्घ)v, location);
		वापस -EINVAL;
	पूर्ण

	hi20 = (offset + 0x800) & 0xfffff000;
	lo12 = (offset - hi20) & 0xfff;
	*location = (*location & 0xfff) | hi20;
	*(location + 1) = (*(location + 1) & 0xfffff) | (lo12 << 20);
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_relax_rela(काष्ठा module *me, u32 *location,
				    Elf_Addr v)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_align_rela(काष्ठा module *me, u32 *location,
				    Elf_Addr v)
अणु
	pr_err(
	  "%s: The unexpected relocation type 'R_RISCV_ALIGN' from PC = %p\n",
	  me->name, location);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक apply_r_riscv_add32_rela(काष्ठा module *me, u32 *location,
				    Elf_Addr v)
अणु
	*(u32 *)location += (u32)v;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_add64_rela(काष्ठा module *me, u32 *location,
				    Elf_Addr v)
अणु
	*(u64 *)location += (u64)v;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_sub32_rela(काष्ठा module *me, u32 *location,
				    Elf_Addr v)
अणु
	*(u32 *)location -= (u32)v;
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_riscv_sub64_rela(काष्ठा module *me, u32 *location,
				    Elf_Addr v)
अणु
	*(u64 *)location -= (u64)v;
	वापस 0;
पूर्ण

अटल पूर्णांक (*reloc_handlers_rela[]) (काष्ठा module *me, u32 *location,
				Elf_Addr v) = अणु
	[R_RISCV_32]			= apply_r_riscv_32_rela,
	[R_RISCV_64]			= apply_r_riscv_64_rela,
	[R_RISCV_BRANCH]		= apply_r_riscv_branch_rela,
	[R_RISCV_JAL]			= apply_r_riscv_jal_rela,
	[R_RISCV_RVC_BRANCH]		= apply_r_riscv_rcv_branch_rela,
	[R_RISCV_RVC_JUMP]		= apply_r_riscv_rvc_jump_rela,
	[R_RISCV_PCREL_HI20]		= apply_r_riscv_pcrel_hi20_rela,
	[R_RISCV_PCREL_LO12_I]		= apply_r_riscv_pcrel_lo12_i_rela,
	[R_RISCV_PCREL_LO12_S]		= apply_r_riscv_pcrel_lo12_s_rela,
	[R_RISCV_HI20]			= apply_r_riscv_hi20_rela,
	[R_RISCV_LO12_I]		= apply_r_riscv_lo12_i_rela,
	[R_RISCV_LO12_S]		= apply_r_riscv_lo12_s_rela,
	[R_RISCV_GOT_HI20]		= apply_r_riscv_got_hi20_rela,
	[R_RISCV_CALL_PLT]		= apply_r_riscv_call_plt_rela,
	[R_RISCV_CALL]			= apply_r_riscv_call_rela,
	[R_RISCV_RELAX]			= apply_r_riscv_relax_rela,
	[R_RISCV_ALIGN]			= apply_r_riscv_align_rela,
	[R_RISCV_ADD32]			= apply_r_riscv_add32_rela,
	[R_RISCV_ADD64]			= apply_r_riscv_add64_rela,
	[R_RISCV_SUB32]			= apply_r_riscv_sub32_rela,
	[R_RISCV_SUB64]			= apply_r_riscv_sub64_rela,
पूर्ण;

पूर्णांक apply_relocate_add(Elf_Shdr *sechdrs, स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	Elf_Rela *rel = (व्योम *) sechdrs[rअन्यथाc].sh_addr;
	पूर्णांक (*handler)(काष्ठा module *me, u32 *location, Elf_Addr v);
	Elf_Sym *sym;
	u32 *location;
	अचिन्हित पूर्णांक i, type;
	Elf_Addr v;
	पूर्णांक res;

	pr_debug("Applying relocate section %u to %u\n", rअन्यथाc,
	       sechdrs[rअन्यथाc].sh_info);

	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rel[i].r_offset;
		/* This is the symbol it is referring to */
		sym = (Elf_Sym *)sechdrs[symindex].sh_addr
			+ ELF_RISCV_R_SYM(rel[i].r_info);
		अगर (IS_ERR_VALUE(sym->st_value)) अणु
			/* Ignore unresolved weak symbol */
			अगर (ELF_ST_BIND(sym->st_info) == STB_WEAK)
				जारी;
			pr_warn("%s: Unknown symbol %s\n",
				me->name, strtab + sym->st_name);
			वापस -ENOENT;
		पूर्ण

		type = ELF_RISCV_R_TYPE(rel[i].r_info);

		अगर (type < ARRAY_SIZE(reloc_handlers_rela))
			handler = reloc_handlers_rela[type];
		अन्यथा
			handler = शून्य;

		अगर (!handler) अणु
			pr_err("%s: Unknown relocation type %u\n",
			       me->name, type);
			वापस -EINVAL;
		पूर्ण

		v = sym->st_value + rel[i].r_addend;

		अगर (type == R_RISCV_PCREL_LO12_I || type == R_RISCV_PCREL_LO12_S) अणु
			अचिन्हित पूर्णांक j;

			क्रम (j = 0; j < sechdrs[rअन्यथाc].sh_size / माप(*rel); j++) अणु
				अचिन्हित दीर्घ hi20_loc =
					sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
					+ rel[j].r_offset;
				u32 hi20_type = ELF_RISCV_R_TYPE(rel[j].r_info);

				/* Find the corresponding HI20 relocation entry */
				अगर (hi20_loc == sym->st_value
				    && (hi20_type == R_RISCV_PCREL_HI20
					|| hi20_type == R_RISCV_GOT_HI20)) अणु
					s32 hi20, lo12;
					Elf_Sym *hi20_sym =
						(Elf_Sym *)sechdrs[symindex].sh_addr
						+ ELF_RISCV_R_SYM(rel[j].r_info);
					अचिन्हित दीर्घ hi20_sym_val =
						hi20_sym->st_value
						+ rel[j].r_addend;

					/* Calculate lo12 */
					माप_प्रकार offset = hi20_sym_val - hi20_loc;
					अगर (IS_ENABLED(CONFIG_MODULE_SECTIONS)
					    && hi20_type == R_RISCV_GOT_HI20) अणु
						offset = module_emit_got_entry(
							 me, hi20_sym_val);
						offset = offset - hi20_loc;
					पूर्ण
					hi20 = (offset + 0x800) & 0xfffff000;
					lo12 = offset - hi20;
					v = lo12;

					अवरोध;
				पूर्ण
			पूर्ण
			अगर (j == sechdrs[rअन्यथाc].sh_size / माप(*rel)) अणु
				pr_err(
				  "%s: Can not find HI20 relocation information\n",
				  me->name);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		res = handler(me, location, v);
		अगर (res)
			वापस res;
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_MMU) && defined(CONFIG_64BIT)
व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node_range(size, 1, MODULES_VADDR,
				    MODULES_END, GFP_KERNEL,
				    PAGE_KERNEL, 0, NUMA_NO_NODE,
				    __builtin_वापस_address(0));
पूर्ण
#पूर्ण_अगर
