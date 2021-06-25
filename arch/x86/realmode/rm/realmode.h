<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_X86_REALMODE_RM_REALMODE_H
#घोषणा ARCH_X86_REALMODE_RM_REALMODE_H

#अगर_घोषित __ASSEMBLY__

/*
 * 16-bit ljmpw to the real_mode_seg
 *
 * This must be खोलो-coded since gas will choke on using a
 * relocatable symbol क्रम the segment portion.
 */
#घोषणा LJMPW_RM(to)	.byte 0xea ; .word (to), real_mode_seg

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Signature at the end of the realmode region
 */
#घोषणा REALMODE_END_SIGNATURE	0x65a22c82

#पूर्ण_अगर /* ARCH_X86_REALMODE_RM_REALMODE_H */
