<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * uncompress.c
 *
 * (C) Copyright 1999 Linus Torvalds
 *
 * cramfs पूर्णांकerfaces to the uncompression library. There's really just
 * three entrypoपूर्णांकs:
 *
 *  - cramfs_uncompress_init() - called to initialize the thing.
 *  - cramfs_uncompress_निकास() - tell me when you're करोne
 *  - cramfs_uncompress_block() - uncompress a block.
 *
 * NOTE NOTE NOTE! The uncompression is entirely single-thपढ़ोed. We
 * only have one stream, and we'll initialize it only once even अगर it
 * then is used by multiple fileप्रणालीs.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/zlib.h>
#समावेश "internal.h"

अटल z_stream stream;
अटल पूर्णांक initialized;

/* Returns length of decompressed data. */
पूर्णांक cramfs_uncompress_block(व्योम *dst, पूर्णांक dstlen, व्योम *src, पूर्णांक srclen)
अणु
	पूर्णांक err;

	stream.next_in = src;
	stream.avail_in = srclen;

	stream.next_out = dst;
	stream.avail_out = dstlen;

	err = zlib_inflateReset(&stream);
	अगर (err != Z_OK) अणु
		pr_err("zlib_inflateReset error %d\n", err);
		zlib_inflateEnd(&stream);
		zlib_inflateInit(&stream);
	पूर्ण

	err = zlib_inflate(&stream, Z_FINISH);
	अगर (err != Z_STREAM_END)
		जाओ err;
	वापस stream.total_out;

err:
	pr_err("Error %d while decompressing!\n", err);
	pr_err("%p(%d)->%p(%d)\n", src, srclen, dst, dstlen);
	वापस -EIO;
पूर्ण

पूर्णांक cramfs_uncompress_init(व्योम)
अणु
	अगर (!initialized++) अणु
		stream.workspace = vदो_स्मृति(zlib_inflate_workspacesize());
		अगर (!stream.workspace) अणु
			initialized = 0;
			वापस -ENOMEM;
		पूर्ण
		stream.next_in = शून्य;
		stream.avail_in = 0;
		zlib_inflateInit(&stream);
	पूर्ण
	वापस 0;
पूर्ण

व्योम cramfs_uncompress_निकास(व्योम)
अणु
	अगर (!--initialized) अणु
		zlib_inflateEnd(&stream);
		vमुक्त(stream.workspace);
	पूर्ण
पूर्ण
