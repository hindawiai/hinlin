<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
व्योम convert_to_tag_list(काष्ठा tag *tags);

#अगर_घोषित CONFIG_ATAGS
स्थिर काष्ठा machine_desc *setup_machine_tags(व्योम *__atags_vaddr,
	अचिन्हित पूर्णांक machine_nr);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा machine_desc * __init __noवापस
setup_machine_tags(व्योम *__atags_vaddr, अचिन्हित पूर्णांक machine_nr)
अणु
	early_prपूर्णांक("no ATAGS support: can't continue\n");
	जबतक (true);
	unreachable();
पूर्ण
#पूर्ण_अगर
