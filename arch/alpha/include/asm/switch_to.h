<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_SWITCH_TO_H
#घोषणा __ALPHA_SWITCH_TO_H


काष्ठा task_काष्ठा;
बाह्य काष्ठा task_काष्ठा *alpha_चयन_to(अचिन्हित दीर्घ, काष्ठा task_काष्ठा *);

#घोषणा चयन_to(P,N,L)						 \
  करो अणु									 \
    (L) = alpha_चयन_to(virt_to_phys(&task_thपढ़ो_info(N)->pcb), (P)); \
    check_mmu_context();						 \
  पूर्ण जबतक (0)

#पूर्ण_अगर /* __ALPHA_SWITCH_TO_H */
