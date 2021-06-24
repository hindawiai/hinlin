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

#अगर_अघोषित __ISYS_IRQ_GLOBAL_H__
#घोषणा __ISYS_IRQ_GLOBAL_H__

#अगर defined(ISP2401)

/* Register offset/index from base location */
#घोषणा ISYS_IRQ_EDGE_REG_IDX		(0)
#घोषणा ISYS_IRQ_MASK_REG_IDX		(ISYS_IRQ_EDGE_REG_IDX + 1)
#घोषणा ISYS_IRQ_STATUS_REG_IDX		(ISYS_IRQ_EDGE_REG_IDX + 2)
#घोषणा ISYS_IRQ_CLEAR_REG_IDX		(ISYS_IRQ_EDGE_REG_IDX + 3)
#घोषणा ISYS_IRQ_ENABLE_REG_IDX		(ISYS_IRQ_EDGE_REG_IDX + 4)
#घोषणा ISYS_IRQ_LEVEL_NO_REG_IDX	(ISYS_IRQ_EDGE_REG_IDX + 5)

/* Register values */
#घोषणा ISYS_IRQ_MASK_REG_VALUE		(0xFFFF)
#घोषणा ISYS_IRQ_CLEAR_REG_VALUE	(0xFFFF)
#घोषणा ISYS_IRQ_ENABLE_REG_VALUE	(0xFFFF)

#पूर्ण_अगर /* defined(ISP2401) */

#पूर्ण_अगर	/* __ISYS_IRQ_GLOBAL_H__ */
