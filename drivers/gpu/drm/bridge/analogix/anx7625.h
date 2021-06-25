<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2020, Analogix Semiconductor. All rights reserved.
 *
 */

#अगर_अघोषित __ANX7625_H__
#घोषणा __ANX7625_H__

#घोषणा ANX7625_DRV_VERSION "0.1.04"

/* Loading OCM re-trying बार */
#घोषणा OCM_LOADING_TIME 10

/*********  ANX7625 Register  **********/
#घोषणा TX_P0_ADDR				0x70
#घोषणा TX_P1_ADDR				0x7A
#घोषणा TX_P2_ADDR				0x72

#घोषणा RX_P0_ADDR				0x7e
#घोषणा RX_P1_ADDR				0x84
#घोषणा RX_P2_ADDR				0x54

#घोषणा RSVD_00_ADDR				0x00
#घोषणा RSVD_D1_ADDR				0xD1
#घोषणा RSVD_60_ADDR				0x60
#घोषणा RSVD_39_ADDR				0x39
#घोषणा RSVD_7F_ADDR				0x7F

#घोषणा TCPC_INTERFACE_ADDR			0x58

/* Clock frequency in Hz */
#घोषणा XTAL_FRQ        (27 * 1000000)

#घोषणा  POST_DIVIDER_MIN	1
#घोषणा  POST_DIVIDER_MAX	16
#घोषणा  PLL_OUT_FREQ_MIN	520000000UL
#घोषणा  PLL_OUT_FREQ_MAX	730000000UL
#घोषणा  PLL_OUT_FREQ_ABS_MIN	300000000UL
#घोषणा  PLL_OUT_FREQ_ABS_MAX	800000000UL
#घोषणा  MAX_UNSIGNED_24BIT	16777215UL

/***************************************************************/
/* Register definition of device address 0x58 */

#घोषणा PRODUCT_ID_L 0x02
#घोषणा PRODUCT_ID_H 0x03

#घोषणा INTR_ALERT_1  0xCC
#घोषणा INTR_SOFTWARE_INT BIT(3)
#घोषणा INTR_RECEIVED_MSG BIT(5)

#घोषणा SYSTEM_STSTUS 0x45
#घोषणा INTERFACE_CHANGE_INT 0x44
#घोषणा HPD_STATUS_CHANGE 0x80
#घोषणा HPD_STATUS 0x80

/******** END of I2C Address 0x58 ********/

/***************************************************************/
/* Register definition of device address 0x70 */
#घोषणा  I2C_ADDR_70_DPTX              0x70

#घोषणा SP_TX_LINK_BW_SET_REG 0xA0
#घोषणा SP_TX_LANE_COUNT_SET_REG 0xA1

#घोषणा M_VID_0 0xC0
#घोषणा M_VID_1 0xC1
#घोषणा M_VID_2 0xC2
#घोषणा N_VID_0 0xC3
#घोषणा N_VID_1 0xC4
#घोषणा N_VID_2 0xC5

/***************************************************************/
/* Register definition of device address 0x72 */
#घोषणा AUX_RST	0x04
#घोषणा RST_CTRL2 0x07

#घोषणा SP_TX_TOTAL_LINE_STA_L 0x24
#घोषणा SP_TX_TOTAL_LINE_STA_H 0x25
#घोषणा SP_TX_ACT_LINE_STA_L 0x26
#घोषणा SP_TX_ACT_LINE_STA_H 0x27
#घोषणा SP_TX_V_F_PORCH_STA 0x28
#घोषणा SP_TX_V_SYNC_STA 0x29
#घोषणा SP_TX_V_B_PORCH_STA 0x2A
#घोषणा SP_TX_TOTAL_PIXEL_STA_L 0x2B
#घोषणा SP_TX_TOTAL_PIXEL_STA_H 0x2C
#घोषणा SP_TX_ACT_PIXEL_STA_L 0x2D
#घोषणा SP_TX_ACT_PIXEL_STA_H 0x2E
#घोषणा SP_TX_H_F_PORCH_STA_L 0x2F
#घोषणा SP_TX_H_F_PORCH_STA_H 0x30
#घोषणा SP_TX_H_SYNC_STA_L 0x31
#घोषणा SP_TX_H_SYNC_STA_H 0x32
#घोषणा SP_TX_H_B_PORCH_STA_L 0x33
#घोषणा SP_TX_H_B_PORCH_STA_H 0x34

#घोषणा SP_TX_VID_CTRL 0x84
#घोषणा SP_TX_BPC_MASK 0xE0
#घोषणा SP_TX_BPC_6    0x00
#घोषणा SP_TX_BPC_8    0x20
#घोषणा SP_TX_BPC_10   0x40
#घोषणा SP_TX_BPC_12   0x60

#घोषणा VIDEO_BIT_MATRIX_12 0x4c

#घोषणा AUDIO_CHANNEL_STATUS_1 0xd0
#घोषणा AUDIO_CHANNEL_STATUS_2 0xd1
#घोषणा AUDIO_CHANNEL_STATUS_3 0xd2
#घोषणा AUDIO_CHANNEL_STATUS_4 0xd3
#घोषणा AUDIO_CHANNEL_STATUS_5 0xd4
#घोषणा AUDIO_CHANNEL_STATUS_6 0xd5
#घोषणा TDM_SLAVE_MODE 0x10
#घोषणा I2S_SLAVE_MODE 0x08

#घोषणा AUDIO_CONTROL_REGISTER 0xe6
#घोषणा TDM_TIMING_MODE 0x08

#घोषणा I2C_ADDR_72_DPTX              0x72

#घोषणा HP_MIN			8
#घोषणा HBLANKING_MIN		80
#घोषणा SYNC_LEN_DEF		32
#घोषणा HFP_HBP_DEF		((HBLANKING_MIN - SYNC_LEN_DEF) / 2)
#घोषणा VIDEO_CONTROL_0	0x08

#घोषणा  ACTIVE_LINES_L         0x14
#घोषणा  ACTIVE_LINES_H         0x15  /* Bit[7:6] are reserved */
#घोषणा  VERTICAL_FRONT_PORCH   0x16
#घोषणा  VERTICAL_SYNC_WIDTH    0x17
#घोषणा  VERTICAL_BACK_PORCH    0x18

#घोषणा  HORIZONTAL_TOTAL_PIXELS_L    0x19
#घोषणा  HORIZONTAL_TOTAL_PIXELS_H    0x1A  /* Bit[7:6] are reserved */
#घोषणा  HORIZONTAL_ACTIVE_PIXELS_L   0x1B
#घोषणा  HORIZONTAL_ACTIVE_PIXELS_H   0x1C  /* Bit[7:6] are reserved */
#घोषणा  HORIZONTAL_FRONT_PORCH_L     0x1D
#घोषणा  HORIZONTAL_FRONT_PORCH_H     0x1E  /* Bit[7:4] are reserved */
#घोषणा  HORIZONTAL_SYNC_WIDTH_L      0x1F
#घोषणा  HORIZONTAL_SYNC_WIDTH_H      0x20  /* Bit[7:4] are reserved */
#घोषणा  HORIZONTAL_BACK_PORCH_L      0x21
#घोषणा  HORIZONTAL_BACK_PORCH_H      0x22  /* Bit[7:4] are reserved */

/******** END of I2C Address 0x72 *********/
/***************************************************************/
/* Register definition of device address 0x7e */

#घोषणा  I2C_ADDR_7E_FLASH_CONTROLLER  0x7E

#घोषणा FLASH_LOAD_STA 0x05
#घोषणा FLASH_LOAD_STA_CHK	BIT(7)

#घोषणा  XTAL_FRQ_SEL    0x3F
/* bit field positions */
#घोषणा  XTAL_FRQ_SEL_POS    5
/* bit field values */
#घोषणा  XTAL_FRQ_19M2   (0 << XTAL_FRQ_SEL_POS)
#घोषणा  XTAL_FRQ_27M    (4 << XTAL_FRQ_SEL_POS)

#घोषणा  R_DSC_CTRL_0    0x40
#घोषणा  READ_STATUS_EN  7
#घोषणा  CLK_1MEG_RB     6  /* 1MHz घड़ी reset; 0=reset, 0=reset release */
#घोषणा  DSC_BIST_DONE   1  /* Bit[5:1]: 1=DSC MBIST pass */
#घोषणा  DSC_EN          0x01  /* 1=DSC enabled, 0=DSC disabled */

#घोषणा OCM_FW_VERSION   0x31
#घोषणा OCM_FW_REVERSION 0x32

#घोषणा AP_AUX_ADDR_7_0   0x11
#घोषणा AP_AUX_ADDR_15_8  0x12
#घोषणा AP_AUX_ADDR_19_16 0x13

/* Bit[0:3] AUX status, bit 4 op_en, bit 5 address only */
#घोषणा AP_AUX_CTRL_STATUS 0x14
#घोषणा AP_AUX_CTRL_OP_EN 0x10
#घोषणा AP_AUX_CTRL_ADDRONLY 0x20

#घोषणा AP_AUX_BUFF_START 0x15
#घोषणा PIXEL_CLOCK_L 0x25
#घोषणा PIXEL_CLOCK_H 0x26

#घोषणा AP_AUX_COMMAND 0x27  /* com+len */
/* Bit 0&1: 3D video काष्ठाure */
/* 0x01: frame packing,  0x02:Line alternative, 0x03:Side-by-side(full) */
#घोषणा AP_AV_STATUS 0x28
#घोषणा AP_VIDEO_CHG  BIT(2)
#घोषणा AP_AUDIO_CHG  BIT(3)
#घोषणा AP_MIPI_MUTE  BIT(4) /* 1:MIPI input mute, 0: ummute */
#घोषणा AP_MIPI_RX_EN BIT(5) /* 1: MIPI RX input in  0: no RX in */
#घोषणा AP_DISABLE_PD BIT(6)
#घोषणा AP_DISABLE_DISPLAY BIT(7)
/***************************************************************/
/* Register definition of device address 0x84 */
#घोषणा  MIPI_PHY_CONTROL_3            0x03
#घोषणा  MIPI_HS_PWD_CLK               7
#घोषणा  MIPI_HS_RT_CLK                6
#घोषणा  MIPI_PD_CLK                   5
#घोषणा  MIPI_CLK_RT_MANUAL_PD_EN      4
#घोषणा  MIPI_CLK_HS_MANUAL_PD_EN      3
#घोषणा  MIPI_CLK_DET_DET_BYPASS       2
#घोषणा  MIPI_CLK_MISS_CTRL            1
#घोषणा  MIPI_PD_LPTX_CH_MANUAL_PD_EN  0

#घोषणा  MIPI_LANE_CTRL_0		0x05
#घोषणा  MIPI_TIME_HS_PRPR		0x08

/*
 * After MIPI RX protocol layer received video frames,
 * Protocol layer starts to reस्थिरruct video stream from PHY
 */
#घोषणा  MIPI_VIDEO_STABLE_CNT           0x0A

#घोषणा  MIPI_LANE_CTRL_10               0x0F
#घोषणा  MIPI_DIGITAL_ADJ_1   0x1B

#घोषणा  MIPI_PLL_M_NUM_23_16   0x1E
#घोषणा  MIPI_PLL_M_NUM_15_8    0x1F
#घोषणा  MIPI_PLL_M_NUM_7_0     0x20
#घोषणा  MIPI_PLL_N_NUM_23_16   0x21
#घोषणा  MIPI_PLL_N_NUM_15_8    0x22
#घोषणा  MIPI_PLL_N_NUM_7_0     0x23

#घोषणा  MIPI_DIGITAL_PLL_6     0x2A
/* Bit[7:6]: VCO band control, only effective */
#घोषणा  MIPI_M_NUM_READY        0x10
#घोषणा  MIPI_N_NUM_READY        0x08
#घोषणा  STABLE_INTEGER_CNT_EN   0x04
#घोषणा  MIPI_PLL_TEST_BIT       0
/* Bit[1:0]: test poपूर्णांक output select - */
/* 00: VCO घातer, 01: dvdd_pdt, 10: dvdd, 11: vcox */

#घोषणा  MIPI_DIGITAL_PLL_7      0x2B
#घोषणा  MIPI_PLL_FORCE_N_EN     7
#घोषणा  MIPI_PLL_FORCE_BAND_EN  6

#घोषणा  MIPI_PLL_VCO_TUNE_REG   4
/* Bit[5:4]: VCO metal capacitance - */
/* 00: +20% fast, 01: +10% fast (शेष), 10: typical, 11: -10% slow */
#घोषणा  MIPI_PLL_VCO_TUNE_REG_VAL   0x30

#घोषणा  MIPI_PLL_PLL_LDO_BIT    2
/* Bit[3:2]: vco_v2i घातer - */
/* 00: 1.40V, 01: 1.45V (शेष), 10: 1.50V, 11: 1.55V */
#घोषणा  MIPI_PLL_RESET_N        0x02
#घोषणा  MIPI_FRQ_FORCE_NDET     0

#घोषणा  MIPI_ALERT_CLR_0        0x2D
#घोषणा  HS_link_error_clear     7
/* This bit itself is S/C, and it clears 0x84:0x31[7] */

#घोषणा  MIPI_ALERT_OUT_0        0x31
#घोषणा  check_sum_err_hs_sync   7
/* This bit is cleared by 0x84:0x2D[7] */

#घोषणा  MIPI_DIGITAL_PLL_8    0x33
#घोषणा  MIPI_POST_DIV_VAL     4
/* N means भागided by (n+1), n = 0~15 */
#घोषणा  MIPI_EN_LOCK_FRZ      3
#घोषणा  MIPI_FRQ_COUNTER_RST  2
#घोषणा  MIPI_FRQ_SET_REG_8    1
/* Bit 0 is reserved */

#घोषणा  MIPI_DIGITAL_PLL_9    0x34

#घोषणा  MIPI_DIGITAL_PLL_16   0x3B
#घोषणा  MIPI_FRQ_FREEZE_NDET          7
#घोषणा  MIPI_FRQ_REG_SET_ENABLE       6
#घोषणा  MIPI_REG_FORCE_SEL_EN         5
#घोषणा  MIPI_REG_SEL_DIV_REG          4
#घोषणा  MIPI_REG_FORCE_PRE_DIV_EN     3
/* Bit 2 is reserved */
#घोषणा  MIPI_FREF_D_IND               1
#घोषणा  REF_CLK_27000KHZ    1
#घोषणा  REF_CLK_19200KHZ    0
#घोषणा  MIPI_REG_PLL_PLL_TEST_ENABLE  0

#घोषणा  MIPI_DIGITAL_PLL_18  0x3D
#घोषणा  FRQ_COUNT_RB_SEL       7
#घोषणा  REG_FORCE_POST_DIV_EN  6
#घोषणा  MIPI_DPI_SELECT        5
#घोषणा  SELECT_DSI  1
#घोषणा  SELECT_DPI  0
#घोषणा  REG_BAUD_DIV_RATIO     0

#घोषणा  H_BLANK_L            0x3E
/* For DSC only */
#घोषणा  H_BLANK_H            0x3F
/* For DSC only; note: bit[7:6] are reserved */
#घोषणा  MIPI_SWAP  0x4A
#घोषणा  MIPI_SWAP_CH0    7
#घोषणा  MIPI_SWAP_CH1    6
#घोषणा  MIPI_SWAP_CH2    5
#घोषणा  MIPI_SWAP_CH3    4
#घोषणा  MIPI_SWAP_CLK    3
/* Bit[2:0] are reserved */

/******** END of I2C Address 0x84 *********/

/* DPCD regs */
#घोषणा DPCD_DPCD_REV                  0x00
#घोषणा DPCD_MAX_LINK_RATE             0x01
#घोषणा DPCD_MAX_LANE_COUNT            0x02

/*********  ANX7625 Register End  **********/

/***************** Display *****************/
क्रमागत audio_fs अणु
	AUDIO_FS_441K  = 0x00,
	AUDIO_FS_48K   = 0x02,
	AUDIO_FS_32K   = 0x03,
	AUDIO_FS_882K  = 0x08,
	AUDIO_FS_96K   = 0x0a,
	AUDIO_FS_1764K = 0x0c,
	AUDIO_FS_192K  = 0x0e
पूर्ण;

क्रमागत audio_wd_len अणु
	AUDIO_W_LEN_16_20MAX = 0x02,
	AUDIO_W_LEN_18_20MAX = 0x04,
	AUDIO_W_LEN_17_20MAX = 0x0c,
	AUDIO_W_LEN_19_20MAX = 0x08,
	AUDIO_W_LEN_20_20MAX = 0x0a,
	AUDIO_W_LEN_20_24MAX = 0x03,
	AUDIO_W_LEN_22_24MAX = 0x05,
	AUDIO_W_LEN_21_24MAX = 0x0d,
	AUDIO_W_LEN_23_24MAX = 0x09,
	AUDIO_W_LEN_24_24MAX = 0x0b
पूर्ण;

#घोषणा I2S_CH_2	0x01
#घोषणा TDM_CH_4	0x03
#घोषणा TDM_CH_6	0x05
#घोषणा TDM_CH_8	0x07

#घोषणा MAX_DPCD_BUFFER_SIZE	16

#घोषणा ONE_BLOCK_SIZE      128
#घोषणा FOUR_BLOCK_SIZE     (128 * 4)

#घोषणा MAX_EDID_BLOCK	3
#घोषणा EDID_TRY_CNT	3
#घोषणा SUPPORT_PIXEL_CLOCK	300000

काष्ठा s_edid_data अणु
	पूर्णांक edid_block_num;
	u8 edid_raw_data[FOUR_BLOCK_SIZE];
पूर्ण;

/***************** Display End *****************/

काष्ठा anx7625_platक्रमm_data अणु
	काष्ठा gpio_desc *gpio_p_on;
	काष्ठा gpio_desc *gpio_reset;
	काष्ठा regulator_bulk_data supplies[3];
	काष्ठा drm_bridge *panel_bridge;
	पूर्णांक पूर्णांकp_irq;
	u32 low_घातer_mode;
	काष्ठा device_node *mipi_host_node;
पूर्ण;

काष्ठा anx7625_i2c_client अणु
	काष्ठा i2c_client *tx_p0_client;
	काष्ठा i2c_client *tx_p1_client;
	काष्ठा i2c_client *tx_p2_client;
	काष्ठा i2c_client *rx_p0_client;
	काष्ठा i2c_client *rx_p1_client;
	काष्ठा i2c_client *rx_p2_client;
	काष्ठा i2c_client *tcpc_client;
पूर्ण;

काष्ठा anx7625_data अणु
	काष्ठा anx7625_platक्रमm_data pdata;
	atomic_t घातer_status;
	पूर्णांक hpd_status;
	पूर्णांक hpd_high_cnt;
	/* Lock क्रम work queue */
	काष्ठा mutex lock;
	काष्ठा i2c_client *client;
	काष्ठा anx7625_i2c_client i2c;
	काष्ठा i2c_client *last_client;
	काष्ठा s_edid_data slimport_edid_p;
	काष्ठा work_काष्ठा work;
	काष्ठा workqueue_काष्ठा *workqueue;
	अक्षर edid_block;
	काष्ठा display_timing dt;
	u8 display_timing_valid;
	काष्ठा drm_bridge bridge;
	u8 bridge_attached;
	काष्ठा mipi_dsi_device *dsi;
पूर्ण;

#पूर्ण_अगर  /* __ANX7625_H__ */
