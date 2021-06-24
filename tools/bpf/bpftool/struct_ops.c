<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2020 Facebook */

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>

#समावेश <linux/err.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/btf.h>
#समावेश <bpf/libbpf.h>

#समावेश "json_writer.h"
#समावेश "main.h"

#घोषणा STRUCT_OPS_VALUE_PREFIX "bpf_struct_ops_"

अटल स्थिर काष्ठा btf_type *map_info_type;
अटल __u32 map_info_alloc_len;
अटल काष्ठा btf *btf_vmlinux;
अटल __s32 map_info_type_id;

काष्ठा res अणु
	अचिन्हित पूर्णांक nr_maps;
	अचिन्हित पूर्णांक nr_errs;
पूर्ण;

अटल स्थिर काष्ठा btf *get_btf_vmlinux(व्योम)
अणु
	अगर (btf_vmlinux)
		वापस btf_vmlinux;

	btf_vmlinux = libbpf_find_kernel_btf();
	अगर (IS_ERR(btf_vmlinux))
		p_err("struct_ops requires kernel CONFIG_DEBUG_INFO_BTF=y");

	वापस btf_vmlinux;
पूर्ण

अटल स्थिर अक्षर *get_kern_काष्ठा_ops_name(स्थिर काष्ठा bpf_map_info *info)
अणु
	स्थिर काष्ठा btf *kern_btf;
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *st_ops_name;

	kern_btf = get_btf_vmlinux();
	अगर (IS_ERR(kern_btf))
		वापस "<btf_vmlinux_not_found>";

	t = btf__type_by_id(kern_btf, info->btf_vmlinux_value_type_id);
	st_ops_name = btf__name_by_offset(kern_btf, t->name_off);
	st_ops_name += म_माप(STRUCT_OPS_VALUE_PREFIX);

	वापस st_ops_name;
पूर्ण

अटल __s32 get_map_info_type_id(व्योम)
अणु
	स्थिर काष्ठा btf *kern_btf;

	अगर (map_info_type_id)
		वापस map_info_type_id;

	kern_btf = get_btf_vmlinux();
	अगर (IS_ERR(kern_btf)) अणु
		map_info_type_id = PTR_ERR(kern_btf);
		वापस map_info_type_id;
	पूर्ण

	map_info_type_id = btf__find_by_name_kind(kern_btf, "bpf_map_info",
						  BTF_KIND_STRUCT);
	अगर (map_info_type_id < 0) अणु
		p_err("can't find bpf_map_info from btf_vmlinux");
		वापस map_info_type_id;
	पूर्ण
	map_info_type = btf__type_by_id(kern_btf, map_info_type_id);

	/* Ensure map_info_alloc() has at least what the bpftool needs */
	map_info_alloc_len = map_info_type->size;
	अगर (map_info_alloc_len < माप(काष्ठा bpf_map_info))
		map_info_alloc_len = माप(काष्ठा bpf_map_info);

	वापस map_info_type_id;
पूर्ण

/* If the subcmd needs to prपूर्णांक out the bpf_map_info,
 * it should always call map_info_alloc to allocate
 * a bpf_map_info object instead of allocating it
 * on the stack.
 *
 * map_info_alloc() will take the running kernel's btf
 * पूर्णांकo account.  i.e. it will consider the
 * माप(काष्ठा bpf_map_info) of the running kernel.
 *
 * It will enable the "struct_ops" cmd to prपूर्णांक the latest
 * "struct bpf_map_info".
 *
 * [ Recall that "struct_ops" requires the kernel's btf to
 *   be available ]
 */
अटल काष्ठा bpf_map_info *map_info_alloc(__u32 *alloc_len)
अणु
	काष्ठा bpf_map_info *info;

	अगर (get_map_info_type_id() < 0)
		वापस शून्य;

	info = सुस्मृति(1, map_info_alloc_len);
	अगर (!info)
		p_err("mem alloc failed");
	अन्यथा
		*alloc_len = map_info_alloc_len;

	वापस info;
पूर्ण

/* It iterates all काष्ठा_ops maps of the प्रणाली.
 * It वापसs the fd in "*res_fd" and map_info in "*info".
 * In the very first iteration, info->id should be 0.
 * An optional map "*name" filter can be specअगरied.
 * The filter can be made more flexible in the future.
 * e.g. filter by kernel-काष्ठा-ops-name, regex-name, glob-name, ...etc.
 *
 * Return value:
 *     1: A काष्ठा_ops map found.  It is वापसed in "*res_fd" and "*info".
 *	  The caller can जारी to call get_next in the future.
 *     0: No काष्ठा_ops map is वापसed.
 *        All काष्ठा_ops map has been found.
 *    -1: Error and the caller should पात the iteration.
 */
अटल पूर्णांक get_next_काष्ठा_ops_map(स्थिर अक्षर *name, पूर्णांक *res_fd,
				   काष्ठा bpf_map_info *info, __u32 info_len)
अणु
	__u32 id = info->id;
	पूर्णांक err, fd;

	जबतक (true) अणु
		err = bpf_map_get_next_id(id, &id);
		अगर (err) अणु
			अगर (त्रुटि_सं == ENOENT)
				वापस 0;
			p_err("can't get next map: %s", म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण

		fd = bpf_map_get_fd_by_id(id);
		अगर (fd < 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				जारी;
			p_err("can't get map by id (%u): %s",
			      id, म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण

		err = bpf_obj_get_info_by_fd(fd, info, &info_len);
		अगर (err) अणु
			p_err("can't get map info: %s", म_त्रुटि(त्रुटि_सं));
			बंद(fd);
			वापस -1;
		पूर्ण

		अगर (info->type == BPF_MAP_TYPE_STRUCT_OPS &&
		    (!name || !म_भेद(name, info->name))) अणु
			*res_fd = fd;
			वापस 1;
		पूर्ण
		बंद(fd);
	पूर्ण
पूर्ण

अटल पूर्णांक cmd_retval(स्थिर काष्ठा res *res, bool must_have_one_map)
अणु
	अगर (res->nr_errs || (!res->nr_maps && must_have_one_map))
		वापस -1;

	वापस 0;
पूर्ण

/* "data" is the work_func निजी storage */
प्रकार पूर्णांक (*work_func)(पूर्णांक fd, स्थिर काष्ठा bpf_map_info *info, व्योम *data,
			 काष्ठा json_ग_लिखोr *wtr);

/* Find all काष्ठा_ops map in the प्रणाली.
 * Filter out by "name" (अगर specअगरied).
 * Then call "func(fd, info, data, wtr)" on each काष्ठा_ops map found.
 */
अटल काष्ठा res करो_search(स्थिर अक्षर *name, work_func func, व्योम *data,
			    काष्ठा json_ग_लिखोr *wtr)
अणु
	काष्ठा bpf_map_info *info;
	काष्ठा res res = अणुपूर्ण;
	__u32 info_len;
	पूर्णांक fd, err;

	info = map_info_alloc(&info_len);
	अगर (!info) अणु
		res.nr_errs++;
		वापस res;
	पूर्ण

	अगर (wtr)
		jsonw_start_array(wtr);
	जबतक ((err = get_next_काष्ठा_ops_map(name, &fd, info, info_len)) == 1) अणु
		res.nr_maps++;
		err = func(fd, info, data, wtr);
		अगर (err)
			res.nr_errs++;
		बंद(fd);
	पूर्ण
	अगर (wtr)
		jsonw_end_array(wtr);

	अगर (err)
		res.nr_errs++;

	अगर (!wtr && name && !res.nr_errs && !res.nr_maps)
		/* It is not prपूर्णांकing empty [].
		 * Thus, needs to specअगरically say nothing found
		 * क्रम "name" here.
		 */
		p_err("no struct_ops found for %s", name);
	अन्यथा अगर (!wtr && json_output && !res.nr_errs)
		/* The "func()" above is not writing any json (i.e. !wtr
		 * test here).
		 *
		 * However, "-j" is enabled and there is no errs here,
		 * so call json_null() as the current convention of
		 * other cmds.
		 */
		jsonw_null(json_wtr);

	मुक्त(info);
	वापस res;
पूर्ण

अटल काष्ठा res करो_one_id(स्थिर अक्षर *id_str, work_func func, व्योम *data,
			    काष्ठा json_ग_लिखोr *wtr)
अणु
	काष्ठा bpf_map_info *info;
	काष्ठा res res = अणुपूर्ण;
	अचिन्हित दीर्घ id;
	__u32 info_len;
	अक्षर *endptr;
	पूर्णांक fd;

	id = म_से_अदीर्घ(id_str, &endptr, 0);
	अगर (*endptr || !id || id > UINT32_MAX) अणु
		p_err("invalid id %s", id_str);
		res.nr_errs++;
		वापस res;
	पूर्ण

	fd = bpf_map_get_fd_by_id(id);
	अगर (fd == -1) अणु
		p_err("can't get map by id (%lu): %s", id, म_त्रुटि(त्रुटि_सं));
		res.nr_errs++;
		वापस res;
	पूर्ण

	info = map_info_alloc(&info_len);
	अगर (!info) अणु
		res.nr_errs++;
		जाओ करोne;
	पूर्ण

	अगर (bpf_obj_get_info_by_fd(fd, info, &info_len)) अणु
		p_err("can't get map info: %s", म_त्रुटि(त्रुटि_सं));
		res.nr_errs++;
		जाओ करोne;
	पूर्ण

	अगर (info->type != BPF_MAP_TYPE_STRUCT_OPS) अणु
		p_err("%s id %u is not a struct_ops map", info->name, info->id);
		res.nr_errs++;
		जाओ करोne;
	पूर्ण

	res.nr_maps++;

	अगर (func(fd, info, data, wtr))
		res.nr_errs++;
	अन्यथा अगर (!wtr && json_output)
		/* The "func()" above is not writing any json (i.e. !wtr
		 * test here).
		 *
		 * However, "-j" is enabled and there is no errs here,
		 * so call json_null() as the current convention of
		 * other cmds.
		 */
		jsonw_null(json_wtr);

करोne:
	मुक्त(info);
	बंद(fd);

	वापस res;
पूर्ण

अटल काष्ठा res करो_work_on_काष्ठा_ops(स्थिर अक्षर *search_type,
					स्थिर अक्षर *search_term,
					work_func func, व्योम *data,
					काष्ठा json_ग_लिखोr *wtr)
अणु
	अगर (search_type) अणु
		अगर (is_prefix(search_type, "id"))
			वापस करो_one_id(search_term, func, data, wtr);
		अन्यथा अगर (!is_prefix(search_type, "name"))
			usage();
	पूर्ण

	वापस करो_search(search_term, func, data, wtr);
पूर्ण

अटल पूर्णांक __करो_show(पूर्णांक fd, स्थिर काष्ठा bpf_map_info *info, व्योम *data,
		     काष्ठा json_ग_लिखोr *wtr)
अणु
	अगर (wtr) अणु
		jsonw_start_object(wtr);
		jsonw_uपूर्णांक_field(wtr, "id", info->id);
		jsonw_string_field(wtr, "name", info->name);
		jsonw_string_field(wtr, "kernel_struct_ops",
				   get_kern_काष्ठा_ops_name(info));
		jsonw_end_object(wtr);
	पूर्ण अन्यथा अणु
		म_लिखो("%u: %-15s %-32s\n", info->id, info->name,
		       get_kern_काष्ठा_ops_name(info));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_show(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *search_type = शून्य, *search_term = शून्य;
	काष्ठा res res;

	अगर (argc && argc != 2)
		usage();

	अगर (argc == 2) अणु
		search_type = GET_ARG();
		search_term = GET_ARG();
	पूर्ण

	res = करो_work_on_काष्ठा_ops(search_type, search_term, __करो_show,
				    शून्य, json_wtr);

	वापस cmd_retval(&res, !!search_term);
पूर्ण

अटल पूर्णांक __करो_dump(पूर्णांक fd, स्थिर काष्ठा bpf_map_info *info, व्योम *data,
		     काष्ठा json_ग_लिखोr *wtr)
अणु
	काष्ठा btf_dumper *d = (काष्ठा btf_dumper *)data;
	स्थिर काष्ठा btf_type *काष्ठा_ops_type;
	स्थिर काष्ठा btf *kern_btf = d->btf;
	स्थिर अक्षर *काष्ठा_ops_name;
	पूर्णांक zero = 0;
	व्योम *value;

	/* note: d->jw == wtr */

	kern_btf = d->btf;

	/* The kernel supporting BPF_MAP_TYPE_STRUCT_OPS must have
	 * btf_vmlinux_value_type_id.
	 */
	काष्ठा_ops_type = btf__type_by_id(kern_btf,
					  info->btf_vmlinux_value_type_id);
	काष्ठा_ops_name = btf__name_by_offset(kern_btf,
					      काष्ठा_ops_type->name_off);
	value = सुस्मृति(1, info->value_size);
	अगर (!value) अणु
		p_err("mem alloc failed");
		वापस -1;
	पूर्ण

	अगर (bpf_map_lookup_elem(fd, &zero, value)) अणु
		p_err("can't lookup struct_ops map %s id %u",
		      info->name, info->id);
		मुक्त(value);
		वापस -1;
	पूर्ण

	jsonw_start_object(wtr);
	jsonw_name(wtr, "bpf_map_info");
	btf_dumper_type(d, map_info_type_id, (व्योम *)info);
	jsonw_end_object(wtr);

	jsonw_start_object(wtr);
	jsonw_name(wtr, काष्ठा_ops_name);
	btf_dumper_type(d, info->btf_vmlinux_value_type_id, value);
	jsonw_end_object(wtr);

	मुक्त(value);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_dump(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *search_type = शून्य, *search_term = शून्य;
	json_ग_लिखोr_t *wtr = json_wtr;
	स्थिर काष्ठा btf *kern_btf;
	काष्ठा btf_dumper d = अणुपूर्ण;
	काष्ठा res res;

	अगर (argc && argc != 2)
		usage();

	अगर (argc == 2) अणु
		search_type = GET_ARG();
		search_term = GET_ARG();
	पूर्ण

	kern_btf = get_btf_vmlinux();
	अगर (IS_ERR(kern_btf))
		वापस -1;

	अगर (!json_output) अणु
		wtr = jsonw_new(मानक_निकास);
		अगर (!wtr) अणु
			p_err("can't create json writer");
			वापस -1;
		पूर्ण
		jsonw_pretty(wtr, true);
	पूर्ण

	d.btf = kern_btf;
	d.jw = wtr;
	d.is_plain_text = !json_output;
	d.prog_id_as_func_ptr = true;

	res = करो_work_on_काष्ठा_ops(search_type, search_term, __करो_dump, &d,
				    wtr);

	अगर (!json_output)
		jsonw_destroy(&wtr);

	वापस cmd_retval(&res, !!search_term);
पूर्ण

अटल पूर्णांक __करो_unरेजिस्टर(पूर्णांक fd, स्थिर काष्ठा bpf_map_info *info, व्योम *data,
			   काष्ठा json_ग_लिखोr *wtr)
अणु
	पूर्णांक zero = 0;

	अगर (bpf_map_delete_elem(fd, &zero)) अणु
		p_err("can't unload %s %s id %u: %s",
		      get_kern_काष्ठा_ops_name(info), info->name,
		      info->id, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	p_info("Unregistered %s %s id %u",
	       get_kern_काष्ठा_ops_name(info), info->name,
	       info->id);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_unरेजिस्टर(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *search_type, *search_term;
	काष्ठा res res;

	अगर (argc != 2)
		usage();

	search_type = GET_ARG();
	search_term = GET_ARG();

	res = करो_work_on_काष्ठा_ops(search_type, search_term,
				    __करो_unरेजिस्टर, शून्य, शून्य);

	वापस cmd_retval(&res, true);
पूर्ण

अटल पूर्णांक करो_रेजिस्टर(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_object_load_attr load_attr = अणुपूर्ण;
	स्थिर काष्ठा bpf_map_def *def;
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	पूर्णांक nr_errs = 0, nr_maps = 0;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_link *link;
	काष्ठा bpf_map *map;
	स्थिर अक्षर *file;

	अगर (argc != 1)
		usage();

	file = GET_ARG();

	obj = bpf_object__खोलो(file);
	अगर (IS_ERR_OR_शून्य(obj))
		वापस -1;

	set_max_rlimit();

	load_attr.obj = obj;
	अगर (verअगरier_logs)
		/* log_level1 + log_level2 + stats, but not stable UAPI */
		load_attr.log_level = 1 + 2 + 4;

	अगर (bpf_object__load_xattr(&load_attr)) अणु
		bpf_object__बंद(obj);
		वापस -1;
	पूर्ण

	bpf_object__क्रम_each_map(map, obj) अणु
		def = bpf_map__def(map);
		अगर (def->type != BPF_MAP_TYPE_STRUCT_OPS)
			जारी;

		link = bpf_map__attach_काष्ठा_ops(map);
		अगर (IS_ERR(link)) अणु
			p_err("can't register struct_ops %s: %s",
			      bpf_map__name(map),
			      म_त्रुटि(-PTR_ERR(link)));
			nr_errs++;
			जारी;
		पूर्ण
		nr_maps++;

		bpf_link__disconnect(link);
		bpf_link__destroy(link);

		अगर (!bpf_obj_get_info_by_fd(bpf_map__fd(map), &info,
					    &info_len))
			p_info("Registered %s %s id %u",
			       get_kern_काष्ठा_ops_name(&info),
			       bpf_map__name(map),
			       info.id);
		अन्यथा
			/* Not p_err.  The काष्ठा_ops was attached
			 * successfully.
			 */
			p_info("Registered %s but can't find id: %s",
			       bpf_map__name(map), म_त्रुटि(त्रुटि_सं));
	पूर्ण

	bpf_object__बंद(obj);

	अगर (nr_errs)
		वापस -1;

	अगर (!nr_maps) अणु
		p_err("no struct_ops found in %s", file);
		वापस -1;
	पूर्ण

	अगर (json_output)
		jsonw_null(json_wtr);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (json_output) अणु
		jsonw_null(json_wtr);
		वापस 0;
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s { show | list } [STRUCT_OPS_MAP]\n"
		"       %1$s %2$s dump [STRUCT_OPS_MAP]\n"
		"       %1$s %2$s register OBJ\n"
		"       %1$s %2$s unregister STRUCT_OPS_MAP\n"
		"       %1$s %2$s help\n"
		"\n"
		"       OPTIONS := { {-j|--json} [{-p|--pretty}] }\n"
		"       STRUCT_OPS_MAP := [ id STRUCT_OPS_MAP_ID | name STRUCT_OPS_MAP_NAME ]\n"
		"",
		bin_name, argv[-2]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "show",	करो_show पूर्ण,
	अणु "list",	करो_show पूर्ण,
	अणु "register",	करो_रेजिस्टर पूर्ण,
	अणु "unregister",	करो_unरेजिस्टर पूर्ण,
	अणु "dump",	करो_dump पूर्ण,
	अणु "help",	करो_help पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_काष्ठा_ops(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक err;

	err = cmd_select(cmds, argc, argv, करो_help);

	अगर (!IS_ERR(btf_vmlinux))
		btf__मुक्त(btf_vmlinux);

	वापस err;
पूर्ण
