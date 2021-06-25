<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
Support क्रम Intel Camera Imaging ISP subप्रणाली.
Copyright (c) 2010 - 2015, Intel Corporation.

This program is मुक्त software; you can redistribute it and/or modअगरy it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
more details.
*/

#अगर_अघोषित _INPUT_BUF_ISP_H_
#घोषणा _INPUT_BUF_ISP_H_

/* Temporary include, since IA_CSS_BINARY_MODE_COPY is still needed */
#समावेश "sh_css_defs.h"
#समावेश "isp_const.h" /* MAX_VECTORS_PER_INPUT_LINE */

#घोषणा INPUT_BUF_HEIGHT	2 /* द्विगुन buffer */
#घोषणा INPUT_BUF_LINES		2

#अगर_अघोषित ENABLE_CONTINUOUS
#घोषणा ENABLE_CONTINUOUS 0
#पूर्ण_अगर

/* In continuous mode, the input buffer must be a fixed size क्रम all binaries
 * and at a fixed address since it will be used by the SP. */
#घोषणा EXTRA_INPUT_VECTORS	2 /* For left padding */
#घोषणा MAX_VECTORS_PER_INPUT_LINE_CONT (CEIL_DIV(SH_CSS_MAX_SENSOR_WIDTH, ISP_NWAY) + EXTRA_INPUT_VECTORS)

/* The input buffer should be on a fixed address in vmem, क्रम continuous capture */
#घोषणा INPUT_BUF_ADDR 0x0

#पूर्ण_अगर /* _INPUT_BUF_ISP_H_ */
