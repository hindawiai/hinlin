<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.0+ WITH Linux-syscall-note */
/*  Generic MTRR (Memory Type Range Register) ioctls.

    Copyright (C) 1997-1999  Riअक्षरd Gooch

    This library is मुक्त software; you can redistribute it and/or
    modअगरy it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License क्रम more details.

    You should have received a copy of the GNU Library General Public
    License aदीर्घ with this library; अगर not, ग_लिखो to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    Riअक्षरd Gooch may be reached by email at  rgooch@atnf.csiro.au
    The postal address is:
      Riअक्षरd Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Australia.
*/
#अगर_अघोषित _UAPI_ASM_X86_MTRR_H
#घोषणा _UAPI_ASM_X86_MTRR_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/त्रुटिसं.स>

#घोषणा	MTRR_IOCTL_BASE	'M'

/* Warning: this काष्ठाure has a dअगरferent order from i386
   on x86-64. The 32bit emulation code takes care of that.
   But you need to use this क्रम 64bit, otherwise your X server
   will अवरोध. */

#अगर_घोषित __i386__
काष्ठा mtrr_sentry अणु
    अचिन्हित दीर्घ base;    /*  Base address     */
    अचिन्हित पूर्णांक size;    /*  Size of region   */
    अचिन्हित पूर्णांक type;     /*  Type of region   */
पूर्ण;

काष्ठा mtrr_gentry अणु
    अचिन्हित पूर्णांक regnum;   /*  Register number  */
    अचिन्हित दीर्घ base;    /*  Base address     */
    अचिन्हित पूर्णांक size;    /*  Size of region   */
    अचिन्हित पूर्णांक type;     /*  Type of region   */
पूर्ण;

#अन्यथा /* __i386__ */

काष्ठा mtrr_sentry अणु
	__u64 base;		/*  Base address     */
	__u32 size;		/*  Size of region   */
	__u32 type;		/*  Type of region   */
पूर्ण;

काष्ठा mtrr_gentry अणु
	__u64 base;		/*  Base address     */
	__u32 size;		/*  Size of region   */
	__u32 regnum;		/*  Register number  */
	__u32 type;		/*  Type of region   */
	__u32 _pad;		/*  Unused	     */
पूर्ण;

#पूर्ण_अगर /* !__i386__ */

काष्ठा mtrr_var_range अणु
	__u32 base_lo;
	__u32 base_hi;
	__u32 mask_lo;
	__u32 mask_hi;
पूर्ण;

/* In the Intel processor's MTRR पूर्णांकerface, the MTRR type is always held in
   an 8 bit field: */
प्रकार __u8 mtrr_type;

#घोषणा MTRR_NUM_FIXED_RANGES 88
#घोषणा MTRR_MAX_VAR_RANGES 256

काष्ठा mtrr_state_type अणु
	काष्ठा mtrr_var_range var_ranges[MTRR_MAX_VAR_RANGES];
	mtrr_type fixed_ranges[MTRR_NUM_FIXED_RANGES];
	अचिन्हित अक्षर enabled;
	अचिन्हित अक्षर have_fixed;
	mtrr_type def_type;
पूर्ण;

#घोषणा MTRRphysBase_MSR(reg) (0x200 + 2 * (reg))
#घोषणा MTRRphysMask_MSR(reg) (0x200 + 2 * (reg) + 1)

/*  These are the various ioctls  */
#घोषणा MTRRIOC_ADD_ENTRY        _IOW(MTRR_IOCTL_BASE,  0, काष्ठा mtrr_sentry)
#घोषणा MTRRIOC_SET_ENTRY        _IOW(MTRR_IOCTL_BASE,  1, काष्ठा mtrr_sentry)
#घोषणा MTRRIOC_DEL_ENTRY        _IOW(MTRR_IOCTL_BASE,  2, काष्ठा mtrr_sentry)
#घोषणा MTRRIOC_GET_ENTRY        _IOWR(MTRR_IOCTL_BASE, 3, काष्ठा mtrr_gentry)
#घोषणा MTRRIOC_KILL_ENTRY       _IOW(MTRR_IOCTL_BASE,  4, काष्ठा mtrr_sentry)
#घोषणा MTRRIOC_ADD_PAGE_ENTRY   _IOW(MTRR_IOCTL_BASE,  5, काष्ठा mtrr_sentry)
#घोषणा MTRRIOC_SET_PAGE_ENTRY   _IOW(MTRR_IOCTL_BASE,  6, काष्ठा mtrr_sentry)
#घोषणा MTRRIOC_DEL_PAGE_ENTRY   _IOW(MTRR_IOCTL_BASE,  7, काष्ठा mtrr_sentry)
#घोषणा MTRRIOC_GET_PAGE_ENTRY   _IOWR(MTRR_IOCTL_BASE, 8, काष्ठा mtrr_gentry)
#घोषणा MTRRIOC_KILL_PAGE_ENTRY  _IOW(MTRR_IOCTL_BASE,  9, काष्ठा mtrr_sentry)

/* MTRR memory types, which are defined in SDM */
#घोषणा MTRR_TYPE_UNCACHABLE 0
#घोषणा MTRR_TYPE_WRCOMB     1
/*#घोषणा MTRR_TYPE_         2*/
/*#घोषणा MTRR_TYPE_         3*/
#घोषणा MTRR_TYPE_WRTHROUGH  4
#घोषणा MTRR_TYPE_WRPROT     5
#घोषणा MTRR_TYPE_WRBACK     6
#घोषणा MTRR_NUM_TYPES       7

/*
 * Invalid MTRR memory type.  mtrr_type_lookup() वापसs this value when
 * MTRRs are disabled.  Note, this value is allocated from the reserved
 * values (0x7-0xff) of the MTRR memory types.
 */
#घोषणा MTRR_TYPE_INVALID    0xff

#पूर्ण_अगर /* _UAPI_ASM_X86_MTRR_H */
