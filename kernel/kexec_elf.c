<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Load ELF vmlinux file क्रम the kexec_file_load syscall.
 *
 * Copyright (C) 2004  Adam Litke (agl@us.ibm.com)
 * Copyright (C) 2004  IBM Corp.
 * Copyright (C) 2005  R Sharada (sharada@in.ibm.com)
 * Copyright (C) 2006  Mohan Kumar M (mohan@in.ibm.com)
 * Copyright (C) 2016  IBM Corporation
 *
 * Based on kexec-tools' kexec-elf-exec.c and kexec-elf-ppc64.c.
 * Heavily modअगरied क्रम the kernel by
 * Thiago Jung Bauermann <bauerman@linux.vnet.ibm.com>.
 */

#घोषणा pr_fmt(fmt)	"kexec_elf: " fmt

#समावेश <linux/elf.h>
#समावेश <linux/kexec.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

अटल अंतरभूत bool elf_is_elf_file(स्थिर काष्ठा elfhdr *ehdr)
अणु
	वापस स_भेद(ehdr->e_ident, ELFMAG, SELFMAG) == 0;
पूर्ण

अटल uपूर्णांक64_t elf64_to_cpu(स्थिर काष्ठा elfhdr *ehdr, uपूर्णांक64_t value)
अणु
	अगर (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
		value = le64_to_cpu(value);
	अन्यथा अगर (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
		value = be64_to_cpu(value);

	वापस value;
पूर्ण

अटल uपूर्णांक32_t elf32_to_cpu(स्थिर काष्ठा elfhdr *ehdr, uपूर्णांक32_t value)
अणु
	अगर (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
		value = le32_to_cpu(value);
	अन्यथा अगर (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
		value = be32_to_cpu(value);

	वापस value;
पूर्ण

अटल uपूर्णांक16_t elf16_to_cpu(स्थिर काष्ठा elfhdr *ehdr, uपूर्णांक16_t value)
अणु
	अगर (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
		value = le16_to_cpu(value);
	अन्यथा अगर (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
		value = be16_to_cpu(value);

	वापस value;
पूर्ण

/**
 * elf_is_ehdr_sane - check that it is safe to use the ELF header
 * @buf_len:	size of the buffer in which the ELF file is loaded.
 */
अटल bool elf_is_ehdr_sane(स्थिर काष्ठा elfhdr *ehdr, माप_प्रकार buf_len)
अणु
	अगर (ehdr->e_phnum > 0 && ehdr->e_phentsize != माप(काष्ठा elf_phdr)) अणु
		pr_debug("Bad program header size.\n");
		वापस false;
	पूर्ण अन्यथा अगर (ehdr->e_shnum > 0 &&
		   ehdr->e_shentsize != माप(काष्ठा elf_shdr)) अणु
		pr_debug("Bad section header size.\n");
		वापस false;
	पूर्ण अन्यथा अगर (ehdr->e_ident[EI_VERSION] != EV_CURRENT ||
		   ehdr->e_version != EV_CURRENT) अणु
		pr_debug("Unknown ELF version.\n");
		वापस false;
	पूर्ण

	अगर (ehdr->e_phoff > 0 && ehdr->e_phnum > 0) अणु
		माप_प्रकार phdr_size;

		/*
		 * e_phnum is at most 65535 so calculating the size of the
		 * program header cannot overflow.
		 */
		phdr_size = माप(काष्ठा elf_phdr) * ehdr->e_phnum;

		/* Sanity check the program header table location. */
		अगर (ehdr->e_phoff + phdr_size < ehdr->e_phoff) अणु
			pr_debug("Program headers at invalid location.\n");
			वापस false;
		पूर्ण अन्यथा अगर (ehdr->e_phoff + phdr_size > buf_len) अणु
			pr_debug("Program headers truncated.\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (ehdr->e_shoff > 0 && ehdr->e_shnum > 0) अणु
		माप_प्रकार shdr_size;

		/*
		 * e_shnum is at most 65536 so calculating
		 * the size of the section header cannot overflow.
		 */
		shdr_size = माप(काष्ठा elf_shdr) * ehdr->e_shnum;

		/* Sanity check the section header table location. */
		अगर (ehdr->e_shoff + shdr_size < ehdr->e_shoff) अणु
			pr_debug("Section headers at invalid location.\n");
			वापस false;
		पूर्ण अन्यथा अगर (ehdr->e_shoff + shdr_size > buf_len) अणु
			pr_debug("Section headers truncated.\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक elf_पढ़ो_ehdr(स्थिर अक्षर *buf, माप_प्रकार len, काष्ठा elfhdr *ehdr)
अणु
	काष्ठा elfhdr *buf_ehdr;

	अगर (len < माप(*buf_ehdr)) अणु
		pr_debug("Buffer is too small to hold ELF header.\n");
		वापस -ENOEXEC;
	पूर्ण

	स_रखो(ehdr, 0, माप(*ehdr));
	स_नकल(ehdr->e_ident, buf, माप(ehdr->e_ident));
	अगर (!elf_is_elf_file(ehdr)) अणु
		pr_debug("No ELF header magic.\n");
		वापस -ENOEXEC;
	पूर्ण

	अगर (ehdr->e_ident[EI_CLASS] != ELF_CLASS) अणु
		pr_debug("Not a supported ELF class.\n");
		वापस -ENOEXEC;
	पूर्ण अन्यथा  अगर (ehdr->e_ident[EI_DATA] != ELFDATA2LSB &&
		ehdr->e_ident[EI_DATA] != ELFDATA2MSB) अणु
		pr_debug("Not a supported ELF data format.\n");
		वापस -ENOEXEC;
	पूर्ण

	buf_ehdr = (काष्ठा elfhdr *) buf;
	अगर (elf16_to_cpu(ehdr, buf_ehdr->e_ehsize) != माप(*buf_ehdr)) अणु
		pr_debug("Bad ELF header size.\n");
		वापस -ENOEXEC;
	पूर्ण

	ehdr->e_type      = elf16_to_cpu(ehdr, buf_ehdr->e_type);
	ehdr->e_machine   = elf16_to_cpu(ehdr, buf_ehdr->e_machine);
	ehdr->e_version   = elf32_to_cpu(ehdr, buf_ehdr->e_version);
	ehdr->e_flags     = elf32_to_cpu(ehdr, buf_ehdr->e_flags);
	ehdr->e_phentsize = elf16_to_cpu(ehdr, buf_ehdr->e_phentsize);
	ehdr->e_phnum     = elf16_to_cpu(ehdr, buf_ehdr->e_phnum);
	ehdr->e_shentsize = elf16_to_cpu(ehdr, buf_ehdr->e_shentsize);
	ehdr->e_shnum     = elf16_to_cpu(ehdr, buf_ehdr->e_shnum);
	ehdr->e_shstrndx  = elf16_to_cpu(ehdr, buf_ehdr->e_shstrndx);

	चयन (ehdr->e_ident[EI_CLASS]) अणु
	हाल ELFCLASS64:
		ehdr->e_entry = elf64_to_cpu(ehdr, buf_ehdr->e_entry);
		ehdr->e_phoff = elf64_to_cpu(ehdr, buf_ehdr->e_phoff);
		ehdr->e_shoff = elf64_to_cpu(ehdr, buf_ehdr->e_shoff);
		अवरोध;

	हाल ELFCLASS32:
		ehdr->e_entry = elf32_to_cpu(ehdr, buf_ehdr->e_entry);
		ehdr->e_phoff = elf32_to_cpu(ehdr, buf_ehdr->e_phoff);
		ehdr->e_shoff = elf32_to_cpu(ehdr, buf_ehdr->e_shoff);
		अवरोध;

	शेष:
		pr_debug("Unknown ELF class.\n");
		वापस -EINVAL;
	पूर्ण

	वापस elf_is_ehdr_sane(ehdr, len) ? 0 : -ENOEXEC;
पूर्ण

/**
 * elf_is_phdr_sane - check that it is safe to use the program header
 * @buf_len:	size of the buffer in which the ELF file is loaded.
 */
अटल bool elf_is_phdr_sane(स्थिर काष्ठा elf_phdr *phdr, माप_प्रकार buf_len)
अणु

	अगर (phdr->p_offset + phdr->p_filesz < phdr->p_offset) अणु
		pr_debug("ELF segment location wraps around.\n");
		वापस false;
	पूर्ण अन्यथा अगर (phdr->p_offset + phdr->p_filesz > buf_len) अणु
		pr_debug("ELF segment not in file.\n");
		वापस false;
	पूर्ण अन्यथा अगर (phdr->p_paddr + phdr->p_memsz < phdr->p_paddr) अणु
		pr_debug("ELF segment address wraps around.\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक elf_पढ़ो_phdr(स्थिर अक्षर *buf, माप_प्रकार len,
			 काष्ठा kexec_elf_info *elf_info,
			 पूर्णांक idx)
अणु
	/* Override the स्थिर in proghdrs, we are the ones करोing the loading. */
	काष्ठा elf_phdr *phdr = (काष्ठा elf_phdr *) &elf_info->proghdrs[idx];
	स्थिर काष्ठा elfhdr *ehdr = elf_info->ehdr;
	स्थिर अक्षर *pbuf;
	काष्ठा elf_phdr *buf_phdr;

	pbuf = buf + elf_info->ehdr->e_phoff + (idx * माप(*buf_phdr));
	buf_phdr = (काष्ठा elf_phdr *) pbuf;

	phdr->p_type   = elf32_to_cpu(elf_info->ehdr, buf_phdr->p_type);
	phdr->p_flags  = elf32_to_cpu(elf_info->ehdr, buf_phdr->p_flags);

	चयन (ehdr->e_ident[EI_CLASS]) अणु
	हाल ELFCLASS64:
		phdr->p_offset = elf64_to_cpu(ehdr, buf_phdr->p_offset);
		phdr->p_paddr  = elf64_to_cpu(ehdr, buf_phdr->p_paddr);
		phdr->p_vaddr  = elf64_to_cpu(ehdr, buf_phdr->p_vaddr);
		phdr->p_filesz = elf64_to_cpu(ehdr, buf_phdr->p_filesz);
		phdr->p_memsz  = elf64_to_cpu(ehdr, buf_phdr->p_memsz);
		phdr->p_align  = elf64_to_cpu(ehdr, buf_phdr->p_align);
		अवरोध;

	हाल ELFCLASS32:
		phdr->p_offset = elf32_to_cpu(ehdr, buf_phdr->p_offset);
		phdr->p_paddr  = elf32_to_cpu(ehdr, buf_phdr->p_paddr);
		phdr->p_vaddr  = elf32_to_cpu(ehdr, buf_phdr->p_vaddr);
		phdr->p_filesz = elf32_to_cpu(ehdr, buf_phdr->p_filesz);
		phdr->p_memsz  = elf32_to_cpu(ehdr, buf_phdr->p_memsz);
		phdr->p_align  = elf32_to_cpu(ehdr, buf_phdr->p_align);
		अवरोध;

	शेष:
		pr_debug("Unknown ELF class.\n");
		वापस -EINVAL;
	पूर्ण

	वापस elf_is_phdr_sane(phdr, len) ? 0 : -ENOEXEC;
पूर्ण

/**
 * elf_पढ़ो_phdrs - पढ़ो the program headers from the buffer
 *
 * This function assumes that the program header table was checked क्रम sanity.
 * Use elf_is_ehdr_sane() अगर it wasn't.
 */
अटल पूर्णांक elf_पढ़ो_phdrs(स्थिर अक्षर *buf, माप_प्रकार len,
			  काष्ठा kexec_elf_info *elf_info)
अणु
	माप_प्रकार phdr_size, i;
	स्थिर काष्ठा elfhdr *ehdr = elf_info->ehdr;

	/*
	 * e_phnum is at most 65535 so calculating the size of the
	 * program header cannot overflow.
	 */
	phdr_size = माप(काष्ठा elf_phdr) * ehdr->e_phnum;

	elf_info->proghdrs = kzalloc(phdr_size, GFP_KERNEL);
	अगर (!elf_info->proghdrs)
		वापस -ENOMEM;

	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		पूर्णांक ret;

		ret = elf_पढ़ो_phdr(buf, len, elf_info, i);
		अगर (ret) अणु
			kमुक्त(elf_info->proghdrs);
			elf_info->proghdrs = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * elf_पढ़ो_from_buffer - पढ़ो ELF file and sets up ELF header and ELF info
 * @buf:	Buffer to पढ़ो ELF file from.
 * @len:	Size of @buf.
 * @ehdr:	Poपूर्णांकer to existing काष्ठा which will be populated.
 * @elf_info:	Poपूर्णांकer to existing काष्ठा which will be populated.
 *
 * This function allows पढ़ोing ELF files with dअगरferent byte order than
 * the kernel, byte-swapping the fields as needed.
 *
 * Return:
 * On success वापसs 0, and the caller should call
 * kexec_मुक्त_elf_info(elf_info) to मुक्त the memory allocated क्रम the section
 * and program headers.
 */
अटल पूर्णांक elf_पढ़ो_from_buffer(स्थिर अक्षर *buf, माप_प्रकार len,
				काष्ठा elfhdr *ehdr,
				काष्ठा kexec_elf_info *elf_info)
अणु
	पूर्णांक ret;

	ret = elf_पढ़ो_ehdr(buf, len, ehdr);
	अगर (ret)
		वापस ret;

	elf_info->buffer = buf;
	elf_info->ehdr = ehdr;
	अगर (ehdr->e_phoff > 0 && ehdr->e_phnum > 0) अणु
		ret = elf_पढ़ो_phdrs(buf, len, elf_info);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * kexec_मुक्त_elf_info - मुक्त memory allocated by elf_पढ़ो_from_buffer
 */
व्योम kexec_मुक्त_elf_info(काष्ठा kexec_elf_info *elf_info)
अणु
	kमुक्त(elf_info->proghdrs);
	स_रखो(elf_info, 0, माप(*elf_info));
पूर्ण
/**
 * kexec_build_elf_info - पढ़ो ELF executable and check that we can use it
 */
पूर्णांक kexec_build_elf_info(स्थिर अक्षर *buf, माप_प्रकार len, काष्ठा elfhdr *ehdr,
			       काष्ठा kexec_elf_info *elf_info)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	ret = elf_पढ़ो_from_buffer(buf, len, ehdr, elf_info);
	अगर (ret)
		वापस ret;

	/* Big endian vmlinux has type ET_DYN. */
	अगर (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN) अणु
		pr_err("Not an ELF executable.\n");
		जाओ error;
	पूर्ण अन्यथा अगर (!elf_info->proghdrs) अणु
		pr_err("No ELF program header.\n");
		जाओ error;
	पूर्ण

	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		/*
		 * Kexec करोes not support loading पूर्णांकerpreters.
		 * In addition this check keeps us from attempting
		 * to kexec ordinay executables.
		 */
		अगर (elf_info->proghdrs[i].p_type == PT_INTERP) अणु
			pr_err("Requires an ELF interpreter.\n");
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;
error:
	kexec_मुक्त_elf_info(elf_info);
	वापस -ENOEXEC;
पूर्ण


पूर्णांक kexec_elf_probe(स्थिर अक्षर *buf, अचिन्हित दीर्घ len)
अणु
	काष्ठा elfhdr ehdr;
	काष्ठा kexec_elf_info elf_info;
	पूर्णांक ret;

	ret = kexec_build_elf_info(buf, len, &ehdr, &elf_info);
	अगर (ret)
		वापस ret;

	kexec_मुक्त_elf_info(&elf_info);

	वापस elf_check_arch(&ehdr) ? 0 : -ENOEXEC;
पूर्ण

/**
 * kexec_elf_load - load ELF executable image
 * @lowest_load_addr:	On वापस, will be the address where the first PT_LOAD
 *			section will be loaded in memory.
 *
 * Return:
 * 0 on success, negative value on failure.
 */
पूर्णांक kexec_elf_load(काष्ठा kimage *image, काष्ठा elfhdr *ehdr,
			 काष्ठा kexec_elf_info *elf_info,
			 काष्ठा kexec_buf *kbuf,
			 अचिन्हित दीर्घ *lowest_load_addr)
अणु
	अचिन्हित दीर्घ lowest_addr = अच_पूर्णांक_उच्च;
	पूर्णांक ret;
	माप_प्रकार i;

	/* Read in the PT_LOAD segments. */
	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		अचिन्हित दीर्घ load_addr;
		माप_प्रकार size;
		स्थिर काष्ठा elf_phdr *phdr;

		phdr = &elf_info->proghdrs[i];
		अगर (phdr->p_type != PT_LOAD)
			जारी;

		size = phdr->p_filesz;
		अगर (size > phdr->p_memsz)
			size = phdr->p_memsz;

		kbuf->buffer = (व्योम *) elf_info->buffer + phdr->p_offset;
		kbuf->bufsz = size;
		kbuf->memsz = phdr->p_memsz;
		kbuf->buf_align = phdr->p_align;
		kbuf->buf_min = phdr->p_paddr;
		kbuf->mem = KEXEC_BUF_MEM_UNKNOWN;
		ret = kexec_add_buffer(kbuf);
		अगर (ret)
			जाओ out;
		load_addr = kbuf->mem;

		अगर (load_addr < lowest_addr)
			lowest_addr = load_addr;
	पूर्ण

	*lowest_load_addr = lowest_addr;
	ret = 0;
 out:
	वापस ret;
पूर्ण
