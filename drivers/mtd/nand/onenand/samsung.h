<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2008-2010 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 */
#अगर_अघोषित __SAMSUNG_ONEन_अंकD_H__
#घोषणा __SAMSUNG_ONEन_अंकD_H__

/*
 * Oneन_अंकD Controller
 */
#घोषणा MEM_CFG_OFFSET		0x0000
#घोषणा BURST_LEN_OFFSET	0x0010
#घोषणा MEM_RESET_OFFSET	0x0020
#घोषणा INT_ERR_STAT_OFFSET	0x0030
#घोषणा INT_ERR_MASK_OFFSET	0x0040
#घोषणा INT_ERR_ACK_OFFSET	0x0050
#घोषणा ECC_ERR_STAT_OFFSET	0x0060
#घोषणा MANUFACT_ID_OFFSET	0x0070
#घोषणा DEVICE_ID_OFFSET	0x0080
#घोषणा DATA_BUF_SIZE_OFFSET	0x0090
#घोषणा BOOT_BUF_SIZE_OFFSET	0x00A0
#घोषणा BUF_AMOUNT_OFFSET	0x00B0
#घोषणा TECH_OFFSET		0x00C0
#घोषणा FBA_WIDTH_OFFSET	0x00D0
#घोषणा FPA_WIDTH_OFFSET	0x00E0
#घोषणा FSA_WIDTH_OFFSET	0x00F0
#घोषणा TRANS_SPARE_OFFSET	0x0140
#घोषणा DBS_DFS_WIDTH_OFFSET	0x0160
#घोषणा INT_PIN_ENABLE_OFFSET	0x01A0
#घोषणा ACC_CLOCK_OFFSET	0x01C0
#घोषणा FLASH_VER_ID_OFFSET	0x01F0
#घोषणा FLASH_AUX_CNTRL_OFFSET	0x0300		/* s3c64xx only */

#घोषणा ONEन_अंकD_MEM_RESET_HOT	0x3
#घोषणा ONEन_अंकD_MEM_RESET_COLD	0x2
#घोषणा ONEन_अंकD_MEM_RESET_WARM	0x1

#घोषणा CACHE_OP_ERR		(1 << 13)
#घोषणा RST_CMP			(1 << 12)
#घोषणा RDY_ACT			(1 << 11)
#घोषणा INT_ACT			(1 << 10)
#घोषणा UNSUP_CMD		(1 << 9)
#घोषणा LOCKED_BLK		(1 << 8)
#घोषणा BLK_RW_CMP		(1 << 7)
#घोषणा ERS_CMP			(1 << 6)
#घोषणा PGM_CMP			(1 << 5)
#घोषणा LOAD_CMP		(1 << 4)
#घोषणा ERS_FAIL		(1 << 3)
#घोषणा PGM_FAIL		(1 << 2)
#घोषणा INT_TO			(1 << 1)
#घोषणा LD_FAIL_ECC_ERR		(1 << 0)

#घोषणा TSRF			(1 << 0)

#पूर्ण_अगर
