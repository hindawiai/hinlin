<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RECV_OSDEP_H_
#घोषणा __RECV_OSDEP_H_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

पूर्णांक _rtw_init_recv_priv(काष्ठा recv_priv *precvpriv, काष्ठा adapter *padapter);
व्योम _rtw_मुक्त_recv_priv(काष्ठा recv_priv *precvpriv);

s32  rtw_recv_entry(काष्ठा recv_frame *precv_frame);
पूर्णांक rtw_recv_indicatepkt(काष्ठा adapter *adapter,
			 काष्ठा recv_frame *recv_frame);

व्योम rtw_handle_tkip_mic_err(काष्ठा adapter *padapter, u8 bgroup);

पूर्णांक rtw_os_recvbuf_resource_alloc(काष्ठा recv_buf *precvbuf);

व्योम rtw_init_recv_समयr(काष्ठा recv_reorder_ctrl *preorder_ctrl);

#पूर्ण_अगर /*  */
