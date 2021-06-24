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

#अगर_अघोषित __TIMED_CTRL_H_INCLUDED__
#घोषणा __TIMED_CTRL_H_INCLUDED__

/*
 * This file is included on every cell अणुSP,ISP,hostपूर्ण and on every प्रणाली
 * that uses the input प्रणाली device(s). It defines the API to DLI bridge
 *
 * System and cell specअगरic पूर्णांकerfaces and अंतरभूत code are included
 * conditionally through Makefile path settings.
 *
 *  - .        प्रणाली and cell agnostic पूर्णांकerfaces, स्थिरants and identअगरiers
 *	- खुला:  प्रणाली agnostic, cell specअगरic पूर्णांकerfaces
 *	- निजी: प्रणाली dependent, cell specअगरic पूर्णांकerfaces & अंतरभूत implementations
 *	- global:  प्रणाली specअगरic स्थिरants and identअगरiers
 *	- local:   प्रणाली and cell specअगरic स्थिरants and identअगरiers
 */

#समावेश "system_local.h"
#समावेश "timed_ctrl_local.h"

#अगर_अघोषित __INLINE_TIMED_CTRL__
#घोषणा STORAGE_CLASS_TIMED_CTRL_H बाह्य
#घोषणा STORAGE_CLASS_TIMED_CTRL_C
#समावेश "timed_ctrl_public.h"
#अन्यथा  /* __INLINE_TIMED_CTRL__ */
#घोषणा STORAGE_CLASS_TIMED_CTRL_H अटल अंतरभूत
#घोषणा STORAGE_CLASS_TIMED_CTRL_C अटल अंतरभूत
#समावेश "timed_ctrl_private.h"
#पूर्ण_अगर /* __INLINE_TIMED_CTRL__ */

#पूर्ण_अगर /* __TIMED_CTRL_H_INCLUDED__ */
