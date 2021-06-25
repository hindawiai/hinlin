<शैली गुरु>
/* Write the contents of the <certfile> पूर्णांकo kernel symbol प्रणाली_extra_cert
 *
 * Copyright (C) IBM Corporation, 2015
 *
 * Author: Mehmet Kayaalp <mkayaalp@linux.vnet.ibm.com>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 * Usage: insert-sys-cert [-s <System.map> -b <vmlinux> -c <certfile>
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <प्रकार.स>
#समावेश <माला.स>
#समावेश <सीमा.स>
#समावेश <stdbool.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <elf.h>

#घोषणा CERT_SYM  "system_extra_cert"
#घोषणा USED_SYM  "system_extra_cert_used"
#घोषणा LSIZE_SYM "system_certificate_list_size"

#घोषणा info(क्रमmat, args...) ख_लिखो(मानक_त्रुटि, "INFO:    " क्रमmat, ## args)
#घोषणा warn(क्रमmat, args...) ख_लिखो(मानक_निकास, "WARNING: " क्रमmat, ## args)
#घोषणा  err(क्रमmat, args...) ख_लिखो(मानक_त्रुटि, "ERROR:   " क्रमmat, ## args)

#अगर UINTPTR_MAX == 0xffffffff
#घोषणा CURRENT_ELFCLASS ELFCLASS32
#घोषणा Elf_Ehdr	Elf32_Ehdr
#घोषणा Elf_Shdr	Elf32_Shdr
#घोषणा Elf_Sym		Elf32_Sym
#अन्यथा
#घोषणा CURRENT_ELFCLASS ELFCLASS64
#घोषणा Elf_Ehdr	Elf64_Ehdr
#घोषणा Elf_Shdr	Elf64_Shdr
#घोषणा Elf_Sym		Elf64_Sym
#पूर्ण_अगर

अटल अचिन्हित अक्षर endianness(व्योम)
अणु
	uपूर्णांक16_t two_byte = 0x00FF;
	uपूर्णांक8_t low_address = *((uपूर्णांक8_t *)&two_byte);

	अगर (low_address == 0)
		वापस ELFDATA2MSB;
	अन्यथा
		वापस ELFDATA2LSB;
पूर्ण

काष्ठा sym अणु
	अक्षर *name;
	अचिन्हित दीर्घ address;
	अचिन्हित दीर्घ offset;
	व्योम *content;
	पूर्णांक size;
पूर्ण;

अटल अचिन्हित दीर्घ get_offset_from_address(Elf_Ehdr *hdr, अचिन्हित दीर्घ addr)
अणु
	Elf_Shdr *x;
	अचिन्हित पूर्णांक i, num_sections;

	x = (व्योम *)hdr + hdr->e_shoff;
	अगर (hdr->e_shnum == SHN_UNDEF)
		num_sections = x[0].sh_size;
	अन्यथा
		num_sections = hdr->e_shnum;

	क्रम (i = 1; i < num_sections; i++) अणु
		अचिन्हित दीर्घ start = x[i].sh_addr;
		अचिन्हित दीर्घ end = start + x[i].sh_size;
		अचिन्हित दीर्घ offset = x[i].sh_offset;

		अगर (addr >= start && addr <= end)
			वापस addr - start + offset;
	पूर्ण
	वापस 0;
पूर्ण


#घोषणा LINE_SIZE 100

अटल व्योम get_symbol_from_map(Elf_Ehdr *hdr, खाता *f, अक्षर *name,
				काष्ठा sym *s)
अणु
	अक्षर l[LINE_SIZE];
	अक्षर *w, *p, *n;

	s->size = 0;
	s->address = 0;
	s->offset = 0;
	अगर (ख_जाओ(f, 0, शुरू_से) != 0) अणु
		लिखो_त्रुटि("File seek failed");
		निकास(निकास_त्रुटि);
	पूर्ण
	जबतक (ख_माला_लो(l, LINE_SIZE, f)) अणु
		p = म_अक्षर(l, '\n');
		अगर (!p) अणु
			err("Missing line ending.\n");
			वापस;
		पूर्ण
		n = म_माला(l, name);
		अगर (n)
			अवरोध;
	पूर्ण
	अगर (!n) अणु
		err("Unable to find symbol: %s\n", name);
		वापस;
	पूर्ण
	w = म_अक्षर(l, ' ');
	अगर (!w)
		वापस;

	*w = '\0';
	s->address = म_से_अदीर्घ(l, शून्य, 16);
	अगर (s->address == 0)
		वापस;
	s->offset = get_offset_from_address(hdr, s->address);
	s->name = name;
	s->content = (व्योम *)hdr + s->offset;
पूर्ण

अटल Elf_Sym *find_elf_symbol(Elf_Ehdr *hdr, Elf_Shdr *symtab, अक्षर *name)
अणु
	Elf_Sym *sym, *symtab_start;
	अक्षर *strtab, *symname;
	अचिन्हित पूर्णांक link;
	Elf_Shdr *x;
	पूर्णांक i, n;

	x = (व्योम *)hdr + hdr->e_shoff;
	link = symtab->sh_link;
	symtab_start = (व्योम *)hdr + symtab->sh_offset;
	n = symtab->sh_size / symtab->sh_entsize;
	strtab = (व्योम *)hdr + x[link].sh_offset;

	क्रम (i = 0; i < n; i++) अणु
		sym = &symtab_start[i];
		symname = strtab + sym->st_name;
		अगर (म_भेद(symname, name) == 0)
			वापस sym;
	पूर्ण
	err("Unable to find symbol: %s\n", name);
	वापस शून्य;
पूर्ण

अटल व्योम get_symbol_from_table(Elf_Ehdr *hdr, Elf_Shdr *symtab,
				  अक्षर *name, काष्ठा sym *s)
अणु
	Elf_Shdr *sec;
	पूर्णांक secndx;
	Elf_Sym *elf_sym;
	Elf_Shdr *x;

	x = (व्योम *)hdr + hdr->e_shoff;
	s->size = 0;
	s->address = 0;
	s->offset = 0;
	elf_sym = find_elf_symbol(hdr, symtab, name);
	अगर (!elf_sym)
		वापस;
	secndx = elf_sym->st_shndx;
	अगर (!secndx)
		वापस;
	sec = &x[secndx];
	s->size = elf_sym->st_size;
	s->address = elf_sym->st_value;
	s->offset = s->address - sec->sh_addr
			       + sec->sh_offset;
	s->name = name;
	s->content = (व्योम *)hdr + s->offset;
पूर्ण

अटल Elf_Shdr *get_symbol_table(Elf_Ehdr *hdr)
अणु
	Elf_Shdr *x;
	अचिन्हित पूर्णांक i, num_sections;

	x = (व्योम *)hdr + hdr->e_shoff;
	अगर (hdr->e_shnum == SHN_UNDEF)
		num_sections = x[0].sh_size;
	अन्यथा
		num_sections = hdr->e_shnum;

	क्रम (i = 1; i < num_sections; i++)
		अगर (x[i].sh_type == SHT_SYMTAB)
			वापस &x[i];
	वापस शून्य;
पूर्ण

अटल व्योम *map_file(अक्षर *file_name, पूर्णांक *size)
अणु
	काष्ठा stat st;
	व्योम *map;
	पूर्णांक fd;

	fd = खोलो(file_name, O_RDWR);
	अगर (fd < 0) अणु
		लिखो_त्रुटि(file_name);
		वापस शून्य;
	पूर्ण
	अगर (ख_स्थिति(fd, &st)) अणु
		लिखो_त्रुटि("Could not determine file size");
		बंद(fd);
		वापस शून्य;
	पूर्ण
	*size = st.st_size;
	map = mmap(शून्य, *size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	अगर (map == MAP_FAILED) अणु
		लिखो_त्रुटि("Mapping to memory failed");
		बंद(fd);
		वापस शून्य;
	पूर्ण
	बंद(fd);
	वापस map;
पूर्ण

अटल अक्षर *पढ़ो_file(अक्षर *file_name, पूर्णांक *size)
अणु
	काष्ठा stat st;
	अक्षर *buf;
	पूर्णांक fd;

	fd = खोलो(file_name, O_RDONLY);
	अगर (fd < 0) अणु
		लिखो_त्रुटि(file_name);
		वापस शून्य;
	पूर्ण
	अगर (ख_स्थिति(fd, &st)) अणु
		लिखो_त्रुटि("Could not determine file size");
		बंद(fd);
		वापस शून्य;
	पूर्ण
	*size = st.st_size;
	buf = दो_स्मृति(*size);
	अगर (!buf) अणु
		लिखो_त्रुटि("Allocating memory failed");
		बंद(fd);
		वापस शून्य;
	पूर्ण
	अगर (पढ़ो(fd, buf, *size) != *size) अणु
		लिखो_त्रुटि("File read failed");
		बंद(fd);
		वापस शून्य;
	पूर्ण
	बंद(fd);
	वापस buf;
पूर्ण

अटल व्योम prपूर्णांक_sym(Elf_Ehdr *hdr, काष्ठा sym *s)
अणु
	info("sym:    %s\n", s->name);
	info("addr:   0x%lx\n", s->address);
	info("size:   %d\n", s->size);
	info("offset: 0x%lx\n", (अचिन्हित दीर्घ)s->offset);
पूर्ण

अटल व्योम prपूर्णांक_usage(अक्षर *e)
अणु
	म_लिखो("Usage %s [-s <System.map>] -b <vmlinux> -c <certfile>\n", e);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *प्रणाली_map_file = शून्य;
	अक्षर *vmlinux_file = शून्य;
	अक्षर *cert_file = शून्य;
	पूर्णांक vmlinux_size;
	पूर्णांक cert_size;
	Elf_Ehdr *hdr;
	अक्षर *cert;
	खाता *प्रणाली_map;
	अचिन्हित दीर्घ *lsize;
	पूर्णांक *used;
	पूर्णांक opt;
	Elf_Shdr *symtab = शून्य;
	काष्ठा sym cert_sym, lsize_sym, used_sym;

	जबतक ((opt = getopt(argc, argv, "b:c:s:")) != -1) अणु
		चयन (opt) अणु
		हाल 's':
			प्रणाली_map_file = optarg;
			अवरोध;
		हाल 'b':
			vmlinux_file = optarg;
			अवरोध;
		हाल 'c':
			cert_file = optarg;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!vmlinux_file || !cert_file) अणु
		prपूर्णांक_usage(argv[0]);
		निकास(निकास_त्रुटि);
	पूर्ण

	cert = पढ़ो_file(cert_file, &cert_size);
	अगर (!cert)
		निकास(निकास_त्रुटि);

	hdr = map_file(vmlinux_file, &vmlinux_size);
	अगर (!hdr)
		निकास(निकास_त्रुटि);

	अगर (vmlinux_size < माप(*hdr)) अणु
		err("Invalid ELF file.\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर ((hdr->e_ident[EI_MAG0] != ELFMAG0) ||
	    (hdr->e_ident[EI_MAG1] != ELFMAG1) ||
	    (hdr->e_ident[EI_MAG2] != ELFMAG2) ||
	    (hdr->e_ident[EI_MAG3] != ELFMAG3)) अणु
		err("Invalid ELF magic.\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (hdr->e_ident[EI_CLASS] != CURRENT_ELFCLASS) अणु
		err("ELF class mismatch.\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (hdr->e_ident[EI_DATA] != endianness()) अणु
		err("ELF endian mismatch.\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (hdr->e_shoff > vmlinux_size) अणु
		err("Could not find section header.\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	symtab = get_symbol_table(hdr);
	अगर (!symtab) अणु
		warn("Could not find the symbol table.\n");
		अगर (!प्रणाली_map_file) अणु
			err("Please provide a System.map file.\n");
			prपूर्णांक_usage(argv[0]);
			निकास(निकास_त्रुटि);
		पूर्ण

		प्रणाली_map = ख_खोलो(प्रणाली_map_file, "r");
		अगर (!प्रणाली_map) अणु
			लिखो_त्रुटि(प्रणाली_map_file);
			निकास(निकास_त्रुटि);
		पूर्ण
		get_symbol_from_map(hdr, प्रणाली_map, CERT_SYM, &cert_sym);
		get_symbol_from_map(hdr, प्रणाली_map, USED_SYM, &used_sym);
		get_symbol_from_map(hdr, प्रणाली_map, LSIZE_SYM, &lsize_sym);
		cert_sym.size = used_sym.address - cert_sym.address;
	पूर्ण अन्यथा अणु
		info("Symbol table found.\n");
		अगर (प्रणाली_map_file)
			warn("System.map is ignored.\n");
		get_symbol_from_table(hdr, symtab, CERT_SYM, &cert_sym);
		get_symbol_from_table(hdr, symtab, USED_SYM, &used_sym);
		get_symbol_from_table(hdr, symtab, LSIZE_SYM, &lsize_sym);
	पूर्ण

	अगर (!cert_sym.offset || !lsize_sym.offset || !used_sym.offset)
		निकास(निकास_त्रुटि);

	prपूर्णांक_sym(hdr, &cert_sym);
	prपूर्णांक_sym(hdr, &used_sym);
	prपूर्णांक_sym(hdr, &lsize_sym);

	lsize = (अचिन्हित दीर्घ *)lsize_sym.content;
	used = (पूर्णांक *)used_sym.content;

	अगर (cert_sym.size < cert_size) अणु
		err("Certificate is larger than the reserved area!\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* If the existing cert is the same, करोn't overग_लिखो */
	अगर (cert_size == *used &&
	    म_भेदन(cert_sym.content, cert, cert_size) == 0) अणु
		warn("Certificate was already inserted.\n");
		निकास(निकास_सफल);
	पूर्ण

	अगर (*used > 0)
		warn("Replacing previously inserted certificate.\n");

	स_नकल(cert_sym.content, cert, cert_size);
	अगर (cert_size < cert_sym.size)
		स_रखो(cert_sym.content + cert_size,
			0, cert_sym.size - cert_size);

	*lsize = *lsize + cert_size - *used;
	*used = cert_size;
	info("Inserted the contents of %s into %lx.\n", cert_file,
						cert_sym.address);
	info("Used %d bytes out of %d bytes reserved.\n", *used,
						 cert_sym.size);
	निकास(निकास_सफल);
पूर्ण
