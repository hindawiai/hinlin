<शैली गुरु>
#अगर_अघोषित _LINUX_MMAP_LOCK_H
#घोषणा _LINUX_MMAP_LOCK_H

#समावेश <linux/lockdep.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/tracepoपूर्णांक-defs.h>
#समावेश <linux/types.h>

#घोषणा MMAP_LOCK_INITIALIZER(name) \
	.mmap_lock = __RWSEM_INITIALIZER((name).mmap_lock),

DECLARE_TRACEPOINT(mmap_lock_start_locking);
DECLARE_TRACEPOINT(mmap_lock_acquire_वापसed);
DECLARE_TRACEPOINT(mmap_lock_released);

#अगर_घोषित CONFIG_TRACING

व्योम __mmap_lock_करो_trace_start_locking(काष्ठा mm_काष्ठा *mm, bool ग_लिखो);
व्योम __mmap_lock_करो_trace_acquire_वापसed(काष्ठा mm_काष्ठा *mm, bool ग_लिखो,
					   bool success);
व्योम __mmap_lock_करो_trace_released(काष्ठा mm_काष्ठा *mm, bool ग_लिखो);

अटल अंतरभूत व्योम __mmap_lock_trace_start_locking(काष्ठा mm_काष्ठा *mm,
						   bool ग_लिखो)
अणु
	अगर (tracepoपूर्णांक_enabled(mmap_lock_start_locking))
		__mmap_lock_करो_trace_start_locking(mm, ग_लिखो);
पूर्ण

अटल अंतरभूत व्योम __mmap_lock_trace_acquire_वापसed(काष्ठा mm_काष्ठा *mm,
						      bool ग_लिखो, bool success)
अणु
	अगर (tracepoपूर्णांक_enabled(mmap_lock_acquire_वापसed))
		__mmap_lock_करो_trace_acquire_वापसed(mm, ग_लिखो, success);
पूर्ण

अटल अंतरभूत व्योम __mmap_lock_trace_released(काष्ठा mm_काष्ठा *mm, bool ग_लिखो)
अणु
	अगर (tracepoपूर्णांक_enabled(mmap_lock_released))
		__mmap_lock_करो_trace_released(mm, ग_लिखो);
पूर्ण

#अन्यथा /* !CONFIG_TRACING */

अटल अंतरभूत व्योम __mmap_lock_trace_start_locking(काष्ठा mm_काष्ठा *mm,
						   bool ग_लिखो)
अणु
पूर्ण

अटल अंतरभूत व्योम __mmap_lock_trace_acquire_वापसed(काष्ठा mm_काष्ठा *mm,
						      bool ग_लिखो, bool success)
अणु
पूर्ण

अटल अंतरभूत व्योम __mmap_lock_trace_released(काष्ठा mm_काष्ठा *mm, bool ग_लिखो)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_TRACING */

अटल अंतरभूत व्योम mmap_init_lock(काष्ठा mm_काष्ठा *mm)
अणु
	init_rwsem(&mm->mmap_lock);
पूर्ण

अटल अंतरभूत व्योम mmap_ग_लिखो_lock(काष्ठा mm_काष्ठा *mm)
अणु
	__mmap_lock_trace_start_locking(mm, true);
	करोwn_ग_लिखो(&mm->mmap_lock);
	__mmap_lock_trace_acquire_वापसed(mm, true, true);
पूर्ण

अटल अंतरभूत व्योम mmap_ग_लिखो_lock_nested(काष्ठा mm_काष्ठा *mm, पूर्णांक subclass)
अणु
	__mmap_lock_trace_start_locking(mm, true);
	करोwn_ग_लिखो_nested(&mm->mmap_lock, subclass);
	__mmap_lock_trace_acquire_वापसed(mm, true, true);
पूर्ण

अटल अंतरभूत पूर्णांक mmap_ग_लिखो_lock_समाप्तable(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक ret;

	__mmap_lock_trace_start_locking(mm, true);
	ret = करोwn_ग_लिखो_समाप्तable(&mm->mmap_lock);
	__mmap_lock_trace_acquire_वापसed(mm, true, ret == 0);
	वापस ret;
पूर्ण

अटल अंतरभूत bool mmap_ग_लिखो_trylock(काष्ठा mm_काष्ठा *mm)
अणु
	bool ret;

	__mmap_lock_trace_start_locking(mm, true);
	ret = करोwn_ग_लिखो_trylock(&mm->mmap_lock) != 0;
	__mmap_lock_trace_acquire_वापसed(mm, true, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम mmap_ग_लिखो_unlock(काष्ठा mm_काष्ठा *mm)
अणु
	up_ग_लिखो(&mm->mmap_lock);
	__mmap_lock_trace_released(mm, true);
पूर्ण

अटल अंतरभूत व्योम mmap_ग_लिखो_करोwngrade(काष्ठा mm_काष्ठा *mm)
अणु
	करोwngrade_ग_लिखो(&mm->mmap_lock);
	__mmap_lock_trace_acquire_वापसed(mm, false, true);
पूर्ण

अटल अंतरभूत व्योम mmap_पढ़ो_lock(काष्ठा mm_काष्ठा *mm)
अणु
	__mmap_lock_trace_start_locking(mm, false);
	करोwn_पढ़ो(&mm->mmap_lock);
	__mmap_lock_trace_acquire_वापसed(mm, false, true);
पूर्ण

अटल अंतरभूत पूर्णांक mmap_पढ़ो_lock_समाप्तable(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक ret;

	__mmap_lock_trace_start_locking(mm, false);
	ret = करोwn_पढ़ो_समाप्तable(&mm->mmap_lock);
	__mmap_lock_trace_acquire_वापसed(mm, false, ret == 0);
	वापस ret;
पूर्ण

अटल अंतरभूत bool mmap_पढ़ो_trylock(काष्ठा mm_काष्ठा *mm)
अणु
	bool ret;

	__mmap_lock_trace_start_locking(mm, false);
	ret = करोwn_पढ़ो_trylock(&mm->mmap_lock) != 0;
	__mmap_lock_trace_acquire_वापसed(mm, false, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम mmap_पढ़ो_unlock(काष्ठा mm_काष्ठा *mm)
अणु
	up_पढ़ो(&mm->mmap_lock);
	__mmap_lock_trace_released(mm, false);
पूर्ण

अटल अंतरभूत bool mmap_पढ़ो_trylock_non_owner(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mmap_पढ़ो_trylock(mm)) अणु
		rwsem_release(&mm->mmap_lock.dep_map, _RET_IP_);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम mmap_पढ़ो_unlock_non_owner(काष्ठा mm_काष्ठा *mm)
अणु
	up_पढ़ो_non_owner(&mm->mmap_lock);
	__mmap_lock_trace_released(mm, false);
पूर्ण

अटल अंतरभूत व्योम mmap_निश्चित_locked(काष्ठा mm_काष्ठा *mm)
अणु
	lockdep_निश्चित_held(&mm->mmap_lock);
	VM_BUG_ON_MM(!rwsem_is_locked(&mm->mmap_lock), mm);
पूर्ण

अटल अंतरभूत व्योम mmap_निश्चित_ग_लिखो_locked(काष्ठा mm_काष्ठा *mm)
अणु
	lockdep_निश्चित_held_ग_लिखो(&mm->mmap_lock);
	VM_BUG_ON_MM(!rwsem_is_locked(&mm->mmap_lock), mm);
पूर्ण

अटल अंतरभूत पूर्णांक mmap_lock_is_contended(काष्ठा mm_काष्ठा *mm)
अणु
	वापस rwsem_is_contended(&mm->mmap_lock);
पूर्ण

#पूर्ण_अगर /* _LINUX_MMAP_LOCK_H */
