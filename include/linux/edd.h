<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/include/linux/edd.h
 *  Copyright (C) 2002, 2003, 2004 Dell Inc.
 *  by Matt Domsch <Matt_Domsch@dell.com>
 *
 * काष्ठाures and definitions क्रम the पूर्णांक 13h, ax=अणु41,48पूर्णh
 * BIOS Enhanced Disk Drive Services
 * This is based on the T13 group करोcument D1572 Revision 0 (August 14 2002)
 * available at http://www.t13.org/करोcs2002/d1572r0.pdf.  It is
 * very similar to D1484 Revision 3 http://www.t13.org/करोcs2002/d1484r3.pdf
 *
 * In a nutshell, arch/अणुi386,x86_64पूर्ण/boot/setup.S populates a scratch
 * table in the boot_params that contains a list of BIOS-क्रमागतerated
 * boot devices.
 * In arch/अणुi386,x86_64पूर्ण/kernel/setup.c, this inक्रमmation is
 * transferred पूर्णांकo the edd काष्ठाure, and in drivers/firmware/edd.c, that
 * inक्रमmation is used to identअगरy BIOS boot disk.  The code in setup.S
 * is very sensitive to the size of these काष्ठाures.
 */
#अगर_अघोषित _LINUX_EDD_H
#घोषणा _LINUX_EDD_H

#समावेश <uapi/linux/edd.h>

#अगर_अघोषित __ASSEMBLY__
बाह्य काष्ठा edd edd;
#पूर्ण_अगर				/*!__ASSEMBLY__ */
#पूर्ण_अगर				/* _LINUX_EDD_H */
