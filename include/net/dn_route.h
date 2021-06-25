<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _NET_DN_ROUTE_H
#घोषणा _NET_DN_ROUTE_H

/******************************************************************************
    (c) 1995-1998 E.M. Serrat		emserrat@geocities.com
    
*******************************************************************************/

काष्ठा sk_buff *dn_alloc_skb(काष्ठा sock *sk, पूर्णांक size, gfp_t pri);
पूर्णांक dn_route_output_sock(काष्ठा dst_entry __rcu **pprt, काष्ठा flowidn *,
			 काष्ठा sock *sk, पूर्णांक flags);
पूर्णांक dn_cache_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
व्योम dn_rt_cache_flush(पूर्णांक delay);
पूर्णांक dn_route_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		 काष्ठा packet_type *pt, काष्ठा net_device *orig_dev);

/* Masks क्रम flags field */
#घोषणा DN_RT_F_PID 0x07 /* Mask क्रम packet type                      */
#घोषणा DN_RT_F_PF  0x80 /* Padding Follows                           */
#घोषणा DN_RT_F_VER 0x40 /* Version =0 discard packet अगर ==1          */
#घोषणा DN_RT_F_IE  0x20 /* Intra Ethernet, Reserved in लघु pkt     */
#घोषणा DN_RT_F_RTS 0x10 /* Packet is being वापसed to sender        */
#घोषणा DN_RT_F_RQR 0x08 /* Return packet to sender upon non-delivery */

/* Mask क्रम types of routing packets */
#घोषणा DN_RT_PKT_MSK   0x06
/* Types of routing packets */
#घोषणा DN_RT_PKT_SHORT 0x02 /* Short routing packet */
#घोषणा DN_RT_PKT_LONG  0x06 /* Long routing packet  */

/* Mask क्रम control/routing selection */
#घोषणा DN_RT_PKT_CNTL  0x01 /* Set to 1 अगर a control packet  */
/* Types of control packets */
#घोषणा DN_RT_CNTL_MSK  0x0f /* Mask क्रम control packets      */
#घोषणा DN_RT_PKT_INIT  0x01 /* Initialisation packet         */
#घोषणा DN_RT_PKT_VERI  0x03 /* Verअगरication Message          */
#घोषणा DN_RT_PKT_HELO  0x05 /* Hello and Test Message        */
#घोषणा DN_RT_PKT_L1RT  0x07 /* Level 1 Routing Message       */
#घोषणा DN_RT_PKT_L2RT  0x09 /* Level 2 Routing Message       */
#घोषणा DN_RT_PKT_ERTH  0x0b /* Ethernet Router Hello         */
#घोषणा DN_RT_PKT_EEDH  0x0d /* Ethernet EndNode Hello        */

/* Values क्रम info field in hello message */
#घोषणा DN_RT_INFO_TYPE 0x03 /* Type mask                     */
#घोषणा DN_RT_INFO_L1RT 0x02 /* L1 Router                     */
#घोषणा DN_RT_INFO_L2RT 0x01 /* L2 Router                     */
#घोषणा DN_RT_INFO_ENDN 0x03 /* EndNode                       */
#घोषणा DN_RT_INFO_VERI 0x04 /* Verअगरication Reqd.            */
#घोषणा DN_RT_INFO_RJCT 0x08 /* Reject Flag, Reserved         */
#घोषणा DN_RT_INFO_VFLD 0x10 /* Verअगरication Failed, Reserved */
#घोषणा DN_RT_INFO_NOML 0x20 /* No Multicast traffic accepted */
#घोषणा DN_RT_INFO_BLKR 0x40 /* Blocking Requested            */

/*
 * The fl काष्ठाure is what we used to look up the route.
 * The rt_saddr & rt_daddr entries are the same as key.saddr & key.daddr
 * except क्रम local input routes, where the rt_saddr = fl.fld_dst and
 * rt_daddr = fl.fld_src to allow the route to be used क्रम वापसing
 * packets to the originating host.
 */
काष्ठा dn_route अणु
	काष्ठा dst_entry dst;
	काष्ठा dn_route __rcu *dn_next;

	काष्ठा neighbour *n;

	काष्ठा flowidn fld;

	__le16 rt_saddr;
	__le16 rt_daddr;
	__le16 rt_gateway;
	__le16 rt_local_src;	/* Source used क्रम क्रमwarding packets */
	__le16 rt_src_map;
	__le16 rt_dst_map;

	अचिन्हित पूर्णांक rt_flags;
	अचिन्हित पूर्णांक rt_type;
पूर्ण;

अटल अंतरभूत bool dn_is_input_route(काष्ठा dn_route *rt)
अणु
	वापस rt->fld.flowidn_iअगर != 0;
पूर्ण

अटल अंतरभूत bool dn_is_output_route(काष्ठा dn_route *rt)
अणु
	वापस rt->fld.flowidn_iअगर == 0;
पूर्ण

व्योम dn_route_init(व्योम);
व्योम dn_route_cleanup(व्योम);

#समावेश <net/sock.h>
#समावेश <linux/अगर_arp.h>

अटल अंतरभूत व्योम dn_rt_send(काष्ठा sk_buff *skb)
अणु
	dev_queue_xmit(skb);
पूर्ण

अटल अंतरभूत व्योम dn_rt_finish_output(काष्ठा sk_buff *skb, अक्षर *dst, अक्षर *src)
अणु
	काष्ठा net_device *dev = skb->dev;

	अगर ((dev->type != ARPHRD_ETHER) && (dev->type != ARPHRD_LOOPBACK))
		dst = शून्य;

	अगर (dev_hard_header(skb, dev, ETH_P_DNA_RT, dst, src, skb->len) >= 0)
		dn_rt_send(skb);
	अन्यथा
		kमुक्त_skb(skb);
पूर्ण

#पूर्ण_अगर /* _NET_DN_ROUTE_H */
