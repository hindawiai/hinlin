<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2019 Facebook */

#समावेश <निश्चित.स>
#समावेश <सीमा.स>
#समावेश <unistd.h>
#समावेश <sys/file.h>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <linux/err.h>
#समावेश <linux/zभाग.स>
#समावेश <bpf/bpf.h>
#समावेश <bpf/btf.h>
#समावेश <bpf/libbpf.h>
#समावेश <api/fs/fs.h>
#समावेश <perf/bpf_perf.h>

#समावेश "bpf_counter.h"
#समावेश "counts.h"
#समावेश "debug.h"
#समावेश "evsel.h"
#समावेश "evlist.h"
#समावेश "target.h"
#समावेश "cpumap.h"
#समावेश "thread_map.h"

#समावेश "bpf_skel/bpf_prog_profiler.skel.h"
#समावेश "bpf_skel/bperf_u.h"
#समावेश "bpf_skel/bperf_leader.skel.h"
#समावेश "bpf_skel/bperf_follower.skel.h"

#घोषणा ATTR_MAP_SIZE 16

अटल अंतरभूत व्योम *u64_to_ptr(__u64 ptr)
अणु
	वापस (व्योम *)(अचिन्हित दीर्घ)ptr;
पूर्ण

अटल व्योम set_max_rlimit(व्योम)
अणु
	काष्ठा rlimit rinf = अणु RLIM_अनन्त, RLIM_अनन्त पूर्ण;

	setrlimit(RLIMIT_MEMLOCK, &rinf);
पूर्ण

अटल काष्ठा bpf_counter *bpf_counter_alloc(व्योम)
अणु
	काष्ठा bpf_counter *counter;

	counter = zalloc(माप(*counter));
	अगर (counter)
		INIT_LIST_HEAD(&counter->list);
	वापस counter;
पूर्ण

अटल पूर्णांक bpf_program_profiler__destroy(काष्ठा evsel *evsel)
अणु
	काष्ठा bpf_counter *counter, *पंचांगp;

	list_क्रम_each_entry_safe(counter, पंचांगp,
				 &evsel->bpf_counter_list, list) अणु
		list_del_init(&counter->list);
		bpf_prog_profiler_bpf__destroy(counter->skel);
		मुक्त(counter);
	पूर्ण
	निश्चित(list_empty(&evsel->bpf_counter_list));

	वापस 0;
पूर्ण

अटल अक्षर *bpf_target_prog_name(पूर्णांक tgt_fd)
अणु
	काष्ठा bpf_prog_info_linear *info_linear;
	काष्ठा bpf_func_info *func_info;
	स्थिर काष्ठा btf_type *t;
	अक्षर *name = शून्य;
	काष्ठा btf *btf;

	info_linear = bpf_program__get_prog_info_linear(
		tgt_fd, 1UL << BPF_PROG_INFO_FUNC_INFO);
	अगर (IS_ERR_OR_शून्य(info_linear)) अणु
		pr_debug("failed to get info_linear for prog FD %d\n", tgt_fd);
		वापस शून्य;
	पूर्ण

	अगर (info_linear->info.btf_id == 0 ||
	    btf__get_from_id(info_linear->info.btf_id, &btf)) अणु
		pr_debug("prog FD %d doesn't have valid btf\n", tgt_fd);
		जाओ out;
	पूर्ण

	func_info = u64_to_ptr(info_linear->info.func_info);
	t = btf__type_by_id(btf, func_info[0].type_id);
	अगर (!t) अणु
		pr_debug("btf %d doesn't have type %d\n",
			 info_linear->info.btf_id, func_info[0].type_id);
		जाओ out;
	पूर्ण
	name = strdup(btf__name_by_offset(btf, t->name_off));
out:
	मुक्त(info_linear);
	वापस name;
पूर्ण

अटल पूर्णांक bpf_program_profiler_load_one(काष्ठा evsel *evsel, u32 prog_id)
अणु
	काष्ठा bpf_prog_profiler_bpf *skel;
	काष्ठा bpf_counter *counter;
	काष्ठा bpf_program *prog;
	अक्षर *prog_name;
	पूर्णांक prog_fd;
	पूर्णांक err;

	prog_fd = bpf_prog_get_fd_by_id(prog_id);
	अगर (prog_fd < 0) अणु
		pr_err("Failed to open fd for bpf prog %u\n", prog_id);
		वापस -1;
	पूर्ण
	counter = bpf_counter_alloc();
	अगर (!counter) अणु
		बंद(prog_fd);
		वापस -1;
	पूर्ण

	skel = bpf_prog_profiler_bpf__खोलो();
	अगर (!skel) अणु
		pr_err("Failed to open bpf skeleton\n");
		जाओ err_out;
	पूर्ण

	skel->rodata->num_cpu = evsel__nr_cpus(evsel);

	bpf_map__resize(skel->maps.events, evsel__nr_cpus(evsel));
	bpf_map__resize(skel->maps.fentry_पढ़ोings, 1);
	bpf_map__resize(skel->maps.accum_पढ़ोings, 1);

	prog_name = bpf_target_prog_name(prog_fd);
	अगर (!prog_name) अणु
		pr_err("Failed to get program name for bpf prog %u. Does it have BTF?\n", prog_id);
		जाओ err_out;
	पूर्ण

	bpf_object__क्रम_each_program(prog, skel->obj) अणु
		err = bpf_program__set_attach_target(prog, prog_fd, prog_name);
		अगर (err) अणु
			pr_err("bpf_program__set_attach_target failed.\n"
			       "Does bpf prog %u have BTF?\n", prog_id);
			जाओ err_out;
		पूर्ण
	पूर्ण
	set_max_rlimit();
	err = bpf_prog_profiler_bpf__load(skel);
	अगर (err) अणु
		pr_err("bpf_prog_profiler_bpf__load failed\n");
		जाओ err_out;
	पूर्ण

	निश्चित(skel != शून्य);
	counter->skel = skel;
	list_add(&counter->list, &evsel->bpf_counter_list);
	बंद(prog_fd);
	वापस 0;
err_out:
	bpf_prog_profiler_bpf__destroy(skel);
	मुक्त(counter);
	बंद(prog_fd);
	वापस -1;
पूर्ण

अटल पूर्णांक bpf_program_profiler__load(काष्ठा evsel *evsel, काष्ठा target *target)
अणु
	अक्षर *bpf_str, *bpf_str_, *tok, *saveptr = शून्य, *p;
	u32 prog_id;
	पूर्णांक ret;

	bpf_str_ = bpf_str = strdup(target->bpf_str);
	अगर (!bpf_str)
		वापस -1;

	जबतक ((tok = म_मोहर_r(bpf_str, ",", &saveptr)) != शून्य) अणु
		prog_id = म_से_अदीर्घ(tok, &p, 10);
		अगर (prog_id == 0 || prog_id == अच_पूर्णांक_उच्च ||
		    (*p != '\0' && *p != ',')) अणु
			pr_err("Failed to parse bpf prog ids %s\n",
			       target->bpf_str);
			वापस -1;
		पूर्ण

		ret = bpf_program_profiler_load_one(evsel, prog_id);
		अगर (ret) अणु
			bpf_program_profiler__destroy(evsel);
			मुक्त(bpf_str_);
			वापस -1;
		पूर्ण
		bpf_str = शून्य;
	पूर्ण
	मुक्त(bpf_str_);
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_program_profiler__enable(काष्ठा evsel *evsel)
अणु
	काष्ठा bpf_counter *counter;
	पूर्णांक ret;

	list_क्रम_each_entry(counter, &evsel->bpf_counter_list, list) अणु
		निश्चित(counter->skel != शून्य);
		ret = bpf_prog_profiler_bpf__attach(counter->skel);
		अगर (ret) अणु
			bpf_program_profiler__destroy(evsel);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_program_profiler__disable(काष्ठा evsel *evsel)
अणु
	काष्ठा bpf_counter *counter;

	list_क्रम_each_entry(counter, &evsel->bpf_counter_list, list) अणु
		निश्चित(counter->skel != शून्य);
		bpf_prog_profiler_bpf__detach(counter->skel);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_program_profiler__पढ़ो(काष्ठा evsel *evsel)
अणु
	// perf_cpu_map uses /sys/devices/प्रणाली/cpu/online
	पूर्णांक num_cpu = evsel__nr_cpus(evsel);
	// BPF_MAP_TYPE_PERCPU_ARRAY uses /sys/devices/प्रणाली/cpu/possible
	// Someबार possible > online, like on a Ryzen 3900X that has 24
	// thपढ़ोs but its possible showed 0-31 -acme
	पूर्णांक num_cpu_bpf = libbpf_num_possible_cpus();
	काष्ठा bpf_perf_event_value values[num_cpu_bpf];
	काष्ठा bpf_counter *counter;
	पूर्णांक पढ़ोing_map_fd;
	__u32 key = 0;
	पूर्णांक err, cpu;

	अगर (list_empty(&evsel->bpf_counter_list))
		वापस -EAGAIN;

	क्रम (cpu = 0; cpu < num_cpu; cpu++) अणु
		perf_counts(evsel->counts, cpu, 0)->val = 0;
		perf_counts(evsel->counts, cpu, 0)->ena = 0;
		perf_counts(evsel->counts, cpu, 0)->run = 0;
	पूर्ण
	list_क्रम_each_entry(counter, &evsel->bpf_counter_list, list) अणु
		काष्ठा bpf_prog_profiler_bpf *skel = counter->skel;

		निश्चित(skel != शून्य);
		पढ़ोing_map_fd = bpf_map__fd(skel->maps.accum_पढ़ोings);

		err = bpf_map_lookup_elem(पढ़ोing_map_fd, &key, values);
		अगर (err) अणु
			pr_err("failed to read value\n");
			वापस err;
		पूर्ण

		क्रम (cpu = 0; cpu < num_cpu; cpu++) अणु
			perf_counts(evsel->counts, cpu, 0)->val += values[cpu].counter;
			perf_counts(evsel->counts, cpu, 0)->ena += values[cpu].enabled;
			perf_counts(evsel->counts, cpu, 0)->run += values[cpu].running;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_program_profiler__install_pe(काष्ठा evsel *evsel, पूर्णांक cpu,
					    पूर्णांक fd)
अणु
	काष्ठा bpf_prog_profiler_bpf *skel;
	काष्ठा bpf_counter *counter;
	पूर्णांक ret;

	list_क्रम_each_entry(counter, &evsel->bpf_counter_list, list) अणु
		skel = counter->skel;
		निश्चित(skel != शून्य);

		ret = bpf_map_update_elem(bpf_map__fd(skel->maps.events),
					  &cpu, &fd, BPF_ANY);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा bpf_counter_ops bpf_program_profiler_ops = अणु
	.load       = bpf_program_profiler__load,
	.enable	    = bpf_program_profiler__enable,
	.disable    = bpf_program_profiler__disable,
	.पढ़ो       = bpf_program_profiler__पढ़ो,
	.destroy    = bpf_program_profiler__destroy,
	.install_pe = bpf_program_profiler__install_pe,
पूर्ण;

अटल __u32 bpf_link_get_id(पूर्णांक fd)
अणु
	काष्ठा bpf_link_info link_info = अणु0पूर्ण;
	__u32 link_info_len = माप(link_info);

	bpf_obj_get_info_by_fd(fd, &link_info, &link_info_len);
	वापस link_info.id;
पूर्ण

अटल __u32 bpf_link_get_prog_id(पूर्णांक fd)
अणु
	काष्ठा bpf_link_info link_info = अणु0पूर्ण;
	__u32 link_info_len = माप(link_info);

	bpf_obj_get_info_by_fd(fd, &link_info, &link_info_len);
	वापस link_info.prog_id;
पूर्ण

अटल __u32 bpf_map_get_id(पूर्णांक fd)
अणु
	काष्ठा bpf_map_info map_info = अणु0पूर्ण;
	__u32 map_info_len = माप(map_info);

	bpf_obj_get_info_by_fd(fd, &map_info, &map_info_len);
	वापस map_info.id;
पूर्ण

अटल bool bperf_attr_map_compatible(पूर्णांक attr_map_fd)
अणु
	काष्ठा bpf_map_info map_info = अणु0पूर्ण;
	__u32 map_info_len = माप(map_info);
	पूर्णांक err;

	err = bpf_obj_get_info_by_fd(attr_map_fd, &map_info, &map_info_len);

	अगर (err)
		वापस false;
	वापस (map_info.key_size == माप(काष्ठा perf_event_attr)) &&
		(map_info.value_size == माप(काष्ठा perf_event_attr_map_entry));
पूर्ण

अटल पूर्णांक bperf_lock_attr_map(काष्ठा target *target)
अणु
	अक्षर path[PATH_MAX];
	पूर्णांक map_fd, err;

	अगर (target->attr_map) अणु
		scnम_लिखो(path, PATH_MAX, "%s", target->attr_map);
	पूर्ण अन्यथा अणु
		scnम_लिखो(path, PATH_MAX, "%s/fs/bpf/%s", sysfs__mountpoपूर्णांक(),
			  BPF_PERF_DEFAULT_ATTR_MAP_PATH);
	पूर्ण

	अगर (access(path, F_OK)) अणु
		map_fd = bpf_create_map(BPF_MAP_TYPE_HASH,
					माप(काष्ठा perf_event_attr),
					माप(काष्ठा perf_event_attr_map_entry),
					ATTR_MAP_SIZE, 0);
		अगर (map_fd < 0)
			वापस -1;

		err = bpf_obj_pin(map_fd, path);
		अगर (err) अणु
			/* someone pinned the map in parallel? */
			बंद(map_fd);
			map_fd = bpf_obj_get(path);
			अगर (map_fd < 0)
				वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		map_fd = bpf_obj_get(path);
		अगर (map_fd < 0)
			वापस -1;
	पूर्ण

	अगर (!bperf_attr_map_compatible(map_fd)) अणु
		बंद(map_fd);
		वापस -1;

	पूर्ण
	err = flock(map_fd, LOCK_EX);
	अगर (err) अणु
		बंद(map_fd);
		वापस -1;
	पूर्ण
	वापस map_fd;
पूर्ण

/* trigger the leader program on a cpu */
अटल पूर्णांक bperf_trigger_पढ़ोing(पूर्णांक prog_fd, पूर्णांक cpu)
अणु
	DECLARE_LIBBPF_OPTS(bpf_test_run_opts, opts,
			    .ctx_in = शून्य,
			    .ctx_size_in = 0,
			    .flags = BPF_F_TEST_RUN_ON_CPU,
			    .cpu = cpu,
			    .retval = 0,
		);

	वापस bpf_prog_test_run_opts(prog_fd, &opts);
पूर्ण

अटल पूर्णांक bperf_check_target(काष्ठा evsel *evsel,
			      काष्ठा target *target,
			      क्रमागत bperf_filter_type *filter_type,
			      __u32 *filter_entry_cnt)
अणु
	अगर (evsel->leader->core.nr_members > 1) अणु
		pr_err("bpf managed perf events do not yet support groups.\n");
		वापस -1;
	पूर्ण

	/* determine filter type based on target */
	अगर (target->प्रणाली_wide) अणु
		*filter_type = BPERF_FILTER_GLOBAL;
		*filter_entry_cnt = 1;
	पूर्ण अन्यथा अगर (target->cpu_list) अणु
		*filter_type = BPERF_FILTER_CPU;
		*filter_entry_cnt = perf_cpu_map__nr(evsel__cpus(evsel));
	पूर्ण अन्यथा अगर (target->tid) अणु
		*filter_type = BPERF_FILTER_PID;
		*filter_entry_cnt = perf_thपढ़ो_map__nr(evsel->core.thपढ़ोs);
	पूर्ण अन्यथा अगर (target->pid || evsel->evlist->workload.pid != -1) अणु
		*filter_type = BPERF_FILTER_TGID;
		*filter_entry_cnt = perf_thपढ़ो_map__nr(evsel->core.thपढ़ोs);
	पूर्ण अन्यथा अणु
		pr_err("bpf managed perf events do not yet support these targets.\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल	काष्ठा perf_cpu_map *all_cpu_map;

अटल पूर्णांक bperf_reload_leader_program(काष्ठा evsel *evsel, पूर्णांक attr_map_fd,
				       काष्ठा perf_event_attr_map_entry *entry)
अणु
	काष्ठा bperf_leader_bpf *skel = bperf_leader_bpf__खोलो();
	पूर्णांक link_fd, dअगरf_map_fd, err;
	काष्ठा bpf_link *link = शून्य;

	अगर (!skel) अणु
		pr_err("Failed to open leader skeleton\n");
		वापस -1;
	पूर्ण

	bpf_map__resize(skel->maps.events, libbpf_num_possible_cpus());
	err = bperf_leader_bpf__load(skel);
	अगर (err) अणु
		pr_err("Failed to load leader skeleton\n");
		जाओ out;
	पूर्ण

	link = bpf_program__attach(skel->progs.on_चयन);
	अगर (IS_ERR(link)) अणु
		pr_err("Failed to attach leader program\n");
		err = PTR_ERR(link);
		जाओ out;
	पूर्ण

	link_fd = bpf_link__fd(link);
	dअगरf_map_fd = bpf_map__fd(skel->maps.dअगरf_पढ़ोings);
	entry->link_id = bpf_link_get_id(link_fd);
	entry->dअगरf_map_id = bpf_map_get_id(dअगरf_map_fd);
	err = bpf_map_update_elem(attr_map_fd, &evsel->core.attr, entry, BPF_ANY);
	निश्चित(err == 0);

	evsel->bperf_leader_link_fd = bpf_link_get_fd_by_id(entry->link_id);
	निश्चित(evsel->bperf_leader_link_fd >= 0);

	/*
	 * save leader_skel क्रम install_pe, which is called within
	 * following evsel__खोलो_per_cpu call
	 */
	evsel->leader_skel = skel;
	evsel__खोलो_per_cpu(evsel, all_cpu_map, -1);

out:
	bperf_leader_bpf__destroy(skel);
	bpf_link__destroy(link);
	वापस err;
पूर्ण

अटल पूर्णांक bperf__load(काष्ठा evsel *evsel, काष्ठा target *target)
अणु
	काष्ठा perf_event_attr_map_entry entry = अणु0xffffffff, 0xffffffffपूर्ण;
	पूर्णांक attr_map_fd, dअगरf_map_fd = -1, err;
	क्रमागत bperf_filter_type filter_type;
	__u32 filter_entry_cnt, i;

	अगर (bperf_check_target(evsel, target, &filter_type, &filter_entry_cnt))
		वापस -1;

	अगर (!all_cpu_map) अणु
		all_cpu_map = perf_cpu_map__new(शून्य);
		अगर (!all_cpu_map)
			वापस -1;
	पूर्ण

	evsel->bperf_leader_prog_fd = -1;
	evsel->bperf_leader_link_fd = -1;

	/*
	 * Step 1: hold a fd on the leader program and the bpf_link, अगर
	 * the program is not alपढ़ोy gone, reload the program.
	 * Use flock() to ensure exclusive access to the perf_event_attr
	 * map.
	 */
	attr_map_fd = bperf_lock_attr_map(target);
	अगर (attr_map_fd < 0) अणु
		pr_err("Failed to lock perf_event_attr map\n");
		वापस -1;
	पूर्ण

	err = bpf_map_lookup_elem(attr_map_fd, &evsel->core.attr, &entry);
	अगर (err) अणु
		err = bpf_map_update_elem(attr_map_fd, &evsel->core.attr, &entry, BPF_ANY);
		अगर (err)
			जाओ out;
	पूर्ण

	evsel->bperf_leader_link_fd = bpf_link_get_fd_by_id(entry.link_id);
	अगर (evsel->bperf_leader_link_fd < 0 &&
	    bperf_reload_leader_program(evsel, attr_map_fd, &entry)) अणु
		err = -1;
		जाओ out;
	पूर्ण
	/*
	 * The bpf_link holds reference to the leader program, and the
	 * leader program holds reference to the maps. Thereक्रमe, अगर
	 * link_id is valid, dअगरf_map_id should also be valid.
	 */
	evsel->bperf_leader_prog_fd = bpf_prog_get_fd_by_id(
		bpf_link_get_prog_id(evsel->bperf_leader_link_fd));
	निश्चित(evsel->bperf_leader_prog_fd >= 0);

	dअगरf_map_fd = bpf_map_get_fd_by_id(entry.dअगरf_map_id);
	निश्चित(dअगरf_map_fd >= 0);

	/*
	 * bperf uses BPF_PROG_TEST_RUN to get accurate पढ़ोing. Check
	 * whether the kernel support it
	 */
	err = bperf_trigger_पढ़ोing(evsel->bperf_leader_prog_fd, 0);
	अगर (err) अणु
		pr_err("The kernel does not support test_run for raw_tp BPF programs.\n"
		       "Therefore, --use-bpf might show inaccurate readings\n");
		जाओ out;
	पूर्ण

	/* Step 2: load the follower skeleton */
	evsel->follower_skel = bperf_follower_bpf__खोलो();
	अगर (!evsel->follower_skel) अणु
		err = -1;
		pr_err("Failed to open follower skeleton\n");
		जाओ out;
	पूर्ण

	/* attach fनिकास program to the leader program */
	bpf_program__set_attach_target(evsel->follower_skel->progs.fनिकास_XXX,
				       evsel->bperf_leader_prog_fd, "on_switch");

	/* connect to leader dअगरf_पढ़ोing map */
	bpf_map__reuse_fd(evsel->follower_skel->maps.dअगरf_पढ़ोings, dअगरf_map_fd);

	/* set up पढ़ोing map */
	bpf_map__set_max_entries(evsel->follower_skel->maps.accum_पढ़ोings,
				 filter_entry_cnt);
	/* set up follower filter based on target */
	bpf_map__set_max_entries(evsel->follower_skel->maps.filter,
				 filter_entry_cnt);
	err = bperf_follower_bpf__load(evsel->follower_skel);
	अगर (err) अणु
		pr_err("Failed to load follower skeleton\n");
		bperf_follower_bpf__destroy(evsel->follower_skel);
		evsel->follower_skel = शून्य;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < filter_entry_cnt; i++) अणु
		पूर्णांक filter_map_fd;
		__u32 key;

		अगर (filter_type == BPERF_FILTER_PID ||
		    filter_type == BPERF_FILTER_TGID)
			key = evsel->core.thपढ़ोs->map[i].pid;
		अन्यथा अगर (filter_type == BPERF_FILTER_CPU)
			key = evsel->core.cpus->map[i];
		अन्यथा
			अवरोध;

		filter_map_fd = bpf_map__fd(evsel->follower_skel->maps.filter);
		bpf_map_update_elem(filter_map_fd, &key, &i, BPF_ANY);
	पूर्ण

	evsel->follower_skel->bss->type = filter_type;

	err = bperf_follower_bpf__attach(evsel->follower_skel);

out:
	अगर (err && evsel->bperf_leader_link_fd >= 0)
		बंद(evsel->bperf_leader_link_fd);
	अगर (err && evsel->bperf_leader_prog_fd >= 0)
		बंद(evsel->bperf_leader_prog_fd);
	अगर (dअगरf_map_fd >= 0)
		बंद(dअगरf_map_fd);

	flock(attr_map_fd, LOCK_UN);
	बंद(attr_map_fd);

	वापस err;
पूर्ण

अटल पूर्णांक bperf__install_pe(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक fd)
अणु
	काष्ठा bperf_leader_bpf *skel = evsel->leader_skel;

	वापस bpf_map_update_elem(bpf_map__fd(skel->maps.events),
				   &cpu, &fd, BPF_ANY);
पूर्ण

/*
 * trigger the leader prog on each cpu, so the accum_पढ़ोing map could get
 * the latest पढ़ोings.
 */
अटल पूर्णांक bperf_sync_counters(काष्ठा evsel *evsel)
अणु
	पूर्णांक num_cpu, i, cpu;

	num_cpu = all_cpu_map->nr;
	क्रम (i = 0; i < num_cpu; i++) अणु
		cpu = all_cpu_map->map[i];
		bperf_trigger_पढ़ोing(evsel->bperf_leader_prog_fd, cpu);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bperf__enable(काष्ठा evsel *evsel)
अणु
	evsel->follower_skel->bss->enabled = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक bperf__disable(काष्ठा evsel *evsel)
अणु
	evsel->follower_skel->bss->enabled = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक bperf__पढ़ो(काष्ठा evsel *evsel)
अणु
	काष्ठा bperf_follower_bpf *skel = evsel->follower_skel;
	__u32 num_cpu_bpf = cpu__max_cpu();
	काष्ठा bpf_perf_event_value values[num_cpu_bpf];
	पूर्णांक पढ़ोing_map_fd, err = 0;
	__u32 i, j, num_cpu;

	bperf_sync_counters(evsel);
	पढ़ोing_map_fd = bpf_map__fd(skel->maps.accum_पढ़ोings);

	क्रम (i = 0; i < bpf_map__max_entries(skel->maps.accum_पढ़ोings); i++) अणु
		__u32 cpu;

		err = bpf_map_lookup_elem(पढ़ोing_map_fd, &i, values);
		अगर (err)
			जाओ out;
		चयन (evsel->follower_skel->bss->type) अणु
		हाल BPERF_FILTER_GLOBAL:
			निश्चित(i == 0);

			num_cpu = all_cpu_map->nr;
			क्रम (j = 0; j < num_cpu; j++) अणु
				cpu = all_cpu_map->map[j];
				perf_counts(evsel->counts, cpu, 0)->val = values[cpu].counter;
				perf_counts(evsel->counts, cpu, 0)->ena = values[cpu].enabled;
				perf_counts(evsel->counts, cpu, 0)->run = values[cpu].running;
			पूर्ण
			अवरोध;
		हाल BPERF_FILTER_CPU:
			cpu = evsel->core.cpus->map[i];
			perf_counts(evsel->counts, i, 0)->val = values[cpu].counter;
			perf_counts(evsel->counts, i, 0)->ena = values[cpu].enabled;
			perf_counts(evsel->counts, i, 0)->run = values[cpu].running;
			अवरोध;
		हाल BPERF_FILTER_PID:
		हाल BPERF_FILTER_TGID:
			perf_counts(evsel->counts, 0, i)->val = 0;
			perf_counts(evsel->counts, 0, i)->ena = 0;
			perf_counts(evsel->counts, 0, i)->run = 0;

			क्रम (cpu = 0; cpu < num_cpu_bpf; cpu++) अणु
				perf_counts(evsel->counts, 0, i)->val += values[cpu].counter;
				perf_counts(evsel->counts, 0, i)->ena += values[cpu].enabled;
				perf_counts(evsel->counts, 0, i)->run += values[cpu].running;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक bperf__destroy(काष्ठा evsel *evsel)
अणु
	bperf_follower_bpf__destroy(evsel->follower_skel);
	बंद(evsel->bperf_leader_prog_fd);
	बंद(evsel->bperf_leader_link_fd);
	वापस 0;
पूर्ण

/*
 * bperf: share hardware PMCs with BPF
 *
 * perf uses perक्रमmance monitoring counters (PMC) to monitor प्रणाली
 * perक्रमmance. The PMCs are limited hardware resources. For example,
 * Intel CPUs have 3x fixed PMCs and 4x programmable PMCs per cpu.
 *
 * Modern data center प्रणालीs use these PMCs in many dअगरferent ways:
 * प्रणाली level monitoring, (maybe nested) container level monitoring, per
 * process monitoring, profiling (in sample mode), etc. In some हालs,
 * there are more active perf_events than available hardware PMCs. To allow
 * all perf_events to have a chance to run, it is necessary to करो expensive
 * समय multiplexing of events.
 *
 * On the other hand, many monitoring tools count the common metrics
 * (cycles, inकाष्ठाions). It is a waste to have multiple tools create
 * multiple perf_events of "cycles" and occupy multiple PMCs.
 *
 * bperf tries to reduce such wastes by allowing multiple perf_events of
 * "cycles" or "instructions" (at dअगरferent scopes) to share PMUs. Instead
 * of having each perf-stat session to पढ़ो its own perf_events, bperf uses
 * BPF programs to पढ़ो the perf_events and aggregate पढ़ोings to BPF maps.
 * Then, the perf-stat session(s) पढ़ोs the values from these BPF maps.
 *
 *                                ||
 *       shared progs and maps <- || -> per session progs and maps
 *                                ||
 *   ---------------              ||
 *   | perf_events |              ||
 *   ---------------       fनिकास  ||      -----------------
 *          |             --------||----> | follower prog |
 *       --------------- /        || ---  -----------------
 * cs -> | leader prog |/         ||/        |         |
 *   --> ---------------         /||  --------------  ------------------
 *  /       |         |         / ||  | filter map |  | accum_पढ़ोings |
 * /  ------------  ------------  ||  --------------  ------------------
 * |  | prev map |  | dअगरf map |  ||                        |
 * |  ------------  ------------  ||                        |
 *  \                             ||                        |
 * = \ ==================================================== | ============
 *    \                                                    /   user space
 *     \                                                  /
 *      \                                                /
 *    BPF_PROG_TEST_RUN                    BPF_MAP_LOOKUP_ELEM
 *        \                                            /
 *         \                                          /
 *          \------  perf-stat ----------------------/
 *
 * The figure above shows the architecture of bperf. Note that the figure
 * is भागided पूर्णांकo 3 regions: shared progs and maps (top left), per session
 * progs and maps (top right), and user space (bottom).
 *
 * The leader prog is triggered on each context चयन (cs). The leader
 * prog पढ़ोs perf_events and stores the dअगरference (current_पढ़ोing -
 * previous_पढ़ोing) to the dअगरf map. For the same metric, e.g. "cycles",
 * multiple perf-stat sessions share the same leader prog.
 *
 * Each perf-stat session creates a follower prog as fनिकास program to the
 * leader prog. It is possible to attach up to BPF_MAX_TRAMP_PROGS (38)
 * follower progs to the same leader prog. The follower prog checks current
 * task and processor ID to decide whether to add the value from the dअगरf
 * map to its accumulated पढ़ोing map (accum_पढ़ोings).
 *
 * Finally, perf-stat user space पढ़ोs the value from accum_पढ़ोing map.
 *
 * Besides context चयन, it is also necessary to trigger the leader prog
 * beक्रमe perf-stat पढ़ोs the value. Otherwise, the accum_पढ़ोing map may
 * not have the latest पढ़ोing from the perf_events. This is achieved by
 * triggering the event via sys_bpf(BPF_PROG_TEST_RUN) to each CPU.
 *
 * Comment beक्रमe the definition of काष्ठा perf_event_attr_map_entry
 * describes how dअगरferent sessions of perf-stat share inक्रमmation about
 * the leader prog.
 */

काष्ठा bpf_counter_ops bperf_ops = अणु
	.load       = bperf__load,
	.enable     = bperf__enable,
	.disable    = bperf__disable,
	.पढ़ो       = bperf__पढ़ो,
	.install_pe = bperf__install_pe,
	.destroy    = bperf__destroy,
पूर्ण;

अटल अंतरभूत bool bpf_counter_skip(काष्ठा evsel *evsel)
अणु
	वापस list_empty(&evsel->bpf_counter_list) &&
		evsel->follower_skel == शून्य;
पूर्ण

पूर्णांक bpf_counter__install_pe(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक fd)
अणु
	अगर (bpf_counter_skip(evsel))
		वापस 0;
	वापस evsel->bpf_counter_ops->install_pe(evsel, cpu, fd);
पूर्ण

पूर्णांक bpf_counter__load(काष्ठा evsel *evsel, काष्ठा target *target)
अणु
	अगर (target->bpf_str)
		evsel->bpf_counter_ops = &bpf_program_profiler_ops;
	अन्यथा अगर (target->use_bpf || evsel->bpf_counter ||
		 evsel__match_bpf_counter_events(evsel->name))
		evsel->bpf_counter_ops = &bperf_ops;

	अगर (evsel->bpf_counter_ops)
		वापस evsel->bpf_counter_ops->load(evsel, target);
	वापस 0;
पूर्ण

पूर्णांक bpf_counter__enable(काष्ठा evsel *evsel)
अणु
	अगर (bpf_counter_skip(evsel))
		वापस 0;
	वापस evsel->bpf_counter_ops->enable(evsel);
पूर्ण

पूर्णांक bpf_counter__disable(काष्ठा evsel *evsel)
अणु
	अगर (bpf_counter_skip(evsel))
		वापस 0;
	वापस evsel->bpf_counter_ops->disable(evsel);
पूर्ण

पूर्णांक bpf_counter__पढ़ो(काष्ठा evsel *evsel)
अणु
	अगर (bpf_counter_skip(evsel))
		वापस -EAGAIN;
	वापस evsel->bpf_counter_ops->पढ़ो(evsel);
पूर्ण

व्योम bpf_counter__destroy(काष्ठा evsel *evsel)
अणु
	अगर (bpf_counter_skip(evsel))
		वापस;
	evsel->bpf_counter_ops->destroy(evsel);
	evsel->bpf_counter_ops = शून्य;
पूर्ण
