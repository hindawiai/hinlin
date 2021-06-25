<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Facebook */

#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/err.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <bpf/btf.h>

#समावेश "json_writer.h"
#समावेश "main.h"

#घोषणा MAX_OBJ_NAME_LEN 64

अटल व्योम sanitize_identअगरier(अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; name[i]; i++)
		अगर (!है_अक्षर_अंक(name[i]) && name[i] != '_')
			name[i] = '_';
पूर्ण

अटल bool str_has_suffix(स्थिर अक्षर *str, स्थिर अक्षर *suffix)
अणु
	माप_प्रकार i, n1 = म_माप(str), n2 = म_माप(suffix);

	अगर (n1 < n2)
		वापस false;

	क्रम (i = 0; i < n2; i++) अणु
		अगर (str[n1 - i - 1] != suffix[n2 - i - 1])
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम get_obj_name(अक्षर *name, स्थिर अक्षर *file)
अणु
	/* Using basename() GNU version which करोesn't modअगरy arg. */
	म_नकलन(name, basename(file), MAX_OBJ_NAME_LEN - 1);
	name[MAX_OBJ_NAME_LEN - 1] = '\0';
	अगर (str_has_suffix(name, ".o"))
		name[म_माप(name) - 2] = '\0';
	sanitize_identअगरier(name);
पूर्ण

अटल व्योम get_header_guard(अक्षर *guard, स्थिर अक्षर *obj_name)
अणु
	पूर्णांक i;

	प्र_लिखो(guard, "__%s_SKEL_H__", obj_name);
	क्रम (i = 0; guard[i]; i++)
		guard[i] = बड़े(guard[i]);
पूर्ण

अटल स्थिर अक्षर *get_map_ident(स्थिर काष्ठा bpf_map *map)
अणु
	स्थिर अक्षर *name = bpf_map__name(map);

	अगर (!bpf_map__is_पूर्णांकernal(map))
		वापस name;

	अगर (str_has_suffix(name, ".data"))
		वापस "data";
	अन्यथा अगर (str_has_suffix(name, ".rodata"))
		वापस "rodata";
	अन्यथा अगर (str_has_suffix(name, ".bss"))
		वापस "bss";
	अन्यथा अगर (str_has_suffix(name, ".kconfig"))
		वापस "kconfig";
	अन्यथा
		वापस शून्य;
पूर्ण

अटल व्योम codegen_btf_dump_म_लिखो(व्योम *ctx, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	भ_लिखो(fmt, args);
पूर्ण

अटल पूर्णांक codegen_datasec_def(काष्ठा bpf_object *obj,
			       काष्ठा btf *btf,
			       काष्ठा btf_dump *d,
			       स्थिर काष्ठा btf_type *sec,
			       स्थिर अक्षर *obj_name)
अणु
	स्थिर अक्षर *sec_name = btf__name_by_offset(btf, sec->name_off);
	स्थिर काष्ठा btf_var_secinfo *sec_var = btf_var_secinfos(sec);
	पूर्णांक i, err, off = 0, pad_cnt = 0, vlen = btf_vlen(sec);
	स्थिर अक्षर *sec_ident;
	अक्षर var_ident[256];
	bool strip_mods = false;

	अगर (म_भेद(sec_name, ".data") == 0) अणु
		sec_ident = "data";
	पूर्ण अन्यथा अगर (म_भेद(sec_name, ".bss") == 0) अणु
		sec_ident = "bss";
	पूर्ण अन्यथा अगर (म_भेद(sec_name, ".rodata") == 0) अणु
		sec_ident = "rodata";
		strip_mods = true;
	पूर्ण अन्यथा अगर (म_भेद(sec_name, ".kconfig") == 0) अणु
		sec_ident = "kconfig";
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	म_लिखो("	struct %s__%s {\n", obj_name, sec_ident);
	क्रम (i = 0; i < vlen; i++, sec_var++) अणु
		स्थिर काष्ठा btf_type *var = btf__type_by_id(btf, sec_var->type);
		स्थिर अक्षर *var_name = btf__name_by_offset(btf, var->name_off);
		DECLARE_LIBBPF_OPTS(btf_dump_emit_type_decl_opts, opts,
			.field_name = var_ident,
			.indent_level = 2,
			.strip_mods = strip_mods,
		);
		पूर्णांक need_off = sec_var->offset, align_off, align;
		__u32 var_type_id = var->type;

		अगर (off > need_off) अणु
			p_err("Something is wrong for %s's variable #%d: need offset %d, already at %d.\n",
			      sec_name, i, need_off, off);
			वापस -EINVAL;
		पूर्ण

		align = btf__align_of(btf, var->type);
		अगर (align <= 0) अणु
			p_err("Failed to determine alignment of variable '%s': %d",
			      var_name, align);
			वापस -EINVAL;
		पूर्ण
		/* Assume 32-bit architectures when generating data section
		 * काष्ठा memory layout. Given bpftool can't know which target
		 * host architecture it's emitting skeleton क्रम, we need to be
		 * conservative and assume 32-bit one to ensure enough padding
		 * bytes are generated क्रम poपूर्णांकer and दीर्घ types. This will
		 * still work correctly क्रम 64-bit architectures, because in
		 * the worst हाल we'll generate unnecessary padding field,
		 * which on 64-bit architectures is not strictly necessary and
		 * would be handled by natural 8-byte alignment. But it still
		 * will be a correct memory layout, based on recorded offsets
		 * in BTF.
		 */
		अगर (align > 4)
			align = 4;

		align_off = (off + align - 1) / align * align;
		अगर (align_off != need_off) अणु
			म_लिखो("\t\tchar __pad%d[%d];\n",
			       pad_cnt, need_off - off);
			pad_cnt++;
		पूर्ण

		/* sanitize variable name, e.g., क्रम अटल vars inside
		 * a function, it's name is '<function name>.<variable name>',
		 * which we'll turn into a '<function name>_<variable name>'
		 */
		var_ident[0] = '\0';
		म_जोड़न(var_ident, var_name, माप(var_ident) - 1);
		sanitize_identअगरier(var_ident);

		म_लिखो("\t\t");
		err = btf_dump__emit_type_decl(d, var_type_id, &opts);
		अगर (err)
			वापस err;
		म_लिखो(";\n");

		off = sec_var->offset + sec_var->size;
	पूर्ण
	म_लिखो("	} *%s;\n", sec_ident);
	वापस 0;
पूर्ण

अटल पूर्णांक codegen_datasecs(काष्ठा bpf_object *obj, स्थिर अक्षर *obj_name)
अणु
	काष्ठा btf *btf = bpf_object__btf(obj);
	पूर्णांक n = btf__get_nr_types(btf);
	काष्ठा btf_dump *d;
	पूर्णांक i, err = 0;

	d = btf_dump__new(btf, शून्य, शून्य, codegen_btf_dump_म_लिखो);
	अगर (IS_ERR(d))
		वापस PTR_ERR(d);

	क्रम (i = 1; i <= n; i++) अणु
		स्थिर काष्ठा btf_type *t = btf__type_by_id(btf, i);

		अगर (!btf_is_datasec(t))
			जारी;

		err = codegen_datasec_def(obj, btf, d, t, obj_name);
		अगर (err)
			जाओ out;
	पूर्ण
out:
	btf_dump__मुक्त(d);
	वापस err;
पूर्ण

अटल व्योम codegen(स्थिर अक्षर *ढाँचा, ...)
अणु
	स्थिर अक्षर *src, *end;
	पूर्णांक skip_tअसल = 0, n;
	अक्षर *s, *dst;
	बहु_सूची args;
	अक्षर c;

	n = म_माप(ढाँचा);
	s = दो_स्मृति(n + 1);
	अगर (!s)
		निकास(-1);
	src = ढाँचा;
	dst = s;

	/* find out "baseline" indentation to skip */
	जबतक ((c = *src++)) अणु
		अगर (c == '\t') अणु
			skip_tअसल++;
		पूर्ण अन्यथा अगर (c == '\n') अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			p_err("unrecognized character at pos %td in template '%s'",
			      src - ढाँचा - 1, ढाँचा);
			मुक्त(s);
			निकास(-1);
		पूर्ण
	पूर्ण

	जबतक (*src) अणु
		/* skip baseline indentation tअसल */
		क्रम (n = skip_tअसल; n > 0; n--, src++) अणु
			अगर (*src != '\t') अणु
				p_err("not enough tabs at pos %td in template '%s'",
				      src - ढाँचा - 1, ढाँचा);
				मुक्त(s);
				निकास(-1);
			पूर्ण
		पूर्ण
		/* trim trailing whitespace */
		end = म_अक्षरnul(src, '\n');
		क्रम (n = end - src; n > 0 && है_खाली(src[n - 1]); n--)
			;
		स_नकल(dst, src, n);
		dst += n;
		अगर (*end)
			*dst++ = '\n';
		src = *end ? end + 1 : end;
	पूर्ण
	*dst++ = '\0';

	/* prपूर्णांक out using adjusted ढाँचा */
	बहु_शुरू(args, ढाँचा);
	n = भ_लिखो(s, args);
	बहु_पूर्ण(args);

	मुक्त(s);
पूर्ण

अटल पूर्णांक करो_skeleton(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर header_guard[MAX_OBJ_NAME_LEN + माप("__SKEL_H__")];
	माप_प्रकार i, map_cnt = 0, prog_cnt = 0, file_sz, mmap_sz;
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, opts);
	अक्षर obj_name[MAX_OBJ_NAME_LEN] = "", *obj_data;
	काष्ठा bpf_object *obj = शून्य;
	स्थिर अक्षर *file, *ident;
	काष्ठा bpf_program *prog;
	पूर्णांक fd, len, err = -1;
	काष्ठा bpf_map *map;
	काष्ठा btf *btf;
	काष्ठा stat st;

	अगर (!REQ_ARGS(1)) अणु
		usage();
		वापस -1;
	पूर्ण
	file = GET_ARG();

	जबतक (argc) अणु
		अगर (!REQ_ARGS(2))
			वापस -1;

		अगर (is_prefix(*argv, "name")) अणु
			NEXT_ARG();

			अगर (obj_name[0] != '\0') अणु
				p_err("object name already specified");
				वापस -1;
			पूर्ण

			म_नकलन(obj_name, *argv, MAX_OBJ_NAME_LEN - 1);
			obj_name[MAX_OBJ_NAME_LEN - 1] = '\0';
		पूर्ण अन्यथा अणु
			p_err("unknown arg %s", *argv);
			वापस -1;
		पूर्ण

		NEXT_ARG();
	पूर्ण

	अगर (argc) अणु
		p_err("extra unknown arguments");
		वापस -1;
	पूर्ण

	अगर (stat(file, &st)) अणु
		p_err("failed to stat() %s: %s", file, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण
	file_sz = st.st_size;
	mmap_sz = roundup(file_sz, sysconf(_SC_PAGE_SIZE));
	fd = खोलो(file, O_RDONLY);
	अगर (fd < 0) अणु
		p_err("failed to open() %s: %s", file, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण
	obj_data = mmap(शून्य, mmap_sz, PROT_READ, MAP_PRIVATE, fd, 0);
	अगर (obj_data == MAP_FAILED) अणु
		obj_data = शून्य;
		p_err("failed to mmap() %s: %s", file, म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण
	अगर (obj_name[0] == '\0')
		get_obj_name(obj_name, file);
	opts.object_name = obj_name;
	obj = bpf_object__खोलो_mem(obj_data, file_sz, &opts);
	अगर (IS_ERR(obj)) अणु
		अक्षर err_buf[256];

		libbpf_म_त्रुटि(PTR_ERR(obj), err_buf, माप(err_buf));
		p_err("failed to open BPF object file: %s", err_buf);
		obj = शून्य;
		जाओ out;
	पूर्ण

	bpf_object__क्रम_each_map(map, obj) अणु
		ident = get_map_ident(map);
		अगर (!ident) अणु
			p_err("ignoring unrecognized internal map '%s'...",
			      bpf_map__name(map));
			जारी;
		पूर्ण
		map_cnt++;
	पूर्ण
	bpf_object__क्रम_each_program(prog, obj) अणु
		prog_cnt++;
	पूर्ण

	get_header_guard(header_guard, obj_name);
	codegen("\
		\न\
		/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */   \न\
									    \न\
		/* THIS खाता IS AUTOGENERATED! */			    \न\
		#अगर_अघोषित %2$s						    \न\
		#घोषणा %2$s						    \न\
									    \न\
		#समावेश <मानककोष.स>					    \न\
		#समावेश <bpf/libbpf.h>					    \न\
									    \न\
		काष्ठा %1$s अणु						    \न\
			काष्ठा bpf_object_skeleton *skeleton;		    \न\
			काष्ठा bpf_object *obj;				    \न\
		",
		obj_name, header_guard
	);

	अगर (map_cnt) अणु
		म_लिखो("\tstruct {\n");
		bpf_object__क्रम_each_map(map, obj) अणु
			ident = get_map_ident(map);
			अगर (!ident)
				जारी;
			म_लिखो("\t\tstruct bpf_map *%s;\n", ident);
		पूर्ण
		म_लिखो("\t} maps;\n");
	पूर्ण

	अगर (prog_cnt) अणु
		म_लिखो("\tstruct {\n");
		bpf_object__क्रम_each_program(prog, obj) अणु
			म_लिखो("\t\tstruct bpf_program *%s;\n",
			       bpf_program__name(prog));
		पूर्ण
		म_लिखो("\t} progs;\n");
		म_लिखो("\tstruct {\n");
		bpf_object__क्रम_each_program(prog, obj) अणु
			म_लिखो("\t\tstruct bpf_link *%s;\n",
			       bpf_program__name(prog));
		पूर्ण
		म_लिखो("\t} links;\n");
	पूर्ण

	btf = bpf_object__btf(obj);
	अगर (btf) अणु
		err = codegen_datasecs(obj, obj_name);
		अगर (err)
			जाओ out;
	पूर्ण

	codegen("\
		\न\
		पूर्ण;							    \न\
									    \न\
		अटल व्योम						    \न\
		%1$s__destroy(काष्ठा %1$s *obj)				    \न\
		अणु							    \न\
			अगर (!obj)					    \न\
				वापस;					    \न\
			अगर (obj->skeleton)				    \न\
				bpf_object__destroy_skeleton(obj->skeleton);\न\
			मुक्त(obj);					    \न\
		पूर्ण							    \न\
									    \न\
		अटल अंतरभूत पूर्णांक					    \न\
		%1$s__create_skeleton(काष्ठा %1$s *obj);		    \न\
									    \न\
		अटल अंतरभूत काष्ठा %1$s *				    \न\
		%1$s__खोलो_opts(स्थिर काष्ठा bpf_object_खोलो_opts *opts)    \न\
		अणु							    \न\
			काष्ठा %1$s *obj;				    \न\
									    \न\
			obj = (काष्ठा %1$s *)सुस्मृति(1, माप(*obj));	    \न\
			अगर (!obj)					    \न\
				वापस शून्य;				    \न\
			अगर (%1$s__create_skeleton(obj))			    \न\
				जाओ err;				    \न\
			अगर (bpf_object__खोलो_skeleton(obj->skeleton, opts)) \न\
				जाओ err;				    \न\
									    \न\
			वापस obj;					    \न\
		err:							    \न\
			%1$s__destroy(obj);				    \न\
			वापस शून्य;					    \न\
		पूर्ण							    \न\
									    \न\
		अटल अंतरभूत काष्ठा %1$s *				    \न\
		%1$s__खोलो(व्योम)					    \न\
		अणु							    \न\
			वापस %1$s__खोलो_opts(शून्य);			    \न\
		पूर्ण							    \न\
									    \न\
		अटल अंतरभूत पूर्णांक					    \न\
		%1$s__load(काष्ठा %1$s *obj)				    \न\
		अणु							    \न\
			वापस bpf_object__load_skeleton(obj->skeleton);    \न\
		पूर्ण							    \न\
									    \न\
		अटल अंतरभूत काष्ठा %1$s *				    \न\
		%1$s__खोलो_and_load(व्योम)				    \न\
		अणु							    \न\
			काष्ठा %1$s *obj;				    \न\
									    \न\
			obj = %1$s__खोलो();				    \न\
			अगर (!obj)					    \न\
				वापस शून्य;				    \न\
			अगर (%1$s__load(obj)) अणु				    \न\
				%1$s__destroy(obj);			    \न\
				वापस शून्य;				    \न\
			पूर्ण						    \न\
			वापस obj;					    \न\
		पूर्ण							    \न\
									    \न\
		अटल अंतरभूत पूर्णांक					    \न\
		%1$s__attach(काष्ठा %1$s *obj)				    \न\
		अणु							    \न\
			वापस bpf_object__attach_skeleton(obj->skeleton);  \न\
		पूर्ण							    \न\
									    \न\
		अटल अंतरभूत व्योम					    \न\
		%1$s__detach(काष्ठा %1$s *obj)				    \न\
		अणु							    \न\
			वापस bpf_object__detach_skeleton(obj->skeleton);  \न\
		पूर्ण							    \न\
		",
		obj_name
	);

	codegen("\
		\न\
									    \न\
		अटल अंतरभूत पूर्णांक					    \न\
		%1$s__create_skeleton(काष्ठा %1$s *obj)			    \न\
		अणु							    \न\
			काष्ठा bpf_object_skeleton *s;			    \न\
									    \न\
			s = (काष्ठा bpf_object_skeleton *)सुस्मृति(1, माप(*s));\न\
			अगर (!s)						    \न\
				वापस -1;				    \न\
			obj->skeleton = s;				    \न\
									    \न\
			s->sz = माप(*s);				    \न\
			s->name = \"%1$s\";				    \न\
			s->obj = &obj->obj;				    \न\
		",
		obj_name
	);
	अगर (map_cnt) अणु
		codegen("\
			\न\
									    \न\
				/* maps */				    \न\
				s->map_cnt = %zu;			    \न\
				s->map_skel_sz = माप(*s->maps);	    \न\
				s->maps = (काष्ठा bpf_map_skeleton *)सुस्मृति(s->map_cnt, s->map_skel_sz);\न\
				अगर (!s->maps)				    \न\
					जाओ err;			    \न\
			",
			map_cnt
		);
		i = 0;
		bpf_object__क्रम_each_map(map, obj) अणु
			ident = get_map_ident(map);

			अगर (!ident)
				जारी;

			codegen("\
				\न\
									    \न\
					s->maps[%zu].name = \"%s\";	    \न\
					s->maps[%zu].map = &obj->maps.%s;   \न\
				",
				i, bpf_map__name(map), i, ident);
			/* memory-mapped पूर्णांकernal maps */
			अगर (bpf_map__is_पूर्णांकernal(map) &&
			    (bpf_map__def(map)->map_flags & BPF_F_MMAPABLE)) अणु
				म_लिखो("\ts->maps[%zu].mmaped = (void **)&obj->%s;\n",
				       i, ident);
			पूर्ण
			i++;
		पूर्ण
	पूर्ण
	अगर (prog_cnt) अणु
		codegen("\
			\न\
									    \न\
				/* programs */				    \न\
				s->prog_cnt = %zu;			    \न\
				s->prog_skel_sz = माप(*s->progs);	    \न\
				s->progs = (काष्ठा bpf_prog_skeleton *)सुस्मृति(s->prog_cnt, s->prog_skel_sz);\न\
				अगर (!s->progs)				    \न\
					जाओ err;			    \न\
			",
			prog_cnt
		);
		i = 0;
		bpf_object__क्रम_each_program(prog, obj) अणु
			codegen("\
				\न\
									    \न\
					s->progs[%1$zu].name = \"%2$s\";    \न\
					s->progs[%1$zu].prog = &obj->progs.%2$s;\न\
					s->progs[%1$zu].link = &obj->links.%2$s;\न\
				",
				i, bpf_program__name(prog));
			i++;
		पूर्ण
	पूर्ण
	codegen("\
		\न\
									    \न\
			s->data_sz = %d;				    \न\
			s->data = (व्योम *)\"\\				    \न\
		",
		file_sz);

	/* embed contents of BPF object file */
	क्रम (i = 0, len = 0; i < file_sz; i++) अणु
		पूर्णांक w = obj_data[i] ? 4 : 2;

		len += w;
		अगर (len > 78) अणु
			म_लिखो("\\\n");
			len = w;
		पूर्ण
		अगर (!obj_data[i])
			म_लिखो("\\0");
		अन्यथा
			म_लिखो("\\x%02x", (अचिन्हित अक्षर)obj_data[i]);
	पूर्ण

	codegen("\
		\न\
		\";							    \न\
									    \न\
			वापस 0;					    \न\
		err:							    \न\
			bpf_object__destroy_skeleton(s);		    \न\
			वापस -1;					    \न\
		पूर्ण							    \न\
									    \न\
		#पूर्ण_अगर /* %s */						    \न\
		",
		header_guard);
	err = 0;
out:
	bpf_object__बंद(obj);
	अगर (obj_data)
		munmap(obj_data, mmap_sz);
	बंद(fd);
	वापस err;
पूर्ण

अटल पूर्णांक करो_object(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_linker *linker;
	स्थिर अक्षर *output_file, *file;
	पूर्णांक err = 0;

	अगर (!REQ_ARGS(2)) अणु
		usage();
		वापस -1;
	पूर्ण

	output_file = GET_ARG();

	linker = bpf_linker__new(output_file, शून्य);
	अगर (!linker) अणु
		p_err("failed to create BPF linker instance");
		वापस -1;
	पूर्ण

	जबतक (argc) अणु
		file = GET_ARG();

		err = bpf_linker__add_file(linker, file);
		अगर (err) अणु
			p_err("failed to link '%s': %s (%d)", file, म_त्रुटि(err), err);
			जाओ out;
		पूर्ण
	पूर्ण

	err = bpf_linker__finalize(linker);
	अगर (err) अणु
		p_err("failed to finalize ELF file: %s (%d)", म_त्रुटि(err), err);
		जाओ out;
	पूर्ण

	err = 0;
out:
	bpf_linker__मुक्त(linker);
	वापस err;
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (json_output) अणु
		jsonw_null(json_wtr);
		वापस 0;
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s object OUTPUT_FILE INPUT_FILE [INPUT_FILE...]\n"
		"       %1$s %2$s skeleton FILE [name OBJECT_NAME]\n"
		"       %1$s %2$s help\n"
		"\n"
		"       " HELP_SPEC_OPTIONS "\n"
		"",
		bin_name, "gen");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "object",	करो_object पूर्ण,
	अणु "skeleton",	करो_skeleton पूर्ण,
	अणु "help",	करो_help पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_gen(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
