<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VTI CMA3000_D0x Accelerometer driver
 *
 * Copyright (C) 2010 Texas Instruments
 * Author: Hemanth V <hemanthv@ti.com>
 */

#अगर_अघोषित _INPUT_CMA3000_H
#घोषणा _INPUT_CMA3000_H

#समावेश <linux/types.h>
#समावेश <linux/input.h>

काष्ठा device;
काष्ठा cma3000_accl_data;

काष्ठा cma3000_bus_ops अणु
	u16 bustype;
	u8 ctrl_mod;
	पूर्णांक (*पढ़ो)(काष्ठा device *, u8, अक्षर *);
	पूर्णांक (*ग_लिखो)(काष्ठा device *, u8, u8, अक्षर *);
पूर्ण;

काष्ठा cma3000_accl_data *cma3000_init(काष्ठा device *dev, पूर्णांक irq,
					स्थिर काष्ठा cma3000_bus_ops *bops);
व्योम cma3000_निकास(काष्ठा cma3000_accl_data *);
व्योम cma3000_suspend(काष्ठा cma3000_accl_data *);
व्योम cma3000_resume(काष्ठा cma3000_accl_data *);

#पूर्ण_अगर
