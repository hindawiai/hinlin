<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Oracle.  All rights reserved.
 *
 * Based on jffs2 zlib code:
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Created by David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/zlib.h>
#समावेश <linux/zutil.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/bपन.स>
#समावेश <linux/refcount.h>
#समावेश "compression.h"

/* workspace buffer size क्रम s390 zlib hardware support */
#घोषणा ZLIB_DFLTCC_BUF_SIZE    (4 * PAGE_SIZE)

काष्ठा workspace अणु
	z_stream strm;
	अक्षर *buf;
	अचिन्हित पूर्णांक buf_size;
	काष्ठा list_head list;
	पूर्णांक level;
पूर्ण;

अटल काष्ठा workspace_manager wsm;

काष्ठा list_head *zlib_get_workspace(अचिन्हित पूर्णांक level)
अणु
	काष्ठा list_head *ws = btrfs_get_workspace(BTRFS_COMPRESS_ZLIB, level);
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);

	workspace->level = level;

	वापस ws;
पूर्ण

व्योम zlib_मुक्त_workspace(काष्ठा list_head *ws)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);

	kvमुक्त(workspace->strm.workspace);
	kमुक्त(workspace->buf);
	kमुक्त(workspace);
पूर्ण

काष्ठा list_head *zlib_alloc_workspace(अचिन्हित पूर्णांक level)
अणु
	काष्ठा workspace *workspace;
	पूर्णांक workspacesize;

	workspace = kzalloc(माप(*workspace), GFP_KERNEL);
	अगर (!workspace)
		वापस ERR_PTR(-ENOMEM);

	workspacesize = max(zlib_deflate_workspacesize(MAX_WBITS, MAX_MEM_LEVEL),
			zlib_inflate_workspacesize());
	workspace->strm.workspace = kvदो_स्मृति(workspacesize, GFP_KERNEL);
	workspace->level = level;
	workspace->buf = शून्य;
	/*
	 * In हाल of s390 zlib hardware support, allocate lager workspace
	 * buffer. If allocator fails, fall back to a single page buffer.
	 */
	अगर (zlib_deflate_dfltcc_enabled()) अणु
		workspace->buf = kदो_स्मृति(ZLIB_DFLTCC_BUF_SIZE,
					 __GFP_NOMEMALLOC | __GFP_NORETRY |
					 __GFP_NOWARN | GFP_NOIO);
		workspace->buf_size = ZLIB_DFLTCC_BUF_SIZE;
	पूर्ण
	अगर (!workspace->buf) अणु
		workspace->buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
		workspace->buf_size = PAGE_SIZE;
	पूर्ण
	अगर (!workspace->strm.workspace || !workspace->buf)
		जाओ fail;

	INIT_LIST_HEAD(&workspace->list);

	वापस &workspace->list;
fail:
	zlib_मुक्त_workspace(&workspace->list);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

पूर्णांक zlib_compress_pages(काष्ठा list_head *ws, काष्ठा address_space *mapping,
		u64 start, काष्ठा page **pages, अचिन्हित दीर्घ *out_pages,
		अचिन्हित दीर्घ *total_in, अचिन्हित दीर्घ *total_out)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);
	पूर्णांक ret;
	अक्षर *data_in;
	अक्षर *cpage_out;
	पूर्णांक nr_pages = 0;
	काष्ठा page *in_page = शून्य;
	काष्ठा page *out_page = शून्य;
	अचिन्हित दीर्घ bytes_left;
	अचिन्हित पूर्णांक in_buf_pages;
	अचिन्हित दीर्घ len = *total_out;
	अचिन्हित दीर्घ nr_dest_pages = *out_pages;
	स्थिर अचिन्हित दीर्घ max_out = nr_dest_pages * PAGE_SIZE;

	*out_pages = 0;
	*total_out = 0;
	*total_in = 0;

	अगर (Z_OK != zlib_deflateInit(&workspace->strm, workspace->level)) अणु
		pr_warn("BTRFS: deflateInit failed\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	workspace->strm.total_in = 0;
	workspace->strm.total_out = 0;

	out_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
	अगर (out_page == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	cpage_out = kmap(out_page);
	pages[0] = out_page;
	nr_pages = 1;

	workspace->strm.next_in = workspace->buf;
	workspace->strm.avail_in = 0;
	workspace->strm.next_out = cpage_out;
	workspace->strm.avail_out = PAGE_SIZE;

	जबतक (workspace->strm.total_in < len) अणु
		/*
		 * Get next input pages and copy the contents to
		 * the workspace buffer अगर required.
		 */
		अगर (workspace->strm.avail_in == 0) अणु
			bytes_left = len - workspace->strm.total_in;
			in_buf_pages = min(DIV_ROUND_UP(bytes_left, PAGE_SIZE),
					   workspace->buf_size / PAGE_SIZE);
			अगर (in_buf_pages > 1) अणु
				पूर्णांक i;

				क्रम (i = 0; i < in_buf_pages; i++) अणु
					अगर (in_page) अणु
						kunmap(in_page);
						put_page(in_page);
					पूर्ण
					in_page = find_get_page(mapping,
								start >> PAGE_SHIFT);
					data_in = kmap(in_page);
					स_नकल(workspace->buf + i * PAGE_SIZE,
					       data_in, PAGE_SIZE);
					start += PAGE_SIZE;
				पूर्ण
				workspace->strm.next_in = workspace->buf;
			पूर्ण अन्यथा अणु
				अगर (in_page) अणु
					kunmap(in_page);
					put_page(in_page);
				पूर्ण
				in_page = find_get_page(mapping,
							start >> PAGE_SHIFT);
				data_in = kmap(in_page);
				start += PAGE_SIZE;
				workspace->strm.next_in = data_in;
			पूर्ण
			workspace->strm.avail_in = min(bytes_left,
						       (अचिन्हित दीर्घ) workspace->buf_size);
		पूर्ण

		ret = zlib_deflate(&workspace->strm, Z_SYNC_FLUSH);
		अगर (ret != Z_OK) अणु
			pr_debug("BTRFS: deflate in loop returned %d\n",
			       ret);
			zlib_deflateEnd(&workspace->strm);
			ret = -EIO;
			जाओ out;
		पूर्ण

		/* we're making it bigger, give up */
		अगर (workspace->strm.total_in > 8192 &&
		    workspace->strm.total_in <
		    workspace->strm.total_out) अणु
			ret = -E2BIG;
			जाओ out;
		पूर्ण
		/* we need another page क्रम writing out.  Test this
		 * beक्रमe the total_in so we will pull in a new page क्रम
		 * the stream end अगर required
		 */
		अगर (workspace->strm.avail_out == 0) अणु
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
			pages[nr_pages] = out_page;
			nr_pages++;
			workspace->strm.avail_out = PAGE_SIZE;
			workspace->strm.next_out = cpage_out;
		पूर्ण
		/* we're all करोne */
		अगर (workspace->strm.total_in >= len)
			अवरोध;
		अगर (workspace->strm.total_out > max_out)
			अवरोध;
	पूर्ण
	workspace->strm.avail_in = 0;
	/*
	 * Call deflate with Z_FINISH flush parameter providing more output
	 * space but no more input data, until it वापसs with Z_STREAM_END.
	 */
	जबतक (ret != Z_STREAM_END) अणु
		ret = zlib_deflate(&workspace->strm, Z_FINISH);
		अगर (ret == Z_STREAM_END)
			अवरोध;
		अगर (ret != Z_OK && ret != Z_BUF_ERROR) अणु
			zlib_deflateEnd(&workspace->strm);
			ret = -EIO;
			जाओ out;
		पूर्ण अन्यथा अगर (workspace->strm.avail_out == 0) अणु
			/* get another page क्रम the stream end */
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
			pages[nr_pages] = out_page;
			nr_pages++;
			workspace->strm.avail_out = PAGE_SIZE;
			workspace->strm.next_out = cpage_out;
		पूर्ण
	पूर्ण
	zlib_deflateEnd(&workspace->strm);

	अगर (workspace->strm.total_out >= workspace->strm.total_in) अणु
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	ret = 0;
	*total_out = workspace->strm.total_out;
	*total_in = workspace->strm.total_in;
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

पूर्णांक zlib_decompress_bio(काष्ठा list_head *ws, काष्ठा compressed_bio *cb)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);
	पूर्णांक ret = 0, ret2;
	पूर्णांक wbits = MAX_WBITS;
	अक्षर *data_in;
	माप_प्रकार total_out = 0;
	अचिन्हित दीर्घ page_in_index = 0;
	माप_प्रकार srclen = cb->compressed_len;
	अचिन्हित दीर्घ total_pages_in = DIV_ROUND_UP(srclen, PAGE_SIZE);
	अचिन्हित दीर्घ buf_start;
	काष्ठा page **pages_in = cb->compressed_pages;
	u64 disk_start = cb->start;
	काष्ठा bio *orig_bio = cb->orig_bio;

	data_in = kmap(pages_in[page_in_index]);
	workspace->strm.next_in = data_in;
	workspace->strm.avail_in = min_t(माप_प्रकार, srclen, PAGE_SIZE);
	workspace->strm.total_in = 0;

	workspace->strm.total_out = 0;
	workspace->strm.next_out = workspace->buf;
	workspace->strm.avail_out = workspace->buf_size;

	/* If it's deflate, and it's got no preset dictionary, then
	   we can tell zlib to skip the adler32 check. */
	अगर (srclen > 2 && !(data_in[1] & PRESET_DICT) &&
	    ((data_in[0] & 0x0f) == Z_DEFLATED) &&
	    !(((data_in[0]<<8) + data_in[1]) % 31)) अणु

		wbits = -((data_in[0] >> 4) + 8);
		workspace->strm.next_in += 2;
		workspace->strm.avail_in -= 2;
	पूर्ण

	अगर (Z_OK != zlib_inflateInit2(&workspace->strm, wbits)) अणु
		pr_warn("BTRFS: inflateInit failed\n");
		kunmap(pages_in[page_in_index]);
		वापस -EIO;
	पूर्ण
	जबतक (workspace->strm.total_in < srclen) अणु
		ret = zlib_inflate(&workspace->strm, Z_NO_FLUSH);
		अगर (ret != Z_OK && ret != Z_STREAM_END)
			अवरोध;

		buf_start = total_out;
		total_out = workspace->strm.total_out;

		/* we didn't make progress in this inflate call, we're करोne */
		अगर (buf_start == total_out)
			अवरोध;

		ret2 = btrfs_decompress_buf2page(workspace->buf, buf_start,
						 total_out, disk_start,
						 orig_bio);
		अगर (ret2 == 0) अणु
			ret = 0;
			जाओ करोne;
		पूर्ण

		workspace->strm.next_out = workspace->buf;
		workspace->strm.avail_out = workspace->buf_size;

		अगर (workspace->strm.avail_in == 0) अणु
			अचिन्हित दीर्घ पंचांगp;
			kunmap(pages_in[page_in_index]);
			page_in_index++;
			अगर (page_in_index >= total_pages_in) अणु
				data_in = शून्य;
				अवरोध;
			पूर्ण
			data_in = kmap(pages_in[page_in_index]);
			workspace->strm.next_in = data_in;
			पंचांगp = srclen - workspace->strm.total_in;
			workspace->strm.avail_in = min(पंचांगp,
							   PAGE_SIZE);
		पूर्ण
	पूर्ण
	अगर (ret != Z_STREAM_END)
		ret = -EIO;
	अन्यथा
		ret = 0;
करोne:
	zlib_inflateEnd(&workspace->strm);
	अगर (data_in)
		kunmap(pages_in[page_in_index]);
	अगर (!ret)
		zero_fill_bio(orig_bio);
	वापस ret;
पूर्ण

पूर्णांक zlib_decompress(काष्ठा list_head *ws, अचिन्हित अक्षर *data_in,
		काष्ठा page *dest_page, अचिन्हित दीर्घ start_byte, माप_प्रकार srclen,
		माप_प्रकार destlen)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);
	पूर्णांक ret = 0;
	पूर्णांक wbits = MAX_WBITS;
	अचिन्हित दीर्घ bytes_left;
	अचिन्हित दीर्घ total_out = 0;
	अचिन्हित दीर्घ pg_offset = 0;

	destlen = min_t(अचिन्हित दीर्घ, destlen, PAGE_SIZE);
	bytes_left = destlen;

	workspace->strm.next_in = data_in;
	workspace->strm.avail_in = srclen;
	workspace->strm.total_in = 0;

	workspace->strm.next_out = workspace->buf;
	workspace->strm.avail_out = workspace->buf_size;
	workspace->strm.total_out = 0;
	/* If it's deflate, and it's got no preset dictionary, then
	   we can tell zlib to skip the adler32 check. */
	अगर (srclen > 2 && !(data_in[1] & PRESET_DICT) &&
	    ((data_in[0] & 0x0f) == Z_DEFLATED) &&
	    !(((data_in[0]<<8) + data_in[1]) % 31)) अणु

		wbits = -((data_in[0] >> 4) + 8);
		workspace->strm.next_in += 2;
		workspace->strm.avail_in -= 2;
	पूर्ण

	अगर (Z_OK != zlib_inflateInit2(&workspace->strm, wbits)) अणु
		pr_warn("BTRFS: inflateInit failed\n");
		वापस -EIO;
	पूर्ण

	जबतक (bytes_left > 0) अणु
		अचिन्हित दीर्घ buf_start;
		अचिन्हित दीर्घ buf_offset;
		अचिन्हित दीर्घ bytes;

		ret = zlib_inflate(&workspace->strm, Z_NO_FLUSH);
		अगर (ret != Z_OK && ret != Z_STREAM_END)
			अवरोध;

		buf_start = total_out;
		total_out = workspace->strm.total_out;

		अगर (total_out == buf_start) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण

		अगर (total_out <= start_byte)
			जाओ next;

		अगर (total_out > start_byte && buf_start < start_byte)
			buf_offset = start_byte - buf_start;
		अन्यथा
			buf_offset = 0;

		bytes = min(PAGE_SIZE - pg_offset,
			    PAGE_SIZE - (buf_offset % PAGE_SIZE));
		bytes = min(bytes, bytes_left);

		स_नकल_to_page(dest_page, pg_offset,
			       workspace->buf + buf_offset, bytes);

		pg_offset += bytes;
		bytes_left -= bytes;
next:
		workspace->strm.next_out = workspace->buf;
		workspace->strm.avail_out = workspace->buf_size;
	पूर्ण

	अगर (ret != Z_STREAM_END && bytes_left != 0)
		ret = -EIO;
	अन्यथा
		ret = 0;

	zlib_inflateEnd(&workspace->strm);

	/*
	 * this should only happen अगर zlib वापसed fewer bytes than we
	 * expected.  btrfs_get_block is responsible क्रम zeroing from the
	 * end of the अंतरभूत extent (destlen) to the end of the page
	 */
	अगर (pg_offset < destlen) अणु
		memzero_page(dest_page, pg_offset, destlen - pg_offset);
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा btrfs_compress_op btrfs_zlib_compress = अणु
	.workspace_manager	= &wsm,
	.max_level		= 9,
	.शेष_level		= BTRFS_ZLIB_DEFAULT_LEVEL,
पूर्ण;
