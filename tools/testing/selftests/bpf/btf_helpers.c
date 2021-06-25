<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <bpf/btf.h>
#समावेश <bpf/libbpf.h>
#समावेश "test_progs.h"

अटल स्थिर अक्षर * स्थिर btf_kind_str_mapping[] = अणु
	[BTF_KIND_UNKN]		= "UNKNOWN",
	[BTF_KIND_INT]		= "INT",
	[BTF_KIND_PTR]		= "PTR",
	[BTF_KIND_ARRAY]	= "ARRAY",
	[BTF_KIND_STRUCT]	= "STRUCT",
	[BTF_KIND_UNION]	= "UNION",
	[BTF_KIND_ENUM]		= "ENUM",
	[BTF_KIND_FWD]		= "FWD",
	[BTF_KIND_TYPEDEF]	= "TYPEDEF",
	[BTF_KIND_VOLATILE]	= "VOLATILE",
	[BTF_KIND_CONST]	= "CONST",
	[BTF_KIND_RESTRICT]	= "RESTRICT",
	[BTF_KIND_FUNC]		= "FUNC",
	[BTF_KIND_FUNC_PROTO]	= "FUNC_PROTO",
	[BTF_KIND_VAR]		= "VAR",
	[BTF_KIND_DATASEC]	= "DATASEC",
	[BTF_KIND_FLOAT]	= "FLOAT",
पूर्ण;

अटल स्थिर अक्षर *btf_kind_str(__u16 kind)
अणु
	अगर (kind > BTF_KIND_DATASEC)
		वापस "UNKNOWN";
	वापस btf_kind_str_mapping[kind];
पूर्ण

अटल स्थिर अक्षर *btf_पूर्णांक_enc_str(__u8 encoding)
अणु
	चयन (encoding) अणु
	हाल 0:
		वापस "(none)";
	हाल BTF_INT_SIGNED:
		वापस "SIGNED";
	हाल BTF_INT_CHAR:
		वापस "CHAR";
	हाल BTF_INT_BOOL:
		वापस "BOOL";
	शेष:
		वापस "UNKN";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *btf_var_linkage_str(__u32 linkage)
अणु
	चयन (linkage) अणु
	हाल BTF_VAR_STATIC:
		वापस "static";
	हाल BTF_VAR_GLOBAL_ALLOCATED:
		वापस "global-alloc";
	शेष:
		वापस "(unknown)";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *btf_func_linkage_str(स्थिर काष्ठा btf_type *t)
अणु
	चयन (btf_vlen(t)) अणु
	हाल BTF_FUNC_STATIC:
		वापस "static";
	हाल BTF_FUNC_GLOBAL:
		वापस "global";
	हाल BTF_FUNC_EXTERN:
		वापस "extern";
	शेष:
		वापस "(unknown)";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *btf_str(स्थिर काष्ठा btf *btf, __u32 off)
अणु
	अगर (!off)
		वापस "(anon)";
	वापस btf__str_by_offset(btf, off) ?: "(invalid)";
पूर्ण

पूर्णांक ख_लिखो_btf_type_raw(खाता *out, स्थिर काष्ठा btf *btf, __u32 id)
अणु
	स्थिर काष्ठा btf_type *t;
	पूर्णांक kind, i;
	__u32 vlen;

	t = btf__type_by_id(btf, id);
	अगर (!t)
		वापस -EINVAL;

	vlen = btf_vlen(t);
	kind = btf_kind(t);

	ख_लिखो(out, "[%u] %s '%s'", id, btf_kind_str(kind), btf_str(btf, t->name_off));

	चयन (kind) अणु
	हाल BTF_KIND_INT:
		ख_लिखो(out, " size=%u bits_offset=%u nr_bits=%u encoding=%s",
			t->size, btf_पूर्णांक_offset(t), btf_पूर्णांक_bits(t),
			btf_पूर्णांक_enc_str(btf_पूर्णांक_encoding(t)));
		अवरोध;
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_RESTRICT:
	हाल BTF_KIND_TYPEDEF:
		ख_लिखो(out, " type_id=%u", t->type);
		अवरोध;
	हाल BTF_KIND_ARRAY: अणु
		स्थिर काष्ठा btf_array *arr = btf_array(t);

		ख_लिखो(out, " type_id=%u index_type_id=%u nr_elems=%u",
			arr->type, arr->index_type, arr->nelems);
		अवरोध;
	पूर्ण
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION: अणु
		स्थिर काष्ठा btf_member *m = btf_members(t);

		ख_लिखो(out, " size=%u vlen=%u", t->size, vlen);
		क्रम (i = 0; i < vlen; i++, m++) अणु
			__u32 bit_off, bit_sz;

			bit_off = btf_member_bit_offset(t, i);
			bit_sz = btf_member_bitfield_size(t, i);
			ख_लिखो(out, "\n\t'%s' type_id=%u bits_offset=%u",
				btf_str(btf, m->name_off), m->type, bit_off);
			अगर (bit_sz)
				ख_लिखो(out, " bitfield_size=%u", bit_sz);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_ENUM: अणु
		स्थिर काष्ठा btf_क्रमागत *v = btf_क्रमागत(t);

		ख_लिखो(out, " size=%u vlen=%u", t->size, vlen);
		क्रम (i = 0; i < vlen; i++, v++) अणु
			ख_लिखो(out, "\n\t'%s' val=%u",
				btf_str(btf, v->name_off), v->val);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_FWD:
		ख_लिखो(out, " fwd_kind=%s", btf_kflag(t) ? "union" : "struct");
		अवरोध;
	हाल BTF_KIND_FUNC:
		ख_लिखो(out, " type_id=%u linkage=%s", t->type, btf_func_linkage_str(t));
		अवरोध;
	हाल BTF_KIND_FUNC_PROTO: अणु
		स्थिर काष्ठा btf_param *p = btf_params(t);

		ख_लिखो(out, " ret_type_id=%u vlen=%u", t->type, vlen);
		क्रम (i = 0; i < vlen; i++, p++) अणु
			ख_लिखो(out, "\n\t'%s' type_id=%u",
				btf_str(btf, p->name_off), p->type);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_VAR:
		ख_लिखो(out, " type_id=%u, linkage=%s",
			t->type, btf_var_linkage_str(btf_var(t)->linkage));
		अवरोध;
	हाल BTF_KIND_DATASEC: अणु
		स्थिर काष्ठा btf_var_secinfo *v = btf_var_secinfos(t);

		ख_लिखो(out, " size=%u vlen=%u", t->size, vlen);
		क्रम (i = 0; i < vlen; i++, v++) अणु
			ख_लिखो(out, "\n\ttype_id=%u offset=%u size=%u",
				v->type, v->offset, v->size);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_FLOAT:
		ख_लिखो(out, " size=%u", t->size);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Prपूर्णांक raw BTF type dump पूर्णांकo a local buffer and वापस string poपूर्णांकer back.
 * Buffer *will* be overwritten by subsequent btf_type_raw_dump() calls
 */
स्थिर अक्षर *btf_type_raw_dump(स्थिर काष्ठा btf *btf, पूर्णांक type_id)
अणु
	अटल अक्षर buf[16 * 1024];
	खाता *buf_file;

	buf_file = fmemखोलो(buf, माप(buf) - 1, "w");
	अगर (!buf_file) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to open memstream: %d\n", त्रुटि_सं);
		वापस शून्य;
	पूर्ण

	ख_लिखो_btf_type_raw(buf_file, btf, type_id);
	ख_साफ(buf_file);
	ख_बंद(buf_file);

	वापस buf;
पूर्ण

पूर्णांक btf_validate_raw(काष्ठा btf *btf, पूर्णांक nr_types, स्थिर अक्षर *exp_types[])
अणु
	पूर्णांक i;
	bool ok = true;

	ASSERT_EQ(btf__get_nr_types(btf), nr_types, "btf_nr_types");

	क्रम (i = 1; i <= nr_types; i++) अणु
		अगर (!ASSERT_STREQ(btf_type_raw_dump(btf, i), exp_types[i - 1], "raw_dump"))
			ok = false;
	पूर्ण

	वापस ok;
पूर्ण

अटल व्योम btf_dump_म_लिखो(व्योम *ctx, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	भख_लिखो(ctx, fmt, args);
पूर्ण

/* Prपूर्णांक BTF-to-C dump पूर्णांकo a local buffer and वापस string poपूर्णांकer back.
 * Buffer *will* be overwritten by subsequent btf_type_raw_dump() calls
 */
स्थिर अक्षर *btf_type_c_dump(स्थिर काष्ठा btf *btf)
अणु
	अटल अक्षर buf[16 * 1024];
	खाता *buf_file;
	काष्ठा btf_dump *d = शून्य;
	काष्ठा btf_dump_opts opts = अणुपूर्ण;
	पूर्णांक err, i;

	buf_file = fmemखोलो(buf, माप(buf) - 1, "w");
	अगर (!buf_file) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to open memstream: %d\n", त्रुटि_सं);
		वापस शून्य;
	पूर्ण

	opts.ctx = buf_file;
	d = btf_dump__new(btf, शून्य, &opts, btf_dump_म_लिखो);
	अगर (libbpf_get_error(d)) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to create btf_dump instance: %ld\n", libbpf_get_error(d));
		वापस शून्य;
	पूर्ण

	क्रम (i = 1; i <= btf__get_nr_types(btf); i++) अणु
		err = btf_dump__dump_type(d, i);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to dump type [%d]: %d\n", i, err);
			वापस शून्य;
		पूर्ण
	पूर्ण

	ख_साफ(buf_file);
	ख_बंद(buf_file);
	वापस buf;
पूर्ण
