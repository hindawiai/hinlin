<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_ZONES_COMMON_H
#घोषणा _NF_CONNTRACK_ZONES_COMMON_H

#समावेश <uapi/linux/netfilter/nf_conntrack_tuple_common.h>

#घोषणा NF_CT_DEFAULT_ZONE_ID	0

#घोषणा NF_CT_ZONE_सूची_ORIG	(1 << IP_CT_सूची_ORIGINAL)
#घोषणा NF_CT_ZONE_सूची_REPL	(1 << IP_CT_सूची_REPLY)

#घोषणा NF_CT_DEFAULT_ZONE_सूची	(NF_CT_ZONE_सूची_ORIG | NF_CT_ZONE_सूची_REPL)

#घोषणा NF_CT_FLAG_MARK		1

काष्ठा nf_conntrack_zone अणु
	u16	id;
	u8	flags;
	u8	dir;
पूर्ण;

बाह्य स्थिर काष्ठा nf_conntrack_zone nf_ct_zone_dflt;

#पूर्ण_अगर /* _NF_CONNTRACK_ZONES_COMMON_H */
