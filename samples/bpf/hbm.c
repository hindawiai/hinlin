<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * Example program क्रम Host Bandwidth Managment
 *
 * This program loads a cgroup skb BPF program to enक्रमce cgroup output
 * (egress) or input (ingress) bandwidth limits.
 *
 * USAGE: hbm [-d] [-l] [-n <id>] [-r <rate>] [-s] [-t <secs>] [-w] [-h] [prog]
 *   Where:
 *    -d	Prपूर्णांक BPF trace debug buffer
 *    -l	Also limit flows करोing loopback
 *    -n <#>	To create cgroup \"/hbm#\" and attach prog
 *		Default is /hbm1
 *    --no_cn   Do not वापस cn notअगरications
 *    -r <rate>	Rate limit in Mbps
 *    -s	Get HBM stats (marked, dropped, etc.)
 *    -t <समय>	Exit after specअगरied seconds (शेष is 0)
 *    -w	Work conserving flag. cgroup can increase its bandwidth
 *		beyond the rate limit specअगरied जबतक there is available
 *		bandwidth. Current implementation assumes there is only
 *		NIC (eth0), but can be extended to support multiple NICs.
 *		Currrently only supported क्रम egress.
 *    -h	Prपूर्णांक this info
 *    prog	BPF program file name. Name शेषs to hbm_out_kern.o
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <निश्चित.स>
#समावेश <sys/resource.h>
#समावेश <sys/समय.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/unistd.h>
#समावेश <linux/compiler.h>

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>
#समावेश <getopt.h>

#समावेश "bpf_rlimit.h"
#समावेश "cgroup_helpers.h"
#समावेश "hbm.h"
#समावेश "bpf_util.h"
#समावेश <bpf/libbpf.h>

bool outFlag = true;
पूर्णांक minRate = 1000;		/* cgroup rate limit in Mbps */
पूर्णांक rate = 1000;		/* can grow अगर rate conserving is enabled */
पूर्णांक dur = 1;
bool stats_flag;
bool loopback_flag;
bool debugFlag;
bool work_conserving_flag;
bool no_cn_flag;
bool edt_flag;

अटल व्योम Usage(व्योम);
अटल व्योम पढ़ो_trace_pipe2(व्योम);
अटल व्योम करो_error(अक्षर *msg, bool त्रुटि_सं_flag);

#घोषणा DEBUGFS "/sys/kernel/debug/tracing/"

अटल काष्ठा bpf_program *bpf_prog;
अटल काष्ठा bpf_object *obj;
अटल पूर्णांक queue_stats_fd;

अटल व्योम पढ़ो_trace_pipe2(व्योम)
अणु
	पूर्णांक trace_fd;
	खाता *outf;
	अक्षर *outFname = "hbm_out.log";

	trace_fd = खोलो(DEBUGFS "trace_pipe", O_RDONLY, 0);
	अगर (trace_fd < 0) अणु
		म_लिखो("Error opening trace_pipe\n");
		वापस;
	पूर्ण

//	Future support of ingress
//	अगर (!outFlag)
//		outFname = "hbm_in.log";
	outf = ख_खोलो(outFname, "w");

	अगर (outf == शून्य)
		म_लिखो("Error creating %s\n", outFname);

	जबतक (1) अणु
		अटल अक्षर buf[4097];
		sमाप_प्रकार sz;

		sz = पढ़ो(trace_fd, buf, माप(buf) - 1);
		अगर (sz > 0) अणु
			buf[sz] = 0;
			माला_दो(buf);
			अगर (outf != शून्य) अणु
				ख_लिखो(outf, "%s\n", buf);
				ख_साफ(outf);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम करो_error(अक्षर *msg, bool त्रुटि_सं_flag)
अणु
	अगर (त्रुटि_सं_flag)
		म_लिखो("ERROR: %s, errno: %d\n", msg, त्रुटि_सं);
	अन्यथा
		म_लिखो("ERROR: %s\n", msg);
	निकास(1);
पूर्ण

अटल पूर्णांक prog_load(अक्षर *prog)
अणु
	obj = bpf_object__खोलो_file(prog, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		म_लिखो("ERROR: opening BPF object file failed\n");
		वापस 1;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		म_लिखो("ERROR: loading BPF object file failed\n");
		जाओ err;
	पूर्ण

	bpf_prog = bpf_object__find_program_by_title(obj, "cgroup_skb/egress");
	अगर (!bpf_prog) अणु
		म_लिखो("ERROR: finding a prog in obj file failed\n");
		जाओ err;
	पूर्ण

	queue_stats_fd = bpf_object__find_map_fd_by_name(obj, "queue_stats");
	अगर (queue_stats_fd < 0) अणु
		म_लिखो("ERROR: finding a map in obj file failed\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	bpf_object__बंद(obj);
	वापस 1;
पूर्ण

अटल पूर्णांक run_bpf_prog(अक्षर *prog, पूर्णांक cg_id)
अणु
	काष्ठा hbm_queue_stats qstats = अणु0पूर्ण;
	अक्षर cg_dir[100], cg_pin_path[100];
	काष्ठा bpf_link *link = शून्य;
	पूर्णांक key = 0;
	पूर्णांक cg1 = 0;
	पूर्णांक rc = 0;

	प्र_लिखो(cg_dir, "/hbm%d", cg_id);
	rc = prog_load(prog);
	अगर (rc != 0)
		वापस rc;

	अगर (setup_cgroup_environment()) अणु
		म_लिखो("ERROR: setting cgroup environment\n");
		जाओ err;
	पूर्ण
	cg1 = create_and_get_cgroup(cg_dir);
	अगर (!cg1) अणु
		म_लिखो("ERROR: create_and_get_cgroup\n");
		जाओ err;
	पूर्ण
	अगर (join_cgroup(cg_dir)) अणु
		म_लिखो("ERROR: join_cgroup\n");
		जाओ err;
	पूर्ण

	qstats.rate = rate;
	qstats.stats = stats_flag ? 1 : 0;
	qstats.loopback = loopback_flag ? 1 : 0;
	qstats.no_cn = no_cn_flag ? 1 : 0;
	अगर (bpf_map_update_elem(queue_stats_fd, &key, &qstats, BPF_ANY)) अणु
		म_लिखो("ERROR: Could not update map element\n");
		जाओ err;
	पूर्ण

	अगर (!outFlag)
		bpf_program__set_expected_attach_type(bpf_prog, BPF_CGROUP_INET_INGRESS);

	link = bpf_program__attach_cgroup(bpf_prog, cg1);
	अगर (libbpf_get_error(link)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach_cgroup failed\n");
		जाओ err;
	पूर्ण

	प्र_लिखो(cg_pin_path, "/sys/fs/bpf/hbm%d", cg_id);
	rc = bpf_link__pin(link, cg_pin_path);
	अगर (rc < 0) अणु
		म_लिखो("ERROR: bpf_link__pin failed: %d\n", rc);
		जाओ err;
	पूर्ण

	अगर (work_conserving_flag) अणु
		काष्ठा समयval t0, t_last, t_new;
		खाता *fin;
		अचिन्हित दीर्घ दीर्घ last_eth_tx_bytes, new_eth_tx_bytes;
		चिन्हित दीर्घ दीर्घ last_cg_tx_bytes, new_cg_tx_bytes;
		चिन्हित दीर्घ दीर्घ delta_समय, delta_bytes, delta_rate;
		पूर्णांक delta_ms;
#घोषणा DELTA_RATE_CHECK 10000		/* in us */
#घोषणा RATE_THRESHOLD 9500000000	/* 9.5 Gbps */

		bpf_map_lookup_elem(queue_stats_fd, &key, &qstats);
		अगर (समय_लोofday(&t0, शून्य) < 0)
			करो_error("gettimeofday failed", true);
		t_last = t0;
		fin = ख_खोलो("/sys/class/net/eth0/statistics/tx_bytes", "r");
		अगर (ख_पूछो(fin, "%llu", &last_eth_tx_bytes) != 1)
			करो_error("fscanf fails", false);
		ख_बंद(fin);
		last_cg_tx_bytes = qstats.bytes_total;
		जबतक (true) अणु
			usleep(DELTA_RATE_CHECK);
			अगर (समय_लोofday(&t_new, शून्य) < 0)
				करो_error("gettimeofday failed", true);
			delta_ms = (t_new.tv_sec - t0.tv_sec) * 1000 +
				(t_new.tv_usec - t0.tv_usec)/1000;
			अगर (delta_ms > dur * 1000)
				अवरोध;
			delta_समय = (t_new.tv_sec - t_last.tv_sec) * 1000000 +
				(t_new.tv_usec - t_last.tv_usec);
			अगर (delta_समय == 0)
				जारी;
			t_last = t_new;
			fin = ख_खोलो("/sys/class/net/eth0/statistics/tx_bytes",
				    "r");
			अगर (ख_पूछो(fin, "%llu", &new_eth_tx_bytes) != 1)
				करो_error("fscanf fails", false);
			ख_बंद(fin);
			म_लिखो("  new_eth_tx_bytes:%llu\n",
			       new_eth_tx_bytes);
			bpf_map_lookup_elem(queue_stats_fd, &key, &qstats);
			new_cg_tx_bytes = qstats.bytes_total;
			delta_bytes = new_eth_tx_bytes - last_eth_tx_bytes;
			last_eth_tx_bytes = new_eth_tx_bytes;
			delta_rate = (delta_bytes * 8000000) / delta_समय;
			म_लिखो("%5d - eth_rate:%.1fGbps cg_rate:%.3fGbps",
			       delta_ms, delta_rate/1000000000.0,
			       rate/1000.0);
			अगर (delta_rate < RATE_THRESHOLD) अणु
				/* can increase cgroup rate limit, but first
				 * check अगर we are using the current limit.
				 * Currently increasing by 6.25%, unknown
				 * अगर that is the optimal rate.
				 */
				पूर्णांक rate_dअगरf100;

				delta_bytes = new_cg_tx_bytes -
					last_cg_tx_bytes;
				last_cg_tx_bytes = new_cg_tx_bytes;
				delta_rate = (delta_bytes * 8000000) /
					delta_समय;
				म_लिखो(" rate:%.3fGbps",
				       delta_rate/1000000000.0);
				rate_dअगरf100 = (((दीर्घ दीर्घ)rate)*1000000 -
						     delta_rate) * 100 /
					(((दीर्घ दीर्घ) rate) * 1000000);
				म_लिखो("  rdiff:%d", rate_dअगरf100);
				अगर (rate_dअगरf100  <= 3) अणु
					rate += (rate >> 4);
					अगर (rate > RATE_THRESHOLD / 1000000)
						rate = RATE_THRESHOLD / 1000000;
					qstats.rate = rate;
					म_लिखो(" INC\n");
				पूर्ण अन्यथा अणु
					म_लिखो("\n");
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Need to decrease cgroup rate limit.
				 * Currently decreasing by 12.5%, unknown
				 * अगर that is optimal
				 */
				म_लिखो(" DEC\n");
				rate -= (rate >> 3);
				अगर (rate < minRate)
					rate = minRate;
				qstats.rate = rate;
			पूर्ण
			अगर (bpf_map_update_elem(queue_stats_fd, &key, &qstats, BPF_ANY))
				करो_error("update map element fails", false);
		पूर्ण
	पूर्ण अन्यथा अणु
		sleep(dur);
	पूर्ण
	// Get stats!
	अगर (stats_flag && bpf_map_lookup_elem(queue_stats_fd, &key, &qstats)) अणु
		अक्षर fname[100];
		खाता *fout;

		अगर (!outFlag)
			प्र_लिखो(fname, "hbm.%d.in", cg_id);
		अन्यथा
			प्र_लिखो(fname, "hbm.%d.out", cg_id);
		fout = ख_खोलो(fname, "w");
		ख_लिखो(fout, "id:%d\n", cg_id);
		ख_लिखो(fout, "ERROR: Could not lookup queue_stats\n");
	पूर्ण अन्यथा अगर (stats_flag && qstats.lastPacketTime >
		   qstats.firstPacketTime) अणु
		दीर्घ दीर्घ delta_us = (qstats.lastPacketTime -
				      qstats.firstPacketTime)/1000;
		अचिन्हित पूर्णांक rate_mbps = ((qstats.bytes_total -
					   qstats.bytes_dropped) * 8 /
					  delta_us);
		द्विगुन percent_pkts, percent_bytes;
		अक्षर fname[100];
		खाता *fout;
		पूर्णांक k;
		अटल स्थिर अक्षर *वापसValNames[] = अणु
			"DROP_PKT",
			"ALLOW_PKT",
			"DROP_PKT_CWR",
			"ALLOW_PKT_CWR"
		पूर्ण;
#घोषणा RET_VAL_COUNT 4

// Future support of ingress
//		अगर (!outFlag)
//			प्र_लिखो(fname, "hbm.%d.in", cg_id);
//		अन्यथा
		प्र_लिखो(fname, "hbm.%d.out", cg_id);
		fout = ख_खोलो(fname, "w");
		ख_लिखो(fout, "id:%d\n", cg_id);
		ख_लिखो(fout, "rate_mbps:%d\n", rate_mbps);
		ख_लिखो(fout, "duration:%.1f secs\n",
			(qstats.lastPacketTime - qstats.firstPacketTime) /
			1000000000.0);
		ख_लिखो(fout, "packets:%d\n", (पूर्णांक)qstats.pkts_total);
		ख_लिखो(fout, "bytes_MB:%d\n", (पूर्णांक)(qstats.bytes_total /
						     1000000));
		ख_लिखो(fout, "pkts_dropped:%d\n", (पूर्णांक)qstats.pkts_dropped);
		ख_लिखो(fout, "bytes_dropped_MB:%d\n",
			(पूर्णांक)(qstats.bytes_dropped /
						       1000000));
		// Marked Pkts and Bytes
		percent_pkts = (qstats.pkts_marked * 100.0) /
			(qstats.pkts_total + 1);
		percent_bytes = (qstats.bytes_marked * 100.0) /
			(qstats.bytes_total + 1);
		ख_लिखो(fout, "pkts_marked_percent:%6.2f\n", percent_pkts);
		ख_लिखो(fout, "bytes_marked_percent:%6.2f\n", percent_bytes);

		// Dropped Pkts and Bytes
		percent_pkts = (qstats.pkts_dropped * 100.0) /
			(qstats.pkts_total + 1);
		percent_bytes = (qstats.bytes_dropped * 100.0) /
			(qstats.bytes_total + 1);
		ख_लिखो(fout, "pkts_dropped_percent:%6.2f\n", percent_pkts);
		ख_लिखो(fout, "bytes_dropped_percent:%6.2f\n", percent_bytes);

		// ECN CE markings
		percent_pkts = (qstats.pkts_ecn_ce * 100.0) /
			(qstats.pkts_total + 1);
		ख_लिखो(fout, "pkts_ecn_ce:%6.2f (%d)\n", percent_pkts,
			(पूर्णांक)qstats.pkts_ecn_ce);

		// Average cwnd
		ख_लिखो(fout, "avg cwnd:%d\n",
			(पूर्णांक)(qstats.sum_cwnd / (qstats.sum_cwnd_cnt + 1)));
		// Average rtt
		ख_लिखो(fout, "avg rtt:%d\n",
			(पूर्णांक)(qstats.sum_rtt / (qstats.pkts_total + 1)));
		// Average credit
		अगर (edt_flag)
			ख_लिखो(fout, "avg credit_ms:%.03f\n",
				(qstats.sum_credit /
				 (qstats.pkts_total + 1.0)) / 1000000.0);
		अन्यथा
			ख_लिखो(fout, "avg credit:%d\n",
				(पूर्णांक)(qstats.sum_credit /
				      (1500 * ((पूर्णांक)qstats.pkts_total ) + 1)));

		// Return values stats
		क्रम (k = 0; k < RET_VAL_COUNT; k++) अणु
			percent_pkts = (qstats.वापसValCount[k] * 100.0) /
				(qstats.pkts_total + 1);
			ख_लिखो(fout, "%s:%6.2f (%d)\n", वापसValNames[k],
				percent_pkts, (पूर्णांक)qstats.वापसValCount[k]);
		पूर्ण
		ख_बंद(fout);
	पूर्ण

	अगर (debugFlag)
		पढ़ो_trace_pipe2();
	जाओ cleanup;

err:
	rc = 1;

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);

	अगर (cg1 != -1)
		बंद(cg1);

	अगर (rc != 0)
		cleanup_cgroup_environment();
	वापस rc;
पूर्ण

अटल व्योम Usage(व्योम)
अणु
	म_लिखो("This program loads a cgroup skb BPF program to enforce\n"
	       "cgroup output (egress) bandwidth limits.\n\n"
	       "USAGE: hbm [-o] [-d]  [-l] [-n <id>] [--no_cn] [-r <rate>]\n"
	       "           [-s] [-t <secs>] [-w] [-h] [prog]\n"
	       "  Where:\n"
	       "    -o         indicates egress direction (default)\n"
	       "    -d         print BPF trace debug buffer\n"
	       "    --edt      use fq's Earliest Departure Time\n"
	       "    -l         also limit flows using loopback\n"
	       "    -n <#>     to create cgroup \"/hbm#\" and attach prog\n"
	       "               Default is /hbm1\n"
	       "    --no_cn    disable CN notifications\n"
	       "    -r <rate>  Rate in Mbps\n"
	       "    -s         Update HBM stats\n"
	       "    -t <time>  Exit after specified seconds (default is 0)\n"
	       "    -w	       Work conserving flag. cgroup can increase\n"
	       "               bandwidth beyond the rate limit specified\n"
	       "               while there is available bandwidth. Current\n"
	       "               implementation assumes there is only eth0\n"
	       "               but can be extended to support multiple NICs\n"
	       "    -h         print this info\n"
	       "    prog       BPF program file name. Name defaults to\n"
	       "                 hbm_out_kern.o\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *prog = "hbm_out_kern.o";
	पूर्णांक  k;
	पूर्णांक cg_id = 1;
	अक्षर *optstring = "iodln:r:st:wh";
	काष्ठा option loptions[] = अणु
		अणु"no_cn", 0, शून्य, 1पूर्ण,
		अणु"edt", 0, शून्य, 2पूर्ण,
		अणुशून्य, 0, शून्य, 0पूर्ण
	पूर्ण;

	जबतक ((k = getopt_दीर्घ(argc, argv, optstring, loptions, शून्य)) != -1) अणु
		चयन (k) अणु
		हाल 1:
			no_cn_flag = true;
			अवरोध;
		हाल 2:
			prog = "hbm_edt_kern.o";
			edt_flag = true;
			अवरोध;
		हाल'o':
			अवरोध;
		हाल 'd':
			debugFlag = true;
			अवरोध;
		हाल 'l':
			loopback_flag = true;
			अवरोध;
		हाल 'n':
			cg_id = म_से_प(optarg);
			अवरोध;
		हाल 'r':
			minRate = म_से_प(optarg) * 1.024;
			rate = minRate;
			अवरोध;
		हाल 's':
			stats_flag = true;
			अवरोध;
		हाल 't':
			dur = म_से_प(optarg);
			अवरोध;
		हाल 'w':
			work_conserving_flag = true;
			अवरोध;
		हाल '?':
			अगर (optopt == 'n' || optopt == 'r' || optopt == 't')
				ख_लिखो(मानक_त्रुटि,
					"Option -%c requires an argument.\n\n",
					optopt);
		हाल 'h':
			__fallthrough;
		शेष:
			Usage();
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (optind < argc)
		prog = argv[optind];
	म_लिखो("HBM prog: %s\n", prog != शून्य ? prog : "NULL");

	वापस run_bpf_prog(prog, cg_id);
पूर्ण
