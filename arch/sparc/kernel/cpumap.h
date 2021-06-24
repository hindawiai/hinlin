<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CPUMAP_H
#घोषणा _CPUMAP_H

#अगर_घोषित CONFIG_SMP
व्योम cpu_map_rebuild(व्योम);
पूर्णांक map_to_cpu(अचिन्हित पूर्णांक index);
#घोषणा cpu_map_init() cpu_map_rebuild()
#अन्यथा
#घोषणा cpu_map_init() करो अणुपूर्ण जबतक (0)
अटल अंतरभूत पूर्णांक map_to_cpu(अचिन्हित पूर्णांक index)
अणु
	वापस raw_smp_processor_id();
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
