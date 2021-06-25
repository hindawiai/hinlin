<शैली गुरु>
/**
 * Copyright (c) 2016-present, Yann Collet, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of https://github.com/facebook/zstd.
 * An additional grant of patent rights can be found in the PATENTS file in the
 * same directory.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it under
 * the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation. This program is dual-licensed; you may select
 * either version 2 of the GNU General Public License ("GPL") or BSD license
 * ("BSD").
 */

/* Note : this module is expected to reमुख्य निजी, करो not expose it */

#अगर_अघोषित ERROR_H_MODULE
#घोषणा ERROR_H_MODULE

/* ****************************************
*  Dependencies
******************************************/
#समावेश <linux/types.h> /* माप_प्रकार */
#समावेश <linux/zstd.h>  /* क्रमागत list */

/* ****************************************
*  Compiler-specअगरic
******************************************/
#घोषणा ERR_STATIC अटल __attribute__((unused))

/*-****************************************
*  Customization (error_खुला.h)
******************************************/
प्रकार ZSTD_ErrorCode ERR_क्रमागत;
#घोषणा PREFIX(name) ZSTD_error_##name

/*-****************************************
*  Error codes handling
******************************************/
#घोषणा ERROR(name) ((माप_प्रकार)-PREFIX(name))

ERR_STATIC अचिन्हित ERR_isError(माप_प्रकार code) अणु वापस (code > ERROR(maxCode)); पूर्ण

ERR_STATIC ERR_क्रमागत ERR_getErrorCode(माप_प्रकार code)
अणु
	अगर (!ERR_isError(code))
		वापस (ERR_क्रमागत)0;
	वापस (ERR_क्रमागत)(0 - code);
पूर्ण

#पूर्ण_अगर /* ERROR_H_MODULE */
