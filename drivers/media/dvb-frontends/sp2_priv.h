<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CIMaX SP2/HF CI driver
 *
 * Copyright (C) 2014 Olli Salonen <olli.salonen@iki.fi>
 */

#अगर_अघोषित SP2_PRIV_H
#घोषणा SP2_PRIV_H

#समावेश "sp2.h"
#समावेश <media/dvb_frontend.h>

/* state काष्ठा */
काष्ठा sp2 अणु
	पूर्णांक status;
	काष्ठा i2c_client *client;
	काष्ठा dvb_adapter *dvb_adap;
	काष्ठा dvb_ca_en50221 ca;
	पूर्णांक module_access_type;
	अचिन्हित दीर्घ next_status_checked_समय;
	व्योम *priv;
	व्योम *ci_control;
पूर्ण;

#घोषणा SP2_CI_ATTR_ACS		0x00
#घोषणा SP2_CI_IO_ACS		0x04
#घोषणा SP2_CI_WR		0
#घोषणा SP2_CI_RD		1

/* Module control रेजिस्टर (0x00 module A, 0x09 module B) bits */
#घोषणा SP2_MOD_CTL_DET		0x01
#घोषणा SP2_MOD_CTL_AUTO	0x02
#घोषणा SP2_MOD_CTL_ACS0	0x04
#घोषणा SP2_MOD_CTL_ACS1	0x08
#घोषणा SP2_MOD_CTL_HAD		0x10
#घोषणा SP2_MOD_CTL_TSIEN	0x20
#घोषणा SP2_MOD_CTL_TSOEN	0x40
#घोषणा SP2_MOD_CTL_RST		0x80

#पूर्ण_अगर
