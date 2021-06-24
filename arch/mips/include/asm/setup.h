<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MIPS_SETUP_H
#घोषणा _MIPS_SETUP_H

#समावेश <linux/types.h>
#समावेश <uapi/यंत्र/setup.h>

बाह्य व्योम prom_अक्षर_दो(अक्षर);
बाह्य व्योम setup_early_prपूर्णांकk(व्योम);

#अगर_घोषित CONFIG_EARLY_PRINTK_8250
बाह्य व्योम setup_8250_early_prपूर्णांकk_port(अचिन्हित दीर्घ base,
	अचिन्हित पूर्णांक reg_shअगरt, अचिन्हित पूर्णांक समयout);
#अन्यथा
अटल अंतरभूत व्योम setup_8250_early_prपूर्णांकk_port(अचिन्हित दीर्घ base,
	अचिन्हित पूर्णांक reg_shअगरt, अचिन्हित पूर्णांक समयout) अणुपूर्ण
#पूर्ण_अगर

बाह्य व्योम set_handler(अचिन्हित दीर्घ offset, व्योम *addr, अचिन्हित दीर्घ len);
बाह्य व्योम set_uncached_handler(अचिन्हित दीर्घ offset, व्योम *addr, अचिन्हित दीर्घ len);

प्रकार व्योम (*vi_handler_t)(व्योम);
बाह्य व्योम *set_vi_handler(पूर्णांक n, vi_handler_t addr);

बाह्य व्योम *set_except_vector(पूर्णांक n, व्योम *addr);
बाह्य अचिन्हित दीर्घ ebase;
बाह्य अचिन्हित पूर्णांक hwrena;
बाह्य व्योम per_cpu_trap_init(bool);
बाह्य व्योम cpu_cache_init(व्योम);

#पूर्ण_अगर /* __SETUP_H */
