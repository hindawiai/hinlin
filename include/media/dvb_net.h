<शैली गुरु>
/*
 * dvb_net.h
 *
 * Copyright (C) 2001 Ralph Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित _DVB_NET_H_
#घोषणा _DVB_NET_H_

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <media/dvbdev.h>

#घोषणा DVB_NET_DEVICES_MAX 10

#अगर_घोषित CONFIG_DVB_NET

/**
 * काष्ठा dvb_net - describes a DVB network पूर्णांकerface
 *
 * @dvbdev:		poपूर्णांकer to &काष्ठा dvb_device.
 * @device:		array of poपूर्णांकers to &काष्ठा net_device.
 * @state:		array of पूर्णांकegers to each net device. A value
 *			dअगरferent than zero means that the पूर्णांकerface is
 *			in usage.
 * @निकास:		flag to indicate when the device is being हटाओd.
 * @demux:		poपूर्णांकer to &काष्ठा dmx_demux.
 * @ioctl_mutex:	protect access to this काष्ठा.
 *
 * Currently, the core supports up to %DVB_NET_DEVICES_MAX (10) network
 * devices.
 */

काष्ठा dvb_net अणु
	काष्ठा dvb_device *dvbdev;
	काष्ठा net_device *device[DVB_NET_DEVICES_MAX];
	पूर्णांक state[DVB_NET_DEVICES_MAX];
	अचिन्हित पूर्णांक निकास:1;
	काष्ठा dmx_demux *demux;
	काष्ठा mutex ioctl_mutex;
पूर्ण;

/**
 * dvb_net_init - nitializes a digital TV network device and रेजिस्टरs it.
 *
 * @adap:	poपूर्णांकer to &काष्ठा dvb_adapter.
 * @dvbnet:	poपूर्णांकer to &काष्ठा dvb_net.
 * @dmxdemux:	poपूर्णांकer to &काष्ठा dmx_demux.
 */
पूर्णांक dvb_net_init(काष्ठा dvb_adapter *adap, काष्ठा dvb_net *dvbnet,
		  काष्ठा dmx_demux *dmxdemux);

/**
 * dvb_net_release - releases a digital TV network device and unरेजिस्टरs it.
 *
 * @dvbnet:	poपूर्णांकer to &काष्ठा dvb_net.
 */
व्योम dvb_net_release(काष्ठा dvb_net *dvbnet);

#अन्यथा

काष्ठा dvb_net अणु
	काष्ठा dvb_device *dvbdev;
पूर्ण;

अटल अंतरभूत व्योम dvb_net_release(काष्ठा dvb_net *dvbnet)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक dvb_net_init(काष्ठा dvb_adapter *adap,
			       काष्ठा dvb_net *dvbnet, काष्ठा dmx_demux *dmx)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* अगरdef CONFIG_DVB_NET */

#पूर्ण_अगर
