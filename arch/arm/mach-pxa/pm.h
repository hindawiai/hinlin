<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005 Riअक्षरd Purdie
 */

#समावेश <linux/suspend.h>

काष्ठा pxa_cpu_pm_fns अणु
	पूर्णांक	save_count;
	व्योम	(*save)(अचिन्हित दीर्घ *);
	व्योम	(*restore)(अचिन्हित दीर्घ *);
	पूर्णांक	(*valid)(suspend_state_t state);
	व्योम	(*enter)(suspend_state_t state);
	पूर्णांक	(*prepare)(व्योम);
	व्योम	(*finish)(व्योम);
पूर्ण;

बाह्य काष्ठा pxa_cpu_pm_fns *pxa_cpu_pm_fns;

/* sleep.S */
बाह्य पूर्णांक pxa25x_finish_suspend(अचिन्हित दीर्घ);
बाह्य पूर्णांक pxa27x_finish_suspend(अचिन्हित दीर्घ);

बाह्य पूर्णांक pxa_pm_enter(suspend_state_t state);
बाह्य पूर्णांक pxa_pm_prepare(व्योम);
बाह्य व्योम pxa_pm_finish(व्योम);

बाह्य स्थिर अक्षर pm_enter_standby_start[], pm_enter_standby_end[];
बाह्य पूर्णांक pxa3xx_finish_suspend(अचिन्हित दीर्घ);

/* NOTE: this is क्रम PM debugging on Lubbock,  it's really a big
 * ugly, but let's keep the crap minimum here, instead of direct
 * accessing the LUBBOCK CPLD रेजिस्टरs in arch/arm/mach-pxa/pm.c
 */
#अगर_घोषित CONFIG_ARCH_LUBBOCK
बाह्य व्योम lubbock_set_hexled(uपूर्णांक32_t value);
#अन्यथा
#घोषणा lubbock_set_hexled(x)
#पूर्ण_अगर
