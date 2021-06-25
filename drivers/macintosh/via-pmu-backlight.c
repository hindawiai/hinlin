<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Backlight code क्रम via-pmu
 *
 * Copyright (C) 1998 Paul Mackerras and Fabio Riccardi.
 * Copyright (C) 2001-2002 Benjamin Herrenschmidt
 * Copyright (C) 2006      Michael Hanselmann <linux-kernel@hansmi.ch>
 *
 */

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <यंत्र/backlight.h>
#समावेश <यंत्र/prom.h>

#घोषणा MAX_PMU_LEVEL 0xFF

अटल स्थिर काष्ठा backlight_ops pmu_backlight_data;
अटल DEFINE_SPINLOCK(pmu_backlight_lock);
अटल पूर्णांक sleeping, uses_pmu_bl;
अटल u8 bl_curve[FB_BACKLIGHT_LEVELS];

अटल व्योम pmu_backlight_init_curve(u8 off, u8 min, u8 max)
अणु
	पूर्णांक i, flat, count, range = (max - min);

	bl_curve[0] = off;

	क्रम (flat = 1; flat < (FB_BACKLIGHT_LEVELS / 16); ++flat)
		bl_curve[flat] = min;

	count = FB_BACKLIGHT_LEVELS * 15 / 16;
	क्रम (i = 0; i < count; ++i)
		bl_curve[flat + i] = min + (range * (i + 1) / count);
पूर्ण

अटल पूर्णांक pmu_backlight_curve_lookup(पूर्णांक value)
अणु
	पूर्णांक level = (FB_BACKLIGHT_LEVELS - 1);
	पूर्णांक i, max = 0;

	/* Look क्रम biggest value */
	क्रम (i = 0; i < FB_BACKLIGHT_LEVELS; i++)
		max = max((पूर्णांक)bl_curve[i], max);

	/* Look क्रम nearest value */
	क्रम (i = 0; i < FB_BACKLIGHT_LEVELS; i++) अणु
		पूर्णांक dअगरf = असल(bl_curve[i] - value);
		अगर (dअगरf < max) अणु
			max = dअगरf;
			level = i;
		पूर्ण
	पूर्ण
	वापस level;
पूर्ण

अटल पूर्णांक pmu_backlight_get_level_brightness(पूर्णांक level)
अणु
	पूर्णांक pmulevel;

	/* Get and convert the value */
	pmulevel = bl_curve[level] * FB_BACKLIGHT_MAX / MAX_PMU_LEVEL;
	अगर (pmulevel < 0)
		pmulevel = 0;
	अन्यथा अगर (pmulevel > MAX_PMU_LEVEL)
		pmulevel = MAX_PMU_LEVEL;

	वापस pmulevel;
पूर्ण

अटल पूर्णांक __pmu_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा adb_request req;
	पूर्णांक level = bd->props.brightness;


	अगर (bd->props.घातer != FB_BLANK_UNBLANK ||
	    bd->props.fb_blank != FB_BLANK_UNBLANK)
		level = 0;

	अगर (level > 0) अणु
		पूर्णांक pmulevel = pmu_backlight_get_level_brightness(level);

		pmu_request(&req, शून्य, 2, PMU_BACKLIGHT_BRIGHT, pmulevel);
		pmu_रुको_complete(&req);

		pmu_request(&req, शून्य, 2, PMU_POWER_CTRL,
			PMU_POW_BACKLIGHT | PMU_POW_ON);
		pmu_रुको_complete(&req);
	पूर्ण अन्यथा अणु
		pmu_request(&req, शून्य, 2, PMU_POWER_CTRL,
			PMU_POW_BACKLIGHT | PMU_POW_OFF);
		pmu_रुको_complete(&req);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pmu_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&pmu_backlight_lock, flags);
	/* Don't update brightness when sleeping */
	अगर (!sleeping)
		rc = __pmu_backlight_update_status(bd);
	spin_unlock_irqrestore(&pmu_backlight_lock, flags);
	वापस rc;
पूर्ण


अटल स्थिर काष्ठा backlight_ops pmu_backlight_data = अणु
	.update_status	= pmu_backlight_update_status,

पूर्ण;

#अगर_घोषित CONFIG_PM
व्योम pmu_backlight_set_sleep(पूर्णांक sleep)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pmu_backlight_lock, flags);
	sleeping = sleep;
	अगर (pmac_backlight && uses_pmu_bl) अणु
		अगर (sleep) अणु
			काष्ठा adb_request req;

			pmu_request(&req, शून्य, 2, PMU_POWER_CTRL,
				    PMU_POW_BACKLIGHT | PMU_POW_OFF);
			pmu_रुको_complete(&req);
		पूर्ण अन्यथा
			__pmu_backlight_update_status(pmac_backlight);
	पूर्ण
	spin_unlock_irqrestore(&pmu_backlight_lock, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

व्योम __init pmu_backlight_init(व्योम)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bd;
	अक्षर name[10];
	पूर्णांक level, स्वतःsave;

	/* Special हाल क्रम the old PowerBook since I can't test on it */
	स्वतःsave =
		of_machine_is_compatible("AAPL,3400/2400") ||
		of_machine_is_compatible("AAPL,3500");

	अगर (!स्वतःsave &&
	    !pmac_has_backlight_type("pmu") &&
	    !of_machine_is_compatible("AAPL,PowerBook1998") &&
	    !of_machine_is_compatible("PowerBook1,1"))
		वापस;

	snम_लिखो(name, माप(name), "pmubl");

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = FB_BACKLIGHT_LEVELS - 1;
	bd = backlight_device_रेजिस्टर(name, शून्य, शून्य, &pmu_backlight_data,
				       &props);
	अगर (IS_ERR(bd)) अणु
		prपूर्णांकk(KERN_ERR "PMU Backlight registration failed\n");
		वापस;
	पूर्ण
	uses_pmu_bl = 1;
	pmu_backlight_init_curve(0x7F, 0x46, 0x0E);

	level = bd->props.max_brightness;

	अगर (स्वतःsave) अणु
		/* पढ़ो स्वतःsaved value अगर available */
		काष्ठा adb_request req;
		pmu_request(&req, शून्य, 2, 0xd9, 0);
		pmu_रुको_complete(&req);

		level = pmu_backlight_curve_lookup(
				(req.reply[0] >> 4) *
				bd->props.max_brightness / 15);
	पूर्ण

	bd->props.brightness = level;
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	prपूर्णांकk(KERN_INFO "PMU Backlight initialized (%s)\n", name);
पूर्ण
