<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/module.c
 *
 *  Copyright (C) 2002 Russell King.
 *  Modअगरied क्रम nommu by Hyok S. Choi
 *
 * Module allocation method suggested by Andi Kleen.
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/opcodes.h>

#अगर_घोषित CONFIG_XIP_KERNEL
/*
 * The XIP kernel text is mapped in the module area क्रम modules and
 * some other stuff to work without any indirect relocations.
 * MODULES_VADDR is redefined here and not in यंत्र/memory.h to aव्योम
 * recompiling the whole kernel when CONFIG_XIP_KERNEL is turned on/off.
 */
#अघोषित MODULES_VADDR
#घोषणा MODULES_VADDR	(((अचिन्हित दीर्घ)_exiprom + ~PMD_MASK) & PMD_MASK)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	gfp_t gfp_mask = GFP_KERNEL;
	व्योम *p;

	/* Silence the initial allocation */
	अगर (IS_ENABLED(CONFIG_ARM_MODULE_PLTS))
		gfp_mask |= __GFP_NOWARN;

	p = __vदो_स्मृति_node_range(size, 1, MODULES_VADDR, MODULES_END,
				gfp_mask, PAGE_KERNEL_EXEC, 0, NUMA_NO_NODE,
				__builtin_वापस_address(0));
	अगर (!IS_ENABLED(CONFIG_ARM_MODULE_PLTS) || p)
		वापस p;
	वापस __vदो_स्मृति_node_range(size, 1,  VMALLOC_START, VMALLOC_END,
				GFP_KERNEL, PAGE_KERNEL_EXEC, 0, NUMA_NO_NODE,
				__builtin_वापस_address(0));
पूर्ण
#पूर्ण_अगर

bool module_init_section(स्थिर अक्षर *name)
अणु
	वापस strstarts(name, ".init") ||
		strstarts(name, ".ARM.extab.init") ||
		strstarts(name, ".ARM.exidx.init");
पूर्ण

bool module_निकास_section(स्थिर अक्षर *name)
अणु
	वापस strstarts(name, ".exit") ||
		strstarts(name, ".ARM.extab.exit") ||
		strstarts(name, ".ARM.exidx.exit");
पूर्ण

पूर्णांक
apply_relocate(Elf32_Shdr *sechdrs, स्थिर अक्षर *strtab, अचिन्हित पूर्णांक symindex,
	       अचिन्हित पूर्णांक relindex, काष्ठा module *module)
अणु
	Elf32_Shdr *symsec = sechdrs + symindex;
	Elf32_Shdr *rअन्यथाc = sechdrs + relindex;
	Elf32_Shdr *dstsec = sechdrs + rअन्यथाc->sh_info;
	Elf32_Rel *rel = (व्योम *)rअन्यथाc->sh_addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < rअन्यथाc->sh_size / माप(Elf32_Rel); i++, rel++) अणु
		अचिन्हित दीर्घ loc;
		Elf32_Sym *sym;
		स्थिर अक्षर *symname;
		s32 offset;
		u32 पंचांगp;
#अगर_घोषित CONFIG_THUMB2_KERNEL
		u32 upper, lower, sign, j1, j2;
#पूर्ण_अगर

		offset = ELF32_R_SYM(rel->r_info);
		अगर (offset < 0 || offset > (symsec->sh_size / माप(Elf32_Sym))) अणु
			pr_err("%s: section %u reloc %u: bad relocation sym offset\n",
				module->name, relindex, i);
			वापस -ENOEXEC;
		पूर्ण

		sym = ((Elf32_Sym *)symsec->sh_addr) + offset;
		symname = strtab + sym->st_name;

		अगर (rel->r_offset < 0 || rel->r_offset > dstsec->sh_size - माप(u32)) अणु
			pr_err("%s: section %u reloc %u sym '%s': out of bounds relocation, offset %d size %u\n",
			       module->name, relindex, i, symname,
			       rel->r_offset, dstsec->sh_size);
			वापस -ENOEXEC;
		पूर्ण

		loc = dstsec->sh_addr + rel->r_offset;

		चयन (ELF32_R_TYPE(rel->r_info)) अणु
		हाल R_ARM_NONE:
			/* ignore */
			अवरोध;

		हाल R_ARM_ABS32:
		हाल R_ARM_TARGET1:
			*(u32 *)loc += sym->st_value;
			अवरोध;

		हाल R_ARM_PC24:
		हाल R_ARM_CALL:
		हाल R_ARM_JUMP24:
			अगर (sym->st_value & 3) अणु
				pr_err("%s: section %u reloc %u sym '%s': unsupported interworking call (ARM -> Thumb)\n",
				       module->name, relindex, i, symname);
				वापस -ENOEXEC;
			पूर्ण

			offset = __mem_to_opcode_arm(*(u32 *)loc);
			offset = (offset & 0x00ffffff) << 2;
			अगर (offset & 0x02000000)
				offset -= 0x04000000;

			offset += sym->st_value - loc;

			/*
			 * Route through a PLT entry अगर 'offset' exceeds the
			 * supported range. Note that 'offset + loc + 8'
			 * contains the असलolute jump target, i.e.,
			 * @sym + addend, corrected क्रम the +8 PC bias.
			 */
			अगर (IS_ENABLED(CONFIG_ARM_MODULE_PLTS) &&
			    (offset <= (s32)0xfe000000 ||
			     offset >= (s32)0x02000000))
				offset = get_module_plt(module, loc,
							offset + loc + 8)
					 - loc - 8;

			अगर (offset <= (s32)0xfe000000 ||
			    offset >= (s32)0x02000000) अणु
				pr_err("%s: section %u reloc %u sym '%s': relocation %u out of range (%#lx -> %#x)\n",
				       module->name, relindex, i, symname,
				       ELF32_R_TYPE(rel->r_info), loc,
				       sym->st_value);
				वापस -ENOEXEC;
			पूर्ण

			offset >>= 2;
			offset &= 0x00ffffff;

			*(u32 *)loc &= __opcode_to_mem_arm(0xff000000);
			*(u32 *)loc |= __opcode_to_mem_arm(offset);
			अवरोध;

	       हाल R_ARM_V4BX:
		       /* Preserve Rm and the condition code. Alter
			* other bits to re-code inकाष्ठाion as
			* MOV PC,Rm.
			*/
		       *(u32 *)loc &= __opcode_to_mem_arm(0xf000000f);
		       *(u32 *)loc |= __opcode_to_mem_arm(0x01a0f000);
		       अवरोध;

		हाल R_ARM_PREL31:
			offset = (*(s32 *)loc << 1) >> 1; /* sign extend */
			offset += sym->st_value - loc;
			अगर (offset >= 0x40000000 || offset < -0x40000000) अणु
				pr_err("%s: section %u reloc %u sym '%s': relocation %u out of range (%#lx -> %#x)\n",
				       module->name, relindex, i, symname,
				       ELF32_R_TYPE(rel->r_info), loc,
				       sym->st_value);
				वापस -ENOEXEC;
			पूर्ण
			*(u32 *)loc &= 0x80000000;
			*(u32 *)loc |= offset & 0x7fffffff;
			अवरोध;

		हाल R_ARM_REL32:
			*(u32 *)loc += sym->st_value - loc;
			अवरोध;

		हाल R_ARM_MOVW_ABS_NC:
		हाल R_ARM_MOVT_ABS:
		हाल R_ARM_MOVW_PREL_NC:
		हाल R_ARM_MOVT_PREL:
			offset = पंचांगp = __mem_to_opcode_arm(*(u32 *)loc);
			offset = ((offset & 0xf0000) >> 4) | (offset & 0xfff);
			offset = (offset ^ 0x8000) - 0x8000;

			offset += sym->st_value;
			अगर (ELF32_R_TYPE(rel->r_info) == R_ARM_MOVT_PREL ||
			    ELF32_R_TYPE(rel->r_info) == R_ARM_MOVW_PREL_NC)
				offset -= loc;
			अगर (ELF32_R_TYPE(rel->r_info) == R_ARM_MOVT_ABS ||
			    ELF32_R_TYPE(rel->r_info) == R_ARM_MOVT_PREL)
				offset >>= 16;

			पंचांगp &= 0xfff0f000;
			पंचांगp |= ((offset & 0xf000) << 4) |
				(offset & 0x0fff);

			*(u32 *)loc = __opcode_to_mem_arm(पंचांगp);
			अवरोध;

#अगर_घोषित CONFIG_THUMB2_KERNEL
		हाल R_ARM_THM_CALL:
		हाल R_ARM_THM_JUMP24:
			/*
			 * For function symbols, only Thumb addresses are
			 * allowed (no पूर्णांकerworking).
			 *
			 * For non-function symbols, the destination
			 * has no specअगरic ARM/Thumb disposition, so
			 * the branch is resolved under the assumption
			 * that पूर्णांकerworking is not required.
			 */
			अगर (ELF32_ST_TYPE(sym->st_info) == STT_FUNC &&
			    !(sym->st_value & 1)) अणु
				pr_err("%s: section %u reloc %u sym '%s': unsupported interworking call (Thumb -> ARM)\n",
				       module->name, relindex, i, symname);
				वापस -ENOEXEC;
			पूर्ण

			upper = __mem_to_opcode_thumb16(*(u16 *)loc);
			lower = __mem_to_opcode_thumb16(*(u16 *)(loc + 2));

			/*
			 * 25 bit चिन्हित address range (Thumb-2 BL and B.W
			 * inकाष्ठाions):
			 *   S:I1:I2:imm10:imm11:0
			 * where:
			 *   S     = upper[10]   = offset[24]
			 *   I1    = ~(J1 ^ S)   = offset[23]
			 *   I2    = ~(J2 ^ S)   = offset[22]
			 *   imm10 = upper[9:0]  = offset[21:12]
			 *   imm11 = lower[10:0] = offset[11:1]
			 *   J1    = lower[13]
			 *   J2    = lower[11]
			 */
			sign = (upper >> 10) & 1;
			j1 = (lower >> 13) & 1;
			j2 = (lower >> 11) & 1;
			offset = (sign << 24) | ((~(j1 ^ sign) & 1) << 23) |
				((~(j2 ^ sign) & 1) << 22) |
				((upper & 0x03ff) << 12) |
				((lower & 0x07ff) << 1);
			अगर (offset & 0x01000000)
				offset -= 0x02000000;
			offset += sym->st_value - loc;

			/*
			 * Route through a PLT entry अगर 'offset' exceeds the
			 * supported range.
			 */
			अगर (IS_ENABLED(CONFIG_ARM_MODULE_PLTS) &&
			    (offset <= (s32)0xff000000 ||
			     offset >= (s32)0x01000000))
				offset = get_module_plt(module, loc,
							offset + loc + 4)
					 - loc - 4;

			अगर (offset <= (s32)0xff000000 ||
			    offset >= (s32)0x01000000) अणु
				pr_err("%s: section %u reloc %u sym '%s': relocation %u out of range (%#lx -> %#x)\n",
				       module->name, relindex, i, symname,
				       ELF32_R_TYPE(rel->r_info), loc,
				       sym->st_value);
				वापस -ENOEXEC;
			पूर्ण

			sign = (offset >> 24) & 1;
			j1 = sign ^ (~(offset >> 23) & 1);
			j2 = sign ^ (~(offset >> 22) & 1);
			upper = (u16)((upper & 0xf800) | (sign << 10) |
					    ((offset >> 12) & 0x03ff));
			lower = (u16)((lower & 0xd000) |
				      (j1 << 13) | (j2 << 11) |
				      ((offset >> 1) & 0x07ff));

			*(u16 *)loc = __opcode_to_mem_thumb16(upper);
			*(u16 *)(loc + 2) = __opcode_to_mem_thumb16(lower);
			अवरोध;

		हाल R_ARM_THM_MOVW_ABS_NC:
		हाल R_ARM_THM_MOVT_ABS:
		हाल R_ARM_THM_MOVW_PREL_NC:
		हाल R_ARM_THM_MOVT_PREL:
			upper = __mem_to_opcode_thumb16(*(u16 *)loc);
			lower = __mem_to_opcode_thumb16(*(u16 *)(loc + 2));

			/*
			 * MOVT/MOVW inकाष्ठाions encoding in Thumb-2:
			 *
			 * i	= upper[10]
			 * imm4	= upper[3:0]
			 * imm3	= lower[14:12]
			 * imm8	= lower[7:0]
			 *
			 * imm16 = imm4:i:imm3:imm8
			 */
			offset = ((upper & 0x000f) << 12) |
				((upper & 0x0400) << 1) |
				((lower & 0x7000) >> 4) | (lower & 0x00ff);
			offset = (offset ^ 0x8000) - 0x8000;
			offset += sym->st_value;

			अगर (ELF32_R_TYPE(rel->r_info) == R_ARM_THM_MOVT_PREL ||
			    ELF32_R_TYPE(rel->r_info) == R_ARM_THM_MOVW_PREL_NC)
				offset -= loc;
			अगर (ELF32_R_TYPE(rel->r_info) == R_ARM_THM_MOVT_ABS ||
			    ELF32_R_TYPE(rel->r_info) == R_ARM_THM_MOVT_PREL)
				offset >>= 16;

			upper = (u16)((upper & 0xfbf0) |
				      ((offset & 0xf000) >> 12) |
				      ((offset & 0x0800) >> 1));
			lower = (u16)((lower & 0x8f00) |
				      ((offset & 0x0700) << 4) |
				      (offset & 0x00ff));
			*(u16 *)loc = __opcode_to_mem_thumb16(upper);
			*(u16 *)(loc + 2) = __opcode_to_mem_thumb16(lower);
			अवरोध;
#पूर्ण_अगर

		शेष:
			pr_err("%s: unknown relocation: %u\n",
			       module->name, ELF32_R_TYPE(rel->r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा mod_unwind_map अणु
	स्थिर Elf_Shdr *unw_sec;
	स्थिर Elf_Shdr *txt_sec;
पूर्ण;

अटल स्थिर Elf_Shdr *find_mod_section(स्थिर Elf32_Ehdr *hdr,
	स्थिर Elf_Shdr *sechdrs, स्थिर अक्षर *name)
अणु
	स्थिर Elf_Shdr *s, *se;
	स्थिर अक्षर *secstrs = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	क्रम (s = sechdrs, se = sechdrs + hdr->e_shnum; s < se; s++)
		अगर (म_भेद(name, secstrs + s->sh_name) == 0)
			वापस s;

	वापस शून्य;
पूर्ण

बाह्य व्योम fixup_pv_table(स्थिर व्योम *, अचिन्हित दीर्घ);
बाह्य व्योम fixup_smp(स्थिर व्योम *, अचिन्हित दीर्घ);

पूर्णांक module_finalize(स्थिर Elf32_Ehdr *hdr, स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *mod)
अणु
	स्थिर Elf_Shdr *s = शून्य;
#अगर_घोषित CONFIG_ARM_UNWIND
	स्थिर अक्षर *secstrs = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;
	स्थिर Elf_Shdr *sechdrs_end = sechdrs + hdr->e_shnum;
	काष्ठा mod_unwind_map maps[ARM_SEC_MAX];
	पूर्णांक i;

	स_रखो(maps, 0, माप(maps));

	क्रम (s = sechdrs; s < sechdrs_end; s++) अणु
		स्थिर अक्षर *secname = secstrs + s->sh_name;

		अगर (!(s->sh_flags & SHF_ALLOC))
			जारी;

		अगर (म_भेद(".ARM.exidx.init.text", secname) == 0)
			maps[ARM_SEC_INIT].unw_sec = s;
		अन्यथा अगर (म_भेद(".ARM.exidx", secname) == 0)
			maps[ARM_SEC_CORE].unw_sec = s;
		अन्यथा अगर (म_भेद(".ARM.exidx.exit.text", secname) == 0)
			maps[ARM_SEC_EXIT].unw_sec = s;
		अन्यथा अगर (म_भेद(".ARM.exidx.text.unlikely", secname) == 0)
			maps[ARM_SEC_UNLIKELY].unw_sec = s;
		अन्यथा अगर (म_भेद(".ARM.exidx.text.hot", secname) == 0)
			maps[ARM_SEC_HOT].unw_sec = s;
		अन्यथा अगर (म_भेद(".init.text", secname) == 0)
			maps[ARM_SEC_INIT].txt_sec = s;
		अन्यथा अगर (म_भेद(".text", secname) == 0)
			maps[ARM_SEC_CORE].txt_sec = s;
		अन्यथा अगर (म_भेद(".exit.text", secname) == 0)
			maps[ARM_SEC_EXIT].txt_sec = s;
		अन्यथा अगर (म_भेद(".text.unlikely", secname) == 0)
			maps[ARM_SEC_UNLIKELY].txt_sec = s;
		अन्यथा अगर (म_भेद(".text.hot", secname) == 0)
			maps[ARM_SEC_HOT].txt_sec = s;
	पूर्ण

	क्रम (i = 0; i < ARM_SEC_MAX; i++)
		अगर (maps[i].unw_sec && maps[i].txt_sec)
			mod->arch.unwind[i] =
				unwind_table_add(maps[i].unw_sec->sh_addr,
					         maps[i].unw_sec->sh_size,
					         maps[i].txt_sec->sh_addr,
					         maps[i].txt_sec->sh_size);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_PATCH_PHYS_VIRT
	s = find_mod_section(hdr, sechdrs, ".pv_table");
	अगर (s)
		fixup_pv_table((व्योम *)s->sh_addr, s->sh_size);
#पूर्ण_अगर
	s = find_mod_section(hdr, sechdrs, ".alt.smp.init");
	अगर (s && !is_smp())
#अगर_घोषित CONFIG_SMP_ON_UP
		fixup_smp((व्योम *)s->sh_addr, s->sh_size);
#अन्यथा
		वापस -EINVAL;
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम
module_arch_cleanup(काष्ठा module *mod)
अणु
#अगर_घोषित CONFIG_ARM_UNWIND
	पूर्णांक i;

	क्रम (i = 0; i < ARM_SEC_MAX; i++) अणु
		unwind_table_del(mod->arch.unwind[i]);
		mod->arch.unwind[i] = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम __weak module_arch_मुक्तing_init(काष्ठा module *mod)
अणु
#अगर_घोषित CONFIG_ARM_UNWIND
	unwind_table_del(mod->arch.unwind[ARM_SEC_INIT]);
	mod->arch.unwind[ARM_SEC_INIT] = शून्य;
#पूर्ण_अगर
पूर्ण
