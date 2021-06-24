<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-bitset.h"
#समावेश "dm-transaction-manager.h"

#समावेश <linux/export.h>
#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "bitset"
#घोषणा BITS_PER_ARRAY_ENTRY 64

/*----------------------------------------------------------------*/

अटल काष्ठा dm_btree_value_type bitset_bvt = अणु
	.context = शून्य,
	.size = माप(__le64),
	.inc = शून्य,
	.dec = शून्य,
	.equal = शून्य,
पूर्ण;

/*----------------------------------------------------------------*/

व्योम dm_disk_bitset_init(काष्ठा dm_transaction_manager *पंचांग,
			 काष्ठा dm_disk_bitset *info)
अणु
	dm_array_info_init(&info->array_info, पंचांग, &bitset_bvt);
	info->current_index_set = false;
पूर्ण
EXPORT_SYMBOL_GPL(dm_disk_bitset_init);

पूर्णांक dm_bitset_empty(काष्ठा dm_disk_bitset *info, dm_block_t *root)
अणु
	वापस dm_array_empty(&info->array_info, root);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_empty);

काष्ठा packer_context अणु
	bit_value_fn fn;
	अचिन्हित nr_bits;
	व्योम *context;
पूर्ण;

अटल पूर्णांक pack_bits(uपूर्णांक32_t index, व्योम *value, व्योम *context)
अणु
	पूर्णांक r;
	काष्ठा packer_context *p = context;
	अचिन्हित bit, nr = min(64u, p->nr_bits - (index * 64));
	uपूर्णांक64_t word = 0;
	bool bv;

	क्रम (bit = 0; bit < nr; bit++) अणु
		r = p->fn(index * 64 + bit, &bv, p->context);
		अगर (r)
			वापस r;

		अगर (bv)
			set_bit(bit, (अचिन्हित दीर्घ *) &word);
		अन्यथा
			clear_bit(bit, (अचिन्हित दीर्घ *) &word);
	पूर्ण

	*((__le64 *) value) = cpu_to_le64(word);

	वापस 0;
पूर्ण

पूर्णांक dm_bitset_new(काष्ठा dm_disk_bitset *info, dm_block_t *root,
		  uपूर्णांक32_t size, bit_value_fn fn, व्योम *context)
अणु
	काष्ठा packer_context p;
	p.fn = fn;
	p.nr_bits = size;
	p.context = context;

	वापस dm_array_new(&info->array_info, root, dm_भाग_up(size, 64), pack_bits, &p);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_new);

पूर्णांक dm_bitset_resize(काष्ठा dm_disk_bitset *info, dm_block_t root,
		     uपूर्णांक32_t old_nr_entries, uपूर्णांक32_t new_nr_entries,
		     bool शेष_value, dm_block_t *new_root)
अणु
	uपूर्णांक32_t old_blocks = dm_भाग_up(old_nr_entries, BITS_PER_ARRAY_ENTRY);
	uपूर्णांक32_t new_blocks = dm_भाग_up(new_nr_entries, BITS_PER_ARRAY_ENTRY);
	__le64 value = शेष_value ? cpu_to_le64(~0) : cpu_to_le64(0);

	__dm_bless_क्रम_disk(&value);
	वापस dm_array_resize(&info->array_info, root, old_blocks, new_blocks,
			       &value, new_root);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_resize);

पूर्णांक dm_bitset_del(काष्ठा dm_disk_bitset *info, dm_block_t root)
अणु
	वापस dm_array_del(&info->array_info, root);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_del);

पूर्णांक dm_bitset_flush(काष्ठा dm_disk_bitset *info, dm_block_t root,
		    dm_block_t *new_root)
अणु
	पूर्णांक r;
	__le64 value;

	अगर (!info->current_index_set || !info->dirty)
		वापस 0;

	value = cpu_to_le64(info->current_bits);

	__dm_bless_क्रम_disk(&value);
	r = dm_array_set_value(&info->array_info, root, info->current_index,
			       &value, new_root);
	अगर (r)
		वापस r;

	info->current_index_set = false;
	info->dirty = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_flush);

अटल पूर्णांक पढ़ो_bits(काष्ठा dm_disk_bitset *info, dm_block_t root,
		     uपूर्णांक32_t array_index)
अणु
	पूर्णांक r;
	__le64 value;

	r = dm_array_get_value(&info->array_info, root, array_index, &value);
	अगर (r)
		वापस r;

	info->current_bits = le64_to_cpu(value);
	info->current_index_set = true;
	info->current_index = array_index;
	info->dirty = false;

	वापस 0;
पूर्ण

अटल पूर्णांक get_array_entry(काष्ठा dm_disk_bitset *info, dm_block_t root,
			   uपूर्णांक32_t index, dm_block_t *new_root)
अणु
	पूर्णांक r;
	अचिन्हित array_index = index / BITS_PER_ARRAY_ENTRY;

	अगर (info->current_index_set) अणु
		अगर (info->current_index == array_index)
			वापस 0;

		r = dm_bitset_flush(info, root, new_root);
		अगर (r)
			वापस r;
	पूर्ण

	वापस पढ़ो_bits(info, root, array_index);
पूर्ण

पूर्णांक dm_bitset_set_bit(काष्ठा dm_disk_bitset *info, dm_block_t root,
		      uपूर्णांक32_t index, dm_block_t *new_root)
अणु
	पूर्णांक r;
	अचिन्हित b = index % BITS_PER_ARRAY_ENTRY;

	r = get_array_entry(info, root, index, new_root);
	अगर (r)
		वापस r;

	set_bit(b, (अचिन्हित दीर्घ *) &info->current_bits);
	info->dirty = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_set_bit);

पूर्णांक dm_bitset_clear_bit(काष्ठा dm_disk_bitset *info, dm_block_t root,
			uपूर्णांक32_t index, dm_block_t *new_root)
अणु
	पूर्णांक r;
	अचिन्हित b = index % BITS_PER_ARRAY_ENTRY;

	r = get_array_entry(info, root, index, new_root);
	अगर (r)
		वापस r;

	clear_bit(b, (अचिन्हित दीर्घ *) &info->current_bits);
	info->dirty = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_clear_bit);

पूर्णांक dm_bitset_test_bit(काष्ठा dm_disk_bitset *info, dm_block_t root,
		       uपूर्णांक32_t index, dm_block_t *new_root, bool *result)
अणु
	पूर्णांक r;
	अचिन्हित b = index % BITS_PER_ARRAY_ENTRY;

	r = get_array_entry(info, root, index, new_root);
	अगर (r)
		वापस r;

	*result = test_bit(b, (अचिन्हित दीर्घ *) &info->current_bits);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_test_bit);

अटल पूर्णांक cursor_next_array_entry(काष्ठा dm_bitset_cursor *c)
अणु
	पूर्णांक r;
	__le64 *value;

	r = dm_array_cursor_next(&c->cursor);
	अगर (r)
		वापस r;

	dm_array_cursor_get_value(&c->cursor, (व्योम **) &value);
	c->array_index++;
	c->bit_index = 0;
	c->current_bits = le64_to_cpu(*value);
	वापस 0;
पूर्ण

पूर्णांक dm_bitset_cursor_begin(काष्ठा dm_disk_bitset *info,
			   dm_block_t root, uपूर्णांक32_t nr_entries,
			   काष्ठा dm_bitset_cursor *c)
अणु
	पूर्णांक r;
	__le64 *value;

	अगर (!nr_entries)
		वापस -ENODATA;

	c->info = info;
	c->entries_reमुख्यing = nr_entries;

	r = dm_array_cursor_begin(&info->array_info, root, &c->cursor);
	अगर (r)
		वापस r;

	dm_array_cursor_get_value(&c->cursor, (व्योम **) &value);
	c->array_index = 0;
	c->bit_index = 0;
	c->current_bits = le64_to_cpu(*value);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_cursor_begin);

व्योम dm_bitset_cursor_end(काष्ठा dm_bitset_cursor *c)
अणु
	वापस dm_array_cursor_end(&c->cursor);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_cursor_end);

पूर्णांक dm_bitset_cursor_next(काष्ठा dm_bitset_cursor *c)
अणु
	पूर्णांक r = 0;

	अगर (!c->entries_reमुख्यing)
		वापस -ENODATA;

	c->entries_reमुख्यing--;
	अगर (++c->bit_index > 63)
		r = cursor_next_array_entry(c);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_cursor_next);

पूर्णांक dm_bitset_cursor_skip(काष्ठा dm_bitset_cursor *c, uपूर्णांक32_t count)
अणु
	पूर्णांक r;
	__le64 *value;
	uपूर्णांक32_t nr_array_skip;
	uपूर्णांक32_t reमुख्यing_in_word = 64 - c->bit_index;

	अगर (c->entries_reमुख्यing < count)
		वापस -ENODATA;

	अगर (count < reमुख्यing_in_word) अणु
		c->bit_index += count;
		c->entries_reमुख्यing -= count;
		वापस 0;

	पूर्ण अन्यथा अणु
		c->entries_reमुख्यing -= reमुख्यing_in_word;
		count -= reमुख्यing_in_word;
	पूर्ण

	nr_array_skip = (count / 64) + 1;
	r = dm_array_cursor_skip(&c->cursor, nr_array_skip);
	अगर (r)
		वापस r;

	dm_array_cursor_get_value(&c->cursor, (व्योम **) &value);
	c->entries_reमुख्यing -= count;
	c->array_index += nr_array_skip;
	c->bit_index = count & 63;
	c->current_bits = le64_to_cpu(*value);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_cursor_skip);

bool dm_bitset_cursor_get_value(काष्ठा dm_bitset_cursor *c)
अणु
	वापस test_bit(c->bit_index, (अचिन्हित दीर्घ *) &c->current_bits);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bitset_cursor_get_value);

/*----------------------------------------------------------------*/
