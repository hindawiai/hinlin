<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2020 Christoph Hellwig.
 *
 * Support क्रम "universal" poपूर्णांकers that can poपूर्णांक to either kernel or userspace
 * memory.
 */
#अगर_अघोषित _LINUX_SOCKPTR_H
#घोषणा _LINUX_SOCKPTR_H

#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

प्रकार काष्ठा अणु
	जोड़ अणु
		व्योम		*kernel;
		व्योम __user	*user;
	पूर्ण;
	bool		is_kernel : 1;
पूर्ण sockptr_t;

अटल अंतरभूत bool sockptr_is_kernel(sockptr_t sockptr)
अणु
	वापस sockptr.is_kernel;
पूर्ण

अटल अंतरभूत sockptr_t KERNEL_SOCKPTR(व्योम *p)
अणु
	वापस (sockptr_t) अणु .kernel = p, .is_kernel = true पूर्ण;
पूर्ण

अटल अंतरभूत sockptr_t USER_SOCKPTR(व्योम __user *p)
अणु
	वापस (sockptr_t) अणु .user = p पूर्ण;
पूर्ण

अटल अंतरभूत bool sockptr_is_null(sockptr_t sockptr)
अणु
	अगर (sockptr_is_kernel(sockptr))
		वापस !sockptr.kernel;
	वापस !sockptr.user;
पूर्ण

अटल अंतरभूत पूर्णांक copy_from_sockptr_offset(व्योम *dst, sockptr_t src,
		माप_प्रकार offset, माप_प्रकार size)
अणु
	अगर (!sockptr_is_kernel(src))
		वापस copy_from_user(dst, src.user + offset, size);
	स_नकल(dst, src.kernel + offset, size);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक copy_from_sockptr(व्योम *dst, sockptr_t src, माप_प्रकार size)
अणु
	वापस copy_from_sockptr_offset(dst, src, 0, size);
पूर्ण

अटल अंतरभूत पूर्णांक copy_to_sockptr_offset(sockptr_t dst, माप_प्रकार offset,
		स्थिर व्योम *src, माप_प्रकार size)
अणु
	अगर (!sockptr_is_kernel(dst))
		वापस copy_to_user(dst.user + offset, src, size);
	स_नकल(dst.kernel + offset, src, size);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *memdup_sockptr(sockptr_t src, माप_प्रकार len)
अणु
	व्योम *p = kदो_स्मृति_track_caller(len, GFP_USER | __GFP_NOWARN);

	अगर (!p)
		वापस ERR_PTR(-ENOMEM);
	अगर (copy_from_sockptr(p, src, len)) अणु
		kमुक्त(p);
		वापस ERR_PTR(-EFAULT);
	पूर्ण
	वापस p;
पूर्ण

अटल अंतरभूत व्योम *memdup_sockptr_nul(sockptr_t src, माप_प्रकार len)
अणु
	अक्षर *p = kदो_स्मृति_track_caller(len + 1, GFP_KERNEL);

	अगर (!p)
		वापस ERR_PTR(-ENOMEM);
	अगर (copy_from_sockptr(p, src, len)) अणु
		kमुक्त(p);
		वापस ERR_PTR(-EFAULT);
	पूर्ण
	p[len] = '\0';
	वापस p;
पूर्ण

अटल अंतरभूत दीर्घ म_नकलन_from_sockptr(अक्षर *dst, sockptr_t src, माप_प्रकार count)
अणु
	अगर (sockptr_is_kernel(src)) अणु
		माप_प्रकार len = min(strnlen(src.kernel, count - 1) + 1, count);

		स_नकल(dst, src.kernel, len);
		वापस len;
	पूर्ण
	वापस म_नकलन_from_user(dst, src.user, count);
पूर्ण

#पूर्ण_अगर /* _LINUX_SOCKPTR_H */
