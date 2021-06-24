<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Linux driver क्रम devices based on the DiBcom DiB0700 USB bridge
 *
 *  Copyright (C) 2005-6 DiBcom, SA
 */
#अगर_अघोषित _DIB0700_H_
#घोषणा _DIB0700_H_

#घोषणा DVB_USB_LOG_PREFIX "dib0700"
#समावेश "dvb-usb.h"

#समावेश "dib07x0.h"

बाह्य पूर्णांक dvb_usb_dib0700_debug;
#घोषणा deb_info(args...)   dprपूर्णांकk(dvb_usb_dib0700_debug,0x01,args)
#घोषणा deb_fw(args...)     dprपूर्णांकk(dvb_usb_dib0700_debug,0x02,args)
#घोषणा deb_fwdata(args...) dprपूर्णांकk(dvb_usb_dib0700_debug,0x04,args)
#घोषणा deb_data(args...)   dprपूर्णांकk(dvb_usb_dib0700_debug,0x08,args)

#घोषणा REQUEST_SET_USB_XFER_LEN    0x0 /* valid only क्रम firmware version */
					/* higher than 1.21 */
#घोषणा REQUEST_I2C_READ            0x2
#घोषणा REQUEST_I2C_WRITE           0x3
#घोषणा REQUEST_POLL_RC             0x4 /* deprecated in firmware v1.20 */
#घोषणा REQUEST_JUMPRAM             0x8
#घोषणा REQUEST_SET_CLOCK           0xB
#घोषणा REQUEST_SET_GPIO            0xC
#घोषणा REQUEST_ENABLE_VIDEO        0xF
	// 1 Byte: 4MSB(1 = enable streaming, 0 = disable streaming) 4LSB(Video Mode: 0 = MPEG2 188Bytes, 1 = Analog)
	// 2 Byte: MPEG2 mode:  4MSB(1 = Master Mode, 0 = Slave Mode) 4LSB(Channel 1 = bit0, Channel 2 = bit1)
	// 2 Byte: Analog mode: 4MSB(0 = 625 lines, 1 = 525 lines)    4LSB(     "                "           )
#घोषणा REQUEST_SET_I2C_PARAM       0x10
#घोषणा REQUEST_SET_RC              0x11
#घोषणा REQUEST_NEW_I2C_READ        0x12
#घोषणा REQUEST_NEW_I2C_WRITE       0x13
#घोषणा REQUEST_GET_VERSION         0x15

काष्ठा dib0700_state अणु
	u8 channel_state;
	u16 mt2060_अगर1[2];
	u8 rc_toggle;
	u8 rc_counter;
	u8 is_dib7000pc;
	u8 fw_use_new_i2c_api;
	u8 disable_streaming_master_mode;
	u32 fw_version;
	u32 nb_packet_buffer_size;
	पूर्णांक (*पढ़ो_status)(काष्ठा dvb_frontend *, क्रमागत fe_status *);
	पूर्णांक (*sleep)(काष्ठा dvb_frontend* fe);
	u8 buf[255];
	काष्ठा i2c_client *i2c_client_demod;
	काष्ठा i2c_client *i2c_client_tuner;
पूर्ण;

पूर्णांक dib0700_get_version(काष्ठा dvb_usb_device *d, u32 *hwversion,
			u32 *romversion, u32 *ramversion, u32 *fwtype);
पूर्णांक dib0700_set_gpio(काष्ठा dvb_usb_device *d, क्रमागत dib07x0_gpios gpio,
		     u8 gpio_dir, u8 gpio_val);
पूर्णांक dib0700_ctrl_घड़ी(काष्ठा dvb_usb_device *d, u32 clk_MHz, u8 घड़ी_out_gp3);
पूर्णांक dib0700_ctrl_rd(काष्ठा dvb_usb_device *d, u8 *tx, u8 txlen, u8 *rx,
		    u8 rxlen);
पूर्णांक dib0700_करोwnload_firmware(काष्ठा usb_device *d,
			      स्थिर काष्ठा firmware *fw);
पूर्णांक dib0700_rc_setup(काष्ठा dvb_usb_device *d, काष्ठा usb_पूर्णांकerface *पूर्णांकf);
पूर्णांक dib0700_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff);
पूर्णांक dib0700_identअगरy_state(काष्ठा usb_device *d,
			   स्थिर काष्ठा dvb_usb_device_properties *props,
			   स्थिर काष्ठा dvb_usb_device_description **desc,
			   पूर्णांक *cold);
पूर्णांक dib0700_change_protocol(काष्ठा rc_dev *dev, u64 *rc_proto);
पूर्णांक dib0700_set_i2c_speed(काष्ठा dvb_usb_device *d, u16 scl_kHz);

बाह्य काष्ठा i2c_algorithm dib0700_i2c_algo;
बाह्य पूर्णांक dib0700_device_count;
बाह्य पूर्णांक dvb_usb_dib0700_ir_proto;
बाह्य काष्ठा dvb_usb_device_properties dib0700_devices[];
बाह्य काष्ठा usb_device_id dib0700_usb_id_table[];

#पूर्ण_अगर
