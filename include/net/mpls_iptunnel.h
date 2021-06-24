<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 Cumulus Networks, Inc.
 */

#अगर_अघोषित _NET_MPLS_IPTUNNEL_H
#घोषणा _NET_MPLS_IPTUNNEL_H 1

काष्ठा mpls_iptunnel_encap अणु
	u8	labels;
	u8	ttl_propagate;
	u8	शेष_ttl;
	u8	reserved1;
	u32	label[];
पूर्ण;

अटल अंतरभूत काष्ठा mpls_iptunnel_encap *mpls_lwtunnel_encap(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस (काष्ठा mpls_iptunnel_encap *)lwtstate->data;
पूर्ण

#पूर्ण_अगर
