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

/*-*************************************
*  Dependencies
***************************************/
#समावेश "error_private.h"
#समावेश "zstd_internal.h" /* declaration of ZSTD_isError, ZSTD_getErrorName, ZSTD_getErrorCode, ZSTD_getErrorString, ZSTD_versionNumber */
#समावेश <linux/kernel.h>

/*=**************************************************************
*  Custom allocator
****************************************************************/

#घोषणा stack_push(stack, size)                                 \
	(अणु                                                      \
		व्योम *स्थिर ptr = ZSTD_PTR_ALIGN((stack)->ptr); \
		(stack)->ptr = (अक्षर *)ptr + (size);            \
		(stack)->ptr <= (stack)->end ? ptr : शून्य;      \
	पूर्ण)

ZSTD_customMem ZSTD_initStack(व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	ZSTD_customMem stackMem = अणुZSTD_stackAlloc, ZSTD_stackFree, workspaceपूर्ण;
	ZSTD_stack *stack = (ZSTD_stack *)workspace;
	/* Verअगरy preconditions */
	अगर (!workspace || workspaceSize < माप(ZSTD_stack) || workspace != ZSTD_PTR_ALIGN(workspace)) अणु
		ZSTD_customMem error = अणुशून्य, शून्य, शून्यपूर्ण;
		वापस error;
	पूर्ण
	/* Initialize the stack */
	stack->ptr = workspace;
	stack->end = (अक्षर *)workspace + workspaceSize;
	stack_push(stack, माप(ZSTD_stack));
	वापस stackMem;
पूर्ण

व्योम *ZSTD_stackAllocAll(व्योम *opaque, माप_प्रकार *size)
अणु
	ZSTD_stack *stack = (ZSTD_stack *)opaque;
	*size = (BYTE स्थिर *)stack->end - (BYTE *)ZSTD_PTR_ALIGN(stack->ptr);
	वापस stack_push(stack, *size);
पूर्ण

व्योम *ZSTD_stackAlloc(व्योम *opaque, माप_प्रकार size)
अणु
	ZSTD_stack *stack = (ZSTD_stack *)opaque;
	वापस stack_push(stack, size);
पूर्ण
व्योम ZSTD_stackFree(व्योम *opaque, व्योम *address)
अणु
	(व्योम)opaque;
	(व्योम)address;
पूर्ण

व्योम *ZSTD_दो_स्मृति(माप_प्रकार size, ZSTD_customMem customMem) अणु वापस customMem.customAlloc(customMem.opaque, size); पूर्ण

व्योम ZSTD_मुक्त(व्योम *ptr, ZSTD_customMem customMem)
अणु
	अगर (ptr != शून्य)
		customMem.customFree(customMem.opaque, ptr);
पूर्ण
