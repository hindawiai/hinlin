<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <test_progs.h>
#समावेश "bpf_iter_ipv6_route.skel.h"
#समावेश "bpf_iter_netlink.skel.h"
#समावेश "bpf_iter_bpf_map.skel.h"
#समावेश "bpf_iter_task.skel.h"
#समावेश "bpf_iter_task_stack.skel.h"
#समावेश "bpf_iter_task_file.skel.h"
#समावेश "bpf_iter_task_vma.skel.h"
#समावेश "bpf_iter_task_btf.skel.h"
#समावेश "bpf_iter_tcp4.skel.h"
#समावेश "bpf_iter_tcp6.skel.h"
#समावेश "bpf_iter_udp4.skel.h"
#समावेश "bpf_iter_udp6.skel.h"
#समावेश "bpf_iter_test_kern1.skel.h"
#समावेश "bpf_iter_test_kern2.skel.h"
#समावेश "bpf_iter_test_kern3.skel.h"
#समावेश "bpf_iter_test_kern4.skel.h"
#समावेश "bpf_iter_bpf_hash_map.skel.h"
#समावेश "bpf_iter_bpf_percpu_hash_map.skel.h"
#समावेश "bpf_iter_bpf_array_map.skel.h"
#समावेश "bpf_iter_bpf_percpu_array_map.skel.h"
#समावेश "bpf_iter_bpf_sk_storage_helpers.skel.h"
#समावेश "bpf_iter_bpf_sk_storage_map.skel.h"
#समावेश "bpf_iter_test_kern5.skel.h"
#समावेश "bpf_iter_test_kern6.skel.h"

अटल पूर्णांक duration;

अटल व्योम test_btf_id_or_null(व्योम)
अणु
	काष्ठा bpf_iter_test_kern3 *skel;

	skel = bpf_iter_test_kern3__खोलो_and_load();
	अगर (CHECK(skel, "bpf_iter_test_kern3__open_and_load",
		  "skeleton open_and_load unexpectedly succeeded\n")) अणु
		bpf_iter_test_kern3__destroy(skel);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम करो_dummy_पढ़ो(काष्ठा bpf_program *prog)
अणु
	काष्ठा bpf_link *link;
	अक्षर buf[16] = अणुपूर्ण;
	पूर्णांक iter_fd, len;

	link = bpf_program__attach_iter(prog, शून्य);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		वापस;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	/* not check contents, but ensure पढ़ो() ends without error */
	जबतक ((len = पढ़ो(iter_fd, buf, माप(buf))) > 0)
		;
	CHECK(len < 0, "read", "read failed: %s\n", म_त्रुटि(त्रुटि_सं));

	बंद(iter_fd);

मुक्त_link:
	bpf_link__destroy(link);
पूर्ण

अटल पूर्णांक पढ़ो_fd_पूर्णांकo_buffer(पूर्णांक fd, अक्षर *buf, पूर्णांक size)
अणु
	पूर्णांक bufleft = size;
	पूर्णांक len;

	करो अणु
		len = पढ़ो(fd, buf, bufleft);
		अगर (len > 0) अणु
			buf += len;
			bufleft -= len;
		पूर्ण
	पूर्ण जबतक (len > 0);

	वापस len < 0 ? len : size - bufleft;
पूर्ण

अटल व्योम test_ipv6_route(व्योम)
अणु
	काष्ठा bpf_iter_ipv6_route *skel;

	skel = bpf_iter_ipv6_route__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_ipv6_route__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	करो_dummy_पढ़ो(skel->progs.dump_ipv6_route);

	bpf_iter_ipv6_route__destroy(skel);
पूर्ण

अटल व्योम test_netlink(व्योम)
अणु
	काष्ठा bpf_iter_netlink *skel;

	skel = bpf_iter_netlink__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_netlink__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	करो_dummy_पढ़ो(skel->progs.dump_netlink);

	bpf_iter_netlink__destroy(skel);
पूर्ण

अटल व्योम test_bpf_map(व्योम)
अणु
	काष्ठा bpf_iter_bpf_map *skel;

	skel = bpf_iter_bpf_map__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_bpf_map__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	करो_dummy_पढ़ो(skel->progs.dump_bpf_map);

	bpf_iter_bpf_map__destroy(skel);
पूर्ण

अटल व्योम test_task(व्योम)
अणु
	काष्ठा bpf_iter_task *skel;

	skel = bpf_iter_task__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_task__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	करो_dummy_पढ़ो(skel->progs.dump_task);

	bpf_iter_task__destroy(skel);
पूर्ण

अटल व्योम test_task_stack(व्योम)
अणु
	काष्ठा bpf_iter_task_stack *skel;

	skel = bpf_iter_task_stack__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_task_stack__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	करो_dummy_पढ़ो(skel->progs.dump_task_stack);
	करो_dummy_पढ़ो(skel->progs.get_task_user_stacks);

	bpf_iter_task_stack__destroy(skel);
पूर्ण

अटल व्योम *करो_nothing(व्योम *arg)
अणु
	pthपढ़ो_निकास(arg);
पूर्ण

अटल व्योम test_task_file(व्योम)
अणु
	काष्ठा bpf_iter_task_file *skel;
	pthपढ़ो_t thपढ़ो_id;
	व्योम *ret;

	skel = bpf_iter_task_file__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_task_file__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	skel->bss->tgid = getpid();

	अगर (CHECK(pthपढ़ो_create(&thपढ़ो_id, शून्य, &करो_nothing, शून्य),
		  "pthread_create", "pthread_create failed\n"))
		जाओ करोne;

	करो_dummy_पढ़ो(skel->progs.dump_task_file);

	अगर (CHECK(pthपढ़ो_join(thपढ़ो_id, &ret) || ret != शून्य,
		  "pthread_join", "pthread_join failed\n"))
		जाओ करोne;

	CHECK(skel->bss->count != 0, "check_count",
	      "invalid non pthread file visit count %d\n", skel->bss->count);

करोne:
	bpf_iter_task_file__destroy(skel);
पूर्ण

#घोषणा TASKBUFSZ		32768

अटल अक्षर taskbuf[TASKBUFSZ];

अटल पूर्णांक करो_btf_पढ़ो(काष्ठा bpf_iter_task_btf *skel)
अणु
	काष्ठा bpf_program *prog = skel->progs.dump_task_काष्ठा;
	काष्ठा bpf_iter_task_btf__bss *bss = skel->bss;
	पूर्णांक iter_fd = -1, err;
	काष्ठा bpf_link *link;
	अक्षर *buf = taskbuf;
	पूर्णांक ret = 0;

	link = bpf_program__attach_iter(prog, शून्य);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		वापस ret;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	err = पढ़ो_fd_पूर्णांकo_buffer(iter_fd, buf, TASKBUFSZ);
	अगर (bss->skip) अणु
		म_लिखो("%s:SKIP:no __builtin_btf_type_id\n", __func__);
		ret = 1;
		test__skip();
		जाओ मुक्त_link;
	पूर्ण

	अगर (CHECK(err < 0, "read", "read failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ मुक्त_link;

	CHECK(म_माला(taskbuf, "(struct task_struct)") == शून्य,
	      "check for btf representation of task_struct in iter data",
	      "struct task_struct not found");
मुक्त_link:
	अगर (iter_fd > 0)
		बंद(iter_fd);
	bpf_link__destroy(link);
	वापस ret;
पूर्ण

अटल व्योम test_task_btf(व्योम)
अणु
	काष्ठा bpf_iter_task_btf__bss *bss;
	काष्ठा bpf_iter_task_btf *skel;
	पूर्णांक ret;

	skel = bpf_iter_task_btf__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_task_btf__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	bss = skel->bss;

	ret = करो_btf_पढ़ो(skel);
	अगर (ret)
		जाओ cleanup;

	अगर (CHECK(bss->tasks == 0, "check if iterated over tasks",
		  "no task iteration, did BPF program run?\n"))
		जाओ cleanup;

	CHECK(bss->seq_err != 0, "check for unexpected err",
	      "bpf_seq_printf_btf returned %ld", bss->seq_err);

cleanup:
	bpf_iter_task_btf__destroy(skel);
पूर्ण

अटल व्योम test_tcp4(व्योम)
अणु
	काष्ठा bpf_iter_tcp4 *skel;

	skel = bpf_iter_tcp4__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_tcp4__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	करो_dummy_पढ़ो(skel->progs.dump_tcp4);

	bpf_iter_tcp4__destroy(skel);
पूर्ण

अटल व्योम test_tcp6(व्योम)
अणु
	काष्ठा bpf_iter_tcp6 *skel;

	skel = bpf_iter_tcp6__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_tcp6__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	करो_dummy_पढ़ो(skel->progs.dump_tcp6);

	bpf_iter_tcp6__destroy(skel);
पूर्ण

अटल व्योम test_udp4(व्योम)
अणु
	काष्ठा bpf_iter_udp4 *skel;

	skel = bpf_iter_udp4__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_udp4__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	करो_dummy_पढ़ो(skel->progs.dump_udp4);

	bpf_iter_udp4__destroy(skel);
पूर्ण

अटल व्योम test_udp6(व्योम)
अणु
	काष्ठा bpf_iter_udp6 *skel;

	skel = bpf_iter_udp6__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_udp6__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	करो_dummy_पढ़ो(skel->progs.dump_udp6);

	bpf_iter_udp6__destroy(skel);
पूर्ण

/* The expected string is less than 16 bytes */
अटल पूर्णांक करो_पढ़ो_with_fd(पूर्णांक iter_fd, स्थिर अक्षर *expected,
			   bool पढ़ो_one_अक्षर)
अणु
	पूर्णांक err = -1, len, पढ़ो_buf_len, start;
	अक्षर buf[16] = अणुपूर्ण;

	पढ़ो_buf_len = पढ़ो_one_अक्षर ? 1 : 16;
	start = 0;
	जबतक ((len = पढ़ो(iter_fd, buf + start, पढ़ो_buf_len)) > 0) अणु
		start += len;
		अगर (CHECK(start >= 16, "read", "read len %d\n", len))
			वापस -1;
		पढ़ो_buf_len = पढ़ो_one_अक्षर ? 1 : 16 - start;
	पूर्ण
	अगर (CHECK(len < 0, "read", "read failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		वापस -1;

	err = म_भेद(buf, expected);
	अगर (CHECK(err, "read", "incorrect read result: buf %s, expected %s\n",
		  buf, expected))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम test_anon_iter(bool पढ़ो_one_अक्षर)
अणु
	काष्ठा bpf_iter_test_kern1 *skel;
	काष्ठा bpf_link *link;
	पूर्णांक iter_fd, err;

	skel = bpf_iter_test_kern1__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_test_kern1__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	err = bpf_iter_test_kern1__attach(skel);
	अगर (CHECK(err, "bpf_iter_test_kern1__attach",
		  "skeleton attach failed\n")) अणु
		जाओ out;
	पूर्ण

	link = skel->links.dump_task;
	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ out;

	करो_पढ़ो_with_fd(iter_fd, "abcd", पढ़ो_one_अक्षर);
	बंद(iter_fd);

out:
	bpf_iter_test_kern1__destroy(skel);
पूर्ण

अटल पूर्णांक करो_पढ़ो(स्थिर अक्षर *path, स्थिर अक्षर *expected)
अणु
	पूर्णांक err, iter_fd;

	iter_fd = खोलो(path, O_RDONLY);
	अगर (CHECK(iter_fd < 0, "open", "open %s failed: %s\n",
		  path, म_त्रुटि(त्रुटि_सं)))
		वापस -1;

	err = करो_पढ़ो_with_fd(iter_fd, expected, false);
	बंद(iter_fd);
	वापस err;
पूर्ण

अटल व्योम test_file_iter(व्योम)
अणु
	स्थिर अक्षर *path = "/sys/fs/bpf/bpf_iter_test1";
	काष्ठा bpf_iter_test_kern1 *skel1;
	काष्ठा bpf_iter_test_kern2 *skel2;
	काष्ठा bpf_link *link;
	पूर्णांक err;

	skel1 = bpf_iter_test_kern1__खोलो_and_load();
	अगर (CHECK(!skel1, "bpf_iter_test_kern1__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	link = bpf_program__attach_iter(skel1->progs.dump_task, शून्य);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		जाओ out;

	/* unlink this path अगर it exists. */
	unlink(path);

	err = bpf_link__pin(link, path);
	अगर (CHECK(err, "pin_iter", "pin_iter to %s failed: %d\n", path, err))
		जाओ मुक्त_link;

	err = करो_पढ़ो(path, "abcd");
	अगर (err)
		जाओ unlink_path;

	/* file based iterator seems working fine. Let us a link update
	 * of the underlying link and `cat` the iterator again, its content
	 * should change.
	 */
	skel2 = bpf_iter_test_kern2__खोलो_and_load();
	अगर (CHECK(!skel2, "bpf_iter_test_kern2__open_and_load",
		  "skeleton open_and_load failed\n"))
		जाओ unlink_path;

	err = bpf_link__update_program(link, skel2->progs.dump_task);
	अगर (CHECK(err, "update_prog", "update_prog failed\n"))
		जाओ destroy_skel2;

	करो_पढ़ो(path, "ABCD");

destroy_skel2:
	bpf_iter_test_kern2__destroy(skel2);
unlink_path:
	unlink(path);
मुक्त_link:
	bpf_link__destroy(link);
out:
	bpf_iter_test_kern1__destroy(skel1);
पूर्ण

अटल व्योम test_overflow(bool test_e2big_overflow, bool ret1)
अणु
	__u32 map_info_len, total_पढ़ो_len, expected_पढ़ो_len;
	पूर्णांक err, iter_fd, map1_fd, map2_fd, len;
	काष्ठा bpf_map_info map_info = अणुपूर्ण;
	काष्ठा bpf_iter_test_kern4 *skel;
	काष्ठा bpf_link *link;
	__u32 iter_size;
	अक्षर *buf;

	skel = bpf_iter_test_kern4__खोलो();
	अगर (CHECK(!skel, "bpf_iter_test_kern4__open",
		  "skeleton open failed\n"))
		वापस;

	/* create two maps: bpf program will only करो bpf_seq_ग_लिखो
	 * क्रम these two maps. The goal is one map output almost
	 * fills seq_file buffer and then the other will trigger
	 * overflow and needs restart.
	 */
	map1_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, 4, 8, 1, 0);
	अगर (CHECK(map1_fd < 0, "bpf_create_map",
		  "map_creation failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ out;
	map2_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, 4, 8, 1, 0);
	अगर (CHECK(map2_fd < 0, "bpf_create_map",
		  "map_creation failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ मुक्त_map1;

	/* bpf_seq_म_लिखो kernel buffer is 8 pages, so one map
	 * bpf_seq_ग_लिखो will mostly fill it, and the other map
	 * will partially fill and then trigger overflow and need
	 * bpf_seq_पढ़ो restart.
	 */
	iter_size = sysconf(_SC_PAGE_SIZE) << 3;

	अगर (test_e2big_overflow) अणु
		skel->rodata->prपूर्णांक_len = (iter_size + 8) / 8;
		expected_पढ़ो_len = 2 * (iter_size + 8);
	पूर्ण अन्यथा अगर (!ret1) अणु
		skel->rodata->prपूर्णांक_len = (iter_size - 8) / 8;
		expected_पढ़ो_len = 2 * (iter_size - 8);
	पूर्ण अन्यथा अणु
		skel->rodata->prपूर्णांक_len = 1;
		expected_पढ़ो_len = 2 * 8;
	पूर्ण
	skel->rodata->ret1 = ret1;

	अगर (CHECK(bpf_iter_test_kern4__load(skel),
		  "bpf_iter_test_kern4__load", "skeleton load failed\n"))
		जाओ मुक्त_map2;

	/* setup filtering map_id in bpf program */
	map_info_len = माप(map_info);
	err = bpf_obj_get_info_by_fd(map1_fd, &map_info, &map_info_len);
	अगर (CHECK(err, "get_map_info", "get map info failed: %s\n",
		  म_त्रुटि(त्रुटि_सं)))
		जाओ मुक्त_map2;
	skel->bss->map1_id = map_info.id;

	err = bpf_obj_get_info_by_fd(map2_fd, &map_info, &map_info_len);
	अगर (CHECK(err, "get_map_info", "get map info failed: %s\n",
		  म_त्रुटि(त्रुटि_सं)))
		जाओ मुक्त_map2;
	skel->bss->map2_id = map_info.id;

	link = bpf_program__attach_iter(skel->progs.dump_bpf_map, शून्य);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		जाओ मुक्त_map2;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	buf = दो_स्मृति(expected_पढ़ो_len);
	अगर (!buf)
		जाओ बंद_iter;

	/* करो पढ़ो */
	total_पढ़ो_len = 0;
	अगर (test_e2big_overflow) अणु
		जबतक ((len = पढ़ो(iter_fd, buf, expected_पढ़ो_len)) > 0)
			total_पढ़ो_len += len;

		CHECK(len != -1 || त्रुटि_सं != E2BIG, "read",
		      "expected ret -1, errno E2BIG, but get ret %d, error %s\n",
			  len, म_त्रुटि(त्रुटि_सं));
		जाओ मुक्त_buf;
	पूर्ण अन्यथा अगर (!ret1) अणु
		जबतक ((len = पढ़ो(iter_fd, buf, expected_पढ़ो_len)) > 0)
			total_पढ़ो_len += len;

		अगर (CHECK(len < 0, "read", "read failed: %s\n",
			  म_त्रुटि(त्रुटि_सं)))
			जाओ मुक्त_buf;
	पूर्ण अन्यथा अणु
		करो अणु
			len = पढ़ो(iter_fd, buf, expected_पढ़ो_len);
			अगर (len > 0)
				total_पढ़ो_len += len;
		पूर्ण जबतक (len > 0 || len == -EAGAIN);

		अगर (CHECK(len < 0, "read", "read failed: %s\n",
			  म_त्रुटि(त्रुटि_सं)))
			जाओ मुक्त_buf;
	पूर्ण

	अगर (CHECK(total_पढ़ो_len != expected_पढ़ो_len, "read",
		  "total len %u, expected len %u\n", total_पढ़ो_len,
		  expected_पढ़ो_len))
		जाओ मुक्त_buf;

	अगर (CHECK(skel->bss->map1_accessed != 1, "map1_accessed",
		  "expected 1 actual %d\n", skel->bss->map1_accessed))
		जाओ मुक्त_buf;

	अगर (CHECK(skel->bss->map2_accessed != 2, "map2_accessed",
		  "expected 2 actual %d\n", skel->bss->map2_accessed))
		जाओ मुक्त_buf;

	CHECK(skel->bss->map2_seqnum1 != skel->bss->map2_seqnum2,
	      "map2_seqnum", "two different seqnum %lld %lld\n",
	      skel->bss->map2_seqnum1, skel->bss->map2_seqnum2);

मुक्त_buf:
	मुक्त(buf);
बंद_iter:
	बंद(iter_fd);
मुक्त_link:
	bpf_link__destroy(link);
मुक्त_map2:
	बंद(map2_fd);
मुक्त_map1:
	बंद(map1_fd);
out:
	bpf_iter_test_kern4__destroy(skel);
पूर्ण

अटल व्योम test_bpf_hash_map(व्योम)
अणु
	__u32 expected_key_a = 0, expected_key_b = 0, expected_key_c = 0;
	DECLARE_LIBBPF_OPTS(bpf_iter_attach_opts, opts);
	काष्ठा bpf_iter_bpf_hash_map *skel;
	पूर्णांक err, i, len, map_fd, iter_fd;
	जोड़ bpf_iter_link_info linfo;
	__u64 val, expected_val = 0;
	काष्ठा bpf_link *link;
	काष्ठा key_t अणु
		पूर्णांक a;
		पूर्णांक b;
		पूर्णांक c;
	पूर्ण key;
	अक्षर buf[64];

	skel = bpf_iter_bpf_hash_map__खोलो();
	अगर (CHECK(!skel, "bpf_iter_bpf_hash_map__open",
		  "skeleton open failed\n"))
		वापस;

	skel->bss->in_test_mode = true;

	err = bpf_iter_bpf_hash_map__load(skel);
	अगर (CHECK(!skel, "bpf_iter_bpf_hash_map__load",
		  "skeleton load failed\n"))
		जाओ out;

	/* iterator with hashmap2 and hashmap3 should fail */
	स_रखो(&linfo, 0, माप(linfo));
	linfo.map.map_fd = bpf_map__fd(skel->maps.hashmap2);
	opts.link_info = &linfo;
	opts.link_info_len = माप(linfo);
	link = bpf_program__attach_iter(skel->progs.dump_bpf_hash_map, &opts);
	अगर (CHECK(!IS_ERR(link), "attach_iter",
		  "attach_iter for hashmap2 unexpected succeeded\n"))
		जाओ out;

	linfo.map.map_fd = bpf_map__fd(skel->maps.hashmap3);
	link = bpf_program__attach_iter(skel->progs.dump_bpf_hash_map, &opts);
	अगर (CHECK(!IS_ERR(link), "attach_iter",
		  "attach_iter for hashmap3 unexpected succeeded\n"))
		जाओ out;

	/* hashmap1 should be good, update map values here */
	map_fd = bpf_map__fd(skel->maps.hashmap1);
	क्रम (i = 0; i < bpf_map__max_entries(skel->maps.hashmap1); i++) अणु
		key.a = i + 1;
		key.b = i + 2;
		key.c = i + 3;
		val = i + 4;
		expected_key_a += key.a;
		expected_key_b += key.b;
		expected_key_c += key.c;
		expected_val += val;

		err = bpf_map_update_elem(map_fd, &key, &val, BPF_ANY);
		अगर (CHECK(err, "map_update", "map_update failed\n"))
			जाओ out;
	पूर्ण

	linfo.map.map_fd = map_fd;
	link = bpf_program__attach_iter(skel->progs.dump_bpf_hash_map, &opts);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		जाओ out;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	/* करो some tests */
	जबतक ((len = पढ़ो(iter_fd, buf, माप(buf))) > 0)
		;
	अगर (CHECK(len < 0, "read", "read failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ बंद_iter;

	/* test results */
	अगर (CHECK(skel->bss->key_sum_a != expected_key_a,
		  "key_sum_a", "got %u expected %u\n",
		  skel->bss->key_sum_a, expected_key_a))
		जाओ बंद_iter;
	अगर (CHECK(skel->bss->key_sum_b != expected_key_b,
		  "key_sum_b", "got %u expected %u\n",
		  skel->bss->key_sum_b, expected_key_b))
		जाओ बंद_iter;
	अगर (CHECK(skel->bss->val_sum != expected_val,
		  "val_sum", "got %llu expected %llu\n",
		  skel->bss->val_sum, expected_val))
		जाओ बंद_iter;

बंद_iter:
	बंद(iter_fd);
मुक्त_link:
	bpf_link__destroy(link);
out:
	bpf_iter_bpf_hash_map__destroy(skel);
पूर्ण

अटल व्योम test_bpf_percpu_hash_map(व्योम)
अणु
	__u32 expected_key_a = 0, expected_key_b = 0, expected_key_c = 0;
	DECLARE_LIBBPF_OPTS(bpf_iter_attach_opts, opts);
	काष्ठा bpf_iter_bpf_percpu_hash_map *skel;
	पूर्णांक err, i, j, len, map_fd, iter_fd;
	जोड़ bpf_iter_link_info linfo;
	__u32 expected_val = 0;
	काष्ठा bpf_link *link;
	काष्ठा key_t अणु
		पूर्णांक a;
		पूर्णांक b;
		पूर्णांक c;
	पूर्ण key;
	अक्षर buf[64];
	व्योम *val;

	val = दो_स्मृति(8 * bpf_num_possible_cpus());

	skel = bpf_iter_bpf_percpu_hash_map__खोलो();
	अगर (CHECK(!skel, "bpf_iter_bpf_percpu_hash_map__open",
		  "skeleton open failed\n"))
		वापस;

	skel->rodata->num_cpus = bpf_num_possible_cpus();

	err = bpf_iter_bpf_percpu_hash_map__load(skel);
	अगर (CHECK(!skel, "bpf_iter_bpf_percpu_hash_map__load",
		  "skeleton load failed\n"))
		जाओ out;

	/* update map values here */
	map_fd = bpf_map__fd(skel->maps.hashmap1);
	क्रम (i = 0; i < bpf_map__max_entries(skel->maps.hashmap1); i++) अणु
		key.a = i + 1;
		key.b = i + 2;
		key.c = i + 3;
		expected_key_a += key.a;
		expected_key_b += key.b;
		expected_key_c += key.c;

		क्रम (j = 0; j < bpf_num_possible_cpus(); j++) अणु
			*(__u32 *)(val + j * 8) = i + j;
			expected_val += i + j;
		पूर्ण

		err = bpf_map_update_elem(map_fd, &key, val, BPF_ANY);
		अगर (CHECK(err, "map_update", "map_update failed\n"))
			जाओ out;
	पूर्ण

	स_रखो(&linfo, 0, माप(linfo));
	linfo.map.map_fd = map_fd;
	opts.link_info = &linfo;
	opts.link_info_len = माप(linfo);
	link = bpf_program__attach_iter(skel->progs.dump_bpf_percpu_hash_map, &opts);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		जाओ out;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	/* करो some tests */
	जबतक ((len = पढ़ो(iter_fd, buf, माप(buf))) > 0)
		;
	अगर (CHECK(len < 0, "read", "read failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ बंद_iter;

	/* test results */
	अगर (CHECK(skel->bss->key_sum_a != expected_key_a,
		  "key_sum_a", "got %u expected %u\n",
		  skel->bss->key_sum_a, expected_key_a))
		जाओ बंद_iter;
	अगर (CHECK(skel->bss->key_sum_b != expected_key_b,
		  "key_sum_b", "got %u expected %u\n",
		  skel->bss->key_sum_b, expected_key_b))
		जाओ बंद_iter;
	अगर (CHECK(skel->bss->val_sum != expected_val,
		  "val_sum", "got %u expected %u\n",
		  skel->bss->val_sum, expected_val))
		जाओ बंद_iter;

बंद_iter:
	बंद(iter_fd);
मुक्त_link:
	bpf_link__destroy(link);
out:
	bpf_iter_bpf_percpu_hash_map__destroy(skel);
पूर्ण

अटल व्योम test_bpf_array_map(व्योम)
अणु
	__u64 val, expected_val = 0, res_first_val, first_val = 0;
	DECLARE_LIBBPF_OPTS(bpf_iter_attach_opts, opts);
	__u32 expected_key = 0, res_first_key;
	काष्ठा bpf_iter_bpf_array_map *skel;
	जोड़ bpf_iter_link_info linfo;
	पूर्णांक err, i, map_fd, iter_fd;
	काष्ठा bpf_link *link;
	अक्षर buf[64] = अणुपूर्ण;
	पूर्णांक len, start;

	skel = bpf_iter_bpf_array_map__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_bpf_array_map__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	map_fd = bpf_map__fd(skel->maps.arraymap1);
	क्रम (i = 0; i < bpf_map__max_entries(skel->maps.arraymap1); i++) अणु
		val = i + 4;
		expected_key += i;
		expected_val += val;

		अगर (i == 0)
			first_val = val;

		err = bpf_map_update_elem(map_fd, &i, &val, BPF_ANY);
		अगर (CHECK(err, "map_update", "map_update failed\n"))
			जाओ out;
	पूर्ण

	स_रखो(&linfo, 0, माप(linfo));
	linfo.map.map_fd = map_fd;
	opts.link_info = &linfo;
	opts.link_info_len = माप(linfo);
	link = bpf_program__attach_iter(skel->progs.dump_bpf_array_map, &opts);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		जाओ out;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	/* करो some tests */
	start = 0;
	जबतक ((len = पढ़ो(iter_fd, buf + start, माप(buf) - start)) > 0)
		start += len;
	अगर (CHECK(len < 0, "read", "read failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ बंद_iter;

	/* test results */
	res_first_key = *(__u32 *)buf;
	res_first_val = *(__u64 *)(buf + माप(__u32));
	अगर (CHECK(res_first_key != 0 || res_first_val != first_val,
		  "bpf_seq_write",
		  "seq_write failure: first key %u vs expected 0, "
		  " first value %llu vs expected %llu\n",
		  res_first_key, res_first_val, first_val))
		जाओ बंद_iter;

	अगर (CHECK(skel->bss->key_sum != expected_key,
		  "key_sum", "got %u expected %u\n",
		  skel->bss->key_sum, expected_key))
		जाओ बंद_iter;
	अगर (CHECK(skel->bss->val_sum != expected_val,
		  "val_sum", "got %llu expected %llu\n",
		  skel->bss->val_sum, expected_val))
		जाओ बंद_iter;

	क्रम (i = 0; i < bpf_map__max_entries(skel->maps.arraymap1); i++) अणु
		err = bpf_map_lookup_elem(map_fd, &i, &val);
		अगर (CHECK(err, "map_lookup", "map_lookup failed\n"))
			जाओ out;
		अगर (CHECK(i != val, "invalid_val",
			  "got value %llu expected %u\n", val, i))
			जाओ out;
	पूर्ण

बंद_iter:
	बंद(iter_fd);
मुक्त_link:
	bpf_link__destroy(link);
out:
	bpf_iter_bpf_array_map__destroy(skel);
पूर्ण

अटल व्योम test_bpf_percpu_array_map(व्योम)
अणु
	DECLARE_LIBBPF_OPTS(bpf_iter_attach_opts, opts);
	काष्ठा bpf_iter_bpf_percpu_array_map *skel;
	__u32 expected_key = 0, expected_val = 0;
	जोड़ bpf_iter_link_info linfo;
	पूर्णांक err, i, j, map_fd, iter_fd;
	काष्ठा bpf_link *link;
	अक्षर buf[64];
	व्योम *val;
	पूर्णांक len;

	val = दो_स्मृति(8 * bpf_num_possible_cpus());

	skel = bpf_iter_bpf_percpu_array_map__खोलो();
	अगर (CHECK(!skel, "bpf_iter_bpf_percpu_array_map__open",
		  "skeleton open failed\n"))
		वापस;

	skel->rodata->num_cpus = bpf_num_possible_cpus();

	err = bpf_iter_bpf_percpu_array_map__load(skel);
	अगर (CHECK(!skel, "bpf_iter_bpf_percpu_array_map__load",
		  "skeleton load failed\n"))
		जाओ out;

	/* update map values here */
	map_fd = bpf_map__fd(skel->maps.arraymap1);
	क्रम (i = 0; i < bpf_map__max_entries(skel->maps.arraymap1); i++) अणु
		expected_key += i;

		क्रम (j = 0; j < bpf_num_possible_cpus(); j++) अणु
			*(__u32 *)(val + j * 8) = i + j;
			expected_val += i + j;
		पूर्ण

		err = bpf_map_update_elem(map_fd, &i, val, BPF_ANY);
		अगर (CHECK(err, "map_update", "map_update failed\n"))
			जाओ out;
	पूर्ण

	स_रखो(&linfo, 0, माप(linfo));
	linfo.map.map_fd = map_fd;
	opts.link_info = &linfo;
	opts.link_info_len = माप(linfo);
	link = bpf_program__attach_iter(skel->progs.dump_bpf_percpu_array_map, &opts);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		जाओ out;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	/* करो some tests */
	जबतक ((len = पढ़ो(iter_fd, buf, माप(buf))) > 0)
		;
	अगर (CHECK(len < 0, "read", "read failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ बंद_iter;

	/* test results */
	अगर (CHECK(skel->bss->key_sum != expected_key,
		  "key_sum", "got %u expected %u\n",
		  skel->bss->key_sum, expected_key))
		जाओ बंद_iter;
	अगर (CHECK(skel->bss->val_sum != expected_val,
		  "val_sum", "got %u expected %u\n",
		  skel->bss->val_sum, expected_val))
		जाओ बंद_iter;

बंद_iter:
	बंद(iter_fd);
मुक्त_link:
	bpf_link__destroy(link);
out:
	bpf_iter_bpf_percpu_array_map__destroy(skel);
पूर्ण

/* An iterator program deletes all local storage in a map. */
अटल व्योम test_bpf_sk_storage_delete(व्योम)
अणु
	DECLARE_LIBBPF_OPTS(bpf_iter_attach_opts, opts);
	काष्ठा bpf_iter_bpf_sk_storage_helpers *skel;
	जोड़ bpf_iter_link_info linfo;
	पूर्णांक err, len, map_fd, iter_fd;
	काष्ठा bpf_link *link;
	पूर्णांक sock_fd = -1;
	__u32 val = 42;
	अक्षर buf[64];

	skel = bpf_iter_bpf_sk_storage_helpers__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_bpf_sk_storage_helpers__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	map_fd = bpf_map__fd(skel->maps.sk_stg_map);

	sock_fd = socket(AF_INET6, SOCK_STREAM, 0);
	अगर (CHECK(sock_fd < 0, "socket", "errno: %d\n", त्रुटि_सं))
		जाओ out;
	err = bpf_map_update_elem(map_fd, &sock_fd, &val, BPF_NOEXIST);
	अगर (CHECK(err, "map_update", "map_update failed\n"))
		जाओ out;

	स_रखो(&linfo, 0, माप(linfo));
	linfo.map.map_fd = map_fd;
	opts.link_info = &linfo;
	opts.link_info_len = माप(linfo);
	link = bpf_program__attach_iter(skel->progs.delete_bpf_sk_storage_map,
					&opts);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		जाओ out;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	/* करो some tests */
	जबतक ((len = पढ़ो(iter_fd, buf, माप(buf))) > 0)
		;
	अगर (CHECK(len < 0, "read", "read failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ बंद_iter;

	/* test results */
	err = bpf_map_lookup_elem(map_fd, &sock_fd, &val);
	अगर (CHECK(!err || त्रुटि_सं != ENOENT, "bpf_map_lookup_elem",
		  "map value wasn't deleted (err=%d, errno=%d)\n", err, त्रुटि_सं))
		जाओ बंद_iter;

बंद_iter:
	बंद(iter_fd);
मुक्त_link:
	bpf_link__destroy(link);
out:
	अगर (sock_fd >= 0)
		बंद(sock_fd);
	bpf_iter_bpf_sk_storage_helpers__destroy(skel);
पूर्ण

/* This creates a socket and its local storage. It then runs a task_iter BPF
 * program that replaces the existing socket local storage with the tgid of the
 * only task owning a file descriptor to this socket, this process, prog_tests.
 * It then runs a tcp socket iterator that negates the value in the existing
 * socket local storage, the test verअगरies that the resulting value is -pid.
 */
अटल व्योम test_bpf_sk_storage_get(व्योम)
अणु
	काष्ठा bpf_iter_bpf_sk_storage_helpers *skel;
	पूर्णांक err, map_fd, val = -1;
	पूर्णांक sock_fd = -1;

	skel = bpf_iter_bpf_sk_storage_helpers__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_bpf_sk_storage_helpers__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	sock_fd = socket(AF_INET6, SOCK_STREAM, 0);
	अगर (CHECK(sock_fd < 0, "socket", "errno: %d\n", त्रुटि_सं))
		जाओ out;

	err = listen(sock_fd, 1);
	अगर (CHECK(err != 0, "listen", "errno: %d\n", त्रुटि_सं))
		जाओ बंद_socket;

	map_fd = bpf_map__fd(skel->maps.sk_stg_map);

	err = bpf_map_update_elem(map_fd, &sock_fd, &val, BPF_NOEXIST);
	अगर (CHECK(err, "bpf_map_update_elem", "map_update_failed\n"))
		जाओ बंद_socket;

	करो_dummy_पढ़ो(skel->progs.fill_socket_owner);

	err = bpf_map_lookup_elem(map_fd, &sock_fd, &val);
	अगर (CHECK(err || val != getpid(), "bpf_map_lookup_elem",
	    "map value wasn't set correctly (expected %d, got %d, err=%d)\n",
	    getpid(), val, err))
		जाओ बंद_socket;

	करो_dummy_पढ़ो(skel->progs.negate_socket_local_storage);

	err = bpf_map_lookup_elem(map_fd, &sock_fd, &val);
	CHECK(err || val != -getpid(), "bpf_map_lookup_elem",
	      "map value wasn't set correctly (expected %d, got %d, err=%d)\n",
	      -getpid(), val, err);

बंद_socket:
	बंद(sock_fd);
out:
	bpf_iter_bpf_sk_storage_helpers__destroy(skel);
पूर्ण

अटल व्योम test_bpf_sk_storage_map(व्योम)
अणु
	DECLARE_LIBBPF_OPTS(bpf_iter_attach_opts, opts);
	पूर्णांक err, i, len, map_fd, iter_fd, num_sockets;
	काष्ठा bpf_iter_bpf_sk_storage_map *skel;
	जोड़ bpf_iter_link_info linfo;
	पूर्णांक sock_fd[3] = अणु-1, -1, -1पूर्ण;
	__u32 val, expected_val = 0;
	काष्ठा bpf_link *link;
	अक्षर buf[64];

	skel = bpf_iter_bpf_sk_storage_map__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_bpf_sk_storage_map__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	map_fd = bpf_map__fd(skel->maps.sk_stg_map);
	num_sockets = ARRAY_SIZE(sock_fd);
	क्रम (i = 0; i < num_sockets; i++) अणु
		sock_fd[i] = socket(AF_INET6, SOCK_STREAM, 0);
		अगर (CHECK(sock_fd[i] < 0, "socket", "errno: %d\n", त्रुटि_सं))
			जाओ out;

		val = i + 1;
		expected_val += val;

		err = bpf_map_update_elem(map_fd, &sock_fd[i], &val,
					  BPF_NOEXIST);
		अगर (CHECK(err, "map_update", "map_update failed\n"))
			जाओ out;
	पूर्ण

	स_रखो(&linfo, 0, माप(linfo));
	linfo.map.map_fd = map_fd;
	opts.link_info = &linfo;
	opts.link_info_len = माप(linfo);
	link = bpf_program__attach_iter(skel->progs.dump_bpf_sk_storage_map, &opts);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		जाओ out;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	/* करो some tests */
	जबतक ((len = पढ़ो(iter_fd, buf, माप(buf))) > 0)
		;
	अगर (CHECK(len < 0, "read", "read failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ बंद_iter;

	/* test results */
	अगर (CHECK(skel->bss->ipv6_sk_count != num_sockets,
		  "ipv6_sk_count", "got %u expected %u\n",
		  skel->bss->ipv6_sk_count, num_sockets))
		जाओ बंद_iter;

	अगर (CHECK(skel->bss->val_sum != expected_val,
		  "val_sum", "got %u expected %u\n",
		  skel->bss->val_sum, expected_val))
		जाओ बंद_iter;

बंद_iter:
	बंद(iter_fd);
मुक्त_link:
	bpf_link__destroy(link);
out:
	क्रम (i = 0; i < num_sockets; i++) अणु
		अगर (sock_fd[i] >= 0)
			बंद(sock_fd[i]);
	पूर्ण
	bpf_iter_bpf_sk_storage_map__destroy(skel);
पूर्ण

अटल व्योम test_rकरोnly_buf_out_of_bound(व्योम)
अणु
	DECLARE_LIBBPF_OPTS(bpf_iter_attach_opts, opts);
	काष्ठा bpf_iter_test_kern5 *skel;
	जोड़ bpf_iter_link_info linfo;
	काष्ठा bpf_link *link;

	skel = bpf_iter_test_kern5__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_test_kern5__open_and_load",
		  "skeleton open_and_load failed\n"))
		वापस;

	स_रखो(&linfo, 0, माप(linfo));
	linfo.map.map_fd = bpf_map__fd(skel->maps.hashmap1);
	opts.link_info = &linfo;
	opts.link_info_len = माप(linfo);
	link = bpf_program__attach_iter(skel->progs.dump_bpf_hash_map, &opts);
	अगर (CHECK(!IS_ERR(link), "attach_iter", "unexpected success\n"))
		bpf_link__destroy(link);

	bpf_iter_test_kern5__destroy(skel);
पूर्ण

अटल व्योम test_buf_neg_offset(व्योम)
अणु
	काष्ठा bpf_iter_test_kern6 *skel;

	skel = bpf_iter_test_kern6__खोलो_and_load();
	अगर (CHECK(skel, "bpf_iter_test_kern6__open_and_load",
		  "skeleton open_and_load unexpected success\n"))
		bpf_iter_test_kern6__destroy(skel);
पूर्ण

#घोषणा CMP_BUFFER_SIZE 1024
अटल अक्षर task_vma_output[CMP_BUFFER_SIZE];
अटल अक्षर proc_maps_output[CMP_BUFFER_SIZE];

/* हटाओ \0 and \ट from str, and only keep the first line */
अटल व्योम str_strip_first_line(अक्षर *str)
अणु
	अक्षर *dst = str, *src = str;

	करो अणु
		अगर (*src == ' ' || *src == '\t')
			src++;
		अन्यथा
			*(dst++) = *(src++);

	पूर्ण जबतक (*src != '\0' && *src != '\n');

	*dst = '\0';
पूर्ण

#घोषणा min(a, b) ((a) < (b) ? (a) : (b))

अटल व्योम test_task_vma(व्योम)
अणु
	पूर्णांक err, iter_fd = -1, proc_maps_fd = -1;
	काष्ठा bpf_iter_task_vma *skel;
	पूर्णांक len, पढ़ो_size = 4;
	अक्षर maps_path[64];

	skel = bpf_iter_task_vma__खोलो();
	अगर (CHECK(!skel, "bpf_iter_task_vma__open", "skeleton open failed\n"))
		वापस;

	skel->bss->pid = getpid();

	err = bpf_iter_task_vma__load(skel);
	अगर (CHECK(err, "bpf_iter_task_vma__load", "skeleton load failed\n"))
		जाओ out;

	skel->links.proc_maps = bpf_program__attach_iter(
		skel->progs.proc_maps, शून्य);

	अगर (CHECK(IS_ERR(skel->links.proc_maps), "bpf_program__attach_iter",
		  "attach iterator failed\n")) अणु
		skel->links.proc_maps = शून्य;
		जाओ out;
	पूर्ण

	iter_fd = bpf_iter_create(bpf_link__fd(skel->links.proc_maps));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ out;

	/* Read CMP_BUFFER_SIZE (1kB) from bpf_iter. Read in small chunks
	 * to trigger seq_file corner हालs. The expected output is much
	 * दीर्घer than 1kB, so the जबतक loop will terminate.
	 */
	len = 0;
	जबतक (len < CMP_BUFFER_SIZE) अणु
		err = पढ़ो_fd_पूर्णांकo_buffer(iter_fd, task_vma_output + len,
					  min(पढ़ो_size, CMP_BUFFER_SIZE - len));
		अगर (CHECK(err < 0, "read_iter_fd", "read_iter_fd failed\n"))
			जाओ out;
		len += err;
	पूर्ण

	/* पढ़ो CMP_BUFFER_SIZE (1kB) from /proc/pid/maps */
	snम_लिखो(maps_path, 64, "/proc/%u/maps", skel->bss->pid);
	proc_maps_fd = खोलो(maps_path, O_RDONLY);
	अगर (CHECK(proc_maps_fd < 0, "open_proc_maps", "open_proc_maps failed\n"))
		जाओ out;
	err = पढ़ो_fd_पूर्णांकo_buffer(proc_maps_fd, proc_maps_output, CMP_BUFFER_SIZE);
	अगर (CHECK(err < 0, "read_prog_maps_fd", "read_prog_maps_fd failed\n"))
		जाओ out;

	/* strip and compare the first line of the two files */
	str_strip_first_line(task_vma_output);
	str_strip_first_line(proc_maps_output);

	CHECK(म_भेद(task_vma_output, proc_maps_output), "compare_output",
	      "found mismatch\n");
out:
	बंद(proc_maps_fd);
	बंद(iter_fd);
	bpf_iter_task_vma__destroy(skel);
पूर्ण

व्योम test_bpf_iter(व्योम)
अणु
	अगर (test__start_subtest("btf_id_or_null"))
		test_btf_id_or_null();
	अगर (test__start_subtest("ipv6_route"))
		test_ipv6_route();
	अगर (test__start_subtest("netlink"))
		test_netlink();
	अगर (test__start_subtest("bpf_map"))
		test_bpf_map();
	अगर (test__start_subtest("task"))
		test_task();
	अगर (test__start_subtest("task_stack"))
		test_task_stack();
	अगर (test__start_subtest("task_file"))
		test_task_file();
	अगर (test__start_subtest("task_vma"))
		test_task_vma();
	अगर (test__start_subtest("task_btf"))
		test_task_btf();
	अगर (test__start_subtest("tcp4"))
		test_tcp4();
	अगर (test__start_subtest("tcp6"))
		test_tcp6();
	अगर (test__start_subtest("udp4"))
		test_udp4();
	अगर (test__start_subtest("udp6"))
		test_udp6();
	अगर (test__start_subtest("anon"))
		test_anon_iter(false);
	अगर (test__start_subtest("anon-read-one-char"))
		test_anon_iter(true);
	अगर (test__start_subtest("file"))
		test_file_iter();
	अगर (test__start_subtest("overflow"))
		test_overflow(false, false);
	अगर (test__start_subtest("overflow-e2big"))
		test_overflow(true, false);
	अगर (test__start_subtest("prog-ret-1"))
		test_overflow(false, true);
	अगर (test__start_subtest("bpf_hash_map"))
		test_bpf_hash_map();
	अगर (test__start_subtest("bpf_percpu_hash_map"))
		test_bpf_percpu_hash_map();
	अगर (test__start_subtest("bpf_array_map"))
		test_bpf_array_map();
	अगर (test__start_subtest("bpf_percpu_array_map"))
		test_bpf_percpu_array_map();
	अगर (test__start_subtest("bpf_sk_storage_map"))
		test_bpf_sk_storage_map();
	अगर (test__start_subtest("bpf_sk_storage_delete"))
		test_bpf_sk_storage_delete();
	अगर (test__start_subtest("bpf_sk_storage_get"))
		test_bpf_sk_storage_get();
	अगर (test__start_subtest("rdonly-buf-out-of-bound"))
		test_rकरोnly_buf_out_of_bound();
	अगर (test__start_subtest("buf-neg-offset"))
		test_buf_neg_offset();
पूर्ण
