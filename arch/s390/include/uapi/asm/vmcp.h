<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright IBM Corp. 2004, 2005
 * Interface implementation क्रम communication with the z/VM control program
 * Version 1.0
 * Author(s): Christian Borntraeger <cborntra@de.ibm.com>
 *
 *
 * z/VMs CP offers the possibility to issue commands via the diagnose code 8
 * this driver implements a अक्षरacter device that issues these commands and
 * वापसs the answer of CP.
 *
 * The idea of this driver is based on cpपूर्णांक from Neale Ferguson
 */

#अगर_अघोषित _UAPI_ASM_VMCP_H
#घोषणा _UAPI_ASM_VMCP_H

#समावेश <linux/ioctl.h>

#घोषणा VMCP_GETCODE	_IOR(0x10, 1, पूर्णांक)
#घोषणा VMCP_SETBUF	_IOW(0x10, 2, पूर्णांक)
#घोषणा VMCP_GETSIZE	_IOR(0x10, 3, पूर्णांक)

#पूर्ण_अगर /* _UAPI_ASM_VMCP_H */
