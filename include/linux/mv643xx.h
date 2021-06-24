<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * mv643xx.h - MV-643XX Internal रेजिस्टरs definition file.
 *
 * Copyright 2002 Momentum Computer, Inc.
 * 	Author: Matthew Dharm <mdharm@momenco.com>
 * Copyright 2002 GALILEO TECHNOLOGY, LTD. 
 */
#अगर_अघोषित __ASM_MV643XX_H
#घोषणा __ASM_MV643XX_H

#समावेश <यंत्र/types.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/mv643xx_i2c.h>

/****************************************/
/* Processor Address Space              */
/****************************************/

/* DDR SDRAM BAR and size रेजिस्टरs */

#घोषणा MV64340_CS_0_BASE_ADDR                                      0x008
#घोषणा MV64340_CS_0_SIZE                                           0x010
#घोषणा MV64340_CS_1_BASE_ADDR                                      0x208
#घोषणा MV64340_CS_1_SIZE                                           0x210
#घोषणा MV64340_CS_2_BASE_ADDR                                      0x018
#घोषणा MV64340_CS_2_SIZE                                           0x020
#घोषणा MV64340_CS_3_BASE_ADDR                                      0x218
#घोषणा MV64340_CS_3_SIZE                                           0x220

/* Devices BAR and size रेजिस्टरs */

#घोषणा MV64340_DEV_CS0_BASE_ADDR                                   0x028
#घोषणा MV64340_DEV_CS0_SIZE                                        0x030
#घोषणा MV64340_DEV_CS1_BASE_ADDR                                   0x228
#घोषणा MV64340_DEV_CS1_SIZE                                        0x230
#घोषणा MV64340_DEV_CS2_BASE_ADDR                                   0x248
#घोषणा MV64340_DEV_CS2_SIZE                                        0x250
#घोषणा MV64340_DEV_CS3_BASE_ADDR                                   0x038
#घोषणा MV64340_DEV_CS3_SIZE                                        0x040
#घोषणा MV64340_BOOTCS_BASE_ADDR                                    0x238
#घोषणा MV64340_BOOTCS_SIZE                                         0x240

/* PCI 0 BAR and size रेजिस्टरs */

#घोषणा MV64340_PCI_0_IO_BASE_ADDR                                  0x048
#घोषणा MV64340_PCI_0_IO_SIZE                                       0x050
#घोषणा MV64340_PCI_0_MEMORY0_BASE_ADDR                             0x058
#घोषणा MV64340_PCI_0_MEMORY0_SIZE                                  0x060
#घोषणा MV64340_PCI_0_MEMORY1_BASE_ADDR                             0x080
#घोषणा MV64340_PCI_0_MEMORY1_SIZE                                  0x088
#घोषणा MV64340_PCI_0_MEMORY2_BASE_ADDR                             0x258
#घोषणा MV64340_PCI_0_MEMORY2_SIZE                                  0x260
#घोषणा MV64340_PCI_0_MEMORY3_BASE_ADDR                             0x280
#घोषणा MV64340_PCI_0_MEMORY3_SIZE                                  0x288

/* PCI 1 BAR and size रेजिस्टरs */
#घोषणा MV64340_PCI_1_IO_BASE_ADDR                                  0x090
#घोषणा MV64340_PCI_1_IO_SIZE                                       0x098
#घोषणा MV64340_PCI_1_MEMORY0_BASE_ADDR                             0x0a0
#घोषणा MV64340_PCI_1_MEMORY0_SIZE                                  0x0a8
#घोषणा MV64340_PCI_1_MEMORY1_BASE_ADDR                             0x0b0
#घोषणा MV64340_PCI_1_MEMORY1_SIZE                                  0x0b8
#घोषणा MV64340_PCI_1_MEMORY2_BASE_ADDR                             0x2a0
#घोषणा MV64340_PCI_1_MEMORY2_SIZE                                  0x2a8
#घोषणा MV64340_PCI_1_MEMORY3_BASE_ADDR                             0x2b0
#घोषणा MV64340_PCI_1_MEMORY3_SIZE                                  0x2b8

/* SRAM base address */
#घोषणा MV64340_INTEGRATED_SRAM_BASE_ADDR                           0x268

/* पूर्णांकernal रेजिस्टरs space base address */
#घोषणा MV64340_INTERNAL_SPACE_BASE_ADDR                            0x068

/* Enables the CS , DEV_CS , PCI 0 and PCI 1 
   winकरोws above */
#घोषणा MV64340_BASE_ADDR_ENABLE                                    0x278

/****************************************/
/* PCI remap रेजिस्टरs                  */
/****************************************/
      /* PCI 0 */
#घोषणा MV64340_PCI_0_IO_ADDR_REMAP                                 0x0f0
#घोषणा MV64340_PCI_0_MEMORY0_LOW_ADDR_REMAP                        0x0f8
#घोषणा MV64340_PCI_0_MEMORY0_HIGH_ADDR_REMAP                       0x320
#घोषणा MV64340_PCI_0_MEMORY1_LOW_ADDR_REMAP                        0x100
#घोषणा MV64340_PCI_0_MEMORY1_HIGH_ADDR_REMAP                       0x328
#घोषणा MV64340_PCI_0_MEMORY2_LOW_ADDR_REMAP                        0x2f8
#घोषणा MV64340_PCI_0_MEMORY2_HIGH_ADDR_REMAP                       0x330
#घोषणा MV64340_PCI_0_MEMORY3_LOW_ADDR_REMAP                        0x300
#घोषणा MV64340_PCI_0_MEMORY3_HIGH_ADDR_REMAP                       0x338
      /* PCI 1 */
#घोषणा MV64340_PCI_1_IO_ADDR_REMAP                                 0x108
#घोषणा MV64340_PCI_1_MEMORY0_LOW_ADDR_REMAP                        0x110
#घोषणा MV64340_PCI_1_MEMORY0_HIGH_ADDR_REMAP                       0x340
#घोषणा MV64340_PCI_1_MEMORY1_LOW_ADDR_REMAP                        0x118
#घोषणा MV64340_PCI_1_MEMORY1_HIGH_ADDR_REMAP                       0x348
#घोषणा MV64340_PCI_1_MEMORY2_LOW_ADDR_REMAP                        0x310
#घोषणा MV64340_PCI_1_MEMORY2_HIGH_ADDR_REMAP                       0x350
#घोषणा MV64340_PCI_1_MEMORY3_LOW_ADDR_REMAP                        0x318
#घोषणा MV64340_PCI_1_MEMORY3_HIGH_ADDR_REMAP                       0x358
 
#घोषणा MV64340_CPU_PCI_0_HEADERS_RETARGET_CONTROL                  0x3b0
#घोषणा MV64340_CPU_PCI_0_HEADERS_RETARGET_BASE                     0x3b8
#घोषणा MV64340_CPU_PCI_1_HEADERS_RETARGET_CONTROL                  0x3c0
#घोषणा MV64340_CPU_PCI_1_HEADERS_RETARGET_BASE                     0x3c8
#घोषणा MV64340_CPU_GE_HEADERS_RETARGET_CONTROL                     0x3d0
#घोषणा MV64340_CPU_GE_HEADERS_RETARGET_BASE                        0x3d8
#घोषणा MV64340_CPU_IDMA_HEADERS_RETARGET_CONTROL                   0x3e0
#घोषणा MV64340_CPU_IDMA_HEADERS_RETARGET_BASE                      0x3e8

/****************************************/
/*         CPU Control Registers        */
/****************************************/

#घोषणा MV64340_CPU_CONFIG                                          0x000
#घोषणा MV64340_CPU_MODE                                            0x120
#घोषणा MV64340_CPU_MASTER_CONTROL                                  0x160
#घोषणा MV64340_CPU_CROSS_BAR_CONTROL_LOW                           0x150
#घोषणा MV64340_CPU_CROSS_BAR_CONTROL_HIGH                          0x158
#घोषणा MV64340_CPU_CROSS_BAR_TIMEOUT                               0x168

/****************************************/
/* SMP RegisterS                        */
/****************************************/

#घोषणा MV64340_SMP_WHO_AM_I                                        0x200
#घोषणा MV64340_SMP_CPU0_DOORBELL                                   0x214
#घोषणा MV64340_SMP_CPU0_DOORBELL_CLEAR                             0x21C
#घोषणा MV64340_SMP_CPU1_DOORBELL                                   0x224
#घोषणा MV64340_SMP_CPU1_DOORBELL_CLEAR                             0x22C
#घोषणा MV64340_SMP_CPU0_DOORBELL_MASK                              0x234
#घोषणा MV64340_SMP_CPU1_DOORBELL_MASK                              0x23C
#घोषणा MV64340_SMP_SEMAPHOR0                                       0x244
#घोषणा MV64340_SMP_SEMAPHOR1                                       0x24c
#घोषणा MV64340_SMP_SEMAPHOR2                                       0x254
#घोषणा MV64340_SMP_SEMAPHOR3                                       0x25c
#घोषणा MV64340_SMP_SEMAPHOR4                                       0x264
#घोषणा MV64340_SMP_SEMAPHOR5                                       0x26c
#घोषणा MV64340_SMP_SEMAPHOR6                                       0x274
#घोषणा MV64340_SMP_SEMAPHOR7                                       0x27c

/****************************************/
/*  CPU Sync Barrier Register           */
/****************************************/

#घोषणा MV64340_CPU_0_SYNC_BARRIER_TRIGGER                          0x0c0
#घोषणा MV64340_CPU_0_SYNC_BARRIER_VIRTUAL                          0x0c8
#घोषणा MV64340_CPU_1_SYNC_BARRIER_TRIGGER                          0x0d0
#घोषणा MV64340_CPU_1_SYNC_BARRIER_VIRTUAL                          0x0d8

/****************************************/
/* CPU Access Protect                   */
/****************************************/

#घोषणा MV64340_CPU_PROTECT_WINDOW_0_BASE_ADDR                      0x180
#घोषणा MV64340_CPU_PROTECT_WINDOW_0_SIZE                           0x188
#घोषणा MV64340_CPU_PROTECT_WINDOW_1_BASE_ADDR                      0x190
#घोषणा MV64340_CPU_PROTECT_WINDOW_1_SIZE                           0x198
#घोषणा MV64340_CPU_PROTECT_WINDOW_2_BASE_ADDR                      0x1a0
#घोषणा MV64340_CPU_PROTECT_WINDOW_2_SIZE                           0x1a8
#घोषणा MV64340_CPU_PROTECT_WINDOW_3_BASE_ADDR                      0x1b0
#घोषणा MV64340_CPU_PROTECT_WINDOW_3_SIZE                           0x1b8


/****************************************/
/*          CPU Error Report            */
/****************************************/

#घोषणा MV64340_CPU_ERROR_ADDR_LOW                                  0x070
#घोषणा MV64340_CPU_ERROR_ADDR_HIGH                                 0x078
#घोषणा MV64340_CPU_ERROR_DATA_LOW                                  0x128
#घोषणा MV64340_CPU_ERROR_DATA_HIGH                                 0x130
#घोषणा MV64340_CPU_ERROR_PARITY                                    0x138
#घोषणा MV64340_CPU_ERROR_CAUSE                                     0x140
#घोषणा MV64340_CPU_ERROR_MASK                                      0x148

/****************************************/
/*      CPU Interface Debug Registers 	*/
/****************************************/

#घोषणा MV64340_PUNIT_SLAVE_DEBUG_LOW                               0x360
#घोषणा MV64340_PUNIT_SLAVE_DEBUG_HIGH                              0x368
#घोषणा MV64340_PUNIT_MASTER_DEBUG_LOW                              0x370
#घोषणा MV64340_PUNIT_MASTER_DEBUG_HIGH                             0x378
#घोषणा MV64340_PUNIT_MMASK                                         0x3e4

/****************************************/
/*  Integrated SRAM Registers           */
/****************************************/

#घोषणा MV64340_SRAM_CONFIG                                         0x380
#घोषणा MV64340_SRAM_TEST_MODE                                      0X3F4
#घोषणा MV64340_SRAM_ERROR_CAUSE                                    0x388
#घोषणा MV64340_SRAM_ERROR_ADDR                                     0x390
#घोषणा MV64340_SRAM_ERROR_ADDR_HIGH                                0X3F8
#घोषणा MV64340_SRAM_ERROR_DATA_LOW                                 0x398
#घोषणा MV64340_SRAM_ERROR_DATA_HIGH                                0x3a0
#घोषणा MV64340_SRAM_ERROR_DATA_PARITY                              0x3a8

/****************************************/
/* SDRAM Configuration                  */
/****************************************/

#घोषणा MV64340_SDRAM_CONFIG                                        0x1400
#घोषणा MV64340_D_UNIT_CONTROL_LOW                                  0x1404
#घोषणा MV64340_D_UNIT_CONTROL_HIGH                                 0x1424
#घोषणा MV64340_SDRAM_TIMING_CONTROL_LOW                            0x1408
#घोषणा MV64340_SDRAM_TIMING_CONTROL_HIGH                           0x140c
#घोषणा MV64340_SDRAM_ADDR_CONTROL                                  0x1410
#घोषणा MV64340_SDRAM_OPEN_PAGES_CONTROL                            0x1414
#घोषणा MV64340_SDRAM_OPERATION                                     0x1418
#घोषणा MV64340_SDRAM_MODE                                          0x141c
#घोषणा MV64340_EXTENDED_DRAM_MODE                                  0x1420
#घोषणा MV64340_SDRAM_CROSS_BAR_CONTROL_LOW                         0x1430
#घोषणा MV64340_SDRAM_CROSS_BAR_CONTROL_HIGH                        0x1434
#घोषणा MV64340_SDRAM_CROSS_BAR_TIMEOUT                             0x1438
#घोषणा MV64340_SDRAM_ADDR_CTRL_PADS_CALIBRATION                    0x14c0
#घोषणा MV64340_SDRAM_DATA_PADS_CALIBRATION                         0x14c4

/****************************************/
/* SDRAM Error Report                   */
/****************************************/

#घोषणा MV64340_SDRAM_ERROR_DATA_LOW                                0x1444
#घोषणा MV64340_SDRAM_ERROR_DATA_HIGH                               0x1440
#घोषणा MV64340_SDRAM_ERROR_ADDR                                    0x1450
#घोषणा MV64340_SDRAM_RECEIVED_ECC                                  0x1448
#घोषणा MV64340_SDRAM_CALCULATED_ECC                                0x144c
#घोषणा MV64340_SDRAM_ECC_CONTROL                                   0x1454
#घोषणा MV64340_SDRAM_ECC_ERROR_COUNTER                             0x1458

/******************************************/
/*  Controlled Delay Line (CDL) Registers */
/******************************************/

#घोषणा MV64340_DFCDL_CONFIG0                                       0x1480
#घोषणा MV64340_DFCDL_CONFIG1                                       0x1484
#घोषणा MV64340_DLL_WRITE                                           0x1488
#घोषणा MV64340_DLL_READ                                            0x148c
#घोषणा MV64340_SRAM_ADDR                                           0x1490
#घोषणा MV64340_SRAM_DATA0                                          0x1494
#घोषणा MV64340_SRAM_DATA1                                          0x1498
#घोषणा MV64340_SRAM_DATA2                                          0x149c
#घोषणा MV64340_DFCL_PROBE                                          0x14a0

/******************************************/
/*   Debug Registers                      */
/******************************************/

#घोषणा MV64340_DUNIT_DEBUG_LOW                                     0x1460
#घोषणा MV64340_DUNIT_DEBUG_HIGH                                    0x1464
#घोषणा MV64340_DUNIT_MMASK                                         0X1b40

/****************************************/
/* Device Parameters			*/
/****************************************/

#घोषणा MV64340_DEVICE_BANK0_PARAMETERS				    0x45c
#घोषणा MV64340_DEVICE_BANK1_PARAMETERS				    0x460
#घोषणा MV64340_DEVICE_BANK2_PARAMETERS				    0x464
#घोषणा MV64340_DEVICE_BANK3_PARAMETERS				    0x468
#घोषणा MV64340_DEVICE_BOOT_BANK_PARAMETERS			    0x46c
#घोषणा MV64340_DEVICE_INTERFACE_CONTROL                            0x4c0
#घोषणा MV64340_DEVICE_INTERFACE_CROSS_BAR_CONTROL_LOW              0x4c8
#घोषणा MV64340_DEVICE_INTERFACE_CROSS_BAR_CONTROL_HIGH             0x4cc
#घोषणा MV64340_DEVICE_INTERFACE_CROSS_BAR_TIMEOUT                  0x4c4

/****************************************/
/* Device पूर्णांकerrupt रेजिस्टरs		*/
/****************************************/

#घोषणा MV64340_DEVICE_INTERRUPT_CAUSE				    0x4d0
#घोषणा MV64340_DEVICE_INTERRUPT_MASK				    0x4d4
#घोषणा MV64340_DEVICE_ERROR_ADDR				    0x4d8
#घोषणा MV64340_DEVICE_ERROR_DATA   				    0x4dc
#घोषणा MV64340_DEVICE_ERROR_PARITY     			    0x4e0

/****************************************/
/* Device debug रेजिस्टरs   		*/
/****************************************/

#घोषणा MV64340_DEVICE_DEBUG_LOW     				    0x4e4
#घोषणा MV64340_DEVICE_DEBUG_HIGH     				    0x4e8
#घोषणा MV64340_RUNIT_MMASK                                         0x4f0

/****************************************/
/* PCI Slave Address Decoding रेजिस्टरs */
/****************************************/

#घोषणा MV64340_PCI_0_CS_0_BANK_SIZE                                0xc08
#घोषणा MV64340_PCI_1_CS_0_BANK_SIZE                                0xc88
#घोषणा MV64340_PCI_0_CS_1_BANK_SIZE                                0xd08
#घोषणा MV64340_PCI_1_CS_1_BANK_SIZE                                0xd88
#घोषणा MV64340_PCI_0_CS_2_BANK_SIZE                                0xc0c
#घोषणा MV64340_PCI_1_CS_2_BANK_SIZE                                0xc8c
#घोषणा MV64340_PCI_0_CS_3_BANK_SIZE                                0xd0c
#घोषणा MV64340_PCI_1_CS_3_BANK_SIZE                                0xd8c
#घोषणा MV64340_PCI_0_DEVCS_0_BANK_SIZE                             0xc10
#घोषणा MV64340_PCI_1_DEVCS_0_BANK_SIZE                             0xc90
#घोषणा MV64340_PCI_0_DEVCS_1_BANK_SIZE                             0xd10
#घोषणा MV64340_PCI_1_DEVCS_1_BANK_SIZE                             0xd90
#घोषणा MV64340_PCI_0_DEVCS_2_BANK_SIZE                             0xd18
#घोषणा MV64340_PCI_1_DEVCS_2_BANK_SIZE                             0xd98
#घोषणा MV64340_PCI_0_DEVCS_3_BANK_SIZE                             0xc14
#घोषणा MV64340_PCI_1_DEVCS_3_BANK_SIZE                             0xc94
#घोषणा MV64340_PCI_0_DEVCS_BOOT_BANK_SIZE                          0xd14
#घोषणा MV64340_PCI_1_DEVCS_BOOT_BANK_SIZE                          0xd94
#घोषणा MV64340_PCI_0_P2P_MEM0_BAR_SIZE                             0xd1c
#घोषणा MV64340_PCI_1_P2P_MEM0_BAR_SIZE                             0xd9c
#घोषणा MV64340_PCI_0_P2P_MEM1_BAR_SIZE                             0xd20
#घोषणा MV64340_PCI_1_P2P_MEM1_BAR_SIZE                             0xda0
#घोषणा MV64340_PCI_0_P2P_I_O_BAR_SIZE                              0xd24
#घोषणा MV64340_PCI_1_P2P_I_O_BAR_SIZE                              0xda4
#घोषणा MV64340_PCI_0_CPU_BAR_SIZE                                  0xd28
#घोषणा MV64340_PCI_1_CPU_BAR_SIZE                                  0xda8
#घोषणा MV64340_PCI_0_INTERNAL_SRAM_BAR_SIZE                        0xe00
#घोषणा MV64340_PCI_1_INTERNAL_SRAM_BAR_SIZE                        0xe80
#घोषणा MV64340_PCI_0_EXPANSION_ROM_BAR_SIZE                        0xd2c
#घोषणा MV64340_PCI_1_EXPANSION_ROM_BAR_SIZE                        0xd9c
#घोषणा MV64340_PCI_0_BASE_ADDR_REG_ENABLE                          0xc3c
#घोषणा MV64340_PCI_1_BASE_ADDR_REG_ENABLE                          0xcbc
#घोषणा MV64340_PCI_0_CS_0_BASE_ADDR_REMAP			    0xc48
#घोषणा MV64340_PCI_1_CS_0_BASE_ADDR_REMAP			    0xcc8
#घोषणा MV64340_PCI_0_CS_1_BASE_ADDR_REMAP			    0xd48
#घोषणा MV64340_PCI_1_CS_1_BASE_ADDR_REMAP			    0xdc8
#घोषणा MV64340_PCI_0_CS_2_BASE_ADDR_REMAP			    0xc4c
#घोषणा MV64340_PCI_1_CS_2_BASE_ADDR_REMAP			    0xccc
#घोषणा MV64340_PCI_0_CS_3_BASE_ADDR_REMAP			    0xd4c
#घोषणा MV64340_PCI_1_CS_3_BASE_ADDR_REMAP			    0xdcc
#घोषणा MV64340_PCI_0_CS_0_BASE_HIGH_ADDR_REMAP			    0xF04
#घोषणा MV64340_PCI_1_CS_0_BASE_HIGH_ADDR_REMAP			    0xF84
#घोषणा MV64340_PCI_0_CS_1_BASE_HIGH_ADDR_REMAP			    0xF08
#घोषणा MV64340_PCI_1_CS_1_BASE_HIGH_ADDR_REMAP			    0xF88
#घोषणा MV64340_PCI_0_CS_2_BASE_HIGH_ADDR_REMAP			    0xF0C
#घोषणा MV64340_PCI_1_CS_2_BASE_HIGH_ADDR_REMAP			    0xF8C
#घोषणा MV64340_PCI_0_CS_3_BASE_HIGH_ADDR_REMAP			    0xF10
#घोषणा MV64340_PCI_1_CS_3_BASE_HIGH_ADDR_REMAP			    0xF90
#घोषणा MV64340_PCI_0_DEVCS_0_BASE_ADDR_REMAP			    0xc50
#घोषणा MV64340_PCI_1_DEVCS_0_BASE_ADDR_REMAP			    0xcd0
#घोषणा MV64340_PCI_0_DEVCS_1_BASE_ADDR_REMAP			    0xd50
#घोषणा MV64340_PCI_1_DEVCS_1_BASE_ADDR_REMAP			    0xdd0
#घोषणा MV64340_PCI_0_DEVCS_2_BASE_ADDR_REMAP			    0xd58
#घोषणा MV64340_PCI_1_DEVCS_2_BASE_ADDR_REMAP			    0xdd8
#घोषणा MV64340_PCI_0_DEVCS_3_BASE_ADDR_REMAP           	    0xc54
#घोषणा MV64340_PCI_1_DEVCS_3_BASE_ADDR_REMAP           	    0xcd4
#घोषणा MV64340_PCI_0_DEVCS_BOOTCS_BASE_ADDR_REMAP      	    0xd54
#घोषणा MV64340_PCI_1_DEVCS_BOOTCS_BASE_ADDR_REMAP      	    0xdd4
#घोषणा MV64340_PCI_0_P2P_MEM0_BASE_ADDR_REMAP_LOW                  0xd5c
#घोषणा MV64340_PCI_1_P2P_MEM0_BASE_ADDR_REMAP_LOW                  0xddc
#घोषणा MV64340_PCI_0_P2P_MEM0_BASE_ADDR_REMAP_HIGH                 0xd60
#घोषणा MV64340_PCI_1_P2P_MEM0_BASE_ADDR_REMAP_HIGH                 0xde0
#घोषणा MV64340_PCI_0_P2P_MEM1_BASE_ADDR_REMAP_LOW                  0xd64
#घोषणा MV64340_PCI_1_P2P_MEM1_BASE_ADDR_REMAP_LOW                  0xde4
#घोषणा MV64340_PCI_0_P2P_MEM1_BASE_ADDR_REMAP_HIGH                 0xd68
#घोषणा MV64340_PCI_1_P2P_MEM1_BASE_ADDR_REMAP_HIGH                 0xde8
#घोषणा MV64340_PCI_0_P2P_I_O_BASE_ADDR_REMAP                       0xd6c
#घोषणा MV64340_PCI_1_P2P_I_O_BASE_ADDR_REMAP                       0xdec 
#घोषणा MV64340_PCI_0_CPU_BASE_ADDR_REMAP_LOW                       0xd70
#घोषणा MV64340_PCI_1_CPU_BASE_ADDR_REMAP_LOW                       0xdf0
#घोषणा MV64340_PCI_0_CPU_BASE_ADDR_REMAP_HIGH                      0xd74
#घोषणा MV64340_PCI_1_CPU_BASE_ADDR_REMAP_HIGH                      0xdf4
#घोषणा MV64340_PCI_0_INTEGRATED_SRAM_BASE_ADDR_REMAP               0xf00
#घोषणा MV64340_PCI_1_INTEGRATED_SRAM_BASE_ADDR_REMAP               0xf80
#घोषणा MV64340_PCI_0_EXPANSION_ROM_BASE_ADDR_REMAP                 0xf38
#घोषणा MV64340_PCI_1_EXPANSION_ROM_BASE_ADDR_REMAP                 0xfb8
#घोषणा MV64340_PCI_0_ADDR_DECODE_CONTROL                           0xd3c
#घोषणा MV64340_PCI_1_ADDR_DECODE_CONTROL                           0xdbc
#घोषणा MV64340_PCI_0_HEADERS_RETARGET_CONTROL                      0xF40
#घोषणा MV64340_PCI_1_HEADERS_RETARGET_CONTROL                      0xFc0
#घोषणा MV64340_PCI_0_HEADERS_RETARGET_BASE                         0xF44
#घोषणा MV64340_PCI_1_HEADERS_RETARGET_BASE                         0xFc4
#घोषणा MV64340_PCI_0_HEADERS_RETARGET_HIGH                         0xF48
#घोषणा MV64340_PCI_1_HEADERS_RETARGET_HIGH                         0xFc8

/***********************************/
/*   PCI Control Register Map      */
/***********************************/

#घोषणा MV64340_PCI_0_DLL_STATUS_AND_COMMAND                        0x1d20
#घोषणा MV64340_PCI_1_DLL_STATUS_AND_COMMAND                        0x1da0
#घोषणा MV64340_PCI_0_MPP_PADS_DRIVE_CONTROL                        0x1d1C
#घोषणा MV64340_PCI_1_MPP_PADS_DRIVE_CONTROL                        0x1d9C
#घोषणा MV64340_PCI_0_COMMAND			         	    0xc00
#घोषणा MV64340_PCI_1_COMMAND					    0xc80
#घोषणा MV64340_PCI_0_MODE                                          0xd00
#घोषणा MV64340_PCI_1_MODE                                          0xd80
#घोषणा MV64340_PCI_0_RETRY	        	 		    0xc04
#घोषणा MV64340_PCI_1_RETRY				            0xc84
#घोषणा MV64340_PCI_0_READ_BUFFER_DISCARD_TIMER                     0xd04
#घोषणा MV64340_PCI_1_READ_BUFFER_DISCARD_TIMER                     0xd84
#घोषणा MV64340_PCI_0_MSI_TRIGGER_TIMER                             0xc38
#घोषणा MV64340_PCI_1_MSI_TRIGGER_TIMER                             0xcb8
#घोषणा MV64340_PCI_0_ARBITER_CONTROL                               0x1d00
#घोषणा MV64340_PCI_1_ARBITER_CONTROL                               0x1d80
#घोषणा MV64340_PCI_0_CROSS_BAR_CONTROL_LOW                         0x1d08
#घोषणा MV64340_PCI_1_CROSS_BAR_CONTROL_LOW                         0x1d88
#घोषणा MV64340_PCI_0_CROSS_BAR_CONTROL_HIGH                        0x1d0c
#घोषणा MV64340_PCI_1_CROSS_BAR_CONTROL_HIGH                        0x1d8c
#घोषणा MV64340_PCI_0_CROSS_BAR_TIMEOUT                             0x1d04
#घोषणा MV64340_PCI_1_CROSS_BAR_TIMEOUT                             0x1d84
#घोषणा MV64340_PCI_0_SYNC_BARRIER_TRIGGER_REG                      0x1D18
#घोषणा MV64340_PCI_1_SYNC_BARRIER_TRIGGER_REG                      0x1D98
#घोषणा MV64340_PCI_0_SYNC_BARRIER_VIRTUAL_REG                      0x1d10
#घोषणा MV64340_PCI_1_SYNC_BARRIER_VIRTUAL_REG                      0x1d90
#घोषणा MV64340_PCI_0_P2P_CONFIG                                    0x1d14
#घोषणा MV64340_PCI_1_P2P_CONFIG                                    0x1d94

#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_0_LOW                     0x1e00
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_0_HIGH                    0x1e04
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_SIZE_0                         0x1e08
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_1_LOW                     0x1e10
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_1_HIGH                    0x1e14
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_SIZE_1                         0x1e18
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_2_LOW                     0x1e20
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_2_HIGH                    0x1e24
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_SIZE_2                         0x1e28
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_3_LOW                     0x1e30
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_3_HIGH                    0x1e34
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_SIZE_3                         0x1e38
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_4_LOW                     0x1e40
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_4_HIGH                    0x1e44
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_SIZE_4                         0x1e48
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_5_LOW                     0x1e50
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_BASE_5_HIGH                    0x1e54
#घोषणा MV64340_PCI_0_ACCESS_CONTROL_SIZE_5                         0x1e58

#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_0_LOW                     0x1e80
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_0_HIGH                    0x1e84
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_SIZE_0                         0x1e88
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_1_LOW                     0x1e90
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_1_HIGH                    0x1e94
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_SIZE_1                         0x1e98
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_2_LOW                     0x1ea0
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_2_HIGH                    0x1ea4
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_SIZE_2                         0x1ea8
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_3_LOW                     0x1eb0
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_3_HIGH                    0x1eb4
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_SIZE_3                         0x1eb8
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_4_LOW                     0x1ec0
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_4_HIGH                    0x1ec4
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_SIZE_4                         0x1ec8
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_5_LOW                     0x1ed0
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_BASE_5_HIGH                    0x1ed4
#घोषणा MV64340_PCI_1_ACCESS_CONTROL_SIZE_5                         0x1ed8

/****************************************/
/*   PCI Configuration Access Registers */
/****************************************/

#घोषणा MV64340_PCI_0_CONFIG_ADDR 				    0xcf8
#घोषणा MV64340_PCI_0_CONFIG_DATA_VIRTUAL_REG                       0xcfc
#घोषणा MV64340_PCI_1_CONFIG_ADDR 				    0xc78
#घोषणा MV64340_PCI_1_CONFIG_DATA_VIRTUAL_REG                       0xc7c
#घोषणा MV64340_PCI_0_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG	            0xc34
#घोषणा MV64340_PCI_1_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG	            0xcb4

/****************************************/
/*   PCI Error Report Registers         */
/****************************************/

#घोषणा MV64340_PCI_0_SERR_MASK					    0xc28
#घोषणा MV64340_PCI_1_SERR_MASK					    0xca8
#घोषणा MV64340_PCI_0_ERROR_ADDR_LOW                                0x1d40
#घोषणा MV64340_PCI_1_ERROR_ADDR_LOW                                0x1dc0
#घोषणा MV64340_PCI_0_ERROR_ADDR_HIGH                               0x1d44
#घोषणा MV64340_PCI_1_ERROR_ADDR_HIGH                               0x1dc4
#घोषणा MV64340_PCI_0_ERROR_ATTRIBUTE                               0x1d48
#घोषणा MV64340_PCI_1_ERROR_ATTRIBUTE                               0x1dc8
#घोषणा MV64340_PCI_0_ERROR_COMMAND                                 0x1d50
#घोषणा MV64340_PCI_1_ERROR_COMMAND                                 0x1dd0
#घोषणा MV64340_PCI_0_ERROR_CAUSE                                   0x1d58
#घोषणा MV64340_PCI_1_ERROR_CAUSE                                   0x1dd8
#घोषणा MV64340_PCI_0_ERROR_MASK                                    0x1d5c
#घोषणा MV64340_PCI_1_ERROR_MASK                                    0x1ddc

/****************************************/
/*   PCI Debug Registers                */
/****************************************/

#घोषणा MV64340_PCI_0_MMASK                                         0X1D24
#घोषणा MV64340_PCI_1_MMASK                                         0X1DA4

/*********************************************/
/* PCI Configuration, Function 0, Registers  */
/*********************************************/

#घोषणा MV64340_PCI_DEVICE_AND_VENDOR_ID 			    0x000
#घोषणा MV64340_PCI_STATUS_AND_COMMAND				    0x004
#घोषणा MV64340_PCI_CLASS_CODE_AND_REVISION_ID			    0x008
#घोषणा MV64340_PCI_BIST_HEADER_TYPE_LATENCY_TIMER_CACHE_LINE 	    0x00C

#घोषणा MV64340_PCI_SCS_0_BASE_ADDR_LOW   	      		    0x010
#घोषणा MV64340_PCI_SCS_0_BASE_ADDR_HIGH   		            0x014
#घोषणा MV64340_PCI_SCS_1_BASE_ADDR_LOW  	     	            0x018
#घोषणा MV64340_PCI_SCS_1_BASE_ADDR_HIGH 		            0x01C
#घोषणा MV64340_PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_LOW      	    0x020
#घोषणा MV64340_PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_HIGH     	    0x024
#घोषणा MV64340_PCI_SUBSYSTEM_ID_AND_SUBSYSTEM_VENDOR_ID	    0x02c
#घोषणा MV64340_PCI_EXPANSION_ROM_BASE_ADDR_REG	                    0x030
#घोषणा MV64340_PCI_CAPABILTY_LIST_POINTER                          0x034
#घोषणा MV64340_PCI_INTERRUPT_PIN_AND_LINE 			    0x03C
       /* capability list */
#घोषणा MV64340_PCI_POWER_MANAGEMENT_CAPABILITY                     0x040
#घोषणा MV64340_PCI_POWER_MANAGEMENT_STATUS_AND_CONTROL             0x044
#घोषणा MV64340_PCI_VPD_ADDR                                        0x048
#घोषणा MV64340_PCI_VPD_DATA                                        0x04c
#घोषणा MV64340_PCI_MSI_MESSAGE_CONTROL                             0x050
#घोषणा MV64340_PCI_MSI_MESSAGE_ADDR                                0x054
#घोषणा MV64340_PCI_MSI_MESSAGE_UPPER_ADDR                          0x058
#घोषणा MV64340_PCI_MSI_MESSAGE_DATA                                0x05c
#घोषणा MV64340_PCI_X_COMMAND                                       0x060
#घोषणा MV64340_PCI_X_STATUS                                        0x064
#घोषणा MV64340_PCI_COMPACT_PCI_HOT_SWAP                            0x068

/***********************************************/
/*   PCI Configuration, Function 1, Registers  */
/***********************************************/

#घोषणा MV64340_PCI_SCS_2_BASE_ADDR_LOW   			    0x110
#घोषणा MV64340_PCI_SCS_2_BASE_ADDR_HIGH			    0x114
#घोषणा MV64340_PCI_SCS_3_BASE_ADDR_LOW 			    0x118
#घोषणा MV64340_PCI_SCS_3_BASE_ADDR_HIGH			    0x11c
#घोषणा MV64340_PCI_INTERNAL_SRAM_BASE_ADDR_LOW          	    0x120
#घोषणा MV64340_PCI_INTERNAL_SRAM_BASE_ADDR_HIGH         	    0x124

/***********************************************/
/*  PCI Configuration, Function 2, Registers   */
/***********************************************/

#घोषणा MV64340_PCI_DEVCS_0_BASE_ADDR_LOW	    		    0x210
#घोषणा MV64340_PCI_DEVCS_0_BASE_ADDR_HIGH 			    0x214
#घोषणा MV64340_PCI_DEVCS_1_BASE_ADDR_LOW 			    0x218
#घोषणा MV64340_PCI_DEVCS_1_BASE_ADDR_HIGH      		    0x21c
#घोषणा MV64340_PCI_DEVCS_2_BASE_ADDR_LOW 			    0x220
#घोषणा MV64340_PCI_DEVCS_2_BASE_ADDR_HIGH      		    0x224

/***********************************************/
/*  PCI Configuration, Function 3, Registers   */
/***********************************************/

#घोषणा MV64340_PCI_DEVCS_3_BASE_ADDR_LOW	    		    0x310
#घोषणा MV64340_PCI_DEVCS_3_BASE_ADDR_HIGH 			    0x314
#घोषणा MV64340_PCI_BOOT_CS_BASE_ADDR_LOW			    0x318
#घोषणा MV64340_PCI_BOOT_CS_BASE_ADDR_HIGH      		    0x31c
#घोषणा MV64340_PCI_CPU_BASE_ADDR_LOW 				    0x220
#घोषणा MV64340_PCI_CPU_BASE_ADDR_HIGH      			    0x224

/***********************************************/
/*  PCI Configuration, Function 4, Registers   */
/***********************************************/

#घोषणा MV64340_PCI_P2P_MEM0_BASE_ADDR_LOW  			    0x410
#घोषणा MV64340_PCI_P2P_MEM0_BASE_ADDR_HIGH 			    0x414
#घोषणा MV64340_PCI_P2P_MEM1_BASE_ADDR_LOW   			    0x418
#घोषणा MV64340_PCI_P2P_MEM1_BASE_ADDR_HIGH 			    0x41c
#घोषणा MV64340_PCI_P2P_I_O_BASE_ADDR                 	            0x420
#घोषणा MV64340_PCI_INTERNAL_REGS_I_O_MAPPED_BASE_ADDR              0x424

/****************************************/
/* Messaging Unit Registers (I20)   	*/
/****************************************/

#घोषणा MV64340_I2O_INBOUND_MESSAGE_REG0_PCI_0_SIDE		    0x010
#घोषणा MV64340_I2O_INBOUND_MESSAGE_REG1_PCI_0_SIDE  		    0x014
#घोषणा MV64340_I2O_OUTBOUND_MESSAGE_REG0_PCI_0_SIDE 		    0x018
#घोषणा MV64340_I2O_OUTBOUND_MESSAGE_REG1_PCI_0_SIDE  		    0x01C
#घोषणा MV64340_I2O_INBOUND_DOORBELL_REG_PCI_0_SIDE  		    0x020
#घोषणा MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE          0x024
#घोषणा MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_PCI_0_SIDE	    0x028
#घोषणा MV64340_I2O_OUTBOUND_DOORBELL_REG_PCI_0_SIDE 		    0x02C
#घोषणा MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE         0x030
#घोषणा MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_PCI_0_SIDE          0x034
#घोषणा MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_0_SIDE       0x040
#घोषणा MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_0_SIDE      0x044
#घोषणा MV64340_I2O_QUEUE_CONTROL_REG_PCI_0_SIDE 		    0x050
#घोषणा MV64340_I2O_QUEUE_BASE_ADDR_REG_PCI_0_SIDE 		    0x054
#घोषणा MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_PCI_0_SIDE        0x060
#घोषणा MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_PCI_0_SIDE        0x064
#घोषणा MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_PCI_0_SIDE        0x068
#घोषणा MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_PCI_0_SIDE        0x06C
#घोषणा MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_PCI_0_SIDE       0x070
#घोषणा MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_PCI_0_SIDE       0x074
#घोषणा MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_PCI_0_SIDE       0x0F8
#घोषणा MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_PCI_0_SIDE       0x0FC

#घोषणा MV64340_I2O_INBOUND_MESSAGE_REG0_PCI_1_SIDE		    0x090
#घोषणा MV64340_I2O_INBOUND_MESSAGE_REG1_PCI_1_SIDE  		    0x094
#घोषणा MV64340_I2O_OUTBOUND_MESSAGE_REG0_PCI_1_SIDE 		    0x098
#घोषणा MV64340_I2O_OUTBOUND_MESSAGE_REG1_PCI_1_SIDE  		    0x09C
#घोषणा MV64340_I2O_INBOUND_DOORBELL_REG_PCI_1_SIDE  		    0x0A0
#घोषणा MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_PCI_1_SIDE          0x0A4
#घोषणा MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_PCI_1_SIDE	    0x0A8
#घोषणा MV64340_I2O_OUTBOUND_DOORBELL_REG_PCI_1_SIDE 		    0x0AC
#घोषणा MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_PCI_1_SIDE         0x0B0
#घोषणा MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_PCI_1_SIDE          0x0B4
#घोषणा MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_1_SIDE       0x0C0
#घोषणा MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_1_SIDE      0x0C4
#घोषणा MV64340_I2O_QUEUE_CONTROL_REG_PCI_1_SIDE 		    0x0D0
#घोषणा MV64340_I2O_QUEUE_BASE_ADDR_REG_PCI_1_SIDE 		    0x0D4
#घोषणा MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_PCI_1_SIDE        0x0E0
#घोषणा MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_PCI_1_SIDE        0x0E4
#घोषणा MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_PCI_1_SIDE        0x0E8
#घोषणा MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_PCI_1_SIDE        0x0EC
#घोषणा MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_PCI_1_SIDE       0x0F0
#घोषणा MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_PCI_1_SIDE       0x0F4
#घोषणा MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_PCI_1_SIDE       0x078
#घोषणा MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_PCI_1_SIDE       0x07C

#घोषणा MV64340_I2O_INBOUND_MESSAGE_REG0_CPU0_SIDE		    0x1C10
#घोषणा MV64340_I2O_INBOUND_MESSAGE_REG1_CPU0_SIDE  		    0x1C14
#घोषणा MV64340_I2O_OUTBOUND_MESSAGE_REG0_CPU0_SIDE 		    0x1C18
#घोषणा MV64340_I2O_OUTBOUND_MESSAGE_REG1_CPU0_SIDE  		    0x1C1C
#घोषणा MV64340_I2O_INBOUND_DOORBELL_REG_CPU0_SIDE  		    0x1C20
#घोषणा MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_CPU0_SIDE  	    0x1C24
#घोषणा MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_CPU0_SIDE	    0x1C28
#घोषणा MV64340_I2O_OUTBOUND_DOORBELL_REG_CPU0_SIDE 		    0x1C2C
#घोषणा MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_CPU0_SIDE          0x1C30
#घोषणा MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_CPU0_SIDE           0x1C34
#घोषणा MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_CPU0_SIDE        0x1C40
#घोषणा MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_CPU0_SIDE       0x1C44
#घोषणा MV64340_I2O_QUEUE_CONTROL_REG_CPU0_SIDE 		    0x1C50
#घोषणा MV64340_I2O_QUEUE_BASE_ADDR_REG_CPU0_SIDE 		    0x1C54
#घोषणा MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_CPU0_SIDE         0x1C60
#घोषणा MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_CPU0_SIDE         0x1C64
#घोषणा MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_CPU0_SIDE         0x1C68
#घोषणा MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_CPU0_SIDE         0x1C6C
#घोषणा MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_CPU0_SIDE        0x1C70
#घोषणा MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_CPU0_SIDE        0x1C74
#घोषणा MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_CPU0_SIDE        0x1CF8
#घोषणा MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_CPU0_SIDE        0x1CFC
#घोषणा MV64340_I2O_INBOUND_MESSAGE_REG0_CPU1_SIDE		    0x1C90
#घोषणा MV64340_I2O_INBOUND_MESSAGE_REG1_CPU1_SIDE  		    0x1C94
#घोषणा MV64340_I2O_OUTBOUND_MESSAGE_REG0_CPU1_SIDE 		    0x1C98
#घोषणा MV64340_I2O_OUTBOUND_MESSAGE_REG1_CPU1_SIDE  		    0x1C9C
#घोषणा MV64340_I2O_INBOUND_DOORBELL_REG_CPU1_SIDE  		    0x1CA0
#घोषणा MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_CPU1_SIDE  	    0x1CA4
#घोषणा MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_CPU1_SIDE	    0x1CA8
#घोषणा MV64340_I2O_OUTBOUND_DOORBELL_REG_CPU1_SIDE 		    0x1CAC
#घोषणा MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_CPU1_SIDE          0x1CB0
#घोषणा MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_CPU1_SIDE           0x1CB4
#घोषणा MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_CPU1_SIDE        0x1CC0
#घोषणा MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_CPU1_SIDE       0x1CC4
#घोषणा MV64340_I2O_QUEUE_CONTROL_REG_CPU1_SIDE 		    0x1CD0
#घोषणा MV64340_I2O_QUEUE_BASE_ADDR_REG_CPU1_SIDE 		    0x1CD4
#घोषणा MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_CPU1_SIDE         0x1CE0
#घोषणा MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_CPU1_SIDE         0x1CE4
#घोषणा MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_CPU1_SIDE         0x1CE8
#घोषणा MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_CPU1_SIDE         0x1CEC
#घोषणा MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_CPU1_SIDE        0x1CF0
#घोषणा MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_CPU1_SIDE        0x1CF4
#घोषणा MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_CPU1_SIDE        0x1C78
#घोषणा MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_CPU1_SIDE        0x1C7C

/****************************************/
/*        Ethernet Unit Registers  		*/
/****************************************/

/*******************************************/
/*          CUNIT  Registers               */
/*******************************************/

         /* Address Decoding Register Map */
           
#घोषणा MV64340_CUNIT_BASE_ADDR_REG0                                0xf200
#घोषणा MV64340_CUNIT_BASE_ADDR_REG1                                0xf208
#घोषणा MV64340_CUNIT_BASE_ADDR_REG2                                0xf210
#घोषणा MV64340_CUNIT_BASE_ADDR_REG3                                0xf218
#घोषणा MV64340_CUNIT_SIZE0                                         0xf204
#घोषणा MV64340_CUNIT_SIZE1                                         0xf20c
#घोषणा MV64340_CUNIT_SIZE2                                         0xf214
#घोषणा MV64340_CUNIT_SIZE3                                         0xf21c
#घोषणा MV64340_CUNIT_HIGH_ADDR_REMAP_REG0                          0xf240
#घोषणा MV64340_CUNIT_HIGH_ADDR_REMAP_REG1                          0xf244
#घोषणा MV64340_CUNIT_BASE_ADDR_ENABLE_REG                          0xf250
#घोषणा MV64340_MPSC0_ACCESS_PROTECTION_REG                         0xf254
#घोषणा MV64340_MPSC1_ACCESS_PROTECTION_REG                         0xf258
#घोषणा MV64340_CUNIT_INTERNAL_SPACE_BASE_ADDR_REG                  0xf25C

        /*  Error Report Registers  */

#घोषणा MV64340_CUNIT_INTERRUPT_CAUSE_REG                           0xf310
#घोषणा MV64340_CUNIT_INTERRUPT_MASK_REG                            0xf314
#घोषणा MV64340_CUNIT_ERROR_ADDR                                    0xf318

        /*  Cunit Control Registers */

#घोषणा MV64340_CUNIT_ARBITER_CONTROL_REG                           0xf300
#घोषणा MV64340_CUNIT_CONFIG_REG                                    0xb40c
#घोषणा MV64340_CUNIT_CRROSBAR_TIMEOUT_REG                          0xf304

        /*  Cunit Debug Registers   */

#घोषणा MV64340_CUNIT_DEBUG_LOW                                     0xf340
#घोषणा MV64340_CUNIT_DEBUG_HIGH                                    0xf344
#घोषणा MV64340_CUNIT_MMASK                                         0xf380

        /*  MPSCs Clocks Routing Registers  */

#घोषणा MV64340_MPSC_ROUTING_REG                                    0xb400
#घोषणा MV64340_MPSC_RX_CLOCK_ROUTING_REG                           0xb404
#घोषणा MV64340_MPSC_TX_CLOCK_ROUTING_REG                           0xb408

        /*  MPSCs Interrupts Registers    */

#घोषणा MV64340_MPSC_CAUSE_REG(port)                               (0xb804 + (port<<3))
#घोषणा MV64340_MPSC_MASK_REG(port)                                (0xb884 + (port<<3))
 
#घोषणा MV64340_MPSC_MAIN_CONFIG_LOW(port)                         (0x8000 + (port<<12))
#घोषणा MV64340_MPSC_MAIN_CONFIG_HIGH(port)                        (0x8004 + (port<<12))    
#घोषणा MV64340_MPSC_PROTOCOL_CONFIG(port)                         (0x8008 + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG1(port)                            (0x800c + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG2(port)                            (0x8010 + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG3(port)                            (0x8014 + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG4(port)                            (0x8018 + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG5(port)                            (0x801c + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG6(port)                            (0x8020 + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG7(port)                            (0x8024 + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG8(port)                            (0x8028 + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG9(port)                            (0x802c + (port<<12))    
#घोषणा MV64340_MPSC_CHANNEL_REG10(port)                           (0x8030 + (port<<12))    
        
        /*  MPSC0 Registers      */


/***************************************/
/*          SDMA Registers             */
/***************************************/

#घोषणा MV64340_SDMA_CONFIG_REG(channel)                        (0x4000 + (channel<<13))        
#घोषणा MV64340_SDMA_COMMAND_REG(channel)                       (0x4008 + (channel<<13))        
#घोषणा MV64340_SDMA_CURRENT_RX_DESCRIPTOR_POINTER(channel)     (0x4810 + (channel<<13))        
#घोषणा MV64340_SDMA_CURRENT_TX_DESCRIPTOR_POINTER(channel)     (0x4c10 + (channel<<13))        
#घोषणा MV64340_SDMA_FIRST_TX_DESCRIPTOR_POINTER(channel)       (0x4c14 + (channel<<13)) 

#घोषणा MV64340_SDMA_CAUSE_REG                                      0xb800
#घोषणा MV64340_SDMA_MASK_REG                                       0xb880
         
/* BRG Interrupts */

#घोषणा MV64340_BRG_CONFIG_REG(brg)                              (0xb200 + (brg<<3))
#घोषणा MV64340_BRG_BAUDE_TUNING_REG(brg)                        (0xb208 + (brg<<3))
#घोषणा MV64340_BRG_CAUSE_REG                                       0xb834
#घोषणा MV64340_BRG_MASK_REG                                        0xb8b4

/****************************************/
/* DMA Channel Control			*/
/****************************************/

#घोषणा MV64340_DMA_CHANNEL0_CONTROL 				    0x840
#घोषणा MV64340_DMA_CHANNEL0_CONTROL_HIGH			    0x880
#घोषणा MV64340_DMA_CHANNEL1_CONTROL 				    0x844
#घोषणा MV64340_DMA_CHANNEL1_CONTROL_HIGH			    0x884
#घोषणा MV64340_DMA_CHANNEL2_CONTROL 				    0x848
#घोषणा MV64340_DMA_CHANNEL2_CONTROL_HIGH			    0x888
#घोषणा MV64340_DMA_CHANNEL3_CONTROL 				    0x84C
#घोषणा MV64340_DMA_CHANNEL3_CONTROL_HIGH			    0x88C


/****************************************/
/*           IDMA Registers             */
/****************************************/

#घोषणा MV64340_DMA_CHANNEL0_BYTE_COUNT                             0x800
#घोषणा MV64340_DMA_CHANNEL1_BYTE_COUNT                             0x804
#घोषणा MV64340_DMA_CHANNEL2_BYTE_COUNT                             0x808
#घोषणा MV64340_DMA_CHANNEL3_BYTE_COUNT                             0x80C
#घोषणा MV64340_DMA_CHANNEL0_SOURCE_ADDR                            0x810
#घोषणा MV64340_DMA_CHANNEL1_SOURCE_ADDR                            0x814
#घोषणा MV64340_DMA_CHANNEL2_SOURCE_ADDR                            0x818
#घोषणा MV64340_DMA_CHANNEL3_SOURCE_ADDR                            0x81c
#घोषणा MV64340_DMA_CHANNEL0_DESTINATION_ADDR                       0x820
#घोषणा MV64340_DMA_CHANNEL1_DESTINATION_ADDR                       0x824
#घोषणा MV64340_DMA_CHANNEL2_DESTINATION_ADDR                       0x828
#घोषणा MV64340_DMA_CHANNEL3_DESTINATION_ADDR                       0x82C
#घोषणा MV64340_DMA_CHANNEL0_NEXT_DESCRIPTOR_POINTER                0x830
#घोषणा MV64340_DMA_CHANNEL1_NEXT_DESCRIPTOR_POINTER                0x834
#घोषणा MV64340_DMA_CHANNEL2_NEXT_DESCRIPTOR_POINTER                0x838
#घोषणा MV64340_DMA_CHANNEL3_NEXT_DESCRIPTOR_POINTER                0x83C
#घोषणा MV64340_DMA_CHANNEL0_CURRENT_DESCRIPTOR_POINTER             0x870
#घोषणा MV64340_DMA_CHANNEL1_CURRENT_DESCRIPTOR_POINTER             0x874
#घोषणा MV64340_DMA_CHANNEL2_CURRENT_DESCRIPTOR_POINTER             0x878
#घोषणा MV64340_DMA_CHANNEL3_CURRENT_DESCRIPTOR_POINTER             0x87C

 /*  IDMA Address Decoding Base Address Registers  */
 
#घोषणा MV64340_DMA_BASE_ADDR_REG0                                  0xa00
#घोषणा MV64340_DMA_BASE_ADDR_REG1                                  0xa08
#घोषणा MV64340_DMA_BASE_ADDR_REG2                                  0xa10
#घोषणा MV64340_DMA_BASE_ADDR_REG3                                  0xa18
#घोषणा MV64340_DMA_BASE_ADDR_REG4                                  0xa20
#घोषणा MV64340_DMA_BASE_ADDR_REG5                                  0xa28
#घोषणा MV64340_DMA_BASE_ADDR_REG6                                  0xa30
#घोषणा MV64340_DMA_BASE_ADDR_REG7                                  0xa38
 
 /*  IDMA Address Decoding Size Address Register   */
 
#घोषणा MV64340_DMA_SIZE_REG0                                       0xa04
#घोषणा MV64340_DMA_SIZE_REG1                                       0xa0c
#घोषणा MV64340_DMA_SIZE_REG2                                       0xa14
#घोषणा MV64340_DMA_SIZE_REG3                                       0xa1c
#घोषणा MV64340_DMA_SIZE_REG4                                       0xa24
#घोषणा MV64340_DMA_SIZE_REG5                                       0xa2c
#घोषणा MV64340_DMA_SIZE_REG6                                       0xa34
#घोषणा MV64340_DMA_SIZE_REG7                                       0xa3C

 /* IDMA Address Decoding High Address Remap and Access 
                  Protection Registers                    */
                  
#घोषणा MV64340_DMA_HIGH_ADDR_REMAP_REG0                            0xa60
#घोषणा MV64340_DMA_HIGH_ADDR_REMAP_REG1                            0xa64
#घोषणा MV64340_DMA_HIGH_ADDR_REMAP_REG2                            0xa68
#घोषणा MV64340_DMA_HIGH_ADDR_REMAP_REG3                            0xa6C
#घोषणा MV64340_DMA_BASE_ADDR_ENABLE_REG                            0xa80
#घोषणा MV64340_DMA_CHANNEL0_ACCESS_PROTECTION_REG                  0xa70
#घोषणा MV64340_DMA_CHANNEL1_ACCESS_PROTECTION_REG                  0xa74
#घोषणा MV64340_DMA_CHANNEL2_ACCESS_PROTECTION_REG                  0xa78
#घोषणा MV64340_DMA_CHANNEL3_ACCESS_PROTECTION_REG                  0xa7c
#घोषणा MV64340_DMA_ARBITER_CONTROL                                 0x860
#घोषणा MV64340_DMA_CROSS_BAR_TIMEOUT                               0x8d0

 /*  IDMA Headers Retarget Registers   */

#घोषणा MV64340_DMA_HEADERS_RETARGET_CONTROL                        0xa84
#घोषणा MV64340_DMA_HEADERS_RETARGET_BASE                           0xa88

 /*  IDMA Interrupt Register  */

#घोषणा MV64340_DMA_INTERRUPT_CAUSE_REG                             0x8c0
#घोषणा MV64340_DMA_INTERRUPT_CAUSE_MASK                            0x8c4
#घोषणा MV64340_DMA_ERROR_ADDR                                      0x8c8
#घोषणा MV64340_DMA_ERROR_SELECT                                    0x8cc

 /*  IDMA Debug Register ( क्रम पूर्णांकernal use )    */

#घोषणा MV64340_DMA_DEBUG_LOW                                       0x8e0
#घोषणा MV64340_DMA_DEBUG_HIGH                                      0x8e4
#घोषणा MV64340_DMA_SPARE                                           0xA8C

/****************************************/
/* Timer_Counter 			*/
/****************************************/

#घोषणा MV64340_TIMER_COUNTER0					    0x850
#घोषणा MV64340_TIMER_COUNTER1					    0x854
#घोषणा MV64340_TIMER_COUNTER2					    0x858
#घोषणा MV64340_TIMER_COUNTER3					    0x85C
#घोषणा MV64340_TIMER_COUNTER_0_3_CONTROL			    0x864
#घोषणा MV64340_TIMER_COUNTER_0_3_INTERRUPT_CAUSE		    0x868
#घोषणा MV64340_TIMER_COUNTER_0_3_INTERRUPT_MASK      		    0x86c

/****************************************/
/*         Watchकरोg रेजिस्टरs  	        */
/****************************************/

#घोषणा MV64340_WATCHDOG_CONFIG_REG                                 0xb410
#घोषणा MV64340_WATCHDOG_VALUE_REG                                  0xb414

/****************************************/
/* I2C Registers                        */
/****************************************/

#घोषणा MV64XXX_I2C_OFFSET                                          0xc000
#घोषणा MV64XXX_I2C_REG_BLOCK_SIZE                                  0x0020

/****************************************/
/* GPP Interface Registers              */
/****************************************/

#घोषणा MV64340_GPP_IO_CONTROL                                      0xf100
#घोषणा MV64340_GPP_LEVEL_CONTROL                                   0xf110
#घोषणा MV64340_GPP_VALUE                                           0xf104
#घोषणा MV64340_GPP_INTERRUPT_CAUSE                                 0xf108
#घोषणा MV64340_GPP_INTERRUPT_MASK0                                 0xf10c
#घोषणा MV64340_GPP_INTERRUPT_MASK1                                 0xf114
#घोषणा MV64340_GPP_VALUE_SET                                       0xf118
#घोषणा MV64340_GPP_VALUE_CLEAR                                     0xf11c

/****************************************/
/* Interrupt Controller Registers       */
/****************************************/

/****************************************/
/* Interrupts	  			*/
/****************************************/

#घोषणा MV64340_MAIN_INTERRUPT_CAUSE_LOW                            0x004
#घोषणा MV64340_MAIN_INTERRUPT_CAUSE_HIGH                           0x00c
#घोषणा MV64340_CPU_INTERRUPT0_MASK_LOW                             0x014
#घोषणा MV64340_CPU_INTERRUPT0_MASK_HIGH                            0x01c
#घोषणा MV64340_CPU_INTERRUPT0_SELECT_CAUSE                         0x024
#घोषणा MV64340_CPU_INTERRUPT1_MASK_LOW                             0x034
#घोषणा MV64340_CPU_INTERRUPT1_MASK_HIGH                            0x03c
#घोषणा MV64340_CPU_INTERRUPT1_SELECT_CAUSE                         0x044
#घोषणा MV64340_INTERRUPT0_MASK_0_LOW                               0x054
#घोषणा MV64340_INTERRUPT0_MASK_0_HIGH                              0x05c
#घोषणा MV64340_INTERRUPT0_SELECT_CAUSE                             0x064
#घोषणा MV64340_INTERRUPT1_MASK_0_LOW                               0x074
#घोषणा MV64340_INTERRUPT1_MASK_0_HIGH                              0x07c
#घोषणा MV64340_INTERRUPT1_SELECT_CAUSE                             0x084

/****************************************/
/*      MPP Interface Registers         */
/****************************************/

#घोषणा MV64340_MPP_CONTROL0                                        0xf000
#घोषणा MV64340_MPP_CONTROL1                                        0xf004
#घोषणा MV64340_MPP_CONTROL2                                        0xf008
#घोषणा MV64340_MPP_CONTROL3                                        0xf00c

/****************************************/
/*    Serial Initialization रेजिस्टरs   */
/****************************************/

#घोषणा MV64340_SERIAL_INIT_LAST_DATA                               0xf324
#घोषणा MV64340_SERIAL_INIT_CONTROL                                 0xf328
#घोषणा MV64340_SERIAL_INIT_STATUS                                  0xf32c

बाह्य व्योम mv64340_irq_init(अचिन्हित पूर्णांक base);

/* Watchकरोg Platक्रमm Device, Driver Data */
#घोषणा	MV64x60_WDT_NAME			"mv64x60_wdt"

काष्ठा mv64x60_wdt_pdata अणु
	पूर्णांक	समयout;	/* watchकरोg expiry in seconds, शेष 10 */
	पूर्णांक	bus_clk;	/* bus घड़ी in MHz, शेष 133 */
पूर्ण;

#पूर्ण_अगर /* __ASM_MV643XX_H */
