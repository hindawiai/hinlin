<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 */

#अगर_अघोषित _AS102_DRV_H
#घोषणा _AS102_DRV_H
#समावेश <linux/usb.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dmxdev.h>
#समावेश "as10x_handle.h"
#समावेश "as10x_cmd.h"
#समावेश "as102_usb_drv.h"

#घोषणा DRIVER_FULL_NAME "Abilis Systems as10x usb driver"
#घोषणा DRIVER_NAME "as10x_usb"

#घोषणा debug	as102_debug
बाह्य काष्ठा usb_driver as102_usb_driver;
बाह्य पूर्णांक elna_enable;

#घोषणा AS102_DEVICE_MAJOR	192

#घोषणा AS102_USB_BUF_SIZE	512
#घोषणा MAX_STREAM_URB		32

काष्ठा as10x_bus_adapter_t अणु
	काष्ठा usb_device *usb_dev;
	/* bus token lock */
	काष्ठा mutex lock;
	/* low level पूर्णांकerface क्रम bus adapter */
	जोड़ as10x_bus_token_t अणु
		/* usb token */
		काष्ठा as10x_usb_token_cmd_t usb;
	पूर्ण token;

	/* token cmd xfer id */
	uपूर्णांक16_t cmd_xid;

	/* as10x command and response क्रम dvb पूर्णांकerface*/
	काष्ठा as10x_cmd_t *cmd, *rsp;

	/* bus adapter निजी ops callback */
	स्थिर काष्ठा as102_priv_ops_t *ops;
पूर्ण;

काष्ठा as102_dev_t अणु
	स्थिर अक्षर *name;
	काष्ठा as10x_bus_adapter_t bus_adap;
	काष्ठा list_head device_entry;
	काष्ठा kref kref;
	uपूर्णांक8_t elna_cfg;

	काष्ठा dvb_adapter dvb_adap;
	काष्ठा dvb_frontend *dvb_fe;
	काष्ठा dvb_demux dvb_dmx;
	काष्ठा dmxdev dvb_dmxdev;

	/* समयr handle to trig ts stream करोwnload */
	काष्ठा समयr_list समयr_handle;

	काष्ठा mutex sem;
	dma_addr_t dma_addr;
	व्योम *stream;
	पूर्णांक streaming;
	काष्ठा urb *stream_urb[MAX_STREAM_URB];
पूर्ण;

पूर्णांक as102_dvb_रेजिस्टर(काष्ठा as102_dev_t *dev);
व्योम as102_dvb_unरेजिस्टर(काष्ठा as102_dev_t *dev);

#पूर्ण_अगर
