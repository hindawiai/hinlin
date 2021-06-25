<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 पूर्णांकerrupt handling
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#घोषणा HW2_I2C1_INT			(1 << 22)
#घोषणा HW2_I2C2_INT			(1 << 23)
#घोषणा HW2_INT_CLR_STATUS		0xc730c4
#घोषणा HW2_INT_MASK5_PCI		0xc730e4
#घोषणा SW1_INT_SET                     0xc73100
#घोषणा SW1_INT_STATUS                  0xc73104
#घोषणा SW1_INT_ENABLE_PCI              0xc7311c
#घोषणा SW2_INT_SET                     0xc73140
#घोषणा SW2_INT_STATUS                  0xc73144
#घोषणा SW2_INT_ENABLE_CPU              0xc73158
#घोषणा SW2_INT_ENABLE_PCI              0xc7315c

irqवापस_t cx18_irq_handler(पूर्णांक irq, व्योम *dev_id);
