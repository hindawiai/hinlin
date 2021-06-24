<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_DCCP_H
#घोषणा _NF_CONNTRACK_DCCP_H

/* Exposed to userspace over nfnetlink */
क्रमागत ct_dccp_states अणु
	CT_DCCP_NONE,
	CT_DCCP_REQUEST,
	CT_DCCP_RESPOND,
	CT_DCCP_PARTOPEN,
	CT_DCCP_OPEN,
	CT_DCCP_CLOSEREQ,
	CT_DCCP_CLOSING,
	CT_DCCP_TIMEWAIT,
	CT_DCCP_IGNORE,
	CT_DCCP_INVALID,
	__CT_DCCP_MAX
पूर्ण;
#घोषणा CT_DCCP_MAX		(__CT_DCCP_MAX - 1)

क्रमागत ct_dccp_roles अणु
	CT_DCCP_ROLE_CLIENT,
	CT_DCCP_ROLE_SERVER,
	__CT_DCCP_ROLE_MAX
पूर्ण;
#घोषणा CT_DCCP_ROLE_MAX	(__CT_DCCP_ROLE_MAX - 1)

#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>

काष्ठा nf_ct_dccp अणु
	u_पूर्णांक8_t	role[IP_CT_सूची_MAX];
	u_पूर्णांक8_t	state;
	u_पूर्णांक8_t	last_pkt;
	u_पूर्णांक8_t	last_dir;
	u_पूर्णांक64_t	handshake_seq;
पूर्ण;

#पूर्ण_अगर /* _NF_CONNTRACK_DCCP_H */
