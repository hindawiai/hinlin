<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * acpi_lpat.c - LPAT table processing functions
 *
 * Copyright (C) 2015 Intel Corporation. All rights reserved.
 */

#समावेश <linux/export.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/acpi_lpat.h>

/**
 * acpi_lpat_raw_to_temp(): Return temperature from raw value through
 * LPAT conversion table
 *
 * @lpat_table: the temperature_raw mapping table काष्ठाure
 * @raw: the raw value, used as a key to get the temperature from the
 *       above mapping table
 *
 * A positive converted temperature value will be वापसed on success,
 * a negative त्रुटि_सं will be वापसed in error हालs.
 */
पूर्णांक acpi_lpat_raw_to_temp(काष्ठा acpi_lpat_conversion_table *lpat_table,
			  पूर्णांक raw)
अणु
	पूर्णांक i, delta_temp, delta_raw, temp;
	काष्ठा acpi_lpat *lpat = lpat_table->lpat;

	क्रम (i = 0; i < lpat_table->lpat_count - 1; i++) अणु
		अगर ((raw >= lpat[i].raw && raw <= lpat[i+1].raw) ||
		    (raw <= lpat[i].raw && raw >= lpat[i+1].raw))
			अवरोध;
	पूर्ण

	अगर (i == lpat_table->lpat_count - 1)
		वापस -ENOENT;

	delta_temp = lpat[i+1].temp - lpat[i].temp;
	delta_raw = lpat[i+1].raw - lpat[i].raw;
	temp = lpat[i].temp + (raw - lpat[i].raw) * delta_temp / delta_raw;

	वापस temp;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_lpat_raw_to_temp);

/**
 * acpi_lpat_temp_to_raw(): Return raw value from temperature through
 * LPAT conversion table
 *
 * @lpat_table: the temperature_raw mapping table
 * @temp: the temperature, used as a key to get the raw value from the
 *        above mapping table
 *
 * The raw value will be वापसed on success,
 * a negative त्रुटि_सं will be वापसed in error हालs.
 */
पूर्णांक acpi_lpat_temp_to_raw(काष्ठा acpi_lpat_conversion_table *lpat_table,
			  पूर्णांक temp)
अणु
	पूर्णांक i, delta_temp, delta_raw, raw;
	काष्ठा acpi_lpat *lpat = lpat_table->lpat;

	क्रम (i = 0; i < lpat_table->lpat_count - 1; i++) अणु
		अगर (temp >= lpat[i].temp && temp <= lpat[i+1].temp)
			अवरोध;
	पूर्ण

	अगर (i ==  lpat_table->lpat_count - 1)
		वापस -ENOENT;

	delta_temp = lpat[i+1].temp - lpat[i].temp;
	delta_raw = lpat[i+1].raw - lpat[i].raw;
	raw = lpat[i].raw + (temp - lpat[i].temp) * delta_raw / delta_temp;

	वापस raw;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_lpat_temp_to_raw);

/**
 * acpi_lpat_get_conversion_table(): Parse ACPI LPAT table अगर present.
 *
 * @handle: Handle to acpi device
 *
 * Parse LPAT table to a काष्ठा of type acpi_lpat_table. On success
 * it वापसs a poपूर्णांकer to newly allocated table. This table must
 * be मुक्तd by the caller when finished processing, using a call to
 * acpi_lpat_मुक्त_conversion_table.
 */
काष्ठा acpi_lpat_conversion_table *acpi_lpat_get_conversion_table(acpi_handle
								  handle)
अणु
	काष्ठा acpi_lpat_conversion_table *lpat_table = शून्य;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj_p, *obj_e;
	पूर्णांक *lpat, i;
	acpi_status status;

	status = acpi_evaluate_object(handle, "LPAT", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस शून्य;

	obj_p = (जोड़ acpi_object *)buffer.poपूर्णांकer;
	अगर (!obj_p || (obj_p->type != ACPI_TYPE_PACKAGE) ||
	    (obj_p->package.count % 2) || (obj_p->package.count < 4))
		जाओ out;

	lpat = kसुस्मृति(obj_p->package.count, माप(पूर्णांक), GFP_KERNEL);
	अगर (!lpat)
		जाओ out;

	क्रम (i = 0; i < obj_p->package.count; i++) अणु
		obj_e = &obj_p->package.elements[i];
		अगर (obj_e->type != ACPI_TYPE_INTEGER) अणु
			kमुक्त(lpat);
			जाओ out;
		पूर्ण
		lpat[i] = (s64)obj_e->पूर्णांकeger.value;
	पूर्ण

	lpat_table = kzalloc(माप(*lpat_table), GFP_KERNEL);
	अगर (!lpat_table) अणु
		kमुक्त(lpat);
		जाओ out;
	पूर्ण

	lpat_table->lpat = (काष्ठा acpi_lpat *)lpat;
	lpat_table->lpat_count = obj_p->package.count / 2;

out:
	kमुक्त(buffer.poपूर्णांकer);
	वापस lpat_table;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_lpat_get_conversion_table);

/**
 * acpi_lpat_मुक्त_conversion_table(): Free LPAT table.
 *
 * @lpat_table: the temperature_raw mapping table काष्ठाure
 *
 * Frees the LPAT table previously allocated by a call to
 * acpi_lpat_get_conversion_table.
 */
व्योम acpi_lpat_मुक्त_conversion_table(काष्ठा acpi_lpat_conversion_table
				     *lpat_table)
अणु
	अगर (lpat_table) अणु
		kमुक्त(lpat_table->lpat);
		kमुक्त(lpat_table);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(acpi_lpat_मुक्त_conversion_table);
