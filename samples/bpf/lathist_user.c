<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2015 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2015 BMW Car IT GmbH
 */
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>

#घोषणा MAX_ENTRIES	20
#घोषणा MAX_CPU		4
#घोषणा MAX_STARS	40

काष्ठा cpu_hist अणु
	दीर्घ data[MAX_ENTRIES];
	दीर्घ max;
पूर्ण;

अटल काष्ठा cpu_hist cpu_hist[MAX_CPU];

अटल व्योम stars(अक्षर *str, दीर्घ val, दीर्घ max, पूर्णांक width)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (width * val / max) - 1 && i < width - 1; i++)
		str[i] = '*';
	अगर (val > max)
		str[i - 1] = '+';
	str[i] = '\0';
पूर्ण

अटल व्योम prपूर्णांक_hist(व्योम)
अणु
	अक्षर starstr[MAX_STARS];
	काष्ठा cpu_hist *hist;
	पूर्णांक i, j;

	/* clear screen */
	म_लिखो("\033[2J");

	क्रम (j = 0; j < MAX_CPU; j++) अणु
		hist = &cpu_hist[j];

		/* ignore CPUs without data (maybe offline?) */
		अगर (hist->max == 0)
			जारी;

		म_लिखो("CPU %d\n", j);
		म_लिखो("      latency        : count     distribution\n");
		क्रम (i = 1; i <= MAX_ENTRIES; i++) अणु
			stars(starstr, hist->data[i - 1], hist->max, MAX_STARS);
			म_लिखो("%8ld -> %-8ld : %-8ld |%-*s|\n",
				(1l << i) >> 1, (1l << i) - 1,
				hist->data[i - 1], MAX_STARS, starstr);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_data(पूर्णांक fd)
अणु
	दीर्घ key, value;
	पूर्णांक c, i;

	क्रम (i = 0; i < MAX_CPU; i++)
		cpu_hist[i].max = 0;

	क्रम (c = 0; c < MAX_CPU; c++) अणु
		क्रम (i = 0; i < MAX_ENTRIES; i++) अणु
			key = c * MAX_ENTRIES + i;
			bpf_map_lookup_elem(fd, &key, &value);

			cpu_hist[c].data[i] = value;
			अगर (value > cpu_hist[c].max)
				cpu_hist[c].max = value;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_link *links[2];
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	पूर्णांक map_fd, i = 0;

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

	map_fd = bpf_object__find_map_fd_by_name(obj, "my_lat");
	अगर (map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		links[i] = bpf_program__attach(prog);
		अगर (libbpf_get_error(links[i])) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
			links[i] = शून्य;
			जाओ cleanup;
		पूर्ण
		i++;
	पूर्ण

	जबतक (1) अणु
		get_data(map_fd);
		prपूर्णांक_hist();
		sleep(5);
	पूर्ण

cleanup:
	क्रम (i--; i >= 0; i--)
		bpf_link__destroy(links[i]);

	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
