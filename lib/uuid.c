<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Unअगरied UUID/GUID definition
 *
 * Copyright (C) 2009, 2016 Intel Corp.
 *	Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/uuid.h>
#समावेश <linux/अक्रमom.h>

स्थिर guid_t guid_null;
EXPORT_SYMBOL(guid_null);
स्थिर uuid_t uuid_null;
EXPORT_SYMBOL(uuid_null);

स्थिर u8 guid_index[16] = अणु3,2,1,0,5,4,7,6,8,9,10,11,12,13,14,15पूर्ण;
स्थिर u8 uuid_index[16] = अणु0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15पूर्ण;

/**
 * generate_अक्रमom_uuid - generate a अक्रमom UUID
 * @uuid: where to put the generated UUID
 *
 * Ranकरोm UUID पूर्णांकerface
 *
 * Used to create a Boot ID or a fileप्रणाली UUID/GUID, but can be
 * useful क्रम other kernel drivers.
 */
व्योम generate_अक्रमom_uuid(अचिन्हित अक्षर uuid[16])
अणु
	get_अक्रमom_bytes(uuid, 16);
	/* Set UUID version to 4 --- truly अक्रमom generation */
	uuid[6] = (uuid[6] & 0x0F) | 0x40;
	/* Set the UUID variant to DCE */
	uuid[8] = (uuid[8] & 0x3F) | 0x80;
पूर्ण
EXPORT_SYMBOL(generate_अक्रमom_uuid);

व्योम generate_अक्रमom_guid(अचिन्हित अक्षर guid[16])
अणु
	get_अक्रमom_bytes(guid, 16);
	/* Set GUID version to 4 --- truly अक्रमom generation */
	guid[7] = (guid[7] & 0x0F) | 0x40;
	/* Set the GUID variant to DCE */
	guid[8] = (guid[8] & 0x3F) | 0x80;
पूर्ण
EXPORT_SYMBOL(generate_अक्रमom_guid);

अटल व्योम __uuid_gen_common(__u8 b[16])
अणु
	pअक्रमom_bytes(b, 16);
	/* reversion 0b10 */
	b[8] = (b[8] & 0x3F) | 0x80;
पूर्ण

व्योम guid_gen(guid_t *lu)
अणु
	__uuid_gen_common(lu->b);
	/* version 4 : अक्रमom generation */
	lu->b[7] = (lu->b[7] & 0x0F) | 0x40;
पूर्ण
EXPORT_SYMBOL_GPL(guid_gen);

व्योम uuid_gen(uuid_t *bu)
अणु
	__uuid_gen_common(bu->b);
	/* version 4 : अक्रमom generation */
	bu->b[6] = (bu->b[6] & 0x0F) | 0x40;
पूर्ण
EXPORT_SYMBOL_GPL(uuid_gen);

/**
 * uuid_is_valid - checks अगर a UUID string is valid
 * @uuid:	UUID string to check
 *
 * Description:
 * It checks अगर the UUID string is following the क्रमmat:
 *	xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
 *
 * where x is a hex digit.
 *
 * Return: true अगर input is valid UUID string.
 */
bool uuid_is_valid(स्थिर अक्षर *uuid)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < UUID_STRING_LEN; i++) अणु
		अगर (i == 8 || i == 13 || i == 18 || i == 23) अणु
			अगर (uuid[i] != '-')
				वापस false;
		पूर्ण अन्यथा अगर (!है_षष्ठादशक(uuid[i])) अणु
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(uuid_is_valid);

अटल पूर्णांक __uuid_parse(स्थिर अक्षर *uuid, __u8 b[16], स्थिर u8 ei[16])
अणु
	अटल स्थिर u8 si[16] = अणु0,2,4,6,9,11,14,16,19,21,24,26,28,30,32,34पूर्ण;
	अचिन्हित पूर्णांक i;

	अगर (!uuid_is_valid(uuid))
		वापस -EINVAL;

	क्रम (i = 0; i < 16; i++) अणु
		पूर्णांक hi = hex_to_bin(uuid[si[i] + 0]);
		पूर्णांक lo = hex_to_bin(uuid[si[i] + 1]);

		b[ei[i]] = (hi << 4) | lo;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक guid_parse(स्थिर अक्षर *uuid, guid_t *u)
अणु
	वापस __uuid_parse(uuid, u->b, guid_index);
पूर्ण
EXPORT_SYMBOL(guid_parse);

पूर्णांक uuid_parse(स्थिर अक्षर *uuid, uuid_t *u)
अणु
	वापस __uuid_parse(uuid, u->b, uuid_index);
पूर्ण
EXPORT_SYMBOL(uuid_parse);
