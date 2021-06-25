<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2015 Imagination Technologies, Inc.
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#अगर_अघोषित __ASM_MIPS_BOARDS_SEAD3_ADDR_H
#घोषणा __ASM_MIPS_BOARDS_SEAD3_ADDR_H

/*
 * Target #0 Register Decode
 */
#घोषणा SEAD3_SD_SPDCNF				0xbb000040
#घोषणा SEAD3_SD_SPADDR				0xbb000048
#घोषणा SEAD3_SD_DATA				0xbb000050

/*
 * Target #1 Register Decode
 */
#घोषणा SEAD3_CFG				0xbb100110
#घोषणा SEAD3_GIC_BASE_ADDRESS			0xbb1c0000
#घोषणा SEAD3_SHARED_SECTION			0xbb1c0000
#घोषणा SEAD3_VPE_LOCAL_SECTION			0xbb1c8000
#घोषणा SEAD3_VPE_OTHER_SECTION			0xbb1cc000
#घोषणा SEAD3_USER_MODE_VISIBLE_SECTION		0xbb1d0000

/*
 * Target #3 Register Decode
 */
#घोषणा SEAD3_USB_HS_BASE			0xbb200000
#घोषणा SEAD3_USB_HS_IDENTIFICATION_REGS	0xbb200000
#घोषणा SEAD3_USB_HS_CAPABILITY_REGS		0xbb200100
#घोषणा SEAD3_USB_HS_OPERATIONAL_REGS		0xbb200140
#घोषणा SEAD3_RESERVED				0xbe800000

/*
 * Target #3 Register Decode
 */
#घोषणा SEAD3_SRAM				0xbe000000
#घोषणा SEAD3_OPTIONAL_SRAM			0xbe400000
#घोषणा SEAD3_FPGA				0xbf000000

#घोषणा SEAD3_PI_PIC32_USB_STATUS		0xbf000060
#घोषणा   SEAD3_PI_PIC32_USB_STATUS_IO_RDY	(1 << 0)
#घोषणा   SEAD3_PI_PIC32_USB_STATUS_SPL_INT	(1 << 1)
#घोषणा   SEAD3_PI_PIC32_USB_STATUS_GPIOA_INT	(1 << 2)
#घोषणा   SEAD3_PI_PIC32_USB_STATUS_GPIOB_INT	(1 << 3)

#घोषणा SEAD3_PI_SOFT_ENDIAN			0xbf000070

#घोषणा SEAD3_CPLD_P_SWITCH			0xbf000200
#घोषणा SEAD3_CPLD_F_SWITCH			0xbf000208
#घोषणा SEAD3_CPLD_P_LED			0xbf000210
#घोषणा SEAD3_CPLD_F_LED			0xbf000218
#घोषणा SEAD3_NEWSC_LIVE			0xbf000220
#घोषणा SEAD3_NEWSC_REG				0xbf000228
#घोषणा SEAD3_NEWSC_CTRL			0xbf000230

#घोषणा SEAD3_LCD_CONTROL			0xbf000400
#घोषणा SEAD3_LCD_DATA				0xbf000408
#घोषणा SEAD3_CPLD_LCD_STATUS			0xbf000410
#घोषणा SEAD3_CPLD_LCD_DATA			0xbf000418

#घोषणा SEAD3_CPLD_PI_DEVRST			0xbf000480
#घोषणा SEAD3_CPLD_PI_DEVRST_IC32_RST		(1 << 0)
#घोषणा SEAD3_RESERVED_0			0xbf000500

#घोषणा SEAD3_PIC32_REGISTERS			0xbf000600
#घोषणा SEAD3_RESERVED_1			0xbf000700
#घोषणा SEAD3_UART_CH_0				0xbf000800
#घोषणा SEAD3_UART_CH_1				0xbf000900
#घोषणा SEAD3_RESERVED_2			0xbf000a00
#घोषणा SEAD3_ETHERNET				0xbf010000
#घोषणा SEAD3_RESERVED_3			0xbf020000
#घोषणा SEAD3_USER_EXPANSION			0xbf400000
#घोषणा SEAD3_RESERVED_4			0xbf800000
#घोषणा SEAD3_BOOT_FLASH_EXTENSION		0xbfa00000
#घोषणा SEAD3_BOOT_FLASH			0xbfc00000
#घोषणा SEAD3_REVISION_REGISTER			0xbfc00010

#पूर्ण_अगर /* __ASM_MIPS_BOARDS_SEAD3_ADDR_H  */
