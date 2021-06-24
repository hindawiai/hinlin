<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PKEYS_HELPER_H
#घोषणा _PKEYS_HELPER_H
#घोषणा _GNU_SOURCE
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <संकेत.स>
#समावेश <निश्चित.स>
#समावेश <मानककोष.स>
#समावेश <ucontext.h>
#समावेश <sys/mman.h>

/* Define some kernel-like types */
#घोषणा  u8 __u8
#घोषणा u16 __u16
#घोषणा u32 __u32
#घोषणा u64 __u64

#घोषणा PTR_ERR_ENOTSUP ((व्योम *)-ENOTSUP)

#अगर_अघोषित DEBUG_LEVEL
#घोषणा DEBUG_LEVEL 0
#पूर्ण_अगर
#घोषणा DPRINT_IN_SIGNAL_BUF_SIZE 4096
बाह्य पूर्णांक dprपूर्णांक_in_संकेत;
बाह्य अक्षर dprपूर्णांक_in_संकेत_buffer[DPRINT_IN_SIGNAL_BUF_SIZE];

बाह्य पूर्णांक test_nr;
बाह्य पूर्णांक iteration_nr;

#अगर_घोषित __GNUC__
__attribute__((क्रमmat(म_लिखो, 1, 2)))
#पूर्ण_अगर
अटल अंतरभूत व्योम sigsafe_म_लिखो(स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची ap;

	अगर (!dprपूर्णांक_in_संकेत) अणु
		बहु_शुरू(ap, क्रमmat);
		भ_लिखो(क्रमmat, ap);
		बहु_पूर्ण(ap);
	पूर्ण अन्यथा अणु
		पूर्णांक ret;
		/*
		 * No म_लिखो() functions are संकेत-safe.
		 * They deadlock easily. Write the क्रमmat
		 * string to get some output, even अगर
		 * incomplete.
		 */
		ret = ग_लिखो(1, क्रमmat, म_माप(क्रमmat));
		अगर (ret < 0)
			निकास(1);
	पूर्ण
पूर्ण
#घोषणा dम_लिखो_level(level, args...) करो अणु	\
	अगर (level <= DEBUG_LEVEL)		\
		sigsafe_म_लिखो(args);		\
पूर्ण जबतक (0)
#घोषणा dम_लिखो0(args...) dम_लिखो_level(0, args)
#घोषणा dम_लिखो1(args...) dम_लिखो_level(1, args)
#घोषणा dम_लिखो2(args...) dम_लिखो_level(2, args)
#घोषणा dम_लिखो3(args...) dम_लिखो_level(3, args)
#घोषणा dम_लिखो4(args...) dम_लिखो_level(4, args)

बाह्य व्योम पात_hooks(व्योम);
#घोषणा pkey_निश्चित(condition) करो अणु		\
	अगर (!(condition)) अणु			\
		dम_लिखो0("assert() at %s::%d test_nr: %d iteration: %d\n", \
				__खाता__, __LINE__,	\
				test_nr, iteration_nr);	\
		dम_लिखो0("errno at assert: %d", त्रुटि_सं);	\
		पात_hooks();			\
		निकास(__LINE__);			\
	पूर्ण					\
पूर्ण जबतक (0)

__attribute__((noअंतरभूत)) पूर्णांक पढ़ो_ptr(पूर्णांक *ptr);
व्योम expected_pkey_fault(पूर्णांक pkey);
पूर्णांक sys_pkey_alloc(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ init_val);
पूर्णांक sys_pkey_मुक्त(अचिन्हित दीर्घ pkey);
पूर्णांक mprotect_pkey(व्योम *ptr, माप_प्रकार size, अचिन्हित दीर्घ orig_prot,
		अचिन्हित दीर्घ pkey);
व्योम record_pkey_दो_स्मृति(व्योम *ptr, दीर्घ size, पूर्णांक prot);

#अगर defined(__i386__) || defined(__x86_64__) /* arch */
#समावेश "pkey-x86.h"
#या_अगर defined(__घातerpc64__) /* arch */
#समावेश "pkey-powerpc.h"
#अन्यथा /* arch */
#त्रुटि Architecture not supported
#पूर्ण_अगर /* arch */

#घोषणा PKEY_MASK	(PKEY_DISABLE_ACCESS | PKEY_DISABLE_WRITE)

अटल अंतरभूत u64 set_pkey_bits(u64 reg, पूर्णांक pkey, u64 flags)
अणु
	u32 shअगरt = pkey_bit_position(pkey);
	/* mask out bits from pkey in old value */
	reg &= ~((u64)PKEY_MASK << shअगरt);
	/* OR in new bits क्रम pkey */
	reg |= (flags & PKEY_MASK) << shअगरt;
	वापस reg;
पूर्ण

अटल अंतरभूत u64 get_pkey_bits(u64 reg, पूर्णांक pkey)
अणु
	u32 shअगरt = pkey_bit_position(pkey);
	/*
	 * shअगरt करोwn the relevant bits to the lowest two, then
	 * mask off all the other higher bits
	 */
	वापस ((reg >> shअगरt) & PKEY_MASK);
पूर्ण

बाह्य u64 shaकरोw_pkey_reg;

अटल अंतरभूत u64 _पढ़ो_pkey_reg(पूर्णांक line)
अणु
	u64 pkey_reg = __पढ़ो_pkey_reg();

	dम_लिखो4("read_pkey_reg(line=%d) pkey_reg: %016llx"
			" shadow: %016llx\n",
			line, pkey_reg, shaकरोw_pkey_reg);
	निश्चित(pkey_reg == shaकरोw_pkey_reg);

	वापस pkey_reg;
पूर्ण

#घोषणा पढ़ो_pkey_reg() _पढ़ो_pkey_reg(__LINE__)

अटल अंतरभूत व्योम ग_लिखो_pkey_reg(u64 pkey_reg)
अणु
	dम_लिखो4("%s() changing %016llx to %016llx\n", __func__,
			__पढ़ो_pkey_reg(), pkey_reg);
	/* will करो the shaकरोw check क्रम us: */
	पढ़ो_pkey_reg();
	__ग_लिखो_pkey_reg(pkey_reg);
	shaकरोw_pkey_reg = pkey_reg;
	dम_लिखो4("%s(%016llx) pkey_reg: %016llx\n", __func__,
			pkey_reg, __पढ़ो_pkey_reg());
पूर्ण

/*
 * These are technically racy. since something could
 * change PKEY रेजिस्टर between the पढ़ो and the ग_लिखो.
 */
अटल अंतरभूत व्योम __pkey_access_allow(पूर्णांक pkey, पूर्णांक करो_allow)
अणु
	u64 pkey_reg = पढ़ो_pkey_reg();
	पूर्णांक bit = pkey * 2;

	अगर (करो_allow)
		pkey_reg &= (1<<bit);
	अन्यथा
		pkey_reg |= (1<<bit);

	dम_लिखो4("pkey_reg now: %016llx\n", पढ़ो_pkey_reg());
	ग_लिखो_pkey_reg(pkey_reg);
पूर्ण

अटल अंतरभूत व्योम __pkey_ग_लिखो_allow(पूर्णांक pkey, पूर्णांक करो_allow_ग_लिखो)
अणु
	u64 pkey_reg = पढ़ो_pkey_reg();
	पूर्णांक bit = pkey * 2 + 1;

	अगर (करो_allow_ग_लिखो)
		pkey_reg &= (1<<bit);
	अन्यथा
		pkey_reg |= (1<<bit);

	ग_लिखो_pkey_reg(pkey_reg);
	dम_लिखो4("pkey_reg now: %016llx\n", पढ़ो_pkey_reg());
पूर्ण

#घोषणा ARRAY_SIZE(x) (माप(x) / माप(*(x)))
#घोषणा ALIGN_UP(x, align_to)	(((x) + ((align_to)-1)) & ~((align_to)-1))
#घोषणा ALIGN_DOWN(x, align_to) ((x) & ~((align_to)-1))
#घोषणा ALIGN_PTR_UP(p, ptr_align_to)	\
	((typeof(p))ALIGN_UP((अचिन्हित दीर्घ)(p), ptr_align_to))
#घोषणा ALIGN_PTR_DOWN(p, ptr_align_to)	\
	((typeof(p))ALIGN_DOWN((अचिन्हित दीर्घ)(p), ptr_align_to))
#घोषणा __stringअगरy_1(x...)     #x
#घोषणा __stringअगरy(x...)       __stringअगरy_1(x)

अटल अंतरभूत u32 *siginfo_get_pkey_ptr(siginfo_t *si)
अणु
#अगर_घोषित si_pkey
	वापस &si->si_pkey;
#अन्यथा
	वापस (u32 *)(((u8 *)si) + si_pkey_offset);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक kernel_has_pkeys(व्योम)
अणु
	/* try allocating a key and see अगर it succeeds */
	पूर्णांक ret = sys_pkey_alloc(0, 0);
	अगर (ret <= 0) अणु
		वापस 0;
	पूर्ण
	sys_pkey_मुक्त(ret);
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक is_pkeys_supported(व्योम)
अणु
	/* check अगर the cpu supports pkeys */
	अगर (!cpu_has_pkeys()) अणु
		dम_लिखो1("SKIP: %s: no CPU support\n", __func__);
		वापस 0;
	पूर्ण

	/* check अगर the kernel supports pkeys */
	अगर (!kernel_has_pkeys()) अणु
		dम_लिखो1("SKIP: %s: no kernel support\n", __func__);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

#पूर्ण_अगर /* _PKEYS_HELPER_H */
