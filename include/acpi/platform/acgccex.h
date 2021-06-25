<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acgccex.h - Extra GCC specअगरic defines, etc.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACGCCEX_H__
#घोषणा __ACGCCEX_H__

/*
 * Some versions of gcc implement म_अक्षर() with a buggy macro. So,
 * undef it here. Prevents error messages of this क्रमm (usually from the
 * file getopt.c):
 *
 * error: logical '&&' with non-zero स्थिरant will always evaluate as true
 */
#अगर_घोषित म_अक्षर
#अघोषित म_अक्षर
#पूर्ण_अगर

#पूर्ण_अगर				/* __ACGCCEX_H__ */
