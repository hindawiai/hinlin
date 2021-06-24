<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * xz_wrapper.c
 */


#समावेश <linux/mutex.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/xz.h>
#समावेश <linux/bitops.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"
#समावेश "decompressor.h"
#समावेश "page_actor.h"

काष्ठा squashfs_xz अणु
	काष्ठा xz_dec *state;
	काष्ठा xz_buf buf;
पूर्ण;

काष्ठा disk_comp_opts अणु
	__le32 dictionary_size;
	__le32 flags;
पूर्ण;

काष्ठा comp_opts अणु
	पूर्णांक dict_size;
पूर्ण;

अटल व्योम *squashfs_xz_comp_opts(काष्ठा squashfs_sb_info *msblk,
	व्योम *buff, पूर्णांक len)
अणु
	काष्ठा disk_comp_opts *comp_opts = buff;
	काष्ठा comp_opts *opts;
	पूर्णांक err = 0, n;

	opts = kदो_स्मृति(माप(*opts), GFP_KERNEL);
	अगर (opts == शून्य) अणु
		err = -ENOMEM;
		जाओ out2;
	पूर्ण

	अगर (comp_opts) अणु
		/* check compressor options are the expected length */
		अगर (len < माप(*comp_opts)) अणु
			err = -EIO;
			जाओ out;
		पूर्ण

		opts->dict_size = le32_to_cpu(comp_opts->dictionary_size);

		/* the dictionary size should be 2^n or 2^n+2^(n+1) */
		n = ffs(opts->dict_size) - 1;
		अगर (opts->dict_size != (1 << n) && opts->dict_size != (1 << n) +
						(1 << (n + 1))) अणु
			err = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		/* use शेषs */
		opts->dict_size = max_t(पूर्णांक, msblk->block_size,
							SQUASHFS_METADATA_SIZE);

	वापस opts;

out:
	kमुक्त(opts);
out2:
	वापस ERR_PTR(err);
पूर्ण


अटल व्योम *squashfs_xz_init(काष्ठा squashfs_sb_info *msblk, व्योम *buff)
अणु
	काष्ठा comp_opts *comp_opts = buff;
	काष्ठा squashfs_xz *stream;
	पूर्णांक err;

	stream = kदो_स्मृति(माप(*stream), GFP_KERNEL);
	अगर (stream == शून्य) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	stream->state = xz_dec_init(XZ_PREALLOC, comp_opts->dict_size);
	अगर (stream->state == शून्य) अणु
		kमुक्त(stream);
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	वापस stream;

failed:
	ERROR("Failed to initialise xz decompressor\n");
	वापस ERR_PTR(err);
पूर्ण


अटल व्योम squashfs_xz_मुक्त(व्योम *strm)
अणु
	काष्ठा squashfs_xz *stream = strm;

	अगर (stream) अणु
		xz_dec_end(stream->state);
		kमुक्त(stream);
	पूर्ण
पूर्ण


अटल पूर्णांक squashfs_xz_uncompress(काष्ठा squashfs_sb_info *msblk, व्योम *strm,
	काष्ठा bio *bio, पूर्णांक offset, पूर्णांक length,
	काष्ठा squashfs_page_actor *output)
अणु
	काष्ठा bvec_iter_all iter_all = अणुपूर्ण;
	काष्ठा bio_vec *bvec = bvec_init_iter_all(&iter_all);
	पूर्णांक total = 0, error = 0;
	काष्ठा squashfs_xz *stream = strm;

	xz_dec_reset(stream->state);
	stream->buf.in_pos = 0;
	stream->buf.in_size = 0;
	stream->buf.out_pos = 0;
	stream->buf.out_size = PAGE_SIZE;
	stream->buf.out = squashfs_first_page(output);

	क्रम (;;) अणु
		क्रमागत xz_ret xz_err;

		अगर (stream->buf.in_pos == stream->buf.in_size) अणु
			स्थिर व्योम *data;
			पूर्णांक avail;

			अगर (!bio_next_segment(bio, &iter_all)) अणु
				/* XZ_STREAM_END must be reached. */
				error = -EIO;
				अवरोध;
			पूर्ण

			avail = min(length, ((पूर्णांक)bvec->bv_len) - offset);
			data = page_address(bvec->bv_page) + bvec->bv_offset;
			length -= avail;
			stream->buf.in = data + offset;
			stream->buf.in_size = avail;
			stream->buf.in_pos = 0;
			offset = 0;
		पूर्ण

		अगर (stream->buf.out_pos == stream->buf.out_size) अणु
			stream->buf.out = squashfs_next_page(output);
			अगर (stream->buf.out != शून्य) अणु
				stream->buf.out_pos = 0;
				total += PAGE_SIZE;
			पूर्ण
		पूर्ण

		xz_err = xz_dec_run(stream->state, &stream->buf);
		अगर (xz_err == XZ_STREAM_END)
			अवरोध;
		अगर (xz_err != XZ_OK) अणु
			error = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	squashfs_finish_page(output);

	वापस error ? error : total + stream->buf.out_pos;
पूर्ण

स्थिर काष्ठा squashfs_decompressor squashfs_xz_comp_ops = अणु
	.init = squashfs_xz_init,
	.comp_opts = squashfs_xz_comp_opts,
	.मुक्त = squashfs_xz_मुक्त,
	.decompress = squashfs_xz_uncompress,
	.id = XZ_COMPRESSION,
	.name = "xz",
	.supported = 1
पूर्ण;
