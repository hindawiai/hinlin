<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Kernel पूर्णांकerface क्रम the s390 arch_अक्रमom_* functions
 *
 * Copyright IBM Corp. 2017, 2020
 *
 * Author: Harald Freudenberger <freude@de.ibm.com>
 *
 */

#अगर_अघोषित _ASM_S390_ARCHRANDOM_H
#घोषणा _ASM_S390_ARCHRANDOM_H

#अगर_घोषित CONFIG_ARCH_RANDOM

#समावेश <linux/अटल_key.h>
#समावेश <linux/atomic.h>

DECLARE_STATIC_KEY_FALSE(s390_arch_अक्रमom_available);
बाह्य atomic64_t s390_arch_अक्रमom_counter;

bool s390_arch_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v);
bool s390_arch_अक्रमom_generate(u8 *buf, अचिन्हित पूर्णांक nbytes);

अटल अंतरभूत bool __must_check arch_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	अगर (अटल_branch_likely(&s390_arch_अक्रमom_available))
		वापस s390_arch_get_अक्रमom_दीर्घ(v);
	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	अगर (अटल_branch_likely(&s390_arch_अक्रमom_available)) अणु
		वापस s390_arch_अक्रमom_generate((u8 *)v, माप(*v));
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	अगर (अटल_branch_likely(&s390_arch_अक्रमom_available)) अणु
		वापस s390_arch_अक्रमom_generate((u8 *)v, माप(*v));
	पूर्ण
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_ARCH_RANDOM */
#पूर्ण_अगर /* _ASM_S390_ARCHRANDOM_H */
