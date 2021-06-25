<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP Crypto driver common support routines.
 *
 * Copyright (c) 2017 Texas Instruments Incorporated
 *   Tero Kristo <t-kristo@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/scatterwalk.h>

#समावेश "omap-crypto.h"

अटल पूर्णांक omap_crypto_copy_sg_lists(पूर्णांक total, पूर्णांक bs,
				     काष्ठा scatterlist **sg,
				     काष्ठा scatterlist *new_sg, u16 flags)
अणु
	पूर्णांक n = sg_nents(*sg);
	काष्ठा scatterlist *पंचांगp;

	अगर (!(flags & OMAP_CRYPTO_FORCE_SINGLE_ENTRY)) अणु
		new_sg = kदो_स्मृति_array(n, माप(*sg), GFP_KERNEL);
		अगर (!new_sg)
			वापस -ENOMEM;

		sg_init_table(new_sg, n);
	पूर्ण

	पंचांगp = new_sg;

	जबतक (*sg && total) अणु
		पूर्णांक len = (*sg)->length;

		अगर (total < len)
			len = total;

		अगर (len > 0) अणु
			total -= len;
			sg_set_page(पंचांगp, sg_page(*sg), len, (*sg)->offset);
			अगर (total <= 0)
				sg_mark_end(पंचांगp);
			पंचांगp = sg_next(पंचांगp);
		पूर्ण

		*sg = sg_next(*sg);
	पूर्ण

	*sg = new_sg;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_crypto_copy_sgs(पूर्णांक total, पूर्णांक bs, काष्ठा scatterlist **sg,
				काष्ठा scatterlist *new_sg, u16 flags)
अणु
	व्योम *buf;
	पूर्णांक pages;
	पूर्णांक new_len;

	new_len = ALIGN(total, bs);
	pages = get_order(new_len);

	buf = (व्योम *)__get_मुक्त_pages(GFP_ATOMIC, pages);
	अगर (!buf) अणु
		pr_err("%s: Couldn't allocate pages for unaligned cases.\n",
		       __func__);
		वापस -ENOMEM;
	पूर्ण

	अगर (flags & OMAP_CRYPTO_COPY_DATA) अणु
		scatterwalk_map_and_copy(buf, *sg, 0, total, 0);
		अगर (flags & OMAP_CRYPTO_ZERO_BUF)
			स_रखो(buf + total, 0, new_len - total);
	पूर्ण

	अगर (!(flags & OMAP_CRYPTO_FORCE_SINGLE_ENTRY))
		sg_init_table(new_sg, 1);

	sg_set_buf(new_sg, buf, new_len);

	*sg = new_sg;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_crypto_check_sg(काष्ठा scatterlist *sg, पूर्णांक total, पूर्णांक bs,
				u16 flags)
अणु
	पूर्णांक len = 0;
	पूर्णांक num_sg = 0;

	अगर (!IS_ALIGNED(total, bs))
		वापस OMAP_CRYPTO_NOT_ALIGNED;

	जबतक (sg) अणु
		num_sg++;

		अगर (!IS_ALIGNED(sg->offset, 4))
			वापस OMAP_CRYPTO_NOT_ALIGNED;
		अगर (!IS_ALIGNED(sg->length, bs))
			वापस OMAP_CRYPTO_NOT_ALIGNED;
#अगर_घोषित CONFIG_ZONE_DMA
		अगर (page_zonक्रमागत(sg_page(sg)) != ZONE_DMA)
			वापस OMAP_CRYPTO_NOT_ALIGNED;
#पूर्ण_अगर

		len += sg->length;
		sg = sg_next(sg);

		अगर (len >= total)
			अवरोध;
	पूर्ण

	अगर ((flags & OMAP_CRYPTO_FORCE_SINGLE_ENTRY) && num_sg > 1)
		वापस OMAP_CRYPTO_NOT_ALIGNED;

	अगर (len != total)
		वापस OMAP_CRYPTO_BAD_DATA_LENGTH;

	वापस 0;
पूर्ण

पूर्णांक omap_crypto_align_sg(काष्ठा scatterlist **sg, पूर्णांक total, पूर्णांक bs,
			 काष्ठा scatterlist *new_sg, u16 flags,
			 u8 flags_shअगरt, अचिन्हित दीर्घ *dd_flags)
अणु
	पूर्णांक ret;

	*dd_flags &= ~(OMAP_CRYPTO_COPY_MASK << flags_shअगरt);

	अगर (flags & OMAP_CRYPTO_FORCE_COPY)
		ret = OMAP_CRYPTO_NOT_ALIGNED;
	अन्यथा
		ret = omap_crypto_check_sg(*sg, total, bs, flags);

	अगर (ret == OMAP_CRYPTO_NOT_ALIGNED) अणु
		ret = omap_crypto_copy_sgs(total, bs, sg, new_sg, flags);
		अगर (ret)
			वापस ret;
		*dd_flags |= OMAP_CRYPTO_DATA_COPIED << flags_shअगरt;
	पूर्ण अन्यथा अगर (ret == OMAP_CRYPTO_BAD_DATA_LENGTH) अणु
		ret = omap_crypto_copy_sg_lists(total, bs, sg, new_sg, flags);
		अगर (ret)
			वापस ret;
		अगर (!(flags & OMAP_CRYPTO_FORCE_SINGLE_ENTRY))
			*dd_flags |= OMAP_CRYPTO_SG_COPIED << flags_shअगरt;
	पूर्ण अन्यथा अगर (flags & OMAP_CRYPTO_FORCE_SINGLE_ENTRY) अणु
		sg_set_buf(new_sg, sg_virt(*sg), (*sg)->length);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_crypto_align_sg);

अटल व्योम omap_crypto_copy_data(काष्ठा scatterlist *src,
				  काष्ठा scatterlist *dst,
				  पूर्णांक offset, पूर्णांक len)
अणु
	पूर्णांक amt;
	व्योम *srcb, *dstb;
	पूर्णांक srco = 0, dsto = offset;

	जबतक (src && dst && len) अणु
		अगर (srco >= src->length) अणु
			srco -= src->length;
			src = sg_next(src);
			जारी;
		पूर्ण

		अगर (dsto >= dst->length) अणु
			dsto -= dst->length;
			dst = sg_next(dst);
			जारी;
		पूर्ण

		amt = min(src->length - srco, dst->length - dsto);
		amt = min(len, amt);

		srcb = kmap_atomic(sg_page(src)) + srco + src->offset;
		dstb = kmap_atomic(sg_page(dst)) + dsto + dst->offset;

		स_नकल(dstb, srcb, amt);

		अगर (!PageSlab(sg_page(dst)))
			flush_kernel_dcache_page(sg_page(dst));

		kunmap_atomic(srcb);
		kunmap_atomic(dstb);

		srco += amt;
		dsto += amt;
		len -= amt;
	पूर्ण
पूर्ण

व्योम omap_crypto_cleanup(काष्ठा scatterlist *sg, काष्ठा scatterlist *orig,
			 पूर्णांक offset, पूर्णांक len, u8 flags_shअगरt,
			 अचिन्हित दीर्घ flags)
अणु
	व्योम *buf;
	पूर्णांक pages;

	flags >>= flags_shअगरt;
	flags &= OMAP_CRYPTO_COPY_MASK;

	अगर (!flags)
		वापस;

	buf = sg_virt(sg);
	pages = get_order(len);

	अगर (orig && (flags & OMAP_CRYPTO_COPY_MASK))
		omap_crypto_copy_data(sg, orig, offset, len);

	अगर (flags & OMAP_CRYPTO_DATA_COPIED)
		मुक्त_pages((अचिन्हित दीर्घ)buf, pages);
	अन्यथा अगर (flags & OMAP_CRYPTO_SG_COPIED)
		kमुक्त(sg);
पूर्ण
EXPORT_SYMBOL_GPL(omap_crypto_cleanup);

MODULE_DESCRIPTION("OMAP crypto support library.");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Tero Kristo <t-kristo@ti.com>");
