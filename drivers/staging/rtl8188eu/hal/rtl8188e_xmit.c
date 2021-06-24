<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8188E_XMIT_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <rtl8188e_hal.h>

व्योम handle_txrpt_ccx_88e(काष्ठा adapter *adapter, u8 *buf)
अणु
	काष्ठा txrpt_ccx_88e *txrpt_ccx = (काष्ठा txrpt_ccx_88e *)buf;

	अगर (txrpt_ccx->पूर्णांक_ccx) अणु
		अगर (txrpt_ccx->pkt_ok)
			rtw_ack_tx_करोne(&adapter->xmitpriv,
					RTW_SCTX_DONE_SUCCESS);
		अन्यथा
			rtw_ack_tx_करोne(&adapter->xmitpriv,
					RTW_SCTX_DONE_CCX_PKT_FAIL);
	पूर्ण
पूर्ण

व्योम _dbg_dump_tx_info(काष्ठा adapter *padapter, पूर्णांक frame_tag,
		       काष्ठा tx_desc *ptxdesc)
अणु
	u8 dmp_txpkt;
	bool dump_txdesc = false;

	rtw_hal_get_def_var(padapter, HAL_DEF_DBG_DUMP_TXPKT, &(dmp_txpkt));

	अगर (dmp_txpkt == 1) अणु/* dump txdesc क्रम data frame */
		DBG_88E("dump tx_desc for data frame\n");
		अगर ((frame_tag & 0x0f) == DATA_FRAMETAG)
			dump_txdesc = true;
	पूर्ण अन्यथा अगर (dmp_txpkt == 2) अणु/* dump txdesc क्रम mgnt frame */
		DBG_88E("dump tx_desc for mgnt frame\n");
		अगर ((frame_tag & 0x0f) == MGNT_FRAMETAG)
			dump_txdesc = true;
	पूर्ण

	अगर (dump_txdesc) अणु
		DBG_88E("=====================================\n");
		DBG_88E("txdw0(0x%08x)\n", ptxdesc->txdw0);
		DBG_88E("txdw1(0x%08x)\n", ptxdesc->txdw1);
		DBG_88E("txdw2(0x%08x)\n", ptxdesc->txdw2);
		DBG_88E("txdw3(0x%08x)\n", ptxdesc->txdw3);
		DBG_88E("txdw4(0x%08x)\n", ptxdesc->txdw4);
		DBG_88E("txdw5(0x%08x)\n", ptxdesc->txdw5);
		DBG_88E("txdw6(0x%08x)\n", ptxdesc->txdw6);
		DBG_88E("txdw7(0x%08x)\n", ptxdesc->txdw7);
		DBG_88E("=====================================\n");
	पूर्ण
पूर्ण
