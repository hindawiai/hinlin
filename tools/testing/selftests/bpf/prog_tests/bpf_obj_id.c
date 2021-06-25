<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

#घोषणा nr_iters 2

व्योम test_bpf_obj_id(व्योम)
अणु
	स्थिर __u64 array_magic_value = 0xfaceb00c;
	स्थिर __u32 array_key = 0;
	स्थिर अक्षर *file = "./test_obj_id.o";
	स्थिर अक्षर *expected_prog_name = "test_obj_id";
	स्थिर अक्षर *expected_map_name = "test_map_id";
	स्थिर __u64 nsec_per_sec = 1000000000;

	काष्ठा bpf_object *objs[nr_iters] = अणुपूर्ण;
	काष्ठा bpf_link *links[nr_iters] = अणुपूर्ण;
	काष्ठा bpf_program *prog;
	पूर्णांक prog_fds[nr_iters], map_fds[nr_iters];
	/* +1 to test क्रम the info_len वापसed by kernel */
	काष्ठा bpf_prog_info prog_infos[nr_iters + 1];
	काष्ठा bpf_map_info map_infos[nr_iters + 1];
	काष्ठा bpf_link_info link_infos[nr_iters + 1];
	/* Each prog only uses one map. +1 to test nr_map_ids
	 * वापसed by kernel.
	 */
	__u32 map_ids[nr_iters + 1];
	अक्षर jited_insns[128], xlated_insns[128], zeros[128], tp_name[128];
	__u32 i, next_id, info_len, nr_id_found, duration = 0;
	काष्ठा बारpec real_समय_प्रकारs, boot_समय_प्रकारs;
	पूर्णांक err = 0;
	__u64 array_value;
	uid_t my_uid = getuid();
	समय_प्रकार now, load_समय;

	err = bpf_prog_get_fd_by_id(0);
	CHECK(err >= 0 || त्रुटि_सं != ENOENT,
	      "get-fd-by-notexist-prog-id", "err %d errno %d\n", err, त्रुटि_सं);

	err = bpf_map_get_fd_by_id(0);
	CHECK(err >= 0 || त्रुटि_सं != ENOENT,
	      "get-fd-by-notexist-map-id", "err %d errno %d\n", err, त्रुटि_सं);

	err = bpf_link_get_fd_by_id(0);
	CHECK(err >= 0 || त्रुटि_सं != ENOENT,
	      "get-fd-by-notexist-link-id", "err %d errno %d\n", err, त्रुटि_सं);

	/* Check bpf_obj_get_info_by_fd() */
	bzero(zeros, माप(zeros));
	क्रम (i = 0; i < nr_iters; i++) अणु
		now = समय(शून्य);
		err = bpf_prog_load(file, BPF_PROG_TYPE_RAW_TRACEPOINT,
				    &objs[i], &prog_fds[i]);
		/* test_obj_id.o is a dumb prog. It should never fail
		 * to load.
		 */
		अगर (CHECK_FAIL(err))
			जारी;

		/* Insert a magic value to the map */
		map_fds[i] = bpf_find_map(__func__, objs[i], "test_map_id");
		अगर (CHECK_FAIL(map_fds[i] < 0))
			जाओ करोne;
		err = bpf_map_update_elem(map_fds[i], &array_key,
					  &array_magic_value, 0);
		अगर (CHECK_FAIL(err))
			जाओ करोne;

		prog = bpf_object__find_program_by_title(objs[i],
							 "raw_tp/sys_enter");
		अगर (CHECK_FAIL(!prog))
			जाओ करोne;
		links[i] = bpf_program__attach(prog);
		err = libbpf_get_error(links[i]);
		अगर (CHECK(err, "prog_attach", "prog #%d, err %d\n", i, err)) अणु
			links[i] = शून्य;
			जाओ करोne;
		पूर्ण

		/* Check getting map info */
		info_len = माप(काष्ठा bpf_map_info) * 2;
		bzero(&map_infos[i], info_len);
		err = bpf_obj_get_info_by_fd(map_fds[i], &map_infos[i],
					     &info_len);
		अगर (CHECK(err ||
			  map_infos[i].type != BPF_MAP_TYPE_ARRAY ||
			  map_infos[i].key_size != माप(__u32) ||
			  map_infos[i].value_size != माप(__u64) ||
			  map_infos[i].max_entries != 1 ||
			  map_infos[i].map_flags != 0 ||
			  info_len != माप(काष्ठा bpf_map_info) ||
			  म_भेद((अक्षर *)map_infos[i].name, expected_map_name),
			  "get-map-info(fd)",
			  "err %d errno %d type %d(%d) info_len %u(%zu) key_size %u value_size %u max_entries %u map_flags %X name %s(%s)\n",
			  err, त्रुटि_सं,
			  map_infos[i].type, BPF_MAP_TYPE_ARRAY,
			  info_len, माप(काष्ठा bpf_map_info),
			  map_infos[i].key_size,
			  map_infos[i].value_size,
			  map_infos[i].max_entries,
			  map_infos[i].map_flags,
			  map_infos[i].name, expected_map_name))
			जाओ करोne;

		/* Check getting prog info */
		info_len = माप(काष्ठा bpf_prog_info) * 2;
		bzero(&prog_infos[i], info_len);
		bzero(jited_insns, माप(jited_insns));
		bzero(xlated_insns, माप(xlated_insns));
		prog_infos[i].jited_prog_insns = ptr_to_u64(jited_insns);
		prog_infos[i].jited_prog_len = माप(jited_insns);
		prog_infos[i].xlated_prog_insns = ptr_to_u64(xlated_insns);
		prog_infos[i].xlated_prog_len = माप(xlated_insns);
		prog_infos[i].map_ids = ptr_to_u64(map_ids + i);
		prog_infos[i].nr_map_ids = 2;
		err = घड़ी_समय_लो(CLOCK_REALTIME, &real_समय_प्रकारs);
		अगर (CHECK_FAIL(err))
			जाओ करोne;
		err = घड़ी_समय_लो(CLOCK_BOOTTIME, &boot_समय_प्रकारs);
		अगर (CHECK_FAIL(err))
			जाओ करोne;
		err = bpf_obj_get_info_by_fd(prog_fds[i], &prog_infos[i],
					     &info_len);
		load_समय = (real_समय_प्रकारs.tv_sec - boot_समय_प्रकारs.tv_sec)
			+ (prog_infos[i].load_समय / nsec_per_sec);
		अगर (CHECK(err ||
			  prog_infos[i].type != BPF_PROG_TYPE_RAW_TRACEPOINT ||
			  info_len != माप(काष्ठा bpf_prog_info) ||
			  (env.jit_enabled && !prog_infos[i].jited_prog_len) ||
			  (env.jit_enabled &&
			   !स_भेद(jited_insns, zeros, माप(zeros))) ||
			  !prog_infos[i].xlated_prog_len ||
			  !स_भेद(xlated_insns, zeros, माप(zeros)) ||
			  load_समय < now - 60 || load_समय > now + 60 ||
			  prog_infos[i].created_by_uid != my_uid ||
			  prog_infos[i].nr_map_ids != 1 ||
			  *(पूर्णांक *)(दीर्घ)prog_infos[i].map_ids != map_infos[i].id ||
			  म_भेद((अक्षर *)prog_infos[i].name, expected_prog_name),
			  "get-prog-info(fd)",
			  "err %d errno %d i %d type %d(%d) info_len %u(%zu) "
			  "jit_enabled %d jited_prog_len %u xlated_prog_len %u "
			  "jited_prog %d xlated_prog %d load_time %lu(%lu) "
			  "uid %u(%u) nr_map_ids %u(%u) map_id %u(%u) "
			  "name %s(%s)\n",
			  err, त्रुटि_सं, i,
			  prog_infos[i].type, BPF_PROG_TYPE_SOCKET_FILTER,
			  info_len, माप(काष्ठा bpf_prog_info),
			  env.jit_enabled,
			  prog_infos[i].jited_prog_len,
			  prog_infos[i].xlated_prog_len,
			  !!स_भेद(jited_insns, zeros, माप(zeros)),
			  !!स_भेद(xlated_insns, zeros, माप(zeros)),
			  load_समय, now,
			  prog_infos[i].created_by_uid, my_uid,
			  prog_infos[i].nr_map_ids, 1,
			  *(पूर्णांक *)(दीर्घ)prog_infos[i].map_ids, map_infos[i].id,
			  prog_infos[i].name, expected_prog_name))
			जाओ करोne;

		/* Check getting link info */
		info_len = माप(काष्ठा bpf_link_info) * 2;
		bzero(&link_infos[i], info_len);
		link_infos[i].raw_tracepoपूर्णांक.tp_name = ptr_to_u64(&tp_name);
		link_infos[i].raw_tracepoपूर्णांक.tp_name_len = माप(tp_name);
		err = bpf_obj_get_info_by_fd(bpf_link__fd(links[i]),
					     &link_infos[i], &info_len);
		अगर (CHECK(err ||
			  link_infos[i].type != BPF_LINK_TYPE_RAW_TRACEPOINT ||
			  link_infos[i].prog_id != prog_infos[i].id ||
			  link_infos[i].raw_tracepoपूर्णांक.tp_name != ptr_to_u64(&tp_name) ||
			  म_भेद(u64_to_ptr(link_infos[i].raw_tracepoपूर्णांक.tp_name),
				 "sys_enter") ||
			  info_len != माप(काष्ठा bpf_link_info),
			  "get-link-info(fd)",
			  "err %d errno %d info_len %u(%zu) type %d(%d) id %d "
			  "prog_id %d (%d) tp_name %s(%s)\n",
			  err, त्रुटि_सं,
			  info_len, माप(काष्ठा bpf_link_info),
			  link_infos[i].type, BPF_LINK_TYPE_RAW_TRACEPOINT,
			  link_infos[i].id,
			  link_infos[i].prog_id, prog_infos[i].id,
			  (स्थिर अक्षर *)u64_to_ptr(link_infos[i].raw_tracepoपूर्णांक.tp_name),
			  "sys_enter"))
			जाओ करोne;

	पूर्ण

	/* Check bpf_prog_get_next_id() */
	nr_id_found = 0;
	next_id = 0;
	जबतक (!bpf_prog_get_next_id(next_id, &next_id)) अणु
		काष्ठा bpf_prog_info prog_info = अणुपूर्ण;
		__u32 saved_map_id;
		पूर्णांक prog_fd;

		info_len = माप(prog_info);

		prog_fd = bpf_prog_get_fd_by_id(next_id);
		अगर (prog_fd < 0 && त्रुटि_सं == ENOENT)
			/* The bpf_prog is in the dead row */
			जारी;
		अगर (CHECK(prog_fd < 0, "get-prog-fd(next_id)",
			  "prog_fd %d next_id %d errno %d\n",
			  prog_fd, next_id, त्रुटि_सं))
			अवरोध;

		क्रम (i = 0; i < nr_iters; i++)
			अगर (prog_infos[i].id == next_id)
				अवरोध;

		अगर (i == nr_iters)
			जारी;

		nr_id_found++;

		/* Negative test:
		 * prog_info.nr_map_ids = 1
		 * prog_info.map_ids = शून्य
		 */
		prog_info.nr_map_ids = 1;
		err = bpf_obj_get_info_by_fd(prog_fd, &prog_info, &info_len);
		अगर (CHECK(!err || त्रुटि_सं != EFAULT,
			  "get-prog-fd-bad-nr-map-ids", "err %d errno %d(%d)",
			  err, त्रुटि_सं, EFAULT))
			अवरोध;
		bzero(&prog_info, माप(prog_info));
		info_len = माप(prog_info);

		saved_map_id = *(पूर्णांक *)((दीर्घ)prog_infos[i].map_ids);
		prog_info.map_ids = prog_infos[i].map_ids;
		prog_info.nr_map_ids = 2;
		err = bpf_obj_get_info_by_fd(prog_fd, &prog_info, &info_len);
		prog_infos[i].jited_prog_insns = 0;
		prog_infos[i].xlated_prog_insns = 0;
		CHECK(err || info_len != माप(काष्ठा bpf_prog_info) ||
		      स_भेद(&prog_info, &prog_infos[i], info_len) ||
		      *(पूर्णांक *)(दीर्घ)prog_info.map_ids != saved_map_id,
		      "get-prog-info(next_id->fd)",
		      "err %d errno %d info_len %u(%zu) memcmp %d map_id %u(%u)\n",
		      err, त्रुटि_सं, info_len, माप(काष्ठा bpf_prog_info),
		      स_भेद(&prog_info, &prog_infos[i], info_len),
		      *(पूर्णांक *)(दीर्घ)prog_info.map_ids, saved_map_id);
		बंद(prog_fd);
	पूर्ण
	CHECK(nr_id_found != nr_iters,
	      "check total prog id found by get_next_id",
	      "nr_id_found %u(%u)\n",
	      nr_id_found, nr_iters);

	/* Check bpf_map_get_next_id() */
	nr_id_found = 0;
	next_id = 0;
	जबतक (!bpf_map_get_next_id(next_id, &next_id)) अणु
		काष्ठा bpf_map_info map_info = अणुपूर्ण;
		पूर्णांक map_fd;

		info_len = माप(map_info);

		map_fd = bpf_map_get_fd_by_id(next_id);
		अगर (map_fd < 0 && त्रुटि_सं == ENOENT)
			/* The bpf_map is in the dead row */
			जारी;
		अगर (CHECK(map_fd < 0, "get-map-fd(next_id)",
			  "map_fd %d next_id %u errno %d\n",
			  map_fd, next_id, त्रुटि_सं))
			अवरोध;

		क्रम (i = 0; i < nr_iters; i++)
			अगर (map_infos[i].id == next_id)
				अवरोध;

		अगर (i == nr_iters)
			जारी;

		nr_id_found++;

		err = bpf_map_lookup_elem(map_fd, &array_key, &array_value);
		अगर (CHECK_FAIL(err))
			जाओ करोne;

		err = bpf_obj_get_info_by_fd(map_fd, &map_info, &info_len);
		CHECK(err || info_len != माप(काष्ठा bpf_map_info) ||
		      स_भेद(&map_info, &map_infos[i], info_len) ||
		      array_value != array_magic_value,
		      "check get-map-info(next_id->fd)",
		      "err %d errno %d info_len %u(%zu) memcmp %d array_value %llu(%llu)\n",
		      err, त्रुटि_सं, info_len, माप(काष्ठा bpf_map_info),
		      स_भेद(&map_info, &map_infos[i], info_len),
		      array_value, array_magic_value);

		बंद(map_fd);
	पूर्ण
	CHECK(nr_id_found != nr_iters,
	      "check total map id found by get_next_id",
	      "nr_id_found %u(%u)\n",
	      nr_id_found, nr_iters);

	/* Check bpf_link_get_next_id() */
	nr_id_found = 0;
	next_id = 0;
	जबतक (!bpf_link_get_next_id(next_id, &next_id)) अणु
		काष्ठा bpf_link_info link_info;
		पूर्णांक link_fd, cmp_res;

		info_len = माप(link_info);
		स_रखो(&link_info, 0, info_len);

		link_fd = bpf_link_get_fd_by_id(next_id);
		अगर (link_fd < 0 && त्रुटि_सं == ENOENT)
			/* The bpf_link is in the dead row */
			जारी;
		अगर (CHECK(link_fd < 0, "get-link-fd(next_id)",
			  "link_fd %d next_id %u errno %d\n",
			  link_fd, next_id, त्रुटि_सं))
			अवरोध;

		क्रम (i = 0; i < nr_iters; i++)
			अगर (link_infos[i].id == next_id)
				अवरोध;

		अगर (i == nr_iters)
			जारी;

		nr_id_found++;

		err = bpf_obj_get_info_by_fd(link_fd, &link_info, &info_len);
		cmp_res = स_भेद(&link_info, &link_infos[i],
				दुरत्व(काष्ठा bpf_link_info, raw_tracepoपूर्णांक));
		CHECK(err || info_len != माप(link_info) || cmp_res,
		      "check get-link-info(next_id->fd)",
		      "err %d errno %d info_len %u(%zu) memcmp %d\n",
		      err, त्रुटि_सं, info_len, माप(काष्ठा bpf_link_info),
		      cmp_res);

		बंद(link_fd);
	पूर्ण
	CHECK(nr_id_found != nr_iters,
	      "check total link id found by get_next_id",
	      "nr_id_found %u(%u)\n", nr_id_found, nr_iters);

करोne:
	क्रम (i = 0; i < nr_iters; i++) अणु
		bpf_link__destroy(links[i]);
		bpf_object__बंद(objs[i]);
	पूर्ण
पूर्ण
