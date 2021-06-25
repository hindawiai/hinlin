<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tag parsing.
 *
 * Copyright (C) 1995-2001 Russell King
 */

/*
 * This is the traditional way of passing data to the kernel at boot समय.  Rather
 * than passing a fixed inflexible काष्ठाure to the kernel, we pass a list
 * of variable-sized tags to the kernel.  The first tag must be a ATAG_CORE
 * tag क्रम the list to be recognised (to distinguish the tagged list from
 * a param_काष्ठा).  The list is terminated with a zero-length tag (this tag
 * is not parsed in any way).
 */

#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/memblock.h>
#समावेश <uapi/linux/mount.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "atags.h"

अटल अक्षर शेष_command_line[COMMAND_LINE_SIZE] __initdata = CONFIG_CMDLINE;

#अगर_अघोषित MEM_SIZE
#घोषणा MEM_SIZE	(16*1024*1024)
#पूर्ण_अगर

अटल काष्ठा अणु
	काष्ठा tag_header hdr1;
	काष्ठा tag_core   core;
	काष्ठा tag_header hdr2;
	काष्ठा tag_mem32  mem;
	काष्ठा tag_header hdr3;
पूर्ण शेष_tags __initdata = अणु
	अणु tag_size(tag_core), ATAG_CORE पूर्ण,
	अणु 1, PAGE_SIZE, 0xff पूर्ण,
	अणु tag_size(tag_mem32), ATAG_MEM पूर्ण,
	अणु MEM_SIZE पूर्ण,
	अणु 0, ATAG_NONE पूर्ण
पूर्ण;

अटल पूर्णांक __init parse_tag_core(स्थिर काष्ठा tag *tag)
अणु
	अगर (tag->hdr.size > 2) अणु
		अगर ((tag->u.core.flags & 1) == 0)
			root_mountflags &= ~MS_RDONLY;
		ROOT_DEV = old_decode_dev(tag->u.core.rootdev);
	पूर्ण
	वापस 0;
पूर्ण

__tagtable(ATAG_CORE, parse_tag_core);

अटल पूर्णांक __init parse_tag_mem32(स्थिर काष्ठा tag *tag)
अणु
	वापस arm_add_memory(tag->u.mem.start, tag->u.mem.size);
पूर्ण

__tagtable(ATAG_MEM, parse_tag_mem32);

#अगर defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_DUMMY_CONSOLE)
अटल पूर्णांक __init parse_tag_videotext(स्थिर काष्ठा tag *tag)
अणु
	screen_info.orig_x            = tag->u.videotext.x;
	screen_info.orig_y            = tag->u.videotext.y;
	screen_info.orig_video_page   = tag->u.videotext.video_page;
	screen_info.orig_video_mode   = tag->u.videotext.video_mode;
	screen_info.orig_video_cols   = tag->u.videotext.video_cols;
	screen_info.orig_video_ega_bx = tag->u.videotext.video_ega_bx;
	screen_info.orig_video_lines  = tag->u.videotext.video_lines;
	screen_info.orig_video_isVGA  = tag->u.videotext.video_isvga;
	screen_info.orig_video_poपूर्णांकs = tag->u.videotext.video_poपूर्णांकs;
	वापस 0;
पूर्ण

__tagtable(ATAG_VIDEOTEXT, parse_tag_videotext);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_DEV_RAM
अटल पूर्णांक __init parse_tag_ramdisk(स्थिर काष्ठा tag *tag)
अणु
	rd_image_start = tag->u.ramdisk.start;

	अगर (tag->u.ramdisk.size)
		rd_size = tag->u.ramdisk.size;

	वापस 0;
पूर्ण

__tagtable(ATAG_RAMDISK, parse_tag_ramdisk);
#पूर्ण_अगर

अटल पूर्णांक __init parse_tag_serialnr(स्थिर काष्ठा tag *tag)
अणु
	प्रणाली_serial_low = tag->u.serialnr.low;
	प्रणाली_serial_high = tag->u.serialnr.high;
	वापस 0;
पूर्ण

__tagtable(ATAG_SERIAL, parse_tag_serialnr);

अटल पूर्णांक __init parse_tag_revision(स्थिर काष्ठा tag *tag)
अणु
	प्रणाली_rev = tag->u.revision.rev;
	वापस 0;
पूर्ण

__tagtable(ATAG_REVISION, parse_tag_revision);

अटल पूर्णांक __init parse_tag_cmdline(स्थिर काष्ठा tag *tag)
अणु
#अगर defined(CONFIG_CMDLINE_EXTEND)
	strlcat(शेष_command_line, " ", COMMAND_LINE_SIZE);
	strlcat(शेष_command_line, tag->u.cmdline.cmdline,
		COMMAND_LINE_SIZE);
#या_अगर defined(CONFIG_CMDLINE_FORCE)
	pr_warn("Ignoring tag cmdline (using the default kernel command line)\n");
#अन्यथा
	strlcpy(शेष_command_line, tag->u.cmdline.cmdline,
		COMMAND_LINE_SIZE);
#पूर्ण_अगर
	वापस 0;
पूर्ण

__tagtable(ATAG_CMDLINE, parse_tag_cmdline);

/*
 * Scan the tag table क्रम this tag, and call its parse function.
 * The tag table is built by the linker from all the __tagtable
 * declarations.
 */
अटल पूर्णांक __init parse_tag(स्थिर काष्ठा tag *tag)
अणु
	बाह्य काष्ठा tagtable __tagtable_begin, __tagtable_end;
	काष्ठा tagtable *t;

	क्रम (t = &__tagtable_begin; t < &__tagtable_end; t++)
		अगर (tag->hdr.tag == t->tag) अणु
			t->parse(tag);
			अवरोध;
		पूर्ण

	वापस t < &__tagtable_end;
पूर्ण

/*
 * Parse all tags in the list, checking both the global and architecture
 * specअगरic tag tables.
 */
अटल व्योम __init parse_tags(स्थिर काष्ठा tag *t)
अणु
	क्रम (; t->hdr.size; t = tag_next(t))
		अगर (!parse_tag(t))
			pr_warn("Ignoring unrecognised tag 0x%08x\n",
				t->hdr.tag);
पूर्ण

अटल व्योम __init squash_mem_tags(काष्ठा tag *tag)
अणु
	क्रम (; tag->hdr.size; tag = tag_next(tag))
		अगर (tag->hdr.tag == ATAG_MEM)
			tag->hdr.tag = ATAG_NONE;
पूर्ण

स्थिर काष्ठा machine_desc * __init
setup_machine_tags(व्योम *atags_vaddr, अचिन्हित पूर्णांक machine_nr)
अणु
	काष्ठा tag *tags = (काष्ठा tag *)&शेष_tags;
	स्थिर काष्ठा machine_desc *mdesc = शून्य, *p;
	अक्षर *from = शेष_command_line;

	शेष_tags.mem.start = PHYS_OFFSET;

	/*
	 * locate machine in the list of supported machines.
	 */
	क्रम_each_machine_desc(p)
		अगर (machine_nr == p->nr) अणु
			pr_info("Machine: %s\n", p->name);
			mdesc = p;
			अवरोध;
		पूर्ण

	अगर (!mdesc)
		वापस शून्य;

	अगर (atags_vaddr)
		tags = atags_vaddr;
	अन्यथा अगर (mdesc->atag_offset)
		tags = (व्योम *)(PAGE_OFFSET + mdesc->atag_offset);

#अगर defined(CONFIG_DEPRECATED_PARAM_STRUCT)
	/*
	 * If we have the old style parameters, convert them to
	 * a tag list.
	 */
	अगर (tags->hdr.tag != ATAG_CORE)
		convert_to_tag_list(tags);
#पूर्ण_अगर
	अगर (tags->hdr.tag != ATAG_CORE) अणु
		early_prपूर्णांक("Warning: Neither atags nor dtb found\n");
		tags = (काष्ठा tag *)&शेष_tags;
	पूर्ण

	अगर (mdesc->fixup)
		mdesc->fixup(tags, &from);

	अगर (tags->hdr.tag == ATAG_CORE) अणु
		अगर (memblock_phys_mem_size())
			squash_mem_tags(tags);
		save_atags(tags);
		parse_tags(tags);
	पूर्ण

	/* parse_early_param needs a boot_command_line */
	strlcpy(boot_command_line, from, COMMAND_LINE_SIZE);

	वापस mdesc;
पूर्ण
