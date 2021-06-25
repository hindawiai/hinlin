<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * elf.c - ELF access library
 *
 * Adapted from kpatch (https://github.com/dynup/kpatch):
 * Copyright (C) 2013-2015 Josh Poimboeuf <jpoimboe@redhat.com>
 * Copyright (C) 2014 Seth Jennings <sjenning@redhat.com>
 */

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <objtool/builtin.h>

#समावेश <objtool/elf.h>
#समावेश <objtool/warn.h>

#घोषणा MAX_NAME_LEN 128

अटल अंतरभूत u32 str_hash(स्थिर अक्षर *str)
अणु
	वापस jhash(str, म_माप(str), 0);
पूर्ण

अटल अंतरभूत पूर्णांक elf_hash_bits(व्योम)
अणु
	वापस vmlinux ? ELF_HASH_BITS : 16;
पूर्ण

#घोषणा elf_hash_add(hashtable, node, key) \
	hlist_add_head(node, &hashtable[hash_min(key, elf_hash_bits())])

अटल व्योम elf_hash_init(काष्ठा hlist_head *table)
अणु
	__hash_init(table, 1U << elf_hash_bits());
पूर्ण

#घोषणा elf_hash_क्रम_each_possible(name, obj, member, key)			\
	hlist_क्रम_each_entry(obj, &name[hash_min(key, elf_hash_bits())], member)

अटल bool symbol_to_offset(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	काष्ठा symbol *sa = rb_entry(a, काष्ठा symbol, node);
	काष्ठा symbol *sb = rb_entry(b, काष्ठा symbol, node);

	अगर (sa->offset < sb->offset)
		वापस true;
	अगर (sa->offset > sb->offset)
		वापस false;

	अगर (sa->len < sb->len)
		वापस true;
	अगर (sa->len > sb->len)
		वापस false;

	sa->alias = sb;

	वापस false;
पूर्ण

अटल पूर्णांक symbol_by_offset(स्थिर व्योम *key, स्थिर काष्ठा rb_node *node)
अणु
	स्थिर काष्ठा symbol *s = rb_entry(node, काष्ठा symbol, node);
	स्थिर अचिन्हित दीर्घ *o = key;

	अगर (*o < s->offset)
		वापस -1;
	अगर (*o >= s->offset + s->len)
		वापस 1;

	वापस 0;
पूर्ण

काष्ठा section *find_section_by_name(स्थिर काष्ठा elf *elf, स्थिर अक्षर *name)
अणु
	काष्ठा section *sec;

	elf_hash_क्रम_each_possible(elf->section_name_hash, sec, name_hash, str_hash(name))
		अगर (!म_भेद(sec->name, name))
			वापस sec;

	वापस शून्य;
पूर्ण

अटल काष्ठा section *find_section_by_index(काष्ठा elf *elf,
					     अचिन्हित पूर्णांक idx)
अणु
	काष्ठा section *sec;

	elf_hash_क्रम_each_possible(elf->section_hash, sec, hash, idx)
		अगर (sec->idx == idx)
			वापस sec;

	वापस शून्य;
पूर्ण

अटल काष्ठा symbol *find_symbol_by_index(काष्ठा elf *elf, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा symbol *sym;

	elf_hash_क्रम_each_possible(elf->symbol_hash, sym, hash, idx)
		अगर (sym->idx == idx)
			वापस sym;

	वापस शून्य;
पूर्ण

काष्ठा symbol *find_symbol_by_offset(काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	काष्ठा rb_node *node;

	rb_क्रम_each(node, &offset, &sec->symbol_tree, symbol_by_offset) अणु
		काष्ठा symbol *s = rb_entry(node, काष्ठा symbol, node);

		अगर (s->offset == offset && s->type != STT_SECTION)
			वापस s;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा symbol *find_func_by_offset(काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	काष्ठा rb_node *node;

	rb_क्रम_each(node, &offset, &sec->symbol_tree, symbol_by_offset) अणु
		काष्ठा symbol *s = rb_entry(node, काष्ठा symbol, node);

		अगर (s->offset == offset && s->type == STT_FUNC)
			वापस s;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा symbol *find_symbol_containing(स्थिर काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	काष्ठा rb_node *node;

	rb_क्रम_each(node, &offset, &sec->symbol_tree, symbol_by_offset) अणु
		काष्ठा symbol *s = rb_entry(node, काष्ठा symbol, node);

		अगर (s->type != STT_SECTION)
			वापस s;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा symbol *find_func_containing(काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	काष्ठा rb_node *node;

	rb_क्रम_each(node, &offset, &sec->symbol_tree, symbol_by_offset) अणु
		काष्ठा symbol *s = rb_entry(node, काष्ठा symbol, node);

		अगर (s->type == STT_FUNC)
			वापस s;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा symbol *find_symbol_by_name(स्थिर काष्ठा elf *elf, स्थिर अक्षर *name)
अणु
	काष्ठा symbol *sym;

	elf_hash_क्रम_each_possible(elf->symbol_name_hash, sym, name_hash, str_hash(name))
		अगर (!म_भेद(sym->name, name))
			वापस sym;

	वापस शून्य;
पूर्ण

काष्ठा reloc *find_reloc_by_dest_range(स्थिर काष्ठा elf *elf, काष्ठा section *sec,
				     अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक len)
अणु
	काष्ठा reloc *reloc, *r = शून्य;
	अचिन्हित दीर्घ o;

	अगर (!sec->reloc)
		वापस शून्य;

	sec = sec->reloc;

	क्रम_offset_range(o, offset, offset + len) अणु
		elf_hash_क्रम_each_possible(elf->reloc_hash, reloc, hash,
				       sec_offset_hash(sec, o)) अणु
			अगर (reloc->sec != sec)
				जारी;

			अगर (reloc->offset >= offset && reloc->offset < offset + len) अणु
				अगर (!r || reloc->offset < r->offset)
					r = reloc;
			पूर्ण
		पूर्ण
		अगर (r)
			वापस r;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा reloc *find_reloc_by_dest(स्थिर काष्ठा elf *elf, काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	वापस find_reloc_by_dest_range(elf, sec, offset, 1);
पूर्ण

अटल पूर्णांक पढ़ो_sections(काष्ठा elf *elf)
अणु
	Elf_Scn *s = शून्य;
	काष्ठा section *sec;
	माप_प्रकार shstrndx, sections_nr;
	पूर्णांक i;

	अगर (elf_माला_लोhdrnum(elf->elf, &sections_nr)) अणु
		WARN_ELF("elf_getshdrnum");
		वापस -1;
	पूर्ण

	अगर (elf_माला_लोhdrstrndx(elf->elf, &shstrndx)) अणु
		WARN_ELF("elf_getshdrstrndx");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < sections_nr; i++) अणु
		sec = दो_स्मृति(माप(*sec));
		अगर (!sec) अणु
			लिखो_त्रुटि("malloc");
			वापस -1;
		पूर्ण
		स_रखो(sec, 0, माप(*sec));

		INIT_LIST_HEAD(&sec->symbol_list);
		INIT_LIST_HEAD(&sec->reloc_list);

		s = elf_माला_लोcn(elf->elf, i);
		अगर (!s) अणु
			WARN_ELF("elf_getscn");
			वापस -1;
		पूर्ण

		sec->idx = elf_ndxscn(s);

		अगर (!gelf_माला_लोhdr(s, &sec->sh)) अणु
			WARN_ELF("gelf_getshdr");
			वापस -1;
		पूर्ण

		sec->name = elf_strptr(elf->elf, shstrndx, sec->sh.sh_name);
		अगर (!sec->name) अणु
			WARN_ELF("elf_strptr");
			वापस -1;
		पूर्ण

		अगर (sec->sh.sh_size != 0) अणु
			sec->data = elf_getdata(s, शून्य);
			अगर (!sec->data) अणु
				WARN_ELF("elf_getdata");
				वापस -1;
			पूर्ण
			अगर (sec->data->d_off != 0 ||
			    sec->data->d_size != sec->sh.sh_size) अणु
				WARN("unexpected data attributes for %s",
				     sec->name);
				वापस -1;
			पूर्ण
		पूर्ण
		sec->len = sec->sh.sh_size;

		list_add_tail(&sec->list, &elf->sections);
		elf_hash_add(elf->section_hash, &sec->hash, sec->idx);
		elf_hash_add(elf->section_name_hash, &sec->name_hash, str_hash(sec->name));
	पूर्ण

	अगर (stats)
		म_लिखो("nr_sections: %lu\n", (अचिन्हित दीर्घ)sections_nr);

	/* sanity check, one more call to elf_nextscn() should वापस शून्य */
	अगर (elf_nextscn(elf->elf, s)) अणु
		WARN("section entry mismatch");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम elf_add_symbol(काष्ठा elf *elf, काष्ठा symbol *sym)
अणु
	काष्ठा list_head *entry;
	काष्ठा rb_node *pnode;

	sym->type = GELF_ST_TYPE(sym->sym.st_info);
	sym->bind = GELF_ST_BIND(sym->sym.st_info);

	sym->offset = sym->sym.st_value;
	sym->len = sym->sym.st_size;

	rb_add(&sym->node, &sym->sec->symbol_tree, symbol_to_offset);
	pnode = rb_prev(&sym->node);
	अगर (pnode)
		entry = &rb_entry(pnode, काष्ठा symbol, node)->list;
	अन्यथा
		entry = &sym->sec->symbol_list;
	list_add(&sym->list, entry);
	elf_hash_add(elf->symbol_hash, &sym->hash, sym->idx);
	elf_hash_add(elf->symbol_name_hash, &sym->name_hash, str_hash(sym->name));

	/*
	 * Don't store empty STT_NOTYPE symbols in the rbtree.  They
	 * can exist within a function, confusing the sorting.
	 */
	अगर (!sym->len)
		rb_erase(&sym->node, &sym->sec->symbol_tree);
पूर्ण

अटल पूर्णांक पढ़ो_symbols(काष्ठा elf *elf)
अणु
	काष्ठा section *symtab, *symtab_shndx, *sec;
	काष्ठा symbol *sym, *pfunc;
	पूर्णांक symbols_nr, i;
	अक्षर *coldstr;
	Elf_Data *shndx_data = शून्य;
	Elf32_Word shndx;

	symtab = find_section_by_name(elf, ".symtab");
	अगर (!symtab) अणु
		/*
		 * A missing symbol table is actually possible अगर it's an empty
		 * .o file.  This can happen क्रम thunk_64.o.
		 */
		वापस 0;
	पूर्ण

	symtab_shndx = find_section_by_name(elf, ".symtab_shndx");
	अगर (symtab_shndx)
		shndx_data = symtab_shndx->data;

	symbols_nr = symtab->sh.sh_size / symtab->sh.sh_entsize;

	क्रम (i = 0; i < symbols_nr; i++) अणु
		sym = दो_स्मृति(माप(*sym));
		अगर (!sym) अणु
			लिखो_त्रुटि("malloc");
			वापस -1;
		पूर्ण
		स_रखो(sym, 0, माप(*sym));
		sym->alias = sym;

		sym->idx = i;

		अगर (!gelf_माला_लोymshndx(symtab->data, shndx_data, i, &sym->sym,
				      &shndx)) अणु
			WARN_ELF("gelf_getsymshndx");
			जाओ err;
		पूर्ण

		sym->name = elf_strptr(elf->elf, symtab->sh.sh_link,
				       sym->sym.st_name);
		अगर (!sym->name) अणु
			WARN_ELF("elf_strptr");
			जाओ err;
		पूर्ण

		अगर ((sym->sym.st_shndx > SHN_UNDEF &&
		     sym->sym.st_shndx < SHN_LORESERVE) ||
		    (shndx_data && sym->sym.st_shndx == SHN_XINDEX)) अणु
			अगर (sym->sym.st_shndx != SHN_XINDEX)
				shndx = sym->sym.st_shndx;

			sym->sec = find_section_by_index(elf, shndx);
			अगर (!sym->sec) अणु
				WARN("couldn't find section for symbol %s",
				     sym->name);
				जाओ err;
			पूर्ण
			अगर (GELF_ST_TYPE(sym->sym.st_info) == STT_SECTION) अणु
				sym->name = sym->sec->name;
				sym->sec->sym = sym;
			पूर्ण
		पूर्ण अन्यथा
			sym->sec = find_section_by_index(elf, 0);

		elf_add_symbol(elf, sym);
	पूर्ण

	अगर (stats)
		म_लिखो("nr_symbols: %lu\n", (अचिन्हित दीर्घ)symbols_nr);

	/* Create parent/child links क्रम any cold subfunctions */
	list_क्रम_each_entry(sec, &elf->sections, list) अणु
		list_क्रम_each_entry(sym, &sec->symbol_list, list) अणु
			अक्षर pname[MAX_NAME_LEN + 1];
			माप_प्रकार pnamelen;
			अगर (sym->type != STT_FUNC)
				जारी;

			अगर (sym->pfunc == शून्य)
				sym->pfunc = sym;

			अगर (sym->cfunc == शून्य)
				sym->cfunc = sym;

			coldstr = म_माला(sym->name, ".cold");
			अगर (!coldstr)
				जारी;

			pnamelen = coldstr - sym->name;
			अगर (pnamelen > MAX_NAME_LEN) अणु
				WARN("%s(): parent function name exceeds maximum length of %d characters",
				     sym->name, MAX_NAME_LEN);
				वापस -1;
			पूर्ण

			म_नकलन(pname, sym->name, pnamelen);
			pname[pnamelen] = '\0';
			pfunc = find_symbol_by_name(elf, pname);

			अगर (!pfunc) अणु
				WARN("%s(): can't find parent function",
				     sym->name);
				वापस -1;
			पूर्ण

			sym->pfunc = pfunc;
			pfunc->cfunc = sym;

			/*
			 * Unक्रमtunately, -fnoreorder-functions माला_दो the child
			 * inside the parent.  Remove the overlap so we can
			 * have sane assumptions.
			 *
			 * Note that pfunc->len now no दीर्घer matches
			 * pfunc->sym.st_size.
			 */
			अगर (sym->sec == pfunc->sec &&
			    sym->offset >= pfunc->offset &&
			    sym->offset + sym->len == pfunc->offset + pfunc->len) अणु
				pfunc->len -= sym->len;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err:
	मुक्त(sym);
	वापस -1;
पूर्ण

अटल काष्ठा section *elf_create_reloc_section(काष्ठा elf *elf,
						काष्ठा section *base,
						पूर्णांक reltype);

पूर्णांक elf_add_reloc(काष्ठा elf *elf, काष्ठा section *sec, अचिन्हित दीर्घ offset,
		  अचिन्हित पूर्णांक type, काष्ठा symbol *sym, पूर्णांक addend)
अणु
	काष्ठा reloc *reloc;

	अगर (!sec->reloc && !elf_create_reloc_section(elf, sec, SHT_RELA))
		वापस -1;

	reloc = दो_स्मृति(माप(*reloc));
	अगर (!reloc) अणु
		लिखो_त्रुटि("malloc");
		वापस -1;
	पूर्ण
	स_रखो(reloc, 0, माप(*reloc));

	reloc->sec = sec->reloc;
	reloc->offset = offset;
	reloc->type = type;
	reloc->sym = sym;
	reloc->addend = addend;

	list_add_tail(&reloc->list, &sec->reloc->reloc_list);
	elf_hash_add(elf->reloc_hash, &reloc->hash, reloc_hash(reloc));

	sec->reloc->changed = true;

	वापस 0;
पूर्ण

पूर्णांक elf_add_reloc_to_insn(काष्ठा elf *elf, काष्ठा section *sec,
			  अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक type,
			  काष्ठा section *insn_sec, अचिन्हित दीर्घ insn_off)
अणु
	काष्ठा symbol *sym;
	पूर्णांक addend;

	अगर (insn_sec->sym) अणु
		sym = insn_sec->sym;
		addend = insn_off;

	पूर्ण अन्यथा अणु
		/*
		 * The Clang assembler strips section symbols, so we have to
		 * reference the function symbol instead:
		 */
		sym = find_symbol_containing(insn_sec, insn_off);
		अगर (!sym) अणु
			/*
			 * Hack alert.  This happens when we need to reference
			 * the NOP pad insn immediately after the function.
			 */
			sym = find_symbol_containing(insn_sec, insn_off - 1);
		पूर्ण

		अगर (!sym) अणु
			WARN("can't find symbol containing %s+0x%lx", insn_sec->name, insn_off);
			वापस -1;
		पूर्ण

		addend = insn_off - sym->offset;
	पूर्ण

	वापस elf_add_reloc(elf, sec, offset, type, sym, addend);
पूर्ण

अटल पूर्णांक पढ़ो_rel_reloc(काष्ठा section *sec, पूर्णांक i, काष्ठा reloc *reloc, अचिन्हित पूर्णांक *symndx)
अणु
	अगर (!gelf_getrel(sec->data, i, &reloc->rel)) अणु
		WARN_ELF("gelf_getrel");
		वापस -1;
	पूर्ण
	reloc->type = GELF_R_TYPE(reloc->rel.r_info);
	reloc->addend = 0;
	reloc->offset = reloc->rel.r_offset;
	*symndx = GELF_R_SYM(reloc->rel.r_info);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_rela_reloc(काष्ठा section *sec, पूर्णांक i, काष्ठा reloc *reloc, अचिन्हित पूर्णांक *symndx)
अणु
	अगर (!gelf_getrela(sec->data, i, &reloc->rela)) अणु
		WARN_ELF("gelf_getrela");
		वापस -1;
	पूर्ण
	reloc->type = GELF_R_TYPE(reloc->rela.r_info);
	reloc->addend = reloc->rela.r_addend;
	reloc->offset = reloc->rela.r_offset;
	*symndx = GELF_R_SYM(reloc->rela.r_info);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_relocs(काष्ठा elf *elf)
अणु
	काष्ठा section *sec;
	काष्ठा reloc *reloc;
	पूर्णांक i;
	अचिन्हित पूर्णांक symndx;
	अचिन्हित दीर्घ nr_reloc, max_reloc = 0, tot_reloc = 0;

	list_क्रम_each_entry(sec, &elf->sections, list) अणु
		अगर ((sec->sh.sh_type != SHT_RELA) &&
		    (sec->sh.sh_type != SHT_REL))
			जारी;

		sec->base = find_section_by_index(elf, sec->sh.sh_info);
		अगर (!sec->base) अणु
			WARN("can't find base section for reloc section %s",
			     sec->name);
			वापस -1;
		पूर्ण

		sec->base->reloc = sec;

		nr_reloc = 0;
		क्रम (i = 0; i < sec->sh.sh_size / sec->sh.sh_entsize; i++) अणु
			reloc = दो_स्मृति(माप(*reloc));
			अगर (!reloc) अणु
				लिखो_त्रुटि("malloc");
				वापस -1;
			पूर्ण
			स_रखो(reloc, 0, माप(*reloc));
			चयन (sec->sh.sh_type) अणु
			हाल SHT_REL:
				अगर (पढ़ो_rel_reloc(sec, i, reloc, &symndx))
					वापस -1;
				अवरोध;
			हाल SHT_RELA:
				अगर (पढ़ो_rela_reloc(sec, i, reloc, &symndx))
					वापस -1;
				अवरोध;
			शेष: वापस -1;
			पूर्ण

			reloc->sec = sec;
			reloc->idx = i;
			reloc->sym = find_symbol_by_index(elf, symndx);
			अगर (!reloc->sym) अणु
				WARN("can't find reloc entry symbol %d for %s",
				     symndx, sec->name);
				वापस -1;
			पूर्ण

			list_add_tail(&reloc->list, &sec->reloc_list);
			elf_hash_add(elf->reloc_hash, &reloc->hash, reloc_hash(reloc));

			nr_reloc++;
		पूर्ण
		max_reloc = max(max_reloc, nr_reloc);
		tot_reloc += nr_reloc;
	पूर्ण

	अगर (stats) अणु
		म_लिखो("max_reloc: %lu\n", max_reloc);
		म_लिखो("tot_reloc: %lu\n", tot_reloc);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा elf *elf_खोलो_पढ़ो(स्थिर अक्षर *name, पूर्णांक flags)
अणु
	काष्ठा elf *elf;
	Elf_Cmd cmd;

	elf_version(EV_CURRENT);

	elf = दो_स्मृति(माप(*elf));
	अगर (!elf) अणु
		लिखो_त्रुटि("malloc");
		वापस शून्य;
	पूर्ण
	स_रखो(elf, 0, दुरत्व(काष्ठा elf, sections));

	INIT_LIST_HEAD(&elf->sections);

	elf_hash_init(elf->symbol_hash);
	elf_hash_init(elf->symbol_name_hash);
	elf_hash_init(elf->section_hash);
	elf_hash_init(elf->section_name_hash);
	elf_hash_init(elf->reloc_hash);

	elf->fd = खोलो(name, flags);
	अगर (elf->fd == -1) अणु
		ख_लिखो(मानक_त्रुटि, "objtool: Can't open '%s': %s\n",
			name, म_त्रुटि(त्रुटि_सं));
		जाओ err;
	पूर्ण

	अगर ((flags & O_ACCMODE) == O_RDONLY)
		cmd = ELF_C_READ_MMAP;
	अन्यथा अगर ((flags & O_ACCMODE) == O_RDWR)
		cmd = ELF_C_RDWR;
	अन्यथा /* O_WRONLY */
		cmd = ELF_C_WRITE;

	elf->elf = elf_begin(elf->fd, cmd, शून्य);
	अगर (!elf->elf) अणु
		WARN_ELF("elf_begin");
		जाओ err;
	पूर्ण

	अगर (!gelf_getehdr(elf->elf, &elf->ehdr)) अणु
		WARN_ELF("gelf_getehdr");
		जाओ err;
	पूर्ण

	अगर (पढ़ो_sections(elf))
		जाओ err;

	अगर (पढ़ो_symbols(elf))
		जाओ err;

	अगर (पढ़ो_relocs(elf))
		जाओ err;

	वापस elf;

err:
	elf_बंद(elf);
	वापस शून्य;
पूर्ण

अटल पूर्णांक elf_add_string(काष्ठा elf *elf, काष्ठा section *strtab, अक्षर *str)
अणु
	Elf_Data *data;
	Elf_Scn *s;
	पूर्णांक len;

	अगर (!strtab)
		strtab = find_section_by_name(elf, ".strtab");
	अगर (!strtab) अणु
		WARN("can't find .strtab section");
		वापस -1;
	पूर्ण

	s = elf_माला_लोcn(elf->elf, strtab->idx);
	अगर (!s) अणु
		WARN_ELF("elf_getscn");
		वापस -1;
	पूर्ण

	data = elf_newdata(s);
	अगर (!data) अणु
		WARN_ELF("elf_newdata");
		वापस -1;
	पूर्ण

	data->d_buf = str;
	data->d_size = म_माप(str) + 1;
	data->d_align = 1;

	len = strtab->len;
	strtab->len += data->d_size;
	strtab->changed = true;

	वापस len;
पूर्ण

काष्ठा symbol *elf_create_undef_symbol(काष्ठा elf *elf, स्थिर अक्षर *name)
अणु
	काष्ठा section *symtab, *symtab_shndx;
	काष्ठा symbol *sym;
	Elf_Data *data;
	Elf_Scn *s;

	sym = दो_स्मृति(माप(*sym));
	अगर (!sym) अणु
		लिखो_त्रुटि("malloc");
		वापस शून्य;
	पूर्ण
	स_रखो(sym, 0, माप(*sym));

	sym->name = strdup(name);

	sym->sym.st_name = elf_add_string(elf, शून्य, sym->name);
	अगर (sym->sym.st_name == -1)
		वापस शून्य;

	sym->sym.st_info = GELF_ST_INFO(STB_GLOBAL, STT_NOTYPE);
	// st_other 0
	// st_shndx 0
	// st_value 0
	// st_size 0

	symtab = find_section_by_name(elf, ".symtab");
	अगर (!symtab) अणु
		WARN("can't find .symtab");
		वापस शून्य;
	पूर्ण

	s = elf_माला_लोcn(elf->elf, symtab->idx);
	अगर (!s) अणु
		WARN_ELF("elf_getscn");
		वापस शून्य;
	पूर्ण

	data = elf_newdata(s);
	अगर (!data) अणु
		WARN_ELF("elf_newdata");
		वापस शून्य;
	पूर्ण

	data->d_buf = &sym->sym;
	data->d_size = माप(sym->sym);
	data->d_align = 1;
	data->d_type = ELF_T_SYM;

	sym->idx = symtab->len / माप(sym->sym);

	symtab->len += data->d_size;
	symtab->changed = true;

	symtab_shndx = find_section_by_name(elf, ".symtab_shndx");
	अगर (symtab_shndx) अणु
		s = elf_माला_लोcn(elf->elf, symtab_shndx->idx);
		अगर (!s) अणु
			WARN_ELF("elf_getscn");
			वापस शून्य;
		पूर्ण

		data = elf_newdata(s);
		अगर (!data) अणु
			WARN_ELF("elf_newdata");
			वापस शून्य;
		पूर्ण

		data->d_buf = &sym->sym.st_size; /* conveniently 0 */
		data->d_size = माप(Elf32_Word);
		data->d_align = 4;
		data->d_type = ELF_T_WORD;

		symtab_shndx->len += 4;
		symtab_shndx->changed = true;
	पूर्ण

	sym->sec = find_section_by_index(elf, 0);

	elf_add_symbol(elf, sym);

	वापस sym;
पूर्ण

काष्ठा section *elf_create_section(काष्ठा elf *elf, स्थिर अक्षर *name,
				   अचिन्हित पूर्णांक sh_flags, माप_प्रकार entsize, पूर्णांक nr)
अणु
	काष्ठा section *sec, *shstrtab;
	माप_प्रकार size = entsize * nr;
	Elf_Scn *s;

	sec = दो_स्मृति(माप(*sec));
	अगर (!sec) अणु
		लिखो_त्रुटि("malloc");
		वापस शून्य;
	पूर्ण
	स_रखो(sec, 0, माप(*sec));

	INIT_LIST_HEAD(&sec->symbol_list);
	INIT_LIST_HEAD(&sec->reloc_list);

	s = elf_newscn(elf->elf);
	अगर (!s) अणु
		WARN_ELF("elf_newscn");
		वापस शून्य;
	पूर्ण

	sec->name = strdup(name);
	अगर (!sec->name) अणु
		लिखो_त्रुटि("strdup");
		वापस शून्य;
	पूर्ण

	sec->idx = elf_ndxscn(s);
	sec->len = size;
	sec->changed = true;

	sec->data = elf_newdata(s);
	अगर (!sec->data) अणु
		WARN_ELF("elf_newdata");
		वापस शून्य;
	पूर्ण

	sec->data->d_size = size;
	sec->data->d_align = 1;

	अगर (size) अणु
		sec->data->d_buf = दो_स्मृति(size);
		अगर (!sec->data->d_buf) अणु
			लिखो_त्रुटि("malloc");
			वापस शून्य;
		पूर्ण
		स_रखो(sec->data->d_buf, 0, size);
	पूर्ण

	अगर (!gelf_माला_लोhdr(s, &sec->sh)) अणु
		WARN_ELF("gelf_getshdr");
		वापस शून्य;
	पूर्ण

	sec->sh.sh_size = size;
	sec->sh.sh_entsize = entsize;
	sec->sh.sh_type = SHT_PROGBITS;
	sec->sh.sh_addralign = 1;
	sec->sh.sh_flags = SHF_ALLOC | sh_flags;

	/* Add section name to .shstrtab (or .strtab क्रम Clang) */
	shstrtab = find_section_by_name(elf, ".shstrtab");
	अगर (!shstrtab)
		shstrtab = find_section_by_name(elf, ".strtab");
	अगर (!shstrtab) अणु
		WARN("can't find .shstrtab or .strtab section");
		वापस शून्य;
	पूर्ण
	sec->sh.sh_name = elf_add_string(elf, shstrtab, sec->name);
	अगर (sec->sh.sh_name == -1)
		वापस शून्य;

	list_add_tail(&sec->list, &elf->sections);
	elf_hash_add(elf->section_hash, &sec->hash, sec->idx);
	elf_hash_add(elf->section_name_hash, &sec->name_hash, str_hash(sec->name));

	elf->changed = true;

	वापस sec;
पूर्ण

अटल काष्ठा section *elf_create_rel_reloc_section(काष्ठा elf *elf, काष्ठा section *base)
अणु
	अक्षर *relocname;
	काष्ठा section *sec;

	relocname = दो_स्मृति(म_माप(base->name) + म_माप(".rel") + 1);
	अगर (!relocname) अणु
		लिखो_त्रुटि("malloc");
		वापस शून्य;
	पूर्ण
	म_नकल(relocname, ".rel");
	म_जोड़ो(relocname, base->name);

	sec = elf_create_section(elf, relocname, 0, माप(GElf_Rel), 0);
	मुक्त(relocname);
	अगर (!sec)
		वापस शून्य;

	base->reloc = sec;
	sec->base = base;

	sec->sh.sh_type = SHT_REL;
	sec->sh.sh_addralign = 8;
	sec->sh.sh_link = find_section_by_name(elf, ".symtab")->idx;
	sec->sh.sh_info = base->idx;
	sec->sh.sh_flags = SHF_INFO_LINK;

	वापस sec;
पूर्ण

अटल काष्ठा section *elf_create_rela_reloc_section(काष्ठा elf *elf, काष्ठा section *base)
अणु
	अक्षर *relocname;
	काष्ठा section *sec;

	relocname = दो_स्मृति(म_माप(base->name) + म_माप(".rela") + 1);
	अगर (!relocname) अणु
		लिखो_त्रुटि("malloc");
		वापस शून्य;
	पूर्ण
	म_नकल(relocname, ".rela");
	म_जोड़ो(relocname, base->name);

	sec = elf_create_section(elf, relocname, 0, माप(GElf_Rela), 0);
	मुक्त(relocname);
	अगर (!sec)
		वापस शून्य;

	base->reloc = sec;
	sec->base = base;

	sec->sh.sh_type = SHT_RELA;
	sec->sh.sh_addralign = 8;
	sec->sh.sh_link = find_section_by_name(elf, ".symtab")->idx;
	sec->sh.sh_info = base->idx;
	sec->sh.sh_flags = SHF_INFO_LINK;

	वापस sec;
पूर्ण

अटल काष्ठा section *elf_create_reloc_section(काष्ठा elf *elf,
					 काष्ठा section *base,
					 पूर्णांक reltype)
अणु
	चयन (reltype) अणु
	हाल SHT_REL:  वापस elf_create_rel_reloc_section(elf, base);
	हाल SHT_RELA: वापस elf_create_rela_reloc_section(elf, base);
	शेष:       वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक elf_rebuild_rel_reloc_section(काष्ठा section *sec, पूर्णांक nr)
अणु
	काष्ठा reloc *reloc;
	पूर्णांक idx = 0, size;
	व्योम *buf;

	/* Allocate a buffer क्रम relocations */
	size = nr * माप(GElf_Rel);
	buf = दो_स्मृति(size);
	अगर (!buf) अणु
		लिखो_त्रुटि("malloc");
		वापस -1;
	पूर्ण

	sec->data->d_buf = buf;
	sec->data->d_size = size;
	sec->data->d_type = ELF_T_REL;

	sec->sh.sh_size = size;

	idx = 0;
	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		reloc->rel.r_offset = reloc->offset;
		reloc->rel.r_info = GELF_R_INFO(reloc->sym->idx, reloc->type);
		gelf_update_rel(sec->data, idx, &reloc->rel);
		idx++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elf_rebuild_rela_reloc_section(काष्ठा section *sec, पूर्णांक nr)
अणु
	काष्ठा reloc *reloc;
	पूर्णांक idx = 0, size;
	व्योम *buf;

	/* Allocate a buffer क्रम relocations with addends */
	size = nr * माप(GElf_Rela);
	buf = दो_स्मृति(size);
	अगर (!buf) अणु
		लिखो_त्रुटि("malloc");
		वापस -1;
	पूर्ण

	sec->data->d_buf = buf;
	sec->data->d_size = size;
	sec->data->d_type = ELF_T_RELA;

	sec->sh.sh_size = size;

	idx = 0;
	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		reloc->rela.r_offset = reloc->offset;
		reloc->rela.r_addend = reloc->addend;
		reloc->rela.r_info = GELF_R_INFO(reloc->sym->idx, reloc->type);
		gelf_update_rela(sec->data, idx, &reloc->rela);
		idx++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elf_rebuild_reloc_section(काष्ठा elf *elf, काष्ठा section *sec)
अणु
	काष्ठा reloc *reloc;
	पूर्णांक nr;

	nr = 0;
	list_क्रम_each_entry(reloc, &sec->reloc_list, list)
		nr++;

	चयन (sec->sh.sh_type) अणु
	हाल SHT_REL:  वापस elf_rebuild_rel_reloc_section(sec, nr);
	हाल SHT_RELA: वापस elf_rebuild_rela_reloc_section(sec, nr);
	शेष:       वापस -1;
	पूर्ण
पूर्ण

पूर्णांक elf_ग_लिखो_insn(काष्ठा elf *elf, काष्ठा section *sec,
		   अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक len,
		   स्थिर अक्षर *insn)
अणु
	Elf_Data *data = sec->data;

	अगर (data->d_type != ELF_T_BYTE || data->d_off) अणु
		WARN("write to unexpected data for section: %s", sec->name);
		वापस -1;
	पूर्ण

	स_नकल(data->d_buf + offset, insn, len);
	elf_flagdata(data, ELF_C_SET, ELF_F_सूचीTY);

	elf->changed = true;

	वापस 0;
पूर्ण

पूर्णांक elf_ग_लिखो_reloc(काष्ठा elf *elf, काष्ठा reloc *reloc)
अणु
	काष्ठा section *sec = reloc->sec;

	अगर (sec->sh.sh_type == SHT_REL) अणु
		reloc->rel.r_info = GELF_R_INFO(reloc->sym->idx, reloc->type);
		reloc->rel.r_offset = reloc->offset;

		अगर (!gelf_update_rel(sec->data, reloc->idx, &reloc->rel)) अणु
			WARN_ELF("gelf_update_rel");
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		reloc->rela.r_info = GELF_R_INFO(reloc->sym->idx, reloc->type);
		reloc->rela.r_addend = reloc->addend;
		reloc->rela.r_offset = reloc->offset;

		अगर (!gelf_update_rela(sec->data, reloc->idx, &reloc->rela)) अणु
			WARN_ELF("gelf_update_rela");
			वापस -1;
		पूर्ण
	पूर्ण

	elf->changed = true;

	वापस 0;
पूर्ण

पूर्णांक elf_ग_लिखो(काष्ठा elf *elf)
अणु
	काष्ठा section *sec;
	Elf_Scn *s;

	/* Update changed relocation sections and section headers: */
	list_क्रम_each_entry(sec, &elf->sections, list) अणु
		अगर (sec->changed) अणु
			अगर (sec->base &&
			    elf_rebuild_reloc_section(elf, sec)) अणु
				WARN("elf_rebuild_reloc_section");
				वापस -1;
			पूर्ण

			s = elf_माला_लोcn(elf->elf, sec->idx);
			अगर (!s) अणु
				WARN_ELF("elf_getscn");
				वापस -1;
			पूर्ण
			अगर (!gelf_update_shdr(s, &sec->sh)) अणु
				WARN_ELF("gelf_update_shdr");
				वापस -1;
			पूर्ण

			sec->changed = false;
			elf->changed = true;
		पूर्ण
	पूर्ण

	/* Make sure the new section header entries get updated properly. */
	elf_flagelf(elf->elf, ELF_C_SET, ELF_F_सूचीTY);

	/* Write all changes to the file. */
	अगर (elf_update(elf->elf, ELF_C_WRITE) < 0) अणु
		WARN_ELF("elf_update");
		वापस -1;
	पूर्ण

	elf->changed = false;

	वापस 0;
पूर्ण

व्योम elf_बंद(काष्ठा elf *elf)
अणु
	काष्ठा section *sec, *पंचांगpsec;
	काष्ठा symbol *sym, *पंचांगpsym;
	काष्ठा reloc *reloc, *पंचांगpreloc;

	अगर (elf->elf)
		elf_end(elf->elf);

	अगर (elf->fd > 0)
		बंद(elf->fd);

	list_क्रम_each_entry_safe(sec, पंचांगpsec, &elf->sections, list) अणु
		list_क्रम_each_entry_safe(sym, पंचांगpsym, &sec->symbol_list, list) अणु
			list_del(&sym->list);
			hash_del(&sym->hash);
			मुक्त(sym);
		पूर्ण
		list_क्रम_each_entry_safe(reloc, पंचांगpreloc, &sec->reloc_list, list) अणु
			list_del(&reloc->list);
			hash_del(&reloc->hash);
			मुक्त(reloc);
		पूर्ण
		list_del(&sec->list);
		मुक्त(sec);
	पूर्ण

	मुक्त(elf);
पूर्ण
