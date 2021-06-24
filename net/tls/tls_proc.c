<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Netronome Systems, Inc. */

#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <net/snmp.h>
#समावेश <net/tls.h>

#अगर_घोषित CONFIG_PROC_FS
अटल स्थिर काष्ठा snmp_mib tls_mib_list[] = अणु
	SNMP_MIB_ITEM("TlsCurrTxSw", LINUX_MIB_TLSCURRTXSW),
	SNMP_MIB_ITEM("TlsCurrRxSw", LINUX_MIB_TLSCURRRXSW),
	SNMP_MIB_ITEM("TlsCurrTxDevice", LINUX_MIB_TLSCURRTXDEVICE),
	SNMP_MIB_ITEM("TlsCurrRxDevice", LINUX_MIB_TLSCURRRXDEVICE),
	SNMP_MIB_ITEM("TlsTxSw", LINUX_MIB_TLSTXSW),
	SNMP_MIB_ITEM("TlsRxSw", LINUX_MIB_TLSRXSW),
	SNMP_MIB_ITEM("TlsTxDevice", LINUX_MIB_TLSTXDEVICE),
	SNMP_MIB_ITEM("TlsRxDevice", LINUX_MIB_TLSRXDEVICE),
	SNMP_MIB_ITEM("TlsDecryptError", LINUX_MIB_TLSDECRYPTERROR),
	SNMP_MIB_ITEM("TlsRxDeviceResync", LINUX_MIB_TLSRXDEVICERESYNC),
	SNMP_MIB_SENTINEL
पूर्ण;

अटल पूर्णांक tls_statistics_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अचिन्हित दीर्घ buf[LINUX_MIB_TLSMAX] = अणुपूर्ण;
	काष्ठा net *net = seq->निजी;
	पूर्णांक i;

	snmp_get_cpu_field_batch(buf, tls_mib_list, net->mib.tls_statistics);
	क्रम (i = 0; tls_mib_list[i].name; i++)
		seq_म_लिखो(seq, "%-32s\t%lu\n", tls_mib_list[i].name, buf[i]);

	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक __net_init tls_proc_init(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_net_single("tls_stat", 0444, net->proc_net,
				    tls_statistics_seq_show, शून्य))
		वापस -ENOMEM;
#पूर्ण_अगर /* CONFIG_PROC_FS */

	वापस 0;
पूर्ण

व्योम __net_निकास tls_proc_fini(काष्ठा net *net)
अणु
	हटाओ_proc_entry("tls_stat", net->proc_net);
पूर्ण
