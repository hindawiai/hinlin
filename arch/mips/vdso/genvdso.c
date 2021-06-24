<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Alex Smith <alex.smith@imgtec.com>
 */

/*
 * This tool is used to generate the real VDSO images from the raw image. It
 * first patches up the MIPS ABI flags and GNU attributes sections defined in
 * elf.S to have the correct name and type. It then generates a C source file
 * to be compiled पूर्णांकo the kernel containing the VDSO image data and a
 * mips_vdso_image काष्ठा क्रम it, including symbol offsets extracted from the
 * image.
 *
 * We need to be passed both a stripped and unstripped VDSO image. The stripped
 * image is compiled पूर्णांकo the kernel, but we must also patch up the unstripped
 * image's ABI flags sections so that it can be installed and used क्रम
 * debugging.
 */

#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>

#समावेश <byteswap.h>
#समावेश <elf.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

/* Define these in हाल the प्रणाली elf.h is not new enough to have them. */
#अगर_अघोषित SHT_GNU_ATTRIBUTES
# define SHT_GNU_ATTRIBUTES	0x6ffffff5
#पूर्ण_अगर
#अगर_अघोषित SHT_MIPS_ABIFLAGS
# define SHT_MIPS_ABIFLAGS	0x7000002a
#पूर्ण_अगर

क्रमागत अणु
	ABI_O32 = (1 << 0),
	ABI_N32 = (1 << 1),
	ABI_N64 = (1 << 2),

	ABI_ALL = ABI_O32 | ABI_N32 | ABI_N64,
पूर्ण;

/* Symbols the kernel requires offsets क्रम. */
अटल काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *offset_name;
	अचिन्हित पूर्णांक abis;
पूर्ण vdso_symbols[] = अणु
	अणु "__vdso_sigreturn", "off_sigreturn", ABI_O32 पूर्ण,
	अणु "__vdso_rt_sigreturn", "off_rt_sigreturn", ABI_ALL पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर अक्षर *program_name;
अटल स्थिर अक्षर *vdso_name;
अटल अचिन्हित अक्षर elf_class;
अटल अचिन्हित पूर्णांक elf_abi;
अटल bool need_swap;
अटल खाता *out_file;

#अगर __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
# define HOST_ORDER		ELFDATA2LSB
#या_अगर __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
# define HOST_ORDER		ELFDATA2MSB
#पूर्ण_अगर

#घोषणा BUILD_SWAP(bits)						\
	अटल uपूर्णांक##bits##_t swap_uपूर्णांक##bits(uपूर्णांक##bits##_t val)	\
	अणु								\
		वापस need_swap ? bswap_##bits(val) : val;		\
	पूर्ण

BUILD_SWAP(16)
BUILD_SWAP(32)
BUILD_SWAP(64)

#घोषणा __FUNC(name, bits) name##bits
#घोषणा _FUNC(name, bits) __FUNC(name, bits)
#घोषणा FUNC(name) _FUNC(name, ELF_BITS)

#घोषणा __ELF(x, bits) Elf##bits##_##x
#घोषणा _ELF(x, bits) __ELF(x, bits)
#घोषणा ELF(x) _ELF(x, ELF_BITS)

/*
 * Include genvdso.h twice with ELF_BITS defined dअगरferently to get functions
 * क्रम both ELF32 and ELF64.
 */

#घोषणा ELF_BITS 64
#समावेश "genvdso.h"
#अघोषित ELF_BITS

#घोषणा ELF_BITS 32
#समावेश "genvdso.h"
#अघोषित ELF_BITS

अटल व्योम *map_vdso(स्थिर अक्षर *path, माप_प्रकार *_size)
अणु
	पूर्णांक fd;
	काष्ठा stat stat;
	व्योम *addr;
	स्थिर Elf32_Ehdr *ehdr;

	fd = खोलो(path, O_RDWR);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Failed to open '%s': %s\n", program_name,
			path, म_त्रुटि(त्रुटि_सं));
		वापस शून्य;
	पूर्ण

	अगर (ख_स्थिति(fd, &stat) != 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Failed to stat '%s': %s\n", program_name,
			path, म_त्रुटि(त्रुटि_सं));
		बंद(fd);
		वापस शून्य;
	पूर्ण

	addr = mmap(शून्य, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
		    0);
	अगर (addr == MAP_FAILED) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Failed to map '%s': %s\n", program_name,
			path, म_त्रुटि(त्रुटि_सं));
		बंद(fd);
		वापस शून्य;
	पूर्ण

	/* ELF32/64 header क्रमmats are the same क्रम the bits we're checking. */
	ehdr = addr;

	अगर (स_भेद(ehdr->e_ident, ELFMAG, SELFMAG) != 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: '%s' is not an ELF file\n", program_name,
			path);
		बंद(fd);
		वापस शून्य;
	पूर्ण

	elf_class = ehdr->e_ident[EI_CLASS];
	चयन (elf_class) अणु
	हाल ELFCLASS32:
	हाल ELFCLASS64:
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "%s: '%s' has invalid ELF class\n",
			program_name, path);
		बंद(fd);
		वापस शून्य;
	पूर्ण

	चयन (ehdr->e_ident[EI_DATA]) अणु
	हाल ELFDATA2LSB:
	हाल ELFDATA2MSB:
		need_swap = ehdr->e_ident[EI_DATA] != HOST_ORDER;
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "%s: '%s' has invalid ELF data order\n",
			program_name, path);
		बंद(fd);
		वापस शून्य;
	पूर्ण

	अगर (swap_uपूर्णांक16(ehdr->e_machine) != EM_MIPS) अणु
		ख_लिखो(मानक_त्रुटि,
			"%s: '%s' has invalid ELF machine (expected EM_MIPS)\n",
			program_name, path);
		बंद(fd);
		वापस शून्य;
	पूर्ण अन्यथा अगर (swap_uपूर्णांक16(ehdr->e_type) != ET_DYN) अणु
		ख_लिखो(मानक_त्रुटि,
			"%s: '%s' has invalid ELF type (expected ET_DYN)\n",
			program_name, path);
		बंद(fd);
		वापस शून्य;
	पूर्ण

	*_size = stat.st_size;
	बंद(fd);
	वापस addr;
पूर्ण

अटल bool patch_vdso(स्थिर अक्षर *path, व्योम *vdso)
अणु
	अगर (elf_class == ELFCLASS64)
		वापस patch_vdso64(path, vdso);
	अन्यथा
		वापस patch_vdso32(path, vdso);
पूर्ण

अटल bool get_symbols(स्थिर अक्षर *path, व्योम *vdso)
अणु
	अगर (elf_class == ELFCLASS64)
		वापस get_symbols64(path, vdso);
	अन्यथा
		वापस get_symbols32(path, vdso);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *dbg_vdso_path, *vdso_path, *out_path;
	व्योम *dbg_vdso, *vdso;
	माप_प्रकार dbg_vdso_size, vdso_size, i;

	program_name = argv[0];

	अगर (argc < 4 || argc > 5) अणु
		ख_लिखो(मानक_त्रुटि,
			"Usage: %s <debug VDSO> <stripped VDSO> <output file> [<name>]\n",
			program_name);
		वापस निकास_त्रुटि;
	पूर्ण

	dbg_vdso_path = argv[1];
	vdso_path = argv[2];
	out_path = argv[3];
	vdso_name = (argc > 4) ? argv[4] : "";

	dbg_vdso = map_vdso(dbg_vdso_path, &dbg_vdso_size);
	अगर (!dbg_vdso)
		वापस निकास_त्रुटि;

	vdso = map_vdso(vdso_path, &vdso_size);
	अगर (!vdso)
		वापस निकास_त्रुटि;

	/* Patch both the VDSOs' ABI flags sections. */
	अगर (!patch_vdso(dbg_vdso_path, dbg_vdso))
		वापस निकास_त्रुटि;
	अगर (!patch_vdso(vdso_path, vdso))
		वापस निकास_त्रुटि;

	अगर (msync(dbg_vdso, dbg_vdso_size, MS_SYNC) != 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Failed to sync '%s': %s\n", program_name,
			dbg_vdso_path, म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण अन्यथा अगर (msync(vdso, vdso_size, MS_SYNC) != 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Failed to sync '%s': %s\n", program_name,
			vdso_path, म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण

	out_file = ख_खोलो(out_path, "w");
	अगर (!out_file) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Failed to open '%s': %s\n", program_name,
			out_path, म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण

	ख_लिखो(out_file, "/* Automatically generated - do not edit */\n");
	ख_लिखो(out_file, "#include <linux/linkage.h>\n");
	ख_लिखो(out_file, "#include <linux/mm.h>\n");
	ख_लिखो(out_file, "#include <asm/vdso.h>\n");
	ख_लिखो(out_file, "static int vdso_mremap(\n");
	ख_लिखो(out_file, "	const struct vm_special_mapping *sm,\n");
	ख_लिखो(out_file, "	struct vm_area_struct *new_vma)\n");
	ख_लिखो(out_file, "{\n");
	ख_लिखो(out_file, "	current->mm->context.vdso =\n");
	ख_लिखो(out_file, "	(void *)(new_vma->vm_start);\n");
	ख_लिखो(out_file, "	return 0;\n");
	ख_लिखो(out_file, "}\n");

	/* Write out the stripped VDSO data. */
	ख_लिखो(out_file,
		"static unsigned char vdso_data[PAGE_ALIGN(%zu)] __page_aligned_data = {\n\t",
		vdso_size);
	क्रम (i = 0; i < vdso_size; i++) अणु
		अगर (!(i % 10))
			ख_लिखो(out_file, "\n\t");
		ख_लिखो(out_file, "0x%02x, ", ((अचिन्हित अक्षर *)vdso)[i]);
	पूर्ण
	ख_लिखो(out_file, "\n};\n");

	/* Pपुनः_स्मृतिate a page array. */
	ख_लिखो(out_file,
		"static struct page *vdso_pages[PAGE_ALIGN(%zu) / PAGE_SIZE];\n",
		vdso_size);

	ख_लिखो(out_file, "struct mips_vdso_image vdso_image%s%s = {\n",
		(vdso_name[0]) ? "_" : "", vdso_name);
	ख_लिखो(out_file, "\t.data = vdso_data,\n");
	ख_लिखो(out_file, "\t.size = PAGE_ALIGN(%zu),\n", vdso_size);
	ख_लिखो(out_file, "\t.mapping = {\n");
	ख_लिखो(out_file, "\t\t.name = \"[vdso]\",\n");
	ख_लिखो(out_file, "\t\t.pages = vdso_pages,\n");
	ख_लिखो(out_file, "\t\t.mremap = vdso_mremap,\n");
	ख_लिखो(out_file, "\t},\n");

	/* Calculate and ग_लिखो symbol offsets to <output file> */
	अगर (!get_symbols(dbg_vdso_path, dbg_vdso)) अणु
		unlink(out_path);
		ख_बंद(out_file);
		वापस निकास_त्रुटि;
	पूर्ण

	ख_लिखो(out_file, "};\n");
	ख_बंद(out_file);

	वापस निकास_सफल;
पूर्ण
