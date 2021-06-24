<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* This file is derived from the GAS 2.1.4 assembler control file.
   The GAS product is under the GNU General Public License, version 2 or later.
   As such, this file is also under that license.

   If the file क्रमmat changes in the COFF object, this file should be
   subsequently updated to reflect the changes.

   The actual loader module only uses a few of these काष्ठाures. The full
   set is करोcumented here because I received the full set. If you wish
   more inक्रमmation about COFF, then O'Reilly has a very excellent book.
*/

#अगर_अघोषित _UAPI_LINUX_COFF_H
#घोषणा _UAPI_LINUX_COFF_H

#घोषणा  E_SYMNMLEN  8   /* Number of अक्षरacters in a symbol name         */
#घोषणा  E_FILNMLEN 14   /* Number of अक्षरacters in a file name           */
#घोषणा  E_DIMNUM    4   /* Number of array dimensions in auxiliary entry */

/*
 * These defines are byte order independent. There is no alignment of fields
 * permitted in the काष्ठाures. Thereक्रमe they are declared as अक्षरacters
 * and the values loaded from the अक्षरacter positions. It also makes it
 * nice to have it "endian" independent.
 */
 
/* Load a लघु पूर्णांक from the following tables with little-endian क्रमmats */
#घोषणा COFF_SHORT_L(ps) ((लघु)(((अचिन्हित लघु)((अचिन्हित अक्षर)ps[1])<<8)|\
				  ((अचिन्हित लघु)((अचिन्हित अक्षर)ps[0]))))

/* Load a दीर्घ पूर्णांक from the following tables with little-endian क्रमmats */
#घोषणा COFF_LONG_L(ps) (((दीर्घ)(((अचिन्हित दीर्घ)((अचिन्हित अक्षर)ps[3])<<24) |\
				 ((अचिन्हित दीर्घ)((अचिन्हित अक्षर)ps[2])<<16) |\
				 ((अचिन्हित दीर्घ)((अचिन्हित अक्षर)ps[1])<<8)  |\
				 ((अचिन्हित दीर्घ)((अचिन्हित अक्षर)ps[0])))))
 
/* Load a लघु पूर्णांक from the following tables with big-endian क्रमmats */
#घोषणा COFF_SHORT_H(ps) ((लघु)(((अचिन्हित लघु)((अचिन्हित अक्षर)ps[0])<<8)|\
				  ((अचिन्हित लघु)((अचिन्हित अक्षर)ps[1]))))

/* Load a दीर्घ पूर्णांक from the following tables with big-endian क्रमmats */
#घोषणा COFF_LONG_H(ps) (((दीर्घ)(((अचिन्हित दीर्घ)((अचिन्हित अक्षर)ps[0])<<24) |\
				 ((अचिन्हित दीर्घ)((अचिन्हित अक्षर)ps[1])<<16) |\
				 ((अचिन्हित दीर्घ)((अचिन्हित अक्षर)ps[2])<<8)  |\
				 ((अचिन्हित दीर्घ)((अचिन्हित अक्षर)ps[3])))))

/* These may be overridden later by brain dead implementations which generate
   a big-endian header with little-endian data. In that हाल, generate a
   replacement macro which tests a flag and uses either of the two above
   as appropriate. */

#घोषणा COFF_LONG(v)   COFF_LONG_L(v)
#घोषणा COFF_SHORT(v)  COFF_SHORT_L(v)

/*** coff inक्रमmation क्रम Intel 386/486.  */

/********************** खाता HEADER **********************/

काष्ठा COFF_filehdr अणु
	अक्षर f_magic[2];	/* magic number			*/
	अक्षर f_nscns[2];	/* number of sections		*/
	अक्षर f_timdat[4];	/* समय & date stamp		*/
	अक्षर f_symptr[4];	/* file poपूर्णांकer to symtab	*/
	अक्षर f_nsyms[4];	/* number of symtab entries	*/
	अक्षर f_opthdr[2];	/* माप(optional hdr)		*/
	अक्षर f_flags[2];	/* flags			*/
पूर्ण;

/*
 *   Bits क्रम f_flags:
 *
 *	F_RELFLG	relocation info stripped from file
 *	F_EXEC		file is executable  (i.e. no unresolved बाह्यal
 *			references)
 *	F_LNNO		line numbers stripped from file
 *	F_LSYMS		local symbols stripped from file
 *	F_MINMAL	this is a minimal object file (".m") output of fextract
 *	F_UPDATE	this is a fully bound update file, output of ogen
 *	F_SWABD		this file has had its bytes swabbed (in names)
 *	F_AR16WR	this file has the byte ordering of an AR16WR
 *			(e.g. 11/70) machine
 *	F_AR32WR	this file has the byte ordering of an AR32WR machine
 *			(e.g. vax and iNTEL 386)
 *	F_AR32W		this file has the byte ordering of an AR32W machine
 *			(e.g. 3b,maxi)
 *	F_PATCH		file contains "patch" list in optional header
 *	F_NODF		(minimal file only) no decision functions क्रम
 *			replaced functions
 */

#घोषणा  COFF_F_RELFLG		0000001
#घोषणा  COFF_F_EXEC		0000002
#घोषणा  COFF_F_LNNO		0000004
#घोषणा  COFF_F_LSYMS		0000010
#घोषणा  COFF_F_MINMAL		0000020
#घोषणा  COFF_F_UPDATE		0000040
#घोषणा  COFF_F_SWABD		0000100
#घोषणा  COFF_F_AR16WR		0000200
#घोषणा  COFF_F_AR32WR		0000400
#घोषणा  COFF_F_AR32W		0001000
#घोषणा  COFF_F_PATCH		0002000
#घोषणा  COFF_F_NODF		0002000

#घोषणा	COFF_I386MAGIC	        0x14c   /* Linux's प्रणाली    */

#अगर 0   /* Perhaps, someday, these क्रमmats may be used.      */
#घोषणा COFF_I386PTXMAGIC	0x154
#घोषणा COFF_I386AIXMAGIC	0x175   /* IBM's AIX प्रणाली  */
#घोषणा COFF_I386BADMAG(x) ((COFF_SHORT((x).f_magic) != COFF_I386MAGIC) \
			  && COFF_SHORT((x).f_magic) != COFF_I386PTXMAGIC \
			  && COFF_SHORT((x).f_magic) != COFF_I386AIXMAGIC)
#अन्यथा
#घोषणा COFF_I386BADMAG(x) (COFF_SHORT((x).f_magic) != COFF_I386MAGIC)
#पूर्ण_अगर

#घोषणा	COFF_FILHDR	काष्ठा COFF_filehdr
#घोषणा	COFF_FILHSZ	माप(COFF_FILHDR)

/********************** AOUT "OPTIONAL HEADER" **********************/

/* Linux COFF must have this "optional" header. Standard COFF has no entry
   location क्रम the "entry" poपूर्णांक. They normally would start with the first
   location of the .text section. This is not a good idea क्रम linux. So,
   the use of this "optional" header is not optional. It is required.

   Do not be tempted to assume that the size of the optional header is
   a स्थिरant and simply index the next byte by the size of this काष्ठाure.
   Use the 'f_opthdr' field in the मुख्य coff header क्रम the size of the
   काष्ठाure actually written to the file!!
*/

प्रकार काष्ठा 
अणु
  अक्षर 	magic[2];		/* type of file				 */
  अक्षर	vstamp[2];		/* version stamp			 */
  अक्षर	tsize[4];		/* text size in bytes, padded to FW bdry */
  अक्षर	dsize[4];		/* initialized   data "   "		 */
  अक्षर	bsize[4];		/* uninitialized data "   "		 */
  अक्षर	entry[4];		/* entry pt.				 */
  अक्षर 	text_start[4];		/* base of text used क्रम this file       */
  अक्षर 	data_start[4];		/* base of data used क्रम this file       */
पूर्ण
COFF_AOUTHDR;

#घोषणा COFF_AOUTSZ (माप(COFF_AOUTHDR))

#घोषणा COFF_STMAGIC	0401
#घोषणा COFF_OMAGIC     0404
#घोषणा COFF_JMAGIC     0407    /* dirty text and data image, can't share  */
#घोषणा COFF_DMAGIC     0410    /* dirty text segment, data aligned        */
#घोषणा COFF_ZMAGIC     0413    /* The proper magic number क्रम executables  */
#घोषणा COFF_SHMAGIC	0443	/* shared library header                   */

/********************** SECTION HEADER **********************/

काष्ठा COFF_scnhdr अणु
  अक्षर		s_name[8];	/* section name			    */
  अक्षर		s_paddr[4];	/* physical address, aliased s_nlib */
  अक्षर		s_vaddr[4];	/* भव address		    */
  अक्षर		s_size[4];	/* section size			    */
  अक्षर		s_scnptr[4];	/* file ptr to raw data क्रम section */
  अक्षर		s_relptr[4];	/* file ptr to relocation	    */
  अक्षर		s_lnnoptr[4];	/* file ptr to line numbers	    */
  अक्षर		s_nreloc[2];	/* number of relocation entries	    */
  अक्षर		s_nlnno[2];	/* number of line number entries    */
  अक्षर		s_flags[4];	/* flags			    */
पूर्ण;

#घोषणा	COFF_SCNHDR	काष्ठा COFF_scnhdr
#घोषणा	COFF_SCNHSZ	माप(COFF_SCNHDR)

/*
 * names of "special" sections
 */

#घोषणा COFF_TEXT	".text"
#घोषणा COFF_DATA	".data"
#घोषणा COFF_BSS	".bss"
#घोषणा COFF_COMMENT    ".comment"
#घोषणा COFF_LIB        ".lib"

#घोषणा COFF_SECT_TEXT  0      /* Section क्रम inकाष्ठाion code             */
#घोषणा COFF_SECT_DATA  1      /* Section क्रम initialized globals          */
#घोषणा COFF_SECT_BSS   2      /* Section क्रम un-initialized globals       */
#घोषणा COFF_SECT_REQD  3      /* Minimum number of sections क्रम good file */

#घोषणा COFF_STYP_REG     0x00 /* regular segment                          */
#घोषणा COFF_STYP_DSECT   0x01 /* dummy segment                            */
#घोषणा COFF_STYP_NOLOAD  0x02 /* no-load segment                          */
#घोषणा COFF_STYP_GROUP   0x04 /* group segment                            */
#घोषणा COFF_STYP_PAD     0x08 /* .pad segment                             */
#घोषणा COFF_STYP_COPY    0x10 /* copy section                             */
#घोषणा COFF_STYP_TEXT    0x20 /* .text segment                            */
#घोषणा COFF_STYP_DATA    0x40 /* .data segment                            */
#घोषणा COFF_STYP_BSS     0x80 /* .bss segment                             */
#घोषणा COFF_STYP_INFO   0x200 /* .comment section                         */
#घोषणा COFF_STYP_OVER   0x400 /* overlay section                          */
#घोषणा COFF_STYP_LIB    0x800 /* library section                          */

/*
 * Shared libraries have the following section header in the data field क्रम
 * each library.
 */

काष्ठा COFF_slib अणु
  अक्षर		sl_entsz[4];	/* Size of this entry               */
  अक्षर		sl_pathndx[4];	/* size of the header field         */
पूर्ण;

#घोषणा	COFF_SLIBHD	काष्ठा COFF_slib
#घोषणा	COFF_SLIBSZ	माप(COFF_SLIBHD)

/********************** LINE NUMBERS **********************/

/* 1 line number entry क्रम every "breakpointable" source line in a section.
 * Line numbers are grouped on a per function basis; first entry in a function
 * grouping will have l_lnno = 0 and in place of physical address will be the
 * symbol table index of the function name.
 */

काष्ठा COFF_lineno अणु
  जोड़ अणु
    अक्षर l_symndx[4];	/* function name symbol index, अगरf l_lnno == 0*/
    अक्षर l_paddr[4];	/* (physical) address of line number	*/
  पूर्ण l_addr;
  अक्षर l_lnno[2];	/* line number		*/
पूर्ण;

#घोषणा	COFF_LINENO	काष्ठा COFF_lineno
#घोषणा	COFF_LINESZ	6

/********************** SYMBOLS **********************/

#घोषणा COFF_E_SYMNMLEN	 8	/* # अक्षरacters in a लघु symbol name	*/
#घोषणा COFF_E_FILNMLEN	14	/* # अक्षरacters in a file name		*/
#घोषणा COFF_E_DIMNUM	 4	/* # array dimensions in auxiliary entry */

/*
 *  All symbols and sections have the following definition
 */

काष्ठा COFF_syment 
अणु
  जोड़ अणु
    अक्षर e_name[E_SYMNMLEN];    /* Symbol name (first 8 अक्षरacters) */
    काष्ठा अणु
      अक्षर e_zeroes[4];         /* Leading zeros */
      अक्षर e_offset[4];         /* Offset अगर this is a header section */
    पूर्ण e;
  पूर्ण e;

  अक्षर e_value[4];              /* Value (address) of the segment */
  अक्षर e_scnum[2];              /* Section number */
  अक्षर e_type[2];               /* Type of section */
  अक्षर e_sclass[1];             /* Loader class */
  अक्षर e_numaux[1];             /* Number of auxiliary entries which follow */
पूर्ण;

#घोषणा COFF_N_BTMASK	(0xf)   /* Mask क्रम important class bits */
#घोषणा COFF_N_TMASK	(0x30)  /* Mask क्रम important type bits  */
#घोषणा COFF_N_BTSHFT	(4)     /* # bits to shअगरt class field   */
#घोषणा COFF_N_TSHIFT	(2)     /* # bits to shअगरt type field    */

/*
 *  Auxiliary entries because the मुख्य table is too limiting.
 */
  
जोड़ COFF_auxent अणु

/*
 *  Debugger inक्रमmation
 */

  काष्ठा अणु
    अक्षर x_tagndx[4];	        /* str, un, or क्रमागत tag indx */
    जोड़ अणु
      काष्ठा अणु
	अक्षर  x_lnno[2];        /* declaration line number */
	अक्षर  x_size[2];        /* str/जोड़/array size */
      पूर्ण x_lnsz;
      अक्षर x_fsize[4];	        /* size of function */
    पूर्ण x_misc;

    जोड़ अणु
      काष्ठा अणु		        /* अगर ISFCN, tag, or .bb */
	अक्षर x_lnnoptr[4];	/* ptr to fcn line # */
	अक्षर x_endndx[4];	/* entry ndx past block end */
      पूर्ण x_fcn;

      काष्ठा अणु		        /* अगर ISARY, up to 4 dimen. */
	अक्षर x_dimen[E_DIMNUM][2];
      पूर्ण x_ary;
    पूर्ण x_fcnary;

    अक्षर x_tvndx[2];	/* tv index */
  पूर्ण x_sym;

/*
 *   Source file names (debugger inक्रमmation)
 */

  जोड़ अणु
    अक्षर x_fname[E_FILNMLEN];
    काष्ठा अणु
      अक्षर x_zeroes[4];
      अक्षर x_offset[4];
    पूर्ण x_n;
  पूर्ण x_file;

/*
 *   Section inक्रमmation
 */

  काष्ठा अणु
    अक्षर x_scnlen[4];	/* section length */
    अक्षर x_nreloc[2];	/* # relocation entries */
    अक्षर x_nlinno[2];	/* # line numbers */
  पूर्ण x_scn;

/*
 *   Transfer vector (branch table)
 */
  
  काष्ठा अणु
    अक्षर x_tvfill[4];	/* tv fill value */
    अक्षर x_tvlen[2];	/* length of .tv */
    अक्षर x_tvran[2][2];	/* tv range */
  पूर्ण x_tv;		/* info about .tv section (in auxent of symbol .tv)) */
पूर्ण;

#घोषणा	COFF_SYMENT	काष्ठा COFF_syment
#घोषणा	COFF_SYMESZ	18	
#घोषणा	COFF_AUXENT	जोड़ COFF_auxent
#घोषणा	COFF_AUXESZ	18

#घोषणा COFF_ETEXT	"etext"

/********************** RELOCATION सूचीECTIVES **********************/

काष्ठा COFF_reloc अणु
  अक्षर r_vaddr[4];        /* Virtual address of item    */
  अक्षर r_symndx[4];       /* Symbol index in the symtab */
  अक्षर r_type[2];         /* Relocation type            */
पूर्ण;

#घोषणा COFF_RELOC काष्ठा COFF_reloc
#घोषणा COFF_RELSZ 10

#घोषणा COFF_DEF_DATA_SECTION_ALIGNMENT  4
#घोषणा COFF_DEF_BSS_SECTION_ALIGNMENT   4
#घोषणा COFF_DEF_TEXT_SECTION_ALIGNMENT  4

/* For new sections we haven't heard of beक्रमe */
#घोषणा COFF_DEF_SECTION_ALIGNMENT       4

#पूर्ण_अगर /* _UAPI_LINUX_COFF_H */
