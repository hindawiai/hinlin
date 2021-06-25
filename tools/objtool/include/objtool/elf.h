<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#अगर_अघोषित _OBJTOOL_ELF_H
#घोषणा _OBJTOOL_ELF_H

#समावेश <मानकपन.स>
#समावेश <gelf.h>
#समावेश <linux/list.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/jhash.h>

#अगर_घोषित LIBELF_USE_DEPRECATED
# define elf_माला_लोhdrnum    elf_माला_लोhnum
# define elf_माला_लोhdrstrndx elf_माला_लोhstrndx
#पूर्ण_अगर

/*
 * Fallback क्रम प्रणालीs without this "read, mmaping if possible" cmd.
 */
#अगर_अघोषित ELF_C_READ_MMAP
#घोषणा ELF_C_READ_MMAP ELF_C_READ
#पूर्ण_अगर

काष्ठा section अणु
	काष्ठा list_head list;
	काष्ठा hlist_node hash;
	काष्ठा hlist_node name_hash;
	GElf_Shdr sh;
	काष्ठा rb_root symbol_tree;
	काष्ठा list_head symbol_list;
	काष्ठा list_head reloc_list;
	काष्ठा section *base, *reloc;
	काष्ठा symbol *sym;
	Elf_Data *data;
	अक्षर *name;
	पूर्णांक idx;
	अचिन्हित पूर्णांक len;
	bool changed, text, rodata, noinstr;
पूर्ण;

काष्ठा symbol अणु
	काष्ठा list_head list;
	काष्ठा rb_node node;
	काष्ठा hlist_node hash;
	काष्ठा hlist_node name_hash;
	GElf_Sym sym;
	काष्ठा section *sec;
	अक्षर *name;
	अचिन्हित पूर्णांक idx;
	अचिन्हित अक्षर bind, type;
	अचिन्हित दीर्घ offset;
	अचिन्हित पूर्णांक len;
	काष्ठा symbol *pfunc, *cfunc, *alias;
	bool uaccess_safe;
	bool अटल_call_tramp;
पूर्ण;

काष्ठा reloc अणु
	काष्ठा list_head list;
	काष्ठा hlist_node hash;
	जोड़ अणु
		GElf_Rela rela;
		GElf_Rel  rel;
	पूर्ण;
	काष्ठा section *sec;
	काष्ठा symbol *sym;
	अचिन्हित दीर्घ offset;
	अचिन्हित पूर्णांक type;
	पूर्णांक addend;
	पूर्णांक idx;
	bool jump_table_start;
पूर्ण;

#घोषणा ELF_HASH_BITS	20

काष्ठा elf अणु
	Elf *elf;
	GElf_Ehdr ehdr;
	पूर्णांक fd;
	bool changed;
	अक्षर *name;
	काष्ठा list_head sections;
	DECLARE_HASHTABLE(symbol_hash, ELF_HASH_BITS);
	DECLARE_HASHTABLE(symbol_name_hash, ELF_HASH_BITS);
	DECLARE_HASHTABLE(section_hash, ELF_HASH_BITS);
	DECLARE_HASHTABLE(section_name_hash, ELF_HASH_BITS);
	DECLARE_HASHTABLE(reloc_hash, ELF_HASH_BITS);
पूर्ण;

#घोषणा OFFSET_STRIDE_BITS	4
#घोषणा OFFSET_STRIDE		(1UL << OFFSET_STRIDE_BITS)
#घोषणा OFFSET_STRIDE_MASK	(~(OFFSET_STRIDE - 1))

#घोषणा क्रम_offset_range(_offset, _start, _end)			\
	क्रम (_offset = ((_start) & OFFSET_STRIDE_MASK);		\
	     _offset >= ((_start) & OFFSET_STRIDE_MASK) &&	\
	     _offset <= ((_end) & OFFSET_STRIDE_MASK);		\
	     _offset += OFFSET_STRIDE)

अटल अंतरभूत u32 sec_offset_hash(काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	u32 ol, oh, idx = sec->idx;

	offset &= OFFSET_STRIDE_MASK;

	ol = offset;
	oh = (offset >> 16) >> 16;

	__jhash_mix(ol, oh, idx);

	वापस ol;
पूर्ण

अटल अंतरभूत u32 reloc_hash(काष्ठा reloc *reloc)
अणु
	वापस sec_offset_hash(reloc->sec, reloc->offset);
पूर्ण

काष्ठा elf *elf_खोलो_पढ़ो(स्थिर अक्षर *name, पूर्णांक flags);
काष्ठा section *elf_create_section(काष्ठा elf *elf, स्थिर अक्षर *name, अचिन्हित पूर्णांक sh_flags, माप_प्रकार entsize, पूर्णांक nr);

पूर्णांक elf_add_reloc(काष्ठा elf *elf, काष्ठा section *sec, अचिन्हित दीर्घ offset,
		  अचिन्हित पूर्णांक type, काष्ठा symbol *sym, पूर्णांक addend);
पूर्णांक elf_add_reloc_to_insn(काष्ठा elf *elf, काष्ठा section *sec,
			  अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक type,
			  काष्ठा section *insn_sec, अचिन्हित दीर्घ insn_off);

पूर्णांक elf_ग_लिखो_insn(काष्ठा elf *elf, काष्ठा section *sec,
		   अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक len,
		   स्थिर अक्षर *insn);
पूर्णांक elf_ग_लिखो_reloc(काष्ठा elf *elf, काष्ठा reloc *reloc);
काष्ठा symbol *elf_create_undef_symbol(काष्ठा elf *elf, स्थिर अक्षर *name);
पूर्णांक elf_ग_लिखो(काष्ठा elf *elf);
व्योम elf_बंद(काष्ठा elf *elf);

काष्ठा section *find_section_by_name(स्थिर काष्ठा elf *elf, स्थिर अक्षर *name);
काष्ठा symbol *find_func_by_offset(काष्ठा section *sec, अचिन्हित दीर्घ offset);
काष्ठा symbol *find_symbol_by_offset(काष्ठा section *sec, अचिन्हित दीर्घ offset);
काष्ठा symbol *find_symbol_by_name(स्थिर काष्ठा elf *elf, स्थिर अक्षर *name);
काष्ठा symbol *find_symbol_containing(स्थिर काष्ठा section *sec, अचिन्हित दीर्घ offset);
काष्ठा reloc *find_reloc_by_dest(स्थिर काष्ठा elf *elf, काष्ठा section *sec, अचिन्हित दीर्घ offset);
काष्ठा reloc *find_reloc_by_dest_range(स्थिर काष्ठा elf *elf, काष्ठा section *sec,
				     अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक len);
काष्ठा symbol *find_func_containing(काष्ठा section *sec, अचिन्हित दीर्घ offset);

#घोषणा क्रम_each_sec(file, sec)						\
	list_क्रम_each_entry(sec, &file->elf->sections, list)

#पूर्ण_अगर /* _OBJTOOL_ELF_H */
