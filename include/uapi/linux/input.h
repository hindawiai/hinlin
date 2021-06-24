<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (c) 1999-2002 Vojtech Pavlik
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#अगर_अघोषित _UAPI_INPUT_H
#घोषणा _UAPI_INPUT_H


#अगर_अघोषित __KERNEL__
#समावेश <sys/समय.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/types.h>
#समावेश <linux/types.h>
#पूर्ण_अगर

#समावेश "input-event-codes.h"

/*
 * The event काष्ठाure itself
 * Note that __USE_TIME_BITS64 is defined by libc based on
 * application's request to use 64 bit समय_प्रकार.
 */

काष्ठा input_event अणु
#अगर (__BITS_PER_LONG != 32 || !defined(__USE_TIME_BITS64)) && !defined(__KERNEL__)
	काष्ठा समयval समय;
#घोषणा input_event_sec समय.tv_sec
#घोषणा input_event_usec समय.tv_usec
#अन्यथा
	__kernel_uदीर्घ_t __sec;
#अगर defined(__sparc__) && defined(__arch64__)
	अचिन्हित पूर्णांक __usec;
	अचिन्हित पूर्णांक __pad;
#अन्यथा
	__kernel_uदीर्घ_t __usec;
#पूर्ण_अगर
#घोषणा input_event_sec  __sec
#घोषणा input_event_usec __usec
#पूर्ण_अगर
	__u16 type;
	__u16 code;
	__s32 value;
पूर्ण;

/*
 * Protocol version.
 */

#घोषणा EV_VERSION		0x010001

/*
 * IOCTLs (0x00 - 0x7f)
 */

काष्ठा input_id अणु
	__u16 bustype;
	__u16 venकरोr;
	__u16 product;
	__u16 version;
पूर्ण;

/**
 * काष्ठा input_असलinfo - used by EVIOCGABS/EVIOCSABS ioctls
 * @value: latest reported value क्रम the axis.
 * @minimum: specअगरies minimum value क्रम the axis.
 * @maximum: specअगरies maximum value क्रम the axis.
 * @fuzz: specअगरies fuzz value that is used to filter noise from
 *	the event stream.
 * @flat: values that are within this value will be discarded by
 *	joydev पूर्णांकerface and reported as 0 instead.
 * @resolution: specअगरies resolution क्रम the values reported क्रम
 *	the axis.
 *
 * Note that input core करोes not clamp reported values to the
 * [minimum, maximum] limits, such task is left to userspace.
 *
 * The शेष resolution क्रम मुख्य axes (ABS_X, ABS_Y, ABS_Z)
 * is reported in units per millimeter (units/mm), resolution
 * क्रम rotational axes (ABS_RX, ABS_RY, ABS_RZ) is reported
 * in units per radian.
 * When INPUT_PROP_ACCELEROMETER is set the resolution changes.
 * The मुख्य axes (ABS_X, ABS_Y, ABS_Z) are then reported in
 * units per g (units/g) and in units per degree per second
 * (units/deg/s) क्रम rotational axes (ABS_RX, ABS_RY, ABS_RZ).
 */
काष्ठा input_असलinfo अणु
	__s32 value;
	__s32 minimum;
	__s32 maximum;
	__s32 fuzz;
	__s32 flat;
	__s32 resolution;
पूर्ण;

/**
 * काष्ठा input_keymap_entry - used by EVIOCGKEYCODE/EVIOCSKEYCODE ioctls
 * @scancode: scancode represented in machine-endian क्रमm.
 * @len: length of the scancode that resides in @scancode buffer.
 * @index: index in the keymap, may be used instead of scancode
 * @flags: allows to specअगरy how kernel should handle the request. For
 *	example, setting INPUT_KEYMAP_BY_INDEX flag indicates that kernel
 *	should perक्रमm lookup in keymap by @index instead of @scancode
 * @keycode: key code asचिन्हित to this scancode
 *
 * The काष्ठाure is used to retrieve and modअगरy keymap data. Users have
 * option of perक्रमming lookup either by @scancode itself or by @index
 * in keymap entry. EVIOCGKEYCODE will also वापस scancode or index
 * (depending on which element was used to perक्रमm lookup).
 */
काष्ठा input_keymap_entry अणु
#घोषणा INPUT_KEYMAP_BY_INDEX	(1 << 0)
	__u8  flags;
	__u8  len;
	__u16 index;
	__u32 keycode;
	__u8  scancode[32];
पूर्ण;

काष्ठा input_mask अणु
	__u32 type;
	__u32 codes_size;
	__u64 codes_ptr;
पूर्ण;

#घोषणा EVIOCGVERSION		_IOR('E', 0x01, पूर्णांक)			/* get driver version */
#घोषणा EVIOCGID		_IOR('E', 0x02, काष्ठा input_id)	/* get device ID */
#घोषणा EVIOCGREP		_IOR('E', 0x03, अचिन्हित पूर्णांक[2])	/* get repeat settings */
#घोषणा EVIOCSREP		_IOW('E', 0x03, अचिन्हित पूर्णांक[2])	/* set repeat settings */

#घोषणा EVIOCGKEYCODE		_IOR('E', 0x04, अचिन्हित पूर्णांक[2])        /* get keycode */
#घोषणा EVIOCGKEYCODE_V2	_IOR('E', 0x04, काष्ठा input_keymap_entry)
#घोषणा EVIOCSKEYCODE		_IOW('E', 0x04, अचिन्हित पूर्णांक[2])        /* set keycode */
#घोषणा EVIOCSKEYCODE_V2	_IOW('E', 0x04, काष्ठा input_keymap_entry)

#घोषणा EVIOCGNAME(len)		_IOC(_IOC_READ, 'E', 0x06, len)		/* get device name */
#घोषणा EVIOCGPHYS(len)		_IOC(_IOC_READ, 'E', 0x07, len)		/* get physical location */
#घोषणा EVIOCGUNIQ(len)		_IOC(_IOC_READ, 'E', 0x08, len)		/* get unique identअगरier */
#घोषणा EVIOCGPROP(len)		_IOC(_IOC_READ, 'E', 0x09, len)		/* get device properties */

/**
 * EVIOCGMTSLOTS(len) - get MT slot values
 * @len: size of the data buffer in bytes
 *
 * The ioctl buffer argument should be binary equivalent to
 *
 * काष्ठा input_mt_request_layout अणु
 *	__u32 code;
 *	__s32 values[num_slots];
 * पूर्ण;
 *
 * where num_slots is the (arbitrary) number of MT slots to extract.
 *
 * The ioctl size argument (len) is the size of the buffer, which
 * should satisfy len = (num_slots + 1) * माप(__s32).  If len is
 * too small to fit all available slots, the first num_slots are
 * वापसed.
 *
 * Beक्रमe the call, code is set to the wanted ABS_MT event type. On
 * वापस, values[] is filled with the slot values क्रम the specअगरied
 * ABS_MT code.
 *
 * If the request code is not an ABS_MT value, -EINVAL is वापसed.
 */
#घोषणा EVIOCGMTSLOTS(len)	_IOC(_IOC_READ, 'E', 0x0a, len)

#घोषणा EVIOCGKEY(len)		_IOC(_IOC_READ, 'E', 0x18, len)		/* get global key state */
#घोषणा EVIOCGLED(len)		_IOC(_IOC_READ, 'E', 0x19, len)		/* get all LEDs */
#घोषणा EVIOCGSND(len)		_IOC(_IOC_READ, 'E', 0x1a, len)		/* get all sounds status */
#घोषणा EVIOCGSW(len)		_IOC(_IOC_READ, 'E', 0x1b, len)		/* get all चयन states */

#घोषणा EVIOCGBIT(ev,len)	_IOC(_IOC_READ, 'E', 0x20 + (ev), len)	/* get event bits */
#घोषणा EVIOCGABS(असल)		_IOR('E', 0x40 + (असल), काष्ठा input_असलinfo)	/* get असल value/limits */
#घोषणा EVIOCSABS(असल)		_IOW('E', 0xc0 + (असल), काष्ठा input_असलinfo)	/* set असल value/limits */

#घोषणा EVIOCSFF		_IOW('E', 0x80, काष्ठा ff_effect)	/* send a क्रमce effect to a क्रमce feedback device */
#घोषणा EVIOCRMFF		_IOW('E', 0x81, पूर्णांक)			/* Erase a क्रमce effect */
#घोषणा EVIOCGEFFECTS		_IOR('E', 0x84, पूर्णांक)			/* Report number of effects playable at the same समय */

#घोषणा EVIOCGRAB		_IOW('E', 0x90, पूर्णांक)			/* Grab/Release device */
#घोषणा EVIOCREVOKE		_IOW('E', 0x91, पूर्णांक)			/* Revoke device access */

/**
 * EVIOCGMASK - Retrieve current event mask
 *
 * This ioctl allows user to retrieve the current event mask क्रम specअगरic
 * event type. The argument must be of type "struct input_mask" and
 * specअगरies the event type to query, the address of the receive buffer and
 * the size of the receive buffer.
 *
 * The event mask is a per-client mask that specअगरies which events are
 * क्रमwarded to the client. Each event code is represented by a single bit
 * in the event mask. If the bit is set, the event is passed to the client
 * normally. Otherwise, the event is filtered and will never be queued on
 * the client's receive buffer.
 *
 * Event masks करो not affect global state of the input device. They only
 * affect the file descriptor they are applied to.
 *
 * The शेष event mask क्रम a client has all bits set, i.e. all events
 * are क्रमwarded to the client. If the kernel is queried क्रम an unknown
 * event type or अगर the receive buffer is larger than the number of
 * event codes known to the kernel, the kernel वापसs all zeroes क्रम those
 * codes.
 *
 * At maximum, codes_size bytes are copied.
 *
 * This ioctl may fail with ENODEV in हाल the file is revoked, EFAULT
 * अगर the receive-buffer poपूर्णांकs to invalid memory, or EINVAL अगर the kernel
 * करोes not implement the ioctl.
 */
#घोषणा EVIOCGMASK		_IOR('E', 0x92, काष्ठा input_mask)	/* Get event-masks */

/**
 * EVIOCSMASK - Set event mask
 *
 * This ioctl is the counterpart to EVIOCGMASK. Instead of receiving the
 * current event mask, this changes the client's event mask क्रम a specअगरic
 * type.  See EVIOCGMASK क्रम a description of event-masks and the
 * argument-type.
 *
 * This ioctl provides full क्रमward compatibility. If the passed event type
 * is unknown to the kernel, or अगर the number of event codes specअगरied in
 * the mask is bigger than what is known to the kernel, the ioctl is still
 * accepted and applied. However, any unknown codes are left untouched and
 * stay cleared. That means, the kernel always filters unknown codes
 * regardless of what the client requests.  If the new mask करोesn't cover
 * all known event-codes, all reमुख्यing codes are स्वतःmatically cleared and
 * thus filtered.
 *
 * This ioctl may fail with ENODEV in हाल the file is revoked. EFAULT is
 * वापसed अगर the receive-buffer poपूर्णांकs to invalid memory. EINVAL is वापसed
 * अगर the kernel करोes not implement the ioctl.
 */
#घोषणा EVIOCSMASK		_IOW('E', 0x93, काष्ठा input_mask)	/* Set event-masks */

#घोषणा EVIOCSCLOCKID		_IOW('E', 0xa0, पूर्णांक)			/* Set घड़ीid to be used क्रम बारtamps */

/*
 * IDs.
 */

#घोषणा ID_BUS			0
#घोषणा ID_VENDOR		1
#घोषणा ID_PRODUCT		2
#घोषणा ID_VERSION		3

#घोषणा BUS_PCI			0x01
#घोषणा BUS_ISAPNP		0x02
#घोषणा BUS_USB			0x03
#घोषणा BUS_HIL			0x04
#घोषणा BUS_BLUETOOTH		0x05
#घोषणा BUS_VIRTUAL		0x06

#घोषणा BUS_ISA			0x10
#घोषणा BUS_I8042		0x11
#घोषणा BUS_XTKBD		0x12
#घोषणा BUS_RS232		0x13
#घोषणा BUS_GAMEPORT		0x14
#घोषणा BUS_PARPORT		0x15
#घोषणा BUS_AMIGA		0x16
#घोषणा BUS_ADB			0x17
#घोषणा BUS_I2C			0x18
#घोषणा BUS_HOST		0x19
#घोषणा BUS_GSC			0x1A
#घोषणा BUS_ATARI		0x1B
#घोषणा BUS_SPI			0x1C
#घोषणा BUS_RMI			0x1D
#घोषणा BUS_CEC			0x1E
#घोषणा BUS_INTEL_ISHTP		0x1F

/*
 * MT_TOOL types
 */
#घोषणा MT_TOOL_FINGER		0x00
#घोषणा MT_TOOL_PEN		0x01
#घोषणा MT_TOOL_PALM		0x02
#घोषणा MT_TOOL_DIAL		0x0a
#घोषणा MT_TOOL_MAX		0x0f

/*
 * Values describing the status of a क्रमce-feedback effect
 */
#घोषणा FF_STATUS_STOPPED	0x00
#घोषणा FF_STATUS_PLAYING	0x01
#घोषणा FF_STATUS_MAX		0x01

/*
 * Structures used in ioctls to upload effects to a device
 * They are pieces of a bigger काष्ठाure (called ff_effect)
 */

/*
 * All duration values are expressed in ms. Values above 32767 ms (0x7fff)
 * should not be used and have unspecअगरied results.
 */

/**
 * काष्ठा ff_replay - defines scheduling of the क्रमce-feedback effect
 * @length: duration of the effect
 * @delay: delay beक्रमe effect should start playing
 */
काष्ठा ff_replay अणु
	__u16 length;
	__u16 delay;
पूर्ण;

/**
 * काष्ठा ff_trigger - defines what triggers the क्रमce-feedback effect
 * @button: number of the button triggering the effect
 * @पूर्णांकerval: controls how soon the effect can be re-triggered
 */
काष्ठा ff_trigger अणु
	__u16 button;
	__u16 पूर्णांकerval;
पूर्ण;

/**
 * काष्ठा ff_envelope - generic क्रमce-feedback effect envelope
 * @attack_length: duration of the attack (ms)
 * @attack_level: level at the beginning of the attack
 * @fade_length: duration of fade (ms)
 * @fade_level: level at the end of fade
 *
 * The @attack_level and @fade_level are असलolute values; when applying
 * envelope क्रमce-feedback core will convert to positive/negative
 * value based on polarity of the शेष level of the effect.
 * Valid range क्रम the attack and fade levels is 0x0000 - 0x7fff
 */
काष्ठा ff_envelope अणु
	__u16 attack_length;
	__u16 attack_level;
	__u16 fade_length;
	__u16 fade_level;
पूर्ण;

/**
 * काष्ठा ff_स्थिरant_effect - defines parameters of a स्थिरant क्रमce-feedback effect
 * @level: strength of the effect; may be negative
 * @envelope: envelope data
 */
काष्ठा ff_स्थिरant_effect अणु
	__s16 level;
	काष्ठा ff_envelope envelope;
पूर्ण;

/**
 * काष्ठा ff_ramp_effect - defines parameters of a ramp क्रमce-feedback effect
 * @start_level: beginning strength of the effect; may be negative
 * @end_level: final strength of the effect; may be negative
 * @envelope: envelope data
 */
काष्ठा ff_ramp_effect अणु
	__s16 start_level;
	__s16 end_level;
	काष्ठा ff_envelope envelope;
पूर्ण;

/**
 * काष्ठा ff_condition_effect - defines a spring or friction क्रमce-feedback effect
 * @right_saturation: maximum level when joystick moved all way to the right
 * @left_saturation: same क्रम the left side
 * @right_coeff: controls how fast the क्रमce grows when the joystick moves
 *	to the right
 * @left_coeff: same क्रम the left side
 * @deadband: size of the dead zone, where no क्रमce is produced
 * @center: position of the dead zone
 */
काष्ठा ff_condition_effect अणु
	__u16 right_saturation;
	__u16 left_saturation;

	__s16 right_coeff;
	__s16 left_coeff;

	__u16 deadband;
	__s16 center;
पूर्ण;

/**
 * काष्ठा ff_periodic_effect - defines parameters of a periodic क्रमce-feedback effect
 * @waveक्रमm: kind of the effect (wave)
 * @period: period of the wave (ms)
 * @magnitude: peak value
 * @offset: mean value of the wave (roughly)
 * @phase: 'horizontal' shअगरt
 * @envelope: envelope data
 * @custom_len: number of samples (FF_CUSTOM only)
 * @custom_data: buffer of samples (FF_CUSTOM only)
 *
 * Known waveक्रमms - FF_SQUARE, FF_TRIANGLE, FF_SINE, FF_SAW_UP,
 * FF_SAW_DOWN, FF_CUSTOM. The exact syntax FF_CUSTOM is undefined
 * क्रम the समय being as no driver supports it yet.
 *
 * Note: the data poपूर्णांकed by custom_data is copied by the driver.
 * You can thereक्रमe dispose of the memory after the upload/update.
 */
काष्ठा ff_periodic_effect अणु
	__u16 waveक्रमm;
	__u16 period;
	__s16 magnitude;
	__s16 offset;
	__u16 phase;

	काष्ठा ff_envelope envelope;

	__u32 custom_len;
	__s16 __user *custom_data;
पूर्ण;

/**
 * काष्ठा ff_rumble_effect - defines parameters of a periodic क्रमce-feedback effect
 * @strong_magnitude: magnitude of the heavy motor
 * @weak_magnitude: magnitude of the light one
 *
 * Some rumble pads have two motors of dअगरferent weight. Strong_magnitude
 * represents the magnitude of the vibration generated by the heavy one.
 */
काष्ठा ff_rumble_effect अणु
	__u16 strong_magnitude;
	__u16 weak_magnitude;
पूर्ण;

/**
 * काष्ठा ff_effect - defines क्रमce feedback effect
 * @type: type of the effect (FF_CONSTANT, FF_PERIODIC, FF_RAMP, FF_SPRING,
 *	FF_FRICTION, FF_DAMPER, FF_RUMBLE, FF_INERTIA, or FF_CUSTOM)
 * @id: an unique id asचिन्हित to an effect
 * @direction: direction of the effect
 * @trigger: trigger conditions (काष्ठा ff_trigger)
 * @replay: scheduling of the effect (काष्ठा ff_replay)
 * @u: effect-specअगरic काष्ठाure (one of ff_स्थिरant_effect, ff_ramp_effect,
 *	ff_periodic_effect, ff_condition_effect, ff_rumble_effect) further
 *	defining effect parameters
 *
 * This काष्ठाure is sent through ioctl from the application to the driver.
 * To create a new effect application should set its @id to -1; the kernel
 * will वापस asचिन्हित @id which can later be used to update or delete
 * this effect.
 *
 * Direction of the effect is encoded as follows:
 *	0 deg -> 0x0000 (करोwn)
 *	90 deg -> 0x4000 (left)
 *	180 deg -> 0x8000 (up)
 *	270 deg -> 0xC000 (right)
 */
काष्ठा ff_effect अणु
	__u16 type;
	__s16 id;
	__u16 direction;
	काष्ठा ff_trigger trigger;
	काष्ठा ff_replay replay;

	जोड़ अणु
		काष्ठा ff_स्थिरant_effect स्थिरant;
		काष्ठा ff_ramp_effect ramp;
		काष्ठा ff_periodic_effect periodic;
		काष्ठा ff_condition_effect condition[2]; /* One क्रम each axis */
		काष्ठा ff_rumble_effect rumble;
	पूर्ण u;
पूर्ण;

/*
 * Force feedback effect types
 */

#घोषणा FF_RUMBLE	0x50
#घोषणा FF_PERIODIC	0x51
#घोषणा FF_CONSTANT	0x52
#घोषणा FF_SPRING	0x53
#घोषणा FF_FRICTION	0x54
#घोषणा FF_DAMPER	0x55
#घोषणा FF_INERTIA	0x56
#घोषणा FF_RAMP		0x57

#घोषणा FF_EFFECT_MIN	FF_RUMBLE
#घोषणा FF_EFFECT_MAX	FF_RAMP

/*
 * Force feedback periodic effect types
 */

#घोषणा FF_SQUARE	0x58
#घोषणा FF_TRIANGLE	0x59
#घोषणा FF_SINE		0x5a
#घोषणा FF_SAW_UP	0x5b
#घोषणा FF_SAW_DOWN	0x5c
#घोषणा FF_CUSTOM	0x5d

#घोषणा FF_WAVEFORM_MIN	FF_SQUARE
#घोषणा FF_WAVEFORM_MAX	FF_CUSTOM

/*
 * Set ff device properties
 */

#घोषणा FF_GAIN		0x60
#घोषणा FF_AUTOCENTER	0x61

/*
 * ff->playback(effect_id = FF_GAIN) is the first effect_id to
 * cause a collision with another ff method, in this हाल ff->set_gain().
 * Thereक्रमe the greatest safe value क्रम effect_id is FF_GAIN - 1,
 * and thus the total number of effects should never exceed FF_GAIN.
 */
#घोषणा FF_MAX_EFFECTS	FF_GAIN

#घोषणा FF_MAX		0x7f
#घोषणा FF_CNT		(FF_MAX+1)

#पूर्ण_अगर /* _UAPI_INPUT_H */
