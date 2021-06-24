<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013, 2014
 * Phillip Lougher <phillip@squashfs.org.uk>
 */

#समावेश <linux/bपन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/lz4.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"
#समावेश "decompressor.h"
#समावेश "page_actor.h"

#घोषणा LZ4_LEGACY	1

काष्ठा lz4_comp_opts अणु
	__le32 version;
	__le32 flags;
पूर्ण;

काष्ठा squashfs_lz4 अणु
	व्योम *input;
	व्योम *output;
पूर्ण;


अटल व्योम *lz4_comp_opts(काष्ठा squashfs_sb_info *msblk,
	व्योम *buff, पूर्णांक len)
अणु
	काष्ठा lz4_comp_opts *comp_opts = buff;

	/* LZ4 compressed fileप्रणालीs always have compression options */
	अगर (comp_opts == शून्य || len < माप(*comp_opts))
		वापस ERR_PTR(-EIO);

	अगर (le32_to_cpu(comp_opts->version) != LZ4_LEGACY) अणु
		/* LZ4 क्रमmat currently used by the kernel is the 'legacy'
		 * क्रमmat */
		ERROR("Unknown LZ4 version\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस शून्य;
पूर्ण


अटल व्योम *lz4_init(काष्ठा squashfs_sb_info *msblk, व्योम *buff)
अणु
	पूर्णांक block_size = max_t(पूर्णांक, msblk->block_size, SQUASHFS_METADATA_SIZE);
	काष्ठा squashfs_lz4 *stream;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (stream == शून्य)
		जाओ failed;
	stream->input = vदो_स्मृति(block_size);
	अगर (stream->input == शून्य)
		जाओ failed2;
	stream->output = vदो_स्मृति(block_size);
	अगर (stream->output == शून्य)
		जाओ failed3;

	वापस stream;

failed3:
	vमुक्त(stream->input);
failed2:
	kमुक्त(stream);
failed:
	ERROR("Failed to initialise LZ4 decompressor\n");
	वापस ERR_PTR(-ENOMEM);
पूर्ण


अटल व्योम lz4_मुक्त(व्योम *strm)
अणु
	काष्ठा squashfs_lz4 *stream = strm;

	अगर (stream) अणु
		vमुक्त(stream->input);
		vमुक्त(stream->output);
	पूर्ण
	kमुक्त(stream);
पूर्ण


अटल पूर्णांक lz4_uncompress(काष्ठा squashfs_sb_info *msblk, व्योम *strm,
	काष्ठा bio *bio, पूर्णांक offset, पूर्णांक length,
	काष्ठा squashfs_page_actor *output)
अणु
	काष्ठा bvec_iter_all iter_all = अणुपूर्ण;
	काष्ठा bio_vec *bvec = bvec_init_iter_all(&iter_all);
	काष्ठा squashfs_lz4 *stream = strm;
	व्योम *buff = stream->input, *data;
	पूर्णांक bytes = length, res;

	जबतक (bio_next_segment(bio, &iter_all)) अणु
		पूर्णांक avail = min(bytes, ((पूर्णांक)bvec->bv_len) - offset);

		data = page_address(bvec->bv_page) + bvec->bv_offset;
		स_नकल(buff, data + offset, avail);
		buff += avail;
		bytes -= avail;
		offset = 0;
	पूर्ण

	res = LZ4_decompress_safe(stream->input, stream->output,
		length, output->length);

	अगर (res < 0)
		वापस -EIO;

	bytes = res;
	data = squashfs_first_page(output);
	buff = stream->output;
	जबतक (data) अणु
		अगर (bytes <= PAGE_SIZE) अणु
			स_नकल(data, buff, bytes);
			अवरोध;
		पूर्ण
		स_नकल(data, buff, PAGE_SIZE);
		buff += PAGE_SIZE;
		bytes -= PAGE_SIZE;
		data = squashfs_next_page(output);
	पूर्ण
	squashfs_finish_page(output);

	वापस res;
पूर्ण

स्थिर काष्ठा squashfs_decompressor squashfs_lz4_comp_ops = अणु
	.init = lz4_init,
	.comp_opts = lz4_comp_opts,
	.मुक्त = lz4_मुक्त,
	.decompress = lz4_uncompress,
	.id = LZ4_COMPRESSION,
	.name = "lz4",
	.supported = 1
पूर्ण;
