<शैली गुरु>
/*
 * Licensed under the GPL
 */

#अगर_अघोषित __UM_SYSDEP_CHECKSUM_H
#घोषणा __UM_SYSDEP_CHECKSUM_H

अटल अंतरभूत अचिन्हित add32_with_carry(अचिन्हित a, अचिन्हित b)
अणु
        यंत्र("addl %2,%0\n\t"
            "adcl $0,%0"
            : "=r" (a)
            : "0" (a), "r" (b));
        वापस a;
पूर्ण

बाह्य __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len);

#पूर्ण_अगर
