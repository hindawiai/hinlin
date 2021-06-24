<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  linux/include/यंत्र/setup.h
 *
 *  Copyright (C) 1997-1999 Russell King
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  Structure passed to kernel to tell it about the
 *  hardware it's running on.  See Documentation/arm/setup.rst
 *  क्रम more info.
 */
#अगर_अघोषित _UAPI__ASMARM_SETUP_H
#घोषणा _UAPI__ASMARM_SETUP_H

#समावेश <linux/types.h>

#घोषणा COMMAND_LINE_SIZE 1024

/* The list ends with an ATAG_NONE node. */
#घोषणा ATAG_NONE	0x00000000

काष्ठा tag_header अणु
	__u32 size;
	__u32 tag;
पूर्ण;

/* The list must start with an ATAG_CORE node */
#घोषणा ATAG_CORE	0x54410001

काष्ठा tag_core अणु
	__u32 flags;		/* bit 0 = पढ़ो-only */
	__u32 pagesize;
	__u32 rootdev;
पूर्ण;

/* it is allowed to have multiple ATAG_MEM nodes */
#घोषणा ATAG_MEM	0x54410002

काष्ठा tag_mem32 अणु
	__u32	size;
	__u32	start;	/* physical start address */
पूर्ण;

/* VGA text type displays */
#घोषणा ATAG_VIDEOTEXT	0x54410003

काष्ठा tag_videotext अणु
	__u8		x;
	__u8		y;
	__u16		video_page;
	__u8		video_mode;
	__u8		video_cols;
	__u16		video_ega_bx;
	__u8		video_lines;
	__u8		video_isvga;
	__u16		video_poपूर्णांकs;
पूर्ण;

/* describes how the ramdisk will be used in kernel */
#घोषणा ATAG_RAMDISK	0x54410004

काष्ठा tag_ramdisk अणु
	__u32 flags;	/* bit 0 = load, bit 1 = prompt */
	__u32 size;	/* decompressed ramdisk size in _kilo_ bytes */
	__u32 start;	/* starting block of floppy-based RAM disk image */
पूर्ण;

/* describes where the compressed ramdisk image lives (भव address) */
/*
 * this one accidentally used भव addresses - as such,
 * it's deprecated.
 */
#घोषणा ATAG_INITRD	0x54410005

/* describes where the compressed ramdisk image lives (physical address) */
#घोषणा ATAG_INITRD2	0x54420005

काष्ठा tag_initrd अणु
	__u32 start;	/* physical start address */
	__u32 size;	/* size of compressed ramdisk image in bytes */
पूर्ण;

/* board serial number. "64 bits should be enough for everybody" */
#घोषणा ATAG_SERIAL	0x54410006

काष्ठा tag_serialnr अणु
	__u32 low;
	__u32 high;
पूर्ण;

/* board revision */
#घोषणा ATAG_REVISION	0x54410007

काष्ठा tag_revision अणु
	__u32 rev;
पूर्ण;

/* initial values क्रम vesafb-type framebuffers. see काष्ठा screen_info
 * in include/linux/tty.h
 */
#घोषणा ATAG_VIDEOLFB	0x54410008

काष्ठा tag_videolfb अणु
	__u16		lfb_width;
	__u16		lfb_height;
	__u16		lfb_depth;
	__u16		lfb_linelength;
	__u32		lfb_base;
	__u32		lfb_size;
	__u8		red_size;
	__u8		red_pos;
	__u8		green_size;
	__u8		green_pos;
	__u8		blue_size;
	__u8		blue_pos;
	__u8		rsvd_size;
	__u8		rsvd_pos;
पूर्ण;

/* command line: \0 terminated string */
#घोषणा ATAG_CMDLINE	0x54410009

काष्ठा tag_cmdline अणु
	अक्षर	cmdline[1];	/* this is the minimum size */
पूर्ण;

/* acorn RiscPC specअगरic inक्रमmation */
#घोषणा ATAG_ACORN	0x41000101

काष्ठा tag_acorn अणु
	__u32 memc_control_reg;
	__u32 vram_pages;
	__u8 soundशेष;
	__u8 adfsdrives;
पूर्ण;

/* footbridge memory घड़ी, see arch/arm/mach-footbridge/arch.c */
#घोषणा ATAG_MEMCLK	0x41000402

काष्ठा tag_memclk अणु
	__u32 fmemclk;
पूर्ण;

काष्ठा tag अणु
	काष्ठा tag_header hdr;
	जोड़ अणु
		काष्ठा tag_core		core;
		काष्ठा tag_mem32	mem;
		काष्ठा tag_videotext	videotext;
		काष्ठा tag_ramdisk	ramdisk;
		काष्ठा tag_initrd	initrd;
		काष्ठा tag_serialnr	serialnr;
		काष्ठा tag_revision	revision;
		काष्ठा tag_videolfb	videolfb;
		काष्ठा tag_cmdline	cmdline;

		/*
		 * Acorn specअगरic
		 */
		काष्ठा tag_acorn	acorn;

		/*
		 * DC21285 specअगरic
		 */
		काष्ठा tag_memclk	memclk;
	पूर्ण u;
पूर्ण;

काष्ठा tagtable अणु
	__u32 tag;
	पूर्णांक (*parse)(स्थिर काष्ठा tag *);
पूर्ण;

#घोषणा tag_member_present(tag,member)				\
	((अचिन्हित दीर्घ)(&((काष्ठा tag *)0L)->member + 1)	\
		<= (tag)->hdr.size * 4)

#घोषणा tag_next(t)	((काष्ठा tag *)((__u32 *)(t) + (t)->hdr.size))
#घोषणा tag_size(type)	((माप(काष्ठा tag_header) + माप(काष्ठा type)) >> 2)

#घोषणा क्रम_each_tag(t,base)		\
	क्रम (t = base; t->hdr.size; t = tag_next(t))


#पूर्ण_अगर /* _UAPI__ASMARM_SETUP_H */
