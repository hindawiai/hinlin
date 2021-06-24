<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Module Name: acpidump.h - Include file क्रम acpi_dump utility
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

/*
 * Global variables. Defined in मुख्य.c only, बाह्यed in all other files
 */
#अगर_घोषित _DECLARE_GLOBALS
#घोषणा EXTERN
#घोषणा INIT_GLOBAL(a,b)        a=b
#अन्यथा
#घोषणा EXTERN                  बाह्य
#घोषणा INIT_GLOBAL(a,b)        a
#पूर्ण_अगर

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "actables.h"
#समावेश "acapps.h"

/* Globals */

EXTERN u8 INIT_GLOBAL(gbl_summary_mode, FALSE);
EXTERN u8 INIT_GLOBAL(gbl_verbose_mode, FALSE);
EXTERN u8 INIT_GLOBAL(gbl_binary_mode, FALSE);
EXTERN u8 INIT_GLOBAL(gbl_dump_customized_tables, TRUE);
EXTERN u8 INIT_GLOBAL(gbl_करो_not_dump_xsdt, FALSE);
EXTERN ACPI_खाता INIT_GLOBAL(gbl_output_file, शून्य);
EXTERN अक्षर INIT_GLOBAL(*gbl_output_filename, शून्य);
EXTERN u64 INIT_GLOBAL(gbl_rsdp_base, 0);

/* Action table used to defer requested options */

काष्ठा ap_dump_action अणु
	अक्षर *argument;
	u32 to_be_करोne;
पूर्ण;

#घोषणा AP_MAX_ACTIONS              32

#घोषणा AP_DUMP_ALL_TABLES          0
#घोषणा AP_DUMP_TABLE_BY_ADDRESS    1
#घोषणा AP_DUMP_TABLE_BY_NAME       2
#घोषणा AP_DUMP_TABLE_BY_खाता       3

#घोषणा AP_MAX_ACPI_खाताS           256	/* Prevent infinite loops */

/* Minimum FADT sizes क्रम various table addresses */

#घोषणा MIN_FADT_FOR_DSDT           (ACPI_FADT_OFFSET (dsdt) + माप (u32))
#घोषणा MIN_FADT_FOR_FACS           (ACPI_FADT_OFFSET (facs) + माप (u32))
#घोषणा MIN_FADT_FOR_XDSDT          (ACPI_FADT_OFFSET (Xdsdt) + माप (u64))
#घोषणा MIN_FADT_FOR_XFACS          (ACPI_FADT_OFFSET (Xfacs) + माप (u64))

/*
 * apdump - Table get/dump routines
 */
पूर्णांक ap_dump_table_from_file(अक्षर *pathname);

पूर्णांक ap_dump_table_by_name(अक्षर *signature);

पूर्णांक ap_dump_table_by_address(अक्षर *ascii_address);

पूर्णांक ap_dump_all_tables(व्योम);

u8 ap_is_valid_header(काष्ठा acpi_table_header *table);

u8 ap_is_valid_checksum(काष्ठा acpi_table_header *table);

u32 ap_get_table_length(काष्ठा acpi_table_header *table);

/*
 * apfiles - File I/O utilities
 */
पूर्णांक ap_खोलो_output_file(अक्षर *pathname);

पूर्णांक ap_ग_लिखो_to_binary_file(काष्ठा acpi_table_header *table, u32 instance);

काष्ठा acpi_table_header *ap_get_table_from_file(अक्षर *pathname,
						 u32 *file_size);
