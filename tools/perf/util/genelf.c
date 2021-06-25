<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * genelf.c
 * Copyright (C) 2014, Google, Inc
 *
 * Contributed by:
 * 	Stephane Eranian <eranian@gmail.com>
 */

#समावेश <sys/types.h>
#समावेश <मानकघोष.स>
#समावेश <libelf.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <fcntl.h>
#समावेश <err.h>
#अगर_घोषित HAVE_DWARF_SUPPORT
#समावेश <dwarf.h>
#पूर्ण_अगर

#समावेश "genelf.h"
#समावेश "../util/jitdump.h"
#समावेश <linux/compiler.h>

#अगर_अघोषित NT_GNU_BUILD_ID
#घोषणा NT_GNU_BUILD_ID 3
#पूर्ण_अगर

#घोषणा BUILD_ID_URANDOM /* dअगरferent uuid क्रम each run */

#अगर_घोषित HAVE_LIBCRYPTO

#घोषणा BUILD_ID_MD5
#अघोषित BUILD_ID_SHA	/* करोes not seem to work well when linked with Java */
#अघोषित BUILD_ID_URANDOM /* dअगरferent uuid क्रम each run */

#अगर_घोषित BUILD_ID_SHA
#समावेश <खोलोssl/sha.h>
#पूर्ण_अगर

#अगर_घोषित BUILD_ID_MD5
#समावेश <खोलोssl/md5.h>
#पूर्ण_अगर
#पूर्ण_अगर


प्रकार काष्ठा अणु
  अचिन्हित पूर्णांक namesz;  /* Size of entry's owner string */
  अचिन्हित पूर्णांक descsz;  /* Size of the note descriptor */
  अचिन्हित पूर्णांक type;    /* Interpretation of the descriptor */
  अक्षर         name[0]; /* Start of the name+desc data */
पूर्ण Elf_Note;

काष्ठा options अणु
	अक्षर *output;
	पूर्णांक fd;
पूर्ण;

अटल अक्षर shd_string_table[] = अणु
	0,
	'.', 't', 'e', 'x', 't', 0,			/*  1 */
	'.', 's', 'h', 's', 't', 'r', 't', 'a', 'b', 0, /*  7 */
	'.', 's', 'y', 'm', 't', 'a', 'b', 0,		/* 17 */
	'.', 's', 't', 'r', 't', 'a', 'b', 0,		/* 25 */
	'.', 'n', 'o', 't', 'e', '.', 'g', 'n', 'u', '.', 'b', 'u', 'i', 'l', 'd', '-', 'i', 'd', 0, /* 33 */
	'.', 'd', 'e', 'b', 'u', 'g', '_', 'l', 'i', 'n', 'e', 0, /* 52 */
	'.', 'd', 'e', 'b', 'u', 'g', '_', 'i', 'n', 'f', 'o', 0, /* 64 */
	'.', 'd', 'e', 'b', 'u', 'g', '_', 'a', 'b', 'b', 'r', 'e', 'v', 0, /* 76 */
	'.', 'e', 'h', '_', 'f', 'r', 'a', 'm', 'e', '_', 'h', 'd', 'r', 0, /* 90 */
	'.', 'e', 'h', '_', 'f', 'r', 'a', 'm', 'e', 0, /* 104 */
पूर्ण;

अटल काष्ठा buildid_note अणु
	Elf_Note desc;		/* descsz: size of build-id, must be multiple of 4 */
	अक्षर	 name[4];	/* GNU\0 */
	अक्षर	 build_id[20];
पूर्ण bnote;

अटल Elf_Sym symtab[]=अणु
	/* symbol 0 MUST be the undefined symbol */
	अणु .st_name  = 0, /* index in sym_string table */
	  .st_info  = ELF_ST_TYPE(STT_NOTYPE),
	  .st_shndx = 0, /* क्रम now */
	  .st_value = 0x0,
	  .st_other = ELF_ST_VIS(STV_DEFAULT),
	  .st_size  = 0,
	पूर्ण,
	अणु .st_name  = 1, /* index in sym_string table */
	  .st_info  = ELF_ST_BIND(STB_LOCAL) | ELF_ST_TYPE(STT_FUNC),
	  .st_shndx = 1,
	  .st_value = 0, /* क्रम now */
	  .st_other = ELF_ST_VIS(STV_DEFAULT),
	  .st_size  = 0, /* क्रम now */
	पूर्ण
पूर्ण;

#अगर_घोषित BUILD_ID_URANDOM
अटल व्योम
gen_build_id(काष्ठा buildid_note *note,
	     अचिन्हित दीर्घ load_addr __maybe_unused,
	     स्थिर व्योम *code __maybe_unused,
	     माप_प्रकार csize __maybe_unused)
अणु
	पूर्णांक fd;
	माप_प्रकार sz = माप(note->build_id);
	sमाप_प्रकार sret;

	fd = खोलो("/dev/urandom", O_RDONLY);
	अगर (fd == -1)
		err(1, "cannot access /dev/urandom for buildid");

	sret = पढ़ो(fd, note->build_id, sz);

	बंद(fd);

	अगर (sret != (sमाप_प्रकार)sz)
		स_रखो(note->build_id, 0, sz);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित BUILD_ID_SHA
अटल व्योम
gen_build_id(काष्ठा buildid_note *note,
	     अचिन्हित दीर्घ load_addr __maybe_unused,
	     स्थिर व्योम *code,
	     माप_प्रकार csize)
अणु
	अगर (माप(note->build_id) < SHA_DIGEST_LENGTH)
		errx(1, "build_id too small for SHA1");

	SHA1(code, csize, (अचिन्हित अक्षर *)note->build_id);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित BUILD_ID_MD5
अटल व्योम
gen_build_id(काष्ठा buildid_note *note, अचिन्हित दीर्घ load_addr, स्थिर व्योम *code, माप_प्रकार csize)
अणु
	MD5_CTX context;

	अगर (माप(note->build_id) < 16)
		errx(1, "build_id too small for MD5");

	MD5_Init(&context);
	MD5_Update(&context, &load_addr, माप(load_addr));
	MD5_Update(&context, code, csize);
	MD5_Final((अचिन्हित अक्षर *)note->build_id, &context);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
jit_add_eh_frame_info(Elf *e, व्योम* unwinding, uपूर्णांक64_t unwinding_header_size,
		      uपूर्णांक64_t unwinding_size, uपूर्णांक64_t base_offset)
अणु
	Elf_Data *d;
	Elf_Scn *scn;
	Elf_Shdr *shdr;
	uपूर्णांक64_t unwinding_table_size = unwinding_size - unwinding_header_size;

	/*
	 * setup eh_frame section
	 */
	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		वापस -1;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		वापस -1;
	पूर्ण

	d->d_align = 8;
	d->d_off = 0LL;
	d->d_buf = unwinding;
	d->d_type = ELF_T_BYTE;
	d->d_size = unwinding_table_size;
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		वापस -1;
	पूर्ण

	shdr->sh_name = 104;
	shdr->sh_type = SHT_PROGBITS;
	shdr->sh_addr = base_offset;
	shdr->sh_flags = SHF_ALLOC;
	shdr->sh_entsize = 0;

	/*
	 * setup eh_frame_hdr section
	 */
	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		वापस -1;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		वापस -1;
	पूर्ण

	d->d_align = 4;
	d->d_off = 0LL;
	d->d_buf = unwinding + unwinding_table_size;
	d->d_type = ELF_T_BYTE;
	d->d_size = unwinding_header_size;
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		वापस -1;
	पूर्ण

	shdr->sh_name = 90;
	shdr->sh_type = SHT_PROGBITS;
	shdr->sh_addr = base_offset + unwinding_table_size;
	shdr->sh_flags = SHF_ALLOC;
	shdr->sh_entsize = 0;

	वापस 0;
पूर्ण

/*
 * fd: file descriptor खोलो क्रम writing क्रम the output file
 * load_addr: code load address (could be zero, just used क्रम buildid)
 * sym: function name (क्रम native code - used as the symbol)
 * code: the native code
 * csize: the code size in bytes
 */
पूर्णांक
jit_ग_लिखो_elf(पूर्णांक fd, uपूर्णांक64_t load_addr, स्थिर अक्षर *sym,
	      स्थिर व्योम *code, पूर्णांक csize,
	      व्योम *debug __maybe_unused, पूर्णांक nr_debug_entries __maybe_unused,
	      व्योम *unwinding, uपूर्णांक64_t unwinding_header_size, uपूर्णांक64_t unwinding_size)
अणु
	Elf *e;
	Elf_Data *d;
	Elf_Scn *scn;
	Elf_Ehdr *ehdr;
	Elf_Shdr *shdr;
	uपूर्णांक64_t eh_frame_base_offset;
	अक्षर *strsym = शून्य;
	पूर्णांक symlen;
	पूर्णांक retval = -1;

	अगर (elf_version(EV_CURRENT) == EV_NONE) अणु
		warnx("ELF initialization failed");
		वापस -1;
	पूर्ण

	e = elf_begin(fd, ELF_C_WRITE, शून्य);
	अगर (!e) अणु
		warnx("elf_begin failed");
		जाओ error;
	पूर्ण

	/*
	 * setup ELF header
	 */
	ehdr = elf_newehdr(e);
	अगर (!ehdr) अणु
		warnx("cannot get ehdr");
		जाओ error;
	पूर्ण

	ehdr->e_ident[EI_DATA] = GEN_ELF_ENDIAN;
	ehdr->e_ident[EI_CLASS] = GEN_ELF_CLASS;
	ehdr->e_machine = GEN_ELF_ARCH;
	ehdr->e_type = ET_DYN;
	ehdr->e_entry = GEN_ELF_TEXT_OFFSET;
	ehdr->e_version = EV_CURRENT;
	ehdr->e_shstrndx= unwinding ? 4 : 2; /* shdr index क्रम section name */

	/*
	 * setup text section
	 */
	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		जाओ error;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		जाओ error;
	पूर्ण

	d->d_align = 16;
	d->d_off = 0LL;
	d->d_buf = (व्योम *)code;
	d->d_type = ELF_T_BYTE;
	d->d_size = csize;
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		जाओ error;
	पूर्ण

	shdr->sh_name = 1;
	shdr->sh_type = SHT_PROGBITS;
	shdr->sh_addr = GEN_ELF_TEXT_OFFSET;
	shdr->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	shdr->sh_entsize = 0;

	/*
	 * Setup .eh_frame_hdr and .eh_frame
	 */
	अगर (unwinding) अणु
		eh_frame_base_offset = ALIGN_8(GEN_ELF_TEXT_OFFSET + csize);
		retval = jit_add_eh_frame_info(e, unwinding,
					       unwinding_header_size, unwinding_size,
					       eh_frame_base_offset);
		अगर (retval)
			जाओ error;
	पूर्ण

	/*
	 * setup section headers string table
	 */
	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		जाओ error;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		जाओ error;
	पूर्ण

	d->d_align = 1;
	d->d_off = 0LL;
	d->d_buf = shd_string_table;
	d->d_type = ELF_T_BYTE;
	d->d_size = माप(shd_string_table);
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		जाओ error;
	पूर्ण

	shdr->sh_name = 7; /* offset of '.shstrtab' in shd_string_table */
	shdr->sh_type = SHT_STRTAB;
	shdr->sh_flags = 0;
	shdr->sh_entsize = 0;

	/*
	 * setup symtab section
	 */
	symtab[1].st_size  = csize;
	symtab[1].st_value = GEN_ELF_TEXT_OFFSET;

	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		जाओ error;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		जाओ error;
	पूर्ण

	d->d_align = 8;
	d->d_off = 0LL;
	d->d_buf = symtab;
	d->d_type = ELF_T_SYM;
	d->d_size = माप(symtab);
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		जाओ error;
	पूर्ण

	shdr->sh_name = 17; /* offset of '.symtab' in shd_string_table */
	shdr->sh_type = SHT_SYMTAB;
	shdr->sh_flags = 0;
	shdr->sh_entsize = माप(Elf_Sym);
	shdr->sh_link = unwinding ? 6 : 4; /* index of .strtab section */

	/*
	 * setup symbols string table
	 * 2 = 1 क्रम 0 in 1st entry, 1 क्रम the 0 at end of symbol क्रम 2nd entry
	 */
	symlen = 2 + म_माप(sym);
	strsym = सुस्मृति(1, symlen);
	अगर (!strsym) अणु
		warnx("cannot allocate strsym");
		जाओ error;
	पूर्ण
	म_नकल(strsym + 1, sym);

	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		जाओ error;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		जाओ error;
	पूर्ण

	d->d_align = 1;
	d->d_off = 0LL;
	d->d_buf = strsym;
	d->d_type = ELF_T_BYTE;
	d->d_size = symlen;
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		जाओ error;
	पूर्ण

	shdr->sh_name = 25; /* offset in shd_string_table */
	shdr->sh_type = SHT_STRTAB;
	shdr->sh_flags = 0;
	shdr->sh_entsize = 0;

	/*
	 * setup build-id section
	 */
	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		जाओ error;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		जाओ error;
	पूर्ण

	/*
	 * build-id generation
	 */
	gen_build_id(&bnote, load_addr, code, csize);
	bnote.desc.namesz = माप(bnote.name); /* must include 0 termination */
	bnote.desc.descsz = माप(bnote.build_id);
	bnote.desc.type   = NT_GNU_BUILD_ID;
	म_नकल(bnote.name, "GNU");

	d->d_align = 4;
	d->d_off = 0LL;
	d->d_buf = &bnote;
	d->d_type = ELF_T_BYTE;
	d->d_size = माप(bnote);
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		जाओ error;
	पूर्ण

	shdr->sh_name = 33; /* offset in shd_string_table */
	shdr->sh_type = SHT_NOTE;
	shdr->sh_addr = 0x0;
	shdr->sh_flags = SHF_ALLOC;
	shdr->sh_size = माप(bnote);
	shdr->sh_entsize = 0;

#अगर_घोषित HAVE_DWARF_SUPPORT
	अगर (debug && nr_debug_entries) अणु
		retval = jit_add_debug_info(e, load_addr, debug, nr_debug_entries);
		अगर (retval)
			जाओ error;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अगर (elf_update(e, ELF_C_WRITE) < 0) अणु
			warnx("elf_update 4 failed");
			जाओ error;
		पूर्ण
	पूर्ण

	retval = 0;
error:
	(व्योम)elf_end(e);

	मुक्त(strsym);


	वापस retval;
पूर्ण
