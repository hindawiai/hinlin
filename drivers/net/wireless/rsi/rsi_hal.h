<शैली गुरु>
/*
 * Copyright (c) 2017 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __RSI_HAL_H__
#घोषणा __RSI_HAL_H__

/* Device Operating modes */
#घोषणा DEV_OPMODE_WIFI_ALONE		1
#घोषणा DEV_OPMODE_BT_ALONE		4
#घोषणा DEV_OPMODE_BT_LE_ALONE		8
#घोषणा DEV_OPMODE_BT_DUAL		12
#घोषणा DEV_OPMODE_STA_BT		5
#घोषणा DEV_OPMODE_STA_BT_LE		9
#घोषणा DEV_OPMODE_STA_BT_DUAL		13
#घोषणा DEV_OPMODE_AP_BT		6
#घोषणा DEV_OPMODE_AP_BT_DUAL		14

#घोषणा FLASH_WRITE_CHUNK_SIZE		(4 * 1024)
#घोषणा FLASH_SECTOR_SIZE		(4 * 1024)

#घोषणा FLASH_SIZE_ADDR			0x04000016
#घोषणा PING_BUFFER_ADDRESS		0x19000
#घोषणा PONG_BUFFER_ADDRESS		0x1a000
#घोषणा SWBL_REGIN			0x41050034
#घोषणा SWBL_REGOUT			0x4105003c
#घोषणा PING_WRITE			0x1
#घोषणा PONG_WRITE			0x2

#घोषणा BL_CMD_TIMEOUT			2000
#घोषणा BL_BURN_TIMEOUT			(50 * 1000)

#घोषणा REGIN_VALID			0xA
#घोषणा REGIN_INPUT			0xA0
#घोषणा REGOUT_VALID			0xAB
#घोषणा REGOUT_INVALID			(~0xAB)
#घोषणा CMD_PASS			0xAA
#घोषणा CMD_FAIL			0xCC

#घोषणा LOAD_HOSTED_FW			'A'
#घोषणा BURN_HOSTED_FW			'B'
#घोषणा PING_VALID			'I'
#घोषणा PONG_VALID			'O'
#घोषणा PING_AVAIL			'I'
#घोषणा PONG_AVAIL			'O'
#घोषणा खातापूर्ण_REACHED			'E'
#घोषणा CHECK_CRC			'K'
#घोषणा POLLING_MODE			'P'
#घोषणा CONFIG_AUTO_READ_MODE		'R'
#घोषणा JUMP_TO_ZERO_PC			'J'
#घोषणा FW_LOADING_SUCCESSFUL		'S'
#घोषणा LOADING_INITIATED		'1'

#घोषणा RSI_ULP_RESET_REG		0x161
#घोषणा RSI_WATCH_DOG_TIMER_1		0x16c
#घोषणा RSI_WATCH_DOG_TIMER_2		0x16d
#घोषणा RSI_WATCH_DOG_DELAY_TIMER_1		0x16e
#घोषणा RSI_WATCH_DOG_DELAY_TIMER_2		0x16f
#घोषणा RSI_WATCH_DOG_TIMER_ENABLE		0x170

/* Watchकरोg समयr addresses क्रम 9116 */
#घोषणा NWP_AHB_BASE_ADDR		0x41300000
#घोषणा NWP_WWD_INTERRUPT_TIMER		(NWP_AHB_BASE_ADDR + 0x300)
#घोषणा NWP_WWD_SYSTEM_RESET_TIMER	(NWP_AHB_BASE_ADDR + 0x304)
#घोषणा NWP_WWD_WINDOW_TIMER		(NWP_AHB_BASE_ADDR + 0x308)
#घोषणा NWP_WWD_TIMER_SETTINGS		(NWP_AHB_BASE_ADDR + 0x30C)
#घोषणा NWP_WWD_MODE_AND_RSTART		(NWP_AHB_BASE_ADDR + 0x310)
#घोषणा NWP_WWD_RESET_BYPASS		(NWP_AHB_BASE_ADDR + 0x314)
#घोषणा NWP_FSM_INTR_MASK_REG		(NWP_AHB_BASE_ADDR + 0x104)

/* Watchकरोg समयr values */
#घोषणा NWP_WWD_INT_TIMER_CLKS		5
#घोषणा NWP_WWD_SYS_RESET_TIMER_CLKS	4
#घोषणा NWP_WWD_TIMER_DISABLE		0xAA0001

#घोषणा RSI_ULP_WRITE_0			00
#घोषणा RSI_ULP_WRITE_2			02
#घोषणा RSI_ULP_WRITE_50		50

#घोषणा RSI_RESTART_WDT			BIT(11)
#घोषणा RSI_BYPASS_ULP_ON_WDT		BIT(1)

#घोषणा RSI_ULP_TIMER_ENABLE		((0xaa000) | RSI_RESTART_WDT |	\
					 RSI_BYPASS_ULP_ON_WDT)
#घोषणा RSI_RF_SPI_PROG_REG_BASE_ADDR	0x40080000

#घोषणा RSI_GSPI_CTRL_REG0		(RSI_RF_SPI_PROG_REG_BASE_ADDR)
#घोषणा RSI_GSPI_CTRL_REG1		(RSI_RF_SPI_PROG_REG_BASE_ADDR + 0x2)
#घोषणा RSI_GSPI_DATA_REG0		(RSI_RF_SPI_PROG_REG_BASE_ADDR + 0x4)
#घोषणा RSI_GSPI_DATA_REG1		(RSI_RF_SPI_PROG_REG_BASE_ADDR + 0x6)
#घोषणा RSI_GSPI_DATA_REG2		(RSI_RF_SPI_PROG_REG_BASE_ADDR + 0x8)

#घोषणा RSI_GSPI_CTRL_REG0_VALUE		0x340

#घोषणा RSI_GSPI_DMA_MODE			BIT(13)

#घोषणा RSI_GSPI_2_ULP			BIT(12)
#घोषणा RSI_GSPI_TRIG			BIT(7)
#घोषणा RSI_GSPI_READ			BIT(6)
#घोषणा RSI_GSPI_RF_SPI_ACTIVE		BIT(8)

/* Boot loader commands */
#घोषणा SEND_RPS_खाता			'2'

#घोषणा FW_IMAGE_MIN_ADDRESS		(68 * 1024)
#घोषणा MAX_FLASH_खाता_SIZE		(400 * 1024) //400K
#घोषणा FLASH_START_ADDRESS		16

#घोषणा COMMON_HAL_CARD_READY_IND	0x0

#घोषणा COMMAN_HAL_WAIT_FOR_CARD_READY	1

#घोषणा RSI_DEV_OPMODE_WIFI_ALONE	1
#घोषणा RSI_DEV_COEX_MODE_WIFI_ALONE	1

#घोषणा BBP_INFO_40MHZ 0x6

#घोषणा FW_FLASH_OFFSET			0x820
#घोषणा LMAC_VER_OFFSET_9113		(FW_FLASH_OFFSET + 0x200)
#घोषणा LMAC_VER_OFFSET_9116		0x22C2
#घोषणा MAX_DWORD_ALIGN_BYTES		64
#घोषणा RSI_COMMON_REG_SIZE		2
#घोषणा RSI_9116_REG_SIZE		4
#घोषणा FW_ALIGN_SIZE			4
#घोषणा RSI_9116_FW_MAGIC_WORD		0x5aa5

#घोषणा MEM_ACCESS_CTRL_FROM_HOST	0x41300000
#घोषणा RAM_384K_ACCESS_FROM_TA		(BIT(2) | BIT(3) | BIT(4) | BIT(5) | \
					 BIT(20) | BIT(21) | BIT(22) | \
					 BIT(23) | BIT(24) | BIT(25))

काष्ठा bl_header अणु
	__le32 flags;
	__le32 image_no;
	__le32 check_sum;
	__le32 flash_start_address;
	__le32 flash_len;
पूर्ण __packed;

काष्ठा ta_metadata अणु
	अक्षर *name;
	अचिन्हित पूर्णांक address;
पूर्ण;

#घोषणा RSI_BL_CTRL_LEN_MASK			0xFFFFFF
#घोषणा RSI_BL_CTRL_SPI_32BIT_MODE		BIT(27)
#घोषणा RSI_BL_CTRL_REL_TA_SOFTRESET		BIT(28)
#घोषणा RSI_BL_CTRL_START_FROM_ROM_PC		BIT(29)
#घोषणा RSI_BL_CTRL_SPI_8BIT_MODE		BIT(30)
#घोषणा RSI_BL_CTRL_LAST_ENTRY			BIT(31)
काष्ठा bootload_entry अणु
	__le32 control;
	__le32 dst_addr;
पूर्ण __packed;

काष्ठा bootload_ds अणु
	__le16 fixed_pattern;
	__le16 offset;
	__le32 reserved;
	काष्ठा bootload_entry bl_entry[7];
पूर्ण __packed;

काष्ठा rsi_mgmt_desc अणु
	__le16 len_qno;
	u8 frame_type;
	u8 misc_flags;
	u8 xtend_desc_size;
	u8 header_len;
	__le16 frame_info;
	__le16 rate_info;
	__le16 bbp_info;
	__le16 seq_ctrl;
	u8 reserved2;
	u8 sta_id;
पूर्ण __packed;

काष्ठा rsi_data_desc अणु
	__le16 len_qno;
	u8 cfm_frame_type;
	u8 misc_flags;
	u8 xtend_desc_size;
	u8 header_len;
	__le16 frame_info;
	__le16 rate_info;
	__le16 bbp_info;
	__le16 mac_flags;
	u8 qid_tid;
	u8 sta_id;
पूर्ण __packed;

काष्ठा rsi_bt_desc अणु
	__le16 len_qno;
	__le16 reserved1;
	__le32 reserved2;
	__le32 reserved3;
	__le16 reserved4;
	__le16 bt_pkt_type;
पूर्ण __packed;

पूर्णांक rsi_hal_device_init(काष्ठा rsi_hw *adapter);
पूर्णांक rsi_prepare_mgmt_desc(काष्ठा rsi_common *common, काष्ठा sk_buff *skb);
पूर्णांक rsi_prepare_data_desc(काष्ठा rsi_common *common, काष्ठा sk_buff *skb);
पूर्णांक rsi_prepare_beacon(काष्ठा rsi_common *common, काष्ठा sk_buff *skb);
पूर्णांक rsi_send_pkt_to_bus(काष्ठा rsi_common *common, काष्ठा sk_buff *skb);
पूर्णांक rsi_send_bt_pkt(काष्ठा rsi_common *common, काष्ठा sk_buff *skb);

#पूर्ण_अगर
