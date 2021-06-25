<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_घोषित CONFIG_MMU
#समावेश "setup_mm.c"
#अन्यथा
#समावेश "setup_no.c"
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_INPUT_M68K_BEEP)
व्योम (*mach_beep)(अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
EXPORT_SYMBOL(mach_beep);
#पूर्ण_अगर
