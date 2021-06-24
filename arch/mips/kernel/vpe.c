<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004, 2005 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2013 Imagination Technologies Ltd.
 *
 * VPE spport module क्रम loading a MIPS SP program पूर्णांकo VPE1. The SP
 * environment is rather simple since there are no TLBs. It needs
 * to be relocatable (or partiall linked). Initialize your stack in
 * the startup-code. The loader looks क्रम the symbol __start and sets
 * up the execution to resume from there. To load and run, simply करो
 * a cat SP 'binary' to the /dev/vpe1 device.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/elf.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/poll.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/mips_mt.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/vpe.h>

#अगर_अघोषित ARCH_SHF_SMALL
#घोषणा ARCH_SHF_SMALL 0
#पूर्ण_अगर

/* If this is set, the section beदीर्घs in the init part of the module */
#घोषणा INIT_OFFSET_MASK (1UL << (BITS_PER_LONG-1))

काष्ठा vpe_control vpecontrol = अणु
	.vpe_list_lock	= __SPIN_LOCK_UNLOCKED(vpe_list_lock),
	.vpe_list	= LIST_HEAD_INIT(vpecontrol.vpe_list),
	.tc_list_lock	= __SPIN_LOCK_UNLOCKED(tc_list_lock),
	.tc_list	= LIST_HEAD_INIT(vpecontrol.tc_list)
पूर्ण;

/* get the vpe associated with this minor */
काष्ठा vpe *get_vpe(पूर्णांक minor)
अणु
	काष्ठा vpe *res, *v;

	अगर (!cpu_has_mipsmt)
		वापस शून्य;

	res = शून्य;
	spin_lock(&vpecontrol.vpe_list_lock);
	list_क्रम_each_entry(v, &vpecontrol.vpe_list, list) अणु
		अगर (v->minor == VPE_MODULE_MINOR) अणु
			res = v;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&vpecontrol.vpe_list_lock);

	वापस res;
पूर्ण

/* get the vpe associated with this minor */
काष्ठा tc *get_tc(पूर्णांक index)
अणु
	काष्ठा tc *res, *t;

	res = शून्य;
	spin_lock(&vpecontrol.tc_list_lock);
	list_क्रम_each_entry(t, &vpecontrol.tc_list, list) अणु
		अगर (t->index == index) अणु
			res = t;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&vpecontrol.tc_list_lock);

	वापस res;
पूर्ण

/* allocate a vpe and associate it with this minor (or index) */
काष्ठा vpe *alloc_vpe(पूर्णांक minor)
अणु
	काष्ठा vpe *v;

	v = kzalloc(माप(काष्ठा vpe), GFP_KERNEL);
	अगर (v == शून्य)
		जाओ out;

	INIT_LIST_HEAD(&v->tc);
	spin_lock(&vpecontrol.vpe_list_lock);
	list_add_tail(&v->list, &vpecontrol.vpe_list);
	spin_unlock(&vpecontrol.vpe_list_lock);

	INIT_LIST_HEAD(&v->notअगरy);
	v->minor = VPE_MODULE_MINOR;

out:
	वापस v;
पूर्ण

/* allocate a tc. At startup only tc0 is running, all other can be halted. */
काष्ठा tc *alloc_tc(पूर्णांक index)
अणु
	काष्ठा tc *tc;

	tc = kzalloc(माप(काष्ठा tc), GFP_KERNEL);
	अगर (tc == शून्य)
		जाओ out;

	INIT_LIST_HEAD(&tc->tc);
	tc->index = index;

	spin_lock(&vpecontrol.tc_list_lock);
	list_add_tail(&tc->list, &vpecontrol.tc_list);
	spin_unlock(&vpecontrol.tc_list_lock);

out:
	वापस tc;
पूर्ण

/* clean up and मुक्त everything */
व्योम release_vpe(काष्ठा vpe *v)
अणु
	list_del(&v->list);
	अगर (v->load_addr)
		release_progmem(v->load_addr);
	kमुक्त(v);
पूर्ण

/* Find some VPE program space */
व्योम *alloc_progmem(अचिन्हित दीर्घ len)
अणु
	व्योम *addr;

#अगर_घोषित CONFIG_MIPS_VPE_LOADER_TOM
	/*
	 * This means you must tell Linux to use less memory than you
	 * physically have, क्रम example by passing a mem= boot argument.
	 */
	addr = pfn_to_kaddr(max_low_pfn);
	स_रखो(addr, 0, len);
#अन्यथा
	/* simple grab some mem क्रम now */
	addr = kzalloc(len, GFP_KERNEL);
#पूर्ण_अगर

	वापस addr;
पूर्ण

व्योम release_progmem(व्योम *ptr)
अणु
#अगर_अघोषित CONFIG_MIPS_VPE_LOADER_TOM
	kमुक्त(ptr);
#पूर्ण_अगर
पूर्ण

/* Update size with this section: वापस offset. */
अटल दीर्घ get_offset(अचिन्हित दीर्घ *size, Elf_Shdr *sechdr)
अणु
	दीर्घ ret;

	ret = ALIGN(*size, sechdr->sh_addralign ? : 1);
	*size = ret + sechdr->sh_size;
	वापस ret;
पूर्ण

/* Lay out the SHF_ALLOC sections in a way not dissimilar to how ld
   might -- code, पढ़ो-only data, पढ़ो-ग_लिखो data, small data.	Tally
   sizes, and place the offsets पूर्णांकo sh_entsize fields: high bit means it
   beदीर्घs in init. */
अटल व्योम layout_sections(काष्ठा module *mod, स्थिर Elf_Ehdr *hdr,
			    Elf_Shdr *sechdrs, स्थिर अक्षर *secstrings)
अणु
	अटल अचिन्हित दीर्घ स्थिर masks[][2] = अणु
		/* NOTE: all executable code must be the first section
		 * in this array; otherwise modअगरy the text_size
		 * finder in the two loops below */
		अणुSHF_EXECINSTR | SHF_ALLOC, ARCH_SHF_SMALLपूर्ण,
		अणुSHF_ALLOC, SHF_WRITE | ARCH_SHF_SMALLपूर्ण,
		अणुSHF_WRITE | SHF_ALLOC, ARCH_SHF_SMALLपूर्ण,
		अणुARCH_SHF_SMALL | SHF_ALLOC, 0पूर्ण
	पूर्ण;
	अचिन्हित पूर्णांक m, i;

	क्रम (i = 0; i < hdr->e_shnum; i++)
		sechdrs[i].sh_entsize = ~0UL;

	क्रम (m = 0; m < ARRAY_SIZE(masks); ++m) अणु
		क्रम (i = 0; i < hdr->e_shnum; ++i) अणु
			Elf_Shdr *s = &sechdrs[i];

			अगर ((s->sh_flags & masks[m][0]) != masks[m][0]
			    || (s->sh_flags & masks[m][1])
			    || s->sh_entsize != ~0UL)
				जारी;
			s->sh_entsize =
				get_offset((अचिन्हित दीर्घ *)&mod->core_layout.size, s);
		पूर्ण

		अगर (m == 0)
			mod->core_layout.text_size = mod->core_layout.size;

	पूर्ण
पूर्ण

/* from module-elf32.c, but subverted a little */

काष्ठा mips_hi16 अणु
	काष्ठा mips_hi16 *next;
	Elf32_Addr *addr;
	Elf32_Addr value;
पूर्ण;

अटल काष्ठा mips_hi16 *mips_hi16_list;
अटल अचिन्हित पूर्णांक gp_offs, gp_addr;

अटल पूर्णांक apply_r_mips_none(काष्ठा module *me, uपूर्णांक32_t *location,
			     Elf32_Addr v)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_gprel16(काष्ठा module *me, uपूर्णांक32_t *location,
				Elf32_Addr v)
अणु
	पूर्णांक rel;

	अगर (!(*location & 0xffff)) अणु
		rel = (पूर्णांक)v - gp_addr;
	पूर्ण अन्यथा अणु
		/* .sbss + gp(relative) + offset */
		/* kludge! */
		rel =  (पूर्णांक)(लघु)((पूर्णांक)v + gp_offs +
				    (पूर्णांक)(लघु)(*location & 0xffff) - gp_addr);
	पूर्ण

	अगर ((rel > 32768) || (rel < -32768)) अणु
		pr_debug("VPE loader: apply_r_mips_gprel16: relative address 0x%x out of range of gp register\n",
			 rel);
		वापस -ENOEXEC;
	पूर्ण

	*location = (*location & 0xffff0000) | (rel & 0xffff);

	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_pc16(काष्ठा module *me, uपूर्णांक32_t *location,
			     Elf32_Addr v)
अणु
	पूर्णांक rel;
	rel = (((अचिन्हित पूर्णांक)v - (अचिन्हित पूर्णांक)location));
	rel >>= 2; /* because the offset is in _inकाष्ठाions_ not bytes. */
	rel -= 1;  /* and one inकाष्ठाion less due to the branch delay slot. */

	अगर ((rel > 32768) || (rel < -32768)) अणु
		pr_debug("VPE loader: apply_r_mips_pc16: relative address out of range 0x%x\n",
			 rel);
		वापस -ENOEXEC;
	पूर्ण

	*location = (*location & 0xffff0000) | (rel & 0xffff);

	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_32(काष्ठा module *me, uपूर्णांक32_t *location,
			   Elf32_Addr v)
अणु
	*location += v;

	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_26(काष्ठा module *me, uपूर्णांक32_t *location,
			   Elf32_Addr v)
अणु
	अगर (v % 4) अणु
		pr_debug("VPE loader: apply_r_mips_26: unaligned relocation\n");
		वापस -ENOEXEC;
	पूर्ण

/*
 * Not desperately convinced this is a good check of an overflow condition
 * anyway. But it माला_लो in the way of handling undefined weak symbols which
 * we want to set to zero.
 * अगर ((v & 0xf0000000) != (((अचिन्हित दीर्घ)location + 4) & 0xf0000000)) अणु
 * prपूर्णांकk(KERN_ERR
 * "module %s: relocation overflow\n",
 * me->name);
 * वापस -ENOEXEC;
 * पूर्ण
 */

	*location = (*location & ~0x03ffffff) |
		((*location + (v >> 2)) & 0x03ffffff);
	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_hi16(काष्ठा module *me, uपूर्णांक32_t *location,
			     Elf32_Addr v)
अणु
	काष्ठा mips_hi16 *n;

	/*
	 * We cannot relocate this one now because we करोn't know the value of
	 * the carry we need to add.  Save the inक्रमmation, and let LO16 करो the
	 * actual relocation.
	 */
	n = kदो_स्मृति(माप(*n), GFP_KERNEL);
	अगर (!n)
		वापस -ENOMEM;

	n->addr = location;
	n->value = v;
	n->next = mips_hi16_list;
	mips_hi16_list = n;

	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_lo16(काष्ठा module *me, uपूर्णांक32_t *location,
			     Elf32_Addr v)
अणु
	अचिन्हित दीर्घ insnlo = *location;
	Elf32_Addr val, vallo;
	काष्ठा mips_hi16 *l, *next;

	/* Sign extend the addend we extract from the lo insn.	*/
	vallo = ((insnlo & 0xffff) ^ 0x8000) - 0x8000;

	अगर (mips_hi16_list != शून्य) अणु

		l = mips_hi16_list;
		जबतक (l != शून्य) अणु
			अचिन्हित दीर्घ insn;

			/*
			 * The value क्रम the HI16 had best be the same.
			 */
			अगर (v != l->value) अणु
				pr_debug("VPE loader: apply_r_mips_lo16/hi16: inconsistent value information\n");
				जाओ out_मुक्त;
			पूर्ण

			/*
			 * Do the HI16 relocation.  Note that we actually करोn't
			 * need to know anything about the LO16 itself, except
			 * where to find the low 16 bits of the addend needed
			 * by the LO16.
			 */
			insn = *l->addr;
			val = ((insn & 0xffff) << 16) + vallo;
			val += v;

			/*
			 * Account क्रम the sign extension that will happen in
			 * the low bits.
			 */
			val = ((val >> 16) + ((val & 0x8000) != 0)) & 0xffff;

			insn = (insn & ~0xffff) | val;
			*l->addr = insn;

			next = l->next;
			kमुक्त(l);
			l = next;
		पूर्ण

		mips_hi16_list = शून्य;
	पूर्ण

	/*
	 * Ok, we're करोne with the HI16 relocs.	 Now deal with the LO16.
	 */
	val = v + vallo;
	insnlo = (insnlo & ~0xffff) | (val & 0xffff);
	*location = insnlo;

	वापस 0;

out_मुक्त:
	जबतक (l != शून्य) अणु
		next = l->next;
		kमुक्त(l);
		l = next;
	पूर्ण
	mips_hi16_list = शून्य;

	वापस -ENOEXEC;
पूर्ण

अटल पूर्णांक (*reloc_handlers[]) (काष्ठा module *me, uपूर्णांक32_t *location,
				Elf32_Addr v) = अणु
	[R_MIPS_NONE]	= apply_r_mips_none,
	[R_MIPS_32]	= apply_r_mips_32,
	[R_MIPS_26]	= apply_r_mips_26,
	[R_MIPS_HI16]	= apply_r_mips_hi16,
	[R_MIPS_LO16]	= apply_r_mips_lo16,
	[R_MIPS_GPREL16] = apply_r_mips_gprel16,
	[R_MIPS_PC16] = apply_r_mips_pc16
पूर्ण;

अटल अक्षर *rstrs[] = अणु
	[R_MIPS_NONE]	= "MIPS_NONE",
	[R_MIPS_32]	= "MIPS_32",
	[R_MIPS_26]	= "MIPS_26",
	[R_MIPS_HI16]	= "MIPS_HI16",
	[R_MIPS_LO16]	= "MIPS_LO16",
	[R_MIPS_GPREL16] = "MIPS_GPREL16",
	[R_MIPS_PC16] = "MIPS_PC16"
पूर्ण;

अटल पूर्णांक apply_relocations(Elf32_Shdr *sechdrs,
		      स्थिर अक्षर *strtab,
		      अचिन्हित पूर्णांक symindex,
		      अचिन्हित पूर्णांक rअन्यथाc,
		      काष्ठा module *me)
अणु
	Elf32_Rel *rel = (व्योम *) sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym;
	uपूर्णांक32_t *location;
	अचिन्हित पूर्णांक i;
	Elf32_Addr v;
	पूर्णांक res;

	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		Elf32_Word r_info = rel[i].r_info;

		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rel[i].r_offset;
		/* This is the symbol it is referring to */
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(r_info);

		अगर (!sym->st_value) अणु
			pr_debug("%s: undefined weak symbol %s\n",
				 me->name, strtab + sym->st_name);
			/* just prपूर्णांक the warning, करोnt barf */
		पूर्ण

		v = sym->st_value;

		res = reloc_handlers[ELF32_R_TYPE(r_info)](me, location, v);
		अगर (res) अणु
			अक्षर *r = rstrs[ELF32_R_TYPE(r_info)];
			pr_warn("VPE loader: .text+0x%x relocation type %s for symbol \"%s\" failed\n",
				rel[i].r_offset, r ? r : "UNKNOWN",
				strtab + sym->st_name);
			वापस res;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम save_gp_address(अचिन्हित पूर्णांक secbase, अचिन्हित पूर्णांक rel)
अणु
	gp_addr = secbase + rel;
	gp_offs = gp_addr - (secbase & 0xffff0000);
पूर्ण
/* end module-elf32.c */

/* Change all symbols so that sh_value encodes the poपूर्णांकer directly. */
अटल व्योम simplअगरy_symbols(Elf_Shdr *sechdrs,
			    अचिन्हित पूर्णांक symindex,
			    स्थिर अक्षर *strtab,
			    स्थिर अक्षर *secstrings,
			    अचिन्हित पूर्णांक nsecs, काष्ठा module *mod)
अणु
	Elf_Sym *sym = (व्योम *)sechdrs[symindex].sh_addr;
	अचिन्हित दीर्घ secbase, bssbase = 0;
	अचिन्हित पूर्णांक i, n = sechdrs[symindex].sh_size / माप(Elf_Sym);
	पूर्णांक size;

	/* find the .bss section क्रम COMMON symbols */
	क्रम (i = 0; i < nsecs; i++) अणु
		अगर (म_भेदन(secstrings + sechdrs[i].sh_name, ".bss", 4) == 0) अणु
			bssbase = sechdrs[i].sh_addr;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 1; i < n; i++) अणु
		चयन (sym[i].st_shndx) अणु
		हाल SHN_COMMON:
			/* Allocate space क्रम the symbol in the .bss section.
			   st_value is currently size.
			   We want it to have the address of the symbol. */

			size = sym[i].st_value;
			sym[i].st_value = bssbase;

			bssbase += size;
			अवरोध;

		हाल SHN_ABS:
			/* Don't need to करो anything */
			अवरोध;

		हाल SHN_UNDEF:
			/* ret = -ENOENT; */
			अवरोध;

		हाल SHN_MIPS_SCOMMON:
			pr_debug("simplify_symbols: ignoring SHN_MIPS_SCOMMON symbol <%s> st_shndx %d\n",
				 strtab + sym[i].st_name, sym[i].st_shndx);
			/* .sbss section */
			अवरोध;

		शेष:
			secbase = sechdrs[sym[i].st_shndx].sh_addr;

			अगर (म_भेदन(strtab + sym[i].st_name, "_gp", 3) == 0)
				save_gp_address(secbase, sym[i].st_value);

			sym[i].st_value += secbase;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित DEBUG_ELFLOADER
अटल व्योम dump_elfsymbols(Elf_Shdr *sechdrs, अचिन्हित पूर्णांक symindex,
			    स्थिर अक्षर *strtab, काष्ठा module *mod)
अणु
	Elf_Sym *sym = (व्योम *)sechdrs[symindex].sh_addr;
	अचिन्हित पूर्णांक i, n = sechdrs[symindex].sh_size / माप(Elf_Sym);

	pr_debug("dump_elfsymbols: n %d\n", n);
	क्रम (i = 1; i < n; i++) अणु
		pr_debug(" i %d name <%s> 0x%x\n", i, strtab + sym[i].st_name,
			 sym[i].st_value);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक find_vpe_symbols(काष्ठा vpe *v, Elf_Shdr *sechdrs,
				      अचिन्हित पूर्णांक symindex, स्थिर अक्षर *strtab,
				      काष्ठा module *mod)
अणु
	Elf_Sym *sym = (व्योम *)sechdrs[symindex].sh_addr;
	अचिन्हित पूर्णांक i, n = sechdrs[symindex].sh_size / माप(Elf_Sym);

	क्रम (i = 1; i < n; i++) अणु
		अगर (म_भेद(strtab + sym[i].st_name, "__start") == 0)
			v->__start = sym[i].st_value;

		अगर (म_भेद(strtab + sym[i].st_name, "vpe_shared") == 0)
			v->shared_ptr = (व्योम *)sym[i].st_value;
	पूर्ण

	अगर ((v->__start == 0) || (v->shared_ptr == शून्य))
		वापस -1;

	वापस 0;
पूर्ण

/*
 * Allocates a VPE with some program code space(the load address), copies the
 * contents of the program (p)buffer perक्रमming relocatations/etc, मुक्त's it
 * when finished.
 */
अटल पूर्णांक vpe_elfload(काष्ठा vpe *v)
अणु
	Elf_Ehdr *hdr;
	Elf_Shdr *sechdrs;
	दीर्घ err = 0;
	अक्षर *secstrings, *strtab = शून्य;
	अचिन्हित पूर्णांक len, i, symindex = 0, strindex = 0, relocate = 0;
	काष्ठा module mod; /* so we can re-use the relocations code */

	स_रखो(&mod, 0, माप(काष्ठा module));
	म_नकल(mod.name, "VPE loader");

	hdr = (Elf_Ehdr *) v->pbuffer;
	len = v->plen;

	/* Sanity checks against insmoding binaries or wrong arch,
	   weird elf version */
	अगर (स_भेद(hdr->e_ident, ELFMAG, SELFMAG) != 0
	    || (hdr->e_type != ET_REL && hdr->e_type != ET_EXEC)
	    || !elf_check_arch(hdr)
	    || hdr->e_shentsize != माप(*sechdrs)) अणु
		pr_warn("VPE loader: program wrong arch or weird elf version\n");

		वापस -ENOEXEC;
	पूर्ण

	अगर (hdr->e_type == ET_REL)
		relocate = 1;

	अगर (len < hdr->e_shoff + hdr->e_shnum * माप(Elf_Shdr)) अणु
		pr_err("VPE loader: program length %u truncated\n", len);

		वापस -ENOEXEC;
	पूर्ण

	/* Convenience variables */
	sechdrs = (व्योम *)hdr + hdr->e_shoff;
	secstrings = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;
	sechdrs[0].sh_addr = 0;

	/* And these should exist, but gcc whinges अगर we करोn't init them */
	symindex = strindex = 0;

	अगर (relocate) अणु
		क्रम (i = 1; i < hdr->e_shnum; i++) अणु
			अगर ((sechdrs[i].sh_type != SHT_NOBITS) &&
			    (len < sechdrs[i].sh_offset + sechdrs[i].sh_size)) अणु
				pr_err("VPE program length %u truncated\n",
				       len);
				वापस -ENOEXEC;
			पूर्ण

			/* Mark all sections sh_addr with their address in the
			   temporary image. */
			sechdrs[i].sh_addr = (माप_प्रकार) hdr +
				sechdrs[i].sh_offset;

			/* Internal symbols and strings. */
			अगर (sechdrs[i].sh_type == SHT_SYMTAB) अणु
				symindex = i;
				strindex = sechdrs[i].sh_link;
				strtab = (अक्षर *)hdr +
					sechdrs[strindex].sh_offset;
			पूर्ण
		पूर्ण
		layout_sections(&mod, hdr, sechdrs, secstrings);
	पूर्ण

	v->load_addr = alloc_progmem(mod.core_layout.size);
	अगर (!v->load_addr)
		वापस -ENOMEM;

	pr_info("VPE loader: loading to %p\n", v->load_addr);

	अगर (relocate) अणु
		क्रम (i = 0; i < hdr->e_shnum; i++) अणु
			व्योम *dest;

			अगर (!(sechdrs[i].sh_flags & SHF_ALLOC))
				जारी;

			dest = v->load_addr + sechdrs[i].sh_entsize;

			अगर (sechdrs[i].sh_type != SHT_NOBITS)
				स_नकल(dest, (व्योम *)sechdrs[i].sh_addr,
				       sechdrs[i].sh_size);
			/* Update sh_addr to poपूर्णांक to copy in image. */
			sechdrs[i].sh_addr = (अचिन्हित दीर्घ)dest;

			pr_debug(" section sh_name %s sh_addr 0x%x\n",
				 secstrings + sechdrs[i].sh_name,
				 sechdrs[i].sh_addr);
		पूर्ण

		/* Fix up syms, so that st_value is a poपूर्णांकer to location. */
		simplअगरy_symbols(sechdrs, symindex, strtab, secstrings,
				 hdr->e_shnum, &mod);

		/* Now करो relocations. */
		क्रम (i = 1; i < hdr->e_shnum; i++) अणु
			स्थिर अक्षर *strtab = (अक्षर *)sechdrs[strindex].sh_addr;
			अचिन्हित पूर्णांक info = sechdrs[i].sh_info;

			/* Not a valid relocation section? */
			अगर (info >= hdr->e_shnum)
				जारी;

			/* Don't bother with non-allocated sections */
			अगर (!(sechdrs[info].sh_flags & SHF_ALLOC))
				जारी;

			अगर (sechdrs[i].sh_type == SHT_REL)
				err = apply_relocations(sechdrs, strtab,
							symindex, i, &mod);
			अन्यथा अगर (sechdrs[i].sh_type == SHT_RELA)
				err = apply_relocate_add(sechdrs, strtab,
							 symindex, i, &mod);
			अगर (err < 0)
				वापस err;

		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा elf_phdr *phdr = (काष्ठा elf_phdr *)
						((अक्षर *)hdr + hdr->e_phoff);

		क्रम (i = 0; i < hdr->e_phnum; i++) अणु
			अगर (phdr->p_type == PT_LOAD) अणु
				स_नकल((व्योम *)phdr->p_paddr,
				       (अक्षर *)hdr + phdr->p_offset,
				       phdr->p_filesz);
				स_रखो((व्योम *)phdr->p_paddr + phdr->p_filesz,
				       0, phdr->p_memsz - phdr->p_filesz);
		    पूर्ण
		    phdr++;
		पूर्ण

		क्रम (i = 0; i < hdr->e_shnum; i++) अणु
			/* Internal symbols and strings. */
			अगर (sechdrs[i].sh_type == SHT_SYMTAB) अणु
				symindex = i;
				strindex = sechdrs[i].sh_link;
				strtab = (अक्षर *)hdr +
					sechdrs[strindex].sh_offset;

				/*
				 * mark symtab's address क्रम when we try
				 * to find the magic symbols
				 */
				sechdrs[i].sh_addr = (माप_प्रकार) hdr +
					sechdrs[i].sh_offset;
			पूर्ण
		पूर्ण
	पूर्ण

	/* make sure it's physically written out */
	flush_icache_range((अचिन्हित दीर्घ)v->load_addr,
			   (अचिन्हित दीर्घ)v->load_addr + v->len);

	अगर ((find_vpe_symbols(v, sechdrs, symindex, strtab, &mod)) < 0) अणु
		अगर (v->__start == 0) अणु
			pr_warn("VPE loader: program does not contain a __start symbol\n");
			वापस -ENOEXEC;
		पूर्ण

		अगर (v->shared_ptr == शून्य)
			pr_warn("VPE loader: program does not contain vpe_shared symbol.\n"
				" Unable to use AMVP (AP/SP) facilities.\n");
	पूर्ण

	pr_info(" elf loaded\n");
	वापस 0;
पूर्ण

/* checks VPE is unused and माला_लो पढ़ोy to load program	*/
अटल पूर्णांक vpe_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	क्रमागत vpe_state state;
	काष्ठा vpe_notअगरications *notअगरier;
	काष्ठा vpe *v;

	अगर (VPE_MODULE_MINOR != iminor(inode)) अणु
		/* assume only 1 device at the moment. */
		pr_warn("VPE loader: only vpe1 is supported\n");

		वापस -ENODEV;
	पूर्ण

	v = get_vpe(aprp_cpu_index());
	अगर (v == शून्य) अणु
		pr_warn("VPE loader: unable to get vpe\n");

		वापस -ENODEV;
	पूर्ण

	state = xchg(&v->state, VPE_STATE_INUSE);
	अगर (state != VPE_STATE_UNUSED) अणु
		pr_debug("VPE loader: tc in use dumping regs\n");

		list_क्रम_each_entry(notअगरier, &v->notअगरy, list)
			notअगरier->stop(aprp_cpu_index());

		release_progmem(v->load_addr);
		cleanup_tc(get_tc(aprp_cpu_index()));
	पूर्ण

	/* this of-course trashes what was there beक्रमe... */
	v->pbuffer = vदो_स्मृति(P_SIZE);
	अगर (!v->pbuffer) अणु
		pr_warn("VPE loader: unable to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण
	v->plen = P_SIZE;
	v->load_addr = शून्य;
	v->len = 0;
	v->shared_ptr = शून्य;
	v->__start = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vpe_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
#अगर defined(CONFIG_MIPS_VPE_LOADER_MT) || defined(CONFIG_MIPS_VPE_LOADER_CMP)
	काष्ठा vpe *v;
	Elf_Ehdr *hdr;
	पूर्णांक ret = 0;

	v = get_vpe(aprp_cpu_index());
	अगर (v == शून्य)
		वापस -ENODEV;

	hdr = (Elf_Ehdr *) v->pbuffer;
	अगर (स_भेद(hdr->e_ident, ELFMAG, SELFMAG) == 0) अणु
		अगर (vpe_elfload(v) >= 0) अणु
			vpe_run(v);
		पूर्ण अन्यथा अणु
			pr_warn("VPE loader: ELF load failed.\n");
			ret = -ENOEXEC;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_warn("VPE loader: only elf files are supported\n");
		ret = -ENOEXEC;
	पूर्ण

	/* It's good to be able to run the SP and अगर it chokes have a look at
	   the /dev/rt?. But अगर we reset the poपूर्णांकer to the shared काष्ठा we
	   lose what has happened. So perhaps अगर garbage is sent to the vpe
	   device, use it as a trigger क्रम the reset. Hopefully a nice
	   executable will be aदीर्घ लघुly. */
	अगर (ret < 0)
		v->shared_ptr = शून्य;

	vमुक्त(v->pbuffer);
	v->plen = 0;

	वापस ret;
#अन्यथा
	pr_warn("VPE loader: ELF load failed.\n");
	वापस -ENOEXEC;
#पूर्ण_अगर
पूर्ण

अटल sमाप_प्रकार vpe_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			 माप_प्रकार count, loff_t *ppos)
अणु
	माप_प्रकार ret = count;
	काष्ठा vpe *v;

	अगर (iminor(file_inode(file)) != VPE_MODULE_MINOR)
		वापस -ENODEV;

	v = get_vpe(aprp_cpu_index());

	अगर (v == शून्य)
		वापस -ENODEV;

	अगर ((count + v->len) > v->plen) अणु
		pr_warn("VPE loader: elf size too big. Perhaps strip unneeded symbols\n");
		वापस -ENOMEM;
	पूर्ण

	count -= copy_from_user(v->pbuffer + v->len, buffer, count);
	अगर (!count)
		वापस -EFAULT;

	v->len += count;
	वापस ret;
पूर्ण

स्थिर काष्ठा file_operations vpe_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = vpe_खोलो,
	.release = vpe_release,
	.ग_लिखो = vpe_ग_लिखो,
	.llseek = noop_llseek,
पूर्ण;

व्योम *vpe_get_shared(पूर्णांक index)
अणु
	काष्ठा vpe *v = get_vpe(index);

	अगर (v == शून्य)
		वापस शून्य;

	वापस v->shared_ptr;
पूर्ण
EXPORT_SYMBOL(vpe_get_shared);

पूर्णांक vpe_notअगरy(पूर्णांक index, काष्ठा vpe_notअगरications *notअगरy)
अणु
	काष्ठा vpe *v = get_vpe(index);

	अगर (v == शून्य)
		वापस -1;

	list_add(&notअगरy->list, &v->notअगरy);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vpe_notअगरy);

module_init(vpe_module_init);
module_निकास(vpe_module_निकास);
MODULE_DESCRIPTION("MIPS VPE Loader");
MODULE_AUTHOR("Elizabeth Oldham, MIPS Technologies, Inc.");
MODULE_LICENSE("GPL");
