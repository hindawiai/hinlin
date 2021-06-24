<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * lib/bust_spinlocks.c
 *
 * Provides a minimal bust_spinlocks क्रम architectures which करोn't
 * have one of their own.
 *
 * bust_spinlocks() clears any spinlocks which would prevent oops, die(), BUG()
 * and panic() inक्रमmation from reaching the user.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/tty.h>
#समावेश <linux/रुको.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/console.h>

व्योम bust_spinlocks(पूर्णांक yes)
अणु
	अगर (yes) अणु
		++oops_in_progress;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_VT
		unblank_screen();
#पूर्ण_अगर
		console_unblank();
		अगर (--oops_in_progress == 0)
			wake_up_klogd();
	पूर्ण
पूर्ण
