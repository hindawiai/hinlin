<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 *******************************************************************************/
#घोषणा _SDIO_OPS_LINUX_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>

अटल bool rtw_sdio_claim_host_needed(काष्ठा sdio_func *func)
अणु
	काष्ठा dvobj_priv *dvobj = sdio_get_drvdata(func);
	काष्ठा sdio_data *sdio_data = &dvobj->पूर्णांकf_data;

	अगर (sdio_data->sys_sdio_irq_thd && sdio_data->sys_sdio_irq_thd == current)
		वापस false;
	वापस true;
पूर्ण

अंतरभूत व्योम rtw_sdio_set_irq_thd(काष्ठा dvobj_priv *dvobj, व्योम *thd_hdl)
अणु
	काष्ठा sdio_data *sdio_data = &dvobj->पूर्णांकf_data;

	sdio_data->sys_sdio_irq_thd = thd_hdl;
पूर्ण

u8 sd_f0_पढ़ो8(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, s32 *err)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;

	u8 v = 0;
	काष्ठा sdio_func *func;
	bool claim_needed;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस v;

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	अगर (claim_needed)
		sdio_claim_host(func);
	v = sdio_f0_पढ़ोb(func, addr, err);
	अगर (claim_needed)
		sdio_release_host(func);
	वापस v;
पूर्ण

/*
 * Return:
 *0		Success
 *others	Fail
 */
s32 _sd_cmd52_पढ़ो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pdata)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;

	पूर्णांक err = 0, i;
	काष्ठा sdio_func *func;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस err;

	func = psdio->func;

	क्रम (i = 0; i < cnt; i++) अणु
		pdata[i] = sdio_पढ़ोb(func, addr + i, &err);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/*
 * Return:
 *0		Success
 *others	Fail
 */
s32 sd_cmd52_पढ़ो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pdata)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;

	पूर्णांक err = 0;
	काष्ठा sdio_func *func;
	bool claim_needed;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस err;

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	अगर (claim_needed)
		sdio_claim_host(func);
	err = _sd_cmd52_पढ़ो(pपूर्णांकfhdl, addr, cnt, pdata);
	अगर (claim_needed)
		sdio_release_host(func);
	वापस err;
पूर्ण

/*
 * Return:
 *0		Success
 *others	Fail
 */
s32 _sd_cmd52_ग_लिखो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pdata)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;

	पूर्णांक err = 0, i;
	काष्ठा sdio_func *func;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस err;

	func = psdio->func;

	क्रम (i = 0; i < cnt; i++) अणु
		sdio_ग_लिखोb(func, pdata[i], addr + i, &err);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/*
 * Return:
 *0		Success
 *others	Fail
 */
s32 sd_cmd52_ग_लिखो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pdata)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;

	पूर्णांक err = 0;
	काष्ठा sdio_func *func;
	bool claim_needed;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस err;

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	अगर (claim_needed)
		sdio_claim_host(func);
	err = _sd_cmd52_ग_लिखो(pपूर्णांकfhdl, addr, cnt, pdata);
	अगर (claim_needed)
		sdio_release_host(func);
	वापस err;
पूर्ण

u8 sd_पढ़ो8(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, s32 *err)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;

	u8 v = 0;
	काष्ठा sdio_func *func;
	bool claim_needed;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस v;

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	अगर (claim_needed)
		sdio_claim_host(func);
	v = sdio_पढ़ोb(func, addr, err);
	अगर (claim_needed)
		sdio_release_host(func);
	वापस v;
पूर्ण

u32 sd_पढ़ो32(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, s32 *err)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;
	u32 v = 0;
	काष्ठा sdio_func *func;
	bool claim_needed;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस v;

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	अगर (claim_needed)
		sdio_claim_host(func);
	v = sdio_पढ़ोl(func, addr, err);
	अगर (claim_needed)
		sdio_release_host(func);

	अगर (err && *err) अणु
		पूर्णांक i;

		*err = 0;
		क्रम (i = 0; i < SD_IO_TRY_CNT; i++) अणु
			अगर (claim_needed)
				sdio_claim_host(func);
			v = sdio_पढ़ोl(func, addr, err);
			अगर (claim_needed)
				sdio_release_host(func);

			अगर (*err == 0) अणु
				rtw_reset_continual_io_error(psdiodev);
				अवरोध;
			पूर्ण अन्यथा अणु
				अगर ((-ESHUTDOWN == *err) || (-ENODEV == *err))
					padapter->bSurpriseRemoved = true;

				अगर (rtw_inc_and_chk_continual_io_error(psdiodev) == true) अणु
					padapter->bSurpriseRemoved = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस  v;
पूर्ण

व्योम sd_ग_लिखो8(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u8 v, s32 *err)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;
	काष्ठा sdio_func *func;
	bool claim_needed;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस;

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	अगर (claim_needed)
		sdio_claim_host(func);
	sdio_ग_लिखोb(func, v, addr, err);
	अगर (claim_needed)
		sdio_release_host(func);
पूर्ण

व्योम sd_ग_लिखो32(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 v, s32 *err)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;
	काष्ठा sdio_func *func;
	bool claim_needed;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस;

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	अगर (claim_needed)
		sdio_claim_host(func);
	sdio_ग_लिखोl(func, v, addr, err);
	अगर (claim_needed)
		sdio_release_host(func);

	अगर (err && *err) अणु
		पूर्णांक i;

		*err = 0;
		क्रम (i = 0; i < SD_IO_TRY_CNT; i++) अणु
			अगर (claim_needed)
				sdio_claim_host(func);
			sdio_ग_लिखोl(func, v, addr, err);
			अगर (claim_needed)
				sdio_release_host(func);
			अगर (*err == 0) अणु
				rtw_reset_continual_io_error(psdiodev);
				अवरोध;
			पूर्ण अन्यथा अणु
				अगर ((-ESHUTDOWN == *err) || (-ENODEV == *err))
					padapter->bSurpriseRemoved = true;

				अगर (rtw_inc_and_chk_continual_io_error(psdiodev) == true) अणु
					padapter->bSurpriseRemoved = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

	पूर्ण
पूर्ण

/*
 * Use CMD53 to पढ़ो data from SDIO device.
 * This function MUST be called after sdio_claim_host() or
 * in SDIO ISR(host had been claimed).
 *
 * Parameters:
 *psdio	poपूर्णांकer of SDIO_DATA
 *addr	address to पढ़ो
 *cnt		amount to पढ़ो
 *pdata	poपूर्णांकer to put data, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *0		Success
 *others	Fail
 */
s32 _sd_पढ़ो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, व्योम *pdata)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;

	पूर्णांक err = -EPERM;
	काष्ठा sdio_func *func;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस err;

	func = psdio->func;

	अगर (unlikely((cnt == 1) || (cnt == 2))) अणु
		पूर्णांक i;
		u8 *pbuf = pdata;

		क्रम (i = 0; i < cnt; i++) अणु
			*(pbuf + i) = sdio_पढ़ोb(func, addr + i, &err);

			अगर (err)
				अवरोध;
		पूर्ण
		वापस err;
	पूर्ण

	err = sdio_स_नकल_fromio(func, pdata, addr, cnt);

	वापस err;
पूर्ण

/*
 * Use CMD53 to पढ़ो data from SDIO device.
 *
 * Parameters:
 *psdio	poपूर्णांकer of SDIO_DATA
 *addr	address to पढ़ो
 *cnt		amount to पढ़ो
 *pdata	poपूर्णांकer to put data, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *0		Success
 *others	Fail
 */
s32 sd_पढ़ो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, व्योम *pdata)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;

	काष्ठा sdio_func *func;
	bool claim_needed;
	s32 err = -EPERM;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस err;

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	अगर (claim_needed)
		sdio_claim_host(func);
	err = _sd_पढ़ो(pपूर्णांकfhdl, addr, cnt, pdata);
	अगर (claim_needed)
		sdio_release_host(func);
	वापस err;
पूर्ण

/*
 * Use CMD53 to ग_लिखो data to SDIO device.
 * This function MUST be called after sdio_claim_host() or
 * in SDIO ISR(host had been claimed).
 *
 * Parameters:
 *psdio	poपूर्णांकer of SDIO_DATA
 *addr	address to ग_लिखो
 *cnt		amount to ग_लिखो
 *pdata	data poपूर्णांकer, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *0		Success
 *others	Fail
 */
s32 _sd_ग_लिखो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, व्योम *pdata)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;

	काष्ठा sdio_func *func;
	u32 size;
	s32 err =  -EPERM;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस err;

	func = psdio->func;
/*	size = sdio_align_size(func, cnt); */

	अगर (unlikely((cnt == 1) || (cnt == 2))) अणु
		पूर्णांक i;
		u8 *pbuf = pdata;

		क्रम (i = 0; i < cnt; i++) अणु
			sdio_ग_लिखोb(func, *(pbuf + i), addr + i, &err);
			अगर (err)
				अवरोध;
		पूर्ण

		वापस err;
	पूर्ण

	size = cnt;
	err = sdio_स_नकल_toio(func, addr, pdata, size);

	वापस err;
पूर्ण

/*
 * Use CMD53 to ग_लिखो data to SDIO device.
 *
 * Parameters:
 *  psdio	poपूर्णांकer of SDIO_DATA
 *  addr	address to ग_लिखो
 *  cnt		amount to ग_लिखो
 *  pdata	data poपूर्णांकer, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *  0		Success
 *  others	Fail
 */
s32 sd_ग_लिखो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, व्योम *pdata)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *psdiodev;
	काष्ठा sdio_data *psdio;
	काष्ठा sdio_func *func;
	bool claim_needed;
	s32 err =  -EPERM;

	padapter = pपूर्णांकfhdl->padapter;
	psdiodev = pपूर्णांकfhdl->pपूर्णांकf_dev;
	psdio = &psdiodev->पूर्णांकf_data;

	अगर (padapter->bSurpriseRemoved)
		वापस err;

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	अगर (claim_needed)
		sdio_claim_host(func);
	err = _sd_ग_लिखो(pपूर्णांकfhdl, addr, cnt, pdata);
	अगर (claim_needed)
		sdio_release_host(func);
	वापस err;
पूर्ण
