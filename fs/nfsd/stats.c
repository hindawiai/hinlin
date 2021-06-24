<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * procfs-based user access to knfsd statistics
 *
 * /proc/net/rpc/nfsd
 *
 * Format:
 *	rc <hits> <misses> <nocache>
 *			Statistsics क्रम the reply cache
 *	fh <stale> <deprecated filehandle cache stats>
 *			statistics क्रम filehandle lookup
 *	io <bytes-पढ़ो> <bytes-written>
 *			statistics क्रम IO throughput
 *	th <thपढ़ोs> <deprecated thपढ़ो usage histogram stats>
 *			number of thपढ़ोs
 *	ra <deprecated ra-cache stats>
 *
 *	plus generic RPC stats (see net/sunrpc/stats.c)
 *
 * Copyright (C) 1995, 1996, 1997 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <net/net_namespace.h>

#समावेश "nfsd.h"

काष्ठा nfsd_stats	nfsdstats;
काष्ठा svc_stat		nfsd_svcstats = अणु
	.program	= &nfsd_program,
पूर्ण;

अटल पूर्णांक nfsd_proc_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i;

	seq_म_लिखो(seq, "rc %lld %lld %lld\nfh %lld 0 0 0 0\nio %lld %lld\n",
		   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_RC_HITS]),
		   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_RC_MISSES]),
		   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_RC_NOCACHE]),
		   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_FH_STALE]),
		   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_IO_READ]),
		   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_IO_WRITE]));

	/* thपढ़ो usage: */
	seq_म_लिखो(seq, "th %u 0", nfsdstats.th_cnt);

	/* deprecated thपढ़ो usage histogram stats */
	क्रम (i = 0; i < 10; i++)
		seq_माला_दो(seq, " 0.000");

	/* deprecated ra-cache stats */
	seq_माला_दो(seq, "\nra 0 0 0 0 0 0 0 0 0 0 0 0\n");

	/* show my rpc info */
	svc_seq_show(seq, &nfsd_svcstats);

#अगर_घोषित CONFIG_NFSD_V4
	/* Show count क्रम inभागidual nfsv4 operations */
	/* Writing operation numbers 0 1 2 also क्रम मुख्यtaining unअगरormity */
	seq_म_लिखो(seq,"proc4ops %u", LAST_NFS4_OP + 1);
	क्रम (i = 0; i <= LAST_NFS4_OP; i++) अणु
		seq_म_लिखो(seq, " %lld",
			   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_NFS4_OP(i)]));
	पूर्ण

	seq_अ_दो(seq, '\n');
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक nfsd_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, nfsd_proc_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops nfsd_proc_ops = अणु
	.proc_खोलो	= nfsd_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

पूर्णांक nfsd_percpu_counters_init(काष्ठा percpu_counter counters[], पूर्णांक num)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; !err && i < num; i++)
		err = percpu_counter_init(&counters[i], 0, GFP_KERNEL);

	अगर (!err)
		वापस 0;

	क्रम (; i > 0; i--)
		percpu_counter_destroy(&counters[i-1]);

	वापस err;
पूर्ण

व्योम nfsd_percpu_counters_reset(काष्ठा percpu_counter counters[], पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		percpu_counter_set(&counters[i], 0);
पूर्ण

व्योम nfsd_percpu_counters_destroy(काष्ठा percpu_counter counters[], पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		percpu_counter_destroy(&counters[i]);
पूर्ण

अटल पूर्णांक nfsd_stat_counters_init(व्योम)
अणु
	वापस nfsd_percpu_counters_init(nfsdstats.counter, NFSD_STATS_COUNTERS_NUM);
पूर्ण

अटल व्योम nfsd_stat_counters_destroy(व्योम)
अणु
	nfsd_percpu_counters_destroy(nfsdstats.counter, NFSD_STATS_COUNTERS_NUM);
पूर्ण

पूर्णांक nfsd_stat_init(व्योम)
अणु
	पूर्णांक err;

	err = nfsd_stat_counters_init();
	अगर (err)
		वापस err;

	svc_proc_रेजिस्टर(&init_net, &nfsd_svcstats, &nfsd_proc_ops);

	वापस 0;
पूर्ण

व्योम nfsd_stat_shutकरोwn(व्योम)
अणु
	nfsd_stat_counters_destroy();
	svc_proc_unरेजिस्टर(&init_net, "nfsd");
पूर्ण
