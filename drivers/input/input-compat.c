<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 32bit compatibility wrappers क्रम the input subप्रणाली.
 *
 * Very heavily based on evdev.c - Copyright (c) 1999-2002 Vojtech Pavlik
 */

#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश "input-compat.h"

#अगर_घोषित CONFIG_COMPAT

पूर्णांक input_event_from_user(स्थिर अक्षर __user *buffer,
			  काष्ठा input_event *event)
अणु
	अगर (in_compat_syscall() && !COMPAT_USE_64BIT_TIME) अणु
		काष्ठा input_event_compat compat_event;

		अगर (copy_from_user(&compat_event, buffer,
				   माप(काष्ठा input_event_compat)))
			वापस -EFAULT;

		event->input_event_sec = compat_event.sec;
		event->input_event_usec = compat_event.usec;
		event->type = compat_event.type;
		event->code = compat_event.code;
		event->value = compat_event.value;

	पूर्ण अन्यथा अणु
		अगर (copy_from_user(event, buffer, माप(काष्ठा input_event)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक input_event_to_user(अक्षर __user *buffer,
			स्थिर काष्ठा input_event *event)
अणु
	अगर (in_compat_syscall() && !COMPAT_USE_64BIT_TIME) अणु
		काष्ठा input_event_compat compat_event;

		compat_event.sec = event->input_event_sec;
		compat_event.usec = event->input_event_usec;
		compat_event.type = event->type;
		compat_event.code = event->code;
		compat_event.value = event->value;

		अगर (copy_to_user(buffer, &compat_event,
				 माप(काष्ठा input_event_compat)))
			वापस -EFAULT;

	पूर्ण अन्यथा अणु
		अगर (copy_to_user(buffer, event, माप(काष्ठा input_event)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक input_ff_effect_from_user(स्थिर अक्षर __user *buffer, माप_प्रकार size,
			      काष्ठा ff_effect *effect)
अणु
	अगर (in_compat_syscall()) अणु
		काष्ठा ff_effect_compat *compat_effect;

		अगर (size != माप(काष्ठा ff_effect_compat))
			वापस -EINVAL;

		/*
		 * It so happens that the poपूर्णांकer which needs to be changed
		 * is the last field in the काष्ठाure, so we can retrieve the
		 * whole thing and replace just the poपूर्णांकer.
		 */
		compat_effect = (काष्ठा ff_effect_compat *)effect;

		अगर (copy_from_user(compat_effect, buffer,
				   माप(काष्ठा ff_effect_compat)))
			वापस -EFAULT;

		अगर (compat_effect->type == FF_PERIODIC &&
		    compat_effect->u.periodic.waveक्रमm == FF_CUSTOM)
			effect->u.periodic.custom_data =
				compat_ptr(compat_effect->u.periodic.custom_data);
	पूर्ण अन्यथा अणु
		अगर (size != माप(काष्ठा ff_effect))
			वापस -EINVAL;

		अगर (copy_from_user(effect, buffer, माप(काष्ठा ff_effect)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा

पूर्णांक input_event_from_user(स्थिर अक्षर __user *buffer,
			 काष्ठा input_event *event)
अणु
	अगर (copy_from_user(event, buffer, माप(काष्ठा input_event)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक input_event_to_user(अक्षर __user *buffer,
			स्थिर काष्ठा input_event *event)
अणु
	अगर (copy_to_user(buffer, event, माप(काष्ठा input_event)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक input_ff_effect_from_user(स्थिर अक्षर __user *buffer, माप_प्रकार size,
			      काष्ठा ff_effect *effect)
अणु
	अगर (size != माप(काष्ठा ff_effect))
		वापस -EINVAL;

	अगर (copy_from_user(effect, buffer, माप(काष्ठा ff_effect)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */

EXPORT_SYMBOL_GPL(input_event_from_user);
EXPORT_SYMBOL_GPL(input_event_to_user);
EXPORT_SYMBOL_GPL(input_ff_effect_from_user);
