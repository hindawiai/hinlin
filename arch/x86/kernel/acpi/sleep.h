<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Variables and functions used by the code in sleep.c
 */

#समावेश <linux/linkage.h>

बाह्य अचिन्हित दीर्घ saved_video_mode;
बाह्य दीर्घ saved_magic;

बाह्य पूर्णांक wakeup_pmode_वापस;

बाह्य u8 wake_sleep_flags;

बाह्य अचिन्हित दीर्घ acpi_copy_wakeup_routine(अचिन्हित दीर्घ);
बाह्य व्योम wakeup_दीर्घ64(व्योम);

बाह्य व्योम करो_suspend_lowlevel(व्योम);

बाह्य पूर्णांक x86_acpi_suspend_lowlevel(व्योम);

यंत्रlinkage acpi_status x86_acpi_enter_sleep_state(u8 state);
