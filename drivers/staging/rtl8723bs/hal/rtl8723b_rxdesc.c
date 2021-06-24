<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8723B_REDESC_C_

#समावेश <rtl8723b_hal.h>

अटल व्योम process_rssi(काष्ठा adapter *padapter, जोड़ recv_frame *prframe)
अणु
	काष्ठा rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	काष्ठा संकेत_stat *संकेत_stat = &padapter->recvpriv.संकेत_strength_data;

	/* अगर (pRfd->Status.bPacketToSelf || pRfd->Status.bPacketBeacon) */
	अणु
		अगर (संकेत_stat->update_req) अणु
			संकेत_stat->total_num = 0;
			संकेत_stat->total_val = 0;
			संकेत_stat->update_req = 0;
		पूर्ण

		संकेत_stat->total_num++;
		संकेत_stat->total_val  += pattrib->phy_info.SignalStrength;
		संकेत_stat->avg_val = संकेत_stat->total_val / संकेत_stat->total_num;
	पूर्ण

पूर्ण /*  Process_UI_RSSI_8192C */

अटल व्योम process_link_qual(काष्ठा adapter *padapter, जोड़ recv_frame *prframe)
अणु
	काष्ठा rx_pkt_attrib *pattrib;
	काष्ठा संकेत_stat *संकेत_stat;

	अगर (!prframe || !padapter)
		वापस;

	pattrib = &prframe->u.hdr.attrib;
	संकेत_stat = &padapter->recvpriv.संकेत_qual_data;

	अगर (संकेत_stat->update_req) अणु
		संकेत_stat->total_num = 0;
		संकेत_stat->total_val = 0;
		संकेत_stat->update_req = 0;
	पूर्ण

	संकेत_stat->total_num++;
	संकेत_stat->total_val  += pattrib->phy_info.SignalQuality;
	संकेत_stat->avg_val = संकेत_stat->total_val / संकेत_stat->total_num;
पूर्ण /*  Process_UiLinkQuality8192S */


व्योम rtl8723b_process_phy_info(काष्ठा adapter *padapter, व्योम *prframe)
अणु
	जोड़ recv_frame *precvframe = prframe;
	/*  */
	/*  Check RSSI */
	/*  */
	process_rssi(padapter, precvframe);
	/*  */
	/*  Check PWDB. */
	/*  */
	/* process_PWDB(padapter, precvframe); */

	/* UpdateRxSignalStatistics8192C(Adapter, pRfd); */
	/*  */
	/*  Check EVM */
	/*  */
	process_link_qual(padapter,  precvframe);
	#अगर_घोषित DBG_RX_SIGNAL_DISPLAY_RAW_DATA
	rtw_store_phy_info(padapter, prframe);
	#पूर्ण_अगर

पूर्ण
