<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 Sergey Senozhatsky.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpu.h>
#समावेश <linux/crypto.h>

#समावेश "zcomp.h"

अटल स्थिर अक्षर * स्थिर backends[] = अणु
#अगर IS_ENABLED(CONFIG_CRYPTO_LZO)
	"lzo",
	"lzo-rle",
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_CRYPTO_LZ4)
	"lz4",
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_CRYPTO_LZ4HC)
	"lz4hc",
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_CRYPTO_842)
	"842",
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_CRYPTO_ZSTD)
	"zstd",
#पूर्ण_अगर
पूर्ण;

अटल व्योम zcomp_strm_मुक्त(काष्ठा zcomp_strm *zstrm)
अणु
	अगर (!IS_ERR_OR_शून्य(zstrm->tfm))
		crypto_मुक्त_comp(zstrm->tfm);
	मुक्त_pages((अचिन्हित दीर्घ)zstrm->buffer, 1);
	zstrm->tfm = शून्य;
	zstrm->buffer = शून्य;
पूर्ण

/*
 * Initialize zcomp_strm काष्ठाure with ->tfm initialized by backend, and
 * ->buffer. Return a negative value on error.
 */
अटल पूर्णांक zcomp_strm_init(काष्ठा zcomp_strm *zstrm, काष्ठा zcomp *comp)
अणु
	zstrm->tfm = crypto_alloc_comp(comp->name, 0, 0);
	/*
	 * allocate 2 pages. 1 क्रम compressed data, plus 1 extra क्रम the
	 * हाल when compressed size is larger than the original one
	 */
	zstrm->buffer = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, 1);
	अगर (IS_ERR_OR_शून्य(zstrm->tfm) || !zstrm->buffer) अणु
		zcomp_strm_मुक्त(zstrm);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

bool zcomp_available_algorithm(स्थिर अक्षर *comp)
अणु
	पूर्णांक i;

	i = sysfs_match_string(backends, comp);
	अगर (i >= 0)
		वापस true;

	/*
	 * Crypto करोes not ignore a trailing new line symbol,
	 * so make sure you करोn't supply a string containing
	 * one.
	 * This also means that we permit zcomp initialisation
	 * with any compressing algorithm known to crypto api.
	 */
	वापस crypto_has_comp(comp, 0, 0) == 1;
पूर्ण

/* show available compressors */
sमाप_प्रकार zcomp_available_show(स्थिर अक्षर *comp, अक्षर *buf)
अणु
	bool known_algorithm = false;
	sमाप_प्रकार sz = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(backends); i++) अणु
		अगर (!म_भेद(comp, backends[i])) अणु
			known_algorithm = true;
			sz += scnम_लिखो(buf + sz, PAGE_SIZE - sz - 2,
					"[%s] ", backends[i]);
		पूर्ण अन्यथा अणु
			sz += scnम_लिखो(buf + sz, PAGE_SIZE - sz - 2,
					"%s ", backends[i]);
		पूर्ण
	पूर्ण

	/*
	 * Out-of-tree module known to crypto api or a missing
	 * entry in `backends'.
	 */
	अगर (!known_algorithm && crypto_has_comp(comp, 0, 0) == 1)
		sz += scnम_लिखो(buf + sz, PAGE_SIZE - sz - 2,
				"[%s] ", comp);

	sz += scnम_लिखो(buf + sz, PAGE_SIZE - sz, "\n");
	वापस sz;
पूर्ण

काष्ठा zcomp_strm *zcomp_stream_get(काष्ठा zcomp *comp)
अणु
	local_lock(&comp->stream->lock);
	वापस this_cpu_ptr(comp->stream);
पूर्ण

व्योम zcomp_stream_put(काष्ठा zcomp *comp)
अणु
	local_unlock(&comp->stream->lock);
पूर्ण

पूर्णांक zcomp_compress(काष्ठा zcomp_strm *zstrm,
		स्थिर व्योम *src, अचिन्हित पूर्णांक *dst_len)
अणु
	/*
	 * Our dst memory (zstrm->buffer) is always `2 * PAGE_SIZE' sized
	 * because someबार we can endup having a bigger compressed data
	 * due to various reasons: क्रम example compression algorithms tend
	 * to add some padding to the compressed buffer. Speaking of padding,
	 * comp algorithm `842' pads the compressed length to multiple of 8
	 * and वापसs -ENOSP when the dst memory is not big enough, which
	 * is not something that ZRAM wants to see. We can handle the
	 * `compressed_size > PAGE_SIZE' हाल easily in ZRAM, but when we
	 * receive -ERRNO from the compressing backend we can't help it
	 * anymore. To make `842' happy we need to tell the exact size of
	 * the dst buffer, zram_drv will take care of the fact that
	 * compressed buffer is too big.
	 */
	*dst_len = PAGE_SIZE * 2;

	वापस crypto_comp_compress(zstrm->tfm,
			src, PAGE_SIZE,
			zstrm->buffer, dst_len);
पूर्ण

पूर्णांक zcomp_decompress(काष्ठा zcomp_strm *zstrm,
		स्थिर व्योम *src, अचिन्हित पूर्णांक src_len, व्योम *dst)
अणु
	अचिन्हित पूर्णांक dst_len = PAGE_SIZE;

	वापस crypto_comp_decompress(zstrm->tfm,
			src, src_len,
			dst, &dst_len);
पूर्ण

पूर्णांक zcomp_cpu_up_prepare(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा zcomp *comp = hlist_entry(node, काष्ठा zcomp, node);
	काष्ठा zcomp_strm *zstrm;
	पूर्णांक ret;

	zstrm = per_cpu_ptr(comp->stream, cpu);
	local_lock_init(&zstrm->lock);

	ret = zcomp_strm_init(zstrm, comp);
	अगर (ret)
		pr_err("Can't allocate a compression stream\n");
	वापस ret;
पूर्ण

पूर्णांक zcomp_cpu_dead(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा zcomp *comp = hlist_entry(node, काष्ठा zcomp, node);
	काष्ठा zcomp_strm *zstrm;

	zstrm = per_cpu_ptr(comp->stream, cpu);
	zcomp_strm_मुक्त(zstrm);
	वापस 0;
पूर्ण

अटल पूर्णांक zcomp_init(काष्ठा zcomp *comp)
अणु
	पूर्णांक ret;

	comp->stream = alloc_percpu(काष्ठा zcomp_strm);
	अगर (!comp->stream)
		वापस -ENOMEM;

	ret = cpuhp_state_add_instance(CPUHP_ZCOMP_PREPARE, &comp->node);
	अगर (ret < 0)
		जाओ cleanup;
	वापस 0;

cleanup:
	मुक्त_percpu(comp->stream);
	वापस ret;
पूर्ण

व्योम zcomp_destroy(काष्ठा zcomp *comp)
अणु
	cpuhp_state_हटाओ_instance(CPUHP_ZCOMP_PREPARE, &comp->node);
	मुक्त_percpu(comp->stream);
	kमुक्त(comp);
पूर्ण

/*
 * search available compressors क्रम requested algorithm.
 * allocate new zcomp and initialize it. वापस compressing
 * backend poपूर्णांकer or ERR_PTR अगर things went bad. ERR_PTR(-EINVAL)
 * अगर requested algorithm is not supported, ERR_PTR(-ENOMEM) in
 * हाल of allocation error, or any other error potentially
 * वापसed by zcomp_init().
 */
काष्ठा zcomp *zcomp_create(स्थिर अक्षर *compress)
अणु
	काष्ठा zcomp *comp;
	पूर्णांक error;

	अगर (!zcomp_available_algorithm(compress))
		वापस ERR_PTR(-EINVAL);

	comp = kzalloc(माप(काष्ठा zcomp), GFP_KERNEL);
	अगर (!comp)
		वापस ERR_PTR(-ENOMEM);

	comp->name = compress;
	error = zcomp_init(comp);
	अगर (error) अणु
		kमुक्त(comp);
		वापस ERR_PTR(error);
	पूर्ण
	वापस comp;
पूर्ण
