<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register cache access API - rbtree caching support
//
// Copyright 2011 Wolfson Microelectronics plc
//
// Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश "internal.h"

अटल पूर्णांक regcache_rbtree_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक value);
अटल पूर्णांक regcache_rbtree_निकास(काष्ठा regmap *map);

काष्ठा regcache_rbtree_node अणु
	/* block of adjacent रेजिस्टरs */
	व्योम *block;
	/* Which रेजिस्टरs are present */
	दीर्घ *cache_present;
	/* base रेजिस्टर handled by this block */
	अचिन्हित पूर्णांक base_reg;
	/* number of रेजिस्टरs available in the block */
	अचिन्हित पूर्णांक blklen;
	/* the actual rbtree node holding this block */
	काष्ठा rb_node node;
पूर्ण;

काष्ठा regcache_rbtree_ctx अणु
	काष्ठा rb_root root;
	काष्ठा regcache_rbtree_node *cached_rbnode;
पूर्ण;

अटल अंतरभूत व्योम regcache_rbtree_get_base_top_reg(
	काष्ठा regmap *map,
	काष्ठा regcache_rbtree_node *rbnode,
	अचिन्हित पूर्णांक *base, अचिन्हित पूर्णांक *top)
अणु
	*base = rbnode->base_reg;
	*top = rbnode->base_reg + ((rbnode->blklen - 1) * map->reg_stride);
पूर्ण

अटल अचिन्हित पूर्णांक regcache_rbtree_get_रेजिस्टर(काष्ठा regmap *map,
	काष्ठा regcache_rbtree_node *rbnode, अचिन्हित पूर्णांक idx)
अणु
	वापस regcache_get_val(map, rbnode->block, idx);
पूर्ण

अटल व्योम regcache_rbtree_set_रेजिस्टर(काष्ठा regmap *map,
					 काष्ठा regcache_rbtree_node *rbnode,
					 अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक val)
अणु
	set_bit(idx, rbnode->cache_present);
	regcache_set_val(map, rbnode->block, idx, val);
पूर्ण

अटल काष्ठा regcache_rbtree_node *regcache_rbtree_lookup(काष्ठा regmap *map,
							   अचिन्हित पूर्णांक reg)
अणु
	काष्ठा regcache_rbtree_ctx *rbtree_ctx = map->cache;
	काष्ठा rb_node *node;
	काष्ठा regcache_rbtree_node *rbnode;
	अचिन्हित पूर्णांक base_reg, top_reg;

	rbnode = rbtree_ctx->cached_rbnode;
	अगर (rbnode) अणु
		regcache_rbtree_get_base_top_reg(map, rbnode, &base_reg,
						 &top_reg);
		अगर (reg >= base_reg && reg <= top_reg)
			वापस rbnode;
	पूर्ण

	node = rbtree_ctx->root.rb_node;
	जबतक (node) अणु
		rbnode = rb_entry(node, काष्ठा regcache_rbtree_node, node);
		regcache_rbtree_get_base_top_reg(map, rbnode, &base_reg,
						 &top_reg);
		अगर (reg >= base_reg && reg <= top_reg) अणु
			rbtree_ctx->cached_rbnode = rbnode;
			वापस rbnode;
		पूर्ण अन्यथा अगर (reg > top_reg) अणु
			node = node->rb_right;
		पूर्ण अन्यथा अगर (reg < base_reg) अणु
			node = node->rb_left;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक regcache_rbtree_insert(काष्ठा regmap *map, काष्ठा rb_root *root,
				  काष्ठा regcache_rbtree_node *rbnode)
अणु
	काष्ठा rb_node **new, *parent;
	काष्ठा regcache_rbtree_node *rbnode_पंचांगp;
	अचिन्हित पूर्णांक base_reg_पंचांगp, top_reg_पंचांगp;
	अचिन्हित पूर्णांक base_reg;

	parent = शून्य;
	new = &root->rb_node;
	जबतक (*new) अणु
		rbnode_पंचांगp = rb_entry(*new, काष्ठा regcache_rbtree_node, node);
		/* base and top रेजिस्टरs of the current rbnode */
		regcache_rbtree_get_base_top_reg(map, rbnode_पंचांगp, &base_reg_पंचांगp,
						 &top_reg_पंचांगp);
		/* base रेजिस्टर of the rbnode to be added */
		base_reg = rbnode->base_reg;
		parent = *new;
		/* अगर this रेजिस्टर has alपढ़ोy been inserted, just वापस */
		अगर (base_reg >= base_reg_पंचांगp &&
		    base_reg <= top_reg_पंचांगp)
			वापस 0;
		अन्यथा अगर (base_reg > top_reg_पंचांगp)
			new = &((*new)->rb_right);
		अन्यथा अगर (base_reg < base_reg_पंचांगp)
			new = &((*new)->rb_left);
	पूर्ण

	/* insert the node पूर्णांकo the rbtree */
	rb_link_node(&rbnode->node, parent, new);
	rb_insert_color(&rbnode->node, root);

	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक rbtree_show(काष्ठा seq_file *s, व्योम *ignored)
अणु
	काष्ठा regmap *map = s->निजी;
	काष्ठा regcache_rbtree_ctx *rbtree_ctx = map->cache;
	काष्ठा regcache_rbtree_node *n;
	काष्ठा rb_node *node;
	अचिन्हित पूर्णांक base, top;
	माप_प्रकार mem_size;
	पूर्णांक nodes = 0;
	पूर्णांक रेजिस्टरs = 0;
	पूर्णांक this_रेजिस्टरs, average;

	map->lock(map->lock_arg);

	mem_size = माप(*rbtree_ctx);

	क्रम (node = rb_first(&rbtree_ctx->root); node != शून्य;
	     node = rb_next(node)) अणु
		n = rb_entry(node, काष्ठा regcache_rbtree_node, node);
		mem_size += माप(*n);
		mem_size += (n->blklen * map->cache_word_size);
		mem_size += BITS_TO_LONGS(n->blklen) * माप(दीर्घ);

		regcache_rbtree_get_base_top_reg(map, n, &base, &top);
		this_रेजिस्टरs = ((top - base) / map->reg_stride) + 1;
		seq_म_लिखो(s, "%x-%x (%d)\n", base, top, this_रेजिस्टरs);

		nodes++;
		रेजिस्टरs += this_रेजिस्टरs;
	पूर्ण

	अगर (nodes)
		average = रेजिस्टरs / nodes;
	अन्यथा
		average = 0;

	seq_म_लिखो(s, "%d nodes, %d registers, average %d registers, used %zu bytes\n",
		   nodes, रेजिस्टरs, average, mem_size);

	map->unlock(map->lock_arg);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(rbtree);

अटल व्योम rbtree_debugfs_init(काष्ठा regmap *map)
अणु
	debugfs_create_file("rbtree", 0400, map->debugfs, map, &rbtree_fops);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक regcache_rbtree_init(काष्ठा regmap *map)
अणु
	काष्ठा regcache_rbtree_ctx *rbtree_ctx;
	पूर्णांक i;
	पूर्णांक ret;

	map->cache = kदो_स्मृति(माप *rbtree_ctx, GFP_KERNEL);
	अगर (!map->cache)
		वापस -ENOMEM;

	rbtree_ctx = map->cache;
	rbtree_ctx->root = RB_ROOT;
	rbtree_ctx->cached_rbnode = शून्य;

	क्रम (i = 0; i < map->num_reg_शेषs; i++) अणु
		ret = regcache_rbtree_ग_लिखो(map,
					    map->reg_शेषs[i].reg,
					    map->reg_शेषs[i].def);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	regcache_rbtree_निकास(map);
	वापस ret;
पूर्ण

अटल पूर्णांक regcache_rbtree_निकास(काष्ठा regmap *map)
अणु
	काष्ठा rb_node *next;
	काष्ठा regcache_rbtree_ctx *rbtree_ctx;
	काष्ठा regcache_rbtree_node *rbtree_node;

	/* अगर we've alपढ़ोy been called then just वापस */
	rbtree_ctx = map->cache;
	अगर (!rbtree_ctx)
		वापस 0;

	/* मुक्त up the rbtree */
	next = rb_first(&rbtree_ctx->root);
	जबतक (next) अणु
		rbtree_node = rb_entry(next, काष्ठा regcache_rbtree_node, node);
		next = rb_next(&rbtree_node->node);
		rb_erase(&rbtree_node->node, &rbtree_ctx->root);
		kमुक्त(rbtree_node->cache_present);
		kमुक्त(rbtree_node->block);
		kमुक्त(rbtree_node);
	पूर्ण

	/* release the resources */
	kमुक्त(map->cache);
	map->cache = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक regcache_rbtree_पढ़ो(काष्ठा regmap *map,
				अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value)
अणु
	काष्ठा regcache_rbtree_node *rbnode;
	अचिन्हित पूर्णांक reg_पंचांगp;

	rbnode = regcache_rbtree_lookup(map, reg);
	अगर (rbnode) अणु
		reg_पंचांगp = (reg - rbnode->base_reg) / map->reg_stride;
		अगर (!test_bit(reg_पंचांगp, rbnode->cache_present))
			वापस -ENOENT;
		*value = regcache_rbtree_get_रेजिस्टर(map, rbnode, reg_पंचांगp);
	पूर्ण अन्यथा अणु
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक regcache_rbtree_insert_to_block(काष्ठा regmap *map,
					   काष्ठा regcache_rbtree_node *rbnode,
					   अचिन्हित पूर्णांक base_reg,
					   अचिन्हित पूर्णांक top_reg,
					   अचिन्हित पूर्णांक reg,
					   अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक blklen;
	अचिन्हित पूर्णांक pos, offset;
	अचिन्हित दीर्घ *present;
	u8 *blk;

	blklen = (top_reg - base_reg) / map->reg_stride + 1;
	pos = (reg - base_reg) / map->reg_stride;
	offset = (rbnode->base_reg - base_reg) / map->reg_stride;

	blk = kपुनः_स्मृति(rbnode->block,
		       blklen * map->cache_word_size,
		       GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	अगर (BITS_TO_LONGS(blklen) > BITS_TO_LONGS(rbnode->blklen)) अणु
		present = kपुनः_स्मृति(rbnode->cache_present,
				   BITS_TO_LONGS(blklen) * माप(*present),
				   GFP_KERNEL);
		अगर (!present) अणु
			kमुक्त(blk);
			वापस -ENOMEM;
		पूर्ण

		स_रखो(present + BITS_TO_LONGS(rbnode->blklen), 0,
		       (BITS_TO_LONGS(blklen) - BITS_TO_LONGS(rbnode->blklen))
		       * माप(*present));
	पूर्ण अन्यथा अणु
		present = rbnode->cache_present;
	पूर्ण

	/* insert the रेजिस्टर value in the correct place in the rbnode block */
	अगर (pos == 0) अणु
		स_हटाओ(blk + offset * map->cache_word_size,
			blk, rbnode->blklen * map->cache_word_size);
		biपंचांगap_shअगरt_left(present, present, offset, blklen);
	पूर्ण

	/* update the rbnode block, its size and the base रेजिस्टर */
	rbnode->block = blk;
	rbnode->blklen = blklen;
	rbnode->base_reg = base_reg;
	rbnode->cache_present = present;

	regcache_rbtree_set_रेजिस्टर(map, rbnode, pos, value);
	वापस 0;
पूर्ण

अटल काष्ठा regcache_rbtree_node *
regcache_rbtree_node_alloc(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा regcache_rbtree_node *rbnode;
	स्थिर काष्ठा regmap_range *range;
	पूर्णांक i;

	rbnode = kzalloc(माप(*rbnode), GFP_KERNEL);
	अगर (!rbnode)
		वापस शून्य;

	/* If there is a पढ़ो table then use it to guess at an allocation */
	अगर (map->rd_table) अणु
		क्रम (i = 0; i < map->rd_table->n_yes_ranges; i++) अणु
			अगर (regmap_reg_in_range(reg,
						&map->rd_table->yes_ranges[i]))
				अवरोध;
		पूर्ण

		अगर (i != map->rd_table->n_yes_ranges) अणु
			range = &map->rd_table->yes_ranges[i];
			rbnode->blklen = (range->range_max - range->range_min) /
				map->reg_stride	+ 1;
			rbnode->base_reg = range->range_min;
		पूर्ण
	पूर्ण

	अगर (!rbnode->blklen) अणु
		rbnode->blklen = 1;
		rbnode->base_reg = reg;
	पूर्ण

	rbnode->block = kदो_स्मृति_array(rbnode->blklen, map->cache_word_size,
				      GFP_KERNEL);
	अगर (!rbnode->block)
		जाओ err_मुक्त;

	rbnode->cache_present = kसुस्मृति(BITS_TO_LONGS(rbnode->blklen),
					माप(*rbnode->cache_present),
					GFP_KERNEL);
	अगर (!rbnode->cache_present)
		जाओ err_मुक्त_block;

	वापस rbnode;

err_मुक्त_block:
	kमुक्त(rbnode->block);
err_मुक्त:
	kमुक्त(rbnode);
	वापस शून्य;
पूर्ण

अटल पूर्णांक regcache_rbtree_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक value)
अणु
	काष्ठा regcache_rbtree_ctx *rbtree_ctx;
	काष्ठा regcache_rbtree_node *rbnode, *rbnode_पंचांगp;
	काष्ठा rb_node *node;
	अचिन्हित पूर्णांक reg_पंचांगp;
	पूर्णांक ret;

	rbtree_ctx = map->cache;

	/* अगर we can't locate it in the cached rbnode we'll have
	 * to traverse the rbtree looking क्रम it.
	 */
	rbnode = regcache_rbtree_lookup(map, reg);
	अगर (rbnode) अणु
		reg_पंचांगp = (reg - rbnode->base_reg) / map->reg_stride;
		regcache_rbtree_set_रेजिस्टर(map, rbnode, reg_पंचांगp, value);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक base_reg, top_reg;
		अचिन्हित पूर्णांक new_base_reg, new_top_reg;
		अचिन्हित पूर्णांक min, max;
		अचिन्हित पूर्णांक max_dist;
		अचिन्हित पूर्णांक dist, best_dist = अच_पूर्णांक_उच्च;

		max_dist = map->reg_stride * माप(*rbnode_पंचांगp) /
			map->cache_word_size;
		अगर (reg < max_dist)
			min = 0;
		अन्यथा
			min = reg - max_dist;
		max = reg + max_dist;

		/* look क्रम an adjacent रेजिस्टर to the one we are about to add */
		node = rbtree_ctx->root.rb_node;
		जबतक (node) अणु
			rbnode_पंचांगp = rb_entry(node, काष्ठा regcache_rbtree_node,
					      node);

			regcache_rbtree_get_base_top_reg(map, rbnode_पंचांगp,
				&base_reg, &top_reg);

			अगर (base_reg <= max && top_reg >= min) अणु
				अगर (reg < base_reg)
					dist = base_reg - reg;
				अन्यथा अगर (reg > top_reg)
					dist = reg - top_reg;
				अन्यथा
					dist = 0;
				अगर (dist < best_dist) अणु
					rbnode = rbnode_पंचांगp;
					best_dist = dist;
					new_base_reg = min(reg, base_reg);
					new_top_reg = max(reg, top_reg);
				पूर्ण
			पूर्ण

			/*
			 * Keep looking, we want to choose the बंदst block,
			 * otherwise we might end up creating overlapping
			 * blocks, which अवरोधs the rbtree.
			 */
			अगर (reg < base_reg)
				node = node->rb_left;
			अन्यथा अगर (reg > top_reg)
				node = node->rb_right;
			अन्यथा
				अवरोध;
		पूर्ण

		अगर (rbnode) अणु
			ret = regcache_rbtree_insert_to_block(map, rbnode,
							      new_base_reg,
							      new_top_reg, reg,
							      value);
			अगर (ret)
				वापस ret;
			rbtree_ctx->cached_rbnode = rbnode;
			वापस 0;
		पूर्ण

		/* We did not manage to find a place to insert it in
		 * an existing block so create a new rbnode.
		 */
		rbnode = regcache_rbtree_node_alloc(map, reg);
		अगर (!rbnode)
			वापस -ENOMEM;
		regcache_rbtree_set_रेजिस्टर(map, rbnode,
					     reg - rbnode->base_reg, value);
		regcache_rbtree_insert(map, &rbtree_ctx->root, rbnode);
		rbtree_ctx->cached_rbnode = rbnode;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक regcache_rbtree_sync(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
				अचिन्हित पूर्णांक max)
अणु
	काष्ठा regcache_rbtree_ctx *rbtree_ctx;
	काष्ठा rb_node *node;
	काष्ठा regcache_rbtree_node *rbnode;
	अचिन्हित पूर्णांक base_reg, top_reg;
	अचिन्हित पूर्णांक start, end;
	पूर्णांक ret;

	rbtree_ctx = map->cache;
	क्रम (node = rb_first(&rbtree_ctx->root); node; node = rb_next(node)) अणु
		rbnode = rb_entry(node, काष्ठा regcache_rbtree_node, node);

		regcache_rbtree_get_base_top_reg(map, rbnode, &base_reg,
			&top_reg);
		अगर (base_reg > max)
			अवरोध;
		अगर (top_reg < min)
			जारी;

		अगर (min > base_reg)
			start = (min - base_reg) / map->reg_stride;
		अन्यथा
			start = 0;

		अगर (max < top_reg)
			end = (max - base_reg) / map->reg_stride + 1;
		अन्यथा
			end = rbnode->blklen;

		ret = regcache_sync_block(map, rbnode->block,
					  rbnode->cache_present,
					  rbnode->base_reg, start, end);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस regmap_async_complete(map);
पूर्ण

अटल पूर्णांक regcache_rbtree_drop(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
				अचिन्हित पूर्णांक max)
अणु
	काष्ठा regcache_rbtree_ctx *rbtree_ctx;
	काष्ठा regcache_rbtree_node *rbnode;
	काष्ठा rb_node *node;
	अचिन्हित पूर्णांक base_reg, top_reg;
	अचिन्हित पूर्णांक start, end;

	rbtree_ctx = map->cache;
	क्रम (node = rb_first(&rbtree_ctx->root); node; node = rb_next(node)) अणु
		rbnode = rb_entry(node, काष्ठा regcache_rbtree_node, node);

		regcache_rbtree_get_base_top_reg(map, rbnode, &base_reg,
			&top_reg);
		अगर (base_reg > max)
			अवरोध;
		अगर (top_reg < min)
			जारी;

		अगर (min > base_reg)
			start = (min - base_reg) / map->reg_stride;
		अन्यथा
			start = 0;

		अगर (max < top_reg)
			end = (max - base_reg) / map->reg_stride + 1;
		अन्यथा
			end = rbnode->blklen;

		biपंचांगap_clear(rbnode->cache_present, start, end - start);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा regcache_ops regcache_rbtree_ops = अणु
	.type = REGCACHE_RBTREE,
	.name = "rbtree",
	.init = regcache_rbtree_init,
	.निकास = regcache_rbtree_निकास,
#अगर_घोषित CONFIG_DEBUG_FS
	.debugfs_init = rbtree_debugfs_init,
#पूर्ण_अगर
	.पढ़ो = regcache_rbtree_पढ़ो,
	.ग_लिखो = regcache_rbtree_ग_लिखो,
	.sync = regcache_rbtree_sync,
	.drop = regcache_rbtree_drop,
पूर्ण;
