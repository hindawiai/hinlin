<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Platक्रमm profile sysfs पूर्णांकerface
 *
 * See Documentation/ABI/testing/sysfs-platक्रमm_profile.rst क्रम more
 * inक्रमmation.
 */

#अगर_अघोषित _PLATFORM_PROखाता_H_
#घोषणा _PLATFORM_PROखाता_H_

#समावेश <linux/bitops.h>

/*
 * If more options are added please update profile_names array in
 * platक्रमm_profile.c and sysfs-platक्रमm_profile करोcumentation.
 */

क्रमागत platक्रमm_profile_option अणु
	PLATFORM_PROखाता_LOW_POWER,
	PLATFORM_PROखाता_COOL,
	PLATFORM_PROखाता_QUIET,
	PLATFORM_PROखाता_BALANCED,
	PLATFORM_PROखाता_BALANCED_PERFORMANCE,
	PLATFORM_PROखाता_PERFORMANCE,
	PLATFORM_PROखाता_LAST, /*must always be last */
पूर्ण;

काष्ठा platक्रमm_profile_handler अणु
	अचिन्हित दीर्घ choices[BITS_TO_LONGS(PLATFORM_PROखाता_LAST)];
	पूर्णांक (*profile_get)(काष्ठा platक्रमm_profile_handler *pprof,
				क्रमागत platक्रमm_profile_option *profile);
	पूर्णांक (*profile_set)(काष्ठा platक्रमm_profile_handler *pprof,
				क्रमागत platक्रमm_profile_option profile);
पूर्ण;

पूर्णांक platक्रमm_profile_रेजिस्टर(काष्ठा platक्रमm_profile_handler *pprof);
पूर्णांक platक्रमm_profile_हटाओ(व्योम);
व्योम platक्रमm_profile_notअगरy(व्योम);

#पूर्ण_अगर  /*_PLATFORM_PROखाता_H_*/
