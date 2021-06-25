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
#समावेश "rtl_ps.h"
#समावेश "rtl_core.h"
#समावेश "r8192E_phy.h"
#समावेश "r8192E_phyreg.h"
#समावेश "r8190P_rtl8256.h" /* RTL8225 Radio frontend */
#समावेश "r8192E_cmdpkt.h"
#समावेश <linux/jअगरfies.h>

अटल व्योम _rtl92e_hw_sleep(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&priv->rf_ps_lock, flags);
	अगर (priv->RFChangeInProgress) अणु
		spin_unlock_irqrestore(&priv->rf_ps_lock, flags);
		RT_TRACE(COMP_DBG,
			 "%s(): RF Change in progress!\n", __func__);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&priv->rf_ps_lock, flags);
	RT_TRACE(COMP_DBG, "%s()============>come to sleep down\n", __func__);

	rtl92e_set_rf_state(dev, eRfSleep, RF_CHANGE_BY_PS);
पूर्ण

व्योम rtl92e_hw_sleep_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = container_of_dwork_rsl(data,
				     काष्ठा rtllib_device, hw_sleep_wq);
	काष्ठा net_device *dev = ieee->dev;

	_rtl92e_hw_sleep(dev);
पूर्ण

व्योम rtl92e_hw_wakeup(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&priv->rf_ps_lock, flags);
	अगर (priv->RFChangeInProgress) अणु
		spin_unlock_irqrestore(&priv->rf_ps_lock, flags);
		RT_TRACE(COMP_DBG,
			 "%s(): RF Change in progress!\n", __func__);
		schedule_delayed_work(&priv->rtllib->hw_wakeup_wq,
				      msecs_to_jअगरfies(10));
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&priv->rf_ps_lock, flags);
	RT_TRACE(COMP_PS, "%s()============>come to wake up\n", __func__);
	rtl92e_set_rf_state(dev, eRfOn, RF_CHANGE_BY_PS);
पूर्ण

व्योम rtl92e_hw_wakeup_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = container_of_dwork_rsl(data,
				     काष्ठा rtllib_device, hw_wakeup_wq);
	काष्ठा net_device *dev = ieee->dev;

	rtl92e_hw_wakeup(dev);
पूर्ण

#घोषणा MIN_SLEEP_TIME 50
#घोषणा MAX_SLEEP_TIME 10000
व्योम rtl92e_enter_sleep(काष्ठा net_device *dev, u64 समय)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	u32 पंचांगp;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समयout;

	spin_lock_irqsave(&priv->ps_lock, flags);

	समय -= msecs_to_jअगरfies(8 + 16 + 7);

	समयout = jअगरfies + msecs_to_jअगरfies(MIN_SLEEP_TIME);
	अगर (समय_beक्रमe((अचिन्हित दीर्घ)समय, समयout)) अणु
		spin_unlock_irqrestore(&priv->ps_lock, flags);
		netdev_info(dev, "too short to sleep::%lld < %ld\n",
			    समय - jअगरfies, msecs_to_jअगरfies(MIN_SLEEP_TIME));
		वापस;
	पूर्ण
	समयout = jअगरfies + msecs_to_jअगरfies(MAX_SLEEP_TIME);
	अगर (समय_after((अचिन्हित दीर्घ)समय, समयout)) अणु
		netdev_info(dev, "========>too long to sleep:%lld > %ld\n",
			    समय - jअगरfies, msecs_to_jअगरfies(MAX_SLEEP_TIME));
		spin_unlock_irqrestore(&priv->ps_lock, flags);
		वापस;
	पूर्ण
	पंचांगp = समय - jअगरfies;
	schedule_delayed_work(&priv->rtllib->hw_wakeup_wq, पंचांगp);
	schedule_delayed_work(&priv->rtllib->hw_sleep_wq, 0);
	spin_unlock_irqrestore(&priv->ps_lock, flags);
पूर्ण

अटल व्योम _rtl92e_ps_update_rf_state(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					&(priv->rtllib->PowerSaveControl);

	RT_TRACE(COMP_PS, "%s() --------->\n", __func__);
	pPSC->bSwRfProcessing = true;

	RT_TRACE(COMP_PS, "%s(): Set RF to %s.\n", __func__,
		 pPSC->eInactivePowerState == eRfOff ? "OFF" : "ON");
	rtl92e_set_rf_state(dev, pPSC->eInactivePowerState, RF_CHANGE_BY_IPS);

	pPSC->bSwRfProcessing = false;
	RT_TRACE(COMP_PS, "%s() <---------\n", __func__);
पूर्ण

व्योम rtl92e_ips_enter(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					&(priv->rtllib->PowerSaveControl);
	क्रमागत rt_rf_घातer_state rtState;

	अगर (pPSC->bInactivePs) अणु
		rtState = priv->rtllib->eRFPowerState;
		अगर (rtState == eRfOn && !pPSC->bSwRfProcessing &&
			(priv->rtllib->state != RTLLIB_LINKED) &&
			(priv->rtllib->iw_mode != IW_MODE_MASTER)) अणु
			RT_TRACE(COMP_PS, "%s(): Turn off RF.\n", __func__);
			pPSC->eInactivePowerState = eRfOff;
			priv->isRFOff = true;
			priv->bInPowerSaveMode = true;
			_rtl92e_ps_update_rf_state(dev);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92e_ips_leave(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					&(priv->rtllib->PowerSaveControl);
	क्रमागत rt_rf_घातer_state rtState;

	अगर (pPSC->bInactivePs) अणु
		rtState = priv->rtllib->eRFPowerState;
		अगर (rtState != eRfOn  && !pPSC->bSwRfProcessing &&
		    priv->rtllib->RfOffReason <= RF_CHANGE_BY_IPS) अणु
			RT_TRACE(COMP_PS, "%s(): Turn on RF.\n", __func__);
			pPSC->eInactivePowerState = eRfOn;
			priv->bInPowerSaveMode = false;
			_rtl92e_ps_update_rf_state(dev);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92e_ips_leave_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = container_of_work_rsl(data,
				     काष्ठा rtllib_device, ips_leave_wq);
	काष्ठा net_device *dev = ieee->dev;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);

	mutex_lock(&priv->rtllib->ips_mutex);
	rtl92e_ips_leave(dev);
	mutex_unlock(&priv->rtllib->ips_mutex);
पूर्ण

व्योम rtl92e_rtllib_ips_leave_wq(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);
	क्रमागत rt_rf_घातer_state rtState;

	rtState = priv->rtllib->eRFPowerState;

	अगर (priv->rtllib->PowerSaveControl.bInactivePs) अणु
		अगर (rtState == eRfOff) अणु
			अगर (priv->rtllib->RfOffReason > RF_CHANGE_BY_IPS) अणु
				netdev_warn(dev, "%s(): RF is OFF.\n",
					    __func__);
				वापस;
			पूर्ण
			netdev_info(dev, "=========>%s(): rtl92e_ips_leave\n",
				    __func__);
			schedule_work(&priv->rtllib->ips_leave_wq);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92e_rtllib_ips_leave(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);

	mutex_lock(&priv->rtllib->ips_mutex);
	rtl92e_ips_leave(dev);
	mutex_unlock(&priv->rtllib->ips_mutex);
पूर्ण

अटल bool _rtl92e_ps_set_mode(काष्ठा net_device *dev, u8 rtPsMode)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->rtllib->iw_mode == IW_MODE_ADHOC)
		वापस false;

	RT_TRACE(COMP_LPS, "%s(): set ieee->ps = %x\n", __func__, rtPsMode);
	अगर (!priv->ps_क्रमce)
		priv->rtllib->ps = rtPsMode;
	अगर (priv->rtllib->sta_sleep != LPS_IS_WAKE &&
	    rtPsMode == RTLLIB_PS_DISABLED) अणु
		अचिन्हित दीर्घ flags;

		rtl92e_hw_wakeup(dev);
		priv->rtllib->sta_sleep = LPS_IS_WAKE;

		spin_lock_irqsave(&(priv->rtllib->mgmt_tx_lock), flags);
		RT_TRACE(COMP_DBG,
			 "LPS leave: notify AP we are awaked ++++++++++ SendNullFunctionData\n");
		rtllib_sta_ps_send_null_frame(priv->rtllib, 0);
		spin_unlock_irqrestore(&(priv->rtllib->mgmt_tx_lock), flags);
	पूर्ण

	वापस true;
पूर्ण

व्योम rtl92e_leisure_ps_enter(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					&(priv->rtllib->PowerSaveControl);

	RT_TRACE(COMP_PS, "%s()...\n", __func__);
	RT_TRACE(COMP_PS,
		 "pPSC->bLeisurePs = %d, ieee->ps = %d,pPSC->LpsIdleCount is %d,RT_CHECK_FOR_HANG_PERIOD is %d\n",
		 pPSC->bLeisurePs, priv->rtllib->ps, pPSC->LpsIdleCount,
		 RT_CHECK_FOR_HANG_PERIOD);

	अगर (!((priv->rtllib->iw_mode == IW_MODE_INFRA) &&
	    (priv->rtllib->state == RTLLIB_LINKED))
	    || (priv->rtllib->iw_mode == IW_MODE_ADHOC) ||
	    (priv->rtllib->iw_mode == IW_MODE_MASTER))
		वापस;

	अगर (pPSC->bLeisurePs) अणु
		अगर (pPSC->LpsIdleCount >= RT_CHECK_FOR_HANG_PERIOD) अणु

			अगर (priv->rtllib->ps == RTLLIB_PS_DISABLED) अणु

				RT_TRACE(COMP_LPS,
					 "%s(): Enter 802.11 power save mode...\n", __func__);

				अगर (!pPSC->bFwCtrlLPS) अणु
					अगर (priv->rtllib->SetFwCmdHandler)
						priv->rtllib->SetFwCmdHandler(
							dev, FW_CMD_LPS_ENTER);
				पूर्ण
				_rtl92e_ps_set_mode(dev, RTLLIB_PS_MBCAST |
							 RTLLIB_PS_UNICAST);
			पूर्ण
		पूर्ण अन्यथा
			pPSC->LpsIdleCount++;
	पूर्ण
पूर्ण

व्योम rtl92e_leisure_ps_leave(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					&(priv->rtllib->PowerSaveControl);


	RT_TRACE(COMP_PS, "%s()...\n", __func__);
	RT_TRACE(COMP_PS, "pPSC->bLeisurePs = %d, ieee->ps = %d\n",
		pPSC->bLeisurePs, priv->rtllib->ps);

	अगर (pPSC->bLeisurePs) अणु
		अगर (priv->rtllib->ps != RTLLIB_PS_DISABLED) अणु
			RT_TRACE(COMP_LPS,
				 "%s(): Busy Traffic , Leave 802.11 power save..\n", __func__);
			_rtl92e_ps_set_mode(dev, RTLLIB_PS_DISABLED);

			अगर (!pPSC->bFwCtrlLPS) अणु
				अगर (priv->rtllib->SetFwCmdHandler)
					priv->rtllib->SetFwCmdHandler(dev,
							 FW_CMD_LPS_LEAVE);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
