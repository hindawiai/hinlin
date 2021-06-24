<शैली गुरु>
#अगर_अघोषित _LINUX_TIME32_H
#घोषणा _LINUX_TIME32_H
/*
 * These are all पूर्णांकerfaces based on the old समय_प्रकार definition
 * that overflows in 2038 on 32-bit architectures. New code
 * should use the replacements based on समय64_t and बारpec64.
 *
 * Any पूर्णांकerfaces in here that become unused as we migrate
 * code to समय64_t should get हटाओd.
 */

#समावेश <linux/समय64.h>
#समावेश <linux/समयx.h>

#समावेश <vdso/समय32.h>

काष्ठा old_iसमयrspec32 अणु
	काष्ठा old_बारpec32 it_पूर्णांकerval;
	काष्ठा old_बारpec32 it_value;
पूर्ण;

काष्ठा old_utimbuf32 अणु
	old_समय32_t	aस_समय;
	old_समय32_t	modसमय;
पूर्ण;

काष्ठा old_समयx32 अणु
	u32 modes;
	s32 offset;
	s32 freq;
	s32 maxerror;
	s32 esterror;
	s32 status;
	s32 स्थिरant;
	s32 precision;
	s32 tolerance;
	काष्ठा old_समयval32 समय;
	s32 tick;
	s32 ppsfreq;
	s32 jitter;
	s32 shअगरt;
	s32 stabil;
	s32 jitcnt;
	s32 calcnt;
	s32 errcnt;
	s32 stbcnt;
	s32 tai;

	s32:32; s32:32; s32:32; s32:32;
	s32:32; s32:32; s32:32; s32:32;
	s32:32; s32:32; s32:32;
पूर्ण;

बाह्य पूर्णांक get_old_बारpec32(काष्ठा बारpec64 *, स्थिर व्योम __user *);
बाह्य पूर्णांक put_old_बारpec32(स्थिर काष्ठा बारpec64 *, व्योम __user *);
बाह्य पूर्णांक get_old_iसमयrspec32(काष्ठा iसमयrspec64 *its,
			स्थिर काष्ठा old_iसमयrspec32 __user *uits);
बाह्य पूर्णांक put_old_iसमयrspec32(स्थिर काष्ठा iसमयrspec64 *its,
			काष्ठा old_iसमयrspec32 __user *uits);
काष्ठा __kernel_समयx;
पूर्णांक get_old_समयx32(काष्ठा __kernel_समयx *, स्थिर काष्ठा old_समयx32 __user *);
पूर्णांक put_old_समयx32(काष्ठा old_समयx32 __user *, स्थिर काष्ठा __kernel_समयx *);

/**
 * ns_to_kernel_old_समयval - Convert nanoseconds to समयval
 * @nsec:	the nanoseconds value to be converted
 *
 * Returns the समयval representation of the nsec parameter.
 */
बाह्य काष्ठा __kernel_old_समयval ns_to_kernel_old_समयval(s64 nsec);

#पूर्ण_अगर
