<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * H/W layer of ISHTP provider device (ISH)
 *
 * Copyright (c) 2014-2016, Intel Corporation.
 */

#अगर_अघोषित _ISHTP_HW_ISH_H_
#घोषणा _ISHTP_HW_ISH_H_

#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "hw-ish-regs.h"
#समावेश "ishtp-dev.h"

#घोषणा CHV_DEVICE_ID		0x22D8
#घोषणा BXT_Ax_DEVICE_ID	0x0AA2
#घोषणा BXT_Bx_DEVICE_ID	0x1AA2
#घोषणा APL_Ax_DEVICE_ID	0x5AA2
#घोषणा SPT_Ax_DEVICE_ID	0x9D35
#घोषणा CNL_Ax_DEVICE_ID	0x9DFC
#घोषणा GLK_Ax_DEVICE_ID	0x31A2
#घोषणा CNL_H_DEVICE_ID		0xA37C
#घोषणा ICL_MOBILE_DEVICE_ID	0x34FC
#घोषणा SPT_H_DEVICE_ID		0xA135
#घोषणा CML_LP_DEVICE_ID	0x02FC
#घोषणा CMP_H_DEVICE_ID		0x06FC
#घोषणा EHL_Ax_DEVICE_ID	0x4BB3
#घोषणा TGL_LP_DEVICE_ID	0xA0FC
#घोषणा TGL_H_DEVICE_ID		0x43FC
#घोषणा ADL_S_DEVICE_ID		0x7AF8
#घोषणा ADL_P_DEVICE_ID		0x51FC

#घोषणा	REVISION_ID_CHT_A0	0x6
#घोषणा	REVISION_ID_CHT_Ax_SI	0x0
#घोषणा	REVISION_ID_CHT_Bx_SI	0x10
#घोषणा	REVISION_ID_CHT_Kx_SI	0x20
#घोषणा	REVISION_ID_CHT_Dx_SI	0x30
#घोषणा	REVISION_ID_CHT_B0	0xB0
#घोषणा	REVISION_ID_SI_MASK	0x70

काष्ठा ipc_rst_payload_type अणु
	uपूर्णांक16_t	reset_id;
	uपूर्णांक16_t	reserved;
पूर्ण;

काष्ठा समय_sync_क्रमmat अणु
	uपूर्णांक8_t ts1_source;
	uपूर्णांक8_t ts2_source;
	uपूर्णांक16_t reserved;
पूर्ण __packed;

काष्ठा ipc_समय_update_msg अणु
	uपूर्णांक64_t primary_host_समय;
	काष्ठा समय_sync_क्रमmat sync_info;
	uपूर्णांक64_t secondary_host_समय;
पूर्ण __packed;

क्रमागत अणु
	HOST_UTC_TIME_USEC = 0,
	HOST_SYSTEM_TIME_USEC = 1
पूर्ण;

काष्ठा ish_hw अणु
	व्योम __iomem *mem_addr;
पूर्ण;

/*
 * ISH FW status type
 */
क्रमागत अणु
	FWSTS_AFTER_RESET		= 0,
	FWSTS_WAIT_FOR_HOST		= 4,
	FWSTS_START_KERNEL_DMA		= 5,
	FWSTS_FW_IS_RUNNING		= 7,
	FWSTS_SENSOR_APP_LOADED		= 8,
	FWSTS_SENSOR_APP_RUNNING	= 15
पूर्ण;

#घोषणा to_ish_hw(dev) (काष्ठा ish_hw *)((dev)->hw)

irqवापस_t ish_irq_handler(पूर्णांक irq, व्योम *dev_id);
काष्ठा ishtp_device *ish_dev_init(काष्ठा pci_dev *pdev);
पूर्णांक ish_hw_start(काष्ठा ishtp_device *dev);
व्योम ish_device_disable(काष्ठा ishtp_device *dev);
पूर्णांक ish_disable_dma(काष्ठा ishtp_device *dev);
व्योम ish_set_host_पढ़ोy(काष्ठा ishtp_device *dev);

#पूर्ण_अगर /* _ISHTP_HW_ISH_H_ */
