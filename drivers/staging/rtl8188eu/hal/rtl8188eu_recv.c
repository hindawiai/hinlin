<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8188EU_RECV_C_
#समावेश <linux/kmemleak.h>
#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <recv_osdep.h>
#समावेश <mlme_osdep.h>

#समावेश <usb_ops_linux.h>
#समावेश <wअगरi.h>

#समावेश <rtl8188e_hal.h>

पूर्णांक rtw_hal_init_recv_priv(काष्ठा adapter *padapter)
अणु
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;
	पूर्णांक i, res = _SUCCESS;
	काष्ठा recv_buf *precvbuf;

	tasklet_setup(&precvpriv->recv_tasklet, rtl8188eu_recv_tasklet);

	/* init recv_buf */
	_rtw_init_queue(&precvpriv->मुक्त_recv_buf_queue);

	precvpriv->precv_buf =
		kसुस्मृति(NR_RECVBUFF, माप(काष्ठा recv_buf), GFP_KERNEL);
	अगर (!precvpriv->precv_buf) अणु
		res = _FAIL;
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
			 ("alloc recv_buf fail!\n"));
		जाओ निकास;
	पूर्ण
	precvbuf = precvpriv->precv_buf;

	क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
		res = rtw_os_recvbuf_resource_alloc(precvbuf);
		अगर (res == _FAIL)
			अवरोध;
		precvbuf->adapter = padapter;
		precvbuf++;
	पूर्ण
	skb_queue_head_init(&precvpriv->rx_skb_queue);
	अणु
		पूर्णांक i;
		काष्ठा sk_buff *pskb = शून्य;

		skb_queue_head_init(&precvpriv->मुक्त_recv_skb_queue);

		क्रम (i = 0; i < NR_PREALLOC_RECV_SKB; i++) अणु
			pskb = __netdev_alloc_skb(padapter->pnetdev,
						  MAX_RECVBUF_SZ, GFP_KERNEL);
			अगर (pskb) अणु
				kmemleak_not_leak(pskb);
				skb_queue_tail(&precvpriv->मुक्त_recv_skb_queue,
					       pskb);
			पूर्ण
			pskb = शून्य;
		पूर्ण
	पूर्ण
निकास:
	वापस res;
पूर्ण

व्योम rtw_hal_मुक्त_recv_priv(काष्ठा adapter *padapter)
अणु
	पूर्णांक i;
	काष्ठा recv_buf *precvbuf;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;

	precvbuf = precvpriv->precv_buf;

	क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
		usb_मुक्त_urb(precvbuf->purb);
		precvbuf++;
	पूर्ण

	kमुक्त(precvpriv->precv_buf);

	अगर (skb_queue_len(&precvpriv->rx_skb_queue))
		DBG_88E(KERN_WARNING "rx_skb_queue not empty\n");
	skb_queue_purge(&precvpriv->rx_skb_queue);

	अगर (skb_queue_len(&precvpriv->मुक्त_recv_skb_queue))
		DBG_88E(KERN_WARNING "free_recv_skb_queue not empty, %d\n",
			skb_queue_len(&precvpriv->मुक्त_recv_skb_queue));

	skb_queue_purge(&precvpriv->मुक्त_recv_skb_queue);
पूर्ण
