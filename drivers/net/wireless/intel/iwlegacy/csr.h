<शैली गुरु>
/******************************************************************************
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2005 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA 02110,
 * USA
 *
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 * BSD LICENSE
 *
 * Copyright(c) 2005 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/
#अगर_अघोषित __il_csr_h__
#घोषणा __il_csr_h__
/*
 * CSR (control and status रेजिस्टरs)
 *
 * CSR रेजिस्टरs are mapped directly पूर्णांकo PCI bus space, and are accessible
 * whenever platक्रमm supplies घातer to device, even when device is in
 * low घातer states due to driver-invoked device resets
 * (e.g. CSR_RESET_REG_FLAG_SW_RESET) or uCode-driven घातer-saving modes.
 *
 * Use _il_wr() and _il_rd() family to access these रेजिस्टरs;
 * these provide simple PCI bus access, without waking up the MAC.
 * Do not use il_wr() family क्रम these रेजिस्टरs;
 * no need to "grab nic access" via CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ.
 * The MAC (uCode processor, etc.) करोes not need to be घातered up क्रम accessing
 * the CSR रेजिस्टरs.
 *
 * NOTE:  Device करोes need to be awake in order to पढ़ो this memory
 *        via CSR_EEPROM रेजिस्टर
 */
#घोषणा CSR_BASE    (0x000)

#घोषणा CSR_HW_IF_CONFIG_REG    (CSR_BASE+0x000)	/* hardware पूर्णांकerface config */
#घोषणा CSR_INT_COALESCING      (CSR_BASE+0x004)	/* accum पूर्णांकs, 32-usec units */
#घोषणा CSR_INT                 (CSR_BASE+0x008)	/* host पूर्णांकerrupt status/ack */
#घोषणा CSR_INT_MASK            (CSR_BASE+0x00c)	/* host पूर्णांकerrupt enable */
#घोषणा CSR_FH_INT_STATUS       (CSR_BASE+0x010)	/* busmaster पूर्णांक status/ack */
#घोषणा CSR_GPIO_IN             (CSR_BASE+0x018)	/* पढ़ो बाह्यal chip pins */
#घोषणा CSR_RESET               (CSR_BASE+0x020)	/* busmaster enable, NMI, etc */
#घोषणा CSR_GP_CNTRL            (CSR_BASE+0x024)

/* 2nd byte of CSR_INT_COALESCING, not accessible via _il_wr()! */
#घोषणा CSR_INT_PERIODIC_REG	(CSR_BASE+0x005)

/*
 * Hardware revision info
 * Bit fields:
 * 31-8:  Reserved
 *  7-4:  Type of device:  see CSR_HW_REV_TYPE_xxx definitions
 *  3-2:  Revision step:  0 = A, 1 = B, 2 = C, 3 = D
 *  1-0:  "Dash" (-) value, as in A-1, etc.
 *
 * NOTE:  Revision step affects calculation of CCK txघातer क्रम 4965.
 * NOTE:  See also CSR_HW_REV_WA_REG (work-around क्रम bug in 4965).
 */
#घोषणा CSR_HW_REV              (CSR_BASE+0x028)

/*
 * EEPROM memory पढ़ोs
 *
 * NOTE:  Device must be awake, initialized via apm_ops.init(),
 *        in order to पढ़ो.
 */
#घोषणा CSR_EEPROM_REG          (CSR_BASE+0x02c)
#घोषणा CSR_EEPROM_GP           (CSR_BASE+0x030)

#घोषणा CSR_GIO_REG		(CSR_BASE+0x03C)
#घोषणा CSR_GP_UCODE_REG	(CSR_BASE+0x048)
#घोषणा CSR_GP_DRIVER_REG	(CSR_BASE+0x050)

/*
 * UCODE-DRIVER GP (general purpose) mailbox रेजिस्टरs.
 * SET/CLR रेजिस्टरs set/clear bit(s) अगर "1" is written.
 */
#घोषणा CSR_UCODE_DRV_GP1       (CSR_BASE+0x054)
#घोषणा CSR_UCODE_DRV_GP1_SET   (CSR_BASE+0x058)
#घोषणा CSR_UCODE_DRV_GP1_CLR   (CSR_BASE+0x05c)
#घोषणा CSR_UCODE_DRV_GP2       (CSR_BASE+0x060)

#घोषणा CSR_LED_REG             (CSR_BASE+0x094)
#घोषणा CSR_DRAM_INT_TBL_REG	(CSR_BASE+0x0A0)

/* GIO Chicken Bits (PCI Express bus link घातer management) */
#घोषणा CSR_GIO_CHICKEN_BITS    (CSR_BASE+0x100)

/* Analog phase-lock-loop configuration  */
#घोषणा CSR_ANA_PLL_CFG         (CSR_BASE+0x20c)

/*
 * CSR Hardware Revision Workaround Register.  Indicates hardware rev;
 * "step" determines CCK backoff क्रम txघातer calculation.  Used क्रम 4965 only.
 * See also CSR_HW_REV रेजिस्टर.
 * Bit fields:
 *  3-2:  0 = A, 1 = B, 2 = C, 3 = D step
 *  1-0:  "Dash" (-) value, as in C-1, etc.
 */
#घोषणा CSR_HW_REV_WA_REG		(CSR_BASE+0x22C)

#घोषणा CSR_DBG_HPET_MEM_REG		(CSR_BASE+0x240)
#घोषणा CSR_DBG_LINK_PWR_MGMT_REG	(CSR_BASE+0x250)

/* Bits क्रम CSR_HW_IF_CONFIG_REG */
#घोषणा CSR49_HW_IF_CONFIG_REG_BIT_4965_R	(0x00000010)
#घोषणा CSR_HW_IF_CONFIG_REG_MSK_BOARD_VER	(0x00000C00)
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_MAC_SI 	(0x00000100)
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI	(0x00000200)

#घोषणा CSR39_HW_IF_CONFIG_REG_BIT_3945_MB         (0x00000100)
#घोषणा CSR39_HW_IF_CONFIG_REG_BIT_3945_MM         (0x00000200)
#घोषणा CSR39_HW_IF_CONFIG_REG_BIT_SKU_MRC            (0x00000400)
#घोषणा CSR39_HW_IF_CONFIG_REG_BIT_BOARD_TYPE         (0x00000800)
#घोषणा CSR39_HW_IF_CONFIG_REG_BITS_SILICON_TYPE_A    (0x00000000)
#घोषणा CSR39_HW_IF_CONFIG_REG_BITS_SILICON_TYPE_B    (0x00001000)

#घोषणा CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A	(0x00080000)
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM	(0x00200000)
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_NIC_READY	(0x00400000)	/* PCI_OWN_SEM */
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_NIC_PREPARE_DONE (0x02000000)	/* ME_OWN */
#घोषणा CSR_HW_IF_CONFIG_REG_PREPARE		  (0x08000000)	/* WAKE_ME */

#घोषणा CSR_INT_PERIODIC_DIS			(0x00)	/* disable periodic पूर्णांक */
#घोषणा CSR_INT_PERIODIC_ENA			(0xFF)	/* 255*32 usec ~ 8 msec */

/* पूर्णांकerrupt flags in INTA, set by uCode or hardware (e.g. dma),
 * acknowledged (reset) by host writing "1" to flagged bits. */
#घोषणा CSR_INT_BIT_FH_RX        (1 << 31)	/* Rx DMA, cmd responses, FH_INT[17:16] */
#घोषणा CSR_INT_BIT_HW_ERR       (1 << 29)	/* DMA hardware error FH_INT[31] */
#घोषणा CSR_INT_BIT_RX_PERIODIC	 (1 << 28)	/* Rx periodic */
#घोषणा CSR_INT_BIT_FH_TX        (1 << 27)	/* Tx DMA FH_INT[1:0] */
#घोषणा CSR_INT_BIT_SCD          (1 << 26)	/* TXQ poपूर्णांकer advanced */
#घोषणा CSR_INT_BIT_SW_ERR       (1 << 25)	/* uCode error */
#घोषणा CSR_INT_BIT_RF_KILL      (1 << 7)	/* HW RFKILL चयन GP_CNTRL[27] toggled */
#घोषणा CSR_INT_BIT_CT_KILL      (1 << 6)	/* Critical temp (chip too hot) rfसमाप्त */
#घोषणा CSR_INT_BIT_SW_RX        (1 << 3)	/* Rx, command responses, 3945 */
#घोषणा CSR_INT_BIT_WAKEUP       (1 << 1)	/* NIC controller waking up (pwr mgmt) */
#घोषणा CSR_INT_BIT_ALIVE        (1 << 0)	/* uCode पूर्णांकerrupts once it initializes */

#घोषणा CSR_INI_SET_MASK	(CSR_INT_BIT_FH_RX   | \
				 CSR_INT_BIT_HW_ERR  | \
				 CSR_INT_BIT_FH_TX   | \
				 CSR_INT_BIT_SW_ERR  | \
				 CSR_INT_BIT_RF_KILL | \
				 CSR_INT_BIT_SW_RX   | \
				 CSR_INT_BIT_WAKEUP  | \
				 CSR_INT_BIT_ALIVE)

/* पूर्णांकerrupt flags in FH (flow handler) (PCI busmaster DMA) */
#घोषणा CSR_FH_INT_BIT_ERR       (1 << 31)	/* Error */
#घोषणा CSR_FH_INT_BIT_HI_PRIOR  (1 << 30)	/* High priority Rx, bypass coalescing */
#घोषणा CSR39_FH_INT_BIT_RX_CHNL2  (1 << 18)	/* Rx channel 2 (3945 only) */
#घोषणा CSR_FH_INT_BIT_RX_CHNL1  (1 << 17)	/* Rx channel 1 */
#घोषणा CSR_FH_INT_BIT_RX_CHNL0  (1 << 16)	/* Rx channel 0 */
#घोषणा CSR39_FH_INT_BIT_TX_CHNL6  (1 << 6)	/* Tx channel 6 (3945 only) */
#घोषणा CSR_FH_INT_BIT_TX_CHNL1  (1 << 1)	/* Tx channel 1 */
#घोषणा CSR_FH_INT_BIT_TX_CHNL0  (1 << 0)	/* Tx channel 0 */

#घोषणा CSR39_FH_INT_RX_MASK	(CSR_FH_INT_BIT_HI_PRIOR | \
				 CSR39_FH_INT_BIT_RX_CHNL2 | \
				 CSR_FH_INT_BIT_RX_CHNL1 | \
				 CSR_FH_INT_BIT_RX_CHNL0)

#घोषणा CSR39_FH_INT_TX_MASK	(CSR39_FH_INT_BIT_TX_CHNL6 | \
				 CSR_FH_INT_BIT_TX_CHNL1 | \
				 CSR_FH_INT_BIT_TX_CHNL0)

#घोषणा CSR49_FH_INT_RX_MASK	(CSR_FH_INT_BIT_HI_PRIOR | \
				 CSR_FH_INT_BIT_RX_CHNL1 | \
				 CSR_FH_INT_BIT_RX_CHNL0)

#घोषणा CSR49_FH_INT_TX_MASK	(CSR_FH_INT_BIT_TX_CHNL1 | \
				 CSR_FH_INT_BIT_TX_CHNL0)

/* GPIO */
#घोषणा CSR_GPIO_IN_BIT_AUX_POWER                   (0x00000200)
#घोषणा CSR_GPIO_IN_VAL_VAUX_PWR_SRC                (0x00000000)
#घोषणा CSR_GPIO_IN_VAL_VMAIN_PWR_SRC               (0x00000200)

/* RESET */
#घोषणा CSR_RESET_REG_FLAG_NEVO_RESET                (0x00000001)
#घोषणा CSR_RESET_REG_FLAG_FORCE_NMI                 (0x00000002)
#घोषणा CSR_RESET_REG_FLAG_SW_RESET                  (0x00000080)
#घोषणा CSR_RESET_REG_FLAG_MASTER_DISABLED           (0x00000100)
#घोषणा CSR_RESET_REG_FLAG_STOP_MASTER               (0x00000200)
#घोषणा CSR_RESET_LINK_PWR_MGMT_DISABLED             (0x80000000)

/*
 * GP (general purpose) CONTROL REGISTER
 * Bit fields:
 *    27:  HW_RF_KILL_SW
 *         Indicates state of (platक्रमm's) hardware RF-Kill चयन
 * 26-24:  POWER_SAVE_TYPE
 *         Indicates current घातer-saving mode:
 *         000 -- No घातer saving
 *         001 -- MAC घातer-करोwn
 *         010 -- PHY (radio) घातer-करोwn
 *         011 -- Error
 *   9-6:  SYS_CONFIG
 *         Indicates current प्रणाली configuration, reflecting pins on chip
 *         as क्रमced high/low by device circuit board.
 *     4:  GOING_TO_SLEEP
 *         Indicates MAC is entering a घातer-saving sleep घातer-करोwn.
 *         Not a good समय to access device-पूर्णांकernal resources.
 *     3:  MAC_ACCESS_REQ
 *         Host sets this to request and मुख्यtain MAC wakeup, to allow host
 *         access to device-पूर्णांकernal resources.  Host must रुको क्रम
 *         MAC_CLOCK_READY (and !GOING_TO_SLEEP) beक्रमe accessing non-CSR
 *         device रेजिस्टरs.
 *     2:  INIT_DONE
 *         Host sets this to put device पूर्णांकo fully operational D0 घातer mode.
 *         Host resets this after SW_RESET to put device पूर्णांकo low घातer mode.
 *     0:  MAC_CLOCK_READY
 *         Indicates MAC (ucode processor, etc.) is घातered up and can run.
 *         Internal resources are accessible.
 *         NOTE:  This करोes not indicate that the processor is actually running.
 *         NOTE:  This करोes not indicate that 4965 or 3945 has completed
 *                init or post-घातer-करोwn restore of पूर्णांकernal SRAM memory.
 *                Use CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP as indication that
 *                SRAM is restored and uCode is in normal operation mode.
 *                Later devices (5xxx/6xxx/1xxx) use non-अस्थिर SRAM, and
 *                करो not need to save/restore it.
 *         NOTE:  After device reset, this bit reमुख्यs "0" until host sets
 *                INIT_DONE
 */
#घोषणा CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY        (0x00000001)
#घोषणा CSR_GP_CNTRL_REG_FLAG_INIT_DONE              (0x00000004)
#घोषणा CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ         (0x00000008)
#घोषणा CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP         (0x00000010)

#घोषणा CSR_GP_CNTRL_REG_VAL_MAC_ACCESS_EN           (0x00000001)

#घोषणा CSR_GP_CNTRL_REG_MSK_POWER_SAVE_TYPE         (0x07000000)
#घोषणा CSR_GP_CNTRL_REG_FLAG_MAC_POWER_SAVE         (0x04000000)
#घोषणा CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW          (0x08000000)

/* EEPROM REG */
#घोषणा CSR_EEPROM_REG_READ_VALID_MSK	(0x00000001)
#घोषणा CSR_EEPROM_REG_BIT_CMD		(0x00000002)
#घोषणा CSR_EEPROM_REG_MSK_ADDR		(0x0000FFFC)
#घोषणा CSR_EEPROM_REG_MSK_DATA		(0xFFFF0000)

/* EEPROM GP */
#घोषणा CSR_EEPROM_GP_VALID_MSK		(0x00000007)	/* signature */
#घोषणा CSR_EEPROM_GP_IF_OWNER_MSK	(0x00000180)
#घोषणा CSR_EEPROM_GP_GOOD_SIG_EEP_LESS_THAN_4K		(0x00000002)
#घोषणा CSR_EEPROM_GP_GOOD_SIG_EEP_MORE_THAN_4K		(0x00000004)

/* GP REG */
#घोषणा CSR_GP_REG_POWER_SAVE_STATUS_MSK            (0x03000000)	/* bit 24/25 */
#घोषणा CSR_GP_REG_NO_POWER_SAVE            (0x00000000)
#घोषणा CSR_GP_REG_MAC_POWER_SAVE           (0x01000000)
#घोषणा CSR_GP_REG_PHY_POWER_SAVE           (0x02000000)
#घोषणा CSR_GP_REG_POWER_SAVE_ERROR         (0x03000000)

/* CSR GIO */
#घोषणा CSR_GIO_REG_VAL_L0S_ENABLED	(0x00000002)

/*
 * UCODE-DRIVER GP (general purpose) mailbox रेजिस्टर 1
 * Host driver and uCode ग_लिखो and/or पढ़ो this रेजिस्टर to communicate with
 * each other.
 * Bit fields:
 *     4:  UCODE_DISABLE
 *         Host sets this to request permanent halt of uCode, same as
 *         sending CARD_STATE command with "halt" bit set.
 *     3:  CT_KILL_EXIT
 *         Host sets this to request निकास from CT_KILL state, i.e. host thinks
 *         device temperature is low enough to जारी normal operation.
 *     2:  CMD_BLOCKED
 *         Host sets this during RF KILL घातer-करोwn sequence (HW, SW, CT KILL)
 *         to release uCode to clear all Tx and command queues, enter
 *         unassociated mode, and घातer करोwn.
 *         NOTE:  Some devices also use HBUS_TARG_MBX_C रेजिस्टर क्रम this bit.
 *     1:  SW_BIT_RFKILL
 *         Host sets this when issuing CARD_STATE command to request
 *         device sleep.
 *     0:  MAC_SLEEP
 *         uCode sets this when preparing a घातer-saving घातer-करोwn.
 *         uCode resets this when घातer-up is complete and SRAM is sane.
 *         NOTE:  3945/4965 saves पूर्णांकernal SRAM data to host when घातering करोwn,
 *                and must restore this data after घातering back up.
 *                MAC_SLEEP is the best indication that restore is complete.
 *                Later devices (5xxx/6xxx/1xxx) use non-अस्थिर SRAM, and
 *                करो not need to save/restore it.
 */
#घोषणा CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP             (0x00000001)
#घोषणा CSR_UCODE_SW_BIT_RFKILL                     (0x00000002)
#घोषणा CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED           (0x00000004)
#घोषणा CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT      (0x00000008)

/* GIO Chicken Bits (PCI Express bus link घातer management) */
#घोषणा CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX  (0x00800000)
#घोषणा CSR_GIO_CHICKEN_BITS_REG_BIT_DIS_L0S_EXIT_TIMER  (0x20000000)

/* LED */
#घोषणा CSR_LED_BSM_CTRL_MSK (0xFFFFFFDF)
#घोषणा CSR_LED_REG_TRUN_ON (0x78)
#घोषणा CSR_LED_REG_TRUN_OFF (0x38)

/* ANA_PLL */
#घोषणा CSR39_ANA_PLL_CFG_VAL        (0x01000000)

/* HPET MEM debug */
#घोषणा CSR_DBG_HPET_MEM_REG_VAL	(0xFFFF0000)

/* DRAM INT TBL */
#घोषणा CSR_DRAM_INT_TBL_ENABLE		(1 << 31)
#घोषणा CSR_DRAM_INIT_TBL_WRAP_CHECK	(1 << 27)

/*
 * HBUS (Host-side Bus)
 *
 * HBUS रेजिस्टरs are mapped directly पूर्णांकo PCI bus space, but are used
 * to indirectly access device's पूर्णांकernal memory or रेजिस्टरs that
 * may be घातered-करोwn.
 *
 * Use il_wr()/il_rd() family
 * क्रम these रेजिस्टरs;
 * host must "grab nic access" via CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ
 * to make sure the MAC (uCode processor, etc.) is घातered up क्रम accessing
 * पूर्णांकernal resources.
 *
 * Do not use _il_wr()/_il_rd() family to access these रेजिस्टरs;
 * these provide only simple PCI bus access, without waking up the MAC.
 */
#घोषणा HBUS_BASE	(0x400)

/*
 * Registers क्रम accessing device's पूर्णांकernal SRAM memory (e.g. SCD SRAM
 * काष्ठाures, error log, event log, verअगरying uCode load).
 * First ग_लिखो to address रेजिस्टर, then पढ़ो from or ग_लिखो to data रेजिस्टर
 * to complete the job.  Once the address रेजिस्टर is set up, accesses to
 * data रेजिस्टरs स्वतः-increment the address by one dword.
 * Bit usage क्रम address रेजिस्टरs (पढ़ो or ग_लिखो):
 *  0-31:  memory address within device
 */
#घोषणा HBUS_TARG_MEM_RADDR     (HBUS_BASE+0x00c)
#घोषणा HBUS_TARG_MEM_WADDR     (HBUS_BASE+0x010)
#घोषणा HBUS_TARG_MEM_WDAT      (HBUS_BASE+0x018)
#घोषणा HBUS_TARG_MEM_RDAT      (HBUS_BASE+0x01c)

/* Mailbox C, used as workaround alternative to CSR_UCODE_DRV_GP1 mailbox */
#घोषणा HBUS_TARG_MBX_C         (HBUS_BASE+0x030)
#घोषणा HBUS_TARG_MBX_C_REG_BIT_CMD_BLOCKED         (0x00000004)

/*
 * Registers क्रम accessing device's पूर्णांकernal peripheral रेजिस्टरs
 * (e.g. SCD, BSM, etc.).  First ग_लिखो to address रेजिस्टर,
 * then पढ़ो from or ग_लिखो to data रेजिस्टर to complete the job.
 * Bit usage क्रम address रेजिस्टरs (पढ़ो or ग_लिखो):
 *  0-15:  रेजिस्टर address (offset) within device
 * 24-25:  (# bytes - 1) to पढ़ो or ग_लिखो (e.g. 3 क्रम dword)
 */
#घोषणा HBUS_TARG_PRPH_WADDR    (HBUS_BASE+0x044)
#घोषणा HBUS_TARG_PRPH_RADDR    (HBUS_BASE+0x048)
#घोषणा HBUS_TARG_PRPH_WDAT     (HBUS_BASE+0x04c)
#घोषणा HBUS_TARG_PRPH_RDAT     (HBUS_BASE+0x050)

/*
 * Per-Tx-queue ग_लिखो poपूर्णांकer (idx, really!)
 * Indicates idx to next TFD that driver will fill (1 past latest filled).
 * Bit usage:
 *  0-7:  queue ग_लिखो idx
 * 11-8:  queue selector
 */
#घोषणा HBUS_TARG_WRPTR         (HBUS_BASE+0x060)

#पूर्ण_अगर /* !__il_csr_h__ */
