<शैली गुरु>
/*
 * SPEAr3xx/6xx Machine family specअगरic definition
 *
 * Copyright (C) 2009,2012 ST Microelectronics
 * Rajeev Kumar<rajeev-dlh.kumar@st.com>
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __MACH_SPEAR_H
#घोषणा __MACH_SPEAR_H

#समावेश <यंत्र/memory.h>

#अगर defined(CONFIG_ARCH_SPEAR3XX) || defined (CONFIG_ARCH_SPEAR6XX)

/* ICM1 - Low speed connection */
#घोषणा SPEAR_ICM1_2_BASE		UL(0xD0000000)
#घोषणा VA_SPEAR_ICM1_2_BASE		IOMEM(0xFD000000)
#घोषणा SPEAR_ICM1_UART_BASE		UL(0xD0000000)
#घोषणा VA_SPEAR_ICM1_UART_BASE		(VA_SPEAR_ICM1_2_BASE - SPEAR_ICM1_2_BASE + SPEAR_ICM1_UART_BASE)
#घोषणा SPEAR3XX_ICM1_SSP_BASE		UL(0xD0100000)

/* ML-1, 2 - Multi Layer CPU Subप्रणाली */
#घोषणा SPEAR_ICM3_ML1_2_BASE		UL(0xF0000000)
#घोषणा VA_SPEAR6XX_ML_CPU_BASE		IOMEM(0xF0000000)

/* ICM3 - Basic Subप्रणाली */
#घोषणा SPEAR_ICM3_SMI_CTRL_BASE	UL(0xFC000000)
#घोषणा VA_SPEAR_ICM3_SMI_CTRL_BASE	IOMEM(0xFC000000)
#घोषणा SPEAR_ICM3_DMA_BASE		UL(0xFC400000)
#घोषणा SPEAR_ICM3_SYS_CTRL_BASE	UL(0xFCA00000)
#घोषणा VA_SPEAR_ICM3_SYS_CTRL_BASE	(VA_SPEAR_ICM3_SMI_CTRL_BASE - SPEAR_ICM3_SMI_CTRL_BASE + SPEAR_ICM3_SYS_CTRL_BASE)
#घोषणा SPEAR_ICM3_MISC_REG_BASE	UL(0xFCA80000)
#घोषणा VA_SPEAR_ICM3_MISC_REG_BASE	(VA_SPEAR_ICM3_SMI_CTRL_BASE - SPEAR_ICM3_SMI_CTRL_BASE + SPEAR_ICM3_MISC_REG_BASE)

/* Debug uart क्रम linux, will be used क्रम debug and uncompress messages */
#घोषणा SPEAR_DBG_UART_BASE		SPEAR_ICM1_UART_BASE

/* Sysctl base क्रम spear platक्रमm */
#घोषणा SPEAR_SYS_CTRL_BASE		SPEAR_ICM3_SYS_CTRL_BASE
#घोषणा VA_SPEAR_SYS_CTRL_BASE		VA_SPEAR_ICM3_SYS_CTRL_BASE
#पूर्ण_अगर /* SPEAR3xx || SPEAR6XX */

/* SPEAr320 Macros */
#घोषणा SPEAR320_SOC_CONFIG_BASE	UL(0xB3000000)
#घोषणा VA_SPEAR320_SOC_CONFIG_BASE	IOMEM(0xFE000000)

#अगर_घोषित CONFIG_ARCH_SPEAR13XX

#घोषणा PERIP_GRP2_BASE				UL(0xB3000000)
#घोषणा VA_PERIP_GRP2_BASE			IOMEM(0xF9000000)
#घोषणा MCIF_SDHCI_BASE				UL(0xB3000000)
#घोषणा SYSRAM0_BASE				UL(0xB3800000)
#घोषणा VA_SYSRAM0_BASE				IOMEM(0xF9800000)
#घोषणा SYS_LOCATION				(VA_SYSRAM0_BASE + 0x600)

#घोषणा PERIP_GRP1_BASE				UL(0xE0000000)
#घोषणा VA_PERIP_GRP1_BASE			IOMEM(0xFD000000)
#घोषणा UART_BASE				UL(0xE0000000)
#घोषणा VA_UART_BASE				IOMEM(0xFD000000)
#घोषणा SSP_BASE				UL(0xE0100000)
#घोषणा MISC_BASE				UL(0xE0700000)
#घोषणा VA_MISC_BASE				IOMEM(0xFD700000)

#घोषणा A9SM_AND_MPMC_BASE			UL(0xEC000000)
#घोषणा VA_A9SM_AND_MPMC_BASE			IOMEM(0xFC000000)

#घोषणा SPEAR1310_RAS_BASE			UL(0xD8400000)
#घोषणा VA_SPEAR1310_RAS_BASE			IOMEM(UL(0xFA400000))

/* A9SM peripheral offsets */
#घोषणा A9SM_PERIP_BASE				UL(0xEC800000)
#घोषणा VA_A9SM_PERIP_BASE			IOMEM(0xFC800000)
#घोषणा VA_SCU_BASE				(VA_A9SM_PERIP_BASE + 0x00)

#घोषणा L2CC_BASE				UL(0xED000000)
#घोषणा VA_L2CC_BASE				IOMEM(UL(0xFB000000))

/* others */
#घोषणा MCIF_CF_BASE				UL(0xB2800000)

/* Debug uart क्रम linux, will be used क्रम debug and uncompress messages */
#घोषणा SPEAR_DBG_UART_BASE			UART_BASE

#पूर्ण_अगर /* SPEAR13XX */

#पूर्ण_अगर /* __MACH_SPEAR_H */
