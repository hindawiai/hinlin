<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#अगर_अघोषित __HW_H__
#घोषणा __HW_H__

#समावेश <linux/seq_file.h>

#समावेश "viamode.h"
#समावेश "global.h"
#समावेश "via_modesetting.h"

#घोषणा viafb_पढ़ो_reg(p, i)			via_पढ़ो_reg(p, i)
#घोषणा viafb_ग_लिखो_reg(i, p, d)		via_ग_लिखो_reg(p, i, d)
#घोषणा viafb_ग_लिखो_reg_mask(i, p, d, m)	via_ग_लिखो_reg_mask(p, i, d, m)

/* VIA output devices */
#घोषणा VIA_LDVP0	0x00000001
#घोषणा VIA_LDVP1	0x00000002
#घोषणा VIA_DVP0	0x00000004
#घोषणा VIA_CRT		0x00000010
#घोषणा VIA_DVP1	0x00000020
#घोषणा VIA_LVDS1	0x00000040
#घोषणा VIA_LVDS2	0x00000080

/* VIA output device घातer states */
#घोषणा VIA_STATE_ON		0
#घोषणा VIA_STATE_STANDBY	1
#घोषणा VIA_STATE_SUSPEND	2
#घोषणा VIA_STATE_OFF		3

/* VIA output device sync polarity */
#घोषणा VIA_HSYNC_NEGATIVE	0x01
#घोषणा VIA_VSYNC_NEGATIVE	0x02

/**********************************************************/
/* Definition IGA2 Design Method of CRTC Shaकरोw Registers */
/**********************************************************/
#घोषणा IGA2_HOR_TOTAL_SHADOW_FORMULA(x)           ((x/8)-5)
#घोषणा IGA2_HOR_BLANK_END_SHADOW_FORMULA(x, y)     (((x+y)/8)-1)
#घोषणा IGA2_VER_TOTAL_SHADOW_FORMULA(x)           ((x)-2)
#घोषणा IGA2_VER_ADDR_SHADOW_FORMULA(x)            ((x)-1)
#घोषणा IGA2_VER_BLANK_START_SHADOW_FORMULA(x)     ((x)-1)
#घोषणा IGA2_VER_BLANK_END_SHADOW_FORMULA(x, y)     ((x+y)-1)
#घोषणा IGA2_VER_SYNC_START_SHADOW_FORMULA(x)      (x)
#घोषणा IGA2_VER_SYNC_END_SHADOW_FORMULA(x, y)      (x+y)

/* Define Register Number क्रम IGA2 Shaकरोw CRTC Timing */

/* location: अणुCR6D,0,7पूर्ण,अणुCR71,3,3पूर्ण */
#घोषणा IGA2_SHADOW_HOR_TOTAL_REG_NUM       2
/* location: अणुCR6E,0,7पूर्ण */
#घोषणा IGA2_SHADOW_HOR_BLANK_END_REG_NUM   1
/* location: अणुCR6F,0,7पूर्ण,अणुCR71,0,2पूर्ण */
#घोषणा IGA2_SHADOW_VER_TOTAL_REG_NUM       2
/* location: अणुCR70,0,7पूर्ण,अणुCR71,4,6पूर्ण */
#घोषणा IGA2_SHADOW_VER_ADDR_REG_NUM        2
/* location: अणुCR72,0,7पूर्ण,अणुCR74,4,6पूर्ण */
#घोषणा IGA2_SHADOW_VER_BLANK_START_REG_NUM 2
/* location: अणुCR73,0,7पूर्ण,अणुCR74,0,2पूर्ण */
#घोषणा IGA2_SHADOW_VER_BLANK_END_REG_NUM   2
/* location: अणुCR75,0,7पूर्ण,अणुCR76,4,6पूर्ण */
#घोषणा IGA2_SHADOW_VER_SYNC_START_REG_NUM  2
/* location: अणुCR76,0,3पूर्ण */
#घोषणा IGA2_SHADOW_VER_SYNC_END_REG_NUM    1

/* Define Fetch Count Register*/

/* location: अणुSR1C,0,7पूर्ण,अणुSR1D,0,1पूर्ण */
#घोषणा IGA1_FETCH_COUNT_REG_NUM        2
/* 16 bytes alignment. */
#घोषणा IGA1_FETCH_COUNT_ALIGN_BYTE     16
/* x: H resolution, y: color depth */
#घोषणा IGA1_FETCH_COUNT_PATCH_VALUE    4
#घोषणा IGA1_FETCH_COUNT_FORMULA(x, y)   \
	(((x*y)/IGA1_FETCH_COUNT_ALIGN_BYTE) + IGA1_FETCH_COUNT_PATCH_VALUE)

/* location: अणुCR65,0,7पूर्ण,अणुCR67,2,3पूर्ण */
#घोषणा IGA2_FETCH_COUNT_REG_NUM        2
#घोषणा IGA2_FETCH_COUNT_ALIGN_BYTE     16
#घोषणा IGA2_FETCH_COUNT_PATCH_VALUE    0
#घोषणा IGA2_FETCH_COUNT_FORMULA(x, y)   \
	(((x*y)/IGA2_FETCH_COUNT_ALIGN_BYTE) + IGA2_FETCH_COUNT_PATCH_VALUE)

/* Staring Address*/

/* location: अणुCR0C,0,7पूर्ण,अणुCR0D,0,7पूर्ण,अणुCR34,0,7पूर्ण,अणुCR48,0,1पूर्ण */
#घोषणा IGA1_STARTING_ADDR_REG_NUM      4
/* location: अणुCR62,1,7पूर्ण,अणुCR63,0,7पूर्ण,अणुCR64,0,7पूर्ण */
#घोषणा IGA2_STARTING_ADDR_REG_NUM      3

/* Define Display OFFSET*/
/* These value are by HW suggested value*/
/* location: अणुSR17,0,7पूर्ण */
#घोषणा K800_IGA1_FIFO_MAX_DEPTH                384
/* location: अणुSR16,0,5पूर्ण,अणुSR16,7,7पूर्ण */
#घोषणा K800_IGA1_FIFO_THRESHOLD                328
/* location: अणुSR18,0,5पूर्ण,अणुSR18,7,7पूर्ण */
#घोषणा K800_IGA1_FIFO_HIGH_THRESHOLD           296
/* location: अणुSR22,0,4पूर्ण. (128/4) =64, K800 must be set zero, */
				/* because HW only 5 bits */
#घोषणा K800_IGA1_DISPLAY_QUEUE_EXPIRE_NUM      0

/* location: अणुCR68,4,7पूर्ण,अणुCR94,7,7पूर्ण,अणुCR95,7,7पूर्ण */
#घोषणा K800_IGA2_FIFO_MAX_DEPTH                384
/* location: अणुCR68,0,3पूर्ण,अणुCR95,4,6पूर्ण */
#घोषणा K800_IGA2_FIFO_THRESHOLD                328
/* location: अणुCR92,0,3पूर्ण,अणुCR95,0,2पूर्ण */
#घोषणा K800_IGA2_FIFO_HIGH_THRESHOLD           296
/* location: अणुCR94,0,6पूर्ण */
#घोषणा K800_IGA2_DISPLAY_QUEUE_EXPIRE_NUM      128

/* location: अणुSR17,0,7पूर्ण */
#घोषणा P880_IGA1_FIFO_MAX_DEPTH                192
/* location: अणुSR16,0,5पूर्ण,अणुSR16,7,7पूर्ण */
#घोषणा P880_IGA1_FIFO_THRESHOLD                128
/* location: अणुSR18,0,5पूर्ण,अणुSR18,7,7पूर्ण */
#घोषणा P880_IGA1_FIFO_HIGH_THRESHOLD           64
/* location: अणुSR22,0,4पूर्ण. (128/4) =64, K800 must be set zero, */
				/* because HW only 5 bits */
#घोषणा P880_IGA1_DISPLAY_QUEUE_EXPIRE_NUM      0

/* location: अणुCR68,4,7पूर्ण,अणुCR94,7,7पूर्ण,अणुCR95,7,7पूर्ण */
#घोषणा P880_IGA2_FIFO_MAX_DEPTH                96
/* location: अणुCR68,0,3पूर्ण,अणुCR95,4,6पूर्ण */
#घोषणा P880_IGA2_FIFO_THRESHOLD                64
/* location: अणुCR92,0,3पूर्ण,अणुCR95,0,2पूर्ण */
#घोषणा P880_IGA2_FIFO_HIGH_THRESHOLD           32
/* location: अणुCR94,0,6पूर्ण */
#घोषणा P880_IGA2_DISPLAY_QUEUE_EXPIRE_NUM      128

/* VT3314 chipset*/

/* location: अणुSR17,0,7पूर्ण */
#घोषणा CN700_IGA1_FIFO_MAX_DEPTH               96
/* location: अणुSR16,0,5पूर्ण,अणुSR16,7,7पूर्ण */
#घोषणा CN700_IGA1_FIFO_THRESHOLD               80
/* location: अणुSR18,0,5पूर्ण,अणुSR18,7,7पूर्ण */
#घोषणा CN700_IGA1_FIFO_HIGH_THRESHOLD          64
/* location: अणुSR22,0,4पूर्ण. (128/4) =64, P800 must be set zero,
				because HW only 5 bits */
#घोषणा CN700_IGA1_DISPLAY_QUEUE_EXPIRE_NUM     0
/* location: अणुCR68,4,7पूर्ण,अणुCR94,7,7पूर्ण,अणुCR95,7,7पूर्ण */
#घोषणा CN700_IGA2_FIFO_MAX_DEPTH               96
/* location: अणुCR68,0,3पूर्ण,अणुCR95,4,6पूर्ण */
#घोषणा CN700_IGA2_FIFO_THRESHOLD               80
/* location: अणुCR92,0,3पूर्ण,अणुCR95,0,2पूर्ण */
#घोषणा CN700_IGA2_FIFO_HIGH_THRESHOLD          32
/* location: अणुCR94,0,6पूर्ण */
#घोषणा CN700_IGA2_DISPLAY_QUEUE_EXPIRE_NUM     128

/* For VT3324, these values are suggested by HW */
/* location: अणुSR17,0,7पूर्ण */
#घोषणा CX700_IGA1_FIFO_MAX_DEPTH               192
/* location: अणुSR16,0,5पूर्ण,अणुSR16,7,7पूर्ण */
#घोषणा CX700_IGA1_FIFO_THRESHOLD               128
/* location: अणुSR18,0,5पूर्ण,अणुSR18,7,7पूर्ण */
#घोषणा CX700_IGA1_FIFO_HIGH_THRESHOLD          128
/* location: अणुSR22,0,4पूर्ण */
#घोषणा CX700_IGA1_DISPLAY_QUEUE_EXPIRE_NUM     124

/* location: अणुCR68,4,7पूर्ण,अणुCR94,7,7पूर्ण,अणुCR95,7,7पूर्ण */
#घोषणा CX700_IGA2_FIFO_MAX_DEPTH               96
/* location: अणुCR68,0,3पूर्ण,अणुCR95,4,6पूर्ण */
#घोषणा CX700_IGA2_FIFO_THRESHOLD               64
/* location: अणुCR92,0,3पूर्ण,अणुCR95,0,2पूर्ण */
#घोषणा CX700_IGA2_FIFO_HIGH_THRESHOLD          32
/* location: अणुCR94,0,6पूर्ण */
#घोषणा CX700_IGA2_DISPLAY_QUEUE_EXPIRE_NUM     128

/* VT3336 chipset*/
/* location: अणुSR17,0,7पूर्ण */
#घोषणा K8M890_IGA1_FIFO_MAX_DEPTH               360
/* location: अणुSR16,0,5पूर्ण,अणुSR16,7,7पूर्ण */
#घोषणा K8M890_IGA1_FIFO_THRESHOLD               328
/* location: अणुSR18,0,5पूर्ण,अणुSR18,7,7पूर्ण */
#घोषणा K8M890_IGA1_FIFO_HIGH_THRESHOLD          296
/* location: अणुSR22,0,4पूर्ण. */
#घोषणा K8M890_IGA1_DISPLAY_QUEUE_EXPIRE_NUM     124

/* location: अणुCR68,4,7पूर्ण,अणुCR94,7,7पूर्ण,अणुCR95,7,7पूर्ण */
#घोषणा K8M890_IGA2_FIFO_MAX_DEPTH               360
/* location: अणुCR68,0,3पूर्ण,अणुCR95,4,6पूर्ण */
#घोषणा K8M890_IGA2_FIFO_THRESHOLD               328
/* location: अणुCR92,0,3पूर्ण,अणुCR95,0,2पूर्ण */
#घोषणा K8M890_IGA2_FIFO_HIGH_THRESHOLD          296
/* location: अणुCR94,0,6पूर्ण */
#घोषणा K8M890_IGA2_DISPLAY_QUEUE_EXPIRE_NUM     124

/* VT3327 chipset*/
/* location: अणुSR17,0,7पूर्ण */
#घोषणा P4M890_IGA1_FIFO_MAX_DEPTH               96
/* location: अणुSR16,0,5पूर्ण,अणुSR16,7,7पूर्ण */
#घोषणा P4M890_IGA1_FIFO_THRESHOLD               76
/* location: अणुSR18,0,5पूर्ण,अणुSR18,7,7पूर्ण */
#घोषणा P4M890_IGA1_FIFO_HIGH_THRESHOLD          64
/* location: अणुSR22,0,4पूर्ण. (32/4) =8 */
#घोषणा P4M890_IGA1_DISPLAY_QUEUE_EXPIRE_NUM     32
/* location: अणुCR68,4,7पूर्ण,अणुCR94,7,7पूर्ण,अणुCR95,7,7पूर्ण */
#घोषणा P4M890_IGA2_FIFO_MAX_DEPTH               96
/* location: अणुCR68,0,3पूर्ण,अणुCR95,4,6पूर्ण */
#घोषणा P4M890_IGA2_FIFO_THRESHOLD               76
/* location: अणुCR92,0,3पूर्ण,अणुCR95,0,2पूर्ण */
#घोषणा P4M890_IGA2_FIFO_HIGH_THRESHOLD          64
/* location: अणुCR94,0,6पूर्ण */
#घोषणा P4M890_IGA2_DISPLAY_QUEUE_EXPIRE_NUM     32

/* VT3364 chipset*/
/* location: अणुSR17,0,7पूर्ण */
#घोषणा P4M900_IGA1_FIFO_MAX_DEPTH               96
/* location: अणुSR16,0,5पूर्ण,अणुSR16,7,7पूर्ण */
#घोषणा P4M900_IGA1_FIFO_THRESHOLD               76
/* location: अणुSR18,0,5पूर्ण,अणुSR18,7,7पूर्ण */
#घोषणा P4M900_IGA1_FIFO_HIGH_THRESHOLD          76
/* location: अणुSR22,0,4पूर्ण. */
#घोषणा P4M900_IGA1_DISPLAY_QUEUE_EXPIRE_NUM     32
/* location: अणुCR68,4,7पूर्ण,अणुCR94,7,7पूर्ण,अणुCR95,7,7पूर्ण */
#घोषणा P4M900_IGA2_FIFO_MAX_DEPTH               96
/* location: अणुCR68,0,3पूर्ण,अणुCR95,4,6पूर्ण */
#घोषणा P4M900_IGA2_FIFO_THRESHOLD               76
/* location: अणुCR92,0,3पूर्ण,अणुCR95,0,2पूर्ण */
#घोषणा P4M900_IGA2_FIFO_HIGH_THRESHOLD          76
/* location: अणुCR94,0,6पूर्ण */
#घोषणा P4M900_IGA2_DISPLAY_QUEUE_EXPIRE_NUM     32

/* For VT3353, these values are suggested by HW */
/* location: अणुSR17,0,7पूर्ण */
#घोषणा VX800_IGA1_FIFO_MAX_DEPTH               192
/* location: अणुSR16,0,5पूर्ण,अणुSR16,7,7पूर्ण */
#घोषणा VX800_IGA1_FIFO_THRESHOLD               152
/* location: अणुSR18,0,5पूर्ण,अणुSR18,7,7पूर्ण */
#घोषणा VX800_IGA1_FIFO_HIGH_THRESHOLD          152
/* location: अणुSR22,0,4पूर्ण */
#घोषणा VX800_IGA1_DISPLAY_QUEUE_EXPIRE_NUM      64
/* location: अणुCR68,4,7पूर्ण,अणुCR94,7,7पूर्ण,अणुCR95,7,7पूर्ण */
#घोषणा VX800_IGA2_FIFO_MAX_DEPTH               96
/* location: अणुCR68,0,3पूर्ण,अणुCR95,4,6पूर्ण */
#घोषणा VX800_IGA2_FIFO_THRESHOLD               64
/* location: अणुCR92,0,3पूर्ण,अणुCR95,0,2पूर्ण */
#घोषणा VX800_IGA2_FIFO_HIGH_THRESHOLD          32
/* location: अणुCR94,0,6पूर्ण */
#घोषणा VX800_IGA2_DISPLAY_QUEUE_EXPIRE_NUM     128

/* For VT3409 */
#घोषणा VX855_IGA1_FIFO_MAX_DEPTH               400
#घोषणा VX855_IGA1_FIFO_THRESHOLD               320
#घोषणा VX855_IGA1_FIFO_HIGH_THRESHOLD          320
#घोषणा VX855_IGA1_DISPLAY_QUEUE_EXPIRE_NUM     160

#घोषणा VX855_IGA2_FIFO_MAX_DEPTH               200
#घोषणा VX855_IGA2_FIFO_THRESHOLD               160
#घोषणा VX855_IGA2_FIFO_HIGH_THRESHOLD          160
#घोषणा VX855_IGA2_DISPLAY_QUEUE_EXPIRE_NUM     320

/* For VT3410 */
#घोषणा VX900_IGA1_FIFO_MAX_DEPTH               400
#घोषणा VX900_IGA1_FIFO_THRESHOLD               320
#घोषणा VX900_IGA1_FIFO_HIGH_THRESHOLD          320
#घोषणा VX900_IGA1_DISPLAY_QUEUE_EXPIRE_NUM     160

#घोषणा VX900_IGA2_FIFO_MAX_DEPTH               192
#घोषणा VX900_IGA2_FIFO_THRESHOLD               160
#घोषणा VX900_IGA2_FIFO_HIGH_THRESHOLD          160
#घोषणा VX900_IGA2_DISPLAY_QUEUE_EXPIRE_NUM     320

#घोषणा IGA1_FIFO_DEPTH_SELECT_REG_NUM          1
#घोषणा IGA1_FIFO_THRESHOLD_REG_NUM             2
#घोषणा IGA1_FIFO_HIGH_THRESHOLD_REG_NUM        2
#घोषणा IGA1_DISPLAY_QUEUE_EXPIRE_NUM_REG_NUM   1

#घोषणा IGA2_FIFO_DEPTH_SELECT_REG_NUM          3
#घोषणा IGA2_FIFO_THRESHOLD_REG_NUM             2
#घोषणा IGA2_FIFO_HIGH_THRESHOLD_REG_NUM        2
#घोषणा IGA2_DISPLAY_QUEUE_EXPIRE_NUM_REG_NUM   1

#घोषणा IGA1_FIFO_DEPTH_SELECT_FORMULA(x)                   ((x/2)-1)
#घोषणा IGA1_FIFO_THRESHOLD_FORMULA(x)                      (x/4)
#घोषणा IGA1_DISPLAY_QUEUE_EXPIRE_NUM_FORMULA(x)            (x/4)
#घोषणा IGA1_FIFO_HIGH_THRESHOLD_FORMULA(x)                 (x/4)
#घोषणा IGA2_FIFO_DEPTH_SELECT_FORMULA(x)                   (((x/2)/4)-1)
#घोषणा IGA2_FIFO_THRESHOLD_FORMULA(x)                      (x/4)
#घोषणा IGA2_DISPLAY_QUEUE_EXPIRE_NUM_FORMULA(x)            (x/4)
#घोषणा IGA2_FIFO_HIGH_THRESHOLD_FORMULA(x)                 (x/4)

/************************************************************************/
/*  LCD Timing                                                          */
/************************************************************************/

/* 500 ms = 500000 us */
#घोषणा LCD_POWER_SEQ_TD0               500000
/* 50 ms = 50000 us */
#घोषणा LCD_POWER_SEQ_TD1               50000
/* 0 us */
#घोषणा LCD_POWER_SEQ_TD2               0
/* 210 ms = 210000 us */
#घोषणा LCD_POWER_SEQ_TD3               210000
/* 2^10 * (1/14.31818M) = 71.475 us (K400.revA) */
#घोषणा CLE266_POWER_SEQ_UNIT           71
/* 2^11 * (1/14.31818M) = 142.95 us (K400.revB) */
#घोषणा K800_POWER_SEQ_UNIT             142
/* 2^13 * (1/14.31818M) = 572.1 us */
#घोषणा P880_POWER_SEQ_UNIT             572

#घोषणा CLE266_POWER_SEQ_FORMULA(x)     ((x)/CLE266_POWER_SEQ_UNIT)
#घोषणा K800_POWER_SEQ_FORMULA(x)       ((x)/K800_POWER_SEQ_UNIT)
#घोषणा P880_POWER_SEQ_FORMULA(x)       ((x)/P880_POWER_SEQ_UNIT)

/* location: अणुCR8B,0,7पूर्ण,अणुCR8F,0,3पूर्ण */
#घोषणा LCD_POWER_SEQ_TD0_REG_NUM       2
/* location: अणुCR8C,0,7पूर्ण,अणुCR8F,4,7पूर्ण */
#घोषणा LCD_POWER_SEQ_TD1_REG_NUM       2
/* location: अणुCR8D,0,7पूर्ण,अणुCR90,0,3पूर्ण */
#घोषणा LCD_POWER_SEQ_TD2_REG_NUM       2
/* location: अणुCR8E,0,7पूर्ण,अणुCR90,4,7पूर्ण */
#घोषणा LCD_POWER_SEQ_TD3_REG_NUM       2

/* LCD Scaling factor*/
/* x: indicate setting horizontal size*/
/* y: indicate panel horizontal size*/

/* Horizontal scaling factor 10 bits (2^10) */
#घोषणा CLE266_LCD_HOR_SCF_FORMULA(x, y)   (((x-1)*1024)/(y-1))
/* Vertical scaling factor 10 bits (2^10) */
#घोषणा CLE266_LCD_VER_SCF_FORMULA(x, y)   (((x-1)*1024)/(y-1))
/* Horizontal scaling factor 10 bits (2^12) */
#घोषणा K800_LCD_HOR_SCF_FORMULA(x, y)     (((x-1)*4096)/(y-1))
/* Vertical scaling factor 10 bits (2^11) */
#घोषणा K800_LCD_VER_SCF_FORMULA(x, y)     (((x-1)*2048)/(y-1))

/* location: अणुCR9F,0,1पूर्ण,अणुCR77,0,7पूर्ण,अणुCR79,4,5पूर्ण */
#घोषणा LCD_HOR_SCALING_FACTOR_REG_NUM  3
/* location: अणुCR79,3,3पूर्ण,अणुCR78,0,7पूर्ण,अणुCR79,6,7पूर्ण */
#घोषणा LCD_VER_SCALING_FACTOR_REG_NUM  3
/* location: अणुCR77,0,7पूर्ण,अणुCR79,4,5पूर्ण */
#घोषणा LCD_HOR_SCALING_FACTOR_REG_NUM_CLE  2
/* location: अणुCR78,0,7पूर्ण,अणुCR79,6,7पूर्ण */
#घोषणा LCD_VER_SCALING_FACTOR_REG_NUM_CLE  2

काष्ठा io_रेजिस्टर अणु
	u8 io_addr;
	u8 start_bit;
	u8 end_bit;
पूर्ण;

/*****************************************************
**      Define IGA2 Shaकरोw Display Timing         ****
*****************************************************/

/* IGA2 Shaकरोw Horizontal Total */
काष्ठा iga2_shaकरोw_hor_total अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_SHADOW_HOR_TOTAL_REG_NUM];
पूर्ण;

/* IGA2 Shaकरोw Horizontal Blank End */
काष्ठा iga2_shaकरोw_hor_blank_end अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_SHADOW_HOR_BLANK_END_REG_NUM];
पूर्ण;

/* IGA2 Shaकरोw Vertical Total */
काष्ठा iga2_shaकरोw_ver_total अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_SHADOW_VER_TOTAL_REG_NUM];
पूर्ण;

/* IGA2 Shaकरोw Vertical Addressable Video */
काष्ठा iga2_shaकरोw_ver_addr अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_SHADOW_VER_ADDR_REG_NUM];
पूर्ण;

/* IGA2 Shaकरोw Vertical Blank Start */
काष्ठा iga2_shaकरोw_ver_blank_start अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_SHADOW_VER_BLANK_START_REG_NUM];
पूर्ण;

/* IGA2 Shaकरोw Vertical Blank End */
काष्ठा iga2_shaकरोw_ver_blank_end अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_SHADOW_VER_BLANK_END_REG_NUM];
पूर्ण;

/* IGA2 Shaकरोw Vertical Sync Start */
काष्ठा iga2_shaकरोw_ver_sync_start अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_SHADOW_VER_SYNC_START_REG_NUM];
पूर्ण;

/* IGA2 Shaकरोw Vertical Sync End */
काष्ठा iga2_shaकरोw_ver_sync_end अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_SHADOW_VER_SYNC_END_REG_NUM];
पूर्ण;

/* IGA1 Fetch Count Register */
काष्ठा iga1_fetch_count अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA1_FETCH_COUNT_REG_NUM];
पूर्ण;

/* IGA2 Fetch Count Register */
काष्ठा iga2_fetch_count अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_FETCH_COUNT_REG_NUM];
पूर्ण;

काष्ठा fetch_count अणु
	काष्ठा iga1_fetch_count iga1_fetch_count_reg;
	काष्ठा iga2_fetch_count iga2_fetch_count_reg;
पूर्ण;

/* Starting Address Register */
काष्ठा iga1_starting_addr अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA1_STARTING_ADDR_REG_NUM];
पूर्ण;

काष्ठा iga2_starting_addr अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_STARTING_ADDR_REG_NUM];
पूर्ण;

काष्ठा starting_addr अणु
	काष्ठा iga1_starting_addr iga1_starting_addr_reg;
	काष्ठा iga2_starting_addr iga2_starting_addr_reg;
पूर्ण;

/* LCD Power Sequence Timer */
काष्ठा lcd_pwd_seq_td0 अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[LCD_POWER_SEQ_TD0_REG_NUM];
पूर्ण;

काष्ठा lcd_pwd_seq_td1 अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[LCD_POWER_SEQ_TD1_REG_NUM];
पूर्ण;

काष्ठा lcd_pwd_seq_td2 अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[LCD_POWER_SEQ_TD2_REG_NUM];
पूर्ण;

काष्ठा lcd_pwd_seq_td3 अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[LCD_POWER_SEQ_TD3_REG_NUM];
पूर्ण;

काष्ठा _lcd_pwd_seq_समयr अणु
	काष्ठा lcd_pwd_seq_td0 td0;
	काष्ठा lcd_pwd_seq_td1 td1;
	काष्ठा lcd_pwd_seq_td2 td2;
	काष्ठा lcd_pwd_seq_td3 td3;
पूर्ण;

/* LCD Scaling Factor */
काष्ठा _lcd_hor_scaling_factor अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[LCD_HOR_SCALING_FACTOR_REG_NUM];
पूर्ण;

काष्ठा _lcd_ver_scaling_factor अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[LCD_VER_SCALING_FACTOR_REG_NUM];
पूर्ण;

काष्ठा _lcd_scaling_factor अणु
	काष्ठा _lcd_hor_scaling_factor lcd_hor_scaling_factor;
	काष्ठा _lcd_ver_scaling_factor lcd_ver_scaling_factor;
पूर्ण;

काष्ठा pll_limit अणु
	u16 multiplier_min;
	u16 multiplier_max;
	u8 भागisor;
	u8 rshअगरt;
पूर्ण;

काष्ठा rgbLUT अणु
	u8 red;
	u8 green;
	u8 blue;
पूर्ण;

काष्ठा lcd_pwd_seq_समयr अणु
	u16 td0;
	u16 td1;
	u16 td2;
	u16 td3;
पूर्ण;

/* Display FIFO Relation Registers*/
काष्ठा iga1_fअगरo_depth_select अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA1_FIFO_DEPTH_SELECT_REG_NUM];
पूर्ण;

काष्ठा iga1_fअगरo_threshold_select अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA1_FIFO_THRESHOLD_REG_NUM];
पूर्ण;

काष्ठा iga1_fअगरo_high_threshold_select अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA1_FIFO_HIGH_THRESHOLD_REG_NUM];
पूर्ण;

काष्ठा iga1_display_queue_expire_num अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA1_DISPLAY_QUEUE_EXPIRE_NUM_REG_NUM];
पूर्ण;

काष्ठा iga2_fअगरo_depth_select अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_FIFO_DEPTH_SELECT_REG_NUM];
पूर्ण;

काष्ठा iga2_fअगरo_threshold_select अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_FIFO_THRESHOLD_REG_NUM];
पूर्ण;

काष्ठा iga2_fअगरo_high_threshold_select अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_FIFO_HIGH_THRESHOLD_REG_NUM];
पूर्ण;

काष्ठा iga2_display_queue_expire_num अणु
	पूर्णांक reg_num;
	काष्ठा io_रेजिस्टर reg[IGA2_DISPLAY_QUEUE_EXPIRE_NUM_REG_NUM];
पूर्ण;

काष्ठा fअगरo_depth_select अणु
	काष्ठा iga1_fअगरo_depth_select iga1_fअगरo_depth_select_reg;
	काष्ठा iga2_fअगरo_depth_select iga2_fअगरo_depth_select_reg;
पूर्ण;

काष्ठा fअगरo_threshold_select अणु
	काष्ठा iga1_fअगरo_threshold_select iga1_fअगरo_threshold_select_reg;
	काष्ठा iga2_fअगरo_threshold_select iga2_fअगरo_threshold_select_reg;
पूर्ण;

काष्ठा fअगरo_high_threshold_select अणु
	काष्ठा iga1_fअगरo_high_threshold_select
	 iga1_fअगरo_high_threshold_select_reg;
	काष्ठा iga2_fअगरo_high_threshold_select
	 iga2_fअगरo_high_threshold_select_reg;
पूर्ण;

काष्ठा display_queue_expire_num अणु
	काष्ठा iga1_display_queue_expire_num
	 iga1_display_queue_expire_num_reg;
	काष्ठा iga2_display_queue_expire_num
	 iga2_display_queue_expire_num_reg;
पूर्ण;

काष्ठा iga2_shaकरोw_crtc_timing अणु
	काष्ठा iga2_shaकरोw_hor_total hor_total_shaकरोw;
	काष्ठा iga2_shaकरोw_hor_blank_end hor_blank_end_shaकरोw;
	काष्ठा iga2_shaकरोw_ver_total ver_total_shaकरोw;
	काष्ठा iga2_shaकरोw_ver_addr ver_addr_shaकरोw;
	काष्ठा iga2_shaकरोw_ver_blank_start ver_blank_start_shaकरोw;
	काष्ठा iga2_shaकरोw_ver_blank_end ver_blank_end_shaकरोw;
	काष्ठा iga2_shaकरोw_ver_sync_start ver_sync_start_shaकरोw;
	काष्ठा iga2_shaकरोw_ver_sync_end ver_sync_end_shaकरोw;
पूर्ण;

/* device ID */
#घोषणा CLE266_FUNCTION3    0x3123
#घोषणा KM400_FUNCTION3     0x3205
#घोषणा CN400_FUNCTION2     0x2259
#घोषणा CN400_FUNCTION3     0x3259
/* support VT3314 chipset */
#घोषणा CN700_FUNCTION2     0x2314
#घोषणा CN700_FUNCTION3     0x3208
/* VT3324 chipset */
#घोषणा CX700_FUNCTION2     0x2324
#घोषणा CX700_FUNCTION3     0x3324
/* VT3204 chipset*/
#घोषणा KM800_FUNCTION3      0x3204
/* VT3336 chipset*/
#घोषणा KM890_FUNCTION3      0x3336
/* VT3327 chipset*/
#घोषणा P4M890_FUNCTION3     0x3327
/* VT3293 chipset*/
#घोषणा CN750_FUNCTION3     0x3208
/* VT3364 chipset*/
#घोषणा P4M900_FUNCTION3    0x3364
/* VT3353 chipset*/
#घोषणा VX800_FUNCTION3     0x3353
/* VT3409 chipset*/
#घोषणा VX855_FUNCTION3     0x3409
/* VT3410 chipset*/
#घोषणा VX900_FUNCTION3     0x3410

काष्ठा IODATA अणु
	u8 Index;
	u8 Mask;
	u8 Data;
पूर्ण;

काष्ठा pci_device_id_info अणु
	u32 venकरोr;
	u32 device;
	u32 chip_index;
पूर्ण;

काष्ठा via_device_mapping अणु
	u32 device;
	स्थिर अक्षर *name;
पूर्ण;

बाह्य पूर्णांक viafb_SAMM_ON;
बाह्य पूर्णांक viafb_dual_fb;
बाह्य पूर्णांक viafb_LCD2_ON;
बाह्य पूर्णांक viafb_LCD_ON;
बाह्य पूर्णांक viafb_DVI_ON;
बाह्य पूर्णांक viafb_hotplug;

काष्ठा via_display_timing var_to_timing(स्थिर काष्ठा fb_var_screeninfo *var,
	u16 cxres, u16 cyres);
व्योम viafb_fill_crtc_timing(स्थिर काष्ठा fb_var_screeninfo *var,
	u16 cxres, u16 cyres, पूर्णांक iga);
व्योम viafb_set_vघड़ी(u32 CLK, पूर्णांक set_iga);
व्योम viafb_load_reg(पूर्णांक timing_value, पूर्णांक viafb_load_reg_num,
	काष्ठा io_रेजिस्टर *reg,
	      पूर्णांक io_type);
व्योम via_set_source(u32 devices, u8 iga);
व्योम via_set_state(u32 devices, u8 state);
व्योम via_set_sync_polarity(u32 devices, u8 polarity);
u32 via_parse_odev(अक्षर *input, अक्षर **end);
व्योम via_odev_to_seq(काष्ठा seq_file *m, u32 odev);
व्योम init_ad9389(व्योम);
/* Access I/O Function */
व्योम viafb_lock_crt(व्योम);
व्योम viafb_unlock_crt(व्योम);
व्योम viafb_load_fetch_count_reg(पूर्णांक h_addr, पूर्णांक bpp_byte, पूर्णांक set_iga);
व्योम viafb_ग_लिखो_regx(काष्ठा io_reg RegTable[], पूर्णांक ItemNum);
व्योम viafb_load_FIFO_reg(पूर्णांक set_iga, पूर्णांक hor_active, पूर्णांक ver_active);
व्योम viafb_set_dpa_gfx(पूर्णांक output_पूर्णांकerface, काष्ठा GFX_DPA_SETTING\
					*p_gfx_dpa_setting);

पूर्णांक viafb_seपंचांगode(व्योम);
व्योम viafb_fill_var_timing_info(काष्ठा fb_var_screeninfo *var,
	स्थिर काष्ठा fb_videomode *mode);
व्योम viafb_init_chip_info(पूर्णांक chip_type);
व्योम viafb_init_dac(पूर्णांक set_iga);
पूर्णांक viafb_get_refresh(पूर्णांक hres, पूर्णांक vres, u32 भग्न_refresh);
व्योम viafb_update_device_setting(पूर्णांक hres, पूर्णांक vres, पूर्णांक bpp, पूर्णांक flag);

व्योम viafb_set_iga_path(व्योम);
व्योम viafb_set_primary_color_रेजिस्टर(u8 index, u8 red, u8 green, u8 blue);
व्योम viafb_set_secondary_color_रेजिस्टर(u8 index, u8 red, u8 green, u8 blue);
व्योम viafb_get_fb_info(अचिन्हित पूर्णांक *fb_base, अचिन्हित पूर्णांक *fb_len);

#पूर्ण_अगर /* __HW_H__ */
