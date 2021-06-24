<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * recordmcount.h
 *
 * This code was taken out of recordmcount.c written by
 * Copyright 2009 John F. Reiser <jreiser@BitWagon.com>.  All rights reserved.
 *
 * The original code had the same algorithms क्रम both 32bit
 * and 64bit ELF files, but the code was duplicated to support
 * the dअगरference in काष्ठाures that were used. This
 * file creates a macro of everything that is dअगरferent between
 * the 64 and 32 bit code, such that by including this header
 * twice we can create both sets of functions by including this
 * header once with RECORD_MCOUNT_64 undefined, and again with
 * it defined.
 *
 * This conversion to macros was करोne by:
 * Copyright 2010 Steven Rostedt <srostedt@redhat.com>, Red Hat Inc.
 */
#अघोषित append_func
#अघोषित is_fake_mcount
#अघोषित fn_is_fake_mcount
#अघोषित MIPS_is_fake_mcount
#अघोषित mcount_adjust
#अघोषित sअगरt_rel_mcount
#अघोषित nop_mcount
#अघोषित find_secsym_ndx
#अघोषित __has_rel_mcount
#अघोषित has_rel_mcount
#अघोषित tot_relsize
#अघोषित get_mcountsym
#अघोषित find_symtab
#अघोषित get_shnum
#अघोषित set_shnum
#अघोषित get_shstrndx
#अघोषित get_symindex
#अघोषित get_sym_str_and_relp
#अघोषित करो_func
#अघोषित Elf_Addr
#अघोषित Elf_Ehdr
#अघोषित Elf_Shdr
#अघोषित Elf_Rel
#अघोषित Elf_Rela
#अघोषित Elf_Sym
#अघोषित ELF_R_SYM
#अघोषित Elf_r_sym
#अघोषित ELF_R_INFO
#अघोषित Elf_r_info
#अघोषित ELF_ST_BIND
#अघोषित ELF_ST_TYPE
#अघोषित fn_ELF_R_SYM
#अघोषित fn_ELF_R_INFO
#अघोषित uपूर्णांक_t
#अघोषित _w
#अघोषित _align
#अघोषित _size

#अगर_घोषित RECORD_MCOUNT_64
# define append_func		append64
# define sअगरt_rel_mcount	sअगरt64_rel_mcount
# define nop_mcount		nop_mcount_64
# define find_secsym_ndx	find64_secsym_ndx
# define __has_rel_mcount	__has64_rel_mcount
# define has_rel_mcount		has64_rel_mcount
# define tot_relsize		tot64_relsize
# define find_symtab		find_symtab64
# define get_shnum		get_shnum64
# define set_shnum		set_shnum64
# define get_shstrndx		get_shstrndx64
# define get_symindex		get_symindex64
# define get_sym_str_and_relp	get_sym_str_and_relp_64
# define करो_func		करो64
# define get_mcountsym		get_mcountsym_64
# define is_fake_mcount		is_fake_mcount64
# define fn_is_fake_mcount	fn_is_fake_mcount64
# define MIPS_is_fake_mcount	MIPS64_is_fake_mcount
# define mcount_adjust		mcount_adjust_64
# define Elf_Addr		Elf64_Addr
# define Elf_Ehdr		Elf64_Ehdr
# define Elf_Shdr		Elf64_Shdr
# define Elf_Rel		Elf64_Rel
# define Elf_Rela		Elf64_Rela
# define Elf_Sym		Elf64_Sym
# define ELF_R_SYM		ELF64_R_SYM
# define Elf_r_sym		Elf64_r_sym
# define ELF_R_INFO		ELF64_R_INFO
# define Elf_r_info		Elf64_r_info
# define ELF_ST_BIND		ELF64_ST_BIND
# define ELF_ST_TYPE		ELF64_ST_TYPE
# define fn_ELF_R_SYM		fn_ELF64_R_SYM
# define fn_ELF_R_INFO		fn_ELF64_R_INFO
# define uपूर्णांक_t			uपूर्णांक64_t
# define _w			w8
# define _align			7u
# define _size			8
#अन्यथा
# define append_func		append32
# define sअगरt_rel_mcount	sअगरt32_rel_mcount
# define nop_mcount		nop_mcount_32
# define find_secsym_ndx	find32_secsym_ndx
# define __has_rel_mcount	__has32_rel_mcount
# define has_rel_mcount		has32_rel_mcount
# define tot_relsize		tot32_relsize
# define find_symtab		find_symtab32
# define get_shnum		get_shnum32
# define set_shnum		set_shnum32
# define get_shstrndx		get_shstrndx32
# define get_symindex		get_symindex32
# define get_sym_str_and_relp	get_sym_str_and_relp_32
# define करो_func		करो32
# define get_mcountsym		get_mcountsym_32
# define is_fake_mcount		is_fake_mcount32
# define fn_is_fake_mcount	fn_is_fake_mcount32
# define MIPS_is_fake_mcount	MIPS32_is_fake_mcount
# define mcount_adjust		mcount_adjust_32
# define Elf_Addr		Elf32_Addr
# define Elf_Ehdr		Elf32_Ehdr
# define Elf_Shdr		Elf32_Shdr
# define Elf_Rel		Elf32_Rel
# define Elf_Rela		Elf32_Rela
# define Elf_Sym		Elf32_Sym
# define ELF_R_SYM		ELF32_R_SYM
# define Elf_r_sym		Elf32_r_sym
# define ELF_R_INFO		ELF32_R_INFO
# define Elf_r_info		Elf32_r_info
# define ELF_ST_BIND		ELF32_ST_BIND
# define ELF_ST_TYPE		ELF32_ST_TYPE
# define fn_ELF_R_SYM		fn_ELF32_R_SYM
# define fn_ELF_R_INFO		fn_ELF32_R_INFO
# define uपूर्णांक_t			uपूर्णांक32_t
# define _w			w
# define _align			3u
# define _size			4
#पूर्ण_अगर

/* Functions and poपूर्णांकers that करो_file() may override क्रम specअगरic e_machine. */
अटल पूर्णांक fn_is_fake_mcount(Elf_Rel स्थिर *rp)
अणु
	वापस 0;
पूर्ण
अटल पूर्णांक (*is_fake_mcount)(Elf_Rel स्थिर *rp) = fn_is_fake_mcount;

अटल uपूर्णांक_t fn_ELF_R_SYM(Elf_Rel स्थिर *rp)
अणु
	वापस ELF_R_SYM(_w(rp->r_info));
पूर्ण
अटल uपूर्णांक_t (*Elf_r_sym)(Elf_Rel स्थिर *rp) = fn_ELF_R_SYM;

अटल व्योम fn_ELF_R_INFO(Elf_Rel *स्थिर rp, अचिन्हित sym, अचिन्हित type)
अणु
	rp->r_info = _w(ELF_R_INFO(sym, type));
पूर्ण
अटल व्योम (*Elf_r_info)(Elf_Rel *स्थिर rp, अचिन्हित sym, अचिन्हित type) = fn_ELF_R_INFO;

अटल पूर्णांक mcount_adjust = 0;

/*
 * MIPS mcount दीर्घ call has 2 _mcount symbols, only the position of the 1st
 * _mcount symbol is needed क्रम dynamic function tracer, with it, to disable
 * tracing(ftrace_make_nop), the inकाष्ठाion in the position is replaced with
 * the "b label" inकाष्ठाion, to enable tracing(ftrace_make_call), replace the
 * inकाष्ठाion back. So, here, we set the 2nd one as fake and filter it.
 *
 * c:	3c030000	lui	v1,0x0		<-->	b	label
 *		c: R_MIPS_HI16	_mcount
 *		c: R_MIPS_NONE	*ABS*
 *		c: R_MIPS_NONE	*ABS*
 * 10:	64630000	daddiu	v1,v1,0
 *		10: R_MIPS_LO16	_mcount
 *		10: R_MIPS_NONE	*ABS*
 *		10: R_MIPS_NONE	*ABS*
 * 14:	03e0082d	move	at,ra
 * 18:	0060f809	jalr	v1
 * label:
 */
#घोषणा MIPS_FAKEMCOUNT_OFFSET	4

अटल पूर्णांक MIPS_is_fake_mcount(Elf_Rel स्थिर *rp)
अणु
	अटल Elf_Addr old_r_offset = ~(Elf_Addr)0;
	Elf_Addr current_r_offset = _w(rp->r_offset);
	पूर्णांक is_fake;

	is_fake = (old_r_offset != ~(Elf_Addr)0) &&
		(current_r_offset - old_r_offset == MIPS_FAKEMCOUNT_OFFSET);
	old_r_offset = current_r_offset;

	वापस is_fake;
पूर्ण

अटल अचिन्हित पूर्णांक get_symindex(Elf_Sym स्थिर *sym, Elf32_Word स्थिर *symtab,
				 Elf32_Word स्थिर *symtab_shndx)
अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित लघु shndx = w2(sym->st_shndx);
	पूर्णांक index;

	अगर (shndx > SHN_UNDEF && shndx < SHN_LORESERVE)
		वापस shndx;

	अगर (shndx == SHN_XINDEX) अणु
		offset = (अचिन्हित दीर्घ)sym - (अचिन्हित दीर्घ)symtab;
		index = offset / माप(*sym);

		वापस w(symtab_shndx[index]);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक get_shnum(Elf_Ehdr स्थिर *ehdr, Elf_Shdr स्थिर *shdr0)
अणु
	अगर (shdr0 && !ehdr->e_shnum)
		वापस w(shdr0->sh_size);

	वापस w2(ehdr->e_shnum);
पूर्ण

अटल व्योम set_shnum(Elf_Ehdr *ehdr, Elf_Shdr *shdr0, अचिन्हित पूर्णांक new_shnum)
अणु
	अगर (new_shnum >= SHN_LORESERVE) अणु
		ehdr->e_shnum = 0;
		shdr0->sh_size = w(new_shnum);
	पूर्ण अन्यथा
		ehdr->e_shnum = w2(new_shnum);
पूर्ण

अटल पूर्णांक get_shstrndx(Elf_Ehdr स्थिर *ehdr, Elf_Shdr स्थिर *shdr0)
अणु
	अगर (ehdr->e_shstrndx != SHN_XINDEX)
		वापस w2(ehdr->e_shstrndx);

	वापस w(shdr0->sh_link);
पूर्ण

अटल व्योम find_symtab(Elf_Ehdr *स्थिर ehdr, Elf_Shdr स्थिर *shdr0,
			अचिन्हित स्थिर nhdr, Elf32_Word **symtab,
			Elf32_Word **symtab_shndx)
अणु
	Elf_Shdr स्थिर *relhdr;
	अचिन्हित k;

	*symtab = शून्य;
	*symtab_shndx = शून्य;

	क्रम (relhdr = shdr0, k = nhdr; k; --k, ++relhdr) अणु
		अगर (relhdr->sh_type == SHT_SYMTAB)
			*symtab = (व्योम *)ehdr + relhdr->sh_offset;
		अन्यथा अगर (relhdr->sh_type == SHT_SYMTAB_SHNDX)
			*symtab_shndx = (व्योम *)ehdr + relhdr->sh_offset;

		अगर (*symtab && *symtab_shndx)
			अवरोध;
	पूर्ण
पूर्ण

/* Append the new shstrtab, Elf_Shdr[], __mcount_loc and its relocations. */
अटल पूर्णांक append_func(Elf_Ehdr *स्थिर ehdr,
			Elf_Shdr *स्थिर shstr,
			uपूर्णांक_t स्थिर *स्थिर mloc0,
			uपूर्णांक_t स्थिर *स्थिर mlocp,
			Elf_Rel स्थिर *स्थिर mrel0,
			Elf_Rel स्थिर *स्थिर mrelp,
			अचिन्हित पूर्णांक स्थिर rel_entsize,
			अचिन्हित पूर्णांक स्थिर symsec_sh_link)
अणु
	/* Begin स्थिरructing output file */
	Elf_Shdr mcsec;
	अक्षर स्थिर *mc_name = (माप(Elf_Rela) == rel_entsize)
		? ".rela__mcount_loc"
		:  ".rel__mcount_loc";
	uपूर्णांक_t स्थिर old_shoff = _w(ehdr->e_shoff);
	uपूर्णांक_t स्थिर old_shstr_sh_size   = _w(shstr->sh_size);
	uपूर्णांक_t स्थिर old_shstr_sh_offset = _w(shstr->sh_offset);
	Elf_Shdr *स्थिर shdr0 = (Elf_Shdr *)(old_shoff + (व्योम *)ehdr);
	अचिन्हित पूर्णांक स्थिर old_shnum = get_shnum(ehdr, shdr0);
	अचिन्हित पूर्णांक स्थिर new_shnum = 2 + old_shnum; /* अणु.rel,पूर्ण__mcount_loc */
	uपूर्णांक_t t = 1 + म_माप(mc_name) + _w(shstr->sh_size);
	uपूर्णांक_t new_e_shoff;

	shstr->sh_size = _w(t);
	shstr->sh_offset = _w(sb.st_size);
	t += sb.st_size;
	t += (_align & -t);  /* word-byte align */
	new_e_shoff = t;

	set_shnum(ehdr, shdr0, new_shnum);

	/* body क्रम new shstrtab */
	अगर (ulseek(sb.st_size, शुरू_से) < 0)
		वापस -1;
	अगर (uग_लिखो(old_shstr_sh_offset + (व्योम *)ehdr, old_shstr_sh_size) < 0)
		वापस -1;
	अगर (uग_लिखो(mc_name, 1 + म_माप(mc_name)) < 0)
		वापस -1;

	/* old(modअगरied) Elf_Shdr table, word-byte aligned */
	अगर (ulseek(t, शुरू_से) < 0)
		वापस -1;
	t += माप(Elf_Shdr) * old_shnum;
	अगर (uग_लिखो(old_shoff + (व्योम *)ehdr,
	       माप(Elf_Shdr) * old_shnum) < 0)
		वापस -1;

	/* new sections __mcount_loc and .rel__mcount_loc */
	t += 2*माप(mcsec);
	mcsec.sh_name = w((माप(Elf_Rela) == rel_entsize) + म_माप(".rel")
		+ old_shstr_sh_size);
	mcsec.sh_type = w(SHT_PROGBITS);
	mcsec.sh_flags = _w(SHF_ALLOC);
	mcsec.sh_addr = 0;
	mcsec.sh_offset = _w(t);
	mcsec.sh_size = _w((व्योम *)mlocp - (व्योम *)mloc0);
	mcsec.sh_link = 0;
	mcsec.sh_info = 0;
	mcsec.sh_addralign = _w(_size);
	mcsec.sh_entsize = _w(_size);
	अगर (uग_लिखो(&mcsec, माप(mcsec)) < 0)
		वापस -1;

	mcsec.sh_name = w(old_shstr_sh_size);
	mcsec.sh_type = (माप(Elf_Rela) == rel_entsize)
		? w(SHT_RELA)
		: w(SHT_REL);
	mcsec.sh_flags = 0;
	mcsec.sh_addr = 0;
	mcsec.sh_offset = _w((व्योम *)mlocp - (व्योम *)mloc0 + t);
	mcsec.sh_size   = _w((व्योम *)mrelp - (व्योम *)mrel0);
	mcsec.sh_link = w(symsec_sh_link);
	mcsec.sh_info = w(old_shnum);
	mcsec.sh_addralign = _w(_size);
	mcsec.sh_entsize = _w(rel_entsize);

	अगर (uग_लिखो(&mcsec, माप(mcsec)) < 0)
		वापस -1;

	अगर (uग_लिखो(mloc0, (व्योम *)mlocp - (व्योम *)mloc0) < 0)
		वापस -1;
	अगर (uग_लिखो(mrel0, (व्योम *)mrelp - (व्योम *)mrel0) < 0)
		वापस -1;

	ehdr->e_shoff = _w(new_e_shoff);
	अगर (ulseek(0, शुरू_से) < 0)
		वापस -1;
	अगर (uग_लिखो(ehdr, माप(*ehdr)) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल अचिन्हित get_mcountsym(Elf_Sym स्थिर *स्थिर sym0,
			      Elf_Rel स्थिर *relp,
			      अक्षर स्थिर *स्थिर str0)
अणु
	अचिन्हित mcountsym = 0;

	Elf_Sym स्थिर *स्थिर symp =
		&sym0[Elf_r_sym(relp)];
	अक्षर स्थिर *symname = &str0[w(symp->st_name)];
	अक्षर स्थिर *mcount = gpfx == '_' ? "_mcount" : "mcount";
	अक्षर स्थिर *fentry = "__fentry__";

	अगर (symname[0] == '.')
		++symname;  /* ppc64 hack */
	अगर (म_भेद(mcount, symname) == 0 ||
	    (alपंचांगcount && म_भेद(alपंचांगcount, symname) == 0) ||
	    (म_भेद(fentry, symname) == 0))
		mcountsym = Elf_r_sym(relp);

	वापस mcountsym;
पूर्ण

अटल व्योम get_sym_str_and_relp(Elf_Shdr स्थिर *स्थिर relhdr,
				 Elf_Ehdr स्थिर *स्थिर ehdr,
				 Elf_Sym स्थिर **sym0,
				 अक्षर स्थिर **str0,
				 Elf_Rel स्थिर **relp)
अणु
	Elf_Shdr *स्थिर shdr0 = (Elf_Shdr *)(_w(ehdr->e_shoff)
		+ (व्योम *)ehdr);
	अचिन्हित स्थिर symsec_sh_link = w(relhdr->sh_link);
	Elf_Shdr स्थिर *स्थिर symsec = &shdr0[symsec_sh_link];
	Elf_Shdr स्थिर *स्थिर strsec = &shdr0[w(symsec->sh_link)];
	Elf_Rel स्थिर *स्थिर rel0 = (Elf_Rel स्थिर *)(_w(relhdr->sh_offset)
		+ (व्योम *)ehdr);

	*sym0 = (Elf_Sym स्थिर *)(_w(symsec->sh_offset)
				  + (व्योम *)ehdr);

	*str0 = (अक्षर स्थिर *)(_w(strsec->sh_offset)
			       + (व्योम *)ehdr);

	*relp = rel0;
पूर्ण

/*
 * Look at the relocations in order to find the calls to mcount.
 * Accumulate the section offsets that are found, and their relocation info,
 * onto the end of the existing arrays.
 */
अटल uपूर्णांक_t *sअगरt_rel_mcount(uपूर्णांक_t *mlocp,
			       अचिन्हित स्थिर offbase,
			       Elf_Rel **स्थिर mrelpp,
			       Elf_Shdr स्थिर *स्थिर relhdr,
			       Elf_Ehdr स्थिर *स्थिर ehdr,
			       अचिन्हित स्थिर recsym,
			       uपूर्णांक_t स्थिर recval,
			       अचिन्हित स्थिर reltype)
अणु
	uपूर्णांक_t *स्थिर mloc0 = mlocp;
	Elf_Rel *mrelp = *mrelpp;
	Elf_Sym स्थिर *sym0;
	अक्षर स्थिर *str0;
	Elf_Rel स्थिर *relp;
	अचिन्हित rel_entsize = _w(relhdr->sh_entsize);
	अचिन्हित स्थिर nrel = _w(relhdr->sh_size) / rel_entsize;
	अचिन्हित mcountsym = 0;
	अचिन्हित t;

	get_sym_str_and_relp(relhdr, ehdr, &sym0, &str0, &relp);

	क्रम (t = nrel; t; --t) अणु
		अगर (!mcountsym)
			mcountsym = get_mcountsym(sym0, relp, str0);

		अगर (mcountsym && mcountsym == Elf_r_sym(relp) &&
				!is_fake_mcount(relp)) अणु
			uपूर्णांक_t स्थिर addend =
				_w(_w(relp->r_offset) - recval + mcount_adjust);
			mrelp->r_offset = _w(offbase
				+ ((व्योम *)mlocp - (व्योम *)mloc0));
			Elf_r_info(mrelp, recsym, reltype);
			अगर (rel_entsize == माप(Elf_Rela)) अणु
				((Elf_Rela *)mrelp)->r_addend = addend;
				*mlocp++ = 0;
			पूर्ण अन्यथा
				*mlocp++ = addend;

			mrelp = (Elf_Rel *)(rel_entsize + (व्योम *)mrelp);
		पूर्ण
		relp = (Elf_Rel स्थिर *)(rel_entsize + (व्योम *)relp);
	पूर्ण
	*mrelpp = mrelp;
	वापस mlocp;
पूर्ण

/*
 * Read the relocation table again, but this समय its called on sections
 * that are not going to be traced. The mcount calls here will be converted
 * पूर्णांकo nops.
 */
अटल पूर्णांक nop_mcount(Elf_Shdr स्थिर *स्थिर relhdr,
		      Elf_Ehdr स्थिर *स्थिर ehdr,
		      स्थिर अक्षर *स्थिर txtname)
अणु
	Elf_Shdr *स्थिर shdr0 = (Elf_Shdr *)(_w(ehdr->e_shoff)
		+ (व्योम *)ehdr);
	Elf_Sym स्थिर *sym0;
	अक्षर स्थिर *str0;
	Elf_Rel स्थिर *relp;
	Elf_Shdr स्थिर *स्थिर shdr = &shdr0[w(relhdr->sh_info)];
	अचिन्हित rel_entsize = _w(relhdr->sh_entsize);
	अचिन्हित स्थिर nrel = _w(relhdr->sh_size) / rel_entsize;
	अचिन्हित mcountsym = 0;
	अचिन्हित t;
	पूर्णांक once = 0;

	get_sym_str_and_relp(relhdr, ehdr, &sym0, &str0, &relp);

	क्रम (t = nrel; t; --t) अणु
		पूर्णांक ret = -1;

		अगर (!mcountsym)
			mcountsym = get_mcountsym(sym0, relp, str0);

		अगर (mcountsym == Elf_r_sym(relp) && !is_fake_mcount(relp)) अणु
			अगर (make_nop)
				ret = make_nop((व्योम *)ehdr, _w(shdr->sh_offset) + _w(relp->r_offset));
			अगर (warn_on_notrace_sect && !once) अणु
				म_लिखो("Section %s has mcount callers being ignored\n",
				       txtname);
				once = 1;
				/* just warn? */
				अगर (!make_nop)
					वापस 0;
			पूर्ण
		पूर्ण

		/*
		 * If we successfully हटाओd the mcount, mark the relocation
		 * as a nop (करोn't करो anything with it).
		 */
		अगर (!ret) अणु
			Elf_Rel rel;
			rel = *(Elf_Rel *)relp;
			Elf_r_info(&rel, Elf_r_sym(relp), rel_type_nop);
			अगर (ulseek((व्योम *)relp - (व्योम *)ehdr, शुरू_से) < 0)
				वापस -1;
			अगर (uग_लिखो(&rel, माप(rel)) < 0)
				वापस -1;
		पूर्ण
		relp = (Elf_Rel स्थिर *)(rel_entsize + (व्योम *)relp);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Find a symbol in the given section, to be used as the base क्रम relocating
 * the table of offsets of calls to mcount.  A local or global symbol suffices,
 * but aव्योम a Weak symbol because it may be overridden; the change in value
 * would invalidate the relocations of the offsets of the calls to mcount.
 * Often the found symbol will be the unnamed local symbol generated by
 * GNU 'as' क्रम the start of each section.  For example:
 *    Num:    Value  Size Type    Bind   Vis      Ndx Name
 *      2: 00000000     0 SECTION LOCAL  DEFAULT    1
 */
अटल पूर्णांक find_secsym_ndx(अचिन्हित स्थिर txtndx,
				अक्षर स्थिर *स्थिर txtname,
				uपूर्णांक_t *स्थिर recvalp,
				अचिन्हित पूर्णांक *sym_index,
				Elf_Shdr स्थिर *स्थिर symhdr,
				Elf32_Word स्थिर *symtab,
				Elf32_Word स्थिर *symtab_shndx,
				Elf_Ehdr स्थिर *स्थिर ehdr)
अणु
	Elf_Sym स्थिर *स्थिर sym0 = (Elf_Sym स्थिर *)(_w(symhdr->sh_offset)
		+ (व्योम *)ehdr);
	अचिन्हित स्थिर nsym = _w(symhdr->sh_size) / _w(symhdr->sh_entsize);
	Elf_Sym स्थिर *symp;
	अचिन्हित t;

	क्रम (symp = sym0, t = nsym; t; --t, ++symp) अणु
		अचिन्हित पूर्णांक स्थिर st_bind = ELF_ST_BIND(symp->st_info);

		अगर (txtndx == get_symindex(symp, symtab, symtab_shndx)
			/* aव्योम STB_WEAK */
		    && (STB_LOCAL == st_bind || STB_GLOBAL == st_bind)) अणु
			/* function symbols on ARM have quirks, aव्योम them */
			अगर (w2(ehdr->e_machine) == EM_ARM
			    && ELF_ST_TYPE(symp->st_info) == STT_FUNC)
				जारी;

			*recvalp = _w(symp->st_value);
			*sym_index = symp - sym0;
			वापस 0;
		पूर्ण
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "Cannot find symbol for section %u: %s.\n",
		txtndx, txtname);
	वापस -1;
पूर्ण

/* Evade ISO C restriction: no declaration after statement in has_rel_mcount. */
अटल अक्षर स्थिर * __has_rel_mcount(Elf_Shdr स्थिर *स्थिर relhdr, /* reltype */
				     Elf_Shdr स्थिर *स्थिर shdr0,
				     अक्षर स्थिर *स्थिर shstrtab,
				     अक्षर स्थिर *स्थिर fname)
अणु
	/* .sh_info depends on .sh_type == SHT_REL[,A] */
	Elf_Shdr स्थिर *स्थिर txthdr = &shdr0[w(relhdr->sh_info)];
	अक्षर स्थिर *स्थिर txtname = &shstrtab[w(txthdr->sh_name)];

	अगर (म_भेद("__mcount_loc", txtname) == 0) अणु
		ख_लिखो(मानक_त्रुटि, "warning: __mcount_loc already exists: %s\n",
			fname);
		वापस alपढ़ोy_has_rel_mcount;
	पूर्ण
	अगर (w(txthdr->sh_type) != SHT_PROGBITS ||
	    !(_w(txthdr->sh_flags) & SHF_EXECINSTR))
		वापस शून्य;
	वापस txtname;
पूर्ण

अटल अक्षर स्थिर *has_rel_mcount(Elf_Shdr स्थिर *स्थिर relhdr,
				  Elf_Shdr स्थिर *स्थिर shdr0,
				  अक्षर स्थिर *स्थिर shstrtab,
				  अक्षर स्थिर *स्थिर fname)
अणु
	अगर (w(relhdr->sh_type) != SHT_REL && w(relhdr->sh_type) != SHT_RELA)
		वापस शून्य;
	वापस __has_rel_mcount(relhdr, shdr0, shstrtab, fname);
पूर्ण


अटल अचिन्हित tot_relsize(Elf_Shdr स्थिर *स्थिर shdr0,
			    अचिन्हित nhdr,
			    स्थिर अक्षर *स्थिर shstrtab,
			    स्थिर अक्षर *स्थिर fname)
अणु
	अचिन्हित totrelsz = 0;
	Elf_Shdr स्थिर *shdrp = shdr0;
	अक्षर स्थिर *txtname;

	क्रम (; nhdr; --nhdr, ++shdrp) अणु
		txtname = has_rel_mcount(shdrp, shdr0, shstrtab, fname);
		अगर (txtname == alपढ़ोy_has_rel_mcount) अणु
			totrelsz = 0;
			अवरोध;
		पूर्ण
		अगर (txtname && is_mcounted_section_name(txtname))
			totrelsz += _w(shdrp->sh_size);
	पूर्ण
	वापस totrelsz;
पूर्ण

/* Overall supervision क्रम Elf32 ET_REL file. */
अटल पूर्णांक करो_func(Elf_Ehdr *स्थिर ehdr, अक्षर स्थिर *स्थिर fname,
		   अचिन्हित स्थिर reltype)
अणु
	Elf_Shdr *स्थिर shdr0 = (Elf_Shdr *)(_w(ehdr->e_shoff)
		+ (व्योम *)ehdr);
	अचिन्हित स्थिर nhdr = get_shnum(ehdr, shdr0);
	Elf_Shdr *स्थिर shstr = &shdr0[get_shstrndx(ehdr, shdr0)];
	अक्षर स्थिर *स्थिर shstrtab = (अक्षर स्थिर *)(_w(shstr->sh_offset)
		+ (व्योम *)ehdr);

	Elf_Shdr स्थिर *relhdr;
	अचिन्हित k;

	Elf32_Word *symtab;
	Elf32_Word *symtab_shndx;

	/* Upper bound on space: assume all relevant relocs are क्रम mcount. */
	अचिन्हित       totrelsz;

	Elf_Rel *      mrel0;
	Elf_Rel *      mrelp;

	uपूर्णांक_t *      mloc0;
	uपूर्णांक_t *      mlocp;

	अचिन्हित rel_entsize = 0;
	अचिन्हित symsec_sh_link = 0;

	पूर्णांक result = 0;

	totrelsz = tot_relsize(shdr0, nhdr, shstrtab, fname);
	अगर (totrelsz == 0)
		वापस 0;
	mrel0 = uदो_स्मृति(totrelsz);
	mrelp = mrel0;
	अगर (!mrel0)
		वापस -1;

	/* 2*माप(address) <= माप(Elf_Rel) */
	mloc0 = uदो_स्मृति(totrelsz>>1);
	mlocp = mloc0;
	अगर (!mloc0) अणु
		मुक्त(mrel0);
		वापस -1;
	पूर्ण

	find_symtab(ehdr, shdr0, nhdr, &symtab, &symtab_shndx);

	क्रम (relhdr = shdr0, k = nhdr; k; --k, ++relhdr) अणु
		अक्षर स्थिर *स्थिर txtname = has_rel_mcount(relhdr, shdr0,
			shstrtab, fname);
		अगर (txtname == alपढ़ोy_has_rel_mcount) अणु
			result = 0;
			file_updated = 0;
			जाओ out; /* Nothing to be करोne; करोn't append! */
		पूर्ण
		अगर (txtname && is_mcounted_section_name(txtname)) अणु
			अचिन्हित पूर्णांक recsym;
			uपूर्णांक_t recval = 0;

			symsec_sh_link = w(relhdr->sh_link);
			result = find_secsym_ndx(w(relhdr->sh_info), txtname,
						&recval, &recsym,
						&shdr0[symsec_sh_link],
						symtab, symtab_shndx,
						ehdr);
			अगर (result)
				जाओ out;

			rel_entsize = _w(relhdr->sh_entsize);
			mlocp = sअगरt_rel_mcount(mlocp,
				(व्योम *)mlocp - (व्योम *)mloc0, &mrelp,
				relhdr, ehdr, recsym, recval, reltype);
		पूर्ण अन्यथा अगर (txtname && (warn_on_notrace_sect || make_nop)) अणु
			/*
			 * This section is ignored by ftrace, but still
			 * has mcount calls. Convert them to nops now.
			 */
			अगर (nop_mcount(relhdr, ehdr, txtname) < 0) अणु
				result = -1;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!result && mloc0 != mlocp)
		result = append_func(ehdr, shstr, mloc0, mlocp, mrel0, mrelp,
				     rel_entsize, symsec_sh_link);
out:
	मुक्त(mrel0);
	मुक्त(mloc0);
	वापस result;
पूर्ण
