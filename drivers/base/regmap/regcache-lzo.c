<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register cache access API - LZO caching support
//
// Copyright 2011 Wolfson Microelectronics plc
//
// Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>

#समावेश <linux/device.h>
#समावेश <linux/lzo.h>
#समावेश <linux/slab.h>

#समावेश "internal.h"

अटल पूर्णांक regcache_lzo_निकास(काष्ठा regmap *map);

काष्ठा regcache_lzo_ctx अणु
	व्योम *wmem;
	व्योम *dst;
	स्थिर व्योम *src;
	माप_प्रकार src_len;
	माप_प्रकार dst_len;
	माप_प्रकार decompressed_size;
	अचिन्हित दीर्घ *sync_bmp;
	पूर्णांक sync_bmp_nbits;
पूर्ण;

#घोषणा LZO_BLOCK_NUM 8
अटल पूर्णांक regcache_lzo_block_count(काष्ठा regmap *map)
अणु
	वापस LZO_BLOCK_NUM;
पूर्ण

अटल पूर्णांक regcache_lzo_prepare(काष्ठा regcache_lzo_ctx *lzo_ctx)
अणु
	lzo_ctx->wmem = kदो_स्मृति(LZO1X_MEM_COMPRESS, GFP_KERNEL);
	अगर (!lzo_ctx->wmem)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक regcache_lzo_compress(काष्ठा regcache_lzo_ctx *lzo_ctx)
अणु
	माप_प्रकार compress_size;
	पूर्णांक ret;

	ret = lzo1x_1_compress(lzo_ctx->src, lzo_ctx->src_len,
			       lzo_ctx->dst, &compress_size, lzo_ctx->wmem);
	अगर (ret != LZO_E_OK || compress_size > lzo_ctx->dst_len)
		वापस -EINVAL;
	lzo_ctx->dst_len = compress_size;
	वापस 0;
पूर्ण

अटल पूर्णांक regcache_lzo_decompress(काष्ठा regcache_lzo_ctx *lzo_ctx)
अणु
	माप_प्रकार dst_len;
	पूर्णांक ret;

	dst_len = lzo_ctx->dst_len;
	ret = lzo1x_decompress_safe(lzo_ctx->src, lzo_ctx->src_len,
				    lzo_ctx->dst, &dst_len);
	अगर (ret != LZO_E_OK || dst_len != lzo_ctx->dst_len)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक regcache_lzo_compress_cache_block(काष्ठा regmap *map,
		काष्ठा regcache_lzo_ctx *lzo_ctx)
अणु
	पूर्णांक ret;

	lzo_ctx->dst_len = lzo1x_worst_compress(PAGE_SIZE);
	lzo_ctx->dst = kदो_स्मृति(lzo_ctx->dst_len, GFP_KERNEL);
	अगर (!lzo_ctx->dst) अणु
		lzo_ctx->dst_len = 0;
		वापस -ENOMEM;
	पूर्ण

	ret = regcache_lzo_compress(lzo_ctx);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक regcache_lzo_decompress_cache_block(काष्ठा regmap *map,
		काष्ठा regcache_lzo_ctx *lzo_ctx)
अणु
	पूर्णांक ret;

	lzo_ctx->dst_len = lzo_ctx->decompressed_size;
	lzo_ctx->dst = kदो_स्मृति(lzo_ctx->dst_len, GFP_KERNEL);
	अगर (!lzo_ctx->dst) अणु
		lzo_ctx->dst_len = 0;
		वापस -ENOMEM;
	पूर्ण

	ret = regcache_lzo_decompress(lzo_ctx);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regcache_lzo_get_blkindex(काष्ठा regmap *map,
					    अचिन्हित पूर्णांक reg)
अणु
	वापस ((reg / map->reg_stride) * map->cache_word_size) /
		DIV_ROUND_UP(map->cache_size_raw,
			     regcache_lzo_block_count(map));
पूर्ण

अटल अंतरभूत पूर्णांक regcache_lzo_get_blkpos(काष्ठा regmap *map,
					  अचिन्हित पूर्णांक reg)
अणु
	वापस (reg / map->reg_stride) %
		    (DIV_ROUND_UP(map->cache_size_raw,
				  regcache_lzo_block_count(map)) /
		     map->cache_word_size);
पूर्ण

अटल अंतरभूत पूर्णांक regcache_lzo_get_blksize(काष्ठा regmap *map)
अणु
	वापस DIV_ROUND_UP(map->cache_size_raw,
			    regcache_lzo_block_count(map));
पूर्ण

अटल पूर्णांक regcache_lzo_init(काष्ठा regmap *map)
अणु
	काष्ठा regcache_lzo_ctx **lzo_blocks;
	माप_प्रकार bmp_size;
	पूर्णांक ret, i, blksize, blkcount;
	स्थिर अक्षर *p, *end;
	अचिन्हित दीर्घ *sync_bmp;

	ret = 0;

	blkcount = regcache_lzo_block_count(map);
	map->cache = kसुस्मृति(blkcount, माप(*lzo_blocks),
			     GFP_KERNEL);
	अगर (!map->cache)
		वापस -ENOMEM;
	lzo_blocks = map->cache;

	/*
	 * allocate a biपंचांगap to be used when syncing the cache with
	 * the hardware.  Each समय a रेजिस्टर is modअगरied, the corresponding
	 * bit is set in the biपंचांगap, so we know that we have to sync
	 * that रेजिस्टर.
	 */
	bmp_size = map->num_reg_शेषs_raw;
	sync_bmp = biपंचांगap_zalloc(bmp_size, GFP_KERNEL);
	अगर (!sync_bmp) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* allocate the lzo blocks and initialize them */
	क्रम (i = 0; i < blkcount; i++) अणु
		lzo_blocks[i] = kzalloc(माप **lzo_blocks,
					GFP_KERNEL);
		अगर (!lzo_blocks[i]) अणु
			biपंचांगap_मुक्त(sync_bmp);
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		lzo_blocks[i]->sync_bmp = sync_bmp;
		lzo_blocks[i]->sync_bmp_nbits = bmp_size;
		/* alloc the working space क्रम the compressed block */
		ret = regcache_lzo_prepare(lzo_blocks[i]);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	blksize = regcache_lzo_get_blksize(map);
	p = map->reg_शेषs_raw;
	end = map->reg_शेषs_raw + map->cache_size_raw;
	/* compress the रेजिस्टर map and fill the lzo blocks */
	क्रम (i = 0; i < blkcount; i++, p += blksize) अणु
		lzo_blocks[i]->src = p;
		अगर (p + blksize > end)
			lzo_blocks[i]->src_len = end - p;
		अन्यथा
			lzo_blocks[i]->src_len = blksize;
		ret = regcache_lzo_compress_cache_block(map,
						       lzo_blocks[i]);
		अगर (ret < 0)
			जाओ err;
		lzo_blocks[i]->decompressed_size =
			lzo_blocks[i]->src_len;
	पूर्ण

	वापस 0;
err:
	regcache_lzo_निकास(map);
	वापस ret;
पूर्ण

अटल पूर्णांक regcache_lzo_निकास(काष्ठा regmap *map)
अणु
	काष्ठा regcache_lzo_ctx **lzo_blocks;
	पूर्णांक i, blkcount;

	lzo_blocks = map->cache;
	अगर (!lzo_blocks)
		वापस 0;

	blkcount = regcache_lzo_block_count(map);
	/*
	 * the poपूर्णांकer to the biपंचांगap used क्रम syncing the cache
	 * is shared amongst all lzo_blocks.  Ensure it is मुक्तd
	 * only once.
	 */
	अगर (lzo_blocks[0])
		biपंचांगap_मुक्त(lzo_blocks[0]->sync_bmp);
	क्रम (i = 0; i < blkcount; i++) अणु
		अगर (lzo_blocks[i]) अणु
			kमुक्त(lzo_blocks[i]->wmem);
			kमुक्त(lzo_blocks[i]->dst);
		पूर्ण
		/* each lzo_block is a poपूर्णांकer वापसed by kदो_स्मृति or शून्य */
		kमुक्त(lzo_blocks[i]);
	पूर्ण
	kमुक्त(lzo_blocks);
	map->cache = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक regcache_lzo_पढ़ो(काष्ठा regmap *map,
			     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value)
अणु
	काष्ठा regcache_lzo_ctx *lzo_block, **lzo_blocks;
	पूर्णांक ret, blkindex, blkpos;
	माप_प्रकार पंचांगp_dst_len;
	व्योम *पंचांगp_dst;

	/* index of the compressed lzo block */
	blkindex = regcache_lzo_get_blkindex(map, reg);
	/* रेजिस्टर index within the decompressed block */
	blkpos = regcache_lzo_get_blkpos(map, reg);
	lzo_blocks = map->cache;
	lzo_block = lzo_blocks[blkindex];

	/* save the poपूर्णांकer and length of the compressed block */
	पंचांगp_dst = lzo_block->dst;
	पंचांगp_dst_len = lzo_block->dst_len;

	/* prepare the source to be the compressed block */
	lzo_block->src = lzo_block->dst;
	lzo_block->src_len = lzo_block->dst_len;

	/* decompress the block */
	ret = regcache_lzo_decompress_cache_block(map, lzo_block);
	अगर (ret >= 0)
		/* fetch the value from the cache */
		*value = regcache_get_val(map, lzo_block->dst, blkpos);

	kमुक्त(lzo_block->dst);
	/* restore the poपूर्णांकer and length of the compressed block */
	lzo_block->dst = पंचांगp_dst;
	lzo_block->dst_len = पंचांगp_dst_len;

	वापस ret;
पूर्ण

अटल पूर्णांक regcache_lzo_ग_लिखो(काष्ठा regmap *map,
			      अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा regcache_lzo_ctx *lzo_block, **lzo_blocks;
	पूर्णांक ret, blkindex, blkpos;
	माप_प्रकार पंचांगp_dst_len;
	व्योम *पंचांगp_dst;

	/* index of the compressed lzo block */
	blkindex = regcache_lzo_get_blkindex(map, reg);
	/* रेजिस्टर index within the decompressed block */
	blkpos = regcache_lzo_get_blkpos(map, reg);
	lzo_blocks = map->cache;
	lzo_block = lzo_blocks[blkindex];

	/* save the poपूर्णांकer and length of the compressed block */
	पंचांगp_dst = lzo_block->dst;
	पंचांगp_dst_len = lzo_block->dst_len;

	/* prepare the source to be the compressed block */
	lzo_block->src = lzo_block->dst;
	lzo_block->src_len = lzo_block->dst_len;

	/* decompress the block */
	ret = regcache_lzo_decompress_cache_block(map, lzo_block);
	अगर (ret < 0) अणु
		kमुक्त(lzo_block->dst);
		जाओ out;
	पूर्ण

	/* ग_लिखो the new value to the cache */
	अगर (regcache_set_val(map, lzo_block->dst, blkpos, value)) अणु
		kमुक्त(lzo_block->dst);
		जाओ out;
	पूर्ण

	/* prepare the source to be the decompressed block */
	lzo_block->src = lzo_block->dst;
	lzo_block->src_len = lzo_block->dst_len;

	/* compress the block */
	ret = regcache_lzo_compress_cache_block(map, lzo_block);
	अगर (ret < 0) अणु
		kमुक्त(lzo_block->dst);
		kमुक्त(lzo_block->src);
		जाओ out;
	पूर्ण

	/* set the bit so we know we have to sync this रेजिस्टर */
	set_bit(reg / map->reg_stride, lzo_block->sync_bmp);
	kमुक्त(पंचांगp_dst);
	kमुक्त(lzo_block->src);
	वापस 0;
out:
	lzo_block->dst = पंचांगp_dst;
	lzo_block->dst_len = पंचांगp_dst_len;
	वापस ret;
पूर्ण

अटल पूर्णांक regcache_lzo_sync(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
			     अचिन्हित पूर्णांक max)
अणु
	काष्ठा regcache_lzo_ctx **lzo_blocks;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;
	पूर्णांक ret;

	lzo_blocks = map->cache;
	i = min;
	क्रम_each_set_bit_from(i, lzo_blocks[0]->sync_bmp,
			      lzo_blocks[0]->sync_bmp_nbits) अणु
		अगर (i > max)
			जारी;

		ret = regcache_पढ़ो(map, i, &val);
		अगर (ret)
			वापस ret;

		/* Is this the hardware शेष?  If so skip. */
		ret = regcache_lookup_reg(map, i);
		अगर (ret > 0 && val == map->reg_शेषs[ret].def)
			जारी;

		map->cache_bypass = true;
		ret = _regmap_ग_लिखो(map, i, val);
		map->cache_bypass = false;
		अगर (ret)
			वापस ret;
		dev_dbg(map->dev, "Synced register %#x, value %#x\n",
			i, val);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा regcache_ops regcache_lzo_ops = अणु
	.type = REGCACHE_COMPRESSED,
	.name = "lzo",
	.init = regcache_lzo_init,
	.निकास = regcache_lzo_निकास,
	.पढ़ो = regcache_lzo_पढ़ो,
	.ग_लिखो = regcache_lzo_ग_लिखो,
	.sync = regcache_lzo_sync
पूर्ण;
