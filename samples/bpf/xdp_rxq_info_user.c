<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2017 Jesper Dangaard Brouer, Red Hat Inc.
 */
अटल स्थिर अक्षर *__करोc__ = " XDP RX-queue info extract example\n\n"
	"Monitor how many packets per sec (pps) are received\n"
	"per NIC RX queue index and which CPU processed the packet\n"
	;

#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <क्षेत्र.स>
#समावेश <sys/resource.h>
#समावेश <getopt.h>
#समावेश <net/अगर.h>
#समावेश <समय.स>

#समावेश <arpa/inet.h>
#समावेश <linux/अगर_link.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "bpf_util.h"

अटल पूर्णांक अगरindex = -1;
अटल अक्षर अगरname_buf[IF_NAMESIZE];
अटल अक्षर *अगरname;
अटल __u32 prog_id;

अटल __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;

अटल काष्ठा bpf_map *stats_global_map;
अटल काष्ठा bpf_map *rx_queue_index_map;

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
	अणु"no-separators", no_argument,		शून्य, 'z' पूर्ण,
	अणु"action",	required_argument,	शून्य, 'a' पूर्ण,
	अणु"readmem",	no_argument,		शून्य, 'r' पूर्ण,
	अणु"swapmac",	no_argument,		शून्य, 'm' पूर्ण,
	अणु"force",	no_argument,		शून्य, 'F' पूर्ण,
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
	निकास(EXIT_OK);
पूर्ण

काष्ठा config अणु
	__u32 action;
	पूर्णांक अगरindex;
	__u32 options;
पूर्ण;
क्रमागत cfg_options_flags अणु
	NO_TOUCH = 0x0U,
	READ_MEM = 0x1U,
	SWAP_MAC = 0x2U,
पूर्ण;
#घोषणा XDP_ACTION_MAX (XDP_TX + 1)
#घोषणा XDP_ACTION_MAX_STRLEN 11
अटल स्थिर अक्षर *xdp_action_names[XDP_ACTION_MAX] = अणु
	[XDP_ABORTED]	= "XDP_ABORTED",
	[XDP_DROP]	= "XDP_DROP",
	[XDP_PASS]	= "XDP_PASS",
	[XDP_TX]	= "XDP_TX",
पूर्ण;

अटल स्थिर अक्षर *action2str(पूर्णांक action)
अणु
	अगर (action < XDP_ACTION_MAX)
		वापस xdp_action_names[action];
	वापस शून्य;
पूर्ण

अटल पूर्णांक parse_xdp_action(अक्षर *action_str)
अणु
	माप_प्रकार maxlen;
	__u64 action = -1;
	पूर्णांक i;

	क्रम (i = 0; i < XDP_ACTION_MAX; i++) अणु
		maxlen = XDP_ACTION_MAX_STRLEN;
		अगर (म_भेदन(xdp_action_names[i], action_str, maxlen) == 0) अणु
			action = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस action;
पूर्ण

अटल व्योम list_xdp_actions(व्योम)
अणु
	पूर्णांक i;

	म_लिखो("Available XDP --action <options>\n");
	क्रम (i = 0; i < XDP_ACTION_MAX; i++)
		म_लिखो("\t%s\n", xdp_action_names[i]);
	म_लिखो("\n");
पूर्ण

अटल अक्षर* options2str(क्रमागत cfg_options_flags flag)
अणु
	अगर (flag == NO_TOUCH)
		वापस "no_touch";
	अगर (flag & SWAP_MAC)
		वापस "swapmac";
	अगर (flag & READ_MEM)
		वापस "read";
	ख_लिखो(मानक_त्रुटि, "ERR: Unknown config option flags");
	निकास(EXIT_FAIL);
पूर्ण

अटल व्योम usage(अक्षर *argv[])
अणु
	पूर्णांक i;

	म_लिखो("\nDOCUMENTATION:\n%s\n", __करोc__);
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
	म_लिखो("\n");
	list_xdp_actions();
पूर्ण

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
	__u64 issue;
पूर्ण;
काष्ठा record अणु
	__u64 बारtamp;
	काष्ठा datarec total;
	काष्ठा datarec *cpu;
पूर्ण;
काष्ठा stats_record अणु
	काष्ठा record stats;
	काष्ठा record *rxq;
पूर्ण;

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

अटल काष्ठा record *alloc_record_per_rxq(व्योम)
अणु
	अचिन्हित पूर्णांक nr_rxqs = bpf_map__def(rx_queue_index_map)->max_entries;
	काष्ठा record *array;

	array = सुस्मृति(nr_rxqs, माप(काष्ठा record));
	अगर (!array) अणु
		ख_लिखो(मानक_त्रुटि, "Mem alloc error (nr_rxqs:%u)\n", nr_rxqs);
		निकास(EXIT_FAIL_MEM);
	पूर्ण
	वापस array;
पूर्ण

अटल काष्ठा stats_record *alloc_stats_record(व्योम)
अणु
	अचिन्हित पूर्णांक nr_rxqs = bpf_map__def(rx_queue_index_map)->max_entries;
	काष्ठा stats_record *rec;
	पूर्णांक i;

	rec = सुस्मृति(1, माप(काष्ठा stats_record));
	अगर (!rec) अणु
		ख_लिखो(मानक_त्रुटि, "Mem alloc error\n");
		निकास(EXIT_FAIL_MEM);
	पूर्ण
	rec->rxq = alloc_record_per_rxq();
	क्रम (i = 0; i < nr_rxqs; i++)
		rec->rxq[i].cpu = alloc_record_per_cpu();

	rec->stats.cpu = alloc_record_per_cpu();
	वापस rec;
पूर्ण

अटल व्योम मुक्त_stats_record(काष्ठा stats_record *r)
अणु
	अचिन्हित पूर्णांक nr_rxqs = bpf_map__def(rx_queue_index_map)->max_entries;
	पूर्णांक i;

	क्रम (i = 0; i < nr_rxqs; i++)
		मुक्त(r->rxq[i].cpu);

	मुक्त(r->rxq);
	मुक्त(r->stats.cpu);
	मुक्त(r);
पूर्ण

अटल bool map_collect_percpu(पूर्णांक fd, __u32 key, काष्ठा record *rec)
अणु
	/* For percpu maps, userspace माला_लो a value per possible CPU */
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	काष्ठा datarec values[nr_cpus];
	__u64 sum_processed = 0;
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
		rec->cpu[i].issue = values[i].issue;
		sum_issue        += values[i].issue;
	पूर्ण
	rec->total.processed = sum_processed;
	rec->total.issue     = sum_issue;
	वापस true;
पूर्ण

अटल व्योम stats_collect(काष्ठा stats_record *rec)
अणु
	पूर्णांक fd, i, max_rxqs;

	fd = bpf_map__fd(stats_global_map);
	map_collect_percpu(fd, 0, &rec->stats);

	fd = bpf_map__fd(rx_queue_index_map);
	max_rxqs = bpf_map__def(rx_queue_index_map)->max_entries;
	क्रम (i = 0; i < max_rxqs; i++)
		map_collect_percpu(fd, i, &rec->rxq[i]);
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

अटल व्योम stats_prपूर्णांक(काष्ठा stats_record *stats_rec,
			काष्ठा stats_record *stats_prev,
			पूर्णांक action, __u32 cfg_opt)
अणु
	अचिन्हित पूर्णांक nr_rxqs = bpf_map__def(rx_queue_index_map)->max_entries;
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	द्विगुन pps = 0, err = 0;
	काष्ठा record *rec, *prev;
	द्विगुन t;
	पूर्णांक rxq;
	पूर्णांक i;

	/* Header */
	म_लिखो("\nRunning XDP on dev:%s (ifindex:%d) action:%s options:%s\n",
	       अगरname, अगरindex, action2str(action), options2str(cfg_opt));

	/* stats_global_map */
	अणु
		अक्षर *fmt_rx = "%-15s %-7d %'-11.0f %'-10.0f %s\n";
		अक्षर *fm2_rx = "%-15s %-7s %'-11.0f\n";
		अक्षर *errstr = "";

		म_लिखो("%-15s %-7s %-11s %-11s\n",
		       "XDP stats", "CPU", "pps", "issue-pps");

		rec  =  &stats_rec->stats;
		prev = &stats_prev->stats;
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps = calc_pps     (r, p, t);
			err = calc_errs_pps(r, p, t);
			अगर (err > 0)
				errstr = "invalid-ifindex";
			अगर (pps > 0)
				म_लिखो(fmt_rx, "XDP-RX CPU",
					i, pps, err, errstr);
		पूर्ण
		pps  = calc_pps     (&rec->total, &prev->total, t);
		err  = calc_errs_pps(&rec->total, &prev->total, t);
		म_लिखो(fm2_rx, "XDP-RX CPU", "total", pps, err);
	पूर्ण

	/* rx_queue_index_map */
	म_लिखो("\n%-15s %-7s %-11s %-11s\n",
	       "RXQ stats", "RXQ:CPU", "pps", "issue-pps");

	क्रम (rxq = 0; rxq < nr_rxqs; rxq++) अणु
		अक्षर *fmt_rx = "%-15s %3d:%-3d %'-11.0f %'-10.0f %s\n";
		अक्षर *fm2_rx = "%-15s %3d:%-3s %'-11.0f\n";
		अक्षर *errstr = "";
		पूर्णांक rxq_ = rxq;

		/* Last RXQ in map catch overflows */
		अगर (rxq_ == nr_rxqs - 1)
			rxq_ = -1;

		rec  =  &stats_rec->rxq[rxq];
		prev = &stats_prev->rxq[rxq];
		t = calc_period(rec, prev);
		क्रम (i = 0; i < nr_cpus; i++) अणु
			काष्ठा datarec *r = &rec->cpu[i];
			काष्ठा datarec *p = &prev->cpu[i];

			pps = calc_pps     (r, p, t);
			err = calc_errs_pps(r, p, t);
			अगर (err > 0) अणु
				अगर (rxq_ == -1)
					errstr = "map-overflow-RXQ";
				अन्यथा
					errstr = "err";
			पूर्ण
			अगर (pps > 0)
				म_लिखो(fmt_rx, "rx_queue_index",
				       rxq_, i, pps, err, errstr);
		पूर्ण
		pps  = calc_pps     (&rec->total, &prev->total, t);
		err  = calc_errs_pps(&rec->total, &prev->total, t);
		अगर (pps || err)
			म_लिखो(fm2_rx, "rx_queue_index", rxq_, "sum", pps, err);
	पूर्ण
पूर्ण


/* Poपूर्णांकer swap trick */
अटल अंतरभूत व्योम swap(काष्ठा stats_record **a, काष्ठा stats_record **b)
अणु
	काष्ठा stats_record *पंचांगp;

	पंचांगp = *a;
	*a = *b;
	*b = पंचांगp;
पूर्ण

अटल व्योम stats_poll(पूर्णांक पूर्णांकerval, पूर्णांक action, __u32 cfg_opt)
अणु
	काष्ठा stats_record *record, *prev;

	record = alloc_stats_record();
	prev   = alloc_stats_record();
	stats_collect(record);

	जबतक (1) अणु
		swap(&prev, &record);
		stats_collect(record);
		stats_prपूर्णांक(record, prev, action, cfg_opt);
		sleep(पूर्णांकerval);
	पूर्ण

	मुक्त_stats_record(record);
	मुक्त_stats_record(prev);
पूर्ण


पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	__u32 cfg_options= NO_TOUCH ; /* Default: Don't touch packet memory */
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type	= BPF_PROG_TYPE_XDP,
	पूर्ण;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	पूर्णांक prog_fd, map_fd, opt, err;
	bool use_separators = true;
	काष्ठा config cfg = अणु 0 पूर्ण;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	अक्षर filename[256];
	पूर्णांक दीर्घindex = 0;
	पूर्णांक पूर्णांकerval = 2;
	__u32 key = 0;


	अक्षर action_str_buf[XDP_ACTION_MAX_STRLEN + 1 /* क्रम \0 */] = अणु 0 पूर्ण;
	पूर्णांक action = XDP_PASS; /* Default action */
	अक्षर *action_str = शून्य;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	अगर (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		वापस EXIT_FAIL;

	map =  bpf_object__find_map_by_name(obj, "config_map");
	stats_global_map = bpf_object__find_map_by_name(obj, "stats_global_map");
	rx_queue_index_map = bpf_object__find_map_by_name(obj, "rx_queue_index_map");
	अगर (!map || !stats_global_map || !rx_queue_index_map) अणु
		म_लिखो("finding a map in obj file failed\n");
		वापस EXIT_FAIL;
	पूर्ण
	map_fd = bpf_map__fd(map);

	अगर (!prog_fd) अणु
		ख_लिखो(मानक_त्रुटि, "ERR: bpf_prog_load_xattr: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस EXIT_FAIL;
	पूर्ण

	/* Parse commands line args */
	जबतक ((opt = getopt_दीर्घ(argc, argv, "FhSrmzd:s:a:",
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
		हाल 'z':
			use_separators = false;
			अवरोध;
		हाल 'a':
			action_str = (अक्षर *)&action_str_buf;
			म_नकलन(action_str, optarg, XDP_ACTION_MAX_STRLEN);
			अवरोध;
		हाल 'r':
			cfg_options |= READ_MEM;
			अवरोध;
		हाल 'm':
			cfg_options |= SWAP_MAC;
			अवरोध;
		हाल 'F':
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			अवरोध;
		हाल 'h':
		error:
		शेष:
			usage(argv);
			वापस EXIT_FAIL_OPTION;
		पूर्ण
	पूर्ण

	अगर (!(xdp_flags & XDP_FLAGS_SKB_MODE))
		xdp_flags |= XDP_FLAGS_DRV_MODE;

	/* Required option */
	अगर (अगरindex == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERR: required option --dev missing\n");
		usage(argv);
		वापस EXIT_FAIL_OPTION;
	पूर्ण
	cfg.अगरindex = अगरindex;

	/* Parse action string */
	अगर (action_str) अणु
		action = parse_xdp_action(action_str);
		अगर (action < 0) अणु
			ख_लिखो(मानक_त्रुटि, "ERR: Invalid XDP --action: %s\n",
				action_str);
			list_xdp_actions();
			वापस EXIT_FAIL_OPTION;
		पूर्ण
	पूर्ण
	cfg.action = action;

	/* XDP_TX requires changing MAC-addrs, अन्यथा HW may drop */
	अगर (action == XDP_TX)
		cfg_options |= SWAP_MAC;
	cfg.options = cfg_options;

	/* Trick to pretty म_लिखो with thousands separators use %' */
	अगर (use_separators)
		रखो_क्षेत्र(LC_NUMERIC, "en_US");

	/* User-side setup अगरindex in config_map */
	err = bpf_map_update_elem(map_fd, &key, &cfg, 0);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "Store config failed (err:%d)\n", err);
		निकास(EXIT_FAIL_BPF);
	पूर्ण

	/* Remove XDP program when program is पूर्णांकerrupted or समाप्तed */
	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	अगर (bpf_set_link_xdp_fd(अगरindex, prog_fd, xdp_flags) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "link set xdp fd failed\n");
		वापस EXIT_FAIL_XDP;
	पूर्ण

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (err) अणु
		म_लिखो("can't get prog info - %s\n", म_त्रुटि(त्रुटि_सं));
		वापस err;
	पूर्ण
	prog_id = info.id;

	stats_poll(पूर्णांकerval, action, cfg_options);
	वापस EXIT_OK;
पूर्ण
