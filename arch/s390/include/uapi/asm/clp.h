<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ioctl पूर्णांकerface क्रम /dev/clp
 *
 * Copyright IBM Corp. 2016
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _ASM_CLP_H
#घोषणा _ASM_CLP_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

काष्ठा clp_req अणु
	अचिन्हित पूर्णांक c : 1;
	अचिन्हित पूर्णांक r : 1;
	अचिन्हित पूर्णांक lps : 6;
	अचिन्हित पूर्णांक cmd : 8;
	अचिन्हित पूर्णांक : 16;
	अचिन्हित पूर्णांक reserved;
	__u64 data_p;
पूर्ण;

#घोषणा CLP_IOCTL_MAGIC 'c'

#घोषणा CLP_SYNC _IOWR(CLP_IOCTL_MAGIC, 0xC1, काष्ठा clp_req)

#पूर्ण_अगर
