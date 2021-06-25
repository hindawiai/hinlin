<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _HAL_SDIO_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_data.h>

u8 rtw_hal_sdio_max_txoqt_मुक्त_space(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);

	अगर (pHalData->SdioTxOQTMaxFreeSpace < 8)
		pHalData->SdioTxOQTMaxFreeSpace = 8;

	वापस pHalData->SdioTxOQTMaxFreeSpace;
पूर्ण

u8 rtw_hal_sdio_query_tx_मुक्तpage(
	काष्ठा adapter *padapter, u8 PageIdx, u8 RequiredPageNum
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);

	अगर ((pHalData->SdioTxFIFOFreePage[PageIdx]+pHalData->SdioTxFIFOFreePage[PUBLIC_QUEUE_IDX]) >= (RequiredPageNum))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

व्योम rtw_hal_sdio_update_tx_मुक्तpage(
	काष्ठा adapter *padapter, u8 PageIdx, u8 RequiredPageNum
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8 DedicatedPgNum = 0;
	u8 RequiredPublicFreePgNum = 0;
	/* _irqL irql; */

	/* spin_lock_bh(&pHalData->SdioTxFIFOFreePageLock); */

	DedicatedPgNum = pHalData->SdioTxFIFOFreePage[PageIdx];
	अगर (RequiredPageNum <= DedicatedPgNum) अणु
		pHalData->SdioTxFIFOFreePage[PageIdx] -= RequiredPageNum;
	पूर्ण अन्यथा अणु
		pHalData->SdioTxFIFOFreePage[PageIdx] = 0;
		RequiredPublicFreePgNum = RequiredPageNum - DedicatedPgNum;
		pHalData->SdioTxFIFOFreePage[PUBLIC_QUEUE_IDX] -= RequiredPublicFreePgNum;
	पूर्ण

	/* spin_unlock_bh(&pHalData->SdioTxFIFOFreePageLock); */
पूर्ण

व्योम rtw_hal_set_sdio_tx_max_length(
	काष्ठा adapter *padapter, u8 numHQ, u8 numNQ, u8 numLQ, u8 numPubQ
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u32 page_size;
	u32 lenHQ, lenNQ, lenLQ;

	rtw_hal_get_def_var(padapter, HAL_DEF_TX_PAGE_SIZE, &page_size);

	lenHQ = ((numHQ + numPubQ) >> 1) * page_size;
	lenNQ = ((numNQ + numPubQ) >> 1) * page_size;
	lenLQ = ((numLQ + numPubQ) >> 1) * page_size;

	pHalData->sdio_tx_max_len[HI_QUEUE_IDX] =
		(lenHQ > MAX_XMITBUF_SZ) ? MAX_XMITBUF_SZ : lenHQ;
	pHalData->sdio_tx_max_len[MID_QUEUE_IDX] =
		(lenNQ > MAX_XMITBUF_SZ) ? MAX_XMITBUF_SZ : lenNQ;
	pHalData->sdio_tx_max_len[LOW_QUEUE_IDX] =
		(lenLQ > MAX_XMITBUF_SZ) ? MAX_XMITBUF_SZ : lenLQ;
पूर्ण

u32 rtw_hal_get_sdio_tx_max_length(काष्ठा adapter *padapter, u8 queue_idx)
अणु
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u32 deviceId, max_len;


	deviceId = ffaddr2deviceId(pdvobjpriv, queue_idx);
	चयन (deviceId) अणु
	हाल WLAN_TX_HIQ_DEVICE_ID:
		max_len = pHalData->sdio_tx_max_len[HI_QUEUE_IDX];
		अवरोध;

	हाल WLAN_TX_MIQ_DEVICE_ID:
		max_len = pHalData->sdio_tx_max_len[MID_QUEUE_IDX];
		अवरोध;

	हाल WLAN_TX_LOQ_DEVICE_ID:
		max_len = pHalData->sdio_tx_max_len[LOW_QUEUE_IDX];
		अवरोध;

	शेष:
		max_len = pHalData->sdio_tx_max_len[MID_QUEUE_IDX];
		अवरोध;
	पूर्ण

	वापस max_len;
पूर्ण
