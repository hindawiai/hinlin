<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * decompressor.c
 */

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/buffer_head.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "decompressor.h"
#समावेश "squashfs.h"
#समावेश "page_actor.h"

/*
 * This file (and decompressor.h) implements a decompressor framework क्रम
 * Squashfs, allowing multiple decompressors to be easily supported
 */

अटल स्थिर काष्ठा squashfs_decompressor squashfs_lzma_unsupported_comp_ops = अणु
	शून्य, शून्य, शून्य, शून्य, LZMA_COMPRESSION, "lzma", 0
पूर्ण;

#अगर_अघोषित CONFIG_SQUASHFS_LZ4
अटल स्थिर काष्ठा squashfs_decompressor squashfs_lz4_comp_ops = अणु
	शून्य, शून्य, शून्य, शून्य, LZ4_COMPRESSION, "lz4", 0
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित CONFIG_SQUASHFS_LZO
अटल स्थिर काष्ठा squashfs_decompressor squashfs_lzo_comp_ops = अणु
	शून्य, शून्य, शून्य, शून्य, LZO_COMPRESSION, "lzo", 0
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित CONFIG_SQUASHFS_XZ
अटल स्थिर काष्ठा squashfs_decompressor squashfs_xz_comp_ops = अणु
	शून्य, शून्य, शून्य, शून्य, XZ_COMPRESSION, "xz", 0
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित CONFIG_SQUASHFS_ZLIB
अटल स्थिर काष्ठा squashfs_decompressor squashfs_zlib_comp_ops = अणु
	शून्य, शून्य, शून्य, शून्य, ZLIB_COMPRESSION, "zlib", 0
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित CONFIG_SQUASHFS_ZSTD
अटल स्थिर काष्ठा squashfs_decompressor squashfs_zstd_comp_ops = अणु
	शून्य, शून्य, शून्य, शून्य, ZSTD_COMPRESSION, "zstd", 0
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा squashfs_decompressor squashfs_unknown_comp_ops = अणु
	शून्य, शून्य, शून्य, शून्य, 0, "unknown", 0
पूर्ण;

अटल स्थिर काष्ठा squashfs_decompressor *decompressor[] = अणु
	&squashfs_zlib_comp_ops,
	&squashfs_lz4_comp_ops,
	&squashfs_lzo_comp_ops,
	&squashfs_xz_comp_ops,
	&squashfs_lzma_unsupported_comp_ops,
	&squashfs_zstd_comp_ops,
	&squashfs_unknown_comp_ops
पूर्ण;


स्थिर काष्ठा squashfs_decompressor *squashfs_lookup_decompressor(पूर्णांक id)
अणु
	पूर्णांक i;

	क्रम (i = 0; decompressor[i]->id; i++)
		अगर (id == decompressor[i]->id)
			अवरोध;

	वापस decompressor[i];
पूर्ण


अटल व्योम *get_comp_opts(काष्ठा super_block *sb, अचिन्हित लघु flags)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	व्योम *buffer = शून्य, *comp_opts;
	काष्ठा squashfs_page_actor *actor = शून्य;
	पूर्णांक length = 0;

	/*
	 * Read decompressor specअगरic options from file प्रणाली अगर present
	 */
	अगर (SQUASHFS_COMP_OPTS(flags)) अणु
		buffer = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
		अगर (buffer == शून्य) अणु
			comp_opts = ERR_PTR(-ENOMEM);
			जाओ out;
		पूर्ण

		actor = squashfs_page_actor_init(&buffer, 1, 0);
		अगर (actor == शून्य) अणु
			comp_opts = ERR_PTR(-ENOMEM);
			जाओ out;
		पूर्ण

		length = squashfs_पढ़ो_data(sb,
			माप(काष्ठा squashfs_super_block), 0, शून्य, actor);

		अगर (length < 0) अणु
			comp_opts = ERR_PTR(length);
			जाओ out;
		पूर्ण
	पूर्ण

	comp_opts = squashfs_comp_opts(msblk, buffer, length);

out:
	kमुक्त(actor);
	kमुक्त(buffer);
	वापस comp_opts;
पूर्ण


व्योम *squashfs_decompressor_setup(काष्ठा super_block *sb, अचिन्हित लघु flags)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	व्योम *stream, *comp_opts = get_comp_opts(sb, flags);

	अगर (IS_ERR(comp_opts))
		वापस comp_opts;

	stream = squashfs_decompressor_create(msblk, comp_opts);
	अगर (IS_ERR(stream))
		kमुक्त(comp_opts);

	वापस stream;
पूर्ण
