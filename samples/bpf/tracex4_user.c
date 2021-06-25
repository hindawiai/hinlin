<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015 PLUMgrid, http://plumgrid.com
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <sys/resource.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

काष्ठा pair अणु
	दीर्घ दीर्घ val;
	__u64 ip;
पूर्ण;

अटल __u64 समय_get_ns(व्योम)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
	वापस ts.tv_sec * 1000000000ull + ts.tv_nsec;
पूर्ण

अटल व्योम prपूर्णांक_old_objects(पूर्णांक fd)
अणु
	दीर्घ दीर्घ val = समय_get_ns();
	__u64 key, next_key;
	काष्ठा pair v;

	key = ग_लिखो(1, "\e[1;1H\e[2J", 12); /* clear screen */

	key = -1;
	जबतक (bpf_map_get_next_key(fd, &key, &next_key) == 0) अणु
		bpf_map_lookup_elem(fd, &next_key, &v);
		key = next_key;
		अगर (val - v.val < 1000000000ll)
			/* object was allocated more then 1 sec ago */
			जारी;
		म_लिखो("obj 0x%llx is %2lldsec old was allocated at ip %llx\n",
		       next_key, (val - v.val) / 1000000000ll, v.ip);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **argv)
अणु
	काष्ठा bpf_link *links[2];
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	पूर्णांक map_fd, i, j = 0;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd = bpf_object__find_map_fd_by_name(obj, "my_map");
	अगर (map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		links[j] = bpf_program__attach(prog);
		अगर (libbpf_get_error(links[j])) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
			links[j] = शून्य;
			जाओ cleanup;
		पूर्ण
		j++;
	पूर्ण

	क्रम (i = 0; ; i++) अणु
		prपूर्णांक_old_objects(map_fd);
		sleep(1);
	पूर्ण

cleanup:
	क्रम (j--; j >= 0; j--)
		bpf_link__destroy(links[j]);

	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
