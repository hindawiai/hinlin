<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Miscellaneous procedures क्रम dealing with the PowerMac hardware.
 * Contains support क्रम the backlight.
 *
 *   Copyright (C) 2000 Benjamin Herrenschmidt
 *   Copyright (C) 2006 Michael Hanselmann <linux-kernel@hansmi.ch>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/atomic.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/backlight.h>

#घोषणा OLD_BACKLIGHT_MAX 15

अटल व्योम pmac_backlight_key_worker(काष्ठा work_काष्ठा *work);
अटल व्योम pmac_backlight_set_legacy_worker(काष्ठा work_काष्ठा *work);

अटल DECLARE_WORK(pmac_backlight_key_work, pmac_backlight_key_worker);
अटल DECLARE_WORK(pmac_backlight_set_legacy_work, pmac_backlight_set_legacy_worker);

/* Although these variables are used in पूर्णांकerrupt context, it makes no sense to
 * protect them. No user is able to produce enough key events per second and
 * notice the errors that might happen.
 */
अटल पूर्णांक pmac_backlight_key_queued;
अटल पूर्णांक pmac_backlight_set_legacy_queued;

/* The via-pmu code allows the backlight to be grabbed, in which हाल the
 * in-kernel control of the brightness needs to be disabled. This should
 * only be used by really old PowerBooks.
 */
अटल atomic_t kernel_backlight_disabled = ATOMIC_INIT(0);

/* Protect the pmac_backlight variable below.
   You should hold this lock when using the pmac_backlight poपूर्णांकer to
   prevent its potential removal. */
DEFINE_MUTEX(pmac_backlight_mutex);

/* Main backlight storage
 *
 * Backlight drivers in this variable are required to have the "ops"
 * attribute set and to have an update_status function.
 *
 * We can only store one backlight here, but since Apple laptops have only one
 * पूर्णांकernal display, it करोesn't matter. Other backlight drivers can be used
 * independently.
 *
 */
काष्ठा backlight_device *pmac_backlight;

पूर्णांक pmac_has_backlight_type(स्थिर अक्षर *type)
अणु
	काष्ठा device_node* bk_node = of_find_node_by_name(शून्य, "backlight");

	अगर (bk_node) अणु
		स्थिर अक्षर *prop = of_get_property(bk_node,
				"backlight-control", शून्य);
		अगर (prop && म_भेदन(prop, type, म_माप(type)) == 0) अणु
			of_node_put(bk_node);
			वापस 1;
		पूर्ण
		of_node_put(bk_node);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pmac_backlight_curve_lookup(काष्ठा fb_info *info, पूर्णांक value)
अणु
	पूर्णांक level = (FB_BACKLIGHT_LEVELS - 1);

	अगर (info && info->bl_dev) अणु
		पूर्णांक i, max = 0;

		/* Look क्रम biggest value */
		क्रम (i = 0; i < FB_BACKLIGHT_LEVELS; i++)
			max = max((पूर्णांक)info->bl_curve[i], max);

		/* Look क्रम nearest value */
		क्रम (i = 0; i < FB_BACKLIGHT_LEVELS; i++) अणु
			पूर्णांक dअगरf = असल(info->bl_curve[i] - value);
			अगर (dअगरf < max) अणु
				max = dअगरf;
				level = i;
			पूर्ण
		पूर्ण

	पूर्ण

	वापस level;
पूर्ण

अटल व्योम pmac_backlight_key_worker(काष्ठा work_काष्ठा *work)
अणु
	अगर (atomic_पढ़ो(&kernel_backlight_disabled))
		वापस;

	mutex_lock(&pmac_backlight_mutex);
	अगर (pmac_backlight) अणु
		काष्ठा backlight_properties *props;
		पूर्णांक brightness;

		props = &pmac_backlight->props;

		brightness = props->brightness +
			((pmac_backlight_key_queued?-1:1) *
			 (props->max_brightness / 15));

		अगर (brightness < 0)
			brightness = 0;
		अन्यथा अगर (brightness > props->max_brightness)
			brightness = props->max_brightness;

		props->brightness = brightness;
		backlight_update_status(pmac_backlight);
	पूर्ण
	mutex_unlock(&pmac_backlight_mutex);
पूर्ण

/* This function is called in पूर्णांकerrupt context */
व्योम pmac_backlight_key(पूर्णांक direction)
अणु
	अगर (atomic_पढ़ो(&kernel_backlight_disabled))
		वापस;

	/* we can receive multiple पूर्णांकerrupts here, but the scheduled work
	 * will run only once, with the last value
	 */
	pmac_backlight_key_queued = direction;
	schedule_work(&pmac_backlight_key_work);
पूर्ण

अटल पूर्णांक __pmac_backlight_set_legacy_brightness(पूर्णांक brightness)
अणु
	पूर्णांक error = -ENXIO;

	mutex_lock(&pmac_backlight_mutex);
	अगर (pmac_backlight) अणु
		काष्ठा backlight_properties *props;

		props = &pmac_backlight->props;
		props->brightness = brightness *
			(props->max_brightness + 1) /
			(OLD_BACKLIGHT_MAX + 1);

		अगर (props->brightness > props->max_brightness)
			props->brightness = props->max_brightness;
		अन्यथा अगर (props->brightness < 0)
			props->brightness = 0;

		backlight_update_status(pmac_backlight);

		error = 0;
	पूर्ण
	mutex_unlock(&pmac_backlight_mutex);

	वापस error;
पूर्ण

अटल व्योम pmac_backlight_set_legacy_worker(काष्ठा work_काष्ठा *work)
अणु
	अगर (atomic_पढ़ो(&kernel_backlight_disabled))
		वापस;

	__pmac_backlight_set_legacy_brightness(pmac_backlight_set_legacy_queued);
पूर्ण

/* This function is called in पूर्णांकerrupt context */
व्योम pmac_backlight_set_legacy_brightness_pmu(पूर्णांक brightness) अणु
	अगर (atomic_पढ़ो(&kernel_backlight_disabled))
		वापस;

	pmac_backlight_set_legacy_queued = brightness;
	schedule_work(&pmac_backlight_set_legacy_work);
पूर्ण

पूर्णांक pmac_backlight_set_legacy_brightness(पूर्णांक brightness)
अणु
	वापस __pmac_backlight_set_legacy_brightness(brightness);
पूर्ण

पूर्णांक pmac_backlight_get_legacy_brightness(व्योम)
अणु
	पूर्णांक result = -ENXIO;

	mutex_lock(&pmac_backlight_mutex);
	अगर (pmac_backlight) अणु
		काष्ठा backlight_properties *props;

		props = &pmac_backlight->props;

		result = props->brightness *
			(OLD_BACKLIGHT_MAX + 1) /
			(props->max_brightness + 1);
	पूर्ण
	mutex_unlock(&pmac_backlight_mutex);

	वापस result;
पूर्ण

व्योम pmac_backlight_disable(व्योम)
अणु
	atomic_inc(&kernel_backlight_disabled);
पूर्ण

व्योम pmac_backlight_enable(व्योम)
अणु
	atomic_dec(&kernel_backlight_disabled);
पूर्ण

EXPORT_SYMBOL_GPL(pmac_backlight);
EXPORT_SYMBOL_GPL(pmac_backlight_mutex);
EXPORT_SYMBOL_GPL(pmac_has_backlight_type);
