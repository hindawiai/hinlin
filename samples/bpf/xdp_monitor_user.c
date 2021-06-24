<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright(c) 2017 Jesper Dangaard Brouer, Red Hat, Inc.
 */
अटल स्थिर अक्षर *__करोc__=
 "XDP monitor tool, based on tracepoints\n"
;

अटल स्थिर अक्षर *__करोc_err_only__=
 " NOTICE: Only tracking XDP redirect errors\n"
 "         Enable TX success stats via '--stats'\n"
 "         (which comes with a per packet processing overhead)\n"
;

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <unistd.h>
#समावेश <क्षेत्र.स>

#समावेश <sys/resource.h>
#समावेश <getopt.h>
#समावेश <net/अगर.h>
#समावेश <समय.स>

#समावेश <संकेत.स>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "bpf_util.h"

क्रमागत map_type अणु
	REसूचीECT_ERR_CNT,
	EXCEPTION_CNT,
	CPUMAP_ENQUEUE_CNT,
	CPUMAP_KTHREAD_CNT,
	DEVMAP_XMIT_CNT,
पूर्ण;

अटल स्थिर अक्षर *स्थिर map_type_strings[] = अणु
	[REसूचीECT_ERR_CNT] = "redirect_err_cnt",
	[EXCEPTION_CNT] = "exception_cnt",
	[CPUMAP_ENQUEUE_CNT] = "cpumap_enqueue_cnt",
	[CPUMAP_KTHREAD_CNT] = "cpumap_kthread_cnt",
	[DEVMAP_XMIT_CNT] = "devmap_xmit_cnt",
पूर्ण;

#घोषणा NUM_MAP 5
#घोषणा NUM_TP 8

अटल पूर्णांक tp_cnt;
अटल पूर्णांक map_cnt;
अटल पूर्णांक verbose = 1;
अटल bool debug = false;
काष्ठा bpf_map *map_data[NUM_MAP] = अणुपूर्ण;
काष्ठा bpf_link *tp_links[NUM_TP] = अणुपूर्ण;
काष्ठा bpf_object *obj;

अटल स्थिर काष्ठा option दीर्घ_options[] = अणु
	अणु"help",	no_argument,		शून्य, 'h' पूर्ण,
	अणु"debug",	no_argument,		शून्य, 'D' पूर्ण,
	अणु"stats",	no_argument,		शून्य, 'S' पूर्ण,
	अणु"sec", 	required_argument,	शून्य, 's' पूर्ण,
	अणु0, 0, शून्य,  0 पूर्ण
पूर्ण;

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	/* Detach tracepoपूर्णांकs */
	जबतक (tp_cnt)
		bpf_link__destroy(tp_links[--tp_cnt]);

	bpf_object__बंद(obj);
	निकास(0);
पूर्ण

/* C standard specअगरies two स्थिरants, निकास_सफल(0) and निकास_त्रुटि(1) */
#घोषणा EXIT_FAIL_MEM	5

अटल व्योम usage(अक्षर *argv[])
अणु
	पूर्णांक i;
	म_लिखो("\nDOCUMENTATION:\n%s\n", __करोc__);
	म_लिखो("\n");
	म_लिखो(" Usage: %s (options-see-below)\n",
	       argv[0]);
	म_लिखो(" Listing options:\n");
	क्रम (i = 0; दीर्घ_options[i].name != 0; i++) अणु
		म_लिखो(" --%-15s", दीर्घ_options[i].name);
		अगर (दीर्घ_options[i].flag != शून्य)
			म_लिखो(" flag (internal value:%d)",
			       *दीर्घ_options[i].flag);
		अन्यथा
			म_लिखो("short-option: -%c",
			       दीर्घ_options[i].val);
		म_लिखो("\n");
	पूर्ण
	म_लिखो("\n");
पूर्ण

#घोषणा न_अंकOSEC_PER_SEC 1000000000 /* 10^9 */
अटल __u64 समय_लो(व्योम)
अणु
	काष्ठा बारpec t;
	पूर्णांक res;

	res = घड़ी_समय_लो(CLOCK_MONOTONIC, &t);
	अगर (res < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Error with gettimeofday! (%i)\n", res);
		निकास(निकास_त्रुटि);
	पूर्ण
	वापस (__u64) t.tv_sec * न_अंकOSEC_PER_SEC + t.tv_nsec;
पूर्ण

क्रमागत अणु
	REसूची_SUCCESS = 0,
	REसूची_ERROR = 1,
पूर्ण;
#घोषणा REसूची_RES_MAX 2
अटल स्थिर अक्षर *redir_names[REसूची_RES_MAX] = अणु
	[REसूची_SUCCESS]	= "Success",
	[REसूची_ERROR]	= "Error",
पूर्ण;
अटल स्थिर अक्षर *err2str(पूर्णांक err)
अणु
	अगर (err < REसूची_RES_MAX)
		वापस redir_names[err];
	वापस शून्य;
पूर्ण
/* क्रमागत xdp_action */
#घोषणा XDP_UNKNOWN	XDP_REसूचीECT + 1
#घोषणा XDP_ACTION_MAX (XDP_UNKNOWN + 1)
अटल स्थिर अक्षर *xdp_action_names[XDP_ACTION_MAX] = अणु
	[XDP_ABORTED]	= "XDP_ABORTED",
	[XDP_DROP]	= "XDP_DROP",
	[XDP_PASS]	= "XDP_PASS",
	[XDP_TX]	= "XDP_TX",
	[XDP_REसूचीECT]	= "XDP_REDIRECT",
	[XDP_UNKNOWN]	= "XDP_UNKNOWN",
पूर्ण;
अटल स्थिर अक्षर *action2str(पूर्णांक action)
अणु
	अगर (action < XDP_ACTION_MAX)
		वापस xdp_action_names[action];
	वापस शून्य;
पूर्ण

/* Common stats data record shared with _kern.c */
काष्ठा datarec अणु
	__u64 processed;
	__u64 dropped;
	__u64 info;
	__u64 err;
पूर्ण;
#घोषणा MAX_CPUS 64

/* Userspace काष्ठाs क्रम collection of stats from maps */
काष्ठा record अणु
	__u64 बारtamp;
	काष्ठा datarec total;
	काष्ठा datarec *cpu;
पूर्ण;
काष्ठा u64rec अणु
	__u64 processed;
पूर्ण;
काष्ठा record_u64 अणु
	/* record क्रम _kern side __u64 values */
	__u64 बारtamp;
	काष्ठा u64rec total;
	काष्ठा u64rec *cpu;
पूर्ण;

काष्ठा stats_record अणु
	काष्ठा record_u64 xdp_redirect[REसूची_RES_MAX];
	काष्ठा record_u64 xdp_exception[XDP_ACTION_MAX];
	काष्ठा record xdp_cpumap_kthपढ़ो;
	काष्ठा record xdp_cpumap_enqueue[MAX_CPUS];
	काष्ठा record xdp_devmap_xmit;
पूर्ण;

अटल bool map_collect_record(पूर्णांक fd, __u32 key, काष्ठा record *rec)
अणु
	/* For percpu maps, userspace माला_लो a value per possible CPU */
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	काष्ठा datarec values[nr_cpus];
	__u64 sum_processed = 0;
	__u64 sum_dropped = 0;
	__u64 sum_info = 0;
	__u64 sum_err = 0;
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
		rec->cpu[i].info = values[i].info;
		sum_info        += values[i].info;
		rec->cpu[i].err = values[i].err;
		sum_err        += values[i].err;
	पूर्ण
	rec->total.processed = sum_processed;
	rec->total.dropped   = sum_dropped;
	rec->total.info      = sum_info;
	rec->total.err       = sum_err;
	वापस true;
पूर्ण

अटल bool map_collect_record_u64(पूर्णांक fd, __u32 key, काष्ठा record_u64 *rec)
अणु
	/* For percpu maps, userspace माला_लो a value per possible CPU */
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	काष्ठा u64rec values[nr_cpus];
	__u64 sum_total = 0;
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
		sum_total            += values[i].processed;
	पूर्ण
	rec->total.processed = sum_total;
	वापस true;
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

अटल द्विगुन calc_period_u64(काष्ठा record_u64 *r, काष्ठा record_u64 *p)
अणु
	द्विगुन period_ = 0;
	__u64 period = 0;

	period = r->बारtamp - p->बारtamp;
	अगर (period > 0)
		period_ = ((द्विगुन) period / न_अंकOSEC_PER_SEC);

	वापस period_;
पूर्ण

अटल द्विगुन calc_pps(काष्ठा datarec *r, काष्ठा datarec *p, द्विगुन period)
अणु
	__u64 packets = 0;
	द्विगुन pps = 0;

	अगर (period > 0) अणु
		packets = r->processed - p->processed;
		pps = packets / period;
	पूर्ण
	वापस pps;
पूर्ण

अटल द्विगुन calc_pps_u64(काष्ठा u64rec *r, काष्ठा u64rec *p, द्विगुन period)
अणु
	__u64 packets = 0;
	द्विगुन pps = 0;

	अगर (period > 0) अणु
		packets = r->processed - p->processed;
		pps = packets / period;
	पूर्ण
	वापस pps;
पूर्ण

अटल द्विगुन calc_drop(काष्ठा datarec *r, काष्ठा datarec *p, द्विगुन period)
अणु
	__u64 packets = 0;
	द्विगुन pps = 0;

	अगर (period > 0) अणु
		packets = r->dropped - p->dropped;
		pps = packets / period;
	पूर्ण
	वापस pps;
पूर्ण

अटल द्विगुन calc_info(काष्ठा datarec *r, काष्ठा datarec *p, द्विगुन period)
अणु
	__u64 packets = 0;
	द्विगुन pps = 0;

	अगर (period > 0) अणु
		packets = r->info - p->info;
		pps = packets / period;
	पूर्ण
	वापस pps;
पूर्ण

अटल द्विगुन calc_err(काष्ठा datarec *r, काष्ठा datarec *p, द्विगुन period)
अणु
	__u64 packets = 0;
	द्विगुन pps = 0;

	अगर (period > 0) अणु
		packets = r->err - p->err;
		pps = packets / period;
	पूर्ण
	वापस pps;
पूर्ण

अटल व्योम stats_prपूर्णांक(काष्ठा stats_record *stats_rec,
			काष्ठा stats_record *stats_prev,
			bool err_only)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	पूर्णांक rec_i = 0, i, to_cpu;
	द्विगुन t = 0, pps = 0;

	/* Header */
	म_लिखो("%-15s %-7s %-12s %-12s %-9s\n",
	       "XDP-event", "CPU:to", "pps", "drop-pps", "extra-info");

	/* tracepoपूर्णांक: xdp:xdp_redirect_* */
	अगर (err_only)
		rec_i = REसूची_ERROR;

	क्रम (; rec_i < REसूची_RES_MAX; rec_i++) अणु
		काष्ठा record_u64 *rec, *prev;
		अक्षर *fmt1 = "%-15s %-7d %'-12.0f %'-12.0f %s\n";
		अक्षर *fmt2 = "%-15s %-7s %'-12.0f %'-12.0f %s\n";

		rec  =  &stats_rec->xdp_redirect[rec_i];
		prev = &stats_prev->xdp_redirect[rec_i];
		t = calc_period_u64(rec, prev);

		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा u64rec *r = &rec->cpu[i];
			काष्ठा u64rec *p = &prev->cpu[i];

			pps = calc_pps_u64(r, p, t);
			अगर (pps > 0)
				म_लिखो(fmt1, "XDP_REDIRECT", i,
				       rec_i ? 0.0: pps, rec_i ? pps : 0.0,
				       err2str(rec_i));
		पूर्ण
		pps = calc_pps_u64(&rec->total, &prev->total, t);
		म_लिखो(fmt2, "XDP_REDIRECT", "total",
		       rec_i ? 0.0: pps, rec_i ? pps : 0.0, err2str(rec_i));
	पूर्ण

	/* tracepoपूर्णांक: xdp:xdp_exception */
	क्रम (rec_i = 0; rec_i < XDP_ACTION_MAX; rec_i++) अणु
		काष्ठा record_u64 *rec, *prev;
		अक्षर *fmt1 = "%-15s %-7d %'-12.0f %'-12.0f %s\n";
		अक्षर *fmt2 = "%-15s %-7s %'-12.0f %'-12.0f %s\n";

		rec  =  &stats_rec->xdp_exception[rec_i];
		prev = &stats_prev->xdp_exception[rec_i];
		t = calc_period_u64(rec, prev);

		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा u64rec *r = &rec->cpu[i];
			काष्ठा u64rec *p = &prev->cpu[i];

			pps = calc_pps_u64(r, p, t);
			अगर (pps > 0)
				म_लिखो(fmt1, "Exception", i,
				       0.0, pps, action2str(rec_i));
		पूर्ण
		pps = calc_pps_u64(&rec->total, &prev->total, t);
		अगर (pps > 0)
			म_लिखो(fmt2, "Exception", "total",
			       0.0, pps, action2str(rec_i));
	पूर्ण

	/* cpumap enqueue stats */
	क्रम (to_cpu = 0; to_cpu < MAX_CPUS; to_cpu++) अणु
		अक्षर *fmt1 = "%-15s %3d:%-3d %'-12.0f %'-12.0f %'-10.2f %s\n";
		अक्षर *fmt2 = "%-15s %3s:%-3d %'-12.0f %'-12.0f %'-10.2f %s\n";
		काष्ठा record *rec, *prev;
		अक्षर *info_str = "";
		द्विगुन drop, info;

		rec  =  &stats_rec->xdp_cpumap_enqueue[to_cpu];
		prev = &stats_prev->xdp_cpumap_enqueue[to_cpu];
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps  = calc_pps(r, p, t);
			drop = calc_drop(r, p, t);
			info = calc_info(r, p, t);
			अगर (info > 0) अणु
				info_str = "bulk-average";
				info = pps / info; /* calc average bulk size */
			पूर्ण
			अगर (pps > 0)
				म_लिखो(fmt1, "cpumap-enqueue",
				       i, to_cpu, pps, drop, info, info_str);
		पूर्ण
		pps = calc_pps(&rec->total, &prev->total, t);
		अगर (pps > 0) अणु
			drop = calc_drop(&rec->total, &prev->total, t);
			info = calc_info(&rec->total, &prev->total, t);
			अगर (info > 0) अणु
				info_str = "bulk-average";
				info = pps / info; /* calc average bulk size */
			पूर्ण
			म_लिखो(fmt2, "cpumap-enqueue",
			       "sum", to_cpu, pps, drop, info, info_str);
		पूर्ण
	पूर्ण

	/* cpumap kthपढ़ो stats */
	अणु
		अक्षर *fmt1 = "%-15s %-7d %'-12.0f %'-12.0f %'-10.0f %s\n";
		अक्षर *fmt2 = "%-15s %-7s %'-12.0f %'-12.0f %'-10.0f %s\n";
		काष्ठा record *rec, *prev;
		द्विगुन drop, info;
		अक्षर *i_str = "";

		rec  =  &stats_rec->xdp_cpumap_kthपढ़ो;
		prev = &stats_prev->xdp_cpumap_kthपढ़ो;
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps  = calc_pps(r, p, t);
			drop = calc_drop(r, p, t);
			info = calc_info(r, p, t);
			अगर (info > 0)
				i_str = "sched";
			अगर (pps > 0 || drop > 0)
				म_लिखो(fmt1, "cpumap-kthread",
				       i, pps, drop, info, i_str);
		पूर्ण
		pps = calc_pps(&rec->total, &prev->total, t);
		drop = calc_drop(&rec->total, &prev->total, t);
		info = calc_info(&rec->total, &prev->total, t);
		अगर (info > 0)
			i_str = "sched-sum";
		म_लिखो(fmt2, "cpumap-kthread", "total", pps, drop, info, i_str);
	पूर्ण

	/* devmap nकरो_xdp_xmit stats */
	अणु
		अक्षर *fmt1 = "%-15s %-7d %'-12.0f %'-12.0f %'-10.2f %s %s\n";
		अक्षर *fmt2 = "%-15s %-7s %'-12.0f %'-12.0f %'-10.2f %s %s\n";
		काष्ठा record *rec, *prev;
		द्विगुन drop, info, err;
		अक्षर *i_str = "";
		अक्षर *err_str = "";

		rec  =  &stats_rec->xdp_devmap_xmit;
		prev = &stats_prev->xdp_devmap_xmit;
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps  = calc_pps(r, p, t);
			drop = calc_drop(r, p, t);
			info = calc_info(r, p, t);
			err  = calc_err(r, p, t);
			अगर (info > 0) अणु
				i_str = "bulk-average";
				info = (pps+drop) / info; /* calc avg bulk */
			पूर्ण
			अगर (err > 0)
				err_str = "drv-err";
			अगर (pps > 0 || drop > 0)
				म_लिखो(fmt1, "devmap-xmit",
				       i, pps, drop, info, i_str, err_str);
		पूर्ण
		pps = calc_pps(&rec->total, &prev->total, t);
		drop = calc_drop(&rec->total, &prev->total, t);
		info = calc_info(&rec->total, &prev->total, t);
		err  = calc_err(&rec->total, &prev->total, t);
		अगर (info > 0) अणु
			i_str = "bulk-average";
			info = (pps+drop) / info; /* calc avg bulk */
		पूर्ण
		अगर (err > 0)
			err_str = "drv-err";
		म_लिखो(fmt2, "devmap-xmit", "total", pps, drop,
		       info, i_str, err_str);
	पूर्ण

	म_लिखो("\n");
पूर्ण

अटल bool stats_collect(काष्ठा stats_record *rec)
अणु
	पूर्णांक fd;
	पूर्णांक i;

	/* TODO: Detect अगर someone unloaded the perf event_fd's, as
	 * this can happen by someone running perf-record -e
	 */

	fd = bpf_map__fd(map_data[REसूचीECT_ERR_CNT]);
	क्रम (i = 0; i < REसूची_RES_MAX; i++)
		map_collect_record_u64(fd, i, &rec->xdp_redirect[i]);

	fd = bpf_map__fd(map_data[EXCEPTION_CNT]);
	क्रम (i = 0; i < XDP_ACTION_MAX; i++) अणु
		map_collect_record_u64(fd, i, &rec->xdp_exception[i]);
	पूर्ण

	fd = bpf_map__fd(map_data[CPUMAP_ENQUEUE_CNT]);
	क्रम (i = 0; i < MAX_CPUS; i++)
		map_collect_record(fd, i, &rec->xdp_cpumap_enqueue[i]);

	fd = bpf_map__fd(map_data[CPUMAP_KTHREAD_CNT]);
	map_collect_record(fd, 0, &rec->xdp_cpumap_kthपढ़ो);

	fd = bpf_map__fd(map_data[DEVMAP_XMIT_CNT]);
	map_collect_record(fd, 0, &rec->xdp_devmap_xmit);

	वापस true;
पूर्ण

अटल व्योम *alloc_rec_per_cpu(पूर्णांक record_size)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	व्योम *array;

	array = सुस्मृति(nr_cpus, record_size);
	अगर (!array) अणु
		ख_लिखो(मानक_त्रुटि, "Mem alloc error (nr_cpus:%u)\n", nr_cpus);
		निकास(EXIT_FAIL_MEM);
	पूर्ण
	वापस array;
पूर्ण

अटल काष्ठा stats_record *alloc_stats_record(व्योम)
अणु
	काष्ठा stats_record *rec;
	पूर्णांक rec_sz;
	पूर्णांक i;

	/* Alloc मुख्य stats_record काष्ठाure */
	rec = सुस्मृति(1, माप(*rec));
	अगर (!rec) अणु
		ख_लिखो(मानक_त्रुटि, "Mem alloc error\n");
		निकास(EXIT_FAIL_MEM);
	पूर्ण

	/* Alloc stats stored per CPU क्रम each record */
	rec_sz = माप(काष्ठा u64rec);
	क्रम (i = 0; i < REसूची_RES_MAX; i++)
		rec->xdp_redirect[i].cpu = alloc_rec_per_cpu(rec_sz);

	क्रम (i = 0; i < XDP_ACTION_MAX; i++)
		rec->xdp_exception[i].cpu = alloc_rec_per_cpu(rec_sz);

	rec_sz = माप(काष्ठा datarec);
	rec->xdp_cpumap_kthपढ़ो.cpu = alloc_rec_per_cpu(rec_sz);
	rec->xdp_devmap_xmit.cpu    = alloc_rec_per_cpu(rec_sz);

	क्रम (i = 0; i < MAX_CPUS; i++)
		rec->xdp_cpumap_enqueue[i].cpu = alloc_rec_per_cpu(rec_sz);

	वापस rec;
पूर्ण

अटल व्योम मुक्त_stats_record(काष्ठा stats_record *r)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < REसूची_RES_MAX; i++)
		मुक्त(r->xdp_redirect[i].cpu);

	क्रम (i = 0; i < XDP_ACTION_MAX; i++)
		मुक्त(r->xdp_exception[i].cpu);

	मुक्त(r->xdp_cpumap_kthपढ़ो.cpu);
	मुक्त(r->xdp_devmap_xmit.cpu);

	क्रम (i = 0; i < MAX_CPUS; i++)
		मुक्त(r->xdp_cpumap_enqueue[i].cpu);

	मुक्त(r);
पूर्ण

/* Poपूर्णांकer swap trick */
अटल अंतरभूत व्योम swap(काष्ठा stats_record **a, काष्ठा stats_record **b)
अणु
	काष्ठा stats_record *पंचांगp;

	पंचांगp = *a;
	*a = *b;
	*b = पंचांगp;
पूर्ण

अटल व्योम stats_poll(पूर्णांक पूर्णांकerval, bool err_only)
अणु
	काष्ठा stats_record *rec, *prev;

	rec  = alloc_stats_record();
	prev = alloc_stats_record();
	stats_collect(rec);

	अगर (err_only)
		म_लिखो("\n%s\n", __करोc_err_only__);

	/* Trick to pretty म_लिखो with thousands separators use %' */
	रखो_क्षेत्र(LC_NUMERIC, "en_US");

	/* Header */
	अगर (verbose)
		म_लिखो("\n%s", __करोc__);

	/* TODO Need more advanced stats on error types */
	अगर (verbose) अणु
		म_लिखो(" - Stats map0: %s\n", bpf_map__name(map_data[0]));
		म_लिखो(" - Stats map1: %s\n", bpf_map__name(map_data[1]));
		म_लिखो("\n");
	पूर्ण
	ख_साफ(मानक_निकास);

	जबतक (1) अणु
		swap(&prev, &rec);
		stats_collect(rec);
		stats_prपूर्णांक(rec, prev, err_only);
		ख_साफ(मानक_निकास);
		sleep(पूर्णांकerval);
	पूर्ण

	मुक्त_stats_record(rec);
	मुक्त_stats_record(prev);
पूर्ण

अटल व्योम prपूर्णांक_bpf_prog_info(व्योम)
अणु
	काष्ठा bpf_program *prog;
	काष्ठा bpf_map *map;
	पूर्णांक i = 0;

	/* Prog info */
	म_लिखो("Loaded BPF prog have %d bpf program(s)\n", tp_cnt);
	bpf_object__क्रम_each_program(prog, obj) अणु
		म_लिखो(" - prog_fd[%d] = fd(%d)\n", i, bpf_program__fd(prog));
		i++;
	पूर्ण

	i = 0;
	/* Maps info */
	म_लिखो("Loaded BPF prog have %d map(s)\n", map_cnt);
	bpf_object__क्रम_each_map(map, obj) अणु
		स्थिर अक्षर *name = bpf_map__name(map);
		पूर्णांक fd		 = bpf_map__fd(map);

		म_लिखो(" - map_data[%d] = fd(%d) name:%s\n", i, fd, name);
		i++;
	पूर्ण

	/* Event info */
	म_लिखो("Searching for (max:%d) event file descriptor(s)\n", tp_cnt);
	क्रम (i = 0; i < tp_cnt; i++) अणु
		पूर्णांक fd = bpf_link__fd(tp_links[i]);

		अगर (fd != -1)
			म_लिखो(" - event_fd[%d] = fd(%d)\n", i, fd);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_program *prog;
	पूर्णांक दीर्घindex = 0, opt;
	पूर्णांक ret = निकास_त्रुटि;
	क्रमागत map_type type;
	अक्षर filename[256];

	/* Default settings: */
	bool errors_only = true;
	पूर्णांक पूर्णांकerval = 2;

	/* Parse commands line args */
	जबतक ((opt = getopt_दीर्घ(argc, argv, "hDSs:",
				  दीर्घ_options, &दीर्घindex)) != -1) अणु
		चयन (opt) अणु
		हाल 'D':
			debug = true;
			अवरोध;
		हाल 'S':
			errors_only = false;
			अवरोध;
		हाल 's':
			पूर्णांकerval = म_से_प(optarg);
			अवरोध;
		हाल 'h':
		शेष:
			usage(argv);
			वापस ret;
		पूर्ण
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);

	/* Remove tracepoपूर्णांक program when program is पूर्णांकerrupted or समाप्तed */
	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		म_लिखो("ERROR: opening BPF object file failed\n");
		obj = शून्य;
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		म_लिखो("ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	क्रम (type = 0; type < NUM_MAP; type++) अणु
		map_data[type] =
			bpf_object__find_map_by_name(obj, map_type_strings[type]);

		अगर (libbpf_get_error(map_data[type])) अणु
			म_लिखो("ERROR: finding a map in obj file failed\n");
			जाओ cleanup;
		पूर्ण
		map_cnt++;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		tp_links[tp_cnt] = bpf_program__attach(prog);
		अगर (libbpf_get_error(tp_links[tp_cnt])) अणु
			म_लिखो("ERROR: bpf_program__attach failed\n");
			tp_links[tp_cnt] = शून्य;
			जाओ cleanup;
		पूर्ण
		tp_cnt++;
	पूर्ण

	अगर (debug) अणु
		prपूर्णांक_bpf_prog_info();
	पूर्ण

	/* Unload/stop tracepoपूर्णांक event by closing bpf_link's */
	अगर (errors_only) अणु
		/* The bpf_link[i] depend on the order of
		 * the functions was defined in _kern.c
		 */
		bpf_link__destroy(tp_links[2]);	/* tracepoपूर्णांक/xdp/xdp_redirect */
		tp_links[2] = शून्य;

		bpf_link__destroy(tp_links[3]);	/* tracepoपूर्णांक/xdp/xdp_redirect_map */
		tp_links[3] = शून्य;
	पूर्ण

	stats_poll(पूर्णांकerval, errors_only);

	ret = निकास_सफल;

cleanup:
	/* Detach tracepoपूर्णांकs */
	जबतक (tp_cnt)
		bpf_link__destroy(tp_links[--tp_cnt]);

	bpf_object__बंद(obj);
	वापस ret;
पूर्ण
