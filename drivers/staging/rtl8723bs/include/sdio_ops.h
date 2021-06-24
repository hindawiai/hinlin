<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __SDIO_OPS_H__
#घोषणा __SDIO_OPS_H__


#समावेश <sdio_ops_linux.h>

बाह्य व्योम sdio_set_पूर्णांकf_ops(काष्ठा adapter *padapter, काष्ठा _io_ops *pops);

/* बाह्य व्योम sdio_func1cmd52_पढ़ो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *rmem); */
/* बाह्य व्योम sdio_func1cmd52_ग_लिखो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *wmem); */
बाह्य u8 SdioLocalCmd52Read1Byte(काष्ठा adapter *padapter, u32 addr);
बाह्य व्योम SdioLocalCmd52Write1Byte(काष्ठा adapter *padapter, u32 addr, u8 v);
बाह्य s32 sdio_local_पढ़ो(काष्ठा adapter *padapter, u32 addr, u32 cnt, u8 *pbuf);
बाह्य s32 sdio_local_ग_लिखो(काष्ठा adapter *padapter, u32 addr, u32 cnt, u8 *pbuf);

u32 _sdio_पढ़ो32(काष्ठा adapter *padapter, u32 addr);
s32 _sdio_ग_लिखो32(काष्ठा adapter *padapter, u32 addr, u32 val);

बाह्य व्योम sd_पूर्णांक_hdl(काष्ठा adapter *padapter);
बाह्य u8 CheckIPSStatus(काष्ठा adapter *padapter);

बाह्य व्योम InitInterrupt8723BSdio(काष्ठा adapter *padapter);
बाह्य व्योम InitSysInterrupt8723BSdio(काष्ठा adapter *padapter);
बाह्य व्योम EnableInterrupt8723BSdio(काष्ठा adapter *padapter);
बाह्य व्योम DisableInterrupt8723BSdio(काष्ठा adapter *padapter);
बाह्य u8 HalQueryTxBufferStatus8723BSdio(काष्ठा adapter *padapter);
बाह्य व्योम HalQueryTxOQTBufferStatus8723BSdio(काष्ठा adapter *padapter);
#पूर्ण_अगर /*  !__SDIO_OPS_H__ */
