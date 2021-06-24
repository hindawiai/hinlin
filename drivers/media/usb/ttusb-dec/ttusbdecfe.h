<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * TTUSB DEC Driver
 *
 * Copyright (C) 2003-2004 Alex Woods <linux-dvb@giblets.org>
 */

#अगर_अघोषित TTUSBDECFE_H
#घोषणा TTUSBDECFE_H

#समावेश <linux/dvb/frontend.h>

काष्ठा ttusbdecfe_config
अणु
	पूर्णांक (*send_command)(काष्ठा dvb_frontend* fe, स्थिर u8 command,
			    पूर्णांक param_length, स्थिर u8 params[],
			    पूर्णांक *result_length, u8 cmd_result[]);
पूर्ण;

बाह्य काष्ठा dvb_frontend* ttusbdecfe_dvbs_attach(स्थिर काष्ठा ttusbdecfe_config* config);

बाह्य काष्ठा dvb_frontend* ttusbdecfe_dvbt_attach(स्थिर काष्ठा ttusbdecfe_config* config);

#पूर्ण_अगर // TTUSBDECFE_H
