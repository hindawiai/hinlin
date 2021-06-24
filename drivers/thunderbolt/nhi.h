<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Thunderbolt driver - NHI driver
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#अगर_अघोषित DSL3510_H_
#घोषणा DSL3510_H_

#समावेश <linux/thunderbolt.h>

क्रमागत nhi_fw_mode अणु
	NHI_FW_SAFE_MODE,
	NHI_FW_AUTH_MODE,
	NHI_FW_EP_MODE,
	NHI_FW_CM_MODE,
पूर्ण;

क्रमागत nhi_mailbox_cmd अणु
	NHI_MAILBOX_SAVE_DEVS = 0x05,
	NHI_MAILBOX_DISCONNECT_PCIE_PATHS = 0x06,
	NHI_MAILBOX_DRV_UNLOADS = 0x07,
	NHI_MAILBOX_DISCONNECT_PA = 0x10,
	NHI_MAILBOX_DISCONNECT_PB = 0x11,
	NHI_MAILBOX_ALLOW_ALL_DEVS = 0x23,
पूर्ण;

पूर्णांक nhi_mailbox_cmd(काष्ठा tb_nhi *nhi, क्रमागत nhi_mailbox_cmd cmd, u32 data);
क्रमागत nhi_fw_mode nhi_mailbox_mode(काष्ठा tb_nhi *nhi);

/**
 * काष्ठा tb_nhi_ops - NHI specअगरic optional operations
 * @init: NHI specअगरic initialization
 * @suspend_noirq: NHI specअगरic suspend_noirq hook
 * @resume_noirq: NHI specअगरic resume_noirq hook
 * @runसमय_suspend: NHI specअगरic runसमय_suspend hook
 * @runसमय_resume: NHI specअगरic runसमय_resume hook
 * @shutकरोwn: NHI specअगरic shutकरोwn
 */
काष्ठा tb_nhi_ops अणु
	पूर्णांक (*init)(काष्ठा tb_nhi *nhi);
	पूर्णांक (*suspend_noirq)(काष्ठा tb_nhi *nhi, bool wakeup);
	पूर्णांक (*resume_noirq)(काष्ठा tb_nhi *nhi);
	पूर्णांक (*runसमय_suspend)(काष्ठा tb_nhi *nhi);
	पूर्णांक (*runसमय_resume)(काष्ठा tb_nhi *nhi);
	व्योम (*shutकरोwn)(काष्ठा tb_nhi *nhi);
पूर्ण;

बाह्य स्थिर काष्ठा tb_nhi_ops icl_nhi_ops;

/*
 * PCI IDs used in this driver from Win Ridge क्रमward. There is no
 * need क्रम the PCI quirk anymore as we will use ICM also on Apple
 * hardware.
 */
#घोषणा PCI_DEVICE_ID_INTEL_MAPLE_RIDGE_4C_NHI		0x1137
#घोषणा PCI_DEVICE_ID_INTEL_WIN_RIDGE_2C_NHI            0x157d
#घोषणा PCI_DEVICE_ID_INTEL_WIN_RIDGE_2C_BRIDGE         0x157e
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_NHI		0x15bf
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_BRIDGE	0x15c0
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_NHI	0x15d2
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_BRIDGE	0x15d3
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_NHI	0x15d9
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_BRIDGE	0x15da
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_USBONLY_NHI	0x15dc
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_USBONLY_NHI	0x15dd
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_USBONLY_NHI	0x15de
#घोषणा PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_BRIDGE	0x15e7
#घोषणा PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_NHI		0x15e8
#घोषणा PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_BRIDGE	0x15ea
#घोषणा PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_NHI		0x15eb
#घोषणा PCI_DEVICE_ID_INTEL_TITAN_RIDGE_DD_BRIDGE	0x15ef
#घोषणा PCI_DEVICE_ID_INTEL_ICL_NHI1			0x8a0d
#घोषणा PCI_DEVICE_ID_INTEL_ICL_NHI0			0x8a17
#घोषणा PCI_DEVICE_ID_INTEL_TGL_NHI0			0x9a1b
#घोषणा PCI_DEVICE_ID_INTEL_TGL_NHI1			0x9a1d
#घोषणा PCI_DEVICE_ID_INTEL_TGL_H_NHI0			0x9a1f
#घोषणा PCI_DEVICE_ID_INTEL_TGL_H_NHI1			0x9a21

#घोषणा PCI_CLASS_SERIAL_USB_USB4			0x0c0340

#पूर्ण_अगर
