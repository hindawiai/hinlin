<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * acpi_lpat.h - LPAT table processing functions
 *
 * Copyright (C) 2015 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित ACPI_LPAT_H
#घोषणा ACPI_LPAT_H

काष्ठा acpi_lpat अणु
	पूर्णांक temp;
	पूर्णांक raw;
पूर्ण;

काष्ठा acpi_lpat_conversion_table अणु
	काष्ठा acpi_lpat *lpat;
	पूर्णांक lpat_count;
पूर्ण;

#अगर_घोषित CONFIG_ACPI

पूर्णांक acpi_lpat_raw_to_temp(काष्ठा acpi_lpat_conversion_table *lpat_table,
			  पूर्णांक raw);
पूर्णांक acpi_lpat_temp_to_raw(काष्ठा acpi_lpat_conversion_table *lpat_table,
			  पूर्णांक temp);
काष्ठा acpi_lpat_conversion_table *acpi_lpat_get_conversion_table(acpi_handle
								  handle);
व्योम acpi_lpat_मुक्त_conversion_table(काष्ठा acpi_lpat_conversion_table
				     *lpat_table);

#अन्यथा
अटल पूर्णांक acpi_lpat_raw_to_temp(काष्ठा acpi_lpat_conversion_table *lpat_table,
				 पूर्णांक raw)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_lpat_temp_to_raw(काष्ठा acpi_lpat_conversion_table *lpat_table,
				 पूर्णांक temp)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा acpi_lpat_conversion_table *acpi_lpat_get_conversion_table(
							acpi_handle handle)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम acpi_lpat_मुक्त_conversion_table(काष्ठा acpi_lpat_conversion_table
					    *lpat_table)
अणु
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
