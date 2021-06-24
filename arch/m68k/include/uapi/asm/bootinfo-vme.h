<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
** यंत्र/bootinfo-vme.h -- VME-specअगरic boot inक्रमmation definitions
*/

#अगर_अघोषित _UAPI_ASM_M68K_BOOTINFO_VME_H
#घोषणा _UAPI_ASM_M68K_BOOTINFO_VME_H


#समावेश <linux/types.h>


    /*
     *  VME-specअगरic tags
     */

#घोषणा BI_VME_TYPE		0x8000	/* VME sub-architecture (__be32) */
#घोषणा BI_VME_BRDINFO		0x8001	/* VME board inक्रमmation (काष्ठा) */


    /*
     *  VME models (BI_VME_TYPE)
     */

#घोषणा VME_TYPE_TP34V		0x0034	/* Tadpole TP34V */
#घोषणा VME_TYPE_MVME147	0x0147	/* Motorola MVME147 */
#घोषणा VME_TYPE_MVME162	0x0162	/* Motorola MVME162 */
#घोषणा VME_TYPE_MVME166	0x0166	/* Motorola MVME166 */
#घोषणा VME_TYPE_MVME167	0x0167	/* Motorola MVME167 */
#घोषणा VME_TYPE_MVME172	0x0172	/* Motorola MVME172 */
#घोषणा VME_TYPE_MVME177	0x0177	/* Motorola MVME177 */
#घोषणा VME_TYPE_BVME4000	0x4000	/* BVM Ltd. BVME4000 */
#घोषणा VME_TYPE_BVME6000	0x6000	/* BVM Ltd. BVME6000 */


#अगर_अघोषित __ASSEMBLY__

/*
 * Board ID data काष्ठाure - poपूर्णांकer to this retrieved from Bug by head.S
 *
 * BI_VME_BRDINFO is a 32 byte काष्ठा as वापसed by the Bug code on
 * Motorola VME boards.  Contains board number, Bug version, board
 * configuration options, etc.
 *
 * Note, bytes 12 and 13 are board no in BCD (0162,0166,0167,0177,etc)
 */

प्रकार काष्ठा अणु
	अक्षर	bdid[4];
	__u8	rev, mth, day, yr;
	__be16	size, reserved;
	__be16	brdno;
	अक्षर	brdsuffix[2];
	__be32	options;
	__be16	clun, dlun, ctype, dnum;
	__be32	option2;
पूर्ण t_bdid, *p_bdid;

#पूर्ण_अगर /* __ASSEMBLY__ */


    /*
     *  Latest VME bootinfo versions
     */

#घोषणा MVME147_BOOTI_VERSION	MK_BI_VERSION(2, 0)
#घोषणा MVME16x_BOOTI_VERSION	MK_BI_VERSION(2, 0)
#घोषणा BVME6000_BOOTI_VERSION	MK_BI_VERSION(2, 0)


#पूर्ण_अगर /* _UAPI_ASM_M68K_BOOTINFO_VME_H */
