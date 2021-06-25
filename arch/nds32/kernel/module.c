<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/module.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/pgtable.h>

व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node_range(size, 1, MODULES_VADDR, MODULES_END,
				    GFP_KERNEL, PAGE_KERNEL, 0, NUMA_NO_NODE,
				    __builtin_वापस_address(0));
पूर्ण

व्योम module_मुक्त(काष्ठा module *module, व्योम *region)
अणु
	vमुक्त(region);
पूर्ण

पूर्णांक module_frob_arch_sections(Elf_Ehdr * hdr,
			      Elf_Shdr * sechdrs,
			      अक्षर *secstrings, काष्ठा module *mod)
अणु
	वापस 0;
पूर्ण

व्योम करो_reloc16(अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक *loc, अचिन्हित पूर्णांक val_mask,
		अचिन्हित पूर्णांक val_shअगरt, अचिन्हित पूर्णांक loc_mask,
		अचिन्हित पूर्णांक partial_in_place, अचिन्हित पूर्णांक swap)
अणु
	अचिन्हित पूर्णांक पंचांगp = 0, पंचांगp2 = 0;

	__यंत्र__ __अस्थिर__("\tlhi.bi\t%0, [%2], 0\n"
			     "\tbeqz\t%3, 1f\n"
			     "\twsbh\t%0, %1\n"
			     "1:\n":"=r"(पंचांगp):"0"(पंचांगp), "r"(loc), "r"(swap)
	    );

	पंचांगp2 = पंचांगp & loc_mask;
	अगर (partial_in_place) अणु
		पंचांगp &= (~loc_mask);
		पंचांगp =
		    पंचांगp2 | ((पंचांगp + ((val & val_mask) >> val_shअगरt)) & val_mask);
	पूर्ण अन्यथा अणु
		पंचांगp = पंचांगp2 | ((val & val_mask) >> val_shअगरt);
	पूर्ण

	__यंत्र__ __अस्थिर__("\tbeqz\t%3, 2f\n"
			     "\twsbh\t%0, %1\n"
			     "2:\n"
			     "\tshi.bi\t%0, [%2], 0\n":"=r"(पंचांगp):"0"(पंचांगp),
			     "r"(loc), "r"(swap)
	    );
पूर्ण

व्योम करो_reloc32(अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक *loc, अचिन्हित पूर्णांक val_mask,
		अचिन्हित पूर्णांक val_shअगरt, अचिन्हित पूर्णांक loc_mask,
		अचिन्हित पूर्णांक partial_in_place, अचिन्हित पूर्णांक swap)
अणु
	अचिन्हित पूर्णांक पंचांगp = 0, पंचांगp2 = 0;

	__यंत्र__ __अस्थिर__("\tlmw.bi\t%0, [%2], %0, 0\n"
			     "\tbeqz\t%3, 1f\n"
			     "\twsbh\t%0, %1\n"
			     "\trotri\t%0, %1, 16\n"
			     "1:\n":"=r"(पंचांगp):"0"(पंचांगp), "r"(loc), "r"(swap)
	    );

	पंचांगp2 = पंचांगp & loc_mask;
	अगर (partial_in_place) अणु
		पंचांगp &= (~loc_mask);
		पंचांगp =
		    पंचांगp2 | ((पंचांगp + ((val & val_mask) >> val_shअगरt)) & val_mask);
	पूर्ण अन्यथा अणु
		पंचांगp = पंचांगp2 | ((val & val_mask) >> val_shअगरt);
	पूर्ण

	__यंत्र__ __अस्थिर__("\tbeqz\t%3, 2f\n"
			     "\twsbh\t%0, %1\n"
			     "\trotri\t%0, %1, 16\n"
			     "2:\n"
			     "\tsmw.bi\t%0, [%2], %0, 0\n":"=r"(पंचांगp):"0"(पंचांगp),
			     "r"(loc), "r"(swap)
	    );
पूर्ण

अटल अंतरभूत पूर्णांक exceed_limit(पूर्णांक offset, अचिन्हित पूर्णांक val_mask,
			       काष्ठा module *module, Elf32_Rela * rel,
			       अचिन्हित पूर्णांक relindex, अचिन्हित पूर्णांक reloc_order)
अणु
	पूर्णांक असल_off = offset < 0 ? ~offset : offset;

	अगर (असल_off & (~val_mask)) अणु
		pr_err("\n%s: relocation type %d out of range.\n"
		       "please rebuild the kernel module with gcc option \"-Wa,-mno-small-text\".\n",
		       module->name, ELF32_R_TYPE(rel->r_info));
		pr_err("section %d reloc %d offset 0x%x relative 0x%x.\n",
		       relindex, reloc_order, rel->r_offset, offset);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

#अगर_घोषित __NDS32_EL__
#घोषणा NEED_SWAP 1
#अन्यथा
#घोषणा NEED_SWAP 0
#पूर्ण_अगर

पूर्णांक
apply_relocate_add(Elf32_Shdr * sechdrs, स्थिर अक्षर *strtab,
		   अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक relindex,
		   काष्ठा module *module)
अणु
	Elf32_Shdr *symsec = sechdrs + symindex;
	Elf32_Shdr *rअन्यथाc = sechdrs + relindex;
	Elf32_Shdr *dstsec = sechdrs + rअन्यथाc->sh_info;
	Elf32_Rela *rel = (व्योम *)rअन्यथाc->sh_addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < rअन्यथाc->sh_size / माप(Elf32_Rela); i++, rel++) अणु
		Elf32_Addr *loc;
		Elf32_Sym *sym;
		Elf32_Addr v;
		s32 offset;

		offset = ELF32_R_SYM(rel->r_info);
		अगर (offset < 0
		    || offset > (symsec->sh_size / माप(Elf32_Sym))) अणु
			pr_err("%s: bad relocation\n", module->name);
			pr_err("section %d reloc %d\n", relindex, i);
			वापस -ENOEXEC;
		पूर्ण

		sym = ((Elf32_Sym *) symsec->sh_addr) + offset;

		अगर (rel->r_offset < 0
		    || rel->r_offset > dstsec->sh_size - माप(u16)) अणु
			pr_err("%s: out of bounds relocation\n", module->name);
			pr_err("section %d reloc %d offset 0x%0x size %d\n",
			       relindex, i, rel->r_offset, dstsec->sh_size);
			वापस -ENOEXEC;
		पूर्ण

		loc = (Elf32_Addr *) (dstsec->sh_addr + rel->r_offset);
		v = sym->st_value + rel->r_addend;

		चयन (ELF32_R_TYPE(rel->r_info)) अणु
		हाल R_NDS32_NONE:
		हाल R_NDS32_INSN16:
		हाल R_NDS32_LABEL:
		हाल R_NDS32_LONGCALL1:
		हाल R_NDS32_LONGCALL2:
		हाल R_NDS32_LONGCALL3:
		हाल R_NDS32_LONGCALL4:
		हाल R_NDS32_LONGJUMP1:
		हाल R_NDS32_LONGJUMP2:
		हाल R_NDS32_LONGJUMP3:
		हाल R_NDS32_9_FIXED_RELA:
		हाल R_NDS32_15_FIXED_RELA:
		हाल R_NDS32_17_FIXED_RELA:
		हाल R_NDS32_25_FIXED_RELA:
		हाल R_NDS32_LOADSTORE:
		हाल R_NDS32_DWARF2_OP1_RELA:
		हाल R_NDS32_DWARF2_OP2_RELA:
		हाल R_NDS32_DWARF2_LEB_RELA:
		हाल R_NDS32_RELA_NOP_MIX ... R_NDS32_RELA_NOP_MAX:
			अवरोध;

		हाल R_NDS32_32_RELA:
			करो_reloc32(v, loc, 0xffffffff, 0, 0, 0, 0);
			अवरोध;

		हाल R_NDS32_HI20_RELA:
			करो_reloc32(v, loc, 0xfffff000, 12, 0xfff00000, 0,
				   NEED_SWAP);
			अवरोध;

		हाल R_NDS32_LO12S3_RELA:
			करो_reloc32(v, loc, 0x00000fff, 3, 0xfffff000, 0,
				   NEED_SWAP);
			अवरोध;

		हाल R_NDS32_LO12S2_RELA:
			करो_reloc32(v, loc, 0x00000fff, 2, 0xfffff000, 0,
				   NEED_SWAP);
			अवरोध;

		हाल R_NDS32_LO12S1_RELA:
			करो_reloc32(v, loc, 0x00000fff, 1, 0xfffff000, 0,
				   NEED_SWAP);
			अवरोध;

		हाल R_NDS32_LO12S0_RELA:
		हाल R_NDS32_LO12S0_ORI_RELA:
			करो_reloc32(v, loc, 0x00000fff, 0, 0xfffff000, 0,
				   NEED_SWAP);
			अवरोध;

		हाल R_NDS32_9_PCREL_RELA:
			अगर (exceed_limit
			    ((v - (Elf32_Addr) loc), 0x000000ff, module, rel,
			     relindex, i))
				वापस -ENOEXEC;
			करो_reloc16(v - (Elf32_Addr) loc, loc, 0x000001ff, 1,
				   0xffffff00, 0, NEED_SWAP);
			अवरोध;

		हाल R_NDS32_15_PCREL_RELA:
			अगर (exceed_limit
			    ((v - (Elf32_Addr) loc), 0x00003fff, module, rel,
			     relindex, i))
				वापस -ENOEXEC;
			करो_reloc32(v - (Elf32_Addr) loc, loc, 0x00007fff, 1,
				   0xffffc000, 0, NEED_SWAP);
			अवरोध;

		हाल R_NDS32_17_PCREL_RELA:
			अगर (exceed_limit
			    ((v - (Elf32_Addr) loc), 0x0000ffff, module, rel,
			     relindex, i))
				वापस -ENOEXEC;
			करो_reloc32(v - (Elf32_Addr) loc, loc, 0x0001ffff, 1,
				   0xffff0000, 0, NEED_SWAP);
			अवरोध;

		हाल R_NDS32_25_PCREL_RELA:
			अगर (exceed_limit
			    ((v - (Elf32_Addr) loc), 0x00ffffff, module, rel,
			     relindex, i))
				वापस -ENOEXEC;
			करो_reloc32(v - (Elf32_Addr) loc, loc, 0x01ffffff, 1,
				   0xff000000, 0, NEED_SWAP);
			अवरोध;
		हाल R_NDS32_WORD_9_PCREL_RELA:
			अगर (exceed_limit
			    ((v - (Elf32_Addr) loc), 0x000000ff, module, rel,
			     relindex, i))
				वापस -ENOEXEC;
			करो_reloc32(v - (Elf32_Addr) loc, loc, 0x000001ff, 1,
				   0xffffff00, 0, NEED_SWAP);
			अवरोध;

		हाल R_NDS32_SDA15S3_RELA:
		हाल R_NDS32_SDA15S2_RELA:
		हाल R_NDS32_SDA15S1_RELA:
		हाल R_NDS32_SDA15S0_RELA:
			pr_err("%s: unsupported relocation type %d.\n",
			       module->name, ELF32_R_TYPE(rel->r_info));
			pr_err
			    ("Small data section access doesn't work in the kernel space; "
			     "please rebuild the kernel module with gcc option -mcmodel=large.\n");
			pr_err("section %d reloc %d offset 0x%x size %d\n",
			       relindex, i, rel->r_offset, dstsec->sh_size);
			अवरोध;

		शेष:
			pr_err("%s: unsupported relocation type %d.\n",
			       module->name, ELF32_R_TYPE(rel->r_info));
			pr_err("section %d reloc %d offset 0x%x size %d\n",
			       relindex, i, rel->r_offset, dstsec->sh_size);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
module_finalize(स्थिर Elf32_Ehdr * hdr, स्थिर Elf_Shdr * sechdrs,
		काष्ठा module *module)
अणु
	वापस 0;
पूर्ण

व्योम module_arch_cleanup(काष्ठा module *mod)
अणु
पूर्ण
