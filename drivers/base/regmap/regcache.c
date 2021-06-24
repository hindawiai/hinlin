<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register cache access API
//
// Copyright 2011 Wolfson Microelectronics plc
//
// Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>

#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>

#समावेश "trace.h"
#समावेश "internal.h"

अटल स्थिर काष्ठा regcache_ops *cache_types[] = अणु
	&regcache_rbtree_ops,
#अगर IS_ENABLED(CONFIG_REGCACHE_COMPRESSED)
	&regcache_lzo_ops,
#पूर्ण_अगर
	&regcache_flat_ops,
पूर्ण;

अटल पूर्णांक regcache_hw_init(काष्ठा regmap *map)
अणु
	पूर्णांक i, j;
	पूर्णांक ret;
	पूर्णांक count;
	अचिन्हित पूर्णांक reg, val;
	व्योम *पंचांगp_buf;

	अगर (!map->num_reg_शेषs_raw)
		वापस -EINVAL;

	/* calculate the size of reg_शेषs */
	क्रम (count = 0, i = 0; i < map->num_reg_शेषs_raw; i++)
		अगर (regmap_पढ़ोable(map, i * map->reg_stride) &&
		    !regmap_अस्थिर(map, i * map->reg_stride))
			count++;

	/* all रेजिस्टरs are unपढ़ोable or अस्थिर, so just bypass */
	अगर (!count) अणु
		map->cache_bypass = true;
		वापस 0;
	पूर्ण

	map->num_reg_शेषs = count;
	map->reg_शेषs = kदो_स्मृति_array(count, माप(काष्ठा reg_शेष),
					  GFP_KERNEL);
	अगर (!map->reg_शेषs)
		वापस -ENOMEM;

	अगर (!map->reg_शेषs_raw) अणु
		bool cache_bypass = map->cache_bypass;
		dev_warn(map->dev, "No cache defaults, reading back from HW\n");

		/* Bypass the cache access till data पढ़ो from HW */
		map->cache_bypass = true;
		पंचांगp_buf = kदो_स्मृति(map->cache_size_raw, GFP_KERNEL);
		अगर (!पंचांगp_buf) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त;
		पूर्ण
		ret = regmap_raw_पढ़ो(map, 0, पंचांगp_buf,
				      map->cache_size_raw);
		map->cache_bypass = cache_bypass;
		अगर (ret == 0) अणु
			map->reg_शेषs_raw = पंचांगp_buf;
			map->cache_मुक्त = true;
		पूर्ण अन्यथा अणु
			kमुक्त(पंचांगp_buf);
		पूर्ण
	पूर्ण

	/* fill the reg_शेषs */
	क्रम (i = 0, j = 0; i < map->num_reg_शेषs_raw; i++) अणु
		reg = i * map->reg_stride;

		अगर (!regmap_पढ़ोable(map, reg))
			जारी;

		अगर (regmap_अस्थिर(map, reg))
			जारी;

		अगर (map->reg_शेषs_raw) अणु
			val = regcache_get_val(map, map->reg_शेषs_raw, i);
		पूर्ण अन्यथा अणु
			bool cache_bypass = map->cache_bypass;

			map->cache_bypass = true;
			ret = regmap_पढ़ो(map, reg, &val);
			map->cache_bypass = cache_bypass;
			अगर (ret != 0) अणु
				dev_err(map->dev, "Failed to read %d: %d\n",
					reg, ret);
				जाओ err_मुक्त;
			पूर्ण
		पूर्ण

		map->reg_शेषs[j].reg = reg;
		map->reg_शेषs[j].def = val;
		j++;
	पूर्ण

	वापस 0;

err_मुक्त:
	kमुक्त(map->reg_शेषs);

	वापस ret;
पूर्ण

पूर्णांक regcache_init(काष्ठा regmap *map, स्थिर काष्ठा regmap_config *config)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	व्योम *पंचांगp_buf;

	अगर (map->cache_type == REGCACHE_NONE) अणु
		अगर (config->reg_शेषs || config->num_reg_शेषs_raw)
			dev_warn(map->dev,
				 "No cache used with register defaults set!\n");

		map->cache_bypass = true;
		वापस 0;
	पूर्ण

	अगर (config->reg_शेषs && !config->num_reg_शेषs) अणु
		dev_err(map->dev,
			 "Register defaults are set without the number!\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < config->num_reg_शेषs; i++)
		अगर (config->reg_शेषs[i].reg % map->reg_stride)
			वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(cache_types); i++)
		अगर (cache_types[i]->type == map->cache_type)
			अवरोध;

	अगर (i == ARRAY_SIZE(cache_types)) अणु
		dev_err(map->dev, "Could not match compress type: %d\n",
			map->cache_type);
		वापस -EINVAL;
	पूर्ण

	map->num_reg_शेषs = config->num_reg_शेषs;
	map->num_reg_शेषs_raw = config->num_reg_शेषs_raw;
	map->reg_शेषs_raw = config->reg_शेषs_raw;
	map->cache_word_size = DIV_ROUND_UP(config->val_bits, 8);
	map->cache_size_raw = map->cache_word_size * config->num_reg_शेषs_raw;

	map->cache = शून्य;
	map->cache_ops = cache_types[i];

	अगर (!map->cache_ops->पढ़ो ||
	    !map->cache_ops->ग_लिखो ||
	    !map->cache_ops->name)
		वापस -EINVAL;

	/* We still need to ensure that the reg_शेषs
	 * won't vanish from under us.  We'll need to make
	 * a copy of it.
	 */
	अगर (config->reg_शेषs) अणु
		पंचांगp_buf = kmemdup(config->reg_शेषs, map->num_reg_शेषs *
				  माप(काष्ठा reg_शेष), GFP_KERNEL);
		अगर (!पंचांगp_buf)
			वापस -ENOMEM;
		map->reg_शेषs = पंचांगp_buf;
	पूर्ण अन्यथा अगर (map->num_reg_शेषs_raw) अणु
		/* Some devices such as PMICs करोn't have cache शेषs,
		 * we cope with this by पढ़ोing back the HW रेजिस्टरs and
		 * crafting the cache शेषs by hand.
		 */
		ret = regcache_hw_init(map);
		अगर (ret < 0)
			वापस ret;
		अगर (map->cache_bypass)
			वापस 0;
	पूर्ण

	अगर (!map->max_रेजिस्टर)
		map->max_रेजिस्टर = map->num_reg_शेषs_raw;

	अगर (map->cache_ops->init) अणु
		dev_dbg(map->dev, "Initializing %s cache\n",
			map->cache_ops->name);
		ret = map->cache_ops->init(map);
		अगर (ret)
			जाओ err_मुक्त;
	पूर्ण
	वापस 0;

err_मुक्त:
	kमुक्त(map->reg_शेषs);
	अगर (map->cache_मुक्त)
		kमुक्त(map->reg_शेषs_raw);

	वापस ret;
पूर्ण

व्योम regcache_निकास(काष्ठा regmap *map)
अणु
	अगर (map->cache_type == REGCACHE_NONE)
		वापस;

	BUG_ON(!map->cache_ops);

	kमुक्त(map->reg_शेषs);
	अगर (map->cache_मुक्त)
		kमुक्त(map->reg_शेषs_raw);

	अगर (map->cache_ops->निकास) अणु
		dev_dbg(map->dev, "Destroying %s cache\n",
			map->cache_ops->name);
		map->cache_ops->निकास(map);
	पूर्ण
पूर्ण

/**
 * regcache_पढ़ो - Fetch the value of a given रेजिस्टर from the cache.
 *
 * @map: map to configure.
 * @reg: The रेजिस्टर index.
 * @value: The value to be वापसed.
 *
 * Return a negative value on failure, 0 on success.
 */
पूर्णांक regcache_पढ़ो(काष्ठा regmap *map,
		  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक ret;

	अगर (map->cache_type == REGCACHE_NONE)
		वापस -ENOSYS;

	BUG_ON(!map->cache_ops);

	अगर (!regmap_अस्थिर(map, reg)) अणु
		ret = map->cache_ops->पढ़ो(map, reg, value);

		अगर (ret == 0)
			trace_regmap_reg_पढ़ो_cache(map, reg, *value);

		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * regcache_ग_लिखो - Set the value of a given रेजिस्टर in the cache.
 *
 * @map: map to configure.
 * @reg: The रेजिस्टर index.
 * @value: The new रेजिस्टर value.
 *
 * Return a negative value on failure, 0 on success.
 */
पूर्णांक regcache_ग_लिखो(काष्ठा regmap *map,
		   अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	अगर (map->cache_type == REGCACHE_NONE)
		वापस 0;

	BUG_ON(!map->cache_ops);

	अगर (!regmap_अस्थिर(map, reg))
		वापस map->cache_ops->ग_लिखो(map, reg, value);

	वापस 0;
पूर्ण

अटल bool regcache_reg_needs_sync(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	/* If we करोn't know the chip just got reset, then sync everything. */
	अगर (!map->no_sync_शेषs)
		वापस true;

	/* Is this the hardware शेष?  If so skip. */
	ret = regcache_lookup_reg(map, reg);
	अगर (ret >= 0 && val == map->reg_शेषs[ret].def)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक regcache_शेष_sync(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
				 अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक reg;

	क्रम (reg = min; reg <= max; reg += map->reg_stride) अणु
		अचिन्हित पूर्णांक val;
		पूर्णांक ret;

		अगर (regmap_अस्थिर(map, reg) ||
		    !regmap_ग_लिखोable(map, reg))
			जारी;

		ret = regcache_पढ़ो(map, reg, &val);
		अगर (ret)
			वापस ret;

		अगर (!regcache_reg_needs_sync(map, reg, val))
			जारी;

		map->cache_bypass = true;
		ret = _regmap_ग_लिखो(map, reg, val);
		map->cache_bypass = false;
		अगर (ret) अणु
			dev_err(map->dev, "Unable to sync register %#x. %d\n",
				reg, ret);
			वापस ret;
		पूर्ण
		dev_dbg(map->dev, "Synced register %#x, value %#x\n", reg, val);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * regcache_sync - Sync the रेजिस्टर cache with the hardware.
 *
 * @map: map to configure.
 *
 * Any रेजिस्टरs that should not be synced should be marked as
 * अस्थिर.  In general drivers can choose not to use the provided
 * syncing functionality अगर they so require.
 *
 * Return a negative value on failure, 0 on success.
 */
पूर्णांक regcache_sync(काष्ठा regmap *map)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;
	स्थिर अक्षर *name;
	bool bypass;

	BUG_ON(!map->cache_ops);

	map->lock(map->lock_arg);
	/* Remember the initial bypass state */
	bypass = map->cache_bypass;
	dev_dbg(map->dev, "Syncing %s cache\n",
		map->cache_ops->name);
	name = map->cache_ops->name;
	trace_regcache_sync(map, name, "start");

	अगर (!map->cache_dirty)
		जाओ out;

	map->async = true;

	/* Apply any patch first */
	map->cache_bypass = true;
	क्रम (i = 0; i < map->patch_regs; i++) अणु
		ret = _regmap_ग_लिखो(map, map->patch[i].reg, map->patch[i].def);
		अगर (ret != 0) अणु
			dev_err(map->dev, "Failed to write %x = %x: %d\n",
				map->patch[i].reg, map->patch[i].def, ret);
			जाओ out;
		पूर्ण
	पूर्ण
	map->cache_bypass = false;

	अगर (map->cache_ops->sync)
		ret = map->cache_ops->sync(map, 0, map->max_रेजिस्टर);
	अन्यथा
		ret = regcache_शेष_sync(map, 0, map->max_रेजिस्टर);

	अगर (ret == 0)
		map->cache_dirty = false;

out:
	/* Restore the bypass state */
	map->async = false;
	map->cache_bypass = bypass;
	map->no_sync_शेषs = false;
	map->unlock(map->lock_arg);

	regmap_async_complete(map);

	trace_regcache_sync(map, name, "stop");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regcache_sync);

/**
 * regcache_sync_region - Sync part  of the रेजिस्टर cache with the hardware.
 *
 * @map: map to sync.
 * @min: first रेजिस्टर to sync
 * @max: last रेजिस्टर to sync
 *
 * Write all non-शेष रेजिस्टर values in the specअगरied region to
 * the hardware.
 *
 * Return a negative value on failure, 0 on success.
 */
पूर्णांक regcache_sync_region(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
			 अचिन्हित पूर्णांक max)
अणु
	पूर्णांक ret = 0;
	स्थिर अक्षर *name;
	bool bypass;

	BUG_ON(!map->cache_ops);

	map->lock(map->lock_arg);

	/* Remember the initial bypass state */
	bypass = map->cache_bypass;

	name = map->cache_ops->name;
	dev_dbg(map->dev, "Syncing %s cache from %d-%d\n", name, min, max);

	trace_regcache_sync(map, name, "start region");

	अगर (!map->cache_dirty)
		जाओ out;

	map->async = true;

	अगर (map->cache_ops->sync)
		ret = map->cache_ops->sync(map, min, max);
	अन्यथा
		ret = regcache_शेष_sync(map, min, max);

out:
	/* Restore the bypass state */
	map->cache_bypass = bypass;
	map->async = false;
	map->no_sync_शेषs = false;
	map->unlock(map->lock_arg);

	regmap_async_complete(map);

	trace_regcache_sync(map, name, "stop region");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regcache_sync_region);

/**
 * regcache_drop_region - Discard part of the रेजिस्टर cache
 *
 * @map: map to operate on
 * @min: first रेजिस्टर to discard
 * @max: last रेजिस्टर to discard
 *
 * Discard part of the रेजिस्टर cache.
 *
 * Return a negative value on failure, 0 on success.
 */
पूर्णांक regcache_drop_region(काष्ठा regmap *map, अचिन्हित पूर्णांक min,
			 अचिन्हित पूर्णांक max)
अणु
	पूर्णांक ret = 0;

	अगर (!map->cache_ops || !map->cache_ops->drop)
		वापस -EINVAL;

	map->lock(map->lock_arg);

	trace_regcache_drop_region(map, min, max);

	ret = map->cache_ops->drop(map, min, max);

	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regcache_drop_region);

/**
 * regcache_cache_only - Put a रेजिस्टर map पूर्णांकo cache only mode
 *
 * @map: map to configure
 * @enable: flag अगर changes should be written to the hardware
 *
 * When a रेजिस्टर map is marked as cache only ग_लिखोs to the रेजिस्टर
 * map API will only update the रेजिस्टर cache, they will not cause
 * any hardware changes.  This is useful क्रम allowing portions of
 * drivers to act as though the device were functioning as normal when
 * it is disabled क्रम घातer saving reasons.
 */
व्योम regcache_cache_only(काष्ठा regmap *map, bool enable)
अणु
	map->lock(map->lock_arg);
	WARN_ON(map->cache_bypass && enable);
	map->cache_only = enable;
	trace_regmap_cache_only(map, enable);
	map->unlock(map->lock_arg);
पूर्ण
EXPORT_SYMBOL_GPL(regcache_cache_only);

/**
 * regcache_mark_dirty - Indicate that HW रेजिस्टरs were reset to शेष values
 *
 * @map: map to mark
 *
 * Inक्रमm regcache that the device has been घातered करोwn or reset, so that
 * on resume, regcache_sync() knows to ग_लिखो out all non-शेष values
 * stored in the cache.
 *
 * If this function is not called, regcache_sync() will assume that
 * the hardware state still matches the cache state, modulo any ग_लिखोs that
 * happened when cache_only was true.
 */
व्योम regcache_mark_dirty(काष्ठा regmap *map)
अणु
	map->lock(map->lock_arg);
	map->cache_dirty = true;
	map->no_sync_शेषs = true;
	map->unlock(map->lock_arg);
पूर्ण
EXPORT_SYMBOL_GPL(regcache_mark_dirty);

/**
 * regcache_cache_bypass - Put a रेजिस्टर map पूर्णांकo cache bypass mode
 *
 * @map: map to configure
 * @enable: flag अगर changes should not be written to the cache
 *
 * When a रेजिस्टर map is marked with the cache bypass option, ग_लिखोs
 * to the रेजिस्टर map API will only update the hardware and not the
 * the cache directly.  This is useful when syncing the cache back to
 * the hardware.
 */
व्योम regcache_cache_bypass(काष्ठा regmap *map, bool enable)
अणु
	map->lock(map->lock_arg);
	WARN_ON(map->cache_only && enable);
	map->cache_bypass = enable;
	trace_regmap_cache_bypass(map, enable);
	map->unlock(map->lock_arg);
पूर्ण
EXPORT_SYMBOL_GPL(regcache_cache_bypass);

bool regcache_set_val(काष्ठा regmap *map, व्योम *base, अचिन्हित पूर्णांक idx,
		      अचिन्हित पूर्णांक val)
अणु
	अगर (regcache_get_val(map, base, idx) == val)
		वापस true;

	/* Use device native क्रमmat अगर possible */
	अगर (map->क्रमmat.क्रमmat_val) अणु
		map->क्रमmat.क्रमmat_val(base + (map->cache_word_size * idx),
				       val, 0);
		वापस false;
	पूर्ण

	चयन (map->cache_word_size) अणु
	हाल 1: अणु
		u8 *cache = base;

		cache[idx] = val;
		अवरोध;
	पूर्ण
	हाल 2: अणु
		u16 *cache = base;

		cache[idx] = val;
		अवरोध;
	पूर्ण
	हाल 4: अणु
		u32 *cache = base;

		cache[idx] = val;
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_64BIT
	हाल 8: अणु
		u64 *cache = base;

		cache[idx] = val;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण
	वापस false;
पूर्ण

अचिन्हित पूर्णांक regcache_get_val(काष्ठा regmap *map, स्थिर व्योम *base,
			      अचिन्हित पूर्णांक idx)
अणु
	अगर (!base)
		वापस -EINVAL;

	/* Use device native क्रमmat अगर possible */
	अगर (map->क्रमmat.parse_val)
		वापस map->क्रमmat.parse_val(regcache_get_val_addr(map, base,
								   idx));

	चयन (map->cache_word_size) अणु
	हाल 1: अणु
		स्थिर u8 *cache = base;

		वापस cache[idx];
	पूर्ण
	हाल 2: अणु
		स्थिर u16 *cache = base;

		वापस cache[idx];
	पूर्ण
	हाल 4: अणु
		स्थिर u32 *cache = base;

		वापस cache[idx];
	पूर्ण
#अगर_घोषित CONFIG_64BIT
	हाल 8: अणु
		स्थिर u64 *cache = base;

		वापस cache[idx];
	पूर्ण
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण
	/* unreachable */
	वापस -1;
पूर्ण

अटल पूर्णांक regcache_शेष_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा reg_शेष *_a = a;
	स्थिर काष्ठा reg_शेष *_b = b;

	वापस _a->reg - _b->reg;
पूर्ण

पूर्णांक regcache_lookup_reg(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा reg_शेष key;
	काष्ठा reg_शेष *r;

	key.reg = reg;
	key.def = 0;

	r = द्वा_खोज(&key, map->reg_शेषs, map->num_reg_शेषs,
		    माप(काष्ठा reg_शेष), regcache_शेष_cmp);

	अगर (r)
		वापस r - map->reg_शेषs;
	अन्यथा
		वापस -ENOENT;
पूर्ण

अटल bool regcache_reg_present(अचिन्हित दीर्घ *cache_present, अचिन्हित पूर्णांक idx)
अणु
	अगर (!cache_present)
		वापस true;

	वापस test_bit(idx, cache_present);
पूर्ण

अटल पूर्णांक regcache_sync_block_single(काष्ठा regmap *map, व्योम *block,
				      अचिन्हित दीर्घ *cache_present,
				      अचिन्हित पूर्णांक block_base,
				      अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	अचिन्हित पूर्णांक i, regपंचांगp, val;
	पूर्णांक ret;

	क्रम (i = start; i < end; i++) अणु
		regपंचांगp = block_base + (i * map->reg_stride);

		अगर (!regcache_reg_present(cache_present, i) ||
		    !regmap_ग_लिखोable(map, regपंचांगp))
			जारी;

		val = regcache_get_val(map, block, i);
		अगर (!regcache_reg_needs_sync(map, regपंचांगp, val))
			जारी;

		map->cache_bypass = true;

		ret = _regmap_ग_लिखो(map, regपंचांगp, val);

		map->cache_bypass = false;
		अगर (ret != 0) अणु
			dev_err(map->dev, "Unable to sync register %#x. %d\n",
				regपंचांगp, ret);
			वापस ret;
		पूर्ण
		dev_dbg(map->dev, "Synced register %#x, value %#x\n",
			regपंचांगp, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक regcache_sync_block_raw_flush(काष्ठा regmap *map, स्थिर व्योम **data,
					 अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक cur)
अणु
	माप_प्रकार val_bytes = map->क्रमmat.val_bytes;
	पूर्णांक ret, count;

	अगर (*data == शून्य)
		वापस 0;

	count = (cur - base) / map->reg_stride;

	dev_dbg(map->dev, "Writing %zu bytes for %d registers from 0x%x-0x%x\n",
		count * val_bytes, count, base, cur - map->reg_stride);

	map->cache_bypass = true;

	ret = _regmap_raw_ग_लिखो(map, base, *data, count * val_bytes, false);
	अगर (ret)
		dev_err(map->dev, "Unable to sync registers %#x-%#x. %d\n",
			base, cur - map->reg_stride, ret);

	map->cache_bypass = false;

	*data = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक regcache_sync_block_raw(काष्ठा regmap *map, व्योम *block,
			    अचिन्हित दीर्घ *cache_present,
			    अचिन्हित पूर्णांक block_base, अचिन्हित पूर्णांक start,
			    अचिन्हित पूर्णांक end)
अणु
	अचिन्हित पूर्णांक i, val;
	अचिन्हित पूर्णांक regपंचांगp = 0;
	अचिन्हित पूर्णांक base = 0;
	स्थिर व्योम *data = शून्य;
	पूर्णांक ret;

	क्रम (i = start; i < end; i++) अणु
		regपंचांगp = block_base + (i * map->reg_stride);

		अगर (!regcache_reg_present(cache_present, i) ||
		    !regmap_ग_लिखोable(map, regपंचांगp)) अणु
			ret = regcache_sync_block_raw_flush(map, &data,
							    base, regपंचांगp);
			अगर (ret != 0)
				वापस ret;
			जारी;
		पूर्ण

		val = regcache_get_val(map, block, i);
		अगर (!regcache_reg_needs_sync(map, regपंचांगp, val)) अणु
			ret = regcache_sync_block_raw_flush(map, &data,
							    base, regपंचांगp);
			अगर (ret != 0)
				वापस ret;
			जारी;
		पूर्ण

		अगर (!data) अणु
			data = regcache_get_val_addr(map, block, i);
			base = regपंचांगp;
		पूर्ण
	पूर्ण

	वापस regcache_sync_block_raw_flush(map, &data, base, regपंचांगp +
			map->reg_stride);
पूर्ण

पूर्णांक regcache_sync_block(काष्ठा regmap *map, व्योम *block,
			अचिन्हित दीर्घ *cache_present,
			अचिन्हित पूर्णांक block_base, अचिन्हित पूर्णांक start,
			अचिन्हित पूर्णांक end)
अणु
	अगर (regmap_can_raw_ग_लिखो(map) && !map->use_single_ग_लिखो)
		वापस regcache_sync_block_raw(map, block, cache_present,
					       block_base, start, end);
	अन्यथा
		वापस regcache_sync_block_single(map, block, cache_present,
						  block_base, start, end);
पूर्ण
