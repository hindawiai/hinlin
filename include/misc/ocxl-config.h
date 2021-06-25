<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#अगर_अघोषित _OCXL_CONFIG_H_
#घोषणा _OCXL_CONFIG_H_

/*
 * This file lists the various स्थिरants used to पढ़ो the
 * configuration space of an खोलोcapi adapter.
 *
 * It follows the specअगरication क्रम खोलोcapi 3.0
 */

#घोषणा OCXL_EXT_CAP_ID_DVSEC                 0x23

#घोषणा OCXL_DVSEC_VENDOR_OFFSET              0x4
#घोषणा OCXL_DVSEC_ID_OFFSET                  0x8
#घोषणा OCXL_DVSEC_TL_ID                      0xF000
#घोषणा   OCXL_DVSEC_TL_BACKOFF_TIMERS          0x10
#घोषणा   OCXL_DVSEC_TL_RECV_CAP                0x18
#घोषणा   OCXL_DVSEC_TL_SEND_CAP                0x20
#घोषणा   OCXL_DVSEC_TL_RECV_RATE               0x30
#घोषणा   OCXL_DVSEC_TL_SEND_RATE               0x50
#घोषणा OCXL_DVSEC_FUNC_ID                    0xF001
#घोषणा   OCXL_DVSEC_FUNC_OFF_INDEX             0x08
#घोषणा   OCXL_DVSEC_FUNC_OFF_ACTAG             0x0C
#घोषणा OCXL_DVSEC_AFU_INFO_ID                0xF003
#घोषणा   OCXL_DVSEC_AFU_INFO_AFU_IDX           0x0A
#घोषणा   OCXL_DVSEC_AFU_INFO_OFF               0x0C
#घोषणा   OCXL_DVSEC_AFU_INFO_DATA              0x10
#घोषणा OCXL_DVSEC_AFU_CTRL_ID                0xF004
#घोषणा   OCXL_DVSEC_AFU_CTRL_AFU_IDX           0x0A
#घोषणा   OCXL_DVSEC_AFU_CTRL_TERM_PASID        0x0C
#घोषणा   OCXL_DVSEC_AFU_CTRL_ENABLE            0x0F
#घोषणा   OCXL_DVSEC_AFU_CTRL_PASID_SUP         0x10
#घोषणा   OCXL_DVSEC_AFU_CTRL_PASID_EN          0x11
#घोषणा   OCXL_DVSEC_AFU_CTRL_PASID_BASE        0x14
#घोषणा   OCXL_DVSEC_AFU_CTRL_ACTAG_SUP         0x18
#घोषणा   OCXL_DVSEC_AFU_CTRL_ACTAG_EN          0x1A
#घोषणा   OCXL_DVSEC_AFU_CTRL_ACTAG_BASE        0x1C
#घोषणा OCXL_DVSEC_VENDOR_ID                  0xF0F0
#घोषणा   OCXL_DVSEC_VENDOR_CFG_VERS            0x0C
#घोषणा   OCXL_DVSEC_VENDOR_TLX_VERS            0x10
#घोषणा   OCXL_DVSEC_VENDOR_DLX_VERS            0x20
#घोषणा   OCXL_DVSEC_VENDOR_RESET_RELOAD        0x38

#पूर्ण_अगर /* _OCXL_CONFIG_H_ */
