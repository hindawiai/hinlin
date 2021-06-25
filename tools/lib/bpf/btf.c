<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2018 Facebook */

#समावेश <byteswap.h>
#समावेश <endian.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/utsname.h>
#समावेश <sys/param.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/btf.h>
#समावेश <gelf.h>
#समावेश "btf.h"
#समावेश "bpf.h"
#समावेश "libbpf.h"
#समावेश "libbpf_internal.h"
#समावेश "hashmap.h"
#समावेश "strset.h"

#घोषणा BTF_MAX_NR_TYPES 0x7fffffffU
#घोषणा BTF_MAX_STR_OFFSET 0x7fffffffU

अटल काष्ठा btf_type btf_व्योम;

काष्ठा btf अणु
	/* raw BTF data in native endianness */
	व्योम *raw_data;
	/* raw BTF data in non-native endianness */
	व्योम *raw_data_swapped;
	__u32 raw_size;
	/* whether target endianness dअगरfers from the native one */
	bool swapped_endian;

	/*
	 * When BTF is loaded from an ELF or raw memory it is stored
	 * in a contiguous memory block. The hdr, type_data, and, strs_data
	 * poपूर्णांक inside that memory region to their respective parts of BTF
	 * representation:
	 *
	 * +--------------------------------+
	 * |  Header  |  Types  |  Strings  |
	 * +--------------------------------+
	 * ^          ^         ^
	 * |          |         |
	 * hdr        |         |
	 * types_data-+         |
	 * strs_data------------+
	 *
	 * If BTF data is later modअगरied, e.g., due to types added or
	 * हटाओd, BTF deduplication perक्रमmed, etc, this contiguous
	 * representation is broken up पूर्णांकo three independently allocated
	 * memory regions to be able to modअगरy them independently.
	 * raw_data is nulled out at that poपूर्णांक, but can be later allocated
	 * and cached again अगर user calls btf__get_raw_data(), at which poपूर्णांक
	 * raw_data will contain a contiguous copy of header, types, and
	 * strings:
	 *
	 * +----------+  +---------+  +-----------+
	 * |  Header  |  |  Types  |  |  Strings  |
	 * +----------+  +---------+  +-----------+
	 * ^             ^            ^
	 * |             |            |
	 * hdr           |            |
	 * types_data----+            |
	 * strset__data(strs_set)-----+
	 *
	 *               +----------+---------+-----------+
	 *               |  Header  |  Types  |  Strings  |
	 * raw_data----->+----------+---------+-----------+
	 */
	काष्ठा btf_header *hdr;

	व्योम *types_data;
	माप_प्रकार types_data_cap; /* used size stored in hdr->type_len */

	/* type ID to `काष्ठा btf_type *` lookup index
	 * type_offs[0] corresponds to the first non-VOID type:
	 *   - क्रम base BTF it's type [1];
	 *   - क्रम split BTF it's the first non-base BTF type.
	 */
	__u32 *type_offs;
	माप_प्रकार type_offs_cap;
	/* number of types in this BTF instance:
	 *   - करोesn't include special [0] व्योम type;
	 *   - क्रम split BTF counts number of types added on top of base BTF.
	 */
	__u32 nr_types;
	/* अगर not शून्य, poपूर्णांकs to the base BTF on top of which the current
	 * split BTF is based
	 */
	काष्ठा btf *base_btf;
	/* BTF type ID of the first type in this BTF instance:
	 *   - क्रम base BTF it's equal to 1;
	 *   - क्रम split BTF it's equal to biggest type ID of base BTF plus 1.
	 */
	पूर्णांक start_id;
	/* logical string offset of this BTF instance:
	 *   - क्रम base BTF it's equal to 0;
	 *   - क्रम split BTF it's equal to total size of base BTF's string section size.
	 */
	पूर्णांक start_str_off;

	/* only one of strs_data or strs_set can be non-शून्य, depending on
	 * whether BTF is in a modअगरiable state (strs_set is used) or not
	 * (strs_data poपूर्णांकs inside raw_data)
	 */
	व्योम *strs_data;
	/* a set of unique strings */
	काष्ठा strset *strs_set;
	/* whether strings are alपढ़ोy deduplicated */
	bool strs_deduped;

	/* BTF object FD, अगर loaded पूर्णांकo kernel */
	पूर्णांक fd;

	/* Poपूर्णांकer size (in bytes) क्रम a target architecture of this BTF */
	पूर्णांक ptr_sz;
पूर्ण;

अटल अंतरभूत __u64 ptr_to_u64(स्थिर व्योम *ptr)
अणु
	वापस (__u64) (अचिन्हित दीर्घ) ptr;
पूर्ण

/* Ensure given dynamically allocated memory region poपूर्णांकed to by *data* with
 * capacity of *cap_cnt* elements each taking *elem_sz* bytes has enough
 * memory to accomodate *add_cnt* new elements, assuming *cur_cnt* elements
 * are alपढ़ोy used. At most *max_cnt* elements can be ever allocated.
 * If necessary, memory is पुनः_स्मृतिated and all existing data is copied over,
 * new poपूर्णांकer to the memory region is stored at *data, new memory region
 * capacity (in number of elements) is stored in *cap.
 * On success, memory poपूर्णांकer to the beginning of unused memory is वापसed.
 * On error, शून्य is वापसed.
 */
व्योम *libbpf_add_mem(व्योम **data, माप_प्रकार *cap_cnt, माप_प्रकार elem_sz,
		     माप_प्रकार cur_cnt, माप_प्रकार max_cnt, माप_प्रकार add_cnt)
अणु
	माप_प्रकार new_cnt;
	व्योम *new_data;

	अगर (cur_cnt + add_cnt <= *cap_cnt)
		वापस *data + cur_cnt * elem_sz;

	/* requested more than the set limit */
	अगर (cur_cnt + add_cnt > max_cnt)
		वापस शून्य;

	new_cnt = *cap_cnt;
	new_cnt += new_cnt / 4;		  /* expand by 25% */
	अगर (new_cnt < 16)		  /* but at least 16 elements */
		new_cnt = 16;
	अगर (new_cnt > max_cnt)		  /* but not exceeding a set limit */
		new_cnt = max_cnt;
	अगर (new_cnt < cur_cnt + add_cnt)  /* also ensure we have enough memory */
		new_cnt = cur_cnt + add_cnt;

	new_data = libbpf_पुनः_स्मृतिarray(*data, new_cnt, elem_sz);
	अगर (!new_data)
		वापस शून्य;

	/* zero out newly allocated portion of memory */
	स_रखो(new_data + (*cap_cnt) * elem_sz, 0, (new_cnt - *cap_cnt) * elem_sz);

	*data = new_data;
	*cap_cnt = new_cnt;
	वापस new_data + cur_cnt * elem_sz;
पूर्ण

/* Ensure given dynamically allocated memory region has enough allocated space
 * to accommodate *need_cnt* elements of size *elem_sz* bytes each
 */
पूर्णांक libbpf_ensure_mem(व्योम **data, माप_प्रकार *cap_cnt, माप_प्रकार elem_sz, माप_प्रकार need_cnt)
अणु
	व्योम *p;

	अगर (need_cnt <= *cap_cnt)
		वापस 0;

	p = libbpf_add_mem(data, cap_cnt, elem_sz, *cap_cnt, SIZE_MAX, need_cnt - *cap_cnt);
	अगर (!p)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक btf_add_type_idx_entry(काष्ठा btf *btf, __u32 type_off)
अणु
	__u32 *p;

	p = libbpf_add_mem((व्योम **)&btf->type_offs, &btf->type_offs_cap, माप(__u32),
			   btf->nr_types, BTF_MAX_NR_TYPES, 1);
	अगर (!p)
		वापस -ENOMEM;

	*p = type_off;
	वापस 0;
पूर्ण

अटल व्योम btf_bswap_hdr(काष्ठा btf_header *h)
अणु
	h->magic = bswap_16(h->magic);
	h->hdr_len = bswap_32(h->hdr_len);
	h->type_off = bswap_32(h->type_off);
	h->type_len = bswap_32(h->type_len);
	h->str_off = bswap_32(h->str_off);
	h->str_len = bswap_32(h->str_len);
पूर्ण

अटल पूर्णांक btf_parse_hdr(काष्ठा btf *btf)
अणु
	काष्ठा btf_header *hdr = btf->hdr;
	__u32 meta_left;

	अगर (btf->raw_size < माप(काष्ठा btf_header)) अणु
		pr_debug("BTF header not found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->magic == bswap_16(BTF_MAGIC)) अणु
		btf->swapped_endian = true;
		अगर (bswap_32(hdr->hdr_len) != माप(काष्ठा btf_header)) अणु
			pr_warn("Can't load BTF with non-native endianness due to unsupported header length %u\n",
				bswap_32(hdr->hdr_len));
			वापस -ENOTSUP;
		पूर्ण
		btf_bswap_hdr(hdr);
	पूर्ण अन्यथा अगर (hdr->magic != BTF_MAGIC) अणु
		pr_debug("Invalid BTF magic:%x\n", hdr->magic);
		वापस -EINVAL;
	पूर्ण

	meta_left = btf->raw_size - माप(*hdr);
	अगर (meta_left < hdr->str_off + hdr->str_len) अणु
		pr_debug("Invalid BTF total size:%u\n", btf->raw_size);
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->type_off + hdr->type_len > hdr->str_off) अणु
		pr_debug("Invalid BTF data sections layout: type data at %u + %u, strings data at %u + %u\n",
			 hdr->type_off, hdr->type_len, hdr->str_off, hdr->str_len);
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->type_off % 4) अणु
		pr_debug("BTF type section is not aligned to 4 bytes\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btf_parse_str_sec(काष्ठा btf *btf)
अणु
	स्थिर काष्ठा btf_header *hdr = btf->hdr;
	स्थिर अक्षर *start = btf->strs_data;
	स्थिर अक्षर *end = start + btf->hdr->str_len;

	अगर (btf->base_btf && hdr->str_len == 0)
		वापस 0;
	अगर (!hdr->str_len || hdr->str_len - 1 > BTF_MAX_STR_OFFSET || end[-1]) अणु
		pr_debug("Invalid BTF string section\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!btf->base_btf && start[0]) अणु
		pr_debug("Invalid BTF string section\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btf_type_size(स्थिर काष्ठा btf_type *t)
अणु
	स्थिर पूर्णांक base_size = माप(काष्ठा btf_type);
	__u16 vlen = btf_vlen(t);

	चयन (btf_kind(t)) अणु
	हाल BTF_KIND_FWD:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_RESTRICT:
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_FUNC:
	हाल BTF_KIND_FLOAT:
		वापस base_size;
	हाल BTF_KIND_INT:
		वापस base_size + माप(__u32);
	हाल BTF_KIND_ENUM:
		वापस base_size + vlen * माप(काष्ठा btf_क्रमागत);
	हाल BTF_KIND_ARRAY:
		वापस base_size + माप(काष्ठा btf_array);
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
		वापस base_size + vlen * माप(काष्ठा btf_member);
	हाल BTF_KIND_FUNC_PROTO:
		वापस base_size + vlen * माप(काष्ठा btf_param);
	हाल BTF_KIND_VAR:
		वापस base_size + माप(काष्ठा btf_var);
	हाल BTF_KIND_DATASEC:
		वापस base_size + vlen * माप(काष्ठा btf_var_secinfo);
	शेष:
		pr_debug("Unsupported BTF_KIND:%u\n", btf_kind(t));
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम btf_bswap_type_base(काष्ठा btf_type *t)
अणु
	t->name_off = bswap_32(t->name_off);
	t->info = bswap_32(t->info);
	t->type = bswap_32(t->type);
पूर्ण

अटल पूर्णांक btf_bswap_type_rest(काष्ठा btf_type *t)
अणु
	काष्ठा btf_var_secinfo *v;
	काष्ठा btf_member *m;
	काष्ठा btf_array *a;
	काष्ठा btf_param *p;
	काष्ठा btf_क्रमागत *e;
	__u16 vlen = btf_vlen(t);
	पूर्णांक i;

	चयन (btf_kind(t)) अणु
	हाल BTF_KIND_FWD:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_RESTRICT:
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_FUNC:
	हाल BTF_KIND_FLOAT:
		वापस 0;
	हाल BTF_KIND_INT:
		*(__u32 *)(t + 1) = bswap_32(*(__u32 *)(t + 1));
		वापस 0;
	हाल BTF_KIND_ENUM:
		क्रम (i = 0, e = btf_क्रमागत(t); i < vlen; i++, e++) अणु
			e->name_off = bswap_32(e->name_off);
			e->val = bswap_32(e->val);
		पूर्ण
		वापस 0;
	हाल BTF_KIND_ARRAY:
		a = btf_array(t);
		a->type = bswap_32(a->type);
		a->index_type = bswap_32(a->index_type);
		a->nelems = bswap_32(a->nelems);
		वापस 0;
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
		क्रम (i = 0, m = btf_members(t); i < vlen; i++, m++) अणु
			m->name_off = bswap_32(m->name_off);
			m->type = bswap_32(m->type);
			m->offset = bswap_32(m->offset);
		पूर्ण
		वापस 0;
	हाल BTF_KIND_FUNC_PROTO:
		क्रम (i = 0, p = btf_params(t); i < vlen; i++, p++) अणु
			p->name_off = bswap_32(p->name_off);
			p->type = bswap_32(p->type);
		पूर्ण
		वापस 0;
	हाल BTF_KIND_VAR:
		btf_var(t)->linkage = bswap_32(btf_var(t)->linkage);
		वापस 0;
	हाल BTF_KIND_DATASEC:
		क्रम (i = 0, v = btf_var_secinfos(t); i < vlen; i++, v++) अणु
			v->type = bswap_32(v->type);
			v->offset = bswap_32(v->offset);
			v->size = bswap_32(v->size);
		पूर्ण
		वापस 0;
	शेष:
		pr_debug("Unsupported BTF_KIND:%u\n", btf_kind(t));
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक btf_parse_type_sec(काष्ठा btf *btf)
अणु
	काष्ठा btf_header *hdr = btf->hdr;
	व्योम *next_type = btf->types_data;
	व्योम *end_type = next_type + hdr->type_len;
	पूर्णांक err, type_size;

	जबतक (next_type + माप(काष्ठा btf_type) <= end_type) अणु
		अगर (btf->swapped_endian)
			btf_bswap_type_base(next_type);

		type_size = btf_type_size(next_type);
		अगर (type_size < 0)
			वापस type_size;
		अगर (next_type + type_size > end_type) अणु
			pr_warn("BTF type [%d] is malformed\n", btf->start_id + btf->nr_types);
			वापस -EINVAL;
		पूर्ण

		अगर (btf->swapped_endian && btf_bswap_type_rest(next_type))
			वापस -EINVAL;

		err = btf_add_type_idx_entry(btf, next_type - btf->types_data);
		अगर (err)
			वापस err;

		next_type += type_size;
		btf->nr_types++;
	पूर्ण

	अगर (next_type != end_type) अणु
		pr_warn("BTF types data is malformed\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

__u32 btf__get_nr_types(स्थिर काष्ठा btf *btf)
अणु
	वापस btf->start_id + btf->nr_types - 1;
पूर्ण

स्थिर काष्ठा btf *btf__base_btf(स्थिर काष्ठा btf *btf)
अणु
	वापस btf->base_btf;
पूर्ण

/* पूर्णांकernal helper वापसing non-स्थिर poपूर्णांकer to a type */
काष्ठा btf_type *btf_type_by_id(काष्ठा btf *btf, __u32 type_id)
अणु
	अगर (type_id == 0)
		वापस &btf_व्योम;
	अगर (type_id < btf->start_id)
		वापस btf_type_by_id(btf->base_btf, type_id);
	वापस btf->types_data + btf->type_offs[type_id - btf->start_id];
पूर्ण

स्थिर काष्ठा btf_type *btf__type_by_id(स्थिर काष्ठा btf *btf, __u32 type_id)
अणु
	अगर (type_id >= btf->start_id + btf->nr_types)
		वापस शून्य;
	वापस btf_type_by_id((काष्ठा btf *)btf, type_id);
पूर्ण

अटल पूर्णांक determine_ptr_size(स्थिर काष्ठा btf *btf)
अणु
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *name;
	पूर्णांक i, n;

	अगर (btf->base_btf && btf->base_btf->ptr_sz > 0)
		वापस btf->base_btf->ptr_sz;

	n = btf__get_nr_types(btf);
	क्रम (i = 1; i <= n; i++) अणु
		t = btf__type_by_id(btf, i);
		अगर (!btf_is_पूर्णांक(t))
			जारी;

		name = btf__name_by_offset(btf, t->name_off);
		अगर (!name)
			जारी;

		अगर (म_भेद(name, "long int") == 0 ||
		    म_भेद(name, "long unsigned int") == 0) अणु
			अगर (t->size != 4 && t->size != 8)
				जारी;
			वापस t->size;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल माप_प्रकार btf_ptr_sz(स्थिर काष्ठा btf *btf)
अणु
	अगर (!btf->ptr_sz)
		((काष्ठा btf *)btf)->ptr_sz = determine_ptr_size(btf);
	वापस btf->ptr_sz < 0 ? माप(व्योम *) : btf->ptr_sz;
पूर्ण

/* Return poपूर्णांकer size this BTF instance assumes. The size is heuristically
 * determined by looking क्रम 'long' or 'unsigned long' पूर्णांकeger type and
 * recording its size in bytes. If BTF type inक्रमmation करोesn't have any such
 * type, this function वापसs 0. In the latter हाल, native architecture's
 * poपूर्णांकer size is assumed, so will be either 4 or 8, depending on
 * architecture that libbpf was compiled क्रम. It's possible to override
 * guessed value by using btf__set_poपूर्णांकer_size() API.
 */
माप_प्रकार btf__poपूर्णांकer_size(स्थिर काष्ठा btf *btf)
अणु
	अगर (!btf->ptr_sz)
		((काष्ठा btf *)btf)->ptr_sz = determine_ptr_size(btf);

	अगर (btf->ptr_sz < 0)
		/* not enough BTF type info to guess */
		वापस 0;

	वापस btf->ptr_sz;
पूर्ण

/* Override or set poपूर्णांकer size in bytes. Only values of 4 and 8 are
 * supported.
 */
पूर्णांक btf__set_poपूर्णांकer_size(काष्ठा btf *btf, माप_प्रकार ptr_sz)
अणु
	अगर (ptr_sz != 4 && ptr_sz != 8)
		वापस -EINVAL;
	btf->ptr_sz = ptr_sz;
	वापस 0;
पूर्ण

अटल bool is_host_big_endian(व्योम)
अणु
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
	वापस false;
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
	वापस true;
#अन्यथा
# error "Unrecognized __BYTE_ORDER__"
#पूर्ण_अगर
पूर्ण

क्रमागत btf_endianness btf__endianness(स्थिर काष्ठा btf *btf)
अणु
	अगर (is_host_big_endian())
		वापस btf->swapped_endian ? BTF_LITTLE_ENDIAN : BTF_BIG_ENDIAN;
	अन्यथा
		वापस btf->swapped_endian ? BTF_BIG_ENDIAN : BTF_LITTLE_ENDIAN;
पूर्ण

पूर्णांक btf__set_endianness(काष्ठा btf *btf, क्रमागत btf_endianness endian)
अणु
	अगर (endian != BTF_LITTLE_ENDIAN && endian != BTF_BIG_ENDIAN)
		वापस -EINVAL;

	btf->swapped_endian = is_host_big_endian() != (endian == BTF_BIG_ENDIAN);
	अगर (!btf->swapped_endian) अणु
		मुक्त(btf->raw_data_swapped);
		btf->raw_data_swapped = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool btf_type_is_व्योम(स्थिर काष्ठा btf_type *t)
अणु
	वापस t == &btf_व्योम || btf_is_fwd(t);
पूर्ण

अटल bool btf_type_is_व्योम_or_null(स्थिर काष्ठा btf_type *t)
अणु
	वापस !t || btf_type_is_व्योम(t);
पूर्ण

#घोषणा MAX_RESOLVE_DEPTH 32

__s64 btf__resolve_size(स्थिर काष्ठा btf *btf, __u32 type_id)
अणु
	स्थिर काष्ठा btf_array *array;
	स्थिर काष्ठा btf_type *t;
	__u32 nelems = 1;
	__s64 size = -1;
	पूर्णांक i;

	t = btf__type_by_id(btf, type_id);
	क्रम (i = 0; i < MAX_RESOLVE_DEPTH && !btf_type_is_व्योम_or_null(t);
	     i++) अणु
		चयन (btf_kind(t)) अणु
		हाल BTF_KIND_INT:
		हाल BTF_KIND_STRUCT:
		हाल BTF_KIND_UNION:
		हाल BTF_KIND_ENUM:
		हाल BTF_KIND_DATASEC:
		हाल BTF_KIND_FLOAT:
			size = t->size;
			जाओ करोne;
		हाल BTF_KIND_PTR:
			size = btf_ptr_sz(btf);
			जाओ करोne;
		हाल BTF_KIND_TYPEDEF:
		हाल BTF_KIND_VOLATILE:
		हाल BTF_KIND_CONST:
		हाल BTF_KIND_RESTRICT:
		हाल BTF_KIND_VAR:
			type_id = t->type;
			अवरोध;
		हाल BTF_KIND_ARRAY:
			array = btf_array(t);
			अगर (nelems && array->nelems > UINT32_MAX / nelems)
				वापस -E2BIG;
			nelems *= array->nelems;
			type_id = array->type;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		t = btf__type_by_id(btf, type_id);
	पूर्ण

करोne:
	अगर (size < 0)
		वापस -EINVAL;
	अगर (nelems && size > UINT32_MAX / nelems)
		वापस -E2BIG;

	वापस nelems * size;
पूर्ण

पूर्णांक btf__align_of(स्थिर काष्ठा btf *btf, __u32 id)
अणु
	स्थिर काष्ठा btf_type *t = btf__type_by_id(btf, id);
	__u16 kind = btf_kind(t);

	चयन (kind) अणु
	हाल BTF_KIND_INT:
	हाल BTF_KIND_ENUM:
	हाल BTF_KIND_FLOAT:
		वापस min(btf_ptr_sz(btf), (माप_प्रकार)t->size);
	हाल BTF_KIND_PTR:
		वापस btf_ptr_sz(btf);
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_RESTRICT:
		वापस btf__align_of(btf, t->type);
	हाल BTF_KIND_ARRAY:
		वापस btf__align_of(btf, btf_array(t)->type);
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION: अणु
		स्थिर काष्ठा btf_member *m = btf_members(t);
		__u16 vlen = btf_vlen(t);
		पूर्णांक i, max_align = 1, align;

		क्रम (i = 0; i < vlen; i++, m++) अणु
			align = btf__align_of(btf, m->type);
			अगर (align <= 0)
				वापस align;
			max_align = max(max_align, align);
		पूर्ण

		वापस max_align;
	पूर्ण
	शेष:
		pr_warn("unsupported BTF_KIND:%u\n", btf_kind(t));
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक btf__resolve_type(स्थिर काष्ठा btf *btf, __u32 type_id)
अणु
	स्थिर काष्ठा btf_type *t;
	पूर्णांक depth = 0;

	t = btf__type_by_id(btf, type_id);
	जबतक (depth < MAX_RESOLVE_DEPTH &&
	       !btf_type_is_व्योम_or_null(t) &&
	       (btf_is_mod(t) || btf_is_प्रकार(t) || btf_is_var(t))) अणु
		type_id = t->type;
		t = btf__type_by_id(btf, type_id);
		depth++;
	पूर्ण

	अगर (depth == MAX_RESOLVE_DEPTH || btf_type_is_व्योम_or_null(t))
		वापस -EINVAL;

	वापस type_id;
पूर्ण

__s32 btf__find_by_name(स्थिर काष्ठा btf *btf, स्थिर अक्षर *type_name)
अणु
	__u32 i, nr_types = btf__get_nr_types(btf);

	अगर (!म_भेद(type_name, "void"))
		वापस 0;

	क्रम (i = 1; i <= nr_types; i++) अणु
		स्थिर काष्ठा btf_type *t = btf__type_by_id(btf, i);
		स्थिर अक्षर *name = btf__name_by_offset(btf, t->name_off);

		अगर (name && !म_भेद(type_name, name))
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

__s32 btf__find_by_name_kind(स्थिर काष्ठा btf *btf, स्थिर अक्षर *type_name,
			     __u32 kind)
अणु
	__u32 i, nr_types = btf__get_nr_types(btf);

	अगर (kind == BTF_KIND_UNKN || !म_भेद(type_name, "void"))
		वापस 0;

	क्रम (i = 1; i <= nr_types; i++) अणु
		स्थिर काष्ठा btf_type *t = btf__type_by_id(btf, i);
		स्थिर अक्षर *name;

		अगर (btf_kind(t) != kind)
			जारी;
		name = btf__name_by_offset(btf, t->name_off);
		अगर (name && !म_भेद(type_name, name))
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल bool btf_is_modअगरiable(स्थिर काष्ठा btf *btf)
अणु
	वापस (व्योम *)btf->hdr != btf->raw_data;
पूर्ण

व्योम btf__मुक्त(काष्ठा btf *btf)
अणु
	अगर (IS_ERR_OR_शून्य(btf))
		वापस;

	अगर (btf->fd >= 0)
		बंद(btf->fd);

	अगर (btf_is_modअगरiable(btf)) अणु
		/* अगर BTF was modअगरied after loading, it will have a split
		 * in-memory representation क्रम header, types, and strings
		 * sections, so we need to मुक्त all of them inभागidually. It
		 * might still have a cached contiguous raw data present,
		 * which will be unconditionally मुक्तd below.
		 */
		मुक्त(btf->hdr);
		मुक्त(btf->types_data);
		strset__मुक्त(btf->strs_set);
	पूर्ण
	मुक्त(btf->raw_data);
	मुक्त(btf->raw_data_swapped);
	मुक्त(btf->type_offs);
	मुक्त(btf);
पूर्ण

अटल काष्ठा btf *btf_new_empty(काष्ठा btf *base_btf)
अणु
	काष्ठा btf *btf;

	btf = सुस्मृति(1, माप(*btf));
	अगर (!btf)
		वापस ERR_PTR(-ENOMEM);

	btf->nr_types = 0;
	btf->start_id = 1;
	btf->start_str_off = 0;
	btf->fd = -1;
	btf->ptr_sz = माप(व्योम *);
	btf->swapped_endian = false;

	अगर (base_btf) अणु
		btf->base_btf = base_btf;
		btf->start_id = btf__get_nr_types(base_btf) + 1;
		btf->start_str_off = base_btf->hdr->str_len;
	पूर्ण

	/* +1 क्रम empty string at offset 0 */
	btf->raw_size = माप(काष्ठा btf_header) + (base_btf ? 0 : 1);
	btf->raw_data = सुस्मृति(1, btf->raw_size);
	अगर (!btf->raw_data) अणु
		मुक्त(btf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	btf->hdr = btf->raw_data;
	btf->hdr->hdr_len = माप(काष्ठा btf_header);
	btf->hdr->magic = BTF_MAGIC;
	btf->hdr->version = BTF_VERSION;

	btf->types_data = btf->raw_data + btf->hdr->hdr_len;
	btf->strs_data = btf->raw_data + btf->hdr->hdr_len;
	btf->hdr->str_len = base_btf ? 0 : 1; /* empty string at offset 0 */

	वापस btf;
पूर्ण

काष्ठा btf *btf__new_empty(व्योम)
अणु
	वापस btf_new_empty(शून्य);
पूर्ण

काष्ठा btf *btf__new_empty_split(काष्ठा btf *base_btf)
अणु
	वापस btf_new_empty(base_btf);
पूर्ण

अटल काष्ठा btf *btf_new(स्थिर व्योम *data, __u32 size, काष्ठा btf *base_btf)
अणु
	काष्ठा btf *btf;
	पूर्णांक err;

	btf = सुस्मृति(1, माप(काष्ठा btf));
	अगर (!btf)
		वापस ERR_PTR(-ENOMEM);

	btf->nr_types = 0;
	btf->start_id = 1;
	btf->start_str_off = 0;

	अगर (base_btf) अणु
		btf->base_btf = base_btf;
		btf->start_id = btf__get_nr_types(base_btf) + 1;
		btf->start_str_off = base_btf->hdr->str_len;
	पूर्ण

	btf->raw_data = दो_स्मृति(size);
	अगर (!btf->raw_data) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण
	स_नकल(btf->raw_data, data, size);
	btf->raw_size = size;

	btf->hdr = btf->raw_data;
	err = btf_parse_hdr(btf);
	अगर (err)
		जाओ करोne;

	btf->strs_data = btf->raw_data + btf->hdr->hdr_len + btf->hdr->str_off;
	btf->types_data = btf->raw_data + btf->hdr->hdr_len + btf->hdr->type_off;

	err = btf_parse_str_sec(btf);
	err = err ?: btf_parse_type_sec(btf);
	अगर (err)
		जाओ करोne;

	btf->fd = -1;

करोne:
	अगर (err) अणु
		btf__मुक्त(btf);
		वापस ERR_PTR(err);
	पूर्ण

	वापस btf;
पूर्ण

काष्ठा btf *btf__new(स्थिर व्योम *data, __u32 size)
अणु
	वापस btf_new(data, size, शून्य);
पूर्ण

अटल काष्ठा btf *btf_parse_elf(स्थिर अक्षर *path, काष्ठा btf *base_btf,
				 काष्ठा btf_ext **btf_ext)
अणु
	Elf_Data *btf_data = शून्य, *btf_ext_data = शून्य;
	पूर्णांक err = 0, fd = -1, idx = 0;
	काष्ठा btf *btf = शून्य;
	Elf_Scn *scn = शून्य;
	Elf *elf = शून्य;
	GElf_Ehdr ehdr;
	माप_प्रकार shstrndx;

	अगर (elf_version(EV_CURRENT) == EV_NONE) अणु
		pr_warn("failed to init libelf for %s\n", path);
		वापस ERR_PTR(-LIBBPF_ERRNO__LIBELF);
	पूर्ण

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("failed to open %s: %s\n", path, म_त्रुटि(त्रुटि_सं));
		वापस ERR_PTR(err);
	पूर्ण

	err = -LIBBPF_ERRNO__FORMAT;

	elf = elf_begin(fd, ELF_C_READ, शून्य);
	अगर (!elf) अणु
		pr_warn("failed to open %s as ELF file\n", path);
		जाओ करोne;
	पूर्ण
	अगर (!gelf_getehdr(elf, &ehdr)) अणु
		pr_warn("failed to get EHDR from %s\n", path);
		जाओ करोne;
	पूर्ण

	अगर (elf_माला_लोhdrstrndx(elf, &shstrndx)) अणु
		pr_warn("failed to get section names section index for %s\n",
			path);
		जाओ करोne;
	पूर्ण

	अगर (!elf_rawdata(elf_माला_लोcn(elf, shstrndx), शून्य)) अणु
		pr_warn("failed to get e_shstrndx from %s\n", path);
		जाओ करोne;
	पूर्ण

	जबतक ((scn = elf_nextscn(elf, scn)) != शून्य) अणु
		GElf_Shdr sh;
		अक्षर *name;

		idx++;
		अगर (gelf_माला_लोhdr(scn, &sh) != &sh) अणु
			pr_warn("failed to get section(%d) header from %s\n",
				idx, path);
			जाओ करोne;
		पूर्ण
		name = elf_strptr(elf, shstrndx, sh.sh_name);
		अगर (!name) अणु
			pr_warn("failed to get section(%d) name from %s\n",
				idx, path);
			जाओ करोne;
		पूर्ण
		अगर (म_भेद(name, BTF_ELF_SEC) == 0) अणु
			btf_data = elf_getdata(scn, 0);
			अगर (!btf_data) अणु
				pr_warn("failed to get section(%d, %s) data from %s\n",
					idx, name, path);
				जाओ करोne;
			पूर्ण
			जारी;
		पूर्ण अन्यथा अगर (btf_ext && म_भेद(name, BTF_EXT_ELF_SEC) == 0) अणु
			btf_ext_data = elf_getdata(scn, 0);
			अगर (!btf_ext_data) अणु
				pr_warn("failed to get section(%d, %s) data from %s\n",
					idx, name, path);
				जाओ करोne;
			पूर्ण
			जारी;
		पूर्ण
	पूर्ण

	err = 0;

	अगर (!btf_data) अणु
		err = -ENOENT;
		जाओ करोne;
	पूर्ण
	btf = btf_new(btf_data->d_buf, btf_data->d_size, base_btf);
	अगर (IS_ERR(btf))
		जाओ करोne;

	चयन (gelf_अ_लोlass(elf)) अणु
	हाल ELFCLASS32:
		btf__set_poपूर्णांकer_size(btf, 4);
		अवरोध;
	हाल ELFCLASS64:
		btf__set_poपूर्णांकer_size(btf, 8);
		अवरोध;
	शेष:
		pr_warn("failed to get ELF class (bitness) for %s\n", path);
		अवरोध;
	पूर्ण

	अगर (btf_ext && btf_ext_data) अणु
		*btf_ext = btf_ext__new(btf_ext_data->d_buf,
					btf_ext_data->d_size);
		अगर (IS_ERR(*btf_ext))
			जाओ करोne;
	पूर्ण अन्यथा अगर (btf_ext) अणु
		*btf_ext = शून्य;
	पूर्ण
करोne:
	अगर (elf)
		elf_end(elf);
	बंद(fd);

	अगर (err)
		वापस ERR_PTR(err);
	/*
	 * btf is always parsed beक्रमe btf_ext, so no need to clean up
	 * btf_ext, अगर btf loading failed
	 */
	अगर (IS_ERR(btf))
		वापस btf;
	अगर (btf_ext && IS_ERR(*btf_ext)) अणु
		btf__मुक्त(btf);
		err = PTR_ERR(*btf_ext);
		वापस ERR_PTR(err);
	पूर्ण
	वापस btf;
पूर्ण

काष्ठा btf *btf__parse_elf(स्थिर अक्षर *path, काष्ठा btf_ext **btf_ext)
अणु
	वापस btf_parse_elf(path, शून्य, btf_ext);
पूर्ण

काष्ठा btf *btf__parse_elf_split(स्थिर अक्षर *path, काष्ठा btf *base_btf)
अणु
	वापस btf_parse_elf(path, base_btf, शून्य);
पूर्ण

अटल काष्ठा btf *btf_parse_raw(स्थिर अक्षर *path, काष्ठा btf *base_btf)
अणु
	काष्ठा btf *btf = शून्य;
	व्योम *data = शून्य;
	खाता *f = शून्य;
	__u16 magic;
	पूर्णांक err = 0;
	दीर्घ sz;

	f = ख_खोलो(path, "rb");
	अगर (!f) अणु
		err = -त्रुटि_सं;
		जाओ err_out;
	पूर्ण

	/* check BTF magic */
	अगर (ख_पढ़ो(&magic, 1, माप(magic), f) < माप(magic)) अणु
		err = -EIO;
		जाओ err_out;
	पूर्ण
	अगर (magic != BTF_MAGIC && magic != bswap_16(BTF_MAGIC)) अणु
		/* definitely not a raw BTF */
		err = -EPROTO;
		जाओ err_out;
	पूर्ण

	/* get file size */
	अगर (ख_जाओ(f, 0, अंत_से)) अणु
		err = -त्रुटि_सं;
		जाओ err_out;
	पूर्ण
	sz = ख_बताओ(f);
	अगर (sz < 0) अणु
		err = -त्रुटि_सं;
		जाओ err_out;
	पूर्ण
	/* शुरुआत to the start */
	अगर (ख_जाओ(f, 0, शुरू_से)) अणु
		err = -त्रुटि_सं;
		जाओ err_out;
	पूर्ण

	/* pre-alloc memory and पढ़ो all of BTF data */
	data = दो_स्मृति(sz);
	अगर (!data) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	अगर (ख_पढ़ो(data, 1, sz, f) < sz) अणु
		err = -EIO;
		जाओ err_out;
	पूर्ण

	/* finally parse BTF data */
	btf = btf_new(data, sz, base_btf);

err_out:
	मुक्त(data);
	अगर (f)
		ख_बंद(f);
	वापस err ? ERR_PTR(err) : btf;
पूर्ण

काष्ठा btf *btf__parse_raw(स्थिर अक्षर *path)
अणु
	वापस btf_parse_raw(path, शून्य);
पूर्ण

काष्ठा btf *btf__parse_raw_split(स्थिर अक्षर *path, काष्ठा btf *base_btf)
अणु
	वापस btf_parse_raw(path, base_btf);
पूर्ण

अटल काष्ठा btf *btf_parse(स्थिर अक्षर *path, काष्ठा btf *base_btf, काष्ठा btf_ext **btf_ext)
अणु
	काष्ठा btf *btf;

	अगर (btf_ext)
		*btf_ext = शून्य;

	btf = btf_parse_raw(path, base_btf);
	अगर (!IS_ERR(btf) || PTR_ERR(btf) != -EPROTO)
		वापस btf;

	वापस btf_parse_elf(path, base_btf, btf_ext);
पूर्ण

काष्ठा btf *btf__parse(स्थिर अक्षर *path, काष्ठा btf_ext **btf_ext)
अणु
	वापस btf_parse(path, शून्य, btf_ext);
पूर्ण

काष्ठा btf *btf__parse_split(स्थिर अक्षर *path, काष्ठा btf *base_btf)
अणु
	वापस btf_parse(path, base_btf, शून्य);
पूर्ण

अटल पूर्णांक compare_vsi_off(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा btf_var_secinfo *a = _a;
	स्थिर काष्ठा btf_var_secinfo *b = _b;

	वापस a->offset - b->offset;
पूर्ण

अटल पूर्णांक btf_fixup_datasec(काष्ठा bpf_object *obj, काष्ठा btf *btf,
			     काष्ठा btf_type *t)
अणु
	__u32 size = 0, off = 0, i, vars = btf_vlen(t);
	स्थिर अक्षर *name = btf__name_by_offset(btf, t->name_off);
	स्थिर काष्ठा btf_type *t_var;
	काष्ठा btf_var_secinfo *vsi;
	स्थिर काष्ठा btf_var *var;
	पूर्णांक ret;

	अगर (!name) अणु
		pr_debug("No name found in string section for DATASEC kind.\n");
		वापस -ENOENT;
	पूर्ण

	/* .बाह्य datasec size and var offsets were set correctly during
	 * बाह्य collection step, so just skip straight to sorting variables
	 */
	अगर (t->size)
		जाओ sort_vars;

	ret = bpf_object__section_size(obj, name, &size);
	अगर (ret || !size || (t->size && t->size != size)) अणु
		pr_debug("Invalid size for section %s: %u bytes\n", name, size);
		वापस -ENOENT;
	पूर्ण

	t->size = size;

	क्रम (i = 0, vsi = btf_var_secinfos(t); i < vars; i++, vsi++) अणु
		t_var = btf__type_by_id(btf, vsi->type);
		var = btf_var(t_var);

		अगर (!btf_is_var(t_var)) अणु
			pr_debug("Non-VAR type seen in section %s\n", name);
			वापस -EINVAL;
		पूर्ण

		अगर (var->linkage == BTF_VAR_STATIC)
			जारी;

		name = btf__name_by_offset(btf, t_var->name_off);
		अगर (!name) अणु
			pr_debug("No name found in string section for VAR kind\n");
			वापस -ENOENT;
		पूर्ण

		ret = bpf_object__variable_offset(obj, name, &off);
		अगर (ret) अणु
			pr_debug("No offset found in symbol table for VAR %s\n",
				 name);
			वापस -ENOENT;
		पूर्ण

		vsi->offset = off;
	पूर्ण

sort_vars:
	क्विक(btf_var_secinfos(t), vars, माप(*vsi), compare_vsi_off);
	वापस 0;
पूर्ण

पूर्णांक btf__finalize_data(काष्ठा bpf_object *obj, काष्ठा btf *btf)
अणु
	पूर्णांक err = 0;
	__u32 i;

	क्रम (i = 1; i <= btf->nr_types; i++) अणु
		काष्ठा btf_type *t = btf_type_by_id(btf, i);

		/* Loader needs to fix up some of the things compiler
		 * couldn't get its hands on जबतक emitting BTF. This
		 * is section size and global variable offset. We use
		 * the info from the ELF itself क्रम this purpose.
		 */
		अगर (btf_is_datasec(t)) अणु
			err = btf_fixup_datasec(obj, btf, t);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम *btf_get_raw_data(स्थिर काष्ठा btf *btf, __u32 *size, bool swap_endian);

पूर्णांक btf__load(काष्ठा btf *btf)
अणु
	__u32 log_buf_size = 0, raw_size;
	अक्षर *log_buf = शून्य;
	व्योम *raw_data;
	पूर्णांक err = 0;

	अगर (btf->fd >= 0)
		वापस -EEXIST;

retry_load:
	अगर (log_buf_size) अणु
		log_buf = दो_स्मृति(log_buf_size);
		अगर (!log_buf)
			वापस -ENOMEM;

		*log_buf = 0;
	पूर्ण

	raw_data = btf_get_raw_data(btf, &raw_size, false);
	अगर (!raw_data) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण
	/* cache native raw data representation */
	btf->raw_size = raw_size;
	btf->raw_data = raw_data;

	btf->fd = bpf_load_btf(raw_data, raw_size, log_buf, log_buf_size, false);
	अगर (btf->fd < 0) अणु
		अगर (!log_buf || त्रुटि_सं == ENOSPC) अणु
			log_buf_size = max((__u32)BPF_LOG_BUF_SIZE,
					   log_buf_size << 1);
			मुक्त(log_buf);
			जाओ retry_load;
		पूर्ण

		err = -त्रुटि_सं;
		pr_warn("Error loading BTF: %s(%d)\n", म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
		अगर (*log_buf)
			pr_warn("%s\n", log_buf);
		जाओ करोne;
	पूर्ण

करोne:
	मुक्त(log_buf);
	वापस err;
पूर्ण

पूर्णांक btf__fd(स्थिर काष्ठा btf *btf)
अणु
	वापस btf->fd;
पूर्ण

व्योम btf__set_fd(काष्ठा btf *btf, पूर्णांक fd)
अणु
	btf->fd = fd;
पूर्ण

अटल स्थिर व्योम *btf_strs_data(स्थिर काष्ठा btf *btf)
अणु
	वापस btf->strs_data ? btf->strs_data : strset__data(btf->strs_set);
पूर्ण

अटल व्योम *btf_get_raw_data(स्थिर काष्ठा btf *btf, __u32 *size, bool swap_endian)
अणु
	काष्ठा btf_header *hdr = btf->hdr;
	काष्ठा btf_type *t;
	व्योम *data, *p;
	__u32 data_sz;
	पूर्णांक i;

	data = swap_endian ? btf->raw_data_swapped : btf->raw_data;
	अगर (data) अणु
		*size = btf->raw_size;
		वापस data;
	पूर्ण

	data_sz = hdr->hdr_len + hdr->type_len + hdr->str_len;
	data = सुस्मृति(1, data_sz);
	अगर (!data)
		वापस शून्य;
	p = data;

	स_नकल(p, hdr, hdr->hdr_len);
	अगर (swap_endian)
		btf_bswap_hdr(p);
	p += hdr->hdr_len;

	स_नकल(p, btf->types_data, hdr->type_len);
	अगर (swap_endian) अणु
		क्रम (i = 0; i < btf->nr_types; i++) अणु
			t = p + btf->type_offs[i];
			/* btf_bswap_type_rest() relies on native t->info, so
			 * we swap base type info after we swapped all the
			 * additional inक्रमmation
			 */
			अगर (btf_bswap_type_rest(t))
				जाओ err_out;
			btf_bswap_type_base(t);
		पूर्ण
	पूर्ण
	p += hdr->type_len;

	स_नकल(p, btf_strs_data(btf), hdr->str_len);
	p += hdr->str_len;

	*size = data_sz;
	वापस data;
err_out:
	मुक्त(data);
	वापस शून्य;
पूर्ण

स्थिर व्योम *btf__get_raw_data(स्थिर काष्ठा btf *btf_ro, __u32 *size)
अणु
	काष्ठा btf *btf = (काष्ठा btf *)btf_ro;
	__u32 data_sz;
	व्योम *data;

	data = btf_get_raw_data(btf, &data_sz, btf->swapped_endian);
	अगर (!data)
		वापस शून्य;

	btf->raw_size = data_sz;
	अगर (btf->swapped_endian)
		btf->raw_data_swapped = data;
	अन्यथा
		btf->raw_data = data;
	*size = data_sz;
	वापस data;
पूर्ण

स्थिर अक्षर *btf__str_by_offset(स्थिर काष्ठा btf *btf, __u32 offset)
अणु
	अगर (offset < btf->start_str_off)
		वापस btf__str_by_offset(btf->base_btf, offset);
	अन्यथा अगर (offset - btf->start_str_off < btf->hdr->str_len)
		वापस btf_strs_data(btf) + (offset - btf->start_str_off);
	अन्यथा
		वापस शून्य;
पूर्ण

स्थिर अक्षर *btf__name_by_offset(स्थिर काष्ठा btf *btf, __u32 offset)
अणु
	वापस btf__str_by_offset(btf, offset);
पूर्ण

काष्ठा btf *btf_get_from_fd(पूर्णांक btf_fd, काष्ठा btf *base_btf)
अणु
	काष्ठा bpf_btf_info btf_info;
	__u32 len = माप(btf_info);
	__u32 last_size;
	काष्ठा btf *btf;
	व्योम *ptr;
	पूर्णांक err;

	/* we won't know btf_size until we call bpf_obj_get_info_by_fd(). so
	 * let's start with a sane शेष - 4KiB here - and resize it only अगर
	 * bpf_obj_get_info_by_fd() needs a bigger buffer.
	 */
	last_size = 4096;
	ptr = दो_स्मृति(last_size);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	स_रखो(&btf_info, 0, माप(btf_info));
	btf_info.btf = ptr_to_u64(ptr);
	btf_info.btf_size = last_size;
	err = bpf_obj_get_info_by_fd(btf_fd, &btf_info, &len);

	अगर (!err && btf_info.btf_size > last_size) अणु
		व्योम *temp_ptr;

		last_size = btf_info.btf_size;
		temp_ptr = पुनः_स्मृति(ptr, last_size);
		अगर (!temp_ptr) अणु
			btf = ERR_PTR(-ENOMEM);
			जाओ निकास_मुक्त;
		पूर्ण
		ptr = temp_ptr;

		len = माप(btf_info);
		स_रखो(&btf_info, 0, माप(btf_info));
		btf_info.btf = ptr_to_u64(ptr);
		btf_info.btf_size = last_size;

		err = bpf_obj_get_info_by_fd(btf_fd, &btf_info, &len);
	पूर्ण

	अगर (err || btf_info.btf_size > last_size) अणु
		btf = err ? ERR_PTR(-त्रुटि_सं) : ERR_PTR(-E2BIG);
		जाओ निकास_मुक्त;
	पूर्ण

	btf = btf_new(ptr, btf_info.btf_size, base_btf);

निकास_मुक्त:
	मुक्त(ptr);
	वापस btf;
पूर्ण

पूर्णांक btf__get_from_id(__u32 id, काष्ठा btf **btf)
अणु
	काष्ठा btf *res;
	पूर्णांक btf_fd;

	*btf = शून्य;
	btf_fd = bpf_btf_get_fd_by_id(id);
	अगर (btf_fd < 0)
		वापस -त्रुटि_सं;

	res = btf_get_from_fd(btf_fd, शून्य);
	बंद(btf_fd);
	अगर (IS_ERR(res))
		वापस PTR_ERR(res);

	*btf = res;
	वापस 0;
पूर्ण

पूर्णांक btf__get_map_kv_tids(स्थिर काष्ठा btf *btf, स्थिर अक्षर *map_name,
			 __u32 expected_key_size, __u32 expected_value_size,
			 __u32 *key_type_id, __u32 *value_type_id)
अणु
	स्थिर काष्ठा btf_type *container_type;
	स्थिर काष्ठा btf_member *key, *value;
	स्थिर माप_प्रकार max_name = 256;
	अक्षर container_name[max_name];
	__s64 key_size, value_size;
	__s32 container_id;

	अगर (snम_लिखो(container_name, max_name, "____btf_map_%s", map_name) ==
	    max_name) अणु
		pr_warn("map:%s length of '____btf_map_%s' is too long\n",
			map_name, map_name);
		वापस -EINVAL;
	पूर्ण

	container_id = btf__find_by_name(btf, container_name);
	अगर (container_id < 0) अणु
		pr_debug("map:%s container_name:%s cannot be found in BTF. Missing BPF_ANNOTATE_KV_PAIR?\n",
			 map_name, container_name);
		वापस container_id;
	पूर्ण

	container_type = btf__type_by_id(btf, container_id);
	अगर (!container_type) अणु
		pr_warn("map:%s cannot find BTF type for container_id:%u\n",
			map_name, container_id);
		वापस -EINVAL;
	पूर्ण

	अगर (!btf_is_काष्ठा(container_type) || btf_vlen(container_type) < 2) अणु
		pr_warn("map:%s container_name:%s is an invalid container struct\n",
			map_name, container_name);
		वापस -EINVAL;
	पूर्ण

	key = btf_members(container_type);
	value = key + 1;

	key_size = btf__resolve_size(btf, key->type);
	अगर (key_size < 0) अणु
		pr_warn("map:%s invalid BTF key_type_size\n", map_name);
		वापस key_size;
	पूर्ण

	अगर (expected_key_size != key_size) अणु
		pr_warn("map:%s btf_key_type_size:%u != map_def_key_size:%u\n",
			map_name, (__u32)key_size, expected_key_size);
		वापस -EINVAL;
	पूर्ण

	value_size = btf__resolve_size(btf, value->type);
	अगर (value_size < 0) अणु
		pr_warn("map:%s invalid BTF value_type_size\n", map_name);
		वापस value_size;
	पूर्ण

	अगर (expected_value_size != value_size) अणु
		pr_warn("map:%s btf_value_type_size:%u != map_def_value_size:%u\n",
			map_name, (__u32)value_size, expected_value_size);
		वापस -EINVAL;
	पूर्ण

	*key_type_id = key->type;
	*value_type_id = value->type;

	वापस 0;
पूर्ण

अटल व्योम btf_invalidate_raw_data(काष्ठा btf *btf)
अणु
	अगर (btf->raw_data) अणु
		मुक्त(btf->raw_data);
		btf->raw_data = शून्य;
	पूर्ण
	अगर (btf->raw_data_swapped) अणु
		मुक्त(btf->raw_data_swapped);
		btf->raw_data_swapped = शून्य;
	पूर्ण
पूर्ण

/* Ensure BTF is पढ़ोy to be modअगरied (by splitting पूर्णांकo a three memory
 * regions क्रम header, types, and strings). Also invalidate cached
 * raw_data, अगर any.
 */
अटल पूर्णांक btf_ensure_modअगरiable(काष्ठा btf *btf)
अणु
	व्योम *hdr, *types;
	काष्ठा strset *set = शून्य;
	पूर्णांक err = -ENOMEM;

	अगर (btf_is_modअगरiable(btf)) अणु
		/* any BTF modअगरication invalidates raw_data */
		btf_invalidate_raw_data(btf);
		वापस 0;
	पूर्ण

	/* split raw data पूर्णांकo three memory regions */
	hdr = दो_स्मृति(btf->hdr->hdr_len);
	types = दो_स्मृति(btf->hdr->type_len);
	अगर (!hdr || !types)
		जाओ err_out;

	स_नकल(hdr, btf->hdr, btf->hdr->hdr_len);
	स_नकल(types, btf->types_data, btf->hdr->type_len);

	/* build lookup index क्रम all strings */
	set = strset__new(BTF_MAX_STR_OFFSET, btf->strs_data, btf->hdr->str_len);
	अगर (IS_ERR(set)) अणु
		err = PTR_ERR(set);
		जाओ err_out;
	पूर्ण

	/* only when everything was successful, update पूर्णांकernal state */
	btf->hdr = hdr;
	btf->types_data = types;
	btf->types_data_cap = btf->hdr->type_len;
	btf->strs_data = शून्य;
	btf->strs_set = set;
	/* अगर BTF was created from scratch, all strings are guaranteed to be
	 * unique and deduplicated
	 */
	अगर (btf->hdr->str_len == 0)
		btf->strs_deduped = true;
	अगर (!btf->base_btf && btf->hdr->str_len == 1)
		btf->strs_deduped = true;

	/* invalidate raw_data representation */
	btf_invalidate_raw_data(btf);

	वापस 0;

err_out:
	strset__मुक्त(set);
	मुक्त(hdr);
	मुक्त(types);
	वापस err;
पूर्ण

/* Find an offset in BTF string section that corresponds to a given string *s*.
 * Returns:
 *   - >0 offset पूर्णांकo string section, अगर string is found;
 *   - -ENOENT, अगर string is not in the string section;
 *   - <0, on any other error.
 */
पूर्णांक btf__find_str(काष्ठा btf *btf, स्थिर अक्षर *s)
अणु
	पूर्णांक off;

	अगर (btf->base_btf) अणु
		off = btf__find_str(btf->base_btf, s);
		अगर (off != -ENOENT)
			वापस off;
	पूर्ण

	/* BTF needs to be in a modअगरiable state to build string lookup index */
	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	off = strset__find_str(btf->strs_set, s);
	अगर (off < 0)
		वापस off;

	वापस btf->start_str_off + off;
पूर्ण

/* Add a string s to the BTF string section.
 * Returns:
 *   - > 0 offset पूर्णांकo string section, on success;
 *   - < 0, on error.
 */
पूर्णांक btf__add_str(काष्ठा btf *btf, स्थिर अक्षर *s)
अणु
	पूर्णांक off;

	अगर (btf->base_btf) अणु
		off = btf__find_str(btf->base_btf, s);
		अगर (off != -ENOENT)
			वापस off;
	पूर्ण

	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	off = strset__add_str(btf->strs_set, s);
	अगर (off < 0)
		वापस off;

	btf->hdr->str_len = strset__data_size(btf->strs_set);

	वापस btf->start_str_off + off;
पूर्ण

अटल व्योम *btf_add_type_mem(काष्ठा btf *btf, माप_प्रकार add_sz)
अणु
	वापस libbpf_add_mem(&btf->types_data, &btf->types_data_cap, 1,
			      btf->hdr->type_len, अच_पूर्णांक_उच्च, add_sz);
पूर्ण

अटल व्योम btf_type_inc_vlen(काष्ठा btf_type *t)
अणु
	t->info = btf_type_info(btf_kind(t), btf_vlen(t) + 1, btf_kflag(t));
पूर्ण

अटल पूर्णांक btf_commit_type(काष्ठा btf *btf, पूर्णांक data_sz)
अणु
	पूर्णांक err;

	err = btf_add_type_idx_entry(btf, btf->hdr->type_len);
	अगर (err)
		वापस err;

	btf->hdr->type_len += data_sz;
	btf->hdr->str_off += data_sz;
	btf->nr_types++;
	वापस btf->start_id + btf->nr_types - 1;
पूर्ण

काष्ठा btf_pipe अणु
	स्थिर काष्ठा btf *src;
	काष्ठा btf *dst;
पूर्ण;

अटल पूर्णांक btf_reग_लिखो_str(__u32 *str_off, व्योम *ctx)
अणु
	काष्ठा btf_pipe *p = ctx;
	पूर्णांक off;

	अगर (!*str_off) /* nothing to करो क्रम empty strings */
		वापस 0;

	off = btf__add_str(p->dst, btf__str_by_offset(p->src, *str_off));
	अगर (off < 0)
		वापस off;

	*str_off = off;
	वापस 0;
पूर्ण

पूर्णांक btf__add_type(काष्ठा btf *btf, स्थिर काष्ठा btf *src_btf, स्थिर काष्ठा btf_type *src_type)
अणु
	काष्ठा btf_pipe p = अणु .src = src_btf, .dst = btf पूर्ण;
	काष्ठा btf_type *t;
	पूर्णांक sz, err;

	sz = btf_type_size(src_type);
	अगर (sz < 0)
		वापस sz;

	/* deस्थिरruct BTF, अगर necessary, and invalidate raw_data */
	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	स_नकल(t, src_type, sz);

	err = btf_type_visit_str_offs(t, btf_reग_लिखो_str, &p);
	अगर (err)
		वापस err;

	वापस btf_commit_type(btf, sz);
पूर्ण

/*
 * Append new BTF_KIND_INT type with:
 *   - *name* - non-empty, non-शून्य type name;
 *   - *sz* - घातer-of-2 (1, 2, 4, ..) size of the type, in bytes;
 *   - encoding is a combination of BTF_INT_SIGNED, BTF_INT_CHAR, BTF_INT_BOOL.
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_पूर्णांक(काष्ठा btf *btf, स्थिर अक्षर *name, माप_प्रकार byte_sz, पूर्णांक encoding)
अणु
	काष्ठा btf_type *t;
	पूर्णांक sz, name_off;

	/* non-empty name */
	अगर (!name || !name[0])
		वापस -EINVAL;
	/* byte_sz must be घातer of 2 */
	अगर (!byte_sz || (byte_sz & (byte_sz - 1)) || byte_sz > 16)
		वापस -EINVAL;
	अगर (encoding & ~(BTF_INT_SIGNED | BTF_INT_CHAR | BTF_INT_BOOL))
		वापस -EINVAL;

	/* deस्थिरruct BTF, अगर necessary, and invalidate raw_data */
	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_type) + माप(पूर्णांक);
	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	/* अगर something goes wrong later, we might end up with an extra string,
	 * but that shouldn't be a problem, because BTF can't be स्थिरructed
	 * completely anyway and will most probably be just discarded
	 */
	name_off = btf__add_str(btf, name);
	अगर (name_off < 0)
		वापस name_off;

	t->name_off = name_off;
	t->info = btf_type_info(BTF_KIND_INT, 0, 0);
	t->size = byte_sz;
	/* set INT info, we करोn't allow setting legacy bit offset/size */
	*(__u32 *)(t + 1) = (encoding << 24) | (byte_sz * 8);

	वापस btf_commit_type(btf, sz);
पूर्ण

/*
 * Append new BTF_KIND_FLOAT type with:
 *   - *name* - non-empty, non-शून्य type name;
 *   - *sz* - size of the type, in bytes;
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_भग्न(काष्ठा btf *btf, स्थिर अक्षर *name, माप_प्रकार byte_sz)
अणु
	काष्ठा btf_type *t;
	पूर्णांक sz, name_off;

	/* non-empty name */
	अगर (!name || !name[0])
		वापस -EINVAL;

	/* byte_sz must be one of the explicitly allowed values */
	अगर (byte_sz != 2 && byte_sz != 4 && byte_sz != 8 && byte_sz != 12 &&
	    byte_sz != 16)
		वापस -EINVAL;

	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_type);
	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	name_off = btf__add_str(btf, name);
	अगर (name_off < 0)
		वापस name_off;

	t->name_off = name_off;
	t->info = btf_type_info(BTF_KIND_FLOAT, 0, 0);
	t->size = byte_sz;

	वापस btf_commit_type(btf, sz);
पूर्ण

/* it's completely legal to append BTF types with type IDs poपूर्णांकing क्रमward to
 * types that haven't been appended yet, so we only make sure that id looks
 * sane, we can't guarantee that ID will always be valid
 */
अटल पूर्णांक validate_type_id(पूर्णांक id)
अणु
	अगर (id < 0 || id > BTF_MAX_NR_TYPES)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/* generic append function क्रम PTR, TYPEDEF, CONST/VOLATILE/RESTRICT */
अटल पूर्णांक btf_add_ref_kind(काष्ठा btf *btf, पूर्णांक kind, स्थिर अक्षर *name, पूर्णांक ref_type_id)
अणु
	काष्ठा btf_type *t;
	पूर्णांक sz, name_off = 0;

	अगर (validate_type_id(ref_type_id))
		वापस -EINVAL;

	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_type);
	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	अगर (name && name[0]) अणु
		name_off = btf__add_str(btf, name);
		अगर (name_off < 0)
			वापस name_off;
	पूर्ण

	t->name_off = name_off;
	t->info = btf_type_info(kind, 0, 0);
	t->type = ref_type_id;

	वापस btf_commit_type(btf, sz);
पूर्ण

/*
 * Append new BTF_KIND_PTR type with:
 *   - *ref_type_id* - referenced type ID, it might not exist yet;
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_ptr(काष्ठा btf *btf, पूर्णांक ref_type_id)
अणु
	वापस btf_add_ref_kind(btf, BTF_KIND_PTR, शून्य, ref_type_id);
पूर्ण

/*
 * Append new BTF_KIND_ARRAY type with:
 *   - *index_type_id* - type ID of the type describing array index;
 *   - *elem_type_id* - type ID of the type describing array element;
 *   - *nr_elems* - the size of the array;
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_array(काष्ठा btf *btf, पूर्णांक index_type_id, पूर्णांक elem_type_id, __u32 nr_elems)
अणु
	काष्ठा btf_type *t;
	काष्ठा btf_array *a;
	पूर्णांक sz;

	अगर (validate_type_id(index_type_id) || validate_type_id(elem_type_id))
		वापस -EINVAL;

	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_type) + माप(काष्ठा btf_array);
	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	t->name_off = 0;
	t->info = btf_type_info(BTF_KIND_ARRAY, 0, 0);
	t->size = 0;

	a = btf_array(t);
	a->type = elem_type_id;
	a->index_type = index_type_id;
	a->nelems = nr_elems;

	वापस btf_commit_type(btf, sz);
पूर्ण

/* generic STRUCT/UNION append function */
अटल पूर्णांक btf_add_composite(काष्ठा btf *btf, पूर्णांक kind, स्थिर अक्षर *name, __u32 bytes_sz)
अणु
	काष्ठा btf_type *t;
	पूर्णांक sz, name_off = 0;

	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_type);
	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	अगर (name && name[0]) अणु
		name_off = btf__add_str(btf, name);
		अगर (name_off < 0)
			वापस name_off;
	पूर्ण

	/* start out with vlen=0 and no kflag; this will be adjusted when
	 * adding each member
	 */
	t->name_off = name_off;
	t->info = btf_type_info(kind, 0, 0);
	t->size = bytes_sz;

	वापस btf_commit_type(btf, sz);
पूर्ण

/*
 * Append new BTF_KIND_STRUCT type with:
 *   - *name* - name of the काष्ठा, can be शून्य or empty क्रम anonymous काष्ठाs;
 *   - *byte_sz* - size of the काष्ठा, in bytes;
 *
 * Struct initially has no fields in it. Fields can be added by
 * btf__add_field() right after btf__add_काष्ठा() succeeds.
 *
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_काष्ठा(काष्ठा btf *btf, स्थिर अक्षर *name, __u32 byte_sz)
अणु
	वापस btf_add_composite(btf, BTF_KIND_STRUCT, name, byte_sz);
पूर्ण

/*
 * Append new BTF_KIND_UNION type with:
 *   - *name* - name of the जोड़, can be शून्य or empty क्रम anonymous जोड़;
 *   - *byte_sz* - size of the जोड़, in bytes;
 *
 * Union initially has no fields in it. Fields can be added by
 * btf__add_field() right after btf__add_जोड़() succeeds. All fields
 * should have *bit_offset* of 0.
 *
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_जोड़(काष्ठा btf *btf, स्थिर अक्षर *name, __u32 byte_sz)
अणु
	वापस btf_add_composite(btf, BTF_KIND_UNION, name, byte_sz);
पूर्ण

अटल काष्ठा btf_type *btf_last_type(काष्ठा btf *btf)
अणु
	वापस btf_type_by_id(btf, btf__get_nr_types(btf));
पूर्ण

/*
 * Append new field क्रम the current STRUCT/UNION type with:
 *   - *name* - name of the field, can be शून्य or empty क्रम anonymous field;
 *   - *type_id* - type ID क्रम the type describing field type;
 *   - *bit_offset* - bit offset of the start of the field within काष्ठा/जोड़;
 *   - *bit_size* - bit size of a bitfield, 0 क्रम non-bitfield fields;
 * Returns:
 *   -  0, on success;
 *   - <0, on error.
 */
पूर्णांक btf__add_field(काष्ठा btf *btf, स्थिर अक्षर *name, पूर्णांक type_id,
		   __u32 bit_offset, __u32 bit_size)
अणु
	काष्ठा btf_type *t;
	काष्ठा btf_member *m;
	bool is_bitfield;
	पूर्णांक sz, name_off = 0;

	/* last type should be जोड़/काष्ठा */
	अगर (btf->nr_types == 0)
		वापस -EINVAL;
	t = btf_last_type(btf);
	अगर (!btf_is_composite(t))
		वापस -EINVAL;

	अगर (validate_type_id(type_id))
		वापस -EINVAL;
	/* best-efक्रमt bit field offset/size enक्रमcement */
	is_bitfield = bit_size || (bit_offset % 8 != 0);
	अगर (is_bitfield && (bit_size == 0 || bit_size > 255 || bit_offset > 0xffffff))
		वापस -EINVAL;

	/* only offset 0 is allowed क्रम जोड़s */
	अगर (btf_is_जोड़(t) && bit_offset)
		वापस -EINVAL;

	/* decompose and invalidate raw data */
	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_member);
	m = btf_add_type_mem(btf, sz);
	अगर (!m)
		वापस -ENOMEM;

	अगर (name && name[0]) अणु
		name_off = btf__add_str(btf, name);
		अगर (name_off < 0)
			वापस name_off;
	पूर्ण

	m->name_off = name_off;
	m->type = type_id;
	m->offset = bit_offset | (bit_size << 24);

	/* btf_add_type_mem can invalidate t poपूर्णांकer */
	t = btf_last_type(btf);
	/* update parent type's vlen and kflag */
	t->info = btf_type_info(btf_kind(t), btf_vlen(t) + 1, is_bitfield || btf_kflag(t));

	btf->hdr->type_len += sz;
	btf->hdr->str_off += sz;
	वापस 0;
पूर्ण

/*
 * Append new BTF_KIND_ENUM type with:
 *   - *name* - name of the क्रमागत, can be शून्य or empty क्रम anonymous क्रमागतs;
 *   - *byte_sz* - size of the क्रमागत, in bytes.
 *
 * Enum initially has no क्रमागत values in it (and corresponds to क्रमागत क्रमward
 * declaration). Enumerator values can be added by btf__add_क्रमागत_value()
 * immediately after btf__add_क्रमागत() succeeds.
 *
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_क्रमागत(काष्ठा btf *btf, स्थिर अक्षर *name, __u32 byte_sz)
अणु
	काष्ठा btf_type *t;
	पूर्णांक sz, name_off = 0;

	/* byte_sz must be घातer of 2 */
	अगर (!byte_sz || (byte_sz & (byte_sz - 1)) || byte_sz > 8)
		वापस -EINVAL;

	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_type);
	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	अगर (name && name[0]) अणु
		name_off = btf__add_str(btf, name);
		अगर (name_off < 0)
			वापस name_off;
	पूर्ण

	/* start out with vlen=0; it will be adjusted when adding क्रमागत values */
	t->name_off = name_off;
	t->info = btf_type_info(BTF_KIND_ENUM, 0, 0);
	t->size = byte_sz;

	वापस btf_commit_type(btf, sz);
पूर्ण

/*
 * Append new क्रमागत value क्रम the current ENUM type with:
 *   - *name* - name of the क्रमागतerator value, can't be शून्य or empty;
 *   - *value* - पूर्णांकeger value corresponding to क्रमागत value *name*;
 * Returns:
 *   -  0, on success;
 *   - <0, on error.
 */
पूर्णांक btf__add_क्रमागत_value(काष्ठा btf *btf, स्थिर अक्षर *name, __s64 value)
अणु
	काष्ठा btf_type *t;
	काष्ठा btf_क्रमागत *v;
	पूर्णांक sz, name_off;

	/* last type should be BTF_KIND_ENUM */
	अगर (btf->nr_types == 0)
		वापस -EINVAL;
	t = btf_last_type(btf);
	अगर (!btf_is_क्रमागत(t))
		वापस -EINVAL;

	/* non-empty name */
	अगर (!name || !name[0])
		वापस -EINVAL;
	अगर (value < पूर्णांक_न्यून || value > अच_पूर्णांक_उच्च)
		वापस -E2BIG;

	/* decompose and invalidate raw data */
	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_क्रमागत);
	v = btf_add_type_mem(btf, sz);
	अगर (!v)
		वापस -ENOMEM;

	name_off = btf__add_str(btf, name);
	अगर (name_off < 0)
		वापस name_off;

	v->name_off = name_off;
	v->val = value;

	/* update parent type's vlen */
	t = btf_last_type(btf);
	btf_type_inc_vlen(t);

	btf->hdr->type_len += sz;
	btf->hdr->str_off += sz;
	वापस 0;
पूर्ण

/*
 * Append new BTF_KIND_FWD type with:
 *   - *name*, non-empty/non-शून्य name;
 *   - *fwd_kind*, kind of क्रमward declaration, one of BTF_FWD_STRUCT,
 *     BTF_FWD_UNION, or BTF_FWD_ENUM;
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_fwd(काष्ठा btf *btf, स्थिर अक्षर *name, क्रमागत btf_fwd_kind fwd_kind)
अणु
	अगर (!name || !name[0])
		वापस -EINVAL;

	चयन (fwd_kind) अणु
	हाल BTF_FWD_STRUCT:
	हाल BTF_FWD_UNION: अणु
		काष्ठा btf_type *t;
		पूर्णांक id;

		id = btf_add_ref_kind(btf, BTF_KIND_FWD, name, 0);
		अगर (id <= 0)
			वापस id;
		t = btf_type_by_id(btf, id);
		t->info = btf_type_info(BTF_KIND_FWD, 0, fwd_kind == BTF_FWD_UNION);
		वापस id;
	पूर्ण
	हाल BTF_FWD_ENUM:
		/* क्रमागत क्रमward in BTF currently is just an क्रमागत with no क्रमागत
		 * values; we also assume a standard 4-byte size क्रम it
		 */
		वापस btf__add_क्रमागत(btf, name, माप(पूर्णांक));
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Append new BTF_KING_TYPEDEF type with:
 *   - *name*, non-empty/non-शून्य name;
 *   - *ref_type_id* - referenced type ID, it might not exist yet;
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_प्रकार(काष्ठा btf *btf, स्थिर अक्षर *name, पूर्णांक ref_type_id)
अणु
	अगर (!name || !name[0])
		वापस -EINVAL;

	वापस btf_add_ref_kind(btf, BTF_KIND_TYPEDEF, name, ref_type_id);
पूर्ण

/*
 * Append new BTF_KIND_VOLATILE type with:
 *   - *ref_type_id* - referenced type ID, it might not exist yet;
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_अस्थिर(काष्ठा btf *btf, पूर्णांक ref_type_id)
अणु
	वापस btf_add_ref_kind(btf, BTF_KIND_VOLATILE, शून्य, ref_type_id);
पूर्ण

/*
 * Append new BTF_KIND_CONST type with:
 *   - *ref_type_id* - referenced type ID, it might not exist yet;
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_स्थिर(काष्ठा btf *btf, पूर्णांक ref_type_id)
अणु
	वापस btf_add_ref_kind(btf, BTF_KIND_CONST, शून्य, ref_type_id);
पूर्ण

/*
 * Append new BTF_KIND_RESTRICT type with:
 *   - *ref_type_id* - referenced type ID, it might not exist yet;
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_restrict(काष्ठा btf *btf, पूर्णांक ref_type_id)
अणु
	वापस btf_add_ref_kind(btf, BTF_KIND_RESTRICT, शून्य, ref_type_id);
पूर्ण

/*
 * Append new BTF_KIND_FUNC type with:
 *   - *name*, non-empty/non-शून्य name;
 *   - *proto_type_id* - FUNC_PROTO's type ID, it might not exist yet;
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_func(काष्ठा btf *btf, स्थिर अक्षर *name,
		  क्रमागत btf_func_linkage linkage, पूर्णांक proto_type_id)
अणु
	पूर्णांक id;

	अगर (!name || !name[0])
		वापस -EINVAL;
	अगर (linkage != BTF_FUNC_STATIC && linkage != BTF_FUNC_GLOBAL &&
	    linkage != BTF_FUNC_EXTERN)
		वापस -EINVAL;

	id = btf_add_ref_kind(btf, BTF_KIND_FUNC, name, proto_type_id);
	अगर (id > 0) अणु
		काष्ठा btf_type *t = btf_type_by_id(btf, id);

		t->info = btf_type_info(BTF_KIND_FUNC, linkage, 0);
	पूर्ण
	वापस id;
पूर्ण

/*
 * Append new BTF_KIND_FUNC_PROTO with:
 *   - *ret_type_id* - type ID क्रम वापस result of a function.
 *
 * Function prototype initially has no arguments, but they can be added by
 * btf__add_func_param() one by one, immediately after
 * btf__add_func_proto() succeeded.
 *
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_func_proto(काष्ठा btf *btf, पूर्णांक ret_type_id)
अणु
	काष्ठा btf_type *t;
	पूर्णांक sz;

	अगर (validate_type_id(ret_type_id))
		वापस -EINVAL;

	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_type);
	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	/* start out with vlen=0; this will be adjusted when adding क्रमागत
	 * values, अगर necessary
	 */
	t->name_off = 0;
	t->info = btf_type_info(BTF_KIND_FUNC_PROTO, 0, 0);
	t->type = ret_type_id;

	वापस btf_commit_type(btf, sz);
पूर्ण

/*
 * Append new function parameter क्रम current FUNC_PROTO type with:
 *   - *name* - parameter name, can be शून्य or empty;
 *   - *type_id* - type ID describing the type of the parameter.
 * Returns:
 *   -  0, on success;
 *   - <0, on error.
 */
पूर्णांक btf__add_func_param(काष्ठा btf *btf, स्थिर अक्षर *name, पूर्णांक type_id)
अणु
	काष्ठा btf_type *t;
	काष्ठा btf_param *p;
	पूर्णांक sz, name_off = 0;

	अगर (validate_type_id(type_id))
		वापस -EINVAL;

	/* last type should be BTF_KIND_FUNC_PROTO */
	अगर (btf->nr_types == 0)
		वापस -EINVAL;
	t = btf_last_type(btf);
	अगर (!btf_is_func_proto(t))
		वापस -EINVAL;

	/* decompose and invalidate raw data */
	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_param);
	p = btf_add_type_mem(btf, sz);
	अगर (!p)
		वापस -ENOMEM;

	अगर (name && name[0]) अणु
		name_off = btf__add_str(btf, name);
		अगर (name_off < 0)
			वापस name_off;
	पूर्ण

	p->name_off = name_off;
	p->type = type_id;

	/* update parent type's vlen */
	t = btf_last_type(btf);
	btf_type_inc_vlen(t);

	btf->hdr->type_len += sz;
	btf->hdr->str_off += sz;
	वापस 0;
पूर्ण

/*
 * Append new BTF_KIND_VAR type with:
 *   - *name* - non-empty/non-शून्य name;
 *   - *linkage* - variable linkage, one of BTF_VAR_STATIC,
 *     BTF_VAR_GLOBAL_ALLOCATED, or BTF_VAR_GLOBAL_EXTERN;
 *   - *type_id* - type ID of the type describing the type of the variable.
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_var(काष्ठा btf *btf, स्थिर अक्षर *name, पूर्णांक linkage, पूर्णांक type_id)
अणु
	काष्ठा btf_type *t;
	काष्ठा btf_var *v;
	पूर्णांक sz, name_off;

	/* non-empty name */
	अगर (!name || !name[0])
		वापस -EINVAL;
	अगर (linkage != BTF_VAR_STATIC && linkage != BTF_VAR_GLOBAL_ALLOCATED &&
	    linkage != BTF_VAR_GLOBAL_EXTERN)
		वापस -EINVAL;
	अगर (validate_type_id(type_id))
		वापस -EINVAL;

	/* deस्थिरruct BTF, अगर necessary, and invalidate raw_data */
	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_type) + माप(काष्ठा btf_var);
	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	name_off = btf__add_str(btf, name);
	अगर (name_off < 0)
		वापस name_off;

	t->name_off = name_off;
	t->info = btf_type_info(BTF_KIND_VAR, 0, 0);
	t->type = type_id;

	v = btf_var(t);
	v->linkage = linkage;

	वापस btf_commit_type(btf, sz);
पूर्ण

/*
 * Append new BTF_KIND_DATASEC type with:
 *   - *name* - non-empty/non-शून्य name;
 *   - *byte_sz* - data section size, in bytes.
 *
 * Data section is initially empty. Variables info can be added with
 * btf__add_datasec_var_info() calls, after btf__add_datasec() succeeds.
 *
 * Returns:
 *   - >0, type ID of newly added BTF type;
 *   - <0, on error.
 */
पूर्णांक btf__add_datasec(काष्ठा btf *btf, स्थिर अक्षर *name, __u32 byte_sz)
अणु
	काष्ठा btf_type *t;
	पूर्णांक sz, name_off;

	/* non-empty name */
	अगर (!name || !name[0])
		वापस -EINVAL;

	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_type);
	t = btf_add_type_mem(btf, sz);
	अगर (!t)
		वापस -ENOMEM;

	name_off = btf__add_str(btf, name);
	अगर (name_off < 0)
		वापस name_off;

	/* start with vlen=0, which will be update as var_secinfos are added */
	t->name_off = name_off;
	t->info = btf_type_info(BTF_KIND_DATASEC, 0, 0);
	t->size = byte_sz;

	वापस btf_commit_type(btf, sz);
पूर्ण

/*
 * Append new data section variable inक्रमmation entry क्रम current DATASEC type:
 *   - *var_type_id* - type ID, describing type of the variable;
 *   - *offset* - variable offset within data section, in bytes;
 *   - *byte_sz* - variable size, in bytes.
 *
 * Returns:
 *   -  0, on success;
 *   - <0, on error.
 */
पूर्णांक btf__add_datasec_var_info(काष्ठा btf *btf, पूर्णांक var_type_id, __u32 offset, __u32 byte_sz)
अणु
	काष्ठा btf_type *t;
	काष्ठा btf_var_secinfo *v;
	पूर्णांक sz;

	/* last type should be BTF_KIND_DATASEC */
	अगर (btf->nr_types == 0)
		वापस -EINVAL;
	t = btf_last_type(btf);
	अगर (!btf_is_datasec(t))
		वापस -EINVAL;

	अगर (validate_type_id(var_type_id))
		वापस -EINVAL;

	/* decompose and invalidate raw data */
	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	sz = माप(काष्ठा btf_var_secinfo);
	v = btf_add_type_mem(btf, sz);
	अगर (!v)
		वापस -ENOMEM;

	v->type = var_type_id;
	v->offset = offset;
	v->size = byte_sz;

	/* update parent type's vlen */
	t = btf_last_type(btf);
	btf_type_inc_vlen(t);

	btf->hdr->type_len += sz;
	btf->hdr->str_off += sz;
	वापस 0;
पूर्ण

काष्ठा btf_ext_sec_setup_param अणु
	__u32 off;
	__u32 len;
	__u32 min_rec_size;
	काष्ठा btf_ext_info *ext_info;
	स्थिर अक्षर *desc;
पूर्ण;

अटल पूर्णांक btf_ext_setup_info(काष्ठा btf_ext *btf_ext,
			      काष्ठा btf_ext_sec_setup_param *ext_sec)
अणु
	स्थिर काष्ठा btf_ext_info_sec *sinfo;
	काष्ठा btf_ext_info *ext_info;
	__u32 info_left, record_size;
	/* The start of the info sec (including the __u32 record_size). */
	व्योम *info;

	अगर (ext_sec->len == 0)
		वापस 0;

	अगर (ext_sec->off & 0x03) अणु
		pr_debug(".BTF.ext %s section is not aligned to 4 bytes\n",
		     ext_sec->desc);
		वापस -EINVAL;
	पूर्ण

	info = btf_ext->data + btf_ext->hdr->hdr_len + ext_sec->off;
	info_left = ext_sec->len;

	अगर (btf_ext->data + btf_ext->data_size < info + ext_sec->len) अणु
		pr_debug("%s section (off:%u len:%u) is beyond the end of the ELF section .BTF.ext\n",
			 ext_sec->desc, ext_sec->off, ext_sec->len);
		वापस -EINVAL;
	पूर्ण

	/* At least a record size */
	अगर (info_left < माप(__u32)) अणु
		pr_debug(".BTF.ext %s record size not found\n", ext_sec->desc);
		वापस -EINVAL;
	पूर्ण

	/* The record size needs to meet the minimum standard */
	record_size = *(__u32 *)info;
	अगर (record_size < ext_sec->min_rec_size ||
	    record_size & 0x03) अणु
		pr_debug("%s section in .BTF.ext has invalid record size %u\n",
			 ext_sec->desc, record_size);
		वापस -EINVAL;
	पूर्ण

	sinfo = info + माप(__u32);
	info_left -= माप(__u32);

	/* If no records, वापस failure now so .BTF.ext won't be used. */
	अगर (!info_left) अणु
		pr_debug("%s section in .BTF.ext has no records", ext_sec->desc);
		वापस -EINVAL;
	पूर्ण

	जबतक (info_left) अणु
		अचिन्हित पूर्णांक sec_hdrlen = माप(काष्ठा btf_ext_info_sec);
		__u64 total_record_size;
		__u32 num_records;

		अगर (info_left < sec_hdrlen) अणु
			pr_debug("%s section header is not found in .BTF.ext\n",
			     ext_sec->desc);
			वापस -EINVAL;
		पूर्ण

		num_records = sinfo->num_info;
		अगर (num_records == 0) अणु
			pr_debug("%s section has incorrect num_records in .BTF.ext\n",
			     ext_sec->desc);
			वापस -EINVAL;
		पूर्ण

		total_record_size = sec_hdrlen +
				    (__u64)num_records * record_size;
		अगर (info_left < total_record_size) अणु
			pr_debug("%s section has incorrect num_records in .BTF.ext\n",
			     ext_sec->desc);
			वापस -EINVAL;
		पूर्ण

		info_left -= total_record_size;
		sinfo = (व्योम *)sinfo + total_record_size;
	पूर्ण

	ext_info = ext_sec->ext_info;
	ext_info->len = ext_sec->len - माप(__u32);
	ext_info->rec_size = record_size;
	ext_info->info = info + माप(__u32);

	वापस 0;
पूर्ण

अटल पूर्णांक btf_ext_setup_func_info(काष्ठा btf_ext *btf_ext)
अणु
	काष्ठा btf_ext_sec_setup_param param = अणु
		.off = btf_ext->hdr->func_info_off,
		.len = btf_ext->hdr->func_info_len,
		.min_rec_size = माप(काष्ठा bpf_func_info_min),
		.ext_info = &btf_ext->func_info,
		.desc = "func_info"
	पूर्ण;

	वापस btf_ext_setup_info(btf_ext, &param);
पूर्ण

अटल पूर्णांक btf_ext_setup_line_info(काष्ठा btf_ext *btf_ext)
अणु
	काष्ठा btf_ext_sec_setup_param param = अणु
		.off = btf_ext->hdr->line_info_off,
		.len = btf_ext->hdr->line_info_len,
		.min_rec_size = माप(काष्ठा bpf_line_info_min),
		.ext_info = &btf_ext->line_info,
		.desc = "line_info",
	पूर्ण;

	वापस btf_ext_setup_info(btf_ext, &param);
पूर्ण

अटल पूर्णांक btf_ext_setup_core_relos(काष्ठा btf_ext *btf_ext)
अणु
	काष्ठा btf_ext_sec_setup_param param = अणु
		.off = btf_ext->hdr->core_relo_off,
		.len = btf_ext->hdr->core_relo_len,
		.min_rec_size = माप(काष्ठा bpf_core_relo),
		.ext_info = &btf_ext->core_relo_info,
		.desc = "core_relo",
	पूर्ण;

	वापस btf_ext_setup_info(btf_ext, &param);
पूर्ण

अटल पूर्णांक btf_ext_parse_hdr(__u8 *data, __u32 data_size)
अणु
	स्थिर काष्ठा btf_ext_header *hdr = (काष्ठा btf_ext_header *)data;

	अगर (data_size < दुरत्वend(काष्ठा btf_ext_header, hdr_len) ||
	    data_size < hdr->hdr_len) अणु
		pr_debug("BTF.ext header not found");
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->magic == bswap_16(BTF_MAGIC)) अणु
		pr_warn("BTF.ext in non-native endianness is not supported\n");
		वापस -ENOTSUP;
	पूर्ण अन्यथा अगर (hdr->magic != BTF_MAGIC) अणु
		pr_debug("Invalid BTF.ext magic:%x\n", hdr->magic);
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->version != BTF_VERSION) अणु
		pr_debug("Unsupported BTF.ext version:%u\n", hdr->version);
		वापस -ENOTSUP;
	पूर्ण

	अगर (hdr->flags) अणु
		pr_debug("Unsupported BTF.ext flags:%x\n", hdr->flags);
		वापस -ENOTSUP;
	पूर्ण

	अगर (data_size == hdr->hdr_len) अणु
		pr_debug("BTF.ext has no data\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम btf_ext__मुक्त(काष्ठा btf_ext *btf_ext)
अणु
	अगर (IS_ERR_OR_शून्य(btf_ext))
		वापस;
	मुक्त(btf_ext->data);
	मुक्त(btf_ext);
पूर्ण

काष्ठा btf_ext *btf_ext__new(__u8 *data, __u32 size)
अणु
	काष्ठा btf_ext *btf_ext;
	पूर्णांक err;

	err = btf_ext_parse_hdr(data, size);
	अगर (err)
		वापस ERR_PTR(err);

	btf_ext = सुस्मृति(1, माप(काष्ठा btf_ext));
	अगर (!btf_ext)
		वापस ERR_PTR(-ENOMEM);

	btf_ext->data_size = size;
	btf_ext->data = दो_स्मृति(size);
	अगर (!btf_ext->data) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण
	स_नकल(btf_ext->data, data, size);

	अगर (btf_ext->hdr->hdr_len <
	    दुरत्वend(काष्ठा btf_ext_header, line_info_len))
		जाओ करोne;
	err = btf_ext_setup_func_info(btf_ext);
	अगर (err)
		जाओ करोne;

	err = btf_ext_setup_line_info(btf_ext);
	अगर (err)
		जाओ करोne;

	अगर (btf_ext->hdr->hdr_len < दुरत्वend(काष्ठा btf_ext_header, core_relo_len))
		जाओ करोne;
	err = btf_ext_setup_core_relos(btf_ext);
	अगर (err)
		जाओ करोne;

करोne:
	अगर (err) अणु
		btf_ext__मुक्त(btf_ext);
		वापस ERR_PTR(err);
	पूर्ण

	वापस btf_ext;
पूर्ण

स्थिर व्योम *btf_ext__get_raw_data(स्थिर काष्ठा btf_ext *btf_ext, __u32 *size)
अणु
	*size = btf_ext->data_size;
	वापस btf_ext->data;
पूर्ण

अटल पूर्णांक btf_ext_reloc_info(स्थिर काष्ठा btf *btf,
			      स्थिर काष्ठा btf_ext_info *ext_info,
			      स्थिर अक्षर *sec_name, __u32 insns_cnt,
			      व्योम **info, __u32 *cnt)
अणु
	__u32 sec_hdrlen = माप(काष्ठा btf_ext_info_sec);
	__u32 i, record_size, existing_len, records_len;
	काष्ठा btf_ext_info_sec *sinfo;
	स्थिर अक्षर *info_sec_name;
	__u64 reमुख्य_len;
	व्योम *data;

	record_size = ext_info->rec_size;
	sinfo = ext_info->info;
	reमुख्य_len = ext_info->len;
	जबतक (reमुख्य_len > 0) अणु
		records_len = sinfo->num_info * record_size;
		info_sec_name = btf__name_by_offset(btf, sinfo->sec_name_off);
		अगर (म_भेद(info_sec_name, sec_name)) अणु
			reमुख्य_len -= sec_hdrlen + records_len;
			sinfo = (व्योम *)sinfo + sec_hdrlen + records_len;
			जारी;
		पूर्ण

		existing_len = (*cnt) * record_size;
		data = पुनः_स्मृति(*info, existing_len + records_len);
		अगर (!data)
			वापस -ENOMEM;

		स_नकल(data + existing_len, sinfo->data, records_len);
		/* adjust insn_off only, the rest data will be passed
		 * to the kernel.
		 */
		क्रम (i = 0; i < sinfo->num_info; i++) अणु
			__u32 *insn_off;

			insn_off = data + existing_len + (i * record_size);
			*insn_off = *insn_off / माप(काष्ठा bpf_insn) +
				insns_cnt;
		पूर्ण
		*info = data;
		*cnt += sinfo->num_info;
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

पूर्णांक btf_ext__reloc_func_info(स्थिर काष्ठा btf *btf,
			     स्थिर काष्ठा btf_ext *btf_ext,
			     स्थिर अक्षर *sec_name, __u32 insns_cnt,
			     व्योम **func_info, __u32 *cnt)
अणु
	वापस btf_ext_reloc_info(btf, &btf_ext->func_info, sec_name,
				  insns_cnt, func_info, cnt);
पूर्ण

पूर्णांक btf_ext__reloc_line_info(स्थिर काष्ठा btf *btf,
			     स्थिर काष्ठा btf_ext *btf_ext,
			     स्थिर अक्षर *sec_name, __u32 insns_cnt,
			     व्योम **line_info, __u32 *cnt)
अणु
	वापस btf_ext_reloc_info(btf, &btf_ext->line_info, sec_name,
				  insns_cnt, line_info, cnt);
पूर्ण

__u32 btf_ext__func_info_rec_size(स्थिर काष्ठा btf_ext *btf_ext)
अणु
	वापस btf_ext->func_info.rec_size;
पूर्ण

__u32 btf_ext__line_info_rec_size(स्थिर काष्ठा btf_ext *btf_ext)
अणु
	वापस btf_ext->line_info.rec_size;
पूर्ण

काष्ठा btf_dedup;

अटल काष्ठा btf_dedup *btf_dedup_new(काष्ठा btf *btf, काष्ठा btf_ext *btf_ext,
				       स्थिर काष्ठा btf_dedup_opts *opts);
अटल व्योम btf_dedup_मुक्त(काष्ठा btf_dedup *d);
अटल पूर्णांक btf_dedup_prep(काष्ठा btf_dedup *d);
अटल पूर्णांक btf_dedup_strings(काष्ठा btf_dedup *d);
अटल पूर्णांक btf_dedup_prim_types(काष्ठा btf_dedup *d);
अटल पूर्णांक btf_dedup_काष्ठा_types(काष्ठा btf_dedup *d);
अटल पूर्णांक btf_dedup_ref_types(काष्ठा btf_dedup *d);
अटल पूर्णांक btf_dedup_compact_types(काष्ठा btf_dedup *d);
अटल पूर्णांक btf_dedup_remap_types(काष्ठा btf_dedup *d);

/*
 * Deduplicate BTF types and strings.
 *
 * BTF dedup algorithm takes as an input `काष्ठा btf` representing `.BTF` ELF
 * section with all BTF type descriptors and string data. It overग_लिखोs that
 * memory in-place with deduplicated types and strings without any loss of
 * inक्रमmation. If optional `काष्ठा btf_ext` representing '.BTF.ext' ELF section
 * is provided, all the strings referenced from .BTF.ext section are honored
 * and updated to poपूर्णांक to the right offsets after deduplication.
 *
 * If function वापसs with error, type/string data might be garbled and should
 * be discarded.
 *
 * More verbose and detailed description of both problem btf_dedup is solving,
 * as well as solution could be found at:
 * https://facebookmicrosites.github.io/bpf/blog/2018/11/14/btf-enhancement.hपंचांगl
 *
 * Problem description and justअगरication
 * =====================================
 *
 * BTF type inक्रमmation is typically emitted either as a result of conversion
 * from DWARF to BTF or directly by compiler. In both हालs, each compilation
 * unit contains inक्रमmation about a subset of all the types that are used
 * in an application. These subsets are frequently overlapping and contain a lot
 * of duplicated inक्रमmation when later concatenated together पूर्णांकo a single
 * binary. This algorithm ensures that each unique type is represented by single
 * BTF type descriptor, greatly reducing resulting size of BTF data.
 *
 * Compilation unit isolation and subsequent duplication of data is not the only
 * problem. The same type hierarchy (e.g., काष्ठा and all the type that काष्ठा
 * references) in dअगरferent compilation units can be represented in BTF to
 * various degrees of completeness (or, rather, incompleteness) due to
 * काष्ठा/जोड़ क्रमward declarations.
 *
 * Let's take a look at an example, that we'll use to better understand the
 * problem (and solution). Suppose we have two compilation units, each using
 * same `काष्ठा S`, but each of them having incomplete type inक्रमmation about
 * काष्ठा's fields:
 *
 * // CU #1:
 * काष्ठा S;
 * काष्ठा A अणु
 *	पूर्णांक a;
 *	काष्ठा A* self;
 *	काष्ठा S* parent;
 * पूर्ण;
 * काष्ठा B;
 * काष्ठा S अणु
 *	काष्ठा A* a_ptr;
 *	काष्ठा B* b_ptr;
 * पूर्ण;
 *
 * // CU #2:
 * काष्ठा S;
 * काष्ठा A;
 * काष्ठा B अणु
 *	पूर्णांक b;
 *	काष्ठा B* self;
 *	काष्ठा S* parent;
 * पूर्ण;
 * काष्ठा S अणु
 *	काष्ठा A* a_ptr;
 *	काष्ठा B* b_ptr;
 * पूर्ण;
 *
 * In हाल of CU #1, BTF data will know only that `काष्ठा B` exist (but no
 * more), but will know the complete type inक्रमmation about `काष्ठा A`. While
 * क्रम CU #2, it will know full type inक्रमmation about `काष्ठा B`, but will
 * only know about क्रमward declaration of `काष्ठा A` (in BTF terms, it will
 * have `BTF_KIND_FWD` type descriptor with name `B`).
 *
 * This compilation unit isolation means that it's possible that there is no
 * single CU with complete type inक्रमmation describing काष्ठाs `S`, `A`, and
 * `B`. Also, we might get tons of duplicated and redundant type inक्रमmation.
 *
 * Additional complication we need to keep in mind comes from the fact that
 * types, in general, can क्रमm graphs containing cycles, not just DAGs.
 *
 * While algorithm करोes deduplication, it also merges and resolves type
 * inक्रमmation (unless disabled throught `काष्ठा btf_opts`), whenever possible.
 * E.g., in the example above with two compilation units having partial type
 * inक्रमmation क्रम काष्ठाs `A` and `B`, the output of algorithm will emit
 * a single copy of each BTF type that describes काष्ठाs `A`, `B`, and `S`
 * (as well as type inक्रमmation क्रम `पूर्णांक` and poपूर्णांकers), as अगर they were defined
 * in a single compilation unit as:
 *
 * काष्ठा A अणु
 *	पूर्णांक a;
 *	काष्ठा A* self;
 *	काष्ठा S* parent;
 * पूर्ण;
 * काष्ठा B अणु
 *	पूर्णांक b;
 *	काष्ठा B* self;
 *	काष्ठा S* parent;
 * पूर्ण;
 * काष्ठा S अणु
 *	काष्ठा A* a_ptr;
 *	काष्ठा B* b_ptr;
 * पूर्ण;
 *
 * Algorithm summary
 * =================
 *
 * Algorithm completes its work in 6 separate passes:
 *
 * 1. Strings deduplication.
 * 2. Primitive types deduplication (पूर्णांक, क्रमागत, fwd).
 * 3. Struct/जोड़ types deduplication.
 * 4. Reference types deduplication (poपूर्णांकers, प्रकारs, arrays, funcs, func
 *    protos, and स्थिर/अस्थिर/restrict modअगरiers).
 * 5. Types compaction.
 * 6. Types remapping.
 *
 * Algorithm determines canonical type descriptor, which is a single
 * representative type क्रम each truly unique type. This canonical type is the
 * one that will go पूर्णांकo final deduplicated BTF type inक्रमmation. For
 * काष्ठा/जोड़s, it is also the type that algorithm will merge additional type
 * inक्रमmation पूर्णांकo (जबतक resolving FWDs), as it discovers it from data in
 * other CUs. Each input BTF type eventually माला_लो either mapped to itself, अगर
 * that type is canonical, or to some other type, अगर that type is equivalent
 * and was chosen as canonical representative. This mapping is stored in
 * `btf_dedup->map` array. This map is also used to record STRUCT/UNION that
 * FWD type got resolved to.
 *
 * To facilitate fast discovery of canonical types, we also मुख्यtain canonical
 * index (`btf_dedup->dedup_table`), which maps type descriptor's signature hash
 * (i.e., hashed kind, name, size, fields, etc) पूर्णांकo a list of canonical types
 * that match that signature. With sufficiently good choice of type signature
 * hashing function, we can limit number of canonical types क्रम each unique type
 * signature to a very small number, allowing to find canonical type क्रम any
 * duplicated type very quickly.
 *
 * Struct/जोड़ deduplication is the most critical part and algorithm क्रम
 * deduplicating काष्ठाs/जोड़s is described in greater details in comments क्रम
 * `btf_dedup_is_equiv` function.
 */
पूर्णांक btf__dedup(काष्ठा btf *btf, काष्ठा btf_ext *btf_ext,
	       स्थिर काष्ठा btf_dedup_opts *opts)
अणु
	काष्ठा btf_dedup *d = btf_dedup_new(btf, btf_ext, opts);
	पूर्णांक err;

	अगर (IS_ERR(d)) अणु
		pr_debug("btf_dedup_new failed: %ld", PTR_ERR(d));
		वापस -EINVAL;
	पूर्ण

	अगर (btf_ensure_modअगरiable(btf))
		वापस -ENOMEM;

	err = btf_dedup_prep(d);
	अगर (err) अणु
		pr_debug("btf_dedup_prep failed:%d\n", err);
		जाओ करोne;
	पूर्ण
	err = btf_dedup_strings(d);
	अगर (err < 0) अणु
		pr_debug("btf_dedup_strings failed:%d\n", err);
		जाओ करोne;
	पूर्ण
	err = btf_dedup_prim_types(d);
	अगर (err < 0) अणु
		pr_debug("btf_dedup_prim_types failed:%d\n", err);
		जाओ करोne;
	पूर्ण
	err = btf_dedup_काष्ठा_types(d);
	अगर (err < 0) अणु
		pr_debug("btf_dedup_struct_types failed:%d\n", err);
		जाओ करोne;
	पूर्ण
	err = btf_dedup_ref_types(d);
	अगर (err < 0) अणु
		pr_debug("btf_dedup_ref_types failed:%d\n", err);
		जाओ करोne;
	पूर्ण
	err = btf_dedup_compact_types(d);
	अगर (err < 0) अणु
		pr_debug("btf_dedup_compact_types failed:%d\n", err);
		जाओ करोne;
	पूर्ण
	err = btf_dedup_remap_types(d);
	अगर (err < 0) अणु
		pr_debug("btf_dedup_remap_types failed:%d\n", err);
		जाओ करोne;
	पूर्ण

करोne:
	btf_dedup_मुक्त(d);
	वापस err;
पूर्ण

#घोषणा BTF_UNPROCESSED_ID ((__u32)-1)
#घोषणा BTF_IN_PROGRESS_ID ((__u32)-2)

काष्ठा btf_dedup अणु
	/* .BTF section to be deduped in-place */
	काष्ठा btf *btf;
	/*
	 * Optional .BTF.ext section. When provided, any strings referenced
	 * from it will be taken पूर्णांकo account when deduping strings
	 */
	काष्ठा btf_ext *btf_ext;
	/*
	 * This is a map from any type's signature hash to a list of possible
	 * canonical representative type candidates. Hash collisions are
	 * ignored, so even types of various kinds can share same list of
	 * candidates, which is fine because we rely on subsequent
	 * btf_xxx_equal() checks to authoritatively verअगरy type equality.
	 */
	काष्ठा hashmap *dedup_table;
	/* Canonical types map */
	__u32 *map;
	/* Hypothetical mapping, used during type graph equivalence checks */
	__u32 *hypot_map;
	__u32 *hypot_list;
	माप_प्रकार hypot_cnt;
	माप_प्रकार hypot_cap;
	/* Whether hypothetical mapping, अगर successful, would need to adjust
	 * alपढ़ोy canonicalized types (due to a new क्रमward declaration to
	 * concrete type resolution). In such हाल, during split BTF dedup
	 * candidate type would still be considered as dअगरferent, because base
	 * BTF is considered to be immutable.
	 */
	bool hypot_adjust_canon;
	/* Various option modअगरying behavior of algorithm */
	काष्ठा btf_dedup_opts opts;
	/* temporary strings deduplication state */
	काष्ठा strset *strs_set;
पूर्ण;

अटल दीर्घ hash_combine(दीर्घ h, दीर्घ value)
अणु
	वापस h * 31 + value;
पूर्ण

#घोषणा क्रम_each_dedup_cand(d, node, hash) \
	hashmap__क्रम_each_key_entry(d->dedup_table, node, (व्योम *)hash)

अटल पूर्णांक btf_dedup_table_add(काष्ठा btf_dedup *d, दीर्घ hash, __u32 type_id)
अणु
	वापस hashmap__append(d->dedup_table,
			       (व्योम *)hash, (व्योम *)(दीर्घ)type_id);
पूर्ण

अटल पूर्णांक btf_dedup_hypot_map_add(काष्ठा btf_dedup *d,
				   __u32 from_id, __u32 to_id)
अणु
	अगर (d->hypot_cnt == d->hypot_cap) अणु
		__u32 *new_list;

		d->hypot_cap += max((माप_प्रकार)16, d->hypot_cap / 2);
		new_list = libbpf_पुनः_स्मृतिarray(d->hypot_list, d->hypot_cap, माप(__u32));
		अगर (!new_list)
			वापस -ENOMEM;
		d->hypot_list = new_list;
	पूर्ण
	d->hypot_list[d->hypot_cnt++] = from_id;
	d->hypot_map[from_id] = to_id;
	वापस 0;
पूर्ण

अटल व्योम btf_dedup_clear_hypot_map(काष्ठा btf_dedup *d)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < d->hypot_cnt; i++)
		d->hypot_map[d->hypot_list[i]] = BTF_UNPROCESSED_ID;
	d->hypot_cnt = 0;
	d->hypot_adjust_canon = false;
पूर्ण

अटल व्योम btf_dedup_मुक्त(काष्ठा btf_dedup *d)
अणु
	hashmap__मुक्त(d->dedup_table);
	d->dedup_table = शून्य;

	मुक्त(d->map);
	d->map = शून्य;

	मुक्त(d->hypot_map);
	d->hypot_map = शून्य;

	मुक्त(d->hypot_list);
	d->hypot_list = शून्य;

	मुक्त(d);
पूर्ण

अटल माप_प्रकार btf_dedup_identity_hash_fn(स्थिर व्योम *key, व्योम *ctx)
अणु
	वापस (माप_प्रकार)key;
पूर्ण

अटल माप_प्रकार btf_dedup_collision_hash_fn(स्थिर व्योम *key, व्योम *ctx)
अणु
	वापस 0;
पूर्ण

अटल bool btf_dedup_equal_fn(स्थिर व्योम *k1, स्थिर व्योम *k2, व्योम *ctx)
अणु
	वापस k1 == k2;
पूर्ण

अटल काष्ठा btf_dedup *btf_dedup_new(काष्ठा btf *btf, काष्ठा btf_ext *btf_ext,
				       स्थिर काष्ठा btf_dedup_opts *opts)
अणु
	काष्ठा btf_dedup *d = सुस्मृति(1, माप(काष्ठा btf_dedup));
	hashmap_hash_fn hash_fn = btf_dedup_identity_hash_fn;
	पूर्णांक i, err = 0, type_cnt;

	अगर (!d)
		वापस ERR_PTR(-ENOMEM);

	d->opts.करोnt_resolve_fwds = opts && opts->करोnt_resolve_fwds;
	/* dedup_table_size is now used only to क्रमce collisions in tests */
	अगर (opts && opts->dedup_table_size == 1)
		hash_fn = btf_dedup_collision_hash_fn;

	d->btf = btf;
	d->btf_ext = btf_ext;

	d->dedup_table = hashmap__new(hash_fn, btf_dedup_equal_fn, शून्य);
	अगर (IS_ERR(d->dedup_table)) अणु
		err = PTR_ERR(d->dedup_table);
		d->dedup_table = शून्य;
		जाओ करोne;
	पूर्ण

	type_cnt = btf__get_nr_types(btf) + 1;
	d->map = दो_स्मृति(माप(__u32) * type_cnt);
	अगर (!d->map) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण
	/* special BTF "void" type is made canonical immediately */
	d->map[0] = 0;
	क्रम (i = 1; i < type_cnt; i++) अणु
		काष्ठा btf_type *t = btf_type_by_id(d->btf, i);

		/* VAR and DATASEC are never deduped and are self-canonical */
		अगर (btf_is_var(t) || btf_is_datasec(t))
			d->map[i] = i;
		अन्यथा
			d->map[i] = BTF_UNPROCESSED_ID;
	पूर्ण

	d->hypot_map = दो_स्मृति(माप(__u32) * type_cnt);
	अगर (!d->hypot_map) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण
	क्रम (i = 0; i < type_cnt; i++)
		d->hypot_map[i] = BTF_UNPROCESSED_ID;

करोne:
	अगर (err) अणु
		btf_dedup_मुक्त(d);
		वापस ERR_PTR(err);
	पूर्ण

	वापस d;
पूर्ण

/*
 * Iterate over all possible places in .BTF and .BTF.ext that can reference
 * string and pass poपूर्णांकer to it to a provided callback `fn`.
 */
अटल पूर्णांक btf_क्रम_each_str_off(काष्ठा btf_dedup *d, str_off_visit_fn fn, व्योम *ctx)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < d->btf->nr_types; i++) अणु
		काष्ठा btf_type *t = btf_type_by_id(d->btf, d->btf->start_id + i);

		r = btf_type_visit_str_offs(t, fn, ctx);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (!d->btf_ext)
		वापस 0;

	r = btf_ext_visit_str_offs(d->btf_ext, fn, ctx);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक strs_dedup_remap_str_off(__u32 *str_off_ptr, व्योम *ctx)
अणु
	काष्ठा btf_dedup *d = ctx;
	__u32 str_off = *str_off_ptr;
	स्थिर अक्षर *s;
	पूर्णांक off, err;

	/* करोn't touch empty string or string in मुख्य BTF */
	अगर (str_off == 0 || str_off < d->btf->start_str_off)
		वापस 0;

	s = btf__str_by_offset(d->btf, str_off);
	अगर (d->btf->base_btf) अणु
		err = btf__find_str(d->btf->base_btf, s);
		अगर (err >= 0) अणु
			*str_off_ptr = err;
			वापस 0;
		पूर्ण
		अगर (err != -ENOENT)
			वापस err;
	पूर्ण

	off = strset__add_str(d->strs_set, s);
	अगर (off < 0)
		वापस off;

	*str_off_ptr = d->btf->start_str_off + off;
	वापस 0;
पूर्ण

/*
 * Dedup string and filter out those that are not referenced from either .BTF
 * or .BTF.ext (अगर provided) sections.
 *
 * This is करोne by building index of all strings in BTF's string section,
 * then iterating over all entities that can reference strings (e.g., type
 * names, काष्ठा field names, .BTF.ext line info, etc) and marking corresponding
 * strings as used. After that all used strings are deduped and compacted पूर्णांकo
 * sequential blob of memory and new offsets are calculated. Then all the string
 * references are iterated again and rewritten using new offsets.
 */
अटल पूर्णांक btf_dedup_strings(काष्ठा btf_dedup *d)
अणु
	पूर्णांक err;

	अगर (d->btf->strs_deduped)
		वापस 0;

	d->strs_set = strset__new(BTF_MAX_STR_OFFSET, शून्य, 0);
	अगर (IS_ERR(d->strs_set)) अणु
		err = PTR_ERR(d->strs_set);
		जाओ err_out;
	पूर्ण

	अगर (!d->btf->base_btf) अणु
		/* insert empty string; we won't be looking it up during strings
		 * dedup, but it's good to have it क्रम generic BTF string lookups
		 */
		err = strset__add_str(d->strs_set, "");
		अगर (err < 0)
			जाओ err_out;
	पूर्ण

	/* remap string offsets */
	err = btf_क्रम_each_str_off(d, strs_dedup_remap_str_off, d);
	अगर (err)
		जाओ err_out;

	/* replace BTF string data and hash with deduped ones */
	strset__मुक्त(d->btf->strs_set);
	d->btf->hdr->str_len = strset__data_size(d->strs_set);
	d->btf->strs_set = d->strs_set;
	d->strs_set = शून्य;
	d->btf->strs_deduped = true;
	वापस 0;

err_out:
	strset__मुक्त(d->strs_set);
	d->strs_set = शून्य;

	वापस err;
पूर्ण

अटल दीर्घ btf_hash_common(काष्ठा btf_type *t)
अणु
	दीर्घ h;

	h = hash_combine(0, t->name_off);
	h = hash_combine(h, t->info);
	h = hash_combine(h, t->size);
	वापस h;
पूर्ण

अटल bool btf_equal_common(काष्ठा btf_type *t1, काष्ठा btf_type *t2)
अणु
	वापस t1->name_off == t2->name_off &&
	       t1->info == t2->info &&
	       t1->size == t2->size;
पूर्ण

/* Calculate type signature hash of INT. */
अटल दीर्घ btf_hash_पूर्णांक(काष्ठा btf_type *t)
अणु
	__u32 info = *(__u32 *)(t + 1);
	दीर्घ h;

	h = btf_hash_common(t);
	h = hash_combine(h, info);
	वापस h;
पूर्ण

/* Check काष्ठाural equality of two INTs. */
अटल bool btf_equal_पूर्णांक(काष्ठा btf_type *t1, काष्ठा btf_type *t2)
अणु
	__u32 info1, info2;

	अगर (!btf_equal_common(t1, t2))
		वापस false;
	info1 = *(__u32 *)(t1 + 1);
	info2 = *(__u32 *)(t2 + 1);
	वापस info1 == info2;
पूर्ण

/* Calculate type signature hash of ENUM. */
अटल दीर्घ btf_hash_क्रमागत(काष्ठा btf_type *t)
अणु
	दीर्घ h;

	/* करोn't hash vlen and क्रमागत members to support क्रमागत fwd resolving */
	h = hash_combine(0, t->name_off);
	h = hash_combine(h, t->info & ~0xffff);
	h = hash_combine(h, t->size);
	वापस h;
पूर्ण

/* Check काष्ठाural equality of two ENUMs. */
अटल bool btf_equal_क्रमागत(काष्ठा btf_type *t1, काष्ठा btf_type *t2)
अणु
	स्थिर काष्ठा btf_क्रमागत *m1, *m2;
	__u16 vlen;
	पूर्णांक i;

	अगर (!btf_equal_common(t1, t2))
		वापस false;

	vlen = btf_vlen(t1);
	m1 = btf_क्रमागत(t1);
	m2 = btf_क्रमागत(t2);
	क्रम (i = 0; i < vlen; i++) अणु
		अगर (m1->name_off != m2->name_off || m1->val != m2->val)
			वापस false;
		m1++;
		m2++;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत bool btf_is_क्रमागत_fwd(काष्ठा btf_type *t)
अणु
	वापस btf_is_क्रमागत(t) && btf_vlen(t) == 0;
पूर्ण

अटल bool btf_compat_क्रमागत(काष्ठा btf_type *t1, काष्ठा btf_type *t2)
अणु
	अगर (!btf_is_क्रमागत_fwd(t1) && !btf_is_क्रमागत_fwd(t2))
		वापस btf_equal_क्रमागत(t1, t2);
	/* ignore vlen when comparing */
	वापस t1->name_off == t2->name_off &&
	       (t1->info & ~0xffff) == (t2->info & ~0xffff) &&
	       t1->size == t2->size;
पूर्ण

/*
 * Calculate type signature hash of STRUCT/UNION, ignoring referenced type IDs,
 * as referenced type IDs equivalence is established separately during type
 * graph equivalence check algorithm.
 */
अटल दीर्घ btf_hash_काष्ठा(काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_member *member = btf_members(t);
	__u32 vlen = btf_vlen(t);
	दीर्घ h = btf_hash_common(t);
	पूर्णांक i;

	क्रम (i = 0; i < vlen; i++) अणु
		h = hash_combine(h, member->name_off);
		h = hash_combine(h, member->offset);
		/* no hashing of referenced type ID, it can be unresolved yet */
		member++;
	पूर्ण
	वापस h;
पूर्ण

/*
 * Check काष्ठाural compatibility of two FUNC_PROTOs, ignoring referenced type
 * IDs. This check is perक्रमmed during type graph equivalence check and
 * referenced types equivalence is checked separately.
 */
अटल bool btf_shallow_equal_काष्ठा(काष्ठा btf_type *t1, काष्ठा btf_type *t2)
अणु
	स्थिर काष्ठा btf_member *m1, *m2;
	__u16 vlen;
	पूर्णांक i;

	अगर (!btf_equal_common(t1, t2))
		वापस false;

	vlen = btf_vlen(t1);
	m1 = btf_members(t1);
	m2 = btf_members(t2);
	क्रम (i = 0; i < vlen; i++) अणु
		अगर (m1->name_off != m2->name_off || m1->offset != m2->offset)
			वापस false;
		m1++;
		m2++;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Calculate type signature hash of ARRAY, including referenced type IDs,
 * under assumption that they were alपढ़ोy resolved to canonical type IDs and
 * are not going to change.
 */
अटल दीर्घ btf_hash_array(काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_array *info = btf_array(t);
	दीर्घ h = btf_hash_common(t);

	h = hash_combine(h, info->type);
	h = hash_combine(h, info->index_type);
	h = hash_combine(h, info->nelems);
	वापस h;
पूर्ण

/*
 * Check exact equality of two ARRAYs, taking पूर्णांकo account referenced
 * type IDs, under assumption that they were alपढ़ोy resolved to canonical
 * type IDs and are not going to change.
 * This function is called during reference types deduplication to compare
 * ARRAY to potential canonical representative.
 */
अटल bool btf_equal_array(काष्ठा btf_type *t1, काष्ठा btf_type *t2)
अणु
	स्थिर काष्ठा btf_array *info1, *info2;

	अगर (!btf_equal_common(t1, t2))
		वापस false;

	info1 = btf_array(t1);
	info2 = btf_array(t2);
	वापस info1->type == info2->type &&
	       info1->index_type == info2->index_type &&
	       info1->nelems == info2->nelems;
पूर्ण

/*
 * Check काष्ठाural compatibility of two ARRAYs, ignoring referenced type
 * IDs. This check is perक्रमmed during type graph equivalence check and
 * referenced types equivalence is checked separately.
 */
अटल bool btf_compat_array(काष्ठा btf_type *t1, काष्ठा btf_type *t2)
अणु
	अगर (!btf_equal_common(t1, t2))
		वापस false;

	वापस btf_array(t1)->nelems == btf_array(t2)->nelems;
पूर्ण

/*
 * Calculate type signature hash of FUNC_PROTO, including referenced type IDs,
 * under assumption that they were alपढ़ोy resolved to canonical type IDs and
 * are not going to change.
 */
अटल दीर्घ btf_hash_fnproto(काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_param *member = btf_params(t);
	__u16 vlen = btf_vlen(t);
	दीर्घ h = btf_hash_common(t);
	पूर्णांक i;

	क्रम (i = 0; i < vlen; i++) अणु
		h = hash_combine(h, member->name_off);
		h = hash_combine(h, member->type);
		member++;
	पूर्ण
	वापस h;
पूर्ण

/*
 * Check exact equality of two FUNC_PROTOs, taking पूर्णांकo account referenced
 * type IDs, under assumption that they were alपढ़ोy resolved to canonical
 * type IDs and are not going to change.
 * This function is called during reference types deduplication to compare
 * FUNC_PROTO to potential canonical representative.
 */
अटल bool btf_equal_fnproto(काष्ठा btf_type *t1, काष्ठा btf_type *t2)
अणु
	स्थिर काष्ठा btf_param *m1, *m2;
	__u16 vlen;
	पूर्णांक i;

	अगर (!btf_equal_common(t1, t2))
		वापस false;

	vlen = btf_vlen(t1);
	m1 = btf_params(t1);
	m2 = btf_params(t2);
	क्रम (i = 0; i < vlen; i++) अणु
		अगर (m1->name_off != m2->name_off || m1->type != m2->type)
			वापस false;
		m1++;
		m2++;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Check काष्ठाural compatibility of two FUNC_PROTOs, ignoring referenced type
 * IDs. This check is perक्रमmed during type graph equivalence check and
 * referenced types equivalence is checked separately.
 */
अटल bool btf_compat_fnproto(काष्ठा btf_type *t1, काष्ठा btf_type *t2)
अणु
	स्थिर काष्ठा btf_param *m1, *m2;
	__u16 vlen;
	पूर्णांक i;

	/* skip वापस type ID */
	अगर (t1->name_off != t2->name_off || t1->info != t2->info)
		वापस false;

	vlen = btf_vlen(t1);
	m1 = btf_params(t1);
	m2 = btf_params(t2);
	क्रम (i = 0; i < vlen; i++) अणु
		अगर (m1->name_off != m2->name_off)
			वापस false;
		m1++;
		m2++;
	पूर्ण
	वापस true;
पूर्ण

/* Prepare split BTF क्रम deduplication by calculating hashes of base BTF's
 * types and initializing the rest of the state (canonical type mapping) क्रम
 * the fixed base BTF part.
 */
अटल पूर्णांक btf_dedup_prep(काष्ठा btf_dedup *d)
अणु
	काष्ठा btf_type *t;
	पूर्णांक type_id;
	दीर्घ h;

	अगर (!d->btf->base_btf)
		वापस 0;

	क्रम (type_id = 1; type_id < d->btf->start_id; type_id++) अणु
		t = btf_type_by_id(d->btf, type_id);

		/* all base BTF types are self-canonical by definition */
		d->map[type_id] = type_id;

		चयन (btf_kind(t)) अणु
		हाल BTF_KIND_VAR:
		हाल BTF_KIND_DATASEC:
			/* VAR and DATASEC are never hash/deduplicated */
			जारी;
		हाल BTF_KIND_CONST:
		हाल BTF_KIND_VOLATILE:
		हाल BTF_KIND_RESTRICT:
		हाल BTF_KIND_PTR:
		हाल BTF_KIND_FWD:
		हाल BTF_KIND_TYPEDEF:
		हाल BTF_KIND_FUNC:
		हाल BTF_KIND_FLOAT:
			h = btf_hash_common(t);
			अवरोध;
		हाल BTF_KIND_INT:
			h = btf_hash_पूर्णांक(t);
			अवरोध;
		हाल BTF_KIND_ENUM:
			h = btf_hash_क्रमागत(t);
			अवरोध;
		हाल BTF_KIND_STRUCT:
		हाल BTF_KIND_UNION:
			h = btf_hash_काष्ठा(t);
			अवरोध;
		हाल BTF_KIND_ARRAY:
			h = btf_hash_array(t);
			अवरोध;
		हाल BTF_KIND_FUNC_PROTO:
			h = btf_hash_fnproto(t);
			अवरोध;
		शेष:
			pr_debug("unknown kind %d for type [%d]\n", btf_kind(t), type_id);
			वापस -EINVAL;
		पूर्ण
		अगर (btf_dedup_table_add(d, h, type_id))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Deduplicate primitive types, that can't reference other types, by calculating
 * their type signature hash and comparing them with any possible canonical
 * candidate. If no canonical candidate matches, type itself is marked as
 * canonical and is added पूर्णांकo `btf_dedup->dedup_table` as another candidate.
 */
अटल पूर्णांक btf_dedup_prim_type(काष्ठा btf_dedup *d, __u32 type_id)
अणु
	काष्ठा btf_type *t = btf_type_by_id(d->btf, type_id);
	काष्ठा hashmap_entry *hash_entry;
	काष्ठा btf_type *cand;
	/* अगर we करोn't find equivalent type, then we are canonical */
	__u32 new_id = type_id;
	__u32 cand_id;
	दीर्घ h;

	चयन (btf_kind(t)) अणु
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_RESTRICT:
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_ARRAY:
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
	हाल BTF_KIND_FUNC:
	हाल BTF_KIND_FUNC_PROTO:
	हाल BTF_KIND_VAR:
	हाल BTF_KIND_DATASEC:
		वापस 0;

	हाल BTF_KIND_INT:
		h = btf_hash_पूर्णांक(t);
		क्रम_each_dedup_cand(d, hash_entry, h) अणु
			cand_id = (__u32)(दीर्घ)hash_entry->value;
			cand = btf_type_by_id(d->btf, cand_id);
			अगर (btf_equal_पूर्णांक(t, cand)) अणु
				new_id = cand_id;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BTF_KIND_ENUM:
		h = btf_hash_क्रमागत(t);
		क्रम_each_dedup_cand(d, hash_entry, h) अणु
			cand_id = (__u32)(दीर्घ)hash_entry->value;
			cand = btf_type_by_id(d->btf, cand_id);
			अगर (btf_equal_क्रमागत(t, cand)) अणु
				new_id = cand_id;
				अवरोध;
			पूर्ण
			अगर (d->opts.करोnt_resolve_fwds)
				जारी;
			अगर (btf_compat_क्रमागत(t, cand)) अणु
				अगर (btf_is_क्रमागत_fwd(t)) अणु
					/* resolve fwd to full क्रमागत */
					new_id = cand_id;
					अवरोध;
				पूर्ण
				/* resolve canonical क्रमागत fwd to full क्रमागत */
				d->map[cand_id] = type_id;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BTF_KIND_FWD:
	हाल BTF_KIND_FLOAT:
		h = btf_hash_common(t);
		क्रम_each_dedup_cand(d, hash_entry, h) अणु
			cand_id = (__u32)(दीर्घ)hash_entry->value;
			cand = btf_type_by_id(d->btf, cand_id);
			अगर (btf_equal_common(t, cand)) अणु
				new_id = cand_id;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	d->map[type_id] = new_id;
	अगर (type_id == new_id && btf_dedup_table_add(d, h, type_id))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक btf_dedup_prim_types(काष्ठा btf_dedup *d)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < d->btf->nr_types; i++) अणु
		err = btf_dedup_prim_type(d, d->btf->start_id + i);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Check whether type is alपढ़ोy mapped पूर्णांकo canonical one (could be to itself).
 */
अटल अंतरभूत bool is_type_mapped(काष्ठा btf_dedup *d, uपूर्णांक32_t type_id)
अणु
	वापस d->map[type_id] <= BTF_MAX_NR_TYPES;
पूर्ण

/*
 * Resolve type ID पूर्णांकo its canonical type ID, अगर any; otherwise वापस original
 * type ID. If type is FWD and is resolved पूर्णांकo STRUCT/UNION alपढ़ोy, follow
 * STRUCT/UNION link and resolve it पूर्णांकo canonical type ID as well.
 */
अटल अंतरभूत __u32 resolve_type_id(काष्ठा btf_dedup *d, __u32 type_id)
अणु
	जबतक (is_type_mapped(d, type_id) && d->map[type_id] != type_id)
		type_id = d->map[type_id];
	वापस type_id;
पूर्ण

/*
 * Resolve FWD to underlying STRUCT/UNION, अगर any; otherwise वापस original
 * type ID.
 */
अटल uपूर्णांक32_t resolve_fwd_id(काष्ठा btf_dedup *d, uपूर्णांक32_t type_id)
अणु
	__u32 orig_type_id = type_id;

	अगर (!btf_is_fwd(btf__type_by_id(d->btf, type_id)))
		वापस type_id;

	जबतक (is_type_mapped(d, type_id) && d->map[type_id] != type_id)
		type_id = d->map[type_id];

	अगर (!btf_is_fwd(btf__type_by_id(d->btf, type_id)))
		वापस type_id;

	वापस orig_type_id;
पूर्ण


अटल अंतरभूत __u16 btf_fwd_kind(काष्ठा btf_type *t)
अणु
	वापस btf_kflag(t) ? BTF_KIND_UNION : BTF_KIND_STRUCT;
पूर्ण

/* Check अगर given two types are identical ARRAY definitions */
अटल पूर्णांक btf_dedup_identical_arrays(काष्ठा btf_dedup *d, __u32 id1, __u32 id2)
अणु
	काष्ठा btf_type *t1, *t2;

	t1 = btf_type_by_id(d->btf, id1);
	t2 = btf_type_by_id(d->btf, id2);
	अगर (!btf_is_array(t1) || !btf_is_array(t2))
		वापस 0;

	वापस btf_equal_array(t1, t2);
पूर्ण

/*
 * Check equivalence of BTF type graph क्रमmed by candidate काष्ठा/जोड़ (we'll
 * call it "candidate graph" in this description क्रम brevity) to a type graph
 * क्रमmed by (potential) canonical काष्ठा/जोड़ ("canonical graph" क्रम brevity
 * here, though keep in mind that not all types in canonical graph are
 * necessarily canonical representatives themselves, some of them might be
 * duplicates or its uniqueness might not have been established yet).
 * Returns:
 *  - >0, अगर type graphs are equivalent;
 *  -  0, अगर not equivalent;
 *  - <0, on error.
 *
 * Algorithm perक्रमms side-by-side DFS traversal of both type graphs and checks
 * equivalence of BTF types at each step. If at any poपूर्णांक BTF types in candidate
 * and canonical graphs are not compatible काष्ठाurally, whole graphs are
 * incompatible. If types are काष्ठाurally equivalent (i.e., all inक्रमmation
 * except referenced type IDs is exactly the same), a mapping from `canon_id` to
 * a `cand_id` is recored in hypothetical mapping (`btf_dedup->hypot_map`).
 * If a type references other types, then those referenced types are checked
 * क्रम equivalence recursively.
 *
 * During DFS traversal, अगर we find that क्रम current `canon_id` type we
 * alपढ़ोy have some mapping in hypothetical map, we check क्रम two possible
 * situations:
 *   - `canon_id` is mapped to exactly the same type as `cand_id`. This will
 *     happen when type graphs have cycles. In this हाल we assume those two
 *     types are equivalent.
 *   - `canon_id` is mapped to dअगरferent type. This is contradiction in our
 *     hypothetical mapping, because same graph in canonical graph corresponds
 *     to two dअगरferent types in candidate graph, which क्रम equivalent type
 *     graphs shouldn't happen. This condition terminates equivalence check
 *     with negative result.
 *
 * If type graphs traversal exhausts types to check and find no contradiction,
 * then type graphs are equivalent.
 *
 * When checking types क्रम equivalence, there is one special हाल: FWD types.
 * If FWD type resolution is allowed and one of the types (either from canonical
 * or candidate graph) is FWD and other is STRUCT/UNION (depending on FWD's kind
 * flag) and their names match, hypothetical mapping is updated to poपूर्णांक from
 * FWD to STRUCT/UNION. If graphs will be determined as equivalent successfully,
 * this mapping will be used to record FWD -> STRUCT/UNION mapping permanently.
 *
 * Technically, this could lead to incorrect FWD to STRUCT/UNION resolution,
 * अगर there are two exactly named (or anonymous) काष्ठाs/जोड़s that are
 * compatible काष्ठाurally, one of which has FWD field, जबतक other is concrete
 * STRUCT/UNION, but according to C sources they are dअगरferent काष्ठाs/जोड़s
 * that are referencing dअगरferent types with the same name. This is extremely
 * unlikely to happen, but btf_dedup API allows to disable FWD resolution अगर
 * this logic is causing problems.
 *
 * Doing FWD resolution means that both candidate and/or canonical graphs can
 * consists of portions of the graph that come from multiple compilation units.
 * This is due to the fact that types within single compilation unit are always
 * deduplicated and FWDs are alपढ़ोy resolved, अगर referenced काष्ठा/जोड़
 * definiton is available. So, अगर we had unresolved FWD and found corresponding
 * STRUCT/UNION, they will be from dअगरferent compilation units. This
 * consequently means that when we "link" FWD to corresponding STRUCT/UNION,
 * type graph will likely have at least two dअगरferent BTF types that describe
 * same type (e.g., most probably there will be two dअगरferent BTF types क्रम the
 * same 'int' primitive type) and could even have "overlapping" parts of type
 * graph that describe same subset of types.
 *
 * This in turn means that our assumption that each type in canonical graph
 * must correspond to exactly one type in candidate graph might not hold
 * anymore and will make it harder to detect contradictions using hypothetical
 * map. To handle this problem, we allow to follow FWD -> STRUCT/UNION
 * resolution only in canonical graph. FWDs in candidate graphs are never
 * resolved. To see why it's OK, let's check all possible situations w.r.t. FWDs
 * that can occur:
 *   - Both types in canonical and candidate graphs are FWDs. If they are
 *     काष्ठाurally equivalent, then they can either be both resolved to the
 *     same STRUCT/UNION or not resolved at all. In both हालs they are
 *     equivalent and there is no need to resolve FWD on candidate side.
 *   - Both types in canonical and candidate graphs are concrete STRUCT/UNION,
 *     so nothing to resolve as well, algorithm will check equivalence anyway.
 *   - Type in canonical graph is FWD, जबतक type in candidate is concrete
 *     STRUCT/UNION. In this हाल candidate graph comes from single compilation
 *     unit, so there is exactly one BTF type क्रम each unique C type. After
 *     resolving FWD पूर्णांकo STRUCT/UNION, there might be more than one BTF type
 *     in canonical graph mapping to single BTF type in candidate graph, but
 *     because hypothetical mapping maps from canonical to candidate types, it's
 *     alright, and we still मुख्यtain the property of having single `canon_id`
 *     mapping to single `cand_id` (there could be two dअगरferent `canon_id`
 *     mapped to the same `cand_id`, but it's not contradictory).
 *   - Type in canonical graph is concrete STRUCT/UNION, जबतक type in candidate
 *     graph is FWD. In this हाल we are just going to check compatibility of
 *     STRUCT/UNION and corresponding FWD, and अगर they are compatible, we'll
 *     assume that whatever STRUCT/UNION FWD resolves to must be equivalent to
 *     a concrete STRUCT/UNION from canonical graph. If the rest of type graphs
 *     turn out equivalent, we'll re-resolve FWD to concrete STRUCT/UNION from
 *     canonical graph.
 */
अटल पूर्णांक btf_dedup_is_equiv(काष्ठा btf_dedup *d, __u32 cand_id,
			      __u32 canon_id)
अणु
	काष्ठा btf_type *cand_type;
	काष्ठा btf_type *canon_type;
	__u32 hypot_type_id;
	__u16 cand_kind;
	__u16 canon_kind;
	पूर्णांक i, eq;

	/* अगर both resolve to the same canonical, they must be equivalent */
	अगर (resolve_type_id(d, cand_id) == resolve_type_id(d, canon_id))
		वापस 1;

	canon_id = resolve_fwd_id(d, canon_id);

	hypot_type_id = d->hypot_map[canon_id];
	अगर (hypot_type_id <= BTF_MAX_NR_TYPES) अणु
		/* In some हालs compiler will generate dअगरferent DWARF types
		 * क्रम *identical* array type definitions and use them क्रम
		 * dअगरferent fields within the *same* काष्ठा. This अवरोधs type
		 * equivalence check, which makes an assumption that candidate
		 * types sub-graph has a consistent and deduped-by-compiler
		 * types within a single CU. So work around that by explicitly
		 * allowing identical array types here.
		 */
		वापस hypot_type_id == cand_id ||
		       btf_dedup_identical_arrays(d, hypot_type_id, cand_id);
	पूर्ण

	अगर (btf_dedup_hypot_map_add(d, canon_id, cand_id))
		वापस -ENOMEM;

	cand_type = btf_type_by_id(d->btf, cand_id);
	canon_type = btf_type_by_id(d->btf, canon_id);
	cand_kind = btf_kind(cand_type);
	canon_kind = btf_kind(canon_type);

	अगर (cand_type->name_off != canon_type->name_off)
		वापस 0;

	/* FWD <--> STRUCT/UNION equivalence check, अगर enabled */
	अगर (!d->opts.करोnt_resolve_fwds
	    && (cand_kind == BTF_KIND_FWD || canon_kind == BTF_KIND_FWD)
	    && cand_kind != canon_kind) अणु
		__u16 real_kind;
		__u16 fwd_kind;

		अगर (cand_kind == BTF_KIND_FWD) अणु
			real_kind = canon_kind;
			fwd_kind = btf_fwd_kind(cand_type);
		पूर्ण अन्यथा अणु
			real_kind = cand_kind;
			fwd_kind = btf_fwd_kind(canon_type);
			/* we'd need to resolve base FWD to STRUCT/UNION */
			अगर (fwd_kind == real_kind && canon_id < d->btf->start_id)
				d->hypot_adjust_canon = true;
		पूर्ण
		वापस fwd_kind == real_kind;
	पूर्ण

	अगर (cand_kind != canon_kind)
		वापस 0;

	चयन (cand_kind) अणु
	हाल BTF_KIND_INT:
		वापस btf_equal_पूर्णांक(cand_type, canon_type);

	हाल BTF_KIND_ENUM:
		अगर (d->opts.करोnt_resolve_fwds)
			वापस btf_equal_क्रमागत(cand_type, canon_type);
		अन्यथा
			वापस btf_compat_क्रमागत(cand_type, canon_type);

	हाल BTF_KIND_FWD:
	हाल BTF_KIND_FLOAT:
		वापस btf_equal_common(cand_type, canon_type);

	हाल BTF_KIND_CONST:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_RESTRICT:
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_FUNC:
		अगर (cand_type->info != canon_type->info)
			वापस 0;
		वापस btf_dedup_is_equiv(d, cand_type->type, canon_type->type);

	हाल BTF_KIND_ARRAY: अणु
		स्थिर काष्ठा btf_array *cand_arr, *canon_arr;

		अगर (!btf_compat_array(cand_type, canon_type))
			वापस 0;
		cand_arr = btf_array(cand_type);
		canon_arr = btf_array(canon_type);
		eq = btf_dedup_is_equiv(d, cand_arr->index_type, canon_arr->index_type);
		अगर (eq <= 0)
			वापस eq;
		वापस btf_dedup_is_equiv(d, cand_arr->type, canon_arr->type);
	पूर्ण

	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION: अणु
		स्थिर काष्ठा btf_member *cand_m, *canon_m;
		__u16 vlen;

		अगर (!btf_shallow_equal_काष्ठा(cand_type, canon_type))
			वापस 0;
		vlen = btf_vlen(cand_type);
		cand_m = btf_members(cand_type);
		canon_m = btf_members(canon_type);
		क्रम (i = 0; i < vlen; i++) अणु
			eq = btf_dedup_is_equiv(d, cand_m->type, canon_m->type);
			अगर (eq <= 0)
				वापस eq;
			cand_m++;
			canon_m++;
		पूर्ण

		वापस 1;
	पूर्ण

	हाल BTF_KIND_FUNC_PROTO: अणु
		स्थिर काष्ठा btf_param *cand_p, *canon_p;
		__u16 vlen;

		अगर (!btf_compat_fnproto(cand_type, canon_type))
			वापस 0;
		eq = btf_dedup_is_equiv(d, cand_type->type, canon_type->type);
		अगर (eq <= 0)
			वापस eq;
		vlen = btf_vlen(cand_type);
		cand_p = btf_params(cand_type);
		canon_p = btf_params(canon_type);
		क्रम (i = 0; i < vlen; i++) अणु
			eq = btf_dedup_is_equiv(d, cand_p->type, canon_p->type);
			अगर (eq <= 0)
				वापस eq;
			cand_p++;
			canon_p++;
		पूर्ण
		वापस 1;
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Use hypothetical mapping, produced by successful type graph equivalence
 * check, to augment existing काष्ठा/जोड़ canonical mapping, where possible.
 *
 * If BTF_KIND_FWD resolution is allowed, this mapping is also used to record
 * FWD -> STRUCT/UNION correspondence as well. FWD resolution is bidirectional:
 * it करोesn't matter अगर FWD type was part of canonical graph or candidate one,
 * we are recording the mapping anyway. As opposed to carefulness required
 * क्रम काष्ठा/जोड़ correspondence mapping (described below), क्रम FWD resolution
 * it's not important, as by the समय that FWD type (reference type) will be
 * deduplicated all काष्ठाs/जोड़s will be deduped alपढ़ोy anyway.
 *
 * Recording STRUCT/UNION mapping is purely a perक्रमmance optimization and is
 * not required क्रम correctness. It needs to be करोne carefully to ensure that
 * काष्ठा/जोड़ from candidate's type graph is not mapped पूर्णांकo corresponding
 * काष्ठा/जोड़ from canonical type graph that itself hasn't been resolved पूर्णांकo
 * canonical representative. The only guarantee we have is that canonical
 * काष्ठा/जोड़ was determined as canonical and that won't change. But any
 * types referenced through that काष्ठा/जोड़ fields could have been not yet
 * resolved, so in हाल like that it's too early to establish any kind of
 * correspondence between काष्ठाs/जोड़s.
 *
 * No canonical correspondence is derived क्रम primitive types (they are alपढ़ोy
 * deduplicated completely alपढ़ोy anyway) or reference types (they rely on
 * stability of काष्ठा/जोड़ canonical relationship क्रम equivalence checks).
 */
अटल व्योम btf_dedup_merge_hypot_map(काष्ठा btf_dedup *d)
अणु
	__u32 canon_type_id, targ_type_id;
	__u16 t_kind, c_kind;
	__u32 t_id, c_id;
	पूर्णांक i;

	क्रम (i = 0; i < d->hypot_cnt; i++) अणु
		canon_type_id = d->hypot_list[i];
		targ_type_id = d->hypot_map[canon_type_id];
		t_id = resolve_type_id(d, targ_type_id);
		c_id = resolve_type_id(d, canon_type_id);
		t_kind = btf_kind(btf__type_by_id(d->btf, t_id));
		c_kind = btf_kind(btf__type_by_id(d->btf, c_id));
		/*
		 * Resolve FWD पूर्णांकo STRUCT/UNION.
		 * It's ok to resolve FWD into STRUCT/UNION that's not yet
		 * mapped to canonical representative (as opposed to
		 * STRUCT/UNION <--> STRUCT/UNION mapping logic below), because
		 * eventually that काष्ठा is going to be mapped and all resolved
		 * FWDs will स्वतःmatically resolve to correct canonical
		 * representative. This will happen beक्रमe ref type deduping,
		 * which critically depends on stability of these mapping. This
		 * stability is not a requirement क्रम STRUCT/UNION equivalence
		 * checks, though.
		 */

		/* अगर it's the split BTF हाल, we still need to poपूर्णांक base FWD
		 * to STRUCT/UNION in a split BTF, because FWDs from split BTF
		 * will be resolved against base FWD. If we करोn't poपूर्णांक base
		 * canonical FWD to the resolved STRUCT/UNION, then all the
		 * FWDs in split BTF won't be correctly resolved to a proper
		 * STRUCT/UNION.
		 */
		अगर (t_kind != BTF_KIND_FWD && c_kind == BTF_KIND_FWD)
			d->map[c_id] = t_id;

		/* अगर graph equivalence determined that we'd need to adjust
		 * base canonical types, then we need to only poपूर्णांक base FWDs
		 * to STRUCTs/UNIONs and करो no more modअगरications. For all
		 * other purposes the type graphs were not equivalent.
		 */
		अगर (d->hypot_adjust_canon)
			जारी;
		
		अगर (t_kind == BTF_KIND_FWD && c_kind != BTF_KIND_FWD)
			d->map[t_id] = c_id;

		अगर ((t_kind == BTF_KIND_STRUCT || t_kind == BTF_KIND_UNION) &&
		    c_kind != BTF_KIND_FWD &&
		    is_type_mapped(d, c_id) &&
		    !is_type_mapped(d, t_id)) अणु
			/*
			 * as a perf optimization, we can map काष्ठा/जोड़
			 * that's part of type graph we just verअगरied क्रम
			 * equivalence. We can करो that क्रम काष्ठा/जोड़ that has
			 * canonical representative only, though.
			 */
			d->map[t_id] = c_id;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Deduplicate काष्ठा/जोड़ types.
 *
 * For each काष्ठा/जोड़ type its type signature hash is calculated, taking
 * पूर्णांकo account type's name, size, number, order and names of fields, but
 * ignoring type ID's referenced from fields, because they might not be deduped
 * completely until after reference types deduplication phase. This type hash
 * is used to iterate over all potential canonical types, sharing same hash.
 * For each canonical candidate we check whether type graphs that they क्रमm
 * (through referenced types in fields and so on) are equivalent using algorithm
 * implemented in `btf_dedup_is_equiv`. If such equivalence is found and
 * BTF_KIND_FWD resolution is allowed, then hypothetical mapping
 * (btf_dedup->hypot_map) produced by aक्रमementioned type graph equivalence
 * algorithm is used to record FWD -> STRUCT/UNION mapping. It's also used to
 * potentially map other काष्ठाs/जोड़s to their canonical representatives,
 * अगर such relationship hasn't yet been established. This speeds up algorithm
 * by eliminating some of the duplicate work.
 *
 * If no matching canonical representative was found, काष्ठा/जोड़ is marked
 * as canonical क्रम itself and is added पूर्णांकo btf_dedup->dedup_table hash map
 * क्रम further look ups.
 */
अटल पूर्णांक btf_dedup_काष्ठा_type(काष्ठा btf_dedup *d, __u32 type_id)
अणु
	काष्ठा btf_type *cand_type, *t;
	काष्ठा hashmap_entry *hash_entry;
	/* अगर we करोn't find equivalent type, then we are canonical */
	__u32 new_id = type_id;
	__u16 kind;
	दीर्घ h;

	/* alपढ़ोy deduped or is in process of deduping (loop detected) */
	अगर (d->map[type_id] <= BTF_MAX_NR_TYPES)
		वापस 0;

	t = btf_type_by_id(d->btf, type_id);
	kind = btf_kind(t);

	अगर (kind != BTF_KIND_STRUCT && kind != BTF_KIND_UNION)
		वापस 0;

	h = btf_hash_काष्ठा(t);
	क्रम_each_dedup_cand(d, hash_entry, h) अणु
		__u32 cand_id = (__u32)(दीर्घ)hash_entry->value;
		पूर्णांक eq;

		/*
		 * Even though btf_dedup_is_equiv() checks क्रम
		 * btf_shallow_equal_काष्ठा() पूर्णांकernally when checking two
		 * काष्ठाs (जोड़s) क्रम equivalence, we need to guard here
		 * from picking matching FWD type as a dedup candidate.
		 * This can happen due to hash collision. In such हाल just
		 * relying on btf_dedup_is_equiv() would lead to potentially
		 * creating a loop (FWD -> STRUCT and STRUCT -> FWD), because
		 * FWD and compatible STRUCT/UNION are considered equivalent.
		 */
		cand_type = btf_type_by_id(d->btf, cand_id);
		अगर (!btf_shallow_equal_काष्ठा(t, cand_type))
			जारी;

		btf_dedup_clear_hypot_map(d);
		eq = btf_dedup_is_equiv(d, type_id, cand_id);
		अगर (eq < 0)
			वापस eq;
		अगर (!eq)
			जारी;
		btf_dedup_merge_hypot_map(d);
		अगर (d->hypot_adjust_canon) /* not really equivalent */
			जारी;
		new_id = cand_id;
		अवरोध;
	पूर्ण

	d->map[type_id] = new_id;
	अगर (type_id == new_id && btf_dedup_table_add(d, h, type_id))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक btf_dedup_काष्ठा_types(काष्ठा btf_dedup *d)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < d->btf->nr_types; i++) अणु
		err = btf_dedup_काष्ठा_type(d, d->btf->start_id + i);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Deduplicate reference type.
 *
 * Once all primitive and काष्ठा/जोड़ types got deduplicated, we can easily
 * deduplicate all other (reference) BTF types. This is करोne in two steps:
 *
 * 1. Resolve all referenced type IDs पूर्णांकo their canonical type IDs. This
 * resolution can be करोne either immediately क्रम primitive or काष्ठा/जोड़ types
 * (because they were deduped in previous two phases) or recursively क्रम
 * reference types. Recursion will always terminate at either primitive or
 * काष्ठा/जोड़ type, at which poपूर्णांक we can "unwind" chain of reference types
 * one by one. There is no danger of encountering cycles because in C type
 * प्रणाली the only way to क्रमm type cycle is through काष्ठा/जोड़, so any chain
 * of reference types, even those taking part in a type cycle, will inevitably
 * reach काष्ठा/जोड़ at some poपूर्णांक.
 *
 * 2. Once all referenced type IDs are resolved पूर्णांकo canonical ones, BTF type
 * becomes "stable", in the sense that no further deduplication will cause
 * any changes to it. With that, it's now possible to calculate type's signature
 * hash (this समय taking पूर्णांकo account referenced type IDs) and loop over all
 * potential canonical representatives. If no match was found, current type
 * will become canonical representative of itself and will be added पूर्णांकo
 * btf_dedup->dedup_table as another possible canonical representative.
 */
अटल पूर्णांक btf_dedup_ref_type(काष्ठा btf_dedup *d, __u32 type_id)
अणु
	काष्ठा hashmap_entry *hash_entry;
	__u32 new_id = type_id, cand_id;
	काष्ठा btf_type *t, *cand;
	/* अगर we करोn't find equivalent type, then we are representative type */
	पूर्णांक ref_type_id;
	दीर्घ h;

	अगर (d->map[type_id] == BTF_IN_PROGRESS_ID)
		वापस -ELOOP;
	अगर (d->map[type_id] <= BTF_MAX_NR_TYPES)
		वापस resolve_type_id(d, type_id);

	t = btf_type_by_id(d->btf, type_id);
	d->map[type_id] = BTF_IN_PROGRESS_ID;

	चयन (btf_kind(t)) अणु
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_RESTRICT:
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_FUNC:
		ref_type_id = btf_dedup_ref_type(d, t->type);
		अगर (ref_type_id < 0)
			वापस ref_type_id;
		t->type = ref_type_id;

		h = btf_hash_common(t);
		क्रम_each_dedup_cand(d, hash_entry, h) अणु
			cand_id = (__u32)(दीर्घ)hash_entry->value;
			cand = btf_type_by_id(d->btf, cand_id);
			अगर (btf_equal_common(t, cand)) अणु
				new_id = cand_id;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BTF_KIND_ARRAY: अणु
		काष्ठा btf_array *info = btf_array(t);

		ref_type_id = btf_dedup_ref_type(d, info->type);
		अगर (ref_type_id < 0)
			वापस ref_type_id;
		info->type = ref_type_id;

		ref_type_id = btf_dedup_ref_type(d, info->index_type);
		अगर (ref_type_id < 0)
			वापस ref_type_id;
		info->index_type = ref_type_id;

		h = btf_hash_array(t);
		क्रम_each_dedup_cand(d, hash_entry, h) अणु
			cand_id = (__u32)(दीर्घ)hash_entry->value;
			cand = btf_type_by_id(d->btf, cand_id);
			अगर (btf_equal_array(t, cand)) अणु
				new_id = cand_id;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	हाल BTF_KIND_FUNC_PROTO: अणु
		काष्ठा btf_param *param;
		__u16 vlen;
		पूर्णांक i;

		ref_type_id = btf_dedup_ref_type(d, t->type);
		अगर (ref_type_id < 0)
			वापस ref_type_id;
		t->type = ref_type_id;

		vlen = btf_vlen(t);
		param = btf_params(t);
		क्रम (i = 0; i < vlen; i++) अणु
			ref_type_id = btf_dedup_ref_type(d, param->type);
			अगर (ref_type_id < 0)
				वापस ref_type_id;
			param->type = ref_type_id;
			param++;
		पूर्ण

		h = btf_hash_fnproto(t);
		क्रम_each_dedup_cand(d, hash_entry, h) अणु
			cand_id = (__u32)(दीर्घ)hash_entry->value;
			cand = btf_type_by_id(d->btf, cand_id);
			अगर (btf_equal_fnproto(t, cand)) अणु
				new_id = cand_id;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण

	d->map[type_id] = new_id;
	अगर (type_id == new_id && btf_dedup_table_add(d, h, type_id))
		वापस -ENOMEM;

	वापस new_id;
पूर्ण

अटल पूर्णांक btf_dedup_ref_types(काष्ठा btf_dedup *d)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < d->btf->nr_types; i++) अणु
		err = btf_dedup_ref_type(d, d->btf->start_id + i);
		अगर (err < 0)
			वापस err;
	पूर्ण
	/* we won't need d->dedup_table anymore */
	hashmap__मुक्त(d->dedup_table);
	d->dedup_table = शून्य;
	वापस 0;
पूर्ण

/*
 * Compact types.
 *
 * After we established क्रम each type its corresponding canonical representative
 * type, we now can eliminate types that are not canonical and leave only
 * canonical ones layed out sequentially in memory by copying them over
 * duplicates. During compaction btf_dedup->hypot_map array is reused to store
 * a map from original type ID to a new compacted type ID, which will be used
 * during next phase to "fix up" type IDs, referenced from काष्ठा/जोड़ and
 * reference types.
 */
अटल पूर्णांक btf_dedup_compact_types(काष्ठा btf_dedup *d)
अणु
	__u32 *new_offs;
	__u32 next_type_id = d->btf->start_id;
	स्थिर काष्ठा btf_type *t;
	व्योम *p;
	पूर्णांक i, id, len;

	/* we are going to reuse hypot_map to store compaction remapping */
	d->hypot_map[0] = 0;
	/* base BTF types are not rक्रमागतbered */
	क्रम (id = 1; id < d->btf->start_id; id++)
		d->hypot_map[id] = id;
	क्रम (i = 0, id = d->btf->start_id; i < d->btf->nr_types; i++, id++)
		d->hypot_map[id] = BTF_UNPROCESSED_ID;

	p = d->btf->types_data;

	क्रम (i = 0, id = d->btf->start_id; i < d->btf->nr_types; i++, id++) अणु
		अगर (d->map[id] != id)
			जारी;

		t = btf__type_by_id(d->btf, id);
		len = btf_type_size(t);
		अगर (len < 0)
			वापस len;

		स_हटाओ(p, t, len);
		d->hypot_map[id] = next_type_id;
		d->btf->type_offs[next_type_id - d->btf->start_id] = p - d->btf->types_data;
		p += len;
		next_type_id++;
	पूर्ण

	/* shrink काष्ठा btf's पूर्णांकernal types index and update btf_header */
	d->btf->nr_types = next_type_id - d->btf->start_id;
	d->btf->type_offs_cap = d->btf->nr_types;
	d->btf->hdr->type_len = p - d->btf->types_data;
	new_offs = libbpf_पुनः_स्मृतिarray(d->btf->type_offs, d->btf->type_offs_cap,
				       माप(*new_offs));
	अगर (d->btf->type_offs_cap && !new_offs)
		वापस -ENOMEM;
	d->btf->type_offs = new_offs;
	d->btf->hdr->str_off = d->btf->hdr->type_len;
	d->btf->raw_size = d->btf->hdr->hdr_len + d->btf->hdr->type_len + d->btf->hdr->str_len;
	वापस 0;
पूर्ण

/*
 * Figure out final (deduplicated and compacted) type ID क्रम provided original
 * `type_id` by first resolving it पूर्णांकo corresponding canonical type ID and
 * then mapping it to a deduplicated type ID, stored in btf_dedup->hypot_map,
 * which is populated during compaction phase.
 */
अटल पूर्णांक btf_dedup_remap_type_id(__u32 *type_id, व्योम *ctx)
अणु
	काष्ठा btf_dedup *d = ctx;
	__u32 resolved_type_id, new_type_id;

	resolved_type_id = resolve_type_id(d, *type_id);
	new_type_id = d->hypot_map[resolved_type_id];
	अगर (new_type_id > BTF_MAX_NR_TYPES)
		वापस -EINVAL;

	*type_id = new_type_id;
	वापस 0;
पूर्ण

/*
 * Remap referenced type IDs पूर्णांकo deduped type IDs.
 *
 * After BTF types are deduplicated and compacted, their final type IDs may
 * dअगरfer from original ones. The map from original to a corresponding
 * deduped type ID is stored in btf_dedup->hypot_map and is populated during
 * compaction phase. During remapping phase we are rewriting all type IDs
 * referenced from any BTF type (e.g., काष्ठा fields, func proto args, etc) to
 * their final deduped type IDs.
 */
अटल पूर्णांक btf_dedup_remap_types(काष्ठा btf_dedup *d)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < d->btf->nr_types; i++) अणु
		काष्ठा btf_type *t = btf_type_by_id(d->btf, d->btf->start_id + i);

		r = btf_type_visit_type_ids(t, btf_dedup_remap_type_id, d);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (!d->btf_ext)
		वापस 0;

	r = btf_ext_visit_type_ids(d->btf_ext, btf_dedup_remap_type_id, d);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

/*
 * Probe few well-known locations क्रम vmlinux kernel image and try to load BTF
 * data out of it to use क्रम target BTF.
 */
काष्ठा btf *libbpf_find_kernel_btf(व्योम)
अणु
	काष्ठा अणु
		स्थिर अक्षर *path_fmt;
		bool raw_btf;
	पूर्ण locations[] = अणु
		/* try canonical vmlinux BTF through sysfs first */
		अणु "/sys/kernel/btf/vmlinux", true /* raw BTF */ पूर्ण,
		/* fall back to trying to find vmlinux ELF on disk otherwise */
		अणु "/boot/vmlinux-%1$s" पूर्ण,
		अणु "/lib/modules/%1$s/vmlinux-%1$s" पूर्ण,
		अणु "/lib/modules/%1$s/build/vmlinux" पूर्ण,
		अणु "/usr/lib/modules/%1$s/kernel/vmlinux" पूर्ण,
		अणु "/usr/lib/debug/boot/vmlinux-%1$s" पूर्ण,
		अणु "/usr/lib/debug/boot/vmlinux-%1$s.debug" पूर्ण,
		अणु "/usr/lib/debug/lib/modules/%1$s/vmlinux" पूर्ण,
	पूर्ण;
	अक्षर path[PATH_MAX + 1];
	काष्ठा utsname buf;
	काष्ठा btf *btf;
	पूर्णांक i;

	uname(&buf);

	क्रम (i = 0; i < ARRAY_SIZE(locations); i++) अणु
		snम_लिखो(path, PATH_MAX, locations[i].path_fmt, buf.release);

		अगर (access(path, R_OK))
			जारी;

		अगर (locations[i].raw_btf)
			btf = btf__parse_raw(path);
		अन्यथा
			btf = btf__parse_elf(path, शून्य);

		pr_debug("loading kernel BTF '%s': %ld\n",
			 path, IS_ERR(btf) ? PTR_ERR(btf) : 0);
		अगर (IS_ERR(btf))
			जारी;

		वापस btf;
	पूर्ण

	pr_warn("failed to find valid kernel BTF\n");
	वापस ERR_PTR(-ESRCH);
पूर्ण

पूर्णांक btf_type_visit_type_ids(काष्ठा btf_type *t, type_id_visit_fn visit, व्योम *ctx)
अणु
	पूर्णांक i, n, err;

	चयन (btf_kind(t)) अणु
	हाल BTF_KIND_INT:
	हाल BTF_KIND_FLOAT:
	हाल BTF_KIND_ENUM:
		वापस 0;

	हाल BTF_KIND_FWD:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_RESTRICT:
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_FUNC:
	हाल BTF_KIND_VAR:
		वापस visit(&t->type, ctx);

	हाल BTF_KIND_ARRAY: अणु
		काष्ठा btf_array *a = btf_array(t);

		err = visit(&a->type, ctx);
		err = err ?: visit(&a->index_type, ctx);
		वापस err;
	पूर्ण

	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION: अणु
		काष्ठा btf_member *m = btf_members(t);

		क्रम (i = 0, n = btf_vlen(t); i < n; i++, m++) अणु
			err = visit(&m->type, ctx);
			अगर (err)
				वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	हाल BTF_KIND_FUNC_PROTO: अणु
		काष्ठा btf_param *m = btf_params(t);

		err = visit(&t->type, ctx);
		अगर (err)
			वापस err;
		क्रम (i = 0, n = btf_vlen(t); i < n; i++, m++) अणु
			err = visit(&m->type, ctx);
			अगर (err)
				वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	हाल BTF_KIND_DATASEC: अणु
		काष्ठा btf_var_secinfo *m = btf_var_secinfos(t);

		क्रम (i = 0, n = btf_vlen(t); i < n; i++, m++) अणु
			err = visit(&m->type, ctx);
			अगर (err)
				वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक btf_type_visit_str_offs(काष्ठा btf_type *t, str_off_visit_fn visit, व्योम *ctx)
अणु
	पूर्णांक i, n, err;

	err = visit(&t->name_off, ctx);
	अगर (err)
		वापस err;

	चयन (btf_kind(t)) अणु
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION: अणु
		काष्ठा btf_member *m = btf_members(t);

		क्रम (i = 0, n = btf_vlen(t); i < n; i++, m++) अणु
			err = visit(&m->name_off, ctx);
			अगर (err)
				वापस err;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_ENUM: अणु
		काष्ठा btf_क्रमागत *m = btf_क्रमागत(t);

		क्रम (i = 0, n = btf_vlen(t); i < n; i++, m++) अणु
			err = visit(&m->name_off, ctx);
			अगर (err)
				वापस err;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_FUNC_PROTO: अणु
		काष्ठा btf_param *m = btf_params(t);

		क्रम (i = 0, n = btf_vlen(t); i < n; i++, m++) अणु
			err = visit(&m->name_off, ctx);
			अगर (err)
				वापस err;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक btf_ext_visit_type_ids(काष्ठा btf_ext *btf_ext, type_id_visit_fn visit, व्योम *ctx)
अणु
	स्थिर काष्ठा btf_ext_info *seg;
	काष्ठा btf_ext_info_sec *sec;
	पूर्णांक i, err;

	seg = &btf_ext->func_info;
	क्रम_each_btf_ext_sec(seg, sec) अणु
		काष्ठा bpf_func_info_min *rec;

		क्रम_each_btf_ext_rec(seg, sec, i, rec) अणु
			err = visit(&rec->type_id, ctx);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	seg = &btf_ext->core_relo_info;
	क्रम_each_btf_ext_sec(seg, sec) अणु
		काष्ठा bpf_core_relo *rec;

		क्रम_each_btf_ext_rec(seg, sec, i, rec) अणु
			err = visit(&rec->type_id, ctx);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक btf_ext_visit_str_offs(काष्ठा btf_ext *btf_ext, str_off_visit_fn visit, व्योम *ctx)
अणु
	स्थिर काष्ठा btf_ext_info *seg;
	काष्ठा btf_ext_info_sec *sec;
	पूर्णांक i, err;

	seg = &btf_ext->func_info;
	क्रम_each_btf_ext_sec(seg, sec) अणु
		err = visit(&sec->sec_name_off, ctx);
		अगर (err)
			वापस err;
	पूर्ण

	seg = &btf_ext->line_info;
	क्रम_each_btf_ext_sec(seg, sec) अणु
		काष्ठा bpf_line_info_min *rec;

		err = visit(&sec->sec_name_off, ctx);
		अगर (err)
			वापस err;

		क्रम_each_btf_ext_rec(seg, sec, i, rec) अणु
			err = visit(&rec->file_name_off, ctx);
			अगर (err)
				वापस err;
			err = visit(&rec->line_off, ctx);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	seg = &btf_ext->core_relo_info;
	क्रम_each_btf_ext_sec(seg, sec) अणु
		काष्ठा bpf_core_relo *rec;

		err = visit(&sec->sec_name_off, ctx);
		अगर (err)
			वापस err;

		क्रम_each_btf_ext_rec(seg, sec, i, rec) अणु
			err = visit(&rec->access_str_off, ctx);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
