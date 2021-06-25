<शैली गुरु>
/*
 * net/tipc/bearer.h: Include file क्रम TIPC bearer code
 *
 * Copyright (c) 1996-2006, 2013-2016, Ericsson AB
 * Copyright (c) 2005, 2010-2011, Wind River Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _TIPC_BEARER_H
#घोषणा _TIPC_BEARER_H

#समावेश "netlink.h"
#समावेश "core.h"
#समावेश "msg.h"
#समावेश <net/genetlink.h>

#घोषणा MAX_MEDIA	3

/* Identअगरiers associated with TIPC message header media address info
 * - address info field is 32 bytes दीर्घ
 * - the field's actual content and length is defined per media
 * - reमुख्यing unused bytes in the field are set to zero
 */
#घोषणा TIPC_MEDIA_INFO_SIZE	32
#घोषणा TIPC_MEDIA_TYPE_OFFSET	3
#घोषणा TIPC_MEDIA_ADDR_OFFSET	4

/*
 * Identअगरiers of supported TIPC media types
 */
#घोषणा TIPC_MEDIA_TYPE_ETH	1
#घोषणा TIPC_MEDIA_TYPE_IB	2
#घोषणा TIPC_MEDIA_TYPE_UDP	3

/* Minimum bearer MTU */
#घोषणा TIPC_MIN_BEARER_MTU	(MAX_H_SIZE + INT_H_SIZE)

/* Identअगरiers क्रम distinguishing between broadcast/multicast and replicast
 */
#घोषणा TIPC_BROADCAST_SUPPORT  1
#घोषणा TIPC_REPLICAST_SUPPORT  2

/**
 * काष्ठा tipc_media_addr - destination address used by TIPC bearers
 * @value: address info (क्रमmat defined by media)
 * @media_id: TIPC media type identअगरier
 * @broadcast: non-zero अगर address is a broadcast address
 */
काष्ठा tipc_media_addr अणु
	u8 value[TIPC_MEDIA_INFO_SIZE];
	u8 media_id;
	u8 broadcast;
पूर्ण;

काष्ठा tipc_bearer;

/**
 * काष्ठा tipc_media - Media specअगरic info exposed to generic bearer layer
 * @send_msg: routine which handles buffer transmission
 * @enable_media: routine which enables a media
 * @disable_media: routine which disables a media
 * @addr2str: convert media address क्रमmat to string
 * @addr2msg: convert from media addr क्रमmat to discovery msg addr क्रमmat
 * @msg2addr: convert from discovery msg addr क्रमmat to media addr क्रमmat
 * @raw2addr: convert from raw addr क्रमmat to media addr क्रमmat
 * @priority: शेष link (and bearer) priority
 * @tolerance: शेष समय (in ms) beक्रमe declaring link failure
 * @min_win: minimum winकरोw (in packets) beक्रमe declaring link congestion
 * @max_win: maximum winकरोw (in packets) beक्रमe declaring link congestion
 * @mtu: max packet size bearer can support क्रम media type not dependent on
 * underlying device MTU
 * @type_id: TIPC media identअगरier
 * @hwaddr_len: TIPC media address len
 * @name: media name
 */
काष्ठा tipc_media अणु
	पूर्णांक (*send_msg)(काष्ठा net *net, काष्ठा sk_buff *buf,
			काष्ठा tipc_bearer *b,
			काष्ठा tipc_media_addr *dest);
	पूर्णांक (*enable_media)(काष्ठा net *net, काष्ठा tipc_bearer *b,
			    काष्ठा nlattr *attr[]);
	व्योम (*disable_media)(काष्ठा tipc_bearer *b);
	पूर्णांक (*addr2str)(काष्ठा tipc_media_addr *addr,
			अक्षर *strbuf,
			पूर्णांक bufsz);
	पूर्णांक (*addr2msg)(अक्षर *msg, काष्ठा tipc_media_addr *addr);
	पूर्णांक (*msg2addr)(काष्ठा tipc_bearer *b,
			काष्ठा tipc_media_addr *addr,
			अक्षर *msg);
	पूर्णांक (*raw2addr)(काष्ठा tipc_bearer *b,
			काष्ठा tipc_media_addr *addr,
			अक्षर *raw);
	u32 priority;
	u32 tolerance;
	u32 min_win;
	u32 max_win;
	u32 mtu;
	u32 type_id;
	u32 hwaddr_len;
	अक्षर name[TIPC_MAX_MEDIA_NAME];
पूर्ण;

/**
 * काष्ठा tipc_bearer - Generic TIPC bearer काष्ठाure
 * @media_ptr: poपूर्णांकer to additional media-specअगरic inक्रमmation about bearer
 * @mtu: max packet size bearer can support
 * @addr: media-specअगरic address associated with bearer
 * @name: bearer name (क्रमmat = media:पूर्णांकerface)
 * @media: ptr to media काष्ठाure associated with bearer
 * @bcast_addr: media address used in broadcasting
 * @pt: packet type क्रम bearer
 * @rcu: rcu काष्ठा क्रम tipc_bearer
 * @priority: शेष link priority क्रम bearer
 * @min_win: minimum winकरोw (in packets) beक्रमe declaring link congestion
 * @max_win: maximum winकरोw (in packets) beक्रमe declaring link congestion
 * @tolerance: शेष link tolerance क्रम bearer
 * @करोमुख्य: network करोमुख्य to which links can be established
 * @identity: array index of this bearer within TIPC bearer array
 * @disc: ptr to link setup request
 * @net_plane: network plane ('A' through 'H') currently associated with bearer
 * @up: bearer up flag (bit 0)
 * @refcnt: tipc_bearer reference counter
 *
 * Note: media-specअगरic code is responsible क्रम initialization of the fields
 * indicated below when a bearer is enabled; TIPC's generic bearer code takes
 * care of initializing all other fields.
 */
काष्ठा tipc_bearer अणु
	व्योम __rcu *media_ptr;			/* initialized by media */
	u32 mtu;				/* initialized by media */
	काष्ठा tipc_media_addr addr;		/* initialized by media */
	अक्षर name[TIPC_MAX_BEARER_NAME];
	काष्ठा tipc_media *media;
	काष्ठा tipc_media_addr bcast_addr;
	काष्ठा packet_type pt;
	काष्ठा rcu_head rcu;
	u32 priority;
	u32 min_win;
	u32 max_win;
	u32 tolerance;
	u32 करोमुख्य;
	u32 identity;
	काष्ठा tipc_discoverer *disc;
	अक्षर net_plane;
	अचिन्हित दीर्घ up;
	refcount_t refcnt;
पूर्ण;

काष्ठा tipc_bearer_names अणु
	अक्षर media_name[TIPC_MAX_MEDIA_NAME];
	अक्षर अगर_name[TIPC_MAX_IF_NAME];
पूर्ण;

/*
 * TIPC routines available to supported media types
 */

व्योम tipc_rcv(काष्ठा net *net, काष्ठा sk_buff *skb, काष्ठा tipc_bearer *b);

/*
 * Routines made available to TIPC by supported media types
 */
बाह्य काष्ठा tipc_media eth_media_info;

#अगर_घोषित CONFIG_TIPC_MEDIA_IB
बाह्य काष्ठा tipc_media ib_media_info;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TIPC_MEDIA_UDP
बाह्य काष्ठा tipc_media udp_media_info;
#पूर्ण_अगर

पूर्णांक tipc_nl_bearer_disable(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक __tipc_nl_bearer_disable(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_bearer_enable(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक __tipc_nl_bearer_enable(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_bearer_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक tipc_nl_bearer_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_bearer_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक __tipc_nl_bearer_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_bearer_add(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

पूर्णांक tipc_nl_media_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक tipc_nl_media_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_media_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक __tipc_nl_media_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

पूर्णांक tipc_media_set_priority(स्थिर अक्षर *name, u32 new_value);
पूर्णांक tipc_media_set_winकरोw(स्थिर अक्षर *name, u32 new_value);
पूर्णांक tipc_media_addr_म_लिखो(अक्षर *buf, पूर्णांक len, काष्ठा tipc_media_addr *a);
पूर्णांक tipc_enable_l2_media(काष्ठा net *net, काष्ठा tipc_bearer *b,
			 काष्ठा nlattr *attrs[]);
bool tipc_bearer_hold(काष्ठा tipc_bearer *b);
व्योम tipc_bearer_put(काष्ठा tipc_bearer *b);
व्योम tipc_disable_l2_media(काष्ठा tipc_bearer *b);
पूर्णांक tipc_l2_send_msg(काष्ठा net *net, काष्ठा sk_buff *buf,
		     काष्ठा tipc_bearer *b, काष्ठा tipc_media_addr *dest);

व्योम tipc_bearer_add_dest(काष्ठा net *net, u32 bearer_id, u32 dest);
व्योम tipc_bearer_हटाओ_dest(काष्ठा net *net, u32 bearer_id, u32 dest);
काष्ठा tipc_bearer *tipc_bearer_find(काष्ठा net *net, स्थिर अक्षर *name);
पूर्णांक tipc_bearer_get_name(काष्ठा net *net, अक्षर *name, u32 bearer_id);
काष्ठा tipc_media *tipc_media_find(स्थिर अक्षर *name);
पूर्णांक tipc_bearer_setup(व्योम);
व्योम tipc_bearer_cleanup(व्योम);
व्योम tipc_bearer_stop(काष्ठा net *net);
पूर्णांक tipc_bearer_mtu(काष्ठा net *net, u32 bearer_id);
bool tipc_bearer_bcast_support(काष्ठा net *net, u32 bearer_id);
व्योम tipc_bearer_xmit_skb(काष्ठा net *net, u32 bearer_id,
			  काष्ठा sk_buff *skb,
			  काष्ठा tipc_media_addr *dest);
व्योम tipc_bearer_xmit(काष्ठा net *net, u32 bearer_id,
		      काष्ठा sk_buff_head *xmitq,
		      काष्ठा tipc_media_addr *dst,
		      काष्ठा tipc_node *__dnode);
व्योम tipc_bearer_bc_xmit(काष्ठा net *net, u32 bearer_id,
			 काष्ठा sk_buff_head *xmitq);
व्योम tipc_clone_to_loopback(काष्ठा net *net, काष्ठा sk_buff_head *pkts);
पूर्णांक tipc_attach_loopback(काष्ठा net *net);
व्योम tipc_detach_loopback(काष्ठा net *net);

अटल अंतरभूत व्योम tipc_loopback_trace(काष्ठा net *net,
				       काष्ठा sk_buff_head *pkts)
अणु
	अगर (unlikely(dev_nit_active(net->loopback_dev)))
		tipc_clone_to_loopback(net, pkts);
पूर्ण

/* check अगर device MTU is too low क्रम tipc headers */
अटल अंतरभूत bool tipc_mtu_bad(काष्ठा net_device *dev, अचिन्हित पूर्णांक reserve)
अणु
	अगर (dev->mtu >= TIPC_MIN_BEARER_MTU + reserve)
		वापस false;
	netdev_warn(dev, "MTU too low for tipc bearer\n");
	वापस true;
पूर्ण

#पूर्ण_अगर	/* _TIPC_BEARER_H */
