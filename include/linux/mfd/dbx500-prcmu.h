<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST Ericsson SA 2011
 *
 * STE Ux500 PRCMU API
 */
#अगर_अघोषित __MACH_PRCMU_H
#घोषणा __MACH_PRCMU_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/err.h>

#समावेश <dt-bindings/mfd/dbx500-prcmu.h> /* For घड़ी identअगरiers */

/* Offset क्रम the firmware version within the TCPM */
#घोषणा DB8500_PRCMU_FW_VERSION_OFFSET 0xA4
#घोषणा DBX540_PRCMU_FW_VERSION_OFFSET 0xA8

/* PRCMU Wakeup defines */
क्रमागत prcmu_wakeup_index अणु
	PRCMU_WAKEUP_INDEX_RTC,
	PRCMU_WAKEUP_INDEX_RTT0,
	PRCMU_WAKEUP_INDEX_RTT1,
	PRCMU_WAKEUP_INDEX_HSI0,
	PRCMU_WAKEUP_INDEX_HSI1,
	PRCMU_WAKEUP_INDEX_USB,
	PRCMU_WAKEUP_INDEX_ABB,
	PRCMU_WAKEUP_INDEX_ABB_FIFO,
	PRCMU_WAKEUP_INDEX_ARM,
	PRCMU_WAKEUP_INDEX_CD_IRQ,
	NUM_PRCMU_WAKEUP_INDICES
पूर्ण;
#घोषणा PRCMU_WAKEUP(_name) (BIT(PRCMU_WAKEUP_INDEX_##_name))

/* EPOD (घातer करोमुख्य) IDs */

/*
 * DB8500 EPODs
 * - EPOD_ID_SVAMMDSP: घातer करोमुख्य क्रम SVA MMDSP
 * - EPOD_ID_SVAPIPE: घातer करोमुख्य क्रम SVA pipe
 * - EPOD_ID_SIAMMDSP: घातer करोमुख्य क्रम SIA MMDSP
 * - EPOD_ID_SIAPIPE: घातer करोमुख्य क्रम SIA pipe
 * - EPOD_ID_SGA: घातer करोमुख्य क्रम SGA
 * - EPOD_ID_B2R2_MCDE: घातer करोमुख्य क्रम B2R2 and MCDE
 * - EPOD_ID_ESRAM12: घातer करोमुख्य क्रम ESRAM 1 and 2
 * - EPOD_ID_ESRAM34: घातer करोमुख्य क्रम ESRAM 3 and 4
 * - NUM_EPOD_ID: number of घातer करोमुख्यs
 *
 * TODO: These should be prefixed.
 */
#घोषणा EPOD_ID_SVAMMDSP	0
#घोषणा EPOD_ID_SVAPIPE		1
#घोषणा EPOD_ID_SIAMMDSP	2
#घोषणा EPOD_ID_SIAPIPE		3
#घोषणा EPOD_ID_SGA		4
#घोषणा EPOD_ID_B2R2_MCDE	5
#घोषणा EPOD_ID_ESRAM12		6
#घोषणा EPOD_ID_ESRAM34		7
#घोषणा NUM_EPOD_ID		8

/*
 * state definition क्रम EPOD (घातer करोमुख्य)
 * - EPOD_STATE_NO_CHANGE: The EPOD should reमुख्य unchanged
 * - EPOD_STATE_OFF: The EPOD is चयनed off
 * - EPOD_STATE_RAMRET: The EPOD is चयनed off with its पूर्णांकernal RAM in
 *                         retention
 * - EPOD_STATE_ON_CLK_OFF: The EPOD is चयनed on, घड़ी is still off
 * - EPOD_STATE_ON: Same as above, but with घड़ी enabled
 */
#घोषणा EPOD_STATE_NO_CHANGE	0x00
#घोषणा EPOD_STATE_OFF		0x01
#घोषणा EPOD_STATE_RAMRET	0x02
#घोषणा EPOD_STATE_ON_CLK_OFF	0x03
#घोषणा EPOD_STATE_ON		0x04

/*
 * CLKOUT sources
 */
#घोषणा PRCMU_CLKSRC_CLK38M		0x00
#घोषणा PRCMU_CLKSRC_ACLK		0x01
#घोषणा PRCMU_CLKSRC_SYSCLK		0x02
#घोषणा PRCMU_CLKSRC_LCDCLK		0x03
#घोषणा PRCMU_CLKSRC_SDMMCCLK		0x04
#घोषणा PRCMU_CLKSRC_TVCLK		0x05
#घोषणा PRCMU_CLKSRC_TIMCLK		0x06
#घोषणा PRCMU_CLKSRC_CLK009		0x07
/* These are only valid क्रम CLKOUT1: */
#घोषणा PRCMU_CLKSRC_SIAMMDSPCLK	0x40
#घोषणा PRCMU_CLKSRC_I2CCLK		0x41
#घोषणा PRCMU_CLKSRC_MSP02CLK		0x42
#घोषणा PRCMU_CLKSRC_ARMPLL_OBSCLK	0x43
#घोषणा PRCMU_CLKSRC_HSIRXCLK		0x44
#घोषणा PRCMU_CLKSRC_HSITXCLK		0x45
#घोषणा PRCMU_CLKSRC_ARMCLKFIX		0x46
#घोषणा PRCMU_CLKSRC_HDMICLK		0x47

/**
 * क्रमागत prcmu_wकरोg_id - PRCMU watchकरोg IDs
 * @PRCMU_WDOG_ALL: use all समयrs
 * @PRCMU_WDOG_CPU1: use first CPU समयr only
 * @PRCMU_WDOG_CPU2: use second CPU समयr conly
 */
क्रमागत prcmu_wकरोg_id अणु
	PRCMU_WDOG_ALL = 0x00,
	PRCMU_WDOG_CPU1 = 0x01,
	PRCMU_WDOG_CPU2 = 0x02,
पूर्ण;

/**
 * क्रमागत ape_opp - APE OPP states definition
 * @APE_OPP_INIT:
 * @APE_NO_CHANGE: The APE operating poपूर्णांक is unchanged
 * @APE_100_OPP: The new APE operating poपूर्णांक is ape100opp
 * @APE_50_OPP: 50%
 * @APE_50_PARTLY_25_OPP: 50%, except some घड़ीs at 25%.
 */
क्रमागत ape_opp अणु
	APE_OPP_INIT = 0x00,
	APE_NO_CHANGE = 0x01,
	APE_100_OPP = 0x02,
	APE_50_OPP = 0x03,
	APE_50_PARTLY_25_OPP = 0xFF,
पूर्ण;

/**
 * क्रमागत arm_opp - ARM OPP states definition
 * @ARM_OPP_INIT:
 * @ARM_NO_CHANGE: The ARM operating poपूर्णांक is unchanged
 * @ARM_100_OPP: The new ARM operating poपूर्णांक is arm100opp
 * @ARM_50_OPP: The new ARM operating poपूर्णांक is arm50opp
 * @ARM_MAX_OPP: Operating poपूर्णांक is "max" (more than 100)
 * @ARM_MAX_FREQ100OPP: Set max opp अगर available, अन्यथा 100
 * @ARM_EXTCLK: The new ARM operating poपूर्णांक is armExtClk
 */
क्रमागत arm_opp अणु
	ARM_OPP_INIT = 0x00,
	ARM_NO_CHANGE = 0x01,
	ARM_100_OPP = 0x02,
	ARM_50_OPP = 0x03,
	ARM_MAX_OPP = 0x04,
	ARM_MAX_FREQ100OPP = 0x05,
	ARM_EXTCLK = 0x07
पूर्ण;

/**
 * क्रमागत ddr_opp - DDR OPP states definition
 * @DDR_100_OPP: The new DDR operating poपूर्णांक is ddr100opp
 * @DDR_50_OPP: The new DDR operating poपूर्णांक is ddr50opp
 * @DDR_25_OPP: The new DDR operating poपूर्णांक is ddr25opp
 */
क्रमागत ddr_opp अणु
	DDR_100_OPP = 0x00,
	DDR_50_OPP = 0x01,
	DDR_25_OPP = 0x02,
पूर्ण;

/*
 * Definitions क्रम controlling ESRAM0 in deep sleep.
 */
#घोषणा ESRAM0_DEEP_SLEEP_STATE_OFF 1
#घोषणा ESRAM0_DEEP_SLEEP_STATE_RET 2

/**
 * क्रमागत ddr_pwrst - DDR घातer states definition
 * @DDR_PWR_STATE_UNCHANGED: SDRAM and DDR controller state is unchanged
 * @DDR_PWR_STATE_ON:
 * @DDR_PWR_STATE_OFFLOWLAT:
 * @DDR_PWR_STATE_OFFHIGHLAT:
 */
क्रमागत ddr_pwrst अणु
	DDR_PWR_STATE_UNCHANGED     = 0x00,
	DDR_PWR_STATE_ON            = 0x01,
	DDR_PWR_STATE_OFFLOWLAT     = 0x02,
	DDR_PWR_STATE_OFFHIGHLAT    = 0x03
पूर्ण;

#घोषणा DB8500_PRCMU_LEGACY_OFFSET		0xDD4

#घोषणा PRCMU_FW_PROJECT_U8500		2
#घोषणा PRCMU_FW_PROJECT_U8400		3
#घोषणा PRCMU_FW_PROJECT_U9500		4 /* Customer specअगरic */
#घोषणा PRCMU_FW_PROJECT_U8500_MBB	5
#घोषणा PRCMU_FW_PROJECT_U8500_C1	6
#घोषणा PRCMU_FW_PROJECT_U8500_C2	7
#घोषणा PRCMU_FW_PROJECT_U8500_C3	8
#घोषणा PRCMU_FW_PROJECT_U8500_C4	9
#घोषणा PRCMU_FW_PROJECT_U9500_MBL	10
#घोषणा PRCMU_FW_PROJECT_U8500_MBL	11 /* Customer specअगरic */
#घोषणा PRCMU_FW_PROJECT_U8500_MBL2	12 /* Customer specअगरic */
#घोषणा PRCMU_FW_PROJECT_U8520		13
#घोषणा PRCMU_FW_PROJECT_U8420		14
#घोषणा PRCMU_FW_PROJECT_U8420_SYSCLK	17
#घोषणा PRCMU_FW_PROJECT_A9420		20
/* [32..63] 9540 and derivatives */
#घोषणा PRCMU_FW_PROJECT_U9540		32
/* [64..95] 8540 and derivatives */
#घोषणा PRCMU_FW_PROJECT_L8540		64
/* [96..126] 8580 and derivatives */
#घोषणा PRCMU_FW_PROJECT_L8580		96

#घोषणा PRCMU_FW_PROJECT_NAME_LEN	20
काष्ठा prcmu_fw_version अणु
	u32 project; /* Notice, project shअगरted with 8 on ux540 */
	u8 api_version;
	u8 func_version;
	u8 errata;
	अक्षर project_name[PRCMU_FW_PROJECT_NAME_LEN];
पूर्ण;

#समावेश <linux/mfd/db8500-prcmu.h>

#अगर defined(CONFIG_UX500_SOC_DB8500)

अटल अंतरभूत व्योम prcmu_early_init(व्योम)
अणु
	वापस db8500_prcmu_early_init();
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_घातer_state(u8 state, bool keep_ulp_clk,
		bool keep_ap_pll)
अणु
	वापस db8500_prcmu_set_घातer_state(state, keep_ulp_clk,
		keep_ap_pll);
पूर्ण

अटल अंतरभूत u8 prcmu_get_घातer_state_result(व्योम)
अणु
	वापस db8500_prcmu_get_घातer_state_result();
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_epod(u16 epod_id, u8 epod_state)
अणु
	वापस db8500_prcmu_set_epod(epod_id, epod_state);
पूर्ण

अटल अंतरभूत व्योम prcmu_enable_wakeups(u32 wakeups)
अणु
	db8500_prcmu_enable_wakeups(wakeups);
पूर्ण

अटल अंतरभूत व्योम prcmu_disable_wakeups(व्योम)
अणु
	prcmu_enable_wakeups(0);
पूर्ण

अटल अंतरभूत व्योम prcmu_config_abb_event_पढ़ोout(u32 abb_events)
अणु
	db8500_prcmu_config_abb_event_पढ़ोout(abb_events);
पूर्ण

अटल अंतरभूत व्योम prcmu_get_abb_event_buffer(व्योम __iomem **buf)
अणु
	db8500_prcmu_get_abb_event_buffer(buf);
पूर्ण

पूर्णांक prcmu_abb_पढ़ो(u8 slave, u8 reg, u8 *value, u8 size);
पूर्णांक prcmu_abb_ग_लिखो(u8 slave, u8 reg, u8 *value, u8 size);
पूर्णांक prcmu_abb_ग_लिखो_masked(u8 slave, u8 reg, u8 *value, u8 *mask, u8 size);

पूर्णांक prcmu_config_clkout(u8 clkout, u8 source, u8 भाग);

अटल अंतरभूत पूर्णांक prcmu_request_घड़ी(u8 घड़ी, bool enable)
अणु
	वापस db8500_prcmu_request_घड़ी(घड़ी, enable);
पूर्ण

अचिन्हित दीर्घ prcmu_घड़ी_rate(u8 घड़ी);
दीर्घ prcmu_round_घड़ी_rate(u8 घड़ी, अचिन्हित दीर्घ rate);
पूर्णांक prcmu_set_घड़ी_rate(u8 घड़ी, अचिन्हित दीर्घ rate);

अटल अंतरभूत पूर्णांक prcmu_get_ddr_opp(व्योम)
अणु
	वापस db8500_prcmu_get_ddr_opp();
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_arm_opp(u8 opp)
अणु
	वापस db8500_prcmu_set_arm_opp(opp);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_get_arm_opp(व्योम)
अणु
	वापस db8500_prcmu_get_arm_opp();
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_ape_opp(u8 opp)
अणु
	वापस db8500_prcmu_set_ape_opp(opp);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_get_ape_opp(व्योम)
अणु
	वापस db8500_prcmu_get_ape_opp();
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_request_ape_opp_100_voltage(bool enable)
अणु
	वापस db8500_prcmu_request_ape_opp_100_voltage(enable);
पूर्ण

अटल अंतरभूत व्योम prcmu_प्रणाली_reset(u16 reset_code)
अणु
	वापस db8500_prcmu_प्रणाली_reset(reset_code);
पूर्ण

अटल अंतरभूत u16 prcmu_get_reset_code(व्योम)
अणु
	वापस db8500_prcmu_get_reset_code();
पूर्ण

पूर्णांक prcmu_ac_wake_req(व्योम);
व्योम prcmu_ac_sleep_req(व्योम);
अटल अंतरभूत व्योम prcmu_modem_reset(व्योम)
अणु
	वापस db8500_prcmu_modem_reset();
पूर्ण

अटल अंतरभूत bool prcmu_is_ac_wake_requested(व्योम)
अणु
	वापस db8500_prcmu_is_ac_wake_requested();
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_config_esram0_deep_sleep(u8 state)
अणु
	वापस db8500_prcmu_config_esram0_deep_sleep(state);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_config_hotकरोg(u8 threshold)
अणु
	वापस db8500_prcmu_config_hotकरोg(threshold);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_config_hoपंचांगon(u8 low, u8 high)
अणु
	वापस db8500_prcmu_config_hoपंचांगon(low, high);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_start_temp_sense(u16 cycles32k)
अणु
	वापस  db8500_prcmu_start_temp_sense(cycles32k);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_stop_temp_sense(व्योम)
अणु
	वापस  db8500_prcmu_stop_temp_sense();
पूर्ण

अटल अंतरभूत u32 prcmu_पढ़ो(अचिन्हित पूर्णांक reg)
अणु
	वापस db8500_prcmu_पढ़ो(reg);
पूर्ण

अटल अंतरभूत व्योम prcmu_ग_लिखो(अचिन्हित पूर्णांक reg, u32 value)
अणु
	db8500_prcmu_ग_लिखो(reg, value);
पूर्ण

अटल अंतरभूत व्योम prcmu_ग_लिखो_masked(अचिन्हित पूर्णांक reg, u32 mask, u32 value)
अणु
	db8500_prcmu_ग_लिखो_masked(reg, mask, value);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_enable_a9wकरोg(u8 id)
अणु
	वापस db8500_prcmu_enable_a9wकरोg(id);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_disable_a9wकरोg(u8 id)
अणु
	वापस db8500_prcmu_disable_a9wकरोg(id);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_kick_a9wकरोg(u8 id)
अणु
	वापस db8500_prcmu_kick_a9wकरोg(id);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_load_a9wकरोg(u8 id, u32 समयout)
अणु
	वापस db8500_prcmu_load_a9wकरोg(id, समयout);
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_config_a9wकरोg(u8 num, bool sleep_स्वतः_off)
अणु
	वापस db8500_prcmu_config_a9wकरोg(num, sleep_स्वतः_off);
पूर्ण
#अन्यथा

अटल अंतरभूत व्योम prcmu_early_init(व्योम) अणुपूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_घातer_state(u8 state, bool keep_ulp_clk,
	bool keep_ap_pll)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_epod(u16 epod_id, u8 epod_state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम prcmu_enable_wakeups(u32 wakeups) अणुपूर्ण

अटल अंतरभूत व्योम prcmu_disable_wakeups(व्योम) अणुपूर्ण

अटल अंतरभूत पूर्णांक prcmu_abb_पढ़ो(u8 slave, u8 reg, u8 *value, u8 size)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_abb_ग_लिखो(u8 slave, u8 reg, u8 *value, u8 size)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_abb_ग_लिखो_masked(u8 slave, u8 reg, u8 *value, u8 *mask,
	u8 size)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_config_clkout(u8 clkout, u8 source, u8 भाग)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_request_घड़ी(u8 घड़ी, bool enable)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत दीर्घ prcmu_round_घड़ी_rate(u8 घड़ी, अचिन्हित दीर्घ rate)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_घड़ी_rate(u8 घड़ी, अचिन्हित दीर्घ rate)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ prcmu_घड़ी_rate(u8 घड़ी)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_ape_opp(u8 opp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_get_ape_opp(व्योम)
अणु
	वापस APE_100_OPP;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_request_ape_opp_100_voltage(bool enable)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_set_arm_opp(u8 opp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_get_arm_opp(व्योम)
अणु
	वापस ARM_100_OPP;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_get_ddr_opp(व्योम)
अणु
	वापस DDR_100_OPP;
पूर्ण

अटल अंतरभूत व्योम prcmu_प्रणाली_reset(u16 reset_code) अणुपूर्ण

अटल अंतरभूत u16 prcmu_get_reset_code(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_ac_wake_req(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम prcmu_ac_sleep_req(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम prcmu_modem_reset(व्योम) अणुपूर्ण

अटल अंतरभूत bool prcmu_is_ac_wake_requested(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_config_esram0_deep_sleep(u8 state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम prcmu_config_abb_event_पढ़ोout(u32 abb_events) अणुपूर्ण

अटल अंतरभूत व्योम prcmu_get_abb_event_buffer(व्योम __iomem **buf)
अणु
	*buf = शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_config_hotकरोg(u8 threshold)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_config_hoपंचांगon(u8 low, u8 high)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_start_temp_sense(u16 cycles32k)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_stop_temp_sense(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 prcmu_पढ़ो(अचिन्हित पूर्णांक reg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम prcmu_ग_लिखो(अचिन्हित पूर्णांक reg, u32 value) अणुपूर्ण

अटल अंतरभूत व्योम prcmu_ग_लिखो_masked(अचिन्हित पूर्णांक reg, u32 mask, u32 value) अणुपूर्ण

#पूर्ण_अगर

अटल अंतरभूत व्योम prcmu_set(अचिन्हित पूर्णांक reg, u32 bits)
अणु
	prcmu_ग_लिखो_masked(reg, bits, bits);
पूर्ण

अटल अंतरभूत व्योम prcmu_clear(अचिन्हित पूर्णांक reg, u32 bits)
अणु
	prcmu_ग_लिखो_masked(reg, bits, 0);
पूर्ण

/* PRCMU QoS APE OPP class */
#घोषणा PRCMU_QOS_APE_OPP 1
#घोषणा PRCMU_QOS_DDR_OPP 2
#घोषणा PRCMU_QOS_ARM_OPP 3
#घोषणा PRCMU_QOS_DEFAULT_VALUE -1

#अगर_घोषित CONFIG_DBX500_PRCMU_QOS_POWER

अचिन्हित दीर्घ prcmu_qos_get_cpufreq_opp_delay(व्योम);
व्योम prcmu_qos_set_cpufreq_opp_delay(अचिन्हित दीर्घ);
व्योम prcmu_qos_क्रमce_opp(पूर्णांक, s32);
पूर्णांक prcmu_qos_requirement(पूर्णांक pm_qos_class);
पूर्णांक prcmu_qos_add_requirement(पूर्णांक pm_qos_class, अक्षर *name, s32 value);
पूर्णांक prcmu_qos_update_requirement(पूर्णांक pm_qos_class, अक्षर *name, s32 new_value);
व्योम prcmu_qos_हटाओ_requirement(पूर्णांक pm_qos_class, अक्षर *name);
पूर्णांक prcmu_qos_add_notअगरier(पूर्णांक prcmu_qos_class,
			   काष्ठा notअगरier_block *notअगरier);
पूर्णांक prcmu_qos_हटाओ_notअगरier(पूर्णांक prcmu_qos_class,
			      काष्ठा notअगरier_block *notअगरier);

#अन्यथा

अटल अंतरभूत अचिन्हित दीर्घ prcmu_qos_get_cpufreq_opp_delay(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम prcmu_qos_set_cpufreq_opp_delay(अचिन्हित दीर्घ n) अणुपूर्ण

अटल अंतरभूत व्योम prcmu_qos_क्रमce_opp(पूर्णांक prcmu_qos_class, s32 i) अणुपूर्ण

अटल अंतरभूत पूर्णांक prcmu_qos_requirement(पूर्णांक prcmu_qos_class)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_qos_add_requirement(पूर्णांक prcmu_qos_class,
					    अक्षर *name, s32 value)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_qos_update_requirement(पूर्णांक prcmu_qos_class,
					       अक्षर *name, s32 new_value)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम prcmu_qos_हटाओ_requirement(पूर्णांक prcmu_qos_class, अक्षर *name)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक prcmu_qos_add_notअगरier(पूर्णांक prcmu_qos_class,
					 काष्ठा notअगरier_block *notअगरier)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक prcmu_qos_हटाओ_notअगरier(पूर्णांक prcmu_qos_class,
					    काष्ठा notअगरier_block *notअगरier)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __MACH_PRCMU_H */
