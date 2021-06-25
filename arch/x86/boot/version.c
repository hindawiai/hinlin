<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * Kernel version string
 */

#समावेश "boot.h"
#समावेश <generated/utsrelease.h>
#समावेश <generated/compile.h>

स्थिर अक्षर kernel_version[] =
	UTS_RELEASE " (" LINUX_COMPILE_BY "@" LINUX_COMPILE_HOST ") "
	UTS_VERSION;
