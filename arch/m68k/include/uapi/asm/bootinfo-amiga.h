<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
** यंत्र/bootinfo-amiga.h -- Amiga-specअगरic boot inक्रमmation definitions
*/

#अगर_अघोषित _UAPI_ASM_M68K_BOOTINFO_AMIGA_H
#घोषणा _UAPI_ASM_M68K_BOOTINFO_AMIGA_H


    /*
     *  Amiga-specअगरic tags
     */

#घोषणा BI_AMIGA_MODEL		0x8000	/* model (__be32) */
#घोषणा BI_AMIGA_AUTOCON	0x8001	/* AutoConfig device */
					/* (AmigaOS काष्ठा ConfigDev) */
#घोषणा BI_AMIGA_CHIP_SIZE	0x8002	/* size of Chip RAM (__be32) */
#घोषणा BI_AMIGA_VBLANK		0x8003	/* VBLANK frequency (__u8) */
#घोषणा BI_AMIGA_PSFREQ		0x8004	/* घातer supply frequency (__u8) */
#घोषणा BI_AMIGA_ECLOCK		0x8005	/* EClock frequency (__be32) */
#घोषणा BI_AMIGA_CHIPSET	0x8006	/* native chipset present (__be32) */
#घोषणा BI_AMIGA_SERPER		0x8007	/* serial port period (__be16) */


    /*
     *  Amiga models (BI_AMIGA_MODEL)
     */

#घोषणा AMI_UNKNOWN		0
#घोषणा AMI_500			1
#घोषणा AMI_500PLUS		2
#घोषणा AMI_600			3
#घोषणा AMI_1000		4
#घोषणा AMI_1200		5
#घोषणा AMI_2000		6
#घोषणा AMI_2500		7
#घोषणा AMI_3000		8
#घोषणा AMI_3000T		9
#घोषणा AMI_3000PLUS		10
#घोषणा AMI_4000		11
#घोषणा AMI_4000T		12
#घोषणा AMI_CDTV		13
#घोषणा AMI_CD32		14
#घोषणा AMI_DRACO		15


    /*
     *  Amiga chipsets (BI_AMIGA_CHIPSET)
     */

#घोषणा CS_STONEAGE		0
#घोषणा CS_OCS			1
#घोषणा CS_ECS			2
#घोषणा CS_AGA			3


    /*
     *  Latest Amiga bootinfo version
     */

#घोषणा AMIGA_BOOTI_VERSION	MK_BI_VERSION(2, 0)


#पूर्ण_अगर /* _UAPI_ASM_M68K_BOOTINFO_AMIGA_H */
