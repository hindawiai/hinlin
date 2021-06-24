<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Oracle.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/bपन.स>
#समावेश <linux/lzo.h>
#समावेश <linux/refcount.h>
#समावेश "compression.h"

#घोषणा LZO_LEN	4

/*
 * Btrfs LZO compression क्रमmat
 *
 * Regular and अंतरभूतd LZO compressed data extents consist of:
 *
 * 1.  Header
 *     Fixed size. LZO_LEN (4) bytes दीर्घ, LE32.
 *     Records the total size (including the header) of compressed data.
 *
 * 2.  Segment(s)
 *     Variable size. Each segment includes one segment header, followed by data
 *     payload.
 *     One regular LZO compressed extent can have one or more segments.
 *     For अंतरभूतd LZO compressed extent, only one segment is allowed.
 *     One segment represents at most one page of uncompressed data.
 *
 * 2.1 Segment header
 *     Fixed size. LZO_LEN (4) bytes दीर्घ, LE32.
 *     Records the total size of the segment (not including the header).
 *     Segment header never crosses page boundary, thus it's possible to
 *     have at most 3 padding zeros at the end of the page.
 *
 * 2.2 Data Payload
 *     Variable size. Size up limit should be lzo1x_worst_compress(PAGE_SIZE)
 *     which is 4419 क्रम a 4KiB page.
 *
 * Example:
 * Page 1:
 *          0     0x2   0x4   0x6   0x8   0xa   0xc   0xe     0x10
 * 0x0000   |  Header   | SegHdr 01 | Data payload 01 ...     |
 * ...
 * 0x0ff0   | SegHdr  N | Data payload  N     ...          |00|
 *                                                          ^^ padding zeros
 * Page 2:
 * 0x1000   | SegHdr N+1| Data payload N+1 ...                |
 */

काष्ठा workspace अणु
	व्योम *mem;
	व्योम *buf;	/* where decompressed data goes */
	व्योम *cbuf;	/* where compressed data goes */
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा workspace_manager wsm;

व्योम lzo_मुक्त_workspace(काष्ठा list_head *ws)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);

	kvमुक्त(workspace->buf);
	kvमुक्त(workspace->cbuf);
	kvमुक्त(workspace->mem);
	kमुक्त(workspace);
पूर्ण

काष्ठा list_head *lzo_alloc_workspace(अचिन्हित पूर्णांक level)
अणु
	काष्ठा workspace *workspace;

	workspace = kzalloc(माप(*workspace), GFP_KERNEL);
	अगर (!workspace)
		वापस ERR_PTR(-ENOMEM);

	workspace->mem = kvदो_स्मृति(LZO1X_MEM_COMPRESS, GFP_KERNEL);
	workspace->buf = kvदो_स्मृति(lzo1x_worst_compress(PAGE_SIZE), GFP_KERNEL);
	workspace->cbuf = kvदो_स्मृति(lzo1x_worst_compress(PAGE_SIZE), GFP_KERNEL);
	अगर (!workspace->mem || !workspace->buf || !workspace->cbuf)
		जाओ fail;

	INIT_LIST_HEAD(&workspace->list);

	वापस &workspace->list;
fail:
	lzo_मुक्त_workspace(&workspace->list);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_compress_length(अक्षर *buf, माप_प्रकार len)
अणु
	__le32 dlen;

	dlen = cpu_to_le32(len);
	स_नकल(buf, &dlen, LZO_LEN);
पूर्ण

अटल अंतरभूत माप_प्रकार पढ़ो_compress_length(स्थिर अक्षर *buf)
अणु
	__le32 dlen;

	स_नकल(&dlen, buf, LZO_LEN);
	वापस le32_to_cpu(dlen);
पूर्ण

पूर्णांक lzo_compress_pages(काष्ठा list_head *ws, काष्ठा address_space *mapping,
		u64 start, काष्ठा page **pages, अचिन्हित दीर्घ *out_pages,
		अचिन्हित दीर्घ *total_in, अचिन्हित दीर्घ *total_out)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);
	पूर्णांक ret = 0;
	अक्षर *data_in;
	अक्षर *cpage_out, *sizes_ptr;
	पूर्णांक nr_pages = 0;
	काष्ठा page *in_page = शून्य;
	काष्ठा page *out_page = शून्य;
	अचिन्हित दीर्घ bytes_left;
	अचिन्हित दीर्घ len = *total_out;
	अचिन्हित दीर्घ nr_dest_pages = *out_pages;
	स्थिर अचिन्हित दीर्घ max_out = nr_dest_pages * PAGE_SIZE;
	माप_प्रकार in_len;
	माप_प्रकार out_len;
	अक्षर *buf;
	अचिन्हित दीर्घ tot_in = 0;
	अचिन्हित दीर्घ tot_out = 0;
	अचिन्हित दीर्घ pg_bytes_left;
	अचिन्हित दीर्घ out_offset;
	अचिन्हित दीर्घ bytes;

	*out_pages = 0;
	*total_out = 0;
	*total_in = 0;

	in_page = find_get_page(mapping, start >> PAGE_SHIFT);
	data_in = kmap(in_page);

	/*
	 * store the size of all chunks of compressed data in
	 * the first 4 bytes
	 */
	out_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
	अगर (out_page == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	cpage_out = kmap(out_page);
	out_offset = LZO_LEN;
	tot_out = LZO_LEN;
	pages[0] = out_page;
	nr_pages = 1;
	pg_bytes_left = PAGE_SIZE - LZO_LEN;

	/* compress at most one page of data each समय */
	in_len = min(len, PAGE_SIZE);
	जबतक (tot_in < len) अणु
		ret = lzo1x_1_compress(data_in, in_len, workspace->cbuf,
				       &out_len, workspace->mem);
		अगर (ret != LZO_E_OK) अणु
			pr_debug("BTRFS: lzo in loop returned %d\n",
			       ret);
			ret = -EIO;
			जाओ out;
		पूर्ण

		/* store the size of this chunk of compressed data */
		ग_लिखो_compress_length(cpage_out + out_offset, out_len);
		tot_out += LZO_LEN;
		out_offset += LZO_LEN;
		pg_bytes_left -= LZO_LEN;

		tot_in += in_len;
		tot_out += out_len;

		/* copy bytes from the working buffer पूर्णांकo the pages */
		buf = workspace->cbuf;
		जबतक (out_len) अणु
			bytes = min_t(अचिन्हित दीर्घ, pg_bytes_left, out_len);

			स_नकल(cpage_out + out_offset, buf, bytes);

			out_len -= bytes;
			pg_bytes_left -= bytes;
			buf += bytes;
			out_offset += bytes;

			/*
			 * we need another page क्रम writing out.
			 *
			 * Note अगर there's less than 4 bytes left, we just
			 * skip to a new page.
			 */
			अगर ((out_len == 0 && pg_bytes_left < LZO_LEN) ||
			    pg_bytes_left == 0) अणु
				अगर (pg_bytes_left) अणु
					स_रखो(cpage_out + out_offset, 0,
					       pg_bytes_left);
					tot_out += pg_bytes_left;
				पूर्ण

				/* we're done, don't allocate new page */
				अगर (out_len == 0 && tot_in >= len)
					अवरोध;

				kunmap(out_page);
				अगर (nr_pages == nr_dest_pages) अणु
					out_page = शून्य;
					ret = -E2BIG;
					जाओ out;
				पूर्ण

				out_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
				अगर (out_page == शून्य) अणु
					ret = -ENOMEM;
					जाओ out;
				पूर्ण
				cpage_out = kmap(out_page);
				pages[nr_pages++] = out_page;

				pg_bytes_left = PAGE_SIZE;
				out_offset = 0;
			पूर्ण
		पूर्ण

		/* we're making it bigger, give up */
		अगर (tot_in > 8192 && tot_in < tot_out) अणु
			ret = -E2BIG;
			जाओ out;
		पूर्ण

		/* we're all करोne */
		अगर (tot_in >= len)
			अवरोध;

		अगर (tot_out > max_out)
			अवरोध;

		bytes_left = len - tot_in;
		kunmap(in_page);
		put_page(in_page);

		start += PAGE_SIZE;
		in_page = find_get_page(mapping, start >> PAGE_SHIFT);
		data_in = kmap(in_page);
		in_len = min(bytes_left, PAGE_SIZE);
	पूर्ण

	अगर (tot_out >= tot_in) अणु
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	/* store the size of all chunks of compressed data */
	sizes_ptr = kmap_local_page(pages[0]);
	ग_लिखो_compress_length(sizes_ptr, tot_out);
	kunmap_local(sizes_ptr);

	ret = 0;
	*total_out = tot_out;
	*total_in = tot_in;
out:
	*out_pages = nr_pages;
	अगर (out_page)
		kunmap(out_page);

	अगर (in_page) अणु
		kunmap(in_page);
		put_page(in_page);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक lzo_decompress_bio(काष्ठा list_head *ws, काष्ठा compressed_bio *cb)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);
	पूर्णांक ret = 0, ret2;
	अक्षर *data_in;
	अचिन्हित दीर्घ page_in_index = 0;
	माप_प्रकार srclen = cb->compressed_len;
	अचिन्हित दीर्घ total_pages_in = DIV_ROUND_UP(srclen, PAGE_SIZE);
	अचिन्हित दीर्घ buf_start;
	अचिन्हित दीर्घ buf_offset = 0;
	अचिन्हित दीर्घ bytes;
	अचिन्हित दीर्घ working_bytes;
	माप_प्रकार in_len;
	माप_प्रकार out_len;
	स्थिर माप_प्रकार max_segment_len = lzo1x_worst_compress(PAGE_SIZE);
	अचिन्हित दीर्घ in_offset;
	अचिन्हित दीर्घ in_page_bytes_left;
	अचिन्हित दीर्घ tot_in;
	अचिन्हित दीर्घ tot_out;
	अचिन्हित दीर्घ tot_len;
	अक्षर *buf;
	bool may_late_unmap, need_unmap;
	काष्ठा page **pages_in = cb->compressed_pages;
	u64 disk_start = cb->start;
	काष्ठा bio *orig_bio = cb->orig_bio;

	data_in = kmap(pages_in[0]);
	tot_len = पढ़ो_compress_length(data_in);
	/*
	 * Compressed data header check.
	 *
	 * The real compressed size can't exceed the maximum extent length, and
	 * all pages should be used (whole unused page with just the segment
	 * header is not possible).  If this happens it means the compressed
	 * extent is corrupted.
	 */
	अगर (tot_len > min_t(माप_प्रकार, BTRFS_MAX_COMPRESSED, srclen) ||
	    tot_len < srclen - PAGE_SIZE) अणु
		ret = -EUCLEAN;
		जाओ करोne;
	पूर्ण

	tot_in = LZO_LEN;
	in_offset = LZO_LEN;
	in_page_bytes_left = PAGE_SIZE - LZO_LEN;

	tot_out = 0;

	जबतक (tot_in < tot_len) अणु
		in_len = पढ़ो_compress_length(data_in + in_offset);
		in_page_bytes_left -= LZO_LEN;
		in_offset += LZO_LEN;
		tot_in += LZO_LEN;

		/*
		 * Segment header check.
		 *
		 * The segment length must not exceed the maximum LZO
		 * compression size, nor the total compressed size.
		 */
		अगर (in_len > max_segment_len || tot_in + in_len > tot_len) अणु
			ret = -EUCLEAN;
			जाओ करोne;
		पूर्ण

		tot_in += in_len;
		working_bytes = in_len;
		may_late_unmap = need_unmap = false;

		/* fast path: aव्योम using the working buffer */
		अगर (in_page_bytes_left >= in_len) अणु
			buf = data_in + in_offset;
			bytes = in_len;
			may_late_unmap = true;
			जाओ cont;
		पूर्ण

		/* copy bytes from the pages पूर्णांकo the working buffer */
		buf = workspace->cbuf;
		buf_offset = 0;
		जबतक (working_bytes) अणु
			bytes = min(working_bytes, in_page_bytes_left);

			स_नकल(buf + buf_offset, data_in + in_offset, bytes);
			buf_offset += bytes;
cont:
			working_bytes -= bytes;
			in_page_bytes_left -= bytes;
			in_offset += bytes;

			/* check अगर we need to pick another page */
			अगर ((working_bytes == 0 && in_page_bytes_left < LZO_LEN)
			    || in_page_bytes_left == 0) अणु
				tot_in += in_page_bytes_left;

				अगर (working_bytes == 0 && tot_in >= tot_len)
					अवरोध;

				अगर (page_in_index + 1 >= total_pages_in) अणु
					ret = -EIO;
					जाओ करोne;
				पूर्ण

				अगर (may_late_unmap)
					need_unmap = true;
				अन्यथा
					kunmap(pages_in[page_in_index]);

				data_in = kmap(pages_in[++page_in_index]);

				in_page_bytes_left = PAGE_SIZE;
				in_offset = 0;
			पूर्ण
		पूर्ण

		out_len = max_segment_len;
		ret = lzo1x_decompress_safe(buf, in_len, workspace->buf,
					    &out_len);
		अगर (need_unmap)
			kunmap(pages_in[page_in_index - 1]);
		अगर (ret != LZO_E_OK) अणु
			pr_warn("BTRFS: decompress failed\n");
			ret = -EIO;
			अवरोध;
		पूर्ण

		buf_start = tot_out;
		tot_out += out_len;

		ret2 = btrfs_decompress_buf2page(workspace->buf, buf_start,
						 tot_out, disk_start, orig_bio);
		अगर (ret2 == 0)
			अवरोध;
	पूर्ण
करोne:
	kunmap(pages_in[page_in_index]);
	अगर (!ret)
		zero_fill_bio(orig_bio);
	वापस ret;
पूर्ण

पूर्णांक lzo_decompress(काष्ठा list_head *ws, अचिन्हित अक्षर *data_in,
		काष्ठा page *dest_page, अचिन्हित दीर्घ start_byte, माप_प्रकार srclen,
		माप_प्रकार destlen)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);
	माप_प्रकार in_len;
	माप_प्रकार out_len;
	माप_प्रकार max_segment_len = lzo1x_worst_compress(PAGE_SIZE);
	पूर्णांक ret = 0;
	अक्षर *kaddr;
	अचिन्हित दीर्घ bytes;

	अगर (srclen < LZO_LEN || srclen > max_segment_len + LZO_LEN * 2)
		वापस -EUCLEAN;

	in_len = पढ़ो_compress_length(data_in);
	अगर (in_len != srclen)
		वापस -EUCLEAN;
	data_in += LZO_LEN;

	in_len = पढ़ो_compress_length(data_in);
	अगर (in_len != srclen - LZO_LEN * 2) अणु
		ret = -EUCLEAN;
		जाओ out;
	पूर्ण
	data_in += LZO_LEN;

	out_len = PAGE_SIZE;
	ret = lzo1x_decompress_safe(data_in, in_len, workspace->buf, &out_len);
	अगर (ret != LZO_E_OK) अणु
		pr_warn("BTRFS: decompress failed!\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (out_len < start_byte) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/*
	 * the caller is alपढ़ोy checking against PAGE_SIZE, but lets
	 * move this check बंदr to the स_नकल/स_रखो
	 */
	destlen = min_t(अचिन्हित दीर्घ, destlen, PAGE_SIZE);
	bytes = min_t(अचिन्हित दीर्घ, destlen, out_len - start_byte);

	kaddr = kmap_local_page(dest_page);
	स_नकल(kaddr, workspace->buf + start_byte, bytes);

	/*
	 * btrfs_getblock is करोing a zero on the tail of the page too,
	 * but this will cover anything missing from the decompressed
	 * data.
	 */
	अगर (bytes < destlen)
		स_रखो(kaddr+bytes, 0, destlen-bytes);
	kunmap_local(kaddr);
out:
	वापस ret;
पूर्ण

स्थिर काष्ठा btrfs_compress_op btrfs_lzo_compress = अणु
	.workspace_manager	= &wsm,
	.max_level		= 1,
	.शेष_level		= 1,
पूर्ण;
