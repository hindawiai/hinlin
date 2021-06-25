<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002-2003  David McCullough <davidm@snapgear.com>
 * Copyright (C) 1998       Kenneth Albanowski <kjahds@kjahds.com>
 *                          The Silver Hammer Group, Ltd.
 *
 * This file provides the definitions and काष्ठाures needed to
 * support uClinux flat-क्रमmat executables.
 */
#अगर_अघोषित _LINUX_FLAT_H
#घोषणा _LINUX_FLAT_H

#घोषणा	FLAT_VERSION			0x00000004L

/*
 * To make everything easier to port and manage cross platक्रमm
 * development,  all fields are in network byte order.
 */

काष्ठा flat_hdr अणु
	अक्षर	magic[4];
	__be32	rev;          /* version (as above) */
	__be32	entry;        /* Offset of first executable inकाष्ठाion
				 with text segment from beginning of file */
	__be32	data_start;   /* Offset of data segment from beginning of
				 file */
	__be32	data_end;     /* Offset of end of data segment from beginning
				 of file */
	__be32	bss_end;      /* Offset of end of bss segment from beginning
				 of file */

	/* (It is assumed that data_end through bss_end क्रमms the bss segment.) */

	__be32	stack_size;   /* Size of stack, in bytes */
	__be32	reloc_start;  /* Offset of relocation records from beginning of
				 file */
	__be32	reloc_count;  /* Number of relocation records */
	__be32	flags;
	__be32	build_date;   /* When the program/library was built */
	__u32	filler[5];    /* Reservered, set to zero */
पूर्ण;

#घोषणा FLAT_FLAG_RAM    0x0001 /* load program entirely पूर्णांकo RAM */
#घोषणा FLAT_FLAG_GOTPIC 0x0002 /* program is PIC with GOT */
#घोषणा FLAT_FLAG_GZIP   0x0004 /* all but the header is compressed */
#घोषणा FLAT_FLAG_GZDATA 0x0008 /* only data/relocs are compressed (क्रम XIP) */
#घोषणा FLAT_FLAG_KTRACE 0x0010 /* output useful kernel trace क्रम debugging */

/*
 * While it would be nice to keep this header clean,  users of older
 * tools still need this support in the kernel.  So this section is
 * purely क्रम compatibility with old tool chains.
 *
 * DO NOT make changes or enhancements to the old क्रमmat please,  just work
 *        with the क्रमmat above,  except to fix bugs with old क्रमmat support.
 */

#घोषणा	OLD_FLAT_VERSION			0x00000002L
#घोषणा OLD_FLAT_RELOC_TYPE_TEXT	0
#घोषणा OLD_FLAT_RELOC_TYPE_DATA	1
#घोषणा OLD_FLAT_RELOC_TYPE_BSS		2

प्रकार जोड़ अणु
	u32		value;
	काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD) || \
    (defined(mc68000) && !defined(CONFIG_COLDFIRE))
		s32	offset : 30;
		u32	type : 2;
# elअगर defined(__BIG_ENDIAN_BITFIELD)
		u32	type : 2;
		s32	offset : 30;
# अन्यथा
#   	error "Unknown bitfield order for flat files."
# endअगर
	पूर्ण reloc;
पूर्ण flat_v2_reloc_t;

#पूर्ण_अगर /* _LINUX_FLAT_H */
