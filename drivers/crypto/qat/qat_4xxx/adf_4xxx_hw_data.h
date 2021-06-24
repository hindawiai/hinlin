<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_4XXX_HW_DATA_H_
#घोषणा ADF_4XXX_HW_DATA_H_

#समावेश <adf_accel_devices.h>

/* PCIe configuration space */
#घोषणा ADF_4XXX_SRAM_BAR		0
#घोषणा ADF_4XXX_PMISC_BAR		1
#घोषणा ADF_4XXX_ETR_BAR		2
#घोषणा ADF_4XXX_RX_RINGS_OFFSET	1
#घोषणा ADF_4XXX_TX_RINGS_MASK		0x1
#घोषणा ADF_4XXX_MAX_ACCELERATORS	1
#घोषणा ADF_4XXX_MAX_ACCELENGINES	9
#घोषणा ADF_4XXX_BAR_MASK		(BIT(0) | BIT(2) | BIT(4))

/* Physical function fuses */
#घोषणा ADF_4XXX_FUSECTL0_OFFSET	(0x2C8)
#घोषणा ADF_4XXX_FUSECTL1_OFFSET	(0x2CC)
#घोषणा ADF_4XXX_FUSECTL2_OFFSET	(0x2D0)
#घोषणा ADF_4XXX_FUSECTL3_OFFSET	(0x2D4)
#घोषणा ADF_4XXX_FUSECTL4_OFFSET	(0x2D8)
#घोषणा ADF_4XXX_FUSECTL5_OFFSET	(0x2DC)

#घोषणा ADF_4XXX_ACCELERATORS_MASK	(0x1)
#घोषणा ADF_4XXX_ACCELENGINES_MASK	(0x1FF)
#घोषणा ADF_4XXX_ADMIN_AE_MASK		(0x100)

#घोषणा ADF_4XXX_ETR_MAX_BANKS		64

/* MSIX पूर्णांकerrupt */
#घोषणा ADF_4XXX_SMIAPF_RP_X0_MASK_OFFSET	(0x41A040)
#घोषणा ADF_4XXX_SMIAPF_RP_X1_MASK_OFFSET	(0x41A044)
#घोषणा ADF_4XXX_SMIAPF_MASK_OFFSET		(0x41A084)
#घोषणा ADF_4XXX_MSIX_RTTABLE_OFFSET(i)		(0x409000 + ((i) * 0x04))

/* Bank and ring configuration */
#घोषणा ADF_4XXX_NUM_RINGS_PER_BANK	2

/* Error source रेजिस्टरs */
#घोषणा ADF_4XXX_ERRSOU0	(0x41A200)
#घोषणा ADF_4XXX_ERRSOU1	(0x41A204)
#घोषणा ADF_4XXX_ERRSOU2	(0x41A208)
#घोषणा ADF_4XXX_ERRSOU3	(0x41A20C)

/* Error source mask रेजिस्टरs */
#घोषणा ADF_4XXX_ERRMSK0	(0x41A210)
#घोषणा ADF_4XXX_ERRMSK1	(0x41A214)
#घोषणा ADF_4XXX_ERRMSK2	(0x41A218)
#घोषणा ADF_4XXX_ERRMSK3	(0x41A21C)

#घोषणा ADF_4XXX_VFLNOTIFY	BIT(7)

/* Arbiter configuration */
#घोषणा ADF_4XXX_ARB_CONFIG			(BIT(31) | BIT(6) | BIT(0))
#घोषणा ADF_4XXX_ARB_OFFSET			(0x0)
#घोषणा ADF_4XXX_ARB_WRK_2_SER_MAP_OFFSET	(0x400)

/* Admin Interface Reg Offset */
#घोषणा ADF_4XXX_ADMINMSGUR_OFFSET	(0x500574)
#घोषणा ADF_4XXX_ADMINMSGLR_OFFSET	(0x500578)
#घोषणा ADF_4XXX_MAILBOX_BASE_OFFSET	(0x600970)

/* Firmware Binaries */
#घोषणा ADF_4XXX_FW		"qat_4xxx.bin"
#घोषणा ADF_4XXX_MMP		"qat_4xxx_mmp.bin"
#घोषणा ADF_4XXX_SYM_OBJ	"qat_4xxx_sym.bin"
#घोषणा ADF_4XXX_ASYM_OBJ	"qat_4xxx_asym.bin"
#घोषणा ADF_4XXX_ADMIN_OBJ	"qat_4xxx_admin.bin"

/* qat_4xxx fuse bits are dअगरferent from old GENs, redefine them */
क्रमागत icp_qat_4xxx_slice_mask अणु
	ICP_ACCEL_4XXX_MASK_CIPHER_SLICE = BIT(0),
	ICP_ACCEL_4XXX_MASK_AUTH_SLICE = BIT(1),
	ICP_ACCEL_4XXX_MASK_PKE_SLICE = BIT(2),
	ICP_ACCEL_4XXX_MASK_COMPRESS_SLICE = BIT(3),
	ICP_ACCEL_4XXX_MASK_UCS_SLICE = BIT(4),
	ICP_ACCEL_4XXX_MASK_EIA3_SLICE = BIT(5),
	ICP_ACCEL_4XXX_MASK_SMX_SLICE = BIT(6),
पूर्ण;

व्योम adf_init_hw_data_4xxx(काष्ठा adf_hw_device_data *hw_data);
व्योम adf_clean_hw_data_4xxx(काष्ठा adf_hw_device_data *hw_data);

#पूर्ण_अगर
