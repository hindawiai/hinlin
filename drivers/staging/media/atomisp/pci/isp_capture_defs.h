<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _isp_capture_defs_h
#घोषणा _isp_capture_defs_h

#घोषणा _ISP_CAPTURE_REG_ALIGN                    4  /* assuming 32 bit control bus width */
#घोषणा _ISP_CAPTURE_BITS_PER_ELEM                32  /* only क्रम data, not SOP */
#घोषणा _ISP_CAPTURE_BYTES_PER_ELEM               (_ISP_CAPTURE_BITS_PER_ELEM / 8)
#घोषणा _ISP_CAPTURE_BYTES_PER_WORD               32		/* 256/8 */
#घोषणा _ISP_CAPTURE_ELEM_PER_WORD                _ISP_CAPTURE_BYTES_PER_WORD / _ISP_CAPTURE_BYTES_PER_ELEM

/* --------------------------------------------------*/

#घोषणा NOF_IRQS                                  2

/* --------------------------------------------------*/
/* REGISTER INFO */
/* --------------------------------------------------*/

// Number of रेजिस्टरs
#घोषणा CAPT_NOF_REGS                             16

// Register id's of MMIO slave accesible रेजिस्टरs
#घोषणा CAPT_START_MODE_REG_ID                    0
#घोषणा CAPT_START_ADDR_REG_ID                    1
#घोषणा CAPT_MEM_REGION_SIZE_REG_ID               2
#घोषणा CAPT_NUM_MEM_REGIONS_REG_ID               3
#घोषणा CAPT_INIT_REG_ID                          4
#घोषणा CAPT_START_REG_ID                         5
#घोषणा CAPT_STOP_REG_ID                          6

#घोषणा CAPT_PACKET_LENGTH_REG_ID                 7
#घोषणा CAPT_RECEIVED_LENGTH_REG_ID               8
#घोषणा CAPT_RECEIVED_SHORT_PACKETS_REG_ID        9
#घोषणा CAPT_RECEIVED_LONG_PACKETS_REG_ID         10
#घोषणा CAPT_LAST_COMMAND_REG_ID                  11
#घोषणा CAPT_NEXT_COMMAND_REG_ID                  12
#घोषणा CAPT_LAST_ACKNOWLEDGE_REG_ID              13
#घोषणा CAPT_NEXT_ACKNOWLEDGE_REG_ID              14
#घोषणा CAPT_FSM_STATE_INFO_REG_ID                15

// Register width
#घोषणा CAPT_START_MODE_REG_WIDTH                 1

#घोषणा CAPT_START_REG_WIDTH                      1
#घोषणा CAPT_STOP_REG_WIDTH                       1

/* --------------------------------------------------*/
/* FSM */
/* --------------------------------------------------*/
#घोषणा CAPT_WRITE2MEM_FSM_STATE_BITS             2
#घोषणा CAPT_SYNCHRONIZER_FSM_STATE_BITS          3

#घोषणा CAPT_PACKET_LENGTH_REG_WIDTH              17
#घोषणा CAPT_RECEIVED_LENGTH_REG_WIDTH            17
#घोषणा CAPT_RECEIVED_SHORT_PACKETS_REG_WIDTH     32
#घोषणा CAPT_RECEIVED_LONG_PACKETS_REG_WIDTH      32
#घोषणा CAPT_LAST_COMMAND_REG_WIDTH               32
#घोषणा CAPT_LAST_ACKNOWLEDGE_REG_WIDTH           32
#घोषणा CAPT_NEXT_ACKNOWLEDGE_REG_WIDTH           32
#घोषणा CAPT_FSM_STATE_INFO_REG_WIDTH             ((CAPT_WRITE2MEM_FSM_STATE_BITS * 3) + (CAPT_SYNCHRONIZER_FSM_STATE_BITS * 3))

/* रेजिस्टर reset value */
#घोषणा CAPT_START_MODE_REG_RSTVAL                0
#घोषणा CAPT_START_ADDR_REG_RSTVAL                0
#घोषणा CAPT_MEM_REGION_SIZE_REG_RSTVAL           128
#घोषणा CAPT_NUM_MEM_REGIONS_REG_RSTVAL           3
#घोषणा CAPT_INIT_REG_RSTVAL                      0

#घोषणा CAPT_START_REG_RSTVAL                     0
#घोषणा CAPT_STOP_REG_RSTVAL                      0

#घोषणा CAPT_PACKET_LENGTH_REG_RSTVAL             0
#घोषणा CAPT_RECEIVED_LENGTH_REG_RSTVAL           0
#घोषणा CAPT_RECEIVED_SHORT_PACKETS_REG_RSTVAL    0
#घोषणा CAPT_RECEIVED_LONG_PACKETS_REG_RSTVAL     0
#घोषणा CAPT_LAST_COMMAND_REG_RSTVAL              0
#घोषणा CAPT_NEXT_COMMAND_REG_RSTVAL              0
#घोषणा CAPT_LAST_ACKNOWLEDGE_REG_RSTVAL          0
#घोषणा CAPT_NEXT_ACKNOWLEDGE_REG_RSTVAL          0
#घोषणा CAPT_FSM_STATE_INFO_REG_RSTVAL            0

/* bit definitions */
#घोषणा CAPT_INIT_RST_REG_BIT                     0
#घोषणा CAPT_INIT_FLUSH_BIT                       1
#घोषणा CAPT_INIT_RESYNC_BIT                      2
#घोषणा CAPT_INIT_RESTART_BIT                     3
#घोषणा CAPT_INIT_RESTART_MEM_ADDR_LSB            4

#घोषणा CAPT_INIT_RST_REG_IDX                     CAPT_INIT_RST_REG_BIT
#घोषणा CAPT_INIT_RST_REG_BITS                    1
#घोषणा CAPT_INIT_FLUSH_IDX                       CAPT_INIT_FLUSH_BIT
#घोषणा CAPT_INIT_FLUSH_BITS                      1
#घोषणा CAPT_INIT_RESYNC_IDX                      CAPT_INIT_RESYNC_BIT
#घोषणा CAPT_INIT_RESYNC_BITS                     1
#घोषणा CAPT_INIT_RESTART_IDX                     CAPT_INIT_RESTART_BIT
#घोषणा CAPT_INIT_RESTART_BITS									1
#घोषणा CAPT_INIT_RESTART_MEM_ADDR_IDX            CAPT_INIT_RESTART_MEM_ADDR_LSB

/* --------------------------------------------------*/
/* TOKEN INFO */
/* --------------------------------------------------*/
#घोषणा CAPT_TOKEN_ID_LSB                         0
#घोषणा CAPT_TOKEN_ID_MSB                         3
#घोषणा CAPT_TOKEN_WIDTH                         (CAPT_TOKEN_ID_MSB - CAPT_TOKEN_ID_LSB  + 1) /* 4 */

/* Command tokens IDs */
#घोषणा CAPT_START_TOKEN_ID                       0 /* 0000b */
#घोषणा CAPT_STOP_TOKEN_ID                        1 /* 0001b */
#घोषणा CAPT_FREEZE_TOKEN_ID                      2 /* 0010b */
#घोषणा CAPT_RESUME_TOKEN_ID                      3 /* 0011b */
#घोषणा CAPT_INIT_TOKEN_ID                        8 /* 1000b */

#घोषणा CAPT_START_TOKEN_BIT                      0
#घोषणा CAPT_STOP_TOKEN_BIT                       0
#घोषणा CAPT_FREEZE_TOKEN_BIT                     0
#घोषणा CAPT_RESUME_TOKEN_BIT                     0
#घोषणा CAPT_INIT_TOKEN_BIT                       0

/* Acknowledge token IDs */
#घोषणा CAPT_END_OF_PACKET_RECEIVED_TOKEN_ID      0 /* 0000b */
#घोषणा CAPT_END_OF_PACKET_WRITTEN_TOKEN_ID       1 /* 0001b */
#घोषणा CAPT_END_OF_REGION_WRITTEN_TOKEN_ID       2 /* 0010b */
#घोषणा CAPT_FLUSH_DONE_TOKEN_ID                  3 /* 0011b */
#घोषणा CAPT_PREMATURE_SOP_TOKEN_ID               4 /* 0100b */
#घोषणा CAPT_MISSING_SOP_TOKEN_ID                 5 /* 0101b */
#घोषणा CAPT_UNDEF_PH_TOKEN_ID                    6 /* 0110b */
#घोषणा CAPT_STOP_ACK_TOKEN_ID                    7 /* 0111b */

#घोषणा CAPT_PACKET_LENGTH_TOKEN_MSB             19
#घोषणा CAPT_PACKET_LENGTH_TOKEN_LSB              4
#घोषणा CAPT_SUPER_PACKET_LENGTH_TOKEN_MSB       20
#घोषणा CAPT_SUPER_PACKET_LENGTH_TOKEN_LSB        4
#घोषणा CAPT_PACKET_DATA_FORMAT_ID_TOKEN_MSB     25
#घोषणा CAPT_PACKET_DATA_FORMAT_ID_TOKEN_LSB     20
#घोषणा CAPT_PACKET_CH_ID_TOKEN_MSB              27
#घोषणा CAPT_PACKET_CH_ID_TOKEN_LSB              26
#घोषणा CAPT_PACKET_MEM_REGION_ID_TOKEN_MSB      29
#घोषणा CAPT_PACKET_MEM_REGION_ID_TOKEN_LSB      21

/*  bit definition */
#घोषणा CAPT_CMD_IDX                              CAPT_TOKEN_ID_LSB
#घोषणा	CAPT_CMD_BITS                             (CAPT_TOKEN_ID_MSB - CAPT_TOKEN_ID_LSB + 1)
#घोषणा CAPT_SOP_IDX                              32
#घोषणा CAPT_SOP_BITS                             1
#घोषणा CAPT_PKT_INFO_IDX                         16
#घोषणा CAPT_PKT_INFO_BITS                        8
#घोषणा CAPT_PKT_TYPE_IDX                         0
#घोषणा CAPT_PKT_TYPE_BITS                        6
#घोषणा CAPT_HEADER_DATA_IDX                      0
#घोषणा CAPT_HEADER_DATA_BITS                     16
#घोषणा CAPT_PKT_DATA_IDX                         0
#घोषणा CAPT_PKT_DATA_BITS                        32
#घोषणा CAPT_WORD_CNT_IDX                         0
#घोषणा CAPT_WORD_CNT_BITS                        16
#घोषणा CAPT_ACK_TOKEN_ID_IDX                     0
#घोषणा CAPT_ACK_TOKEN_ID_BITS                    4
//#घोषणा CAPT_ACK_PKT_LEN_IDX                      CAPT_PACKET_LENGTH_TOKEN_LSB
//#घोषणा CAPT_ACK_PKT_LEN_BITS                     (CAPT_PACKET_LENGTH_TOKEN_MSB - CAPT_PACKET_LENGTH_TOKEN_LSB + 1)
//#घोषणा CAPT_ACK_PKT_INFO_IDX                     20
//#घोषणा CAPT_ACK_PKT_INFO_BITS                    8
//#घोषणा CAPT_ACK_MEM_REG_ID1_IDX                  20			/* क्रम capt_end_of_packet_written */
//#घोषणा CAPT_ACK_MEM_REG_ID2_IDX                  4       /* क्रम capt_end_of_region_written */
#घोषणा CAPT_ACK_PKT_LEN_IDX                      CAPT_PACKET_LENGTH_TOKEN_LSB
#घोषणा CAPT_ACK_PKT_LEN_BITS                     (CAPT_PACKET_LENGTH_TOKEN_MSB - CAPT_PACKET_LENGTH_TOKEN_LSB + 1)
#घोषणा CAPT_ACK_SUPER_PKT_LEN_IDX                CAPT_SUPER_PACKET_LENGTH_TOKEN_LSB
#घोषणा CAPT_ACK_SUPER_PKT_LEN_BITS               (CAPT_SUPER_PACKET_LENGTH_TOKEN_MSB - CAPT_SUPER_PACKET_LENGTH_TOKEN_LSB + 1)
#घोषणा CAPT_ACK_PKT_INFO_IDX                     CAPT_PACKET_DATA_FORMAT_ID_TOKEN_LSB
#घोषणा CAPT_ACK_PKT_INFO_BITS                    (CAPT_PACKET_CH_ID_TOKEN_MSB - CAPT_PACKET_DATA_FORMAT_ID_TOKEN_LSB + 1)
#घोषणा CAPT_ACK_MEM_REGION_ID_IDX                CAPT_PACKET_MEM_REGION_ID_TOKEN_LSB
#घोषणा CAPT_ACK_MEM_REGION_ID_BITS               (CAPT_PACKET_MEM_REGION_ID_TOKEN_MSB - CAPT_PACKET_MEM_REGION_ID_TOKEN_LSB + 1)
#घोषणा CAPT_ACK_PKT_TYPE_IDX                     CAPT_PACKET_DATA_FORMAT_ID_TOKEN_LSB
#घोषणा CAPT_ACK_PKT_TYPE_BITS                    (CAPT_PACKET_DATA_FORMAT_ID_TOKEN_MSB - CAPT_PACKET_DATA_FORMAT_ID_TOKEN_LSB + 1)
#घोषणा CAPT_INIT_TOKEN_INIT_IDX                  4
#घोषणा CAPT_INIT_TOKEN_INIT_BITS                 22

/* --------------------------------------------------*/
/* MIPI */
/* --------------------------------------------------*/

#घोषणा CAPT_WORD_COUNT_WIDTH                     16
#घोषणा CAPT_PKT_CODE_WIDTH                       6
#घोषणा CAPT_CHN_NO_WIDTH                         2
#घोषणा CAPT_ERROR_INFO_WIDTH                     8

#घोषणा LONG_PKTCODE_MAX                          63
#घोषणा LONG_PKTCODE_MIN                          16
#घोषणा SHORT_PKTCODE_MAX                         15

/* --------------------------------------------------*/
/* Packet Info */
/* --------------------------------------------------*/
#घोषणा CAPT_START_OF_FRAME                       0
#घोषणा CAPT_END_OF_FRAME                         1
#घोषणा CAPT_START_OF_LINE                        2
#घोषणा CAPT_END_OF_LINE                          3
#घोषणा CAPT_LINE_PAYLOAD                         4
#घोषणा CAPT_GEN_SH_PKT                           5

/* --------------------------------------------------*/
/* Packet Data Type */
/* --------------------------------------------------*/

#घोषणा CAPT_YUV420_8_DATA                       24   /* 01 1000 YUV420 8-bit                                        */
#घोषणा CAPT_YUV420_10_DATA                      25   /* 01 1001  YUV420 10-bit                                      */
#घोषणा CAPT_YUV420_8L_DATA                      26   /* 01 1010   YUV420 8-bit legacy                               */
#घोषणा CAPT_YUV422_8_DATA                       30   /* 01 1110   YUV422 8-bit                                      */
#घोषणा CAPT_YUV422_10_DATA                      31   /* 01 1111   YUV422 10-bit                                     */
#घोषणा CAPT_RGB444_DATA                         32   /* 10 0000   RGB444                                            */
#घोषणा CAPT_RGB555_DATA						 33   /* 10 0001   RGB555                                            */
#घोषणा CAPT_RGB565_DATA						 34   /* 10 0010   RGB565                                            */
#घोषणा CAPT_RGB666_DATA						 35   /* 10 0011   RGB666                                            */
#घोषणा CAPT_RGB888_DATA						 36   /* 10 0100   RGB888                                            */
#घोषणा CAPT_RAW6_DATA							 40   /* 10 1000   RAW6                                              */
#घोषणा CAPT_RAW7_DATA							 41   /* 10 1001   RAW7                                              */
#घोषणा CAPT_RAW8_DATA							 42   /* 10 1010   RAW8                                              */
#घोषणा CAPT_RAW10_DATA						 43   /* 10 1011   RAW10                                             */
#घोषणा CAPT_RAW12_DATA						 44   /* 10 1100   RAW12                                             */
#घोषणा CAPT_RAW14_DATA						 45   /* 10 1101   RAW14                                             */
#घोषणा CAPT_USR_DEF_1_DATA						 48   /* 11 0000    JPEG [User Defined 8-bit Data Type 1]            */
#घोषणा CAPT_USR_DEF_2_DATA						 49   /* 11 0001    User Defined 8-bit Data Type 2                   */
#घोषणा CAPT_USR_DEF_3_DATA						 50   /* 11 0010    User Defined 8-bit Data Type 3                   */
#घोषणा CAPT_USR_DEF_4_DATA						 51   /* 11 0011    User Defined 8-bit Data Type 4                   */
#घोषणा CAPT_USR_DEF_5_DATA						 52   /* 11 0100    User Defined 8-bit Data Type 5                   */
#घोषणा CAPT_USR_DEF_6_DATA						 53   /* 11 0101    User Defined 8-bit Data Type 6                   */
#घोषणा CAPT_USR_DEF_7_DATA						 54   /* 11 0110    User Defined 8-bit Data Type 7                   */
#घोषणा CAPT_USR_DEF_8_DATA						 55   /* 11 0111    User Defined 8-bit Data Type 8                   */
#घोषणा CAPT_Emb_DATA							 18   /* 01 0010    embedded eight bit non image data                */
#घोषणा CAPT_SOF_DATA							 0   /* 00 0000    frame start                                      */
#घोषणा CAPT_खातापूर्ण_DATA							 1   /* 00 0001    frame end                                        */
#घोषणा CAPT_SOL_DATA							 2   /* 00 0010    line start                                       */
#घोषणा CAPT_EOL_DATA							 3   /* 00 0011    line end                                         */
#घोषणा CAPT_GEN_SH1_DATA						 8   /* 00 1000  Generic Short Packet Code 1                        */
#घोषणा CAPT_GEN_SH2_DATA						 9   /* 00 1001    Generic Short Packet Code 2                      */
#घोषणा CAPT_GEN_SH3_DATA						 10   /* 00 1010    Generic Short Packet Code 3                      */
#घोषणा CAPT_GEN_SH4_DATA						 11   /* 00 1011    Generic Short Packet Code 4                      */
#घोषणा CAPT_GEN_SH5_DATA						 12   /* 00 1100    Generic Short Packet Code 5                      */
#घोषणा CAPT_GEN_SH6_DATA						 13   /* 00 1101    Generic Short Packet Code 6                      */
#घोषणा CAPT_GEN_SH7_DATA						 14   /* 00 1110    Generic Short Packet Code 7                      */
#घोषणा CAPT_GEN_SH8_DATA						 15   /* 00 1111    Generic Short Packet Code 8                      */
#घोषणा CAPT_YUV420_8_CSPS_DATA					 28   /* 01 1100   YUV420 8-bit (Chroma Shअगरted Pixel Sampling)      */
#घोषणा CAPT_YUV420_10_CSPS_DATA					 29   /* 01 1101   YUV420 10-bit (Chroma Shअगरted Pixel Sampling)     */
#घोषणा CAPT_RESERVED_DATA_TYPE_MIN              56
#घोषणा CAPT_RESERVED_DATA_TYPE_MAX              63
#घोषणा CAPT_GEN_LONG_RESERVED_DATA_TYPE_MIN     19
#घोषणा CAPT_GEN_LONG_RESERVED_DATA_TYPE_MAX     23
#घोषणा CAPT_YUV_RESERVED_DATA_TYPE              27
#घोषणा CAPT_RGB_RESERVED_DATA_TYPE_MIN          37
#घोषणा CAPT_RGB_RESERVED_DATA_TYPE_MAX          39
#घोषणा CAPT_RAW_RESERVED_DATA_TYPE_MIN          46
#घोषणा CAPT_RAW_RESERVED_DATA_TYPE_MAX          47

/* --------------------------------------------------*/
/* Capture Unit State */
/* --------------------------------------------------*/
#घोषणा CAPT_FREE_RUN                             0
#घोषणा CAPT_NO_SYNC                              1
#घोषणा CAPT_SYNC_SWP                             2
#घोषणा CAPT_SYNC_MWP                             3
#घोषणा CAPT_SYNC_WAIT                            4
#घोषणा CAPT_FREEZE                               5
#घोषणा CAPT_RUN                                  6

/* --------------------------------------------------*/

#पूर्ण_अगर /* _isp_capture_defs_h */
