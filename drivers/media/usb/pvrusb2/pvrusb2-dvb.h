<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PVRUSB2_DVB_H__
#घोषणा __PVRUSB2_DVB_H__

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dmxdev.h>
#समावेश "pvrusb2-context.h"

#घोषणा PVR2_DVB_BUFFER_COUNT 32
#घोषणा PVR2_DVB_BUFFER_SIZE PAGE_ALIGN(0x4000)

काष्ठा pvr2_dvb_adapter अणु
	काष्ठा pvr2_channel	channel;

	काष्ठा dvb_adapter	dvb_adap;
	काष्ठा dmxdev		dmxdev;
	काष्ठा dvb_demux	demux;
	काष्ठा dvb_net		dvb_net;
	काष्ठा dvb_frontend	*fe[2];

	काष्ठा i2c_client	*i2c_client_demod[2];
	काष्ठा i2c_client	*i2c_client_tuner;

	पूर्णांक			feedcount;
	पूर्णांक			max_feed_count;

	काष्ठा task_काष्ठा	*thपढ़ो;
	काष्ठा mutex		lock;

	अचिन्हित पूर्णांक		stream_run:1;

	रुको_queue_head_t	buffer_रुको_data;
	अक्षर			*buffer_storage[PVR2_DVB_BUFFER_COUNT];
पूर्ण;

काष्ठा pvr2_dvb_props अणु
	पूर्णांक (*frontend_attach) (काष्ठा pvr2_dvb_adapter *);
	पूर्णांक (*tuner_attach) (काष्ठा pvr2_dvb_adapter *);
पूर्ण;

काष्ठा pvr2_dvb_adapter *pvr2_dvb_create(काष्ठा pvr2_context *pvr);

#पूर्ण_अगर /* __PVRUSB2_DVB_H__ */
