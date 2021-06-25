<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* IBM RS/6000 "XCOFF" file definitions क्रम BFD.
   Copyright (C) 1990, 1991 Free Software Foundation, Inc.
   FIXME: Can someone provide a transliteration of this name पूर्णांकo ASCII?
   Using the following अक्षरs caused a compiler warning on HIUX (so I replaced
   them with octal escapes), and isn't useful without an understanding of what
   अक्षरacter set it is.
   Written by Mimi Ph\373\364ng-Th\345o V\365 of IBM
   and John Gilmore of Cygnus Support.  */

/********************** खाता HEADER **********************/

काष्ठा बाह्यal_filehdr अणु
	अक्षर f_magic[2];	/* magic number			*/
	अक्षर f_nscns[2];	/* number of sections		*/
	अक्षर f_timdat[4];	/* समय & date stamp		*/
	अक्षर f_symptr[4];	/* file poपूर्णांकer to symtab	*/
	अक्षर f_nsyms[4];	/* number of symtab entries	*/
	अक्षर f_opthdr[2];	/* माप(optional hdr)		*/
	अक्षर f_flags[2];	/* flags			*/
पूर्ण;

        /* IBM RS/6000 */
#घोषणा U802WRMAGIC     0730    /* ग_लिखोable text segments **chh**      */
#घोषणा U802ROMAGIC     0735    /* पढ़ोonly sharable text segments      */
#घोषणा U802TOCMAGIC    0737    /* पढ़ोonly text segments and TOC       */

#घोषणा BADMAG(x)	\
	((x).f_magic != U802ROMAGIC && (x).f_magic != U802WRMAGIC && \
	 (x).f_magic != U802TOCMAGIC)

#घोषणा	FILHDR	काष्ठा बाह्यal_filehdr
#घोषणा	FILHSZ	20


/********************** AOUT "OPTIONAL HEADER" **********************/


प्रकार काष्ठा
अणु
  अचिन्हित अक्षर	magic[2];	/* type of file			*/
  अचिन्हित अक्षर	vstamp[2];	/* version stamp		*/
  अचिन्हित अक्षर	tsize[4];	/* text size in bytes, padded to FW bdry */
  अचिन्हित अक्षर	dsize[4];	/* initialized data "  "	*/
  अचिन्हित अक्षर	bsize[4];	/* uninitialized data "   "	*/
  अचिन्हित अक्षर	entry[4];	/* entry pt.			*/
  अचिन्हित अक्षर	text_start[4];	/* base of text used क्रम this file */
  अचिन्हित अक्षर	data_start[4];	/* base of data used क्रम this file */
  अचिन्हित अक्षर	o_toc[4];	/* address of TOC */
  अचिन्हित अक्षर	o_snentry[2];	/* section number of entry poपूर्णांक */
  अचिन्हित अक्षर	o_sntext[2];	/* section number of .text section */
  अचिन्हित अक्षर	o_sndata[2];	/* section number of .data section */
  अचिन्हित अक्षर	o_sntoc[2];	/* section number of TOC */
  अचिन्हित अक्षर	o_snloader[2];	/* section number of .loader section */
  अचिन्हित अक्षर	o_snbss[2];	/* section number of .bss section */
  अचिन्हित अक्षर	o_algntext[2];	/* .text alignment */
  अचिन्हित अक्षर	o_algndata[2];	/* .data alignment */
  अचिन्हित अक्षर	o_modtype[2];	/* module type (??) */
  अचिन्हित अक्षर o_cputype[2];	/* cpu type */
  अचिन्हित अक्षर	o_maxstack[4];	/* max stack size (??) */
  अचिन्हित अक्षर o_maxdata[4];	/* max data size (??) */
  अचिन्हित अक्षर	o_resv2[12];	/* reserved */
पूर्ण
AOUTHDR;

#घोषणा AOUTSZ 72
#घोषणा SMALL_AOUTSZ (28)
#घोषणा AOUTHDRSZ 72

#घोषणा	RS6K_AOUTHDR_OMAGIC	0x0107	/* old: text & data ग_लिखोable */
#घोषणा	RS6K_AOUTHDR_NMAGIC	0x0108	/* new: text r/o, data r/w */
#घोषणा	RS6K_AOUTHDR_ZMAGIC	0x010B	/* paged: text r/o, both page-aligned */


/********************** SECTION HEADER **********************/


काष्ठा बाह्यal_scnhdr अणु
	अक्षर		s_name[8];	/* section name			*/
	अक्षर		s_paddr[4];	/* physical address, aliased s_nlib */
	अक्षर		s_vaddr[4];	/* भव address		*/
	अक्षर		s_size[4];	/* section size			*/
	अक्षर		s_scnptr[4];	/* file ptr to raw data क्रम section */
	अक्षर		s_relptr[4];	/* file ptr to relocation	*/
	अक्षर		s_lnnoptr[4];	/* file ptr to line numbers	*/
	अक्षर		s_nreloc[2];	/* number of relocation entries	*/
	अक्षर		s_nlnno[2];	/* number of line number entries*/
	अक्षर		s_flags[4];	/* flags			*/
पूर्ण;

/*
 * names of "special" sections
 */
#घोषणा _TEXT	".text"
#घोषणा _DATA	".data"
#घोषणा _BSS	".bss"
#घोषणा _PAD	".pad"
#घोषणा _LOADER	".loader"

#घोषणा	SCNHDR	काष्ठा बाह्यal_scnhdr
#घोषणा	SCNHSZ	40

/* XCOFF uses a special .loader section with type STYP_LOADER.  */
#घोषणा STYP_LOADER 0x1000

/* XCOFF uses a special .debug section with type STYP_DEBUG.  */
#घोषणा STYP_DEBUG 0x2000

/* XCOFF handles line number or relocation overflow by creating
   another section header with STYP_OVRFLO set.  */
#घोषणा STYP_OVRFLO 0x8000

/********************** LINE NUMBERS **********************/

/* 1 line number entry क्रम every "breakpointable" source line in a section.
 * Line numbers are grouped on a per function basis; first entry in a function
 * grouping will have l_lnno = 0 and in place of physical address will be the
 * symbol table index of the function name.
 */
काष्ठा बाह्यal_lineno अणु
	जोड़ अणु
		अक्षर l_symndx[4];	/* function name symbol index, अगरf l_lnno == 0*/
		अक्षर l_paddr[4];	/* (physical) address of line number	*/
	पूर्ण l_addr;
	अक्षर l_lnno[2];	/* line number		*/
पूर्ण;


#घोषणा	LINENO	काष्ठा बाह्यal_lineno
#घोषणा	LINESZ	6


/********************** SYMBOLS **********************/

#घोषणा E_SYMNMLEN	8	/* # अक्षरacters in a symbol name	*/
#घोषणा E_FILNMLEN	14	/* # अक्षरacters in a file name		*/
#घोषणा E_DIMNUM	4	/* # array dimensions in auxiliary entry */

काष्ठा बाह्यal_syment
अणु
  जोड़ अणु
    अक्षर e_name[E_SYMNMLEN];
    काष्ठा अणु
      अक्षर e_zeroes[4];
      अक्षर e_offset[4];
    पूर्ण e;
  पूर्ण e;
  अक्षर e_value[4];
  अक्षर e_scnum[2];
  अक्षर e_type[2];
  अक्षर e_sclass[1];
  अक्षर e_numaux[1];
पूर्ण;



#घोषणा N_BTMASK	(017)
#घोषणा N_TMASK		(060)
#घोषणा N_BTSHFT	(4)
#घोषणा N_TSHIFT	(2)


जोड़ बाह्यal_auxent अणु
	काष्ठा अणु
		अक्षर x_tagndx[4];	/* str, un, or क्रमागत tag indx */
		जोड़ अणु
			काष्ठा अणु
			    अक्षर  x_lnno[2]; /* declaration line number */
			    अक्षर  x_size[2]; /* str/जोड़/array size */
			पूर्ण x_lnsz;
			अक्षर x_fsize[4];	/* size of function */
		पूर्ण x_misc;
		जोड़ अणु
			काष्ठा अणु		/* अगर ISFCN, tag, or .bb */
			    अक्षर x_lnnoptr[4];	/* ptr to fcn line # */
			    अक्षर x_endndx[4];	/* entry ndx past block end */
			पूर्ण x_fcn;
			काष्ठा अणु		/* अगर ISARY, up to 4 dimen. */
			    अक्षर x_dimen[E_DIMNUM][2];
			पूर्ण x_ary;
		पूर्ण x_fcnary;
		अक्षर x_tvndx[2];		/* tv index */
	पूर्ण x_sym;

	जोड़ अणु
		अक्षर x_fname[E_FILNMLEN];
		काष्ठा अणु
			अक्षर x_zeroes[4];
			अक्षर x_offset[4];
		पूर्ण x_n;
	पूर्ण x_file;

	काष्ठा अणु
		अक्षर x_scnlen[4];			/* section length */
		अक्षर x_nreloc[2];	/* # relocation entries */
		अक्षर x_nlinno[2];	/* # line numbers */
	पूर्ण x_scn;

        काष्ठा अणु
		अक्षर x_tvfill[4];	/* tv fill value */
		अक्षर x_tvlen[2];	/* length of .tv */
		अक्षर x_tvran[2][2];	/* tv range */
	पूर्ण x_tv;		/* info about .tv section (in auxent of symbol .tv)) */

	काष्ठा अणु
		अचिन्हित अक्षर x_scnlen[4];
		अचिन्हित अक्षर x_parmhash[4];
		अचिन्हित अक्षर x_snhash[2];
		अचिन्हित अक्षर x_smtyp[1];
		अचिन्हित अक्षर x_smclas[1];
		अचिन्हित अक्षर x_stab[4];
		अचिन्हित अक्षर x_snstab[2];
	पूर्ण x_csect;

पूर्ण;

#घोषणा	SYMENT	काष्ठा बाह्यal_syment
#घोषणा	SYMESZ	18
#घोषणा	AUXENT	जोड़ बाह्यal_auxent
#घोषणा	AUXESZ	18
#घोषणा DBXMASK 0x80		/* क्रम dbx storage mask */
#घोषणा SYMNAME_IN_DEBUG(symptr) ((symptr)->n_sclass & DBXMASK)



/********************** RELOCATION सूचीECTIVES **********************/


काष्ठा बाह्यal_reloc अणु
  अक्षर r_vaddr[4];
  अक्षर r_symndx[4];
  अक्षर r_size[1];
  अक्षर r_type[1];
पूर्ण;


#घोषणा RELOC काष्ठा बाह्यal_reloc
#घोषणा RELSZ 10

#घोषणा DEFAULT_DATA_SECTION_ALIGNMENT 4
#घोषणा DEFAULT_BSS_SECTION_ALIGNMENT 4
#घोषणा DEFAULT_TEXT_SECTION_ALIGNMENT 4
/* For new sections we haven't heard of beक्रमe */
#घोषणा DEFAULT_SECTION_ALIGNMENT 4
