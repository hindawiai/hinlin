<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * apple.c - Apple ACPI quirks
 * Copyright (C) 2017 Lukas Wunner <lukas@wunner.de>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>
#समावेश <linux/uuid.h>

/* Apple _DSM device properties GUID */
अटल स्थिर guid_t apple_prp_guid =
	GUID_INIT(0xa0b5b7c6, 0x1318, 0x441c,
		  0xb0, 0xc9, 0xfe, 0x69, 0x5e, 0xaf, 0x94, 0x9b);

/**
 * acpi_extract_apple_properties - retrieve and convert Apple _DSM properties
 * @adev: ACPI device क्रम which to retrieve the properties
 *
 * Invoke Apple's custom _DSM once to check the protocol version and once more
 * to retrieve the properties.  They are marshalled up in a single package as
 * alternating key/value elements, unlike _DSD which stores them as a package
 * of 2-element packages.  Convert to _DSD क्रमmat and make them available under
 * the primary fwnode.
 */
व्योम acpi_extract_apple_properties(काष्ठा acpi_device *adev)
अणु
	अचिन्हित पूर्णांक i, j = 0, newsize = 0, numprops, numvalid;
	जोड़ acpi_object *props, *newprops;
	अचिन्हित दीर्घ *valid = शून्य;
	व्योम *मुक्त_space;

	अगर (!x86_apple_machine)
		वापस;

	props = acpi_evaluate_dsm_typed(adev->handle, &apple_prp_guid, 1, 0,
					शून्य, ACPI_TYPE_BUFFER);
	अगर (!props)
		वापस;

	अगर (!props->buffer.length)
		जाओ out_मुक्त;

	अगर (props->buffer.poपूर्णांकer[0] != 3) अणु
		acpi_handle_info(adev->handle, FW_INFO
				 "unsupported properties version %*ph\n",
				 props->buffer.length, props->buffer.poपूर्णांकer);
		जाओ out_मुक्त;
	पूर्ण

	ACPI_FREE(props);
	props = acpi_evaluate_dsm_typed(adev->handle, &apple_prp_guid, 1, 1,
					शून्य, ACPI_TYPE_PACKAGE);
	अगर (!props)
		वापस;

	numprops = props->package.count / 2;
	अगर (!numprops)
		जाओ out_मुक्त;

	valid = biपंचांगap_zalloc(numprops, GFP_KERNEL);
	अगर (!valid)
		जाओ out_मुक्त;

	/* newsize = key length + value length of each tuple */
	क्रम (i = 0; i < numprops; i++) अणु
		जोड़ acpi_object *key = &props->package.elements[i * 2];
		जोड़ acpi_object *val = &props->package.elements[i * 2 + 1];

		अगर ( key->type != ACPI_TYPE_STRING ||
		    (val->type != ACPI_TYPE_INTEGER &&
		     val->type != ACPI_TYPE_BUFFER))
			जारी; /* skip invalid properties */

		__set_bit(i, valid);
		newsize += key->string.length + 1;
		अगर ( val->type == ACPI_TYPE_BUFFER)
			newsize += val->buffer.length;
	पूर्ण

	numvalid = biपंचांगap_weight(valid, numprops);
	अगर (numprops > numvalid)
		acpi_handle_info(adev->handle, FW_INFO
				 "skipped %u properties: wrong type\n",
				 numprops - numvalid);
	अगर (numvalid == 0)
		जाओ out_मुक्त;

	/* newsize += top-level package + 3 objects क्रम each key/value tuple */
	newsize	+= (1 + 3 * numvalid) * माप(जोड़ acpi_object);
	newprops = ACPI_ALLOCATE_ZEROED(newsize);
	अगर (!newprops)
		जाओ out_मुक्त;

	/* layout: top-level package | packages | key/value tuples | strings */
	newprops->type = ACPI_TYPE_PACKAGE;
	newprops->package.count = numvalid;
	newprops->package.elements = &newprops[1];
	मुक्त_space = &newprops[1 + 3 * numvalid];

	क्रम_each_set_bit(i, valid, numprops) अणु
		जोड़ acpi_object *key = &props->package.elements[i * 2];
		जोड़ acpi_object *val = &props->package.elements[i * 2 + 1];
		अचिन्हित पूर्णांक k = 1 + numvalid + j * 2; /* index पूर्णांकo newprops */
		अचिन्हित पूर्णांक v = k + 1;

		newprops[1 + j].type = ACPI_TYPE_PACKAGE;
		newprops[1 + j].package.count = 2;
		newprops[1 + j].package.elements = &newprops[k];

		newprops[k].type = ACPI_TYPE_STRING;
		newprops[k].string.length = key->string.length;
		newprops[k].string.poपूर्णांकer = मुक्त_space;
		स_नकल(मुक्त_space, key->string.poपूर्णांकer, key->string.length);
		मुक्त_space += key->string.length + 1;

		newprops[v].type = val->type;
		अगर (val->type == ACPI_TYPE_INTEGER) अणु
			newprops[v].पूर्णांकeger.value = val->पूर्णांकeger.value;
		पूर्ण अन्यथा अणु
			newprops[v].buffer.length = val->buffer.length;
			newprops[v].buffer.poपूर्णांकer = मुक्त_space;
			स_नकल(मुक्त_space, val->buffer.poपूर्णांकer,
			       val->buffer.length);
			मुक्त_space += val->buffer.length;
		पूर्ण
		j++; /* count valid properties */
	पूर्ण
	WARN_ON(मुक्त_space != (व्योम *)newprops + newsize);

	adev->data.poपूर्णांकer = newprops;
	acpi_data_add_props(&adev->data, &apple_prp_guid, newprops);

out_मुक्त:
	ACPI_FREE(props);
	biपंचांगap_मुक्त(valid);
पूर्ण
