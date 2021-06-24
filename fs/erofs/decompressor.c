<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2019 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश "compress.h"
#समावेश <linux/module.h>
#समावेश <linux/lz4.h>

#अगर_अघोषित LZ4_DISTANCE_MAX	/* history winकरोw size */
#घोषणा LZ4_DISTANCE_MAX 65535	/* set to maximum value by शेष */
#पूर्ण_अगर

#घोषणा LZ4_MAX_DISTANCE_PAGES	(DIV_ROUND_UP(LZ4_DISTANCE_MAX, PAGE_SIZE) + 1)
#अगर_अघोषित LZ4_DECOMPRESS_INPLACE_MARGIN
#घोषणा LZ4_DECOMPRESS_INPLACE_MARGIN(srcsize)  (((srcsize) >> 8) + 32)
#पूर्ण_अगर

काष्ठा z_erofs_decompressor अणु
	/*
	 * अगर destpages have sparsed pages, fill them with bounce pages.
	 * it also check whether destpages indicate continuous physical memory.
	 */
	पूर्णांक (*prepare_destpages)(काष्ठा z_erofs_decompress_req *rq,
				 काष्ठा list_head *pagepool);
	पूर्णांक (*decompress)(काष्ठा z_erofs_decompress_req *rq, u8 *out);
	अक्षर *name;
पूर्ण;

पूर्णांक z_erofs_load_lz4_config(काष्ठा super_block *sb,
			    काष्ठा erofs_super_block *dsb,
			    काष्ठा z_erofs_lz4_cfgs *lz4, पूर्णांक size)
अणु
	काष्ठा erofs_sb_info *sbi = EROFS_SB(sb);
	u16 distance;

	अगर (lz4) अणु
		अगर (size < माप(काष्ठा z_erofs_lz4_cfgs)) अणु
			erofs_err(sb, "invalid lz4 cfgs, size=%u", size);
			वापस -EINVAL;
		पूर्ण
		distance = le16_to_cpu(lz4->max_distance);

		sbi->lz4.max_pclusterblks = le16_to_cpu(lz4->max_pclusterblks);
		अगर (!sbi->lz4.max_pclusterblks) अणु
			sbi->lz4.max_pclusterblks = 1;	/* reserved हाल */
		पूर्ण अन्यथा अगर (sbi->lz4.max_pclusterblks >
			   Z_EROFS_PCLUSTER_MAX_SIZE / EROFS_BLKSIZ) अणु
			erofs_err(sb, "too large lz4 pclusterblks %u",
				  sbi->lz4.max_pclusterblks);
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (sbi->lz4.max_pclusterblks >= 2) अणु
			erofs_info(sb, "EXPERIMENTAL big pcluster feature in use. Use at your own risk!");
		पूर्ण
	पूर्ण अन्यथा अणु
		distance = le16_to_cpu(dsb->u1.lz4_max_distance);
		sbi->lz4.max_pclusterblks = 1;
	पूर्ण

	sbi->lz4.max_distance_pages = distance ?
					DIV_ROUND_UP(distance, PAGE_SIZE) + 1 :
					LZ4_MAX_DISTANCE_PAGES;
	वापस erofs_pcpubuf_growsize(sbi->lz4.max_pclusterblks);
पूर्ण

अटल पूर्णांक z_erofs_lz4_prepare_destpages(काष्ठा z_erofs_decompress_req *rq,
					 काष्ठा list_head *pagepool)
अणु
	स्थिर अचिन्हित पूर्णांक nr =
		PAGE_ALIGN(rq->pageofs_out + rq->outमाला_दोize) >> PAGE_SHIFT;
	काष्ठा page *availables[LZ4_MAX_DISTANCE_PAGES] = अणु शून्य पूर्ण;
	अचिन्हित दीर्घ bounced[DIV_ROUND_UP(LZ4_MAX_DISTANCE_PAGES,
					   BITS_PER_LONG)] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक lz4_max_distance_pages =
				EROFS_SB(rq->sb)->lz4.max_distance_pages;
	व्योम *kaddr = शून्य;
	अचिन्हित पूर्णांक i, j, top;

	top = 0;
	क्रम (i = j = 0; i < nr; ++i, ++j) अणु
		काष्ठा page *स्थिर page = rq->out[i];
		काष्ठा page *victim;

		अगर (j >= lz4_max_distance_pages)
			j = 0;

		/* 'valid' bounced can only be tested after a complete round */
		अगर (test_bit(j, bounced)) अणु
			DBG_BUGON(i < lz4_max_distance_pages);
			DBG_BUGON(top >= lz4_max_distance_pages);
			availables[top++] = rq->out[i - lz4_max_distance_pages];
		पूर्ण

		अगर (page) अणु
			__clear_bit(j, bounced);
			अगर (kaddr) अणु
				अगर (kaddr + PAGE_SIZE == page_address(page))
					kaddr += PAGE_SIZE;
				अन्यथा
					kaddr = शून्य;
			पूर्ण अन्यथा अगर (!i) अणु
				kaddr = page_address(page);
			पूर्ण
			जारी;
		पूर्ण
		kaddr = शून्य;
		__set_bit(j, bounced);

		अगर (top) अणु
			victim = availables[--top];
			get_page(victim);
		पूर्ण अन्यथा अणु
			victim = erofs_allocpage(pagepool,
						 GFP_KERNEL | __GFP_NOFAIL);
			set_page_निजी(victim, Z_EROFS_SHORTLIVED_PAGE);
		पूर्ण
		rq->out[i] = victim;
	पूर्ण
	वापस kaddr ? 1 : 0;
पूर्ण

अटल व्योम *z_erofs_handle_inplace_io(काष्ठा z_erofs_decompress_req *rq,
			व्योम *inpage, अचिन्हित पूर्णांक *inpuपंचांगargin, पूर्णांक *maptype,
			bool support_0padding)
अणु
	अचिन्हित पूर्णांक nrpages_in, nrpages_out;
	अचिन्हित पूर्णांक ofull, oend, inमाला_दोize, total, i, j;
	काष्ठा page **in;
	व्योम *src, *पंचांगp;

	inमाला_दोize = rq->inमाला_दोize;
	nrpages_in = PAGE_ALIGN(inमाला_दोize) >> PAGE_SHIFT;
	oend = rq->pageofs_out + rq->outमाला_दोize;
	ofull = PAGE_ALIGN(oend);
	nrpages_out = ofull >> PAGE_SHIFT;

	अगर (rq->inplace_io) अणु
		अगर (rq->partial_decoding || !support_0padding ||
		    ofull - oend < LZ4_DECOMPRESS_INPLACE_MARGIN(inमाला_दोize))
			जाओ करोcopy;

		क्रम (i = 0; i < nrpages_in; ++i) अणु
			DBG_BUGON(rq->in[i] == शून्य);
			क्रम (j = 0; j < nrpages_out - nrpages_in + i; ++j)
				अगर (rq->out[j] == rq->in[i])
					जाओ करोcopy;
		पूर्ण
	पूर्ण

	अगर (nrpages_in <= 1) अणु
		*maptype = 0;
		वापस inpage;
	पूर्ण
	kunmap_atomic(inpage);
	might_sleep();
	src = erofs_vm_map_ram(rq->in, nrpages_in);
	अगर (!src)
		वापस ERR_PTR(-ENOMEM);
	*maptype = 1;
	वापस src;

करोcopy:
	/* Or copy compressed data which can be overlapped to per-CPU buffer */
	in = rq->in;
	src = erofs_get_pcpubuf(nrpages_in);
	अगर (!src) अणु
		DBG_BUGON(1);
		kunmap_atomic(inpage);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	पंचांगp = src;
	total = rq->inमाला_दोize;
	जबतक (total) अणु
		अचिन्हित पूर्णांक page_copycnt =
			min_t(अचिन्हित पूर्णांक, total, PAGE_SIZE - *inpuपंचांगargin);

		अगर (!inpage)
			inpage = kmap_atomic(*in);
		स_नकल(पंचांगp, inpage + *inpuपंचांगargin, page_copycnt);
		kunmap_atomic(inpage);
		inpage = शून्य;
		पंचांगp += page_copycnt;
		total -= page_copycnt;
		++in;
		*inpuपंचांगargin = 0;
	पूर्ण
	*maptype = 2;
	वापस src;
पूर्ण

अटल पूर्णांक z_erofs_lz4_decompress(काष्ठा z_erofs_decompress_req *rq, u8 *out)
अणु
	अचिन्हित पूर्णांक inpuपंचांगargin;
	u8 *headpage, *src;
	bool support_0padding;
	पूर्णांक ret, maptype;

	DBG_BUGON(*rq->in == शून्य);
	headpage = kmap_atomic(*rq->in);
	inpuपंचांगargin = 0;
	support_0padding = false;

	/* decompression inplace is only safe when 0padding is enabled */
	अगर (erofs_sb_has_lz4_0padding(EROFS_SB(rq->sb))) अणु
		support_0padding = true;

		जबतक (!headpage[inpuपंचांगargin & ~PAGE_MASK])
			अगर (!(++inpuपंचांगargin & ~PAGE_MASK))
				अवरोध;

		अगर (inpuपंचांगargin >= rq->inमाला_दोize) अणु
			kunmap_atomic(headpage);
			वापस -EIO;
		पूर्ण
	पूर्ण

	rq->inमाला_दोize -= inpuपंचांगargin;
	src = z_erofs_handle_inplace_io(rq, headpage, &inpuपंचांगargin, &maptype,
					support_0padding);
	अगर (IS_ERR(src))
		वापस PTR_ERR(src);

	/* legacy क्रमmat could compress extra data in a pcluster. */
	अगर (rq->partial_decoding || !support_0padding)
		ret = LZ4_decompress_safe_partial(src + inpuपंचांगargin, out,
				rq->inमाला_दोize, rq->outमाला_दोize, rq->outमाला_दोize);
	अन्यथा
		ret = LZ4_decompress_safe(src + inpuपंचांगargin, out,
					  rq->inमाला_दोize, rq->outमाला_दोize);

	अगर (ret != rq->outमाला_दोize) अणु
		erofs_err(rq->sb, "failed to decompress %d in[%u, %u] out[%u]",
			  ret, rq->inमाला_दोize, inpuपंचांगargin, rq->outमाला_दोize);

		WARN_ON(1);
		prपूर्णांक_hex_dump(KERN_DEBUG, "[ in]: ", DUMP_PREFIX_OFFSET,
			       16, 1, src + inpuपंचांगargin, rq->inमाला_दोize, true);
		prपूर्णांक_hex_dump(KERN_DEBUG, "[out]: ", DUMP_PREFIX_OFFSET,
			       16, 1, out, rq->outमाला_दोize, true);

		अगर (ret >= 0)
			स_रखो(out + ret, 0, rq->outमाला_दोize - ret);
		ret = -EIO;
	पूर्ण

	अगर (maptype == 0) अणु
		kunmap_atomic(src);
	पूर्ण अन्यथा अगर (maptype == 1) अणु
		vm_unmap_ram(src, PAGE_ALIGN(rq->inमाला_दोize) >> PAGE_SHIFT);
	पूर्ण अन्यथा अगर (maptype == 2) अणु
		erofs_put_pcpubuf(src);
	पूर्ण अन्यथा अणु
		DBG_BUGON(1);
		वापस -EFAULT;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा z_erofs_decompressor decompressors[] = अणु
	[Z_EROFS_COMPRESSION_SHIFTED] = अणु
		.name = "shifted"
	पूर्ण,
	[Z_EROFS_COMPRESSION_LZ4] = अणु
		.prepare_destpages = z_erofs_lz4_prepare_destpages,
		.decompress = z_erofs_lz4_decompress,
		.name = "lz4"
	पूर्ण,
पूर्ण;

अटल व्योम copy_from_pcpubuf(काष्ठा page **out, स्थिर अक्षर *dst,
			      अचिन्हित लघु pageofs_out,
			      अचिन्हित पूर्णांक outमाला_दोize)
अणु
	स्थिर अक्षर *end = dst + outमाला_दोize;
	स्थिर अचिन्हित पूर्णांक righthalf = PAGE_SIZE - pageofs_out;
	स्थिर अक्षर *cur = dst - pageofs_out;

	जबतक (cur < end) अणु
		काष्ठा page *स्थिर page = *out++;

		अगर (page) अणु
			अक्षर *buf = kmap_atomic(page);

			अगर (cur >= dst) अणु
				स_नकल(buf, cur, min_t(uपूर्णांक, PAGE_SIZE,
						       end - cur));
			पूर्ण अन्यथा अणु
				स_नकल(buf + pageofs_out, cur + pageofs_out,
				       min_t(uपूर्णांक, righthalf, end - cur));
			पूर्ण
			kunmap_atomic(buf);
		पूर्ण
		cur += PAGE_SIZE;
	पूर्ण
पूर्ण

अटल पूर्णांक z_erofs_decompress_generic(काष्ठा z_erofs_decompress_req *rq,
				      काष्ठा list_head *pagepool)
अणु
	स्थिर अचिन्हित पूर्णांक nrpages_out =
		PAGE_ALIGN(rq->pageofs_out + rq->outमाला_दोize) >> PAGE_SHIFT;
	स्थिर काष्ठा z_erofs_decompressor *alg = decompressors + rq->alg;
	अचिन्हित पूर्णांक dst_maptype;
	व्योम *dst;
	पूर्णांक ret;

	/* two optimized fast paths only क्रम non bigpcluster हालs yet */
	अगर (rq->inमाला_दोize <= PAGE_SIZE) अणु
		अगर (nrpages_out == 1 && !rq->inplace_io) अणु
			DBG_BUGON(!*rq->out);
			dst = kmap_atomic(*rq->out);
			dst_maptype = 0;
			जाओ dsपंचांगap_out;
		पूर्ण

		/*
		 * For the हाल of small output size (especially much less
		 * than PAGE_SIZE), स_नकल the decompressed data rather than
		 * compressed data is preferred.
		 */
		अगर (rq->outमाला_दोize <= PAGE_SIZE * 7 / 8) अणु
			dst = erofs_get_pcpubuf(1);
			अगर (IS_ERR(dst))
				वापस PTR_ERR(dst);

			rq->inplace_io = false;
			ret = alg->decompress(rq, dst);
			अगर (!ret)
				copy_from_pcpubuf(rq->out, dst, rq->pageofs_out,
						  rq->outमाला_दोize);

			erofs_put_pcpubuf(dst);
			वापस ret;
		पूर्ण
	पूर्ण

	/* general decoding path which can be used क्रम all हालs */
	ret = alg->prepare_destpages(rq, pagepool);
	अगर (ret < 0)
		वापस ret;
	अगर (ret) अणु
		dst = page_address(*rq->out);
		dst_maptype = 1;
		जाओ dsपंचांगap_out;
	पूर्ण

	dst = erofs_vm_map_ram(rq->out, nrpages_out);
	अगर (!dst)
		वापस -ENOMEM;
	dst_maptype = 2;

dsपंचांगap_out:
	ret = alg->decompress(rq, dst + rq->pageofs_out);

	अगर (!dst_maptype)
		kunmap_atomic(dst);
	अन्यथा अगर (dst_maptype == 2)
		vm_unmap_ram(dst, nrpages_out);
	वापस ret;
पूर्ण

अटल पूर्णांक z_erofs_shअगरted_transक्रमm(स्थिर काष्ठा z_erofs_decompress_req *rq,
				     काष्ठा list_head *pagepool)
अणु
	स्थिर अचिन्हित पूर्णांक nrpages_out =
		PAGE_ALIGN(rq->pageofs_out + rq->outमाला_दोize) >> PAGE_SHIFT;
	स्थिर अचिन्हित पूर्णांक righthalf = PAGE_SIZE - rq->pageofs_out;
	अचिन्हित अक्षर *src, *dst;

	अगर (nrpages_out > 2) अणु
		DBG_BUGON(1);
		वापस -EIO;
	पूर्ण

	अगर (rq->out[0] == *rq->in) अणु
		DBG_BUGON(nrpages_out != 1);
		वापस 0;
	पूर्ण

	src = kmap_atomic(*rq->in);
	अगर (rq->out[0]) अणु
		dst = kmap_atomic(rq->out[0]);
		स_नकल(dst + rq->pageofs_out, src, righthalf);
		kunmap_atomic(dst);
	पूर्ण

	अगर (nrpages_out == 2) अणु
		DBG_BUGON(!rq->out[1]);
		अगर (rq->out[1] == *rq->in) अणु
			स_हटाओ(src, src + righthalf, rq->pageofs_out);
		पूर्ण अन्यथा अणु
			dst = kmap_atomic(rq->out[1]);
			स_नकल(dst, src + righthalf, rq->pageofs_out);
			kunmap_atomic(dst);
		पूर्ण
	पूर्ण
	kunmap_atomic(src);
	वापस 0;
पूर्ण

पूर्णांक z_erofs_decompress(काष्ठा z_erofs_decompress_req *rq,
		       काष्ठा list_head *pagepool)
अणु
	अगर (rq->alg == Z_EROFS_COMPRESSION_SHIFTED)
		वापस z_erofs_shअगरted_transक्रमm(rq, pagepool);
	वापस z_erofs_decompress_generic(rq, pagepool);
पूर्ण

