<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  Kernel module help क्रम Alpha.
    Copyright (C) 2002 Riअक्षरd Henderson.

*/
#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#अगर 0
#घोषणा DEBUGP prपूर्णांकk
#अन्यथा
#घोषणा DEBUGP(fmt...)
#पूर्ण_अगर

/* Allocate the GOT at the end of the core sections.  */

काष्ठा got_entry अणु
	काष्ठा got_entry *next;
	Elf64_Sxword r_addend;
	पूर्णांक got_offset;
पूर्ण;

अटल अंतरभूत व्योम
process_reloc_क्रम_got(Elf64_Rela *rela,
		      काष्ठा got_entry *chains, Elf64_Xword *poffset)
अणु
	अचिन्हित दीर्घ r_sym = ELF64_R_SYM (rela->r_info);
	अचिन्हित दीर्घ r_type = ELF64_R_TYPE (rela->r_info);
	Elf64_Sxword r_addend = rela->r_addend;
	काष्ठा got_entry *g;

	अगर (r_type != R_ALPHA_LITERAL)
		वापस;

	क्रम (g = chains + r_sym; g ; g = g->next)
		अगर (g->r_addend == r_addend) अणु
			अगर (g->got_offset == 0) अणु
				g->got_offset = *poffset;
				*poffset += 8;
			पूर्ण
			जाओ found_entry;
		पूर्ण

	g = kदो_स्मृति (माप (*g), GFP_KERNEL);
	g->next = chains[r_sym].next;
	g->r_addend = r_addend;
	g->got_offset = *poffset;
	*poffset += 8;
	chains[r_sym].next = g;

 found_entry:
	/* Trick: most of the ELF64_R_TYPE field is unused.  There are
	   42 valid relocation types, and a 32-bit field.  Co-opt the
	   bits above 256 to store the got offset क्रम this reloc.  */
	rela->r_info |= g->got_offset << 8;
पूर्ण

पूर्णांक
module_frob_arch_sections(Elf64_Ehdr *hdr, Elf64_Shdr *sechdrs,
			  अक्षर *secstrings, काष्ठा module *me)
अणु
	काष्ठा got_entry *chains;
	Elf64_Rela *rela;
	Elf64_Shdr *esechdrs, *symtab, *s, *got;
	अचिन्हित दीर्घ nsyms, nrela, i;

	esechdrs = sechdrs + hdr->e_shnum;
	symtab = got = शून्य;

	/* Find out how large the symbol table is.  Allocate one got_entry
	   head per symbol.  Normally this will be enough, but not always.
	   We'll chain dअगरferent offsets क्रम the symbol करोwn each head.  */
	क्रम (s = sechdrs; s < esechdrs; ++s)
		अगर (s->sh_type == SHT_SYMTAB)
			symtab = s;
		अन्यथा अगर (!म_भेद(".got", secstrings + s->sh_name)) अणु
			got = s;
			me->arch.gotsecindex = s - sechdrs;
		पूर्ण

	अगर (!symtab) अणु
		prपूर्णांकk(KERN_ERR "module %s: no symbol table\n", me->name);
		वापस -ENOEXEC;
	पूर्ण
	अगर (!got) अणु
		prपूर्णांकk(KERN_ERR "module %s: no got section\n", me->name);
		वापस -ENOEXEC;
	पूर्ण

	nsyms = symtab->sh_size / माप(Elf64_Sym);
	chains = kसुस्मृति(nsyms, माप(काष्ठा got_entry), GFP_KERNEL);
	अगर (!chains) अणु
		prपूर्णांकk(KERN_ERR
		       "module %s: no memory for symbol chain buffer\n",
		       me->name);
		वापस -ENOMEM;
	पूर्ण

	got->sh_size = 0;
	got->sh_addralign = 8;
	got->sh_type = SHT_NOBITS;

	/* Examine all LITERAL relocations to find out what GOT entries
	   are required.  This sizes the GOT section as well.  */
	क्रम (s = sechdrs; s < esechdrs; ++s)
		अगर (s->sh_type == SHT_RELA) अणु
			nrela = s->sh_size / माप(Elf64_Rela);
			rela = (व्योम *)hdr + s->sh_offset;
			क्रम (i = 0; i < nrela; ++i)
				process_reloc_क्रम_got(rela+i, chains,
						      &got->sh_size);
		पूर्ण

	/* Free the memory we allocated.  */
	क्रम (i = 0; i < nsyms; ++i) अणु
		काष्ठा got_entry *g, *n;
		क्रम (g = chains[i].next; g ; g = n) अणु
			n = g->next;
			kमुक्त(g);
		पूर्ण
	पूर्ण
	kमुक्त(chains);

	वापस 0;
पूर्ण

पूर्णांक
apply_relocate_add(Elf64_Shdr *sechdrs, स्थिर अक्षर *strtab,
		   अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc,
		   काष्ठा module *me)
अणु
	Elf64_Rela *rela = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	अचिन्हित दीर्घ i, n = sechdrs[rअन्यथाc].sh_size / माप(*rela);
	Elf64_Sym *symtab, *sym;
	व्योम *base, *location;
	अचिन्हित दीर्घ got, gp;

	DEBUGP("Applying relocate section %u to %u\n", rअन्यथाc,
	       sechdrs[rअन्यथाc].sh_info);

	base = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr;
	symtab = (Elf64_Sym *)sechdrs[symindex].sh_addr;

	/* The small sections were sorted to the end of the segment.
	   The following should definitely cover them.  */
	gp = (u64)me->core_layout.base + me->core_layout.size - 0x8000;
	got = sechdrs[me->arch.gotsecindex].sh_addr;

	क्रम (i = 0; i < n; i++) अणु
		अचिन्हित दीर्घ r_sym = ELF64_R_SYM (rela[i].r_info);
		अचिन्हित दीर्घ r_type = ELF64_R_TYPE (rela[i].r_info);
		अचिन्हित दीर्घ r_got_offset = r_type >> 8;
		अचिन्हित दीर्घ value, hi, lo;
		r_type &= 0xff;

		/* This is where to make the change.  */
		location = base + rela[i].r_offset;

		/* This is the symbol it is referring to.  Note that all
		   unresolved symbols have been resolved.  */
		sym = symtab + r_sym;
		value = sym->st_value + rela[i].r_addend;

		चयन (r_type) अणु
		हाल R_ALPHA_NONE:
			अवरोध;
		हाल R_ALPHA_REFLONG:
			*(u32 *)location = value;
			अवरोध;
		हाल R_ALPHA_REFQUAD:
			/* BUG() can produce misaligned relocations. */
			((u32 *)location)[0] = value;
			((u32 *)location)[1] = value >> 32;
			अवरोध;
		हाल R_ALPHA_GPREL32:
			value -= gp;
			अगर ((पूर्णांक)value != value)
				जाओ reloc_overflow;
			*(u32 *)location = value;
			अवरोध;
		हाल R_ALPHA_LITERAL:
			hi = got + r_got_offset;
			lo = hi - gp;
			अगर ((लघु)lo != lo)
				जाओ reloc_overflow;
			*(u16 *)location = lo;
			*(u64 *)hi = value;
			अवरोध;
		हाल R_ALPHA_LITUSE:
			अवरोध;
		हाल R_ALPHA_GPDISP:
			value = gp - (u64)location;
			lo = (लघु)value;
			hi = (पूर्णांक)(value - lo);
			अगर (hi + lo != value)
				जाओ reloc_overflow;
			*(u16 *)location = hi >> 16;
			*(u16 *)(location + rela[i].r_addend) = lo;
			अवरोध;
		हाल R_ALPHA_BRSGP:
			/* BRSGP is only allowed to bind to local symbols.
			   If the section is undef, this means that the
			   value was resolved from somewhere अन्यथा.  */
			अगर (sym->st_shndx == SHN_UNDEF)
				जाओ reloc_overflow;
			अगर ((sym->st_other & STO_ALPHA_STD_GPLOAD) ==
			    STO_ALPHA_STD_GPLOAD)
				/* Omit the prologue. */
				value += 8;
			fallthrough;
		हाल R_ALPHA_BRADDR:
			value -= (u64)location + 4;
			अगर (value & 3)
				जाओ reloc_overflow;
			value = (दीर्घ)value >> 2;
			अगर (value + (1<<21) >= 1<<22)
				जाओ reloc_overflow;
			value &= 0x1fffff;
			value |= *(u32 *)location & ~0x1fffff;
			*(u32 *)location = value;
			अवरोध;
		हाल R_ALPHA_HINT:
			अवरोध;
		हाल R_ALPHA_SREL32:
			value -= (u64)location;
			अगर ((पूर्णांक)value != value)
				जाओ reloc_overflow;
			*(u32 *)location = value;
			अवरोध;
		हाल R_ALPHA_SREL64:
			value -= (u64)location;
			*(u64 *)location = value;
			अवरोध;
		हाल R_ALPHA_GPRELHIGH:
			value = (दीर्घ)(value - gp + 0x8000) >> 16;
			अगर ((लघु) value != value)
				जाओ reloc_overflow;
			*(u16 *)location = value;
			अवरोध;
		हाल R_ALPHA_GPRELLOW:
			value -= gp;
			*(u16 *)location = value;
			अवरोध;
		हाल R_ALPHA_GPREL16:
			value -= gp;
			अगर ((लघु) value != value)
				जाओ reloc_overflow;
			*(u16 *)location = value;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "module %s: Unknown relocation: %lu\n",
			       me->name, r_type);
			वापस -ENOEXEC;
		reloc_overflow:
			अगर (ELF64_ST_TYPE (sym->st_info) == STT_SECTION)
			  prपूर्णांकk(KERN_ERR
			         "module %s: Relocation (type %lu) overflow vs section %d\n",
			         me->name, r_type, sym->st_shndx);
			अन्यथा
			  prपूर्णांकk(KERN_ERR
			         "module %s: Relocation (type %lu) overflow vs %s\n",
			         me->name, r_type, strtab + sym->st_name);
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
