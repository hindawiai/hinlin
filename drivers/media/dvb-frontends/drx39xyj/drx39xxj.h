<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Micronas DRX39xx family (drx3933j)
 *
 *  Written by Devin Heiपंचांगueller <devin.heiपंचांगueller@kernelद_असल.com>
 */

#अगर_अघोषित DRX39XXJ_H
#घोषणा DRX39XXJ_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>
#समावेश "drx_driver.h"

काष्ठा drx39xxj_state अणु
	काष्ठा i2c_adapter *i2c;
	काष्ठा drx_demod_instance *demod;
	काष्ठा dvb_frontend frontend;
	अचिन्हित पूर्णांक i2c_gate_खोलो:1;
	स्थिर काष्ठा firmware *fw;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_DRX39XYJ)
काष्ठा dvb_frontend *drx39xxj_attach(काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *drx39xxj_attach(काष्ठा i2c_adapter *i2c) अणु
	वापस शून्य;
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* DVB_DUMMY_FE_H */
