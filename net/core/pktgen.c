<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Authors:
 * Copyright 2001, 2002 by Robert Olsson <robert.olsson@its.uu.se>
 *                             Uppsala University and
 *                             Swedish University of Agricultural Sciences
 *
 * Alexey Kuznetsov  <kuznet@ms2.inr.ac.ru>
 * Ben Greear <greearb@candelatech.com>
 * Jens Lथआथआs <jens.laas@data.slu.se>
 *
 * A tool क्रम loading the network with preconfigurated packets.
 * The tool is implemented as a linux module.  Parameters are output
 * device, delay (to hard_xmit), number of packets, and whether
 * to use multiple SKBs or just the same one.
 * pktgen uses the installed पूर्णांकerface's output routine.
 *
 * Additional hacking by:
 *
 * Jens.Laas@data.slu.se
 * Improved by ANK. 010120.
 * Improved by ANK even more. 010212.
 * MAC address typo fixed. 010417 --ro
 * Integrated.  020301 --DaveM
 * Added multiskb option 020301 --DaveM
 * Scaling of results. 020417--sigurdur@linpro.no
 * Signअगरicant re-work of the module:
 *   *  Convert to thपढ़ोed model to more efficiently be able to transmit
 *       and receive on multiple पूर्णांकerfaces at once.
 *   *  Converted many counters to __u64 to allow दीर्घer runs.
 *   *  Allow configuration of ranges, like min/max IP address, MACs,
 *       and UDP-ports, क्रम both source and destination, and can
 *       set to use a अक्रमom distribution or sequentially walk the range.
 *   *  Can now change most values after starting.
 *   *  Place 12-byte packet in UDP payload with magic number,
 *       sequence number, and बारtamp.
 *   *  Add receiver code that detects dropped pkts, re-ordered pkts, and
 *       latencies (with micro-second) precision.
 *   *  Add IOCTL पूर्णांकerface to easily get counters & configuration.
 *   --Ben Greear <greearb@candelatech.com>
 *
 * Renamed multiskb to clone_skb and cleaned up sending core क्रम two distinct
 * skb modes. A clone_skb=0 mode क्रम Ben "ranges" work and a clone_skb != 0
 * as a "fastpath" with a configurable number of clones after alloc's.
 * clone_skb=0 means all packets are allocated this also means ranges समय
 * stamps etc can be used. clone_skb=100 means 1 दो_स्मृति is followed by 100
 * clones.
 *
 * Also moved to /proc/net/pktgen/
 * --ro
 *
 * Sept 10:  Fixed thपढ़ोing/locking.  Lots of bone-headed and more clever
 *    mistakes.  Also merged in DaveM's patch in the -pre6 patch.
 * --Ben Greear <greearb@candelatech.com>
 *
 * Integrated to 2.5.x 021029 --Lucio Maciel (luciomaciel@zipmail.com.br)
 *
 * 021124 Finished major redesign and reग_लिखो क्रम new functionality.
 * See Documentation/networking/pktgen.rst क्रम how to use this.
 *
 * The new operation:
 * For each CPU one thपढ़ो/process is created at start. This process checks
 * क्रम running devices in the अगर_list and sends packets until count is 0 it
 * also the thपढ़ो checks the thपढ़ो->control which is used क्रम पूर्णांकer-process
 * communication. controlling process "posts" operations to the thपढ़ोs this
 * way.
 * The अगर_list is RCU रक्षित, and the अगर_lock reमुख्यs to protect updating
 * of अगर_list, from "add_device" as it invoked from userspace (via proc ग_लिखो).
 *
 * By design there should only be *one* "controlling" process. In practice
 * multiple ग_लिखो accesses gives unpredictable result. Understood by "write"
 * to /proc gives result code thats should be पढ़ो be the "writer".
 * For practical use this should be no problem.
 *
 * Note when adding devices to a specअगरic CPU there good idea to also assign
 * /proc/irq/XX/smp_affinity so TX-पूर्णांकerrupts माला_लो bound to the same CPU.
 * --ro
 *
 * Fix refcount off by one अगर first packet fails, potential null deref,
 * memleak 030710- KJP
 *
 * First "ranges" functionality क्रम ipv6 030726 --ro
 *
 * Included flow support. 030802 ANK.
 *
 * Fixed unaligned access on IA-64 Grant Grundler <grundler@parisc-linux.org>
 *
 * Remove अगर fix from added Harald Welte <laक्रमge@netfilter.org> 040419
 * ia64 compilation fix from  Aron Grअगरfis <aron@hp.com> 040604
 *
 * New xmit() वापस, करो_भाग and misc clean up by Stephen Hemminger
 * <shemminger@osdl.org> 040923
 *
 * Randy Dunlap fixed u64 prपूर्णांकk compiler warning
 *
 * Remove FCS from BW calculation.  Lennert Buytenhek <buytenh@wantstofly.org>
 * New समय handling. Lennert Buytenhek <buytenh@wantstofly.org> 041213
 *
 * Corrections from Nikolai Malykh (nmalykh@bilim.com)
 * Removed unused flags F_SET_SRCMAC & F_SET_SRCIP 041230
 *
 * पूर्णांकerruptible_sleep_on_समयout() replaced Nishanth Aravamudan <nacc@us.ibm.com>
 * 050103
 *
 * MPLS support by Steven Whitehouse <steve@chygwyn.com>
 *
 * 802.1Q/Q-in-Q support by Francesco Fondelli (FF) <francesco.fondelli@gmail.com>
 *
 * Fixed src_mac command to set source mac of packet to value specअगरied in
 * command by Adit Ranaभागe <adit.262@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sys.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/unistd.h>
#समावेश <linux/माला.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/capability.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inet.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/रुको.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/mmzone.h>
#समावेश <net/net_namespace.h>
#समावेश <net/checksum.h>
#समावेश <net/ipv6.h>
#समावेश <net/udp.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/addrconf.h>
#अगर_घोषित CONFIG_XFRM
#समावेश <net/xfrm.h>
#पूर्ण_अगर
#समावेश <net/netns/generic.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/समयx.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/भाग64.h>		/* करो_भाग */

#घोषणा VERSION	"2.75"
#घोषणा IP_NAME_SZ 32
#घोषणा MAX_MPLS_LABELS 16 /* This is the max label stack depth */
#घोषणा MPLS_STACK_BOTTOM htonl(0x00000100)

#घोषणा func_enter() pr_debug("entering %s\n", __func__);

#घोषणा PKT_FLAGS							\
	pf(IPV6)		/* Interface in IPV6 Mode */		\
	pf(IPSRC_RND)		/* IP-Src Ranकरोm  */			\
	pf(IPDST_RND)		/* IP-Dst Ranकरोm  */			\
	pf(TXSIZE_RND)		/* Transmit size is अक्रमom */		\
	pf(UDPSRC_RND)		/* UDP-Src Ranकरोm */			\
	pf(UDPDST_RND)		/* UDP-Dst Ranकरोm */			\
	pf(UDPCSUM)		/* Include UDP checksum */		\
	pf(NO_TIMESTAMP)	/* Don't बारtamp packets (शेष TS) */ \
	pf(MPLS_RND)		/* Ranकरोm MPLS labels */		\
	pf(QUEUE_MAP_RND)	/* queue map Ranकरोm */			\
	pf(QUEUE_MAP_CPU)	/* queue map mirrors smp_processor_id() */ \
	pf(FLOW_SEQ)		/* Sequential flows */			\
	pf(IPSEC)		/* ipsec on क्रम flows */		\
	pf(MACSRC_RND)		/* MAC-Src Ranकरोm */			\
	pf(MACDST_RND)		/* MAC-Dst Ranकरोm */			\
	pf(VID_RND)		/* Ranकरोm VLAN ID */			\
	pf(SVID_RND)		/* Ranकरोm SVLAN ID */			\
	pf(NODE)		/* Node memory alloc*/			\

#घोषणा pf(flag)		flag##_SHIFT,
क्रमागत pkt_flags अणु
	PKT_FLAGS
पूर्ण;
#अघोषित pf

/* Device flag bits */
#घोषणा pf(flag)		अटल स्थिर __u32 F_##flag = (1<<flag##_SHIFT);
PKT_FLAGS
#अघोषित pf

#घोषणा pf(flag)		__stringअगरy(flag),
अटल अक्षर *pkt_flag_names[] = अणु
	PKT_FLAGS
पूर्ण;
#अघोषित pf

#घोषणा NR_PKT_FLAGS		ARRAY_SIZE(pkt_flag_names)

/* Thपढ़ो control flag bits */
#घोषणा T_STOP        (1<<0)	/* Stop run */
#घोषणा T_RUN         (1<<1)	/* Start run */
#घोषणा T_REMDEVALL   (1<<2)	/* Remove all devs */
#घोषणा T_REMDEV      (1<<3)	/* Remove one dev */

/* Xmit modes */
#घोषणा M_START_XMIT		0	/* Default normal TX */
#घोषणा M_NETIF_RECEIVE 	1	/* Inject packets पूर्णांकo stack */
#घोषणा M_QUEUE_XMIT		2	/* Inject packet पूर्णांकo qdisc */

/* If lock -- protects updating of अगर_list */
#घोषणा   अगर_lock(t)           mutex_lock(&(t->अगर_lock));
#घोषणा   अगर_unlock(t)           mutex_unlock(&(t->अगर_lock));

/* Used to help with determining the pkts on receive */
#घोषणा PKTGEN_MAGIC 0xbe9be955
#घोषणा PG_PROC_सूची "pktgen"
#घोषणा PGCTRL	    "pgctrl"

#घोषणा MAX_CFLOWS  65536

#घोषणा VLAN_TAG_SIZE(x) ((x)->vlan_id == 0xffff ? 0 : 4)
#घोषणा SVLAN_TAG_SIZE(x) ((x)->svlan_id == 0xffff ? 0 : 4)

काष्ठा flow_state अणु
	__be32 cur_daddr;
	पूर्णांक count;
#अगर_घोषित CONFIG_XFRM
	काष्ठा xfrm_state *x;
#पूर्ण_अगर
	__u32 flags;
पूर्ण;

/* flow flag bits */
#घोषणा F_INIT   (1<<0)		/* flow has been initialized */

काष्ठा pktgen_dev अणु
	/*
	 * Try to keep frequent/infrequent used vars. separated.
	 */
	काष्ठा proc_dir_entry *entry;	/* proc file */
	काष्ठा pktgen_thपढ़ो *pg_thपढ़ो;/* the owner */
	काष्ठा list_head list;		/* chaining in the thपढ़ो's run-queue */
	काष्ठा rcu_head	 rcu;		/* मुक्तd by RCU */

	पूर्णांक running;		/* अगर false, the test will stop */

	/* If min != max, then we will either करो a linear iteration, or
	 * we will करो a अक्रमom selection from within the range.
	 */
	__u32 flags;
	पूर्णांक xmit_mode;
	पूर्णांक min_pkt_size;
	पूर्णांक max_pkt_size;
	पूर्णांक pkt_overhead;	/* overhead क्रम MPLS, VLANs, IPSEC etc */
	पूर्णांक nfrags;
	पूर्णांक removal_mark;	/* non-zero => the device is marked क्रम
				 * removal by worker thपढ़ो */

	काष्ठा page *page;
	u64 delay;		/* nano-seconds */

	__u64 count;		/* Default No packets to send */
	__u64 sofar;		/* How many pkts we've sent so far */
	__u64 tx_bytes;		/* How many bytes we've transmitted */
	__u64 errors;		/* Errors when trying to transmit, */

	/* runसमय counters relating to clone_skb */

	__u32 clone_count;
	पूर्णांक last_ok;		/* Was last skb sent?
				 * Or a failed transmit of some sort?
				 * This will keep sequence numbers in order
				 */
	kसमय_प्रकार next_tx;
	kसमय_प्रकार started_at;
	kसमय_प्रकार stopped_at;
	u64	idle_acc;	/* nano-seconds */

	__u32 seq_num;

	पूर्णांक clone_skb;		/*
				 * Use multiple SKBs during packet gen.
				 * If this number is greater than 1, then
				 * that many copies of the same packet will be
				 * sent beक्रमe a new packet is allocated.
				 * If you want to send 1024 identical packets
				 * beक्रमe creating a new packet,
				 * set clone_skb to 1024.
				 */

	अक्षर dst_min[IP_NAME_SZ];	/* IP, ie 1.2.3.4 */
	अक्षर dst_max[IP_NAME_SZ];	/* IP, ie 1.2.3.4 */
	अक्षर src_min[IP_NAME_SZ];	/* IP, ie 1.2.3.4 */
	अक्षर src_max[IP_NAME_SZ];	/* IP, ie 1.2.3.4 */

	काष्ठा in6_addr in6_saddr;
	काष्ठा in6_addr in6_daddr;
	काष्ठा in6_addr cur_in6_daddr;
	काष्ठा in6_addr cur_in6_saddr;
	/* For ranges */
	काष्ठा in6_addr min_in6_daddr;
	काष्ठा in6_addr max_in6_daddr;
	काष्ठा in6_addr min_in6_saddr;
	काष्ठा in6_addr max_in6_saddr;

	/* If we're करोing ranges, अक्रमom or incremental, then this
	 * defines the min/max क्रम those ranges.
	 */
	__be32 saddr_min;	/* inclusive, source IP address */
	__be32 saddr_max;	/* exclusive, source IP address */
	__be32 daddr_min;	/* inclusive, dest IP address */
	__be32 daddr_max;	/* exclusive, dest IP address */

	__u16 udp_src_min;	/* inclusive, source UDP port */
	__u16 udp_src_max;	/* exclusive, source UDP port */
	__u16 udp_dst_min;	/* inclusive, dest UDP port */
	__u16 udp_dst_max;	/* exclusive, dest UDP port */

	/* DSCP + ECN */
	__u8 tos;            /* six MSB of (क्रमmer) IPv4 TOS
				are क्रम dscp codepoपूर्णांक */
	__u8 traffic_class;  /* ditto क्रम the (क्रमmer) Traffic Class in IPv6
				(see RFC 3260, sec. 4) */

	/* MPLS */
	अचिन्हित पूर्णांक nr_labels;	/* Depth of stack, 0 = no MPLS */
	__be32 labels[MAX_MPLS_LABELS];

	/* VLAN/SVLAN (802.1Q/Q-in-Q) */
	__u8  vlan_p;
	__u8  vlan_cfi;
	__u16 vlan_id;  /* 0xffff means no vlan tag */

	__u8  svlan_p;
	__u8  svlan_cfi;
	__u16 svlan_id; /* 0xffff means no svlan tag */

	__u32 src_mac_count;	/* How many MACs to iterate through */
	__u32 dst_mac_count;	/* How many MACs to iterate through */

	अचिन्हित अक्षर dst_mac[ETH_ALEN];
	अचिन्हित अक्षर src_mac[ETH_ALEN];

	__u32 cur_dst_mac_offset;
	__u32 cur_src_mac_offset;
	__be32 cur_saddr;
	__be32 cur_daddr;
	__u16 ip_id;
	__u16 cur_udp_dst;
	__u16 cur_udp_src;
	__u16 cur_queue_map;
	__u32 cur_pkt_size;
	__u32 last_pkt_size;

	__u8 hh[14];
	/* = अणु
	   0x00, 0x80, 0xC8, 0x79, 0xB3, 0xCB,

	   We fill in SRC address later
	   0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	   0x08, 0x00
	   पूर्ण;
	 */
	__u16 pad;		/* pad out the hh काष्ठा to an even 16 bytes */

	काष्ठा sk_buff *skb;	/* skb we are to transmit next, used क्रम when we
				 * are transmitting the same one multiple बार
				 */
	काष्ठा net_device *odev; /* The out-going device.
				  * Note that the device should have it's
				  * pg_info poपूर्णांकer poपूर्णांकing back to this
				  * device.
				  * Set when the user specअगरies the out-going
				  * device name (not when the inject is
				  * started as it used to करो.)
				  */
	अक्षर odevname[32];
	काष्ठा flow_state *flows;
	अचिन्हित पूर्णांक cflows;	/* Concurrent flows (config) */
	अचिन्हित पूर्णांक lflow;		/* Flow length  (config) */
	अचिन्हित पूर्णांक nflows;	/* accumulated flows (stats) */
	अचिन्हित पूर्णांक curfl;		/* current sequenced flow (state)*/

	u16 queue_map_min;
	u16 queue_map_max;
	__u32 skb_priority;	/* skb priority field */
	अचिन्हित पूर्णांक burst;	/* number of duplicated packets to burst */
	पूर्णांक node;               /* Memory node */

#अगर_घोषित CONFIG_XFRM
	__u8	ipsmode;		/* IPSEC mode (config) */
	__u8	ipsproto;		/* IPSEC type (config) */
	__u32	spi;
	काष्ठा xfrm_dst xdst;
	काष्ठा dst_ops dstops;
#पूर्ण_अगर
	अक्षर result[512];
पूर्ण;

काष्ठा pktgen_hdr अणु
	__be32 pgh_magic;
	__be32 seq_num;
	__be32 tv_sec;
	__be32 tv_usec;
पूर्ण;


अटल अचिन्हित पूर्णांक pg_net_id __पढ़ो_mostly;

काष्ठा pktgen_net अणु
	काष्ठा net		*net;
	काष्ठा proc_dir_entry	*proc_dir;
	काष्ठा list_head	pktgen_thपढ़ोs;
	bool			pktgen_निकासing;
पूर्ण;

काष्ठा pktgen_thपढ़ो अणु
	काष्ठा mutex अगर_lock;		/* क्रम list of devices */
	काष्ठा list_head अगर_list;	/* All device here */
	काष्ठा list_head th_list;
	काष्ठा task_काष्ठा *tsk;
	अक्षर result[512];

	/* Field क्रम thपढ़ो to receive "posted" events terminate,
	   stop अगरs etc. */

	u32 control;
	पूर्णांक cpu;

	रुको_queue_head_t queue;
	काष्ठा completion start_करोne;
	काष्ठा pktgen_net *net;
पूर्ण;

#घोषणा REMOVE 1
#घोषणा FIND   0

अटल स्थिर अक्षर version[] =
	"Packet Generator for packet performance testing. "
	"Version: " VERSION "\n";

अटल पूर्णांक pktgen_हटाओ_device(काष्ठा pktgen_thपढ़ो *t, काष्ठा pktgen_dev *i);
अटल पूर्णांक pktgen_add_device(काष्ठा pktgen_thपढ़ो *t, स्थिर अक्षर *अगरname);
अटल काष्ठा pktgen_dev *pktgen_find_dev(काष्ठा pktgen_thपढ़ो *t,
					  स्थिर अक्षर *अगरname, bool exact);
अटल पूर्णांक pktgen_device_event(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल व्योम pktgen_run_all_thपढ़ोs(काष्ठा pktgen_net *pn);
अटल व्योम pktgen_reset_all_thपढ़ोs(काष्ठा pktgen_net *pn);
अटल व्योम pktgen_stop_all_thपढ़ोs_अगरs(काष्ठा pktgen_net *pn);

अटल व्योम pktgen_stop(काष्ठा pktgen_thपढ़ो *t);
अटल व्योम pktgen_clear_counters(काष्ठा pktgen_dev *pkt_dev);

/* Module parameters, शेषs. */
अटल पूर्णांक pg_count_d __पढ़ो_mostly = 1000;
अटल पूर्णांक pg_delay_d __पढ़ो_mostly;
अटल पूर्णांक pg_clone_skb_d  __पढ़ो_mostly;
अटल पूर्णांक debug  __पढ़ो_mostly;

अटल DEFINE_MUTEX(pktgen_thपढ़ो_lock);

अटल काष्ठा notअगरier_block pktgen_notअगरier_block = अणु
	.notअगरier_call = pktgen_device_event,
पूर्ण;

/*
 * /proc handling functions
 *
 */

अटल पूर्णांक pgctrl_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	seq_माला_दो(seq, version);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार pgctrl_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर data[128];
	काष्ठा pktgen_net *pn = net_generic(current->nsproxy->net_ns, pg_net_id);

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (count == 0)
		वापस -EINVAL;

	अगर (count > माप(data))
		count = माप(data);

	अगर (copy_from_user(data, buf, count))
		वापस -EFAULT;

	data[count - 1] = 0;	/* Strip trailing '\n' and terminate string */

	अगर (!म_भेद(data, "stop"))
		pktgen_stop_all_thपढ़ोs_अगरs(pn);

	अन्यथा अगर (!म_भेद(data, "start"))
		pktgen_run_all_thपढ़ोs(pn);

	अन्यथा अगर (!म_भेद(data, "reset"))
		pktgen_reset_all_thपढ़ोs(pn);

	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल पूर्णांक pgctrl_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, pgctrl_show, PDE_DATA(inode));
पूर्ण

अटल स्थिर काष्ठा proc_ops pktgen_proc_ops = अणु
	.proc_खोलो	= pgctrl_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= pgctrl_ग_लिखो,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक pktgen_अगर_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	स्थिर काष्ठा pktgen_dev *pkt_dev = seq->निजी;
	kसमय_प्रकार stopped;
	अचिन्हित पूर्णांक i;
	u64 idle;

	seq_म_लिखो(seq,
		   "Params: count %llu  min_pkt_size: %u  max_pkt_size: %u\n",
		   (अचिन्हित दीर्घ दीर्घ)pkt_dev->count, pkt_dev->min_pkt_size,
		   pkt_dev->max_pkt_size);

	seq_म_लिखो(seq,
		   "     frags: %d  delay: %llu  clone_skb: %d  ifname: %s\n",
		   pkt_dev->nfrags, (अचिन्हित दीर्घ दीर्घ) pkt_dev->delay,
		   pkt_dev->clone_skb, pkt_dev->odevname);

	seq_म_लिखो(seq, "     flows: %u flowlen: %u\n", pkt_dev->cflows,
		   pkt_dev->lflow);

	seq_म_लिखो(seq,
		   "     queue_map_min: %u  queue_map_max: %u\n",
		   pkt_dev->queue_map_min,
		   pkt_dev->queue_map_max);

	अगर (pkt_dev->skb_priority)
		seq_म_लिखो(seq, "     skb_priority: %u\n",
			   pkt_dev->skb_priority);

	अगर (pkt_dev->flags & F_IPV6) अणु
		seq_म_लिखो(seq,
			   "     saddr: %pI6c  min_saddr: %pI6c  max_saddr: %pI6c\n"
			   "     daddr: %pI6c  min_daddr: %pI6c  max_daddr: %pI6c\n",
			   &pkt_dev->in6_saddr,
			   &pkt_dev->min_in6_saddr, &pkt_dev->max_in6_saddr,
			   &pkt_dev->in6_daddr,
			   &pkt_dev->min_in6_daddr, &pkt_dev->max_in6_daddr);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(seq,
			   "     dst_min: %s  dst_max: %s\n",
			   pkt_dev->dst_min, pkt_dev->dst_max);
		seq_म_लिखो(seq,
			   "     src_min: %s  src_max: %s\n",
			   pkt_dev->src_min, pkt_dev->src_max);
	पूर्ण

	seq_माला_दो(seq, "     src_mac: ");

	seq_म_लिखो(seq, "%pM ",
		   is_zero_ether_addr(pkt_dev->src_mac) ?
			     pkt_dev->odev->dev_addr : pkt_dev->src_mac);

	seq_माला_दो(seq, "dst_mac: ");
	seq_म_लिखो(seq, "%pM\n", pkt_dev->dst_mac);

	seq_म_लिखो(seq,
		   "     udp_src_min: %d  udp_src_max: %d"
		   "  udp_dst_min: %d  udp_dst_max: %d\n",
		   pkt_dev->udp_src_min, pkt_dev->udp_src_max,
		   pkt_dev->udp_dst_min, pkt_dev->udp_dst_max);

	seq_म_लिखो(seq,
		   "     src_mac_count: %d  dst_mac_count: %d\n",
		   pkt_dev->src_mac_count, pkt_dev->dst_mac_count);

	अगर (pkt_dev->nr_labels) अणु
		seq_माला_दो(seq, "     mpls: ");
		क्रम (i = 0; i < pkt_dev->nr_labels; i++)
			seq_म_लिखो(seq, "%08x%s", ntohl(pkt_dev->labels[i]),
				   i == pkt_dev->nr_labels-1 ? "\n" : ", ");
	पूर्ण

	अगर (pkt_dev->vlan_id != 0xffff)
		seq_म_लिखो(seq, "     vlan_id: %u  vlan_p: %u  vlan_cfi: %u\n",
			   pkt_dev->vlan_id, pkt_dev->vlan_p,
			   pkt_dev->vlan_cfi);

	अगर (pkt_dev->svlan_id != 0xffff)
		seq_म_लिखो(seq, "     svlan_id: %u  vlan_p: %u  vlan_cfi: %u\n",
			   pkt_dev->svlan_id, pkt_dev->svlan_p,
			   pkt_dev->svlan_cfi);

	अगर (pkt_dev->tos)
		seq_म_लिखो(seq, "     tos: 0x%02x\n", pkt_dev->tos);

	अगर (pkt_dev->traffic_class)
		seq_म_लिखो(seq, "     traffic_class: 0x%02x\n", pkt_dev->traffic_class);

	अगर (pkt_dev->burst > 1)
		seq_म_लिखो(seq, "     burst: %d\n", pkt_dev->burst);

	अगर (pkt_dev->node >= 0)
		seq_म_लिखो(seq, "     node: %d\n", pkt_dev->node);

	अगर (pkt_dev->xmit_mode == M_NETIF_RECEIVE)
		seq_माला_दो(seq, "     xmit_mode: netif_receive\n");
	अन्यथा अगर (pkt_dev->xmit_mode == M_QUEUE_XMIT)
		seq_माला_दो(seq, "     xmit_mode: xmit_queue\n");

	seq_माला_दो(seq, "     Flags: ");

	क्रम (i = 0; i < NR_PKT_FLAGS; i++) अणु
		अगर (i == F_FLOW_SEQ)
			अगर (!pkt_dev->cflows)
				जारी;

		अगर (pkt_dev->flags & (1 << i))
			seq_म_लिखो(seq, "%s  ", pkt_flag_names[i]);
		अन्यथा अगर (i == F_FLOW_SEQ)
			seq_माला_दो(seq, "FLOW_RND  ");

#अगर_घोषित CONFIG_XFRM
		अगर (i == F_IPSEC && pkt_dev->spi)
			seq_म_लिखो(seq, "spi:%u", pkt_dev->spi);
#पूर्ण_अगर
	पूर्ण

	seq_माला_दो(seq, "\n");

	/* not really stopped, more like last-running-at */
	stopped = pkt_dev->running ? kसमय_get() : pkt_dev->stopped_at;
	idle = pkt_dev->idle_acc;
	करो_भाग(idle, NSEC_PER_USEC);

	seq_म_लिखो(seq,
		   "Current:\n     pkts-sofar: %llu  errors: %llu\n",
		   (अचिन्हित दीर्घ दीर्घ)pkt_dev->sofar,
		   (अचिन्हित दीर्घ दीर्घ)pkt_dev->errors);

	seq_म_लिखो(seq,
		   "     started: %lluus  stopped: %lluus idle: %lluus\n",
		   (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_us(pkt_dev->started_at),
		   (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_us(stopped),
		   (अचिन्हित दीर्घ दीर्घ) idle);

	seq_म_लिखो(seq,
		   "     seq_num: %d  cur_dst_mac_offset: %d  cur_src_mac_offset: %d\n",
		   pkt_dev->seq_num, pkt_dev->cur_dst_mac_offset,
		   pkt_dev->cur_src_mac_offset);

	अगर (pkt_dev->flags & F_IPV6) अणु
		seq_म_लिखो(seq, "     cur_saddr: %pI6c  cur_daddr: %pI6c\n",
				&pkt_dev->cur_in6_saddr,
				&pkt_dev->cur_in6_daddr);
	पूर्ण अन्यथा
		seq_म_लिखो(seq, "     cur_saddr: %pI4  cur_daddr: %pI4\n",
			   &pkt_dev->cur_saddr, &pkt_dev->cur_daddr);

	seq_म_लिखो(seq, "     cur_udp_dst: %d  cur_udp_src: %d\n",
		   pkt_dev->cur_udp_dst, pkt_dev->cur_udp_src);

	seq_म_लिखो(seq, "     cur_queue_map: %u\n", pkt_dev->cur_queue_map);

	seq_म_लिखो(seq, "     flows: %u\n", pkt_dev->nflows);

	अगर (pkt_dev->result[0])
		seq_म_लिखो(seq, "Result: %s\n", pkt_dev->result);
	अन्यथा
		seq_माला_दो(seq, "Result: Idle\n");

	वापस 0;
पूर्ण


अटल पूर्णांक hex32_arg(स्थिर अक्षर __user *user_buffer, अचिन्हित दीर्घ maxlen,
		     __u32 *num)
अणु
	पूर्णांक i = 0;
	*num = 0;

	क्रम (; i < maxlen; i++) अणु
		पूर्णांक value;
		अक्षर c;
		*num <<= 4;
		अगर (get_user(c, &user_buffer[i]))
			वापस -EFAULT;
		value = hex_to_bin(c);
		अगर (value >= 0)
			*num |= value;
		अन्यथा
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक count_trail_अक्षरs(स्थिर अक्षर __user * user_buffer,
			     अचिन्हित पूर्णांक maxlen)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < maxlen; i++) अणु
		अक्षर c;
		अगर (get_user(c, &user_buffer[i]))
			वापस -EFAULT;
		चयन (c) अणु
		हाल '\"':
		हाल '\n':
		हाल '\r':
		हाल '\t':
		हाल ' ':
		हाल '=':
			अवरोध;
		शेष:
			जाओ करोne;
		पूर्ण
	पूर्ण
करोne:
	वापस i;
पूर्ण

अटल दीर्घ num_arg(स्थिर अक्षर __user *user_buffer, अचिन्हित दीर्घ maxlen,
				अचिन्हित दीर्घ *num)
अणु
	पूर्णांक i;
	*num = 0;

	क्रम (i = 0; i < maxlen; i++) अणु
		अक्षर c;
		अगर (get_user(c, &user_buffer[i]))
			वापस -EFAULT;
		अगर ((c >= '0') && (c <= '9')) अणु
			*num *= 10;
			*num += c - '0';
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक strn_len(स्थिर अक्षर __user * user_buffer, अचिन्हित पूर्णांक maxlen)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < maxlen; i++) अणु
		अक्षर c;
		अगर (get_user(c, &user_buffer[i]))
			वापस -EFAULT;
		चयन (c) अणु
		हाल '\"':
		हाल '\n':
		हाल '\r':
		हाल '\t':
		हाल ' ':
			जाओ करोne_str;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
करोne_str:
	वापस i;
पूर्ण

अटल sमाप_प्रकार get_labels(स्थिर अक्षर __user *buffer, काष्ठा pktgen_dev *pkt_dev)
अणु
	अचिन्हित पूर्णांक n = 0;
	अक्षर c;
	sमाप_प्रकार i = 0;
	पूर्णांक len;

	pkt_dev->nr_labels = 0;
	करो अणु
		__u32 पंचांगp;
		len = hex32_arg(&buffer[i], 8, &पंचांगp);
		अगर (len <= 0)
			वापस len;
		pkt_dev->labels[n] = htonl(पंचांगp);
		अगर (pkt_dev->labels[n] & MPLS_STACK_BOTTOM)
			pkt_dev->flags |= F_MPLS_RND;
		i += len;
		अगर (get_user(c, &buffer[i]))
			वापस -EFAULT;
		i++;
		n++;
		अगर (n >= MAX_MPLS_LABELS)
			वापस -E2BIG;
	पूर्ण जबतक (c == ',');

	pkt_dev->nr_labels = n;
	वापस i;
पूर्ण

अटल __u32 pktgen_पढ़ो_flag(स्थिर अक्षर *f, bool *disable)
अणु
	__u32 i;

	अगर (f[0] == '!') अणु
		*disable = true;
		f++;
	पूर्ण

	क्रम (i = 0; i < NR_PKT_FLAGS; i++) अणु
		अगर (!IS_ENABLED(CONFIG_XFRM) && i == IPSEC_SHIFT)
			जारी;

		/* allow only disabling ipv6 flag */
		अगर (!*disable && i == IPV6_SHIFT)
			जारी;

		अगर (म_भेद(f, pkt_flag_names[i]) == 0)
			वापस 1 << i;
	पूर्ण

	अगर (म_भेद(f, "FLOW_RND") == 0) अणु
		*disable = !*disable;
		वापस F_FLOW_SEQ;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pktgen_अगर_ग_लिखो(काष्ठा file *file,
			       स्थिर अक्षर __user * user_buffer, माप_प्रकार count,
			       loff_t * offset)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा pktgen_dev *pkt_dev = seq->निजी;
	पूर्णांक i, max, len;
	अक्षर name[16], valstr[32];
	अचिन्हित दीर्घ value = 0;
	अक्षर *pg_result = शून्य;
	पूर्णांक पंचांगp = 0;
	अक्षर buf[128];

	pg_result = &(pkt_dev->result[0]);

	अगर (count < 1) अणु
		pr_warn("wrong command format\n");
		वापस -EINVAL;
	पूर्ण

	max = count;
	पंचांगp = count_trail_अक्षरs(user_buffer, max);
	अगर (पंचांगp < 0) अणु
		pr_warn("illegal format\n");
		वापस पंचांगp;
	पूर्ण
	i = पंचांगp;

	/* Read variable name */

	len = strn_len(&user_buffer[i], माप(name) - 1);
	अगर (len < 0)
		वापस len;

	स_रखो(name, 0, माप(name));
	अगर (copy_from_user(name, &user_buffer[i], len))
		वापस -EFAULT;
	i += len;

	max = count - i;
	len = count_trail_अक्षरs(&user_buffer[i], max);
	अगर (len < 0)
		वापस len;

	i += len;

	अगर (debug) अणु
		माप_प्रकार copy = min_t(माप_प्रकार, count + 1, 1024);
		अक्षर *tp = strndup_user(user_buffer, copy);

		अगर (IS_ERR(tp))
			वापस PTR_ERR(tp);

		pr_debug("%s,%zu  buffer -:%s:-\n", name, count, tp);
		kमुक्त(tp);
	पूर्ण

	अगर (!म_भेद(name, "min_pkt_size")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value < 14 + 20 + 8)
			value = 14 + 20 + 8;
		अगर (value != pkt_dev->min_pkt_size) अणु
			pkt_dev->min_pkt_size = value;
			pkt_dev->cur_pkt_size = value;
		पूर्ण
		प्र_लिखो(pg_result, "OK: min_pkt_size=%d",
			pkt_dev->min_pkt_size);
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "max_pkt_size")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value < 14 + 20 + 8)
			value = 14 + 20 + 8;
		अगर (value != pkt_dev->max_pkt_size) अणु
			pkt_dev->max_pkt_size = value;
			pkt_dev->cur_pkt_size = value;
		पूर्ण
		प्र_लिखो(pg_result, "OK: max_pkt_size=%d",
			pkt_dev->max_pkt_size);
		वापस count;
	पूर्ण

	/* Shortcut क्रम min = max */

	अगर (!म_भेद(name, "pkt_size")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value < 14 + 20 + 8)
			value = 14 + 20 + 8;
		अगर (value != pkt_dev->min_pkt_size) अणु
			pkt_dev->min_pkt_size = value;
			pkt_dev->max_pkt_size = value;
			pkt_dev->cur_pkt_size = value;
		पूर्ण
		प्र_लिखो(pg_result, "OK: pkt_size=%d", pkt_dev->min_pkt_size);
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "debug")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		debug = value;
		प्र_लिखो(pg_result, "OK: debug=%u", debug);
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "frags")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		pkt_dev->nfrags = value;
		प्र_लिखो(pg_result, "OK: frags=%d", pkt_dev->nfrags);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "delay")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value == 0x7FFFFFFF)
			pkt_dev->delay = ULदीर्घ_उच्च;
		अन्यथा
			pkt_dev->delay = (u64)value;

		प्र_लिखो(pg_result, "OK: delay=%llu",
			(अचिन्हित दीर्घ दीर्घ) pkt_dev->delay);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "rate")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (!value)
			वापस len;
		pkt_dev->delay = pkt_dev->min_pkt_size*8*NSEC_PER_USEC/value;
		अगर (debug)
			pr_info("Delay set at: %llu ns\n", pkt_dev->delay);

		प्र_लिखो(pg_result, "OK: rate=%lu", value);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "ratep")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (!value)
			वापस len;
		pkt_dev->delay = NSEC_PER_SEC/value;
		अगर (debug)
			pr_info("Delay set at: %llu ns\n", pkt_dev->delay);

		प्र_लिखो(pg_result, "OK: rate=%lu", value);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "udp_src_min")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value != pkt_dev->udp_src_min) अणु
			pkt_dev->udp_src_min = value;
			pkt_dev->cur_udp_src = value;
		पूर्ण
		प्र_लिखो(pg_result, "OK: udp_src_min=%u", pkt_dev->udp_src_min);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "udp_dst_min")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value != pkt_dev->udp_dst_min) अणु
			pkt_dev->udp_dst_min = value;
			pkt_dev->cur_udp_dst = value;
		पूर्ण
		प्र_लिखो(pg_result, "OK: udp_dst_min=%u", pkt_dev->udp_dst_min);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "udp_src_max")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value != pkt_dev->udp_src_max) अणु
			pkt_dev->udp_src_max = value;
			pkt_dev->cur_udp_src = value;
		पूर्ण
		प्र_लिखो(pg_result, "OK: udp_src_max=%u", pkt_dev->udp_src_max);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "udp_dst_max")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value != pkt_dev->udp_dst_max) अणु
			pkt_dev->udp_dst_max = value;
			pkt_dev->cur_udp_dst = value;
		पूर्ण
		प्र_लिखो(pg_result, "OK: udp_dst_max=%u", pkt_dev->udp_dst_max);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "clone_skb")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;
		अगर ((value > 0) &&
		    ((pkt_dev->xmit_mode == M_NETIF_RECEIVE) ||
		     !(pkt_dev->odev->priv_flags & IFF_TX_SKB_SHARING)))
			वापस -ENOTSUPP;
		i += len;
		pkt_dev->clone_skb = value;

		प्र_लिखो(pg_result, "OK: clone_skb=%d", pkt_dev->clone_skb);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "count")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		pkt_dev->count = value;
		प्र_लिखो(pg_result, "OK: count=%llu",
			(अचिन्हित दीर्घ दीर्घ)pkt_dev->count);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "src_mac_count")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (pkt_dev->src_mac_count != value) अणु
			pkt_dev->src_mac_count = value;
			pkt_dev->cur_src_mac_offset = 0;
		पूर्ण
		प्र_लिखो(pg_result, "OK: src_mac_count=%d",
			pkt_dev->src_mac_count);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "dst_mac_count")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (pkt_dev->dst_mac_count != value) अणु
			pkt_dev->dst_mac_count = value;
			pkt_dev->cur_dst_mac_offset = 0;
		पूर्ण
		प्र_लिखो(pg_result, "OK: dst_mac_count=%d",
			pkt_dev->dst_mac_count);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "burst")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर ((value > 1) &&
		    ((pkt_dev->xmit_mode == M_QUEUE_XMIT) ||
		     ((pkt_dev->xmit_mode == M_START_XMIT) &&
		     (!(pkt_dev->odev->priv_flags & IFF_TX_SKB_SHARING)))))
			वापस -ENOTSUPP;
		pkt_dev->burst = value < 1 ? 1 : value;
		प्र_लिखो(pg_result, "OK: burst=%u", pkt_dev->burst);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "node")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;

		अगर (node_possible(value)) अणु
			pkt_dev->node = value;
			प्र_लिखो(pg_result, "OK: node=%d", pkt_dev->node);
			अगर (pkt_dev->page) अणु
				put_page(pkt_dev->page);
				pkt_dev->page = शून्य;
			पूर्ण
		पूर्ण
		अन्यथा
			प्र_लिखो(pg_result, "ERROR: node not possible");
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "xmit_mode")) अणु
		अक्षर f[32];

		स_रखो(f, 0, 32);
		len = strn_len(&user_buffer[i], माप(f) - 1);
		अगर (len < 0)
			वापस len;

		अगर (copy_from_user(f, &user_buffer[i], len))
			वापस -EFAULT;
		i += len;

		अगर (म_भेद(f, "start_xmit") == 0) अणु
			pkt_dev->xmit_mode = M_START_XMIT;
		पूर्ण अन्यथा अगर (म_भेद(f, "netif_receive") == 0) अणु
			/* clone_skb set earlier, not supported in this mode */
			अगर (pkt_dev->clone_skb > 0)
				वापस -ENOTSUPP;

			pkt_dev->xmit_mode = M_NETIF_RECEIVE;

			/* make sure new packet is allocated every समय
			 * pktgen_xmit() is called
			 */
			pkt_dev->last_ok = 1;

			/* override clone_skb अगर user passed शेष value
			 * at module loading समय
			 */
			pkt_dev->clone_skb = 0;
		पूर्ण अन्यथा अगर (म_भेद(f, "queue_xmit") == 0) अणु
			pkt_dev->xmit_mode = M_QUEUE_XMIT;
			pkt_dev->last_ok = 1;
		पूर्ण अन्यथा अणु
			प्र_लिखो(pg_result,
				"xmit_mode -:%s:- unknown\nAvailable modes: %s",
				f, "start_xmit, netif_receive\n");
			वापस count;
		पूर्ण
		प्र_लिखो(pg_result, "OK: xmit_mode=%s", f);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "flag")) अणु
		__u32 flag;
		अक्षर f[32];
		bool disable = false;

		स_रखो(f, 0, 32);
		len = strn_len(&user_buffer[i], माप(f) - 1);
		अगर (len < 0)
			वापस len;

		अगर (copy_from_user(f, &user_buffer[i], len))
			वापस -EFAULT;
		i += len;

		flag = pktgen_पढ़ो_flag(f, &disable);

		अगर (flag) अणु
			अगर (disable)
				pkt_dev->flags &= ~flag;
			अन्यथा
				pkt_dev->flags |= flag;
		पूर्ण अन्यथा अणु
			प्र_लिखो(pg_result,
				"Flag -:%s:- unknown\nAvailable flags, (prepend ! to un-set flag):\n%s",
				f,
				"IPSRC_RND, IPDST_RND, UDPSRC_RND, UDPDST_RND, "
				"MACSRC_RND, MACDST_RND, TXSIZE_RND, IPV6, "
				"MPLS_RND, VID_RND, SVID_RND, FLOW_SEQ, "
				"QUEUE_MAP_RND, QUEUE_MAP_CPU, UDPCSUM, "
				"NO_TIMESTAMP, "
#अगर_घोषित CONFIG_XFRM
				"IPSEC, "
#पूर्ण_अगर
				"NODE_ALLOC\n");
			वापस count;
		पूर्ण
		प्र_लिखो(pg_result, "OK: flags=0x%x", pkt_dev->flags);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "dst_min") || !म_भेद(name, "dst")) अणु
		len = strn_len(&user_buffer[i], माप(pkt_dev->dst_min) - 1);
		अगर (len < 0)
			वापस len;

		अगर (copy_from_user(buf, &user_buffer[i], len))
			वापस -EFAULT;
		buf[len] = 0;
		अगर (म_भेद(buf, pkt_dev->dst_min) != 0) अणु
			स_रखो(pkt_dev->dst_min, 0, माप(pkt_dev->dst_min));
			म_नकल(pkt_dev->dst_min, buf);
			pkt_dev->daddr_min = in_aton(pkt_dev->dst_min);
			pkt_dev->cur_daddr = pkt_dev->daddr_min;
		पूर्ण
		अगर (debug)
			pr_debug("dst_min set to: %s\n", pkt_dev->dst_min);
		i += len;
		प्र_लिखो(pg_result, "OK: dst_min=%s", pkt_dev->dst_min);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "dst_max")) अणु
		len = strn_len(&user_buffer[i], माप(pkt_dev->dst_max) - 1);
		अगर (len < 0)
			वापस len;

		अगर (copy_from_user(buf, &user_buffer[i], len))
			वापस -EFAULT;
		buf[len] = 0;
		अगर (म_भेद(buf, pkt_dev->dst_max) != 0) अणु
			स_रखो(pkt_dev->dst_max, 0, माप(pkt_dev->dst_max));
			म_नकल(pkt_dev->dst_max, buf);
			pkt_dev->daddr_max = in_aton(pkt_dev->dst_max);
			pkt_dev->cur_daddr = pkt_dev->daddr_max;
		पूर्ण
		अगर (debug)
			pr_debug("dst_max set to: %s\n", pkt_dev->dst_max);
		i += len;
		प्र_लिखो(pg_result, "OK: dst_max=%s", pkt_dev->dst_max);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "dst6")) अणु
		len = strn_len(&user_buffer[i], माप(buf) - 1);
		अगर (len < 0)
			वापस len;

		pkt_dev->flags |= F_IPV6;

		अगर (copy_from_user(buf, &user_buffer[i], len))
			वापस -EFAULT;
		buf[len] = 0;

		in6_pton(buf, -1, pkt_dev->in6_daddr.s6_addr, -1, शून्य);
		snम_लिखो(buf, माप(buf), "%pI6c", &pkt_dev->in6_daddr);

		pkt_dev->cur_in6_daddr = pkt_dev->in6_daddr;

		अगर (debug)
			pr_debug("dst6 set to: %s\n", buf);

		i += len;
		प्र_लिखो(pg_result, "OK: dst6=%s", buf);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "dst6_min")) अणु
		len = strn_len(&user_buffer[i], माप(buf) - 1);
		अगर (len < 0)
			वापस len;

		pkt_dev->flags |= F_IPV6;

		अगर (copy_from_user(buf, &user_buffer[i], len))
			वापस -EFAULT;
		buf[len] = 0;

		in6_pton(buf, -1, pkt_dev->min_in6_daddr.s6_addr, -1, शून्य);
		snम_लिखो(buf, माप(buf), "%pI6c", &pkt_dev->min_in6_daddr);

		pkt_dev->cur_in6_daddr = pkt_dev->min_in6_daddr;
		अगर (debug)
			pr_debug("dst6_min set to: %s\n", buf);

		i += len;
		प्र_लिखो(pg_result, "OK: dst6_min=%s", buf);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "dst6_max")) अणु
		len = strn_len(&user_buffer[i], माप(buf) - 1);
		अगर (len < 0)
			वापस len;

		pkt_dev->flags |= F_IPV6;

		अगर (copy_from_user(buf, &user_buffer[i], len))
			वापस -EFAULT;
		buf[len] = 0;

		in6_pton(buf, -1, pkt_dev->max_in6_daddr.s6_addr, -1, शून्य);
		snम_लिखो(buf, माप(buf), "%pI6c", &pkt_dev->max_in6_daddr);

		अगर (debug)
			pr_debug("dst6_max set to: %s\n", buf);

		i += len;
		प्र_लिखो(pg_result, "OK: dst6_max=%s", buf);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "src6")) अणु
		len = strn_len(&user_buffer[i], माप(buf) - 1);
		अगर (len < 0)
			वापस len;

		pkt_dev->flags |= F_IPV6;

		अगर (copy_from_user(buf, &user_buffer[i], len))
			वापस -EFAULT;
		buf[len] = 0;

		in6_pton(buf, -1, pkt_dev->in6_saddr.s6_addr, -1, शून्य);
		snम_लिखो(buf, माप(buf), "%pI6c", &pkt_dev->in6_saddr);

		pkt_dev->cur_in6_saddr = pkt_dev->in6_saddr;

		अगर (debug)
			pr_debug("src6 set to: %s\n", buf);

		i += len;
		प्र_लिखो(pg_result, "OK: src6=%s", buf);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "src_min")) अणु
		len = strn_len(&user_buffer[i], माप(pkt_dev->src_min) - 1);
		अगर (len < 0)
			वापस len;

		अगर (copy_from_user(buf, &user_buffer[i], len))
			वापस -EFAULT;
		buf[len] = 0;
		अगर (म_भेद(buf, pkt_dev->src_min) != 0) अणु
			स_रखो(pkt_dev->src_min, 0, माप(pkt_dev->src_min));
			म_नकल(pkt_dev->src_min, buf);
			pkt_dev->saddr_min = in_aton(pkt_dev->src_min);
			pkt_dev->cur_saddr = pkt_dev->saddr_min;
		पूर्ण
		अगर (debug)
			pr_debug("src_min set to: %s\n", pkt_dev->src_min);
		i += len;
		प्र_लिखो(pg_result, "OK: src_min=%s", pkt_dev->src_min);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "src_max")) अणु
		len = strn_len(&user_buffer[i], माप(pkt_dev->src_max) - 1);
		अगर (len < 0)
			वापस len;

		अगर (copy_from_user(buf, &user_buffer[i], len))
			वापस -EFAULT;
		buf[len] = 0;
		अगर (म_भेद(buf, pkt_dev->src_max) != 0) अणु
			स_रखो(pkt_dev->src_max, 0, माप(pkt_dev->src_max));
			म_नकल(pkt_dev->src_max, buf);
			pkt_dev->saddr_max = in_aton(pkt_dev->src_max);
			pkt_dev->cur_saddr = pkt_dev->saddr_max;
		पूर्ण
		अगर (debug)
			pr_debug("src_max set to: %s\n", pkt_dev->src_max);
		i += len;
		प्र_लिखो(pg_result, "OK: src_max=%s", pkt_dev->src_max);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "dst_mac")) अणु
		len = strn_len(&user_buffer[i], माप(valstr) - 1);
		अगर (len < 0)
			वापस len;

		स_रखो(valstr, 0, माप(valstr));
		अगर (copy_from_user(valstr, &user_buffer[i], len))
			वापस -EFAULT;

		अगर (!mac_pton(valstr, pkt_dev->dst_mac))
			वापस -EINVAL;
		/* Set up Dest MAC */
		ether_addr_copy(&pkt_dev->hh[0], pkt_dev->dst_mac);

		प्र_लिखो(pg_result, "OK: dstmac %pM", pkt_dev->dst_mac);
		वापस count;
	पूर्ण
	अगर (!म_भेद(name, "src_mac")) अणु
		len = strn_len(&user_buffer[i], माप(valstr) - 1);
		अगर (len < 0)
			वापस len;

		स_रखो(valstr, 0, माप(valstr));
		अगर (copy_from_user(valstr, &user_buffer[i], len))
			वापस -EFAULT;

		अगर (!mac_pton(valstr, pkt_dev->src_mac))
			वापस -EINVAL;
		/* Set up Src MAC */
		ether_addr_copy(&pkt_dev->hh[6], pkt_dev->src_mac);

		प्र_लिखो(pg_result, "OK: srcmac %pM", pkt_dev->src_mac);
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "clear_counters")) अणु
		pktgen_clear_counters(pkt_dev);
		प्र_लिखो(pg_result, "OK: Clearing counters.\n");
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "flows")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value > MAX_CFLOWS)
			value = MAX_CFLOWS;

		pkt_dev->cflows = value;
		प्र_लिखो(pg_result, "OK: flows=%u", pkt_dev->cflows);
		वापस count;
	पूर्ण
#अगर_घोषित CONFIG_XFRM
	अगर (!म_भेद(name, "spi")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		pkt_dev->spi = value;
		प्र_लिखो(pg_result, "OK: spi=%u", pkt_dev->spi);
		वापस count;
	पूर्ण
#पूर्ण_अगर
	अगर (!म_भेद(name, "flowlen")) अणु
		len = num_arg(&user_buffer[i], 10, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		pkt_dev->lflow = value;
		प्र_लिखो(pg_result, "OK: flowlen=%u", pkt_dev->lflow);
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "queue_map_min")) अणु
		len = num_arg(&user_buffer[i], 5, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		pkt_dev->queue_map_min = value;
		प्र_लिखो(pg_result, "OK: queue_map_min=%u", pkt_dev->queue_map_min);
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "queue_map_max")) अणु
		len = num_arg(&user_buffer[i], 5, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		pkt_dev->queue_map_max = value;
		प्र_लिखो(pg_result, "OK: queue_map_max=%u", pkt_dev->queue_map_max);
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "mpls")) अणु
		अचिन्हित पूर्णांक n, cnt;

		len = get_labels(&user_buffer[i], pkt_dev);
		अगर (len < 0)
			वापस len;
		i += len;
		cnt = प्र_लिखो(pg_result, "OK: mpls=");
		क्रम (n = 0; n < pkt_dev->nr_labels; n++)
			cnt += प्र_लिखो(pg_result + cnt,
				       "%08x%s", ntohl(pkt_dev->labels[n]),
				       n == pkt_dev->nr_labels-1 ? "" : ",");

		अगर (pkt_dev->nr_labels && pkt_dev->vlan_id != 0xffff) अणु
			pkt_dev->vlan_id = 0xffff; /* turn off VLAN/SVLAN */
			pkt_dev->svlan_id = 0xffff;

			अगर (debug)
				pr_debug("VLAN/SVLAN auto turned off\n");
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "vlan_id")) अणु
		len = num_arg(&user_buffer[i], 4, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (value <= 4095) अणु
			pkt_dev->vlan_id = value;  /* turn on VLAN */

			अगर (debug)
				pr_debug("VLAN turned on\n");

			अगर (debug && pkt_dev->nr_labels)
				pr_debug("MPLS auto turned off\n");

			pkt_dev->nr_labels = 0;    /* turn off MPLS */
			प्र_लिखो(pg_result, "OK: vlan_id=%u", pkt_dev->vlan_id);
		पूर्ण अन्यथा अणु
			pkt_dev->vlan_id = 0xffff; /* turn off VLAN/SVLAN */
			pkt_dev->svlan_id = 0xffff;

			अगर (debug)
				pr_debug("VLAN/SVLAN turned off\n");
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "vlan_p")) अणु
		len = num_arg(&user_buffer[i], 1, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर ((value <= 7) && (pkt_dev->vlan_id != 0xffff)) अणु
			pkt_dev->vlan_p = value;
			प्र_लिखो(pg_result, "OK: vlan_p=%u", pkt_dev->vlan_p);
		पूर्ण अन्यथा अणु
			प्र_लिखो(pg_result, "ERROR: vlan_p must be 0-7");
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "vlan_cfi")) अणु
		len = num_arg(&user_buffer[i], 1, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर ((value <= 1) && (pkt_dev->vlan_id != 0xffff)) अणु
			pkt_dev->vlan_cfi = value;
			प्र_लिखो(pg_result, "OK: vlan_cfi=%u", pkt_dev->vlan_cfi);
		पूर्ण अन्यथा अणु
			प्र_लिखो(pg_result, "ERROR: vlan_cfi must be 0-1");
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "svlan_id")) अणु
		len = num_arg(&user_buffer[i], 4, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर ((value <= 4095) && ((pkt_dev->vlan_id != 0xffff))) अणु
			pkt_dev->svlan_id = value;  /* turn on SVLAN */

			अगर (debug)
				pr_debug("SVLAN turned on\n");

			अगर (debug && pkt_dev->nr_labels)
				pr_debug("MPLS auto turned off\n");

			pkt_dev->nr_labels = 0;    /* turn off MPLS */
			प्र_लिखो(pg_result, "OK: svlan_id=%u", pkt_dev->svlan_id);
		पूर्ण अन्यथा अणु
			pkt_dev->vlan_id = 0xffff; /* turn off VLAN/SVLAN */
			pkt_dev->svlan_id = 0xffff;

			अगर (debug)
				pr_debug("VLAN/SVLAN turned off\n");
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "svlan_p")) अणु
		len = num_arg(&user_buffer[i], 1, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर ((value <= 7) && (pkt_dev->svlan_id != 0xffff)) अणु
			pkt_dev->svlan_p = value;
			प्र_लिखो(pg_result, "OK: svlan_p=%u", pkt_dev->svlan_p);
		पूर्ण अन्यथा अणु
			प्र_लिखो(pg_result, "ERROR: svlan_p must be 0-7");
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "svlan_cfi")) अणु
		len = num_arg(&user_buffer[i], 1, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर ((value <= 1) && (pkt_dev->svlan_id != 0xffff)) अणु
			pkt_dev->svlan_cfi = value;
			प्र_लिखो(pg_result, "OK: svlan_cfi=%u", pkt_dev->svlan_cfi);
		पूर्ण अन्यथा अणु
			प्र_लिखो(pg_result, "ERROR: svlan_cfi must be 0-1");
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "tos")) अणु
		__u32 पंचांगp_value = 0;
		len = hex32_arg(&user_buffer[i], 2, &पंचांगp_value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (len == 2) अणु
			pkt_dev->tos = पंचांगp_value;
			प्र_लिखो(pg_result, "OK: tos=0x%02x", pkt_dev->tos);
		पूर्ण अन्यथा अणु
			प्र_लिखो(pg_result, "ERROR: tos must be 00-ff");
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "traffic_class")) अणु
		__u32 पंचांगp_value = 0;
		len = hex32_arg(&user_buffer[i], 2, &पंचांगp_value);
		अगर (len < 0)
			वापस len;

		i += len;
		अगर (len == 2) अणु
			pkt_dev->traffic_class = पंचांगp_value;
			प्र_लिखो(pg_result, "OK: traffic_class=0x%02x", pkt_dev->traffic_class);
		पूर्ण अन्यथा अणु
			प्र_लिखो(pg_result, "ERROR: traffic_class must be 00-ff");
		पूर्ण
		वापस count;
	पूर्ण

	अगर (!म_भेद(name, "skb_priority")) अणु
		len = num_arg(&user_buffer[i], 9, &value);
		अगर (len < 0)
			वापस len;

		i += len;
		pkt_dev->skb_priority = value;
		प्र_लिखो(pg_result, "OK: skb_priority=%i",
			pkt_dev->skb_priority);
		वापस count;
	पूर्ण

	प्र_लिखो(pkt_dev->result, "No such parameter \"%s\"", name);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pktgen_अगर_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, pktgen_अगर_show, PDE_DATA(inode));
पूर्ण

अटल स्थिर काष्ठा proc_ops pktgen_अगर_proc_ops = अणु
	.proc_खोलो	= pktgen_अगर_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= pktgen_अगर_ग_लिखो,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक pktgen_thपढ़ो_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा pktgen_thपढ़ो *t = seq->निजी;
	स्थिर काष्ठा pktgen_dev *pkt_dev;

	BUG_ON(!t);

	seq_माला_दो(seq, "Running: ");

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pkt_dev, &t->अगर_list, list)
		अगर (pkt_dev->running)
			seq_म_लिखो(seq, "%s ", pkt_dev->odevname);

	seq_माला_दो(seq, "\nStopped: ");

	list_क्रम_each_entry_rcu(pkt_dev, &t->अगर_list, list)
		अगर (!pkt_dev->running)
			seq_म_लिखो(seq, "%s ", pkt_dev->odevname);

	अगर (t->result[0])
		seq_म_लिखो(seq, "\nResult: %s\n", t->result);
	अन्यथा
		seq_माला_दो(seq, "\nResult: NA\n");

	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pktgen_thपढ़ो_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user * user_buffer,
				   माप_प्रकार count, loff_t * offset)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा pktgen_thपढ़ो *t = seq->निजी;
	पूर्णांक i, max, len, ret;
	अक्षर name[40];
	अक्षर *pg_result;

	अगर (count < 1) अणु
		//      प्र_लिखो(pg_result, "Wrong command format");
		वापस -EINVAL;
	पूर्ण

	max = count;
	len = count_trail_अक्षरs(user_buffer, max);
	अगर (len < 0)
		वापस len;

	i = len;

	/* Read variable name */

	len = strn_len(&user_buffer[i], माप(name) - 1);
	अगर (len < 0)
		वापस len;

	स_रखो(name, 0, माप(name));
	अगर (copy_from_user(name, &user_buffer[i], len))
		वापस -EFAULT;
	i += len;

	max = count - i;
	len = count_trail_अक्षरs(&user_buffer[i], max);
	अगर (len < 0)
		वापस len;

	i += len;

	अगर (debug)
		pr_debug("t=%s, count=%lu\n", name, (अचिन्हित दीर्घ)count);

	अगर (!t) अणु
		pr_err("ERROR: No thread\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	pg_result = &(t->result[0]);

	अगर (!म_भेद(name, "add_device")) अणु
		अक्षर f[32];
		स_रखो(f, 0, 32);
		len = strn_len(&user_buffer[i], माप(f) - 1);
		अगर (len < 0) अणु
			ret = len;
			जाओ out;
		पूर्ण
		अगर (copy_from_user(f, &user_buffer[i], len))
			वापस -EFAULT;
		i += len;
		mutex_lock(&pktgen_thपढ़ो_lock);
		ret = pktgen_add_device(t, f);
		mutex_unlock(&pktgen_thपढ़ो_lock);
		अगर (!ret) अणु
			ret = count;
			प्र_लिखो(pg_result, "OK: add_device=%s", f);
		पूर्ण अन्यथा
			प्र_लिखो(pg_result, "ERROR: can not add device %s", f);
		जाओ out;
	पूर्ण

	अगर (!म_भेद(name, "rem_device_all")) अणु
		mutex_lock(&pktgen_thपढ़ो_lock);
		t->control |= T_REMDEVALL;
		mutex_unlock(&pktgen_thपढ़ो_lock);
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(125));	/* Propagate thपढ़ो->control  */
		ret = count;
		प्र_लिखो(pg_result, "OK: rem_device_all");
		जाओ out;
	पूर्ण

	अगर (!म_भेद(name, "max_before_softirq")) अणु
		प्र_लिखो(pg_result, "OK: Note! max_before_softirq is obsoleted -- Do not use");
		ret = count;
		जाओ out;
	पूर्ण

	ret = -EINVAL;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक pktgen_thपढ़ो_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, pktgen_thपढ़ो_show, PDE_DATA(inode));
पूर्ण

अटल स्थिर काष्ठा proc_ops pktgen_thपढ़ो_proc_ops = अणु
	.proc_खोलो	= pktgen_thपढ़ो_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= pktgen_thपढ़ो_ग_लिखो,
	.proc_release	= single_release,
पूर्ण;

/* Think find or हटाओ क्रम NN */
अटल काष्ठा pktgen_dev *__pktgen_NN_thपढ़ोs(स्थिर काष्ठा pktgen_net *pn,
					      स्थिर अक्षर *अगरname, पूर्णांक हटाओ)
अणु
	काष्ठा pktgen_thपढ़ो *t;
	काष्ठा pktgen_dev *pkt_dev = शून्य;
	bool exact = (हटाओ == FIND);

	list_क्रम_each_entry(t, &pn->pktgen_thपढ़ोs, th_list) अणु
		pkt_dev = pktgen_find_dev(t, अगरname, exact);
		अगर (pkt_dev) अणु
			अगर (हटाओ) अणु
				pkt_dev->removal_mark = 1;
				t->control |= T_REMDEV;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	वापस pkt_dev;
पूर्ण

/*
 * mark a device क्रम removal
 */
अटल व्योम pktgen_mark_device(स्थिर काष्ठा pktgen_net *pn, स्थिर अक्षर *अगरname)
अणु
	काष्ठा pktgen_dev *pkt_dev = शून्य;
	स्थिर पूर्णांक max_tries = 10, msec_per_try = 125;
	पूर्णांक i = 0;

	mutex_lock(&pktgen_thपढ़ो_lock);
	pr_debug("%s: marking %s for removal\n", __func__, अगरname);

	जबतक (1) अणु

		pkt_dev = __pktgen_NN_thपढ़ोs(pn, अगरname, REMOVE);
		अगर (pkt_dev == शून्य)
			अवरोध;	/* success */

		mutex_unlock(&pktgen_thपढ़ो_lock);
		pr_debug("%s: waiting for %s to disappear....\n",
			 __func__, अगरname);
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(msec_per_try));
		mutex_lock(&pktgen_thपढ़ो_lock);

		अगर (++i >= max_tries) अणु
			pr_err("%s: timed out after waiting %d msec for device %s to be removed\n",
			       __func__, msec_per_try * i, अगरname);
			अवरोध;
		पूर्ण

	पूर्ण

	mutex_unlock(&pktgen_thपढ़ो_lock);
पूर्ण

अटल व्योम pktgen_change_name(स्थिर काष्ठा pktgen_net *pn, काष्ठा net_device *dev)
अणु
	काष्ठा pktgen_thपढ़ो *t;

	mutex_lock(&pktgen_thपढ़ो_lock);

	list_क्रम_each_entry(t, &pn->pktgen_thपढ़ोs, th_list) अणु
		काष्ठा pktgen_dev *pkt_dev;

		अगर_lock(t);
		list_क्रम_each_entry(pkt_dev, &t->अगर_list, list) अणु
			अगर (pkt_dev->odev != dev)
				जारी;

			proc_हटाओ(pkt_dev->entry);

			pkt_dev->entry = proc_create_data(dev->name, 0600,
							  pn->proc_dir,
							  &pktgen_अगर_proc_ops,
							  pkt_dev);
			अगर (!pkt_dev->entry)
				pr_err("can't move proc entry for '%s'\n",
				       dev->name);
			अवरोध;
		पूर्ण
		अगर_unlock(t);
	पूर्ण
	mutex_unlock(&pktgen_thपढ़ो_lock);
पूर्ण

अटल पूर्णांक pktgen_device_event(काष्ठा notअगरier_block *unused,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा pktgen_net *pn = net_generic(dev_net(dev), pg_net_id);

	अगर (pn->pktgen_निकासing)
		वापस NOTIFY_DONE;

	/* It is OK that we करो not hold the group lock right now,
	 * as we run under the RTNL lock.
	 */

	चयन (event) अणु
	हाल NETDEV_CHANGENAME:
		pktgen_change_name(pn, dev);
		अवरोध;

	हाल NETDEV_UNREGISTER:
		pktgen_mark_device(pn, dev->name);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा net_device *pktgen_dev_get_by_name(स्थिर काष्ठा pktgen_net *pn,
						 काष्ठा pktgen_dev *pkt_dev,
						 स्थिर अक्षर *अगरname)
अणु
	अक्षर b[IFNAMSIZ+5];
	पूर्णांक i;

	क्रम (i = 0; अगरname[i] != '@'; i++) अणु
		अगर (i == IFNAMSIZ)
			अवरोध;

		b[i] = अगरname[i];
	पूर्ण
	b[i] = 0;

	वापस dev_get_by_name(pn->net, b);
पूर्ण


/* Associate pktgen_dev with a device. */

अटल पूर्णांक pktgen_setup_dev(स्थिर काष्ठा pktgen_net *pn,
			    काष्ठा pktgen_dev *pkt_dev, स्थिर अक्षर *अगरname)
अणु
	काष्ठा net_device *odev;
	पूर्णांक err;

	/* Clean old setups */
	अगर (pkt_dev->odev) अणु
		dev_put(pkt_dev->odev);
		pkt_dev->odev = शून्य;
	पूर्ण

	odev = pktgen_dev_get_by_name(pn, pkt_dev, अगरname);
	अगर (!odev) अणु
		pr_err("no such netdevice: \"%s\"\n", अगरname);
		वापस -ENODEV;
	पूर्ण

	अगर (odev->type != ARPHRD_ETHER && odev->type != ARPHRD_LOOPBACK) अणु
		pr_err("not an ethernet or loopback device: \"%s\"\n", अगरname);
		err = -EINVAL;
	पूर्ण अन्यथा अगर (!netअगर_running(odev)) अणु
		pr_err("device is down: \"%s\"\n", अगरname);
		err = -ENETDOWN;
	पूर्ण अन्यथा अणु
		pkt_dev->odev = odev;
		वापस 0;
	पूर्ण

	dev_put(odev);
	वापस err;
पूर्ण

/* Read pkt_dev from the पूर्णांकerface and set up पूर्णांकernal pktgen_dev
 * काष्ठाure to have the right inक्रमmation to create/send packets
 */
अटल व्योम pktgen_setup_inject(काष्ठा pktgen_dev *pkt_dev)
अणु
	पूर्णांक ntxq;

	अगर (!pkt_dev->odev) अणु
		pr_err("ERROR: pkt_dev->odev == NULL in setup_inject\n");
		प्र_लिखो(pkt_dev->result,
			"ERROR: pkt_dev->odev == NULL in setup_inject.\n");
		वापस;
	पूर्ण

	/* make sure that we करोn't pick a non-existing transmit queue */
	ntxq = pkt_dev->odev->real_num_tx_queues;

	अगर (ntxq <= pkt_dev->queue_map_min) अणु
		pr_warn("WARNING: Requested queue_map_min (zero-based) (%d) exceeds valid range [0 - %d] for (%d) queues on %s, resetting\n",
			pkt_dev->queue_map_min, (ntxq ?: 1) - 1, ntxq,
			pkt_dev->odevname);
		pkt_dev->queue_map_min = (ntxq ?: 1) - 1;
	पूर्ण
	अगर (pkt_dev->queue_map_max >= ntxq) अणु
		pr_warn("WARNING: Requested queue_map_max (zero-based) (%d) exceeds valid range [0 - %d] for (%d) queues on %s, resetting\n",
			pkt_dev->queue_map_max, (ntxq ?: 1) - 1, ntxq,
			pkt_dev->odevname);
		pkt_dev->queue_map_max = (ntxq ?: 1) - 1;
	पूर्ण

	/* Default to the पूर्णांकerface's mac अगर not explicitly set. */

	अगर (is_zero_ether_addr(pkt_dev->src_mac))
		ether_addr_copy(&(pkt_dev->hh[6]), pkt_dev->odev->dev_addr);

	/* Set up Dest MAC */
	ether_addr_copy(&(pkt_dev->hh[0]), pkt_dev->dst_mac);

	अगर (pkt_dev->flags & F_IPV6) अणु
		पूर्णांक i, set = 0, err = 1;
		काष्ठा inet6_dev *idev;

		अगर (pkt_dev->min_pkt_size == 0) अणु
			pkt_dev->min_pkt_size = 14 + माप(काष्ठा ipv6hdr)
						+ माप(काष्ठा udphdr)
						+ माप(काष्ठा pktgen_hdr)
						+ pkt_dev->pkt_overhead;
		पूर्ण

		क्रम (i = 0; i < माप(काष्ठा in6_addr); i++)
			अगर (pkt_dev->cur_in6_saddr.s6_addr[i]) अणु
				set = 1;
				अवरोध;
			पूर्ण

		अगर (!set) अणु

			/*
			 * Use linklevel address अगर unconfigured.
			 *
			 * use ipv6_get_lladdr अगर/when it's get exported
			 */

			rcu_पढ़ो_lock();
			idev = __in6_dev_get(pkt_dev->odev);
			अगर (idev) अणु
				काष्ठा inet6_अगरaddr *अगरp;

				पढ़ो_lock_bh(&idev->lock);
				list_क्रम_each_entry(अगरp, &idev->addr_list, अगर_list) अणु
					अगर ((अगरp->scope & IFA_LINK) &&
					    !(अगरp->flags & IFA_F_TENTATIVE)) अणु
						pkt_dev->cur_in6_saddr = अगरp->addr;
						err = 0;
						अवरोध;
					पूर्ण
				पूर्ण
				पढ़ो_unlock_bh(&idev->lock);
			पूर्ण
			rcu_पढ़ो_unlock();
			अगर (err)
				pr_err("ERROR: IPv6 link address not available\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pkt_dev->min_pkt_size == 0) अणु
			pkt_dev->min_pkt_size = 14 + माप(काष्ठा iphdr)
						+ माप(काष्ठा udphdr)
						+ माप(काष्ठा pktgen_hdr)
						+ pkt_dev->pkt_overhead;
		पूर्ण

		pkt_dev->saddr_min = 0;
		pkt_dev->saddr_max = 0;
		अगर (म_माप(pkt_dev->src_min) == 0) अणु

			काष्ठा in_device *in_dev;

			rcu_पढ़ो_lock();
			in_dev = __in_dev_get_rcu(pkt_dev->odev);
			अगर (in_dev) अणु
				स्थिर काष्ठा in_अगरaddr *अगरa;

				अगरa = rcu_dereference(in_dev->अगरa_list);
				अगर (अगरa) अणु
					pkt_dev->saddr_min = अगरa->अगरa_address;
					pkt_dev->saddr_max = pkt_dev->saddr_min;
				पूर्ण
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण अन्यथा अणु
			pkt_dev->saddr_min = in_aton(pkt_dev->src_min);
			pkt_dev->saddr_max = in_aton(pkt_dev->src_max);
		पूर्ण

		pkt_dev->daddr_min = in_aton(pkt_dev->dst_min);
		pkt_dev->daddr_max = in_aton(pkt_dev->dst_max);
	पूर्ण
	/* Initialize current values. */
	pkt_dev->cur_pkt_size = pkt_dev->min_pkt_size;
	अगर (pkt_dev->min_pkt_size > pkt_dev->max_pkt_size)
		pkt_dev->max_pkt_size = pkt_dev->min_pkt_size;

	pkt_dev->cur_dst_mac_offset = 0;
	pkt_dev->cur_src_mac_offset = 0;
	pkt_dev->cur_saddr = pkt_dev->saddr_min;
	pkt_dev->cur_daddr = pkt_dev->daddr_min;
	pkt_dev->cur_udp_dst = pkt_dev->udp_dst_min;
	pkt_dev->cur_udp_src = pkt_dev->udp_src_min;
	pkt_dev->nflows = 0;
पूर्ण


अटल व्योम spin(काष्ठा pktgen_dev *pkt_dev, kसमय_प्रकार spin_until)
अणु
	kसमय_प्रकार start_समय, end_समय;
	s64 reमुख्यing;
	काष्ठा hrसमयr_sleeper t;

	hrसमयr_init_sleeper_on_stack(&t, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	hrसमयr_set_expires(&t.समयr, spin_until);

	reमुख्यing = kसमय_प्रकारo_ns(hrसमयr_expires_reमुख्यing(&t.समयr));
	अगर (reमुख्यing <= 0)
		जाओ out;

	start_समय = kसमय_get();
	अगर (reमुख्यing < 100000) अणु
		/* क्रम small delays (<100us), just loop until limit is reached */
		करो अणु
			end_समय = kसमय_get();
		पूर्ण जबतक (kसमय_compare(end_समय, spin_until) < 0);
	पूर्ण अन्यथा अणु
		करो अणु
			set_current_state(TASK_INTERRUPTIBLE);
			hrसमयr_sleeper_start_expires(&t, HRTIMER_MODE_ABS);

			अगर (likely(t.task))
				schedule();

			hrसमयr_cancel(&t.समयr);
		पूर्ण जबतक (t.task && pkt_dev->running && !संकेत_pending(current));
		__set_current_state(TASK_RUNNING);
		end_समय = kसमय_get();
	पूर्ण

	pkt_dev->idle_acc += kसमय_प्रकारo_ns(kसमय_sub(end_समय, start_समय));
out:
	pkt_dev->next_tx = kसमय_add_ns(spin_until, pkt_dev->delay);
	destroy_hrसमयr_on_stack(&t.समयr);
पूर्ण

अटल अंतरभूत व्योम set_pkt_overhead(काष्ठा pktgen_dev *pkt_dev)
अणु
	pkt_dev->pkt_overhead = 0;
	pkt_dev->pkt_overhead += pkt_dev->nr_labels*माप(u32);
	pkt_dev->pkt_overhead += VLAN_TAG_SIZE(pkt_dev);
	pkt_dev->pkt_overhead += SVLAN_TAG_SIZE(pkt_dev);
पूर्ण

अटल अंतरभूत पूर्णांक f_seen(स्थिर काष्ठा pktgen_dev *pkt_dev, पूर्णांक flow)
अणु
	वापस !!(pkt_dev->flows[flow].flags & F_INIT);
पूर्ण

अटल अंतरभूत पूर्णांक f_pick(काष्ठा pktgen_dev *pkt_dev)
अणु
	पूर्णांक flow = pkt_dev->curfl;

	अगर (pkt_dev->flags & F_FLOW_SEQ) अणु
		अगर (pkt_dev->flows[flow].count >= pkt_dev->lflow) अणु
			/* reset समय */
			pkt_dev->flows[flow].count = 0;
			pkt_dev->flows[flow].flags = 0;
			pkt_dev->curfl += 1;
			अगर (pkt_dev->curfl >= pkt_dev->cflows)
				pkt_dev->curfl = 0; /*reset */
		पूर्ण
	पूर्ण अन्यथा अणु
		flow = pअक्रमom_u32() % pkt_dev->cflows;
		pkt_dev->curfl = flow;

		अगर (pkt_dev->flows[flow].count > pkt_dev->lflow) अणु
			pkt_dev->flows[flow].count = 0;
			pkt_dev->flows[flow].flags = 0;
		पूर्ण
	पूर्ण

	वापस pkt_dev->curfl;
पूर्ण


#अगर_घोषित CONFIG_XFRM
/* If there was alपढ़ोy an IPSEC SA, we keep it as is, अन्यथा
 * we go look क्रम it ...
*/
#घोषणा DUMMY_MARK 0
अटल व्योम get_ipsec_sa(काष्ठा pktgen_dev *pkt_dev, पूर्णांक flow)
अणु
	काष्ठा xfrm_state *x = pkt_dev->flows[flow].x;
	काष्ठा pktgen_net *pn = net_generic(dev_net(pkt_dev->odev), pg_net_id);
	अगर (!x) अणु

		अगर (pkt_dev->spi) अणु
			/* We need as quick as possible to find the right SA
			 * Searching with minimum criteria to archieve this.
			 */
			x = xfrm_state_lookup_byspi(pn->net, htonl(pkt_dev->spi), AF_INET);
		पूर्ण अन्यथा अणु
			/* slow path: we करोnt alपढ़ोy have xfrm_state */
			x = xfrm_stateonly_find(pn->net, DUMMY_MARK, 0,
						(xfrm_address_t *)&pkt_dev->cur_daddr,
						(xfrm_address_t *)&pkt_dev->cur_saddr,
						AF_INET,
						pkt_dev->ipsmode,
						pkt_dev->ipsproto, 0);
		पूर्ण
		अगर (x) अणु
			pkt_dev->flows[flow].x = x;
			set_pkt_overhead(pkt_dev);
			pkt_dev->pkt_overhead += x->props.header_len;
		पूर्ण

	पूर्ण
पूर्ण
#पूर्ण_अगर
अटल व्योम set_cur_queue_map(काष्ठा pktgen_dev *pkt_dev)
अणु

	अगर (pkt_dev->flags & F_QUEUE_MAP_CPU)
		pkt_dev->cur_queue_map = smp_processor_id();

	अन्यथा अगर (pkt_dev->queue_map_min <= pkt_dev->queue_map_max) अणु
		__u16 t;
		अगर (pkt_dev->flags & F_QUEUE_MAP_RND) अणु
			t = pअक्रमom_u32() %
				(pkt_dev->queue_map_max -
				 pkt_dev->queue_map_min + 1)
				+ pkt_dev->queue_map_min;
		पूर्ण अन्यथा अणु
			t = pkt_dev->cur_queue_map + 1;
			अगर (t > pkt_dev->queue_map_max)
				t = pkt_dev->queue_map_min;
		पूर्ण
		pkt_dev->cur_queue_map = t;
	पूर्ण
	pkt_dev->cur_queue_map  = pkt_dev->cur_queue_map % pkt_dev->odev->real_num_tx_queues;
पूर्ण

/* Increment/अक्रमomize headers according to flags and current values
 * क्रम IP src/dest, UDP src/dst port, MAC-Addr src/dst
 */
अटल व्योम mod_cur_headers(काष्ठा pktgen_dev *pkt_dev)
अणु
	__u32 imn;
	__u32 imx;
	पूर्णांक flow = 0;

	अगर (pkt_dev->cflows)
		flow = f_pick(pkt_dev);

	/*  Deal with source MAC */
	अगर (pkt_dev->src_mac_count > 1) अणु
		__u32 mc;
		__u32 पंचांगp;

		अगर (pkt_dev->flags & F_MACSRC_RND)
			mc = pअक्रमom_u32() % pkt_dev->src_mac_count;
		अन्यथा अणु
			mc = pkt_dev->cur_src_mac_offset++;
			अगर (pkt_dev->cur_src_mac_offset >=
			    pkt_dev->src_mac_count)
				pkt_dev->cur_src_mac_offset = 0;
		पूर्ण

		पंचांगp = pkt_dev->src_mac[5] + (mc & 0xFF);
		pkt_dev->hh[11] = पंचांगp;
		पंचांगp = (pkt_dev->src_mac[4] + ((mc >> 8) & 0xFF) + (पंचांगp >> 8));
		pkt_dev->hh[10] = पंचांगp;
		पंचांगp = (pkt_dev->src_mac[3] + ((mc >> 16) & 0xFF) + (पंचांगp >> 8));
		pkt_dev->hh[9] = पंचांगp;
		पंचांगp = (pkt_dev->src_mac[2] + ((mc >> 24) & 0xFF) + (पंचांगp >> 8));
		pkt_dev->hh[8] = पंचांगp;
		पंचांगp = (pkt_dev->src_mac[1] + (पंचांगp >> 8));
		pkt_dev->hh[7] = पंचांगp;
	पूर्ण

	/*  Deal with Destination MAC */
	अगर (pkt_dev->dst_mac_count > 1) अणु
		__u32 mc;
		__u32 पंचांगp;

		अगर (pkt_dev->flags & F_MACDST_RND)
			mc = pअक्रमom_u32() % pkt_dev->dst_mac_count;

		अन्यथा अणु
			mc = pkt_dev->cur_dst_mac_offset++;
			अगर (pkt_dev->cur_dst_mac_offset >=
			    pkt_dev->dst_mac_count) अणु
				pkt_dev->cur_dst_mac_offset = 0;
			पूर्ण
		पूर्ण

		पंचांगp = pkt_dev->dst_mac[5] + (mc & 0xFF);
		pkt_dev->hh[5] = पंचांगp;
		पंचांगp = (pkt_dev->dst_mac[4] + ((mc >> 8) & 0xFF) + (पंचांगp >> 8));
		pkt_dev->hh[4] = पंचांगp;
		पंचांगp = (pkt_dev->dst_mac[3] + ((mc >> 16) & 0xFF) + (पंचांगp >> 8));
		pkt_dev->hh[3] = पंचांगp;
		पंचांगp = (pkt_dev->dst_mac[2] + ((mc >> 24) & 0xFF) + (पंचांगp >> 8));
		pkt_dev->hh[2] = पंचांगp;
		पंचांगp = (pkt_dev->dst_mac[1] + (पंचांगp >> 8));
		pkt_dev->hh[1] = पंचांगp;
	पूर्ण

	अगर (pkt_dev->flags & F_MPLS_RND) अणु
		अचिन्हित पूर्णांक i;
		क्रम (i = 0; i < pkt_dev->nr_labels; i++)
			अगर (pkt_dev->labels[i] & MPLS_STACK_BOTTOM)
				pkt_dev->labels[i] = MPLS_STACK_BOTTOM |
					     ((__क्रमce __be32)pअक्रमom_u32() &
						      htonl(0x000fffff));
	पूर्ण

	अगर ((pkt_dev->flags & F_VID_RND) && (pkt_dev->vlan_id != 0xffff)) अणु
		pkt_dev->vlan_id = pअक्रमom_u32() & (4096 - 1);
	पूर्ण

	अगर ((pkt_dev->flags & F_SVID_RND) && (pkt_dev->svlan_id != 0xffff)) अणु
		pkt_dev->svlan_id = pअक्रमom_u32() & (4096 - 1);
	पूर्ण

	अगर (pkt_dev->udp_src_min < pkt_dev->udp_src_max) अणु
		अगर (pkt_dev->flags & F_UDPSRC_RND)
			pkt_dev->cur_udp_src = pअक्रमom_u32() %
				(pkt_dev->udp_src_max - pkt_dev->udp_src_min)
				+ pkt_dev->udp_src_min;

		अन्यथा अणु
			pkt_dev->cur_udp_src++;
			अगर (pkt_dev->cur_udp_src >= pkt_dev->udp_src_max)
				pkt_dev->cur_udp_src = pkt_dev->udp_src_min;
		पूर्ण
	पूर्ण

	अगर (pkt_dev->udp_dst_min < pkt_dev->udp_dst_max) अणु
		अगर (pkt_dev->flags & F_UDPDST_RND) अणु
			pkt_dev->cur_udp_dst = pअक्रमom_u32() %
				(pkt_dev->udp_dst_max - pkt_dev->udp_dst_min)
				+ pkt_dev->udp_dst_min;
		पूर्ण अन्यथा अणु
			pkt_dev->cur_udp_dst++;
			अगर (pkt_dev->cur_udp_dst >= pkt_dev->udp_dst_max)
				pkt_dev->cur_udp_dst = pkt_dev->udp_dst_min;
		पूर्ण
	पूर्ण

	अगर (!(pkt_dev->flags & F_IPV6)) अणु

		imn = ntohl(pkt_dev->saddr_min);
		imx = ntohl(pkt_dev->saddr_max);
		अगर (imn < imx) अणु
			__u32 t;
			अगर (pkt_dev->flags & F_IPSRC_RND)
				t = pअक्रमom_u32() % (imx - imn) + imn;
			अन्यथा अणु
				t = ntohl(pkt_dev->cur_saddr);
				t++;
				अगर (t > imx)
					t = imn;

			पूर्ण
			pkt_dev->cur_saddr = htonl(t);
		पूर्ण

		अगर (pkt_dev->cflows && f_seen(pkt_dev, flow)) अणु
			pkt_dev->cur_daddr = pkt_dev->flows[flow].cur_daddr;
		पूर्ण अन्यथा अणु
			imn = ntohl(pkt_dev->daddr_min);
			imx = ntohl(pkt_dev->daddr_max);
			अगर (imn < imx) अणु
				__u32 t;
				__be32 s;
				अगर (pkt_dev->flags & F_IPDST_RND) अणु

					करो अणु
						t = pअक्रमom_u32() %
							(imx - imn) + imn;
						s = htonl(t);
					पूर्ण जबतक (ipv4_is_loopback(s) ||
						ipv4_is_multicast(s) ||
						ipv4_is_lbcast(s) ||
						ipv4_is_zeronet(s) ||
						ipv4_is_local_multicast(s));
					pkt_dev->cur_daddr = s;
				पूर्ण अन्यथा अणु
					t = ntohl(pkt_dev->cur_daddr);
					t++;
					अगर (t > imx) अणु
						t = imn;
					पूर्ण
					pkt_dev->cur_daddr = htonl(t);
				पूर्ण
			पूर्ण
			अगर (pkt_dev->cflows) अणु
				pkt_dev->flows[flow].flags |= F_INIT;
				pkt_dev->flows[flow].cur_daddr =
				    pkt_dev->cur_daddr;
#अगर_घोषित CONFIG_XFRM
				अगर (pkt_dev->flags & F_IPSEC)
					get_ipsec_sa(pkt_dev, flow);
#पूर्ण_अगर
				pkt_dev->nflows++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु		/* IPV6 * */

		अगर (!ipv6_addr_any(&pkt_dev->min_in6_daddr)) अणु
			पूर्णांक i;

			/* Only अक्रमom destinations yet */

			क्रम (i = 0; i < 4; i++) अणु
				pkt_dev->cur_in6_daddr.s6_addr32[i] =
				    (((__क्रमce __be32)pअक्रमom_u32() |
				      pkt_dev->min_in6_daddr.s6_addr32[i]) &
				     pkt_dev->max_in6_daddr.s6_addr32[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pkt_dev->min_pkt_size < pkt_dev->max_pkt_size) अणु
		__u32 t;
		अगर (pkt_dev->flags & F_TXSIZE_RND) अणु
			t = pअक्रमom_u32() %
				(pkt_dev->max_pkt_size - pkt_dev->min_pkt_size)
				+ pkt_dev->min_pkt_size;
		पूर्ण अन्यथा अणु
			t = pkt_dev->cur_pkt_size + 1;
			अगर (t > pkt_dev->max_pkt_size)
				t = pkt_dev->min_pkt_size;
		पूर्ण
		pkt_dev->cur_pkt_size = t;
	पूर्ण

	set_cur_queue_map(pkt_dev);

	pkt_dev->flows[flow].count++;
पूर्ण


#अगर_घोषित CONFIG_XFRM
अटल u32 pktgen_dst_metrics[RTAX_MAX + 1] = अणु

	[RTAX_HOPLIMIT] = 0x5, /* Set a अटल hoplimit */
पूर्ण;

अटल पूर्णांक pktgen_output_ipsec(काष्ठा sk_buff *skb, काष्ठा pktgen_dev *pkt_dev)
अणु
	काष्ठा xfrm_state *x = pkt_dev->flows[pkt_dev->curfl].x;
	पूर्णांक err = 0;
	काष्ठा net *net = dev_net(pkt_dev->odev);

	अगर (!x)
		वापस 0;
	/* XXX: we करोnt support tunnel mode क्रम now until
	 * we resolve the dst issue */
	अगर ((x->props.mode != XFRM_MODE_TRANSPORT) && (pkt_dev->spi == 0))
		वापस 0;

	/* But when user specअगरy an valid SPI, transक्रमmation
	 * supports both transport/tunnel mode + ESP/AH type.
	 */
	अगर ((x->props.mode == XFRM_MODE_TUNNEL) && (pkt_dev->spi != 0))
		skb->_skb_refdst = (अचिन्हित दीर्घ)&pkt_dev->xdst.u.dst | SKB_DST_NOREF;

	rcu_पढ़ो_lock_bh();
	err = pktgen_xfrm_outer_mode_output(x, skb);
	rcu_पढ़ो_unlock_bh();
	अगर (err) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEMODEERROR);
		जाओ error;
	पूर्ण
	err = x->type->output(x, skb);
	अगर (err) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEPROTOERROR);
		जाओ error;
	पूर्ण
	spin_lock_bh(&x->lock);
	x->curlft.bytes += skb->len;
	x->curlft.packets++;
	spin_unlock_bh(&x->lock);
error:
	वापस err;
पूर्ण

अटल व्योम मुक्त_SAs(काष्ठा pktgen_dev *pkt_dev)
अणु
	अगर (pkt_dev->cflows) अणु
		/* let go of the SAs अगर we have them */
		पूर्णांक i;
		क्रम (i = 0; i < pkt_dev->cflows; i++) अणु
			काष्ठा xfrm_state *x = pkt_dev->flows[i].x;
			अगर (x) अणु
				xfrm_state_put(x);
				pkt_dev->flows[i].x = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक process_ipsec(काष्ठा pktgen_dev *pkt_dev,
			      काष्ठा sk_buff *skb, __be16 protocol)
अणु
	अगर (pkt_dev->flags & F_IPSEC) अणु
		काष्ठा xfrm_state *x = pkt_dev->flows[pkt_dev->curfl].x;
		पूर्णांक nhead = 0;
		अगर (x) अणु
			काष्ठा ethhdr *eth;
			काष्ठा iphdr *iph;
			पूर्णांक ret;

			nhead = x->props.header_len - skb_headroom(skb);
			अगर (nhead > 0) अणु
				ret = pskb_expand_head(skb, nhead, 0, GFP_ATOMIC);
				अगर (ret < 0) अणु
					pr_err("Error expanding ipsec packet %d\n",
					       ret);
					जाओ err;
				पूर्ण
			पूर्ण

			/* ipsec is not expecting ll header */
			skb_pull(skb, ETH_HLEN);
			ret = pktgen_output_ipsec(skb, pkt_dev);
			अगर (ret) अणु
				pr_err("Error creating ipsec packet %d\n", ret);
				जाओ err;
			पूर्ण
			/* restore ll */
			eth = skb_push(skb, ETH_HLEN);
			स_नकल(eth, pkt_dev->hh, 2 * ETH_ALEN);
			eth->h_proto = protocol;

			/* Update IPv4 header len as well as checksum value */
			iph = ip_hdr(skb);
			iph->tot_len = htons(skb->len - ETH_HLEN);
			ip_send_check(iph);
		पूर्ण
	पूर्ण
	वापस 1;
err:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम mpls_push(__be32 *mpls, काष्ठा pktgen_dev *pkt_dev)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < pkt_dev->nr_labels; i++)
		*mpls++ = pkt_dev->labels[i] & ~MPLS_STACK_BOTTOM;

	mpls--;
	*mpls |= MPLS_STACK_BOTTOM;
पूर्ण

अटल अंतरभूत __be16 build_tci(अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक cfi,
			       अचिन्हित पूर्णांक prio)
अणु
	वापस htons(id | (cfi << 12) | (prio << 13));
पूर्ण

अटल व्योम pktgen_finalize_skb(काष्ठा pktgen_dev *pkt_dev, काष्ठा sk_buff *skb,
				पूर्णांक datalen)
अणु
	काष्ठा बारpec64 बारtamp;
	काष्ठा pktgen_hdr *pgh;

	pgh = skb_put(skb, माप(*pgh));
	datalen -= माप(*pgh);

	अगर (pkt_dev->nfrags <= 0) अणु
		skb_put_zero(skb, datalen);
	पूर्ण अन्यथा अणु
		पूर्णांक frags = pkt_dev->nfrags;
		पूर्णांक i, len;
		पूर्णांक frag_len;


		अगर (frags > MAX_SKB_FRAGS)
			frags = MAX_SKB_FRAGS;
		len = datalen - frags * PAGE_SIZE;
		अगर (len > 0) अणु
			skb_put_zero(skb, len);
			datalen = frags * PAGE_SIZE;
		पूर्ण

		i = 0;
		frag_len = (datalen/frags) < PAGE_SIZE ?
			   (datalen/frags) : PAGE_SIZE;
		जबतक (datalen > 0) अणु
			अगर (unlikely(!pkt_dev->page)) अणु
				पूर्णांक node = numa_node_id();

				अगर (pkt_dev->node >= 0 && (pkt_dev->flags & F_NODE))
					node = pkt_dev->node;
				pkt_dev->page = alloc_pages_node(node, GFP_KERNEL | __GFP_ZERO, 0);
				अगर (!pkt_dev->page)
					अवरोध;
			पूर्ण
			get_page(pkt_dev->page);
			skb_frag_set_page(skb, i, pkt_dev->page);
			skb_frag_off_set(&skb_shinfo(skb)->frags[i], 0);
			/*last fragment, fill rest of data*/
			अगर (i == (frags - 1))
				skb_frag_size_set(&skb_shinfo(skb)->frags[i],
				    (datalen < PAGE_SIZE ? datalen : PAGE_SIZE));
			अन्यथा
				skb_frag_size_set(&skb_shinfo(skb)->frags[i], frag_len);
			datalen -= skb_frag_size(&skb_shinfo(skb)->frags[i]);
			skb->len += skb_frag_size(&skb_shinfo(skb)->frags[i]);
			skb->data_len += skb_frag_size(&skb_shinfo(skb)->frags[i]);
			i++;
			skb_shinfo(skb)->nr_frags = i;
		पूर्ण
	पूर्ण

	/* Stamp the समय, and sequence number,
	 * convert them to network byte order
	 */
	pgh->pgh_magic = htonl(PKTGEN_MAGIC);
	pgh->seq_num = htonl(pkt_dev->seq_num);

	अगर (pkt_dev->flags & F_NO_TIMESTAMP) अणु
		pgh->tv_sec = 0;
		pgh->tv_usec = 0;
	पूर्ण अन्यथा अणु
		/*
		 * pgh->tv_sec wraps in y2106 when पूर्णांकerpreted as अचिन्हित
		 * as करोne by wireshark, or y2038 when पूर्णांकerpreted as चिन्हित.
		 * This is probably harmless, but अगर anyone wants to improve
		 * it, we could पूर्णांकroduce a variant that माला_दो 64-bit nanoseconds
		 * पूर्णांकo the respective header bytes.
		 * This would also be slightly faster to पढ़ो.
		 */
		kसमय_get_real_ts64(&बारtamp);
		pgh->tv_sec = htonl(बारtamp.tv_sec);
		pgh->tv_usec = htonl(बारtamp.tv_nsec / NSEC_PER_USEC);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *pktgen_alloc_skb(काष्ठा net_device *dev,
					काष्ठा pktgen_dev *pkt_dev)
अणु
	अचिन्हित पूर्णांक extralen = LL_RESERVED_SPACE(dev);
	काष्ठा sk_buff *skb = शून्य;
	अचिन्हित पूर्णांक size;

	size = pkt_dev->cur_pkt_size + 64 + extralen + pkt_dev->pkt_overhead;
	अगर (pkt_dev->flags & F_NODE) अणु
		पूर्णांक node = pkt_dev->node >= 0 ? pkt_dev->node : numa_node_id();

		skb = __alloc_skb(NET_SKB_PAD + size, GFP_NOWAIT, 0, node);
		अगर (likely(skb)) अणु
			skb_reserve(skb, NET_SKB_PAD);
			skb->dev = dev;
		पूर्ण
	पूर्ण अन्यथा अणु
		 skb = __netdev_alloc_skb(dev, size, GFP_NOWAIT);
	पूर्ण

	/* the caller pre-fetches from skb->data and reserves क्रम the mac hdr */
	अगर (likely(skb))
		skb_reserve(skb, extralen - 16);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *fill_packet_ipv4(काष्ठा net_device *odev,
					काष्ठा pktgen_dev *pkt_dev)
अणु
	काष्ठा sk_buff *skb = शून्य;
	__u8 *eth;
	काष्ठा udphdr *udph;
	पूर्णांक datalen, iplen;
	काष्ठा iphdr *iph;
	__be16 protocol = htons(ETH_P_IP);
	__be32 *mpls;
	__be16 *vlan_tci = शून्य;                 /* Encapsulates priority and VLAN ID */
	__be16 *vlan_encapsulated_proto = शून्य;  /* packet type ID field (or len) क्रम VLAN tag */
	__be16 *svlan_tci = शून्य;                /* Encapsulates priority and SVLAN ID */
	__be16 *svlan_encapsulated_proto = शून्य; /* packet type ID field (or len) क्रम SVLAN tag */
	u16 queue_map;

	अगर (pkt_dev->nr_labels)
		protocol = htons(ETH_P_MPLS_UC);

	अगर (pkt_dev->vlan_id != 0xffff)
		protocol = htons(ETH_P_8021Q);

	/* Update any of the values, used when we're incrementing various
	 * fields.
	 */
	mod_cur_headers(pkt_dev);
	queue_map = pkt_dev->cur_queue_map;

	skb = pktgen_alloc_skb(odev, pkt_dev);
	अगर (!skb) अणु
		प्र_लिखो(pkt_dev->result, "No memory");
		वापस शून्य;
	पूर्ण

	prefetchw(skb->data);
	skb_reserve(skb, 16);

	/*  Reserve क्रम ethernet and IP header  */
	eth = skb_push(skb, 14);
	mpls = skb_put(skb, pkt_dev->nr_labels * माप(__u32));
	अगर (pkt_dev->nr_labels)
		mpls_push(mpls, pkt_dev);

	अगर (pkt_dev->vlan_id != 0xffff) अणु
		अगर (pkt_dev->svlan_id != 0xffff) अणु
			svlan_tci = skb_put(skb, माप(__be16));
			*svlan_tci = build_tci(pkt_dev->svlan_id,
					       pkt_dev->svlan_cfi,
					       pkt_dev->svlan_p);
			svlan_encapsulated_proto = skb_put(skb,
							   माप(__be16));
			*svlan_encapsulated_proto = htons(ETH_P_8021Q);
		पूर्ण
		vlan_tci = skb_put(skb, माप(__be16));
		*vlan_tci = build_tci(pkt_dev->vlan_id,
				      pkt_dev->vlan_cfi,
				      pkt_dev->vlan_p);
		vlan_encapsulated_proto = skb_put(skb, माप(__be16));
		*vlan_encapsulated_proto = htons(ETH_P_IP);
	पूर्ण

	skb_reset_mac_header(skb);
	skb_set_network_header(skb, skb->len);
	iph = skb_put(skb, माप(काष्ठा iphdr));

	skb_set_transport_header(skb, skb->len);
	udph = skb_put(skb, माप(काष्ठा udphdr));
	skb_set_queue_mapping(skb, queue_map);
	skb->priority = pkt_dev->skb_priority;

	स_नकल(eth, pkt_dev->hh, 12);
	*(__be16 *) & eth[12] = protocol;

	/* Eth + IPh + UDPh + mpls */
	datalen = pkt_dev->cur_pkt_size - 14 - 20 - 8 -
		  pkt_dev->pkt_overhead;
	अगर (datalen < 0 || datalen < माप(काष्ठा pktgen_hdr))
		datalen = माप(काष्ठा pktgen_hdr);

	udph->source = htons(pkt_dev->cur_udp_src);
	udph->dest = htons(pkt_dev->cur_udp_dst);
	udph->len = htons(datalen + 8);	/* DATA + udphdr */
	udph->check = 0;

	iph->ihl = 5;
	iph->version = 4;
	iph->ttl = 32;
	iph->tos = pkt_dev->tos;
	iph->protocol = IPPROTO_UDP;	/* UDP */
	iph->saddr = pkt_dev->cur_saddr;
	iph->daddr = pkt_dev->cur_daddr;
	iph->id = htons(pkt_dev->ip_id);
	pkt_dev->ip_id++;
	iph->frag_off = 0;
	iplen = 20 + 8 + datalen;
	iph->tot_len = htons(iplen);
	ip_send_check(iph);
	skb->protocol = protocol;
	skb->dev = odev;
	skb->pkt_type = PACKET_HOST;

	pktgen_finalize_skb(pkt_dev, skb, datalen);

	अगर (!(pkt_dev->flags & F_UDPCSUM)) अणु
		skb->ip_summed = CHECKSUM_NONE;
	पूर्ण अन्यथा अगर (odev->features & (NETIF_F_HW_CSUM | NETIF_F_IP_CSUM)) अणु
		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum = 0;
		udp4_hwcsum(skb, iph->saddr, iph->daddr);
	पूर्ण अन्यथा अणु
		__wsum csum = skb_checksum(skb, skb_transport_offset(skb), datalen + 8, 0);

		/* add protocol-dependent pseuकरो-header */
		udph->check = csum_tcpudp_magic(iph->saddr, iph->daddr,
						datalen + 8, IPPROTO_UDP, csum);

		अगर (udph->check == 0)
			udph->check = CSUM_MANGLED_0;
	पूर्ण

#अगर_घोषित CONFIG_XFRM
	अगर (!process_ipsec(pkt_dev, skb, protocol))
		वापस शून्य;
#पूर्ण_अगर

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *fill_packet_ipv6(काष्ठा net_device *odev,
					काष्ठा pktgen_dev *pkt_dev)
अणु
	काष्ठा sk_buff *skb = शून्य;
	__u8 *eth;
	काष्ठा udphdr *udph;
	पूर्णांक datalen, udplen;
	काष्ठा ipv6hdr *iph;
	__be16 protocol = htons(ETH_P_IPV6);
	__be32 *mpls;
	__be16 *vlan_tci = शून्य;                 /* Encapsulates priority and VLAN ID */
	__be16 *vlan_encapsulated_proto = शून्य;  /* packet type ID field (or len) क्रम VLAN tag */
	__be16 *svlan_tci = शून्य;                /* Encapsulates priority and SVLAN ID */
	__be16 *svlan_encapsulated_proto = शून्य; /* packet type ID field (or len) क्रम SVLAN tag */
	u16 queue_map;

	अगर (pkt_dev->nr_labels)
		protocol = htons(ETH_P_MPLS_UC);

	अगर (pkt_dev->vlan_id != 0xffff)
		protocol = htons(ETH_P_8021Q);

	/* Update any of the values, used when we're incrementing various
	 * fields.
	 */
	mod_cur_headers(pkt_dev);
	queue_map = pkt_dev->cur_queue_map;

	skb = pktgen_alloc_skb(odev, pkt_dev);
	अगर (!skb) अणु
		प्र_लिखो(pkt_dev->result, "No memory");
		वापस शून्य;
	पूर्ण

	prefetchw(skb->data);
	skb_reserve(skb, 16);

	/*  Reserve क्रम ethernet and IP header  */
	eth = skb_push(skb, 14);
	mpls = skb_put(skb, pkt_dev->nr_labels * माप(__u32));
	अगर (pkt_dev->nr_labels)
		mpls_push(mpls, pkt_dev);

	अगर (pkt_dev->vlan_id != 0xffff) अणु
		अगर (pkt_dev->svlan_id != 0xffff) अणु
			svlan_tci = skb_put(skb, माप(__be16));
			*svlan_tci = build_tci(pkt_dev->svlan_id,
					       pkt_dev->svlan_cfi,
					       pkt_dev->svlan_p);
			svlan_encapsulated_proto = skb_put(skb,
							   माप(__be16));
			*svlan_encapsulated_proto = htons(ETH_P_8021Q);
		पूर्ण
		vlan_tci = skb_put(skb, माप(__be16));
		*vlan_tci = build_tci(pkt_dev->vlan_id,
				      pkt_dev->vlan_cfi,
				      pkt_dev->vlan_p);
		vlan_encapsulated_proto = skb_put(skb, माप(__be16));
		*vlan_encapsulated_proto = htons(ETH_P_IPV6);
	पूर्ण

	skb_reset_mac_header(skb);
	skb_set_network_header(skb, skb->len);
	iph = skb_put(skb, माप(काष्ठा ipv6hdr));

	skb_set_transport_header(skb, skb->len);
	udph = skb_put(skb, माप(काष्ठा udphdr));
	skb_set_queue_mapping(skb, queue_map);
	skb->priority = pkt_dev->skb_priority;

	स_नकल(eth, pkt_dev->hh, 12);
	*(__be16 *) &eth[12] = protocol;

	/* Eth + IPh + UDPh + mpls */
	datalen = pkt_dev->cur_pkt_size - 14 -
		  माप(काष्ठा ipv6hdr) - माप(काष्ठा udphdr) -
		  pkt_dev->pkt_overhead;

	अगर (datalen < 0 || datalen < माप(काष्ठा pktgen_hdr)) अणु
		datalen = माप(काष्ठा pktgen_hdr);
		net_info_ratelimited("increased datalen to %d\n", datalen);
	पूर्ण

	udplen = datalen + माप(काष्ठा udphdr);
	udph->source = htons(pkt_dev->cur_udp_src);
	udph->dest = htons(pkt_dev->cur_udp_dst);
	udph->len = htons(udplen);
	udph->check = 0;

	*(__be32 *) iph = htonl(0x60000000);	/* Version + flow */

	अगर (pkt_dev->traffic_class) अणु
		/* Version + traffic class + flow (0) */
		*(__be32 *)iph |= htonl(0x60000000 | (pkt_dev->traffic_class << 20));
	पूर्ण

	iph->hop_limit = 32;

	iph->payload_len = htons(udplen);
	iph->nexthdr = IPPROTO_UDP;

	iph->daddr = pkt_dev->cur_in6_daddr;
	iph->saddr = pkt_dev->cur_in6_saddr;

	skb->protocol = protocol;
	skb->dev = odev;
	skb->pkt_type = PACKET_HOST;

	pktgen_finalize_skb(pkt_dev, skb, datalen);

	अगर (!(pkt_dev->flags & F_UDPCSUM)) अणु
		skb->ip_summed = CHECKSUM_NONE;
	पूर्ण अन्यथा अगर (odev->features & (NETIF_F_HW_CSUM | NETIF_F_IPV6_CSUM)) अणु
		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = दुरत्व(काष्ठा udphdr, check);
		udph->check = ~csum_ipv6_magic(&iph->saddr, &iph->daddr, udplen, IPPROTO_UDP, 0);
	पूर्ण अन्यथा अणु
		__wsum csum = skb_checksum(skb, skb_transport_offset(skb), udplen, 0);

		/* add protocol-dependent pseuकरो-header */
		udph->check = csum_ipv6_magic(&iph->saddr, &iph->daddr, udplen, IPPROTO_UDP, csum);

		अगर (udph->check == 0)
			udph->check = CSUM_MANGLED_0;
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *fill_packet(काष्ठा net_device *odev,
				   काष्ठा pktgen_dev *pkt_dev)
अणु
	अगर (pkt_dev->flags & F_IPV6)
		वापस fill_packet_ipv6(odev, pkt_dev);
	अन्यथा
		वापस fill_packet_ipv4(odev, pkt_dev);
पूर्ण

अटल व्योम pktgen_clear_counters(काष्ठा pktgen_dev *pkt_dev)
अणु
	pkt_dev->seq_num = 1;
	pkt_dev->idle_acc = 0;
	pkt_dev->sofar = 0;
	pkt_dev->tx_bytes = 0;
	pkt_dev->errors = 0;
पूर्ण

/* Set up काष्ठाure क्रम sending pkts, clear counters */

अटल व्योम pktgen_run(काष्ठा pktgen_thपढ़ो *t)
अणु
	काष्ठा pktgen_dev *pkt_dev;
	पूर्णांक started = 0;

	func_enter();

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pkt_dev, &t->अगर_list, list) अणु

		/*
		 * setup odev and create initial packet.
		 */
		pktgen_setup_inject(pkt_dev);

		अगर (pkt_dev->odev) अणु
			pktgen_clear_counters(pkt_dev);
			pkt_dev->skb = शून्य;
			pkt_dev->started_at = pkt_dev->next_tx = kसमय_get();

			set_pkt_overhead(pkt_dev);

			म_नकल(pkt_dev->result, "Starting");
			pkt_dev->running = 1;	/* Cranke yeself! */
			started++;
		पूर्ण अन्यथा
			म_नकल(pkt_dev->result, "Error starting");
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (started)
		t->control &= ~(T_STOP);
पूर्ण

अटल व्योम pktgen_stop_all_thपढ़ोs_अगरs(काष्ठा pktgen_net *pn)
अणु
	काष्ठा pktgen_thपढ़ो *t;

	func_enter();

	mutex_lock(&pktgen_thपढ़ो_lock);

	list_क्रम_each_entry(t, &pn->pktgen_thपढ़ोs, th_list)
		t->control |= T_STOP;

	mutex_unlock(&pktgen_thपढ़ो_lock);
पूर्ण

अटल पूर्णांक thपढ़ो_is_running(स्थिर काष्ठा pktgen_thपढ़ो *t)
अणु
	स्थिर काष्ठा pktgen_dev *pkt_dev;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pkt_dev, &t->अगर_list, list)
		अगर (pkt_dev->running) अणु
			rcu_पढ़ो_unlock();
			वापस 1;
		पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक pktgen_रुको_thपढ़ो_run(काष्ठा pktgen_thपढ़ो *t)
अणु
	जबतक (thपढ़ो_is_running(t)) अणु

		/* note: 't' will still be around even after the unlock/lock
		 * cycle because pktgen_thपढ़ो thपढ़ोs are only cleared at
		 * net निकास
		 */
		mutex_unlock(&pktgen_thपढ़ो_lock);
		msleep_पूर्णांकerruptible(100);
		mutex_lock(&pktgen_thपढ़ो_lock);

		अगर (संकेत_pending(current))
			जाओ संकेत;
	पूर्ण
	वापस 1;
संकेत:
	वापस 0;
पूर्ण

अटल पूर्णांक pktgen_रुको_all_thपढ़ोs_run(काष्ठा pktgen_net *pn)
अणु
	काष्ठा pktgen_thपढ़ो *t;
	पूर्णांक sig = 1;

	/* prevent from racing with rmmod */
	अगर (!try_module_get(THIS_MODULE))
		वापस sig;

	mutex_lock(&pktgen_thपढ़ो_lock);

	list_क्रम_each_entry(t, &pn->pktgen_thपढ़ोs, th_list) अणु
		sig = pktgen_रुको_thपढ़ो_run(t);
		अगर (sig == 0)
			अवरोध;
	पूर्ण

	अगर (sig == 0)
		list_क्रम_each_entry(t, &pn->pktgen_thपढ़ोs, th_list)
			t->control |= (T_STOP);

	mutex_unlock(&pktgen_thपढ़ो_lock);
	module_put(THIS_MODULE);
	वापस sig;
पूर्ण

अटल व्योम pktgen_run_all_thपढ़ोs(काष्ठा pktgen_net *pn)
अणु
	काष्ठा pktgen_thपढ़ो *t;

	func_enter();

	mutex_lock(&pktgen_thपढ़ो_lock);

	list_क्रम_each_entry(t, &pn->pktgen_thपढ़ोs, th_list)
		t->control |= (T_RUN);

	mutex_unlock(&pktgen_thपढ़ो_lock);

	/* Propagate thपढ़ो->control  */
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(125));

	pktgen_रुको_all_thपढ़ोs_run(pn);
पूर्ण

अटल व्योम pktgen_reset_all_thपढ़ोs(काष्ठा pktgen_net *pn)
अणु
	काष्ठा pktgen_thपढ़ो *t;

	func_enter();

	mutex_lock(&pktgen_thपढ़ो_lock);

	list_क्रम_each_entry(t, &pn->pktgen_thपढ़ोs, th_list)
		t->control |= (T_REMDEVALL);

	mutex_unlock(&pktgen_thपढ़ो_lock);

	/* Propagate thपढ़ो->control  */
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(125));

	pktgen_रुको_all_thपढ़ोs_run(pn);
पूर्ण

अटल व्योम show_results(काष्ठा pktgen_dev *pkt_dev, पूर्णांक nr_frags)
अणु
	__u64 bps, mbps, pps;
	अक्षर *p = pkt_dev->result;
	kसमय_प्रकार elapsed = kसमय_sub(pkt_dev->stopped_at,
				    pkt_dev->started_at);
	kसमय_प्रकार idle = ns_to_kसमय(pkt_dev->idle_acc);

	p += प्र_लिखो(p, "OK: %llu(c%llu+d%llu) usec, %llu (%dbyte,%dfrags)\n",
		     (अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_us(elapsed),
		     (अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_us(kसमय_sub(elapsed, idle)),
		     (अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_us(idle),
		     (अचिन्हित दीर्घ दीर्घ)pkt_dev->sofar,
		     pkt_dev->cur_pkt_size, nr_frags);

	pps = भाग64_u64(pkt_dev->sofar * NSEC_PER_SEC,
			kसमय_प्रकारo_ns(elapsed));

	bps = pps * 8 * pkt_dev->cur_pkt_size;

	mbps = bps;
	करो_भाग(mbps, 1000000);
	p += प्र_लिखो(p, "  %llupps %lluMb/sec (%llubps) errors: %llu",
		     (अचिन्हित दीर्घ दीर्घ)pps,
		     (अचिन्हित दीर्घ दीर्घ)mbps,
		     (अचिन्हित दीर्घ दीर्घ)bps,
		     (अचिन्हित दीर्घ दीर्घ)pkt_dev->errors);
पूर्ण

/* Set stopped-at समयr, हटाओ from running list, करो counters & statistics */
अटल पूर्णांक pktgen_stop_device(काष्ठा pktgen_dev *pkt_dev)
अणु
	पूर्णांक nr_frags = pkt_dev->skb ? skb_shinfo(pkt_dev->skb)->nr_frags : -1;

	अगर (!pkt_dev->running) अणु
		pr_warn("interface: %s is already stopped\n",
			pkt_dev->odevname);
		वापस -EINVAL;
	पूर्ण

	pkt_dev->running = 0;
	kमुक्त_skb(pkt_dev->skb);
	pkt_dev->skb = शून्य;
	pkt_dev->stopped_at = kसमय_get();

	show_results(pkt_dev, nr_frags);

	वापस 0;
पूर्ण

अटल काष्ठा pktgen_dev *next_to_run(काष्ठा pktgen_thपढ़ो *t)
अणु
	काष्ठा pktgen_dev *pkt_dev, *best = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pkt_dev, &t->अगर_list, list) अणु
		अगर (!pkt_dev->running)
			जारी;
		अगर (best == शून्य)
			best = pkt_dev;
		अन्यथा अगर (kसमय_compare(pkt_dev->next_tx, best->next_tx) < 0)
			best = pkt_dev;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस best;
पूर्ण

अटल व्योम pktgen_stop(काष्ठा pktgen_thपढ़ो *t)
अणु
	काष्ठा pktgen_dev *pkt_dev;

	func_enter();

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(pkt_dev, &t->अगर_list, list) अणु
		pktgen_stop_device(pkt_dev);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/*
 * one of our devices needs to be हटाओd - find it
 * and हटाओ it
 */
अटल व्योम pktgen_rem_one_अगर(काष्ठा pktgen_thपढ़ो *t)
अणु
	काष्ठा list_head *q, *n;
	काष्ठा pktgen_dev *cur;

	func_enter();

	list_क्रम_each_safe(q, n, &t->अगर_list) अणु
		cur = list_entry(q, काष्ठा pktgen_dev, list);

		अगर (!cur->removal_mark)
			जारी;

		kमुक्त_skb(cur->skb);
		cur->skb = शून्य;

		pktgen_हटाओ_device(t, cur);

		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pktgen_rem_all_अगरs(काष्ठा pktgen_thपढ़ो *t)
अणु
	काष्ठा list_head *q, *n;
	काष्ठा pktgen_dev *cur;

	func_enter();

	/* Remove all devices, मुक्त mem */

	list_क्रम_each_safe(q, n, &t->अगर_list) अणु
		cur = list_entry(q, काष्ठा pktgen_dev, list);

		kमुक्त_skb(cur->skb);
		cur->skb = शून्य;

		pktgen_हटाओ_device(t, cur);
	पूर्ण
पूर्ण

अटल व्योम pktgen_rem_thपढ़ो(काष्ठा pktgen_thपढ़ो *t)
अणु
	/* Remove from the thपढ़ो list */
	हटाओ_proc_entry(t->tsk->comm, t->net->proc_dir);
पूर्ण

अटल व्योम pktgen_resched(काष्ठा pktgen_dev *pkt_dev)
अणु
	kसमय_प्रकार idle_start = kसमय_get();
	schedule();
	pkt_dev->idle_acc += kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), idle_start));
पूर्ण

अटल व्योम pktgen_रुको_क्रम_skb(काष्ठा pktgen_dev *pkt_dev)
अणु
	kसमय_प्रकार idle_start = kसमय_get();

	जबतक (refcount_पढ़ो(&(pkt_dev->skb->users)) != 1) अणु
		अगर (संकेत_pending(current))
			अवरोध;

		अगर (need_resched())
			pktgen_resched(pkt_dev);
		अन्यथा
			cpu_relax();
	पूर्ण
	pkt_dev->idle_acc += kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), idle_start));
पूर्ण

अटल व्योम pktgen_xmit(काष्ठा pktgen_dev *pkt_dev)
अणु
	अचिन्हित पूर्णांक burst = READ_ONCE(pkt_dev->burst);
	काष्ठा net_device *odev = pkt_dev->odev;
	काष्ठा netdev_queue *txq;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	/* If device is offline, then करोn't send */
	अगर (unlikely(!netअगर_running(odev) || !netअगर_carrier_ok(odev))) अणु
		pktgen_stop_device(pkt_dev);
		वापस;
	पूर्ण

	/* This is max DELAY, this has special meaning of
	 * "never transmit"
	 */
	अगर (unlikely(pkt_dev->delay == ULदीर्घ_उच्च)) अणु
		pkt_dev->next_tx = kसमय_add_ns(kसमय_get(), अच_दीर्घ_उच्च);
		वापस;
	पूर्ण

	/* If no skb or clone count exhausted then get new one */
	अगर (!pkt_dev->skb || (pkt_dev->last_ok &&
			      ++pkt_dev->clone_count >= pkt_dev->clone_skb)) अणु
		/* build a new pkt */
		kमुक्त_skb(pkt_dev->skb);

		pkt_dev->skb = fill_packet(odev, pkt_dev);
		अगर (pkt_dev->skb == शून्य) अणु
			pr_err("ERROR: couldn't allocate skb in fill_packet\n");
			schedule();
			pkt_dev->clone_count--;	/* back out increment, OOM */
			वापस;
		पूर्ण
		pkt_dev->last_pkt_size = pkt_dev->skb->len;
		pkt_dev->clone_count = 0;	/* reset counter */
	पूर्ण

	अगर (pkt_dev->delay && pkt_dev->last_ok)
		spin(pkt_dev, pkt_dev->next_tx);

	अगर (pkt_dev->xmit_mode == M_NETIF_RECEIVE) अणु
		skb = pkt_dev->skb;
		skb->protocol = eth_type_trans(skb, skb->dev);
		refcount_add(burst, &skb->users);
		local_bh_disable();
		करो अणु
			ret = netअगर_receive_skb(skb);
			अगर (ret == NET_RX_DROP)
				pkt_dev->errors++;
			pkt_dev->sofar++;
			pkt_dev->seq_num++;
			अगर (refcount_पढ़ो(&skb->users) != burst) अणु
				/* skb was queued by rps/rfs or taps,
				 * so cannot reuse this skb
				 */
				WARN_ON(refcount_sub_and_test(burst - 1, &skb->users));
				/* get out of the loop and रुको
				 * until skb is consumed
				 */
				अवरोध;
			पूर्ण
			/* skb was 'freed' by stack, so clean few
			 * bits and reuse it
			 */
			skb_reset_redirect(skb);
		पूर्ण जबतक (--burst > 0);
		जाओ out; /* Skips xmit_mode M_START_XMIT */
	पूर्ण अन्यथा अगर (pkt_dev->xmit_mode == M_QUEUE_XMIT) अणु
		local_bh_disable();
		refcount_inc(&pkt_dev->skb->users);

		ret = dev_queue_xmit(pkt_dev->skb);
		चयन (ret) अणु
		हाल NET_XMIT_SUCCESS:
			pkt_dev->sofar++;
			pkt_dev->seq_num++;
			pkt_dev->tx_bytes += pkt_dev->last_pkt_size;
			अवरोध;
		हाल NET_XMIT_DROP:
		हाल NET_XMIT_CN:
		/* These are all valid वापस codes क्रम a qdisc but
		 * indicate packets are being dropped or will likely
		 * be dropped soon.
		 */
		हाल NETDEV_TX_BUSY:
		/* qdisc may call dev_hard_start_xmit directly in हालs
		 * where no queues exist e.g. loopback device, भव
		 * devices, etc. In this हाल we need to handle
		 * NETDEV_TX_ codes.
		 */
		शेष:
			pkt_dev->errors++;
			net_info_ratelimited("%s xmit error: %d\n",
					     pkt_dev->odevname, ret);
			अवरोध;
		पूर्ण
		जाओ out;
	पूर्ण

	txq = skb_get_tx_queue(odev, pkt_dev->skb);

	local_bh_disable();

	HARD_TX_LOCK(odev, txq, smp_processor_id());

	अगर (unlikely(netअगर_xmit_frozen_or_drv_stopped(txq))) अणु
		pkt_dev->last_ok = 0;
		जाओ unlock;
	पूर्ण
	refcount_add(burst, &pkt_dev->skb->users);

xmit_more:
	ret = netdev_start_xmit(pkt_dev->skb, odev, txq, --burst > 0);

	चयन (ret) अणु
	हाल NETDEV_TX_OK:
		pkt_dev->last_ok = 1;
		pkt_dev->sofar++;
		pkt_dev->seq_num++;
		pkt_dev->tx_bytes += pkt_dev->last_pkt_size;
		अगर (burst > 0 && !netअगर_xmit_frozen_or_drv_stopped(txq))
			जाओ xmit_more;
		अवरोध;
	हाल NET_XMIT_DROP:
	हाल NET_XMIT_CN:
		/* skb has been consumed */
		pkt_dev->errors++;
		अवरोध;
	शेष: /* Drivers are not supposed to वापस other values! */
		net_info_ratelimited("%s xmit error: %d\n",
				     pkt_dev->odevname, ret);
		pkt_dev->errors++;
		fallthrough;
	हाल NETDEV_TX_BUSY:
		/* Retry it next समय */
		refcount_dec(&(pkt_dev->skb->users));
		pkt_dev->last_ok = 0;
	पूर्ण
	अगर (unlikely(burst))
		WARN_ON(refcount_sub_and_test(burst, &pkt_dev->skb->users));
unlock:
	HARD_TX_UNLOCK(odev, txq);

out:
	local_bh_enable();

	/* If pkt_dev->count is zero, then run क्रमever */
	अगर ((pkt_dev->count != 0) && (pkt_dev->sofar >= pkt_dev->count)) अणु
		pktgen_रुको_क्रम_skb(pkt_dev);

		/* Done with this */
		pktgen_stop_device(pkt_dev);
	पूर्ण
पूर्ण

/*
 * Main loop of the thपढ़ो goes here
 */

अटल पूर्णांक pktgen_thपढ़ो_worker(व्योम *arg)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा pktgen_thपढ़ो *t = arg;
	काष्ठा pktgen_dev *pkt_dev = शून्य;
	पूर्णांक cpu = t->cpu;

	WARN_ON(smp_processor_id() != cpu);

	init_रुकोqueue_head(&t->queue);
	complete(&t->start_करोne);

	pr_debug("starting pktgen/%d:  pid=%d\n", cpu, task_pid_nr(current));

	set_मुक्तzable();

	जबतक (!kthपढ़ो_should_stop()) अणु
		pkt_dev = next_to_run(t);

		अगर (unlikely(!pkt_dev && t->control == 0)) अणु
			अगर (t->net->pktgen_निकासing)
				अवरोध;
			रुको_event_पूर्णांकerruptible_समयout(t->queue,
							 t->control != 0,
							 HZ/10);
			try_to_मुक्तze();
			जारी;
		पूर्ण

		अगर (likely(pkt_dev)) अणु
			pktgen_xmit(pkt_dev);

			अगर (need_resched())
				pktgen_resched(pkt_dev);
			अन्यथा
				cpu_relax();
		पूर्ण

		अगर (t->control & T_STOP) अणु
			pktgen_stop(t);
			t->control &= ~(T_STOP);
		पूर्ण

		अगर (t->control & T_RUN) अणु
			pktgen_run(t);
			t->control &= ~(T_RUN);
		पूर्ण

		अगर (t->control & T_REMDEVALL) अणु
			pktgen_rem_all_अगरs(t);
			t->control &= ~(T_REMDEVALL);
		पूर्ण

		अगर (t->control & T_REMDEV) अणु
			pktgen_rem_one_अगर(t);
			t->control &= ~(T_REMDEV);
		पूर्ण

		try_to_मुक्तze();
	पूर्ण

	pr_debug("%s stopping all device\n", t->tsk->comm);
	pktgen_stop(t);

	pr_debug("%s removing all device\n", t->tsk->comm);
	pktgen_rem_all_अगरs(t);

	pr_debug("%s removing thread\n", t->tsk->comm);
	pktgen_rem_thपढ़ो(t);

	वापस 0;
पूर्ण

अटल काष्ठा pktgen_dev *pktgen_find_dev(काष्ठा pktgen_thपढ़ो *t,
					  स्थिर अक्षर *अगरname, bool exact)
अणु
	काष्ठा pktgen_dev *p, *pkt_dev = शून्य;
	माप_प्रकार len = म_माप(अगरname);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(p, &t->अगर_list, list)
		अगर (म_भेदन(p->odevname, अगरname, len) == 0) अणु
			अगर (p->odevname[len]) अणु
				अगर (exact || p->odevname[len] != '@')
					जारी;
			पूर्ण
			pkt_dev = p;
			अवरोध;
		पूर्ण

	rcu_पढ़ो_unlock();
	pr_debug("find_dev(%s) returning %p\n", अगरname, pkt_dev);
	वापस pkt_dev;
पूर्ण

/*
 * Adds a dev at front of अगर_list.
 */

अटल पूर्णांक add_dev_to_thपढ़ो(काष्ठा pktgen_thपढ़ो *t,
			     काष्ठा pktgen_dev *pkt_dev)
अणु
	पूर्णांक rv = 0;

	/* This function cannot be called concurrently, as its called
	 * under pktgen_thपढ़ो_lock mutex, but it can run from
	 * userspace on another CPU than the kthपढ़ो.  The अगर_lock()
	 * is used here to sync with concurrent instances of
	 * _rem_dev_from_अगर_list() invoked via kthपढ़ो, which is also
	 * updating the अगर_list */
	अगर_lock(t);

	अगर (pkt_dev->pg_thपढ़ो) अणु
		pr_err("ERROR: already assigned to a thread\n");
		rv = -EBUSY;
		जाओ out;
	पूर्ण

	pkt_dev->running = 0;
	pkt_dev->pg_thपढ़ो = t;
	list_add_rcu(&pkt_dev->list, &t->अगर_list);

out:
	अगर_unlock(t);
	वापस rv;
पूर्ण

/* Called under thपढ़ो lock */

अटल पूर्णांक pktgen_add_device(काष्ठा pktgen_thपढ़ो *t, स्थिर अक्षर *अगरname)
अणु
	काष्ठा pktgen_dev *pkt_dev;
	पूर्णांक err;
	पूर्णांक node = cpu_to_node(t->cpu);

	/* We करोn't allow a device to be on several thपढ़ोs */

	pkt_dev = __pktgen_NN_thपढ़ोs(t->net, अगरname, FIND);
	अगर (pkt_dev) अणु
		pr_err("ERROR: interface already used\n");
		वापस -EBUSY;
	पूर्ण

	pkt_dev = kzalloc_node(माप(काष्ठा pktgen_dev), GFP_KERNEL, node);
	अगर (!pkt_dev)
		वापस -ENOMEM;

	म_नकल(pkt_dev->odevname, अगरname);
	pkt_dev->flows = vzalloc_node(array_size(MAX_CFLOWS,
						 माप(काष्ठा flow_state)),
				      node);
	अगर (pkt_dev->flows == शून्य) अणु
		kमुक्त(pkt_dev);
		वापस -ENOMEM;
	पूर्ण

	pkt_dev->removal_mark = 0;
	pkt_dev->nfrags = 0;
	pkt_dev->delay = pg_delay_d;
	pkt_dev->count = pg_count_d;
	pkt_dev->sofar = 0;
	pkt_dev->udp_src_min = 9;	/* sink port */
	pkt_dev->udp_src_max = 9;
	pkt_dev->udp_dst_min = 9;
	pkt_dev->udp_dst_max = 9;
	pkt_dev->vlan_p = 0;
	pkt_dev->vlan_cfi = 0;
	pkt_dev->vlan_id = 0xffff;
	pkt_dev->svlan_p = 0;
	pkt_dev->svlan_cfi = 0;
	pkt_dev->svlan_id = 0xffff;
	pkt_dev->burst = 1;
	pkt_dev->node = NUMA_NO_NODE;

	err = pktgen_setup_dev(t->net, pkt_dev, अगरname);
	अगर (err)
		जाओ out1;
	अगर (pkt_dev->odev->priv_flags & IFF_TX_SKB_SHARING)
		pkt_dev->clone_skb = pg_clone_skb_d;

	pkt_dev->entry = proc_create_data(अगरname, 0600, t->net->proc_dir,
					  &pktgen_अगर_proc_ops, pkt_dev);
	अगर (!pkt_dev->entry) अणु
		pr_err("cannot create %s/%s procfs entry\n",
		       PG_PROC_सूची, अगरname);
		err = -EINVAL;
		जाओ out2;
	पूर्ण
#अगर_घोषित CONFIG_XFRM
	pkt_dev->ipsmode = XFRM_MODE_TRANSPORT;
	pkt_dev->ipsproto = IPPROTO_ESP;

	/* xfrm tunnel mode needs additional dst to extract outter
	 * ip header protocol/ttl/id field, here creat a phony one.
	 * instead of looking क्रम a valid rt, which definitely hurting
	 * perक्रमmance under such circumstance.
	 */
	pkt_dev->dstops.family = AF_INET;
	pkt_dev->xdst.u.dst.dev = pkt_dev->odev;
	dst_init_metrics(&pkt_dev->xdst.u.dst, pktgen_dst_metrics, false);
	pkt_dev->xdst.child = &pkt_dev->xdst.u.dst;
	pkt_dev->xdst.u.dst.ops = &pkt_dev->dstops;
#पूर्ण_अगर

	वापस add_dev_to_thपढ़ो(t, pkt_dev);
out2:
	dev_put(pkt_dev->odev);
out1:
#अगर_घोषित CONFIG_XFRM
	मुक्त_SAs(pkt_dev);
#पूर्ण_अगर
	vमुक्त(pkt_dev->flows);
	kमुक्त(pkt_dev);
	वापस err;
पूर्ण

अटल पूर्णांक __net_init pktgen_create_thपढ़ो(पूर्णांक cpu, काष्ठा pktgen_net *pn)
अणु
	काष्ठा pktgen_thपढ़ो *t;
	काष्ठा proc_dir_entry *pe;
	काष्ठा task_काष्ठा *p;

	t = kzalloc_node(माप(काष्ठा pktgen_thपढ़ो), GFP_KERNEL,
			 cpu_to_node(cpu));
	अगर (!t) अणु
		pr_err("ERROR: out of memory, can't create new thread\n");
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&t->अगर_lock);
	t->cpu = cpu;

	INIT_LIST_HEAD(&t->अगर_list);

	list_add_tail(&t->th_list, &pn->pktgen_thपढ़ोs);
	init_completion(&t->start_करोne);

	p = kthपढ़ो_create_on_node(pktgen_thपढ़ो_worker,
				   t,
				   cpu_to_node(cpu),
				   "kpktgend_%d", cpu);
	अगर (IS_ERR(p)) अणु
		pr_err("kthread_create_on_node() failed for cpu %d\n", t->cpu);
		list_del(&t->th_list);
		kमुक्त(t);
		वापस PTR_ERR(p);
	पूर्ण
	kthपढ़ो_bind(p, cpu);
	t->tsk = p;

	pe = proc_create_data(t->tsk->comm, 0600, pn->proc_dir,
			      &pktgen_thपढ़ो_proc_ops, t);
	अगर (!pe) अणु
		pr_err("cannot create %s/%s procfs entry\n",
		       PG_PROC_सूची, t->tsk->comm);
		kthपढ़ो_stop(p);
		list_del(&t->th_list);
		kमुक्त(t);
		वापस -EINVAL;
	पूर्ण

	t->net = pn;
	get_task_काष्ठा(p);
	wake_up_process(p);
	रुको_क्रम_completion(&t->start_करोne);

	वापस 0;
पूर्ण

/*
 * Removes a device from the thपढ़ो अगर_list.
 */
अटल व्योम _rem_dev_from_अगर_list(काष्ठा pktgen_thपढ़ो *t,
				  काष्ठा pktgen_dev *pkt_dev)
अणु
	काष्ठा list_head *q, *n;
	काष्ठा pktgen_dev *p;

	अगर_lock(t);
	list_क्रम_each_safe(q, n, &t->अगर_list) अणु
		p = list_entry(q, काष्ठा pktgen_dev, list);
		अगर (p == pkt_dev)
			list_del_rcu(&p->list);
	पूर्ण
	अगर_unlock(t);
पूर्ण

अटल पूर्णांक pktgen_हटाओ_device(काष्ठा pktgen_thपढ़ो *t,
				काष्ठा pktgen_dev *pkt_dev)
अणु
	pr_debug("remove_device pkt_dev=%p\n", pkt_dev);

	अगर (pkt_dev->running) अणु
		pr_warn("WARNING: trying to remove a running interface, stopping it now\n");
		pktgen_stop_device(pkt_dev);
	पूर्ण

	/* Dis-associate from the पूर्णांकerface */

	अगर (pkt_dev->odev) अणु
		dev_put(pkt_dev->odev);
		pkt_dev->odev = शून्य;
	पूर्ण

	/* Remove proc beक्रमe अगर_list entry, because add_device uses
	 * list to determine अगर पूर्णांकerface alपढ़ोy exist, aव्योम race
	 * with proc_create_data() */
	proc_हटाओ(pkt_dev->entry);

	/* And update the thपढ़ो अगर_list */
	_rem_dev_from_अगर_list(t, pkt_dev);

#अगर_घोषित CONFIG_XFRM
	मुक्त_SAs(pkt_dev);
#पूर्ण_अगर
	vमुक्त(pkt_dev->flows);
	अगर (pkt_dev->page)
		put_page(pkt_dev->page);
	kमुक्त_rcu(pkt_dev, rcu);
	वापस 0;
पूर्ण

अटल पूर्णांक __net_init pg_net_init(काष्ठा net *net)
अणु
	काष्ठा pktgen_net *pn = net_generic(net, pg_net_id);
	काष्ठा proc_dir_entry *pe;
	पूर्णांक cpu, ret = 0;

	pn->net = net;
	INIT_LIST_HEAD(&pn->pktgen_thपढ़ोs);
	pn->pktgen_निकासing = false;
	pn->proc_dir = proc_सूची_गढ़ो(PG_PROC_सूची, pn->net->proc_net);
	अगर (!pn->proc_dir) अणु
		pr_warn("cannot create /proc/net/%s\n", PG_PROC_सूची);
		वापस -ENODEV;
	पूर्ण
	pe = proc_create(PGCTRL, 0600, pn->proc_dir, &pktgen_proc_ops);
	अगर (pe == शून्य) अणु
		pr_err("cannot create %s procfs entry\n", PGCTRL);
		ret = -EINVAL;
		जाओ हटाओ;
	पूर्ण

	क्रम_each_online_cpu(cpu) अणु
		पूर्णांक err;

		err = pktgen_create_thपढ़ो(cpu, pn);
		अगर (err)
			pr_warn("Cannot create thread for cpu %d (%d)\n",
				   cpu, err);
	पूर्ण

	अगर (list_empty(&pn->pktgen_thपढ़ोs)) अणु
		pr_err("Initialization failed for all threads\n");
		ret = -ENODEV;
		जाओ हटाओ_entry;
	पूर्ण

	वापस 0;

हटाओ_entry:
	हटाओ_proc_entry(PGCTRL, pn->proc_dir);
हटाओ:
	हटाओ_proc_entry(PG_PROC_सूची, pn->net->proc_net);
	वापस ret;
पूर्ण

अटल व्योम __net_निकास pg_net_निकास(काष्ठा net *net)
अणु
	काष्ठा pktgen_net *pn = net_generic(net, pg_net_id);
	काष्ठा pktgen_thपढ़ो *t;
	काष्ठा list_head *q, *n;
	LIST_HEAD(list);

	/* Stop all पूर्णांकerfaces & thपढ़ोs */
	pn->pktgen_निकासing = true;

	mutex_lock(&pktgen_thपढ़ो_lock);
	list_splice_init(&pn->pktgen_thपढ़ोs, &list);
	mutex_unlock(&pktgen_thपढ़ो_lock);

	list_क्रम_each_safe(q, n, &list) अणु
		t = list_entry(q, काष्ठा pktgen_thपढ़ो, th_list);
		list_del(&t->th_list);
		kthपढ़ो_stop(t->tsk);
		put_task_काष्ठा(t->tsk);
		kमुक्त(t);
	पूर्ण

	हटाओ_proc_entry(PGCTRL, pn->proc_dir);
	हटाओ_proc_entry(PG_PROC_सूची, pn->net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations pg_net_ops = अणु
	.init = pg_net_init,
	.निकास = pg_net_निकास,
	.id   = &pg_net_id,
	.size = माप(काष्ठा pktgen_net),
पूर्ण;

अटल पूर्णांक __init pg_init(व्योम)
अणु
	पूर्णांक ret = 0;

	pr_info("%s", version);
	ret = रेजिस्टर_pernet_subsys(&pg_net_ops);
	अगर (ret)
		वापस ret;
	ret = रेजिस्टर_netdevice_notअगरier(&pktgen_notअगरier_block);
	अगर (ret)
		unरेजिस्टर_pernet_subsys(&pg_net_ops);

	वापस ret;
पूर्ण

अटल व्योम __निकास pg_cleanup(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&pktgen_notअगरier_block);
	unरेजिस्टर_pernet_subsys(&pg_net_ops);
	/* Don't need rcu_barrier() due to use of kमुक्त_rcu() */
पूर्ण

module_init(pg_init);
module_निकास(pg_cleanup);

MODULE_AUTHOR("Robert Olsson <robert.olsson@its.uu.se>");
MODULE_DESCRIPTION("Packet Generator tool");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
module_param(pg_count_d, पूर्णांक, 0);
MODULE_PARM_DESC(pg_count_d, "Default number of packets to inject");
module_param(pg_delay_d, पूर्णांक, 0);
MODULE_PARM_DESC(pg_delay_d, "Default delay between packets (nanoseconds)");
module_param(pg_clone_skb_d, पूर्णांक, 0);
MODULE_PARM_DESC(pg_clone_skb_d, "Default number of copies of the same packet");
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Enable debugging of pktgen module");
