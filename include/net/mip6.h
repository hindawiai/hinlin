<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C)2003-2006 Helsinki University of Technology
 * Copyright (C)2003-2006 USAGI/WIDE Project
 */
/*
 * Authors:
 *	Noriaki TAKAMIYA @USAGI
 *	Masahide NAKAMURA @USAGI
 *	YOSHIFUJI Hideaki @USAGI
 */
#अगर_अघोषित _NET_MIP6_H
#घोषणा _NET_MIP6_H

#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>

/*
 * Mobility Header
 */
काष्ठा ip6_mh अणु
	__u8	ip6mh_proto;
	__u8	ip6mh_hdrlen;
	__u8	ip6mh_type;
	__u8	ip6mh_reserved;
	__u16	ip6mh_cksum;
	/* Followed by type specअगरic messages */
	__u8	data[];
पूर्ण __packed;

#घोषणा IP6_MH_TYPE_BRR		0   /* Binding Refresh Request */
#घोषणा IP6_MH_TYPE_HOTI	1   /* HOTI Message   */
#घोषणा IP6_MH_TYPE_COTI	2   /* COTI Message  */
#घोषणा IP6_MH_TYPE_HOT		3   /* HOT Message   */
#घोषणा IP6_MH_TYPE_COT		4   /* COT Message  */
#घोषणा IP6_MH_TYPE_BU		5   /* Binding Update */
#घोषणा IP6_MH_TYPE_BACK	6   /* Binding ACK */
#घोषणा IP6_MH_TYPE_BERROR	7   /* Binding Error */
#घोषणा IP6_MH_TYPE_MAX		IP6_MH_TYPE_BERROR

#पूर्ण_अगर
