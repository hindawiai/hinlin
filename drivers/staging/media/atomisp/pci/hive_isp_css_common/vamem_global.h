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

#अगर_अघोषित __VAMEM_GLOBAL_H_INCLUDED__
#घोषणा __VAMEM_GLOBAL_H_INCLUDED__

#समावेश <type_support.h>

#घोषणा IS_VAMEM_VERSION_2

/* (log) stepsize of linear पूर्णांकerpolation */
#घोषणा VAMEM_INTERP_STEP_LOG2	4
#घोषणा VAMEM_INTERP_STEP		BIT(VAMEM_INTERP_STEP_LOG2)
/* (physical) size of the tables */
#घोषणा VAMEM_TABLE_UNIT_SIZE	((1 << (ISP_VAMEM_ADDRESS_BITS - VAMEM_INTERP_STEP_LOG2)) + 1)
/* (logical) size of the tables */
#घोषणा VAMEM_TABLE_UNIT_STEP	((VAMEM_TABLE_UNIT_SIZE - 1) << 1)
/* Number of tables */
#घोषणा VAMEM_TABLE_UNIT_COUNT	(ISP_VAMEM_DEPTH / VAMEM_TABLE_UNIT_STEP)

प्रकार u16				vamem_data_t;

#पूर्ण_अगर /* __VAMEM_GLOBAL_H_INCLUDED__ */
