<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsdump - AML debugger support क्रम resource काष्ठाures.
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsdump")

/*
 * All functions in this module are used by the AML Debugger only
 */
/* Local prototypes */
अटल व्योम acpi_rs_out_string(स्थिर अक्षर *title, स्थिर अक्षर *value);

अटल व्योम acpi_rs_out_पूर्णांकeger8(स्थिर अक्षर *title, u8 value);

अटल व्योम acpi_rs_out_पूर्णांकeger16(स्थिर अक्षर *title, u16 value);

अटल व्योम acpi_rs_out_पूर्णांकeger32(स्थिर अक्षर *title, u32 value);

अटल व्योम acpi_rs_out_पूर्णांकeger64(स्थिर अक्षर *title, u64 value);

अटल व्योम acpi_rs_out_title(स्थिर अक्षर *title);

अटल व्योम acpi_rs_dump_byte_list(u16 length, u8 *data);

अटल व्योम acpi_rs_dump_word_list(u16 length, u16 *data);

अटल व्योम acpi_rs_dump_dword_list(u8 length, u32 *data);

अटल व्योम acpi_rs_dump_लघु_byte_list(u8 length, u8 *data);

अटल व्योम
acpi_rs_dump_resource_source(काष्ठा acpi_resource_source *resource_source);

अटल व्योम
acpi_rs_dump_resource_label(अक्षर *title,
			    काष्ठा acpi_resource_label *resource_label);

अटल व्योम acpi_rs_dump_address_common(जोड़ acpi_resource_data *resource);

अटल व्योम
acpi_rs_dump_descriptor(व्योम *resource, काष्ठा acpi_rsdump_info *table);

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_dump_resource_list
 *
 * PARAMETERS:  resource_list       - Poपूर्णांकer to a resource descriptor list
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dispatches the काष्ठाure to the correct dump routine.
 *
 ******************************************************************************/

व्योम acpi_rs_dump_resource_list(काष्ठा acpi_resource *resource_list)
अणु
	u32 count = 0;
	u32 type;

	ACPI_FUNCTION_ENTRY();

	/* Check अगर debug output enabled */

	अगर (!ACPI_IS_DEBUG_ENABLED(ACPI_LV_RESOURCES, _COMPONENT)) अणु
		वापस;
	पूर्ण

	/* Walk list and dump all resource descriptors (END_TAG terminates) */

	करो अणु
		acpi_os_म_लिखो("\n[%02X] ", count);
		count++;

		/* Validate Type beक्रमe dispatch */

		type = resource_list->type;
		अगर (type > ACPI_RESOURCE_TYPE_MAX) अणु
			acpi_os_म_लिखो
			    ("Invalid descriptor type (%X) in resource list\n",
			     resource_list->type);
			वापस;
		पूर्ण अन्यथा अगर (!resource_list->type) अणु
			ACPI_ERROR((AE_INFO, "Invalid Zero Resource Type"));
			वापस;
		पूर्ण

		/* Sanity check the length. It must not be zero, or we loop क्रमever */

		अगर (!resource_list->length) अणु
			acpi_os_म_लिखो
			    ("Invalid zero length descriptor in resource list\n");
			वापस;
		पूर्ण

		/* Dump the resource descriptor */

		अगर (type == ACPI_RESOURCE_TYPE_SERIAL_BUS) अणु
			acpi_rs_dump_descriptor(&resource_list->data,
						acpi_gbl_dump_serial_bus_dispatch
						[resource_list->data.
						 common_serial_bus.type]);
		पूर्ण अन्यथा अणु
			acpi_rs_dump_descriptor(&resource_list->data,
						acpi_gbl_dump_resource_dispatch
						[type]);
		पूर्ण

		/* Poपूर्णांक to the next resource काष्ठाure */

		resource_list = ACPI_NEXT_RESOURCE(resource_list);

		/* Exit when END_TAG descriptor is reached */

	पूर्ण जबतक (type != ACPI_RESOURCE_TYPE_END_TAG);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_dump_irq_list
 *
 * PARAMETERS:  route_table     - Poपूर्णांकer to the routing table to dump.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक IRQ routing table
 *
 ******************************************************************************/

व्योम acpi_rs_dump_irq_list(u8 *route_table)
अणु
	काष्ठा acpi_pci_routing_table *prt_element;
	u8 count;

	ACPI_FUNCTION_ENTRY();

	/* Check अगर debug output enabled */

	अगर (!ACPI_IS_DEBUG_ENABLED(ACPI_LV_RESOURCES, _COMPONENT)) अणु
		वापस;
	पूर्ण

	prt_element = ACPI_CAST_PTR(काष्ठा acpi_pci_routing_table, route_table);

	/* Dump all table elements, Exit on zero length element */

	क्रम (count = 0; prt_element->length; count++) अणु
		acpi_os_म_लिखो("\n[%02X] PCI IRQ Routing Table Package\n",
			       count);
		acpi_rs_dump_descriptor(prt_element, acpi_rs_dump_prt);

		prt_element = ACPI_ADD_PTR(काष्ठा acpi_pci_routing_table,
					   prt_element, prt_element->length);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_dump_descriptor
 *
 * PARAMETERS:  resource            - Buffer containing the resource
 *              table               - Table entry to decode the resource
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump a resource descriptor based on a dump table entry.
 *
 ******************************************************************************/

अटल व्योम
acpi_rs_dump_descriptor(व्योम *resource, काष्ठा acpi_rsdump_info *table)
अणु
	u8 *target = शून्य;
	u8 *previous_target;
	स्थिर अक्षर *name;
	u8 count;

	/* First table entry must contain the table length (# of table entries) */

	count = table->offset;

	जबतक (count) अणु
		previous_target = target;
		target = ACPI_ADD_PTR(u8, resource, table->offset);
		name = table->name;

		चयन (table->opcode) अणु
		हाल ACPI_RSD_TITLE:
			/*
			 * Optional resource title
			 */
			अगर (table->name) अणु
				acpi_os_म_लिखो("%s Resource\n", name);
			पूर्ण
			अवरोध;

			/* Strings */

		हाल ACPI_RSD_LITERAL:

			acpi_rs_out_string(name,
					   ACPI_CAST_PTR(अक्षर, table->poपूर्णांकer));
			अवरोध;

		हाल ACPI_RSD_STRING:

			acpi_rs_out_string(name, ACPI_CAST_PTR(अक्षर, target));
			अवरोध;

			/* Data items, 8/16/32/64 bit */

		हाल ACPI_RSD_UINT8:

			अगर (table->poपूर्णांकer) अणु
				acpi_rs_out_string(name,
						   table->poपूर्णांकer[*target]);
			पूर्ण अन्यथा अणु
				acpi_rs_out_पूर्णांकeger8(name, ACPI_GET8(target));
			पूर्ण
			अवरोध;

		हाल ACPI_RSD_UINT16:

			acpi_rs_out_पूर्णांकeger16(name, ACPI_GET16(target));
			अवरोध;

		हाल ACPI_RSD_UINT32:

			acpi_rs_out_पूर्णांकeger32(name, ACPI_GET32(target));
			अवरोध;

		हाल ACPI_RSD_UINT64:

			acpi_rs_out_पूर्णांकeger64(name, ACPI_GET64(target));
			अवरोध;

			/* Flags: 1-bit and 2-bit flags supported */

		हाल ACPI_RSD_1BITFLAG:

			acpi_rs_out_string(name,
					   table->poपूर्णांकer[*target & 0x01]);
			अवरोध;

		हाल ACPI_RSD_2BITFLAG:

			acpi_rs_out_string(name,
					   table->poपूर्णांकer[*target & 0x03]);
			अवरोध;

		हाल ACPI_RSD_3BITFLAG:

			acpi_rs_out_string(name,
					   table->poपूर्णांकer[*target & 0x07]);
			अवरोध;

		हाल ACPI_RSD_6BITFLAG:

			acpi_rs_out_पूर्णांकeger8(name, (ACPI_GET8(target) & 0x3F));
			अवरोध;

		हाल ACPI_RSD_SHORTLIST:
			/*
			 * Short byte list (single line output) क्रम DMA and IRQ resources
			 * Note: The list length is obtained from the previous table entry
			 */
			अगर (previous_target) अणु
				acpi_rs_out_title(name);
				acpi_rs_dump_लघु_byte_list(*previous_target,
							     target);
			पूर्ण
			अवरोध;

		हाल ACPI_RSD_SHORTLISTX:
			/*
			 * Short byte list (single line output) क्रम GPIO venकरोr data
			 * Note: The list length is obtained from the previous table entry
			 */
			अगर (previous_target) अणु
				acpi_rs_out_title(name);
				acpi_rs_dump_लघु_byte_list(*previous_target,
							     *
							     (ACPI_CAST_INसूचीECT_PTR
							      (u8, target)));
			पूर्ण
			अवरोध;

		हाल ACPI_RSD_LONGLIST:
			/*
			 * Long byte list क्रम Venकरोr resource data
			 * Note: The list length is obtained from the previous table entry
			 */
			अगर (previous_target) अणु
				acpi_rs_dump_byte_list(ACPI_GET16
						       (previous_target),
						       target);
			पूर्ण
			अवरोध;

		हाल ACPI_RSD_DWORDLIST:
			/*
			 * Dword list क्रम Extended Interrupt resources
			 * Note: The list length is obtained from the previous table entry
			 */
			अगर (previous_target) अणु
				acpi_rs_dump_dword_list(*previous_target,
							ACPI_CAST_PTR(u32,
								      target));
			पूर्ण
			अवरोध;

		हाल ACPI_RSD_WORDLIST:
			/*
			 * Word list क्रम GPIO Pin Table
			 * Note: The list length is obtained from the previous table entry
			 */
			अगर (previous_target) अणु
				acpi_rs_dump_word_list(*previous_target,
						       *(ACPI_CAST_INसूचीECT_PTR
							 (u16, target)));
			पूर्ण
			अवरोध;

		हाल ACPI_RSD_ADDRESS:
			/*
			 * Common flags क्रम all Address resources
			 */
			acpi_rs_dump_address_common(ACPI_CAST_PTR
						    (जोड़ acpi_resource_data,
						     target));
			अवरोध;

		हाल ACPI_RSD_SOURCE:
			/*
			 * Optional resource_source क्रम Address resources
			 */
			acpi_rs_dump_resource_source(ACPI_CAST_PTR
						     (काष्ठा
								   acpi_resource_source,
								   target));
			अवरोध;

		हाल ACPI_RSD_LABEL:
			/*
			 * resource_label
			 */
			acpi_rs_dump_resource_label("Resource Label",
						    ACPI_CAST_PTR(काष्ठा
								  acpi_resource_label,
								  target));
			अवरोध;

		हाल ACPI_RSD_SOURCE_LABEL:
			/*
			 * resource_source_label
			 */
			acpi_rs_dump_resource_label("Resource Source Label",
						    ACPI_CAST_PTR(काष्ठा
								  acpi_resource_label,
								  target));
			अवरोध;

		शेष:

			acpi_os_म_लिखो("**** Invalid table opcode [%X] ****\n",
				       table->opcode);
			वापस;
		पूर्ण

		table++;
		count--;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_dump_resource_source
 *
 * PARAMETERS:  resource_source     - Poपूर्णांकer to a Resource Source काष्ठा
 *
 * RETURN:      None
 *
 * DESCRIPTION: Common routine क्रम dumping the optional resource_source and the
 *              corresponding resource_source_index.
 *
 ******************************************************************************/

अटल व्योम
acpi_rs_dump_resource_source(काष्ठा acpi_resource_source *resource_source)
अणु
	ACPI_FUNCTION_ENTRY();

	अगर (resource_source->index == 0xFF) अणु
		वापस;
	पूर्ण

	acpi_rs_out_पूर्णांकeger8("Resource Source Index", resource_source->index);

	acpi_rs_out_string("Resource Source",
			   resource_source->string_ptr ?
			   resource_source->string_ptr : "[Not Specified]");
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_dump_resource_label
 *
 * PARAMETERS:  title              - Title of the dumped resource field
 *              resource_label     - Poपूर्णांकer to a Resource Label काष्ठा
 *
 * RETURN:      None
 *
 * DESCRIPTION: Common routine क्रम dumping the resource_label
 *
 ******************************************************************************/

अटल व्योम
acpi_rs_dump_resource_label(अक्षर *title,
			    काष्ठा acpi_resource_label *resource_label)
अणु
	ACPI_FUNCTION_ENTRY();

	acpi_rs_out_string(title,
			   resource_label->string_ptr ?
			   resource_label->string_ptr : "[Not Specified]");
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_dump_address_common
 *
 * PARAMETERS:  resource        - Poपूर्णांकer to an पूर्णांकernal resource descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump the fields that are common to all Address resource
 *              descriptors
 *
 ******************************************************************************/

अटल व्योम acpi_rs_dump_address_common(जोड़ acpi_resource_data *resource)
अणु
	ACPI_FUNCTION_ENTRY();

	/* Decode the type-specअगरic flags */

	चयन (resource->address.resource_type) अणु
	हाल ACPI_MEMORY_RANGE:

		acpi_rs_dump_descriptor(resource, acpi_rs_dump_memory_flags);
		अवरोध;

	हाल ACPI_IO_RANGE:

		acpi_rs_dump_descriptor(resource, acpi_rs_dump_io_flags);
		अवरोध;

	हाल ACPI_BUS_NUMBER_RANGE:

		acpi_rs_out_string("Resource Type", "Bus Number Range");
		अवरोध;

	शेष:

		acpi_rs_out_पूर्णांकeger8("Resource Type",
				     (u8) resource->address.resource_type);
		अवरोध;
	पूर्ण

	/* Decode the general flags */

	acpi_rs_dump_descriptor(resource, acpi_rs_dump_general_flags);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_out*
 *
 * PARAMETERS:  title       - Name of the resource field
 *              value       - Value of the resource field
 *
 * RETURN:      None
 *
 * DESCRIPTION: Miscellaneous helper functions to consistently क्रमmat the
 *              output of the resource dump routines
 *
 ******************************************************************************/

अटल व्योम acpi_rs_out_string(स्थिर अक्षर *title, स्थिर अक्षर *value)
अणु

	acpi_os_म_लिखो("%27s : %s", title, value);
	अगर (!*value) अणु
		acpi_os_म_लिखो("[NULL NAMESTRING]");
	पूर्ण
	acpi_os_म_लिखो("\n");
पूर्ण

अटल व्योम acpi_rs_out_पूर्णांकeger8(स्थिर अक्षर *title, u8 value)
अणु
	acpi_os_म_लिखो("%27s : %2.2X\n", title, value);
पूर्ण

अटल व्योम acpi_rs_out_पूर्णांकeger16(स्थिर अक्षर *title, u16 value)
अणु

	acpi_os_म_लिखो("%27s : %4.4X\n", title, value);
पूर्ण

अटल व्योम acpi_rs_out_पूर्णांकeger32(स्थिर अक्षर *title, u32 value)
अणु

	acpi_os_म_लिखो("%27s : %8.8X\n", title, value);
पूर्ण

अटल व्योम acpi_rs_out_पूर्णांकeger64(स्थिर अक्षर *title, u64 value)
अणु

	acpi_os_म_लिखो("%27s : %8.8X%8.8X\n", title, ACPI_FORMAT_UINT64(value));
पूर्ण

अटल व्योम acpi_rs_out_title(स्थिर अक्षर *title)
अणु

	acpi_os_म_लिखो("%27s : ", title);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_dump*List
 *
 * PARAMETERS:  length      - Number of elements in the list
 *              data        - Start of the list
 *
 * RETURN:      None
 *
 * DESCRIPTION: Miscellaneous functions to dump lists of raw data
 *
 ******************************************************************************/

अटल व्योम acpi_rs_dump_byte_list(u16 length, u8 * data)
अणु
	u16 i;

	क्रम (i = 0; i < length; i++) अणु
		acpi_os_म_लिखो("%25s%2.2X : %2.2X\n", "Byte", i, data[i]);
	पूर्ण
पूर्ण

अटल व्योम acpi_rs_dump_लघु_byte_list(u8 length, u8 * data)
अणु
	u8 i;

	क्रम (i = 0; i < length; i++) अणु
		acpi_os_म_लिखो("%X ", data[i]);
	पूर्ण

	acpi_os_म_लिखो("\n");
पूर्ण

अटल व्योम acpi_rs_dump_dword_list(u8 length, u32 * data)
अणु
	u8 i;

	क्रम (i = 0; i < length; i++) अणु
		acpi_os_म_लिखो("%25s%2.2X : %8.8X\n", "Dword", i, data[i]);
	पूर्ण
पूर्ण

अटल व्योम acpi_rs_dump_word_list(u16 length, u16 *data)
अणु
	u16 i;

	क्रम (i = 0; i < length; i++) अणु
		acpi_os_म_लिखो("%25s%2.2X : %4.4X\n", "Word", i, data[i]);
	पूर्ण
पूर्ण
