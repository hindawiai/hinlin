<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <sys/resource.h>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>
#समावेश "trace_helpers.h"

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **argv)
अणु
	अक्षर filename[256], symbol[256];
	काष्ठा bpf_object *obj = शून्य;
	काष्ठा bpf_link *links[20];
	दीर्घ key, next_key, value;
	काष्ठा bpf_program *prog;
	पूर्णांक map_fd, i, j = 0;
	स्थिर अक्षर *section;
	काष्ठा ksym *sym;

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

	map_fd = bpf_object__find_map_fd_by_name(obj, "my_map");
	अगर (map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		section = bpf_program__section_name(prog);
		अगर (माला_पूछो(section, "kprobe/%s", symbol) != 1)
			जारी;

		/* Attach prog only when symbol exists */
		अगर (ksym_get_addr(symbol)) अणु
			links[j] = bpf_program__attach(prog);
			अगर (libbpf_get_error(links[j])) अणु
				ख_लिखो(मानक_त्रुटि, "bpf_program__attach failed\n");
				links[j] = शून्य;
				जाओ cleanup;
			पूर्ण
			j++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		key = 0;
		म_लिखो("kprobing funcs:");
		जबतक (bpf_map_get_next_key(map_fd, &key, &next_key) == 0) अणु
			bpf_map_lookup_elem(map_fd, &next_key, &value);
			निश्चित(next_key == value);
			sym = ksym_search(value);
			key = next_key;
			अगर (!sym) अणु
				म_लिखो("ksym not found. Is kallsyms loaded?\n");
				जारी;
			पूर्ण

			म_लिखो(" %s", sym->name);
		पूर्ण
		अगर (key)
			म_लिखो("\n");
		key = 0;
		जबतक (bpf_map_get_next_key(map_fd, &key, &next_key) == 0)
			bpf_map_delete_elem(map_fd, &next_key);
		sleep(1);
	पूर्ण

cleanup:
	क्रम (j--; j >= 0; j--)
		bpf_link__destroy(links[j]);

	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
