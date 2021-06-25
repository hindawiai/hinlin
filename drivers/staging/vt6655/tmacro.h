<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: पंचांगacro.h
 *
 * Purpose: define basic common types and macros
 *
 * Author: Tevin Chen
 *
 * Date: May 21, 1996
 *
 */

#अगर_अघोषित __TMACRO_H__
#घोषणा __TMACRO_H__

/****** Common helper macros ***********************************************/

#अगर !defined(LOBYTE)
#घोषणा LOBYTE(w)           ((अचिन्हित अक्षर)(w))
#पूर्ण_अगर
#अगर !defined(HIBYTE)
#घोषणा HIBYTE(w)           ((अचिन्हित अक्षर)(((अचिन्हित लघु)(w) >> 8) & 0xFF))
#पूर्ण_अगर

#अगर !defined(LOWORD)
#घोषणा LOWORD(d)           ((अचिन्हित लघु)(d))
#पूर्ण_अगर
#अगर !defined(HIWORD)
#घोषणा HIWORD(d)           ((अचिन्हित लघु)((((अचिन्हित दीर्घ)(d)) >> 16) & 0xFFFF))
#पूर्ण_अगर

#घोषणा LODWORD(q)          ((q).u.dwLowDword)
#घोषणा HIDWORD(q)          ((q).u.dwHighDword)

#अगर !defined(MAKEWORD)
#घोषणा MAKEWORD(lb, hb)    ((अचिन्हित लघु)(((अचिन्हित अक्षर)(lb)) | (((अचिन्हित लघु)((अचिन्हित अक्षर)(hb))) << 8)))
#पूर्ण_अगर
#अगर !defined(MAKEDWORD)
#घोषणा MAKEDWORD(lw, hw)   ((अचिन्हित दीर्घ)(((अचिन्हित लघु)(lw)) | (((अचिन्हित दीर्घ)((अचिन्हित लघु)(hw))) << 16)))
#पूर्ण_अगर

#पूर्ण_अगर /* __TMACRO_H__ */
