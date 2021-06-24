<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <linux/perf_event.h>
#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <sys/resource.h>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>
#समावेश "trace_helpers.h"

#घोषणा PRINT_RAW_ADDR 0

/* counts, stackmap */
अटल पूर्णांक map_fd[2];

अटल व्योम prपूर्णांक_ksym(__u64 addr)
अणु
	काष्ठा ksym *sym;

	अगर (!addr)
		वापस;
	sym = ksym_search(addr);
	अगर (!sym) अणु
		म_लिखो("ksym not found. Is kallsyms loaded?\n");
		वापस;
	पूर्ण

	अगर (PRINT_RAW_ADDR)
		म_लिखो("%s/%llx;", sym->name, addr);
	अन्यथा
		म_लिखो("%s;", sym->name);
पूर्ण

#घोषणा TASK_COMM_LEN 16

काष्ठा key_t अणु
	अक्षर waker[TASK_COMM_LEN];
	अक्षर target[TASK_COMM_LEN];
	__u32 wret;
	__u32 tret;
पूर्ण;

अटल व्योम prपूर्णांक_stack(काष्ठा key_t *key, __u64 count)
अणु
	__u64 ip[PERF_MAX_STACK_DEPTH] = अणुपूर्ण;
	अटल bool warned;
	पूर्णांक i;

	म_लिखो("%s;", key->target);
	अगर (bpf_map_lookup_elem(map_fd[1], &key->tret, ip) != 0) अणु
		म_लिखो("---;");
	पूर्ण अन्यथा अणु
		क्रम (i = PERF_MAX_STACK_DEPTH - 1; i >= 0; i--)
			prपूर्णांक_ksym(ip[i]);
	पूर्ण
	म_लिखो("-;");
	अगर (bpf_map_lookup_elem(map_fd[1], &key->wret, ip) != 0) अणु
		म_लिखो("---;");
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < PERF_MAX_STACK_DEPTH; i++)
			prपूर्णांक_ksym(ip[i]);
	पूर्ण
	म_लिखो(";%s %lld\n", key->waker, count);

	अगर ((key->tret == -EEXIST || key->wret == -EEXIST) && !warned) अणु
		म_लिखो("stackmap collisions seen. Consider increasing size\n");
		warned = true;
	पूर्ण अन्यथा अगर (((पूर्णांक)(key->tret) < 0 || (पूर्णांक)(key->wret) < 0)) अणु
		म_लिखो("err stackid %d %d\n", key->tret, key->wret);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_stacks(पूर्णांक fd)
अणु
	काष्ठा key_t key = अणुपूर्ण, next_key;
	__u64 value;

	जबतक (bpf_map_get_next_key(fd, &key, &next_key) == 0) अणु
		bpf_map_lookup_elem(fd, &next_key, &value);
		prपूर्णांक_stack(&next_key, value);
		key = next_key;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	prपूर्णांक_stacks(map_fd[0]);
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_object *obj = शून्य;
	काष्ठा bpf_link *links[2];
	काष्ठा bpf_program *prog;
	पूर्णांक delay = 1, i = 0;
	अक्षर filename[256];

	अगर (load_kallsyms()) अणु
		म_लिखो("failed to process /proc/kallsyms\n");
		वापस 2;
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		obj = शून्य;
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "counts");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "stackmap");
	अगर (map_fd[0] < 0 || map_fd[1] < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	bpf_object__क्रम_each_program(prog, obj) अणु
		links[i] = bpf_program__attach(prog);
		अगर (libbpf_get_error(links[i])) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
			links[i] = शून्य;
			जाओ cleanup;
		पूर्ण
		i++;
	पूर्ण

	अगर (argc > 1)
		delay = म_से_प(argv[1]);
	sleep(delay);
	prपूर्णांक_stacks(map_fd[0]);

cleanup:
	क्रम (i--; i >= 0; i--)
		bpf_link__destroy(links[i]);

	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
