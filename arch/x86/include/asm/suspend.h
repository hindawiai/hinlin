<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित CONFIG_X86_32
# include <यंत्र/suspend_32.h>
#अन्यथा
# include <यंत्र/suspend_64.h>
#पूर्ण_अगर
बाह्य अचिन्हित दीर्घ restore_jump_address __visible;
बाह्य अचिन्हित दीर्घ jump_address_phys;
बाह्य अचिन्हित दीर्घ restore_cr3 __visible;
बाह्य अचिन्हित दीर्घ temp_pgt __visible;
बाह्य अचिन्हित दीर्घ relocated_restore_code __visible;
बाह्य पूर्णांक relocate_restore_code(व्योम);
/* Defined in hibernate_यंत्र_32/64.S */
बाह्य यंत्रlinkage __visible पूर्णांक restore_image(व्योम);
