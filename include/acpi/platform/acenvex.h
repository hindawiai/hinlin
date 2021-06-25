<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acenvex.h - Extra host and compiler configuration
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACENVEX_H__
#घोषणा __ACENVEX_H__

/*! [Begin] no source code translation */

/******************************************************************************
 *
 * Extra host configuration files. All ACPICA headers are included beक्रमe
 * including these files.
 *
 *****************************************************************************/

#अगर defined(_LINUX) || defined(__linux__)
#समावेश <acpi/platक्रमm/aclinuxex.h>

#या_अगर defined(__DragonFly__)
#समावेश "acdragonflyex.h"

/*
 * EFI applications can be built with -nostdlib, in this हाल, it must be
 * included after including all other host environmental definitions, in
 * order to override the definitions.
 */
#या_अगर defined(_AED_EFI) || defined(_GNU_EFI) || defined(_EDK2_EFI)
#समावेश "acefiex.h"

#पूर्ण_अगर

#अगर defined(__GNUC__) && !defined(__INTEL_COMPILER)
#समावेश "acgccex.h"

#या_अगर defined(_MSC_VER)
#समावेश "acmsvcex.h"

#पूर्ण_अगर

/*! [End] no source code translation !*/

#पूर्ण_अगर				/* __ACENVEX_H__ */
