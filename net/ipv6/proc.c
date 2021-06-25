<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		This file implements the various access functions क्रम the
 *		PROC file प्रणाली.  This is very similar to the IPv4 version,
 *		except it reports the sockets in the INET6 address family.
 *
 * Authors:	David S. Miller (davem@caip.rutgers.edu)
 *		YOSHIFUJI Hideaki <yoshfuji@linux-ipv6.org>
 */
#समावेश <linux/socket.h>
#समावेश <linux/net.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/ip.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ipv6.h>

#घोषणा MAX4(a, b, c, d) \
	max_t(u32, max_t(u32, a, b), max_t(u32, c, d))
#घोषणा SNMP_MIB_MAX MAX4(UDP_MIB_MAX, TCP_MIB_MAX, \
			IPSTATS_MIB_MAX, ICMP_MIB_MAX)

अटल पूर्णांक sockstat6_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net *net = seq->निजी;

	seq_म_लिखो(seq, "TCP6: inuse %d\n",
		       sock_prot_inuse_get(net, &tcpv6_prot));
	seq_म_लिखो(seq, "UDP6: inuse %d\n",
		       sock_prot_inuse_get(net, &udpv6_prot));
	seq_म_लिखो(seq, "UDPLITE6: inuse %d\n",
			sock_prot_inuse_get(net, &udplitev6_prot));
	seq_म_लिखो(seq, "RAW6: inuse %d\n",
		       sock_prot_inuse_get(net, &rawv6_prot));
	seq_म_लिखो(seq, "FRAG6: inuse %u memory %lu\n",
		   atomic_पढ़ो(&net->ipv6.fqdir->rhashtable.nelems),
		   frag_mem_limit(net->ipv6.fqdir));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snmp_mib snmp6_ipstats_list[] = अणु
/* ipv6 mib according to RFC 2465 */
	SNMP_MIB_ITEM("Ip6InReceives", IPSTATS_MIB_INPKTS),
	SNMP_MIB_ITEM("Ip6InHdrErrors", IPSTATS_MIB_INHDRERRORS),
	SNMP_MIB_ITEM("Ip6InTooBigErrors", IPSTATS_MIB_INTOOBIGERRORS),
	SNMP_MIB_ITEM("Ip6InNoRoutes", IPSTATS_MIB_INNOROUTES),
	SNMP_MIB_ITEM("Ip6InAddrErrors", IPSTATS_MIB_INADDRERRORS),
	SNMP_MIB_ITEM("Ip6InUnknownProtos", IPSTATS_MIB_INUNKNOWNPROTOS),
	SNMP_MIB_ITEM("Ip6InTruncatedPkts", IPSTATS_MIB_INTRUNCATEDPKTS),
	SNMP_MIB_ITEM("Ip6InDiscards", IPSTATS_MIB_INDISCARDS),
	SNMP_MIB_ITEM("Ip6InDelivers", IPSTATS_MIB_INDELIVERS),
	SNMP_MIB_ITEM("Ip6OutForwDatagrams", IPSTATS_MIB_OUTFORWDATAGRAMS),
	SNMP_MIB_ITEM("Ip6OutRequests", IPSTATS_MIB_OUTPKTS),
	SNMP_MIB_ITEM("Ip6OutDiscards", IPSTATS_MIB_OUTDISCARDS),
	SNMP_MIB_ITEM("Ip6OutNoRoutes", IPSTATS_MIB_OUTNOROUTES),
	SNMP_MIB_ITEM("Ip6ReasmTimeout", IPSTATS_MIB_REASMTIMEOUT),
	SNMP_MIB_ITEM("Ip6ReasmReqds", IPSTATS_MIB_REASMREQDS),
	SNMP_MIB_ITEM("Ip6ReasmOKs", IPSTATS_MIB_REASMOKS),
	SNMP_MIB_ITEM("Ip6ReasmFails", IPSTATS_MIB_REASMFAILS),
	SNMP_MIB_ITEM("Ip6FragOKs", IPSTATS_MIB_FRAGOKS),
	SNMP_MIB_ITEM("Ip6FragFails", IPSTATS_MIB_FRAGFAILS),
	SNMP_MIB_ITEM("Ip6FragCreates", IPSTATS_MIB_FRAGCREATES),
	SNMP_MIB_ITEM("Ip6InMcastPkts", IPSTATS_MIB_INMCASTPKTS),
	SNMP_MIB_ITEM("Ip6OutMcastPkts", IPSTATS_MIB_OUTMCASTPKTS),
	SNMP_MIB_ITEM("Ip6InOctets", IPSTATS_MIB_INOCTETS),
	SNMP_MIB_ITEM("Ip6OutOctets", IPSTATS_MIB_OUTOCTETS),
	SNMP_MIB_ITEM("Ip6InMcastOctets", IPSTATS_MIB_INMCASTOCTETS),
	SNMP_MIB_ITEM("Ip6OutMcastOctets", IPSTATS_MIB_OUTMCASTOCTETS),
	SNMP_MIB_ITEM("Ip6InBcastOctets", IPSTATS_MIB_INBCASTOCTETS),
	SNMP_MIB_ITEM("Ip6OutBcastOctets", IPSTATS_MIB_OUTBCASTOCTETS),
	/* IPSTATS_MIB_CSUMERRORS is not relevant in IPv6 (no checksum) */
	SNMP_MIB_ITEM("Ip6InNoECTPkts", IPSTATS_MIB_NOECTPKTS),
	SNMP_MIB_ITEM("Ip6InECT1Pkts", IPSTATS_MIB_ECT1PKTS),
	SNMP_MIB_ITEM("Ip6InECT0Pkts", IPSTATS_MIB_ECT0PKTS),
	SNMP_MIB_ITEM("Ip6InCEPkts", IPSTATS_MIB_CEPKTS),
	SNMP_MIB_SENTINEL
पूर्ण;

अटल स्थिर काष्ठा snmp_mib snmp6_icmp6_list[] = अणु
/* icmpv6 mib according to RFC 2466 */
	SNMP_MIB_ITEM("Icmp6InMsgs", ICMP6_MIB_INMSGS),
	SNMP_MIB_ITEM("Icmp6InErrors", ICMP6_MIB_INERRORS),
	SNMP_MIB_ITEM("Icmp6OutMsgs", ICMP6_MIB_OUTMSGS),
	SNMP_MIB_ITEM("Icmp6OutErrors", ICMP6_MIB_OUTERRORS),
	SNMP_MIB_ITEM("Icmp6InCsumErrors", ICMP6_MIB_CSUMERRORS),
	SNMP_MIB_SENTINEL
पूर्ण;

/* RFC 4293 v6 ICMPMsgStatsTable; named items क्रम RFC 2466 compatibility */
अटल स्थिर अक्षर *स्थिर icmp6type2name[256] = अणु
	[ICMPV6_DEST_UNREACH] = "DestUnreachs",
	[ICMPV6_PKT_TOOBIG] = "PktTooBigs",
	[ICMPV6_TIME_EXCEED] = "TimeExcds",
	[ICMPV6_PARAMPROB] = "ParmProblems",
	[ICMPV6_ECHO_REQUEST] = "Echos",
	[ICMPV6_ECHO_REPLY] = "EchoReplies",
	[ICMPV6_MGM_QUERY] = "GroupMembQueries",
	[ICMPV6_MGM_REPORT] = "GroupMembResponses",
	[ICMPV6_MGM_REDUCTION] = "GroupMembReductions",
	[ICMPV6_MLD2_REPORT] = "MLDv2Reports",
	[NDISC_ROUTER_ADVERTISEMENT] = "RouterAdvertisements",
	[NDISC_ROUTER_SOLICITATION] = "RouterSolicits",
	[NDISC_NEIGHBOUR_ADVERTISEMENT] = "NeighborAdvertisements",
	[NDISC_NEIGHBOUR_SOLICITATION] = "NeighborSolicits",
	[NDISC_REसूचीECT] = "Redirects",
पूर्ण;


अटल स्थिर काष्ठा snmp_mib snmp6_udp6_list[] = अणु
	SNMP_MIB_ITEM("Udp6InDatagrams", UDP_MIB_INDATAGRAMS),
	SNMP_MIB_ITEM("Udp6NoPorts", UDP_MIB_NOPORTS),
	SNMP_MIB_ITEM("Udp6InErrors", UDP_MIB_INERRORS),
	SNMP_MIB_ITEM("Udp6OutDatagrams", UDP_MIB_OUTDATAGRAMS),
	SNMP_MIB_ITEM("Udp6RcvbufErrors", UDP_MIB_RCVBUFERRORS),
	SNMP_MIB_ITEM("Udp6SndbufErrors", UDP_MIB_SNDBUFERRORS),
	SNMP_MIB_ITEM("Udp6InCsumErrors", UDP_MIB_CSUMERRORS),
	SNMP_MIB_ITEM("Udp6IgnoredMulti", UDP_MIB_IGNOREDMULTI),
	SNMP_MIB_ITEM("Udp6MemErrors", UDP_MIB_MEMERRORS),
	SNMP_MIB_SENTINEL
पूर्ण;

अटल स्थिर काष्ठा snmp_mib snmp6_udplite6_list[] = अणु
	SNMP_MIB_ITEM("UdpLite6InDatagrams", UDP_MIB_INDATAGRAMS),
	SNMP_MIB_ITEM("UdpLite6NoPorts", UDP_MIB_NOPORTS),
	SNMP_MIB_ITEM("UdpLite6InErrors", UDP_MIB_INERRORS),
	SNMP_MIB_ITEM("UdpLite6OutDatagrams", UDP_MIB_OUTDATAGRAMS),
	SNMP_MIB_ITEM("UdpLite6RcvbufErrors", UDP_MIB_RCVBUFERRORS),
	SNMP_MIB_ITEM("UdpLite6SndbufErrors", UDP_MIB_SNDBUFERRORS),
	SNMP_MIB_ITEM("UdpLite6InCsumErrors", UDP_MIB_CSUMERRORS),
	SNMP_MIB_ITEM("UdpLite6MemErrors", UDP_MIB_MEMERRORS),
	SNMP_MIB_SENTINEL
पूर्ण;

अटल व्योम snmp6_seq_show_icmpv6msg(काष्ठा seq_file *seq, atomic_दीर्घ_t *smib)
अणु
	अक्षर name[32];
	पूर्णांक i;

	/* prपूर्णांक by name -- deprecated items */
	क्रम (i = 0; i < ICMP6MSG_MIB_MAX; i++) अणु
		पूर्णांक icmptype;
		स्थिर अक्षर *p;

		icmptype = i & 0xff;
		p = icmp6type2name[icmptype];
		अगर (!p)	/* करोn't prपूर्णांक un-named types here */
			जारी;
		snम_लिखो(name, माप(name), "Icmp6%s%s",
			i & 0x100 ? "Out" : "In", p);
		seq_म_लिखो(seq, "%-32s\t%lu\n", name,
			   atomic_दीर्घ_पढ़ो(smib + i));
	पूर्ण

	/* prपूर्णांक by number (nonzero only) - ICMPMsgStat क्रमmat */
	क्रम (i = 0; i < ICMP6MSG_MIB_MAX; i++) अणु
		अचिन्हित दीर्घ val;

		val = atomic_दीर्घ_पढ़ो(smib + i);
		अगर (!val)
			जारी;
		snम_लिखो(name, माप(name), "Icmp6%sType%u",
			i & 0x100 ?  "Out" : "In", i & 0xff);
		seq_म_लिखो(seq, "%-32s\t%lu\n", name, val);
	पूर्ण
पूर्ण

/* can be called either with percpu mib (pcpumib != शून्य),
 * or shared one (smib != शून्य)
 */
अटल व्योम snmp6_seq_show_item(काष्ठा seq_file *seq, व्योम __percpu *pcpumib,
				atomic_दीर्घ_t *smib,
				स्थिर काष्ठा snmp_mib *itemlist)
अणु
	अचिन्हित दीर्घ buff[SNMP_MIB_MAX];
	पूर्णांक i;

	अगर (pcpumib) अणु
		स_रखो(buff, 0, माप(अचिन्हित दीर्घ) * SNMP_MIB_MAX);

		snmp_get_cpu_field_batch(buff, itemlist, pcpumib);
		क्रम (i = 0; itemlist[i].name; i++)
			seq_म_लिखो(seq, "%-32s\t%lu\n",
				   itemlist[i].name, buff[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; itemlist[i].name; i++)
			seq_म_लिखो(seq, "%-32s\t%lu\n", itemlist[i].name,
				   atomic_दीर्घ_पढ़ो(smib + itemlist[i].entry));
	पूर्ण
पूर्ण

अटल व्योम snmp6_seq_show_item64(काष्ठा seq_file *seq, व्योम __percpu *mib,
				  स्थिर काष्ठा snmp_mib *itemlist, माप_प्रकार syncpoff)
अणु
	u64 buff64[SNMP_MIB_MAX];
	पूर्णांक i;

	स_रखो(buff64, 0, माप(u64) * SNMP_MIB_MAX);

	snmp_get_cpu_field64_batch(buff64, itemlist, mib, syncpoff);
	क्रम (i = 0; itemlist[i].name; i++)
		seq_म_लिखो(seq, "%-32s\t%llu\n", itemlist[i].name, buff64[i]);
पूर्ण

अटल पूर्णांक snmp6_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net *net = (काष्ठा net *)seq->निजी;

	snmp6_seq_show_item64(seq, net->mib.ipv6_statistics,
			    snmp6_ipstats_list, दुरत्व(काष्ठा ipstats_mib, syncp));
	snmp6_seq_show_item(seq, net->mib.icmpv6_statistics,
			    शून्य, snmp6_icmp6_list);
	snmp6_seq_show_icmpv6msg(seq, net->mib.icmpv6msg_statistics->mibs);
	snmp6_seq_show_item(seq, net->mib.udp_stats_in6,
			    शून्य, snmp6_udp6_list);
	snmp6_seq_show_item(seq, net->mib.udplite_stats_in6,
			    शून्य, snmp6_udplite6_list);
	वापस 0;
पूर्ण

अटल पूर्णांक snmp6_dev_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा inet6_dev *idev = (काष्ठा inet6_dev *)seq->निजी;

	seq_म_लिखो(seq, "%-32s\t%u\n", "ifIndex", idev->dev->अगरindex);
	snmp6_seq_show_item64(seq, idev->stats.ipv6,
			    snmp6_ipstats_list, दुरत्व(काष्ठा ipstats_mib, syncp));
	snmp6_seq_show_item(seq, शून्य, idev->stats.icmpv6dev->mibs,
			    snmp6_icmp6_list);
	snmp6_seq_show_icmpv6msg(seq, idev->stats.icmpv6msgdev->mibs);
	वापस 0;
पूर्ण

पूर्णांक snmp6_रेजिस्टर_dev(काष्ठा inet6_dev *idev)
अणु
	काष्ठा proc_dir_entry *p;
	काष्ठा net *net;

	अगर (!idev || !idev->dev)
		वापस -EINVAL;

	net = dev_net(idev->dev);
	अगर (!net->mib.proc_net_devsnmp6)
		वापस -ENOENT;

	p = proc_create_single_data(idev->dev->name, 0444,
			net->mib.proc_net_devsnmp6, snmp6_dev_seq_show, idev);
	अगर (!p)
		वापस -ENOMEM;

	idev->stats.proc_dir_entry = p;
	वापस 0;
पूर्ण

पूर्णांक snmp6_unरेजिस्टर_dev(काष्ठा inet6_dev *idev)
अणु
	काष्ठा net *net = dev_net(idev->dev);
	अगर (!net->mib.proc_net_devsnmp6)
		वापस -ENOENT;
	अगर (!idev->stats.proc_dir_entry)
		वापस -EINVAL;
	proc_हटाओ(idev->stats.proc_dir_entry);
	idev->stats.proc_dir_entry = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक __net_init ipv6_proc_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net_single("sockstat6", 0444, net->proc_net,
			sockstat6_seq_show, शून्य))
		वापस -ENOMEM;

	अगर (!proc_create_net_single("snmp6", 0444, net->proc_net,
			snmp6_seq_show, शून्य))
		जाओ proc_snmp6_fail;

	net->mib.proc_net_devsnmp6 = proc_सूची_गढ़ो("dev_snmp6", net->proc_net);
	अगर (!net->mib.proc_net_devsnmp6)
		जाओ proc_dev_snmp6_fail;
	वापस 0;

proc_dev_snmp6_fail:
	हटाओ_proc_entry("snmp6", net->proc_net);
proc_snmp6_fail:
	हटाओ_proc_entry("sockstat6", net->proc_net);
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास ipv6_proc_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("sockstat6", net->proc_net);
	हटाओ_proc_entry("dev_snmp6", net->proc_net);
	हटाओ_proc_entry("snmp6", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations ipv6_proc_ops = अणु
	.init = ipv6_proc_init_net,
	.निकास = ipv6_proc_निकास_net,
पूर्ण;

पूर्णांक __init ipv6_misc_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&ipv6_proc_ops);
पूर्ण

व्योम ipv6_misc_proc_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ipv6_proc_ops);
पूर्ण
