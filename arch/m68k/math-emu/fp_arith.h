<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*

   fp_arith.h: भग्नing-poपूर्णांक math routines क्रम the Linux-m68k
   भग्नing poपूर्णांक emulator.

   Copyright (c) 1998 David Huggins-Daines.

   Somewhat based on the AlphaLinux भग्नing poपूर्णांक emulator, by David
   Mosberger-Tang.


 */

#अगर_अघोषित FP_ARITH_H
#घोषणा FP_ARITH_H

/* easy ones */
काष्ठा fp_ext *
fp_भ_असल(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_fneg(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);

/* straightक्रमward arithmetic */
काष्ठा fp_ext *
fp_fadd(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_fsub(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_fcmp(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_ftst(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_fmul(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_fभाग(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);

/* ones that करो rounding and पूर्णांकeger conversions */
काष्ठा fp_ext *
fp_भ_शेष(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_frem(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_fपूर्णांक(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_fपूर्णांकrz(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);
काष्ठा fp_ext *
fp_fscale(काष्ठा fp_ext *dest, काष्ठा fp_ext *src);

#पूर्ण_अगर	/* FP_ARITH__H */
