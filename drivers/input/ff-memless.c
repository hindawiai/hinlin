<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम memoryless devices
 *
 *  Copyright (c) 2006 Anssi Hannula <anssi.hannula@gmail.com>
 *  Copyright (c) 2006 Dmitry Torokhov <dtor@mail.ru>
 */

/*
 */

/* #घोषणा DEBUG */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/fixp-arith.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anssi Hannula <anssi.hannula@gmail.com>");
MODULE_DESCRIPTION("Force feedback support for memoryless devices");

/* Number of effects handled with memoryless devices */
#घोषणा FF_MEMLESS_EFFECTS	16

/* Envelope update पूर्णांकerval in ms */
#घोषणा FF_ENVELOPE_INTERVAL	50

#घोषणा FF_EFFECT_STARTED	0
#घोषणा FF_EFFECT_PLAYING	1
#घोषणा FF_EFFECT_ABORTING	2

काष्ठा ml_effect_state अणु
	काष्ठा ff_effect *effect;
	अचिन्हित दीर्घ flags;	/* effect state (STARTED, PLAYING, etc) */
	पूर्णांक count;		/* loop count of the effect */
	अचिन्हित दीर्घ play_at;	/* start समय */
	अचिन्हित दीर्घ stop_at;	/* stop समय */
	अचिन्हित दीर्घ adj_at;	/* last समय the effect was sent */
पूर्ण;

काष्ठा ml_device अणु
	व्योम *निजी;
	काष्ठा ml_effect_state states[FF_MEMLESS_EFFECTS];
	पूर्णांक gain;
	काष्ठा समयr_list समयr;
	काष्ठा input_dev *dev;

	पूर्णांक (*play_effect)(काष्ठा input_dev *dev, व्योम *data,
			   काष्ठा ff_effect *effect);
पूर्ण;

अटल स्थिर काष्ठा ff_envelope *get_envelope(स्थिर काष्ठा ff_effect *effect)
अणु
	अटल स्थिर काष्ठा ff_envelope empty_envelope;

	चयन (effect->type) अणु
	हाल FF_PERIODIC:
		वापस &effect->u.periodic.envelope;

	हाल FF_CONSTANT:
		वापस &effect->u.स्थिरant.envelope;

	शेष:
		वापस &empty_envelope;
	पूर्ण
पूर्ण

/*
 * Check क्रम the next समय envelope requires an update on memoryless devices
 */
अटल अचिन्हित दीर्घ calculate_next_समय(काष्ठा ml_effect_state *state)
अणु
	स्थिर काष्ठा ff_envelope *envelope = get_envelope(state->effect);
	अचिन्हित दीर्घ attack_stop, fade_start, next_fade;

	अगर (envelope->attack_length) अणु
		attack_stop = state->play_at +
			msecs_to_jअगरfies(envelope->attack_length);
		अगर (समय_beक्रमe(state->adj_at, attack_stop))
			वापस state->adj_at +
					msecs_to_jअगरfies(FF_ENVELOPE_INTERVAL);
	पूर्ण

	अगर (state->effect->replay.length) अणु
		अगर (envelope->fade_length) अणु
			/* check when fading should start */
			fade_start = state->stop_at -
					msecs_to_jअगरfies(envelope->fade_length);

			अगर (समय_beक्रमe(state->adj_at, fade_start))
				वापस fade_start;

			/* alपढ़ोy fading, advance to next checkpoपूर्णांक */
			next_fade = state->adj_at +
					msecs_to_jअगरfies(FF_ENVELOPE_INTERVAL);
			अगर (समय_beक्रमe(next_fade, state->stop_at))
				वापस next_fade;
		पूर्ण

		वापस state->stop_at;
	पूर्ण

	वापस state->play_at;
पूर्ण

अटल व्योम ml_schedule_समयr(काष्ठा ml_device *ml)
अणु
	काष्ठा ml_effect_state *state;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ earliest = 0;
	अचिन्हित दीर्घ next_at;
	पूर्णांक events = 0;
	पूर्णांक i;

	pr_debug("calculating next timer\n");

	क्रम (i = 0; i < FF_MEMLESS_EFFECTS; i++) अणु

		state = &ml->states[i];

		अगर (!test_bit(FF_EFFECT_STARTED, &state->flags))
			जारी;

		अगर (test_bit(FF_EFFECT_PLAYING, &state->flags))
			next_at = calculate_next_समय(state);
		अन्यथा
			next_at = state->play_at;

		अगर (समय_beक्रमe_eq(now, next_at) &&
		    (++events == 1 || समय_beक्रमe(next_at, earliest)))
			earliest = next_at;
	पूर्ण

	अगर (!events) अणु
		pr_debug("no actions\n");
		del_समयr(&ml->समयr);
	पूर्ण अन्यथा अणु
		pr_debug("timer set\n");
		mod_समयr(&ml->समयr, earliest);
	पूर्ण
पूर्ण

/*
 * Apply an envelope to a value
 */
अटल पूर्णांक apply_envelope(काष्ठा ml_effect_state *state, पूर्णांक value,
			  काष्ठा ff_envelope *envelope)
अणु
	काष्ठा ff_effect *effect = state->effect;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक समय_from_level;
	पूर्णांक समय_of_envelope;
	पूर्णांक envelope_level;
	पूर्णांक dअगरference;

	अगर (envelope->attack_length &&
	    समय_beक्रमe(now,
			state->play_at + msecs_to_jअगरfies(envelope->attack_length))) अणु
		pr_debug("value = 0x%x, attack_level = 0x%x\n",
			 value, envelope->attack_level);
		समय_from_level = jअगरfies_to_msecs(now - state->play_at);
		समय_of_envelope = envelope->attack_length;
		envelope_level = min_t(u16, envelope->attack_level, 0x7fff);

	पूर्ण अन्यथा अगर (envelope->fade_length && effect->replay.length &&
		   समय_after(now,
			      state->stop_at - msecs_to_jअगरfies(envelope->fade_length)) &&
		   समय_beक्रमe(now, state->stop_at)) अणु
		समय_from_level = jअगरfies_to_msecs(state->stop_at - now);
		समय_of_envelope = envelope->fade_length;
		envelope_level = min_t(u16, envelope->fade_level, 0x7fff);
	पूर्ण अन्यथा
		वापस value;

	dअगरference = असल(value) - envelope_level;

	pr_debug("difference = %d\n", dअगरference);
	pr_debug("time_from_level = 0x%x\n", समय_from_level);
	pr_debug("time_of_envelope = 0x%x\n", समय_of_envelope);

	dअगरference = dअगरference * समय_from_level / समय_of_envelope;

	pr_debug("difference = %d\n", dअगरference);

	वापस value < 0 ?
		-(dअगरference + envelope_level) : (dअगरference + envelope_level);
पूर्ण

/*
 * Return the type the effect has to be converted पूर्णांकo (memless devices)
 */
अटल पूर्णांक get_compatible_type(काष्ठा ff_device *ff, पूर्णांक effect_type)
अणु

	अगर (test_bit(effect_type, ff->ffbit))
		वापस effect_type;

	अगर (effect_type == FF_PERIODIC && test_bit(FF_RUMBLE, ff->ffbit))
		वापस FF_RUMBLE;

	pr_err("invalid type in get_compatible_type()\n");

	वापस 0;
पूर्ण

/*
 * Only left/right direction should be used (under/over 0x8000) क्रम
 * क्रमward/reverse motor direction (to keep calculation fast & simple).
 */
अटल u16 ml_calculate_direction(u16 direction, u16 क्रमce,
				  u16 new_direction, u16 new_क्रमce)
अणु
	अगर (!क्रमce)
		वापस new_direction;
	अगर (!new_क्रमce)
		वापस direction;
	वापस (((u32)(direction >> 1) * क्रमce +
		 (new_direction >> 1) * new_क्रमce) /
		(क्रमce + new_क्रमce)) << 1;
पूर्ण

#घोषणा FRAC_N 8
अटल अंतरभूत s16 fixp_new16(s16 a)
अणु
	वापस ((s32)a) >> (16 - FRAC_N);
पूर्ण

अटल अंतरभूत s16 fixp_mult(s16 a, s16 b)
अणु
	a = ((s32)a * 0x100) / 0x7fff;
	वापस ((s32)(a * b)) >> FRAC_N;
पूर्ण

/*
 * Combine two effects and apply gain.
 */
अटल व्योम ml_combine_effects(काष्ठा ff_effect *effect,
			       काष्ठा ml_effect_state *state,
			       पूर्णांक gain)
अणु
	काष्ठा ff_effect *new = state->effect;
	अचिन्हित पूर्णांक strong, weak, i;
	पूर्णांक x, y;
	s16 level;

	चयन (new->type) अणु
	हाल FF_CONSTANT:
		i = new->direction * 360 / 0xffff;
		level = fixp_new16(apply_envelope(state,
					new->u.स्थिरant.level,
					&new->u.स्थिरant.envelope));
		x = fixp_mult(fixp_sin16(i), level) * gain / 0xffff;
		y = fixp_mult(-fixp_cos16(i), level) * gain / 0xffff;
		/*
		 * here we abuse ff_ramp to hold x and y of स्थिरant क्रमce
		 * If in future any driver wants something अन्यथा than x and y
		 * in s8, this should be changed to something more generic
		 */
		effect->u.ramp.start_level =
			clamp_val(effect->u.ramp.start_level + x, -0x80, 0x7f);
		effect->u.ramp.end_level =
			clamp_val(effect->u.ramp.end_level + y, -0x80, 0x7f);
		अवरोध;

	हाल FF_RUMBLE:
		strong = (u32)new->u.rumble.strong_magnitude * gain / 0xffff;
		weak = (u32)new->u.rumble.weak_magnitude * gain / 0xffff;

		अगर (effect->u.rumble.strong_magnitude + strong)
			effect->direction = ml_calculate_direction(
				effect->direction,
				effect->u.rumble.strong_magnitude,
				new->direction, strong);
		अन्यथा अगर (effect->u.rumble.weak_magnitude + weak)
			effect->direction = ml_calculate_direction(
				effect->direction,
				effect->u.rumble.weak_magnitude,
				new->direction, weak);
		अन्यथा
			effect->direction = 0;
		effect->u.rumble.strong_magnitude =
			min(strong + effect->u.rumble.strong_magnitude,
			    0xffffU);
		effect->u.rumble.weak_magnitude =
			min(weak + effect->u.rumble.weak_magnitude, 0xffffU);
		अवरोध;

	हाल FF_PERIODIC:
		i = apply_envelope(state, असल(new->u.periodic.magnitude),
				   &new->u.periodic.envelope);

		/* here we also scale it 0x7fff => 0xffff */
		i = i * gain / 0x7fff;

		अगर (effect->u.rumble.strong_magnitude + i)
			effect->direction = ml_calculate_direction(
				effect->direction,
				effect->u.rumble.strong_magnitude,
				new->direction, i);
		अन्यथा
			effect->direction = 0;
		effect->u.rumble.strong_magnitude =
			min(i + effect->u.rumble.strong_magnitude, 0xffffU);
		effect->u.rumble.weak_magnitude =
			min(i + effect->u.rumble.weak_magnitude, 0xffffU);
		अवरोध;

	शेष:
		pr_err("invalid type in ml_combine_effects()\n");
		अवरोध;
	पूर्ण

पूर्ण


/*
 * Because memoryless devices have only one effect per effect type active
 * at one समय we have to combine multiple effects पूर्णांकo one
 */
अटल पूर्णांक ml_get_combo_effect(काष्ठा ml_device *ml,
			       अचिन्हित दीर्घ *effect_handled,
			       काष्ठा ff_effect *combo_effect)
अणु
	काष्ठा ff_effect *effect;
	काष्ठा ml_effect_state *state;
	पूर्णांक effect_type;
	पूर्णांक i;

	स_रखो(combo_effect, 0, माप(काष्ठा ff_effect));

	क्रम (i = 0; i < FF_MEMLESS_EFFECTS; i++) अणु
		अगर (__test_and_set_bit(i, effect_handled))
			जारी;

		state = &ml->states[i];
		effect = state->effect;

		अगर (!test_bit(FF_EFFECT_STARTED, &state->flags))
			जारी;

		अगर (समय_beक्रमe(jअगरfies, state->play_at))
			जारी;

		/*
		 * here we have started effects that are either
		 * currently playing (and may need be पातed)
		 * or need to start playing.
		 */
		effect_type = get_compatible_type(ml->dev->ff, effect->type);
		अगर (combo_effect->type != effect_type) अणु
			अगर (combo_effect->type != 0) अणु
				__clear_bit(i, effect_handled);
				जारी;
			पूर्ण
			combo_effect->type = effect_type;
		पूर्ण

		अगर (__test_and_clear_bit(FF_EFFECT_ABORTING, &state->flags)) अणु
			__clear_bit(FF_EFFECT_PLAYING, &state->flags);
			__clear_bit(FF_EFFECT_STARTED, &state->flags);
		पूर्ण अन्यथा अगर (effect->replay.length &&
			   समय_after_eq(jअगरfies, state->stop_at)) अणु

			__clear_bit(FF_EFFECT_PLAYING, &state->flags);

			अगर (--state->count <= 0) अणु
				__clear_bit(FF_EFFECT_STARTED, &state->flags);
			पूर्ण अन्यथा अणु
				state->play_at = jअगरfies +
					msecs_to_jअगरfies(effect->replay.delay);
				state->stop_at = state->play_at +
					msecs_to_jअगरfies(effect->replay.length);
			पूर्ण
		पूर्ण अन्यथा अणु
			__set_bit(FF_EFFECT_PLAYING, &state->flags);
			state->adj_at = jअगरfies;
			ml_combine_effects(combo_effect, state, ml->gain);
		पूर्ण
	पूर्ण

	वापस combo_effect->type != 0;
पूर्ण

अटल व्योम ml_play_effects(काष्ठा ml_device *ml)
अणु
	काष्ठा ff_effect effect;
	DECLARE_BITMAP(handled_bm, FF_MEMLESS_EFFECTS);

	स_रखो(handled_bm, 0, माप(handled_bm));

	जबतक (ml_get_combo_effect(ml, handled_bm, &effect))
		ml->play_effect(ml->dev, ml->निजी, &effect);

	ml_schedule_समयr(ml);
पूर्ण

अटल व्योम ml_effect_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ml_device *ml = from_समयr(ml, t, समयr);
	काष्ठा input_dev *dev = ml->dev;
	अचिन्हित दीर्घ flags;

	pr_debug("timer: updating effects\n");

	spin_lock_irqsave(&dev->event_lock, flags);
	ml_play_effects(ml);
	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

/*
 * Sets requested gain क्रम FF effects. Called with dev->event_lock held.
 */
अटल व्योम ml_ff_set_gain(काष्ठा input_dev *dev, u16 gain)
अणु
	काष्ठा ml_device *ml = dev->ff->निजी;
	पूर्णांक i;

	ml->gain = gain;

	क्रम (i = 0; i < FF_MEMLESS_EFFECTS; i++)
		__clear_bit(FF_EFFECT_PLAYING, &ml->states[i].flags);

	ml_play_effects(ml);
पूर्ण

/*
 * Start/stop specअगरied FF effect. Called with dev->event_lock held.
 */
अटल पूर्णांक ml_ff_playback(काष्ठा input_dev *dev, पूर्णांक effect_id, पूर्णांक value)
अणु
	काष्ठा ml_device *ml = dev->ff->निजी;
	काष्ठा ml_effect_state *state = &ml->states[effect_id];

	अगर (value > 0) अणु
		pr_debug("initiated play\n");

		__set_bit(FF_EFFECT_STARTED, &state->flags);
		state->count = value;
		state->play_at = jअगरfies +
				 msecs_to_jअगरfies(state->effect->replay.delay);
		state->stop_at = state->play_at +
				 msecs_to_jअगरfies(state->effect->replay.length);
		state->adj_at = state->play_at;

	पूर्ण अन्यथा अणु
		pr_debug("initiated stop\n");

		अगर (test_bit(FF_EFFECT_PLAYING, &state->flags))
			__set_bit(FF_EFFECT_ABORTING, &state->flags);
		अन्यथा
			__clear_bit(FF_EFFECT_STARTED, &state->flags);
	पूर्ण

	ml_play_effects(ml);

	वापस 0;
पूर्ण

अटल पूर्णांक ml_ff_upload(काष्ठा input_dev *dev,
			काष्ठा ff_effect *effect, काष्ठा ff_effect *old)
अणु
	काष्ठा ml_device *ml = dev->ff->निजी;
	काष्ठा ml_effect_state *state = &ml->states[effect->id];

	spin_lock_irq(&dev->event_lock);

	अगर (test_bit(FF_EFFECT_STARTED, &state->flags)) अणु
		__clear_bit(FF_EFFECT_PLAYING, &state->flags);
		state->play_at = jअगरfies +
				 msecs_to_jअगरfies(state->effect->replay.delay);
		state->stop_at = state->play_at +
				 msecs_to_jअगरfies(state->effect->replay.length);
		state->adj_at = state->play_at;
		ml_schedule_समयr(ml);
	पूर्ण

	spin_unlock_irq(&dev->event_lock);

	वापस 0;
पूर्ण

अटल व्योम ml_ff_destroy(काष्ठा ff_device *ff)
अणु
	काष्ठा ml_device *ml = ff->निजी;

	/*
	 * Even though we stop all playing effects when tearing करोwn
	 * an input device (via input_device_flush() that calls पूर्णांकo
	 * input_ff_flush() that stops and erases all effects), we
	 * करो not actually stop the समयr, and thereक्रमe we should
	 * करो it here.
	 */
	del_समयr_sync(&ml->समयr);

	kमुक्त(ml->निजी);
पूर्ण

/**
 * input_ff_create_memless() - create memoryless क्रमce-feedback device
 * @dev: input device supporting क्रमce-feedback
 * @data: driver-specअगरic data to be passed पूर्णांकo @play_effect
 * @play_effect: driver-specअगरic method क्रम playing FF effect
 */
पूर्णांक input_ff_create_memless(काष्ठा input_dev *dev, व्योम *data,
		पूर्णांक (*play_effect)(काष्ठा input_dev *, व्योम *, काष्ठा ff_effect *))
अणु
	काष्ठा ml_device *ml;
	काष्ठा ff_device *ff;
	पूर्णांक error;
	पूर्णांक i;

	ml = kzalloc(माप(काष्ठा ml_device), GFP_KERNEL);
	अगर (!ml)
		वापस -ENOMEM;

	ml->dev = dev;
	ml->निजी = data;
	ml->play_effect = play_effect;
	ml->gain = 0xffff;
	समयr_setup(&ml->समयr, ml_effect_समयr, 0);

	set_bit(FF_GAIN, dev->ffbit);

	error = input_ff_create(dev, FF_MEMLESS_EFFECTS);
	अगर (error) अणु
		kमुक्त(ml);
		वापस error;
	पूर्ण

	ff = dev->ff;
	ff->निजी = ml;
	ff->upload = ml_ff_upload;
	ff->playback = ml_ff_playback;
	ff->set_gain = ml_ff_set_gain;
	ff->destroy = ml_ff_destroy;

	/* we can emulate periodic effects with RUMBLE */
	अगर (test_bit(FF_RUMBLE, ff->ffbit)) अणु
		set_bit(FF_PERIODIC, dev->ffbit);
		set_bit(FF_SINE, dev->ffbit);
		set_bit(FF_TRIANGLE, dev->ffbit);
		set_bit(FF_SQUARE, dev->ffbit);
	पूर्ण

	क्रम (i = 0; i < FF_MEMLESS_EFFECTS; i++)
		ml->states[i].effect = &ff->effects[i];

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(input_ff_create_memless);
