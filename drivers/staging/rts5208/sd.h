<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#अगर_अघोषित __REALTEK_RTSX_SD_H
#घोषणा __REALTEK_RTSX_SD_H

#समावेश "rtsx_chip.h"

#घोषणा SUPPORT_VOLTAGE	0x003C0000

/* Error Code */
#घोषणा	SD_NO_ERROR		0x0
#घोषणा	SD_CRC_ERR		0x80
#घोषणा	SD_TO_ERR		0x40
#घोषणा	SD_NO_CARD		0x20
#घोषणा SD_BUSY			0x10
#घोषणा	SD_STS_ERR		0x08
#घोषणा SD_RSP_TIMEOUT		0x04
#घोषणा SD_IO_ERR		0x02

/* Return code क्रम MMC चयन bus */
#घोषणा SWITCH_SUCCESS		0
#घोषणा SWITCH_ERR		1
#घोषणा SWITCH_FAIL		2

/* MMC/SD Command Index */
/* Basic command (class 0) */
#घोषणा GO_IDLE_STATE		0
#घोषणा	SEND_OP_COND		1
#घोषणा	ALL_SEND_CID		2
#घोषणा	SET_RELATIVE_ADDR	3
#घोषणा	SEND_RELATIVE_ADDR	3
#घोषणा	SET_DSR			4
#घोषणा IO_SEND_OP_COND		5
#घोषणा	SWITCH			6
#घोषणा	SELECT_CARD		7
#घोषणा	DESELECT_CARD		7
/* CMD8 is "SEND_EXT_CSD" क्रम MMC4.x Spec
 * जबतक is "SEND_IF_COND" क्रम SD 2.0
 */
#घोषणा	SEND_EXT_CSD		8
#घोषणा	SEND_IF_COND		8

#घोषणा	SEND_CSD		9
#घोषणा	SEND_CID		10
#घोषणा	VOLTAGE_SWITCH		11
#घोषणा	READ_DAT_UTIL_STOP	11
#घोषणा	STOP_TRANSMISSION	12
#घोषणा	SEND_STATUS		13
#घोषणा	GO_INACTIVE_STATE	15

#घोषणा	SET_BLOCKLEN		16
#घोषणा	READ_SINGLE_BLOCK	17
#घोषणा	READ_MULTIPLE_BLOCK	18
#घोषणा	SEND_TUNING_PATTERN	19

#घोषणा	BUSTEST_R		14
#घोषणा	BUSTEST_W		19

#घोषणा	WRITE_BLOCK		24
#घोषणा	WRITE_MULTIPLE_BLOCK	25
#घोषणा	PROGRAM_CSD		27

#घोषणा	ERASE_WR_BLK_START	32
#घोषणा	ERASE_WR_BLK_END	33
#घोषणा	ERASE_CMD		38

#घोषणा LOCK_UNLOCK		42
#घोषणा	IO_RW_सूचीECT		52

#घोषणा	APP_CMD			55
#घोषणा	GEN_CMD			56

#घोषणा	SET_BUS_WIDTH		6
#घोषणा	SD_STATUS		13
#घोषणा	SEND_NUM_WR_BLOCKS	22
#घोषणा	SET_WR_BLK_ERASE_COUNT	23
#घोषणा	SD_APP_OP_COND		41
#घोषणा	SET_CLR_CARD_DETECT	42
#घोषणा	SEND_SCR		51

#घोषणा	SD_READ_COMPLETE	0x00
#घोषणा	SD_READ_TO		0x01
#घोषणा	SD_READ_ADVENCE		0x02

#घोषणा	SD_CHECK_MODE		0x00
#घोषणा	SD_SWITCH_MODE		0x80
#घोषणा	SD_FUNC_GROUP_1		0x01
#घोषणा	SD_FUNC_GROUP_2		0x02
#घोषणा	SD_FUNC_GROUP_3		0x03
#घोषणा	SD_FUNC_GROUP_4		0x04
#घोषणा	SD_CHECK_SPEC_V1_1	0xFF

#घोषणा	NO_ARGUMENT				0x00
#घोषणा	CHECK_PATTERN				0x000000AA
#घोषणा	VOLTAGE_SUPPLY_RANGE			0x00000100
#घोषणा	SUPPORT_HIGH_AND_EXTENDED_CAPACITY	0x40000000
#घोषणा	SUPPORT_MAX_POWER_PERMANCE		0x10000000
#घोषणा	SUPPORT_1V8				0x01000000

#घोषणा	SWITCH_NO_ERR		0x00
#घोषणा	CARD_NOT_EXIST		0x01
#घोषणा	SPEC_NOT_SUPPORT	0x02
#घोषणा	CHECK_MODE_ERR		0x03
#घोषणा	CHECK_NOT_READY		0x04
#घोषणा	SWITCH_CRC_ERR		0x05
#घोषणा	SWITCH_MODE_ERR		0x06
#घोषणा	SWITCH_PASS		0x07

#अगर_घोषित SUPPORT_SD_LOCK
#घोषणा SD_ERASE		0x08
#घोषणा SD_LOCK			0x04
#घोषणा SD_UNLOCK		0x00
#घोषणा SD_CLR_PWD		0x02
#घोषणा SD_SET_PWD		0x01

#घोषणा SD_PWD_LEN		0x10

#घोषणा SD_LOCKED		0x80
#घोषणा SD_LOCK_1BIT_MODE	0x40
#घोषणा SD_PWD_EXIST		0x20
#घोषणा SD_UNLOCK_POW_ON	0x01
#घोषणा SD_SDR_RST		0x02

#घोषणा SD_NOT_ERASE		0x00
#घोषणा SD_UNDER_ERASING	0x01
#घोषणा SD_COMPLETE_ERASE	0x02

#घोषणा SD_RW_FORBIDDEN		0x0F

#पूर्ण_अगर

#घोषणा	HS_SUPPORT			0x01
#घोषणा	SDR50_SUPPORT			0x02
#घोषणा	SDR104_SUPPORT			0x03
#घोषणा	DDR50_SUPPORT			0x04

#घोषणा	HS_SUPPORT_MASK			0x02
#घोषणा	SDR50_SUPPORT_MASK		0x04
#घोषणा	SDR104_SUPPORT_MASK		0x08
#घोषणा	DDR50_SUPPORT_MASK		0x10

#घोषणा	HS_QUERY_SWITCH_OK		0x01
#घोषणा	SDR50_QUERY_SWITCH_OK		0x02
#घोषणा	SDR104_QUERY_SWITCH_OK		0x03
#घोषणा	DDR50_QUERY_SWITCH_OK		0x04

#घोषणा	HS_SWITCH_BUSY			0x02
#घोषणा	SDR50_SWITCH_BUSY		0x04
#घोषणा	SDR104_SWITCH_BUSY		0x08
#घोषणा	DDR50_SWITCH_BUSY		0x10

#घोषणा	FUNCTION_GROUP1_SUPPORT_OFFSET       0x0D
#घोषणा FUNCTION_GROUP1_QUERY_SWITCH_OFFSET  0x10
#घोषणा FUNCTION_GROUP1_CHECK_BUSY_OFFSET    0x1D

#घोषणा	DRIVING_TYPE_A		0x01
#घोषणा	DRIVING_TYPE_B		    0x00
#घोषणा	DRIVING_TYPE_C		    0x02
#घोषणा	DRIVING_TYPE_D		0x03

#घोषणा	DRIVING_TYPE_A_MASK	    0x02
#घोषणा	DRIVING_TYPE_B_MASK	    0x01
#घोषणा	DRIVING_TYPE_C_MASK	    0x04
#घोषणा	DRIVING_TYPE_D_MASK	    0x08

#घोषणा	TYPE_A_QUERY_SWITCH_OK	0x01
#घोषणा	TYPE_B_QUERY_SWITCH_OK	0x00
#घोषणा	TYPE_C_QUERY_SWITCH_OK  0x02
#घोषणा	TYPE_D_QUERY_SWITCH_OK  0x03

#घोषणा	TYPE_A_SWITCH_BUSY	    0x02
#घोषणा	TYPE_B_SWITCH_BUSY	    0x01
#घोषणा	TYPE_C_SWITCH_BUSY      0x04
#घोषणा	TYPE_D_SWITCH_BUSY      0x08

#घोषणा	FUNCTION_GROUP3_SUPPORT_OFFSET       0x09
#घोषणा FUNCTION_GROUP3_QUERY_SWITCH_OFFSET  0x0F
#घोषणा FUNCTION_GROUP3_CHECK_BUSY_OFFSET    0x19

#घोषणा	CURRENT_LIMIT_200	    0x00
#घोषणा	CURRENT_LIMIT_400	    0x01
#घोषणा	CURRENT_LIMIT_600	    0x02
#घोषणा	CURRENT_LIMIT_800	    0x03

#घोषणा	CURRENT_LIMIT_200_MASK	0x01
#घोषणा	CURRENT_LIMIT_400_MASK	0x02
#घोषणा	CURRENT_LIMIT_600_MASK	0x04
#घोषणा	CURRENT_LIMIT_800_MASK	0x08

#घोषणा	CURRENT_LIMIT_200_QUERY_SWITCH_OK    0x00
#घोषणा	CURRENT_LIMIT_400_QUERY_SWITCH_OK    0x01
#घोषणा	CURRENT_LIMIT_600_QUERY_SWITCH_OK    0x02
#घोषणा	CURRENT_LIMIT_800_QUERY_SWITCH_OK    0x03

#घोषणा	CURRENT_LIMIT_200_SWITCH_BUSY        0x01
#घोषणा	CURRENT_LIMIT_400_SWITCH_BUSY	     0x02
#घोषणा	CURRENT_LIMIT_600_SWITCH_BUSY        0x04
#घोषणा	CURRENT_LIMIT_800_SWITCH_BUSY        0x08

#घोषणा	FUNCTION_GROUP4_SUPPORT_OFFSET       0x07
#घोषणा FUNCTION_GROUP4_QUERY_SWITCH_OFFSET  0x0F
#घोषणा FUNCTION_GROUP4_CHECK_BUSY_OFFSET    0x17

#घोषणा	DATA_STRUCTURE_VER_OFFSET	0x11

#घोषणा MAX_PHASE			31

#घोषणा MMC_8BIT_BUS			0x0010
#घोषणा MMC_4BIT_BUS			0x0020

#घोषणा MMC_SWITCH_ERR			0x80

#घोषणा SD_IO_3V3		0
#घोषणा SD_IO_1V8		1

#घोषणा TUNE_TX    0x00
#घोषणा TUNE_RX	   0x01

#घोषणा CHANGE_TX  0x00
#घोषणा CHANGE_RX  0x01

#घोषणा DCM_HIGH_FREQUENCY_MODE  0x00
#घोषणा DCM_LOW_FREQUENCY_MODE   0x01

#घोषणा DCM_HIGH_FREQUENCY_MODE_SET  0x0C
#घोषणा DCM_LOW_FREQUENCY_MODE_SET   0x00

#घोषणा MULTIPLY_BY_1    0x00
#घोषणा MULTIPLY_BY_2    0x01
#घोषणा MULTIPLY_BY_3    0x02
#घोषणा MULTIPLY_BY_4    0x03
#घोषणा MULTIPLY_BY_5    0x04
#घोषणा MULTIPLY_BY_6    0x05
#घोषणा MULTIPLY_BY_7    0x06
#घोषणा MULTIPLY_BY_8    0x07
#घोषणा MULTIPLY_BY_9    0x08
#घोषणा MULTIPLY_BY_10   0x09

#घोषणा DIVIDE_BY_2      0x01
#घोषणा DIVIDE_BY_3      0x02
#घोषणा DIVIDE_BY_4      0x03
#घोषणा DIVIDE_BY_5      0x04
#घोषणा DIVIDE_BY_6      0x05
#घोषणा DIVIDE_BY_7      0x06
#घोषणा DIVIDE_BY_8      0x07
#घोषणा DIVIDE_BY_9      0x08
#घोषणा DIVIDE_BY_10     0x09

काष्ठा timing_phase_path अणु
	पूर्णांक start;
	पूर्णांक end;
	पूर्णांक mid;
	पूर्णांक len;
पूर्ण;

पूर्णांक sd_select_card(काष्ठा rtsx_chip *chip, पूर्णांक select);
पूर्णांक sd_pull_ctl_enable(काष्ठा rtsx_chip *chip);
पूर्णांक reset_sd_card(काष्ठा rtsx_chip *chip);
पूर्णांक sd_चयन_घड़ी(काष्ठा rtsx_chip *chip);
व्योम sd_stop_seq_mode(काष्ठा rtsx_chip *chip);
पूर्णांक sd_rw(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
	  u32 start_sector, u16 sector_cnt);
व्योम sd_cleanup_work(काष्ठा rtsx_chip *chip);
पूर्णांक sd_घातer_off_card3v3(काष्ठा rtsx_chip *chip);
पूर्णांक release_sd_card(काष्ठा rtsx_chip *chip);
#अगर_घोषित SUPPORT_CPRM
पूर्णांक ext_sd_send_cmd_get_rsp(काष्ठा rtsx_chip *chip, u8 cmd_idx,
			    u32 arg, u8 rsp_type, u8 *rsp, पूर्णांक rsp_len,
			    bool special_check);
पूर्णांक ext_sd_get_rsp(काष्ठा rtsx_chip *chip, पूर्णांक len, u8 *rsp, u8 rsp_type);

पूर्णांक sd_pass_thru_mode(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक sd_execute_no_data(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक sd_execute_पढ़ो_data(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक sd_execute_ग_लिखो_data(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक sd_get_cmd_rsp(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक sd_hw_rst(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
#पूर्ण_अगर

#पूर्ण_अगर  /* __REALTEK_RTSX_SD_H */
