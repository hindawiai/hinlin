<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013
 * Phillip Lougher <phillip@squashfs.org.uk>
 */

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/bपन.स>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "decompressor.h"
#समावेश "squashfs.h"

/*
 * This file implements single-thपढ़ोed decompression in the
 * decompressor framework
 */

काष्ठा squashfs_stream अणु
	व्योम		*stream;
	काष्ठा mutex	mutex;
पूर्ण;

व्योम *squashfs_decompressor_create(काष्ठा squashfs_sb_info *msblk,
						व्योम *comp_opts)
अणु
	काष्ठा squashfs_stream *stream;
	पूर्णांक err = -ENOMEM;

	stream = kदो_स्मृति(माप(*stream), GFP_KERNEL);
	अगर (stream == शून्य)
		जाओ out;

	stream->stream = msblk->decompressor->init(msblk, comp_opts);
	अगर (IS_ERR(stream->stream)) अणु
		err = PTR_ERR(stream->stream);
		जाओ out;
	पूर्ण

	kमुक्त(comp_opts);
	mutex_init(&stream->mutex);
	वापस stream;

out:
	kमुक्त(stream);
	वापस ERR_PTR(err);
पूर्ण

व्योम squashfs_decompressor_destroy(काष्ठा squashfs_sb_info *msblk)
अणु
	काष्ठा squashfs_stream *stream = msblk->stream;

	अगर (stream) अणु
		msblk->decompressor->मुक्त(stream->stream);
		kमुक्त(stream);
	पूर्ण
पूर्ण

पूर्णांक squashfs_decompress(काष्ठा squashfs_sb_info *msblk, काष्ठा bio *bio,
			पूर्णांक offset, पूर्णांक length,
			काष्ठा squashfs_page_actor *output)
अणु
	पूर्णांक res;
	काष्ठा squashfs_stream *stream = msblk->stream;

	mutex_lock(&stream->mutex);
	res = msblk->decompressor->decompress(msblk, stream->stream, bio,
		offset, length, output);
	mutex_unlock(&stream->mutex);

	अगर (res < 0)
		ERROR("%s decompression failed, data probably corrupt\n",
			msblk->decompressor->name);

	वापस res;
पूर्ण

पूर्णांक squashfs_max_decompressors(व्योम)
अणु
	वापस 1;
पूर्ण
