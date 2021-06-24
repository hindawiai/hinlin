<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <elf.h>

#समावेश "elfconfig.h"

/* On BSD-alike OSes elf.h defines these according to host's word size */
#अघोषित ELF_ST_BIND
#अघोषित ELF_ST_TYPE
#अघोषित ELF_R_SYM
#अघोषित ELF_R_TYPE

#अगर KERNEL_ELFCLASS == ELFCLASS32

#घोषणा Elf_Ehdr    Elf32_Ehdr
#घोषणा Elf_Shdr    Elf32_Shdr
#घोषणा Elf_Sym     Elf32_Sym
#घोषणा Elf_Addr    Elf32_Addr
#घोषणा Elf_Sword   Elf64_Sword
#घोषणा Elf_Section Elf32_Half
#घोषणा ELF_ST_BIND ELF32_ST_BIND
#घोषणा ELF_ST_TYPE ELF32_ST_TYPE

#घोषणा Elf_Rel     Elf32_Rel
#घोषणा Elf_Rela    Elf32_Rela
#घोषणा ELF_R_SYM   ELF32_R_SYM
#घोषणा ELF_R_TYPE  ELF32_R_TYPE
#अन्यथा

#घोषणा Elf_Ehdr    Elf64_Ehdr
#घोषणा Elf_Shdr    Elf64_Shdr
#घोषणा Elf_Sym     Elf64_Sym
#घोषणा Elf_Addr    Elf64_Addr
#घोषणा Elf_Sword   Elf64_Sxword
#घोषणा Elf_Section Elf64_Half
#घोषणा ELF_ST_BIND ELF64_ST_BIND
#घोषणा ELF_ST_TYPE ELF64_ST_TYPE

#घोषणा Elf_Rel     Elf64_Rel
#घोषणा Elf_Rela    Elf64_Rela
#घोषणा ELF_R_SYM   ELF64_R_SYM
#घोषणा ELF_R_TYPE  ELF64_R_TYPE
#पूर्ण_अगर

/* The 64-bit MIPS ELF ABI uses an unusual reloc क्रमmat. */
प्रकार काष्ठा
अणु
	Elf32_Word    r_sym;	/* Symbol index */
	अचिन्हित अक्षर r_ssym;	/* Special symbol क्रम 2nd relocation */
	अचिन्हित अक्षर r_type3;	/* 3rd relocation type */
	अचिन्हित अक्षर r_type2;	/* 2nd relocation type */
	अचिन्हित अक्षर r_type1;	/* 1st relocation type */
पूर्ण _Elf64_Mips_R_Info;

प्रकार जोड़
अणु
	Elf64_Xword		r_info_number;
	_Elf64_Mips_R_Info	r_info_fields;
पूर्ण _Elf64_Mips_R_Info_जोड़;

#घोषणा ELF64_MIPS_R_SYM(i) \
  ((__extension__ (_Elf64_Mips_R_Info_जोड़)(i)).r_info_fields.r_sym)

#घोषणा ELF64_MIPS_R_TYPE(i) \
  ((__extension__ (_Elf64_Mips_R_Info_जोड़)(i)).r_info_fields.r_type1)

#अगर KERNEL_ELFDATA != HOST_ELFDATA

अटल अंतरभूत व्योम __endian(स्थिर व्योम *src, व्योम *dest, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < size; i++)
		((अचिन्हित अक्षर*)dest)[i] = ((अचिन्हित अक्षर*)src)[size - i-1];
पूर्ण

#घोषणा TO_NATIVE(x)						\
(अणु								\
	typeof(x) __x;						\
	__endian(&(x), &(__x), माप(__x));			\
	__x;							\
पूर्ण)

#अन्यथा /* endianness matches */

#घोषणा TO_NATIVE(x) (x)

#पूर्ण_अगर

#घोषणा NOFAIL(ptr)   करो_nofail((ptr), #ptr)
व्योम *करो_nofail(व्योम *ptr, स्थिर अक्षर *expr);

काष्ठा buffer अणु
	अक्षर *p;
	पूर्णांक pos;
	पूर्णांक size;
पूर्ण;

व्योम __attribute__((क्रमmat(म_लिखो, 2, 3)))
buf_म_लिखो(काष्ठा buffer *buf, स्थिर अक्षर *fmt, ...);

व्योम
buf_ग_लिखो(काष्ठा buffer *buf, स्थिर अक्षर *s, पूर्णांक len);

काष्ठा namespace_list अणु
	काष्ठा namespace_list *next;
	अक्षर namespace[];
पूर्ण;

काष्ठा module अणु
	काष्ठा module *next;
	पूर्णांक gpl_compatible;
	काष्ठा symbol *unres;
	पूर्णांक from_dump;  /* 1 अगर module was loaded from *.symvers */
	पूर्णांक is_vmlinux;
	पूर्णांक seen;
	पूर्णांक has_init;
	पूर्णांक has_cleanup;
	काष्ठा buffer dev_table_buf;
	अक्षर	     srcversion[25];
	// Missing namespace dependencies
	काष्ठा namespace_list *missing_namespaces;
	// Actual imported namespaces
	काष्ठा namespace_list *imported_namespaces;
	अक्षर name[];
पूर्ण;

काष्ठा elf_info अणु
	माप_प्रकार size;
	Elf_Ehdr     *hdr;
	Elf_Shdr     *sechdrs;
	Elf_Sym      *symtab_start;
	Elf_Sym      *symtab_stop;
	Elf_Section  export_sec;
	Elf_Section  export_gpl_sec;
	अक्षर         *strtab;
	अक्षर	     *modinfo;
	अचिन्हित पूर्णांक modinfo_len;

	/* support क्रम 32bit section numbers */

	अचिन्हित पूर्णांक num_sections; /* max_secindex + 1 */
	अचिन्हित पूर्णांक secindex_strings;
	/* अगर Nth symbol table entry has .st_shndx = SHN_XINDEX,
	 * take shndx from symtab_shndx_start[N] instead */
	Elf32_Word   *symtab_shndx_start;
	Elf32_Word   *symtab_shndx_stop;
पूर्ण;

अटल अंतरभूत पूर्णांक is_shndx_special(अचिन्हित पूर्णांक i)
अणु
	वापस i != SHN_XINDEX && i >= SHN_LORESERVE && i <= SHN_HIRESERVE;
पूर्ण

/*
 * Move reserved section indices SHN_LORESERVE..SHN_HIRESERVE out of
 * the way to -256..-1, to aव्योम conflicting with real section
 * indices.
 */
#घोषणा SPECIAL(i) ((i) - (SHN_HIRESERVE + 1))

/* Accessor क्रम sym->st_shndx, hides ugliness of "64k sections" */
अटल अंतरभूत अचिन्हित पूर्णांक get_secindex(स्थिर काष्ठा elf_info *info,
					स्थिर Elf_Sym *sym)
अणु
	अगर (is_shndx_special(sym->st_shndx))
		वापस SPECIAL(sym->st_shndx);
	अगर (sym->st_shndx != SHN_XINDEX)
		वापस sym->st_shndx;
	वापस info->symtab_shndx_start[sym - info->symtab_start];
पूर्ण

अटल अंतरभूत bool strends(स्थिर अक्षर *str, स्थिर अक्षर *postfix)
अणु
	अगर (म_माप(str) < म_माप(postfix))
		वापस false;

	वापस म_भेद(str + म_माप(str) - म_माप(postfix), postfix) == 0;
पूर्ण

/* file2alias.c */
बाह्य अचिन्हित पूर्णांक cross_build;
व्योम handle_moddevtable(काष्ठा module *mod, काष्ठा elf_info *info,
			Elf_Sym *sym, स्थिर अक्षर *symname);
व्योम add_moddevtable(काष्ठा buffer *buf, काष्ठा module *mod);

/* sumversion.c */
व्योम get_src_version(स्थिर अक्षर *modname, अक्षर sum[], अचिन्हित sumlen);

/* from modpost.c */
अक्षर *पढ़ो_text_file(स्थिर अक्षर *filename);
अक्षर *get_line(अक्षर **stringp);

क्रमागत loglevel अणु
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
पूर्ण;

व्योम modpost_log(क्रमागत loglevel loglevel, स्थिर अक्षर *fmt, ...);

/*
 * warn - show the given message, then let modpost जारी running, still
 *        allowing modpost to निकास successfully. This should be used when
 *        we still allow to generate vmlinux and modules.
 *
 * error - show the given message, then let modpost जारी running, but fail
 *         in the end. This should be used when we should stop building vmlinux
 *         or modules, but we can जारी running modpost to catch as many
 *         issues as possible.
 *
 * fatal - show the given message, and bail out immediately. This should be
 *         used when there is no poपूर्णांक to जारी running modpost.
 */
#घोषणा warn(fmt, args...)	modpost_log(LOG_WARN, fmt, ##args)
#घोषणा error(fmt, args...)	modpost_log(LOG_ERROR, fmt, ##args)
#घोषणा fatal(fmt, args...)	modpost_log(LOG_FATAL, fmt, ##args)
