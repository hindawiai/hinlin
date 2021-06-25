<शैली गुरु>
/*
 * Copyright (c) 1995
 *	Ted Lemon (hereinafter referred to as the author)
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* elf2ecoff.c

   This program converts an elf executable to an ECOFF executable.
   No symbol table is retained.	  This is useful primarily in building
   net-bootable kernels क्रम machines (e.g., DECstation and Alpha) which
   only support the ECOFF object file क्रमmat. */

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <elf.h>
#समावेश <सीमा.स>
#समावेश <netinet/in.h>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <पूर्णांकtypes.h>

#समावेश "ecoff.h"

/*
 * Some extra ELF definitions
 */
#घोषणा PT_MIPS_REGINFO 	0x70000000	/* Register usage inक्रमmation */
#घोषणा PT_MIPS_ABIFLAGS	0x70000003	/* Records ABI related flags  */

/* -------------------------------------------------------------------- */

काष्ठा sect अणु
	uपूर्णांक32_t vaddr;
	uपूर्णांक32_t len;
पूर्ण;

पूर्णांक *symTypeTable;
पूर्णांक must_convert_endian;
पूर्णांक क्रमmat_bigendian;

अटल व्योम copy(पूर्णांक out, पूर्णांक in, off_t offset, off_t size)
अणु
	अक्षर ibuf[4096];
	पूर्णांक reमुख्यing, cur, count;

	/* Go to the start of the ELF symbol table... */
	अगर (lseek(in, offset, शुरू_से) < 0) अणु
		लिखो_त्रुटि("copy: lseek");
		निकास(1);
	पूर्ण

	reमुख्यing = size;
	जबतक (reमुख्यing) अणु
		cur = reमुख्यing;
		अगर (cur > माप ibuf)
			cur = माप ibuf;
		reमुख्यing -= cur;
		अगर ((count = पढ़ो(in, ibuf, cur)) != cur) अणु
			ख_लिखो(मानक_त्रुटि, "copy: read: %s\n",
				count ? म_त्रुटि(त्रुटि_सं) :
				"premature end of file");
			निकास(1);
		पूर्ण
		अगर ((count = ग_लिखो(out, ibuf, cur)) != cur) अणु
			लिखो_त्रुटि("copy: write");
			निकास(1);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Combine two segments, which must be contiguous.   If pad is true, it's
 * okay क्रम there to be padding between.
 */
अटल व्योम combine(काष्ठा sect *base, काष्ठा sect *new, पूर्णांक pad)
अणु
	अगर (!base->len)
		*base = *new;
	अन्यथा अगर (new->len) अणु
		अगर (base->vaddr + base->len != new->vaddr) अणु
			अगर (pad)
				base->len = new->vaddr - base->vaddr;
			अन्यथा अणु
				ख_लिखो(मानक_त्रुटि,
					"Non-contiguous data can't be converted.\n");
				निकास(1);
			पूर्ण
		पूर्ण
		base->len += new->len;
	पूर्ण
पूर्ण

अटल पूर्णांक phcmp(स्थिर व्योम *v1, स्थिर व्योम *v2)
अणु
	स्थिर Elf32_Phdr *h1 = v1;
	स्थिर Elf32_Phdr *h2 = v2;

	अगर (h1->p_vaddr > h2->p_vaddr)
		वापस 1;
	अन्यथा अगर (h1->p_vaddr < h2->p_vaddr)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

अटल अक्षर *saveRead(पूर्णांक file, off_t offset, off_t len, अक्षर *name)
अणु
	अक्षर *पंचांगp;
	पूर्णांक count;
	off_t off;
	अगर ((off = lseek(file, offset, शुरू_से)) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: fseek: %s\n", name, म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण
	अगर (!(पंचांगp = (अक्षर *) दो_स्मृति(len))) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Can't allocate %ld bytes.\n", name,
			len);
		निकास(1);
	पूर्ण
	count = पढ़ो(file, पंचांगp, len);
	अगर (count != len) अणु
		ख_लिखो(मानक_त्रुटि, "%s: read: %s.\n",
			name,
			count ? म_त्रुटि(त्रुटि_सं) : "End of file reached");
		निकास(1);
	पूर्ण
	वापस पंचांगp;
पूर्ण

#घोषणा swab16(x) \
	((uपूर्णांक16_t)( \
		(((uपूर्णांक16_t)(x) & (uपूर्णांक16_t)0x00ffU) << 8) | \
		(((uपूर्णांक16_t)(x) & (uपूर्णांक16_t)0xff00U) >> 8) ))

#घोषणा swab32(x) \
	((अचिन्हित पूर्णांक)( \
		(((uपूर्णांक32_t)(x) & (uपूर्णांक32_t)0x000000ffUL) << 24) | \
		(((uपूर्णांक32_t)(x) & (uपूर्णांक32_t)0x0000ff00UL) <<  8) | \
		(((uपूर्णांक32_t)(x) & (uपूर्णांक32_t)0x00ff0000UL) >>  8) | \
		(((uपूर्णांक32_t)(x) & (uपूर्णांक32_t)0xff000000UL) >> 24) ))

अटल व्योम convert_elf_hdr(Elf32_Ehdr * e)
अणु
	e->e_type = swab16(e->e_type);
	e->e_machine = swab16(e->e_machine);
	e->e_version = swab32(e->e_version);
	e->e_entry = swab32(e->e_entry);
	e->e_phoff = swab32(e->e_phoff);
	e->e_shoff = swab32(e->e_shoff);
	e->e_flags = swab32(e->e_flags);
	e->e_ehsize = swab16(e->e_ehsize);
	e->e_phentsize = swab16(e->e_phentsize);
	e->e_phnum = swab16(e->e_phnum);
	e->e_shentsize = swab16(e->e_shentsize);
	e->e_shnum = swab16(e->e_shnum);
	e->e_shstrndx = swab16(e->e_shstrndx);
पूर्ण

अटल व्योम convert_elf_phdrs(Elf32_Phdr * p, पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++, p++) अणु
		p->p_type = swab32(p->p_type);
		p->p_offset = swab32(p->p_offset);
		p->p_vaddr = swab32(p->p_vaddr);
		p->p_paddr = swab32(p->p_paddr);
		p->p_filesz = swab32(p->p_filesz);
		p->p_memsz = swab32(p->p_memsz);
		p->p_flags = swab32(p->p_flags);
		p->p_align = swab32(p->p_align);
	पूर्ण

पूर्ण

अटल व्योम convert_elf_shdrs(Elf32_Shdr * s, पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++, s++) अणु
		s->sh_name = swab32(s->sh_name);
		s->sh_type = swab32(s->sh_type);
		s->sh_flags = swab32(s->sh_flags);
		s->sh_addr = swab32(s->sh_addr);
		s->sh_offset = swab32(s->sh_offset);
		s->sh_size = swab32(s->sh_size);
		s->sh_link = swab32(s->sh_link);
		s->sh_info = swab32(s->sh_info);
		s->sh_addralign = swab32(s->sh_addralign);
		s->sh_entsize = swab32(s->sh_entsize);
	पूर्ण
पूर्ण

अटल व्योम convert_ecoff_filehdr(काष्ठा filehdr *f)
अणु
	f->f_magic = swab16(f->f_magic);
	f->f_nscns = swab16(f->f_nscns);
	f->f_timdat = swab32(f->f_timdat);
	f->f_symptr = swab32(f->f_symptr);
	f->f_nsyms = swab32(f->f_nsyms);
	f->f_opthdr = swab16(f->f_opthdr);
	f->f_flags = swab16(f->f_flags);
पूर्ण

अटल व्योम convert_ecoff_aouthdr(काष्ठा aouthdr *a)
अणु
	a->magic = swab16(a->magic);
	a->vstamp = swab16(a->vstamp);
	a->tsize = swab32(a->tsize);
	a->dsize = swab32(a->dsize);
	a->bsize = swab32(a->bsize);
	a->entry = swab32(a->entry);
	a->text_start = swab32(a->text_start);
	a->data_start = swab32(a->data_start);
	a->bss_start = swab32(a->bss_start);
	a->gprmask = swab32(a->gprmask);
	a->cprmask[0] = swab32(a->cprmask[0]);
	a->cprmask[1] = swab32(a->cprmask[1]);
	a->cprmask[2] = swab32(a->cprmask[2]);
	a->cprmask[3] = swab32(a->cprmask[3]);
	a->gp_value = swab32(a->gp_value);
पूर्ण

अटल व्योम convert_ecoff_esecs(काष्ठा scnhdr *s, पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++, s++) अणु
		s->s_paddr = swab32(s->s_paddr);
		s->s_vaddr = swab32(s->s_vaddr);
		s->s_size = swab32(s->s_size);
		s->s_scnptr = swab32(s->s_scnptr);
		s->s_relptr = swab32(s->s_relptr);
		s->s_lnnoptr = swab32(s->s_lnnoptr);
		s->s_nreloc = swab16(s->s_nreloc);
		s->s_nlnno = swab16(s->s_nlnno);
		s->s_flags = swab32(s->s_flags);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	Elf32_Ehdr ex;
	Elf32_Phdr *ph;
	Elf32_Shdr *sh;
	पूर्णांक i, pad;
	काष्ठा sect text, data, bss;
	काष्ठा filehdr efh;
	काष्ठा aouthdr eah;
	काष्ठा scnhdr esecs[6];
	पूर्णांक infile, outfile;
	uपूर्णांक32_t cur_vma = UINT32_MAX;
	पूर्णांक addflag = 0;
	पूर्णांक nosecs;

	text.len = data.len = bss.len = 0;
	text.vaddr = data.vaddr = bss.vaddr = 0;

	/* Check args... */
	अगर (argc < 3 || argc > 4) अणु
	      usage:
		ख_लिखो(मानक_त्रुटि,
			"usage: elf2ecoff <elf executable> <ecoff executable> [-a]\n");
		निकास(1);
	पूर्ण
	अगर (argc == 4) अणु
		अगर (म_भेद(argv[3], "-a"))
			जाओ usage;
		addflag = 1;
	पूर्ण

	/* Try the input file... */
	अगर ((infile = खोलो(argv[1], O_RDONLY)) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Can't open %s for read: %s\n",
			argv[1], म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	/* Read the header, which is at the beginning of the file... */
	i = पढ़ो(infile, &ex, माप ex);
	अगर (i != माप ex) अणु
		ख_लिखो(मानक_त्रुटि, "ex: %s: %s.\n",
			argv[1],
			i ? म_त्रुटि(त्रुटि_सं) : "End of file reached");
		निकास(1);
	पूर्ण

	अगर (ex.e_ident[EI_DATA] == ELFDATA2MSB)
		क्रमmat_bigendian = 1;

	अगर (ntohs(0xaa55) == 0xaa55) अणु
		अगर (!क्रमmat_bigendian)
			must_convert_endian = 1;
	पूर्ण अन्यथा अणु
		अगर (क्रमmat_bigendian)
			must_convert_endian = 1;
	पूर्ण
	अगर (must_convert_endian)
		convert_elf_hdr(&ex);

	/* Read the program headers... */
	ph = (Elf32_Phdr *) saveRead(infile, ex.e_phoff,
				     ex.e_phnum * माप(Elf32_Phdr),
				     "ph");
	अगर (must_convert_endian)
		convert_elf_phdrs(ph, ex.e_phnum);
	/* Read the section headers... */
	sh = (Elf32_Shdr *) saveRead(infile, ex.e_shoff,
				     ex.e_shnum * माप(Elf32_Shdr),
				     "sh");
	अगर (must_convert_endian)
		convert_elf_shdrs(sh, ex.e_shnum);

	/* Figure out अगर we can cram the program header पूर्णांकo an ECOFF
	   header...  Basically, we can't handle anything but loadable
	   segments, but we can ignore some kinds of segments.	We can't
	   handle holes in the address space.  Segments may be out of order,
	   so we sort them first. */

	क्विक(ph, ex.e_phnum, माप(Elf32_Phdr), phcmp);

	क्रम (i = 0; i < ex.e_phnum; i++) अणु
		/* Section types we can ignore... */
		चयन (ph[i].p_type) अणु
		हाल PT_शून्य:
		हाल PT_NOTE:
		हाल PT_PHDR:
		हाल PT_MIPS_REGINFO:
		हाल PT_MIPS_ABIFLAGS:
			जारी;

		हाल PT_LOAD:
			/* Writable (data) segment? */
			अगर (ph[i].p_flags & PF_W) अणु
				काष्ठा sect ndata, nbss;

				ndata.vaddr = ph[i].p_vaddr;
				ndata.len = ph[i].p_filesz;
				nbss.vaddr = ph[i].p_vaddr + ph[i].p_filesz;
				nbss.len = ph[i].p_memsz - ph[i].p_filesz;

				combine(&data, &ndata, 0);
				combine(&bss, &nbss, 1);
			पूर्ण अन्यथा अणु
				काष्ठा sect ntxt;

				ntxt.vaddr = ph[i].p_vaddr;
				ntxt.len = ph[i].p_filesz;

				combine(&text, &ntxt, 0);
			पूर्ण
			/* Remember the lowest segment start address. */
			अगर (ph[i].p_vaddr < cur_vma)
				cur_vma = ph[i].p_vaddr;
			अवरोध;

		शेष:
			/* Section types we can't handle... */
			ख_लिखो(मानक_त्रुटि,
				"Program header %d type %d can't be converted.\n",
				ex.e_phnum, ph[i].p_type);
			निकास(1);
		पूर्ण
	पूर्ण

	/* Sections must be in order to be converted... */
	अगर (text.vaddr > data.vaddr || data.vaddr > bss.vaddr ||
	    text.vaddr + text.len > data.vaddr
	    || data.vaddr + data.len > bss.vaddr) अणु
		ख_लिखो(मानक_त्रुटि,
			"Sections ordering prevents a.out conversion.\n");
		निकास(1);
	पूर्ण

	/* If there's a data section but no text section, then the loader
	   combined everything पूर्णांकo one section.   That needs to be the
	   text section, so just make the data section zero length following
	   text. */
	अगर (data.len && !text.len) अणु
		text = data;
		data.vaddr = text.vaddr + text.len;
		data.len = 0;
	पूर्ण

	/* If there is a gap between text and data, we'll fill it when we copy
	   the data, so update the length of the text segment as represented in
	   a.out to reflect that, since a.out करोesn't allow gaps in the program
	   address space. */
	अगर (text.vaddr + text.len < data.vaddr)
		text.len = data.vaddr - text.vaddr;

	/* We now have enough inक्रमmation to cons up an a.out header... */
	eah.magic = OMAGIC;
	eah.vstamp = 200;
	eah.tsize = text.len;
	eah.dsize = data.len;
	eah.bsize = bss.len;
	eah.entry = ex.e_entry;
	eah.text_start = text.vaddr;
	eah.data_start = data.vaddr;
	eah.bss_start = bss.vaddr;
	eah.gprmask = 0xf3fffffe;
	स_रखो(&eah.cprmask, '\0', माप eah.cprmask);
	eah.gp_value = 0;	/* unused. */

	अगर (क्रमmat_bigendian)
		efh.f_magic = MIPSEBMAGIC;
	अन्यथा
		efh.f_magic = MIPSELMAGIC;
	अगर (addflag)
		nosecs = 6;
	अन्यथा
		nosecs = 3;
	efh.f_nscns = nosecs;
	efh.f_timdat = 0;	/* bogus */
	efh.f_symptr = 0;
	efh.f_nsyms = 0;
	efh.f_opthdr = माप eah;
	efh.f_flags = 0x100f;	/* Stripped, not sharable. */

	स_रखो(esecs, 0, माप esecs);
	म_नकल(esecs[0].s_name, ".text");
	म_नकल(esecs[1].s_name, ".data");
	म_नकल(esecs[2].s_name, ".bss");
	अगर (addflag) अणु
		म_नकल(esecs[3].s_name, ".rdata");
		म_नकल(esecs[4].s_name, ".sdata");
		म_नकल(esecs[5].s_name, ".sbss");
	पूर्ण
	esecs[0].s_paddr = esecs[0].s_vaddr = eah.text_start;
	esecs[1].s_paddr = esecs[1].s_vaddr = eah.data_start;
	esecs[2].s_paddr = esecs[2].s_vaddr = eah.bss_start;
	अगर (addflag) अणु
		esecs[3].s_paddr = esecs[3].s_vaddr = 0;
		esecs[4].s_paddr = esecs[4].s_vaddr = 0;
		esecs[5].s_paddr = esecs[5].s_vaddr = 0;
	पूर्ण
	esecs[0].s_size = eah.tsize;
	esecs[1].s_size = eah.dsize;
	esecs[2].s_size = eah.bsize;
	अगर (addflag) अणु
		esecs[3].s_size = 0;
		esecs[4].s_size = 0;
		esecs[5].s_size = 0;
	पूर्ण
	esecs[0].s_scnptr = N_TXTOFF(efh, eah);
	esecs[1].s_scnptr = N_DATOFF(efh, eah);
#घोषणा ECOFF_SEGMENT_ALIGNMENT(a) 0x10
#घोषणा ECOFF_ROUND(s, a) (((s)+(a)-1)&~((a)-1))
	esecs[2].s_scnptr = esecs[1].s_scnptr +
	    ECOFF_ROUND(esecs[1].s_size, ECOFF_SEGMENT_ALIGNMENT(&eah));
	अगर (addflag) अणु
		esecs[3].s_scnptr = 0;
		esecs[4].s_scnptr = 0;
		esecs[5].s_scnptr = 0;
	पूर्ण
	esecs[0].s_relptr = esecs[1].s_relptr = esecs[2].s_relptr = 0;
	esecs[0].s_lnnoptr = esecs[1].s_lnnoptr = esecs[2].s_lnnoptr = 0;
	esecs[0].s_nreloc = esecs[1].s_nreloc = esecs[2].s_nreloc = 0;
	esecs[0].s_nlnno = esecs[1].s_nlnno = esecs[2].s_nlnno = 0;
	अगर (addflag) अणु
		esecs[3].s_relptr = esecs[4].s_relptr
		    = esecs[5].s_relptr = 0;
		esecs[3].s_lnnoptr = esecs[4].s_lnnoptr
		    = esecs[5].s_lnnoptr = 0;
		esecs[3].s_nreloc = esecs[4].s_nreloc = esecs[5].s_nreloc =
		    0;
		esecs[3].s_nlnno = esecs[4].s_nlnno = esecs[5].s_nlnno = 0;
	पूर्ण
	esecs[0].s_flags = 0x20;
	esecs[1].s_flags = 0x40;
	esecs[2].s_flags = 0x82;
	अगर (addflag) अणु
		esecs[3].s_flags = 0x100;
		esecs[4].s_flags = 0x200;
		esecs[5].s_flags = 0x400;
	पूर्ण

	/* Make the output file... */
	अगर ((outfile = खोलो(argv[2], O_WRONLY | O_CREAT, 0777)) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Unable to create %s: %s\n", argv[2],
			म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	अगर (must_convert_endian)
		convert_ecoff_filehdr(&efh);
	/* Write the headers... */
	i = ग_लिखो(outfile, &efh, माप efh);
	अगर (i != माप efh) अणु
		लिखो_त्रुटि("efh: write");
		निकास(1);

		क्रम (i = 0; i < nosecs; i++) अणु
			म_लिखो
			    ("Section %d: %s phys %"PRIx32"  size %"PRIx32"\t file offset %"PRIx32"\n",
			     i, esecs[i].s_name, esecs[i].s_paddr,
			     esecs[i].s_size, esecs[i].s_scnptr);
		पूर्ण
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "wrote %d byte file header.\n", i);

	अगर (must_convert_endian)
		convert_ecoff_aouthdr(&eah);
	i = ग_लिखो(outfile, &eah, माप eah);
	अगर (i != माप eah) अणु
		लिखो_त्रुटि("eah: write");
		निकास(1);
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "wrote %d byte a.out header.\n", i);

	अगर (must_convert_endian)
		convert_ecoff_esecs(&esecs[0], nosecs);
	i = ग_लिखो(outfile, &esecs, nosecs * माप(काष्ठा scnhdr));
	अगर (i != nosecs * माप(काष्ठा scnhdr)) अणु
		लिखो_त्रुटि("esecs: write");
		निकास(1);
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "wrote %d bytes of section headers.\n", i);

	pad = (माप(efh) + माप(eah) + nosecs * माप(काष्ठा scnhdr)) & 15;
	अगर (pad) अणु
		pad = 16 - pad;
		i = ग_लिखो(outfile, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0", pad);
		अगर (i < 0) अणु
			लिखो_त्रुटि("ipad: write");
			निकास(1);
		पूर्ण
		ख_लिखो(मानक_त्रुटि, "wrote %d byte pad.\n", i);
	पूर्ण

	/*
	 * Copy the loadable sections.	 Zero-fill any gaps less than 64k;
	 * complain about any zero-filling, and die अगर we're asked to zero-fill
	 * more than 64k.
	 */
	क्रम (i = 0; i < ex.e_phnum; i++) अणु
		/* Unprocessable sections were handled above, so just verअगरy that
		   the section can be loaded beक्रमe copying. */
		अगर (ph[i].p_type == PT_LOAD && ph[i].p_filesz) अणु
			अगर (cur_vma != ph[i].p_vaddr) अणु
				uपूर्णांक32_t gap = ph[i].p_vaddr - cur_vma;
				अक्षर obuf[1024];
				अगर (gap > 65536) अणु
					ख_लिखो(मानक_त्रुटि,
						"Intersegment gap (%"PRId32" bytes) too large.\n",
						gap);
					निकास(1);
				पूर्ण
				ख_लिखो(मानक_त्रुटि,
					"Warning: %d byte intersegment gap.\n",
					gap);
				स_रखो(obuf, 0, माप obuf);
				जबतक (gap) अणु
					पूर्णांक count =
					    ग_लिखो(outfile, obuf,
						  (gap >
						   माप obuf ? माप
						   obuf : gap));
					अगर (count < 0) अणु
						ख_लिखो(मानक_त्रुटि,
							"Error writing gap: %s\n",
							म_त्रुटि(त्रुटि_सं));
						निकास(1);
					पूर्ण
					gap -= count;
				पूर्ण
			पूर्ण
			ख_लिखो(मानक_त्रुटि, "writing %d bytes...\n",
				ph[i].p_filesz);
			copy(outfile, infile, ph[i].p_offset,
			     ph[i].p_filesz);
			cur_vma = ph[i].p_vaddr + ph[i].p_filesz;
		पूर्ण
	पूर्ण

	/*
	 * Write a page of padding क्रम boot PROMS that पढ़ो entire pages.
	 * Without this, they may attempt to पढ़ो past the end of the
	 * data section, incur an error, and refuse to boot.
	 */
	अणु
		अक्षर obuf[4096];
		स_रखो(obuf, 0, माप obuf);
		अगर (ग_लिखो(outfile, obuf, माप(obuf)) != माप(obuf)) अणु
			ख_लिखो(मानक_त्रुटि, "Error writing PROM padding: %s\n",
				म_त्रुटि(त्रुटि_सं));
			निकास(1);
		पूर्ण
	पूर्ण

	/* Looks like we won... */
	निकास(0);
पूर्ण
