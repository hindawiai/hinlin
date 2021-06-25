<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश "item.h"
#समावेश "core_acl_flex_keys.h"

/* For the purpose of the driver, define an पूर्णांकernal storage scratchpad
 * that will be used to store key/mask values. For each defined element type
 * define an पूर्णांकernal storage geometry.
 *
 * When adding new elements, MLXSW_AFK_ELEMENT_STORAGE_SIZE must be increased
 * accordingly.
 */
अटल स्थिर काष्ठा mlxsw_afk_element_info mlxsw_afk_element_infos[] = अणु
	MLXSW_AFK_ELEMENT_INFO_U32(SRC_SYS_PORT, 0x00, 16, 16),
	MLXSW_AFK_ELEMENT_INFO_BUF(DMAC_32_47, 0x04, 2),
	MLXSW_AFK_ELEMENT_INFO_BUF(DMAC_0_31, 0x06, 4),
	MLXSW_AFK_ELEMENT_INFO_BUF(SMAC_32_47, 0x0A, 2),
	MLXSW_AFK_ELEMENT_INFO_BUF(SMAC_0_31, 0x0C, 4),
	MLXSW_AFK_ELEMENT_INFO_U32(ETHERTYPE, 0x00, 0, 16),
	MLXSW_AFK_ELEMENT_INFO_U32(IP_PROTO, 0x10, 0, 8),
	MLXSW_AFK_ELEMENT_INFO_U32(VID, 0x10, 8, 12),
	MLXSW_AFK_ELEMENT_INFO_U32(PCP, 0x10, 20, 3),
	MLXSW_AFK_ELEMENT_INFO_U32(TCP_FLAGS, 0x10, 23, 9),
	MLXSW_AFK_ELEMENT_INFO_U32(DST_L4_PORT, 0x14, 0, 16),
	MLXSW_AFK_ELEMENT_INFO_U32(SRC_L4_PORT, 0x14, 16, 16),
	MLXSW_AFK_ELEMENT_INFO_U32(IP_TTL_, 0x18, 0, 8),
	MLXSW_AFK_ELEMENT_INFO_U32(IP_ECN, 0x18, 9, 2),
	MLXSW_AFK_ELEMENT_INFO_U32(IP_DSCP, 0x18, 11, 6),
	MLXSW_AFK_ELEMENT_INFO_U32(VIRT_ROUTER_8_10, 0x18, 17, 3),
	MLXSW_AFK_ELEMENT_INFO_U32(VIRT_ROUTER_0_7, 0x18, 20, 8),
	MLXSW_AFK_ELEMENT_INFO_BUF(SRC_IP_96_127, 0x20, 4),
	MLXSW_AFK_ELEMENT_INFO_BUF(SRC_IP_64_95, 0x24, 4),
	MLXSW_AFK_ELEMENT_INFO_BUF(SRC_IP_32_63, 0x28, 4),
	MLXSW_AFK_ELEMENT_INFO_BUF(SRC_IP_0_31, 0x2C, 4),
	MLXSW_AFK_ELEMENT_INFO_BUF(DST_IP_96_127, 0x30, 4),
	MLXSW_AFK_ELEMENT_INFO_BUF(DST_IP_64_95, 0x34, 4),
	MLXSW_AFK_ELEMENT_INFO_BUF(DST_IP_32_63, 0x38, 4),
	MLXSW_AFK_ELEMENT_INFO_BUF(DST_IP_0_31, 0x3C, 4),
पूर्ण;

काष्ठा mlxsw_afk अणु
	काष्ठा list_head key_info_list;
	अचिन्हित पूर्णांक max_blocks;
	स्थिर काष्ठा mlxsw_afk_ops *ops;
	स्थिर काष्ठा mlxsw_afk_block *blocks;
	अचिन्हित पूर्णांक blocks_count;
पूर्ण;

अटल bool mlxsw_afk_blocks_check(काष्ठा mlxsw_afk *mlxsw_afk)
अणु
	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0; i < mlxsw_afk->blocks_count; i++) अणु
		स्थिर काष्ठा mlxsw_afk_block *block = &mlxsw_afk->blocks[i];

		क्रम (j = 0; j < block->instances_count; j++) अणु
			स्थिर काष्ठा mlxsw_afk_element_info *elinfo;
			काष्ठा mlxsw_afk_element_inst *elinst;

			elinst = &block->instances[j];
			elinfo = &mlxsw_afk_element_infos[elinst->element];
			अगर (elinst->type != elinfo->type ||
			    (!elinst->aव्योम_size_check &&
			     elinst->item.size.bits !=
			     elinfo->item.size.bits))
				वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

काष्ठा mlxsw_afk *mlxsw_afk_create(अचिन्हित पूर्णांक max_blocks,
				   स्थिर काष्ठा mlxsw_afk_ops *ops)
अणु
	काष्ठा mlxsw_afk *mlxsw_afk;

	mlxsw_afk = kzalloc(माप(*mlxsw_afk), GFP_KERNEL);
	अगर (!mlxsw_afk)
		वापस शून्य;
	INIT_LIST_HEAD(&mlxsw_afk->key_info_list);
	mlxsw_afk->max_blocks = max_blocks;
	mlxsw_afk->ops = ops;
	mlxsw_afk->blocks = ops->blocks;
	mlxsw_afk->blocks_count = ops->blocks_count;
	WARN_ON(!mlxsw_afk_blocks_check(mlxsw_afk));
	वापस mlxsw_afk;
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_create);

व्योम mlxsw_afk_destroy(काष्ठा mlxsw_afk *mlxsw_afk)
अणु
	WARN_ON(!list_empty(&mlxsw_afk->key_info_list));
	kमुक्त(mlxsw_afk);
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_destroy);

काष्ठा mlxsw_afk_key_info अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक ref_count;
	अचिन्हित पूर्णांक blocks_count;
	पूर्णांक element_to_block[MLXSW_AFK_ELEMENT_MAX]; /* index is element, value
						      * is index inside "blocks"
						      */
	काष्ठा mlxsw_afk_element_usage elusage;
	स्थिर काष्ठा mlxsw_afk_block *blocks[];
पूर्ण;

अटल bool
mlxsw_afk_key_info_elements_eq(काष्ठा mlxsw_afk_key_info *key_info,
			       काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	वापस स_भेद(&key_info->elusage, elusage, माप(*elusage)) == 0;
पूर्ण

अटल काष्ठा mlxsw_afk_key_info *
mlxsw_afk_key_info_find(काष्ठा mlxsw_afk *mlxsw_afk,
			काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	काष्ठा mlxsw_afk_key_info *key_info;

	list_क्रम_each_entry(key_info, &mlxsw_afk->key_info_list, list) अणु
		अगर (mlxsw_afk_key_info_elements_eq(key_info, elusage))
			वापस key_info;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा mlxsw_afk_picker अणु
	DECLARE_BITMAP(element, MLXSW_AFK_ELEMENT_MAX);
	अचिन्हित पूर्णांक total;
पूर्ण;

अटल व्योम mlxsw_afk_picker_count_hits(काष्ठा mlxsw_afk *mlxsw_afk,
					काष्ठा mlxsw_afk_picker *picker,
					क्रमागत mlxsw_afk_element element)
अणु
	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0; i < mlxsw_afk->blocks_count; i++) अणु
		स्थिर काष्ठा mlxsw_afk_block *block = &mlxsw_afk->blocks[i];

		क्रम (j = 0; j < block->instances_count; j++) अणु
			काष्ठा mlxsw_afk_element_inst *elinst;

			elinst = &block->instances[j];
			अगर (elinst->element == element) अणु
				__set_bit(element, picker[i].element);
				picker[i].total++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mlxsw_afk_picker_subtract_hits(काष्ठा mlxsw_afk *mlxsw_afk,
					   काष्ठा mlxsw_afk_picker *picker,
					   पूर्णांक block_index)
अणु
	DECLARE_BITMAP(hits_element, MLXSW_AFK_ELEMENT_MAX);
	पूर्णांक i;
	पूर्णांक j;

	स_नकल(&hits_element, &picker[block_index].element,
	       माप(hits_element));

	क्रम (i = 0; i < mlxsw_afk->blocks_count; i++) अणु
		क्रम_each_set_bit(j, hits_element, MLXSW_AFK_ELEMENT_MAX) अणु
			अगर (__test_and_clear_bit(j, picker[i].element))
				picker[i].total--;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_afk_picker_most_hits_get(काष्ठा mlxsw_afk *mlxsw_afk,
					  काष्ठा mlxsw_afk_picker *picker)
अणु
	पूर्णांक most_index = -EINVAL; /* Should never happen to वापस this */
	पूर्णांक most_hits = 0;
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_afk->blocks_count; i++) अणु
		अगर (picker[i].total > most_hits) अणु
			most_hits = picker[i].total;
			most_index = i;
		पूर्ण
	पूर्ण
	वापस most_index;
पूर्ण

अटल पूर्णांक mlxsw_afk_picker_key_info_add(काष्ठा mlxsw_afk *mlxsw_afk,
					 काष्ठा mlxsw_afk_picker *picker,
					 पूर्णांक block_index,
					 काष्ठा mlxsw_afk_key_info *key_info)
अणु
	क्रमागत mlxsw_afk_element element;

	अगर (key_info->blocks_count == mlxsw_afk->max_blocks)
		वापस -EINVAL;

	क्रम_each_set_bit(element, picker[block_index].element,
			 MLXSW_AFK_ELEMENT_MAX) अणु
		key_info->element_to_block[element] = key_info->blocks_count;
		mlxsw_afk_element_usage_add(&key_info->elusage, element);
	पूर्ण

	key_info->blocks[key_info->blocks_count] =
					&mlxsw_afk->blocks[block_index];
	key_info->blocks_count++;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_afk_picker(काष्ठा mlxsw_afk *mlxsw_afk,
			    काष्ठा mlxsw_afk_key_info *key_info,
			    काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	काष्ठा mlxsw_afk_picker *picker;
	क्रमागत mlxsw_afk_element element;
	पूर्णांक err;

	picker = kसुस्मृति(mlxsw_afk->blocks_count, माप(*picker), GFP_KERNEL);
	अगर (!picker)
		वापस -ENOMEM;

	/* Since the same elements could be present in multiple blocks,
	 * we must find out optimal block list in order to make the
	 * block count as low as possible.
	 *
	 * First, we count hits. We go over all available blocks and count
	 * how many of requested elements are covered by each.
	 *
	 * Then in loop, we find block with most hits and add it to
	 * output key_info. Then we have to subtract this block hits so
	 * the next iteration will find most suitable block क्रम
	 * the rest of requested elements.
	 */

	mlxsw_afk_element_usage_क्रम_each(element, elusage)
		mlxsw_afk_picker_count_hits(mlxsw_afk, picker, element);

	करो अणु
		पूर्णांक block_index;

		block_index = mlxsw_afk_picker_most_hits_get(mlxsw_afk, picker);
		अगर (block_index < 0) अणु
			err = block_index;
			जाओ out;
		पूर्ण
		err = mlxsw_afk_picker_key_info_add(mlxsw_afk, picker,
						    block_index, key_info);
		अगर (err)
			जाओ out;
		mlxsw_afk_picker_subtract_hits(mlxsw_afk, picker, block_index);
	पूर्ण जबतक (!mlxsw_afk_key_info_elements_eq(key_info, elusage));

	err = 0;
out:
	kमुक्त(picker);
	वापस err;
पूर्ण

अटल काष्ठा mlxsw_afk_key_info *
mlxsw_afk_key_info_create(काष्ठा mlxsw_afk *mlxsw_afk,
			  काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	काष्ठा mlxsw_afk_key_info *key_info;
	पूर्णांक err;

	key_info = kzalloc(काष्ठा_size(key_info, blocks, mlxsw_afk->max_blocks),
			   GFP_KERNEL);
	अगर (!key_info)
		वापस ERR_PTR(-ENOMEM);
	err = mlxsw_afk_picker(mlxsw_afk, key_info, elusage);
	अगर (err)
		जाओ err_picker;
	list_add(&key_info->list, &mlxsw_afk->key_info_list);
	key_info->ref_count = 1;
	वापस key_info;

err_picker:
	kमुक्त(key_info);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_afk_key_info_destroy(काष्ठा mlxsw_afk_key_info *key_info)
अणु
	list_del(&key_info->list);
	kमुक्त(key_info);
पूर्ण

काष्ठा mlxsw_afk_key_info *
mlxsw_afk_key_info_get(काष्ठा mlxsw_afk *mlxsw_afk,
		       काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	काष्ठा mlxsw_afk_key_info *key_info;

	key_info = mlxsw_afk_key_info_find(mlxsw_afk, elusage);
	अगर (key_info) अणु
		key_info->ref_count++;
		वापस key_info;
	पूर्ण
	वापस mlxsw_afk_key_info_create(mlxsw_afk, elusage);
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_key_info_get);

व्योम mlxsw_afk_key_info_put(काष्ठा mlxsw_afk_key_info *key_info)
अणु
	अगर (--key_info->ref_count)
		वापस;
	mlxsw_afk_key_info_destroy(key_info);
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_key_info_put);

bool mlxsw_afk_key_info_subset(काष्ठा mlxsw_afk_key_info *key_info,
			       काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	वापस mlxsw_afk_element_usage_subset(elusage, &key_info->elusage);
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_key_info_subset);

अटल स्थिर काष्ठा mlxsw_afk_element_inst *
mlxsw_afk_block_elinst_get(स्थिर काष्ठा mlxsw_afk_block *block,
			   क्रमागत mlxsw_afk_element element)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < block->instances_count; i++) अणु
		काष्ठा mlxsw_afk_element_inst *elinst;

		elinst = &block->instances[i];
		अगर (elinst->element == element)
			वापस elinst;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा mlxsw_afk_element_inst *
mlxsw_afk_key_info_elinst_get(काष्ठा mlxsw_afk_key_info *key_info,
			      क्रमागत mlxsw_afk_element element,
			      पूर्णांक *p_block_index)
अणु
	स्थिर काष्ठा mlxsw_afk_element_inst *elinst;
	स्थिर काष्ठा mlxsw_afk_block *block;
	पूर्णांक block_index;

	अगर (WARN_ON(!test_bit(element, key_info->elusage.usage)))
		वापस शून्य;
	block_index = key_info->element_to_block[element];
	block = key_info->blocks[block_index];

	elinst = mlxsw_afk_block_elinst_get(block, element);
	अगर (WARN_ON(!elinst))
		वापस शून्य;

	*p_block_index = block_index;
	वापस elinst;
पूर्ण

u16
mlxsw_afk_key_info_block_encoding_get(स्थिर काष्ठा mlxsw_afk_key_info *key_info,
				      पूर्णांक block_index)
अणु
	वापस key_info->blocks[block_index]->encoding;
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_key_info_block_encoding_get);

अचिन्हित पूर्णांक
mlxsw_afk_key_info_blocks_count_get(स्थिर काष्ठा mlxsw_afk_key_info *key_info)
अणु
	वापस key_info->blocks_count;
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_key_info_blocks_count_get);

व्योम mlxsw_afk_values_add_u32(काष्ठा mlxsw_afk_element_values *values,
			      क्रमागत mlxsw_afk_element element,
			      u32 key_value, u32 mask_value)
अणु
	स्थिर काष्ठा mlxsw_afk_element_info *elinfo =
				&mlxsw_afk_element_infos[element];
	स्थिर काष्ठा mlxsw_item *storage_item = &elinfo->item;

	अगर (!mask_value)
		वापस;
	अगर (WARN_ON(elinfo->type != MLXSW_AFK_ELEMENT_TYPE_U32))
		वापस;
	__mlxsw_item_set32(values->storage.key, storage_item, 0, key_value);
	__mlxsw_item_set32(values->storage.mask, storage_item, 0, mask_value);
	mlxsw_afk_element_usage_add(&values->elusage, element);
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_values_add_u32);

व्योम mlxsw_afk_values_add_buf(काष्ठा mlxsw_afk_element_values *values,
			      क्रमागत mlxsw_afk_element element,
			      स्थिर अक्षर *key_value, स्थिर अक्षर *mask_value,
			      अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा mlxsw_afk_element_info *elinfo =
				&mlxsw_afk_element_infos[element];
	स्थिर काष्ठा mlxsw_item *storage_item = &elinfo->item;

	अगर (!स_प्रथम_inv(mask_value, 0, len)) /* If mask is zero */
		वापस;
	अगर (WARN_ON(elinfo->type != MLXSW_AFK_ELEMENT_TYPE_BUF) ||
	    WARN_ON(elinfo->item.size.bytes != len))
		वापस;
	__mlxsw_item_स_नकल_to(values->storage.key, key_value,
			       storage_item, 0);
	__mlxsw_item_स_नकल_to(values->storage.mask, mask_value,
			       storage_item, 0);
	mlxsw_afk_element_usage_add(&values->elusage, element);
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_values_add_buf);

अटल व्योम mlxsw_sp_afk_encode_u32(स्थिर काष्ठा mlxsw_item *storage_item,
				    स्थिर काष्ठा mlxsw_item *output_item,
				    अक्षर *storage, अक्षर *output, पूर्णांक dअगरf)
अणु
	u32 value;

	value = __mlxsw_item_get32(storage, storage_item, 0);
	__mlxsw_item_set32(output, output_item, 0, value + dअगरf);
पूर्ण

अटल व्योम mlxsw_sp_afk_encode_buf(स्थिर काष्ठा mlxsw_item *storage_item,
				    स्थिर काष्ठा mlxsw_item *output_item,
				    अक्षर *storage, अक्षर *output)
अणु
	अक्षर *storage_data = __mlxsw_item_data(storage, storage_item, 0);
	अक्षर *output_data = __mlxsw_item_data(output, output_item, 0);
	माप_प्रकार len = output_item->size.bytes;

	स_नकल(output_data, storage_data, len);
पूर्ण

अटल व्योम
mlxsw_sp_afk_encode_one(स्थिर काष्ठा mlxsw_afk_element_inst *elinst,
			अक्षर *output, अक्षर *storage, पूर्णांक u32_dअगरf)
अणु
	स्थिर काष्ठा mlxsw_item *output_item = &elinst->item;
	स्थिर काष्ठा mlxsw_afk_element_info *elinfo;
	स्थिर काष्ठा mlxsw_item *storage_item;

	elinfo = &mlxsw_afk_element_infos[elinst->element];
	storage_item = &elinfo->item;
	अगर (elinst->type == MLXSW_AFK_ELEMENT_TYPE_U32)
		mlxsw_sp_afk_encode_u32(storage_item, output_item,
					storage, output, u32_dअगरf);
	अन्यथा अगर (elinst->type == MLXSW_AFK_ELEMENT_TYPE_BUF)
		mlxsw_sp_afk_encode_buf(storage_item, output_item,
					storage, output);
पूर्ण

#घोषणा MLXSW_SP_AFK_KEY_BLOCK_MAX_SIZE 16

व्योम mlxsw_afk_encode(काष्ठा mlxsw_afk *mlxsw_afk,
		      काष्ठा mlxsw_afk_key_info *key_info,
		      काष्ठा mlxsw_afk_element_values *values,
		      अक्षर *key, अक्षर *mask)
अणु
	अचिन्हित पूर्णांक blocks_count =
			mlxsw_afk_key_info_blocks_count_get(key_info);
	अक्षर block_mask[MLXSW_SP_AFK_KEY_BLOCK_MAX_SIZE];
	अक्षर block_key[MLXSW_SP_AFK_KEY_BLOCK_MAX_SIZE];
	स्थिर काष्ठा mlxsw_afk_element_inst *elinst;
	क्रमागत mlxsw_afk_element element;
	पूर्णांक block_index, i;

	क्रम (i = 0; i < blocks_count; i++) अणु
		स_रखो(block_key, 0, MLXSW_SP_AFK_KEY_BLOCK_MAX_SIZE);
		स_रखो(block_mask, 0, MLXSW_SP_AFK_KEY_BLOCK_MAX_SIZE);

		mlxsw_afk_element_usage_क्रम_each(element, &values->elusage) अणु
			elinst = mlxsw_afk_key_info_elinst_get(key_info,
							       element,
							       &block_index);
			अगर (!elinst || block_index != i)
				जारी;

			mlxsw_sp_afk_encode_one(elinst, block_key,
						values->storage.key,
						elinst->u32_key_dअगरf);
			mlxsw_sp_afk_encode_one(elinst, block_mask,
						values->storage.mask, 0);
		पूर्ण

		mlxsw_afk->ops->encode_block(key, i, block_key);
		mlxsw_afk->ops->encode_block(mask, i, block_mask);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_encode);

व्योम mlxsw_afk_clear(काष्ठा mlxsw_afk *mlxsw_afk, अक्षर *key,
		     पूर्णांक block_start, पूर्णांक block_end)
अणु
	पूर्णांक i;

	क्रम (i = block_start; i <= block_end; i++)
		mlxsw_afk->ops->clear_block(key, i);
पूर्ण
EXPORT_SYMBOL(mlxsw_afk_clear);
