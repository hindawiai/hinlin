<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */
/* Copyright (c) 2018 Facebook */

#अगर_अघोषित __LIBBPF_BTF_H
#घोषणा __LIBBPF_BTF_H

#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <linux/btf.h>
#समावेश <linux/types.h>

#समावेश "libbpf_common.h"

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा BTF_ELF_SEC ".BTF"
#घोषणा BTF_EXT_ELF_SEC ".BTF.ext"
#घोषणा MAPS_ELF_SEC ".maps"

काष्ठा btf;
काष्ठा btf_ext;
काष्ठा btf_type;

काष्ठा bpf_object;

क्रमागत btf_endianness अणु
	BTF_LITTLE_ENDIAN = 0,
	BTF_BIG_ENDIAN = 1,
पूर्ण;

LIBBPF_API व्योम btf__मुक्त(काष्ठा btf *btf);

LIBBPF_API काष्ठा btf *btf__new(स्थिर व्योम *data, __u32 size);
LIBBPF_API काष्ठा btf *btf__new_split(स्थिर व्योम *data, __u32 size, काष्ठा btf *base_btf);
LIBBPF_API काष्ठा btf *btf__new_empty(व्योम);
LIBBPF_API काष्ठा btf *btf__new_empty_split(काष्ठा btf *base_btf);

LIBBPF_API काष्ठा btf *btf__parse(स्थिर अक्षर *path, काष्ठा btf_ext **btf_ext);
LIBBPF_API काष्ठा btf *btf__parse_split(स्थिर अक्षर *path, काष्ठा btf *base_btf);
LIBBPF_API काष्ठा btf *btf__parse_elf(स्थिर अक्षर *path, काष्ठा btf_ext **btf_ext);
LIBBPF_API काष्ठा btf *btf__parse_elf_split(स्थिर अक्षर *path, काष्ठा btf *base_btf);
LIBBPF_API काष्ठा btf *btf__parse_raw(स्थिर अक्षर *path);
LIBBPF_API काष्ठा btf *btf__parse_raw_split(स्थिर अक्षर *path, काष्ठा btf *base_btf);

LIBBPF_API पूर्णांक btf__finalize_data(काष्ठा bpf_object *obj, काष्ठा btf *btf);
LIBBPF_API पूर्णांक btf__load(काष्ठा btf *btf);
LIBBPF_API __s32 btf__find_by_name(स्थिर काष्ठा btf *btf,
				   स्थिर अक्षर *type_name);
LIBBPF_API __s32 btf__find_by_name_kind(स्थिर काष्ठा btf *btf,
					स्थिर अक्षर *type_name, __u32 kind);
LIBBPF_API __u32 btf__get_nr_types(स्थिर काष्ठा btf *btf);
LIBBPF_API स्थिर काष्ठा btf *btf__base_btf(स्थिर काष्ठा btf *btf);
LIBBPF_API स्थिर काष्ठा btf_type *btf__type_by_id(स्थिर काष्ठा btf *btf,
						  __u32 id);
LIBBPF_API माप_प्रकार btf__poपूर्णांकer_size(स्थिर काष्ठा btf *btf);
LIBBPF_API पूर्णांक btf__set_poपूर्णांकer_size(काष्ठा btf *btf, माप_प्रकार ptr_sz);
LIBBPF_API क्रमागत btf_endianness btf__endianness(स्थिर काष्ठा btf *btf);
LIBBPF_API पूर्णांक btf__set_endianness(काष्ठा btf *btf, क्रमागत btf_endianness endian);
LIBBPF_API __s64 btf__resolve_size(स्थिर काष्ठा btf *btf, __u32 type_id);
LIBBPF_API पूर्णांक btf__resolve_type(स्थिर काष्ठा btf *btf, __u32 type_id);
LIBBPF_API पूर्णांक btf__align_of(स्थिर काष्ठा btf *btf, __u32 id);
LIBBPF_API पूर्णांक btf__fd(स्थिर काष्ठा btf *btf);
LIBBPF_API व्योम btf__set_fd(काष्ठा btf *btf, पूर्णांक fd);
LIBBPF_API स्थिर व्योम *btf__get_raw_data(स्थिर काष्ठा btf *btf, __u32 *size);
LIBBPF_API स्थिर अक्षर *btf__name_by_offset(स्थिर काष्ठा btf *btf, __u32 offset);
LIBBPF_API स्थिर अक्षर *btf__str_by_offset(स्थिर काष्ठा btf *btf, __u32 offset);
LIBBPF_API पूर्णांक btf__get_from_id(__u32 id, काष्ठा btf **btf);
LIBBPF_API पूर्णांक btf__get_map_kv_tids(स्थिर काष्ठा btf *btf, स्थिर अक्षर *map_name,
				    __u32 expected_key_size,
				    __u32 expected_value_size,
				    __u32 *key_type_id, __u32 *value_type_id);

LIBBPF_API काष्ठा btf_ext *btf_ext__new(__u8 *data, __u32 size);
LIBBPF_API व्योम btf_ext__मुक्त(काष्ठा btf_ext *btf_ext);
LIBBPF_API स्थिर व्योम *btf_ext__get_raw_data(स्थिर काष्ठा btf_ext *btf_ext,
					     __u32 *size);
LIBBPF_API LIBBPF_DEPRECATED("btf_ext__reloc_func_info was never meant as a public API and has wrong assumptions embedded in it; it will be removed in the future libbpf versions")
पूर्णांक btf_ext__reloc_func_info(स्थिर काष्ठा btf *btf,
			     स्थिर काष्ठा btf_ext *btf_ext,
			     स्थिर अक्षर *sec_name, __u32 insns_cnt,
			     व्योम **func_info, __u32 *cnt);
LIBBPF_API LIBBPF_DEPRECATED("btf_ext__reloc_line_info was never meant as a public API and has wrong assumptions embedded in it; it will be removed in the future libbpf versions")
पूर्णांक btf_ext__reloc_line_info(स्थिर काष्ठा btf *btf,
			     स्थिर काष्ठा btf_ext *btf_ext,
			     स्थिर अक्षर *sec_name, __u32 insns_cnt,
			     व्योम **line_info, __u32 *cnt);
LIBBPF_API __u32 btf_ext__func_info_rec_size(स्थिर काष्ठा btf_ext *btf_ext);
LIBBPF_API __u32 btf_ext__line_info_rec_size(स्थिर काष्ठा btf_ext *btf_ext);

LIBBPF_API काष्ठा btf *libbpf_find_kernel_btf(व्योम);

LIBBPF_API पूर्णांक btf__find_str(काष्ठा btf *btf, स्थिर अक्षर *s);
LIBBPF_API पूर्णांक btf__add_str(काष्ठा btf *btf, स्थिर अक्षर *s);
LIBBPF_API पूर्णांक btf__add_type(काष्ठा btf *btf, स्थिर काष्ठा btf *src_btf,
			     स्थिर काष्ठा btf_type *src_type);

LIBBPF_API पूर्णांक btf__add_पूर्णांक(काष्ठा btf *btf, स्थिर अक्षर *name, माप_प्रकार byte_sz, पूर्णांक encoding);
LIBBPF_API पूर्णांक btf__add_भग्न(काष्ठा btf *btf, स्थिर अक्षर *name, माप_प्रकार byte_sz);
LIBBPF_API पूर्णांक btf__add_ptr(काष्ठा btf *btf, पूर्णांक ref_type_id);
LIBBPF_API पूर्णांक btf__add_array(काष्ठा btf *btf,
			      पूर्णांक index_type_id, पूर्णांक elem_type_id, __u32 nr_elems);
/* काष्ठा/जोड़ स्थिरruction APIs */
LIBBPF_API पूर्णांक btf__add_काष्ठा(काष्ठा btf *btf, स्थिर अक्षर *name, __u32 sz);
LIBBPF_API पूर्णांक btf__add_जोड़(काष्ठा btf *btf, स्थिर अक्षर *name, __u32 sz);
LIBBPF_API पूर्णांक btf__add_field(काष्ठा btf *btf, स्थिर अक्षर *name, पूर्णांक field_type_id,
			      __u32 bit_offset, __u32 bit_size);

/* क्रमागत स्थिरruction APIs */
LIBBPF_API पूर्णांक btf__add_क्रमागत(काष्ठा btf *btf, स्थिर अक्षर *name, __u32 bytes_sz);
LIBBPF_API पूर्णांक btf__add_क्रमागत_value(काष्ठा btf *btf, स्थिर अक्षर *name, __s64 value);

क्रमागत btf_fwd_kind अणु
	BTF_FWD_STRUCT = 0,
	BTF_FWD_UNION = 1,
	BTF_FWD_ENUM = 2,
पूर्ण;

LIBBPF_API पूर्णांक btf__add_fwd(काष्ठा btf *btf, स्थिर अक्षर *name, क्रमागत btf_fwd_kind fwd_kind);
LIBBPF_API पूर्णांक btf__add_प्रकार(काष्ठा btf *btf, स्थिर अक्षर *name, पूर्णांक ref_type_id);
LIBBPF_API पूर्णांक btf__add_अस्थिर(काष्ठा btf *btf, पूर्णांक ref_type_id);
LIBBPF_API पूर्णांक btf__add_स्थिर(काष्ठा btf *btf, पूर्णांक ref_type_id);
LIBBPF_API पूर्णांक btf__add_restrict(काष्ठा btf *btf, पूर्णांक ref_type_id);

/* func and func_proto स्थिरruction APIs */
LIBBPF_API पूर्णांक btf__add_func(काष्ठा btf *btf, स्थिर अक्षर *name,
			     क्रमागत btf_func_linkage linkage, पूर्णांक proto_type_id);
LIBBPF_API पूर्णांक btf__add_func_proto(काष्ठा btf *btf, पूर्णांक ret_type_id);
LIBBPF_API पूर्णांक btf__add_func_param(काष्ठा btf *btf, स्थिर अक्षर *name, पूर्णांक type_id);

/* var & datasec स्थिरruction APIs */
LIBBPF_API पूर्णांक btf__add_var(काष्ठा btf *btf, स्थिर अक्षर *name, पूर्णांक linkage, पूर्णांक type_id);
LIBBPF_API पूर्णांक btf__add_datasec(काष्ठा btf *btf, स्थिर अक्षर *name, __u32 byte_sz);
LIBBPF_API पूर्णांक btf__add_datasec_var_info(काष्ठा btf *btf, पूर्णांक var_type_id,
					 __u32 offset, __u32 byte_sz);

काष्ठा btf_dedup_opts अणु
	अचिन्हित पूर्णांक dedup_table_size;
	bool करोnt_resolve_fwds;
पूर्ण;

LIBBPF_API पूर्णांक btf__dedup(काष्ठा btf *btf, काष्ठा btf_ext *btf_ext,
			  स्थिर काष्ठा btf_dedup_opts *opts);

काष्ठा btf_dump;

काष्ठा btf_dump_opts अणु
	व्योम *ctx;
पूर्ण;

प्रकार व्योम (*btf_dump_म_लिखो_fn_t)(व्योम *ctx, स्थिर अक्षर *fmt, बहु_सूची args);

LIBBPF_API काष्ठा btf_dump *btf_dump__new(स्थिर काष्ठा btf *btf,
					  स्थिर काष्ठा btf_ext *btf_ext,
					  स्थिर काष्ठा btf_dump_opts *opts,
					  btf_dump_म_लिखो_fn_t म_लिखो_fn);
LIBBPF_API व्योम btf_dump__मुक्त(काष्ठा btf_dump *d);

LIBBPF_API पूर्णांक btf_dump__dump_type(काष्ठा btf_dump *d, __u32 id);

काष्ठा btf_dump_emit_type_decl_opts अणु
	/* size of this काष्ठा, क्रम क्रमward/backward compatiblity */
	माप_प्रकार sz;
	/* optional field name क्रम type declaration, e.g.:
	 * - काष्ठा my_काष्ठा <FNAME>
	 * - व्योम (*<FNAME>)(पूर्णांक)
	 * - अक्षर (*<FNAME>)[123]
	 */
	स्थिर अक्षर *field_name;
	/* extra indentation level (in number of tअसल) to emit क्रम multi-line
	 * type declarations (e.g., anonymous काष्ठा); applies क्रम lines
	 * starting from the second one (first line is assumed to have
	 * necessary indentation alपढ़ोy
	 */
	पूर्णांक indent_level;
	/* strip all the स्थिर/अस्थिर/restrict mods */
	bool strip_mods;
	माप_प्रकार :0;
पूर्ण;
#घोषणा btf_dump_emit_type_decl_opts__last_field strip_mods

LIBBPF_API पूर्णांक
btf_dump__emit_type_decl(काष्ठा btf_dump *d, __u32 id,
			 स्थिर काष्ठा btf_dump_emit_type_decl_opts *opts);

/*
 * A set of helpers क्रम easier BTF types handling
 */
अटल अंतरभूत __u16 btf_kind(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info);
पूर्ण

अटल अंतरभूत __u16 btf_vlen(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_VLEN(t->info);
पूर्ण

अटल अंतरभूत bool btf_kflag(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KFLAG(t->info);
पूर्ण

अटल अंतरभूत bool btf_is_व्योम(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_UNKN;
पूर्ण

अटल अंतरभूत bool btf_is_पूर्णांक(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_INT;
पूर्ण

अटल अंतरभूत bool btf_is_ptr(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_PTR;
पूर्ण

अटल अंतरभूत bool btf_is_array(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_ARRAY;
पूर्ण

अटल अंतरभूत bool btf_is_काष्ठा(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_STRUCT;
पूर्ण

अटल अंतरभूत bool btf_is_जोड़(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_UNION;
पूर्ण

अटल अंतरभूत bool btf_is_composite(स्थिर काष्ठा btf_type *t)
अणु
	__u16 kind = btf_kind(t);

	वापस kind == BTF_KIND_STRUCT || kind == BTF_KIND_UNION;
पूर्ण

अटल अंतरभूत bool btf_is_क्रमागत(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_ENUM;
पूर्ण

अटल अंतरभूत bool btf_is_fwd(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_FWD;
पूर्ण

अटल अंतरभूत bool btf_is_प्रकार(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_TYPEDEF;
पूर्ण

अटल अंतरभूत bool btf_is_अस्थिर(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_VOLATILE;
पूर्ण

अटल अंतरभूत bool btf_is_स्थिर(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_CONST;
पूर्ण

अटल अंतरभूत bool btf_is_restrict(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_RESTRICT;
पूर्ण

अटल अंतरभूत bool btf_is_mod(स्थिर काष्ठा btf_type *t)
अणु
	__u16 kind = btf_kind(t);

	वापस kind == BTF_KIND_VOLATILE ||
	       kind == BTF_KIND_CONST ||
	       kind == BTF_KIND_RESTRICT;
पूर्ण

अटल अंतरभूत bool btf_is_func(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_FUNC;
पूर्ण

अटल अंतरभूत bool btf_is_func_proto(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_FUNC_PROTO;
पूर्ण

अटल अंतरभूत bool btf_is_var(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_VAR;
पूर्ण

अटल अंतरभूत bool btf_is_datasec(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_DATASEC;
पूर्ण

अटल अंतरभूत bool btf_is_भग्न(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind(t) == BTF_KIND_FLOAT;
पूर्ण

अटल अंतरभूत __u8 btf_पूर्णांक_encoding(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INT_ENCODING(*(__u32 *)(t + 1));
पूर्ण

अटल अंतरभूत __u8 btf_पूर्णांक_offset(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INT_OFFSET(*(__u32 *)(t + 1));
पूर्ण

अटल अंतरभूत __u8 btf_पूर्णांक_bits(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INT_BITS(*(__u32 *)(t + 1));
पूर्ण

अटल अंतरभूत काष्ठा btf_array *btf_array(स्थिर काष्ठा btf_type *t)
अणु
	वापस (काष्ठा btf_array *)(t + 1);
पूर्ण

अटल अंतरभूत काष्ठा btf_क्रमागत *btf_क्रमागत(स्थिर काष्ठा btf_type *t)
अणु
	वापस (काष्ठा btf_क्रमागत *)(t + 1);
पूर्ण

अटल अंतरभूत काष्ठा btf_member *btf_members(स्थिर काष्ठा btf_type *t)
अणु
	वापस (काष्ठा btf_member *)(t + 1);
पूर्ण

/* Get bit offset of a member with specअगरied index. */
अटल अंतरभूत __u32 btf_member_bit_offset(स्थिर काष्ठा btf_type *t,
					  __u32 member_idx)
अणु
	स्थिर काष्ठा btf_member *m = btf_members(t) + member_idx;
	bool kflag = btf_kflag(t);

	वापस kflag ? BTF_MEMBER_BIT_OFFSET(m->offset) : m->offset;
पूर्ण
/*
 * Get bitfield size of a member, assuming t is BTF_KIND_STRUCT or
 * BTF_KIND_UNION. If member is not a bitfield, zero is वापसed.
 */
अटल अंतरभूत __u32 btf_member_bitfield_size(स्थिर काष्ठा btf_type *t,
					     __u32 member_idx)
अणु
	स्थिर काष्ठा btf_member *m = btf_members(t) + member_idx;
	bool kflag = btf_kflag(t);

	वापस kflag ? BTF_MEMBER_BITFIELD_SIZE(m->offset) : 0;
पूर्ण

अटल अंतरभूत काष्ठा btf_param *btf_params(स्थिर काष्ठा btf_type *t)
अणु
	वापस (काष्ठा btf_param *)(t + 1);
पूर्ण

अटल अंतरभूत काष्ठा btf_var *btf_var(स्थिर काष्ठा btf_type *t)
अणु
	वापस (काष्ठा btf_var *)(t + 1);
पूर्ण

अटल अंतरभूत काष्ठा btf_var_secinfo *
btf_var_secinfos(स्थिर काष्ठा btf_type *t)
अणु
	वापस (काष्ठा btf_var_secinfo *)(t + 1);
पूर्ण

#अगर_घोषित __cplusplus
पूर्ण /* बाह्य "C" */
#पूर्ण_अगर

#पूर्ण_अगर /* __LIBBPF_BTF_H */
