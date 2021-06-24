<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * NetChip 2280 high/full speed USB device controller.
 * Unlike many such controllers, this one talks PCI.
 *
 * Copyright (C) 2002 NetChip Technology, Inc. (http://www.netchip.com)
 * Copyright (C) 2003 David Brownell
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#अगर_अघोषित __LINUX_USB_NET2280_H
#घोषणा __LINUX_USB_NET2280_H

/*-------------------------------------------------------------------------*/

/* NET2280 MEMORY MAPPED REGISTERS
 *
 * The रेजिस्टर layout came from the chip करोcumentation, and the bit
 * number definitions were extracted from chip specअगरication.
 *
 * Use the shअगरt चालक ('<<') to build bit masks, with पढ़ोl/ग_लिखोl
 * to access the रेजिस्टरs through PCI.
 */

/* मुख्य रेजिस्टरs, BAR0 + 0x0000 */
काष्ठा net2280_regs अणु
	/* offset 0x0000 */
	u32		devinit;
#घोषणा     LOCAL_CLOCK_FREQUENCY                               8
#घोषणा     FORCE_PCI_RESET                                     7
#घोषणा     PCI_ID                                              6
#घोषणा     PCI_ENABLE                                          5
#घोषणा     FIFO_SOFT_RESET                                     4
#घोषणा     CFG_SOFT_RESET                                      3
#घोषणा     PCI_SOFT_RESET                                      2
#घोषणा     USB_SOFT_RESET                                      1
#घोषणा     M8051_RESET                                         0
	u32		eectl;
#घोषणा     EEPROM_ADDRESS_WIDTH                                23
#घोषणा     EEPROM_CHIP_SELECT_ACTIVE                           22
#घोषणा     EEPROM_PRESENT                                      21
#घोषणा     EEPROM_VALID                                        20
#घोषणा     EEPROM_BUSY                                         19
#घोषणा     EEPROM_CHIP_SELECT_ENABLE                           18
#घोषणा     EEPROM_BYTE_READ_START                              17
#घोषणा     EEPROM_BYTE_WRITE_START                             16
#घोषणा     EEPROM_READ_DATA                                    8
#घोषणा     EEPROM_WRITE_DATA                                   0
	u32		eeclkfreq;
	u32		_unused0;
	/* offset 0x0010 */

	u32		pciirqenb0;		/* पूर्णांकerrupt PCI master ... */
#घोषणा     SETUP_PACKET_INTERRUPT_ENABLE                       7
#घोषणा     ENDPOINT_F_INTERRUPT_ENABLE                         6
#घोषणा     ENDPOINT_E_INTERRUPT_ENABLE                         5
#घोषणा     ENDPOINT_D_INTERRUPT_ENABLE                         4
#घोषणा     ENDPOINT_C_INTERRUPT_ENABLE                         3
#घोषणा     ENDPOINT_B_INTERRUPT_ENABLE                         2
#घोषणा     ENDPOINT_A_INTERRUPT_ENABLE                         1
#घोषणा     ENDPOINT_0_INTERRUPT_ENABLE                         0
	u32		pciirqenb1;
#घोषणा     PCI_INTERRUPT_ENABLE                                31
#घोषणा     POWER_STATE_CHANGE_INTERRUPT_ENABLE                 27
#घोषणा     PCI_ARBITER_TIMEOUT_INTERRUPT_ENABLE                26
#घोषणा     PCI_PARITY_ERROR_INTERRUPT_ENABLE                   25
#घोषणा     PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE          20
#घोषणा     PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE          19
#घोषणा     PCI_TARGET_ABORT_ASSERTED_INTERRUPT_ENABLE          18
#घोषणा     PCI_RETRY_ABORT_INTERRUPT_ENABLE                    17
#घोषणा     PCI_MASTER_CYCLE_DONE_INTERRUPT_ENABLE              16
#घोषणा     GPIO_INTERRUPT_ENABLE                               13
#घोषणा     DMA_D_INTERRUPT_ENABLE                              12
#घोषणा     DMA_C_INTERRUPT_ENABLE                              11
#घोषणा     DMA_B_INTERRUPT_ENABLE                              10
#घोषणा     DMA_A_INTERRUPT_ENABLE                              9
#घोषणा     EEPROM_DONE_INTERRUPT_ENABLE                        8
#घोषणा     VBUS_INTERRUPT_ENABLE                               7
#घोषणा     CONTROL_STATUS_INTERRUPT_ENABLE                     6
#घोषणा     ROOT_PORT_RESET_INTERRUPT_ENABLE                    4
#घोषणा     SUSPEND_REQUEST_INTERRUPT_ENABLE                    3
#घोषणा     SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE             2
#घोषणा     RESUME_INTERRUPT_ENABLE                             1
#घोषणा     SOF_INTERRUPT_ENABLE                                0
	u32		cpu_irqenb0;		/* ... or onboard 8051 */
#घोषणा     SETUP_PACKET_INTERRUPT_ENABLE                       7
#घोषणा     ENDPOINT_F_INTERRUPT_ENABLE                         6
#घोषणा     ENDPOINT_E_INTERRUPT_ENABLE                         5
#घोषणा     ENDPOINT_D_INTERRUPT_ENABLE                         4
#घोषणा     ENDPOINT_C_INTERRUPT_ENABLE                         3
#घोषणा     ENDPOINT_B_INTERRUPT_ENABLE                         2
#घोषणा     ENDPOINT_A_INTERRUPT_ENABLE                         1
#घोषणा     ENDPOINT_0_INTERRUPT_ENABLE                         0
	u32		cpu_irqenb1;
#घोषणा     CPU_INTERRUPT_ENABLE                                31
#घोषणा     POWER_STATE_CHANGE_INTERRUPT_ENABLE                 27
#घोषणा     PCI_ARBITER_TIMEOUT_INTERRUPT_ENABLE                26
#घोषणा     PCI_PARITY_ERROR_INTERRUPT_ENABLE                   25
#घोषणा     PCI_INTA_INTERRUPT_ENABLE                           24
#घोषणा     PCI_PME_INTERRUPT_ENABLE                            23
#घोषणा     PCI_SERR_INTERRUPT_ENABLE                           22
#घोषणा     PCI_PERR_INTERRUPT_ENABLE                           21
#घोषणा     PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE          20
#घोषणा     PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE          19
#घोषणा     PCI_RETRY_ABORT_INTERRUPT_ENABLE                    17
#घोषणा     PCI_MASTER_CYCLE_DONE_INTERRUPT_ENABLE              16
#घोषणा     GPIO_INTERRUPT_ENABLE                               13
#घोषणा     DMA_D_INTERRUPT_ENABLE                              12
#घोषणा     DMA_C_INTERRUPT_ENABLE                              11
#घोषणा     DMA_B_INTERRUPT_ENABLE                              10
#घोषणा     DMA_A_INTERRUPT_ENABLE                              9
#घोषणा     EEPROM_DONE_INTERRUPT_ENABLE                        8
#घोषणा     VBUS_INTERRUPT_ENABLE                               7
#घोषणा     CONTROL_STATUS_INTERRUPT_ENABLE                     6
#घोषणा     ROOT_PORT_RESET_INTERRUPT_ENABLE                    4
#घोषणा     SUSPEND_REQUEST_INTERRUPT_ENABLE                    3
#घोषणा     SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE             2
#घोषणा     RESUME_INTERRUPT_ENABLE                             1
#घोषणा     SOF_INTERRUPT_ENABLE                                0

	/* offset 0x0020 */
	u32		_unused1;
	u32		usbirqenb1;
#घोषणा     USB_INTERRUPT_ENABLE                                31
#घोषणा     POWER_STATE_CHANGE_INTERRUPT_ENABLE                 27
#घोषणा     PCI_ARBITER_TIMEOUT_INTERRUPT_ENABLE                26
#घोषणा     PCI_PARITY_ERROR_INTERRUPT_ENABLE                   25
#घोषणा     PCI_INTA_INTERRUPT_ENABLE                           24
#घोषणा     PCI_PME_INTERRUPT_ENABLE                            23
#घोषणा     PCI_SERR_INTERRUPT_ENABLE                           22
#घोषणा     PCI_PERR_INTERRUPT_ENABLE                           21
#घोषणा     PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE          20
#घोषणा     PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE          19
#घोषणा     PCI_RETRY_ABORT_INTERRUPT_ENABLE                    17
#घोषणा     PCI_MASTER_CYCLE_DONE_INTERRUPT_ENABLE              16
#घोषणा     GPIO_INTERRUPT_ENABLE                               13
#घोषणा     DMA_D_INTERRUPT_ENABLE                              12
#घोषणा     DMA_C_INTERRUPT_ENABLE                              11
#घोषणा     DMA_B_INTERRUPT_ENABLE                              10
#घोषणा     DMA_A_INTERRUPT_ENABLE                              9
#घोषणा     EEPROM_DONE_INTERRUPT_ENABLE                        8
#घोषणा     VBUS_INTERRUPT_ENABLE                               7
#घोषणा     CONTROL_STATUS_INTERRUPT_ENABLE                     6
#घोषणा     ROOT_PORT_RESET_INTERRUPT_ENABLE                    4
#घोषणा     SUSPEND_REQUEST_INTERRUPT_ENABLE                    3
#घोषणा     SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE             2
#घोषणा     RESUME_INTERRUPT_ENABLE                             1
#घोषणा     SOF_INTERRUPT_ENABLE                                0
	u32		irqstat0;
#घोषणा     INTA_ASSERTED                                       12
#घोषणा     SETUP_PACKET_INTERRUPT                              7
#घोषणा     ENDPOINT_F_INTERRUPT                                6
#घोषणा     ENDPOINT_E_INTERRUPT                                5
#घोषणा     ENDPOINT_D_INTERRUPT                                4
#घोषणा     ENDPOINT_C_INTERRUPT                                3
#घोषणा     ENDPOINT_B_INTERRUPT                                2
#घोषणा     ENDPOINT_A_INTERRUPT                                1
#घोषणा     ENDPOINT_0_INTERRUPT                                0
#घोषणा     USB3380_IRQSTAT0_EP_INTR_MASK_IN (0xF << 17)
#घोषणा     USB3380_IRQSTAT0_EP_INTR_MASK_OUT (0xF << 1)

	u32		irqstat1;
#घोषणा     POWER_STATE_CHANGE_INTERRUPT                        27
#घोषणा     PCI_ARBITER_TIMEOUT_INTERRUPT                       26
#घोषणा     PCI_PARITY_ERROR_INTERRUPT                          25
#घोषणा     PCI_INTA_INTERRUPT                                  24
#घोषणा     PCI_PME_INTERRUPT                                   23
#घोषणा     PCI_SERR_INTERRUPT                                  22
#घोषणा     PCI_PERR_INTERRUPT                                  21
#घोषणा     PCI_MASTER_ABORT_RECEIVED_INTERRUPT                 20
#घोषणा     PCI_TARGET_ABORT_RECEIVED_INTERRUPT                 19
#घोषणा     PCI_RETRY_ABORT_INTERRUPT                           17
#घोषणा     PCI_MASTER_CYCLE_DONE_INTERRUPT                     16
#घोषणा     SOF_DOWN_INTERRUPT                                  14
#घोषणा     GPIO_INTERRUPT                                      13
#घोषणा     DMA_D_INTERRUPT                                     12
#घोषणा     DMA_C_INTERRUPT                                     11
#घोषणा     DMA_B_INTERRUPT                                     10
#घोषणा     DMA_A_INTERRUPT                                     9
#घोषणा     EEPROM_DONE_INTERRUPT                               8
#घोषणा     VBUS_INTERRUPT                                      7
#घोषणा     CONTROL_STATUS_INTERRUPT                            6
#घोषणा     ROOT_PORT_RESET_INTERRUPT                           4
#घोषणा     SUSPEND_REQUEST_INTERRUPT                           3
#घोषणा     SUSPEND_REQUEST_CHANGE_INTERRUPT                    2
#घोषणा     RESUME_INTERRUPT                                    1
#घोषणा     SOF_INTERRUPT                                       0
	/* offset 0x0030 */
	u32		idxaddr;
	u32		idxdata;
	u32		fअगरoctl;
#घोषणा     PCI_BASE2_RANGE                                     16
#घोषणा     IGNORE_FIFO_AVAILABILITY                            3
#घोषणा     PCI_BASE2_SELECT                                    2
#घोषणा     FIFO_CONFIGURATION_SELECT                           0
	u32		_unused2;
	/* offset 0x0040 */
	u32		memaddr;
#घोषणा     START                                               28
#घोषणा     सूचीECTION                                           27
#घोषणा     FIFO_DIAGNOSTIC_SELECT                              24
#घोषणा     MEMORY_ADDRESS                                      0
	u32		memdata0;
	u32		memdata1;
	u32		_unused3;
	/* offset 0x0050 */
	u32		gpioctl;
#घोषणा     GPIO3_LED_SELECT                                    12
#घोषणा     GPIO3_INTERRUPT_ENABLE                              11
#घोषणा     GPIO2_INTERRUPT_ENABLE                              10
#घोषणा     GPIO1_INTERRUPT_ENABLE                              9
#घोषणा     GPIO0_INTERRUPT_ENABLE                              8
#घोषणा     GPIO3_OUTPUT_ENABLE                                 7
#घोषणा     GPIO2_OUTPUT_ENABLE                                 6
#घोषणा     GPIO1_OUTPUT_ENABLE                                 5
#घोषणा     GPIO0_OUTPUT_ENABLE                                 4
#घोषणा     GPIO3_DATA                                          3
#घोषणा     GPIO2_DATA                                          2
#घोषणा     GPIO1_DATA                                          1
#घोषणा     GPIO0_DATA                                          0
	u32		gpiostat;
#घोषणा     GPIO3_INTERRUPT                                     3
#घोषणा     GPIO2_INTERRUPT                                     2
#घोषणा     GPIO1_INTERRUPT                                     1
#घोषणा     GPIO0_INTERRUPT                                     0
पूर्ण __attribute__ ((packed));

/* usb control, BAR0 + 0x0080 */
काष्ठा net2280_usb_regs अणु
	/* offset 0x0080 */
	u32		stdrsp;
#घोषणा     STALL_UNSUPPORTED_REQUESTS                          31
#घोषणा     SET_TEST_MODE                                       16
#घोषणा     GET_OTHER_SPEED_CONFIGURATION                       15
#घोषणा     GET_DEVICE_QUALIFIER                                14
#घोषणा     SET_ADDRESS                                         13
#घोषणा     ENDPOINT_SET_CLEAR_HALT                             12
#घोषणा     DEVICE_SET_CLEAR_DEVICE_REMOTE_WAKEUP               11
#घोषणा     GET_STRING_DESCRIPTOR_2                             10
#घोषणा     GET_STRING_DESCRIPTOR_1                             9
#घोषणा     GET_STRING_DESCRIPTOR_0                             8
#घोषणा     GET_SET_INTERFACE                                   6
#घोषणा     GET_SET_CONFIGURATION                               5
#घोषणा     GET_CONFIGURATION_DESCRIPTOR                        4
#घोषणा     GET_DEVICE_DESCRIPTOR                               3
#घोषणा     GET_ENDPOINT_STATUS                                 2
#घोषणा     GET_INTERFACE_STATUS                                1
#घोषणा     GET_DEVICE_STATUS                                   0
	u32		prodvendid;
#घोषणा     PRODUCT_ID                                          16
#घोषणा     VENDOR_ID                                           0
	u32		relnum;
	u32		usbctl;
#घोषणा     SERIAL_NUMBER_INDEX                                 16
#घोषणा     PRODUCT_ID_STRING_ENABLE                            13
#घोषणा     VENDOR_ID_STRING_ENABLE                             12
#घोषणा     USB_ROOT_PORT_WAKEUP_ENABLE                         11
#घोषणा     VBUS_PIN                                            10
#घोषणा     TIMED_DISCONNECT                                    9
#घोषणा     SUSPEND_IMMEDIATELY                                 7
#घोषणा     SELF_POWERED_USB_DEVICE                             6
#घोषणा     REMOTE_WAKEUP_SUPPORT                               5
#घोषणा     PME_POLARITY                                        4
#घोषणा     USB_DETECT_ENABLE                                   3
#घोषणा     PME_WAKEUP_ENABLE                                   2
#घोषणा     DEVICE_REMOTE_WAKEUP_ENABLE                         1
#घोषणा     SELF_POWERED_STATUS                                 0
	/* offset 0x0090 */
	u32		usbstat;
#घोषणा     HIGH_SPEED                                          7
#घोषणा     FULL_SPEED                                          6
#घोषणा     GENERATE_RESUME                                     5
#घोषणा     GENERATE_DEVICE_REMOTE_WAKEUP                       4
	u32		xcvrdiag;
#घोषणा     FORCE_HIGH_SPEED_MODE                               31
#घोषणा     FORCE_FULL_SPEED_MODE                               30
#घोषणा     USB_TEST_MODE                                       24
#घोषणा     LINE_STATE                                          16
#घोषणा     TRANSCEIVER_OPERATION_MODE                          2
#घोषणा     TRANSCEIVER_SELECT                                  1
#घोषणा     TERMINATION_SELECT                                  0
	u32		setup0123;
	u32		setup4567;
	/* offset 0x0090 */
	u32		_unused0;
	u32		ouraddr;
#घोषणा     FORCE_IMMEDIATE                                     7
#घोषणा     OUR_USB_ADDRESS                                     0
	u32		ourconfig;
पूर्ण __attribute__ ((packed));

/* pci control, BAR0 + 0x0100 */
काष्ठा net2280_pci_regs अणु
	/* offset 0x0100 */
	u32		 pcimstctl;
#घोषणा     PCI_ARBITER_PARK_SELECT                             13
#घोषणा     PCI_MULTI LEVEL_ARBITER                             12
#घोषणा     PCI_RETRY_ABORT_ENABLE                              11
#घोषणा     DMA_MEMORY_WRITE_AND_INVALIDATE_ENABLE              10
#घोषणा     DMA_READ_MULTIPLE_ENABLE                            9
#घोषणा     DMA_READ_LINE_ENABLE                                8
#घोषणा     PCI_MASTER_COMMAND_SELECT                           6
#घोषणा         MEM_READ_OR_WRITE                                   0
#घोषणा         IO_READ_OR_WRITE                                    1
#घोषणा         CFG_READ_OR_WRITE                                   2
#घोषणा     PCI_MASTER_START                                    5
#घोषणा     PCI_MASTER_READ_WRITE                               4
#घोषणा         PCI_MASTER_WRITE                                    0
#घोषणा         PCI_MASTER_READ                                     1
#घोषणा     PCI_MASTER_BYTE_WRITE_ENABLES                       0
	u32		 pcimstaddr;
	u32		 pcimstdata;
	u32		 pcimststat;
#घोषणा     PCI_ARBITER_CLEAR                                   2
#घोषणा     PCI_EXTERNAL_ARBITER                                1
#घोषणा     PCI_HOST_MODE                                       0
पूर्ण __attribute__ ((packed));

/* dma control, BAR0 + 0x0180 ... array of four काष्ठाs like this,
 * क्रम channels 0..3.  see also काष्ठा net2280_dma:  descriptor
 * that can be loaded पूर्णांकo some of these रेजिस्टरs.
 */
काष्ठा net2280_dma_regs अणु	/* [11.7] */
	/* offset 0x0180, 0x01a0, 0x01c0, 0x01e0, */
	u32		dmactl;
#घोषणा     DMA_SCATTER_GATHER_DONE_INTERRUPT_ENABLE            25
#घोषणा     DMA_CLEAR_COUNT_ENABLE                              21
#घोषणा     DESCRIPTOR_POLLING_RATE                             19
#घोषणा         POLL_CONTINUOUS                                     0
#घोषणा         POLL_1_USEC                                         1
#घोषणा         POLL_100_USEC                                       2
#घोषणा         POLL_1_MSEC                                         3
#घोषणा     DMA_VALID_BIT_POLLING_ENABLE                        18
#घोषणा     DMA_VALID_BIT_ENABLE                                17
#घोषणा     DMA_SCATTER_GATHER_ENABLE                           16
#घोषणा     DMA_OUT_AUTO_START_ENABLE                           4
#घोषणा     DMA_PREEMPT_ENABLE                                  3
#घोषणा     DMA_FIFO_VALIDATE                                   2
#घोषणा     DMA_ENABLE                                          1
#घोषणा     DMA_ADDRESS_HOLD                                    0
	u32		dmastat;
#घोषणा     DMA_ABORT_DONE_INTERRUPT                            27
#घोषणा     DMA_SCATTER_GATHER_DONE_INTERRUPT                   25
#घोषणा     DMA_TRANSACTION_DONE_INTERRUPT                      24
#घोषणा     DMA_ABORT                                           1
#घोषणा     DMA_START                                           0
	u32		_unused0[2];
	/* offset 0x0190, 0x01b0, 0x01d0, 0x01f0, */
	u32		dmacount;
#घोषणा     VALID_BIT                                           31
#घोषणा     DMA_सूचीECTION                                       30
#घोषणा     DMA_DONE_INTERRUPT_ENABLE                           29
#घोषणा     END_OF_CHAIN                                        28
#घोषणा         DMA_BYTE_COUNT_MASK                                 ((1<<24)-1)
#घोषणा     DMA_BYTE_COUNT                                      0
	u32		dmaaddr;
	u32		dmadesc;
	u32		_unused1;
पूर्ण __attribute__ ((packed));

/* dedicated endpoपूर्णांक रेजिस्टरs, BAR0 + 0x0200 */

काष्ठा net2280_dep_regs अणु	/* [11.8] */
	/* offset 0x0200, 0x0210, 0x220, 0x230, 0x240 */
	u32		dep_cfg;
	/* offset 0x0204, 0x0214, 0x224, 0x234, 0x244 */
	u32		dep_rsp;
	u32		_unused[2];
पूर्ण __attribute__ ((packed));

/* configurable endpoपूर्णांक रेजिस्टरs, BAR0 + 0x0300 ... array of seven काष्ठाs
 * like this, क्रम ep0 then the configurable endpoपूर्णांकs A..F
 * ep0 reserved क्रम control; E and F have only 64 bytes of fअगरo
 */
काष्ठा net2280_ep_regs अणु	/* [11.9] */
	/* offset 0x0300, 0x0320, 0x0340, 0x0360, 0x0380, 0x03a0, 0x03c0 */
	u32		ep_cfg;
#घोषणा     ENDPOINT_BYTE_COUNT                                 16
#घोषणा     ENDPOINT_ENABLE                                     10
#घोषणा     ENDPOINT_TYPE                                       8
#घोषणा     ENDPOINT_सूचीECTION                                  7
#घोषणा     ENDPOINT_NUMBER                                     0
	u32		ep_rsp;
#घोषणा     SET_NAK_OUT_PACKETS                                 15
#घोषणा     SET_EP_HIDE_STATUS_PHASE                            14
#घोषणा     SET_EP_FORCE_CRC_ERROR                              13
#घोषणा     SET_INTERRUPT_MODE                                  12
#घोषणा     SET_CONTROL_STATUS_PHASE_HANDSHAKE                  11
#घोषणा     SET_NAK_OUT_PACKETS_MODE                            10
#घोषणा     SET_ENDPOINT_TOGGLE                                 9
#घोषणा     SET_ENDPOINT_HALT                                   8
#घोषणा     CLEAR_NAK_OUT_PACKETS                               7
#घोषणा     CLEAR_EP_HIDE_STATUS_PHASE                          6
#घोषणा     CLEAR_EP_FORCE_CRC_ERROR                            5
#घोषणा     CLEAR_INTERRUPT_MODE                                4
#घोषणा     CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE                3
#घोषणा     CLEAR_NAK_OUT_PACKETS_MODE                          2
#घोषणा     CLEAR_ENDPOINT_TOGGLE                               1
#घोषणा     CLEAR_ENDPOINT_HALT                                 0
	u32		ep_irqenb;
#घोषणा     SHORT_PACKET_OUT_DONE_INTERRUPT_ENABLE              6
#घोषणा     SHORT_PACKET_TRANSFERRED_INTERRUPT_ENABLE           5
#घोषणा     DATA_PACKET_RECEIVED_INTERRUPT_ENABLE               3
#घोषणा     DATA_PACKET_TRANSMITTED_INTERRUPT_ENABLE            2
#घोषणा     DATA_OUT_PING_TOKEN_INTERRUPT_ENABLE                1
#घोषणा     DATA_IN_TOKEN_INTERRUPT_ENABLE                      0
	u32		ep_stat;
#घोषणा     FIFO_VALID_COUNT                                    24
#घोषणा     HIGH_BANDWIDTH_OUT_TRANSACTION_PID                  22
#घोषणा     TIMEOUT                                             21
#घोषणा     USB_STALL_SENT                                      20
#घोषणा     USB_IN_NAK_SENT                                     19
#घोषणा     USB_IN_ACK_RCVD                                     18
#घोषणा     USB_OUT_PING_NAK_SENT                               17
#घोषणा     USB_OUT_ACK_SENT                                    16
#घोषणा     FIFO_OVERFLOW                                       13
#घोषणा     FIFO_UNDERFLOW                                      12
#घोषणा     FIFO_FULL                                           11
#घोषणा     FIFO_EMPTY                                          10
#घोषणा     FIFO_FLUSH                                          9
#घोषणा     SHORT_PACKET_OUT_DONE_INTERRUPT                     6
#घोषणा     SHORT_PACKET_TRANSFERRED_INTERRUPT                  5
#घोषणा     NAK_OUT_PACKETS                                     4
#घोषणा     DATA_PACKET_RECEIVED_INTERRUPT                      3
#घोषणा     DATA_PACKET_TRANSMITTED_INTERRUPT                   2
#घोषणा     DATA_OUT_PING_TOKEN_INTERRUPT                       1
#घोषणा     DATA_IN_TOKEN_INTERRUPT                             0
	/* offset 0x0310, 0x0330, 0x0350, 0x0370, 0x0390, 0x03b0, 0x03d0 */
	u32		ep_avail;
	u32		ep_data;
	u32		_unused0[2];
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर /* __LINUX_USB_NET2280_H */
