<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/seq_file.h>
#समावेश <net/ip.h>
#समावेश <net/mptcp.h>
#समावेश <net/snmp.h>
#समावेश <net/net_namespace.h>

#समावेश "mib.h"

अटल स्थिर काष्ठा snmp_mib mptcp_snmp_list[] = अणु
	SNMP_MIB_ITEM("MPCapableSYNRX", MPTCP_MIB_MPCAPABLEPASSIVE),
	SNMP_MIB_ITEM("MPCapableSYNTX", MPTCP_MIB_MPCAPABLEACTIVE),
	SNMP_MIB_ITEM("MPCapableSYNACKRX", MPTCP_MIB_MPCAPABLEACTIVEACK),
	SNMP_MIB_ITEM("MPCapableACKRX", MPTCP_MIB_MPCAPABLEPASSIVEACK),
	SNMP_MIB_ITEM("MPCapableFallbackACK", MPTCP_MIB_MPCAPABLEPASSIVEFALLBACK),
	SNMP_MIB_ITEM("MPCapableFallbackSYNACK", MPTCP_MIB_MPCAPABLEACTIVEFALLBACK),
	SNMP_MIB_ITEM("MPFallbackTokenInit", MPTCP_MIB_TOKENFALLBACKINIT),
	SNMP_MIB_ITEM("MPTCPRetrans", MPTCP_MIB_RETRANSSEGS),
	SNMP_MIB_ITEM("MPJoinNoTokenFound", MPTCP_MIB_JOINNOTOKEN),
	SNMP_MIB_ITEM("MPJoinSynRx", MPTCP_MIB_JOINSYNRX),
	SNMP_MIB_ITEM("MPJoinSynAckRx", MPTCP_MIB_JOINSYNACKRX),
	SNMP_MIB_ITEM("MPJoinSynAckHMacFailure", MPTCP_MIB_JOINSYNACKMAC),
	SNMP_MIB_ITEM("MPJoinAckRx", MPTCP_MIB_JOINACKRX),
	SNMP_MIB_ITEM("MPJoinAckHMacFailure", MPTCP_MIB_JOINACKMAC),
	SNMP_MIB_ITEM("DSSNotMatching", MPTCP_MIB_DSSNOMATCH),
	SNMP_MIB_ITEM("InfiniteMapRx", MPTCP_MIB_INFINITEMAPRX),
	SNMP_MIB_ITEM("OFOQueueTail", MPTCP_MIB_OFOQUEUETAIL),
	SNMP_MIB_ITEM("OFOQueue", MPTCP_MIB_OFOQUEUE),
	SNMP_MIB_ITEM("OFOMerge", MPTCP_MIB_OFOMERGE),
	SNMP_MIB_ITEM("NoDSSInWindow", MPTCP_MIB_NODSSWINDOW),
	SNMP_MIB_ITEM("DuplicateData", MPTCP_MIB_DUPDATA),
	SNMP_MIB_ITEM("AddAddr", MPTCP_MIB_ADDADDR),
	SNMP_MIB_ITEM("EchoAdd", MPTCP_MIB_ECHOADD),
	SNMP_MIB_ITEM("PortAdd", MPTCP_MIB_PORTADD),
	SNMP_MIB_ITEM("MPJoinPortSynRx", MPTCP_MIB_JOINPORTSYNRX),
	SNMP_MIB_ITEM("MPJoinPortSynAckRx", MPTCP_MIB_JOINPORTSYNACKRX),
	SNMP_MIB_ITEM("MPJoinPortAckRx", MPTCP_MIB_JOINPORTACKRX),
	SNMP_MIB_ITEM("MismatchPortSynRx", MPTCP_MIB_MISMATCHPORTSYNRX),
	SNMP_MIB_ITEM("MismatchPortAckRx", MPTCP_MIB_MISMATCHPORTACKRX),
	SNMP_MIB_ITEM("RmAddr", MPTCP_MIB_RMADDR),
	SNMP_MIB_ITEM("RmSubflow", MPTCP_MIB_RMSUBFLOW),
	SNMP_MIB_ITEM("MPPrioTx", MPTCP_MIB_MPPRIOTX),
	SNMP_MIB_ITEM("MPPrioRx", MPTCP_MIB_MPPRIORX),
	SNMP_MIB_SENTINEL
पूर्ण;

/* mptcp_mib_alloc - allocate percpu mib counters
 *
 * These are allocated when the first mptcp socket is created so
 * we करो not waste percpu memory अगर mptcp isn't in use.
 */
bool mptcp_mib_alloc(काष्ठा net *net)
अणु
	काष्ठा mptcp_mib __percpu *mib = alloc_percpu(काष्ठा mptcp_mib);

	अगर (!mib)
		वापस false;

	अगर (cmpxchg(&net->mib.mptcp_statistics, शून्य, mib))
		मुक्त_percpu(mib);

	वापस true;
पूर्ण

व्योम mptcp_seq_show(काष्ठा seq_file *seq)
अणु
	काष्ठा net *net = seq->निजी;
	पूर्णांक i;

	seq_माला_दो(seq, "MPTcpExt:");
	क्रम (i = 0; mptcp_snmp_list[i].name; i++)
		seq_म_लिखो(seq, " %s", mptcp_snmp_list[i].name);

	seq_माला_दो(seq, "\nMPTcpExt:");

	अगर (!net->mib.mptcp_statistics) अणु
		क्रम (i = 0; mptcp_snmp_list[i].name; i++)
			seq_माला_दो(seq, " 0");

		seq_अ_दो(seq, '\n');
		वापस;
	पूर्ण

	क्रम (i = 0; mptcp_snmp_list[i].name; i++)
		seq_म_लिखो(seq, " %lu",
			   snmp_fold_field(net->mib.mptcp_statistics,
					   mptcp_snmp_list[i].entry));
	seq_अ_दो(seq, '\n');
पूर्ण
