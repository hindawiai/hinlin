<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API क्रम the NX-842 hardware compression.
 *
 * Copyright (C) IBM Corporation, 2011-2015
 *
 * Designer of the Power data compression engine:
 *   Bulent Abali <abali@us.ibm.com>
 *
 * Original Authors: Robert Jennings <rcj@linux.vnet.ibm.com>
 *                   Seth Jennings <sjenning@linux.vnet.ibm.com>
 *
 * Reग_लिखो: Dan Streeपंचांगan <ddstreet@ieee.org>
 *
 * This is an पूर्णांकerface to the NX-842 compression hardware in PowerPC
 * processors.  Most of the complनिकासy of this drvier is due to the fact that
 * the NX-842 compression hardware requires the input and output data buffers
 * to be specअगरically aligned, to be a specअगरic multiple in length, and within
 * specअगरic minimum and maximum lengths.  Those restrictions, provided by the
 * nx-842 driver via nx842_स्थिरraपूर्णांकs, mean this driver must use bounce
 * buffers and headers to correct misaligned in or out buffers, and to split
 * input buffers that are too large.
 *
 * This driver will fall back to software decompression अगर the hardware
 * decompression fails, so this driver's decompression should never fail as
 * दीर्घ as the provided compressed buffer is valid.  Any compressed buffer
 * created by this driver will have a header (except ones where the input
 * perfectly matches the स्थिरraपूर्णांकs); so users of this driver cannot simply
 * pass a compressed buffer created by this driver over to the 842 software
 * decompression library.  Instead, users must use this driver to decompress;
 * अगर the hardware fails or is unavailable, the compressed buffer will be
 * parsed and the header हटाओd, and the raw 842 buffer(s) passed to the 842
 * software decompression library.
 *
 * This करोes not fall back to software compression, however, since the caller
 * of this function is specअगरically requesting hardware compression; अगर the
 * hardware compression fails, the caller can fall back to software
 * compression, and the raw 842 compressed buffer that the software compressor
 * creates can be passed to this driver क्रम hardware decompression; any
 * buffer without our specअगरic header magic is assumed to be a raw 842 buffer
 * and passed directly to the hardware.  Note that the software compression
 * library will produce a compressed buffer that is incompatible with the
 * hardware decompressor अगर the original input buffer length is not a multiple
 * of 8; अगर such a compressed buffer is passed to this driver क्रम
 * decompression, the hardware will reject it and this driver will then pass
 * it over to the software library क्रम decompression.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sw842.h>
#समावेश <linux/spinlock.h>

#समावेश "nx-842.h"

/* The first 5 bits of this magic are 0x1f, which is an invalid 842 5-bit
 * ढाँचा (see lib/842/842.h), so this magic number will never appear at
 * the start of a raw 842 compressed buffer.  That is important, as any buffer
 * passed to us without this magic is assumed to be a raw 842 compressed
 * buffer, and passed directly to the hardware to decompress.
 */
#घोषणा NX842_CRYPTO_MAGIC	(0xf842)
#घोषणा NX842_CRYPTO_HEADER_SIZE(g)				\
	(माप(काष्ठा nx842_crypto_header) +			\
	 माप(काष्ठा nx842_crypto_header_group) * (g))
#घोषणा NX842_CRYPTO_HEADER_MAX_SIZE				\
	NX842_CRYPTO_HEADER_SIZE(NX842_CRYPTO_GROUP_MAX)

/* bounce buffer size */
#घोषणा BOUNCE_BUFFER_ORDER	(2)
#घोषणा BOUNCE_BUFFER_SIZE					\
	((अचिन्हित पूर्णांक)(PAGE_SIZE << BOUNCE_BUFFER_ORDER))

/* try दीर्घer on comp because we can fallback to sw decomp अगर hw is busy */
#घोषणा COMP_BUSY_TIMEOUT	(250) /* ms */
#घोषणा DECOMP_BUSY_TIMEOUT	(50) /* ms */

काष्ठा nx842_crypto_param अणु
	u8 *in;
	अचिन्हित पूर्णांक ireमुख्य;
	u8 *out;
	अचिन्हित पूर्णांक oreमुख्य;
	अचिन्हित पूर्णांक ototal;
पूर्ण;

अटल पूर्णांक update_param(काष्ठा nx842_crypto_param *p,
			अचिन्हित पूर्णांक slen, अचिन्हित पूर्णांक dlen)
अणु
	अगर (p->ireमुख्य < slen)
		वापस -EOVERFLOW;
	अगर (p->oreमुख्य < dlen)
		वापस -ENOSPC;

	p->in += slen;
	p->ireमुख्य -= slen;
	p->out += dlen;
	p->oreमुख्य -= dlen;
	p->ototal += dlen;

	वापस 0;
पूर्ण

पूर्णांक nx842_crypto_init(काष्ठा crypto_tfm *tfm, काष्ठा nx842_driver *driver)
अणु
	काष्ठा nx842_crypto_ctx *ctx = crypto_tfm_ctx(tfm);

	spin_lock_init(&ctx->lock);
	ctx->driver = driver;
	ctx->wmem = kदो_स्मृति(driver->workmem_size, GFP_KERNEL);
	ctx->sbounce = (u8 *)__get_मुक्त_pages(GFP_KERNEL, BOUNCE_BUFFER_ORDER);
	ctx->dbounce = (u8 *)__get_मुक्त_pages(GFP_KERNEL, BOUNCE_BUFFER_ORDER);
	अगर (!ctx->wmem || !ctx->sbounce || !ctx->dbounce) अणु
		kमुक्त(ctx->wmem);
		मुक्त_page((अचिन्हित दीर्घ)ctx->sbounce);
		मुक्त_page((अचिन्हित दीर्घ)ctx->dbounce);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nx842_crypto_init);

व्योम nx842_crypto_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा nx842_crypto_ctx *ctx = crypto_tfm_ctx(tfm);

	kमुक्त(ctx->wmem);
	मुक्त_page((अचिन्हित दीर्घ)ctx->sbounce);
	मुक्त_page((अचिन्हित दीर्घ)ctx->dbounce);
पूर्ण
EXPORT_SYMBOL_GPL(nx842_crypto_निकास);

अटल व्योम check_स्थिरraपूर्णांकs(काष्ठा nx842_स्थिरraपूर्णांकs *c)
अणु
	/* limit maximum, to always have enough bounce buffer to decompress */
	अगर (c->maximum > BOUNCE_BUFFER_SIZE)
		c->maximum = BOUNCE_BUFFER_SIZE;
पूर्ण

अटल पूर्णांक nx842_crypto_add_header(काष्ठा nx842_crypto_header *hdr, u8 *buf)
अणु
	पूर्णांक s = NX842_CRYPTO_HEADER_SIZE(hdr->groups);

	/* compress should have added space क्रम header */
	अगर (s > be16_to_cpu(hdr->group[0].padding)) अणु
		pr_err("Internal error: no space for header\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(buf, hdr, s);

	prपूर्णांक_hex_dump_debug("header ", DUMP_PREFIX_OFFSET, 16, 1, buf, s, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक compress(काष्ठा nx842_crypto_ctx *ctx,
		    काष्ठा nx842_crypto_param *p,
		    काष्ठा nx842_crypto_header_group *g,
		    काष्ठा nx842_स्थिरraपूर्णांकs *c,
		    u16 *ignore,
		    अचिन्हित पूर्णांक hdrsize)
अणु
	अचिन्हित पूर्णांक slen = p->ireमुख्य, dlen = p->oreमुख्य, पंचांगplen;
	अचिन्हित पूर्णांक adj_slen = slen;
	u8 *src = p->in, *dst = p->out;
	पूर्णांक ret, dskip = 0;
	kसमय_प्रकार समयout;

	अगर (p->ireमुख्य == 0)
		वापस -EOVERFLOW;

	अगर (p->oreमुख्य == 0 || hdrsize + c->minimum > dlen)
		वापस -ENOSPC;

	अगर (slen % c->multiple)
		adj_slen = round_up(slen, c->multiple);
	अगर (slen < c->minimum)
		adj_slen = c->minimum;
	अगर (slen > c->maximum)
		adj_slen = slen = c->maximum;
	अगर (adj_slen > slen || (u64)src % c->alignment) अणु
		adj_slen = min(adj_slen, BOUNCE_BUFFER_SIZE);
		slen = min(slen, BOUNCE_BUFFER_SIZE);
		अगर (adj_slen > slen)
			स_रखो(ctx->sbounce + slen, 0, adj_slen - slen);
		स_नकल(ctx->sbounce, src, slen);
		src = ctx->sbounce;
		slen = adj_slen;
		pr_debug("using comp sbounce buffer, len %x\n", slen);
	पूर्ण

	dst += hdrsize;
	dlen -= hdrsize;

	अगर ((u64)dst % c->alignment) अणु
		dskip = (पूर्णांक)(PTR_ALIGN(dst, c->alignment) - dst);
		dst += dskip;
		dlen -= dskip;
	पूर्ण
	अगर (dlen % c->multiple)
		dlen = round_करोwn(dlen, c->multiple);
	अगर (dlen < c->minimum) अणु
nospc:
		dst = ctx->dbounce;
		dlen = min(p->oreमुख्य, BOUNCE_BUFFER_SIZE);
		dlen = round_करोwn(dlen, c->multiple);
		dskip = 0;
		pr_debug("using comp dbounce buffer, len %x\n", dlen);
	पूर्ण
	अगर (dlen > c->maximum)
		dlen = c->maximum;

	पंचांगplen = dlen;
	समयout = kसमय_add_ms(kसमय_get(), COMP_BUSY_TIMEOUT);
	करो अणु
		dlen = पंचांगplen; /* reset dlen, अगर we're retrying */
		ret = ctx->driver->compress(src, slen, dst, &dlen, ctx->wmem);
		/* possibly we should reduce the slen here, instead of
		 * retrying with the dbounce buffer?
		 */
		अगर (ret == -ENOSPC && dst != ctx->dbounce)
			जाओ nospc;
	पूर्ण जबतक (ret == -EBUSY && kसमय_beक्रमe(kसमय_get(), समयout));
	अगर (ret)
		वापस ret;

	dskip += hdrsize;

	अगर (dst == ctx->dbounce)
		स_नकल(p->out + dskip, dst, dlen);

	g->padding = cpu_to_be16(dskip);
	g->compressed_length = cpu_to_be32(dlen);
	g->uncompressed_length = cpu_to_be32(slen);

	अगर (p->ireमुख्य < slen) अणु
		*ignore = slen - p->ireमुख्य;
		slen = p->ireमुख्य;
	पूर्ण

	pr_debug("compress slen %x ignore %x dlen %x padding %x\n",
		 slen, *ignore, dlen, dskip);

	वापस update_param(p, slen, dskip + dlen);
पूर्ण

पूर्णांक nx842_crypto_compress(काष्ठा crypto_tfm *tfm,
			  स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			  u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा nx842_crypto_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा nx842_crypto_header *hdr = &ctx->header;
	काष्ठा nx842_crypto_param p;
	काष्ठा nx842_स्थिरraपूर्णांकs c = *ctx->driver->स्थिरraपूर्णांकs;
	अचिन्हित पूर्णांक groups, hdrsize, h;
	पूर्णांक ret, n;
	bool add_header;
	u16 ignore = 0;

	check_स्थिरraपूर्णांकs(&c);

	p.in = (u8 *)src;
	p.ireमुख्य = slen;
	p.out = dst;
	p.oreमुख्य = *dlen;
	p.ototal = 0;

	*dlen = 0;

	groups = min_t(अचिन्हित पूर्णांक, NX842_CRYPTO_GROUP_MAX,
		       DIV_ROUND_UP(p.ireमुख्य, c.maximum));
	hdrsize = NX842_CRYPTO_HEADER_SIZE(groups);

	spin_lock_bh(&ctx->lock);

	/* skip adding header अगर the buffers meet all स्थिरraपूर्णांकs */
	add_header = (p.ireमुख्य % c.multiple	||
		      p.ireमुख्य < c.minimum	||
		      p.ireमुख्य > c.maximum	||
		      (u64)p.in % c.alignment	||
		      p.oreमुख्य % c.multiple	||
		      p.oreमुख्य < c.minimum	||
		      p.oreमुख्य > c.maximum	||
		      (u64)p.out % c.alignment);

	hdr->magic = cpu_to_be16(NX842_CRYPTO_MAGIC);
	hdr->groups = 0;
	hdr->ignore = 0;

	जबतक (p.ireमुख्य > 0) अणु
		n = hdr->groups++;
		ret = -ENOSPC;
		अगर (hdr->groups > NX842_CRYPTO_GROUP_MAX)
			जाओ unlock;

		/* header goes beक्रमe first group */
		h = !n && add_header ? hdrsize : 0;

		अगर (ignore)
			pr_warn("internal error, ignore is set %x\n", ignore);

		ret = compress(ctx, &p, &hdr->group[n], &c, &ignore, h);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	अगर (!add_header && hdr->groups > 1) अणु
		pr_err("Internal error: No header but multiple groups\n");
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	/* ignore indicates the input stream needed to be padded */
	hdr->ignore = cpu_to_be16(ignore);
	अगर (ignore)
		pr_debug("marked %d bytes as ignore\n", ignore);

	अगर (add_header)
		ret = nx842_crypto_add_header(hdr, dst);
	अगर (ret)
		जाओ unlock;

	*dlen = p.ototal;

	pr_debug("compress total slen %x dlen %x\n", slen, *dlen);

unlock:
	spin_unlock_bh(&ctx->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nx842_crypto_compress);

अटल पूर्णांक decompress(काष्ठा nx842_crypto_ctx *ctx,
		      काष्ठा nx842_crypto_param *p,
		      काष्ठा nx842_crypto_header_group *g,
		      काष्ठा nx842_स्थिरraपूर्णांकs *c,
		      u16 ignore)
अणु
	अचिन्हित पूर्णांक slen = be32_to_cpu(g->compressed_length);
	अचिन्हित पूर्णांक required_len = be32_to_cpu(g->uncompressed_length);
	अचिन्हित पूर्णांक dlen = p->oreमुख्य, पंचांगplen;
	अचिन्हित पूर्णांक adj_slen = slen;
	u8 *src = p->in, *dst = p->out;
	u16 padding = be16_to_cpu(g->padding);
	पूर्णांक ret, spadding = 0;
	kसमय_प्रकार समयout;

	अगर (!slen || !required_len)
		वापस -EINVAL;

	अगर (p->ireमुख्य <= 0 || padding + slen > p->ireमुख्य)
		वापस -EOVERFLOW;

	अगर (p->oreमुख्य <= 0 || required_len - ignore > p->oreमुख्य)
		वापस -ENOSPC;

	src += padding;

	अगर (slen % c->multiple)
		adj_slen = round_up(slen, c->multiple);
	अगर (slen < c->minimum)
		adj_slen = c->minimum;
	अगर (slen > c->maximum)
		जाओ usesw;
	अगर (slen < adj_slen || (u64)src % c->alignment) अणु
		/* we can append padding bytes because the 842 क्रमmat defines
		 * an "end" ढाँचा (see lib/842/842_decompress.c) and will
		 * ignore any bytes following it.
		 */
		अगर (slen < adj_slen)
			स_रखो(ctx->sbounce + slen, 0, adj_slen - slen);
		स_नकल(ctx->sbounce, src, slen);
		src = ctx->sbounce;
		spadding = adj_slen - slen;
		slen = adj_slen;
		pr_debug("using decomp sbounce buffer, len %x\n", slen);
	पूर्ण

	अगर (dlen % c->multiple)
		dlen = round_करोwn(dlen, c->multiple);
	अगर (dlen < required_len || (u64)dst % c->alignment) अणु
		dst = ctx->dbounce;
		dlen = min(required_len, BOUNCE_BUFFER_SIZE);
		pr_debug("using decomp dbounce buffer, len %x\n", dlen);
	पूर्ण
	अगर (dlen < c->minimum)
		जाओ usesw;
	अगर (dlen > c->maximum)
		dlen = c->maximum;

	पंचांगplen = dlen;
	समयout = kसमय_add_ms(kसमय_get(), DECOMP_BUSY_TIMEOUT);
	करो अणु
		dlen = पंचांगplen; /* reset dlen, अगर we're retrying */
		ret = ctx->driver->decompress(src, slen, dst, &dlen, ctx->wmem);
	पूर्ण जबतक (ret == -EBUSY && kसमय_beक्रमe(kसमय_get(), समयout));
	अगर (ret) अणु
usesw:
		/* reset everything, sw करोesn't have स्थिरraपूर्णांकs */
		src = p->in + padding;
		slen = be32_to_cpu(g->compressed_length);
		spadding = 0;
		dst = p->out;
		dlen = p->oreमुख्य;
		अगर (dlen < required_len) अणु /* have ignore bytes */
			dst = ctx->dbounce;
			dlen = BOUNCE_BUFFER_SIZE;
		पूर्ण
		pr_info_ratelimited("using software 842 decompression\n");
		ret = sw842_decompress(src, slen, dst, &dlen);
	पूर्ण
	अगर (ret)
		वापस ret;

	slen -= spadding;

	dlen -= ignore;
	अगर (ignore)
		pr_debug("ignoring last %x bytes\n", ignore);

	अगर (dst == ctx->dbounce)
		स_नकल(p->out, dst, dlen);

	pr_debug("decompress slen %x padding %x dlen %x ignore %x\n",
		 slen, padding, dlen, ignore);

	वापस update_param(p, slen + padding, dlen);
पूर्ण

पूर्णांक nx842_crypto_decompress(काष्ठा crypto_tfm *tfm,
			    स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			    u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा nx842_crypto_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा nx842_crypto_header *hdr;
	काष्ठा nx842_crypto_param p;
	काष्ठा nx842_स्थिरraपूर्णांकs c = *ctx->driver->स्थिरraपूर्णांकs;
	पूर्णांक n, ret, hdr_len;
	u16 ignore = 0;

	check_स्थिरraपूर्णांकs(&c);

	p.in = (u8 *)src;
	p.ireमुख्य = slen;
	p.out = dst;
	p.oreमुख्य = *dlen;
	p.ototal = 0;

	*dlen = 0;

	hdr = (काष्ठा nx842_crypto_header *)src;

	spin_lock_bh(&ctx->lock);

	/* If it करोesn't start with our header magic number, assume it's a raw
	 * 842 compressed buffer and pass it directly to the hardware driver
	 */
	अगर (be16_to_cpu(hdr->magic) != NX842_CRYPTO_MAGIC) अणु
		काष्ठा nx842_crypto_header_group g = अणु
			.padding =		0,
			.compressed_length =	cpu_to_be32(p.ireमुख्य),
			.uncompressed_length =	cpu_to_be32(p.oreमुख्य),
		पूर्ण;

		ret = decompress(ctx, &p, &g, &c, 0);
		अगर (ret)
			जाओ unlock;

		जाओ success;
	पूर्ण

	अगर (!hdr->groups) अणु
		pr_err("header has no groups\n");
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण
	अगर (hdr->groups > NX842_CRYPTO_GROUP_MAX) अणु
		pr_err("header has too many groups %x, max %x\n",
		       hdr->groups, NX842_CRYPTO_GROUP_MAX);
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	hdr_len = NX842_CRYPTO_HEADER_SIZE(hdr->groups);
	अगर (hdr_len > slen) अणु
		ret = -EOVERFLOW;
		जाओ unlock;
	पूर्ण

	स_नकल(&ctx->header, src, hdr_len);
	hdr = &ctx->header;

	क्रम (n = 0; n < hdr->groups; n++) अणु
		/* ignore applies to last group */
		अगर (n + 1 == hdr->groups)
			ignore = be16_to_cpu(hdr->ignore);

		ret = decompress(ctx, &p, &hdr->group[n], &c, ignore);
		अगर (ret)
			जाओ unlock;
	पूर्ण

success:
	*dlen = p.ototal;

	pr_debug("decompress total slen %x dlen %x\n", slen, *dlen);

	ret = 0;

unlock:
	spin_unlock_bh(&ctx->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nx842_crypto_decompress);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IBM PowerPC Nest (NX) 842 Hardware Compression Driver");
MODULE_AUTHOR("Dan Streetman <ddstreet@ieee.org>");
