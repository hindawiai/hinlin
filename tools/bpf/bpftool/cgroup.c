<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (C) 2017 Facebook
// Author: Roman Gushchin <guro@fb.com>

#घोषणा _XOPEN_SOURCE 500
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <ftw.h>
#समावेश <mntent.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#समावेश <bpf/bpf.h>

#समावेश "main.h"

#घोषणा HELP_SPEC_ATTACH_FLAGS						\
	"ATTACH_FLAGS := { multi | override }"

#घोषणा HELP_SPEC_ATTACH_TYPES						       \
	"       ATTACH_TYPE := { ingress | egress | sock_create |\n"	       \
	"                        sock_ops | device | bind4 | bind6 |\n"	       \
	"                        post_bind4 | post_bind6 | connect4 |\n"       \
	"                        connect6 | getpeername4 | getpeername6 |\n"   \
	"                        getsockname4 | getsockname6 | sendmsg4 |\n"   \
	"                        sendmsg6 | recvmsg4 | recvmsg6 |\n"           \
	"                        sysctl | getsockopt | setsockopt |\n"	       \
	"                        sock_release }"

अटल अचिन्हित पूर्णांक query_flags;

अटल क्रमागत bpf_attach_type parse_attach_type(स्थिर अक्षर *str)
अणु
	क्रमागत bpf_attach_type type;

	क्रम (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++) अणु
		अगर (attach_type_name[type] &&
		    is_prefix(str, attach_type_name[type]))
			वापस type;
	पूर्ण

	वापस __MAX_BPF_ATTACH_TYPE;
पूर्ण

अटल पूर्णांक show_bpf_prog(पूर्णांक id, क्रमागत bpf_attach_type attach_type,
			 स्थिर अक्षर *attach_flags_str,
			 पूर्णांक level)
अणु
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	पूर्णांक prog_fd;

	prog_fd = bpf_prog_get_fd_by_id(id);
	अगर (prog_fd < 0)
		वापस -1;

	अगर (bpf_obj_get_info_by_fd(prog_fd, &info, &info_len)) अणु
		बंद(prog_fd);
		वापस -1;
	पूर्ण

	अगर (json_output) अणु
		jsonw_start_object(json_wtr);
		jsonw_uपूर्णांक_field(json_wtr, "id", info.id);
		अगर (attach_type < ARRAY_SIZE(attach_type_name))
			jsonw_string_field(json_wtr, "attach_type",
					   attach_type_name[attach_type]);
		अन्यथा
			jsonw_uपूर्णांक_field(json_wtr, "attach_type", attach_type);
		jsonw_string_field(json_wtr, "attach_flags",
				   attach_flags_str);
		jsonw_string_field(json_wtr, "name", info.name);
		jsonw_end_object(json_wtr);
	पूर्ण अन्यथा अणु
		म_लिखो("%s%-8u ", level ? "    " : "", info.id);
		अगर (attach_type < ARRAY_SIZE(attach_type_name))
			म_लिखो("%-15s", attach_type_name[attach_type]);
		अन्यथा
			म_लिखो("type %-10u", attach_type);
		म_लिखो(" %-15s %-15s\n", attach_flags_str, info.name);
	पूर्ण

	बंद(prog_fd);
	वापस 0;
पूर्ण

अटल पूर्णांक count_attached_bpf_progs(पूर्णांक cgroup_fd, क्रमागत bpf_attach_type type)
अणु
	__u32 prog_cnt = 0;
	पूर्णांक ret;

	ret = bpf_prog_query(cgroup_fd, type, query_flags, शून्य,
			     शून्य, &prog_cnt);
	अगर (ret)
		वापस -1;

	वापस prog_cnt;
पूर्ण

अटल पूर्णांक cgroup_has_attached_progs(पूर्णांक cgroup_fd)
अणु
	क्रमागत bpf_attach_type type;
	bool no_prog = true;

	क्रम (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++) अणु
		पूर्णांक count = count_attached_bpf_progs(cgroup_fd, type);

		अगर (count < 0 && त्रुटि_सं != EINVAL)
			वापस -1;

		अगर (count > 0) अणु
			no_prog = false;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस no_prog ? 0 : 1;
पूर्ण
अटल पूर्णांक show_attached_bpf_progs(पूर्णांक cgroup_fd, क्रमागत bpf_attach_type type,
				   पूर्णांक level)
अणु
	स्थिर अक्षर *attach_flags_str;
	__u32 prog_ids[1024] = अणु0पूर्ण;
	__u32 prog_cnt, iter;
	__u32 attach_flags;
	अक्षर buf[32];
	पूर्णांक ret;

	prog_cnt = ARRAY_SIZE(prog_ids);
	ret = bpf_prog_query(cgroup_fd, type, query_flags, &attach_flags,
			     prog_ids, &prog_cnt);
	अगर (ret)
		वापस ret;

	अगर (prog_cnt == 0)
		वापस 0;

	चयन (attach_flags) अणु
	हाल BPF_F_ALLOW_MULTI:
		attach_flags_str = "multi";
		अवरोध;
	हाल BPF_F_ALLOW_OVERRIDE:
		attach_flags_str = "override";
		अवरोध;
	हाल 0:
		attach_flags_str = "";
		अवरोध;
	शेष:
		snम_लिखो(buf, माप(buf), "unknown(%x)", attach_flags);
		attach_flags_str = buf;
	पूर्ण

	क्रम (iter = 0; iter < prog_cnt; iter++)
		show_bpf_prog(prog_ids[iter], type,
			      attach_flags_str, level);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_show(पूर्णांक argc, अक्षर **argv)
अणु
	क्रमागत bpf_attach_type type;
	पूर्णांक has_attached_progs;
	स्थिर अक्षर *path;
	पूर्णांक cgroup_fd;
	पूर्णांक ret = -1;

	query_flags = 0;

	अगर (!REQ_ARGS(1))
		वापस -1;
	path = GET_ARG();

	जबतक (argc) अणु
		अगर (is_prefix(*argv, "effective")) अणु
			अगर (query_flags & BPF_F_QUERY_EFFECTIVE) अणु
				p_err("duplicated argument: %s", *argv);
				वापस -1;
			पूर्ण
			query_flags |= BPF_F_QUERY_EFFECTIVE;
			NEXT_ARG();
		पूर्ण अन्यथा अणु
			p_err("expected no more arguments, 'effective', got: '%s'?",
			      *argv);
			वापस -1;
		पूर्ण
	पूर्ण

	cgroup_fd = खोलो(path, O_RDONLY);
	अगर (cgroup_fd < 0) अणु
		p_err("can't open cgroup %s", path);
		जाओ निकास;
	पूर्ण

	has_attached_progs = cgroup_has_attached_progs(cgroup_fd);
	अगर (has_attached_progs < 0) अणु
		p_err("can't query bpf programs attached to %s: %s",
		      path, म_त्रुटि(त्रुटि_सं));
		जाओ निकास_cgroup;
	पूर्ण अन्यथा अगर (!has_attached_progs) अणु
		ret = 0;
		जाओ निकास_cgroup;
	पूर्ण

	अगर (json_output)
		jsonw_start_array(json_wtr);
	अन्यथा
		म_लिखो("%-8s %-15s %-15s %-15s\n", "ID", "AttachType",
		       "AttachFlags", "Name");

	क्रम (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++) अणु
		/*
		 * Not all attach types may be supported, so it's expected,
		 * that some requests will fail.
		 * If we were able to get the show क्रम at least one
		 * attach type, let's वापस 0.
		 */
		अगर (show_attached_bpf_progs(cgroup_fd, type, 0) == 0)
			ret = 0;
	पूर्ण

	अगर (json_output)
		jsonw_end_array(json_wtr);

निकास_cgroup:
	बंद(cgroup_fd);
निकास:
	वापस ret;
पूर्ण

/*
 * To distinguish nftw() errors and करो_show_tree_fn() errors
 * and aव्योम duplicating error messages, let's वापस -2
 * from करो_show_tree_fn() in हाल of error.
 */
#घोषणा NFTW_ERR		-1
#घोषणा SHOW_TREE_FN_ERR	-2
अटल पूर्णांक करो_show_tree_fn(स्थिर अक्षर *fpath, स्थिर काष्ठा stat *sb,
			   पूर्णांक typeflag, काष्ठा FTW *ftw)
अणु
	क्रमागत bpf_attach_type type;
	पूर्णांक has_attached_progs;
	पूर्णांक cgroup_fd;

	अगर (typeflag != FTW_D)
		वापस 0;

	cgroup_fd = खोलो(fpath, O_RDONLY);
	अगर (cgroup_fd < 0) अणु
		p_err("can't open cgroup %s: %s", fpath, म_त्रुटि(त्रुटि_सं));
		वापस SHOW_TREE_FN_ERR;
	पूर्ण

	has_attached_progs = cgroup_has_attached_progs(cgroup_fd);
	अगर (has_attached_progs < 0) अणु
		p_err("can't query bpf programs attached to %s: %s",
		      fpath, म_त्रुटि(त्रुटि_सं));
		बंद(cgroup_fd);
		वापस SHOW_TREE_FN_ERR;
	पूर्ण अन्यथा अगर (!has_attached_progs) अणु
		बंद(cgroup_fd);
		वापस 0;
	पूर्ण

	अगर (json_output) अणु
		jsonw_start_object(json_wtr);
		jsonw_string_field(json_wtr, "cgroup", fpath);
		jsonw_name(json_wtr, "programs");
		jsonw_start_array(json_wtr);
	पूर्ण अन्यथा अणु
		म_लिखो("%s\n", fpath);
	पूर्ण

	क्रम (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++)
		show_attached_bpf_progs(cgroup_fd, type, ftw->level);

	अगर (त्रुटि_सं == EINVAL)
		/* Last attach type करोes not support query.
		 * Do not report an error क्रम this, especially because batch
		 * mode would stop processing commands.
		 */
		त्रुटि_सं = 0;

	अगर (json_output) अणु
		jsonw_end_array(json_wtr);
		jsonw_end_object(json_wtr);
	पूर्ण

	बंद(cgroup_fd);

	वापस 0;
पूर्ण

अटल अक्षर *find_cgroup_root(व्योम)
अणु
	काष्ठा mntent *mnt;
	खाता *f;

	f = ख_खोलो("/proc/mounts", "r");
	अगर (f == शून्य)
		वापस शून्य;

	जबतक ((mnt = geपंचांगntent(f))) अणु
		अगर (म_भेद(mnt->mnt_type, "cgroup2") == 0) अणु
			ख_बंद(f);
			वापस strdup(mnt->mnt_dir);
		पूर्ण
	पूर्ण

	ख_बंद(f);
	वापस शून्य;
पूर्ण

अटल पूर्णांक करो_show_tree(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *cgroup_root, *cgroup_alloced = शून्य;
	पूर्णांक ret;

	query_flags = 0;

	अगर (!argc) अणु
		cgroup_alloced = find_cgroup_root();
		अगर (!cgroup_alloced) अणु
			p_err("cgroup v2 isn't mounted");
			वापस -1;
		पूर्ण
		cgroup_root = cgroup_alloced;
	पूर्ण अन्यथा अणु
		cgroup_root = GET_ARG();

		जबतक (argc) अणु
			अगर (is_prefix(*argv, "effective")) अणु
				अगर (query_flags & BPF_F_QUERY_EFFECTIVE) अणु
					p_err("duplicated argument: %s", *argv);
					वापस -1;
				पूर्ण
				query_flags |= BPF_F_QUERY_EFFECTIVE;
				NEXT_ARG();
			पूर्ण अन्यथा अणु
				p_err("expected no more arguments, 'effective', got: '%s'?",
				      *argv);
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (json_output)
		jsonw_start_array(json_wtr);
	अन्यथा
		म_लिखो("%s\n"
		       "%-8s %-15s %-15s %-15s\n",
		       "CgroupPath",
		       "ID", "AttachType", "AttachFlags", "Name");

	चयन (nftw(cgroup_root, करो_show_tree_fn, 1024, FTW_MOUNT)) अणु
	हाल NFTW_ERR:
		p_err("can't iterate over %s: %s", cgroup_root,
		      म_त्रुटि(त्रुटि_सं));
		ret = -1;
		अवरोध;
	हाल SHOW_TREE_FN_ERR:
		ret = -1;
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

	अगर (json_output)
		jsonw_end_array(json_wtr);

	मुक्त(cgroup_alloced);

	वापस ret;
पूर्ण

अटल पूर्णांक करो_attach(पूर्णांक argc, अक्षर **argv)
अणु
	क्रमागत bpf_attach_type attach_type;
	पूर्णांक cgroup_fd, prog_fd;
	पूर्णांक attach_flags = 0;
	पूर्णांक ret = -1;
	पूर्णांक i;

	अगर (argc < 4) अणु
		p_err("too few parameters for cgroup attach");
		जाओ निकास;
	पूर्ण

	cgroup_fd = खोलो(argv[0], O_RDONLY);
	अगर (cgroup_fd < 0) अणु
		p_err("can't open cgroup %s", argv[0]);
		जाओ निकास;
	पूर्ण

	attach_type = parse_attach_type(argv[1]);
	अगर (attach_type == __MAX_BPF_ATTACH_TYPE) अणु
		p_err("invalid attach type");
		जाओ निकास_cgroup;
	पूर्ण

	argc -= 2;
	argv = &argv[2];
	prog_fd = prog_parse_fd(&argc, &argv);
	अगर (prog_fd < 0)
		जाओ निकास_cgroup;

	क्रम (i = 0; i < argc; i++) अणु
		अगर (is_prefix(argv[i], "multi")) अणु
			attach_flags |= BPF_F_ALLOW_MULTI;
		पूर्ण अन्यथा अगर (is_prefix(argv[i], "override")) अणु
			attach_flags |= BPF_F_ALLOW_OVERRIDE;
		पूर्ण अन्यथा अणु
			p_err("unknown option: %s", argv[i]);
			जाओ निकास_cgroup;
		पूर्ण
	पूर्ण

	अगर (bpf_prog_attach(prog_fd, cgroup_fd, attach_type, attach_flags)) अणु
		p_err("failed to attach program");
		जाओ निकास_prog;
	पूर्ण

	अगर (json_output)
		jsonw_null(json_wtr);

	ret = 0;

निकास_prog:
	बंद(prog_fd);
निकास_cgroup:
	बंद(cgroup_fd);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक करो_detach(पूर्णांक argc, अक्षर **argv)
अणु
	क्रमागत bpf_attach_type attach_type;
	पूर्णांक prog_fd, cgroup_fd;
	पूर्णांक ret = -1;

	अगर (argc < 4) अणु
		p_err("too few parameters for cgroup detach");
		जाओ निकास;
	पूर्ण

	cgroup_fd = खोलो(argv[0], O_RDONLY);
	अगर (cgroup_fd < 0) अणु
		p_err("can't open cgroup %s", argv[0]);
		जाओ निकास;
	पूर्ण

	attach_type = parse_attach_type(argv[1]);
	अगर (attach_type == __MAX_BPF_ATTACH_TYPE) अणु
		p_err("invalid attach type");
		जाओ निकास_cgroup;
	पूर्ण

	argc -= 2;
	argv = &argv[2];
	prog_fd = prog_parse_fd(&argc, &argv);
	अगर (prog_fd < 0)
		जाओ निकास_cgroup;

	अगर (bpf_prog_detach2(prog_fd, cgroup_fd, attach_type)) अणु
		p_err("failed to detach program");
		जाओ निकास_prog;
	पूर्ण

	अगर (json_output)
		jsonw_null(json_wtr);

	ret = 0;

निकास_prog:
	बंद(prog_fd);
निकास_cgroup:
	बंद(cgroup_fd);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (json_output) अणु
		jsonw_null(json_wtr);
		वापस 0;
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s { show | list } CGROUP [**effective**]\n"
		"       %1$s %2$s tree [CGROUP_ROOT] [**effective**]\n"
		"       %1$s %2$s attach CGROUP ATTACH_TYPE PROG [ATTACH_FLAGS]\n"
		"       %1$s %2$s detach CGROUP ATTACH_TYPE PROG\n"
		"       %1$s %2$s help\n"
		"\n"
		HELP_SPEC_ATTACH_TYPES "\n"
		"       " HELP_SPEC_ATTACH_FLAGS "\n"
		"       " HELP_SPEC_PROGRAM "\n"
		"       " HELP_SPEC_OPTIONS "\n"
		"",
		bin_name, argv[-2]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "show",	करो_show पूर्ण,
	अणु "list",	करो_show पूर्ण,
	अणु "tree",       करो_show_tree पूर्ण,
	अणु "attach",	करो_attach पूर्ण,
	अणु "detach",	करो_detach पूर्ण,
	अणु "help",	करो_help पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_cgroup(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
