<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Force feedback support क्रम Linux input subप्रणाली
 *
 *  Copyright (c) 2006 Anssi Hannula <anssi.hannula@gmail.com>
 *  Copyright (c) 2006 Dmitry Torokhov <dtor@mail.ru>
 */

/*
 */

/* #घोषणा DEBUG */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

/*
 * Check that the effect_id is a valid effect and whether the user
 * is the owner
 */
अटल पूर्णांक check_effect_access(काष्ठा ff_device *ff, पूर्णांक effect_id,
				काष्ठा file *file)
अणु
	अगर (effect_id < 0 || effect_id >= ff->max_effects ||
	    !ff->effect_owners[effect_id])
		वापस -EINVAL;

	अगर (file && ff->effect_owners[effect_id] != file)
		वापस -EACCES;

	वापस 0;
पूर्ण

/*
 * Checks whether 2 effects can be combined together
 */
अटल अंतरभूत पूर्णांक check_effects_compatible(काष्ठा ff_effect *e1,
					   काष्ठा ff_effect *e2)
अणु
	वापस e1->type == e2->type &&
	       (e1->type != FF_PERIODIC ||
		e1->u.periodic.waveक्रमm == e2->u.periodic.waveक्रमm);
पूर्ण

/*
 * Convert an effect पूर्णांकo compatible one
 */
अटल पूर्णांक compat_effect(काष्ठा ff_device *ff, काष्ठा ff_effect *effect)
अणु
	पूर्णांक magnitude;

	चयन (effect->type) अणु
	हाल FF_RUMBLE:
		अगर (!test_bit(FF_PERIODIC, ff->ffbit))
			वापस -EINVAL;

		/*
		 * calculate magnitude of sine wave as average of rumble's
		 * 2/3 of strong magnitude and 1/3 of weak magnitude
		 */
		magnitude = effect->u.rumble.strong_magnitude / 3 +
			    effect->u.rumble.weak_magnitude / 6;

		effect->type = FF_PERIODIC;
		effect->u.periodic.waveक्रमm = FF_SINE;
		effect->u.periodic.period = 50;
		effect->u.periodic.magnitude = max(magnitude, 0x7fff);
		effect->u.periodic.offset = 0;
		effect->u.periodic.phase = 0;
		effect->u.periodic.envelope.attack_length = 0;
		effect->u.periodic.envelope.attack_level = 0;
		effect->u.periodic.envelope.fade_length = 0;
		effect->u.periodic.envelope.fade_level = 0;

		वापस 0;

	शेष:
		/* Let driver handle conversion */
		वापस 0;
	पूर्ण
पूर्ण

/**
 * input_ff_upload() - upload effect पूर्णांकo क्रमce-feedback device
 * @dev: input device
 * @effect: effect to be uploaded
 * @file: owner of the effect
 */
पूर्णांक input_ff_upload(काष्ठा input_dev *dev, काष्ठा ff_effect *effect,
		    काष्ठा file *file)
अणु
	काष्ठा ff_device *ff = dev->ff;
	काष्ठा ff_effect *old;
	पूर्णांक ret = 0;
	पूर्णांक id;

	अगर (!test_bit(EV_FF, dev->evbit))
		वापस -ENOSYS;

	अगर (effect->type < FF_EFFECT_MIN || effect->type > FF_EFFECT_MAX ||
	    !test_bit(effect->type, dev->ffbit)) अणु
		dev_dbg(&dev->dev, "invalid or not supported effect type in upload\n");
		वापस -EINVAL;
	पूर्ण

	अगर (effect->type == FF_PERIODIC &&
	    (effect->u.periodic.waveक्रमm < FF_WAVEFORM_MIN ||
	     effect->u.periodic.waveक्रमm > FF_WAVEFORM_MAX ||
	     !test_bit(effect->u.periodic.waveक्रमm, dev->ffbit))) अणु
		dev_dbg(&dev->dev, "invalid or not supported wave form in upload\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!test_bit(effect->type, ff->ffbit)) अणु
		ret = compat_effect(ff, effect);
		अगर (ret)
			वापस ret;
	पूर्ण

	mutex_lock(&ff->mutex);

	अगर (effect->id == -1) अणु
		क्रम (id = 0; id < ff->max_effects; id++)
			अगर (!ff->effect_owners[id])
				अवरोध;

		अगर (id >= ff->max_effects) अणु
			ret = -ENOSPC;
			जाओ out;
		पूर्ण

		effect->id = id;
		old = शून्य;

	पूर्ण अन्यथा अणु
		id = effect->id;

		ret = check_effect_access(ff, id, file);
		अगर (ret)
			जाओ out;

		old = &ff->effects[id];

		अगर (!check_effects_compatible(effect, old)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ff->upload(dev, effect, old);
	अगर (ret)
		जाओ out;

	spin_lock_irq(&dev->event_lock);
	ff->effects[id] = *effect;
	ff->effect_owners[id] = file;
	spin_unlock_irq(&dev->event_lock);

 out:
	mutex_unlock(&ff->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(input_ff_upload);

/*
 * Erases the effect अगर the requester is also the effect owner. The mutex
 * should alपढ़ोy be locked beक्रमe calling this function.
 */
अटल पूर्णांक erase_effect(काष्ठा input_dev *dev, पूर्णांक effect_id,
			काष्ठा file *file)
अणु
	काष्ठा ff_device *ff = dev->ff;
	पूर्णांक error;

	error = check_effect_access(ff, effect_id, file);
	अगर (error)
		वापस error;

	spin_lock_irq(&dev->event_lock);
	ff->playback(dev, effect_id, 0);
	ff->effect_owners[effect_id] = शून्य;
	spin_unlock_irq(&dev->event_lock);

	अगर (ff->erase) अणु
		error = ff->erase(dev, effect_id);
		अगर (error) अणु
			spin_lock_irq(&dev->event_lock);
			ff->effect_owners[effect_id] = file;
			spin_unlock_irq(&dev->event_lock);

			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * input_ff_erase - erase a क्रमce-feedback effect from device
 * @dev: input device to erase effect from
 * @effect_id: id of the effect to be erased
 * @file: purported owner of the request
 *
 * This function erases a क्रमce-feedback effect from specअगरied device.
 * The effect will only be erased अगर it was uploaded through the same
 * file handle that is requesting erase.
 */
पूर्णांक input_ff_erase(काष्ठा input_dev *dev, पूर्णांक effect_id, काष्ठा file *file)
अणु
	काष्ठा ff_device *ff = dev->ff;
	पूर्णांक ret;

	अगर (!test_bit(EV_FF, dev->evbit))
		वापस -ENOSYS;

	mutex_lock(&ff->mutex);
	ret = erase_effect(dev, effect_id, file);
	mutex_unlock(&ff->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(input_ff_erase);

/*
 * input_ff_flush - erase all effects owned by a file handle
 * @dev: input device to erase effect from
 * @file: purported owner of the effects
 *
 * This function erases all क्रमce-feedback effects associated with
 * the given owner from specअगरied device. Note that @file may be %शून्य,
 * in which हाल all effects will be erased.
 */
पूर्णांक input_ff_flush(काष्ठा input_dev *dev, काष्ठा file *file)
अणु
	काष्ठा ff_device *ff = dev->ff;
	पूर्णांक i;

	dev_dbg(&dev->dev, "flushing now\n");

	mutex_lock(&ff->mutex);

	क्रम (i = 0; i < ff->max_effects; i++)
		erase_effect(dev, i, file);

	mutex_unlock(&ff->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(input_ff_flush);

/**
 * input_ff_event() - generic handler क्रम क्रमce-feedback events
 * @dev: input device to send the effect to
 * @type: event type (anything but EV_FF is ignored)
 * @code: event code
 * @value: event value
 */
पूर्णांक input_ff_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
		   अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा ff_device *ff = dev->ff;

	अगर (type != EV_FF)
		वापस 0;

	चयन (code) अणु
	हाल FF_GAIN:
		अगर (!test_bit(FF_GAIN, dev->ffbit) || value > 0xffffU)
			अवरोध;

		ff->set_gain(dev, value);
		अवरोध;

	हाल FF_AUTOCENTER:
		अगर (!test_bit(FF_AUTOCENTER, dev->ffbit) || value > 0xffffU)
			अवरोध;

		ff->set_स्वतःcenter(dev, value);
		अवरोध;

	शेष:
		अगर (check_effect_access(ff, code, शून्य) == 0)
			ff->playback(dev, code, value);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(input_ff_event);

/**
 * input_ff_create() - create क्रमce-feedback device
 * @dev: input device supporting क्रमce-feedback
 * @max_effects: maximum number of effects supported by the device
 *
 * This function allocates all necessary memory क्रम a क्रमce feedback
 * portion of an input device and installs all शेष handlers.
 * @dev->ffbit should be alपढ़ोy set up beक्रमe calling this function.
 * Once ff device is created you need to setup its upload, erase,
 * playback and other handlers beक्रमe रेजिस्टरing input device
 */
पूर्णांक input_ff_create(काष्ठा input_dev *dev, अचिन्हित पूर्णांक max_effects)
अणु
	काष्ठा ff_device *ff;
	माप_प्रकार ff_dev_size;
	पूर्णांक i;

	अगर (!max_effects) अणु
		dev_err(&dev->dev, "cannot allocate device without any effects\n");
		वापस -EINVAL;
	पूर्ण

	अगर (max_effects > FF_MAX_EFFECTS) अणु
		dev_err(&dev->dev, "cannot allocate more than FF_MAX_EFFECTS effects\n");
		वापस -EINVAL;
	पूर्ण

	ff_dev_size = माप(काष्ठा ff_device) +
				max_effects * माप(काष्ठा file *);
	अगर (ff_dev_size < max_effects) /* overflow */
		वापस -EINVAL;

	ff = kzalloc(ff_dev_size, GFP_KERNEL);
	अगर (!ff)
		वापस -ENOMEM;

	ff->effects = kसुस्मृति(max_effects, माप(काष्ठा ff_effect),
			      GFP_KERNEL);
	अगर (!ff->effects) अणु
		kमुक्त(ff);
		वापस -ENOMEM;
	पूर्ण

	ff->max_effects = max_effects;
	mutex_init(&ff->mutex);

	dev->ff = ff;
	dev->flush = input_ff_flush;
	dev->event = input_ff_event;
	__set_bit(EV_FF, dev->evbit);

	/* Copy "true" bits पूर्णांकo ff device biपंचांगap */
	क्रम_each_set_bit(i, dev->ffbit, FF_CNT)
		__set_bit(i, ff->ffbit);

	/* we can emulate RUMBLE with periodic effects */
	अगर (test_bit(FF_PERIODIC, ff->ffbit))
		__set_bit(FF_RUMBLE, dev->ffbit);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(input_ff_create);

/**
 * input_ff_destroy() - मुक्तs क्रमce feedback portion of input device
 * @dev: input device supporting क्रमce feedback
 *
 * This function is only needed in error path as input core will
 * स्वतःmatically मुक्त क्रमce feedback काष्ठाures when device is
 * destroyed.
 */
व्योम input_ff_destroy(काष्ठा input_dev *dev)
अणु
	काष्ठा ff_device *ff = dev->ff;

	__clear_bit(EV_FF, dev->evbit);
	अगर (ff) अणु
		अगर (ff->destroy)
			ff->destroy(ff);
		kमुक्त(ff->निजी);
		kमुक्त(ff->effects);
		kमुक्त(ff);
		dev->ff = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(input_ff_destroy);
