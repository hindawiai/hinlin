<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause */
/*
 * Copyright 2018-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित _EFA_REGS_H_
#घोषणा _EFA_REGS_H_

क्रमागत efa_regs_reset_reason_types अणु
	EFA_REGS_RESET_NORMAL                       = 0,
	/* Keep alive समयout */
	EFA_REGS_RESET_KEEP_ALIVE_TO                = 1,
	EFA_REGS_RESET_ADMIN_TO                     = 2,
	EFA_REGS_RESET_INIT_ERR                     = 3,
	EFA_REGS_RESET_DRIVER_INVALID_STATE         = 4,
	EFA_REGS_RESET_OS_TRIGGER                   = 5,
	EFA_REGS_RESET_SHUTDOWN                     = 6,
	EFA_REGS_RESET_USER_TRIGGER                 = 7,
	EFA_REGS_RESET_GENERIC                      = 8,
पूर्ण;

/* efa_रेजिस्टरs offsets */

/* 0 base */
#घोषणा EFA_REGS_VERSION_OFF                                0x0
#घोषणा EFA_REGS_CONTROLLER_VERSION_OFF                     0x4
#घोषणा EFA_REGS_CAPS_OFF                                   0x8
#घोषणा EFA_REGS_AQ_BASE_LO_OFF                             0x10
#घोषणा EFA_REGS_AQ_BASE_HI_OFF                             0x14
#घोषणा EFA_REGS_AQ_CAPS_OFF                                0x18
#घोषणा EFA_REGS_ACQ_BASE_LO_OFF                            0x20
#घोषणा EFA_REGS_ACQ_BASE_HI_OFF                            0x24
#घोषणा EFA_REGS_ACQ_CAPS_OFF                               0x28
#घोषणा EFA_REGS_AQ_PROD_DB_OFF                             0x2c
#घोषणा EFA_REGS_AENQ_CAPS_OFF                              0x34
#घोषणा EFA_REGS_AENQ_BASE_LO_OFF                           0x38
#घोषणा EFA_REGS_AENQ_BASE_HI_OFF                           0x3c
#घोषणा EFA_REGS_AENQ_CONS_DB_OFF                           0x40
#घोषणा EFA_REGS_INTR_MASK_OFF                              0x4c
#घोषणा EFA_REGS_DEV_CTL_OFF                                0x54
#घोषणा EFA_REGS_DEV_STS_OFF                                0x58
#घोषणा EFA_REGS_MMIO_REG_READ_OFF                          0x5c
#घोषणा EFA_REGS_MMIO_RESP_LO_OFF                           0x60
#घोषणा EFA_REGS_MMIO_RESP_HI_OFF                           0x64

/* version रेजिस्टर */
#घोषणा EFA_REGS_VERSION_MINOR_VERSION_MASK                 0xff
#घोषणा EFA_REGS_VERSION_MAJOR_VERSION_MASK                 0xff00

/* controller_version रेजिस्टर */
#घोषणा EFA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION_MASK   0xff
#घोषणा EFA_REGS_CONTROLLER_VERSION_MINOR_VERSION_MASK      0xff00
#घोषणा EFA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_MASK      0xff0000
#घोषणा EFA_REGS_CONTROLLER_VERSION_IMPL_ID_MASK            0xff000000

/* caps रेजिस्टर */
#घोषणा EFA_REGS_CAPS_CONTIGUOUS_QUEUE_REQUIRED_MASK        0x1
#घोषणा EFA_REGS_CAPS_RESET_TIMEOUT_MASK                    0x3e
#घोषणा EFA_REGS_CAPS_DMA_ADDR_WIDTH_MASK                   0xff00
#घोषणा EFA_REGS_CAPS_ADMIN_CMD_TO_MASK                     0xf0000

/* aq_caps रेजिस्टर */
#घोषणा EFA_REGS_AQ_CAPS_AQ_DEPTH_MASK                      0xffff
#घोषणा EFA_REGS_AQ_CAPS_AQ_ENTRY_SIZE_MASK                 0xffff0000

/* acq_caps रेजिस्टर */
#घोषणा EFA_REGS_ACQ_CAPS_ACQ_DEPTH_MASK                    0xffff
#घोषणा EFA_REGS_ACQ_CAPS_ACQ_ENTRY_SIZE_MASK               0xff0000
#घोषणा EFA_REGS_ACQ_CAPS_ACQ_MSIX_VECTOR_MASK              0xff000000

/* aenq_caps रेजिस्टर */
#घोषणा EFA_REGS_AENQ_CAPS_AENQ_DEPTH_MASK                  0xffff
#घोषणा EFA_REGS_AENQ_CAPS_AENQ_ENTRY_SIZE_MASK             0xff0000
#घोषणा EFA_REGS_AENQ_CAPS_AENQ_MSIX_VECTOR_MASK            0xff000000

/* पूर्णांकr_mask रेजिस्टर */
#घोषणा EFA_REGS_INTR_MASK_EN_MASK                          0x1

/* dev_ctl रेजिस्टर */
#घोषणा EFA_REGS_DEV_CTL_DEV_RESET_MASK                     0x1
#घोषणा EFA_REGS_DEV_CTL_AQ_RESTART_MASK                    0x2
#घोषणा EFA_REGS_DEV_CTL_RESET_REASON_MASK                  0xf0000000

/* dev_sts रेजिस्टर */
#घोषणा EFA_REGS_DEV_STS_READY_MASK                         0x1
#घोषणा EFA_REGS_DEV_STS_AQ_RESTART_IN_PROGRESS_MASK        0x2
#घोषणा EFA_REGS_DEV_STS_AQ_RESTART_FINISHED_MASK           0x4
#घोषणा EFA_REGS_DEV_STS_RESET_IN_PROGRESS_MASK             0x8
#घोषणा EFA_REGS_DEV_STS_RESET_FINISHED_MASK                0x10
#घोषणा EFA_REGS_DEV_STS_FATAL_ERROR_MASK                   0x20

/* mmio_reg_पढ़ो रेजिस्टर */
#घोषणा EFA_REGS_MMIO_REG_READ_REQ_ID_MASK                  0xffff
#घोषणा EFA_REGS_MMIO_REG_READ_REG_OFF_MASK                 0xffff0000

#पूर्ण_अगर /* _EFA_REGS_H_ */
