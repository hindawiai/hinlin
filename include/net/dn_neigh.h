<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_DN_NEIGH_H
#घोषणा _NET_DN_NEIGH_H

/*
 * The position of the first two fields of
 * this काष्ठाure are critical - SJW
 */
काष्ठा dn_neigh अणु
        काष्ठा neighbour n;
	__le16 addr;
        अचिन्हित दीर्घ flags;
#घोषणा DN_NDFLAG_R1    0x0001 /* Router L1      */
#घोषणा DN_NDFLAG_R2    0x0002 /* Router L2      */
#घोषणा DN_NDFLAG_P3    0x0004 /* Phase III Node */
        अचिन्हित दीर्घ blksize;
	__u8 priority;
पूर्ण;

व्योम dn_neigh_init(व्योम);
व्योम dn_neigh_cleanup(व्योम);
पूर्णांक dn_neigh_router_hello(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक dn_neigh_endnode_hello(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम dn_neigh_poपूर्णांकopoपूर्णांक_hello(काष्ठा sk_buff *skb);
पूर्णांक dn_neigh_elist(काष्ठा net_device *dev, अचिन्हित अक्षर *ptr, पूर्णांक n);
पूर्णांक dn_to_neigh_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);

बाह्य काष्ठा neigh_table dn_neigh_table;

#पूर्ण_अगर /* _NET_DN_NEIGH_H */
