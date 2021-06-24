<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ELF loader क्रम kexec_file_load प्रणाली call.
 *
 * Copyright IBM Corp. 2018
 *
 * Author(s): Philipp Ruकरो <pruकरो@linux.vnet.ibm.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/setup.h>

अटल पूर्णांक kexec_file_add_kernel_elf(काष्ठा kimage *image,
				     काष्ठा s390_load_data *data)
अणु
	काष्ठा kexec_buf buf;
	स्थिर Elf_Ehdr *ehdr;
	स्थिर Elf_Phdr *phdr;
	Elf_Addr entry;
	व्योम *kernel;
	पूर्णांक i, ret;

	kernel = image->kernel_buf;
	ehdr = (Elf_Ehdr *)kernel;
	buf.image = image;
	अगर (image->type == KEXEC_TYPE_CRASH)
		entry = STARTUP_KDUMP_OFFSET;
	अन्यथा
		entry = ehdr->e_entry;

	phdr = (व्योम *)ehdr + ehdr->e_phoff;
	क्रम (i = 0; i < ehdr->e_phnum; i++, phdr++) अणु
		अगर (phdr->p_type != PT_LOAD)
			जारी;

		buf.buffer = kernel + phdr->p_offset;
		buf.bufsz = phdr->p_filesz;

		buf.mem = ALIGN(phdr->p_paddr, phdr->p_align);
		अगर (image->type == KEXEC_TYPE_CRASH)
			buf.mem += crashk_res.start;
		buf.memsz = phdr->p_memsz;
		data->memsz = ALIGN(data->memsz, phdr->p_align) + buf.memsz;

		अगर (entry - phdr->p_paddr < phdr->p_memsz) अणु
			data->kernel_buf = buf.buffer;
			data->kernel_mem = buf.mem;
			data->parm = buf.buffer + PARMAREA;
		पूर्ण

		ipl_report_add_component(data->report, &buf,
					 IPL_RB_COMPONENT_FLAG_SIGNED |
					 IPL_RB_COMPONENT_FLAG_VERIFIED,
					 IPL_RB_CERT_UNKNOWN);
		ret = kexec_add_buffer(&buf);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस data->memsz ? 0 : -EINVAL;
पूर्ण

अटल व्योम *s390_elf_load(काष्ठा kimage *image,
			   अक्षर *kernel, अचिन्हित दीर्घ kernel_len,
			   अक्षर *initrd, अचिन्हित दीर्घ initrd_len,
			   अक्षर *cmdline, अचिन्हित दीर्घ cmdline_len)
अणु
	स्थिर Elf_Ehdr *ehdr;
	स्थिर Elf_Phdr *phdr;
	माप_प्रकार size;
	पूर्णांक i;

	/* image->fobs->probe alपढ़ोy checked क्रम valid ELF magic number. */
	ehdr = (Elf_Ehdr *)kernel;

	अगर (ehdr->e_type != ET_EXEC ||
	    ehdr->e_ident[EI_CLASS] != ELFCLASS64 ||
	    !elf_check_arch(ehdr))
		वापस ERR_PTR(-EINVAL);

	अगर (!ehdr->e_phnum || ehdr->e_phentsize != माप(Elf_Phdr))
		वापस ERR_PTR(-EINVAL);

	size = ehdr->e_ehsize + ehdr->e_phoff;
	size += ehdr->e_phentsize * ehdr->e_phnum;
	अगर (size > kernel_len)
		वापस ERR_PTR(-EINVAL);

	phdr = (व्योम *)ehdr + ehdr->e_phoff;
	size = ALIGN(size, phdr->p_align);
	क्रम (i = 0; i < ehdr->e_phnum; i++, phdr++) अणु
		अगर (phdr->p_type == PT_INTERP)
			वापस ERR_PTR(-EINVAL);

		अगर (phdr->p_offset > kernel_len)
			वापस ERR_PTR(-EINVAL);

		size += ALIGN(phdr->p_filesz, phdr->p_align);
	पूर्ण

	अगर (size > kernel_len)
		वापस ERR_PTR(-EINVAL);

	वापस kexec_file_add_components(image, kexec_file_add_kernel_elf);
पूर्ण

अटल पूर्णांक s390_elf_probe(स्थिर अक्षर *buf, अचिन्हित दीर्घ len)
अणु
	स्थिर Elf_Ehdr *ehdr;

	अगर (len < माप(Elf_Ehdr))
		वापस -ENOEXEC;

	ehdr = (Elf_Ehdr *)buf;

	/* Only check the ELF magic number here and करो proper validity check
	 * in the loader. Any check here that fails would send the erroneous
	 * ELF file to the image loader that करोes not care what it माला_लो.
	 * (Most likely) causing behavior not पूर्णांकended by the user.
	 */
	अगर (स_भेद(ehdr->e_ident, ELFMAG, SELFMAG) != 0)
		वापस -ENOEXEC;

	वापस 0;
पूर्ण

स्थिर काष्ठा kexec_file_ops s390_kexec_elf_ops = अणु
	.probe = s390_elf_probe,
	.load = s390_elf_load,
#अगर_घोषित CONFIG_KEXEC_SIG
	.verअगरy_sig = s390_verअगरy_sig,
#पूर्ण_अगर /* CONFIG_KEXEC_SIG */
पूर्ण;
