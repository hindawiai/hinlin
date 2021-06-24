<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* Copyright (C) 2019 Netronome Systems, Inc. */

#अगर_अघोषित __LINUX_TC_MPLS_H
#घोषणा __LINUX_TC_MPLS_H

#समावेश <linux/pkt_cls.h>

#घोषणा TCA_MPLS_ACT_POP	1
#घोषणा TCA_MPLS_ACT_PUSH	2
#घोषणा TCA_MPLS_ACT_MODIFY	3
#घोषणा TCA_MPLS_ACT_DEC_TTL	4
#घोषणा TCA_MPLS_ACT_MAC_PUSH	5

काष्ठा tc_mpls अणु
	tc_gen;		/* generic TC action fields. */
	पूर्णांक m_action;	/* action of type TCA_MPLS_ACT_*. */
पूर्ण;

क्रमागत अणु
	TCA_MPLS_UNSPEC,
	TCA_MPLS_TM,	/* काष्ठा tcf_t; समय values associated with action. */
	TCA_MPLS_PARMS,	/* काष्ठा tc_mpls; action type and general TC fields. */
	TCA_MPLS_PAD,
	TCA_MPLS_PROTO,	/* be16; eth_type of pushed or next (क्रम pop) header. */
	TCA_MPLS_LABEL,	/* u32; MPLS label. Lower 20 bits are used. */
	TCA_MPLS_TC,	/* u8; MPLS TC field. Lower 3 bits are used. */
	TCA_MPLS_TTL,	/* u8; MPLS TTL field. Must not be 0. */
	TCA_MPLS_BOS,	/* u8; MPLS BOS field. Either 1 or 0. */
	__TCA_MPLS_MAX,
पूर्ण;
#घोषणा TCA_MPLS_MAX (__TCA_MPLS_MAX - 1)

#पूर्ण_अगर
