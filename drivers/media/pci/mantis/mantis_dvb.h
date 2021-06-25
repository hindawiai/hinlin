<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MANTIS_DVB_H
#घोषणा __MANTIS_DVB_H

क्रमागत mantis_घातer अणु
	POWER_OFF	= 0,
	POWER_ON	= 1
पूर्ण;

बाह्य पूर्णांक mantis_frontend_घातer(काष्ठा mantis_pci *mantis, क्रमागत mantis_घातer घातer);
बाह्य व्योम mantis_frontend_soft_reset(काष्ठा mantis_pci *mantis);

बाह्य पूर्णांक mantis_dvb_init(काष्ठा mantis_pci *mantis);
बाह्य पूर्णांक mantis_dvb_निकास(काष्ठा mantis_pci *mantis);

#पूर्ण_अगर /* __MANTIS_DVB_H */
