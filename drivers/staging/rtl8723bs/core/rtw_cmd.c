<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_CMD_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_btcoex.h>
#समावेश <linux/jअगरfies.h>

अटल काष्ठा _cmd_callback rtw_cmd_callback[] = अणु
	अणुGEN_CMD_CODE(_Read_MACREG), शून्यपूर्ण, /*0*/
	अणुGEN_CMD_CODE(_Write_MACREG), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Read_BBREG), &rtw_getbbrfreg_cmdrsp_callbackपूर्ण,
	अणुGEN_CMD_CODE(_Write_BBREG), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Read_RFREG), &rtw_getbbrfreg_cmdrsp_callbackपूर्ण,
	अणुGEN_CMD_CODE(_Write_RFREG), शून्यपूर्ण, /*5*/
	अणुGEN_CMD_CODE(_Read_EEPROM), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Write_EEPROM), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Read_EFUSE), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Write_EFUSE), शून्यपूर्ण,

	अणुGEN_CMD_CODE(_Read_CAM),	शून्यपूर्ण,	/*10*/
	अणुGEN_CMD_CODE(_Write_CAM),	 शून्यपूर्ण,
	अणुGEN_CMD_CODE(_setBCNITV), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_setMBIDCFG), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_JoinBss), &rtw_joinbss_cmd_callbackपूर्ण,  /*14*/
	अणुGEN_CMD_CODE(_DisConnect), &rtw_disassoc_cmd_callbackपूर्ण, /*15*/
	अणुGEN_CMD_CODE(_CreateBss), &rtw_createbss_cmd_callbackपूर्ण,
	अणुGEN_CMD_CODE(_SetOpMode), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SiteSurvey), &rtw_survey_cmd_callbackपूर्ण, /*18*/
	अणुGEN_CMD_CODE(_SetAuth), शून्यपूर्ण,

	अणुGEN_CMD_CODE(_SetKey), शून्यपूर्ण,	/*20*/
	अणुGEN_CMD_CODE(_SetStaKey), &rtw_setstaKey_cmdrsp_callbackपूर्ण,
	अणुGEN_CMD_CODE(_SetAssocSta), &rtw_setassocsta_cmdrsp_callbackपूर्ण,
	अणुGEN_CMD_CODE(_DelAssocSta), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetStaPwrState), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetBasicRate), शून्यपूर्ण, /*25*/
	अणुGEN_CMD_CODE(_GetBasicRate), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetDataRate), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_GetDataRate), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetPhyInfo), शून्यपूर्ण,

	अणुGEN_CMD_CODE(_GetPhyInfo), शून्यपूर्ण, /*30*/
	अणुGEN_CMD_CODE(_SetPhy), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_GetPhy), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_पढ़ोRssi), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_पढ़ोGain), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetAtim), शून्यपूर्ण, /*35*/
	अणुGEN_CMD_CODE(_SetPwrMode), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_JoinbssRpt), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetRaTable), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_GetRaTable), शून्यपूर्ण,

	अणुGEN_CMD_CODE(_GetCCXReport), शून्यपूर्ण, /*40*/
	अणुGEN_CMD_CODE(_GetDTMReport),	शून्यपूर्ण,
	अणुGEN_CMD_CODE(_GetTXRateStatistics), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetUsbSuspend), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetH2cLbk), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_AddBAReq), शून्यपूर्ण, /*45*/
	अणुGEN_CMD_CODE(_SetChannel), शून्यपूर्ण,		/*46*/
	अणुGEN_CMD_CODE(_SetTxPower), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SwitchAntenna), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetCrystalCap), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetSingleCarrierTx), शून्यपूर्ण,	/*50*/

	अणुGEN_CMD_CODE(_SetSingleToneTx), शून्यपूर्ण, /*51*/
	अणुGEN_CMD_CODE(_SetCarrierSuppressionTx), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetContinuousTx), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SwitchBandwidth), शून्यपूर्ण,		/*54*/
	अणुGEN_CMD_CODE(_TX_Beacon), शून्यपूर्ण,/*55*/

	अणुGEN_CMD_CODE(_Set_MLME_EVT), शून्यपूर्ण,/*56*/
	अणुGEN_CMD_CODE(_Set_Drv_Extra), शून्यपूर्ण,/*57*/
	अणुGEN_CMD_CODE(_Set_H2C_MSG), शून्यपूर्ण,/*58*/
	अणुGEN_CMD_CODE(_SetChannelPlan), शून्यपूर्ण,/*59*/

	अणुGEN_CMD_CODE(_SetChannelSwitch), शून्यपूर्ण,/*60*/
	अणुGEN_CMD_CODE(_TDLS), शून्यपूर्ण,/*61*/
	अणुGEN_CMD_CODE(_ChkBMCSleepq), शून्यपूर्ण, /*62*/

	अणुGEN_CMD_CODE(_RunInThपढ़ोCMD), शून्यपूर्ण,/*63*/
पूर्ण;

अटल काष्ठा cmd_hdl wlancmds[] = अणु
	GEN_DRV_CMD_HANDLER(0, शून्य) /*0*/
	GEN_DRV_CMD_HANDLER(0, शून्य)
	GEN_DRV_CMD_HANDLER(0, शून्य)
	GEN_DRV_CMD_HANDLER(0, शून्य)
	GEN_DRV_CMD_HANDLER(0, शून्य)
	GEN_DRV_CMD_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य) /*10*/
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा joinbss_parm), join_cmd_hdl) /*14*/
	GEN_MLME_EXT_HANDLER(माप(काष्ठा disconnect_parm), disconnect_hdl)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा createbss_parm), createbss_hdl)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा setopmode_parm), setopmode_hdl)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा sitesurvey_parm), sitesurvey_cmd_hdl) /*18*/
	GEN_MLME_EXT_HANDLER(माप(काष्ठा setauth_parm), setauth_hdl)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा setkey_parm), setkey_hdl) /*20*/
	GEN_MLME_EXT_HANDLER(माप(काष्ठा set_stakey_parm), set_stakey_hdl)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा set_assocsta_parm), शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा del_assocsta_parm), शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा setstapwrstate_parm), शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा setbasicrate_parm), शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा getbasicrate_parm), शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा setdatarate_parm), शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा getdatarate_parm), शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा setphyinfo_parm), शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा getphyinfo_parm), शून्य)  /*30*/
	GEN_MLME_EXT_HANDLER(माप(काष्ठा setphy_parm), शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा getphy_parm), शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)	/*40*/
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा addBaReq_parm), add_ba_hdl)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा set_ch_parm), set_ch_hdl) /* 46 */
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य) /*50*/
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(0, शून्य)
	GEN_MLME_EXT_HANDLER(माप(काष्ठा Tx_Beacon_param), tx_beacon_hdl) /*55*/

	GEN_MLME_EXT_HANDLER(0, mlme_evt_hdl) /*56*/
	GEN_MLME_EXT_HANDLER(0, rtw_drvextra_cmd_hdl) /*57*/

	GEN_MLME_EXT_HANDLER(0, h2c_msg_hdl) /*58*/
	GEN_MLME_EXT_HANDLER(माप(काष्ठा SetChannelPlan_param), set_chplan_hdl) /*59*/

	GEN_MLME_EXT_HANDLER(माप(काष्ठा SetChannelSwitch_param), set_csa_hdl) /*60*/
	GEN_MLME_EXT_HANDLER(माप(काष्ठा TDLSoption_param), tdls_hdl) /*61*/
	GEN_MLME_EXT_HANDLER(0, chk_bmc_sleepq_hdl) /*62*/
	GEN_MLME_EXT_HANDLER(माप(काष्ठा RunInThपढ़ो_param), run_in_thपढ़ो_hdl) /*63*/
पूर्ण;

/*
Caller and the rtw_cmd_thपढ़ो can protect cmd_q by spin_lock.
No irqsave is necessary.
*/

पूर्णांक rtw_init_cmd_priv(काष्ठा	cmd_priv *pcmdpriv)
अणु
	पूर्णांक res = 0;

	init_completion(&pcmdpriv->cmd_queue_comp);
	init_completion(&pcmdpriv->terminate_cmdthपढ़ो_comp);

	_rtw_init_queue(&(pcmdpriv->cmd_queue));

	/* allocate DMA-able/Non-Page memory क्रम cmd_buf and rsp_buf */

	pcmdpriv->cmd_seq = 1;

	pcmdpriv->cmd_allocated_buf = rtw_zदो_स्मृति(MAX_CMDSZ + CMDBUFF_ALIGN_SZ);

	अगर (!pcmdpriv->cmd_allocated_buf) अणु
		res = -ENOMEM;
		जाओ निकास;
	पूर्ण

	pcmdpriv->cmd_buf = pcmdpriv->cmd_allocated_buf  +  CMDBUFF_ALIGN_SZ - ((SIZE_PTR)(pcmdpriv->cmd_allocated_buf) & (CMDBUFF_ALIGN_SZ-1));

	pcmdpriv->rsp_allocated_buf = rtw_zदो_स्मृति(MAX_RSPSZ + 4);

	अगर (!pcmdpriv->rsp_allocated_buf) अणु
		res = -ENOMEM;
		जाओ निकास;
	पूर्ण

	pcmdpriv->rsp_buf = pcmdpriv->rsp_allocated_buf  +  4 - ((SIZE_PTR)(pcmdpriv->rsp_allocated_buf) & 3);

	pcmdpriv->cmd_issued_cnt = 0;
	pcmdpriv->cmd_करोne_cnt = 0;
	pcmdpriv->rsp_cnt = 0;

	mutex_init(&pcmdpriv->sctx_mutex);
निकास:
	वापस res;
पूर्ण

अटल व्योम c2h_wk_callback(काष्ठा work_काष्ठा *work);
पूर्णांक rtw_init_evt_priv(काष्ठा evt_priv *pevtpriv)
अणु
	/* allocate DMA-able/Non-Page memory क्रम cmd_buf and rsp_buf */
	atomic_set(&pevtpriv->event_seq, 0);
	pevtpriv->evt_करोne_cnt = 0;

	_init_workitem(&pevtpriv->c2h_wk, c2h_wk_callback, शून्य);
	pevtpriv->c2h_wk_alive = false;
	pevtpriv->c2h_queue = rtw_cbuf_alloc(C2H_QUEUE_MAX_LEN+1);
	अगर (!pevtpriv->c2h_queue)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम _rtw_मुक्त_evt_priv(काष्ठा	evt_priv *pevtpriv)
अणु
	_cancel_workitem_sync(&pevtpriv->c2h_wk);
	जबतक (pevtpriv->c2h_wk_alive)
		msleep(10);

	जबतक (!rtw_cbuf_empty(pevtpriv->c2h_queue)) अणु
		व्योम *c2h = rtw_cbuf_pop(pevtpriv->c2h_queue);
		अगर (c2h && c2h != (व्योम *)pevtpriv)
			kमुक्त(c2h);
	पूर्ण
	kमुक्त(pevtpriv->c2h_queue);
पूर्ण

व्योम _rtw_मुक्त_cmd_priv(काष्ठा	cmd_priv *pcmdpriv)
अणु
	अगर (pcmdpriv) अणु
		kमुक्त(pcmdpriv->cmd_allocated_buf);

		kमुक्त(pcmdpriv->rsp_allocated_buf);

		mutex_destroy(&pcmdpriv->sctx_mutex);
	पूर्ण
पूर्ण

/*
Calling Context:

rtw_enqueue_cmd can only be called between kernel thपढ़ो,
since only spin_lock is used.

ISR/Call-Back functions can't call this sub-function.

*/

पूर्णांक _rtw_enqueue_cmd(काष्ठा __queue *queue, काष्ठा cmd_obj *obj)
अणु
	अचिन्हित दीर्घ irqL;

	अगर (obj == शून्य)
		जाओ निकास;

	/* spin_lock_bh(&queue->lock); */
	spin_lock_irqsave(&queue->lock, irqL);

	list_add_tail(&obj->list, &queue->queue);

	/* spin_unlock_bh(&queue->lock); */
	spin_unlock_irqrestore(&queue->lock, irqL);

निकास:
	वापस _SUCCESS;
पूर्ण

काष्ठा	cmd_obj	*_rtw_dequeue_cmd(काष्ठा __queue *queue)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा cmd_obj *obj;

	/* spin_lock_bh(&(queue->lock)); */
	spin_lock_irqsave(&queue->lock, irqL);
	अगर (list_empty(&(queue->queue)))
		obj = शून्य;
	अन्यथा अणु
		obj = container_of(get_next(&(queue->queue)), काष्ठा cmd_obj, list);
		list_del_init(&obj->list);
	पूर्ण

	/* spin_unlock_bh(&(queue->lock)); */
	spin_unlock_irqrestore(&queue->lock, irqL);

	वापस obj;
पूर्ण

व्योम rtw_मुक्त_evt_priv(काष्ठा	evt_priv *pevtpriv)
अणु
	_rtw_मुक्त_evt_priv(pevtpriv);
पूर्ण

व्योम rtw_मुक्त_cmd_priv(काष्ठा	cmd_priv *pcmdpriv)
अणु
	_rtw_मुक्त_cmd_priv(pcmdpriv);
पूर्ण

पूर्णांक rtw_cmd_filter(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *cmd_obj);
पूर्णांक rtw_cmd_filter(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *cmd_obj)
अणु
	u8 bAllow = false; /* set to true to allow enqueuing cmd when hw_init_completed is false */

	अगर (cmd_obj->cmdcode == GEN_CMD_CODE(_SetChannelPlan))
		bAllow = true;

	अगर ((pcmdpriv->padapter->hw_init_completed == false && bAllow == false)
		|| atomic_पढ़ो(&(pcmdpriv->cmdthd_running)) == false	/* com_thपढ़ो not running */
	)
		वापस _FAIL;

	वापस _SUCCESS;
पूर्ण



पूर्णांक rtw_enqueue_cmd(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *cmd_obj)
अणु
	पूर्णांक res = _FAIL;
	काष्ठा adapter *padapter = pcmdpriv->padapter;

	अगर (cmd_obj == शून्य)
		जाओ निकास;

	cmd_obj->padapter = padapter;

	res = rtw_cmd_filter(pcmdpriv, cmd_obj);
	अगर (res == _FAIL) अणु
		rtw_मुक्त_cmd_obj(cmd_obj);
		जाओ निकास;
	पूर्ण

	res = _rtw_enqueue_cmd(&pcmdpriv->cmd_queue, cmd_obj);

	अगर (res == _SUCCESS)
		complete(&pcmdpriv->cmd_queue_comp);

निकास:
	वापस res;
पूर्ण

काष्ठा	cmd_obj	*rtw_dequeue_cmd(काष्ठा cmd_priv *pcmdpriv)
अणु
	वापस _rtw_dequeue_cmd(&pcmdpriv->cmd_queue);
पूर्ण

व्योम rtw_मुक्त_cmd_obj(काष्ठा cmd_obj *pcmd)
अणु
	अगर ((pcmd->cmdcode != _JoinBss_CMD_) &&
	    (pcmd->cmdcode != _CreateBss_CMD_)) अणु
		/* मुक्त parmbuf in cmd_obj */
		kमुक्त(pcmd->parmbuf);
	पूर्ण

	अगर (pcmd->rsp) अणु
		अगर (pcmd->rspsz != 0) अणु
			/* मुक्त rsp in cmd_obj */
			kमुक्त(pcmd->rsp);
		पूर्ण
	पूर्ण

	/* मुक्त cmd_obj */
	kमुक्त(pcmd);
पूर्ण


व्योम rtw_stop_cmd_thपढ़ो(काष्ठा adapter *adapter)
अणु
	अगर (adapter->cmdThपढ़ो &&
		atomic_पढ़ो(&(adapter->cmdpriv.cmdthd_running)) == true &&
		adapter->cmdpriv.stop_req == 0) अणु
		adapter->cmdpriv.stop_req = 1;
		complete(&adapter->cmdpriv.cmd_queue_comp);
		रुको_क्रम_completion(&adapter->cmdpriv.terminate_cmdthपढ़ो_comp);
	पूर्ण
पूर्ण

पूर्णांक rtw_cmd_thपढ़ो(व्योम *context)
अणु
	u8 ret;
	काष्ठा cmd_obj *pcmd;
	u8 *pcmdbuf;
	u8 (*cmd_hdl)(काष्ठा adapter *padapter, u8 *pbuf);
	व्योम (*pcmd_callback)(काष्ठा adapter *dev, काष्ठा cmd_obj *pcmd);
	काष्ठा adapter *padapter = context;
	काष्ठा cmd_priv *pcmdpriv = &(padapter->cmdpriv);
	काष्ठा drvextra_cmd_parm *extra_parm = शून्य;

	thपढ़ो_enter("RTW_CMD_THREAD");

	pcmdbuf = pcmdpriv->cmd_buf;

	pcmdpriv->stop_req = 0;
	atomic_set(&(pcmdpriv->cmdthd_running), true);
	complete(&pcmdpriv->terminate_cmdthपढ़ो_comp);

	जबतक (1) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&pcmdpriv->cmd_queue_comp)) अणु
			netdev_dbg(padapter->pnetdev,
				   FUNC_ADPT_FMT " wait_for_completion_interruptible(&pcmdpriv->cmd_queue_comp) return != 0, break\n",
				   FUNC_ADPT_ARG(padapter));
			अवरोध;
		पूर्ण

		अगर ((padapter->bDriverStopped == true) || (padapter->bSurpriseRemoved == true)) अणु
			netdev_dbg(padapter->pnetdev,
				   "%s: DriverStopped(%d) SurpriseRemoved(%d) break at line %d\n",
				   __func__, padapter->bDriverStopped,
				   padapter->bSurpriseRemoved, __LINE__);
			अवरोध;
		पूर्ण

		अगर (pcmdpriv->stop_req) अणु
			netdev_dbg(padapter->pnetdev,
				   FUNC_ADPT_FMT " stop_req:%u, break\n",
				   FUNC_ADPT_ARG(padapter),
				   pcmdpriv->stop_req);
			अवरोध;
		पूर्ण

		अगर (list_empty(&pcmdpriv->cmd_queue.queue))
			जारी;

		अगर (rtw_रेजिस्टर_cmd_alive(padapter) != _SUCCESS)
			जारी;

_next:
		अगर ((padapter->bDriverStopped == true) || (padapter->bSurpriseRemoved == true)) अणु
			netdev_dbg(padapter->pnetdev,
				   "%s: DriverStopped(%d) SurpriseRemoved(%d) break at line %d\n",
				   __func__, padapter->bDriverStopped,
				   padapter->bSurpriseRemoved, __LINE__);
			अवरोध;
		पूर्ण

		pcmd = rtw_dequeue_cmd(pcmdpriv);
		अगर (!pcmd) अणु
			rtw_unरेजिस्टर_cmd_alive(padapter);
			जारी;
		पूर्ण

		अगर (rtw_cmd_filter(pcmdpriv, pcmd) == _FAIL) अणु
			pcmd->res = H2C_DROPPED;
			जाओ post_process;
		पूर्ण

		pcmdpriv->cmd_issued_cnt++;

		pcmd->cmdsz = round_up((pcmd->cmdsz), 4);

		स_नकल(pcmdbuf, pcmd->parmbuf, pcmd->cmdsz);

		अगर (pcmd->cmdcode < ARRAY_SIZE(wlancmds)) अणु
			cmd_hdl = wlancmds[pcmd->cmdcode].h2cfuns;

			अगर (cmd_hdl) अणु
				ret = cmd_hdl(pcmd->padapter, pcmdbuf);
				pcmd->res = ret;
			पूर्ण

			pcmdpriv->cmd_seq++;
		पूर्ण अन्यथा अणु
			pcmd->res = H2C_PARAMETERS_ERROR;
		पूर्ण

		cmd_hdl = शून्य;

post_process:

		अगर (mutex_lock_पूर्णांकerruptible(&(pcmd->padapter->cmdpriv.sctx_mutex)) == 0) अणु
			अगर (pcmd->sctx) अणु
				netdev_dbg(padapter->pnetdev,
					   FUNC_ADPT_FMT " pcmd->sctx\n",
					   FUNC_ADPT_ARG(pcmd->padapter));

				अगर (pcmd->res == H2C_SUCCESS)
					rtw_sctx_करोne(&pcmd->sctx);
				अन्यथा
					rtw_sctx_करोne_err(&pcmd->sctx, RTW_SCTX_DONE_CMD_ERROR);
			पूर्ण
			mutex_unlock(&(pcmd->padapter->cmdpriv.sctx_mutex));
		पूर्ण

		/* call callback function क्रम post-processed */
		अगर (pcmd->cmdcode < ARRAY_SIZE(rtw_cmd_callback)) अणु
			pcmd_callback = rtw_cmd_callback[pcmd->cmdcode].callback;
			अगर (pcmd_callback == शून्य) अणु
				rtw_मुक्त_cmd_obj(pcmd);
			पूर्ण अन्यथा अणु
				/* toकरो: !!! fill rsp_buf to pcmd->rsp अगर (pcmd->rsp!= शून्य) */
				pcmd_callback(pcmd->padapter, pcmd);/* need consider that मुक्त cmd_obj in rtw_cmd_callback */
			पूर्ण
		पूर्ण अन्यथा अणु
			rtw_मुक्त_cmd_obj(pcmd);
		पूर्ण

		flush_संकेतs_thपढ़ो();

		जाओ _next;

	पूर्ण

	/*  मुक्त all cmd_obj resources */
	करो अणु
		pcmd = rtw_dequeue_cmd(pcmdpriv);
		अगर (pcmd == शून्य) अणु
			rtw_unरेजिस्टर_cmd_alive(padapter);
			अवरोध;
		पूर्ण

		अगर (pcmd->cmdcode == GEN_CMD_CODE(_Set_Drv_Extra)) अणु
			extra_parm = (काष्ठा drvextra_cmd_parm *)pcmd->parmbuf;
			अगर (extra_parm->pbuf && extra_parm->size > 0)
				kमुक्त(extra_parm->pbuf);
		पूर्ण

		rtw_मुक्त_cmd_obj(pcmd);
	पूर्ण जबतक (1);

	complete(&pcmdpriv->terminate_cmdthपढ़ो_comp);
	atomic_set(&(pcmdpriv->cmdthd_running), false);

	thपढ़ो_निकास();
पूर्ण

/*
rtw_sitesurvey_cmd(~)
	### NOTE:#### (!!!!)
	MUST TAKE CARE THAT BEFORE CALLING THIS FUNC, YOU SHOULD HAVE LOCKED pmlmepriv->lock
*/
u8 rtw_sitesurvey_cmd(काष्ठा adapter  *padapter, काष्ठा ndis_802_11_ssid *ssid, पूर्णांक ssid_num,
	काष्ठा rtw_ieee80211_channel *ch, पूर्णांक ch_num)
अणु
	u8 res = _FAIL;
	काष्ठा cmd_obj		*ph2c;
	काष्ठा sitesurvey_parm	*psurveyPara;
	काष्ठा cmd_priv 	*pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true)
		rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_SCAN, 1);

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य)
		वापस _FAIL;

	psurveyPara = rtw_zदो_स्मृति(माप(काष्ठा sitesurvey_parm));
	अगर (psurveyPara == शून्य) अणु
		kमुक्त(ph2c);
		वापस _FAIL;
	पूर्ण

	rtw_मुक्त_network_queue(padapter, false);

	init_h2fwcmd_w_parm_no_rsp(ph2c, psurveyPara, GEN_CMD_CODE(_SiteSurvey));

	/* psurveyPara->bsslimit = 48; */
	psurveyPara->scan_mode = pmlmepriv->scan_mode;

	/* prepare ssid list */
	अगर (ssid) अणु
		पूर्णांक i;
		क्रम (i = 0; i < ssid_num && i < RTW_SSID_SCAN_AMOUNT; i++) अणु
			अगर (ssid[i].SsidLength) अणु
				स_नकल(&psurveyPara->ssid[i], &ssid[i], माप(काष्ठा ndis_802_11_ssid));
				psurveyPara->ssid_num++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* prepare channel list */
	अगर (ch) अणु
		पूर्णांक i;
		क्रम (i = 0; i < ch_num && i < RTW_CHANNEL_SCAN_AMOUNT; i++) अणु
			अगर (ch[i].hw_value && !(ch[i].flags & RTW_IEEE80211_CHAN_DISABLED)) अणु
				स_नकल(&psurveyPara->ch[i], &ch[i], माप(काष्ठा rtw_ieee80211_channel));
				psurveyPara->ch_num++;
			पूर्ण
		पूर्ण
	पूर्ण

	set_fwstate(pmlmepriv, _FW_UNDER_SURVEY);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

	अगर (res == _SUCCESS) अणु

		pmlmepriv->scan_start_समय = jअगरfies;
		_set_समयr(&pmlmepriv->scan_to_समयr, SCANNING_TIMEOUT);
	पूर्ण अन्यथा अणु
		_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	पूर्ण
	वापस res;
पूर्ण

u8 rtw_setdatarate_cmd(काष्ठा adapter *padapter, u8 *rateset)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा setdatarate_parm *pbsetdataratepara;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pbsetdataratepara = rtw_zदो_स्मृति(माप(काष्ठा setdatarate_parm));
	अगर (pbsetdataratepara == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	init_h2fwcmd_w_parm_no_rsp(ph2c, pbsetdataratepara, GEN_CMD_CODE(_SetDataRate));
	pbsetdataratepara->mac_id = 5;
	स_नकल(pbsetdataratepara->datarates, rateset, NumRates);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);
निकास:
	वापस res;
पूर्ण

व्योम rtw_getbbrfreg_cmdrsp_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	/* rtw_मुक्त_cmd_obj(pcmd); */
	kमुक्त(pcmd->parmbuf);
	kमुक्त(pcmd);
पूर्ण

u8 rtw_createbss_cmd(काष्ठा adapter  *padapter)
अणु
	काष्ठा cmd_obj *pcmd;
	काष्ठा cmd_priv 			*pcmdpriv = &padapter->cmdpriv;
	काष्ठा wlan_bssid_ex		*pdev_network = &padapter->registrypriv.dev_network;
	u8 res = _SUCCESS;

	pcmd = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (pcmd == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	INIT_LIST_HEAD(&pcmd->list);
	pcmd->cmdcode = _CreateBss_CMD_;
	pcmd->parmbuf = (अचिन्हित अक्षर *)pdev_network;
	pcmd->cmdsz = get_wlan_bssid_ex_sz((काष्ठा wlan_bssid_ex *)pdev_network);
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;

	pdev_network->Length = pcmd->cmdsz;

	res = rtw_enqueue_cmd(pcmdpriv, pcmd);

निकास:
	वापस res;
पूर्ण

पूर्णांक rtw_startbss_cmd(काष्ठा adapter  *padapter, पूर्णांक flags)
अणु
	काष्ठा cmd_obj *pcmd;
	काष्ठा cmd_priv  *pcmdpriv = &padapter->cmdpriv;
	काष्ठा submit_ctx sctx;
	पूर्णांक res = _SUCCESS;

	अगर (flags & RTW_CMDF_सूचीECTLY) अणु
		/* no need to enqueue, करो the cmd hdl directly and मुक्त cmd parameter */
		start_bss_network(padapter, (u8 *)&(padapter->mlmepriv.cur_network.network));
	पूर्ण अन्यथा अणु
		/* need enqueue, prepare cmd_obj and enqueue */
		pcmd = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
		अगर (pcmd == शून्य) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		INIT_LIST_HEAD(&pcmd->list);
		pcmd->cmdcode = GEN_CMD_CODE(_CreateBss);
		pcmd->parmbuf = शून्य;
		pcmd->cmdsz =  0;
		pcmd->rsp = शून्य;
		pcmd->rspsz = 0;

		अगर (flags & RTW_CMDF_WAIT_ACK) अणु
			pcmd->sctx = &sctx;
			rtw_sctx_init(&sctx, 2000);
		पूर्ण

		res = rtw_enqueue_cmd(pcmdpriv, pcmd);

		अगर (res == _SUCCESS && (flags & RTW_CMDF_WAIT_ACK)) अणु
			rtw_sctx_रुको(&sctx, __func__);
			अगर (mutex_lock_पूर्णांकerruptible(&pcmdpriv->sctx_mutex) == 0) अणु
				अगर (sctx.status == RTW_SCTX_SUBMITTED)
					pcmd->sctx = शून्य;
				mutex_unlock(&pcmdpriv->sctx_mutex);
			पूर्ण
		पूर्ण
	पूर्ण

निकास:
	वापस res;
पूर्ण

u8 rtw_joinbss_cmd(काष्ठा adapter  *padapter, काष्ठा wlan_network *pnetwork)
अणु
	u8 res = _SUCCESS;
	uपूर्णांक	t_len = 0;
	काष्ठा wlan_bssid_ex		*psecnetwork;
	काष्ठा cmd_obj		*pcmd;
	काष्ठा cmd_priv 	*pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_priv 	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv 	*pqospriv = &pmlmepriv->qospriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा ht_priv 		*phtpriv = &pmlmepriv->htpriv;
	क्रमागत ndis_802_11_network_infraकाष्ठाure ndis_network_mode = pnetwork->network.Infraकाष्ठाureMode;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u32 पंचांगp_len;
	u8 *pपंचांगp = शून्य;

	pcmd = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (pcmd == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	/* क्रम IEs is fix buf size */
	t_len = माप(काष्ठा wlan_bssid_ex);


	/* क्रम hidden ap to set fw_state here */
	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE|WIFI_ADHOC_STATE) != true) अणु
		चयन (ndis_network_mode) अणु
		हाल Ndis802_11IBSS:
			set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			अवरोध;

		हाल Ndis802_11Infraकाष्ठाure:
			set_fwstate(pmlmepriv, WIFI_STATION_STATE);
			अवरोध;

		हाल Ndis802_11APMode:
		हाल Ndis802_11AutoUnknown:
		हाल Ndis802_11Infraकाष्ठाureMax:
			अवरोध;

		पूर्ण
	पूर्ण

	psecnetwork = (काष्ठा wlan_bssid_ex *)&psecuritypriv->sec_bss;

	स_रखो(psecnetwork, 0, t_len);

	स_नकल(psecnetwork, &pnetwork->network, get_wlan_bssid_ex_sz(&pnetwork->network));

	psecuritypriv->authenticator_ie[0] = (अचिन्हित अक्षर)psecnetwork->IELength;

	अगर ((psecnetwork->IELength-12) < (256-1))
		स_नकल(&psecuritypriv->authenticator_ie[1], &psecnetwork->IEs[12], psecnetwork->IELength-12);
	अन्यथा
		स_नकल(&psecuritypriv->authenticator_ie[1], &psecnetwork->IEs[12], (256-1));

	psecnetwork->IELength = 0;
	/*  Added by Albert 2009/02/18 */
	/*  If the driver wants to use the bssid to create the connection. */
	/*  If not,  we have to copy the connecting AP's MAC address to it so that */
	/*  the driver just has the bssid inक्रमmation क्रम PMKIDList searching. */

	अगर (pmlmepriv->assoc_by_bssid == false)
		स_नकल(&pmlmepriv->assoc_bssid[0], &pnetwork->network.MacAddress[0], ETH_ALEN);

	psecnetwork->IELength = rtw_reकाष्ठा_sec_ie(padapter, &pnetwork->network.IEs[0], &psecnetwork->IEs[0], pnetwork->network.IELength);


	pqospriv->qos_option = 0;

	अगर (pregistrypriv->wmm_enable) अणु
		पंचांगp_len = rtw_reकाष्ठा_wmm_ie(padapter, &pnetwork->network.IEs[0], &psecnetwork->IEs[0], pnetwork->network.IELength, psecnetwork->IELength);

		अगर (psecnetwork->IELength != पंचांगp_len) अणु
			psecnetwork->IELength = पंचांगp_len;
			pqospriv->qos_option = 1; /* There is WMM IE in this corresp. beacon */
		पूर्ण अन्यथा अणु
			pqospriv->qos_option = 0;/* There is no WMM IE in this corresp. beacon */
		पूर्ण
	पूर्ण

	phtpriv->ht_option = false;
	pपंचांगp = rtw_get_ie(&pnetwork->network.IEs[12], WLAN_EID_HT_CAPABILITY, &पंचांगp_len, pnetwork->network.IELength-12);
	अगर (pregistrypriv->ht_enable && pपंचांगp && पंचांगp_len > 0) अणु
		/* 	Added by Albert 2010/06/23 */
		/* 	For the WEP mode, we will use the bg mode to करो the connection to aव्योम some IOT issue. */
		/* 	Especially क्रम Realtek 8192u SoftAP. */
		अगर ((padapter->securitypriv.करोt11PrivacyAlgrthm != _WEP40_) &&
			(padapter->securitypriv.करोt11PrivacyAlgrthm != _WEP104_) &&
			(padapter->securitypriv.करोt11PrivacyAlgrthm != _TKIP_)) अणु
			rtw_ht_use_शेष_setting(padapter);

			rtw_build_wmm_ie_ht(padapter, &psecnetwork->IEs[12], &psecnetwork->IELength);

			/* rtw_reकाष्ठाure_ht_ie */
			rtw_reकाष्ठाure_ht_ie(padapter, &pnetwork->network.IEs[12], &psecnetwork->IEs[0],
									pnetwork->network.IELength-12, &psecnetwork->IELength,
									pnetwork->network.Configuration.DSConfig);
		पूर्ण
	पूर्ण

	rtw_append_exented_cap(padapter, &psecnetwork->IEs[0], &psecnetwork->IELength);

	pmlmeinfo->assoc_AP_venकरोr = check_assoc_AP(pnetwork->network.IEs, pnetwork->network.IELength);

	pcmd->cmdsz = get_wlan_bssid_ex_sz(psecnetwork);/* get cmdsz beक्रमe endian conversion */

	INIT_LIST_HEAD(&pcmd->list);
	pcmd->cmdcode = _JoinBss_CMD_;/* GEN_CMD_CODE(_JoinBss) */
	pcmd->parmbuf = (अचिन्हित अक्षर *)psecnetwork;
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;

	res = rtw_enqueue_cmd(pcmdpriv, pcmd);

निकास:
	वापस res;
पूर्ण

u8 rtw_disassoc_cmd(काष्ठा adapter *padapter, u32 deauth_समयout_ms, bool enqueue) /* क्रम sta_mode */
अणु
	काष्ठा cmd_obj *cmकरोbj = शून्य;
	काष्ठा disconnect_parm *param = शून्य;
	काष्ठा cmd_priv *cmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	/* prepare cmd parameter */
	param = rtw_zदो_स्मृति(माप(*param));
	अगर (param == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	param->deauth_समयout_ms = deauth_समयout_ms;

	अगर (enqueue) अणु
		/* need enqueue, prepare cmd_obj and enqueue */
		cmकरोbj = rtw_zदो_स्मृति(माप(*cmकरोbj));
		अगर (cmकरोbj == शून्य) अणु
			res = _FAIL;
			kमुक्त(param);
			जाओ निकास;
		पूर्ण
		init_h2fwcmd_w_parm_no_rsp(cmकरोbj, param, _DisConnect_CMD_);
		res = rtw_enqueue_cmd(cmdpriv, cmकरोbj);
	पूर्ण अन्यथा अणु
		/* no need to enqueue, करो the cmd hdl directly and मुक्त cmd parameter */
		अगर (disconnect_hdl(padapter, (u8 *)param) != H2C_SUCCESS)
			res = _FAIL;
		kमुक्त(param);
	पूर्ण

निकास:
	वापस res;
पूर्ण

u8 rtw_setopmode_cmd(काष्ठा adapter  *padapter, क्रमागत ndis_802_11_network_infraकाष्ठाure networktype, bool enqueue)
अणु
	काष्ठा	cmd_obj *ph2c;
	काष्ठा	setopmode_parm *psetop;

	काष्ठा	cmd_priv   *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	psetop = rtw_zदो_स्मृति(माप(काष्ठा setopmode_parm));

	अगर (psetop == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	psetop->mode = (u8)networktype;

	अगर (enqueue) अणु
		ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
		अगर (ph2c == शून्य) अणु
			kमुक्त(psetop);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		init_h2fwcmd_w_parm_no_rsp(ph2c, psetop, _SetOpMode_CMD_);
		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	पूर्ण अन्यथा अणु
		setopmode_hdl(padapter, (u8 *)psetop);
		kमुक्त(psetop);
	पूर्ण
निकास:
	वापस res;
पूर्ण

u8 rtw_setstakey_cmd(काष्ठा adapter *padapter, काष्ठा sta_info *sta, u8 unicast_key, bool enqueue)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा set_stakey_parm	*psetstakey_para;
	काष्ठा cmd_priv 			*pcmdpriv = &padapter->cmdpriv;
	काष्ठा set_stakey_rsp		*psetstakey_rsp = शून्य;

	काष्ठा mlme_priv 		*pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv 	*psecuritypriv = &padapter->securitypriv;
	u8 res = _SUCCESS;

	psetstakey_para = rtw_zदो_स्मृति(माप(काष्ठा set_stakey_parm));
	अगर (psetstakey_para == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	स_नकल(psetstakey_para->addr, sta->hwaddr, ETH_ALEN);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		psetstakey_para->algorithm = (अचिन्हित अक्षर) psecuritypriv->करोt11PrivacyAlgrthm;
	अन्यथा
		GET_ENCRY_ALGO(psecuritypriv, sta, psetstakey_para->algorithm, false);

	अगर (unicast_key == true)
		स_नकल(&psetstakey_para->key, &sta->करोt118021x_UncstKey, 16);
	अन्यथा
		स_नकल(&psetstakey_para->key, &psecuritypriv->करोt118021XGrpKey[psecuritypriv->करोt118021XGrpKeyid].skey, 16);

	/* jeff: set this because at least sw key is पढ़ोy */
	padapter->securitypriv.busetkipkey = true;

	अगर (enqueue) अणु
		ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
		अगर (ph2c == शून्य) अणु
			kमुक्त(psetstakey_para);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		psetstakey_rsp = rtw_zदो_स्मृति(माप(काष्ठा set_stakey_rsp));
		अगर (psetstakey_rsp == शून्य) अणु
			kमुक्त(ph2c);
			kमुक्त(psetstakey_para);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);
		ph2c->rsp = (u8 *) psetstakey_rsp;
		ph2c->rspsz = माप(काष्ठा set_stakey_rsp);
		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	पूर्ण अन्यथा अणु
		set_stakey_hdl(padapter, (u8 *)psetstakey_para);
		kमुक्त(psetstakey_para);
	पूर्ण
निकास:
	वापस res;
पूर्ण

u8 rtw_clearstakey_cmd(काष्ठा adapter *padapter, काष्ठा sta_info *sta, u8 enqueue)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा set_stakey_parm	*psetstakey_para;
	काष्ठा cmd_priv 			*pcmdpriv = &padapter->cmdpriv;
	काष्ठा set_stakey_rsp		*psetstakey_rsp = शून्य;
	s16 cam_id = 0;
	u8 res = _SUCCESS;

	अगर (!enqueue) अणु
		जबतक ((cam_id = rtw_camid_search(padapter, sta->hwaddr, -1)) >= 0) अणु
			netdev_dbg(padapter->pnetdev,
				   "clear key for addr:%pM, camid:%d\n",
				   MAC_ARG(sta->hwaddr), cam_id);
			clear_cam_entry(padapter, cam_id);
			rtw_camid_मुक्त(padapter, cam_id);
		पूर्ण
	पूर्ण अन्यथा अणु
		ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
		अगर (ph2c == शून्य) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		psetstakey_para = rtw_zदो_स्मृति(माप(काष्ठा set_stakey_parm));
		अगर (psetstakey_para == शून्य) अणु
			kमुक्त(ph2c);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		psetstakey_rsp = rtw_zदो_स्मृति(माप(काष्ठा set_stakey_rsp));
		अगर (psetstakey_rsp == शून्य) अणु
			kमुक्त(ph2c);
			kमुक्त(psetstakey_para);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);
		ph2c->rsp = (u8 *) psetstakey_rsp;
		ph2c->rspsz = माप(काष्ठा set_stakey_rsp);

		स_नकल(psetstakey_para->addr, sta->hwaddr, ETH_ALEN);

		psetstakey_para->algorithm = _NO_PRIVACY_;

		res = rtw_enqueue_cmd(pcmdpriv, ph2c);

	पूर्ण

निकास:
	वापस res;
पूर्ण

u8 rtw_addbareq_cmd(काष्ठा adapter *padapter, u8 tid, u8 *addr)
अणु
	काष्ठा cmd_priv 	*pcmdpriv = &padapter->cmdpriv;
	काष्ठा cmd_obj *ph2c;
	काष्ठा addBaReq_parm	*paddbareq_parm;

	u8 res = _SUCCESS;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	paddbareq_parm = rtw_zदो_स्मृति(माप(काष्ठा addBaReq_parm));
	अगर (paddbareq_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	paddbareq_parm->tid = tid;
	स_नकल(paddbareq_parm->addr, addr, ETH_ALEN);

	init_h2fwcmd_w_parm_no_rsp(ph2c, paddbareq_parm, GEN_CMD_CODE(_AddBAReq));

	/* rtw_enqueue_cmd(pcmdpriv, ph2c); */
	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:
	वापस res;
पूर्ण
/* add क्रम CONFIG_IEEE80211W, none 11w can use it */
u8 rtw_reset_securitypriv_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा drvextra_cmd_parm  *pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
	अगर (pdrvextra_cmd_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = RESET_SECURITYPRIV;
	pdrvextra_cmd_parm->type = 0;
	pdrvextra_cmd_parm->size = 0;
	pdrvextra_cmd_parm->pbuf = शून्य;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));


	/* rtw_enqueue_cmd(pcmdpriv, ph2c); */
	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:
	वापस res;
पूर्ण

u8 rtw_मुक्त_assoc_resources_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा drvextra_cmd_parm  *pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
	अगर (pdrvextra_cmd_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = FREE_ASSOC_RESOURCES;
	pdrvextra_cmd_parm->type = 0;
	pdrvextra_cmd_parm->size = 0;
	pdrvextra_cmd_parm->pbuf = शून्य;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));


	/* rtw_enqueue_cmd(pcmdpriv, ph2c); */
	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:
	वापस res;
पूर्ण

u8 rtw_dynamic_chk_wk_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा drvextra_cmd_parm  *pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	/* only  primary padapter करोes this cmd */
	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
	अगर (pdrvextra_cmd_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = DYNAMIC_CHK_WK_CID;
	pdrvextra_cmd_parm->type = 0;
	pdrvextra_cmd_parm->size = 0;
	pdrvextra_cmd_parm->pbuf = शून्य;
	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));


	/* rtw_enqueue_cmd(pcmdpriv, ph2c); */
	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:
	वापस res;
पूर्ण

u8 rtw_set_chplan_cmd(काष्ठा adapter *padapter, u8 chplan, u8 enqueue, u8 swconfig)
अणु
	काष्ठा	cmd_obj *pcmकरोbj;
	काष्ठा	SetChannelPlan_param *setChannelPlan_param;
	काष्ठा	cmd_priv   *pcmdpriv = &padapter->cmdpriv;

	u8 res = _SUCCESS;

	/*  check अगर allow software config */
	अगर (swconfig && rtw_hal_is_disable_sw_channel_plan(padapter) == true) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	/* check input parameter */
	अगर (!rtw_is_channel_plan_valid(chplan)) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	/* prepare cmd parameter */
	setChannelPlan_param = rtw_zदो_स्मृति(माप(काष्ठा SetChannelPlan_param));
	अगर (setChannelPlan_param == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	setChannelPlan_param->channel_plan = chplan;

	अगर (enqueue) अणु
		/* need enqueue, prepare cmd_obj and enqueue */
		pcmकरोbj = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
		अगर (pcmकरोbj == शून्य) अणु
			kमुक्त(setChannelPlan_param);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		init_h2fwcmd_w_parm_no_rsp(pcmकरोbj, setChannelPlan_param, GEN_CMD_CODE(_SetChannelPlan));
		res = rtw_enqueue_cmd(pcmdpriv, pcmकरोbj);
	पूर्ण अन्यथा अणु
		/* no need to enqueue, करो the cmd hdl directly and मुक्त cmd parameter */
		अगर (set_chplan_hdl(padapter, (अचिन्हित अक्षर *)setChannelPlan_param) != H2C_SUCCESS)
			res = _FAIL;

		kमुक्त(setChannelPlan_param);
	पूर्ण

	/* करो something based on res... */
	अगर (res == _SUCCESS)
		padapter->mlmepriv.ChannelPlan = chplan;

निकास:
	वापस res;
पूर्ण

अटल व्योम collect_traffic_statistics(काष्ठा adapter *padapter)
अणु
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);

	/*  Tx */
	pdvobjpriv->traffic_stat.tx_bytes = padapter->xmitpriv.tx_bytes;
	pdvobjpriv->traffic_stat.tx_pkts = padapter->xmitpriv.tx_pkts;
	pdvobjpriv->traffic_stat.tx_drop = padapter->xmitpriv.tx_drop;

	/*  Rx */
	pdvobjpriv->traffic_stat.rx_bytes = padapter->recvpriv.rx_bytes;
	pdvobjpriv->traffic_stat.rx_pkts = padapter->recvpriv.rx_pkts;
	pdvobjpriv->traffic_stat.rx_drop = padapter->recvpriv.rx_drop;

	/*  Calculate throughput in last पूर्णांकerval */
	pdvobjpriv->traffic_stat.cur_tx_bytes = pdvobjpriv->traffic_stat.tx_bytes - pdvobjpriv->traffic_stat.last_tx_bytes;
	pdvobjpriv->traffic_stat.cur_rx_bytes = pdvobjpriv->traffic_stat.rx_bytes - pdvobjpriv->traffic_stat.last_rx_bytes;
	pdvobjpriv->traffic_stat.last_tx_bytes = pdvobjpriv->traffic_stat.tx_bytes;
	pdvobjpriv->traffic_stat.last_rx_bytes = pdvobjpriv->traffic_stat.rx_bytes;

	pdvobjpriv->traffic_stat.cur_tx_tp = (u32)(pdvobjpriv->traffic_stat.cur_tx_bytes * 8/2/1024/1024);
	pdvobjpriv->traffic_stat.cur_rx_tp = (u32)(pdvobjpriv->traffic_stat.cur_rx_bytes * 8/2/1024/1024);
पूर्ण

u8 traffic_status_watchकरोg(काष्ठा adapter *padapter, u8 from_समयr)
अणु
	u8 bEnterPS = false;
	u16 BusyThresholdHigh = 25;
	u16 BusyThresholdLow = 10;
	u16 BusyThreshold = BusyThresholdHigh;
	u8 bBusyTraffic = false, bTxBusyTraffic = false, bRxBusyTraffic = false;
	u8 bHigherBusyTraffic = false, bHigherBusyRxTraffic = false, bHigherBusyTxTraffic = false;

	काष्ठा mlme_priv 	*pmlmepriv = &(padapter->mlmepriv);

	collect_traffic_statistics(padapter);

	/*  */
	/*  Determine अगर our traffic is busy now */
	/*  */
	अगर ((check_fwstate(pmlmepriv, _FW_LINKED) == true)
		/*&& !MgntInitAdapterInProgress(pMgntInfo)*/) अणु
		/*  अगर we उठाओ bBusyTraffic in last watchकरोg, using lower threshold. */
		अगर (pmlmepriv->LinkDetectInfo.bBusyTraffic)
				BusyThreshold = BusyThresholdLow;

		अगर (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > BusyThreshold ||
			pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > BusyThreshold) अणु
			bBusyTraffic = true;

			अगर (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > pmlmepriv->LinkDetectInfo.NumTxOkInPeriod)
				bRxBusyTraffic = true;
			अन्यथा
				bTxBusyTraffic = true;
		पूर्ण

		/*  Higher Tx/Rx data. */
		अगर (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > 4000 ||
			pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > 4000) अणु
			bHigherBusyTraffic = true;

			अगर (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > pmlmepriv->LinkDetectInfo.NumTxOkInPeriod)
				bHigherBusyRxTraffic = true;
			अन्यथा
				bHigherBusyTxTraffic = true;
		पूर्ण

		/*  check traffic क्रम  घातersaving. */
		अगर (((pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod + pmlmepriv->LinkDetectInfo.NumTxOkInPeriod) > 8) ||
			(pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod > 2)) अणु
			bEnterPS = false;

			अगर (bBusyTraffic == true) अणु
				अगर (pmlmepriv->LinkDetectInfo.TrafficTransitionCount <= 4)
					pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 4;

				pmlmepriv->LinkDetectInfo.TrafficTransitionCount++;

				अगर (pmlmepriv->LinkDetectInfo.TrafficTransitionCount > 30/*TrafficTransitionLevel*/)
					pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 30;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (pmlmepriv->LinkDetectInfo.TrafficTransitionCount >= 2)
				pmlmepriv->LinkDetectInfo.TrafficTransitionCount -= 2;
			अन्यथा
				pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 0;

			अगर (pmlmepriv->LinkDetectInfo.TrafficTransitionCount == 0)
				bEnterPS = true;
		पूर्ण

		/*  LeisurePS only work in infra mode. */
		अगर (bEnterPS) अणु
			अगर (!from_समयr)
				LPS_Enter(padapter, "TRAFFIC_IDLE");
		पूर्ण अन्यथा अणु
			अगर (!from_समयr)
				LPS_Leave(padapter, "TRAFFIC_BUSY");
			अन्यथा
				rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_TRAFFIC_BUSY, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(padapter);
		पूर्णांक n_assoc_अगरace = 0;

		अगर (check_fwstate(&(dvobj->padapters->mlmepriv), WIFI_ASOC_STATE))
			n_assoc_अगरace++;

		अगर (!from_समयr && n_assoc_अगरace == 0)
			LPS_Leave(padapter, "NON_LINKED");
	पूर्ण

	pmlmepriv->LinkDetectInfo.NumRxOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.NumTxOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.bBusyTraffic = bBusyTraffic;
	pmlmepriv->LinkDetectInfo.bTxBusyTraffic = bTxBusyTraffic;
	pmlmepriv->LinkDetectInfo.bRxBusyTraffic = bRxBusyTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyTraffic = bHigherBusyTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyRxTraffic = bHigherBusyRxTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyTxTraffic = bHigherBusyTxTraffic;

	वापस bEnterPS;

पूर्ण

अटल व्योम dynamic_chk_wk_hdl(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv;
	pmlmepriv = &(padapter->mlmepriv);

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
		expire_समयout_chk(padapter);

	/* क्रम debug purpose */
	_linked_info_dump(padapter);


	/* अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING|_FW_UNDER_SURVEY) ==false) */
	अणु
		linked_status_chk(padapter);
		traffic_status_watchकरोg(padapter, 0);
	पूर्ण

	rtw_hal_dm_watchकरोg(padapter);

	/* check_hw_pbc(padapter, pdrvextra_cmd->pbuf, pdrvextra_cmd->type); */

	/*  */
	/*  BT-Coexist */
	/*  */
	hal_btcoex_Handler(padapter);


	/* always call rtw_ps_processor() at last one. */
	अगर (is_primary_adapter(padapter))
		rtw_ps_processor(padapter);
पूर्ण

व्योम lps_ctrl_wk_hdl(काष्ठा adapter *padapter, u8 lps_ctrl_type);
व्योम lps_ctrl_wk_hdl(काष्ठा adapter *padapter, u8 lps_ctrl_type)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	u8 mstatus;

	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)
		|| (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true)) अणु
		वापस;
	पूर्ण

	चयन (lps_ctrl_type) अणु
	हाल LPS_CTRL_SCAN:
		hal_btcoex_ScanNotअगरy(padapter, true);

		अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true) अणु
			/*  connect */
			LPS_Leave(padapter, "LPS_CTRL_SCAN");
		पूर्ण
		अवरोध;
	हाल LPS_CTRL_JOINBSS:
		LPS_Leave(padapter, "LPS_CTRL_JOINBSS");
		अवरोध;
	हाल LPS_CTRL_CONNECT:
		mstatus = 1;/* connect */
		/*  Reset LPS Setting */
		pwrpriv->LpsIdleCount = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_JOINBSSRPT, (u8 *)(&mstatus));
		rtw_btcoex_MediaStatusNotअगरy(padapter, mstatus);
		अवरोध;
	हाल LPS_CTRL_DISCONNECT:
		mstatus = 0;/* disconnect */
		rtw_btcoex_MediaStatusNotअगरy(padapter, mstatus);
		LPS_Leave(padapter, "LPS_CTRL_DISCONNECT");
		rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_JOINBSSRPT, (u8 *)(&mstatus));
		अवरोध;
	हाल LPS_CTRL_SPECIAL_PACKET:
		pwrpriv->DelayLPSLastTimeStamp = jअगरfies;
		hal_btcoex_SpecialPacketNotअगरy(padapter, PACKET_DHCP);
		LPS_Leave(padapter, "LPS_CTRL_SPECIAL_PACKET");
		अवरोध;
	हाल LPS_CTRL_LEAVE:
		LPS_Leave(padapter, "LPS_CTRL_LEAVE");
		अवरोध;
	हाल LPS_CTRL_TRAFFIC_BUSY:
		LPS_Leave(padapter, "LPS_CTRL_TRAFFIC_BUSY");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

u8 rtw_lps_ctrl_wk_cmd(काष्ठा adapter *padapter, u8 lps_ctrl_type, u8 enqueue)
अणु
	काष्ठा cmd_obj	*ph2c;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	/* काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(padapter); */
	u8 res = _SUCCESS;

	/* अगर (!pwrctrlpriv->bLeisurePs) */
	/* 	वापस res; */

	अगर (enqueue) अणु
		ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
		अगर (ph2c == शून्य) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
		अगर (pdrvextra_cmd_parm == शून्य) अणु
			kमुक्त(ph2c);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		pdrvextra_cmd_parm->ec_id = LPS_CTRL_WK_CID;
		pdrvextra_cmd_parm->type = lps_ctrl_type;
		pdrvextra_cmd_parm->size = 0;
		pdrvextra_cmd_parm->pbuf = शून्य;

		init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));

		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	पूर्ण अन्यथा अणु
		lps_ctrl_wk_hdl(padapter, lps_ctrl_type);
	पूर्ण

निकास:
	वापस res;
पूर्ण

अटल व्योम rtw_dm_in_lps_hdl(काष्ठा adapter *padapter)
अणु
	rtw_hal_set_hwreg(padapter, HW_VAR_DM_IN_LPS, शून्य);
पूर्ण

u8 rtw_dm_in_lps_wk_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj	*ph2c;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;


	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
	अगर (pdrvextra_cmd_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = DM_IN_LPS_WK_CID;
	pdrvextra_cmd_parm->type = 0;
	pdrvextra_cmd_parm->size = 0;
	pdrvextra_cmd_parm->pbuf = शून्य;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:

	वापस res;

पूर्ण

अटल व्योम rtw_lps_change_dtim_hdl(काष्ठा adapter *padapter, u8 dtim)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);

	अगर (dtim <= 0 || dtim > 16)
		वापस;

	अगर (hal_btcoex_IsBtControlLps(padapter) == true)
		वापस;

	mutex_lock(&pwrpriv->lock);

	अगर (pwrpriv->dtim != dtim)
		pwrpriv->dtim = dtim;

	अगर (pwrpriv->fw_current_in_ps_mode && (pwrpriv->pwr_mode > PS_MODE_ACTIVE)) अणु
		u8 ps_mode = pwrpriv->pwr_mode;

		rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_PWRMODE, (u8 *)(&ps_mode));
	पूर्ण

	mutex_unlock(&pwrpriv->lock);
पूर्ण

अटल व्योम rtw_dm_ra_mask_hdl(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	अगर (psta)
		set_sta_rate(padapter, psta);
पूर्ण

u8 rtw_dm_ra_mask_wk_cmd(काष्ठा adapter *padapter, u8 *psta)
अणु
	काष्ठा cmd_obj	*ph2c;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;


	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
	अगर (pdrvextra_cmd_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = DM_RA_MSK_WK_CID;
	pdrvextra_cmd_parm->type = 0;
	pdrvextra_cmd_parm->size = 0;
	pdrvextra_cmd_parm->pbuf = psta;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:

	वापस res;

पूर्ण

u8 rtw_ps_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj		*ppscmd;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	ppscmd = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ppscmd == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
	अगर (pdrvextra_cmd_parm == शून्य) अणु
		kमुक्त(ppscmd);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = POWER_SAVING_CTRL_WK_CID;
	pdrvextra_cmd_parm->type = 0;
	pdrvextra_cmd_parm->size = 0;
	pdrvextra_cmd_parm->pbuf = शून्य;
	init_h2fwcmd_w_parm_no_rsp(ppscmd, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));

	res = rtw_enqueue_cmd(pcmdpriv, ppscmd);

निकास:
	वापस res;
पूर्ण

u32 g_रुको_hiq_empty;

अटल व्योम rtw_chk_hi_queue_hdl(काष्ठा adapter *padapter)
अणु
	काष्ठा sta_info *psta_bmc;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	अचिन्हित दीर्घ start = jअगरfies;
	u8 empty = false;

	psta_bmc = rtw_get_bcmc_stainfo(padapter);
	अगर (!psta_bmc)
		वापस;

	rtw_hal_get_hwreg(padapter, HW_VAR_CHK_HI_QUEUE_EMPTY, &empty);

	जबतक (false == empty && jअगरfies_to_msecs(jअगरfies - start) < g_रुको_hiq_empty) अणु
		msleep(100);
		rtw_hal_get_hwreg(padapter, HW_VAR_CHK_HI_QUEUE_EMPTY, &empty);
	पूर्ण

	अगर (psta_bmc->sleepq_len == 0) अणु
		अगर (empty == _SUCCESS) अणु
			bool update_tim = false;

			अगर (pstapriv->tim_biपंचांगap & BIT(0))
				update_tim = true;

			pstapriv->tim_biपंचांगap &= ~BIT(0);
			pstapriv->sta_dz_biपंचांगap &= ~BIT(0);

			अगर (update_tim)
				update_beacon(padapter, WLAN_EID_TIM, शून्य, true);
		पूर्ण अन्यथा अणु/* re check again */
			rtw_chk_hi_queue_cmd(padapter);
		पूर्ण

	पूर्ण

पूर्ण

u8 rtw_chk_hi_queue_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj	*ph2c;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
	अगर (pdrvextra_cmd_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = CHECK_HIQ_WK_CID;
	pdrvextra_cmd_parm->type = 0;
	pdrvextra_cmd_parm->size = 0;
	pdrvextra_cmd_parm->pbuf = शून्य;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:

	वापस res;

पूर्ण

काष्ठा btinfo अणु
	u8 cid;
	u8 len;

	u8 bConnection:1;
	u8 bSCOeSCO:1;
	u8 bInQPage:1;
	u8 bACLBusy:1;
	u8 bSCOBusy:1;
	u8 bHID:1;
	u8 bA2DP:1;
	u8 bFTP:1;

	u8 retry_cnt:4;
	u8 rsvd_34:1;
	u8 rsvd_35:1;
	u8 rsvd_36:1;
	u8 rsvd_37:1;

	u8 rssi;

	u8 rsvd_50:1;
	u8 rsvd_51:1;
	u8 rsvd_52:1;
	u8 rsvd_53:1;
	u8 rsvd_54:1;
	u8 rsvd_55:1;
	u8 eSCO_SCO:1;
	u8 Master_Slave:1;

	u8 rsvd_6;
	u8 rsvd_7;
पूर्ण;

अटल व्योम rtw_btinfo_hdl(काष्ठा adapter *adapter, u8 *buf, u16 buf_len)
अणु
	#घोषणा BTINFO_WIFI_FETCH 0x23
	#घोषणा BTINFO_BT_AUTO_RPT 0x27
	काष्ठा btinfo *info = (काष्ठा btinfo *)buf;
	u8 cmd_idx;
	u8 len;

	cmd_idx = info->cid;

	अगर (info->len > buf_len-2) अणु
		rtw_warn_on(1);
		len = buf_len-2;
	पूर्ण अन्यथा अणु
		len = info->len;
	पूर्ण

	/* transक्रमm BT-FW btinfo to WiFI-FW C2H क्रमmat and notअगरy */
	अगर (cmd_idx == BTINFO_WIFI_FETCH)
		buf[1] = 0;
	अन्यथा अगर (cmd_idx == BTINFO_BT_AUTO_RPT)
		buf[1] = 2;
	hal_btcoex_BtInfoNotअगरy(adapter, len+1, &buf[1]);
पूर्ण

u8 rtw_c2h_packet_wk_cmd(काष्ठा adapter *padapter, u8 *pbuf, u16 length)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा drvextra_cmd_parm *pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
	अगर (pdrvextra_cmd_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = C2H_WK_CID;
	pdrvextra_cmd_parm->type = 0;
	pdrvextra_cmd_parm->size = length;
	pdrvextra_cmd_parm->pbuf = pbuf;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:
	वापस res;
पूर्ण

/* करोnt call R/W in this function, beuहाल SDIO पूर्णांकerrupt have claim host */
/* or deadlock will happen and cause special-प्रणालीserver-died in android */
u8 rtw_c2h_wk_cmd(काष्ठा adapter *padapter, u8 *c2h_evt)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा drvextra_cmd_parm *pdrvextra_cmd_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (ph2c == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = rtw_zदो_स्मृति(माप(काष्ठा drvextra_cmd_parm));
	अगर (pdrvextra_cmd_parm == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = C2H_WK_CID;
	pdrvextra_cmd_parm->type = 0;
	pdrvextra_cmd_parm->size =  c2h_evt?16:0;
	pdrvextra_cmd_parm->pbuf = c2h_evt;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:

	वापस res;
पूर्ण

अटल व्योम c2h_wk_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा evt_priv *evtpriv = container_of(work, काष्ठा evt_priv, c2h_wk);
	काष्ठा adapter *adapter = container_of(evtpriv, काष्ठा adapter, evtpriv);
	u8 *c2h_evt;
	c2h_id_filter ccx_id_filter = rtw_hal_c2h_id_filter_ccx(adapter);

	evtpriv->c2h_wk_alive = true;

	जबतक (!rtw_cbuf_empty(evtpriv->c2h_queue)) अणु
		c2h_evt = (u8 *)rtw_cbuf_pop(evtpriv->c2h_queue);
		अगर (c2h_evt) अणु
			/* This C2H event is पढ़ो, clear it */
			c2h_evt_clear(adapter);
		पूर्ण अन्यथा अणु
			c2h_evt = rtw_दो_स्मृति(16);
			अगर (c2h_evt) अणु
				/* This C2H event is not पढ़ो, पढ़ो & clear now */
				अगर (c2h_evt_पढ़ो_88xx(adapter, c2h_evt) != _SUCCESS) अणु
					kमुक्त(c2h_evt);
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Special poपूर्णांकer to trigger c2h_evt_clear only */
		अगर ((व्योम *)c2h_evt == (व्योम *)evtpriv)
			जारी;

		अगर (!rtw_hal_c2h_valid(adapter, c2h_evt)) अणु
			kमुक्त(c2h_evt);
			जारी;
		पूर्ण

		अगर (ccx_id_filter(c2h_evt) == true) अणु
			/* Handle CCX report here */
			rtw_hal_c2h_handler(adapter, c2h_evt);
			kमुक्त(c2h_evt);
		पूर्ण अन्यथा अणु
			/* Enqueue पूर्णांकo cmd_thपढ़ो क्रम others */
			rtw_c2h_wk_cmd(adapter, c2h_evt);
		पूर्ण
	पूर्ण

	evtpriv->c2h_wk_alive = false;
पूर्ण

u8 rtw_drvextra_cmd_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा drvextra_cmd_parm *pdrvextra_cmd;

	अगर (!pbuf)
		वापस H2C_PARAMETERS_ERROR;

	pdrvextra_cmd = (काष्ठा drvextra_cmd_parm *)pbuf;

	चयन (pdrvextra_cmd->ec_id) अणु
	हाल DYNAMIC_CHK_WK_CID:/* only  primary padapter go to this cmd, but execute dynamic_chk_wk_hdl() क्रम two पूर्णांकerfaces */
		dynamic_chk_wk_hdl(padapter);
		अवरोध;
	हाल POWER_SAVING_CTRL_WK_CID:
		rtw_ps_processor(padapter);
		अवरोध;
	हाल LPS_CTRL_WK_CID:
		lps_ctrl_wk_hdl(padapter, (u8)pdrvextra_cmd->type);
		अवरोध;
	हाल DM_IN_LPS_WK_CID:
		rtw_dm_in_lps_hdl(padapter);
		अवरोध;
	हाल LPS_CHANGE_DTIM_CID:
		rtw_lps_change_dtim_hdl(padapter, (u8)pdrvextra_cmd->type);
		अवरोध;
	हाल CHECK_HIQ_WK_CID:
		rtw_chk_hi_queue_hdl(padapter);
		अवरोध;
	/* add क्रम CONFIG_IEEE80211W, none 11w can use it */
	हाल RESET_SECURITYPRIV:
		rtw_reset_securitypriv(padapter);
		अवरोध;
	हाल FREE_ASSOC_RESOURCES:
		rtw_मुक्त_assoc_resources(padapter, 1);
		अवरोध;
	हाल C2H_WK_CID:
		rtw_hal_set_hwreg_with_buf(padapter, HW_VAR_C2H_HANDLE, pdrvextra_cmd->pbuf, pdrvextra_cmd->size);
		अवरोध;
	हाल DM_RA_MSK_WK_CID:
		rtw_dm_ra_mask_hdl(padapter, (काष्ठा sta_info *)pdrvextra_cmd->pbuf);
		अवरोध;
	हाल BTINFO_WK_CID:
		rtw_btinfo_hdl(padapter, pdrvextra_cmd->pbuf, pdrvextra_cmd->size);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (pdrvextra_cmd->pbuf && pdrvextra_cmd->size > 0)
		kमुक्त(pdrvextra_cmd->pbuf);

	वापस H2C_SUCCESS;
पूर्ण

व्योम rtw_survey_cmd_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (pcmd->res == H2C_DROPPED) अणु
		/* TODO: cancel समयr and करो समयout handler directly... */
		/* need to make समयout handlerOS independent */
		_set_समयr(&pmlmepriv->scan_to_समयr, 1);
	पूर्ण अन्यथा अगर (pcmd->res != H2C_SUCCESS) अणु
		_set_समयr(&pmlmepriv->scan_to_समयr, 1);
	पूर्ण

	/*  मुक्त cmd */
	rtw_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम rtw_disassoc_cmd_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (pcmd->res != H2C_SUCCESS) अणु
		spin_lock_bh(&pmlmepriv->lock);
		set_fwstate(pmlmepriv, _FW_LINKED);
		spin_unlock_bh(&pmlmepriv->lock);

		वापस;
	पूर्ण
	/*  मुक्त cmd */
	rtw_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम rtw_joinbss_cmd_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (pcmd->res == H2C_DROPPED) अणु
		/* TODO: cancel समयr and करो समयout handler directly... */
		/* need to make समयout handlerOS independent */
		_set_समयr(&pmlmepriv->assoc_समयr, 1);
	पूर्ण अन्यथा अगर (pcmd->res != H2C_SUCCESS) अणु
		_set_समयr(&pmlmepriv->assoc_समयr, 1);
	पूर्ण

	rtw_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम rtw_createbss_cmd_callback(काष्ठा adapter *padapter, काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा sta_info *psta = शून्य;
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pnetwork = (काष्ठा wlan_bssid_ex *)pcmd->parmbuf;
	काष्ठा wlan_network *tgt_network = &(pmlmepriv->cur_network);

	अगर (pcmd->parmbuf == शून्य)
		जाओ निकास;

	अगर (pcmd->res != H2C_SUCCESS)
		_set_समयr(&pmlmepriv->assoc_समयr, 1);

	del_समयr_sync(&pmlmepriv->assoc_समयr);

	spin_lock_bh(&pmlmepriv->lock);


	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		psta = rtw_get_stainfo(&padapter->stapriv, pnetwork->MacAddress);
		अगर (!psta) अणु
			psta = rtw_alloc_stainfo(&padapter->stapriv, pnetwork->MacAddress);
			अगर (!psta)
				जाओ createbss_cmd_fail;
		पूर्ण

		rtw_indicate_connect(padapter);
	पूर्ण अन्यथा अणु
		pwlan = rtw_alloc_network(pmlmepriv);
		spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
		अगर (pwlan == शून्य) अणु
			pwlan = rtw_get_oldest_wlan_network(&pmlmepriv->scanned_queue);
			अगर (pwlan == शून्य) अणु
				spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
				जाओ createbss_cmd_fail;
			पूर्ण
			pwlan->last_scanned = jअगरfies;
		पूर्ण अन्यथा अणु
			list_add_tail(&(pwlan->list), &pmlmepriv->scanned_queue.queue);
		पूर्ण

		pnetwork->Length = get_wlan_bssid_ex_sz(pnetwork);
		स_नकल(&(pwlan->network), pnetwork, pnetwork->Length);
		/* pwlan->fixed = true; */

		/* list_add_tail(&(pwlan->list), &pmlmepriv->scanned_queue.queue); */

		/*  copy pdev_network inक्रमmation to	pmlmepriv->cur_network */
		स_नकल(&tgt_network->network, pnetwork, (get_wlan_bssid_ex_sz(pnetwork)));

		/*  reset DSConfig */
		/* tgt_network->network.Configuration.DSConfig = (u32)rtw_ch2freq(pnetwork->Configuration.DSConfig); */

		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

		spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
		/*  we will set _FW_LINKED when there is one more sat to join us (rtw_stassoc_event_callback) */

	पूर्ण

createbss_cmd_fail:

	spin_unlock_bh(&pmlmepriv->lock);
निकास:
	rtw_मुक्त_cmd_obj(pcmd);
पूर्ण



व्योम rtw_setstaKey_cmdrsp_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु

	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा set_stakey_rsp *psetstakey_rsp = (काष्ठा set_stakey_rsp *) (pcmd->rsp);
	काष्ठा sta_info *psta = rtw_get_stainfo(pstapriv, psetstakey_rsp->addr);

	अगर (!psta)
		जाओ निकास;

निकास:
	rtw_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम rtw_setassocsta_cmdrsp_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा set_assocsta_parm *passocsta_parm = (काष्ठा set_assocsta_parm *)(pcmd->parmbuf);
	काष्ठा set_assocsta_rsp *passocsta_rsp = (काष्ठा set_assocsta_rsp *) (pcmd->rsp);
	काष्ठा sta_info *psta = rtw_get_stainfo(pstapriv, passocsta_parm->addr);

	अगर (!psta)
		जाओ निकास;

	psta->aid = passocsta_rsp->cam_id;
	psta->mac_id = passocsta_rsp->cam_id;

	spin_lock_bh(&pmlmepriv->lock);

	अगर ((check_fwstate(pmlmepriv, WIFI_MP_STATE) == true) && (check_fwstate(pmlmepriv, _FW_UNDER_LINKING) == true))
		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

	set_fwstate(pmlmepriv, _FW_LINKED);
	spin_unlock_bh(&pmlmepriv->lock);

निकास:
	rtw_मुक्त_cmd_obj(pcmd);
पूर्ण
