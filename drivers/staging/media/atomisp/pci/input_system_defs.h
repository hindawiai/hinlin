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

#अगर_अघोषित _input_प्रणाली_defs_h
#घोषणा _input_प्रणाली_defs_h

/* csi controller modes */
#घोषणा HIVE_CSI_CONFIG_MAIN                   0
#घोषणा HIVE_CSI_CONFIG_STEREO1                4
#घोषणा HIVE_CSI_CONFIG_STEREO2                8

/* general purpose रेजिस्टर IDs */

/* Stream Multicast select modes */
#घोषणा HIVE_ISYS_GPREG_MULTICAST_A_IDX           0
#घोषणा HIVE_ISYS_GPREG_MULTICAST_B_IDX           1
#घोषणा HIVE_ISYS_GPREG_MULTICAST_C_IDX           2

/* Stream Mux select modes */
#घोषणा HIVE_ISYS_GPREG_MUX_IDX                   3

/* streaming monitor status and control */
#घोषणा HIVE_ISYS_GPREG_STRMON_STAT_IDX           4
#घोषणा HIVE_ISYS_GPREG_STRMON_COND_IDX           5
#घोषणा HIVE_ISYS_GPREG_STRMON_IRQ_EN_IDX         6
#घोषणा HIVE_ISYS_GPREG_SRST_IDX                  7
#घोषणा HIVE_ISYS_GPREG_SLV_REG_SRST_IDX          8
#घोषणा HIVE_ISYS_GPREG_REG_PORT_A_IDX            9
#घोषणा HIVE_ISYS_GPREG_REG_PORT_B_IDX            10

/* Bit numbers of the soft reset रेजिस्टर */
#घोषणा HIVE_ISYS_GPREG_SRST_CAPT_FIFO_A_BIT      0
#घोषणा HIVE_ISYS_GPREG_SRST_CAPT_FIFO_B_BIT      1
#घोषणा HIVE_ISYS_GPREG_SRST_CAPT_FIFO_C_BIT      2
#घोषणा HIVE_ISYS_GPREG_SRST_MULTICAST_A_BIT      3
#घोषणा HIVE_ISYS_GPREG_SRST_MULTICAST_B_BIT      4
#घोषणा HIVE_ISYS_GPREG_SRST_MULTICAST_C_BIT      5
#घोषणा HIVE_ISYS_GPREG_SRST_CAPT_A_BIT           6
#घोषणा HIVE_ISYS_GPREG_SRST_CAPT_B_BIT           7
#घोषणा HIVE_ISYS_GPREG_SRST_CAPT_C_BIT           8
#घोषणा HIVE_ISYS_GPREG_SRST_ACQ_BIT              9
/* For ISYS_CTRL 5bits are defined to allow soft-reset per sub-controller and top-ctrl */
#घोषणा HIVE_ISYS_GPREG_SRST_ISYS_CTRL_BIT        10  /*LSB क्रम 5bit vector */
#घोषणा HIVE_ISYS_GPREG_SRST_ISYS_CTRL_CAPT_A_BIT 10
#घोषणा HIVE_ISYS_GPREG_SRST_ISYS_CTRL_CAPT_B_BIT 11
#घोषणा HIVE_ISYS_GPREG_SRST_ISYS_CTRL_CAPT_C_BIT 12
#घोषणा HIVE_ISYS_GPREG_SRST_ISYS_CTRL_ACQ_BIT    13
#घोषणा HIVE_ISYS_GPREG_SRST_ISYS_CTRL_TOP_BIT    14
/* -- */
#घोषणा HIVE_ISYS_GPREG_SRST_STR_MUX_BIT          15
#घोषणा HIVE_ISYS_GPREG_SRST_CIO2AHB_BIT          16
#घोषणा HIVE_ISYS_GPREG_SRST_GEN_SHORT_FIFO_BIT   17
#घोषणा HIVE_ISYS_GPREG_SRST_WIDE_BUS_BIT         18 // includes CIO conv
#घोषणा HIVE_ISYS_GPREG_SRST_DMA_BIT              19
#घोषणा HIVE_ISYS_GPREG_SRST_SF_CTRL_CAPT_A_BIT   20
#घोषणा HIVE_ISYS_GPREG_SRST_SF_CTRL_CAPT_B_BIT   21
#घोषणा HIVE_ISYS_GPREG_SRST_SF_CTRL_CAPT_C_BIT   22
#घोषणा HIVE_ISYS_GPREG_SRST_SF_CTRL_ACQ_BIT      23
#घोषणा HIVE_ISYS_GPREG_SRST_CSI_BE_OUT_BIT       24

#घोषणा HIVE_ISYS_GPREG_SLV_REG_SRST_CAPT_A_BIT    0
#घोषणा HIVE_ISYS_GPREG_SLV_REG_SRST_CAPT_B_BIT    1
#घोषणा HIVE_ISYS_GPREG_SLV_REG_SRST_CAPT_C_BIT    2
#घोषणा HIVE_ISYS_GPREG_SLV_REG_SRST_ACQ_BIT       3
#घोषणा HIVE_ISYS_GPREG_SLV_REG_SRST_DMA_BIT        4
#घोषणा HIVE_ISYS_GPREG_SLV_REG_SRST_ISYS_CTRL_BIT  5

/* streaming monitor port id's */
#घोषणा HIVE_ISYS_STR_MON_PORT_CAPA            0
#घोषणा HIVE_ISYS_STR_MON_PORT_CAPB            1
#घोषणा HIVE_ISYS_STR_MON_PORT_CAPC            2
#घोषणा HIVE_ISYS_STR_MON_PORT_ACQ             3
#घोषणा HIVE_ISYS_STR_MON_PORT_CSS_GENSH       4
#घोषणा HIVE_ISYS_STR_MON_PORT_SF_GENSH        5
#घोषणा HIVE_ISYS_STR_MON_PORT_SP2ISYS         6
#घोषणा HIVE_ISYS_STR_MON_PORT_ISYS2SP         7
#घोषणा HIVE_ISYS_STR_MON_PORT_PIXA            8
#घोषणा HIVE_ISYS_STR_MON_PORT_PIXB            9

/* पूर्णांकerrupt bit ID's        */
#घोषणा HIVE_ISYS_IRQ_CSI_SOF_BIT_ID           0
#घोषणा HIVE_ISYS_IRQ_CSI_खातापूर्ण_BIT_ID           1
#घोषणा HIVE_ISYS_IRQ_CSI_SOL_BIT_ID           2
#घोषणा HIVE_ISYS_IRQ_CSI_EOL_BIT_ID           3
#घोषणा HIVE_ISYS_IRQ_CSI_RECEIVER_BIT_ID      4
#घोषणा HIVE_ISYS_IRQ_CSI_RECEIVER_BE_BIT_ID   5
#घोषणा HIVE_ISYS_IRQ_CAP_UNIT_A_NO_SOP        6
#घोषणा HIVE_ISYS_IRQ_CAP_UNIT_A_LATE_SOP      7
/*#घोषणा HIVE_ISYS_IRQ_CAP_UNIT_A_UNDEF_PH      7*/
#घोषणा HIVE_ISYS_IRQ_CAP_UNIT_B_NO_SOP        8
#घोषणा HIVE_ISYS_IRQ_CAP_UNIT_B_LATE_SOP      9
/*#घोषणा HIVE_ISYS_IRQ_CAP_UNIT_B_UNDEF_PH     10*/
#घोषणा HIVE_ISYS_IRQ_CAP_UNIT_C_NO_SOP       10
#घोषणा HIVE_ISYS_IRQ_CAP_UNIT_C_LATE_SOP     11
/*#घोषणा HIVE_ISYS_IRQ_CAP_UNIT_C_UNDEF_PH     13*/
#घोषणा HIVE_ISYS_IRQ_ACQ_UNIT_SOP_MISMATCH   12
/*#घोषणा HIVE_ISYS_IRQ_ACQ_UNIT_UNDEF_PH       15*/
#घोषणा HIVE_ISYS_IRQ_INP_CTRL_CAPA           13
#घोषणा HIVE_ISYS_IRQ_INP_CTRL_CAPB           14
#घोषणा HIVE_ISYS_IRQ_INP_CTRL_CAPC           15
#घोषणा HIVE_ISYS_IRQ_CIO2AHB                 16
#घोषणा HIVE_ISYS_IRQ_DMA_BIT_ID              17
#घोषणा HIVE_ISYS_IRQ_STREAM_MON_BIT_ID       18
#घोषणा HIVE_ISYS_IRQ_NUM_BITS                19

/* DMA */
#घोषणा HIVE_ISYS_DMA_CHANNEL                  0
#घोषणा HIVE_ISYS_DMA_IBUF_DDR_CONN            0
#घोषणा HIVE_ISYS_DMA_HEIGHT                   1
#घोषणा HIVE_ISYS_DMA_ELEMS                    1 /* both master buses of same width */
#घोषणा HIVE_ISYS_DMA_STRIDE                   0 /* no stride required as height is fixed to 1 */
#घोषणा HIVE_ISYS_DMA_CROP                     0 /* no cropping */
#घोषणा HIVE_ISYS_DMA_EXTENSION                0 /* no extension as elem width is same on both side */

#पूर्ण_अगर /* _input_प्रणाली_defs_h */
