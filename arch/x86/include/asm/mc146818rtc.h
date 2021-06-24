<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Machine dependent access functions क्रम RTC रेजिस्टरs.
 */
#अगर_अघोषित _ASM_X86_MC146818RTC_H
#घोषणा _ASM_X86_MC146818RTC_H

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>

#अगर_अघोषित RTC_PORT
#घोषणा RTC_PORT(x)	(0x70 + (x))
#घोषणा RTC_ALWAYS_BCD	1	/* RTC operates in binary mode */
#पूर्ण_अगर

#अगर defined(CONFIG_X86_32)
/*
 * This lock provides nmi access to the CMOS/RTC रेजिस्टरs.  It has some
 * special properties.  It is owned by a CPU and stores the index रेजिस्टर
 * currently being accessed (अगर owned).  The idea here is that it works
 * like a normal lock (normally).  However, in an NMI, the NMI code will
 * first check to see अगर its CPU owns the lock, meaning that the NMI
 * पूर्णांकerrupted during the पढ़ो/ग_लिखो of the device.  If it करोes, it goes ahead
 * and perक्रमms the access and then restores the index रेजिस्टर.  If it करोes
 * not, it locks normally.
 *
 * Note that since we are working with NMIs, we need this lock even in
 * a non-SMP machine just to mark that the lock is owned.
 *
 * This only works with compare-and-swap.  There is no other way to
 * atomically claim the lock and set the owner.
 */
#समावेश <linux/smp.h>
बाह्य अस्थिर अचिन्हित दीर्घ cmos_lock;

/*
 * All of these below must be called with पूर्णांकerrupts off, preempt
 * disabled, etc.
 */

अटल अंतरभूत व्योम lock_cmos(अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ new;
	new = ((smp_processor_id() + 1) << 8) | reg;
	क्रम (;;) अणु
		अगर (cmos_lock) अणु
			cpu_relax();
			जारी;
		पूर्ण
		अगर (__cmpxchg(&cmos_lock, 0, new, माप(cmos_lock)) == 0)
			वापस;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम unlock_cmos(व्योम)
अणु
	cmos_lock = 0;
पूर्ण

अटल अंतरभूत पूर्णांक करो_i_have_lock_cmos(व्योम)
अणु
	वापस (cmos_lock >> 8) == (smp_processor_id() + 1);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर current_lock_cmos_reg(व्योम)
अणु
	वापस cmos_lock & 0xff;
पूर्ण

#घोषणा lock_cmos_prefix(reg)			\
	करो अणु					\
		अचिन्हित दीर्घ cmos_flags;	\
		local_irq_save(cmos_flags);	\
		lock_cmos(reg)

#घोषणा lock_cmos_suffix(reg)			\
	unlock_cmos();				\
	local_irq_restore(cmos_flags);		\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा lock_cmos_prefix(reg) करो अणुपूर्ण जबतक (0)
#घोषणा lock_cmos_suffix(reg) करो अणुपूर्ण जबतक (0)
#घोषणा lock_cmos(reg) करो अणु पूर्ण जबतक (0)
#घोषणा unlock_cmos() करो अणु पूर्ण जबतक (0)
#घोषणा करो_i_have_lock_cmos() 0
#घोषणा current_lock_cmos_reg() 0
#पूर्ण_अगर

/*
 * The yet supported machines all access the RTC index रेजिस्टर via
 * an ISA port access but the way to access the date रेजिस्टर dअगरfers ...
 */
#घोषणा CMOS_READ(addr) rtc_cmos_पढ़ो(addr)
#घोषणा CMOS_WRITE(val, addr) rtc_cmos_ग_लिखो(val, addr)
अचिन्हित अक्षर rtc_cmos_पढ़ो(अचिन्हित अक्षर addr);
व्योम rtc_cmos_ग_लिखो(अचिन्हित अक्षर val, अचिन्हित अक्षर addr);

बाह्य पूर्णांक mach_set_rtc_mmss(स्थिर काष्ठा बारpec64 *now);
बाह्य व्योम mach_get_cmos_समय(काष्ठा बारpec64 *now);

#घोषणा RTC_IRQ 8

#पूर्ण_अगर /* _ASM_X86_MC146818RTC_H */
