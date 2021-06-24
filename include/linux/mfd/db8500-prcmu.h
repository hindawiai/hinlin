<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) STMicroelectronics 2009
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Kumar Sanghvi <kumar.sanghvi@stericsson.com>
 *
 * PRCMU f/w APIs
 */
#अगर_अघोषित __MFD_DB8500_PRCMU_H
#घोषणा __MFD_DB8500_PRCMU_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>

/*
 * Registers
 */
#घोषणा DB8500_PRCM_LINE_VALUE 0x170
#घोषणा DB8500_PRCM_LINE_VALUE_HSI_CAWAKE0	BIT(3)

#घोषणा DB8500_PRCM_DSI_SW_RESET 0x324
#घोषणा DB8500_PRCM_DSI_SW_RESET_DSI0_SW_RESETN BIT(0)
#घोषणा DB8500_PRCM_DSI_SW_RESET_DSI1_SW_RESETN BIT(1)
#घोषणा DB8500_PRCM_DSI_SW_RESET_DSI2_SW_RESETN BIT(2)

/* This portion previously known as <mach/prcmu-fw-defs_v1.h> */

/**
 * क्रमागत state - ON/OFF state definition
 * @OFF: State is ON
 * @ON: State is OFF
 *
 */
क्रमागत state अणु
	OFF = 0x0,
	ON  = 0x1,
पूर्ण;

/**
 * क्रमागत ret_state - general purpose On/Off/Retention states
 *
 */
क्रमागत ret_state अणु
	OFFST = 0,
	ONST  = 1,
	RETST = 2
पूर्ण;

/**
 * क्रमागत clk_arm - ARM Cortex A9 घड़ी schemes
 * @A9_OFF:
 * @A9_BOOT:
 * @A9_OPPT1:
 * @A9_OPPT2:
 * @A9_EXTCLK:
 */
क्रमागत clk_arm अणु
	A9_OFF,
	A9_BOOT,
	A9_OPPT1,
	A9_OPPT2,
	A9_EXTCLK
पूर्ण;

/**
 * क्रमागत clk_gen - GEN#0/GEN#1 घड़ी schemes
 * @GEN_OFF:
 * @GEN_BOOT:
 * @GEN_OPPT1:
 */
क्रमागत clk_gen अणु
	GEN_OFF,
	GEN_BOOT,
	GEN_OPPT1,
पूर्ण;

/* some inक्रमmation between arm and xp70 */

/**
 * क्रमागत romcode_ग_लिखो - Romcode message written by A9 AND पढ़ो by XP70
 * @RDY_2_DS: Value set when ApDeepSleep state can be executed by XP70
 * @RDY_2_XP70_RST: Value set when 0x0F has been successfully polled by the
 *                 romcode. The xp70 will go पूर्णांकo self-reset
 */
क्रमागत romcode_ग_लिखो अणु
	RDY_2_DS = 0x09,
	RDY_2_XP70_RST = 0x10
पूर्ण;

/**
 * क्रमागत romcode_पढ़ो - Romcode message written by XP70 and पढ़ो by A9
 * @INIT: Init value when romcode field is not used
 * @FS_2_DS: Value set when घातer state is going from ApExecute to
 *          ApDeepSleep
 * @END_DS: Value set when ApDeepSleep घातer state is reached coming from
 *         ApExecute state
 * @DS_TO_FS: Value set when घातer state is going from ApDeepSleep to
 *           ApExecute
 * @END_FS: Value set when ApExecute घातer state is reached coming from
 *         ApDeepSleep state
 * @SWR: Value set when घातer state is going to ApReset
 * @END_SWR: Value set when the xp70 finished executing ApReset actions and
 *          रुकोs क्रम romcode acknowledgment to go to self-reset
 */
क्रमागत romcode_पढ़ो अणु
	INIT = 0x00,
	FS_2_DS = 0x0A,
	END_DS = 0x0B,
	DS_TO_FS = 0x0C,
	END_FS = 0x0D,
	SWR = 0x0E,
	END_SWR = 0x0F
पूर्ण;

/**
 * क्रमागत ap_pwrst - current घातer states defined in PRCMU firmware
 * @NO_PWRST: Current घातer state init
 * @AP_BOOT: Current घातer state is apBoot
 * @AP_EXECUTE: Current घातer state is apExecute
 * @AP_DEEP_SLEEP: Current घातer state is apDeepSleep
 * @AP_SLEEP: Current घातer state is apSleep
 * @AP_IDLE: Current घातer state is apIdle
 * @AP_RESET: Current घातer state is apReset
 */
क्रमागत ap_pwrst अणु
	NO_PWRST = 0x00,
	AP_BOOT = 0x01,
	AP_EXECUTE = 0x02,
	AP_DEEP_SLEEP = 0x03,
	AP_SLEEP = 0x04,
	AP_IDLE = 0x05,
	AP_RESET = 0x06
पूर्ण;

/**
 * क्रमागत ap_pwrst_trans - Transition states defined in PRCMU firmware
 * @NO_TRANSITION: No घातer state transition
 * @APEXECUTE_TO_APSLEEP: Power state transition from ApExecute to ApSleep
 * @APIDLE_TO_APSLEEP: Power state transition from ApIdle to ApSleep
 * @APBOOT_TO_APEXECUTE: Power state transition from ApBoot to ApExecute
 * @APEXECUTE_TO_APDEEPSLEEP: Power state transition from ApExecute to
 *                          ApDeepSleep
 * @APEXECUTE_TO_APIDLE: Power state transition from ApExecute to ApIdle
 */
क्रमागत ap_pwrst_trans अणु
	PRCMU_AP_NO_CHANGE		= 0x00,
	APEXECUTE_TO_APSLEEP		= 0x01,
	APIDLE_TO_APSLEEP		= 0x02, /* To be हटाओd */
	PRCMU_AP_SLEEP			= 0x01,
	APBOOT_TO_APEXECUTE		= 0x03,
	APEXECUTE_TO_APDEEPSLEEP	= 0x04, /* To be हटाओd */
	PRCMU_AP_DEEP_SLEEP		= 0x04,
	APEXECUTE_TO_APIDLE		= 0x05, /* To be हटाओd */
	PRCMU_AP_IDLE			= 0x05,
	PRCMU_AP_DEEP_IDLE		= 0x07,
पूर्ण;

/**
 * क्रमागत hw_acc_state - State definition क्रम hardware accelerator
 * @HW_NO_CHANGE: The hardware accelerator state must reमुख्य unchanged
 * @HW_OFF: The hardware accelerator must be चयनed off
 * @HW_OFF_RAMRET: The hardware accelerator must be चयनed off with its
 *               पूर्णांकernal RAM in retention
 * @HW_ON: The hwa hardware accelerator hwa must be चयनed on
 *
 * NOTE! Deprecated, to be हटाओd when all users चयनed over to use the
 * regulator API.
 */
क्रमागत hw_acc_state अणु
	HW_NO_CHANGE = 0x00,
	HW_OFF = 0x01,
	HW_OFF_RAMRET = 0x02,
	HW_ON = 0x04
पूर्ण;

/**
 * क्रमागत  mbox_2_arm_stat - Status messages definition क्रम mbox_arm
 * @BOOT_TO_EXECUTEOK: The apBoot to apExecute state transition has been
 *                    completed
 * @DEEPSLEEPOK: The apExecute to apDeepSleep state transition has been
 *              completed
 * @SLEEPOK: The apExecute to apSleep state transition has been completed
 * @IDLEOK: The apExecute to apIdle state transition has been completed
 * @SOFTRESETOK: The A9 watchकरोg/ SoftReset state has been completed
 * @SOFTRESETGO : The A9 watchकरोg/SoftReset state is on going
 * @BOOT_TO_EXECUTE: The apBoot to apExecute state transition is on going
 * @EXECUTE_TO_DEEPSLEEP: The apExecute to apDeepSleep state transition is on
 *                       going
 * @DEEPSLEEP_TO_EXECUTE: The apDeepSleep to apExecute state transition is on
 *                       going
 * @DEEPSLEEP_TO_EXECUTEOK: The apDeepSleep to apExecute state transition has
 *                         been completed
 * @EXECUTE_TO_SLEEP: The apExecute to apSleep state transition is on going
 * @SLEEP_TO_EXECUTE: The apSleep to apExecute state transition is on going
 * @SLEEP_TO_EXECUTEOK: The apSleep to apExecute state transition has been
 *                     completed
 * @EXECUTE_TO_IDLE: The apExecute to apIdle state transition is on going
 * @IDLE_TO_EXECUTE: The apIdle to apExecute state transition is on going
 * @IDLE_TO_EXECUTEOK: The apIdle to apExecute state transition has been
 *                    completed
 * @INIT_STATUS: Status init
 */
क्रमागत ap_pwrsttr_status अणु
	BOOT_TO_EXECUTEOK = 0xFF,
	DEEPSLEEPOK = 0xFE,
	SLEEPOK = 0xFD,
	IDLEOK = 0xFC,
	SOFTRESETOK = 0xFB,
	SOFTRESETGO = 0xFA,
	BOOT_TO_EXECUTE = 0xF9,
	EXECUTE_TO_DEEPSLEEP = 0xF8,
	DEEPSLEEP_TO_EXECUTE = 0xF7,
	DEEPSLEEP_TO_EXECUTEOK = 0xF6,
	EXECUTE_TO_SLEEP = 0xF5,
	SLEEP_TO_EXECUTE = 0xF4,
	SLEEP_TO_EXECUTEOK = 0xF3,
	EXECUTE_TO_IDLE = 0xF2,
	IDLE_TO_EXECUTE = 0xF1,
	IDLE_TO_EXECUTEOK = 0xF0,
	RDYTODS_RETURNTOEXE    = 0xEF,
	NORDYTODS_RETURNTOEXE  = 0xEE,
	EXETOSLEEP_RETURNTOEXE = 0xED,
	EXETOIDLE_RETURNTOEXE  = 0xEC,
	INIT_STATUS = 0xEB,

	/*error messages */
	INITERROR                     = 0x00,
	PLLARMLOCKP_ER                = 0x01,
	PLLDDRLOCKP_ER                = 0x02,
	PLLSOCLOCKP_ER                = 0x03,
	PLLSOCK1LOCKP_ER              = 0x04,
	ARMWFI_ER                     = 0x05,
	SYSCLKOK_ER                   = 0x06,
	I2C_NACK_DATA_ER              = 0x07,
	BOOT_ER                       = 0x08,
	I2C_STATUS_ALWAYS_1           = 0x0A,
	I2C_NACK_REG_ADDR_ER          = 0x0B,
	I2C_NACK_DATA0123_ER          = 0x1B,
	I2C_NACK_ADDR_ER              = 0x1F,
	CURAPPWRSTISNOT_BOOT          = 0x20,
	CURAPPWRSTISNOT_EXECUTE       = 0x21,
	CURAPPWRSTISNOT_SLEEPMODE     = 0x22,
	CURAPPWRSTISNOT_CORRECTFORIT10 = 0x23,
	FIFO4500WUISNOT_WUPEVENT      = 0x24,
	PLL32KLOCKP_ER                = 0x29,
	DDRDEEPSLEEPOK_ER             = 0x2A,
	ROMCODEREADY_ER               = 0x50,
	WUPBEFOREDS                   = 0x51,
	DDRCONFIG_ER                  = 0x52,
	WUPBEFORESLEEP                = 0x53,
	WUPBEFOREIDLE                 = 0x54
पूर्ण;  /* earlier called as  mbox_2_arm_stat */

/**
 * क्रमागत dvfs_stat - DVFS status messages definition
 * @DVFS_GO: A state transition DVFS is on going
 * @DVFS_ARM100OPPOK: The state transition DVFS has been completed क्रम 100OPP
 * @DVFS_ARM50OPPOK: The state transition DVFS has been completed क्रम 50OPP
 * @DVFS_ARMEXTCLKOK: The state transition DVFS has been completed क्रम EXTCLK
 * @DVFS_NOCHGTCLKOK: The state transition DVFS has been completed क्रम
 *                   NOCHGCLK
 * @DVFS_INITSTATUS: Value init
 */
क्रमागत dvfs_stat अणु
	DVFS_GO = 0xFF,
	DVFS_ARM100OPPOK = 0xFE,
	DVFS_ARM50OPPOK = 0xFD,
	DVFS_ARMEXTCLKOK = 0xFC,
	DVFS_NOCHGTCLKOK = 0xFB,
	DVFS_INITSTATUS = 0x00
पूर्ण;

/**
 * क्रमागत sva_mmdsp_stat - SVA MMDSP status messages
 * @SVA_MMDSP_GO: SVAMMDSP पूर्णांकerrupt has happened
 * @SVA_MMDSP_INIT: Status init
 */
क्रमागत sva_mmdsp_stat अणु
	SVA_MMDSP_GO = 0xFF,
	SVA_MMDSP_INIT = 0x00
पूर्ण;

/**
 * क्रमागत sia_mmdsp_stat - SIA MMDSP status messages
 * @SIA_MMDSP_GO: SIAMMDSP पूर्णांकerrupt has happened
 * @SIA_MMDSP_INIT: Status init
 */
क्रमागत sia_mmdsp_stat अणु
	SIA_MMDSP_GO = 0xFF,
	SIA_MMDSP_INIT = 0x00
पूर्ण;

/**
 * क्रमागत  mbox_to_arm_err - Error messages definition
 * @INIT_ERR: Init value
 * @PLLARMLOCKP_ERR: PLLARM has not been correctly locked in given समय
 * @PLLDDRLOCKP_ERR: PLLDDR has not been correctly locked in the given समय
 * @PLLSOC0LOCKP_ERR: PLLSOC0 has not been correctly locked in the given समय
 * @PLLSOC1LOCKP_ERR: PLLSOC1 has not been correctly locked in the given समय
 * @ARMWFI_ERR: The ARM WFI has not been correctly executed in the given समय
 * @SYSCLKOK_ERR: The SYSCLK is not available in the given समय
 * @BOOT_ERR: Romcode has not validated the XP70 self reset in the given समय
 * @ROMCODESAVECONTEXT: The Romcode didn.t correctly save it secure context
 * @VARMHIGHSPEEDVALTO_ERR: The ARM high speed supply value transfered
 *          through I2C has not been correctly executed in the given समय
 * @VARMHIGHSPEEDACCESS_ERR: The command value of VarmHighSpeedVal transfered
 *             through I2C has not been correctly executed in the given समय
 * @VARMLOWSPEEDVALTO_ERR:The ARM low speed supply value transfered through
 *                     I2C has not been correctly executed in the given समय
 * @VARMLOWSPEEDACCESS_ERR: The command value of VarmLowSpeedVal transfered
 *             through I2C has not been correctly executed in the given समय
 * @VARMRETENTIONVALTO_ERR: The ARM retention supply value transfered through
 *                     I2C has not been correctly executed in the given समय
 * @VARMRETENTIONACCESS_ERR: The command value of VarmRetentionVal transfered
 *             through I2C has not been correctly executed in the given समय
 * @VAPEHIGHSPEEDVALTO_ERR: The APE highspeed supply value transfered through
 *                     I2C has not been correctly executed in the given समय
 * @VSAFEHPVALTO_ERR: The SAFE high घातer supply value transfered through I2C
 *                         has not been correctly executed in the given समय
 * @VMODSEL1VALTO_ERR: The MODEM sel1 supply value transfered through I2C has
 *                             not been correctly executed in the given समय
 * @VMODSEL2VALTO_ERR: The MODEM sel2 supply value transfered through I2C has
 *                             not been correctly executed in the given समय
 * @VARMOFFACCESS_ERR: The command value of Varm ON/OFF transfered through
 *                     I2C has not been correctly executed in the given समय
 * @VAPखातापूर्णFACCESS_ERR: The command value of Vape ON/OFF transfered through
 *                     I2C has not been correctly executed in the given समय
 * @VARMRETACCES_ERR: The command value of Varm retention ON/OFF transfered
 *             through I2C has not been correctly executed in the given समय
 * @CURAPPWRSTISNOTBOOT:Generated when Arm want to करो घातer state transition
 *             ApBoot to ApExecute but the घातer current state is not Apboot
 * @CURAPPWRSTISNOTEXECUTE: Generated when Arm want to करो घातer state
 *              transition from ApExecute to others घातer state but the
 *              घातer current state is not ApExecute
 * @CURAPPWRSTISNOTSLEEPMODE: Generated when wake up events are transmitted
 *             but the घातer current state is not ApDeepSleep/ApSleep/ApIdle
 * @CURAPPWRSTISNOTCORRECTDBG:  Generated when wake up events are transmitted
 *              but the घातer current state is not correct
 * @ARMREGU1VALTO_ERR:The ArmRegu1 value transferred through I2C has not
 *                    been correctly executed in the given समय
 * @ARMREGU2VALTO_ERR: The ArmRegu2 value transferred through I2C has not
 *                    been correctly executed in the given समय
 * @VAPEREGUVALTO_ERR: The VApeRegu value transfered through I2C has not
 *                    been correctly executed in the given समय
 * @VSMPS3REGUVALTO_ERR: The VSmps3Regu value transfered through I2C has not
 *                      been correctly executed in the given समय
 * @VMODREGUVALTO_ERR: The VModemRegu value transfered through I2C has not
 *                    been correctly executed in the given समय
 */
क्रमागत mbox_to_arm_err अणु
	INIT_ERR = 0x00,
	PLLARMLOCKP_ERR = 0x01,
	PLLDDRLOCKP_ERR = 0x02,
	PLLSOC0LOCKP_ERR = 0x03,
	PLLSOC1LOCKP_ERR = 0x04,
	ARMWFI_ERR = 0x05,
	SYSCLKOK_ERR = 0x06,
	BOOT_ERR = 0x07,
	ROMCODESAVECONTEXT = 0x08,
	VARMHIGHSPEEDVALTO_ERR = 0x10,
	VARMHIGHSPEEDACCESS_ERR = 0x11,
	VARMLOWSPEEDVALTO_ERR = 0x12,
	VARMLOWSPEEDACCESS_ERR = 0x13,
	VARMRETENTIONVALTO_ERR = 0x14,
	VARMRETENTIONACCESS_ERR = 0x15,
	VAPEHIGHSPEEDVALTO_ERR = 0x16,
	VSAFEHPVALTO_ERR = 0x17,
	VMODSEL1VALTO_ERR = 0x18,
	VMODSEL2VALTO_ERR = 0x19,
	VARMOFFACCESS_ERR = 0x1A,
	VAPखातापूर्णFACCESS_ERR = 0x1B,
	VARMRETACCES_ERR = 0x1C,
	CURAPPWRSTISNOTBOOT = 0x20,
	CURAPPWRSTISNOTEXECUTE = 0x21,
	CURAPPWRSTISNOTSLEEPMODE = 0x22,
	CURAPPWRSTISNOTCORRECTDBG = 0x23,
	ARMREGU1VALTO_ERR = 0x24,
	ARMREGU2VALTO_ERR = 0x25,
	VAPEREGUVALTO_ERR = 0x26,
	VSMPS3REGUVALTO_ERR = 0x27,
	VMODREGUVALTO_ERR = 0x28
पूर्ण;

क्रमागत hw_acc अणु
	SVAMMDSP = 0,
	SVAPIPE = 1,
	SIAMMDSP = 2,
	SIAPIPE = 3,
	SGA = 4,
	B2R2MCDE = 5,
	ESRAM12 = 6,
	ESRAM34 = 7,
पूर्ण;

क्रमागत cs_pwrmgt अणु
	PWRDNCS0  = 0,
	WKUPCS0   = 1,
	PWRDNCS1  = 2,
	WKUPCS1   = 3
पूर्ण;

/* Defs related to स्वतःnomous घातer management */

/**
 * क्रमागत sia_sva_pwr_policy - Power policy
 * @NO_CHGT:	No change
 * @DSPOFF_HWPOFF:
 * @DSPOFFRAMRET_HWPOFF:
 * @DSPCLKOFF_HWPOFF:
 * @DSPCLKOFF_HWPCLKOFF:
 *
 */
क्रमागत sia_sva_pwr_policy अणु
	NO_CHGT			= 0x0,
	DSPOFF_HWPOFF		= 0x1,
	DSPOFFRAMRET_HWPOFF	= 0x2,
	DSPCLKOFF_HWPOFF	= 0x3,
	DSPCLKOFF_HWPCLKOFF	= 0x4,
पूर्ण;

/**
 * क्रमागत स्वतः_enable - Auto Power enable
 * @AUTO_OFF:
 * @AUTO_ON:
 *
 */
क्रमागत स्वतः_enable अणु
	AUTO_OFF	= 0x0,
	AUTO_ON		= 0x1,
पूर्ण;

/* End of file previously known as prcmu-fw-defs_v1.h */

/**
 * क्रमागत prcmu_घातer_status - results from set_घातer_state
 * @PRCMU_SLEEP_OK: Sleep went ok
 * @PRCMU_DEEP_SLEEP_OK: DeepSleep went ok
 * @PRCMU_IDLE_OK: Idle went ok
 * @PRCMU_DEEPIDLE_OK: DeepIdle went ok
 * @PRCMU_PRCMU2ARMPENDINGIT_ER: Pending पूर्णांकerrupt detected
 * @PRCMU_ARMPENDINGIT_ER: Pending पूर्णांकerrupt detected
 *
 */
क्रमागत prcmu_घातer_status अणु
	PRCMU_SLEEP_OK			= 0xf3,
	PRCMU_DEEP_SLEEP_OK		= 0xf6,
	PRCMU_IDLE_OK			= 0xf0,
	PRCMU_DEEPIDLE_OK		= 0xe3,
	PRCMU_PRCMU2ARMPENDINGIT_ER	= 0x91,
	PRCMU_ARMPENDINGIT_ER		= 0x93,
पूर्ण;

/*
 * Definitions क्रम स्वतःnomous घातer management configuration.
 */

#घोषणा PRCMU_AUTO_PM_OFF 0
#घोषणा PRCMU_AUTO_PM_ON 1

#घोषणा PRCMU_AUTO_PM_POWER_ON_HSEM BIT(0)
#घोषणा PRCMU_AUTO_PM_POWER_ON_ABB_FIFO_IT BIT(1)

क्रमागत prcmu_स्वतः_pm_policy अणु
	PRCMU_AUTO_PM_POLICY_NO_CHANGE,
	PRCMU_AUTO_PM_POLICY_DSP_OFF_HWP_OFF,
	PRCMU_AUTO_PM_POLICY_DSP_OFF_RAMRET_HWP_OFF,
	PRCMU_AUTO_PM_POLICY_DSP_CLK_OFF_HWP_OFF,
	PRCMU_AUTO_PM_POLICY_DSP_CLK_OFF_HWP_CLK_OFF,
पूर्ण;

/**
 * काष्ठा prcmu_स्वतः_pm_config - Autonomous घातer management configuration.
 * @sia_स्वतः_pm_enable: SIA स्वतःnomous pm enable. (PRCMU_AUTO_PM_अणुOFF,ONपूर्ण)
 * @sia_घातer_on:       SIA घातer ON enable. (PRCMU_AUTO_PM_POWER_ON_* biपंचांगask)
 * @sia_policy:         SIA घातer policy. (क्रमागत prcmu_स्वतः_pm_policy)
 * @sva_स्वतः_pm_enable: SVA स्वतःnomous pm enable. (PRCMU_AUTO_PM_अणुOFF,ONपूर्ण)
 * @sva_घातer_on:       SVA घातer ON enable. (PRCMU_AUTO_PM_POWER_ON_* biपंचांगask)
 * @sva_policy:         SVA घातer policy. (क्रमागत prcmu_स्वतः_pm_policy)
 */
काष्ठा prcmu_स्वतः_pm_config अणु
	u8 sia_स्वतः_pm_enable;
	u8 sia_घातer_on;
	u8 sia_policy;
	u8 sva_स्वतः_pm_enable;
	u8 sva_घातer_on;
	u8 sva_policy;
पूर्ण;

#अगर_घोषित CONFIG_MFD_DB8500_PRCMU

व्योम db8500_prcmu_early_init(व्योम);
पूर्णांक prcmu_set_rc_a2p(क्रमागत romcode_ग_लिखो);
क्रमागत romcode_पढ़ो prcmu_get_rc_p2a(व्योम);
क्रमागत ap_pwrst prcmu_get_xp70_current_state(व्योम);
bool prcmu_has_arm_maxopp(व्योम);
काष्ठा prcmu_fw_version *prcmu_get_fw_version(व्योम);
पूर्णांक prcmu_release_usb_wakeup_state(व्योम);
व्योम prcmu_configure_स्वतः_pm(काष्ठा prcmu_स्वतः_pm_config *sleep,
	काष्ठा prcmu_स्वतः_pm_config *idle);
bool prcmu_is_स्वतः_pm_enabled(व्योम);

पूर्णांक prcmu_config_clkout(u8 clkout, u8 source, u8 भाग);
पूर्णांक prcmu_set_घड़ी_भागider(u8 घड़ी, u8 भागider);
पूर्णांक db8500_prcmu_config_hotकरोg(u8 threshold);
पूर्णांक db8500_prcmu_config_hoपंचांगon(u8 low, u8 high);
पूर्णांक db8500_prcmu_start_temp_sense(u16 cycles32k);
पूर्णांक db8500_prcmu_stop_temp_sense(व्योम);
पूर्णांक prcmu_abb_पढ़ो(u8 slave, u8 reg, u8 *value, u8 size);
पूर्णांक prcmu_abb_ग_लिखो(u8 slave, u8 reg, u8 *value, u8 size);

पूर्णांक prcmu_ac_wake_req(व्योम);
व्योम prcmu_ac_sleep_req(व्योम);
व्योम db8500_prcmu_modem_reset(व्योम);

पूर्णांक db8500_prcmu_config_a9wकरोg(u8 num, bool sleep_स्वतः_off);
पूर्णांक db8500_prcmu_enable_a9wकरोg(u8 id);
पूर्णांक db8500_prcmu_disable_a9wकरोg(u8 id);
पूर्णांक db8500_prcmu_kick_a9wकरोg(u8 id);
पूर्णांक db8500_prcmu_load_a9wकरोg(u8 id, u32 val);

व्योम db8500_prcmu_प्रणाली_reset(u16 reset_code);
पूर्णांक db8500_prcmu_set_घातer_state(u8 state, bool keep_ulp_clk, bool keep_ap_pll);
u8 db8500_prcmu_get_घातer_state_result(व्योम);
व्योम db8500_prcmu_enable_wakeups(u32 wakeups);
पूर्णांक db8500_prcmu_set_epod(u16 epod_id, u8 epod_state);
पूर्णांक db8500_prcmu_request_घड़ी(u8 घड़ी, bool enable);
व्योम db8500_prcmu_config_abb_event_पढ़ोout(u32 abb_events);
व्योम db8500_prcmu_get_abb_event_buffer(व्योम __iomem **buf);
पूर्णांक db8500_prcmu_config_esram0_deep_sleep(u8 state);
u16 db8500_prcmu_get_reset_code(व्योम);
bool db8500_prcmu_is_ac_wake_requested(व्योम);
पूर्णांक db8500_prcmu_set_arm_opp(u8 opp);
पूर्णांक db8500_prcmu_get_arm_opp(व्योम);
पूर्णांक db8500_prcmu_set_ape_opp(u8 opp);
पूर्णांक db8500_prcmu_get_ape_opp(व्योम);
पूर्णांक db8500_prcmu_request_ape_opp_100_voltage(bool enable);
पूर्णांक db8500_prcmu_get_ddr_opp(व्योम);

u32 db8500_prcmu_पढ़ो(अचिन्हित पूर्णांक reg);
व्योम db8500_prcmu_ग_लिखो(अचिन्हित पूर्णांक reg, u32 value);
व्योम db8500_prcmu_ग_लिखो_masked(अचिन्हित पूर्णांक reg, u32 mask, u32 value);

#अन्यथा /* !CONFIG_MFD_DB8500_PRCMU */

अटल अंतरभूत व्योम db8500_prcmu_early_init(व्योम) अणुपूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_rc_a2p(क्रमागत romcode_ग_लिखो code)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत romcode_पढ़ो prcmu_get_rc_p2a(व्योम)
अणु
	वापस INIT;
पूर्ण

अटल अंतरभूत क्रमागत ap_pwrst prcmu_get_xp70_current_state(व्योम)
अणु
	वापस AP_EXECUTE;
पूर्ण

अटल अंतरभूत bool prcmu_has_arm_maxopp(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा prcmu_fw_version *prcmu_get_fw_version(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_set_ape_opp(u8 opp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_get_ape_opp(व्योम)
अणु
	वापस APE_100_OPP;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_request_ape_opp_100_voltage(bool enable)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_release_usb_wakeup_state(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_get_ddr_opp(व्योम)
अणु
	वापस DDR_100_OPP;
पूर्ण

अटल अंतरभूत व्योम prcmu_configure_स्वतः_pm(काष्ठा prcmu_स्वतः_pm_config *sleep,
	काष्ठा prcmu_स्वतः_pm_config *idle)
अणु
पूर्ण

अटल अंतरभूत bool prcmu_is_स्वतः_pm_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_config_clkout(u8 clkout, u8 source, u8 भाग)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_घड़ी_भागider(u8 घड़ी, u8 भागider)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_config_hotकरोg(u8 threshold)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_config_hoपंचांगon(u8 low, u8 high)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_start_temp_sense(u16 cycles32k)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_stop_temp_sense(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_abb_पढ़ो(u8 slave, u8 reg, u8 *value, u8 size)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_abb_ग_लिखो(u8 slave, u8 reg, u8 *value, u8 size)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_ac_wake_req(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम prcmu_ac_sleep_req(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम db8500_prcmu_modem_reset(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम db8500_prcmu_प्रणाली_reset(u16 reset_code) अणुपूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_set_घातer_state(u8 state, bool keep_ulp_clk,
	bool keep_ap_pll)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u8 db8500_prcmu_get_घातer_state_result(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम db8500_prcmu_enable_wakeups(u32 wakeups) अणुपूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_set_epod(u16 epod_id, u8 epod_state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_request_घड़ी(u8 घड़ी, bool enable)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_config_esram0_deep_sleep(u8 state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम db8500_prcmu_config_abb_event_पढ़ोout(u32 abb_events) अणुपूर्ण

अटल अंतरभूत व्योम db8500_prcmu_get_abb_event_buffer(व्योम __iomem **buf) अणुपूर्ण

अटल अंतरभूत u16 db8500_prcmu_get_reset_code(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_config_a9wकरोg(u8 num, bool sleep_स्वतः_off)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_enable_a9wकरोg(u8 id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_disable_a9wकरोg(u8 id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_kick_a9wकरोg(u8 id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_load_a9wकरोg(u8 id, u32 val)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool db8500_prcmu_is_ac_wake_requested(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_set_arm_opp(u8 opp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक db8500_prcmu_get_arm_opp(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 db8500_prcmu_पढ़ो(अचिन्हित पूर्णांक reg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम db8500_prcmu_ग_लिखो(अचिन्हित पूर्णांक reg, u32 value) अणुपूर्ण

अटल अंतरभूत व्योम db8500_prcmu_ग_लिखो_masked(अचिन्हित पूर्णांक reg, u32 mask,
	u32 value) अणुपूर्ण

#पूर्ण_अगर /* !CONFIG_MFD_DB8500_PRCMU */

#पूर्ण_अगर /* __MFD_DB8500_PRCMU_H */
