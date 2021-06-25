<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Mantis VP-1034 driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MANTIS_VP1034_H
#घोषणा __MANTIS_VP1034_H

#समावेश <media/dvb_frontend.h>
#समावेश "mantis_common.h"


#घोषणा MANTIS_VP_1034_DVB_S	0x0014

बाह्य काष्ठा mantis_hwconfig vp1034_config;
बाह्य पूर्णांक vp1034_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage);

#पूर्ण_अगर /* __MANTIS_VP1034_H */
