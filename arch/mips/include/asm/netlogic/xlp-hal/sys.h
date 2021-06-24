<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __NLM_HAL_SYS_H__
#घोषणा __NLM_HAL_SYS_H__

/**
* @file_name sys.h
* @author Netlogic Microप्रणालीs
* @brief HAL क्रम System configuration रेजिस्टरs
*/
#घोषणा SYS_CHIP_RESET				0x00
#घोषणा SYS_POWER_ON_RESET_CFG			0x01
#घोषणा SYS_EFUSE_DEVICE_CFG_STATUS0		0x02
#घोषणा SYS_EFUSE_DEVICE_CFG_STATUS1		0x03
#घोषणा SYS_EFUSE_DEVICE_CFG_STATUS2		0x04
#घोषणा SYS_EFUSE_DEVICE_CFG3			0x05
#घोषणा SYS_EFUSE_DEVICE_CFG4			0x06
#घोषणा SYS_EFUSE_DEVICE_CFG5			0x07
#घोषणा SYS_EFUSE_DEVICE_CFG6			0x08
#घोषणा SYS_EFUSE_DEVICE_CFG7			0x09
#घोषणा SYS_PLL_CTRL				0x0a
#घोषणा SYS_CPU_RESET				0x0b
#घोषणा SYS_CPU_NONCOHERENT_MODE		0x0d
#घोषणा SYS_CORE_DFS_DIS_CTRL			0x0e
#घोषणा SYS_CORE_DFS_RST_CTRL			0x0f
#घोषणा SYS_CORE_DFS_BYP_CTRL			0x10
#घोषणा SYS_CORE_DFS_PHA_CTRL			0x11
#घोषणा SYS_CORE_DFS_DIV_INC_CTRL		0x12
#घोषणा SYS_CORE_DFS_DIV_DEC_CTRL		0x13
#घोषणा SYS_CORE_DFS_DIV_VALUE			0x14
#घोषणा SYS_RESET				0x15
#घोषणा SYS_DFS_DIS_CTRL			0x16
#घोषणा SYS_DFS_RST_CTRL			0x17
#घोषणा SYS_DFS_BYP_CTRL			0x18
#घोषणा SYS_DFS_DIV_INC_CTRL			0x19
#घोषणा SYS_DFS_DIV_DEC_CTRL			0x1a
#घोषणा SYS_DFS_DIV_VALUE0			0x1b
#घोषणा SYS_DFS_DIV_VALUE1			0x1c
#घोषणा SYS_SENSE_AMP_DLY			0x1d
#घोषणा SYS_SOC_SENSE_AMP_DLY			0x1e
#घोषणा SYS_CTRL0				0x1f
#घोषणा SYS_CTRL1				0x20
#घोषणा SYS_TIMEOUT_BS1				0x21
#घोषणा SYS_BYTE_SWAP				0x22
#घोषणा SYS_VRM_VID				0x23
#घोषणा SYS_PWR_RAM_CMD				0x24
#घोषणा SYS_PWR_RAM_ADDR			0x25
#घोषणा SYS_PWR_RAM_DATA0			0x26
#घोषणा SYS_PWR_RAM_DATA1			0x27
#घोषणा SYS_PWR_RAM_DATA2			0x28
#घोषणा SYS_PWR_UCODE				0x29
#घोषणा SYS_CPU0_PWR_STATUS			0x2a
#घोषणा SYS_CPU1_PWR_STATUS			0x2b
#घोषणा SYS_CPU2_PWR_STATUS			0x2c
#घोषणा SYS_CPU3_PWR_STATUS			0x2d
#घोषणा SYS_CPU4_PWR_STATUS			0x2e
#घोषणा SYS_CPU5_PWR_STATUS			0x2f
#घोषणा SYS_CPU6_PWR_STATUS			0x30
#घोषणा SYS_CPU7_PWR_STATUS			0x31
#घोषणा SYS_STATUS				0x32
#घोषणा SYS_INT_POL				0x33
#घोषणा SYS_INT_TYPE				0x34
#घोषणा SYS_INT_STATUS				0x35
#घोषणा SYS_INT_MASK0				0x36
#घोषणा SYS_INT_MASK1				0x37
#घोषणा SYS_UCO_S_ECC				0x38
#घोषणा SYS_UCO_M_ECC				0x39
#घोषणा SYS_UCO_ADDR				0x3a
#घोषणा SYS_UCO_INSTR				0x3b
#घोषणा SYS_MEM_BIST0				0x3c
#घोषणा SYS_MEM_BIST1				0x3d
#घोषणा SYS_MEM_BIST2				0x3e
#घोषणा SYS_MEM_BIST3				0x3f
#घोषणा SYS_MEM_BIST4				0x40
#घोषणा SYS_MEM_BIST5				0x41
#घोषणा SYS_MEM_BIST6				0x42
#घोषणा SYS_MEM_BIST7				0x43
#घोषणा SYS_MEM_BIST8				0x44
#घोषणा SYS_MEM_BIST9				0x45
#घोषणा SYS_MEM_BIST10				0x46
#घोषणा SYS_MEM_BIST11				0x47
#घोषणा SYS_MEM_BIST12				0x48
#घोषणा SYS_SCRTCH0				0x49
#घोषणा SYS_SCRTCH1				0x4a
#घोषणा SYS_SCRTCH2				0x4b
#घोषणा SYS_SCRTCH3				0x4c

/* PLL रेजिस्टरs XLP2XX */
#घोषणा SYS_CPU_PLL_CTRL0(core)			(0x1c0 + (core * 4))
#घोषणा SYS_CPU_PLL_CTRL1(core)			(0x1c1 + (core * 4))
#घोषणा SYS_CPU_PLL_CTRL2(core)			(0x1c2 + (core * 4))
#घोषणा SYS_CPU_PLL_CTRL3(core)			(0x1c3 + (core * 4))
#घोषणा SYS_PLL_CTRL0				0x240
#घोषणा SYS_PLL_CTRL1				0x241
#घोषणा SYS_PLL_CTRL2				0x242
#घोषणा SYS_PLL_CTRL3				0x243
#घोषणा SYS_DMC_PLL_CTRL0			0x244
#घोषणा SYS_DMC_PLL_CTRL1			0x245
#घोषणा SYS_DMC_PLL_CTRL2			0x246
#घोषणा SYS_DMC_PLL_CTRL3			0x247

#घोषणा SYS_PLL_CTRL0_DEVX(x)			(0x248 + (x) * 4)
#घोषणा SYS_PLL_CTRL1_DEVX(x)			(0x249 + (x) * 4)
#घोषणा SYS_PLL_CTRL2_DEVX(x)			(0x24a + (x) * 4)
#घोषणा SYS_PLL_CTRL3_DEVX(x)			(0x24b + (x) * 4)

#घोषणा SYS_CPU_PLL_CHG_CTRL			0x288
#घोषणा SYS_PLL_CHG_CTRL			0x289
#घोषणा SYS_CLK_DEV_DIS				0x28a
#घोषणा SYS_CLK_DEV_SEL				0x28b
#घोषणा SYS_CLK_DEV_DIV				0x28c
#घोषणा SYS_CLK_DEV_CHG				0x28d
#घोषणा SYS_CLK_DEV_SEL_REG			0x28e
#घोषणा SYS_CLK_DEV_DIV_REG			0x28f
#घोषणा SYS_CPU_PLL_LOCK			0x29f
#घोषणा SYS_SYS_PLL_LOCK			0x2a0
#घोषणा SYS_PLL_MEM_CMD				0x2a1
#घोषणा SYS_CPU_PLL_MEM_REQ			0x2a2
#घोषणा SYS_SYS_PLL_MEM_REQ			0x2a3
#घोषणा SYS_PLL_MEM_STAT			0x2a4

/* PLL रेजिस्टरs XLP9XX */
#घोषणा SYS_9XX_CPU_PLL_CTRL0(core)		(0xc0 + (core * 4))
#घोषणा SYS_9XX_CPU_PLL_CTRL1(core)		(0xc1 + (core * 4))
#घोषणा SYS_9XX_CPU_PLL_CTRL2(core)		(0xc2 + (core * 4))
#घोषणा SYS_9XX_CPU_PLL_CTRL3(core)		(0xc3 + (core * 4))
#घोषणा SYS_9XX_DMC_PLL_CTRL0			0x140
#घोषणा SYS_9XX_DMC_PLL_CTRL1			0x141
#घोषणा SYS_9XX_DMC_PLL_CTRL2			0x142
#घोषणा SYS_9XX_DMC_PLL_CTRL3			0x143
#घोषणा SYS_9XX_PLL_CTRL0			0x144
#घोषणा SYS_9XX_PLL_CTRL1			0x145
#घोषणा SYS_9XX_PLL_CTRL2			0x146
#घोषणा SYS_9XX_PLL_CTRL3			0x147

#घोषणा SYS_9XX_PLL_CTRL0_DEVX(x)		(0x148 + (x) * 4)
#घोषणा SYS_9XX_PLL_CTRL1_DEVX(x)		(0x149 + (x) * 4)
#घोषणा SYS_9XX_PLL_CTRL2_DEVX(x)		(0x14a + (x) * 4)
#घोषणा SYS_9XX_PLL_CTRL3_DEVX(x)		(0x14b + (x) * 4)

#घोषणा SYS_9XX_CPU_PLL_CHG_CTRL		0x188
#घोषणा SYS_9XX_PLL_CHG_CTRL			0x189
#घोषणा SYS_9XX_CLK_DEV_DIS			0x18a
#घोषणा SYS_9XX_CLK_DEV_SEL			0x18b
#घोषणा SYS_9XX_CLK_DEV_DIV			0x18d
#घोषणा SYS_9XX_CLK_DEV_CHG			0x18f

#घोषणा SYS_9XX_CLK_DEV_SEL_REG			0x1a4
#घोषणा SYS_9XX_CLK_DEV_DIV_REG			0x1a6

/* Registers changed on 9XX */
#घोषणा SYS_9XX_POWER_ON_RESET_CFG		0x00
#घोषणा SYS_9XX_CHIP_RESET			0x01
#घोषणा SYS_9XX_CPU_RESET			0x02
#घोषणा SYS_9XX_CPU_NONCOHERENT_MODE		0x03

/* XLP 9XX fuse block रेजिस्टरs */
#घोषणा FUSE_9XX_DEVCFG6			0xc6

#अगर_अघोषित __ASSEMBLY__

#घोषणा nlm_पढ़ो_sys_reg(b, r)		nlm_पढ़ो_reg(b, r)
#घोषणा nlm_ग_लिखो_sys_reg(b, r, v)	nlm_ग_लिखो_reg(b, r, v)
#घोषणा nlm_get_sys_pcibase(node)	nlm_pcicfg_base(cpu_is_xlp9xx() ? \
		XLP9XX_IO_SYS_OFFSET(node) : XLP_IO_SYS_OFFSET(node))
#घोषणा nlm_get_sys_regbase(node) (nlm_get_sys_pcibase(node) + XLP_IO_PCI_HDRSZ)

/* XLP9XX fuse block */
#घोषणा nlm_get_fuse_pcibase(node)	\
			nlm_pcicfg_base(XLP9XX_IO_FUSE_OFFSET(node))
#घोषणा nlm_get_fuse_regbase(node)	\
			(nlm_get_fuse_pcibase(node) + XLP_IO_PCI_HDRSZ)

#घोषणा nlm_get_घड़ी_pcibase(node)	\
			nlm_pcicfg_base(XLP9XX_IO_CLOCK_OFFSET(node))
#घोषणा nlm_get_घड़ी_regbase(node)	\
			(nlm_get_घड़ी_pcibase(node) + XLP_IO_PCI_HDRSZ)

अचिन्हित पूर्णांक nlm_get_pic_frequency(पूर्णांक node);
#पूर्ण_अगर
#पूर्ण_अगर
