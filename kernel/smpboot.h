<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SMPBOOT_H
#घोषणा SMPBOOT_H

काष्ठा task_काष्ठा;

#अगर_घोषित CONFIG_GENERIC_SMP_IDLE_THREAD
काष्ठा task_काष्ठा *idle_thपढ़ो_get(अचिन्हित पूर्णांक cpu);
व्योम idle_thपढ़ो_set_boot_cpu(व्योम);
व्योम idle_thपढ़ोs_init(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा task_काष्ठा *idle_thपढ़ो_get(अचिन्हित पूर्णांक cpu) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम idle_thपढ़ो_set_boot_cpu(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम idle_thपढ़ोs_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक smpboot_create_thपढ़ोs(अचिन्हित पूर्णांक cpu);
पूर्णांक smpboot_park_thपढ़ोs(अचिन्हित पूर्णांक cpu);
पूर्णांक smpboot_unpark_thपढ़ोs(अचिन्हित पूर्णांक cpu);

व्योम __init cpuhp_thपढ़ोs_init(व्योम);

#पूर्ण_अगर
