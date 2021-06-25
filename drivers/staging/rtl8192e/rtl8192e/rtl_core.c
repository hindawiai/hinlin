<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Based on the r8180 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश <linux/uaccess.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ieee80211.h>
#समावेश "rtl_core.h"
#समावेश "r8192E_phy.h"
#समावेश "r8192E_phyreg.h"
#समावेश "r8190P_rtl8256.h"
#समावेश "r8192E_cmdpkt.h"

#समावेश "rtl_wx.h"
#समावेश "rtl_dm.h"

#समावेश "rtl_pm.h"

पूर्णांक hwwep = 1;
अटल पूर्णांक channels = 0x3fff;
अटल अक्षर *अगरname = "wlan%d";


अटल स्थिर काष्ठा rtl819x_ops rtl819xp_ops = अणु
	.nic_type			= NIC_8192E,
	.get_eeprom_size		= rtl92e_get_eeprom_size,
	.init_adapter_variable		= rtl92e_init_variables,
	.initialize_adapter		= rtl92e_start_adapter,
	.link_change			= rtl92e_link_change,
	.tx_fill_descriptor		= rtl92e_fill_tx_desc,
	.tx_fill_cmd_descriptor		= rtl92e_fill_tx_cmd_desc,
	.rx_query_status_descriptor	= rtl92e_get_rx_stats,
	.rx_command_packet_handler = शून्य,
	.stop_adapter			= rtl92e_stop_adapter,
	.update_ratr_table		= rtl92e_update_ratr_table,
	.irq_enable			= rtl92e_enable_irq,
	.irq_disable			= rtl92e_disable_irq,
	.irq_clear			= rtl92e_clear_irq,
	.rx_enable			= rtl92e_enable_rx,
	.tx_enable			= rtl92e_enable_tx,
	.पूर्णांकerrupt_recognized		= rtl92e_ack_irq,
	.TxCheckStuckHandler		= rtl92e_is_tx_stuck,
	.RxCheckStuckHandler		= rtl92e_is_rx_stuck,
पूर्ण;

अटल काष्ठा pci_device_id rtl8192_pci_id_tbl[] = अणु
	अणुRTL_PCI_DEVICE(0x10ec, 0x8192, rtl819xp_ops)पूर्ण,
	अणुRTL_PCI_DEVICE(0x07aa, 0x0044, rtl819xp_ops)पूर्ण,
	अणुRTL_PCI_DEVICE(0x07aa, 0x0047, rtl819xp_ops)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, rtl8192_pci_id_tbl);

अटल पूर्णांक _rtl92e_pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id);
अटल व्योम _rtl92e_pci_disconnect(काष्ठा pci_dev *pdev);
अटल irqवापस_t _rtl92e_irq(पूर्णांक irq, व्योम *netdev);

अटल SIMPLE_DEV_PM_OPS(rtl92e_pm_ops, rtl92e_suspend, rtl92e_resume);

अटल काष्ठा pci_driver rtl8192_pci_driver = अणु
	.name = DRV_NAME,	/* Driver name   */
	.id_table = rtl8192_pci_id_tbl,	/* PCI_ID table  */
	.probe	= _rtl92e_pci_probe,	/* probe fn      */
	.हटाओ	 = _rtl92e_pci_disconnect,	/* हटाओ fn */
	.driver.pm = &rtl92e_pm_ops,
पूर्ण;

अटल लघु _rtl92e_is_tx_queue_empty(काष्ठा net_device *dev);
अटल व्योम _rtl92e_watchकरोg_wq_cb(व्योम *data);
अटल व्योम _rtl92e_watchकरोg_समयr_cb(काष्ठा समयr_list *t);
अटल व्योम _rtl92e_hard_data_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   पूर्णांक rate);
अटल पूर्णांक _rtl92e_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल व्योम _rtl92e_tx_cmd(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
अटल लघु _rtl92e_tx(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
अटल लघु _rtl92e_pci_initdescring(काष्ठा net_device *dev);
अटल व्योम _rtl92e_irq_tx_tasklet(काष्ठा tasklet_काष्ठा *t);
अटल व्योम _rtl92e_irq_rx_tasklet(काष्ठा tasklet_काष्ठा *t);
अटल व्योम _rtl92e_cancel_deferred_work(काष्ठा r8192_priv *priv);
अटल पूर्णांक _rtl92e_up(काष्ठा net_device *dev, bool is_silent_reset);
अटल पूर्णांक _rtl92e_try_up(काष्ठा net_device *dev);
अटल पूर्णांक _rtl92e_करोwn(काष्ठा net_device *dev, bool shutकरोwnrf);
अटल व्योम _rtl92e_restart(व्योम *data);

/****************************************************************************
 *  -----------------------------IO STUFF-------------------------
 ****************************************************************************/

u8 rtl92e_पढ़ोb(काष्ठा net_device *dev, पूर्णांक x)
अणु
	वापस 0xff & पढ़ोb((u8 __iomem *)dev->mem_start + x);
पूर्ण

u32 rtl92e_पढ़ोl(काष्ठा net_device *dev, पूर्णांक x)
अणु
	वापस पढ़ोl((u8 __iomem *)dev->mem_start + x);
पूर्ण

u16 rtl92e_पढ़ोw(काष्ठा net_device *dev, पूर्णांक x)
अणु
	वापस पढ़ोw((u8 __iomem *)dev->mem_start + x);
पूर्ण

व्योम rtl92e_ग_लिखोb(काष्ठा net_device *dev, पूर्णांक x, u8 y)
अणु
	ग_लिखोb(y, (u8 __iomem *)dev->mem_start + x);

	udelay(20);
पूर्ण

व्योम rtl92e_ग_लिखोl(काष्ठा net_device *dev, पूर्णांक x, u32 y)
अणु
	ग_लिखोl(y, (u8 __iomem *)dev->mem_start + x);

	udelay(20);
पूर्ण

व्योम rtl92e_ग_लिखोw(काष्ठा net_device *dev, पूर्णांक x, u16 y)
अणु
	ग_लिखोw(y, (u8 __iomem *)dev->mem_start + x);

	udelay(20);
पूर्ण

/****************************************************************************
 *  -----------------------------GENERAL FUNCTION-------------------------
 ****************************************************************************/
bool rtl92e_set_rf_state(काष्ठा net_device *dev,
			 क्रमागत rt_rf_घातer_state StateToSet,
			 RT_RF_CHANGE_SOURCE ChangeSource)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;
	bool			bActionAllowed = false;
	bool			bConnectBySSID = false;
	क्रमागत rt_rf_घातer_state rtState;
	u16			RFWaitCounter = 0;
	अचिन्हित दीर्घ flag;

	RT_TRACE((COMP_PS | COMP_RF),
		 "===>%s: StateToSet(%d)\n", __func__, StateToSet);

	जबतक (true) अणु
		spin_lock_irqsave(&priv->rf_ps_lock, flag);
		अगर (priv->RFChangeInProgress) अणु
			spin_unlock_irqrestore(&priv->rf_ps_lock, flag);
			RT_TRACE((COMP_PS | COMP_RF),
				 "%s: RF Change in progress! Wait to set..StateToSet(%d).\n",
				 __func__, StateToSet);

			जबतक (priv->RFChangeInProgress) अणु
				RFWaitCounter++;
				RT_TRACE((COMP_PS | COMP_RF),
					 "%s: Wait 1 ms (%d times)...\n",
					 __func__, RFWaitCounter);
				mdelay(1);

				अगर (RFWaitCounter > 100) अणु
					netdev_warn(dev,
						    "%s(): Timeout waiting for RF change.\n",
						    __func__);
					वापस false;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			priv->RFChangeInProgress = true;
			spin_unlock_irqrestore(&priv->rf_ps_lock, flag);
			अवरोध;
		पूर्ण
	पूर्ण

	rtState = priv->rtllib->eRFPowerState;

	चयन (StateToSet) अणु
	हाल eRfOn:
		priv->rtllib->RfOffReason &= (~ChangeSource);

		अगर ((ChangeSource == RF_CHANGE_BY_HW) && priv->bHwRadioOff)
			priv->bHwRadioOff = false;

		अगर (!priv->rtllib->RfOffReason) अणु
			priv->rtllib->RfOffReason = 0;
			bActionAllowed = true;


			अगर (rtState == eRfOff &&
			    ChangeSource >= RF_CHANGE_BY_HW)
				bConnectBySSID = true;
		पूर्ण अन्यथा अणु
			RT_TRACE((COMP_PS | COMP_RF),
				 "%s - eRfon reject pMgntInfo->RfOffReason= 0x%x, ChangeSource=0x%X\n",
				 __func__, priv->rtllib->RfOffReason, ChangeSource);
	पूर्ण

		अवरोध;

	हाल eRfOff:

		अगर ((priv->rtllib->iw_mode == IW_MODE_INFRA) ||
		    (priv->rtllib->iw_mode == IW_MODE_ADHOC)) अणु
			अगर ((priv->rtllib->RfOffReason > RF_CHANGE_BY_IPS) ||
			    (ChangeSource > RF_CHANGE_BY_IPS)) अणु
				अगर (ieee->state == RTLLIB_LINKED)
					priv->blinked_ingpio = true;
				अन्यथा
					priv->blinked_ingpio = false;
				rtllib_MgntDisconnect(priv->rtllib,
						      WLAN_REASON_DISASSOC_STA_HAS_LEFT);
			पूर्ण
		पूर्ण
		अगर ((ChangeSource == RF_CHANGE_BY_HW) && !priv->bHwRadioOff)
			priv->bHwRadioOff = true;
		priv->rtllib->RfOffReason |= ChangeSource;
		bActionAllowed = true;
		अवरोध;

	हाल eRfSleep:
		priv->rtllib->RfOffReason |= ChangeSource;
		bActionAllowed = true;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (bActionAllowed) अणु
		RT_TRACE((COMP_PS | COMP_RF),
			 "%s: Action is allowed.... StateToSet(%d), RfOffReason(%#X)\n",
			 __func__, StateToSet, priv->rtllib->RfOffReason);
		PHY_SetRFPowerState(dev, StateToSet);
		अगर (StateToSet == eRfOn) अणु

			अगर (bConnectBySSID && priv->blinked_ingpio) अणु
				schedule_delayed_work(
					 &ieee->associate_procedure_wq, 0);
				priv->blinked_ingpio = false;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		RT_TRACE((COMP_PS | COMP_RF),
			 "%s: Action is rejected.... StateToSet(%d), ChangeSource(%#X), RfOffReason(%#X)\n",
			 __func__, StateToSet, ChangeSource, priv->rtllib->RfOffReason);
	पूर्ण

	spin_lock_irqsave(&priv->rf_ps_lock, flag);
	priv->RFChangeInProgress = false;
	spin_unlock_irqrestore(&priv->rf_ps_lock, flag);

	RT_TRACE((COMP_PS | COMP_RF), "<===%s\n", __func__);
	वापस bActionAllowed;
पूर्ण

अटल लघु _rtl92e_check_nic_enough_desc(काष्ठा net_device *dev, पूर्णांक prio)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtl8192_tx_ring *ring = &priv->tx_ring[prio];

	अगर (ring->entries - skb_queue_len(&ring->queue) >= 2)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम _rtl92e_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	schedule_work(&priv->reset_wq);
	netdev_info(dev, "TXTIMEOUT");
पूर्ण

व्योम rtl92e_irq_enable(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->irq_enabled = 1;

	priv->ops->irq_enable(dev);
पूर्ण

व्योम rtl92e_irq_disable(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->ops->irq_disable(dev);

	priv->irq_enabled = 0;
पूर्ण

अटल व्योम _rtl92e_set_chan(काष्ठा net_device *dev, लघु ch)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	RT_TRACE(COMP_CH, "=====>%s()====ch:%d\n", __func__, ch);
	अगर (priv->chan_क्रमced)
		वापस;

	priv->chan = ch;

	अगर (priv->rf_set_chan)
		priv->rf_set_chan(dev, priv->chan);
पूर्ण

अटल व्योम _rtl92e_update_cap(काष्ठा net_device *dev, u16 cap)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_network *net = &priv->rtllib->current_network;
	bool		ShortPreamble;

	अगर (cap & WLAN_CAPABILITY_SHORT_PREAMBLE) अणु
		अगर (priv->करोt11CurrentPreambleMode != PREAMBLE_SHORT) अणु
			ShortPreamble = true;
			priv->करोt11CurrentPreambleMode = PREAMBLE_SHORT;
			RT_TRACE(COMP_DBG,
				 "%s(): WLAN_CAPABILITY_SHORT_PREAMBLE\n",
				 __func__);
			priv->rtllib->SetHwRegHandler(dev, HW_VAR_ACK_PREAMBLE,
					(अचिन्हित अक्षर *)&ShortPreamble);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->करोt11CurrentPreambleMode != PREAMBLE_LONG) अणु
			ShortPreamble = false;
			priv->करोt11CurrentPreambleMode = PREAMBLE_LONG;
			RT_TRACE(COMP_DBG,
				 "%s(): WLAN_CAPABILITY_LONG_PREAMBLE\n",
				 __func__);
			priv->rtllib->SetHwRegHandler(dev, HW_VAR_ACK_PREAMBLE,
					      (अचिन्हित अक्षर *)&ShortPreamble);
		पूर्ण
	पूर्ण

	अगर (net->mode & (IEEE_G | IEEE_N_24G)) अणु
		u8	slot_समय_val;
		u8	CurSlotTime = priv->slot_समय;

		अगर ((cap & WLAN_CAPABILITY_SHORT_SLOT_TIME) &&
		   (!priv->rtllib->pHTInfo->bCurrentRT2RTLongSlotTime)) अणु
			अगर (CurSlotTime != SHORT_SLOT_TIME) अणु
				slot_समय_val = SHORT_SLOT_TIME;
				priv->rtllib->SetHwRegHandler(dev,
					 HW_VAR_SLOT_TIME, &slot_समय_val);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (CurSlotTime != NON_SHORT_SLOT_TIME) अणु
				slot_समय_val = NON_SHORT_SLOT_TIME;
				priv->rtllib->SetHwRegHandler(dev,
					 HW_VAR_SLOT_TIME, &slot_समय_val);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rtllib_qos_parameters def_qos_parameters = अणु
	अणुcpu_to_le16(3), cpu_to_le16(3), cpu_to_le16(3), cpu_to_le16(3)पूर्ण,
	अणुcpu_to_le16(7), cpu_to_le16(7), cpu_to_le16(7), cpu_to_le16(7)पूर्ण,
	अणु2, 2, 2, 2पूर्ण,
	अणु0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0पूर्ण
पूर्ण;

अटल व्योम _rtl92e_update_beacon(व्योम *data)
अणु
	काष्ठा r8192_priv *priv = container_of_work_rsl(data, काष्ठा r8192_priv,
				  update_beacon_wq.work);
	काष्ठा net_device *dev = priv->rtllib->dev;
	काष्ठा rtllib_device *ieee = priv->rtllib;
	काष्ठा rtllib_network *net = &ieee->current_network;

	अगर (ieee->pHTInfo->bCurrentHTSupport)
		HT_update_self_and_peer_setting(ieee, net);
	ieee->pHTInfo->bCurrentRT2RTLongSlotTime = net->bssht.bd_rt2rt_दीर्घ_slot_समय;
	ieee->pHTInfo->RT2RT_HT_Mode = net->bssht.rt2rt_ht_mode;
	_rtl92e_update_cap(dev, net->capability);
पूर्ण

अटल व्योम _rtl92e_qos_activate(व्योम *data)
अणु
	काष्ठा r8192_priv *priv = container_of_work_rsl(data, काष्ठा r8192_priv,
				  qos_activate);
	काष्ठा net_device *dev = priv->rtllib->dev;
	पूर्णांक i;

	mutex_lock(&priv->mutex);
	अगर (priv->rtllib->state != RTLLIB_LINKED)
		जाओ success;
	RT_TRACE(COMP_QOS,
		 "qos active process with associate response received\n");

	क्रम (i = 0; i <  QOS_QUEUE_NUM; i++)
		priv->rtllib->SetHwRegHandler(dev, HW_VAR_AC_PARAM, (u8 *)(&i));


success:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक _rtl92e_qos_handle_probe_response(काष्ठा r8192_priv *priv,
					     पूर्णांक active_network,
					     काष्ठा rtllib_network *network)
अणु
	पूर्णांक ret = 0;
	u32 size = माप(काष्ठा rtllib_qos_parameters);

	अगर (priv->rtllib->state != RTLLIB_LINKED)
		वापस ret;

	अगर (priv->rtllib->iw_mode != IW_MODE_INFRA)
		वापस ret;

	अगर (network->flags & NETWORK_HAS_QOS_MASK) अणु
		अगर (active_network &&
				(network->flags & NETWORK_HAS_QOS_PARAMETERS))
			network->qos_data.active = network->qos_data.supported;

		अगर ((network->qos_data.active == 1) && (active_network == 1) &&
				(network->flags & NETWORK_HAS_QOS_PARAMETERS) &&
				(network->qos_data.old_param_count !=
				network->qos_data.param_count)) अणु
			network->qos_data.old_param_count =
				network->qos_data.param_count;
			priv->rtllib->wmm_acm = network->qos_data.wmm_acm;
			schedule_work(&priv->qos_activate);
			RT_TRACE(COMP_QOS,
				 "QoS parameters change call qos_activate\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(&priv->rtllib->current_network.qos_data.parameters,
		       &def_qos_parameters, size);

		अगर ((network->qos_data.active == 1) && (active_network == 1)) अणु
			schedule_work(&priv->qos_activate);
			RT_TRACE(COMP_QOS,
				 "QoS was disabled call qos_activate\n");
		पूर्ण
		network->qos_data.active = 0;
		network->qos_data.supported = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_handle_beacon(काष्ठा net_device *dev,
				 काष्ठा rtllib_beacon *beacon,
				 काष्ठा rtllib_network *network)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	_rtl92e_qos_handle_probe_response(priv, 1, network);

	schedule_delayed_work(&priv->update_beacon_wq, 0);
	वापस 0;

पूर्ण

अटल पूर्णांक _rtl92e_qos_assoc_resp(काष्ठा r8192_priv *priv,
				  काष्ठा rtllib_network *network)
अणु
	अचिन्हित दीर्घ flags;
	u32 size = माप(काष्ठा rtllib_qos_parameters);
	पूर्णांक set_qos_param = 0;

	अगर (!priv || !network)
		वापस 0;

	अगर (priv->rtllib->state != RTLLIB_LINKED)
		वापस 0;

	अगर (priv->rtllib->iw_mode != IW_MODE_INFRA)
		वापस 0;

	spin_lock_irqsave(&priv->rtllib->lock, flags);
	अगर (network->flags & NETWORK_HAS_QOS_PARAMETERS) अणु
		स_नकल(&priv->rtllib->current_network.qos_data.parameters,
		       &network->qos_data.parameters,
		       माप(काष्ठा rtllib_qos_parameters));
		priv->rtllib->current_network.qos_data.active = 1;
		priv->rtllib->wmm_acm = network->qos_data.wmm_acm;
		set_qos_param = 1;
		priv->rtllib->current_network.qos_data.old_param_count =
			priv->rtllib->current_network.qos_data.param_count;
		priv->rtllib->current_network.qos_data.param_count =
			network->qos_data.param_count;
	पूर्ण अन्यथा अणु
		स_नकल(&priv->rtllib->current_network.qos_data.parameters,
		&def_qos_parameters, size);
		priv->rtllib->current_network.qos_data.active = 0;
		priv->rtllib->current_network.qos_data.supported = 0;
		set_qos_param = 1;
	पूर्ण

	spin_unlock_irqrestore(&priv->rtllib->lock, flags);

	RT_TRACE(COMP_QOS, "%s: network->flags = %d,%d\n", __func__,
		 network->flags, priv->rtllib->current_network.qos_data.active);
	अगर (set_qos_param == 1) अणु
		rtl92e_dm_init_edca_turbo(priv->rtllib->dev);
		schedule_work(&priv->qos_activate);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_handle_assoc_response(काष्ठा net_device *dev,
				 काष्ठा rtllib_assoc_response_frame *resp,
				 काष्ठा rtllib_network *network)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	_rtl92e_qos_assoc_resp(priv, network);
	वापस 0;
पूर्ण

अटल व्योम _rtl92e_prepare_beacon(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा r8192_priv *priv = from_tasklet(priv, t,
					       irq_prepare_beacon_tasklet);
	काष्ठा net_device *dev = priv->rtllib->dev;
	काष्ठा sk_buff *pskb = शून्य, *pnewskb = शून्य;
	काष्ठा cb_desc *tcb_desc = शून्य;
	काष्ठा rtl8192_tx_ring *ring = शून्य;
	काष्ठा tx_desc *pdesc = शून्य;

	ring = &priv->tx_ring[BEACON_QUEUE];
	pskb = __skb_dequeue(&ring->queue);
	kमुक्त_skb(pskb);

	pnewskb = rtllib_get_beacon(priv->rtllib);
	अगर (!pnewskb)
		वापस;

	tcb_desc = (काष्ठा cb_desc *)(pnewskb->cb + 8);
	tcb_desc->queue_index = BEACON_QUEUE;
	tcb_desc->data_rate = 2;
	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;
	skb_push(pnewskb, priv->rtllib->tx_headroom);

	pdesc = &ring->desc[0];
	priv->ops->tx_fill_descriptor(dev, pdesc, tcb_desc, pnewskb);
	__skb_queue_tail(&ring->queue, pnewskb);
	pdesc->OWN = 1;
पूर्ण

अटल व्योम _rtl92e_stop_beacon(काष्ठा net_device *dev)
अणु
पूर्ण

व्योम rtl92e_config_rate(काष्ठा net_device *dev, u16 *rate_config)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_network *net;
	u8 i = 0, basic_rate = 0;

	net = &priv->rtllib->current_network;

	क्रम (i = 0; i < net->rates_len; i++) अणु
		basic_rate = net->rates[i] & 0x7f;
		चयन (basic_rate) अणु
		हाल MGN_1M:
			*rate_config |= RRSR_1M;
			अवरोध;
		हाल MGN_2M:
			*rate_config |= RRSR_2M;
			अवरोध;
		हाल MGN_5_5M:
			*rate_config |= RRSR_5_5M;
			अवरोध;
		हाल MGN_11M:
			*rate_config |= RRSR_11M;
			अवरोध;
		हाल MGN_6M:
			*rate_config |= RRSR_6M;
			अवरोध;
		हाल MGN_9M:
			*rate_config |= RRSR_9M;
			अवरोध;
		हाल MGN_12M:
			*rate_config |= RRSR_12M;
			अवरोध;
		हाल MGN_18M:
			*rate_config |= RRSR_18M;
			अवरोध;
		हाल MGN_24M:
			*rate_config |= RRSR_24M;
			अवरोध;
		हाल MGN_36M:
			*rate_config |= RRSR_36M;
			अवरोध;
		हाल MGN_48M:
			*rate_config |= RRSR_48M;
			अवरोध;
		हाल MGN_54M:
			*rate_config |= RRSR_54M;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < net->rates_ex_len; i++) अणु
		basic_rate = net->rates_ex[i] & 0x7f;
		चयन (basic_rate) अणु
		हाल MGN_1M:
			*rate_config |= RRSR_1M;
			अवरोध;
		हाल MGN_2M:
			*rate_config |= RRSR_2M;
			अवरोध;
		हाल MGN_5_5M:
			*rate_config |= RRSR_5_5M;
			अवरोध;
		हाल MGN_11M:
			*rate_config |= RRSR_11M;
			अवरोध;
		हाल MGN_6M:
			*rate_config |= RRSR_6M;
			अवरोध;
		हाल MGN_9M:
			*rate_config |= RRSR_9M;
			अवरोध;
		हाल MGN_12M:
			*rate_config |= RRSR_12M;
			अवरोध;
		हाल MGN_18M:
			*rate_config |= RRSR_18M;
			अवरोध;
		हाल MGN_24M:
			*rate_config |= RRSR_24M;
			अवरोध;
		हाल MGN_36M:
			*rate_config |= RRSR_36M;
			अवरोध;
		हाल MGN_48M:
			*rate_config |= RRSR_48M;
			अवरोध;
		हाल MGN_54M:
			*rate_config |= RRSR_54M;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_refresh_support_rate(काष्ठा r8192_priv *priv)
अणु
	काष्ठा rtllib_device *ieee = priv->rtllib;

	अगर (ieee->mode == WIRELESS_MODE_N_24G ||
	    ieee->mode == WIRELESS_MODE_N_5G) अणु
		स_नकल(ieee->Regकरोt11HTOperationalRateSet,
		       ieee->RegHTSuppRateSet, 16);
		स_नकल(ieee->Regकरोt11TxHTOperationalRateSet,
		       ieee->RegHTSuppRateSet, 16);

	पूर्ण अन्यथा अणु
		स_रखो(ieee->Regकरोt11HTOperationalRateSet, 0, 16);
	पूर्ण
पूर्ण

अटल u8 _rtl92e_get_supported_wireless_mode(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 ret = 0;

	चयन (priv->rf_chip) अणु
	हाल RF_8225:
	हाल RF_8256:
	हाल RF_6052:
	हाल RF_PSEUDO_11N:
		ret = (WIRELESS_MODE_N_24G | WIRELESS_MODE_G | WIRELESS_MODE_B);
		अवरोध;
	हाल RF_8258:
		ret = (WIRELESS_MODE_A | WIRELESS_MODE_N_5G);
		अवरोध;
	शेष:
		ret = WIRELESS_MODE_B;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

व्योम rtl92e_set_wireless_mode(काष्ठा net_device *dev, u8 wireless_mode)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 bSupportMode = _rtl92e_get_supported_wireless_mode(dev);

	अगर ((wireless_mode == WIRELESS_MODE_AUTO) ||
	    ((wireless_mode & bSupportMode) == 0)) अणु
		अगर (bSupportMode & WIRELESS_MODE_N_24G) अणु
			wireless_mode = WIRELESS_MODE_N_24G;
		पूर्ण अन्यथा अगर (bSupportMode & WIRELESS_MODE_N_5G) अणु
			wireless_mode = WIRELESS_MODE_N_5G;
		पूर्ण अन्यथा अगर ((bSupportMode & WIRELESS_MODE_A)) अणु
			wireless_mode = WIRELESS_MODE_A;
		पूर्ण अन्यथा अगर ((bSupportMode & WIRELESS_MODE_G)) अणु
			wireless_mode = WIRELESS_MODE_G;
		पूर्ण अन्यथा अगर ((bSupportMode & WIRELESS_MODE_B)) अणु
			wireless_mode = WIRELESS_MODE_B;
		पूर्ण अन्यथा अणु
			netdev_info(dev,
				    "%s(): Unsupported mode requested. Fallback to 802.11b\n",
				    __func__);
			wireless_mode = WIRELESS_MODE_B;
		पूर्ण
	पूर्ण

	अगर ((wireless_mode & (WIRELESS_MODE_B | WIRELESS_MODE_G)) ==
	    (WIRELESS_MODE_G | WIRELESS_MODE_B))
		wireless_mode = WIRELESS_MODE_G;

	priv->rtllib->mode = wireless_mode;

	अगर ((wireless_mode == WIRELESS_MODE_N_24G) ||
	    (wireless_mode == WIRELESS_MODE_N_5G)) अणु
		priv->rtllib->pHTInfo->bEnableHT = 1;
		RT_TRACE(COMP_DBG, "%s(), wireless_mode:%x, bEnableHT = 1\n",
			 __func__, wireless_mode);
	पूर्ण अन्यथा अणु
		priv->rtllib->pHTInfo->bEnableHT = 0;
		RT_TRACE(COMP_DBG, "%s(), wireless_mode:%x, bEnableHT = 0\n",
			 __func__, wireless_mode);
	पूर्ण

	RT_TRACE(COMP_INIT, "Current Wireless Mode is %x\n", wireless_mode);
	_rtl92e_refresh_support_rate(priv);
पूर्ण

अटल पूर्णांक _rtl92e_sta_up(काष्ठा net_device *dev, bool is_silent_reset)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					(&priv->rtllib->PowerSaveControl);
	bool init_status;

	priv->bDriverIsGoingToUnload = false;
	priv->bdisable_nic = false;

	priv->up = 1;
	priv->rtllib->ieee_up = 1;

	priv->up_first_समय = 0;
	RT_TRACE(COMP_INIT, "Bringing up iface");
	priv->bfirst_init = true;
	init_status = priv->ops->initialize_adapter(dev);
	अगर (!init_status) अणु
		netdev_err(dev, "%s(): Initialization failed!\n", __func__);
		priv->bfirst_init = false;
		वापस -1;
	पूर्ण

	RT_TRACE(COMP_INIT, "start adapter finished\n");
	RT_CLEAR_PS_LEVEL(pPSC, RT_RF_OFF_LEVL_HALT_NIC);
	priv->bfirst_init = false;

	अगर (priv->polling_समयr_on == 0)
		rtl92e_check_rfctrl_gpio_समयr(&priv->gpio_polling_समयr);

	अगर (priv->rtllib->state != RTLLIB_LINKED)
		rtllib_sofपंचांगac_start_protocol(priv->rtllib, 0);
	rtllib_reset_queue(priv->rtllib);
	_rtl92e_watchकरोg_समयr_cb(&priv->watch_करोg_समयr);

	अगर (!netअगर_queue_stopped(dev))
		netअगर_start_queue(dev);
	अन्यथा
		netअगर_wake_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_sta_करोwn(काष्ठा net_device *dev, bool shutकरोwnrf)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अचिन्हित दीर्घ flags = 0;
	u8 RFInProgressTimeOut = 0;

	अगर (priv->up == 0)
		वापस -1;

	अगर (priv->rtllib->rtllib_ips_leave)
		priv->rtllib->rtllib_ips_leave(dev);

	अगर (priv->rtllib->state == RTLLIB_LINKED)
		rtl92e_leisure_ps_leave(dev);

	priv->bDriverIsGoingToUnload = true;
	priv->up = 0;
	priv->rtllib->ieee_up = 0;
	priv->bfirst_after_करोwn = true;
	RT_TRACE(COMP_DOWN, "==========>%s()\n", __func__);
	अगर (!netअगर_queue_stopped(dev))
		netअगर_stop_queue(dev);

	priv->rtllib->wpa_ie_len = 0;
	kमुक्त(priv->rtllib->wpa_ie);
	priv->rtllib->wpa_ie = शून्य;
	rtl92e_cam_reset(dev);
	स_रखो(priv->rtllib->swcamtable, 0, माप(काष्ठा sw_cam_table) * 32);
	rtl92e_irq_disable(dev);

	del_समयr_sync(&priv->watch_करोg_समयr);
	_rtl92e_cancel_deferred_work(priv);
	cancel_delayed_work(&priv->rtllib->hw_wakeup_wq);

	rtllib_sofपंचांगac_stop_protocol(priv->rtllib, 0, true);
	spin_lock_irqsave(&priv->rf_ps_lock, flags);
	जबतक (priv->RFChangeInProgress) अणु
		spin_unlock_irqrestore(&priv->rf_ps_lock, flags);
		अगर (RFInProgressTimeOut > 100) अणु
			spin_lock_irqsave(&priv->rf_ps_lock, flags);
			अवरोध;
		पूर्ण
		RT_TRACE(COMP_DBG,
			 "===>%s():RF is in progress, need to wait until rf change is done.\n",
			 __func__);
		mdelay(1);
		RFInProgressTimeOut++;
		spin_lock_irqsave(&priv->rf_ps_lock, flags);
	पूर्ण
	priv->RFChangeInProgress = true;
	spin_unlock_irqrestore(&priv->rf_ps_lock, flags);
	priv->ops->stop_adapter(dev, false);
	spin_lock_irqsave(&priv->rf_ps_lock, flags);
	priv->RFChangeInProgress = false;
	spin_unlock_irqrestore(&priv->rf_ps_lock, flags);
	udelay(100);
	स_रखो(&priv->rtllib->current_network, 0,
	       दुरत्व(काष्ठा rtllib_network, list));
	RT_TRACE(COMP_DOWN, "<==========%s()\n", __func__);

	वापस 0;
पूर्ण

अटल व्योम _rtl92e_init_priv_handler(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->rtllib->sofपंचांगac_hard_start_xmit	= _rtl92e_hard_start_xmit;
	priv->rtllib->set_chan			= _rtl92e_set_chan;
	priv->rtllib->link_change		= priv->ops->link_change;
	priv->rtllib->sofपंचांगac_data_hard_start_xmit = _rtl92e_hard_data_xmit;
	priv->rtllib->check_nic_enough_desc	= _rtl92e_check_nic_enough_desc;
	priv->rtllib->handle_assoc_response	= _rtl92e_handle_assoc_response;
	priv->rtllib->handle_beacon		= _rtl92e_handle_beacon;
	priv->rtllib->SetWirelessMode		= rtl92e_set_wireless_mode;
	priv->rtllib->LeisurePSLeave		= rtl92e_leisure_ps_leave;
	priv->rtllib->SetBWModeHandler		= rtl92e_set_bw_mode;
	priv->rf_set_chan			= rtl92e_set_channel;

	priv->rtllib->start_send_beacons = rtl92e_start_beacon;
	priv->rtllib->stop_send_beacons = _rtl92e_stop_beacon;

	priv->rtllib->sta_wake_up = rtl92e_hw_wakeup;
	priv->rtllib->enter_sleep_state = rtl92e_enter_sleep;
	priv->rtllib->ps_is_queue_empty = _rtl92e_is_tx_queue_empty;

	priv->rtllib->GetNmodeSupportBySecCfg = rtl92e_get_nmode_support_by_sec;
	priv->rtllib->GetHalfNmodeSupportByAPsHandler =
						rtl92e_is_halfn_supported_by_ap;

	priv->rtllib->SetHwRegHandler = rtl92e_set_reg;
	priv->rtllib->AllowAllDestAddrHandler = rtl92e_set_monitor_mode;
	priv->rtllib->SetFwCmdHandler = शून्य;
	priv->rtllib->InitialGainHandler = rtl92e_init_gain;
	priv->rtllib->rtllib_ips_leave_wq = rtl92e_rtllib_ips_leave_wq;
	priv->rtllib->rtllib_ips_leave = rtl92e_rtllib_ips_leave;

	priv->rtllib->LedControlHandler = शून्य;
	priv->rtllib->UpdateBeaconInterruptHandler = शून्य;

	priv->rtllib->ScanOperationBackupHandler = rtl92e_scan_op_backup;
पूर्ण

अटल व्योम _rtl92e_init_priv_स्थिरant(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					&priv->rtllib->PowerSaveControl;

	pPSC->RegMaxLPSAwakeIntvl = 5;
पूर्ण


अटल व्योम _rtl92e_init_priv_variable(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 i;

	priv->AcmMethod = eAcmWay2_SW;
	priv->करोt11CurrentPreambleMode = PREAMBLE_AUTO;
	priv->rtllib->status = 0;
	priv->polling_समयr_on = 0;
	priv->up_first_समय = 1;
	priv->blinked_ingpio = false;
	priv->bDriverIsGoingToUnload = false;
	priv->being_init_adapter = false;
	priv->initialized_at_probe = false;
	priv->bdisable_nic = false;
	priv->bfirst_init = false;
	priv->txringcount = 64;
	priv->rxbuffersize = 9100;
	priv->rxringcount = MAX_RX_COUNT;
	priv->irq_enabled = 0;
	priv->chan = 1;
	priv->RegChannelPlan = 0xf;
	priv->rtllib->mode = WIRELESS_MODE_AUTO;
	priv->rtllib->iw_mode = IW_MODE_INFRA;
	priv->rtllib->bNetPromiscuousMode = false;
	priv->rtllib->IntelPromiscuousModeInfo.bPromiscuousOn = false;
	priv->rtllib->IntelPromiscuousModeInfo.bFilterSourceStationFrame =
								 false;
	priv->rtllib->ieee_up = 0;
	priv->retry_rts = DEFAULT_RETRY_RTS;
	priv->retry_data = DEFAULT_RETRY_DATA;
	priv->rtllib->rts = DEFAULT_RTS_THRESHOLD;
	priv->rtllib->rate = 110;
	priv->rtllib->लघु_slot = 1;
	priv->promisc = (dev->flags & IFF_PROMISC) ? 1 : 0;
	priv->bcck_in_ch14 = false;
	priv->bfsync_processing  = false;
	priv->CCKPresentAttentuation = 0;
	priv->rfa_txघातertrackingindex = 0;
	priv->rfc_txघातertrackingindex = 0;
	priv->CckPwEnl = 6;
	priv->ScanDelay = 50;
	priv->ResetProgress = RESET_TYPE_NORESET;
	priv->bForcedSilentReset = false;
	priv->bDisableNormalResetCheck = false;
	priv->क्रमce_reset = false;
	स_रखो(priv->rtllib->swcamtable, 0, माप(काष्ठा sw_cam_table) * 32);

	स_रखो(&priv->InterruptLog, 0, माप(काष्ठा log_पूर्णांक_8190));
	priv->RxCounter = 0;
	priv->rtllib->wx_set_enc = 0;
	priv->bHwRadioOff = false;
	priv->RegRfOff = false;
	priv->isRFOff = false;
	priv->bInPowerSaveMode = false;
	priv->rtllib->RfOffReason = 0;
	priv->RFChangeInProgress = false;
	priv->bHwRfOffAction = 0;
	priv->SetRFPowerStateInProgress = false;
	priv->rtllib->PowerSaveControl.bInactivePs = true;
	priv->rtllib->PowerSaveControl.bIPSModeBackup = false;
	priv->rtllib->PowerSaveControl.bLeisurePs = true;
	priv->rtllib->PowerSaveControl.bFwCtrlLPS = false;
	priv->rtllib->LPSDelayCnt = 0;
	priv->rtllib->sta_sleep = LPS_IS_WAKE;
	priv->rtllib->eRFPowerState = eRfOn;

	priv->rtllib->current_network.beacon_पूर्णांकerval = DEFAULT_BEACONINTERVAL;
	priv->rtllib->iw_mode = IW_MODE_INFRA;
	priv->rtllib->active_scan = 1;
	priv->rtllib->be_scan_inprogress = false;
	priv->rtllib->modulation = RTLLIB_CCK_MODULATION |
				   RTLLIB_OFDM_MODULATION;
	priv->rtllib->host_encrypt = 1;
	priv->rtllib->host_decrypt = 1;

	priv->rtllib->fts = DEFAULT_FRAG_THRESHOLD;

	priv->card_type = PCI;

	priv->pFirmware = vzalloc(माप(काष्ठा rt_firmware));
	अगर (!priv->pFirmware)
		netdev_err(dev,
			   "rtl8192e: Unable to allocate space for firmware\n");

	skb_queue_head_init(&priv->skb_queue);

	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->rtllib->skb_रुकोQ[i]);
	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->rtllib->skb_aggQ[i]);
पूर्ण

अटल व्योम _rtl92e_init_priv_lock(काष्ठा r8192_priv *priv)
अणु
	spin_lock_init(&priv->tx_lock);
	spin_lock_init(&priv->irq_th_lock);
	spin_lock_init(&priv->rf_ps_lock);
	spin_lock_init(&priv->ps_lock);
	mutex_init(&priv->wx_mutex);
	mutex_init(&priv->rf_mutex);
	mutex_init(&priv->mutex);
पूर्ण

अटल व्योम _rtl92e_init_priv_task(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	INIT_WORK_RSL(&priv->reset_wq, (व्योम *)_rtl92e_restart, dev);
	INIT_WORK_RSL(&priv->rtllib->ips_leave_wq, (व्योम *)rtl92e_ips_leave_wq,
		      dev);
	INIT_DELAYED_WORK_RSL(&priv->watch_करोg_wq,
			      (व्योम *)_rtl92e_watchकरोg_wq_cb, dev);
	INIT_DELAYED_WORK_RSL(&priv->txघातer_tracking_wq,
			      (व्योम *)rtl92e_dm_txघातer_tracking_wq, dev);
	INIT_DELAYED_WORK_RSL(&priv->rfpath_check_wq,
			      (व्योम *)rtl92e_dm_rf_pathcheck_wq, dev);
	INIT_DELAYED_WORK_RSL(&priv->update_beacon_wq,
			      (व्योम *)_rtl92e_update_beacon, dev);
	INIT_WORK_RSL(&priv->qos_activate, (व्योम *)_rtl92e_qos_activate, dev);
	INIT_DELAYED_WORK_RSL(&priv->rtllib->hw_wakeup_wq,
			      (व्योम *)rtl92e_hw_wakeup_wq, dev);
	INIT_DELAYED_WORK_RSL(&priv->rtllib->hw_sleep_wq,
			      (व्योम *)rtl92e_hw_sleep_wq, dev);
	tasklet_setup(&priv->irq_rx_tasklet, _rtl92e_irq_rx_tasklet);
	tasklet_setup(&priv->irq_tx_tasklet, _rtl92e_irq_tx_tasklet);
	tasklet_setup(&priv->irq_prepare_beacon_tasklet,
		      _rtl92e_prepare_beacon);
पूर्ण

अटल लघु _rtl92e_get_channel_map(काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर ((priv->rf_chip != RF_8225) && (priv->rf_chip != RF_8256) &&
						(priv->rf_chip != RF_6052)) अणु
		netdev_err(dev, "%s: unknown rf chip, can't set channel map\n",
			   __func__);
		वापस -1;
	पूर्ण

	अगर (priv->ChannelPlan >= COUNTRY_CODE_MAX) अणु
		netdev_info(dev,
			    "rtl819x_init:Error channel plan! Set to default.\n");
		priv->ChannelPlan = COUNTRY_CODE_FCC;
	पूर्ण
	RT_TRACE(COMP_INIT, "Channel plan is %d\n", priv->ChannelPlan);
	करोt11d_init(priv->rtllib);
	करोt11d_channel_map(priv->ChannelPlan, priv->rtllib);
	क्रम (i = 1; i <= 11; i++)
		(priv->rtllib->active_channel_map)[i] = 1;
	(priv->rtllib->active_channel_map)[12] = 2;
	(priv->rtllib->active_channel_map)[13] = 2;

	वापस 0;
पूर्ण

अटल लघु _rtl92e_init(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	स_रखो(&priv->stats, 0, माप(काष्ठा rt_stats));

	_rtl92e_init_priv_handler(dev);
	_rtl92e_init_priv_स्थिरant(dev);
	_rtl92e_init_priv_variable(dev);
	_rtl92e_init_priv_lock(priv);
	_rtl92e_init_priv_task(dev);
	priv->ops->get_eeprom_size(dev);
	priv->ops->init_adapter_variable(dev);
	_rtl92e_get_channel_map(dev);

	rtl92e_dm_init(dev);

	समयr_setup(&priv->watch_करोg_समयr, _rtl92e_watchकरोg_समयr_cb, 0);

	समयr_setup(&priv->gpio_polling_समयr, rtl92e_check_rfctrl_gpio_समयr,
		    0);

	rtl92e_irq_disable(dev);
	अगर (request_irq(dev->irq, _rtl92e_irq, IRQF_SHARED, dev->name, dev)) अणु
		netdev_err(dev, "Error allocating IRQ %d", dev->irq);
		वापस -1;
	पूर्ण

	priv->irq = dev->irq;
	RT_TRACE(COMP_INIT, "IRQ %d\n", dev->irq);

	अगर (_rtl92e_pci_initdescring(dev) != 0) अणु
		netdev_err(dev, "Endopoints initialization failed");
		मुक्त_irq(dev->irq, dev);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/***************************************************************************
 * -------------------------------WATCHDOG STUFF---------------------------
 **************************************************************************/
अटल लघु _rtl92e_is_tx_queue_empty(काष्ठा net_device *dev)
अणु
	पूर्णांक i = 0;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	क्रम (i = 0; i <= MGNT_QUEUE; i++) अणु
		अगर ((i == TXCMD_QUEUE) || (i == HCCA_QUEUE))
			जारी;
		अगर (skb_queue_len(&(&priv->tx_ring[i])->queue) > 0) अणु
			netdev_info(dev, "===>tx queue is not empty:%d, %d\n",
			       i, skb_queue_len(&(&priv->tx_ring[i])->queue));
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल क्रमागत reset_type _rtl92e_tx_check_stuck(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8	QueueID;
	bool	bCheckFwTxCnt = false;
	काष्ठा rtl8192_tx_ring  *ring = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा cb_desc *tcb_desc = शून्य;
	अचिन्हित दीर्घ flags = 0;

	चयन (priv->rtllib->ps) अणु
	हाल RTLLIB_PS_DISABLED:
		अवरोध;
	हाल (RTLLIB_PS_MBCAST | RTLLIB_PS_UNICAST):
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&priv->irq_th_lock, flags);
	क्रम (QueueID = 0; QueueID < MAX_TX_QUEUE; QueueID++) अणु
		अगर (QueueID == TXCMD_QUEUE)
			जारी;

		अगर (QueueID == BEACON_QUEUE)
			जारी;

		ring = &priv->tx_ring[QueueID];

		अगर (skb_queue_len(&ring->queue) == 0) अणु
			जारी;
		पूर्ण अन्यथा अणु
			skb = __skb_peek(&ring->queue);
			tcb_desc = (काष्ठा cb_desc *)(skb->cb +
				    MAX_DEV_ADDR_SIZE);
			tcb_desc->nStuckCount++;
			bCheckFwTxCnt = true;
			अगर (tcb_desc->nStuckCount > 1)
				netdev_info(dev,
					    "%s: QueueID=%d tcb_desc->nStuckCount=%d\n",
					    __func__, QueueID,
					    tcb_desc->nStuckCount);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->irq_th_lock, flags);

	अगर (bCheckFwTxCnt) अणु
		अगर (priv->ops->TxCheckStuckHandler(dev)) अणु
			RT_TRACE(COMP_RESET,
				 "TxCheckStuck(): Fw indicates no Tx condition!\n");
			वापस RESET_TYPE_SILENT;
		पूर्ण
	पूर्ण

	वापस RESET_TYPE_NORESET;
पूर्ण

अटल क्रमागत reset_type _rtl92e_rx_check_stuck(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->ops->RxCheckStuckHandler(dev)) अणु
		RT_TRACE(COMP_RESET, "RxStuck Condition\n");
		वापस RESET_TYPE_SILENT;
	पूर्ण

	वापस RESET_TYPE_NORESET;
पूर्ण

अटल क्रमागत reset_type _rtl92e_अगर_check_reset(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	क्रमागत reset_type TxResetType = RESET_TYPE_NORESET;
	क्रमागत reset_type RxResetType = RESET_TYPE_NORESET;
	क्रमागत rt_rf_घातer_state rfState;

	rfState = priv->rtllib->eRFPowerState;

	अगर (rfState == eRfOn)
		TxResetType = _rtl92e_tx_check_stuck(dev);

	अगर (rfState == eRfOn &&
	    (priv->rtllib->iw_mode == IW_MODE_INFRA) &&
	    (priv->rtllib->state == RTLLIB_LINKED))
		RxResetType = _rtl92e_rx_check_stuck(dev);

	अगर (TxResetType == RESET_TYPE_NORMAL ||
	    RxResetType == RESET_TYPE_NORMAL) अणु
		netdev_info(dev, "%s(): TxResetType is %d, RxResetType is %d\n",
			    __func__, TxResetType, RxResetType);
		वापस RESET_TYPE_NORMAL;
	पूर्ण अन्यथा अगर (TxResetType == RESET_TYPE_SILENT ||
		   RxResetType == RESET_TYPE_SILENT) अणु
		netdev_info(dev, "%s(): TxResetType is %d, RxResetType is %d\n",
			    __func__, TxResetType, RxResetType);
		वापस RESET_TYPE_SILENT;
	पूर्ण अन्यथा अणु
		वापस RESET_TYPE_NORESET;
	पूर्ण

पूर्ण

अटल व्योम _rtl92e_अगर_silent_reset(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8	reset_बार = 0;
	पूर्णांक reset_status = 0;
	काष्ठा rtllib_device *ieee = priv->rtllib;
	अचिन्हित दीर्घ flag;

	अगर (priv->ResetProgress == RESET_TYPE_NORESET) अणु

		RT_TRACE(COMP_RESET, "=========>Reset progress!!\n");

		priv->ResetProgress = RESET_TYPE_SILENT;

		spin_lock_irqsave(&priv->rf_ps_lock, flag);
		अगर (priv->RFChangeInProgress) अणु
			spin_unlock_irqrestore(&priv->rf_ps_lock, flag);
			जाओ END;
		पूर्ण
		priv->RFChangeInProgress = true;
		priv->bResetInProgress = true;
		spin_unlock_irqrestore(&priv->rf_ps_lock, flag);

RESET_START:

		mutex_lock(&priv->wx_mutex);

		अगर (priv->rtllib->state == RTLLIB_LINKED)
			rtl92e_leisure_ps_leave(dev);

		अगर (priv->up) अणु
			netdev_info(dev, "%s():the driver is not up.\n",
				    __func__);
			mutex_unlock(&priv->wx_mutex);
			वापस;
		पूर्ण
		priv->up = 0;

		RT_TRACE(COMP_RESET, "%s():======>start to down the driver\n",
			  __func__);
		mdelay(1000);
		RT_TRACE(COMP_RESET,
			 "%s():111111111111111111111111======>start to down the driver\n",
			 __func__);

		अगर (!netअगर_queue_stopped(dev))
			netअगर_stop_queue(dev);

		rtl92e_irq_disable(dev);
		del_समयr_sync(&priv->watch_करोg_समयr);
		_rtl92e_cancel_deferred_work(priv);
		rtl92e_dm_deinit(dev);
		rtllib_stop_scan_syncro(ieee);

		अगर (ieee->state == RTLLIB_LINKED) अणु
			mutex_lock(&ieee->wx_mutex);
			netdev_info(dev, "ieee->state is RTLLIB_LINKED\n");
			rtllib_stop_send_beacons(priv->rtllib);
			del_समयr_sync(&ieee->associate_समयr);
			cancel_delayed_work(&ieee->associate_retry_wq);
			rtllib_stop_scan(ieee);
			netअगर_carrier_off(dev);
			mutex_unlock(&ieee->wx_mutex);
		पूर्ण अन्यथा अणु
			netdev_info(dev, "ieee->state is NOT LINKED\n");
			rtllib_sofपंचांगac_stop_protocol(priv->rtllib, 0, true);
		पूर्ण

		rtl92e_dm_backup_state(dev);

		mutex_unlock(&priv->wx_mutex);
		RT_TRACE(COMP_RESET,
			 "%s():<==========down process is finished\n",
			 __func__);

		RT_TRACE(COMP_RESET, "%s():<===========up process start\n",
			 __func__);
		reset_status = _rtl92e_up(dev, true);

		RT_TRACE(COMP_RESET,
			 "%s():<===========up process is finished\n", __func__);
		अगर (reset_status == -1) अणु
			अगर (reset_बार < 3) अणु
				reset_बार++;
				जाओ RESET_START;
			पूर्ण अन्यथा अणु
				netdev_warn(dev, "%s():	Reset Failed\n",
					    __func__);
			पूर्ण
		पूर्ण

		ieee->is_silent_reset = 1;

		spin_lock_irqsave(&priv->rf_ps_lock, flag);
		priv->RFChangeInProgress = false;
		spin_unlock_irqrestore(&priv->rf_ps_lock, flag);

		rtl92e_enable_hw_security_config(dev);

		अगर (ieee->state == RTLLIB_LINKED && ieee->iw_mode ==
		    IW_MODE_INFRA) अणु
			ieee->set_chan(ieee->dev,
				       ieee->current_network.channel);

			schedule_work(&ieee->associate_complete_wq);

		पूर्ण अन्यथा अगर (ieee->state == RTLLIB_LINKED && ieee->iw_mode ==
			   IW_MODE_ADHOC) अणु
			ieee->set_chan(ieee->dev,
				       ieee->current_network.channel);
			ieee->link_change(ieee->dev);

			notअगरy_wx_assoc_event(ieee);

			rtllib_start_send_beacons(ieee);

			netअगर_carrier_on(ieee->dev);
		पूर्ण

		rtl92e_cam_restore(dev);
		rtl92e_dm_restore_state(dev);
END:
		priv->ResetProgress = RESET_TYPE_NORESET;
		priv->reset_count++;

		priv->bForcedSilentReset = false;
		priv->bResetInProgress = false;

		rtl92e_ग_लिखोb(dev, UFWP, 1);
		RT_TRACE(COMP_RESET, "Reset finished!! ====>[%d]\n",
			 priv->reset_count);
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_update_rxcounts(काष्ठा r8192_priv *priv, u32 *TotalRxBcnNum,
				    u32 *TotalRxDataNum)
अणु
	u16	SlotIndex;
	u8	i;

	*TotalRxBcnNum = 0;
	*TotalRxDataNum = 0;

	SlotIndex = (priv->rtllib->LinkDetectInfo.SlotIndex++) %
			(priv->rtllib->LinkDetectInfo.SlotNum);
	priv->rtllib->LinkDetectInfo.RxBcnNum[SlotIndex] =
			priv->rtllib->LinkDetectInfo.NumRecvBcnInPeriod;
	priv->rtllib->LinkDetectInfo.RxDataNum[SlotIndex] =
			priv->rtllib->LinkDetectInfo.NumRecvDataInPeriod;
	क्रम (i = 0; i < priv->rtllib->LinkDetectInfo.SlotNum; i++) अणु
		*TotalRxBcnNum += priv->rtllib->LinkDetectInfo.RxBcnNum[i];
		*TotalRxDataNum += priv->rtllib->LinkDetectInfo.RxDataNum[i];
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_watchकरोg_wq_cb(व्योम *data)
अणु
	काष्ठा r8192_priv *priv = container_of_dwork_rsl(data,
				  काष्ठा r8192_priv, watch_करोg_wq);
	काष्ठा net_device *dev = priv->rtllib->dev;
	काष्ठा rtllib_device *ieee = priv->rtllib;
	क्रमागत reset_type ResetType = RESET_TYPE_NORESET;
	अटल u8 check_reset_cnt;
	अचिन्हित दीर्घ flags;
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					(&priv->rtllib->PowerSaveControl);
	bool bBusyTraffic = false;
	bool	bHigherBusyTraffic = false;
	bool	bHigherBusyRxTraffic = false;
	bool bEnterPS = false;

	अगर (!priv->up || priv->bHwRadioOff)
		वापस;

	अगर (priv->rtllib->state >= RTLLIB_LINKED) अणु
		अगर (priv->rtllib->CntAfterLink < 2)
			priv->rtllib->CntAfterLink++;
	पूर्ण अन्यथा अणु
		priv->rtllib->CntAfterLink = 0;
	पूर्ण

	rtl92e_dm_watchकरोg(dev);

	अगर (!rtllib_act_scanning(priv->rtllib, false)) अणु
		अगर ((ieee->iw_mode == IW_MODE_INFRA) && (ieee->state ==
		     RTLLIB_NOLINK) &&
		     (ieee->eRFPowerState == eRfOn) && !ieee->is_set_key &&
		     (!ieee->proto_stoppping) && !ieee->wx_set_enc) अणु
			अगर ((ieee->PowerSaveControl.ReturnPoपूर्णांक ==
			     IPS_CALLBACK_NONE) &&
			     (!ieee->bNetPromiscuousMode)) अणु
				RT_TRACE(COMP_PS,
					 "====================>haha: rtl92e_ips_enter()\n");
				rtl92e_ips_enter(dev);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((ieee->state == RTLLIB_LINKED) && (ieee->iw_mode ==
	     IW_MODE_INFRA) && (!ieee->bNetPromiscuousMode)) अणु
		अगर (ieee->LinkDetectInfo.NumRxOkInPeriod > 100 ||
		ieee->LinkDetectInfo.NumTxOkInPeriod > 100)
			bBusyTraffic = true;


		अगर (ieee->LinkDetectInfo.NumRxOkInPeriod > 4000 ||
		    ieee->LinkDetectInfo.NumTxOkInPeriod > 4000) अणु
			bHigherBusyTraffic = true;
			अगर (ieee->LinkDetectInfo.NumRxOkInPeriod > 5000)
				bHigherBusyRxTraffic = true;
			अन्यथा
				bHigherBusyRxTraffic = false;
		पूर्ण

		अगर (((ieee->LinkDetectInfo.NumRxUnicastOkInPeriod +
		    ieee->LinkDetectInfo.NumTxOkInPeriod) > 8) ||
		    (ieee->LinkDetectInfo.NumRxUnicastOkInPeriod > 2))
			bEnterPS = false;
		अन्यथा
			bEnterPS = true;

		अगर (ieee->current_network.beacon_पूर्णांकerval < 95)
			bEnterPS = false;

		अगर (bEnterPS)
			rtl92e_leisure_ps_enter(dev);
		अन्यथा
			rtl92e_leisure_ps_leave(dev);

	पूर्ण अन्यथा अणु
		RT_TRACE(COMP_LPS, "====>no link LPS leave\n");
		rtl92e_leisure_ps_leave(dev);
	पूर्ण

	ieee->LinkDetectInfo.NumRxOkInPeriod = 0;
	ieee->LinkDetectInfo.NumTxOkInPeriod = 0;
	ieee->LinkDetectInfo.NumRxUnicastOkInPeriod = 0;
	ieee->LinkDetectInfo.bBusyTraffic = bBusyTraffic;

	ieee->LinkDetectInfo.bHigherBusyTraffic = bHigherBusyTraffic;
	ieee->LinkDetectInfo.bHigherBusyRxTraffic = bHigherBusyRxTraffic;

	अगर (ieee->state == RTLLIB_LINKED && ieee->iw_mode == IW_MODE_INFRA) अणु
		u32	TotalRxBcnNum = 0;
		u32	TotalRxDataNum = 0;

		_rtl92e_update_rxcounts(priv, &TotalRxBcnNum, &TotalRxDataNum);

		अगर ((TotalRxBcnNum + TotalRxDataNum) == 0)
			priv->check_roaming_cnt++;
		अन्यथा
			priv->check_roaming_cnt = 0;


		अगर (priv->check_roaming_cnt > 0) अणु
			अगर (ieee->eRFPowerState == eRfOff)
				netdev_info(dev, "%s(): RF is off\n", __func__);

			netdev_info(dev,
				    "===>%s(): AP is power off, chan:%d, connect another one\n",
				    __func__, priv->chan);

			ieee->state = RTLLIB_ASSOCIATING;

			RemovePeerTS(priv->rtllib,
				     priv->rtllib->current_network.bssid);
			ieee->is_roaming = true;
			ieee->is_set_key = false;
			ieee->link_change(dev);
			अगर (ieee->LedControlHandler)
				ieee->LedControlHandler(ieee->dev,
							LED_CTL_START_TO_LINK);

			notअगरy_wx_assoc_event(ieee);

			अगर (!(ieee->rtllib_ap_sec_type(ieee) &
			     (SEC_ALG_CCMP | SEC_ALG_TKIP)))
				schedule_delayed_work(
					&ieee->associate_procedure_wq, 0);

			priv->check_roaming_cnt = 0;
		पूर्ण
		ieee->LinkDetectInfo.NumRecvBcnInPeriod = 0;
		ieee->LinkDetectInfo.NumRecvDataInPeriod = 0;

	पूर्ण

	spin_lock_irqsave(&priv->tx_lock, flags);
	अगर ((check_reset_cnt++ >= 3) && (!ieee->is_roaming) &&
	    (!priv->RFChangeInProgress) && (!pPSC->bSwRfProcessing)) अणु
		ResetType = _rtl92e_अगर_check_reset(dev);
		check_reset_cnt = 3;
	पूर्ण
	spin_unlock_irqrestore(&priv->tx_lock, flags);

	अगर (!priv->bDisableNormalResetCheck && ResetType == RESET_TYPE_NORMAL) अणु
		priv->ResetProgress = RESET_TYPE_NORMAL;
		RT_TRACE(COMP_RESET, "%s(): NOMAL RESET\n", __func__);
		वापस;
	पूर्ण

	अगर (((priv->क्रमce_reset) || (!priv->bDisableNormalResetCheck &&
	      ResetType == RESET_TYPE_SILENT)))
		_rtl92e_अगर_silent_reset(dev);
	priv->क्रमce_reset = false;
	priv->bForcedSilentReset = false;
	priv->bResetInProgress = false;
	RT_TRACE(COMP_TRACE, " <==RtUsbCheckForHangWorkItemCallback()\n");
पूर्ण

अटल व्योम _rtl92e_watchकरोg_समयr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा r8192_priv *priv = from_समयr(priv, t, watch_करोg_समयr);

	schedule_delayed_work(&priv->watch_करोg_wq, 0);
	mod_समयr(&priv->watch_करोg_समयr, jअगरfies +
		  msecs_to_jअगरfies(RTLLIB_WATCH_DOG_TIME));
पूर्ण

/****************************************************************************
 * ---------------------------- NIC TX/RX STUFF---------------------------
 ****************************************************************************/
व्योम rtl92e_rx_enable(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->ops->rx_enable(dev);
पूर्ण

व्योम rtl92e_tx_enable(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->ops->tx_enable(dev);

	rtllib_reset_queue(priv->rtllib);
पूर्ण


अटल व्योम _rtl92e_मुक्त_rx_ring(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक i, rx_queue_idx;

	क्रम (rx_queue_idx = 0; rx_queue_idx < MAX_RX_QUEUE;
	     rx_queue_idx++) अणु
		क्रम (i = 0; i < priv->rxringcount; i++) अणु
			काष्ठा sk_buff *skb = priv->rx_buf[rx_queue_idx][i];

			अगर (!skb)
				जारी;

			dma_unmap_single(&priv->pdev->dev,
					 *((dma_addr_t *)skb->cb),
					 priv->rxbuffersize, DMA_FROM_DEVICE);
			kमुक्त_skb(skb);
		पूर्ण

		dma_मुक्त_coherent(&priv->pdev->dev,
				  माप(*priv->rx_ring[rx_queue_idx]) * priv->rxringcount,
				  priv->rx_ring[rx_queue_idx],
				  priv->rx_ring_dma[rx_queue_idx]);
		priv->rx_ring[rx_queue_idx] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_मुक्त_tx_ring(काष्ठा net_device *dev, अचिन्हित पूर्णांक prio)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtl8192_tx_ring *ring = &priv->tx_ring[prio];

	जबतक (skb_queue_len(&ring->queue)) अणु
		काष्ठा tx_desc *entry = &ring->desc[ring->idx];
		काष्ठा sk_buff *skb = __skb_dequeue(&ring->queue);

		dma_unmap_single(&priv->pdev->dev, entry->TxBuffAddr,
				 skb->len, DMA_TO_DEVICE);
		kमुक्त_skb(skb);
		ring->idx = (ring->idx + 1) % ring->entries;
	पूर्ण

	dma_मुक्त_coherent(&priv->pdev->dev,
			  माप(*ring->desc) * ring->entries, ring->desc,
			  ring->dma);
	ring->desc = शून्य;
पूर्ण

अटल व्योम _rtl92e_hard_data_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   पूर्णांक rate)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक ret;
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb +
				    MAX_DEV_ADDR_SIZE);
	u8 queue_index = tcb_desc->queue_index;

	अगर ((priv->rtllib->eRFPowerState == eRfOff) || !priv->up ||
	     priv->bResetInProgress) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (queue_index == TXCMD_QUEUE)
		netdev_warn(dev, "%s(): queue index == TXCMD_QUEUE\n",
			    __func__);

	स_नकल((अचिन्हित अक्षर *)(skb->cb), &dev, माप(dev));
	skb_push(skb, priv->rtllib->tx_headroom);
	ret = _rtl92e_tx(dev, skb);

	अगर (queue_index != MGNT_QUEUE) अणु
		priv->rtllib->stats.tx_bytes += (skb->len -
						 priv->rtllib->tx_headroom);
		priv->rtllib->stats.tx_packets++;
	पूर्ण

	अगर (ret != 0)
		kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक _rtl92e_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक ret;
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb +
				    MAX_DEV_ADDR_SIZE);
	u8 queue_index = tcb_desc->queue_index;

	अगर (queue_index != TXCMD_QUEUE) अणु
		अगर ((priv->rtllib->eRFPowerState == eRfOff) ||
		     !priv->up || priv->bResetInProgress) अणु
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
	पूर्ण

	स_नकल((अचिन्हित अक्षर *)(skb->cb), &dev, माप(dev));
	अगर (queue_index == TXCMD_QUEUE) अणु
		_rtl92e_tx_cmd(dev, skb);
		वापस 0;
	पूर्ण

	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;
	tcb_desc->bTxEnableFwCalcDur = 1;
	skb_push(skb, priv->rtllib->tx_headroom);
	ret = _rtl92e_tx(dev, skb);
	अगर (ret != 0)
		kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल व्योम _rtl92e_tx_isr(काष्ठा net_device *dev, पूर्णांक prio)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	काष्ठा rtl8192_tx_ring *ring = &priv->tx_ring[prio];

	जबतक (skb_queue_len(&ring->queue)) अणु
		काष्ठा tx_desc *entry = &ring->desc[ring->idx];
		काष्ठा sk_buff *skb;

		अगर (prio != BEACON_QUEUE) अणु
			अगर (entry->OWN)
				वापस;
			ring->idx = (ring->idx + 1) % ring->entries;
		पूर्ण

		skb = __skb_dequeue(&ring->queue);
		dma_unmap_single(&priv->pdev->dev, entry->TxBuffAddr,
				 skb->len, DMA_TO_DEVICE);

		kमुक्त_skb(skb);
	पूर्ण
	अगर (prio != BEACON_QUEUE)
		tasklet_schedule(&priv->irq_tx_tasklet);
पूर्ण

अटल व्योम _rtl92e_tx_cmd(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtl8192_tx_ring *ring;
	काष्ठा tx_desc_cmd *entry;
	अचिन्हित पूर्णांक idx;
	काष्ठा cb_desc *tcb_desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->irq_th_lock, flags);
	ring = &priv->tx_ring[TXCMD_QUEUE];

	idx = (ring->idx + skb_queue_len(&ring->queue)) % ring->entries;
	entry = (काष्ठा tx_desc_cmd *)&ring->desc[idx];

	tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);

	priv->ops->tx_fill_cmd_descriptor(dev, entry, tcb_desc, skb);

	__skb_queue_tail(&ring->queue, skb);
	spin_unlock_irqrestore(&priv->irq_th_lock, flags);
पूर्ण

अटल लघु _rtl92e_tx(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtl8192_tx_ring  *ring;
	अचिन्हित दीर्घ flags;
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb +
				    MAX_DEV_ADDR_SIZE);
	काष्ठा tx_desc *pdesc = शून्य;
	काष्ठा rtllib_hdr_1addr *header = शून्य;
	u16 fc = 0, type = 0;
	u8 *pda_addr = शून्य;
	पूर्णांक   idx;
	u32 fwinfo_size = 0;

	अगर (priv->bdisable_nic) अणु
		netdev_warn(dev, "%s: Nic is disabled! Can't tx packet.\n",
			    __func__);
		वापस skb->len;
	पूर्ण

	priv->rtllib->bAwakePktSent = true;

	fwinfo_size = माप(काष्ठा tx_fwinfo_8190pci);

	header = (काष्ठा rtllib_hdr_1addr *)(((u8 *)skb->data) + fwinfo_size);
	fc = le16_to_cpu(header->frame_ctl);
	type = WLAN_FC_GET_TYPE(fc);
	pda_addr = header->addr1;

	अगर (is_broadcast_ether_addr(pda_addr))
		priv->stats.txbytesbroadcast += skb->len - fwinfo_size;
	अन्यथा अगर (is_multicast_ether_addr(pda_addr))
		priv->stats.txbytesmulticast += skb->len - fwinfo_size;
	अन्यथा
		priv->stats.txbytesunicast += skb->len - fwinfo_size;

	spin_lock_irqsave(&priv->irq_th_lock, flags);
	ring = &priv->tx_ring[tcb_desc->queue_index];
	अगर (tcb_desc->queue_index != BEACON_QUEUE)
		idx = (ring->idx + skb_queue_len(&ring->queue)) % ring->entries;
	अन्यथा
		idx = 0;

	pdesc = &ring->desc[idx];
	अगर ((pdesc->OWN == 1) && (tcb_desc->queue_index != BEACON_QUEUE)) अणु
		netdev_warn(dev,
			    "No more TX desc@%d, ring->idx = %d, idx = %d, skblen = 0x%x queuelen=%d",
			    tcb_desc->queue_index, ring->idx, idx, skb->len,
			    skb_queue_len(&ring->queue));
		spin_unlock_irqrestore(&priv->irq_th_lock, flags);
		वापस skb->len;
	पूर्ण

	अगर (type == RTLLIB_FTYPE_DATA) अणु
		अगर (priv->rtllib->LedControlHandler)
			priv->rtllib->LedControlHandler(dev, LED_CTL_TX);
	पूर्ण
	priv->ops->tx_fill_descriptor(dev, pdesc, tcb_desc, skb);
	__skb_queue_tail(&ring->queue, skb);
	pdesc->OWN = 1;
	spin_unlock_irqrestore(&priv->irq_th_lock, flags);
	netअगर_trans_update(dev);

	rtl92e_ग_लिखोw(dev, TPPoll, 0x01 << tcb_desc->queue_index);
	वापस 0;
पूर्ण

अटल लघु _rtl92e_alloc_rx_ring(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rx_desc *entry = शून्य;
	पूर्णांक i, rx_queue_idx;

	क्रम (rx_queue_idx = 0; rx_queue_idx < MAX_RX_QUEUE; rx_queue_idx++) अणु
		priv->rx_ring[rx_queue_idx] = dma_alloc_coherent(&priv->pdev->dev,
								 माप(*priv->rx_ring[rx_queue_idx]) * priv->rxringcount,
								 &priv->rx_ring_dma[rx_queue_idx],
								 GFP_ATOMIC);
		अगर (!priv->rx_ring[rx_queue_idx] ||
		    (अचिन्हित दीर्घ)priv->rx_ring[rx_queue_idx] & 0xFF) अणु
			netdev_warn(dev, "Cannot allocate RX ring\n");
			वापस -ENOMEM;
		पूर्ण

		priv->rx_idx[rx_queue_idx] = 0;

		क्रम (i = 0; i < priv->rxringcount; i++) अणु
			काष्ठा sk_buff *skb = dev_alloc_skb(priv->rxbuffersize);
			dma_addr_t *mapping;

			entry = &priv->rx_ring[rx_queue_idx][i];
			अगर (!skb)
				वापस 0;
			skb->dev = dev;
			priv->rx_buf[rx_queue_idx][i] = skb;
			mapping = (dma_addr_t *)skb->cb;
			*mapping = dma_map_single(&priv->pdev->dev,
						  skb_tail_poपूर्णांकer_rsl(skb),
						  priv->rxbuffersize, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&priv->pdev->dev, *mapping)) अणु
				dev_kमुक्त_skb_any(skb);
				वापस -1;
			पूर्ण
			entry->BufferAddress = *mapping;

			entry->Length = priv->rxbuffersize;
			entry->OWN = 1;
		पूर्ण

		अगर (entry)
			entry->EOR = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_alloc_tx_ring(काष्ठा net_device *dev, अचिन्हित पूर्णांक prio,
				 अचिन्हित पूर्णांक entries)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा tx_desc *ring;
	dma_addr_t dma;
	पूर्णांक i;

	ring = dma_alloc_coherent(&priv->pdev->dev, माप(*ring) * entries,
				  &dma, GFP_ATOMIC);
	अगर (!ring || (अचिन्हित दीर्घ)ring & 0xFF) अणु
		netdev_warn(dev, "Cannot allocate TX ring (prio = %d)\n", prio);
		वापस -ENOMEM;
	पूर्ण

	priv->tx_ring[prio].desc = ring;
	priv->tx_ring[prio].dma = dma;
	priv->tx_ring[prio].idx = 0;
	priv->tx_ring[prio].entries = entries;
	skb_queue_head_init(&priv->tx_ring[prio].queue);

	क्रम (i = 0; i < entries; i++)
		ring[i].NextDescAddress =
			(u32)dma + ((i + 1) % entries) *
			माप(*ring);

	वापस 0;
पूर्ण

अटल लघु _rtl92e_pci_initdescring(काष्ठा net_device *dev)
अणु
	u32 ret;
	पूर्णांक i;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	ret = _rtl92e_alloc_rx_ring(dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < MAX_TX_QUEUE_COUNT; i++) अणु
		ret = _rtl92e_alloc_tx_ring(dev, i, priv->txringcount);
		अगर (ret)
			जाओ err_मुक्त_rings;
	पूर्ण

	वापस 0;

err_मुक्त_rings:
	_rtl92e_मुक्त_rx_ring(dev);
	क्रम (i = 0; i < MAX_TX_QUEUE_COUNT; i++)
		अगर (priv->tx_ring[i].desc)
			_rtl92e_मुक्त_tx_ring(dev, i);
	वापस 1;
पूर्ण

व्योम rtl92e_reset_desc_ring(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक i, rx_queue_idx;
	अचिन्हित दीर्घ flags = 0;

	क्रम (rx_queue_idx = 0; rx_queue_idx < MAX_RX_QUEUE; rx_queue_idx++) अणु
		अगर (priv->rx_ring[rx_queue_idx]) अणु
			काष्ठा rx_desc *entry = शून्य;

			क्रम (i = 0; i < priv->rxringcount; i++) अणु
				entry = &priv->rx_ring[rx_queue_idx][i];
				entry->OWN = 1;
			पूर्ण
			priv->rx_idx[rx_queue_idx] = 0;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&priv->irq_th_lock, flags);
	क्रम (i = 0; i < MAX_TX_QUEUE_COUNT; i++) अणु
		अगर (priv->tx_ring[i].desc) अणु
			काष्ठा rtl8192_tx_ring *ring = &priv->tx_ring[i];

			जबतक (skb_queue_len(&ring->queue)) अणु
				काष्ठा tx_desc *entry = &ring->desc[ring->idx];
				काष्ठा sk_buff *skb =
						 __skb_dequeue(&ring->queue);

				dma_unmap_single(&priv->pdev->dev,
						 entry->TxBuffAddr, skb->len,
						 DMA_TO_DEVICE);
				kमुक्त_skb(skb);
				ring->idx = (ring->idx + 1) % ring->entries;
			पूर्ण
			ring->idx = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->irq_th_lock, flags);
पूर्ण

व्योम rtl92e_update_rx_pkt_बारtamp(काष्ठा net_device *dev,
				    काष्ठा rtllib_rx_stats *stats)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (stats->bIsAMPDU && !stats->bFirstMPDU)
		stats->mac_समय = priv->LastRxDescTSF;
	अन्यथा
		priv->LastRxDescTSF = stats->mac_समय;
पूर्ण

दीर्घ rtl92e_translate_to_dbm(काष्ठा r8192_priv *priv, u8 संकेत_strength_index)
अणु
	दीर्घ	संकेत_घातer;

	संकेत_घातer = (दीर्घ)((संकेत_strength_index + 1) >> 1);
	संकेत_घातer -= 95;

	वापस संकेत_घातer;
पूर्ण


व्योम rtl92e_update_rx_statistics(काष्ठा r8192_priv *priv,
				 काष्ठा rtllib_rx_stats *pprevious_stats)
अणु
	पूर्णांक weighting = 0;


	अगर (priv->stats.recv_संकेत_घातer == 0)
		priv->stats.recv_संकेत_घातer =
					 pprevious_stats->RecvSignalPower;

	अगर (pprevious_stats->RecvSignalPower > priv->stats.recv_संकेत_घातer)
		weighting = 5;
	अन्यथा अगर (pprevious_stats->RecvSignalPower <
		 priv->stats.recv_संकेत_घातer)
		weighting = (-5);
	priv->stats.recv_संकेत_घातer = (priv->stats.recv_संकेत_घातer * 5 +
					pprevious_stats->RecvSignalPower +
					weighting) / 6;
पूर्ण

u8 rtl92e_rx_db_to_percent(s8 antघातer)
अणु
	अगर ((antघातer <= -100) || (antघातer >= 20))
		वापस	0;
	अन्यथा अगर (antघातer >= 0)
		वापस	100;
	अन्यथा
		वापस	100 + antघातer;

पूर्ण	/* QueryRxPwrPercentage */

u8 rtl92e_evm_db_to_percent(s8 value)
अणु
	s8 ret_val = clamp(-value, 0, 33) * 3;

	अगर (ret_val == 99)
		ret_val = 100;

	वापस ret_val;
पूर्ण

व्योम rtl92e_copy_mpdu_stats(काष्ठा rtllib_rx_stats *psrc_stats,
			    काष्ठा rtllib_rx_stats *ptarget_stats)
अणु
	ptarget_stats->bIsAMPDU = psrc_stats->bIsAMPDU;
	ptarget_stats->bFirstMPDU = psrc_stats->bFirstMPDU;
पूर्ण



अटल व्योम _rtl92e_rx_normal(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_hdr_1addr *rtllib_hdr = शून्य;
	bool unicast_packet = false;
	bool bLedBlinking = true;
	u16 fc = 0, type = 0;
	u32 skb_len = 0;
	पूर्णांक rx_queue_idx = RX_MPDU_QUEUE;

	काष्ठा rtllib_rx_stats stats = अणु
		.संकेत = 0,
		.noise = (u8)-98,
		.rate = 0,
		.freq = RTLLIB_24GHZ_BAND,
	पूर्ण;
	अचिन्हित पूर्णांक count = priv->rxringcount;

	stats.nic_type = NIC_8192E;

	जबतक (count--) अणु
		काष्ठा rx_desc *pdesc = &priv->rx_ring[rx_queue_idx]
					[priv->rx_idx[rx_queue_idx]];
		काष्ठा sk_buff *skb = priv->rx_buf[rx_queue_idx]
				      [priv->rx_idx[rx_queue_idx]];
		काष्ठा sk_buff *new_skb;

		अगर (pdesc->OWN)
			वापस;
		अगर (!priv->ops->rx_query_status_descriptor(dev, &stats,
		pdesc, skb))
			जाओ करोne;
		new_skb = dev_alloc_skb(priv->rxbuffersize);
		/* अगर allocation of new skb failed - drop current packet
		 * and reuse skb
		 */
		अगर (unlikely(!new_skb))
			जाओ करोne;

		dma_unmap_single(&priv->pdev->dev, *((dma_addr_t *)skb->cb),
				 priv->rxbuffersize, DMA_FROM_DEVICE);

		skb_put(skb, pdesc->Length);
		skb_reserve(skb, stats.RxDrvInfoSize +
			stats.RxBufShअगरt);
		skb_trim(skb, skb->len - 4/*sCrcLng*/);
		rtllib_hdr = (काष्ठा rtllib_hdr_1addr *)skb->data;
		अगर (!is_multicast_ether_addr(rtllib_hdr->addr1)) अणु
			/* unicast packet */
			unicast_packet = true;
		पूर्ण
		fc = le16_to_cpu(rtllib_hdr->frame_ctl);
		type = WLAN_FC_GET_TYPE(fc);
		अगर (type == RTLLIB_FTYPE_MGMT)
			bLedBlinking = false;

		अगर (bLedBlinking)
			अगर (priv->rtllib->LedControlHandler)
				priv->rtllib->LedControlHandler(dev,
							LED_CTL_RX);

		अगर (stats.bCRC) अणु
			अगर (type != RTLLIB_FTYPE_MGMT)
				priv->stats.rxdatacrcerr++;
			अन्यथा
				priv->stats.rxmgmtcrcerr++;
		पूर्ण

		skb_len = skb->len;

		अगर (!rtllib_rx(priv->rtllib, skb, &stats)) अणु
			dev_kमुक्त_skb_any(skb);
		पूर्ण अन्यथा अणु
			priv->stats.rxok++;
			अगर (unicast_packet)
				priv->stats.rxbytesunicast += skb_len;
		पूर्ण

		skb = new_skb;
		skb->dev = dev;

		priv->rx_buf[rx_queue_idx][priv->rx_idx[rx_queue_idx]] =
								 skb;
		*((dma_addr_t *)skb->cb) = dma_map_single(&priv->pdev->dev,
							  skb_tail_poपूर्णांकer_rsl(skb),
							  priv->rxbuffersize, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&priv->pdev->dev, *((dma_addr_t *)skb->cb))) अणु
			dev_kमुक्त_skb_any(skb);
			वापस;
		पूर्ण
करोne:
		pdesc->BufferAddress = *((dma_addr_t *)skb->cb);
		pdesc->OWN = 1;
		pdesc->Length = priv->rxbuffersize;
		अगर (priv->rx_idx[rx_queue_idx] == priv->rxringcount - 1)
			pdesc->EOR = 1;
		priv->rx_idx[rx_queue_idx] = (priv->rx_idx[rx_queue_idx] + 1) %
					      priv->rxringcount;
	पूर्ण

पूर्ण

अटल व्योम _rtl92e_tx_resume(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;
	काष्ठा sk_buff *skb;
	पूर्णांक queue_index;

	क्रम (queue_index = BK_QUEUE;
	     queue_index < MAX_QUEUE_SIZE; queue_index++) अणु
		जबतक ((!skb_queue_empty(&ieee->skb_रुकोQ[queue_index])) &&
		(priv->rtllib->check_nic_enough_desc(dev, queue_index) > 0)) अणु
			skb = skb_dequeue(&ieee->skb_रुकोQ[queue_index]);
			ieee->sofपंचांगac_data_hard_start_xmit(skb, dev, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_irq_tx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा r8192_priv *priv = from_tasklet(priv, t, irq_tx_tasklet);

	_rtl92e_tx_resume(priv->rtllib->dev);
पूर्ण

अटल व्योम _rtl92e_irq_rx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा r8192_priv *priv = from_tasklet(priv, t, irq_rx_tasklet);

	_rtl92e_rx_normal(priv->rtllib->dev);

	rtl92e_ग_लिखोl(priv->rtllib->dev, INTA_MASK,
		      rtl92e_पढ़ोl(priv->rtllib->dev, INTA_MASK) | IMR_RDU);
पूर्ण

/****************************************************************************
 * ---------------------------- NIC START/CLOSE STUFF---------------------------
 ****************************************************************************/
अटल व्योम _rtl92e_cancel_deferred_work(काष्ठा r8192_priv *priv)
अणु
	cancel_delayed_work_sync(&priv->watch_करोg_wq);
	cancel_delayed_work_sync(&priv->update_beacon_wq);
	cancel_delayed_work(&priv->rtllib->hw_sleep_wq);
	cancel_work_sync(&priv->reset_wq);
	cancel_work_sync(&priv->qos_activate);
पूर्ण

अटल पूर्णांक _rtl92e_up(काष्ठा net_device *dev, bool is_silent_reset)
अणु
	अगर (_rtl92e_sta_up(dev, is_silent_reset) == -1)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक ret;

	mutex_lock(&priv->wx_mutex);
	ret = _rtl92e_try_up(dev);
	mutex_unlock(&priv->wx_mutex);
	वापस ret;

पूर्ण

अटल पूर्णांक _rtl92e_try_up(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->up == 1)
		वापस -1;
	वापस _rtl92e_up(dev, false);
पूर्ण


अटल पूर्णांक _rtl92e_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक ret;

	अगर ((rtllib_act_scanning(priv->rtllib, false)) &&
		!(priv->rtllib->sofपंचांगac_features & IEEE_SOFTMAC_SCAN)) अणु
		rtllib_stop_scan(priv->rtllib);
	पूर्ण

	mutex_lock(&priv->wx_mutex);

	ret = _rtl92e_करोwn(dev, true);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;

पूर्ण

अटल पूर्णांक _rtl92e_करोwn(काष्ठा net_device *dev, bool shutकरोwnrf)
अणु
	अगर (_rtl92e_sta_करोwn(dev, shutकरोwnrf) == -1)
		वापस -1;

	वापस 0;
पूर्ण

व्योम rtl92e_commit(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->up == 0)
		वापस;
	rtllib_sofपंचांगac_stop_protocol(priv->rtllib, 0, true);
	rtl92e_irq_disable(dev);
	priv->ops->stop_adapter(dev, true);
	_rtl92e_up(dev, false);
पूर्ण

अटल व्योम _rtl92e_restart(व्योम *data)
अणु
	काष्ठा r8192_priv *priv = container_of_work_rsl(data, काष्ठा r8192_priv,
				  reset_wq);
	काष्ठा net_device *dev = priv->rtllib->dev;

	mutex_lock(&priv->wx_mutex);

	rtl92e_commit(dev);

	mutex_unlock(&priv->wx_mutex);
पूर्ण

अटल व्योम _rtl92e_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	लघु promisc;

	promisc = (dev->flags & IFF_PROMISC) ? 1 : 0;
	priv->promisc = promisc;

पूर्ण


अटल पूर्णांक _rtl92e_set_mac_adr(काष्ठा net_device *dev, व्योम *mac)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा sockaddr *addr = mac;

	mutex_lock(&priv->wx_mutex);

	ether_addr_copy(dev->dev_addr, addr->sa_data);

	schedule_work(&priv->reset_wq);
	mutex_unlock(&priv->wx_mutex);

	वापस 0;
पूर्ण

अटल irqवापस_t _rtl92e_irq(पूर्णांक irq, व्योम *netdev)
अणु
	काष्ठा net_device *dev = netdev;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अचिन्हित दीर्घ flags;
	u32 पूर्णांकa;
	u32 पूर्णांकb;

	पूर्णांकb = 0;

	अगर (priv->irq_enabled == 0)
		जाओ करोne;

	spin_lock_irqsave(&priv->irq_th_lock, flags);

	priv->ops->पूर्णांकerrupt_recognized(dev, &पूर्णांकa, &पूर्णांकb);
	priv->stats.shपूर्णांकs++;

	अगर (!पूर्णांकa) अणु
		spin_unlock_irqrestore(&priv->irq_th_lock, flags);
		जाओ करोne;
	पूर्ण

	अगर (पूर्णांकa == 0xffff) अणु
		spin_unlock_irqrestore(&priv->irq_th_lock, flags);
		जाओ करोne;
	पूर्ण

	priv->stats.पूर्णांकs++;

	अगर (!netअगर_running(dev)) अणु
		spin_unlock_irqrestore(&priv->irq_th_lock, flags);
		जाओ करोne;
	पूर्ण

	अगर (पूर्णांकa & IMR_TBDOK) अणु
		RT_TRACE(COMP_INTR, "beacon ok interrupt!\n");
		priv->stats.txbeaconokपूर्णांक++;
	पूर्ण

	अगर (पूर्णांकa & IMR_TBDER) अणु
		RT_TRACE(COMP_INTR, "beacon ok interrupt!\n");
		priv->stats.txbeaconerr++;
	पूर्ण

	अगर (पूर्णांकa & IMR_BDOK)
		RT_TRACE(COMP_INTR, "beacon interrupt!\n");

	अगर (पूर्णांकa  & IMR_MGNTDOK) अणु
		RT_TRACE(COMP_INTR, "Manage ok interrupt!\n");
		priv->stats.txmanageokपूर्णांक++;
		_rtl92e_tx_isr(dev, MGNT_QUEUE);
		spin_unlock_irqrestore(&priv->irq_th_lock, flags);
		अगर (priv->rtllib->ack_tx_to_ieee) अणु
			अगर (_rtl92e_is_tx_queue_empty(dev)) अणु
				priv->rtllib->ack_tx_to_ieee = 0;
				rtllib_ps_tx_ack(priv->rtllib, 1);
			पूर्ण
		पूर्ण
		spin_lock_irqsave(&priv->irq_th_lock, flags);
	पूर्ण

	अगर (पूर्णांकa & IMR_COMDOK) अणु
		priv->stats.txcmdpktokपूर्णांक++;
		_rtl92e_tx_isr(dev, TXCMD_QUEUE);
	पूर्ण

	अगर (पूर्णांकa & IMR_HIGHDOK)
		_rtl92e_tx_isr(dev, HIGH_QUEUE);

	अगर (पूर्णांकa & IMR_ROK) अणु
		priv->stats.rxपूर्णांक++;
		priv->InterruptLog.nIMR_ROK++;
		tasklet_schedule(&priv->irq_rx_tasklet);
	पूर्ण

	अगर (पूर्णांकa & IMR_BcnInt) अणु
		RT_TRACE(COMP_INTR, "prepare beacon for interrupt!\n");
		tasklet_schedule(&priv->irq_prepare_beacon_tasklet);
	पूर्ण

	अगर (पूर्णांकa & IMR_RDU) अणु
		RT_TRACE(COMP_INTR, "rx descriptor unavailable!\n");
		priv->stats.rxrdu++;
		rtl92e_ग_लिखोl(dev, INTA_MASK,
			      rtl92e_पढ़ोl(dev, INTA_MASK) & ~IMR_RDU);
		tasklet_schedule(&priv->irq_rx_tasklet);
	पूर्ण

	अगर (पूर्णांकa & IMR_RXFOVW) अणु
		RT_TRACE(COMP_INTR, "rx overflow !\n");
		priv->stats.rxoverflow++;
		tasklet_schedule(&priv->irq_rx_tasklet);
	पूर्ण

	अगर (पूर्णांकa & IMR_TXFOVW)
		priv->stats.txoverflow++;

	अगर (पूर्णांकa & IMR_BKDOK) अणु
		RT_TRACE(COMP_INTR, "BK Tx OK interrupt!\n");
		priv->stats.txbkokपूर्णांक++;
		priv->rtllib->LinkDetectInfo.NumTxOkInPeriod++;
		_rtl92e_tx_isr(dev, BK_QUEUE);
	पूर्ण

	अगर (पूर्णांकa & IMR_BEDOK) अणु
		RT_TRACE(COMP_INTR, "BE TX OK interrupt!\n");
		priv->stats.txbeokपूर्णांक++;
		priv->rtllib->LinkDetectInfo.NumTxOkInPeriod++;
		_rtl92e_tx_isr(dev, BE_QUEUE);
	पूर्ण

	अगर (पूर्णांकa & IMR_VIDOK) अणु
		RT_TRACE(COMP_INTR, "VI TX OK interrupt!\n");
		priv->stats.txviokपूर्णांक++;
		priv->rtllib->LinkDetectInfo.NumTxOkInPeriod++;
		_rtl92e_tx_isr(dev, VI_QUEUE);
	पूर्ण

	अगर (पूर्णांकa & IMR_VODOK) अणु
		priv->stats.txvookपूर्णांक++;
		RT_TRACE(COMP_INTR, "Vo TX OK interrupt!\n");
		priv->rtllib->LinkDetectInfo.NumTxOkInPeriod++;
		_rtl92e_tx_isr(dev, VO_QUEUE);
	पूर्ण

	spin_unlock_irqrestore(&priv->irq_th_lock, flags);

करोne:

	वापस IRQ_HANDLED;
पूर्ण



/****************************************************************************
 * ---------------------------- PCI_STUFF---------------------------
 ****************************************************************************/
अटल स्थिर काष्ठा net_device_ops rtl8192_netdev_ops = अणु
	.nकरो_खोलो = _rtl92e_खोलो,
	.nकरो_stop = _rtl92e_बंद,
	.nकरो_tx_समयout = _rtl92e_tx_समयout,
	.nकरो_set_rx_mode = _rtl92e_set_multicast,
	.nकरो_set_mac_address = _rtl92e_set_mac_adr,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_start_xmit = rtllib_xmit,
पूर्ण;

अटल पूर्णांक _rtl92e_pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित दीर्घ ioaddr = 0;
	काष्ठा net_device *dev = शून्य;
	काष्ठा r8192_priv *priv = शून्य;
	काष्ठा rtl819x_ops *ops = (काष्ठा rtl819x_ops *)(id->driver_data);
	अचिन्हित दीर्घ pmem_start, pmem_len, pmem_flags;
	पूर्णांक err = -ENOMEM;
	u8 revision_id;

	RT_TRACE(COMP_INIT, "Configuring chip resources");

	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev, "Failed to enable PCI device");
		वापस -EIO;
	पूर्ण

	pci_set_master(pdev);

	अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		अगर (dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
			dev_info(&pdev->dev,
				 "Unable to obtain 32bit DMA for consistent allocations\n");
			जाओ err_pci_disable;
		पूर्ण
	पूर्ण
	dev = alloc_rtllib(माप(काष्ठा r8192_priv));
	अगर (!dev)
		जाओ err_pci_disable;

	err = -ENODEV;

	pci_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);
	priv = rtllib_priv(dev);
	priv->rtllib = (काष्ठा rtllib_device *)netdev_priv_rsl(dev);
	priv->pdev = pdev;
	priv->rtllib->pdev = pdev;
	अगर ((pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_DLINK) &&
	    (pdev->subप्रणाली_device == 0x3304))
		priv->rtllib->bSupportRemoteWakeUp = 1;
	अन्यथा
		priv->rtllib->bSupportRemoteWakeUp = 0;

	pmem_start = pci_resource_start(pdev, 1);
	pmem_len = pci_resource_len(pdev, 1);
	pmem_flags = pci_resource_flags(pdev, 1);

	अगर (!(pmem_flags & IORESOURCE_MEM)) अणु
		netdev_err(dev, "region #1 not a MMIO resource, aborting");
		जाओ err_rel_rtllib;
	पूर्ण

	dev_info(&pdev->dev, "Memory mapped space start: 0x%08lx\n",
		 pmem_start);
	अगर (!request_mem_region(pmem_start, pmem_len, DRV_NAME)) अणु
		netdev_err(dev, "request_mem_region failed!");
		जाओ err_rel_rtllib;
	पूर्ण


	ioaddr = (अचिन्हित दीर्घ)ioremap(pmem_start, pmem_len);
	अगर (ioaddr == (अचिन्हित दीर्घ)शून्य) अणु
		netdev_err(dev, "ioremap failed!");
		जाओ err_rel_mem;
	पूर्ण

	dev->mem_start = ioaddr;
	dev->mem_end = ioaddr + pci_resource_len(pdev, 0);

	pci_पढ़ो_config_byte(pdev, 0x08, &revision_id);
	/* If the revisionid is 0x10, the device uses rtl8192se. */
	अगर (pdev->device == 0x8192 && revision_id == 0x10)
		जाओ err_unmap;

	priv->ops = ops;

	अगर (!rtl92e_check_adapter(pdev, dev))
		जाओ err_unmap;

	dev->irq = pdev->irq;
	priv->irq = 0;

	dev->netdev_ops = &rtl8192_netdev_ops;

	dev->wireless_handlers = &r8192_wx_handlers_def;
	dev->ethtool_ops = &rtl819x_ethtool_ops;

	dev->type = ARPHRD_ETHER;
	dev->watchकरोg_समयo = HZ * 3;

	अगर (dev_alloc_name(dev, अगरname) < 0) अणु
		RT_TRACE(COMP_INIT,
			 "Oops: devname already taken! Trying wlan%%d...\n");
		dev_alloc_name(dev, अगरname);
	पूर्ण

	RT_TRACE(COMP_INIT, "Driver probe completed1\n");
	अगर (_rtl92e_init(dev) != 0) अणु
		netdev_warn(dev, "Initialization failed");
		जाओ err_मुक्त_irq;
	पूर्ण

	netअगर_carrier_off(dev);
	netअगर_stop_queue(dev);

	अगर (रेजिस्टर_netdev(dev))
		जाओ err_मुक्त_irq;
	RT_TRACE(COMP_INIT, "dev name: %s\n", dev->name);

	अगर (priv->polling_समयr_on == 0)
		rtl92e_check_rfctrl_gpio_समयr(&priv->gpio_polling_समयr);

	RT_TRACE(COMP_INIT, "Driver probe completed\n");
	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
	priv->irq = 0;
err_unmap:
	iounmap((व्योम __iomem *)ioaddr);
err_rel_mem:
	release_mem_region(pmem_start, pmem_len);
err_rel_rtllib:
	मुक्त_rtllib(dev);
err_pci_disable:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

अटल व्योम _rtl92e_pci_disconnect(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा r8192_priv *priv;
	u32 i;

	अगर (dev) अणु
		unरेजिस्टर_netdev(dev);

		priv = rtllib_priv(dev);

		del_समयr_sync(&priv->gpio_polling_समयr);
		cancel_delayed_work_sync(&priv->gpio_change_rf_wq);
		priv->polling_समयr_on = 0;
		_rtl92e_करोwn(dev, true);
		rtl92e_dm_deinit(dev);
		vमुक्त(priv->pFirmware);
		priv->pFirmware = शून्य;
		_rtl92e_मुक्त_rx_ring(dev);
		क्रम (i = 0; i < MAX_TX_QUEUE_COUNT; i++)
			_rtl92e_मुक्त_tx_ring(dev, i);

		अगर (priv->irq) अणु
			dev_info(&pdev->dev, "Freeing irq %d\n", dev->irq);
			मुक्त_irq(dev->irq, dev);
			priv->irq = 0;
		पूर्ण
		मुक्त_rtllib(dev);

		अगर (dev->mem_start != 0) अणु
			iounmap((व्योम __iomem *)dev->mem_start);
			release_mem_region(pci_resource_start(pdev, 1),
					pci_resource_len(pdev, 1));
		पूर्ण
	पूर्ण अन्यथा अणु
		priv = rtllib_priv(dev);
	पूर्ण

	pci_disable_device(pdev);
	RT_TRACE(COMP_DOWN, "wlan driver removed\n");
पूर्ण

bool rtl92e_enable_nic(काष्ठा net_device *dev)
अणु
	bool init_status = true;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					(&priv->rtllib->PowerSaveControl);

	अगर (!priv->up) अणु
		netdev_warn(dev, "%s(): Driver is already down!\n", __func__);
		priv->bdisable_nic = false;
		वापस false;
	पूर्ण

	RT_TRACE(COMP_PS, "===========>%s()\n", __func__);
	priv->bfirst_init = true;
	init_status = priv->ops->initialize_adapter(dev);
	अगर (!init_status) अणु
		netdev_warn(dev, "%s(): Initialization failed!\n", __func__);
		priv->bdisable_nic = false;
		वापस false;
	पूर्ण
	RT_TRACE(COMP_INIT, "start adapter finished\n");
	RT_CLEAR_PS_LEVEL(pPSC, RT_RF_OFF_LEVL_HALT_NIC);
	priv->bfirst_init = false;

	rtl92e_irq_enable(dev);
	priv->bdisable_nic = false;
	RT_TRACE(COMP_PS, "<===========%s()\n", __func__);
	वापस init_status;
पूर्ण

bool rtl92e_disable_nic(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 पंचांगp_state = 0;

	RT_TRACE(COMP_PS, "=========>%s()\n", __func__);
	priv->bdisable_nic = true;
	पंचांगp_state = priv->rtllib->state;
	rtllib_sofपंचांगac_stop_protocol(priv->rtllib, 0, false);
	priv->rtllib->state = पंचांगp_state;
	_rtl92e_cancel_deferred_work(priv);
	rtl92e_irq_disable(dev);

	priv->ops->stop_adapter(dev, false);
	RT_TRACE(COMP_PS, "<=========%s()\n", __func__);

	वापस true;
पूर्ण

module_pci_driver(rtl8192_pci_driver);

व्योम rtl92e_check_rfctrl_gpio_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा r8192_priv *priv = from_समयr(priv, t, gpio_polling_समयr);

	priv->polling_समयr_on = 1;

	schedule_delayed_work(&priv->gpio_change_rf_wq, 0);

	mod_समयr(&priv->gpio_polling_समयr, jअगरfies +
		  msecs_to_jअगरfies(RTLLIB_WATCH_DOG_TIME));
पूर्ण

/***************************************************************************
 * ------------------- module init / निकास stubs ----------------
 ***************************************************************************/
MODULE_DESCRIPTION("Linux driver for Realtek RTL819x WiFi cards");
MODULE_AUTHOR(DRV_COPYRIGHT " " DRV_AUTHOR);
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(RTL8192E_BOOT_IMG_FW);
MODULE_FIRMWARE(RTL8192E_MAIN_IMG_FW);
MODULE_FIRMWARE(RTL8192E_DATA_IMG_FW);

module_param(अगरname, अक्षरp, 0644);
module_param(hwwep, पूर्णांक, 0644);
module_param(channels, पूर्णांक, 0644);

MODULE_PARM_DESC(अगरname, " Net interface name, wlan%d=default");
MODULE_PARM_DESC(hwwep, " Try to use hardware WEP support(default use hw. set 0 to use software security)");
MODULE_PARM_DESC(channels, " Channel bitmask for specific locales. NYI");
