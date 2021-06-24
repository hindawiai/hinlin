<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  BSD Process Accounting क्रम Linux - Definitions
 *
 *  Author: Marco van Wieringen (mvw@planets.elm.net)
 *
 *  This header file contains the definitions needed to implement
 *  BSD-style process accounting. The kernel accounting code and all
 *  user-level programs that try to करो something useful with the
 *  process accounting log must include this file.
 *
 *  Copyright (C) 1995 - 1997 Marco van Wieringen - ELM Consultancy B.V.
 *
 */
#अगर_अघोषित _LINUX_ACCT_H
#घोषणा _LINUX_ACCT_H

#समावेश <uapi/linux/acct.h>



#अगर_घोषित CONFIG_BSD_PROCESS_ACCT
काष्ठा pid_namespace;
बाह्य पूर्णांक acct_parm[]; /* क्रम sysctl */
बाह्य व्योम acct_collect(दीर्घ निकासcode, पूर्णांक group_dead);
बाह्य व्योम acct_process(व्योम);
बाह्य व्योम acct_निकास_ns(काष्ठा pid_namespace *);
#अन्यथा
#घोषणा acct_collect(x,y)	करो अणु पूर्ण जबतक (0)
#घोषणा acct_process()		करो अणु पूर्ण जबतक (0)
#घोषणा acct_निकास_ns(ns)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * ACCT_VERSION numbers as yet defined:
 * 0: old क्रमmat (until 2.6.7) with 16 bit uid/gid
 * 1: extended variant (binary compatible on M68K)
 * 2: extended variant (binary compatible on everything except M68K)
 * 3: new binary incompatible क्रमmat (64 bytes)
 * 4: new binary incompatible क्रमmat (128 bytes)
 * 5: new binary incompatible क्रमmat (128 bytes, second half)
 *
 */

#अघोषित ACCT_VERSION
#अघोषित AHZ

#अगर_घोषित CONFIG_BSD_PROCESS_ACCT_V3
#घोषणा ACCT_VERSION	3
#घोषणा AHZ		100
प्रकार काष्ठा acct_v3 acct_t;
#अन्यथा
#अगर_घोषित CONFIG_M68K
#घोषणा ACCT_VERSION	1
#अन्यथा
#घोषणा ACCT_VERSION	2
#पूर्ण_अगर
#घोषणा AHZ		(USER_HZ)
प्रकार काष्ठा acct acct_t;
#पूर्ण_अगर

#समावेश <linux/jअगरfies.h>
/*
 * Yet another set of HZ to *HZ helper functions.
 * See <linux/jअगरfies.h> क्रम the original.
 */

अटल अंतरभूत u32 jअगरfies_to_AHZ(अचिन्हित दीर्घ x)
अणु
#अगर (TICK_NSEC % (NSEC_PER_SEC / AHZ)) == 0
# अगर HZ < AHZ
	वापस x * (AHZ / HZ);
# अन्यथा
	वापस x / (HZ / AHZ);
# endअगर
#अन्यथा
        u64 पंचांगp = (u64)x * TICK_NSEC;
        करो_भाग(पंचांगp, (NSEC_PER_SEC / AHZ));
        वापस (दीर्घ)पंचांगp;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u64 nsec_to_AHZ(u64 x)
अणु
#अगर (NSEC_PER_SEC % AHZ) == 0
	करो_भाग(x, (NSEC_PER_SEC / AHZ));
#या_अगर (AHZ % 512) == 0
	x *= AHZ/512;
	करो_भाग(x, (NSEC_PER_SEC / 512));
#अन्यथा
	/*
         * max relative error 5.7e-8 (1.8s per year) क्रम AHZ <= 1024,
         * overflow after 64.99 years.
         * exact क्रम AHZ=60, 72, 90, 120, 144, 180, 300, 600, 900, ...
         */
	x *= 9;
	करो_भाग(x, (अचिन्हित दीर्घ)((9ull * NSEC_PER_SEC + (AHZ/2))
	                          / AHZ));
#पूर्ण_अगर
	वापस x;
पूर्ण

#पूर्ण_अगर	/* _LINUX_ACCT_H */
