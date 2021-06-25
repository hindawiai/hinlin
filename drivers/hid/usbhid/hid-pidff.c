<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback driver क्रम USB HID PID compliant devices
 *
 *  Copyright (c) 2005, 2006 Anssi Hannula <anssi.hannula@gmail.com>
 */

/*
 */

/* #घोषणा DEBUG */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <linux/hid.h>

#समावेश "usbhid.h"

#घोषणा	PID_EFFECTS_MAX		64

/* Report usage table used to put reports पूर्णांकo an array */

#घोषणा PID_SET_EFFECT		0
#घोषणा PID_EFFECT_OPERATION	1
#घोषणा PID_DEVICE_GAIN		2
#घोषणा PID_POOL		3
#घोषणा PID_BLOCK_LOAD		4
#घोषणा PID_BLOCK_FREE		5
#घोषणा PID_DEVICE_CONTROL	6
#घोषणा PID_CREATE_NEW_EFFECT	7

#घोषणा PID_REQUIRED_REPORTS	7

#घोषणा PID_SET_ENVELOPE	8
#घोषणा PID_SET_CONDITION	9
#घोषणा PID_SET_PERIODIC	10
#घोषणा PID_SET_CONSTANT	11
#घोषणा PID_SET_RAMP		12
अटल स्थिर u8 pidff_reports[] = अणु
	0x21, 0x77, 0x7d, 0x7f, 0x89, 0x90, 0x96, 0xab,
	0x5a, 0x5f, 0x6e, 0x73, 0x74
पूर्ण;

/* device_control is really 0x95, but 0x96 specअगरied as it is the usage of
the only field in that report */

/* Value usage tables used to put fields and values पूर्णांकo arrays */

#घोषणा PID_EFFECT_BLOCK_INDEX	0

#घोषणा PID_DURATION		1
#घोषणा PID_GAIN		2
#घोषणा PID_TRIGGER_BUTTON	3
#घोषणा PID_TRIGGER_REPEAT_INT	4
#घोषणा PID_सूचीECTION_ENABLE	5
#घोषणा PID_START_DELAY		6
अटल स्थिर u8 pidff_set_effect[] = अणु
	0x22, 0x50, 0x52, 0x53, 0x54, 0x56, 0xa7
पूर्ण;

#घोषणा PID_ATTACK_LEVEL	1
#घोषणा PID_ATTACK_TIME		2
#घोषणा PID_FADE_LEVEL		3
#घोषणा PID_FADE_TIME		4
अटल स्थिर u8 pidff_set_envelope[] = अणु 0x22, 0x5b, 0x5c, 0x5d, 0x5e पूर्ण;

#घोषणा PID_PARAM_BLOCK_OFFSET	1
#घोषणा PID_CP_OFFSET		2
#घोषणा PID_POS_COEFFICIENT	3
#घोषणा PID_NEG_COEFFICIENT	4
#घोषणा PID_POS_SATURATION	5
#घोषणा PID_NEG_SATURATION	6
#घोषणा PID_DEAD_BAND		7
अटल स्थिर u8 pidff_set_condition[] = अणु
	0x22, 0x23, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65
पूर्ण;

#घोषणा PID_MAGNITUDE		1
#घोषणा PID_OFFSET		2
#घोषणा PID_PHASE		3
#घोषणा PID_PERIOD		4
अटल स्थिर u8 pidff_set_periodic[] = अणु 0x22, 0x70, 0x6f, 0x71, 0x72 पूर्ण;
अटल स्थिर u8 pidff_set_स्थिरant[] = अणु 0x22, 0x70 पूर्ण;

#घोषणा PID_RAMP_START		1
#घोषणा PID_RAMP_END		2
अटल स्थिर u8 pidff_set_ramp[] = अणु 0x22, 0x75, 0x76 पूर्ण;

#घोषणा PID_RAM_POOL_AVAILABLE	1
अटल स्थिर u8 pidff_block_load[] = अणु 0x22, 0xac पूर्ण;

#घोषणा PID_LOOP_COUNT		1
अटल स्थिर u8 pidff_effect_operation[] = अणु 0x22, 0x7c पूर्ण;

अटल स्थिर u8 pidff_block_मुक्त[] = अणु 0x22 पूर्ण;

#घोषणा PID_DEVICE_GAIN_FIELD	0
अटल स्थिर u8 pidff_device_gain[] = अणु 0x7e पूर्ण;

#घोषणा PID_RAM_POOL_SIZE	0
#घोषणा PID_SIMULTANEOUS_MAX	1
#घोषणा PID_DEVICE_MANAGED_POOL	2
अटल स्थिर u8 pidff_pool[] = अणु 0x80, 0x83, 0xa9 पूर्ण;

/* Special field key tables used to put special field keys पूर्णांकo arrays */

#घोषणा PID_ENABLE_ACTUATORS	0
#घोषणा PID_RESET		1
अटल स्थिर u8 pidff_device_control[] = अणु 0x97, 0x9a पूर्ण;

#घोषणा PID_CONSTANT	0
#घोषणा PID_RAMP	1
#घोषणा PID_SQUARE	2
#घोषणा PID_SINE	3
#घोषणा PID_TRIANGLE	4
#घोषणा PID_SAW_UP	5
#घोषणा PID_SAW_DOWN	6
#घोषणा PID_SPRING	7
#घोषणा PID_DAMPER	8
#घोषणा PID_INERTIA	9
#घोषणा PID_FRICTION	10
अटल स्थिर u8 pidff_effect_types[] = अणु
	0x26, 0x27, 0x30, 0x31, 0x32, 0x33, 0x34,
	0x40, 0x41, 0x42, 0x43
पूर्ण;

#घोषणा PID_BLOCK_LOAD_SUCCESS	0
#घोषणा PID_BLOCK_LOAD_FULL	1
अटल स्थिर u8 pidff_block_load_status[] = अणु 0x8c, 0x8d पूर्ण;

#घोषणा PID_EFFECT_START	0
#घोषणा PID_EFFECT_STOP		1
अटल स्थिर u8 pidff_effect_operation_status[] = अणु 0x79, 0x7b पूर्ण;

काष्ठा pidff_usage अणु
	काष्ठा hid_field *field;
	s32 *value;
पूर्ण;

काष्ठा pidff_device अणु
	काष्ठा hid_device *hid;

	काष्ठा hid_report *reports[माप(pidff_reports)];

	काष्ठा pidff_usage set_effect[माप(pidff_set_effect)];
	काष्ठा pidff_usage set_envelope[माप(pidff_set_envelope)];
	काष्ठा pidff_usage set_condition[माप(pidff_set_condition)];
	काष्ठा pidff_usage set_periodic[माप(pidff_set_periodic)];
	काष्ठा pidff_usage set_स्थिरant[माप(pidff_set_स्थिरant)];
	काष्ठा pidff_usage set_ramp[माप(pidff_set_ramp)];

	काष्ठा pidff_usage device_gain[माप(pidff_device_gain)];
	काष्ठा pidff_usage block_load[माप(pidff_block_load)];
	काष्ठा pidff_usage pool[माप(pidff_pool)];
	काष्ठा pidff_usage effect_operation[माप(pidff_effect_operation)];
	काष्ठा pidff_usage block_मुक्त[माप(pidff_block_मुक्त)];

	/* Special field is a field that is not composed of
	   usage<->value pairs that pidff_usage values are */

	/* Special field in create_new_effect */
	काष्ठा hid_field *create_new_effect_type;

	/* Special fields in set_effect */
	काष्ठा hid_field *set_effect_type;
	काष्ठा hid_field *effect_direction;

	/* Special field in device_control */
	काष्ठा hid_field *device_control;

	/* Special field in block_load */
	काष्ठा hid_field *block_load_status;

	/* Special field in effect_operation */
	काष्ठा hid_field *effect_operation_status;

	पूर्णांक control_id[माप(pidff_device_control)];
	पूर्णांक type_id[माप(pidff_effect_types)];
	पूर्णांक status_id[माप(pidff_block_load_status)];
	पूर्णांक operation_id[माप(pidff_effect_operation_status)];

	पूर्णांक pid_id[PID_EFFECTS_MAX];
पूर्ण;

/*
 * Scale an अचिन्हित value with range 0..max क्रम the given field
 */
अटल पूर्णांक pidff_rescale(पूर्णांक i, पूर्णांक max, काष्ठा hid_field *field)
अणु
	वापस i * (field->logical_maximum - field->logical_minimum) / max +
	    field->logical_minimum;
पूर्ण

/*
 * Scale a चिन्हित value in range -0x8000..0x7fff क्रम the given field
 */
अटल पूर्णांक pidff_rescale_चिन्हित(पूर्णांक i, काष्ठा hid_field *field)
अणु
	वापस i == 0 ? 0 : i >
	    0 ? i * field->logical_maximum / 0x7fff : i *
	    field->logical_minimum / -0x8000;
पूर्ण

अटल व्योम pidff_set(काष्ठा pidff_usage *usage, u16 value)
अणु
	usage->value[0] = pidff_rescale(value, 0xffff, usage->field);
	pr_debug("calculated from %d to %d\n", value, usage->value[0]);
पूर्ण

अटल व्योम pidff_set_चिन्हित(काष्ठा pidff_usage *usage, s16 value)
अणु
	अगर (usage->field->logical_minimum < 0)
		usage->value[0] = pidff_rescale_चिन्हित(value, usage->field);
	अन्यथा अणु
		अगर (value < 0)
			usage->value[0] =
			    pidff_rescale(-value, 0x8000, usage->field);
		अन्यथा
			usage->value[0] =
			    pidff_rescale(value, 0x7fff, usage->field);
	पूर्ण
	pr_debug("calculated from %d to %d\n", value, usage->value[0]);
पूर्ण

/*
 * Send envelope report to the device
 */
अटल व्योम pidff_set_envelope_report(काष्ठा pidff_device *pidff,
				      काष्ठा ff_envelope *envelope)
अणु
	pidff->set_envelope[PID_EFFECT_BLOCK_INDEX].value[0] =
	    pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];

	pidff->set_envelope[PID_ATTACK_LEVEL].value[0] =
	    pidff_rescale(envelope->attack_level >
			  0x7fff ? 0x7fff : envelope->attack_level, 0x7fff,
			  pidff->set_envelope[PID_ATTACK_LEVEL].field);
	pidff->set_envelope[PID_FADE_LEVEL].value[0] =
	    pidff_rescale(envelope->fade_level >
			  0x7fff ? 0x7fff : envelope->fade_level, 0x7fff,
			  pidff->set_envelope[PID_FADE_LEVEL].field);

	pidff->set_envelope[PID_ATTACK_TIME].value[0] = envelope->attack_length;
	pidff->set_envelope[PID_FADE_TIME].value[0] = envelope->fade_length;

	hid_dbg(pidff->hid, "attack %u => %d\n",
		envelope->attack_level,
		pidff->set_envelope[PID_ATTACK_LEVEL].value[0]);

	hid_hw_request(pidff->hid, pidff->reports[PID_SET_ENVELOPE],
			HID_REQ_SET_REPORT);
पूर्ण

/*
 * Test अगर the new envelope dअगरfers from old one
 */
अटल पूर्णांक pidff_needs_set_envelope(काष्ठा ff_envelope *envelope,
				    काष्ठा ff_envelope *old)
अणु
	वापस envelope->attack_level != old->attack_level ||
	       envelope->fade_level != old->fade_level ||
	       envelope->attack_length != old->attack_length ||
	       envelope->fade_length != old->fade_length;
पूर्ण

/*
 * Send स्थिरant क्रमce report to the device
 */
अटल व्योम pidff_set_स्थिरant_क्रमce_report(काष्ठा pidff_device *pidff,
					    काष्ठा ff_effect *effect)
अणु
	pidff->set_स्थिरant[PID_EFFECT_BLOCK_INDEX].value[0] =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];
	pidff_set_चिन्हित(&pidff->set_स्थिरant[PID_MAGNITUDE],
			 effect->u.स्थिरant.level);

	hid_hw_request(pidff->hid, pidff->reports[PID_SET_CONSTANT],
			HID_REQ_SET_REPORT);
पूर्ण

/*
 * Test अगर the स्थिरant parameters have changed between effects
 */
अटल पूर्णांक pidff_needs_set_स्थिरant(काष्ठा ff_effect *effect,
				    काष्ठा ff_effect *old)
अणु
	वापस effect->u.स्थिरant.level != old->u.स्थिरant.level;
पूर्ण

/*
 * Send set effect report to the device
 */
अटल व्योम pidff_set_effect_report(काष्ठा pidff_device *pidff,
				    काष्ठा ff_effect *effect)
अणु
	pidff->set_effect[PID_EFFECT_BLOCK_INDEX].value[0] =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];
	pidff->set_effect_type->value[0] =
		pidff->create_new_effect_type->value[0];
	pidff->set_effect[PID_DURATION].value[0] = effect->replay.length;
	pidff->set_effect[PID_TRIGGER_BUTTON].value[0] = effect->trigger.button;
	pidff->set_effect[PID_TRIGGER_REPEAT_INT].value[0] =
		effect->trigger.पूर्णांकerval;
	pidff->set_effect[PID_GAIN].value[0] =
		pidff->set_effect[PID_GAIN].field->logical_maximum;
	pidff->set_effect[PID_सूचीECTION_ENABLE].value[0] = 1;
	pidff->effect_direction->value[0] =
		pidff_rescale(effect->direction, 0xffff,
				pidff->effect_direction);
	pidff->set_effect[PID_START_DELAY].value[0] = effect->replay.delay;

	hid_hw_request(pidff->hid, pidff->reports[PID_SET_EFFECT],
			HID_REQ_SET_REPORT);
पूर्ण

/*
 * Test अगर the values used in set_effect have changed
 */
अटल पूर्णांक pidff_needs_set_effect(काष्ठा ff_effect *effect,
				  काष्ठा ff_effect *old)
अणु
	वापस effect->replay.length != old->replay.length ||
	       effect->trigger.पूर्णांकerval != old->trigger.पूर्णांकerval ||
	       effect->trigger.button != old->trigger.button ||
	       effect->direction != old->direction ||
	       effect->replay.delay != old->replay.delay;
पूर्ण

/*
 * Send periodic effect report to the device
 */
अटल व्योम pidff_set_periodic_report(काष्ठा pidff_device *pidff,
				      काष्ठा ff_effect *effect)
अणु
	pidff->set_periodic[PID_EFFECT_BLOCK_INDEX].value[0] =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];
	pidff_set_चिन्हित(&pidff->set_periodic[PID_MAGNITUDE],
			 effect->u.periodic.magnitude);
	pidff_set_चिन्हित(&pidff->set_periodic[PID_OFFSET],
			 effect->u.periodic.offset);
	pidff_set(&pidff->set_periodic[PID_PHASE], effect->u.periodic.phase);
	pidff->set_periodic[PID_PERIOD].value[0] = effect->u.periodic.period;

	hid_hw_request(pidff->hid, pidff->reports[PID_SET_PERIODIC],
			HID_REQ_SET_REPORT);

पूर्ण

/*
 * Test अगर periodic effect parameters have changed
 */
अटल पूर्णांक pidff_needs_set_periodic(काष्ठा ff_effect *effect,
				    काष्ठा ff_effect *old)
अणु
	वापस effect->u.periodic.magnitude != old->u.periodic.magnitude ||
	       effect->u.periodic.offset != old->u.periodic.offset ||
	       effect->u.periodic.phase != old->u.periodic.phase ||
	       effect->u.periodic.period != old->u.periodic.period;
पूर्ण

/*
 * Send condition effect reports to the device
 */
अटल व्योम pidff_set_condition_report(काष्ठा pidff_device *pidff,
				       काष्ठा ff_effect *effect)
अणु
	पूर्णांक i;

	pidff->set_condition[PID_EFFECT_BLOCK_INDEX].value[0] =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];

	क्रम (i = 0; i < 2; i++) अणु
		pidff->set_condition[PID_PARAM_BLOCK_OFFSET].value[0] = i;
		pidff_set_चिन्हित(&pidff->set_condition[PID_CP_OFFSET],
				 effect->u.condition[i].center);
		pidff_set_चिन्हित(&pidff->set_condition[PID_POS_COEFFICIENT],
				 effect->u.condition[i].right_coeff);
		pidff_set_चिन्हित(&pidff->set_condition[PID_NEG_COEFFICIENT],
				 effect->u.condition[i].left_coeff);
		pidff_set(&pidff->set_condition[PID_POS_SATURATION],
			  effect->u.condition[i].right_saturation);
		pidff_set(&pidff->set_condition[PID_NEG_SATURATION],
			  effect->u.condition[i].left_saturation);
		pidff_set(&pidff->set_condition[PID_DEAD_BAND],
			  effect->u.condition[i].deadband);
		hid_hw_request(pidff->hid, pidff->reports[PID_SET_CONDITION],
				HID_REQ_SET_REPORT);
	पूर्ण
पूर्ण

/*
 * Test अगर condition effect parameters have changed
 */
अटल पूर्णांक pidff_needs_set_condition(काष्ठा ff_effect *effect,
				     काष्ठा ff_effect *old)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा ff_condition_effect *cond = &effect->u.condition[i];
		काष्ठा ff_condition_effect *old_cond = &old->u.condition[i];

		ret |= cond->center != old_cond->center ||
		       cond->right_coeff != old_cond->right_coeff ||
		       cond->left_coeff != old_cond->left_coeff ||
		       cond->right_saturation != old_cond->right_saturation ||
		       cond->left_saturation != old_cond->left_saturation ||
		       cond->deadband != old_cond->deadband;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Send ramp क्रमce report to the device
 */
अटल व्योम pidff_set_ramp_क्रमce_report(काष्ठा pidff_device *pidff,
					काष्ठा ff_effect *effect)
अणु
	pidff->set_ramp[PID_EFFECT_BLOCK_INDEX].value[0] =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];
	pidff_set_चिन्हित(&pidff->set_ramp[PID_RAMP_START],
			 effect->u.ramp.start_level);
	pidff_set_चिन्हित(&pidff->set_ramp[PID_RAMP_END],
			 effect->u.ramp.end_level);
	hid_hw_request(pidff->hid, pidff->reports[PID_SET_RAMP],
			HID_REQ_SET_REPORT);
पूर्ण

/*
 * Test अगर ramp क्रमce parameters have changed
 */
अटल पूर्णांक pidff_needs_set_ramp(काष्ठा ff_effect *effect, काष्ठा ff_effect *old)
अणु
	वापस effect->u.ramp.start_level != old->u.ramp.start_level ||
	       effect->u.ramp.end_level != old->u.ramp.end_level;
पूर्ण

/*
 * Send a request क्रम effect upload to the device
 *
 * Returns 0 अगर device reported success, -ENOSPC अगर the device reported memory
 * is full. Upon unknown response the function will retry क्रम 60 बार, अगर
 * still unsuccessful -EIO is वापसed.
 */
अटल पूर्णांक pidff_request_effect_upload(काष्ठा pidff_device *pidff, पूर्णांक efnum)
अणु
	पूर्णांक j;

	pidff->create_new_effect_type->value[0] = efnum;
	hid_hw_request(pidff->hid, pidff->reports[PID_CREATE_NEW_EFFECT],
			HID_REQ_SET_REPORT);
	hid_dbg(pidff->hid, "create_new_effect sent, type: %d\n", efnum);

	pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0] = 0;
	pidff->block_load_status->value[0] = 0;
	hid_hw_रुको(pidff->hid);

	क्रम (j = 0; j < 60; j++) अणु
		hid_dbg(pidff->hid, "pid_block_load requested\n");
		hid_hw_request(pidff->hid, pidff->reports[PID_BLOCK_LOAD],
				HID_REQ_GET_REPORT);
		hid_hw_रुको(pidff->hid);
		अगर (pidff->block_load_status->value[0] ==
		    pidff->status_id[PID_BLOCK_LOAD_SUCCESS]) अणु
			hid_dbg(pidff->hid, "device reported free memory: %d bytes\n",
				 pidff->block_load[PID_RAM_POOL_AVAILABLE].value ?
				 pidff->block_load[PID_RAM_POOL_AVAILABLE].value[0] : -1);
			वापस 0;
		पूर्ण
		अगर (pidff->block_load_status->value[0] ==
		    pidff->status_id[PID_BLOCK_LOAD_FULL]) अणु
			hid_dbg(pidff->hid, "not enough memory free: %d bytes\n",
				pidff->block_load[PID_RAM_POOL_AVAILABLE].value ?
				pidff->block_load[PID_RAM_POOL_AVAILABLE].value[0] : -1);
			वापस -ENOSPC;
		पूर्ण
	पूर्ण
	hid_err(pidff->hid, "pid_block_load failed 60 times\n");
	वापस -EIO;
पूर्ण

/*
 * Play the effect with PID id n बार
 */
अटल व्योम pidff_playback_pid(काष्ठा pidff_device *pidff, पूर्णांक pid_id, पूर्णांक n)
अणु
	pidff->effect_operation[PID_EFFECT_BLOCK_INDEX].value[0] = pid_id;

	अगर (n == 0) अणु
		pidff->effect_operation_status->value[0] =
			pidff->operation_id[PID_EFFECT_STOP];
	पूर्ण अन्यथा अणु
		pidff->effect_operation_status->value[0] =
			pidff->operation_id[PID_EFFECT_START];
		pidff->effect_operation[PID_LOOP_COUNT].value[0] = n;
	पूर्ण

	hid_hw_request(pidff->hid, pidff->reports[PID_EFFECT_OPERATION],
			HID_REQ_SET_REPORT);
पूर्ण

/*
 * Play the effect with effect id @effect_id क्रम @value बार
 */
अटल पूर्णांक pidff_playback(काष्ठा input_dev *dev, पूर्णांक effect_id, पूर्णांक value)
अणु
	काष्ठा pidff_device *pidff = dev->ff->निजी;

	pidff_playback_pid(pidff, pidff->pid_id[effect_id], value);

	वापस 0;
पूर्ण

/*
 * Erase effect with PID id
 */
अटल व्योम pidff_erase_pid(काष्ठा pidff_device *pidff, पूर्णांक pid_id)
अणु
	pidff->block_मुक्त[PID_EFFECT_BLOCK_INDEX].value[0] = pid_id;
	hid_hw_request(pidff->hid, pidff->reports[PID_BLOCK_FREE],
			HID_REQ_SET_REPORT);
पूर्ण

/*
 * Stop and erase effect with effect_id
 */
अटल पूर्णांक pidff_erase_effect(काष्ठा input_dev *dev, पूर्णांक effect_id)
अणु
	काष्ठा pidff_device *pidff = dev->ff->निजी;
	पूर्णांक pid_id = pidff->pid_id[effect_id];

	hid_dbg(pidff->hid, "starting to erase %d/%d\n",
		effect_id, pidff->pid_id[effect_id]);
	/* Wait क्रम the queue to clear. We करो not want a full fअगरo to
	   prevent the effect removal. */
	hid_hw_रुको(pidff->hid);
	pidff_playback_pid(pidff, pid_id, 0);
	pidff_erase_pid(pidff, pid_id);

	वापस 0;
पूर्ण

/*
 * Effect upload handler
 */
अटल पूर्णांक pidff_upload_effect(काष्ठा input_dev *dev, काष्ठा ff_effect *effect,
			       काष्ठा ff_effect *old)
अणु
	काष्ठा pidff_device *pidff = dev->ff->निजी;
	पूर्णांक type_id;
	पूर्णांक error;

	pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0] = 0;
	अगर (old) अणु
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0] =
			pidff->pid_id[effect->id];
	पूर्ण

	चयन (effect->type) अणु
	हाल FF_CONSTANT:
		अगर (!old) अणु
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_CONSTANT]);
			अगर (error)
				वापस error;
		पूर्ण
		अगर (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		अगर (!old || pidff_needs_set_स्थिरant(effect, old))
			pidff_set_स्थिरant_क्रमce_report(pidff, effect);
		अगर (!old ||
		    pidff_needs_set_envelope(&effect->u.स्थिरant.envelope,
					&old->u.स्थिरant.envelope))
			pidff_set_envelope_report(pidff,
					&effect->u.स्थिरant.envelope);
		अवरोध;

	हाल FF_PERIODIC:
		अगर (!old) अणु
			चयन (effect->u.periodic.waveक्रमm) अणु
			हाल FF_SQUARE:
				type_id = PID_SQUARE;
				अवरोध;
			हाल FF_TRIANGLE:
				type_id = PID_TRIANGLE;
				अवरोध;
			हाल FF_SINE:
				type_id = PID_SINE;
				अवरोध;
			हाल FF_SAW_UP:
				type_id = PID_SAW_UP;
				अवरोध;
			हाल FF_SAW_DOWN:
				type_id = PID_SAW_DOWN;
				अवरोध;
			शेष:
				hid_err(pidff->hid, "invalid waveform\n");
				वापस -EINVAL;
			पूर्ण

			error = pidff_request_effect_upload(pidff,
					pidff->type_id[type_id]);
			अगर (error)
				वापस error;
		पूर्ण
		अगर (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		अगर (!old || pidff_needs_set_periodic(effect, old))
			pidff_set_periodic_report(pidff, effect);
		अगर (!old ||
		    pidff_needs_set_envelope(&effect->u.periodic.envelope,
					&old->u.periodic.envelope))
			pidff_set_envelope_report(pidff,
					&effect->u.periodic.envelope);
		अवरोध;

	हाल FF_RAMP:
		अगर (!old) अणु
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_RAMP]);
			अगर (error)
				वापस error;
		पूर्ण
		अगर (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		अगर (!old || pidff_needs_set_ramp(effect, old))
			pidff_set_ramp_क्रमce_report(pidff, effect);
		अगर (!old ||
		    pidff_needs_set_envelope(&effect->u.ramp.envelope,
					&old->u.ramp.envelope))
			pidff_set_envelope_report(pidff,
					&effect->u.ramp.envelope);
		अवरोध;

	हाल FF_SPRING:
		अगर (!old) अणु
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_SPRING]);
			अगर (error)
				वापस error;
		पूर्ण
		अगर (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		अगर (!old || pidff_needs_set_condition(effect, old))
			pidff_set_condition_report(pidff, effect);
		अवरोध;

	हाल FF_FRICTION:
		अगर (!old) अणु
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_FRICTION]);
			अगर (error)
				वापस error;
		पूर्ण
		अगर (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		अगर (!old || pidff_needs_set_condition(effect, old))
			pidff_set_condition_report(pidff, effect);
		अवरोध;

	हाल FF_DAMPER:
		अगर (!old) अणु
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_DAMPER]);
			अगर (error)
				वापस error;
		पूर्ण
		अगर (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		अगर (!old || pidff_needs_set_condition(effect, old))
			pidff_set_condition_report(pidff, effect);
		अवरोध;

	हाल FF_INERTIA:
		अगर (!old) अणु
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_INERTIA]);
			अगर (error)
				वापस error;
		पूर्ण
		अगर (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		अगर (!old || pidff_needs_set_condition(effect, old))
			pidff_set_condition_report(pidff, effect);
		अवरोध;

	शेष:
		hid_err(pidff->hid, "invalid type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!old)
		pidff->pid_id[effect->id] =
		    pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];

	hid_dbg(pidff->hid, "uploaded\n");

	वापस 0;
पूर्ण

/*
 * set_gain() handler
 */
अटल व्योम pidff_set_gain(काष्ठा input_dev *dev, u16 gain)
अणु
	काष्ठा pidff_device *pidff = dev->ff->निजी;

	pidff_set(&pidff->device_gain[PID_DEVICE_GAIN_FIELD], gain);
	hid_hw_request(pidff->hid, pidff->reports[PID_DEVICE_GAIN],
			HID_REQ_SET_REPORT);
पूर्ण

अटल व्योम pidff_स्वतःcenter(काष्ठा pidff_device *pidff, u16 magnitude)
अणु
	काष्ठा hid_field *field =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].field;

	अगर (!magnitude) अणु
		pidff_playback_pid(pidff, field->logical_minimum, 0);
		वापस;
	पूर्ण

	pidff_playback_pid(pidff, field->logical_minimum, 1);

	pidff->set_effect[PID_EFFECT_BLOCK_INDEX].value[0] =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].field->logical_minimum;
	pidff->set_effect_type->value[0] = pidff->type_id[PID_SPRING];
	pidff->set_effect[PID_DURATION].value[0] = 0;
	pidff->set_effect[PID_TRIGGER_BUTTON].value[0] = 0;
	pidff->set_effect[PID_TRIGGER_REPEAT_INT].value[0] = 0;
	pidff_set(&pidff->set_effect[PID_GAIN], magnitude);
	pidff->set_effect[PID_सूचीECTION_ENABLE].value[0] = 1;
	pidff->set_effect[PID_START_DELAY].value[0] = 0;

	hid_hw_request(pidff->hid, pidff->reports[PID_SET_EFFECT],
			HID_REQ_SET_REPORT);
पूर्ण

/*
 * pidff_set_स्वतःcenter() handler
 */
अटल व्योम pidff_set_स्वतःcenter(काष्ठा input_dev *dev, u16 magnitude)
अणु
	काष्ठा pidff_device *pidff = dev->ff->निजी;

	pidff_स्वतःcenter(pidff, magnitude);
पूर्ण

/*
 * Find fields from a report and fill a pidff_usage
 */
अटल पूर्णांक pidff_find_fields(काष्ठा pidff_usage *usage, स्थिर u8 *table,
			     काष्ठा hid_report *report, पूर्णांक count, पूर्णांक strict)
अणु
	पूर्णांक i, j, k, found;

	क्रम (k = 0; k < count; k++) अणु
		found = 0;
		क्रम (i = 0; i < report->maxfield; i++) अणु
			अगर (report->field[i]->maxusage !=
			    report->field[i]->report_count) अणु
				pr_debug("maxusage and report_count do not match, skipping\n");
				जारी;
			पूर्ण
			क्रम (j = 0; j < report->field[i]->maxusage; j++) अणु
				अगर (report->field[i]->usage[j].hid ==
				    (HID_UP_PID | table[k])) अणु
					pr_debug("found %d at %d->%d\n",
						 k, i, j);
					usage[k].field = report->field[i];
					usage[k].value =
						&report->field[i]->value[j];
					found = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (found)
				अवरोध;
		पूर्ण
		अगर (!found && strict) अणु
			pr_debug("failed to locate %d\n", k);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return index पूर्णांकo pidff_reports क्रम the given usage
 */
अटल पूर्णांक pidff_check_usage(पूर्णांक usage)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < माप(pidff_reports); i++)
		अगर (usage == (HID_UP_PID | pidff_reports[i]))
			वापस i;

	वापस -1;
पूर्ण

/*
 * Find the reports and fill pidff->reports[]
 * report_type specअगरies either OUTPUT or FEATURE reports
 */
अटल व्योम pidff_find_reports(काष्ठा hid_device *hid, पूर्णांक report_type,
			       काष्ठा pidff_device *pidff)
अणु
	काष्ठा hid_report *report;
	पूर्णांक i, ret;

	list_क्रम_each_entry(report,
			    &hid->report_क्रमागत[report_type].report_list, list) अणु
		अगर (report->maxfield < 1)
			जारी;
		ret = pidff_check_usage(report->field[0]->logical);
		अगर (ret != -1) अणु
			hid_dbg(hid, "found usage 0x%02x from field->logical\n",
				pidff_reports[ret]);
			pidff->reports[ret] = report;
			जारी;
		पूर्ण

		/*
		 * Someबार logical collections are stacked to indicate
		 * dअगरferent usages क्रम the report and the field, in which
		 * हाल we want the usage of the parent. However, Linux HID
		 * implementation hides this fact, so we have to dig it up
		 * ourselves
		 */
		i = report->field[0]->usage[0].collection_index;
		अगर (i <= 0 ||
		    hid->collection[i - 1].type != HID_COLLECTION_LOGICAL)
			जारी;
		ret = pidff_check_usage(hid->collection[i - 1].usage);
		अगर (ret != -1 && !pidff->reports[ret]) अणु
			hid_dbg(hid,
				"found usage 0x%02x from collection array\n",
				pidff_reports[ret]);
			pidff->reports[ret] = report;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Test अगर the required reports have been found
 */
अटल पूर्णांक pidff_reports_ok(काष्ठा pidff_device *pidff)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= PID_REQUIRED_REPORTS; i++) अणु
		अगर (!pidff->reports[i]) अणु
			hid_dbg(pidff->hid, "%d missing\n", i);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Find a field with a specअगरic usage within a report
 */
अटल काष्ठा hid_field *pidff_find_special_field(काष्ठा hid_report *report,
						  पूर्णांक usage, पूर्णांक enक्रमce_min)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < report->maxfield; i++) अणु
		अगर (report->field[i]->logical == (HID_UP_PID | usage) &&
		    report->field[i]->report_count > 0) अणु
			अगर (!enक्रमce_min ||
			    report->field[i]->logical_minimum == 1)
				वापस report->field[i];
			अन्यथा अणु
				pr_err("logical_minimum is not 1 as it should be\n");
				वापस शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Fill a pidff->*_id काष्ठा table
 */
अटल पूर्णांक pidff_find_special_keys(पूर्णांक *keys, काष्ठा hid_field *fld,
				   स्थिर u8 *usagetable, पूर्णांक count)
अणु

	पूर्णांक i, j;
	पूर्णांक found = 0;

	क्रम (i = 0; i < count; i++) अणु
		क्रम (j = 0; j < fld->maxusage; j++) अणु
			अगर (fld->usage[j].hid == (HID_UP_PID | usagetable[i])) अणु
				keys[i] = j + 1;
				found++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

#घोषणा PIDFF_FIND_SPECIAL_KEYS(keys, field, name) \
	pidff_find_special_keys(pidff->keys, pidff->field, pidff_ ## name, \
		माप(pidff_ ## name))

/*
 * Find and check the special fields
 */
अटल पूर्णांक pidff_find_special_fields(काष्ठा pidff_device *pidff)
अणु
	hid_dbg(pidff->hid, "finding special fields\n");

	pidff->create_new_effect_type =
		pidff_find_special_field(pidff->reports[PID_CREATE_NEW_EFFECT],
					 0x25, 1);
	pidff->set_effect_type =
		pidff_find_special_field(pidff->reports[PID_SET_EFFECT],
					 0x25, 1);
	pidff->effect_direction =
		pidff_find_special_field(pidff->reports[PID_SET_EFFECT],
					 0x57, 0);
	pidff->device_control =
		pidff_find_special_field(pidff->reports[PID_DEVICE_CONTROL],
					 0x96, 1);
	pidff->block_load_status =
		pidff_find_special_field(pidff->reports[PID_BLOCK_LOAD],
					 0x8b, 1);
	pidff->effect_operation_status =
		pidff_find_special_field(pidff->reports[PID_EFFECT_OPERATION],
					 0x78, 1);

	hid_dbg(pidff->hid, "search done\n");

	अगर (!pidff->create_new_effect_type || !pidff->set_effect_type) अणु
		hid_err(pidff->hid, "effect lists not found\n");
		वापस -1;
	पूर्ण

	अगर (!pidff->effect_direction) अणु
		hid_err(pidff->hid, "direction field not found\n");
		वापस -1;
	पूर्ण

	अगर (!pidff->device_control) अणु
		hid_err(pidff->hid, "device control field not found\n");
		वापस -1;
	पूर्ण

	अगर (!pidff->block_load_status) अणु
		hid_err(pidff->hid, "block load status field not found\n");
		वापस -1;
	पूर्ण

	अगर (!pidff->effect_operation_status) अणु
		hid_err(pidff->hid, "effect operation field not found\n");
		वापस -1;
	पूर्ण

	pidff_find_special_keys(pidff->control_id, pidff->device_control,
				pidff_device_control,
				माप(pidff_device_control));

	PIDFF_FIND_SPECIAL_KEYS(control_id, device_control, device_control);

	अगर (!PIDFF_FIND_SPECIAL_KEYS(type_id, create_new_effect_type,
				     effect_types)) अणु
		hid_err(pidff->hid, "no effect types found\n");
		वापस -1;
	पूर्ण

	अगर (PIDFF_FIND_SPECIAL_KEYS(status_id, block_load_status,
				    block_load_status) !=
			माप(pidff_block_load_status)) अणु
		hid_err(pidff->hid,
			"block load status identifiers not found\n");
		वापस -1;
	पूर्ण

	अगर (PIDFF_FIND_SPECIAL_KEYS(operation_id, effect_operation_status,
				    effect_operation_status) !=
			माप(pidff_effect_operation_status)) अणु
		hid_err(pidff->hid, "effect operation identifiers not found\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Find the implemented effect types
 */
अटल पूर्णांक pidff_find_effects(काष्ठा pidff_device *pidff,
			      काष्ठा input_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < माप(pidff_effect_types); i++) अणु
		पूर्णांक pidff_type = pidff->type_id[i];
		अगर (pidff->set_effect_type->usage[pidff_type].hid !=
		    pidff->create_new_effect_type->usage[pidff_type].hid) अणु
			hid_err(pidff->hid,
				"effect type number %d is invalid\n", i);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (pidff->type_id[PID_CONSTANT])
		set_bit(FF_CONSTANT, dev->ffbit);
	अगर (pidff->type_id[PID_RAMP])
		set_bit(FF_RAMP, dev->ffbit);
	अगर (pidff->type_id[PID_SQUARE]) अणु
		set_bit(FF_SQUARE, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	पूर्ण
	अगर (pidff->type_id[PID_SINE]) अणु
		set_bit(FF_SINE, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	पूर्ण
	अगर (pidff->type_id[PID_TRIANGLE]) अणु
		set_bit(FF_TRIANGLE, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	पूर्ण
	अगर (pidff->type_id[PID_SAW_UP]) अणु
		set_bit(FF_SAW_UP, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	पूर्ण
	अगर (pidff->type_id[PID_SAW_DOWN]) अणु
		set_bit(FF_SAW_DOWN, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	पूर्ण
	अगर (pidff->type_id[PID_SPRING])
		set_bit(FF_SPRING, dev->ffbit);
	अगर (pidff->type_id[PID_DAMPER])
		set_bit(FF_DAMPER, dev->ffbit);
	अगर (pidff->type_id[PID_INERTIA])
		set_bit(FF_INERTIA, dev->ffbit);
	अगर (pidff->type_id[PID_FRICTION])
		set_bit(FF_FRICTION, dev->ffbit);

	वापस 0;

पूर्ण

#घोषणा PIDFF_FIND_FIELDS(name, report, strict) \
	pidff_find_fields(pidff->name, pidff_ ## name, \
		pidff->reports[report], \
		माप(pidff_ ## name), strict)

/*
 * Fill and check the pidff_usages
 */
अटल पूर्णांक pidff_init_fields(काष्ठा pidff_device *pidff, काष्ठा input_dev *dev)
अणु
	पूर्णांक envelope_ok = 0;

	अगर (PIDFF_FIND_FIELDS(set_effect, PID_SET_EFFECT, 1)) अणु
		hid_err(pidff->hid, "unknown set_effect report layout\n");
		वापस -ENODEV;
	पूर्ण

	PIDFF_FIND_FIELDS(block_load, PID_BLOCK_LOAD, 0);
	अगर (!pidff->block_load[PID_EFFECT_BLOCK_INDEX].value) अणु
		hid_err(pidff->hid, "unknown pid_block_load report layout\n");
		वापस -ENODEV;
	पूर्ण

	अगर (PIDFF_FIND_FIELDS(effect_operation, PID_EFFECT_OPERATION, 1)) अणु
		hid_err(pidff->hid, "unknown effect_operation report layout\n");
		वापस -ENODEV;
	पूर्ण

	अगर (PIDFF_FIND_FIELDS(block_मुक्त, PID_BLOCK_FREE, 1)) अणु
		hid_err(pidff->hid, "unknown pid_block_free report layout\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!PIDFF_FIND_FIELDS(set_envelope, PID_SET_ENVELOPE, 1))
		envelope_ok = 1;

	अगर (pidff_find_special_fields(pidff) || pidff_find_effects(pidff, dev))
		वापस -ENODEV;

	अगर (!envelope_ok) अणु
		अगर (test_and_clear_bit(FF_CONSTANT, dev->ffbit))
			hid_warn(pidff->hid,
				 "has constant effect but no envelope\n");
		अगर (test_and_clear_bit(FF_RAMP, dev->ffbit))
			hid_warn(pidff->hid,
				 "has ramp effect but no envelope\n");

		अगर (test_and_clear_bit(FF_PERIODIC, dev->ffbit))
			hid_warn(pidff->hid,
				 "has periodic effect but no envelope\n");
	पूर्ण

	अगर (test_bit(FF_CONSTANT, dev->ffbit) &&
	    PIDFF_FIND_FIELDS(set_स्थिरant, PID_SET_CONSTANT, 1)) अणु
		hid_warn(pidff->hid, "unknown constant effect layout\n");
		clear_bit(FF_CONSTANT, dev->ffbit);
	पूर्ण

	अगर (test_bit(FF_RAMP, dev->ffbit) &&
	    PIDFF_FIND_FIELDS(set_ramp, PID_SET_RAMP, 1)) अणु
		hid_warn(pidff->hid, "unknown ramp effect layout\n");
		clear_bit(FF_RAMP, dev->ffbit);
	पूर्ण

	अगर ((test_bit(FF_SPRING, dev->ffbit) ||
	     test_bit(FF_DAMPER, dev->ffbit) ||
	     test_bit(FF_FRICTION, dev->ffbit) ||
	     test_bit(FF_INERTIA, dev->ffbit)) &&
	    PIDFF_FIND_FIELDS(set_condition, PID_SET_CONDITION, 1)) अणु
		hid_warn(pidff->hid, "unknown condition effect layout\n");
		clear_bit(FF_SPRING, dev->ffbit);
		clear_bit(FF_DAMPER, dev->ffbit);
		clear_bit(FF_FRICTION, dev->ffbit);
		clear_bit(FF_INERTIA, dev->ffbit);
	पूर्ण

	अगर (test_bit(FF_PERIODIC, dev->ffbit) &&
	    PIDFF_FIND_FIELDS(set_periodic, PID_SET_PERIODIC, 1)) अणु
		hid_warn(pidff->hid, "unknown periodic effect layout\n");
		clear_bit(FF_PERIODIC, dev->ffbit);
	पूर्ण

	PIDFF_FIND_FIELDS(pool, PID_POOL, 0);

	अगर (!PIDFF_FIND_FIELDS(device_gain, PID_DEVICE_GAIN, 1))
		set_bit(FF_GAIN, dev->ffbit);

	वापस 0;
पूर्ण

/*
 * Reset the device
 */
अटल व्योम pidff_reset(काष्ठा pidff_device *pidff)
अणु
	काष्ठा hid_device *hid = pidff->hid;
	पूर्णांक i = 0;

	pidff->device_control->value[0] = pidff->control_id[PID_RESET];
	/* We reset twice as someबार hid_रुको_io isn't रुकोing दीर्घ enough */
	hid_hw_request(hid, pidff->reports[PID_DEVICE_CONTROL], HID_REQ_SET_REPORT);
	hid_hw_रुको(hid);
	hid_hw_request(hid, pidff->reports[PID_DEVICE_CONTROL], HID_REQ_SET_REPORT);
	hid_hw_रुको(hid);

	pidff->device_control->value[0] =
		pidff->control_id[PID_ENABLE_ACTUATORS];
	hid_hw_request(hid, pidff->reports[PID_DEVICE_CONTROL], HID_REQ_SET_REPORT);
	hid_hw_रुको(hid);

	/* pool report is someबार messed up, refetch it */
	hid_hw_request(hid, pidff->reports[PID_POOL], HID_REQ_GET_REPORT);
	hid_hw_रुको(hid);

	अगर (pidff->pool[PID_SIMULTANEOUS_MAX].value) अणु
		जबतक (pidff->pool[PID_SIMULTANEOUS_MAX].value[0] < 2) अणु
			अगर (i++ > 20) अणु
				hid_warn(pidff->hid,
					 "device reports %d simultaneous effects\n",
					 pidff->pool[PID_SIMULTANEOUS_MAX].value[0]);
				अवरोध;
			पूर्ण
			hid_dbg(pidff->hid, "pid_pool requested again\n");
			hid_hw_request(hid, pidff->reports[PID_POOL],
					  HID_REQ_GET_REPORT);
			hid_hw_रुको(hid);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Test अगर स्वतःcenter modअगरication is using the supported method
 */
अटल पूर्णांक pidff_check_स्वतःcenter(काष्ठा pidff_device *pidff,
				  काष्ठा input_dev *dev)
अणु
	पूर्णांक error;

	/*
	 * Let's find out अगर स्वतःcenter modअगरication is supported
	 * Specअगरication करोesn't specअगरy anything, so we request an
	 * effect upload and cancel it immediately. If the approved
	 * effect id was one above the minimum, then we assume the first
	 * effect id is a built-in spring type effect used क्रम स्वतःcenter
	 */

	error = pidff_request_effect_upload(pidff, 1);
	अगर (error) अणु
		hid_err(pidff->hid, "upload request failed\n");
		वापस error;
	पूर्ण

	अगर (pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0] ==
	    pidff->block_load[PID_EFFECT_BLOCK_INDEX].field->logical_minimum + 1) अणु
		pidff_स्वतःcenter(pidff, 0xffff);
		set_bit(FF_AUTOCENTER, dev->ffbit);
	पूर्ण अन्यथा अणु
		hid_notice(pidff->hid,
			   "device has unknown autocenter control method\n");
	पूर्ण

	pidff_erase_pid(pidff,
			pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0]);

	वापस 0;

पूर्ण

/*
 * Check अगर the device is PID and initialize it
 */
पूर्णांक hid_pidff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा pidff_device *pidff;
	काष्ठा hid_input *hidinput = list_entry(hid->inमाला_दो.next,
						काष्ठा hid_input, list);
	काष्ठा input_dev *dev = hidinput->input;
	काष्ठा ff_device *ff;
	पूर्णांक max_effects;
	पूर्णांक error;

	hid_dbg(hid, "starting pid init\n");

	अगर (list_empty(&hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list)) अणु
		hid_dbg(hid, "not a PID device, no output report\n");
		वापस -ENODEV;
	पूर्ण

	pidff = kzalloc(माप(*pidff), GFP_KERNEL);
	अगर (!pidff)
		वापस -ENOMEM;

	pidff->hid = hid;

	hid_device_io_start(hid);

	pidff_find_reports(hid, HID_OUTPUT_REPORT, pidff);
	pidff_find_reports(hid, HID_FEATURE_REPORT, pidff);

	अगर (!pidff_reports_ok(pidff)) अणु
		hid_dbg(hid, "reports not ok, aborting\n");
		error = -ENODEV;
		जाओ fail;
	पूर्ण

	error = pidff_init_fields(pidff, dev);
	अगर (error)
		जाओ fail;

	pidff_reset(pidff);

	अगर (test_bit(FF_GAIN, dev->ffbit)) अणु
		pidff_set(&pidff->device_gain[PID_DEVICE_GAIN_FIELD], 0xffff);
		hid_hw_request(hid, pidff->reports[PID_DEVICE_GAIN],
				     HID_REQ_SET_REPORT);
	पूर्ण

	error = pidff_check_स्वतःcenter(pidff, dev);
	अगर (error)
		जाओ fail;

	max_effects =
	    pidff->block_load[PID_EFFECT_BLOCK_INDEX].field->logical_maximum -
	    pidff->block_load[PID_EFFECT_BLOCK_INDEX].field->logical_minimum +
	    1;
	hid_dbg(hid, "max effects is %d\n", max_effects);

	अगर (max_effects > PID_EFFECTS_MAX)
		max_effects = PID_EFFECTS_MAX;

	अगर (pidff->pool[PID_SIMULTANEOUS_MAX].value)
		hid_dbg(hid, "max simultaneous effects is %d\n",
			pidff->pool[PID_SIMULTANEOUS_MAX].value[0]);

	अगर (pidff->pool[PID_RAM_POOL_SIZE].value)
		hid_dbg(hid, "device memory size is %d bytes\n",
			pidff->pool[PID_RAM_POOL_SIZE].value[0]);

	अगर (pidff->pool[PID_DEVICE_MANAGED_POOL].value &&
	    pidff->pool[PID_DEVICE_MANAGED_POOL].value[0] == 0) अणु
		error = -EPERM;
		hid_notice(hid,
			   "device does not support device managed pool\n");
		जाओ fail;
	पूर्ण

	error = input_ff_create(dev, max_effects);
	अगर (error)
		जाओ fail;

	ff = dev->ff;
	ff->निजी = pidff;
	ff->upload = pidff_upload_effect;
	ff->erase = pidff_erase_effect;
	ff->set_gain = pidff_set_gain;
	ff->set_स्वतःcenter = pidff_set_स्वतःcenter;
	ff->playback = pidff_playback;

	hid_info(dev, "Force feedback for USB HID PID devices by Anssi Hannula <anssi.hannula@gmail.com>\n");

	hid_device_io_stop(hid);

	वापस 0;

 fail:
	hid_device_io_stop(hid);

	kमुक्त(pidff);
	वापस error;
पूर्ण
