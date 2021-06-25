<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2006-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#अगर_अघोषित __CNA_H__
#घोषणा __CNA_H__

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_ether.h>

#घोषणा bfa_sm_fault(__event)    करो अणु                            \
	pr_err("SM Assertion failure: %s: %d: event = %d\n",	\
		 __खाता__, __LINE__, __event);			\
पूर्ण जबतक (0)

बाह्य अक्षर bfa_version[];

#घोषणा CNA_FW_खाता_CT	"ctfw-3.2.5.1.bin"
#घोषणा CNA_FW_खाता_CT2	"ct2fw-3.2.5.1.bin"
#घोषणा FC_SYMNAME_MAX	256	/*!< max name server symbolic name size */

#पूर्ण_अगर /* __CNA_H__ */
