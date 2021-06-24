<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register map access API
//
// Copyright 2011 Wolfson Microelectronics plc
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/property.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/hwspinlock.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

#समावेश "internal.h"

/*
 * Someबार क्रम failures during very early init the trace
 * infraकाष्ठाure isn't available early enough to be used.  For this
 * sort of problem defining LOG_DEVICE will add prपूर्णांकks क्रम basic
 * रेजिस्टर I/O on a specअगरic device.
 */
#अघोषित LOG_DEVICE

#अगर_घोषित LOG_DEVICE
अटल अंतरभूत bool regmap_should_log(काष्ठा regmap *map)
अणु
	वापस (map->dev && म_भेद(dev_name(map->dev), LOG_DEVICE) == 0);
पूर्ण
#अन्यथा
अटल अंतरभूत bool regmap_should_log(काष्ठा regmap *map) अणु वापस false; पूर्ण
#पूर्ण_अगर


अटल पूर्णांक _regmap_update_bits(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
			       bool *change, bool क्रमce_ग_लिखो);

अटल पूर्णांक _regmap_bus_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक *val);
अटल पूर्णांक _regmap_bus_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक *val);
अटल पूर्णांक _regmap_bus_क्रमmatted_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				       अचिन्हित पूर्णांक val);
अटल पूर्णांक _regmap_bus_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक val);
अटल पूर्णांक _regmap_bus_raw_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक val);

bool regmap_reg_in_ranges(अचिन्हित पूर्णांक reg,
			  स्थिर काष्ठा regmap_range *ranges,
			  अचिन्हित पूर्णांक nranges)
अणु
	स्थिर काष्ठा regmap_range *r;
	पूर्णांक i;

	क्रम (i = 0, r = ranges; i < nranges; i++, r++)
		अगर (regmap_reg_in_range(reg, r))
			वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_reg_in_ranges);

bool regmap_check_range_table(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			      स्थिर काष्ठा regmap_access_table *table)
अणु
	/* Check "no ranges" first */
	अगर (regmap_reg_in_ranges(reg, table->no_ranges, table->n_no_ranges))
		वापस false;

	/* In हाल zero "yes ranges" are supplied, any reg is OK */
	अगर (!table->n_yes_ranges)
		वापस true;

	वापस regmap_reg_in_ranges(reg, table->yes_ranges,
				    table->n_yes_ranges);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_check_range_table);

bool regmap_ग_लिखोable(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	अगर (map->max_रेजिस्टर && reg > map->max_रेजिस्टर)
		वापस false;

	अगर (map->ग_लिखोable_reg)
		वापस map->ग_लिखोable_reg(map->dev, reg);

	अगर (map->wr_table)
		वापस regmap_check_range_table(map, reg, map->wr_table);

	वापस true;
पूर्ण

bool regmap_cached(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	अगर (map->cache_type == REGCACHE_NONE)
		वापस false;

	अगर (!map->cache_ops)
		वापस false;

	अगर (map->max_रेजिस्टर && reg > map->max_रेजिस्टर)
		वापस false;

	map->lock(map->lock_arg);
	ret = regcache_पढ़ो(map, reg, &val);
	map->unlock(map->lock_arg);
	अगर (ret)
		वापस false;

	वापस true;
पूर्ण

bool regmap_पढ़ोable(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	अगर (!map->reg_पढ़ो)
		वापस false;

	अगर (map->max_रेजिस्टर && reg > map->max_रेजिस्टर)
		वापस false;

	अगर (map->क्रमmat.क्रमmat_ग_लिखो)
		वापस false;

	अगर (map->पढ़ोable_reg)
		वापस map->पढ़ोable_reg(map->dev, reg);

	अगर (map->rd_table)
		वापस regmap_check_range_table(map, reg, map->rd_table);

	वापस true;
पूर्ण

bool regmap_अस्थिर(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	अगर (!map->क्रमmat.क्रमmat_ग_लिखो && !regmap_पढ़ोable(map, reg))
		वापस false;

	अगर (map->अस्थिर_reg)
		वापस map->अस्थिर_reg(map->dev, reg);

	अगर (map->अस्थिर_table)
		वापस regmap_check_range_table(map, reg, map->अस्थिर_table);

	अगर (map->cache_ops)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

bool regmap_precious(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	अगर (!regmap_पढ़ोable(map, reg))
		वापस false;

	अगर (map->precious_reg)
		वापस map->precious_reg(map->dev, reg);

	अगर (map->precious_table)
		वापस regmap_check_range_table(map, reg, map->precious_table);

	वापस false;
पूर्ण

bool regmap_ग_लिखोable_noinc(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	अगर (map->ग_लिखोable_noinc_reg)
		वापस map->ग_लिखोable_noinc_reg(map->dev, reg);

	अगर (map->wr_noinc_table)
		वापस regmap_check_range_table(map, reg, map->wr_noinc_table);

	वापस true;
पूर्ण

bool regmap_पढ़ोable_noinc(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	अगर (map->पढ़ोable_noinc_reg)
		वापस map->पढ़ोable_noinc_reg(map->dev, reg);

	अगर (map->rd_noinc_table)
		वापस regmap_check_range_table(map, reg, map->rd_noinc_table);

	वापस true;
पूर्ण

अटल bool regmap_अस्थिर_range(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
	माप_प्रकार num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		अगर (!regmap_अस्थिर(map, reg + regmap_get_offset(map, i)))
			वापस false;

	वापस true;
पूर्ण

अटल व्योम regmap_क्रमmat_12_20_ग_लिखो(काष्ठा regmap *map,
				     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	u8 *out = map->work_buf;

	out[0] = reg >> 4;
	out[1] = (reg << 4) | (val >> 16);
	out[2] = val >> 8;
	out[3] = val;
पूर्ण


अटल व्योम regmap_क्रमmat_2_6_ग_लिखो(काष्ठा regmap *map,
				     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	u8 *out = map->work_buf;

	*out = (reg << 6) | val;
पूर्ण

अटल व्योम regmap_क्रमmat_4_12_ग_लिखो(काष्ठा regmap *map,
				     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	__be16 *out = map->work_buf;
	*out = cpu_to_be16((reg << 12) | val);
पूर्ण

अटल व्योम regmap_क्रमmat_7_9_ग_लिखो(काष्ठा regmap *map,
				    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	__be16 *out = map->work_buf;
	*out = cpu_to_be16((reg << 9) | val);
पूर्ण

अटल व्योम regmap_क्रमmat_10_14_ग_लिखो(काष्ठा regmap *map,
				    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	u8 *out = map->work_buf;

	out[2] = val;
	out[1] = (val >> 8) | (reg << 6);
	out[0] = reg >> 2;
पूर्ण

अटल व्योम regmap_क्रमmat_8(व्योम *buf, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	u8 *b = buf;

	b[0] = val << shअगरt;
पूर्ण

अटल व्योम regmap_क्रमmat_16_be(व्योम *buf, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	put_unaligned_be16(val << shअगरt, buf);
पूर्ण

अटल व्योम regmap_क्रमmat_16_le(व्योम *buf, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	put_unaligned_le16(val << shअगरt, buf);
पूर्ण

अटल व्योम regmap_क्रमmat_16_native(व्योम *buf, अचिन्हित पूर्णांक val,
				    अचिन्हित पूर्णांक shअगरt)
अणु
	u16 v = val << shअगरt;

	स_नकल(buf, &v, माप(v));
पूर्ण

अटल व्योम regmap_क्रमmat_24(व्योम *buf, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	u8 *b = buf;

	val <<= shअगरt;

	b[0] = val >> 16;
	b[1] = val >> 8;
	b[2] = val;
पूर्ण

अटल व्योम regmap_क्रमmat_32_be(व्योम *buf, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	put_unaligned_be32(val << shअगरt, buf);
पूर्ण

अटल व्योम regmap_क्रमmat_32_le(व्योम *buf, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	put_unaligned_le32(val << shअगरt, buf);
पूर्ण

अटल व्योम regmap_क्रमmat_32_native(व्योम *buf, अचिन्हित पूर्णांक val,
				    अचिन्हित पूर्णांक shअगरt)
अणु
	u32 v = val << shअगरt;

	स_नकल(buf, &v, माप(v));
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल व्योम regmap_क्रमmat_64_be(व्योम *buf, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	put_unaligned_be64((u64) val << shअगरt, buf);
पूर्ण

अटल व्योम regmap_क्रमmat_64_le(व्योम *buf, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	put_unaligned_le64((u64) val << shअगरt, buf);
पूर्ण

अटल व्योम regmap_क्रमmat_64_native(व्योम *buf, अचिन्हित पूर्णांक val,
				    अचिन्हित पूर्णांक shअगरt)
अणु
	u64 v = (u64) val << shअगरt;

	स_नकल(buf, &v, माप(v));
पूर्ण
#पूर्ण_अगर

अटल व्योम regmap_parse_inplace_noop(व्योम *buf)
अणु
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_8(स्थिर व्योम *buf)
अणु
	स्थिर u8 *b = buf;

	वापस b[0];
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_16_be(स्थिर व्योम *buf)
अणु
	वापस get_unaligned_be16(buf);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_16_le(स्थिर व्योम *buf)
अणु
	वापस get_unaligned_le16(buf);
पूर्ण

अटल व्योम regmap_parse_16_be_inplace(व्योम *buf)
अणु
	u16 v = get_unaligned_be16(buf);

	स_नकल(buf, &v, माप(v));
पूर्ण

अटल व्योम regmap_parse_16_le_inplace(व्योम *buf)
अणु
	u16 v = get_unaligned_le16(buf);

	स_नकल(buf, &v, माप(v));
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_16_native(स्थिर व्योम *buf)
अणु
	u16 v;

	स_नकल(&v, buf, माप(v));
	वापस v;
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_24(स्थिर व्योम *buf)
अणु
	स्थिर u8 *b = buf;
	अचिन्हित पूर्णांक ret = b[2];
	ret |= ((अचिन्हित पूर्णांक)b[1]) << 8;
	ret |= ((अचिन्हित पूर्णांक)b[0]) << 16;

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_32_be(स्थिर व्योम *buf)
अणु
	वापस get_unaligned_be32(buf);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_32_le(स्थिर व्योम *buf)
अणु
	वापस get_unaligned_le32(buf);
पूर्ण

अटल व्योम regmap_parse_32_be_inplace(व्योम *buf)
अणु
	u32 v = get_unaligned_be32(buf);

	स_नकल(buf, &v, माप(v));
पूर्ण

अटल व्योम regmap_parse_32_le_inplace(व्योम *buf)
अणु
	u32 v = get_unaligned_le32(buf);

	स_नकल(buf, &v, माप(v));
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_32_native(स्थिर व्योम *buf)
अणु
	u32 v;

	स_नकल(&v, buf, माप(v));
	वापस v;
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल अचिन्हित पूर्णांक regmap_parse_64_be(स्थिर व्योम *buf)
अणु
	वापस get_unaligned_be64(buf);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_64_le(स्थिर व्योम *buf)
अणु
	वापस get_unaligned_le64(buf);
पूर्ण

अटल व्योम regmap_parse_64_be_inplace(व्योम *buf)
अणु
	u64 v =  get_unaligned_be64(buf);

	स_नकल(buf, &v, माप(v));
पूर्ण

अटल व्योम regmap_parse_64_le_inplace(व्योम *buf)
अणु
	u64 v = get_unaligned_le64(buf);

	स_नकल(buf, &v, माप(v));
पूर्ण

अटल अचिन्हित पूर्णांक regmap_parse_64_native(स्थिर व्योम *buf)
अणु
	u64 v;

	स_नकल(&v, buf, माप(v));
	वापस v;
पूर्ण
#पूर्ण_अगर

अटल व्योम regmap_lock_hwlock(व्योम *__map)
अणु
	काष्ठा regmap *map = __map;

	hwspin_lock_समयout(map->hwlock, अच_पूर्णांक_उच्च);
पूर्ण

अटल व्योम regmap_lock_hwlock_irq(व्योम *__map)
अणु
	काष्ठा regmap *map = __map;

	hwspin_lock_समयout_irq(map->hwlock, अच_पूर्णांक_उच्च);
पूर्ण

अटल व्योम regmap_lock_hwlock_irqsave(व्योम *__map)
अणु
	काष्ठा regmap *map = __map;

	hwspin_lock_समयout_irqsave(map->hwlock, अच_पूर्णांक_उच्च,
				    &map->spinlock_flags);
पूर्ण

अटल व्योम regmap_unlock_hwlock(व्योम *__map)
अणु
	काष्ठा regmap *map = __map;

	hwspin_unlock(map->hwlock);
पूर्ण

अटल व्योम regmap_unlock_hwlock_irq(व्योम *__map)
अणु
	काष्ठा regmap *map = __map;

	hwspin_unlock_irq(map->hwlock);
पूर्ण

अटल व्योम regmap_unlock_hwlock_irqrestore(व्योम *__map)
अणु
	काष्ठा regmap *map = __map;

	hwspin_unlock_irqrestore(map->hwlock, &map->spinlock_flags);
पूर्ण

अटल व्योम regmap_lock_unlock_none(व्योम *__map)
अणु

पूर्ण

अटल व्योम regmap_lock_mutex(व्योम *__map)
अणु
	काष्ठा regmap *map = __map;
	mutex_lock(&map->mutex);
पूर्ण

अटल व्योम regmap_unlock_mutex(व्योम *__map)
अणु
	काष्ठा regmap *map = __map;
	mutex_unlock(&map->mutex);
पूर्ण

अटल व्योम regmap_lock_spinlock(व्योम *__map)
__acquires(&map->spinlock)
अणु
	काष्ठा regmap *map = __map;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&map->spinlock, flags);
	map->spinlock_flags = flags;
पूर्ण

अटल व्योम regmap_unlock_spinlock(व्योम *__map)
__releases(&map->spinlock)
अणु
	काष्ठा regmap *map = __map;
	spin_unlock_irqrestore(&map->spinlock, map->spinlock_flags);
पूर्ण

अटल व्योम dev_get_regmap_release(काष्ठा device *dev, व्योम *res)
अणु
	/*
	 * We करोn't actually have anything to करो here; the goal here
	 * is not to manage the regmap but to provide a simple way to
	 * get the regmap back given a काष्ठा device.
	 */
पूर्ण

अटल bool _regmap_range_add(काष्ठा regmap *map,
			      काष्ठा regmap_range_node *data)
अणु
	काष्ठा rb_root *root = &map->range_tree;
	काष्ठा rb_node **new = &(root->rb_node), *parent = शून्य;

	जबतक (*new) अणु
		काष्ठा regmap_range_node *this =
			rb_entry(*new, काष्ठा regmap_range_node, node);

		parent = *new;
		अगर (data->range_max < this->range_min)
			new = &((*new)->rb_left);
		अन्यथा अगर (data->range_min > this->range_max)
			new = &((*new)->rb_right);
		अन्यथा
			वापस false;
	पूर्ण

	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node, root);

	वापस true;
पूर्ण

अटल काष्ठा regmap_range_node *_regmap_range_lookup(काष्ठा regmap *map,
						      अचिन्हित पूर्णांक reg)
अणु
	काष्ठा rb_node *node = map->range_tree.rb_node;

	जबतक (node) अणु
		काष्ठा regmap_range_node *this =
			rb_entry(node, काष्ठा regmap_range_node, node);

		अगर (reg < this->range_min)
			node = node->rb_left;
		अन्यथा अगर (reg > this->range_max)
			node = node->rb_right;
		अन्यथा
			वापस this;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम regmap_range_निकास(काष्ठा regmap *map)
अणु
	काष्ठा rb_node *next;
	काष्ठा regmap_range_node *range_node;

	next = rb_first(&map->range_tree);
	जबतक (next) अणु
		range_node = rb_entry(next, काष्ठा regmap_range_node, node);
		next = rb_next(&range_node->node);
		rb_erase(&range_node->node, &map->range_tree);
		kमुक्त(range_node);
	पूर्ण

	kमुक्त(map->selector_work_buf);
पूर्ण

अटल पूर्णांक regmap_set_name(काष्ठा regmap *map, स्थिर काष्ठा regmap_config *config)
अणु
	अगर (config->name) अणु
		स्थिर अक्षर *name = kstrdup_स्थिर(config->name, GFP_KERNEL);

		अगर (!name)
			वापस -ENOMEM;

		kमुक्त_स्थिर(map->name);
		map->name = name;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक regmap_attach_dev(काष्ठा device *dev, काष्ठा regmap *map,
		      स्थिर काष्ठा regmap_config *config)
अणु
	काष्ठा regmap **m;
	पूर्णांक ret;

	map->dev = dev;

	ret = regmap_set_name(map, config);
	अगर (ret)
		वापस ret;

	regmap_debugfs_init(map);

	/* Add a devres resource क्रम dev_get_regmap() */
	m = devres_alloc(dev_get_regmap_release, माप(*m), GFP_KERNEL);
	अगर (!m) अणु
		regmap_debugfs_निकास(map);
		वापस -ENOMEM;
	पूर्ण
	*m = map;
	devres_add(dev, m);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_attach_dev);

अटल क्रमागत regmap_endian regmap_get_reg_endian(स्थिर काष्ठा regmap_bus *bus,
					स्थिर काष्ठा regmap_config *config)
अणु
	क्रमागत regmap_endian endian;

	/* Retrieve the endianness specअगरication from the regmap config */
	endian = config->reg_क्रमmat_endian;

	/* If the regmap config specअगरied a non-शेष value, use that */
	अगर (endian != REGMAP_ENDIAN_DEFAULT)
		वापस endian;

	/* Retrieve the endianness specअगरication from the bus config */
	अगर (bus && bus->reg_क्रमmat_endian_शेष)
		endian = bus->reg_क्रमmat_endian_शेष;

	/* If the bus specअगरied a non-शेष value, use that */
	अगर (endian != REGMAP_ENDIAN_DEFAULT)
		वापस endian;

	/* Use this अगर no other value was found */
	वापस REGMAP_ENDIAN_BIG;
पूर्ण

क्रमागत regmap_endian regmap_get_val_endian(काष्ठा device *dev,
					 स्थिर काष्ठा regmap_bus *bus,
					 स्थिर काष्ठा regmap_config *config)
अणु
	काष्ठा fwnode_handle *fwnode = dev ? dev_fwnode(dev) : शून्य;
	क्रमागत regmap_endian endian;

	/* Retrieve the endianness specअगरication from the regmap config */
	endian = config->val_क्रमmat_endian;

	/* If the regmap config specअगरied a non-शेष value, use that */
	अगर (endian != REGMAP_ENDIAN_DEFAULT)
		वापस endian;

	/* If the firmware node exist try to get endianness from it */
	अगर (fwnode_property_पढ़ो_bool(fwnode, "big-endian"))
		endian = REGMAP_ENDIAN_BIG;
	अन्यथा अगर (fwnode_property_पढ़ो_bool(fwnode, "little-endian"))
		endian = REGMAP_ENDIAN_LITTLE;
	अन्यथा अगर (fwnode_property_पढ़ो_bool(fwnode, "native-endian"))
		endian = REGMAP_ENDIAN_NATIVE;

	/* If the endianness was specअगरied in fwnode, use that */
	अगर (endian != REGMAP_ENDIAN_DEFAULT)
		वापस endian;

	/* Retrieve the endianness specअगरication from the bus config */
	अगर (bus && bus->val_क्रमmat_endian_शेष)
		endian = bus->val_क्रमmat_endian_शेष;

	/* If the bus specअगरied a non-शेष value, use that */
	अगर (endian != REGMAP_ENDIAN_DEFAULT)
		वापस endian;

	/* Use this अगर no other value was found */
	वापस REGMAP_ENDIAN_BIG;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_get_val_endian);

काष्ठा regmap *__regmap_init(काष्ठा device *dev,
			     स्थिर काष्ठा regmap_bus *bus,
			     व्योम *bus_context,
			     स्थिर काष्ठा regmap_config *config,
			     काष्ठा lock_class_key *lock_key,
			     स्थिर अक्षर *lock_name)
अणु
	काष्ठा regmap *map;
	पूर्णांक ret = -EINVAL;
	क्रमागत regmap_endian reg_endian, val_endian;
	पूर्णांक i, j;

	अगर (!config)
		जाओ err;

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (map == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = regmap_set_name(map, config);
	अगर (ret)
		जाओ err_map;

	ret = -EINVAL; /* Later error paths rely on this */

	अगर (config->disable_locking) अणु
		map->lock = map->unlock = regmap_lock_unlock_none;
		map->can_sleep = config->can_sleep;
		regmap_debugfs_disable(map);
	पूर्ण अन्यथा अगर (config->lock && config->unlock) अणु
		map->lock = config->lock;
		map->unlock = config->unlock;
		map->lock_arg = config->lock_arg;
		map->can_sleep = config->can_sleep;
	पूर्ण अन्यथा अगर (config->use_hwlock) अणु
		map->hwlock = hwspin_lock_request_specअगरic(config->hwlock_id);
		अगर (!map->hwlock) अणु
			ret = -ENXIO;
			जाओ err_name;
		पूर्ण

		चयन (config->hwlock_mode) अणु
		हाल HWLOCK_IRQSTATE:
			map->lock = regmap_lock_hwlock_irqsave;
			map->unlock = regmap_unlock_hwlock_irqrestore;
			अवरोध;
		हाल HWLOCK_IRQ:
			map->lock = regmap_lock_hwlock_irq;
			map->unlock = regmap_unlock_hwlock_irq;
			अवरोध;
		शेष:
			map->lock = regmap_lock_hwlock;
			map->unlock = regmap_unlock_hwlock;
			अवरोध;
		पूर्ण

		map->lock_arg = map;
	पूर्ण अन्यथा अणु
		अगर ((bus && bus->fast_io) ||
		    config->fast_io) अणु
			spin_lock_init(&map->spinlock);
			map->lock = regmap_lock_spinlock;
			map->unlock = regmap_unlock_spinlock;
			lockdep_set_class_and_name(&map->spinlock,
						   lock_key, lock_name);
		पूर्ण अन्यथा अणु
			mutex_init(&map->mutex);
			map->lock = regmap_lock_mutex;
			map->unlock = regmap_unlock_mutex;
			map->can_sleep = true;
			lockdep_set_class_and_name(&map->mutex,
						   lock_key, lock_name);
		पूर्ण
		map->lock_arg = map;
	पूर्ण

	/*
	 * When we ग_लिखो in fast-paths with regmap_bulk_ग_लिखो() करोn't allocate
	 * scratch buffers with sleeping allocations.
	 */
	अगर ((bus && bus->fast_io) || config->fast_io)
		map->alloc_flags = GFP_ATOMIC;
	अन्यथा
		map->alloc_flags = GFP_KERNEL;

	map->क्रमmat.reg_bytes = DIV_ROUND_UP(config->reg_bits, 8);
	map->क्रमmat.pad_bytes = config->pad_bits / 8;
	map->क्रमmat.val_bytes = DIV_ROUND_UP(config->val_bits, 8);
	map->क्रमmat.buf_size = DIV_ROUND_UP(config->reg_bits +
			config->val_bits + config->pad_bits, 8);
	map->reg_shअगरt = config->pad_bits % 8;
	अगर (config->reg_stride)
		map->reg_stride = config->reg_stride;
	अन्यथा
		map->reg_stride = 1;
	अगर (is_घातer_of_2(map->reg_stride))
		map->reg_stride_order = ilog2(map->reg_stride);
	अन्यथा
		map->reg_stride_order = -1;
	map->use_single_पढ़ो = config->use_single_पढ़ो || !bus || !bus->पढ़ो;
	map->use_single_ग_लिखो = config->use_single_ग_लिखो || !bus || !bus->ग_लिखो;
	map->can_multi_ग_लिखो = config->can_multi_ग_लिखो && bus && bus->ग_लिखो;
	अगर (bus) अणु
		map->max_raw_पढ़ो = bus->max_raw_पढ़ो;
		map->max_raw_ग_लिखो = bus->max_raw_ग_लिखो;
	पूर्ण
	map->dev = dev;
	map->bus = bus;
	map->bus_context = bus_context;
	map->max_रेजिस्टर = config->max_रेजिस्टर;
	map->wr_table = config->wr_table;
	map->rd_table = config->rd_table;
	map->अस्थिर_table = config->अस्थिर_table;
	map->precious_table = config->precious_table;
	map->wr_noinc_table = config->wr_noinc_table;
	map->rd_noinc_table = config->rd_noinc_table;
	map->ग_लिखोable_reg = config->ग_लिखोable_reg;
	map->पढ़ोable_reg = config->पढ़ोable_reg;
	map->अस्थिर_reg = config->अस्थिर_reg;
	map->precious_reg = config->precious_reg;
	map->ग_लिखोable_noinc_reg = config->ग_लिखोable_noinc_reg;
	map->पढ़ोable_noinc_reg = config->पढ़ोable_noinc_reg;
	map->cache_type = config->cache_type;

	spin_lock_init(&map->async_lock);
	INIT_LIST_HEAD(&map->async_list);
	INIT_LIST_HEAD(&map->async_मुक्त);
	init_रुकोqueue_head(&map->async_रुकोq);

	अगर (config->पढ़ो_flag_mask ||
	    config->ग_लिखो_flag_mask ||
	    config->zero_flag_mask) अणु
		map->पढ़ो_flag_mask = config->पढ़ो_flag_mask;
		map->ग_लिखो_flag_mask = config->ग_लिखो_flag_mask;
	पूर्ण अन्यथा अगर (bus) अणु
		map->पढ़ो_flag_mask = bus->पढ़ो_flag_mask;
	पूर्ण

	अगर (!bus) अणु
		map->reg_पढ़ो  = config->reg_पढ़ो;
		map->reg_ग_लिखो = config->reg_ग_लिखो;

		map->defer_caching = false;
		जाओ skip_क्रमmat_initialization;
	पूर्ण अन्यथा अगर (!bus->पढ़ो || !bus->ग_लिखो) अणु
		map->reg_पढ़ो = _regmap_bus_reg_पढ़ो;
		map->reg_ग_लिखो = _regmap_bus_reg_ग_लिखो;
		map->reg_update_bits = bus->reg_update_bits;

		map->defer_caching = false;
		जाओ skip_क्रमmat_initialization;
	पूर्ण अन्यथा अणु
		map->reg_पढ़ो  = _regmap_bus_पढ़ो;
		map->reg_update_bits = bus->reg_update_bits;
	पूर्ण

	reg_endian = regmap_get_reg_endian(bus, config);
	val_endian = regmap_get_val_endian(dev, bus, config);

	चयन (config->reg_bits + map->reg_shअगरt) अणु
	हाल 2:
		चयन (config->val_bits) अणु
		हाल 6:
			map->क्रमmat.क्रमmat_ग_लिखो = regmap_क्रमmat_2_6_ग_लिखो;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;

	हाल 4:
		चयन (config->val_bits) अणु
		हाल 12:
			map->क्रमmat.क्रमmat_ग_लिखो = regmap_क्रमmat_4_12_ग_लिखो;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;

	हाल 7:
		चयन (config->val_bits) अणु
		हाल 9:
			map->क्रमmat.क्रमmat_ग_लिखो = regmap_क्रमmat_7_9_ग_लिखो;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;

	हाल 10:
		चयन (config->val_bits) अणु
		हाल 14:
			map->क्रमmat.क्रमmat_ग_लिखो = regmap_क्रमmat_10_14_ग_लिखो;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;

	हाल 12:
		चयन (config->val_bits) अणु
		हाल 20:
			map->क्रमmat.क्रमmat_ग_लिखो = regmap_क्रमmat_12_20_ग_लिखो;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;

	हाल 8:
		map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_8;
		अवरोध;

	हाल 16:
		चयन (reg_endian) अणु
		हाल REGMAP_ENDIAN_BIG:
			map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_16_be;
			अवरोध;
		हाल REGMAP_ENDIAN_LITTLE:
			map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_16_le;
			अवरोध;
		हाल REGMAP_ENDIAN_NATIVE:
			map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_16_native;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;

	हाल 24:
		अगर (reg_endian != REGMAP_ENDIAN_BIG)
			जाओ err_hwlock;
		map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_24;
		अवरोध;

	हाल 32:
		चयन (reg_endian) अणु
		हाल REGMAP_ENDIAN_BIG:
			map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_32_be;
			अवरोध;
		हाल REGMAP_ENDIAN_LITTLE:
			map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_32_le;
			अवरोध;
		हाल REGMAP_ENDIAN_NATIVE:
			map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_32_native;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;

#अगर_घोषित CONFIG_64BIT
	हाल 64:
		चयन (reg_endian) अणु
		हाल REGMAP_ENDIAN_BIG:
			map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_64_be;
			अवरोध;
		हाल REGMAP_ENDIAN_LITTLE:
			map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_64_le;
			अवरोध;
		हाल REGMAP_ENDIAN_NATIVE:
			map->क्रमmat.क्रमmat_reg = regmap_क्रमmat_64_native;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;
#पूर्ण_अगर

	शेष:
		जाओ err_hwlock;
	पूर्ण

	अगर (val_endian == REGMAP_ENDIAN_NATIVE)
		map->क्रमmat.parse_inplace = regmap_parse_inplace_noop;

	चयन (config->val_bits) अणु
	हाल 8:
		map->क्रमmat.क्रमmat_val = regmap_क्रमmat_8;
		map->क्रमmat.parse_val = regmap_parse_8;
		map->क्रमmat.parse_inplace = regmap_parse_inplace_noop;
		अवरोध;
	हाल 16:
		चयन (val_endian) अणु
		हाल REGMAP_ENDIAN_BIG:
			map->क्रमmat.क्रमmat_val = regmap_क्रमmat_16_be;
			map->क्रमmat.parse_val = regmap_parse_16_be;
			map->क्रमmat.parse_inplace = regmap_parse_16_be_inplace;
			अवरोध;
		हाल REGMAP_ENDIAN_LITTLE:
			map->क्रमmat.क्रमmat_val = regmap_क्रमmat_16_le;
			map->क्रमmat.parse_val = regmap_parse_16_le;
			map->क्रमmat.parse_inplace = regmap_parse_16_le_inplace;
			अवरोध;
		हाल REGMAP_ENDIAN_NATIVE:
			map->क्रमmat.क्रमmat_val = regmap_क्रमmat_16_native;
			map->क्रमmat.parse_val = regmap_parse_16_native;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;
	हाल 24:
		अगर (val_endian != REGMAP_ENDIAN_BIG)
			जाओ err_hwlock;
		map->क्रमmat.क्रमmat_val = regmap_क्रमmat_24;
		map->क्रमmat.parse_val = regmap_parse_24;
		अवरोध;
	हाल 32:
		चयन (val_endian) अणु
		हाल REGMAP_ENDIAN_BIG:
			map->क्रमmat.क्रमmat_val = regmap_क्रमmat_32_be;
			map->क्रमmat.parse_val = regmap_parse_32_be;
			map->क्रमmat.parse_inplace = regmap_parse_32_be_inplace;
			अवरोध;
		हाल REGMAP_ENDIAN_LITTLE:
			map->क्रमmat.क्रमmat_val = regmap_क्रमmat_32_le;
			map->क्रमmat.parse_val = regmap_parse_32_le;
			map->क्रमmat.parse_inplace = regmap_parse_32_le_inplace;
			अवरोध;
		हाल REGMAP_ENDIAN_NATIVE:
			map->क्रमmat.क्रमmat_val = regmap_क्रमmat_32_native;
			map->क्रमmat.parse_val = regmap_parse_32_native;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;
#अगर_घोषित CONFIG_64BIT
	हाल 64:
		चयन (val_endian) अणु
		हाल REGMAP_ENDIAN_BIG:
			map->क्रमmat.क्रमmat_val = regmap_क्रमmat_64_be;
			map->क्रमmat.parse_val = regmap_parse_64_be;
			map->क्रमmat.parse_inplace = regmap_parse_64_be_inplace;
			अवरोध;
		हाल REGMAP_ENDIAN_LITTLE:
			map->क्रमmat.क्रमmat_val = regmap_क्रमmat_64_le;
			map->क्रमmat.parse_val = regmap_parse_64_le;
			map->क्रमmat.parse_inplace = regmap_parse_64_le_inplace;
			अवरोध;
		हाल REGMAP_ENDIAN_NATIVE:
			map->क्रमmat.क्रमmat_val = regmap_क्रमmat_64_native;
			map->क्रमmat.parse_val = regmap_parse_64_native;
			अवरोध;
		शेष:
			जाओ err_hwlock;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	अगर (map->क्रमmat.क्रमmat_ग_लिखो) अणु
		अगर ((reg_endian != REGMAP_ENDIAN_BIG) ||
		    (val_endian != REGMAP_ENDIAN_BIG))
			जाओ err_hwlock;
		map->use_single_ग_लिखो = true;
	पूर्ण

	अगर (!map->क्रमmat.क्रमmat_ग_लिखो &&
	    !(map->क्रमmat.क्रमmat_reg && map->क्रमmat.क्रमmat_val))
		जाओ err_hwlock;

	map->work_buf = kzalloc(map->क्रमmat.buf_size, GFP_KERNEL);
	अगर (map->work_buf == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_hwlock;
	पूर्ण

	अगर (map->क्रमmat.क्रमmat_ग_लिखो) अणु
		map->defer_caching = false;
		map->reg_ग_लिखो = _regmap_bus_क्रमmatted_ग_लिखो;
	पूर्ण अन्यथा अगर (map->क्रमmat.क्रमmat_val) अणु
		map->defer_caching = true;
		map->reg_ग_लिखो = _regmap_bus_raw_ग_लिखो;
	पूर्ण

skip_क्रमmat_initialization:

	map->range_tree = RB_ROOT;
	क्रम (i = 0; i < config->num_ranges; i++) अणु
		स्थिर काष्ठा regmap_range_cfg *range_cfg = &config->ranges[i];
		काष्ठा regmap_range_node *new;

		/* Sanity check */
		अगर (range_cfg->range_max < range_cfg->range_min) अणु
			dev_err(map->dev, "Invalid range %d: %d < %d\n", i,
				range_cfg->range_max, range_cfg->range_min);
			जाओ err_range;
		पूर्ण

		अगर (range_cfg->range_max > map->max_रेजिस्टर) अणु
			dev_err(map->dev, "Invalid range %d: %d > %d\n", i,
				range_cfg->range_max, map->max_रेजिस्टर);
			जाओ err_range;
		पूर्ण

		अगर (range_cfg->selector_reg > map->max_रेजिस्टर) अणु
			dev_err(map->dev,
				"Invalid range %d: selector out of map\n", i);
			जाओ err_range;
		पूर्ण

		अगर (range_cfg->winकरोw_len == 0) अणु
			dev_err(map->dev, "Invalid range %d: window_len 0\n",
				i);
			जाओ err_range;
		पूर्ण

		/* Make sure, that this रेजिस्टर range has no selector
		   or data winकरोw within its boundary */
		क्रम (j = 0; j < config->num_ranges; j++) अणु
			अचिन्हित sel_reg = config->ranges[j].selector_reg;
			अचिन्हित win_min = config->ranges[j].winकरोw_start;
			अचिन्हित win_max = win_min +
					   config->ranges[j].winकरोw_len - 1;

			/* Allow data winकरोw inside its own भव range */
			अगर (j == i)
				जारी;

			अगर (range_cfg->range_min <= sel_reg &&
			    sel_reg <= range_cfg->range_max) अणु
				dev_err(map->dev,
					"Range %d: selector for %d in window\n",
					i, j);
				जाओ err_range;
			पूर्ण

			अगर (!(win_max < range_cfg->range_min ||
			      win_min > range_cfg->range_max)) अणु
				dev_err(map->dev,
					"Range %d: window for %d in window\n",
					i, j);
				जाओ err_range;
			पूर्ण
		पूर्ण

		new = kzalloc(माप(*new), GFP_KERNEL);
		अगर (new == शून्य) अणु
			ret = -ENOMEM;
			जाओ err_range;
		पूर्ण

		new->map = map;
		new->name = range_cfg->name;
		new->range_min = range_cfg->range_min;
		new->range_max = range_cfg->range_max;
		new->selector_reg = range_cfg->selector_reg;
		new->selector_mask = range_cfg->selector_mask;
		new->selector_shअगरt = range_cfg->selector_shअगरt;
		new->winकरोw_start = range_cfg->winकरोw_start;
		new->winकरोw_len = range_cfg->winकरोw_len;

		अगर (!_regmap_range_add(map, new)) अणु
			dev_err(map->dev, "Failed to add range %d\n", i);
			kमुक्त(new);
			जाओ err_range;
		पूर्ण

		अगर (map->selector_work_buf == शून्य) अणु
			map->selector_work_buf =
				kzalloc(map->क्रमmat.buf_size, GFP_KERNEL);
			अगर (map->selector_work_buf == शून्य) अणु
				ret = -ENOMEM;
				जाओ err_range;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = regcache_init(map, config);
	अगर (ret != 0)
		जाओ err_range;

	अगर (dev) अणु
		ret = regmap_attach_dev(dev, map, config);
		अगर (ret != 0)
			जाओ err_regcache;
	पूर्ण अन्यथा अणु
		regmap_debugfs_init(map);
	पूर्ण

	वापस map;

err_regcache:
	regcache_निकास(map);
err_range:
	regmap_range_निकास(map);
	kमुक्त(map->work_buf);
err_hwlock:
	अगर (map->hwlock)
		hwspin_lock_मुक्त(map->hwlock);
err_name:
	kमुक्त_स्थिर(map->name);
err_map:
	kमुक्त(map);
err:
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init);

अटल व्योम devm_regmap_release(काष्ठा device *dev, व्योम *res)
अणु
	regmap_निकास(*(काष्ठा regmap **)res);
पूर्ण

काष्ठा regmap *__devm_regmap_init(काष्ठा device *dev,
				  स्थिर काष्ठा regmap_bus *bus,
				  व्योम *bus_context,
				  स्थिर काष्ठा regmap_config *config,
				  काष्ठा lock_class_key *lock_key,
				  स्थिर अक्षर *lock_name)
अणु
	काष्ठा regmap **ptr, *regmap;

	ptr = devres_alloc(devm_regmap_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	regmap = __regmap_init(dev, bus, bus_context, config,
			       lock_key, lock_name);
	अगर (!IS_ERR(regmap)) अणु
		*ptr = regmap;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस regmap;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init);

अटल व्योम regmap_field_init(काष्ठा regmap_field *rm_field,
	काष्ठा regmap *regmap, काष्ठा reg_field reg_field)
अणु
	rm_field->regmap = regmap;
	rm_field->reg = reg_field.reg;
	rm_field->shअगरt = reg_field.lsb;
	rm_field->mask = GENMASK(reg_field.msb, reg_field.lsb);
	rm_field->id_size = reg_field.id_size;
	rm_field->id_offset = reg_field.id_offset;
पूर्ण

/**
 * devm_regmap_field_alloc() - Allocate and initialise a रेजिस्टर field.
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @regmap: regmap bank in which this रेजिस्टर field is located.
 * @reg_field: Register field with in the bank.
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap_field. The regmap_field will be स्वतःmatically मुक्तd
 * by the device management code.
 */
काष्ठा regmap_field *devm_regmap_field_alloc(काष्ठा device *dev,
		काष्ठा regmap *regmap, काष्ठा reg_field reg_field)
अणु
	काष्ठा regmap_field *rm_field = devm_kzalloc(dev,
					माप(*rm_field), GFP_KERNEL);
	अगर (!rm_field)
		वापस ERR_PTR(-ENOMEM);

	regmap_field_init(rm_field, regmap, reg_field);

	वापस rm_field;

पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_field_alloc);


/**
 * regmap_field_bulk_alloc() - Allocate and initialise a bulk रेजिस्टर field.
 *
 * @regmap: regmap bank in which this रेजिस्टर field is located.
 * @rm_field: regmap रेजिस्टर fields within the bank.
 * @reg_field: Register fields within the bank.
 * @num_fields: Number of रेजिस्टर fields.
 *
 * The वापस value will be an -ENOMEM on error or zero क्रम success.
 * Newly allocated regmap_fields should be मुक्तd by calling
 * regmap_field_bulk_मुक्त()
 */
पूर्णांक regmap_field_bulk_alloc(काष्ठा regmap *regmap,
			    काष्ठा regmap_field **rm_field,
			    काष्ठा reg_field *reg_field,
			    पूर्णांक num_fields)
अणु
	काष्ठा regmap_field *rf;
	पूर्णांक i;

	rf = kसुस्मृति(num_fields, माप(*rf), GFP_KERNEL);
	अगर (!rf)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_fields; i++) अणु
		regmap_field_init(&rf[i], regmap, reg_field[i]);
		rm_field[i] = &rf[i];
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_field_bulk_alloc);

/**
 * devm_regmap_field_bulk_alloc() - Allocate and initialise a bulk रेजिस्टर
 * fields.
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @regmap: regmap bank in which this रेजिस्टर field is located.
 * @rm_field: regmap रेजिस्टर fields within the bank.
 * @reg_field: Register fields within the bank.
 * @num_fields: Number of रेजिस्टर fields.
 *
 * The वापस value will be an -ENOMEM on error or zero क्रम success.
 * Newly allocated regmap_fields will be स्वतःmatically मुक्तd by the
 * device management code.
 */
पूर्णांक devm_regmap_field_bulk_alloc(काष्ठा device *dev,
				 काष्ठा regmap *regmap,
				 काष्ठा regmap_field **rm_field,
				 काष्ठा reg_field *reg_field,
				 पूर्णांक num_fields)
अणु
	काष्ठा regmap_field *rf;
	पूर्णांक i;

	rf = devm_kसुस्मृति(dev, num_fields, माप(*rf), GFP_KERNEL);
	अगर (!rf)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_fields; i++) अणु
		regmap_field_init(&rf[i], regmap, reg_field[i]);
		rm_field[i] = &rf[i];
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_field_bulk_alloc);

/**
 * regmap_field_bulk_मुक्त() - Free रेजिस्टर field allocated using
 *                       regmap_field_bulk_alloc.
 *
 * @field: regmap fields which should be मुक्तd.
 */
व्योम regmap_field_bulk_मुक्त(काष्ठा regmap_field *field)
अणु
	kमुक्त(field);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_field_bulk_मुक्त);

/**
 * devm_regmap_field_bulk_मुक्त() - Free a bulk रेजिस्टर field allocated using
 *                            devm_regmap_field_bulk_alloc.
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @field: regmap field which should be मुक्तd.
 *
 * Free रेजिस्टर field allocated using devm_regmap_field_bulk_alloc(). Usually
 * drivers need not call this function, as the memory allocated via devm
 * will be मुक्तd as per device-driver lअगरe-cycle.
 */
व्योम devm_regmap_field_bulk_मुक्त(काष्ठा device *dev,
				 काष्ठा regmap_field *field)
अणु
	devm_kमुक्त(dev, field);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_field_bulk_मुक्त);

/**
 * devm_regmap_field_मुक्त() - Free a रेजिस्टर field allocated using
 *                            devm_regmap_field_alloc.
 *
 * @dev: Device that will be पूर्णांकeracted with
 * @field: regmap field which should be मुक्तd.
 *
 * Free रेजिस्टर field allocated using devm_regmap_field_alloc(). Usually
 * drivers need not call this function, as the memory allocated via devm
 * will be मुक्तd as per device-driver lअगरe-cyle.
 */
व्योम devm_regmap_field_मुक्त(काष्ठा device *dev,
	काष्ठा regmap_field *field)
अणु
	devm_kमुक्त(dev, field);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_field_मुक्त);

/**
 * regmap_field_alloc() - Allocate and initialise a रेजिस्टर field.
 *
 * @regmap: regmap bank in which this रेजिस्टर field is located.
 * @reg_field: Register field with in the bank.
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap_field. The regmap_field should be मुक्तd by the
 * user once its finished working with it using regmap_field_मुक्त().
 */
काष्ठा regmap_field *regmap_field_alloc(काष्ठा regmap *regmap,
		काष्ठा reg_field reg_field)
अणु
	काष्ठा regmap_field *rm_field = kzalloc(माप(*rm_field), GFP_KERNEL);

	अगर (!rm_field)
		वापस ERR_PTR(-ENOMEM);

	regmap_field_init(rm_field, regmap, reg_field);

	वापस rm_field;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_field_alloc);

/**
 * regmap_field_मुक्त() - Free रेजिस्टर field allocated using
 *                       regmap_field_alloc.
 *
 * @field: regmap field which should be मुक्तd.
 */
व्योम regmap_field_मुक्त(काष्ठा regmap_field *field)
अणु
	kमुक्त(field);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_field_मुक्त);

/**
 * regmap_reinit_cache() - Reinitialise the current रेजिस्टर cache
 *
 * @map: Register map to operate on.
 * @config: New configuration.  Only the cache data will be used.
 *
 * Discard any existing रेजिस्टर cache क्रम the map and initialize a
 * new cache.  This can be used to restore the cache to शेषs or to
 * update the cache configuration to reflect runसमय discovery of the
 * hardware.
 *
 * No explicit locking is करोne here, the user needs to ensure that
 * this function will not race with other calls to regmap.
 */
पूर्णांक regmap_reinit_cache(काष्ठा regmap *map, स्थिर काष्ठा regmap_config *config)
अणु
	पूर्णांक ret;

	regcache_निकास(map);
	regmap_debugfs_निकास(map);

	map->max_रेजिस्टर = config->max_रेजिस्टर;
	map->ग_लिखोable_reg = config->ग_लिखोable_reg;
	map->पढ़ोable_reg = config->पढ़ोable_reg;
	map->अस्थिर_reg = config->अस्थिर_reg;
	map->precious_reg = config->precious_reg;
	map->ग_लिखोable_noinc_reg = config->ग_लिखोable_noinc_reg;
	map->पढ़ोable_noinc_reg = config->पढ़ोable_noinc_reg;
	map->cache_type = config->cache_type;

	ret = regmap_set_name(map, config);
	अगर (ret)
		वापस ret;

	regmap_debugfs_init(map);

	map->cache_bypass = false;
	map->cache_only = false;

	वापस regcache_init(map, config);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_reinit_cache);

/**
 * regmap_निकास() - Free a previously allocated रेजिस्टर map
 *
 * @map: Register map to operate on.
 */
व्योम regmap_निकास(काष्ठा regmap *map)
अणु
	काष्ठा regmap_async *async;

	regcache_निकास(map);
	regmap_debugfs_निकास(map);
	regmap_range_निकास(map);
	अगर (map->bus && map->bus->मुक्त_context)
		map->bus->मुक्त_context(map->bus_context);
	kमुक्त(map->work_buf);
	जबतक (!list_empty(&map->async_मुक्त)) अणु
		async = list_first_entry_or_null(&map->async_मुक्त,
						 काष्ठा regmap_async,
						 list);
		list_del(&async->list);
		kमुक्त(async->work_buf);
		kमुक्त(async);
	पूर्ण
	अगर (map->hwlock)
		hwspin_lock_मुक्त(map->hwlock);
	अगर (map->lock == regmap_lock_mutex)
		mutex_destroy(&map->mutex);
	kमुक्त_स्थिर(map->name);
	kमुक्त(map->patch);
	kमुक्त(map);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_निकास);

अटल पूर्णांक dev_get_regmap_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा regmap **r = res;
	अगर (!r || !*r) अणु
		WARN_ON(!r || !*r);
		वापस 0;
	पूर्ण

	/* If the user didn't specअगरy a name match any */
	अगर (data)
		वापस !म_भेद((*r)->name, data);
	अन्यथा
		वापस 1;
पूर्ण

/**
 * dev_get_regmap() - Obtain the regmap (अगर any) क्रम a device
 *
 * @dev: Device to retrieve the map क्रम
 * @name: Optional name क्रम the रेजिस्टर map, usually शून्य.
 *
 * Returns the regmap क्रम the device अगर one is present, or शून्य.  If
 * name is specअगरied then it must match the name specअगरied when
 * रेजिस्टरing the device, अगर it is शून्य then the first regmap found
 * will be used.  Devices with multiple रेजिस्टर maps are very rare,
 * generic code should normally not need to specअगरy a name.
 */
काष्ठा regmap *dev_get_regmap(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा regmap **r = devres_find(dev, dev_get_regmap_release,
					dev_get_regmap_match, (व्योम *)name);

	अगर (!r)
		वापस शून्य;
	वापस *r;
पूर्ण
EXPORT_SYMBOL_GPL(dev_get_regmap);

/**
 * regmap_get_device() - Obtain the device from a regmap
 *
 * @map: Register map to operate on.
 *
 * Returns the underlying device that the regmap has been created क्रम.
 */
काष्ठा device *regmap_get_device(काष्ठा regmap *map)
अणु
	वापस map->dev;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_get_device);

अटल पूर्णांक _regmap_select_page(काष्ठा regmap *map, अचिन्हित पूर्णांक *reg,
			       काष्ठा regmap_range_node *range,
			       अचिन्हित पूर्णांक val_num)
अणु
	व्योम *orig_work_buf;
	अचिन्हित पूर्णांक win_offset;
	अचिन्हित पूर्णांक win_page;
	bool page_chg;
	पूर्णांक ret;

	win_offset = (*reg - range->range_min) % range->winकरोw_len;
	win_page = (*reg - range->range_min) / range->winकरोw_len;

	अगर (val_num > 1) अणु
		/* Bulk ग_लिखो shouldn't cross range boundary */
		अगर (*reg + val_num - 1 > range->range_max)
			वापस -EINVAL;

		/* ... or single page boundary */
		अगर (val_num > range->winकरोw_len - win_offset)
			वापस -EINVAL;
	पूर्ण

	/* It is possible to have selector रेजिस्टर inside data winकरोw.
	   In that हाल, selector रेजिस्टर is located on every page and
	   it needs no page चयनing, when accessed alone. */
	अगर (val_num > 1 ||
	    range->winकरोw_start + win_offset != range->selector_reg) अणु
		/* Use separate work_buf during page चयनing */
		orig_work_buf = map->work_buf;
		map->work_buf = map->selector_work_buf;

		ret = _regmap_update_bits(map, range->selector_reg,
					  range->selector_mask,
					  win_page << range->selector_shअगरt,
					  &page_chg, false);

		map->work_buf = orig_work_buf;

		अगर (ret != 0)
			वापस ret;
	पूर्ण

	*reg = range->winकरोw_start + win_offset;

	वापस 0;
पूर्ण

अटल व्योम regmap_set_work_buf_flag_mask(काष्ठा regmap *map, पूर्णांक max_bytes,
					  अचिन्हित दीर्घ mask)
अणु
	u8 *buf;
	पूर्णांक i;

	अगर (!mask || !map->work_buf)
		वापस;

	buf = map->work_buf;

	क्रम (i = 0; i < max_bytes; i++)
		buf[i] |= (mask >> (8 * i)) & 0xff;
पूर्ण

अटल पूर्णांक _regmap_raw_ग_लिखो_impl(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				  स्थिर व्योम *val, माप_प्रकार val_len, bool noinc)
अणु
	काष्ठा regmap_range_node *range;
	अचिन्हित दीर्घ flags;
	व्योम *work_val = map->work_buf + map->क्रमmat.reg_bytes +
		map->क्रमmat.pad_bytes;
	व्योम *buf;
	पूर्णांक ret = -ENOTSUPP;
	माप_प्रकार len;
	पूर्णांक i;

	WARN_ON(!map->bus);

	/* Check क्रम unwritable or noinc रेजिस्टरs in range
	 * beक्रमe we start
	 */
	अगर (!regmap_ग_लिखोable_noinc(map, reg)) अणु
		क्रम (i = 0; i < val_len / map->क्रमmat.val_bytes; i++) अणु
			अचिन्हित पूर्णांक element =
				reg + regmap_get_offset(map, i);
			अगर (!regmap_ग_लिखोable(map, element) ||
				regmap_ग_लिखोable_noinc(map, element))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!map->cache_bypass && map->क्रमmat.parse_val) अणु
		अचिन्हित पूर्णांक ival;
		पूर्णांक val_bytes = map->क्रमmat.val_bytes;
		क्रम (i = 0; i < val_len / val_bytes; i++) अणु
			ival = map->क्रमmat.parse_val(val + (i * val_bytes));
			ret = regcache_ग_लिखो(map,
					     reg + regmap_get_offset(map, i),
					     ival);
			अगर (ret) अणु
				dev_err(map->dev,
					"Error in caching of register: %x ret: %d\n",
					reg + i, ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (map->cache_only) अणु
			map->cache_dirty = true;
			वापस 0;
		पूर्ण
	पूर्ण

	range = _regmap_range_lookup(map, reg);
	अगर (range) अणु
		पूर्णांक val_num = val_len / map->क्रमmat.val_bytes;
		पूर्णांक win_offset = (reg - range->range_min) % range->winकरोw_len;
		पूर्णांक win_residue = range->winकरोw_len - win_offset;

		/* If the ग_लिखो goes beyond the end of the winकरोw split it */
		जबतक (val_num > win_residue) अणु
			dev_dbg(map->dev, "Writing window %d/%zu\n",
				win_residue, val_len / map->क्रमmat.val_bytes);
			ret = _regmap_raw_ग_लिखो_impl(map, reg, val,
						     win_residue *
						     map->क्रमmat.val_bytes, noinc);
			अगर (ret != 0)
				वापस ret;

			reg += win_residue;
			val_num -= win_residue;
			val += win_residue * map->क्रमmat.val_bytes;
			val_len -= win_residue * map->क्रमmat.val_bytes;

			win_offset = (reg - range->range_min) %
				range->winकरोw_len;
			win_residue = range->winकरोw_len - win_offset;
		पूर्ण

		ret = _regmap_select_page(map, &reg, range, noinc ? 1 : val_num);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	map->क्रमmat.क्रमmat_reg(map->work_buf, reg, map->reg_shअगरt);
	regmap_set_work_buf_flag_mask(map, map->क्रमmat.reg_bytes,
				      map->ग_लिखो_flag_mask);

	/*
	 * Essentially all I/O mechanisms will be faster with a single
	 * buffer to ग_लिखो.  Since रेजिस्टर syncs often generate raw
	 * ग_लिखोs of single रेजिस्टरs optimise that हाल.
	 */
	अगर (val != work_val && val_len == map->क्रमmat.val_bytes) अणु
		स_नकल(work_val, val, map->क्रमmat.val_bytes);
		val = work_val;
	पूर्ण

	अगर (map->async && map->bus->async_ग_लिखो) अणु
		काष्ठा regmap_async *async;

		trace_regmap_async_ग_लिखो_start(map, reg, val_len);

		spin_lock_irqsave(&map->async_lock, flags);
		async = list_first_entry_or_null(&map->async_मुक्त,
						 काष्ठा regmap_async,
						 list);
		अगर (async)
			list_del(&async->list);
		spin_unlock_irqrestore(&map->async_lock, flags);

		अगर (!async) अणु
			async = map->bus->async_alloc();
			अगर (!async)
				वापस -ENOMEM;

			async->work_buf = kzalloc(map->क्रमmat.buf_size,
						  GFP_KERNEL | GFP_DMA);
			अगर (!async->work_buf) अणु
				kमुक्त(async);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		async->map = map;

		/* If the caller supplied the value we can use it safely. */
		स_नकल(async->work_buf, map->work_buf, map->क्रमmat.pad_bytes +
		       map->क्रमmat.reg_bytes + map->क्रमmat.val_bytes);

		spin_lock_irqsave(&map->async_lock, flags);
		list_add_tail(&async->list, &map->async_list);
		spin_unlock_irqrestore(&map->async_lock, flags);

		अगर (val != work_val)
			ret = map->bus->async_ग_लिखो(map->bus_context,
						    async->work_buf,
						    map->क्रमmat.reg_bytes +
						    map->क्रमmat.pad_bytes,
						    val, val_len, async);
		अन्यथा
			ret = map->bus->async_ग_लिखो(map->bus_context,
						    async->work_buf,
						    map->क्रमmat.reg_bytes +
						    map->क्रमmat.pad_bytes +
						    val_len, शून्य, 0, async);

		अगर (ret != 0) अणु
			dev_err(map->dev, "Failed to schedule write: %d\n",
				ret);

			spin_lock_irqsave(&map->async_lock, flags);
			list_move(&async->list, &map->async_मुक्त);
			spin_unlock_irqrestore(&map->async_lock, flags);
		पूर्ण

		वापस ret;
	पूर्ण

	trace_regmap_hw_ग_लिखो_start(map, reg, val_len / map->क्रमmat.val_bytes);

	/* If we're करोing a single रेजिस्टर ग_लिखो we can probably just
	 * send the work_buf directly, otherwise try to करो a gather
	 * ग_लिखो.
	 */
	अगर (val == work_val)
		ret = map->bus->ग_लिखो(map->bus_context, map->work_buf,
				      map->क्रमmat.reg_bytes +
				      map->क्रमmat.pad_bytes +
				      val_len);
	अन्यथा अगर (map->bus->gather_ग_लिखो)
		ret = map->bus->gather_ग_लिखो(map->bus_context, map->work_buf,
					     map->क्रमmat.reg_bytes +
					     map->क्रमmat.pad_bytes,
					     val, val_len);
	अन्यथा
		ret = -ENOTSUPP;

	/* If that didn't work fall back on linearising by hand. */
	अगर (ret == -ENOTSUPP) अणु
		len = map->क्रमmat.reg_bytes + map->क्रमmat.pad_bytes + val_len;
		buf = kzalloc(len, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		स_नकल(buf, map->work_buf, map->क्रमmat.reg_bytes);
		स_नकल(buf + map->क्रमmat.reg_bytes + map->क्रमmat.pad_bytes,
		       val, val_len);
		ret = map->bus->ग_लिखो(map->bus_context, buf, len);

		kमुक्त(buf);
	पूर्ण अन्यथा अगर (ret != 0 && !map->cache_bypass && map->क्रमmat.parse_val) अणु
		/* regcache_drop_region() takes lock that we alपढ़ोy have,
		 * thus call map->cache_ops->drop() directly
		 */
		अगर (map->cache_ops && map->cache_ops->drop)
			map->cache_ops->drop(map, reg, reg + 1);
	पूर्ण

	trace_regmap_hw_ग_लिखो_करोne(map, reg, val_len / map->क्रमmat.val_bytes);

	वापस ret;
पूर्ण

/**
 * regmap_can_raw_ग_लिखो - Test अगर regmap_raw_ग_लिखो() is supported
 *
 * @map: Map to check.
 */
bool regmap_can_raw_ग_लिखो(काष्ठा regmap *map)
अणु
	वापस map->bus && map->bus->ग_लिखो && map->क्रमmat.क्रमmat_val &&
		map->क्रमmat.क्रमmat_reg;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_can_raw_ग_लिखो);

/**
 * regmap_get_raw_पढ़ो_max - Get the maximum size we can पढ़ो
 *
 * @map: Map to check.
 */
माप_प्रकार regmap_get_raw_पढ़ो_max(काष्ठा regmap *map)
अणु
	वापस map->max_raw_पढ़ो;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_get_raw_पढ़ो_max);

/**
 * regmap_get_raw_ग_लिखो_max - Get the maximum size we can पढ़ो
 *
 * @map: Map to check.
 */
माप_प्रकार regmap_get_raw_ग_लिखो_max(काष्ठा regmap *map)
अणु
	वापस map->max_raw_ग_लिखो;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_get_raw_ग_लिखो_max);

अटल पूर्णांक _regmap_bus_क्रमmatted_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				       अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;
	काष्ठा regmap_range_node *range;
	काष्ठा regmap *map = context;

	WARN_ON(!map->bus || !map->क्रमmat.क्रमmat_ग_लिखो);

	range = _regmap_range_lookup(map, reg);
	अगर (range) अणु
		ret = _regmap_select_page(map, &reg, range, 1);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	map->क्रमmat.क्रमmat_ग_लिखो(map, reg, val);

	trace_regmap_hw_ग_लिखो_start(map, reg, 1);

	ret = map->bus->ग_लिखो(map->bus_context, map->work_buf,
			      map->क्रमmat.buf_size);

	trace_regmap_hw_ग_लिखो_करोne(map, reg, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक _regmap_bus_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक val)
अणु
	काष्ठा regmap *map = context;

	वापस map->bus->reg_ग_लिखो(map->bus_context, reg, val);
पूर्ण

अटल पूर्णांक _regmap_bus_raw_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक val)
अणु
	काष्ठा regmap *map = context;

	WARN_ON(!map->bus || !map->क्रमmat.क्रमmat_val);

	map->क्रमmat.क्रमmat_val(map->work_buf + map->क्रमmat.reg_bytes
			       + map->क्रमmat.pad_bytes, val, 0);
	वापस _regmap_raw_ग_लिखो_impl(map, reg,
				      map->work_buf +
				      map->क्रमmat.reg_bytes +
				      map->क्रमmat.pad_bytes,
				      map->क्रमmat.val_bytes,
				      false);
पूर्ण

अटल अंतरभूत व्योम *_regmap_map_get_context(काष्ठा regmap *map)
अणु
	वापस (map->bus) ? map : map->bus_context;
पूर्ण

पूर्णांक _regmap_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		  अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;
	व्योम *context = _regmap_map_get_context(map);

	अगर (!regmap_ग_लिखोable(map, reg))
		वापस -EIO;

	अगर (!map->cache_bypass && !map->defer_caching) अणु
		ret = regcache_ग_लिखो(map, reg, val);
		अगर (ret != 0)
			वापस ret;
		अगर (map->cache_only) अणु
			map->cache_dirty = true;
			वापस 0;
		पूर्ण
	पूर्ण

	ret = map->reg_ग_लिखो(context, reg, val);
	अगर (ret == 0) अणु
		अगर (regmap_should_log(map))
			dev_info(map->dev, "%x <= %x\n", reg, val);

		trace_regmap_reg_ग_लिखो(map, reg, val);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * regmap_ग_लिखो() - Write a value to a single रेजिस्टर
 *
 * @map: Register map to ग_लिखो to
 * @reg: Register to ग_लिखो to
 * @val: Value to be written
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	अगर (!IS_ALIGNED(reg, map->reg_stride))
		वापस -EINVAL;

	map->lock(map->lock_arg);

	ret = _regmap_ग_लिखो(map, reg, val);

	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_ग_लिखो);

/**
 * regmap_ग_लिखो_async() - Write a value to a single रेजिस्टर asynchronously
 *
 * @map: Register map to ग_लिखो to
 * @reg: Register to ग_लिखो to
 * @val: Value to be written
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_ग_लिखो_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	अगर (!IS_ALIGNED(reg, map->reg_stride))
		वापस -EINVAL;

	map->lock(map->lock_arg);

	map->async = true;

	ret = _regmap_ग_लिखो(map, reg, val);

	map->async = false;

	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_ग_लिखो_async);

पूर्णांक _regmap_raw_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		      स्थिर व्योम *val, माप_प्रकार val_len, bool noinc)
अणु
	माप_प्रकार val_bytes = map->क्रमmat.val_bytes;
	माप_प्रकार val_count = val_len / val_bytes;
	माप_प्रकार chunk_count, chunk_bytes;
	माप_प्रकार chunk_regs = val_count;
	पूर्णांक ret, i;

	अगर (!val_count)
		वापस -EINVAL;

	अगर (map->use_single_ग_लिखो)
		chunk_regs = 1;
	अन्यथा अगर (map->max_raw_ग_लिखो && val_len > map->max_raw_ग_लिखो)
		chunk_regs = map->max_raw_ग_लिखो / val_bytes;

	chunk_count = val_count / chunk_regs;
	chunk_bytes = chunk_regs * val_bytes;

	/* Write as many bytes as possible with chunk_size */
	क्रम (i = 0; i < chunk_count; i++) अणु
		ret = _regmap_raw_ग_लिखो_impl(map, reg, val, chunk_bytes, noinc);
		अगर (ret)
			वापस ret;

		reg += regmap_get_offset(map, chunk_regs);
		val += chunk_bytes;
		val_len -= chunk_bytes;
	पूर्ण

	/* Write reमुख्यing bytes */
	अगर (val_len)
		ret = _regmap_raw_ग_लिखो_impl(map, reg, val, val_len, noinc);

	वापस ret;
पूर्ण

/**
 * regmap_raw_ग_लिखो() - Write raw values to one or more रेजिस्टरs
 *
 * @map: Register map to ग_लिखो to
 * @reg: Initial रेजिस्टर to ग_लिखो to
 * @val: Block of data to be written, laid out क्रम direct transmission to the
 *       device
 * @val_len: Length of data poपूर्णांकed to by val.
 *
 * This function is पूर्णांकended to be used क्रम things like firmware
 * करोwnload where a large block of data needs to be transferred to the
 * device.  No क्रमmatting will be करोne on the data provided.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_raw_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		     स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	पूर्णांक ret;

	अगर (!regmap_can_raw_ग_लिखो(map))
		वापस -EINVAL;
	अगर (val_len % map->क्रमmat.val_bytes)
		वापस -EINVAL;

	map->lock(map->lock_arg);

	ret = _regmap_raw_ग_लिखो(map, reg, val, val_len, false);

	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_raw_ग_लिखो);

/**
 * regmap_noinc_ग_लिखो(): Write data from a रेजिस्टर without incrementing the
 *			रेजिस्टर number
 *
 * @map: Register map to ग_लिखो to
 * @reg: Register to ग_लिखो to
 * @val: Poपूर्णांकer to data buffer
 * @val_len: Length of output buffer in bytes.
 *
 * The regmap API usually assumes that bulk bus ग_लिखो operations will ग_लिखो a
 * range of रेजिस्टरs. Some devices have certain रेजिस्टरs क्रम which a ग_लिखो
 * operation can ग_लिखो to an पूर्णांकernal FIFO.
 *
 * The target रेजिस्टर must be अस्थिर but रेजिस्टरs after it can be
 * completely unrelated cacheable रेजिस्टरs.
 *
 * This will attempt multiple ग_लिखोs as required to ग_लिखो val_len bytes.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will be
 * वापसed in error हालs.
 */
पूर्णांक regmap_noinc_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		      स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	माप_प्रकार ग_लिखो_len;
	पूर्णांक ret;

	अगर (!map->bus)
		वापस -EINVAL;
	अगर (!map->bus->ग_लिखो)
		वापस -ENOTSUPP;
	अगर (val_len % map->क्रमmat.val_bytes)
		वापस -EINVAL;
	अगर (!IS_ALIGNED(reg, map->reg_stride))
		वापस -EINVAL;
	अगर (val_len == 0)
		वापस -EINVAL;

	map->lock(map->lock_arg);

	अगर (!regmap_अस्थिर(map, reg) || !regmap_ग_लिखोable_noinc(map, reg)) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	जबतक (val_len) अणु
		अगर (map->max_raw_ग_लिखो && map->max_raw_ग_लिखो < val_len)
			ग_लिखो_len = map->max_raw_ग_लिखो;
		अन्यथा
			ग_लिखो_len = val_len;
		ret = _regmap_raw_ग_लिखो(map, reg, val, ग_लिखो_len, true);
		अगर (ret)
			जाओ out_unlock;
		val = ((u8 *)val) + ग_लिखो_len;
		val_len -= ग_लिखो_len;
	पूर्ण

out_unlock:
	map->unlock(map->lock_arg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_noinc_ग_लिखो);

/**
 * regmap_field_update_bits_base() - Perक्रमm a पढ़ो/modअगरy/ग_लिखो cycle a
 *                                   रेजिस्टर field.
 *
 * @field: Register field to ग_लिखो to
 * @mask: Biपंचांगask to change
 * @val: Value to be written
 * @change: Boolean indicating अगर a ग_लिखो was करोne
 * @async: Boolean indicating asynchronously
 * @क्रमce: Boolean indicating use क्रमce update
 *
 * Perक्रमm a पढ़ो/modअगरy/ग_लिखो cycle on the रेजिस्टर field with change,
 * async, क्रमce option.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_field_update_bits_base(काष्ठा regmap_field *field,
				  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
				  bool *change, bool async, bool क्रमce)
अणु
	mask = (mask << field->shअगरt) & field->mask;

	वापस regmap_update_bits_base(field->regmap, field->reg,
				       mask, val << field->shअगरt,
				       change, async, क्रमce);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_field_update_bits_base);

/**
 * regmap_fields_update_bits_base() - Perक्रमm a पढ़ो/modअगरy/ग_लिखो cycle a
 *                                    रेजिस्टर field with port ID
 *
 * @field: Register field to ग_लिखो to
 * @id: port ID
 * @mask: Biपंचांगask to change
 * @val: Value to be written
 * @change: Boolean indicating अगर a ग_लिखो was करोne
 * @async: Boolean indicating asynchronously
 * @क्रमce: Boolean indicating use क्रमce update
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_fields_update_bits_base(काष्ठा regmap_field *field, अचिन्हित पूर्णांक id,
				   अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
				   bool *change, bool async, bool क्रमce)
अणु
	अगर (id >= field->id_size)
		वापस -EINVAL;

	mask = (mask << field->shअगरt) & field->mask;

	वापस regmap_update_bits_base(field->regmap,
				       field->reg + (field->id_offset * id),
				       mask, val << field->shअगरt,
				       change, async, क्रमce);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_fields_update_bits_base);

/**
 * regmap_bulk_ग_लिखो() - Write multiple रेजिस्टरs to the device
 *
 * @map: Register map to ग_लिखो to
 * @reg: First रेजिस्टर to be ग_लिखो from
 * @val: Block of data to be written, in native रेजिस्टर size क्रम device
 * @val_count: Number of रेजिस्टरs to ग_लिखो
 *
 * This function is पूर्णांकended to be used क्रम writing a large block of
 * data to the device either in single transfer or multiple transfer.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_bulk_ग_लिखो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, स्थिर व्योम *val,
		     माप_प्रकार val_count)
अणु
	पूर्णांक ret = 0, i;
	माप_प्रकार val_bytes = map->क्रमmat.val_bytes;

	अगर (!IS_ALIGNED(reg, map->reg_stride))
		वापस -EINVAL;

	/*
	 * Some devices करोn't support bulk ग_लिखो, क्रम them we have a series of
	 * single ग_लिखो operations.
	 */
	अगर (!map->bus || !map->क्रमmat.parse_inplace) अणु
		map->lock(map->lock_arg);
		क्रम (i = 0; i < val_count; i++) अणु
			अचिन्हित पूर्णांक ival;

			चयन (val_bytes) अणु
			हाल 1:
				ival = *(u8 *)(val + (i * val_bytes));
				अवरोध;
			हाल 2:
				ival = *(u16 *)(val + (i * val_bytes));
				अवरोध;
			हाल 4:
				ival = *(u32 *)(val + (i * val_bytes));
				अवरोध;
#अगर_घोषित CONFIG_64BIT
			हाल 8:
				ival = *(u64 *)(val + (i * val_bytes));
				अवरोध;
#पूर्ण_अगर
			शेष:
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			ret = _regmap_ग_लिखो(map,
					    reg + regmap_get_offset(map, i),
					    ival);
			अगर (ret != 0)
				जाओ out;
		पूर्ण
out:
		map->unlock(map->lock_arg);
	पूर्ण अन्यथा अणु
		व्योम *wval;

		wval = kmemdup(val, val_count * val_bytes, map->alloc_flags);
		अगर (!wval)
			वापस -ENOMEM;

		क्रम (i = 0; i < val_count * val_bytes; i += val_bytes)
			map->क्रमmat.parse_inplace(wval + i);

		ret = regmap_raw_ग_लिखो(map, reg, wval, val_bytes * val_count);

		kमुक्त(wval);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_bulk_ग_लिखो);

/*
 * _regmap_raw_multi_reg_ग_लिखो()
 *
 * the (रेजिस्टर,newvalue) pairs in regs have not been क्रमmatted, but
 * they are all in the same page and have been changed to being page
 * relative. The page रेजिस्टर has been written अगर that was necessary.
 */
अटल पूर्णांक _regmap_raw_multi_reg_ग_लिखो(काष्ठा regmap *map,
				       स्थिर काष्ठा reg_sequence *regs,
				       माप_प्रकार num_regs)
अणु
	पूर्णांक ret;
	व्योम *buf;
	पूर्णांक i;
	u8 *u8;
	माप_प्रकार val_bytes = map->क्रमmat.val_bytes;
	माप_प्रकार reg_bytes = map->क्रमmat.reg_bytes;
	माप_प्रकार pad_bytes = map->क्रमmat.pad_bytes;
	माप_प्रकार pair_size = reg_bytes + pad_bytes + val_bytes;
	माप_प्रकार len = pair_size * num_regs;

	अगर (!len)
		वापस -EINVAL;

	buf = kzalloc(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* We have to linearise by hand. */

	u8 = buf;

	क्रम (i = 0; i < num_regs; i++) अणु
		अचिन्हित पूर्णांक reg = regs[i].reg;
		अचिन्हित पूर्णांक val = regs[i].def;
		trace_regmap_hw_ग_लिखो_start(map, reg, 1);
		map->क्रमmat.क्रमmat_reg(u8, reg, map->reg_shअगरt);
		u8 += reg_bytes + pad_bytes;
		map->क्रमmat.क्रमmat_val(u8, val, 0);
		u8 += val_bytes;
	पूर्ण
	u8 = buf;
	*u8 |= map->ग_लिखो_flag_mask;

	ret = map->bus->ग_लिखो(map->bus_context, buf, len);

	kमुक्त(buf);

	क्रम (i = 0; i < num_regs; i++) अणु
		पूर्णांक reg = regs[i].reg;
		trace_regmap_hw_ग_लिखो_करोne(map, reg, 1);
	पूर्ण
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक _regmap_रेजिस्टर_page(काष्ठा regmap *map,
					  अचिन्हित पूर्णांक reg,
					  काष्ठा regmap_range_node *range)
अणु
	अचिन्हित पूर्णांक win_page = (reg - range->range_min) / range->winकरोw_len;

	वापस win_page;
पूर्ण

अटल पूर्णांक _regmap_range_multi_paged_reg_ग_लिखो(काष्ठा regmap *map,
					       काष्ठा reg_sequence *regs,
					       माप_प्रकार num_regs)
अणु
	पूर्णांक ret;
	पूर्णांक i, n;
	काष्ठा reg_sequence *base;
	अचिन्हित पूर्णांक this_page = 0;
	अचिन्हित पूर्णांक page_change = 0;
	/*
	 * the set of रेजिस्टरs are not neccessarily in order, but
	 * since the order of ग_लिखो must be preserved this algorithm
	 * chops the set each समय the page changes. This also applies
	 * अगर there is a delay required at any poपूर्णांक in the sequence.
	 */
	base = regs;
	क्रम (i = 0, n = 0; i < num_regs; i++, n++) अणु
		अचिन्हित पूर्णांक reg = regs[i].reg;
		काष्ठा regmap_range_node *range;

		range = _regmap_range_lookup(map, reg);
		अगर (range) अणु
			अचिन्हित पूर्णांक win_page = _regmap_रेजिस्टर_page(map, reg,
								      range);

			अगर (i == 0)
				this_page = win_page;
			अगर (win_page != this_page) अणु
				this_page = win_page;
				page_change = 1;
			पूर्ण
		पूर्ण

		/* If we have both a page change and a delay make sure to
		 * ग_लिखो the regs and apply the delay beक्रमe we change the
		 * page.
		 */

		अगर (page_change || regs[i].delay_us) अणु

				/* For situations where the first ग_लिखो requires
				 * a delay we need to make sure we करोn't call
				 * raw_multi_reg_ग_लिखो with n=0
				 * This can't occur with page अवरोधs as we
				 * never ग_लिखो on the first iteration
				 */
				अगर (regs[i].delay_us && i == 0)
					n = 1;

				ret = _regmap_raw_multi_reg_ग_लिखो(map, base, n);
				अगर (ret != 0)
					वापस ret;

				अगर (regs[i].delay_us) अणु
					अगर (map->can_sleep)
						fsleep(regs[i].delay_us);
					अन्यथा
						udelay(regs[i].delay_us);
				पूर्ण

				base += n;
				n = 0;

				अगर (page_change) अणु
					ret = _regmap_select_page(map,
								  &base[n].reg,
								  range, 1);
					अगर (ret != 0)
						वापस ret;

					page_change = 0;
				पूर्ण

		पूर्ण

	पूर्ण
	अगर (n > 0)
		वापस _regmap_raw_multi_reg_ग_लिखो(map, base, n);
	वापस 0;
पूर्ण

अटल पूर्णांक _regmap_multi_reg_ग_लिखो(काष्ठा regmap *map,
				   स्थिर काष्ठा reg_sequence *regs,
				   माप_प्रकार num_regs)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	अगर (!map->can_multi_ग_लिखो) अणु
		क्रम (i = 0; i < num_regs; i++) अणु
			ret = _regmap_ग_लिखो(map, regs[i].reg, regs[i].def);
			अगर (ret != 0)
				वापस ret;

			अगर (regs[i].delay_us) अणु
				अगर (map->can_sleep)
					fsleep(regs[i].delay_us);
				अन्यथा
					udelay(regs[i].delay_us);
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (!map->क्रमmat.parse_inplace)
		वापस -EINVAL;

	अगर (map->ग_लिखोable_reg)
		क्रम (i = 0; i < num_regs; i++) अणु
			पूर्णांक reg = regs[i].reg;
			अगर (!map->ग_लिखोable_reg(map->dev, reg))
				वापस -EINVAL;
			अगर (!IS_ALIGNED(reg, map->reg_stride))
				वापस -EINVAL;
		पूर्ण

	अगर (!map->cache_bypass) अणु
		क्रम (i = 0; i < num_regs; i++) अणु
			अचिन्हित पूर्णांक val = regs[i].def;
			अचिन्हित पूर्णांक reg = regs[i].reg;
			ret = regcache_ग_लिखो(map, reg, val);
			अगर (ret) अणु
				dev_err(map->dev,
				"Error in caching of register: %x ret: %d\n",
								reg, ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (map->cache_only) अणु
			map->cache_dirty = true;
			वापस 0;
		पूर्ण
	पूर्ण

	WARN_ON(!map->bus);

	क्रम (i = 0; i < num_regs; i++) अणु
		अचिन्हित पूर्णांक reg = regs[i].reg;
		काष्ठा regmap_range_node *range;

		/* Coalesce all the ग_लिखोs between a page अवरोध or a delay
		 * in a sequence
		 */
		range = _regmap_range_lookup(map, reg);
		अगर (range || regs[i].delay_us) अणु
			माप_प्रकार len = माप(काष्ठा reg_sequence)*num_regs;
			काष्ठा reg_sequence *base = kmemdup(regs, len,
							   GFP_KERNEL);
			अगर (!base)
				वापस -ENOMEM;
			ret = _regmap_range_multi_paged_reg_ग_लिखो(map, base,
								  num_regs);
			kमुक्त(base);

			वापस ret;
		पूर्ण
	पूर्ण
	वापस _regmap_raw_multi_reg_ग_लिखो(map, regs, num_regs);
पूर्ण

/**
 * regmap_multi_reg_ग_लिखो() - Write multiple रेजिस्टरs to the device
 *
 * @map: Register map to ग_लिखो to
 * @regs: Array of काष्ठाures containing रेजिस्टर,value to be written
 * @num_regs: Number of रेजिस्टरs to ग_लिखो
 *
 * Write multiple रेजिस्टरs to the device where the set of रेजिस्टर, value
 * pairs are supplied in any order, possibly not all in a single range.
 *
 * The 'normal' block ग_लिखो mode will send ultimately send data on the
 * target bus as R,V1,V2,V3,..,Vn where successively higher रेजिस्टरs are
 * addressed. However, this alternative block multi ग_लिखो mode will send
 * the data as R1,V1,R2,V2,..,Rn,Vn on the target bus. The target device
 * must of course support the mode.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will be
 * वापसed in error हालs.
 */
पूर्णांक regmap_multi_reg_ग_लिखो(काष्ठा regmap *map, स्थिर काष्ठा reg_sequence *regs,
			   पूर्णांक num_regs)
अणु
	पूर्णांक ret;

	map->lock(map->lock_arg);

	ret = _regmap_multi_reg_ग_लिखो(map, regs, num_regs);

	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_multi_reg_ग_लिखो);

/**
 * regmap_multi_reg_ग_लिखो_bypassed() - Write multiple रेजिस्टरs to the
 *                                     device but not the cache
 *
 * @map: Register map to ग_लिखो to
 * @regs: Array of काष्ठाures containing रेजिस्टर,value to be written
 * @num_regs: Number of रेजिस्टरs to ग_लिखो
 *
 * Write multiple रेजिस्टरs to the device but not the cache where the set
 * of रेजिस्टर are supplied in any order.
 *
 * This function is पूर्णांकended to be used क्रम writing a large block of data
 * atomically to the device in single transfer क्रम those I2C client devices
 * that implement this alternative block ग_लिखो mode.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_multi_reg_ग_लिखो_bypassed(काष्ठा regmap *map,
				    स्थिर काष्ठा reg_sequence *regs,
				    पूर्णांक num_regs)
अणु
	पूर्णांक ret;
	bool bypass;

	map->lock(map->lock_arg);

	bypass = map->cache_bypass;
	map->cache_bypass = true;

	ret = _regmap_multi_reg_ग_लिखो(map, regs, num_regs);

	map->cache_bypass = bypass;

	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_multi_reg_ग_लिखो_bypassed);

/**
 * regmap_raw_ग_लिखो_async() - Write raw values to one or more रेजिस्टरs
 *                            asynchronously
 *
 * @map: Register map to ग_लिखो to
 * @reg: Initial रेजिस्टर to ग_लिखो to
 * @val: Block of data to be written, laid out क्रम direct transmission to the
 *       device.  Must be valid until regmap_async_complete() is called.
 * @val_len: Length of data poपूर्णांकed to by val.
 *
 * This function is पूर्णांकended to be used क्रम things like firmware
 * करोwnload where a large block of data needs to be transferred to the
 * device.  No क्रमmatting will be करोne on the data provided.
 *
 * If supported by the underlying bus the ग_लिखो will be scheduled
 * asynchronously, helping maximise I/O speed on higher speed buses
 * like SPI.  regmap_async_complete() can be called to ensure that all
 * asynchrnous ग_लिखोs have been completed.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_raw_ग_लिखो_async(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			   स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	पूर्णांक ret;

	अगर (val_len % map->क्रमmat.val_bytes)
		वापस -EINVAL;
	अगर (!IS_ALIGNED(reg, map->reg_stride))
		वापस -EINVAL;

	map->lock(map->lock_arg);

	map->async = true;

	ret = _regmap_raw_ग_लिखो(map, reg, val, val_len, false);

	map->async = false;

	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_raw_ग_लिखो_async);

अटल पूर्णांक _regmap_raw_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, व्योम *val,
			    अचिन्हित पूर्णांक val_len, bool noinc)
अणु
	काष्ठा regmap_range_node *range;
	पूर्णांक ret;

	WARN_ON(!map->bus);

	अगर (!map->bus || !map->bus->पढ़ो)
		वापस -EINVAL;

	range = _regmap_range_lookup(map, reg);
	अगर (range) अणु
		ret = _regmap_select_page(map, &reg, range,
					  noinc ? 1 : val_len / map->क्रमmat.val_bytes);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	map->क्रमmat.क्रमmat_reg(map->work_buf, reg, map->reg_shअगरt);
	regmap_set_work_buf_flag_mask(map, map->क्रमmat.reg_bytes,
				      map->पढ़ो_flag_mask);
	trace_regmap_hw_पढ़ो_start(map, reg, val_len / map->क्रमmat.val_bytes);

	ret = map->bus->पढ़ो(map->bus_context, map->work_buf,
			     map->क्रमmat.reg_bytes + map->क्रमmat.pad_bytes,
			     val, val_len);

	trace_regmap_hw_पढ़ो_करोne(map, reg, val_len / map->क्रमmat.val_bytes);

	वापस ret;
पूर्ण

अटल पूर्णांक _regmap_bus_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक *val)
अणु
	काष्ठा regmap *map = context;

	वापस map->bus->reg_पढ़ो(map->bus_context, reg, val);
पूर्ण

अटल पूर्णांक _regmap_bus_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	काष्ठा regmap *map = context;
	व्योम *work_val = map->work_buf + map->क्रमmat.reg_bytes +
		map->क्रमmat.pad_bytes;

	अगर (!map->क्रमmat.parse_val)
		वापस -EINVAL;

	ret = _regmap_raw_पढ़ो(map, reg, work_val, map->क्रमmat.val_bytes, false);
	अगर (ret == 0)
		*val = map->क्रमmat.parse_val(work_val);

	वापस ret;
पूर्ण

अटल पूर्णांक _regmap_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	व्योम *context = _regmap_map_get_context(map);

	अगर (!map->cache_bypass) अणु
		ret = regcache_पढ़ो(map, reg, val);
		अगर (ret == 0)
			वापस 0;
	पूर्ण

	अगर (map->cache_only)
		वापस -EBUSY;

	अगर (!regmap_पढ़ोable(map, reg))
		वापस -EIO;

	ret = map->reg_पढ़ो(context, reg, val);
	अगर (ret == 0) अणु
		अगर (regmap_should_log(map))
			dev_info(map->dev, "%x => %x\n", reg, *val);

		trace_regmap_reg_पढ़ो(map, reg, *val);

		अगर (!map->cache_bypass)
			regcache_ग_लिखो(map, reg, *val);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * regmap_पढ़ो() - Read a value from a single रेजिस्टर
 *
 * @map: Register map to पढ़ो from
 * @reg: Register to be पढ़ो from
 * @val: Poपूर्णांकer to store पढ़ो value
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;

	अगर (!IS_ALIGNED(reg, map->reg_stride))
		वापस -EINVAL;

	map->lock(map->lock_arg);

	ret = _regmap_पढ़ो(map, reg, val);

	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_पढ़ो);

/**
 * regmap_raw_पढ़ो() - Read raw data from the device
 *
 * @map: Register map to पढ़ो from
 * @reg: First रेजिस्टर to be पढ़ो from
 * @val: Poपूर्णांकer to store पढ़ो value
 * @val_len: Size of data to पढ़ो
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_raw_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, व्योम *val,
		    माप_प्रकार val_len)
अणु
	माप_प्रकार val_bytes = map->क्रमmat.val_bytes;
	माप_प्रकार val_count = val_len / val_bytes;
	अचिन्हित पूर्णांक v;
	पूर्णांक ret, i;

	अगर (!map->bus)
		वापस -EINVAL;
	अगर (val_len % map->क्रमmat.val_bytes)
		वापस -EINVAL;
	अगर (!IS_ALIGNED(reg, map->reg_stride))
		वापस -EINVAL;
	अगर (val_count == 0)
		वापस -EINVAL;

	map->lock(map->lock_arg);

	अगर (regmap_अस्थिर_range(map, reg, val_count) || map->cache_bypass ||
	    map->cache_type == REGCACHE_NONE) अणु
		माप_प्रकार chunk_count, chunk_bytes;
		माप_प्रकार chunk_regs = val_count;

		अगर (!map->bus->पढ़ो) अणु
			ret = -ENOTSUPP;
			जाओ out;
		पूर्ण

		अगर (map->use_single_पढ़ो)
			chunk_regs = 1;
		अन्यथा अगर (map->max_raw_पढ़ो && val_len > map->max_raw_पढ़ो)
			chunk_regs = map->max_raw_पढ़ो / val_bytes;

		chunk_count = val_count / chunk_regs;
		chunk_bytes = chunk_regs * val_bytes;

		/* Read bytes that fit पूर्णांकo whole chunks */
		क्रम (i = 0; i < chunk_count; i++) अणु
			ret = _regmap_raw_पढ़ो(map, reg, val, chunk_bytes, false);
			अगर (ret != 0)
				जाओ out;

			reg += regmap_get_offset(map, chunk_regs);
			val += chunk_bytes;
			val_len -= chunk_bytes;
		पूर्ण

		/* Read reमुख्यing bytes */
		अगर (val_len) अणु
			ret = _regmap_raw_पढ़ो(map, reg, val, val_len, false);
			अगर (ret != 0)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Otherwise go word by word क्रम the cache; should be low
		 * cost as we expect to hit the cache.
		 */
		क्रम (i = 0; i < val_count; i++) अणु
			ret = _regmap_पढ़ो(map, reg + regmap_get_offset(map, i),
					   &v);
			अगर (ret != 0)
				जाओ out;

			map->क्रमmat.क्रमmat_val(val + (i * val_bytes), v, 0);
		पूर्ण
	पूर्ण

 out:
	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_raw_पढ़ो);

/**
 * regmap_noinc_पढ़ो(): Read data from a रेजिस्टर without incrementing the
 *			रेजिस्टर number
 *
 * @map: Register map to पढ़ो from
 * @reg: Register to पढ़ो from
 * @val: Poपूर्णांकer to data buffer
 * @val_len: Length of output buffer in bytes.
 *
 * The regmap API usually assumes that bulk bus पढ़ो operations will पढ़ो a
 * range of रेजिस्टरs. Some devices have certain रेजिस्टरs क्रम which a पढ़ो
 * operation पढ़ो will पढ़ो from an पूर्णांकernal FIFO.
 *
 * The target रेजिस्टर must be अस्थिर but रेजिस्टरs after it can be
 * completely unrelated cacheable रेजिस्टरs.
 *
 * This will attempt multiple पढ़ोs as required to पढ़ो val_len bytes.
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will be
 * वापसed in error हालs.
 */
पूर्णांक regmap_noinc_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		      व्योम *val, माप_प्रकार val_len)
अणु
	माप_प्रकार पढ़ो_len;
	पूर्णांक ret;

	अगर (!map->bus)
		वापस -EINVAL;
	अगर (!map->bus->पढ़ो)
		वापस -ENOTSUPP;
	अगर (val_len % map->क्रमmat.val_bytes)
		वापस -EINVAL;
	अगर (!IS_ALIGNED(reg, map->reg_stride))
		वापस -EINVAL;
	अगर (val_len == 0)
		वापस -EINVAL;

	map->lock(map->lock_arg);

	अगर (!regmap_अस्थिर(map, reg) || !regmap_पढ़ोable_noinc(map, reg)) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	जबतक (val_len) अणु
		अगर (map->max_raw_पढ़ो && map->max_raw_पढ़ो < val_len)
			पढ़ो_len = map->max_raw_पढ़ो;
		अन्यथा
			पढ़ो_len = val_len;
		ret = _regmap_raw_पढ़ो(map, reg, val, पढ़ो_len, true);
		अगर (ret)
			जाओ out_unlock;
		val = ((u8 *)val) + पढ़ो_len;
		val_len -= पढ़ो_len;
	पूर्ण

out_unlock:
	map->unlock(map->lock_arg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_noinc_पढ़ो);

/**
 * regmap_field_पढ़ो(): Read a value to a single रेजिस्टर field
 *
 * @field: Register field to पढ़ो from
 * @val: Poपूर्णांकer to store पढ़ो value
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_field_पढ़ो(काष्ठा regmap_field *field, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;
	ret = regmap_पढ़ो(field->regmap, field->reg, &reg_val);
	अगर (ret != 0)
		वापस ret;

	reg_val &= field->mask;
	reg_val >>= field->shअगरt;
	*val = reg_val;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_field_पढ़ो);

/**
 * regmap_fields_पढ़ो() - Read a value to a single रेजिस्टर field with port ID
 *
 * @field: Register field to पढ़ो from
 * @id: port ID
 * @val: Poपूर्णांकer to store पढ़ो value
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_fields_पढ़ो(काष्ठा regmap_field *field, अचिन्हित पूर्णांक id,
		       अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;

	अगर (id >= field->id_size)
		वापस -EINVAL;

	ret = regmap_पढ़ो(field->regmap,
			  field->reg + (field->id_offset * id),
			  &reg_val);
	अगर (ret != 0)
		वापस ret;

	reg_val &= field->mask;
	reg_val >>= field->shअगरt;
	*val = reg_val;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_fields_पढ़ो);

/**
 * regmap_bulk_पढ़ो() - Read multiple रेजिस्टरs from the device
 *
 * @map: Register map to पढ़ो from
 * @reg: First रेजिस्टर to be पढ़ो from
 * @val: Poपूर्णांकer to store पढ़ो value, in native रेजिस्टर size क्रम device
 * @val_count: Number of रेजिस्टरs to पढ़ो
 *
 * A value of zero will be वापसed on success, a negative त्रुटि_सं will
 * be वापसed in error हालs.
 */
पूर्णांक regmap_bulk_पढ़ो(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, व्योम *val,
		     माप_प्रकार val_count)
अणु
	पूर्णांक ret, i;
	माप_प्रकार val_bytes = map->क्रमmat.val_bytes;
	bool vol = regmap_अस्थिर_range(map, reg, val_count);

	अगर (!IS_ALIGNED(reg, map->reg_stride))
		वापस -EINVAL;
	अगर (val_count == 0)
		वापस -EINVAL;

	अगर (map->bus && map->क्रमmat.parse_inplace && (vol || map->cache_type == REGCACHE_NONE)) अणु
		ret = regmap_raw_पढ़ो(map, reg, val, val_bytes * val_count);
		अगर (ret != 0)
			वापस ret;

		क्रम (i = 0; i < val_count * val_bytes; i += val_bytes)
			map->क्रमmat.parse_inplace(val + i);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_64BIT
		u64 *u64 = val;
#पूर्ण_अगर
		u32 *u32 = val;
		u16 *u16 = val;
		u8 *u8 = val;

		map->lock(map->lock_arg);

		क्रम (i = 0; i < val_count; i++) अणु
			अचिन्हित पूर्णांक ival;

			ret = _regmap_पढ़ो(map, reg + regmap_get_offset(map, i),
					   &ival);
			अगर (ret != 0)
				जाओ out;

			चयन (map->क्रमmat.val_bytes) अणु
#अगर_घोषित CONFIG_64BIT
			हाल 8:
				u64[i] = ival;
				अवरोध;
#पूर्ण_अगर
			हाल 4:
				u32[i] = ival;
				अवरोध;
			हाल 2:
				u16[i] = ival;
				अवरोध;
			हाल 1:
				u8[i] = ival;
				अवरोध;
			शेष:
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण

out:
		map->unlock(map->lock_arg);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_bulk_पढ़ो);

अटल पूर्णांक _regmap_update_bits(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
			       bool *change, bool क्रमce_ग_लिखो)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पंचांगp, orig;

	अगर (change)
		*change = false;

	अगर (regmap_अस्थिर(map, reg) && map->reg_update_bits) अणु
		ret = map->reg_update_bits(map->bus_context, reg, mask, val);
		अगर (ret == 0 && change)
			*change = true;
	पूर्ण अन्यथा अणु
		ret = _regmap_पढ़ो(map, reg, &orig);
		अगर (ret != 0)
			वापस ret;

		पंचांगp = orig & ~mask;
		पंचांगp |= val & mask;

		अगर (क्रमce_ग_लिखो || (पंचांगp != orig)) अणु
			ret = _regmap_ग_लिखो(map, reg, पंचांगp);
			अगर (ret == 0 && change)
				*change = true;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * regmap_update_bits_base() - Perक्रमm a पढ़ो/modअगरy/ग_लिखो cycle on a रेजिस्टर
 *
 * @map: Register map to update
 * @reg: Register to update
 * @mask: Biपंचांगask to change
 * @val: New value क्रम biपंचांगask
 * @change: Boolean indicating अगर a ग_लिखो was करोne
 * @async: Boolean indicating asynchronously
 * @क्रमce: Boolean indicating use क्रमce update
 *
 * Perक्रमm a पढ़ो/modअगरy/ग_लिखो cycle on a रेजिस्टर map with change, async, क्रमce
 * options.
 *
 * If async is true:
 *
 * With most buses the पढ़ो must be करोne synchronously so this is most useful
 * क्रम devices with a cache which करो not need to पूर्णांकeract with the hardware to
 * determine the current रेजिस्टर value.
 *
 * Returns zero क्रम success, a negative number on error.
 */
पूर्णांक regmap_update_bits_base(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val,
			    bool *change, bool async, bool क्रमce)
अणु
	पूर्णांक ret;

	map->lock(map->lock_arg);

	map->async = async;

	ret = _regmap_update_bits(map, reg, mask, val, change, क्रमce);

	map->async = false;

	map->unlock(map->lock_arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_update_bits_base);

/**
 * regmap_test_bits() - Check अगर all specअगरied bits are set in a रेजिस्टर.
 *
 * @map: Register map to operate on
 * @reg: Register to पढ़ो from
 * @bits: Bits to test
 *
 * Returns 0 अगर at least one of the tested bits is not set, 1 अगर all tested
 * bits are set and a negative error number अगर the underlying regmap_पढ़ो()
 * fails.
 */
पूर्णांक regmap_test_bits(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक val, ret;

	ret = regmap_पढ़ो(map, reg, &val);
	अगर (ret)
		वापस ret;

	वापस (val & bits) == bits;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_test_bits);

व्योम regmap_async_complete_cb(काष्ठा regmap_async *async, पूर्णांक ret)
अणु
	काष्ठा regmap *map = async->map;
	bool wake;

	trace_regmap_async_io_complete(map);

	spin_lock(&map->async_lock);
	list_move(&async->list, &map->async_मुक्त);
	wake = list_empty(&map->async_list);

	अगर (ret != 0)
		map->async_ret = ret;

	spin_unlock(&map->async_lock);

	अगर (wake)
		wake_up(&map->async_रुकोq);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_async_complete_cb);

अटल पूर्णांक regmap_async_is_करोne(काष्ठा regmap *map)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&map->async_lock, flags);
	ret = list_empty(&map->async_list);
	spin_unlock_irqrestore(&map->async_lock, flags);

	वापस ret;
पूर्ण

/**
 * regmap_async_complete - Ensure all asynchronous I/O has completed.
 *
 * @map: Map to operate on.
 *
 * Blocks until any pending asynchronous I/O has completed.  Returns
 * an error code क्रम any failed I/O operations.
 */
पूर्णांक regmap_async_complete(काष्ठा regmap *map)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Nothing to करो with no async support */
	अगर (!map->bus || !map->bus->async_ग_लिखो)
		वापस 0;

	trace_regmap_async_complete_start(map);

	रुको_event(map->async_रुकोq, regmap_async_is_करोne(map));

	spin_lock_irqsave(&map->async_lock, flags);
	ret = map->async_ret;
	map->async_ret = 0;
	spin_unlock_irqrestore(&map->async_lock, flags);

	trace_regmap_async_complete_करोne(map);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_async_complete);

/**
 * regmap_रेजिस्टर_patch - Register and apply रेजिस्टर updates to be applied
 *                         on device initialistion
 *
 * @map: Register map to apply updates to.
 * @regs: Values to update.
 * @num_regs: Number of entries in regs.
 *
 * Register a set of रेजिस्टर updates to be applied to the device
 * whenever the device रेजिस्टरs are synchronised with the cache and
 * apply them immediately.  Typically this is used to apply
 * corrections to be applied to the device शेषs on startup, such
 * as the updates some venकरोrs provide to unकरोcumented रेजिस्टरs.
 *
 * The caller must ensure that this function cannot be called
 * concurrently with either itself or regcache_sync().
 */
पूर्णांक regmap_रेजिस्टर_patch(काष्ठा regmap *map, स्थिर काष्ठा reg_sequence *regs,
			  पूर्णांक num_regs)
अणु
	काष्ठा reg_sequence *p;
	पूर्णांक ret;
	bool bypass;

	अगर (WARN_ONCE(num_regs <= 0, "invalid registers number (%d)\n",
	    num_regs))
		वापस 0;

	p = kपुनः_स्मृति(map->patch,
		     माप(काष्ठा reg_sequence) * (map->patch_regs + num_regs),
		     GFP_KERNEL);
	अगर (p) अणु
		स_नकल(p + map->patch_regs, regs, num_regs * माप(*regs));
		map->patch = p;
		map->patch_regs += num_regs;
	पूर्ण अन्यथा अणु
		वापस -ENOMEM;
	पूर्ण

	map->lock(map->lock_arg);

	bypass = map->cache_bypass;

	map->cache_bypass = true;
	map->async = true;

	ret = _regmap_multi_reg_ग_लिखो(map, regs, num_regs);

	map->async = false;
	map->cache_bypass = bypass;

	map->unlock(map->lock_arg);

	regmap_async_complete(map);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_रेजिस्टर_patch);

/**
 * regmap_get_val_bytes() - Report the size of a रेजिस्टर value
 *
 * @map: Register map to operate on.
 *
 * Report the size of a रेजिस्टर value, मुख्यly पूर्णांकended to क्रम use by
 * generic infraकाष्ठाure built on top of regmap.
 */
पूर्णांक regmap_get_val_bytes(काष्ठा regmap *map)
अणु
	अगर (map->क्रमmat.क्रमmat_ग_लिखो)
		वापस -EINVAL;

	वापस map->क्रमmat.val_bytes;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_get_val_bytes);

/**
 * regmap_get_max_रेजिस्टर() - Report the max रेजिस्टर value
 *
 * @map: Register map to operate on.
 *
 * Report the max रेजिस्टर value, मुख्यly पूर्णांकended to क्रम use by
 * generic infraकाष्ठाure built on top of regmap.
 */
पूर्णांक regmap_get_max_रेजिस्टर(काष्ठा regmap *map)
अणु
	वापस map->max_रेजिस्टर ? map->max_रेजिस्टर : -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_get_max_रेजिस्टर);

/**
 * regmap_get_reg_stride() - Report the रेजिस्टर address stride
 *
 * @map: Register map to operate on.
 *
 * Report the रेजिस्टर address stride, मुख्यly पूर्णांकended to क्रम use by
 * generic infraकाष्ठाure built on top of regmap.
 */
पूर्णांक regmap_get_reg_stride(काष्ठा regmap *map)
अणु
	वापस map->reg_stride;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_get_reg_stride);

पूर्णांक regmap_parse_val(काष्ठा regmap *map, स्थिर व्योम *buf,
			अचिन्हित पूर्णांक *val)
अणु
	अगर (!map->क्रमmat.parse_val)
		वापस -EINVAL;

	*val = map->क्रमmat.parse_val(buf);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_parse_val);

अटल पूर्णांक __init regmap_initcall(व्योम)
अणु
	regmap_debugfs_initcall();

	वापस 0;
पूर्ण
postcore_initcall(regmap_initcall);
