<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * include/linux/platक्रमm_data/ams-delta-fiq.h
 *
 * Taken from the original Amstrad modअगरications to fiq.h
 *
 * Copyright (c) 2004 Amstrad Plc
 * Copyright (c) 2006 Matt Callow
 * Copyright (c) 2010 Janusz Krzysztofik
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#अगर_अघोषित __LINUX_PLATFORM_DATA_AMS_DELTA_FIQ_H
#घोषणा __LINUX_PLATFORM_DATA_AMS_DELTA_FIQ_H

/*
 * These are the offsets from the beginning of the fiq_buffer. They are put here
 * since the buffer and header need to be accessed by drivers servicing devices
 * which generate GPIO पूर्णांकerrupts - e.g. keyboard, modem, hook चयन.
 */
#घोषणा FIQ_MASK		 0
#घोषणा FIQ_STATE		 1
#घोषणा FIQ_KEYS_CNT		 2
#घोषणा FIQ_TAIL_OFFSET		 3
#घोषणा FIQ_HEAD_OFFSET		 4
#घोषणा FIQ_BUF_LEN		 5
#घोषणा FIQ_KEY			 6
#घोषणा FIQ_MISSED_KEYS		 7
#घोषणा FIQ_BUFFER_START	 8
#घोषणा FIQ_GPIO_INT_MASK	 9
#घोषणा FIQ_KEYS_HICNT		10
#घोषणा FIQ_IRQ_PEND		11
#घोषणा FIQ_SIR_CODE_L1		12
#घोषणा IRQ_SIR_CODE_L2		13

#घोषणा FIQ_CNT_INT_00		14
#घोषणा FIQ_CNT_INT_KEY		15
#घोषणा FIQ_CNT_INT_MDM		16
#घोषणा FIQ_CNT_INT_03		17
#घोषणा FIQ_CNT_INT_HSW		18
#घोषणा FIQ_CNT_INT_05		19
#घोषणा FIQ_CNT_INT_06		20
#घोषणा FIQ_CNT_INT_07		21
#घोषणा FIQ_CNT_INT_08		22
#घोषणा FIQ_CNT_INT_09		23
#घोषणा FIQ_CNT_INT_10		24
#घोषणा FIQ_CNT_INT_11		25
#घोषणा FIQ_CNT_INT_12		26
#घोषणा FIQ_CNT_INT_13		27
#घोषणा FIQ_CNT_INT_14		28
#घोषणा FIQ_CNT_INT_15		29

#घोषणा FIQ_CIRC_BUFF		30      /*Start of circular buffer */

#पूर्ण_अगर
