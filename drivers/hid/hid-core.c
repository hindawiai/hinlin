<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID support क्रम Linux
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2012 Jiri Kosina
 */

/*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/input.h>
#समावेश <linux/रुको.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched.h>
#समावेश <linux/semaphore.h>

#समावेश <linux/hid.h>
#समावेश <linux/hiddev.h>
#समावेश <linux/hid-debug.h>
#समावेश <linux/hidraw.h>

#समावेश "hid-ids.h"

/*
 * Version Inक्रमmation
 */

#घोषणा DRIVER_DESC "HID core driver"

पूर्णांक hid_debug = 0;
module_param_named(debug, hid_debug, पूर्णांक, 0600);
MODULE_PARM_DESC(debug, "toggle HID debugging messages");
EXPORT_SYMBOL_GPL(hid_debug);

अटल पूर्णांक hid_ignore_special_drivers = 0;
module_param_named(ignore_special_drivers, hid_ignore_special_drivers, पूर्णांक, 0600);
MODULE_PARM_DESC(ignore_special_drivers, "Ignore any special drivers and handle all devices by generic driver");

/*
 * Register a new report क्रम a device.
 */

काष्ठा hid_report *hid_रेजिस्टर_report(काष्ठा hid_device *device,
				       अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक id,
				       अचिन्हित पूर्णांक application)
अणु
	काष्ठा hid_report_क्रमागत *report_क्रमागत = device->report_क्रमागत + type;
	काष्ठा hid_report *report;

	अगर (id >= HID_MAX_IDS)
		वापस शून्य;
	अगर (report_क्रमागत->report_id_hash[id])
		वापस report_क्रमागत->report_id_hash[id];

	report = kzalloc(माप(काष्ठा hid_report), GFP_KERNEL);
	अगर (!report)
		वापस शून्य;

	अगर (id != 0)
		report_क्रमागत->numbered = 1;

	report->id = id;
	report->type = type;
	report->size = 0;
	report->device = device;
	report->application = application;
	report_क्रमागत->report_id_hash[id] = report;

	list_add_tail(&report->list, &report_क्रमागत->report_list);

	वापस report;
पूर्ण
EXPORT_SYMBOL_GPL(hid_रेजिस्टर_report);

/*
 * Register a new field क्रम this report.
 */

अटल काष्ठा hid_field *hid_रेजिस्टर_field(काष्ठा hid_report *report, अचिन्हित usages)
अणु
	काष्ठा hid_field *field;

	अगर (report->maxfield == HID_MAX_FIELDS) अणु
		hid_err(report->device, "too many fields in report\n");
		वापस शून्य;
	पूर्ण

	field = kzalloc((माप(काष्ठा hid_field) +
			 usages * माप(काष्ठा hid_usage) +
			 usages * माप(अचिन्हित)), GFP_KERNEL);
	अगर (!field)
		वापस शून्य;

	field->index = report->maxfield++;
	report->field[field->index] = field;
	field->usage = (काष्ठा hid_usage *)(field + 1);
	field->value = (s32 *)(field->usage + usages);
	field->report = report;

	वापस field;
पूर्ण

/*
 * Open a collection. The type/usage is pushed on the stack.
 */

अटल पूर्णांक खोलो_collection(काष्ठा hid_parser *parser, अचिन्हित type)
अणु
	काष्ठा hid_collection *collection;
	अचिन्हित usage;
	पूर्णांक collection_index;

	usage = parser->local.usage[0];

	अगर (parser->collection_stack_ptr == parser->collection_stack_size) अणु
		अचिन्हित पूर्णांक *collection_stack;
		अचिन्हित पूर्णांक new_size = parser->collection_stack_size +
					HID_COLLECTION_STACK_SIZE;

		collection_stack = kपुनः_स्मृति(parser->collection_stack,
					    new_size * माप(अचिन्हित पूर्णांक),
					    GFP_KERNEL);
		अगर (!collection_stack)
			वापस -ENOMEM;

		parser->collection_stack = collection_stack;
		parser->collection_stack_size = new_size;
	पूर्ण

	अगर (parser->device->maxcollection == parser->device->collection_size) अणु
		collection = kदो_स्मृति(
				array3_size(माप(काष्ठा hid_collection),
					    parser->device->collection_size,
					    2),
				GFP_KERNEL);
		अगर (collection == शून्य) अणु
			hid_err(parser->device, "failed to reallocate collection array\n");
			वापस -ENOMEM;
		पूर्ण
		स_नकल(collection, parser->device->collection,
			माप(काष्ठा hid_collection) *
			parser->device->collection_size);
		स_रखो(collection + parser->device->collection_size, 0,
			माप(काष्ठा hid_collection) *
			parser->device->collection_size);
		kमुक्त(parser->device->collection);
		parser->device->collection = collection;
		parser->device->collection_size *= 2;
	पूर्ण

	parser->collection_stack[parser->collection_stack_ptr++] =
		parser->device->maxcollection;

	collection_index = parser->device->maxcollection++;
	collection = parser->device->collection + collection_index;
	collection->type = type;
	collection->usage = usage;
	collection->level = parser->collection_stack_ptr - 1;
	collection->parent_idx = (collection->level == 0) ? -1 :
		parser->collection_stack[collection->level - 1];

	अगर (type == HID_COLLECTION_APPLICATION)
		parser->device->maxapplication++;

	वापस 0;
पूर्ण

/*
 * Close a collection.
 */

अटल पूर्णांक बंद_collection(काष्ठा hid_parser *parser)
अणु
	अगर (!parser->collection_stack_ptr) अणु
		hid_err(parser->device, "collection stack underflow\n");
		वापस -EINVAL;
	पूर्ण
	parser->collection_stack_ptr--;
	वापस 0;
पूर्ण

/*
 * Climb up the stack, search क्रम the specअगरied collection type
 * and वापस the usage.
 */

अटल अचिन्हित hid_lookup_collection(काष्ठा hid_parser *parser, अचिन्हित type)
अणु
	काष्ठा hid_collection *collection = parser->device->collection;
	पूर्णांक n;

	क्रम (n = parser->collection_stack_ptr - 1; n >= 0; n--) अणु
		अचिन्हित index = parser->collection_stack[n];
		अगर (collection[index].type == type)
			वापस collection[index].usage;
	पूर्ण
	वापस 0; /* we know nothing about this usage type */
पूर्ण

/*
 * Concatenate usage which defines 16 bits or less with the
 * currently defined usage page to क्रमm a 32 bit usage
 */

अटल व्योम complete_usage(काष्ठा hid_parser *parser, अचिन्हित पूर्णांक index)
अणु
	parser->local.usage[index] &= 0xFFFF;
	parser->local.usage[index] |=
		(parser->global.usage_page & 0xFFFF) << 16;
पूर्ण

/*
 * Add a usage to the temporary parser table.
 */

अटल पूर्णांक hid_add_usage(काष्ठा hid_parser *parser, अचिन्हित usage, u8 size)
अणु
	अगर (parser->local.usage_index >= HID_MAX_USAGES) अणु
		hid_err(parser->device, "usage index exceeded\n");
		वापस -1;
	पूर्ण
	parser->local.usage[parser->local.usage_index] = usage;

	/*
	 * If Usage item only includes usage id, concatenate it with
	 * currently defined usage page
	 */
	अगर (size <= 2)
		complete_usage(parser, parser->local.usage_index);

	parser->local.usage_size[parser->local.usage_index] = size;
	parser->local.collection_index[parser->local.usage_index] =
		parser->collection_stack_ptr ?
		parser->collection_stack[parser->collection_stack_ptr - 1] : 0;
	parser->local.usage_index++;
	वापस 0;
पूर्ण

/*
 * Register a new field क्रम this report.
 */

अटल पूर्णांक hid_add_field(काष्ठा hid_parser *parser, अचिन्हित report_type, अचिन्हित flags)
अणु
	काष्ठा hid_report *report;
	काष्ठा hid_field *field;
	अचिन्हित पूर्णांक usages;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक application;

	application = hid_lookup_collection(parser, HID_COLLECTION_APPLICATION);

	report = hid_रेजिस्टर_report(parser->device, report_type,
				     parser->global.report_id, application);
	अगर (!report) अणु
		hid_err(parser->device, "hid_register_report failed\n");
		वापस -1;
	पूर्ण

	/* Handle both चिन्हित and अचिन्हित हालs properly */
	अगर ((parser->global.logical_minimum < 0 &&
		parser->global.logical_maximum <
		parser->global.logical_minimum) ||
		(parser->global.logical_minimum >= 0 &&
		(__u32)parser->global.logical_maximum <
		(__u32)parser->global.logical_minimum)) अणु
		dbg_hid("logical range invalid 0x%x 0x%x\n",
			parser->global.logical_minimum,
			parser->global.logical_maximum);
		वापस -1;
	पूर्ण

	offset = report->size;
	report->size += parser->global.report_size * parser->global.report_count;

	/* Total size check: Allow क्रम possible report index byte */
	अगर (report->size > (HID_MAX_BUFFER_SIZE - 1) << 3) अणु
		hid_err(parser->device, "report is too long\n");
		वापस -1;
	पूर्ण

	अगर (!parser->local.usage_index) /* Ignore padding fields */
		वापस 0;

	usages = max_t(अचिन्हित, parser->local.usage_index,
				 parser->global.report_count);

	field = hid_रेजिस्टर_field(report, usages);
	अगर (!field)
		वापस 0;

	field->physical = hid_lookup_collection(parser, HID_COLLECTION_PHYSICAL);
	field->logical = hid_lookup_collection(parser, HID_COLLECTION_LOGICAL);
	field->application = application;

	क्रम (i = 0; i < usages; i++) अणु
		अचिन्हित j = i;
		/* Duplicate the last usage we parsed अगर we have excess values */
		अगर (i >= parser->local.usage_index)
			j = parser->local.usage_index - 1;
		field->usage[i].hid = parser->local.usage[j];
		field->usage[i].collection_index =
			parser->local.collection_index[j];
		field->usage[i].usage_index = i;
		field->usage[i].resolution_multiplier = 1;
	पूर्ण

	field->maxusage = usages;
	field->flags = flags;
	field->report_offset = offset;
	field->report_type = report_type;
	field->report_size = parser->global.report_size;
	field->report_count = parser->global.report_count;
	field->logical_minimum = parser->global.logical_minimum;
	field->logical_maximum = parser->global.logical_maximum;
	field->physical_minimum = parser->global.physical_minimum;
	field->physical_maximum = parser->global.physical_maximum;
	field->unit_exponent = parser->global.unit_exponent;
	field->unit = parser->global.unit;

	वापस 0;
पूर्ण

/*
 * Read data value from item.
 */

अटल u32 item_udata(काष्ठा hid_item *item)
अणु
	चयन (item->size) अणु
	हाल 1: वापस item->data.u8;
	हाल 2: वापस item->data.u16;
	हाल 4: वापस item->data.u32;
	पूर्ण
	वापस 0;
पूर्ण

अटल s32 item_sdata(काष्ठा hid_item *item)
अणु
	चयन (item->size) अणु
	हाल 1: वापस item->data.s8;
	हाल 2: वापस item->data.s16;
	हाल 4: वापस item->data.s32;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Process a global item.
 */

अटल पूर्णांक hid_parser_global(काष्ठा hid_parser *parser, काष्ठा hid_item *item)
अणु
	__s32 raw_value;
	चयन (item->tag) अणु
	हाल HID_GLOBAL_ITEM_TAG_PUSH:

		अगर (parser->global_stack_ptr == HID_GLOBAL_STACK_SIZE) अणु
			hid_err(parser->device, "global environment stack overflow\n");
			वापस -1;
		पूर्ण

		स_नकल(parser->global_stack + parser->global_stack_ptr++,
			&parser->global, माप(काष्ठा hid_global));
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_POP:

		अगर (!parser->global_stack_ptr) अणु
			hid_err(parser->device, "global environment stack underflow\n");
			वापस -1;
		पूर्ण

		स_नकल(&parser->global, parser->global_stack +
			--parser->global_stack_ptr, माप(काष्ठा hid_global));
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_USAGE_PAGE:
		parser->global.usage_page = item_udata(item);
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_LOGICAL_MINIMUM:
		parser->global.logical_minimum = item_sdata(item);
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_LOGICAL_MAXIMUM:
		अगर (parser->global.logical_minimum < 0)
			parser->global.logical_maximum = item_sdata(item);
		अन्यथा
			parser->global.logical_maximum = item_udata(item);
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_PHYSICAL_MINIMUM:
		parser->global.physical_minimum = item_sdata(item);
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_PHYSICAL_MAXIMUM:
		अगर (parser->global.physical_minimum < 0)
			parser->global.physical_maximum = item_sdata(item);
		अन्यथा
			parser->global.physical_maximum = item_udata(item);
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_UNIT_EXPONENT:
		/* Many devices provide unit exponent as a two's complement
		 * nibble due to the common misunderstanding of HID
		 * specअगरication 1.11, 6.2.2.7 Global Items. Attempt to handle
		 * both this and the standard encoding. */
		raw_value = item_sdata(item);
		अगर (!(raw_value & 0xfffffff0))
			parser->global.unit_exponent = hid_snto32(raw_value, 4);
		अन्यथा
			parser->global.unit_exponent = raw_value;
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_UNIT:
		parser->global.unit = item_udata(item);
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_REPORT_SIZE:
		parser->global.report_size = item_udata(item);
		अगर (parser->global.report_size > 256) अणु
			hid_err(parser->device, "invalid report_size %d\n",
					parser->global.report_size);
			वापस -1;
		पूर्ण
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_REPORT_COUNT:
		parser->global.report_count = item_udata(item);
		अगर (parser->global.report_count > HID_MAX_USAGES) अणु
			hid_err(parser->device, "invalid report_count %d\n",
					parser->global.report_count);
			वापस -1;
		पूर्ण
		वापस 0;

	हाल HID_GLOBAL_ITEM_TAG_REPORT_ID:
		parser->global.report_id = item_udata(item);
		अगर (parser->global.report_id == 0 ||
		    parser->global.report_id >= HID_MAX_IDS) अणु
			hid_err(parser->device, "report_id %u is invalid\n",
				parser->global.report_id);
			वापस -1;
		पूर्ण
		वापस 0;

	शेष:
		hid_err(parser->device, "unknown global tag 0x%x\n", item->tag);
		वापस -1;
	पूर्ण
पूर्ण

/*
 * Process a local item.
 */

अटल पूर्णांक hid_parser_local(काष्ठा hid_parser *parser, काष्ठा hid_item *item)
अणु
	__u32 data;
	अचिन्हित n;
	__u32 count;

	data = item_udata(item);

	चयन (item->tag) अणु
	हाल HID_LOCAL_ITEM_TAG_DELIMITER:

		अगर (data) अणु
			/*
			 * We treat items beक्रमe the first delimiter
			 * as global to all usage sets (branch 0).
			 * In the moment we process only these global
			 * items and the first delimiter set.
			 */
			अगर (parser->local.delimiter_depth != 0) अणु
				hid_err(parser->device, "nested delimiters\n");
				वापस -1;
			पूर्ण
			parser->local.delimiter_depth++;
			parser->local.delimiter_branch++;
		पूर्ण अन्यथा अणु
			अगर (parser->local.delimiter_depth < 1) अणु
				hid_err(parser->device, "bogus close delimiter\n");
				वापस -1;
			पूर्ण
			parser->local.delimiter_depth--;
		पूर्ण
		वापस 0;

	हाल HID_LOCAL_ITEM_TAG_USAGE:

		अगर (parser->local.delimiter_branch > 1) अणु
			dbg_hid("alternative usage ignored\n");
			वापस 0;
		पूर्ण

		वापस hid_add_usage(parser, data, item->size);

	हाल HID_LOCAL_ITEM_TAG_USAGE_MINIMUM:

		अगर (parser->local.delimiter_branch > 1) अणु
			dbg_hid("alternative usage ignored\n");
			वापस 0;
		पूर्ण

		parser->local.usage_minimum = data;
		वापस 0;

	हाल HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM:

		अगर (parser->local.delimiter_branch > 1) अणु
			dbg_hid("alternative usage ignored\n");
			वापस 0;
		पूर्ण

		count = data - parser->local.usage_minimum;
		अगर (count + parser->local.usage_index >= HID_MAX_USAGES) अणु
			/*
			 * We करो not warn अगर the name is not set, we are
			 * actually pre-scanning the device.
			 */
			अगर (dev_name(&parser->device->dev))
				hid_warn(parser->device,
					 "ignoring exceeding usage max\n");
			data = HID_MAX_USAGES - parser->local.usage_index +
				parser->local.usage_minimum - 1;
			अगर (data <= 0) अणु
				hid_err(parser->device,
					"no more usage index available\n");
				वापस -1;
			पूर्ण
		पूर्ण

		क्रम (n = parser->local.usage_minimum; n <= data; n++)
			अगर (hid_add_usage(parser, n, item->size)) अणु
				dbg_hid("hid_add_usage failed\n");
				वापस -1;
			पूर्ण
		वापस 0;

	शेष:

		dbg_hid("unknown local item tag 0x%x\n", item->tag);
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Concatenate Usage Pages पूर्णांकo Usages where relevant:
 * As per specअगरication, 6.2.2.8: "When the parser encounters a मुख्य item it
 * concatenates the last declared Usage Page with a Usage to क्रमm a complete
 * usage value."
 */

अटल व्योम hid_concatenate_last_usage_page(काष्ठा hid_parser *parser)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक usage_page;
	अचिन्हित पूर्णांक current_page;

	अगर (!parser->local.usage_index)
		वापस;

	usage_page = parser->global.usage_page;

	/*
	 * Concatenate usage page again only अगर last declared Usage Page
	 * has not been alपढ़ोy used in previous usages concatenation
	 */
	क्रम (i = parser->local.usage_index - 1; i >= 0; i--) अणु
		अगर (parser->local.usage_size[i] > 2)
			/* Ignore extended usages */
			जारी;

		current_page = parser->local.usage[i] >> 16;
		अगर (current_page == usage_page)
			अवरोध;

		complete_usage(parser, i);
	पूर्ण
पूर्ण

/*
 * Process a मुख्य item.
 */

अटल पूर्णांक hid_parser_मुख्य(काष्ठा hid_parser *parser, काष्ठा hid_item *item)
अणु
	__u32 data;
	पूर्णांक ret;

	hid_concatenate_last_usage_page(parser);

	data = item_udata(item);

	चयन (item->tag) अणु
	हाल HID_MAIN_ITEM_TAG_BEGIN_COLLECTION:
		ret = खोलो_collection(parser, data & 0xff);
		अवरोध;
	हाल HID_MAIN_ITEM_TAG_END_COLLECTION:
		ret = बंद_collection(parser);
		अवरोध;
	हाल HID_MAIN_ITEM_TAG_INPUT:
		ret = hid_add_field(parser, HID_INPUT_REPORT, data);
		अवरोध;
	हाल HID_MAIN_ITEM_TAG_OUTPUT:
		ret = hid_add_field(parser, HID_OUTPUT_REPORT, data);
		अवरोध;
	हाल HID_MAIN_ITEM_TAG_FEATURE:
		ret = hid_add_field(parser, HID_FEATURE_REPORT, data);
		अवरोध;
	शेष:
		hid_warn(parser->device, "unknown main item tag 0x%x\n", item->tag);
		ret = 0;
	पूर्ण

	स_रखो(&parser->local, 0, माप(parser->local));	/* Reset the local parser environment */

	वापस ret;
पूर्ण

/*
 * Process a reserved item.
 */

अटल पूर्णांक hid_parser_reserved(काष्ठा hid_parser *parser, काष्ठा hid_item *item)
अणु
	dbg_hid("reserved item type, tag 0x%x\n", item->tag);
	वापस 0;
पूर्ण

/*
 * Free a report and all रेजिस्टरed fields. The field->usage and
 * field->value table's are allocated behind the field, so we need
 * only to मुक्त(field) itself.
 */

अटल व्योम hid_मुक्त_report(काष्ठा hid_report *report)
अणु
	अचिन्हित n;

	क्रम (n = 0; n < report->maxfield; n++)
		kमुक्त(report->field[n]);
	kमुक्त(report);
पूर्ण

/*
 * Close report. This function वापसs the device
 * state to the poपूर्णांक prior to hid_खोलो_report().
 */
अटल व्योम hid_बंद_report(काष्ठा hid_device *device)
अणु
	अचिन्हित i, j;

	क्रम (i = 0; i < HID_REPORT_TYPES; i++) अणु
		काष्ठा hid_report_क्रमागत *report_क्रमागत = device->report_क्रमागत + i;

		क्रम (j = 0; j < HID_MAX_IDS; j++) अणु
			काष्ठा hid_report *report = report_क्रमागत->report_id_hash[j];
			अगर (report)
				hid_मुक्त_report(report);
		पूर्ण
		स_रखो(report_क्रमागत, 0, माप(*report_क्रमागत));
		INIT_LIST_HEAD(&report_क्रमागत->report_list);
	पूर्ण

	kमुक्त(device->rdesc);
	device->rdesc = शून्य;
	device->rsize = 0;

	kमुक्त(device->collection);
	device->collection = शून्य;
	device->collection_size = 0;
	device->maxcollection = 0;
	device->maxapplication = 0;

	device->status &= ~HID_STAT_PARSED;
पूर्ण

/*
 * Free a device काष्ठाure, all reports, and all fields.
 */

अटल व्योम hid_device_release(काष्ठा device *dev)
अणु
	काष्ठा hid_device *hid = to_hid_device(dev);

	hid_बंद_report(hid);
	kमुक्त(hid->dev_rdesc);
	kमुक्त(hid);
पूर्ण

/*
 * Fetch a report description item from the data stream. We support दीर्घ
 * items, though they are not used yet.
 */

अटल u8 *fetch_item(__u8 *start, __u8 *end, काष्ठा hid_item *item)
अणु
	u8 b;

	अगर ((end - start) <= 0)
		वापस शून्य;

	b = *start++;

	item->type = (b >> 2) & 3;
	item->tag  = (b >> 4) & 15;

	अगर (item->tag == HID_ITEM_TAG_LONG) अणु

		item->क्रमmat = HID_ITEM_FORMAT_LONG;

		अगर ((end - start) < 2)
			वापस शून्य;

		item->size = *start++;
		item->tag  = *start++;

		अगर ((end - start) < item->size)
			वापस शून्य;

		item->data.दीर्घdata = start;
		start += item->size;
		वापस start;
	पूर्ण

	item->क्रमmat = HID_ITEM_FORMAT_SHORT;
	item->size = b & 3;

	चयन (item->size) अणु
	हाल 0:
		वापस start;

	हाल 1:
		अगर ((end - start) < 1)
			वापस शून्य;
		item->data.u8 = *start++;
		वापस start;

	हाल 2:
		अगर ((end - start) < 2)
			वापस शून्य;
		item->data.u16 = get_unaligned_le16(start);
		start = (__u8 *)((__le16 *)start + 1);
		वापस start;

	हाल 3:
		item->size++;
		अगर ((end - start) < 4)
			वापस शून्य;
		item->data.u32 = get_unaligned_le32(start);
		start = (__u8 *)((__le32 *)start + 1);
		वापस start;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम hid_scan_input_usage(काष्ठा hid_parser *parser, u32 usage)
अणु
	काष्ठा hid_device *hid = parser->device;

	अगर (usage == HID_DG_CONTACTID)
		hid->group = HID_GROUP_MULTITOUCH;
पूर्ण

अटल व्योम hid_scan_feature_usage(काष्ठा hid_parser *parser, u32 usage)
अणु
	अगर (usage == 0xff0000c5 && parser->global.report_count == 256 &&
	    parser->global.report_size == 8)
		parser->scan_flags |= HID_SCAN_FLAG_MT_WIN_8;

	अगर (usage == 0xff0000c6 && parser->global.report_count == 1 &&
	    parser->global.report_size == 8)
		parser->scan_flags |= HID_SCAN_FLAG_MT_WIN_8;
पूर्ण

अटल व्योम hid_scan_collection(काष्ठा hid_parser *parser, अचिन्हित type)
अणु
	काष्ठा hid_device *hid = parser->device;
	पूर्णांक i;

	अगर (((parser->global.usage_page << 16) == HID_UP_SENSOR) &&
	    type == HID_COLLECTION_PHYSICAL)
		hid->group = HID_GROUP_SENSOR_HUB;

	अगर (hid->venकरोr == USB_VENDOR_ID_MICROSOFT &&
	    hid->product == USB_DEVICE_ID_MS_POWER_COVER &&
	    hid->group == HID_GROUP_MULTITOUCH)
		hid->group = HID_GROUP_GENERIC;

	अगर ((parser->global.usage_page << 16) == HID_UP_GENDESK)
		क्रम (i = 0; i < parser->local.usage_index; i++)
			अगर (parser->local.usage[i] == HID_GD_POINTER)
				parser->scan_flags |= HID_SCAN_FLAG_GD_POINTER;

	अगर ((parser->global.usage_page << 16) >= HID_UP_MSVENDOR)
		parser->scan_flags |= HID_SCAN_FLAG_VENDOR_SPECIFIC;

	अगर ((parser->global.usage_page << 16) == HID_UP_GOOGLEVENDOR)
		क्रम (i = 0; i < parser->local.usage_index; i++)
			अगर (parser->local.usage[i] ==
					(HID_UP_GOOGLEVENDOR | 0x0001))
				parser->device->group =
					HID_GROUP_VIVALDI;
पूर्ण

अटल पूर्णांक hid_scan_मुख्य(काष्ठा hid_parser *parser, काष्ठा hid_item *item)
अणु
	__u32 data;
	पूर्णांक i;

	hid_concatenate_last_usage_page(parser);

	data = item_udata(item);

	चयन (item->tag) अणु
	हाल HID_MAIN_ITEM_TAG_BEGIN_COLLECTION:
		hid_scan_collection(parser, data & 0xff);
		अवरोध;
	हाल HID_MAIN_ITEM_TAG_END_COLLECTION:
		अवरोध;
	हाल HID_MAIN_ITEM_TAG_INPUT:
		/* ignore स्थिरant inमाला_दो, they will be ignored by hid-input */
		अगर (data & HID_MAIN_ITEM_CONSTANT)
			अवरोध;
		क्रम (i = 0; i < parser->local.usage_index; i++)
			hid_scan_input_usage(parser, parser->local.usage[i]);
		अवरोध;
	हाल HID_MAIN_ITEM_TAG_OUTPUT:
		अवरोध;
	हाल HID_MAIN_ITEM_TAG_FEATURE:
		क्रम (i = 0; i < parser->local.usage_index; i++)
			hid_scan_feature_usage(parser, parser->local.usage[i]);
		अवरोध;
	पूर्ण

	/* Reset the local parser environment */
	स_रखो(&parser->local, 0, माप(parser->local));

	वापस 0;
पूर्ण

/*
 * Scan a report descriptor beक्रमe the device is added to the bus.
 * Sets device groups and other properties that determine what driver
 * to load.
 */
अटल पूर्णांक hid_scan_report(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_parser *parser;
	काष्ठा hid_item item;
	__u8 *start = hid->dev_rdesc;
	__u8 *end = start + hid->dev_rsize;
	अटल पूर्णांक (*dispatch_type[])(काष्ठा hid_parser *parser,
				      काष्ठा hid_item *item) = अणु
		hid_scan_मुख्य,
		hid_parser_global,
		hid_parser_local,
		hid_parser_reserved
	पूर्ण;

	parser = vzalloc(माप(काष्ठा hid_parser));
	अगर (!parser)
		वापस -ENOMEM;

	parser->device = hid;
	hid->group = HID_GROUP_GENERIC;

	/*
	 * The parsing is simpler than the one in hid_खोलो_report() as we should
	 * be robust against hid errors. Those errors will be उठाओd by
	 * hid_खोलो_report() anyway.
	 */
	जबतक ((start = fetch_item(start, end, &item)) != शून्य)
		dispatch_type[item.type](parser, &item);

	/*
	 * Handle special flags set during scanning.
	 */
	अगर ((parser->scan_flags & HID_SCAN_FLAG_MT_WIN_8) &&
	    (hid->group == HID_GROUP_MULTITOUCH))
		hid->group = HID_GROUP_MULTITOUCH_WIN_8;

	/*
	 * Venकरोr specअगरic handlings
	 */
	चयन (hid->venकरोr) अणु
	हाल USB_VENDOR_ID_WACOM:
		hid->group = HID_GROUP_WACOM;
		अवरोध;
	हाल USB_VENDOR_ID_SYNAPTICS:
		अगर (hid->group == HID_GROUP_GENERIC)
			अगर ((parser->scan_flags & HID_SCAN_FLAG_VENDOR_SPECIFIC)
			    && (parser->scan_flags & HID_SCAN_FLAG_GD_POINTER))
				/*
				 * hid-rmi should take care of them,
				 * not hid-generic
				 */
				hid->group = HID_GROUP_RMI;
		अवरोध;
	पूर्ण

	kमुक्त(parser->collection_stack);
	vमुक्त(parser);
	वापस 0;
पूर्ण

/**
 * hid_parse_report - parse device report
 *
 * @hid: hid device
 * @start: report start
 * @size: report size
 *
 * Allocate the device report as पढ़ो by the bus driver. This function should
 * only be called from parse() in ll drivers.
 */
पूर्णांक hid_parse_report(काष्ठा hid_device *hid, __u8 *start, अचिन्हित size)
अणु
	hid->dev_rdesc = kmemdup(start, size, GFP_KERNEL);
	अगर (!hid->dev_rdesc)
		वापस -ENOMEM;
	hid->dev_rsize = size;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hid_parse_report);

अटल स्थिर अक्षर * स्थिर hid_report_names[] = अणु
	"HID_INPUT_REPORT",
	"HID_OUTPUT_REPORT",
	"HID_FEATURE_REPORT",
पूर्ण;
/**
 * hid_validate_values - validate existing device report's value indexes
 *
 * @hid: hid device
 * @type: which report type to examine
 * @id: which report ID to examine (0 क्रम first)
 * @field_index: which report field to examine
 * @report_counts: expected number of values
 *
 * Validate the number of values in a given field of a given report, after
 * parsing.
 */
काष्ठा hid_report *hid_validate_values(काष्ठा hid_device *hid,
				       अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक id,
				       अचिन्हित पूर्णांक field_index,
				       अचिन्हित पूर्णांक report_counts)
अणु
	काष्ठा hid_report *report;

	अगर (type > HID_FEATURE_REPORT) अणु
		hid_err(hid, "invalid HID report type %u\n", type);
		वापस शून्य;
	पूर्ण

	अगर (id >= HID_MAX_IDS) अणु
		hid_err(hid, "invalid HID report id %u\n", id);
		वापस शून्य;
	पूर्ण

	/*
	 * Explicitly not using hid_get_report() here since it depends on
	 * ->numbered being checked, which may not always be the हाल when
	 * drivers go to access report values.
	 */
	अगर (id == 0) अणु
		/*
		 * Validating on id 0 means we should examine the first
		 * report in the list.
		 */
		report = list_entry(
				hid->report_क्रमागत[type].report_list.next,
				काष्ठा hid_report, list);
	पूर्ण अन्यथा अणु
		report = hid->report_क्रमागत[type].report_id_hash[id];
	पूर्ण
	अगर (!report) अणु
		hid_err(hid, "missing %s %u\n", hid_report_names[type], id);
		वापस शून्य;
	पूर्ण
	अगर (report->maxfield <= field_index) अणु
		hid_err(hid, "not enough fields in %s %u\n",
			hid_report_names[type], id);
		वापस शून्य;
	पूर्ण
	अगर (report->field[field_index]->report_count < report_counts) अणु
		hid_err(hid, "not enough values in %s %u field %u\n",
			hid_report_names[type], id, field_index);
		वापस शून्य;
	पूर्ण
	वापस report;
पूर्ण
EXPORT_SYMBOL_GPL(hid_validate_values);

अटल पूर्णांक hid_calculate_multiplier(काष्ठा hid_device *hid,
				     काष्ठा hid_field *multiplier)
अणु
	पूर्णांक m;
	__s32 v = *multiplier->value;
	__s32 lmin = multiplier->logical_minimum;
	__s32 lmax = multiplier->logical_maximum;
	__s32 pmin = multiplier->physical_minimum;
	__s32 pmax = multiplier->physical_maximum;

	/*
	 * "Because OS implementations will generally भागide the control's
	 * reported count by the Effective Resolution Multiplier, designers
	 * should take care not to establish a potential Effective
	 * Resolution Multiplier of zero."
	 * HID Usage Table, v1.12, Section 4.3.1, p31
	 */
	अगर (lmax - lmin == 0)
		वापस 1;
	/*
	 * Handling the unit exponent is left as an exercise to whoever
	 * finds a device where that exponent is not 0.
	 */
	m = ((v - lmin)/(lmax - lmin) * (pmax - pmin) + pmin);
	अगर (unlikely(multiplier->unit_exponent != 0)) अणु
		hid_warn(hid,
			 "unsupported Resolution Multiplier unit exponent %d\n",
			 multiplier->unit_exponent);
	पूर्ण

	/* There are no devices with an effective multiplier > 255 */
	अगर (unlikely(m == 0 || m > 255 || m < -255)) अणु
		hid_warn(hid, "unsupported Resolution Multiplier %d\n", m);
		m = 1;
	पूर्ण

	वापस m;
पूर्ण

अटल व्योम hid_apply_multiplier_to_field(काष्ठा hid_device *hid,
					  काष्ठा hid_field *field,
					  काष्ठा hid_collection *multiplier_collection,
					  पूर्णांक effective_multiplier)
अणु
	काष्ठा hid_collection *collection;
	काष्ठा hid_usage *usage;
	पूर्णांक i;

	/*
	 * If multiplier_collection is शून्य, the multiplier applies
	 * to all fields in the report.
	 * Otherwise, it is the Logical Collection the multiplier applies to
	 * but our field may be in a subcollection of that collection.
	 */
	क्रम (i = 0; i < field->maxusage; i++) अणु
		usage = &field->usage[i];

		collection = &hid->collection[usage->collection_index];
		जबतक (collection->parent_idx != -1 &&
		       collection != multiplier_collection)
			collection = &hid->collection[collection->parent_idx];

		अगर (collection->parent_idx != -1 ||
		    multiplier_collection == शून्य)
			usage->resolution_multiplier = effective_multiplier;

	पूर्ण
पूर्ण

अटल व्योम hid_apply_multiplier(काष्ठा hid_device *hid,
				 काष्ठा hid_field *multiplier)
अणु
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;
	काष्ठा hid_report *rep;
	काष्ठा hid_field *field;
	काष्ठा hid_collection *multiplier_collection;
	पूर्णांक effective_multiplier;
	पूर्णांक i;

	/*
	 * "The Resolution Multiplier control must be contained in the same
	 * Logical Collection as the control(s) to which it is to be applied.
	 * If no Resolution Multiplier is defined, then the Resolution
	 * Multiplier शेषs to 1.  If more than one control exists in a
	 * Logical Collection, the Resolution Multiplier is associated with
	 * all controls in the collection. If no Logical Collection is
	 * defined, the Resolution Multiplier is associated with all
	 * controls in the report."
	 * HID Usage Table, v1.12, Section 4.3.1, p30
	 *
	 * Thus, search from the current collection upwards until we find a
	 * logical collection. Then search all fields क्रम that same parent
	 * collection. Those are the fields the multiplier applies to.
	 *
	 * If we have more than one multiplier, it will overग_लिखो the
	 * applicable fields later.
	 */
	multiplier_collection = &hid->collection[multiplier->usage->collection_index];
	जबतक (multiplier_collection->parent_idx != -1 &&
	       multiplier_collection->type != HID_COLLECTION_LOGICAL)
		multiplier_collection = &hid->collection[multiplier_collection->parent_idx];

	effective_multiplier = hid_calculate_multiplier(hid, multiplier);

	rep_क्रमागत = &hid->report_क्रमागत[HID_INPUT_REPORT];
	list_क्रम_each_entry(rep, &rep_क्रमागत->report_list, list) अणु
		क्रम (i = 0; i < rep->maxfield; i++) अणु
			field = rep->field[i];
			hid_apply_multiplier_to_field(hid, field,
						      multiplier_collection,
						      effective_multiplier);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * hid_setup_resolution_multiplier - set up all resolution multipliers
 *
 * @device: hid device
 *
 * Search क्रम all Resolution Multiplier Feature Reports and apply their
 * value to all matching Input items. This only updates the पूर्णांकernal काष्ठा
 * fields.
 *
 * The Resolution Multiplier is applied by the hardware. If the multiplier
 * is anything other than 1, the hardware will send pre-multiplied events
 * so that the same physical पूर्णांकeraction generates an accumulated
 *	accumulated_value = value * * multiplier
 * This may be achieved by sending
 * - "value * multiplier" क्रम each event, or
 * - "value" but "multiplier" बार as frequently, or
 * - a combination of the above
 * The only guarantee is that the same physical पूर्णांकeraction always generates
 * an accumulated 'value * multiplier'.
 *
 * This function must be called beक्रमe any event processing and after
 * any SetRequest to the Resolution Multiplier.
 */
व्योम hid_setup_resolution_multiplier(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;
	काष्ठा hid_report *rep;
	काष्ठा hid_usage *usage;
	पूर्णांक i, j;

	rep_क्रमागत = &hid->report_क्रमागत[HID_FEATURE_REPORT];
	list_क्रम_each_entry(rep, &rep_क्रमागत->report_list, list) अणु
		क्रम (i = 0; i < rep->maxfield; i++) अणु
			/* Ignore अगर report count is out of bounds. */
			अगर (rep->field[i]->report_count < 1)
				जारी;

			क्रम (j = 0; j < rep->field[i]->maxusage; j++) अणु
				usage = &rep->field[i]->usage[j];
				अगर (usage->hid == HID_GD_RESOLUTION_MULTIPLIER)
					hid_apply_multiplier(hid,
							     rep->field[i]);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hid_setup_resolution_multiplier);

/**
 * hid_खोलो_report - खोलो a driver-specअगरic device report
 *
 * @device: hid device
 *
 * Parse a report description पूर्णांकo a hid_device काष्ठाure. Reports are
 * क्रमागतerated, fields are attached to these reports.
 * 0 वापसed on success, otherwise nonzero error value.
 *
 * This function (or the equivalent hid_parse() macro) should only be
 * called from probe() in drivers, beक्रमe starting the device.
 */
पूर्णांक hid_खोलो_report(काष्ठा hid_device *device)
अणु
	काष्ठा hid_parser *parser;
	काष्ठा hid_item item;
	अचिन्हित पूर्णांक size;
	__u8 *start;
	__u8 *buf;
	__u8 *end;
	__u8 *next;
	पूर्णांक ret;
	अटल पूर्णांक (*dispatch_type[])(काष्ठा hid_parser *parser,
				      काष्ठा hid_item *item) = अणु
		hid_parser_मुख्य,
		hid_parser_global,
		hid_parser_local,
		hid_parser_reserved
	पूर्ण;

	अगर (WARN_ON(device->status & HID_STAT_PARSED))
		वापस -EBUSY;

	start = device->dev_rdesc;
	अगर (WARN_ON(!start))
		वापस -ENODEV;
	size = device->dev_rsize;

	buf = kmemdup(start, size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	अगर (device->driver->report_fixup)
		start = device->driver->report_fixup(device, buf, &size);
	अन्यथा
		start = buf;

	start = kmemdup(start, size, GFP_KERNEL);
	kमुक्त(buf);
	अगर (start == शून्य)
		वापस -ENOMEM;

	device->rdesc = start;
	device->rsize = size;

	parser = vzalloc(माप(काष्ठा hid_parser));
	अगर (!parser) अणु
		ret = -ENOMEM;
		जाओ alloc_err;
	पूर्ण

	parser->device = device;

	end = start + size;

	device->collection = kसुस्मृति(HID_DEFAULT_NUM_COLLECTIONS,
				     माप(काष्ठा hid_collection), GFP_KERNEL);
	अगर (!device->collection) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	device->collection_size = HID_DEFAULT_NUM_COLLECTIONS;

	ret = -EINVAL;
	जबतक ((next = fetch_item(start, end, &item)) != शून्य) अणु
		start = next;

		अगर (item.क्रमmat != HID_ITEM_FORMAT_SHORT) अणु
			hid_err(device, "unexpected long global item\n");
			जाओ err;
		पूर्ण

		अगर (dispatch_type[item.type](parser, &item)) अणु
			hid_err(device, "item %u %u %u %u parsing failed\n",
				item.क्रमmat, (अचिन्हित)item.size,
				(अचिन्हित)item.type, (अचिन्हित)item.tag);
			जाओ err;
		पूर्ण

		अगर (start == end) अणु
			अगर (parser->collection_stack_ptr) अणु
				hid_err(device, "unbalanced collection at end of report description\n");
				जाओ err;
			पूर्ण
			अगर (parser->local.delimiter_depth) अणु
				hid_err(device, "unbalanced delimiter at end of report description\n");
				जाओ err;
			पूर्ण

			/*
			 * fetch initial values in हाल the device's
			 * शेष multiplier isn't the recommended 1
			 */
			hid_setup_resolution_multiplier(device);

			kमुक्त(parser->collection_stack);
			vमुक्त(parser);
			device->status |= HID_STAT_PARSED;

			वापस 0;
		पूर्ण
	पूर्ण

	hid_err(device, "item fetching failed at offset %u/%u\n",
		size - (अचिन्हित पूर्णांक)(end - start), size);
err:
	kमुक्त(parser->collection_stack);
alloc_err:
	vमुक्त(parser);
	hid_बंद_report(device);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hid_खोलो_report);

/*
 * Convert a चिन्हित n-bit पूर्णांकeger to चिन्हित 32-bit पूर्णांकeger. Common
 * हालs are करोne through the compiler, the screwed things has to be
 * करोne by hand.
 */

अटल s32 snto32(__u32 value, अचिन्हित n)
अणु
	अगर (!value || !n)
		वापस 0;

	चयन (n) अणु
	हाल 8:  वापस ((__s8)value);
	हाल 16: वापस ((__s16)value);
	हाल 32: वापस ((__s32)value);
	पूर्ण
	वापस value & (1 << (n - 1)) ? value | (~0U << n) : value;
पूर्ण

s32 hid_snto32(__u32 value, अचिन्हित n)
अणु
	वापस snto32(value, n);
पूर्ण
EXPORT_SYMBOL_GPL(hid_snto32);

/*
 * Convert a चिन्हित 32-bit पूर्णांकeger to a चिन्हित n-bit पूर्णांकeger.
 */

अटल u32 s32ton(__s32 value, अचिन्हित n)
अणु
	s32 a = value >> (n - 1);
	अगर (a && a != -1)
		वापस value < 0 ? 1 << (n - 1) : (1 << (n - 1)) - 1;
	वापस value & ((1 << n) - 1);
पूर्ण

/*
 * Extract/implement a data field from/to a little endian report (bit array).
 *
 * Code sort-of follows HID spec:
 *     http://www.usb.org/developers/hidpage/HID1_11.pdf
 *
 * While the USB HID spec allows unlimited length bit fields in "report
 * descriptors", most devices never use more than 16 bits.
 * One model of UPS is claimed to report "LINEV" as a 32-bit field.
 * Search linux-kernel and linux-usb-devel archives क्रम "hid-core extract".
 */

अटल u32 __extract(u8 *report, अचिन्हित offset, पूर्णांक n)
अणु
	अचिन्हित पूर्णांक idx = offset / 8;
	अचिन्हित पूर्णांक bit_nr = 0;
	अचिन्हित पूर्णांक bit_shअगरt = offset % 8;
	पूर्णांक bits_to_copy = 8 - bit_shअगरt;
	u32 value = 0;
	u32 mask = n < 32 ? (1U << n) - 1 : ~0U;

	जबतक (n > 0) अणु
		value |= ((u32)report[idx] >> bit_shअगरt) << bit_nr;
		n -= bits_to_copy;
		bit_nr += bits_to_copy;
		bits_to_copy = 8;
		bit_shअगरt = 0;
		idx++;
	पूर्ण

	वापस value & mask;
पूर्ण

u32 hid_field_extract(स्थिर काष्ठा hid_device *hid, u8 *report,
			अचिन्हित offset, अचिन्हित n)
अणु
	अगर (n > 32) अणु
		hid_warn_once(hid, "%s() called with n (%d) > 32! (%s)\n",
			      __func__, n, current->comm);
		n = 32;
	पूर्ण

	वापस __extract(report, offset, n);
पूर्ण
EXPORT_SYMBOL_GPL(hid_field_extract);

/*
 * "implement" : set bits in a little endian bit stream.
 * Same concepts as "extract" (see comments above).
 * The data mangled in the bit stream reमुख्यs in little endian
 * order the whole समय. It make more sense to talk about
 * endianness of रेजिस्टर values by considering a रेजिस्टर
 * a "cached" copy of the little endian bit stream.
 */

अटल व्योम __implement(u8 *report, अचिन्हित offset, पूर्णांक n, u32 value)
अणु
	अचिन्हित पूर्णांक idx = offset / 8;
	अचिन्हित पूर्णांक bit_shअगरt = offset % 8;
	पूर्णांक bits_to_set = 8 - bit_shअगरt;

	जबतक (n - bits_to_set >= 0) अणु
		report[idx] &= ~(0xff << bit_shअगरt);
		report[idx] |= value << bit_shअगरt;
		value >>= bits_to_set;
		n -= bits_to_set;
		bits_to_set = 8;
		bit_shअगरt = 0;
		idx++;
	पूर्ण

	/* last nibble */
	अगर (n) अणु
		u8 bit_mask = ((1U << n) - 1);
		report[idx] &= ~(bit_mask << bit_shअगरt);
		report[idx] |= value << bit_shअगरt;
	पूर्ण
पूर्ण

अटल व्योम implement(स्थिर काष्ठा hid_device *hid, u8 *report,
		      अचिन्हित offset, अचिन्हित n, u32 value)
अणु
	अगर (unlikely(n > 32)) अणु
		hid_warn(hid, "%s() called with n (%d) > 32! (%s)\n",
			 __func__, n, current->comm);
		n = 32;
	पूर्ण अन्यथा अगर (n < 32) अणु
		u32 m = (1U << n) - 1;

		अगर (unlikely(value > m)) अणु
			hid_warn(hid,
				 "%s() called with too large value %d (n: %d)! (%s)\n",
				 __func__, value, n, current->comm);
			WARN_ON(1);
			value &= m;
		पूर्ण
	पूर्ण

	__implement(report, offset, n, value);
पूर्ण

/*
 * Search an array क्रम a value.
 */

अटल पूर्णांक search(__s32 *array, __s32 value, अचिन्हित n)
अणु
	जबतक (n--) अणु
		अगर (*array++ == value)
			वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

/**
 * hid_match_report - check अगर driver's raw_event should be called
 *
 * @hid: hid device
 * @report: hid report to match against
 *
 * compare hid->driver->report_table->report_type to report->type
 */
अटल पूर्णांक hid_match_report(काष्ठा hid_device *hid, काष्ठा hid_report *report)
अणु
	स्थिर काष्ठा hid_report_id *id = hid->driver->report_table;

	अगर (!id) /* शून्य means all */
		वापस 1;

	क्रम (; id->report_type != HID_TERMINATOR; id++)
		अगर (id->report_type == HID_ANY_ID ||
				id->report_type == report->type)
			वापस 1;
	वापस 0;
पूर्ण

/**
 * hid_match_usage - check अगर driver's event should be called
 *
 * @hid: hid device
 * @usage: usage to match against
 *
 * compare hid->driver->usage_table->usage_अणुtype,codeपूर्ण to
 * usage->usage_अणुtype,codeपूर्ण
 */
अटल पूर्णांक hid_match_usage(काष्ठा hid_device *hid, काष्ठा hid_usage *usage)
अणु
	स्थिर काष्ठा hid_usage_id *id = hid->driver->usage_table;

	अगर (!id) /* शून्य means all */
		वापस 1;

	क्रम (; id->usage_type != HID_ANY_ID - 1; id++)
		अगर ((id->usage_hid == HID_ANY_ID ||
				id->usage_hid == usage->hid) &&
				(id->usage_type == HID_ANY_ID ||
				id->usage_type == usage->type) &&
				(id->usage_code == HID_ANY_ID ||
				 id->usage_code == usage->code))
			वापस 1;
	वापस 0;
पूर्ण

अटल व्योम hid_process_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value, पूर्णांक पूर्णांकerrupt)
अणु
	काष्ठा hid_driver *hdrv = hid->driver;
	पूर्णांक ret;

	अगर (!list_empty(&hid->debug_list))
		hid_dump_input(hid, usage, value);

	अगर (hdrv && hdrv->event && hid_match_usage(hid, usage)) अणु
		ret = hdrv->event(hid, field, usage, value);
		अगर (ret != 0) अणु
			अगर (ret < 0)
				hid_err(hid, "%s's event failed with %d\n",
						hdrv->name, ret);
			वापस;
		पूर्ण
	पूर्ण

	अगर (hid->claimed & HID_CLAIMED_INPUT)
		hidinput_hid_event(hid, field, usage, value);
	अगर (hid->claimed & HID_CLAIMED_HIDDEV && पूर्णांकerrupt && hid->hiddev_hid_event)
		hid->hiddev_hid_event(hid, field, usage, value);
पूर्ण

/*
 * Analyse a received field, and fetch the data from it. The field
 * content is stored क्रम next report processing (we करो dअगरferential
 * reporting to the layer).
 */

अटल व्योम hid_input_field(काष्ठा hid_device *hid, काष्ठा hid_field *field,
			    __u8 *data, पूर्णांक पूर्णांकerrupt)
अणु
	अचिन्हित n;
	अचिन्हित count = field->report_count;
	अचिन्हित offset = field->report_offset;
	अचिन्हित size = field->report_size;
	__s32 min = field->logical_minimum;
	__s32 max = field->logical_maximum;
	__s32 *value;

	value = kदो_स्मृति_array(count, माप(__s32), GFP_ATOMIC);
	अगर (!value)
		वापस;

	क्रम (n = 0; n < count; n++) अणु

		value[n] = min < 0 ?
			snto32(hid_field_extract(hid, data, offset + n * size,
			       size), size) :
			hid_field_extract(hid, data, offset + n * size, size);

		/* Ignore report अगर ErrorRollOver */
		अगर (!(field->flags & HID_MAIN_ITEM_VARIABLE) &&
		    value[n] >= min && value[n] <= max &&
		    value[n] - min < field->maxusage &&
		    field->usage[value[n] - min].hid == HID_UP_KEYBOARD + 1)
			जाओ निकास;
	पूर्ण

	क्रम (n = 0; n < count; n++) अणु

		अगर (HID_MAIN_ITEM_VARIABLE & field->flags) अणु
			hid_process_event(hid, field, &field->usage[n], value[n], पूर्णांकerrupt);
			जारी;
		पूर्ण

		अगर (field->value[n] >= min && field->value[n] <= max
			&& field->value[n] - min < field->maxusage
			&& field->usage[field->value[n] - min].hid
			&& search(value, field->value[n], count))
				hid_process_event(hid, field, &field->usage[field->value[n] - min], 0, पूर्णांकerrupt);

		अगर (value[n] >= min && value[n] <= max
			&& value[n] - min < field->maxusage
			&& field->usage[value[n] - min].hid
			&& search(field->value, value[n], count))
				hid_process_event(hid, field, &field->usage[value[n] - min], 1, पूर्णांकerrupt);
	पूर्ण

	स_नकल(field->value, value, count * माप(__s32));
निकास:
	kमुक्त(value);
पूर्ण

/*
 * Output the field पूर्णांकo the report.
 */

अटल व्योम hid_output_field(स्थिर काष्ठा hid_device *hid,
			     काष्ठा hid_field *field, __u8 *data)
अणु
	अचिन्हित count = field->report_count;
	अचिन्हित offset = field->report_offset;
	अचिन्हित size = field->report_size;
	अचिन्हित n;

	क्रम (n = 0; n < count; n++) अणु
		अगर (field->logical_minimum < 0)	/* चिन्हित values */
			implement(hid, data, offset + n * size, size,
				  s32ton(field->value[n], size));
		अन्यथा				/* अचिन्हित values */
			implement(hid, data, offset + n * size, size,
				  field->value[n]);
	पूर्ण
पूर्ण

/*
 * Compute the size of a report.
 */
अटल माप_प्रकार hid_compute_report_size(काष्ठा hid_report *report)
अणु
	अगर (report->size)
		वापस ((report->size - 1) >> 3) + 1;

	वापस 0;
पूर्ण

/*
 * Create a report. 'data' has to be allocated using
 * hid_alloc_report_buf() so that it has proper size.
 */

व्योम hid_output_report(काष्ठा hid_report *report, __u8 *data)
अणु
	अचिन्हित n;

	अगर (report->id > 0)
		*data++ = report->id;

	स_रखो(data, 0, hid_compute_report_size(report));
	क्रम (n = 0; n < report->maxfield; n++)
		hid_output_field(report->device, report->field[n], data);
पूर्ण
EXPORT_SYMBOL_GPL(hid_output_report);

/*
 * Allocator क्रम buffer that is going to be passed to hid_output_report()
 */
u8 *hid_alloc_report_buf(काष्ठा hid_report *report, gfp_t flags)
अणु
	/*
	 * 7 extra bytes are necessary to achieve proper functionality
	 * of implement() working on 8 byte chunks
	 */

	u32 len = hid_report_len(report) + 7;

	वापस kदो_स्मृति(len, flags);
पूर्ण
EXPORT_SYMBOL_GPL(hid_alloc_report_buf);

/*
 * Set a field value. The report this field beदीर्घs to has to be
 * created and transferred to the device, to set this value in the
 * device.
 */

पूर्णांक hid_set_field(काष्ठा hid_field *field, अचिन्हित offset, __s32 value)
अणु
	अचिन्हित size;

	अगर (!field)
		वापस -1;

	size = field->report_size;

	hid_dump_input(field->report->device, field->usage + offset, value);

	अगर (offset >= field->report_count) अणु
		hid_err(field->report->device, "offset (%d) exceeds report_count (%d)\n",
				offset, field->report_count);
		वापस -1;
	पूर्ण
	अगर (field->logical_minimum < 0) अणु
		अगर (value != snto32(s32ton(value, size), size)) अणु
			hid_err(field->report->device, "value %d is out of range\n", value);
			वापस -1;
		पूर्ण
	पूर्ण
	field->value[offset] = value;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hid_set_field);

अटल काष्ठा hid_report *hid_get_report(काष्ठा hid_report_क्रमागत *report_क्रमागत,
		स्थिर u8 *data)
अणु
	काष्ठा hid_report *report;
	अचिन्हित पूर्णांक n = 0;	/* Normally report number is 0 */

	/* Device uses numbered reports, data[0] is report number */
	अगर (report_क्रमागत->numbered)
		n = *data;

	report = report_क्रमागत->report_id_hash[n];
	अगर (report == शून्य)
		dbg_hid("undefined report_id %u received\n", n);

	वापस report;
पूर्ण

/*
 * Implement a generic .request() callback, using .raw_request()
 * DO NOT USE in hid drivers directly, but through hid_hw_request instead.
 */
पूर्णांक __hid_request(काष्ठा hid_device *hid, काष्ठा hid_report *report,
		पूर्णांक reqtype)
अणु
	अक्षर *buf;
	पूर्णांक ret;
	u32 len;

	buf = hid_alloc_report_buf(report, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len = hid_report_len(report);

	अगर (reqtype == HID_REQ_SET_REPORT)
		hid_output_report(report, buf);

	ret = hid->ll_driver->raw_request(hid, report->id, buf, len,
					  report->type, reqtype);
	अगर (ret < 0) अणु
		dbg_hid("unable to complete request: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (reqtype == HID_REQ_GET_REPORT)
		hid_input_report(hid, report->type, buf, ret, 0);

	ret = 0;

out:
	kमुक्त(buf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__hid_request);

पूर्णांक hid_report_raw_event(काष्ठा hid_device *hid, पूर्णांक type, u8 *data, u32 size,
		पूर्णांक पूर्णांकerrupt)
अणु
	काष्ठा hid_report_क्रमागत *report_क्रमागत = hid->report_क्रमागत + type;
	काष्ठा hid_report *report;
	काष्ठा hid_driver *hdrv;
	अचिन्हित पूर्णांक a;
	u32 rsize, csize = size;
	u8 *cdata = data;
	पूर्णांक ret = 0;

	report = hid_get_report(report_क्रमागत, data);
	अगर (!report)
		जाओ out;

	अगर (report_क्रमागत->numbered) अणु
		cdata++;
		csize--;
	पूर्ण

	rsize = hid_compute_report_size(report);

	अगर (report_क्रमागत->numbered && rsize >= HID_MAX_BUFFER_SIZE)
		rsize = HID_MAX_BUFFER_SIZE - 1;
	अन्यथा अगर (rsize > HID_MAX_BUFFER_SIZE)
		rsize = HID_MAX_BUFFER_SIZE;

	अगर (csize < rsize) अणु
		dbg_hid("report %d is too short, (%d < %d)\n", report->id,
				csize, rsize);
		स_रखो(cdata + csize, 0, rsize - csize);
	पूर्ण

	अगर ((hid->claimed & HID_CLAIMED_HIDDEV) && hid->hiddev_report_event)
		hid->hiddev_report_event(hid, report);
	अगर (hid->claimed & HID_CLAIMED_HIDRAW) अणु
		ret = hidraw_report_event(hid, data, size);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (hid->claimed != HID_CLAIMED_HIDRAW && report->maxfield) अणु
		क्रम (a = 0; a < report->maxfield; a++)
			hid_input_field(hid, report->field[a], cdata, पूर्णांकerrupt);
		hdrv = hid->driver;
		अगर (hdrv && hdrv->report)
			hdrv->report(hid, report);
	पूर्ण

	अगर (hid->claimed & HID_CLAIMED_INPUT)
		hidinput_report_event(hid, report);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hid_report_raw_event);

/**
 * hid_input_report - report data from lower layer (usb, bt...)
 *
 * @hid: hid device
 * @type: HID report type (HID_*_REPORT)
 * @data: report contents
 * @size: size of data parameter
 * @पूर्णांकerrupt: distinguish between पूर्णांकerrupt and control transfers
 *
 * This is data entry क्रम lower layers.
 */
पूर्णांक hid_input_report(काष्ठा hid_device *hid, पूर्णांक type, u8 *data, u32 size, पूर्णांक पूर्णांकerrupt)
अणु
	काष्ठा hid_report_क्रमागत *report_क्रमागत;
	काष्ठा hid_driver *hdrv;
	काष्ठा hid_report *report;
	पूर्णांक ret = 0;

	अगर (!hid)
		वापस -ENODEV;

	अगर (करोwn_trylock(&hid->driver_input_lock))
		वापस -EBUSY;

	अगर (!hid->driver) अणु
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण
	report_क्रमागत = hid->report_क्रमागत + type;
	hdrv = hid->driver;

	अगर (!size) अणु
		dbg_hid("empty report\n");
		ret = -1;
		जाओ unlock;
	पूर्ण

	/* Aव्योम unnecessary overhead अगर debugfs is disabled */
	अगर (!list_empty(&hid->debug_list))
		hid_dump_report(hid, type, data, size);

	report = hid_get_report(report_क्रमागत, data);

	अगर (!report) अणु
		ret = -1;
		जाओ unlock;
	पूर्ण

	अगर (hdrv && hdrv->raw_event && hid_match_report(hid, report)) अणु
		ret = hdrv->raw_event(hid, report, data, size);
		अगर (ret < 0)
			जाओ unlock;
	पूर्ण

	ret = hid_report_raw_event(hid, type, data, size, पूर्णांकerrupt);

unlock:
	up(&hid->driver_input_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hid_input_report);

bool hid_match_one_id(स्थिर काष्ठा hid_device *hdev,
		      स्थिर काष्ठा hid_device_id *id)
अणु
	वापस (id->bus == HID_BUS_ANY || id->bus == hdev->bus) &&
		(id->group == HID_GROUP_ANY || id->group == hdev->group) &&
		(id->venकरोr == HID_ANY_ID || id->venकरोr == hdev->venकरोr) &&
		(id->product == HID_ANY_ID || id->product == hdev->product);
पूर्ण

स्थिर काष्ठा hid_device_id *hid_match_id(स्थिर काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	क्रम (; id->bus; id++)
		अगर (hid_match_one_id(hdev, id))
			वापस id;

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा hid_device_id hid_hiddev_list[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MGE, USB_DEVICE_ID_MGE_UPS) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MGE, USB_DEVICE_ID_MGE_UPS1) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल bool hid_hiddev(काष्ठा hid_device *hdev)
अणु
	वापस !!hid_match_id(hdev, hid_hiddev_list);
पूर्ण


अटल sमाप_प्रकार
पढ़ो_report_descriptor(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा hid_device *hdev = to_hid_device(dev);

	अगर (off >= hdev->rsize)
		वापस 0;

	अगर (off + count > hdev->rsize)
		count = hdev->rsize - off;

	स_नकल(buf, hdev->rdesc + off, count);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_country(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);

	वापस प्र_लिखो(buf, "%02x\n", hdev->country & 0xff);
पूर्ण

अटल काष्ठा bin_attribute dev_bin_attr_report_desc = अणु
	.attr = अणु .name = "report_descriptor", .mode = 0444 पूर्ण,
	.पढ़ो = पढ़ो_report_descriptor,
	.size = HID_MAX_DESCRIPTOR_SIZE,
पूर्ण;

अटल स्थिर काष्ठा device_attribute dev_attr_country = अणु
	.attr = अणु .name = "country", .mode = 0444 पूर्ण,
	.show = show_country,
पूर्ण;

पूर्णांक hid_connect(काष्ठा hid_device *hdev, अचिन्हित पूर्णांक connect_mask)
अणु
	अटल स्थिर अक्षर *types[] = अणु "Device", "Pointer", "Mouse", "Device",
		"Joystick", "Gamepad", "Keyboard", "Keypad",
		"Multi-Axis Controller"
	पूर्ण;
	स्थिर अक्षर *type, *bus;
	अक्षर buf[64] = "";
	अचिन्हित पूर्णांक i;
	पूर्णांक len;
	पूर्णांक ret;

	अगर (hdev->quirks & HID_QUIRK_HIDDEV_FORCE)
		connect_mask |= (HID_CONNECT_HIDDEV_FORCE | HID_CONNECT_HIDDEV);
	अगर (hdev->quirks & HID_QUIRK_HIDINPUT_FORCE)
		connect_mask |= HID_CONNECT_HIDINPUT_FORCE;
	अगर (hdev->bus != BUS_USB)
		connect_mask &= ~HID_CONNECT_HIDDEV;
	अगर (hid_hiddev(hdev))
		connect_mask |= HID_CONNECT_HIDDEV_FORCE;

	अगर ((connect_mask & HID_CONNECT_HIDINPUT) && !hidinput_connect(hdev,
				connect_mask & HID_CONNECT_HIDINPUT_FORCE))
		hdev->claimed |= HID_CLAIMED_INPUT;

	अगर ((connect_mask & HID_CONNECT_HIDDEV) && hdev->hiddev_connect &&
			!hdev->hiddev_connect(hdev,
				connect_mask & HID_CONNECT_HIDDEV_FORCE))
		hdev->claimed |= HID_CLAIMED_HIDDEV;
	अगर ((connect_mask & HID_CONNECT_HIDRAW) && !hidraw_connect(hdev))
		hdev->claimed |= HID_CLAIMED_HIDRAW;

	अगर (connect_mask & HID_CONNECT_DRIVER)
		hdev->claimed |= HID_CLAIMED_DRIVER;

	/* Drivers with the ->raw_event callback set are not required to connect
	 * to any other listener. */
	अगर (!hdev->claimed && !hdev->driver->raw_event) अणु
		hid_err(hdev, "device has no listeners, quitting\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((hdev->claimed & HID_CLAIMED_INPUT) &&
			(connect_mask & HID_CONNECT_FF) && hdev->ff_init)
		hdev->ff_init(hdev);

	len = 0;
	अगर (hdev->claimed & HID_CLAIMED_INPUT)
		len += प्र_लिखो(buf + len, "input");
	अगर (hdev->claimed & HID_CLAIMED_HIDDEV)
		len += प्र_लिखो(buf + len, "%shiddev%d", len ? "," : "",
				((काष्ठा hiddev *)hdev->hiddev)->minor);
	अगर (hdev->claimed & HID_CLAIMED_HIDRAW)
		len += प्र_लिखो(buf + len, "%shidraw%d", len ? "," : "",
				((काष्ठा hidraw *)hdev->hidraw)->minor);

	type = "Device";
	क्रम (i = 0; i < hdev->maxcollection; i++) अणु
		काष्ठा hid_collection *col = &hdev->collection[i];
		अगर (col->type == HID_COLLECTION_APPLICATION &&
		   (col->usage & HID_USAGE_PAGE) == HID_UP_GENDESK &&
		   (col->usage & 0xffff) < ARRAY_SIZE(types)) अणु
			type = types[col->usage & 0xffff];
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (hdev->bus) अणु
	हाल BUS_USB:
		bus = "USB";
		अवरोध;
	हाल BUS_BLUETOOTH:
		bus = "BLUETOOTH";
		अवरोध;
	हाल BUS_I2C:
		bus = "I2C";
		अवरोध;
	हाल BUS_VIRTUAL:
		bus = "VIRTUAL";
		अवरोध;
	शेष:
		bus = "<UNKNOWN>";
	पूर्ण

	ret = device_create_file(&hdev->dev, &dev_attr_country);
	अगर (ret)
		hid_warn(hdev,
			 "can't create sysfs country code attribute err: %d\n", ret);

	hid_info(hdev, "%s: %s HID v%x.%02x %s [%s] on %s\n",
		 buf, bus, hdev->version >> 8, hdev->version & 0xff,
		 type, hdev->name, hdev->phys);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hid_connect);

व्योम hid_disconnect(काष्ठा hid_device *hdev)
अणु
	device_हटाओ_file(&hdev->dev, &dev_attr_country);
	अगर (hdev->claimed & HID_CLAIMED_INPUT)
		hidinput_disconnect(hdev);
	अगर (hdev->claimed & HID_CLAIMED_HIDDEV)
		hdev->hiddev_disconnect(hdev);
	अगर (hdev->claimed & HID_CLAIMED_HIDRAW)
		hidraw_disconnect(hdev);
	hdev->claimed = 0;
पूर्ण
EXPORT_SYMBOL_GPL(hid_disconnect);

/**
 * hid_hw_start - start underlying HW
 * @hdev: hid device
 * @connect_mask: which outमाला_दो to connect, see HID_CONNECT_*
 *
 * Call this in probe function *after* hid_parse. This will setup HW
 * buffers and start the device (अगर not defeirred to device खोलो).
 * hid_hw_stop must be called अगर this was successful.
 */
पूर्णांक hid_hw_start(काष्ठा hid_device *hdev, अचिन्हित पूर्णांक connect_mask)
अणु
	पूर्णांक error;

	error = hdev->ll_driver->start(hdev);
	अगर (error)
		वापस error;

	अगर (connect_mask) अणु
		error = hid_connect(hdev, connect_mask);
		अगर (error) अणु
			hdev->ll_driver->stop(hdev);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hid_hw_start);

/**
 * hid_hw_stop - stop underlying HW
 * @hdev: hid device
 *
 * This is usually called from हटाओ function or from probe when something
 * failed and hid_hw_start was called alपढ़ोy.
 */
व्योम hid_hw_stop(काष्ठा hid_device *hdev)
अणु
	hid_disconnect(hdev);
	hdev->ll_driver->stop(hdev);
पूर्ण
EXPORT_SYMBOL_GPL(hid_hw_stop);

/**
 * hid_hw_खोलो - संकेत underlying HW to start delivering events
 * @hdev: hid device
 *
 * Tell underlying HW to start delivering events from the device.
 * This function should be called someसमय after successful call
 * to hid_hw_start().
 */
पूर्णांक hid_hw_खोलो(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret;

	ret = mutex_lock_समाप्तable(&hdev->ll_खोलो_lock);
	अगर (ret)
		वापस ret;

	अगर (!hdev->ll_खोलो_count++) अणु
		ret = hdev->ll_driver->खोलो(hdev);
		अगर (ret)
			hdev->ll_खोलो_count--;
	पूर्ण

	mutex_unlock(&hdev->ll_खोलो_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hid_hw_खोलो);

/**
 * hid_hw_बंद - संकेत underlaying HW to stop delivering events
 *
 * @hdev: hid device
 *
 * This function indicates that we are not पूर्णांकerested in the events
 * from this device anymore. Delivery of events may or may not stop,
 * depending on the number of users still outstanding.
 */
व्योम hid_hw_बंद(काष्ठा hid_device *hdev)
अणु
	mutex_lock(&hdev->ll_खोलो_lock);
	अगर (!--hdev->ll_खोलो_count)
		hdev->ll_driver->बंद(hdev);
	mutex_unlock(&hdev->ll_खोलो_lock);
पूर्ण
EXPORT_SYMBOL_GPL(hid_hw_बंद);

काष्ठा hid_dynid अणु
	काष्ठा list_head list;
	काष्ठा hid_device_id id;
पूर्ण;

/**
 * new_id_store - add a new HID device ID to this driver and re-probe devices
 * @drv: target device driver
 * @buf: buffer क्रम scanning device ID data
 * @count: input size
 *
 * Adds a new dynamic hid device ID to this driver,
 * and causes the driver to probe क्रम all devices again.
 */
अटल sमाप_प्रकार new_id_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा hid_driver *hdrv = to_hid_driver(drv);
	काष्ठा hid_dynid *dynid;
	__u32 bus, venकरोr, product;
	अचिन्हित दीर्घ driver_data = 0;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%x %x %x %lx",
			&bus, &venकरोr, &product, &driver_data);
	अगर (ret < 3)
		वापस -EINVAL;

	dynid = kzalloc(माप(*dynid), GFP_KERNEL);
	अगर (!dynid)
		वापस -ENOMEM;

	dynid->id.bus = bus;
	dynid->id.group = HID_GROUP_ANY;
	dynid->id.venकरोr = venकरोr;
	dynid->id.product = product;
	dynid->id.driver_data = driver_data;

	spin_lock(&hdrv->dyn_lock);
	list_add_tail(&dynid->list, &hdrv->dyn_list);
	spin_unlock(&hdrv->dyn_lock);

	ret = driver_attach(&hdrv->driver);

	वापस ret ? : count;
पूर्ण
अटल DRIVER_ATTR_WO(new_id);

अटल काष्ठा attribute *hid_drv_attrs[] = अणु
	&driver_attr_new_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(hid_drv);

अटल व्योम hid_मुक्त_dynids(काष्ठा hid_driver *hdrv)
अणु
	काष्ठा hid_dynid *dynid, *n;

	spin_lock(&hdrv->dyn_lock);
	list_क्रम_each_entry_safe(dynid, n, &hdrv->dyn_list, list) अणु
		list_del(&dynid->list);
		kमुक्त(dynid);
	पूर्ण
	spin_unlock(&hdrv->dyn_lock);
पूर्ण

स्थिर काष्ठा hid_device_id *hid_match_device(काष्ठा hid_device *hdev,
					     काष्ठा hid_driver *hdrv)
अणु
	काष्ठा hid_dynid *dynid;

	spin_lock(&hdrv->dyn_lock);
	list_क्रम_each_entry(dynid, &hdrv->dyn_list, list) अणु
		अगर (hid_match_one_id(hdev, &dynid->id)) अणु
			spin_unlock(&hdrv->dyn_lock);
			वापस &dynid->id;
		पूर्ण
	पूर्ण
	spin_unlock(&hdrv->dyn_lock);

	वापस hid_match_id(hdev, hdrv->id_table);
पूर्ण
EXPORT_SYMBOL_GPL(hid_match_device);

अटल पूर्णांक hid_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा hid_driver *hdrv = to_hid_driver(drv);
	काष्ठा hid_device *hdev = to_hid_device(dev);

	वापस hid_match_device(hdev, hdrv) != शून्य;
पूर्ण

/**
 * hid_compare_device_paths - check अगर both devices share the same path
 * @hdev_a: hid device
 * @hdev_b: hid device
 * @separator: अक्षर to use as separator
 *
 * Check अगर two devices share the same path up to the last occurrence of
 * the separator अक्षर. Both paths must exist (i.e., zero-length paths
 * करोn't match).
 */
bool hid_compare_device_paths(काष्ठा hid_device *hdev_a,
			      काष्ठा hid_device *hdev_b, अक्षर separator)
अणु
	पूर्णांक n1 = म_खोजप(hdev_a->phys, separator) - hdev_a->phys;
	पूर्णांक n2 = म_खोजप(hdev_b->phys, separator) - hdev_b->phys;

	अगर (n1 != n2 || n1 <= 0 || n2 <= 0)
		वापस false;

	वापस !म_भेदन(hdev_a->phys, hdev_b->phys, n1);
पूर्ण
EXPORT_SYMBOL_GPL(hid_compare_device_paths);

अटल पूर्णांक hid_device_probe(काष्ठा device *dev)
अणु
	काष्ठा hid_driver *hdrv = to_hid_driver(dev->driver);
	काष्ठा hid_device *hdev = to_hid_device(dev);
	स्थिर काष्ठा hid_device_id *id;
	पूर्णांक ret = 0;

	अगर (करोwn_पूर्णांकerruptible(&hdev->driver_input_lock)) अणु
		ret = -EINTR;
		जाओ end;
	पूर्ण
	hdev->io_started = false;

	clear_bit(ffs(HID_STAT_REPROBED), &hdev->status);

	अगर (!hdev->driver) अणु
		id = hid_match_device(hdev, hdrv);
		अगर (id == शून्य) अणु
			ret = -ENODEV;
			जाओ unlock;
		पूर्ण

		अगर (hdrv->match) अणु
			अगर (!hdrv->match(hdev, hid_ignore_special_drivers)) अणु
				ret = -ENODEV;
				जाओ unlock;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * hid-generic implements .match(), so अगर
			 * hid_ignore_special_drivers is set, we can safely
			 * वापस.
			 */
			अगर (hid_ignore_special_drivers) अणु
				ret = -ENODEV;
				जाओ unlock;
			पूर्ण
		पूर्ण

		/* reset the quirks that has been previously set */
		hdev->quirks = hid_lookup_quirk(hdev);
		hdev->driver = hdrv;
		अगर (hdrv->probe) अणु
			ret = hdrv->probe(hdev, id);
		पूर्ण अन्यथा अणु /* शेष probe */
			ret = hid_खोलो_report(hdev);
			अगर (!ret)
				ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
		पूर्ण
		अगर (ret) अणु
			hid_बंद_report(hdev);
			hdev->driver = शून्य;
		पूर्ण
	पूर्ण
unlock:
	अगर (!hdev->io_started)
		up(&hdev->driver_input_lock);
end:
	वापस ret;
पूर्ण

अटल पूर्णांक hid_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा hid_driver *hdrv;
	पूर्णांक ret = 0;

	अगर (करोwn_पूर्णांकerruptible(&hdev->driver_input_lock)) अणु
		ret = -EINTR;
		जाओ end;
	पूर्ण
	hdev->io_started = false;

	hdrv = hdev->driver;
	अगर (hdrv) अणु
		अगर (hdrv->हटाओ)
			hdrv->हटाओ(hdev);
		अन्यथा /* शेष हटाओ */
			hid_hw_stop(hdev);
		hid_बंद_report(hdev);
		hdev->driver = शून्य;
	पूर्ण

	अगर (!hdev->io_started)
		up(&hdev->driver_input_lock);
end:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			     अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = container_of(dev, काष्ठा hid_device, dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "hid:b%04Xg%04Xv%08Xp%08X\n",
			 hdev->bus, hdev->group, hdev->venकरोr, hdev->product);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *hid_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
अटल काष्ठा bin_attribute *hid_dev_bin_attrs[] = अणु
	&dev_bin_attr_report_desc,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group hid_dev_group = अणु
	.attrs = hid_dev_attrs,
	.bin_attrs = hid_dev_bin_attrs,
पूर्ण;
__ATTRIBUTE_GROUPS(hid_dev);

अटल पूर्णांक hid_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);

	अगर (add_uevent_var(env, "HID_ID=%04X:%08X:%08X",
			hdev->bus, hdev->venकरोr, hdev->product))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "HID_NAME=%s", hdev->name))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "HID_PHYS=%s", hdev->phys))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "HID_UNIQ=%s", hdev->uniq))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "MODALIAS=hid:b%04Xg%04Xv%08Xp%08X",
			   hdev->bus, hdev->group, hdev->venकरोr, hdev->product))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

काष्ठा bus_type hid_bus_type = अणु
	.name		= "hid",
	.dev_groups	= hid_dev_groups,
	.drv_groups	= hid_drv_groups,
	.match		= hid_bus_match,
	.probe		= hid_device_probe,
	.हटाओ		= hid_device_हटाओ,
	.uevent		= hid_uevent,
पूर्ण;
EXPORT_SYMBOL(hid_bus_type);

पूर्णांक hid_add_device(काष्ठा hid_device *hdev)
अणु
	अटल atomic_t id = ATOMIC_INIT(0);
	पूर्णांक ret;

	अगर (WARN_ON(hdev->status & HID_STAT_ADDED))
		वापस -EBUSY;

	hdev->quirks = hid_lookup_quirk(hdev);

	/* we need to समाप्त them here, otherwise they will stay allocated to
	 * रुको क्रम coming driver */
	अगर (hid_ignore(hdev))
		वापस -ENODEV;

	/*
	 * Check क्रम the mandatory transport channel.
	 */
	 अगर (!hdev->ll_driver->raw_request) अणु
		hid_err(hdev, "transport driver missing .raw_request()\n");
		वापस -EINVAL;
	 पूर्ण

	/*
	 * Read the device report descriptor once and use as ढाँचा
	 * क्रम the driver-specअगरic modअगरications.
	 */
	ret = hdev->ll_driver->parse(hdev);
	अगर (ret)
		वापस ret;
	अगर (!hdev->dev_rdesc)
		वापस -ENODEV;

	/*
	 * Scan generic devices क्रम group inक्रमmation
	 */
	अगर (hid_ignore_special_drivers) अणु
		hdev->group = HID_GROUP_GENERIC;
	पूर्ण अन्यथा अगर (!hdev->group &&
		   !(hdev->quirks & HID_QUIRK_HAVE_SPECIAL_DRIVER)) अणु
		ret = hid_scan_report(hdev);
		अगर (ret)
			hid_warn(hdev, "bad device descriptor (%d)\n", ret);
	पूर्ण

	/* XXX hack, any other cleaner solution after the driver core
	 * is converted to allow more than 20 bytes as the device name? */
	dev_set_name(&hdev->dev, "%04X:%04X:%04X.%04X", hdev->bus,
		     hdev->venकरोr, hdev->product, atomic_inc_वापस(&id));

	hid_debug_रेजिस्टर(hdev, dev_name(&hdev->dev));
	ret = device_add(&hdev->dev);
	अगर (!ret)
		hdev->status |= HID_STAT_ADDED;
	अन्यथा
		hid_debug_unरेजिस्टर(hdev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hid_add_device);

/**
 * hid_allocate_device - allocate new hid device descriptor
 *
 * Allocate and initialize hid device, so that hid_destroy_device might be
 * used to मुक्त it.
 *
 * New hid_device poपूर्णांकer is वापसed on success, otherwise ERR_PTR encoded
 * error value.
 */
काष्ठा hid_device *hid_allocate_device(व्योम)
अणु
	काष्ठा hid_device *hdev;
	पूर्णांक ret = -ENOMEM;

	hdev = kzalloc(माप(*hdev), GFP_KERNEL);
	अगर (hdev == शून्य)
		वापस ERR_PTR(ret);

	device_initialize(&hdev->dev);
	hdev->dev.release = hid_device_release;
	hdev->dev.bus = &hid_bus_type;
	device_enable_async_suspend(&hdev->dev);

	hid_बंद_report(hdev);

	init_रुकोqueue_head(&hdev->debug_रुको);
	INIT_LIST_HEAD(&hdev->debug_list);
	spin_lock_init(&hdev->debug_list_lock);
	sema_init(&hdev->driver_input_lock, 1);
	mutex_init(&hdev->ll_खोलो_lock);

	वापस hdev;
पूर्ण
EXPORT_SYMBOL_GPL(hid_allocate_device);

अटल व्योम hid_हटाओ_device(काष्ठा hid_device *hdev)
अणु
	अगर (hdev->status & HID_STAT_ADDED) अणु
		device_del(&hdev->dev);
		hid_debug_unरेजिस्टर(hdev);
		hdev->status &= ~HID_STAT_ADDED;
	पूर्ण
	kमुक्त(hdev->dev_rdesc);
	hdev->dev_rdesc = शून्य;
	hdev->dev_rsize = 0;
पूर्ण

/**
 * hid_destroy_device - मुक्त previously allocated device
 *
 * @hdev: hid device
 *
 * If you allocate hid_device through hid_allocate_device, you should ever
 * मुक्त by this function.
 */
व्योम hid_destroy_device(काष्ठा hid_device *hdev)
अणु
	hid_हटाओ_device(hdev);
	put_device(&hdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(hid_destroy_device);


अटल पूर्णांक __hid_bus_reprobe_drivers(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा hid_driver *hdrv = data;
	काष्ठा hid_device *hdev = to_hid_device(dev);

	अगर (hdev->driver == hdrv &&
	    !hdrv->match(hdev, hid_ignore_special_drivers) &&
	    !test_and_set_bit(ffs(HID_STAT_REPROBED), &hdev->status))
		वापस device_reprobe(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __hid_bus_driver_added(काष्ठा device_driver *drv, व्योम *data)
अणु
	काष्ठा hid_driver *hdrv = to_hid_driver(drv);

	अगर (hdrv->match) अणु
		bus_क्रम_each_dev(&hid_bus_type, शून्य, hdrv,
				 __hid_bus_reprobe_drivers);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __bus_हटाओd_driver(काष्ठा device_driver *drv, व्योम *data)
अणु
	वापस bus_rescan_devices(&hid_bus_type);
पूर्ण

पूर्णांक __hid_रेजिस्टर_driver(काष्ठा hid_driver *hdrv, काष्ठा module *owner,
		स्थिर अक्षर *mod_name)
अणु
	पूर्णांक ret;

	hdrv->driver.name = hdrv->name;
	hdrv->driver.bus = &hid_bus_type;
	hdrv->driver.owner = owner;
	hdrv->driver.mod_name = mod_name;

	INIT_LIST_HEAD(&hdrv->dyn_list);
	spin_lock_init(&hdrv->dyn_lock);

	ret = driver_रेजिस्टर(&hdrv->driver);

	अगर (ret == 0)
		bus_क्रम_each_drv(&hid_bus_type, शून्य, शून्य,
				 __hid_bus_driver_added);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__hid_रेजिस्टर_driver);

व्योम hid_unरेजिस्टर_driver(काष्ठा hid_driver *hdrv)
अणु
	driver_unरेजिस्टर(&hdrv->driver);
	hid_मुक्त_dynids(hdrv);

	bus_क्रम_each_drv(&hid_bus_type, शून्य, hdrv, __bus_हटाओd_driver);
पूर्ण
EXPORT_SYMBOL_GPL(hid_unरेजिस्टर_driver);

पूर्णांक hid_check_keys_pressed(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_input *hidinput;
	पूर्णांक i;

	अगर (!(hid->claimed & HID_CLAIMED_INPUT))
		वापस 0;

	list_क्रम_each_entry(hidinput, &hid->inमाला_दो, list) अणु
		क्रम (i = 0; i < BITS_TO_LONGS(KEY_MAX); i++)
			अगर (hidinput->input->key[i])
				वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hid_check_keys_pressed);

अटल पूर्णांक __init hid_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (hid_debug)
		pr_warn("hid_debug is now used solely for parser and driver debugging.\n"
			"debugfs is now used for inspecting the device (report descriptor, reports)\n");

	ret = bus_रेजिस्टर(&hid_bus_type);
	अगर (ret) अणु
		pr_err("can't register hid bus\n");
		जाओ err;
	पूर्ण

	ret = hidraw_init();
	अगर (ret)
		जाओ err_bus;

	hid_debug_init();

	वापस 0;
err_bus:
	bus_unरेजिस्टर(&hid_bus_type);
err:
	वापस ret;
पूर्ण

अटल व्योम __निकास hid_निकास(व्योम)
अणु
	hid_debug_निकास();
	hidraw_निकास();
	bus_unरेजिस्टर(&hid_bus_type);
	hid_quirks_निकास(HID_BUS_ANY);
पूर्ण

module_init(hid_init);
module_निकास(hid_निकास);

MODULE_AUTHOR("Andreas Gal");
MODULE_AUTHOR("Vojtech Pavlik");
MODULE_AUTHOR("Jiri Kosina");
MODULE_LICENSE("GPL");
