<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __VDSO_CLOCKSOURCE_H
#घोषणा __VDSO_CLOCKSOURCE_H

#समावेश <vdso/सीमा.स>

#अगर_घोषित CONFIG_GENERIC_GETTIMखातापूर्णDAY
#समावेश <यंत्र/vdso/घड़ीsource.h>
#पूर्ण_अगर /* CONFIG_GENERIC_GETTIMखातापूर्णDAY */

क्रमागत vdso_घड़ी_mode अणु
	VDSO_CLOCKMODE_NONE,
#अगर_घोषित CONFIG_GENERIC_GETTIMखातापूर्णDAY
	VDSO_ARCH_CLOCKMODES,
#पूर्ण_अगर
	VDSO_CLOCKMODE_MAX,

	/* Indicator क्रम समय namespace VDSO */
	VDSO_CLOCKMODE_TIMENS = पूर्णांक_उच्च
पूर्ण;

#पूर्ण_अगर /* __VDSO_CLOCKSOURCE_H */
