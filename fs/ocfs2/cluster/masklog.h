<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2005 Oracle.  All rights reserved.
 */

#अगर_अघोषित O2CLUSTER_MASKLOG_H
#घोषणा O2CLUSTER_MASKLOG_H

/*
 * For now this is a trivial wrapper around prपूर्णांकk() that gives the critical
 * ability to enable sets of debugging output at run-समय.  In the future this
 * will almost certainly be redirected to relayfs so that it can pay a
 * substantially lower heisenberg tax.
 *
 * Callers associate the message with a biपंचांगask and a global biपंचांगask is
 * मुख्यtained with help from /proc.  If any of the bits match the message is
 * output.
 *
 * We must have efficient bit tests on i386 and it seems gcc still emits crazy
 * code क्रम the 64bit compare.  It emits very good code क्रम the dual अचिन्हित
 * दीर्घ tests, though, completely aव्योमing tests that can never pass अगर the
 * caller gives a स्थिरant biपंचांगask that fills one of the दीर्घs with all 0s.  So
 * the desire is to have almost all of the calls decided on by comparing just
 * one of the दीर्घs.  This leads to having infrequently given bits that are
 * frequently matched in the high bits.
 *
 * _ERROR and _NOTICE are used क्रम messages that always go to the console and
 * have appropriate KERN_ prefixes.  We wrap these in our function instead of
 * just calling prपूर्णांकk() so that this can eventually make its way through
 * relayfs aदीर्घ with the debugging messages.  Everything अन्यथा माला_लो KERN_DEBUG.
 * The अंतरभूत tests and macro dance give GCC the opportunity to quite cleverly
 * only emit the appropriage prपूर्णांकk() when the caller passes in a स्थिरant
 * mask, as is almost always the हाल.
 *
 * All this biपंचांगask nonsense is managed from the files under
 * /sys/fs/o2cb/logmask/.  Reading the files gives a straightक्रमward
 * indication of which bits are allowed (allow) or denied (off/deny).
 * 	ENTRY deny
 * 	EXIT deny
 * 	TCP off
 * 	MSG off
 * 	SOCKET off
 * 	ERROR allow
 * 	NOTICE allow
 *
 * Writing changes the state of a given bit and requires a strictly क्रमmatted
 * single ग_लिखो() call:
 *
 * 	ग_लिखो(fd, "allow", 5);
 *
 * Echoing allow/deny/off string पूर्णांकo the logmask files can flip the bits
 * on or off as expected; here is the bash script क्रम example:
 *
 * log_mask="/sys/fs/o2cb/log_mask"
 * क्रम node in ENTRY EXIT TCP MSG SOCKET ERROR NOTICE; करो
 *	echo allow >"$log_mask"/"$node"
 * करोne
 *
 * The debugfs.ocfs2 tool can also flip the bits with the -l option:
 *
 * debugfs.ocfs2 -l TCP allow
 */

/* क्रम task_काष्ठा */
#समावेश <linux/sched.h>

/* bits that are frequently given and infrequently matched in the low word */
/* NOTE: If you add a flag, you need to also update masklog.c! */
#घोषणा ML_TCP		0x0000000000000001ULL /* net cluster/tcp.c */
#घोषणा ML_MSG		0x0000000000000002ULL /* net network messages */
#घोषणा ML_SOCKET	0x0000000000000004ULL /* net socket lअगरeसमय */
#घोषणा ML_HEARTBEAT	0x0000000000000008ULL /* hb all heartbeat tracking */
#घोषणा ML_HB_BIO	0x0000000000000010ULL /* hb io tracing */
#घोषणा ML_DLMFS	0x0000000000000020ULL /* dlm user dlmfs */
#घोषणा ML_DLM		0x0000000000000040ULL /* dlm general debugging */
#घोषणा ML_DLM_DOMAIN	0x0000000000000080ULL /* dlm करोमुख्य debugging */
#घोषणा ML_DLM_THREAD	0x0000000000000100ULL /* dlm करोमुख्य thपढ़ो */
#घोषणा ML_DLM_MASTER	0x0000000000000200ULL /* dlm master functions */
#घोषणा ML_DLM_RECOVERY	0x0000000000000400ULL /* dlm master functions */
#घोषणा ML_DLM_GLUE	0x0000000000000800ULL /* ocfs2 dlm glue layer */
#घोषणा ML_VOTE		0x0000000000001000ULL /* ocfs2 node messaging  */
#घोषणा ML_CONN		0x0000000000002000ULL /* net connection management */
#घोषणा ML_QUORUM	0x0000000000004000ULL /* net connection quorum */
#घोषणा ML_BASTS	0x0000000000008000ULL /* dlmglue asts and basts */
#घोषणा ML_CLUSTER	0x0000000000010000ULL /* cluster stack */

/* bits that are infrequently given and frequently matched in the high word */
#घोषणा ML_ERROR	0x1000000000000000ULL /* sent to KERN_ERR */
#घोषणा ML_NOTICE	0x2000000000000000ULL /* setn to KERN_NOTICE */
#घोषणा ML_KTHREAD	0x4000000000000000ULL /* kernel thपढ़ो activity */

#घोषणा MLOG_INITIAL_AND_MASK (ML_ERROR|ML_NOTICE)
#अगर_अघोषित MLOG_MASK_PREFIX
#घोषणा MLOG_MASK_PREFIX 0
#पूर्ण_अगर

/*
 * When logging is disabled, क्रमce the bit test to 0 क्रम anything other
 * than errors and notices, allowing gcc to हटाओ the code completely.
 * When enabled, allow all masks.
 */
#अगर defined(CONFIG_OCFS2_DEBUG_MASKLOG)
#घोषणा ML_ALLOWED_BITS ~0
#अन्यथा
#घोषणा ML_ALLOWED_BITS (ML_ERROR|ML_NOTICE)
#पूर्ण_अगर

#घोषणा MLOG_MAX_BITS 64

काष्ठा mlog_bits अणु
	अचिन्हित दीर्घ words[MLOG_MAX_BITS / BITS_PER_LONG];
पूर्ण;

बाह्य काष्ठा mlog_bits mlog_and_bits, mlog_not_bits;

#अगर BITS_PER_LONG == 32

#घोषणा __mlog_test_u64(mask, bits)			\
	( (u32)(mask & 0xffffffff) & bits.words[0] || 	\
	  ((u64)(mask) >> 32) & bits.words[1] )
#घोषणा __mlog_set_u64(mask, bits) करो अणु			\
	bits.words[0] |= (u32)(mask & 0xffffffff);	\
       	bits.words[1] |= (u64)(mask) >> 32;		\
पूर्ण जबतक (0)
#घोषणा __mlog_clear_u64(mask, bits) करो अणु		\
	bits.words[0] &= ~((u32)(mask & 0xffffffff));	\
       	bits.words[1] &= ~((u64)(mask) >> 32);		\
पूर्ण जबतक (0)
#घोषणा MLOG_BITS_RHS(mask) अणु				\
	अणु						\
		[0] = (u32)(mask & 0xffffffff),		\
		[1] = (u64)(mask) >> 32,		\
	पूर्ण						\
पूर्ण

#अन्यथा /* 32bit दीर्घ above, 64bit दीर्घ below */

#घोषणा __mlog_test_u64(mask, bits)	((mask) & bits.words[0])
#घोषणा __mlog_set_u64(mask, bits) करो अणु		\
	bits.words[0] |= (mask);		\
पूर्ण जबतक (0)
#घोषणा __mlog_clear_u64(mask, bits) करो अणु	\
	bits.words[0] &= ~(mask);		\
पूर्ण जबतक (0)
#घोषणा MLOG_BITS_RHS(mask) अणु अणु (mask) पूर्ण पूर्ण

#पूर्ण_अगर

__म_लिखो(4, 5)
व्योम __mlog_prपूर्णांकk(स्थिर u64 *m, स्थिर अक्षर *func, पूर्णांक line,
		   स्थिर अक्षर *fmt, ...);

/*
 * Testing beक्रमe the __mlog_prपूर्णांकk call lets the compiler eliminate the
 * call completely when (m & ML_ALLOWED_BITS) is 0.
 */
#घोषणा mlog(mask, fmt, ...)						\
करो अणु									\
	u64 _m = MLOG_MASK_PREFIX | (mask);				\
	अगर (_m & ML_ALLOWED_BITS)					\
		__mlog_prपूर्णांकk(&_m, __func__, __LINE__, fmt,		\
			      ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा mlog_ratelimited(mask, fmt, ...)				\
करो अणु									\
	अटल DEFINE_RATELIMIT_STATE(_rs,				\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);		\
	अगर (__ratelimit(&_rs))						\
		mlog(mask, fmt, ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा mlog_त्रुटि_सं(st) (अणु						\
	पूर्णांक _st = (st);							\
	अगर (_st != -ERESTARTSYS && _st != -EINTR &&			\
	    _st != AOP_TRUNCATED_PAGE && _st != -ENOSPC &&		\
	    _st != -EDQUOT)						\
		mlog(ML_ERROR, "status = %lld\n", (दीर्घ दीर्घ)_st);	\
	_st;								\
पूर्ण)

#घोषणा mlog_bug_on_msg(cond, fmt, args...) करो अणु			\
	अगर (cond) अणु							\
		mlog(ML_ERROR, "bug expression: " #cond "\n");		\
		mlog(ML_ERROR, fmt, ##args);				\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
पूर्णांक mlog_sys_init(काष्ठा kset *o2cb_subsys);
व्योम mlog_sys_shutकरोwn(व्योम);

#पूर्ण_अगर /* O2CLUSTER_MASKLOG_H */
