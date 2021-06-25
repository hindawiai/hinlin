<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Some ECOFF definitions.
 */

#समावेश <मानक_निवेशt.h>

प्रकार काष्ठा filehdr अणु
	uपूर्णांक16_t	f_magic;	/* magic number */
	uपूर्णांक16_t	f_nscns;	/* number of sections */
	पूर्णांक32_t		f_timdat;	/* समय & date stamp */
	पूर्णांक32_t		f_symptr;	/* file poपूर्णांकer to symbolic header */
	पूर्णांक32_t		f_nsyms;	/* माप(symbolic hdr) */
	uपूर्णांक16_t	f_opthdr;	/* माप(optional hdr) */
	uपूर्णांक16_t	f_flags;	/* flags */
पूर्ण FILHDR;
#घोषणा FILHSZ	माप(FILHDR)

#घोषणा MIPSEBMAGIC	0x160
#घोषणा MIPSELMAGIC	0x162

प्रकार काष्ठा scnhdr अणु
	अक्षर		s_name[8];	/* section name */
	पूर्णांक32_t		s_paddr;	/* physical address, aliased s_nlib */
	पूर्णांक32_t		s_vaddr;	/* भव address */
	पूर्णांक32_t		s_size;		/* section size */
	पूर्णांक32_t		s_scnptr;	/* file ptr to raw data क्रम section */
	पूर्णांक32_t		s_relptr;	/* file ptr to relocation */
	पूर्णांक32_t		s_lnnoptr;	/* file ptr to gp histogram */
	uपूर्णांक16_t	s_nreloc;	/* number of relocation entries */
	uपूर्णांक16_t	s_nlnno;	/* number of gp histogram entries */
	पूर्णांक32_t		s_flags;	/* flags */
पूर्ण SCNHDR;
#घोषणा SCNHSZ		माप(SCNHDR)
#घोषणा SCNROUND	((पूर्णांक32_t)16)

प्रकार काष्ठा aouthdr अणु
	पूर्णांक16_t	magic;		/* see above				*/
	पूर्णांक16_t	vstamp;		/* version stamp			*/
	पूर्णांक32_t	tsize;		/* text size in bytes, padded to DW bdry*/
	पूर्णांक32_t	dsize;		/* initialized data "  "		*/
	पूर्णांक32_t	bsize;		/* uninitialized data "	  "		*/
	पूर्णांक32_t	entry;		/* entry pt.				*/
	पूर्णांक32_t	text_start;	/* base of text used क्रम this file	*/
	पूर्णांक32_t	data_start;	/* base of data used क्रम this file	*/
	पूर्णांक32_t	bss_start;	/* base of bss used क्रम this file	*/
	पूर्णांक32_t	gprmask;	/* general purpose रेजिस्टर mask	*/
	पूर्णांक32_t	cprmask[4];	/* co-processor रेजिस्टर masks		*/
	पूर्णांक32_t	gp_value;	/* the gp value used क्रम this object	*/
पूर्ण AOUTHDR;
#घोषणा AOUTHSZ माप(AOUTHDR)

#घोषणा OMAGIC		0407
#घोषणा NMAGIC		0410
#घोषणा ZMAGIC		0413
#घोषणा SMAGIC		0411
#घोषणा LIBMAGIC	0443

#घोषणा N_TXTOFF(f, a) \
 ((a).magic == ZMAGIC || (a).magic == LIBMAGIC ? 0 : \
  ((a).vstamp < 23 ? \
   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + 7) & 0xfffffff8) : \
   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + SCNROUND-1) & ~(SCNROUND-1)) ) )
#घोषणा N_DATOFF(f, a) \
  N_TXTOFF(f, a) + (a).tsize;
