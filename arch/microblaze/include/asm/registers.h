<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_REGISTERS_H
#घोषणा _ASM_MICROBLAZE_REGISTERS_H

#घोषणा MSR_BE	(1<<0) /* 0x001 */
#घोषणा MSR_IE	(1<<1) /* 0x002 */
#घोषणा MSR_C	(1<<2) /* 0x004 */
#घोषणा MSR_BIP	(1<<3) /* 0x008 */
#घोषणा MSR_FSL	(1<<4) /* 0x010 */
#घोषणा MSR_ICE	(1<<5) /* 0x020 */
#घोषणा MSR_DZ	(1<<6) /* 0x040 */
#घोषणा MSR_DCE	(1<<7) /* 0x080 */
#घोषणा MSR_EE	(1<<8) /* 0x100 */
#घोषणा MSR_EIP	(1<<9) /* 0x200 */
#घोषणा MSR_CC	(1<<31)

/* Floating Poपूर्णांक Status Register (FSR) Bits */
#घोषणा FSR_IO		(1<<4) /* Invalid operation */
#घोषणा FSR_DZ		(1<<3) /* Divide-by-zero */
#घोषणा FSR_OF		(1<<2) /* Overflow */
#घोषणा FSR_UF		(1<<1) /* Underflow */
#घोषणा FSR_DO		(1<<0) /* Denormalized opeअक्रम error */

/* Machine State Register (MSR) Fields */
# define MSR_UM		(1<<11) /* User Mode */
# define MSR_UMS	(1<<12) /* User Mode Save */
# define MSR_VM		(1<<13) /* Virtual Mode */
# define MSR_VMS	(1<<14) /* Virtual Mode Save */

# define MSR_KERNEL	(MSR_EE | MSR_VM)
/* # define MSR_USER	(MSR_KERNEL | MSR_UM | MSR_IE) */
# define MSR_KERNEL_VMS	(MSR_EE | MSR_VMS)
/* # define MSR_USER_VMS	(MSR_KERNEL_VMS | MSR_UMS | MSR_IE) */

/* Exception State Register (ESR) Fields */
# define	  ESR_DIZ	(1<<11) /* Zone Protection */
# define	  ESR_S		(1<<10) /* Store inकाष्ठाion */

#पूर्ण_अगर /* _ASM_MICROBLAZE_REGISTERS_H */
