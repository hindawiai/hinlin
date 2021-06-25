<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_VDSO_H
#घोषणा __ASM_VDSO_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__

काष्ठा mm_काष्ठा;

#अगर_घोषित CONFIG_VDSO

व्योम arm_install_vdso(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);

बाह्य अचिन्हित पूर्णांक vdso_total_pages;

#अन्यथा /* CONFIG_VDSO */

अटल अंतरभूत व्योम arm_install_vdso(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
पूर्ण

#घोषणा vdso_total_pages 0

#पूर्ण_अगर /* CONFIG_VDSO */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASM_VDSO_H */
