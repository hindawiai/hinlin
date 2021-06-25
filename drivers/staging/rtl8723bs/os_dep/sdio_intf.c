<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _HCI_INTF_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_btcoex.h>
#समावेश <linux/jअगरfies.h>

#अगर_अघोषित dev_to_sdio_func
#घोषणा dev_to_sdio_func(d)     container_of(d, काष्ठा sdio_func, dev)
#पूर्ण_अगर

अटल स्थिर काष्ठा sdio_device_id sdio_ids[] = अणु
	अणु SDIO_DEVICE(0x024c, 0x0523), पूर्ण,
	अणु SDIO_DEVICE(0x024c, 0x0525), पूर्ण,
	अणु SDIO_DEVICE(0x024c, 0x0623), पूर्ण,
	अणु SDIO_DEVICE(0x024c, 0x0626), पूर्ण,
	अणु SDIO_DEVICE(0x024c, 0x0627), पूर्ण,
	अणु SDIO_DEVICE(0x024c, 0xb723), पूर्ण,
	अणु /* end: all zeroes */				पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdio, sdio_ids);

अटल पूर्णांक rtw_drv_init(काष्ठा sdio_func *func, स्थिर काष्ठा sdio_device_id *id);
अटल व्योम rtw_dev_हटाओ(काष्ठा sdio_func *func);
अटल पूर्णांक rtw_sdio_resume(काष्ठा device *dev);
अटल पूर्णांक rtw_sdio_suspend(काष्ठा device *dev);

अटल स्थिर काष्ठा dev_pm_ops rtw_sdio_pm_ops = अणु
	.suspend	= rtw_sdio_suspend,
	.resume	= rtw_sdio_resume,
पूर्ण;

अटल काष्ठा sdio_driver rtl8723bs_sdio_driver = अणु
	.probe = rtw_drv_init,
	.हटाओ = rtw_dev_हटाओ,
	.name = "rtl8723bs",
	.id_table = sdio_ids,
	.drv = अणु
		.pm = &rtw_sdio_pm_ops,
	पूर्ण
पूर्ण;

अटल व्योम sd_sync_पूर्णांक_hdl(काष्ठा sdio_func *func)
अणु
	काष्ठा dvobj_priv *psdpriv;


	psdpriv = sdio_get_drvdata(func);

	अगर (!psdpriv->अगर1)
		वापस;

	rtw_sdio_set_irq_thd(psdpriv, current);
	sd_पूर्णांक_hdl(psdpriv->अगर1);
	rtw_sdio_set_irq_thd(psdpriv, शून्य);
पूर्ण

अटल पूर्णांक sdio_alloc_irq(काष्ठा dvobj_priv *dvobj)
अणु
	काष्ठा sdio_data *psdio_data;
	काष्ठा sdio_func *func;
	पूर्णांक err;

	psdio_data = &dvobj->पूर्णांकf_data;
	func = psdio_data->func;

	sdio_claim_host(func);

	err = sdio_claim_irq(func, &sd_sync_पूर्णांक_hdl);
	अगर (err) अणु
		dvobj->drv_dbg.dbg_sdio_alloc_irq_error_cnt++;
		prपूर्णांकk(KERN_CRIT "%s: sdio_claim_irq FAIL(%d)!\n", __func__, err);
	पूर्ण अन्यथा अणु
		dvobj->drv_dbg.dbg_sdio_alloc_irq_cnt++;
		dvobj->irq_alloc = 1;
	पूर्ण

	sdio_release_host(func);

	वापस err?_FAIL:_SUCCESS;
पूर्ण

अटल व्योम sdio_मुक्त_irq(काष्ठा dvobj_priv *dvobj)
अणु
	काष्ठा sdio_data *psdio_data;
	काष्ठा sdio_func *func;
	पूर्णांक err;

	अगर (dvobj->irq_alloc) अणु
		psdio_data = &dvobj->पूर्णांकf_data;
		func = psdio_data->func;

		अगर (func) अणु
			sdio_claim_host(func);
			err = sdio_release_irq(func);
			अगर (err) अणु
				dvobj->drv_dbg.dbg_sdio_मुक्त_irq_error_cnt++;
				netdev_err(dvobj->अगर1->pnetdev,
					   "%s: sdio_release_irq FAIL(%d)!\n",
					   __func__, err);
			पूर्ण अन्यथा
				dvobj->drv_dbg.dbg_sdio_मुक्त_irq_cnt++;
			sdio_release_host(func);
		पूर्ण
		dvobj->irq_alloc = 0;
	पूर्ण
पूर्ण

अटल u32 sdio_init(काष्ठा dvobj_priv *dvobj)
अणु
	काष्ठा sdio_data *psdio_data;
	काष्ठा sdio_func *func;
	पूर्णांक err;

	psdio_data = &dvobj->पूर्णांकf_data;
	func = psdio_data->func;

	/* 3 1. init SDIO bus */
	sdio_claim_host(func);

	err = sdio_enable_func(func);
	अगर (err) अणु
		dvobj->drv_dbg.dbg_sdio_init_error_cnt++;
		जाओ release;
	पूर्ण

	err = sdio_set_block_size(func, 512);
	अगर (err) अणु
		dvobj->drv_dbg.dbg_sdio_init_error_cnt++;
		जाओ release;
	पूर्ण
	psdio_data->block_transfer_len = 512;
	psdio_data->tx_block_mode = 1;
	psdio_data->rx_block_mode = 1;

release:
	sdio_release_host(func);

	अगर (err)
		वापस _FAIL;
	वापस _SUCCESS;
पूर्ण

अटल व्योम sdio_deinit(काष्ठा dvobj_priv *dvobj)
अणु
	काष्ठा sdio_func *func;
	पूर्णांक err;

	func = dvobj->पूर्णांकf_data.func;

	अगर (func) अणु
		sdio_claim_host(func);
		err = sdio_disable_func(func);
		अगर (err)
			dvobj->drv_dbg.dbg_sdio_deinit_error_cnt++;

		अगर (dvobj->irq_alloc) अणु
			err = sdio_release_irq(func);
			अगर (err)
				dvobj->drv_dbg.dbg_sdio_मुक्त_irq_error_cnt++;
			अन्यथा
				dvobj->drv_dbg.dbg_sdio_मुक्त_irq_cnt++;
		पूर्ण

		sdio_release_host(func);
	पूर्ण
पूर्ण
अटल काष्ठा dvobj_priv *sdio_dvobj_init(काष्ठा sdio_func *func)
अणु
	पूर्णांक status = _FAIL;
	काष्ठा dvobj_priv *dvobj = शून्य;
	काष्ठा sdio_data *psdio;

	dvobj = devobj_init();
	अगर (!dvobj)
		जाओ निकास;

	sdio_set_drvdata(func, dvobj);

	psdio = &dvobj->पूर्णांकf_data;
	psdio->func = func;

	अगर (sdio_init(dvobj) != _SUCCESS)
		जाओ मुक्त_dvobj;

	rtw_reset_continual_io_error(dvobj);
	status = _SUCCESS;

मुक्त_dvobj:
	अगर (status != _SUCCESS && dvobj) अणु
		sdio_set_drvdata(func, शून्य);

		devobj_deinit(dvobj);

		dvobj = शून्य;
	पूर्ण
निकास:
	वापस dvobj;
पूर्ण

अटल व्योम sdio_dvobj_deinit(काष्ठा sdio_func *func)
अणु
	काष्ठा dvobj_priv *dvobj = sdio_get_drvdata(func);

	sdio_set_drvdata(func, शून्य);
	अगर (dvobj) अणु
		sdio_deinit(dvobj);
		devobj_deinit(dvobj);
	पूर्ण
पूर्ण

व्योम rtw_set_hal_ops(काष्ठा adapter *padapter)
अणु
	/* alloc memory क्रम HAL DATA */
	rtw_hal_data_init(padapter);

	rtl8723bs_set_hal_ops(padapter);
पूर्ण

अटल व्योम sd_पूर्णांकf_start(काष्ठा adapter *padapter)
अणु
	अगर (!padapter)
		वापस;

	/*  hal dep */
	rtw_hal_enable_पूर्णांकerrupt(padapter);
पूर्ण

अटल व्योम sd_पूर्णांकf_stop(काष्ठा adapter *padapter)
अणु
	अगर (!padapter)
		वापस;

	/*  hal dep */
	rtw_hal_disable_पूर्णांकerrupt(padapter);
पूर्ण


अटल काष्ठा adapter *rtw_sdio_अगर1_init(काष्ठा dvobj_priv *dvobj, स्थिर काष्ठा sdio_device_id  *pdid)
अणु
	पूर्णांक status = _FAIL;
	काष्ठा net_device *pnetdev;
	काष्ठा adapter *padapter = शून्य;
	काष्ठा sdio_data *psdio = &dvobj->पूर्णांकf_data;

	padapter = vzalloc(माप(*padapter));
	अगर (!padapter)
		जाओ निकास;

	padapter->dvobj = dvobj;
	dvobj->अगर1 = padapter;

	padapter->bDriverStopped = true;

	dvobj->padapters = padapter;
	padapter->अगरace_id = 0;

	/* 3 1. init network device data */
	pnetdev = rtw_init_netdev(padapter);
	अगर (!pnetdev)
		जाओ मुक्त_adapter;

	SET_NETDEV_DEV(pnetdev, dvobj_to_dev(dvobj));

	padapter = rtw_netdev_priv(pnetdev);

	/* 3 3. init driver special setting, पूर्णांकerface, OS and hardware relative */

	/* 4 3.1 set hardware operation functions */
	rtw_set_hal_ops(padapter);


	/* 3 5. initialize Chip version */
	padapter->पूर्णांकf_start = &sd_पूर्णांकf_start;
	padapter->पूर्णांकf_stop = &sd_पूर्णांकf_stop;

	padapter->पूर्णांकf_init = &sdio_init;
	padapter->पूर्णांकf_deinit = &sdio_deinit;
	padapter->पूर्णांकf_alloc_irq = &sdio_alloc_irq;
	padapter->पूर्णांकf_मुक्त_irq = &sdio_मुक्त_irq;

	अगर (rtw_init_io_priv(padapter, sdio_set_पूर्णांकf_ops) == _FAIL)
		जाओ मुक्त_hal_data;

	rtw_hal_पढ़ो_chip_version(padapter);

	rtw_hal_chip_configure(padapter);

	hal_btcoex_Initialize((व्योम *) padapter);

	/* 3 6. पढ़ो efuse/eeprom data */
	rtw_hal_पढ़ो_chip_info(padapter);

	/* 3 7. init driver common data */
	अगर (rtw_init_drv_sw(padapter) == _FAIL)
		जाओ मुक्त_hal_data;

	rtw_wdev_alloc(padapter, dvobj_to_dev(dvobj));

	/* 3 8. get WLan MAC address */
	/*  set mac addr */
	rtw_macaddr_cfg(&psdio->func->dev, padapter->eeprompriv.mac_addr);

	rtw_hal_disable_पूर्णांकerrupt(padapter);

	status = _SUCCESS;

मुक्त_hal_data:
	अगर (status != _SUCCESS && padapter->HalData)
		kमुक्त(padapter->HalData);

	अगर (status != _SUCCESS) अणु
		rtw_wdev_unरेजिस्टर(padapter->rtw_wdev);
		rtw_wdev_मुक्त(padapter->rtw_wdev);
	पूर्ण

मुक्त_adapter:
	अगर (status != _SUCCESS) अणु
		अगर (pnetdev)
			rtw_मुक्त_netdev(pnetdev);
		अन्यथा
			vमुक्त((u8 *)padapter);
		padapter = शून्य;
	पूर्ण
निकास:
	वापस padapter;
पूर्ण

अटल व्योम rtw_sdio_अगर1_deinit(काष्ठा adapter *अगर1)
अणु
	काष्ठा net_device *pnetdev = अगर1->pnetdev;
	काष्ठा mlme_priv *pmlmepriv = &अगर1->mlmepriv;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED))
		rtw_disassoc_cmd(अगर1, 0, false);

	मुक्त_mlme_ap_info(अगर1);

	rtw_cancel_all_समयr(अगर1);

	rtw_dev_unload(अगर1);

	अगर (अगर1->rtw_wdev)
		rtw_wdev_मुक्त(अगर1->rtw_wdev);

	rtw_मुक्त_drv_sw(अगर1);

	अगर (pnetdev)
		rtw_मुक्त_netdev(pnetdev);
पूर्ण

/*
 * drv_init() - a device potentially क्रम us
 *
 * notes: drv_init() is called when the bus driver has located a card क्रम us to support.
 *        We accept the new device by वापसing 0.
 */
अटल पूर्णांक rtw_drv_init(
	काष्ठा sdio_func *func,
	स्थिर काष्ठा sdio_device_id *id)
अणु
	पूर्णांक status = _FAIL;
	काष्ठा adapter *अगर1 = शून्य;
	काष्ठा dvobj_priv *dvobj;

	dvobj = sdio_dvobj_init(func);
	अगर (!dvobj)
		जाओ निकास;

	अगर1 = rtw_sdio_अगर1_init(dvobj, id);
	अगर (!अगर1)
		जाओ मुक्त_dvobj;

	/* dev_alloc_name && रेजिस्टर_netdev */
	status = rtw_drv_रेजिस्टर_netdev(अगर1);
	अगर (status != _SUCCESS)
		जाओ मुक्त_अगर1;

	अगर (sdio_alloc_irq(dvobj) != _SUCCESS)
		जाओ मुक्त_अगर1;

	rtw_ndev_notअगरier_रेजिस्टर();
	status = _SUCCESS;

मुक्त_अगर1:
	अगर (status != _SUCCESS && अगर1)
		rtw_sdio_अगर1_deinit(अगर1);

मुक्त_dvobj:
	अगर (status != _SUCCESS)
		sdio_dvobj_deinit(func);
निकास:
	वापस status == _SUCCESS ? 0 : -ENODEV;
पूर्ण

अटल व्योम rtw_dev_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा dvobj_priv *dvobj = sdio_get_drvdata(func);
	काष्ठा adapter *padapter = dvobj->अगर1;

	dvobj->processing_dev_हटाओ = true;

	rtw_unरेजिस्टर_netdevs(dvobj);

	अगर (!padapter->bSurpriseRemoved) अणु
		पूर्णांक err;

		/* test surprise हटाओ */
		sdio_claim_host(func);
		sdio_पढ़ोb(func, 0, &err);
		sdio_release_host(func);
		अगर (err == -ENOMEDIUM)
			padapter->bSurpriseRemoved = true;
	पूर्ण

	rtw_ps_deny(padapter, PS_DENY_DRV_REMOVE);

	rtw_pm_set_ips(padapter, IPS_NONE);
	rtw_pm_set_lps(padapter, PS_MODE_ACTIVE);

	LeaveAllPowerSaveMode(padapter);

	rtw_btcoex_HaltNotअगरy(padapter);

	rtw_sdio_अगर1_deinit(padapter);

	sdio_dvobj_deinit(func);
पूर्ण

अटल पूर्णांक rtw_sdio_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा dvobj_priv *psdpriv = sdio_get_drvdata(func);
	काष्ठा pwrctrl_priv *pwrpriv = dvobj_to_pwrctl(psdpriv);
	काष्ठा adapter *padapter = psdpriv->अगर1;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	अगर (padapter->bDriverStopped)
		वापस 0;

	अगर (pwrpriv->bInSuspend) अणु
		pdbgpriv->dbg_suspend_error_cnt++;
		वापस 0;
	पूर्ण

	वापस rtw_suspend_common(padapter);
पूर्ण

अटल पूर्णांक rtw_resume_process(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	काष्ठा dvobj_priv *psdpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	अगर (!pwrpriv->bInSuspend) अणु
		pdbgpriv->dbg_resume_error_cnt++;
		वापस -1;
	पूर्ण

	वापस rtw_resume_common(padapter);
पूर्ण

अटल पूर्णांक rtw_sdio_resume(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा dvobj_priv *psdpriv = sdio_get_drvdata(func);
	काष्ठा adapter *padapter = psdpriv->अगर1;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	पूर्णांक ret = 0;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	pdbgpriv->dbg_resume_cnt++;

	ret = rtw_resume_process(padapter);

	pmlmeext->last_scan_समय = jअगरfies;
	वापस ret;
पूर्ण

अटल पूर्णांक __init rtw_drv_entry(व्योम)
अणु
	पूर्णांक ret;

	ret = sdio_रेजिस्टर_driver(&rtl8723bs_sdio_driver);
	अगर (ret != 0)
		rtw_ndev_notअगरier_unरेजिस्टर();

	वापस ret;
पूर्ण

अटल व्योम __निकास rtw_drv_halt(व्योम)
अणु
	sdio_unरेजिस्टर_driver(&rtl8723bs_sdio_driver);

	rtw_ndev_notअगरier_unरेजिस्टर();
पूर्ण


module_init(rtw_drv_entry);
module_निकास(rtw_drv_halt);
