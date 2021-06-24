<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2018 Intel Corporation. */

#समावेश <यंत्र/barrier.h>
#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <libgen.h>
#समावेश <linux/bpf.h>
#समावेश <linux/compiler.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_xdp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/udp.h>
#समावेश <arpa/inet.h>
#समावेश <क्षेत्र.स>
#समावेश <net/ethernet.h>
#समावेश <net/अगर.h>
#समावेश <poll.h>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/capability.h>
#समावेश <sys/mman.h>
#समावेश <sys/resource.h>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <sys/un.h>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश <bpf/libbpf.h>
#समावेश <bpf/xsk.h>
#समावेश <bpf/bpf.h>
#समावेश "xdpsock.h"

#अगर_अघोषित SOL_XDP
#घोषणा SOL_XDP 283
#पूर्ण_अगर

#अगर_अघोषित AF_XDP
#घोषणा AF_XDP 44
#पूर्ण_अगर

#अगर_अघोषित PF_XDP
#घोषणा PF_XDP AF_XDP
#पूर्ण_अगर

#घोषणा NUM_FRAMES (4 * 1024)
#घोषणा MIN_PKT_SIZE 64

#घोषणा DEBUG_HEXDUMP 0

प्रकार __u64 u64;
प्रकार __u32 u32;
प्रकार __u16 u16;
प्रकार __u8  u8;

अटल अचिन्हित दीर्घ prev_समय;

क्रमागत benchmark_type अणु
	BENCH_RXDROP = 0,
	BENCH_TXONLY = 1,
	BENCH_L2FWD = 2,
पूर्ण;

अटल क्रमागत benchmark_type opt_bench = BENCH_RXDROP;
अटल u32 opt_xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
अटल स्थिर अक्षर *opt_अगर = "";
अटल पूर्णांक opt_अगरindex;
अटल पूर्णांक opt_queue;
अटल अचिन्हित दीर्घ opt_duration;
अटल अचिन्हित दीर्घ start_समय;
अटल bool benchmark_करोne;
अटल u32 opt_batch_size = 64;
अटल पूर्णांक opt_pkt_count;
अटल u16 opt_pkt_size = MIN_PKT_SIZE;
अटल u32 opt_pkt_fill_pattern = 0x12345678;
अटल bool opt_extra_stats;
अटल bool opt_quiet;
अटल bool opt_app_stats;
अटल स्थिर अक्षर *opt_irq_str = "";
अटल u32 irq_no;
अटल पूर्णांक irqs_at_init = -1;
अटल पूर्णांक opt_poll;
अटल पूर्णांक opt_पूर्णांकerval = 1;
अटल u32 opt_xdp_bind_flags = XDP_USE_NEED_WAKEUP;
अटल u32 opt_umem_flags;
अटल पूर्णांक opt_unaligned_chunks;
अटल पूर्णांक opt_mmap_flags;
अटल पूर्णांक opt_xsk_frame_size = XSK_UMEM__DEFAULT_FRAME_SIZE;
अटल पूर्णांक opt_समयout = 1000;
अटल bool opt_need_wakeup = true;
अटल u32 opt_num_xsks = 1;
अटल bool opt_busy_poll;
अटल bool opt_reduced_cap;

काष्ठा xsk_ring_stats अणु
	अचिन्हित दीर्घ rx_npkts;
	अचिन्हित दीर्घ tx_npkts;
	अचिन्हित दीर्घ rx_dropped_npkts;
	अचिन्हित दीर्घ rx_invalid_npkts;
	अचिन्हित दीर्घ tx_invalid_npkts;
	अचिन्हित दीर्घ rx_full_npkts;
	अचिन्हित दीर्घ rx_fill_empty_npkts;
	अचिन्हित दीर्घ tx_empty_npkts;
	अचिन्हित दीर्घ prev_rx_npkts;
	अचिन्हित दीर्घ prev_tx_npkts;
	अचिन्हित दीर्घ prev_rx_dropped_npkts;
	अचिन्हित दीर्घ prev_rx_invalid_npkts;
	अचिन्हित दीर्घ prev_tx_invalid_npkts;
	अचिन्हित दीर्घ prev_rx_full_npkts;
	अचिन्हित दीर्घ prev_rx_fill_empty_npkts;
	अचिन्हित दीर्घ prev_tx_empty_npkts;
पूर्ण;

काष्ठा xsk_driver_stats अणु
	अचिन्हित दीर्घ पूर्णांकrs;
	अचिन्हित दीर्घ prev_पूर्णांकrs;
पूर्ण;

काष्ठा xsk_app_stats अणु
	अचिन्हित दीर्घ rx_empty_polls;
	अचिन्हित दीर्घ fill_fail_polls;
	अचिन्हित दीर्घ copy_tx_sendtos;
	अचिन्हित दीर्घ tx_wakeup_sendtos;
	अचिन्हित दीर्घ opt_polls;
	अचिन्हित दीर्घ prev_rx_empty_polls;
	अचिन्हित दीर्घ prev_fill_fail_polls;
	अचिन्हित दीर्घ prev_copy_tx_sendtos;
	अचिन्हित दीर्घ prev_tx_wakeup_sendtos;
	अचिन्हित दीर्घ prev_opt_polls;
पूर्ण;

काष्ठा xsk_umem_info अणु
	काष्ठा xsk_ring_prod fq;
	काष्ठा xsk_ring_cons cq;
	काष्ठा xsk_umem *umem;
	व्योम *buffer;
पूर्ण;

काष्ठा xsk_socket_info अणु
	काष्ठा xsk_ring_cons rx;
	काष्ठा xsk_ring_prod tx;
	काष्ठा xsk_umem_info *umem;
	काष्ठा xsk_socket *xsk;
	काष्ठा xsk_ring_stats ring_stats;
	काष्ठा xsk_app_stats app_stats;
	काष्ठा xsk_driver_stats drv_stats;
	u32 outstanding_tx;
पूर्ण;

अटल पूर्णांक num_socks;
काष्ठा xsk_socket_info *xsks[MAX_SOCKS];
पूर्णांक sock;

अटल अचिन्हित दीर्घ get_nsecs(व्योम)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
	वापस ts.tv_sec * 1000000000UL + ts.tv_nsec;
पूर्ण

अटल व्योम prपूर्णांक_benchmark(bool running)
अणु
	स्थिर अक्षर *bench_str = "INVALID";

	अगर (opt_bench == BENCH_RXDROP)
		bench_str = "rxdrop";
	अन्यथा अगर (opt_bench == BENCH_TXONLY)
		bench_str = "txonly";
	अन्यथा अगर (opt_bench == BENCH_L2FWD)
		bench_str = "l2fwd";

	म_लिखो("%s:%d %s ", opt_अगर, opt_queue, bench_str);
	अगर (opt_xdp_flags & XDP_FLAGS_SKB_MODE)
		म_लिखो("xdp-skb ");
	अन्यथा अगर (opt_xdp_flags & XDP_FLAGS_DRV_MODE)
		म_लिखो("xdp-drv ");
	अन्यथा
		म_लिखो("	");

	अगर (opt_poll)
		म_लिखो("poll() ");

	अगर (running) अणु
		म_लिखो("running...");
		ख_साफ(मानक_निकास);
	पूर्ण
पूर्ण

अटल पूर्णांक xsk_get_xdp_stats(पूर्णांक fd, काष्ठा xsk_socket_info *xsk)
अणु
	काष्ठा xdp_statistics stats;
	socklen_t optlen;
	पूर्णांक err;

	optlen = माप(stats);
	err = माला_लोockopt(fd, SOL_XDP, XDP_STATISTICS, &stats, &optlen);
	अगर (err)
		वापस err;

	अगर (optlen == माप(काष्ठा xdp_statistics)) अणु
		xsk->ring_stats.rx_dropped_npkts = stats.rx_dropped;
		xsk->ring_stats.rx_invalid_npkts = stats.rx_invalid_descs;
		xsk->ring_stats.tx_invalid_npkts = stats.tx_invalid_descs;
		xsk->ring_stats.rx_full_npkts = stats.rx_ring_full;
		xsk->ring_stats.rx_fill_empty_npkts = stats.rx_fill_ring_empty_descs;
		xsk->ring_stats.tx_empty_npkts = stats.tx_ring_empty_descs;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम dump_app_stats(दीर्घ dt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_socks && xsks[i]; i++) अणु
		अक्षर *fmt = "%-18s %'-14.0f %'-14lu\n";
		द्विगुन rx_empty_polls_ps, fill_fail_polls_ps, copy_tx_sendtos_ps,
				tx_wakeup_sendtos_ps, opt_polls_ps;

		rx_empty_polls_ps = (xsks[i]->app_stats.rx_empty_polls -
					xsks[i]->app_stats.prev_rx_empty_polls) * 1000000000. / dt;
		fill_fail_polls_ps = (xsks[i]->app_stats.fill_fail_polls -
					xsks[i]->app_stats.prev_fill_fail_polls) * 1000000000. / dt;
		copy_tx_sendtos_ps = (xsks[i]->app_stats.copy_tx_sendtos -
					xsks[i]->app_stats.prev_copy_tx_sendtos) * 1000000000. / dt;
		tx_wakeup_sendtos_ps = (xsks[i]->app_stats.tx_wakeup_sendtos -
					xsks[i]->app_stats.prev_tx_wakeup_sendtos)
										* 1000000000. / dt;
		opt_polls_ps = (xsks[i]->app_stats.opt_polls -
					xsks[i]->app_stats.prev_opt_polls) * 1000000000. / dt;

		म_लिखो("\n%-18s %-14s %-14s\n", "", "calls/s", "count");
		म_लिखो(fmt, "rx empty polls", rx_empty_polls_ps, xsks[i]->app_stats.rx_empty_polls);
		म_लिखो(fmt, "fill fail polls", fill_fail_polls_ps,
							xsks[i]->app_stats.fill_fail_polls);
		म_लिखो(fmt, "copy tx sendtos", copy_tx_sendtos_ps,
							xsks[i]->app_stats.copy_tx_sendtos);
		म_लिखो(fmt, "tx wakeup sendtos", tx_wakeup_sendtos_ps,
							xsks[i]->app_stats.tx_wakeup_sendtos);
		म_लिखो(fmt, "opt polls", opt_polls_ps, xsks[i]->app_stats.opt_polls);

		xsks[i]->app_stats.prev_rx_empty_polls = xsks[i]->app_stats.rx_empty_polls;
		xsks[i]->app_stats.prev_fill_fail_polls = xsks[i]->app_stats.fill_fail_polls;
		xsks[i]->app_stats.prev_copy_tx_sendtos = xsks[i]->app_stats.copy_tx_sendtos;
		xsks[i]->app_stats.prev_tx_wakeup_sendtos = xsks[i]->app_stats.tx_wakeup_sendtos;
		xsks[i]->app_stats.prev_opt_polls = xsks[i]->app_stats.opt_polls;
	पूर्ण
पूर्ण

अटल bool get_पूर्णांकerrupt_number(व्योम)
अणु
	खाता *f_पूर्णांक_proc;
	अक्षर line[4096];
	bool found = false;

	f_पूर्णांक_proc = ख_खोलो("/proc/interrupts", "r");
	अगर (f_पूर्णांक_proc == शून्य) अणु
		म_लिखो("Failed to open /proc/interrupts.\n");
		वापस found;
	पूर्ण

	जबतक (!ख_पूर्ण(f_पूर्णांक_proc) && !found) अणु
		/* Make sure to पढ़ो a full line at a समय */
		अगर (ख_माला_लो(line, माप(line), f_पूर्णांक_proc) == शून्य ||
				line[म_माप(line) - 1] != '\n') अणु
			म_लिखो("Error reading from interrupts file\n");
			अवरोध;
		पूर्ण

		/* Extract पूर्णांकerrupt number from line */
		अगर (म_माला(line, opt_irq_str) != शून्य) अणु
			irq_no = म_से_प(line);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	ख_बंद(f_पूर्णांक_proc);

	वापस found;
पूर्ण

अटल पूर्णांक get_irqs(व्योम)
अणु
	अक्षर count_path[PATH_MAX];
	पूर्णांक total_पूर्णांकrs = -1;
	खाता *f_count_proc;
	अक्षर line[4096];

	snम_लिखो(count_path, माप(count_path),
		"/sys/kernel/irq/%i/per_cpu_count", irq_no);
	f_count_proc = ख_खोलो(count_path, "r");
	अगर (f_count_proc == शून्य) अणु
		म_लिखो("Failed to open %s\n", count_path);
		वापस total_पूर्णांकrs;
	पूर्ण

	अगर (ख_माला_लो(line, माप(line), f_count_proc) == शून्य ||
			line[म_माप(line) - 1] != '\n') अणु
		म_लिखो("Error reading from %s\n", count_path);
	पूर्ण अन्यथा अणु
		अटल स्थिर अक्षर com[2] = ",";
		अक्षर *token;

		total_पूर्णांकrs = 0;
		token = म_मोहर(line, com);
		जबतक (token != शून्य) अणु
			/* sum up पूर्णांकerrupts across all cores */
			total_पूर्णांकrs += म_से_प(token);
			token = म_मोहर(शून्य, com);
		पूर्ण
	पूर्ण

	ख_बंद(f_count_proc);

	वापस total_पूर्णांकrs;
पूर्ण

अटल व्योम dump_driver_stats(दीर्घ dt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_socks && xsks[i]; i++) अणु
		अक्षर *fmt = "%-18s %'-14.0f %'-14lu\n";
		द्विगुन पूर्णांकrs_ps;
		पूर्णांक n_पूर्णांकs = get_irqs();

		अगर (n_पूर्णांकs < 0) अणु
			म_लिखो("error getting intr info for intr %i\n", irq_no);
			वापस;
		पूर्ण
		xsks[i]->drv_stats.पूर्णांकrs = n_पूर्णांकs - irqs_at_init;

		पूर्णांकrs_ps = (xsks[i]->drv_stats.पूर्णांकrs - xsks[i]->drv_stats.prev_पूर्णांकrs) *
			 1000000000. / dt;

		म_लिखो("\n%-18s %-14s %-14s\n", "", "intrs/s", "count");
		म_लिखो(fmt, "irqs", पूर्णांकrs_ps, xsks[i]->drv_stats.पूर्णांकrs);

		xsks[i]->drv_stats.prev_पूर्णांकrs = xsks[i]->drv_stats.पूर्णांकrs;
	पूर्ण
पूर्ण

अटल व्योम dump_stats(व्योम)
अणु
	अचिन्हित दीर्घ now = get_nsecs();
	दीर्घ dt = now - prev_समय;
	पूर्णांक i;

	prev_समय = now;

	क्रम (i = 0; i < num_socks && xsks[i]; i++) अणु
		अक्षर *fmt = "%-18s %'-14.0f %'-14lu\n";
		द्विगुन rx_pps, tx_pps, dropped_pps, rx_invalid_pps, full_pps, fill_empty_pps,
			tx_invalid_pps, tx_empty_pps;

		rx_pps = (xsks[i]->ring_stats.rx_npkts - xsks[i]->ring_stats.prev_rx_npkts) *
			 1000000000. / dt;
		tx_pps = (xsks[i]->ring_stats.tx_npkts - xsks[i]->ring_stats.prev_tx_npkts) *
			 1000000000. / dt;

		म_लिखो("\n sock%d@", i);
		prपूर्णांक_benchmark(false);
		म_लिखो("\n");

		म_लिखो("%-18s %-14s %-14s %-14.2f\n", "", "pps", "pkts",
		       dt / 1000000000.);
		म_लिखो(fmt, "rx", rx_pps, xsks[i]->ring_stats.rx_npkts);
		म_लिखो(fmt, "tx", tx_pps, xsks[i]->ring_stats.tx_npkts);

		xsks[i]->ring_stats.prev_rx_npkts = xsks[i]->ring_stats.rx_npkts;
		xsks[i]->ring_stats.prev_tx_npkts = xsks[i]->ring_stats.tx_npkts;

		अगर (opt_extra_stats) अणु
			अगर (!xsk_get_xdp_stats(xsk_socket__fd(xsks[i]->xsk), xsks[i])) अणु
				dropped_pps = (xsks[i]->ring_stats.rx_dropped_npkts -
						xsks[i]->ring_stats.prev_rx_dropped_npkts) *
							1000000000. / dt;
				rx_invalid_pps = (xsks[i]->ring_stats.rx_invalid_npkts -
						xsks[i]->ring_stats.prev_rx_invalid_npkts) *
							1000000000. / dt;
				tx_invalid_pps = (xsks[i]->ring_stats.tx_invalid_npkts -
						xsks[i]->ring_stats.prev_tx_invalid_npkts) *
							1000000000. / dt;
				full_pps = (xsks[i]->ring_stats.rx_full_npkts -
						xsks[i]->ring_stats.prev_rx_full_npkts) *
							1000000000. / dt;
				fill_empty_pps = (xsks[i]->ring_stats.rx_fill_empty_npkts -
						xsks[i]->ring_stats.prev_rx_fill_empty_npkts) *
							1000000000. / dt;
				tx_empty_pps = (xsks[i]->ring_stats.tx_empty_npkts -
						xsks[i]->ring_stats.prev_tx_empty_npkts) *
							1000000000. / dt;

				म_लिखो(fmt, "rx dropped", dropped_pps,
				       xsks[i]->ring_stats.rx_dropped_npkts);
				म_लिखो(fmt, "rx invalid", rx_invalid_pps,
				       xsks[i]->ring_stats.rx_invalid_npkts);
				म_लिखो(fmt, "tx invalid", tx_invalid_pps,
				       xsks[i]->ring_stats.tx_invalid_npkts);
				म_लिखो(fmt, "rx queue full", full_pps,
				       xsks[i]->ring_stats.rx_full_npkts);
				म_लिखो(fmt, "fill ring empty", fill_empty_pps,
				       xsks[i]->ring_stats.rx_fill_empty_npkts);
				म_लिखो(fmt, "tx ring empty", tx_empty_pps,
				       xsks[i]->ring_stats.tx_empty_npkts);

				xsks[i]->ring_stats.prev_rx_dropped_npkts =
					xsks[i]->ring_stats.rx_dropped_npkts;
				xsks[i]->ring_stats.prev_rx_invalid_npkts =
					xsks[i]->ring_stats.rx_invalid_npkts;
				xsks[i]->ring_stats.prev_tx_invalid_npkts =
					xsks[i]->ring_stats.tx_invalid_npkts;
				xsks[i]->ring_stats.prev_rx_full_npkts =
					xsks[i]->ring_stats.rx_full_npkts;
				xsks[i]->ring_stats.prev_rx_fill_empty_npkts =
					xsks[i]->ring_stats.rx_fill_empty_npkts;
				xsks[i]->ring_stats.prev_tx_empty_npkts =
					xsks[i]->ring_stats.tx_empty_npkts;
			पूर्ण अन्यथा अणु
				म_लिखो("%-15s\n", "Error retrieving extra stats");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (opt_app_stats)
		dump_app_stats(dt);
	अगर (irq_no)
		dump_driver_stats(dt);
पूर्ण

अटल bool is_benchmark_करोne(व्योम)
अणु
	अगर (opt_duration > 0) अणु
		अचिन्हित दीर्घ dt = (get_nsecs() - start_समय);

		अगर (dt >= opt_duration)
			benchmark_करोne = true;
	पूर्ण
	वापस benchmark_करोne;
पूर्ण

अटल व्योम *poller(व्योम *arg)
अणु
	(व्योम)arg;
	जबतक (!is_benchmark_करोne()) अणु
		sleep(opt_पूर्णांकerval);
		dump_stats();
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	benchmark_करोne = true;
पूर्ण

अटल व्योम __निकास_with_error(पूर्णांक error, स्थिर अक्षर *file, स्थिर अक्षर *func,
			      पूर्णांक line)
अणु
	ख_लिखो(मानक_त्रुटि, "%s:%s:%i: errno: %d/\"%s\"\n", file, func,
		line, error, म_त्रुटि(error));
	निकास(निकास_त्रुटि);
पूर्ण

#घोषणा निकास_with_error(error) __निकास_with_error(error, __खाता__, __func__, __LINE__)

अटल व्योम xdpsock_cleanup(व्योम)
अणु
	काष्ठा xsk_umem *umem = xsks[0]->umem->umem;
	पूर्णांक i, cmd = CLOSE_CONN;

	dump_stats();
	क्रम (i = 0; i < num_socks; i++)
		xsk_socket__delete(xsks[i]->xsk);
	(व्योम)xsk_umem__delete(umem);

	अगर (opt_reduced_cap) अणु
		अगर (ग_लिखो(sock, &cmd, माप(पूर्णांक)) < 0)
			निकास_with_error(त्रुटि_सं);
	पूर्ण
पूर्ण

अटल व्योम swap_mac_addresses(व्योम *data)
अणु
	काष्ठा ether_header *eth = (काष्ठा ether_header *)data;
	काष्ठा ether_addr *src_addr = (काष्ठा ether_addr *)&eth->ether_shost;
	काष्ठा ether_addr *dst_addr = (काष्ठा ether_addr *)&eth->ether_dhost;
	काष्ठा ether_addr पंचांगp;

	पंचांगp = *src_addr;
	*src_addr = *dst_addr;
	*dst_addr = पंचांगp;
पूर्ण

अटल व्योम hex_dump(व्योम *pkt, माप_प्रकार length, u64 addr)
अणु
	स्थिर अचिन्हित अक्षर *address = (अचिन्हित अक्षर *)pkt;
	स्थिर अचिन्हित अक्षर *line = address;
	माप_प्रकार line_size = 32;
	अचिन्हित अक्षर c;
	अक्षर buf[32];
	पूर्णांक i = 0;

	अगर (!DEBUG_HEXDUMP)
		वापस;

	प्र_लिखो(buf, "addr=%llu", addr);
	म_लिखो("length = %zu\n", length);
	म_लिखो("%s | ", buf);
	जबतक (length-- > 0) अणु
		म_लिखो("%02X ", *address++);
		अगर (!(++i % line_size) || (length == 0 && i % line_size)) अणु
			अगर (length == 0) अणु
				जबतक (i++ % line_size)
					म_लिखो("__ ");
			पूर्ण
			म_लिखो(" | ");	/* right बंद */
			जबतक (line < address) अणु
				c = *line++;
				म_लिखो("%c", (c < 33 || c == 255) ? 0x2E : c);
			पूर्ण
			म_लिखो("\n");
			अगर (length > 0)
				म_लिखो("%s | ", buf);
		पूर्ण
	पूर्ण
	म_लिखो("\n");
पूर्ण

अटल व्योम *स_रखो32_htonl(व्योम *dest, u32 val, u32 size)
अणु
	u32 *ptr = (u32 *)dest;
	पूर्णांक i;

	val = htonl(val);

	क्रम (i = 0; i < (size & (~0x3)); i += 4)
		ptr[i >> 2] = val;

	क्रम (; i < size; i++)
		((अक्षर *)dest)[i] = ((अक्षर *)&val)[i & 3];

	वापस dest;
पूर्ण

/*
 * This function code has been taken from
 * Linux kernel lib/checksum.c
 */
अटल अंतरभूत अचिन्हित लघु from32to16(अचिन्हित पूर्णांक x)
अणु
	/* add up 16-bit and 16-bit क्रम 16+c bit */
	x = (x & 0xffff) + (x >> 16);
	/* add up carry.. */
	x = (x & 0xffff) + (x >> 16);
	वापस x;
पूर्ण

/*
 * This function code has been taken from
 * Linux kernel lib/checksum.c
 */
अटल अचिन्हित पूर्णांक करो_csum(स्थिर अचिन्हित अक्षर *buff, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक result = 0;
	पूर्णांक odd;

	अगर (len <= 0)
		जाओ out;
	odd = 1 & (अचिन्हित दीर्घ)buff;
	अगर (odd) अणु
#अगर_घोषित __LITTLE_ENDIAN
		result += (*buff << 8);
#अन्यथा
		result = *buff;
#पूर्ण_अगर
		len--;
		buff++;
	पूर्ण
	अगर (len >= 2) अणु
		अगर (2 & (अचिन्हित दीर्घ)buff) अणु
			result += *(अचिन्हित लघु *)buff;
			len -= 2;
			buff += 2;
		पूर्ण
		अगर (len >= 4) अणु
			स्थिर अचिन्हित अक्षर *end = buff +
						   ((अचिन्हित पूर्णांक)len & ~3);
			अचिन्हित पूर्णांक carry = 0;

			करो अणु
				अचिन्हित पूर्णांक w = *(अचिन्हित पूर्णांक *)buff;

				buff += 4;
				result += carry;
				result += w;
				carry = (w > result);
			पूर्ण जबतक (buff < end);
			result += carry;
			result = (result & 0xffff) + (result >> 16);
		पूर्ण
		अगर (len & 2) अणु
			result += *(अचिन्हित लघु *)buff;
			buff += 2;
		पूर्ण
	पूर्ण
	अगर (len & 1)
#अगर_घोषित __LITTLE_ENDIAN
		result += *buff;
#अन्यथा
		result += (*buff << 8);
#पूर्ण_अगर
	result = from32to16(result);
	अगर (odd)
		result = ((result >> 8) & 0xff) | ((result & 0xff) << 8);
out:
	वापस result;
पूर्ण

__sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl);

/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 *	This function code has been taken from
 *	Linux kernel lib/checksum.c
 */
__sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	वापस (__क्रमce __sum16)~करो_csum(iph, ihl * 4);
पूर्ण

/*
 * Fold a partial checksum
 * This function code has been taken from
 * Linux kernel include/यंत्र-generic/checksum.h
 */
अटल अंतरभूत __sum16 csum_fold(__wsum csum)
अणु
	u32 sum = (__क्रमce u32)csum;

	sum = (sum & 0xffff) + (sum >> 16);
	sum = (sum & 0xffff) + (sum >> 16);
	वापस (__क्रमce __sum16)~sum;
पूर्ण

/*
 * This function code has been taken from
 * Linux kernel lib/checksum.c
 */
अटल अंतरभूत u32 from64to32(u64 x)
अणु
	/* add up 32-bit and 32-bit क्रम 32+c bit */
	x = (x & 0xffffffff) + (x >> 32);
	/* add up carry.. */
	x = (x & 0xffffffff) + (x >> 32);
	वापस (u32)x;
पूर्ण

__wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
			  __u32 len, __u8 proto, __wsum sum);

/*
 * This function code has been taken from
 * Linux kernel lib/checksum.c
 */
__wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
			  __u32 len, __u8 proto, __wsum sum)
अणु
	अचिन्हित दीर्घ दीर्घ s = (__क्रमce u32)sum;

	s += (__क्रमce u32)saddr;
	s += (__क्रमce u32)daddr;
#अगर_घोषित __BIG_ENDIAN__
	s += proto + len;
#अन्यथा
	s += (proto + len) << 8;
#पूर्ण_अगर
	वापस (__क्रमce __wsum)from64to32(s);
पूर्ण

/*
 * This function has been taken from
 * Linux kernel include/यंत्र-generic/checksum.h
 */
अटल अंतरभूत __sum16
csum_tcpudp_magic(__be32 saddr, __be32 daddr, __u32 len,
		  __u8 proto, __wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
पूर्ण

अटल अंतरभूत u16 udp_csum(u32 saddr, u32 daddr, u32 len,
			   u8 proto, u16 *udp_pkt)
अणु
	u32 csum = 0;
	u32 cnt = 0;

	/* udp hdr and data */
	क्रम (; cnt < len; cnt += 2)
		csum += udp_pkt[cnt >> 1];

	वापस csum_tcpudp_magic(saddr, daddr, len, proto, csum);
पूर्ण

#घोषणा ETH_FCS_SIZE 4

#घोषणा PKT_HDR_SIZE (माप(काष्ठा ethhdr) + माप(काष्ठा iphdr) + \
		      माप(काष्ठा udphdr))

#घोषणा PKT_SIZE		(opt_pkt_size - ETH_FCS_SIZE)
#घोषणा IP_PKT_SIZE		(PKT_SIZE - माप(काष्ठा ethhdr))
#घोषणा UDP_PKT_SIZE		(IP_PKT_SIZE - माप(काष्ठा iphdr))
#घोषणा UDP_PKT_DATA_SIZE	(UDP_PKT_SIZE - माप(काष्ठा udphdr))

अटल u8 pkt_data[XSK_UMEM__DEFAULT_FRAME_SIZE];

अटल व्योम gen_eth_hdr_data(व्योम)
अणु
	काष्ठा udphdr *udp_hdr = (काष्ठा udphdr *)(pkt_data +
						   माप(काष्ठा ethhdr) +
						   माप(काष्ठा iphdr));
	काष्ठा iphdr *ip_hdr = (काष्ठा iphdr *)(pkt_data +
						माप(काष्ठा ethhdr));
	काष्ठा ethhdr *eth_hdr = (काष्ठा ethhdr *)pkt_data;

	/* ethernet header */
	स_नकल(eth_hdr->h_dest, "\x3c\xfd\xfe\x9e\x7f\x71", ETH_ALEN);
	स_नकल(eth_hdr->h_source, "\xec\xb1\xd7\x98\x3a\xc0", ETH_ALEN);
	eth_hdr->h_proto = htons(ETH_P_IP);

	/* IP header */
	ip_hdr->version = IPVERSION;
	ip_hdr->ihl = 0x5; /* 20 byte header */
	ip_hdr->tos = 0x0;
	ip_hdr->tot_len = htons(IP_PKT_SIZE);
	ip_hdr->id = 0;
	ip_hdr->frag_off = 0;
	ip_hdr->ttl = IPDEFTTL;
	ip_hdr->protocol = IPPROTO_UDP;
	ip_hdr->saddr = htonl(0x0a0a0a10);
	ip_hdr->daddr = htonl(0x0a0a0a20);

	/* IP header checksum */
	ip_hdr->check = 0;
	ip_hdr->check = ip_fast_csum((स्थिर व्योम *)ip_hdr, ip_hdr->ihl);

	/* UDP header */
	udp_hdr->source = htons(0x1000);
	udp_hdr->dest = htons(0x1000);
	udp_hdr->len = htons(UDP_PKT_SIZE);

	/* UDP data */
	स_रखो32_htonl(pkt_data + PKT_HDR_SIZE, opt_pkt_fill_pattern,
		       UDP_PKT_DATA_SIZE);

	/* UDP header checksum */
	udp_hdr->check = 0;
	udp_hdr->check = udp_csum(ip_hdr->saddr, ip_hdr->daddr, UDP_PKT_SIZE,
				  IPPROTO_UDP, (u16 *)udp_hdr);
पूर्ण

अटल व्योम gen_eth_frame(काष्ठा xsk_umem_info *umem, u64 addr)
अणु
	स_नकल(xsk_umem__get_data(umem->buffer, addr), pkt_data,
	       PKT_SIZE);
पूर्ण

अटल काष्ठा xsk_umem_info *xsk_configure_umem(व्योम *buffer, u64 size)
अणु
	काष्ठा xsk_umem_info *umem;
	काष्ठा xsk_umem_config cfg = अणु
		/* We recommend that you set the fill ring size >= HW RX ring size +
		 * AF_XDP RX ring size. Make sure you fill up the fill ring
		 * with buffers at regular पूर्णांकervals, and you will with this setting
		 * aव्योम allocation failures in the driver. These are usually quite
		 * expensive since drivers have not been written to assume that
		 * allocation failures are common. For regular sockets, kernel
		 * allocated memory is used that only runs out in OOM situations
		 * that should be rare.
		 */
		.fill_size = XSK_RING_PROD__DEFAULT_NUM_DESCS * 2,
		.comp_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
		.frame_size = opt_xsk_frame_size,
		.frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM,
		.flags = opt_umem_flags
	पूर्ण;
	पूर्णांक ret;

	umem = सुस्मृति(1, माप(*umem));
	अगर (!umem)
		निकास_with_error(त्रुटि_सं);

	ret = xsk_umem__create(&umem->umem, buffer, size, &umem->fq, &umem->cq,
			       &cfg);
	अगर (ret)
		निकास_with_error(-ret);

	umem->buffer = buffer;
	वापस umem;
पूर्ण

अटल व्योम xsk_populate_fill_ring(काष्ठा xsk_umem_info *umem)
अणु
	पूर्णांक ret, i;
	u32 idx;

	ret = xsk_ring_prod__reserve(&umem->fq,
				     XSK_RING_PROD__DEFAULT_NUM_DESCS * 2, &idx);
	अगर (ret != XSK_RING_PROD__DEFAULT_NUM_DESCS * 2)
		निकास_with_error(-ret);
	क्रम (i = 0; i < XSK_RING_PROD__DEFAULT_NUM_DESCS * 2; i++)
		*xsk_ring_prod__fill_addr(&umem->fq, idx++) =
			i * opt_xsk_frame_size;
	xsk_ring_prod__submit(&umem->fq, XSK_RING_PROD__DEFAULT_NUM_DESCS * 2);
पूर्ण

अटल काष्ठा xsk_socket_info *xsk_configure_socket(काष्ठा xsk_umem_info *umem,
						    bool rx, bool tx)
अणु
	काष्ठा xsk_socket_config cfg;
	काष्ठा xsk_socket_info *xsk;
	काष्ठा xsk_ring_cons *rxr;
	काष्ठा xsk_ring_prod *txr;
	पूर्णांक ret;

	xsk = सुस्मृति(1, माप(*xsk));
	अगर (!xsk)
		निकास_with_error(त्रुटि_सं);

	xsk->umem = umem;
	cfg.rx_size = XSK_RING_CONS__DEFAULT_NUM_DESCS;
	cfg.tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS;
	अगर (opt_num_xsks > 1 || opt_reduced_cap)
		cfg.libbpf_flags = XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD;
	अन्यथा
		cfg.libbpf_flags = 0;
	cfg.xdp_flags = opt_xdp_flags;
	cfg.bind_flags = opt_xdp_bind_flags;

	rxr = rx ? &xsk->rx : शून्य;
	txr = tx ? &xsk->tx : शून्य;
	ret = xsk_socket__create(&xsk->xsk, opt_अगर, opt_queue, umem->umem,
				 rxr, txr, &cfg);
	अगर (ret)
		निकास_with_error(-ret);

	xsk->app_stats.rx_empty_polls = 0;
	xsk->app_stats.fill_fail_polls = 0;
	xsk->app_stats.copy_tx_sendtos = 0;
	xsk->app_stats.tx_wakeup_sendtos = 0;
	xsk->app_stats.opt_polls = 0;
	xsk->app_stats.prev_rx_empty_polls = 0;
	xsk->app_stats.prev_fill_fail_polls = 0;
	xsk->app_stats.prev_copy_tx_sendtos = 0;
	xsk->app_stats.prev_tx_wakeup_sendtos = 0;
	xsk->app_stats.prev_opt_polls = 0;

	वापस xsk;
पूर्ण

अटल काष्ठा option दीर्घ_options[] = अणु
	अणु"rxdrop", no_argument, 0, 'r'पूर्ण,
	अणु"txonly", no_argument, 0, 't'पूर्ण,
	अणु"l2fwd", no_argument, 0, 'l'पूर्ण,
	अणु"interface", required_argument, 0, 'i'पूर्ण,
	अणु"queue", required_argument, 0, 'q'पूर्ण,
	अणु"poll", no_argument, 0, 'p'पूर्ण,
	अणु"xdp-skb", no_argument, 0, 'S'पूर्ण,
	अणु"xdp-native", no_argument, 0, 'N'पूर्ण,
	अणु"interval", required_argument, 0, 'n'पूर्ण,
	अणु"zero-copy", no_argument, 0, 'z'पूर्ण,
	अणु"copy", no_argument, 0, 'c'पूर्ण,
	अणु"frame-size", required_argument, 0, 'f'पूर्ण,
	अणु"no-need-wakeup", no_argument, 0, 'm'पूर्ण,
	अणु"unaligned", no_argument, 0, 'u'पूर्ण,
	अणु"shared-umem", no_argument, 0, 'M'पूर्ण,
	अणु"force", no_argument, 0, 'F'पूर्ण,
	अणु"duration", required_argument, 0, 'd'पूर्ण,
	अणु"batch-size", required_argument, 0, 'b'पूर्ण,
	अणु"tx-pkt-count", required_argument, 0, 'C'पूर्ण,
	अणु"tx-pkt-size", required_argument, 0, 's'पूर्ण,
	अणु"tx-pkt-pattern", required_argument, 0, 'P'पूर्ण,
	अणु"extra-stats", no_argument, 0, 'x'पूर्ण,
	अणु"quiet", no_argument, 0, 'Q'पूर्ण,
	अणु"app-stats", no_argument, 0, 'a'पूर्ण,
	अणु"irq-string", no_argument, 0, 'I'पूर्ण,
	अणु"busy-poll", no_argument, 0, 'B'पूर्ण,
	अणु"reduce-cap", no_argument, 0, 'R'पूर्ण,
	अणु0, 0, 0, 0पूर्ण
पूर्ण;

अटल व्योम usage(स्थिर अक्षर *prog)
अणु
	स्थिर अक्षर *str =
		"  Usage: %s [OPTIONS]\n"
		"  Options:\n"
		"  -r, --rxdrop		Discard all incoming packets (default)\n"
		"  -t, --txonly		Only send packets\n"
		"  -l, --l2fwd		MAC swap L2 forwarding\n"
		"  -i, --interface=n	Run on interface n\n"
		"  -q, --queue=n	Use queue n (default 0)\n"
		"  -p, --poll		Use poll syscall\n"
		"  -S, --xdp-skb=n	Use XDP skb-mod\n"
		"  -N, --xdp-native=n	Enforce XDP native mode\n"
		"  -n, --interval=n	Specify statistics update interval (default 1 sec).\n"
		"  -z, --zero-copy      Force zero-copy mode.\n"
		"  -c, --copy           Force copy mode.\n"
		"  -m, --no-need-wakeup Turn off use of driver need wakeup flag.\n"
		"  -f, --frame-size=n   Set the frame size (must be a power of two in aligned mode, default is %d).\n"
		"  -u, --unaligned	Enable unaligned chunk placement\n"
		"  -M, --shared-umem	Enable XDP_SHARED_UMEM (cannot be used with -R)\n"
		"  -F, --force		Force loading the XDP prog\n"
		"  -d, --duration=n	Duration in secs to run command.\n"
		"			Default: forever.\n"
		"  -b, --batch-size=n	Batch size for sending or receiving\n"
		"			packets. Default: %d\n"
		"  -C, --tx-pkt-count=n	Number of packets to send.\n"
		"			Default: Continuous packets.\n"
		"  -s, --tx-pkt-size=n	Transmit packet size.\n"
		"			(Default: %d bytes)\n"
		"			Min size: %d, Max size %d.\n"
		"  -P, --tx-pkt-pattern=nPacket fill pattern. Default: 0x%x\n"
		"  -x, --extra-stats	Display extra statistics.\n"
		"  -Q, --quiet          Do not display any stats.\n"
		"  -a, --app-stats	Display application (syscall) statistics.\n"
		"  -I, --irq-string	Display driver interrupt statistics for interface associated with irq-string.\n"
		"  -B, --busy-poll      Busy poll.\n"
		"  -R, --reduce-cap	Use reduced capabilities (cannot be used with -M)\n"
		"\n";
	ख_लिखो(मानक_त्रुटि, str, prog, XSK_UMEM__DEFAULT_FRAME_SIZE,
		opt_batch_size, MIN_PKT_SIZE, MIN_PKT_SIZE,
		XSK_UMEM__DEFAULT_FRAME_SIZE, opt_pkt_fill_pattern);

	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम parse_command_line(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक option_index, c;

	opterr = 0;

	क्रम (;;) अणु
		c = getopt_दीर्घ(argc, argv, "Frtli:q:pSNn:czf:muMd:b:C:s:P:xQaI:BR",
				दीर्घ_options, &option_index);
		अगर (c == -1)
			अवरोध;

		चयन (c) अणु
		हाल 'r':
			opt_bench = BENCH_RXDROP;
			अवरोध;
		हाल 't':
			opt_bench = BENCH_TXONLY;
			अवरोध;
		हाल 'l':
			opt_bench = BENCH_L2FWD;
			अवरोध;
		हाल 'i':
			opt_अगर = optarg;
			अवरोध;
		हाल 'q':
			opt_queue = म_से_प(optarg);
			अवरोध;
		हाल 'p':
			opt_poll = 1;
			अवरोध;
		हाल 'S':
			opt_xdp_flags |= XDP_FLAGS_SKB_MODE;
			opt_xdp_bind_flags |= XDP_COPY;
			अवरोध;
		हाल 'N':
			/* शेष, set below */
			अवरोध;
		हाल 'n':
			opt_पूर्णांकerval = म_से_प(optarg);
			अवरोध;
		हाल 'z':
			opt_xdp_bind_flags |= XDP_ZEROCOPY;
			अवरोध;
		हाल 'c':
			opt_xdp_bind_flags |= XDP_COPY;
			अवरोध;
		हाल 'u':
			opt_umem_flags |= XDP_UMEM_UNALIGNED_CHUNK_FLAG;
			opt_unaligned_chunks = 1;
			opt_mmap_flags = MAP_HUGETLB;
			अवरोध;
		हाल 'F':
			opt_xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			अवरोध;
		हाल 'f':
			opt_xsk_frame_size = म_से_प(optarg);
			अवरोध;
		हाल 'm':
			opt_need_wakeup = false;
			opt_xdp_bind_flags &= ~XDP_USE_NEED_WAKEUP;
			अवरोध;
		हाल 'M':
			opt_num_xsks = MAX_SOCKS;
			अवरोध;
		हाल 'd':
			opt_duration = म_से_प(optarg);
			opt_duration *= 1000000000;
			अवरोध;
		हाल 'b':
			opt_batch_size = म_से_प(optarg);
			अवरोध;
		हाल 'C':
			opt_pkt_count = म_से_प(optarg);
			अवरोध;
		हाल 's':
			opt_pkt_size = म_से_प(optarg);
			अगर (opt_pkt_size > (XSK_UMEM__DEFAULT_FRAME_SIZE) ||
			    opt_pkt_size < MIN_PKT_SIZE) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: Invalid frame size %d\n",
					opt_pkt_size);
				usage(basename(argv[0]));
			पूर्ण
			अवरोध;
		हाल 'P':
			opt_pkt_fill_pattern = म_से_दीर्घ(optarg, शून्य, 16);
			अवरोध;
		हाल 'x':
			opt_extra_stats = 1;
			अवरोध;
		हाल 'Q':
			opt_quiet = 1;
			अवरोध;
		हाल 'a':
			opt_app_stats = 1;
			अवरोध;
		हाल 'I':
			opt_irq_str = optarg;
			अगर (get_पूर्णांकerrupt_number())
				irqs_at_init = get_irqs();
			अगर (irqs_at_init < 0) अणु
				ख_लिखो(मानक_त्रुटि, "ERROR: Failed to get irqs for %s\n", opt_irq_str);
				usage(basename(argv[0]));
			पूर्ण
			अवरोध;
		हाल 'B':
			opt_busy_poll = 1;
			अवरोध;
		हाल 'R':
			opt_reduced_cap = true;
			अवरोध;
		शेष:
			usage(basename(argv[0]));
		पूर्ण
	पूर्ण

	अगर (!(opt_xdp_flags & XDP_FLAGS_SKB_MODE))
		opt_xdp_flags |= XDP_FLAGS_DRV_MODE;

	opt_अगरindex = अगर_nametoindex(opt_अगर);
	अगर (!opt_अगरindex) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: interface \"%s\" does not exist\n",
			opt_अगर);
		usage(basename(argv[0]));
	पूर्ण

	अगर ((opt_xsk_frame_size & (opt_xsk_frame_size - 1)) &&
	    !opt_unaligned_chunks) अणु
		ख_लिखो(मानक_त्रुटि, "--frame-size=%d is not a power of two\n",
			opt_xsk_frame_size);
		usage(basename(argv[0]));
	पूर्ण

	अगर (opt_reduced_cap && opt_num_xsks > 1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: -M and -R cannot be used together\n");
		usage(basename(argv[0]));
	पूर्ण
पूर्ण

अटल व्योम kick_tx(काष्ठा xsk_socket_info *xsk)
अणु
	पूर्णांक ret;

	ret = sendto(xsk_socket__fd(xsk->xsk), शून्य, 0, MSG_DONTWAIT, शून्य, 0);
	अगर (ret >= 0 || त्रुटि_सं == ENOBUFS || त्रुटि_सं == EAGAIN ||
	    त्रुटि_सं == EBUSY || त्रुटि_सं == ENETDOWN)
		वापस;
	निकास_with_error(त्रुटि_सं);
पूर्ण

अटल अंतरभूत व्योम complete_tx_l2fwd(काष्ठा xsk_socket_info *xsk)
अणु
	काष्ठा xsk_umem_info *umem = xsk->umem;
	u32 idx_cq = 0, idx_fq = 0;
	अचिन्हित पूर्णांक rcvd;
	माप_प्रकार ndescs;

	अगर (!xsk->outstanding_tx)
		वापस;

	/* In copy mode, Tx is driven by a syscall so we need to use e.g. sendto() to
	 * really send the packets. In zero-copy mode we करो not have to करो this, since Tx
	 * is driven by the NAPI loop. So as an optimization, we करो not have to call
	 * sendto() all the समय in zero-copy mode क्रम l2fwd.
	 */
	अगर (opt_xdp_bind_flags & XDP_COPY) अणु
		xsk->app_stats.copy_tx_sendtos++;
		kick_tx(xsk);
	पूर्ण

	ndescs = (xsk->outstanding_tx > opt_batch_size) ? opt_batch_size :
		xsk->outstanding_tx;

	/* re-add completed Tx buffers */
	rcvd = xsk_ring_cons__peek(&umem->cq, ndescs, &idx_cq);
	अगर (rcvd > 0) अणु
		अचिन्हित पूर्णांक i;
		पूर्णांक ret;

		ret = xsk_ring_prod__reserve(&umem->fq, rcvd, &idx_fq);
		जबतक (ret != rcvd) अणु
			अगर (ret < 0)
				निकास_with_error(-ret);
			अगर (opt_busy_poll || xsk_ring_prod__needs_wakeup(&umem->fq)) अणु
				xsk->app_stats.fill_fail_polls++;
				recvfrom(xsk_socket__fd(xsk->xsk), शून्य, 0, MSG_DONTWAIT, शून्य,
					 शून्य);
			पूर्ण
			ret = xsk_ring_prod__reserve(&umem->fq, rcvd, &idx_fq);
		पूर्ण

		क्रम (i = 0; i < rcvd; i++)
			*xsk_ring_prod__fill_addr(&umem->fq, idx_fq++) =
				*xsk_ring_cons__comp_addr(&umem->cq, idx_cq++);

		xsk_ring_prod__submit(&xsk->umem->fq, rcvd);
		xsk_ring_cons__release(&xsk->umem->cq, rcvd);
		xsk->outstanding_tx -= rcvd;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम complete_tx_only(काष्ठा xsk_socket_info *xsk,
				    पूर्णांक batch_size)
अणु
	अचिन्हित पूर्णांक rcvd;
	u32 idx;

	अगर (!xsk->outstanding_tx)
		वापस;

	अगर (!opt_need_wakeup || xsk_ring_prod__needs_wakeup(&xsk->tx)) अणु
		xsk->app_stats.tx_wakeup_sendtos++;
		kick_tx(xsk);
	पूर्ण

	rcvd = xsk_ring_cons__peek(&xsk->umem->cq, batch_size, &idx);
	अगर (rcvd > 0) अणु
		xsk_ring_cons__release(&xsk->umem->cq, rcvd);
		xsk->outstanding_tx -= rcvd;
	पूर्ण
पूर्ण

अटल व्योम rx_drop(काष्ठा xsk_socket_info *xsk)
अणु
	अचिन्हित पूर्णांक rcvd, i;
	u32 idx_rx = 0, idx_fq = 0;
	पूर्णांक ret;

	rcvd = xsk_ring_cons__peek(&xsk->rx, opt_batch_size, &idx_rx);
	अगर (!rcvd) अणु
		अगर (opt_busy_poll || xsk_ring_prod__needs_wakeup(&xsk->umem->fq)) अणु
			xsk->app_stats.rx_empty_polls++;
			recvfrom(xsk_socket__fd(xsk->xsk), शून्य, 0, MSG_DONTWAIT, शून्य, शून्य);
		पूर्ण
		वापस;
	पूर्ण

	ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
	जबतक (ret != rcvd) अणु
		अगर (ret < 0)
			निकास_with_error(-ret);
		अगर (opt_busy_poll || xsk_ring_prod__needs_wakeup(&xsk->umem->fq)) अणु
			xsk->app_stats.fill_fail_polls++;
			recvfrom(xsk_socket__fd(xsk->xsk), शून्य, 0, MSG_DONTWAIT, शून्य, शून्य);
		पूर्ण
		ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
	पूर्ण

	क्रम (i = 0; i < rcvd; i++) अणु
		u64 addr = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx)->addr;
		u32 len = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx++)->len;
		u64 orig = xsk_umem__extract_addr(addr);

		addr = xsk_umem__add_offset_to_addr(addr);
		अक्षर *pkt = xsk_umem__get_data(xsk->umem->buffer, addr);

		hex_dump(pkt, len, addr);
		*xsk_ring_prod__fill_addr(&xsk->umem->fq, idx_fq++) = orig;
	पूर्ण

	xsk_ring_prod__submit(&xsk->umem->fq, rcvd);
	xsk_ring_cons__release(&xsk->rx, rcvd);
	xsk->ring_stats.rx_npkts += rcvd;
पूर्ण

अटल व्योम rx_drop_all(व्योम)
अणु
	काष्ठा pollfd fds[MAX_SOCKS] = अणुपूर्ण;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_socks; i++) अणु
		fds[i].fd = xsk_socket__fd(xsks[i]->xsk);
		fds[i].events = POLLIN;
	पूर्ण

	क्रम (;;) अणु
		अगर (opt_poll) अणु
			क्रम (i = 0; i < num_socks; i++)
				xsks[i]->app_stats.opt_polls++;
			ret = poll(fds, num_socks, opt_समयout);
			अगर (ret <= 0)
				जारी;
		पूर्ण

		क्रम (i = 0; i < num_socks; i++)
			rx_drop(xsks[i]);

		अगर (benchmark_करोne)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tx_only(काष्ठा xsk_socket_info *xsk, u32 *frame_nb, पूर्णांक batch_size)
अणु
	u32 idx;
	अचिन्हित पूर्णांक i;

	जबतक (xsk_ring_prod__reserve(&xsk->tx, batch_size, &idx) <
				      batch_size) अणु
		complete_tx_only(xsk, batch_size);
		अगर (benchmark_करोne)
			वापस;
	पूर्ण

	क्रम (i = 0; i < batch_size; i++) अणु
		काष्ठा xdp_desc *tx_desc = xsk_ring_prod__tx_desc(&xsk->tx,
								  idx + i);
		tx_desc->addr = (*frame_nb + i) * opt_xsk_frame_size;
		tx_desc->len = PKT_SIZE;
	पूर्ण

	xsk_ring_prod__submit(&xsk->tx, batch_size);
	xsk->ring_stats.tx_npkts += batch_size;
	xsk->outstanding_tx += batch_size;
	*frame_nb += batch_size;
	*frame_nb %= NUM_FRAMES;
	complete_tx_only(xsk, batch_size);
पूर्ण

अटल अंतरभूत पूर्णांक get_batch_size(पूर्णांक pkt_cnt)
अणु
	अगर (!opt_pkt_count)
		वापस opt_batch_size;

	अगर (pkt_cnt + opt_batch_size <= opt_pkt_count)
		वापस opt_batch_size;

	वापस opt_pkt_count - pkt_cnt;
पूर्ण

अटल व्योम complete_tx_only_all(व्योम)
अणु
	bool pending;
	पूर्णांक i;

	करो अणु
		pending = false;
		क्रम (i = 0; i < num_socks; i++) अणु
			अगर (xsks[i]->outstanding_tx) अणु
				complete_tx_only(xsks[i], opt_batch_size);
				pending = !!xsks[i]->outstanding_tx;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (pending);
पूर्ण

अटल व्योम tx_only_all(व्योम)
अणु
	काष्ठा pollfd fds[MAX_SOCKS] = अणुपूर्ण;
	u32 frame_nb[MAX_SOCKS] = अणुपूर्ण;
	पूर्णांक pkt_cnt = 0;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_socks; i++) अणु
		fds[0].fd = xsk_socket__fd(xsks[i]->xsk);
		fds[0].events = POLLOUT;
	पूर्ण

	जबतक ((opt_pkt_count && pkt_cnt < opt_pkt_count) || !opt_pkt_count) अणु
		पूर्णांक batch_size = get_batch_size(pkt_cnt);

		अगर (opt_poll) अणु
			क्रम (i = 0; i < num_socks; i++)
				xsks[i]->app_stats.opt_polls++;
			ret = poll(fds, num_socks, opt_समयout);
			अगर (ret <= 0)
				जारी;

			अगर (!(fds[0].revents & POLLOUT))
				जारी;
		पूर्ण

		क्रम (i = 0; i < num_socks; i++)
			tx_only(xsks[i], &frame_nb[i], batch_size);

		pkt_cnt += batch_size;

		अगर (benchmark_करोne)
			अवरोध;
	पूर्ण

	अगर (opt_pkt_count)
		complete_tx_only_all();
पूर्ण

अटल व्योम l2fwd(काष्ठा xsk_socket_info *xsk)
अणु
	अचिन्हित पूर्णांक rcvd, i;
	u32 idx_rx = 0, idx_tx = 0;
	पूर्णांक ret;

	complete_tx_l2fwd(xsk);

	rcvd = xsk_ring_cons__peek(&xsk->rx, opt_batch_size, &idx_rx);
	अगर (!rcvd) अणु
		अगर (opt_busy_poll || xsk_ring_prod__needs_wakeup(&xsk->umem->fq)) अणु
			xsk->app_stats.rx_empty_polls++;
			recvfrom(xsk_socket__fd(xsk->xsk), शून्य, 0, MSG_DONTWAIT, शून्य, शून्य);
		पूर्ण
		वापस;
	पूर्ण
	xsk->ring_stats.rx_npkts += rcvd;

	ret = xsk_ring_prod__reserve(&xsk->tx, rcvd, &idx_tx);
	जबतक (ret != rcvd) अणु
		अगर (ret < 0)
			निकास_with_error(-ret);
		complete_tx_l2fwd(xsk);
		अगर (opt_busy_poll || xsk_ring_prod__needs_wakeup(&xsk->tx)) अणु
			xsk->app_stats.tx_wakeup_sendtos++;
			kick_tx(xsk);
		पूर्ण
		ret = xsk_ring_prod__reserve(&xsk->tx, rcvd, &idx_tx);
	पूर्ण

	क्रम (i = 0; i < rcvd; i++) अणु
		u64 addr = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx)->addr;
		u32 len = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx++)->len;
		u64 orig = addr;

		addr = xsk_umem__add_offset_to_addr(addr);
		अक्षर *pkt = xsk_umem__get_data(xsk->umem->buffer, addr);

		swap_mac_addresses(pkt);

		hex_dump(pkt, len, addr);
		xsk_ring_prod__tx_desc(&xsk->tx, idx_tx)->addr = orig;
		xsk_ring_prod__tx_desc(&xsk->tx, idx_tx++)->len = len;
	पूर्ण

	xsk_ring_prod__submit(&xsk->tx, rcvd);
	xsk_ring_cons__release(&xsk->rx, rcvd);

	xsk->ring_stats.tx_npkts += rcvd;
	xsk->outstanding_tx += rcvd;
पूर्ण

अटल व्योम l2fwd_all(व्योम)
अणु
	काष्ठा pollfd fds[MAX_SOCKS] = अणुपूर्ण;
	पूर्णांक i, ret;

	क्रम (;;) अणु
		अगर (opt_poll) अणु
			क्रम (i = 0; i < num_socks; i++) अणु
				fds[i].fd = xsk_socket__fd(xsks[i]->xsk);
				fds[i].events = POLLOUT | POLLIN;
				xsks[i]->app_stats.opt_polls++;
			पूर्ण
			ret = poll(fds, num_socks, opt_समयout);
			अगर (ret <= 0)
				जारी;
		पूर्ण

		क्रम (i = 0; i < num_socks; i++)
			l2fwd(xsks[i]);

		अगर (benchmark_करोne)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम load_xdp_program(अक्षर **argv, काष्ठा bpf_object **obj)
अणु
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type      = BPF_PROG_TYPE_XDP,
	पूर्ण;
	अक्षर xdp_filename[256];
	पूर्णांक prog_fd;

	snम_लिखो(xdp_filename, माप(xdp_filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = xdp_filename;

	अगर (bpf_prog_load_xattr(&prog_load_attr, obj, &prog_fd))
		निकास(निकास_त्रुटि);
	अगर (prog_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: no program found: %s\n",
			म_त्रुटि(prog_fd));
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (bpf_set_link_xdp_fd(opt_अगरindex, prog_fd, opt_xdp_flags) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: link set xdp fd failed\n");
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम enter_xsks_पूर्णांकo_map(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_map *map;
	पूर्णांक i, xsks_map;

	map = bpf_object__find_map_by_name(obj, "xsks_map");
	xsks_map = bpf_map__fd(map);
	अगर (xsks_map < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: no xsks map found: %s\n",
			म_त्रुटि(xsks_map));
			निकास(निकास_त्रुटि);
	पूर्ण

	क्रम (i = 0; i < num_socks; i++) अणु
		पूर्णांक fd = xsk_socket__fd(xsks[i]->xsk);
		पूर्णांक key, ret;

		key = i;
		ret = bpf_map_update_elem(xsks_map, &key, &fd, 0);
		अगर (ret) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_map_update_elem %d\n", i);
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम apply_setsockopt(काष्ठा xsk_socket_info *xsk)
अणु
	पूर्णांक sock_opt;

	अगर (!opt_busy_poll)
		वापस;

	sock_opt = 1;
	अगर (setsockopt(xsk_socket__fd(xsk->xsk), SOL_SOCKET, SO_PREFER_BUSY_POLL,
		       (व्योम *)&sock_opt, माप(sock_opt)) < 0)
		निकास_with_error(त्रुटि_सं);

	sock_opt = 20;
	अगर (setsockopt(xsk_socket__fd(xsk->xsk), SOL_SOCKET, SO_BUSY_POLL,
		       (व्योम *)&sock_opt, माप(sock_opt)) < 0)
		निकास_with_error(त्रुटि_सं);

	sock_opt = opt_batch_size;
	अगर (setsockopt(xsk_socket__fd(xsk->xsk), SOL_SOCKET, SO_BUSY_POLL_BUDGET,
		       (व्योम *)&sock_opt, माप(sock_opt)) < 0)
		निकास_with_error(त्रुटि_सं);
पूर्ण

अटल पूर्णांक recv_xsks_map_fd_from_ctrl_node(पूर्णांक sock, पूर्णांक *_fd)
अणु
	अक्षर cms[CMSG_SPACE(माप(पूर्णांक))];
	काष्ठा cmsghdr *cmsg;
	काष्ठा msghdr msg;
	काष्ठा iovec iov;
	पूर्णांक value;
	पूर्णांक len;

	iov.iov_base = &value;
	iov.iov_len = माप(पूर्णांक);

	msg.msg_name = 0;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = 0;
	msg.msg_control = (caddr_t)cms;
	msg.msg_controllen = माप(cms);

	len = recvmsg(sock, &msg, 0);

	अगर (len < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Recvmsg failed length incorrect.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (len == 0) अणु
		ख_लिखो(मानक_त्रुटि, "Recvmsg failed no data\n");
		वापस -EINVAL;
	पूर्ण

	cmsg = CMSG_FIRSTHDR(&msg);
	*_fd = *(पूर्णांक *)CMSG_DATA(cmsg);

	वापस 0;
पूर्ण

अटल पूर्णांक
recv_xsks_map_fd(पूर्णांक *xsks_map_fd)
अणु
	काष्ठा sockaddr_un server;
	पूर्णांक err;

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	अगर (sock < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Error opening socket stream: %s", म_त्रुटि(त्रुटि_सं));
		वापस त्रुटि_सं;
	पूर्ण

	server.sun_family = AF_UNIX;
	म_नकल(server.sun_path, SOCKET_NAME);

	अगर (connect(sock, (काष्ठा sockaddr *)&server, माप(काष्ठा sockaddr_un)) < 0) अणु
		बंद(sock);
		ख_लिखो(मानक_त्रुटि, "Error connecting stream socket: %s", म_त्रुटि(त्रुटि_सं));
		वापस त्रुटि_सं;
	पूर्ण

	err = recv_xsks_map_fd_from_ctrl_node(sock, xsks_map_fd);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "Error %d receiving fd\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा __user_cap_header_काष्ठा hdr = अणु _LINUX_CAPABILITY_VERSION_3, 0 पूर्ण;
	काष्ठा __user_cap_data_काष्ठा data[2] = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा rlimit r = अणुRLIM_अनन्त, RLIM_अनन्तपूर्ण;
	bool rx = false, tx = false;
	काष्ठा xsk_umem_info *umem;
	काष्ठा bpf_object *obj;
	पूर्णांक xsks_map_fd = 0;
	pthपढ़ो_t pt;
	पूर्णांक i, ret;
	व्योम *bufs;

	parse_command_line(argc, argv);

	अगर (opt_reduced_cap) अणु
		अगर (capget(&hdr, data)  < 0)
			ख_लिखो(मानक_त्रुटि, "Error getting capabilities\n");

		data->effective &= CAP_TO_MASK(CAP_NET_RAW);
		data->permitted &= CAP_TO_MASK(CAP_NET_RAW);

		अगर (capset(&hdr, data) < 0)
			ख_लिखो(मानक_त्रुटि, "Setting capabilities failed\n");

		अगर (capget(&hdr, data)  < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Error getting capabilities\n");
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "Capabilities EFF %x Caps INH %x Caps Per %x\n",
				data[0].effective, data[0].inheritable, data[0].permitted);
			ख_लिखो(मानक_त्रुटि, "Capabilities EFF %x Caps INH %x Caps Per %x\n",
				data[1].effective, data[1].inheritable, data[1].permitted);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (setrlimit(RLIMIT_MEMLOCK, &r)) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: setrlimit(RLIMIT_MEMLOCK) \"%s\"\n",
				म_त्रुटि(त्रुटि_सं));
			निकास(निकास_त्रुटि);
		पूर्ण

		अगर (opt_num_xsks > 1)
			load_xdp_program(argv, &obj);
	पूर्ण

	/* Reserve memory क्रम the umem. Use hugepages अगर unaligned chunk mode */
	bufs = mmap(शून्य, NUM_FRAMES * opt_xsk_frame_size,
		    PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANONYMOUS | opt_mmap_flags, -1, 0);
	अगर (bufs == MAP_FAILED) अणु
		म_लिखो("ERROR: mmap failed\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Create sockets... */
	umem = xsk_configure_umem(bufs, NUM_FRAMES * opt_xsk_frame_size);
	अगर (opt_bench == BENCH_RXDROP || opt_bench == BENCH_L2FWD) अणु
		rx = true;
		xsk_populate_fill_ring(umem);
	पूर्ण
	अगर (opt_bench == BENCH_L2FWD || opt_bench == BENCH_TXONLY)
		tx = true;
	क्रम (i = 0; i < opt_num_xsks; i++)
		xsks[num_socks++] = xsk_configure_socket(umem, rx, tx);

	क्रम (i = 0; i < opt_num_xsks; i++)
		apply_setsockopt(xsks[i]);

	अगर (opt_bench == BENCH_TXONLY) अणु
		gen_eth_hdr_data();

		क्रम (i = 0; i < NUM_FRAMES; i++)
			gen_eth_frame(umem, i * opt_xsk_frame_size);
	पूर्ण

	अगर (opt_num_xsks > 1 && opt_bench != BENCH_TXONLY)
		enter_xsks_पूर्णांकo_map(obj);

	अगर (opt_reduced_cap) अणु
		ret = recv_xsks_map_fd(&xsks_map_fd);
		अगर (ret) अणु
			ख_लिखो(मानक_त्रुटि, "Error %d receiving xsks_map_fd\n", ret);
			निकास_with_error(ret);
		पूर्ण
		अगर (xsks[0]->xsk) अणु
			ret = xsk_socket__update_xskmap(xsks[0]->xsk, xsks_map_fd);
			अगर (ret) अणु
				ख_लिखो(मानक_त्रुटि, "Update of BPF map failed(%d)\n", ret);
				निकास_with_error(ret);
			पूर्ण
		पूर्ण
	पूर्ण

	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);
	संकेत(SIGABRT, पूर्णांक_निकास);

	रखो_क्षेत्र(LC_ALL, "");

	अगर (!opt_quiet) अणु
		ret = pthपढ़ो_create(&pt, शून्य, poller, शून्य);
		अगर (ret)
			निकास_with_error(ret);
	पूर्ण

	prev_समय = get_nsecs();
	start_समय = prev_समय;

	अगर (opt_bench == BENCH_RXDROP)
		rx_drop_all();
	अन्यथा अगर (opt_bench == BENCH_TXONLY)
		tx_only_all();
	अन्यथा
		l2fwd_all();

	benchmark_करोne = true;

	अगर (!opt_quiet)
		pthपढ़ो_join(pt, शून्य);

	xdpsock_cleanup();

	munmap(bufs, NUM_FRAMES * opt_xsk_frame_size);

	वापस 0;
पूर्ण
