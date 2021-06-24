<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RECV_OSDEP_H_
#घोषणा __RECV_OSDEP_H_


बाह्य चिन्हित पूर्णांक _rtw_init_recv_priv(काष्ठा recv_priv *precvpriv, काष्ठा adapter *padapter);
बाह्य व्योम _rtw_मुक्त_recv_priv(काष्ठा recv_priv *precvpriv);


बाह्य s32  rtw_recv_entry(जोड़ recv_frame *precv_frame);
बाह्य पूर्णांक rtw_recv_indicatepkt(काष्ठा adapter *adapter, जोड़ recv_frame *precv_frame);
बाह्य व्योम rtw_recv_वापसpacket(काष्ठा net_device *cnxt, काष्ठा sk_buff *pवापसedpkt);

बाह्य व्योम rtw_handle_tkip_mic_err(काष्ठा adapter *padapter, u8 bgroup);

पूर्णांक	rtw_init_recv_priv(काष्ठा recv_priv *precvpriv, काष्ठा adapter *padapter);
व्योम rtw_मुक्त_recv_priv(काष्ठा recv_priv *precvpriv);


व्योम rtw_os_recv_resource_alloc(काष्ठा adapter *padapter, जोड़ recv_frame *precvframe);
व्योम rtw_os_recv_resource_मुक्त(काष्ठा recv_priv *precvpriv);


व्योम rtw_os_मुक्त_recvframe(जोड़ recv_frame *precvframe);


व्योम rtw_os_recvbuf_resource_मुक्त(काष्ठा adapter *padapter, काष्ठा recv_buf *precvbuf);

काष्ठा sk_buff *rtw_os_alloc_msdu_pkt(जोड़ recv_frame *prframe, u16 nSubframe_Length, u8 *pdata);
व्योम rtw_os_recv_indicate_pkt(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt, काष्ठा rx_pkt_attrib *pattrib);

व्योम rtw_init_recv_समयr(काष्ठा recv_reorder_ctrl *preorder_ctrl);


#पूर्ण_अगर /*  */
