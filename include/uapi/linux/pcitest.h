<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/**
 * pcitest.h - PCI test uapi defines
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 *
 */

#अगर_अघोषित __UAPI_LINUX_PCITEST_H
#घोषणा __UAPI_LINUX_PCITEST_H

#घोषणा PCITEST_BAR		_IO('P', 0x1)
#घोषणा PCITEST_LEGACY_IRQ	_IO('P', 0x2)
#घोषणा PCITEST_MSI		_IOW('P', 0x3, पूर्णांक)
#घोषणा PCITEST_WRITE		_IOW('P', 0x4, अचिन्हित दीर्घ)
#घोषणा PCITEST_READ		_IOW('P', 0x5, अचिन्हित दीर्घ)
#घोषणा PCITEST_COPY		_IOW('P', 0x6, अचिन्हित दीर्घ)
#घोषणा PCITEST_MSIX		_IOW('P', 0x7, पूर्णांक)
#घोषणा PCITEST_SET_IRQTYPE	_IOW('P', 0x8, पूर्णांक)
#घोषणा PCITEST_GET_IRQTYPE	_IO('P', 0x9)
#घोषणा PCITEST_CLEAR_IRQ	_IO('P', 0x10)

#घोषणा PCITEST_FLAGS_USE_DMA	0x00000001

काष्ठा pci_endpoपूर्णांक_test_xfer_param अणु
	अचिन्हित दीर्घ size;
	अचिन्हित अक्षर flags;
पूर्ण;

#पूर्ण_अगर /* __UAPI_LINUX_PCITEST_H */
