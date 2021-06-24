<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2002 Vojtech Pavlik <vojtech@ucw.cz>
 *  Copyright (c) 2001-2002, 2007 Johann Deneux <johann.deneux@gmail.com>
 *
 *  USB/RS232 I-Force joysticks and wheels.
 */

#समावेश "iforce.h"

/*
 * Set the magnitude of a स्थिरant क्रमce effect
 * Return error code
 *
 * Note: caller must ensure exclusive access to device
 */

अटल पूर्णांक make_magnitude_modअगरier(काष्ठा अगरorce* अगरorce,
	काष्ठा resource* mod_chunk, पूर्णांक no_alloc, __s16 level)
अणु
	अचिन्हित अक्षर data[3];

	अगर (!no_alloc) अणु
		mutex_lock(&अगरorce->mem_mutex);
		अगर (allocate_resource(&(अगरorce->device_memory), mod_chunk, 2,
			अगरorce->device_memory.start, अगरorce->device_memory.end, 2L,
			शून्य, शून्य)) अणु
			mutex_unlock(&अगरorce->mem_mutex);
			वापस -ENOSPC;
		पूर्ण
		mutex_unlock(&अगरorce->mem_mutex);
	पूर्ण

	data[0] = LO(mod_chunk->start);
	data[1] = HI(mod_chunk->start);
	data[2] = HIFIX80(level);

	अगरorce_send_packet(अगरorce, FF_CMD_MAGNITUDE, data);

	अगरorce_dump_packet(अगरorce, "magnitude", FF_CMD_MAGNITUDE, data);
	वापस 0;
पूर्ण

/*
 * Upload the component of an effect dealing with the period, phase and magnitude
 */

अटल पूर्णांक make_period_modअगरier(काष्ठा अगरorce* अगरorce,
	काष्ठा resource* mod_chunk, पूर्णांक no_alloc,
	__s16 magnitude, __s16 offset, u16 period, u16 phase)
अणु
	अचिन्हित अक्षर data[7];

	period = TIME_SCALE(period);

	अगर (!no_alloc) अणु
		mutex_lock(&अगरorce->mem_mutex);
		अगर (allocate_resource(&(अगरorce->device_memory), mod_chunk, 0x0c,
			अगरorce->device_memory.start, अगरorce->device_memory.end, 2L,
			शून्य, शून्य)) अणु
			mutex_unlock(&अगरorce->mem_mutex);
			वापस -ENOSPC;
		पूर्ण
		mutex_unlock(&अगरorce->mem_mutex);
	पूर्ण

	data[0] = LO(mod_chunk->start);
	data[1] = HI(mod_chunk->start);

	data[2] = HIFIX80(magnitude);
	data[3] = HIFIX80(offset);
	data[4] = HI(phase);

	data[5] = LO(period);
	data[6] = HI(period);

	अगरorce_send_packet(अगरorce, FF_CMD_PERIOD, data);

	वापस 0;
पूर्ण

/*
 * Uploads the part of an effect setting the envelope of the क्रमce
 */

अटल पूर्णांक make_envelope_modअगरier(काष्ठा अगरorce* अगरorce,
	काष्ठा resource* mod_chunk, पूर्णांक no_alloc,
	u16 attack_duration, __s16 initial_level,
	u16 fade_duration, __s16 final_level)
अणु
	अचिन्हित अक्षर data[8];

	attack_duration = TIME_SCALE(attack_duration);
	fade_duration = TIME_SCALE(fade_duration);

	अगर (!no_alloc) अणु
		mutex_lock(&अगरorce->mem_mutex);
		अगर (allocate_resource(&(अगरorce->device_memory), mod_chunk, 0x0e,
			अगरorce->device_memory.start, अगरorce->device_memory.end, 2L,
			शून्य, शून्य)) अणु
			mutex_unlock(&अगरorce->mem_mutex);
			वापस -ENOSPC;
		पूर्ण
		mutex_unlock(&अगरorce->mem_mutex);
	पूर्ण

	data[0] = LO(mod_chunk->start);
	data[1] = HI(mod_chunk->start);

	data[2] = LO(attack_duration);
	data[3] = HI(attack_duration);
	data[4] = HI(initial_level);

	data[5] = LO(fade_duration);
	data[6] = HI(fade_duration);
	data[7] = HI(final_level);

	अगरorce_send_packet(अगरorce, FF_CMD_ENVELOPE, data);

	वापस 0;
पूर्ण

/*
 * Component of spring, friction, inertia... effects
 */

अटल पूर्णांक make_condition_modअगरier(काष्ठा अगरorce* अगरorce,
	काष्ठा resource* mod_chunk, पूर्णांक no_alloc,
	__u16 rsat, __u16 lsat, __s16 rk, __s16 lk, u16 db, __s16 center)
अणु
	अचिन्हित अक्षर data[10];

	अगर (!no_alloc) अणु
		mutex_lock(&अगरorce->mem_mutex);
		अगर (allocate_resource(&(अगरorce->device_memory), mod_chunk, 8,
			अगरorce->device_memory.start, अगरorce->device_memory.end, 2L,
			शून्य, शून्य)) अणु
			mutex_unlock(&अगरorce->mem_mutex);
			वापस -ENOSPC;
		पूर्ण
		mutex_unlock(&अगरorce->mem_mutex);
	पूर्ण

	data[0] = LO(mod_chunk->start);
	data[1] = HI(mod_chunk->start);

	data[2] = (100 * rk) >> 15;	/* Dangerous: the sign is extended by gcc on plateक्रमms providing an arith shअगरt */
	data[3] = (100 * lk) >> 15; /* This code is incorrect on cpus lacking arith shअगरt */

	center = (500 * center) >> 15;
	data[4] = LO(center);
	data[5] = HI(center);

	db = (1000 * db) >> 16;
	data[6] = LO(db);
	data[7] = HI(db);

	data[8] = (100 * rsat) >> 16;
	data[9] = (100 * lsat) >> 16;

	अगरorce_send_packet(अगरorce, FF_CMD_CONDITION, data);
	अगरorce_dump_packet(अगरorce, "condition", FF_CMD_CONDITION, data);

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर find_button(काष्ठा अगरorce *अगरorce, चिन्हित लघु button)
अणु
	पूर्णांक i;

	क्रम (i = 1; अगरorce->type->btn[i] >= 0; i++)
		अगर (अगरorce->type->btn[i] == button)
			वापस i + 1;
	वापस 0;
पूर्ण

/*
 * Analyse the changes in an effect, and tell अगर we need to send an condition
 * parameter packet
 */
अटल पूर्णांक need_condition_modअगरier(काष्ठा अगरorce *अगरorce,
				   काष्ठा ff_effect *old,
				   काष्ठा ff_effect *new)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (new->type != FF_SPRING && new->type != FF_FRICTION) अणु
		dev_warn(&अगरorce->dev->dev, "bad effect type in %s\n",
			 __func__);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		ret |= old->u.condition[i].right_saturation != new->u.condition[i].right_saturation
			|| old->u.condition[i].left_saturation != new->u.condition[i].left_saturation
			|| old->u.condition[i].right_coeff != new->u.condition[i].right_coeff
			|| old->u.condition[i].left_coeff != new->u.condition[i].left_coeff
			|| old->u.condition[i].deadband != new->u.condition[i].deadband
			|| old->u.condition[i].center != new->u.condition[i].center;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Analyse the changes in an effect, and tell अगर we need to send a magnitude
 * parameter packet
 */
अटल पूर्णांक need_magnitude_modअगरier(काष्ठा अगरorce *अगरorce,
				   काष्ठा ff_effect *old,
				   काष्ठा ff_effect *effect)
अणु
	अगर (effect->type != FF_CONSTANT) अणु
		dev_warn(&अगरorce->dev->dev, "bad effect type in %s\n",
			 __func__);
		वापस 0;
	पूर्ण

	वापस old->u.स्थिरant.level != effect->u.स्थिरant.level;
पूर्ण

/*
 * Analyse the changes in an effect, and tell अगर we need to send an envelope
 * parameter packet
 */
अटल पूर्णांक need_envelope_modअगरier(काष्ठा अगरorce *अगरorce, काष्ठा ff_effect *old,
				  काष्ठा ff_effect *effect)
अणु
	चयन (effect->type) अणु
	हाल FF_CONSTANT:
		अगर (old->u.स्थिरant.envelope.attack_length != effect->u.स्थिरant.envelope.attack_length
		|| old->u.स्थिरant.envelope.attack_level != effect->u.स्थिरant.envelope.attack_level
		|| old->u.स्थिरant.envelope.fade_length != effect->u.स्थिरant.envelope.fade_length
		|| old->u.स्थिरant.envelope.fade_level != effect->u.स्थिरant.envelope.fade_level)
			वापस 1;
		अवरोध;

	हाल FF_PERIODIC:
		अगर (old->u.periodic.envelope.attack_length != effect->u.periodic.envelope.attack_length
		|| old->u.periodic.envelope.attack_level != effect->u.periodic.envelope.attack_level
		|| old->u.periodic.envelope.fade_length != effect->u.periodic.envelope.fade_length
		|| old->u.periodic.envelope.fade_level != effect->u.periodic.envelope.fade_level)
			वापस 1;
		अवरोध;

	शेष:
		dev_warn(&अगरorce->dev->dev, "bad effect type in %s\n",
			 __func__);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Analyse the changes in an effect, and tell अगर we need to send a periodic
 * parameter effect
 */
अटल पूर्णांक need_period_modअगरier(काष्ठा अगरorce *अगरorce, काष्ठा ff_effect *old,
				काष्ठा ff_effect *new)
अणु
	अगर (new->type != FF_PERIODIC) अणु
		dev_warn(&अगरorce->dev->dev, "bad effect type in %s\n",
			 __func__);
		वापस 0;
	पूर्ण
	वापस (old->u.periodic.period != new->u.periodic.period
		|| old->u.periodic.magnitude != new->u.periodic.magnitude
		|| old->u.periodic.offset != new->u.periodic.offset
		|| old->u.periodic.phase != new->u.periodic.phase);
पूर्ण

/*
 * Analyse the changes in an effect, and tell अगर we need to send an effect
 * packet
 */
अटल पूर्णांक need_core(काष्ठा ff_effect *old, काष्ठा ff_effect *new)
अणु
	अगर (old->direction != new->direction
		|| old->trigger.button != new->trigger.button
		|| old->trigger.पूर्णांकerval != new->trigger.पूर्णांकerval
		|| old->replay.length != new->replay.length
		|| old->replay.delay != new->replay.delay)
		वापस 1;

	वापस 0;
पूर्ण
/*
 * Send the part common to all effects to the device
 */
अटल पूर्णांक make_core(काष्ठा अगरorce* अगरorce, u16 id, u16 mod_id1, u16 mod_id2,
	u8 effect_type, u8 axes, u16 duration, u16 delay, u16 button,
	u16 पूर्णांकerval, u16 direction)
अणु
	अचिन्हित अक्षर data[14];

	duration = TIME_SCALE(duration);
	delay    = TIME_SCALE(delay);
	पूर्णांकerval = TIME_SCALE(पूर्णांकerval);

	data[0]  = LO(id);
	data[1]  = effect_type;
	data[2]  = LO(axes) | find_button(अगरorce, button);

	data[3]  = LO(duration);
	data[4]  = HI(duration);

	data[5]  = HI(direction);

	data[6]  = LO(पूर्णांकerval);
	data[7]  = HI(पूर्णांकerval);

	data[8]  = LO(mod_id1);
	data[9]  = HI(mod_id1);
	data[10] = LO(mod_id2);
	data[11] = HI(mod_id2);

	data[12] = LO(delay);
	data[13] = HI(delay);

	/* Stop effect */
/*	अगरorce_control_playback(अगरorce, id, 0);*/

	अगरorce_send_packet(अगरorce, FF_CMD_EFFECT, data);

	/* If needed, restart effect */
	अगर (test_bit(FF_CORE_SHOULD_PLAY, अगरorce->core_effects[id].flags)) अणु
		/* BUG: perhaps we should replay n बार, instead of 1. But we करो not know n */
		अगरorce_control_playback(अगरorce, id, 1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Upload a periodic effect to the device
 * See also अगरorce_upload_स्थिरant.
 */
पूर्णांक अगरorce_upload_periodic(काष्ठा अगरorce *अगरorce, काष्ठा ff_effect *effect, काष्ठा ff_effect *old)
अणु
	u8 wave_code;
	पूर्णांक core_id = effect->id;
	काष्ठा अगरorce_core_effect* core_effect = अगरorce->core_effects + core_id;
	काष्ठा resource* mod1_chunk = &(अगरorce->core_effects[core_id].mod1_chunk);
	काष्ठा resource* mod2_chunk = &(अगरorce->core_effects[core_id].mod2_chunk);
	पूर्णांक param1_err = 1;
	पूर्णांक param2_err = 1;
	पूर्णांक core_err = 0;

	अगर (!old || need_period_modअगरier(अगरorce, old, effect)) अणु
		param1_err = make_period_modअगरier(अगरorce, mod1_chunk,
			old != शून्य,
			effect->u.periodic.magnitude, effect->u.periodic.offset,
			effect->u.periodic.period, effect->u.periodic.phase);
		अगर (param1_err)
			वापस param1_err;
		set_bit(FF_MOD1_IS_USED, core_effect->flags);
	पूर्ण

	अगर (!old || need_envelope_modअगरier(अगरorce, old, effect)) अणु
		param2_err = make_envelope_modअगरier(अगरorce, mod2_chunk,
			old !=शून्य,
			effect->u.periodic.envelope.attack_length,
			effect->u.periodic.envelope.attack_level,
			effect->u.periodic.envelope.fade_length,
			effect->u.periodic.envelope.fade_level);
		अगर (param2_err)
			वापस param2_err;
		set_bit(FF_MOD2_IS_USED, core_effect->flags);
	पूर्ण

	चयन (effect->u.periodic.waveक्रमm) अणु
	हाल FF_SQUARE:		wave_code = 0x20; अवरोध;
	हाल FF_TRIANGLE:	wave_code = 0x21; अवरोध;
	हाल FF_SINE:		wave_code = 0x22; अवरोध;
	हाल FF_SAW_UP:		wave_code = 0x23; अवरोध;
	हाल FF_SAW_DOWN:	wave_code = 0x24; अवरोध;
	शेष:		wave_code = 0x20; अवरोध;
	पूर्ण

	अगर (!old || need_core(old, effect)) अणु
		core_err = make_core(अगरorce, effect->id,
			mod1_chunk->start,
			mod2_chunk->start,
			wave_code,
			0x20,
			effect->replay.length,
			effect->replay.delay,
			effect->trigger.button,
			effect->trigger.पूर्णांकerval,
			effect->direction);
	पूर्ण

	/* If one of the parameter creation failed, we alपढ़ोy वापसed an
	 * error code.
	 * If the core creation failed, we वापस its error code.
	 * Else: अगर one parameter at least was created, we वापस 0
	 *       अन्यथा we वापस 1;
	 */
	वापस core_err < 0 ? core_err : (param1_err && param2_err);
पूर्ण

/*
 * Upload a स्थिरant क्रमce effect
 * Return value:
 *  <0 Error code
 *  0 Ok, effect created or updated
 *  1 effect did not change since last upload, and no packet was thereक्रमe sent
 */
पूर्णांक अगरorce_upload_स्थिरant(काष्ठा अगरorce *अगरorce, काष्ठा ff_effect *effect, काष्ठा ff_effect *old)
अणु
	पूर्णांक core_id = effect->id;
	काष्ठा अगरorce_core_effect* core_effect = अगरorce->core_effects + core_id;
	काष्ठा resource* mod1_chunk = &(अगरorce->core_effects[core_id].mod1_chunk);
	काष्ठा resource* mod2_chunk = &(अगरorce->core_effects[core_id].mod2_chunk);
	पूर्णांक param1_err = 1;
	पूर्णांक param2_err = 1;
	पूर्णांक core_err = 0;

	अगर (!old || need_magnitude_modअगरier(अगरorce, old, effect)) अणु
		param1_err = make_magnitude_modअगरier(अगरorce, mod1_chunk,
			old != शून्य,
			effect->u.स्थिरant.level);
		अगर (param1_err)
			वापस param1_err;
		set_bit(FF_MOD1_IS_USED, core_effect->flags);
	पूर्ण

	अगर (!old || need_envelope_modअगरier(अगरorce, old, effect)) अणु
		param2_err = make_envelope_modअगरier(अगरorce, mod2_chunk,
			old != शून्य,
			effect->u.स्थिरant.envelope.attack_length,
			effect->u.स्थिरant.envelope.attack_level,
			effect->u.स्थिरant.envelope.fade_length,
			effect->u.स्थिरant.envelope.fade_level);
		अगर (param2_err)
			वापस param2_err;
		set_bit(FF_MOD2_IS_USED, core_effect->flags);
	पूर्ण

	अगर (!old || need_core(old, effect)) अणु
		core_err = make_core(अगरorce, effect->id,
			mod1_chunk->start,
			mod2_chunk->start,
			0x00,
			0x20,
			effect->replay.length,
			effect->replay.delay,
			effect->trigger.button,
			effect->trigger.पूर्णांकerval,
			effect->direction);
	पूर्ण

	/* If one of the parameter creation failed, we alपढ़ोy वापसed an
	 * error code.
	 * If the core creation failed, we वापस its error code.
	 * Else: अगर one parameter at least was created, we वापस 0
	 *       अन्यथा we वापस 1;
	 */
	वापस core_err < 0 ? core_err : (param1_err && param2_err);
पूर्ण

/*
 * Upload an condition effect. Those are क्रम example friction, inertia, springs...
 */
पूर्णांक अगरorce_upload_condition(काष्ठा अगरorce *अगरorce, काष्ठा ff_effect *effect, काष्ठा ff_effect *old)
अणु
	पूर्णांक core_id = effect->id;
	काष्ठा अगरorce_core_effect* core_effect = अगरorce->core_effects + core_id;
	काष्ठा resource* mod1_chunk = &(core_effect->mod1_chunk);
	काष्ठा resource* mod2_chunk = &(core_effect->mod2_chunk);
	u8 type;
	पूर्णांक param_err = 1;
	पूर्णांक core_err = 0;

	चयन (effect->type) अणु
	हाल FF_SPRING:	type = 0x40; अवरोध;
	हाल FF_DAMPER:	type = 0x41; अवरोध;
	शेष: वापस -1;
	पूर्ण

	अगर (!old || need_condition_modअगरier(अगरorce, old, effect)) अणु
		param_err = make_condition_modअगरier(अगरorce, mod1_chunk,
			old != शून्य,
			effect->u.condition[0].right_saturation,
			effect->u.condition[0].left_saturation,
			effect->u.condition[0].right_coeff,
			effect->u.condition[0].left_coeff,
			effect->u.condition[0].deadband,
			effect->u.condition[0].center);
		अगर (param_err)
			वापस param_err;
		set_bit(FF_MOD1_IS_USED, core_effect->flags);

		param_err = make_condition_modअगरier(अगरorce, mod2_chunk,
			old != शून्य,
			effect->u.condition[1].right_saturation,
			effect->u.condition[1].left_saturation,
			effect->u.condition[1].right_coeff,
			effect->u.condition[1].left_coeff,
			effect->u.condition[1].deadband,
			effect->u.condition[1].center);
		अगर (param_err)
			वापस param_err;
		set_bit(FF_MOD2_IS_USED, core_effect->flags);

	पूर्ण

	अगर (!old || need_core(old, effect)) अणु
		core_err = make_core(अगरorce, effect->id,
			mod1_chunk->start, mod2_chunk->start,
			type, 0xc0,
			effect->replay.length, effect->replay.delay,
			effect->trigger.button, effect->trigger.पूर्णांकerval,
			effect->direction);
	पूर्ण

	/* If the parameter creation failed, we alपढ़ोy वापसed an
	 * error code.
	 * If the core creation failed, we वापस its error code.
	 * Else: अगर a parameter  was created, we वापस 0
	 *       अन्यथा we वापस 1;
	 */
	वापस core_err < 0 ? core_err : param_err;
पूर्ण
