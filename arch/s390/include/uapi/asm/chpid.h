<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *    Copyright IBM Corp. 2007, 2012
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#अगर_अघोषित _UAPI_ASM_S390_CHPID_H
#घोषणा _UAPI_ASM_S390_CHPID_H

#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#घोषणा __MAX_CHPID 255

काष्ठा chp_id अणु
	__u8 reserved1;
	__u8 cssid;
	__u8 reserved2;
	__u8 id;
पूर्ण __attribute__((packed));


#पूर्ण_अगर /* _UAPI_ASM_S390_CHPID_H */
