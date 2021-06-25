<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम talking to the PMU.  The PMU is a microcontroller
 * which controls battery अक्षरging and प्रणाली घातer on PowerBook 3400
 * and 2400 models as well as the RTC and various other things.
 *
 * Copyright (C) 1998 Paul Mackerras.
 */
#अगर_अघोषित _LINUX_PMU_H
#घोषणा _LINUX_PMU_H

#समावेश <linux/rtc.h>
#समावेश <uapi/linux/pmu.h>


बाह्य पूर्णांक find_via_pmu(व्योम);

बाह्य पूर्णांक pmu_request(काष्ठा adb_request *req,
		व्योम (*करोne)(काष्ठा adb_request *), पूर्णांक nbytes, ...);
बाह्य पूर्णांक pmu_queue_request(काष्ठा adb_request *req);
बाह्य व्योम pmu_poll(व्योम);
बाह्य व्योम pmu_poll_adb(व्योम); /* For use by xmon */
बाह्य व्योम pmu_रुको_complete(काष्ठा adb_request *req);

/* For use beक्रमe चयनing पूर्णांकerrupts off क्रम a दीर्घ समय;
 * warning: not stackable
 */
#अगर defined(CONFIG_ADB_PMU)
बाह्य व्योम pmu_suspend(व्योम);
बाह्य व्योम pmu_resume(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pmu_suspend(व्योम)
अणुपूर्ण
अटल अंतरभूत व्योम pmu_resume(व्योम)
अणुपूर्ण
#पूर्ण_अगर

बाह्य व्योम pmu_enable_irled(पूर्णांक on);

बाह्य समय64_t pmu_get_समय(व्योम);
बाह्य पूर्णांक pmu_set_rtc_समय(काष्ठा rtc_समय *पंचांग);

बाह्य व्योम pmu_restart(व्योम);
बाह्य व्योम pmu_shutकरोwn(व्योम);
बाह्य व्योम pmu_unlock(व्योम);

बाह्य पूर्णांक pmu_present(व्योम);
बाह्य पूर्णांक pmu_get_model(व्योम);

बाह्य व्योम pmu_backlight_set_sleep(पूर्णांक sleep);

#घोषणा PMU_MAX_BATTERIES	2

/* values क्रम pmu_घातer_flags */
#घोषणा PMU_PWR_AC_PRESENT	0x00000001

/* values क्रम pmu_battery_info.flags */
#घोषणा PMU_BATT_PRESENT	0x00000001
#घोषणा PMU_BATT_CHARGING	0x00000002
#घोषणा PMU_BATT_TYPE_MASK	0x000000f0
#घोषणा PMU_BATT_TYPE_SMART	0x00000010 /* Smart battery */
#घोषणा PMU_BATT_TYPE_HOOPER	0x00000020 /* 3400/3500 */
#घोषणा PMU_BATT_TYPE_COMET	0x00000030 /* 2400 */

काष्ठा pmu_battery_info
अणु
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	अक्षरge;		/* current अक्षरge */
	अचिन्हित पूर्णांक	max_अक्षरge;	/* maximum अक्षरge */
	चिन्हित पूर्णांक	amperage;	/* current, positive अगर अक्षरging */
	अचिन्हित पूर्णांक	voltage;	/* voltage */
	अचिन्हित पूर्णांक	समय_reमुख्यing;	/* reमुख्यing समय */
पूर्ण;

बाह्य पूर्णांक pmu_battery_count;
बाह्य काष्ठा pmu_battery_info pmu_batteries[PMU_MAX_BATTERIES];
बाह्य अचिन्हित पूर्णांक pmu_घातer_flags;

/* Backlight */
बाह्य व्योम pmu_backlight_init(व्योम);

/* some code needs to know अगर the PMU was suspended क्रम hibernation */
#अगर defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
बाह्य पूर्णांक pmu_sys_suspended;
#अन्यथा
/* अगर घातer management is not configured it can't be suspended */
#घोषणा pmu_sys_suspended	0
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_PMU_H */
