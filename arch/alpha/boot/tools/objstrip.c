<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/alpha/boot/tools/objstrip.c
 *
 * Strip the object file headers/trailers from an executable (ELF or ECOFF).
 *
 * Copyright (C) 1996 David Mosberger-Tang.
 */
/*
 * Converts an ECOFF or ELF object file पूर्णांकo a bootable file.  The
 * object file must be a OMAGIC file (i.e., data and bss follow immediately
 * behind the text).  See DEC "Assembly Language Programmer's Guide"
 * करोcumentation क्रम details.  The SRM boot process is करोcumented in
 * the Alpha AXP Architecture Reference Manual, Second Edition by
 * Riअक्षरd L. Sites and Riअक्षरd T. Witek.
 */
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#समावेश <sys/fcntl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>

#समावेश <linux/a.out.h>
#समावेश <linux/coff.h>
#समावेश <linux/param.h>
#अगर_घोषित __ELF__
# include <linux/elf.h>
# define elfhdr elf64_hdr
# define elf_phdr elf64_phdr
# define elf_check_arch(x) ((x)->e_machine == EM_ALPHA)
#पूर्ण_अगर

/* bootfile size must be multiple of BLOCK_SIZE: */
#घोषणा BLOCK_SIZE	512

स्थिर अक्षर * prog_name;


अटल व्योम
usage (व्योम)
अणु
    ख_लिखो(मानक_त्रुटि,
	    "usage: %s [-v] -p file primary\n"
	    "       %s [-vb] file [secondary]\n", prog_name, prog_name);
    निकास(1);
पूर्ण


पूर्णांक
मुख्य (पूर्णांक argc, अक्षर *argv[])
अणु
    माप_प्रकार nwritten, tocopy, n, mem_size, fil_size, pad = 0;
    पूर्णांक fd, ofd, i, j, verbose = 0, primary = 0;
    अक्षर buf[8192], *inname;
    काष्ठा exec * aout;		/* includes file & aout header */
    दीर्घ offset;
#अगर_घोषित __ELF__
    काष्ठा elfhdr *elf;
    काष्ठा elf_phdr *elf_phdr;	/* program header */
    अचिन्हित दीर्घ दीर्घ e_entry;
#पूर्ण_अगर

    prog_name = argv[0];

    क्रम (i = 1; i < argc && argv[i][0] == '-'; ++i) अणु
	क्रम (j = 1; argv[i][j]; ++j) अणु
	    चयन (argv[i][j]) अणु
	      हाल 'v':
		  verbose = ~verbose;
		  अवरोध;

	      हाल 'b':
		  pad = BLOCK_SIZE;
		  अवरोध;

	      हाल 'p':
		  primary = 1;		/* make primary bootblock */
		  अवरोध;
	    पूर्ण
	पूर्ण
    पूर्ण

    अगर (i >= argc) अणु
	usage();
    पूर्ण
    inname = argv[i++];

    fd = खोलो(inname, O_RDONLY);
    अगर (fd == -1) अणु
	लिखो_त्रुटि("open");
	निकास(1);
    पूर्ण

    ofd = 1;
    अगर (i < argc) अणु
	ofd = खोलो(argv[i++], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	अगर (ofd == -1) अणु
	    लिखो_त्रुटि("open");
	    निकास(1);
	पूर्ण
    पूर्ण

    अगर (primary) अणु
	/* generate bootblock क्रम primary loader */
	
	अचिन्हित दीर्घ bb[64], sum = 0;
	काष्ठा stat st;
	off_t size;
	पूर्णांक i;

	अगर (ofd == 1) अणु
	    usage();
	पूर्ण

	अगर (ख_स्थिति(fd, &st) == -1) अणु
	    लिखो_त्रुटि("fstat");
	    निकास(1);
	पूर्ण

	size = (st.st_size + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1);
	स_रखो(bb, 0, माप(bb));
	म_नकल((अक्षर *) bb, "Linux SRM bootblock");
	bb[60] = size / BLOCK_SIZE;	/* count */
	bb[61] = 1;			/* starting sector # */
	bb[62] = 0;			/* flags---must be 0 */
	क्रम (i = 0; i < 63; ++i) अणु
	    sum += bb[i];
	पूर्ण
	bb[63] = sum;
	अगर (ग_लिखो(ofd, bb, माप(bb)) != माप(bb)) अणु
	    लिखो_त्रुटि("boot-block write");
	    निकास(1);
	पूर्ण
	म_लिखो("%lu\n", size);
	वापस 0;
    पूर्ण

    /* पढ़ो and inspect exec header: */

    अगर (पढ़ो(fd, buf, माप(buf)) < 0) अणु
	लिखो_त्रुटि("read");
	निकास(1);
    पूर्ण

#अगर_घोषित __ELF__
    elf = (काष्ठा elfhdr *) buf;

    अगर (elf->e_ident[0] == 0x7f && str_has_prefix((अक्षर *)elf->e_ident + 1, "ELF")) अणु
	अगर (elf->e_type != ET_EXEC) अणु
	    ख_लिखो(मानक_त्रुटि, "%s: %s is not an ELF executable\n",
		    prog_name, inname);
	    निकास(1);
	पूर्ण
	अगर (!elf_check_arch(elf)) अणु
	    ख_लिखो(मानक_त्रुटि, "%s: is not for this processor (e_machine=%d)\n",
		    prog_name, elf->e_machine);
	    निकास(1);
	पूर्ण
	अगर (elf->e_phnum != 1) अणु
	    ख_लिखो(मानक_त्रुटि,
		    "%s: %d program headers (forgot to link with -N?)\n",
		    prog_name, elf->e_phnum);
	पूर्ण

	e_entry = elf->e_entry;

	lseek(fd, elf->e_phoff, शुरू_से);
	अगर (पढ़ो(fd, buf, माप(*elf_phdr)) != माप(*elf_phdr)) अणु
	    लिखो_त्रुटि("read");
	    निकास(1);
	पूर्ण

	elf_phdr = (काष्ठा elf_phdr *) buf;
	offset	 = elf_phdr->p_offset;
	mem_size = elf_phdr->p_memsz;
	fil_size = elf_phdr->p_filesz;

	/* work around ELF bug: */
	अगर (elf_phdr->p_vaddr < e_entry) अणु
	    अचिन्हित दीर्घ delta = e_entry - elf_phdr->p_vaddr;
	    offset   += delta;
	    mem_size -= delta;
	    fil_size -= delta;
	    elf_phdr->p_vaddr += delta;
	पूर्ण

	अगर (verbose) अणु
	    ख_लिखो(मानक_त्रुटि, "%s: extracting %#016lx-%#016lx (at %lx)\n",
		    prog_name, (दीर्घ) elf_phdr->p_vaddr,
		    elf_phdr->p_vaddr + fil_size, offset);
	पूर्ण
    पूर्ण अन्यथा
#पूर्ण_अगर
    अणु
	aout = (काष्ठा exec *) buf;

	अगर (!(aout->fh.f_flags & COFF_F_EXEC)) अणु
	    ख_लिखो(मानक_त्रुटि, "%s: %s is not in executable format\n",
		    prog_name, inname);
	    निकास(1);
	पूर्ण

	अगर (aout->fh.f_opthdr != माप(aout->ah)) अणु
	    ख_लिखो(मानक_त्रुटि, "%s: %s has unexpected optional header size\n",
		    prog_name, inname);
	    निकास(1);
	पूर्ण

	अगर (N_MAGIC(*aout) != OMAGIC) अणु
	    ख_लिखो(मानक_त्रुटि, "%s: %s is not an OMAGIC file\n",
		    prog_name, inname);
	    निकास(1);
	पूर्ण
	offset = N_TXTOFF(*aout);
	fil_size = aout->ah.tsize + aout->ah.dsize;
	mem_size = fil_size + aout->ah.bsize;

	अगर (verbose) अणु
	    ख_लिखो(मानक_त्रुटि, "%s: extracting %#016lx-%#016lx (at %lx)\n",
		    prog_name, aout->ah.text_start,
		    aout->ah.text_start + fil_size, offset);
	पूर्ण
    पूर्ण

    अगर (lseek(fd, offset, शुरू_से) != offset) अणु
	लिखो_त्रुटि("lseek");
	निकास(1);
    पूर्ण

    अगर (verbose) अणु
	ख_लिखो(मानक_त्रुटि, "%s: copying %lu byte from %s\n",
		prog_name, (अचिन्हित दीर्घ) fil_size, inname);
    पूर्ण

    tocopy = fil_size;
    जबतक (tocopy > 0) अणु
	n = tocopy;
	अगर (n > माप(buf)) अणु
	    n = माप(buf);
	पूर्ण
	tocopy -= n;
	अगर ((माप_प्रकार) पढ़ो(fd, buf, n) != n) अणु
	    लिखो_त्रुटि("read");
	    निकास(1);
	पूर्ण
	करो अणु
	    nwritten = ग_लिखो(ofd, buf, n);
	    अगर ((sमाप_प्रकार) nwritten == -1) अणु
		लिखो_त्रुटि("write");
		निकास(1);
	    पूर्ण
	    n -= nwritten;
	पूर्ण जबतक (n > 0);
    पूर्ण

    अगर (pad) अणु
	mem_size = ((mem_size + pad - 1) / pad) * pad;
    पूर्ण

    tocopy = mem_size - fil_size;
    अगर (tocopy > 0) अणु
	ख_लिखो(मानक_त्रुटि,
		"%s: zero-filling bss and aligning to %lu with %lu bytes\n",
		prog_name, pad, (अचिन्हित दीर्घ) tocopy);

	स_रखो(buf, 0x00, माप(buf));
	करो अणु
	    n = tocopy;
	    अगर (n > माप(buf)) अणु
		n = माप(buf);
	    पूर्ण
	    nwritten = ग_लिखो(ofd, buf, n);
	    अगर ((sमाप_प्रकार) nwritten == -1) अणु
		लिखो_त्रुटि("write");
		निकास(1);
	    पूर्ण
	    tocopy -= nwritten;
	पूर्ण जबतक (tocopy > 0);
    पूर्ण
    वापस 0;
पूर्ण
