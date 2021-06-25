<शैली गुरु>
/*
 * IEEE 802.2 User Interface SAPs क्रम Linux, data काष्ठाures and indicators.
 *
 * Copyright (c) 2001 by Jay Schulist <jschlst@samba.org>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
#अगर_अघोषित __LINUX_LLC_H
#घोषणा __LINUX_LLC_H

#समावेश <uapi/linux/llc.h>

#घोषणा LLC_SAP_DYN_START	0xC0
#घोषणा LLC_SAP_DYN_STOP	0xDE
#घोषणा LLC_SAP_DYN_TRIES	4

#घोषणा llc_ui_skb_cb(__skb) ((काष्ठा sockaddr_llc *)&((__skb)->cb[0]))
#पूर्ण_अगर /* __LINUX_LLC_H */
