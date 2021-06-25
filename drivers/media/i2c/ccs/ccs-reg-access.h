<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/media/ccs/ccs-reg-access.h
 *
 * Generic driver क्रम MIPI CCS/SMIA/SMIA++ compliant camera sensors
 *
 * Copyright (C) 2020 Intel Corporation
 * Copyright (C) 2011--2012 Nokia Corporation
 * Contact: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 */

#अगर_अघोषित SMIAPP_REGS_H
#घोषणा SMIAPP_REGS_H

#समावेश <linux/i2c.h>
#समावेश <linux/types.h>

#समावेश "ccs-regs.h"

#घोषणा CCS_REG_ADDR(reg)		((u16)reg)

काष्ठा ccs_sensor;

पूर्णांक ccs_पढ़ो_addr_no_quirk(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val);
पूर्णांक ccs_पढ़ो_addr(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val);
पूर्णांक ccs_पढ़ो_addr_8only(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val);
पूर्णांक ccs_पढ़ो_addr_noconv(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val);
पूर्णांक ccs_ग_लिखो_addr_no_quirk(काष्ठा ccs_sensor *sensor, u32 reg, u32 val);
पूर्णांक ccs_ग_लिखो_addr(काष्ठा ccs_sensor *sensor, u32 reg, u32 val);
पूर्णांक ccs_ग_लिखो_data_regs(काष्ठा ccs_sensor *sensor, काष्ठा ccs_reg *regs,
			माप_प्रकार num_regs);

अचिन्हित पूर्णांक ccs_reg_width(u32 reg);
u32 ccs_reg_conv(काष्ठा ccs_sensor *sensor, u32 reg, u32 val);

#घोषणा ccs_पढ़ो(sensor, reg_name, val) \
	ccs_पढ़ो_addr(sensor, CCS_R_##reg_name, val)

#घोषणा ccs_ग_लिखो(sensor, reg_name, val) \
	ccs_ग_लिखो_addr(sensor, CCS_R_##reg_name, val)

#पूर्ण_अगर
