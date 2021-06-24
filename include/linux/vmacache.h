<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_VMACACHE_H
#घोषणा __LINUX_VMACACHE_H

#समावेश <linux/sched.h>
#समावेश <linux/mm.h>

अटल अंतरभूत व्योम vmacache_flush(काष्ठा task_काष्ठा *tsk)
अणु
	स_रखो(tsk->vmacache.vmas, 0, माप(tsk->vmacache.vmas));
पूर्ण

बाह्य व्योम vmacache_update(अचिन्हित दीर्घ addr, काष्ठा vm_area_काष्ठा *newvma);
बाह्य काष्ठा vm_area_काष्ठा *vmacache_find(काष्ठा mm_काष्ठा *mm,
						    अचिन्हित दीर्घ addr);

#अगर_अघोषित CONFIG_MMU
बाह्य काष्ठा vm_area_काष्ठा *vmacache_find_exact(काष्ठा mm_काष्ठा *mm,
						  अचिन्हित दीर्घ start,
						  अचिन्हित दीर्घ end);
#पूर्ण_अगर

अटल अंतरभूत व्योम vmacache_invalidate(काष्ठा mm_काष्ठा *mm)
अणु
	mm->vmacache_seqnum++;
पूर्ण

#पूर्ण_अगर /* __LINUX_VMACACHE_H */
