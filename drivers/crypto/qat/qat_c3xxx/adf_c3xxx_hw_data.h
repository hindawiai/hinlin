<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_C3XXX_HW_DATA_H_
#घोषणा ADF_C3XXX_HW_DATA_H_

/* PCIe configuration space */
#घोषणा ADF_C3XXX_PMISC_BAR 0
#घोषणा ADF_C3XXX_ETR_BAR 1
#घोषणा ADF_C3XXX_RX_RINGS_OFFSET 8
#घोषणा ADF_C3XXX_TX_RINGS_MASK 0xFF
#घोषणा ADF_C3XXX_MAX_ACCELERATORS 3
#घोषणा ADF_C3XXX_MAX_ACCELENGINES 6
#घोषणा ADF_C3XXX_ACCELERATORS_REG_OFFSET 16
#घोषणा ADF_C3XXX_ACCELERATORS_MASK 0x7
#घोषणा ADF_C3XXX_ACCELENGINES_MASK 0x3F
#घोषणा ADF_C3XXX_ETR_MAX_BANKS 16
#घोषणा ADF_C3XXX_SMIAPF0_MASK_OFFSET (0x3A000 + 0x28)
#घोषणा ADF_C3XXX_SMIAPF1_MASK_OFFSET (0x3A000 + 0x30)
#घोषणा ADF_C3XXX_SMIA0_MASK 0xFFFF
#घोषणा ADF_C3XXX_SMIA1_MASK 0x1
#घोषणा ADF_C3XXX_SOFTSTRAP_CSR_OFFSET 0x2EC
/* Error detection and correction */
#घोषणा ADF_C3XXX_AE_CTX_ENABLES(i) (i * 0x1000 + 0x20818)
#घोषणा ADF_C3XXX_AE_MISC_CONTROL(i) (i * 0x1000 + 0x20960)
#घोषणा ADF_C3XXX_ENABLE_AE_ECC_ERR BIT(28)
#घोषणा ADF_C3XXX_ENABLE_AE_ECC_PARITY_CORR (BIT(24) | BIT(12))
#घोषणा ADF_C3XXX_UERRSSMSH(i) (i * 0x4000 + 0x18)
#घोषणा ADF_C3XXX_CERRSSMSH(i) (i * 0x4000 + 0x10)
#घोषणा ADF_C3XXX_ERRSSMSH_EN BIT(3)

#घोषणा ADF_C3XXX_PF2VF_OFFSET(i)	(0x3A000 + 0x280 + ((i) * 0x04))
#घोषणा ADF_C3XXX_VINTMSK_OFFSET(i)	(0x3A000 + 0x200 + ((i) * 0x04))

/* AE to function mapping */
#घोषणा ADF_C3XXX_AE2FUNC_MAP_GRP_A_NUM_REGS 48
#घोषणा ADF_C3XXX_AE2FUNC_MAP_GRP_B_NUM_REGS 6

/* Firmware Binary */
#घोषणा ADF_C3XXX_FW "qat_c3xxx.bin"
#घोषणा ADF_C3XXX_MMP "qat_c3xxx_mmp.bin"

व्योम adf_init_hw_data_c3xxx(काष्ठा adf_hw_device_data *hw_data);
व्योम adf_clean_hw_data_c3xxx(काष्ठा adf_hw_device_data *hw_data);
#पूर्ण_अगर
