<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_CORE_ACL_FLEX_KEYS_H
#घोषणा _MLXSW_CORE_ACL_FLEX_KEYS_H

#समावेश <linux/types.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "item.h"

क्रमागत mlxsw_afk_element अणु
	MLXSW_AFK_ELEMENT_SRC_SYS_PORT,
	MLXSW_AFK_ELEMENT_DMAC_32_47,
	MLXSW_AFK_ELEMENT_DMAC_0_31,
	MLXSW_AFK_ELEMENT_SMAC_32_47,
	MLXSW_AFK_ELEMENT_SMAC_0_31,
	MLXSW_AFK_ELEMENT_ETHERTYPE,
	MLXSW_AFK_ELEMENT_IP_PROTO,
	MLXSW_AFK_ELEMENT_SRC_IP_96_127,
	MLXSW_AFK_ELEMENT_SRC_IP_64_95,
	MLXSW_AFK_ELEMENT_SRC_IP_32_63,
	MLXSW_AFK_ELEMENT_SRC_IP_0_31,
	MLXSW_AFK_ELEMENT_DST_IP_96_127,
	MLXSW_AFK_ELEMENT_DST_IP_64_95,
	MLXSW_AFK_ELEMENT_DST_IP_32_63,
	MLXSW_AFK_ELEMENT_DST_IP_0_31,
	MLXSW_AFK_ELEMENT_DST_L4_PORT,
	MLXSW_AFK_ELEMENT_SRC_L4_PORT,
	MLXSW_AFK_ELEMENT_VID,
	MLXSW_AFK_ELEMENT_PCP,
	MLXSW_AFK_ELEMENT_TCP_FLAGS,
	MLXSW_AFK_ELEMENT_IP_TTL_,
	MLXSW_AFK_ELEMENT_IP_ECN,
	MLXSW_AFK_ELEMENT_IP_DSCP,
	MLXSW_AFK_ELEMENT_VIRT_ROUTER_8_10,
	MLXSW_AFK_ELEMENT_VIRT_ROUTER_0_7,
	MLXSW_AFK_ELEMENT_MAX,
पूर्ण;

क्रमागत mlxsw_afk_element_type अणु
	MLXSW_AFK_ELEMENT_TYPE_U32,
	MLXSW_AFK_ELEMENT_TYPE_BUF,
पूर्ण;

काष्ठा mlxsw_afk_element_info अणु
	क्रमागत mlxsw_afk_element element; /* element ID */
	क्रमागत mlxsw_afk_element_type type;
	काष्ठा mlxsw_item item; /* element geometry in पूर्णांकernal storage */
पूर्ण;

#घोषणा MLXSW_AFK_ELEMENT_INFO(_type, _element, _offset, _shअगरt, _size)		\
	[MLXSW_AFK_ELEMENT_##_element] = अणु					\
		.element = MLXSW_AFK_ELEMENT_##_element,			\
		.type = _type,							\
		.item = अणु							\
			.offset = _offset,					\
			.shअगरt = _shअगरt,					\
			.size = अणु.bits = _sizeपूर्ण,				\
			.name = #_element,					\
		पूर्ण,								\
	पूर्ण

#घोषणा MLXSW_AFK_ELEMENT_INFO_U32(_element, _offset, _shअगरt, _size)		\
	MLXSW_AFK_ELEMENT_INFO(MLXSW_AFK_ELEMENT_TYPE_U32,			\
			       _element, _offset, _shअगरt, _size)

#घोषणा MLXSW_AFK_ELEMENT_INFO_BUF(_element, _offset, _size)			\
	MLXSW_AFK_ELEMENT_INFO(MLXSW_AFK_ELEMENT_TYPE_BUF,			\
			       _element, _offset, 0, _size)

#घोषणा MLXSW_AFK_ELEMENT_STORAGE_SIZE 0x40

काष्ठा mlxsw_afk_element_inst अणु /* element instance in actual block */
	क्रमागत mlxsw_afk_element element;
	क्रमागत mlxsw_afk_element_type type;
	काष्ठा mlxsw_item item; /* element geometry in block */
	पूर्णांक u32_key_dअगरf; /* in हाल value needs to be adjusted beक्रमe ग_लिखो
			   * this dअगरf is here to handle that
			   */
	bool aव्योम_size_check;
पूर्ण;

#घोषणा MLXSW_AFK_ELEMENT_INST(_type, _element, _offset,			\
			       _shअगरt, _size, _u32_key_dअगरf, _aव्योम_size_check)	\
	अणु									\
		.element = MLXSW_AFK_ELEMENT_##_element,			\
		.type = _type,							\
		.item = अणु							\
			.offset = _offset,					\
			.shअगरt = _shअगरt,					\
			.size = अणु.bits = _sizeपूर्ण,				\
			.name = #_element,					\
		पूर्ण,								\
		.u32_key_dअगरf = _u32_key_dअगरf,					\
		.aव्योम_size_check = _aव्योम_size_check,				\
	पूर्ण

#घोषणा MLXSW_AFK_ELEMENT_INST_U32(_element, _offset, _shअगरt, _size)		\
	MLXSW_AFK_ELEMENT_INST(MLXSW_AFK_ELEMENT_TYPE_U32,			\
			       _element, _offset, _shअगरt, _size, 0, false)

#घोषणा MLXSW_AFK_ELEMENT_INST_EXT_U32(_element, _offset,			\
				       _shअगरt, _size, _key_dअगरf,		\
				       _aव्योम_size_check)			\
	MLXSW_AFK_ELEMENT_INST(MLXSW_AFK_ELEMENT_TYPE_U32,			\
			       _element, _offset, _shअगरt, _size,		\
			       _key_dअगरf, _aव्योम_size_check)

#घोषणा MLXSW_AFK_ELEMENT_INST_BUF(_element, _offset, _size)			\
	MLXSW_AFK_ELEMENT_INST(MLXSW_AFK_ELEMENT_TYPE_BUF,			\
			       _element, _offset, 0, _size, 0, false)

काष्ठा mlxsw_afk_block अणु
	u16 encoding; /* block ID */
	काष्ठा mlxsw_afk_element_inst *instances;
	अचिन्हित पूर्णांक instances_count;
पूर्ण;

#घोषणा MLXSW_AFK_BLOCK(_encoding, _instances)					\
	अणु									\
		.encoding = _encoding,						\
		.instances = _instances,					\
		.instances_count = ARRAY_SIZE(_instances),			\
	पूर्ण

काष्ठा mlxsw_afk_element_usage अणु
	DECLARE_BITMAP(usage, MLXSW_AFK_ELEMENT_MAX);
पूर्ण;

#घोषणा mlxsw_afk_element_usage_क्रम_each(element, elusage)			\
	क्रम_each_set_bit(element, (elusage)->usage, MLXSW_AFK_ELEMENT_MAX)

अटल अंतरभूत व्योम
mlxsw_afk_element_usage_add(काष्ठा mlxsw_afk_element_usage *elusage,
			    क्रमागत mlxsw_afk_element element)
अणु
	__set_bit(element, elusage->usage);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_afk_element_usage_zero(काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	biपंचांगap_zero(elusage->usage, MLXSW_AFK_ELEMENT_MAX);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_afk_element_usage_fill(काष्ठा mlxsw_afk_element_usage *elusage,
			     स्थिर क्रमागत mlxsw_afk_element *elements,
			     अचिन्हित पूर्णांक elements_count)
अणु
	पूर्णांक i;

	mlxsw_afk_element_usage_zero(elusage);
	क्रम (i = 0; i < elements_count; i++)
		mlxsw_afk_element_usage_add(elusage, elements[i]);
पूर्ण

अटल अंतरभूत bool
mlxsw_afk_element_usage_subset(काष्ठा mlxsw_afk_element_usage *elusage_small,
			       काष्ठा mlxsw_afk_element_usage *elusage_big)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_AFK_ELEMENT_MAX; i++)
		अगर (test_bit(i, elusage_small->usage) &&
		    !test_bit(i, elusage_big->usage))
			वापस false;
	वापस true;
पूर्ण

काष्ठा mlxsw_afk;

काष्ठा mlxsw_afk_ops अणु
	स्थिर काष्ठा mlxsw_afk_block *blocks;
	अचिन्हित पूर्णांक blocks_count;
	व्योम (*encode_block)(अक्षर *output, पूर्णांक block_index, अक्षर *block);
	व्योम (*clear_block)(अक्षर *output, पूर्णांक block_index);
पूर्ण;

काष्ठा mlxsw_afk *mlxsw_afk_create(अचिन्हित पूर्णांक max_blocks,
				   स्थिर काष्ठा mlxsw_afk_ops *ops);
व्योम mlxsw_afk_destroy(काष्ठा mlxsw_afk *mlxsw_afk);

काष्ठा mlxsw_afk_key_info;

काष्ठा mlxsw_afk_key_info *
mlxsw_afk_key_info_get(काष्ठा mlxsw_afk *mlxsw_afk,
		       काष्ठा mlxsw_afk_element_usage *elusage);
व्योम mlxsw_afk_key_info_put(काष्ठा mlxsw_afk_key_info *key_info);
bool mlxsw_afk_key_info_subset(काष्ठा mlxsw_afk_key_info *key_info,
			       काष्ठा mlxsw_afk_element_usage *elusage);

u16
mlxsw_afk_key_info_block_encoding_get(स्थिर काष्ठा mlxsw_afk_key_info *key_info,
				      पूर्णांक block_index);
अचिन्हित पूर्णांक
mlxsw_afk_key_info_blocks_count_get(स्थिर काष्ठा mlxsw_afk_key_info *key_info);

काष्ठा mlxsw_afk_element_values अणु
	काष्ठा mlxsw_afk_element_usage elusage;
	काष्ठा अणु
		अक्षर key[MLXSW_AFK_ELEMENT_STORAGE_SIZE];
		अक्षर mask[MLXSW_AFK_ELEMENT_STORAGE_SIZE];
	पूर्ण storage;
पूर्ण;

व्योम mlxsw_afk_values_add_u32(काष्ठा mlxsw_afk_element_values *values,
			      क्रमागत mlxsw_afk_element element,
			      u32 key_value, u32 mask_value);
व्योम mlxsw_afk_values_add_buf(काष्ठा mlxsw_afk_element_values *values,
			      क्रमागत mlxsw_afk_element element,
			      स्थिर अक्षर *key_value, स्थिर अक्षर *mask_value,
			      अचिन्हित पूर्णांक len);
व्योम mlxsw_afk_encode(काष्ठा mlxsw_afk *mlxsw_afk,
		      काष्ठा mlxsw_afk_key_info *key_info,
		      काष्ठा mlxsw_afk_element_values *values,
		      अक्षर *key, अक्षर *mask);
व्योम mlxsw_afk_clear(काष्ठा mlxsw_afk *mlxsw_afk, अक्षर *key,
		     पूर्णांक block_start, पूर्णांक block_end);

#पूर्ण_अगर
