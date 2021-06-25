<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Facebook */

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/err.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/btf.h>
#समावेश <bpf/libbpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/hashtable.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>

#समावेश "json_writer.h"
#समावेश "main.h"

अटल स्थिर अक्षर * स्थिर btf_kind_str[NR_BTF_KINDS] = अणु
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

काष्ठा btf_attach_table अणु
	DECLARE_HASHTABLE(table, 16);
पूर्ण;

काष्ठा btf_attach_poपूर्णांक अणु
	__u32 obj_id;
	__u32 btf_id;
	काष्ठा hlist_node hash;
पूर्ण;

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
		वापस "global";
	हाल BTF_VAR_GLOBAL_EXTERN:
		वापस "extern";
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
	वापस btf__name_by_offset(btf, off) ? : "(invalid)";
पूर्ण

अटल पूर्णांक btf_kind_safe(पूर्णांक kind)
अणु
	वापस kind <= BTF_KIND_MAX ? kind : BTF_KIND_UNKN;
पूर्ण

अटल पूर्णांक dump_btf_type(स्थिर काष्ठा btf *btf, __u32 id,
			 स्थिर काष्ठा btf_type *t)
अणु
	json_ग_लिखोr_t *w = json_wtr;
	पूर्णांक kind = btf_kind(t);

	अगर (json_output) अणु
		jsonw_start_object(w);
		jsonw_uपूर्णांक_field(w, "id", id);
		jsonw_string_field(w, "kind", btf_kind_str[btf_kind_safe(kind)]);
		jsonw_string_field(w, "name", btf_str(btf, t->name_off));
	पूर्ण अन्यथा अणु
		म_लिखो("[%u] %s '%s'", id, btf_kind_str[btf_kind_safe(kind)],
		       btf_str(btf, t->name_off));
	पूर्ण

	चयन (kind) अणु
	हाल BTF_KIND_INT: अणु
		__u32 v = *(__u32 *)(t + 1);
		स्थिर अक्षर *enc;

		enc = btf_पूर्णांक_enc_str(BTF_INT_ENCODING(v));

		अगर (json_output) अणु
			jsonw_uपूर्णांक_field(w, "size", t->size);
			jsonw_uपूर्णांक_field(w, "bits_offset", BTF_INT_OFFSET(v));
			jsonw_uपूर्णांक_field(w, "nr_bits", BTF_INT_BITS(v));
			jsonw_string_field(w, "encoding", enc);
		पूर्ण अन्यथा अणु
			म_लिखो(" size=%u bits_offset=%u nr_bits=%u encoding=%s",
			       t->size, BTF_INT_OFFSET(v), BTF_INT_BITS(v),
			       enc);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_RESTRICT:
	हाल BTF_KIND_TYPEDEF:
		अगर (json_output)
			jsonw_uपूर्णांक_field(w, "type_id", t->type);
		अन्यथा
			म_लिखो(" type_id=%u", t->type);
		अवरोध;
	हाल BTF_KIND_ARRAY: अणु
		स्थिर काष्ठा btf_array *arr = (स्थिर व्योम *)(t + 1);

		अगर (json_output) अणु
			jsonw_uपूर्णांक_field(w, "type_id", arr->type);
			jsonw_uपूर्णांक_field(w, "index_type_id", arr->index_type);
			jsonw_uपूर्णांक_field(w, "nr_elems", arr->nelems);
		पूर्ण अन्यथा अणु
			म_लिखो(" type_id=%u index_type_id=%u nr_elems=%u",
			       arr->type, arr->index_type, arr->nelems);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION: अणु
		स्थिर काष्ठा btf_member *m = (स्थिर व्योम *)(t + 1);
		__u16 vlen = BTF_INFO_VLEN(t->info);
		पूर्णांक i;

		अगर (json_output) अणु
			jsonw_uपूर्णांक_field(w, "size", t->size);
			jsonw_uपूर्णांक_field(w, "vlen", vlen);
			jsonw_name(w, "members");
			jsonw_start_array(w);
		पूर्ण अन्यथा अणु
			म_लिखो(" size=%u vlen=%u", t->size, vlen);
		पूर्ण
		क्रम (i = 0; i < vlen; i++, m++) अणु
			स्थिर अक्षर *name = btf_str(btf, m->name_off);
			__u32 bit_off, bit_sz;

			अगर (BTF_INFO_KFLAG(t->info)) अणु
				bit_off = BTF_MEMBER_BIT_OFFSET(m->offset);
				bit_sz = BTF_MEMBER_BITFIELD_SIZE(m->offset);
			पूर्ण अन्यथा अणु
				bit_off = m->offset;
				bit_sz = 0;
			पूर्ण

			अगर (json_output) अणु
				jsonw_start_object(w);
				jsonw_string_field(w, "name", name);
				jsonw_uपूर्णांक_field(w, "type_id", m->type);
				jsonw_uपूर्णांक_field(w, "bits_offset", bit_off);
				अगर (bit_sz) अणु
					jsonw_uपूर्णांक_field(w, "bitfield_size",
							 bit_sz);
				पूर्ण
				jsonw_end_object(w);
			पूर्ण अन्यथा अणु
				म_लिखो("\n\t'%s' type_id=%u bits_offset=%u",
				       name, m->type, bit_off);
				अगर (bit_sz)
					म_लिखो(" bitfield_size=%u", bit_sz);
			पूर्ण
		पूर्ण
		अगर (json_output)
			jsonw_end_array(w);
		अवरोध;
	पूर्ण
	हाल BTF_KIND_ENUM: अणु
		स्थिर काष्ठा btf_क्रमागत *v = (स्थिर व्योम *)(t + 1);
		__u16 vlen = BTF_INFO_VLEN(t->info);
		पूर्णांक i;

		अगर (json_output) अणु
			jsonw_uपूर्णांक_field(w, "size", t->size);
			jsonw_uपूर्णांक_field(w, "vlen", vlen);
			jsonw_name(w, "values");
			jsonw_start_array(w);
		पूर्ण अन्यथा अणु
			म_लिखो(" size=%u vlen=%u", t->size, vlen);
		पूर्ण
		क्रम (i = 0; i < vlen; i++, v++) अणु
			स्थिर अक्षर *name = btf_str(btf, v->name_off);

			अगर (json_output) अणु
				jsonw_start_object(w);
				jsonw_string_field(w, "name", name);
				jsonw_uपूर्णांक_field(w, "val", v->val);
				jsonw_end_object(w);
			पूर्ण अन्यथा अणु
				म_लिखो("\n\t'%s' val=%u", name, v->val);
			पूर्ण
		पूर्ण
		अगर (json_output)
			jsonw_end_array(w);
		अवरोध;
	पूर्ण
	हाल BTF_KIND_FWD: अणु
		स्थिर अक्षर *fwd_kind = BTF_INFO_KFLAG(t->info) ? "union"
							       : "struct";

		अगर (json_output)
			jsonw_string_field(w, "fwd_kind", fwd_kind);
		अन्यथा
			म_लिखो(" fwd_kind=%s", fwd_kind);
		अवरोध;
	पूर्ण
	हाल BTF_KIND_FUNC: अणु
		स्थिर अक्षर *linkage = btf_func_linkage_str(t);

		अगर (json_output) अणु
			jsonw_uपूर्णांक_field(w, "type_id", t->type);
			jsonw_string_field(w, "linkage", linkage);
		पूर्ण अन्यथा अणु
			म_लिखो(" type_id=%u linkage=%s", t->type, linkage);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_FUNC_PROTO: अणु
		स्थिर काष्ठा btf_param *p = (स्थिर व्योम *)(t + 1);
		__u16 vlen = BTF_INFO_VLEN(t->info);
		पूर्णांक i;

		अगर (json_output) अणु
			jsonw_uपूर्णांक_field(w, "ret_type_id", t->type);
			jsonw_uपूर्णांक_field(w, "vlen", vlen);
			jsonw_name(w, "params");
			jsonw_start_array(w);
		पूर्ण अन्यथा अणु
			म_लिखो(" ret_type_id=%u vlen=%u", t->type, vlen);
		पूर्ण
		क्रम (i = 0; i < vlen; i++, p++) अणु
			स्थिर अक्षर *name = btf_str(btf, p->name_off);

			अगर (json_output) अणु
				jsonw_start_object(w);
				jsonw_string_field(w, "name", name);
				jsonw_uपूर्णांक_field(w, "type_id", p->type);
				jsonw_end_object(w);
			पूर्ण अन्यथा अणु
				म_लिखो("\n\t'%s' type_id=%u", name, p->type);
			पूर्ण
		पूर्ण
		अगर (json_output)
			jsonw_end_array(w);
		अवरोध;
	पूर्ण
	हाल BTF_KIND_VAR: अणु
		स्थिर काष्ठा btf_var *v = (स्थिर व्योम *)(t + 1);
		स्थिर अक्षर *linkage;

		linkage = btf_var_linkage_str(v->linkage);

		अगर (json_output) अणु
			jsonw_uपूर्णांक_field(w, "type_id", t->type);
			jsonw_string_field(w, "linkage", linkage);
		पूर्ण अन्यथा अणु
			म_लिखो(" type_id=%u, linkage=%s", t->type, linkage);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BTF_KIND_DATASEC: अणु
		स्थिर काष्ठा btf_var_secinfo *v = (स्थिर व्योम *)(t + 1);
		स्थिर काष्ठा btf_type *vt;
		__u16 vlen = BTF_INFO_VLEN(t->info);
		पूर्णांक i;

		अगर (json_output) अणु
			jsonw_uपूर्णांक_field(w, "size", t->size);
			jsonw_uपूर्णांक_field(w, "vlen", vlen);
			jsonw_name(w, "vars");
			jsonw_start_array(w);
		पूर्ण अन्यथा अणु
			म_लिखो(" size=%u vlen=%u", t->size, vlen);
		पूर्ण
		क्रम (i = 0; i < vlen; i++, v++) अणु
			अगर (json_output) अणु
				jsonw_start_object(w);
				jsonw_uपूर्णांक_field(w, "type_id", v->type);
				jsonw_uपूर्णांक_field(w, "offset", v->offset);
				jsonw_uपूर्णांक_field(w, "size", v->size);
				jsonw_end_object(w);
			पूर्ण अन्यथा अणु
				म_लिखो("\n\ttype_id=%u offset=%u size=%u",
				       v->type, v->offset, v->size);

				अगर (v->type <= btf__get_nr_types(btf)) अणु
					vt = btf__type_by_id(btf, v->type);
					म_लिखो(" (%s '%s')",
					       btf_kind_str[btf_kind_safe(btf_kind(vt))],
					       btf_str(btf, vt->name_off));
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (json_output)
			jsonw_end_array(w);
		अवरोध;
	पूर्ण
	हाल BTF_KIND_FLOAT: अणु
		अगर (json_output)
			jsonw_uपूर्णांक_field(w, "size", t->size);
		अन्यथा
			म_लिखो(" size=%u", t->size);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	अगर (json_output)
		jsonw_end_object(json_wtr);
	अन्यथा
		म_लिखो("\n");

	वापस 0;
पूर्ण

अटल पूर्णांक dump_btf_raw(स्थिर काष्ठा btf *btf,
			__u32 *root_type_ids, पूर्णांक root_type_cnt)
अणु
	स्थिर काष्ठा btf_type *t;
	पूर्णांक i;

	अगर (json_output) अणु
		jsonw_start_object(json_wtr);
		jsonw_name(json_wtr, "types");
		jsonw_start_array(json_wtr);
	पूर्ण

	अगर (root_type_cnt) अणु
		क्रम (i = 0; i < root_type_cnt; i++) अणु
			t = btf__type_by_id(btf, root_type_ids[i]);
			dump_btf_type(btf, root_type_ids[i], t);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा btf *base;
		पूर्णांक cnt = btf__get_nr_types(btf);
		पूर्णांक start_id = 1;

		base = btf__base_btf(btf);
		अगर (base)
			start_id = btf__get_nr_types(base) + 1;

		क्रम (i = start_id; i <= cnt; i++) अणु
			t = btf__type_by_id(btf, i);
			dump_btf_type(btf, i, t);
		पूर्ण
	पूर्ण

	अगर (json_output) अणु
		jsonw_end_array(json_wtr);
		jsonw_end_object(json_wtr);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __म_लिखो(2, 0) btf_dump_म_लिखो(व्योम *ctx,
					   स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	भख_लिखो(मानक_निकास, fmt, args);
पूर्ण

अटल पूर्णांक dump_btf_c(स्थिर काष्ठा btf *btf,
		      __u32 *root_type_ids, पूर्णांक root_type_cnt)
अणु
	काष्ठा btf_dump *d;
	पूर्णांक err = 0, i;

	d = btf_dump__new(btf, शून्य, शून्य, btf_dump_म_लिखो);
	अगर (IS_ERR(d))
		वापस PTR_ERR(d);

	म_लिखो("#ifndef __VMLINUX_H__\n");
	म_लिखो("#define __VMLINUX_H__\n");
	म_लिखो("\n");
	म_लिखो("#ifndef BPF_NO_PRESERVE_ACCESS_INDEX\n");
	म_लिखो("#pragma clang attribute push (__attribute__((preserve_access_index)), apply_to = record)\n");
	म_लिखो("#endif\n\n");

	अगर (root_type_cnt) अणु
		क्रम (i = 0; i < root_type_cnt; i++) अणु
			err = btf_dump__dump_type(d, root_type_ids[i]);
			अगर (err)
				जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक cnt = btf__get_nr_types(btf);

		क्रम (i = 1; i <= cnt; i++) अणु
			err = btf_dump__dump_type(d, i);
			अगर (err)
				जाओ करोne;
		पूर्ण
	पूर्ण

	म_लिखो("#ifndef BPF_NO_PRESERVE_ACCESS_INDEX\n");
	म_लिखो("#pragma clang attribute pop\n");
	म_लिखो("#endif\n");
	म_लिखो("\n");
	म_लिखो("#endif /* __VMLINUX_H__ */\n");

करोne:
	btf_dump__मुक्त(d);
	वापस err;
पूर्ण

अटल पूर्णांक करो_dump(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा btf *btf = शून्य, *base = शून्य;
	__u32 root_type_ids[2];
	पूर्णांक root_type_cnt = 0;
	bool dump_c = false;
	__u32 btf_id = -1;
	स्थिर अक्षर *src;
	पूर्णांक fd = -1;
	पूर्णांक err;

	अगर (!REQ_ARGS(2)) अणु
		usage();
		वापस -1;
	पूर्ण
	src = GET_ARG();
	अगर (is_prefix(src, "map")) अणु
		काष्ठा bpf_map_info info = अणुपूर्ण;
		__u32 len = माप(info);

		अगर (!REQ_ARGS(2)) अणु
			usage();
			वापस -1;
		पूर्ण

		fd = map_parse_fd_and_info(&argc, &argv, &info, &len);
		अगर (fd < 0)
			वापस -1;

		btf_id = info.btf_id;
		अगर (argc && is_prefix(*argv, "key")) अणु
			root_type_ids[root_type_cnt++] = info.btf_key_type_id;
			NEXT_ARG();
		पूर्ण अन्यथा अगर (argc && is_prefix(*argv, "value")) अणु
			root_type_ids[root_type_cnt++] = info.btf_value_type_id;
			NEXT_ARG();
		पूर्ण अन्यथा अगर (argc && is_prefix(*argv, "all")) अणु
			NEXT_ARG();
		पूर्ण अन्यथा अगर (argc && is_prefix(*argv, "kv")) अणु
			root_type_ids[root_type_cnt++] = info.btf_key_type_id;
			root_type_ids[root_type_cnt++] = info.btf_value_type_id;
			NEXT_ARG();
		पूर्ण अन्यथा अणु
			root_type_ids[root_type_cnt++] = info.btf_key_type_id;
			root_type_ids[root_type_cnt++] = info.btf_value_type_id;
		पूर्ण
	पूर्ण अन्यथा अगर (is_prefix(src, "prog")) अणु
		काष्ठा bpf_prog_info info = अणुपूर्ण;
		__u32 len = माप(info);

		अगर (!REQ_ARGS(2)) अणु
			usage();
			वापस -1;
		पूर्ण

		fd = prog_parse_fd(&argc, &argv);
		अगर (fd < 0)
			वापस -1;

		err = bpf_obj_get_info_by_fd(fd, &info, &len);
		अगर (err) अणु
			p_err("can't get prog info: %s", म_त्रुटि(त्रुटि_सं));
			जाओ करोne;
		पूर्ण

		btf_id = info.btf_id;
	पूर्ण अन्यथा अगर (is_prefix(src, "id")) अणु
		अक्षर *endptr;

		btf_id = म_से_अदीर्घ(*argv, &endptr, 0);
		अगर (*endptr) अणु
			p_err("can't parse %s as ID", *argv);
			वापस -1;
		पूर्ण
		NEXT_ARG();
	पूर्ण अन्यथा अगर (is_prefix(src, "file")) अणु
		स्थिर अक्षर sysfs_prefix[] = "/sys/kernel/btf/";
		स्थिर अक्षर sysfs_vmlinux[] = "/sys/kernel/btf/vmlinux";

		अगर (!base_btf &&
		    म_भेदन(*argv, sysfs_prefix, माप(sysfs_prefix) - 1) == 0 &&
		    म_भेद(*argv, sysfs_vmlinux) != 0) अणु
			base = btf__parse(sysfs_vmlinux, शून्य);
			अगर (libbpf_get_error(base)) अणु
				p_err("failed to parse vmlinux BTF at '%s': %ld\n",
				      sysfs_vmlinux, libbpf_get_error(base));
				base = शून्य;
			पूर्ण
		पूर्ण

		btf = btf__parse_split(*argv, base ?: base_btf);
		अगर (IS_ERR(btf)) अणु
			err = -PTR_ERR(btf);
			btf = शून्य;
			p_err("failed to load BTF from %s: %s",
			      *argv, म_त्रुटि(err));
			जाओ करोne;
		पूर्ण
		NEXT_ARG();
	पूर्ण अन्यथा अणु
		err = -1;
		p_err("unrecognized BTF source specifier: '%s'", src);
		जाओ करोne;
	पूर्ण

	जबतक (argc) अणु
		अगर (is_prefix(*argv, "format")) अणु
			NEXT_ARG();
			अगर (argc < 1) अणु
				p_err("expecting value for 'format' option\n");
				err = -EINVAL;
				जाओ करोne;
			पूर्ण
			अगर (म_भेद(*argv, "c") == 0) अणु
				dump_c = true;
			पूर्ण अन्यथा अगर (म_भेद(*argv, "raw") == 0) अणु
				dump_c = false;
			पूर्ण अन्यथा अणु
				p_err("unrecognized format specifier: '%s', possible values: raw, c",
				      *argv);
				err = -EINVAL;
				जाओ करोne;
			पूर्ण
			NEXT_ARG();
		पूर्ण अन्यथा अणु
			p_err("unrecognized option: '%s'", *argv);
			err = -EINVAL;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (!btf) अणु
		err = btf__get_from_id(btf_id, &btf);
		अगर (err) अणु
			p_err("get btf by id (%u): %s", btf_id, म_त्रुटि(err));
			जाओ करोne;
		पूर्ण
		अगर (!btf) अणु
			err = -ENOENT;
			p_err("can't find btf with ID (%u)", btf_id);
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (dump_c) अणु
		अगर (json_output) अणु
			p_err("JSON output for C-syntax dump is not supported");
			err = -ENOTSUP;
			जाओ करोne;
		पूर्ण
		err = dump_btf_c(btf, root_type_ids, root_type_cnt);
	पूर्ण अन्यथा अणु
		err = dump_btf_raw(btf, root_type_ids, root_type_cnt);
	पूर्ण

करोne:
	बंद(fd);
	btf__मुक्त(btf);
	btf__मुक्त(base);
	वापस err;
पूर्ण

अटल पूर्णांक btf_parse_fd(पूर्णांक *argc, अक्षर ***argv)
अणु
	अचिन्हित पूर्णांक id;
	अक्षर *endptr;
	पूर्णांक fd;

	अगर (!is_prefix(*argv[0], "id")) अणु
		p_err("expected 'id', got: '%s'?", **argv);
		वापस -1;
	पूर्ण
	NEXT_ARGP();

	id = म_से_अदीर्घ(**argv, &endptr, 0);
	अगर (*endptr) अणु
		p_err("can't parse %s as ID", **argv);
		वापस -1;
	पूर्ण
	NEXT_ARGP();

	fd = bpf_btf_get_fd_by_id(id);
	अगर (fd < 0)
		p_err("can't get BTF object by id (%u): %s",
		      id, म_त्रुटि(त्रुटि_सं));

	वापस fd;
पूर्ण

अटल व्योम delete_btf_table(काष्ठा btf_attach_table *tab)
अणु
	काष्ठा btf_attach_poपूर्णांक *obj;
	काष्ठा hlist_node *पंचांगp;

	अचिन्हित पूर्णांक bkt;

	hash_क्रम_each_safe(tab->table, bkt, पंचांगp, obj, hash) अणु
		hash_del(&obj->hash);
		मुक्त(obj);
	पूर्ण
पूर्ण

अटल पूर्णांक
build_btf_type_table(काष्ठा btf_attach_table *tab, क्रमागत bpf_obj_type type,
		     व्योम *info, __u32 *len)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		[BPF_OBJ_UNKNOWN]	= "unknown",
		[BPF_OBJ_PROG]		= "prog",
		[BPF_OBJ_MAP]		= "map",
	पूर्ण;
	काष्ठा btf_attach_poपूर्णांक *obj_node;
	__u32 btf_id, id = 0;
	पूर्णांक err;
	पूर्णांक fd;

	जबतक (true) अणु
		चयन (type) अणु
		हाल BPF_OBJ_PROG:
			err = bpf_prog_get_next_id(id, &id);
			अवरोध;
		हाल BPF_OBJ_MAP:
			err = bpf_map_get_next_id(id, &id);
			अवरोध;
		शेष:
			err = -1;
			p_err("unexpected object type: %d", type);
			जाओ err_मुक्त;
		पूर्ण
		अगर (err) अणु
			अगर (त्रुटि_सं == ENOENT) अणु
				err = 0;
				अवरोध;
			पूर्ण
			p_err("can't get next %s: %s%s", names[type],
			      म_त्रुटि(त्रुटि_सं),
			      त्रुटि_सं == EINVAL ? " -- kernel too old?" : "");
			जाओ err_मुक्त;
		पूर्ण

		चयन (type) अणु
		हाल BPF_OBJ_PROG:
			fd = bpf_prog_get_fd_by_id(id);
			अवरोध;
		हाल BPF_OBJ_MAP:
			fd = bpf_map_get_fd_by_id(id);
			अवरोध;
		शेष:
			err = -1;
			p_err("unexpected object type: %d", type);
			जाओ err_मुक्त;
		पूर्ण
		अगर (fd < 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				जारी;
			p_err("can't get %s by id (%u): %s", names[type], id,
			      म_त्रुटि(त्रुटि_सं));
			err = -1;
			जाओ err_मुक्त;
		पूर्ण

		स_रखो(info, 0, *len);
		err = bpf_obj_get_info_by_fd(fd, info, len);
		बंद(fd);
		अगर (err) अणु
			p_err("can't get %s info: %s", names[type],
			      म_त्रुटि(त्रुटि_सं));
			जाओ err_मुक्त;
		पूर्ण

		चयन (type) अणु
		हाल BPF_OBJ_PROG:
			btf_id = ((काष्ठा bpf_prog_info *)info)->btf_id;
			अवरोध;
		हाल BPF_OBJ_MAP:
			btf_id = ((काष्ठा bpf_map_info *)info)->btf_id;
			अवरोध;
		शेष:
			err = -1;
			p_err("unexpected object type: %d", type);
			जाओ err_मुक्त;
		पूर्ण
		अगर (!btf_id)
			जारी;

		obj_node = सुस्मृति(1, माप(*obj_node));
		अगर (!obj_node) अणु
			p_err("failed to allocate memory: %s", म_त्रुटि(त्रुटि_सं));
			err = -ENOMEM;
			जाओ err_मुक्त;
		पूर्ण

		obj_node->obj_id = id;
		obj_node->btf_id = btf_id;
		hash_add(tab->table, &obj_node->hash, obj_node->btf_id);
	पूर्ण

	वापस 0;

err_मुक्त:
	delete_btf_table(tab);
	वापस err;
पूर्ण

अटल पूर्णांक
build_btf_tables(काष्ठा btf_attach_table *btf_prog_table,
		 काष्ठा btf_attach_table *btf_map_table)
अणु
	काष्ठा bpf_prog_info prog_info;
	__u32 prog_len = माप(prog_info);
	काष्ठा bpf_map_info map_info;
	__u32 map_len = माप(map_info);
	पूर्णांक err = 0;

	err = build_btf_type_table(btf_prog_table, BPF_OBJ_PROG, &prog_info,
				   &prog_len);
	अगर (err)
		वापस err;

	err = build_btf_type_table(btf_map_table, BPF_OBJ_MAP, &map_info,
				   &map_len);
	अगर (err) अणु
		delete_btf_table(btf_prog_table);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
show_btf_plain(काष्ठा bpf_btf_info *info, पूर्णांक fd,
	       काष्ठा btf_attach_table *btf_prog_table,
	       काष्ठा btf_attach_table *btf_map_table)
अणु
	काष्ठा btf_attach_poपूर्णांक *obj;
	स्थिर अक्षर *name = u64_to_ptr(info->name);
	पूर्णांक n;

	म_लिखो("%u: ", info->id);
	अगर (info->kernel_btf)
		म_लिखो("name [%s]  ", name);
	अन्यथा अगर (name && name[0])
		म_लिखो("name %s  ", name);
	अन्यथा
		म_लिखो("name <anon>  ");
	म_लिखो("size %uB", info->btf_size);

	n = 0;
	hash_क्रम_each_possible(btf_prog_table->table, obj, hash, info->id) अणु
		अगर (obj->btf_id == info->id)
			म_लिखो("%s%u", n++ == 0 ? "  prog_ids " : ",",
			       obj->obj_id);
	पूर्ण

	n = 0;
	hash_क्रम_each_possible(btf_map_table->table, obj, hash, info->id) अणु
		अगर (obj->btf_id == info->id)
			म_लिखो("%s%u", n++ == 0 ? "  map_ids " : ",",
			       obj->obj_id);
	पूर्ण
	emit_obj_refs_plain(&refs_table, info->id, "\n\tpids ");

	म_लिखो("\n");
पूर्ण

अटल व्योम
show_btf_json(काष्ठा bpf_btf_info *info, पूर्णांक fd,
	      काष्ठा btf_attach_table *btf_prog_table,
	      काष्ठा btf_attach_table *btf_map_table)
अणु
	काष्ठा btf_attach_poपूर्णांक *obj;
	स्थिर अक्षर *name = u64_to_ptr(info->name);

	jsonw_start_object(json_wtr);	/* btf object */
	jsonw_uपूर्णांक_field(json_wtr, "id", info->id);
	jsonw_uपूर्णांक_field(json_wtr, "size", info->btf_size);

	jsonw_name(json_wtr, "prog_ids");
	jsonw_start_array(json_wtr);	/* prog_ids */
	hash_क्रम_each_possible(btf_prog_table->table, obj, hash,
			       info->id) अणु
		अगर (obj->btf_id == info->id)
			jsonw_uपूर्णांक(json_wtr, obj->obj_id);
	पूर्ण
	jsonw_end_array(json_wtr);	/* prog_ids */

	jsonw_name(json_wtr, "map_ids");
	jsonw_start_array(json_wtr);	/* map_ids */
	hash_क्रम_each_possible(btf_map_table->table, obj, hash,
			       info->id) अणु
		अगर (obj->btf_id == info->id)
			jsonw_uपूर्णांक(json_wtr, obj->obj_id);
	पूर्ण
	jsonw_end_array(json_wtr);	/* map_ids */

	emit_obj_refs_json(&refs_table, info->id, json_wtr); /* pids */

	jsonw_bool_field(json_wtr, "kernel", info->kernel_btf);

	अगर (name && name[0])
		jsonw_string_field(json_wtr, "name", name);

	jsonw_end_object(json_wtr);	/* btf object */
पूर्ण

अटल पूर्णांक
show_btf(पूर्णांक fd, काष्ठा btf_attach_table *btf_prog_table,
	 काष्ठा btf_attach_table *btf_map_table)
अणु
	काष्ठा bpf_btf_info info;
	__u32 len = माप(info);
	अक्षर name[64];
	पूर्णांक err;

	स_रखो(&info, 0, माप(info));
	err = bpf_obj_get_info_by_fd(fd, &info, &len);
	अगर (err) अणु
		p_err("can't get BTF object info: %s", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण
	/* अगर kernel support emitting BTF object name, pass name poपूर्णांकer */
	अगर (info.name_len) अणु
		स_रखो(&info, 0, माप(info));
		info.name_len = माप(name);
		info.name = ptr_to_u64(name);
		len = माप(info);

		err = bpf_obj_get_info_by_fd(fd, &info, &len);
		अगर (err) अणु
			p_err("can't get BTF object info: %s", म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (json_output)
		show_btf_json(&info, fd, btf_prog_table, btf_map_table);
	अन्यथा
		show_btf_plain(&info, fd, btf_prog_table, btf_map_table);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_show(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा btf_attach_table btf_prog_table;
	काष्ठा btf_attach_table btf_map_table;
	पूर्णांक err, fd = -1;
	__u32 id = 0;

	अगर (argc == 2) अणु
		fd = btf_parse_fd(&argc, &argv);
		अगर (fd < 0)
			वापस -1;
	पूर्ण

	अगर (argc) अणु
		अगर (fd >= 0)
			बंद(fd);
		वापस BAD_ARG();
	पूर्ण

	hash_init(btf_prog_table.table);
	hash_init(btf_map_table.table);
	err = build_btf_tables(&btf_prog_table, &btf_map_table);
	अगर (err) अणु
		अगर (fd >= 0)
			बंद(fd);
		वापस err;
	पूर्ण
	build_obj_refs_table(&refs_table, BPF_OBJ_BTF);

	अगर (fd >= 0) अणु
		err = show_btf(fd, &btf_prog_table, &btf_map_table);
		बंद(fd);
		जाओ निकास_मुक्त;
	पूर्ण

	अगर (json_output)
		jsonw_start_array(json_wtr);	/* root array */

	जबतक (true) अणु
		err = bpf_btf_get_next_id(id, &id);
		अगर (err) अणु
			अगर (त्रुटि_सं == ENOENT) अणु
				err = 0;
				अवरोध;
			पूर्ण
			p_err("can't get next BTF object: %s%s",
			      म_त्रुटि(त्रुटि_सं),
			      त्रुटि_सं == EINVAL ? " -- kernel too old?" : "");
			err = -1;
			अवरोध;
		पूर्ण

		fd = bpf_btf_get_fd_by_id(id);
		अगर (fd < 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				जारी;
			p_err("can't get BTF object by id (%u): %s",
			      id, म_त्रुटि(त्रुटि_सं));
			err = -1;
			अवरोध;
		पूर्ण

		err = show_btf(fd, &btf_prog_table, &btf_map_table);
		बंद(fd);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (json_output)
		jsonw_end_array(json_wtr);	/* root array */

निकास_मुक्त:
	delete_btf_table(&btf_prog_table);
	delete_btf_table(&btf_map_table);
	delete_obj_refs_table(&refs_table);

	वापस err;
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (json_output) अणु
		jsonw_null(json_wtr);
		वापस 0;
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s { show | list } [id BTF_ID]\n"
		"       %1$s %2$s dump BTF_SRC [format FORMAT]\n"
		"       %1$s %2$s help\n"
		"\n"
		"       BTF_SRC := { id BTF_ID | prog PROG | map MAP [{key | value | kv | all}] | file FILE }\n"
		"       FORMAT  := { raw | c }\n"
		"       " HELP_SPEC_MAP "\n"
		"       " HELP_SPEC_PROGRAM "\n"
		"       " HELP_SPEC_OPTIONS "\n"
		"",
		bin_name, "btf");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "show",	करो_show पूर्ण,
	अणु "list",	करो_show पूर्ण,
	अणु "help",	करो_help पूर्ण,
	अणु "dump",	करो_dump पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_btf(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
