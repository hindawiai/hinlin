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

#अगर_अघोषित _isp_acquisition_defs_h
#घोषणा _isp_acquisition_defs_h

#घोषणा _ISP_ACQUISITION_REG_ALIGN                4  /* assuming 32 bit control bus width */
#घोषणा _ISP_ACQUISITION_BYTES_PER_ELEM           4

/* --------------------------------------------------*/

#घोषणा NOF_ACQ_IRQS                              1

/* --------------------------------------------------*/
/* FSM */
/* --------------------------------------------------*/
#घोषणा MEM2STREAM_FSM_STATE_BITS                 2
#घोषणा ACQ_SYNCHRONIZER_FSM_STATE_BITS           2

/* --------------------------------------------------*/
/* REGISTER INFO */
/* --------------------------------------------------*/

#घोषणा NOF_ACQ_REGS                              12

// Register id's of MMIO slave accesible रेजिस्टरs
#घोषणा ACQ_START_ADDR_REG_ID                     0
#घोषणा ACQ_MEM_REGION_SIZE_REG_ID                1
#घोषणा ACQ_NUM_MEM_REGIONS_REG_ID                2
#घोषणा ACQ_INIT_REG_ID                           3
#घोषणा ACQ_RECEIVED_SHORT_PACKETS_REG_ID         4
#घोषणा ACQ_RECEIVED_LONG_PACKETS_REG_ID          5
#घोषणा ACQ_LAST_COMMAND_REG_ID                   6
#घोषणा ACQ_NEXT_COMMAND_REG_ID                   7
#घोषणा ACQ_LAST_ACKNOWLEDGE_REG_ID               8
#घोषणा ACQ_NEXT_ACKNOWLEDGE_REG_ID               9
#घोषणा ACQ_FSM_STATE_INFO_REG_ID                 10
#घोषणा ACQ_INT_CNTR_INFO_REG_ID                  11

// Register width
#घोषणा ACQ_START_ADDR_REG_WIDTH                  9
#घोषणा ACQ_MEM_REGION_SIZE_REG_WIDTH             9
#घोषणा ACQ_NUM_MEM_REGIONS_REG_WIDTH             9
#घोषणा ACQ_INIT_REG_WIDTH                        3
#घोषणा ACQ_RECEIVED_SHORT_PACKETS_REG_WIDTH      32
#घोषणा ACQ_RECEIVED_LONG_PACKETS_REG_WIDTH       32
#घोषणा ACQ_LAST_COMMAND_REG_WIDTH                32
#घोषणा ACQ_NEXT_COMMAND_REG_WIDTH                32
#घोषणा ACQ_LAST_ACKNOWLEDGE_REG_WIDTH            32
#घोषणा ACQ_NEXT_ACKNOWLEDGE_REG_WIDTH            32
#घोषणा ACQ_FSM_STATE_INFO_REG_WIDTH              ((MEM2STREAM_FSM_STATE_BITS * 3) + (ACQ_SYNCHRONIZER_FSM_STATE_BITS * 3))
#घोषणा ACQ_INT_CNTR_INFO_REG_WIDTH               32

/* रेजिस्टर reset value */
#घोषणा ACQ_START_ADDR_REG_RSTVAL                 0
#घोषणा ACQ_MEM_REGION_SIZE_REG_RSTVAL            128
#घोषणा ACQ_NUM_MEM_REGIONS_REG_RSTVAL            3
#घोषणा ACQ_INIT_REG_RSTVAL                       0
#घोषणा ACQ_RECEIVED_SHORT_PACKETS_REG_RSTVAL     0
#घोषणा ACQ_RECEIVED_LONG_PACKETS_REG_RSTVAL      0
#घोषणा ACQ_LAST_COMMAND_REG_RSTVAL               0
#घोषणा ACQ_NEXT_COMMAND_REG_RSTVAL               0
#घोषणा ACQ_LAST_ACKNOWLEDGE_REG_RSTVAL           0
#घोषणा ACQ_NEXT_ACKNOWLEDGE_REG_RSTVAL           0
#घोषणा ACQ_FSM_STATE_INFO_REG_RSTVAL             0
#घोषणा ACQ_INT_CNTR_INFO_REG_RSTVAL              0

/* bit definitions */
#घोषणा ACQ_INIT_RST_REG_BIT                      0
#घोषणा ACQ_INIT_RESYNC_BIT                       2
#घोषणा ACQ_INIT_RST_IDX                          ACQ_INIT_RST_REG_BIT
#घोषणा ACQ_INIT_RST_BITS                         1
#घोषणा ACQ_INIT_RESYNC_IDX                       ACQ_INIT_RESYNC_BIT
#घोषणा ACQ_INIT_RESYNC_BITS                      1

/* --------------------------------------------------*/
/* TOKEN INFO */
/* --------------------------------------------------*/
#घोषणा ACQ_TOKEN_ID_LSB                          0
#घोषणा ACQ_TOKEN_ID_MSB                          3
#घोषणा ACQ_TOKEN_WIDTH                           (ACQ_TOKEN_ID_MSB - ACQ_TOKEN_ID_LSB  + 1) // 4
#घोषणा ACQ_TOKEN_ID_IDX                          0
#घोषणा ACQ_TOKEN_ID_BITS                         ACQ_TOKEN_WIDTH
#घोषणा ACQ_INIT_CMD_INIT_IDX                     4
#घोषणा ACQ_INIT_CMD_INIT_BITS                    3
#घोषणा ACQ_CMD_START_ADDR_IDX                    4
#घोषणा ACQ_CMD_START_ADDR_BITS                   9
#घोषणा ACQ_CMD_NOFWORDS_IDX                      13
#घोषणा ACQ_CMD_NOFWORDS_BITS                     9
#घोषणा ACQ_MEM_REGION_ID_IDX                     22
#घोषणा ACQ_MEM_REGION_ID_BITS                    9
#घोषणा ACQ_PACKET_LENGTH_TOKEN_MSB               21
#घोषणा ACQ_PACKET_LENGTH_TOKEN_LSB               13
#घोषणा ACQ_PACKET_DATA_FORMAT_ID_TOKEN_MSB       9
#घोषणा ACQ_PACKET_DATA_FORMAT_ID_TOKEN_LSB       4
#घोषणा ACQ_PACKET_CH_ID_TOKEN_MSB                11
#घोषणा ACQ_PACKET_CH_ID_TOKEN_LSB                10
#घोषणा ACQ_PACKET_MEM_REGION_ID_TOKEN_MSB        12		/* only क्रम capt_end_of_packet_written */
#घोषणा ACQ_PACKET_MEM_REGION_ID_TOKEN_LSB        4		/* only क्रम capt_end_of_packet_written */

/* Command tokens IDs */
#घोषणा ACQ_READ_REGION_AUTO_INCR_TOKEN_ID        0 //0000b
#घोषणा ACQ_READ_REGION_TOKEN_ID                  1 //0001b
#घोषणा ACQ_READ_REGION_SOP_TOKEN_ID              2 //0010b
#घोषणा ACQ_INIT_TOKEN_ID                         8 //1000b

/* Acknowledge token IDs */
#घोषणा ACQ_READ_REGION_ACK_TOKEN_ID              0 //0000b
#घोषणा ACQ_END_OF_PACKET_TOKEN_ID                4 //0100b
#घोषणा ACQ_END_OF_REGION_TOKEN_ID                5 //0101b
#घोषणा ACQ_SOP_MISMATCH_TOKEN_ID                 6 //0110b
#घोषणा ACQ_UNDEF_PH_TOKEN_ID                     7 //0111b

#घोषणा ACQ_TOKEN_MEMREGIONID_MSB                 30
#घोषणा ACQ_TOKEN_MEMREGIONID_LSB                 22
#घोषणा ACQ_TOKEN_NOFWORDS_MSB                    21
#घोषणा ACQ_TOKEN_NOFWORDS_LSB                    13
#घोषणा ACQ_TOKEN_STARTADDR_MSB                   12
#घोषणा ACQ_TOKEN_STARTADDR_LSB                   4

/* --------------------------------------------------*/
/* MIPI */
/* --------------------------------------------------*/

#घोषणा WORD_COUNT_WIDTH                          16
#घोषणा PKT_CODE_WIDTH                            6
#घोषणा CHN_NO_WIDTH                              2
#घोषणा ERROR_INFO_WIDTH                          8

#घोषणा LONG_PKTCODE_MAX                          63
#घोषणा LONG_PKTCODE_MIN                          16
#घोषणा SHORT_PKTCODE_MAX                         15

#घोषणा खातापूर्ण_CODE                                  1

/* --------------------------------------------------*/
/* Packet Info */
/* --------------------------------------------------*/
#घोषणा ACQ_START_OF_FRAME                        0
#घोषणा ACQ_END_OF_FRAME                          1
#घोषणा ACQ_START_OF_LINE                         2
#घोषणा ACQ_END_OF_LINE                           3
#घोषणा ACQ_LINE_PAYLOAD                          4
#घोषणा ACQ_GEN_SH_PKT                            5

/* bit definition */
#घोषणा ACQ_PKT_TYPE_IDX                          16
#घोषणा ACQ_PKT_TYPE_BITS                         6
#घोषणा ACQ_PKT_SOP_IDX                           32
#घोषणा ACQ_WORD_CNT_IDX                          0
#घोषणा ACQ_WORD_CNT_BITS                         16
#घोषणा ACQ_PKT_INFO_IDX                          16
#घोषणा ACQ_PKT_INFO_BITS                         8
#घोषणा ACQ_HEADER_DATA_IDX                       0
#घोषणा ACQ_HEADER_DATA_BITS                      16
#घोषणा ACQ_ACK_TOKEN_ID_IDX                      ACQ_TOKEN_ID_IDX
#घोषणा ACQ_ACK_TOKEN_ID_BITS                     ACQ_TOKEN_ID_BITS
#घोषणा ACQ_ACK_NOFWORDS_IDX                      13
#घोषणा ACQ_ACK_NOFWORDS_BITS                     9
#घोषणा ACQ_ACK_PKT_LEN_IDX                       4
#घोषणा ACQ_ACK_PKT_LEN_BITS                      16

/* --------------------------------------------------*/
/* Packet Data Type */
/* --------------------------------------------------*/

#घोषणा ACQ_YUV420_8_DATA                       24   /* 01 1000 YUV420 8-bit                                        */
#घोषणा ACQ_YUV420_10_DATA                      25   /* 01 1001  YUV420 10-bit                                      */
#घोषणा ACQ_YUV420_8L_DATA                      26   /* 01 1010   YUV420 8-bit legacy                               */
#घोषणा ACQ_YUV422_8_DATA                       30   /* 01 1110   YUV422 8-bit                                      */
#घोषणा ACQ_YUV422_10_DATA                      31   /* 01 1111   YUV422 10-bit                                     */
#घोषणा ACQ_RGB444_DATA                         32   /* 10 0000   RGB444                                            */
#घोषणा ACQ_RGB555_DATA						 33   /* 10 0001   RGB555                                            */
#घोषणा ACQ_RGB565_DATA						 34   /* 10 0010   RGB565                                            */
#घोषणा ACQ_RGB666_DATA						 35   /* 10 0011   RGB666                                            */
#घोषणा ACQ_RGB888_DATA						 36   /* 10 0100   RGB888                                            */
#घोषणा ACQ_RAW6_DATA							 40   /* 10 1000   RAW6                                              */
#घोषणा ACQ_RAW7_DATA							 41   /* 10 1001   RAW7                                              */
#घोषणा ACQ_RAW8_DATA							 42   /* 10 1010   RAW8                                              */
#घोषणा ACQ_RAW10_DATA						 43   /* 10 1011   RAW10                                             */
#घोषणा ACQ_RAW12_DATA						 44   /* 10 1100   RAW12                                             */
#घोषणा ACQ_RAW14_DATA						 45   /* 10 1101   RAW14                                             */
#घोषणा ACQ_USR_DEF_1_DATA						 48   /* 11 0000    JPEG [User Defined 8-bit Data Type 1]            */
#घोषणा ACQ_USR_DEF_2_DATA						 49   /* 11 0001    User Defined 8-bit Data Type 2                   */
#घोषणा ACQ_USR_DEF_3_DATA						 50   /* 11 0010    User Defined 8-bit Data Type 3                   */
#घोषणा ACQ_USR_DEF_4_DATA						 51   /* 11 0011    User Defined 8-bit Data Type 4                   */
#घोषणा ACQ_USR_DEF_5_DATA						 52   /* 11 0100    User Defined 8-bit Data Type 5                   */
#घोषणा ACQ_USR_DEF_6_DATA						 53   /* 11 0101    User Defined 8-bit Data Type 6                   */
#घोषणा ACQ_USR_DEF_7_DATA						 54   /* 11 0110    User Defined 8-bit Data Type 7                   */
#घोषणा ACQ_USR_DEF_8_DATA						 55   /* 11 0111    User Defined 8-bit Data Type 8                   */
#घोषणा ACQ_Emb_DATA							 18   /* 01 0010    embedded eight bit non image data                */
#घोषणा ACQ_SOF_DATA							 0   /* 00 0000    frame start                                      */
#घोषणा ACQ_खातापूर्ण_DATA							 1   /* 00 0001    frame end                                        */
#घोषणा ACQ_SOL_DATA							 2   /* 00 0010    line start                                       */
#घोषणा ACQ_EOL_DATA							 3   /* 00 0011    line end                                         */
#घोषणा ACQ_GEN_SH1_DATA						 8   /* 00 1000  Generic Short Packet Code 1                        */
#घोषणा ACQ_GEN_SH2_DATA						 9   /* 00 1001    Generic Short Packet Code 2                      */
#घोषणा ACQ_GEN_SH3_DATA						 10   /* 00 1010    Generic Short Packet Code 3                      */
#घोषणा ACQ_GEN_SH4_DATA						 11   /* 00 1011    Generic Short Packet Code 4                      */
#घोषणा ACQ_GEN_SH5_DATA						 12   /* 00 1100    Generic Short Packet Code 5                      */
#घोषणा ACQ_GEN_SH6_DATA						 13   /* 00 1101    Generic Short Packet Code 6                      */
#घोषणा ACQ_GEN_SH7_DATA						 14   /* 00 1110    Generic Short Packet Code 7                      */
#घोषणा ACQ_GEN_SH8_DATA						 15   /* 00 1111    Generic Short Packet Code 8                      */
#घोषणा ACQ_YUV420_8_CSPS_DATA					 28   /* 01 1100   YUV420 8-bit (Chroma Shअगरted Pixel Sampling)      */
#घोषणा ACQ_YUV420_10_CSPS_DATA					 29   /* 01 1101   YUV420 10-bit (Chroma Shअगरted Pixel Sampling)     */
#घोषणा ACQ_RESERVED_DATA_TYPE_MIN              56
#घोषणा ACQ_RESERVED_DATA_TYPE_MAX              63
#घोषणा ACQ_GEN_LONG_RESERVED_DATA_TYPE_MIN     19
#घोषणा ACQ_GEN_LONG_RESERVED_DATA_TYPE_MAX     23
#घोषणा ACQ_YUV_RESERVED_DATA_TYPE              27
#घोषणा ACQ_RGB_RESERVED_DATA_TYPE_MIN          37
#घोषणा ACQ_RGB_RESERVED_DATA_TYPE_MAX          39
#घोषणा ACQ_RAW_RESERVED_DATA_TYPE_MIN          46
#घोषणा ACQ_RAW_RESERVED_DATA_TYPE_MAX          47

/* --------------------------------------------------*/

#पूर्ण_अगर /* _isp_acquisition_defs_h */
