<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _INPUT_COMPAT_H
#घोषणा _INPUT_COMPAT_H

/*
 * 32bit compatibility wrappers क्रम the input subप्रणाली.
 *
 * Very heavily based on evdev.c - Copyright (c) 1999-2002 Vojtech Pavlik
 */

#समावेश <linux/compiler.h>
#समावेश <linux/compat.h>
#समावेश <linux/input.h>

#अगर_घोषित CONFIG_COMPAT

काष्ठा input_event_compat अणु
	compat_uदीर्घ_t sec;
	compat_uदीर्घ_t usec;
	__u16 type;
	__u16 code;
	__s32 value;
पूर्ण;

काष्ठा ff_periodic_effect_compat अणु
	__u16 waveक्रमm;
	__u16 period;
	__s16 magnitude;
	__s16 offset;
	__u16 phase;

	काष्ठा ff_envelope envelope;

	__u32 custom_len;
	compat_uptr_t custom_data;
पूर्ण;

काष्ठा ff_effect_compat अणु
	__u16 type;
	__s16 id;
	__u16 direction;
	काष्ठा ff_trigger trigger;
	काष्ठा ff_replay replay;

	जोड़ अणु
		काष्ठा ff_स्थिरant_effect स्थिरant;
		काष्ठा ff_ramp_effect ramp;
		काष्ठा ff_periodic_effect_compat periodic;
		काष्ठा ff_condition_effect condition[2]; /* One क्रम each axis */
		काष्ठा ff_rumble_effect rumble;
	पूर्ण u;
पूर्ण;

अटल अंतरभूत माप_प्रकार input_event_size(व्योम)
अणु
	वापस (in_compat_syscall() && !COMPAT_USE_64BIT_TIME) ?
		माप(काष्ठा input_event_compat) : माप(काष्ठा input_event);
पूर्ण

#अन्यथा

अटल अंतरभूत माप_प्रकार input_event_size(व्योम)
अणु
	वापस माप(काष्ठा input_event);
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */

पूर्णांक input_event_from_user(स्थिर अक्षर __user *buffer,
			 काष्ठा input_event *event);

पूर्णांक input_event_to_user(अक्षर __user *buffer,
			स्थिर काष्ठा input_event *event);

पूर्णांक input_ff_effect_from_user(स्थिर अक्षर __user *buffer, माप_प्रकार size,
			      काष्ठा ff_effect *effect);

#पूर्ण_अगर /* _INPUT_COMPAT_H */
