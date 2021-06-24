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

#अगर_अघोषित __HMEM_GLOBAL_H_INCLUDED__
#घोषणा __HMEM_GLOBAL_H_INCLUDED__

#समावेश <type_support.h>

#घोषणा IS_HMEM_VERSION_1

#समावेश "isp.h"

/*
#घोषणा ISP_HIST_ADDRESS_BITS                  12
#घोषणा ISP_HIST_ALIGNMENT                     4
#घोषणा ISP_HIST_COMP_IN_PREC                  12
#घोषणा ISP_HIST_DEPTH                         1024
#घोषणा ISP_HIST_WIDTH                         24
#घोषणा ISP_HIST_COMPONENTS                    4
*/
#घोषणा ISP_HIST_ALIGNMENT_LOG2		2

#घोषणा HMEM_SIZE_LOG2		(ISP_HIST_ADDRESS_BITS - ISP_HIST_ALIGNMENT_LOG2)
#घोषणा HMEM_SIZE			ISP_HIST_DEPTH

#घोषणा HMEM_UNIT_SIZE		(HMEM_SIZE / ISP_HIST_COMPONENTS)
#घोषणा HMEM_UNIT_COUNT		ISP_HIST_COMPONENTS

#घोषणा HMEM_RANGE_LOG2		ISP_HIST_WIDTH
#घोषणा HMEM_RANGE			BIT(HMEM_RANGE_LOG2)

प्रकार u32			hmem_data_t;

#पूर्ण_अगर /* __HMEM_GLOBAL_H_INCLUDED__ */
