<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
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
*******************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/crc32.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <net/netevent.h>
#समावेश <net/neighbour.h>
#समावेश "i40iw.h"

/**
 * i40iw_arp_table - manage arp table
 * @iwdev: iwarp device
 * @ip_addr: ip address क्रम device
 * @ipv4: flag indicating IPv4 when true
 * @mac_addr: mac address ptr
 * @action: modअगरy, delete or add
 */
पूर्णांक i40iw_arp_table(काष्ठा i40iw_device *iwdev,
		    u32 *ip_addr,
		    bool ipv4,
		    u8 *mac_addr,
		    u32 action)
अणु
	पूर्णांक arp_index;
	पूर्णांक err;
	u32 ip[4];

	अगर (ipv4) अणु
		स_रखो(ip, 0, माप(ip));
		ip[0] = *ip_addr;
	पूर्ण अन्यथा अणु
		स_नकल(ip, ip_addr, माप(ip));
	पूर्ण

	क्रम (arp_index = 0; (u32)arp_index < iwdev->arp_table_size; arp_index++)
		अगर (स_भेद(iwdev->arp_table[arp_index].ip_addr, ip, माप(ip)) == 0)
			अवरोध;
	चयन (action) अणु
	हाल I40IW_ARP_ADD:
		अगर (arp_index != iwdev->arp_table_size)
			वापस -1;

		arp_index = 0;
		err = i40iw_alloc_resource(iwdev, iwdev->allocated_arps,
					   iwdev->arp_table_size,
					   (u32 *)&arp_index,
					   &iwdev->next_arp_index);

		अगर (err)
			वापस err;

		स_नकल(iwdev->arp_table[arp_index].ip_addr, ip, माप(ip));
		ether_addr_copy(iwdev->arp_table[arp_index].mac_addr, mac_addr);
		अवरोध;
	हाल I40IW_ARP_RESOLVE:
		अगर (arp_index == iwdev->arp_table_size)
			वापस -1;
		अवरोध;
	हाल I40IW_ARP_DELETE:
		अगर (arp_index == iwdev->arp_table_size)
			वापस -1;
		स_रखो(iwdev->arp_table[arp_index].ip_addr, 0,
		       माप(iwdev->arp_table[arp_index].ip_addr));
		eth_zero_addr(iwdev->arp_table[arp_index].mac_addr);
		i40iw_मुक्त_resource(iwdev, iwdev->allocated_arps, arp_index);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	वापस arp_index;
पूर्ण

/**
 * i40iw_wr32 - ग_लिखो 32 bits to hw रेजिस्टर
 * @hw: hardware inक्रमmation including रेजिस्टरs
 * @reg: रेजिस्टर offset
 * @value: vvalue to ग_लिखो to रेजिस्टर
 */
अंतरभूत व्योम i40iw_wr32(काष्ठा i40iw_hw *hw, u32 reg, u32 value)
अणु
	ग_लिखोl(value, hw->hw_addr + reg);
पूर्ण

/**
 * i40iw_rd32 - पढ़ो a 32 bit hw रेजिस्टर
 * @hw: hardware inक्रमmation including रेजिस्टरs
 * @reg: रेजिस्टर offset
 *
 * Return value of रेजिस्टर content
 */
अंतरभूत u32 i40iw_rd32(काष्ठा i40iw_hw *hw, u32 reg)
अणु
	वापस पढ़ोl(hw->hw_addr + reg);
पूर्ण

/**
 * i40iw_inetaddr_event - प्रणाली notअगरier क्रम ipv4 addr events
 * @notअगरier: not used
 * @event: event क्रम notअगरier
 * @ptr: अगर address
 */
पूर्णांक i40iw_inetaddr_event(काष्ठा notअगरier_block *notअगरier,
			 अचिन्हित दीर्घ event,
			 व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = ptr;
	काष्ठा net_device *event_netdev = अगरa->अगरa_dev->dev;
	काष्ठा net_device *netdev;
	काष्ठा net_device *upper_dev;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_handler *hdl;
	u32 local_ipaddr;
	u32 action = I40IW_ARP_ADD;

	hdl = i40iw_find_netdev(event_netdev);
	अगर (!hdl)
		वापस NOTIFY_DONE;

	iwdev = &hdl->device;
	अगर (iwdev->init_state < IP_ADDR_REGISTERED || iwdev->closing)
		वापस NOTIFY_DONE;

	netdev = iwdev->ldev->netdev;
	upper_dev = netdev_master_upper_dev_get(netdev);
	अगर (netdev != event_netdev)
		वापस NOTIFY_DONE;

	अगर (upper_dev) अणु
		काष्ठा in_device *in;

		rcu_पढ़ो_lock();
		in = __in_dev_get_rcu(upper_dev);

		local_ipaddr = 0;
		अगर (in) अणु
			काष्ठा in_अगरaddr *अगरa;

			अगरa = rcu_dereference(in->अगरa_list);
			अगर (अगरa)
				local_ipaddr = ntohl(अगरa->अगरa_address);
		पूर्ण

		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		local_ipaddr = ntohl(अगरa->अगरa_address);
	पूर्ण
	चयन (event) अणु
	हाल NETDEV_DOWN:
		action = I40IW_ARP_DELETE;
		fallthrough;
	हाल NETDEV_UP:
	हाल NETDEV_CHANGEADDR:

		/* Just skip अगर no need to handle ARP cache */
		अगर (!local_ipaddr)
			अवरोध;

		i40iw_manage_arp_cache(iwdev,
				       netdev->dev_addr,
				       &local_ipaddr,
				       true,
				       action);
		i40iw_अगर_notअगरy(iwdev, netdev, &local_ipaddr, true,
				(action == I40IW_ARP_ADD) ? true : false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/**
 * i40iw_inet6addr_event - प्रणाली notअगरier क्रम ipv6 addr events
 * @notअगरier: not used
 * @event: event क्रम notअगरier
 * @ptr: अगर address
 */
पूर्णांक i40iw_inet6addr_event(काष्ठा notअगरier_block *notअगरier,
			  अचिन्हित दीर्घ event,
			  व्योम *ptr)
अणु
	काष्ठा inet6_अगरaddr *अगरa = (काष्ठा inet6_अगरaddr *)ptr;
	काष्ठा net_device *event_netdev = अगरa->idev->dev;
	काष्ठा net_device *netdev;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_handler *hdl;
	u32 local_ipaddr6[4];
	u32 action = I40IW_ARP_ADD;

	hdl = i40iw_find_netdev(event_netdev);
	अगर (!hdl)
		वापस NOTIFY_DONE;

	iwdev = &hdl->device;
	अगर (iwdev->init_state < IP_ADDR_REGISTERED || iwdev->closing)
		वापस NOTIFY_DONE;

	netdev = iwdev->ldev->netdev;
	अगर (netdev != event_netdev)
		वापस NOTIFY_DONE;

	i40iw_copy_ip_ntohl(local_ipaddr6, अगरa->addr.in6_u.u6_addr32);
	चयन (event) अणु
	हाल NETDEV_DOWN:
		action = I40IW_ARP_DELETE;
		fallthrough;
	हाल NETDEV_UP:
	हाल NETDEV_CHANGEADDR:
		i40iw_manage_arp_cache(iwdev,
				       netdev->dev_addr,
				       local_ipaddr6,
				       false,
				       action);
		i40iw_अगर_notअगरy(iwdev, netdev, local_ipaddr6, false,
				(action == I40IW_ARP_ADD) ? true : false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/**
 * i40iw_net_event - प्रणाली notअगरier क्रम netevents
 * @notअगरier: not used
 * @event: event क्रम notअगरier
 * @ptr: neighbor
 */
पूर्णांक i40iw_net_event(काष्ठा notअगरier_block *notअगरier, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा neighbour *neigh = ptr;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_handler *iwhdl;
	__be32 *p;
	u32 local_ipaddr[4];

	चयन (event) अणु
	हाल NETEVENT_NEIGH_UPDATE:
		iwhdl = i40iw_find_netdev((काष्ठा net_device *)neigh->dev);
		अगर (!iwhdl)
			वापस NOTIFY_DONE;
		iwdev = &iwhdl->device;
		अगर (iwdev->init_state < IP_ADDR_REGISTERED || iwdev->closing)
			वापस NOTIFY_DONE;
		p = (__be32 *)neigh->primary_key;
		i40iw_copy_ip_ntohl(local_ipaddr, p);
		अगर (neigh->nud_state & NUD_VALID) अणु
			i40iw_manage_arp_cache(iwdev,
					       neigh->ha,
					       local_ipaddr,
					       false,
					       I40IW_ARP_ADD);

		पूर्ण अन्यथा अणु
			i40iw_manage_arp_cache(iwdev,
					       neigh->ha,
					       local_ipaddr,
					       false,
					       I40IW_ARP_DELETE);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/**
 * i40iw_netdevice_event - प्रणाली notअगरier क्रम netdev events
 * @notअगरier: not used
 * @event: event क्रम notअगरier
 * @ptr: netdev
 */
पूर्णांक i40iw_netdevice_event(काष्ठा notअगरier_block *notअगरier,
			  अचिन्हित दीर्घ event,
			  व्योम *ptr)
अणु
	काष्ठा net_device *event_netdev;
	काष्ठा net_device *netdev;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_handler *hdl;

	event_netdev = netdev_notअगरier_info_to_dev(ptr);

	hdl = i40iw_find_netdev(event_netdev);
	अगर (!hdl)
		वापस NOTIFY_DONE;

	iwdev = &hdl->device;
	अगर (iwdev->init_state < RDMA_DEV_REGISTERED || iwdev->closing)
		वापस NOTIFY_DONE;

	netdev = iwdev->ldev->netdev;
	अगर (netdev != event_netdev)
		वापस NOTIFY_DONE;

	iwdev->iw_status = 1;

	चयन (event) अणु
	हाल NETDEV_DOWN:
		iwdev->iw_status = 0;
		fallthrough;
	हाल NETDEV_UP:
		i40iw_port_ibevent(iwdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/**
 * i40iw_get_cqp_request - get cqp काष्ठा
 * @cqp: device cqp ptr
 * @रुको: cqp to be used in रुको mode
 */
काष्ठा i40iw_cqp_request *i40iw_get_cqp_request(काष्ठा i40iw_cqp *cqp, bool रुको)
अणु
	काष्ठा i40iw_cqp_request *cqp_request = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cqp->req_lock, flags);
	अगर (!list_empty(&cqp->cqp_avail_reqs)) अणु
		cqp_request = list_entry(cqp->cqp_avail_reqs.next,
					 काष्ठा i40iw_cqp_request, list);
		list_del_init(&cqp_request->list);
	पूर्ण
	spin_unlock_irqrestore(&cqp->req_lock, flags);
	अगर (!cqp_request) अणु
		cqp_request = kzalloc(माप(*cqp_request), GFP_ATOMIC);
		अगर (cqp_request) अणु
			cqp_request->dynamic = true;
			INIT_LIST_HEAD(&cqp_request->list);
			init_रुकोqueue_head(&cqp_request->रुकोq);
		पूर्ण
	पूर्ण
	अगर (!cqp_request) अणु
		i40iw_pr_err("CQP Request Fail: No Memory");
		वापस शून्य;
	पूर्ण

	अगर (रुको) अणु
		atomic_set(&cqp_request->refcount, 2);
		cqp_request->रुकोing = true;
	पूर्ण अन्यथा अणु
		atomic_set(&cqp_request->refcount, 1);
	पूर्ण
	वापस cqp_request;
पूर्ण

/**
 * i40iw_मुक्त_cqp_request - मुक्त cqp request
 * @cqp: cqp ptr
 * @cqp_request: to be put back in cqp list
 */
व्योम i40iw_मुक्त_cqp_request(काष्ठा i40iw_cqp *cqp, काष्ठा i40iw_cqp_request *cqp_request)
अणु
	काष्ठा i40iw_device *iwdev = container_of(cqp, काष्ठा i40iw_device, cqp);
	अचिन्हित दीर्घ flags;

	अगर (cqp_request->dynamic) अणु
		kमुक्त(cqp_request);
	पूर्ण अन्यथा अणु
		cqp_request->request_करोne = false;
		cqp_request->callback_fcn = शून्य;
		cqp_request->रुकोing = false;

		spin_lock_irqsave(&cqp->req_lock, flags);
		list_add_tail(&cqp_request->list, &cqp->cqp_avail_reqs);
		spin_unlock_irqrestore(&cqp->req_lock, flags);
	पूर्ण
	wake_up(&iwdev->बंद_wq);
पूर्ण

/**
 * i40iw_put_cqp_request - dec ref count and मुक्त अगर 0
 * @cqp: cqp ptr
 * @cqp_request: to be put back in cqp list
 */
व्योम i40iw_put_cqp_request(काष्ठा i40iw_cqp *cqp,
			   काष्ठा i40iw_cqp_request *cqp_request)
अणु
	अगर (atomic_dec_and_test(&cqp_request->refcount))
		i40iw_मुक्त_cqp_request(cqp, cqp_request);
पूर्ण

/**
 * i40iw_मुक्त_pending_cqp_request -मुक्त pending cqp request objs
 * @cqp: cqp ptr
 * @cqp_request: to be put back in cqp list
 */
अटल व्योम i40iw_मुक्त_pending_cqp_request(काष्ठा i40iw_cqp *cqp,
					   काष्ठा i40iw_cqp_request *cqp_request)
अणु
	काष्ठा i40iw_device *iwdev = container_of(cqp, काष्ठा i40iw_device, cqp);

	अगर (cqp_request->रुकोing) अणु
		cqp_request->compl_info.error = true;
		cqp_request->request_करोne = true;
		wake_up(&cqp_request->रुकोq);
	पूर्ण
	i40iw_put_cqp_request(cqp, cqp_request);
	रुको_event_समयout(iwdev->बंद_wq,
			   !atomic_पढ़ो(&cqp_request->refcount),
			   1000);
पूर्ण

/**
 * i40iw_cleanup_pending_cqp_op - clean-up cqp with no completions
 * @iwdev: iwarp device
 */
व्योम i40iw_cleanup_pending_cqp_op(काष्ठा i40iw_device *iwdev)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	काष्ठा i40iw_cqp *cqp = &iwdev->cqp;
	काष्ठा i40iw_cqp_request *cqp_request = शून्य;
	काष्ठा cqp_commands_info *pcmdinfo = शून्य;
	u32 i, pending_work, wqe_idx;

	pending_work = I40IW_RING_WORK_AVAILABLE(cqp->sc_cqp.sq_ring);
	wqe_idx = I40IW_RING_GETCURRENT_TAIL(cqp->sc_cqp.sq_ring);
	क्रम (i = 0; i < pending_work; i++) अणु
		cqp_request = (काष्ठा i40iw_cqp_request *)(अचिन्हित दीर्घ)cqp->scratch_array[wqe_idx];
		अगर (cqp_request)
			i40iw_मुक्त_pending_cqp_request(cqp, cqp_request);
		wqe_idx = (wqe_idx + 1) % I40IW_RING_GETSIZE(cqp->sc_cqp.sq_ring);
	पूर्ण

	जबतक (!list_empty(&dev->cqp_cmd_head)) अणु
		pcmdinfo = (काष्ठा cqp_commands_info *)i40iw_हटाओ_head(&dev->cqp_cmd_head);
		cqp_request = container_of(pcmdinfo, काष्ठा i40iw_cqp_request, info);
		अगर (cqp_request)
			i40iw_मुक्त_pending_cqp_request(cqp, cqp_request);
	पूर्ण
पूर्ण

/**
 * i40iw_रुको_event - रुको क्रम completion
 * @iwdev: iwarp device
 * @cqp_request: cqp request to रुको
 */
अटल पूर्णांक i40iw_रुको_event(काष्ठा i40iw_device *iwdev,
			    काष्ठा i40iw_cqp_request *cqp_request)
अणु
	काष्ठा cqp_commands_info *info = &cqp_request->info;
	काष्ठा i40iw_cqp *iwcqp = &iwdev->cqp;
	काष्ठा i40iw_cqp_समयout cqp_समयout;
	bool cqp_error = false;
	पूर्णांक err_code = 0;
	स_रखो(&cqp_समयout, 0, माप(cqp_समयout));
	cqp_समयout.compl_cqp_cmds = iwdev->sc_dev.cqp_cmd_stats[OP_COMPLETED_COMMANDS];
	करो अणु
		अगर (रुको_event_समयout(cqp_request->रुकोq,
				       cqp_request->request_करोne, CQP_COMPL_WAIT_TIME))
			अवरोध;

		i40iw_check_cqp_progress(&cqp_समयout, &iwdev->sc_dev);

		अगर (cqp_समयout.count < CQP_TIMEOUT_THRESHOLD)
			जारी;

		i40iw_pr_err("error cqp command 0x%x timed out", info->cqp_cmd);
		err_code = -ETIME;
		अगर (!iwdev->reset) अणु
			iwdev->reset = true;
			i40iw_request_reset(iwdev);
		पूर्ण
		जाओ करोne;
	पूर्ण जबतक (1);
	cqp_error = cqp_request->compl_info.error;
	अगर (cqp_error) अणु
		i40iw_pr_err("error cqp command 0x%x completion maj = 0x%x min=0x%x\n",
			     info->cqp_cmd, cqp_request->compl_info.maj_err_code,
			     cqp_request->compl_info.min_err_code);
		err_code = -EPROTO;
		जाओ करोne;
	पूर्ण
करोne:
	i40iw_put_cqp_request(iwcqp, cqp_request);
	वापस err_code;
पूर्ण

/**
 * i40iw_handle_cqp_op - process cqp command
 * @iwdev: iwarp device
 * @cqp_request: cqp request to process
 */
क्रमागत i40iw_status_code i40iw_handle_cqp_op(काष्ठा i40iw_device *iwdev,
					   काष्ठा i40iw_cqp_request
					   *cqp_request)
अणु
	काष्ठा i40iw_sc_dev *dev = &iwdev->sc_dev;
	क्रमागत i40iw_status_code status;
	काष्ठा cqp_commands_info *info = &cqp_request->info;
	पूर्णांक err_code = 0;

	अगर (iwdev->reset) अणु
		i40iw_मुक्त_cqp_request(&iwdev->cqp, cqp_request);
		वापस I40IW_ERR_CQP_COMPL_ERROR;
	पूर्ण

	status = i40iw_process_cqp_cmd(dev, info);
	अगर (status) अणु
		i40iw_pr_err("error cqp command 0x%x failed\n", info->cqp_cmd);
		i40iw_मुक्त_cqp_request(&iwdev->cqp, cqp_request);
		वापस status;
	पूर्ण
	अगर (cqp_request->रुकोing)
		err_code = i40iw_रुको_event(iwdev, cqp_request);
	अगर (err_code)
		status = I40IW_ERR_CQP_COMPL_ERROR;
	वापस status;
पूर्ण

/**
 * i40iw_add_devusecount - add dev refcount
 * @iwdev: dev क्रम refcount
 */
व्योम i40iw_add_devusecount(काष्ठा i40iw_device *iwdev)
अणु
	atomic64_inc(&iwdev->use_count);
पूर्ण

/**
 * i40iw_rem_devusecount - decrement refcount क्रम dev
 * @iwdev: device
 */
व्योम i40iw_rem_devusecount(काष्ठा i40iw_device *iwdev)
अणु
	अगर (!atomic64_dec_and_test(&iwdev->use_count))
		वापस;
	wake_up(&iwdev->बंद_wq);
पूर्ण

/**
 * i40iw_add_pdusecount - add pd refcount
 * @iwpd: pd क्रम refcount
 */
व्योम i40iw_add_pdusecount(काष्ठा i40iw_pd *iwpd)
अणु
	atomic_inc(&iwpd->usecount);
पूर्ण

/**
 * i40iw_rem_pdusecount - decrement refcount क्रम pd and मुक्त अगर 0
 * @iwpd: pd क्रम refcount
 * @iwdev: iwarp device
 */
व्योम i40iw_rem_pdusecount(काष्ठा i40iw_pd *iwpd, काष्ठा i40iw_device *iwdev)
अणु
	अगर (!atomic_dec_and_test(&iwpd->usecount))
		वापस;
	i40iw_मुक्त_resource(iwdev, iwdev->allocated_pds, iwpd->sc_pd.pd_id);
पूर्ण

/**
 * i40iw_qp_add_ref - add refcount क्रम qp
 * @ibqp: iqarp qp
 */
व्योम i40iw_qp_add_ref(काष्ठा ib_qp *ibqp)
अणु
	काष्ठा i40iw_qp *iwqp = (काष्ठा i40iw_qp *)ibqp;

	refcount_inc(&iwqp->refcount);
पूर्ण

/**
 * i40iw_qp_rem_ref - rem refcount क्रम qp and मुक्त अगर 0
 * @ibqp: iqarp qp
 */
व्योम i40iw_qp_rem_ref(काष्ठा ib_qp *ibqp)
अणु
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_device *iwdev;
	u32 qp_num;
	अचिन्हित दीर्घ flags;

	iwqp = to_iwqp(ibqp);
	iwdev = iwqp->iwdev;
	spin_lock_irqsave(&iwdev->qptable_lock, flags);
	अगर (!refcount_dec_and_test(&iwqp->refcount)) अणु
		spin_unlock_irqrestore(&iwdev->qptable_lock, flags);
		वापस;
	पूर्ण

	qp_num = iwqp->ibqp.qp_num;
	iwdev->qp_table[qp_num] = शून्य;
	spin_unlock_irqrestore(&iwdev->qptable_lock, flags);
	complete(&iwqp->मुक्त_qp);

पूर्ण

/**
 * i40iw_get_qp - get qp address
 * @device: iwarp device
 * @qpn: qp number
 */
काष्ठा ib_qp *i40iw_get_qp(काष्ठा ib_device *device, पूर्णांक qpn)
अणु
	काष्ठा i40iw_device *iwdev = to_iwdev(device);

	अगर ((qpn < IW_FIRST_QPN) || (qpn >= iwdev->max_qp))
		वापस शून्य;

	वापस &iwdev->qp_table[qpn]->ibqp;
पूर्ण

/**
 * i40iw_debug_buf - prपूर्णांक debug msg and buffer is mask set
 * @dev: hardware control device काष्ठाure
 * @mask: mask to compare अगर to prपूर्णांक debug buffer
 * @desc: identअगरying string
 * @buf: poपूर्णांकs buffer addr
 * @size: saize of buffer to prपूर्णांक
 */
व्योम i40iw_debug_buf(काष्ठा i40iw_sc_dev *dev,
		     क्रमागत i40iw_debug_flag mask,
		     अक्षर *desc,
		     u64 *buf,
		     u32 size)
अणु
	u32 i;

	अगर (!(dev->debug_mask & mask))
		वापस;
	i40iw_debug(dev, mask, "%s\n", desc);
	i40iw_debug(dev, mask, "starting address virt=%p phy=%llxh\n", buf,
		    (अचिन्हित दीर्घ दीर्घ)virt_to_phys(buf));

	क्रम (i = 0; i < size; i += 8)
		i40iw_debug(dev, mask, "index %03d val: %016llx\n", i, buf[i / 8]);
पूर्ण

/**
 * i40iw_get_hw_addr - वापस hw addr
 * @par: poपूर्णांकs to shared dev
 */
u8 __iomem *i40iw_get_hw_addr(व्योम *par)
अणु
	काष्ठा i40iw_sc_dev *dev = (काष्ठा i40iw_sc_dev *)par;

	वापस dev->hw->hw_addr;
पूर्ण

/**
 * i40iw_हटाओ_head - वापस head entry and हटाओ from list
 * @list: list क्रम entry
 */
व्योम *i40iw_हटाओ_head(काष्ठा list_head *list)
अणु
	काष्ठा list_head *entry;

	अगर (list_empty(list))
		वापस शून्य;

	entry = (व्योम *)list->next;
	list_del(entry);
	वापस (व्योम *)entry;
पूर्ण

/**
 * i40iw_allocate_dma_mem - Memory alloc helper fn
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to fill out
 * @size: size of memory requested
 * @alignment: what to align the allocation to
 */
क्रमागत i40iw_status_code i40iw_allocate_dma_mem(काष्ठा i40iw_hw *hw,
					      काष्ठा i40iw_dma_mem *mem,
					      u64 size,
					      u32 alignment)
अणु
	काष्ठा pci_dev *pcidev = hw->pcidev;

	अगर (!mem)
		वापस I40IW_ERR_PARAM;
	mem->size = ALIGN(size, alignment);
	mem->va = dma_alloc_coherent(&pcidev->dev, mem->size,
				     (dma_addr_t *)&mem->pa, GFP_KERNEL);
	अगर (!mem->va)
		वापस I40IW_ERR_NO_MEMORY;
	वापस 0;
पूर्ण

/**
 * i40iw_मुक्त_dma_mem - Memory मुक्त helper fn
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to मुक्त
 */
व्योम i40iw_मुक्त_dma_mem(काष्ठा i40iw_hw *hw, काष्ठा i40iw_dma_mem *mem)
अणु
	काष्ठा pci_dev *pcidev = hw->pcidev;

	अगर (!mem || !mem->va)
		वापस;

	dma_मुक्त_coherent(&pcidev->dev, mem->size,
			  mem->va, (dma_addr_t)mem->pa);
	mem->va = शून्य;
पूर्ण

/**
 * i40iw_allocate_virt_mem - भव memory alloc helper fn
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to fill out
 * @size: size of memory requested
 */
क्रमागत i40iw_status_code i40iw_allocate_virt_mem(काष्ठा i40iw_hw *hw,
					       काष्ठा i40iw_virt_mem *mem,
					       u32 size)
अणु
	अगर (!mem)
		वापस I40IW_ERR_PARAM;

	mem->size = size;
	mem->va = kzalloc(size, GFP_KERNEL);

	अगर (mem->va)
		वापस 0;
	अन्यथा
		वापस I40IW_ERR_NO_MEMORY;
पूर्ण

/**
 * i40iw_मुक्त_virt_mem - भव memory मुक्त helper fn
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to मुक्त
 */
क्रमागत i40iw_status_code i40iw_मुक्त_virt_mem(काष्ठा i40iw_hw *hw,
					   काष्ठा i40iw_virt_mem *mem)
अणु
	अगर (!mem)
		वापस I40IW_ERR_PARAM;
	/*
	 * mem->va poपूर्णांकs to the parent of mem, so both mem and mem->va
	 * can not be touched once mem->va is मुक्तd
	 */
	kमुक्त(mem->va);
	वापस 0;
पूर्ण

/**
 * i40iw_cqp_sds_cmd - create cqp command क्रम sd
 * @dev: hardware control device काष्ठाure
 * @sdinfo: inक्रमmation  क्रम sd cqp
 *
 */
क्रमागत i40iw_status_code i40iw_cqp_sds_cmd(काष्ठा i40iw_sc_dev *dev,
					 काष्ठा i40iw_update_sds_info *sdinfo)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;
	cqp_info = &cqp_request->info;
	स_नकल(&cqp_info->in.u.update_pe_sds.info, sdinfo,
	       माप(cqp_info->in.u.update_pe_sds.info));
	cqp_info->cqp_cmd = OP_UPDATE_PE_SDS;
	cqp_info->post_sq = 1;
	cqp_info->in.u.update_pe_sds.dev = dev;
	cqp_info->in.u.update_pe_sds.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Update SD's fail");
	वापस status;
पूर्ण

/**
 * i40iw_qp_suspend_resume - cqp command क्रम suspend/resume
 * @dev: hardware control device काष्ठाure
 * @qp: hardware control qp
 * @suspend: flag अगर suspend or resume
 */
व्योम i40iw_qp_suspend_resume(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_qp *qp, bool suspend)
अणु
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा i40iw_sc_cqp *cqp = dev->cqp;
	काष्ठा cqp_commands_info *cqp_info;
	क्रमागत i40iw_status_code status;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, false);
	अगर (!cqp_request)
		वापस;

	cqp_info = &cqp_request->info;
	cqp_info->cqp_cmd = (suspend) ? OP_SUSPEND : OP_RESUME;
	cqp_info->in.u.suspend_resume.cqp = cqp;
	cqp_info->in.u.suspend_resume.qp = qp;
	cqp_info->in.u.suspend_resume.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP QP Suspend/Resume fail");
पूर्ण

/**
 * i40iw_term_modअगरy_qp - modअगरy qp क्रम term message
 * @qp: hardware control qp
 * @next_state: qp's next state
 * @term: terminate code
 * @term_len: length
 */
व्योम i40iw_term_modअगरy_qp(काष्ठा i40iw_sc_qp *qp, u8 next_state, u8 term, u8 term_len)
अणु
	काष्ठा i40iw_qp *iwqp;

	iwqp = (काष्ठा i40iw_qp *)qp->back_qp;
	i40iw_next_iw_state(iwqp, next_state, 0, term, term_len);
पूर्ण;

/**
 * i40iw_terminate_करोne - after terminate is completed
 * @qp: hardware control qp
 * @समयout_occurred: indicates अगर terminate समयr expired
 */
व्योम i40iw_terminate_करोne(काष्ठा i40iw_sc_qp *qp, पूर्णांक समयout_occurred)
अणु
	काष्ठा i40iw_qp *iwqp;
	u32 next_iwarp_state = I40IW_QP_STATE_ERROR;
	u8 hte = 0;
	bool first_समय;
	अचिन्हित दीर्घ flags;

	iwqp = (काष्ठा i40iw_qp *)qp->back_qp;
	spin_lock_irqsave(&iwqp->lock, flags);
	अगर (iwqp->hte_added) अणु
		iwqp->hte_added = 0;
		hte = 1;
	पूर्ण
	first_समय = !(qp->term_flags & I40IW_TERM_DONE);
	qp->term_flags |= I40IW_TERM_DONE;
	spin_unlock_irqrestore(&iwqp->lock, flags);
	अगर (first_समय) अणु
		अगर (!समयout_occurred)
			i40iw_terminate_del_समयr(qp);
		अन्यथा
			next_iwarp_state = I40IW_QP_STATE_CLOSING;

		i40iw_next_iw_state(iwqp, next_iwarp_state, hte, 0, 0);
		i40iw_cm_disconn(iwqp);
	पूर्ण
पूर्ण

/**
 * i40iw_terminate_समयout - समयout happened
 * @t: poपूर्णांकs to iwarp qp
 */
अटल व्योम i40iw_terminate_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा i40iw_qp *iwqp = from_समयr(iwqp, t, terminate_समयr);
	काष्ठा i40iw_sc_qp *qp = (काष्ठा i40iw_sc_qp *)&iwqp->sc_qp;

	i40iw_terminate_करोne(qp, 1);
	i40iw_qp_rem_ref(&iwqp->ibqp);
पूर्ण

/**
 * i40iw_terminate_start_समयr - start terminate समयout
 * @qp: hardware control qp
 */
व्योम i40iw_terminate_start_समयr(काष्ठा i40iw_sc_qp *qp)
अणु
	काष्ठा i40iw_qp *iwqp;

	iwqp = (काष्ठा i40iw_qp *)qp->back_qp;
	i40iw_qp_add_ref(&iwqp->ibqp);
	समयr_setup(&iwqp->terminate_समयr, i40iw_terminate_समयout, 0);
	iwqp->terminate_समयr.expires = jअगरfies + HZ;
	add_समयr(&iwqp->terminate_समयr);
पूर्ण

/**
 * i40iw_terminate_del_समयr - delete terminate समयout
 * @qp: hardware control qp
 */
व्योम i40iw_terminate_del_समयr(काष्ठा i40iw_sc_qp *qp)
अणु
	काष्ठा i40iw_qp *iwqp;

	iwqp = (काष्ठा i40iw_qp *)qp->back_qp;
	अगर (del_समयr(&iwqp->terminate_समयr))
		i40iw_qp_rem_ref(&iwqp->ibqp);
पूर्ण

/**
 * i40iw_cqp_generic_worker - generic worker क्रम cqp
 * @work: work poपूर्णांकer
 */
अटल व्योम i40iw_cqp_generic_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा i40iw_virtchnl_work_info *work_info =
	    &((काष्ठा virtchnl_work *)work)->work_info;

	अगर (work_info->worker_vf_dev)
		work_info->callback_fcn(work_info->worker_vf_dev);
पूर्ण

/**
 * i40iw_cqp_spawn_worker - spawn worket thपढ़ो
 * @dev: device काष्ठा poपूर्णांकer
 * @work_info: work request info
 * @iw_vf_idx: भव function index
 */
व्योम i40iw_cqp_spawn_worker(काष्ठा i40iw_sc_dev *dev,
			    काष्ठा i40iw_virtchnl_work_info *work_info,
			    u32 iw_vf_idx)
अणु
	काष्ठा virtchnl_work *work;
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	work = &iwdev->virtchnl_w[iw_vf_idx];
	स_नकल(&work->work_info, work_info, माप(*work_info));
	INIT_WORK(&work->work, i40iw_cqp_generic_worker);
	queue_work(iwdev->virtchnl_wq, &work->work);
पूर्ण

/**
 * i40iw_cqp_manage_hmc_fcn_worker -
 * @work: work poपूर्णांकer क्रम hmc info
 */
अटल व्योम i40iw_cqp_manage_hmc_fcn_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा i40iw_cqp_request *cqp_request =
	    ((काष्ठा virtchnl_work *)work)->cqp_request;
	काष्ठा i40iw_ccq_cqe_info ccq_cqe_info;
	काष्ठा i40iw_hmc_fcn_info *hmcfcninfo =
			&cqp_request->info.in.u.manage_hmc_pm.info;
	काष्ठा i40iw_device *iwdev =
	    (काष्ठा i40iw_device *)cqp_request->info.in.u.manage_hmc_pm.dev->back_dev;

	ccq_cqe_info.cqp = शून्य;
	ccq_cqe_info.maj_err_code = cqp_request->compl_info.maj_err_code;
	ccq_cqe_info.min_err_code = cqp_request->compl_info.min_err_code;
	ccq_cqe_info.op_code = cqp_request->compl_info.op_code;
	ccq_cqe_info.op_ret_val = cqp_request->compl_info.op_ret_val;
	ccq_cqe_info.scratch = 0;
	ccq_cqe_info.error = cqp_request->compl_info.error;
	hmcfcninfo->callback_fcn(cqp_request->info.in.u.manage_hmc_pm.dev,
				 hmcfcninfo->cqp_callback_param, &ccq_cqe_info);
	i40iw_put_cqp_request(&iwdev->cqp, cqp_request);
पूर्ण

/**
 * i40iw_cqp_manage_hmc_fcn_callback - called function after cqp completion
 * @cqp_request: cqp request info काष्ठा क्रम hmc fun
 * @unused: unused param of callback
 */
अटल व्योम i40iw_cqp_manage_hmc_fcn_callback(काष्ठा i40iw_cqp_request *cqp_request,
					      u32 unused)
अणु
	काष्ठा virtchnl_work *work;
	काष्ठा i40iw_hmc_fcn_info *hmcfcninfo =
	    &cqp_request->info.in.u.manage_hmc_pm.info;
	काष्ठा i40iw_device *iwdev =
	    (काष्ठा i40iw_device *)cqp_request->info.in.u.manage_hmc_pm.dev->
	    back_dev;

	अगर (hmcfcninfo && hmcfcninfo->callback_fcn) अणु
		i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_HMC, "%s1\n", __func__);
		atomic_inc(&cqp_request->refcount);
		work = &iwdev->virtchnl_w[hmcfcninfo->iw_vf_idx];
		work->cqp_request = cqp_request;
		INIT_WORK(&work->work, i40iw_cqp_manage_hmc_fcn_worker);
		queue_work(iwdev->virtchnl_wq, &work->work);
		i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_HMC, "%s2\n", __func__);
	पूर्ण अन्यथा अणु
		i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_HMC, "%s: Something wrong\n", __func__);
	पूर्ण
पूर्ण

/**
 * i40iw_cqp_manage_hmc_fcn_cmd - issue cqp command to manage hmc
 * @dev: hardware control device काष्ठाure
 * @hmcfcninfo: info क्रम hmc
 */
क्रमागत i40iw_status_code i40iw_cqp_manage_hmc_fcn_cmd(काष्ठा i40iw_sc_dev *dev,
						    काष्ठा i40iw_hmc_fcn_info *hmcfcninfo)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	i40iw_debug(&iwdev->sc_dev, I40IW_DEBUG_HMC, "%s\n", __func__);
	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, false);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;
	cqp_info = &cqp_request->info;
	cqp_request->callback_fcn = i40iw_cqp_manage_hmc_fcn_callback;
	cqp_request->param = hmcfcninfo;
	स_नकल(&cqp_info->in.u.manage_hmc_pm.info, hmcfcninfo,
	       माप(*hmcfcninfo));
	cqp_info->in.u.manage_hmc_pm.dev = dev;
	cqp_info->cqp_cmd = OP_MANAGE_HMC_PM_FUNC_TABLE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.manage_hmc_pm.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Manage HMC fail");
	वापस status;
पूर्ण

/**
 * i40iw_cqp_query_fpm_values_cmd - send cqp command क्रम fpm
 * @dev: function device काष्ठा
 * @values_mem: buffer क्रम fpm
 * @hmc_fn_id: function id क्रम fpm
 */
क्रमागत i40iw_status_code i40iw_cqp_query_fpm_values_cmd(काष्ठा i40iw_sc_dev *dev,
						      काष्ठा i40iw_dma_mem *values_mem,
						      u8 hmc_fn_id)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;
	cqp_info = &cqp_request->info;
	cqp_request->param = शून्य;
	cqp_info->in.u.query_fpm_values.cqp = dev->cqp;
	cqp_info->in.u.query_fpm_values.fpm_values_pa = values_mem->pa;
	cqp_info->in.u.query_fpm_values.fpm_values_va = values_mem->va;
	cqp_info->in.u.query_fpm_values.hmc_fn_id = hmc_fn_id;
	cqp_info->cqp_cmd = OP_QUERY_FPM_VALUES;
	cqp_info->post_sq = 1;
	cqp_info->in.u.query_fpm_values.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Query FPM fail");
	वापस status;
पूर्ण

/**
 * i40iw_cqp_commit_fpm_values_cmd - commit fpm values in hw
 * @dev: hardware control device काष्ठाure
 * @values_mem: buffer with fpm values
 * @hmc_fn_id: function id क्रम fpm
 */
क्रमागत i40iw_status_code i40iw_cqp_commit_fpm_values_cmd(काष्ठा i40iw_sc_dev *dev,
						       काष्ठा i40iw_dma_mem *values_mem,
						       u8 hmc_fn_id)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;
	cqp_info = &cqp_request->info;
	cqp_request->param = शून्य;
	cqp_info->in.u.commit_fpm_values.cqp = dev->cqp;
	cqp_info->in.u.commit_fpm_values.fpm_values_pa = values_mem->pa;
	cqp_info->in.u.commit_fpm_values.fpm_values_va = values_mem->va;
	cqp_info->in.u.commit_fpm_values.hmc_fn_id = hmc_fn_id;
	cqp_info->cqp_cmd = OP_COMMIT_FPM_VALUES;
	cqp_info->post_sq = 1;
	cqp_info->in.u.commit_fpm_values.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Commit FPM fail");
	वापस status;
पूर्ण

/**
 * i40iw_vf_रुको_vchnl_resp - रुको क्रम channel msg
 * @dev: function's device काष्ठा
 */
क्रमागत i40iw_status_code i40iw_vf_रुको_vchnl_resp(काष्ठा i40iw_sc_dev *dev)
अणु
	काष्ठा i40iw_device *iwdev = dev->back_dev;
	पूर्णांक समयout_ret;

	i40iw_debug(dev, I40IW_DEBUG_VIRT, "%s[%u] dev %p, iwdev %p\n",
		    __func__, __LINE__, dev, iwdev);

	atomic_set(&iwdev->vchnl_msgs, 2);
	समयout_ret = रुको_event_समयout(iwdev->vchnl_रुकोq,
					 (atomic_पढ़ो(&iwdev->vchnl_msgs) == 1),
					 I40IW_VCHNL_EVENT_TIMEOUT);
	atomic_dec(&iwdev->vchnl_msgs);
	अगर (!समयout_ret) अणु
		i40iw_pr_err("virt channel completion timeout = 0x%x\n", समयout_ret);
		atomic_set(&iwdev->vchnl_msgs, 0);
		dev->vchnl_up = false;
		वापस I40IW_ERR_TIMEOUT;
	पूर्ण
	wake_up(&dev->vf_reqs);
	वापस 0;
पूर्ण

/**
 * i40iw_cqp_cq_create_cmd - create a cq क्रम the cqp
 * @dev: device poपूर्णांकer
 * @cq: poपूर्णांकer to created cq
 */
क्रमागत i40iw_status_code i40iw_cqp_cq_create_cmd(काष्ठा i40iw_sc_dev *dev,
					       काष्ठा i40iw_sc_cq *cq)
अणु
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;
	काष्ठा i40iw_cqp *iwcqp = &iwdev->cqp;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	क्रमागत i40iw_status_code status;

	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;

	cqp_info = &cqp_request->info;
	cqp_info->cqp_cmd = OP_CQ_CREATE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.cq_create.cq = cq;
	cqp_info->in.u.cq_create.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP Create QP fail");

	वापस status;
पूर्ण

/**
 * i40iw_cqp_qp_create_cmd - create a qp क्रम the cqp
 * @dev: device poपूर्णांकer
 * @qp: poपूर्णांकer to created qp
 */
क्रमागत i40iw_status_code i40iw_cqp_qp_create_cmd(काष्ठा i40iw_sc_dev *dev,
					       काष्ठा i40iw_sc_qp *qp)
अणु
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;
	काष्ठा i40iw_cqp *iwcqp = &iwdev->cqp;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	काष्ठा i40iw_create_qp_info *qp_info;
	क्रमागत i40iw_status_code status;

	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	अगर (!cqp_request)
		वापस I40IW_ERR_NO_MEMORY;

	cqp_info = &cqp_request->info;
	qp_info = &cqp_request->info.in.u.qp_create.info;

	स_रखो(qp_info, 0, माप(*qp_info));

	qp_info->cq_num_valid = true;
	qp_info->next_iwarp_state = I40IW_QP_STATE_RTS;

	cqp_info->cqp_cmd = OP_QP_CREATE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_create.qp = qp;
	cqp_info->in.u.qp_create.scratch = (uपूर्णांकptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP-OP QP create fail");
	वापस status;
पूर्ण

/**
 * i40iw_cqp_cq_destroy_cmd - destroy the cqp cq
 * @dev: device poपूर्णांकer
 * @cq: poपूर्णांकer to cq
 */
व्योम i40iw_cqp_cq_destroy_cmd(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_cq *cq)
अणु
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	i40iw_cq_wq_destroy(iwdev, cq);
पूर्ण

/**
 * i40iw_cqp_qp_destroy_cmd - destroy the cqp
 * @dev: device poपूर्णांकer
 * @qp: poपूर्णांकer to qp
 */
व्योम i40iw_cqp_qp_destroy_cmd(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_qp *qp)
अणु
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;
	काष्ठा i40iw_cqp *iwcqp = &iwdev->cqp;
	काष्ठा i40iw_cqp_request *cqp_request;
	काष्ठा cqp_commands_info *cqp_info;
	क्रमागत i40iw_status_code status;

	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	अगर (!cqp_request)
		वापस;

	cqp_info = &cqp_request->info;
	स_रखो(cqp_info, 0, माप(*cqp_info));

	cqp_info->cqp_cmd = OP_QP_DESTROY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_destroy.qp = qp;
	cqp_info->in.u.qp_destroy.scratch = (uपूर्णांकptr_t)cqp_request;
	cqp_info->in.u.qp_destroy.हटाओ_hash_idx = true;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	अगर (status)
		i40iw_pr_err("CQP QP_DESTROY fail");
पूर्ण


/**
 * i40iw_ieq_mpa_crc_ae - generate AE क्रम crc error
 * @dev: hardware control device काष्ठाure
 * @qp: hardware control qp
 */
व्योम i40iw_ieq_mpa_crc_ae(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_qp *qp)
अणु
	काष्ठा i40iw_gen_ae_info info;
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	i40iw_debug(dev, I40IW_DEBUG_AEQ, "%s entered\n", __func__);
	info.ae_code = I40IW_AE_LLP_RECEIVED_MPA_CRC_ERROR;
	info.ae_source = I40IW_AE_SOURCE_RQ;
	i40iw_gen_ae(iwdev, qp, &info, false);
पूर्ण

/**
 * i40iw_init_hash_desc - initialize hash क्रम crc calculation
 * @desc: cryption type
 */
क्रमागत i40iw_status_code i40iw_init_hash_desc(काष्ठा shash_desc **desc)
अणु
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *tdesc;

	tfm = crypto_alloc_shash("crc32c", 0, 0);
	अगर (IS_ERR(tfm))
		वापस I40IW_ERR_MPA_CRC;

	tdesc = kzalloc(माप(*tdesc) + crypto_shash_descsize(tfm),
			GFP_KERNEL);
	अगर (!tdesc) अणु
		crypto_मुक्त_shash(tfm);
		वापस I40IW_ERR_MPA_CRC;
	पूर्ण
	tdesc->tfm = tfm;
	*desc = tdesc;

	वापस 0;
पूर्ण

/**
 * i40iw_मुक्त_hash_desc - मुक्त hash desc
 * @desc: to be मुक्तd
 */
व्योम i40iw_मुक्त_hash_desc(काष्ठा shash_desc *desc)
अणु
	अगर (desc) अणु
		crypto_मुक्त_shash(desc->tfm);
		kमुक्त(desc);
	पूर्ण
पूर्ण

/**
 * i40iw_alloc_query_fpm_buf - allocate buffer क्रम fpm
 * @dev: hardware control device काष्ठाure
 * @mem: buffer ptr क्रम fpm to be allocated
 * @वापस: memory allocation status
 */
क्रमागत i40iw_status_code i40iw_alloc_query_fpm_buf(काष्ठा i40iw_sc_dev *dev,
						 काष्ठा i40iw_dma_mem *mem)
अणु
	क्रमागत i40iw_status_code status;
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;

	status = i40iw_obj_aligned_mem(iwdev, mem, I40IW_QUERY_FPM_BUF_SIZE,
				       I40IW_FPM_QUERY_BUF_ALIGNMENT_MASK);
	वापस status;
पूर्ण

/**
 * i40iw_ieq_check_mpacrc - check अगर mpa crc is OK
 * @desc: desc क्रम hash
 * @addr: address of buffer क्रम crc
 * @length: length of buffer
 * @value: value to be compared
 */
क्रमागत i40iw_status_code i40iw_ieq_check_mpacrc(काष्ठा shash_desc *desc,
					      व्योम *addr,
					      u32 length,
					      u32 value)
अणु
	u32 crc = 0;
	पूर्णांक ret;
	क्रमागत i40iw_status_code ret_code = 0;

	crypto_shash_init(desc);
	ret = crypto_shash_update(desc, addr, length);
	अगर (!ret)
		crypto_shash_final(desc, (u8 *)&crc);
	अगर (crc != value) अणु
		i40iw_pr_err("mpa crc check fail\n");
		ret_code = I40IW_ERR_MPA_CRC;
	पूर्ण
	वापस ret_code;
पूर्ण

/**
 * i40iw_ieq_get_qp - get qp based on quad in puda buffer
 * @dev: hardware control device काष्ठाure
 * @buf: receive puda buffer on exception q
 */
काष्ठा i40iw_sc_qp *i40iw_ieq_get_qp(काष्ठा i40iw_sc_dev *dev,
				     काष्ठा i40iw_puda_buf *buf)
अणु
	काष्ठा i40iw_device *iwdev = (काष्ठा i40iw_device *)dev->back_dev;
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_cm_node *cm_node;
	u32 loc_addr[4], rem_addr[4];
	u16 loc_port, rem_port;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा iphdr *iph = (काष्ठा iphdr *)buf->iph;
	काष्ठा tcphdr *tcph = (काष्ठा tcphdr *)buf->tcph;

	अगर (iph->version == 4) अणु
		स_रखो(loc_addr, 0, माप(loc_addr));
		loc_addr[0] = ntohl(iph->daddr);
		स_रखो(rem_addr, 0, माप(rem_addr));
		rem_addr[0] = ntohl(iph->saddr);
	पूर्ण अन्यथा अणु
		ip6h = (काष्ठा ipv6hdr *)buf->iph;
		i40iw_copy_ip_ntohl(loc_addr, ip6h->daddr.in6_u.u6_addr32);
		i40iw_copy_ip_ntohl(rem_addr, ip6h->saddr.in6_u.u6_addr32);
	पूर्ण
	loc_port = ntohs(tcph->dest);
	rem_port = ntohs(tcph->source);

	cm_node = i40iw_find_node(&iwdev->cm_core, rem_port, rem_addr, loc_port,
				  loc_addr, false, true);
	अगर (!cm_node)
		वापस शून्य;
	iwqp = cm_node->iwqp;
	वापस &iwqp->sc_qp;
पूर्ण

/**
 * i40iw_ieq_update_tcpip_info - update tcpip in the buffer
 * @buf: puda to update
 * @length: length of buffer
 * @seqnum: seq number क्रम tcp
 */
व्योम i40iw_ieq_update_tcpip_info(काष्ठा i40iw_puda_buf *buf, u16 length, u32 seqnum)
अणु
	काष्ठा tcphdr *tcph;
	काष्ठा iphdr *iph;
	u16 iphlen;
	u16 packetsize;
	u8 *addr = (u8 *)buf->mem.va;

	iphlen = (buf->ipv4) ? 20 : 40;
	iph = (काष्ठा iphdr *)(addr + buf->maclen);
	tcph = (काष्ठा tcphdr *)(addr + buf->maclen + iphlen);
	packetsize = length + buf->tcphlen + iphlen;

	iph->tot_len = htons(packetsize);
	tcph->seq = htonl(seqnum);
पूर्ण

/**
 * i40iw_puda_get_tcpip_info - get tcpip info from puda buffer
 * @info: to get inक्रमmation
 * @buf: puda buffer
 */
क्रमागत i40iw_status_code i40iw_puda_get_tcpip_info(काष्ठा i40iw_puda_completion_info *info,
						 काष्ठा i40iw_puda_buf *buf)
अणु
	काष्ठा iphdr *iph;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा tcphdr *tcph;
	u16 iphlen;
	u16 pkt_len;
	u8 *mem = (u8 *)buf->mem.va;
	काष्ठा ethhdr *ethh = (काष्ठा ethhdr *)buf->mem.va;

	अगर (ethh->h_proto == htons(0x8100)) अणु
		info->vlan_valid = true;
		buf->vlan_id = ntohs(((काष्ठा vlan_ethhdr *)ethh)->h_vlan_TCI) & VLAN_VID_MASK;
	पूर्ण
	buf->maclen = (info->vlan_valid) ? 18 : 14;
	iphlen = (info->l3proto) ? 40 : 20;
	buf->ipv4 = (info->l3proto) ? false : true;
	buf->iph = mem + buf->maclen;
	iph = (काष्ठा iphdr *)buf->iph;

	buf->tcph = buf->iph + iphlen;
	tcph = (काष्ठा tcphdr *)buf->tcph;

	अगर (buf->ipv4) अणु
		pkt_len = ntohs(iph->tot_len);
	पूर्ण अन्यथा अणु
		ip6h = (काष्ठा ipv6hdr *)buf->iph;
		pkt_len = ntohs(ip6h->payload_len) + iphlen;
	पूर्ण

	buf->totallen = pkt_len + buf->maclen;

	अगर (info->payload_len < buf->totallen) अणु
		i40iw_pr_err("payload_len = 0x%x totallen expected0x%x\n",
			     info->payload_len, buf->totallen);
		वापस I40IW_ERR_INVALID_SIZE;
	पूर्ण

	buf->tcphlen = (tcph->करोff) << 2;
	buf->datalen = pkt_len - iphlen - buf->tcphlen;
	buf->data = (buf->datalen) ? buf->tcph + buf->tcphlen : शून्य;
	buf->hdrlen = buf->maclen + iphlen + buf->tcphlen;
	buf->seqnum = ntohl(tcph->seq);
	वापस 0;
पूर्ण

/**
 * i40iw_hw_stats_समयout - Stats समयr-handler which updates all HW stats
 * @t: Timer context containing poपूर्णांकer to the vsi काष्ठाure
 */
अटल व्योम i40iw_hw_stats_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा i40iw_vsi_pestat *pf_devstat = from_समयr(pf_devstat, t,
						       stats_समयr);
	काष्ठा i40iw_sc_vsi *sc_vsi = pf_devstat->vsi;
	काष्ठा i40iw_sc_dev *pf_dev = sc_vsi->dev;
	काष्ठा i40iw_vsi_pestat *vf_devstat = शून्य;
	u16 iw_vf_idx;
	अचिन्हित दीर्घ flags;

	/*PF*/
	i40iw_hw_stats_पढ़ो_all(pf_devstat, &pf_devstat->hw_stats);

	क्रम (iw_vf_idx = 0; iw_vf_idx < I40IW_MAX_PE_ENABLED_VF_COUNT; iw_vf_idx++) अणु
		spin_lock_irqsave(&pf_devstat->lock, flags);
		अगर (pf_dev->vf_dev[iw_vf_idx]) अणु
			अगर (pf_dev->vf_dev[iw_vf_idx]->stats_initialized) अणु
				vf_devstat = &pf_dev->vf_dev[iw_vf_idx]->pestat;
				i40iw_hw_stats_पढ़ो_all(vf_devstat, &vf_devstat->hw_stats);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&pf_devstat->lock, flags);
	पूर्ण

	mod_समयr(&pf_devstat->stats_समयr,
		  jअगरfies + msecs_to_jअगरfies(STATS_TIMER_DELAY));
पूर्ण

/**
 * i40iw_hw_stats_start_समयr - Start periodic stats समयr
 * @vsi: poपूर्णांकer to the vsi काष्ठाure
 */
व्योम i40iw_hw_stats_start_समयr(काष्ठा i40iw_sc_vsi *vsi)
अणु
	काष्ठा i40iw_vsi_pestat *devstat = vsi->pestat;

	समयr_setup(&devstat->stats_समयr, i40iw_hw_stats_समयout, 0);
	mod_समयr(&devstat->stats_समयr,
		  jअगरfies + msecs_to_jअगरfies(STATS_TIMER_DELAY));
पूर्ण

/**
 * i40iw_hw_stats_stop_समयr - Delete periodic stats समयr
 * @vsi: poपूर्णांकer to the vsi काष्ठाure
 */
व्योम i40iw_hw_stats_stop_समयr(काष्ठा i40iw_sc_vsi *vsi)
अणु
	काष्ठा i40iw_vsi_pestat *devstat = vsi->pestat;

	del_समयr_sync(&devstat->stats_समयr);
पूर्ण
