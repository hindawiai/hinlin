<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Low-level API.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#अगर_अघोषित WFX_HWIO_H
#घोषणा WFX_HWIO_H

#समावेश <linux/types.h>

काष्ठा wfx_dev;

पूर्णांक wfx_data_पढ़ो(काष्ठा wfx_dev *wdev, व्योम *buf, माप_प्रकार buf_len);
पूर्णांक wfx_data_ग_लिखो(काष्ठा wfx_dev *wdev, स्थिर व्योम *buf, माप_प्रकार buf_len);

पूर्णांक sram_buf_पढ़ो(काष्ठा wfx_dev *wdev, u32 addr, व्योम *buf, माप_प्रकार len);
पूर्णांक sram_buf_ग_लिखो(काष्ठा wfx_dev *wdev, u32 addr, स्थिर व्योम *buf, माप_प्रकार len);

पूर्णांक ahb_buf_पढ़ो(काष्ठा wfx_dev *wdev, u32 addr, व्योम *buf, माप_प्रकार len);
पूर्णांक ahb_buf_ग_लिखो(काष्ठा wfx_dev *wdev, u32 addr, स्थिर व्योम *buf, माप_प्रकार len);

पूर्णांक sram_reg_पढ़ो(काष्ठा wfx_dev *wdev, u32 addr, u32 *val);
पूर्णांक sram_reg_ग_लिखो(काष्ठा wfx_dev *wdev, u32 addr, u32 val);

पूर्णांक ahb_reg_पढ़ो(काष्ठा wfx_dev *wdev, u32 addr, u32 *val);
पूर्णांक ahb_reg_ग_लिखो(काष्ठा wfx_dev *wdev, u32 addr, u32 val);

#घोषणा CFG_ERR_SPI_FRAME          0x00000001 // only with SPI
#घोषणा CFG_ERR_SDIO_BUF_MISMATCH  0x00000001 // only with SDIO
#घोषणा CFG_ERR_BUF_UNDERRUN       0x00000002
#घोषणा CFG_ERR_DATA_IN_TOO_LARGE  0x00000004
#घोषणा CFG_ERR_HOST_NO_OUT_QUEUE  0x00000008
#घोषणा CFG_ERR_BUF_OVERRUN        0x00000010
#घोषणा CFG_ERR_DATA_OUT_TOO_LARGE 0x00000020
#घोषणा CFG_ERR_HOST_NO_IN_QUEUE   0x00000040
#घोषणा CFG_ERR_HOST_CRC_MISS      0x00000080 // only with SDIO
#घोषणा CFG_SPI_IGNORE_CS          0x00000080 // only with SPI
#घोषणा CFG_BYTE_ORDER_MASK        0x00000300 // only writable with SPI
#घोषणा     CFG_BYTE_ORDER_BADC    0x00000000
#घोषणा     CFG_BYTE_ORDER_DCBA    0x00000100
#घोषणा     CFG_BYTE_ORDER_ABCD    0x00000200 // SDIO always use this value
#घोषणा CFG_सूचीECT_ACCESS_MODE     0x00000400
#घोषणा CFG_PREFETCH_AHB           0x00000800
#घोषणा CFG_DISABLE_CPU_CLK        0x00001000
#घोषणा CFG_PREFETCH_SRAM          0x00002000
#घोषणा CFG_CPU_RESET              0x00004000
#घोषणा CFG_SDIO_DISABLE_IRQ       0x00008000 // only with SDIO
#घोषणा CFG_IRQ_ENABLE_DATA        0x00010000
#घोषणा CFG_IRQ_ENABLE_WRDY        0x00020000
#घोषणा CFG_CLK_RISE_EDGE          0x00040000
#घोषणा CFG_SDIO_DISABLE_CRC_CHK   0x00080000 // only with SDIO
#घोषणा CFG_RESERVED               0x00F00000
#घोषणा CFG_DEVICE_ID_MAJOR        0x07000000
#घोषणा CFG_DEVICE_ID_RESERVED     0x78000000
#घोषणा CFG_DEVICE_ID_TYPE         0x80000000
पूर्णांक config_reg_पढ़ो(काष्ठा wfx_dev *wdev, u32 *val);
पूर्णांक config_reg_ग_लिखो(काष्ठा wfx_dev *wdev, u32 val);
पूर्णांक config_reg_ग_लिखो_bits(काष्ठा wfx_dev *wdev, u32 mask, u32 val);

#घोषणा CTRL_NEXT_LEN_MASK   0x00000FFF
#घोषणा CTRL_WLAN_WAKEUP     0x00001000
#घोषणा CTRL_WLAN_READY      0x00002000
पूर्णांक control_reg_पढ़ो(काष्ठा wfx_dev *wdev, u32 *val);
पूर्णांक control_reg_ग_लिखो(काष्ठा wfx_dev *wdev, u32 val);
पूर्णांक control_reg_ग_लिखो_bits(काष्ठा wfx_dev *wdev, u32 mask, u32 val);

#घोषणा IGPR_RW          0x80000000
#घोषणा IGPR_INDEX       0x7F000000
#घोषणा IGPR_VALUE       0x00FFFFFF
पूर्णांक igpr_reg_पढ़ो(काष्ठा wfx_dev *wdev, पूर्णांक index, u32 *val);
पूर्णांक igpr_reg_ग_लिखो(काष्ठा wfx_dev *wdev, पूर्णांक index, u32 val);

#पूर्ण_अगर /* WFX_HWIO_H */
