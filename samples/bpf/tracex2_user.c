<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <sys/resource.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "bpf_util.h"

#घोषणा MAX_INDEX	64
#घोषणा MAX_STARS	38

/* my_map, my_hist_map */
अटल पूर्णांक map_fd[2];

अटल व्योम stars(अक्षर *str, दीर्घ val, दीर्घ max, पूर्णांक width)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (width * val / max) - 1 && i < width - 1; i++)
		str[i] = '*';
	अगर (val > max)
		str[i - 1] = '+';
	str[i] = '\0';
पूर्ण

काष्ठा task अणु
	अक्षर comm[16];
	__u64 pid_tgid;
	__u64 uid_gid;
पूर्ण;

काष्ठा hist_key अणु
	काष्ठा task t;
	__u32 index;
पूर्ण;

#घोषणा SIZE माप(काष्ठा task)

अटल व्योम prपूर्णांक_hist_क्रम_pid(पूर्णांक fd, व्योम *task)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	काष्ठा hist_key key = अणुपूर्ण, next_key;
	दीर्घ values[nr_cpus];
	अक्षर starstr[MAX_STARS];
	दीर्घ value;
	दीर्घ data[MAX_INDEX] = अणुपूर्ण;
	पूर्णांक max_ind = -1;
	दीर्घ max_value = 0;
	पूर्णांक i, ind;

	जबतक (bpf_map_get_next_key(fd, &key, &next_key) == 0) अणु
		अगर (स_भेद(&next_key, task, SIZE)) अणु
			key = next_key;
			जारी;
		पूर्ण
		bpf_map_lookup_elem(fd, &next_key, values);
		value = 0;
		क्रम (i = 0; i < nr_cpus; i++)
			value += values[i];
		ind = next_key.index;
		data[ind] = value;
		अगर (value && ind > max_ind)
			max_ind = ind;
		अगर (value > max_value)
			max_value = value;
		key = next_key;
	पूर्ण

	म_लिखो("           syscall write() stats\n");
	म_लिखो("     byte_size       : count     distribution\n");
	क्रम (i = 1; i <= max_ind + 1; i++) अणु
		stars(starstr, data[i - 1], max_value, MAX_STARS);
		म_लिखो("%8ld -> %-8ld : %-8ld |%-*s|\n",
		       (1l << i) >> 1, (1l << i) - 1, data[i - 1],
		       MAX_STARS, starstr);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_hist(पूर्णांक fd)
अणु
	काष्ठा hist_key key = अणुपूर्ण, next_key;
	अटल काष्ठा task tasks[1024];
	पूर्णांक task_cnt = 0;
	पूर्णांक i;

	जबतक (bpf_map_get_next_key(fd, &key, &next_key) == 0) अणु
		पूर्णांक found = 0;

		क्रम (i = 0; i < task_cnt; i++)
			अगर (स_भेद(&tasks[i], &next_key, SIZE) == 0)
				found = 1;
		अगर (!found)
			स_नकल(&tasks[task_cnt++], &next_key, SIZE);
		key = next_key;
	पूर्ण

	क्रम (i = 0; i < task_cnt; i++) अणु
		म_लिखो("\npid %d cmd %s uid %d\n",
		       (__u32) tasks[i].pid_tgid,
		       tasks[i].comm,
		       (__u32) tasks[i].uid_gid);
		prपूर्णांक_hist_क्रम_pid(fd, &tasks[i]);
	पूर्ण

पूर्ण

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	prपूर्णांक_hist(map_fd[1]);
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **argv)
अणु
	दीर्घ key, next_key, value;
	काष्ठा bpf_link *links[2];
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	पूर्णांक i, j = 0;
	खाता *f;

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

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "my_map");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "my_hist_map");
	अगर (map_fd[0] < 0 || map_fd[1] < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	/* start 'ping' in the background to have some kमुक्त_skb events */
	f = pखोलो("ping -4 -c5 localhost", "r");
	(व्योम) f;

	/* start 'dd' in the background to have plenty of 'write' syscalls */
	f = pखोलो("dd if=/dev/zero of=/dev/null count=5000000", "r");
	(व्योम) f;

	bpf_object__क्रम_each_program(prog, obj) अणु
		links[j] = bpf_program__attach(prog);
		अगर (libbpf_get_error(links[j])) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
			links[j] = शून्य;
			जाओ cleanup;
		पूर्ण
		j++;
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		key = 0;
		जबतक (bpf_map_get_next_key(map_fd[0], &key, &next_key) == 0) अणु
			bpf_map_lookup_elem(map_fd[0], &next_key, &value);
			म_लिखो("location 0x%lx count %ld\n", next_key, value);
			key = next_key;
		पूर्ण
		अगर (key)
			म_लिखो("\n");
		sleep(1);
	पूर्ण
	prपूर्णांक_hist(map_fd[1]);

cleanup:
	क्रम (j--; j >= 0; j--)
		bpf_link__destroy(links[j]);

	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
