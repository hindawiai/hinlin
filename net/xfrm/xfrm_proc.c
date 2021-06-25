<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * xfrm_proc.c
 *
 * Copyright (C)2006-2007 USAGI/WIDE Project
 *
 * Authors:	Masahide NAKAMURA <nakam@linux-ipv6.org>
 */
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>
#समावेश <net/snmp.h>
#समावेश <net/xfrm.h>

अटल स्थिर काष्ठा snmp_mib xfrm_mib_list[] = अणु
	SNMP_MIB_ITEM("XfrmInError", LINUX_MIB_XFRMINERROR),
	SNMP_MIB_ITEM("XfrmInBufferError", LINUX_MIB_XFRMINBUFFERERROR),
	SNMP_MIB_ITEM("XfrmInHdrError", LINUX_MIB_XFRMINHDRERROR),
	SNMP_MIB_ITEM("XfrmInNoStates", LINUX_MIB_XFRMINNOSTATES),
	SNMP_MIB_ITEM("XfrmInStateProtoError", LINUX_MIB_XFRMINSTATEPROTOERROR),
	SNMP_MIB_ITEM("XfrmInStateModeError", LINUX_MIB_XFRMINSTATEMODEERROR),
	SNMP_MIB_ITEM("XfrmInStateSeqError", LINUX_MIB_XFRMINSTATESEQERROR),
	SNMP_MIB_ITEM("XfrmInStateExpired", LINUX_MIB_XFRMINSTATEEXPIRED),
	SNMP_MIB_ITEM("XfrmInStateMismatch", LINUX_MIB_XFRMINSTATEMISMATCH),
	SNMP_MIB_ITEM("XfrmInStateInvalid", LINUX_MIB_XFRMINSTATEINVALID),
	SNMP_MIB_ITEM("XfrmInTmplMismatch", LINUX_MIB_XFRMINTMPLMISMATCH),
	SNMP_MIB_ITEM("XfrmInNoPols", LINUX_MIB_XFRMINNOPOLS),
	SNMP_MIB_ITEM("XfrmInPolBlock", LINUX_MIB_XFRMINPOLBLOCK),
	SNMP_MIB_ITEM("XfrmInPolError", LINUX_MIB_XFRMINPOLERROR),
	SNMP_MIB_ITEM("XfrmOutError", LINUX_MIB_XFRMOUTERROR),
	SNMP_MIB_ITEM("XfrmOutBundleGenError", LINUX_MIB_XFRMOUTBUNDLEGENERROR),
	SNMP_MIB_ITEM("XfrmOutBundleCheckError", LINUX_MIB_XFRMOUTBUNDLECHECKERROR),
	SNMP_MIB_ITEM("XfrmOutNoStates", LINUX_MIB_XFRMOUTNOSTATES),
	SNMP_MIB_ITEM("XfrmOutStateProtoError", LINUX_MIB_XFRMOUTSTATEPROTOERROR),
	SNMP_MIB_ITEM("XfrmOutStateModeError", LINUX_MIB_XFRMOUTSTATEMODEERROR),
	SNMP_MIB_ITEM("XfrmOutStateSeqError", LINUX_MIB_XFRMOUTSTATESEQERROR),
	SNMP_MIB_ITEM("XfrmOutStateExpired", LINUX_MIB_XFRMOUTSTATEEXPIRED),
	SNMP_MIB_ITEM("XfrmOutPolBlock", LINUX_MIB_XFRMOUTPOLBLOCK),
	SNMP_MIB_ITEM("XfrmOutPolDead", LINUX_MIB_XFRMOUTPOLDEAD),
	SNMP_MIB_ITEM("XfrmOutPolError", LINUX_MIB_XFRMOUTPOLERROR),
	SNMP_MIB_ITEM("XfrmFwdHdrError", LINUX_MIB_XFRMFWDHDRERROR),
	SNMP_MIB_ITEM("XfrmOutStateInvalid", LINUX_MIB_XFRMOUTSTATEINVALID),
	SNMP_MIB_ITEM("XfrmAcquireError", LINUX_MIB_XFRMACQUIREERROR),
	SNMP_MIB_SENTINEL
पूर्ण;

अटल पूर्णांक xfrm_statistics_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अचिन्हित दीर्घ buff[LINUX_MIB_XFRMMAX];
	काष्ठा net *net = seq->निजी;
	पूर्णांक i;

	स_रखो(buff, 0, माप(अचिन्हित दीर्घ) * LINUX_MIB_XFRMMAX);

	snmp_get_cpu_field_batch(buff, xfrm_mib_list,
				 net->mib.xfrm_statistics);
	क्रम (i = 0; xfrm_mib_list[i].name; i++)
		seq_म_लिखो(seq, "%-24s\t%lu\n", xfrm_mib_list[i].name,
						buff[i]);

	वापस 0;
पूर्ण

पूर्णांक __net_init xfrm_proc_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net_single("xfrm_stat", 0444, net->proc_net,
			 xfrm_statistics_seq_show, शून्य))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम xfrm_proc_fini(काष्ठा net *net)
अणु
	हटाओ_proc_entry("xfrm_stat", net->proc_net);
पूर्ण
