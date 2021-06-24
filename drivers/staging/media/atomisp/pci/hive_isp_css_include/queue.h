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

#अगर_अघोषित __QUEUE_H_INCLUDED__
#घोषणा __QUEUE_H_INCLUDED__

/*
 * This file is included on every cell अणुSP,ISP,hostपूर्ण and is प्रणाली agnostic
 *
 * System and cell specअगरic पूर्णांकerfaces and अंतरभूत code are included
 * conditionally through Makefile path settings.
 *
 *  - प्रणाली and cell agnostic पूर्णांकerfaces, स्थिरants and identअगरiers
 *	- खुला:  cell specअगरic पूर्णांकerfaces
 *	- निजी: cell specअगरic अंतरभूत implementations
 *	- global:  पूर्णांकer cell स्थिरants and identअगरiers
 *	- local:   cell specअगरic स्थिरants and identअगरiers
 *
 */

#समावेश "queue_local.h"

#अगर_अघोषित __INLINE_QUEUE__
#घोषणा STORAGE_CLASS_QUEUE_H बाह्य
#घोषणा STORAGE_CLASS_QUEUE_C
/* #समावेश "queue_public.h" */
#समावेश "ia_css_queue.h"
#अन्यथा  /* __INLINE_QUEUE__ */
#घोषणा STORAGE_CLASS_QUEUE_H अटल अंतरभूत
#घोषणा STORAGE_CLASS_QUEUE_C अटल अंतरभूत
#समावेश "queue_private.h"
#पूर्ण_अगर /* __INLINE_QUEUE__ */

#पूर्ण_अगर /* __QUEUE_H_INCLUDED__ */
