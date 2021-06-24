<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_A_OUT_H__
#घोषणा __ALPHA_A_OUT_H__

#समावेश <uapi/यंत्र/a.out.h>


/* Assume that start addresses below 4G beदीर्घ to a TASO application.
   Unक्रमtunately, there is no proper bit in the exec header to check.
   Worse, we have to notice the start address beक्रमe swapping to use
   /sbin/loader, which of course is _not_ a TASO application.  */
#घोषणा SET_AOUT_PERSONALITY(BFPM, EX) \
	set_personality (((BFPM->taso || EX.ah.entry < 0x100000000L \
			   ? ADDR_LIMIT_32BIT : 0) | PER_OSF4))

#पूर्ण_अगर /* __A_OUT_GNU_H__ */
