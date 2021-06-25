<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Remote processor elf helpers defines
 *
 * Copyright (C) 2020 Kalray, Inc.
 */

#अगर_अघोषित REMOTEPROC_ELF_LOADER_H
#घोषणा REMOTEPROC_ELF_LOADER_H

#समावेश <linux/elf.h>
#समावेश <linux/types.h>

/**
 * fw_elf_get_class - Get elf class
 * @fw: the ELF firmware image
 *
 * Note that we use and elf32_hdr to access the class since the start of the
 * काष्ठा is the same क्रम both elf class
 *
 * Return: elf class of the firmware
 */
अटल अंतरभूत u8 fw_elf_get_class(स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा elf32_hdr *ehdr = (काष्ठा elf32_hdr *)fw->data;

	वापस ehdr->e_ident[EI_CLASS];
पूर्ण

अटल अंतरभूत व्योम elf_hdr_init_ident(काष्ठा elf32_hdr *hdr, u8 class)
अणु
	स_नकल(hdr->e_ident, ELFMAG, SELFMAG);
	hdr->e_ident[EI_CLASS] = class;
	hdr->e_ident[EI_DATA] = ELFDATA2LSB;
	hdr->e_ident[EI_VERSION] = EV_CURRENT;
	hdr->e_ident[EI_OSABI] = ELFOSABI_NONE;
पूर्ण

/* Generate getter and setter क्रम a specअगरic elf काष्ठा/field */
#घोषणा ELF_GEN_FIELD_GET_SET(__s, __field, __type) \
अटल अंतरभूत __type elf_##__s##_get_##__field(u8 class, स्थिर व्योम *arg) \
अणु \
	अगर (class == ELFCLASS32) \
		वापस (__type) ((स्थिर काष्ठा elf32_##__s *) arg)->__field; \
	अन्यथा \
		वापस (__type) ((स्थिर काष्ठा elf64_##__s *) arg)->__field; \
पूर्ण \
अटल अंतरभूत व्योम elf_##__s##_set_##__field(u8 class, व्योम *arg, \
					     __type value) \
अणु \
	अगर (class == ELFCLASS32) \
		((काष्ठा elf32_##__s *) arg)->__field = (__type) value; \
	अन्यथा \
		((काष्ठा elf64_##__s *) arg)->__field = (__type) value; \
पूर्ण

ELF_GEN_FIELD_GET_SET(hdr, e_entry, u64)
ELF_GEN_FIELD_GET_SET(hdr, e_phnum, u16)
ELF_GEN_FIELD_GET_SET(hdr, e_shnum, u16)
ELF_GEN_FIELD_GET_SET(hdr, e_phoff, u64)
ELF_GEN_FIELD_GET_SET(hdr, e_shoff, u64)
ELF_GEN_FIELD_GET_SET(hdr, e_shstrndx, u16)
ELF_GEN_FIELD_GET_SET(hdr, e_machine, u16)
ELF_GEN_FIELD_GET_SET(hdr, e_type, u16)
ELF_GEN_FIELD_GET_SET(hdr, e_version, u32)
ELF_GEN_FIELD_GET_SET(hdr, e_ehsize, u32)
ELF_GEN_FIELD_GET_SET(hdr, e_phentsize, u16)
ELF_GEN_FIELD_GET_SET(hdr, e_shentsize, u16)

ELF_GEN_FIELD_GET_SET(phdr, p_paddr, u64)
ELF_GEN_FIELD_GET_SET(phdr, p_vaddr, u64)
ELF_GEN_FIELD_GET_SET(phdr, p_filesz, u64)
ELF_GEN_FIELD_GET_SET(phdr, p_memsz, u64)
ELF_GEN_FIELD_GET_SET(phdr, p_type, u32)
ELF_GEN_FIELD_GET_SET(phdr, p_offset, u64)
ELF_GEN_FIELD_GET_SET(phdr, p_flags, u32)
ELF_GEN_FIELD_GET_SET(phdr, p_align, u64)

ELF_GEN_FIELD_GET_SET(shdr, sh_type, u32)
ELF_GEN_FIELD_GET_SET(shdr, sh_flags, u32)
ELF_GEN_FIELD_GET_SET(shdr, sh_entsize, u16)
ELF_GEN_FIELD_GET_SET(shdr, sh_size, u64)
ELF_GEN_FIELD_GET_SET(shdr, sh_offset, u64)
ELF_GEN_FIELD_GET_SET(shdr, sh_name, u32)
ELF_GEN_FIELD_GET_SET(shdr, sh_addr, u64)

#घोषणा ELF_STRUCT_SIZE(__s) \
अटल अंतरभूत अचिन्हित दीर्घ elf_size_of_##__s(u8 class) \
अणु \
	अगर (class == ELFCLASS32)\
		वापस माप(काष्ठा elf32_##__s); \
	अन्यथा \
		वापस माप(काष्ठा elf64_##__s); \
पूर्ण

ELF_STRUCT_SIZE(shdr)
ELF_STRUCT_SIZE(phdr)
ELF_STRUCT_SIZE(hdr)

अटल अंतरभूत अचिन्हित पूर्णांक elf_strtbl_add(स्थिर अक्षर *name, व्योम *ehdr, u8 class, माप_प्रकार *index)
अणु
	u16 shstrndx = elf_hdr_get_e_shstrndx(class, ehdr);
	व्योम *shdr;
	अक्षर *strtab;
	माप_प्रकार idx, ret;

	shdr = ehdr + elf_size_of_hdr(class) + shstrndx * elf_size_of_shdr(class);
	strtab = ehdr + elf_shdr_get_sh_offset(class, shdr);
	idx = index ? *index : 0;
	अगर (!strtab || !name)
		वापस 0;

	ret = idx;
	म_नकल((strtab + idx), name);
	idx += म_माप(name) + 1;
	अगर (index)
		*index = idx;

	वापस ret;
पूर्ण

#पूर्ण_अगर /* REMOTEPROC_ELF_LOADER_H */
