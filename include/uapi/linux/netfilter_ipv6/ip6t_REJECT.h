<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IP6T_REJECT_H
#घोषणा _IP6T_REJECT_H

#समावेश <linux/types.h>

क्रमागत ip6t_reject_with अणु
	IP6T_ICMP6_NO_ROUTE,
	IP6T_ICMP6_ADM_PROHIBITED,
	IP6T_ICMP6_NOT_NEIGHBOUR,
	IP6T_ICMP6_ADDR_UNREACH,
	IP6T_ICMP6_PORT_UNREACH,
	IP6T_ICMP6_ECHOREPLY,
	IP6T_TCP_RESET,
	IP6T_ICMP6_POLICY_FAIL,
	IP6T_ICMP6_REJECT_ROUTE
पूर्ण;

काष्ठा ip6t_reject_info अणु
	__u32	with;	/* reject type */
पूर्ण;

#पूर्ण_अगर /*_IP6T_REJECT_H*/
