<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_IA64_MMIOWB_H
#घोषणा _ASM_IA64_MMIOWB_H

/**
 * mmiowb - I/O ग_लिखो barrier
 *
 * Ensure ordering of I/O space ग_लिखोs.  This will make sure that ग_लिखोs
 * following the barrier will arrive after all previous ग_लिखोs.  For most
 * ia64 platक्रमms, this is a simple 'mf.a' inकाष्ठाion.
 */
#घोषणा mmiowb()	ia64_mfa()

#समावेश <यंत्र-generic/mmiowb.h>

#पूर्ण_अगर	/* _ASM_IA64_MMIOWB_H */
