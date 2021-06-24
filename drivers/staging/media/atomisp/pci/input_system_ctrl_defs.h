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

#अगर_अघोषित _input_प्रणाली_ctrl_defs_h
#घोषणा _input_प्रणाली_ctrl_defs_h

#घोषणा _INPUT_SYSTEM_CTRL_REG_ALIGN                    4  /* assuming 32 bit control bus width */

/* --------------------------------------------------*/

/* --------------------------------------------------*/
/* REGISTER INFO */
/* --------------------------------------------------*/

// Number of रेजिस्टरs
#घोषणा ISYS_CTRL_NOF_REGS                              23

// Register id's of MMIO slave accesible रेजिस्टरs
#घोषणा ISYS_CTRL_CAPT_START_ADDR_A_REG_ID              0
#घोषणा ISYS_CTRL_CAPT_START_ADDR_B_REG_ID              1
#घोषणा ISYS_CTRL_CAPT_START_ADDR_C_REG_ID              2
#घोषणा ISYS_CTRL_CAPT_MEM_REGION_SIZE_A_REG_ID         3
#घोषणा ISYS_CTRL_CAPT_MEM_REGION_SIZE_B_REG_ID         4
#घोषणा ISYS_CTRL_CAPT_MEM_REGION_SIZE_C_REG_ID         5
#घोषणा ISYS_CTRL_CAPT_NUM_MEM_REGIONS_A_REG_ID         6
#घोषणा ISYS_CTRL_CAPT_NUM_MEM_REGIONS_B_REG_ID         7
#घोषणा ISYS_CTRL_CAPT_NUM_MEM_REGIONS_C_REG_ID         8
#घोषणा ISYS_CTRL_ACQ_START_ADDR_REG_ID                 9
#घोषणा ISYS_CTRL_ACQ_MEM_REGION_SIZE_REG_ID            10
#घोषणा ISYS_CTRL_ACQ_NUM_MEM_REGIONS_REG_ID            11
#घोषणा ISYS_CTRL_INIT_REG_ID                           12
#घोषणा ISYS_CTRL_LAST_COMMAND_REG_ID                   13
#घोषणा ISYS_CTRL_NEXT_COMMAND_REG_ID                   14
#घोषणा ISYS_CTRL_LAST_ACKNOWLEDGE_REG_ID               15
#घोषणा ISYS_CTRL_NEXT_ACKNOWLEDGE_REG_ID               16
#घोषणा ISYS_CTRL_FSM_STATE_INFO_REG_ID                 17
#घोषणा ISYS_CTRL_CAPT_A_FSM_STATE_INFO_REG_ID          18
#घोषणा ISYS_CTRL_CAPT_B_FSM_STATE_INFO_REG_ID          19
#घोषणा ISYS_CTRL_CAPT_C_FSM_STATE_INFO_REG_ID          20
#घोषणा ISYS_CTRL_ACQ_FSM_STATE_INFO_REG_ID             21
#घोषणा ISYS_CTRL_CAPT_RESERVE_ONE_MEM_REGION_REG_ID    22

/* रेजिस्टर reset value */
#घोषणा ISYS_CTRL_CAPT_START_ADDR_A_REG_RSTVAL           0
#घोषणा ISYS_CTRL_CAPT_START_ADDR_B_REG_RSTVAL           0
#घोषणा ISYS_CTRL_CAPT_START_ADDR_C_REG_RSTVAL           0
#घोषणा ISYS_CTRL_CAPT_MEM_REGION_SIZE_A_REG_RSTVAL      128
#घोषणा ISYS_CTRL_CAPT_MEM_REGION_SIZE_B_REG_RSTVAL      128
#घोषणा ISYS_CTRL_CAPT_MEM_REGION_SIZE_C_REG_RSTVAL      128
#घोषणा ISYS_CTRL_CAPT_NUM_MEM_REGIONS_A_REG_RSTVAL      3
#घोषणा ISYS_CTRL_CAPT_NUM_MEM_REGIONS_B_REG_RSTVAL      3
#घोषणा ISYS_CTRL_CAPT_NUM_MEM_REGIONS_C_REG_RSTVAL      3
#घोषणा ISYS_CTRL_ACQ_START_ADDR_REG_RSTVAL              0
#घोषणा ISYS_CTRL_ACQ_MEM_REGION_SIZE_REG_RSTVAL         128
#घोषणा ISYS_CTRL_ACQ_NUM_MEM_REGIONS_REG_RSTVAL         3
#घोषणा ISYS_CTRL_INIT_REG_RSTVAL                        0
#घोषणा ISYS_CTRL_LAST_COMMAND_REG_RSTVAL                15    //0x0000_000F (to संकेत non-valid cmd/ack after reset/soft-reset)
#घोषणा ISYS_CTRL_NEXT_COMMAND_REG_RSTVAL                15    //0x0000_000F (to संकेत non-valid cmd/ack after reset/soft-reset)
#घोषणा ISYS_CTRL_LAST_ACKNOWLEDGE_REG_RSTVAL            15    //0x0000_000F (to संकेत non-valid cmd/ack after reset/soft-reset)
#घोषणा ISYS_CTRL_NEXT_ACKNOWLEDGE_REG_RSTVAL            15    //0x0000_000F (to संकेत non-valid cmd/ack after reset/soft-reset)
#घोषणा ISYS_CTRL_FSM_STATE_INFO_REG_RSTVAL              0
#घोषणा ISYS_CTRL_CAPT_A_FSM_STATE_INFO_REG_RSTVAL       0
#घोषणा ISYS_CTRL_CAPT_B_FSM_STATE_INFO_REG_RSTVAL       0
#घोषणा ISYS_CTRL_CAPT_C_FSM_STATE_INFO_REG_RSTVAL       0
#घोषणा ISYS_CTRL_ACQ_FSM_STATE_INFO_REG_RSTVAL          0
#घोषणा ISYS_CTRL_CAPT_RESERVE_ONE_MEM_REGION_REG_RSTVAL 0

/* रेजिस्टर width value */
#घोषणा ISYS_CTRL_CAPT_START_ADDR_A_REG_WIDTH            9
#घोषणा ISYS_CTRL_CAPT_START_ADDR_B_REG_WIDTH            9
#घोषणा ISYS_CTRL_CAPT_START_ADDR_C_REG_WIDTH            9
#घोषणा ISYS_CTRL_CAPT_MEM_REGION_SIZE_A_REG_WIDTH       9
#घोषणा ISYS_CTRL_CAPT_MEM_REGION_SIZE_B_REG_WIDTH       9
#घोषणा ISYS_CTRL_CAPT_MEM_REGION_SIZE_C_REG_WIDTH       9
#घोषणा ISYS_CTRL_CAPT_NUM_MEM_REGIONS_A_REG_WIDTH       9
#घोषणा ISYS_CTRL_CAPT_NUM_MEM_REGIONS_B_REG_WIDTH       9
#घोषणा ISYS_CTRL_CAPT_NUM_MEM_REGIONS_C_REG_WIDTH       9
#घोषणा ISYS_CTRL_ACQ_START_ADDR_REG_WIDTH               9
#घोषणा ISYS_CTRL_ACQ_MEM_REGION_SIZE_REG_WIDTH          9
#घोषणा ISYS_CTRL_ACQ_NUM_MEM_REGIONS_REG_WIDTH          9
#घोषणा ISYS_CTRL_INIT_REG_WIDTH                         3
#घोषणा ISYS_CTRL_LAST_COMMAND_REG_WIDTH                 32    /* slave data width */
#घोषणा ISYS_CTRL_NEXT_COMMAND_REG_WIDTH                 32
#घोषणा ISYS_CTRL_LAST_ACKNOWLEDGE_REG_WIDTH             32
#घोषणा ISYS_CTRL_NEXT_ACKNOWLEDGE_REG_WIDTH             32
#घोषणा ISYS_CTRL_FSM_STATE_INFO_REG_WIDTH               32
#घोषणा ISYS_CTRL_CAPT_A_FSM_STATE_INFO_REG_WIDTH        32
#घोषणा ISYS_CTRL_CAPT_B_FSM_STATE_INFO_REG_WIDTH        32
#घोषणा ISYS_CTRL_CAPT_C_FSM_STATE_INFO_REG_WIDTH        32
#घोषणा ISYS_CTRL_ACQ_FSM_STATE_INFO_REG_WIDTH           32
#घोषणा ISYS_CTRL_CAPT_RESERVE_ONE_MEM_REGION_REG_WIDTH  1

/* bit definitions */

/* --------------------------------------------------*/
/* TOKEN INFO */
/* --------------------------------------------------*/

/*
InpSysCaptFramesAcq  1/0  [3:0] - 'b0000
[7:4] - CaptPortId,
	   CaptA-'b0000
	   CaptB-'b0001
	   CaptC-'b0010
[31:16] - NOF_frames
InpSysCaptFrameExt  2/0  [3:0] - 'b0001'
[7:4] - CaptPortId,
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC

  2/1  [31:0] - बाह्यal capture address
InpSysAcqFrame  2/0  [3:0] - 'b0010,
[31:4] - NOF_ext_mem_words
  2/1  [31:0] - बाह्यal memory पढ़ो start address
InpSysOverruleON  1/0  [3:0] - 'b0011,
[7:4] - overrule port id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

InpSysOverruleOFF  1/0  [3:0] - 'b0100,
[7:4] - overrule port id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

InpSysOverruleCmd  2/0  [3:0] - 'b0101,
[7:4] - overrule port id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

  2/1  [31:0] - command token value क्रम port opid

acknowledge tokens:

InpSysAckCFA  1/0   [3:0] - 'b0000
 [7:4] - CaptPortId,
	   CaptA-'b0000
	   CaptB- 'b0001
	   CaptC-'b0010
 [31:16] - NOF_frames
InpSysAckCFE  1/0  [3:0] - 'b0001'
[7:4] - CaptPortId,
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC

InpSysAckAF  1/0  [3:0] - 'b0010
InpSysAckOverruleON  1/0  [3:0] - 'b0011,
[7:4] - overrule port id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

InpSysAckOverruleOFF  1/0  [3:0] - 'b0100,
[7:4] - overrule port id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

InpSysAckOverrule  2/0  [3:0] - 'b0101,
[7:4] - overrule port id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

  2/1  [31:0] - acknowledge token value from port opid

*/

/* Command and acknowledge tokens IDs */
#घोषणा ISYS_CTRL_CAPT_FRAMES_ACQ_TOKEN_ID        0 /* 0000b */
#घोषणा ISYS_CTRL_CAPT_FRAME_EXT_TOKEN_ID         1 /* 0001b */
#घोषणा ISYS_CTRL_ACQ_FRAME_TOKEN_ID              2 /* 0010b */
#घोषणा ISYS_CTRL_OVERRULE_ON_TOKEN_ID            3 /* 0011b */
#घोषणा ISYS_CTRL_OVERRULE_OFF_TOKEN_ID           4 /* 0100b */
#घोषणा ISYS_CTRL_OVERRULE_TOKEN_ID               5 /* 0101b */

#घोषणा ISYS_CTRL_ACK_CFA_TOKEN_ID                0
#घोषणा ISYS_CTRL_ACK_CFE_TOKEN_ID                1
#घोषणा ISYS_CTRL_ACK_AF_TOKEN_ID                 2
#घोषणा ISYS_CTRL_ACK_OVERRULE_ON_TOKEN_ID        3
#घोषणा ISYS_CTRL_ACK_OVERRULE_OFF_TOKEN_ID       4
#घोषणा ISYS_CTRL_ACK_OVERRULE_TOKEN_ID           5
#घोषणा ISYS_CTRL_ACK_DEVICE_ERROR_TOKEN_ID       6

#घोषणा ISYS_CTRL_TOKEN_ID_MSB                    3
#घोषणा ISYS_CTRL_TOKEN_ID_LSB                    0
#घोषणा ISYS_CTRL_PORT_ID_TOKEN_MSB               7
#घोषणा ISYS_CTRL_PORT_ID_TOKEN_LSB               4
#घोषणा ISYS_CTRL_NOF_CAPT_TOKEN_MSB              31
#घोषणा ISYS_CTRL_NOF_CAPT_TOKEN_LSB              16
#घोषणा ISYS_CTRL_NOF_EXT_TOKEN_MSB               31
#घोषणा ISYS_CTRL_NOF_EXT_TOKEN_LSB               8

#घोषणा ISYS_CTRL_TOKEN_ID_IDX                    0
#घोषणा ISYS_CTRL_TOKEN_ID_BITS                   (ISYS_CTRL_TOKEN_ID_MSB - ISYS_CTRL_TOKEN_ID_LSB + 1)
#घोषणा ISYS_CTRL_PORT_ID_IDX                     (ISYS_CTRL_TOKEN_ID_IDX + ISYS_CTRL_TOKEN_ID_BITS)
#घोषणा ISYS_CTRL_PORT_ID_BITS                    (ISYS_CTRL_PORT_ID_TOKEN_MSB - ISYS_CTRL_PORT_ID_TOKEN_LSB + 1)
#घोषणा ISYS_CTRL_NOF_CAPT_IDX                    ISYS_CTRL_NOF_CAPT_TOKEN_LSB
#घोषणा ISYS_CTRL_NOF_CAPT_BITS                   (ISYS_CTRL_NOF_CAPT_TOKEN_MSB - ISYS_CTRL_NOF_CAPT_TOKEN_LSB + 1)
#घोषणा ISYS_CTRL_NOF_EXT_IDX                     ISYS_CTRL_NOF_EXT_TOKEN_LSB
#घोषणा ISYS_CTRL_NOF_EXT_BITS                    (ISYS_CTRL_NOF_EXT_TOKEN_MSB - ISYS_CTRL_NOF_EXT_TOKEN_LSB + 1)

#घोषणा ISYS_CTRL_PORT_ID_CAPT_A                  0 /* device ID क्रम capture unit A      */
#घोषणा ISYS_CTRL_PORT_ID_CAPT_B                  1 /* device ID क्रम capture unit B      */
#घोषणा ISYS_CTRL_PORT_ID_CAPT_C                  2 /* device ID क्रम capture unit C      */
#घोषणा ISYS_CTRL_PORT_ID_ACQUISITION             3 /* device ID क्रम acquistion unit     */
#घोषणा ISYS_CTRL_PORT_ID_DMA_CAPT_A              4 /* device ID क्रम dma unit            */
#घोषणा ISYS_CTRL_PORT_ID_DMA_CAPT_B              5 /* device ID क्रम dma unit            */
#घोषणा ISYS_CTRL_PORT_ID_DMA_CAPT_C              6 /* device ID क्रम dma unit            */
#घोषणा ISYS_CTRL_PORT_ID_DMA_ACQ                 7 /* device ID क्रम dma unit            */

#घोषणा ISYS_CTRL_NO_ACQ_ACK                      16 /* no ack from acquisition unit */
#घोषणा ISYS_CTRL_NO_DMA_ACK                      0
#घोषणा ISYS_CTRL_NO_CAPT_ACK                     16

#पूर्ण_अगर /* _input_प्रणाली_ctrl_defs_h */
