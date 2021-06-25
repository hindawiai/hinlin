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

#अगर_अघोषित _HRT_DEFS_H_
#घोषणा _HRT_DEFS_H_

#अगर_अघोषित HRTCAT
#घोषणा _HRTCAT(m, n)     m##n
#घोषणा HRTCAT(m, n)      _HRTCAT(m, n)
#पूर्ण_अगर

#अगर_अघोषित HRTSTR
#घोषणा _HRTSTR(x)   #x
#घोषणा HRTSTR(x)    _HRTSTR(x)
#पूर्ण_अगर

#अगर_अघोषित HRTMIN
#घोषणा HRTMIN(a, b) (((a) < (b)) ? (a) : (b))
#पूर्ण_अगर

#अगर_अघोषित HRTMAX
#घोषणा HRTMAX(a, b) (((a) > (b)) ? (a) : (b))
#पूर्ण_अगर

#पूर्ण_अगर /* _HRT_DEFS_H_ */
