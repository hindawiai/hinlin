<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MANTIS_CORE_H
#घोषणा __MANTIS_CORE_H

#समावेश "mantis_common.h"


#घोषणा FE_TYPE_SAT	0
#घोषणा FE_TYPE_CAB	1
#घोषणा FE_TYPE_TER	2

#घोषणा FE_TYPE_TS204	0
#घोषणा FE_TYPE_TS188	1


काष्ठा venकरोrname अणु
	u8  *sub_venकरोr_name;
	u32 sub_venकरोr_id;
पूर्ण;

काष्ठा devicetype अणु
	u8  *sub_device_name;
	u32 sub_device_id;
	u8  device_type;
	u32 type_flags;
पूर्ण;


बाह्य पूर्णांक mantis_dma_init(काष्ठा mantis_pci *mantis);
बाह्य पूर्णांक mantis_dma_निकास(काष्ठा mantis_pci *mantis);
बाह्य व्योम mantis_dma_start(काष्ठा mantis_pci *mantis);
बाह्य व्योम mantis_dma_stop(काष्ठा mantis_pci *mantis);
बाह्य पूर्णांक mantis_i2c_init(काष्ठा mantis_pci *mantis);
बाह्य पूर्णांक mantis_i2c_निकास(काष्ठा mantis_pci *mantis);

#पूर्ण_अगर /* __MANTIS_CORE_H */
