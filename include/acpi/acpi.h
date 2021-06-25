<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acpi.h - Master खुला include file used to पूर्णांकerface to ACPICA
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACPI_H__
#घोषणा __ACPI_H__

/*
 * Public include files क्रम use by code that will पूर्णांकerface to ACPICA.
 *
 * Inक्रमmation includes the ACPICA data types, names, exceptions, and
 * बाह्यal पूर्णांकerface prototypes. Also included are the definitions क्रम
 * all ACPI tables (FADT, MADT, etc.)
 *
 * Note: The order of these include files is important.
 */
#समावेश <acpi/platक्रमm/acenv.h>	/* Environment-specअगरic items */
#समावेश <acpi/acnames.h>		/* Common ACPI names and strings */
#समावेश <acpi/actypes.h>		/* ACPICA data types and काष्ठाures */
#समावेश <acpi/acexcep.h>		/* ACPICA exceptions */
#समावेश <acpi/actbl.h>		/* ACPI table definitions */
#समावेश <acpi/acrestyp.h>		/* Resource Descriptor काष्ठाs */
#समावेश <acpi/platक्रमm/acenvex.h>	/* Extra environment-specअगरic items */
#समावेश <acpi/acoutput.h>		/* Error output and Debug macros */
#समावेश <acpi/acpiosxf.h>		/* OSL पूर्णांकerfaces (ACPICA-to-OS) */
#समावेश <acpi/acpixf.h>		/* ACPI core subप्रणाली बाह्यal पूर्णांकerfaces */

#पूर्ण_अगर				/* __ACPI_H__ */
