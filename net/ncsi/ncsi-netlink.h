<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright Samuel Menकरोza-Jonas, IBM Corporation 2018.
 */

#अगर_अघोषित __NCSI_NETLINK_H__
#घोषणा __NCSI_NETLINK_H__

#समावेश <linux/netdevice.h>

#समावेश "internal.h"

पूर्णांक ncsi_send_netlink_rsp(काष्ठा ncsi_request *nr,
			  काष्ठा ncsi_package *np,
			  काष्ठा ncsi_channel *nc);
पूर्णांक ncsi_send_netlink_समयout(काष्ठा ncsi_request *nr,
			      काष्ठा ncsi_package *np,
			      काष्ठा ncsi_channel *nc);
पूर्णांक ncsi_send_netlink_err(काष्ठा net_device *dev,
			  u32 snd_seq,
			  u32 snd_portid,
			  काष्ठा nlmsghdr *nlhdr,
			  पूर्णांक err);

#पूर्ण_अगर /* __NCSI_NETLINK_H__ */
