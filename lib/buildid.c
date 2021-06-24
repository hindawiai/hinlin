<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/buildid.h>
#समावेश <linux/elf.h>
#समावेश <linux/pagemap.h>

#घोषणा BUILD_ID 3
/*
 * Parse build id from the note segment. This logic can be shared between
 * 32-bit and 64-bit प्रणाली, because Elf32_Nhdr and Elf64_Nhdr are
 * identical.
 */
अटल अंतरभूत पूर्णांक parse_build_id(व्योम *page_addr,
				 अचिन्हित अक्षर *build_id,
				 __u32 *size,
				 व्योम *note_start,
				 Elf32_Word note_size)
अणु
	Elf32_Word note_offs = 0, new_offs;

	/* check क्रम overflow */
	अगर (note_start < page_addr || note_start + note_size < note_start)
		वापस -EINVAL;

	/* only supports note that fits in the first page */
	अगर (note_start + note_size > page_addr + PAGE_SIZE)
		वापस -EINVAL;

	जबतक (note_offs + माप(Elf32_Nhdr) < note_size) अणु
		Elf32_Nhdr *nhdr = (Elf32_Nhdr *)(note_start + note_offs);

		अगर (nhdr->n_type == BUILD_ID &&
		    nhdr->n_namesz == माप("GNU") &&
		    nhdr->n_descsz > 0 &&
		    nhdr->n_descsz <= BUILD_ID_SIZE_MAX) अणु
			स_नकल(build_id,
			       note_start + note_offs +
			       ALIGN(माप("GNU"), 4) + माप(Elf32_Nhdr),
			       nhdr->n_descsz);
			स_रखो(build_id + nhdr->n_descsz, 0,
			       BUILD_ID_SIZE_MAX - nhdr->n_descsz);
			अगर (size)
				*size = nhdr->n_descsz;
			वापस 0;
		पूर्ण
		new_offs = note_offs + माप(Elf32_Nhdr) +
			ALIGN(nhdr->n_namesz, 4) + ALIGN(nhdr->n_descsz, 4);
		अगर (new_offs <= note_offs)  /* overflow */
			अवरोध;
		note_offs = new_offs;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Parse build ID from 32-bit ELF */
अटल पूर्णांक get_build_id_32(व्योम *page_addr, अचिन्हित अक्षर *build_id,
			   __u32 *size)
अणु
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)page_addr;
	Elf32_Phdr *phdr;
	पूर्णांक i;

	/* only supports phdr that fits in one page */
	अगर (ehdr->e_phnum >
	    (PAGE_SIZE - माप(Elf32_Ehdr)) / माप(Elf32_Phdr))
		वापस -EINVAL;

	phdr = (Elf32_Phdr *)(page_addr + माप(Elf32_Ehdr));

	क्रम (i = 0; i < ehdr->e_phnum; ++i) अणु
		अगर (phdr[i].p_type == PT_NOTE &&
		    !parse_build_id(page_addr, build_id, size,
				    page_addr + phdr[i].p_offset,
				    phdr[i].p_filesz))
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Parse build ID from 64-bit ELF */
अटल पूर्णांक get_build_id_64(व्योम *page_addr, अचिन्हित अक्षर *build_id,
			   __u32 *size)
अणु
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)page_addr;
	Elf64_Phdr *phdr;
	पूर्णांक i;

	/* only supports phdr that fits in one page */
	अगर (ehdr->e_phnum >
	    (PAGE_SIZE - माप(Elf64_Ehdr)) / माप(Elf64_Phdr))
		वापस -EINVAL;

	phdr = (Elf64_Phdr *)(page_addr + माप(Elf64_Ehdr));

	क्रम (i = 0; i < ehdr->e_phnum; ++i) अणु
		अगर (phdr[i].p_type == PT_NOTE &&
		    !parse_build_id(page_addr, build_id, size,
				    page_addr + phdr[i].p_offset,
				    phdr[i].p_filesz))
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Parse build ID of ELF file mapped to vma
 * @vma:      vma object
 * @build_id: buffer to store build id, at least BUILD_ID_SIZE दीर्घ
 * @size:     वापसs actual build id size in हाल of success
 *
 * Returns 0 on success, otherwise error (< 0).
 */
पूर्णांक build_id_parse(काष्ठा vm_area_काष्ठा *vma, अचिन्हित अक्षर *build_id,
		   __u32 *size)
अणु
	Elf32_Ehdr *ehdr;
	काष्ठा page *page;
	व्योम *page_addr;
	पूर्णांक ret;

	/* only works क्रम page backed storage  */
	अगर (!vma->vm_file)
		वापस -EINVAL;

	page = find_get_page(vma->vm_file->f_mapping, 0);
	अगर (!page)
		वापस -EFAULT;	/* page not mapped */

	ret = -EINVAL;
	page_addr = kmap_atomic(page);
	ehdr = (Elf32_Ehdr *)page_addr;

	/* compare magic x7f "ELF" */
	अगर (स_भेद(ehdr->e_ident, ELFMAG, SELFMAG) != 0)
		जाओ out;

	/* only support executable file and shared object file */
	अगर (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN)
		जाओ out;

	अगर (ehdr->e_ident[EI_CLASS] == ELFCLASS32)
		ret = get_build_id_32(page_addr, build_id, size);
	अन्यथा अगर (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
		ret = get_build_id_64(page_addr, build_id, size);
out:
	kunmap_atomic(page_addr);
	put_page(page);
	वापस ret;
पूर्ण
