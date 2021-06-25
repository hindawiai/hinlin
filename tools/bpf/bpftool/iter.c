<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (C) 2020 Facebook

#घोषणा _GNU_SOURCE
#समावेश <unistd.h>
#समावेश <linux/err.h>
#समावेश <bpf/libbpf.h>

#समावेश "main.h"

अटल पूर्णांक करो_pin(पूर्णांक argc, अक्षर **argv)
अणु
	DECLARE_LIBBPF_OPTS(bpf_iter_attach_opts, iter_opts);
	जोड़ bpf_iter_link_info linfo;
	स्थिर अक्षर *objfile, *path;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_link *link;
	पूर्णांक err = -1, map_fd = -1;

	अगर (!REQ_ARGS(2))
		usage();

	objfile = GET_ARG();
	path = GET_ARG();

	/* optional arguments */
	अगर (argc) अणु
		अगर (is_prefix(*argv, "map")) अणु
			NEXT_ARG();

			अगर (!REQ_ARGS(2)) अणु
				p_err("incorrect map spec");
				वापस -1;
			पूर्ण

			map_fd = map_parse_fd(&argc, &argv);
			अगर (map_fd < 0)
				वापस -1;

			स_रखो(&linfo, 0, माप(linfo));
			linfo.map.map_fd = map_fd;
			iter_opts.link_info = &linfo;
			iter_opts.link_info_len = माप(linfo);
		पूर्ण
	पूर्ण

	obj = bpf_object__खोलो(objfile);
	अगर (IS_ERR(obj)) अणु
		p_err("can't open objfile %s", objfile);
		जाओ बंद_map_fd;
	पूर्ण

	err = bpf_object__load(obj);
	अगर (err) अणु
		p_err("can't load objfile %s", objfile);
		जाओ बंद_obj;
	पूर्ण

	prog = bpf_program__next(शून्य, obj);
	अगर (!prog) अणु
		p_err("can't find bpf program in objfile %s", objfile);
		जाओ बंद_obj;
	पूर्ण

	link = bpf_program__attach_iter(prog, &iter_opts);
	अगर (IS_ERR(link)) अणु
		err = PTR_ERR(link);
		p_err("attach_iter failed for program %s",
		      bpf_program__name(prog));
		जाओ बंद_obj;
	पूर्ण

	err = mount_bpffs_क्रम_pin(path);
	अगर (err)
		जाओ बंद_link;

	err = bpf_link__pin(link, path);
	अगर (err) अणु
		p_err("pin_iter failed for program %s to path %s",
		      bpf_program__name(prog), path);
		जाओ बंद_link;
	पूर्ण

बंद_link:
	bpf_link__destroy(link);
बंद_obj:
	bpf_object__बंद(obj);
बंद_map_fd:
	अगर (map_fd >= 0)
		बंद(map_fd);
	वापस err;
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s pin OBJ PATH [map MAP]\n"
		"       %1$s %2$s help\n"
		"       " HELP_SPEC_MAP "\n"
		"",
		bin_name, "iter");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "help",	करो_help पूर्ण,
	अणु "pin",	करो_pin पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_iter(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
