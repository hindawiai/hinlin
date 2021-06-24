<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2010 LG Electronics
 * Chan Jeong <chan.jeong@lge.com>
 *
 * lzo_wrapper.c
 */

#समावेश <linux/mutex.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/lzo.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"
#समावेश "decompressor.h"
#समावेश "page_actor.h"

काष्ठा squashfs_lzo अणु
	व्योम	*input;
	व्योम	*output;
पूर्ण;

अटल व्योम *lzo_init(काष्ठा squashfs_sb_info *msblk, व्योम *buff)
अणु
	पूर्णांक block_size = max_t(पूर्णांक, msblk->block_size, SQUASHFS_METADATA_SIZE);

	काष्ठा squashfs_lzo *stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (stream == शून्य)
		जाओ failed;
	stream->input = vदो_स्मृति(block_size);
	अगर (stream->input == शून्य)
		जाओ failed;
	stream->output = vदो_स्मृति(block_size);
	अगर (stream->output == शून्य)
		जाओ failed2;

	वापस stream;

failed2:
	vमुक्त(stream->input);
failed:
	ERROR("Failed to allocate lzo workspace\n");
	kमुक्त(stream);
	वापस ERR_PTR(-ENOMEM);
पूर्ण


अटल व्योम lzo_मुक्त(व्योम *strm)
अणु
	काष्ठा squashfs_lzo *stream = strm;

	अगर (stream) अणु
		vमुक्त(stream->input);
		vमुक्त(stream->output);
	पूर्ण
	kमुक्त(stream);
पूर्ण


अटल पूर्णांक lzo_uncompress(काष्ठा squashfs_sb_info *msblk, व्योम *strm,
	काष्ठा bio *bio, पूर्णांक offset, पूर्णांक length,
	काष्ठा squashfs_page_actor *output)
अणु
	काष्ठा bvec_iter_all iter_all = अणुपूर्ण;
	काष्ठा bio_vec *bvec = bvec_init_iter_all(&iter_all);
	काष्ठा squashfs_lzo *stream = strm;
	व्योम *buff = stream->input, *data;
	पूर्णांक bytes = length, res;
	माप_प्रकार out_len = output->length;

	जबतक (bio_next_segment(bio, &iter_all)) अणु
		पूर्णांक avail = min(bytes, ((पूर्णांक)bvec->bv_len) - offset);

		data = page_address(bvec->bv_page) + bvec->bv_offset;
		स_नकल(buff, data + offset, avail);
		buff += avail;
		bytes -= avail;
		offset = 0;
	पूर्ण

	res = lzo1x_decompress_safe(stream->input, (माप_प्रकार)length,
					stream->output, &out_len);
	अगर (res != LZO_E_OK)
		जाओ failed;

	res = bytes = (पूर्णांक)out_len;
	data = squashfs_first_page(output);
	buff = stream->output;
	जबतक (data) अणु
		अगर (bytes <= PAGE_SIZE) अणु
			स_नकल(data, buff, bytes);
			अवरोध;
		पूर्ण अन्यथा अणु
			स_नकल(data, buff, PAGE_SIZE);
			buff += PAGE_SIZE;
			bytes -= PAGE_SIZE;
			data = squashfs_next_page(output);
		पूर्ण
	पूर्ण
	squashfs_finish_page(output);

	वापस res;

failed:
	वापस -EIO;
पूर्ण

स्थिर काष्ठा squashfs_decompressor squashfs_lzo_comp_ops = अणु
	.init = lzo_init,
	.मुक्त = lzo_मुक्त,
	.decompress = lzo_uncompress,
	.id = LZO_COMPRESSION,
	.name = "lzo",
	.supported = 1
पूर्ण;
