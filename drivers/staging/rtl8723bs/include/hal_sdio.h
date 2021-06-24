<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_SDIO_H_
#घोषणा __HAL_SDIO_H_

#घोषणा ffaddr2deviceId(pdvobj, addr)	(pdvobj->Queue2Pipe[addr])

u8 rtw_hal_sdio_max_txoqt_मुक्त_space(काष्ठा adapter *padapter);
u8 rtw_hal_sdio_query_tx_मुक्तpage(काष्ठा adapter *padapter, u8 PageIdx, u8 RequiredPageNum);
व्योम rtw_hal_sdio_update_tx_मुक्तpage(काष्ठा adapter *padapter, u8 PageIdx, u8 RequiredPageNum);
व्योम rtw_hal_set_sdio_tx_max_length(काष्ठा adapter *padapter, u8 numHQ, u8 numNQ, u8 numLQ, u8 numPubQ);
u32 rtw_hal_get_sdio_tx_max_length(काष्ठा adapter *padapter, u8 queue_idx);

#पूर्ण_अगर /* __RTW_LED_H_ */
