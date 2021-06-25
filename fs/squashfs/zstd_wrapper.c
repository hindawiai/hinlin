<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * zstd_wrapper.c
 */

#समावेश <linux/mutex.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/zstd.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"
#समावेश "decompressor.h"
#समावेश "page_actor.h"

काष्ठा workspace अणु
	व्योम *mem;
	माप_प्रकार mem_size;
	माप_प्रकार winकरोw_size;
पूर्ण;

अटल व्योम *zstd_init(काष्ठा squashfs_sb_info *msblk, व्योम *buff)
अणु
	काष्ठा workspace *wksp = kदो_स्मृति(माप(*wksp), GFP_KERNEL);

	अगर (wksp == शून्य)
		जाओ failed;
	wksp->winकरोw_size = max_t(माप_प्रकार,
			msblk->block_size, SQUASHFS_METADATA_SIZE);
	wksp->mem_size = ZSTD_DStreamWorkspaceBound(wksp->winकरोw_size);
	wksp->mem = vदो_स्मृति(wksp->mem_size);
	अगर (wksp->mem == शून्य)
		जाओ failed;

	वापस wksp;

failed:
	ERROR("Failed to allocate zstd workspace\n");
	kमुक्त(wksp);
	वापस ERR_PTR(-ENOMEM);
पूर्ण


अटल व्योम zstd_मुक्त(व्योम *strm)
अणु
	काष्ठा workspace *wksp = strm;

	अगर (wksp)
		vमुक्त(wksp->mem);
	kमुक्त(wksp);
पूर्ण


अटल पूर्णांक zstd_uncompress(काष्ठा squashfs_sb_info *msblk, व्योम *strm,
	काष्ठा bio *bio, पूर्णांक offset, पूर्णांक length,
	काष्ठा squashfs_page_actor *output)
अणु
	काष्ठा workspace *wksp = strm;
	ZSTD_DStream *stream;
	माप_प्रकार total_out = 0;
	पूर्णांक error = 0;
	ZSTD_inBuffer in_buf = अणु शून्य, 0, 0 पूर्ण;
	ZSTD_outBuffer out_buf = अणु शून्य, 0, 0 पूर्ण;
	काष्ठा bvec_iter_all iter_all = अणुपूर्ण;
	काष्ठा bio_vec *bvec = bvec_init_iter_all(&iter_all);

	stream = ZSTD_initDStream(wksp->winकरोw_size, wksp->mem, wksp->mem_size);

	अगर (!stream) अणु
		ERROR("Failed to initialize zstd decompressor\n");
		वापस -EIO;
	पूर्ण

	out_buf.size = PAGE_SIZE;
	out_buf.dst = squashfs_first_page(output);

	क्रम (;;) अणु
		माप_प्रकार zstd_err;

		अगर (in_buf.pos == in_buf.size) अणु
			स्थिर व्योम *data;
			पूर्णांक avail;

			अगर (!bio_next_segment(bio, &iter_all)) अणु
				error = -EIO;
				अवरोध;
			पूर्ण

			avail = min(length, ((पूर्णांक)bvec->bv_len) - offset);
			data = page_address(bvec->bv_page) + bvec->bv_offset;
			length -= avail;
			in_buf.src = data + offset;
			in_buf.size = avail;
			in_buf.pos = 0;
			offset = 0;
		पूर्ण

		अगर (out_buf.pos == out_buf.size) अणु
			out_buf.dst = squashfs_next_page(output);
			अगर (out_buf.dst == शून्य) अणु
				/* Shouldn't run out of pages
				 * beक्रमe stream is करोne.
				 */
				error = -EIO;
				अवरोध;
			पूर्ण
			out_buf.pos = 0;
			out_buf.size = PAGE_SIZE;
		पूर्ण

		total_out -= out_buf.pos;
		zstd_err = ZSTD_decompressStream(stream, &out_buf, &in_buf);
		total_out += out_buf.pos; /* add the additional data produced */
		अगर (zstd_err == 0)
			अवरोध;

		अगर (ZSTD_isError(zstd_err)) अणु
			ERROR("zstd decompression error: %d\n",
					(पूर्णांक)ZSTD_getErrorCode(zstd_err));
			error = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	squashfs_finish_page(output);

	वापस error ? error : total_out;
पूर्ण

स्थिर काष्ठा squashfs_decompressor squashfs_zstd_comp_ops = अणु
	.init = zstd_init,
	.मुक्त = zstd_मुक्त,
	.decompress = zstd_uncompress,
	.id = ZSTD_COMPRESSION,
	.name = "zstd",
	.supported = 1
पूर्ण;
