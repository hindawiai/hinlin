<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2020 Facebook */

#समावेश <त्रुटिसं.स>
#समावेश <net/अगर.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>

#समावेश <bpf/bpf.h>

#समावेश "json_writer.h"
#समावेश "main.h"

अटल स्थिर अक्षर * स्थिर link_type_name[] = अणु
	[BPF_LINK_TYPE_UNSPEC]			= "unspec",
	[BPF_LINK_TYPE_RAW_TRACEPOINT]		= "raw_tracepoint",
	[BPF_LINK_TYPE_TRACING]			= "tracing",
	[BPF_LINK_TYPE_CGROUP]			= "cgroup",
	[BPF_LINK_TYPE_ITER]			= "iter",
	[BPF_LINK_TYPE_NETNS]			= "netns",
पूर्ण;

अटल पूर्णांक link_parse_fd(पूर्णांक *argc, अक्षर ***argv)
अणु
	पूर्णांक fd;

	अगर (is_prefix(**argv, "id")) अणु
		अचिन्हित पूर्णांक id;
		अक्षर *endptr;

		NEXT_ARGP();

		id = म_से_अदीर्घ(**argv, &endptr, 0);
		अगर (*endptr) अणु
			p_err("can't parse %s as ID", **argv);
			वापस -1;
		पूर्ण
		NEXT_ARGP();

		fd = bpf_link_get_fd_by_id(id);
		अगर (fd < 0)
			p_err("failed to get link with ID %d: %s", id, म_त्रुटि(त्रुटि_सं));
		वापस fd;
	पूर्ण अन्यथा अगर (is_prefix(**argv, "pinned")) अणु
		अक्षर *path;

		NEXT_ARGP();

		path = **argv;
		NEXT_ARGP();

		वापस खोलो_obj_pinned_any(path, BPF_OBJ_LINK);
	पूर्ण

	p_err("expected 'id' or 'pinned', got: '%s'?", **argv);
	वापस -1;
पूर्ण

अटल व्योम
show_link_header_json(काष्ठा bpf_link_info *info, json_ग_लिखोr_t *wtr)
अणु
	jsonw_uपूर्णांक_field(wtr, "id", info->id);
	अगर (info->type < ARRAY_SIZE(link_type_name))
		jsonw_string_field(wtr, "type", link_type_name[info->type]);
	अन्यथा
		jsonw_uपूर्णांक_field(wtr, "type", info->type);

	jsonw_uपूर्णांक_field(json_wtr, "prog_id", info->prog_id);
पूर्ण

अटल व्योम show_link_attach_type_json(__u32 attach_type, json_ग_लिखोr_t *wtr)
अणु
	अगर (attach_type < ARRAY_SIZE(attach_type_name))
		jsonw_string_field(wtr, "attach_type",
				   attach_type_name[attach_type]);
	अन्यथा
		jsonw_uपूर्णांक_field(wtr, "attach_type", attach_type);
पूर्ण

अटल bool is_iter_map_target(स्थिर अक्षर *target_name)
अणु
	वापस म_भेद(target_name, "bpf_map_elem") == 0 ||
	       म_भेद(target_name, "bpf_sk_storage_map") == 0;
पूर्ण

अटल व्योम show_iter_json(काष्ठा bpf_link_info *info, json_ग_लिखोr_t *wtr)
अणु
	स्थिर अक्षर *target_name = u64_to_ptr(info->iter.target_name);

	jsonw_string_field(wtr, "target_name", target_name);

	अगर (is_iter_map_target(target_name))
		jsonw_uपूर्णांक_field(wtr, "map_id", info->iter.map.map_id);
पूर्ण

अटल पूर्णांक get_prog_info(पूर्णांक prog_id, काष्ठा bpf_prog_info *info)
अणु
	__u32 len = माप(*info);
	पूर्णांक err, prog_fd;

	prog_fd = bpf_prog_get_fd_by_id(prog_id);
	अगर (prog_fd < 0)
		वापस prog_fd;

	स_रखो(info, 0, माप(*info));
	err = bpf_obj_get_info_by_fd(prog_fd, info, &len);
	अगर (err)
		p_err("can't get prog info: %s", म_त्रुटि(त्रुटि_सं));
	बंद(prog_fd);
	वापस err;
पूर्ण

अटल पूर्णांक show_link_बंद_json(पूर्णांक fd, काष्ठा bpf_link_info *info)
अणु
	काष्ठा bpf_prog_info prog_info;
	पूर्णांक err;

	jsonw_start_object(json_wtr);

	show_link_header_json(info, json_wtr);

	चयन (info->type) अणु
	हाल BPF_LINK_TYPE_RAW_TRACEPOINT:
		jsonw_string_field(json_wtr, "tp_name",
				   u64_to_ptr(info->raw_tracepoपूर्णांक.tp_name));
		अवरोध;
	हाल BPF_LINK_TYPE_TRACING:
		err = get_prog_info(info->prog_id, &prog_info);
		अगर (err)
			वापस err;

		अगर (prog_info.type < prog_type_name_size)
			jsonw_string_field(json_wtr, "prog_type",
					   prog_type_name[prog_info.type]);
		अन्यथा
			jsonw_uपूर्णांक_field(json_wtr, "prog_type",
					 prog_info.type);

		show_link_attach_type_json(info->tracing.attach_type,
					   json_wtr);
		अवरोध;
	हाल BPF_LINK_TYPE_CGROUP:
		jsonw_lluपूर्णांक_field(json_wtr, "cgroup_id",
				   info->cgroup.cgroup_id);
		show_link_attach_type_json(info->cgroup.attach_type, json_wtr);
		अवरोध;
	हाल BPF_LINK_TYPE_ITER:
		show_iter_json(info, json_wtr);
		अवरोध;
	हाल BPF_LINK_TYPE_NETNS:
		jsonw_uपूर्णांक_field(json_wtr, "netns_ino",
				 info->netns.netns_ino);
		show_link_attach_type_json(info->netns.attach_type, json_wtr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!hash_empty(link_table.table)) अणु
		काष्ठा pinned_obj *obj;

		jsonw_name(json_wtr, "pinned");
		jsonw_start_array(json_wtr);
		hash_क्रम_each_possible(link_table.table, obj, hash, info->id) अणु
			अगर (obj->id == info->id)
				jsonw_string(json_wtr, obj->path);
		पूर्ण
		jsonw_end_array(json_wtr);
	पूर्ण

	emit_obj_refs_json(&refs_table, info->id, json_wtr);

	jsonw_end_object(json_wtr);

	वापस 0;
पूर्ण

अटल व्योम show_link_header_plain(काष्ठा bpf_link_info *info)
अणु
	म_लिखो("%u: ", info->id);
	अगर (info->type < ARRAY_SIZE(link_type_name))
		म_लिखो("%s  ", link_type_name[info->type]);
	अन्यथा
		म_लिखो("type %u  ", info->type);

	म_लिखो("prog %u  ", info->prog_id);
पूर्ण

अटल व्योम show_link_attach_type_plain(__u32 attach_type)
अणु
	अगर (attach_type < ARRAY_SIZE(attach_type_name))
		म_लिखो("attach_type %s  ", attach_type_name[attach_type]);
	अन्यथा
		म_लिखो("attach_type %u  ", attach_type);
पूर्ण

अटल व्योम show_iter_plain(काष्ठा bpf_link_info *info)
अणु
	स्थिर अक्षर *target_name = u64_to_ptr(info->iter.target_name);

	म_लिखो("target_name %s  ", target_name);

	अगर (is_iter_map_target(target_name))
		म_लिखो("map_id %u  ", info->iter.map.map_id);
पूर्ण

अटल पूर्णांक show_link_बंद_plain(पूर्णांक fd, काष्ठा bpf_link_info *info)
अणु
	काष्ठा bpf_prog_info prog_info;
	पूर्णांक err;

	show_link_header_plain(info);

	चयन (info->type) अणु
	हाल BPF_LINK_TYPE_RAW_TRACEPOINT:
		म_लिखो("\n\ttp '%s'  ",
		       (स्थिर अक्षर *)u64_to_ptr(info->raw_tracepoपूर्णांक.tp_name));
		अवरोध;
	हाल BPF_LINK_TYPE_TRACING:
		err = get_prog_info(info->prog_id, &prog_info);
		अगर (err)
			वापस err;

		अगर (prog_info.type < prog_type_name_size)
			म_लिखो("\n\tprog_type %s  ",
			       prog_type_name[prog_info.type]);
		अन्यथा
			म_लिखो("\n\tprog_type %u  ", prog_info.type);

		show_link_attach_type_plain(info->tracing.attach_type);
		अवरोध;
	हाल BPF_LINK_TYPE_CGROUP:
		म_लिखो("\n\tcgroup_id %zu  ", (माप_प्रकार)info->cgroup.cgroup_id);
		show_link_attach_type_plain(info->cgroup.attach_type);
		अवरोध;
	हाल BPF_LINK_TYPE_ITER:
		show_iter_plain(info);
		अवरोध;
	हाल BPF_LINK_TYPE_NETNS:
		म_लिखो("\n\tnetns_ino %u  ", info->netns.netns_ino);
		show_link_attach_type_plain(info->netns.attach_type);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!hash_empty(link_table.table)) अणु
		काष्ठा pinned_obj *obj;

		hash_क्रम_each_possible(link_table.table, obj, hash, info->id) अणु
			अगर (obj->id == info->id)
				म_लिखो("\n\tpinned %s", obj->path);
		पूर्ण
	पूर्ण
	emit_obj_refs_plain(&refs_table, info->id, "\n\tpids ");

	म_लिखो("\n");

	वापस 0;
पूर्ण

अटल पूर्णांक करो_show_link(पूर्णांक fd)
अणु
	काष्ठा bpf_link_info info;
	__u32 len = माप(info);
	अक्षर buf[256];
	पूर्णांक err;

	स_रखो(&info, 0, माप(info));
again:
	err = bpf_obj_get_info_by_fd(fd, &info, &len);
	अगर (err) अणु
		p_err("can't get link info: %s",
		      म_त्रुटि(त्रुटि_सं));
		बंद(fd);
		वापस err;
	पूर्ण
	अगर (info.type == BPF_LINK_TYPE_RAW_TRACEPOINT &&
	    !info.raw_tracepoपूर्णांक.tp_name) अणु
		info.raw_tracepoपूर्णांक.tp_name = (अचिन्हित दीर्घ)&buf;
		info.raw_tracepoपूर्णांक.tp_name_len = माप(buf);
		जाओ again;
	पूर्ण
	अगर (info.type == BPF_LINK_TYPE_ITER &&
	    !info.iter.target_name) अणु
		info.iter.target_name = (अचिन्हित दीर्घ)&buf;
		info.iter.target_name_len = माप(buf);
		जाओ again;
	पूर्ण

	अगर (json_output)
		show_link_बंद_json(fd, &info);
	अन्यथा
		show_link_बंद_plain(fd, &info);

	बंद(fd);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_show(पूर्णांक argc, अक्षर **argv)
अणु
	__u32 id = 0;
	पूर्णांक err, fd;

	अगर (show_pinned)
		build_pinned_obj_table(&link_table, BPF_OBJ_LINK);
	build_obj_refs_table(&refs_table, BPF_OBJ_LINK);

	अगर (argc == 2) अणु
		fd = link_parse_fd(&argc, &argv);
		अगर (fd < 0)
			वापस fd;
		वापस करो_show_link(fd);
	पूर्ण

	अगर (argc)
		वापस BAD_ARG();

	अगर (json_output)
		jsonw_start_array(json_wtr);
	जबतक (true) अणु
		err = bpf_link_get_next_id(id, &id);
		अगर (err) अणु
			अगर (त्रुटि_सं == ENOENT)
				अवरोध;
			p_err("can't get next link: %s%s", म_त्रुटि(त्रुटि_सं),
			      त्रुटि_सं == EINVAL ? " -- kernel too old?" : "");
			अवरोध;
		पूर्ण

		fd = bpf_link_get_fd_by_id(id);
		अगर (fd < 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				जारी;
			p_err("can't get link by id (%u): %s",
			      id, म_त्रुटि(त्रुटि_सं));
			अवरोध;
		पूर्ण

		err = करो_show_link(fd);
		अगर (err)
			अवरोध;
	पूर्ण
	अगर (json_output)
		jsonw_end_array(json_wtr);

	delete_obj_refs_table(&refs_table);

	वापस त्रुटि_सं == ENOENT ? 0 : -1;
पूर्ण

अटल पूर्णांक करो_pin(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक err;

	err = करो_pin_any(argc, argv, link_parse_fd);
	अगर (!err && json_output)
		jsonw_null(json_wtr);
	वापस err;
पूर्ण

अटल पूर्णांक करो_detach(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक err, fd;

	अगर (argc != 2) अणु
		p_err("link specifier is invalid or missing\n");
		वापस 1;
	पूर्ण

	fd = link_parse_fd(&argc, &argv);
	अगर (fd < 0)
		वापस 1;

	err = bpf_link_detach(fd);
	अगर (err)
		err = -त्रुटि_सं;
	बंद(fd);
	अगर (err) अणु
		p_err("failed link detach: %s", म_त्रुटि(-err));
		वापस 1;
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
		"Usage: %1$s %2$s { show | list }   [LINK]\n"
		"       %1$s %2$s pin        LINK  FILE\n"
		"       %1$s %2$s detach     LINK\n"
		"       %1$s %2$s help\n"
		"\n"
		"       " HELP_SPEC_LINK "\n"
		"       " HELP_SPEC_OPTIONS "\n"
		"",
		bin_name, argv[-2]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "show",	करो_show पूर्ण,
	अणु "list",	करो_show पूर्ण,
	अणु "help",	करो_help पूर्ण,
	अणु "pin",	करो_pin पूर्ण,
	अणु "detach",	करो_detach पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_link(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
