<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright(c) 2017 Jesper Dangaard Brouer, Red Hat, Inc.
 */
अटल स्थिर अक्षर *__करोc__ =
	" XDP redirect with a CPU-map type \"BPF_MAP_TYPE_CPUMAP\"";

#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <क्षेत्र.स>
#समावेश <sys/resource.h>
#समावेश <sys/sysinfo.h>
#समावेश <getopt.h>
#समावेश <net/अगर.h>
#समावेश <समय.स>
#समावेश <linux/सीमा.स>

#समावेश <arpa/inet.h>
#समावेश <linux/अगर_link.h>

/* How many xdp_progs are defined in _kern.c */
#घोषणा MAX_PROG 6

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "bpf_util.h"

अटल पूर्णांक अगरindex = -1;
अटल अक्षर अगरname_buf[IF_NAMESIZE];
अटल अक्षर *अगरname;
अटल __u32 prog_id;

अटल __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
अटल पूर्णांक n_cpus;

क्रमागत map_type अणु
	CPU_MAP,
	RX_CNT,
	REसूचीECT_ERR_CNT,
	CPUMAP_ENQUEUE_CNT,
	CPUMAP_KTHREAD_CNT,
	CPUS_AVAILABLE,
	CPUS_COUNT,
	CPUS_ITERATOR,
	EXCEPTION_CNT,
पूर्ण;

अटल स्थिर अक्षर *स्थिर map_type_strings[] = अणु
	[CPU_MAP] = "cpu_map",
	[RX_CNT] = "rx_cnt",
	[REसूचीECT_ERR_CNT] = "redirect_err_cnt",
	[CPUMAP_ENQUEUE_CNT] = "cpumap_enqueue_cnt",
	[CPUMAP_KTHREAD_CNT] = "cpumap_kthread_cnt",
	[CPUS_AVAILABLE] = "cpus_available",
	[CPUS_COUNT] = "cpus_count",
	[CPUS_ITERATOR] = "cpus_iterator",
	[EXCEPTION_CNT] = "exception_cnt",
पूर्ण;

#घोषणा NUM_TP 5
#घोषणा NUM_MAP 9
काष्ठा bpf_link *tp_links[NUM_TP] = अणुपूर्ण;
अटल पूर्णांक map_fds[NUM_MAP];
अटल पूर्णांक tp_cnt = 0;

/* Exit वापस codes */
#घोषणा EXIT_OK		0
#घोषणा EXIT_FAIL		1
#घोषणा EXIT_FAIL_OPTION	2
#घोषणा EXIT_FAIL_XDP		3
#घोषणा EXIT_FAIL_BPF		4
#घोषणा EXIT_FAIL_MEM		5

अटल स्थिर काष्ठा option दीर्घ_options[] = अणु
	अणु"help",	no_argument,		शून्य, 'h' पूर्ण,
	अणु"dev",		required_argument,	शून्य, 'd' पूर्ण,
	अणु"skb-mode",	no_argument,		शून्य, 'S' पूर्ण,
	अणु"sec",		required_argument,	शून्य, 's' पूर्ण,
	अणु"progname",	required_argument,	शून्य, 'p' पूर्ण,
	अणु"qsize",	required_argument,	शून्य, 'q' पूर्ण,
	अणु"cpu",		required_argument,	शून्य, 'c' पूर्ण,
	अणु"stress-mode", no_argument,		शून्य, 'x' पूर्ण,
	अणु"no-separators", no_argument,		शून्य, 'z' पूर्ण,
	अणु"force",	no_argument,		शून्य, 'F' पूर्ण,
	अणु"mprog-disable", no_argument,		शून्य, 'n' पूर्ण,
	अणु"mprog-name",	required_argument,	शून्य, 'e' पूर्ण,
	अणु"mprog-filename", required_argument,	शून्य, 'f' पूर्ण,
	अणु"redirect-device", required_argument,	शून्य, 'r' पूर्ण,
	अणु"redirect-map", required_argument,	शून्य, 'm' पूर्ण,
	अणु0, 0, शून्य,  0 पूर्ण
पूर्ण;

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	__u32 curr_prog_id = 0;

	अगर (अगरindex > -1) अणु
		अगर (bpf_get_link_xdp_id(अगरindex, &curr_prog_id, xdp_flags)) अणु
			म_लिखो("bpf_get_link_xdp_id failed\n");
			निकास(EXIT_FAIL);
		पूर्ण
		अगर (prog_id == curr_prog_id) अणु
			ख_लिखो(मानक_त्रुटि,
				"Interrupted: Removing XDP program on ifindex:%d device:%s\n",
				अगरindex, अगरname);
			bpf_set_link_xdp_fd(अगरindex, -1, xdp_flags);
		पूर्ण अन्यथा अगर (!curr_prog_id) अणु
			म_लिखो("couldn't find a prog id on a given iface\n");
		पूर्ण अन्यथा अणु
			म_लिखो("program on interface changed, not removing\n");
		पूर्ण
	पूर्ण
	/* Detach tracepoपूर्णांकs */
	जबतक (tp_cnt)
		bpf_link__destroy(tp_links[--tp_cnt]);

	निकास(EXIT_OK);
पूर्ण

अटल व्योम prपूर्णांक_avail_progs(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_program *pos;

	bpf_object__क्रम_each_program(pos, obj) अणु
		अगर (bpf_program__is_xdp(pos))
			म_लिखो(" %s\n", bpf_program__section_name(pos));
	पूर्ण
पूर्ण

अटल व्योम usage(अक्षर *argv[], काष्ठा bpf_object *obj)
अणु
	पूर्णांक i;

	म_लिखो("\nDOCUMENTATION:\n%s\n", __करोc__);
	म_लिखो("\n");
	म_लिखो(" Usage: %s (options-see-below)\n", argv[0]);
	म_लिखो(" Listing options:\n");
	क्रम (i = 0; दीर्घ_options[i].name != 0; i++) अणु
		म_लिखो(" --%-12s", दीर्घ_options[i].name);
		अगर (दीर्घ_options[i].flag != शून्य)
			म_लिखो(" flag (internal value:%d)",
				*दीर्घ_options[i].flag);
		अन्यथा
			म_लिखो(" short-option: -%c",
				दीर्घ_options[i].val);
		म_लिखो("\n");
	पूर्ण
	म_लिखो("\n Programs to be used for --progname:\n");
	prपूर्णांक_avail_progs(obj);
	म_लिखो("\n");
पूर्ण

/* समय_लो वापसs the current समय of day in nanoseconds.
 * Cost: घड़ी_समय_लो (ns) => 26ns (CLOCK_MONOTONIC)
 *       घड़ी_समय_लो (ns) =>  9ns (CLOCK_MONOTONIC_COARSE)
 */
#घोषणा न_अंकOSEC_PER_SEC 1000000000 /* 10^9 */
अटल __u64 समय_लो(व्योम)
अणु
	काष्ठा बारpec t;
	पूर्णांक res;

	res = घड़ी_समय_लो(CLOCK_MONOTONIC, &t);
	अगर (res < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Error with gettimeofday! (%i)\n", res);
		निकास(EXIT_FAIL);
	पूर्ण
	वापस (__u64) t.tv_sec * न_अंकOSEC_PER_SEC + t.tv_nsec;
पूर्ण

/* Common stats data record shared with _kern.c */
काष्ठा datarec अणु
	__u64 processed;
	__u64 dropped;
	__u64 issue;
	__u64 xdp_pass;
	__u64 xdp_drop;
	__u64 xdp_redirect;
पूर्ण;
काष्ठा record अणु
	__u64 बारtamp;
	काष्ठा datarec total;
	काष्ठा datarec *cpu;
पूर्ण;
काष्ठा stats_record अणु
	काष्ठा record rx_cnt;
	काष्ठा record redir_err;
	काष्ठा record kthपढ़ो;
	काष्ठा record exception;
	काष्ठा record enq[];
पूर्ण;

अटल bool map_collect_percpu(पूर्णांक fd, __u32 key, काष्ठा record *rec)
अणु
	/* For percpu maps, userspace माला_लो a value per possible CPU */
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	काष्ठा datarec values[nr_cpus];
	__u64 sum_xdp_redirect = 0;
	__u64 sum_xdp_pass = 0;
	__u64 sum_xdp_drop = 0;
	__u64 sum_processed = 0;
	__u64 sum_dropped = 0;
	__u64 sum_issue = 0;
	पूर्णांक i;

	अगर ((bpf_map_lookup_elem(fd, &key, values)) != 0) अणु
		ख_लिखो(मानक_त्रुटि,
			"ERR: bpf_map_lookup_elem failed key:0x%X\n", key);
		वापस false;
	पूर्ण
	/* Get समय as बंद as possible to पढ़ोing map contents */
	rec->बारtamp = समय_लो();

	/* Record and sum values from each CPU */
	क्रम (i = 0; i < nr_cpus; i++) अणु
		rec->cpu[i].processed = values[i].processed;
		sum_processed        += values[i].processed;
		rec->cpu[i].dropped = values[i].dropped;
		sum_dropped        += values[i].dropped;
		rec->cpu[i].issue = values[i].issue;
		sum_issue        += values[i].issue;
		rec->cpu[i].xdp_pass = values[i].xdp_pass;
		sum_xdp_pass += values[i].xdp_pass;
		rec->cpu[i].xdp_drop = values[i].xdp_drop;
		sum_xdp_drop += values[i].xdp_drop;
		rec->cpu[i].xdp_redirect = values[i].xdp_redirect;
		sum_xdp_redirect += values[i].xdp_redirect;
	पूर्ण
	rec->total.processed = sum_processed;
	rec->total.dropped   = sum_dropped;
	rec->total.issue     = sum_issue;
	rec->total.xdp_pass  = sum_xdp_pass;
	rec->total.xdp_drop  = sum_xdp_drop;
	rec->total.xdp_redirect = sum_xdp_redirect;
	वापस true;
पूर्ण

अटल काष्ठा datarec *alloc_record_per_cpu(व्योम)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	काष्ठा datarec *array;

	array = सुस्मृति(nr_cpus, माप(काष्ठा datarec));
	अगर (!array) अणु
		ख_लिखो(मानक_त्रुटि, "Mem alloc error (nr_cpus:%u)\n", nr_cpus);
		निकास(EXIT_FAIL_MEM);
	पूर्ण
	वापस array;
पूर्ण

अटल काष्ठा stats_record *alloc_stats_record(व्योम)
अणु
	काष्ठा stats_record *rec;
	पूर्णांक i, size;

	size = माप(*rec) + n_cpus * माप(काष्ठा record);
	rec = दो_स्मृति(size);
	अगर (!rec) अणु
		ख_लिखो(मानक_त्रुटि, "Mem alloc error\n");
		निकास(EXIT_FAIL_MEM);
	पूर्ण
	स_रखो(rec, 0, size);
	rec->rx_cnt.cpu    = alloc_record_per_cpu();
	rec->redir_err.cpu = alloc_record_per_cpu();
	rec->kthपढ़ो.cpu   = alloc_record_per_cpu();
	rec->exception.cpu = alloc_record_per_cpu();
	क्रम (i = 0; i < n_cpus; i++)
		rec->enq[i].cpu = alloc_record_per_cpu();

	वापस rec;
पूर्ण

अटल व्योम मुक्त_stats_record(काष्ठा stats_record *r)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_cpus; i++)
		मुक्त(r->enq[i].cpu);
	मुक्त(r->exception.cpu);
	मुक्त(r->kthपढ़ो.cpu);
	मुक्त(r->redir_err.cpu);
	मुक्त(r->rx_cnt.cpu);
	मुक्त(r);
पूर्ण

अटल द्विगुन calc_period(काष्ठा record *r, काष्ठा record *p)
अणु
	द्विगुन period_ = 0;
	__u64 period = 0;

	period = r->बारtamp - p->बारtamp;
	अगर (period > 0)
		period_ = ((द्विगुन) period / न_अंकOSEC_PER_SEC);

	वापस period_;
पूर्ण

अटल __u64 calc_pps(काष्ठा datarec *r, काष्ठा datarec *p, द्विगुन period_)
अणु
	__u64 packets = 0;
	__u64 pps = 0;

	अगर (period_ > 0) अणु
		packets = r->processed - p->processed;
		pps = packets / period_;
	पूर्ण
	वापस pps;
पूर्ण

अटल __u64 calc_drop_pps(काष्ठा datarec *r, काष्ठा datarec *p, द्विगुन period_)
अणु
	__u64 packets = 0;
	__u64 pps = 0;

	अगर (period_ > 0) अणु
		packets = r->dropped - p->dropped;
		pps = packets / period_;
	पूर्ण
	वापस pps;
पूर्ण

अटल __u64 calc_errs_pps(काष्ठा datarec *r,
			    काष्ठा datarec *p, द्विगुन period_)
अणु
	__u64 packets = 0;
	__u64 pps = 0;

	अगर (period_ > 0) अणु
		packets = r->issue - p->issue;
		pps = packets / period_;
	पूर्ण
	वापस pps;
पूर्ण

अटल व्योम calc_xdp_pps(काष्ठा datarec *r, काष्ठा datarec *p,
			 द्विगुन *xdp_pass, द्विगुन *xdp_drop,
			 द्विगुन *xdp_redirect, द्विगुन period_)
अणु
	*xdp_pass = 0, *xdp_drop = 0, *xdp_redirect = 0;
	अगर (period_ > 0) अणु
		*xdp_redirect = (r->xdp_redirect - p->xdp_redirect) / period_;
		*xdp_pass = (r->xdp_pass - p->xdp_pass) / period_;
		*xdp_drop = (r->xdp_drop - p->xdp_drop) / period_;
	पूर्ण
पूर्ण

अटल व्योम stats_prपूर्णांक(काष्ठा stats_record *stats_rec,
			काष्ठा stats_record *stats_prev,
			अक्षर *prog_name, अक्षर *mprog_name, पूर्णांक mprog_fd)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	द्विगुन pps = 0, drop = 0, err = 0;
	bool mprog_enabled = false;
	काष्ठा record *rec, *prev;
	पूर्णांक to_cpu;
	द्विगुन t;
	पूर्णांक i;

	अगर (mprog_fd > 0)
		mprog_enabled = true;

	/* Header */
	म_लिखो("Running XDP/eBPF prog_name:%s\n", prog_name);
	म_लिखो("%-15s %-7s %-14s %-11s %-9s\n",
	       "XDP-cpumap", "CPU:to", "pps", "drop-pps", "extra-info");

	/* XDP rx_cnt */
	अणु
		अक्षर *fmt_rx = "%-15s %-7d %'-14.0f %'-11.0f %'-10.0f %s\n";
		अक्षर *fm2_rx = "%-15s %-7s %'-14.0f %'-11.0f\n";
		अक्षर *errstr = "";

		rec  = &stats_rec->rx_cnt;
		prev = &stats_prev->rx_cnt;
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps = calc_pps(r, p, t);
			drop = calc_drop_pps(r, p, t);
			err  = calc_errs_pps(r, p, t);
			अगर (err > 0)
				errstr = "cpu-dest/err";
			अगर (pps > 0)
				म_लिखो(fmt_rx, "XDP-RX",
					i, pps, drop, err, errstr);
		पूर्ण
		pps  = calc_pps(&rec->total, &prev->total, t);
		drop = calc_drop_pps(&rec->total, &prev->total, t);
		err  = calc_errs_pps(&rec->total, &prev->total, t);
		म_लिखो(fm2_rx, "XDP-RX", "total", pps, drop);
	पूर्ण

	/* cpumap enqueue stats */
	क्रम (to_cpu = 0; to_cpu < n_cpus; to_cpu++) अणु
		अक्षर *fmt = "%-15s %3d:%-3d %'-14.0f %'-11.0f %'-10.2f %s\n";
		अक्षर *fm2 = "%-15s %3s:%-3d %'-14.0f %'-11.0f %'-10.2f %s\n";
		अक्षर *errstr = "";

		rec  =  &stats_rec->enq[to_cpu];
		prev = &stats_prev->enq[to_cpu];
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps  = calc_pps(r, p, t);
			drop = calc_drop_pps(r, p, t);
			err  = calc_errs_pps(r, p, t);
			अगर (err > 0) अणु
				errstr = "bulk-average";
				err = pps / err; /* calc average bulk size */
			पूर्ण
			अगर (pps > 0)
				म_लिखो(fmt, "cpumap-enqueue",
				       i, to_cpu, pps, drop, err, errstr);
		पूर्ण
		pps = calc_pps(&rec->total, &prev->total, t);
		अगर (pps > 0) अणु
			drop = calc_drop_pps(&rec->total, &prev->total, t);
			err  = calc_errs_pps(&rec->total, &prev->total, t);
			अगर (err > 0) अणु
				errstr = "bulk-average";
				err = pps / err; /* calc average bulk size */
			पूर्ण
			म_लिखो(fm2, "cpumap-enqueue",
			       "sum", to_cpu, pps, drop, err, errstr);
		पूर्ण
	पूर्ण

	/* cpumap kthपढ़ो stats */
	अणु
		अक्षर *fmt_k = "%-15s %-7d %'-14.0f %'-11.0f %'-10.0f %s\n";
		अक्षर *fm2_k = "%-15s %-7s %'-14.0f %'-11.0f %'-10.0f %s\n";
		अक्षर *e_str = "";

		rec  = &stats_rec->kthपढ़ो;
		prev = &stats_prev->kthपढ़ो;
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps  = calc_pps(r, p, t);
			drop = calc_drop_pps(r, p, t);
			err  = calc_errs_pps(r, p, t);
			अगर (err > 0)
				e_str = "sched";
			अगर (pps > 0)
				म_लिखो(fmt_k, "cpumap_kthread",
				       i, pps, drop, err, e_str);
		पूर्ण
		pps = calc_pps(&rec->total, &prev->total, t);
		drop = calc_drop_pps(&rec->total, &prev->total, t);
		err  = calc_errs_pps(&rec->total, &prev->total, t);
		अगर (err > 0)
			e_str = "sched-sum";
		म_लिखो(fm2_k, "cpumap_kthread", "total", pps, drop, err, e_str);
	पूर्ण

	/* XDP redirect err tracepoपूर्णांकs (very unlikely) */
	अणु
		अक्षर *fmt_err = "%-15s %-7d %'-14.0f %'-11.0f\n";
		अक्षर *fm2_err = "%-15s %-7s %'-14.0f %'-11.0f\n";

		rec  = &stats_rec->redir_err;
		prev = &stats_prev->redir_err;
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps  = calc_pps(r, p, t);
			drop = calc_drop_pps(r, p, t);
			अगर (pps > 0)
				म_लिखो(fmt_err, "redirect_err", i, pps, drop);
		पूर्ण
		pps = calc_pps(&rec->total, &prev->total, t);
		drop = calc_drop_pps(&rec->total, &prev->total, t);
		म_लिखो(fm2_err, "redirect_err", "total", pps, drop);
	पूर्ण

	/* XDP general exception tracepoपूर्णांकs */
	अणु
		अक्षर *fmt_err = "%-15s %-7d %'-14.0f %'-11.0f\n";
		अक्षर *fm2_err = "%-15s %-7s %'-14.0f %'-11.0f\n";

		rec  = &stats_rec->exception;
		prev = &stats_prev->exception;
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps  = calc_pps(r, p, t);
			drop = calc_drop_pps(r, p, t);
			अगर (pps > 0)
				म_लिखो(fmt_err, "xdp_exception", i, pps, drop);
		पूर्ण
		pps = calc_pps(&rec->total, &prev->total, t);
		drop = calc_drop_pps(&rec->total, &prev->total, t);
		म_लिखो(fm2_err, "xdp_exception", "total", pps, drop);
	पूर्ण

	/* CPUMAP attached XDP program that runs on remote/destination CPU */
	अगर (mprog_enabled) अणु
		अक्षर *fmt_k = "%-15s %-7d %'-14.0f %'-11.0f %'-10.0f\n";
		अक्षर *fm2_k = "%-15s %-7s %'-14.0f %'-11.0f %'-10.0f\n";
		द्विगुन xdp_pass, xdp_drop, xdp_redirect;

		म_लिखो("\n2nd remote XDP/eBPF prog_name: %s\n", mprog_name);
		म_लिखो("%-15s %-7s %-14s %-11s %-9s\n",
		       "XDP-cpumap", "CPU:to", "xdp-pass", "xdp-drop", "xdp-redir");

		rec  = &stats_rec->kthपढ़ो;
		prev = &stats_prev->kthपढ़ो;
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			calc_xdp_pps(r, p, &xdp_pass, &xdp_drop,
				     &xdp_redirect, t);
			अगर (xdp_pass > 0 || xdp_drop > 0 || xdp_redirect > 0)
				म_लिखो(fmt_k, "xdp-in-kthread", i, xdp_pass, xdp_drop,
				       xdp_redirect);
		पूर्ण
		calc_xdp_pps(&rec->total, &prev->total, &xdp_pass, &xdp_drop,
			     &xdp_redirect, t);
		म_लिखो(fm2_k, "xdp-in-kthread", "total", xdp_pass, xdp_drop, xdp_redirect);
	पूर्ण

	म_लिखो("\n");
	ख_साफ(मानक_निकास);
पूर्ण

अटल व्योम stats_collect(काष्ठा stats_record *rec)
अणु
	पूर्णांक fd, i;

	fd = map_fds[RX_CNT];
	map_collect_percpu(fd, 0, &rec->rx_cnt);

	fd = map_fds[REसूचीECT_ERR_CNT];
	map_collect_percpu(fd, 1, &rec->redir_err);

	fd = map_fds[CPUMAP_ENQUEUE_CNT];
	क्रम (i = 0; i < n_cpus; i++)
		map_collect_percpu(fd, i, &rec->enq[i]);

	fd = map_fds[CPUMAP_KTHREAD_CNT];
	map_collect_percpu(fd, 0, &rec->kthपढ़ो);

	fd = map_fds[EXCEPTION_CNT];
	map_collect_percpu(fd, 0, &rec->exception);
पूर्ण


/* Poपूर्णांकer swap trick */
अटल अंतरभूत व्योम swap(काष्ठा stats_record **a, काष्ठा stats_record **b)
अणु
	काष्ठा stats_record *पंचांगp;

	पंचांगp = *a;
	*a = *b;
	*b = पंचांगp;
पूर्ण

अटल पूर्णांक create_cpu_entry(__u32 cpu, काष्ठा bpf_cpumap_val *value,
			    __u32 avail_idx, bool new)
अणु
	__u32 curr_cpus_count = 0;
	__u32 key = 0;
	पूर्णांक ret;

	/* Add a CPU entry to cpumap, as this allocate a cpu entry in
	 * the kernel क्रम the cpu.
	 */
	ret = bpf_map_update_elem(map_fds[CPU_MAP], &cpu, value, 0);
	अगर (ret) अणु
		ख_लिखो(मानक_त्रुटि, "Create CPU entry failed (err:%d)\n", ret);
		निकास(EXIT_FAIL_BPF);
	पूर्ण

	/* Inक्रमm bpf_prog's that a new CPU is available to select
	 * from via some control maps.
	 */
	ret = bpf_map_update_elem(map_fds[CPUS_AVAILABLE], &avail_idx, &cpu, 0);
	अगर (ret) अणु
		ख_लिखो(मानक_त्रुटि, "Add to avail CPUs failed\n");
		निकास(EXIT_FAIL_BPF);
	पूर्ण

	/* When not replacing/updating existing entry, bump the count */
	ret = bpf_map_lookup_elem(map_fds[CPUS_COUNT], &key, &curr_cpus_count);
	अगर (ret) अणु
		ख_लिखो(मानक_त्रुटि, "Failed reading curr cpus_count\n");
		निकास(EXIT_FAIL_BPF);
	पूर्ण
	अगर (new) अणु
		curr_cpus_count++;
		ret = bpf_map_update_elem(map_fds[CPUS_COUNT], &key,
					  &curr_cpus_count, 0);
		अगर (ret) अणु
			ख_लिखो(मानक_त्रुटि, "Failed write curr cpus_count\n");
			निकास(EXIT_FAIL_BPF);
		पूर्ण
	पूर्ण
	/* map_fd[7] = cpus_iterator */
	म_लिखो("%s CPU:%u as idx:%u qsize:%d prog_fd: %d (cpus_count:%u)\n",
	       new ? "Add-new":"Replace", cpu, avail_idx,
	       value->qsize, value->bpf_prog.fd, curr_cpus_count);

	वापस 0;
पूर्ण

/* CPUs are zero-indexed. Thus, add a special sentinel शेष value
 * in map cpus_available to mark CPU index'es not configured
 */
अटल व्योम mark_cpus_unavailable(व्योम)
अणु
	__u32 invalid_cpu = n_cpus;
	पूर्णांक ret, i;

	क्रम (i = 0; i < n_cpus; i++) अणु
		ret = bpf_map_update_elem(map_fds[CPUS_AVAILABLE], &i,
					  &invalid_cpu, 0);
		अगर (ret) अणु
			ख_लिखो(मानक_त्रुटि, "Failed marking CPU unavailable\n");
			निकास(EXIT_FAIL_BPF);
		पूर्ण
	पूर्ण
पूर्ण

/* Stress cpumap management code by concurrently changing underlying cpumap */
अटल व्योम stress_cpumap(काष्ठा bpf_cpumap_val *value)
अणु
	/* Changing qsize will cause kernel to मुक्त and alloc a new
	 * bpf_cpu_map_entry, with an associated/complicated tear-करोwn
	 * procedure.
	 */
	value->qsize = 1024;
	create_cpu_entry(1, value, 0, false);
	value->qsize = 8;
	create_cpu_entry(1, value, 0, false);
	value->qsize = 16000;
	create_cpu_entry(1, value, 0, false);
पूर्ण

अटल व्योम stats_poll(पूर्णांक पूर्णांकerval, bool use_separators, अक्षर *prog_name,
		       अक्षर *mprog_name, काष्ठा bpf_cpumap_val *value,
		       bool stress_mode)
अणु
	काष्ठा stats_record *record, *prev;
	पूर्णांक mprog_fd;

	record = alloc_stats_record();
	prev   = alloc_stats_record();
	stats_collect(record);

	/* Trick to pretty म_लिखो with thousands separators use %' */
	अगर (use_separators)
		रखो_क्षेत्र(LC_NUMERIC, "en_US");

	जबतक (1) अणु
		swap(&prev, &record);
		mprog_fd = value->bpf_prog.fd;
		stats_collect(record);
		stats_prपूर्णांक(record, prev, prog_name, mprog_name, mprog_fd);
		sleep(पूर्णांकerval);
		अगर (stress_mode)
			stress_cpumap(value);
	पूर्ण

	मुक्त_stats_record(record);
	मुक्त_stats_record(prev);
पूर्ण

अटल पूर्णांक init_tracepoपूर्णांकs(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_program *prog;

	bpf_object__क्रम_each_program(prog, obj) अणु
		अगर (bpf_program__is_tracepoपूर्णांक(prog) != true)
			जारी;

		tp_links[tp_cnt] = bpf_program__attach(prog);
		अगर (libbpf_get_error(tp_links[tp_cnt])) अणु
			tp_links[tp_cnt] = शून्य;
			वापस -EINVAL;
		पूर्ण
		tp_cnt++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_map_fds(काष्ठा bpf_object *obj)
अणु
	क्रमागत map_type type;

	क्रम (type = 0; type < NUM_MAP; type++) अणु
		map_fds[type] =
			bpf_object__find_map_fd_by_name(obj,
							map_type_strings[type]);

		अगर (map_fds[type] < 0)
			वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक load_cpumap_prog(अक्षर *file_name, अक्षर *prog_name,
			    अक्षर *redir_पूर्णांकerface, अक्षर *redir_map)
अणु
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type		= BPF_PROG_TYPE_XDP,
		.expected_attach_type	= BPF_XDP_CPUMAP,
		.file = file_name,
	पूर्ण;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	पूर्णांक fd;

	अगर (bpf_prog_load_xattr(&prog_load_attr, &obj, &fd))
		वापस -1;

	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERR: bpf_prog_load_xattr: %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस fd;
	पूर्ण

	अगर (redir_पूर्णांकerface && redir_map) अणु
		पूर्णांक err, map_fd, अगरindex_out, key = 0;

		map_fd = bpf_object__find_map_fd_by_name(obj, redir_map);
		अगर (map_fd < 0)
			वापस map_fd;

		अगरindex_out = अगर_nametoindex(redir_पूर्णांकerface);
		अगर (!अगरindex_out)
			वापस -1;

		err = bpf_map_update_elem(map_fd, &key, &अगरindex_out, 0);
		अगर (err < 0)
			वापस err;
	पूर्ण

	prog = bpf_object__find_program_by_title(obj, prog_name);
	अगर (!prog) अणु
		ख_लिखो(मानक_त्रुटि, "bpf_object__find_program_by_title failed\n");
		वापस EXIT_FAIL;
	पूर्ण

	वापस bpf_program__fd(prog);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *prog_name = "xdp_cpu_map5_lb_hash_ip_pairs";
	अक्षर *mprog_filename = "xdp_redirect_kern.o";
	अक्षर *redir_पूर्णांकerface = शून्य, *redir_map = शून्य;
	अक्षर *mprog_name = "xdp_redirect_dummy";
	bool mprog_disable = false;
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type	= BPF_PROG_TYPE_UNSPEC,
	पूर्ण;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	काष्ठा bpf_cpumap_val value;
	bool use_separators = true;
	bool stress_mode = false;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	पूर्णांक err = EXIT_FAIL;
	अक्षर filename[256];
	पूर्णांक added_cpus = 0;
	पूर्णांक दीर्घindex = 0;
	पूर्णांक पूर्णांकerval = 2;
	पूर्णांक add_cpu = -1;
	पूर्णांक opt, prog_fd;
	पूर्णांक *cpu, i;
	__u32 qsize;

	n_cpus = get_nprocs_conf();

	/* Notice: choosing he queue size is very important with the
	 * ixgbe driver, because it's driver page recycling trick is
	 * dependend on pages being वापसed quickly.  The number of
	 * out-standing packets in the प्रणाली must be less-than 2x
	 * RX-ring size.
	 */
	qsize = 128+64;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	अगर (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		वापस err;

	अगर (prog_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERR: bpf_prog_load_xattr: %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस err;
	पूर्ण

	अगर (init_tracepoपूर्णांकs(obj) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERR: bpf_program__attach failed\n");
		वापस err;
	पूर्ण

	अगर (init_map_fds(obj) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "bpf_object__find_map_fd_by_name failed\n");
		वापस err;
	पूर्ण
	mark_cpus_unavailable();

	cpu = दो_स्मृति(n_cpus * माप(पूर्णांक));
	अगर (!cpu) अणु
		ख_लिखो(मानक_त्रुटि, "failed to allocate cpu array\n");
		वापस err;
	पूर्ण
	स_रखो(cpu, 0, n_cpus * माप(पूर्णांक));

	/* Parse commands line args */
	जबतक ((opt = getopt_दीर्घ(argc, argv, "hSd:s:p:q:c:xzFf:e:r:m:",
				  दीर्घ_options, &दीर्घindex)) != -1) अणु
		चयन (opt) अणु
		हाल 'd':
			अगर (म_माप(optarg) >= IF_NAMESIZE) अणु
				ख_लिखो(मानक_त्रुटि, "ERR: --dev name too long\n");
				जाओ error;
			पूर्ण
			अगरname = (अक्षर *)&अगरname_buf;
			म_नकलन(अगरname, optarg, IF_NAMESIZE);
			अगरindex = अगर_nametoindex(अगरname);
			अगर (अगरindex == 0) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERR: --dev name unknown err(%d):%s\n",
					त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
				जाओ error;
			पूर्ण
			अवरोध;
		हाल 's':
			पूर्णांकerval = म_से_प(optarg);
			अवरोध;
		हाल 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
			अवरोध;
		हाल 'x':
			stress_mode = true;
			अवरोध;
		हाल 'z':
			use_separators = false;
			अवरोध;
		हाल 'p':
			/* Selecting eBPF prog to load */
			prog_name = optarg;
			अवरोध;
		हाल 'n':
			mprog_disable = true;
			अवरोध;
		हाल 'f':
			mprog_filename = optarg;
			अवरोध;
		हाल 'e':
			mprog_name = optarg;
			अवरोध;
		हाल 'r':
			redir_पूर्णांकerface = optarg;
			अवरोध;
		हाल 'm':
			redir_map = optarg;
			अवरोध;
		हाल 'c':
			/* Add multiple CPUs */
			add_cpu = म_से_अदीर्घ(optarg, शून्य, 0);
			अगर (add_cpu >= n_cpus) अणु
				ख_लिखो(मानक_त्रुटि,
				"--cpu nr too large for cpumap err(%d):%s\n",
					त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
				जाओ error;
			पूर्ण
			cpu[added_cpus++] = add_cpu;
			अवरोध;
		हाल 'q':
			qsize = म_से_प(optarg);
			अवरोध;
		हाल 'F':
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			अवरोध;
		हाल 'h':
		error:
		शेष:
			मुक्त(cpu);
			usage(argv, obj);
			वापस EXIT_FAIL_OPTION;
		पूर्ण
	पूर्ण

	अगर (!(xdp_flags & XDP_FLAGS_SKB_MODE))
		xdp_flags |= XDP_FLAGS_DRV_MODE;

	/* Required option */
	अगर (अगरindex == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERR: required option --dev missing\n");
		usage(argv, obj);
		err = EXIT_FAIL_OPTION;
		जाओ out;
	पूर्ण
	/* Required option */
	अगर (add_cpu == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERR: required option --cpu missing\n");
		ख_लिखो(मानक_त्रुटि, " Specify multiple --cpu option to add more\n");
		usage(argv, obj);
		err = EXIT_FAIL_OPTION;
		जाओ out;
	पूर्ण

	value.bpf_prog.fd = 0;
	अगर (!mprog_disable)
		value.bpf_prog.fd = load_cpumap_prog(mprog_filename, mprog_name,
						     redir_पूर्णांकerface, redir_map);
	अगर (value.bpf_prog.fd < 0) अणु
		err = value.bpf_prog.fd;
		जाओ out;
	पूर्ण
	value.qsize = qsize;

	क्रम (i = 0; i < added_cpus; i++)
		create_cpu_entry(cpu[i], &value, i, true);

	/* Remove XDP program when program is पूर्णांकerrupted or समाप्तed */
	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	prog = bpf_object__find_program_by_title(obj, prog_name);
	अगर (!prog) अणु
		ख_लिखो(मानक_त्रुटि, "bpf_object__find_program_by_title failed\n");
		जाओ out;
	पूर्ण

	prog_fd = bpf_program__fd(prog);
	अगर (prog_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "bpf_program__fd failed\n");
		जाओ out;
	पूर्ण

	अगर (bpf_set_link_xdp_fd(अगरindex, prog_fd, xdp_flags) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "link set xdp fd failed\n");
		err = EXIT_FAIL_XDP;
		जाओ out;
	पूर्ण

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (err) अणु
		म_लिखो("can't get prog info - %s\n", म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण
	prog_id = info.id;

	stats_poll(पूर्णांकerval, use_separators, prog_name, mprog_name,
		   &value, stress_mode);

	err = EXIT_OK;
out:
	मुक्त(cpu);
	वापस err;
पूर्ण
