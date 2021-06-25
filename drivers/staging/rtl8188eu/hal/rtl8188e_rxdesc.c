<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8188E_REDESC_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <rtl8188e_hal.h>

अटल व्योम process_rssi(काष्ठा adapter *padapter, काष्ठा recv_frame *prframe)
अणु
	काष्ठा rx_pkt_attrib *pattrib = &prframe->attrib;
	काष्ठा संकेत_stat *संकेत_stat = &padapter->recvpriv.संकेत_strength_data;

	अगर (संकेत_stat->update_req) अणु
		संकेत_stat->total_num = 0;
		संकेत_stat->total_val = 0;
		संकेत_stat->update_req = 0;
	पूर्ण

	संकेत_stat->total_num++;
	संकेत_stat->total_val  += pattrib->phy_info.SignalStrength;
	संकेत_stat->avg_val = संकेत_stat->total_val / संकेत_stat->total_num;
पूर्ण /*  Process_UI_RSSI_8192C */

अटल व्योम process_link_qual(काष्ठा adapter *padapter,
			      काष्ठा recv_frame *prframe)
अणु
	काष्ठा rx_pkt_attrib *pattrib;
	काष्ठा संकेत_stat *संकेत_stat;

	अगर (!prframe || !padapter)
		वापस;

	pattrib = &prframe->attrib;
	संकेत_stat = &padapter->recvpriv.संकेत_qual_data;

	अगर (संकेत_stat->update_req) अणु
		संकेत_stat->total_num = 0;
		संकेत_stat->total_val = 0;
		संकेत_stat->update_req = 0;
	पूर्ण

	संकेत_stat->total_num++;
	संकेत_stat->total_val  += pattrib->phy_info.SignalQuality;
	संकेत_stat->avg_val = संकेत_stat->total_val / संकेत_stat->total_num;
पूर्ण

व्योम rtl8188e_process_phy_info(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *precvframe)
अणु
	/*  Check RSSI */
	process_rssi(padapter, precvframe);
	/*  Check EVM */
	process_link_qual(padapter,  precvframe);
पूर्ण

व्योम update_recvframe_attrib_88e(काष्ठा recv_frame *precvframe,
				 काष्ठा recv_stat *prxstat)
अणु
	काष्ठा rx_pkt_attrib	*pattrib;
	काष्ठा recv_stat	report;

	report.rxdw0 = prxstat->rxdw0;
	report.rxdw1 = prxstat->rxdw1;
	report.rxdw2 = prxstat->rxdw2;
	report.rxdw3 = prxstat->rxdw3;
	report.rxdw4 = prxstat->rxdw4;
	report.rxdw5 = prxstat->rxdw5;

	pattrib = &precvframe->attrib;
	स_रखो(pattrib, 0, माप(काष्ठा rx_pkt_attrib));

	pattrib->crc_err = (u8)((le32_to_cpu(report.rxdw0) >> 14) & 0x1);/* u8)prxreport->crc32; */

	/*  update rx report to recv_frame attribute */
	pattrib->pkt_rpt_type = (u8)((le32_to_cpu(report.rxdw3) >> 14) & 0x3);/* prxreport->rpt_sel; */

	अगर (pattrib->pkt_rpt_type == NORMAL_RX) अणु /* Normal rx packet */
		pattrib->pkt_len = (u16)(le32_to_cpu(report.rxdw0) & 0x00003fff);/* u16)prxreport->pktlen; */
		pattrib->drvinfo_sz = (u8)((le32_to_cpu(report.rxdw0) >> 16) & 0xf) * 8;/* u8)(prxreport->drvinfosize << 3); */

		pattrib->physt =  (u8)((le32_to_cpu(report.rxdw0) >> 26) & 0x1);/* u8)prxreport->physt; */

		pattrib->bdecrypted = (le32_to_cpu(report.rxdw0) & BIT(27)) ? 0 : 1;/* u8)(prxreport->swdec ? 0 : 1); */
		pattrib->encrypt = (u8)((le32_to_cpu(report.rxdw0) >> 20) & 0x7);/* u8)prxreport->security; */

		pattrib->qos = (u8)((le32_to_cpu(report.rxdw0) >> 23) & 0x1);/* u8)prxreport->qos; */
		pattrib->priority = (u8)((le32_to_cpu(report.rxdw1) >> 8) & 0xf);/* u8)prxreport->tid; */

		pattrib->amsdu = (u8)((le32_to_cpu(report.rxdw1) >> 13) & 0x1);/* u8)prxreport->amsdu; */

		pattrib->seq_num = (u16)(le32_to_cpu(report.rxdw2) & 0x00000fff);/* u16)prxreport->seq; */
		pattrib->frag_num = (u8)((le32_to_cpu(report.rxdw2) >> 12) & 0xf);/* u8)prxreport->frag; */
		pattrib->mfrag = (u8)((le32_to_cpu(report.rxdw1) >> 27) & 0x1);/* u8)prxreport->mf; */
		pattrib->mdata = (u8)((le32_to_cpu(report.rxdw1) >> 26) & 0x1);/* u8)prxreport->md; */

		pattrib->mcs_rate = (u8)(le32_to_cpu(report.rxdw3) & 0x3f);/* u8)prxreport->rxmcs; */
		pattrib->rxht = (u8)((le32_to_cpu(report.rxdw3) >> 6) & 0x1);/* u8)prxreport->rxht; */

		pattrib->icv_err = (u8)((le32_to_cpu(report.rxdw0) >> 15) & 0x1);/* u8)prxreport->icverr; */
		pattrib->shअगरt_sz = (u8)((le32_to_cpu(report.rxdw0) >> 24) & 0x3);
	पूर्ण अन्यथा अगर (pattrib->pkt_rpt_type == TX_REPORT1) अणु /* CCX */
		pattrib->pkt_len = TX_RPT1_PKT_LEN;
		pattrib->drvinfo_sz = 0;
	पूर्ण अन्यथा अगर (pattrib->pkt_rpt_type == TX_REPORT2) अणु /*  TX RPT */
		pattrib->pkt_len = (u16)(le32_to_cpu(report.rxdw0) & 0x3FF);/* Rx length[9:0] */
		pattrib->drvinfo_sz = 0;

		/*  */
		/*  Get TX report MAC ID valid. */
		/*  */
		pattrib->MacIDValidEntry[0] = le32_to_cpu(report.rxdw4);
		pattrib->MacIDValidEntry[1] = le32_to_cpu(report.rxdw5);

	पूर्ण अन्यथा अगर (pattrib->pkt_rpt_type == HIS_REPORT) अणु /*  USB HISR RPT */
		pattrib->pkt_len = (u16)(le32_to_cpu(report.rxdw0) & 0x00003fff);/* u16)prxreport->pktlen; */
	पूर्ण
पूर्ण

/*
 * Notice:
 *	Beक्रमe calling this function,
 *	precvframe->rx_data should be पढ़ोy!
 */
व्योम update_recvframe_phyinfo_88e(काष्ठा recv_frame *precvframe,
				  काष्ठा phy_stat *pphy_status)
अणु
	काष्ठा adapter *padapter = precvframe->adapter;
	काष्ठा rx_pkt_attrib *pattrib = &precvframe->attrib;
	काष्ठा odm_phy_status_info *pPHYInfo  = (काष्ठा odm_phy_status_info *)(&pattrib->phy_info);
	u8 *wlanhdr;
	काष्ठा ieee80211_hdr *hdr =
		(काष्ठा ieee80211_hdr *)precvframe->pkt->data;
	काष्ठा odm_per_pkt_info	pkt_info;
	u8 *sa = शून्य;
	काष्ठा sta_priv *pstapriv;
	काष्ठा sta_info *psta;

	pkt_info.bPacketMatchBSSID = false;
	pkt_info.bPacketToSelf = false;
	pkt_info.bPacketBeacon = false;

	wlanhdr = precvframe->pkt->data;

	pkt_info.bPacketMatchBSSID = (!ieee80211_is_ctl(hdr->frame_control) &&
		!pattrib->icv_err && !pattrib->crc_err &&
		!स_भेद(get_hdr_bssid(wlanhdr),
		 get_bssid(&padapter->mlmepriv), ETH_ALEN));

	pkt_info.bPacketToSelf = pkt_info.bPacketMatchBSSID &&
				 (!स_भेद(ieee80211_get_DA(hdr),
				  myid(&padapter->eeprompriv), ETH_ALEN));

	pkt_info.bPacketBeacon = pkt_info.bPacketMatchBSSID &&
				 (GetFrameSubType(wlanhdr) == WIFI_BEACON);

	अगर (pkt_info.bPacketBeacon) अणु
		अगर (check_fwstate(&padapter->mlmepriv, WIFI_STATION_STATE))
			sa = padapter->mlmepriv.cur_network.network.MacAddress;
		/* to करो Ad-hoc */
	पूर्ण अन्यथा अणु
		sa = ieee80211_get_SA(hdr);
	पूर्ण

	pstapriv = &padapter->stapriv;
	pkt_info.StationID = 0xFF;
	psta = rtw_get_stainfo(pstapriv, sa);
	अगर (psta)
		pkt_info.StationID = psta->mac_id;
	pkt_info.Rate = pattrib->mcs_rate;

	odm_phy_status_query(&padapter->HalData->odmpriv, pPHYInfo,
			     (u8 *)pphy_status, &(pkt_info));

	precvframe->psta = शून्य;
	अगर (pkt_info.bPacketMatchBSSID &&
	    (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE))) अणु
		अगर (psta) अणु
			precvframe->psta = psta;
			rtl8188e_process_phy_info(padapter, precvframe);
		पूर्ण
	पूर्ण अन्यथा अगर (pkt_info.bPacketToSelf || pkt_info.bPacketBeacon) अणु
		अगर (check_fwstate(&padapter->mlmepriv, WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE)) अणु
			अगर (psta)
				precvframe->psta = psta;
		पूर्ण
		rtl8188e_process_phy_info(padapter, precvframe);
	पूर्ण
पूर्ण
