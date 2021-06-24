<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * System calls under the Sparc.
 *
 * Don't be scared by the ugly clobbers, it is the only way I can
 * think of right now to क्रमce the arguments पूर्णांकo fixed रेजिस्टरs
 * beक्रमe the trap पूर्णांकo the प्रणाली call with gcc 'asm' statements.
 *
 * Copyright (C) 1995, 2007 David S. Miller (davem@davemloft.net)
 *
 * SunOS compatibility based upon preliminary work which is:
 *
 * Copyright (C) 1995 Adrian M. Rodriguez (adrian@remus.rutgers.edu)
 */
#अगर_अघोषित _UAPI_SPARC_UNISTD_H
#घोषणा _UAPI_SPARC_UNISTD_H

#अगर_अघोषित __32bit_syscall_numbers__
#अगर_अघोषित __arch64__
#घोषणा __32bit_syscall_numbers__
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __arch64__
#समावेश <यंत्र/unistd_64.h>
#अन्यथा
#समावेश <यंत्र/unistd_32.h>
#पूर्ण_अगर

/* Biपंचांगask values वापसed from kern_features प्रणाली call.  */
#घोषणा KERN_FEATURE_MIXED_MODE_STACK	0x00000001

#पूर्ण_अगर /* _UAPI_SPARC_UNISTD_H */
