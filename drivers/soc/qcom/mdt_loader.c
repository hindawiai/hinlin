<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm Peripheral Image Loader
 *
 * Copyright (C) 2016 Linaro Ltd
 * Copyright (C) 2015 Sony Mobile Communications Inc
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/elf.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/mdt_loader.h>

अटल bool mdt_phdr_valid(स्थिर काष्ठा elf32_phdr *phdr)
अणु
	अगर (phdr->p_type != PT_LOAD)
		वापस false;

	अगर ((phdr->p_flags & QCOM_MDT_TYPE_MASK) == QCOM_MDT_TYPE_HASH)
		वापस false;

	अगर (!phdr->p_memsz)
		वापस false;

	वापस true;
पूर्ण

/**
 * qcom_mdt_get_size() - acquire size of the memory region needed to load mdt
 * @fw:		firmware object क्रम the mdt file
 *
 * Returns size of the loaded firmware blob, or -EINVAL on failure.
 */
sमाप_प्रकार qcom_mdt_get_size(स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा elf32_phdr *phdrs;
	स्थिर काष्ठा elf32_phdr *phdr;
	स्थिर काष्ठा elf32_hdr *ehdr;
	phys_addr_t min_addr = PHYS_ADDR_MAX;
	phys_addr_t max_addr = 0;
	पूर्णांक i;

	ehdr = (काष्ठा elf32_hdr *)fw->data;
	phdrs = (काष्ठा elf32_phdr *)(ehdr + 1);

	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		phdr = &phdrs[i];

		अगर (!mdt_phdr_valid(phdr))
			जारी;

		अगर (phdr->p_paddr < min_addr)
			min_addr = phdr->p_paddr;

		अगर (phdr->p_paddr + phdr->p_memsz > max_addr)
			max_addr = ALIGN(phdr->p_paddr + phdr->p_memsz, SZ_4K);
	पूर्ण

	वापस min_addr < max_addr ? max_addr - min_addr : -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_mdt_get_size);

/**
 * qcom_mdt_पढ़ो_metadata() - पढ़ो header and metadata from mdt or mbn
 * @fw:		firmware of mdt header or mbn
 * @data_len:	length of the पढ़ो metadata blob
 *
 * The mechanism that perक्रमms the authentication of the loading firmware
 * expects an ELF header directly followed by the segment of hashes, with no
 * padding inbetween. This function allocates a chunk of memory क्रम this pair
 * and copy the two pieces पूर्णांकo the buffer.
 *
 * In the हाल of split firmware the hash is found directly following the ELF
 * header, rather than at p_offset described by the second program header.
 *
 * The caller is responsible to मुक्त (kमुक्त()) the वापसed poपूर्णांकer.
 *
 * Return: poपूर्णांकer to data, or ERR_PTR()
 */
व्योम *qcom_mdt_पढ़ो_metadata(स्थिर काष्ठा firmware *fw, माप_प्रकार *data_len)
अणु
	स्थिर काष्ठा elf32_phdr *phdrs;
	स्थिर काष्ठा elf32_hdr *ehdr;
	माप_प्रकार hash_offset;
	माप_प्रकार hash_size;
	माप_प्रकार ehdr_size;
	व्योम *data;

	ehdr = (काष्ठा elf32_hdr *)fw->data;
	phdrs = (काष्ठा elf32_phdr *)(ehdr + 1);

	अगर (ehdr->e_phnum < 2)
		वापस ERR_PTR(-EINVAL);

	अगर (phdrs[0].p_type == PT_LOAD || phdrs[1].p_type == PT_LOAD)
		वापस ERR_PTR(-EINVAL);

	अगर ((phdrs[1].p_flags & QCOM_MDT_TYPE_MASK) != QCOM_MDT_TYPE_HASH)
		वापस ERR_PTR(-EINVAL);

	ehdr_size = phdrs[0].p_filesz;
	hash_size = phdrs[1].p_filesz;

	data = kदो_स्मृति(ehdr_size + hash_size, GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	/* Is the header and hash alपढ़ोy packed */
	अगर (ehdr_size + hash_size == fw->size)
		hash_offset = phdrs[0].p_filesz;
	अन्यथा
		hash_offset = phdrs[1].p_offset;

	स_नकल(data, fw->data, ehdr_size);
	स_नकल(data + ehdr_size, fw->data + hash_offset, hash_size);

	*data_len = ehdr_size + hash_size;

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_mdt_पढ़ो_metadata);

अटल पूर्णांक __qcom_mdt_load(काष्ठा device *dev, स्थिर काष्ठा firmware *fw,
			   स्थिर अक्षर *firmware, पूर्णांक pas_id, व्योम *mem_region,
			   phys_addr_t mem_phys, माप_प्रकार mem_size,
			   phys_addr_t *reloc_base, bool pas_init)
अणु
	स्थिर काष्ठा elf32_phdr *phdrs;
	स्थिर काष्ठा elf32_phdr *phdr;
	स्थिर काष्ठा elf32_hdr *ehdr;
	स्थिर काष्ठा firmware *seg_fw;
	phys_addr_t mem_reloc;
	phys_addr_t min_addr = PHYS_ADDR_MAX;
	phys_addr_t max_addr = 0;
	माप_प्रकार metadata_len;
	माप_प्रकार fw_name_len;
	sमाप_प्रकार offset;
	व्योम *metadata;
	अक्षर *fw_name;
	bool relocate = false;
	व्योम *ptr;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!fw || !mem_region || !mem_phys || !mem_size)
		वापस -EINVAL;

	ehdr = (काष्ठा elf32_hdr *)fw->data;
	phdrs = (काष्ठा elf32_phdr *)(ehdr + 1);

	fw_name_len = म_माप(firmware);
	अगर (fw_name_len <= 4)
		वापस -EINVAL;

	fw_name = kstrdup(firmware, GFP_KERNEL);
	अगर (!fw_name)
		वापस -ENOMEM;

	अगर (pas_init) अणु
		metadata = qcom_mdt_पढ़ो_metadata(fw, &metadata_len);
		अगर (IS_ERR(metadata)) अणु
			ret = PTR_ERR(metadata);
			जाओ out;
		पूर्ण

		ret = qcom_scm_pas_init_image(pas_id, metadata, metadata_len);

		kमुक्त(metadata);
		अगर (ret) अणु
			dev_err(dev, "invalid firmware metadata\n");
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		phdr = &phdrs[i];

		अगर (!mdt_phdr_valid(phdr))
			जारी;

		अगर (phdr->p_flags & QCOM_MDT_RELOCATABLE)
			relocate = true;

		अगर (phdr->p_paddr < min_addr)
			min_addr = phdr->p_paddr;

		अगर (phdr->p_paddr + phdr->p_memsz > max_addr)
			max_addr = ALIGN(phdr->p_paddr + phdr->p_memsz, SZ_4K);
	पूर्ण

	अगर (relocate) अणु
		अगर (pas_init) अणु
			ret = qcom_scm_pas_mem_setup(pas_id, mem_phys,
						     max_addr - min_addr);
			अगर (ret) अणु
				dev_err(dev, "unable to setup relocation\n");
				जाओ out;
			पूर्ण
		पूर्ण

		/*
		 * The image is relocatable, so offset each segment based on
		 * the lowest segment address.
		 */
		mem_reloc = min_addr;
	पूर्ण अन्यथा अणु
		/*
		 * Image is not relocatable, so offset each segment based on
		 * the allocated physical chunk of memory.
		 */
		mem_reloc = mem_phys;
	पूर्ण

	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		phdr = &phdrs[i];

		अगर (!mdt_phdr_valid(phdr))
			जारी;

		offset = phdr->p_paddr - mem_reloc;
		अगर (offset < 0 || offset + phdr->p_memsz > mem_size) अणु
			dev_err(dev, "segment outside memory range\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (phdr->p_filesz > phdr->p_memsz) अणु
			dev_err(dev,
				"refusing to load segment %d with p_filesz > p_memsz\n",
				i);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ptr = mem_region + offset;

		अगर (phdr->p_filesz && phdr->p_offset < fw->size) अणु
			/* Firmware is large enough to be non-split */
			अगर (phdr->p_offset + phdr->p_filesz > fw->size) अणु
				dev_err(dev,
					"failed to load segment %d from truncated file %s\n",
					i, firmware);
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			स_नकल(ptr, fw->data + phdr->p_offset, phdr->p_filesz);
		पूर्ण अन्यथा अगर (phdr->p_filesz) अणु
			/* Firmware not large enough, load split-out segments */
			प्र_लिखो(fw_name + fw_name_len - 3, "b%02d", i);
			ret = request_firmware_पूर्णांकo_buf(&seg_fw, fw_name, dev,
							ptr, phdr->p_filesz);
			अगर (ret) अणु
				dev_err(dev, "failed to load %s\n", fw_name);
				अवरोध;
			पूर्ण

			अगर (seg_fw->size != phdr->p_filesz) अणु
				dev_err(dev,
					"failed to load segment %d from truncated file %s\n",
					i, fw_name);
				release_firmware(seg_fw);
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			release_firmware(seg_fw);
		पूर्ण

		अगर (phdr->p_memsz > phdr->p_filesz)
			स_रखो(ptr + phdr->p_filesz, 0, phdr->p_memsz - phdr->p_filesz);
	पूर्ण

	अगर (reloc_base)
		*reloc_base = mem_reloc;

out:
	kमुक्त(fw_name);

	वापस ret;
पूर्ण

/**
 * qcom_mdt_load() - load the firmware which header is loaded as fw
 * @dev:	device handle to associate resources with
 * @fw:		firmware object क्रम the mdt file
 * @firmware:	name of the firmware, क्रम स्थिरruction of segment file names
 * @pas_id:	PAS identअगरier
 * @mem_region:	allocated memory region to load firmware पूर्णांकo
 * @mem_phys:	physical address of allocated memory region
 * @mem_size:	size of the allocated memory region
 * @reloc_base:	adjusted physical address after relocation
 *
 * Returns 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक qcom_mdt_load(काष्ठा device *dev, स्थिर काष्ठा firmware *fw,
		  स्थिर अक्षर *firmware, पूर्णांक pas_id, व्योम *mem_region,
		  phys_addr_t mem_phys, माप_प्रकार mem_size,
		  phys_addr_t *reloc_base)
अणु
	वापस __qcom_mdt_load(dev, fw, firmware, pas_id, mem_region, mem_phys,
			       mem_size, reloc_base, true);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_mdt_load);

/**
 * qcom_mdt_load_no_init() - load the firmware which header is loaded as fw
 * @dev:	device handle to associate resources with
 * @fw:		firmware object क्रम the mdt file
 * @firmware:	name of the firmware, क्रम स्थिरruction of segment file names
 * @pas_id:	PAS identअगरier
 * @mem_region:	allocated memory region to load firmware पूर्णांकo
 * @mem_phys:	physical address of allocated memory region
 * @mem_size:	size of the allocated memory region
 * @reloc_base:	adjusted physical address after relocation
 *
 * Returns 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक qcom_mdt_load_no_init(काष्ठा device *dev, स्थिर काष्ठा firmware *fw,
			  स्थिर अक्षर *firmware, पूर्णांक pas_id,
			  व्योम *mem_region, phys_addr_t mem_phys,
			  माप_प्रकार mem_size, phys_addr_t *reloc_base)
अणु
	वापस __qcom_mdt_load(dev, fw, firmware, pas_id, mem_region, mem_phys,
			       mem_size, reloc_base, false);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_mdt_load_no_init);

MODULE_DESCRIPTION("Firmware parser for Qualcomm MDT format");
MODULE_LICENSE("GPL v2");
