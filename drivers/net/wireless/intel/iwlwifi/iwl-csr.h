<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2016 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_csr_h__
#घोषणा __iwl_csr_h__
/*
 * CSR (control and status रेजिस्टरs)
 *
 * CSR रेजिस्टरs are mapped directly पूर्णांकo PCI bus space, and are accessible
 * whenever platक्रमm supplies घातer to device, even when device is in
 * low घातer states due to driver-invoked device resets
 * (e.g. CSR_RESET_REG_FLAG_SW_RESET) or uCode-driven घातer-saving modes.
 *
 * Use iwl_ग_लिखो32() and iwl_पढ़ो32() family to access these रेजिस्टरs;
 * these provide simple PCI bus access, without waking up the MAC.
 * Do not use iwl_ग_लिखो_direct32() family क्रम these रेजिस्टरs;
 * no need to "grab nic access" via CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ.
 * The MAC (uCode processor, etc.) करोes not need to be घातered up क्रम accessing
 * the CSR रेजिस्टरs.
 *
 * NOTE:  Device करोes need to be awake in order to पढ़ो this memory
 *        via CSR_EEPROM and CSR_OTP रेजिस्टरs
 */
#घोषणा CSR_BASE    (0x000)

#घोषणा CSR_HW_IF_CONFIG_REG    (CSR_BASE+0x000) /* hardware पूर्णांकerface config */
#घोषणा CSR_INT_COALESCING      (CSR_BASE+0x004) /* accum पूर्णांकs, 32-usec units */
#घोषणा CSR_INT                 (CSR_BASE+0x008) /* host पूर्णांकerrupt status/ack */
#घोषणा CSR_INT_MASK            (CSR_BASE+0x00c) /* host पूर्णांकerrupt enable */
#घोषणा CSR_FH_INT_STATUS       (CSR_BASE+0x010) /* busmaster पूर्णांक status/ack*/
#घोषणा CSR_GPIO_IN             (CSR_BASE+0x018) /* पढ़ो बाह्यal chip pins */
#घोषणा CSR_RESET               (CSR_BASE+0x020) /* busmaster enable, NMI, etc*/
#घोषणा CSR_GP_CNTRL            (CSR_BASE+0x024)

/* 2nd byte of CSR_INT_COALESCING, not accessible via iwl_ग_लिखो32()! */
#घोषणा CSR_INT_PERIODIC_REG	(CSR_BASE+0x005)

/*
 * Hardware revision info
 * Bit fields:
 * 31-16:  Reserved
 *  15-4:  Type of device:  see CSR_HW_REV_TYPE_xxx definitions
 *  3-2:  Revision step:  0 = A, 1 = B, 2 = C, 3 = D
 *  1-0:  "Dash" (-) value, as in A-1, etc.
 */
#घोषणा CSR_HW_REV              (CSR_BASE+0x028)

/*
 * RF ID revision info
 * Bit fields:
 * 31:24: Reserved (set to 0x0)
 * 23:12: Type
 * 11:8:  Step (A - 0x0, B - 0x1, etc)
 * 7:4:   Dash
 * 3:0:   Flavor
 */
#घोषणा CSR_HW_RF_ID		(CSR_BASE+0x09c)

/*
 * EEPROM and OTP (one-समय-programmable) memory पढ़ोs
 *
 * NOTE:  Device must be awake, initialized via apm_ops.init(),
 *        in order to पढ़ो.
 */
#घोषणा CSR_EEPROM_REG          (CSR_BASE+0x02c)
#घोषणा CSR_EEPROM_GP           (CSR_BASE+0x030)
#घोषणा CSR_OTP_GP_REG   	(CSR_BASE+0x034)

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

#घोषणा CSR_MBOX_SET_REG	(CSR_BASE + 0x88)

#घोषणा CSR_LED_REG             (CSR_BASE+0x094)
#घोषणा CSR_DRAM_INT_TBL_REG	(CSR_BASE+0x0A0)
#घोषणा CSR_MAC_SHADOW_REG_CTRL		(CSR_BASE + 0x0A8) /* 6000 and up */
#घोषणा CSR_MAC_SHADOW_REG_CTRL_RX_WAKE	BIT(20)
#घोषणा CSR_MAC_SHADOW_REG_CTL2		(CSR_BASE + 0x0AC)
#घोषणा CSR_MAC_SHADOW_REG_CTL2_RX_WAKE	0xFFFF

/* LTR control (since IWL_DEVICE_FAMILY_22000) */
#घोषणा CSR_LTR_LONG_VAL_AD			(CSR_BASE + 0x0D4)
#घोषणा CSR_LTR_LONG_VAL_AD_NO_SNOOP_REQ	0x80000000
#घोषणा CSR_LTR_LONG_VAL_AD_NO_SNOOP_SCALE	0x1c000000
#घोषणा CSR_LTR_LONG_VAL_AD_NO_SNOOP_VAL	0x03ff0000
#घोषणा CSR_LTR_LONG_VAL_AD_SNOOP_REQ		0x00008000
#घोषणा CSR_LTR_LONG_VAL_AD_SNOOP_SCALE		0x00001c00
#घोषणा CSR_LTR_LONG_VAL_AD_SNOOP_VAL		0x000003ff
#घोषणा CSR_LTR_LONG_VAL_AD_SCALE_USEC		2

/* GIO Chicken Bits (PCI Express bus link घातer management) */
#घोषणा CSR_GIO_CHICKEN_BITS    (CSR_BASE+0x100)

/* host chicken bits */
#घोषणा CSR_HOST_CHICKEN	(CSR_BASE + 0x204)
#घोषणा CSR_HOST_CHICKEN_PM_IDLE_SRC_DIS_SB_PME	BIT(19)

/* Analog phase-lock-loop configuration  */
#घोषणा CSR_ANA_PLL_CFG         (CSR_BASE+0x20c)

/*
 * CSR HW resources monitor रेजिस्टरs
 */
#घोषणा CSR_MONITOR_CFG_REG		(CSR_BASE+0x214)
#घोषणा CSR_MONITOR_STATUS_REG		(CSR_BASE+0x228)
#घोषणा CSR_MONITOR_XTAL_RESOURCES	(0x00000010)

/*
 * CSR Hardware Revision Workaround Register.  Indicates hardware rev;
 * "step" determines CCK backoff क्रम txघातer calculation.
 * See also CSR_HW_REV रेजिस्टर.
 * Bit fields:
 *  3-2:  0 = A, 1 = B, 2 = C, 3 = D step
 *  1-0:  "Dash" (-) value, as in C-1, etc.
 */
#घोषणा CSR_HW_REV_WA_REG		(CSR_BASE+0x22C)

#घोषणा CSR_DBG_HPET_MEM_REG		(CSR_BASE+0x240)
#घोषणा CSR_DBG_LINK_PWR_MGMT_REG	(CSR_BASE+0x250)

/* Bits क्रम CSR_HW_IF_CONFIG_REG */
#घोषणा CSR_HW_IF_CONFIG_REG_MSK_MAC_DASH	(0x00000003)
#घोषणा CSR_HW_IF_CONFIG_REG_MSK_MAC_STEP	(0x0000000C)
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_MONITOR_SRAM	(0x00000080)
#घोषणा CSR_HW_IF_CONFIG_REG_MSK_BOARD_VER	(0x000000C0)
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_MAC_SI		(0x00000100)
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI	(0x00000200)
#घोषणा CSR_HW_IF_CONFIG_REG_D3_DEBUG		(0x00000200)
#घोषणा CSR_HW_IF_CONFIG_REG_MSK_PHY_TYPE	(0x00000C00)
#घोषणा CSR_HW_IF_CONFIG_REG_MSK_PHY_DASH	(0x00003000)
#घोषणा CSR_HW_IF_CONFIG_REG_MSK_PHY_STEP	(0x0000C000)

#घोषणा CSR_HW_IF_CONFIG_REG_POS_MAC_DASH	(0)
#घोषणा CSR_HW_IF_CONFIG_REG_POS_MAC_STEP	(2)
#घोषणा CSR_HW_IF_CONFIG_REG_POS_BOARD_VER	(6)
#घोषणा CSR_HW_IF_CONFIG_REG_POS_PHY_TYPE	(10)
#घोषणा CSR_HW_IF_CONFIG_REG_POS_PHY_DASH	(12)
#घोषणा CSR_HW_IF_CONFIG_REG_POS_PHY_STEP	(14)

#घोषणा CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A	(0x00080000)
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM	(0x00200000)
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_NIC_READY	(0x00400000) /* PCI_OWN_SEM */
#घोषणा CSR_HW_IF_CONFIG_REG_BIT_NIC_PREPARE_DONE (0x02000000) /* ME_OWN */
#घोषणा CSR_HW_IF_CONFIG_REG_PREPARE		  (0x08000000) /* WAKE_ME */
#घोषणा CSR_HW_IF_CONFIG_REG_ENABLE_PME		  (0x10000000)
#घोषणा CSR_HW_IF_CONFIG_REG_PERSIST_MODE	  (0x40000000) /* PERSISTENCE */

#घोषणा CSR_MBOX_SET_REG_OS_ALIVE		BIT(5)

#घोषणा CSR_INT_PERIODIC_DIS			(0x00) /* disable periodic पूर्णांक*/
#घोषणा CSR_INT_PERIODIC_ENA			(0xFF) /* 255*32 usec ~ 8 msec*/

/* पूर्णांकerrupt flags in INTA, set by uCode or hardware (e.g. dma),
 * acknowledged (reset) by host writing "1" to flagged bits. */
#घोषणा CSR_INT_BIT_FH_RX        (1 << 31) /* Rx DMA, cmd responses, FH_INT[17:16] */
#घोषणा CSR_INT_BIT_HW_ERR       (1 << 29) /* DMA hardware error FH_INT[31] */
#घोषणा CSR_INT_BIT_RX_PERIODIC	 (1 << 28) /* Rx periodic */
#घोषणा CSR_INT_BIT_FH_TX        (1 << 27) /* Tx DMA FH_INT[1:0] */
#घोषणा CSR_INT_BIT_SCD          (1 << 26) /* TXQ poपूर्णांकer advanced */
#घोषणा CSR_INT_BIT_SW_ERR       (1 << 25) /* uCode error */
#घोषणा CSR_INT_BIT_RF_KILL      (1 << 7)  /* HW RFKILL चयन GP_CNTRL[27] toggled */
#घोषणा CSR_INT_BIT_CT_KILL      (1 << 6)  /* Critical temp (chip too hot) rfसमाप्त */
#घोषणा CSR_INT_BIT_SW_RX        (1 << 3)  /* Rx, command responses */
#घोषणा CSR_INT_BIT_WAKEUP       (1 << 1)  /* NIC controller waking up (pwr mgmt) */
#घोषणा CSR_INT_BIT_ALIVE        (1 << 0)  /* uCode पूर्णांकerrupts once it initializes */

#घोषणा CSR_INI_SET_MASK	(CSR_INT_BIT_FH_RX   | \
				 CSR_INT_BIT_HW_ERR  | \
				 CSR_INT_BIT_FH_TX   | \
				 CSR_INT_BIT_SW_ERR  | \
				 CSR_INT_BIT_RF_KILL | \
				 CSR_INT_BIT_SW_RX   | \
				 CSR_INT_BIT_WAKEUP  | \
				 CSR_INT_BIT_ALIVE   | \
				 CSR_INT_BIT_RX_PERIODIC)

/* पूर्णांकerrupt flags in FH (flow handler) (PCI busmaster DMA) */
#घोषणा CSR_FH_INT_BIT_ERR       (1 << 31) /* Error */
#घोषणा CSR_FH_INT_BIT_HI_PRIOR  (1 << 30) /* High priority Rx, bypass coalescing */
#घोषणा CSR_FH_INT_BIT_RX_CHNL1  (1 << 17) /* Rx channel 1 */
#घोषणा CSR_FH_INT_BIT_RX_CHNL0  (1 << 16) /* Rx channel 0 */
#घोषणा CSR_FH_INT_BIT_TX_CHNL1  (1 << 1)  /* Tx channel 1 */
#घोषणा CSR_FH_INT_BIT_TX_CHNL0  (1 << 0)  /* Tx channel 0 */

#घोषणा CSR_FH_INT_RX_MASK	(CSR_FH_INT_BIT_HI_PRIOR | \
				CSR_FH_INT_BIT_RX_CHNL1 | \
				CSR_FH_INT_BIT_RX_CHNL0)

#घोषणा CSR_FH_INT_TX_MASK	(CSR_FH_INT_BIT_TX_CHNL1 | \
				CSR_FH_INT_BIT_TX_CHNL0)

/* GPIO */
#घोषणा CSR_GPIO_IN_BIT_AUX_POWER                   (0x00000200)
#घोषणा CSR_GPIO_IN_VAL_VAUX_PWR_SRC                (0x00000000)
#घोषणा CSR_GPIO_IN_VAL_VMAIN_PWR_SRC               (0x00000200)

/* RESET */
#घोषणा CSR_RESET_REG_FLAG_NEVO_RESET                (0x00000001)
#घोषणा CSR_RESET_REG_FLAG_FORCE_NMI                 (0x00000002)
#घोषणा CSR_RESET_REG_FLAG_SW_RESET		     (0x00000080)
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
 *    10:  XTAL ON request
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
 *         NOTE:  This करोes not indicate that device has completed
 *                init or post-घातer-करोwn restore of पूर्णांकernal SRAM memory.
 *                Use CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP as indication that
 *                SRAM is restored and uCode is in normal operation mode.
 *                Later devices (5xxx/6xxx/1xxx) use non-अस्थिर SRAM, and
 *                करो not need to save/restore it.
 *         NOTE:  After device reset, this bit reमुख्यs "0" until host sets
 *                INIT_DONE
 */
#घोषणा CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY	     (0x00000001)
#घोषणा CSR_GP_CNTRL_REG_FLAG_INIT_DONE		     (0x00000004)
#घोषणा CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ	     (0x00000008)
#घोषणा CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP	     (0x00000010)
#घोषणा CSR_GP_CNTRL_REG_FLAG_XTAL_ON		     (0x00000400)

#घोषणा CSR_GP_CNTRL_REG_VAL_MAC_ACCESS_EN	     (0x00000001)

#घोषणा CSR_GP_CNTRL_REG_MSK_POWER_SAVE_TYPE         (0x07000000)
#घोषणा CSR_GP_CNTRL_REG_FLAG_RFKILL_WAKE_L1A_EN     (0x04000000)
#घोषणा CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW          (0x08000000)


/* HW REV */
#घोषणा CSR_HW_REV_DASH(_val)          (((_val) & 0x0000003) >> 0)
#घोषणा CSR_HW_REV_STEP(_val)          (((_val) & 0x000000C) >> 2)
#घोषणा CSR_HW_REV_TYPE(_val)          (((_val) & 0x000FFF0) >> 4)

/* HW RFID */
#घोषणा CSR_HW_RFID_FLAVOR(_val)       (((_val) & 0x000000F) >> 0)
#घोषणा CSR_HW_RFID_DASH(_val)         (((_val) & 0x00000F0) >> 4)
#घोषणा CSR_HW_RFID_STEP(_val)         (((_val) & 0x0000F00) >> 8)
#घोषणा CSR_HW_RFID_TYPE(_val)         (((_val) & 0x0FFF000) >> 12)
#घोषणा CSR_HW_RFID_IS_CDB(_val)       (((_val) & 0x10000000) >> 28)
#घोषणा CSR_HW_RFID_IS_JACKET(_val)    (((_val) & 0x20000000) >> 29)

/**
 *  hw_rev values
 */
क्रमागत अणु
	SILICON_A_STEP = 0,
	SILICON_B_STEP,
	SILICON_C_STEP,
पूर्ण;


#घोषणा CSR_HW_REV_TYPE_MSK		(0x000FFF0)
#घोषणा CSR_HW_REV_TYPE_5300		(0x0000020)
#घोषणा CSR_HW_REV_TYPE_5350		(0x0000030)
#घोषणा CSR_HW_REV_TYPE_5100		(0x0000050)
#घोषणा CSR_HW_REV_TYPE_5150		(0x0000040)
#घोषणा CSR_HW_REV_TYPE_1000		(0x0000060)
#घोषणा CSR_HW_REV_TYPE_6x00		(0x0000070)
#घोषणा CSR_HW_REV_TYPE_6x50		(0x0000080)
#घोषणा CSR_HW_REV_TYPE_6150		(0x0000084)
#घोषणा CSR_HW_REV_TYPE_6x05		(0x00000B0)
#घोषणा CSR_HW_REV_TYPE_6x30		CSR_HW_REV_TYPE_6x05
#घोषणा CSR_HW_REV_TYPE_6x35		CSR_HW_REV_TYPE_6x05
#घोषणा CSR_HW_REV_TYPE_2x30		(0x00000C0)
#घोषणा CSR_HW_REV_TYPE_2x00		(0x0000100)
#घोषणा CSR_HW_REV_TYPE_105		(0x0000110)
#घोषणा CSR_HW_REV_TYPE_135		(0x0000120)
#घोषणा CSR_HW_REV_TYPE_7265D		(0x0000210)
#घोषणा CSR_HW_REV_TYPE_NONE		(0x00001F0)
#घोषणा CSR_HW_REV_TYPE_QNJ		(0x0000360)
#घोषणा CSR_HW_REV_TYPE_QNJ_B0		(0x0000364)
#घोषणा CSR_HW_REV_TYPE_QU_B0		(0x0000334)
#घोषणा CSR_HW_REV_TYPE_QU_C0		(0x0000338)
#घोषणा CSR_HW_REV_TYPE_QUZ		(0x0000354)
#घोषणा CSR_HW_REV_TYPE_HR_CDB		(0x0000340)
#घोषणा CSR_HW_REV_TYPE_SO		(0x0000370)
#घोषणा CSR_HW_REV_TYPE_TY		(0x0000420)

/* RF_ID value */
#घोषणा CSR_HW_RF_ID_TYPE_JF		(0x00105100)
#घोषणा CSR_HW_RF_ID_TYPE_HR		(0x0010A000)
#घोषणा CSR_HW_RF_ID_TYPE_HR1		(0x0010c100)
#घोषणा CSR_HW_RF_ID_TYPE_HRCDB		(0x00109F00)
#घोषणा CSR_HW_RF_ID_TYPE_GF		(0x0010D000)
#घोषणा CSR_HW_RF_ID_TYPE_GF4		(0x0010E000)

/* HW_RF CHIP ID  */
#घोषणा CSR_HW_RF_ID_TYPE_CHIP_ID(_val) (((_val) >> 12) & 0xFFF)

/* HW_RF CHIP STEP  */
#घोषणा CSR_HW_RF_STEP(_val) (((_val) >> 8) & 0xF)

/* EEPROM REG */
#घोषणा CSR_EEPROM_REG_READ_VALID_MSK	(0x00000001)
#घोषणा CSR_EEPROM_REG_BIT_CMD		(0x00000002)
#घोषणा CSR_EEPROM_REG_MSK_ADDR		(0x0000FFFC)
#घोषणा CSR_EEPROM_REG_MSK_DATA		(0xFFFF0000)

/* EEPROM GP */
#घोषणा CSR_EEPROM_GP_VALID_MSK		(0x00000007) /* signature */
#घोषणा CSR_EEPROM_GP_IF_OWNER_MSK	(0x00000180)
#घोषणा CSR_EEPROM_GP_BAD_SIGNATURE_BOTH_EEP_AND_OTP	(0x00000000)
#घोषणा CSR_EEPROM_GP_BAD_SIG_EEP_GOOD_SIG_OTP		(0x00000001)
#घोषणा CSR_EEPROM_GP_GOOD_SIG_EEP_LESS_THAN_4K		(0x00000002)
#घोषणा CSR_EEPROM_GP_GOOD_SIG_EEP_MORE_THAN_4K		(0x00000004)

/* One-समय-programmable memory general purpose reg */
#घोषणा CSR_OTP_GP_REG_DEVICE_SELECT	(0x00010000) /* 0 - EEPROM, 1 - OTP */
#घोषणा CSR_OTP_GP_REG_OTP_ACCESS_MODE	(0x00020000) /* 0 - असलolute, 1 - relative */
#घोषणा CSR_OTP_GP_REG_ECC_CORR_STATUS_MSK          (0x00100000) /* bit 20 */
#घोषणा CSR_OTP_GP_REG_ECC_UNCORR_STATUS_MSK        (0x00200000) /* bit 21 */

/* GP REG */
#घोषणा CSR_GP_REG_POWER_SAVE_STATUS_MSK            (0x03000000) /* bit 24/25 */
#घोषणा CSR_GP_REG_NO_POWER_SAVE            (0x00000000)
#घोषणा CSR_GP_REG_MAC_POWER_SAVE           (0x01000000)
#घोषणा CSR_GP_REG_PHY_POWER_SAVE           (0x02000000)
#घोषणा CSR_GP_REG_POWER_SAVE_ERROR         (0x03000000)


/* CSR GIO */
#घोषणा CSR_GIO_REG_VAL_L0S_DISABLED	(0x00000002)

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
 *         NOTE:  device saves पूर्णांकernal SRAM data to host when घातering करोwn,
 *                and must restore this data after घातering back up.
 *                MAC_SLEEP is the best indication that restore is complete.
 *                Later devices (5xxx/6xxx/1xxx) use non-अस्थिर SRAM, and
 *                करो not need to save/restore it.
 */
#घोषणा CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP             (0x00000001)
#घोषणा CSR_UCODE_SW_BIT_RFKILL                     (0x00000002)
#घोषणा CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED           (0x00000004)
#घोषणा CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT      (0x00000008)
#घोषणा CSR_UCODE_DRV_GP1_BIT_D3_CFG_COMPLETE       (0x00000020)

/* GP Driver */
#घोषणा CSR_GP_DRIVER_REG_BIT_RADIO_SKU_MSK	    (0x00000003)
#घोषणा CSR_GP_DRIVER_REG_BIT_RADIO_SKU_3x3_HYB	    (0x00000000)
#घोषणा CSR_GP_DRIVER_REG_BIT_RADIO_SKU_2x2_HYB	    (0x00000001)
#घोषणा CSR_GP_DRIVER_REG_BIT_RADIO_SKU_2x2_IPA	    (0x00000002)
#घोषणा CSR_GP_DRIVER_REG_BIT_CALIB_VERSION6	    (0x00000004)
#घोषणा CSR_GP_DRIVER_REG_BIT_6050_1x2		    (0x00000008)

#घोषणा CSR_GP_DRIVER_REG_BIT_RADIO_IQ_INVER	    (0x00000080)

/* GIO Chicken Bits (PCI Express bus link घातer management) */
#घोषणा CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX  (0x00800000)
#घोषणा CSR_GIO_CHICKEN_BITS_REG_BIT_DIS_L0S_EXIT_TIMER  (0x20000000)

/* LED */
#घोषणा CSR_LED_BSM_CTRL_MSK (0xFFFFFFDF)
#घोषणा CSR_LED_REG_TURN_ON (0x60)
#घोषणा CSR_LED_REG_TURN_OFF (0x20)

/* ANA_PLL */
#घोषणा CSR50_ANA_PLL_CFG_VAL        (0x00880300)

/* HPET MEM debug */
#घोषणा CSR_DBG_HPET_MEM_REG_VAL	(0xFFFF0000)

/* DRAM INT TABLE */
#घोषणा CSR_DRAM_INT_TBL_ENABLE		(1 << 31)
#घोषणा CSR_DRAM_INIT_TBL_WRITE_POINTER	(1 << 28)
#घोषणा CSR_DRAM_INIT_TBL_WRAP_CHECK	(1 << 27)

/*
 * SHR target access (Shared block memory space)
 *
 * Shared पूर्णांकernal रेजिस्टरs can be accessed directly from PCI bus through SHR
 * arbiter without need क्रम the MAC HW to be घातered up. This is possible due to
 * indirect पढ़ो/ग_लिखो via HEEP_CTRL_WRD_PCIEX_CTRL (0xEC) and
 * HEEP_CTRL_WRD_PCIEX_DATA (0xF4) रेजिस्टरs.
 *
 * Use iwl_ग_लिखो32()/iwl_पढ़ो32() family to access these रेजिस्टरs. The MAC HW
 * need not be घातered up so no "grab inc access" is required.
 */

/*
 * Registers क्रम accessing shared रेजिस्टरs (e.g. SHR_APMG_GP1,
 * SHR_APMG_XTAL_CFG). For example, to पढ़ो from SHR_APMG_GP1 रेजिस्टर (0x1DC),
 * first, ग_लिखो to the control रेजिस्टर:
 * HEEP_CTRL_WRD_PCIEX_CTRL[15:0] = 0x1DC (offset of the SHR_APMG_GP1 रेजिस्टर)
 * HEEP_CTRL_WRD_PCIEX_CTRL[29:28] = 2 (पढ़ो access)
 * second, पढ़ो from the data रेजिस्टर HEEP_CTRL_WRD_PCIEX_DATA[31:0].
 *
 * To ग_लिखो the रेजिस्टर, first, ग_लिखो to the data रेजिस्टर
 * HEEP_CTRL_WRD_PCIEX_DATA[31:0] and then:
 * HEEP_CTRL_WRD_PCIEX_CTRL[15:0] = 0x1DC (offset of the SHR_APMG_GP1 रेजिस्टर)
 * HEEP_CTRL_WRD_PCIEX_CTRL[29:28] = 3 (ग_लिखो access)
 */
#घोषणा HEEP_CTRL_WRD_PCIEX_CTRL_REG	(CSR_BASE+0x0ec)
#घोषणा HEEP_CTRL_WRD_PCIEX_DATA_REG	(CSR_BASE+0x0f4)

/*
 * HBUS (Host-side Bus)
 *
 * HBUS रेजिस्टरs are mapped directly पूर्णांकo PCI bus space, but are used
 * to indirectly access device's पूर्णांकernal memory or रेजिस्टरs that
 * may be घातered-करोwn.
 *
 * Use iwl_ग_लिखो_direct32()/iwl_पढ़ो_direct32() family क्रम these रेजिस्टरs;
 * host must "grab nic access" via CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ
 * to make sure the MAC (uCode processor, etc.) is घातered up क्रम accessing
 * पूर्णांकernal resources.
 *
 * Do not use iwl_ग_लिखो32()/iwl_पढ़ो32() family to access these रेजिस्टरs;
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

/* Used to enable DBGM */
#घोषणा HBUS_TARG_TEST_REG	(HBUS_BASE+0x05c)

/*
 * Per-Tx-queue ग_लिखो poपूर्णांकer (index, really!)
 * Indicates index to next TFD that driver will fill (1 past latest filled).
 * Bit usage:
 *  0-7:  queue ग_लिखो index
 * 11-8:  queue selector
 */
#घोषणा HBUS_TARG_WRPTR         (HBUS_BASE+0x060)

/**********************************************************
 * CSR values
 **********************************************************/
 /*
 * host पूर्णांकerrupt समयout value
 * used with setting पूर्णांकerrupt coalescing समयr
 * the CSR_INT_COALESCING is an 8 bit रेजिस्टर in 32-usec unit
 *
 * शेष पूर्णांकerrupt coalescing समयr is 64 x 32 = 2048 usecs
 */
#घोषणा IWL_HOST_INT_TIMEOUT_MAX	(0xFF)
#घोषणा IWL_HOST_INT_TIMEOUT_DEF	(0x40)
#घोषणा IWL_HOST_INT_TIMEOUT_MIN	(0x0)
#घोषणा IWL_HOST_INT_OPER_MODE		BIT(31)

/*****************************************************************************
 *                        7000/3000 series SHR DTS addresses                 *
 *****************************************************************************/

/* Diode Results Register Structure: */
क्रमागत dtd_diode_reg अणु
	DTS_DIODE_REG_DIG_VAL			= 0x000000FF, /* bits [7:0] */
	DTS_DIODE_REG_VREF_LOW			= 0x0000FF00, /* bits [15:8] */
	DTS_DIODE_REG_VREF_HIGH			= 0x00FF0000, /* bits [23:16] */
	DTS_DIODE_REG_VREF_ID			= 0x03000000, /* bits [25:24] */
	DTS_DIODE_REG_PASS_ONCE			= 0x80000000, /* bits [31:31] */
	DTS_DIODE_REG_FLAGS_MSK			= 0xFF000000, /* bits [31:24] */
/* Those are the masks INSIDE the flags bit-field: */
	DTS_DIODE_REG_FLAGS_VREFS_ID_POS	= 0,
	DTS_DIODE_REG_FLAGS_VREFS_ID		= 0x00000003, /* bits [1:0] */
	DTS_DIODE_REG_FLAGS_PASS_ONCE_POS	= 7,
	DTS_DIODE_REG_FLAGS_PASS_ONCE		= 0x00000080, /* bits [7:7] */
पूर्ण;

/*****************************************************************************
 *                        MSIX related रेजिस्टरs                             *
 *****************************************************************************/

#घोषणा CSR_MSIX_BASE			(0x2000)
#घोषणा CSR_MSIX_FH_INT_CAUSES_AD	(CSR_MSIX_BASE + 0x800)
#घोषणा CSR_MSIX_FH_INT_MASK_AD		(CSR_MSIX_BASE + 0x804)
#घोषणा CSR_MSIX_HW_INT_CAUSES_AD	(CSR_MSIX_BASE + 0x808)
#घोषणा CSR_MSIX_HW_INT_MASK_AD		(CSR_MSIX_BASE + 0x80C)
#घोषणा CSR_MSIX_AUTOMASK_ST_AD		(CSR_MSIX_BASE + 0x810)
#घोषणा CSR_MSIX_RX_IVAR_AD_REG		(CSR_MSIX_BASE + 0x880)
#घोषणा CSR_MSIX_IVAR_AD_REG		(CSR_MSIX_BASE + 0x890)
#घोषणा CSR_MSIX_PENDING_PBA_AD		(CSR_MSIX_BASE + 0x1000)
#घोषणा CSR_MSIX_RX_IVAR(cause)		(CSR_MSIX_RX_IVAR_AD_REG + (cause))
#घोषणा CSR_MSIX_IVAR(cause)		(CSR_MSIX_IVAR_AD_REG + (cause))

#घोषणा MSIX_FH_INT_CAUSES_Q(q)		(q)

/*
 * Causes क्रम the FH रेजिस्टर पूर्णांकerrupts
 */
क्रमागत msix_fh_पूर्णांक_causes अणु
	MSIX_FH_INT_CAUSES_Q0			= BIT(0),
	MSIX_FH_INT_CAUSES_Q1			= BIT(1),
	MSIX_FH_INT_CAUSES_D2S_CH0_NUM		= BIT(16),
	MSIX_FH_INT_CAUSES_D2S_CH1_NUM		= BIT(17),
	MSIX_FH_INT_CAUSES_S2D			= BIT(19),
	MSIX_FH_INT_CAUSES_FH_ERR		= BIT(21),
पूर्ण;

/* The low 16 bits are क्रम rx data queue indication */
#घोषणा MSIX_FH_INT_CAUSES_DATA_QUEUE 0xffff

/*
 * Causes क्रम the HW रेजिस्टर पूर्णांकerrupts
 */
क्रमागत msix_hw_पूर्णांक_causes अणु
	MSIX_HW_INT_CAUSES_REG_ALIVE		= BIT(0),
	MSIX_HW_INT_CAUSES_REG_WAKEUP		= BIT(1),
	MSIX_HW_INT_CAUSES_REG_IML              = BIT(1),
	MSIX_HW_INT_CAUSES_REG_RESET_DONE	= BIT(2),
	MSIX_HW_INT_CAUSES_REG_CT_KILL		= BIT(6),
	MSIX_HW_INT_CAUSES_REG_RF_KILL		= BIT(7),
	MSIX_HW_INT_CAUSES_REG_PERIODIC		= BIT(8),
	MSIX_HW_INT_CAUSES_REG_SW_ERR		= BIT(25),
	MSIX_HW_INT_CAUSES_REG_SCD		= BIT(26),
	MSIX_HW_INT_CAUSES_REG_FH_TX		= BIT(27),
	MSIX_HW_INT_CAUSES_REG_HW_ERR		= BIT(29),
	MSIX_HW_INT_CAUSES_REG_HAP		= BIT(30),
पूर्ण;

#घोषणा MSIX_MIN_INTERRUPT_VECTORS		2
#घोषणा MSIX_AUTO_CLEAR_CAUSE			0
#घोषणा MSIX_NON_AUTO_CLEAR_CAUSE		BIT(7)

/*****************************************************************************
 *                     HW address related रेजिस्टरs                          *
 *****************************************************************************/

#घोषणा CSR_ADDR_BASE			(0x380)
#घोषणा CSR_MAC_ADDR0_OTP		(CSR_ADDR_BASE)
#घोषणा CSR_MAC_ADDR1_OTP		(CSR_ADDR_BASE + 4)
#घोषणा CSR_MAC_ADDR0_STRAP		(CSR_ADDR_BASE + 8)
#घोषणा CSR_MAC_ADDR1_STRAP		(CSR_ADDR_BASE + 0xC)

#पूर्ण_अगर /* !__iwl_csr_h__ */
