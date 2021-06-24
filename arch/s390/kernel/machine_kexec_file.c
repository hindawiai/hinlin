<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * s390 code क्रम kexec_file_load प्रणाली call
 *
 * Copyright IBM Corp. 2018
 *
 * Author(s): Philipp Ruकरो <pruकरो@linux.vnet.ibm.com>
 */

#समावेश <linux/elf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kexec.h>
#समावेश <linux/module_signature.h>
#समावेश <linux/verअगरication.h>
#समावेश <यंत्र/boot_data.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/setup.h>

स्थिर काष्ठा kexec_file_ops * स्थिर kexec_file_loaders[] = अणु
	&s390_kexec_elf_ops,
	&s390_kexec_image_ops,
	शून्य,
पूर्ण;

#अगर_घोषित CONFIG_KEXEC_SIG
पूर्णांक s390_verअगरy_sig(स्थिर अक्षर *kernel, अचिन्हित दीर्घ kernel_len)
अणु
	स्थिर अचिन्हित दीर्घ marker_len = माप(MODULE_SIG_STRING) - 1;
	काष्ठा module_signature *ms;
	अचिन्हित दीर्घ sig_len;

	/* Skip signature verअगरication when not secure IPLed. */
	अगर (!ipl_secure_flag)
		वापस 0;

	अगर (marker_len > kernel_len)
		वापस -EKEYREJECTED;

	अगर (स_भेद(kernel + kernel_len - marker_len, MODULE_SIG_STRING,
		   marker_len))
		वापस -EKEYREJECTED;
	kernel_len -= marker_len;

	ms = (व्योम *)kernel + kernel_len - माप(*ms);
	kernel_len -= माप(*ms);

	sig_len = be32_to_cpu(ms->sig_len);
	अगर (sig_len >= kernel_len)
		वापस -EKEYREJECTED;
	kernel_len -= sig_len;

	अगर (ms->id_type != PKEY_ID_PKCS7)
		वापस -EKEYREJECTED;

	अगर (ms->algo != 0 ||
	    ms->hash != 0 ||
	    ms->signer_len != 0 ||
	    ms->key_id_len != 0 ||
	    ms->__pad[0] != 0 ||
	    ms->__pad[1] != 0 ||
	    ms->__pad[2] != 0) अणु
		वापस -EBADMSG;
	पूर्ण

	वापस verअगरy_pkcs7_signature(kernel, kernel_len,
				      kernel + kernel_len, sig_len,
				      VERIFY_USE_PLATFORM_KEYRING,
				      VERIFYING_MODULE_SIGNATURE,
				      शून्य, शून्य);
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_SIG */

अटल पूर्णांक kexec_file_update_purgatory(काष्ठा kimage *image,
				       काष्ठा s390_load_data *data)
अणु
	u64 entry, type;
	पूर्णांक ret;

	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		entry = STARTUP_KDUMP_OFFSET;
		type = KEXEC_TYPE_CRASH;
	पूर्ण अन्यथा अणु
		entry = STARTUP_NORMAL_OFFSET;
		type = KEXEC_TYPE_DEFAULT;
	पूर्ण

	ret = kexec_purgatory_get_set_symbol(image, "kernel_entry", &entry,
					     माप(entry), false);
	अगर (ret)
		वापस ret;

	ret = kexec_purgatory_get_set_symbol(image, "kernel_type", &type,
					     माप(type), false);
	अगर (ret)
		वापस ret;

	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		u64 crash_size;

		ret = kexec_purgatory_get_set_symbol(image, "crash_start",
						     &crashk_res.start,
						     माप(crashk_res.start),
						     false);
		अगर (ret)
			वापस ret;

		crash_size = crashk_res.end - crashk_res.start + 1;
		ret = kexec_purgatory_get_set_symbol(image, "crash_size",
						     &crash_size,
						     माप(crash_size),
						     false);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kexec_file_add_purgatory(काष्ठा kimage *image,
				    काष्ठा s390_load_data *data)
अणु
	काष्ठा kexec_buf buf;
	पूर्णांक ret;

	buf.image = image;

	data->memsz = ALIGN(data->memsz, PAGE_SIZE);
	buf.mem = data->memsz;
	अगर (image->type == KEXEC_TYPE_CRASH)
		buf.mem += crashk_res.start;

	ret = kexec_load_purgatory(image, &buf);
	अगर (ret)
		वापस ret;
	data->memsz += buf.memsz;

	वापस kexec_file_update_purgatory(image, data);
पूर्ण

अटल पूर्णांक kexec_file_add_initrd(काष्ठा kimage *image,
				 काष्ठा s390_load_data *data)
अणु
	काष्ठा kexec_buf buf;
	पूर्णांक ret;

	buf.image = image;

	buf.buffer = image->initrd_buf;
	buf.bufsz = image->initrd_buf_len;

	data->memsz = ALIGN(data->memsz, PAGE_SIZE);
	buf.mem = data->memsz;
	अगर (image->type == KEXEC_TYPE_CRASH)
		buf.mem += crashk_res.start;
	buf.memsz = buf.bufsz;

	data->parm->initrd_start = data->memsz;
	data->parm->initrd_size = buf.memsz;
	data->memsz += buf.memsz;

	ret = kexec_add_buffer(&buf);
	अगर (ret)
		वापस ret;

	वापस ipl_report_add_component(data->report, &buf, 0, 0);
पूर्ण

अटल पूर्णांक kexec_file_add_ipl_report(काष्ठा kimage *image,
				     काष्ठा s390_load_data *data)
अणु
	__u32 *lc_ipl_parmblock_ptr;
	अचिन्हित पूर्णांक len, ncerts;
	काष्ठा kexec_buf buf;
	अचिन्हित दीर्घ addr;
	व्योम *ptr, *end;

	buf.image = image;

	data->memsz = ALIGN(data->memsz, PAGE_SIZE);
	buf.mem = data->memsz;
	अगर (image->type == KEXEC_TYPE_CRASH)
		buf.mem += crashk_res.start;

	ptr = (व्योम *)ipl_cert_list_addr;
	end = ptr + ipl_cert_list_size;
	ncerts = 0;
	जबतक (ptr < end) अणु
		ncerts++;
		len = *(अचिन्हित पूर्णांक *)ptr;
		ptr += माप(len);
		ptr += len;
	पूर्ण

	addr = data->memsz + data->report->size;
	addr += ncerts * माप(काष्ठा ipl_rb_certअगरicate_entry);
	ptr = (व्योम *)ipl_cert_list_addr;
	जबतक (ptr < end) अणु
		len = *(अचिन्हित पूर्णांक *)ptr;
		ptr += माप(len);
		ipl_report_add_certअगरicate(data->report, ptr, addr, len);
		addr += len;
		ptr += len;
	पूर्ण

	buf.buffer = ipl_report_finish(data->report);
	buf.bufsz = data->report->size;
	buf.memsz = buf.bufsz;

	data->memsz += buf.memsz;

	lc_ipl_parmblock_ptr =
		data->kernel_buf + दुरत्व(काष्ठा lowcore, ipl_parmblock_ptr);
	*lc_ipl_parmblock_ptr = (__u32)buf.mem;

	वापस kexec_add_buffer(&buf);
पूर्ण

व्योम *kexec_file_add_components(काष्ठा kimage *image,
				पूर्णांक (*add_kernel)(काष्ठा kimage *image,
						  काष्ठा s390_load_data *data))
अणु
	काष्ठा s390_load_data data = अणु0पूर्ण;
	पूर्णांक ret;

	data.report = ipl_report_init(&ipl_block);
	अगर (IS_ERR(data.report))
		वापस data.report;

	ret = add_kernel(image, &data);
	अगर (ret)
		जाओ out;

	अगर (image->cmdline_buf_len >= ARCH_COMMAND_LINE_SIZE) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	स_नकल(data.parm->command_line, image->cmdline_buf,
	       image->cmdline_buf_len);

	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		data.parm->oldmem_base = crashk_res.start;
		data.parm->oldmem_size = crashk_res.end - crashk_res.start + 1;
	पूर्ण

	अगर (image->initrd_buf) अणु
		ret = kexec_file_add_initrd(image, &data);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = kexec_file_add_purgatory(image, &data);
	अगर (ret)
		जाओ out;

	अगर (data.kernel_mem == 0) अणु
		अचिन्हित दीर्घ restart_psw =  0x0008000080000000UL;
		restart_psw += image->start;
		स_नकल(data.kernel_buf, &restart_psw, माप(restart_psw));
		image->start = 0;
	पूर्ण

	ret = kexec_file_add_ipl_report(image, &data);
out:
	ipl_report_मुक्त(data.report);
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक arch_kexec_apply_relocations_add(काष्ठा purgatory_info *pi,
				     Elf_Shdr *section,
				     स्थिर Elf_Shdr *rअन्यथाc,
				     स्थिर Elf_Shdr *symtab)
अणु
	Elf_Rela *relas;
	पूर्णांक i, r_type;

	relas = (व्योम *)pi->ehdr + rअन्यथाc->sh_offset;

	क्रम (i = 0; i < rअन्यथाc->sh_size / माप(*relas); i++) अणु
		स्थिर Elf_Sym *sym;	/* symbol to relocate */
		अचिन्हित दीर्घ addr;	/* final location after relocation */
		अचिन्हित दीर्घ val;	/* relocated symbol value */
		व्योम *loc;		/* पंचांगp location to modअगरy */

		sym = (व्योम *)pi->ehdr + symtab->sh_offset;
		sym += ELF64_R_SYM(relas[i].r_info);

		अगर (sym->st_shndx == SHN_UNDEF)
			वापस -ENOEXEC;

		अगर (sym->st_shndx == SHN_COMMON)
			वापस -ENOEXEC;

		अगर (sym->st_shndx >= pi->ehdr->e_shnum &&
		    sym->st_shndx != SHN_ABS)
			वापस -ENOEXEC;

		loc = pi->purgatory_buf;
		loc += section->sh_offset;
		loc += relas[i].r_offset;

		val = sym->st_value;
		अगर (sym->st_shndx != SHN_ABS)
			val += pi->sechdrs[sym->st_shndx].sh_addr;
		val += relas[i].r_addend;

		addr = section->sh_addr + relas[i].r_offset;

		r_type = ELF64_R_TYPE(relas[i].r_info);
		arch_kexec_करो_relocs(r_type, loc, val, addr);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक arch_kexec_kernel_image_probe(काष्ठा kimage *image, व्योम *buf,
				  अचिन्हित दीर्घ buf_len)
अणु
	/* A kernel must be at least large enough to contain head.S. During
	 * load memory in head.S will be accessed, e.g. to रेजिस्टर the next
	 * command line. If the next kernel were smaller the current kernel
	 * will panic at load.
	 */
	अगर (buf_len < HEAD_END)
		वापस -ENOEXEC;

	वापस kexec_image_probe_शेष(image, buf, buf_len);
पूर्ण
