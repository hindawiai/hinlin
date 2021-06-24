<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Kernel module help क्रम s390.
 *
 *  S390 version
 *    Copyright IBM Corp. 2002, 2003
 *    Author(s): Arnd Bergmann (arndb@de.ibm.com)
 *		 Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  based on i386 version
 *    Copyright (C) 2001 Rusty Russell.
 */
#समावेश <linux/module.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kasan.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/bug.h>
#समावेश <linux/memory.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/facility.h>

#अगर 0
#घोषणा DEBUGP prपूर्णांकk
#अन्यथा
#घोषणा DEBUGP(fmt , ...)
#पूर्ण_अगर

#घोषणा PLT_ENTRY_SIZE 20

व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	व्योम *p;

	अगर (PAGE_ALIGN(size) > MODULES_LEN)
		वापस शून्य;
	p = __vदो_स्मृति_node_range(size, MODULE_ALIGN, MODULES_VADDR, MODULES_END,
				 GFP_KERNEL, PAGE_KERNEL_EXEC, 0, NUMA_NO_NODE,
				 __builtin_वापस_address(0));
	अगर (p && (kasan_module_alloc(p, size) < 0)) अणु
		vमुक्त(p);
		वापस शून्य;
	पूर्ण
	वापस p;
पूर्ण

व्योम module_arch_मुक्तing_init(काष्ठा module *mod)
अणु
	अगर (is_livepatch_module(mod) &&
	    mod->state == MODULE_STATE_LIVE)
		वापस;

	vमुक्त(mod->arch.syminfo);
	mod->arch.syminfo = शून्य;
पूर्ण

अटल व्योम check_rela(Elf_Rela *rela, काष्ठा module *me)
अणु
	काष्ठा mod_arch_syminfo *info;

	info = me->arch.syminfo + ELF_R_SYM (rela->r_info);
	चयन (ELF_R_TYPE (rela->r_info)) अणु
	हाल R_390_GOT12:	/* 12 bit GOT offset.  */
	हाल R_390_GOT16:	/* 16 bit GOT offset.  */
	हाल R_390_GOT20:	/* 20 bit GOT offset.  */
	हाल R_390_GOT32:	/* 32 bit GOT offset.  */
	हाल R_390_GOT64:	/* 64 bit GOT offset.  */
	हाल R_390_GOTENT:	/* 32 bit PC rel. to GOT entry shअगरted by 1. */
	हाल R_390_GOTPLT12:	/* 12 bit offset to jump slot.	*/
	हाल R_390_GOTPLT16:	/* 16 bit offset to jump slot.  */
	हाल R_390_GOTPLT20:	/* 20 bit offset to jump slot.  */
	हाल R_390_GOTPLT32:	/* 32 bit offset to jump slot.  */
	हाल R_390_GOTPLT64:	/* 64 bit offset to jump slot.	*/
	हाल R_390_GOTPLTENT:	/* 32 bit rel. offset to jump slot >> 1. */
		अगर (info->got_offset == -1UL) अणु
			info->got_offset = me->arch.got_size;
			me->arch.got_size += माप(व्योम*);
		पूर्ण
		अवरोध;
	हाल R_390_PLT16DBL:	/* 16 bit PC rel. PLT shअगरted by 1.  */
	हाल R_390_PLT32DBL:	/* 32 bit PC rel. PLT shअगरted by 1.  */
	हाल R_390_PLT32:	/* 32 bit PC relative PLT address.  */
	हाल R_390_PLT64:	/* 64 bit PC relative PLT address.  */
	हाल R_390_PLTOFF16:	/* 16 bit offset from GOT to PLT. */
	हाल R_390_PLTOFF32:	/* 32 bit offset from GOT to PLT. */
	हाल R_390_PLTOFF64:	/* 16 bit offset from GOT to PLT. */
		अगर (info->plt_offset == -1UL) अणु
			info->plt_offset = me->arch.plt_size;
			me->arch.plt_size += PLT_ENTRY_SIZE;
		पूर्ण
		अवरोध;
	हाल R_390_COPY:
	हाल R_390_GLOB_DAT:
	हाल R_390_JMP_SLOT:
	हाल R_390_RELATIVE:
		/* Only needed अगर we want to support loading of 
		   modules linked with -shared. */
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Account क्रम GOT and PLT relocations. We can't add sections क्रम
 * got and plt but we can increase the core module size.
 */
पूर्णांक module_frob_arch_sections(Elf_Ehdr *hdr, Elf_Shdr *sechdrs,
			      अक्षर *secstrings, काष्ठा module *me)
अणु
	Elf_Shdr *symtab;
	Elf_Sym *symbols;
	Elf_Rela *rela;
	अक्षर *strings;
	पूर्णांक nrela, i, j;

	/* Find symbol table and string table. */
	symtab = शून्य;
	क्रम (i = 0; i < hdr->e_shnum; i++)
		चयन (sechdrs[i].sh_type) अणु
		हाल SHT_SYMTAB:
			symtab = sechdrs + i;
			अवरोध;
		पूर्ण
	अगर (!symtab) अणु
		prपूर्णांकk(KERN_ERR "module %s: no symbol table\n", me->name);
		वापस -ENOEXEC;
	पूर्ण

	/* Allocate one syminfo काष्ठाure per symbol. */
	me->arch.nsyms = symtab->sh_size / माप(Elf_Sym);
	me->arch.syminfo = vदो_स्मृति(array_size(माप(काष्ठा mod_arch_syminfo),
					      me->arch.nsyms));
	अगर (!me->arch.syminfo)
		वापस -ENOMEM;
	symbols = (व्योम *) hdr + symtab->sh_offset;
	strings = (व्योम *) hdr + sechdrs[symtab->sh_link].sh_offset;
	क्रम (i = 0; i < me->arch.nsyms; i++) अणु
		अगर (symbols[i].st_shndx == SHN_UNDEF &&
		    म_भेद(strings + symbols[i].st_name,
			   "_GLOBAL_OFFSET_TABLE_") == 0)
			/* "Define" it as असलolute. */
			symbols[i].st_shndx = SHN_ABS;
		me->arch.syminfo[i].got_offset = -1UL;
		me->arch.syminfo[i].plt_offset = -1UL;
		me->arch.syminfo[i].got_initialized = 0;
		me->arch.syminfo[i].plt_initialized = 0;
	पूर्ण

	/* Search क्रम got/plt relocations. */
	me->arch.got_size = me->arch.plt_size = 0;
	क्रम (i = 0; i < hdr->e_shnum; i++) अणु
		अगर (sechdrs[i].sh_type != SHT_RELA)
			जारी;
		nrela = sechdrs[i].sh_size / माप(Elf_Rela);
		rela = (व्योम *) hdr + sechdrs[i].sh_offset;
		क्रम (j = 0; j < nrela; j++)
			check_rela(rela + j, me);
	पूर्ण

	/* Increase core size by size of got & plt and set start
	   offsets क्रम got and plt. */
	me->core_layout.size = ALIGN(me->core_layout.size, 4);
	me->arch.got_offset = me->core_layout.size;
	me->core_layout.size += me->arch.got_size;
	me->arch.plt_offset = me->core_layout.size;
	अगर (me->arch.plt_size) अणु
		अगर (IS_ENABLED(CONFIG_EXPOLINE) && !nospec_disable)
			me->arch.plt_size += PLT_ENTRY_SIZE;
		me->core_layout.size += me->arch.plt_size;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक apply_rela_bits(Elf_Addr loc, Elf_Addr val,
			   पूर्णांक sign, पूर्णांक bits, पूर्णांक shअगरt,
			   व्योम *(*ग_लिखो)(व्योम *dest, स्थिर व्योम *src, माप_प्रकार len))
अणु
	अचिन्हित दीर्घ umax;
	दीर्घ min, max;
	व्योम *dest = (व्योम *)loc;

	अगर (val & ((1UL << shअगरt) - 1))
		वापस -ENOEXEC;
	अगर (sign) अणु
		val = (Elf_Addr)(((दीर्घ) val) >> shअगरt);
		min = -(1L << (bits - 1));
		max = (1L << (bits - 1)) - 1;
		अगर ((दीर्घ) val < min || (दीर्घ) val > max)
			वापस -ENOEXEC;
	पूर्ण अन्यथा अणु
		val >>= shअगरt;
		umax = ((1UL << (bits - 1)) << 1) - 1;
		अगर ((अचिन्हित दीर्घ) val > umax)
			वापस -ENOEXEC;
	पूर्ण

	अगर (bits == 8) अणु
		अचिन्हित अक्षर पंचांगp = val;
		ग_लिखो(dest, &पंचांगp, 1);
	पूर्ण अन्यथा अगर (bits == 12) अणु
		अचिन्हित लघु पंचांगp = (val & 0xfff) |
			(*(अचिन्हित लघु *) loc & 0xf000);
		ग_लिखो(dest, &पंचांगp, 2);
	पूर्ण अन्यथा अगर (bits == 16) अणु
		अचिन्हित लघु पंचांगp = val;
		ग_लिखो(dest, &पंचांगp, 2);
	पूर्ण अन्यथा अगर (bits == 20) अणु
		अचिन्हित पूर्णांक पंचांगp = (val & 0xfff) << 16 |
			(val & 0xff000) >> 4 | (*(अचिन्हित पूर्णांक *) loc & 0xf00000ff);
		ग_लिखो(dest, &पंचांगp, 4);
	पूर्ण अन्यथा अगर (bits == 32) अणु
		अचिन्हित पूर्णांक पंचांगp = val;
		ग_लिखो(dest, &पंचांगp, 4);
	पूर्ण अन्यथा अगर (bits == 64) अणु
		अचिन्हित दीर्घ पंचांगp = val;
		ग_लिखो(dest, &पंचांगp, 8);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक apply_rela(Elf_Rela *rela, Elf_Addr base, Elf_Sym *symtab,
		      स्थिर अक्षर *strtab, काष्ठा module *me,
		      व्योम *(*ग_लिखो)(व्योम *dest, स्थिर व्योम *src, माप_प्रकार len))
अणु
	काष्ठा mod_arch_syminfo *info;
	Elf_Addr loc, val;
	पूर्णांक r_type, r_sym;
	पूर्णांक rc = -ENOEXEC;

	/* This is where to make the change */
	loc = base + rela->r_offset;
	/* This is the symbol it is referring to.  Note that all
	   undefined symbols have been resolved.  */
	r_sym = ELF_R_SYM(rela->r_info);
	r_type = ELF_R_TYPE(rela->r_info);
	info = me->arch.syminfo + r_sym;
	val = symtab[r_sym].st_value;

	चयन (r_type) अणु
	हाल R_390_NONE:	/* No relocation.  */
		rc = 0;
		अवरोध;
	हाल R_390_8:		/* Direct 8 bit.   */
	हाल R_390_12:		/* Direct 12 bit.  */
	हाल R_390_16:		/* Direct 16 bit.  */
	हाल R_390_20:		/* Direct 20 bit.  */
	हाल R_390_32:		/* Direct 32 bit.  */
	हाल R_390_64:		/* Direct 64 bit.  */
		val += rela->r_addend;
		अगर (r_type == R_390_8)
			rc = apply_rela_bits(loc, val, 0, 8, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_12)
			rc = apply_rela_bits(loc, val, 0, 12, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_16)
			rc = apply_rela_bits(loc, val, 0, 16, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_20)
			rc = apply_rela_bits(loc, val, 1, 20, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_32)
			rc = apply_rela_bits(loc, val, 0, 32, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_64)
			rc = apply_rela_bits(loc, val, 0, 64, 0, ग_लिखो);
		अवरोध;
	हाल R_390_PC16:	/* PC relative 16 bit.  */
	हाल R_390_PC16DBL:	/* PC relative 16 bit shअगरted by 1.  */
	हाल R_390_PC32DBL:	/* PC relative 32 bit shअगरted by 1.  */
	हाल R_390_PC32:	/* PC relative 32 bit.  */
	हाल R_390_PC64:	/* PC relative 64 bit.	*/
		val += rela->r_addend - loc;
		अगर (r_type == R_390_PC16)
			rc = apply_rela_bits(loc, val, 1, 16, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_PC16DBL)
			rc = apply_rela_bits(loc, val, 1, 16, 1, ग_लिखो);
		अन्यथा अगर (r_type == R_390_PC32DBL)
			rc = apply_rela_bits(loc, val, 1, 32, 1, ग_लिखो);
		अन्यथा अगर (r_type == R_390_PC32)
			rc = apply_rela_bits(loc, val, 1, 32, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_PC64)
			rc = apply_rela_bits(loc, val, 1, 64, 0, ग_लिखो);
		अवरोध;
	हाल R_390_GOT12:	/* 12 bit GOT offset.  */
	हाल R_390_GOT16:	/* 16 bit GOT offset.  */
	हाल R_390_GOT20:	/* 20 bit GOT offset.  */
	हाल R_390_GOT32:	/* 32 bit GOT offset.  */
	हाल R_390_GOT64:	/* 64 bit GOT offset.  */
	हाल R_390_GOTENT:	/* 32 bit PC rel. to GOT entry shअगरted by 1. */
	हाल R_390_GOTPLT12:	/* 12 bit offset to jump slot.	*/
	हाल R_390_GOTPLT20:	/* 20 bit offset to jump slot.  */
	हाल R_390_GOTPLT16:	/* 16 bit offset to jump slot.  */
	हाल R_390_GOTPLT32:	/* 32 bit offset to jump slot.  */
	हाल R_390_GOTPLT64:	/* 64 bit offset to jump slot.	*/
	हाल R_390_GOTPLTENT:	/* 32 bit rel. offset to jump slot >> 1. */
		अगर (info->got_initialized == 0) अणु
			Elf_Addr *gotent = me->core_layout.base +
					   me->arch.got_offset +
					   info->got_offset;

			ग_लिखो(gotent, &val, माप(*gotent));
			info->got_initialized = 1;
		पूर्ण
		val = info->got_offset + rela->r_addend;
		अगर (r_type == R_390_GOT12 ||
		    r_type == R_390_GOTPLT12)
			rc = apply_rela_bits(loc, val, 0, 12, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_GOT16 ||
			 r_type == R_390_GOTPLT16)
			rc = apply_rela_bits(loc, val, 0, 16, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_GOT20 ||
			 r_type == R_390_GOTPLT20)
			rc = apply_rela_bits(loc, val, 1, 20, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_GOT32 ||
			 r_type == R_390_GOTPLT32)
			rc = apply_rela_bits(loc, val, 0, 32, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_GOT64 ||
			 r_type == R_390_GOTPLT64)
			rc = apply_rela_bits(loc, val, 0, 64, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_GOTENT ||
			 r_type == R_390_GOTPLTENT) अणु
			val += (Elf_Addr) me->core_layout.base - loc;
			rc = apply_rela_bits(loc, val, 1, 32, 1, ग_लिखो);
		पूर्ण
		अवरोध;
	हाल R_390_PLT16DBL:	/* 16 bit PC rel. PLT shअगरted by 1.  */
	हाल R_390_PLT32DBL:	/* 32 bit PC rel. PLT shअगरted by 1.  */
	हाल R_390_PLT32:	/* 32 bit PC relative PLT address.  */
	हाल R_390_PLT64:	/* 64 bit PC relative PLT address.  */
	हाल R_390_PLTOFF16:	/* 16 bit offset from GOT to PLT. */
	हाल R_390_PLTOFF32:	/* 32 bit offset from GOT to PLT. */
	हाल R_390_PLTOFF64:	/* 16 bit offset from GOT to PLT. */
		अगर (info->plt_initialized == 0) अणु
			अचिन्हित पूर्णांक insn[5];
			अचिन्हित पूर्णांक *ip = me->core_layout.base +
					   me->arch.plt_offset +
					   info->plt_offset;

			insn[0] = 0x0d10e310;	/* basr 1,0  */
			insn[1] = 0x100a0004;	/* lg	1,10(1) */
			अगर (IS_ENABLED(CONFIG_EXPOLINE) && !nospec_disable) अणु
				अचिन्हित पूर्णांक *ij;
				ij = me->core_layout.base +
					me->arch.plt_offset +
					me->arch.plt_size - PLT_ENTRY_SIZE;
				insn[2] = 0xa7f40000 +	/* j __jump_r1 */
					(अचिन्हित पूर्णांक)(u16)
					(((अचिन्हित दीर्घ) ij - 8 -
					  (अचिन्हित दीर्घ) ip) / 2);
			पूर्ण अन्यथा अणु
				insn[2] = 0x07f10000;	/* br %r1 */
			पूर्ण
			insn[3] = (अचिन्हित पूर्णांक) (val >> 32);
			insn[4] = (अचिन्हित पूर्णांक) val;

			ग_लिखो(ip, insn, माप(insn));
			info->plt_initialized = 1;
		पूर्ण
		अगर (r_type == R_390_PLTOFF16 ||
		    r_type == R_390_PLTOFF32 ||
		    r_type == R_390_PLTOFF64)
			val = me->arch.plt_offset - me->arch.got_offset +
				info->plt_offset + rela->r_addend;
		अन्यथा अणु
			अगर (!((r_type == R_390_PLT16DBL &&
			       val - loc + 0xffffUL < 0x1ffffeUL) ||
			      (r_type == R_390_PLT32DBL &&
			       val - loc + 0xffffffffULL < 0x1fffffffeULL)))
				val = (Elf_Addr) me->core_layout.base +
					me->arch.plt_offset +
					info->plt_offset;
			val += rela->r_addend - loc;
		पूर्ण
		अगर (r_type == R_390_PLT16DBL)
			rc = apply_rela_bits(loc, val, 1, 16, 1, ग_लिखो);
		अन्यथा अगर (r_type == R_390_PLTOFF16)
			rc = apply_rela_bits(loc, val, 0, 16, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_PLT32DBL)
			rc = apply_rela_bits(loc, val, 1, 32, 1, ग_लिखो);
		अन्यथा अगर (r_type == R_390_PLT32 ||
			 r_type == R_390_PLTOFF32)
			rc = apply_rela_bits(loc, val, 0, 32, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_PLT64 ||
			 r_type == R_390_PLTOFF64)
			rc = apply_rela_bits(loc, val, 0, 64, 0, ग_लिखो);
		अवरोध;
	हाल R_390_GOTOFF16:	/* 16 bit offset to GOT.  */
	हाल R_390_GOTOFF32:	/* 32 bit offset to GOT.  */
	हाल R_390_GOTOFF64:	/* 64 bit offset to GOT. */
		val = val + rela->r_addend -
			((Elf_Addr) me->core_layout.base + me->arch.got_offset);
		अगर (r_type == R_390_GOTOFF16)
			rc = apply_rela_bits(loc, val, 0, 16, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_GOTOFF32)
			rc = apply_rela_bits(loc, val, 0, 32, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_GOTOFF64)
			rc = apply_rela_bits(loc, val, 0, 64, 0, ग_लिखो);
		अवरोध;
	हाल R_390_GOTPC:	/* 32 bit PC relative offset to GOT. */
	हाल R_390_GOTPCDBL:	/* 32 bit PC rel. off. to GOT shअगरted by 1. */
		val = (Elf_Addr) me->core_layout.base + me->arch.got_offset +
			rela->r_addend - loc;
		अगर (r_type == R_390_GOTPC)
			rc = apply_rela_bits(loc, val, 1, 32, 0, ग_लिखो);
		अन्यथा अगर (r_type == R_390_GOTPCDBL)
			rc = apply_rela_bits(loc, val, 1, 32, 1, ग_लिखो);
		अवरोध;
	हाल R_390_COPY:
	हाल R_390_GLOB_DAT:	/* Create GOT entry.  */
	हाल R_390_JMP_SLOT:	/* Create PLT entry.  */
	हाल R_390_RELATIVE:	/* Adjust by program base.  */
		/* Only needed अगर we want to support loading of 
		   modules linked with -shared. */
		वापस -ENOEXEC;
	शेष:
		prपूर्णांकk(KERN_ERR "module %s: unknown relocation: %u\n",
		       me->name, r_type);
		वापस -ENOEXEC;
	पूर्ण
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "module %s: relocation error for symbol %s "
		       "(r_type %i, value 0x%lx)\n",
		       me->name, strtab + symtab[r_sym].st_name,
		       r_type, (अचिन्हित दीर्घ) val);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __apply_relocate_add(Elf_Shdr *sechdrs, स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me,
		       व्योम *(*ग_लिखो)(व्योम *dest, स्थिर व्योम *src, माप_प्रकार len))
अणु
	Elf_Addr base;
	Elf_Sym *symtab;
	Elf_Rela *rela;
	अचिन्हित दीर्घ i, n;
	पूर्णांक rc;

	DEBUGP("Applying relocate section %u to %u\n",
	       rअन्यथाc, sechdrs[rअन्यथाc].sh_info);
	base = sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr;
	symtab = (Elf_Sym *) sechdrs[symindex].sh_addr;
	rela = (Elf_Rela *) sechdrs[rअन्यथाc].sh_addr;
	n = sechdrs[rअन्यथाc].sh_size / माप(Elf_Rela);

	क्रम (i = 0; i < n; i++, rela++) अणु
		rc = apply_rela(rela, base, symtab, strtab, me, ग_लिखो);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक apply_relocate_add(Elf_Shdr *sechdrs, स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	bool early = me->state == MODULE_STATE_UNFORMED;
	व्योम *(*ग_लिखो)(व्योम *, स्थिर व्योम *, माप_प्रकार) = स_नकल;

	अगर (!early)
		ग_लिखो = s390_kernel_ग_लिखो;

	वापस __apply_relocate_add(sechdrs, strtab, symindex, rअन्यथाc, me,
				    ग_लिखो);
पूर्ण

पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		    स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *me)
अणु
	स्थिर Elf_Shdr *s;
	अक्षर *secstrings, *secname;
	व्योम *aseg;

	अगर (IS_ENABLED(CONFIG_EXPOLINE) &&
	    !nospec_disable && me->arch.plt_size) अणु
		अचिन्हित पूर्णांक *ij;

		ij = me->core_layout.base + me->arch.plt_offset +
			me->arch.plt_size - PLT_ENTRY_SIZE;
		अगर (test_facility(35)) अणु
			ij[0] = 0xc6000000;	/* exrl	%r0,.+10	*/
			ij[1] = 0x0005a7f4;	/* j	.		*/
			ij[2] = 0x000007f1;	/* br	%r1		*/
		पूर्ण अन्यथा अणु
			ij[0] = 0x44000000 | (अचिन्हित पूर्णांक)
				दुरत्व(काष्ठा lowcore, br_r1_trampoline);
			ij[1] = 0xa7f40000;	/* j	.		*/
		पूर्ण
	पूर्ण

	secstrings = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;
	क्रम (s = sechdrs; s < sechdrs + hdr->e_shnum; s++) अणु
		aseg = (व्योम *) s->sh_addr;
		secname = secstrings + s->sh_name;

		अगर (!म_भेद(".altinstructions", secname))
			/* patch .altinकाष्ठाions */
			apply_alternatives(aseg, aseg + s->sh_size);

		अगर (IS_ENABLED(CONFIG_EXPOLINE) &&
		    (str_has_prefix(secname, ".s390_indirect")))
			nospec_revert(aseg, aseg + s->sh_size);

		अगर (IS_ENABLED(CONFIG_EXPOLINE) &&
		    (str_has_prefix(secname, ".s390_return")))
			nospec_revert(aseg, aseg + s->sh_size);
	पूर्ण

	jump_label_apply_nops(me);
	वापस 0;
पूर्ण
