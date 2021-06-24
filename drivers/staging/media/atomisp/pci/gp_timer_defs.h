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

#अगर_अघोषित _gp_समयr_defs_h
#घोषणा _gp_समयr_defs_h

#घोषणा _HRT_GP_TIMER_REG_ALIGN 4

#घोषणा HIVE_GP_TIMER_RESET_REG_IDX                              0
#घोषणा HIVE_GP_TIMER_OVERALL_ENABLE_REG_IDX                     1
#घोषणा HIVE_GP_TIMER_ENABLE_REG_IDX(समयr)                     (HIVE_GP_TIMER_OVERALL_ENABLE_REG_IDX + 1 + समयr)
#घोषणा HIVE_GP_TIMER_VALUE_REG_IDX(समयr, समयrs)               (HIVE_GP_TIMER_ENABLE_REG_IDX(समयrs) + समयr)
#घोषणा HIVE_GP_TIMER_COUNT_TYPE_REG_IDX(समयr, समयrs)          (HIVE_GP_TIMER_VALUE_REG_IDX(समयrs, समयrs) + समयr)
#घोषणा HIVE_GP_TIMER_SIGNAL_SELECT_REG_IDX(समयr, समयrs)       (HIVE_GP_TIMER_COUNT_TYPE_REG_IDX(समयrs, समयrs) + समयr)
#घोषणा HIVE_GP_TIMER_IRQ_TRIGGER_VALUE_REG_IDX(irq, समयrs)     (HIVE_GP_TIMER_SIGNAL_SELECT_REG_IDX(समयrs, समयrs) + irq)
#घोषणा HIVE_GP_TIMER_IRQ_TIMER_SELECT_REG_IDX(irq, समयrs, irqs) (HIVE_GP_TIMER_IRQ_TRIGGER_VALUE_REG_IDX(irqs, समयrs) + irq)
#घोषणा HIVE_GP_TIMER_IRQ_ENABLE_REG_IDX(irq, समयrs, irqs)       (HIVE_GP_TIMER_IRQ_TIMER_SELECT_REG_IDX(irqs, समयrs, irqs) + irq)

#घोषणा HIVE_GP_TIMER_COUNT_TYPE_HIGH                            0
#घोषणा HIVE_GP_TIMER_COUNT_TYPE_LOW                             1
#घोषणा HIVE_GP_TIMER_COUNT_TYPE_POSEDGE                         2
#घोषणा HIVE_GP_TIMER_COUNT_TYPE_NEGEDGE                         3
#घोषणा HIVE_GP_TIMER_COUNT_TYPES                                4

#पूर्ण_अगर /* _gp_समयr_defs_h */
