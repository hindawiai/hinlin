<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Remote Processor Framework Elf loader
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 * Mark Grosen <mgrosen@ti.com>
 * Fernanकरो Guzman Lugo <fernanकरो.lugo@ti.com>
 * Suman Anna <s-anna@ti.com>
 * Robert Tivy <rtivy@ti.com>
 * Armanकरो Uribe De Leon <x0095078@ti.com>
 * Sjur Brथइndeland <sjur.bअक्रमeland@stericsson.com>
 */

#घोषणा pr_fmt(fmt)    "%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/elf.h>

#समावेश "remoteproc_internal.h"
#समावेश "remoteproc_elf_helpers.h"

/**
 * rproc_elf_sanity_check() - Sanity Check क्रम ELF32/ELF64 firmware image
 * @rproc: the remote processor handle
 * @fw: the ELF firmware image
 *
 * Make sure this fw image is sane (ie a correct ELF32/ELF64 file).
 */
पूर्णांक rproc_elf_sanity_check(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	स्थिर अक्षर *name = rproc->firmware;
	काष्ठा device *dev = &rproc->dev;
	/*
	 * Elf files are beginning with the same काष्ठाure. Thus, to simplअगरy
	 * header parsing, we can use the elf32_hdr one क्रम both elf64 and
	 * elf32.
	 */
	काष्ठा elf32_hdr *ehdr;
	u32 elf_shdr_get_size;
	u64 phoff, shoff;
	अक्षर class;
	u16 phnum;

	अगर (!fw) अणु
		dev_err(dev, "failed to load %s\n", name);
		वापस -EINVAL;
	पूर्ण

	अगर (fw->size < माप(काष्ठा elf32_hdr)) अणु
		dev_err(dev, "Image is too small\n");
		वापस -EINVAL;
	पूर्ण

	ehdr = (काष्ठा elf32_hdr *)fw->data;

	अगर (स_भेद(ehdr->e_ident, ELFMAG, SELFMAG)) अणु
		dev_err(dev, "Image is corrupted (bad magic)\n");
		वापस -EINVAL;
	पूर्ण

	class = ehdr->e_ident[EI_CLASS];
	अगर (class != ELFCLASS32 && class != ELFCLASS64) अणु
		dev_err(dev, "Unsupported class: %d\n", class);
		वापस -EINVAL;
	पूर्ण

	अगर (class == ELFCLASS64 && fw->size < माप(काष्ठा elf64_hdr)) अणु
		dev_err(dev, "elf64 header is too small\n");
		वापस -EINVAL;
	पूर्ण

	/* We assume the firmware has the same endianness as the host */
# अगरdef __LITTLE_ENDIAN
	अगर (ehdr->e_ident[EI_DATA] != ELFDATA2LSB) अणु
# अन्यथा /* BIG ENDIAN */
	अगर (ehdr->e_ident[EI_DATA] != ELFDATA2MSB) अणु
# endअगर
		dev_err(dev, "Unsupported firmware endianness\n");
		वापस -EINVAL;
	पूर्ण

	phoff = elf_hdr_get_e_phoff(class, fw->data);
	shoff = elf_hdr_get_e_shoff(class, fw->data);
	phnum =  elf_hdr_get_e_phnum(class, fw->data);
	elf_shdr_get_size = elf_size_of_shdr(class);

	अगर (fw->size < shoff + elf_shdr_get_size) अणु
		dev_err(dev, "Image is too small\n");
		वापस -EINVAL;
	पूर्ण

	अगर (phnum == 0) अणु
		dev_err(dev, "No loadable segments\n");
		वापस -EINVAL;
	पूर्ण

	अगर (phoff > fw->size) अणु
		dev_err(dev, "Firmware size is too small\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "Firmware is an elf%d file\n",
		class == ELFCLASS32 ? 32 : 64);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rproc_elf_sanity_check);

/**
 * rproc_elf_get_boot_addr() - Get rproc's boot address.
 * @rproc: the remote processor handle
 * @fw: the ELF firmware image
 *
 * This function वापसs the entry poपूर्णांक address of the ELF
 * image.
 *
 * Note that the boot address is not a configurable property of all remote
 * processors. Some will always boot at a specअगरic hard-coded address.
 */
u64 rproc_elf_get_boot_addr(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	वापस elf_hdr_get_e_entry(fw_elf_get_class(fw), fw->data);
पूर्ण
EXPORT_SYMBOL(rproc_elf_get_boot_addr);

/**
 * rproc_elf_load_segments() - load firmware segments to memory
 * @rproc: remote processor which will be booted using these fw segments
 * @fw: the ELF firmware image
 *
 * This function loads the firmware segments to memory, where the remote
 * processor expects them.
 *
 * Some remote processors will expect their code and data to be placed
 * in specअगरic device addresses, and can't have them dynamically asचिन्हित.
 *
 * We currently support only those kind of remote processors, and expect
 * the program header's paddr member to contain those addresses. We then go
 * through the physically contiguous "carveout" memory regions which we
 * allocated (and mapped) earlier on behalf of the remote processor,
 * and "translate" device address to kernel addresses, so we can copy the
 * segments where they are expected.
 *
 * Currently we only support remote processors that required carveout
 * allocations and got them mapped onto their iommus. Some processors
 * might be dअगरferent: they might not have iommus, and would prefer to
 * directly allocate memory क्रम every segment/resource. This is not yet
 * supported, though.
 */
पूर्णांक rproc_elf_load_segments(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &rproc->dev;
	स्थिर व्योम *ehdr, *phdr;
	पूर्णांक i, ret = 0;
	u16 phnum;
	स्थिर u8 *elf_data = fw->data;
	u8 class = fw_elf_get_class(fw);
	u32 elf_phdr_get_size = elf_size_of_phdr(class);

	ehdr = elf_data;
	phnum = elf_hdr_get_e_phnum(class, ehdr);
	phdr = elf_data + elf_hdr_get_e_phoff(class, ehdr);

	/* go through the available ELF segments */
	क्रम (i = 0; i < phnum; i++, phdr += elf_phdr_get_size) अणु
		u64 da = elf_phdr_get_p_paddr(class, phdr);
		u64 memsz = elf_phdr_get_p_memsz(class, phdr);
		u64 filesz = elf_phdr_get_p_filesz(class, phdr);
		u64 offset = elf_phdr_get_p_offset(class, phdr);
		u32 type = elf_phdr_get_p_type(class, phdr);
		व्योम *ptr;
		bool is_iomem;

		अगर (type != PT_LOAD)
			जारी;

		dev_dbg(dev, "phdr: type %d da 0x%llx memsz 0x%llx filesz 0x%llx\n",
			type, da, memsz, filesz);

		अगर (filesz > memsz) अणु
			dev_err(dev, "bad phdr filesz 0x%llx memsz 0x%llx\n",
				filesz, memsz);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (offset + filesz > fw->size) अणु
			dev_err(dev, "truncated fw: need 0x%llx avail 0x%zx\n",
				offset + filesz, fw->size);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (!rproc_u64_fit_in_माप_प्रकार(memsz)) अणु
			dev_err(dev, "size (%llx) does not fit in size_t type\n",
				memsz);
			ret = -EOVERFLOW;
			अवरोध;
		पूर्ण

		/* grab the kernel address क्रम this device address */
		ptr = rproc_da_to_va(rproc, da, memsz, &is_iomem);
		अगर (!ptr) अणु
			dev_err(dev, "bad phdr da 0x%llx mem 0x%llx\n", da,
				memsz);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* put the segment where the remote processor expects it */
		अगर (filesz) अणु
			अगर (is_iomem)
				स_नकल_fromio(ptr, (व्योम __iomem *)(elf_data + offset), filesz);
			अन्यथा
				स_नकल(ptr, elf_data + offset, filesz);
		पूर्ण

		/*
		 * Zero out reमुख्यing memory क्रम this segment.
		 *
		 * This isn't strictly required since dma_alloc_coherent alपढ़ोy
		 * did this क्रम us. albeit harmless, we may consider removing
		 * this.
		 */
		अगर (memsz > filesz) अणु
			अगर (is_iomem)
				स_रखो_io((व्योम __iomem *)(ptr + filesz), 0, memsz - filesz);
			अन्यथा
				स_रखो(ptr + filesz, 0, memsz - filesz);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(rproc_elf_load_segments);

अटल स्थिर व्योम *
find_table(काष्ठा device *dev, स्थिर काष्ठा firmware *fw)
अणु
	स्थिर व्योम *shdr, *name_table_shdr;
	पूर्णांक i;
	स्थिर अक्षर *name_table;
	काष्ठा resource_table *table = शून्य;
	स्थिर u8 *elf_data = (व्योम *)fw->data;
	u8 class = fw_elf_get_class(fw);
	माप_प्रकार fw_size = fw->size;
	स्थिर व्योम *ehdr = elf_data;
	u16 shnum = elf_hdr_get_e_shnum(class, ehdr);
	u32 elf_shdr_get_size = elf_size_of_shdr(class);
	u16 shstrndx = elf_hdr_get_e_shstrndx(class, ehdr);

	/* look क्रम the resource table and handle it */
	/* First, get the section header according to the elf class */
	shdr = elf_data + elf_hdr_get_e_shoff(class, ehdr);
	/* Compute name table section header entry in shdr array */
	name_table_shdr = shdr + (shstrndx * elf_shdr_get_size);
	/* Finally, compute the name table section address in elf */
	name_table = elf_data + elf_shdr_get_sh_offset(class, name_table_shdr);

	क्रम (i = 0; i < shnum; i++, shdr += elf_shdr_get_size) अणु
		u64 size = elf_shdr_get_sh_size(class, shdr);
		u64 offset = elf_shdr_get_sh_offset(class, shdr);
		u32 name = elf_shdr_get_sh_name(class, shdr);

		अगर (म_भेद(name_table + name, ".resource_table"))
			जारी;

		table = (काष्ठा resource_table *)(elf_data + offset);

		/* make sure we have the entire table */
		अगर (offset + size > fw_size || offset + size < size) अणु
			dev_err(dev, "resource table truncated\n");
			वापस शून्य;
		पूर्ण

		/* make sure table has at least the header */
		अगर (माप(काष्ठा resource_table) > size) अणु
			dev_err(dev, "header-less resource table\n");
			वापस शून्य;
		पूर्ण

		/* we करोn't support any version beyond the first */
		अगर (table->ver != 1) अणु
			dev_err(dev, "unsupported fw ver: %d\n", table->ver);
			वापस शून्य;
		पूर्ण

		/* make sure reserved bytes are zeroes */
		अगर (table->reserved[0] || table->reserved[1]) अणु
			dev_err(dev, "non zero reserved bytes\n");
			वापस शून्य;
		पूर्ण

		/* make sure the offsets array isn't truncated */
		अगर (काष्ठा_size(table, offset, table->num) > size) अणु
			dev_err(dev, "resource table incomplete\n");
			वापस शून्य;
		पूर्ण

		वापस shdr;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * rproc_elf_load_rsc_table() - load the resource table
 * @rproc: the rproc handle
 * @fw: the ELF firmware image
 *
 * This function finds the resource table inside the remote processor's
 * firmware, load it पूर्णांकo the @cached_table and update @table_ptr.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक rproc_elf_load_rsc_table(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	स्थिर व्योम *shdr;
	काष्ठा device *dev = &rproc->dev;
	काष्ठा resource_table *table = शून्य;
	स्थिर u8 *elf_data = fw->data;
	माप_प्रकार tablesz;
	u8 class = fw_elf_get_class(fw);
	u64 sh_offset;

	shdr = find_table(dev, fw);
	अगर (!shdr)
		वापस -EINVAL;

	sh_offset = elf_shdr_get_sh_offset(class, shdr);
	table = (काष्ठा resource_table *)(elf_data + sh_offset);
	tablesz = elf_shdr_get_sh_size(class, shdr);

	/*
	 * Create a copy of the resource table. When a virtio device starts
	 * and calls vring_new_virtqueue() the address of the allocated vring
	 * will be stored in the cached_table. Beक्रमe the device is started,
	 * cached_table will be copied पूर्णांकo device memory.
	 */
	rproc->cached_table = kmemdup(table, tablesz, GFP_KERNEL);
	अगर (!rproc->cached_table)
		वापस -ENOMEM;

	rproc->table_ptr = rproc->cached_table;
	rproc->table_sz = tablesz;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rproc_elf_load_rsc_table);

/**
 * rproc_elf_find_loaded_rsc_table() - find the loaded resource table
 * @rproc: the rproc handle
 * @fw: the ELF firmware image
 *
 * This function finds the location of the loaded resource table. Don't
 * call this function अगर the table wasn't loaded yet - it's a bug अगर you करो.
 *
 * Returns the poपूर्णांकer to the resource table अगर it is found or शून्य otherwise.
 * If the table wasn't loaded yet the result is unspecअगरied.
 */
काष्ठा resource_table *rproc_elf_find_loaded_rsc_table(काष्ठा rproc *rproc,
						       स्थिर काष्ठा firmware *fw)
अणु
	स्थिर व्योम *shdr;
	u64 sh_addr, sh_size;
	u8 class = fw_elf_get_class(fw);
	काष्ठा device *dev = &rproc->dev;

	shdr = find_table(&rproc->dev, fw);
	अगर (!shdr)
		वापस शून्य;

	sh_addr = elf_shdr_get_sh_addr(class, shdr);
	sh_size = elf_shdr_get_sh_size(class, shdr);

	अगर (!rproc_u64_fit_in_माप_प्रकार(sh_size)) अणु
		dev_err(dev, "size (%llx) does not fit in size_t type\n",
			sh_size);
		वापस शून्य;
	पूर्ण

	वापस rproc_da_to_va(rproc, sh_addr, sh_size, शून्य);
पूर्ण
EXPORT_SYMBOL(rproc_elf_find_loaded_rsc_table);
