<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _VIDEOBUF2_DVB_H_
#घोषणा	_VIDEOBUF2_DVB_H_

#समावेश <media/dvbdev.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/videobuf2-v4l2.h>

/* We करोn't actually need to include media-device.h here */
काष्ठा media_device;

/*
 * TODO: This header file should be replaced with videobuf2-core.h
 * Currently, vb2_thपढ़ो is not a stuff of videobuf2-core,
 * since vb2_thपढ़ो has many dependencies on videobuf2-v4l2.
 */

काष्ठा vb2_dvb अणु
	/* filling that the job of the driver */
	अक्षर			*name;
	काष्ठा dvb_frontend	*frontend;
	काष्ठा vb2_queue	dvbq;

	/* video-buf-dvb state info */
	काष्ठा mutex		lock;
	पूर्णांक			nfeeds;

	/* vb2_dvb_(un)रेजिस्टर manages this */
	काष्ठा dvb_demux	demux;
	काष्ठा dmxdev		dmxdev;
	काष्ठा dmx_frontend	fe_hw;
	काष्ठा dmx_frontend	fe_mem;
	काष्ठा dvb_net		net;
पूर्ण;

काष्ठा vb2_dvb_frontend अणु
	काष्ठा list_head felist;
	पूर्णांक id;
	काष्ठा vb2_dvb dvb;
पूर्ण;

काष्ठा vb2_dvb_frontends अणु
	काष्ठा list_head felist;
	काष्ठा mutex lock;
	काष्ठा dvb_adapter adapter;
	पूर्णांक active_fe_id; /* Indicates which frontend in the felist is in use */
	पूर्णांक gate; /* Frontend with gate control 0=!MFE,1=fe0,2=fe1 etc */
पूर्ण;

पूर्णांक vb2_dvb_रेजिस्टर_bus(काष्ठा vb2_dvb_frontends *f,
			 काष्ठा module *module,
			 व्योम *adapter_priv,
			 काष्ठा device *device,
			 काष्ठा media_device *mdev,
			 लघु *adapter_nr,
			 पूर्णांक mfe_shared);

व्योम vb2_dvb_unरेजिस्टर_bus(काष्ठा vb2_dvb_frontends *f);

काष्ठा vb2_dvb_frontend *vb2_dvb_alloc_frontend(काष्ठा vb2_dvb_frontends *f, पूर्णांक id);
व्योम vb2_dvb_dealloc_frontends(काष्ठा vb2_dvb_frontends *f);

काष्ठा vb2_dvb_frontend *vb2_dvb_get_frontend(काष्ठा vb2_dvb_frontends *f, पूर्णांक id);
पूर्णांक vb2_dvb_find_frontend(काष्ठा vb2_dvb_frontends *f, काष्ठा dvb_frontend *p);

#पूर्ण_अगर			/* _VIDEOBUF2_DVB_H_ */
