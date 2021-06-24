<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_SET_H
#घोषणा _XT_SET_H

#समावेश <linux/types.h>
#समावेश <linux/netfilter/ipset/ip_set.h>

/* Revision 0 पूर्णांकerface: backward compatible with netfilter/iptables */

/*
 * Option flags क्रम kernel operations (xt_set_info_v0)
 */
#घोषणा IPSET_SRC		0x01	/* Source match/add */
#घोषणा IPSET_DST		0x02	/* Destination match/add */
#घोषणा IPSET_MATCH_INV		0x04	/* Inverse matching */

काष्ठा xt_set_info_v0 अणु
	ip_set_id_t index;
	जोड़ अणु
		__u32 flags[IPSET_DIM_MAX + 1];
		काष्ठा अणु
			__u32 __flags[IPSET_DIM_MAX];
			__u8 dim;
			__u8 flags;
		पूर्ण compat;
	पूर्ण u;
पूर्ण;

/* match and target infos */
काष्ठा xt_set_info_match_v0 अणु
	काष्ठा xt_set_info_v0 match_set;
पूर्ण;

काष्ठा xt_set_info_target_v0 अणु
	काष्ठा xt_set_info_v0 add_set;
	काष्ठा xt_set_info_v0 del_set;
पूर्ण;

/* Revision 1  match and target */

काष्ठा xt_set_info अणु
	ip_set_id_t index;
	__u8 dim;
	__u8 flags;
पूर्ण;

/* match and target infos */
काष्ठा xt_set_info_match_v1 अणु
	काष्ठा xt_set_info match_set;
पूर्ण;

काष्ठा xt_set_info_target_v1 अणु
	काष्ठा xt_set_info add_set;
	काष्ठा xt_set_info del_set;
पूर्ण;

/* Revision 2 target */

काष्ठा xt_set_info_target_v2 अणु
	काष्ठा xt_set_info add_set;
	काष्ठा xt_set_info del_set;
	__u32 flags;
	__u32 समयout;
पूर्ण;

/* Revision 3 match */

काष्ठा xt_set_info_match_v3 अणु
	काष्ठा xt_set_info match_set;
	काष्ठा ip_set_counter_match0 packets;
	काष्ठा ip_set_counter_match0 bytes;
	__u32 flags;
पूर्ण;

/* Revision 3 target */

काष्ठा xt_set_info_target_v3 अणु
	काष्ठा xt_set_info add_set;
	काष्ठा xt_set_info del_set;
	काष्ठा xt_set_info map_set;
	__u32 flags;
	__u32 समयout;
पूर्ण;

/* Revision 4 match */

काष्ठा xt_set_info_match_v4 अणु
	काष्ठा xt_set_info match_set;
	काष्ठा ip_set_counter_match packets;
	काष्ठा ip_set_counter_match bytes;
	__u32 flags;
पूर्ण;

#पूर्ण_अगर /*_XT_SET_H*/
