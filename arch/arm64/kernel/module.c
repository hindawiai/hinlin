<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AArch64 loadable module support.
 *
 * Copyright (C) 2012 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/elf.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/sections.h>

व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	u64 module_alloc_end = module_alloc_base + MODULES_VSIZE;
	gfp_t gfp_mask = GFP_KERNEL;
	व्योम *p;

	/* Silence the initial allocation */
	अगर (IS_ENABLED(CONFIG_ARM64_MODULE_PLTS))
		gfp_mask |= __GFP_NOWARN;

	अगर (IS_ENABLED(CONFIG_KASAN_GENERIC) ||
	    IS_ENABLED(CONFIG_KASAN_SW_TAGS))
		/* करोn't exceed the अटल module region - see below */
		module_alloc_end = MODULES_END;

	p = __vदो_स्मृति_node_range(size, MODULE_ALIGN, module_alloc_base,
				module_alloc_end, gfp_mask, PAGE_KERNEL, 0,
				NUMA_NO_NODE, __builtin_वापस_address(0));

	अगर (!p && IS_ENABLED(CONFIG_ARM64_MODULE_PLTS) &&
	    (IS_ENABLED(CONFIG_KASAN_VMALLOC) ||
	     (!IS_ENABLED(CONFIG_KASAN_GENERIC) &&
	      !IS_ENABLED(CONFIG_KASAN_SW_TAGS))))
		/*
		 * KASAN without KASAN_VMALLOC can only deal with module
		 * allocations being served from the reserved module region,
		 * since the reमुख्यder of the vदो_स्मृति region is alपढ़ोy
		 * backed by zero shaकरोw pages, and punching holes पूर्णांकo it
		 * is non-trivial. Since the module region is not अक्रमomized
		 * when KASAN is enabled without KASAN_VMALLOC, it is even
		 * less likely that the module region माला_लो exhausted, so we
		 * can simply omit this fallback in that हाल.
		 */
		p = __vदो_स्मृति_node_range(size, MODULE_ALIGN, module_alloc_base,
				module_alloc_base + SZ_2G, GFP_KERNEL,
				PAGE_KERNEL, 0, NUMA_NO_NODE,
				__builtin_वापस_address(0));

	अगर (p && (kasan_module_alloc(p, size) < 0)) अणु
		vमुक्त(p);
		वापस शून्य;
	पूर्ण

	वापस p;
पूर्ण

क्रमागत aarch64_reloc_op अणु
	RELOC_OP_NONE,
	RELOC_OP_ABS,
	RELOC_OP_PREL,
	RELOC_OP_PAGE,
पूर्ण;

अटल u64 करो_reloc(क्रमागत aarch64_reloc_op reloc_op, __le32 *place, u64 val)
अणु
	चयन (reloc_op) अणु
	हाल RELOC_OP_ABS:
		वापस val;
	हाल RELOC_OP_PREL:
		वापस val - (u64)place;
	हाल RELOC_OP_PAGE:
		वापस (val & ~0xfff) - ((u64)place & ~0xfff);
	हाल RELOC_OP_NONE:
		वापस 0;
	पूर्ण

	pr_err("do_reloc: unknown relocation operation %d\n", reloc_op);
	वापस 0;
पूर्ण

अटल पूर्णांक reloc_data(क्रमागत aarch64_reloc_op op, व्योम *place, u64 val, पूर्णांक len)
अणु
	s64 sval = करो_reloc(op, place, val);

	/*
	 * The ELF psABI क्रम AArch64 करोcuments the 16-bit and 32-bit place
	 * relative and असलolute relocations as having a range of [-2^15, 2^16)
	 * or [-2^31, 2^32), respectively. However, in order to be able to
	 * detect overflows reliably, we have to choose whether we पूर्णांकerpret
	 * such quantities as चिन्हित or as अचिन्हित, and stick with it.
	 * The way we organize our address space requires a चिन्हित
	 * पूर्णांकerpretation of 32-bit relative references, so let's use that
	 * क्रम all R_AARCH64_PRELxx relocations. This means our upper
	 * bound क्रम overflow detection should be Sxx_MAX rather than Uxx_MAX.
	 */

	चयन (len) अणु
	हाल 16:
		*(s16 *)place = sval;
		चयन (op) अणु
		हाल RELOC_OP_ABS:
			अगर (sval < 0 || sval > U16_MAX)
				वापस -दुस्फल;
			अवरोध;
		हाल RELOC_OP_PREL:
			अगर (sval < S16_MIN || sval > S16_MAX)
				वापस -दुस्फल;
			अवरोध;
		शेष:
			pr_err("Invalid 16-bit data relocation (%d)\n", op);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल 32:
		*(s32 *)place = sval;
		चयन (op) अणु
		हाल RELOC_OP_ABS:
			अगर (sval < 0 || sval > U32_MAX)
				वापस -दुस्फल;
			अवरोध;
		हाल RELOC_OP_PREL:
			अगर (sval < S32_MIN || sval > S32_MAX)
				वापस -दुस्फल;
			अवरोध;
		शेष:
			pr_err("Invalid 32-bit data relocation (%d)\n", op);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल 64:
		*(s64 *)place = sval;
		अवरोध;
	शेष:
		pr_err("Invalid length (%d) for data relocation\n", len);
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत aarch64_insn_movw_imm_type अणु
	AARCH64_INSN_IMM_MOVNZ,
	AARCH64_INSN_IMM_MOVKZ,
पूर्ण;

अटल पूर्णांक reloc_insn_movw(क्रमागत aarch64_reloc_op op, __le32 *place, u64 val,
			   पूर्णांक lsb, क्रमागत aarch64_insn_movw_imm_type imm_type)
अणु
	u64 imm;
	s64 sval;
	u32 insn = le32_to_cpu(*place);

	sval = करो_reloc(op, place, val);
	imm = sval >> lsb;

	अगर (imm_type == AARCH64_INSN_IMM_MOVNZ) अणु
		/*
		 * For चिन्हित MOVW relocations, we have to manipulate the
		 * inकाष्ठाion encoding depending on whether or not the
		 * immediate is less than zero.
		 */
		insn &= ~(3 << 29);
		अगर (sval >= 0) अणु
			/* >=0: Set the inकाष्ठाion to MOVZ (opcode 10b). */
			insn |= 2 << 29;
		पूर्ण अन्यथा अणु
			/*
			 * <0: Set the inकाष्ठाion to MOVN (opcode 00b).
			 *     Since we've masked the opcode alपढ़ोy, we
			 *     करोn't need to करो anything other than
			 *     inverting the new immediate field.
			 */
			imm = ~imm;
		पूर्ण
	पूर्ण

	/* Update the inकाष्ठाion with the new encoding. */
	insn = aarch64_insn_encode_immediate(AARCH64_INSN_IMM_16, insn, imm);
	*place = cpu_to_le32(insn);

	अगर (imm > U16_MAX)
		वापस -दुस्फल;

	वापस 0;
पूर्ण

अटल पूर्णांक reloc_insn_imm(क्रमागत aarch64_reloc_op op, __le32 *place, u64 val,
			  पूर्णांक lsb, पूर्णांक len, क्रमागत aarch64_insn_imm_type imm_type)
अणु
	u64 imm, imm_mask;
	s64 sval;
	u32 insn = le32_to_cpu(*place);

	/* Calculate the relocation value. */
	sval = करो_reloc(op, place, val);
	sval >>= lsb;

	/* Extract the value bits and shअगरt them to bit 0. */
	imm_mask = (BIT(lsb + len) - 1) >> lsb;
	imm = sval & imm_mask;

	/* Update the inकाष्ठाion's immediate field. */
	insn = aarch64_insn_encode_immediate(imm_type, insn, imm);
	*place = cpu_to_le32(insn);

	/*
	 * Extract the upper value bits (including the sign bit) and
	 * shअगरt them to bit 0.
	 */
	sval = (s64)(sval & ~(imm_mask >> 1)) >> (len - 1);

	/*
	 * Overflow has occurred अगर the upper bits are not all equal to
	 * the sign bit of the value.
	 */
	अगर ((u64)(sval + 1) >= 2)
		वापस -दुस्फल;

	वापस 0;
पूर्ण

अटल पूर्णांक reloc_insn_adrp(काष्ठा module *mod, Elf64_Shdr *sechdrs,
			   __le32 *place, u64 val)
अणु
	u32 insn;

	अगर (!is_क्रमbidden_offset_क्रम_adrp(place))
		वापस reloc_insn_imm(RELOC_OP_PAGE, place, val, 12, 21,
				      AARCH64_INSN_IMM_ADR);

	/* patch ADRP to ADR अगर it is in range */
	अगर (!reloc_insn_imm(RELOC_OP_PREL, place, val & ~0xfff, 0, 21,
			    AARCH64_INSN_IMM_ADR)) अणु
		insn = le32_to_cpu(*place);
		insn &= ~BIT(31);
	पूर्ण अन्यथा अणु
		/* out of range क्रम ADR -> emit a veneer */
		val = module_emit_veneer_क्रम_adrp(mod, sechdrs, place, val & ~0xfff);
		अगर (!val)
			वापस -ENOEXEC;
		insn = aarch64_insn_gen_branch_imm((u64)place, val,
						   AARCH64_INSN_BRANCH_NOLINK);
	पूर्ण

	*place = cpu_to_le32(insn);
	वापस 0;
पूर्ण

पूर्णांक apply_relocate_add(Elf64_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ovf;
	bool overflow_check;
	Elf64_Sym *sym;
	व्योम *loc;
	u64 val;
	Elf64_Rela *rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;

	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* loc corresponds to P in the AArch64 ELF करोcument. */
		loc = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rel[i].r_offset;

		/* sym is the ELF symbol we're referring to. */
		sym = (Elf64_Sym *)sechdrs[symindex].sh_addr
			+ ELF64_R_SYM(rel[i].r_info);

		/* val corresponds to (S + A) in the AArch64 ELF करोcument. */
		val = sym->st_value + rel[i].r_addend;

		/* Check क्रम overflow by शेष. */
		overflow_check = true;

		/* Perक्रमm the अटल relocation. */
		चयन (ELF64_R_TYPE(rel[i].r_info)) अणु
		/* Null relocations. */
		हाल R_ARM_NONE:
		हाल R_AARCH64_NONE:
			ovf = 0;
			अवरोध;

		/* Data relocations. */
		हाल R_AARCH64_ABS64:
			overflow_check = false;
			ovf = reloc_data(RELOC_OP_ABS, loc, val, 64);
			अवरोध;
		हाल R_AARCH64_ABS32:
			ovf = reloc_data(RELOC_OP_ABS, loc, val, 32);
			अवरोध;
		हाल R_AARCH64_ABS16:
			ovf = reloc_data(RELOC_OP_ABS, loc, val, 16);
			अवरोध;
		हाल R_AARCH64_PREL64:
			overflow_check = false;
			ovf = reloc_data(RELOC_OP_PREL, loc, val, 64);
			अवरोध;
		हाल R_AARCH64_PREL32:
			ovf = reloc_data(RELOC_OP_PREL, loc, val, 32);
			अवरोध;
		हाल R_AARCH64_PREL16:
			ovf = reloc_data(RELOC_OP_PREL, loc, val, 16);
			अवरोध;

		/* MOVW inकाष्ठाion relocations. */
		हाल R_AARCH64_MOVW_UABS_G0_NC:
			overflow_check = false;
			fallthrough;
		हाल R_AARCH64_MOVW_UABS_G0:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 0,
					      AARCH64_INSN_IMM_MOVKZ);
			अवरोध;
		हाल R_AARCH64_MOVW_UABS_G1_NC:
			overflow_check = false;
			fallthrough;
		हाल R_AARCH64_MOVW_UABS_G1:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 16,
					      AARCH64_INSN_IMM_MOVKZ);
			अवरोध;
		हाल R_AARCH64_MOVW_UABS_G2_NC:
			overflow_check = false;
			fallthrough;
		हाल R_AARCH64_MOVW_UABS_G2:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 32,
					      AARCH64_INSN_IMM_MOVKZ);
			अवरोध;
		हाल R_AARCH64_MOVW_UABS_G3:
			/* We're using the top bits so we can't overflow. */
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 48,
					      AARCH64_INSN_IMM_MOVKZ);
			अवरोध;
		हाल R_AARCH64_MOVW_SABS_G0:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 0,
					      AARCH64_INSN_IMM_MOVNZ);
			अवरोध;
		हाल R_AARCH64_MOVW_SABS_G1:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 16,
					      AARCH64_INSN_IMM_MOVNZ);
			अवरोध;
		हाल R_AARCH64_MOVW_SABS_G2:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 32,
					      AARCH64_INSN_IMM_MOVNZ);
			अवरोध;
		हाल R_AARCH64_MOVW_PREL_G0_NC:
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 0,
					      AARCH64_INSN_IMM_MOVKZ);
			अवरोध;
		हाल R_AARCH64_MOVW_PREL_G0:
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 0,
					      AARCH64_INSN_IMM_MOVNZ);
			अवरोध;
		हाल R_AARCH64_MOVW_PREL_G1_NC:
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 16,
					      AARCH64_INSN_IMM_MOVKZ);
			अवरोध;
		हाल R_AARCH64_MOVW_PREL_G1:
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 16,
					      AARCH64_INSN_IMM_MOVNZ);
			अवरोध;
		हाल R_AARCH64_MOVW_PREL_G2_NC:
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 32,
					      AARCH64_INSN_IMM_MOVKZ);
			अवरोध;
		हाल R_AARCH64_MOVW_PREL_G2:
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 32,
					      AARCH64_INSN_IMM_MOVNZ);
			अवरोध;
		हाल R_AARCH64_MOVW_PREL_G3:
			/* We're using the top bits so we can't overflow. */
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 48,
					      AARCH64_INSN_IMM_MOVNZ);
			अवरोध;

		/* Immediate inकाष्ठाion relocations. */
		हाल R_AARCH64_LD_PREL_LO19:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2, 19,
					     AARCH64_INSN_IMM_19);
			अवरोध;
		हाल R_AARCH64_ADR_PREL_LO21:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 0, 21,
					     AARCH64_INSN_IMM_ADR);
			अवरोध;
		हाल R_AARCH64_ADR_PREL_PG_HI21_NC:
			overflow_check = false;
			fallthrough;
		हाल R_AARCH64_ADR_PREL_PG_HI21:
			ovf = reloc_insn_adrp(me, sechdrs, loc, val);
			अगर (ovf && ovf != -दुस्फल)
				वापस ovf;
			अवरोध;
		हाल R_AARCH64_ADD_ABS_LO12_NC:
		हाल R_AARCH64_LDST8_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 0, 12,
					     AARCH64_INSN_IMM_12);
			अवरोध;
		हाल R_AARCH64_LDST16_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 1, 11,
					     AARCH64_INSN_IMM_12);
			अवरोध;
		हाल R_AARCH64_LDST32_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 2, 10,
					     AARCH64_INSN_IMM_12);
			अवरोध;
		हाल R_AARCH64_LDST64_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 3, 9,
					     AARCH64_INSN_IMM_12);
			अवरोध;
		हाल R_AARCH64_LDST128_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 4, 8,
					     AARCH64_INSN_IMM_12);
			अवरोध;
		हाल R_AARCH64_TSTBR14:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2, 14,
					     AARCH64_INSN_IMM_14);
			अवरोध;
		हाल R_AARCH64_CONDBR19:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2, 19,
					     AARCH64_INSN_IMM_19);
			अवरोध;
		हाल R_AARCH64_JUMP26:
		हाल R_AARCH64_CALL26:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2, 26,
					     AARCH64_INSN_IMM_26);

			अगर (IS_ENABLED(CONFIG_ARM64_MODULE_PLTS) &&
			    ovf == -दुस्फल) अणु
				val = module_emit_plt_entry(me, sechdrs, loc, &rel[i], sym);
				अगर (!val)
					वापस -ENOEXEC;
				ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2,
						     26, AARCH64_INSN_IMM_26);
			पूर्ण
			अवरोध;

		शेष:
			pr_err("module %s: unsupported RELA relocation: %llu\n",
			       me->name, ELF64_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण

		अगर (overflow_check && ovf == -दुस्फल)
			जाओ overflow;

	पूर्ण

	वापस 0;

overflow:
	pr_err("module %s: overflow in relocation type %d val %Lx\n",
	       me->name, (पूर्णांक)ELF64_R_TYPE(rel[i].r_info), val);
	वापस -ENOEXEC;
पूर्ण

अटल स्थिर Elf_Shdr *find_section(स्थिर Elf_Ehdr *hdr,
				    स्थिर Elf_Shdr *sechdrs,
				    स्थिर अक्षर *name)
अणु
	स्थिर Elf_Shdr *s, *se;
	स्थिर अक्षर *secstrs = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	क्रम (s = sechdrs, se = sechdrs + hdr->e_shnum; s < se; s++) अणु
		अगर (म_भेद(name, secstrs + s->sh_name) == 0)
			वापस s;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम __init_plt(काष्ठा plt_entry *plt, अचिन्हित दीर्घ addr)
अणु
	*plt = get_plt_entry(addr, plt);
पूर्ण

अटल पूर्णांक module_init_ftrace_plt(स्थिर Elf_Ehdr *hdr,
				  स्थिर Elf_Shdr *sechdrs,
				  काष्ठा module *mod)
अणु
#अगर defined(CONFIG_ARM64_MODULE_PLTS) && defined(CONFIG_DYNAMIC_FTRACE)
	स्थिर Elf_Shdr *s;
	काष्ठा plt_entry *plts;

	s = find_section(hdr, sechdrs, ".text.ftrace_trampoline");
	अगर (!s)
		वापस -ENOEXEC;

	plts = (व्योम *)s->sh_addr;

	__init_plt(&plts[FTRACE_PLT_IDX], FTRACE_ADDR);

	अगर (IS_ENABLED(CONFIG_DYNAMIC_FTRACE_WITH_REGS))
		__init_plt(&plts[FTRACE_REGS_PLT_IDX], FTRACE_REGS_ADDR);

	mod->arch.ftrace_trampolines = plts;
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		    स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *me)
अणु
	स्थिर Elf_Shdr *s;
	s = find_section(hdr, sechdrs, ".altinstructions");
	अगर (s)
		apply_alternatives_module((व्योम *)s->sh_addr, s->sh_size);

	वापस module_init_ftrace_plt(hdr, sechdrs, me);
पूर्ण
