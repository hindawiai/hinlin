<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2019 Chelsio Communications.  All rights reserved. */

#अगर_अघोषित __CXGB4_TC_MATCHALL_H__
#घोषणा __CXGB4_TC_MATCHALL_H__

#समावेश <net/pkt_cls.h>

क्रमागत cxgb4_matchall_state अणु
	CXGB4_MATCHALL_STATE_DISABLED = 0,
	CXGB4_MATCHALL_STATE_ENABLED,
पूर्ण;

काष्ठा cxgb4_matchall_egress_entry अणु
	क्रमागत cxgb4_matchall_state state; /* Current MATCHALL offload state */
	u8 hwtc; /* Traffic class bound to port */
	u64 cookie; /* Used to identअगरy the MATCHALL rule offloaded */
पूर्ण;

काष्ठा cxgb4_matchall_ingress_entry अणु
	क्रमागत cxgb4_matchall_state state; /* Current MATCHALL offload state */
	u32 tid[CXGB4_FILTER_TYPE_MAX]; /* Index to hardware filter entries */
	/* Filter entries */
	काष्ठा ch_filter_specअगरication fs[CXGB4_FILTER_TYPE_MAX];
	u16 viid_mirror; /* Identअगरier क्रम allocated Mirror VI */
	u64 bytes; /* # of bytes hitting the filter */
	u64 packets; /* # of packets hitting the filter */
	u64 last_used; /* Last updated jअगरfies समय */
पूर्ण;

काष्ठा cxgb4_tc_port_matchall अणु
	काष्ठा cxgb4_matchall_egress_entry egress; /* Egress offload info */
	काष्ठा cxgb4_matchall_ingress_entry ingress; /* Ingress offload info */
पूर्ण;

काष्ठा cxgb4_tc_matchall अणु
	काष्ठा cxgb4_tc_port_matchall *port_matchall; /* Per port entry */
पूर्ण;

पूर्णांक cxgb4_tc_matchall_replace(काष्ठा net_device *dev,
			      काष्ठा tc_cls_matchall_offload *cls_matchall,
			      bool ingress);
पूर्णांक cxgb4_tc_matchall_destroy(काष्ठा net_device *dev,
			      काष्ठा tc_cls_matchall_offload *cls_matchall,
			      bool ingress);
पूर्णांक cxgb4_tc_matchall_stats(काष्ठा net_device *dev,
			    काष्ठा tc_cls_matchall_offload *cls_matchall);

पूर्णांक cxgb4_init_tc_matchall(काष्ठा adapter *adap);
व्योम cxgb4_cleanup_tc_matchall(काष्ठा adapter *adap);
#पूर्ण_अगर /* __CXGB4_TC_MATCHALL_H__ */
