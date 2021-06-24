<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* dvb-usb-common.h is part of the DVB USB library.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * a header file containing prototypes and types क्रम पूर्णांकernal use of the dvb-usb-lib
 */
#अगर_अघोषित _DVB_USB_COMMON_H_
#घोषणा _DVB_USB_COMMON_H_

#घोषणा DVB_USB_LOG_PREFIX "dvb-usb"
#समावेश "dvb-usb.h"

बाह्य पूर्णांक dvb_usb_debug;
बाह्य पूर्णांक dvb_usb_disable_rc_polling;

#घोषणा deb_info(args...)  dprपूर्णांकk(dvb_usb_debug,0x001,args)
#घोषणा deb_xfer(args...)  dprपूर्णांकk(dvb_usb_debug,0x002,args)
#घोषणा deb_pll(args...)   dprपूर्णांकk(dvb_usb_debug,0x004,args)
#घोषणा deb_ts(args...)    dprपूर्णांकk(dvb_usb_debug,0x008,args)
#घोषणा deb_err(args...)   dprपूर्णांकk(dvb_usb_debug,0x010,args)
#घोषणा deb_rc(args...)    dprपूर्णांकk(dvb_usb_debug,0x020,args)
#घोषणा deb_fw(args...)    dprपूर्णांकk(dvb_usb_debug,0x040,args)
#घोषणा deb_mem(args...)   dprपूर्णांकk(dvb_usb_debug,0x080,args)
#घोषणा deb_uxfer(args...) dprपूर्णांकk(dvb_usb_debug,0x100,args)

/* commonly used  methods */
पूर्णांक dvb_usb_करोwnload_firmware(काष्ठा usb_device *udev,
			      स्थिर काष्ठा dvb_usb_device_properties *props);

बाह्य पूर्णांक dvb_usb_device_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff);

बाह्य पूर्णांक usb_urb_init(काष्ठा usb_data_stream *stream, काष्ठा usb_data_stream_properties *props);
बाह्य पूर्णांक usb_urb_निकास(काष्ठा usb_data_stream *stream);
बाह्य पूर्णांक usb_urb_submit(काष्ठा usb_data_stream *stream);
बाह्य पूर्णांक usb_urb_समाप्त(काष्ठा usb_data_stream *stream);

बाह्य पूर्णांक dvb_usb_adapter_stream_init(काष्ठा dvb_usb_adapter *adap);
बाह्य पूर्णांक dvb_usb_adapter_stream_निकास(काष्ठा dvb_usb_adapter *adap);

बाह्य पूर्णांक dvb_usb_i2c_init(काष्ठा dvb_usb_device *);
बाह्य पूर्णांक dvb_usb_i2c_निकास(काष्ठा dvb_usb_device *);

बाह्य पूर्णांक dvb_usb_adapter_dvb_init(काष्ठा dvb_usb_adapter *adap,
				    लघु *adapter_nums);
बाह्य पूर्णांक dvb_usb_adapter_dvb_निकास(काष्ठा dvb_usb_adapter *adap);
बाह्य पूर्णांक dvb_usb_adapter_frontend_init(काष्ठा dvb_usb_adapter *adap);
बाह्य पूर्णांक dvb_usb_adapter_frontend_निकास(काष्ठा dvb_usb_adapter *adap);

बाह्य पूर्णांक dvb_usb_remote_init(काष्ठा dvb_usb_device *);
बाह्य पूर्णांक dvb_usb_remote_निकास(काष्ठा dvb_usb_device *);

#पूर्ण_अगर
