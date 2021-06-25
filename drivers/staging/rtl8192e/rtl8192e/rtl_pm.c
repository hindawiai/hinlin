<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtl_core.h"
#समावेश "r8192E_hw.h"
#समावेश "r8190P_rtl8256.h"
#समावेश "rtl_pm.h"


पूर्णांक rtl92e_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32	ulRegRead;

	netdev_info(dev, "============> r8192E suspend call.\n");
	del_समयr_sync(&priv->gpio_polling_समयr);
	cancel_delayed_work_sync(&priv->gpio_change_rf_wq);
	priv->polling_समयr_on = 0;

	अगर (!netअगर_running(dev)) अणु
		netdev_info(dev,
			    "RTL819XE:UI is open out of suspend function\n");
		जाओ out_pci_suspend;
	पूर्ण

	अगर (dev->netdev_ops->nकरो_stop)
		dev->netdev_ops->nकरो_stop(dev);
	netअगर_device_detach(dev);

	अगर (!priv->rtllib->bSupportRemoteWakeUp) अणु
		rtl92e_set_rf_state(dev, eRfOff, RF_CHANGE_BY_INIT);
		ulRegRead = rtl92e_पढ़ोl(dev, CPU_GEN);
		ulRegRead |= CPU_GEN_SYSTEM_RESET;
		rtl92e_ग_लिखोl(dev, CPU_GEN, ulRegRead);
	पूर्ण अन्यथा अणु
		rtl92e_ग_लिखोl(dev, WFCRC0, 0xffffffff);
		rtl92e_ग_लिखोl(dev, WFCRC1, 0xffffffff);
		rtl92e_ग_लिखोl(dev, WFCRC2, 0xffffffff);
		rtl92e_ग_लिखोb(dev, PMR, 0x5);
		rtl92e_ग_लिखोb(dev, MacBlkCtrl, 0xa);
	पूर्ण
out_pci_suspend:
	netdev_info(dev, "WOL is %s\n", priv->rtllib->bSupportRemoteWakeUp ?
			    "Supported" : "Not supported");
	device_set_wakeup_enable(dev_d, priv->rtllib->bSupportRemoteWakeUp);

	mdelay(20);

	वापस 0;
पूर्ण

पूर्णांक rtl92e_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 val;

	netdev_info(dev, "================>r8192E resume call.\n");


	pci_पढ़ो_config_dword(pdev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(pdev, 0x40, val & 0xffff00ff);

	device_wakeup_disable(dev_d);

	अगर (priv->polling_समयr_on == 0)
		rtl92e_check_rfctrl_gpio_समयr(&priv->gpio_polling_समयr);

	अगर (!netअगर_running(dev)) अणु
		netdev_info(dev,
			    "RTL819XE:UI is open out of resume function\n");
		जाओ out;
	पूर्ण

	netअगर_device_attach(dev);
	अगर (dev->netdev_ops->nकरो_खोलो)
		dev->netdev_ops->nकरो_खोलो(dev);

	अगर (!priv->rtllib->bSupportRemoteWakeUp)
		rtl92e_set_rf_state(dev, eRfOn, RF_CHANGE_BY_INIT);

out:
	RT_TRACE(COMP_POWER, "<================r8192E resume call.\n");
	वापस 0;
पूर्ण

