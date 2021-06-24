<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_BIOS_H
#घोषणा __ASM_SH_BIOS_H

#अगर_घोषित CONFIG_SH_STANDARD_BIOS

/*
 * Copyright (C) 2000 Greg Banks, Mitch Davis
 * C API to पूर्णांकerface to the standard LinuxSH BIOS
 * usually from within the early stages of kernel boot.
 */
बाह्य व्योम sh_bios_console_ग_लिखो(स्थिर अक्षर *buf, अचिन्हित पूर्णांक len);
बाह्य व्योम sh_bios_gdb_detach(व्योम);

बाह्य व्योम sh_bios_get_node_addr(अचिन्हित अक्षर *node_addr);
बाह्य व्योम sh_bios_shutकरोwn(अचिन्हित पूर्णांक how);

बाह्य व्योम sh_bios_vbr_init(व्योम);
बाह्य व्योम sh_bios_vbr_reload(व्योम);

#अन्यथा

अटल अंतरभूत व्योम sh_bios_vbr_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम sh_bios_vbr_reload(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_SH_STANDARD_BIOS */

#पूर्ण_अगर /* __ASM_SH_BIOS_H */
