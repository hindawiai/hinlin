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

#अगर_अघोषित _input_चयन_2400_defs_h
#घोषणा _input_चयन_2400_defs_h

#घोषणा _HIVE_INPUT_SWITCH_GET_LUT_REG_ID(ch_id, fmt_type) (((ch_id) * 2) + ((fmt_type) >= 16))
#घोषणा _HIVE_INPUT_SWITCH_GET_LUT_REG_LSB(fmt_type)        (((fmt_type) % 16) * 2)

#घोषणा HIVE_INPUT_SWITCH_SELECT_NO_OUTPUT   0
#घोषणा HIVE_INPUT_SWITCH_SELECT_IF_PRIM     1
#घोषणा HIVE_INPUT_SWITCH_SELECT_IF_SEC      2
#घोषणा HIVE_INPUT_SWITCH_SELECT_STR_TO_MEM  3
#घोषणा HIVE_INPUT_SWITCH_VSELECT_NO_OUTPUT  0
#घोषणा HIVE_INPUT_SWITCH_VSELECT_IF_PRIM    1
#घोषणा HIVE_INPUT_SWITCH_VSELECT_IF_SEC     2
#घोषणा HIVE_INPUT_SWITCH_VSELECT_STR_TO_MEM 4

#पूर्ण_अगर /* _input_चयन_2400_defs_h */
