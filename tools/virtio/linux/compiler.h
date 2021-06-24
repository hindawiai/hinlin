<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_COMPILER_H
#घोषणा LINUX_COMPILER_H

#घोषणा WRITE_ONCE(var, val) \
	(*((अस्थिर typeof(val) *)(&(var))) = (val))

#घोषणा READ_ONCE(var) (*((अस्थिर typeof(var) *)(&(var))))

#घोषणा __aligned(x) __attribute((__aligned__(x)))
#पूर्ण_अगर
