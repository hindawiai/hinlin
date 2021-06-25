<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Register map access API पूर्णांकernal header
 *
 * Copyright 2011 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित _REGMAP_INTERNAL_H
#घोषणा _REGMAP_INTERNAL_H

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>

काष्ठा regmap;
काष्ठा regcache_ops;

काष्ठा regmap_debugfs_off_cache अणु
	काष्ठा list_head list;
	off_t min;
	off_t max;
	अचिन्हित पूर्णांक base_reg;
	अचिन्हित पूर्णांक max_reg;
पूर्ण;

काष्ठा regmap_क्रमmat अणु
	माप_प्रकार buf_size;
	माप_प्रकार reg_bytes;
	माप_प्रकार pad_bytes;
	माप_प्रकार val_bytes;
	व्योम (*क्रमmat_ग_लिखो)(काष्ठा regmap *map,
			     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
	व्योम (*क्रमmat_reg)(व्योम *buf, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक shअगरt);
	व्योम (*क्रमmat_val)(व्योम *buf, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt);
	अचिन्हित पूर्णांक (*parse_val)(स्थिर व्योम *buf);
	व्योम (*parse_inplace)(व्योम *buf);
पूर्ण;

काष्ठा regmap_async अणु
	काष्ठा list_head list;
	काष्ठा regmap *map;
	व्योम *work_buf;
पूर्ण;

काष्ठा regmap अणु
	जोड़ अणु
		काष्ठा mutex mutex;
		काष्ठा अणु
			spinlock_t spinlock;
			अचिन्हित दीर्घ spinlock_flags;
		पूर्ण;
	पूर्ण;
	regmap_lock lock;
	regmap_unlock unlock;
	व्योम *lock_arg; /* This is passed to lock/unlock functions */
	gfp_t alloc_flags;

	काष्ठा device *dev; /* Device we करो I/O on */
	व्योम *work_buf;     /* Scratch buffer used to क्रमmat I/O */
	काष्ठा regmap_क्रमmat क्रमmat;  /* Buffer क्रमmat */
	स्थिर काष्ठा regmap_bus *bus;
	व्योम *bus_context;
	स्थिर अक्षर *name;

	bool async;
	spinlock_t async_lock;
	रुको_queue_head_t async_रुकोq;
	काष्ठा list_head async_list;
	काष्ठा list_head async_मुक्त;
	पूर्णांक async_ret;

#अगर_घोषित CONFIG_DEBUG_FS
	bool debugfs_disable;
	काष्ठा dentry *debugfs;
	स्थिर अक्षर *debugfs_name;

	अचिन्हित पूर्णांक debugfs_reg_len;
	अचिन्हित पूर्णांक debugfs_val_len;
	अचिन्हित पूर्णांक debugfs_tot_len;

	काष्ठा list_head debugfs_off_cache;
	काष्ठा mutex cache_lock;
#पूर्ण_अगर

	अचिन्हित पूर्णांक max_रेजिस्टर;
	bool (*ग_लिखोable_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*पढ़ोable_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*अस्थिर_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*precious_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*ग_लिखोable_noinc_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	bool (*पढ़ोable_noinc_reg)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
	स्थिर काष्ठा regmap_access_table *wr_table;
	स्थिर काष्ठा regmap_access_table *rd_table;
	स्थिर काष्ठा regmap_access_table *अस्थिर_table;
	स्थिर काष्ठा regmap_access_table *precious_table;
	स्थिर काष्ठा regmap_access_table *wr_noinc_table;
	स्थिर काष्ठा regmap_access_table *rd_noinc_table;

	पूर्णांक (*reg_पढ़ो)(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val);
	पूर्णांक (*reg_ग_लिखो)(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
	पूर्णांक (*reg_update_bits)(व्योम *context, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val);

	bool defer_caching;

	अचिन्हित दीर्घ पढ़ो_flag_mask;
	अचिन्हित दीर्घ ग_लिखो_flag_mask;

	/* number of bits to (left) shअगरt the reg value when क्रमmatting*/
	पूर्णांक reg_shअगरt;
	पूर्णांक reg_stride;
	पूर्णांक reg_stride_order;

	/* regcache specअगरic members */
	स्थिर काष्ठा regcache_ops *cache_ops;
	क्रमागत regcache_type cache_type;

	/* number of bytes in reg_शेषs_raw */
	अचिन्हित पूर्णांक cache_size_raw;
	/* number of bytes per word in reg_शेषs_raw */
	अचिन्हित पूर्णांक cache_word_size;
	/* number of entries in reg_शेषs */
	अचिन्हित पूर्णांक num_reg_शेषs;
	/* number of entries in reg_शेषs_raw */
	अचिन्हित पूर्णांक num_reg_शेषs_raw;

	/* अगर set, only the cache is modअगरied not the HW */
	bool cache_only;
	/* अगर set, only the HW is modअगरied not the cache */
	bool cache_bypass;
	/* अगर set, remember to मुक्त reg_शेषs_raw */
	bool cache_मुक्त;

	काष्ठा reg_शेष *reg_शेषs;
	स्थिर व्योम *reg_शेषs_raw;
	व्योम *cache;
	/* अगर set, the cache contains newer data than the HW */
	bool cache_dirty;
	/* अगर set, the HW रेजिस्टरs are known to match map->reg_शेषs */
	bool no_sync_शेषs;

	काष्ठा reg_sequence *patch;
	पूर्णांक patch_regs;

	/* अगर set, converts bulk पढ़ो to single पढ़ो */
	bool use_single_पढ़ो;
	/* अगर set, converts bulk ग_लिखो to single ग_लिखो */
	bool use_single_ग_लिखो;
	/* अगर set, the device supports multi ग_लिखो mode */
	bool can_multi_ग_लिखो;

	/* अगर set, raw पढ़ोs/ग_लिखोs are limited to this size */
	माप_प्रकार max_raw_पढ़ो;
	माप_प्रकार max_raw_ग_लिखो;

	काष्ठा rb_root range_tree;
	व्योम *selector_work_buf;	/* Scratch buffer used क्रम selector */

	काष्ठा hwspinlock *hwlock;

	/* अगर set, the regmap core can sleep */
	bool can_sleep;
पूर्ण;

काष्ठा regcache_ops अणु
	स्थिर अक्षर *name;
	क्रमागत regcache_type type;
	पूर्णांक (*init)(काष्ठा regmap *map);
	पूर्णांक (*निकास)(काष्ठा regmap *map);
#अगर_घोषित CONFIG_DEBUG_FS
	व्योम (*debugfs_init)(काष्ठा regmap *map);
#पूर्ण_अगर
	पूर्णांक (*पढ़ो)(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value);
	पूर्णांक (*ग_लिखो)(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value);
	पूर्णांक (*sync)(काष्ठा regmap *map, अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max);
	पूर्णांक (*drop)(काष्ठा regmap *map, अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max);
पूर्ण;

bool regmap_cached(काष्ठा regmap *map, अचिन्हित पूर्णांक reg);
bool regmap_ग_लिखोable(काष्ठा regmap *map, अचिन्हित पूर्णांक reg);
bool regmap_पढ़ोable(काष्ठा regmap *map, अचिन्हित पूर्णांक reg);
bool regmap_अस्थिर(काष्ठा regmap *map, अचिन्हित पूर्णांक reg);
bool regmap_precious(काष्ठा regmap *map, अचिन्हित पूर्णांक reg);
bool regmap_ग_लिखोable_noinc(काष्ठा regmap *map, अचिन्हित पूर्णांक reg);
bool regmap_पढ़ोable_noinc(काष्ठा regmap *map, अचिन्हित पूर्णांक reg);

पूर्णांक _regmap_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		  अचिन्हित पूर्णांक val);

काष्ठा regmap_range_node अणु
	काष्ठा rb_node node;
	स्थिर अक्षर *name;
	काष्ठा regmap *map;

	अचिन्हित पूर्णांक range_min;
	अचिन्हित पूर्णांक range_max;

	अचिन्हित पूर्णांक selector_reg;
	अचिन्हित पूर्णांक selector_mask;
	पूर्णांक selector_shअगरt;

	अचिन्हित पूर्णांक winकरोw_start;
	अचिन्हित पूर्णांक winकरोw_len;
पूर्ण;

काष्ठा regmap_field अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक mask;
	/* lsb */
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक reg;

	अचिन्हित पूर्णांक id_size;
	अचिन्हित पूर्णांक id_offset;
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
बाह्य व्योम regmap_debugfs_initcall(व्योम);
बाह्य व्योम regmap_debugfs_init(काष्ठा regmap *map);
बाह्य व्योम regmap_debugfs_निकास(काष्ठा regmap *map);

अटल अंतरभूत व्योम regmap_debugfs_disable(काष्ठा regmap *map)
अणु
	map->debugfs_disable = true;
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम regmap_debugfs_initcall(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम regmap_debugfs_init(काष्ठा regmap *map) अणु पूर्ण
अटल अंतरभूत व्योम regmap_debugfs_निकास(काष्ठा regmap *map) अणु पूर्ण
अटल अंतरभूत व्योम regmap_debugfs_disable(काष्ठा regmap *map) अणु पूर्ण
#पूर्ण_अगर

/* regcache core declarations */
पूर्णांक regcache_init(काष्ठा regmap *map, स्थिर काष्ठा regmap_config *config);
व्योम regcache_निकास(काष्ठा regmap *map);
पूर्णांक regcache_पढ़ो(काष्ठा regmap *map,
		       अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value);
पूर्णांक regcache_ग_लिखो(काष्ठा regmap *map,
			अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value);
पूर्णांक regcache_sync(काष्ठा regmap *map);
पूर्णांक regcache_sync_block(काष्ठा regmap *map, व्योम *block,
			अचिन्हित दीर्घ *cache_present,
			अचिन्हित पूर्णांक block_base, अचिन्हित पूर्णांक start,
			अचिन्हित पूर्णांक end);

अटल अंतरभूत स्थिर व्योम *regcache_get_val_addr(काष्ठा regmap *map,
						स्थिर व्योम *base,
						अचिन्हित पूर्णांक idx)
अणु
	वापस base + (map->cache_word_size * idx);
पूर्ण

अचिन्हित पूर्णांक regcache_get_val(काष्ठा regmap *map, स्थिर व्योम *base,
			      अचिन्हित पूर्णांक idx);
bool regcache_set_val(काष्ठा regmap *map, व्योम *base, अचिन्हित पूर्णांक idx,
		      अचिन्हित पूर्णांक val);
पूर्णांक regcache_lookup_reg(काष्ठा regmap *map, अचिन्हित पूर्णांक reg);

पूर्णांक _regmap_raw_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		      स्थिर व्योम *val, माप_प्रकार val_len, bool noinc);

व्योम regmap_async_complete_cb(काष्ठा regmap_async *async, पूर्णांक ret);

क्रमागत regmap_endian regmap_get_val_endian(काष्ठा device *dev,
					 स्थिर काष्ठा regmap_bus *bus,
					 स्थिर काष्ठा regmap_config *config);

बाह्य काष्ठा regcache_ops regcache_rbtree_ops;
बाह्य काष्ठा regcache_ops regcache_lzo_ops;
बाह्य काष्ठा regcache_ops regcache_flat_ops;

अटल अंतरभूत स्थिर अक्षर *regmap_name(स्थिर काष्ठा regmap *map)
अणु
	अगर (map->dev)
		वापस dev_name(map->dev);

	वापस map->name;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक regmap_get_offset(स्थिर काष्ठा regmap *map,
					     अचिन्हित पूर्णांक index)
अणु
	अगर (map->reg_stride_order >= 0)
		वापस index << map->reg_stride_order;
	अन्यथा
		वापस index * map->reg_stride;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक regcache_get_index_by_order(स्थिर काष्ठा regmap *map,
						       अचिन्हित पूर्णांक reg)
अणु
	वापस reg >> map->reg_stride_order;
पूर्ण

#पूर्ण_अगर
