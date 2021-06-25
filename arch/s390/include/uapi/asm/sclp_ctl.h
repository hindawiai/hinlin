<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * IOCTL पूर्णांकerface क्रम SCLP
 *
 * Copyright IBM Corp. 2012
 *
 * Author: Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ASM_SCLP_CTL_H
#घोषणा _ASM_SCLP_CTL_H

#समावेश <linux/types.h>

काष्ठा sclp_ctl_sccb अणु
	__u32	cmdw;
	__u64	sccb;
पूर्ण __attribute__((packed));

#घोषणा SCLP_CTL_IOCTL_MAGIC 0x10

#घोषणा SCLP_CTL_SCCB \
	_IOWR(SCLP_CTL_IOCTL_MAGIC, 0x10, काष्ठा sclp_ctl_sccb)

#पूर्ण_अगर
