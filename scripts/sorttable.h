<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * sorttable.h
 *
 * Added ORC unwind tables sort support and other updates:
 * Copyright (C) 1999-2019 Alibaba Group Holding Limited. by:
 * Shile Zhang <shile.zhang@linux.alibaba.com>
 *
 * Copyright 2011 - 2012 Cavium, Inc.
 *
 * Some of code was taken out of arch/x86/kernel/unwind_orc.c, written by:
 * Copyright (C) 2017 Josh Poimboeuf <jpoimboe@redhat.com>
 *
 * Some of this code was taken out of recordmcount.h written by:
 *
 * Copyright 2009 John F. Reiser <jreiser@BitWagon.com>. All rights reserved.
 * Copyright 2010 Steven Rostedt <srostedt@redhat.com>, Red Hat Inc.
 */

#अघोषित extable_ent_size
#अघोषित compare_extable
#अघोषित करो_sort
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
#अघोषित _r
#अघोषित _w

#अगर_घोषित SORTTABLE_64
# define extable_ent_size	16
# define compare_extable	compare_extable_64
# define करो_sort		करो_sort_64
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
# define _r			r8
# define _w			w8
#अन्यथा
# define extable_ent_size	8
# define compare_extable	compare_extable_32
# define करो_sort		करो_sort_32
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
# define _r			r
# define _w			w
#पूर्ण_अगर

#अगर defined(SORTTABLE_64) && defined(UNWINDER_ORC_ENABLED)
/* ORC unwinder only support X86_64 */
#समावेश <त्रुटिसं.स>
#समावेश <pthपढ़ो.h>
#समावेश <यंत्र/orc_types.h>

#घोषणा ERRSTR_MAXSZ	256

अक्षर g_err[ERRSTR_MAXSZ];
पूर्णांक *g_orc_ip_table;
काष्ठा orc_entry *g_orc_table;

pthपढ़ो_t orc_sort_thपढ़ो;

अटल अंतरभूत अचिन्हित दीर्घ orc_ip(स्थिर पूर्णांक *ip)
अणु
	वापस (अचिन्हित दीर्घ)ip + *ip;
पूर्ण

अटल पूर्णांक orc_sort_cmp(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	काष्ठा orc_entry *orc_a;
	स्थिर पूर्णांक *a = g_orc_ip_table + *(पूर्णांक *)_a;
	स्थिर पूर्णांक *b = g_orc_ip_table + *(पूर्णांक *)_b;
	अचिन्हित दीर्घ a_val = orc_ip(a);
	अचिन्हित दीर्घ b_val = orc_ip(b);

	अगर (a_val > b_val)
		वापस 1;
	अगर (a_val < b_val)
		वापस -1;

	/*
	 * The "weak" section terminator entries need to always be on the left
	 * to ensure the lookup code skips them in favor of real entries.
	 * These terminator entries exist to handle any gaps created by
	 * whitelisted .o files which didn't get objtool generation.
	 */
	orc_a = g_orc_table + (a - g_orc_ip_table);
	वापस orc_a->sp_reg == ORC_REG_UNDEFINED && !orc_a->end ? -1 : 1;
पूर्ण

अटल व्योम *sort_orctable(व्योम *arg)
अणु
	पूर्णांक i;
	पूर्णांक *idxs = शून्य;
	पूर्णांक *पंचांगp_orc_ip_table = शून्य;
	काष्ठा orc_entry *पंचांगp_orc_table = शून्य;
	अचिन्हित पूर्णांक *orc_ip_size = (अचिन्हित पूर्णांक *)arg;
	अचिन्हित पूर्णांक num_entries = *orc_ip_size / माप(पूर्णांक);
	अचिन्हित पूर्णांक orc_size = num_entries * माप(काष्ठा orc_entry);

	idxs = (पूर्णांक *)दो_स्मृति(*orc_ip_size);
	अगर (!idxs) अणु
		snम_लिखो(g_err, ERRSTR_MAXSZ, "malloc idxs: %s",
			 म_त्रुटि(त्रुटि_सं));
		pthपढ़ो_निकास(g_err);
	पूर्ण

	पंचांगp_orc_ip_table = (पूर्णांक *)दो_स्मृति(*orc_ip_size);
	अगर (!पंचांगp_orc_ip_table) अणु
		snम_लिखो(g_err, ERRSTR_MAXSZ, "malloc tmp_orc_ip_table: %s",
			 म_त्रुटि(त्रुटि_सं));
		pthपढ़ो_निकास(g_err);
	पूर्ण

	पंचांगp_orc_table = (काष्ठा orc_entry *)दो_स्मृति(orc_size);
	अगर (!पंचांगp_orc_table) अणु
		snम_लिखो(g_err, ERRSTR_MAXSZ, "malloc tmp_orc_table: %s",
			 म_त्रुटि(त्रुटि_सं));
		pthपढ़ो_निकास(g_err);
	पूर्ण

	/* initialize indices array, convert ip_table to असलolute address */
	क्रम (i = 0; i < num_entries; i++) अणु
		idxs[i] = i;
		पंचांगp_orc_ip_table[i] = g_orc_ip_table[i] + i * माप(पूर्णांक);
	पूर्ण
	स_नकल(पंचांगp_orc_table, g_orc_table, orc_size);

	क्विक(idxs, num_entries, माप(पूर्णांक), orc_sort_cmp);

	क्रम (i = 0; i < num_entries; i++) अणु
		अगर (idxs[i] == i)
			जारी;

		/* convert back to relative address */
		g_orc_ip_table[i] = पंचांगp_orc_ip_table[idxs[i]] - i * माप(पूर्णांक);
		g_orc_table[i] = पंचांगp_orc_table[idxs[i]];
	पूर्ण

	मुक्त(idxs);
	मुक्त(पंचांगp_orc_ip_table);
	मुक्त(पंचांगp_orc_table);
	pthपढ़ो_निकास(शून्य);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक compare_extable(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	Elf_Addr av = _r(a);
	Elf_Addr bv = _r(b);

	अगर (av < bv)
		वापस -1;
	अगर (av > bv)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_sort(Elf_Ehdr *ehdr,
		   अक्षर स्थिर *स्थिर fname,
		   table_sort_t custom_sort)
अणु
	पूर्णांक rc = -1;
	Elf_Shdr *s, *shdr = (Elf_Shdr *)((अक्षर *)ehdr + _r(&ehdr->e_shoff));
	Elf_Shdr *strtab_sec = शून्य;
	Elf_Shdr *symtab_sec = शून्य;
	Elf_Shdr *extab_sec = शून्य;
	Elf_Sym *sym;
	स्थिर Elf_Sym *symtab;
	Elf32_Word *symtab_shndx = शून्य;
	Elf_Sym *sort_needed_sym = शून्य;
	Elf_Shdr *sort_needed_sec;
	Elf_Rel *relocs = शून्य;
	पूर्णांक relocs_size = 0;
	uपूर्णांक32_t *sort_needed_loc;
	स्थिर अक्षर *secstrings;
	स्थिर अक्षर *strtab;
	अक्षर *extab_image;
	पूर्णांक extab_index = 0;
	पूर्णांक i;
	पूर्णांक idx;
	अचिन्हित पूर्णांक shnum;
	अचिन्हित पूर्णांक shstrndx;
#अगर defined(SORTTABLE_64) && defined(UNWINDER_ORC_ENABLED)
	अचिन्हित पूर्णांक orc_ip_size = 0;
	अचिन्हित पूर्णांक orc_size = 0;
	अचिन्हित पूर्णांक orc_num_entries = 0;
#पूर्ण_अगर

	shstrndx = r2(&ehdr->e_shstrndx);
	अगर (shstrndx == SHN_XINDEX)
		shstrndx = r(&shdr[0].sh_link);
	secstrings = (स्थिर अक्षर *)ehdr + _r(&shdr[shstrndx].sh_offset);

	shnum = r2(&ehdr->e_shnum);
	अगर (shnum == SHN_UNDEF)
		shnum = _r(&shdr[0].sh_size);

	क्रम (i = 0, s = shdr; s < shdr + shnum; i++, s++) अणु
		idx = r(&s->sh_name);
		अगर (!म_भेद(secstrings + idx, "__ex_table")) अणु
			extab_sec = s;
			extab_index = i;
		पूर्ण
		अगर (!म_भेद(secstrings + idx, ".symtab"))
			symtab_sec = s;
		अगर (!म_भेद(secstrings + idx, ".strtab"))
			strtab_sec = s;

		अगर ((r(&s->sh_type) == SHT_REL ||
		     r(&s->sh_type) == SHT_RELA) &&
		    r(&s->sh_info) == extab_index) अणु
			relocs = (व्योम *)ehdr + _r(&s->sh_offset);
			relocs_size = _r(&s->sh_size);
		पूर्ण
		अगर (r(&s->sh_type) == SHT_SYMTAB_SHNDX)
			symtab_shndx = (Elf32_Word *)((स्थिर अक्षर *)ehdr +
						      _r(&s->sh_offset));

#अगर defined(SORTTABLE_64) && defined(UNWINDER_ORC_ENABLED)
		/* locate the ORC unwind tables */
		अगर (!म_भेद(secstrings + idx, ".orc_unwind_ip")) अणु
			orc_ip_size = s->sh_size;
			g_orc_ip_table = (पूर्णांक *)((व्योम *)ehdr +
						   s->sh_offset);
		पूर्ण
		अगर (!म_भेद(secstrings + idx, ".orc_unwind")) अणु
			orc_size = s->sh_size;
			g_orc_table = (काष्ठा orc_entry *)((व्योम *)ehdr +
							     s->sh_offset);
		पूर्ण
#पूर्ण_अगर
	पूर्ण /* क्रम loop */

#अगर defined(SORTTABLE_64) && defined(UNWINDER_ORC_ENABLED)
	अगर (!g_orc_ip_table || !g_orc_table) अणु
		ख_लिखो(मानक_त्रुटि,
			"incomplete ORC unwind tables in file: %s\n", fname);
		जाओ out;
	पूर्ण

	orc_num_entries = orc_ip_size / माप(पूर्णांक);
	अगर (orc_ip_size % माप(पूर्णांक) != 0 ||
	    orc_size % माप(काष्ठा orc_entry) != 0 ||
	    orc_num_entries != orc_size / माप(काष्ठा orc_entry)) अणु
		ख_लिखो(मानक_त्रुटि,
			"inconsistent ORC unwind table entries in file: %s\n",
			fname);
		जाओ out;
	पूर्ण

	/* create thपढ़ो to sort ORC unwind tables concurrently */
	अगर (pthपढ़ो_create(&orc_sort_thपढ़ो, शून्य,
			   sort_orctable, &orc_ip_size)) अणु
		ख_लिखो(मानक_त्रुटि,
			"pthread_create orc_sort_thread failed '%s': %s\n",
			म_त्रुटि(त्रुटि_सं), fname);
		जाओ out;
	पूर्ण
#पूर्ण_अगर
	अगर (!extab_sec) अणु
		ख_लिखो(मानक_त्रुटि,	"no __ex_table in file: %s\n", fname);
		जाओ out;
	पूर्ण

	अगर (!symtab_sec) अणु
		ख_लिखो(मानक_त्रुटि,	"no .symtab in file: %s\n", fname);
		जाओ out;
	पूर्ण

	अगर (!strtab_sec) अणु
		ख_लिखो(मानक_त्रुटि,	"no .strtab in file: %s\n", fname);
		जाओ out;
	पूर्ण

	extab_image = (व्योम *)ehdr + _r(&extab_sec->sh_offset);
	strtab = (स्थिर अक्षर *)ehdr + _r(&strtab_sec->sh_offset);
	symtab = (स्थिर Elf_Sym *)((स्थिर अक्षर *)ehdr +
						  _r(&symtab_sec->sh_offset));

	अगर (custom_sort) अणु
		custom_sort(extab_image, _r(&extab_sec->sh_size));
	पूर्ण अन्यथा अणु
		पूर्णांक num_entries = _r(&extab_sec->sh_size) / extable_ent_size;
		क्विक(extab_image, num_entries,
		      extable_ent_size, compare_extable);
	पूर्ण

	/* If there were relocations, we no दीर्घer need them. */
	अगर (relocs)
		स_रखो(relocs, 0, relocs_size);

	/* find the flag मुख्य_extable_sort_needed */
	क्रम (sym = (व्योम *)ehdr + _r(&symtab_sec->sh_offset);
	     sym < sym + _r(&symtab_sec->sh_size) / माप(Elf_Sym);
	     sym++) अणु
		अगर (ELF_ST_TYPE(sym->st_info) != STT_OBJECT)
			जारी;
		अगर (!म_भेद(strtab + r(&sym->st_name),
			    "main_extable_sort_needed")) अणु
			sort_needed_sym = sym;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!sort_needed_sym) अणु
		ख_लिखो(मानक_त्रुटि,
			"no main_extable_sort_needed symbol in file: %s\n",
			fname);
		जाओ out;
	पूर्ण

	sort_needed_sec = &shdr[get_secindex(r2(&sym->st_shndx),
					     sort_needed_sym - symtab,
					     symtab_shndx)];
	sort_needed_loc = (व्योम *)ehdr +
		_r(&sort_needed_sec->sh_offset) +
		_r(&sort_needed_sym->st_value) -
		_r(&sort_needed_sec->sh_addr);

	/* extable has been sorted, clear the flag */
	w(0, sort_needed_loc);
	rc = 0;

out:
#अगर defined(SORTTABLE_64) && defined(UNWINDER_ORC_ENABLED)
	अगर (orc_sort_thपढ़ो) अणु
		व्योम *retval = शून्य;
		/* रुको क्रम ORC tables sort करोne */
		rc = pthपढ़ो_join(orc_sort_thपढ़ो, &retval);
		अगर (rc)
			ख_लिखो(मानक_त्रुटि,
				"pthread_join failed '%s': %s\n",
				म_त्रुटि(त्रुटि_सं), fname);
		अन्यथा अगर (retval) अणु
			rc = -1;
			ख_लिखो(मानक_त्रुटि,
				"failed to sort ORC tables '%s': %s\n",
				(अक्षर *)retval, fname);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस rc;
पूर्ण
