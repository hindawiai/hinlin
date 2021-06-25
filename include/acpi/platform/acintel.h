<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acपूर्णांकel.h - VC specअगरic defines, etc.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACINTEL_H__
#घोषणा __ACINTEL_H__

/*
 * Use compiler specअगरic <मानकतर्क.स> is a good practice क्रम even when
 * -noमानक_निवेशc is specअगरied (i.e., ACPI_USE_STANDARD_HEADERS undefined.
 */
#अगर_अघोषित बहु_तर्क
#समावेश <मानकतर्क.स>
#पूर्ण_अगर

/* Configuration specअगरic to Intel 64-bit C compiler */

#घोषणा COMPILER_DEPENDENT_INT64    __पूर्णांक64
#घोषणा COMPILER_DEPENDENT_UINT64   अचिन्हित __पूर्णांक64
#घोषणा ACPI_INLINE                 __अंतरभूत

/*
 * Calling conventions:
 *
 * ACPI_SYSTEM_XFACE        - Interfaces to host OS (handlers, thपढ़ोs)
 * ACPI_EXTERNAL_XFACE      - External ACPI पूर्णांकerfaces
 * ACPI_INTERNAL_XFACE      - Internal ACPI पूर्णांकerfaces
 * ACPI_INTERNAL_VAR_XFACE  - Internal variable-parameter list पूर्णांकerfaces
 */
#घोषणा ACPI_SYSTEM_XFACE
#घोषणा ACPI_EXTERNAL_XFACE
#घोषणा ACPI_INTERNAL_XFACE
#घोषणा ACPI_INTERNAL_VAR_XFACE

/* remark 981 - opeअक्रमs evaluated in no particular order */
#आशय warning(disable:981)

/* warn C4100: unreferenced क्रमmal parameter */
#आशय warning(disable:4100)

/* warn C4127: conditional expression is स्थिरant */
#आशय warning(disable:4127)

/* warn C4706: assignment within conditional expression */
#आशय warning(disable:4706)

/* warn C4214: bit field types other than पूर्णांक */
#आशय warning(disable:4214)

#पूर्ण_अगर				/* __ACINTEL_H__ */
