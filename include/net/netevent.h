<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_EVENT_H
#घोषणा _NET_EVENT_H

/*
 *	Generic netevent notअगरiers
 *
 *	Authors:
 *      Tom Tucker              <tom@खोलोgridcomputing.com>
 *      Steve Wise              <swise@खोलोgridcomputing.com>
 *
 * 	Changes:
 */

काष्ठा dst_entry;
काष्ठा neighbour;

काष्ठा netevent_redirect अणु
	काष्ठा dst_entry *old;
	काष्ठा dst_entry *new;
	काष्ठा neighbour *neigh;
	स्थिर व्योम *daddr;
पूर्ण;

क्रमागत netevent_notअगर_type अणु
	NETEVENT_NEIGH_UPDATE = 1, /* arg is काष्ठा neighbour ptr */
	NETEVENT_REसूचीECT,	   /* arg is काष्ठा netevent_redirect ptr */
	NETEVENT_DELAY_PROBE_TIME_UPDATE, /* arg is काष्ठा neigh_parms ptr */
	NETEVENT_IPV4_MPATH_HASH_UPDATE, /* arg is काष्ठा net ptr */
	NETEVENT_IPV6_MPATH_HASH_UPDATE, /* arg is काष्ठा net ptr */
	NETEVENT_IPV4_FWD_UPDATE_PRIORITY_UPDATE, /* arg is काष्ठा net ptr */
पूर्ण;

पूर्णांक रेजिस्टर_netevent_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_netevent_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक call_netevent_notअगरiers(अचिन्हित दीर्घ val, व्योम *v);

#पूर्ण_अगर
