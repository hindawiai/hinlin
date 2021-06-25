<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register cache access API - flat caching support
//
// Copyright 2012 Wolfson Microelectronics plc
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश "internal.h"

अटल अंतरभूत अचिन्हित पूर्णांक regcache_flat_get_index(स्थिर काष्ठा regmap *map,
						   अचिन्हित पूर्णांक reg)
अणु
	वापस regcache_get_index_by_order(map, reg);
पूर्ण

अटल पूर्णांक regcache_flat_init(काष्ठा regmap *map)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक *cache;

	अगर (!map || map->reg_stride_order < 0 || !map->max_रेजिस्टर)
		वापस -EINVAL;

	map->cache = kसुस्मृति(regcache_flat_get_index(map, map->max_रेजिस्टर)
			     + 1, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!map->cache)
		वापस -ENOMEM;

	cache = map->cache;

	क्रम (i = 0; i < map->num_reg_शेषs; i++) अणु
		अचिन्हित पूर्णांक reg = map->reg_शेषs[i].reg;
		अचिन्हित पूर्णांक index = regcache_flat_get_index(map, reg);

		cache[index] = map->reg_शेषs[i].def;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक regcache_flat_निकास(काष्ठा regmap *map)
अणु
	kमुक्त(map->cache);
	map->cache = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक regcache_flat_पढ़ो(काष्ठा regmap *map,
			      अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value)
अणु
	अचिन्हित पूर्णांक *cache = map->cache;
	अचिन्हित पूर्णांक index = regcache_flat_get_index(map, reg);

	*value = cache[index];

	वापस 0;
पूर्ण

अटल पूर्णांक regcache_flat_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक *cache = map->cache;
	अचिन्हित पूर्णांक index = regcache_flat_get_index(map, reg);

	cache[index] = value;

	वापस 0;
पूर्ण

काष्ठा regcache_ops regcache_flat_ops = अणु
	.type = REGCACHE_FLAT,
	.name = "flat",
	.init = regcache_flat_init,
	.निकास = regcache_flat_निकास,
	.पढ़ो = regcache_flat_पढ़ो,
	.ग_लिखो = regcache_flat_ग_लिखो,
पूर्ण;
