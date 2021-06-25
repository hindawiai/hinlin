<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/linux/mtd/onenand_regs.h
 *
 *  Oneन_अंकD Register header file
 *
 *  Copyright (C) 2005-2007 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 */

#अगर_अघोषित __ONEन_अंकD_REG_H
#घोषणा __ONEन_अंकD_REG_H

/* Memory Address Map Translation (Word order) */
#घोषणा ONEन_अंकD_MEMORY_MAP(x)		((x) << 1)

/*
 * External BufferRAM area
 */
#घोषणा	ONEन_अंकD_BOOTRAM			ONEन_अंकD_MEMORY_MAP(0x0000)
#घोषणा	ONEन_अंकD_DATARAM			ONEन_अंकD_MEMORY_MAP(0x0200)
#घोषणा	ONEन_अंकD_SPARERAM		ONEन_अंकD_MEMORY_MAP(0x8010)

/*
 * Oneन_अंकD Registers
 */
#घोषणा ONEन_अंकD_REG_MANUFACTURER_ID	ONEन_अंकD_MEMORY_MAP(0xF000)
#घोषणा ONEन_अंकD_REG_DEVICE_ID		ONEन_अंकD_MEMORY_MAP(0xF001)
#घोषणा ONEन_अंकD_REG_VERSION_ID		ONEन_अंकD_MEMORY_MAP(0xF002)
#घोषणा ONEन_अंकD_REG_DATA_BUFFER_SIZE	ONEन_अंकD_MEMORY_MAP(0xF003)
#घोषणा ONEन_अंकD_REG_BOOT_BUFFER_SIZE	ONEन_अंकD_MEMORY_MAP(0xF004)
#घोषणा ONEन_अंकD_REG_NUM_BUFFERS		ONEन_अंकD_MEMORY_MAP(0xF005)
#घोषणा ONEन_अंकD_REG_TECHNOLOGY		ONEन_अंकD_MEMORY_MAP(0xF006)

#घोषणा ONEन_अंकD_REG_START_ADDRESS1	ONEन_अंकD_MEMORY_MAP(0xF100)
#घोषणा ONEन_अंकD_REG_START_ADDRESS2	ONEन_अंकD_MEMORY_MAP(0xF101)
#घोषणा ONEन_अंकD_REG_START_ADDRESS3	ONEन_अंकD_MEMORY_MAP(0xF102)
#घोषणा ONEन_अंकD_REG_START_ADDRESS4	ONEन_अंकD_MEMORY_MAP(0xF103)
#घोषणा ONEन_अंकD_REG_START_ADDRESS5	ONEन_अंकD_MEMORY_MAP(0xF104)
#घोषणा ONEन_अंकD_REG_START_ADDRESS6	ONEन_अंकD_MEMORY_MAP(0xF105)
#घोषणा ONEन_अंकD_REG_START_ADDRESS7	ONEन_अंकD_MEMORY_MAP(0xF106)
#घोषणा ONEन_अंकD_REG_START_ADDRESS8	ONEन_अंकD_MEMORY_MAP(0xF107)

#घोषणा ONEन_अंकD_REG_START_BUFFER	ONEन_अंकD_MEMORY_MAP(0xF200)
#घोषणा ONEन_अंकD_REG_COMMAND		ONEन_अंकD_MEMORY_MAP(0xF220)
#घोषणा ONEन_अंकD_REG_SYS_CFG1		ONEन_अंकD_MEMORY_MAP(0xF221)
#घोषणा ONEन_अंकD_REG_SYS_CFG2		ONEन_अंकD_MEMORY_MAP(0xF222)
#घोषणा ONEन_अंकD_REG_CTRL_STATUS		ONEन_अंकD_MEMORY_MAP(0xF240)
#घोषणा ONEन_अंकD_REG_INTERRUPT		ONEन_अंकD_MEMORY_MAP(0xF241)
#घोषणा ONEन_अंकD_REG_START_BLOCK_ADDRESS	ONEन_अंकD_MEMORY_MAP(0xF24C)
#घोषणा ONEन_अंकD_REG_END_BLOCK_ADDRESS	ONEन_अंकD_MEMORY_MAP(0xF24D)
#घोषणा ONEन_अंकD_REG_WP_STATUS		ONEन_अंकD_MEMORY_MAP(0xF24E)

#घोषणा ONEन_अंकD_REG_ECC_STATUS		ONEन_अंकD_MEMORY_MAP(0xFF00)
#घोषणा ONEन_अंकD_REG_ECC_M0		ONEन_अंकD_MEMORY_MAP(0xFF01)
#घोषणा ONEन_अंकD_REG_ECC_S0		ONEन_अंकD_MEMORY_MAP(0xFF02)
#घोषणा ONEन_अंकD_REG_ECC_M1		ONEन_अंकD_MEMORY_MAP(0xFF03)
#घोषणा ONEन_अंकD_REG_ECC_S1		ONEन_अंकD_MEMORY_MAP(0xFF04)
#घोषणा ONEन_अंकD_REG_ECC_M2		ONEन_अंकD_MEMORY_MAP(0xFF05)
#घोषणा ONEन_अंकD_REG_ECC_S2		ONEन_अंकD_MEMORY_MAP(0xFF06)
#घोषणा ONEन_अंकD_REG_ECC_M3		ONEन_अंकD_MEMORY_MAP(0xFF07)
#घोषणा ONEन_अंकD_REG_ECC_S3		ONEन_अंकD_MEMORY_MAP(0xFF08)

/*
 * Device ID Register F001h (R)
 */
#घोषणा DEVICE_IS_FLEXONEन_अंकD		(1 << 9)
#घोषणा FLEXONEन_अंकD_PI_MASK		(0x3ff)
#घोषणा FLEXONEन_अंकD_PI_UNLOCK_SHIFT	(14)
#घोषणा ONEन_अंकD_DEVICE_DENSITY_MASK	(0xf)
#घोषणा ONEन_अंकD_DEVICE_DENSITY_SHIFT	(4)
#घोषणा ONEन_अंकD_DEVICE_IS_DDP		(1 << 3)
#घोषणा ONEन_अंकD_DEVICE_IS_DEMUX		(1 << 2)
#घोषणा ONEन_अंकD_DEVICE_VCC_MASK		(0x3)

#घोषणा ONEन_अंकD_DEVICE_DENSITY_512Mb	(0x002)
#घोषणा ONEन_अंकD_DEVICE_DENSITY_1Gb	(0x003)
#घोषणा ONEन_अंकD_DEVICE_DENSITY_2Gb	(0x004)
#घोषणा ONEन_अंकD_DEVICE_DENSITY_4Gb	(0x005)
#घोषणा ONEन_अंकD_DEVICE_DENSITY_8Gb	(0x006)

/*
 * Version ID Register F002h (R)
 */
#घोषणा ONEन_अंकD_VERSION_PROCESS_SHIFT	(8)

/*
 * Technology Register F006h (R)
 */
#घोषणा ONEन_अंकD_TECHNOLOGY_IS_MLC	(1 << 0)

/*
 * Start Address 1 F100h (R/W) & Start Address 2 F101h (R/W)
 */
#घोषणा ONEन_अंकD_DDP_SHIFT		(15)
#घोषणा ONEन_अंकD_DDP_CHIP0		(0)
#घोषणा ONEन_अंकD_DDP_CHIP1		(1 << ONEन_अंकD_DDP_SHIFT)

/*
 * Start Address 8 F107h (R/W)
 */
/* Note: It's actually 0x3f in हाल of SLC */
#घोषणा ONEन_अंकD_FPA_MASK		(0x7f)
#घोषणा ONEन_अंकD_FPA_SHIFT		(2)
#घोषणा ONEन_अंकD_FSA_MASK		(0x03)

/*
 * Start Buffer Register F200h (R/W)
 */
#घोषणा ONEन_अंकD_BSA_MASK		(0x03)
#घोषणा ONEन_अंकD_BSA_SHIFT		(8)
#घोषणा ONEन_अंकD_BSA_BOOTRAM		(0 << 2)
#घोषणा ONEन_अंकD_BSA_DATARAM0		(2 << 2)
#घोषणा ONEन_अंकD_BSA_DATARAM1		(3 << 2)
/* Note: It's actually 0x03 in हाल of SLC */
#घोषणा ONEन_अंकD_BSC_MASK		(0x07)

/*
 * Command Register F220h (R/W)
 */
#घोषणा ONEन_अंकD_CMD_READ		(0x00)
#घोषणा ONEन_अंकD_CMD_READOOB		(0x13)
#घोषणा ONEन_अंकD_CMD_PROG		(0x80)
#घोषणा ONEन_अंकD_CMD_PROGOOB		(0x1A)
#घोषणा ONEन_अंकD_CMD_2X_PROG		(0x7D)
#घोषणा ONEन_अंकD_CMD_2X_CACHE_PROG	(0x7F)
#घोषणा ONEन_अंकD_CMD_UNLOCK		(0x23)
#घोषणा ONEन_अंकD_CMD_LOCK		(0x2A)
#घोषणा ONEन_अंकD_CMD_LOCK_TIGHT		(0x2C)
#घोषणा ONEन_अंकD_CMD_UNLOCK_ALL		(0x27)
#घोषणा ONEन_अंकD_CMD_ERASE		(0x94)
#घोषणा ONEन_अंकD_CMD_MULTIBLOCK_ERASE	(0x95)
#घोषणा ONEन_अंकD_CMD_ERASE_VERIFY	(0x71)
#घोषणा ONEन_अंकD_CMD_RESET		(0xF0)
#घोषणा ONEन_अंकD_CMD_OTP_ACCESS		(0x65)
#घोषणा ONEन_अंकD_CMD_READID		(0x90)
#घोषणा FLEXONEन_अंकD_CMD_PI_UPDATE	(0x05)
#घोषणा FLEXONEन_अंकD_CMD_PI_ACCESS	(0x66)
#घोषणा FLEXONEन_अंकD_CMD_RECOVER_LSB	(0x05)

/* NOTE: Those are not *REAL* commands */
#घोषणा ONEन_अंकD_CMD_BUFFERRAM		(0x1978)
#घोषणा FLEXONEन_अंकD_CMD_READ_PI		(0x1985)

/*
 * System Configuration 1 Register F221h (R, R/W)
 */
#घोषणा ONEन_अंकD_SYS_CFG1_SYNC_READ	(1 << 15)
#घोषणा ONEन_अंकD_SYS_CFG1_BRL_7		(7 << 12)
#घोषणा ONEन_अंकD_SYS_CFG1_BRL_6		(6 << 12)
#घोषणा ONEन_अंकD_SYS_CFG1_BRL_5		(5 << 12)
#घोषणा ONEन_अंकD_SYS_CFG1_BRL_4		(4 << 12)
#घोषणा ONEन_अंकD_SYS_CFG1_BRL_3		(3 << 12)
#घोषणा ONEन_अंकD_SYS_CFG1_BRL_10		(2 << 12)
#घोषणा ONEन_अंकD_SYS_CFG1_BRL_9		(1 << 12)
#घोषणा ONEन_अंकD_SYS_CFG1_BRL_8		(0 << 12)
#घोषणा ONEन_अंकD_SYS_CFG1_BRL_SHIFT	(12)
#घोषणा ONEन_अंकD_SYS_CFG1_BL_32		(4 << 9)
#घोषणा ONEन_अंकD_SYS_CFG1_BL_16		(3 << 9)
#घोषणा ONEन_अंकD_SYS_CFG1_BL_8		(2 << 9)
#घोषणा ONEन_अंकD_SYS_CFG1_BL_4		(1 << 9)
#घोषणा ONEन_अंकD_SYS_CFG1_BL_CONT	(0 << 9)
#घोषणा ONEन_अंकD_SYS_CFG1_BL_SHIFT	(9)
#घोषणा ONEन_अंकD_SYS_CFG1_NO_ECC		(1 << 8)
#घोषणा ONEन_अंकD_SYS_CFG1_RDY		(1 << 7)
#घोषणा ONEन_अंकD_SYS_CFG1_INT		(1 << 6)
#घोषणा ONEन_अंकD_SYS_CFG1_IOBE		(1 << 5)
#घोषणा ONEन_अंकD_SYS_CFG1_RDY_CONF	(1 << 4)
#घोषणा ONEन_अंकD_SYS_CFG1_VHF		(1 << 3)
#घोषणा ONEन_अंकD_SYS_CFG1_HF		(1 << 2)
#घोषणा ONEन_अंकD_SYS_CFG1_SYNC_WRITE	(1 << 1)

/*
 * Controller Status Register F240h (R)
 */
#घोषणा ONEन_अंकD_CTRL_ONGO		(1 << 15)
#घोषणा ONEन_अंकD_CTRL_LOCK		(1 << 14)
#घोषणा ONEन_अंकD_CTRL_LOAD		(1 << 13)
#घोषणा ONEन_अंकD_CTRL_PROGRAM		(1 << 12)
#घोषणा ONEन_अंकD_CTRL_ERASE		(1 << 11)
#घोषणा ONEन_अंकD_CTRL_ERROR		(1 << 10)
#घोषणा ONEन_अंकD_CTRL_RSTB		(1 << 7)
#घोषणा ONEन_अंकD_CTRL_OTP_L		(1 << 6)
#घोषणा ONEन_अंकD_CTRL_OTP_BL		(1 << 5)

/*
 * Interrupt Status Register F241h (R)
 */
#घोषणा ONEन_अंकD_INT_MASTER		(1 << 15)
#घोषणा ONEन_अंकD_INT_READ		(1 << 7)
#घोषणा ONEन_अंकD_INT_WRITE		(1 << 6)
#घोषणा ONEन_अंकD_INT_ERASE		(1 << 5)
#घोषणा ONEन_अंकD_INT_RESET		(1 << 4)
#घोषणा ONEन_अंकD_INT_CLEAR		(0 << 0)

/*
 * न_अंकD Flash Write Protection Status Register F24Eh (R)
 */
#घोषणा ONEन_अंकD_WP_US			(1 << 2)
#घोषणा ONEन_अंकD_WP_LS			(1 << 1)
#घोषणा ONEन_अंकD_WP_LTS			(1 << 0)

/*
 * ECC Status Reigser FF00h (R)
 */
#घोषणा ONEन_अंकD_ECC_1BIT		(1 << 0)
#घोषणा ONEन_अंकD_ECC_1BIT_ALL		(0x5555)
#घोषणा ONEन_अंकD_ECC_2BIT		(1 << 1)
#घोषणा ONEन_अंकD_ECC_2BIT_ALL		(0xAAAA)
#घोषणा FLEXONEन_अंकD_UNCORRECTABLE_ERROR	(0x1010)
#घोषणा ONEन_अंकD_ECC_3BIT		(1 << 2)
#घोषणा ONEन_अंकD_ECC_4BIT		(1 << 3)
#घोषणा ONEन_अंकD_ECC_4BIT_UNCORRECTABLE	(0x1010)

/*
 * One-Time Programmable (OTP)
 */
#घोषणा FLEXONEन_अंकD_OTP_LOCK_OFFSET		(2048)
#घोषणा ONEन_अंकD_OTP_LOCK_OFFSET		(14)

#पूर्ण_अगर	/* __ONEन_अंकD_REG_H */
