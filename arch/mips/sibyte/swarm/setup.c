<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000, 2001, 2002, 2003, 2004 Broadcom Corporation
 * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)
 */

/*
 * Setup code क्रम the SWARM board
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/initrd.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/sibyte/sb1250.h>
#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#या_अगर defined(CONFIG_SIBYTE_SB1250) || defined(CONFIG_SIBYTE_BCM112X)
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#अन्यथा
#त्रुटि invalid SiByte board configuration
#पूर्ण_अगर
#समावेश <यंत्र/sibyte/sb1250_genbus.h>
#समावेश <यंत्र/sibyte/board.h>

#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
बाह्य व्योम bcm1480_setup(व्योम);
#या_अगर defined(CONFIG_SIBYTE_SB1250) || defined(CONFIG_SIBYTE_BCM112X)
बाह्य व्योम sb1250_setup(व्योम);
#अन्यथा
#त्रुटि invalid SiByte board configuration
#पूर्ण_अगर

बाह्य पूर्णांक xicor_probe(व्योम);
बाह्य पूर्णांक xicor_set_समय(समय64_t);
बाह्य समय64_t xicor_get_समय(व्योम);

बाह्य पूर्णांक m41t81_probe(व्योम);
बाह्य पूर्णांक m41t81_set_समय(समय64_t);
बाह्य समय64_t m41t81_get_समय(व्योम);

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "SiByte " SIBYTE_BOARD_NAME;
पूर्ण

पूर्णांक swarm_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	अगर (!is_fixup && (regs->cp0_cause & 4)) अणु
		/* Data bus error - prपूर्णांक PA */
		prपूर्णांकk("DBE physical address: %010Lx\n",
		       __पढ़ो_64bit_c0_रेजिस्टर($26, 1));
	पूर्ण
	वापस is_fixup ? MIPS_BE_FIXUP : MIPS_BE_FATAL;
पूर्ण

क्रमागत swarm_rtc_type अणु
	RTC_NONE,
	RTC_XICOR,
	RTC_M41T81,
पूर्ण;

क्रमागत swarm_rtc_type swarm_rtc_type;

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	समय64_t sec;

	चयन (swarm_rtc_type) अणु
	हाल RTC_XICOR:
		sec = xicor_get_समय();
		अवरोध;

	हाल RTC_M41T81:
		sec = m41t81_get_समय();
		अवरोध;

	हाल RTC_NONE:
	शेष:
		sec = स_गढ़ो64(2000, 1, 1, 0, 0, 0);
		अवरोध;
	पूर्ण
	ts->tv_sec = sec;
	ts->tv_nsec = 0;
पूर्ण

पूर्णांक update_persistent_घड़ी64(काष्ठा बारpec64 now)
अणु
	समय64_t sec = now.tv_sec;

	चयन (swarm_rtc_type) अणु
	हाल RTC_XICOR:
		वापस xicor_set_समय(sec);

	हाल RTC_M41T81:
		वापस m41t81_set_समय(sec);

	हाल RTC_NONE:
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
	bcm1480_setup();
#या_अगर defined(CONFIG_SIBYTE_SB1250) || defined(CONFIG_SIBYTE_BCM112X)
	sb1250_setup();
#अन्यथा
#त्रुटि invalid SiByte board configuration
#पूर्ण_अगर

	board_be_handler = swarm_be_handler;

	अगर (xicor_probe())
		swarm_rtc_type = RTC_XICOR;
	अगर (m41t81_probe())
		swarm_rtc_type = RTC_M41T81;

#अगर_घोषित CONFIG_VT
	screen_info = (काष्ठा screen_info) अणु
		.orig_video_page	= 52,
		.orig_video_mode	= 3,
		.orig_video_cols	= 80,
		.flags			= 12,
		.orig_video_ega_bx	= 3,
		.orig_video_lines	= 25,
		.orig_video_isVGA	= 0x22,
		.orig_video_poपूर्णांकs	= 16,
       पूर्ण;
       /* XXXKW क्रम CFE, get lines/cols from environment */
#पूर्ण_अगर
पूर्ण

#अगर_घोषित LEDS_PHYS

#अगर_घोषित CONFIG_SIBYTE_CARMEL
/* XXXKW need to detect Monterey/LittleSur/etc */
#अघोषित LEDS_PHYS
#घोषणा LEDS_PHYS MLEDS_PHYS
#पूर्ण_अगर

व्योम setleds(अक्षर *str)
अणु
	व्योम *reg;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		reg = IOADDR(LEDS_PHYS) + 0x20 + ((3 - i) << 3);

		अगर (!str[i])
			ग_लिखोb(' ', reg);
		अन्यथा
			ग_लिखोb(str[i], reg);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* LEDS_PHYS */
