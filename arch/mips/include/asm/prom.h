<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/mips/include/यंत्र/prom.h
 *
 *  Copyright (C) 2010 Cisco Systems Inc. <dediao@cisco.com>
 */
#अगर_अघोषित __ASM_PROM_H
#घोषणा __ASM_PROM_H

#अगर_घोषित CONFIG_USE_OF
#समावेश <linux/bug.h>
#समावेश <linux/पन.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/bootinfo.h>

बाह्य व्योम device_tree_init(व्योम);

काष्ठा boot_param_header;

बाह्य व्योम __dt_setup_arch(व्योम *bph);
बाह्य पूर्णांक __dt_रेजिस्टर_buses(स्थिर अक्षर *bus0, स्थिर अक्षर *bus1);

#अन्यथा /* CONFIG_OF */
अटल अंतरभूत व्योम device_tree_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

बाह्य अक्षर *mips_get_machine_name(व्योम);
बाह्य व्योम mips_set_machine_name(स्थिर अक्षर *name);

#पूर्ण_अगर /* __ASM_PROM_H */
