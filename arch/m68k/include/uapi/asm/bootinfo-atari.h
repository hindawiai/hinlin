<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
** यंत्र/bootinfo-atari.h -- Atari-specअगरic boot inक्रमmation definitions
*/

#अगर_अघोषित _UAPI_ASM_M68K_BOOTINFO_ATARI_H
#घोषणा _UAPI_ASM_M68K_BOOTINFO_ATARI_H


    /*
     *  Atari-specअगरic tags
     */

#घोषणा BI_ATARI_MCH_COOKIE	0x8000	/* _MCH cookie from TOS (__be32) */
#घोषणा BI_ATARI_MCH_TYPE	0x8001	/* special machine type (__be32) */


    /*
     *  mch_cookie values (upper word of BI_ATARI_MCH_COOKIE)
     */

#घोषणा ATARI_MCH_ST		0
#घोषणा ATARI_MCH_STE		1
#घोषणा ATARI_MCH_TT		2
#घोषणा ATARI_MCH_FALCON	3


    /*
     *  Atari machine types (BI_ATARI_MCH_TYPE)
     */

#घोषणा ATARI_MACH_NORMAL	0	/* no special machine type */
#घोषणा ATARI_MACH_MEDUSA	1	/* Medusa 040 */
#घोषणा ATARI_MACH_HADES	2	/* Hades 040 or 060 */
#घोषणा ATARI_MACH_AB40		3	/* Afterburner040 on Falcon */


    /*
     *  Latest Atari bootinfo version
     */

#घोषणा ATARI_BOOTI_VERSION	MK_BI_VERSION(2, 1)


#पूर्ण_अगर /* _UAPI_ASM_M68K_BOOTINFO_ATARI_H */
