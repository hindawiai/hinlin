<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __XMIT_OSDEP_H_
#घोषणा __XMIT_OSDEP_H_


काष्ठा pkt_file अणु
	काष्ठा sk_buff *pkt;
	__kernel_माप_प्रकार pkt_len;	 /* the reमुख्यder length of the खोलो_file */
	अचिन्हित अक्षर *cur_buffer;
	u8 *buf_start;
	u8 *cur_addr;
	__kernel_माप_प्रकार buf_len;
पूर्ण;

#घोषणा NR_XMITFRAME	256

काष्ठा xmit_priv;
काष्ठा pkt_attrib;
काष्ठा sta_xmit_priv;
काष्ठा xmit_frame;
काष्ठा xmit_buf;

बाह्य पूर्णांक _rtw_xmit_entry(काष्ठा sk_buff *pkt, काष्ठा net_device *pnetdev);
बाह्य पूर्णांक rtw_xmit_entry(काष्ठा sk_buff *pkt, काष्ठा net_device *pnetdev);

व्योम rtw_os_xmit_schedule(काष्ठा adapter *padapter);

पूर्णांक rtw_os_xmit_resource_alloc(काष्ठा adapter *padapter, काष्ठा xmit_buf *pxmitbuf, u32 alloc_sz, u8 flag);
व्योम rtw_os_xmit_resource_मुक्त(काष्ठा adapter *padapter, काष्ठा xmit_buf *pxmitbuf, u32 मुक्त_sz, u8 flag);

बाह्य uपूर्णांक rtw_reमुख्यder_len(काष्ठा pkt_file *pfile);
बाह्य व्योम _rtw_खोलो_pktfile(काष्ठा sk_buff *pkt, काष्ठा pkt_file *pfile);
बाह्य uपूर्णांक _rtw_pktfile_पढ़ो(काष्ठा pkt_file *pfile, u8 *rmem, uपूर्णांक rlen);
बाह्य चिन्हित पूर्णांक rtw_enकरोfpktfile(काष्ठा pkt_file *pfile);

बाह्य व्योम rtw_os_pkt_complete(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt);
बाह्य व्योम rtw_os_xmit_complete(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxframe);

#पूर्ण_अगर /* __XMIT_OSDEP_H_ */
