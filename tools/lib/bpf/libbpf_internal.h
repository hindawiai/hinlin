<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */

/*
 * Internal libbpf helpers.
 *
 * Copyright (c) 2019 Facebook
 */

#अगर_अघोषित __LIBBPF_LIBBPF_INTERNAL_H
#घोषणा __LIBBPF_LIBBPF_INTERNAL_H

#समावेश <मानककोष.स>
#समावेश <सीमा.स>

/* make sure libbpf करोesn't use kernel-only पूर्णांकeger प्रकारs */
#आशय GCC poison u8 u16 u32 u64 s8 s16 s32 s64

/* prevent accidental re-addition of पुनः_स्मृतिarray() */
#आशय GCC poison पुनः_स्मृतिarray

#समावेश "libbpf.h"
#समावेश "btf.h"

#अगर_अघोषित EM_BPF
#घोषणा EM_BPF 247
#पूर्ण_अगर

#अगर_अघोषित R_BPF_64_64
#घोषणा R_BPF_64_64 1
#पूर्ण_अगर
#अगर_अघोषित R_BPF_64_32
#घोषणा R_BPF_64_32 10
#पूर्ण_अगर

#अगर_अघोषित SHT_LLVM_ADDRSIG
#घोषणा SHT_LLVM_ADDRSIG 0x6FFF4C03
#पूर्ण_अगर

/* अगर libelf is old and करोesn't support mmap(), fall back to पढ़ो() */
#अगर_अघोषित ELF_C_READ_MMAP
#घोषणा ELF_C_READ_MMAP ELF_C_READ
#पूर्ण_अगर

/* Older libelf all end up in this expression, क्रम both 32 and 64 bit */
#अगर_अघोषित GELF_ST_VISIBILITY
#घोषणा GELF_ST_VISIBILITY(o) ((o) & 0x03)
#पूर्ण_अगर

#घोषणा BTF_INFO_ENC(kind, kind_flag, vlen) \
	((!!(kind_flag) << 31) | ((kind) << 24) | ((vlen) & BTF_MAX_VLEN))
#घोषणा BTF_TYPE_ENC(name, info, size_or_type) (name), (info), (size_or_type)
#घोषणा BTF_INT_ENC(encoding, bits_offset, nr_bits) \
	((encoding) << 24 | (bits_offset) << 16 | (nr_bits))
#घोषणा BTF_TYPE_INT_ENC(name, encoding, bits_offset, bits, sz) \
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_INT, 0, 0), sz), \
	BTF_INT_ENC(encoding, bits_offset, bits)
#घोषणा BTF_MEMBER_ENC(name, type, bits_offset) (name), (type), (bits_offset)
#घोषणा BTF_PARAM_ENC(name, type) (name), (type)
#घोषणा BTF_VAR_SECINFO_ENC(type, offset, size) (type), (offset), (size)
#घोषणा BTF_TYPE_FLOAT_ENC(name, sz) \
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_FLOAT, 0, 0), sz)

#अगर_अघोषित likely
#घोषणा likely(x) __builtin_expect(!!(x), 1)
#पूर्ण_अगर
#अगर_अघोषित unlikely
#घोषणा unlikely(x) __builtin_expect(!!(x), 0)
#पूर्ण_अगर
#अगर_अघोषित min
# define min(x, y) ((x) < (y) ? (x) : (y))
#पूर्ण_अगर
#अगर_अघोषित max
# define max(x, y) ((x) < (y) ? (y) : (x))
#पूर्ण_अगर
#अगर_अघोषित दुरत्वend
# define दुरत्वend(TYPE, FIELD) \
	(दुरत्व(TYPE, FIELD) + माप(((TYPE *)0)->FIELD))
#पूर्ण_अगर

/* Symbol versioning is dअगरferent between अटल and shared library.
 * Properly versioned symbols are needed क्रम shared library, but
 * only the symbol of the new version is needed क्रम अटल library.
 */
#अगर_घोषित SHARED
# define COMPAT_VERSION(पूर्णांकernal_name, api_name, version) \
	यंत्र(".symver " #पूर्णांकernal_name "," #api_name "@" #version);
# define DEFAULT_VERSION(पूर्णांकernal_name, api_name, version) \
	यंत्र(".symver " #पूर्णांकernal_name "," #api_name "@@" #version);
#अन्यथा
# define COMPAT_VERSION(पूर्णांकernal_name, api_name, version)
# define DEFAULT_VERSION(पूर्णांकernal_name, api_name, version) \
	बाह्य typeof(पूर्णांकernal_name) api_name \
	__attribute__((alias(#पूर्णांकernal_name)));
#पूर्ण_अगर

बाह्य व्योम libbpf_prपूर्णांक(क्रमागत libbpf_prपूर्णांक_level level,
			 स्थिर अक्षर *क्रमmat, ...)
	__attribute__((क्रमmat(म_लिखो, 2, 3)));

#घोषणा __pr(level, fmt, ...)	\
करो अणु				\
	libbpf_prपूर्णांक(level, "libbpf: " fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा pr_warn(fmt, ...)	__pr(LIBBPF_WARN, fmt, ##__VA_ARGS__)
#घोषणा pr_info(fmt, ...)	__pr(LIBBPF_INFO, fmt, ##__VA_ARGS__)
#घोषणा pr_debug(fmt, ...)	__pr(LIBBPF_DEBUG, fmt, ##__VA_ARGS__)

#अगर_अघोषित __has_builtin
#घोषणा __has_builtin(x) 0
#पूर्ण_अगर
/*
 * Re-implement glibc's पुनः_स्मृतिarray() क्रम libbpf पूर्णांकernal-only use.
 * पुनः_स्मृतिarray(), unक्रमtunately, is not available in all versions of glibc,
 * so requires extra feature detection and using पुनः_स्मृतिarray() stub from
 * <tools/libc_compat.h> and COMPAT_NEED_REALLOCARRAY. All this complicates
 * build of libbpf unnecessarily and is just a मुख्यtenance burden. Instead,
 * it's trivial to implement libbpf-specअगरic पूर्णांकernal version and use it
 * throughout libbpf.
 */
अटल अंतरभूत व्योम *libbpf_पुनः_स्मृतिarray(व्योम *ptr, माप_प्रकार nmemb, माप_प्रकार size)
अणु
	माप_प्रकार total;

#अगर __has_builtin(__builtin_mul_overflow)
	अगर (unlikely(__builtin_mul_overflow(nmemb, size, &total)))
		वापस शून्य;
#अन्यथा
	अगर (size == 0 || nmemb > अच_दीर्घ_उच्च / size)
		वापस शून्य;
	total = nmemb * size;
#पूर्ण_अगर
	वापस पुनः_स्मृति(ptr, total);
पूर्ण

काष्ठा btf;
काष्ठा btf_type;

काष्ठा btf_type *btf_type_by_id(काष्ठा btf *btf, __u32 type_id);
स्थिर अक्षर *btf_kind_str(स्थिर काष्ठा btf_type *t);
स्थिर काष्ठा btf_type *skip_mods_and_प्रकारs(स्थिर काष्ठा btf *btf, __u32 id, __u32 *res_id);

अटल अंतरभूत क्रमागत btf_func_linkage btf_func_linkage(स्थिर काष्ठा btf_type *t)
अणु
	वापस (क्रमागत btf_func_linkage)(पूर्णांक)btf_vlen(t);
पूर्ण

अटल अंतरभूत __u32 btf_type_info(पूर्णांक kind, पूर्णांक vlen, पूर्णांक kflag)
अणु
	वापस (kflag << 31) | (kind << 24) | vlen;
पूर्ण

क्रमागत map_def_parts अणु
	MAP_DEF_MAP_TYPE	= 0x001,
	MAP_DEF_KEY_TYPE	= 0x002,
	MAP_DEF_KEY_SIZE	= 0x004,
	MAP_DEF_VALUE_TYPE	= 0x008,
	MAP_DEF_VALUE_SIZE	= 0x010,
	MAP_DEF_MAX_ENTRIES	= 0x020,
	MAP_DEF_MAP_FLAGS	= 0x040,
	MAP_DEF_NUMA_NODE	= 0x080,
	MAP_DEF_PINNING		= 0x100,
	MAP_DEF_INNER_MAP	= 0x200,

	MAP_DEF_ALL		= 0x3ff, /* combination of all above */
पूर्ण;

काष्ठा btf_map_def अणु
	क्रमागत map_def_parts parts;
	__u32 map_type;
	__u32 key_type_id;
	__u32 key_size;
	__u32 value_type_id;
	__u32 value_size;
	__u32 max_entries;
	__u32 map_flags;
	__u32 numa_node;
	__u32 pinning;
पूर्ण;

पूर्णांक parse_btf_map_def(स्थिर अक्षर *map_name, काष्ठा btf *btf,
		      स्थिर काष्ठा btf_type *def_t, bool strict,
		      काष्ठा btf_map_def *map_def, काष्ठा btf_map_def *inner_def);

व्योम *libbpf_add_mem(व्योम **data, माप_प्रकार *cap_cnt, माप_प्रकार elem_sz,
		     माप_प्रकार cur_cnt, माप_प्रकार max_cnt, माप_प्रकार add_cnt);
पूर्णांक libbpf_ensure_mem(व्योम **data, माप_प्रकार *cap_cnt, माप_प्रकार elem_sz, माप_प्रकार need_cnt);

अटल अंतरभूत bool libbpf_validate_opts(स्थिर अक्षर *opts,
					माप_प्रकार opts_sz, माप_प्रकार user_sz,
					स्थिर अक्षर *type_name)
अणु
	अगर (user_sz < माप(माप_प्रकार)) अणु
		pr_warn("%s size (%zu) is too small\n", type_name, user_sz);
		वापस false;
	पूर्ण
	अगर (user_sz > opts_sz) अणु
		माप_प्रकार i;

		क्रम (i = opts_sz; i < user_sz; i++) अणु
			अगर (opts[i]) अणु
				pr_warn("%s has non-zero extra bytes\n",
					type_name);
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

#घोषणा OPTS_VALID(opts, type)						      \
	(!(opts) || libbpf_validate_opts((स्थिर अक्षर *)opts,		      \
					 दुरत्वend(काष्ठा type,	      \
						     type##__last_field),     \
					 (opts)->sz, #type))
#घोषणा OPTS_HAS(opts, field) \
	((opts) && opts->sz >= दुरत्वend(typeof(*(opts)), field))
#घोषणा OPTS_GET(opts, field, fallback_value) \
	(OPTS_HAS(opts, field) ? (opts)->field : fallback_value)
#घोषणा OPTS_SET(opts, field, value)		\
	करो अणु					\
		अगर (OPTS_HAS(opts, field))	\
			(opts)->field = value;	\
	पूर्ण जबतक (0)

पूर्णांक parse_cpu_mask_str(स्थिर अक्षर *s, bool **mask, पूर्णांक *mask_sz);
पूर्णांक parse_cpu_mask_file(स्थिर अक्षर *fcpu, bool **mask, पूर्णांक *mask_sz);
पूर्णांक libbpf__load_raw_btf(स्थिर अक्षर *raw_types, माप_प्रकार types_len,
			 स्थिर अक्षर *str_sec, माप_प्रकार str_len);

काष्ठा bpf_prog_load_params अणु
	क्रमागत bpf_prog_type prog_type;
	क्रमागत bpf_attach_type expected_attach_type;
	स्थिर अक्षर *name;
	स्थिर काष्ठा bpf_insn *insns;
	माप_प्रकार insn_cnt;
	स्थिर अक्षर *license;
	__u32 kern_version;
	__u32 attach_prog_fd;
	__u32 attach_btf_obj_fd;
	__u32 attach_btf_id;
	__u32 prog_अगरindex;
	__u32 prog_btf_fd;
	__u32 prog_flags;

	__u32 func_info_rec_size;
	स्थिर व्योम *func_info;
	__u32 func_info_cnt;

	__u32 line_info_rec_size;
	स्थिर व्योम *line_info;
	__u32 line_info_cnt;

	__u32 log_level;
	अक्षर *log_buf;
	माप_प्रकार log_buf_sz;
पूर्ण;

पूर्णांक libbpf__bpf_prog_load(स्थिर काष्ठा bpf_prog_load_params *load_attr);

पूर्णांक bpf_object__section_size(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name,
			     __u32 *size);
पूर्णांक bpf_object__variable_offset(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name,
				__u32 *off);
काष्ठा btf *btf_get_from_fd(पूर्णांक btf_fd, काष्ठा btf *base_btf);

काष्ठा btf_ext_info अणु
	/*
	 * info poपूर्णांकs to the inभागidual info section (e.g. func_info and
	 * line_info) from the .BTF.ext. It करोes not include the __u32 rec_size.
	 */
	व्योम *info;
	__u32 rec_size;
	__u32 len;
पूर्ण;

#घोषणा क्रम_each_btf_ext_sec(seg, sec)					\
	क्रम (sec = (seg)->info;						\
	     (व्योम *)sec < (seg)->info + (seg)->len;			\
	     sec = (व्योम *)sec + माप(काष्ठा btf_ext_info_sec) +	\
		   (seg)->rec_size * sec->num_info)

#घोषणा क्रम_each_btf_ext_rec(seg, sec, i, rec)				\
	क्रम (i = 0, rec = (व्योम *)&(sec)->data;				\
	     i < (sec)->num_info;					\
	     i++, rec = (व्योम *)rec + (seg)->rec_size)

/*
 * The .BTF.ext ELF section layout defined as
 *   काष्ठा btf_ext_header
 *   func_info subsection
 *
 * The func_info subsection layout:
 *   record size क्रम काष्ठा bpf_func_info in the func_info subsection
 *   काष्ठा btf_sec_func_info क्रम section #1
 *   a list of bpf_func_info records क्रम section #1
 *     where काष्ठा bpf_func_info mimics one in include/uapi/linux/bpf.h
 *     but may not be identical
 *   काष्ठा btf_sec_func_info क्रम section #2
 *   a list of bpf_func_info records क्रम section #2
 *   ......
 *
 * Note that the bpf_func_info record size in .BTF.ext may not
 * be the same as the one defined in include/uapi/linux/bpf.h.
 * The loader should ensure that record_size meets minimum
 * requirement and pass the record as is to the kernel. The
 * kernel will handle the func_info properly based on its contents.
 */
काष्ठा btf_ext_header अणु
	__u16	magic;
	__u8	version;
	__u8	flags;
	__u32	hdr_len;

	/* All offsets are in bytes relative to the end of this header */
	__u32	func_info_off;
	__u32	func_info_len;
	__u32	line_info_off;
	__u32	line_info_len;

	/* optional part of .BTF.ext header */
	__u32	core_relo_off;
	__u32	core_relo_len;
पूर्ण;

काष्ठा btf_ext अणु
	जोड़ अणु
		काष्ठा btf_ext_header *hdr;
		व्योम *data;
	पूर्ण;
	काष्ठा btf_ext_info func_info;
	काष्ठा btf_ext_info line_info;
	काष्ठा btf_ext_info core_relo_info;
	__u32 data_size;
पूर्ण;

काष्ठा btf_ext_info_sec अणु
	__u32	sec_name_off;
	__u32	num_info;
	/* Followed by num_info * record_size number of bytes */
	__u8	data[];
पूर्ण;

/* The minimum bpf_func_info checked by the loader */
काष्ठा bpf_func_info_min अणु
	__u32   insn_off;
	__u32   type_id;
पूर्ण;

/* The minimum bpf_line_info checked by the loader */
काष्ठा bpf_line_info_min अणु
	__u32	insn_off;
	__u32	file_name_off;
	__u32	line_off;
	__u32	line_col;
पूर्ण;

/* bpf_core_relo_kind encodes which aspect of captured field/type/क्रमागत value
 * has to be adjusted by relocations.
 */
क्रमागत bpf_core_relo_kind अणु
	BPF_FIELD_BYTE_OFFSET = 0,	/* field byte offset */
	BPF_FIELD_BYTE_SIZE = 1,	/* field size in bytes */
	BPF_FIELD_EXISTS = 2,		/* field existence in target kernel */
	BPF_FIELD_SIGNED = 3,		/* field चिन्हितness (0 - अचिन्हित, 1 - चिन्हित) */
	BPF_FIELD_LSHIFT_U64 = 4,	/* bitfield-specअगरic left bitshअगरt */
	BPF_FIELD_RSHIFT_U64 = 5,	/* bitfield-specअगरic right bitshअगरt */
	BPF_TYPE_ID_LOCAL = 6,		/* type ID in local BPF object */
	BPF_TYPE_ID_TARGET = 7,		/* type ID in target kernel */
	BPF_TYPE_EXISTS = 8,		/* type existence in target kernel */
	BPF_TYPE_SIZE = 9,		/* type size in bytes */
	BPF_ENUMVAL_EXISTS = 10,	/* क्रमागत value existence in target kernel */
	BPF_ENUMVAL_VALUE = 11,		/* क्रमागत value पूर्णांकeger value */
पूर्ण;

/* The minimum bpf_core_relo checked by the loader
 *
 * CO-RE relocation captures the following data:
 * - insn_off - inकाष्ठाion offset (in bytes) within a BPF program that needs
 *   its insn->imm field to be relocated with actual field info;
 * - type_id - BTF type ID of the "root" (containing) entity of a relocatable
 *   type or field;
 * - access_str_off - offset पूर्णांकo corresponding .BTF string section. String
 *   पूर्णांकerpretation depends on specअगरic relocation kind:
 *     - क्रम field-based relocations, string encodes an accessed field using
 *     a sequence of field and array indices, separated by colon (:). It's
 *     conceptually very बंद to LLVM's getelementptr ([0]) instruction's
 *     arguments क्रम identअगरying offset to a field.
 *     - क्रम type-based relocations, strings is expected to be just "0";
 *     - क्रम क्रमागत value-based relocations, string contains an index of क्रमागत
 *     value within its क्रमागत type;
 *
 * Example to provide a better feel.
 *
 *   काष्ठा sample अणु
 *       पूर्णांक a;
 *       काष्ठा अणु
 *           पूर्णांक b[10];
 *       पूर्ण;
 *   पूर्ण;
 *
 *   काष्ठा sample *s = ...;
 *   पूर्णांक x = &s->a;     // encoded as "0:0" (a is field #0)
 *   पूर्णांक y = &s->b[5];  // encoded as "0:1:0:5" (anon काष्ठा is field #1, 
 *                      // b is field #0 inside anon काष्ठा, accessing elem #5)
 *   पूर्णांक z = &s[10]->b; // encoded as "10:1" (ptr is used as an array)
 *
 * type_id क्रम all relocs in this example  will capture BTF type id of
 * `काष्ठा sample`.
 *
 * Such relocation is emitted when using __builtin_preserve_access_index()
 * Clang built-in, passing expression that captures field address, e.g.:
 *
 * bpf_probe_पढ़ो(&dst, माप(dst),
 *		  __builtin_preserve_access_index(&src->a.b.c));
 *
 * In this हाल Clang will emit field relocation recording necessary data to
 * be able to find offset of embedded `a.b.c` field within `src` काष्ठा.
 *
 *   [0] https://llvm.org/करोcs/LangRef.hपंचांगl#getelementptr-inकाष्ठाion
 */
काष्ठा bpf_core_relo अणु
	__u32   insn_off;
	__u32   type_id;
	__u32   access_str_off;
	क्रमागत bpf_core_relo_kind kind;
पूर्ण;

प्रकार पूर्णांक (*type_id_visit_fn)(__u32 *type_id, व्योम *ctx);
प्रकार पूर्णांक (*str_off_visit_fn)(__u32 *str_off, व्योम *ctx);
पूर्णांक btf_type_visit_type_ids(काष्ठा btf_type *t, type_id_visit_fn visit, व्योम *ctx);
पूर्णांक btf_type_visit_str_offs(काष्ठा btf_type *t, str_off_visit_fn visit, व्योम *ctx);
पूर्णांक btf_ext_visit_type_ids(काष्ठा btf_ext *btf_ext, type_id_visit_fn visit, व्योम *ctx);
पूर्णांक btf_ext_visit_str_offs(काष्ठा btf_ext *btf_ext, str_off_visit_fn visit, व्योम *ctx);

#पूर्ण_अगर /* __LIBBPF_LIBBPF_INTERNAL_H */
