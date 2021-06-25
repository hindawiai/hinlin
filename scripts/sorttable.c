<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sorttable.c: Sort the kernel's table
 *
 * Added ORC unwind tables sort support and other updates:
 * Copyright (C) 1999-2019 Alibaba Group Holding Limited. by:
 * Shile Zhang <shile.zhang@linux.alibaba.com>
 *
 * Copyright 2011 - 2012 Cavium, Inc.
 *
 * Based on code taken from recorपंचांगcount.c which is:
 *
 * Copyright 2009 John F. Reiser <jreiser@BitWagon.com>.  All rights reserved.
 *
 * Reकाष्ठाured to fit Linux क्रमmat, as well as other updates:
 * Copyright 2010 Steven Rostedt <srostedt@redhat.com>, Red Hat Inc.
 */

/*
 * Strategy: alter the vmlinux file in-place.
 */

#समावेश <sys/types.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <getopt.h>
#समावेश <elf.h>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश <tools/be_byteshअगरt.h>
#समावेश <tools/le_byteshअगरt.h>

#अगर_अघोषित EM_ARCOMPACT
#घोषणा EM_ARCOMPACT	93
#पूर्ण_अगर

#अगर_अघोषित EM_XTENSA
#घोषणा EM_XTENSA	94
#पूर्ण_अगर

#अगर_अघोषित EM_AARCH64
#घोषणा EM_AARCH64	183
#पूर्ण_अगर

#अगर_अघोषित EM_MICROBLAZE
#घोषणा EM_MICROBLAZE	189
#पूर्ण_अगर

#अगर_अघोषित EM_ARCV2
#घोषणा EM_ARCV2	195
#पूर्ण_अगर

अटल uपूर्णांक32_t (*r)(स्थिर uपूर्णांक32_t *);
अटल uपूर्णांक16_t (*r2)(स्थिर uपूर्णांक16_t *);
अटल uपूर्णांक64_t (*r8)(स्थिर uपूर्णांक64_t *);
अटल व्योम (*w)(uपूर्णांक32_t, uपूर्णांक32_t *);
अटल व्योम (*w2)(uपूर्णांक16_t, uपूर्णांक16_t *);
अटल व्योम (*w8)(uपूर्णांक64_t, uपूर्णांक64_t *);
प्रकार व्योम (*table_sort_t)(अक्षर *, पूर्णांक);

/*
 * Get the whole file as a programming convenience in order to aव्योम
 * दो_स्मृति+lseek+पढ़ो+मुक्त of many pieces.  If successful, then mmap
 * aव्योमs copying unused pieces; अन्यथा just पढ़ो the whole file.
 * Open क्रम both पढ़ो and ग_लिखो.
 */
अटल व्योम *mmap_file(अक्षर स्थिर *fname, माप_प्रकार *size)
अणु
	पूर्णांक fd;
	काष्ठा stat sb;
	व्योम *addr = शून्य;

	fd = खोलो(fname, O_RDWR);
	अगर (fd < 0) अणु
		लिखो_त्रुटि(fname);
		वापस शून्य;
	पूर्ण
	अगर (ख_स्थिति(fd, &sb) < 0) अणु
		लिखो_त्रुटि(fname);
		जाओ out;
	पूर्ण
	अगर (!S_ISREG(sb.st_mode)) अणु
		ख_लिखो(मानक_त्रुटि, "not a regular file: %s\n", fname);
		जाओ out;
	पूर्ण

	addr = mmap(0, sb.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	अगर (addr == MAP_FAILED) अणु
		ख_लिखो(मानक_त्रुटि, "Could not mmap file: %s\n", fname);
		जाओ out;
	पूर्ण

	*size = sb.st_size;

out:
	बंद(fd);
	वापस addr;
पूर्ण

अटल uपूर्णांक32_t rbe(स्थिर uपूर्णांक32_t *x)
अणु
	वापस get_unaligned_be32(x);
पूर्ण

अटल uपूर्णांक16_t r2be(स्थिर uपूर्णांक16_t *x)
अणु
	वापस get_unaligned_be16(x);
पूर्ण

अटल uपूर्णांक64_t r8be(स्थिर uपूर्णांक64_t *x)
अणु
	वापस get_unaligned_be64(x);
पूर्ण

अटल uपूर्णांक32_t rle(स्थिर uपूर्णांक32_t *x)
अणु
	वापस get_unaligned_le32(x);
पूर्ण

अटल uपूर्णांक16_t r2le(स्थिर uपूर्णांक16_t *x)
अणु
	वापस get_unaligned_le16(x);
पूर्ण

अटल uपूर्णांक64_t r8le(स्थिर uपूर्णांक64_t *x)
अणु
	वापस get_unaligned_le64(x);
पूर्ण

अटल व्योम wbe(uपूर्णांक32_t val, uपूर्णांक32_t *x)
अणु
	put_unaligned_be32(val, x);
पूर्ण

अटल व्योम w2be(uपूर्णांक16_t val, uपूर्णांक16_t *x)
अणु
	put_unaligned_be16(val, x);
पूर्ण

अटल व्योम w8be(uपूर्णांक64_t val, uपूर्णांक64_t *x)
अणु
	put_unaligned_be64(val, x);
पूर्ण

अटल व्योम wle(uपूर्णांक32_t val, uपूर्णांक32_t *x)
अणु
	put_unaligned_le32(val, x);
पूर्ण

अटल व्योम w2le(uपूर्णांक16_t val, uपूर्णांक16_t *x)
अणु
	put_unaligned_le16(val, x);
पूर्ण

अटल व्योम w8le(uपूर्णांक64_t val, uपूर्णांक64_t *x)
अणु
	put_unaligned_le64(val, x);
पूर्ण

/*
 * Move reserved section indices SHN_LORESERVE..SHN_HIRESERVE out of
 * the way to -256..-1, to aव्योम conflicting with real section
 * indices.
 */
#घोषणा SPECIAL(i) ((i) - (SHN_HIRESERVE + 1))

अटल अंतरभूत पूर्णांक is_shndx_special(अचिन्हित पूर्णांक i)
अणु
	वापस i != SHN_XINDEX && i >= SHN_LORESERVE && i <= SHN_HIRESERVE;
पूर्ण

/* Accessor क्रम sym->st_shndx, hides ugliness of "64k sections" */
अटल अंतरभूत अचिन्हित पूर्णांक get_secindex(अचिन्हित पूर्णांक shndx,
					अचिन्हित पूर्णांक sym_offs,
					स्थिर Elf32_Word *symtab_shndx_start)
अणु
	अगर (is_shndx_special(shndx))
		वापस SPECIAL(shndx);
	अगर (shndx != SHN_XINDEX)
		वापस shndx;
	वापस r(&symtab_shndx_start[sym_offs]);
पूर्ण

/* 32 bit and 64 bit are very similar */
#समावेश "sorttable.h"
#घोषणा SORTTABLE_64
#समावेश "sorttable.h"

अटल पूर्णांक compare_relative_table(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	पूर्णांक32_t av = (पूर्णांक32_t)r(a);
	पूर्णांक32_t bv = (पूर्णांक32_t)r(b);

	अगर (av < bv)
		वापस -1;
	अगर (av > bv)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम sort_relative_table(अक्षर *extab_image, पूर्णांक image_size)
अणु
	पूर्णांक i = 0;

	/*
	 * Do the same thing the runसमय sort करोes, first normalize to
	 * being relative to the start of the section.
	 */
	जबतक (i < image_size) अणु
		uपूर्णांक32_t *loc = (uपूर्णांक32_t *)(extab_image + i);
		w(r(loc) + i, loc);
		i += 4;
	पूर्ण

	क्विक(extab_image, image_size / 8, 8, compare_relative_table);

	/* Now denormalize. */
	i = 0;
	जबतक (i < image_size) अणु
		uपूर्णांक32_t *loc = (uपूर्णांक32_t *)(extab_image + i);
		w(r(loc) - i, loc);
		i += 4;
	पूर्ण
पूर्ण

अटल व्योम x86_sort_relative_table(अक्षर *extab_image, पूर्णांक image_size)
अणु
	पूर्णांक i = 0;

	जबतक (i < image_size) अणु
		uपूर्णांक32_t *loc = (uपूर्णांक32_t *)(extab_image + i);

		w(r(loc) + i, loc);
		w(r(loc + 1) + i + 4, loc + 1);
		w(r(loc + 2) + i + 8, loc + 2);

		i += माप(uपूर्णांक32_t) * 3;
	पूर्ण

	क्विक(extab_image, image_size / 12, 12, compare_relative_table);

	i = 0;
	जबतक (i < image_size) अणु
		uपूर्णांक32_t *loc = (uपूर्णांक32_t *)(extab_image + i);

		w(r(loc) - i, loc);
		w(r(loc + 1) - (i + 4), loc + 1);
		w(r(loc + 2) - (i + 8), loc + 2);

		i += माप(uपूर्णांक32_t) * 3;
	पूर्ण
पूर्ण

अटल व्योम s390_sort_relative_table(अक्षर *extab_image, पूर्णांक image_size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < image_size; i += 16) अणु
		अक्षर *loc = extab_image + i;
		uपूर्णांक64_t handler;

		w(r((uपूर्णांक32_t *)loc) + i, (uपूर्णांक32_t *)loc);
		w(r((uपूर्णांक32_t *)(loc + 4)) + (i + 4), (uपूर्णांक32_t *)(loc + 4));
		/*
		 * 0 is a special self-relative handler value, which means that
		 * handler should be ignored. It is safe, because it means that
		 * handler field poपूर्णांकs to itself, which should never happen.
		 * When creating extable-relative values, keep it as 0, since
		 * this should never occur either: it would mean that handler
		 * field poपूर्णांकs to the first extable entry.
		 */
		handler = r8((uपूर्णांक64_t *)(loc + 8));
		अगर (handler)
			handler += i + 8;
		w8(handler, (uपूर्णांक64_t *)(loc + 8));
	पूर्ण

	क्विक(extab_image, image_size / 16, 16, compare_relative_table);

	क्रम (i = 0; i < image_size; i += 16) अणु
		अक्षर *loc = extab_image + i;
		uपूर्णांक64_t handler;

		w(r((uपूर्णांक32_t *)loc) - i, (uपूर्णांक32_t *)loc);
		w(r((uपूर्णांक32_t *)(loc + 4)) - (i + 4), (uपूर्णांक32_t *)(loc + 4));
		handler = r8((uपूर्णांक64_t *)(loc + 8));
		अगर (handler)
			handler -= i + 8;
		w8(handler, (uपूर्णांक64_t *)(loc + 8));
	पूर्ण
पूर्ण

अटल पूर्णांक करो_file(अक्षर स्थिर *स्थिर fname, व्योम *addr)
अणु
	पूर्णांक rc = -1;
	Elf32_Ehdr *ehdr = addr;
	table_sort_t custom_sort = शून्य;

	चयन (ehdr->e_ident[EI_DATA]) अणु
	हाल ELFDATA2LSB:
		r	= rle;
		r2	= r2le;
		r8	= r8le;
		w	= wle;
		w2	= w2le;
		w8	= w8le;
		अवरोध;
	हाल ELFDATA2MSB:
		r	= rbe;
		r2	= r2be;
		r8	= r8be;
		w	= wbe;
		w2	= w2be;
		w8	= w8be;
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "unrecognized ELF data encoding %d: %s\n",
			ehdr->e_ident[EI_DATA], fname);
		वापस -1;
	पूर्ण

	अगर (स_भेद(ELFMAG, ehdr->e_ident, SELFMAG) != 0 ||
	    (r2(&ehdr->e_type) != ET_EXEC && r2(&ehdr->e_type) != ET_DYN) ||
	    ehdr->e_ident[EI_VERSION] != EV_CURRENT) अणु
		ख_लिखो(मानक_त्रुटि, "unrecognized ET_EXEC/ET_DYN file %s\n", fname);
		वापस -1;
	पूर्ण

	चयन (r2(&ehdr->e_machine)) अणु
	हाल EM_386:
	हाल EM_X86_64:
		custom_sort = x86_sort_relative_table;
		अवरोध;
	हाल EM_S390:
		custom_sort = s390_sort_relative_table;
		अवरोध;
	हाल EM_AARCH64:
	हाल EM_PARISC:
	हाल EM_PPC:
	हाल EM_PPC64:
		custom_sort = sort_relative_table;
		अवरोध;
	हाल EM_ARCOMPACT:
	हाल EM_ARCV2:
	हाल EM_ARM:
	हाल EM_MICROBLAZE:
	हाल EM_MIPS:
	हाल EM_XTENSA:
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "unrecognized e_machine %d %s\n",
			r2(&ehdr->e_machine), fname);
		वापस -1;
	पूर्ण

	चयन (ehdr->e_ident[EI_CLASS]) अणु
	हाल ELFCLASS32:
		अगर (r2(&ehdr->e_ehsize) != माप(Elf32_Ehdr) ||
		    r2(&ehdr->e_shentsize) != माप(Elf32_Shdr)) अणु
			ख_लिखो(मानक_त्रुटि,
				"unrecognized ET_EXEC/ET_DYN file: %s\n", fname);
			अवरोध;
		पूर्ण
		rc = करो_sort_32(ehdr, fname, custom_sort);
		अवरोध;
	हाल ELFCLASS64:
		अणु
		Elf64_Ehdr *स्थिर ghdr = (Elf64_Ehdr *)ehdr;
		अगर (r2(&ghdr->e_ehsize) != माप(Elf64_Ehdr) ||
		    r2(&ghdr->e_shentsize) != माप(Elf64_Shdr)) अणु
			ख_लिखो(मानक_त्रुटि,
				"unrecognized ET_EXEC/ET_DYN file: %s\n",
				fname);
			अवरोध;
		पूर्ण
		rc = करो_sort_64(ghdr, fname, custom_sort);
		पूर्ण
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "unrecognized ELF class %d %s\n",
			ehdr->e_ident[EI_CLASS], fname);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक i, n_error = 0;  /* gcc-4.3.0 false positive complaपूर्णांक */
	माप_प्रकार size = 0;
	व्योम *addr = शून्य;

	अगर (argc < 2) अणु
		ख_लिखो(मानक_त्रुटि, "usage: sorttable vmlinux...\n");
		वापस 0;
	पूर्ण

	/* Process each file in turn, allowing deep failure. */
	क्रम (i = 1; i < argc; i++) अणु
		addr = mmap_file(argv[i], &size);
		अगर (!addr) अणु
			++n_error;
			जारी;
		पूर्ण

		अगर (करो_file(argv[i], addr))
			++n_error;

		munmap(addr, size);
	पूर्ण

	वापस !!n_error;
पूर्ण
