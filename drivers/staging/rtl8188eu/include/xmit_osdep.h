<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __XMIT_OSDEP_H_
#घोषणा __XMIT_OSDEP_H_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#घोषणा NR_XMITFRAME	256

काष्ठा xmit_priv;
काष्ठा pkt_attrib;
काष्ठा sta_xmit_priv;
काष्ठा xmit_frame;
काष्ठा xmit_buf;

पूर्णांक rtw_xmit_entry(काष्ठा sk_buff *pkt, काष्ठा  net_device *pnetdev);

व्योम rtw_os_xmit_schedule(काष्ठा adapter *padapter);

पूर्णांक rtw_os_xmit_resource_alloc(काष्ठा xmit_buf *pxmitbuf, u32 alloc_sz);
व्योम rtw_os_xmit_resource_मुक्त(काष्ठा xmit_buf *pxmitbuf);

व्योम rtw_os_pkt_complete(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt);
व्योम rtw_os_xmit_complete(काष्ठा adapter *padapter,
			  काष्ठा xmit_frame *pxframe);

#पूर्ण_अगर /* __XMIT_OSDEP_H_ */
