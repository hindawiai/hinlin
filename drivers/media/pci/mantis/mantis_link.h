<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MANTIS_LINK_H
#घोषणा __MANTIS_LINK_H

#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <media/dvb_ca_en50221.h>

क्रमागत mantis_sbuf_status अणु
	MANTIS_SBUF_DATA_AVAIL		= 1,
	MANTIS_SBUF_DATA_EMPTY		= 2,
	MANTIS_SBUF_DATA_OVFLW		= 3
पूर्ण;

काष्ठा mantis_slot अणु
	u32				समयout;
	u32				slave_cfg;
	u32				bar;
पूर्ण;

/* Physical layer */
क्रमागत mantis_slot_state अणु
	MODULE_INSERTED			= 3,
	MODULE_XTRACTED			= 4
पूर्ण;

काष्ठा mantis_ca अणु
	काष्ठा mantis_slot		slot[4];

	काष्ठा work_काष्ठा		hअगर_evm_work;

	u32				hअगर_event;
	रुको_queue_head_t		hअगर_opकरोne_wq;
	रुको_queue_head_t		hअगर_brrdyw_wq;
	रुको_queue_head_t		hअगर_data_wq;
	रुको_queue_head_t		hअगर_ग_लिखो_wq; /* HIF Write op */

	क्रमागत mantis_sbuf_status		sbuf_status;

	क्रमागत mantis_slot_state		slot_state;

	व्योम				*ca_priv;

	काष्ठा dvb_ca_en50221		en50221;
	काष्ठा mutex			ca_lock;
पूर्ण;

/* CA */
बाह्य व्योम mantis_event_cam_plugin(काष्ठा mantis_ca *ca);
बाह्य व्योम mantis_event_cam_unplug(काष्ठा mantis_ca *ca);
बाह्य पूर्णांक mantis_pcmcia_init(काष्ठा mantis_ca *ca);
बाह्य व्योम mantis_pcmcia_निकास(काष्ठा mantis_ca *ca);
बाह्य पूर्णांक mantis_evmgr_init(काष्ठा mantis_ca *ca);
बाह्य व्योम mantis_evmgr_निकास(काष्ठा mantis_ca *ca);

/* HIF */
बाह्य पूर्णांक mantis_hअगर_init(काष्ठा mantis_ca *ca);
बाह्य व्योम mantis_hअगर_निकास(काष्ठा mantis_ca *ca);
बाह्य पूर्णांक mantis_hअगर_पढ़ो_mem(काष्ठा mantis_ca *ca, u32 addr);
बाह्य पूर्णांक mantis_hअगर_ग_लिखो_mem(काष्ठा mantis_ca *ca, u32 addr, u8 data);
बाह्य पूर्णांक mantis_hअगर_पढ़ो_iom(काष्ठा mantis_ca *ca, u32 addr);
बाह्य पूर्णांक mantis_hअगर_ग_लिखो_iom(काष्ठा mantis_ca *ca, u32 addr, u8 data);

#पूर्ण_अगर /* __MANTIS_LINK_H */
