<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Coredump functionality क्रम Remoteproc framework.
 *
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/completion.h>
#समावेश <linux/devcoredump.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/remoteproc.h>
#समावेश "remoteproc_internal.h"
#समावेश "remoteproc_elf_helpers.h"

काष्ठा rproc_coredump_state अणु
	काष्ठा rproc *rproc;
	व्योम *header;
	काष्ठा completion dump_करोne;
पूर्ण;

/**
 * rproc_coredump_cleanup() - clean up dump_segments list
 * @rproc: the remote processor handle
 */
व्योम rproc_coredump_cleanup(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_dump_segment *entry, *पंचांगp;

	list_क्रम_each_entry_safe(entry, पंचांगp, &rproc->dump_segments, node) अणु
		list_del(&entry->node);
		kमुक्त(entry);
	पूर्ण
पूर्ण

/**
 * rproc_coredump_add_segment() - add segment of device memory to coredump
 * @rproc:	handle of a remote processor
 * @da:		device address
 * @size:	size of segment
 *
 * Add device memory to the list of segments to be included in a coredump क्रम
 * the remoteproc.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक rproc_coredump_add_segment(काष्ठा rproc *rproc, dma_addr_t da, माप_प्रकार size)
अणु
	काष्ठा rproc_dump_segment *segment;

	segment = kzalloc(माप(*segment), GFP_KERNEL);
	अगर (!segment)
		वापस -ENOMEM;

	segment->da = da;
	segment->size = size;

	list_add_tail(&segment->node, &rproc->dump_segments);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rproc_coredump_add_segment);

/**
 * rproc_coredump_add_custom_segment() - add custom coredump segment
 * @rproc:	handle of a remote processor
 * @da:		device address
 * @size:	size of segment
 * @dumpfn:	custom dump function called क्रम each segment during coredump
 * @priv:	निजी data
 *
 * Add device memory to the list of segments to be included in the coredump
 * and associate the segment with the given custom dump function and निजी
 * data.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक rproc_coredump_add_custom_segment(काष्ठा rproc *rproc,
				      dma_addr_t da, माप_प्रकार size,
				      व्योम (*dumpfn)(काष्ठा rproc *rproc,
						     काष्ठा rproc_dump_segment *segment,
						     व्योम *dest, माप_प्रकार offset,
						     माप_प्रकार size),
				      व्योम *priv)
अणु
	काष्ठा rproc_dump_segment *segment;

	segment = kzalloc(माप(*segment), GFP_KERNEL);
	अगर (!segment)
		वापस -ENOMEM;

	segment->da = da;
	segment->size = size;
	segment->priv = priv;
	segment->dump = dumpfn;

	list_add_tail(&segment->node, &rproc->dump_segments);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rproc_coredump_add_custom_segment);

/**
 * rproc_coredump_set_elf_info() - set coredump elf inक्रमmation
 * @rproc:	handle of a remote processor
 * @class:	elf class क्रम coredump elf file
 * @machine:	elf machine क्रम coredump elf file
 *
 * Set elf inक्रमmation which will be used क्रम coredump elf file.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक rproc_coredump_set_elf_info(काष्ठा rproc *rproc, u8 class, u16 machine)
अणु
	अगर (class != ELFCLASS64 && class != ELFCLASS32)
		वापस -EINVAL;

	rproc->elf_class = class;
	rproc->elf_machine = machine;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rproc_coredump_set_elf_info);

अटल व्योम rproc_coredump_मुक्त(व्योम *data)
अणु
	काष्ठा rproc_coredump_state *dump_state = data;

	vमुक्त(dump_state->header);
	complete(&dump_state->dump_करोne);
पूर्ण

अटल व्योम *rproc_coredump_find_segment(loff_t user_offset,
					 काष्ठा list_head *segments,
					 माप_प्रकार *data_left)
अणु
	काष्ठा rproc_dump_segment *segment;

	list_क्रम_each_entry(segment, segments, node) अणु
		अगर (user_offset < segment->size) अणु
			*data_left = segment->size - user_offset;
			वापस segment;
		पूर्ण
		user_offset -= segment->size;
	पूर्ण

	*data_left = 0;
	वापस शून्य;
पूर्ण

अटल व्योम rproc_copy_segment(काष्ठा rproc *rproc, व्योम *dest,
			       काष्ठा rproc_dump_segment *segment,
			       माप_प्रकार offset, माप_प्रकार size)
अणु
	व्योम *ptr;
	bool is_iomem;

	अगर (segment->dump) अणु
		segment->dump(rproc, segment, dest, offset, size);
	पूर्ण अन्यथा अणु
		ptr = rproc_da_to_va(rproc, segment->da + offset, size, &is_iomem);
		अगर (!ptr) अणु
			dev_err(&rproc->dev,
				"invalid copy request for segment %pad with offset %zu and size %zu)\n",
				&segment->da, offset, size);
			स_रखो(dest, 0xff, size);
		पूर्ण अन्यथा अणु
			अगर (is_iomem)
				स_नकल_fromio(dest, ptr, size);
			अन्यथा
				स_नकल(dest, ptr, size);
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार rproc_coredump_पढ़ो(अक्षर *buffer, loff_t offset, माप_प्रकार count,
				   व्योम *data, माप_प्रकार header_sz)
अणु
	माप_प्रकार seg_data, bytes_left = count;
	sमाप_प्रकार copy_sz;
	काष्ठा rproc_dump_segment *seg;
	काष्ठा rproc_coredump_state *dump_state = data;
	काष्ठा rproc *rproc = dump_state->rproc;
	व्योम *elfcore = dump_state->header;

	/* Copy the vदो_स्मृति'ed header first. */
	अगर (offset < header_sz) अणु
		copy_sz = memory_पढ़ो_from_buffer(buffer, count, &offset,
						  elfcore, header_sz);

		वापस copy_sz;
	पूर्ण

	/*
	 * Find out the segment memory chunk to be copied based on offset.
	 * Keep copying data until count bytes are पढ़ो.
	 */
	जबतक (bytes_left) अणु
		seg = rproc_coredump_find_segment(offset - header_sz,
						  &rproc->dump_segments,
						  &seg_data);
		/* खातापूर्ण check */
		अगर (!seg) अणु
			dev_info(&rproc->dev, "Ramdump done, %lld bytes read",
				 offset);
			अवरोध;
		पूर्ण

		copy_sz = min_t(माप_प्रकार, bytes_left, seg_data);

		rproc_copy_segment(rproc, buffer, seg, seg->size - seg_data,
				   copy_sz);

		offset += copy_sz;
		buffer += copy_sz;
		bytes_left -= copy_sz;
	पूर्ण

	वापस count - bytes_left;
पूर्ण

/**
 * rproc_coredump() - perक्रमm coredump
 * @rproc:	rproc handle
 *
 * This function will generate an ELF header क्रम the रेजिस्टरed segments
 * and create a devcoredump device associated with rproc. Based on the
 * coredump configuration this function will directly copy the segments
 * from device memory to userspace or copy segments from device memory to
 * a separate buffer, which can then be पढ़ो by userspace.
 * The first approach aव्योमs using extra vदो_स्मृति memory. But it will stall
 * recovery flow until dump is पढ़ो by userspace.
 */
व्योम rproc_coredump(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_dump_segment *segment;
	व्योम *phdr;
	व्योम *ehdr;
	माप_प्रकार data_size;
	माप_प्रकार offset;
	व्योम *data;
	u8 class = rproc->elf_class;
	पूर्णांक phnum = 0;
	काष्ठा rproc_coredump_state dump_state;
	क्रमागत rproc_dump_mechanism dump_conf = rproc->dump_conf;

	अगर (list_empty(&rproc->dump_segments) ||
	    dump_conf == RPROC_COREDUMP_DISABLED)
		वापस;

	अगर (class == ELFCLASSNONE) अणु
		dev_err(&rproc->dev, "Elf class is not set\n");
		वापस;
	पूर्ण

	data_size = elf_size_of_hdr(class);
	list_क्रम_each_entry(segment, &rproc->dump_segments, node) अणु
		/*
		 * For शेष configuration buffer includes headers & segments.
		 * For अंतरभूत dump buffer just includes headers as segments are
		 * directly पढ़ो from device memory.
		 */
		data_size += elf_size_of_phdr(class);
		अगर (dump_conf == RPROC_COREDUMP_ENABLED)
			data_size += segment->size;

		phnum++;
	पूर्ण

	data = vदो_स्मृति(data_size);
	अगर (!data)
		वापस;

	ehdr = data;

	स_रखो(ehdr, 0, elf_size_of_hdr(class));
	/* e_ident field is common क्रम both elf32 and elf64 */
	elf_hdr_init_ident(ehdr, class);

	elf_hdr_set_e_type(class, ehdr, ET_CORE);
	elf_hdr_set_e_machine(class, ehdr, rproc->elf_machine);
	elf_hdr_set_e_version(class, ehdr, EV_CURRENT);
	elf_hdr_set_e_entry(class, ehdr, rproc->bootaddr);
	elf_hdr_set_e_phoff(class, ehdr, elf_size_of_hdr(class));
	elf_hdr_set_e_ehsize(class, ehdr, elf_size_of_hdr(class));
	elf_hdr_set_e_phentsize(class, ehdr, elf_size_of_phdr(class));
	elf_hdr_set_e_phnum(class, ehdr, phnum);

	phdr = data + elf_hdr_get_e_phoff(class, ehdr);
	offset = elf_hdr_get_e_phoff(class, ehdr);
	offset += elf_size_of_phdr(class) * elf_hdr_get_e_phnum(class, ehdr);

	list_क्रम_each_entry(segment, &rproc->dump_segments, node) अणु
		स_रखो(phdr, 0, elf_size_of_phdr(class));
		elf_phdr_set_p_type(class, phdr, PT_LOAD);
		elf_phdr_set_p_offset(class, phdr, offset);
		elf_phdr_set_p_vaddr(class, phdr, segment->da);
		elf_phdr_set_p_paddr(class, phdr, segment->da);
		elf_phdr_set_p_filesz(class, phdr, segment->size);
		elf_phdr_set_p_memsz(class, phdr, segment->size);
		elf_phdr_set_p_flags(class, phdr, PF_R | PF_W | PF_X);
		elf_phdr_set_p_align(class, phdr, 0);

		अगर (dump_conf == RPROC_COREDUMP_ENABLED)
			rproc_copy_segment(rproc, data + offset, segment, 0,
					   segment->size);

		offset += elf_phdr_get_p_filesz(class, phdr);
		phdr += elf_size_of_phdr(class);
	पूर्ण
	अगर (dump_conf == RPROC_COREDUMP_ENABLED) अणु
		dev_coredumpv(&rproc->dev, data, data_size, GFP_KERNEL);
		वापस;
	पूर्ण

	/* Initialize the dump state काष्ठा to be used by rproc_coredump_पढ़ो */
	dump_state.rproc = rproc;
	dump_state.header = data;
	init_completion(&dump_state.dump_करोne);

	dev_coredumpm(&rproc->dev, शून्य, &dump_state, data_size, GFP_KERNEL,
		      rproc_coredump_पढ़ो, rproc_coredump_मुक्त);

	/*
	 * Wait until the dump is पढ़ो and मुक्त is called. Data is मुक्तd
	 * by devcoredump framework स्वतःmatically after 5 minutes.
	 */
	रुको_क्रम_completion(&dump_state.dump_करोne);
पूर्ण

/**
 * rproc_coredump_using_sections() - perक्रमm coredump using section headers
 * @rproc:	rproc handle
 *
 * This function will generate an ELF header क्रम the रेजिस्टरed sections of
 * segments and create a devcoredump device associated with rproc. Based on
 * the coredump configuration this function will directly copy the segments
 * from device memory to userspace or copy segments from device memory to
 * a separate buffer, which can then be पढ़ो by userspace.
 * The first approach aव्योमs using extra vदो_स्मृति memory. But it will stall
 * recovery flow until dump is पढ़ो by userspace.
 */
व्योम rproc_coredump_using_sections(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_dump_segment *segment;
	व्योम *shdr;
	व्योम *ehdr;
	माप_प्रकार data_size;
	माप_प्रकार strtbl_size = 0;
	माप_प्रकार strtbl_index = 1;
	माप_प्रकार offset;
	व्योम *data;
	u8 class = rproc->elf_class;
	पूर्णांक shnum;
	काष्ठा rproc_coredump_state dump_state;
	अचिन्हित पूर्णांक dump_conf = rproc->dump_conf;
	अक्षर *str_tbl = "STR_TBL";

	अगर (list_empty(&rproc->dump_segments) ||
	    dump_conf == RPROC_COREDUMP_DISABLED)
		वापस;

	अगर (class == ELFCLASSNONE) अणु
		dev_err(&rproc->dev, "Elf class is not set\n");
		वापस;
	पूर्ण

	/*
	 * We allocate two extra section headers. The first one is null.
	 * Second section header is क्रम the string table. Also space is
	 * allocated क्रम string table.
	 */
	data_size = elf_size_of_hdr(class) + 2 * elf_size_of_shdr(class);
	shnum = 2;

	/* the extra byte is क्रम the null अक्षरacter at index 0 */
	strtbl_size += म_माप(str_tbl) + 2;

	list_क्रम_each_entry(segment, &rproc->dump_segments, node) अणु
		data_size += elf_size_of_shdr(class);
		strtbl_size += म_माप(segment->priv) + 1;
		अगर (dump_conf == RPROC_COREDUMP_ENABLED)
			data_size += segment->size;
		shnum++;
	पूर्ण

	data_size += strtbl_size;

	data = vदो_स्मृति(data_size);
	अगर (!data)
		वापस;

	ehdr = data;
	स_रखो(ehdr, 0, elf_size_of_hdr(class));
	/* e_ident field is common क्रम both elf32 and elf64 */
	elf_hdr_init_ident(ehdr, class);

	elf_hdr_set_e_type(class, ehdr, ET_CORE);
	elf_hdr_set_e_machine(class, ehdr, rproc->elf_machine);
	elf_hdr_set_e_version(class, ehdr, EV_CURRENT);
	elf_hdr_set_e_entry(class, ehdr, rproc->bootaddr);
	elf_hdr_set_e_shoff(class, ehdr, elf_size_of_hdr(class));
	elf_hdr_set_e_ehsize(class, ehdr, elf_size_of_hdr(class));
	elf_hdr_set_e_shentsize(class, ehdr, elf_size_of_shdr(class));
	elf_hdr_set_e_shnum(class, ehdr, shnum);
	elf_hdr_set_e_shstrndx(class, ehdr, 1);

	/*
	 * The zeroth index of the section header is reserved and is rarely used.
	 * Set the section header as null (SHN_UNDEF) and move to the next one.
	 */
	shdr = data + elf_hdr_get_e_shoff(class, ehdr);
	स_रखो(shdr, 0, elf_size_of_shdr(class));
	shdr += elf_size_of_shdr(class);

	/* Initialize the string table. */
	offset = elf_hdr_get_e_shoff(class, ehdr) +
		 elf_size_of_shdr(class) * elf_hdr_get_e_shnum(class, ehdr);
	स_रखो(data + offset, 0, strtbl_size);

	/* Fill in the string table section header. */
	स_रखो(shdr, 0, elf_size_of_shdr(class));
	elf_shdr_set_sh_type(class, shdr, SHT_STRTAB);
	elf_shdr_set_sh_offset(class, shdr, offset);
	elf_shdr_set_sh_size(class, shdr, strtbl_size);
	elf_shdr_set_sh_entsize(class, shdr, 0);
	elf_shdr_set_sh_flags(class, shdr, 0);
	elf_shdr_set_sh_name(class, shdr, elf_strtbl_add(str_tbl, ehdr, class, &strtbl_index));
	offset += elf_shdr_get_sh_size(class, shdr);
	shdr += elf_size_of_shdr(class);

	list_क्रम_each_entry(segment, &rproc->dump_segments, node) अणु
		स_रखो(shdr, 0, elf_size_of_shdr(class));
		elf_shdr_set_sh_type(class, shdr, SHT_PROGBITS);
		elf_shdr_set_sh_offset(class, shdr, offset);
		elf_shdr_set_sh_addr(class, shdr, segment->da);
		elf_shdr_set_sh_size(class, shdr, segment->size);
		elf_shdr_set_sh_entsize(class, shdr, 0);
		elf_shdr_set_sh_flags(class, shdr, SHF_WRITE);
		elf_shdr_set_sh_name(class, shdr,
				     elf_strtbl_add(segment->priv, ehdr, class, &strtbl_index));

		/* No need to copy segments क्रम अंतरभूत dumps */
		अगर (dump_conf == RPROC_COREDUMP_ENABLED)
			rproc_copy_segment(rproc, data + offset, segment, 0,
					   segment->size);
		offset += elf_shdr_get_sh_size(class, shdr);
		shdr += elf_size_of_shdr(class);
	पूर्ण

	अगर (dump_conf == RPROC_COREDUMP_ENABLED) अणु
		dev_coredumpv(&rproc->dev, data, data_size, GFP_KERNEL);
		वापस;
	पूर्ण

	/* Initialize the dump state काष्ठा to be used by rproc_coredump_पढ़ो */
	dump_state.rproc = rproc;
	dump_state.header = data;
	init_completion(&dump_state.dump_करोne);

	dev_coredumpm(&rproc->dev, शून्य, &dump_state, data_size, GFP_KERNEL,
		      rproc_coredump_पढ़ो, rproc_coredump_मुक्त);

	/* Wait until the dump is पढ़ो and मुक्त is called. Data is मुक्तd
	 * by devcoredump framework स्वतःmatically after 5 minutes.
	 */
	रुको_क्रम_completion(&dump_state.dump_करोne);
पूर्ण
EXPORT_SYMBOL(rproc_coredump_using_sections);
