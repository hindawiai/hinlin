<शैली गुरु>
/* Postprocess module symbol versions
 *
 * Copyright 2003       Kai Germaschewski
 * Copyright 2002-2004  Rusty Russell, IBM Corporation
 * Copyright 2006-2008  Sam Ravnborg
 * Based in part on module-init-tools/depmod.c,file2alias
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 * Usage: modpost vmlinux module1.o module2.o ...
 */

#घोषणा _GNU_SOURCE
#समावेश <elf.h>
#समावेश <मानकपन.स>
#समावेश <प्रकार.स>
#समावेश <माला.स>
#समावेश <सीमा.स>
#समावेश <त्रुटिसं.स>
#समावेश "modpost.h"
#समावेश "../../include/linux/license.h"

/* Are we using CONFIG_MODVERSIONS? */
अटल पूर्णांक modversions = 0;
/* Is CONFIG_MODULE_SRCVERSION_ALL set? */
अटल पूर्णांक all_versions = 0;
/* If we are modposting बाह्यal module set to 1 */
अटल पूर्णांक बाह्यal_module = 0;
/* Only warn about unresolved symbols */
अटल पूर्णांक warn_unresolved = 0;
/* How a symbol is exported */
अटल पूर्णांक sec_mismatch_count = 0;
अटल पूर्णांक sec_mismatch_warn_only = true;
/* ignore missing files */
अटल पूर्णांक ignore_missing_files;
/* If set to 1, only warn (instead of error) about missing ns imports */
अटल पूर्णांक allow_missing_ns_imports;

अटल bool error_occurred;

/*
 * Cut off the warnings when there are too many. This typically occurs when
 * vmlinux is missing. ('make modules' without building vmlinux.)
 */
#घोषणा MAX_UNRESOLVED_REPORTS	10
अटल अचिन्हित पूर्णांक nr_unresolved;

क्रमागत export अणु
	export_plain,
	export_gpl,
	export_unknown
पूर्ण;

/* In kernel, this size is defined in linux/module.h;
 * here we use Elf_Addr instead of दीर्घ क्रम covering cross-compile
 */

#घोषणा MODULE_NAME_LEN (64 - माप(Elf_Addr))

व्योम __attribute__((क्रमmat(म_लिखो, 2, 3)))
modpost_log(क्रमागत loglevel loglevel, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची arglist;

	चयन (loglevel) अणु
	हाल LOG_WARN:
		ख_लिखो(मानक_त्रुटि, "WARNING: ");
		अवरोध;
	हाल LOG_ERROR:
		ख_लिखो(मानक_त्रुटि, "ERROR: ");
		अवरोध;
	हाल LOG_FATAL:
		ख_लिखो(मानक_त्रुटि, "FATAL: ");
		अवरोध;
	शेष: /* invalid loglevel, ignore */
		अवरोध;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "modpost: ");

	बहु_शुरू(arglist, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, arglist);
	बहु_पूर्ण(arglist);

	अगर (loglevel == LOG_FATAL)
		निकास(1);
	अगर (loglevel == LOG_ERROR)
		error_occurred = true;
पूर्ण

व्योम *करो_nofail(व्योम *ptr, स्थिर अक्षर *expr)
अणु
	अगर (!ptr)
		fatal("Memory allocation failure: %s.\n", expr);

	वापस ptr;
पूर्ण

अक्षर *पढ़ो_text_file(स्थिर अक्षर *filename)
अणु
	काष्ठा stat st;
	माप_प्रकार nbytes;
	पूर्णांक fd;
	अक्षर *buf;

	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0) अणु
		लिखो_त्रुटि(filename);
		निकास(1);
	पूर्ण

	अगर (ख_स्थिति(fd, &st) < 0) अणु
		लिखो_त्रुटि(filename);
		निकास(1);
	पूर्ण

	buf = NOFAIL(दो_स्मृति(st.st_size + 1));

	nbytes = st.st_size;

	जबतक (nbytes) अणु
		sमाप_प्रकार bytes_पढ़ो;

		bytes_पढ़ो = पढ़ो(fd, buf, nbytes);
		अगर (bytes_पढ़ो < 0) अणु
			लिखो_त्रुटि(filename);
			निकास(1);
		पूर्ण

		nbytes -= bytes_पढ़ो;
	पूर्ण
	buf[st.st_size] = '\0';

	बंद(fd);

	वापस buf;
पूर्ण

अक्षर *get_line(अक्षर **stringp)
अणु
	अक्षर *orig = *stringp, *next;

	/* करो not वापस the unwanted extra line at खातापूर्ण */
	अगर (!orig || *orig == '\0')
		वापस शून्य;

	/* करोn't use strsep here, it is not available everywhere */
	next = म_अक्षर(orig, '\n');
	अगर (next)
		*next++ = '\0';

	*stringp = next;

	वापस orig;
पूर्ण

/* A list of all modules we processed */
अटल काष्ठा module *modules;

अटल काष्ठा module *find_module(स्थिर अक्षर *modname)
अणु
	काष्ठा module *mod;

	क्रम (mod = modules; mod; mod = mod->next)
		अगर (म_भेद(mod->name, modname) == 0)
			अवरोध;
	वापस mod;
पूर्ण

अटल काष्ठा module *new_module(स्थिर अक्षर *modname)
अणु
	काष्ठा module *mod;

	mod = NOFAIL(दो_स्मृति(माप(*mod) + म_माप(modname) + 1));
	स_रखो(mod, 0, माप(*mod));

	/* add to list */
	म_नकल(mod->name, modname);
	mod->is_vmlinux = (म_भेद(modname, "vmlinux") == 0);
	mod->gpl_compatible = -1;
	mod->next = modules;
	modules = mod;

	वापस mod;
पूर्ण

/* A hash of all exported symbols,
 * काष्ठा symbol is also used क्रम lists of unresolved symbols */

#घोषणा SYMBOL_HASH_SIZE 1024

काष्ठा symbol अणु
	काष्ठा symbol *next;
	काष्ठा module *module;
	अचिन्हित पूर्णांक crc;
	पूर्णांक crc_valid;
	अक्षर *namespace;
	अचिन्हित पूर्णांक weak:1;
	अचिन्हित पूर्णांक is_अटल:1;  /* 1 अगर symbol is not global */
	क्रमागत export  export;       /* Type of export */
	अक्षर name[];
पूर्ण;

अटल काष्ठा symbol *symbolhash[SYMBOL_HASH_SIZE];

/* This is based on the hash algorithm from gdbm, via tdb */
अटल अंतरभूत अचिन्हित पूर्णांक tdb_hash(स्थिर अक्षर *name)
अणु
	अचिन्हित value;	/* Used to compute the hash value.  */
	अचिन्हित   i;	/* Used to cycle through अक्रमom values. */

	/* Set the initial value from the key size. */
	क्रम (value = 0x238F13AF * म_माप(name), i = 0; name[i]; i++)
		value = (value + (((अचिन्हित अक्षर *)name)[i] << (i*5 % 24)));

	वापस (1103515243 * value + 12345);
पूर्ण

/**
 * Allocate a new symbols क्रम use in the hash of exported symbols or
 * the list of unresolved symbols per module
 **/
अटल काष्ठा symbol *alloc_symbol(स्थिर अक्षर *name, अचिन्हित पूर्णांक weak,
				   काष्ठा symbol *next)
अणु
	काष्ठा symbol *s = NOFAIL(दो_स्मृति(माप(*s) + म_माप(name) + 1));

	स_रखो(s, 0, माप(*s));
	म_नकल(s->name, name);
	s->weak = weak;
	s->next = next;
	s->is_अटल = 1;
	वापस s;
पूर्ण

/* For the hash of exported symbols */
अटल काष्ठा symbol *new_symbol(स्थिर अक्षर *name, काष्ठा module *module,
				 क्रमागत export export)
अणु
	अचिन्हित पूर्णांक hash;

	hash = tdb_hash(name) % SYMBOL_HASH_SIZE;
	symbolhash[hash] = alloc_symbol(name, 0, symbolhash[hash]);

	वापस symbolhash[hash];
पूर्ण

अटल काष्ठा symbol *find_symbol(स्थिर अक्षर *name)
अणु
	काष्ठा symbol *s;

	/* For our purposes, .foo matches foo.  PPC64 needs this. */
	अगर (name[0] == '.')
		name++;

	क्रम (s = symbolhash[tdb_hash(name) % SYMBOL_HASH_SIZE]; s; s = s->next) अणु
		अगर (म_भेद(s->name, name) == 0)
			वापस s;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool contains_namespace(काष्ठा namespace_list *list,
			       स्थिर अक्षर *namespace)
अणु
	क्रम (; list; list = list->next)
		अगर (!म_भेद(list->namespace, namespace))
			वापस true;

	वापस false;
पूर्ण

अटल व्योम add_namespace(काष्ठा namespace_list **list, स्थिर अक्षर *namespace)
अणु
	काष्ठा namespace_list *ns_entry;

	अगर (!contains_namespace(*list, namespace)) अणु
		ns_entry = NOFAIL(दो_स्मृति(माप(काष्ठा namespace_list) +
					 म_माप(namespace) + 1));
		म_नकल(ns_entry->namespace, namespace);
		ns_entry->next = *list;
		*list = ns_entry;
	पूर्ण
पूर्ण

अटल bool module_imports_namespace(काष्ठा module *module,
				     स्थिर अक्षर *namespace)
अणु
	वापस contains_namespace(module->imported_namespaces, namespace);
पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *str;
	क्रमागत export export;
पूर्ण export_list[] = अणु
	अणु .str = "EXPORT_SYMBOL",            .export = export_plain पूर्ण,
	अणु .str = "EXPORT_SYMBOL_GPL",        .export = export_gpl पूर्ण,
	अणु .str = "(unknown)",                .export = export_unknown पूर्ण,
पूर्ण;


अटल स्थिर अक्षर *export_str(क्रमागत export ex)
अणु
	वापस export_list[ex].str;
पूर्ण

अटल क्रमागत export export_no(स्थिर अक्षर *s)
अणु
	पूर्णांक i;

	अगर (!s)
		वापस export_unknown;
	क्रम (i = 0; export_list[i].export != export_unknown; i++) अणु
		अगर (म_भेद(export_list[i].str, s) == 0)
			वापस export_list[i].export;
	पूर्ण
	वापस export_unknown;
पूर्ण

अटल व्योम *sym_get_data_by_offset(स्थिर काष्ठा elf_info *info,
				    अचिन्हित पूर्णांक secindex, अचिन्हित दीर्घ offset)
अणु
	Elf_Shdr *sechdr = &info->sechdrs[secindex];

	अगर (info->hdr->e_type != ET_REL)
		offset -= sechdr->sh_addr;

	वापस (व्योम *)info->hdr + sechdr->sh_offset + offset;
पूर्ण

अटल व्योम *sym_get_data(स्थिर काष्ठा elf_info *info, स्थिर Elf_Sym *sym)
अणु
	वापस sym_get_data_by_offset(info, get_secindex(info, sym),
				      sym->st_value);
पूर्ण

अटल स्थिर अक्षर *sech_name(स्थिर काष्ठा elf_info *info, Elf_Shdr *sechdr)
अणु
	वापस sym_get_data_by_offset(info, info->secindex_strings,
				      sechdr->sh_name);
पूर्ण

अटल स्थिर अक्षर *sec_name(स्थिर काष्ठा elf_info *info, पूर्णांक secindex)
अणु
	वापस sech_name(info, &info->sechdrs[secindex]);
पूर्ण

#घोषणा strstarts(str, prefix) (म_भेदन(str, prefix, म_माप(prefix)) == 0)

अटल क्रमागत export export_from_secname(काष्ठा elf_info *elf, अचिन्हित पूर्णांक sec)
अणु
	स्थिर अक्षर *secname = sec_name(elf, sec);

	अगर (strstarts(secname, "___ksymtab+"))
		वापस export_plain;
	अन्यथा अगर (strstarts(secname, "___ksymtab_gpl+"))
		वापस export_gpl;
	अन्यथा
		वापस export_unknown;
पूर्ण

अटल क्रमागत export export_from_sec(काष्ठा elf_info *elf, अचिन्हित पूर्णांक sec)
अणु
	अगर (sec == elf->export_sec)
		वापस export_plain;
	अन्यथा अगर (sec == elf->export_gpl_sec)
		वापस export_gpl;
	अन्यथा
		वापस export_unknown;
पूर्ण

अटल स्थिर अक्षर *namespace_from_kstrtabns(स्थिर काष्ठा elf_info *info,
					    स्थिर Elf_Sym *sym)
अणु
	स्थिर अक्षर *value = sym_get_data(info, sym);
	वापस value[0] ? value : शून्य;
पूर्ण

अटल व्योम sym_update_namespace(स्थिर अक्षर *symname, स्थिर अक्षर *namespace)
अणु
	काष्ठा symbol *s = find_symbol(symname);

	/*
	 * That symbol should have been created earlier and thus this is
	 * actually an निश्चितion.
	 */
	अगर (!s) अणु
		error("Could not update namespace(%s) for symbol %s\n",
		      namespace, symname);
		वापस;
	पूर्ण

	मुक्त(s->namespace);
	s->namespace =
		namespace && namespace[0] ? NOFAIL(strdup(namespace)) : शून्य;
पूर्ण

/**
 * Add an exported symbol - it may have alपढ़ोy been added without a
 * CRC, in this हाल just update the CRC
 **/
अटल काष्ठा symbol *sym_add_exported(स्थिर अक्षर *name, काष्ठा module *mod,
				       क्रमागत export export)
अणु
	काष्ठा symbol *s = find_symbol(name);

	अगर (!s) अणु
		s = new_symbol(name, mod, export);
	पूर्ण अन्यथा अगर (!बाह्यal_module || s->module->is_vmlinux ||
		   s->module == mod) अणु
		warn("%s: '%s' exported twice. Previous export was in %s%s\n",
		     mod->name, name, s->module->name,
		     s->module->is_vmlinux ? "" : ".ko");
		वापस s;
	पूर्ण

	s->module = mod;
	s->export    = export;
	वापस s;
पूर्ण

अटल व्योम sym_set_crc(स्थिर अक्षर *name, अचिन्हित पूर्णांक crc)
अणु
	काष्ठा symbol *s = find_symbol(name);

	/*
	 * Ignore stand-alone __crc_*, which might be स्वतः-generated symbols
	 * such as __*_veneer in ARM ELF.
	 */
	अगर (!s)
		वापस;

	s->crc = crc;
	s->crc_valid = 1;
पूर्ण

अटल व्योम *grab_file(स्थिर अक्षर *filename, माप_प्रकार *size)
अणु
	काष्ठा stat st;
	व्योम *map = MAP_FAILED;
	पूर्णांक fd;

	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0)
		वापस शून्य;
	अगर (ख_स्थिति(fd, &st))
		जाओ failed;

	*size = st.st_size;
	map = mmap(शून्य, *size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);

failed:
	बंद(fd);
	अगर (map == MAP_FAILED)
		वापस शून्य;
	वापस map;
पूर्ण

अटल व्योम release_file(व्योम *file, माप_प्रकार size)
अणु
	munmap(file, size);
पूर्ण

अटल पूर्णांक parse_elf(काष्ठा elf_info *info, स्थिर अक्षर *filename)
अणु
	अचिन्हित पूर्णांक i;
	Elf_Ehdr *hdr;
	Elf_Shdr *sechdrs;
	Elf_Sym  *sym;
	स्थिर अक्षर *secstrings;
	अचिन्हित पूर्णांक symtab_idx = ~0U, symtab_shndx_idx = ~0U;

	hdr = grab_file(filename, &info->size);
	अगर (!hdr) अणु
		अगर (ignore_missing_files) अणु
			ख_लिखो(मानक_त्रुटि, "%s: %s (ignored)\n", filename,
				म_त्रुटि(त्रुटि_सं));
			वापस 0;
		पूर्ण
		लिखो_त्रुटि(filename);
		निकास(1);
	पूर्ण
	info->hdr = hdr;
	अगर (info->size < माप(*hdr)) अणु
		/* file too small, assume this is an empty .o file */
		वापस 0;
	पूर्ण
	/* Is this a valid ELF file? */
	अगर ((hdr->e_ident[EI_MAG0] != ELFMAG0) ||
	    (hdr->e_ident[EI_MAG1] != ELFMAG1) ||
	    (hdr->e_ident[EI_MAG2] != ELFMAG2) ||
	    (hdr->e_ident[EI_MAG3] != ELFMAG3)) अणु
		/* Not an ELF file - silently ignore it */
		वापस 0;
	पूर्ण
	/* Fix endianness in ELF header */
	hdr->e_type      = TO_NATIVE(hdr->e_type);
	hdr->e_machine   = TO_NATIVE(hdr->e_machine);
	hdr->e_version   = TO_NATIVE(hdr->e_version);
	hdr->e_entry     = TO_NATIVE(hdr->e_entry);
	hdr->e_phoff     = TO_NATIVE(hdr->e_phoff);
	hdr->e_shoff     = TO_NATIVE(hdr->e_shoff);
	hdr->e_flags     = TO_NATIVE(hdr->e_flags);
	hdr->e_ehsize    = TO_NATIVE(hdr->e_ehsize);
	hdr->e_phentsize = TO_NATIVE(hdr->e_phentsize);
	hdr->e_phnum     = TO_NATIVE(hdr->e_phnum);
	hdr->e_shentsize = TO_NATIVE(hdr->e_shentsize);
	hdr->e_shnum     = TO_NATIVE(hdr->e_shnum);
	hdr->e_shstrndx  = TO_NATIVE(hdr->e_shstrndx);
	sechdrs = (व्योम *)hdr + hdr->e_shoff;
	info->sechdrs = sechdrs;

	/* Check अगर file offset is correct */
	अगर (hdr->e_shoff > info->size) अणु
		fatal("section header offset=%lu in file '%s' is bigger than filesize=%zu\n",
		      (अचिन्हित दीर्घ)hdr->e_shoff, filename, info->size);
		वापस 0;
	पूर्ण

	अगर (hdr->e_shnum == SHN_UNDEF) अणु
		/*
		 * There are more than 64k sections,
		 * पढ़ो count from .sh_size.
		 */
		info->num_sections = TO_NATIVE(sechdrs[0].sh_size);
	पूर्ण
	अन्यथा अणु
		info->num_sections = hdr->e_shnum;
	पूर्ण
	अगर (hdr->e_shstrndx == SHN_XINDEX) अणु
		info->secindex_strings = TO_NATIVE(sechdrs[0].sh_link);
	पूर्ण
	अन्यथा अणु
		info->secindex_strings = hdr->e_shstrndx;
	पूर्ण

	/* Fix endianness in section headers */
	क्रम (i = 0; i < info->num_sections; i++) अणु
		sechdrs[i].sh_name      = TO_NATIVE(sechdrs[i].sh_name);
		sechdrs[i].sh_type      = TO_NATIVE(sechdrs[i].sh_type);
		sechdrs[i].sh_flags     = TO_NATIVE(sechdrs[i].sh_flags);
		sechdrs[i].sh_addr      = TO_NATIVE(sechdrs[i].sh_addr);
		sechdrs[i].sh_offset    = TO_NATIVE(sechdrs[i].sh_offset);
		sechdrs[i].sh_size      = TO_NATIVE(sechdrs[i].sh_size);
		sechdrs[i].sh_link      = TO_NATIVE(sechdrs[i].sh_link);
		sechdrs[i].sh_info      = TO_NATIVE(sechdrs[i].sh_info);
		sechdrs[i].sh_addralign = TO_NATIVE(sechdrs[i].sh_addralign);
		sechdrs[i].sh_entsize   = TO_NATIVE(sechdrs[i].sh_entsize);
	पूर्ण
	/* Find symbol table. */
	secstrings = (व्योम *)hdr + sechdrs[info->secindex_strings].sh_offset;
	क्रम (i = 1; i < info->num_sections; i++) अणु
		स्थिर अक्षर *secname;
		पूर्णांक nobits = sechdrs[i].sh_type == SHT_NOBITS;

		अगर (!nobits && sechdrs[i].sh_offset > info->size) अणु
			fatal("%s is truncated. sechdrs[i].sh_offset=%lu > "
			      "sizeof(*hrd)=%zu\n", filename,
			      (अचिन्हित दीर्घ)sechdrs[i].sh_offset,
			      माप(*hdr));
			वापस 0;
		पूर्ण
		secname = secstrings + sechdrs[i].sh_name;
		अगर (म_भेद(secname, ".modinfo") == 0) अणु
			अगर (nobits)
				fatal("%s has NOBITS .modinfo\n", filename);
			info->modinfo = (व्योम *)hdr + sechdrs[i].sh_offset;
			info->modinfo_len = sechdrs[i].sh_size;
		पूर्ण अन्यथा अगर (म_भेद(secname, "__ksymtab") == 0)
			info->export_sec = i;
		अन्यथा अगर (म_भेद(secname, "__ksymtab_gpl") == 0)
			info->export_gpl_sec = i;

		अगर (sechdrs[i].sh_type == SHT_SYMTAB) अणु
			अचिन्हित पूर्णांक sh_link_idx;
			symtab_idx = i;
			info->symtab_start = (व्योम *)hdr +
			    sechdrs[i].sh_offset;
			info->symtab_stop  = (व्योम *)hdr +
			    sechdrs[i].sh_offset + sechdrs[i].sh_size;
			sh_link_idx = sechdrs[i].sh_link;
			info->strtab       = (व्योम *)hdr +
			    sechdrs[sh_link_idx].sh_offset;
		पूर्ण

		/* 32bit section no. table? ("more than 64k sections") */
		अगर (sechdrs[i].sh_type == SHT_SYMTAB_SHNDX) अणु
			symtab_shndx_idx = i;
			info->symtab_shndx_start = (व्योम *)hdr +
			    sechdrs[i].sh_offset;
			info->symtab_shndx_stop  = (व्योम *)hdr +
			    sechdrs[i].sh_offset + sechdrs[i].sh_size;
		पूर्ण
	पूर्ण
	अगर (!info->symtab_start)
		fatal("%s has no symtab?\n", filename);

	/* Fix endianness in symbols */
	क्रम (sym = info->symtab_start; sym < info->symtab_stop; sym++) अणु
		sym->st_shndx = TO_NATIVE(sym->st_shndx);
		sym->st_name  = TO_NATIVE(sym->st_name);
		sym->st_value = TO_NATIVE(sym->st_value);
		sym->st_size  = TO_NATIVE(sym->st_size);
	पूर्ण

	अगर (symtab_shndx_idx != ~0U) अणु
		Elf32_Word *p;
		अगर (symtab_idx != sechdrs[symtab_shndx_idx].sh_link)
			fatal("%s: SYMTAB_SHNDX has bad sh_link: %u!=%u\n",
			      filename, sechdrs[symtab_shndx_idx].sh_link,
			      symtab_idx);
		/* Fix endianness */
		क्रम (p = info->symtab_shndx_start; p < info->symtab_shndx_stop;
		     p++)
			*p = TO_NATIVE(*p);
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम parse_elf_finish(काष्ठा elf_info *info)
अणु
	release_file(info->hdr, info->size);
पूर्ण

अटल पूर्णांक ignore_undef_symbol(काष्ठा elf_info *info, स्थिर अक्षर *symname)
अणु
	/* ignore __this_module, it will be resolved लघुly */
	अगर (म_भेद(symname, "__this_module") == 0)
		वापस 1;
	/* ignore global offset table */
	अगर (म_भेद(symname, "_GLOBAL_OFFSET_TABLE_") == 0)
		वापस 1;
	अगर (info->hdr->e_machine == EM_PPC)
		/* Special रेजिस्टर function linked on all modules during final link of .ko */
		अगर (strstarts(symname, "_restgpr_") ||
		    strstarts(symname, "_savegpr_") ||
		    strstarts(symname, "_rest32gpr_") ||
		    strstarts(symname, "_save32gpr_") ||
		    strstarts(symname, "_restvr_") ||
		    strstarts(symname, "_savevr_"))
			वापस 1;
	अगर (info->hdr->e_machine == EM_PPC64)
		/* Special रेजिस्टर function linked on all modules during final link of .ko */
		अगर (strstarts(symname, "_restgpr0_") ||
		    strstarts(symname, "_savegpr0_") ||
		    strstarts(symname, "_restvr_") ||
		    strstarts(symname, "_savevr_") ||
		    म_भेद(symname, ".TOC.") == 0)
			वापस 1;
	/* Do not ignore this symbol */
	वापस 0;
पूर्ण

अटल व्योम handle_modversion(स्थिर काष्ठा module *mod,
			      स्थिर काष्ठा elf_info *info,
			      स्थिर Elf_Sym *sym, स्थिर अक्षर *symname)
अणु
	अचिन्हित पूर्णांक crc;

	अगर (sym->st_shndx == SHN_UNDEF) अणु
		warn("EXPORT symbol \"%s\" [%s%s] version generation failed, symbol will not be versioned.\n",
		     symname, mod->name, mod->is_vmlinux ? "" : ".ko");
		वापस;
	पूर्ण

	अगर (sym->st_shndx == SHN_ABS) अणु
		crc = sym->st_value;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक *crcp;

		/* symbol poपूर्णांकs to the CRC in the ELF object */
		crcp = sym_get_data(info, sym);
		crc = TO_NATIVE(*crcp);
	पूर्ण
	sym_set_crc(symname, crc);
पूर्ण

अटल व्योम handle_symbol(काष्ठा module *mod, काष्ठा elf_info *info,
			  स्थिर Elf_Sym *sym, स्थिर अक्षर *symname)
अणु
	क्रमागत export export;
	स्थिर अक्षर *name;

	अगर (strstarts(symname, "__ksymtab"))
		export = export_from_secname(info, get_secindex(info, sym));
	अन्यथा
		export = export_from_sec(info, get_secindex(info, sym));

	चयन (sym->st_shndx) अणु
	हाल SHN_COMMON:
		अगर (strstarts(symname, "__gnu_lto_")) अणु
			/* Should warn here, but modpost runs beक्रमe the linker */
		पूर्ण अन्यथा
			warn("\"%s\" [%s] is COMMON symbol\n", symname, mod->name);
		अवरोध;
	हाल SHN_UNDEF:
		/* undefined symbol */
		अगर (ELF_ST_BIND(sym->st_info) != STB_GLOBAL &&
		    ELF_ST_BIND(sym->st_info) != STB_WEAK)
			अवरोध;
		अगर (ignore_undef_symbol(info, symname))
			अवरोध;
		अगर (info->hdr->e_machine == EM_SPARC ||
		    info->hdr->e_machine == EM_SPARCV9) अणु
			/* Ignore रेजिस्टर directives. */
			अगर (ELF_ST_TYPE(sym->st_info) == STT_SPARC_REGISTER)
				अवरोध;
			अगर (symname[0] == '.') अणु
				अक्षर *munged = NOFAIL(strdup(symname));
				munged[0] = '_';
				munged[1] = बड़े(munged[1]);
				symname = munged;
			पूर्ण
		पूर्ण

		mod->unres = alloc_symbol(symname,
					  ELF_ST_BIND(sym->st_info) == STB_WEAK,
					  mod->unres);
		अवरोध;
	शेष:
		/* All exported symbols */
		अगर (strstarts(symname, "__ksymtab_")) अणु
			name = symname + म_माप("__ksymtab_");
			sym_add_exported(name, mod, export);
		पूर्ण
		अगर (म_भेद(symname, "init_module") == 0)
			mod->has_init = 1;
		अगर (म_भेद(symname, "cleanup_module") == 0)
			mod->has_cleanup = 1;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * Parse tag=value strings from .modinfo section
 **/
अटल अक्षर *next_string(अक्षर *string, अचिन्हित दीर्घ *secsize)
अणु
	/* Skip non-zero अक्षरs */
	जबतक (string[0]) अणु
		string++;
		अगर ((*secsize)-- <= 1)
			वापस शून्य;
	पूर्ण

	/* Skip any zero padding. */
	जबतक (!string[0]) अणु
		string++;
		अगर ((*secsize)-- <= 1)
			वापस शून्य;
	पूर्ण
	वापस string;
पूर्ण

अटल अक्षर *get_next_modinfo(काष्ठा elf_info *info, स्थिर अक्षर *tag,
			      अक्षर *prev)
अणु
	अक्षर *p;
	अचिन्हित पूर्णांक taglen = म_माप(tag);
	अक्षर *modinfo = info->modinfo;
	अचिन्हित दीर्घ size = info->modinfo_len;

	अगर (prev) अणु
		size -= prev - modinfo;
		modinfo = next_string(prev, &size);
	पूर्ण

	क्रम (p = modinfo; p; p = next_string(p, &size)) अणु
		अगर (म_भेदन(p, tag, taglen) == 0 && p[taglen] == '=')
			वापस p + taglen + 1;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अक्षर *get_modinfo(काष्ठा elf_info *info, स्थिर अक्षर *tag)

अणु
	वापस get_next_modinfo(info, tag, शून्य);
पूर्ण

/**
 * Test अगर string s ends in string sub
 * वापस 0 अगर match
 **/
अटल पूर्णांक strrcmp(स्थिर अक्षर *s, स्थिर अक्षर *sub)
अणु
	पूर्णांक slen, sublen;

	अगर (!s || !sub)
		वापस 1;

	slen = म_माप(s);
	sublen = म_माप(sub);

	अगर ((slen == 0) || (sublen == 0))
		वापस 1;

	अगर (sublen > slen)
		वापस 1;

	वापस स_भेद(s + slen - sublen, sub, sublen);
पूर्ण

अटल स्थिर अक्षर *sym_name(काष्ठा elf_info *elf, Elf_Sym *sym)
अणु
	अगर (sym)
		वापस elf->strtab + sym->st_name;
	अन्यथा
		वापस "(unknown)";
पूर्ण

/* The pattern is an array of simple patterns.
 * "foo" will match an exact string equal to "foo"
 * "*foo" will match a string that ends with "foo"
 * "foo*" will match a string that begins with "foo"
 * "*foo*" will match a string that contains "foo"
 */
अटल पूर्णांक match(स्थिर अक्षर *sym, स्थिर अक्षर * स्थिर pat[])
अणु
	स्थिर अक्षर *p;
	जबतक (*pat) अणु
		p = *pat++;
		स्थिर अक्षर *endp = p + म_माप(p) - 1;

		/* "*foo*" */
		अगर (*p == '*' && *endp == '*') अणु
			अक्षर *bare = NOFAIL(strndup(p + 1, म_माप(p) - 2));
			अक्षर *here = म_माला(sym, bare);

			मुक्त(bare);
			अगर (here != शून्य)
				वापस 1;
		पूर्ण
		/* "*foo" */
		अन्यथा अगर (*p == '*') अणु
			अगर (strrcmp(sym, p + 1) == 0)
				वापस 1;
		पूर्ण
		/* "foo*" */
		अन्यथा अगर (*endp == '*') अणु
			अगर (म_भेदन(sym, p, म_माप(p) - 1) == 0)
				वापस 1;
		पूर्ण
		/* no wildcards */
		अन्यथा अणु
			अगर (म_भेद(p, sym) == 0)
				वापस 1;
		पूर्ण
	पूर्ण
	/* no match */
	वापस 0;
पूर्ण

/* sections that we करो not want to करो full section mismatch check on */
अटल स्थिर अक्षर *स्थिर section_white_list[] =
अणु
	".comment*",
	".debug*",
	".cranges",		/* sh64 */
	".zdebug*",		/* Compressed debug sections. */
	".GCC.command.line",	/* record-gcc-चयनes */
	".mdebug*",        /* alpha, score, mips etc. */
	".pdr",            /* alpha, score, mips etc. */
	".stab*",
	".note*",
	".got*",
	".toc*",
	".xt.prop",				 /* xtensa */
	".xt.lit",         /* xtensa */
	".arcextmap*",			/* arc */
	".gnu.linkonce.arcext*",	/* arc : modules */
	".cmem*",			/* EZchip */
	".fmt_slot*",			/* EZchip */
	".gnu.lto*",
	".discard.*",
	शून्य
पूर्ण;

/*
 * This is used to find sections missing the SHF_ALLOC flag.
 * The cause of this is often a section specअगरied in assembler
 * without "ax" / "aw".
 */
अटल व्योम check_section(स्थिर अक्षर *modname, काष्ठा elf_info *elf,
			  Elf_Shdr *sechdr)
अणु
	स्थिर अक्षर *sec = sech_name(elf, sechdr);

	अगर (sechdr->sh_type == SHT_PROGBITS &&
	    !(sechdr->sh_flags & SHF_ALLOC) &&
	    !match(sec, section_white_list)) अणु
		warn("%s (%s): unexpected non-allocatable section.\n"
		     "Did you forget to use \"ax\"/\"aw\" in a .S file?\n"
		     "Note that for example <linux/init.h> contains\n"
		     "section definitions for use in .S files.\n\n",
		     modname, sec);
	पूर्ण
पूर्ण



#घोषणा ALL_INIT_DATA_SECTIONS \
	".init.setup", ".init.rodata", ".meminit.rodata", \
	".init.data", ".meminit.data"
#घोषणा ALL_EXIT_DATA_SECTIONS \
	".exit.data", ".memexit.data"

#घोषणा ALL_INIT_TEXT_SECTIONS \
	".init.text", ".meminit.text"
#घोषणा ALL_EXIT_TEXT_SECTIONS \
	".exit.text", ".memexit.text"

#घोषणा ALL_PCI_INIT_SECTIONS	\
	".pci_fixup_early", ".pci_fixup_header", ".pci_fixup_final", \
	".pci_fixup_enable", ".pci_fixup_resume", \
	".pci_fixup_resume_early", ".pci_fixup_suspend"

#घोषणा ALL_XXXINIT_SECTIONS MEM_INIT_SECTIONS
#घोषणा ALL_XXXEXIT_SECTIONS MEM_EXIT_SECTIONS

#घोषणा ALL_INIT_SECTIONS INIT_SECTIONS, ALL_XXXINIT_SECTIONS
#घोषणा ALL_EXIT_SECTIONS EXIT_SECTIONS, ALL_XXXEXIT_SECTIONS

#घोषणा DATA_SECTIONS ".data", ".data.rel"
#घोषणा TEXT_SECTIONS ".text", ".text.unlikely", ".sched.text", \
		".kprobes.text", ".cpuidle.text", ".noinstr.text"
#घोषणा OTHER_TEXT_SECTIONS ".ref.text", ".head.text", ".spinlock.text", \
		".fixup", ".entry.text", ".exception.text", ".text.*", \
		".coldtext"

#घोषणा INIT_SECTIONS      ".init.*"
#घोषणा MEM_INIT_SECTIONS  ".meminit.*"

#घोषणा EXIT_SECTIONS      ".exit.*"
#घोषणा MEM_EXIT_SECTIONS  ".memexit.*"

#घोषणा ALL_TEXT_SECTIONS  ALL_INIT_TEXT_SECTIONS, ALL_EXIT_TEXT_SECTIONS, \
		TEXT_SECTIONS, OTHER_TEXT_SECTIONS

/* init data sections */
अटल स्थिर अक्षर *स्थिर init_data_sections[] =
	अणु ALL_INIT_DATA_SECTIONS, शून्य पूर्ण;

/* all init sections */
अटल स्थिर अक्षर *स्थिर init_sections[] = अणु ALL_INIT_SECTIONS, शून्य पूर्ण;

/* All init and निकास sections (code + data) */
अटल स्थिर अक्षर *स्थिर init_निकास_sections[] =
	अणुALL_INIT_SECTIONS, ALL_EXIT_SECTIONS, शून्य पूर्ण;

/* all text sections */
अटल स्थिर अक्षर *स्थिर text_sections[] = अणु ALL_TEXT_SECTIONS, शून्य पूर्ण;

/* data section */
अटल स्थिर अक्षर *स्थिर data_sections[] = अणु DATA_SECTIONS, शून्य पूर्ण;


/* symbols in .data that may refer to init/निकास sections */
#घोषणा DEFAULT_SYMBOL_WHITE_LIST					\
	"*driver",							\
	"*_template", /* scsi uses *_ढाँचा a lot */			\
	"*_timer",    /* arm uses ops काष्ठाures named _समयr a lot */	\
	"*_sht",      /* scsi also used *_sht to some extent */		\
	"*_ops",							\
	"*_probe",							\
	"*_probe_one",							\
	"*_console"

अटल स्थिर अक्षर *स्थिर head_sections[] = अणु ".head.text*", शून्य पूर्ण;
अटल स्थिर अक्षर *स्थिर linker_symbols[] =
	अणु "__init_begin", "_sinittext", "_einittext", शून्य पूर्ण;
अटल स्थिर अक्षर *स्थिर optim_symbols[] = अणु "*.constprop.*", शून्य पूर्ण;

क्रमागत mismatch अणु
	TEXT_TO_ANY_INIT,
	DATA_TO_ANY_INIT,
	TEXT_TO_ANY_EXIT,
	DATA_TO_ANY_EXIT,
	XXXINIT_TO_SOME_INIT,
	XXXEXIT_TO_SOME_EXIT,
	ANY_INIT_TO_ANY_EXIT,
	ANY_EXIT_TO_ANY_INIT,
	EXPORT_TO_INIT_EXIT,
	EXTABLE_TO_NON_TEXT,
पूर्ण;

/**
 * Describe how to match sections on dअगरferent criteria:
 *
 * @fromsec: Array of sections to be matched.
 *
 * @bad_tosec: Relocations applied to a section in @fromsec to a section in
 * this array is क्रमbidden (black-list).  Can be empty.
 *
 * @good_tosec: Relocations applied to a section in @fromsec must be
 * targeting sections in this array (white-list).  Can be empty.
 *
 * @mismatch: Type of mismatch.
 *
 * @symbol_white_list: Do not match a relocation to a symbol in this list
 * even अगर it is targeting a section in @bad_to_sec.
 *
 * @handler: Specअगरic handler to call when a match is found.  If शून्य,
 * शेष_mismatch_handler() will be called.
 *
 */
काष्ठा sectioncheck अणु
	स्थिर अक्षर *fromsec[20];
	स्थिर अक्षर *bad_tosec[20];
	स्थिर अक्षर *good_tosec[20];
	क्रमागत mismatch mismatch;
	स्थिर अक्षर *symbol_white_list[20];
	व्योम (*handler)(स्थिर अक्षर *modname, काष्ठा elf_info *elf,
			स्थिर काष्ठा sectioncheck* स्थिर mismatch,
			Elf_Rela *r, Elf_Sym *sym, स्थिर अक्षर *fromsec);

पूर्ण;

अटल व्योम extable_mismatch_handler(स्थिर अक्षर *modname, काष्ठा elf_info *elf,
				     स्थिर काष्ठा sectioncheck* स्थिर mismatch,
				     Elf_Rela *r, Elf_Sym *sym,
				     स्थिर अक्षर *fromsec);

अटल स्थिर काष्ठा sectioncheck sectioncheck[] = अणु
/* Do not reference init/निकास code/data from
 * normal code and data
 */
अणु
	.fromsec = अणु TEXT_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु ALL_INIT_SECTIONS, शून्य पूर्ण,
	.mismatch = TEXT_TO_ANY_INIT,
	.symbol_white_list = अणु DEFAULT_SYMBOL_WHITE_LIST, शून्य पूर्ण,
पूर्ण,
अणु
	.fromsec = अणु DATA_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु ALL_XXXINIT_SECTIONS, शून्य पूर्ण,
	.mismatch = DATA_TO_ANY_INIT,
	.symbol_white_list = अणु DEFAULT_SYMBOL_WHITE_LIST, शून्य पूर्ण,
पूर्ण,
अणु
	.fromsec = अणु DATA_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु INIT_SECTIONS, शून्य पूर्ण,
	.mismatch = DATA_TO_ANY_INIT,
	.symbol_white_list = अणु
		"*_template", "*_timer", "*_sht", "*_ops",
		"*_probe", "*_probe_one", "*_console", शून्य
	पूर्ण,
पूर्ण,
अणु
	.fromsec = अणु TEXT_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु ALL_EXIT_SECTIONS, शून्य पूर्ण,
	.mismatch = TEXT_TO_ANY_EXIT,
	.symbol_white_list = अणु DEFAULT_SYMBOL_WHITE_LIST, शून्य पूर्ण,
पूर्ण,
अणु
	.fromsec = अणु DATA_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु ALL_EXIT_SECTIONS, शून्य पूर्ण,
	.mismatch = DATA_TO_ANY_EXIT,
	.symbol_white_list = अणु DEFAULT_SYMBOL_WHITE_LIST, शून्य पूर्ण,
पूर्ण,
/* Do not reference init code/data from meminit code/data */
अणु
	.fromsec = अणु ALL_XXXINIT_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु INIT_SECTIONS, शून्य पूर्ण,
	.mismatch = XXXINIT_TO_SOME_INIT,
	.symbol_white_list = अणु DEFAULT_SYMBOL_WHITE_LIST, शून्य पूर्ण,
पूर्ण,
/* Do not reference निकास code/data from memनिकास code/data */
अणु
	.fromsec = अणु ALL_XXXEXIT_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु EXIT_SECTIONS, शून्य पूर्ण,
	.mismatch = XXXEXIT_TO_SOME_EXIT,
	.symbol_white_list = अणु DEFAULT_SYMBOL_WHITE_LIST, शून्य पूर्ण,
पूर्ण,
/* Do not use निकास code/data from init code */
अणु
	.fromsec = अणु ALL_INIT_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु ALL_EXIT_SECTIONS, शून्य पूर्ण,
	.mismatch = ANY_INIT_TO_ANY_EXIT,
	.symbol_white_list = अणु DEFAULT_SYMBOL_WHITE_LIST, शून्य पूर्ण,
पूर्ण,
/* Do not use init code/data from निकास code */
अणु
	.fromsec = अणु ALL_EXIT_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु ALL_INIT_SECTIONS, शून्य पूर्ण,
	.mismatch = ANY_EXIT_TO_ANY_INIT,
	.symbol_white_list = अणु DEFAULT_SYMBOL_WHITE_LIST, शून्य पूर्ण,
पूर्ण,
अणु
	.fromsec = अणु ALL_PCI_INIT_SECTIONS, शून्य पूर्ण,
	.bad_tosec = अणु INIT_SECTIONS, शून्य पूर्ण,
	.mismatch = ANY_INIT_TO_ANY_EXIT,
	.symbol_white_list = अणु शून्य पूर्ण,
पूर्ण,
/* Do not export init/निकास functions or data */
अणु
	.fromsec = अणु "__ksymtab*", शून्य पूर्ण,
	.bad_tosec = अणु INIT_SECTIONS, EXIT_SECTIONS, शून्य पूर्ण,
	.mismatch = EXPORT_TO_INIT_EXIT,
	.symbol_white_list = अणु DEFAULT_SYMBOL_WHITE_LIST, शून्य पूर्ण,
पूर्ण,
अणु
	.fromsec = अणु "__ex_table", शून्य पूर्ण,
	/* If you're adding any new black-listed sections in here, consider
	 * adding a special 'printer' क्रम them in scripts/check_extable.
	 */
	.bad_tosec = अणु ".altinstr_replacement", शून्य पूर्ण,
	.good_tosec = अणुALL_TEXT_SECTIONS , शून्यपूर्ण,
	.mismatch = EXTABLE_TO_NON_TEXT,
	.handler = extable_mismatch_handler,
पूर्ण
पूर्ण;

अटल स्थिर काष्ठा sectioncheck *section_mismatch(
		स्थिर अक्षर *fromsec, स्थिर अक्षर *tosec)
अणु
	पूर्णांक i;
	पूर्णांक elems = माप(sectioncheck) / माप(काष्ठा sectioncheck);
	स्थिर काष्ठा sectioncheck *check = &sectioncheck[0];

	/*
	 * The target section could be the SHT_NUL section when we're
	 * handling relocations to un-resolved symbols, trying to match it
	 * करोesn't make much sense and causes build failures on parisc
	 * architectures.
	 */
	अगर (*tosec == '\0')
		वापस शून्य;

	क्रम (i = 0; i < elems; i++) अणु
		अगर (match(fromsec, check->fromsec)) अणु
			अगर (check->bad_tosec[0] && match(tosec, check->bad_tosec))
				वापस check;
			अगर (check->good_tosec[0] && !match(tosec, check->good_tosec))
				वापस check;
		पूर्ण
		check++;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * Whitelist to allow certain references to pass with no warning.
 *
 * Pattern 1:
 *   If a module parameter is declared __initdata and permissions=0
 *   then this is legal despite the warning generated.
 *   We cannot see value of permissions here, so just ignore
 *   this pattern.
 *   The pattern is identअगरied by:
 *   tosec   = .init.data
 *   fromsec = .data*
 *   atsym   =__param*
 *
 * Pattern 1a:
 *   module_param_call() ops can refer to __init set function अगर permissions=0
 *   The pattern is identअगरied by:
 *   tosec   = .init.text
 *   fromsec = .data*
 *   atsym   = __param_ops_*
 *
 * Pattern 2:
 *   Many drivers utilise a *driver container with references to
 *   add, हटाओ, probe functions etc.
 *   the pattern is identअगरied by:
 *   tosec   = init or निकास section
 *   fromsec = data section
 *   atsym = *driver, *_ढाँचा, *_sht, *_ops, *_probe,
 *           *probe_one, *_console, *_समयr
 *
 * Pattern 3:
 *   Whitelist all references from .head.text to any init section
 *
 * Pattern 4:
 *   Some symbols beदीर्घ to init section but still it is ok to reference
 *   these from non-init sections as these symbols करोn't have any memory
 *   allocated क्रम them and symbol address and value are same. So even
 *   अगर init section is मुक्तd, its ok to reference those symbols.
 *   For ex. symbols marking the init section boundaries.
 *   This pattern is identअगरied by
 *   refsymname = __init_begin, _sinittext, _einittext
 *
 * Pattern 5:
 *   GCC may optimize अटल अंतरभूतs when fed स्थिरant arg(s) resulting
 *   in functions like cpumask_empty() -- generating an associated symbol
 *   cpumask_empty.स्थिरprop.3 that appears in the audit.  If the स्थिर that
 *   is passed in comes from __init, like say nmi_ipi_mask, we get a
 *   meaningless section warning.  May need to add isra symbols too...
 *   This pattern is identअगरied by
 *   tosec   = init section
 *   fromsec = text section
 *   refsymname = *.स्थिरprop.*
 *
 * Pattern 6:
 *   Hide section mismatch warnings क्रम ELF local symbols.  The goal
 *   is to eliminate false positive modpost warnings caused by
 *   compiler-generated ELF local symbol names such as ".LANCHOR1".
 *   Autogenerated symbol names bypass modpost's "Pattern 2"
 *   whitelisting, which relies on pattern-matching against symbol
 *   names to work.  (One situation where gcc can स्वतःgenerate ELF
 *   local symbols is when "-fsection-anchors" is used.)
 **/
अटल पूर्णांक secref_whitelist(स्थिर काष्ठा sectioncheck *mismatch,
			    स्थिर अक्षर *fromsec, स्थिर अक्षर *fromsym,
			    स्थिर अक्षर *tosec, स्थिर अक्षर *tosym)
अणु
	/* Check क्रम pattern 1 */
	अगर (match(tosec, init_data_sections) &&
	    match(fromsec, data_sections) &&
	    strstarts(fromsym, "__param"))
		वापस 0;

	/* Check क्रम pattern 1a */
	अगर (म_भेद(tosec, ".init.text") == 0 &&
	    match(fromsec, data_sections) &&
	    strstarts(fromsym, "__param_ops_"))
		वापस 0;

	/* Check क्रम pattern 2 */
	अगर (match(tosec, init_निकास_sections) &&
	    match(fromsec, data_sections) &&
	    match(fromsym, mismatch->symbol_white_list))
		वापस 0;

	/* Check क्रम pattern 3 */
	अगर (match(fromsec, head_sections) &&
	    match(tosec, init_sections))
		वापस 0;

	/* Check क्रम pattern 4 */
	अगर (match(tosym, linker_symbols))
		वापस 0;

	/* Check क्रम pattern 5 */
	अगर (match(fromsec, text_sections) &&
	    match(tosec, init_sections) &&
	    match(fromsym, optim_symbols))
		वापस 0;

	/* Check क्रम pattern 6 */
	अगर (strstarts(fromsym, ".L"))
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक is_arm_mapping_symbol(स्थिर अक्षर *str)
अणु
	वापस str[0] == '$' && म_अक्षर("axtd", str[1])
	       && (str[2] == '\0' || str[2] == '.');
पूर्ण

/*
 * If there's no name there, ignore it; likewise, ignore it if it's
 * one of the magic symbols emitted used by current ARM tools.
 *
 * Otherwise अगर find_symbols_between() वापसs those symbols, they'll
 * fail the whitelist tests and cause lots of false alarms ... fixable
 * only by merging __निकास and __init sections पूर्णांकo __text, bloating
 * the kernel (which is especially evil on embedded platक्रमms).
 */
अटल अंतरभूत पूर्णांक is_valid_name(काष्ठा elf_info *elf, Elf_Sym *sym)
अणु
	स्थिर अक्षर *name = elf->strtab + sym->st_name;

	अगर (!name || !म_माप(name))
		वापस 0;
	वापस !is_arm_mapping_symbol(name);
पूर्ण

/**
 * Find symbol based on relocation record info.
 * In some हालs the symbol supplied is a valid symbol so
 * वापस refsym. If st_name != 0 we assume this is a valid symbol.
 * In other हालs the symbol needs to be looked up in the symbol table
 * based on section and address.
 *  **/
अटल Elf_Sym *find_elf_symbol(काष्ठा elf_info *elf, Elf64_Sword addr,
				Elf_Sym *relsym)
अणु
	Elf_Sym *sym;
	Elf_Sym *near = शून्य;
	Elf64_Sword distance = 20;
	Elf64_Sword d;
	अचिन्हित पूर्णांक relsym_secindex;

	अगर (relsym->st_name != 0)
		वापस relsym;

	relsym_secindex = get_secindex(elf, relsym);
	क्रम (sym = elf->symtab_start; sym < elf->symtab_stop; sym++) अणु
		अगर (get_secindex(elf, sym) != relsym_secindex)
			जारी;
		अगर (ELF_ST_TYPE(sym->st_info) == STT_SECTION)
			जारी;
		अगर (!is_valid_name(elf, sym))
			जारी;
		अगर (sym->st_value == addr)
			वापस sym;
		/* Find a symbol nearby - addr are maybe negative */
		d = sym->st_value - addr;
		अगर (d < 0)
			d = addr - sym->st_value;
		अगर (d < distance) अणु
			distance = d;
			near = sym;
		पूर्ण
	पूर्ण
	/* We need a बंद match */
	अगर (distance < 20)
		वापस near;
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * Find symbols beक्रमe or equal addr and after addr - in the section sec.
 * If we find two symbols with equal offset prefer one with a valid name.
 * The ELF क्रमmat may have a better way to detect what type of symbol
 * it is, but this works क्रम now.
 **/
अटल Elf_Sym *find_elf_symbol2(काष्ठा elf_info *elf, Elf_Addr addr,
				 स्थिर अक्षर *sec)
अणु
	Elf_Sym *sym;
	Elf_Sym *near = शून्य;
	Elf_Addr distance = ~0;

	क्रम (sym = elf->symtab_start; sym < elf->symtab_stop; sym++) अणु
		स्थिर अक्षर *symsec;

		अगर (is_shndx_special(sym->st_shndx))
			जारी;
		symsec = sec_name(elf, get_secindex(elf, sym));
		अगर (म_भेद(symsec, sec) != 0)
			जारी;
		अगर (!is_valid_name(elf, sym))
			जारी;
		अगर (sym->st_value <= addr) अणु
			अगर ((addr - sym->st_value) < distance) अणु
				distance = addr - sym->st_value;
				near = sym;
			पूर्ण अन्यथा अगर ((addr - sym->st_value) == distance) अणु
				near = sym;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस near;
पूर्ण

/*
 * Convert a section name to the function/data attribute
 * .init.text => __init
 * .memनिकासस्थिर => __memस्थिर
 * etc.
 *
 * The memory of वापसed value has been allocated on a heap. The user of this
 * method should मुक्त it after usage.
*/
अटल अक्षर *sec2annotation(स्थिर अक्षर *s)
अणु
	अगर (match(s, init_निकास_sections)) अणु
		अक्षर *p = NOFAIL(दो_स्मृति(20));
		अक्षर *r = p;

		*p++ = '_';
		*p++ = '_';
		अगर (*s == '.')
			s++;
		जबतक (*s && *s != '.')
			*p++ = *s++;
		*p = '\0';
		अगर (*s == '.')
			s++;
		अगर (म_माला(s, "rodata") != शून्य)
			म_जोड़ो(p, "const ");
		अन्यथा अगर (म_माला(s, "data") != शून्य)
			म_जोड़ो(p, "data ");
		अन्यथा
			म_जोड़ो(p, " ");
		वापस r;
	पूर्ण अन्यथा अणु
		वापस NOFAIL(strdup(""));
	पूर्ण
पूर्ण

अटल पूर्णांक is_function(Elf_Sym *sym)
अणु
	अगर (sym)
		वापस ELF_ST_TYPE(sym->st_info) == STT_FUNC;
	अन्यथा
		वापस -1;
पूर्ण

अटल व्योम prपूर्णांक_section_list(स्थिर अक्षर * स्थिर list[20])
अणु
	स्थिर अक्षर *स्थिर *s = list;

	जबतक (*s) अणु
		ख_लिखो(मानक_त्रुटि, "%s", *s);
		s++;
		अगर (*s)
			ख_लिखो(मानक_त्रुटि, ", ");
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "\n");
पूर्ण

अटल अंतरभूत व्योम get_pretty_name(पूर्णांक is_func, स्थिर अक्षर** name, स्थिर अक्षर** name_p)
अणु
	चयन (is_func) अणु
	हाल 0:	*name = "variable"; *name_p = ""; अवरोध;
	हाल 1:	*name = "function"; *name_p = "()"; अवरोध;
	शेष: *name = "(unknown reference)"; *name_p = ""; अवरोध;
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक a warning about a section mismatch.
 * Try to find symbols near it so user can find it.
 * Check whitelist beक्रमe warning - it may be a false positive.
 */
अटल व्योम report_sec_mismatch(स्थिर अक्षर *modname,
				स्थिर काष्ठा sectioncheck *mismatch,
				स्थिर अक्षर *fromsec,
				अचिन्हित दीर्घ दीर्घ fromaddr,
				स्थिर अक्षर *fromsym,
				पूर्णांक from_is_func,
				स्थिर अक्षर *tosec, स्थिर अक्षर *tosym,
				पूर्णांक to_is_func)
अणु
	स्थिर अक्षर *from, *from_p;
	स्थिर अक्षर *to, *to_p;
	अक्षर *prl_from;
	अक्षर *prl_to;

	sec_mismatch_count++;

	get_pretty_name(from_is_func, &from, &from_p);
	get_pretty_name(to_is_func, &to, &to_p);

	warn("%s(%s+0x%llx): Section mismatch in reference from the %s %s%s "
	     "to the %s %s:%s%s\n",
	     modname, fromsec, fromaddr, from, fromsym, from_p, to, tosec,
	     tosym, to_p);

	चयन (mismatch->mismatch) अणु
	हाल TEXT_TO_ANY_INIT:
		prl_from = sec2annotation(fromsec);
		prl_to = sec2annotation(tosec);
		ख_लिखो(मानक_त्रुटि,
		"The function %s%s() references\n"
		"the %s %s%s%s.\n"
		"This is often because %s lacks a %s\n"
		"annotation or the annotation of %s is wrong.\n",
		prl_from, fromsym,
		to, prl_to, tosym, to_p,
		fromsym, prl_to, tosym);
		मुक्त(prl_from);
		मुक्त(prl_to);
		अवरोध;
	हाल DATA_TO_ANY_INIT: अणु
		prl_to = sec2annotation(tosec);
		ख_लिखो(मानक_त्रुटि,
		"The variable %s references\n"
		"the %s %s%s%s\n"
		"If the reference is valid then annotate the\n"
		"variable with __init* or __refdata (see linux/init.h) "
		"or name the variable:\n",
		fromsym, to, prl_to, tosym, to_p);
		prपूर्णांक_section_list(mismatch->symbol_white_list);
		मुक्त(prl_to);
		अवरोध;
	पूर्ण
	हाल TEXT_TO_ANY_EXIT:
		prl_to = sec2annotation(tosec);
		ख_लिखो(मानक_त्रुटि,
		"The function %s() references a %s in an exit section.\n"
		"Often the %s %s%s has valid usage outside the exit section\n"
		"and the fix is to remove the %sannotation of %s.\n",
		fromsym, to, to, tosym, to_p, prl_to, tosym);
		मुक्त(prl_to);
		अवरोध;
	हाल DATA_TO_ANY_EXIT: अणु
		prl_to = sec2annotation(tosec);
		ख_लिखो(मानक_त्रुटि,
		"The variable %s references\n"
		"the %s %s%s%s\n"
		"If the reference is valid then annotate the\n"
		"variable with __exit* (see linux/init.h) or "
		"name the variable:\n",
		fromsym, to, prl_to, tosym, to_p);
		prपूर्णांक_section_list(mismatch->symbol_white_list);
		मुक्त(prl_to);
		अवरोध;
	पूर्ण
	हाल XXXINIT_TO_SOME_INIT:
	हाल XXXEXIT_TO_SOME_EXIT:
		prl_from = sec2annotation(fromsec);
		prl_to = sec2annotation(tosec);
		ख_लिखो(मानक_त्रुटि,
		"The %s %s%s%s references\n"
		"a %s %s%s%s.\n"
		"If %s is only used by %s then\n"
		"annotate %s with a matching annotation.\n",
		from, prl_from, fromsym, from_p,
		to, prl_to, tosym, to_p,
		tosym, fromsym, tosym);
		मुक्त(prl_from);
		मुक्त(prl_to);
		अवरोध;
	हाल ANY_INIT_TO_ANY_EXIT:
		prl_from = sec2annotation(fromsec);
		prl_to = sec2annotation(tosec);
		ख_लिखो(मानक_त्रुटि,
		"The %s %s%s%s references\n"
		"a %s %s%s%s.\n"
		"This is often seen when error handling "
		"in the init function\n"
		"uses functionality in the exit path.\n"
		"The fix is often to remove the %sannotation of\n"
		"%s%s so it may be used outside an exit section.\n",
		from, prl_from, fromsym, from_p,
		to, prl_to, tosym, to_p,
		prl_to, tosym, to_p);
		मुक्त(prl_from);
		मुक्त(prl_to);
		अवरोध;
	हाल ANY_EXIT_TO_ANY_INIT:
		prl_from = sec2annotation(fromsec);
		prl_to = sec2annotation(tosec);
		ख_लिखो(मानक_त्रुटि,
		"The %s %s%s%s references\n"
		"a %s %s%s%s.\n"
		"This is often seen when error handling "
		"in the exit function\n"
		"uses functionality in the init path.\n"
		"The fix is often to remove the %sannotation of\n"
		"%s%s so it may be used outside an init section.\n",
		from, prl_from, fromsym, from_p,
		to, prl_to, tosym, to_p,
		prl_to, tosym, to_p);
		मुक्त(prl_from);
		मुक्त(prl_to);
		अवरोध;
	हाल EXPORT_TO_INIT_EXIT:
		prl_to = sec2annotation(tosec);
		ख_लिखो(मानक_त्रुटि,
		"The symbol %s is exported and annotated %s\n"
		"Fix this by removing the %sannotation of %s "
		"or drop the export.\n",
		tosym, prl_to, prl_to, tosym);
		मुक्त(prl_to);
		अवरोध;
	हाल EXTABLE_TO_NON_TEXT:
		fatal("There's a special handler for this mismatch type, "
		      "we should never get here.");
		अवरोध;
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "\n");
पूर्ण

अटल व्योम शेष_mismatch_handler(स्थिर अक्षर *modname, काष्ठा elf_info *elf,
				     स्थिर काष्ठा sectioncheck* स्थिर mismatch,
				     Elf_Rela *r, Elf_Sym *sym, स्थिर अक्षर *fromsec)
अणु
	स्थिर अक्षर *tosec;
	Elf_Sym *to;
	Elf_Sym *from;
	स्थिर अक्षर *tosym;
	स्थिर अक्षर *fromsym;

	from = find_elf_symbol2(elf, r->r_offset, fromsec);
	fromsym = sym_name(elf, from);

	अगर (strstarts(fromsym, "reference___initcall"))
		वापस;

	tosec = sec_name(elf, get_secindex(elf, sym));
	to = find_elf_symbol(elf, r->r_addend, sym);
	tosym = sym_name(elf, to);

	/* check whitelist - we may ignore it */
	अगर (secref_whitelist(mismatch,
			     fromsec, fromsym, tosec, tosym)) अणु
		report_sec_mismatch(modname, mismatch,
				    fromsec, r->r_offset, fromsym,
				    is_function(from), tosec, tosym,
				    is_function(to));
	पूर्ण
पूर्ण

अटल पूर्णांक is_executable_section(काष्ठा elf_info* elf, अचिन्हित पूर्णांक section_index)
अणु
	अगर (section_index > elf->num_sections)
		fatal("section_index is outside elf->num_sections!\n");

	वापस ((elf->sechdrs[section_index].sh_flags & SHF_EXECINSTR) == SHF_EXECINSTR);
पूर्ण

/*
 * We rely on a gross hack in section_rel[a]() calling find_extable_entry_size()
 * to know the माप(काष्ठा exception_table_entry) क्रम the target architecture.
 */
अटल अचिन्हित पूर्णांक extable_entry_size = 0;
अटल व्योम find_extable_entry_size(स्थिर अक्षर* स्थिर sec, स्थिर Elf_Rela* r)
अणु
	/*
	 * If we're currently checking the second relocation within __ex_table,
	 * that relocation offset tells us the दुरत्व(काष्ठा
	 * exception_table_entry, fixup) which is equal to माप(काष्ठा
	 * exception_table_entry) भागided by two.  We use that to our advantage
	 * since there's no portable way to get that size as every architecture
	 * seems to go with dअगरferent sized types.  Not pretty but better than
	 * hard-coding the size क्रम every architecture..
	 */
	अगर (!extable_entry_size)
		extable_entry_size = r->r_offset * 2;
पूर्ण

अटल अंतरभूत bool is_extable_fault_address(Elf_Rela *r)
अणु
	/*
	 * extable_entry_size is only discovered after we've handled the
	 * _second_ relocation in __ex_table, so only पात when we're not
	 * handling the first reloc and extable_entry_size is zero.
	 */
	अगर (r->r_offset && extable_entry_size == 0)
		fatal("extable_entry size hasn't been discovered!\n");

	वापस ((r->r_offset == 0) ||
		(r->r_offset % extable_entry_size == 0));
पूर्ण

#घोषणा is_second_extable_reloc(Start, Cur, Sec)			\
	(((Cur) == (Start) + 1) && (म_भेद("__ex_table", (Sec)) == 0))

अटल व्योम report_extable_warnings(स्थिर अक्षर* modname, काष्ठा elf_info* elf,
				    स्थिर काष्ठा sectioncheck* स्थिर mismatch,
				    Elf_Rela* r, Elf_Sym* sym,
				    स्थिर अक्षर* fromsec, स्थिर अक्षर* tosec)
अणु
	Elf_Sym* fromsym = find_elf_symbol2(elf, r->r_offset, fromsec);
	स्थिर अक्षर* fromsym_name = sym_name(elf, fromsym);
	Elf_Sym* tosym = find_elf_symbol(elf, r->r_addend, sym);
	स्थिर अक्षर* tosym_name = sym_name(elf, tosym);
	स्थिर अक्षर* from_pretty_name;
	स्थिर अक्षर* from_pretty_name_p;
	स्थिर अक्षर* to_pretty_name;
	स्थिर अक्षर* to_pretty_name_p;

	get_pretty_name(is_function(fromsym),
			&from_pretty_name, &from_pretty_name_p);
	get_pretty_name(is_function(tosym),
			&to_pretty_name, &to_pretty_name_p);

	warn("%s(%s+0x%lx): Section mismatch in reference"
	     " from the %s %s%s to the %s %s:%s%s\n",
	     modname, fromsec, (दीर्घ)r->r_offset, from_pretty_name,
	     fromsym_name, from_pretty_name_p,
	     to_pretty_name, tosec, tosym_name, to_pretty_name_p);

	अगर (!match(tosec, mismatch->bad_tosec) &&
	    is_executable_section(elf, get_secindex(elf, sym)))
		ख_लिखो(मानक_त्रुटि,
			"The relocation at %s+0x%lx references\n"
			"section \"%s\" which is not in the list of\n"
			"authorized sections.  If you're adding a new section\n"
			"and/or if this reference is valid, add \"%s\" to the\n"
			"list of authorized sections to jump to on fault.\n"
			"This can be achieved by adding \"%s\" to \n"
			"OTHER_TEXT_SECTIONS in scripts/mod/modpost.c.\n",
			fromsec, (दीर्घ)r->r_offset, tosec, tosec, tosec);
पूर्ण

अटल व्योम extable_mismatch_handler(स्थिर अक्षर* modname, काष्ठा elf_info *elf,
				     स्थिर काष्ठा sectioncheck* स्थिर mismatch,
				     Elf_Rela* r, Elf_Sym* sym,
				     स्थिर अक्षर *fromsec)
अणु
	स्थिर अक्षर* tosec = sec_name(elf, get_secindex(elf, sym));

	sec_mismatch_count++;

	report_extable_warnings(modname, elf, mismatch, r, sym, fromsec, tosec);

	अगर (match(tosec, mismatch->bad_tosec))
		fatal("The relocation at %s+0x%lx references\n"
		      "section \"%s\" which is black-listed.\n"
		      "Something is seriously wrong and should be fixed.\n"
		      "You might get more information about where this is\n"
		      "coming from by using scripts/check_extable.sh %s\n",
		      fromsec, (दीर्घ)r->r_offset, tosec, modname);
	अन्यथा अगर (!is_executable_section(elf, get_secindex(elf, sym))) अणु
		अगर (is_extable_fault_address(r))
			fatal("The relocation at %s+0x%lx references\n"
			      "section \"%s\" which is not executable, IOW\n"
			      "it is not possible for the kernel to fault\n"
			      "at that address.  Something is seriously wrong\n"
			      "and should be fixed.\n",
			      fromsec, (दीर्घ)r->r_offset, tosec);
		अन्यथा
			fatal("The relocation at %s+0x%lx references\n"
			      "section \"%s\" which is not executable, IOW\n"
			      "the kernel will fault if it ever tries to\n"
			      "jump to it.  Something is seriously wrong\n"
			      "and should be fixed.\n",
			      fromsec, (दीर्घ)r->r_offset, tosec);
	पूर्ण
पूर्ण

अटल व्योम check_section_mismatch(स्थिर अक्षर *modname, काष्ठा elf_info *elf,
				   Elf_Rela *r, Elf_Sym *sym, स्थिर अक्षर *fromsec)
अणु
	स्थिर अक्षर *tosec = sec_name(elf, get_secindex(elf, sym));
	स्थिर काष्ठा sectioncheck *mismatch = section_mismatch(fromsec, tosec);

	अगर (mismatch) अणु
		अगर (mismatch->handler)
			mismatch->handler(modname, elf,  mismatch,
					  r, sym, fromsec);
		अन्यथा
			शेष_mismatch_handler(modname, elf, mismatch,
						 r, sym, fromsec);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक *reloc_location(काष्ठा elf_info *elf,
				    Elf_Shdr *sechdr, Elf_Rela *r)
अणु
	वापस sym_get_data_by_offset(elf, sechdr->sh_info, r->r_offset);
पूर्ण

अटल पूर्णांक addend_386_rel(काष्ठा elf_info *elf, Elf_Shdr *sechdr, Elf_Rela *r)
अणु
	अचिन्हित पूर्णांक r_typ = ELF_R_TYPE(r->r_info);
	अचिन्हित पूर्णांक *location = reloc_location(elf, sechdr, r);

	चयन (r_typ) अणु
	हाल R_386_32:
		r->r_addend = TO_NATIVE(*location);
		अवरोध;
	हाल R_386_PC32:
		r->r_addend = TO_NATIVE(*location) + 4;
		/* For CONFIG_RELOCATABLE=y */
		अगर (elf->hdr->e_type == ET_EXEC)
			r->r_addend += r->r_offset;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_अघोषित R_ARM_CALL
#घोषणा R_ARM_CALL	28
#पूर्ण_अगर
#अगर_अघोषित R_ARM_JUMP24
#घोषणा R_ARM_JUMP24	29
#पूर्ण_अगर

#अगर_अघोषित	R_ARM_THM_CALL
#घोषणा	R_ARM_THM_CALL		10
#पूर्ण_अगर
#अगर_अघोषित	R_ARM_THM_JUMP24
#घोषणा	R_ARM_THM_JUMP24	30
#पूर्ण_अगर
#अगर_अघोषित	R_ARM_THM_JUMP19
#घोषणा	R_ARM_THM_JUMP19	51
#पूर्ण_अगर

अटल पूर्णांक addend_arm_rel(काष्ठा elf_info *elf, Elf_Shdr *sechdr, Elf_Rela *r)
अणु
	अचिन्हित पूर्णांक r_typ = ELF_R_TYPE(r->r_info);

	चयन (r_typ) अणु
	हाल R_ARM_ABS32:
		/* From ARM ABI: (S + A) | T */
		r->r_addend = (पूर्णांक)(दीर्घ)
			      (elf->symtab_start + ELF_R_SYM(r->r_info));
		अवरोध;
	हाल R_ARM_PC24:
	हाल R_ARM_CALL:
	हाल R_ARM_JUMP24:
	हाल R_ARM_THM_CALL:
	हाल R_ARM_THM_JUMP24:
	हाल R_ARM_THM_JUMP19:
		/* From ARM ABI: ((S + A) | T) - P */
		r->r_addend = (पूर्णांक)(दीर्घ)(elf->hdr +
			      sechdr->sh_offset +
			      (r->r_offset - sechdr->sh_addr));
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक addend_mips_rel(काष्ठा elf_info *elf, Elf_Shdr *sechdr, Elf_Rela *r)
अणु
	अचिन्हित पूर्णांक r_typ = ELF_R_TYPE(r->r_info);
	अचिन्हित पूर्णांक *location = reloc_location(elf, sechdr, r);
	अचिन्हित पूर्णांक inst;

	अगर (r_typ == R_MIPS_HI16)
		वापस 1;	/* skip this */
	inst = TO_NATIVE(*location);
	चयन (r_typ) अणु
	हाल R_MIPS_LO16:
		r->r_addend = inst & 0xffff;
		अवरोध;
	हाल R_MIPS_26:
		r->r_addend = (inst & 0x03ffffff) << 2;
		अवरोध;
	हाल R_MIPS_32:
		r->r_addend = inst;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम section_rela(स्थिर अक्षर *modname, काष्ठा elf_info *elf,
			 Elf_Shdr *sechdr)
अणु
	Elf_Sym  *sym;
	Elf_Rela *rela;
	Elf_Rela r;
	अचिन्हित पूर्णांक r_sym;
	स्थिर अक्षर *fromsec;

	Elf_Rela *start = (व्योम *)elf->hdr + sechdr->sh_offset;
	Elf_Rela *stop  = (व्योम *)start + sechdr->sh_size;

	fromsec = sech_name(elf, sechdr);
	fromsec += म_माप(".rela");
	/* अगर from section (name) is know good then skip it */
	अगर (match(fromsec, section_white_list))
		वापस;

	क्रम (rela = start; rela < stop; rela++) अणु
		r.r_offset = TO_NATIVE(rela->r_offset);
#अगर KERNEL_ELFCLASS == ELFCLASS64
		अगर (elf->hdr->e_machine == EM_MIPS) अणु
			अचिन्हित पूर्णांक r_typ;
			r_sym = ELF64_MIPS_R_SYM(rela->r_info);
			r_sym = TO_NATIVE(r_sym);
			r_typ = ELF64_MIPS_R_TYPE(rela->r_info);
			r.r_info = ELF64_R_INFO(r_sym, r_typ);
		पूर्ण अन्यथा अणु
			r.r_info = TO_NATIVE(rela->r_info);
			r_sym = ELF_R_SYM(r.r_info);
		पूर्ण
#अन्यथा
		r.r_info = TO_NATIVE(rela->r_info);
		r_sym = ELF_R_SYM(r.r_info);
#पूर्ण_अगर
		r.r_addend = TO_NATIVE(rela->r_addend);
		sym = elf->symtab_start + r_sym;
		/* Skip special sections */
		अगर (is_shndx_special(sym->st_shndx))
			जारी;
		अगर (is_second_extable_reloc(start, rela, fromsec))
			find_extable_entry_size(fromsec, &r);
		check_section_mismatch(modname, elf, &r, sym, fromsec);
	पूर्ण
पूर्ण

अटल व्योम section_rel(स्थिर अक्षर *modname, काष्ठा elf_info *elf,
			Elf_Shdr *sechdr)
अणु
	Elf_Sym *sym;
	Elf_Rel *rel;
	Elf_Rela r;
	अचिन्हित पूर्णांक r_sym;
	स्थिर अक्षर *fromsec;

	Elf_Rel *start = (व्योम *)elf->hdr + sechdr->sh_offset;
	Elf_Rel *stop  = (व्योम *)start + sechdr->sh_size;

	fromsec = sech_name(elf, sechdr);
	fromsec += म_माप(".rel");
	/* अगर from section (name) is know good then skip it */
	अगर (match(fromsec, section_white_list))
		वापस;

	क्रम (rel = start; rel < stop; rel++) अणु
		r.r_offset = TO_NATIVE(rel->r_offset);
#अगर KERNEL_ELFCLASS == ELFCLASS64
		अगर (elf->hdr->e_machine == EM_MIPS) अणु
			अचिन्हित पूर्णांक r_typ;
			r_sym = ELF64_MIPS_R_SYM(rel->r_info);
			r_sym = TO_NATIVE(r_sym);
			r_typ = ELF64_MIPS_R_TYPE(rel->r_info);
			r.r_info = ELF64_R_INFO(r_sym, r_typ);
		पूर्ण अन्यथा अणु
			r.r_info = TO_NATIVE(rel->r_info);
			r_sym = ELF_R_SYM(r.r_info);
		पूर्ण
#अन्यथा
		r.r_info = TO_NATIVE(rel->r_info);
		r_sym = ELF_R_SYM(r.r_info);
#पूर्ण_अगर
		r.r_addend = 0;
		चयन (elf->hdr->e_machine) अणु
		हाल EM_386:
			अगर (addend_386_rel(elf, sechdr, &r))
				जारी;
			अवरोध;
		हाल EM_ARM:
			अगर (addend_arm_rel(elf, sechdr, &r))
				जारी;
			अवरोध;
		हाल EM_MIPS:
			अगर (addend_mips_rel(elf, sechdr, &r))
				जारी;
			अवरोध;
		पूर्ण
		sym = elf->symtab_start + r_sym;
		/* Skip special sections */
		अगर (is_shndx_special(sym->st_shndx))
			जारी;
		अगर (is_second_extable_reloc(start, rel, fromsec))
			find_extable_entry_size(fromsec, &r);
		check_section_mismatch(modname, elf, &r, sym, fromsec);
	पूर्ण
पूर्ण

/**
 * A module includes a number of sections that are discarded
 * either when loaded or when used as built-in.
 * For loaded modules all functions marked __init and all data
 * marked __initdata will be discarded when the module has been initialized.
 * Likewise क्रम modules used built-in the sections marked __निकास
 * are discarded because __निकास marked function are supposed to be called
 * only when a module is unloaded which never happens क्रम built-in modules.
 * The check_sec_ref() function traverses all relocation records
 * to find all references to a section that reference a section that will
 * be discarded and warns about it.
 **/
अटल व्योम check_sec_ref(काष्ठा module *mod, स्थिर अक्षर *modname,
			  काष्ठा elf_info *elf)
अणु
	पूर्णांक i;
	Elf_Shdr *sechdrs = elf->sechdrs;

	/* Walk through all sections */
	क्रम (i = 0; i < elf->num_sections; i++) अणु
		check_section(modname, elf, &elf->sechdrs[i]);
		/* We want to process only relocation sections and not .init */
		अगर (sechdrs[i].sh_type == SHT_RELA)
			section_rela(modname, elf, &elf->sechdrs[i]);
		अन्यथा अगर (sechdrs[i].sh_type == SHT_REL)
			section_rel(modname, elf, &elf->sechdrs[i]);
	पूर्ण
पूर्ण

अटल अक्षर *हटाओ_करोt(अक्षर *s)
अणु
	माप_प्रकार n = म_खोज(s, ".");

	अगर (n && s[n]) अणु
		माप_प्रकार m = म_अखोज(s + n + 1, "0123456789");
		अगर (m && (s[n + m] == '.' || s[n + m] == 0))
			s[n] = 0;

		/* strip trailing .lto */
		अगर (strends(s, ".lto"))
			s[म_माप(s) - 4] = '\0';
	पूर्ण
	वापस s;
पूर्ण

अटल व्योम पढ़ो_symbols(स्थिर अक्षर *modname)
अणु
	स्थिर अक्षर *symname;
	अक्षर *version;
	अक्षर *license;
	अक्षर *namespace;
	काष्ठा module *mod;
	काष्ठा elf_info info = अणु पूर्ण;
	Elf_Sym *sym;

	अगर (!parse_elf(&info, modname))
		वापस;

	अणु
		अक्षर *पंचांगp;

		/* strip trailing .o */
		पंचांगp = NOFAIL(strdup(modname));
		पंचांगp[म_माप(पंचांगp) - 2] = '\0';
		/* strip trailing .lto */
		अगर (strends(पंचांगp, ".lto"))
			पंचांगp[म_माप(पंचांगp) - 4] = '\0';
		mod = new_module(पंचांगp);
		मुक्त(पंचांगp);
	पूर्ण

	अगर (!mod->is_vmlinux) अणु
		license = get_modinfo(&info, "license");
		अगर (!license)
			error("missing MODULE_LICENSE() in %s\n", modname);
		जबतक (license) अणु
			अगर (license_is_gpl_compatible(license))
				mod->gpl_compatible = 1;
			अन्यथा अणु
				mod->gpl_compatible = 0;
				अवरोध;
			पूर्ण
			license = get_next_modinfo(&info, "license", license);
		पूर्ण

		namespace = get_modinfo(&info, "import_ns");
		जबतक (namespace) अणु
			add_namespace(&mod->imported_namespaces, namespace);
			namespace = get_next_modinfo(&info, "import_ns",
						     namespace);
		पूर्ण
	पूर्ण

	क्रम (sym = info.symtab_start; sym < info.symtab_stop; sym++) अणु
		symname = हटाओ_करोt(info.strtab + sym->st_name);

		handle_symbol(mod, &info, sym, symname);
		handle_moddevtable(mod, &info, sym, symname);
	पूर्ण

	क्रम (sym = info.symtab_start; sym < info.symtab_stop; sym++) अणु
		symname = हटाओ_करोt(info.strtab + sym->st_name);

		/* Apply symbol namespaces from __kstrtabns_<symbol> entries. */
		अगर (strstarts(symname, "__kstrtabns_"))
			sym_update_namespace(symname + म_माप("__kstrtabns_"),
					     namespace_from_kstrtabns(&info,
								      sym));

		अगर (strstarts(symname, "__crc_"))
			handle_modversion(mod, &info, sym,
					  symname + म_माप("__crc_"));
	पूर्ण

	// check क्रम अटल EXPORT_SYMBOL_* functions && global vars
	क्रम (sym = info.symtab_start; sym < info.symtab_stop; sym++) अणु
		अचिन्हित अक्षर bind = ELF_ST_BIND(sym->st_info);

		अगर (bind == STB_GLOBAL || bind == STB_WEAK) अणु
			काष्ठा symbol *s =
				find_symbol(हटाओ_करोt(info.strtab +
						       sym->st_name));

			अगर (s)
				s->is_अटल = 0;
		पूर्ण
	पूर्ण

	check_sec_ref(mod, modname, &info);

	अगर (!mod->is_vmlinux) अणु
		version = get_modinfo(&info, "version");
		अगर (version || all_versions)
			get_src_version(modname, mod->srcversion,
					माप(mod->srcversion) - 1);
	पूर्ण

	parse_elf_finish(&info);

	/* Our trick to get versioning क्रम module काष्ठा etc. - it's
	 * never passed as an argument to an exported function, so
	 * the स्वतःmatic versioning करोesn't pick it up, but it's really
	 * important anyhow */
	अगर (modversions)
		mod->unres = alloc_symbol("module_layout", 0, mod->unres);
पूर्ण

अटल व्योम पढ़ो_symbols_from_files(स्थिर अक्षर *filename)
अणु
	खाता *in = मानक_निवेश;
	अक्षर fname[PATH_MAX];

	अगर (म_भेद(filename, "-") != 0) अणु
		in = ख_खोलो(filename, "r");
		अगर (!in)
			fatal("Can't open filenames file %s: %m", filename);
	पूर्ण

	जबतक (ख_माला_लो(fname, PATH_MAX, in) != शून्य) अणु
		अगर (strends(fname, "\n"))
			fname[म_माप(fname)-1] = '\0';
		पढ़ो_symbols(fname);
	पूर्ण

	अगर (in != मानक_निवेश)
		ख_बंद(in);
पूर्ण

#घोषणा SZ 500

/* We first ग_लिखो the generated file पूर्णांकo memory using the
 * following helper, then compare to the file on disk and
 * only update the later अगर anything changed */

व्योम __attribute__((क्रमmat(म_लिखो, 2, 3))) buf_म_लिखो(काष्ठा buffer *buf,
						      स्थिर अक्षर *fmt, ...)
अणु
	अक्षर पंचांगp[SZ];
	पूर्णांक len;
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	len = vsnम_लिखो(पंचांगp, SZ, fmt, ap);
	buf_ग_लिखो(buf, पंचांगp, len);
	बहु_पूर्ण(ap);
पूर्ण

व्योम buf_ग_लिखो(काष्ठा buffer *buf, स्थिर अक्षर *s, पूर्णांक len)
अणु
	अगर (buf->size - buf->pos < len) अणु
		buf->size += len + SZ;
		buf->p = NOFAIL(पुनः_स्मृति(buf->p, buf->size));
	पूर्ण
	म_नकलन(buf->p + buf->pos, s, len);
	buf->pos += len;
पूर्ण

अटल व्योम check_क्रम_gpl_usage(क्रमागत export exp, स्थिर अक्षर *m, स्थिर अक्षर *s)
अणु
	चयन (exp) अणु
	हाल export_gpl:
		error("GPL-incompatible module %s.ko uses GPL-only symbol '%s'\n",
		      m, s);
		अवरोध;
	हाल export_plain:
	हाल export_unknown:
		/* ignore */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम check_exports(काष्ठा module *mod)
अणु
	काष्ठा symbol *s, *exp;

	क्रम (s = mod->unres; s; s = s->next) अणु
		स्थिर अक्षर *basename;
		exp = find_symbol(s->name);
		अगर (!exp || exp->module == mod) अणु
			अगर (!s->weak && nr_unresolved++ < MAX_UNRESOLVED_REPORTS)
				modpost_log(warn_unresolved ? LOG_WARN : LOG_ERROR,
					    "\"%s\" [%s.ko] undefined!\n",
					    s->name, mod->name);
			जारी;
		पूर्ण
		basename = म_खोजप(mod->name, '/');
		अगर (basename)
			basename++;
		अन्यथा
			basename = mod->name;

		अगर (exp->namespace &&
		    !module_imports_namespace(mod, exp->namespace)) अणु
			modpost_log(allow_missing_ns_imports ? LOG_WARN : LOG_ERROR,
				    "module %s uses symbol %s from namespace %s, but does not import it.\n",
				    basename, exp->name, exp->namespace);
			add_namespace(&mod->missing_namespaces, exp->namespace);
		पूर्ण

		अगर (!mod->gpl_compatible)
			check_क्रम_gpl_usage(exp->export, basename, exp->name);
	पूर्ण
पूर्ण

अटल व्योम check_modname_len(काष्ठा module *mod)
अणु
	स्थिर अक्षर *mod_name;

	mod_name = म_खोजप(mod->name, '/');
	अगर (mod_name == शून्य)
		mod_name = mod->name;
	अन्यथा
		mod_name++;
	अगर (म_माप(mod_name) >= MODULE_NAME_LEN)
		error("module name is too long [%s.ko]\n", mod->name);
पूर्ण

/**
 * Header क्रम the generated file
 **/
अटल व्योम add_header(काष्ठा buffer *b, काष्ठा module *mod)
अणु
	buf_म_लिखो(b, "#include <linux/module.h>\n");
	/*
	 * Include build-salt.h after module.h in order to
	 * inherit the definitions.
	 */
	buf_म_लिखो(b, "#define INCLUDE_VERMAGIC\n");
	buf_म_लिखो(b, "#include <linux/build-salt.h>\n");
	buf_म_लिखो(b, "#include <linux/elfnote-lto.h>\n");
	buf_म_लिखो(b, "#include <linux/vermagic.h>\n");
	buf_म_लिखो(b, "#include <linux/compiler.h>\n");
	buf_म_लिखो(b, "\n");
	buf_म_लिखो(b, "BUILD_SALT;\n");
	buf_म_लिखो(b, "BUILD_LTO_INFO;\n");
	buf_म_लिखो(b, "\n");
	buf_म_लिखो(b, "MODULE_INFO(vermagic, VERMAGIC_STRING);\n");
	buf_म_लिखो(b, "MODULE_INFO(name, KBUILD_MODNAME);\n");
	buf_म_लिखो(b, "\n");
	buf_म_लिखो(b, "__visible struct module __this_module\n");
	buf_म_लिखो(b, "__section(\".gnu.linkonce.this_module\") = {\n");
	buf_म_लिखो(b, "\t.name = KBUILD_MODNAME,\n");
	अगर (mod->has_init)
		buf_म_लिखो(b, "\t.init = init_module,\n");
	अगर (mod->has_cleanup)
		buf_म_लिखो(b, "#ifdef CONFIG_MODULE_UNLOAD\n"
			      "\t.exit = cleanup_module,\n"
			      "#endif\n");
	buf_म_लिखो(b, "\t.arch = MODULE_ARCH_INIT,\n");
	buf_म_लिखो(b, "};\n");
पूर्ण

अटल व्योम add_पूर्णांकree_flag(काष्ठा buffer *b, पूर्णांक is_पूर्णांकree)
अणु
	अगर (is_पूर्णांकree)
		buf_म_लिखो(b, "\nMODULE_INFO(intree, \"Y\");\n");
पूर्ण

/* Cannot check क्रम assembler */
अटल व्योम add_retpoline(काष्ठा buffer *b)
अणु
	buf_म_लिखो(b, "\n#ifdef CONFIG_RETPOLINE\n");
	buf_म_लिखो(b, "MODULE_INFO(retpoline, \"Y\");\n");
	buf_म_लिखो(b, "#endif\n");
पूर्ण

अटल व्योम add_staging_flag(काष्ठा buffer *b, स्थिर अक्षर *name)
अणु
	अगर (strstarts(name, "drivers/staging"))
		buf_म_लिखो(b, "\nMODULE_INFO(staging, \"Y\");\n");
पूर्ण

/**
 * Record CRCs क्रम unresolved symbols
 **/
अटल व्योम add_versions(काष्ठा buffer *b, काष्ठा module *mod)
अणु
	काष्ठा symbol *s, *exp;

	क्रम (s = mod->unres; s; s = s->next) अणु
		exp = find_symbol(s->name);
		अगर (!exp || exp->module == mod)
			जारी;
		s->module = exp->module;
		s->crc_valid = exp->crc_valid;
		s->crc = exp->crc;
	पूर्ण

	अगर (!modversions)
		वापस;

	buf_म_लिखो(b, "\n");
	buf_म_लिखो(b, "static const struct modversion_info ____versions[]\n");
	buf_म_लिखो(b, "__used __section(\"__versions\") = {\n");

	क्रम (s = mod->unres; s; s = s->next) अणु
		अगर (!s->module)
			जारी;
		अगर (!s->crc_valid) अणु
			warn("\"%s\" [%s.ko] has no CRC!\n",
				s->name, mod->name);
			जारी;
		पूर्ण
		अगर (म_माप(s->name) >= MODULE_NAME_LEN) अणु
			error("too long symbol \"%s\" [%s.ko]\n",
			      s->name, mod->name);
			अवरोध;
		पूर्ण
		buf_म_लिखो(b, "\t{ %#8x, \"%s\" },\n",
			   s->crc, s->name);
	पूर्ण

	buf_म_लिखो(b, "};\n");
पूर्ण

अटल व्योम add_depends(काष्ठा buffer *b, काष्ठा module *mod)
अणु
	काष्ठा symbol *s;
	पूर्णांक first = 1;

	/* Clear ->seen flag of modules that own symbols needed by this. */
	क्रम (s = mod->unres; s; s = s->next)
		अगर (s->module)
			s->module->seen = s->module->is_vmlinux;

	buf_म_लिखो(b, "\n");
	buf_म_लिखो(b, "MODULE_INFO(depends, \"");
	क्रम (s = mod->unres; s; s = s->next) अणु
		स्थिर अक्षर *p;
		अगर (!s->module)
			जारी;

		अगर (s->module->seen)
			जारी;

		s->module->seen = 1;
		p = म_खोजप(s->module->name, '/');
		अगर (p)
			p++;
		अन्यथा
			p = s->module->name;
		buf_म_लिखो(b, "%s%s", first ? "" : ",", p);
		first = 0;
	पूर्ण
	buf_म_लिखो(b, "\");\n");
पूर्ण

अटल व्योम add_srcversion(काष्ठा buffer *b, काष्ठा module *mod)
अणु
	अगर (mod->srcversion[0]) अणु
		buf_म_लिखो(b, "\n");
		buf_म_लिखो(b, "MODULE_INFO(srcversion, \"%s\");\n",
			   mod->srcversion);
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_buf(काष्ठा buffer *b, स्थिर अक्षर *fname)
अणु
	खाता *file;

	file = ख_खोलो(fname, "w");
	अगर (!file) अणु
		लिखो_त्रुटि(fname);
		निकास(1);
	पूर्ण
	अगर (ख_डालो(b->p, 1, b->pos, file) != b->pos) अणु
		लिखो_त्रुटि(fname);
		निकास(1);
	पूर्ण
	अगर (ख_बंद(file) != 0) अणु
		लिखो_त्रुटि(fname);
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_अगर_changed(काष्ठा buffer *b, स्थिर अक्षर *fname)
अणु
	अक्षर *पंचांगp;
	खाता *file;
	काष्ठा stat st;

	file = ख_खोलो(fname, "r");
	अगर (!file)
		जाओ ग_लिखो;

	अगर (ख_स्थिति(fileno(file), &st) < 0)
		जाओ बंद_ग_लिखो;

	अगर (st.st_size != b->pos)
		जाओ बंद_ग_लिखो;

	पंचांगp = NOFAIL(दो_स्मृति(b->pos));
	अगर (ख_पढ़ो(पंचांगp, 1, b->pos, file) != b->pos)
		जाओ मुक्त_ग_लिखो;

	अगर (स_भेद(पंचांगp, b->p, b->pos) != 0)
		जाओ मुक्त_ग_लिखो;

	मुक्त(पंचांगp);
	ख_बंद(file);
	वापस;

 मुक्त_ग_लिखो:
	मुक्त(पंचांगp);
 बंद_ग_लिखो:
	ख_बंद(file);
 ग_लिखो:
	ग_लिखो_buf(b, fname);
पूर्ण

/* parse Module.symvers file. line क्रमmat:
 * 0x12345678<tab>symbol<tab>module<tab>export<tab>namespace
 **/
अटल व्योम पढ़ो_dump(स्थिर अक्षर *fname)
अणु
	अक्षर *buf, *pos, *line;

	buf = पढ़ो_text_file(fname);
	अगर (!buf)
		/* No symbol versions, silently ignore */
		वापस;

	pos = buf;

	जबतक ((line = get_line(&pos))) अणु
		अक्षर *symname, *namespace, *modname, *d, *export;
		अचिन्हित पूर्णांक crc;
		काष्ठा module *mod;
		काष्ठा symbol *s;

		अगर (!(symname = म_अक्षर(line, '\t')))
			जाओ fail;
		*symname++ = '\0';
		अगर (!(modname = म_अक्षर(symname, '\t')))
			जाओ fail;
		*modname++ = '\0';
		अगर (!(export = म_अक्षर(modname, '\t')))
			जाओ fail;
		*export++ = '\0';
		अगर (!(namespace = म_अक्षर(export, '\t')))
			जाओ fail;
		*namespace++ = '\0';

		crc = म_से_अदीर्घ(line, &d, 16);
		अगर (*symname == '\0' || *modname == '\0' || *d != '\0')
			जाओ fail;
		mod = find_module(modname);
		अगर (!mod) अणु
			mod = new_module(modname);
			mod->from_dump = 1;
		पूर्ण
		s = sym_add_exported(symname, mod, export_no(export));
		s->is_अटल = 0;
		sym_set_crc(symname, crc);
		sym_update_namespace(symname, namespace);
	पूर्ण
	मुक्त(buf);
	वापस;
fail:
	मुक्त(buf);
	fatal("parse error in symbol dump file\n");
पूर्ण

अटल व्योम ग_लिखो_dump(स्थिर अक्षर *fname)
अणु
	काष्ठा buffer buf = अणु पूर्ण;
	काष्ठा symbol *symbol;
	स्थिर अक्षर *namespace;
	पूर्णांक n;

	क्रम (n = 0; n < SYMBOL_HASH_SIZE ; n++) अणु
		symbol = symbolhash[n];
		जबतक (symbol) अणु
			अगर (!symbol->module->from_dump) अणु
				namespace = symbol->namespace;
				buf_म_लिखो(&buf, "0x%08x\t%s\t%s\t%s\t%s\n",
					   symbol->crc, symbol->name,
					   symbol->module->name,
					   export_str(symbol->export),
					   namespace ? namespace : "");
			पूर्ण
			symbol = symbol->next;
		पूर्ण
	पूर्ण
	ग_लिखो_buf(&buf, fname);
	मुक्त(buf.p);
पूर्ण

अटल व्योम ग_लिखो_namespace_deps_files(स्थिर अक्षर *fname)
अणु
	काष्ठा module *mod;
	काष्ठा namespace_list *ns;
	काष्ठा buffer ns_deps_buf = अणुपूर्ण;

	क्रम (mod = modules; mod; mod = mod->next) अणु

		अगर (mod->from_dump || !mod->missing_namespaces)
			जारी;

		buf_म_लिखो(&ns_deps_buf, "%s.ko:", mod->name);

		क्रम (ns = mod->missing_namespaces; ns; ns = ns->next)
			buf_म_लिखो(&ns_deps_buf, " %s", ns->namespace);

		buf_म_लिखो(&ns_deps_buf, "\n");
	पूर्ण

	ग_लिखो_अगर_changed(&ns_deps_buf, fname);
	मुक्त(ns_deps_buf.p);
पूर्ण

काष्ठा dump_list अणु
	काष्ठा dump_list *next;
	स्थिर अक्षर *file;
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा module *mod;
	काष्ठा buffer buf = अणु पूर्ण;
	अक्षर *missing_namespace_deps = शून्य;
	अक्षर *dump_ग_लिखो = शून्य, *files_source = शून्य;
	पूर्णांक opt;
	पूर्णांक n;
	काष्ठा dump_list *dump_पढ़ो_start = शून्य;
	काष्ठा dump_list **dump_पढ़ो_iter = &dump_पढ़ो_start;

	जबतक ((opt = getopt(argc, argv, "ei:mnT:o:awENd:")) != -1) अणु
		चयन (opt) अणु
		हाल 'e':
			बाह्यal_module = 1;
			अवरोध;
		हाल 'i':
			*dump_पढ़ो_iter =
				NOFAIL(सुस्मृति(1, माप(**dump_पढ़ो_iter)));
			(*dump_पढ़ो_iter)->file = optarg;
			dump_पढ़ो_iter = &(*dump_पढ़ो_iter)->next;
			अवरोध;
		हाल 'm':
			modversions = 1;
			अवरोध;
		हाल 'n':
			ignore_missing_files = 1;
			अवरोध;
		हाल 'o':
			dump_ग_लिखो = optarg;
			अवरोध;
		हाल 'a':
			all_versions = 1;
			अवरोध;
		हाल 'T':
			files_source = optarg;
			अवरोध;
		हाल 'w':
			warn_unresolved = 1;
			अवरोध;
		हाल 'E':
			sec_mismatch_warn_only = false;
			अवरोध;
		हाल 'N':
			allow_missing_ns_imports = 1;
			अवरोध;
		हाल 'd':
			missing_namespace_deps = optarg;
			अवरोध;
		शेष:
			निकास(1);
		पूर्ण
	पूर्ण

	जबतक (dump_पढ़ो_start) अणु
		काष्ठा dump_list *पंचांगp;

		पढ़ो_dump(dump_पढ़ो_start->file);
		पंचांगp = dump_पढ़ो_start->next;
		मुक्त(dump_पढ़ो_start);
		dump_पढ़ो_start = पंचांगp;
	पूर्ण

	जबतक (optind < argc)
		पढ़ो_symbols(argv[optind++]);

	अगर (files_source)
		पढ़ो_symbols_from_files(files_source);

	क्रम (mod = modules; mod; mod = mod->next) अणु
		अक्षर fname[PATH_MAX];

		अगर (mod->is_vmlinux || mod->from_dump)
			जारी;

		buf.pos = 0;

		check_modname_len(mod);
		check_exports(mod);

		add_header(&buf, mod);
		add_पूर्णांकree_flag(&buf, !बाह्यal_module);
		add_retpoline(&buf);
		add_staging_flag(&buf, mod->name);
		add_versions(&buf, mod);
		add_depends(&buf, mod);
		add_moddevtable(&buf, mod);
		add_srcversion(&buf, mod);

		प्र_लिखो(fname, "%s.mod.c", mod->name);
		ग_लिखो_अगर_changed(&buf, fname);
	पूर्ण

	अगर (missing_namespace_deps)
		ग_लिखो_namespace_deps_files(missing_namespace_deps);

	अगर (dump_ग_लिखो)
		ग_लिखो_dump(dump_ग_लिखो);
	अगर (sec_mismatch_count && !sec_mismatch_warn_only)
		error("Section mismatches detected.\n"
		      "Set CONFIG_SECTION_MISMATCH_WARN_ONLY=y to allow them.\n");
	क्रम (n = 0; n < SYMBOL_HASH_SIZE; n++) अणु
		काष्ठा symbol *s;

		क्रम (s = symbolhash[n]; s; s = s->next) अणु
			अगर (s->is_अटल)
				error("\"%s\" [%s] is a static %s\n",
				      s->name, s->module->name,
				      export_str(s->export));
		पूर्ण
	पूर्ण

	अगर (nr_unresolved > MAX_UNRESOLVED_REPORTS)
		warn("suppressed %u unresolved symbol warnings because there were too many)\n",
		     nr_unresolved - MAX_UNRESOLVED_REPORTS);

	मुक्त(buf.p);

	वापस error_occurred ? 1 : 0;
पूर्ण
