<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: accommon.h - Common include files क्रम generation of ACPICA source
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACCOMMON_H__
#घोषणा __ACCOMMON_H__

/*
 * Common set of includes क्रम all ACPICA source files.
 * We put them here because we करोn't want to duplicate them
 * in the source code again and again.
 *
 * Note: The order of these include files is important.
 */
#समावेश <acpi/acconfig.h>	/* Global configuration स्थिरants */
#समावेश "acmacros.h"		/* C macros */
#समावेश "aclocal.h"		/* Internal data types */
#समावेश "acobject.h"		/* ACPI पूर्णांकernal object */
#समावेश "acstruct.h"		/* Common काष्ठाures */
#समावेश "acglobal.h"		/* All global variables */
#समावेश "achware.h"		/* Hardware defines and पूर्णांकerfaces */
#समावेश "acutils.h"		/* Utility पूर्णांकerfaces */
#अगर_अघोषित ACPI_USE_SYSTEM_CLIBRARY
#समावेश "acclib.h"		/* C library पूर्णांकerfaces */
#पूर्ण_अगर				/* !ACPI_USE_SYSTEM_CLIBRARY */

#पूर्ण_अगर				/* __ACCOMMON_H__ */
