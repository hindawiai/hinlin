<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  This code मुख्यtains a list of active profiling data काष्ठाures.
 *
 *    Copyright IBM Corp. 2009
 *    Author(s): Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 *
 *    Uses gcc-पूर्णांकernal data definitions.
 *    Based on the gcov-kernel patch by:
 *		 Hubertus Franke <frankeh@us.ibm.com>
 *		 Nigel Hinds <nhinds@us.ibm.com>
 *		 Rajan Ravindran <rajancr@us.ibm.com>
 *		 Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 *		 Paul Larson
 */

#घोषणा pr_fmt(fmt)	"gcov: " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश "gcov.h"

पूर्णांक gcov_events_enabled;
DEFINE_MUTEX(gcov_lock);

/**
 * gcov_enable_events - enable event reporting through gcov_event()
 *
 * Turn on reporting of profiling data load/unload-events through the
 * gcov_event() callback. Also replay all previous events once. This function
 * is needed because some events are potentially generated too early क्रम the
 * callback implementation to handle them initially.
 */
व्योम gcov_enable_events(व्योम)
अणु
	काष्ठा gcov_info *info = शून्य;

	mutex_lock(&gcov_lock);
	gcov_events_enabled = 1;

	/* Perक्रमm event callback क्रम previously रेजिस्टरed entries. */
	जबतक ((info = gcov_info_next(info))) अणु
		gcov_event(GCOV_ADD, info);
		cond_resched();
	पूर्ण

	mutex_unlock(&gcov_lock);
पूर्ण

/**
 * store_gcov_u32 - store 32 bit number in gcov क्रमmat to buffer
 * @buffer: target buffer or शून्य
 * @off: offset पूर्णांकo the buffer
 * @v: value to be stored
 *
 * Number क्रमmat defined by gcc: numbers are recorded in the 32 bit
 * अचिन्हित binary क्रमm of the endianness of the machine generating the
 * file. Returns the number of bytes stored. If @buffer is %शून्य, करोesn't
 * store anything.
 */
माप_प्रकार store_gcov_u32(व्योम *buffer, माप_प्रकार off, u32 v)
अणु
	u32 *data;

	अगर (buffer) अणु
		data = buffer + off;
		*data = v;
	पूर्ण

	वापस माप(*data);
पूर्ण

/**
 * store_gcov_u64 - store 64 bit number in gcov क्रमmat to buffer
 * @buffer: target buffer or शून्य
 * @off: offset पूर्णांकo the buffer
 * @v: value to be stored
 *
 * Number क्रमmat defined by gcc: numbers are recorded in the 32 bit
 * अचिन्हित binary क्रमm of the endianness of the machine generating the
 * file. 64 bit numbers are stored as two 32 bit numbers, the low part
 * first. Returns the number of bytes stored. If @buffer is %शून्य, करोesn't store
 * anything.
 */
माप_प्रकार store_gcov_u64(व्योम *buffer, माप_प्रकार off, u64 v)
अणु
	u32 *data;

	अगर (buffer) अणु
		data = buffer + off;

		data[0] = (v & 0xffffffffUL);
		data[1] = (v >> 32);
	पूर्ण

	वापस माप(*data) * 2;
पूर्ण

#अगर_घोषित CONFIG_MODULES
/* Update list and generate events when modules are unloaded. */
अटल पूर्णांक gcov_module_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
				व्योम *data)
अणु
	काष्ठा module *mod = data;
	काष्ठा gcov_info *info = शून्य;
	काष्ठा gcov_info *prev = शून्य;

	अगर (event != MODULE_STATE_GOING)
		वापस NOTIFY_OK;
	mutex_lock(&gcov_lock);

	/* Remove entries located in module from linked list. */
	जबतक ((info = gcov_info_next(info))) अणु
		अगर (gcov_info_within_module(info, mod)) अणु
			gcov_info_unlink(prev, info);
			अगर (gcov_events_enabled)
				gcov_event(GCOV_REMOVE, info);
		पूर्ण अन्यथा
			prev = info;
	पूर्ण

	mutex_unlock(&gcov_lock);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block gcov_nb = अणु
	.notअगरier_call	= gcov_module_notअगरier,
पूर्ण;

अटल पूर्णांक __init gcov_init(व्योम)
अणु
	वापस रेजिस्टर_module_notअगरier(&gcov_nb);
पूर्ण
device_initcall(gcov_init);
#पूर्ण_अगर /* CONFIG_MODULES */
