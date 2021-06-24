<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Program to hack in a PT_NOTE program header entry in an ELF file.
 * This is needed क्रम OF on RS/6000s to load an image correctly.
 * Note that OF needs a program header entry क्रम the note, not an
 * ELF section.
 *
 * Copyright 2000 Paul Mackerras.
 *
 * Adapted क्रम 64 bit little endian images by Andrew Tauferner.
 *
 * Usage: addnote zImage
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <माला.स>

/* CHRP note section */
अटल स्थिर अक्षर arch[] = "PowerPC";

#घोषणा N_DESCR	6
अचिन्हित पूर्णांक descr[N_DESCR] = अणु
	0xffffffff,		/* real-mode = true */
	0x02000000,		/* real-base, i.e. where we expect OF to be */
	0xffffffff,		/* real-size */
	0xffffffff,		/* virt-base */
	0xffffffff,		/* virt-size */
	0x4000,			/* load-base */
पूर्ण;

/* RPA note section */
अटल स्थिर अक्षर rpaname[] = "IBM,RPA-Client-Config";

/*
 * Note: setting ignore_my_client_config *should* mean that OF ignores
 * all the other fields, but there is a firmware bug which means that
 * it looks at the splpar field at least.  So these values need to be
 * reasonable.
 */
#घोषणा N_RPA_DESCR	8
अचिन्हित पूर्णांक rpanote[N_RPA_DESCR] = अणु
	0,			/* lparaffinity */
	64,			/* min_rmo_size */
	0,			/* min_rmo_percent */
	40,			/* max_pft_size */
	1,			/* splpar */
	-1,			/* min_load */
	0,			/* new_mem_def */
	1,			/* ignore_my_client_config */
पूर्ण;

#घोषणा ROUNDUP(len)	(((len) + 3) & ~3)

अचिन्हित अक्षर buf[1024];
#घोषणा ELFDATA2LSB     1
#घोषणा ELFDATA2MSB     2
अटल पूर्णांक e_data = ELFDATA2MSB;
#घोषणा ELFCLASS32      1
#घोषणा ELFCLASS64      2
अटल पूर्णांक e_class = ELFCLASS32;

#घोषणा GET_16BE(off)	((buf[off] << 8) + (buf[(off)+1]))
#घोषणा GET_32BE(off)	((GET_16BE(off) << 16U) + GET_16BE((off)+2U))
#घोषणा GET_64BE(off)	((((अचिन्हित दीर्घ दीर्घ)GET_32BE(off)) << 32ULL) + \
			((अचिन्हित दीर्घ दीर्घ)GET_32BE((off)+4ULL)))
#घोषणा PUT_16BE(off, v)(buf[off] = ((v) >> 8) & 0xff, \
			 buf[(off) + 1] = (v) & 0xff)
#घोषणा PUT_32BE(off, v)(PUT_16BE((off), (v) >> 16L), PUT_16BE((off) + 2, (v)))
#घोषणा PUT_64BE(off, v)((PUT_32BE((off), (v) >> 32L), \
			  PUT_32BE((off) + 4, (v))))

#घोषणा GET_16LE(off)	((buf[off]) + (buf[(off)+1] << 8))
#घोषणा GET_32LE(off)	(GET_16LE(off) + (GET_16LE((off)+2U) << 16U))
#घोषणा GET_64LE(off)	((अचिन्हित दीर्घ दीर्घ)GET_32LE(off) + \
			(((अचिन्हित दीर्घ दीर्घ)GET_32LE((off)+4ULL)) << 32ULL))
#घोषणा PUT_16LE(off, v) (buf[off] = (v) & 0xff, \
			  buf[(off) + 1] = ((v) >> 8) & 0xff)
#घोषणा PUT_32LE(off, v) (PUT_16LE((off), (v)), PUT_16LE((off) + 2, (v) >> 16L))
#घोषणा PUT_64LE(off, v) (PUT_32LE((off), (v)), PUT_32LE((off) + 4, (v) >> 32L))

#घोषणा GET_16(off)	(e_data == ELFDATA2MSB ? GET_16BE(off) : GET_16LE(off))
#घोषणा GET_32(off)	(e_data == ELFDATA2MSB ? GET_32BE(off) : GET_32LE(off))
#घोषणा GET_64(off)	(e_data == ELFDATA2MSB ? GET_64BE(off) : GET_64LE(off))
#घोषणा PUT_16(off, v)	(e_data == ELFDATA2MSB ? PUT_16BE(off, v) : \
			 PUT_16LE(off, v))
#घोषणा PUT_32(off, v)  (e_data == ELFDATA2MSB ? PUT_32BE(off, v) : \
			 PUT_32LE(off, v))
#घोषणा PUT_64(off, v)  (e_data == ELFDATA2MSB ? PUT_64BE(off, v) : \
			 PUT_64LE(off, v))

/* Structure of an ELF file */
#घोषणा E_IDENT		0	/* ELF header */
#घोषणा	E_PHOFF		(e_class == ELFCLASS32 ? 28 : 32)
#घोषणा E_PHENTSIZE	(e_class == ELFCLASS32 ? 42 : 54)
#घोषणा E_PHNUM		(e_class == ELFCLASS32 ? 44 : 56)
#घोषणा E_HSIZE		(e_class == ELFCLASS32 ? 52 : 64)

#घोषणा EI_MAGIC	0	/* offsets in E_IDENT area */
#घोषणा EI_CLASS	4
#घोषणा EI_DATA		5

#घोषणा PH_TYPE		0	/* ELF program header */
#घोषणा PH_OFFSET	(e_class == ELFCLASS32 ? 4 : 8)
#घोषणा PH_खाताSZ	(e_class == ELFCLASS32 ? 16 : 32)
#घोषणा PH_HSIZE	(e_class == ELFCLASS32 ? 32 : 56)

#घोषणा PT_NOTE		4	/* Program header type = note */


अचिन्हित अक्षर elf_magic[4] = अणु 0x7f, 'E', 'L', 'F' पूर्ण;

पूर्णांक
मुख्य(पूर्णांक ac, अक्षर **av)
अणु
	पूर्णांक fd, n, i;
	अचिन्हित दीर्घ ph, ps, np;
	दीर्घ nnote, nnote2, ns;

	अगर (ac != 2) अणु
		ख_लिखो(मानक_त्रुटि, "Usage: %s elf-file\n", av[0]);
		निकास(1);
	पूर्ण
	fd = खोलो(av[1], O_RDWR);
	अगर (fd < 0) अणु
		लिखो_त्रुटि(av[1]);
		निकास(1);
	पूर्ण

	nnote = 12 + ROUNDUP(म_माप(arch) + 1) + माप(descr);
	nnote2 = 12 + ROUNDUP(म_माप(rpaname) + 1) + माप(rpanote);

	n = पढ़ो(fd, buf, माप(buf));
	अगर (n < 0) अणु
		लिखो_त्रुटि("read");
		निकास(1);
	पूर्ण

	अगर (स_भेद(&buf[E_IDENT+EI_MAGIC], elf_magic, 4) != 0)
		जाओ notelf;
	e_class = buf[E_IDENT+EI_CLASS];
	अगर (e_class != ELFCLASS32 && e_class != ELFCLASS64)
		जाओ notelf;
	e_data = buf[E_IDENT+EI_DATA];
	अगर (e_data != ELFDATA2MSB && e_data != ELFDATA2LSB)
		जाओ notelf;
	अगर (n < E_HSIZE)
		जाओ notelf;

	ph = (e_class == ELFCLASS32 ? GET_32(E_PHOFF) : GET_64(E_PHOFF));
	ps = GET_16(E_PHENTSIZE);
	np = GET_16(E_PHNUM);
	अगर (ph < E_HSIZE || ps < PH_HSIZE || np < 1)
		जाओ notelf;
	अगर (ph + (np + 2) * ps + nnote + nnote2 > n)
		जाओ nospace;

	क्रम (i = 0; i < np; ++i) अणु
		अगर (GET_32(ph + PH_TYPE) == PT_NOTE) अणु
			ख_लिखो(मानक_त्रुटि, "%s already has a note entry\n",
				av[1]);
			निकास(0);
		पूर्ण
		ph += ps;
	पूर्ण

	/* XXX check that the area we want to use is all zeroes */
	क्रम (i = 0; i < 2 * ps + nnote + nnote2; ++i)
		अगर (buf[ph + i] != 0)
			जाओ nospace;

	/* fill in the program header entry */
	ns = ph + 2 * ps;
	PUT_32(ph + PH_TYPE, PT_NOTE);
	अगर (e_class == ELFCLASS32)
		PUT_32(ph + PH_OFFSET, ns);
	अन्यथा
		PUT_64(ph + PH_OFFSET, ns);

	अगर (e_class == ELFCLASS32)
		PUT_32(ph + PH_खाताSZ, nnote);
	अन्यथा
		PUT_64(ph + PH_खाताSZ, nnote);

	/* fill in the note area we poपूर्णांक to */
	/* XXX we should probably make this a proper section */
	PUT_32(ns, म_माप(arch) + 1);
	PUT_32(ns + 4, N_DESCR * 4);
	PUT_32(ns + 8, 0x1275);
	म_नकल((अक्षर *) &buf[ns + 12], arch);
	ns += 12 + म_माप(arch) + 1;
	क्रम (i = 0; i < N_DESCR; ++i, ns += 4)
		PUT_32BE(ns, descr[i]);

	/* fill in the second program header entry and the RPA note area */
	ph += ps;
	PUT_32(ph + PH_TYPE, PT_NOTE);
	अगर (e_class == ELFCLASS32)
		PUT_32(ph + PH_OFFSET, ns);
	अन्यथा
		PUT_64(ph + PH_OFFSET, ns);

	अगर (e_class == ELFCLASS32)
		PUT_32(ph + PH_खाताSZ, nnote);
	अन्यथा
		PUT_64(ph + PH_खाताSZ, nnote2);

	/* fill in the note area we poपूर्णांक to */
	PUT_32(ns, म_माप(rpaname) + 1);
	PUT_32(ns + 4, माप(rpanote));
	PUT_32(ns + 8, 0x12759999);
	म_नकल((अक्षर *) &buf[ns + 12], rpaname);
	ns += 12 + ROUNDUP(म_माप(rpaname) + 1);
	क्रम (i = 0; i < N_RPA_DESCR; ++i, ns += 4)
		PUT_32BE(ns, rpanote[i]);

	/* Update the number of program headers */
	PUT_16(E_PHNUM, np + 2);

	/* ग_लिखो back */
	i = lseek(fd, (दीर्घ) 0, शुरू_से);
	अगर (i < 0) अणु
		लिखो_त्रुटि("lseek");
		निकास(1);
	पूर्ण
	i = ग_लिखो(fd, buf, n);
	अगर (i < 0) अणु
		लिखो_त्रुटि("write");
		निकास(1);
	पूर्ण
	अगर (i < n) अणु
		ख_लिखो(मानक_त्रुटि, "%s: write truncated\n", av[1]);
		निकास(1);
	पूर्ण

	निकास(0);

 notelf:
	ख_लिखो(मानक_त्रुटि, "%s does not appear to be an ELF file\n", av[1]);
	निकास(1);

 nospace:
	ख_लिखो(मानक_त्रुटि, "sorry, I can't find space in %s to put the note\n",
		av[1]);
	निकास(1);
पूर्ण
