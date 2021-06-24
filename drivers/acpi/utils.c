<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi_utils.c - ACPI Utility Functions ($Revision: 10 $)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: utils: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dynamic_debug.h>

#समावेश "internal.h"
#समावेश "sleep.h"

/* --------------------------------------------------------------------------
                            Object Evaluation Helpers
   -------------------------------------------------------------------------- */
अटल व्योम acpi_util_eval_error(acpi_handle h, acpi_string p, acpi_status s)
अणु
	acpi_handle_debug(h, "Evaluate [%s]: %s\n", p, acpi_क्रमmat_exception(s));
पूर्ण

acpi_status
acpi_extract_package(जोड़ acpi_object *package,
		     काष्ठा acpi_buffer *क्रमmat, काष्ठा acpi_buffer *buffer)
अणु
	u32 size_required = 0;
	u32 tail_offset = 0;
	अक्षर *क्रमmat_string = शून्य;
	u32 क्रमmat_count = 0;
	u32 i = 0;
	u8 *head = शून्य;
	u8 *tail = शून्य;


	अगर (!package || (package->type != ACPI_TYPE_PACKAGE)
	    || (package->package.count < 1)) अणु
		pr_debug("Invalid package argument\n");
		वापस AE_BAD_PARAMETER;
	पूर्ण

	अगर (!क्रमmat || !क्रमmat->poपूर्णांकer || (क्रमmat->length < 1)) अणु
		pr_debug("Invalid format argument\n");
		वापस AE_BAD_PARAMETER;
	पूर्ण

	अगर (!buffer) अणु
		pr_debug("Invalid buffer argument\n");
		वापस AE_BAD_PARAMETER;
	पूर्ण

	क्रमmat_count = (क्रमmat->length / माप(अक्षर)) - 1;
	अगर (क्रमmat_count > package->package.count) अणु
		pr_debug("Format specifies more objects [%d] than present [%d]\n",
			 क्रमmat_count, package->package.count);
		वापस AE_BAD_DATA;
	पूर्ण

	क्रमmat_string = क्रमmat->poपूर्णांकer;

	/*
	 * Calculate size_required.
	 */
	क्रम (i = 0; i < क्रमmat_count; i++) अणु

		जोड़ acpi_object *element = &(package->package.elements[i]);

		चयन (element->type) अणु

		हाल ACPI_TYPE_INTEGER:
			चयन (क्रमmat_string[i]) अणु
			हाल 'N':
				size_required += माप(u64);
				tail_offset += माप(u64);
				अवरोध;
			हाल 'S':
				size_required +=
				    माप(अक्षर *) + माप(u64) +
				    माप(अक्षर);
				tail_offset += माप(अक्षर *);
				अवरोध;
			शेष:
				pr_debug("Invalid package element [%d]: got number, expected [%c]\n",
					 i, क्रमmat_string[i]);
				वापस AE_BAD_DATA;
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_STRING:
		हाल ACPI_TYPE_BUFFER:
			चयन (क्रमmat_string[i]) अणु
			हाल 'S':
				size_required +=
				    माप(अक्षर *) +
				    (element->string.length * माप(अक्षर)) +
				    माप(अक्षर);
				tail_offset += माप(अक्षर *);
				अवरोध;
			हाल 'B':
				size_required +=
				    माप(u8 *) + element->buffer.length;
				tail_offset += माप(u8 *);
				अवरोध;
			शेष:
				pr_debug("Invalid package element [%d] got string/buffer, expected [%c]\n",
					 i, क्रमmat_string[i]);
				वापस AE_BAD_DATA;
			पूर्ण
			अवरोध;
		हाल ACPI_TYPE_LOCAL_REFERENCE:
			चयन (क्रमmat_string[i]) अणु
			हाल 'R':
				size_required += माप(व्योम *);
				tail_offset += माप(व्योम *);
				अवरोध;
			शेष:
				pr_debug("Invalid package element [%d] got reference, expected [%c]\n",
					 i, क्रमmat_string[i]);
				वापस AE_BAD_DATA;
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_PACKAGE:
		शेष:
			pr_debug("Unsupported element at index=%d\n", i);
			/* TBD: handle nested packages... */
			वापस AE_SUPPORT;
		पूर्ण
	पूर्ण

	/*
	 * Validate output buffer.
	 */
	अगर (buffer->length == ACPI_ALLOCATE_BUFFER) अणु
		buffer->poपूर्णांकer = ACPI_ALLOCATE_ZEROED(size_required);
		अगर (!buffer->poपूर्णांकer)
			वापस AE_NO_MEMORY;
		buffer->length = size_required;
	पूर्ण अन्यथा अणु
		अगर (buffer->length < size_required) अणु
			buffer->length = size_required;
			वापस AE_BUFFER_OVERFLOW;
		पूर्ण अन्यथा अगर (buffer->length != size_required ||
			   !buffer->poपूर्णांकer) अणु
			वापस AE_BAD_PARAMETER;
		पूर्ण
	पूर्ण

	head = buffer->poपूर्णांकer;
	tail = buffer->poपूर्णांकer + tail_offset;

	/*
	 * Extract package data.
	 */
	क्रम (i = 0; i < क्रमmat_count; i++) अणु

		u8 **poपूर्णांकer = शून्य;
		जोड़ acpi_object *element = &(package->package.elements[i]);

		चयन (element->type) अणु

		हाल ACPI_TYPE_INTEGER:
			चयन (क्रमmat_string[i]) अणु
			हाल 'N':
				*((u64 *) head) =
				    element->पूर्णांकeger.value;
				head += माप(u64);
				अवरोध;
			हाल 'S':
				poपूर्णांकer = (u8 **) head;
				*poपूर्णांकer = tail;
				*((u64 *) tail) =
				    element->पूर्णांकeger.value;
				head += माप(u64 *);
				tail += माप(u64);
				/* शून्य terminate string */
				*tail = (अक्षर)0;
				tail += माप(अक्षर);
				अवरोध;
			शेष:
				/* Should never get here */
				अवरोध;
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_STRING:
		हाल ACPI_TYPE_BUFFER:
			चयन (क्रमmat_string[i]) अणु
			हाल 'S':
				poपूर्णांकer = (u8 **) head;
				*poपूर्णांकer = tail;
				स_नकल(tail, element->string.poपूर्णांकer,
				       element->string.length);
				head += माप(अक्षर *);
				tail += element->string.length * माप(अक्षर);
				/* शून्य terminate string */
				*tail = (अक्षर)0;
				tail += माप(अक्षर);
				अवरोध;
			हाल 'B':
				poपूर्णांकer = (u8 **) head;
				*poपूर्णांकer = tail;
				स_नकल(tail, element->buffer.poपूर्णांकer,
				       element->buffer.length);
				head += माप(u8 *);
				tail += element->buffer.length;
				अवरोध;
			शेष:
				/* Should never get here */
				अवरोध;
			पूर्ण
			अवरोध;
		हाल ACPI_TYPE_LOCAL_REFERENCE:
			चयन (क्रमmat_string[i]) अणु
			हाल 'R':
				*(व्योम **)head =
				    (व्योम *)element->reference.handle;
				head += माप(व्योम *);
				अवरोध;
			शेष:
				/* Should never get here */
				अवरोध;
			पूर्ण
			अवरोध;
		हाल ACPI_TYPE_PACKAGE:
			/* TBD: handle nested packages... */
		शेष:
			/* Should never get here */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस AE_OK;
पूर्ण

EXPORT_SYMBOL(acpi_extract_package);

acpi_status
acpi_evaluate_पूर्णांकeger(acpi_handle handle,
		      acpi_string pathname,
		      काष्ठा acpi_object_list *arguments, अचिन्हित दीर्घ दीर्घ *data)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_object element;
	काष्ठा acpi_buffer buffer = अणु 0, शून्य पूर्ण;

	अगर (!data)
		वापस AE_BAD_PARAMETER;

	buffer.length = माप(जोड़ acpi_object);
	buffer.poपूर्णांकer = &element;
	status = acpi_evaluate_object(handle, pathname, arguments, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_util_eval_error(handle, pathname, status);
		वापस status;
	पूर्ण

	अगर (element.type != ACPI_TYPE_INTEGER) अणु
		acpi_util_eval_error(handle, pathname, AE_BAD_DATA);
		वापस AE_BAD_DATA;
	पूर्ण

	*data = element.पूर्णांकeger.value;

	acpi_handle_debug(handle, "Return value [%llu]\n", *data);

	वापस AE_OK;
पूर्ण

EXPORT_SYMBOL(acpi_evaluate_पूर्णांकeger);

acpi_status
acpi_evaluate_reference(acpi_handle handle,
			acpi_string pathname,
			काष्ठा acpi_object_list *arguments,
			काष्ठा acpi_handle_list *list)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_object *package = शून्य;
	जोड़ acpi_object *element = शून्य;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	u32 i = 0;


	अगर (!list) अणु
		वापस AE_BAD_PARAMETER;
	पूर्ण

	/* Evaluate object. */

	status = acpi_evaluate_object(handle, pathname, arguments, &buffer);
	अगर (ACPI_FAILURE(status))
		जाओ end;

	package = buffer.poपूर्णांकer;

	अगर ((buffer.length == 0) || !package) अणु
		status = AE_BAD_DATA;
		acpi_util_eval_error(handle, pathname, status);
		जाओ end;
	पूर्ण
	अगर (package->type != ACPI_TYPE_PACKAGE) अणु
		status = AE_BAD_DATA;
		acpi_util_eval_error(handle, pathname, status);
		जाओ end;
	पूर्ण
	अगर (!package->package.count) अणु
		status = AE_BAD_DATA;
		acpi_util_eval_error(handle, pathname, status);
		जाओ end;
	पूर्ण

	अगर (package->package.count > ACPI_MAX_HANDLES) अणु
		kमुक्त(package);
		वापस AE_NO_MEMORY;
	पूर्ण
	list->count = package->package.count;

	/* Extract package data. */

	क्रम (i = 0; i < list->count; i++) अणु

		element = &(package->package.elements[i]);

		अगर (element->type != ACPI_TYPE_LOCAL_REFERENCE) अणु
			status = AE_BAD_DATA;
			acpi_util_eval_error(handle, pathname, status);
			अवरोध;
		पूर्ण

		अगर (!element->reference.handle) अणु
			status = AE_शून्य_ENTRY;
			acpi_util_eval_error(handle, pathname, status);
			अवरोध;
		पूर्ण
		/* Get the  acpi_handle. */

		list->handles[i] = element->reference.handle;
		acpi_handle_debug(list->handles[i], "Found in reference list\n");
	पूर्ण

      end:
	अगर (ACPI_FAILURE(status)) अणु
		list->count = 0;
		//kमुक्त(list->handles);
	पूर्ण

	kमुक्त(buffer.poपूर्णांकer);

	वापस status;
पूर्ण

EXPORT_SYMBOL(acpi_evaluate_reference);

acpi_status
acpi_get_physical_device_location(acpi_handle handle, काष्ठा acpi_pld_info **pld)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *output;

	status = acpi_evaluate_object(handle, "_PLD", शून्य, &buffer);

	अगर (ACPI_FAILURE(status))
		वापस status;

	output = buffer.poपूर्णांकer;

	अगर (!output || output->type != ACPI_TYPE_PACKAGE
	    || !output->package.count
	    || output->package.elements[0].type != ACPI_TYPE_BUFFER
	    || output->package.elements[0].buffer.length < ACPI_PLD_REV1_BUFFER_SIZE) अणु
		status = AE_TYPE;
		जाओ out;
	पूर्ण

	status = acpi_decode_pld_buffer(
			output->package.elements[0].buffer.poपूर्णांकer,
			output->package.elements[0].buffer.length,
			pld);

out:
	kमुक्त(buffer.poपूर्णांकer);
	वापस status;
पूर्ण
EXPORT_SYMBOL(acpi_get_physical_device_location);

/**
 * acpi_evaluate_ost: Evaluate _OST क्रम hotplug operations
 * @handle: ACPI device handle
 * @source_event: source event code
 * @status_code: status code
 * @status_buf: optional detailed inक्रमmation (शून्य अगर none)
 *
 * Evaluate _OST क्रम hotplug operations. All ACPI hotplug handlers
 * must call this function when evaluating _OST क्रम hotplug operations.
 * When the platक्रमm करोes not support _OST, this function has no effect.
 */
acpi_status
acpi_evaluate_ost(acpi_handle handle, u32 source_event, u32 status_code,
		  काष्ठा acpi_buffer *status_buf)
अणु
	जोड़ acpi_object params[3] = अणु
		अणु.type = ACPI_TYPE_INTEGER,पूर्ण,
		अणु.type = ACPI_TYPE_INTEGER,पूर्ण,
		अणु.type = ACPI_TYPE_BUFFER,पूर्ण
	पूर्ण;
	काष्ठा acpi_object_list arg_list = अणु3, paramsपूर्ण;

	params[0].पूर्णांकeger.value = source_event;
	params[1].पूर्णांकeger.value = status_code;
	अगर (status_buf != शून्य) अणु
		params[2].buffer.poपूर्णांकer = status_buf->poपूर्णांकer;
		params[2].buffer.length = status_buf->length;
	पूर्ण अन्यथा अणु
		params[2].buffer.poपूर्णांकer = शून्य;
		params[2].buffer.length = 0;
	पूर्ण

	वापस acpi_evaluate_object(handle, "_OST", &arg_list, शून्य);
पूर्ण
EXPORT_SYMBOL(acpi_evaluate_ost);

/**
 * acpi_handle_path: Return the object path of handle
 * @handle: ACPI device handle
 *
 * Caller must मुक्त the वापसed buffer
 */
अटल अक्षर *acpi_handle_path(acpi_handle handle)
अणु
	काष्ठा acpi_buffer buffer = अणु
		.length = ACPI_ALLOCATE_BUFFER,
		.poपूर्णांकer = शून्य
	पूर्ण;

	अगर (in_पूर्णांकerrupt() ||
	    acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer) != AE_OK)
		वापस शून्य;
	वापस buffer.poपूर्णांकer;
पूर्ण

/**
 * acpi_handle_prपूर्णांकk: Prपूर्णांक message with ACPI prefix and object path
 * @level: log level
 * @handle: ACPI device handle
 * @fmt: क्रमmat string
 *
 * This function is called through acpi_handle_<level> macros and prपूर्णांकs
 * a message with ACPI prefix and object path.  This function acquires
 * the global namespace mutex to obtain an object path.  In पूर्णांकerrupt
 * context, it shows the object path as <n/a>.
 */
व्योम
acpi_handle_prपूर्णांकk(स्थिर अक्षर *level, acpi_handle handle, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	स्थिर अक्षर *path;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	path = acpi_handle_path(handle);
	prपूर्णांकk("%sACPI: %s: %pV", level, path ? path : "<n/a>" , &vaf);

	बहु_पूर्ण(args);
	kमुक्त(path);
पूर्ण
EXPORT_SYMBOL(acpi_handle_prपूर्णांकk);

#अगर defined(CONFIG_DYNAMIC_DEBUG)
/**
 * __acpi_handle_debug: pr_debug with ACPI prefix and object path
 * @descriptor: Dynamic Debug descriptor
 * @handle: ACPI device handle
 * @fmt: क्रमmat string
 *
 * This function is called through acpi_handle_debug macro and debug
 * prपूर्णांकs a message with ACPI prefix and object path. This function
 * acquires the global namespace mutex to obtain an object path.  In
 * पूर्णांकerrupt context, it shows the object path as <n/a>.
 */
व्योम
__acpi_handle_debug(काष्ठा _ddebug *descriptor, acpi_handle handle,
		    स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	स्थिर अक्षर *path;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	path = acpi_handle_path(handle);
	__dynamic_pr_debug(descriptor, "ACPI: %s: %pV", path ? path : "<n/a>", &vaf);

	बहु_पूर्ण(args);
	kमुक्त(path);
पूर्ण
EXPORT_SYMBOL(__acpi_handle_debug);
#पूर्ण_अगर

/**
 * acpi_evaluation_failure_warn - Log evaluation failure warning.
 * @handle: Parent object handle.
 * @name: Name of the object whose evaluation has failed.
 * @status: Status value वापसed by the failing object evaluation.
 */
व्योम acpi_evaluation_failure_warn(acpi_handle handle, स्थिर अक्षर *name,
				  acpi_status status)
अणु
	acpi_handle_warn(handle, "%s evaluation failed: %s\n", name,
			 acpi_क्रमmat_exception(status));
पूर्ण
EXPORT_SYMBOL_GPL(acpi_evaluation_failure_warn);

/**
 * acpi_has_method: Check whether @handle has a method named @name
 * @handle: ACPI device handle
 * @name: name of object or method
 *
 * Check whether @handle has a method named @name.
 */
bool acpi_has_method(acpi_handle handle, अक्षर *name)
अणु
	acpi_handle पंचांगp;

	वापस ACPI_SUCCESS(acpi_get_handle(handle, name, &पंचांगp));
पूर्ण
EXPORT_SYMBOL(acpi_has_method);

acpi_status acpi_execute_simple_method(acpi_handle handle, अक्षर *method,
				       u64 arg)
अणु
	जोड़ acpi_object obj = अणु .type = ACPI_TYPE_INTEGER पूर्ण;
	काष्ठा acpi_object_list arg_list = अणु .count = 1, .poपूर्णांकer = &obj, पूर्ण;

	obj.पूर्णांकeger.value = arg;

	वापस acpi_evaluate_object(handle, method, &arg_list, शून्य);
पूर्ण
EXPORT_SYMBOL(acpi_execute_simple_method);

/**
 * acpi_evaluate_ej0: Evaluate _EJ0 method क्रम hotplug operations
 * @handle: ACPI device handle
 *
 * Evaluate device's _EJ0 method क्रम hotplug operations.
 */
acpi_status acpi_evaluate_ej0(acpi_handle handle)
अणु
	acpi_status status;

	status = acpi_execute_simple_method(handle, "_EJ0", 1);
	अगर (status == AE_NOT_FOUND)
		acpi_handle_warn(handle, "No _EJ0 support for device\n");
	अन्यथा अगर (ACPI_FAILURE(status))
		acpi_handle_warn(handle, "Eject failed (0x%x)\n", status);

	वापस status;
पूर्ण

/**
 * acpi_evaluate_lck: Evaluate _LCK method to lock/unlock device
 * @handle: ACPI device handle
 * @lock: lock device अगर non-zero, otherwise unlock device
 *
 * Evaluate device's _LCK method अगर present to lock/unlock device
 */
acpi_status acpi_evaluate_lck(acpi_handle handle, पूर्णांक lock)
अणु
	acpi_status status;

	status = acpi_execute_simple_method(handle, "_LCK", !!lock);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND) अणु
		अगर (lock)
			acpi_handle_warn(handle,
				"Locking device failed (0x%x)\n", status);
		अन्यथा
			acpi_handle_warn(handle,
				"Unlocking device failed (0x%x)\n", status);
	पूर्ण

	वापस status;
पूर्ण

/**
 * acpi_evaluate_reg: Evaluate _REG method to रेजिस्टर OpRegion presence
 * @handle: ACPI device handle
 * @space_id: ACPI address space id to रेजिस्टर OpRegion presence क्रम
 * @function: Parameter to pass to _REG one of ACPI_REG_CONNECT or
 *            ACPI_REG_DISCONNECT
 *
 * Evaluate device's _REG method to रेजिस्टर OpRegion presence.
 */
acpi_status acpi_evaluate_reg(acpi_handle handle, u8 space_id, u32 function)
अणु
	काष्ठा acpi_object_list arg_list;
	जोड़ acpi_object params[2];

	params[0].type = ACPI_TYPE_INTEGER;
	params[0].पूर्णांकeger.value = space_id;
	params[1].type = ACPI_TYPE_INTEGER;
	params[1].पूर्णांकeger.value = function;
	arg_list.count = 2;
	arg_list.poपूर्णांकer = params;

	वापस acpi_evaluate_object(handle, "_REG", &arg_list, शून्य);
पूर्ण
EXPORT_SYMBOL(acpi_evaluate_reg);

/**
 * acpi_evaluate_dsm - evaluate device's _DSM method
 * @handle: ACPI device handle
 * @guid: GUID of requested functions, should be 16 bytes
 * @rev: revision number of requested function
 * @func: requested function number
 * @argv4: the function specअगरic parameter
 *
 * Evaluate device's _DSM method with specअगरied GUID, revision id and
 * function number. Caller needs to मुक्त the वापसed object.
 *
 * Though ACPI defines the fourth parameter क्रम _DSM should be a package,
 * some old BIOSes करो expect a buffer or an पूर्णांकeger etc.
 */
जोड़ acpi_object *
acpi_evaluate_dsm(acpi_handle handle, स्थिर guid_t *guid, u64 rev, u64 func,
		  जोड़ acpi_object *argv4)
अणु
	acpi_status ret;
	काष्ठा acpi_buffer buf = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object params[4];
	काष्ठा acpi_object_list input = अणु
		.count = 4,
		.poपूर्णांकer = params,
	पूर्ण;

	params[0].type = ACPI_TYPE_BUFFER;
	params[0].buffer.length = 16;
	params[0].buffer.poपूर्णांकer = (u8 *)guid;
	params[1].type = ACPI_TYPE_INTEGER;
	params[1].पूर्णांकeger.value = rev;
	params[2].type = ACPI_TYPE_INTEGER;
	params[2].पूर्णांकeger.value = func;
	अगर (argv4) अणु
		params[3] = *argv4;
	पूर्ण अन्यथा अणु
		params[3].type = ACPI_TYPE_PACKAGE;
		params[3].package.count = 0;
		params[3].package.elements = शून्य;
	पूर्ण

	ret = acpi_evaluate_object(handle, "_DSM", &input, &buf);
	अगर (ACPI_SUCCESS(ret))
		वापस (जोड़ acpi_object *)buf.poपूर्णांकer;

	अगर (ret != AE_NOT_FOUND)
		acpi_handle_warn(handle,
				"failed to evaluate _DSM (0x%x)\n", ret);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(acpi_evaluate_dsm);

/**
 * acpi_check_dsm - check अगर _DSM method supports requested functions.
 * @handle: ACPI device handle
 * @guid: GUID of requested functions, should be 16 bytes at least
 * @rev: revision number of requested functions
 * @funcs: biपंचांगap of requested functions
 *
 * Evaluate device's _DSM method to check whether it supports requested
 * functions. Currently only support 64 functions at maximum, should be
 * enough क्रम now.
 */
bool acpi_check_dsm(acpi_handle handle, स्थिर guid_t *guid, u64 rev, u64 funcs)
अणु
	पूर्णांक i;
	u64 mask = 0;
	जोड़ acpi_object *obj;

	अगर (funcs == 0)
		वापस false;

	obj = acpi_evaluate_dsm(handle, guid, rev, 0, शून्य);
	अगर (!obj)
		वापस false;

	/* For compatibility, old BIOSes may वापस an पूर्णांकeger */
	अगर (obj->type == ACPI_TYPE_INTEGER)
		mask = obj->पूर्णांकeger.value;
	अन्यथा अगर (obj->type == ACPI_TYPE_BUFFER)
		क्रम (i = 0; i < obj->buffer.length && i < 8; i++)
			mask |= (((u64)obj->buffer.poपूर्णांकer[i]) << (i * 8));
	ACPI_FREE(obj);

	/*
	 * Bit 0 indicates whether there's support क्रम any functions other than
	 * function 0 क्रम the specअगरied GUID and revision.
	 */
	अगर ((mask & 0x1) && (mask & funcs) == funcs)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(acpi_check_dsm);

/**
 * acpi_dev_hid_uid_match - Match device by supplied HID and UID
 * @adev: ACPI device to match.
 * @hid2: Hardware ID of the device.
 * @uid2: Unique ID of the device, pass शून्य to not check _UID.
 *
 * Matches HID and UID in @adev with given @hid2 and @uid2.
 * Returns true अगर matches.
 */
bool acpi_dev_hid_uid_match(काष्ठा acpi_device *adev,
			    स्थिर अक्षर *hid2, स्थिर अक्षर *uid2)
अणु
	स्थिर अक्षर *hid1 = acpi_device_hid(adev);
	स्थिर अक्षर *uid1 = acpi_device_uid(adev);

	अगर (म_भेद(hid1, hid2))
		वापस false;

	अगर (!uid2)
		वापस true;

	वापस uid1 && !म_भेद(uid1, uid2);
पूर्ण
EXPORT_SYMBOL(acpi_dev_hid_uid_match);

/**
 * acpi_dev_found - Detect presence of a given ACPI device in the namespace.
 * @hid: Hardware ID of the device.
 *
 * Return %true अगर the device was present at the moment of invocation.
 * Note that अगर the device is pluggable, it may since have disappeared.
 *
 * For this function to work, acpi_bus_scan() must have been executed
 * which happens in the subsys_initcall() subsection. Hence, करो not
 * call from a subsys_initcall() or earlier (use acpi_get_devices()
 * instead). Calling from module_init() is fine (which is synonymous
 * with device_initcall()).
 */
bool acpi_dev_found(स्थिर अक्षर *hid)
अणु
	काष्ठा acpi_device_bus_id *acpi_device_bus_id;
	bool found = false;

	mutex_lock(&acpi_device_lock);
	list_क्रम_each_entry(acpi_device_bus_id, &acpi_bus_id_list, node)
		अगर (!म_भेद(acpi_device_bus_id->bus_id, hid)) अणु
			found = true;
			अवरोध;
		पूर्ण
	mutex_unlock(&acpi_device_lock);

	वापस found;
पूर्ण
EXPORT_SYMBOL(acpi_dev_found);

काष्ठा acpi_dev_match_info अणु
	काष्ठा acpi_device_id hid[2];
	स्थिर अक्षर *uid;
	s64 hrv;
पूर्ण;

अटल पूर्णांक acpi_dev_match_cb(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा acpi_device *adev = to_acpi_device(dev);
	स्थिर काष्ठा acpi_dev_match_info *match = data;
	अचिन्हित दीर्घ दीर्घ hrv;
	acpi_status status;

	अगर (acpi_match_device_ids(adev, match->hid))
		वापस 0;

	अगर (match->uid && (!adev->pnp.unique_id ||
	    म_भेद(adev->pnp.unique_id, match->uid)))
		वापस 0;

	अगर (match->hrv == -1)
		वापस 1;

	status = acpi_evaluate_पूर्णांकeger(adev->handle, "_HRV", शून्य, &hrv);
	अगर (ACPI_FAILURE(status))
		वापस 0;

	वापस hrv == match->hrv;
पूर्ण

/**
 * acpi_dev_present - Detect that a given ACPI device is present
 * @hid: Hardware ID of the device.
 * @uid: Unique ID of the device, pass शून्य to not check _UID
 * @hrv: Hardware Revision of the device, pass -1 to not check _HRV
 *
 * Return %true अगर a matching device was present at the moment of invocation.
 * Note that अगर the device is pluggable, it may since have disappeared.
 *
 * Note that unlike acpi_dev_found() this function checks the status
 * of the device. So क्रम devices which are present in the DSDT, but
 * which are disabled (their _STA callback वापसs 0) this function
 * will वापस false.
 *
 * For this function to work, acpi_bus_scan() must have been executed
 * which happens in the subsys_initcall() subsection. Hence, करो not
 * call from a subsys_initcall() or earlier (use acpi_get_devices()
 * instead). Calling from module_init() is fine (which is synonymous
 * with device_initcall()).
 */
bool acpi_dev_present(स्थिर अक्षर *hid, स्थिर अक्षर *uid, s64 hrv)
अणु
	काष्ठा acpi_dev_match_info match = अणुपूर्ण;
	काष्ठा device *dev;

	strlcpy(match.hid[0].id, hid, माप(match.hid[0].id));
	match.uid = uid;
	match.hrv = hrv;

	dev = bus_find_device(&acpi_bus_type, शून्य, &match, acpi_dev_match_cb);
	put_device(dev);
	वापस !!dev;
पूर्ण
EXPORT_SYMBOL(acpi_dev_present);

/**
 * acpi_dev_get_next_match_dev - Return the next match of ACPI device
 * @adev: Poपूर्णांकer to the previous ACPI device matching this @hid, @uid and @hrv
 * @hid: Hardware ID of the device.
 * @uid: Unique ID of the device, pass शून्य to not check _UID
 * @hrv: Hardware Revision of the device, pass -1 to not check _HRV
 *
 * Return the next match of ACPI device अगर another matching device was present
 * at the moment of invocation, or शून्य otherwise.
 *
 * FIXME: The function करोes not tolerate the sudden disappearance of @adev, e.g.
 * in the हाल of a hotplug event. That said, the caller should ensure that
 * this will never happen.
 *
 * The caller is responsible क्रम invoking acpi_dev_put() on the वापसed device.
 *
 * See additional inक्रमmation in acpi_dev_present() as well.
 */
काष्ठा acpi_device *
acpi_dev_get_next_match_dev(काष्ठा acpi_device *adev, स्थिर अक्षर *hid, स्थिर अक्षर *uid, s64 hrv)
अणु
	काष्ठा device *start = adev ? &adev->dev : शून्य;
	काष्ठा acpi_dev_match_info match = अणुपूर्ण;
	काष्ठा device *dev;

	strlcpy(match.hid[0].id, hid, माप(match.hid[0].id));
	match.uid = uid;
	match.hrv = hrv;

	dev = bus_find_device(&acpi_bus_type, start, &match, acpi_dev_match_cb);
	वापस dev ? to_acpi_device(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL(acpi_dev_get_next_match_dev);

/**
 * acpi_dev_get_first_match_dev - Return the first match of ACPI device
 * @hid: Hardware ID of the device.
 * @uid: Unique ID of the device, pass शून्य to not check _UID
 * @hrv: Hardware Revision of the device, pass -1 to not check _HRV
 *
 * Return the first match of ACPI device अगर a matching device was present
 * at the moment of invocation, or शून्य otherwise.
 *
 * The caller is responsible क्रम invoking acpi_dev_put() on the वापसed device.
 *
 * See additional inक्रमmation in acpi_dev_present() as well.
 */
काष्ठा acpi_device *
acpi_dev_get_first_match_dev(स्थिर अक्षर *hid, स्थिर अक्षर *uid, s64 hrv)
अणु
	वापस acpi_dev_get_next_match_dev(शून्य, hid, uid, hrv);
पूर्ण
EXPORT_SYMBOL(acpi_dev_get_first_match_dev);

/**
 * acpi_reduced_hardware - Return अगर this is an ACPI-reduced-hw machine
 *
 * Return true when running on an ACPI-reduced-hw machine, false otherwise.
 */
bool acpi_reduced_hardware(व्योम)
अणु
	वापस acpi_gbl_reduced_hardware;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_reduced_hardware);

/*
 * acpi_backlight= handling, this is करोne here rather then in video_detect.c
 * because __setup cannot be used in modules.
 */
अक्षर acpi_video_backlight_string[16];
EXPORT_SYMBOL(acpi_video_backlight_string);

अटल पूर्णांक __init acpi_backlight(अक्षर *str)
अणु
	strlcpy(acpi_video_backlight_string, str,
		माप(acpi_video_backlight_string));
	वापस 1;
पूर्ण
__setup("acpi_backlight=", acpi_backlight);

/**
 * acpi_match_platक्रमm_list - Check अगर the प्रणाली matches with a given list
 * @plat: poपूर्णांकer to acpi_platक्रमm_list table terminated by a शून्य entry
 *
 * Return the matched index अगर the प्रणाली is found in the platक्रमm list.
 * Otherwise, वापस a negative error code.
 */
पूर्णांक acpi_match_platक्रमm_list(स्थिर काष्ठा acpi_platक्रमm_list *plat)
अणु
	काष्ठा acpi_table_header hdr;
	पूर्णांक idx = 0;

	अगर (acpi_disabled)
		वापस -ENODEV;

	क्रम (; plat->oem_id[0]; plat++, idx++) अणु
		अगर (ACPI_FAILURE(acpi_get_table_header(plat->table, 0, &hdr)))
			जारी;

		अगर (म_भेदन(plat->oem_id, hdr.oem_id, ACPI_OEM_ID_SIZE))
			जारी;

		अगर (म_भेदन(plat->oem_table_id, hdr.oem_table_id, ACPI_OEM_TABLE_ID_SIZE))
			जारी;

		अगर ((plat->pred == all_versions) ||
		    (plat->pred == less_than_or_equal && hdr.oem_revision <= plat->oem_revision) ||
		    (plat->pred == greater_than_or_equal && hdr.oem_revision >= plat->oem_revision) ||
		    (plat->pred == equal && hdr.oem_revision == plat->oem_revision))
			वापस idx;
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(acpi_match_platक्रमm_list);
