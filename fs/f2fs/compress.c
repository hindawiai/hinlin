<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * f2fs compress support
 *
 * Copyright (c) 2019 Chao Yu <chao@kernel.org>
 */

#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/lzo.h>
#समावेश <linux/lz4.h>
#समावेश <linux/zstd.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश <trace/events/f2fs.h>

अटल काष्ठा kmem_cache *cic_entry_slab;
अटल काष्ठा kmem_cache *dic_entry_slab;

अटल व्योम *page_array_alloc(काष्ठा inode *inode, पूर्णांक nr)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	अचिन्हित पूर्णांक size = माप(काष्ठा page *) * nr;

	अगर (likely(size <= sbi->page_array_slab_size))
		वापस kmem_cache_zalloc(sbi->page_array_slab, GFP_NOFS);
	वापस f2fs_kzalloc(sbi, size, GFP_NOFS);
पूर्ण

अटल व्योम page_array_मुक्त(काष्ठा inode *inode, व्योम *pages, पूर्णांक nr)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	अचिन्हित पूर्णांक size = माप(काष्ठा page *) * nr;

	अगर (!pages)
		वापस;

	अगर (likely(size <= sbi->page_array_slab_size))
		kmem_cache_मुक्त(sbi->page_array_slab, pages);
	अन्यथा
		kमुक्त(pages);
पूर्ण

काष्ठा f2fs_compress_ops अणु
	पूर्णांक (*init_compress_ctx)(काष्ठा compress_ctx *cc);
	व्योम (*destroy_compress_ctx)(काष्ठा compress_ctx *cc);
	पूर्णांक (*compress_pages)(काष्ठा compress_ctx *cc);
	पूर्णांक (*init_decompress_ctx)(काष्ठा decompress_io_ctx *dic);
	व्योम (*destroy_decompress_ctx)(काष्ठा decompress_io_ctx *dic);
	पूर्णांक (*decompress_pages)(काष्ठा decompress_io_ctx *dic);
पूर्ण;

अटल अचिन्हित पूर्णांक offset_in_cluster(काष्ठा compress_ctx *cc, pgoff_t index)
अणु
	वापस index & (cc->cluster_size - 1);
पूर्ण

अटल pgoff_t cluster_idx(काष्ठा compress_ctx *cc, pgoff_t index)
अणु
	वापस index >> cc->log_cluster_size;
पूर्ण

अटल pgoff_t start_idx_of_cluster(काष्ठा compress_ctx *cc)
अणु
	वापस cc->cluster_idx << cc->log_cluster_size;
पूर्ण

bool f2fs_is_compressed_page(काष्ठा page *page)
अणु
	अगर (!PagePrivate(page))
		वापस false;
	अगर (!page_निजी(page))
		वापस false;
	अगर (IS_ATOMIC_WRITTEN_PAGE(page) || IS_DUMMY_WRITTEN_PAGE(page))
		वापस false;

	f2fs_bug_on(F2FS_M_SB(page->mapping),
		*((u32 *)page_निजी(page)) != F2FS_COMPRESSED_PAGE_MAGIC);
	वापस true;
पूर्ण

अटल व्योम f2fs_set_compressed_page(काष्ठा page *page,
		काष्ठा inode *inode, pgoff_t index, व्योम *data)
अणु
	SetPagePrivate(page);
	set_page_निजी(page, (अचिन्हित दीर्घ)data);

	/* i_crypto_info and iv index */
	page->index = index;
	page->mapping = inode->i_mapping;
पूर्ण

अटल व्योम f2fs_drop_rpages(काष्ठा compress_ctx *cc, पूर्णांक len, bool unlock)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (!cc->rpages[i])
			जारी;
		अगर (unlock)
			unlock_page(cc->rpages[i]);
		अन्यथा
			put_page(cc->rpages[i]);
	पूर्ण
पूर्ण

अटल व्योम f2fs_put_rpages(काष्ठा compress_ctx *cc)
अणु
	f2fs_drop_rpages(cc, cc->cluster_size, false);
पूर्ण

अटल व्योम f2fs_unlock_rpages(काष्ठा compress_ctx *cc, पूर्णांक len)
अणु
	f2fs_drop_rpages(cc, len, true);
पूर्ण

अटल व्योम f2fs_put_rpages_wbc(काष्ठा compress_ctx *cc,
		काष्ठा ग_लिखोback_control *wbc, bool redirty, पूर्णांक unlock)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cc->cluster_size; i++) अणु
		अगर (!cc->rpages[i])
			जारी;
		अगर (redirty)
			redirty_page_क्रम_ग_लिखोpage(wbc, cc->rpages[i]);
		f2fs_put_page(cc->rpages[i], unlock);
	पूर्ण
पूर्ण

काष्ठा page *f2fs_compress_control_page(काष्ठा page *page)
अणु
	वापस ((काष्ठा compress_io_ctx *)page_निजी(page))->rpages[0];
पूर्ण

पूर्णांक f2fs_init_compress_ctx(काष्ठा compress_ctx *cc)
अणु
	अगर (cc->rpages)
		वापस 0;

	cc->rpages = page_array_alloc(cc->inode, cc->cluster_size);
	वापस cc->rpages ? 0 : -ENOMEM;
पूर्ण

व्योम f2fs_destroy_compress_ctx(काष्ठा compress_ctx *cc, bool reuse)
अणु
	page_array_मुक्त(cc->inode, cc->rpages, cc->cluster_size);
	cc->rpages = शून्य;
	cc->nr_rpages = 0;
	cc->nr_cpages = 0;
	अगर (!reuse)
		cc->cluster_idx = शून्य_CLUSTER;
पूर्ण

व्योम f2fs_compress_ctx_add_page(काष्ठा compress_ctx *cc, काष्ठा page *page)
अणु
	अचिन्हित पूर्णांक cluster_ofs;

	अगर (!f2fs_cluster_can_merge_page(cc, page->index))
		f2fs_bug_on(F2FS_I_SB(cc->inode), 1);

	cluster_ofs = offset_in_cluster(cc, page->index);
	cc->rpages[cluster_ofs] = page;
	cc->nr_rpages++;
	cc->cluster_idx = cluster_idx(cc, page->index);
पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_LZO
अटल पूर्णांक lzo_init_compress_ctx(काष्ठा compress_ctx *cc)
अणु
	cc->निजी = f2fs_kvदो_स्मृति(F2FS_I_SB(cc->inode),
				LZO1X_MEM_COMPRESS, GFP_NOFS);
	अगर (!cc->निजी)
		वापस -ENOMEM;

	cc->clen = lzo1x_worst_compress(PAGE_SIZE << cc->log_cluster_size);
	वापस 0;
पूर्ण

अटल व्योम lzo_destroy_compress_ctx(काष्ठा compress_ctx *cc)
अणु
	kvमुक्त(cc->निजी);
	cc->निजी = शून्य;
पूर्ण

अटल पूर्णांक lzo_compress_pages(काष्ठा compress_ctx *cc)
अणु
	पूर्णांक ret;

	ret = lzo1x_1_compress(cc->rbuf, cc->rlen, cc->cbuf->cdata,
					&cc->clen, cc->निजी);
	अगर (ret != LZO_E_OK) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): lzo compress failed, ret:%d\n",
				KERN_ERR, F2FS_I_SB(cc->inode)->sb->s_id, ret);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lzo_decompress_pages(काष्ठा decompress_io_ctx *dic)
अणु
	पूर्णांक ret;

	ret = lzo1x_decompress_safe(dic->cbuf->cdata, dic->clen,
						dic->rbuf, &dic->rlen);
	अगर (ret != LZO_E_OK) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): lzo decompress failed, ret:%d\n",
				KERN_ERR, F2FS_I_SB(dic->inode)->sb->s_id, ret);
		वापस -EIO;
	पूर्ण

	अगर (dic->rlen != PAGE_SIZE << dic->log_cluster_size) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): lzo invalid rlen:%zu, "
					"expected:%lu\n", KERN_ERR,
					F2FS_I_SB(dic->inode)->sb->s_id,
					dic->rlen,
					PAGE_SIZE << dic->log_cluster_size);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा f2fs_compress_ops f2fs_lzo_ops = अणु
	.init_compress_ctx	= lzo_init_compress_ctx,
	.destroy_compress_ctx	= lzo_destroy_compress_ctx,
	.compress_pages		= lzo_compress_pages,
	.decompress_pages	= lzo_decompress_pages,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_F2FS_FS_LZ4
अटल पूर्णांक lz4_init_compress_ctx(काष्ठा compress_ctx *cc)
अणु
	अचिन्हित पूर्णांक size = LZ4_MEM_COMPRESS;

#अगर_घोषित CONFIG_F2FS_FS_LZ4HC
	अगर (F2FS_I(cc->inode)->i_compress_flag >> COMPRESS_LEVEL_OFFSET)
		size = LZ4HC_MEM_COMPRESS;
#पूर्ण_अगर

	cc->निजी = f2fs_kvदो_स्मृति(F2FS_I_SB(cc->inode), size, GFP_NOFS);
	अगर (!cc->निजी)
		वापस -ENOMEM;

	/*
	 * we करो not change cc->clen to LZ4_compressBound(inमाला_दोize) to
	 * adapt worst compress हाल, because lz4 compressor can handle
	 * output budget properly.
	 */
	cc->clen = cc->rlen - PAGE_SIZE - COMPRESS_HEADER_SIZE;
	वापस 0;
पूर्ण

अटल व्योम lz4_destroy_compress_ctx(काष्ठा compress_ctx *cc)
अणु
	kvमुक्त(cc->निजी);
	cc->निजी = शून्य;
पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_LZ4HC
अटल पूर्णांक lz4hc_compress_pages(काष्ठा compress_ctx *cc)
अणु
	अचिन्हित अक्षर level = F2FS_I(cc->inode)->i_compress_flag >>
						COMPRESS_LEVEL_OFFSET;
	पूर्णांक len;

	अगर (level)
		len = LZ4_compress_HC(cc->rbuf, cc->cbuf->cdata, cc->rlen,
					cc->clen, level, cc->निजी);
	अन्यथा
		len = LZ4_compress_शेष(cc->rbuf, cc->cbuf->cdata, cc->rlen,
						cc->clen, cc->निजी);
	अगर (!len)
		वापस -EAGAIN;

	cc->clen = len;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lz4_compress_pages(काष्ठा compress_ctx *cc)
अणु
	पूर्णांक len;

#अगर_घोषित CONFIG_F2FS_FS_LZ4HC
	वापस lz4hc_compress_pages(cc);
#पूर्ण_अगर
	len = LZ4_compress_शेष(cc->rbuf, cc->cbuf->cdata, cc->rlen,
						cc->clen, cc->निजी);
	अगर (!len)
		वापस -EAGAIN;

	cc->clen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक lz4_decompress_pages(काष्ठा decompress_io_ctx *dic)
अणु
	पूर्णांक ret;

	ret = LZ4_decompress_safe(dic->cbuf->cdata, dic->rbuf,
						dic->clen, dic->rlen);
	अगर (ret < 0) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): lz4 decompress failed, ret:%d\n",
				KERN_ERR, F2FS_I_SB(dic->inode)->sb->s_id, ret);
		वापस -EIO;
	पूर्ण

	अगर (ret != PAGE_SIZE << dic->log_cluster_size) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): lz4 invalid rlen:%zu, "
					"expected:%lu\n", KERN_ERR,
					F2FS_I_SB(dic->inode)->sb->s_id,
					dic->rlen,
					PAGE_SIZE << dic->log_cluster_size);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा f2fs_compress_ops f2fs_lz4_ops = अणु
	.init_compress_ctx	= lz4_init_compress_ctx,
	.destroy_compress_ctx	= lz4_destroy_compress_ctx,
	.compress_pages		= lz4_compress_pages,
	.decompress_pages	= lz4_decompress_pages,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_F2FS_FS_ZSTD
#घोषणा F2FS_ZSTD_DEFAULT_CLEVEL	1

अटल पूर्णांक zstd_init_compress_ctx(काष्ठा compress_ctx *cc)
अणु
	ZSTD_parameters params;
	ZSTD_CStream *stream;
	व्योम *workspace;
	अचिन्हित पूर्णांक workspace_size;
	अचिन्हित अक्षर level = F2FS_I(cc->inode)->i_compress_flag >>
						COMPRESS_LEVEL_OFFSET;

	अगर (!level)
		level = F2FS_ZSTD_DEFAULT_CLEVEL;

	params = ZSTD_getParams(level, cc->rlen, 0);
	workspace_size = ZSTD_CStreamWorkspaceBound(params.cParams);

	workspace = f2fs_kvदो_स्मृति(F2FS_I_SB(cc->inode),
					workspace_size, GFP_NOFS);
	अगर (!workspace)
		वापस -ENOMEM;

	stream = ZSTD_initCStream(params, 0, workspace, workspace_size);
	अगर (!stream) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): %s ZSTD_initCStream failed\n",
				KERN_ERR, F2FS_I_SB(cc->inode)->sb->s_id,
				__func__);
		kvमुक्त(workspace);
		वापस -EIO;
	पूर्ण

	cc->निजी = workspace;
	cc->निजी2 = stream;

	cc->clen = cc->rlen - PAGE_SIZE - COMPRESS_HEADER_SIZE;
	वापस 0;
पूर्ण

अटल व्योम zstd_destroy_compress_ctx(काष्ठा compress_ctx *cc)
अणु
	kvमुक्त(cc->निजी);
	cc->निजी = शून्य;
	cc->निजी2 = शून्य;
पूर्ण

अटल पूर्णांक zstd_compress_pages(काष्ठा compress_ctx *cc)
अणु
	ZSTD_CStream *stream = cc->निजी2;
	ZSTD_inBuffer inbuf;
	ZSTD_outBuffer outbuf;
	पूर्णांक src_size = cc->rlen;
	पूर्णांक dst_size = src_size - PAGE_SIZE - COMPRESS_HEADER_SIZE;
	पूर्णांक ret;

	inbuf.pos = 0;
	inbuf.src = cc->rbuf;
	inbuf.size = src_size;

	outbuf.pos = 0;
	outbuf.dst = cc->cbuf->cdata;
	outbuf.size = dst_size;

	ret = ZSTD_compressStream(stream, &outbuf, &inbuf);
	अगर (ZSTD_isError(ret)) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): %s ZSTD_compressStream failed, ret: %d\n",
				KERN_ERR, F2FS_I_SB(cc->inode)->sb->s_id,
				__func__, ZSTD_getErrorCode(ret));
		वापस -EIO;
	पूर्ण

	ret = ZSTD_endStream(stream, &outbuf);
	अगर (ZSTD_isError(ret)) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): %s ZSTD_endStream returned %d\n",
				KERN_ERR, F2FS_I_SB(cc->inode)->sb->s_id,
				__func__, ZSTD_getErrorCode(ret));
		वापस -EIO;
	पूर्ण

	/*
	 * there is compressed data reमुख्यed in पूर्णांकermediate buffer due to
	 * no more space in cbuf.cdata
	 */
	अगर (ret)
		वापस -EAGAIN;

	cc->clen = outbuf.pos;
	वापस 0;
पूर्ण

अटल पूर्णांक zstd_init_decompress_ctx(काष्ठा decompress_io_ctx *dic)
अणु
	ZSTD_DStream *stream;
	व्योम *workspace;
	अचिन्हित पूर्णांक workspace_size;
	अचिन्हित पूर्णांक max_winकरोw_size =
			MAX_COMPRESS_WINDOW_SIZE(dic->log_cluster_size);

	workspace_size = ZSTD_DStreamWorkspaceBound(max_winकरोw_size);

	workspace = f2fs_kvदो_स्मृति(F2FS_I_SB(dic->inode),
					workspace_size, GFP_NOFS);
	अगर (!workspace)
		वापस -ENOMEM;

	stream = ZSTD_initDStream(max_winकरोw_size, workspace, workspace_size);
	अगर (!stream) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): %s ZSTD_initDStream failed\n",
				KERN_ERR, F2FS_I_SB(dic->inode)->sb->s_id,
				__func__);
		kvमुक्त(workspace);
		वापस -EIO;
	पूर्ण

	dic->निजी = workspace;
	dic->निजी2 = stream;

	वापस 0;
पूर्ण

अटल व्योम zstd_destroy_decompress_ctx(काष्ठा decompress_io_ctx *dic)
अणु
	kvमुक्त(dic->निजी);
	dic->निजी = शून्य;
	dic->निजी2 = शून्य;
पूर्ण

अटल पूर्णांक zstd_decompress_pages(काष्ठा decompress_io_ctx *dic)
अणु
	ZSTD_DStream *stream = dic->निजी2;
	ZSTD_inBuffer inbuf;
	ZSTD_outBuffer outbuf;
	पूर्णांक ret;

	inbuf.pos = 0;
	inbuf.src = dic->cbuf->cdata;
	inbuf.size = dic->clen;

	outbuf.pos = 0;
	outbuf.dst = dic->rbuf;
	outbuf.size = dic->rlen;

	ret = ZSTD_decompressStream(stream, &outbuf, &inbuf);
	अगर (ZSTD_isError(ret)) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): %s ZSTD_compressStream failed, ret: %d\n",
				KERN_ERR, F2FS_I_SB(dic->inode)->sb->s_id,
				__func__, ZSTD_getErrorCode(ret));
		वापस -EIO;
	पूर्ण

	अगर (dic->rlen != outbuf.pos) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): %s ZSTD invalid rlen:%zu, "
				"expected:%lu\n", KERN_ERR,
				F2FS_I_SB(dic->inode)->sb->s_id,
				__func__, dic->rlen,
				PAGE_SIZE << dic->log_cluster_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा f2fs_compress_ops f2fs_zstd_ops = अणु
	.init_compress_ctx	= zstd_init_compress_ctx,
	.destroy_compress_ctx	= zstd_destroy_compress_ctx,
	.compress_pages		= zstd_compress_pages,
	.init_decompress_ctx	= zstd_init_decompress_ctx,
	.destroy_decompress_ctx	= zstd_destroy_decompress_ctx,
	.decompress_pages	= zstd_decompress_pages,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_F2FS_FS_LZO
#अगर_घोषित CONFIG_F2FS_FS_LZORLE
अटल पूर्णांक lzorle_compress_pages(काष्ठा compress_ctx *cc)
अणु
	पूर्णांक ret;

	ret = lzorle1x_1_compress(cc->rbuf, cc->rlen, cc->cbuf->cdata,
					&cc->clen, cc->निजी);
	अगर (ret != LZO_E_OK) अणु
		prपूर्णांकk_ratelimited("%sF2FS-fs (%s): lzo-rle compress failed, ret:%d\n",
				KERN_ERR, F2FS_I_SB(cc->inode)->sb->s_id, ret);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा f2fs_compress_ops f2fs_lzorle_ops = अणु
	.init_compress_ctx	= lzo_init_compress_ctx,
	.destroy_compress_ctx	= lzo_destroy_compress_ctx,
	.compress_pages		= lzorle_compress_pages,
	.decompress_pages	= lzo_decompress_pages,
पूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर

अटल स्थिर काष्ठा f2fs_compress_ops *f2fs_cops[COMPRESS_MAX] = अणु
#अगर_घोषित CONFIG_F2FS_FS_LZO
	&f2fs_lzo_ops,
#अन्यथा
	शून्य,
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_FS_LZ4
	&f2fs_lz4_ops,
#अन्यथा
	शून्य,
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_FS_ZSTD
	&f2fs_zstd_ops,
#अन्यथा
	शून्य,
#पूर्ण_अगर
#अगर defined(CONFIG_F2FS_FS_LZO) && defined(CONFIG_F2FS_FS_LZORLE)
	&f2fs_lzorle_ops,
#अन्यथा
	शून्य,
#पूर्ण_अगर
पूर्ण;

bool f2fs_is_compress_backend_पढ़ोy(काष्ठा inode *inode)
अणु
	अगर (!f2fs_compressed_file(inode))
		वापस true;
	वापस f2fs_cops[F2FS_I(inode)->i_compress_algorithm];
पूर्ण

अटल mempool_t *compress_page_pool;
अटल पूर्णांक num_compress_pages = 512;
module_param(num_compress_pages, uपूर्णांक, 0444);
MODULE_PARM_DESC(num_compress_pages,
		"Number of intermediate compress pages to preallocate");

पूर्णांक f2fs_init_compress_mempool(व्योम)
अणु
	compress_page_pool = mempool_create_page_pool(num_compress_pages, 0);
	अगर (!compress_page_pool)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम f2fs_destroy_compress_mempool(व्योम)
अणु
	mempool_destroy(compress_page_pool);
पूर्ण

अटल काष्ठा page *f2fs_compress_alloc_page(व्योम)
अणु
	काष्ठा page *page;

	page = mempool_alloc(compress_page_pool, GFP_NOFS);
	lock_page(page);

	वापस page;
पूर्ण

अटल व्योम f2fs_compress_मुक्त_page(काष्ठा page *page)
अणु
	अगर (!page)
		वापस;
	set_page_निजी(page, (अचिन्हित दीर्घ)शून्य);
	ClearPagePrivate(page);
	page->mapping = शून्य;
	unlock_page(page);
	mempool_मुक्त(page, compress_page_pool);
पूर्ण

#घोषणा MAX_VMAP_RETRIES	3

अटल व्योम *f2fs_vmap(काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i;
	व्योम *buf = शून्य;

	क्रम (i = 0; i < MAX_VMAP_RETRIES; i++) अणु
		buf = vm_map_ram(pages, count, -1);
		अगर (buf)
			अवरोध;
		vm_unmap_aliases();
	पूर्ण
	वापस buf;
पूर्ण

अटल पूर्णांक f2fs_compress_pages(काष्ठा compress_ctx *cc)
अणु
	काष्ठा f2fs_inode_info *fi = F2FS_I(cc->inode);
	स्थिर काष्ठा f2fs_compress_ops *cops =
				f2fs_cops[fi->i_compress_algorithm];
	अचिन्हित पूर्णांक max_len, new_nr_cpages;
	काष्ठा page **new_cpages;
	u32 chksum = 0;
	पूर्णांक i, ret;

	trace_f2fs_compress_pages_start(cc->inode, cc->cluster_idx,
				cc->cluster_size, fi->i_compress_algorithm);

	अगर (cops->init_compress_ctx) अणु
		ret = cops->init_compress_ctx(cc);
		अगर (ret)
			जाओ out;
	पूर्ण

	max_len = COMPRESS_HEADER_SIZE + cc->clen;
	cc->nr_cpages = DIV_ROUND_UP(max_len, PAGE_SIZE);

	cc->cpages = page_array_alloc(cc->inode, cc->nr_cpages);
	अगर (!cc->cpages) अणु
		ret = -ENOMEM;
		जाओ destroy_compress_ctx;
	पूर्ण

	क्रम (i = 0; i < cc->nr_cpages; i++) अणु
		cc->cpages[i] = f2fs_compress_alloc_page();
		अगर (!cc->cpages[i]) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_cpages;
		पूर्ण
	पूर्ण

	cc->rbuf = f2fs_vmap(cc->rpages, cc->cluster_size);
	अगर (!cc->rbuf) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_cpages;
	पूर्ण

	cc->cbuf = f2fs_vmap(cc->cpages, cc->nr_cpages);
	अगर (!cc->cbuf) अणु
		ret = -ENOMEM;
		जाओ out_vunmap_rbuf;
	पूर्ण

	ret = cops->compress_pages(cc);
	अगर (ret)
		जाओ out_vunmap_cbuf;

	max_len = PAGE_SIZE * (cc->cluster_size - 1) - COMPRESS_HEADER_SIZE;

	अगर (cc->clen > max_len) अणु
		ret = -EAGAIN;
		जाओ out_vunmap_cbuf;
	पूर्ण

	cc->cbuf->clen = cpu_to_le32(cc->clen);

	अगर (fi->i_compress_flag & 1 << COMPRESS_CHKSUM)
		chksum = f2fs_crc32(F2FS_I_SB(cc->inode),
					cc->cbuf->cdata, cc->clen);
	cc->cbuf->chksum = cpu_to_le32(chksum);

	क्रम (i = 0; i < COMPRESS_DATA_RESERVED_SIZE; i++)
		cc->cbuf->reserved[i] = cpu_to_le32(0);

	new_nr_cpages = DIV_ROUND_UP(cc->clen + COMPRESS_HEADER_SIZE, PAGE_SIZE);

	/* Now we're going to cut unnecessary tail pages */
	new_cpages = page_array_alloc(cc->inode, new_nr_cpages);
	अगर (!new_cpages) अणु
		ret = -ENOMEM;
		जाओ out_vunmap_cbuf;
	पूर्ण

	/* zero out any unused part of the last page */
	स_रखो(&cc->cbuf->cdata[cc->clen], 0,
			(new_nr_cpages * PAGE_SIZE) -
			(cc->clen + COMPRESS_HEADER_SIZE));

	vm_unmap_ram(cc->cbuf, cc->nr_cpages);
	vm_unmap_ram(cc->rbuf, cc->cluster_size);

	क्रम (i = 0; i < cc->nr_cpages; i++) अणु
		अगर (i < new_nr_cpages) अणु
			new_cpages[i] = cc->cpages[i];
			जारी;
		पूर्ण
		f2fs_compress_मुक्त_page(cc->cpages[i]);
		cc->cpages[i] = शून्य;
	पूर्ण

	अगर (cops->destroy_compress_ctx)
		cops->destroy_compress_ctx(cc);

	page_array_मुक्त(cc->inode, cc->cpages, cc->nr_cpages);
	cc->cpages = new_cpages;
	cc->nr_cpages = new_nr_cpages;

	trace_f2fs_compress_pages_end(cc->inode, cc->cluster_idx,
							cc->clen, ret);
	वापस 0;

out_vunmap_cbuf:
	vm_unmap_ram(cc->cbuf, cc->nr_cpages);
out_vunmap_rbuf:
	vm_unmap_ram(cc->rbuf, cc->cluster_size);
out_मुक्त_cpages:
	क्रम (i = 0; i < cc->nr_cpages; i++) अणु
		अगर (cc->cpages[i])
			f2fs_compress_मुक्त_page(cc->cpages[i]);
	पूर्ण
	page_array_मुक्त(cc->inode, cc->cpages, cc->nr_cpages);
	cc->cpages = शून्य;
destroy_compress_ctx:
	अगर (cops->destroy_compress_ctx)
		cops->destroy_compress_ctx(cc);
out:
	trace_f2fs_compress_pages_end(cc->inode, cc->cluster_idx,
							cc->clen, ret);
	वापस ret;
पूर्ण

अटल व्योम f2fs_decompress_cluster(काष्ठा decompress_io_ctx *dic)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dic->inode);
	काष्ठा f2fs_inode_info *fi = F2FS_I(dic->inode);
	स्थिर काष्ठा f2fs_compress_ops *cops =
			f2fs_cops[fi->i_compress_algorithm];
	पूर्णांक ret;
	पूर्णांक i;

	trace_f2fs_decompress_pages_start(dic->inode, dic->cluster_idx,
				dic->cluster_size, fi->i_compress_algorithm);

	अगर (dic->failed) अणु
		ret = -EIO;
		जाओ out_end_io;
	पूर्ण

	dic->tpages = page_array_alloc(dic->inode, dic->cluster_size);
	अगर (!dic->tpages) अणु
		ret = -ENOMEM;
		जाओ out_end_io;
	पूर्ण

	क्रम (i = 0; i < dic->cluster_size; i++) अणु
		अगर (dic->rpages[i]) अणु
			dic->tpages[i] = dic->rpages[i];
			जारी;
		पूर्ण

		dic->tpages[i] = f2fs_compress_alloc_page();
		अगर (!dic->tpages[i]) अणु
			ret = -ENOMEM;
			जाओ out_end_io;
		पूर्ण
	पूर्ण

	अगर (cops->init_decompress_ctx) अणु
		ret = cops->init_decompress_ctx(dic);
		अगर (ret)
			जाओ out_end_io;
	पूर्ण

	dic->rbuf = f2fs_vmap(dic->tpages, dic->cluster_size);
	अगर (!dic->rbuf) अणु
		ret = -ENOMEM;
		जाओ out_destroy_decompress_ctx;
	पूर्ण

	dic->cbuf = f2fs_vmap(dic->cpages, dic->nr_cpages);
	अगर (!dic->cbuf) अणु
		ret = -ENOMEM;
		जाओ out_vunmap_rbuf;
	पूर्ण

	dic->clen = le32_to_cpu(dic->cbuf->clen);
	dic->rlen = PAGE_SIZE << dic->log_cluster_size;

	अगर (dic->clen > PAGE_SIZE * dic->nr_cpages - COMPRESS_HEADER_SIZE) अणु
		ret = -EFSCORRUPTED;
		जाओ out_vunmap_cbuf;
	पूर्ण

	ret = cops->decompress_pages(dic);

	अगर (!ret && (fi->i_compress_flag & 1 << COMPRESS_CHKSUM)) अणु
		u32 provided = le32_to_cpu(dic->cbuf->chksum);
		u32 calculated = f2fs_crc32(sbi, dic->cbuf->cdata, dic->clen);

		अगर (provided != calculated) अणु
			अगर (!is_inode_flag_set(dic->inode, FI_COMPRESS_CORRUPT)) अणु
				set_inode_flag(dic->inode, FI_COMPRESS_CORRUPT);
				prपूर्णांकk_ratelimited(
					"%sF2FS-fs (%s): checksum invalid, nid = %lu, %x vs %x",
					KERN_INFO, sbi->sb->s_id, dic->inode->i_ino,
					provided, calculated);
			पूर्ण
			set_sbi_flag(sbi, SBI_NEED_FSCK);
		पूर्ण
	पूर्ण

out_vunmap_cbuf:
	vm_unmap_ram(dic->cbuf, dic->nr_cpages);
out_vunmap_rbuf:
	vm_unmap_ram(dic->rbuf, dic->cluster_size);
out_destroy_decompress_ctx:
	अगर (cops->destroy_decompress_ctx)
		cops->destroy_decompress_ctx(dic);
out_end_io:
	trace_f2fs_decompress_pages_end(dic->inode, dic->cluster_idx,
							dic->clen, ret);
	f2fs_decompress_end_io(dic, ret);
पूर्ण

/*
 * This is called when a page of a compressed cluster has been पढ़ो from disk
 * (or failed to be पढ़ो from disk).  It checks whether this page was the last
 * page being रुकोed on in the cluster, and अगर so, it decompresses the cluster
 * (or in the हाल of a failure, cleans up without actually decompressing).
 */
व्योम f2fs_end_पढ़ो_compressed_page(काष्ठा page *page, bool failed)
अणु
	काष्ठा decompress_io_ctx *dic =
			(काष्ठा decompress_io_ctx *)page_निजी(page);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dic->inode);

	dec_page_count(sbi, F2FS_RD_DATA);

	अगर (failed)
		WRITE_ONCE(dic->failed, true);

	अगर (atomic_dec_and_test(&dic->reमुख्यing_pages))
		f2fs_decompress_cluster(dic);
पूर्ण

अटल bool is_page_in_cluster(काष्ठा compress_ctx *cc, pgoff_t index)
अणु
	अगर (cc->cluster_idx == शून्य_CLUSTER)
		वापस true;
	वापस cc->cluster_idx == cluster_idx(cc, index);
पूर्ण

bool f2fs_cluster_is_empty(काष्ठा compress_ctx *cc)
अणु
	वापस cc->nr_rpages == 0;
पूर्ण

अटल bool f2fs_cluster_is_full(काष्ठा compress_ctx *cc)
अणु
	वापस cc->cluster_size == cc->nr_rpages;
पूर्ण

bool f2fs_cluster_can_merge_page(काष्ठा compress_ctx *cc, pgoff_t index)
अणु
	अगर (f2fs_cluster_is_empty(cc))
		वापस true;
	वापस is_page_in_cluster(cc, index);
पूर्ण

अटल bool __cluster_may_compress(काष्ठा compress_ctx *cc)
अणु
	loff_t i_size = i_size_पढ़ो(cc->inode);
	अचिन्हित nr_pages = DIV_ROUND_UP(i_size, PAGE_SIZE);
	पूर्णांक i;

	क्रम (i = 0; i < cc->cluster_size; i++) अणु
		काष्ठा page *page = cc->rpages[i];

		f2fs_bug_on(F2FS_I_SB(cc->inode), !page);

		/* beyond खातापूर्ण */
		अगर (page->index >= nr_pages)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक __f2fs_cluster_blocks(काष्ठा compress_ctx *cc, bool compr)
अणु
	काष्ठा dnode_of_data dn;
	पूर्णांक ret;

	set_new_dnode(&dn, cc->inode, शून्य, शून्य, 0);
	ret = f2fs_get_dnode_of_data(&dn, start_idx_of_cluster(cc),
							LOOKUP_NODE);
	अगर (ret) अणु
		अगर (ret == -ENOENT)
			ret = 0;
		जाओ fail;
	पूर्ण

	अगर (dn.data_blkaddr == COMPRESS_ADDR) अणु
		पूर्णांक i;

		ret = 1;
		क्रम (i = 1; i < cc->cluster_size; i++) अणु
			block_t blkaddr;

			blkaddr = data_blkaddr(dn.inode,
					dn.node_page, dn.ofs_in_node + i);
			अगर (compr) अणु
				अगर (__is_valid_data_blkaddr(blkaddr))
					ret++;
			पूर्ण अन्यथा अणु
				अगर (blkaddr != शून्य_ADDR)
					ret++;
			पूर्ण
		पूर्ण
	पूर्ण
fail:
	f2fs_put_dnode(&dn);
	वापस ret;
पूर्ण

/* वापस # of compressed blocks in compressed cluster */
अटल पूर्णांक f2fs_compressed_blocks(काष्ठा compress_ctx *cc)
अणु
	वापस __f2fs_cluster_blocks(cc, true);
पूर्ण

/* वापस # of valid blocks in compressed cluster */
अटल पूर्णांक f2fs_cluster_blocks(काष्ठा compress_ctx *cc)
अणु
	वापस __f2fs_cluster_blocks(cc, false);
पूर्ण

पूर्णांक f2fs_is_compressed_cluster(काष्ठा inode *inode, pgoff_t index)
अणु
	काष्ठा compress_ctx cc = अणु
		.inode = inode,
		.log_cluster_size = F2FS_I(inode)->i_log_cluster_size,
		.cluster_size = F2FS_I(inode)->i_cluster_size,
		.cluster_idx = index >> F2FS_I(inode)->i_log_cluster_size,
	पूर्ण;

	वापस f2fs_cluster_blocks(&cc);
पूर्ण

अटल bool cluster_may_compress(काष्ठा compress_ctx *cc)
अणु
	अगर (!f2fs_need_compress_data(cc->inode))
		वापस false;
	अगर (f2fs_is_atomic_file(cc->inode))
		वापस false;
	अगर (f2fs_is_mmap_file(cc->inode))
		वापस false;
	अगर (!f2fs_cluster_is_full(cc))
		वापस false;
	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(cc->inode))))
		वापस false;
	वापस __cluster_may_compress(cc);
पूर्ण

अटल व्योम set_cluster_ग_लिखोback(काष्ठा compress_ctx *cc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cc->cluster_size; i++) अणु
		अगर (cc->rpages[i])
			set_page_ग_लिखोback(cc->rpages[i]);
	पूर्ण
पूर्ण

अटल व्योम set_cluster_dirty(काष्ठा compress_ctx *cc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cc->cluster_size; i++)
		अगर (cc->rpages[i])
			set_page_dirty(cc->rpages[i]);
पूर्ण

अटल पूर्णांक prepare_compress_overग_लिखो(काष्ठा compress_ctx *cc,
		काष्ठा page **pagep, pgoff_t index, व्योम **fsdata)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(cc->inode);
	काष्ठा address_space *mapping = cc->inode->i_mapping;
	काष्ठा page *page;
	काष्ठा dnode_of_data dn;
	sector_t last_block_in_bio;
	अचिन्हित fgp_flag = FGP_LOCK | FGP_WRITE | FGP_CREAT;
	pgoff_t start_idx = start_idx_of_cluster(cc);
	पूर्णांक i, ret;
	bool pपुनः_स्मृति;

retry:
	ret = f2fs_cluster_blocks(cc);
	अगर (ret <= 0)
		वापस ret;

	/* compressed हाल */
	pपुनः_स्मृति = (ret < cc->cluster_size);

	ret = f2fs_init_compress_ctx(cc);
	अगर (ret)
		वापस ret;

	/* keep page reference to aव्योम page reclaim */
	क्रम (i = 0; i < cc->cluster_size; i++) अणु
		page = f2fs_pagecache_get_page(mapping, start_idx + i,
							fgp_flag, GFP_NOFS);
		अगर (!page) अणु
			ret = -ENOMEM;
			जाओ unlock_pages;
		पूर्ण

		अगर (PageUptodate(page))
			f2fs_put_page(page, 1);
		अन्यथा
			f2fs_compress_ctx_add_page(cc, page);
	पूर्ण

	अगर (!f2fs_cluster_is_empty(cc)) अणु
		काष्ठा bio *bio = शून्य;

		ret = f2fs_पढ़ो_multi_pages(cc, &bio, cc->cluster_size,
					&last_block_in_bio, false, true);
		f2fs_put_rpages(cc);
		f2fs_destroy_compress_ctx(cc, true);
		अगर (ret)
			जाओ out;
		अगर (bio)
			f2fs_submit_bio(sbi, bio, DATA);

		ret = f2fs_init_compress_ctx(cc);
		अगर (ret)
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < cc->cluster_size; i++) अणु
		f2fs_bug_on(sbi, cc->rpages[i]);

		page = find_lock_page(mapping, start_idx + i);
		अगर (!page) अणु
			/* page can be truncated */
			जाओ release_and_retry;
		पूर्ण

		f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);
		f2fs_compress_ctx_add_page(cc, page);

		अगर (!PageUptodate(page)) अणु
release_and_retry:
			f2fs_put_rpages(cc);
			f2fs_unlock_rpages(cc, i + 1);
			f2fs_destroy_compress_ctx(cc, true);
			जाओ retry;
		पूर्ण
	पूर्ण

	अगर (pपुनः_स्मृति) अणु
		f2fs_करो_map_lock(sbi, F2FS_GET_BLOCK_PRE_AIO, true);

		set_new_dnode(&dn, cc->inode, शून्य, शून्य, 0);

		क्रम (i = cc->cluster_size - 1; i > 0; i--) अणु
			ret = f2fs_get_block(&dn, start_idx + i);
			अगर (ret) अणु
				i = cc->cluster_size;
				अवरोध;
			पूर्ण

			अगर (dn.data_blkaddr != NEW_ADDR)
				अवरोध;
		पूर्ण

		f2fs_करो_map_lock(sbi, F2FS_GET_BLOCK_PRE_AIO, false);
	पूर्ण

	अगर (likely(!ret)) अणु
		*fsdata = cc->rpages;
		*pagep = cc->rpages[offset_in_cluster(cc, index)];
		वापस cc->cluster_size;
	पूर्ण

unlock_pages:
	f2fs_put_rpages(cc);
	f2fs_unlock_rpages(cc, i);
	f2fs_destroy_compress_ctx(cc, true);
out:
	वापस ret;
पूर्ण

पूर्णांक f2fs_prepare_compress_overग_लिखो(काष्ठा inode *inode,
		काष्ठा page **pagep, pgoff_t index, व्योम **fsdata)
अणु
	काष्ठा compress_ctx cc = अणु
		.inode = inode,
		.log_cluster_size = F2FS_I(inode)->i_log_cluster_size,
		.cluster_size = F2FS_I(inode)->i_cluster_size,
		.cluster_idx = index >> F2FS_I(inode)->i_log_cluster_size,
		.rpages = शून्य,
		.nr_rpages = 0,
	पूर्ण;

	वापस prepare_compress_overग_लिखो(&cc, pagep, index, fsdata);
पूर्ण

bool f2fs_compress_ग_लिखो_end(काष्ठा inode *inode, व्योम *fsdata,
					pgoff_t index, अचिन्हित copied)

अणु
	काष्ठा compress_ctx cc = अणु
		.inode = inode,
		.log_cluster_size = F2FS_I(inode)->i_log_cluster_size,
		.cluster_size = F2FS_I(inode)->i_cluster_size,
		.rpages = fsdata,
	पूर्ण;
	bool first_index = (index == cc.rpages[0]->index);

	अगर (copied)
		set_cluster_dirty(&cc);

	f2fs_put_rpages_wbc(&cc, शून्य, false, 1);
	f2fs_destroy_compress_ctx(&cc, false);

	वापस first_index;
पूर्ण

पूर्णांक f2fs_truncate_partial_cluster(काष्ठा inode *inode, u64 from, bool lock)
अणु
	व्योम *fsdata = शून्य;
	काष्ठा page *pagep;
	पूर्णांक log_cluster_size = F2FS_I(inode)->i_log_cluster_size;
	pgoff_t start_idx = from >> (PAGE_SHIFT + log_cluster_size) <<
							log_cluster_size;
	पूर्णांक err;

	err = f2fs_is_compressed_cluster(inode, start_idx);
	अगर (err < 0)
		वापस err;

	/* truncate normal cluster */
	अगर (!err)
		वापस f2fs_करो_truncate_blocks(inode, from, lock);

	/* truncate compressed cluster */
	err = f2fs_prepare_compress_overग_लिखो(inode, &pagep,
						start_idx, &fsdata);

	/* should not be a normal cluster */
	f2fs_bug_on(F2FS_I_SB(inode), err == 0);

	अगर (err <= 0)
		वापस err;

	अगर (err > 0) अणु
		काष्ठा page **rpages = fsdata;
		पूर्णांक cluster_size = F2FS_I(inode)->i_cluster_size;
		पूर्णांक i;

		क्रम (i = cluster_size - 1; i >= 0; i--) अणु
			loff_t start = rpages[i]->index << PAGE_SHIFT;

			अगर (from <= start) अणु
				zero_user_segment(rpages[i], 0, PAGE_SIZE);
			पूर्ण अन्यथा अणु
				zero_user_segment(rpages[i], from - start,
								PAGE_SIZE);
				अवरोध;
			पूर्ण
		पूर्ण

		f2fs_compress_ग_लिखो_end(inode, fsdata, start_idx, true);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_compressed_pages(काष्ठा compress_ctx *cc,
					पूर्णांक *submitted,
					काष्ठा ग_लिखोback_control *wbc,
					क्रमागत iostat_type io_type)
अणु
	काष्ठा inode *inode = cc->inode;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा f2fs_io_info fio = अणु
		.sbi = sbi,
		.ino = cc->inode->i_ino,
		.type = DATA,
		.op = REQ_OP_WRITE,
		.op_flags = wbc_to_ग_लिखो_flags(wbc),
		.old_blkaddr = NEW_ADDR,
		.page = शून्य,
		.encrypted_page = शून्य,
		.compressed_page = शून्य,
		.submitted = false,
		.io_type = io_type,
		.io_wbc = wbc,
		.encrypted = fscrypt_inode_uses_fs_layer_crypto(cc->inode),
	पूर्ण;
	काष्ठा dnode_of_data dn;
	काष्ठा node_info ni;
	काष्ठा compress_io_ctx *cic;
	pgoff_t start_idx = start_idx_of_cluster(cc);
	अचिन्हित पूर्णांक last_index = cc->cluster_size - 1;
	loff_t psize;
	पूर्णांक i, err;

	अगर (IS_NOQUOTA(inode)) अणु
		/*
		 * We need to रुको क्रम node_ग_लिखो to aव्योम block allocation during
		 * checkpoपूर्णांक. This can only happen to quota ग_लिखोs which can cause
		 * the below discard race condition.
		 */
		करोwn_पढ़ो(&sbi->node_ग_लिखो);
	पूर्ण अन्यथा अगर (!f2fs_trylock_op(sbi)) अणु
		जाओ out_मुक्त;
	पूर्ण

	set_new_dnode(&dn, cc->inode, शून्य, शून्य, 0);

	err = f2fs_get_dnode_of_data(&dn, start_idx, LOOKUP_NODE);
	अगर (err)
		जाओ out_unlock_op;

	क्रम (i = 0; i < cc->cluster_size; i++) अणु
		अगर (data_blkaddr(dn.inode, dn.node_page,
					dn.ofs_in_node + i) == शून्य_ADDR)
			जाओ out_put_dnode;
	पूर्ण

	psize = (loff_t)(cc->rpages[last_index]->index + 1) << PAGE_SHIFT;

	err = f2fs_get_node_info(fio.sbi, dn.nid, &ni);
	अगर (err)
		जाओ out_put_dnode;

	fio.version = ni.version;

	cic = kmem_cache_zalloc(cic_entry_slab, GFP_NOFS);
	अगर (!cic)
		जाओ out_put_dnode;

	cic->magic = F2FS_COMPRESSED_PAGE_MAGIC;
	cic->inode = inode;
	atomic_set(&cic->pending_pages, cc->nr_cpages);
	cic->rpages = page_array_alloc(cc->inode, cc->cluster_size);
	अगर (!cic->rpages)
		जाओ out_put_cic;

	cic->nr_rpages = cc->cluster_size;

	क्रम (i = 0; i < cc->nr_cpages; i++) अणु
		f2fs_set_compressed_page(cc->cpages[i], inode,
					cc->rpages[i + 1]->index, cic);
		fio.compressed_page = cc->cpages[i];

		fio.old_blkaddr = data_blkaddr(dn.inode, dn.node_page,
						dn.ofs_in_node + i + 1);

		/* रुको क्रम GCed page ग_लिखोback via META_MAPPING */
		f2fs_रुको_on_block_ग_लिखोback(inode, fio.old_blkaddr);

		अगर (fio.encrypted) अणु
			fio.page = cc->rpages[i + 1];
			err = f2fs_encrypt_one_page(&fio);
			अगर (err)
				जाओ out_destroy_crypt;
			cc->cpages[i] = fio.encrypted_page;
		पूर्ण
	पूर्ण

	set_cluster_ग_लिखोback(cc);

	क्रम (i = 0; i < cc->cluster_size; i++)
		cic->rpages[i] = cc->rpages[i];

	क्रम (i = 0; i < cc->cluster_size; i++, dn.ofs_in_node++) अणु
		block_t blkaddr;

		blkaddr = f2fs_data_blkaddr(&dn);
		fio.page = cc->rpages[i];
		fio.old_blkaddr = blkaddr;

		/* cluster header */
		अगर (i == 0) अणु
			अगर (blkaddr == COMPRESS_ADDR)
				fio.compr_blocks++;
			अगर (__is_valid_data_blkaddr(blkaddr))
				f2fs_invalidate_blocks(sbi, blkaddr);
			f2fs_update_data_blkaddr(&dn, COMPRESS_ADDR);
			जाओ unlock_जारी;
		पूर्ण

		अगर (fio.compr_blocks && __is_valid_data_blkaddr(blkaddr))
			fio.compr_blocks++;

		अगर (i > cc->nr_cpages) अणु
			अगर (__is_valid_data_blkaddr(blkaddr)) अणु
				f2fs_invalidate_blocks(sbi, blkaddr);
				f2fs_update_data_blkaddr(&dn, NEW_ADDR);
			पूर्ण
			जाओ unlock_जारी;
		पूर्ण

		f2fs_bug_on(fio.sbi, blkaddr == शून्य_ADDR);

		अगर (fio.encrypted)
			fio.encrypted_page = cc->cpages[i - 1];
		अन्यथा
			fio.compressed_page = cc->cpages[i - 1];

		cc->cpages[i - 1] = शून्य;
		f2fs_outplace_ग_लिखो_data(&dn, &fio);
		(*submitted)++;
unlock_जारी:
		inode_dec_dirty_pages(cc->inode);
		unlock_page(fio.page);
	पूर्ण

	अगर (fio.compr_blocks)
		f2fs_i_compr_blocks_update(inode, fio.compr_blocks - 1, false);
	f2fs_i_compr_blocks_update(inode, cc->nr_cpages, true);
	add_compr_block_stat(inode, cc->nr_cpages);

	set_inode_flag(cc->inode, FI_APPEND_WRITE);
	अगर (cc->cluster_idx == 0)
		set_inode_flag(inode, FI_FIRST_BLOCK_WRITTEN);

	f2fs_put_dnode(&dn);
	अगर (IS_NOQUOTA(inode))
		up_पढ़ो(&sbi->node_ग_लिखो);
	अन्यथा
		f2fs_unlock_op(sbi);

	spin_lock(&fi->i_size_lock);
	अगर (fi->last_disk_size < psize)
		fi->last_disk_size = psize;
	spin_unlock(&fi->i_size_lock);

	f2fs_put_rpages(cc);
	page_array_मुक्त(cc->inode, cc->cpages, cc->nr_cpages);
	cc->cpages = शून्य;
	f2fs_destroy_compress_ctx(cc, false);
	वापस 0;

out_destroy_crypt:
	page_array_मुक्त(cc->inode, cic->rpages, cc->cluster_size);

	क्रम (--i; i >= 0; i--)
		fscrypt_finalize_bounce_page(&cc->cpages[i]);
	क्रम (i = 0; i < cc->nr_cpages; i++) अणु
		अगर (!cc->cpages[i])
			जारी;
		f2fs_compress_मुक्त_page(cc->cpages[i]);
		cc->cpages[i] = शून्य;
	पूर्ण
out_put_cic:
	kmem_cache_मुक्त(cic_entry_slab, cic);
out_put_dnode:
	f2fs_put_dnode(&dn);
out_unlock_op:
	अगर (IS_NOQUOTA(inode))
		up_पढ़ो(&sbi->node_ग_लिखो);
	अन्यथा
		f2fs_unlock_op(sbi);
out_मुक्त:
	page_array_मुक्त(cc->inode, cc->cpages, cc->nr_cpages);
	cc->cpages = शून्य;
	वापस -EAGAIN;
पूर्ण

व्योम f2fs_compress_ग_लिखो_end_io(काष्ठा bio *bio, काष्ठा page *page)
अणु
	काष्ठा f2fs_sb_info *sbi = bio->bi_निजी;
	काष्ठा compress_io_ctx *cic =
			(काष्ठा compress_io_ctx *)page_निजी(page);
	पूर्णांक i;

	अगर (unlikely(bio->bi_status))
		mapping_set_error(cic->inode->i_mapping, -EIO);

	f2fs_compress_मुक्त_page(page);

	dec_page_count(sbi, F2FS_WB_DATA);

	अगर (atomic_dec_वापस(&cic->pending_pages))
		वापस;

	क्रम (i = 0; i < cic->nr_rpages; i++) अणु
		WARN_ON(!cic->rpages[i]);
		clear_cold_data(cic->rpages[i]);
		end_page_ग_लिखोback(cic->rpages[i]);
	पूर्ण

	page_array_मुक्त(cic->inode, cic->rpages, cic->nr_rpages);
	kmem_cache_मुक्त(cic_entry_slab, cic);
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_raw_pages(काष्ठा compress_ctx *cc,
					पूर्णांक *submitted,
					काष्ठा ग_लिखोback_control *wbc,
					क्रमागत iostat_type io_type)
अणु
	काष्ठा address_space *mapping = cc->inode->i_mapping;
	पूर्णांक _submitted, compr_blocks, ret;
	पूर्णांक i = -1, err = 0;

	compr_blocks = f2fs_compressed_blocks(cc);
	अगर (compr_blocks < 0) अणु
		err = compr_blocks;
		जाओ out_err;
	पूर्ण

	क्रम (i = 0; i < cc->cluster_size; i++) अणु
		अगर (!cc->rpages[i])
			जारी;
retry_ग_लिखो:
		अगर (cc->rpages[i]->mapping != mapping) अणु
			unlock_page(cc->rpages[i]);
			जारी;
		पूर्ण

		BUG_ON(!PageLocked(cc->rpages[i]));

		ret = f2fs_ग_लिखो_single_data_page(cc->rpages[i], &_submitted,
						शून्य, शून्य, wbc, io_type,
						compr_blocks, false);
		अगर (ret) अणु
			अगर (ret == AOP_WRITEPAGE_ACTIVATE) अणु
				unlock_page(cc->rpages[i]);
				ret = 0;
			पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
				/*
				 * क्रम quota file, just redirty left pages to
				 * aव्योम deadlock caused by cluster update race
				 * from क्रमeground operation.
				 */
				अगर (IS_NOQUOTA(cc->inode)) अणु
					err = 0;
					जाओ out_err;
				पूर्ण
				ret = 0;
				cond_resched();
				congestion_रुको(BLK_RW_ASYNC,
						DEFAULT_IO_TIMEOUT);
				lock_page(cc->rpages[i]);

				अगर (!PageDirty(cc->rpages[i])) अणु
					unlock_page(cc->rpages[i]);
					जारी;
				पूर्ण

				clear_page_dirty_क्रम_io(cc->rpages[i]);
				जाओ retry_ग_लिखो;
			पूर्ण
			err = ret;
			जाओ out_err;
		पूर्ण

		*submitted += _submitted;
	पूर्ण

	f2fs_balance_fs(F2FS_M_SB(mapping), true);

	वापस 0;
out_err:
	क्रम (++i; i < cc->cluster_size; i++) अणु
		अगर (!cc->rpages[i])
			जारी;
		redirty_page_क्रम_ग_लिखोpage(wbc, cc->rpages[i]);
		unlock_page(cc->rpages[i]);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक f2fs_ग_लिखो_multi_pages(काष्ठा compress_ctx *cc,
					पूर्णांक *submitted,
					काष्ठा ग_लिखोback_control *wbc,
					क्रमागत iostat_type io_type)
अणु
	पूर्णांक err;

	*submitted = 0;
	अगर (cluster_may_compress(cc)) अणु
		err = f2fs_compress_pages(cc);
		अगर (err == -EAGAIN) अणु
			जाओ ग_लिखो;
		पूर्ण अन्यथा अगर (err) अणु
			f2fs_put_rpages_wbc(cc, wbc, true, 1);
			जाओ destroy_out;
		पूर्ण

		err = f2fs_ग_लिखो_compressed_pages(cc, submitted,
							wbc, io_type);
		अगर (!err)
			वापस 0;
		f2fs_bug_on(F2FS_I_SB(cc->inode), err != -EAGAIN);
	पूर्ण
ग_लिखो:
	f2fs_bug_on(F2FS_I_SB(cc->inode), *submitted);

	err = f2fs_ग_लिखो_raw_pages(cc, submitted, wbc, io_type);
	f2fs_put_rpages_wbc(cc, wbc, false, 0);
destroy_out:
	f2fs_destroy_compress_ctx(cc, false);
	वापस err;
पूर्ण

अटल व्योम f2fs_मुक्त_dic(काष्ठा decompress_io_ctx *dic);

काष्ठा decompress_io_ctx *f2fs_alloc_dic(काष्ठा compress_ctx *cc)
अणु
	काष्ठा decompress_io_ctx *dic;
	pgoff_t start_idx = start_idx_of_cluster(cc);
	पूर्णांक i;

	dic = kmem_cache_zalloc(dic_entry_slab, GFP_NOFS);
	अगर (!dic)
		वापस ERR_PTR(-ENOMEM);

	dic->rpages = page_array_alloc(cc->inode, cc->cluster_size);
	अगर (!dic->rpages) अणु
		kmem_cache_मुक्त(dic_entry_slab, dic);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dic->magic = F2FS_COMPRESSED_PAGE_MAGIC;
	dic->inode = cc->inode;
	atomic_set(&dic->reमुख्यing_pages, cc->nr_cpages);
	dic->cluster_idx = cc->cluster_idx;
	dic->cluster_size = cc->cluster_size;
	dic->log_cluster_size = cc->log_cluster_size;
	dic->nr_cpages = cc->nr_cpages;
	refcount_set(&dic->refcnt, 1);
	dic->failed = false;
	dic->need_verity = f2fs_need_verity(cc->inode, start_idx);

	क्रम (i = 0; i < dic->cluster_size; i++)
		dic->rpages[i] = cc->rpages[i];
	dic->nr_rpages = cc->cluster_size;

	dic->cpages = page_array_alloc(dic->inode, dic->nr_cpages);
	अगर (!dic->cpages)
		जाओ out_मुक्त;

	क्रम (i = 0; i < dic->nr_cpages; i++) अणु
		काष्ठा page *page;

		page = f2fs_compress_alloc_page();
		अगर (!page)
			जाओ out_मुक्त;

		f2fs_set_compressed_page(page, cc->inode,
					start_idx + i + 1, dic);
		dic->cpages[i] = page;
	पूर्ण

	वापस dic;

out_मुक्त:
	f2fs_मुक्त_dic(dic);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम f2fs_मुक्त_dic(काष्ठा decompress_io_ctx *dic)
अणु
	पूर्णांक i;

	अगर (dic->tpages) अणु
		क्रम (i = 0; i < dic->cluster_size; i++) अणु
			अगर (dic->rpages[i])
				जारी;
			अगर (!dic->tpages[i])
				जारी;
			f2fs_compress_मुक्त_page(dic->tpages[i]);
		पूर्ण
		page_array_मुक्त(dic->inode, dic->tpages, dic->cluster_size);
	पूर्ण

	अगर (dic->cpages) अणु
		क्रम (i = 0; i < dic->nr_cpages; i++) अणु
			अगर (!dic->cpages[i])
				जारी;
			f2fs_compress_मुक्त_page(dic->cpages[i]);
		पूर्ण
		page_array_मुक्त(dic->inode, dic->cpages, dic->nr_cpages);
	पूर्ण

	page_array_मुक्त(dic->inode, dic->rpages, dic->nr_rpages);
	kmem_cache_मुक्त(dic_entry_slab, dic);
पूर्ण

अटल व्योम f2fs_put_dic(काष्ठा decompress_io_ctx *dic)
अणु
	अगर (refcount_dec_and_test(&dic->refcnt))
		f2fs_मुक्त_dic(dic);
पूर्ण

/*
 * Update and unlock the cluster's pagecache pages, and release the reference to
 * the decompress_io_ctx that was being held क्रम I/O completion.
 */
अटल व्योम __f2fs_decompress_end_io(काष्ठा decompress_io_ctx *dic, bool failed)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dic->cluster_size; i++) अणु
		काष्ठा page *rpage = dic->rpages[i];

		अगर (!rpage)
			जारी;

		/* PG_error was set अगर verity failed. */
		अगर (failed || PageError(rpage)) अणु
			ClearPageUptodate(rpage);
			/* will re-पढ़ो again later */
			ClearPageError(rpage);
		पूर्ण अन्यथा अणु
			SetPageUptodate(rpage);
		पूर्ण
		unlock_page(rpage);
	पूर्ण

	f2fs_put_dic(dic);
पूर्ण

अटल व्योम f2fs_verअगरy_cluster(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा decompress_io_ctx *dic =
		container_of(work, काष्ठा decompress_io_ctx, verity_work);
	पूर्णांक i;

	/* Verअगरy the cluster's decompressed pages with fs-verity. */
	क्रम (i = 0; i < dic->cluster_size; i++) अणु
		काष्ठा page *rpage = dic->rpages[i];

		अगर (rpage && !fsverity_verअगरy_page(rpage))
			SetPageError(rpage);
	पूर्ण

	__f2fs_decompress_end_io(dic, false);
पूर्ण

/*
 * This is called when a compressed cluster has been decompressed
 * (or failed to be पढ़ो and/or decompressed).
 */
व्योम f2fs_decompress_end_io(काष्ठा decompress_io_ctx *dic, bool failed)
अणु
	अगर (!failed && dic->need_verity) अणु
		/*
		 * Note that to aव्योम deadlocks, the verity work can't be करोne
		 * on the decompression workqueue.  This is because verअगरying
		 * the data pages can involve पढ़ोing metadata pages from the
		 * file, and these metadata pages may be compressed.
		 */
		INIT_WORK(&dic->verity_work, f2fs_verअगरy_cluster);
		fsverity_enqueue_verअगरy_work(&dic->verity_work);
	पूर्ण अन्यथा अणु
		__f2fs_decompress_end_io(dic, failed);
	पूर्ण
पूर्ण

/*
 * Put a reference to a compressed page's decompress_io_ctx.
 *
 * This is called when the page is no दीर्घer needed and can be मुक्तd.
 */
व्योम f2fs_put_page_dic(काष्ठा page *page)
अणु
	काष्ठा decompress_io_ctx *dic =
			(काष्ठा decompress_io_ctx *)page_निजी(page);

	f2fs_put_dic(dic);
पूर्ण

पूर्णांक f2fs_init_page_array_cache(काष्ठा f2fs_sb_info *sbi)
अणु
	dev_t dev = sbi->sb->s_bdev->bd_dev;
	अक्षर slab_name[32];

	प्र_लिखो(slab_name, "f2fs_page_array_entry-%u:%u", MAJOR(dev), MINOR(dev));

	sbi->page_array_slab_size = माप(काष्ठा page *) <<
					F2FS_OPTION(sbi).compress_log_size;

	sbi->page_array_slab = f2fs_kmem_cache_create(slab_name,
					sbi->page_array_slab_size);
	अगर (!sbi->page_array_slab)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम f2fs_destroy_page_array_cache(काष्ठा f2fs_sb_info *sbi)
अणु
	kmem_cache_destroy(sbi->page_array_slab);
पूर्ण

अटल पूर्णांक __init f2fs_init_cic_cache(व्योम)
अणु
	cic_entry_slab = f2fs_kmem_cache_create("f2fs_cic_entry",
					माप(काष्ठा compress_io_ctx));
	अगर (!cic_entry_slab)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम f2fs_destroy_cic_cache(व्योम)
अणु
	kmem_cache_destroy(cic_entry_slab);
पूर्ण

अटल पूर्णांक __init f2fs_init_dic_cache(व्योम)
अणु
	dic_entry_slab = f2fs_kmem_cache_create("f2fs_dic_entry",
					माप(काष्ठा decompress_io_ctx));
	अगर (!dic_entry_slab)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम f2fs_destroy_dic_cache(व्योम)
अणु
	kmem_cache_destroy(dic_entry_slab);
पूर्ण

पूर्णांक __init f2fs_init_compress_cache(व्योम)
अणु
	पूर्णांक err;

	err = f2fs_init_cic_cache();
	अगर (err)
		जाओ out;
	err = f2fs_init_dic_cache();
	अगर (err)
		जाओ मुक्त_cic;
	वापस 0;
मुक्त_cic:
	f2fs_destroy_cic_cache();
out:
	वापस -ENOMEM;
पूर्ण

व्योम f2fs_destroy_compress_cache(व्योम)
अणु
	f2fs_destroy_dic_cache();
	f2fs_destroy_cic_cache();
पूर्ण
