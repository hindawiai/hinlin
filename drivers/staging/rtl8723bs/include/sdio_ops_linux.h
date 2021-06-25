<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __SDIO_OPS_LINUX_H__
#घोषणा __SDIO_OPS_LINUX_H__

#घोषणा SDIO_ERR_VAL8	0xEA
#घोषणा SDIO_ERR_VAL16	0xEAEA
#घोषणा SDIO_ERR_VAL32	0xEAEAEAEA

u8 sd_f0_पढ़ो8(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, s32 *err);

s32 _sd_cmd52_पढ़ो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pdata);
s32 _sd_cmd52_ग_लिखो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pdata);
s32 sd_cmd52_पढ़ो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pdata);
s32 sd_cmd52_ग_लिखो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pdata);

u8 sd_पढ़ो8(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, s32 *err);
u32 sd_पढ़ो32(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, s32 *err);
s32 _sd_पढ़ो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, व्योम *pdata);
s32 sd_पढ़ो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, व्योम *pdata);
व्योम sd_ग_लिखो8(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u8 v, s32 *err);
व्योम sd_ग_लिखो32(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 v, s32 *err);
s32 _sd_ग_लिखो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, व्योम *pdata);
s32 sd_ग_लिखो(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, व्योम *pdata);


व्योम rtw_sdio_set_irq_thd(काष्ठा dvobj_priv *dvobj, व्योम *thd_hdl);
#पूर्ण_अगर
