<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * recordmcount.c: स्थिरruct a table of the locations of calls to 'mcount'
 * so that ftrace can find them quickly.
 * Copyright 2009 John F. Reiser <jreiser@BitWagon.com>.  All rights reserved.
 *
 * Reकाष्ठाured to fit Linux क्रमmat, as well as other updates:
 *  Copyright 2010 Steven Rostedt <srostedt@redhat.com>, Red Hat Inc.
 */

/*
 * Strategy: alter the .o file in-place.
 *
 * Append a new STRTAB that has the new section names, followed by a new array
 * ElfXX_Shdr[] that has the new section headers, followed by the section
 * contents क्रम __mcount_loc and its relocations.  The old shstrtab strings,
 * and the old ElfXX_Shdr[] array, reमुख्य as "garbage" (commonly, a couple
 * kilobytes.)  Subsequent processing by /bin/ld (or the kernel module loader)
 * will ignore the garbage regions, because they are not designated by the
 * new .e_shoff nor the new ElfXX_Shdr[].  [In order to हटाओ the garbage,
 * then use "ld -r" to create a new file that omits the garbage.]
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

#अगर_अघोषित EM_AARCH64
#घोषणा EM_AARCH64	183
#घोषणा R_AARCH64_NONE		0
#घोषणा R_AARCH64_ABS64	257
#पूर्ण_अगर

#घोषणा R_ARM_PC24		1
#घोषणा R_ARM_THM_CALL		10
#घोषणा R_ARM_CALL		28

#घोषणा R_AARCH64_CALL26	283

अटल पूर्णांक fd_map;	/* File descriptor क्रम file being modअगरied. */
अटल पूर्णांक mmap_failed; /* Boolean flag. */
अटल अक्षर gpfx;	/* prefix क्रम global symbol name (someबार '_') */
अटल काष्ठा stat sb;	/* Remember .st_size, etc. */
अटल स्थिर अक्षर *alपंचांगcount;	/* alternate mcount symbol name */
अटल पूर्णांक warn_on_notrace_sect; /* warn when section has mcount not being recorded */
अटल व्योम *file_map;	/* poपूर्णांकer of the mapped file */
अटल व्योम *file_end;	/* poपूर्णांकer to the end of the mapped file */
अटल पूर्णांक file_updated; /* flag to state file was changed */
अटल व्योम *file_ptr;	/* current file poपूर्णांकer location */

अटल व्योम *file_append; /* added to the end of the file */
अटल माप_प्रकार file_append_size; /* how much is added to end of file */

/* Per-file resource cleanup when multiple files. */
अटल व्योम file_append_cleanup(व्योम)
अणु
	मुक्त(file_append);
	file_append = शून्य;
	file_append_size = 0;
	file_updated = 0;
पूर्ण

अटल व्योम mmap_cleanup(व्योम)
अणु
	अगर (!mmap_failed)
		munmap(file_map, sb.st_size);
	अन्यथा
		मुक्त(file_map);
	file_map = शून्य;
पूर्ण

/* ulseek, uग_लिखो, ...:  Check वापस value क्रम errors. */

अटल off_t ulseek(off_t स्थिर offset, पूर्णांक स्थिर whence)
अणु
	चयन (whence) अणु
	हाल शुरू_से:
		file_ptr = file_map + offset;
		अवरोध;
	हाल प्रस्तुत_से:
		file_ptr += offset;
		अवरोध;
	हाल अंत_से:
		file_ptr = file_map + (sb.st_size - offset);
		अवरोध;
	पूर्ण
	अगर (file_ptr < file_map) अणु
		ख_लिखो(मानक_त्रुटि, "lseek: seek before file\n");
		वापस -1;
	पूर्ण
	वापस file_ptr - file_map;
पूर्ण

अटल sमाप_प्रकार uग_लिखो(व्योम स्थिर *स्थिर buf, माप_प्रकार स्थिर count)
अणु
	माप_प्रकार cnt = count;
	off_t idx = 0;

	file_updated = 1;

	अगर (file_ptr + count >= file_end) अणु
		off_t aoffset = (file_ptr + count) - file_end;

		अगर (aoffset > file_append_size) अणु
			file_append = पुनः_स्मृति(file_append, aoffset);
			file_append_size = aoffset;
		पूर्ण
		अगर (!file_append) अणु
			लिखो_त्रुटि("write");
			file_append_cleanup();
			mmap_cleanup();
			वापस -1;
		पूर्ण
		अगर (file_ptr < file_end) अणु
			cnt = file_end - file_ptr;
		पूर्ण अन्यथा अणु
			cnt = 0;
			idx = aoffset - count;
		पूर्ण
	पूर्ण

	अगर (cnt)
		स_नकल(file_ptr, buf, cnt);

	अगर (cnt < count)
		स_नकल(file_append + idx, buf + cnt, count - cnt);

	file_ptr += count;
	वापस count;
पूर्ण

अटल व्योम * uदो_स्मृति(माप_प्रकार size)
अणु
	व्योम *स्थिर addr = दो_स्मृति(size);
	अगर (addr == 0) अणु
		ख_लिखो(मानक_त्रुटि, "malloc failed: %zu bytes\n", size);
		file_append_cleanup();
		mmap_cleanup();
		वापस शून्य;
	पूर्ण
	वापस addr;
पूर्ण

/*
 * Get the whole file as a programming convenience in order to aव्योम
 * दो_स्मृति+lseek+पढ़ो+मुक्त of many pieces.  If successful, then mmap
 * aव्योमs copying unused pieces; अन्यथा just पढ़ो the whole file.
 * Open क्रम both पढ़ो and ग_लिखो; new info will be appended to the file.
 * Use MAP_PRIVATE so that a few changes to the in-memory ElfXX_Ehdr
 * करो not propagate to the file until an explicit overग_लिखो at the last.
 * This preserves most aspects of consistency (all except .st_size)
 * क्रम simultaneous पढ़ोers of the file जबतक we are appending to it.
 * However, multiple ग_लिखोrs still are bad.  We choose not to use
 * locking because it is expensive and the use हाल of kernel build
 * makes multiple ग_लिखोrs unlikely.
 */
अटल व्योम *mmap_file(अक्षर स्थिर *fname)
अणु
	/* Aव्योम problems अगर early cleanup() */
	fd_map = -1;
	mmap_failed = 1;
	file_map = शून्य;
	file_ptr = शून्य;
	file_updated = 0;
	sb.st_size = 0;

	fd_map = खोलो(fname, O_RDONLY);
	अगर (fd_map < 0) अणु
		लिखो_त्रुटि(fname);
		वापस शून्य;
	पूर्ण
	अगर (ख_स्थिति(fd_map, &sb) < 0) अणु
		लिखो_त्रुटि(fname);
		जाओ out;
	पूर्ण
	अगर (!S_ISREG(sb.st_mode)) अणु
		ख_लिखो(मानक_त्रुटि, "not a regular file: %s\n", fname);
		जाओ out;
	पूर्ण
	file_map = mmap(0, sb.st_size, PROT_READ|PROT_WRITE, MAP_PRIVATE,
			fd_map, 0);
	अगर (file_map == MAP_FAILED) अणु
		mmap_failed = 1;
		file_map = uदो_स्मृति(sb.st_size);
		अगर (!file_map) अणु
			लिखो_त्रुटि(fname);
			जाओ out;
		पूर्ण
		अगर (पढ़ो(fd_map, file_map, sb.st_size) != sb.st_size) अणु
			लिखो_त्रुटि(fname);
			मुक्त(file_map);
			file_map = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		mmap_failed = 0;
out:
	बंद(fd_map);
	fd_map = -1;

	file_end = file_map + sb.st_size;

	वापस file_map;
पूर्ण


अटल अचिन्हित अक्षर ideal_nop5_x86_64[5] = अणु 0x0f, 0x1f, 0x44, 0x00, 0x00 पूर्ण;
अटल अचिन्हित अक्षर ideal_nop5_x86_32[5] = अणु 0x3e, 0x8d, 0x74, 0x26, 0x00 पूर्ण;
अटल अचिन्हित अक्षर *ideal_nop;

अटल अक्षर rel_type_nop;

अटल पूर्णांक (*make_nop)(व्योम *map, माप_प्रकार स्थिर offset);

अटल पूर्णांक make_nop_x86(व्योम *map, माप_प्रकार स्थिर offset)
अणु
	uपूर्णांक32_t *ptr;
	अचिन्हित अक्षर *op;

	/* Confirm we have 0xe8 0x0 0x0 0x0 0x0 */
	ptr = map + offset;
	अगर (*ptr != 0)
		वापस -1;

	op = map + offset - 1;
	अगर (*op != 0xe8)
		वापस -1;

	/* convert to nop */
	अगर (ulseek(offset - 1, शुरू_से) < 0)
		वापस -1;
	अगर (uग_लिखो(ideal_nop, 5) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर ideal_nop4_arm_le[4] = अणु 0x00, 0x00, 0xa0, 0xe1 पूर्ण; /* mov r0, r0 */
अटल अचिन्हित अक्षर ideal_nop4_arm_be[4] = अणु 0xe1, 0xa0, 0x00, 0x00 पूर्ण; /* mov r0, r0 */
अटल अचिन्हित अक्षर *ideal_nop4_arm;

अटल अचिन्हित अक्षर bl_mcount_arm_le[4] = अणु 0xfe, 0xff, 0xff, 0xeb पूर्ण; /* bl */
अटल अचिन्हित अक्षर bl_mcount_arm_be[4] = अणु 0xeb, 0xff, 0xff, 0xfe पूर्ण; /* bl */
अटल अचिन्हित अक्षर *bl_mcount_arm;

अटल अचिन्हित अक्षर push_arm_le[4] = अणु 0x04, 0xe0, 0x2d, 0xe5 पूर्ण; /* push अणुlrपूर्ण */
अटल अचिन्हित अक्षर push_arm_be[4] = अणु 0xe5, 0x2d, 0xe0, 0x04 पूर्ण; /* push अणुlrपूर्ण */
अटल अचिन्हित अक्षर *push_arm;

अटल अचिन्हित अक्षर ideal_nop2_thumb_le[2] = अणु 0x00, 0xbf पूर्ण; /* nop */
अटल अचिन्हित अक्षर ideal_nop2_thumb_be[2] = अणु 0xbf, 0x00 पूर्ण; /* nop */
अटल अचिन्हित अक्षर *ideal_nop2_thumb;

अटल अचिन्हित अक्षर push_bl_mcount_thumb_le[6] = अणु 0x00, 0xb5, 0xff, 0xf7, 0xfe, 0xff पूर्ण; /* push अणुlrपूर्ण, bl */
अटल अचिन्हित अक्षर push_bl_mcount_thumb_be[6] = अणु 0xb5, 0x00, 0xf7, 0xff, 0xff, 0xfe पूर्ण; /* push अणुlrपूर्ण, bl */
अटल अचिन्हित अक्षर *push_bl_mcount_thumb;

अटल पूर्णांक make_nop_arm(व्योम *map, माप_प्रकार स्थिर offset)
अणु
	अक्षर *ptr;
	पूर्णांक cnt = 1;
	पूर्णांक nop_size;
	माप_प्रकार off = offset;

	ptr = map + offset;
	अगर (स_भेद(ptr, bl_mcount_arm, 4) == 0) अणु
		अगर (स_भेद(ptr - 4, push_arm, 4) == 0) अणु
			off -= 4;
			cnt = 2;
		पूर्ण
		ideal_nop = ideal_nop4_arm;
		nop_size = 4;
	पूर्ण अन्यथा अगर (स_भेद(ptr - 2, push_bl_mcount_thumb, 6) == 0) अणु
		cnt = 3;
		nop_size = 2;
		off -= 2;
		ideal_nop = ideal_nop2_thumb;
	पूर्ण अन्यथा
		वापस -1;

	/* Convert to nop */
	अगर (ulseek(off, शुरू_से) < 0)
		वापस -1;

	करो अणु
		अगर (uग_लिखो(ideal_nop, nop_size) < 0)
			वापस -1;
	पूर्ण जबतक (--cnt > 0);

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर ideal_nop4_arm64[4] = अणु0x1f, 0x20, 0x03, 0xd5पूर्ण;
अटल पूर्णांक make_nop_arm64(व्योम *map, माप_प्रकार स्थिर offset)
अणु
	uपूर्णांक32_t *ptr;

	ptr = map + offset;
	/* bl <_mcount> is 0x94000000 beक्रमe relocation */
	अगर (*ptr != 0x94000000)
		वापस -1;

	/* Convert to nop */
	अगर (ulseek(offset, शुरू_से) < 0)
		वापस -1;
	अगर (uग_लिखो(ideal_nop, 4) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_file(स्थिर अक्षर *fname)
अणु
	अक्षर पंचांगp_file[म_माप(fname) + 4];
	माप_प्रकार n;

	अगर (!file_updated)
		वापस 0;

	प्र_लिखो(पंचांगp_file, "%s.rc", fname);

	/*
	 * After पढ़ोing the entire file पूर्णांकo memory, delete it
	 * and ग_लिखो it back, to prevent weird side effects of modअगरying
	 * an object file in place.
	 */
	fd_map = खोलो(पंचांगp_file, O_WRONLY | O_TRUNC | O_CREAT, sb.st_mode);
	अगर (fd_map < 0) अणु
		लिखो_त्रुटि(fname);
		वापस -1;
	पूर्ण
	n = ग_लिखो(fd_map, file_map, sb.st_size);
	अगर (n != sb.st_size) अणु
		लिखो_त्रुटि("write");
		बंद(fd_map);
		वापस -1;
	पूर्ण
	अगर (file_append_size) अणु
		n = ग_लिखो(fd_map, file_append, file_append_size);
		अगर (n != file_append_size) अणु
			लिखो_त्रुटि("write");
			बंद(fd_map);
			वापस -1;
		पूर्ण
	पूर्ण
	बंद(fd_map);
	अगर (नाम(पंचांगp_file, fname) < 0) अणु
		लिखो_त्रुटि(fname);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/* w8rev, w8nat, ...: Handle endianness. */

अटल uपूर्णांक64_t w8rev(uपूर्णांक64_t स्थिर x)
अणु
	वापस   ((0xff & (x >> (0 * 8))) << (7 * 8))
	       | ((0xff & (x >> (1 * 8))) << (6 * 8))
	       | ((0xff & (x >> (2 * 8))) << (5 * 8))
	       | ((0xff & (x >> (3 * 8))) << (4 * 8))
	       | ((0xff & (x >> (4 * 8))) << (3 * 8))
	       | ((0xff & (x >> (5 * 8))) << (2 * 8))
	       | ((0xff & (x >> (6 * 8))) << (1 * 8))
	       | ((0xff & (x >> (7 * 8))) << (0 * 8));
पूर्ण

अटल uपूर्णांक32_t w4rev(uपूर्णांक32_t स्थिर x)
अणु
	वापस   ((0xff & (x >> (0 * 8))) << (3 * 8))
	       | ((0xff & (x >> (1 * 8))) << (2 * 8))
	       | ((0xff & (x >> (2 * 8))) << (1 * 8))
	       | ((0xff & (x >> (3 * 8))) << (0 * 8));
पूर्ण

अटल uपूर्णांक32_t w2rev(uपूर्णांक16_t स्थिर x)
अणु
	वापस   ((0xff & (x >> (0 * 8))) << (1 * 8))
	       | ((0xff & (x >> (1 * 8))) << (0 * 8));
पूर्ण

अटल uपूर्णांक64_t w8nat(uपूर्णांक64_t स्थिर x)
अणु
	वापस x;
पूर्ण

अटल uपूर्णांक32_t w4nat(uपूर्णांक32_t स्थिर x)
अणु
	वापस x;
पूर्ण

अटल uपूर्णांक32_t w2nat(uपूर्णांक16_t स्थिर x)
अणु
	वापस x;
पूर्ण

अटल uपूर्णांक64_t (*w8)(uपूर्णांक64_t);
अटल uपूर्णांक32_t (*w)(uपूर्णांक32_t);
अटल uपूर्णांक32_t (*w2)(uपूर्णांक16_t);

/* Names of the sections that could contain calls to mcount. */
अटल पूर्णांक is_mcounted_section_name(अक्षर स्थिर *स्थिर txtname)
अणु
	वापस म_भेदन(".text",          txtname, 5) == 0 ||
		म_भेद(".init.text",     txtname) == 0 ||
		म_भेद(".ref.text",      txtname) == 0 ||
		म_भेद(".sched.text",    txtname) == 0 ||
		म_भेद(".spinlock.text", txtname) == 0 ||
		म_भेद(".irqentry.text", txtname) == 0 ||
		म_भेद(".softirqentry.text", txtname) == 0 ||
		म_भेद(".kprobes.text", txtname) == 0 ||
		म_भेद(".cpuidle.text", txtname) == 0;
पूर्ण

अटल अक्षर स्थिर *alपढ़ोy_has_rel_mcount = "success"; /* our work here is करोne! */

/* 32 bit and 64 bit are very similar */
#समावेश "recordmcount.h"
#घोषणा RECORD_MCOUNT_64
#समावेश "recordmcount.h"

अटल पूर्णांक arm_is_fake_mcount(Elf32_Rel स्थिर *rp)
अणु
	चयन (ELF32_R_TYPE(w(rp->r_info))) अणु
	हाल R_ARM_THM_CALL:
	हाल R_ARM_CALL:
	हाल R_ARM_PC24:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक arm64_is_fake_mcount(Elf64_Rel स्थिर *rp)
अणु
	वापस ELF64_R_TYPE(w8(rp->r_info)) != R_AARCH64_CALL26;
पूर्ण

/* 64-bit EM_MIPS has weird ELF64_Rela.r_info.
 * http://techpubs.sgi.com/library/manuals/4000/007-4658-001/pdf/007-4658-001.pdf
 * We पूर्णांकerpret Table 29 Relocation Operation (Elf64_Rel, Elf64_Rela) [p.40]
 * to imply the order of the members; the spec करोes not say so.
 *	प्रकार अचिन्हित अक्षर Elf64_Byte;
 * fails on MIPS64 because their <elf.h> alपढ़ोy has it!
 */

प्रकार uपूर्णांक8_t myElf64_Byte;		/* Type क्रम a 8-bit quantity.  */

जोड़ mips_r_info अणु
	Elf64_Xword r_info;
	काष्ठा अणु
		Elf64_Word r_sym;		/* Symbol index.  */
		myElf64_Byte r_ssym;		/* Special symbol.  */
		myElf64_Byte r_type3;		/* Third relocation.  */
		myElf64_Byte r_type2;		/* Second relocation.  */
		myElf64_Byte r_type;		/* First relocation.  */
	पूर्ण r_mips;
पूर्ण;

अटल uपूर्णांक64_t MIPS64_r_sym(Elf64_Rel स्थिर *rp)
अणु
	वापस w(((जोड़ mips_r_info)अणु .r_info = rp->r_info पूर्ण).r_mips.r_sym);
पूर्ण

अटल व्योम MIPS64_r_info(Elf64_Rel *स्थिर rp, अचिन्हित sym, अचिन्हित type)
अणु
	rp->r_info = ((जोड़ mips_r_info)अणु
		.r_mips = अणु .r_sym = w(sym), .r_type = type पूर्ण
	पूर्ण).r_info;
पूर्ण

अटल पूर्णांक करो_file(अक्षर स्थिर *स्थिर fname)
अणु
	अचिन्हित पूर्णांक reltype = 0;
	Elf32_Ehdr *ehdr;
	पूर्णांक rc = -1;

	ehdr = mmap_file(fname);
	अगर (!ehdr)
		जाओ out;

	w = w4nat;
	w2 = w2nat;
	w8 = w8nat;
	चयन (ehdr->e_ident[EI_DATA]) अणु
		अटल अचिन्हित पूर्णांक स्थिर endian = 1;
	शेष:
		ख_लिखो(मानक_त्रुटि, "unrecognized ELF data encoding %d: %s\n",
			ehdr->e_ident[EI_DATA], fname);
		जाओ out;
	हाल ELFDATA2LSB:
		अगर (*(अचिन्हित अक्षर स्थिर *)&endian != 1) अणु
			/* मुख्य() is big endian, file.o is little endian. */
			w = w4rev;
			w2 = w2rev;
			w8 = w8rev;
		पूर्ण
		ideal_nop4_arm = ideal_nop4_arm_le;
		bl_mcount_arm = bl_mcount_arm_le;
		push_arm = push_arm_le;
		ideal_nop2_thumb = ideal_nop2_thumb_le;
		push_bl_mcount_thumb = push_bl_mcount_thumb_le;
		अवरोध;
	हाल ELFDATA2MSB:
		अगर (*(अचिन्हित अक्षर स्थिर *)&endian != 0) अणु
			/* मुख्य() is little endian, file.o is big endian. */
			w = w4rev;
			w2 = w2rev;
			w8 = w8rev;
		पूर्ण
		ideal_nop4_arm = ideal_nop4_arm_be;
		bl_mcount_arm = bl_mcount_arm_be;
		push_arm = push_arm_be;
		ideal_nop2_thumb = ideal_nop2_thumb_be;
		push_bl_mcount_thumb = push_bl_mcount_thumb_be;
		अवरोध;
	पूर्ण  /* end चयन */
	अगर (स_भेद(ELFMAG, ehdr->e_ident, SELFMAG) != 0 ||
	    w2(ehdr->e_type) != ET_REL ||
	    ehdr->e_ident[EI_VERSION] != EV_CURRENT) अणु
		ख_लिखो(मानक_त्रुटि, "unrecognized ET_REL file %s\n", fname);
		जाओ out;
	पूर्ण

	gpfx = '_';
	चयन (w2(ehdr->e_machine)) अणु
	शेष:
		ख_लिखो(मानक_त्रुटि, "unrecognized e_machine %u %s\n",
			w2(ehdr->e_machine), fname);
		जाओ out;
	हाल EM_386:
		reltype = R_386_32;
		rel_type_nop = R_386_NONE;
		make_nop = make_nop_x86;
		ideal_nop = ideal_nop5_x86_32;
		mcount_adjust_32 = -1;
		gpfx = 0;
		अवरोध;
	हाल EM_ARM:
		reltype = R_ARM_ABS32;
		alपंचांगcount = "__gnu_mcount_nc";
		make_nop = make_nop_arm;
		rel_type_nop = R_ARM_NONE;
		is_fake_mcount32 = arm_is_fake_mcount;
		gpfx = 0;
		अवरोध;
	हाल EM_AARCH64:
		reltype = R_AARCH64_ABS64;
		make_nop = make_nop_arm64;
		rel_type_nop = R_AARCH64_NONE;
		ideal_nop = ideal_nop4_arm64;
		is_fake_mcount64 = arm64_is_fake_mcount;
		अवरोध;
	हाल EM_IA_64:	reltype = R_IA64_IMM64; अवरोध;
	हाल EM_MIPS:	/* reltype: e_class    */ अवरोध;
	हाल EM_PPC:	reltype = R_PPC_ADDR32; अवरोध;
	हाल EM_PPC64:	reltype = R_PPC64_ADDR64; अवरोध;
	हाल EM_S390:	/* reltype: e_class    */ अवरोध;
	हाल EM_SH:	reltype = R_SH_सूची32; gpfx = 0; अवरोध;
	हाल EM_SPARCV9: reltype = R_SPARC_64; अवरोध;
	हाल EM_X86_64:
		make_nop = make_nop_x86;
		ideal_nop = ideal_nop5_x86_64;
		reltype = R_X86_64_64;
		rel_type_nop = R_X86_64_NONE;
		mcount_adjust_64 = -1;
		gpfx = 0;
		अवरोध;
	पूर्ण  /* end चयन */

	चयन (ehdr->e_ident[EI_CLASS]) अणु
	शेष:
		ख_लिखो(मानक_त्रुटि, "unrecognized ELF class %d %s\n",
			ehdr->e_ident[EI_CLASS], fname);
		जाओ out;
	हाल ELFCLASS32:
		अगर (w2(ehdr->e_ehsize) != माप(Elf32_Ehdr)
		||  w2(ehdr->e_shentsize) != माप(Elf32_Shdr)) अणु
			ख_लिखो(मानक_त्रुटि,
				"unrecognized ET_REL file: %s\n", fname);
			जाओ out;
		पूर्ण
		अगर (w2(ehdr->e_machine) == EM_MIPS) अणु
			reltype = R_MIPS_32;
			is_fake_mcount32 = MIPS32_is_fake_mcount;
		पूर्ण
		अगर (करो32(ehdr, fname, reltype) < 0)
			जाओ out;
		अवरोध;
	हाल ELFCLASS64: अणु
		Elf64_Ehdr *स्थिर ghdr = (Elf64_Ehdr *)ehdr;
		अगर (w2(ghdr->e_ehsize) != माप(Elf64_Ehdr)
		||  w2(ghdr->e_shentsize) != माप(Elf64_Shdr)) अणु
			ख_लिखो(मानक_त्रुटि,
				"unrecognized ET_REL file: %s\n", fname);
			जाओ out;
		पूर्ण
		अगर (w2(ghdr->e_machine) == EM_S390) अणु
			reltype = R_390_64;
			mcount_adjust_64 = -14;
		पूर्ण
		अगर (w2(ghdr->e_machine) == EM_MIPS) अणु
			reltype = R_MIPS_64;
			Elf64_r_sym = MIPS64_r_sym;
			Elf64_r_info = MIPS64_r_info;
			is_fake_mcount64 = MIPS64_is_fake_mcount;
		पूर्ण
		अगर (करो64(ghdr, fname, reltype) < 0)
			जाओ out;
		अवरोध;
	पूर्ण
	पूर्ण  /* end चयन */

	rc = ग_लिखो_file(fname);
out:
	file_append_cleanup();
	mmap_cleanup();
	वापस rc;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	स्थिर अक्षर ftrace[] = "/ftrace.o";
	पूर्णांक ftrace_size = माप(ftrace) - 1;
	पूर्णांक n_error = 0;  /* gcc-4.3.0 false positive complaपूर्णांक */
	पूर्णांक c;
	पूर्णांक i;

	जबतक ((c = getopt(argc, argv, "w")) >= 0) अणु
		चयन (c) अणु
		हाल 'w':
			warn_on_notrace_sect = 1;
			अवरोध;
		शेष:
			ख_लिखो(मानक_त्रुटि, "usage: recordmcount [-w] file.o...\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर ((argc - optind) < 1) अणु
		ख_लिखो(मानक_त्रुटि, "usage: recordmcount [-w] file.o...\n");
		वापस 0;
	पूर्ण

	/* Process each file in turn, allowing deep failure. */
	क्रम (i = optind; i < argc; i++) अणु
		अक्षर *file = argv[i];
		पूर्णांक len;

		/*
		 * The file kernel/trace/ftrace.o references the mcount
		 * function but करोes not call it. Since ftrace.o should
		 * not be traced anyway, we just skip it.
		 */
		len = म_माप(file);
		अगर (len >= ftrace_size &&
		    म_भेद(file + (len - ftrace_size), ftrace) == 0)
			जारी;

		अगर (करो_file(file)) अणु
			ख_लिखो(मानक_त्रुटि, "%s: failed\n", file);
			++n_error;
		पूर्ण
	पूर्ण
	वापस !!n_error;
पूर्ण
