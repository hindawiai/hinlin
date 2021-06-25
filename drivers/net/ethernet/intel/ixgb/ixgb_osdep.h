<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2008 Intel Corporation. */

/* glue क्रम the OS independent part of ixgb
 * includes रेजिस्टर access macros
 */

#अगर_अघोषित _IXGB_OSDEP_H_
#घोषणा _IXGB_OSDEP_H_

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/अगर_ether.h>

#अघोषित ASSERT
#घोषणा ASSERT(x)	BUG_ON(!(x))

#घोषणा ENTER() pr_debug("%s\n", __func__);

#घोषणा IXGB_WRITE_REG(a, reg, value) ( \
	ग_लिखोl((value), ((a)->hw_addr + IXGB_##reg)))

#घोषणा IXGB_READ_REG(a, reg) ( \
	पढ़ोl((a)->hw_addr + IXGB_##reg))

#घोषणा IXGB_WRITE_REG_ARRAY(a, reg, offset, value) ( \
	ग_लिखोl((value), ((a)->hw_addr + IXGB_##reg + ((offset) << 2))))

#घोषणा IXGB_READ_REG_ARRAY(a, reg, offset) ( \
	पढ़ोl((a)->hw_addr + IXGB_##reg + ((offset) << 2)))

#घोषणा IXGB_WRITE_FLUSH(a) IXGB_READ_REG(a, STATUS)

#घोषणा IXGB_MEMCPY स_नकल

#पूर्ण_अगर /* _IXGB_OSDEP_H_ */
