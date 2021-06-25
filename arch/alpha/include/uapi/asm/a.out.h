<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__ALPHA_A_OUT_H__
#घोषणा _UAPI__ALPHA_A_OUT_H__

#समावेश <linux/types.h>

/*
 * OSF/1 ECOFF header काष्ठाs.  ECOFF files consist of:
 * 	- a file header (काष्ठा filehdr),
 *	- an a.out header (काष्ठा aouthdr),
 *	- one or more section headers (काष्ठा scnhdr). 
 *	  The filhdr's "f_nscns" field contains the
 *	  number of section headers.
 */

काष्ठा filehdr
अणु
	/* OSF/1 "file" header */
	__u16 f_magic, f_nscns;
	__u32 f_timdat;
	__u64 f_symptr;
	__u32 f_nsyms;
	__u16 f_opthdr, f_flags;
पूर्ण;

काष्ठा aouthdr
अणु
	__u64 info;		/* after that it looks quite normal.. */
	__u64 tsize;
	__u64 dsize;
	__u64 bsize;
	__u64 entry;
	__u64 text_start;	/* with a few additions that actually make sense */
	__u64 data_start;
	__u64 bss_start;
	__u32 gprmask, fprmask;	/* biपंचांगask of general & भग्नing poपूर्णांक regs used in binary */
	__u64 gpvalue;
पूर्ण;

काष्ठा scnhdr
अणु
	अक्षर	s_name[8];
	__u64	s_paddr;
	__u64	s_vaddr;
	__u64	s_size;
	__u64	s_scnptr;
	__u64	s_relptr;
	__u64	s_lnnoptr;
	__u16	s_nreloc;
	__u16	s_nlnno;
	__u32	s_flags;
पूर्ण;

काष्ठा exec
अणु
	/* OSF/1 "file" header */
	काष्ठा filehdr		fh;
	काष्ठा aouthdr		ah;
पूर्ण;

/*
 * Define's so that the kernel exec code can access the a.out header
 * fields...
 */
#घोषणा	a_info		ah.info
#घोषणा	a_text		ah.tsize
#घोषणा a_data		ah.dsize
#घोषणा a_bss		ah.bsize
#घोषणा a_entry		ah.entry
#घोषणा a_textstart	ah.text_start
#घोषणा	a_datastart	ah.data_start
#घोषणा	a_bssstart	ah.bss_start
#घोषणा	a_gprmask	ah.gprmask
#घोषणा a_fprmask	ah.fprmask
#घोषणा a_gpvalue	ah.gpvalue

#घोषणा N_TXTADDR(x) ((x).a_textstart)
#घोषणा N_DATADDR(x) ((x).a_datastart)
#घोषणा N_BSSADDR(x) ((x).a_bssstart)
#घोषणा N_DRSIZE(x) 0
#घोषणा N_TRSIZE(x) 0
#घोषणा N_SYMSIZE(x) 0

#घोषणा AOUTHSZ		माप(काष्ठा aouthdr)
#घोषणा SCNHSZ		माप(काष्ठा scnhdr)
#घोषणा SCNROUND	16

#घोषणा N_TXTOFF(x) \
  ((दीर्घ) N_MAGIC(x) == ZMAGIC ? 0 : \
   (माप(काष्ठा exec) + (x).fh.f_nscns*SCNHSZ + SCNROUND - 1) & ~(SCNROUND - 1))

#पूर्ण_अगर /* _UAPI__ALPHA_A_OUT_H__ */
