<शैली गुरु>
/*
 * PXA250/210 Power Management Routines
 *
 * Original code क्रम the SA11x0:
 * Copyright (c) 2001 Clअगरf Brake <cbrake@accelent.com>
 *
 * Modअगरied क्रम the PXA250 by Nicolas Pitre:
 * Copyright (c) 2002 Monta Vista Software, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/suspend.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश "pm.h"

काष्ठा pxa_cpu_pm_fns *pxa_cpu_pm_fns;
अटल अचिन्हित दीर्घ *sleep_save;

पूर्णांक pxa_pm_enter(suspend_state_t state)
अणु
	अचिन्हित दीर्घ sleep_save_checksum = 0, checksum = 0;
	पूर्णांक i;

#अगर_घोषित CONFIG_IWMMXT
	/* क्रमce any iWMMXt context to ram **/
	अगर (elf_hwcap & HWCAP_IWMMXT)
		iwmmxt_task_disable(शून्य);
#पूर्ण_अगर

	/* skip रेजिस्टरs saving क्रम standby */
	अगर (state != PM_SUSPEND_STANDBY && pxa_cpu_pm_fns->save) अणु
		pxa_cpu_pm_fns->save(sleep_save);
		/* beक्रमe sleeping, calculate and save a checksum */
		क्रम (i = 0; i < pxa_cpu_pm_fns->save_count - 1; i++)
			sleep_save_checksum += sleep_save[i];
	पूर्ण

	/* *** go zzz *** */
	pxa_cpu_pm_fns->enter(state);

	अगर (state != PM_SUSPEND_STANDBY && pxa_cpu_pm_fns->restore) अणु
		/* after sleeping, validate the checksum */
		क्रम (i = 0; i < pxa_cpu_pm_fns->save_count - 1; i++)
			checksum += sleep_save[i];

		/* अगर invalid, display message and रुको क्रम a hardware reset */
		अगर (checksum != sleep_save_checksum) अणु

			lubbock_set_hexled(0xbadbadc5);

			जबतक (1)
				pxa_cpu_pm_fns->enter(state);
		पूर्ण
		pxa_cpu_pm_fns->restore(sleep_save);
	पूर्ण

	pr_debug("*** made it back from resume\n");

	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(pxa_pm_enter);

अटल पूर्णांक pxa_pm_valid(suspend_state_t state)
अणु
	अगर (pxa_cpu_pm_fns)
		वापस pxa_cpu_pm_fns->valid(state);

	वापस -EINVAL;
पूर्ण

पूर्णांक pxa_pm_prepare(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (pxa_cpu_pm_fns && pxa_cpu_pm_fns->prepare)
		ret = pxa_cpu_pm_fns->prepare();

	वापस ret;
पूर्ण

व्योम pxa_pm_finish(व्योम)
अणु
	अगर (pxa_cpu_pm_fns && pxa_cpu_pm_fns->finish)
		pxa_cpu_pm_fns->finish();
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops pxa_pm_ops = अणु
	.valid		= pxa_pm_valid,
	.enter		= pxa_pm_enter,
	.prepare	= pxa_pm_prepare,
	.finish		= pxa_pm_finish,
पूर्ण;

अटल पूर्णांक __init pxa_pm_init(व्योम)
अणु
	अगर (!pxa_cpu_pm_fns) अणु
		prपूर्णांकk(KERN_ERR "no valid pxa_cpu_pm_fns defined\n");
		वापस -EINVAL;
	पूर्ण

	sleep_save = kदो_स्मृति_array(pxa_cpu_pm_fns->save_count,
				   माप(*sleep_save),
				   GFP_KERNEL);
	अगर (!sleep_save)
		वापस -ENOMEM;

	suspend_set_ops(&pxa_pm_ops);
	वापस 0;
पूर्ण

device_initcall(pxa_pm_init);
