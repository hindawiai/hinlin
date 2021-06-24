<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IPT_REJECT_H
#घोषणा _IPT_REJECT_H

क्रमागत ipt_reject_with अणु
	IPT_ICMP_NET_UNREACHABLE,
	IPT_ICMP_HOST_UNREACHABLE,
	IPT_ICMP_PROT_UNREACHABLE,
	IPT_ICMP_PORT_UNREACHABLE,
	IPT_ICMP_ECHOREPLY,
	IPT_ICMP_NET_PROHIBITED,
	IPT_ICMP_HOST_PROHIBITED,
	IPT_TCP_RESET,
	IPT_ICMP_ADMIN_PROHIBITED
पूर्ण;

काष्ठा ipt_reject_info अणु
	क्रमागत ipt_reject_with with;      /* reject type */
पूर्ण;

#पूर्ण_अगर /*_IPT_REJECT_H*/
