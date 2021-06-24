<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  FUJITSU Extended Socket Network Device driver
 *  Copyright (c) 2015 FUJITSU LIMITED
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/nls.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "fjes.h"
#समावेश "fjes_trace.h"

#घोषणा MAJ 1
#घोषणा MIN 2
#घोषणा DRV_VERSION __stringअगरy(MAJ) "." __stringअगरy(MIN)
#घोषणा DRV_NAME	"fjes"
अक्षर fjes_driver_name[] = DRV_NAME;
अक्षर fjes_driver_version[] = DRV_VERSION;
अटल स्थिर अक्षर fjes_driver_string[] =
		"FUJITSU Extended Socket Network Device Driver";
अटल स्थिर अक्षर fjes_copyright[] =
		"Copyright (c) 2015 FUJITSU LIMITED";

MODULE_AUTHOR("Taku Izumi <izumi.taku@jp.fujitsu.com>");
MODULE_DESCRIPTION("FUJITSU Extended Socket Network Device Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

#घोषणा ACPI_MOTHERBOARD_RESOURCE_HID "PNP0C02"

अटल पूर्णांक fjes_request_irq(काष्ठा fjes_adapter *);
अटल व्योम fjes_मुक्त_irq(काष्ठा fjes_adapter *);

अटल पूर्णांक fjes_खोलो(काष्ठा net_device *);
अटल पूर्णांक fjes_बंद(काष्ठा net_device *);
अटल पूर्णांक fjes_setup_resources(काष्ठा fjes_adapter *);
अटल व्योम fjes_मुक्त_resources(काष्ठा fjes_adapter *);
अटल netdev_tx_t fjes_xmit_frame(काष्ठा sk_buff *, काष्ठा net_device *);
अटल व्योम fjes_उठाओ_पूर्णांकr_rxdata_task(काष्ठा work_काष्ठा *);
अटल व्योम fjes_tx_stall_task(काष्ठा work_काष्ठा *);
अटल व्योम fjes_क्रमce_बंद_task(काष्ठा work_काष्ठा *);
अटल irqवापस_t fjes_पूर्णांकr(पूर्णांक, व्योम*);
अटल व्योम fjes_get_stats64(काष्ठा net_device *, काष्ठा rtnl_link_stats64 *);
अटल पूर्णांक fjes_change_mtu(काष्ठा net_device *, पूर्णांक);
अटल पूर्णांक fjes_vlan_rx_add_vid(काष्ठा net_device *, __be16 proto, u16);
अटल पूर्णांक fjes_vlan_rx_समाप्त_vid(काष्ठा net_device *, __be16 proto, u16);
अटल व्योम fjes_tx_retry(काष्ठा net_device *, अचिन्हित पूर्णांक txqueue);

अटल पूर्णांक fjes_acpi_add(काष्ठा acpi_device *);
अटल पूर्णांक fjes_acpi_हटाओ(काष्ठा acpi_device *);
अटल acpi_status fjes_get_acpi_resource(काष्ठा acpi_resource *, व्योम*);

अटल पूर्णांक fjes_probe(काष्ठा platक्रमm_device *);
अटल पूर्णांक fjes_हटाओ(काष्ठा platक्रमm_device *);

अटल पूर्णांक fjes_sw_init(काष्ठा fjes_adapter *);
अटल व्योम fjes_netdev_setup(काष्ठा net_device *);
अटल व्योम fjes_irq_watch_task(काष्ठा work_काष्ठा *);
अटल व्योम fjes_watch_unshare_task(काष्ठा work_काष्ठा *);
अटल व्योम fjes_rx_irq(काष्ठा fjes_adapter *, पूर्णांक);
अटल पूर्णांक fjes_poll(काष्ठा napi_काष्ठा *, पूर्णांक);

अटल स्थिर काष्ठा acpi_device_id fjes_acpi_ids[] = अणु
	अणुACPI_MOTHERBOARD_RESOURCE_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, fjes_acpi_ids);

अटल काष्ठा acpi_driver fjes_acpi_driver = अणु
	.name = DRV_NAME,
	.class = DRV_NAME,
	.owner = THIS_MODULE,
	.ids = fjes_acpi_ids,
	.ops = अणु
		.add = fjes_acpi_add,
		.हटाओ = fjes_acpi_हटाओ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fjes_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = fjes_probe,
	.हटाओ = fjes_हटाओ,
पूर्ण;

अटल काष्ठा resource fjes_resource[] = अणु
	अणु
		.flags = IORESOURCE_MEM,
		.start = 0,
		.end = 0,
	पूर्ण,
	अणु
		.flags = IORESOURCE_IRQ,
		.start = 0,
		.end = 0,
	पूर्ण,
पूर्ण;

अटल bool is_extended_socket_device(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	अक्षर str_buf[माप(FJES_ACPI_SYMBOL) + 1];
	जोड़ acpi_object *str;
	acpi_status status;
	पूर्णांक result;

	status = acpi_evaluate_object(device->handle, "_STR", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस false;

	str = buffer.poपूर्णांकer;
	result = utf16s_to_utf8s((ब_अक्षर_प्रकार *)str->string.poपूर्णांकer,
				 str->string.length, UTF16_LITTLE_ENDIAN,
				 str_buf, माप(str_buf) - 1);
	str_buf[result] = 0;

	अगर (म_भेदन(FJES_ACPI_SYMBOL, str_buf, म_माप(FJES_ACPI_SYMBOL)) != 0) अणु
		kमुक्त(buffer.poपूर्णांकer);
		वापस false;
	पूर्ण
	kमुक्त(buffer.poपूर्णांकer);

	वापस true;
पूर्ण

अटल पूर्णांक acpi_check_extended_socket_status(काष्ठा acpi_device *device)
अणु
	अचिन्हित दीर्घ दीर्घ sta;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(device->handle, "_STA", शून्य, &sta);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	अगर (!((sta & ACPI_STA_DEVICE_PRESENT) &&
	      (sta & ACPI_STA_DEVICE_ENABLED) &&
	      (sta & ACPI_STA_DEVICE_UI) &&
	      (sta & ACPI_STA_DEVICE_FUNCTIONING)))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक fjes_acpi_add(काष्ठा acpi_device *device)
अणु
	काष्ठा platक्रमm_device *plat_dev;
	acpi_status status;

	अगर (!is_extended_socket_device(device))
		वापस -ENODEV;

	अगर (acpi_check_extended_socket_status(device))
		वापस -ENODEV;

	status = acpi_walk_resources(device->handle, METHOD_NAME__CRS,
				     fjes_get_acpi_resource, fjes_resource);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	/* create platक्रमm_device */
	plat_dev = platक्रमm_device_रेजिस्टर_simple(DRV_NAME, 0, fjes_resource,
						   ARRAY_SIZE(fjes_resource));
	अगर (IS_ERR(plat_dev))
		वापस PTR_ERR(plat_dev);

	device->driver_data = plat_dev;

	वापस 0;
पूर्ण

अटल पूर्णांक fjes_acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा platक्रमm_device *plat_dev;

	plat_dev = (काष्ठा platक्रमm_device *)acpi_driver_data(device);
	platक्रमm_device_unरेजिस्टर(plat_dev);

	वापस 0;
पूर्ण

अटल acpi_status
fjes_get_acpi_resource(काष्ठा acpi_resource *acpi_res, व्योम *data)
अणु
	काष्ठा acpi_resource_address32 *addr;
	काष्ठा acpi_resource_irq *irq;
	काष्ठा resource *res = data;

	चयन (acpi_res->type) अणु
	हाल ACPI_RESOURCE_TYPE_ADDRESS32:
		addr = &acpi_res->data.address32;
		res[0].start = addr->address.minimum;
		res[0].end = addr->address.minimum +
			addr->address.address_length - 1;
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_IRQ:
		irq = &acpi_res->data.irq;
		अगर (irq->पूर्णांकerrupt_count != 1)
			वापस AE_ERROR;
		res[1].start = irq->पूर्णांकerrupts[0];
		res[1].end = irq->पूर्णांकerrupts[0];
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल पूर्णांक fjes_request_irq(काष्ठा fjes_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक result = -1;

	adapter->पूर्णांकerrupt_watch_enable = true;
	अगर (!delayed_work_pending(&adapter->पूर्णांकerrupt_watch_task)) अणु
		queue_delayed_work(adapter->control_wq,
				   &adapter->पूर्णांकerrupt_watch_task,
				   FJES_IRQ_WATCH_DELAY);
	पूर्ण

	अगर (!adapter->irq_रेजिस्टरed) अणु
		result = request_irq(adapter->hw.hw_res.irq, fjes_पूर्णांकr,
				     IRQF_SHARED, netdev->name, adapter);
		अगर (result)
			adapter->irq_रेजिस्टरed = false;
		अन्यथा
			adapter->irq_रेजिस्टरed = true;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम fjes_मुक्त_irq(काष्ठा fjes_adapter *adapter)
अणु
	काष्ठा fjes_hw *hw = &adapter->hw;

	adapter->पूर्णांकerrupt_watch_enable = false;
	cancel_delayed_work_sync(&adapter->पूर्णांकerrupt_watch_task);

	fjes_hw_set_irqmask(hw, REG_ICTL_MASK_ALL, true);

	अगर (adapter->irq_रेजिस्टरed) अणु
		मुक्त_irq(adapter->hw.hw_res.irq, adapter);
		adapter->irq_रेजिस्टरed = false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops fjes_netdev_ops = अणु
	.nकरो_खोलो		= fjes_खोलो,
	.nकरो_stop		= fjes_बंद,
	.nकरो_start_xmit		= fjes_xmit_frame,
	.nकरो_get_stats64	= fjes_get_stats64,
	.nकरो_change_mtu		= fjes_change_mtu,
	.nकरो_tx_समयout		= fjes_tx_retry,
	.nकरो_vlan_rx_add_vid	= fjes_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = fjes_vlan_rx_समाप्त_vid,
पूर्ण;

/* fjes_खोलो - Called when a network पूर्णांकerface is made active */
अटल पूर्णांक fjes_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;
	पूर्णांक result;

	अगर (adapter->खोलो_guard)
		वापस -ENXIO;

	result = fjes_setup_resources(adapter);
	अगर (result)
		जाओ err_setup_res;

	hw->txrx_stop_req_bit = 0;
	hw->epstop_req_bit = 0;

	napi_enable(&adapter->napi);

	fjes_hw_capture_पूर्णांकerrupt_status(hw);

	result = fjes_request_irq(adapter);
	अगर (result)
		जाओ err_req_irq;

	fjes_hw_set_irqmask(hw, REG_ICTL_MASK_ALL, false);

	netअगर_tx_start_all_queues(netdev);
	netअगर_carrier_on(netdev);

	वापस 0;

err_req_irq:
	fjes_मुक्त_irq(adapter);
	napi_disable(&adapter->napi);

err_setup_res:
	fjes_मुक्त_resources(adapter);
	वापस result;
पूर्ण

/* fjes_बंद - Disables a network पूर्णांकerface */
अटल पूर्णांक fjes_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;
	पूर्णांक epidx;

	netअगर_tx_stop_all_queues(netdev);
	netअगर_carrier_off(netdev);

	fjes_hw_उठाओ_epstop(hw);

	napi_disable(&adapter->napi);

	spin_lock_irqsave(&hw->rx_status_lock, flags);
	क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
		अगर (epidx == hw->my_epid)
			जारी;

		अगर (fjes_hw_get_partner_ep_status(hw, epidx) ==
		    EP_PARTNER_SHARED)
			adapter->hw.ep_shm_info[epidx]
				   .tx.info->v1i.rx_status &=
				~FJES_RX_POLL_WORK;
	पूर्ण
	spin_unlock_irqrestore(&hw->rx_status_lock, flags);

	fjes_मुक्त_irq(adapter);

	cancel_delayed_work_sync(&adapter->पूर्णांकerrupt_watch_task);
	cancel_work_sync(&adapter->unshare_watch_task);
	adapter->unshare_watch_biपंचांगask = 0;
	cancel_work_sync(&adapter->उठाओ_पूर्णांकr_rxdata_task);
	cancel_work_sync(&adapter->tx_stall_task);

	cancel_work_sync(&hw->update_zone_task);
	cancel_work_sync(&hw->epstop_task);

	fjes_hw_रुको_epstop(hw);

	fjes_मुक्त_resources(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक fjes_setup_resources(काष्ठा fjes_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ep_share_mem_info *buf_pair;
	काष्ठा fjes_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;
	पूर्णांक epidx;

	mutex_lock(&hw->hw_info.lock);
	result = fjes_hw_request_info(hw);
	चयन (result) अणु
	हाल 0:
		क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
			hw->ep_shm_info[epidx].es_status =
			    hw->hw_info.res_buf->info.info[epidx].es_status;
			hw->ep_shm_info[epidx].zone =
			    hw->hw_info.res_buf->info.info[epidx].zone;
		पूर्ण
		अवरोध;
	शेष:
	हाल -ENOMSG:
	हाल -EBUSY:
		adapter->क्रमce_reset = true;

		mutex_unlock(&hw->hw_info.lock);
		वापस result;
	पूर्ण
	mutex_unlock(&hw->hw_info.lock);

	क्रम (epidx = 0; epidx < (hw->max_epid); epidx++) अणु
		अगर ((epidx != hw->my_epid) &&
		    (hw->ep_shm_info[epidx].es_status ==
		     FJES_ZONING_STATUS_ENABLE)) अणु
			fjes_hw_उठाओ_पूर्णांकerrupt(hw, epidx,
						REG_ICTL_MASK_INFO_UPDATE);
			hw->ep_shm_info[epidx].ep_stats
				.send_पूर्णांकr_zoneupdate += 1;
		पूर्ण
	पूर्ण

	msleep(FJES_OPEN_ZONE_UPDATE_WAIT * hw->max_epid);

	क्रम (epidx = 0; epidx < (hw->max_epid); epidx++) अणु
		अगर (epidx == hw->my_epid)
			जारी;

		buf_pair = &hw->ep_shm_info[epidx];

		spin_lock_irqsave(&hw->rx_status_lock, flags);
		fjes_hw_setup_epbuf(&buf_pair->tx, netdev->dev_addr,
				    netdev->mtu);
		spin_unlock_irqrestore(&hw->rx_status_lock, flags);

		अगर (fjes_hw_epid_is_same_zone(hw, epidx)) अणु
			mutex_lock(&hw->hw_info.lock);
			result =
			fjes_hw_रेजिस्टर_buff_addr(hw, epidx, buf_pair);
			mutex_unlock(&hw->hw_info.lock);

			चयन (result) अणु
			हाल 0:
				अवरोध;
			हाल -ENOMSG:
			हाल -EBUSY:
			शेष:
				adapter->क्रमce_reset = true;
				वापस result;
			पूर्ण

			hw->ep_shm_info[epidx].ep_stats
				.com_regist_buf_exec += 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fjes_मुक्त_resources(काष्ठा fjes_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा fjes_device_command_param param;
	काष्ठा ep_share_mem_info *buf_pair;
	काष्ठा fjes_hw *hw = &adapter->hw;
	bool reset_flag = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;
	पूर्णांक epidx;

	क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
		अगर (epidx == hw->my_epid)
			जारी;

		mutex_lock(&hw->hw_info.lock);
		result = fjes_hw_unरेजिस्टर_buff_addr(hw, epidx);
		mutex_unlock(&hw->hw_info.lock);

		hw->ep_shm_info[epidx].ep_stats.com_unregist_buf_exec += 1;

		अगर (result)
			reset_flag = true;

		buf_pair = &hw->ep_shm_info[epidx];

		spin_lock_irqsave(&hw->rx_status_lock, flags);
		fjes_hw_setup_epbuf(&buf_pair->tx,
				    netdev->dev_addr, netdev->mtu);
		spin_unlock_irqrestore(&hw->rx_status_lock, flags);

		clear_bit(epidx, &hw->txrx_stop_req_bit);
	पूर्ण

	अगर (reset_flag || adapter->क्रमce_reset) अणु
		result = fjes_hw_reset(hw);

		adapter->क्रमce_reset = false;

		अगर (result)
			adapter->खोलो_guard = true;

		hw->hw_info.buffer_share_bit = 0;

		स_रखो((व्योम *)&param, 0, माप(param));

		param.req_len = hw->hw_info.req_buf_size;
		param.req_start = __pa(hw->hw_info.req_buf);
		param.res_len = hw->hw_info.res_buf_size;
		param.res_start = __pa(hw->hw_info.res_buf);
		param.share_start = __pa(hw->hw_info.share->ep_status);

		fjes_hw_init_command_रेजिस्टरs(hw, &param);
	पूर्ण
पूर्ण

अटल व्योम fjes_tx_stall_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fjes_adapter *adapter = container_of(work,
			काष्ठा fjes_adapter, tx_stall_task);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा fjes_hw *hw = &adapter->hw;
	पूर्णांक all_queue_available, sendable;
	क्रमागत ep_partner_status pstatus;
	पूर्णांक max_epid, my_epid, epid;
	जोड़ ep_buffer_info *info;
	पूर्णांक i;

	अगर (((दीर्घ)jअगरfies -
		dev_trans_start(netdev)) > FJES_TX_TX_STALL_TIMEOUT) अणु
		netअगर_wake_queue(netdev);
		वापस;
	पूर्ण

	my_epid = hw->my_epid;
	max_epid = hw->max_epid;

	क्रम (i = 0; i < 5; i++) अणु
		all_queue_available = 1;

		क्रम (epid = 0; epid < max_epid; epid++) अणु
			अगर (my_epid == epid)
				जारी;

			pstatus = fjes_hw_get_partner_ep_status(hw, epid);
			sendable = (pstatus == EP_PARTNER_SHARED);
			अगर (!sendable)
				जारी;

			info = adapter->hw.ep_shm_info[epid].tx.info;

			अगर (!(info->v1i.rx_status & FJES_RX_MTU_CHANGING_DONE))
				वापस;

			अगर (EP_RING_FULL(info->v1i.head, info->v1i.tail,
					 info->v1i.count_max)) अणु
				all_queue_available = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (all_queue_available) अणु
			netअगर_wake_queue(netdev);
			वापस;
		पूर्ण
	पूर्ण

	usleep_range(50, 100);

	queue_work(adapter->txrx_wq, &adapter->tx_stall_task);
पूर्ण

अटल व्योम fjes_क्रमce_बंद_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fjes_adapter *adapter = container_of(work,
			काष्ठा fjes_adapter, क्रमce_बंद_task);
	काष्ठा net_device *netdev = adapter->netdev;

	rtnl_lock();
	dev_बंद(netdev);
	rtnl_unlock();
पूर्ण

अटल व्योम fjes_उठाओ_पूर्णांकr_rxdata_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fjes_adapter *adapter = container_of(work,
			काष्ठा fjes_adapter, उठाओ_पूर्णांकr_rxdata_task);
	काष्ठा fjes_hw *hw = &adapter->hw;
	क्रमागत ep_partner_status pstatus;
	पूर्णांक max_epid, my_epid, epid;

	my_epid = hw->my_epid;
	max_epid = hw->max_epid;

	क्रम (epid = 0; epid < max_epid; epid++)
		hw->ep_shm_info[epid].tx_status_work = 0;

	क्रम (epid = 0; epid < max_epid; epid++) अणु
		अगर (epid == my_epid)
			जारी;

		pstatus = fjes_hw_get_partner_ep_status(hw, epid);
		अगर (pstatus == EP_PARTNER_SHARED) अणु
			hw->ep_shm_info[epid].tx_status_work =
				hw->ep_shm_info[epid].tx.info->v1i.tx_status;

			अगर (hw->ep_shm_info[epid].tx_status_work ==
				FJES_TX_DELAY_SEND_PENDING) अणु
				hw->ep_shm_info[epid].tx.info->v1i.tx_status =
					FJES_TX_DELAY_SEND_NONE;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (epid = 0; epid < max_epid; epid++) अणु
		अगर (epid == my_epid)
			जारी;

		pstatus = fjes_hw_get_partner_ep_status(hw, epid);
		अगर ((hw->ep_shm_info[epid].tx_status_work ==
		     FJES_TX_DELAY_SEND_PENDING) &&
		    (pstatus == EP_PARTNER_SHARED) &&
		    !(hw->ep_shm_info[epid].rx.info->v1i.rx_status &
		      FJES_RX_POLL_WORK)) अणु
			fjes_hw_उठाओ_पूर्णांकerrupt(hw, epid,
						REG_ICTL_MASK_RX_DATA);
			hw->ep_shm_info[epid].ep_stats.send_पूर्णांकr_rx += 1;
		पूर्ण
	पूर्ण

	usleep_range(500, 1000);
पूर्ण

अटल पूर्णांक fjes_tx_send(काष्ठा fjes_adapter *adapter, पूर्णांक dest,
			व्योम *data, माप_प्रकार len)
अणु
	पूर्णांक retval;

	retval = fjes_hw_epbuf_tx_pkt_send(&adapter->hw.ep_shm_info[dest].tx,
					   data, len);
	अगर (retval)
		वापस retval;

	adapter->hw.ep_shm_info[dest].tx.info->v1i.tx_status =
		FJES_TX_DELAY_SEND_PENDING;
	अगर (!work_pending(&adapter->उठाओ_पूर्णांकr_rxdata_task))
		queue_work(adapter->txrx_wq,
			   &adapter->उठाओ_पूर्णांकr_rxdata_task);

	retval = 0;
	वापस retval;
पूर्ण

अटल netdev_tx_t
fjes_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;

	पूर्णांक max_epid, my_epid, dest_epid;
	क्रमागत ep_partner_status pstatus;
	काष्ठा netdev_queue *cur_queue;
	अक्षर लघुpkt[VLAN_ETH_HLEN];
	bool is_multi, vlan;
	काष्ठा ethhdr *eth;
	u16 queue_no = 0;
	u16 vlan_id = 0;
	netdev_tx_t ret;
	अक्षर *data;
	पूर्णांक len;

	ret = NETDEV_TX_OK;
	is_multi = false;
	cur_queue = netdev_get_tx_queue(netdev, queue_no);

	eth = (काष्ठा ethhdr *)skb->data;
	my_epid = hw->my_epid;

	vlan = (vlan_get_tag(skb, &vlan_id) == 0) ? true : false;

	data = skb->data;
	len = skb->len;

	अगर (is_multicast_ether_addr(eth->h_dest)) अणु
		dest_epid = 0;
		max_epid = hw->max_epid;
		is_multi = true;
	पूर्ण अन्यथा अगर (is_local_ether_addr(eth->h_dest)) अणु
		dest_epid = eth->h_dest[ETH_ALEN - 1];
		max_epid = dest_epid + 1;

		अगर ((eth->h_dest[0] == 0x02) &&
		    (0x00 == (eth->h_dest[1] | eth->h_dest[2] |
			      eth->h_dest[3] | eth->h_dest[4])) &&
		    (dest_epid < hw->max_epid)) अणु
			;
		पूर्ण अन्यथा अणु
			dest_epid = 0;
			max_epid = 0;
			ret = NETDEV_TX_OK;

			adapter->stats64.tx_packets += 1;
			hw->ep_shm_info[my_epid].net_stats.tx_packets += 1;
			adapter->stats64.tx_bytes += len;
			hw->ep_shm_info[my_epid].net_stats.tx_bytes += len;
		पूर्ण
	पूर्ण अन्यथा अणु
		dest_epid = 0;
		max_epid = 0;
		ret = NETDEV_TX_OK;

		adapter->stats64.tx_packets += 1;
		hw->ep_shm_info[my_epid].net_stats.tx_packets += 1;
		adapter->stats64.tx_bytes += len;
		hw->ep_shm_info[my_epid].net_stats.tx_bytes += len;
	पूर्ण

	क्रम (; dest_epid < max_epid; dest_epid++) अणु
		अगर (my_epid == dest_epid)
			जारी;

		pstatus = fjes_hw_get_partner_ep_status(hw, dest_epid);
		अगर (pstatus != EP_PARTNER_SHARED) अणु
			अगर (!is_multi)
				hw->ep_shm_info[dest_epid].ep_stats
					.tx_dropped_not_shared += 1;
			ret = NETDEV_TX_OK;
		पूर्ण अन्यथा अगर (!fjes_hw_check_epbuf_version(
				&adapter->hw.ep_shm_info[dest_epid].rx, 0)) अणु
			/* version is NOT 0 */
			adapter->stats64.tx_carrier_errors += 1;
			hw->ep_shm_info[dest_epid].net_stats
						.tx_carrier_errors += 1;
			hw->ep_shm_info[dest_epid].ep_stats
					.tx_dropped_ver_mismatch += 1;

			ret = NETDEV_TX_OK;
		पूर्ण अन्यथा अगर (!fjes_hw_check_mtu(
				&adapter->hw.ep_shm_info[dest_epid].rx,
				netdev->mtu)) अणु
			adapter->stats64.tx_dropped += 1;
			hw->ep_shm_info[dest_epid].net_stats.tx_dropped += 1;
			adapter->stats64.tx_errors += 1;
			hw->ep_shm_info[dest_epid].net_stats.tx_errors += 1;
			hw->ep_shm_info[dest_epid].ep_stats
					.tx_dropped_buf_size_mismatch += 1;

			ret = NETDEV_TX_OK;
		पूर्ण अन्यथा अगर (vlan &&
			   !fjes_hw_check_vlan_id(
				&adapter->hw.ep_shm_info[dest_epid].rx,
				vlan_id)) अणु
			hw->ep_shm_info[dest_epid].ep_stats
				.tx_dropped_vlanid_mismatch += 1;
			ret = NETDEV_TX_OK;
		पूर्ण अन्यथा अणु
			अगर (len < VLAN_ETH_HLEN) अणु
				स_रखो(लघुpkt, 0, VLAN_ETH_HLEN);
				स_नकल(लघुpkt, skb->data, skb->len);
				len = VLAN_ETH_HLEN;
				data = लघुpkt;
			पूर्ण

			अगर (adapter->tx_retry_count == 0) अणु
				adapter->tx_start_jअगरfies = jअगरfies;
				adapter->tx_retry_count = 1;
			पूर्ण अन्यथा अणु
				adapter->tx_retry_count++;
			पूर्ण

			अगर (fjes_tx_send(adapter, dest_epid, data, len)) अणु
				अगर (is_multi) अणु
					ret = NETDEV_TX_OK;
				पूर्ण अन्यथा अगर (
					   ((दीर्घ)jअगरfies -
					    (दीर्घ)adapter->tx_start_jअगरfies) >=
					    FJES_TX_RETRY_TIMEOUT) अणु
					adapter->stats64.tx_fअगरo_errors += 1;
					hw->ep_shm_info[dest_epid].net_stats
								.tx_fअगरo_errors += 1;
					adapter->stats64.tx_errors += 1;
					hw->ep_shm_info[dest_epid].net_stats
								.tx_errors += 1;

					ret = NETDEV_TX_OK;
				पूर्ण अन्यथा अणु
					netअगर_trans_update(netdev);
					hw->ep_shm_info[dest_epid].ep_stats
						.tx_buffer_full += 1;
					netअगर_tx_stop_queue(cur_queue);

					अगर (!work_pending(&adapter->tx_stall_task))
						queue_work(adapter->txrx_wq,
							   &adapter->tx_stall_task);

					ret = NETDEV_TX_BUSY;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (!is_multi) अणु
					adapter->stats64.tx_packets += 1;
					hw->ep_shm_info[dest_epid].net_stats
								.tx_packets += 1;
					adapter->stats64.tx_bytes += len;
					hw->ep_shm_info[dest_epid].net_stats
								.tx_bytes += len;
				पूर्ण

				adapter->tx_retry_count = 0;
				ret = NETDEV_TX_OK;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ret == NETDEV_TX_OK) अणु
		dev_kमुक्त_skb(skb);
		अगर (is_multi) अणु
			adapter->stats64.tx_packets += 1;
			hw->ep_shm_info[my_epid].net_stats.tx_packets += 1;
			adapter->stats64.tx_bytes += 1;
			hw->ep_shm_info[my_epid].net_stats.tx_bytes += len;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम fjes_tx_retry(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा netdev_queue *queue = netdev_get_tx_queue(netdev, 0);

	netअगर_tx_wake_queue(queue);
पूर्ण

अटल व्योम
fjes_get_stats64(काष्ठा net_device *netdev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);

	स_नकल(stats, &adapter->stats64, माप(काष्ठा rtnl_link_stats64));
पूर्ण

अटल पूर्णांक fjes_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	bool running = netअगर_running(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;
	पूर्णांक idx, epidx;

	क्रम (idx = 0; fjes_support_mtu[idx] != 0; idx++) अणु
		अगर (new_mtu <= fjes_support_mtu[idx]) अणु
			new_mtu = fjes_support_mtu[idx];
			अगर (new_mtu == netdev->mtu)
				वापस 0;

			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस ret;

	अगर (running) अणु
		spin_lock_irqsave(&hw->rx_status_lock, flags);
		क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
			अगर (epidx == hw->my_epid)
				जारी;
			hw->ep_shm_info[epidx].tx.info->v1i.rx_status &=
				~FJES_RX_MTU_CHANGING_DONE;
		पूर्ण
		spin_unlock_irqrestore(&hw->rx_status_lock, flags);

		netअगर_tx_stop_all_queues(netdev);
		netअगर_carrier_off(netdev);
		cancel_work_sync(&adapter->tx_stall_task);
		napi_disable(&adapter->napi);

		msleep(1000);

		netअगर_tx_stop_all_queues(netdev);
	पूर्ण

	netdev->mtu = new_mtu;

	अगर (running) अणु
		क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
			अगर (epidx == hw->my_epid)
				जारी;

			spin_lock_irqsave(&hw->rx_status_lock, flags);
			fjes_hw_setup_epbuf(&hw->ep_shm_info[epidx].tx,
					    netdev->dev_addr,
					    netdev->mtu);

			hw->ep_shm_info[epidx].tx.info->v1i.rx_status |=
				FJES_RX_MTU_CHANGING_DONE;
			spin_unlock_irqrestore(&hw->rx_status_lock, flags);
		पूर्ण

		netअगर_tx_wake_all_queues(netdev);
		netअगर_carrier_on(netdev);
		napi_enable(&adapter->napi);
		napi_schedule(&adapter->napi);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fjes_vlan_rx_add_vid(काष्ठा net_device *netdev,
				__be16 proto, u16 vid)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	bool ret = true;
	पूर्णांक epid;

	क्रम (epid = 0; epid < adapter->hw.max_epid; epid++) अणु
		अगर (epid == adapter->hw.my_epid)
			जारी;

		अगर (!fjes_hw_check_vlan_id(
			&adapter->hw.ep_shm_info[epid].tx, vid))
			ret = fjes_hw_set_vlan_id(
				&adapter->hw.ep_shm_info[epid].tx, vid);
	पूर्ण

	वापस ret ? 0 : -ENOSPC;
पूर्ण

अटल पूर्णांक fjes_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				 __be16 proto, u16 vid)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	पूर्णांक epid;

	क्रम (epid = 0; epid < adapter->hw.max_epid; epid++) अणु
		अगर (epid == adapter->hw.my_epid)
			जारी;

		fjes_hw_del_vlan_id(&adapter->hw.ep_shm_info[epid].tx, vid);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fjes_txrx_stop_req_irq(काष्ठा fjes_adapter *adapter,
				   पूर्णांक src_epid)
अणु
	काष्ठा fjes_hw *hw = &adapter->hw;
	क्रमागत ep_partner_status status;
	अचिन्हित दीर्घ flags;

	status = fjes_hw_get_partner_ep_status(hw, src_epid);
	trace_fjes_txrx_stop_req_irq_pre(hw, src_epid, status);
	चयन (status) अणु
	हाल EP_PARTNER_UNSHARE:
	हाल EP_PARTNER_COMPLETE:
	शेष:
		अवरोध;
	हाल EP_PARTNER_WAITING:
		अगर (src_epid < hw->my_epid) अणु
			spin_lock_irqsave(&hw->rx_status_lock, flags);
			hw->ep_shm_info[src_epid].tx.info->v1i.rx_status |=
				FJES_RX_STOP_REQ_DONE;
			spin_unlock_irqrestore(&hw->rx_status_lock, flags);

			clear_bit(src_epid, &hw->txrx_stop_req_bit);
			set_bit(src_epid, &adapter->unshare_watch_biपंचांगask);

			अगर (!work_pending(&adapter->unshare_watch_task))
				queue_work(adapter->control_wq,
					   &adapter->unshare_watch_task);
		पूर्ण
		अवरोध;
	हाल EP_PARTNER_SHARED:
		अगर (hw->ep_shm_info[src_epid].rx.info->v1i.rx_status &
		    FJES_RX_STOP_REQ_REQUEST) अणु
			set_bit(src_epid, &hw->epstop_req_bit);
			अगर (!work_pending(&hw->epstop_task))
				queue_work(adapter->control_wq,
					   &hw->epstop_task);
		पूर्ण
		अवरोध;
	पूर्ण
	trace_fjes_txrx_stop_req_irq_post(hw, src_epid);
पूर्ण

अटल व्योम fjes_stop_req_irq(काष्ठा fjes_adapter *adapter, पूर्णांक src_epid)
अणु
	काष्ठा fjes_hw *hw = &adapter->hw;
	क्रमागत ep_partner_status status;
	अचिन्हित दीर्घ flags;

	set_bit(src_epid, &hw->hw_info.buffer_unshare_reserve_bit);

	status = fjes_hw_get_partner_ep_status(hw, src_epid);
	trace_fjes_stop_req_irq_pre(hw, src_epid, status);
	चयन (status) अणु
	हाल EP_PARTNER_WAITING:
		spin_lock_irqsave(&hw->rx_status_lock, flags);
		hw->ep_shm_info[src_epid].tx.info->v1i.rx_status |=
				FJES_RX_STOP_REQ_DONE;
		spin_unlock_irqrestore(&hw->rx_status_lock, flags);
		clear_bit(src_epid, &hw->txrx_stop_req_bit);
		fallthrough;
	हाल EP_PARTNER_UNSHARE:
	हाल EP_PARTNER_COMPLETE:
	शेष:
		set_bit(src_epid, &adapter->unshare_watch_biपंचांगask);
		अगर (!work_pending(&adapter->unshare_watch_task))
			queue_work(adapter->control_wq,
				   &adapter->unshare_watch_task);
		अवरोध;
	हाल EP_PARTNER_SHARED:
		set_bit(src_epid, &hw->epstop_req_bit);

		अगर (!work_pending(&hw->epstop_task))
			queue_work(adapter->control_wq, &hw->epstop_task);
		अवरोध;
	पूर्ण
	trace_fjes_stop_req_irq_post(hw, src_epid);
पूर्ण

अटल व्योम fjes_update_zone_irq(काष्ठा fjes_adapter *adapter,
				 पूर्णांक src_epid)
अणु
	काष्ठा fjes_hw *hw = &adapter->hw;

	अगर (!work_pending(&hw->update_zone_task))
		queue_work(adapter->control_wq, &hw->update_zone_task);
पूर्ण

अटल irqवापस_t fjes_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fjes_adapter *adapter = data;
	काष्ठा fjes_hw *hw = &adapter->hw;
	irqवापस_t ret;
	u32 icr;

	icr = fjes_hw_capture_पूर्णांकerrupt_status(hw);

	अगर (icr & REG_IS_MASK_IS_ASSERT) अणु
		अगर (icr & REG_ICTL_MASK_RX_DATA) अणु
			fjes_rx_irq(adapter, icr & REG_IS_MASK_EPID);
			hw->ep_shm_info[icr & REG_IS_MASK_EPID].ep_stats
				.recv_पूर्णांकr_rx += 1;
		पूर्ण

		अगर (icr & REG_ICTL_MASK_DEV_STOP_REQ) अणु
			fjes_stop_req_irq(adapter, icr & REG_IS_MASK_EPID);
			hw->ep_shm_info[icr & REG_IS_MASK_EPID].ep_stats
				.recv_पूर्णांकr_stop += 1;
		पूर्ण

		अगर (icr & REG_ICTL_MASK_TXRX_STOP_REQ) अणु
			fjes_txrx_stop_req_irq(adapter, icr & REG_IS_MASK_EPID);
			hw->ep_shm_info[icr & REG_IS_MASK_EPID].ep_stats
				.recv_पूर्णांकr_unshare += 1;
		पूर्ण

		अगर (icr & REG_ICTL_MASK_TXRX_STOP_DONE)
			fjes_hw_set_irqmask(hw,
					    REG_ICTL_MASK_TXRX_STOP_DONE, true);

		अगर (icr & REG_ICTL_MASK_INFO_UPDATE) अणु
			fjes_update_zone_irq(adapter, icr & REG_IS_MASK_EPID);
			hw->ep_shm_info[icr & REG_IS_MASK_EPID].ep_stats
				.recv_पूर्णांकr_zoneupdate += 1;
		पूर्ण

		ret = IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		ret = IRQ_NONE;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fjes_rxframe_search_exist(काष्ठा fjes_adapter *adapter,
				     पूर्णांक start_epid)
अणु
	काष्ठा fjes_hw *hw = &adapter->hw;
	क्रमागत ep_partner_status pstatus;
	पूर्णांक max_epid, cur_epid;
	पूर्णांक i;

	max_epid = hw->max_epid;
	start_epid = (start_epid + 1 + max_epid) % max_epid;

	क्रम (i = 0; i < max_epid; i++) अणु
		cur_epid = (start_epid + i) % max_epid;
		अगर (cur_epid == hw->my_epid)
			जारी;

		pstatus = fjes_hw_get_partner_ep_status(hw, cur_epid);
		अगर (pstatus == EP_PARTNER_SHARED) अणु
			अगर (!fjes_hw_epbuf_rx_is_empty(
				&hw->ep_shm_info[cur_epid].rx))
				वापस cur_epid;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम *fjes_rxframe_get(काष्ठा fjes_adapter *adapter, माप_प्रकार *psize,
			      पूर्णांक *cur_epid)
अणु
	व्योम *frame;

	*cur_epid = fjes_rxframe_search_exist(adapter, *cur_epid);
	अगर (*cur_epid < 0)
		वापस शून्य;

	frame =
	fjes_hw_epbuf_rx_curpkt_get_addr(
		&adapter->hw.ep_shm_info[*cur_epid].rx, psize);

	वापस frame;
पूर्ण

अटल व्योम fjes_rxframe_release(काष्ठा fjes_adapter *adapter, पूर्णांक cur_epid)
अणु
	fjes_hw_epbuf_rx_curpkt_drop(&adapter->hw.ep_shm_info[cur_epid].rx);
पूर्ण

अटल व्योम fjes_rx_irq(काष्ठा fjes_adapter *adapter, पूर्णांक src_epid)
अणु
	काष्ठा fjes_hw *hw = &adapter->hw;

	fjes_hw_set_irqmask(hw, REG_ICTL_MASK_RX_DATA, true);

	adapter->unset_rx_last = true;
	napi_schedule(&adapter->napi);
पूर्ण

अटल पूर्णांक fjes_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा fjes_adapter *adapter =
			container_of(napi, काष्ठा fjes_adapter, napi);
	काष्ठा net_device *netdev = napi->dev;
	काष्ठा fjes_hw *hw = &adapter->hw;
	काष्ठा sk_buff *skb;
	पूर्णांक work_करोne = 0;
	पूर्णांक cur_epid = 0;
	पूर्णांक epidx;
	माप_प्रकार frame_len;
	व्योम *frame;

	spin_lock(&hw->rx_status_lock);
	क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
		अगर (epidx == hw->my_epid)
			जारी;

		अगर (fjes_hw_get_partner_ep_status(hw, epidx) ==
		    EP_PARTNER_SHARED)
			adapter->hw.ep_shm_info[epidx]
				   .tx.info->v1i.rx_status |= FJES_RX_POLL_WORK;
	पूर्ण
	spin_unlock(&hw->rx_status_lock);

	जबतक (work_करोne < budget) अणु
		prefetch(&adapter->hw);
		frame = fjes_rxframe_get(adapter, &frame_len, &cur_epid);

		अगर (frame) अणु
			skb = napi_alloc_skb(napi, frame_len);
			अगर (!skb) अणु
				adapter->stats64.rx_dropped += 1;
				hw->ep_shm_info[cur_epid].net_stats
							 .rx_dropped += 1;
				adapter->stats64.rx_errors += 1;
				hw->ep_shm_info[cur_epid].net_stats
							 .rx_errors += 1;
			पूर्ण अन्यथा अणु
				skb_put_data(skb, frame, frame_len);
				skb->protocol = eth_type_trans(skb, netdev);
				skb->ip_summed = CHECKSUM_UNNECESSARY;

				netअगर_receive_skb(skb);

				work_करोne++;

				adapter->stats64.rx_packets += 1;
				hw->ep_shm_info[cur_epid].net_stats
							 .rx_packets += 1;
				adapter->stats64.rx_bytes += frame_len;
				hw->ep_shm_info[cur_epid].net_stats
							 .rx_bytes += frame_len;

				अगर (is_multicast_ether_addr(
					((काष्ठा ethhdr *)frame)->h_dest)) अणु
					adapter->stats64.multicast += 1;
					hw->ep_shm_info[cur_epid].net_stats
								 .multicast += 1;
				पूर्ण
			पूर्ण

			fjes_rxframe_release(adapter, cur_epid);
			adapter->unset_rx_last = true;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);

		अगर (adapter->unset_rx_last) अणु
			adapter->rx_last_jअगरfies = jअगरfies;
			adapter->unset_rx_last = false;
		पूर्ण

		अगर (((दीर्घ)jअगरfies - (दीर्घ)adapter->rx_last_jअगरfies) < 3) अणु
			napi_reschedule(napi);
		पूर्ण अन्यथा अणु
			spin_lock(&hw->rx_status_lock);
			क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
				अगर (epidx == hw->my_epid)
					जारी;
				अगर (fjes_hw_get_partner_ep_status(hw, epidx) ==
				    EP_PARTNER_SHARED)
					adapter->hw.ep_shm_info[epidx].tx
						   .info->v1i.rx_status &=
						~FJES_RX_POLL_WORK;
			पूर्ण
			spin_unlock(&hw->rx_status_lock);

			fjes_hw_set_irqmask(hw, REG_ICTL_MASK_RX_DATA, false);
		पूर्ण
	पूर्ण

	वापस work_करोne;
पूर्ण

/* fjes_probe - Device Initialization Routine */
अटल पूर्णांक fjes_probe(काष्ठा platक्रमm_device *plat_dev)
अणु
	काष्ठा fjes_adapter *adapter;
	काष्ठा net_device *netdev;
	काष्ठा resource *res;
	काष्ठा fjes_hw *hw;
	पूर्णांक err;

	err = -ENOMEM;
	netdev = alloc_netdev_mq(माप(काष्ठा fjes_adapter), "es%d",
				 NET_NAME_UNKNOWN, fjes_netdev_setup,
				 FJES_MAX_QUEUES);

	अगर (!netdev)
		जाओ err_out;

	SET_NETDEV_DEV(netdev, &plat_dev->dev);

	dev_set_drvdata(&plat_dev->dev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->plat_dev = plat_dev;
	hw = &adapter->hw;
	hw->back = adapter;

	/* setup the निजी काष्ठाure */
	err = fjes_sw_init(adapter);
	अगर (err)
		जाओ err_मुक्त_netdev;

	INIT_WORK(&adapter->क्रमce_बंद_task, fjes_क्रमce_बंद_task);
	adapter->क्रमce_reset = false;
	adapter->खोलो_guard = false;

	adapter->txrx_wq = alloc_workqueue(DRV_NAME "/txrx", WQ_MEM_RECLAIM, 0);
	अगर (unlikely(!adapter->txrx_wq)) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_netdev;
	पूर्ण

	adapter->control_wq = alloc_workqueue(DRV_NAME "/control",
					      WQ_MEM_RECLAIM, 0);
	अगर (unlikely(!adapter->control_wq)) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_txrx_wq;
	पूर्ण

	INIT_WORK(&adapter->tx_stall_task, fjes_tx_stall_task);
	INIT_WORK(&adapter->उठाओ_पूर्णांकr_rxdata_task,
		  fjes_उठाओ_पूर्णांकr_rxdata_task);
	INIT_WORK(&adapter->unshare_watch_task, fjes_watch_unshare_task);
	adapter->unshare_watch_biपंचांगask = 0;

	INIT_DELAYED_WORK(&adapter->पूर्णांकerrupt_watch_task, fjes_irq_watch_task);
	adapter->पूर्णांकerrupt_watch_enable = false;

	res = platक्रमm_get_resource(plat_dev, IORESOURCE_MEM, 0);
	hw->hw_res.start = res->start;
	hw->hw_res.size = resource_size(res);
	hw->hw_res.irq = platक्रमm_get_irq(plat_dev, 0);
	err = fjes_hw_init(&adapter->hw);
	अगर (err)
		जाओ err_मुक्त_control_wq;

	/* setup MAC address (02:00:00:00:00:[epid])*/
	netdev->dev_addr[0] = 2;
	netdev->dev_addr[1] = 0;
	netdev->dev_addr[2] = 0;
	netdev->dev_addr[3] = 0;
	netdev->dev_addr[4] = 0;
	netdev->dev_addr[5] = hw->my_epid; /* EPID */

	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_hw_निकास;

	netअगर_carrier_off(netdev);

	fjes_dbg_adapter_init(adapter);

	वापस 0;

err_hw_निकास:
	fjes_hw_निकास(&adapter->hw);
err_मुक्त_control_wq:
	destroy_workqueue(adapter->control_wq);
err_मुक्त_txrx_wq:
	destroy_workqueue(adapter->txrx_wq);
err_मुक्त_netdev:
	मुक्त_netdev(netdev);
err_out:
	वापस err;
पूर्ण

/* fjes_हटाओ - Device Removal Routine */
अटल पूर्णांक fjes_हटाओ(काष्ठा platक्रमm_device *plat_dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(&plat_dev->dev);
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;

	fjes_dbg_adapter_निकास(adapter);

	cancel_delayed_work_sync(&adapter->पूर्णांकerrupt_watch_task);
	cancel_work_sync(&adapter->unshare_watch_task);
	cancel_work_sync(&adapter->उठाओ_पूर्णांकr_rxdata_task);
	cancel_work_sync(&adapter->tx_stall_task);
	अगर (adapter->control_wq)
		destroy_workqueue(adapter->control_wq);
	अगर (adapter->txrx_wq)
		destroy_workqueue(adapter->txrx_wq);

	unरेजिस्टर_netdev(netdev);

	fjes_hw_निकास(hw);

	netअगर_napi_del(&adapter->napi);

	मुक्त_netdev(netdev);

	वापस 0;
पूर्ण

अटल पूर्णांक fjes_sw_init(काष्ठा fjes_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	netअगर_napi_add(netdev, &adapter->napi, fjes_poll, 64);

	वापस 0;
पूर्ण

/* fjes_netdev_setup - netdevice initialization routine */
अटल व्योम fjes_netdev_setup(काष्ठा net_device *netdev)
अणु
	ether_setup(netdev);

	netdev->watchकरोg_समयo = FJES_TX_RETRY_INTERVAL;
	netdev->netdev_ops = &fjes_netdev_ops;
	fjes_set_ethtool_ops(netdev);
	netdev->mtu = fjes_support_mtu[3];
	netdev->min_mtu = fjes_support_mtu[0];
	netdev->max_mtu = fjes_support_mtu[3];
	netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
पूर्ण

अटल व्योम fjes_irq_watch_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fjes_adapter *adapter = container_of(to_delayed_work(work),
			काष्ठा fjes_adapter, पूर्णांकerrupt_watch_task);

	local_irq_disable();
	fjes_पूर्णांकr(adapter->hw.hw_res.irq, adapter);
	local_irq_enable();

	अगर (fjes_rxframe_search_exist(adapter, 0) >= 0)
		napi_schedule(&adapter->napi);

	अगर (adapter->पूर्णांकerrupt_watch_enable) अणु
		अगर (!delayed_work_pending(&adapter->पूर्णांकerrupt_watch_task))
			queue_delayed_work(adapter->control_wq,
					   &adapter->पूर्णांकerrupt_watch_task,
					   FJES_IRQ_WATCH_DELAY);
	पूर्ण
पूर्ण

अटल व्योम fjes_watch_unshare_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fjes_adapter *adapter =
	container_of(work, काष्ठा fjes_adapter, unshare_watch_task);

	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा fjes_hw *hw = &adapter->hw;

	पूर्णांक unshare_watch, unshare_reserve;
	पूर्णांक max_epid, my_epid, epidx;
	पूर्णांक stop_req, stop_req_करोne;
	uदीर्घ unshare_watch_biपंचांगask;
	अचिन्हित दीर्घ flags;
	पूर्णांक रुको_समय = 0;
	पूर्णांक is_shared;
	पूर्णांक ret;

	my_epid = hw->my_epid;
	max_epid = hw->max_epid;

	unshare_watch_biपंचांगask = adapter->unshare_watch_biपंचांगask;
	adapter->unshare_watch_biपंचांगask = 0;

	जबतक ((unshare_watch_biपंचांगask || hw->txrx_stop_req_bit) &&
	       (रुको_समय < 3000)) अणु
		क्रम (epidx = 0; epidx < max_epid; epidx++) अणु
			अगर (epidx == my_epid)
				जारी;

			is_shared = fjes_hw_epid_is_shared(hw->hw_info.share,
							   epidx);

			stop_req = test_bit(epidx, &hw->txrx_stop_req_bit);

			stop_req_करोne = hw->ep_shm_info[epidx].rx.info->v1i.rx_status &
					FJES_RX_STOP_REQ_DONE;

			unshare_watch = test_bit(epidx, &unshare_watch_biपंचांगask);

			unshare_reserve = test_bit(epidx,
						   &hw->hw_info.buffer_unshare_reserve_bit);

			अगर ((!stop_req ||
			     (is_shared && (!is_shared || !stop_req_करोne))) &&
			    (is_shared || !unshare_watch || !unshare_reserve))
				जारी;

			mutex_lock(&hw->hw_info.lock);
			ret = fjes_hw_unरेजिस्टर_buff_addr(hw, epidx);
			चयन (ret) अणु
			हाल 0:
				अवरोध;
			हाल -ENOMSG:
			हाल -EBUSY:
			शेष:
				अगर (!work_pending(
					&adapter->क्रमce_बंद_task)) अणु
					adapter->क्रमce_reset = true;
					schedule_work(
						&adapter->क्रमce_बंद_task);
				पूर्ण
				अवरोध;
			पूर्ण
			mutex_unlock(&hw->hw_info.lock);
			hw->ep_shm_info[epidx].ep_stats
					.com_unregist_buf_exec += 1;

			spin_lock_irqsave(&hw->rx_status_lock, flags);
			fjes_hw_setup_epbuf(&hw->ep_shm_info[epidx].tx,
					    netdev->dev_addr, netdev->mtu);
			spin_unlock_irqrestore(&hw->rx_status_lock, flags);

			clear_bit(epidx, &hw->txrx_stop_req_bit);
			clear_bit(epidx, &unshare_watch_biपंचांगask);
			clear_bit(epidx,
				  &hw->hw_info.buffer_unshare_reserve_bit);
		पूर्ण

		msleep(100);
		रुको_समय += 100;
	पूर्ण

	अगर (hw->hw_info.buffer_unshare_reserve_bit) अणु
		क्रम (epidx = 0; epidx < max_epid; epidx++) अणु
			अगर (epidx == my_epid)
				जारी;

			अगर (test_bit(epidx,
				     &hw->hw_info.buffer_unshare_reserve_bit)) अणु
				mutex_lock(&hw->hw_info.lock);

				ret = fjes_hw_unरेजिस्टर_buff_addr(hw, epidx);
				चयन (ret) अणु
				हाल 0:
					अवरोध;
				हाल -ENOMSG:
				हाल -EBUSY:
				शेष:
					अगर (!work_pending(
						&adapter->क्रमce_बंद_task)) अणु
						adapter->क्रमce_reset = true;
						schedule_work(
							&adapter->क्रमce_बंद_task);
					पूर्ण
					अवरोध;
				पूर्ण
				mutex_unlock(&hw->hw_info.lock);

				hw->ep_shm_info[epidx].ep_stats
					.com_unregist_buf_exec += 1;

				spin_lock_irqsave(&hw->rx_status_lock, flags);
				fjes_hw_setup_epbuf(
					&hw->ep_shm_info[epidx].tx,
					netdev->dev_addr, netdev->mtu);
				spin_unlock_irqrestore(&hw->rx_status_lock,
						       flags);

				clear_bit(epidx, &hw->txrx_stop_req_bit);
				clear_bit(epidx, &unshare_watch_biपंचांगask);
				clear_bit(epidx, &hw->hw_info.buffer_unshare_reserve_bit);
			पूर्ण

			अगर (test_bit(epidx, &unshare_watch_biपंचांगask)) अणु
				spin_lock_irqsave(&hw->rx_status_lock, flags);
				hw->ep_shm_info[epidx].tx.info->v1i.rx_status &=
						~FJES_RX_STOP_REQ_DONE;
				spin_unlock_irqrestore(&hw->rx_status_lock,
						       flags);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल acpi_status
acpi_find_extended_socket_device(acpi_handle obj_handle, u32 level,
				 व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_device *device;
	bool *found = context;
	पूर्णांक result;

	result = acpi_bus_get_device(obj_handle, &device);
	अगर (result)
		वापस AE_OK;

	अगर (म_भेद(acpi_device_hid(device), ACPI_MOTHERBOARD_RESOURCE_HID))
		वापस AE_OK;

	अगर (!is_extended_socket_device(device))
		वापस AE_OK;

	अगर (acpi_check_extended_socket_status(device))
		वापस AE_OK;

	*found = true;
	वापस AE_CTRL_TERMINATE;
पूर्ण

/* fjes_init_module - Driver Registration Routine */
अटल पूर्णांक __init fjes_init_module(व्योम)
अणु
	bool found = false;
	पूर्णांक result;

	acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT, ACPI_UINT32_MAX,
			    acpi_find_extended_socket_device, शून्य, &found,
			    शून्य);

	अगर (!found)
		वापस -ENODEV;

	pr_info("%s - version %s - %s\n",
		fjes_driver_string, fjes_driver_version, fjes_copyright);

	fjes_dbg_init();

	result = platक्रमm_driver_रेजिस्टर(&fjes_driver);
	अगर (result < 0) अणु
		fjes_dbg_निकास();
		वापस result;
	पूर्ण

	result = acpi_bus_रेजिस्टर_driver(&fjes_acpi_driver);
	अगर (result < 0)
		जाओ fail_acpi_driver;

	वापस 0;

fail_acpi_driver:
	platक्रमm_driver_unरेजिस्टर(&fjes_driver);
	fjes_dbg_निकास();
	वापस result;
पूर्ण

module_init(fjes_init_module);

/* fjes_निकास_module - Driver Exit Cleanup Routine */
अटल व्योम __निकास fjes_निकास_module(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&fjes_acpi_driver);
	platक्रमm_driver_unरेजिस्टर(&fjes_driver);
	fjes_dbg_निकास();
पूर्ण

module_निकास(fjes_निकास_module);
