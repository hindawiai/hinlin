<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Symmetric key cipher operations.
 *
 * Generic encrypt/decrypt wrapper क्रम ciphers, handles operations across
 * multiple page boundaries by using temporary blocks.  In user context,
 * the kernel is given a chance to schedule us once per page.
 *
 * Copyright (c) 2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/bug.h>
#समावेश <linux/cryptouser.h>
#समावेश <linux/compiler.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/seq_file.h>
#समावेश <net/netlink.h>

#समावेश "internal.h"

क्रमागत अणु
	SKCIPHER_WALK_PHYS = 1 << 0,
	SKCIPHER_WALK_SLOW = 1 << 1,
	SKCIPHER_WALK_COPY = 1 << 2,
	SKCIPHER_WALK_DIFF = 1 << 3,
	SKCIPHER_WALK_SLEEP = 1 << 4,
पूर्ण;

काष्ठा skcipher_walk_buffer अणु
	काष्ठा list_head entry;
	काष्ठा scatter_walk dst;
	अचिन्हित पूर्णांक len;
	u8 *data;
	u8 buffer[];
पूर्ण;

अटल पूर्णांक skcipher_walk_next(काष्ठा skcipher_walk *walk);

अटल अंतरभूत व्योम skcipher_unmap(काष्ठा scatter_walk *walk, व्योम *vaddr)
अणु
	अगर (PageHighMem(scatterwalk_page(walk)))
		kunmap_atomic(vaddr);
पूर्ण

अटल अंतरभूत व्योम *skcipher_map(काष्ठा scatter_walk *walk)
अणु
	काष्ठा page *page = scatterwalk_page(walk);

	वापस (PageHighMem(page) ? kmap_atomic(page) : page_address(page)) +
	       offset_in_page(walk->offset);
पूर्ण

अटल अंतरभूत व्योम skcipher_map_src(काष्ठा skcipher_walk *walk)
अणु
	walk->src.virt.addr = skcipher_map(&walk->in);
पूर्ण

अटल अंतरभूत व्योम skcipher_map_dst(काष्ठा skcipher_walk *walk)
अणु
	walk->dst.virt.addr = skcipher_map(&walk->out);
पूर्ण

अटल अंतरभूत व्योम skcipher_unmap_src(काष्ठा skcipher_walk *walk)
अणु
	skcipher_unmap(&walk->in, walk->src.virt.addr);
पूर्ण

अटल अंतरभूत व्योम skcipher_unmap_dst(काष्ठा skcipher_walk *walk)
अणु
	skcipher_unmap(&walk->out, walk->dst.virt.addr);
पूर्ण

अटल अंतरभूत gfp_t skcipher_walk_gfp(काष्ठा skcipher_walk *walk)
अणु
	वापस walk->flags & SKCIPHER_WALK_SLEEP ? GFP_KERNEL : GFP_ATOMIC;
पूर्ण

/* Get a spot of the specअगरied length that करोes not straddle a page.
 * The caller needs to ensure that there is enough space क्रम this operation.
 */
अटल अंतरभूत u8 *skcipher_get_spot(u8 *start, अचिन्हित पूर्णांक len)
अणु
	u8 *end_page = (u8 *)(((अचिन्हित दीर्घ)(start + len - 1)) & PAGE_MASK);

	वापस max(start, end_page);
पूर्ण

अटल पूर्णांक skcipher_करोne_slow(काष्ठा skcipher_walk *walk, अचिन्हित पूर्णांक bsize)
अणु
	u8 *addr;

	addr = (u8 *)ALIGN((अचिन्हित दीर्घ)walk->buffer, walk->alignmask + 1);
	addr = skcipher_get_spot(addr, bsize);
	scatterwalk_copychunks(addr, &walk->out, bsize,
			       (walk->flags & SKCIPHER_WALK_PHYS) ? 2 : 1);
	वापस 0;
पूर्ण

पूर्णांक skcipher_walk_करोne(काष्ठा skcipher_walk *walk, पूर्णांक err)
अणु
	अचिन्हित पूर्णांक n = walk->nbytes;
	अचिन्हित पूर्णांक nbytes = 0;

	अगर (!n)
		जाओ finish;

	अगर (likely(err >= 0)) अणु
		n -= err;
		nbytes = walk->total - n;
	पूर्ण

	अगर (likely(!(walk->flags & (SKCIPHER_WALK_PHYS |
				    SKCIPHER_WALK_SLOW |
				    SKCIPHER_WALK_COPY |
				    SKCIPHER_WALK_DIFF)))) अणु
unmap_src:
		skcipher_unmap_src(walk);
	पूर्ण अन्यथा अगर (walk->flags & SKCIPHER_WALK_DIFF) अणु
		skcipher_unmap_dst(walk);
		जाओ unmap_src;
	पूर्ण अन्यथा अगर (walk->flags & SKCIPHER_WALK_COPY) अणु
		skcipher_map_dst(walk);
		स_नकल(walk->dst.virt.addr, walk->page, n);
		skcipher_unmap_dst(walk);
	पूर्ण अन्यथा अगर (unlikely(walk->flags & SKCIPHER_WALK_SLOW)) अणु
		अगर (err > 0) अणु
			/*
			 * Didn't process all bytes.  Either the algorithm is
			 * broken, or this was the last step and it turned out
			 * the message wasn't evenly भागisible पूर्णांकo blocks but
			 * the algorithm requires it.
			 */
			err = -EINVAL;
			nbytes = 0;
		पूर्ण अन्यथा
			n = skcipher_करोne_slow(walk, n);
	पूर्ण

	अगर (err > 0)
		err = 0;

	walk->total = nbytes;
	walk->nbytes = 0;

	scatterwalk_advance(&walk->in, n);
	scatterwalk_advance(&walk->out, n);
	scatterwalk_करोne(&walk->in, 0, nbytes);
	scatterwalk_करोne(&walk->out, 1, nbytes);

	अगर (nbytes) अणु
		crypto_yield(walk->flags & SKCIPHER_WALK_SLEEP ?
			     CRYPTO_TFM_REQ_MAY_SLEEP : 0);
		वापस skcipher_walk_next(walk);
	पूर्ण

finish:
	/* Short-circuit क्रम the common/fast path. */
	अगर (!((अचिन्हित दीर्घ)walk->buffer | (अचिन्हित दीर्घ)walk->page))
		जाओ out;

	अगर (walk->flags & SKCIPHER_WALK_PHYS)
		जाओ out;

	अगर (walk->iv != walk->oiv)
		स_नकल(walk->oiv, walk->iv, walk->ivsize);
	अगर (walk->buffer != walk->page)
		kमुक्त(walk->buffer);
	अगर (walk->page)
		मुक्त_page((अचिन्हित दीर्घ)walk->page);

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(skcipher_walk_करोne);

व्योम skcipher_walk_complete(काष्ठा skcipher_walk *walk, पूर्णांक err)
अणु
	काष्ठा skcipher_walk_buffer *p, *पंचांगp;

	list_क्रम_each_entry_safe(p, पंचांगp, &walk->buffers, entry) अणु
		u8 *data;

		अगर (err)
			जाओ करोne;

		data = p->data;
		अगर (!data) अणु
			data = PTR_ALIGN(&p->buffer[0], walk->alignmask + 1);
			data = skcipher_get_spot(data, walk->stride);
		पूर्ण

		scatterwalk_copychunks(data, &p->dst, p->len, 1);

		अगर (offset_in_page(p->data) + p->len + walk->stride >
		    PAGE_SIZE)
			मुक्त_page((अचिन्हित दीर्घ)p->data);

करोne:
		list_del(&p->entry);
		kमुक्त(p);
	पूर्ण

	अगर (!err && walk->iv != walk->oiv)
		स_नकल(walk->oiv, walk->iv, walk->ivsize);
	अगर (walk->buffer != walk->page)
		kमुक्त(walk->buffer);
	अगर (walk->page)
		मुक्त_page((अचिन्हित दीर्घ)walk->page);
पूर्ण
EXPORT_SYMBOL_GPL(skcipher_walk_complete);

अटल व्योम skcipher_queue_ग_लिखो(काष्ठा skcipher_walk *walk,
				 काष्ठा skcipher_walk_buffer *p)
अणु
	p->dst = walk->out;
	list_add_tail(&p->entry, &walk->buffers);
पूर्ण

अटल पूर्णांक skcipher_next_slow(काष्ठा skcipher_walk *walk, अचिन्हित पूर्णांक bsize)
अणु
	bool phys = walk->flags & SKCIPHER_WALK_PHYS;
	अचिन्हित alignmask = walk->alignmask;
	काष्ठा skcipher_walk_buffer *p;
	अचिन्हित a;
	अचिन्हित n;
	u8 *buffer;
	व्योम *v;

	अगर (!phys) अणु
		अगर (!walk->buffer)
			walk->buffer = walk->page;
		buffer = walk->buffer;
		अगर (buffer)
			जाओ ok;
	पूर्ण

	/* Start with the minimum alignment of kदो_स्मृति. */
	a = crypto_tfm_ctx_alignment() - 1;
	n = bsize;

	अगर (phys) अणु
		/* Calculate the minimum alignment of p->buffer. */
		a &= (माप(*p) ^ (माप(*p) - 1)) >> 1;
		n += माप(*p);
	पूर्ण

	/* Minimum size to align p->buffer by alignmask. */
	n += alignmask & ~a;

	/* Minimum size to ensure p->buffer करोes not straddle a page. */
	n += (bsize - 1) & ~(alignmask | a);

	v = kzalloc(n, skcipher_walk_gfp(walk));
	अगर (!v)
		वापस skcipher_walk_करोne(walk, -ENOMEM);

	अगर (phys) अणु
		p = v;
		p->len = bsize;
		skcipher_queue_ग_लिखो(walk, p);
		buffer = p->buffer;
	पूर्ण अन्यथा अणु
		walk->buffer = v;
		buffer = v;
	पूर्ण

ok:
	walk->dst.virt.addr = PTR_ALIGN(buffer, alignmask + 1);
	walk->dst.virt.addr = skcipher_get_spot(walk->dst.virt.addr, bsize);
	walk->src.virt.addr = walk->dst.virt.addr;

	scatterwalk_copychunks(walk->src.virt.addr, &walk->in, bsize, 0);

	walk->nbytes = bsize;
	walk->flags |= SKCIPHER_WALK_SLOW;

	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_next_copy(काष्ठा skcipher_walk *walk)
अणु
	काष्ठा skcipher_walk_buffer *p;
	u8 *पंचांगp = walk->page;

	skcipher_map_src(walk);
	स_नकल(पंचांगp, walk->src.virt.addr, walk->nbytes);
	skcipher_unmap_src(walk);

	walk->src.virt.addr = पंचांगp;
	walk->dst.virt.addr = पंचांगp;

	अगर (!(walk->flags & SKCIPHER_WALK_PHYS))
		वापस 0;

	p = kदो_स्मृति(माप(*p), skcipher_walk_gfp(walk));
	अगर (!p)
		वापस -ENOMEM;

	p->data = walk->page;
	p->len = walk->nbytes;
	skcipher_queue_ग_लिखो(walk, p);

	अगर (offset_in_page(walk->page) + walk->nbytes + walk->stride >
	    PAGE_SIZE)
		walk->page = शून्य;
	अन्यथा
		walk->page += walk->nbytes;

	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_next_fast(काष्ठा skcipher_walk *walk)
अणु
	अचिन्हित दीर्घ dअगरf;

	walk->src.phys.page = scatterwalk_page(&walk->in);
	walk->src.phys.offset = offset_in_page(walk->in.offset);
	walk->dst.phys.page = scatterwalk_page(&walk->out);
	walk->dst.phys.offset = offset_in_page(walk->out.offset);

	अगर (walk->flags & SKCIPHER_WALK_PHYS)
		वापस 0;

	dअगरf = walk->src.phys.offset - walk->dst.phys.offset;
	dअगरf |= walk->src.virt.page - walk->dst.virt.page;

	skcipher_map_src(walk);
	walk->dst.virt.addr = walk->src.virt.addr;

	अगर (dअगरf) अणु
		walk->flags |= SKCIPHER_WALK_DIFF;
		skcipher_map_dst(walk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_walk_next(काष्ठा skcipher_walk *walk)
अणु
	अचिन्हित पूर्णांक bsize;
	अचिन्हित पूर्णांक n;
	पूर्णांक err;

	walk->flags &= ~(SKCIPHER_WALK_SLOW | SKCIPHER_WALK_COPY |
			 SKCIPHER_WALK_DIFF);

	n = walk->total;
	bsize = min(walk->stride, max(n, walk->blocksize));
	n = scatterwalk_clamp(&walk->in, n);
	n = scatterwalk_clamp(&walk->out, n);

	अगर (unlikely(n < bsize)) अणु
		अगर (unlikely(walk->total < walk->blocksize))
			वापस skcipher_walk_करोne(walk, -EINVAL);

slow_path:
		err = skcipher_next_slow(walk, bsize);
		जाओ set_phys_lowmem;
	पूर्ण

	अगर (unlikely((walk->in.offset | walk->out.offset) & walk->alignmask)) अणु
		अगर (!walk->page) अणु
			gfp_t gfp = skcipher_walk_gfp(walk);

			walk->page = (व्योम *)__get_मुक्त_page(gfp);
			अगर (!walk->page)
				जाओ slow_path;
		पूर्ण

		walk->nbytes = min_t(अचिन्हित, n,
				     PAGE_SIZE - offset_in_page(walk->page));
		walk->flags |= SKCIPHER_WALK_COPY;
		err = skcipher_next_copy(walk);
		जाओ set_phys_lowmem;
	पूर्ण

	walk->nbytes = n;

	वापस skcipher_next_fast(walk);

set_phys_lowmem:
	अगर (!err && (walk->flags & SKCIPHER_WALK_PHYS)) अणु
		walk->src.phys.page = virt_to_page(walk->src.virt.addr);
		walk->dst.phys.page = virt_to_page(walk->dst.virt.addr);
		walk->src.phys.offset &= PAGE_SIZE - 1;
		walk->dst.phys.offset &= PAGE_SIZE - 1;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक skcipher_copy_iv(काष्ठा skcipher_walk *walk)
अणु
	अचिन्हित a = crypto_tfm_ctx_alignment() - 1;
	अचिन्हित alignmask = walk->alignmask;
	अचिन्हित ivsize = walk->ivsize;
	अचिन्हित bs = walk->stride;
	अचिन्हित aligned_bs;
	अचिन्हित size;
	u8 *iv;

	aligned_bs = ALIGN(bs, alignmask + 1);

	/* Minimum size to align buffer by alignmask. */
	size = alignmask & ~a;

	अगर (walk->flags & SKCIPHER_WALK_PHYS)
		size += ivsize;
	अन्यथा अणु
		size += aligned_bs + ivsize;

		/* Minimum size to ensure buffer करोes not straddle a page. */
		size += (bs - 1) & ~(alignmask | a);
	पूर्ण

	walk->buffer = kदो_स्मृति(size, skcipher_walk_gfp(walk));
	अगर (!walk->buffer)
		वापस -ENOMEM;

	iv = PTR_ALIGN(walk->buffer, alignmask + 1);
	iv = skcipher_get_spot(iv, bs) + aligned_bs;

	walk->iv = स_नकल(iv, walk->iv, walk->ivsize);
	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_walk_first(काष्ठा skcipher_walk *walk)
अणु
	अगर (WARN_ON_ONCE(in_irq()))
		वापस -EDEADLK;

	walk->buffer = शून्य;
	अगर (unlikely(((अचिन्हित दीर्घ)walk->iv & walk->alignmask))) अणु
		पूर्णांक err = skcipher_copy_iv(walk);
		अगर (err)
			वापस err;
	पूर्ण

	walk->page = शून्य;

	वापस skcipher_walk_next(walk);
पूर्ण

अटल पूर्णांक skcipher_walk_skcipher(काष्ठा skcipher_walk *walk,
				  काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);

	walk->total = req->cryptlen;
	walk->nbytes = 0;
	walk->iv = req->iv;
	walk->oiv = req->iv;

	अगर (unlikely(!walk->total))
		वापस 0;

	scatterwalk_start(&walk->in, req->src);
	scatterwalk_start(&walk->out, req->dst);

	walk->flags &= ~SKCIPHER_WALK_SLEEP;
	walk->flags |= req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ?
		       SKCIPHER_WALK_SLEEP : 0;

	walk->blocksize = crypto_skcipher_blocksize(tfm);
	walk->stride = crypto_skcipher_walksize(tfm);
	walk->ivsize = crypto_skcipher_ivsize(tfm);
	walk->alignmask = crypto_skcipher_alignmask(tfm);

	वापस skcipher_walk_first(walk);
पूर्ण

पूर्णांक skcipher_walk_virt(काष्ठा skcipher_walk *walk,
		       काष्ठा skcipher_request *req, bool atomic)
अणु
	पूर्णांक err;

	might_sleep_अगर(req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);

	walk->flags &= ~SKCIPHER_WALK_PHYS;

	err = skcipher_walk_skcipher(walk, req);

	walk->flags &= atomic ? ~SKCIPHER_WALK_SLEEP : ~0;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(skcipher_walk_virt);

पूर्णांक skcipher_walk_async(काष्ठा skcipher_walk *walk,
			काष्ठा skcipher_request *req)
अणु
	walk->flags |= SKCIPHER_WALK_PHYS;

	INIT_LIST_HEAD(&walk->buffers);

	वापस skcipher_walk_skcipher(walk, req);
पूर्ण
EXPORT_SYMBOL_GPL(skcipher_walk_async);

अटल पूर्णांक skcipher_walk_aead_common(काष्ठा skcipher_walk *walk,
				     काष्ठा aead_request *req, bool atomic)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	पूर्णांक err;

	walk->nbytes = 0;
	walk->iv = req->iv;
	walk->oiv = req->iv;

	अगर (unlikely(!walk->total))
		वापस 0;

	walk->flags &= ~SKCIPHER_WALK_PHYS;

	scatterwalk_start(&walk->in, req->src);
	scatterwalk_start(&walk->out, req->dst);

	scatterwalk_copychunks(शून्य, &walk->in, req->assoclen, 2);
	scatterwalk_copychunks(शून्य, &walk->out, req->assoclen, 2);

	scatterwalk_करोne(&walk->in, 0, walk->total);
	scatterwalk_करोne(&walk->out, 0, walk->total);

	अगर (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP)
		walk->flags |= SKCIPHER_WALK_SLEEP;
	अन्यथा
		walk->flags &= ~SKCIPHER_WALK_SLEEP;

	walk->blocksize = crypto_aead_blocksize(tfm);
	walk->stride = crypto_aead_chunksize(tfm);
	walk->ivsize = crypto_aead_ivsize(tfm);
	walk->alignmask = crypto_aead_alignmask(tfm);

	err = skcipher_walk_first(walk);

	अगर (atomic)
		walk->flags &= ~SKCIPHER_WALK_SLEEP;

	वापस err;
पूर्ण

पूर्णांक skcipher_walk_aead_encrypt(काष्ठा skcipher_walk *walk,
			       काष्ठा aead_request *req, bool atomic)
अणु
	walk->total = req->cryptlen;

	वापस skcipher_walk_aead_common(walk, req, atomic);
पूर्ण
EXPORT_SYMBOL_GPL(skcipher_walk_aead_encrypt);

पूर्णांक skcipher_walk_aead_decrypt(काष्ठा skcipher_walk *walk,
			       काष्ठा aead_request *req, bool atomic)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);

	walk->total = req->cryptlen - crypto_aead_authsize(tfm);

	वापस skcipher_walk_aead_common(walk, req, atomic);
पूर्ण
EXPORT_SYMBOL_GPL(skcipher_walk_aead_decrypt);

अटल व्योम skcipher_set_needkey(काष्ठा crypto_skcipher *tfm)
अणु
	अगर (crypto_skcipher_max_keysize(tfm) != 0)
		crypto_skcipher_set_flags(tfm, CRYPTO_TFM_NEED_KEY);
पूर्ण

अटल पूर्णांक skcipher_setkey_unaligned(काष्ठा crypto_skcipher *tfm,
				     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित दीर्घ alignmask = crypto_skcipher_alignmask(tfm);
	काष्ठा skcipher_alg *cipher = crypto_skcipher_alg(tfm);
	u8 *buffer, *alignbuffer;
	अचिन्हित दीर्घ असलize;
	पूर्णांक ret;

	असलize = keylen + alignmask;
	buffer = kदो_स्मृति(असलize, GFP_ATOMIC);
	अगर (!buffer)
		वापस -ENOMEM;

	alignbuffer = (u8 *)ALIGN((अचिन्हित दीर्घ)buffer, alignmask + 1);
	स_नकल(alignbuffer, key, keylen);
	ret = cipher->setkey(tfm, alignbuffer, keylen);
	kमुक्त_sensitive(buffer);
	वापस ret;
पूर्ण

पूर्णांक crypto_skcipher_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा skcipher_alg *cipher = crypto_skcipher_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_skcipher_alignmask(tfm);
	पूर्णांक err;

	अगर (keylen < cipher->min_keysize || keylen > cipher->max_keysize)
		वापस -EINVAL;

	अगर ((अचिन्हित दीर्घ)key & alignmask)
		err = skcipher_setkey_unaligned(tfm, key, keylen);
	अन्यथा
		err = cipher->setkey(tfm, key, keylen);

	अगर (unlikely(err)) अणु
		skcipher_set_needkey(tfm);
		वापस err;
	पूर्ण

	crypto_skcipher_clear_flags(tfm, CRYPTO_TFM_NEED_KEY);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_skcipher_setkey);

पूर्णांक crypto_skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	पूर्णांक ret;

	crypto_stats_get(alg);
	अगर (crypto_skcipher_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		ret = -ENOKEY;
	अन्यथा
		ret = crypto_skcipher_alg(tfm)->encrypt(req);
	crypto_stats_skcipher_encrypt(cryptlen, ret, alg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_skcipher_encrypt);

पूर्णांक crypto_skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	पूर्णांक ret;

	crypto_stats_get(alg);
	अगर (crypto_skcipher_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		ret = -ENOKEY;
	अन्यथा
		ret = crypto_skcipher_alg(tfm)->decrypt(req);
	crypto_stats_skcipher_decrypt(cryptlen, ret, alg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_skcipher_decrypt);

अटल व्योम crypto_skcipher_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_skcipher *skcipher = __crypto_skcipher_cast(tfm);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(skcipher);

	alg->निकास(skcipher);
पूर्ण

अटल पूर्णांक crypto_skcipher_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_skcipher *skcipher = __crypto_skcipher_cast(tfm);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(skcipher);

	skcipher_set_needkey(skcipher);

	अगर (alg->निकास)
		skcipher->base.निकास = crypto_skcipher_निकास_tfm;

	अगर (alg->init)
		वापस alg->init(skcipher);

	वापस 0;
पूर्ण

अटल व्योम crypto_skcipher_मुक्त_instance(काष्ठा crypto_instance *inst)
अणु
	काष्ठा skcipher_instance *skcipher =
		container_of(inst, काष्ठा skcipher_instance, s.base);

	skcipher->मुक्त(skcipher);
पूर्ण

अटल व्योम crypto_skcipher_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
	__maybe_unused;
अटल व्योम crypto_skcipher_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
अणु
	काष्ठा skcipher_alg *skcipher = container_of(alg, काष्ठा skcipher_alg,
						     base);

	seq_म_लिखो(m, "type         : skcipher\n");
	seq_म_लिखो(m, "async        : %s\n",
		   alg->cra_flags & CRYPTO_ALG_ASYNC ?  "yes" : "no");
	seq_म_लिखो(m, "blocksize    : %u\n", alg->cra_blocksize);
	seq_म_लिखो(m, "min keysize  : %u\n", skcipher->min_keysize);
	seq_म_लिखो(m, "max keysize  : %u\n", skcipher->max_keysize);
	seq_म_लिखो(m, "ivsize       : %u\n", skcipher->ivsize);
	seq_म_लिखो(m, "chunksize    : %u\n", skcipher->chunksize);
	seq_म_लिखो(m, "walksize     : %u\n", skcipher->walksize);
पूर्ण

#अगर_घोषित CONFIG_NET
अटल पूर्णांक crypto_skcipher_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_blkcipher rblkcipher;
	काष्ठा skcipher_alg *skcipher = container_of(alg, काष्ठा skcipher_alg,
						     base);

	स_रखो(&rblkcipher, 0, माप(rblkcipher));

	strscpy(rblkcipher.type, "skcipher", माप(rblkcipher.type));
	strscpy(rblkcipher.geniv, "<none>", माप(rblkcipher.geniv));

	rblkcipher.blocksize = alg->cra_blocksize;
	rblkcipher.min_keysize = skcipher->min_keysize;
	rblkcipher.max_keysize = skcipher->max_keysize;
	rblkcipher.ivsize = skcipher->ivsize;

	वापस nla_put(skb, CRYPTOCFGA_REPORT_BLKCIPHER,
		       माप(rblkcipher), &rblkcipher);
पूर्ण
#अन्यथा
अटल पूर्णांक crypto_skcipher_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा crypto_type crypto_skcipher_type = अणु
	.extsize = crypto_alg_extsize,
	.init_tfm = crypto_skcipher_init_tfm,
	.मुक्त = crypto_skcipher_मुक्त_instance,
#अगर_घोषित CONFIG_PROC_FS
	.show = crypto_skcipher_show,
#पूर्ण_अगर
	.report = crypto_skcipher_report,
	.maskclear = ~CRYPTO_ALG_TYPE_MASK,
	.maskset = CRYPTO_ALG_TYPE_MASK,
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.tfmsize = दुरत्व(काष्ठा crypto_skcipher, base),
पूर्ण;

पूर्णांक crypto_grab_skcipher(काष्ठा crypto_skcipher_spawn *spawn,
			 काष्ठा crypto_instance *inst,
			 स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	spawn->base.frontend = &crypto_skcipher_type;
	वापस crypto_grab_spawn(&spawn->base, inst, name, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_grab_skcipher);

काष्ठा crypto_skcipher *crypto_alloc_skcipher(स्थिर अक्षर *alg_name,
					      u32 type, u32 mask)
अणु
	वापस crypto_alloc_tfm(alg_name, &crypto_skcipher_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_skcipher);

काष्ठा crypto_sync_skcipher *crypto_alloc_sync_skcipher(
				स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	काष्ठा crypto_skcipher *tfm;

	/* Only sync algorithms allowed. */
	mask |= CRYPTO_ALG_ASYNC;

	tfm = crypto_alloc_tfm(alg_name, &crypto_skcipher_type, type, mask);

	/*
	 * Make sure we करो not allocate something that might get used with
	 * an on-stack request: check the request size.
	 */
	अगर (!IS_ERR(tfm) && WARN_ON(crypto_skcipher_reqsize(tfm) >
				    MAX_SYNC_SKCIPHER_REQSIZE)) अणु
		crypto_मुक्त_skcipher(tfm);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस (काष्ठा crypto_sync_skcipher *)tfm;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_sync_skcipher);

पूर्णांक crypto_has_skcipher(स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	वापस crypto_type_has_alg(alg_name, &crypto_skcipher_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_has_skcipher);

अटल पूर्णांक skcipher_prepare_alg(काष्ठा skcipher_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	अगर (alg->ivsize > PAGE_SIZE / 8 || alg->chunksize > PAGE_SIZE / 8 ||
	    alg->walksize > PAGE_SIZE / 8)
		वापस -EINVAL;

	अगर (!alg->chunksize)
		alg->chunksize = base->cra_blocksize;
	अगर (!alg->walksize)
		alg->walksize = alg->chunksize;

	base->cra_type = &crypto_skcipher_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_SKCIPHER;

	वापस 0;
पूर्ण

पूर्णांक crypto_रेजिस्टर_skcipher(काष्ठा skcipher_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;
	पूर्णांक err;

	err = skcipher_prepare_alg(alg);
	अगर (err)
		वापस err;

	वापस crypto_रेजिस्टर_alg(base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_skcipher);

व्योम crypto_unरेजिस्टर_skcipher(काष्ठा skcipher_alg *alg)
अणु
	crypto_unरेजिस्टर_alg(&alg->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_skcipher);

पूर्णांक crypto_रेजिस्टर_skciphers(काष्ठा skcipher_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = crypto_रेजिस्टर_skcipher(&algs[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	क्रम (--i; i >= 0; --i)
		crypto_unरेजिस्टर_skcipher(&algs[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_skciphers);

व्योम crypto_unरेजिस्टर_skciphers(काष्ठा skcipher_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = count - 1; i >= 0; --i)
		crypto_unरेजिस्टर_skcipher(&algs[i]);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_skciphers);

पूर्णांक skcipher_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			   काष्ठा skcipher_instance *inst)
अणु
	पूर्णांक err;

	अगर (WARN_ON(!inst->मुक्त))
		वापस -EINVAL;

	err = skcipher_prepare_alg(&inst->alg);
	अगर (err)
		वापस err;

	वापस crypto_रेजिस्टर_instance(पंचांगpl, skcipher_crypto_instance(inst));
पूर्ण
EXPORT_SYMBOL_GPL(skcipher_रेजिस्टर_instance);

अटल पूर्णांक skcipher_setkey_simple(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				  अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_cipher *cipher = skcipher_cipher_simple(tfm);

	crypto_cipher_clear_flags(cipher, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(cipher, crypto_skcipher_get_flags(tfm) &
				CRYPTO_TFM_REQ_MASK);
	वापस crypto_cipher_setkey(cipher, key, keylen);
पूर्ण

अटल पूर्णांक skcipher_init_tfm_simple(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_instance *inst = skcipher_alg_instance(tfm);
	काष्ठा crypto_cipher_spawn *spawn = skcipher_instance_ctx(inst);
	काष्ठा skcipher_ctx_simple *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_cipher *cipher;

	cipher = crypto_spawn_cipher(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->cipher = cipher;
	वापस 0;
पूर्ण

अटल व्योम skcipher_निकास_tfm_simple(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_ctx_simple *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_cipher(ctx->cipher);
पूर्ण

अटल व्योम skcipher_मुक्त_instance_simple(काष्ठा skcipher_instance *inst)
अणु
	crypto_drop_cipher(skcipher_instance_ctx(inst));
	kमुक्त(inst);
पूर्ण

/**
 * skcipher_alloc_instance_simple - allocate instance of simple block cipher mode
 *
 * Allocate an skcipher_instance क्रम a simple block cipher mode of operation,
 * e.g. cbc or ecb.  The instance context will have just a single crypto_spawn,
 * that क्रम the underlying cipher.  The अणुmin,maxपूर्ण_keysize, ivsize, blocksize,
 * alignmask, and priority are set from the underlying cipher but can be
 * overridden अगर needed.  The tfm context शेषs to skcipher_ctx_simple, and
 * शेष ->setkey(), ->init(), and ->निकास() methods are installed.
 *
 * @पंचांगpl: the ढाँचा being instantiated
 * @tb: the ढाँचा parameters
 *
 * Return: a poपूर्णांकer to the new instance, or an ERR_PTR().  The caller still
 *	   needs to रेजिस्टर the instance.
 */
काष्ठा skcipher_instance *skcipher_alloc_instance_simple(
	काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	u32 mask;
	काष्ठा skcipher_instance *inst;
	काष्ठा crypto_cipher_spawn *spawn;
	काष्ठा crypto_alg *cipher_alg;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SKCIPHER, &mask);
	अगर (err)
		वापस ERR_PTR(err);

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस ERR_PTR(-ENOMEM);
	spawn = skcipher_instance_ctx(inst);

	err = crypto_grab_cipher(spawn, skcipher_crypto_instance(inst),
				 crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	cipher_alg = crypto_spawn_cipher_alg(spawn);

	err = crypto_inst_setname(skcipher_crypto_instance(inst), पंचांगpl->name,
				  cipher_alg);
	अगर (err)
		जाओ err_मुक्त_inst;

	inst->मुक्त = skcipher_मुक्त_instance_simple;

	/* Default algorithm properties, can be overridden */
	inst->alg.base.cra_blocksize = cipher_alg->cra_blocksize;
	inst->alg.base.cra_alignmask = cipher_alg->cra_alignmask;
	inst->alg.base.cra_priority = cipher_alg->cra_priority;
	inst->alg.min_keysize = cipher_alg->cra_cipher.cia_min_keysize;
	inst->alg.max_keysize = cipher_alg->cra_cipher.cia_max_keysize;
	inst->alg.ivsize = cipher_alg->cra_blocksize;

	/* Use skcipher_ctx_simple by शेष, can be overridden */
	inst->alg.base.cra_ctxsize = माप(काष्ठा skcipher_ctx_simple);
	inst->alg.setkey = skcipher_setkey_simple;
	inst->alg.init = skcipher_init_tfm_simple;
	inst->alg.निकास = skcipher_निकास_tfm_simple;

	वापस inst;

err_मुक्त_inst:
	skcipher_मुक्त_instance_simple(inst);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(skcipher_alloc_instance_simple);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Symmetric key cipher type");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
