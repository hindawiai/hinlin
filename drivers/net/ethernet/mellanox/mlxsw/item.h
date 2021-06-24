<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_ITEM_H
#घोषणा _MLXSW_ITEM_H

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>

काष्ठा mlxsw_item अणु
	अचिन्हित लघु	offset;		/* bytes in container */
	लघु		step;		/* step in bytes क्रम indexed items */
	अचिन्हित लघु	in_step_offset; /* offset within one step */
	अचिन्हित अक्षर	shअगरt;		/* shअगरt in bits */
	अचिन्हित अक्षर	element_size;	/* size of element in bit array */
	bool		no_real_shअगरt;
	जोड़ अणु
		अचिन्हित अक्षर	bits;
		अचिन्हित लघु	bytes;
	पूर्ण size;
	स्थिर अक्षर	*name;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक
__mlxsw_item_offset(स्थिर काष्ठा mlxsw_item *item, अचिन्हित लघु index,
		    माप_प्रकार typesize)
अणु
	BUG_ON(index && !item->step);
	अगर (item->offset % typesize != 0 ||
	    item->step % typesize != 0 ||
	    item->in_step_offset % typesize != 0) अणु
		pr_err("mlxsw: item bug (name=%s,offset=%x,step=%x,in_step_offset=%x,typesize=%zx)\n",
		       item->name, item->offset, item->step,
		       item->in_step_offset, typesize);
		BUG();
	पूर्ण

	वापस ((item->offset + item->step * index + item->in_step_offset) /
		typesize);
पूर्ण

अटल अंतरभूत u8 __mlxsw_item_get8(स्थिर अक्षर *buf,
				   स्थिर काष्ठा mlxsw_item *item,
				   अचिन्हित लघु index)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index, माप(u8));
	u8 *b = (u8 *) buf;
	u8 पंचांगp;

	पंचांगp = b[offset];
	पंचांगp >>= item->shअगरt;
	पंचांगp &= GENMASK(item->size.bits - 1, 0);
	अगर (item->no_real_shअगरt)
		पंचांगp <<= item->shअगरt;
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम __mlxsw_item_set8(अक्षर *buf, स्थिर काष्ठा mlxsw_item *item,
				     अचिन्हित लघु index, u8 val)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index,
						  माप(u8));
	u8 *b = (u8 *) buf;
	u8 mask = GENMASK(item->size.bits - 1, 0) << item->shअगरt;
	u8 पंचांगp;

	अगर (!item->no_real_shअगरt)
		val <<= item->shअगरt;
	val &= mask;
	पंचांगp = b[offset];
	पंचांगp &= ~mask;
	पंचांगp |= val;
	b[offset] = पंचांगp;
पूर्ण

अटल अंतरभूत u16 __mlxsw_item_get16(स्थिर अक्षर *buf,
				     स्थिर काष्ठा mlxsw_item *item,
				     अचिन्हित लघु index)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index, माप(u16));
	__be16 *b = (__be16 *) buf;
	u16 पंचांगp;

	पंचांगp = be16_to_cpu(b[offset]);
	पंचांगp >>= item->shअगरt;
	पंचांगp &= GENMASK(item->size.bits - 1, 0);
	अगर (item->no_real_shअगरt)
		पंचांगp <<= item->shअगरt;
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम __mlxsw_item_set16(अक्षर *buf, स्थिर काष्ठा mlxsw_item *item,
				      अचिन्हित लघु index, u16 val)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index,
						  माप(u16));
	__be16 *b = (__be16 *) buf;
	u16 mask = GENMASK(item->size.bits - 1, 0) << item->shअगरt;
	u16 पंचांगp;

	अगर (!item->no_real_shअगरt)
		val <<= item->shअगरt;
	val &= mask;
	पंचांगp = be16_to_cpu(b[offset]);
	पंचांगp &= ~mask;
	पंचांगp |= val;
	b[offset] = cpu_to_be16(पंचांगp);
पूर्ण

अटल अंतरभूत u32 __mlxsw_item_get32(स्थिर अक्षर *buf,
				     स्थिर काष्ठा mlxsw_item *item,
				     अचिन्हित लघु index)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index, माप(u32));
	__be32 *b = (__be32 *) buf;
	u32 पंचांगp;

	पंचांगp = be32_to_cpu(b[offset]);
	पंचांगp >>= item->shअगरt;
	पंचांगp &= GENMASK(item->size.bits - 1, 0);
	अगर (item->no_real_shअगरt)
		पंचांगp <<= item->shअगरt;
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम __mlxsw_item_set32(अक्षर *buf, स्थिर काष्ठा mlxsw_item *item,
				      अचिन्हित लघु index, u32 val)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index,
						  माप(u32));
	__be32 *b = (__be32 *) buf;
	u32 mask = GENMASK(item->size.bits - 1, 0) << item->shअगरt;
	u32 पंचांगp;

	अगर (!item->no_real_shअगरt)
		val <<= item->shअगरt;
	val &= mask;
	पंचांगp = be32_to_cpu(b[offset]);
	पंचांगp &= ~mask;
	पंचांगp |= val;
	b[offset] = cpu_to_be32(पंचांगp);
पूर्ण

अटल अंतरभूत u64 __mlxsw_item_get64(स्थिर अक्षर *buf,
				     स्थिर काष्ठा mlxsw_item *item,
				     अचिन्हित लघु index)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index, माप(u64));
	__be64 *b = (__be64 *) buf;
	u64 पंचांगp;

	पंचांगp = be64_to_cpu(b[offset]);
	पंचांगp >>= item->shअगरt;
	पंचांगp &= GENMASK_ULL(item->size.bits - 1, 0);
	अगर (item->no_real_shअगरt)
		पंचांगp <<= item->shअगरt;
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम __mlxsw_item_set64(अक्षर *buf, स्थिर काष्ठा mlxsw_item *item,
				      अचिन्हित लघु index, u64 val)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index, माप(u64));
	__be64 *b = (__be64 *) buf;
	u64 mask = GENMASK_ULL(item->size.bits - 1, 0) << item->shअगरt;
	u64 पंचांगp;

	अगर (!item->no_real_shअगरt)
		val <<= item->shअगरt;
	val &= mask;
	पंचांगp = be64_to_cpu(b[offset]);
	पंचांगp &= ~mask;
	पंचांगp |= val;
	b[offset] = cpu_to_be64(पंचांगp);
पूर्ण

अटल अंतरभूत व्योम __mlxsw_item_स_नकल_from(स्थिर अक्षर *buf, अक्षर *dst,
					    स्थिर काष्ठा mlxsw_item *item,
					    अचिन्हित लघु index)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index, माप(अक्षर));

	स_नकल(dst, &buf[offset], item->size.bytes);
पूर्ण

अटल अंतरभूत व्योम __mlxsw_item_स_नकल_to(अक्षर *buf, स्थिर अक्षर *src,
					  स्थिर काष्ठा mlxsw_item *item,
					  अचिन्हित लघु index)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index, माप(अक्षर));

	स_नकल(&buf[offset], src, item->size.bytes);
पूर्ण

अटल अंतरभूत अक्षर *__mlxsw_item_data(अक्षर *buf, स्थिर काष्ठा mlxsw_item *item,
				      अचिन्हित लघु index)
अणु
	अचिन्हित पूर्णांक offset = __mlxsw_item_offset(item, index, माप(अक्षर));

	वापस &buf[offset];
पूर्ण

अटल अंतरभूत u16
__mlxsw_item_bit_array_offset(स्थिर काष्ठा mlxsw_item *item,
			      u16 index, u8 *shअगरt)
अणु
	u16 max_index, be_index;
	u16 offset;		/* byte offset inside the array */
	u8 in_byte_index;

	BUG_ON(index && !item->element_size);
	अगर (item->offset % माप(u32) != 0 ||
	    BITS_PER_BYTE % item->element_size != 0) अणु
		pr_err("mlxsw: item bug (name=%s,offset=%x,element_size=%x)\n",
		       item->name, item->offset, item->element_size);
		BUG();
	पूर्ण

	max_index = (item->size.bytes << 3) / item->element_size - 1;
	be_index = max_index - index;
	offset = be_index * item->element_size >> 3;
	in_byte_index  = index % (BITS_PER_BYTE / item->element_size);
	*shअगरt = in_byte_index * item->element_size;

	वापस item->offset + offset;
पूर्ण

अटल अंतरभूत u8 __mlxsw_item_bit_array_get(स्थिर अक्षर *buf,
					    स्थिर काष्ठा mlxsw_item *item,
					    u16 index)
अणु
	u8 shअगरt, पंचांगp;
	u16 offset = __mlxsw_item_bit_array_offset(item, index, &shअगरt);

	पंचांगp = buf[offset];
	पंचांगp >>= shअगरt;
	पंचांगp &= GENMASK(item->element_size - 1, 0);
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम __mlxsw_item_bit_array_set(अक्षर *buf,
					      स्थिर काष्ठा mlxsw_item *item,
					      u16 index, u8 val)
अणु
	u8 shअगरt, पंचांगp;
	u16 offset = __mlxsw_item_bit_array_offset(item, index, &shअगरt);
	u8 mask = GENMASK(item->element_size - 1, 0) << shअगरt;

	val <<= shअगरt;
	val &= mask;
	पंचांगp = buf[offset];
	पंचांगp &= ~mask;
	पंचांगp |= val;
	buf[offset] = पंचांगp;
पूर्ण

#घोषणा __ITEM_NAME(_type, _cname, _iname)					\
	mlxsw_##_type##_##_cname##_##_iname##_item

/* _type: cmd_mbox, reg, etc.
 * _cname: contaपूर्णांकer name (e.g. command name, रेजिस्टर name)
 * _iname: item name within the container
 */

#घोषणा MLXSW_ITEM8(_type, _cname, _iname, _offset, _shअगरt, _sizebits)		\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.shअगरt = _shअगरt,							\
	.size = अणु.bits = _sizebits,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत u8 mlxsw_##_type##_##_cname##_##_iname##_get(स्थिर अक्षर *buf)	\
अणु										\
	वापस __mlxsw_item_get8(buf, &__ITEM_NAME(_type, _cname, _iname), 0);	\
पूर्ण										\
अटल अंतरभूत व्योम mlxsw_##_type##_##_cname##_##_iname##_set(अक्षर *buf, u8 val)\
अणु										\
	__mlxsw_item_set8(buf, &__ITEM_NAME(_type, _cname, _iname), 0, val);	\
पूर्ण

#घोषणा MLXSW_ITEM8_INDEXED(_type, _cname, _iname, _offset, _shअगरt, _sizebits,	\
			    _step, _instepoffset, _norealshअगरt)			\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.step = _step,								\
	.in_step_offset = _instepoffset,					\
	.shअगरt = _shअगरt,							\
	.no_real_shअगरt = _norealshअगरt,						\
	.size = अणु.bits = _sizebits,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत u8								\
mlxsw_##_type##_##_cname##_##_iname##_get(स्थिर अक्षर *buf, अचिन्हित लघु index)\
अणु										\
	वापस __mlxsw_item_get8(buf, &__ITEM_NAME(_type, _cname, _iname),	\
				 index);					\
पूर्ण										\
अटल अंतरभूत व्योम								\
mlxsw_##_type##_##_cname##_##_iname##_set(अक्षर *buf, अचिन्हित लघु index,	\
					  u8 val)				\
अणु										\
	__mlxsw_item_set8(buf, &__ITEM_NAME(_type, _cname, _iname),		\
			  index, val);						\
पूर्ण

#घोषणा MLXSW_ITEM16(_type, _cname, _iname, _offset, _shअगरt, _sizebits)		\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.shअगरt = _shअगरt,							\
	.size = अणु.bits = _sizebits,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत u16 mlxsw_##_type##_##_cname##_##_iname##_get(स्थिर अक्षर *buf)	\
अणु										\
	वापस __mlxsw_item_get16(buf, &__ITEM_NAME(_type, _cname, _iname), 0);	\
पूर्ण										\
अटल अंतरभूत व्योम mlxsw_##_type##_##_cname##_##_iname##_set(अक्षर *buf, u16 val)\
अणु										\
	__mlxsw_item_set16(buf, &__ITEM_NAME(_type, _cname, _iname), 0, val);	\
पूर्ण

#घोषणा MLXSW_ITEM16_INDEXED(_type, _cname, _iname, _offset, _shअगरt, _sizebits,	\
			     _step, _instepoffset, _norealshअगरt)		\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.step = _step,								\
	.in_step_offset = _instepoffset,					\
	.shअगरt = _shअगरt,							\
	.no_real_shअगरt = _norealshअगरt,						\
	.size = अणु.bits = _sizebits,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत u16								\
mlxsw_##_type##_##_cname##_##_iname##_get(स्थिर अक्षर *buf, अचिन्हित लघु index)\
अणु										\
	वापस __mlxsw_item_get16(buf, &__ITEM_NAME(_type, _cname, _iname),	\
				  index);					\
पूर्ण										\
अटल अंतरभूत व्योम								\
mlxsw_##_type##_##_cname##_##_iname##_set(अक्षर *buf, अचिन्हित लघु index,	\
					  u16 val)				\
अणु										\
	__mlxsw_item_set16(buf, &__ITEM_NAME(_type, _cname, _iname),		\
			   index, val);						\
पूर्ण

#घोषणा MLXSW_ITEM32(_type, _cname, _iname, _offset, _shअगरt, _sizebits)		\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.shअगरt = _shअगरt,							\
	.size = अणु.bits = _sizebits,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत u32 mlxsw_##_type##_##_cname##_##_iname##_get(स्थिर अक्षर *buf)	\
अणु										\
	वापस __mlxsw_item_get32(buf, &__ITEM_NAME(_type, _cname, _iname), 0);	\
पूर्ण										\
अटल अंतरभूत व्योम mlxsw_##_type##_##_cname##_##_iname##_set(अक्षर *buf, u32 val)\
अणु										\
	__mlxsw_item_set32(buf, &__ITEM_NAME(_type, _cname, _iname), 0, val);	\
पूर्ण

#घोषणा MLXSW_ITEM32_INDEXED(_type, _cname, _iname, _offset, _shअगरt, _sizebits,	\
			     _step, _instepoffset, _norealshअगरt)		\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.step = _step,								\
	.in_step_offset = _instepoffset,					\
	.shअगरt = _shअगरt,							\
	.no_real_shअगरt = _norealshअगरt,						\
	.size = अणु.bits = _sizebits,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत u32								\
mlxsw_##_type##_##_cname##_##_iname##_get(स्थिर अक्षर *buf, अचिन्हित लघु index)\
अणु										\
	वापस __mlxsw_item_get32(buf, &__ITEM_NAME(_type, _cname, _iname),	\
				  index);					\
पूर्ण										\
अटल अंतरभूत व्योम								\
mlxsw_##_type##_##_cname##_##_iname##_set(अक्षर *buf, अचिन्हित लघु index,	\
					  u32 val)				\
अणु										\
	__mlxsw_item_set32(buf, &__ITEM_NAME(_type, _cname, _iname),		\
			   index, val);						\
पूर्ण

#घोषणा MLXSW_ITEM64(_type, _cname, _iname, _offset, _shअगरt, _sizebits)		\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.shअगरt = _shअगरt,							\
	.size = अणु.bits = _sizebits,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत u64 mlxsw_##_type##_##_cname##_##_iname##_get(स्थिर अक्षर *buf)	\
अणु										\
	वापस __mlxsw_item_get64(buf, &__ITEM_NAME(_type, _cname, _iname), 0);	\
पूर्ण										\
अटल अंतरभूत व्योम mlxsw_##_type##_##_cname##_##_iname##_set(अक्षर *buf, u64 val)\
अणु										\
	__mlxsw_item_set64(buf, &__ITEM_NAME(_type, _cname, _iname), 0,	val);	\
पूर्ण

#घोषणा MLXSW_ITEM64_INDEXED(_type, _cname, _iname, _offset, _shअगरt,		\
			     _sizebits, _step, _instepoffset, _norealshअगरt)	\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.step = _step,								\
	.in_step_offset = _instepoffset,					\
	.shअगरt = _shअगरt,							\
	.no_real_shअगरt = _norealshअगरt,						\
	.size = अणु.bits = _sizebits,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत u64								\
mlxsw_##_type##_##_cname##_##_iname##_get(स्थिर अक्षर *buf, अचिन्हित लघु index)\
अणु										\
	वापस __mlxsw_item_get64(buf, &__ITEM_NAME(_type, _cname, _iname),	\
				  index);					\
पूर्ण										\
अटल अंतरभूत व्योम								\
mlxsw_##_type##_##_cname##_##_iname##_set(अक्षर *buf, अचिन्हित लघु index,	\
					  u64 val)				\
अणु										\
	__mlxsw_item_set64(buf, &__ITEM_NAME(_type, _cname, _iname),		\
			   index, val);						\
पूर्ण

#घोषणा MLXSW_ITEM_BUF(_type, _cname, _iname, _offset, _sizebytes)		\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.size = अणु.bytes = _sizebytes,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत व्योम								\
mlxsw_##_type##_##_cname##_##_iname##_स_नकल_from(स्थिर अक्षर *buf, अक्षर *dst)	\
अणु										\
	__mlxsw_item_स_नकल_from(buf, dst,					\
				 &__ITEM_NAME(_type, _cname, _iname), 0);	\
पूर्ण										\
अटल अंतरभूत व्योम								\
mlxsw_##_type##_##_cname##_##_iname##_स_नकल_to(अक्षर *buf, स्थिर अक्षर *src)	\
अणु										\
	__mlxsw_item_स_नकल_to(buf, src,					\
			       &__ITEM_NAME(_type, _cname, _iname), 0);		\
पूर्ण										\
अटल अंतरभूत अक्षर *								\
mlxsw_##_type##_##_cname##_##_iname##_data(अक्षर *buf)				\
अणु										\
	वापस __mlxsw_item_data(buf, &__ITEM_NAME(_type, _cname, _iname), 0);	\
पूर्ण

#घोषणा MLXSW_ITEM_BUF_INDEXED(_type, _cname, _iname, _offset, _sizebytes,	\
			       _step, _instepoffset)				\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.step = _step,								\
	.in_step_offset = _instepoffset,					\
	.size = अणु.bytes = _sizebytes,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत व्योम								\
mlxsw_##_type##_##_cname##_##_iname##_स_नकल_from(स्थिर अक्षर *buf,		\
						  अचिन्हित लघु index,		\
						  अक्षर *dst)			\
अणु										\
	__mlxsw_item_स_नकल_from(buf, dst,					\
				 &__ITEM_NAME(_type, _cname, _iname), index);	\
पूर्ण										\
अटल अंतरभूत व्योम								\
mlxsw_##_type##_##_cname##_##_iname##_स_नकल_to(अक्षर *buf,			\
						अचिन्हित लघु index,		\
						स्थिर अक्षर *src)		\
अणु										\
	__mlxsw_item_स_नकल_to(buf, src,					\
			       &__ITEM_NAME(_type, _cname, _iname), index);	\
पूर्ण										\
अटल अंतरभूत अक्षर *								\
mlxsw_##_type##_##_cname##_##_iname##_data(अक्षर *buf, अचिन्हित लघु index)	\
अणु										\
	वापस __mlxsw_item_data(buf,						\
				 &__ITEM_NAME(_type, _cname, _iname), index);	\
पूर्ण

#घोषणा MLXSW_ITEM_BIT_ARRAY(_type, _cname, _iname, _offset, _sizebytes,	\
			     _element_size)					\
अटल काष्ठा mlxsw_item __ITEM_NAME(_type, _cname, _iname) = अणु			\
	.offset = _offset,							\
	.element_size = _element_size,						\
	.size = अणु.bytes = _sizebytes,पूर्ण,						\
	.name = #_type "_" #_cname "_" #_iname,					\
पूर्ण;										\
अटल अंतरभूत u8								\
mlxsw_##_type##_##_cname##_##_iname##_get(स्थिर अक्षर *buf, u16 index)		\
अणु										\
	वापस __mlxsw_item_bit_array_get(buf,					\
					  &__ITEM_NAME(_type, _cname, _iname),	\
					  index);				\
पूर्ण										\
अटल अंतरभूत व्योम								\
mlxsw_##_type##_##_cname##_##_iname##_set(अक्षर *buf, u16 index, u8 val)		\
अणु										\
	वापस __mlxsw_item_bit_array_set(buf,					\
					  &__ITEM_NAME(_type, _cname, _iname),	\
					  index, val);				\
पूर्ण										\

#पूर्ण_अगर
