<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB 338x super/high/full speed USB device controller.
 * Unlike many such controllers, this one talks PCI.
 *
 * Copyright (C) 2002 NetChip Technology, Inc. (http://www.netchip.com)
 * Copyright (C) 2003 David Brownell
 * Copyright (C) 2014 Ricarकरो Ribalda - Qtechnology/AS
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित __LINUX_USB_USB338X_H
#घोषणा __LINUX_USB_USB338X_H

#समावेश <linux/usb/net2280.h>

/*
 * Extra defined bits क्रम net2280 रेजिस्टरs
 */
#घोषणा     SCRATCH			      0x0b

#घोषणा     DEFECT7374_FSM_FIELD                28
#घोषणा     SUPER_SPEED				 8
#घोषणा     DMA_REQUEST_OUTSTANDING              5
#घोषणा     DMA_PAUSE_DONE_INTERRUPT            26
#घोषणा     SET_ISOCHRONOUS_DELAY               24
#घोषणा     SET_SEL                             22
#घोषणा     SUPER_SPEED_MODE                     8

/*ep_cfg*/
#घोषणा     MAX_BURST_SIZE                      24
#घोषणा     EP_FIFO_BYTE_COUNT                  16
#घोषणा     IN_ENDPOINT_ENABLE                  14
#घोषणा     IN_ENDPOINT_TYPE                    12
#घोषणा     OUT_ENDPOINT_ENABLE                 10
#घोषणा     OUT_ENDPOINT_TYPE                    8
#घोषणा USB3380_EP_CFG_MASK_IN ((0x3 << IN_ENDPOINT_TYPE) | \
				BIT(IN_ENDPOINT_ENABLE))
#घोषणा USB3380_EP_CFG_MASK_OUT ((0x3 << OUT_ENDPOINT_TYPE) | \
				BIT(OUT_ENDPOINT_ENABLE))

काष्ठा usb338x_usb_ext_regs अणु
	u32     usbclass;
#घोषणा     DEVICE_PROTOCOL                     16
#घोषणा     DEVICE_SUB_CLASS                     8
#घोषणा     DEVICE_CLASS                         0
	u32     ss_sel;
#घोषणा     U2_SYSTEM_EXIT_LATENCY               8
#घोषणा     U1_SYSTEM_EXIT_LATENCY               0
	u32     ss_del;
#घोषणा     U2_DEVICE_EXIT_LATENCY               8
#घोषणा     U1_DEVICE_EXIT_LATENCY               0
	u32     usb2lpm;
#घोषणा     USB_L1_LPM_HIRD                      2
#घोषणा     USB_L1_LPM_REMOTE_WAKE               1
#घोषणा     USB_L1_LPM_SUPPORT                   0
	u32     usb3belt;
#घोषणा     BELT_MULTIPLIER                     10
#घोषणा     BEST_EFFORT_LATENCY_TOLERANCE        0
	u32     usbctl2;
#घोषणा     LTM_ENABLE                           7
#घोषणा     U2_ENABLE                            6
#घोषणा     U1_ENABLE                            5
#घोषणा     FUNCTION_SUSPEND                     4
#घोषणा     USB3_CORE_ENABLE                     3
#घोषणा     USB2_CORE_ENABLE                     2
#घोषणा     SERIAL_NUMBER_STRING_ENABLE          0
	u32     in_समयout;
#घोषणा     GPEP3_TIMEOUT                       19
#घोषणा     GPEP2_TIMEOUT                       18
#घोषणा     GPEP1_TIMEOUT                       17
#घोषणा     GPEP0_TIMEOUT                       16
#घोषणा     GPEP3_TIMEOUT_VALUE                 13
#घोषणा     GPEP3_TIMEOUT_ENABLE                12
#घोषणा     GPEP2_TIMEOUT_VALUE                  9
#घोषणा     GPEP2_TIMEOUT_ENABLE                 8
#घोषणा     GPEP1_TIMEOUT_VALUE                  5
#घोषणा     GPEP1_TIMEOUT_ENABLE                 4
#घोषणा     GPEP0_TIMEOUT_VALUE                  1
#घोषणा     GPEP0_TIMEOUT_ENABLE                 0
	u32     isodelay;
#घोषणा     ISOCHRONOUS_DELAY                    0
पूर्ण __packed;

काष्ठा usb338x_fअगरo_regs अणु
	/* offset 0x0500, 0x0520, 0x0540, 0x0560, 0x0580 */
	u32     ep_fअगरo_size_base;
#घोषणा     IN_FIFO_BASE_ADDRESS                                22
#घोषणा     IN_FIFO_SIZE                                        16
#घोषणा     OUT_FIFO_BASE_ADDRESS                               6
#घोषणा     OUT_FIFO_SIZE                                       0
	u32     ep_fअगरo_out_wrptr;
	u32     ep_fअगरo_out_rdptr;
	u32     ep_fअगरo_in_wrptr;
	u32     ep_fअगरo_in_rdptr;
	u32     unused[3];
पूर्ण __packed;


/* Link layer */
काष्ठा usb338x_ll_regs अणु
	/* offset 0x700 */
	u32   ll_ltssm_ctrl1;
	u32   ll_ltssm_ctrl2;
	u32   ll_ltssm_ctrl3;
	u32   unused1;

	/* 0x710 */
	u32   unused2;
	u32   ll_general_ctrl0;
	u32   ll_general_ctrl1;
#घोषणा     PM_U3_AUTO_EXIT                                     29
#घोषणा     PM_U2_AUTO_EXIT                                     28
#घोषणा     PM_U1_AUTO_EXIT                                     27
#घोषणा     PM_FORCE_U2_ENTRY                                   26
#घोषणा     PM_FORCE_U1_ENTRY                                   25
#घोषणा     PM_LGO_COLLISION_SEND_LAU                           24
#घोषणा     PM_सूची_LINK_REJECT                                  23
#घोषणा     PM_FORCE_LINK_ACCEPT                                22
#घोषणा     PM_सूची_ENTRY_U3                                     20
#घोषणा     PM_सूची_ENTRY_U2                                     19
#घोषणा     PM_सूची_ENTRY_U1                                     18
#घोषणा     PM_U2_ENABLE                                        17
#घोषणा     PM_U1_ENABLE                                        16
#घोषणा     SKP_THRESHOLD_ADJUST_FMW                            8
#घोषणा     RESEND_DPP_ON_LRTY_FMW                              7
#घोषणा     DL_BIT_VALUE_FMW                                    6
#घोषणा     FORCE_DL_BIT                                        5
	u32   ll_general_ctrl2;
#घोषणा     SELECT_INVERT_LANE_POLARITY                         7
#घोषणा     FORCE_INVERT_LANE_POLARITY                          6

	/* 0x720 */
	u32   ll_general_ctrl3;
	u32   ll_general_ctrl4;
	u32   ll_error_gen;
	u32   unused3;

	/* 0x730 */
	u32   unused4[4];

	/* 0x740 */
	u32   unused5[2];
	u32   ll_lfps_5;
#घोषणा     TIMER_LFPS_6US                                      16
	u32   ll_lfps_6;
#घोषणा     TIMER_LFPS_80US                                     0

	/* 0x750 */
	u32   unused6[8];

	/* 0x770 */
	u32   unused7[3];
	u32   ll_tsn_counters_2;
#घोषणा     HOT_TX_NORESET_TS2                                  24

	/* 0x780 */
	u32   ll_tsn_counters_3;
#घोषणा     HOT_RX_RESET_TS2                                    0
	u32   unused8[3];

	/* 0x790 */
	u32   unused9;
	u32   ll_lfps_समयrs_2;
#घोषणा     LFPS_TIMERS_2_WORKAROUND_VALUE			0x084d
	u32   unused10;
	u32   ll_tsn_chicken_bit;
#घोषणा     RECOVERY_IDLE_TO_RECOVER_FMW                        3
पूर्ण __packed;

/* protocol layer */
काष्ठा usb338x_pl_regs अणु
	/* offset 0x800 */
	u32   pl_reg_1;
	u32   pl_reg_2;
	u32   pl_reg_3;
	u32   pl_reg_4;
	u32   pl_ep_ctrl;
	/* Protocol Layer Endpoपूर्णांक Control*/
#घोषणा     PL_EP_CTRL                                  0x810
#घोषणा     ENDPOINT_SELECT                             0
	/* [4:0] */
#घोषणा     EP_INITIALIZED                              16
#घोषणा     SEQUENCE_NUMBER_RESET                       17
#घोषणा     CLEAR_ACK_ERROR_CODE                        20
	u32   pl_reg_6;
	u32   pl_reg_7;
	u32   pl_reg_8;
	u32   pl_ep_status_1;
	/* Protocol Layer Endpoपूर्णांक Status 1*/
#घोषणा     PL_EP_STATUS_1                              0x820
#घोषणा     STATE                                       16
#घोषणा     ACK_GOOD_NORMAL                             0x11
#घोषणा     ACK_GOOD_MORE_ACKS_TO_COME                  0x16
	u32   pl_ep_status_2;
	u32   pl_ep_status_3;
	/* Protocol Layer Endpoपूर्णांक Status 3*/
#घोषणा     PL_EP_STATUS_3                              0x828
#घोषणा     SEQUENCE_NUMBER                             0
	u32   pl_ep_status_4;
	/* Protocol Layer Endpoपूर्णांक Status 4*/
#घोषणा     PL_EP_STATUS_4                              0x82c
	u32   pl_ep_cfg_4;
	/* Protocol Layer Endpoपूर्णांक Configuration 4*/
#घोषणा     PL_EP_CFG_4                                 0x830
#घोषणा     NON_CTRL_IN_TOLERATE_BAD_सूची                6
पूर्ण __packed;

#पूर्ण_अगर /* __LINUX_USB_USB338X_H */
