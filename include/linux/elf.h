<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ELF_H
#घोषणा _LINUX_ELF_H

#समावेश <linux/types.h>
#समावेश <यंत्र/elf.h>
#समावेश <uapi/linux/elf.h>

#अगर_अघोषित elf_पढ़ो_implies_exec
  /* Executables क्रम which elf_पढ़ो_implies_exec() वापसs TRUE will
     have the READ_IMPLIES_EXEC personality flag set स्वतःmatically.
     Override in यंत्र/elf.h as needed.  */
# define elf_पढ़ो_implies_exec(ex, have_pt_gnu_stack)	0
#पूर्ण_अगर
#अगर_अघोषित SET_PERSONALITY
#घोषणा SET_PERSONALITY(ex) \
	set_personality(PER_LINUX | (current->personality & (~PER_MASK)))
#पूर्ण_अगर

#अगर_अघोषित SET_PERSONALITY2
#घोषणा SET_PERSONALITY2(ex, state) \
	SET_PERSONALITY(ex)
#पूर्ण_अगर

#अगर_अघोषित START_THREAD
#घोषणा START_THREAD(elf_ex, regs, elf_entry, start_stack)	\
	start_thपढ़ो(regs, elf_entry, start_stack)
#पूर्ण_अगर

#अगर defined(ARCH_HAS_SETUP_ADDITIONAL_PAGES) && !defined(ARCH_SETUP_ADDITIONAL_PAGES)
#घोषणा ARCH_SETUP_ADDITIONAL_PAGES(bprm, ex, पूर्णांकerpreter) \
	arch_setup_additional_pages(bprm, पूर्णांकerpreter)
#पूर्ण_अगर

#घोषणा ELF32_GNU_PROPERTY_ALIGN	4
#घोषणा ELF64_GNU_PROPERTY_ALIGN	8

#अगर ELF_CLASS == ELFCLASS32

बाह्य Elf32_Dyn _DYNAMIC [];
#घोषणा elfhdr		elf32_hdr
#घोषणा elf_phdr	elf32_phdr
#घोषणा elf_shdr	elf32_shdr
#घोषणा elf_note	elf32_note
#घोषणा elf_addr_t	Elf32_Off
#घोषणा Elf_Half	Elf32_Half
#घोषणा Elf_Word	Elf32_Word
#घोषणा ELF_GNU_PROPERTY_ALIGN	ELF32_GNU_PROPERTY_ALIGN

#अन्यथा

बाह्य Elf64_Dyn _DYNAMIC [];
#घोषणा elfhdr		elf64_hdr
#घोषणा elf_phdr	elf64_phdr
#घोषणा elf_shdr	elf64_shdr
#घोषणा elf_note	elf64_note
#घोषणा elf_addr_t	Elf64_Off
#घोषणा Elf_Half	Elf64_Half
#घोषणा Elf_Word	Elf64_Word
#घोषणा ELF_GNU_PROPERTY_ALIGN	ELF64_GNU_PROPERTY_ALIGN

#पूर्ण_अगर

/* Optional callbacks to ग_लिखो extra ELF notes. */
काष्ठा file;
काष्ठा coredump_params;

#अगर_अघोषित ARCH_HAVE_EXTRA_ELF_NOTES
अटल अंतरभूत पूर्णांक elf_coredump_extra_notes_size(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक elf_coredump_extra_notes_ग_लिखो(काष्ठा coredump_params *cprm) अणु वापस 0; पूर्ण
#अन्यथा
बाह्य पूर्णांक elf_coredump_extra_notes_size(व्योम);
बाह्य पूर्णांक elf_coredump_extra_notes_ग_लिखो(काष्ठा coredump_params *cprm);
#पूर्ण_अगर

/*
 * NT_GNU_PROPERTY_TYPE_0 header:
 * Keep this पूर्णांकernal until/unless there is an agreed UAPI definition.
 * pr_type values (GNU_PROPERTY_*) are खुला and defined in the UAPI header.
 */
काष्ठा gnu_property अणु
	u32 pr_type;
	u32 pr_datasz;
पूर्ण;

काष्ठा arch_elf_state;

#अगर_अघोषित CONFIG_ARCH_USE_GNU_PROPERTY
अटल अंतरभूत पूर्णांक arch_parse_elf_property(u32 type, स्थिर व्योम *data,
					  माप_प्रकार datasz, bool compat,
					  काष्ठा arch_elf_state *arch)
अणु
	वापस 0;
पूर्ण
#अन्यथा
बाह्य पूर्णांक arch_parse_elf_property(u32 type, स्थिर व्योम *data, माप_प्रकार datasz,
				   bool compat, काष्ठा arch_elf_state *arch);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_HAVE_ELF_PROT
पूर्णांक arch_elf_adjust_prot(पूर्णांक prot, स्थिर काष्ठा arch_elf_state *state,
			 bool has_पूर्णांकerp, bool is_पूर्णांकerp);
#अन्यथा
अटल अंतरभूत पूर्णांक arch_elf_adjust_prot(पूर्णांक prot,
				       स्थिर काष्ठा arch_elf_state *state,
				       bool has_पूर्णांकerp, bool is_पूर्णांकerp)
अणु
	वापस prot;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_ELF_H */
