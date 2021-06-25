<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/net/ethernet/ibm/ehea/ehea_मुख्य.c
 *
 *  eHEA ethernet device driver क्रम IBM eServer System p
 *
 *  (C) Copyright IBM Corp. 2006
 *
 *  Authors:
 *	 Christoph Raisch <raisch@de.ibm.com>
 *	 Jan-Bernd Themann <themann@de.ibm.com>
 *	 Thomas Klein <tklein@de.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/memory.h>
#समावेश <यंत्र/kexec.h>
#समावेश <linux/mutex.h>
#समावेश <linux/prefetch.h>

#समावेश <net/ip.h>

#समावेश "ehea.h"
#समावेश "ehea_qmr.h"
#समावेश "ehea_phyp.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christoph Raisch <raisch@de.ibm.com>");
MODULE_DESCRIPTION("IBM eServer HEA Driver");
MODULE_VERSION(DRV_VERSION);


अटल पूर्णांक msg_level = -1;
अटल पूर्णांक rq1_entries = EHEA_DEF_ENTRIES_RQ1;
अटल पूर्णांक rq2_entries = EHEA_DEF_ENTRIES_RQ2;
अटल पूर्णांक rq3_entries = EHEA_DEF_ENTRIES_RQ3;
अटल पूर्णांक sq_entries = EHEA_DEF_ENTRIES_SQ;
अटल पूर्णांक use_mcs = 1;
अटल पूर्णांक prop_carrier_state;

module_param(msg_level, पूर्णांक, 0);
module_param(rq1_entries, पूर्णांक, 0);
module_param(rq2_entries, पूर्णांक, 0);
module_param(rq3_entries, पूर्णांक, 0);
module_param(sq_entries, पूर्णांक, 0);
module_param(prop_carrier_state, पूर्णांक, 0);
module_param(use_mcs, पूर्णांक, 0);

MODULE_PARM_DESC(msg_level, "msg_level");
MODULE_PARM_DESC(prop_carrier_state, "Propagate carrier state of physical "
		 "port to stack. 1:yes, 0:no.  Default = 0 ");
MODULE_PARM_DESC(rq3_entries, "Number of entries for Receive Queue 3 "
		 "[2^x - 1], x = [7..14]. Default = "
		 __MODULE_STRING(EHEA_DEF_ENTRIES_RQ3) ")");
MODULE_PARM_DESC(rq2_entries, "Number of entries for Receive Queue 2 "
		 "[2^x - 1], x = [7..14]. Default = "
		 __MODULE_STRING(EHEA_DEF_ENTRIES_RQ2) ")");
MODULE_PARM_DESC(rq1_entries, "Number of entries for Receive Queue 1 "
		 "[2^x - 1], x = [7..14]. Default = "
		 __MODULE_STRING(EHEA_DEF_ENTRIES_RQ1) ")");
MODULE_PARM_DESC(sq_entries, " Number of entries for the Send Queue  "
		 "[2^x - 1], x = [7..14]. Default = "
		 __MODULE_STRING(EHEA_DEF_ENTRIES_SQ) ")");
MODULE_PARM_DESC(use_mcs, " Multiple receive queues, 1: enable, 0: disable, "
		 "Default = 1");

अटल पूर्णांक port_name_cnt;
अटल LIST_HEAD(adapter_list);
अटल अचिन्हित दीर्घ ehea_driver_flags;
अटल DEFINE_MUTEX(dlpar_mem_lock);
अटल काष्ठा ehea_fw_handle_array ehea_fw_handles;
अटल काष्ठा ehea_bcmc_reg_array ehea_bcmc_regs;


अटल पूर्णांक ehea_probe_adapter(काष्ठा platक्रमm_device *dev);

अटल पूर्णांक ehea_हटाओ(काष्ठा platक्रमm_device *dev);

अटल स्थिर काष्ठा of_device_id ehea_module_device_table[] = अणु
	अणु
		.name = "lhea",
		.compatible = "IBM,lhea",
	पूर्ण,
	अणु
		.type = "network",
		.compatible = "IBM,lhea-ethernet",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ehea_module_device_table);

अटल स्थिर काष्ठा of_device_id ehea_device_table[] = अणु
	अणु
		.name = "lhea",
		.compatible = "IBM,lhea",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ehea_device_table);

अटल काष्ठा platक्रमm_driver ehea_driver = अणु
	.driver = अणु
		.name = "ehea",
		.owner = THIS_MODULE,
		.of_match_table = ehea_device_table,
	पूर्ण,
	.probe = ehea_probe_adapter,
	.हटाओ = ehea_हटाओ,
पूर्ण;

व्योम ehea_dump(व्योम *adr, पूर्णांक len, अक्षर *msg)
अणु
	पूर्णांक x;
	अचिन्हित अक्षर *deb = adr;
	क्रम (x = 0; x < len; x += 16) अणु
		pr_info("%s adr=%p ofs=%04x %016llx %016llx\n",
			msg, deb, x, *((u64 *)&deb[0]), *((u64 *)&deb[8]));
		deb += 16;
	पूर्ण
पूर्ण

अटल व्योम ehea_schedule_port_reset(काष्ठा ehea_port *port)
अणु
	अगर (!test_bit(__EHEA_DISABLE_PORT_RESET, &port->flags))
		schedule_work(&port->reset_task);
पूर्ण

अटल व्योम ehea_update_firmware_handles(व्योम)
अणु
	काष्ठा ehea_fw_handle_entry *arr = शून्य;
	काष्ठा ehea_adapter *adapter;
	पूर्णांक num_adapters = 0;
	पूर्णांक num_ports = 0;
	पूर्णांक num_portres = 0;
	पूर्णांक i = 0;
	पूर्णांक num_fw_handles, k, l;

	/* Determine number of handles */
	mutex_lock(&ehea_fw_handles.lock);

	list_क्रम_each_entry(adapter, &adapter_list, list) अणु
		num_adapters++;

		क्रम (k = 0; k < EHEA_MAX_PORTS; k++) अणु
			काष्ठा ehea_port *port = adapter->port[k];

			अगर (!port || (port->state != EHEA_PORT_UP))
				जारी;

			num_ports++;
			num_portres += port->num_def_qps;
		पूर्ण
	पूर्ण

	num_fw_handles = num_adapters * EHEA_NUM_ADAPTER_FW_HANDLES +
			 num_ports * EHEA_NUM_PORT_FW_HANDLES +
			 num_portres * EHEA_NUM_PORTRES_FW_HANDLES;

	अगर (num_fw_handles) अणु
		arr = kसुस्मृति(num_fw_handles, माप(*arr), GFP_KERNEL);
		अगर (!arr)
			जाओ out;  /* Keep the existing array */
	पूर्ण अन्यथा
		जाओ out_update;

	list_क्रम_each_entry(adapter, &adapter_list, list) अणु
		अगर (num_adapters == 0)
			अवरोध;

		क्रम (k = 0; k < EHEA_MAX_PORTS; k++) अणु
			काष्ठा ehea_port *port = adapter->port[k];

			अगर (!port || (port->state != EHEA_PORT_UP) ||
			    (num_ports == 0))
				जारी;

			क्रम (l = 0; l < port->num_def_qps; l++) अणु
				काष्ठा ehea_port_res *pr = &port->port_res[l];

				arr[i].adh = adapter->handle;
				arr[i++].fwh = pr->qp->fw_handle;
				arr[i].adh = adapter->handle;
				arr[i++].fwh = pr->send_cq->fw_handle;
				arr[i].adh = adapter->handle;
				arr[i++].fwh = pr->recv_cq->fw_handle;
				arr[i].adh = adapter->handle;
				arr[i++].fwh = pr->eq->fw_handle;
				arr[i].adh = adapter->handle;
				arr[i++].fwh = pr->send_mr.handle;
				arr[i].adh = adapter->handle;
				arr[i++].fwh = pr->recv_mr.handle;
			पूर्ण
			arr[i].adh = adapter->handle;
			arr[i++].fwh = port->qp_eq->fw_handle;
			num_ports--;
		पूर्ण

		arr[i].adh = adapter->handle;
		arr[i++].fwh = adapter->neq->fw_handle;

		अगर (adapter->mr.handle) अणु
			arr[i].adh = adapter->handle;
			arr[i++].fwh = adapter->mr.handle;
		पूर्ण
		num_adapters--;
	पूर्ण

out_update:
	kमुक्त(ehea_fw_handles.arr);
	ehea_fw_handles.arr = arr;
	ehea_fw_handles.num_entries = i;
out:
	mutex_unlock(&ehea_fw_handles.lock);
पूर्ण

अटल व्योम ehea_update_bcmc_registrations(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ehea_bcmc_reg_entry *arr = शून्य;
	काष्ठा ehea_adapter *adapter;
	काष्ठा ehea_mc_list *mc_entry;
	पूर्णांक num_registrations = 0;
	पूर्णांक i = 0;
	पूर्णांक k;

	spin_lock_irqsave(&ehea_bcmc_regs.lock, flags);

	/* Determine number of registrations */
	list_क्रम_each_entry(adapter, &adapter_list, list)
		क्रम (k = 0; k < EHEA_MAX_PORTS; k++) अणु
			काष्ठा ehea_port *port = adapter->port[k];

			अगर (!port || (port->state != EHEA_PORT_UP))
				जारी;

			num_registrations += 2;	/* Broadcast registrations */

			list_क्रम_each_entry(mc_entry, &port->mc_list->list,list)
				num_registrations += 2;
		पूर्ण

	अगर (num_registrations) अणु
		arr = kसुस्मृति(num_registrations, माप(*arr), GFP_ATOMIC);
		अगर (!arr)
			जाओ out;  /* Keep the existing array */
	पूर्ण अन्यथा
		जाओ out_update;

	list_क्रम_each_entry(adapter, &adapter_list, list) अणु
		क्रम (k = 0; k < EHEA_MAX_PORTS; k++) अणु
			काष्ठा ehea_port *port = adapter->port[k];

			अगर (!port || (port->state != EHEA_PORT_UP))
				जारी;

			अगर (num_registrations == 0)
				जाओ out_update;

			arr[i].adh = adapter->handle;
			arr[i].port_id = port->logical_port_id;
			arr[i].reg_type = EHEA_BCMC_BROADCAST |
					  EHEA_BCMC_UNTAGGED;
			arr[i++].macaddr = port->mac_addr;

			arr[i].adh = adapter->handle;
			arr[i].port_id = port->logical_port_id;
			arr[i].reg_type = EHEA_BCMC_BROADCAST |
					  EHEA_BCMC_VLANID_ALL;
			arr[i++].macaddr = port->mac_addr;
			num_registrations -= 2;

			list_क्रम_each_entry(mc_entry,
					    &port->mc_list->list, list) अणु
				अगर (num_registrations == 0)
					जाओ out_update;

				arr[i].adh = adapter->handle;
				arr[i].port_id = port->logical_port_id;
				arr[i].reg_type = EHEA_BCMC_MULTICAST |
						  EHEA_BCMC_UNTAGGED;
				अगर (mc_entry->macaddr == 0)
					arr[i].reg_type |= EHEA_BCMC_SCOPE_ALL;
				arr[i++].macaddr = mc_entry->macaddr;

				arr[i].adh = adapter->handle;
				arr[i].port_id = port->logical_port_id;
				arr[i].reg_type = EHEA_BCMC_MULTICAST |
						  EHEA_BCMC_VLANID_ALL;
				अगर (mc_entry->macaddr == 0)
					arr[i].reg_type |= EHEA_BCMC_SCOPE_ALL;
				arr[i++].macaddr = mc_entry->macaddr;
				num_registrations -= 2;
			पूर्ण
		पूर्ण
	पूर्ण

out_update:
	kमुक्त(ehea_bcmc_regs.arr);
	ehea_bcmc_regs.arr = arr;
	ehea_bcmc_regs.num_entries = i;
out:
	spin_unlock_irqrestore(&ehea_bcmc_regs.lock, flags);
पूर्ण

अटल व्योम ehea_get_stats64(काष्ठा net_device *dev,
			     काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	u64 rx_packets = 0, tx_packets = 0, rx_bytes = 0, tx_bytes = 0;
	पूर्णांक i;

	क्रम (i = 0; i < port->num_def_qps; i++) अणु
		rx_packets += port->port_res[i].rx_packets;
		rx_bytes   += port->port_res[i].rx_bytes;
	पूर्ण

	क्रम (i = 0; i < port->num_def_qps; i++) अणु
		tx_packets += port->port_res[i].tx_packets;
		tx_bytes   += port->port_res[i].tx_bytes;
	पूर्ण

	stats->tx_packets = tx_packets;
	stats->rx_bytes = rx_bytes;
	stats->tx_bytes = tx_bytes;
	stats->rx_packets = rx_packets;

	stats->multicast = port->stats.multicast;
	stats->rx_errors = port->stats.rx_errors;
पूर्ण

अटल व्योम ehea_update_stats(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ehea_port *port =
		container_of(work, काष्ठा ehea_port, stats_work.work);
	काष्ठा net_device *dev = port->netdev;
	काष्ठा rtnl_link_stats64 *stats = &port->stats;
	काष्ठा hcp_ehea_port_cb2 *cb2;
	u64 hret;

	cb2 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb2) अणु
		netdev_err(dev, "No mem for cb2. Some interface statistics were not updated\n");
		जाओ resched;
	पूर्ण

	hret = ehea_h_query_ehea_port(port->adapter->handle,
				      port->logical_port_id,
				      H_PORT_CB2, H_PORT_CB2_ALL, cb2);
	अगर (hret != H_SUCCESS) अणु
		netdev_err(dev, "query_ehea_port failed\n");
		जाओ out_herr;
	पूर्ण

	अगर (netअगर_msg_hw(port))
		ehea_dump(cb2, माप(*cb2), "net_device_stats");

	stats->multicast = cb2->rxmcp;
	stats->rx_errors = cb2->rxuerr;

out_herr:
	मुक्त_page((अचिन्हित दीर्घ)cb2);
resched:
	schedule_delayed_work(&port->stats_work,
			      round_jअगरfies_relative(msecs_to_jअगरfies(1000)));
पूर्ण

अटल व्योम ehea_refill_rq1(काष्ठा ehea_port_res *pr, पूर्णांक index, पूर्णांक nr_of_wqes)
अणु
	काष्ठा sk_buff **skb_arr_rq1 = pr->rq1_skba.arr;
	काष्ठा net_device *dev = pr->port->netdev;
	पूर्णांक max_index_mask = pr->rq1_skba.len - 1;
	पूर्णांक fill_wqes = pr->rq1_skba.os_skbs + nr_of_wqes;
	पूर्णांक adder = 0;
	पूर्णांक i;

	pr->rq1_skba.os_skbs = 0;

	अगर (unlikely(test_bit(__EHEA_STOP_XFER, &ehea_driver_flags))) अणु
		अगर (nr_of_wqes > 0)
			pr->rq1_skba.index = index;
		pr->rq1_skba.os_skbs = fill_wqes;
		वापस;
	पूर्ण

	क्रम (i = 0; i < fill_wqes; i++) अणु
		अगर (!skb_arr_rq1[index]) अणु
			skb_arr_rq1[index] = netdev_alloc_skb(dev,
							      EHEA_L_PKT_SIZE);
			अगर (!skb_arr_rq1[index]) अणु
				pr->rq1_skba.os_skbs = fill_wqes - i;
				अवरोध;
			पूर्ण
		पूर्ण
		index--;
		index &= max_index_mask;
		adder++;
	पूर्ण

	अगर (adder == 0)
		वापस;

	/* Ring करोorbell */
	ehea_update_rq1a(pr->qp, adder);
पूर्ण

अटल व्योम ehea_init_fill_rq1(काष्ठा ehea_port_res *pr, पूर्णांक nr_rq1a)
अणु
	काष्ठा sk_buff **skb_arr_rq1 = pr->rq1_skba.arr;
	काष्ठा net_device *dev = pr->port->netdev;
	पूर्णांक i;

	अगर (nr_rq1a > pr->rq1_skba.len) अणु
		netdev_err(dev, "NR_RQ1A bigger than skb array len\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < nr_rq1a; i++) अणु
		skb_arr_rq1[i] = netdev_alloc_skb(dev, EHEA_L_PKT_SIZE);
		अगर (!skb_arr_rq1[i])
			अवरोध;
	पूर्ण
	/* Ring करोorbell */
	ehea_update_rq1a(pr->qp, i - 1);
पूर्ण

अटल पूर्णांक ehea_refill_rq_def(काष्ठा ehea_port_res *pr,
			      काष्ठा ehea_q_skb_arr *q_skba, पूर्णांक rq_nr,
			      पूर्णांक num_wqes, पूर्णांक wqe_type, पूर्णांक packet_size)
अणु
	काष्ठा net_device *dev = pr->port->netdev;
	काष्ठा ehea_qp *qp = pr->qp;
	काष्ठा sk_buff **skb_arr = q_skba->arr;
	काष्ठा ehea_rwqe *rwqe;
	पूर्णांक i, index, max_index_mask, fill_wqes;
	पूर्णांक adder = 0;
	पूर्णांक ret = 0;

	fill_wqes = q_skba->os_skbs + num_wqes;
	q_skba->os_skbs = 0;

	अगर (unlikely(test_bit(__EHEA_STOP_XFER, &ehea_driver_flags))) अणु
		q_skba->os_skbs = fill_wqes;
		वापस ret;
	पूर्ण

	index = q_skba->index;
	max_index_mask = q_skba->len - 1;
	क्रम (i = 0; i < fill_wqes; i++) अणु
		u64 पंचांगp_addr;
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(dev, packet_size);
		अगर (!skb) अणु
			q_skba->os_skbs = fill_wqes - i;
			अगर (q_skba->os_skbs == q_skba->len - 2) अणु
				netdev_info(pr->port->netdev,
					    "rq%i ran dry - no mem for skb\n",
					    rq_nr);
				ret = -ENOMEM;
			पूर्ण
			अवरोध;
		पूर्ण

		skb_arr[index] = skb;
		पंचांगp_addr = ehea_map_vaddr(skb->data);
		अगर (पंचांगp_addr == -1) अणु
			dev_consume_skb_any(skb);
			q_skba->os_skbs = fill_wqes - i;
			ret = 0;
			अवरोध;
		पूर्ण

		rwqe = ehea_get_next_rwqe(qp, rq_nr);
		rwqe->wr_id = EHEA_BMASK_SET(EHEA_WR_ID_TYPE, wqe_type)
			    | EHEA_BMASK_SET(EHEA_WR_ID_INDEX, index);
		rwqe->sg_list[0].l_key = pr->recv_mr.lkey;
		rwqe->sg_list[0].vaddr = पंचांगp_addr;
		rwqe->sg_list[0].len = packet_size;
		rwqe->data_segments = 1;

		index++;
		index &= max_index_mask;
		adder++;
	पूर्ण

	q_skba->index = index;
	अगर (adder == 0)
		जाओ out;

	/* Ring करोorbell */
	iosync();
	अगर (rq_nr == 2)
		ehea_update_rq2a(pr->qp, adder);
	अन्यथा
		ehea_update_rq3a(pr->qp, adder);
out:
	वापस ret;
पूर्ण


अटल पूर्णांक ehea_refill_rq2(काष्ठा ehea_port_res *pr, पूर्णांक nr_of_wqes)
अणु
	वापस ehea_refill_rq_def(pr, &pr->rq2_skba, 2,
				  nr_of_wqes, EHEA_RWQE2_TYPE,
				  EHEA_RQ2_PKT_SIZE);
पूर्ण


अटल पूर्णांक ehea_refill_rq3(काष्ठा ehea_port_res *pr, पूर्णांक nr_of_wqes)
अणु
	वापस ehea_refill_rq_def(pr, &pr->rq3_skba, 3,
				  nr_of_wqes, EHEA_RWQE3_TYPE,
				  EHEA_MAX_PACKET_SIZE);
पूर्ण

अटल अंतरभूत पूर्णांक ehea_check_cqe(काष्ठा ehea_cqe *cqe, पूर्णांक *rq_num)
अणु
	*rq_num = (cqe->type & EHEA_CQE_TYPE_RQ) >> 5;
	अगर ((cqe->status & EHEA_CQE_STAT_ERR_MASK) == 0)
		वापस 0;
	अगर (((cqe->status & EHEA_CQE_STAT_ERR_TCP) != 0) &&
	    (cqe->header_length == 0))
		वापस 0;
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम ehea_fill_skb(काष्ठा net_device *dev,
				 काष्ठा sk_buff *skb, काष्ठा ehea_cqe *cqe,
				 काष्ठा ehea_port_res *pr)
अणु
	पूर्णांक length = cqe->num_bytes_transfered - 4;	/*हटाओ CRC */

	skb_put(skb, length);
	skb->protocol = eth_type_trans(skb, dev);

	/* The packet was not an IPV4 packet so a complemented checksum was
	   calculated. The value is found in the Internet Checksum field. */
	अगर (cqe->status & EHEA_CQE_BLIND_CKSUM) अणु
		skb->ip_summed = CHECKSUM_COMPLETE;
		skb->csum = csum_unfold(~cqe->inet_checksum_value);
	पूर्ण अन्यथा
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	skb_record_rx_queue(skb, pr - &pr->port->port_res[0]);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *get_skb_by_index(काष्ठा sk_buff **skb_array,
					       पूर्णांक arr_len,
					       काष्ठा ehea_cqe *cqe)
अणु
	पूर्णांक skb_index = EHEA_BMASK_GET(EHEA_WR_ID_INDEX, cqe->wr_id);
	काष्ठा sk_buff *skb;
	व्योम *pref;
	पूर्णांक x;

	x = skb_index + 1;
	x &= (arr_len - 1);

	pref = skb_array[x];
	अगर (pref) अणु
		prefetchw(pref);
		prefetchw(pref + EHEA_CACHE_LINE);

		pref = (skb_array[x]->data);
		prefetch(pref);
		prefetch(pref + EHEA_CACHE_LINE);
		prefetch(pref + EHEA_CACHE_LINE * 2);
		prefetch(pref + EHEA_CACHE_LINE * 3);
	पूर्ण

	skb = skb_array[skb_index];
	skb_array[skb_index] = शून्य;
	वापस skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *get_skb_by_index_ll(काष्ठा sk_buff **skb_array,
						  पूर्णांक arr_len, पूर्णांक wqe_index)
अणु
	काष्ठा sk_buff *skb;
	व्योम *pref;
	पूर्णांक x;

	x = wqe_index + 1;
	x &= (arr_len - 1);

	pref = skb_array[x];
	अगर (pref) अणु
		prefetchw(pref);
		prefetchw(pref + EHEA_CACHE_LINE);

		pref = (skb_array[x]->data);
		prefetchw(pref);
		prefetchw(pref + EHEA_CACHE_LINE);
	पूर्ण

	skb = skb_array[wqe_index];
	skb_array[wqe_index] = शून्य;
	वापस skb;
पूर्ण

अटल पूर्णांक ehea_treat_poll_error(काष्ठा ehea_port_res *pr, पूर्णांक rq,
				 काष्ठा ehea_cqe *cqe, पूर्णांक *processed_rq2,
				 पूर्णांक *processed_rq3)
अणु
	काष्ठा sk_buff *skb;

	अगर (cqe->status & EHEA_CQE_STAT_ERR_TCP)
		pr->p_stats.err_tcp_cksum++;
	अगर (cqe->status & EHEA_CQE_STAT_ERR_IP)
		pr->p_stats.err_ip_cksum++;
	अगर (cqe->status & EHEA_CQE_STAT_ERR_CRC)
		pr->p_stats.err_frame_crc++;

	अगर (rq == 2) अणु
		*processed_rq2 += 1;
		skb = get_skb_by_index(pr->rq2_skba.arr, pr->rq2_skba.len, cqe);
		dev_kमुक्त_skb(skb);
	पूर्ण अन्यथा अगर (rq == 3) अणु
		*processed_rq3 += 1;
		skb = get_skb_by_index(pr->rq3_skba.arr, pr->rq3_skba.len, cqe);
		dev_kमुक्त_skb(skb);
	पूर्ण

	अगर (cqe->status & EHEA_CQE_STAT_FAT_ERR_MASK) अणु
		अगर (netअगर_msg_rx_err(pr->port)) अणु
			pr_err("Critical receive error for QP %d. Resetting port.\n",
			       pr->qp->init_attr.qp_nr);
			ehea_dump(cqe, माप(*cqe), "CQE");
		पूर्ण
		ehea_schedule_port_reset(pr->port);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ehea_proc_rwqes(काष्ठा net_device *dev,
			   काष्ठा ehea_port_res *pr,
			   पूर्णांक budget)
अणु
	काष्ठा ehea_port *port = pr->port;
	काष्ठा ehea_qp *qp = pr->qp;
	काष्ठा ehea_cqe *cqe;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff **skb_arr_rq1 = pr->rq1_skba.arr;
	काष्ठा sk_buff **skb_arr_rq2 = pr->rq2_skba.arr;
	काष्ठा sk_buff **skb_arr_rq3 = pr->rq3_skba.arr;
	पूर्णांक skb_arr_rq1_len = pr->rq1_skba.len;
	पूर्णांक skb_arr_rq2_len = pr->rq2_skba.len;
	पूर्णांक skb_arr_rq3_len = pr->rq3_skba.len;
	पूर्णांक processed, processed_rq1, processed_rq2, processed_rq3;
	u64 processed_bytes = 0;
	पूर्णांक wqe_index, last_wqe_index, rq, port_reset;

	processed = processed_rq1 = processed_rq2 = processed_rq3 = 0;
	last_wqe_index = 0;

	cqe = ehea_poll_rq1(qp, &wqe_index);
	जबतक ((processed < budget) && cqe) अणु
		ehea_inc_rq1(qp);
		processed_rq1++;
		processed++;
		अगर (netअगर_msg_rx_status(port))
			ehea_dump(cqe, माप(*cqe), "CQE");

		last_wqe_index = wqe_index;
		rmb();
		अगर (!ehea_check_cqe(cqe, &rq)) अणु
			अगर (rq == 1) अणु
				/* LL RQ1 */
				skb = get_skb_by_index_ll(skb_arr_rq1,
							  skb_arr_rq1_len,
							  wqe_index);
				अगर (unlikely(!skb)) अणु
					netअगर_info(port, rx_err, dev,
						  "LL rq1: skb=NULL\n");

					skb = netdev_alloc_skb(dev,
							       EHEA_L_PKT_SIZE);
					अगर (!skb)
						अवरोध;
				पूर्ण
				skb_copy_to_linear_data(skb, ((अक्षर *)cqe) + 64,
						 cqe->num_bytes_transfered - 4);
				ehea_fill_skb(dev, skb, cqe, pr);
			पूर्ण अन्यथा अगर (rq == 2) अणु
				/* RQ2 */
				skb = get_skb_by_index(skb_arr_rq2,
						       skb_arr_rq2_len, cqe);
				अगर (unlikely(!skb)) अणु
					netअगर_err(port, rx_err, dev,
						  "rq2: skb=NULL\n");
					अवरोध;
				पूर्ण
				ehea_fill_skb(dev, skb, cqe, pr);
				processed_rq2++;
			पूर्ण अन्यथा अणु
				/* RQ3 */
				skb = get_skb_by_index(skb_arr_rq3,
						       skb_arr_rq3_len, cqe);
				अगर (unlikely(!skb)) अणु
					netअगर_err(port, rx_err, dev,
						  "rq3: skb=NULL\n");
					अवरोध;
				पूर्ण
				ehea_fill_skb(dev, skb, cqe, pr);
				processed_rq3++;
			पूर्ण

			processed_bytes += skb->len;

			अगर (cqe->status & EHEA_CQE_VLAN_TAG_XTRACT)
				__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
						       cqe->vlan_tag);

			napi_gro_receive(&pr->napi, skb);
		पूर्ण अन्यथा अणु
			pr->p_stats.poll_receive_errors++;
			port_reset = ehea_treat_poll_error(pr, rq, cqe,
							   &processed_rq2,
							   &processed_rq3);
			अगर (port_reset)
				अवरोध;
		पूर्ण
		cqe = ehea_poll_rq1(qp, &wqe_index);
	पूर्ण

	pr->rx_packets += processed;
	pr->rx_bytes += processed_bytes;

	ehea_refill_rq1(pr, last_wqe_index, processed_rq1);
	ehea_refill_rq2(pr, processed_rq2);
	ehea_refill_rq3(pr, processed_rq3);

	वापस processed;
पूर्ण

#घोषणा SWQE_RESTART_CHECK 0xdeadbeaff00d0000ull

अटल व्योम reset_sq_restart_flag(काष्ठा ehea_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < port->num_def_qps; i++) अणु
		काष्ठा ehea_port_res *pr = &port->port_res[i];
		pr->sq_restart_flag = 0;
	पूर्ण
	wake_up(&port->restart_wq);
पूर्ण

अटल व्योम check_sqs(काष्ठा ehea_port *port)
अणु
	काष्ठा ehea_swqe *swqe;
	पूर्णांक swqe_index;
	पूर्णांक i;

	क्रम (i = 0; i < port->num_def_qps; i++) अणु
		काष्ठा ehea_port_res *pr = &port->port_res[i];
		पूर्णांक ret;
		swqe = ehea_get_swqe(pr->qp, &swqe_index);
		स_रखो(swqe, 0, SWQE_HEADER_SIZE);
		atomic_dec(&pr->swqe_avail);

		swqe->tx_control |= EHEA_SWQE_PURGE;
		swqe->wr_id = SWQE_RESTART_CHECK;
		swqe->tx_control |= EHEA_SWQE_SIGNALLED_COMPLETION;
		swqe->tx_control |= EHEA_SWQE_IMM_DATA_PRESENT;
		swqe->immediate_data_length = 80;

		ehea_post_swqe(pr->qp, swqe);

		ret = रुको_event_समयout(port->restart_wq,
					 pr->sq_restart_flag == 0,
					 msecs_to_jअगरfies(100));

		अगर (!ret) अणु
			pr_err("HW/SW queues out of sync\n");
			ehea_schedule_port_reset(pr->port);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण


अटल काष्ठा ehea_cqe *ehea_proc_cqes(काष्ठा ehea_port_res *pr, पूर्णांक my_quota)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ehea_cq *send_cq = pr->send_cq;
	काष्ठा ehea_cqe *cqe;
	पूर्णांक quota = my_quota;
	पूर्णांक cqe_counter = 0;
	पूर्णांक swqe_av = 0;
	पूर्णांक index;
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(pr->port->netdev,
						pr - &pr->port->port_res[0]);

	cqe = ehea_poll_cq(send_cq);
	जबतक (cqe && (quota > 0)) अणु
		ehea_inc_cq(send_cq);

		cqe_counter++;
		rmb();

		अगर (cqe->wr_id == SWQE_RESTART_CHECK) अणु
			pr->sq_restart_flag = 1;
			swqe_av++;
			अवरोध;
		पूर्ण

		अगर (cqe->status & EHEA_CQE_STAT_ERR_MASK) अणु
			pr_err("Bad send completion status=0x%04X\n",
			       cqe->status);

			अगर (netअगर_msg_tx_err(pr->port))
				ehea_dump(cqe, माप(*cqe), "Send CQE");

			अगर (cqe->status & EHEA_CQE_STAT_RESET_MASK) अणु
				pr_err("Resetting port\n");
				ehea_schedule_port_reset(pr->port);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (netअगर_msg_tx_करोne(pr->port))
			ehea_dump(cqe, माप(*cqe), "CQE");

		अगर (likely(EHEA_BMASK_GET(EHEA_WR_ID_TYPE, cqe->wr_id)
			   == EHEA_SWQE2_TYPE)) अणु

			index = EHEA_BMASK_GET(EHEA_WR_ID_INDEX, cqe->wr_id);
			skb = pr->sq_skba.arr[index];
			dev_consume_skb_any(skb);
			pr->sq_skba.arr[index] = शून्य;
		पूर्ण

		swqe_av += EHEA_BMASK_GET(EHEA_WR_ID_REFILL, cqe->wr_id);
		quota--;

		cqe = ehea_poll_cq(send_cq);
	पूर्ण

	ehea_update_feca(send_cq, cqe_counter);
	atomic_add(swqe_av, &pr->swqe_avail);

	अगर (unlikely(netअगर_tx_queue_stopped(txq) &&
		     (atomic_पढ़ो(&pr->swqe_avail) >= pr->swqe_refill_th))) अणु
		__netअगर_tx_lock(txq, smp_processor_id());
		अगर (netअगर_tx_queue_stopped(txq) &&
		    (atomic_पढ़ो(&pr->swqe_avail) >= pr->swqe_refill_th))
			netअगर_tx_wake_queue(txq);
		__netअगर_tx_unlock(txq);
	पूर्ण

	wake_up(&pr->port->swqe_avail_wq);

	वापस cqe;
पूर्ण

#घोषणा EHEA_POLL_MAX_CQES 65535

अटल पूर्णांक ehea_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ehea_port_res *pr = container_of(napi, काष्ठा ehea_port_res,
						napi);
	काष्ठा net_device *dev = pr->port->netdev;
	काष्ठा ehea_cqe *cqe;
	काष्ठा ehea_cqe *cqe_skb = शून्य;
	पूर्णांक wqe_index;
	पूर्णांक rx = 0;

	cqe_skb = ehea_proc_cqes(pr, EHEA_POLL_MAX_CQES);
	rx += ehea_proc_rwqes(dev, pr, budget - rx);

	जबतक (rx != budget) अणु
		napi_complete(napi);
		ehea_reset_cq_ep(pr->recv_cq);
		ehea_reset_cq_ep(pr->send_cq);
		ehea_reset_cq_n1(pr->recv_cq);
		ehea_reset_cq_n1(pr->send_cq);
		rmb();
		cqe = ehea_poll_rq1(pr->qp, &wqe_index);
		cqe_skb = ehea_poll_cq(pr->send_cq);

		अगर (!cqe && !cqe_skb)
			वापस rx;

		अगर (!napi_reschedule(napi))
			वापस rx;

		cqe_skb = ehea_proc_cqes(pr, EHEA_POLL_MAX_CQES);
		rx += ehea_proc_rwqes(dev, pr, budget - rx);
	पूर्ण

	वापस rx;
पूर्ण

अटल irqवापस_t ehea_recv_irq_handler(पूर्णांक irq, व्योम *param)
अणु
	काष्ठा ehea_port_res *pr = param;

	napi_schedule(&pr->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ehea_qp_aff_irq_handler(पूर्णांक irq, व्योम *param)
अणु
	काष्ठा ehea_port *port = param;
	काष्ठा ehea_eqe *eqe;
	काष्ठा ehea_qp *qp;
	u32 qp_token;
	u64 resource_type, aer, aerr;
	पूर्णांक reset_port = 0;

	eqe = ehea_poll_eq(port->qp_eq);

	जबतक (eqe) अणु
		qp_token = EHEA_BMASK_GET(EHEA_EQE_QP_TOKEN, eqe->entry);
		pr_err("QP aff_err: entry=0x%llx, token=0x%x\n",
		       eqe->entry, qp_token);

		qp = port->port_res[qp_token].qp;

		resource_type = ehea_error_data(port->adapter, qp->fw_handle,
						&aer, &aerr);

		अगर (resource_type == EHEA_AER_RESTYPE_QP) अणु
			अगर ((aer & EHEA_AER_RESET_MASK) ||
			    (aerr & EHEA_AERR_RESET_MASK))
				 reset_port = 1;
		पूर्ण अन्यथा
			reset_port = 1;   /* Reset in हाल of CQ or EQ error */

		eqe = ehea_poll_eq(port->qp_eq);
	पूर्ण

	अगर (reset_port) अणु
		pr_err("Resetting port\n");
		ehea_schedule_port_reset(port);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा ehea_port *ehea_get_port(काष्ठा ehea_adapter *adapter,
				       पूर्णांक logical_port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < EHEA_MAX_PORTS; i++)
		अगर (adapter->port[i])
			अगर (adapter->port[i]->logical_port_id == logical_port)
				वापस adapter->port[i];
	वापस शून्य;
पूर्ण

पूर्णांक ehea_sense_port_attr(काष्ठा ehea_port *port)
अणु
	पूर्णांक ret;
	u64 hret;
	काष्ठा hcp_ehea_port_cb0 *cb0;

	/* may be called via ehea_neq_tasklet() */
	cb0 = (व्योम *)get_zeroed_page(GFP_ATOMIC);
	अगर (!cb0) अणु
		pr_err("no mem for cb0\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	hret = ehea_h_query_ehea_port(port->adapter->handle,
				      port->logical_port_id, H_PORT_CB0,
				      EHEA_BMASK_SET(H_PORT_CB0_ALL, 0xFFFF),
				      cb0);
	अगर (hret != H_SUCCESS) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण

	/* MAC address */
	port->mac_addr = cb0->port_mac_addr << 16;

	अगर (!is_valid_ether_addr((u8 *)&port->mac_addr)) अणु
		ret = -EADDRNOTAVAIL;
		जाओ out_मुक्त;
	पूर्ण

	/* Port speed */
	चयन (cb0->port_speed) अणु
	हाल H_SPEED_10M_H:
		port->port_speed = EHEA_SPEED_10M;
		port->full_duplex = 0;
		अवरोध;
	हाल H_SPEED_10M_F:
		port->port_speed = EHEA_SPEED_10M;
		port->full_duplex = 1;
		अवरोध;
	हाल H_SPEED_100M_H:
		port->port_speed = EHEA_SPEED_100M;
		port->full_duplex = 0;
		अवरोध;
	हाल H_SPEED_100M_F:
		port->port_speed = EHEA_SPEED_100M;
		port->full_duplex = 1;
		अवरोध;
	हाल H_SPEED_1G_F:
		port->port_speed = EHEA_SPEED_1G;
		port->full_duplex = 1;
		अवरोध;
	हाल H_SPEED_10G_F:
		port->port_speed = EHEA_SPEED_10G;
		port->full_duplex = 1;
		अवरोध;
	शेष:
		port->port_speed = 0;
		port->full_duplex = 0;
		अवरोध;
	पूर्ण

	port->स्वतःneg = 1;
	port->num_mcs = cb0->num_शेष_qps;

	/* Number of शेष QPs */
	अगर (use_mcs)
		port->num_def_qps = cb0->num_शेष_qps;
	अन्यथा
		port->num_def_qps = 1;

	अगर (!port->num_def_qps) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	ret = 0;
out_मुक्त:
	अगर (ret || netअगर_msg_probe(port))
		ehea_dump(cb0, माप(*cb0), "ehea_sense_port_attr");
	मुक्त_page((अचिन्हित दीर्घ)cb0);
out:
	वापस ret;
पूर्ण

पूर्णांक ehea_set_portspeed(काष्ठा ehea_port *port, u32 port_speed)
अणु
	काष्ठा hcp_ehea_port_cb4 *cb4;
	u64 hret;
	पूर्णांक ret = 0;

	cb4 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb4) अणु
		pr_err("no mem for cb4\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cb4->port_speed = port_speed;

	netअगर_carrier_off(port->netdev);

	hret = ehea_h_modअगरy_ehea_port(port->adapter->handle,
				       port->logical_port_id,
				       H_PORT_CB4, H_PORT_CB4_SPEED, cb4);
	अगर (hret == H_SUCCESS) अणु
		port->स्वतःneg = port_speed == EHEA_SPEED_AUTONEG ? 1 : 0;

		hret = ehea_h_query_ehea_port(port->adapter->handle,
					      port->logical_port_id,
					      H_PORT_CB4, H_PORT_CB4_SPEED,
					      cb4);
		अगर (hret == H_SUCCESS) अणु
			चयन (cb4->port_speed) अणु
			हाल H_SPEED_10M_H:
				port->port_speed = EHEA_SPEED_10M;
				port->full_duplex = 0;
				अवरोध;
			हाल H_SPEED_10M_F:
				port->port_speed = EHEA_SPEED_10M;
				port->full_duplex = 1;
				अवरोध;
			हाल H_SPEED_100M_H:
				port->port_speed = EHEA_SPEED_100M;
				port->full_duplex = 0;
				अवरोध;
			हाल H_SPEED_100M_F:
				port->port_speed = EHEA_SPEED_100M;
				port->full_duplex = 1;
				अवरोध;
			हाल H_SPEED_1G_F:
				port->port_speed = EHEA_SPEED_1G;
				port->full_duplex = 1;
				अवरोध;
			हाल H_SPEED_10G_F:
				port->port_speed = EHEA_SPEED_10G;
				port->full_duplex = 1;
				अवरोध;
			शेष:
				port->port_speed = 0;
				port->full_duplex = 0;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_err("Failed sensing port speed\n");
			ret = -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hret == H_AUTHORITY) अणु
			pr_info("Hypervisor denied setting port speed\n");
			ret = -EPERM;
		पूर्ण अन्यथा अणु
			ret = -EIO;
			pr_err("Failed setting port speed\n");
		पूर्ण
	पूर्ण
	अगर (!prop_carrier_state || (port->phy_link == EHEA_PHY_LINK_UP))
		netअगर_carrier_on(port->netdev);

	मुक्त_page((अचिन्हित दीर्घ)cb4);
out:
	वापस ret;
पूर्ण

अटल व्योम ehea_parse_eqe(काष्ठा ehea_adapter *adapter, u64 eqe)
अणु
	पूर्णांक ret;
	u8 ec;
	u8 portnum;
	काष्ठा ehea_port *port;
	काष्ठा net_device *dev;

	ec = EHEA_BMASK_GET(NEQE_EVENT_CODE, eqe);
	portnum = EHEA_BMASK_GET(NEQE_PORTNUM, eqe);
	port = ehea_get_port(adapter, portnum);
	अगर (!port) अणु
		netdev_err(शून्य, "unknown portnum %x\n", portnum);
		वापस;
	पूर्ण
	dev = port->netdev;

	चयन (ec) अणु
	हाल EHEA_EC_PORTSTATE_CHG:	/* port state change */

		अगर (EHEA_BMASK_GET(NEQE_PORT_UP, eqe)) अणु
			अगर (!netअगर_carrier_ok(dev)) अणु
				ret = ehea_sense_port_attr(port);
				अगर (ret) अणु
					netdev_err(dev, "failed resensing port attributes\n");
					अवरोध;
				पूर्ण

				netअगर_info(port, link, dev,
					   "Logical port up: %dMbps %s Duplex\n",
					   port->port_speed,
					   port->full_duplex == 1 ?
					   "Full" : "Half");

				netअगर_carrier_on(dev);
				netअगर_wake_queue(dev);
			पूर्ण
		पूर्ण अन्यथा
			अगर (netअगर_carrier_ok(dev)) अणु
				netअगर_info(port, link, dev,
					   "Logical port down\n");
				netअगर_carrier_off(dev);
				netअगर_tx_disable(dev);
			पूर्ण

		अगर (EHEA_BMASK_GET(NEQE_EXTSWITCH_PORT_UP, eqe)) अणु
			port->phy_link = EHEA_PHY_LINK_UP;
			netअगर_info(port, link, dev,
				   "Physical port up\n");
			अगर (prop_carrier_state)
				netअगर_carrier_on(dev);
		पूर्ण अन्यथा अणु
			port->phy_link = EHEA_PHY_LINK_DOWN;
			netअगर_info(port, link, dev,
				   "Physical port down\n");
			अगर (prop_carrier_state)
				netअगर_carrier_off(dev);
		पूर्ण

		अगर (EHEA_BMASK_GET(NEQE_EXTSWITCH_PRIMARY, eqe))
			netdev_info(dev,
				    "External switch port is primary port\n");
		अन्यथा
			netdev_info(dev,
				    "External switch port is backup port\n");

		अवरोध;
	हाल EHEA_EC_ADAPTER_MALFUNC:
		netdev_err(dev, "Adapter malfunction\n");
		अवरोध;
	हाल EHEA_EC_PORT_MALFUNC:
		netdev_info(dev, "Port malfunction\n");
		netअगर_carrier_off(dev);
		netअगर_tx_disable(dev);
		अवरोध;
	शेष:
		netdev_err(dev, "unknown event code %x, eqe=0x%llX\n", ec, eqe);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ehea_neq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ehea_adapter *adapter = from_tasklet(adapter, t, neq_tasklet);
	काष्ठा ehea_eqe *eqe;
	u64 event_mask;

	eqe = ehea_poll_eq(adapter->neq);
	pr_debug("eqe=%p\n", eqe);

	जबतक (eqe) अणु
		pr_debug("*eqe=%lx\n", (अचिन्हित दीर्घ) eqe->entry);
		ehea_parse_eqe(adapter, eqe->entry);
		eqe = ehea_poll_eq(adapter->neq);
		pr_debug("next eqe=%p\n", eqe);
	पूर्ण

	event_mask = EHEA_BMASK_SET(NELR_PORTSTATE_CHG, 1)
		   | EHEA_BMASK_SET(NELR_ADAPTER_MALFUNC, 1)
		   | EHEA_BMASK_SET(NELR_PORT_MALFUNC, 1);

	ehea_h_reset_events(adapter->handle,
			    adapter->neq->fw_handle, event_mask);
पूर्ण

अटल irqवापस_t ehea_पूर्णांकerrupt_neq(पूर्णांक irq, व्योम *param)
अणु
	काष्ठा ehea_adapter *adapter = param;
	tasklet_hi_schedule(&adapter->neq_tasklet);
	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक ehea_fill_port_res(काष्ठा ehea_port_res *pr)
अणु
	पूर्णांक ret;
	काष्ठा ehea_qp_init_attr *init_attr = &pr->qp->init_attr;

	ehea_init_fill_rq1(pr, pr->rq1_skba.len);

	ret = ehea_refill_rq2(pr, init_attr->act_nr_rwqes_rq2 - 1);

	ret |= ehea_refill_rq3(pr, init_attr->act_nr_rwqes_rq3 - 1);

	वापस ret;
पूर्ण

अटल पूर्णांक ehea_reg_पूर्णांकerrupts(काष्ठा net_device *dev)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा ehea_port_res *pr;
	पूर्णांक i, ret;


	snम_लिखो(port->पूर्णांक_aff_name, EHEA_IRQ_NAME_SIZE - 1, "%s-aff",
		 dev->name);

	ret = ibmebus_request_irq(port->qp_eq->attr.ist1,
				  ehea_qp_aff_irq_handler,
				  0, port->पूर्णांक_aff_name, port);
	अगर (ret) अणु
		netdev_err(dev, "failed registering irq for qp_aff_irq_handler:ist=%X\n",
			   port->qp_eq->attr.ist1);
		जाओ out_मुक्त_qpeq;
	पूर्ण

	netअगर_info(port, अगरup, dev,
		   "irq_handle 0x%X for function qp_aff_irq_handler registered\n",
		   port->qp_eq->attr.ist1);


	क्रम (i = 0; i < port->num_def_qps; i++) अणु
		pr = &port->port_res[i];
		snम_लिखो(pr->पूर्णांक_send_name, EHEA_IRQ_NAME_SIZE - 1,
			 "%s-queue%d", dev->name, i);
		ret = ibmebus_request_irq(pr->eq->attr.ist1,
					  ehea_recv_irq_handler,
					  0, pr->पूर्णांक_send_name, pr);
		अगर (ret) अणु
			netdev_err(dev, "failed registering irq for ehea_queue port_res_nr:%d, ist=%X\n",
				   i, pr->eq->attr.ist1);
			जाओ out_मुक्त_req;
		पूर्ण
		netअगर_info(port, अगरup, dev,
			   "irq_handle 0x%X for function ehea_queue_int %d registered\n",
			   pr->eq->attr.ist1, i);
	पूर्ण
out:
	वापस ret;


out_मुक्त_req:
	जबतक (--i >= 0) अणु
		u32 ist = port->port_res[i].eq->attr.ist1;
		ibmebus_मुक्त_irq(ist, &port->port_res[i]);
	पूर्ण

out_मुक्त_qpeq:
	ibmebus_मुक्त_irq(port->qp_eq->attr.ist1, port);
	i = port->num_def_qps;

	जाओ out;

पूर्ण

अटल व्योम ehea_मुक्त_पूर्णांकerrupts(काष्ठा net_device *dev)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा ehea_port_res *pr;
	पूर्णांक i;

	/* send */

	क्रम (i = 0; i < port->num_def_qps; i++) अणु
		pr = &port->port_res[i];
		ibmebus_मुक्त_irq(pr->eq->attr.ist1, pr);
		netअगर_info(port, पूर्णांकr, dev,
			   "free send irq for res %d with handle 0x%X\n",
			   i, pr->eq->attr.ist1);
	पूर्ण

	/* associated events */
	ibmebus_मुक्त_irq(port->qp_eq->attr.ist1, port);
	netअगर_info(port, पूर्णांकr, dev,
		   "associated event interrupt for handle 0x%X freed\n",
		   port->qp_eq->attr.ist1);
पूर्ण

अटल पूर्णांक ehea_configure_port(काष्ठा ehea_port *port)
अणु
	पूर्णांक ret, i;
	u64 hret, mask;
	काष्ठा hcp_ehea_port_cb0 *cb0;

	ret = -ENOMEM;
	cb0 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb0)
		जाओ out;

	cb0->port_rc = EHEA_BMASK_SET(PXLY_RC_VALID, 1)
		     | EHEA_BMASK_SET(PXLY_RC_IP_CHKSUM, 1)
		     | EHEA_BMASK_SET(PXLY_RC_TCP_UDP_CHKSUM, 1)
		     | EHEA_BMASK_SET(PXLY_RC_VLAN_XTRACT, 1)
		     | EHEA_BMASK_SET(PXLY_RC_VLAN_TAG_FILTER,
				      PXLY_RC_VLAN_FILTER)
		     | EHEA_BMASK_SET(PXLY_RC_JUMBO_FRAME, 1);

	क्रम (i = 0; i < port->num_mcs; i++)
		अगर (use_mcs)
			cb0->शेष_qpn_arr[i] =
				port->port_res[i].qp->init_attr.qp_nr;
		अन्यथा
			cb0->शेष_qpn_arr[i] =
				port->port_res[0].qp->init_attr.qp_nr;

	अगर (netअगर_msg_अगरup(port))
		ehea_dump(cb0, माप(*cb0), "ehea_configure_port");

	mask = EHEA_BMASK_SET(H_PORT_CB0_PRC, 1)
	     | EHEA_BMASK_SET(H_PORT_CB0_DEFQPNARRAY, 1);

	hret = ehea_h_modअगरy_ehea_port(port->adapter->handle,
				       port->logical_port_id,
				       H_PORT_CB0, mask, cb0);
	ret = -EIO;
	अगर (hret != H_SUCCESS)
		जाओ out_मुक्त;

	ret = 0;

out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ)cb0);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ehea_gen_smrs(काष्ठा ehea_port_res *pr)
अणु
	पूर्णांक ret;
	काष्ठा ehea_adapter *adapter = pr->port->adapter;

	ret = ehea_gen_smr(adapter, &adapter->mr, &pr->send_mr);
	अगर (ret)
		जाओ out;

	ret = ehea_gen_smr(adapter, &adapter->mr, &pr->recv_mr);
	अगर (ret)
		जाओ out_मुक्त;

	वापस 0;

out_मुक्त:
	ehea_rem_mr(&pr->send_mr);
out:
	pr_err("Generating SMRS failed\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक ehea_rem_smrs(काष्ठा ehea_port_res *pr)
अणु
	अगर ((ehea_rem_mr(&pr->send_mr)) ||
	    (ehea_rem_mr(&pr->recv_mr)))
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक ehea_init_q_skba(काष्ठा ehea_q_skb_arr *q_skba, पूर्णांक max_q_entries)
अणु
	पूर्णांक arr_size = माप(व्योम *) * max_q_entries;

	q_skba->arr = vzalloc(arr_size);
	अगर (!q_skba->arr)
		वापस -ENOMEM;

	q_skba->len = max_q_entries;
	q_skba->index = 0;
	q_skba->os_skbs = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ehea_init_port_res(काष्ठा ehea_port *port, काष्ठा ehea_port_res *pr,
			      काष्ठा port_res_cfg *pr_cfg, पूर्णांक queue_token)
अणु
	काष्ठा ehea_adapter *adapter = port->adapter;
	क्रमागत ehea_eq_type eq_type = EHEA_EQ;
	काष्ठा ehea_qp_init_attr *init_attr = शून्य;
	पूर्णांक ret = -EIO;
	u64 tx_bytes, rx_bytes, tx_packets, rx_packets;

	tx_bytes = pr->tx_bytes;
	tx_packets = pr->tx_packets;
	rx_bytes = pr->rx_bytes;
	rx_packets = pr->rx_packets;

	स_रखो(pr, 0, माप(काष्ठा ehea_port_res));

	pr->tx_bytes = tx_bytes;
	pr->tx_packets = tx_packets;
	pr->rx_bytes = rx_bytes;
	pr->rx_packets = rx_packets;

	pr->port = port;

	pr->eq = ehea_create_eq(adapter, eq_type, EHEA_MAX_ENTRIES_EQ, 0);
	अगर (!pr->eq) अणु
		pr_err("create_eq failed (eq)\n");
		जाओ out_मुक्त;
	पूर्ण

	pr->recv_cq = ehea_create_cq(adapter, pr_cfg->max_entries_rcq,
				     pr->eq->fw_handle,
				     port->logical_port_id);
	अगर (!pr->recv_cq) अणु
		pr_err("create_cq failed (cq_recv)\n");
		जाओ out_मुक्त;
	पूर्ण

	pr->send_cq = ehea_create_cq(adapter, pr_cfg->max_entries_scq,
				     pr->eq->fw_handle,
				     port->logical_port_id);
	अगर (!pr->send_cq) अणु
		pr_err("create_cq failed (cq_send)\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (netअगर_msg_अगरup(port))
		pr_info("Send CQ: act_nr_cqes=%d, Recv CQ: act_nr_cqes=%d\n",
			pr->send_cq->attr.act_nr_of_cqes,
			pr->recv_cq->attr.act_nr_of_cqes);

	init_attr = kzalloc(माप(*init_attr), GFP_KERNEL);
	अगर (!init_attr) अणु
		ret = -ENOMEM;
		pr_err("no mem for ehea_qp_init_attr\n");
		जाओ out_मुक्त;
	पूर्ण

	init_attr->low_lat_rq1 = 1;
	init_attr->संकेतingtype = 1;	/* generate CQE अगर specअगरied in WQE */
	init_attr->rq_count = 3;
	init_attr->qp_token = queue_token;
	init_attr->max_nr_send_wqes = pr_cfg->max_entries_sq;
	init_attr->max_nr_rwqes_rq1 = pr_cfg->max_entries_rq1;
	init_attr->max_nr_rwqes_rq2 = pr_cfg->max_entries_rq2;
	init_attr->max_nr_rwqes_rq3 = pr_cfg->max_entries_rq3;
	init_attr->wqe_size_enc_sq = EHEA_SG_SQ;
	init_attr->wqe_size_enc_rq1 = EHEA_SG_RQ1;
	init_attr->wqe_size_enc_rq2 = EHEA_SG_RQ2;
	init_attr->wqe_size_enc_rq3 = EHEA_SG_RQ3;
	init_attr->rq2_threshold = EHEA_RQ2_THRESHOLD;
	init_attr->rq3_threshold = EHEA_RQ3_THRESHOLD;
	init_attr->port_nr = port->logical_port_id;
	init_attr->send_cq_handle = pr->send_cq->fw_handle;
	init_attr->recv_cq_handle = pr->recv_cq->fw_handle;
	init_attr->aff_eq_handle = port->qp_eq->fw_handle;

	pr->qp = ehea_create_qp(adapter, adapter->pd, init_attr);
	अगर (!pr->qp) अणु
		pr_err("create_qp failed\n");
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण

	अगर (netअगर_msg_अगरup(port))
		pr_info("QP: qp_nr=%d\n act_nr_snd_wqe=%d\n nr_rwqe_rq1=%d\n nr_rwqe_rq2=%d\n nr_rwqe_rq3=%d\n",
			init_attr->qp_nr,
			init_attr->act_nr_send_wqes,
			init_attr->act_nr_rwqes_rq1,
			init_attr->act_nr_rwqes_rq2,
			init_attr->act_nr_rwqes_rq3);

	pr->sq_skba_size = init_attr->act_nr_send_wqes + 1;

	ret = ehea_init_q_skba(&pr->sq_skba, pr->sq_skba_size);
	ret |= ehea_init_q_skba(&pr->rq1_skba, init_attr->act_nr_rwqes_rq1 + 1);
	ret |= ehea_init_q_skba(&pr->rq2_skba, init_attr->act_nr_rwqes_rq2 + 1);
	ret |= ehea_init_q_skba(&pr->rq3_skba, init_attr->act_nr_rwqes_rq3 + 1);
	अगर (ret)
		जाओ out_मुक्त;

	pr->swqe_refill_th = init_attr->act_nr_send_wqes / 10;
	अगर (ehea_gen_smrs(pr) != 0) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण

	atomic_set(&pr->swqe_avail, init_attr->act_nr_send_wqes - 1);

	kमुक्त(init_attr);

	netअगर_napi_add(pr->port->netdev, &pr->napi, ehea_poll, 64);

	ret = 0;
	जाओ out;

out_मुक्त:
	kमुक्त(init_attr);
	vमुक्त(pr->sq_skba.arr);
	vमुक्त(pr->rq1_skba.arr);
	vमुक्त(pr->rq2_skba.arr);
	vमुक्त(pr->rq3_skba.arr);
	ehea_destroy_qp(pr->qp);
	ehea_destroy_cq(pr->send_cq);
	ehea_destroy_cq(pr->recv_cq);
	ehea_destroy_eq(pr->eq);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ehea_clean_portres(काष्ठा ehea_port *port, काष्ठा ehea_port_res *pr)
अणु
	पूर्णांक ret, i;

	अगर (pr->qp)
		netअगर_napi_del(&pr->napi);

	ret = ehea_destroy_qp(pr->qp);

	अगर (!ret) अणु
		ehea_destroy_cq(pr->send_cq);
		ehea_destroy_cq(pr->recv_cq);
		ehea_destroy_eq(pr->eq);

		क्रम (i = 0; i < pr->rq1_skba.len; i++)
			dev_kमुक्त_skb(pr->rq1_skba.arr[i]);

		क्रम (i = 0; i < pr->rq2_skba.len; i++)
			dev_kमुक्त_skb(pr->rq2_skba.arr[i]);

		क्रम (i = 0; i < pr->rq3_skba.len; i++)
			dev_kमुक्त_skb(pr->rq3_skba.arr[i]);

		क्रम (i = 0; i < pr->sq_skba.len; i++)
			dev_kमुक्त_skb(pr->sq_skba.arr[i]);

		vमुक्त(pr->rq1_skba.arr);
		vमुक्त(pr->rq2_skba.arr);
		vमुक्त(pr->rq3_skba.arr);
		vमुक्त(pr->sq_skba.arr);
		ret = ehea_rem_smrs(pr);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ग_लिखो_swqe2_immediate(काष्ठा sk_buff *skb, काष्ठा ehea_swqe *swqe,
				  u32 lkey)
अणु
	पूर्णांक skb_data_size = skb_headlen(skb);
	u8 *imm_data = &swqe->u.immdata_desc.immediate_data[0];
	काष्ठा ehea_vsgentry *sg1entry = &swqe->u.immdata_desc.sg_entry;
	अचिन्हित पूर्णांक immediate_len = SWQE2_MAX_IMM;

	swqe->descriptors = 0;

	अगर (skb_is_gso(skb)) अणु
		swqe->tx_control |= EHEA_SWQE_TSO;
		swqe->mss = skb_shinfo(skb)->gso_size;
		/*
		 * For TSO packets we only copy the headers पूर्णांकo the
		 * immediate area.
		 */
		immediate_len = ETH_HLEN + ip_hdrlen(skb) + tcp_hdrlen(skb);
	पूर्ण

	अगर (skb_is_gso(skb) || skb_data_size >= SWQE2_MAX_IMM) अणु
		skb_copy_from_linear_data(skb, imm_data, immediate_len);
		swqe->immediate_data_length = immediate_len;

		अगर (skb_data_size > immediate_len) अणु
			sg1entry->l_key = lkey;
			sg1entry->len = skb_data_size - immediate_len;
			sg1entry->vaddr =
				ehea_map_vaddr(skb->data + immediate_len);
			swqe->descriptors++;
		पूर्ण
	पूर्ण अन्यथा अणु
		skb_copy_from_linear_data(skb, imm_data, skb_data_size);
		swqe->immediate_data_length = skb_data_size;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_swqe2_data(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				    काष्ठा ehea_swqe *swqe, u32 lkey)
अणु
	काष्ठा ehea_vsgentry *sg_list, *sg1entry, *sgentry;
	skb_frag_t *frag;
	पूर्णांक nfrags, sg1entry_contains_frag_data, i;

	nfrags = skb_shinfo(skb)->nr_frags;
	sg1entry = &swqe->u.immdata_desc.sg_entry;
	sg_list = (काष्ठा ehea_vsgentry *)&swqe->u.immdata_desc.sg_list;
	sg1entry_contains_frag_data = 0;

	ग_लिखो_swqe2_immediate(skb, swqe, lkey);

	/* ग_लिखो descriptors */
	अगर (nfrags > 0) अणु
		अगर (swqe->descriptors == 0) अणु
			/* sg1entry not yet used */
			frag = &skb_shinfo(skb)->frags[0];

			/* copy sg1entry data */
			sg1entry->l_key = lkey;
			sg1entry->len = skb_frag_size(frag);
			sg1entry->vaddr =
				ehea_map_vaddr(skb_frag_address(frag));
			swqe->descriptors++;
			sg1entry_contains_frag_data = 1;
		पूर्ण

		क्रम (i = sg1entry_contains_frag_data; i < nfrags; i++) अणु

			frag = &skb_shinfo(skb)->frags[i];
			sgentry = &sg_list[i - sg1entry_contains_frag_data];

			sgentry->l_key = lkey;
			sgentry->len = skb_frag_size(frag);
			sgentry->vaddr = ehea_map_vaddr(skb_frag_address(frag));
			swqe->descriptors++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ehea_broadcast_reg_helper(काष्ठा ehea_port *port, u32 hcallid)
अणु
	पूर्णांक ret = 0;
	u64 hret;
	u8 reg_type;

	/* De/Register untagged packets */
	reg_type = EHEA_BCMC_BROADCAST | EHEA_BCMC_UNTAGGED;
	hret = ehea_h_reg_dereg_bcmc(port->adapter->handle,
				     port->logical_port_id,
				     reg_type, port->mac_addr, 0, hcallid);
	अगर (hret != H_SUCCESS) अणु
		pr_err("%sregistering bc address failed (tagged)\n",
		       hcallid == H_REG_BCMC ? "" : "de");
		ret = -EIO;
		जाओ out_herr;
	पूर्ण

	/* De/Register VLAN packets */
	reg_type = EHEA_BCMC_BROADCAST | EHEA_BCMC_VLANID_ALL;
	hret = ehea_h_reg_dereg_bcmc(port->adapter->handle,
				     port->logical_port_id,
				     reg_type, port->mac_addr, 0, hcallid);
	अगर (hret != H_SUCCESS) अणु
		pr_err("%sregistering bc address failed (vlan)\n",
		       hcallid == H_REG_BCMC ? "" : "de");
		ret = -EIO;
	पूर्ण
out_herr:
	वापस ret;
पूर्ण

अटल पूर्णांक ehea_set_mac_addr(काष्ठा net_device *dev, व्योम *sa)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा sockaddr *mac_addr = sa;
	काष्ठा hcp_ehea_port_cb0 *cb0;
	पूर्णांक ret;
	u64 hret;

	अगर (!is_valid_ether_addr(mac_addr->sa_data)) अणु
		ret = -EADDRNOTAVAIL;
		जाओ out;
	पूर्ण

	cb0 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb0) अणु
		pr_err("no mem for cb0\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(&(cb0->port_mac_addr), &(mac_addr->sa_data[0]), ETH_ALEN);

	cb0->port_mac_addr = cb0->port_mac_addr >> 16;

	hret = ehea_h_modअगरy_ehea_port(port->adapter->handle,
				       port->logical_port_id, H_PORT_CB0,
				       EHEA_BMASK_SET(H_PORT_CB0_MAC, 1), cb0);
	अगर (hret != H_SUCCESS) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण

	स_नकल(dev->dev_addr, mac_addr->sa_data, dev->addr_len);

	/* Deरेजिस्टर old MAC in pHYP */
	अगर (port->state == EHEA_PORT_UP) अणु
		ret = ehea_broadcast_reg_helper(port, H_DEREG_BCMC);
		अगर (ret)
			जाओ out_upregs;
	पूर्ण

	port->mac_addr = cb0->port_mac_addr << 16;

	/* Register new MAC in pHYP */
	अगर (port->state == EHEA_PORT_UP) अणु
		ret = ehea_broadcast_reg_helper(port, H_REG_BCMC);
		अगर (ret)
			जाओ out_upregs;
	पूर्ण

	ret = 0;

out_upregs:
	ehea_update_bcmc_registrations();
out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ)cb0);
out:
	वापस ret;
पूर्ण

अटल व्योम ehea_promiscuous_error(u64 hret, पूर्णांक enable)
अणु
	अगर (hret == H_AUTHORITY)
		pr_info("Hypervisor denied %sabling promiscuous mode\n",
			enable == 1 ? "en" : "dis");
	अन्यथा
		pr_err("failed %sabling promiscuous mode\n",
		       enable == 1 ? "en" : "dis");
पूर्ण

अटल व्योम ehea_promiscuous(काष्ठा net_device *dev, पूर्णांक enable)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा hcp_ehea_port_cb7 *cb7;
	u64 hret;

	अगर (enable == port->promisc)
		वापस;

	cb7 = (व्योम *)get_zeroed_page(GFP_ATOMIC);
	अगर (!cb7) अणु
		pr_err("no mem for cb7\n");
		जाओ out;
	पूर्ण

	/* Modअगरy Pxs_DUCQPN in CB7 */
	cb7->def_uc_qpn = enable == 1 ? port->port_res[0].qp->fw_handle : 0;

	hret = ehea_h_modअगरy_ehea_port(port->adapter->handle,
				       port->logical_port_id,
				       H_PORT_CB7, H_PORT_CB7_DUCQPN, cb7);
	अगर (hret) अणु
		ehea_promiscuous_error(hret, enable);
		जाओ out;
	पूर्ण

	port->promisc = enable;
out:
	मुक्त_page((अचिन्हित दीर्घ)cb7);
पूर्ण

अटल u64 ehea_multicast_reg_helper(काष्ठा ehea_port *port, u64 mc_mac_addr,
				     u32 hcallid)
अणु
	u64 hret;
	u8 reg_type;

	reg_type = EHEA_BCMC_MULTICAST | EHEA_BCMC_UNTAGGED;
	अगर (mc_mac_addr == 0)
		reg_type |= EHEA_BCMC_SCOPE_ALL;

	hret = ehea_h_reg_dereg_bcmc(port->adapter->handle,
				     port->logical_port_id,
				     reg_type, mc_mac_addr, 0, hcallid);
	अगर (hret)
		जाओ out;

	reg_type = EHEA_BCMC_MULTICAST | EHEA_BCMC_VLANID_ALL;
	अगर (mc_mac_addr == 0)
		reg_type |= EHEA_BCMC_SCOPE_ALL;

	hret = ehea_h_reg_dereg_bcmc(port->adapter->handle,
				     port->logical_port_id,
				     reg_type, mc_mac_addr, 0, hcallid);
out:
	वापस hret;
पूर्ण

अटल पूर्णांक ehea_drop_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा ehea_mc_list *mc_entry = port->mc_list;
	काष्ठा list_head *pos;
	काष्ठा list_head *temp;
	पूर्णांक ret = 0;
	u64 hret;

	list_क्रम_each_safe(pos, temp, &(port->mc_list->list)) अणु
		mc_entry = list_entry(pos, काष्ठा ehea_mc_list, list);

		hret = ehea_multicast_reg_helper(port, mc_entry->macaddr,
						 H_DEREG_BCMC);
		अगर (hret) अणु
			pr_err("failed deregistering mcast MAC\n");
			ret = -EIO;
		पूर्ण

		list_del(pos);
		kमुक्त(mc_entry);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ehea_allmulti(काष्ठा net_device *dev, पूर्णांक enable)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	u64 hret;

	अगर (!port->allmulti) अणु
		अगर (enable) अणु
			/* Enable ALLMULTI */
			ehea_drop_multicast_list(dev);
			hret = ehea_multicast_reg_helper(port, 0, H_REG_BCMC);
			अगर (!hret)
				port->allmulti = 1;
			अन्यथा
				netdev_err(dev,
					   "failed enabling IFF_ALLMULTI\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!enable) अणु
			/* Disable ALLMULTI */
			hret = ehea_multicast_reg_helper(port, 0, H_DEREG_BCMC);
			अगर (!hret)
				port->allmulti = 0;
			अन्यथा
				netdev_err(dev,
					   "failed disabling IFF_ALLMULTI\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ehea_add_multicast_entry(काष्ठा ehea_port *port, u8 *mc_mac_addr)
अणु
	काष्ठा ehea_mc_list *ehea_mcl_entry;
	u64 hret;

	ehea_mcl_entry = kzalloc(माप(*ehea_mcl_entry), GFP_ATOMIC);
	अगर (!ehea_mcl_entry)
		वापस;

	INIT_LIST_HEAD(&ehea_mcl_entry->list);

	स_नकल(&ehea_mcl_entry->macaddr, mc_mac_addr, ETH_ALEN);

	hret = ehea_multicast_reg_helper(port, ehea_mcl_entry->macaddr,
					 H_REG_BCMC);
	अगर (!hret)
		list_add(&ehea_mcl_entry->list, &port->mc_list->list);
	अन्यथा अणु
		pr_err("failed registering mcast MAC\n");
		kमुक्त(ehea_mcl_entry);
	पूर्ण
पूर्ण

अटल व्योम ehea_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक ret;

	ehea_promiscuous(dev, !!(dev->flags & IFF_PROMISC));

	अगर (dev->flags & IFF_ALLMULTI) अणु
		ehea_allmulti(dev, 1);
		जाओ out;
	पूर्ण
	ehea_allmulti(dev, 0);

	अगर (!netdev_mc_empty(dev)) अणु
		ret = ehea_drop_multicast_list(dev);
		अगर (ret) अणु
			/* Dropping the current multicast list failed.
			 * Enabling ALL_MULTI is the best we can करो.
			 */
			ehea_allmulti(dev, 1);
		पूर्ण

		अगर (netdev_mc_count(dev) > port->adapter->max_mc_mac) अणु
			pr_info("Mcast registration limit reached (0x%llx). Use ALLMULTI!\n",
				port->adapter->max_mc_mac);
			जाओ out;
		पूर्ण

		netdev_क्रम_each_mc_addr(ha, dev)
			ehea_add_multicast_entry(port, ha->addr);

	पूर्ण
out:
	ehea_update_bcmc_registrations();
पूर्ण

अटल व्योम xmit_common(काष्ठा sk_buff *skb, काष्ठा ehea_swqe *swqe)
अणु
	swqe->tx_control |= EHEA_SWQE_IMM_DATA_PRESENT | EHEA_SWQE_CRC;

	अगर (vlan_get_protocol(skb) != htons(ETH_P_IP))
		वापस;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		swqe->tx_control |= EHEA_SWQE_IP_CHECKSUM;

	swqe->ip_start = skb_network_offset(skb);
	swqe->ip_end = swqe->ip_start + ip_hdrlen(skb) - 1;

	चयन (ip_hdr(skb)->protocol) अणु
	हाल IPPROTO_UDP:
		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			swqe->tx_control |= EHEA_SWQE_TCP_CHECKSUM;

		swqe->tcp_offset = swqe->ip_end + 1 +
				   दुरत्व(काष्ठा udphdr, check);
		अवरोध;

	हाल IPPROTO_TCP:
		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			swqe->tx_control |= EHEA_SWQE_TCP_CHECKSUM;

		swqe->tcp_offset = swqe->ip_end + 1 +
				   दुरत्व(काष्ठा tcphdr, check);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ehea_xmit2(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       काष्ठा ehea_swqe *swqe, u32 lkey)
अणु
	swqe->tx_control |= EHEA_SWQE_DESCRIPTORS_PRESENT;

	xmit_common(skb, swqe);

	ग_लिखो_swqe2_data(skb, dev, swqe, lkey);
पूर्ण

अटल व्योम ehea_xmit3(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       काष्ठा ehea_swqe *swqe)
अणु
	u8 *imm_data = &swqe->u.immdata_nodesc.immediate_data[0];

	xmit_common(skb, swqe);

	अगर (!skb->data_len)
		skb_copy_from_linear_data(skb, imm_data, skb->len);
	अन्यथा
		skb_copy_bits(skb, 0, imm_data, skb->len);

	swqe->immediate_data_length = skb->len;
	dev_consume_skb_any(skb);
पूर्ण

अटल netdev_tx_t ehea_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा ehea_swqe *swqe;
	u32 lkey;
	पूर्णांक swqe_index;
	काष्ठा ehea_port_res *pr;
	काष्ठा netdev_queue *txq;

	pr = &port->port_res[skb_get_queue_mapping(skb)];
	txq = netdev_get_tx_queue(dev, skb_get_queue_mapping(skb));

	swqe = ehea_get_swqe(pr->qp, &swqe_index);
	स_रखो(swqe, 0, SWQE_HEADER_SIZE);
	atomic_dec(&pr->swqe_avail);

	अगर (skb_vlan_tag_present(skb)) अणु
		swqe->tx_control |= EHEA_SWQE_VLAN_INSERT;
		swqe->vlan_tag = skb_vlan_tag_get(skb);
	पूर्ण

	pr->tx_packets++;
	pr->tx_bytes += skb->len;

	अगर (skb->len <= SWQE3_MAX_IMM) अणु
		u32 sig_iv = port->sig_comp_iv;
		u32 swqe_num = pr->swqe_id_counter;
		ehea_xmit3(skb, dev, swqe);
		swqe->wr_id = EHEA_BMASK_SET(EHEA_WR_ID_TYPE, EHEA_SWQE3_TYPE)
			| EHEA_BMASK_SET(EHEA_WR_ID_COUNT, swqe_num);
		अगर (pr->swqe_ll_count >= (sig_iv - 1)) अणु
			swqe->wr_id |= EHEA_BMASK_SET(EHEA_WR_ID_REFILL,
						      sig_iv);
			swqe->tx_control |= EHEA_SWQE_SIGNALLED_COMPLETION;
			pr->swqe_ll_count = 0;
		पूर्ण अन्यथा
			pr->swqe_ll_count += 1;
	पूर्ण अन्यथा अणु
		swqe->wr_id =
			EHEA_BMASK_SET(EHEA_WR_ID_TYPE, EHEA_SWQE2_TYPE)
		      | EHEA_BMASK_SET(EHEA_WR_ID_COUNT, pr->swqe_id_counter)
		      | EHEA_BMASK_SET(EHEA_WR_ID_REFILL, 1)
		      | EHEA_BMASK_SET(EHEA_WR_ID_INDEX, pr->sq_skba.index);
		pr->sq_skba.arr[pr->sq_skba.index] = skb;

		pr->sq_skba.index++;
		pr->sq_skba.index &= (pr->sq_skba.len - 1);

		lkey = pr->send_mr.lkey;
		ehea_xmit2(skb, dev, swqe, lkey);
		swqe->tx_control |= EHEA_SWQE_SIGNALLED_COMPLETION;
	पूर्ण
	pr->swqe_id_counter += 1;

	netअगर_info(port, tx_queued, dev,
		   "post swqe on QP %d\n", pr->qp->init_attr.qp_nr);
	अगर (netअगर_msg_tx_queued(port))
		ehea_dump(swqe, 512, "swqe");

	अगर (unlikely(test_bit(__EHEA_STOP_XFER, &ehea_driver_flags))) अणु
		netअगर_tx_stop_queue(txq);
		swqe->tx_control |= EHEA_SWQE_PURGE;
	पूर्ण

	ehea_post_swqe(pr->qp, swqe);

	अगर (unlikely(atomic_पढ़ो(&pr->swqe_avail) <= 1)) अणु
		pr->p_stats.queue_stopped++;
		netअगर_tx_stop_queue(txq);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ehea_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा ehea_adapter *adapter = port->adapter;
	काष्ठा hcp_ehea_port_cb1 *cb1;
	पूर्णांक index;
	u64 hret;
	पूर्णांक err = 0;

	cb1 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb1) अणु
		pr_err("no mem for cb1\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	hret = ehea_h_query_ehea_port(adapter->handle, port->logical_port_id,
				      H_PORT_CB1, H_PORT_CB1_ALL, cb1);
	अगर (hret != H_SUCCESS) अणु
		pr_err("query_ehea_port failed\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	index = (vid / 64);
	cb1->vlan_filter[index] |= ((u64)(0x8000000000000000 >> (vid & 0x3F)));

	hret = ehea_h_modअगरy_ehea_port(adapter->handle, port->logical_port_id,
				       H_PORT_CB1, H_PORT_CB1_ALL, cb1);
	अगर (hret != H_SUCCESS) अणु
		pr_err("modify_ehea_port failed\n");
		err = -EINVAL;
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ)cb1);
	वापस err;
पूर्ण

अटल पूर्णांक ehea_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा ehea_adapter *adapter = port->adapter;
	काष्ठा hcp_ehea_port_cb1 *cb1;
	पूर्णांक index;
	u64 hret;
	पूर्णांक err = 0;

	cb1 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb1) अणु
		pr_err("no mem for cb1\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	hret = ehea_h_query_ehea_port(adapter->handle, port->logical_port_id,
				      H_PORT_CB1, H_PORT_CB1_ALL, cb1);
	अगर (hret != H_SUCCESS) अणु
		pr_err("query_ehea_port failed\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	index = (vid / 64);
	cb1->vlan_filter[index] &= ~((u64)(0x8000000000000000 >> (vid & 0x3F)));

	hret = ehea_h_modअगरy_ehea_port(adapter->handle, port->logical_port_id,
				       H_PORT_CB1, H_PORT_CB1_ALL, cb1);
	अगर (hret != H_SUCCESS) अणु
		pr_err("modify_ehea_port failed\n");
		err = -EINVAL;
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ)cb1);
	वापस err;
पूर्ण

अटल पूर्णांक ehea_activate_qp(काष्ठा ehea_adapter *adapter, काष्ठा ehea_qp *qp)
अणु
	पूर्णांक ret = -EIO;
	u64 hret;
	u16 dummy16 = 0;
	u64 dummy64 = 0;
	काष्ठा hcp_modअगरy_qp_cb0 *cb0;

	cb0 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb0) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	hret = ehea_h_query_ehea_qp(adapter->handle, 0, qp->fw_handle,
				    EHEA_BMASK_SET(H_QPCB0_ALL, 0xFFFF), cb0);
	अगर (hret != H_SUCCESS) अणु
		pr_err("query_ehea_qp failed (1)\n");
		जाओ out;
	पूर्ण

	cb0->qp_ctl_reg = H_QP_CR_STATE_INITIALIZED;
	hret = ehea_h_modअगरy_ehea_qp(adapter->handle, 0, qp->fw_handle,
				     EHEA_BMASK_SET(H_QPCB0_QP_CTL_REG, 1), cb0,
				     &dummy64, &dummy64, &dummy16, &dummy16);
	अगर (hret != H_SUCCESS) अणु
		pr_err("modify_ehea_qp failed (1)\n");
		जाओ out;
	पूर्ण

	hret = ehea_h_query_ehea_qp(adapter->handle, 0, qp->fw_handle,
				    EHEA_BMASK_SET(H_QPCB0_ALL, 0xFFFF), cb0);
	अगर (hret != H_SUCCESS) अणु
		pr_err("query_ehea_qp failed (2)\n");
		जाओ out;
	पूर्ण

	cb0->qp_ctl_reg = H_QP_CR_ENABLED | H_QP_CR_STATE_INITIALIZED;
	hret = ehea_h_modअगरy_ehea_qp(adapter->handle, 0, qp->fw_handle,
				     EHEA_BMASK_SET(H_QPCB0_QP_CTL_REG, 1), cb0,
				     &dummy64, &dummy64, &dummy16, &dummy16);
	अगर (hret != H_SUCCESS) अणु
		pr_err("modify_ehea_qp failed (2)\n");
		जाओ out;
	पूर्ण

	hret = ehea_h_query_ehea_qp(adapter->handle, 0, qp->fw_handle,
				    EHEA_BMASK_SET(H_QPCB0_ALL, 0xFFFF), cb0);
	अगर (hret != H_SUCCESS) अणु
		pr_err("query_ehea_qp failed (3)\n");
		जाओ out;
	पूर्ण

	cb0->qp_ctl_reg = H_QP_CR_ENABLED | H_QP_CR_STATE_RDY2SND;
	hret = ehea_h_modअगरy_ehea_qp(adapter->handle, 0, qp->fw_handle,
				     EHEA_BMASK_SET(H_QPCB0_QP_CTL_REG, 1), cb0,
				     &dummy64, &dummy64, &dummy16, &dummy16);
	अगर (hret != H_SUCCESS) अणु
		pr_err("modify_ehea_qp failed (3)\n");
		जाओ out;
	पूर्ण

	hret = ehea_h_query_ehea_qp(adapter->handle, 0, qp->fw_handle,
				    EHEA_BMASK_SET(H_QPCB0_ALL, 0xFFFF), cb0);
	अगर (hret != H_SUCCESS) अणु
		pr_err("query_ehea_qp failed (4)\n");
		जाओ out;
	पूर्ण

	ret = 0;
out:
	मुक्त_page((अचिन्हित दीर्घ)cb0);
	वापस ret;
पूर्ण

अटल पूर्णांक ehea_port_res_setup(काष्ठा ehea_port *port, पूर्णांक def_qps)
अणु
	पूर्णांक ret, i;
	काष्ठा port_res_cfg pr_cfg, pr_cfg_small_rx;
	क्रमागत ehea_eq_type eq_type = EHEA_EQ;

	port->qp_eq = ehea_create_eq(port->adapter, eq_type,
				   EHEA_MAX_ENTRIES_EQ, 1);
	अगर (!port->qp_eq) अणु
		ret = -EINVAL;
		pr_err("ehea_create_eq failed (qp_eq)\n");
		जाओ out_समाप्त_eq;
	पूर्ण

	pr_cfg.max_entries_rcq = rq1_entries + rq2_entries + rq3_entries;
	pr_cfg.max_entries_scq = sq_entries * 2;
	pr_cfg.max_entries_sq = sq_entries;
	pr_cfg.max_entries_rq1 = rq1_entries;
	pr_cfg.max_entries_rq2 = rq2_entries;
	pr_cfg.max_entries_rq3 = rq3_entries;

	pr_cfg_small_rx.max_entries_rcq = 1;
	pr_cfg_small_rx.max_entries_scq = sq_entries;
	pr_cfg_small_rx.max_entries_sq = sq_entries;
	pr_cfg_small_rx.max_entries_rq1 = 1;
	pr_cfg_small_rx.max_entries_rq2 = 1;
	pr_cfg_small_rx.max_entries_rq3 = 1;

	क्रम (i = 0; i < def_qps; i++) अणु
		ret = ehea_init_port_res(port, &port->port_res[i], &pr_cfg, i);
		अगर (ret)
			जाओ out_clean_pr;
	पूर्ण
	क्रम (i = def_qps; i < def_qps; i++) अणु
		ret = ehea_init_port_res(port, &port->port_res[i],
					 &pr_cfg_small_rx, i);
		अगर (ret)
			जाओ out_clean_pr;
	पूर्ण

	वापस 0;

out_clean_pr:
	जबतक (--i >= 0)
		ehea_clean_portres(port, &port->port_res[i]);

out_समाप्त_eq:
	ehea_destroy_eq(port->qp_eq);
	वापस ret;
पूर्ण

अटल पूर्णांक ehea_clean_all_portres(काष्ठा ehea_port *port)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < port->num_def_qps; i++)
		ret |= ehea_clean_portres(port, &port->port_res[i]);

	ret |= ehea_destroy_eq(port->qp_eq);

	वापस ret;
पूर्ण

अटल व्योम ehea_हटाओ_adapter_mr(काष्ठा ehea_adapter *adapter)
अणु
	अगर (adapter->active_ports)
		वापस;

	ehea_rem_mr(&adapter->mr);
पूर्ण

अटल पूर्णांक ehea_add_adapter_mr(काष्ठा ehea_adapter *adapter)
अणु
	अगर (adapter->active_ports)
		वापस 0;

	वापस ehea_reg_kernel_mr(adapter, &adapter->mr);
पूर्ण

अटल पूर्णांक ehea_up(काष्ठा net_device *dev)
अणु
	पूर्णांक ret, i;
	काष्ठा ehea_port *port = netdev_priv(dev);

	अगर (port->state == EHEA_PORT_UP)
		वापस 0;

	ret = ehea_port_res_setup(port, port->num_def_qps);
	अगर (ret) अणु
		netdev_err(dev, "port_res_failed\n");
		जाओ out;
	पूर्ण

	/* Set शेष QP क्रम this port */
	ret = ehea_configure_port(port);
	अगर (ret) अणु
		netdev_err(dev, "ehea_configure_port failed. ret:%d\n", ret);
		जाओ out_clean_pr;
	पूर्ण

	ret = ehea_reg_पूर्णांकerrupts(dev);
	अगर (ret) अणु
		netdev_err(dev, "reg_interrupts failed. ret:%d\n", ret);
		जाओ out_clean_pr;
	पूर्ण

	क्रम (i = 0; i < port->num_def_qps; i++) अणु
		ret = ehea_activate_qp(port->adapter, port->port_res[i].qp);
		अगर (ret) अणु
			netdev_err(dev, "activate_qp failed\n");
			जाओ out_मुक्त_irqs;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < port->num_def_qps; i++) अणु
		ret = ehea_fill_port_res(&port->port_res[i]);
		अगर (ret) अणु
			netdev_err(dev, "out_free_irqs\n");
			जाओ out_मुक्त_irqs;
		पूर्ण
	पूर्ण

	ret = ehea_broadcast_reg_helper(port, H_REG_BCMC);
	अगर (ret) अणु
		ret = -EIO;
		जाओ out_मुक्त_irqs;
	पूर्ण

	port->state = EHEA_PORT_UP;

	ret = 0;
	जाओ out;

out_मुक्त_irqs:
	ehea_मुक्त_पूर्णांकerrupts(dev);

out_clean_pr:
	ehea_clean_all_portres(port);
out:
	अगर (ret)
		netdev_info(dev, "Failed starting. ret=%i\n", ret);

	ehea_update_bcmc_registrations();
	ehea_update_firmware_handles();

	वापस ret;
पूर्ण

अटल व्योम port_napi_disable(काष्ठा ehea_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < port->num_def_qps; i++)
		napi_disable(&port->port_res[i].napi);
पूर्ण

अटल व्योम port_napi_enable(काष्ठा ehea_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < port->num_def_qps; i++)
		napi_enable(&port->port_res[i].napi);
पूर्ण

अटल पूर्णांक ehea_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा ehea_port *port = netdev_priv(dev);

	mutex_lock(&port->port_lock);

	netअगर_info(port, अगरup, dev, "enabling port\n");

	netअगर_carrier_off(dev);

	ret = ehea_up(dev);
	अगर (!ret) अणु
		port_napi_enable(port);
		netअगर_tx_start_all_queues(dev);
	पूर्ण

	mutex_unlock(&port->port_lock);
	schedule_delayed_work(&port->stats_work,
			      round_jअगरfies_relative(msecs_to_jअगरfies(1000)));

	वापस ret;
पूर्ण

अटल पूर्णांक ehea_करोwn(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा ehea_port *port = netdev_priv(dev);

	अगर (port->state == EHEA_PORT_DOWN)
		वापस 0;

	ehea_drop_multicast_list(dev);
	ehea_allmulti(dev, 0);
	ehea_broadcast_reg_helper(port, H_DEREG_BCMC);

	ehea_मुक्त_पूर्णांकerrupts(dev);

	port->state = EHEA_PORT_DOWN;

	ehea_update_bcmc_registrations();

	ret = ehea_clean_all_portres(port);
	अगर (ret)
		netdev_info(dev, "Failed freeing resources. ret=%i\n", ret);

	ehea_update_firmware_handles();

	वापस ret;
पूर्ण

अटल पूर्णांक ehea_stop(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा ehea_port *port = netdev_priv(dev);

	netअगर_info(port, अगरकरोwn, dev, "disabling port\n");

	set_bit(__EHEA_DISABLE_PORT_RESET, &port->flags);
	cancel_work_sync(&port->reset_task);
	cancel_delayed_work_sync(&port->stats_work);
	mutex_lock(&port->port_lock);
	netअगर_tx_stop_all_queues(dev);
	port_napi_disable(port);
	ret = ehea_करोwn(dev);
	mutex_unlock(&port->port_lock);
	clear_bit(__EHEA_DISABLE_PORT_RESET, &port->flags);
	वापस ret;
पूर्ण

अटल व्योम ehea_purge_sq(काष्ठा ehea_qp *orig_qp)
अणु
	काष्ठा ehea_qp qp = *orig_qp;
	काष्ठा ehea_qp_init_attr *init_attr = &qp.init_attr;
	काष्ठा ehea_swqe *swqe;
	पूर्णांक wqe_index;
	पूर्णांक i;

	क्रम (i = 0; i < init_attr->act_nr_send_wqes; i++) अणु
		swqe = ehea_get_swqe(&qp, &wqe_index);
		swqe->tx_control |= EHEA_SWQE_PURGE;
	पूर्ण
पूर्ण

अटल व्योम ehea_flush_sq(काष्ठा ehea_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < port->num_def_qps; i++) अणु
		काष्ठा ehea_port_res *pr = &port->port_res[i];
		पूर्णांक swqe_max = pr->sq_skba_size - 2 - pr->swqe_ll_count;
		पूर्णांक ret;

		ret = रुको_event_समयout(port->swqe_avail_wq,
			 atomic_पढ़ो(&pr->swqe_avail) >= swqe_max,
			 msecs_to_jअगरfies(100));

		अगर (!ret) अणु
			pr_err("WARNING: sq not flushed completely\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ehea_stop_qps(काष्ठा net_device *dev)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा ehea_adapter *adapter = port->adapter;
	काष्ठा hcp_modअगरy_qp_cb0 *cb0;
	पूर्णांक ret = -EIO;
	पूर्णांक dret;
	पूर्णांक i;
	u64 hret;
	u64 dummy64 = 0;
	u16 dummy16 = 0;

	cb0 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb0) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < (port->num_def_qps); i++) अणु
		काष्ठा ehea_port_res *pr =  &port->port_res[i];
		काष्ठा ehea_qp *qp = pr->qp;

		/* Purge send queue */
		ehea_purge_sq(qp);

		/* Disable queue pair */
		hret = ehea_h_query_ehea_qp(adapter->handle, 0, qp->fw_handle,
					    EHEA_BMASK_SET(H_QPCB0_ALL, 0xFFFF),
					    cb0);
		अगर (hret != H_SUCCESS) अणु
			pr_err("query_ehea_qp failed (1)\n");
			जाओ out;
		पूर्ण

		cb0->qp_ctl_reg = (cb0->qp_ctl_reg & H_QP_CR_RES_STATE) << 8;
		cb0->qp_ctl_reg &= ~H_QP_CR_ENABLED;

		hret = ehea_h_modअगरy_ehea_qp(adapter->handle, 0, qp->fw_handle,
					     EHEA_BMASK_SET(H_QPCB0_QP_CTL_REG,
							    1), cb0, &dummy64,
					     &dummy64, &dummy16, &dummy16);
		अगर (hret != H_SUCCESS) अणु
			pr_err("modify_ehea_qp failed (1)\n");
			जाओ out;
		पूर्ण

		hret = ehea_h_query_ehea_qp(adapter->handle, 0, qp->fw_handle,
					    EHEA_BMASK_SET(H_QPCB0_ALL, 0xFFFF),
					    cb0);
		अगर (hret != H_SUCCESS) अणु
			pr_err("query_ehea_qp failed (2)\n");
			जाओ out;
		पूर्ण

		/* deरेजिस्टर shared memory regions */
		dret = ehea_rem_smrs(pr);
		अगर (dret) अणु
			pr_err("unreg shared memory region failed\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;
out:
	मुक्त_page((अचिन्हित दीर्घ)cb0);

	वापस ret;
पूर्ण

अटल व्योम ehea_update_rqs(काष्ठा ehea_qp *orig_qp, काष्ठा ehea_port_res *pr)
अणु
	काष्ठा ehea_qp qp = *orig_qp;
	काष्ठा ehea_qp_init_attr *init_attr = &qp.init_attr;
	काष्ठा ehea_rwqe *rwqe;
	काष्ठा sk_buff **skba_rq2 = pr->rq2_skba.arr;
	काष्ठा sk_buff **skba_rq3 = pr->rq3_skba.arr;
	काष्ठा sk_buff *skb;
	u32 lkey = pr->recv_mr.lkey;


	पूर्णांक i;
	पूर्णांक index;

	क्रम (i = 0; i < init_attr->act_nr_rwqes_rq2 + 1; i++) अणु
		rwqe = ehea_get_next_rwqe(&qp, 2);
		rwqe->sg_list[0].l_key = lkey;
		index = EHEA_BMASK_GET(EHEA_WR_ID_INDEX, rwqe->wr_id);
		skb = skba_rq2[index];
		अगर (skb)
			rwqe->sg_list[0].vaddr = ehea_map_vaddr(skb->data);
	पूर्ण

	क्रम (i = 0; i < init_attr->act_nr_rwqes_rq3 + 1; i++) अणु
		rwqe = ehea_get_next_rwqe(&qp, 3);
		rwqe->sg_list[0].l_key = lkey;
		index = EHEA_BMASK_GET(EHEA_WR_ID_INDEX, rwqe->wr_id);
		skb = skba_rq3[index];
		अगर (skb)
			rwqe->sg_list[0].vaddr = ehea_map_vaddr(skb->data);
	पूर्ण
पूर्ण

अटल पूर्णांक ehea_restart_qps(काष्ठा net_device *dev)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	काष्ठा ehea_adapter *adapter = port->adapter;
	पूर्णांक ret = 0;
	पूर्णांक i;

	काष्ठा hcp_modअगरy_qp_cb0 *cb0;
	u64 hret;
	u64 dummy64 = 0;
	u16 dummy16 = 0;

	cb0 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb0) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < (port->num_def_qps); i++) अणु
		काष्ठा ehea_port_res *pr =  &port->port_res[i];
		काष्ठा ehea_qp *qp = pr->qp;

		ret = ehea_gen_smrs(pr);
		अगर (ret) अणु
			netdev_err(dev, "creation of shared memory regions failed\n");
			जाओ out;
		पूर्ण

		ehea_update_rqs(qp, pr);

		/* Enable queue pair */
		hret = ehea_h_query_ehea_qp(adapter->handle, 0, qp->fw_handle,
					    EHEA_BMASK_SET(H_QPCB0_ALL, 0xFFFF),
					    cb0);
		अगर (hret != H_SUCCESS) अणु
			netdev_err(dev, "query_ehea_qp failed (1)\n");
			जाओ out;
		पूर्ण

		cb0->qp_ctl_reg = (cb0->qp_ctl_reg & H_QP_CR_RES_STATE) << 8;
		cb0->qp_ctl_reg |= H_QP_CR_ENABLED;

		hret = ehea_h_modअगरy_ehea_qp(adapter->handle, 0, qp->fw_handle,
					     EHEA_BMASK_SET(H_QPCB0_QP_CTL_REG,
							    1), cb0, &dummy64,
					     &dummy64, &dummy16, &dummy16);
		अगर (hret != H_SUCCESS) अणु
			netdev_err(dev, "modify_ehea_qp failed (1)\n");
			जाओ out;
		पूर्ण

		hret = ehea_h_query_ehea_qp(adapter->handle, 0, qp->fw_handle,
					    EHEA_BMASK_SET(H_QPCB0_ALL, 0xFFFF),
					    cb0);
		अगर (hret != H_SUCCESS) अणु
			netdev_err(dev, "query_ehea_qp failed (2)\n");
			जाओ out;
		पूर्ण

		/* refill entire queue */
		ehea_refill_rq1(pr, pr->rq1_skba.index, 0);
		ehea_refill_rq2(pr, 0);
		ehea_refill_rq3(pr, 0);
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ)cb0);

	वापस ret;
पूर्ण

अटल व्योम ehea_reset_port(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा ehea_port *port =
		container_of(work, काष्ठा ehea_port, reset_task);
	काष्ठा net_device *dev = port->netdev;

	mutex_lock(&dlpar_mem_lock);
	port->resets++;
	mutex_lock(&port->port_lock);
	netअगर_tx_disable(dev);

	port_napi_disable(port);

	ehea_करोwn(dev);

	ret = ehea_up(dev);
	अगर (ret)
		जाओ out;

	ehea_set_multicast_list(dev);

	netअगर_info(port, समयr, dev, "reset successful\n");

	port_napi_enable(port);

	netअगर_tx_wake_all_queues(dev);
out:
	mutex_unlock(&port->port_lock);
	mutex_unlock(&dlpar_mem_lock);
पूर्ण

अटल व्योम ehea_rereg_mrs(व्योम)
अणु
	पूर्णांक ret, i;
	काष्ठा ehea_adapter *adapter;

	pr_info("LPAR memory changed - re-initializing driver\n");

	list_क्रम_each_entry(adapter, &adapter_list, list)
		अगर (adapter->active_ports) अणु
			/* Shutकरोwn all ports */
			क्रम (i = 0; i < EHEA_MAX_PORTS; i++) अणु
				काष्ठा ehea_port *port = adapter->port[i];
				काष्ठा net_device *dev;

				अगर (!port)
					जारी;

				dev = port->netdev;

				अगर (dev->flags & IFF_UP) अणु
					mutex_lock(&port->port_lock);
					netअगर_tx_disable(dev);
					ehea_flush_sq(port);
					ret = ehea_stop_qps(dev);
					अगर (ret) अणु
						mutex_unlock(&port->port_lock);
						जाओ out;
					पूर्ण
					port_napi_disable(port);
					mutex_unlock(&port->port_lock);
				पूर्ण
				reset_sq_restart_flag(port);
			पूर्ण

			/* Unरेजिस्टर old memory region */
			ret = ehea_rem_mr(&adapter->mr);
			अगर (ret) अणु
				pr_err("unregister MR failed - driver inoperable!\n");
				जाओ out;
			पूर्ण
		पूर्ण

	clear_bit(__EHEA_STOP_XFER, &ehea_driver_flags);

	list_क्रम_each_entry(adapter, &adapter_list, list)
		अगर (adapter->active_ports) अणु
			/* Register new memory region */
			ret = ehea_reg_kernel_mr(adapter, &adapter->mr);
			अगर (ret) अणु
				pr_err("register MR failed - driver inoperable!\n");
				जाओ out;
			पूर्ण

			/* Restart all ports */
			क्रम (i = 0; i < EHEA_MAX_PORTS; i++) अणु
				काष्ठा ehea_port *port = adapter->port[i];

				अगर (port) अणु
					काष्ठा net_device *dev = port->netdev;

					अगर (dev->flags & IFF_UP) अणु
						mutex_lock(&port->port_lock);
						ret = ehea_restart_qps(dev);
						अगर (!ret) अणु
							check_sqs(port);
							port_napi_enable(port);
							netअगर_tx_wake_all_queues(dev);
						पूर्ण अन्यथा अणु
							netdev_err(dev, "Unable to restart QPS\n");
						पूर्ण
						mutex_unlock(&port->port_lock);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	pr_info("re-initializing driver complete\n");
out:
	वापस;
पूर्ण

अटल व्योम ehea_tx_watchकरोg(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);

	अगर (netअगर_carrier_ok(dev) &&
	    !test_bit(__EHEA_STOP_XFER, &ehea_driver_flags))
		ehea_schedule_port_reset(port);
पूर्ण

अटल पूर्णांक ehea_sense_adapter_attr(काष्ठा ehea_adapter *adapter)
अणु
	काष्ठा hcp_query_ehea *cb;
	u64 hret;
	पूर्णांक ret;

	cb = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	hret = ehea_h_query_ehea(adapter->handle, cb);

	अगर (hret != H_SUCCESS) अणु
		ret = -EIO;
		जाओ out_herr;
	पूर्ण

	adapter->max_mc_mac = cb->max_mc_mac - 1;
	ret = 0;

out_herr:
	मुक्त_page((अचिन्हित दीर्घ)cb);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ehea_get_jumboframe_status(काष्ठा ehea_port *port, पूर्णांक *jumbo)
अणु
	काष्ठा hcp_ehea_port_cb4 *cb4;
	u64 hret;
	पूर्णांक ret = 0;

	*jumbo = 0;

	/* (Try to) enable *jumbo frames */
	cb4 = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!cb4) अणु
		pr_err("no mem for cb4\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण अन्यथा अणु
		hret = ehea_h_query_ehea_port(port->adapter->handle,
					      port->logical_port_id,
					      H_PORT_CB4,
					      H_PORT_CB4_JUMBO, cb4);
		अगर (hret == H_SUCCESS) अणु
			अगर (cb4->jumbo_frame)
				*jumbo = 1;
			अन्यथा अणु
				cb4->jumbo_frame = 1;
				hret = ehea_h_modअगरy_ehea_port(port->adapter->
							       handle,
							       port->
							       logical_port_id,
							       H_PORT_CB4,
							       H_PORT_CB4_JUMBO,
							       cb4);
				अगर (hret == H_SUCCESS)
					*jumbo = 1;
			पूर्ण
		पूर्ण अन्यथा
			ret = -EINVAL;

		मुक्त_page((अचिन्हित दीर्घ)cb4);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ehea_show_port_id(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ehea_port *port = container_of(dev, काष्ठा ehea_port, ofdev.dev);
	वापस प्र_लिखो(buf, "%d", port->logical_port_id);
पूर्ण

अटल DEVICE_ATTR(log_port_id, 0444, ehea_show_port_id, शून्य);

अटल व्योम logical_port_release(काष्ठा device *dev)
अणु
	काष्ठा ehea_port *port = container_of(dev, काष्ठा ehea_port, ofdev.dev);
	of_node_put(port->ofdev.dev.of_node);
पूर्ण

अटल काष्ठा device *ehea_रेजिस्टर_port(काष्ठा ehea_port *port,
					 काष्ठा device_node *dn)
अणु
	पूर्णांक ret;

	port->ofdev.dev.of_node = of_node_get(dn);
	port->ofdev.dev.parent = &port->adapter->ofdev->dev;
	port->ofdev.dev.bus = &ibmebus_bus_type;

	dev_set_name(&port->ofdev.dev, "port%d", port_name_cnt++);
	port->ofdev.dev.release = logical_port_release;

	ret = of_device_रेजिस्टर(&port->ofdev);
	अगर (ret) अणु
		pr_err("failed to register device. ret=%d\n", ret);
		जाओ out;
	पूर्ण

	ret = device_create_file(&port->ofdev.dev, &dev_attr_log_port_id);
	अगर (ret) अणु
		pr_err("failed to register attributes, ret=%d\n", ret);
		जाओ out_unreg_of_dev;
	पूर्ण

	वापस &port->ofdev.dev;

out_unreg_of_dev:
	of_device_unरेजिस्टर(&port->ofdev);
out:
	वापस शून्य;
पूर्ण

अटल व्योम ehea_unरेजिस्टर_port(काष्ठा ehea_port *port)
अणु
	device_हटाओ_file(&port->ofdev.dev, &dev_attr_log_port_id);
	of_device_unरेजिस्टर(&port->ofdev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ehea_netdev_ops = अणु
	.nकरो_खोलो		= ehea_खोलो,
	.nकरो_stop		= ehea_stop,
	.nकरो_start_xmit		= ehea_start_xmit,
	.nकरो_get_stats64	= ehea_get_stats64,
	.nकरो_set_mac_address	= ehea_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= ehea_set_multicast_list,
	.nकरो_vlan_rx_add_vid	= ehea_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= ehea_vlan_rx_समाप्त_vid,
	.nकरो_tx_समयout		= ehea_tx_watchकरोg,
पूर्ण;

अटल काष्ठा ehea_port *ehea_setup_single_port(काष्ठा ehea_adapter *adapter,
					 u32 logical_port_id,
					 काष्ठा device_node *dn)
अणु
	पूर्णांक ret;
	काष्ठा net_device *dev;
	काष्ठा ehea_port *port;
	काष्ठा device *port_dev;
	पूर्णांक jumbo;

	/* allocate memory क्रम the port काष्ठाures */
	dev = alloc_etherdev_mq(माप(काष्ठा ehea_port), EHEA_MAX_PORT_RES);

	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	port = netdev_priv(dev);

	mutex_init(&port->port_lock);
	port->state = EHEA_PORT_DOWN;
	port->sig_comp_iv = sq_entries / 10;

	port->adapter = adapter;
	port->netdev = dev;
	port->logical_port_id = logical_port_id;

	port->msg_enable = netअगर_msg_init(msg_level, EHEA_MSG_DEFAULT);

	port->mc_list = kzalloc(माप(काष्ठा ehea_mc_list), GFP_KERNEL);
	अगर (!port->mc_list) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_ethdev;
	पूर्ण

	INIT_LIST_HEAD(&port->mc_list->list);

	ret = ehea_sense_port_attr(port);
	अगर (ret)
		जाओ out_मुक्त_mc_list;

	netअगर_set_real_num_rx_queues(dev, port->num_def_qps);
	netअगर_set_real_num_tx_queues(dev, port->num_def_qps);

	port_dev = ehea_रेजिस्टर_port(port, dn);
	अगर (!port_dev)
		जाओ out_मुक्त_mc_list;

	SET_NETDEV_DEV(dev, port_dev);

	/* initialize net_device काष्ठाure */
	स_नकल(dev->dev_addr, &port->mac_addr, ETH_ALEN);

	dev->netdev_ops = &ehea_netdev_ops;
	ehea_set_ethtool_ops(dev);

	dev->hw_features = NETIF_F_SG | NETIF_F_TSO |
		      NETIF_F_IP_CSUM | NETIF_F_HW_VLAN_CTAG_TX;
	dev->features = NETIF_F_SG | NETIF_F_TSO |
		      NETIF_F_HIGHDMA | NETIF_F_IP_CSUM |
		      NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
		      NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_RXCSUM;
	dev->vlan_features = NETIF_F_SG | NETIF_F_TSO | NETIF_F_HIGHDMA |
			NETIF_F_IP_CSUM;
	dev->watchकरोg_समयo = EHEA_WATCH_DOG_TIMEOUT;

	/* MTU range: 68 - 9022 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = EHEA_MAX_PACKET_SIZE;

	INIT_WORK(&port->reset_task, ehea_reset_port);
	INIT_DELAYED_WORK(&port->stats_work, ehea_update_stats);

	init_रुकोqueue_head(&port->swqe_avail_wq);
	init_रुकोqueue_head(&port->restart_wq);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret) अणु
		pr_err("register_netdev failed. ret=%d\n", ret);
		जाओ out_unreg_port;
	पूर्ण

	ret = ehea_get_jumboframe_status(port, &jumbo);
	अगर (ret)
		netdev_err(dev, "failed determining jumbo frame status\n");

	netdev_info(dev, "Jumbo frames are %sabled\n",
		    jumbo == 1 ? "en" : "dis");

	adapter->active_ports++;

	वापस port;

out_unreg_port:
	ehea_unरेजिस्टर_port(port);

out_मुक्त_mc_list:
	kमुक्त(port->mc_list);

out_मुक्त_ethdev:
	मुक्त_netdev(dev);

out_err:
	pr_err("setting up logical port with id=%d failed, ret=%d\n",
	       logical_port_id, ret);
	वापस शून्य;
पूर्ण

अटल व्योम ehea_shutकरोwn_single_port(काष्ठा ehea_port *port)
अणु
	काष्ठा ehea_adapter *adapter = port->adapter;

	cancel_work_sync(&port->reset_task);
	cancel_delayed_work_sync(&port->stats_work);
	unरेजिस्टर_netdev(port->netdev);
	ehea_unरेजिस्टर_port(port);
	kमुक्त(port->mc_list);
	मुक्त_netdev(port->netdev);
	adapter->active_ports--;
पूर्ण

अटल पूर्णांक ehea_setup_ports(काष्ठा ehea_adapter *adapter)
अणु
	काष्ठा device_node *lhea_dn;
	काष्ठा device_node *eth_dn = शून्य;

	स्थिर u32 *dn_log_port_id;
	पूर्णांक i = 0;

	lhea_dn = adapter->ofdev->dev.of_node;
	जबतक ((eth_dn = of_get_next_child(lhea_dn, eth_dn))) अणु

		dn_log_port_id = of_get_property(eth_dn, "ibm,hea-port-no",
						 शून्य);
		अगर (!dn_log_port_id) अणु
			pr_err("bad device node: eth_dn name=%pOF\n", eth_dn);
			जारी;
		पूर्ण

		अगर (ehea_add_adapter_mr(adapter)) अणु
			pr_err("creating MR failed\n");
			of_node_put(eth_dn);
			वापस -EIO;
		पूर्ण

		adapter->port[i] = ehea_setup_single_port(adapter,
							  *dn_log_port_id,
							  eth_dn);
		अगर (adapter->port[i])
			netdev_info(adapter->port[i]->netdev,
				    "logical port id #%d\n", *dn_log_port_id);
		अन्यथा
			ehea_हटाओ_adapter_mr(adapter);

		i++;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा device_node *ehea_get_eth_dn(काष्ठा ehea_adapter *adapter,
					   u32 logical_port_id)
अणु
	काष्ठा device_node *lhea_dn;
	काष्ठा device_node *eth_dn = शून्य;
	स्थिर u32 *dn_log_port_id;

	lhea_dn = adapter->ofdev->dev.of_node;
	जबतक ((eth_dn = of_get_next_child(lhea_dn, eth_dn))) अणु

		dn_log_port_id = of_get_property(eth_dn, "ibm,hea-port-no",
						 शून्य);
		अगर (dn_log_port_id)
			अगर (*dn_log_port_id == logical_port_id)
				वापस eth_dn;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार ehea_probe_port(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ehea_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा ehea_port *port;
	काष्ठा device_node *eth_dn = शून्य;
	पूर्णांक i;

	u32 logical_port_id;

	माला_पूछो(buf, "%d", &logical_port_id);

	port = ehea_get_port(adapter, logical_port_id);

	अगर (port) अणु
		netdev_info(port->netdev, "adding port with logical port id=%d failed: port already configured\n",
			    logical_port_id);
		वापस -EINVAL;
	पूर्ण

	eth_dn = ehea_get_eth_dn(adapter, logical_port_id);

	अगर (!eth_dn) अणु
		pr_info("no logical port with id %d found\n", logical_port_id);
		वापस -EINVAL;
	पूर्ण

	अगर (ehea_add_adapter_mr(adapter)) अणु
		pr_err("creating MR failed\n");
		of_node_put(eth_dn);
		वापस -EIO;
	पूर्ण

	port = ehea_setup_single_port(adapter, logical_port_id, eth_dn);

	of_node_put(eth_dn);

	अगर (port) अणु
		क्रम (i = 0; i < EHEA_MAX_PORTS; i++)
			अगर (!adapter->port[i]) अणु
				adapter->port[i] = port;
				अवरोध;
			पूर्ण

		netdev_info(port->netdev, "added: (logical port id=%d)\n",
			    logical_port_id);
	पूर्ण अन्यथा अणु
		ehea_हटाओ_adapter_mr(adapter);
		वापस -EIO;
	पूर्ण

	वापस (sमाप_प्रकार) count;
पूर्ण

अटल sमाप_प्रकार ehea_हटाओ_port(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ehea_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा ehea_port *port;
	पूर्णांक i;
	u32 logical_port_id;

	माला_पूछो(buf, "%d", &logical_port_id);

	port = ehea_get_port(adapter, logical_port_id);

	अगर (port) अणु
		netdev_info(port->netdev, "removed: (logical port id=%d)\n",
			    logical_port_id);

		ehea_shutकरोwn_single_port(port);

		क्रम (i = 0; i < EHEA_MAX_PORTS; i++)
			अगर (adapter->port[i] == port) अणु
				adapter->port[i] = शून्य;
				अवरोध;
			पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("removing port with logical port id=%d failed. port not configured.\n",
		       logical_port_id);
		वापस -EINVAL;
	पूर्ण

	ehea_हटाओ_adapter_mr(adapter);

	वापस (sमाप_प्रकार) count;
पूर्ण

अटल DEVICE_ATTR(probe_port, 0200, शून्य, ehea_probe_port);
अटल DEVICE_ATTR(हटाओ_port, 0200, शून्य, ehea_हटाओ_port);

अटल पूर्णांक ehea_create_device_sysfs(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret = device_create_file(&dev->dev, &dev_attr_probe_port);
	अगर (ret)
		जाओ out;

	ret = device_create_file(&dev->dev, &dev_attr_हटाओ_port);
out:
	वापस ret;
पूर्ण

अटल व्योम ehea_हटाओ_device_sysfs(काष्ठा platक्रमm_device *dev)
अणु
	device_हटाओ_file(&dev->dev, &dev_attr_probe_port);
	device_हटाओ_file(&dev->dev, &dev_attr_हटाओ_port);
पूर्ण

अटल पूर्णांक ehea_reboot_notअगरier(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ action, व्योम *unused)
अणु
	अगर (action == SYS_RESTART) अणु
		pr_info("Reboot: freeing all eHEA resources\n");
		ibmebus_unरेजिस्टर_driver(&ehea_driver);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ehea_reboot_nb = अणु
	.notअगरier_call = ehea_reboot_notअगरier,
पूर्ण;

अटल पूर्णांक ehea_mem_notअगरier(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ action, व्योम *data)
अणु
	पूर्णांक ret = NOTIFY_BAD;
	काष्ठा memory_notअगरy *arg = data;

	mutex_lock(&dlpar_mem_lock);

	चयन (action) अणु
	हाल MEM_CANCEL_OFFLINE:
		pr_info("memory offlining canceled");
		fallthrough;	/* re-add canceled memory block */

	हाल MEM_ONLINE:
		pr_info("memory is going online");
		set_bit(__EHEA_STOP_XFER, &ehea_driver_flags);
		अगर (ehea_add_sect_bmap(arg->start_pfn, arg->nr_pages))
			जाओ out_unlock;
		ehea_rereg_mrs();
		अवरोध;

	हाल MEM_GOING_OFFLINE:
		pr_info("memory is going offline");
		set_bit(__EHEA_STOP_XFER, &ehea_driver_flags);
		अगर (ehea_rem_sect_bmap(arg->start_pfn, arg->nr_pages))
			जाओ out_unlock;
		ehea_rereg_mrs();
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	ehea_update_firmware_handles();
	ret = NOTIFY_OK;

out_unlock:
	mutex_unlock(&dlpar_mem_lock);
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block ehea_mem_nb = अणु
	.notअगरier_call = ehea_mem_notअगरier,
पूर्ण;

अटल व्योम ehea_crash_handler(व्योम)
अणु
	पूर्णांक i;

	अगर (ehea_fw_handles.arr)
		क्रम (i = 0; i < ehea_fw_handles.num_entries; i++)
			ehea_h_मुक्त_resource(ehea_fw_handles.arr[i].adh,
					     ehea_fw_handles.arr[i].fwh,
					     FORCE_FREE);

	अगर (ehea_bcmc_regs.arr)
		क्रम (i = 0; i < ehea_bcmc_regs.num_entries; i++)
			ehea_h_reg_dereg_bcmc(ehea_bcmc_regs.arr[i].adh,
					      ehea_bcmc_regs.arr[i].port_id,
					      ehea_bcmc_regs.arr[i].reg_type,
					      ehea_bcmc_regs.arr[i].macaddr,
					      0, H_DEREG_BCMC);
पूर्ण

अटल atomic_t ehea_memory_hooks_रेजिस्टरed;

/* Register memory hooks on probe of first adapter */
अटल पूर्णांक ehea_रेजिस्टर_memory_hooks(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (atomic_inc_वापस(&ehea_memory_hooks_रेजिस्टरed) > 1)
		वापस 0;

	ret = ehea_create_busmap();
	अगर (ret) अणु
		pr_info("ehea_create_busmap failed\n");
		जाओ out;
	पूर्ण

	ret = रेजिस्टर_reboot_notअगरier(&ehea_reboot_nb);
	अगर (ret) अणु
		pr_info("register_reboot_notifier failed\n");
		जाओ out;
	पूर्ण

	ret = रेजिस्टर_memory_notअगरier(&ehea_mem_nb);
	अगर (ret) अणु
		pr_info("register_memory_notifier failed\n");
		जाओ out2;
	पूर्ण

	ret = crash_shutकरोwn_रेजिस्टर(ehea_crash_handler);
	अगर (ret) अणु
		pr_info("crash_shutdown_register failed\n");
		जाओ out3;
	पूर्ण

	वापस 0;

out3:
	unरेजिस्टर_memory_notअगरier(&ehea_mem_nb);
out2:
	unरेजिस्टर_reboot_notअगरier(&ehea_reboot_nb);
out:
	atomic_dec(&ehea_memory_hooks_रेजिस्टरed);
	वापस ret;
पूर्ण

अटल व्योम ehea_unरेजिस्टर_memory_hooks(व्योम)
अणु
	/* Only हटाओ the hooks अगर we've रेजिस्टरed them */
	अगर (atomic_पढ़ो(&ehea_memory_hooks_रेजिस्टरed) == 0)
		वापस;

	unरेजिस्टर_reboot_notअगरier(&ehea_reboot_nb);
	अगर (crash_shutकरोwn_unरेजिस्टर(ehea_crash_handler))
		pr_info("failed unregistering crash handler\n");
	unरेजिस्टर_memory_notअगरier(&ehea_mem_nb);
पूर्ण

अटल पूर्णांक ehea_probe_adapter(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ehea_adapter *adapter;
	स्थिर u64 *adapter_handle;
	पूर्णांक ret;
	पूर्णांक i;

	ret = ehea_रेजिस्टर_memory_hooks();
	अगर (ret)
		वापस ret;

	अगर (!dev || !dev->dev.of_node) अणु
		pr_err("Invalid ibmebus device probed\n");
		वापस -EINVAL;
	पूर्ण

	adapter = devm_kzalloc(&dev->dev, माप(*adapter), GFP_KERNEL);
	अगर (!adapter) अणु
		ret = -ENOMEM;
		dev_err(&dev->dev, "no mem for ehea_adapter\n");
		जाओ out;
	पूर्ण

	list_add(&adapter->list, &adapter_list);

	adapter->ofdev = dev;

	adapter_handle = of_get_property(dev->dev.of_node, "ibm,hea-handle",
					 शून्य);
	अगर (adapter_handle)
		adapter->handle = *adapter_handle;

	अगर (!adapter->handle) अणु
		dev_err(&dev->dev, "failed getting handle for adapter"
			" '%pOF'\n", dev->dev.of_node);
		ret = -ENODEV;
		जाओ out_मुक्त_ad;
	पूर्ण

	adapter->pd = EHEA_PD_ID;

	platक्रमm_set_drvdata(dev, adapter);


	/* initialize adapter and ports */
	/* get adapter properties */
	ret = ehea_sense_adapter_attr(adapter);
	अगर (ret) अणु
		dev_err(&dev->dev, "sense_adapter_attr failed: %d\n", ret);
		जाओ out_मुक्त_ad;
	पूर्ण

	adapter->neq = ehea_create_eq(adapter,
				      EHEA_NEQ, EHEA_MAX_ENTRIES_EQ, 1);
	अगर (!adapter->neq) अणु
		ret = -EIO;
		dev_err(&dev->dev, "NEQ creation failed\n");
		जाओ out_मुक्त_ad;
	पूर्ण

	tasklet_setup(&adapter->neq_tasklet, ehea_neq_tasklet);

	ret = ehea_create_device_sysfs(dev);
	अगर (ret)
		जाओ out_समाप्त_eq;

	ret = ehea_setup_ports(adapter);
	अगर (ret) अणु
		dev_err(&dev->dev, "setup_ports failed\n");
		जाओ out_rem_dev_sysfs;
	पूर्ण

	ret = ibmebus_request_irq(adapter->neq->attr.ist1,
				  ehea_पूर्णांकerrupt_neq, 0,
				  "ehea_neq", adapter);
	अगर (ret) अणु
		dev_err(&dev->dev, "requesting NEQ IRQ failed\n");
		जाओ out_shutकरोwn_ports;
	पूर्ण

	/* Handle any events that might be pending. */
	tasklet_hi_schedule(&adapter->neq_tasklet);

	ret = 0;
	जाओ out;

out_shutकरोwn_ports:
	क्रम (i = 0; i < EHEA_MAX_PORTS; i++)
		अगर (adapter->port[i]) अणु
			ehea_shutकरोwn_single_port(adapter->port[i]);
			adapter->port[i] = शून्य;
		पूर्ण

out_rem_dev_sysfs:
	ehea_हटाओ_device_sysfs(dev);

out_समाप्त_eq:
	ehea_destroy_eq(adapter->neq);

out_मुक्त_ad:
	list_del(&adapter->list);

out:
	ehea_update_firmware_handles();

	वापस ret;
पूर्ण

अटल पूर्णांक ehea_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ehea_adapter *adapter = platक्रमm_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < EHEA_MAX_PORTS; i++)
		अगर (adapter->port[i]) अणु
			ehea_shutकरोwn_single_port(adapter->port[i]);
			adapter->port[i] = शून्य;
		पूर्ण

	ehea_हटाओ_device_sysfs(dev);

	ibmebus_मुक्त_irq(adapter->neq->attr.ist1, adapter);
	tasklet_समाप्त(&adapter->neq_tasklet);

	ehea_destroy_eq(adapter->neq);
	ehea_हटाओ_adapter_mr(adapter);
	list_del(&adapter->list);

	ehea_update_firmware_handles();

	वापस 0;
पूर्ण

अटल पूर्णांक check_module_parm(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर ((rq1_entries < EHEA_MIN_ENTRIES_QP) ||
	    (rq1_entries > EHEA_MAX_ENTRIES_RQ1)) अणु
		pr_info("Bad parameter: rq1_entries\n");
		ret = -EINVAL;
	पूर्ण
	अगर ((rq2_entries < EHEA_MIN_ENTRIES_QP) ||
	    (rq2_entries > EHEA_MAX_ENTRIES_RQ2)) अणु
		pr_info("Bad parameter: rq2_entries\n");
		ret = -EINVAL;
	पूर्ण
	अगर ((rq3_entries < EHEA_MIN_ENTRIES_QP) ||
	    (rq3_entries > EHEA_MAX_ENTRIES_RQ3)) अणु
		pr_info("Bad parameter: rq3_entries\n");
		ret = -EINVAL;
	पूर्ण
	अगर ((sq_entries < EHEA_MIN_ENTRIES_QP) ||
	    (sq_entries > EHEA_MAX_ENTRIES_SQ)) अणु
		pr_info("Bad parameter: sq_entries\n");
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार capabilities_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d", EHEA_CAPABILITIES);
पूर्ण

अटल DRIVER_ATTR_RO(capabilities);

अटल पूर्णांक __init ehea_module_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("IBM eHEA ethernet device driver (Release %s)\n", DRV_VERSION);

	स_रखो(&ehea_fw_handles, 0, माप(ehea_fw_handles));
	स_रखो(&ehea_bcmc_regs, 0, माप(ehea_bcmc_regs));

	mutex_init(&ehea_fw_handles.lock);
	spin_lock_init(&ehea_bcmc_regs.lock);

	ret = check_module_parm();
	अगर (ret)
		जाओ out;

	ret = ibmebus_रेजिस्टर_driver(&ehea_driver);
	अगर (ret) अणु
		pr_err("failed registering eHEA device driver on ebus\n");
		जाओ out;
	पूर्ण

	ret = driver_create_file(&ehea_driver.driver,
				 &driver_attr_capabilities);
	अगर (ret) अणु
		pr_err("failed to register capabilities attribute, ret=%d\n",
		       ret);
		जाओ out2;
	पूर्ण

	वापस ret;

out2:
	ibmebus_unरेजिस्टर_driver(&ehea_driver);
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास ehea_module_निकास(व्योम)
अणु
	driver_हटाओ_file(&ehea_driver.driver, &driver_attr_capabilities);
	ibmebus_unरेजिस्टर_driver(&ehea_driver);
	ehea_unरेजिस्टर_memory_hooks();
	kमुक्त(ehea_fw_handles.arr);
	kमुक्त(ehea_bcmc_regs.arr);
	ehea_destroy_busmap();
पूर्ण

module_init(ehea_module_init);
module_निकास(ehea_module_निकास);
