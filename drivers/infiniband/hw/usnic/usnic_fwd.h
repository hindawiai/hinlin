<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित USNIC_FWD_H_
#घोषणा USNIC_FWD_H_

#समावेश <linux/अगर.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/pci.h>
#समावेश <linux/in.h>

#समावेश "usnic_abi.h"
#समावेश "usnic_common_pkt_hdr.h"
#समावेश "vnic_devcmd.h"

काष्ठा usnic_fwd_dev अणु
	काष्ठा pci_dev			*pdev;
	काष्ठा net_device		*netdev;
	spinlock_t			lock;
	/*
	 * The following fields can be पढ़ो directly off the device.
	 * However, they should be set by a accessor function, except name,
	 * which cannot be changed.
	 */
	bool				link_up;
	अक्षर				mac[ETH_ALEN];
	अचिन्हित पूर्णांक			mtu;
	__be32				inaddr;
	अक्षर				name[IFNAMSIZ];
पूर्ण;

काष्ठा usnic_fwd_flow अणु
	uपूर्णांक32_t			flow_id;
	काष्ठा usnic_fwd_dev		*ufdev;
	अचिन्हित पूर्णांक			vnic_idx;
पूर्ण;

काष्ठा usnic_filter_action अणु
	पूर्णांक				vnic_idx;
	काष्ठा filter_action		action;
पूर्ण;

काष्ठा usnic_fwd_dev *usnic_fwd_dev_alloc(काष्ठा pci_dev *pdev);
व्योम usnic_fwd_dev_मुक्त(काष्ठा usnic_fwd_dev *ufdev);

व्योम usnic_fwd_set_mac(काष्ठा usnic_fwd_dev *ufdev, अक्षर mac[ETH_ALEN]);
व्योम usnic_fwd_add_ipaddr(काष्ठा usnic_fwd_dev *ufdev, __be32 inaddr);
व्योम usnic_fwd_del_ipaddr(काष्ठा usnic_fwd_dev *ufdev);
व्योम usnic_fwd_carrier_up(काष्ठा usnic_fwd_dev *ufdev);
व्योम usnic_fwd_carrier_करोwn(काष्ठा usnic_fwd_dev *ufdev);
व्योम usnic_fwd_set_mtu(काष्ठा usnic_fwd_dev *ufdev, अचिन्हित पूर्णांक mtu);

/*
 * Allocate a flow on this क्रमwarding device. Whoever calls this function,
 * must monitor netdev events on ufdev's netdevice. If NETDEV_REBOOT or
 * NETDEV_DOWN is seen, flow will no दीर्घer function and must be
 * immediately मुक्तd by calling usnic_dealloc_flow.
 */
काष्ठा usnic_fwd_flow*
usnic_fwd_alloc_flow(काष्ठा usnic_fwd_dev *ufdev, काष्ठा filter *filter,
				काष्ठा usnic_filter_action *action);
पूर्णांक usnic_fwd_dealloc_flow(काष्ठा usnic_fwd_flow *flow);
पूर्णांक usnic_fwd_enable_qp(काष्ठा usnic_fwd_dev *ufdev, पूर्णांक vnic_idx, पूर्णांक qp_idx);
पूर्णांक usnic_fwd_disable_qp(काष्ठा usnic_fwd_dev *ufdev, पूर्णांक vnic_idx, पूर्णांक qp_idx);

अटल अंतरभूत व्योम usnic_fwd_init_usnic_filter(काष्ठा filter *filter,
						uपूर्णांक32_t usnic_id)
अणु
	filter->type = FILTER_USNIC_ID;
	filter->u.usnic.ethtype = ETH_P_IBOE;
	filter->u.usnic.flags = FILTER_FIELD_USNIC_ETHTYPE |
				FILTER_FIELD_USNIC_ID |
				FILTER_FIELD_USNIC_PROTO;
	filter->u.usnic.proto_version = (USNIC_ROCE_GRH_VER <<
					 USNIC_ROCE_GRH_VER_SHIFT) |
					 USNIC_PROTO_VER;
	filter->u.usnic.usnic_id = usnic_id;
पूर्ण

अटल अंतरभूत व्योम usnic_fwd_init_udp_filter(काष्ठा filter *filter,
						uपूर्णांक32_t daddr, uपूर्णांक16_t dport)
अणु
	filter->type = FILTER_IPV4_5TUPLE;
	filter->u.ipv4.flags = FILTER_FIELD_5TUP_PROTO;
	filter->u.ipv4.protocol = PROTO_UDP;

	अगर (daddr) अणु
		filter->u.ipv4.flags |= FILTER_FIELD_5TUP_DST_AD;
		filter->u.ipv4.dst_addr = daddr;
	पूर्ण

	अगर (dport) अणु
		filter->u.ipv4.flags |= FILTER_FIELD_5TUP_DST_PT;
		filter->u.ipv4.dst_port = dport;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* !USNIC_FWD_H_ */
