<शैली गुरु>
/*
 * Platक्रमm specअगरic functions
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of
 * this archive क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_PLATFORM_H
#घोषणा _XTENSA_PLATFORM_H

#समावेश <linux/types.h>
#समावेश <यंत्र/bootparam.h>

/*
 * platक्रमm_init is called beक्रमe the mmu is initialized to give the
 * platक्रमm a early hook-up. bp_tag_t is a list of configuration tags
 * passed from the boot-loader.
 */
बाह्य व्योम platक्रमm_init(bp_tag_t*);

/*
 * platक्रमm_setup is called from setup_arch with a poपूर्णांकer to the command-line
 * string.
 */
बाह्य व्योम platक्रमm_setup (अक्षर **);

/*
 * platक्रमm_restart is called to restart the प्रणाली.
 */
बाह्य व्योम platक्रमm_restart (व्योम);

/*
 * platक्रमm_halt is called to stop the प्रणाली and halt.
 */
बाह्य व्योम platक्रमm_halt (व्योम);

/*
 * platक्रमm_घातer_off is called to stop the प्रणाली and घातer it off.
 */
बाह्य व्योम platक्रमm_घातer_off (व्योम);

/*
 * platक्रमm_idle is called from the idle function.
 */
बाह्य व्योम platक्रमm_idle (व्योम);

/*
 * platक्रमm_heartbeat is called every HZ
 */
बाह्य व्योम platक्रमm_heartbeat (व्योम);

/*
 * platक्रमm_calibrate_ccount calibrates cpu घड़ी freq (CONFIG_XTENSA_CALIBRATE)
 */
बाह्य व्योम platक्रमm_calibrate_ccount (व्योम);

/*
 * Flush and reset the mmu, simulate a processor reset, and
 * jump to the reset vector.
 */
व्योम cpu_reset(व्योम) __attribute__((noवापस));

#पूर्ण_अगर	/* _XTENSA_PLATFORM_H */
