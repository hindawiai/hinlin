<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 Facebook */

#अगर_अघोषित _TEST_BTF_H
#घोषणा _TEST_BTF_H

#घोषणा BTF_INFO_ENC(kind, kind_flag, vlen)			\
	((!!(kind_flag) << 31) | ((kind) << 24) | ((vlen) & BTF_MAX_VLEN))

#घोषणा BTF_TYPE_ENC(name, info, size_or_type)	\
	(name), (info), (size_or_type)

#घोषणा BTF_INT_ENC(encoding, bits_offset, nr_bits)	\
	((encoding) << 24 | (bits_offset) << 16 | (nr_bits))
#घोषणा BTF_TYPE_INT_ENC(name, encoding, bits_offset, bits, sz)	\
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_INT, 0, 0), sz),	\
	BTF_INT_ENC(encoding, bits_offset, bits)

#घोषणा BTF_FWD_ENC(name, kind_flag) \
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_FWD, kind_flag, 0), 0)

#घोषणा BTF_ARRAY_ENC(type, index_type, nr_elems)	\
	(type), (index_type), (nr_elems)
#घोषणा BTF_TYPE_ARRAY_ENC(type, index_type, nr_elems) \
	BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ARRAY, 0, 0), 0), \
	BTF_ARRAY_ENC(type, index_type, nr_elems)

#घोषणा BTF_STRUCT_ENC(name, nr_elems, sz)	\
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, nr_elems), sz)

#घोषणा BTF_UNION_ENC(name, nr_elems, sz)	\
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_UNION, 0, nr_elems), sz)

#घोषणा BTF_VAR_ENC(name, type, linkage)	\
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_VAR, 0, 0), type), (linkage)
#घोषणा BTF_VAR_SECINFO_ENC(type, offset, size)	\
	(type), (offset), (size)

#घोषणा BTF_MEMBER_ENC(name, type, bits_offset)	\
	(name), (type), (bits_offset)
#घोषणा BTF_ENUM_ENC(name, val) (name), (val)
#घोषणा BTF_MEMBER_OFFSET(bitfield_size, bits_offset) \
	((bitfield_size) << 24 | (bits_offset))

#घोषणा BTF_TYPEDEF_ENC(name, type) \
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_TYPEDEF, 0, 0), type)

#घोषणा BTF_PTR_ENC(type) \
	BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), type)

#घोषणा BTF_CONST_ENC(type) \
	BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), type)

#घोषणा BTF_VOLATILE_ENC(type) \
	BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_VOLATILE, 0, 0), type)

#घोषणा BTF_RESTRICT_ENC(type) \
	BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_RESTRICT, 0, 0), type)

#घोषणा BTF_FUNC_PROTO_ENC(ret_type, nargs) \
	BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_FUNC_PROTO, 0, nargs), ret_type)

#घोषणा BTF_FUNC_PROTO_ARG_ENC(name, type) \
	(name), (type)

#घोषणा BTF_FUNC_ENC(name, func_proto) \
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_FUNC, 0, 0), func_proto)

#घोषणा BTF_TYPE_FLOAT_ENC(name, sz) \
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_FLOAT, 0, 0), sz)

#पूर्ण_अगर /* _TEST_BTF_H */
