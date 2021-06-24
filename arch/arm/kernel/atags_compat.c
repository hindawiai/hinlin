<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/atags_compat.c
 *
 *  Copyright (C) 2001 Russell King
 *
 * We keep the old params compatibility cruft in one place (here)
 * so we करोn't end up with lots of mess around other places.
 *
 * NOTE:
 *  The old काष्ठा param_काष्ठा is deprecated, but it will be kept in
 *  the kernel क्रम 5 years from now (2001). This will allow boot loaders
 *  to convert to the new काष्ठा tag way.
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/page.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "atags.h"

/*
 * Usage:
 *  - करो not go blindly adding fields, add them at the end
 *  - when adding fields, करोn't rely on the address until
 *    a patch from me has been released
 *  - unused fields should be zero (क्रम future expansion)
 *  - this काष्ठाure is relatively लघु-lived - only
 *    guaranteed to contain useful data in setup_arch()
 *
 * This is the old deprecated way to pass parameters to the kernel
 */
काष्ठा param_काष्ठा अणु
    जोड़ अणु
	काष्ठा अणु
	    अचिन्हित दीर्घ page_size;		/*  0 */
	    अचिन्हित दीर्घ nr_pages;		/*  4 */
	    अचिन्हित दीर्घ ramdisk_size;		/*  8 */
	    अचिन्हित दीर्घ flags;		/* 12 */
#घोषणा FLAG_READONLY	1
#घोषणा FLAG_RDLOAD	4
#घोषणा FLAG_RDPROMPT	8
	    अचिन्हित दीर्घ rootdev;		/* 16 */
	    अचिन्हित दीर्घ video_num_cols;	/* 20 */
	    अचिन्हित दीर्घ video_num_rows;	/* 24 */
	    अचिन्हित दीर्घ video_x;		/* 28 */
	    अचिन्हित दीर्घ video_y;		/* 32 */
	    अचिन्हित दीर्घ memc_control_reg;	/* 36 */
	    अचिन्हित अक्षर soundशेष;		/* 40 */
	    अचिन्हित अक्षर adfsdrives;		/* 41 */
	    अचिन्हित अक्षर bytes_per_अक्षर_h;	/* 42 */
	    अचिन्हित अक्षर bytes_per_अक्षर_v;	/* 43 */
	    अचिन्हित दीर्घ pages_in_bank[4];	/* 44 */
	    अचिन्हित दीर्घ pages_in_vram;	/* 60 */
	    अचिन्हित दीर्घ initrd_start;		/* 64 */
	    अचिन्हित दीर्घ initrd_size;		/* 68 */
	    अचिन्हित दीर्घ rd_start;		/* 72 */
	    अचिन्हित दीर्घ प्रणाली_rev;		/* 76 */
	    अचिन्हित दीर्घ प्रणाली_serial_low;	/* 80 */
	    अचिन्हित दीर्घ प्रणाली_serial_high;	/* 84 */
	    अचिन्हित दीर्घ mem_fclk_21285;       /* 88 */
	पूर्ण s;
	अक्षर unused[256];
    पूर्ण u1;
    जोड़ अणु
	अक्षर paths[8][128];
	काष्ठा अणु
	    अचिन्हित दीर्घ magic;
	    अक्षर n[1024 - माप(अचिन्हित दीर्घ)];
	पूर्ण s;
    पूर्ण u2;
    अक्षर commandline[COMMAND_LINE_SIZE];
पूर्ण;

अटल काष्ठा tag * __init memtag(काष्ठा tag *tag, अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	tag = tag_next(tag);
	tag->hdr.tag = ATAG_MEM;
	tag->hdr.size = tag_size(tag_mem32);
	tag->u.mem.size = size;
	tag->u.mem.start = start;

	वापस tag;
पूर्ण

अटल व्योम __init build_tag_list(काष्ठा param_काष्ठा *params, व्योम *taglist)
अणु
	काष्ठा tag *tag = taglist;

	अगर (params->u1.s.page_size != PAGE_SIZE) अणु
		pr_warn("Warning: bad configuration page, trying to continue\n");
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "Converting old-style param struct to taglist\n");

#अगर_घोषित CONFIG_ARCH_NETWINDER
	अगर (params->u1.s.nr_pages != 0x02000 &&
	    params->u1.s.nr_pages != 0x04000 &&
	    params->u1.s.nr_pages != 0x08000 &&
	    params->u1.s.nr_pages != 0x10000) अणु
		pr_warn("Warning: bad NeTTrom parameters detected, using defaults\n");

		params->u1.s.nr_pages = 0x1000;	/* 16MB */
		params->u1.s.ramdisk_size = 0;
		params->u1.s.flags = FLAG_READONLY;
		params->u1.s.initrd_start = 0;
		params->u1.s.initrd_size = 0;
		params->u1.s.rd_start = 0;
	पूर्ण
#पूर्ण_अगर

	tag->hdr.tag  = ATAG_CORE;
	tag->hdr.size = tag_size(tag_core);
	tag->u.core.flags = params->u1.s.flags & FLAG_READONLY;
	tag->u.core.pagesize = params->u1.s.page_size;
	tag->u.core.rootdev = params->u1.s.rootdev;

	tag = tag_next(tag);
	tag->hdr.tag = ATAG_RAMDISK;
	tag->hdr.size = tag_size(tag_ramdisk);
	tag->u.ramdisk.flags = (params->u1.s.flags & FLAG_RDLOAD ? 1 : 0) |
			       (params->u1.s.flags & FLAG_RDPROMPT ? 2 : 0);
	tag->u.ramdisk.size  = params->u1.s.ramdisk_size;
	tag->u.ramdisk.start = params->u1.s.rd_start;

	tag = tag_next(tag);
	tag->hdr.tag = ATAG_INITRD;
	tag->hdr.size = tag_size(tag_initrd);
	tag->u.initrd.start = params->u1.s.initrd_start;
	tag->u.initrd.size  = params->u1.s.initrd_size;

	tag = tag_next(tag);
	tag->hdr.tag = ATAG_SERIAL;
	tag->hdr.size = tag_size(tag_serialnr);
	tag->u.serialnr.low = params->u1.s.प्रणाली_serial_low;
	tag->u.serialnr.high = params->u1.s.प्रणाली_serial_high;

	tag = tag_next(tag);
	tag->hdr.tag = ATAG_REVISION;
	tag->hdr.size = tag_size(tag_revision);
	tag->u.revision.rev = params->u1.s.प्रणाली_rev;

#अगर_घोषित CONFIG_ARCH_ACORN
	अगर (machine_is_riscpc()) अणु
		पूर्णांक i;
		क्रम (i = 0; i < 4; i++)
			tag = memtag(tag, PHYS_OFFSET + (i << 26),
				 params->u1.s.pages_in_bank[i] * PAGE_SIZE);
	पूर्ण अन्यथा
#पूर्ण_अगर
	tag = memtag(tag, PHYS_OFFSET, params->u1.s.nr_pages * PAGE_SIZE);

#अगर_घोषित CONFIG_FOOTBRIDGE
	अगर (params->u1.s.mem_fclk_21285) अणु
		tag = tag_next(tag);
		tag->hdr.tag = ATAG_MEMCLK;
		tag->hdr.size = tag_size(tag_memclk);
		tag->u.memclk.fmemclk = params->u1.s.mem_fclk_21285;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_EBSA285
	अगर (machine_is_ebsa285()) अणु
		tag = tag_next(tag);
		tag->hdr.tag = ATAG_VIDEOTEXT;
		tag->hdr.size = tag_size(tag_videotext);
		tag->u.videotext.x            = params->u1.s.video_x;
		tag->u.videotext.y            = params->u1.s.video_y;
		tag->u.videotext.video_page   = 0;
		tag->u.videotext.video_mode   = 0;
		tag->u.videotext.video_cols   = params->u1.s.video_num_cols;
		tag->u.videotext.video_ega_bx = 0;
		tag->u.videotext.video_lines  = params->u1.s.video_num_rows;
		tag->u.videotext.video_isvga  = 1;
		tag->u.videotext.video_poपूर्णांकs = 8;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_ACORN
	tag = tag_next(tag);
	tag->hdr.tag = ATAG_ACORN;
	tag->hdr.size = tag_size(tag_acorn);
	tag->u.acorn.memc_control_reg = params->u1.s.memc_control_reg;
	tag->u.acorn.vram_pages       = params->u1.s.pages_in_vram;
	tag->u.acorn.soundशेष     = params->u1.s.soundशेष;
	tag->u.acorn.adfsdrives       = params->u1.s.adfsdrives;
#पूर्ण_अगर

	tag = tag_next(tag);
	tag->hdr.tag = ATAG_CMDLINE;
	tag->hdr.size = (म_माप(params->commandline) + 3 +
			 माप(काष्ठा tag_header)) >> 2;
	म_नकल(tag->u.cmdline.cmdline, params->commandline);

	tag = tag_next(tag);
	tag->hdr.tag = ATAG_NONE;
	tag->hdr.size = 0;

	स_हटाओ(params, taglist, ((पूर्णांक)tag) - ((पूर्णांक)taglist) +
				 माप(काष्ठा tag_header));
पूर्ण

व्योम __init convert_to_tag_list(काष्ठा tag *tags)
अणु
	काष्ठा param_काष्ठा *params = (काष्ठा param_काष्ठा *)tags;
	build_tag_list(params, &params->u2);
पूर्ण
