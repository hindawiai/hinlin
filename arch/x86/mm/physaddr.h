<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <यंत्र/processor.h>

अटल अंतरभूत पूर्णांक phys_addr_valid(resource_माप_प्रकार addr)
अणु
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	वापस !(addr >> boot_cpu_data.x86_phys_bits);
#अन्यथा
	वापस 1;
#पूर्ण_अगर
पूर्ण
