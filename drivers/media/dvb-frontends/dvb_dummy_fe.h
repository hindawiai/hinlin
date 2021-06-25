<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Dummy Frontend
 *
 *  Written by Emard <emard@softhome.net>
 */

#अगर_अघोषित DVB_DUMMY_FE_H
#घोषणा DVB_DUMMY_FE_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

#अगर IS_REACHABLE(CONFIG_DVB_DUMMY_FE)
काष्ठा dvb_frontend *dvb_dummy_fe_ofdm_attach(व्योम);
काष्ठा dvb_frontend *dvb_dummy_fe_qpsk_attach(व्योम);
काष्ठा dvb_frontend *dvb_dummy_fe_qam_attach(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *dvb_dummy_fe_ofdm_attach(व्योम)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा dvb_frontend *dvb_dummy_fe_qpsk_attach(व्योम)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा dvb_frontend *dvb_dummy_fe_qam_attach(व्योम)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_DUMMY_FE */

#पूर्ण_अगर // DVB_DUMMY_FE_H
