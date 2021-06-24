<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * block.c
 */

/*
 * This file implements the low-level routines to पढ़ो and decompress
 * datablocks and metadata blocks.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/bपन.स>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"
#समावेश "decompressor.h"
#समावेश "page_actor.h"

/*
 * Returns the amount of bytes copied to the page actor.
 */
अटल पूर्णांक copy_bio_to_actor(काष्ठा bio *bio,
			     काष्ठा squashfs_page_actor *actor,
			     पूर्णांक offset, पूर्णांक req_length)
अणु
	व्योम *actor_addr = squashfs_first_page(actor);
	काष्ठा bvec_iter_all iter_all = अणुपूर्ण;
	काष्ठा bio_vec *bvec = bvec_init_iter_all(&iter_all);
	पूर्णांक copied_bytes = 0;
	पूर्णांक actor_offset = 0;

	अगर (WARN_ON_ONCE(!bio_next_segment(bio, &iter_all)))
		वापस 0;

	जबतक (copied_bytes < req_length) अणु
		पूर्णांक bytes_to_copy = min_t(पूर्णांक, bvec->bv_len - offset,
					  PAGE_SIZE - actor_offset);

		bytes_to_copy = min_t(पूर्णांक, bytes_to_copy,
				      req_length - copied_bytes);
		स_नकल(actor_addr + actor_offset,
		       page_address(bvec->bv_page) + bvec->bv_offset + offset,
		       bytes_to_copy);

		actor_offset += bytes_to_copy;
		copied_bytes += bytes_to_copy;
		offset += bytes_to_copy;

		अगर (actor_offset >= PAGE_SIZE) अणु
			actor_addr = squashfs_next_page(actor);
			अगर (!actor_addr)
				अवरोध;
			actor_offset = 0;
		पूर्ण
		अगर (offset >= bvec->bv_len) अणु
			अगर (!bio_next_segment(bio, &iter_all))
				अवरोध;
			offset = 0;
		पूर्ण
	पूर्ण
	squashfs_finish_page(actor);
	वापस copied_bytes;
पूर्ण

अटल पूर्णांक squashfs_bio_पढ़ो(काष्ठा super_block *sb, u64 index, पूर्णांक length,
			     काष्ठा bio **biop, पूर्णांक *block_offset)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	स्थिर u64 पढ़ो_start = round_करोwn(index, msblk->devblksize);
	स्थिर sector_t block = पढ़ो_start >> msblk->devblksize_log2;
	स्थिर u64 पढ़ो_end = round_up(index + length, msblk->devblksize);
	स्थिर sector_t block_end = पढ़ो_end >> msblk->devblksize_log2;
	पूर्णांक offset = पढ़ो_start - round_करोwn(index, PAGE_SIZE);
	पूर्णांक total_len = (block_end - block) << msblk->devblksize_log2;
	स्थिर पूर्णांक page_count = DIV_ROUND_UP(total_len + offset, PAGE_SIZE);
	पूर्णांक error, i;
	काष्ठा bio *bio;

	अगर (page_count <= BIO_MAX_VECS)
		bio = bio_alloc(GFP_NOIO, page_count);
	अन्यथा
		bio = bio_kदो_स्मृति(GFP_NOIO, page_count);

	अगर (!bio)
		वापस -ENOMEM;

	bio_set_dev(bio, sb->s_bdev);
	bio->bi_opf = READ;
	bio->bi_iter.bi_sector = block * (msblk->devblksize >> SECTOR_SHIFT);

	क्रम (i = 0; i < page_count; ++i) अणु
		अचिन्हित पूर्णांक len =
			min_t(अचिन्हित पूर्णांक, PAGE_SIZE - offset, total_len);
		काष्ठा page *page = alloc_page(GFP_NOIO);

		अगर (!page) अणु
			error = -ENOMEM;
			जाओ out_मुक्त_bio;
		पूर्ण
		अगर (!bio_add_page(bio, page, len, offset)) अणु
			error = -EIO;
			जाओ out_मुक्त_bio;
		पूर्ण
		offset = 0;
		total_len -= len;
	पूर्ण

	error = submit_bio_रुको(bio);
	अगर (error)
		जाओ out_मुक्त_bio;

	*biop = bio;
	*block_offset = index & ((1 << msblk->devblksize_log2) - 1);
	वापस 0;

out_मुक्त_bio:
	bio_मुक्त_pages(bio);
	bio_put(bio);
	वापस error;
पूर्ण

/*
 * Read and decompress a metadata block or datablock.  Length is non-zero
 * अगर a datablock is being पढ़ो (the size is stored अन्यथाwhere in the
 * fileप्रणाली), otherwise the length is obtained from the first two bytes of
 * the metadata block.  A bit in the length field indicates अगर the block
 * is stored uncompressed in the fileप्रणाली (usually because compression
 * generated a larger block - this करोes occasionally happen with compression
 * algorithms).
 */
पूर्णांक squashfs_पढ़ो_data(काष्ठा super_block *sb, u64 index, पूर्णांक length,
		       u64 *next_index, काष्ठा squashfs_page_actor *output)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	काष्ठा bio *bio = शून्य;
	पूर्णांक compressed;
	पूर्णांक res;
	पूर्णांक offset;

	अगर (length) अणु
		/*
		 * Datablock.
		 */
		compressed = SQUASHFS_COMPRESSED_BLOCK(length);
		length = SQUASHFS_COMPRESSED_SIZE_BLOCK(length);
		TRACE("Block @ 0x%llx, %scompressed size %d, src size %d\n",
			index, compressed ? "" : "un", length, output->length);
	पूर्ण अन्यथा अणु
		/*
		 * Metadata block.
		 */
		स्थिर u8 *data;
		काष्ठा bvec_iter_all iter_all = अणुपूर्ण;
		काष्ठा bio_vec *bvec = bvec_init_iter_all(&iter_all);

		अगर (index + 2 > msblk->bytes_used) अणु
			res = -EIO;
			जाओ out;
		पूर्ण
		res = squashfs_bio_पढ़ो(sb, index, 2, &bio, &offset);
		अगर (res)
			जाओ out;

		अगर (WARN_ON_ONCE(!bio_next_segment(bio, &iter_all))) अणु
			res = -EIO;
			जाओ out_मुक्त_bio;
		पूर्ण
		/* Extract the length of the metadata block */
		data = page_address(bvec->bv_page) + bvec->bv_offset;
		length = data[offset];
		अगर (offset < bvec->bv_len - 1) अणु
			length |= data[offset + 1] << 8;
		पूर्ण अन्यथा अणु
			अगर (WARN_ON_ONCE(!bio_next_segment(bio, &iter_all))) अणु
				res = -EIO;
				जाओ out_मुक्त_bio;
			पूर्ण
			data = page_address(bvec->bv_page) + bvec->bv_offset;
			length |= data[0] << 8;
		पूर्ण
		bio_मुक्त_pages(bio);
		bio_put(bio);

		compressed = SQUASHFS_COMPRESSED(length);
		length = SQUASHFS_COMPRESSED_SIZE(length);
		index += 2;

		TRACE("Block @ 0x%llx, %scompressed size %d\n", index - 2,
		      compressed ? "" : "un", length);
	पूर्ण
	अगर (length < 0 || length > output->length ||
			(index + length) > msblk->bytes_used) अणु
		res = -EIO;
		जाओ out;
	पूर्ण

	अगर (next_index)
		*next_index = index + length;

	res = squashfs_bio_पढ़ो(sb, index, length, &bio, &offset);
	अगर (res)
		जाओ out;

	अगर (compressed) अणु
		अगर (!msblk->stream) अणु
			res = -EIO;
			जाओ out_मुक्त_bio;
		पूर्ण
		res = squashfs_decompress(msblk, bio, offset, length, output);
	पूर्ण अन्यथा अणु
		res = copy_bio_to_actor(bio, output, offset, length);
	पूर्ण

out_मुक्त_bio:
	bio_मुक्त_pages(bio);
	bio_put(bio);
out:
	अगर (res < 0)
		ERROR("Failed to read block 0x%llx: %d\n", index, res);

	वापस res;
पूर्ण
