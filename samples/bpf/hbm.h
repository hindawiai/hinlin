<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (c) 2019 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * Include file क्रम Host Bandwidth Management (HBM) programs
 */
काष्ठा hbm_vqueue अणु
	काष्ठा bpf_spin_lock lock;
	/* 4 byte hole */
	अचिन्हित दीर्घ दीर्घ lastसमय;	/* In ns */
	पूर्णांक credit;			/* In bytes */
	अचिन्हित पूर्णांक rate;		/* In bytes per NS << 20 */
पूर्ण;

काष्ठा hbm_queue_stats अणु
	अचिन्हित दीर्घ rate;		/* in Mbps*/
	अचिन्हित दीर्घ stats:1,		/* get HBM stats (marked, dropped,..) */
		loopback:1,		/* also limit flows using loopback */
		no_cn:1;		/* करो not use cn flags */
	अचिन्हित दीर्घ दीर्घ pkts_marked;
	अचिन्हित दीर्घ दीर्घ bytes_marked;
	अचिन्हित दीर्घ दीर्घ pkts_dropped;
	अचिन्हित दीर्घ दीर्घ bytes_dropped;
	अचिन्हित दीर्घ दीर्घ pkts_total;
	अचिन्हित दीर्घ दीर्घ bytes_total;
	अचिन्हित दीर्घ दीर्घ firstPacketTime;
	अचिन्हित दीर्घ दीर्घ lastPacketTime;
	अचिन्हित दीर्घ दीर्घ pkts_ecn_ce;
	अचिन्हित दीर्घ दीर्घ वापसValCount[4];
	अचिन्हित दीर्घ दीर्घ sum_cwnd;
	अचिन्हित दीर्घ दीर्घ sum_rtt;
	अचिन्हित दीर्घ दीर्घ sum_cwnd_cnt;
	दीर्घ दीर्घ sum_credit;
पूर्ण;
