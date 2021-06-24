<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * पूर्णांकernal.h - prपूर्णांकk पूर्णांकernal definitions
 */
#समावेश <linux/percpu.h>

#अगर_घोषित CONFIG_PRINTK

#घोषणा PRINTK_SAFE_CONTEXT_MASK	0x007ffffff
#घोषणा PRINTK_NMI_सूचीECT_CONTEXT_MASK	0x008000000
#घोषणा PRINTK_NMI_CONTEXT_MASK		0xff0000000

#घोषणा PRINTK_NMI_CONTEXT_OFFSET	0x010000000

__म_लिखो(4, 0)
पूर्णांक vprपूर्णांकk_store(पूर्णांक facility, पूर्णांक level,
		  स्थिर काष्ठा dev_prपूर्णांकk_info *dev_info,
		  स्थिर अक्षर *fmt, बहु_सूची args);

__म_लिखो(1, 0) पूर्णांक vprपूर्णांकk_शेष(स्थिर अक्षर *fmt, बहु_सूची args);
__म_लिखो(1, 0) पूर्णांक vprपूर्णांकk_deferred(स्थिर अक्षर *fmt, बहु_सूची args);
व्योम __prपूर्णांकk_safe_enter(व्योम);
व्योम __prपूर्णांकk_safe_निकास(व्योम);

व्योम prपूर्णांकk_safe_init(व्योम);
bool prपूर्णांकk_percpu_data_पढ़ोy(व्योम);

#घोषणा prपूर्णांकk_safe_enter_irqsave(flags)	\
	करो अणु					\
		local_irq_save(flags);		\
		__prपूर्णांकk_safe_enter();		\
	पूर्ण जबतक (0)

#घोषणा prपूर्णांकk_safe_निकास_irqrestore(flags)	\
	करो अणु					\
		__prपूर्णांकk_safe_निकास();		\
		local_irq_restore(flags);	\
	पूर्ण जबतक (0)

#घोषणा prपूर्णांकk_safe_enter_irq()		\
	करो अणु					\
		local_irq_disable();		\
		__prपूर्णांकk_safe_enter();		\
	पूर्ण जबतक (0)

#घोषणा prपूर्णांकk_safe_निकास_irq()			\
	करो अणु					\
		__prपूर्णांकk_safe_निकास();		\
		local_irq_enable();		\
	पूर्ण जबतक (0)

व्योम defer_console_output(व्योम);

#अन्यथा

/*
 * In !PRINTK builds we still export console_sem
 * semaphore and some of console functions (console_unlock()/etc.), so
 * prपूर्णांकk-safe must preserve the existing local IRQ guarantees.
 */
#घोषणा prपूर्णांकk_safe_enter_irqsave(flags) local_irq_save(flags)
#घोषणा prपूर्णांकk_safe_निकास_irqrestore(flags) local_irq_restore(flags)

#घोषणा prपूर्णांकk_safe_enter_irq() local_irq_disable()
#घोषणा prपूर्णांकk_safe_निकास_irq() local_irq_enable()

अटल अंतरभूत व्योम prपूर्णांकk_safe_init(व्योम) अणु पूर्ण
अटल अंतरभूत bool prपूर्णांकk_percpu_data_पढ़ोy(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर /* CONFIG_PRINTK */
