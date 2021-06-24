<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */
#समावेश <test_progs.h>
#समावेश <network_helpers.h>
#समावेश <bpf/btf.h>

प्रकार पूर्णांक (*test_cb)(काष्ठा bpf_object *obj);

अटल पूर्णांक check_data_map(काष्ठा bpf_object *obj, पूर्णांक prog_cnt, bool reset)
अणु
	काष्ठा bpf_map *data_map = शून्य, *map;
	__u64 *result = शून्य;
	स्थिर पूर्णांक zero = 0;
	__u32 duration = 0;
	पूर्णांक ret = -1, i;

	result = दो_स्मृति((prog_cnt + 32 /* spare */) * माप(__u64));
	अगर (CHECK(!result, "alloc_memory", "failed to alloc memory"))
		वापस -ENOMEM;

	bpf_object__क्रम_each_map(map, obj)
		अगर (bpf_map__is_पूर्णांकernal(map)) अणु
			data_map = map;
			अवरोध;
		पूर्ण
	अगर (CHECK(!data_map, "find_data_map", "data map not found\n"))
		जाओ out;

	ret = bpf_map_lookup_elem(bpf_map__fd(data_map), &zero, result);
	अगर (CHECK(ret, "get_result",
		  "failed to get output data: %d\n", ret))
		जाओ out;

	क्रम (i = 0; i < prog_cnt; i++) अणु
		अगर (CHECK(result[i] != 1, "result",
			  "fexit_bpf2bpf result[%d] failed err %llu\n",
			  i, result[i]))
			जाओ out;
		result[i] = 0;
	पूर्ण
	अगर (reset) अणु
		ret = bpf_map_update_elem(bpf_map__fd(data_map), &zero, result, 0);
		अगर (CHECK(ret, "reset_result", "failed to reset result\n"))
			जाओ out;
	पूर्ण

	ret = 0;
out:
	मुक्त(result);
	वापस ret;
पूर्ण

अटल व्योम test_fनिकास_bpf2bpf_common(स्थिर अक्षर *obj_file,
				      स्थिर अक्षर *target_obj_file,
				      पूर्णांक prog_cnt,
				      स्थिर अक्षर **prog_name,
				      bool run_prog,
				      test_cb cb)
अणु
	काष्ठा bpf_object *obj = शून्य, *tgt_obj;
	__u32 retval, tgt_prog_id, info_len;
	काष्ठा bpf_prog_info prog_info = अणुपूर्ण;
	काष्ठा bpf_program **prog = शून्य;
	काष्ठा bpf_link **link = शून्य;
	पूर्णांक err, tgt_fd, i;
	काष्ठा btf *btf;

	err = bpf_prog_load(target_obj_file, BPF_PROG_TYPE_UNSPEC,
			    &tgt_obj, &tgt_fd);
	अगर (!ASSERT_OK(err, "tgt_prog_load"))
		वापस;
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, opts,
			    .attach_prog_fd = tgt_fd,
			   );

	info_len = माप(prog_info);
	err = bpf_obj_get_info_by_fd(tgt_fd, &prog_info, &info_len);
	अगर (!ASSERT_OK(err, "tgt_fd_get_info"))
		जाओ बंद_prog;

	tgt_prog_id = prog_info.id;
	btf = bpf_object__btf(tgt_obj);

	link = सुस्मृति(माप(काष्ठा bpf_link *), prog_cnt);
	अगर (!ASSERT_OK_PTR(link, "link_ptr"))
		जाओ बंद_prog;

	prog = सुस्मृति(माप(काष्ठा bpf_program *), prog_cnt);
	अगर (!ASSERT_OK_PTR(prog, "prog_ptr"))
		जाओ बंद_prog;

	obj = bpf_object__खोलो_file(obj_file, &opts);
	अगर (!ASSERT_OK_PTR(obj, "obj_open"))
		जाओ बंद_prog;

	err = bpf_object__load(obj);
	अगर (!ASSERT_OK(err, "obj_load"))
		जाओ बंद_prog;

	क्रम (i = 0; i < prog_cnt; i++) अणु
		काष्ठा bpf_link_info link_info;
		अक्षर *tgt_name;
		__s32 btf_id;

		tgt_name = म_माला(prog_name[i], "/");
		अगर (!ASSERT_OK_PTR(tgt_name, "tgt_name"))
			जाओ बंद_prog;
		btf_id = btf__find_by_name_kind(btf, tgt_name + 1, BTF_KIND_FUNC);

		prog[i] = bpf_object__find_program_by_title(obj, prog_name[i]);
		अगर (!ASSERT_OK_PTR(prog[i], prog_name[i]))
			जाओ बंद_prog;

		link[i] = bpf_program__attach_trace(prog[i]);
		अगर (!ASSERT_OK_PTR(link[i], "attach_trace"))
			जाओ बंद_prog;

		info_len = माप(link_info);
		स_रखो(&link_info, 0, माप(link_info));
		err = bpf_obj_get_info_by_fd(bpf_link__fd(link[i]),
					     &link_info, &info_len);
		ASSERT_OK(err, "link_fd_get_info");
		ASSERT_EQ(link_info.tracing.attach_type,
			  bpf_program__get_expected_attach_type(prog[i]),
			  "link_attach_type");
		ASSERT_EQ(link_info.tracing.target_obj_id, tgt_prog_id, "link_tgt_obj_id");
		ASSERT_EQ(link_info.tracing.target_btf_id, btf_id, "link_tgt_btf_id");
	पूर्ण

	अगर (cb) अणु
		err = cb(obj);
		अगर (err)
			जाओ बंद_prog;
	पूर्ण

	अगर (!run_prog)
		जाओ बंद_prog;

	err = bpf_prog_test_run(tgt_fd, 1, &pkt_v6, माप(pkt_v6),
				शून्य, शून्य, &retval, शून्य);
	ASSERT_OK(err, "prog_run");
	ASSERT_EQ(retval, 0, "prog_run_ret");

	अगर (check_data_map(obj, prog_cnt, false))
		जाओ बंद_prog;

बंद_prog:
	क्रम (i = 0; i < prog_cnt; i++)
		अगर (!IS_ERR_OR_शून्य(link[i]))
			bpf_link__destroy(link[i]);
	अगर (!IS_ERR_OR_शून्य(obj))
		bpf_object__बंद(obj);
	bpf_object__बंद(tgt_obj);
	मुक्त(link);
	मुक्त(prog);
पूर्ण

अटल व्योम test_target_no_callees(व्योम)
अणु
	स्थिर अक्षर *prog_name[] = अणु
		"fexit/test_pkt_md_access",
	पूर्ण;
	test_fनिकास_bpf2bpf_common("./fexit_bpf2bpf_simple.o",
				  "./test_pkt_md_access.o",
				  ARRAY_SIZE(prog_name),
				  prog_name, true, शून्य);
पूर्ण

अटल व्योम test_target_yes_callees(व्योम)
अणु
	स्थिर अक्षर *prog_name[] = अणु
		"fexit/test_pkt_access",
		"fexit/test_pkt_access_subprog1",
		"fexit/test_pkt_access_subprog2",
		"fexit/test_pkt_access_subprog3",
	पूर्ण;
	test_fनिकास_bpf2bpf_common("./fexit_bpf2bpf.o",
				  "./test_pkt_access.o",
				  ARRAY_SIZE(prog_name),
				  prog_name, true, शून्य);
पूर्ण

अटल व्योम test_func_replace(व्योम)
अणु
	स्थिर अक्षर *prog_name[] = अणु
		"fexit/test_pkt_access",
		"fexit/test_pkt_access_subprog1",
		"fexit/test_pkt_access_subprog2",
		"fexit/test_pkt_access_subprog3",
		"freplace/get_skb_len",
		"freplace/get_skb_ifindex",
		"freplace/get_constant",
		"freplace/test_pkt_write_access_subprog",
	पूर्ण;
	test_fनिकास_bpf2bpf_common("./fexit_bpf2bpf.o",
				  "./test_pkt_access.o",
				  ARRAY_SIZE(prog_name),
				  prog_name, true, शून्य);
पूर्ण

अटल व्योम test_func_replace_verअगरy(व्योम)
अणु
	स्थिर अक्षर *prog_name[] = अणु
		"freplace/do_bind",
	पूर्ण;
	test_fनिकास_bpf2bpf_common("./freplace_connect4.o",
				  "./connect4_prog.o",
				  ARRAY_SIZE(prog_name),
				  prog_name, false, शून्य);
पूर्ण

अटल पूर्णांक test_second_attach(काष्ठा bpf_object *obj)
अणु
	स्थिर अक्षर *prog_name = "freplace/get_constant";
	स्थिर अक्षर *tgt_name = prog_name + 9; /* cut off freplace/ */
	स्थिर अक्षर *tgt_obj_file = "./test_pkt_access.o";
	काष्ठा bpf_program *prog = शून्य;
	काष्ठा bpf_object *tgt_obj;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;
	पूर्णांक err = 0, tgt_fd;

	prog = bpf_object__find_program_by_title(obj, prog_name);
	अगर (CHECK(!prog, "find_prog", "prog %s not found\n", prog_name))
		वापस -ENOENT;

	err = bpf_prog_load(tgt_obj_file, BPF_PROG_TYPE_UNSPEC,
			    &tgt_obj, &tgt_fd);
	अगर (CHECK(err, "second_prog_load", "file %s err %d errno %d\n",
		  tgt_obj_file, err, त्रुटि_सं))
		वापस err;

	link = bpf_program__attach_freplace(prog, tgt_fd, tgt_name);
	अगर (CHECK(IS_ERR(link), "second_link", "failed to attach second link prog_fd %d tgt_fd %d\n", bpf_program__fd(prog), tgt_fd))
		जाओ out;

	err = bpf_prog_test_run(tgt_fd, 1, &pkt_v6, माप(pkt_v6),
				शून्य, शून्य, &retval, &duration);
	अगर (CHECK(err || retval, "ipv6",
		  "err %d errno %d retval %d duration %d\n",
		  err, त्रुटि_सं, retval, duration))
		जाओ out;

	err = check_data_map(obj, 1, true);
	अगर (err)
		जाओ out;

out:
	bpf_link__destroy(link);
	bpf_object__बंद(tgt_obj);
	वापस err;
पूर्ण

अटल व्योम test_func_replace_multi(व्योम)
अणु
	स्थिर अक्षर *prog_name[] = अणु
		"freplace/get_constant",
	पूर्ण;
	test_fनिकास_bpf2bpf_common("./freplace_get_constant.o",
				  "./test_pkt_access.o",
				  ARRAY_SIZE(prog_name),
				  prog_name, true, test_second_attach);
पूर्ण

अटल व्योम test_भ_शेष_ret_freplace(व्योम)
अणु
	काष्ठा bpf_object *freplace_obj = शून्य, *pkt_obj, *भ_शेष_obj = शून्य;
	स्थिर अक्षर *freplace_name = "./freplace_get_constant.o";
	स्थिर अक्षर *भ_शेष_ret_name = "./fmod_ret_freplace.o";
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, opts);
	स्थिर अक्षर *tgt_name = "./test_pkt_access.o";
	काष्ठा bpf_link *freplace_link = शून्य;
	काष्ठा bpf_program *prog;
	__u32 duration = 0;
	पूर्णांक err, pkt_fd;

	err = bpf_prog_load(tgt_name, BPF_PROG_TYPE_UNSPEC,
			    &pkt_obj, &pkt_fd);
	/* the target prog should load fine */
	अगर (CHECK(err, "tgt_prog_load", "file %s err %d errno %d\n",
		  tgt_name, err, त्रुटि_सं))
		वापस;
	opts.attach_prog_fd = pkt_fd;

	freplace_obj = bpf_object__खोलो_file(freplace_name, &opts);
	अगर (CHECK(IS_ERR_OR_शून्य(freplace_obj), "freplace_obj_open",
		  "failed to open %s: %ld\n", freplace_name,
		  PTR_ERR(freplace_obj)))
		जाओ out;

	err = bpf_object__load(freplace_obj);
	अगर (CHECK(err, "freplace_obj_load", "err %d\n", err))
		जाओ out;

	prog = bpf_program__next(शून्य, freplace_obj);
	freplace_link = bpf_program__attach_trace(prog);
	अगर (CHECK(IS_ERR(freplace_link), "freplace_attach_trace", "failed to link\n"))
		जाओ out;

	opts.attach_prog_fd = bpf_program__fd(prog);
	भ_शेष_obj = bpf_object__खोलो_file(भ_शेष_ret_name, &opts);
	अगर (CHECK(IS_ERR_OR_शून्य(भ_शेष_obj), "fmod_obj_open",
		  "failed to open %s: %ld\n", भ_शेष_ret_name,
		  PTR_ERR(भ_शेष_obj)))
		जाओ out;

	err = bpf_object__load(भ_शेष_obj);
	अगर (CHECK(!err, "fmod_obj_load", "loading fmod_ret should fail\n"))
		जाओ out;

out:
	bpf_link__destroy(freplace_link);
	bpf_object__बंद(freplace_obj);
	bpf_object__बंद(भ_शेष_obj);
	bpf_object__बंद(pkt_obj);
पूर्ण


अटल व्योम test_func_sockmap_update(व्योम)
अणु
	स्थिर अक्षर *prog_name[] = अणु
		"freplace/cls_redirect",
	पूर्ण;
	test_fनिकास_bpf2bpf_common("./freplace_cls_redirect.o",
				  "./test_cls_redirect.o",
				  ARRAY_SIZE(prog_name),
				  prog_name, false, शून्य);
पूर्ण

अटल व्योम test_obj_load_failure_common(स्थिर अक्षर *obj_file,
					  स्थिर अक्षर *target_obj_file)

अणु
	/*
	 * standalone test that निश्चितs failure to load freplace prog
	 * because of invalid वापस code.
	 */
	काष्ठा bpf_object *obj = शून्य, *pkt_obj;
	पूर्णांक err, pkt_fd;
	__u32 duration = 0;

	err = bpf_prog_load(target_obj_file, BPF_PROG_TYPE_UNSPEC,
			    &pkt_obj, &pkt_fd);
	/* the target prog should load fine */
	अगर (CHECK(err, "tgt_prog_load", "file %s err %d errno %d\n",
		  target_obj_file, err, त्रुटि_सं))
		वापस;
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, opts,
			    .attach_prog_fd = pkt_fd,
			   );

	obj = bpf_object__खोलो_file(obj_file, &opts);
	अगर (CHECK(IS_ERR_OR_शून्य(obj), "obj_open",
		  "failed to open %s: %ld\n", obj_file,
		  PTR_ERR(obj)))
		जाओ बंद_prog;

	/* It should fail to load the program */
	err = bpf_object__load(obj);
	अगर (CHECK(!err, "bpf_obj_load should fail", "err %d\n", err))
		जाओ बंद_prog;

बंद_prog:
	अगर (!IS_ERR_OR_शून्य(obj))
		bpf_object__बंद(obj);
	bpf_object__बंद(pkt_obj);
पूर्ण

अटल व्योम test_func_replace_वापस_code(व्योम)
अणु
	/* test invalid वापस code in the replaced program */
	test_obj_load_failure_common("./freplace_connect_v4_prog.o",
				     "./connect4_prog.o");
पूर्ण

अटल व्योम test_func_map_prog_compatibility(व्योम)
अणु
	/* test with spin lock map value in the replaced program */
	test_obj_load_failure_common("./freplace_attach_probe.o",
				     "./test_attach_probe.o");
पूर्ण

व्योम test_fनिकास_bpf2bpf(व्योम)
अणु
	अगर (test__start_subtest("target_no_callees"))
		test_target_no_callees();
	अगर (test__start_subtest("target_yes_callees"))
		test_target_yes_callees();
	अगर (test__start_subtest("func_replace"))
		test_func_replace();
	अगर (test__start_subtest("func_replace_verify"))
		test_func_replace_verअगरy();
	अगर (test__start_subtest("func_sockmap_update"))
		test_func_sockmap_update();
	अगर (test__start_subtest("func_replace_return_code"))
		test_func_replace_वापस_code();
	अगर (test__start_subtest("func_map_prog_compatibility"))
		test_func_map_prog_compatibility();
	अगर (test__start_subtest("func_replace_multi"))
		test_func_replace_multi();
	अगर (test__start_subtest("fmod_ret_freplace"))
		test_भ_शेष_ret_freplace();
पूर्ण
