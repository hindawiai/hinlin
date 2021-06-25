<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  This file contains the hardware definitions of the Integrator.
 *
 *  Copyright (C) 1998-1999 ARM Limited.
 */
#अगर_अघोषित INTEGRATOR_HARDWARE_H
#घोषणा INTEGRATOR_HARDWARE_H

/*
 * Where in भव memory the IO devices (समयrs, प्रणाली controllers
 * and so on)
 */
#घोषणा IO_BASE			0xF0000000                 // VA of IO
#घोषणा IO_SIZE			0x0B000000                 // How much?
#घोषणा IO_START		INTEGRATOR_HDR_BASE        // PA of IO

/* macro to get at IO space when running भवly */
#अगर_घोषित CONFIG_MMU
#घोषणा IO_ADDRESS(x)	(((x) & 0x000fffff) | (((x) >> 4) & 0x0ff00000) | IO_BASE)
#अन्यथा
#घोषणा IO_ADDRESS(x)	(x)
#पूर्ण_अगर

#घोषणा __io_address(n)		((व्योम __iomem *)IO_ADDRESS(n))

/*
 *  Integrator memory map
 */
#घोषणा INTEGRATOR_BOOT_ROM_LO          0x00000000
#घोषणा INTEGRATOR_BOOT_ROM_HI          0x20000000
#घोषणा INTEGRATOR_BOOT_ROM_BASE        INTEGRATOR_BOOT_ROM_HI	 /*  Normal position */
#घोषणा INTEGRATOR_BOOT_ROM_SIZE        SZ_512K

/*
 * New Core Modules have dअगरferent amounts of SSRAM, the amount of SSRAM
 * fitted can be found in HDR_STAT.
 *
 * The symbol INTEGRATOR_SSRAM_SIZE is kept, however this now refers to
 * the minimum amount of SSRAM fitted on any core module.
 *
 * New Core Modules also alias the SSRAM.
 *
 */
#घोषणा INTEGRATOR_SSRAM_BASE           0x00000000
#घोषणा INTEGRATOR_SSRAM_ALIAS_BASE     0x10800000
#घोषणा INTEGRATOR_SSRAM_SIZE           SZ_256K

#घोषणा INTEGRATOR_FLASH_BASE           0x24000000
#घोषणा INTEGRATOR_FLASH_SIZE           SZ_32M

#घोषणा INTEGRATOR_MBRD_SSRAM_BASE      0x28000000
#घोषणा INTEGRATOR_MBRD_SSRAM_SIZE      SZ_512K

/*
 *  SDRAM is a SIMM thereक्रमe the size is not known.
 */
#घोषणा INTEGRATOR_SDRAM_BASE           0x00040000

#घोषणा INTEGRATOR_SDRAM_ALIAS_BASE     0x80000000
#घोषणा INTEGRATOR_HDR0_SDRAM_BASE      0x80000000
#घोषणा INTEGRATOR_HDR1_SDRAM_BASE      0x90000000
#घोषणा INTEGRATOR_HDR2_SDRAM_BASE      0xA0000000
#घोषणा INTEGRATOR_HDR3_SDRAM_BASE      0xB0000000

/*
 *  Logic expansion modules
 *
 */
#घोषणा INTEGRATOR_LOGIC_MODULES_BASE   0xC0000000
#घोषणा INTEGRATOR_LOGIC_MODULE0_BASE   0xC0000000
#घोषणा INTEGRATOR_LOGIC_MODULE1_BASE   0xD0000000
#घोषणा INTEGRATOR_LOGIC_MODULE2_BASE   0xE0000000
#घोषणा INTEGRATOR_LOGIC_MODULE3_BASE   0xF0000000

/*
 * Integrator header card रेजिस्टरs
 */
#घोषणा INTEGRATOR_HDR_ID_OFFSET        0x00
#घोषणा INTEGRATOR_HDR_PROC_OFFSET      0x04
#घोषणा INTEGRATOR_HDR_OSC_OFFSET       0x08
#घोषणा INTEGRATOR_HDR_CTRL_OFFSET      0x0C
#घोषणा INTEGRATOR_HDR_STAT_OFFSET      0x10
#घोषणा INTEGRATOR_HDR_LOCK_OFFSET      0x14
#घोषणा INTEGRATOR_HDR_SDRAM_OFFSET     0x20
#घोषणा INTEGRATOR_HDR_INIT_OFFSET      0x24	 /*  CM9x6 */
#घोषणा INTEGRATOR_HDR_IC_OFFSET        0x40
#घोषणा INTEGRATOR_HDR_SPDBASE_OFFSET   0x100
#घोषणा INTEGRATOR_HDR_SPDTOP_OFFSET    0x200

#घोषणा INTEGRATOR_HDR_BASE             0x10000000
#घोषणा INTEGRATOR_HDR_ID               (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_ID_OFFSET)
#घोषणा INTEGRATOR_HDR_PROC             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_PROC_OFFSET)
#घोषणा INTEGRATOR_HDR_OSC              (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_OSC_OFFSET)
#घोषणा INTEGRATOR_HDR_CTRL             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_CTRL_OFFSET)
#घोषणा INTEGRATOR_HDR_STAT             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_STAT_OFFSET)
#घोषणा INTEGRATOR_HDR_LOCK             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_LOCK_OFFSET)
#घोषणा INTEGRATOR_HDR_SDRAM            (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_SDRAM_OFFSET)
#घोषणा INTEGRATOR_HDR_INIT             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_INIT_OFFSET)
#घोषणा INTEGRATOR_HDR_IC               (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_IC_OFFSET)
#घोषणा INTEGRATOR_HDR_SPDBASE          (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_SPDBASE_OFFSET)
#घोषणा INTEGRATOR_HDR_SPDTOP           (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_SPDTOP_OFFSET)

#घोषणा INTEGRATOR_HDR_CTRL_LED         0x01
#घोषणा INTEGRATOR_HDR_CTRL_MBRD_DETECH 0x02
#घोषणा INTEGRATOR_HDR_CTRL_REMAP       0x04
#घोषणा INTEGRATOR_HDR_CTRL_RESET       0x08
#घोषणा INTEGRATOR_HDR_CTRL_HIGHVECTORS 0x10
#घोषणा INTEGRATOR_HDR_CTRL_BIG_ENDIAN  0x20
#घोषणा INTEGRATOR_HDR_CTRL_FASTBUS     0x40
#घोषणा INTEGRATOR_HDR_CTRL_SYNC        0x80

#घोषणा INTEGRATOR_HDR_OSC_CORE_10MHz   0x102
#घोषणा INTEGRATOR_HDR_OSC_CORE_15MHz   0x107
#घोषणा INTEGRATOR_HDR_OSC_CORE_20MHz   0x10C
#घोषणा INTEGRATOR_HDR_OSC_CORE_25MHz   0x111
#घोषणा INTEGRATOR_HDR_OSC_CORE_30MHz   0x116
#घोषणा INTEGRATOR_HDR_OSC_CORE_35MHz   0x11B
#घोषणा INTEGRATOR_HDR_OSC_CORE_40MHz   0x120
#घोषणा INTEGRATOR_HDR_OSC_CORE_45MHz   0x125
#घोषणा INTEGRATOR_HDR_OSC_CORE_50MHz   0x12A
#घोषणा INTEGRATOR_HDR_OSC_CORE_55MHz   0x12F
#घोषणा INTEGRATOR_HDR_OSC_CORE_60MHz   0x134
#घोषणा INTEGRATOR_HDR_OSC_CORE_65MHz   0x139
#घोषणा INTEGRATOR_HDR_OSC_CORE_70MHz   0x13E
#घोषणा INTEGRATOR_HDR_OSC_CORE_75MHz   0x143
#घोषणा INTEGRATOR_HDR_OSC_CORE_80MHz   0x148
#घोषणा INTEGRATOR_HDR_OSC_CORE_85MHz   0x14D
#घोषणा INTEGRATOR_HDR_OSC_CORE_90MHz   0x152
#घोषणा INTEGRATOR_HDR_OSC_CORE_95MHz   0x157
#घोषणा INTEGRATOR_HDR_OSC_CORE_100MHz  0x15C
#घोषणा INTEGRATOR_HDR_OSC_CORE_105MHz  0x161
#घोषणा INTEGRATOR_HDR_OSC_CORE_110MHz  0x166
#घोषणा INTEGRATOR_HDR_OSC_CORE_115MHz  0x16B
#घोषणा INTEGRATOR_HDR_OSC_CORE_120MHz  0x170
#घोषणा INTEGRATOR_HDR_OSC_CORE_125MHz  0x175
#घोषणा INTEGRATOR_HDR_OSC_CORE_130MHz  0x17A
#घोषणा INTEGRATOR_HDR_OSC_CORE_135MHz  0x17F
#घोषणा INTEGRATOR_HDR_OSC_CORE_140MHz  0x184
#घोषणा INTEGRATOR_HDR_OSC_CORE_145MHz  0x189
#घोषणा INTEGRATOR_HDR_OSC_CORE_150MHz  0x18E
#घोषणा INTEGRATOR_HDR_OSC_CORE_155MHz  0x193
#घोषणा INTEGRATOR_HDR_OSC_CORE_160MHz  0x198
#घोषणा INTEGRATOR_HDR_OSC_CORE_MASK    0x7FF

#घोषणा INTEGRATOR_HDR_OSC_MEM_10MHz    0x10C000
#घोषणा INTEGRATOR_HDR_OSC_MEM_15MHz    0x116000
#घोषणा INTEGRATOR_HDR_OSC_MEM_20MHz    0x120000
#घोषणा INTEGRATOR_HDR_OSC_MEM_25MHz    0x12A000
#घोषणा INTEGRATOR_HDR_OSC_MEM_30MHz    0x134000
#घोषणा INTEGRATOR_HDR_OSC_MEM_33MHz    0x13A000
#घोषणा INTEGRATOR_HDR_OSC_MEM_40MHz    0x148000
#घोषणा INTEGRATOR_HDR_OSC_MEM_50MHz    0x15C000
#घोषणा INTEGRATOR_HDR_OSC_MEM_60MHz    0x170000
#घोषणा INTEGRATOR_HDR_OSC_MEM_66MHz    0x17C000
#घोषणा INTEGRATOR_HDR_OSC_MEM_MASK     0x7FF000

#घोषणा INTEGRATOR_HDR_OSC_BUS_MODE_CM7x0  0x0
#घोषणा INTEGRATOR_HDR_OSC_BUS_MODE_CM9x0  0x0800000
#घोषणा INTEGRATOR_HDR_OSC_BUS_MODE_CM9x6  0x1000000
#घोषणा INTEGRATOR_HDR_OSC_BUS_MODE_CM10x00  0x1800000
#घोषणा INTEGRATOR_HDR_OSC_BUS_MODE_MASK  0x1800000

#घोषणा INTEGRATOR_HDR_SDRAM_SPD_OK     (1 << 5)

/*
 * Integrator प्रणाली रेजिस्टरs
 */

/*
 *  System Controller
 */
#घोषणा INTEGRATOR_SC_ID_OFFSET         0x00
#घोषणा INTEGRATOR_SC_OSC_OFFSET        0x04
#घोषणा INTEGRATOR_SC_CTRLS_OFFSET      0x08
#घोषणा INTEGRATOR_SC_CTRLC_OFFSET      0x0C
#घोषणा INTEGRATOR_SC_DEC_OFFSET        0x10
#घोषणा INTEGRATOR_SC_ARB_OFFSET        0x14
#घोषणा INTEGRATOR_SC_LOCK_OFFSET       0x1C

#घोषणा INTEGRATOR_SC_BASE              0x11000000
#घोषणा INTEGRATOR_SC_ID                (INTEGRATOR_SC_BASE + INTEGRATOR_SC_ID_OFFSET)
#घोषणा INTEGRATOR_SC_OSC               (INTEGRATOR_SC_BASE + INTEGRATOR_SC_OSC_OFFSET)
#घोषणा INTEGRATOR_SC_CTRLS             (INTEGRATOR_SC_BASE + INTEGRATOR_SC_CTRLS_OFFSET)
#घोषणा INTEGRATOR_SC_CTRLC             (INTEGRATOR_SC_BASE + INTEGRATOR_SC_CTRLC_OFFSET)
#घोषणा INTEGRATOR_SC_DEC               (INTEGRATOR_SC_BASE + INTEGRATOR_SC_DEC_OFFSET)
#घोषणा INTEGRATOR_SC_ARB               (INTEGRATOR_SC_BASE + INTEGRATOR_SC_ARB_OFFSET)
#घोषणा INTEGRATOR_SC_PCIENABLE         (INTEGRATOR_SC_BASE + INTEGRATOR_SC_PCIENABLE_OFFSET)
#घोषणा INTEGRATOR_SC_LOCK              (INTEGRATOR_SC_BASE + INTEGRATOR_SC_LOCK_OFFSET)

#घोषणा INTEGRATOR_SC_OSC_SYS_10MHz     0x20
#घोषणा INTEGRATOR_SC_OSC_SYS_15MHz     0x34
#घोषणा INTEGRATOR_SC_OSC_SYS_20MHz     0x48
#घोषणा INTEGRATOR_SC_OSC_SYS_25MHz     0x5C
#घोषणा INTEGRATOR_SC_OSC_SYS_33MHz     0x7C
#घोषणा INTEGRATOR_SC_OSC_SYS_MASK      0xFF

#घोषणा INTEGRATOR_SC_OSC_PCI_25MHz     0x100
#घोषणा INTEGRATOR_SC_OSC_PCI_33MHz     0x0
#घोषणा INTEGRATOR_SC_OSC_PCI_MASK      0x100

#घोषणा INTEGRATOR_SC_CTRL_SOFTRST      (1 << 0)
#घोषणा INTEGRATOR_SC_CTRL_nFLVPPEN     (1 << 1)
#घोषणा INTEGRATOR_SC_CTRL_nFLWP        (1 << 2)
#घोषणा INTEGRATOR_SC_CTRL_URTS0        (1 << 4)
#घोषणा INTEGRATOR_SC_CTRL_UDTR0        (1 << 5)
#घोषणा INTEGRATOR_SC_CTRL_URTS1        (1 << 6)
#घोषणा INTEGRATOR_SC_CTRL_UDTR1        (1 << 7)

/*
 *  External Bus Interface
 */
#घोषणा INTEGRATOR_EBI_BASE             0x12000000

#घोषणा INTEGRATOR_EBI_CSR0_OFFSET      0x00
#घोषणा INTEGRATOR_EBI_CSR1_OFFSET      0x04
#घोषणा INTEGRATOR_EBI_CSR2_OFFSET      0x08
#घोषणा INTEGRATOR_EBI_CSR3_OFFSET      0x0C
#घोषणा INTEGRATOR_EBI_LOCK_OFFSET      0x20

#घोषणा INTEGRATOR_EBI_CSR0             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_CSR0_OFFSET)
#घोषणा INTEGRATOR_EBI_CSR1             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_CSR1_OFFSET)
#घोषणा INTEGRATOR_EBI_CSR2             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_CSR2_OFFSET)
#घोषणा INTEGRATOR_EBI_CSR3             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_CSR3_OFFSET)
#घोषणा INTEGRATOR_EBI_LOCK             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_LOCK_OFFSET)

#घोषणा INTEGRATOR_EBI_8_BIT            0x00
#घोषणा INTEGRATOR_EBI_16_BIT           0x01
#घोषणा INTEGRATOR_EBI_32_BIT           0x02
#घोषणा INTEGRATOR_EBI_WRITE_ENABLE     0x04
#घोषणा INTEGRATOR_EBI_SYNC             0x08
#घोषणा INTEGRATOR_EBI_WS_2             0x00
#घोषणा INTEGRATOR_EBI_WS_3             0x10
#घोषणा INTEGRATOR_EBI_WS_4             0x20
#घोषणा INTEGRATOR_EBI_WS_5             0x30
#घोषणा INTEGRATOR_EBI_WS_6             0x40
#घोषणा INTEGRATOR_EBI_WS_7             0x50
#घोषणा INTEGRATOR_EBI_WS_8             0x60
#घोषणा INTEGRATOR_EBI_WS_9             0x70
#घोषणा INTEGRATOR_EBI_WS_10            0x80
#घोषणा INTEGRATOR_EBI_WS_11            0x90
#घोषणा INTEGRATOR_EBI_WS_12            0xA0
#घोषणा INTEGRATOR_EBI_WS_13            0xB0
#घोषणा INTEGRATOR_EBI_WS_14            0xC0
#घोषणा INTEGRATOR_EBI_WS_15            0xD0
#घोषणा INTEGRATOR_EBI_WS_16            0xE0
#घोषणा INTEGRATOR_EBI_WS_17            0xF0


#घोषणा INTEGRATOR_CT_BASE              0x13000000	 /*  Counter/Timers */
#घोषणा INTEGRATOR_IC_BASE              0x14000000	 /*  Interrupt Controller */
#घोषणा INTEGRATOR_RTC_BASE             0x15000000	 /*  Real Time Clock */
#घोषणा INTEGRATOR_UART0_BASE           0x16000000	 /*  UART 0 */
#घोषणा INTEGRATOR_UART1_BASE           0x17000000	 /*  UART 1 */
#घोषणा INTEGRATOR_KBD_BASE             0x18000000	 /*  Keyboard */
#घोषणा INTEGRATOR_MOUSE_BASE           0x19000000	 /*  Mouse */

/*
 *  LED's & Switches
 */
#घोषणा INTEGRATOR_DBG_ALPHA_OFFSET     0x00
#घोषणा INTEGRATOR_DBG_LEDS_OFFSET      0x04
#घोषणा INTEGRATOR_DBG_SWITCH_OFFSET    0x08

#घोषणा INTEGRATOR_DBG_BASE             0x1A000000
#घोषणा INTEGRATOR_DBG_ALPHA            (INTEGRATOR_DBG_BASE + INTEGRATOR_DBG_ALPHA_OFFSET)
#घोषणा INTEGRATOR_DBG_LEDS             (INTEGRATOR_DBG_BASE + INTEGRATOR_DBG_LEDS_OFFSET)
#घोषणा INTEGRATOR_DBG_SWITCH           (INTEGRATOR_DBG_BASE + INTEGRATOR_DBG_SWITCH_OFFSET)

#घोषणा INTEGRATOR_AP_GPIO_BASE		0x1B000000	/* GPIO */

#घोषणा INTEGRATOR_CP_MMC_BASE		0x1C000000	/* MMC */
#घोषणा INTEGRATOR_CP_AACI_BASE		0x1D000000	/* AACI */
#घोषणा INTEGRATOR_CP_ETH_BASE		0xC8000000	/* Ethernet */
#घोषणा INTEGRATOR_CP_GPIO_BASE		0xC9000000	/* GPIO */
#घोषणा INTEGRATOR_CP_SIC_BASE		0xCA000000	/* SIC */
#घोषणा INTEGRATOR_CP_CTL_BASE		0xCB000000	/* CP प्रणाली control */

/* PS2 Keyboard पूर्णांकerface */
#घोषणा KMI0_BASE                       INTEGRATOR_KBD_BASE

/* PS2 Mouse पूर्णांकerface */
#घोषणा KMI1_BASE                       INTEGRATOR_MOUSE_BASE

/*
 * Integrator Interrupt Controllers
 *
 *
 * Offsets from पूर्णांकerrupt controller base
 *
 * System Controller पूर्णांकerrupt controller base is
 *
 * 	INTEGRATOR_IC_BASE + (header_number << 6)
 *
 * Core Module पूर्णांकerrupt controller base is
 *
 * 	INTEGRATOR_HDR_IC
 */
#घोषणा IRQ_STATUS                      0
#घोषणा IRQ_RAW_STATUS                  0x04
#घोषणा IRQ_ENABLE                      0x08
#घोषणा IRQ_ENABLE_SET                  0x08
#घोषणा IRQ_ENABLE_CLEAR                0x0C

#घोषणा INT_SOFT_SET                    0x10
#घोषणा INT_SOFT_CLEAR                  0x14

#घोषणा FIQ_STATUS                      0x20
#घोषणा FIQ_RAW_STATUS                  0x24
#घोषणा FIQ_ENABLE                      0x28
#घोषणा FIQ_ENABLE_SET                  0x28
#घोषणा FIQ_ENABLE_CLEAR                0x2C


/*
 * LED's
 */
#घोषणा GREEN_LED                       0x01
#घोषणा YELLOW_LED                      0x02
#घोषणा RED_LED                         0x04
#घोषणा GREEN_LED_2                     0x08
#घोषणा ALL_LEDS                        0x0F

#घोषणा LED_BANK                        INTEGRATOR_DBG_LEDS

/*
 *  Timer definitions
 *
 *  Only use समयr 1 & 2
 *  (both run at 24MHz and will need the घड़ी भागider set to 16).
 *
 *  Timer 0 runs at bus frequency
 */
#घोषणा INTEGRATOR_TIMER0_BASE          INTEGRATOR_CT_BASE
#घोषणा INTEGRATOR_TIMER1_BASE          (INTEGRATOR_CT_BASE + 0x100)
#घोषणा INTEGRATOR_TIMER2_BASE          (INTEGRATOR_CT_BASE + 0x200)

#घोषणा INTEGRATOR_CSR_BASE             0x10000000
#घोषणा INTEGRATOR_CSR_SIZE             0x10000000

#पूर्ण_अगर /* INTEGRATOR_HARDWARE_H */
