<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright(c) 2020 Intel Corporation. All rights reserved. */
#अगर_अघोषित __CXL_PCI_H__
#घोषणा __CXL_PCI_H__

#घोषणा CXL_MEMORY_PROGIF	0x10

/*
 * See section 8.1 Configuration Space Registers in the CXL 2.0
 * Specअगरication
 */
#घोषणा PCI_DVSEC_HEADER1_LENGTH_MASK	GENMASK(31, 20)
#घोषणा PCI_DVSEC_VENDOR_ID_CXL		0x1E98
#घोषणा PCI_DVSEC_ID_CXL		0x0

#घोषणा PCI_DVSEC_ID_CXL_REGLOC_OFFSET		0x8
#घोषणा PCI_DVSEC_ID_CXL_REGLOC_BLOCK1_OFFSET	0xC

/* BAR Indicator Register (BIR) */
#घोषणा CXL_REGLOC_BIR_MASK GENMASK(2, 0)

/* Register Block Identअगरier (RBI) */
#घोषणा CXL_REGLOC_RBI_MASK GENMASK(15, 8)
#घोषणा CXL_REGLOC_RBI_EMPTY 0
#घोषणा CXL_REGLOC_RBI_COMPONENT 1
#घोषणा CXL_REGLOC_RBI_VIRT 2
#घोषणा CXL_REGLOC_RBI_MEMDEV 3

#घोषणा CXL_REGLOC_ADDR_MASK GENMASK(31, 16)

#पूर्ण_अगर /* __CXL_PCI_H__ */
