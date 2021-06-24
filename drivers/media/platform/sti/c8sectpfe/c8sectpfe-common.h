<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * c8sectpfe-common.h - C8SECTPFE STi DVB driver
 *
 * Copyright (c) STMicroelectronics 2015
 *
 *   Author: Peter Grअगरfin <peter.grअगरfin@linaro.org>
 *
 */
#अगर_अघोषित _C8SECTPFE_COMMON_H_
#घोषणा _C8SECTPFE_COMMON_H_

#समावेश <linux/dvb/dmx.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/version.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

/* Maximum number of channels */
#घोषणा C8SECTPFE_MAXADAPTER (4)
#घोषणा C8SECTPFE_MAXCHANNEL 64
#घोषणा STPTI_MAXCHANNEL 64

#घोषणा MAX_INPUTBLOCKS 7

काष्ठा c8sectpfe;
काष्ठा stdemux;

काष्ठा stdemux अणु
	काष्ठा dvb_demux	dvb_demux;
	काष्ठा dmxdev		dmxdev;
	काष्ठा dmx_frontend	hw_frontend;
	काष्ठा dmx_frontend	mem_frontend;
	पूर्णांक			tsin_index;
	पूर्णांक			running_feed_count;
	काष्ठा			c8sectpfei *c8sectpfei;
पूर्ण;

काष्ठा c8sectpfe अणु
	काष्ठा stdemux demux[MAX_INPUTBLOCKS];
	काष्ठा mutex lock;
	काष्ठा dvb_adapter adapter;
	काष्ठा device *device;
	पूर्णांक mapping;
	पूर्णांक num_feeds;
पूर्ण;

/* Channel registration */
पूर्णांक c8sectpfe_tuner_रेजिस्टर_frontend(काष्ठा c8sectpfe **c8sectpfe,
					काष्ठा c8sectpfei *fei,
					व्योम *start_feed,
					व्योम *stop_feed);

व्योम c8sectpfe_tuner_unरेजिस्टर_frontend(काष्ठा c8sectpfe *c8sectpfe,
						काष्ठा c8sectpfei *fei);

#पूर्ण_अगर
