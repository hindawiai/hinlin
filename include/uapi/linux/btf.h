<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* Copyright (c) 2018 Facebook */
#अगर_अघोषित _UAPI__LINUX_BTF_H__
#घोषणा _UAPI__LINUX_BTF_H__

#समावेश <linux/types.h>

#घोषणा BTF_MAGIC	0xeB9F
#घोषणा BTF_VERSION	1

काष्ठा btf_header अणु
	__u16	magic;
	__u8	version;
	__u8	flags;
	__u32	hdr_len;

	/* All offsets are in bytes relative to the end of this header */
	__u32	type_off;	/* offset of type section	*/
	__u32	type_len;	/* length of type section	*/
	__u32	str_off;	/* offset of string section	*/
	__u32	str_len;	/* length of string section	*/
पूर्ण;

/* Max # of type identअगरier */
#घोषणा BTF_MAX_TYPE	0x000fffff
/* Max offset पूर्णांकo the string section */
#घोषणा BTF_MAX_NAME_OFFSET	0x00ffffff
/* Max # of काष्ठा/जोड़/क्रमागत members or func args */
#घोषणा BTF_MAX_VLEN	0xffff

काष्ठा btf_type अणु
	__u32 name_off;
	/* "info" bits arrangement
	 * bits  0-15: vlen (e.g. # of काष्ठा's members)
	 * bits 16-23: unused
	 * bits 24-27: kind (e.g. पूर्णांक, ptr, array...etc)
	 * bits 28-30: unused
	 * bit     31: kind_flag, currently used by
	 *             काष्ठा, जोड़ and fwd
	 */
	__u32 info;
	/* "size" is used by INT, ENUM, STRUCT, UNION and DATASEC.
	 * "size" tells the size of the type it is describing.
	 *
	 * "type" is used by PTR, TYPEDEF, VOLATILE, CONST, RESTRICT,
	 * FUNC, FUNC_PROTO and VAR.
	 * "type" is a type_id referring to another type.
	 */
	जोड़ अणु
		__u32 size;
		__u32 type;
	पूर्ण;
पूर्ण;

#घोषणा BTF_INFO_KIND(info)	(((info) >> 24) & 0x1f)
#घोषणा BTF_INFO_VLEN(info)	((info) & 0xffff)
#घोषणा BTF_INFO_KFLAG(info)	((info) >> 31)

#घोषणा BTF_KIND_UNKN		0	/* Unknown	*/
#घोषणा BTF_KIND_INT		1	/* Integer	*/
#घोषणा BTF_KIND_PTR		2	/* Poपूर्णांकer	*/
#घोषणा BTF_KIND_ARRAY		3	/* Array	*/
#घोषणा BTF_KIND_STRUCT		4	/* Struct	*/
#घोषणा BTF_KIND_UNION		5	/* Union	*/
#घोषणा BTF_KIND_ENUM		6	/* Enumeration	*/
#घोषणा BTF_KIND_FWD		7	/* Forward	*/
#घोषणा BTF_KIND_TYPEDEF	8	/* Typedef	*/
#घोषणा BTF_KIND_VOLATILE	9	/* Volatile	*/
#घोषणा BTF_KIND_CONST		10	/* Const	*/
#घोषणा BTF_KIND_RESTRICT	11	/* Restrict	*/
#घोषणा BTF_KIND_FUNC		12	/* Function	*/
#घोषणा BTF_KIND_FUNC_PROTO	13	/* Function Proto	*/
#घोषणा BTF_KIND_VAR		14	/* Variable	*/
#घोषणा BTF_KIND_DATASEC	15	/* Section	*/
#घोषणा BTF_KIND_FLOAT		16	/* Floating poपूर्णांक	*/
#घोषणा BTF_KIND_MAX		BTF_KIND_FLOAT
#घोषणा NR_BTF_KINDS		(BTF_KIND_MAX + 1)

/* For some specअगरic BTF_KIND, "struct btf_type" is immediately
 * followed by extra data.
 */

/* BTF_KIND_INT is followed by a u32 and the following
 * is the 32 bits arrangement:
 */
#घोषणा BTF_INT_ENCODING(VAL)	(((VAL) & 0x0f000000) >> 24)
#घोषणा BTF_INT_OFFSET(VAL)	(((VAL) & 0x00ff0000) >> 16)
#घोषणा BTF_INT_BITS(VAL)	((VAL)  & 0x000000ff)

/* Attributes stored in the BTF_INT_ENCODING */
#घोषणा BTF_INT_SIGNED	(1 << 0)
#घोषणा BTF_INT_CHAR	(1 << 1)
#घोषणा BTF_INT_BOOL	(1 << 2)

/* BTF_KIND_ENUM is followed by multiple "struct btf_enum".
 * The exact number of btf_क्रमागत is stored in the vlen (of the
 * info in "struct btf_type").
 */
काष्ठा btf_क्रमागत अणु
	__u32	name_off;
	__s32	val;
पूर्ण;

/* BTF_KIND_ARRAY is followed by one "struct btf_array" */
काष्ठा btf_array अणु
	__u32	type;
	__u32	index_type;
	__u32	nelems;
पूर्ण;

/* BTF_KIND_STRUCT and BTF_KIND_UNION are followed
 * by multiple "struct btf_member".  The exact number
 * of btf_member is stored in the vlen (of the info in
 * "struct btf_type").
 */
काष्ठा btf_member अणु
	__u32	name_off;
	__u32	type;
	/* If the type info kind_flag is set, the btf_member offset
	 * contains both member bitfield size and bit offset. The
	 * bitfield size is set क्रम bitfield members. If the type
	 * info kind_flag is not set, the offset contains only bit
	 * offset.
	 */
	__u32	offset;
पूर्ण;

/* If the काष्ठा/जोड़ type info kind_flag is set, the
 * following two macros are used to access bitfield_size
 * and bit_offset from btf_member.offset.
 */
#घोषणा BTF_MEMBER_BITFIELD_SIZE(val)	((val) >> 24)
#घोषणा BTF_MEMBER_BIT_OFFSET(val)	((val) & 0xffffff)

/* BTF_KIND_FUNC_PROTO is followed by multiple "struct btf_param".
 * The exact number of btf_param is stored in the vlen (of the
 * info in "struct btf_type").
 */
काष्ठा btf_param अणु
	__u32	name_off;
	__u32	type;
पूर्ण;

क्रमागत अणु
	BTF_VAR_STATIC = 0,
	BTF_VAR_GLOBAL_ALLOCATED = 1,
	BTF_VAR_GLOBAL_EXTERN = 2,
पूर्ण;

क्रमागत btf_func_linkage अणु
	BTF_FUNC_STATIC = 0,
	BTF_FUNC_GLOBAL = 1,
	BTF_FUNC_EXTERN = 2,
पूर्ण;

/* BTF_KIND_VAR is followed by a single "struct btf_var" to describe
 * additional inक्रमmation related to the variable such as its linkage.
 */
काष्ठा btf_var अणु
	__u32	linkage;
पूर्ण;

/* BTF_KIND_DATASEC is followed by multiple "struct btf_var_secinfo"
 * to describe all BTF_KIND_VAR types it contains aदीर्घ with it's
 * in-section offset as well as size.
 */
काष्ठा btf_var_secinfo अणु
	__u32	type;
	__u32	offset;
	__u32	size;
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_BTF_H__ */
