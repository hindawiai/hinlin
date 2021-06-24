<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RECV_OSDEP_H_
#घोषणा __RECV_OSDEP_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश <linux/skbuff.h>

व्योम _r8712_init_recv_priv(काष्ठा recv_priv *precvpriv,
			   काष्ठा _adapter *padapter);
व्योम _r8712_मुक्त_recv_priv(काष्ठा recv_priv *precvpriv);
व्योम r8712_recv_entry(जोड़ recv_frame *precv_frame);
व्योम r8712_recv_indicatepkt(काष्ठा _adapter *adapter,
			    जोड़ recv_frame *precv_frame);
व्योम r8712_handle_tkip_mic_err(काष्ठा _adapter *padapter, u8 bgroup);
व्योम r8712_init_recv_priv(काष्ठा recv_priv *precvpriv,
			  काष्ठा _adapter *padapter);
व्योम r8712_मुक्त_recv_priv(काष्ठा recv_priv *precvpriv);
व्योम r8712_os_recv_resource_alloc(काष्ठा _adapter *padapter,
				  जोड़ recv_frame *precvframe);
पूर्णांक r8712_os_recvbuf_resource_alloc(काष्ठा _adapter *padapter,
				    काष्ठा recv_buf *precvbuf);
व्योम r8712_os_recvbuf_resource_मुक्त(काष्ठा _adapter *padapter,
				    काष्ठा recv_buf *precvbuf);
व्योम r8712_init_recv_समयr(काष्ठा recv_reorder_ctrl *preorder_ctrl);

#पूर्ण_अगर
