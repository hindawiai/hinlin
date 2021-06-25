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
#अगर_अघोषित __XMIT_OSDEP_H_
#घोषणा __XMIT_OSDEP_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

काष्ठा pkt_file अणु
	_pkt	*pkt;
	u32	pkt_len;	 /*the reमुख्यder length of the खोलो_file*/
	_buffer	*cur_buffer;
	u8	*buf_start;
	u8	*cur_addr;
	u32	buf_len;
पूर्ण;

#घोषणा NR_XMITFRAME	256

काष्ठा xmit_priv;
काष्ठा pkt_attrib;
काष्ठा sta_xmit_priv;
काष्ठा xmit_frame;
काष्ठा xmit_buf;

पूर्णांक r8712_xmit_entry(_pkt *pkt, काष्ठा  net_device *pnetdev);
व्योम r8712_SetFilter(काष्ठा work_काष्ठा *work);
पूर्णांक r8712_xmit_resource_alloc(काष्ठा _adapter *padapter,
			      काष्ठा xmit_buf *pxmitbuf);
व्योम r8712_xmit_resource_मुक्त(काष्ठा _adapter *padapter,
			      काष्ठा xmit_buf *pxmitbuf);

व्योम r8712_set_qos(काष्ठा pkt_file *ppktfile,
		   काष्ठा pkt_attrib *pattrib);
व्योम _r8712_खोलो_pktfile(_pkt *pktptr, काष्ठा pkt_file *pfile);
uपूर्णांक _r8712_pktfile_पढ़ो(काष्ठा pkt_file *pfile, u8 *rmem, uपूर्णांक rlen);
sपूर्णांक r8712_enकरोfpktfile(काष्ठा pkt_file *pfile);
व्योम r8712_xmit_complete(काष्ठा _adapter *padapter,
			 काष्ठा xmit_frame *pxframe);

#पूर्ण_अगर
