<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2015 PLUMgrid, http://plumgrid.com
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <sys/resource.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "bpf_util.h"

#घोषणा SLOTS 100

अटल व्योम clear_stats(पूर्णांक fd)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	__u64 values[nr_cpus];
	__u32 key;

	स_रखो(values, 0, माप(values));
	क्रम (key = 0; key < SLOTS; key++)
		bpf_map_update_elem(fd, &key, values, BPF_ANY);
पूर्ण

स्थिर अक्षर *color[] = अणु
	"\033[48;5;255m",
	"\033[48;5;252m",
	"\033[48;5;250m",
	"\033[48;5;248m",
	"\033[48;5;246m",
	"\033[48;5;244m",
	"\033[48;5;242m",
	"\033[48;5;240m",
	"\033[48;5;238m",
	"\033[48;5;236m",
	"\033[48;5;234m",
	"\033[48;5;232m",
पूर्ण;
स्थिर पूर्णांक num_colors = ARRAY_SIZE(color);

स्थिर अक्षर nocolor[] = "\033[00m";

स्थिर अक्षर *sym[] = अणु
	" ",
	" ",
	".",
	".",
	"*",
	"*",
	"o",
	"o",
	"O",
	"O",
	"#",
	"#",
पूर्ण;

bool full_range = false;
bool text_only = false;

अटल व्योम prपूर्णांक_banner(व्योम)
अणु
	अगर (full_range)
		म_लिखो("|1ns     |10ns     |100ns    |1us      |10us     |100us"
		       "    |1ms      |10ms     |100ms    |1s       |10s\n");
	अन्यथा
		म_लिखो("|1us      |10us     |100us    |1ms      |10ms     "
		       "|100ms    |1s       |10s\n");
पूर्ण

अटल व्योम prपूर्णांक_hist(पूर्णांक fd)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	__u64 total_events = 0;
	दीर्घ values[nr_cpus];
	__u64 max_cnt = 0;
	__u64 cnt[SLOTS];
	__u64 value;
	__u32 key;
	पूर्णांक i;

	क्रम (key = 0; key < SLOTS; key++) अणु
		bpf_map_lookup_elem(fd, &key, values);
		value = 0;
		क्रम (i = 0; i < nr_cpus; i++)
			value += values[i];
		cnt[key] = value;
		total_events += value;
		अगर (value > max_cnt)
			max_cnt = value;
	पूर्ण
	clear_stats(fd);
	क्रम (key = full_range ? 0 : 29; key < SLOTS; key++) अणु
		पूर्णांक c = num_colors * cnt[key] / (max_cnt + 1);

		अगर (text_only)
			म_लिखो("%s", sym[c]);
		अन्यथा
			म_लिखो("%s %s", color[c], nocolor);
	पूर्ण
	म_लिखो(" # %lld\n", total_events);
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **argv)
अणु
	काष्ठा bpf_link *links[2];
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	पूर्णांक map_fd, i, j = 0;

	क्रम (i = 1; i < ac; i++) अणु
		अगर (म_भेद(argv[i], "-a") == 0) अणु
			full_range = true;
		पूर्ण अन्यथा अगर (म_भेद(argv[i], "-t") == 0) अणु
			text_only = true;
		पूर्ण अन्यथा अगर (म_भेद(argv[i], "-h") == 0) अणु
			म_लिखो("Usage:\n"
			       "  -a display wider latency range\n"
			       "  -t text only\n");
			वापस 1;
		पूर्ण
	पूर्ण

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

	map_fd = bpf_object__find_map_fd_by_name(obj, "lat_map");
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

	म_लिखो("  heatmap of IO latency\n");
	अगर (text_only)
		म_लिखो("  %s", sym[num_colors - 1]);
	अन्यथा
		म_लिखो("  %s %s", color[num_colors - 1], nocolor);
	म_लिखो(" - many events with this latency\n");

	अगर (text_only)
		म_लिखो("  %s", sym[0]);
	अन्यथा
		म_लिखो("  %s %s", color[0], nocolor);
	म_लिखो(" - few events\n");

	क्रम (i = 0; ; i++) अणु
		अगर (i % 20 == 0)
			prपूर्णांक_banner();
		prपूर्णांक_hist(map_fd);
		sleep(2);
	पूर्ण

cleanup:
	क्रम (j--; j >= 0; j--)
		bpf_link__destroy(links[j]);

	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
