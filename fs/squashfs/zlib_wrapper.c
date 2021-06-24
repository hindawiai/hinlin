<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * zlib_wrapper.c
 */


#समावेश <linux/mutex.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/zlib.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"
#समावेश "decompressor.h"
#समावेश "page_actor.h"

अटल व्योम *zlib_init(काष्ठा squashfs_sb_info *dummy, व्योम *buff)
अणु
	z_stream *stream = kदो_स्मृति(माप(z_stream), GFP_KERNEL);
	अगर (stream == शून्य)
		जाओ failed;
	stream->workspace = vदो_स्मृति(zlib_inflate_workspacesize());
	अगर (stream->workspace == शून्य)
		जाओ failed;

	वापस stream;

failed:
	ERROR("Failed to allocate zlib workspace\n");
	kमुक्त(stream);
	वापस ERR_PTR(-ENOMEM);
पूर्ण


अटल व्योम zlib_मुक्त(व्योम *strm)
अणु
	z_stream *stream = strm;

	अगर (stream)
		vमुक्त(stream->workspace);
	kमुक्त(stream);
पूर्ण


अटल पूर्णांक zlib_uncompress(काष्ठा squashfs_sb_info *msblk, व्योम *strm,
	काष्ठा bio *bio, पूर्णांक offset, पूर्णांक length,
	काष्ठा squashfs_page_actor *output)
अणु
	काष्ठा bvec_iter_all iter_all = अणुपूर्ण;
	काष्ठा bio_vec *bvec = bvec_init_iter_all(&iter_all);
	पूर्णांक zlib_init = 0, error = 0;
	z_stream *stream = strm;

	stream->avail_out = PAGE_SIZE;
	stream->next_out = squashfs_first_page(output);
	stream->avail_in = 0;

	क्रम (;;) अणु
		पूर्णांक zlib_err;

		अगर (stream->avail_in == 0) अणु
			स्थिर व्योम *data;
			पूर्णांक avail;

			अगर (!bio_next_segment(bio, &iter_all)) अणु
				/* Z_STREAM_END must be reached. */
				error = -EIO;
				अवरोध;
			पूर्ण

			avail = min(length, ((पूर्णांक)bvec->bv_len) - offset);
			data = page_address(bvec->bv_page) + bvec->bv_offset;
			length -= avail;
			stream->next_in = data + offset;
			stream->avail_in = avail;
			offset = 0;
		पूर्ण

		अगर (stream->avail_out == 0) अणु
			stream->next_out = squashfs_next_page(output);
			अगर (stream->next_out != शून्य)
				stream->avail_out = PAGE_SIZE;
		पूर्ण

		अगर (!zlib_init) अणु
			zlib_err = zlib_inflateInit(stream);
			अगर (zlib_err != Z_OK) अणु
				error = -EIO;
				अवरोध;
			पूर्ण
			zlib_init = 1;
		पूर्ण

		zlib_err = zlib_inflate(stream, Z_SYNC_FLUSH);
		अगर (zlib_err == Z_STREAM_END)
			अवरोध;
		अगर (zlib_err != Z_OK) अणु
			error = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	squashfs_finish_page(output);

	अगर (!error)
		अगर (zlib_inflateEnd(stream) != Z_OK)
			error = -EIO;

	वापस error ? error : stream->total_out;
पूर्ण

स्थिर काष्ठा squashfs_decompressor squashfs_zlib_comp_ops = अणु
	.init = zlib_init,
	.मुक्त = zlib_मुक्त,
	.decompress = zlib_uncompress,
	.id = ZLIB_COMPRESSION,
	.name = "zlib",
	.supported = 1
पूर्ण;

