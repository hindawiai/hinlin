<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_MM_DEBUG_H
#घोषणा LINUX_MM_DEBUG_H 1

#समावेश <linux/bug.h>
#समावेश <linux/stringअगरy.h>

काष्ठा page;
काष्ठा vm_area_काष्ठा;
काष्ठा mm_काष्ठा;

बाह्य व्योम dump_page(काष्ठा page *page, स्थिर अक्षर *reason);
बाह्य व्योम __dump_page(काष्ठा page *page, स्थिर अक्षर *reason);
व्योम dump_vma(स्थिर काष्ठा vm_area_काष्ठा *vma);
व्योम dump_mm(स्थिर काष्ठा mm_काष्ठा *mm);

#अगर_घोषित CONFIG_DEBUG_VM
#घोषणा VM_BUG_ON(cond) BUG_ON(cond)
#घोषणा VM_BUG_ON_PAGE(cond, page)					\
	करो अणु								\
		अगर (unlikely(cond)) अणु					\
			dump_page(page, "VM_BUG_ON_PAGE(" __stringअगरy(cond)")");\
			BUG();						\
		पूर्ण							\
	पूर्ण जबतक (0)
#घोषणा VM_BUG_ON_VMA(cond, vma)					\
	करो अणु								\
		अगर (unlikely(cond)) अणु					\
			dump_vma(vma);					\
			BUG();						\
		पूर्ण							\
	पूर्ण जबतक (0)
#घोषणा VM_BUG_ON_MM(cond, mm)						\
	करो अणु								\
		अगर (unlikely(cond)) अणु					\
			dump_mm(mm);					\
			BUG();						\
		पूर्ण							\
	पूर्ण जबतक (0)
#घोषणा VM_WARN_ON_ONCE_PAGE(cond, page)	(अणु			\
	अटल bool __section(".data.once") __warned;			\
	पूर्णांक __ret_warn_once = !!(cond);					\
									\
	अगर (unlikely(__ret_warn_once && !__warned)) अणु			\
		dump_page(page, "VM_WARN_ON_ONCE_PAGE(" __stringअगरy(cond)")");\
		__warned = true;					\
		WARN_ON(1);						\
	पूर्ण								\
	unlikely(__ret_warn_once);					\
पूर्ण)

#घोषणा VM_WARN_ON(cond) (व्योम)WARN_ON(cond)
#घोषणा VM_WARN_ON_ONCE(cond) (व्योम)WARN_ON_ONCE(cond)
#घोषणा VM_WARN_ONCE(cond, क्रमmat...) (व्योम)WARN_ONCE(cond, क्रमmat)
#घोषणा VM_WARN(cond, क्रमmat...) (व्योम)WARN(cond, क्रमmat)
#अन्यथा
#घोषणा VM_BUG_ON(cond) BUILD_BUG_ON_INVALID(cond)
#घोषणा VM_BUG_ON_PAGE(cond, page) VM_BUG_ON(cond)
#घोषणा VM_BUG_ON_VMA(cond, vma) VM_BUG_ON(cond)
#घोषणा VM_BUG_ON_MM(cond, mm) VM_BUG_ON(cond)
#घोषणा VM_WARN_ON(cond) BUILD_BUG_ON_INVALID(cond)
#घोषणा VM_WARN_ON_ONCE(cond) BUILD_BUG_ON_INVALID(cond)
#घोषणा VM_WARN_ON_ONCE_PAGE(cond, page)  BUILD_BUG_ON_INVALID(cond)
#घोषणा VM_WARN_ONCE(cond, क्रमmat...) BUILD_BUG_ON_INVALID(cond)
#घोषणा VM_WARN(cond, क्रमmat...) BUILD_BUG_ON_INVALID(cond)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_VIRTUAL
#घोषणा VIRTUAL_BUG_ON(cond) BUG_ON(cond)
#अन्यथा
#घोषणा VIRTUAL_BUG_ON(cond) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_VM_PGFLAGS
#घोषणा VM_BUG_ON_PGFLAGS(cond, page) VM_BUG_ON_PAGE(cond, page)
#अन्यथा
#घोषणा VM_BUG_ON_PGFLAGS(cond, page) BUILD_BUG_ON_INVALID(cond)
#पूर्ण_अगर

#पूर्ण_अगर
