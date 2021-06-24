<शैली गुरु>
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
#अगर_अघोषित _ASM_X86_MTRR_H
#घोषणा _ASM_X86_MTRR_H

#समावेश <uapi/यंत्र/mtrr.h>
#समावेश <यंत्र/memtype.h>


/*
 * The following functions are क्रम use by other drivers that cannot use
 * arch_phys_wc_add and arch_phys_wc_del.
 */
# अगरdef CONFIG_MTRR
बाह्य u8 mtrr_type_lookup(u64 addr, u64 end, u8 *unअगरorm);
बाह्य व्योम mtrr_save_fixed_ranges(व्योम *);
बाह्य व्योम mtrr_save_state(व्योम);
बाह्य पूर्णांक mtrr_add(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
		    अचिन्हित पूर्णांक type, bool increment);
बाह्य पूर्णांक mtrr_add_page(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
			 अचिन्हित पूर्णांक type, bool increment);
बाह्य पूर्णांक mtrr_del(पूर्णांक reg, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size);
बाह्य पूर्णांक mtrr_del_page(पूर्णांक reg, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size);
बाह्य व्योम mtrr_centaur_report_mcr(पूर्णांक mcr, u32 lo, u32 hi);
बाह्य व्योम mtrr_ap_init(व्योम);
बाह्य व्योम mtrr_bp_init(व्योम);
बाह्य व्योम set_mtrr_aps_delayed_init(व्योम);
बाह्य व्योम mtrr_aps_init(व्योम);
बाह्य व्योम mtrr_bp_restore(व्योम);
बाह्य पूर्णांक mtrr_trim_uncached_memory(अचिन्हित दीर्घ end_pfn);
बाह्य पूर्णांक amd_special_शेष_mtrr(व्योम);
#  अन्यथा
अटल अंतरभूत u8 mtrr_type_lookup(u64 addr, u64 end, u8 *unअगरorm)
अणु
	/*
	 * Return no-MTRRs:
	 */
	वापस MTRR_TYPE_INVALID;
पूर्ण
#घोषणा mtrr_save_fixed_ranges(arg) करो अणुपूर्ण जबतक (0)
#घोषणा mtrr_save_state() करो अणुपूर्ण जबतक (0)
अटल अंतरभूत पूर्णांक mtrr_add(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
			   अचिन्हित पूर्णांक type, bool increment)
अणु
    वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक mtrr_add_page(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
				अचिन्हित पूर्णांक type, bool increment)
अणु
    वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक mtrr_del(पूर्णांक reg, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
    वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक mtrr_del_page(पूर्णांक reg, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
    वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक mtrr_trim_uncached_memory(अचिन्हित दीर्घ end_pfn)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम mtrr_centaur_report_mcr(पूर्णांक mcr, u32 lo, u32 hi)
अणु
पूर्ण
अटल अंतरभूत व्योम mtrr_bp_init(व्योम)
अणु
	pat_disable("PAT support disabled because CONFIG_MTRR is disabled in the kernel.");
पूर्ण

#घोषणा mtrr_ap_init() करो अणुपूर्ण जबतक (0)
#घोषणा set_mtrr_aps_delayed_init() करो अणुपूर्ण जबतक (0)
#घोषणा mtrr_aps_init() करो अणुपूर्ण जबतक (0)
#घोषणा mtrr_bp_restore() करो अणुपूर्ण जबतक (0)
#  endअगर

#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>

काष्ठा mtrr_sentry32 अणु
    compat_uदीर्घ_t base;    /*  Base address     */
    compat_uपूर्णांक_t size;    /*  Size of region   */
    compat_uपूर्णांक_t type;     /*  Type of region   */
पूर्ण;

काष्ठा mtrr_gentry32 अणु
    compat_uदीर्घ_t regnum;   /*  Register number  */
    compat_uपूर्णांक_t base;    /*  Base address     */
    compat_uपूर्णांक_t size;    /*  Size of region   */
    compat_uपूर्णांक_t type;     /*  Type of region   */
पूर्ण;

#घोषणा MTRR_IOCTL_BASE 'M'

#घोषणा MTRRIOC32_ADD_ENTRY      _IOW(MTRR_IOCTL_BASE,  0, काष्ठा mtrr_sentry32)
#घोषणा MTRRIOC32_SET_ENTRY      _IOW(MTRR_IOCTL_BASE,  1, काष्ठा mtrr_sentry32)
#घोषणा MTRRIOC32_DEL_ENTRY      _IOW(MTRR_IOCTL_BASE,  2, काष्ठा mtrr_sentry32)
#घोषणा MTRRIOC32_GET_ENTRY      _IOWR(MTRR_IOCTL_BASE, 3, काष्ठा mtrr_gentry32)
#घोषणा MTRRIOC32_KILL_ENTRY     _IOW(MTRR_IOCTL_BASE,  4, काष्ठा mtrr_sentry32)
#घोषणा MTRRIOC32_ADD_PAGE_ENTRY _IOW(MTRR_IOCTL_BASE,  5, काष्ठा mtrr_sentry32)
#घोषणा MTRRIOC32_SET_PAGE_ENTRY _IOW(MTRR_IOCTL_BASE,  6, काष्ठा mtrr_sentry32)
#घोषणा MTRRIOC32_DEL_PAGE_ENTRY _IOW(MTRR_IOCTL_BASE,  7, काष्ठा mtrr_sentry32)
#घोषणा MTRRIOC32_GET_PAGE_ENTRY _IOWR(MTRR_IOCTL_BASE, 8, काष्ठा mtrr_gentry32)
#घोषणा MTRRIOC32_KILL_PAGE_ENTRY		\
				 _IOW(MTRR_IOCTL_BASE,  9, काष्ठा mtrr_sentry32)
#पूर्ण_अगर /* CONFIG_COMPAT */

/* Bit fields क्रम enabled in काष्ठा mtrr_state_type */
#घोषणा MTRR_STATE_MTRR_FIXED_ENABLED	0x01
#घोषणा MTRR_STATE_MTRR_ENABLED		0x02

#पूर्ण_अगर /* _ASM_X86_MTRR_H */
