<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// DVB device driver क्रम em28xx
//
// (c) 2008-2011 Mauro Carvalho Chehab <mchehab@kernel.org>
//
// (c) 2008 Devin Heiपंचांगueller <devin.heiपंचांगueller@gmail.com>
//	- Fixes क्रम the driver to properly work with HVR-950
//	- Fixes क्रम the driver to properly work with Pinnacle PCTV HD Pro Stick
//	- Fixes क्रम the driver to properly work with AMD ATI TV Wonder HD 600
//
// (c) 2008 Aidan Thornton <makosoft@googlemail.com>
//
// (c) 2012 Frank Schथअfer <fschaefer.oss@googlemail.com>
//
// Based on cx88-dvb, saa7134-dvb and videobuf-dvb originally written by:
//	(c) 2004, 2005 Chris Pascoe <c.pascoe@itee.uq.edu.au>
//	(c) 2004 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
//
// This program is मुक्त software; you can redistribute it and/or modअगरy
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation version 2 of the License.

#समावेश "em28xx.h"

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dmxdev.h>
#समावेश <media/tuner.h>
#समावेश "tuner-simple.h"
#समावेश <linux/gpपन.स>

#समावेश "lgdt330x.h"
#समावेश "lgdt3305.h"
#समावेश "lgdt3306a.h"
#समावेश "zl10353.h"
#समावेश "s5h1409.h"
#समावेश "mt2060.h"
#समावेश "mt352.h"
#समावेश "mt352_priv.h" /* FIXME */
#समावेश "tda1002x.h"
#समावेश "drx39xyj/drx39xxj.h"
#समावेश "tda18271.h"
#समावेश "s921.h"
#समावेश "drxd.h"
#समावेश "cxd2820r.h"
#समावेश "tda18271c2dd.h"
#समावेश "drxk.h"
#समावेश "tda10071.h"
#समावेश "tda18212.h"
#समावेश "a8293.h"
#समावेश "qt1010.h"
#समावेश "mb86a20s.h"
#समावेश "m88ds3103.h"
#समावेश "ts2020.h"
#समावेश "si2168.h"
#समावेश "si2157.h"
#समावेश "tc90522.h"
#समावेश "qm1d1c0042.h"
#समावेश "mxl692.h"

MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@kernel.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION(DRIVER_DESC " - digital TV interface");
MODULE_VERSION(EM28XX_VERSION);

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages [dvb]");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (debug >= level)						\
		dev_prपूर्णांकk(KERN_DEBUG, &dev->पूर्णांकf->dev,			\
			   "dvb: " fmt, ## arg);			\
पूर्ण जबतक (0)

काष्ठा em28xx_dvb अणु
	काष्ठा dvb_frontend        *fe[2];

	/* feed count management */
	काष्ठा mutex               lock;
	पूर्णांक                        nfeeds;

	/* general boilerplate stuff */
	काष्ठा dvb_adapter         adapter;
	काष्ठा dvb_demux           demux;
	काष्ठा dmxdev              dmxdev;
	काष्ठा dmx_frontend        fe_hw;
	काष्ठा dmx_frontend        fe_mem;
	काष्ठा dvb_net             net;

	/* Due to DRX-K - probably need changes */
	पूर्णांक (*gate_ctrl)(काष्ठा dvb_frontend *fe, पूर्णांक gate);
	काष्ठा semaphore      pll_mutex;
	bool			करोnt_attach_fe1;
	पूर्णांक			lna_gpio;
	काष्ठा i2c_client	*i2c_client_demod;
	काष्ठा i2c_client	*i2c_client_tuner;
	काष्ठा i2c_client	*i2c_client_sec;
पूर्ण;

अटल अंतरभूत व्योम prपूर्णांक_err_status(काष्ठा em28xx *dev,
				    पूर्णांक packet, पूर्णांक status)
अणु
	अक्षर *errmsg = "Unknown";

	चयन (status) अणु
	हाल -ENOENT:
		errmsg = "unlinked synchronously";
		अवरोध;
	हाल -ECONNRESET:
		errmsg = "unlinked asynchronously";
		अवरोध;
	हाल -ENOSR:
		errmsg = "Buffer error (overrun)";
		अवरोध;
	हाल -EPIPE:
		errmsg = "Stalled (device not responding)";
		अवरोध;
	हाल -EOVERFLOW:
		errmsg = "Babble (bad cable?)";
		अवरोध;
	हाल -EPROTO:
		errmsg = "Bit-stuff error (bad cable?)";
		अवरोध;
	हाल -EILSEQ:
		errmsg = "CRC/Timeout (could be anything)";
		अवरोध;
	हाल -ETIME:
		errmsg = "Device does not respond";
		अवरोध;
	पूर्ण
	अगर (packet < 0) अणु
		dprपूर्णांकk(1, "URB status %d [%s].\n", status, errmsg);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(1, "URB packet %d, status %d [%s].\n",
			packet, status, errmsg);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक em28xx_dvb_urb_data_copy(काष्ठा em28xx *dev, काष्ठा urb *urb)
अणु
	पूर्णांक xfer_bulk, num_packets, i;

	अगर (!dev)
		वापस 0;

	अगर (dev->disconnected)
		वापस 0;

	अगर (urb->status < 0)
		prपूर्णांक_err_status(dev, -1, urb->status);

	xfer_bulk = usb_pipebulk(urb->pipe);

	अगर (xfer_bulk) /* bulk */
		num_packets = 1;
	अन्यथा /* isoc */
		num_packets = urb->number_of_packets;

	क्रम (i = 0; i < num_packets; i++) अणु
		अगर (xfer_bulk) अणु
			अगर (urb->status < 0) अणु
				prपूर्णांक_err_status(dev, i, urb->status);
				अगर (urb->status != -EPROTO)
					जारी;
			पूर्ण
			अगर (!urb->actual_length)
				जारी;
			dvb_dmx_swfilter(&dev->dvb->demux, urb->transfer_buffer,
					 urb->actual_length);
		पूर्ण अन्यथा अणु
			अगर (urb->iso_frame_desc[i].status < 0) अणु
				prपूर्णांक_err_status(dev, i,
						 urb->iso_frame_desc[i].status);
				अगर (urb->iso_frame_desc[i].status != -EPROTO)
					जारी;
			पूर्ण
			अगर (!urb->iso_frame_desc[i].actual_length)
				जारी;
			dvb_dmx_swfilter(&dev->dvb->demux,
					 urb->transfer_buffer +
					 urb->iso_frame_desc[i].offset,
					 urb->iso_frame_desc[i].actual_length);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_start_streaming(काष्ठा em28xx_dvb *dvb)
अणु
	पूर्णांक rc;
	काष्ठा em28xx_i2c_bus *i2c_bus = dvb->adapter.priv;
	काष्ठा em28xx *dev = i2c_bus->dev;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	पूर्णांक dvb_max_packet_size, packet_multiplier, dvb_alt;

	अगर (dev->dvb_xfer_bulk) अणु
		अगर (!dev->dvb_ep_bulk)
			वापस -ENODEV;
		dvb_max_packet_size = 512; /* USB 2.0 spec */
		packet_multiplier = EM28XX_DVB_BULK_PACKET_MULTIPLIER;
		dvb_alt = 0;
	पूर्ण अन्यथा अणु /* isoc */
		अगर (!dev->dvb_ep_isoc)
			वापस -ENODEV;
		dvb_max_packet_size = dev->dvb_max_pkt_size_isoc;
		अगर (dvb_max_packet_size < 0)
			वापस dvb_max_packet_size;
		packet_multiplier = EM28XX_DVB_NUM_ISOC_PACKETS;
		dvb_alt = dev->dvb_alt_isoc;
	पूर्ण

	अगर (!dev->board.has_dual_ts)
		usb_set_पूर्णांकerface(udev, dev->अगरnum, dvb_alt);

	rc = em28xx_set_mode(dev, EM28XX_DIGITAL_MODE);
	अगर (rc < 0)
		वापस rc;

	dprपूर्णांकk(1, "Using %d buffers each with %d x %d bytes, alternate %d\n",
		EM28XX_DVB_NUM_BUFS,
		packet_multiplier,
		dvb_max_packet_size, dvb_alt);

	वापस em28xx_init_usb_xfer(dev, EM28XX_DIGITAL_MODE,
				    dev->dvb_xfer_bulk,
				    EM28XX_DVB_NUM_BUFS,
				    dvb_max_packet_size,
				    packet_multiplier,
				    em28xx_dvb_urb_data_copy);
पूर्ण

अटल पूर्णांक em28xx_stop_streaming(काष्ठा em28xx_dvb *dvb)
अणु
	काष्ठा em28xx_i2c_bus *i2c_bus = dvb->adapter.priv;
	काष्ठा em28xx *dev = i2c_bus->dev;

	em28xx_stop_urbs(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux  = feed->demux;
	काष्ठा em28xx_dvb *dvb = demux->priv;
	पूर्णांक rc, ret;

	अगर (!demux->dmx.frontend)
		वापस -EINVAL;

	mutex_lock(&dvb->lock);
	dvb->nfeeds++;
	rc = dvb->nfeeds;

	अगर (dvb->nfeeds == 1) अणु
		ret = em28xx_start_streaming(dvb);
		अगर (ret < 0)
			rc = ret;
	पूर्ण

	mutex_unlock(&dvb->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक em28xx_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux  = feed->demux;
	काष्ठा em28xx_dvb *dvb = demux->priv;
	पूर्णांक err = 0;

	mutex_lock(&dvb->lock);
	dvb->nfeeds--;

	अगर (!dvb->nfeeds)
		err = em28xx_stop_streaming(dvb);

	mutex_unlock(&dvb->lock);
	वापस err;
पूर्ण

/* ------------------------------------------------------------------ */
अटल पूर्णांक em28xx_dvb_bus_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक acquire)
अणु
	काष्ठा em28xx_i2c_bus *i2c_bus = fe->dvb->priv;
	काष्ठा em28xx *dev = i2c_bus->dev;

	अगर (acquire)
		वापस em28xx_set_mode(dev, EM28XX_DIGITAL_MODE);
	अन्यथा
		वापस em28xx_set_mode(dev, EM28XX_SUSPEND);
पूर्ण

/* ------------------------------------------------------------------ */

अटल काष्ठा lgdt330x_config em2880_lgdt3303_dev = अणु
	.demod_chip = LGDT3303,
पूर्ण;

अटल काष्ठा lgdt3305_config em2870_lgdt3304_dev = अणु
	.i2c_addr           = 0x0e,
	.demod_chip         = LGDT3304,
	.spectral_inversion = 1,
	.deny_i2c_rptr      = 1,
	.mpeg_mode          = LGDT3305_MPEG_PARALLEL,
	.tpclk_edge         = LGDT3305_TPCLK_FALLING_EDGE,
	.tpvalid_polarity   = LGDT3305_TP_VALID_HIGH,
	.vsb_अगर_khz         = 3250,
	.qam_अगर_khz         = 4000,
पूर्ण;

अटल काष्ठा lgdt3305_config em2874_lgdt3305_dev = अणु
	.i2c_addr           = 0x0e,
	.demod_chip         = LGDT3305,
	.spectral_inversion = 1,
	.deny_i2c_rptr      = 0,
	.mpeg_mode          = LGDT3305_MPEG_SERIAL,
	.tpclk_edge         = LGDT3305_TPCLK_FALLING_EDGE,
	.tpvalid_polarity   = LGDT3305_TP_VALID_HIGH,
	.vsb_अगर_khz         = 3250,
	.qam_अगर_khz         = 4000,
पूर्ण;

अटल काष्ठा lgdt3305_config em2874_lgdt3305_nogate_dev = अणु
	.i2c_addr           = 0x0e,
	.demod_chip         = LGDT3305,
	.spectral_inversion = 1,
	.deny_i2c_rptr      = 1,
	.mpeg_mode          = LGDT3305_MPEG_SERIAL,
	.tpclk_edge         = LGDT3305_TPCLK_FALLING_EDGE,
	.tpvalid_polarity   = LGDT3305_TP_VALID_HIGH,
	.vsb_अगर_khz         = 3600,
	.qam_अगर_khz         = 3600,
पूर्ण;

अटल काष्ठा s921_config sharp_isdbt = अणु
	.demod_address = 0x30 >> 1
पूर्ण;

अटल काष्ठा zl10353_config em28xx_zl10353_with_xc3028 = अणु
	.demod_address = (0x1e >> 1),
	.no_tuner = 1,
	.parallel_ts = 1,
	.अगर2 = 45600,
पूर्ण;

अटल काष्ठा s5h1409_config em28xx_s5h1409_with_xc3028 = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_PARALLEL_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK
पूर्ण;

अटल काष्ठा tda18271_std_map kworld_a340_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 3250, .agc_mode = 3, .std = 0,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
	.qam_6    = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 1,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config kworld_a340_config = अणु
	.std_map           = &kworld_a340_std_map,
पूर्ण;

अटल काष्ठा tda18271_config kworld_ub435q_v2_config = अणु
	.std_map	= &kworld_a340_std_map,
	.gate		= TDA18271_GATE_DIGITAL,
पूर्ण;

अटल काष्ठा tda18212_config kworld_ub435q_v3_config = अणु
	.अगर_atsc_vsb	= 3600,
	.अगर_atsc_qam	= 3600,
पूर्ण;

अटल काष्ठा zl10353_config em28xx_zl10353_xc3028_no_i2c_gate = अणु
	.demod_address = (0x1e >> 1),
	.no_tuner = 1,
	.disable_i2c_gate_ctrl = 1,
	.parallel_ts = 1,
	.अगर2 = 45600,
पूर्ण;

अटल काष्ठा drxd_config em28xx_drxd = अणु
	.demod_address = 0x70,
	.demod_revision = 0xa2,
	.pll_type = DRXD_PLL_NONE,
	.घड़ी = 12000,
	.insert_rs_byte = 1,
	.IF = 42800000,
	.disable_i2c_gate_ctrl = 1,
पूर्ण;

अटल काष्ठा drxk_config terratec_h5_drxk = अणु
	.adr = 0x29,
	.single_master = 1,
	.no_i2c_bridge = 1,
	.microcode_name = "dvb-usb-terratec-h5-drxk.fw",
	.qam_demod_parameter_count = 2,
पूर्ण;

अटल काष्ठा drxk_config hauppauge_930c_drxk = अणु
	.adr = 0x29,
	.single_master = 1,
	.no_i2c_bridge = 1,
	.microcode_name = "dvb-usb-hauppauge-hvr930c-drxk.fw",
	.chunk_size = 56,
	.qam_demod_parameter_count = 2,
पूर्ण;

अटल काष्ठा drxk_config terratec_htc_stick_drxk = अणु
	.adr = 0x29,
	.single_master = 1,
	.no_i2c_bridge = 1,
	.microcode_name = "dvb-usb-terratec-htc-stick-drxk.fw",
	.chunk_size = 54,
	.qam_demod_parameter_count = 2,
	/* Required क्रम the antenna_gpio to disable LNA. */
	.antenna_dvbt = true,
	/* The winकरोws driver uses the same. This will disable LNA. */
	.antenna_gpio = 0x6,
पूर्ण;

अटल काष्ठा drxk_config maxmedia_ub425_tc_drxk = अणु
	.adr = 0x29,
	.single_master = 1,
	.no_i2c_bridge = 1,
	.microcode_name = "dvb-demod-drxk-01.fw",
	.chunk_size = 62,
	.qam_demod_parameter_count = 2,
पूर्ण;

अटल काष्ठा drxk_config pctv_520e_drxk = अणु
	.adr = 0x29,
	.single_master = 1,
	.microcode_name = "dvb-demod-drxk-pctv.fw",
	.qam_demod_parameter_count = 2,
	.chunk_size = 58,
	.antenna_dvbt = true, /* disable LNA */
	.antenna_gpio = (1 << 2), /* disable LNA */
पूर्ण;

अटल पूर्णांक drxk_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा em28xx_dvb *dvb = fe->sec_priv;
	पूर्णांक status;

	अगर (!dvb)
		वापस -EINVAL;

	अगर (enable) अणु
		करोwn(&dvb->pll_mutex);
		status = dvb->gate_ctrl(fe, 1);
	पूर्ण अन्यथा अणु
		status = dvb->gate_ctrl(fe, 0);
		up(&dvb->pll_mutex);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम hauppauge_hvr930c_init(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;

	अटल स्थिर काष्ठा em28xx_reg_seq hauppauge_hvr930c_init[] = अणु
		अणुEM2874_R80_GPIO_P0_CTRL,	0xff,	0xff,	0x65पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xfb,	0xff,	0x32पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xff,	0xff,	0xb8पूर्ण,
		अणु	-1,			-1,	-1,	-1पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा em28xx_reg_seq hauppauge_hvr930c_end[] = अणु
		अणुEM2874_R80_GPIO_P0_CTRL,	0xef,	0xff,	0x01पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xaf,	0xff,	0x65पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xef,	0xff,	0x76पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xef,	0xff,	0x01पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xcf,	0xff,	0x0bपूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xef,	0xff,	0x40पूर्ण,

		अणुEM2874_R80_GPIO_P0_CTRL,	0xcf,	0xff,	0x65पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xef,	0xff,	0x65पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xcf,	0xff,	0x0bपूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xef,	0xff,	0x65पूर्ण,

		अणु	-1,			-1,	-1,	-1पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा अणु
		अचिन्हित अक्षर r[4];
		पूर्णांक len;
	पूर्ण regs[] = अणु
		अणुअणु 0x06, 0x02, 0x00, 0x31 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x02 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x02, 0x00, 0xc6 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x00, 0xff, 0xaf पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00, 0x03, 0xa0 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x00, 0x73, 0xaf पूर्ण, 4पूर्ण,
		अणुअणु 0x04, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x00, 0x04 पूर्ण, 2पूर्ण,
		अणुअणु 0x00, 0x04, 0x00, 0x0a पूर्ण, 4पूर्ण,
		अणुअणु 0x04, 0x14 पूर्ण, 2पूर्ण,
		अणुअणु 0x04, 0x14, 0x00, 0x00 पूर्ण, 4पूर्ण,
	पूर्ण;

	em28xx_gpio_set(dev, hauppauge_hvr930c_init);
	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x40);
	usleep_range(10000, 11000);
	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x44);
	usleep_range(10000, 11000);

	dev->i2c_client[dev->def_i2c_bus].addr = 0x82 >> 1;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++)
		i2c_master_send(&dev->i2c_client[dev->def_i2c_bus],
				regs[i].r, regs[i].len);
	em28xx_gpio_set(dev, hauppauge_hvr930c_end);

	msleep(100);

	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x44);
	msleep(30);

	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x45);
	usleep_range(10000, 11000);
पूर्ण

अटल व्योम terratec_h5_init(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;
	अटल स्थिर काष्ठा em28xx_reg_seq terratec_h5_init[] = अणु
		अणुEM2820_R08_GPIO_CTRL,		0xff,	0xff,	10पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	100पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xf2,	0xff,	50पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	100पूर्ण,
		अणु	-1,			-1,	-1,	-1पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा em28xx_reg_seq terratec_h5_end[] = अणु
		अणुEM2874_R80_GPIO_P0_CTRL,	0xe6,	0xff,	100पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xa6,	0xff,	50पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xe6,	0xff,	100पूर्ण,
		अणु	-1,			-1,	-1,	-1पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा अणु
		अचिन्हित अक्षर r[4];
		पूर्णांक len;
	पूर्ण regs[] = अणु
		अणुअणु 0x06, 0x02, 0x00, 0x31 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x02 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x02, 0x00, 0xc6 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x00, 0xff, 0xaf पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00, 0x03, 0xa0 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x00, 0x73, 0xaf पूर्ण, 4पूर्ण,
		अणुअणु 0x04, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x00, 0x04 पूर्ण, 2पूर्ण,
		अणुअणु 0x00, 0x04, 0x00, 0x0a पूर्ण, 4पूर्ण,
		अणुअणु 0x04, 0x14 पूर्ण, 2पूर्ण,
		अणुअणु 0x04, 0x14, 0x00, 0x00 पूर्ण, 4पूर्ण,
	पूर्ण;

	em28xx_gpio_set(dev, terratec_h5_init);
	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x40);
	usleep_range(10000, 11000);
	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x45);
	usleep_range(10000, 11000);

	dev->i2c_client[dev->def_i2c_bus].addr = 0x82 >> 1;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++)
		i2c_master_send(&dev->i2c_client[dev->def_i2c_bus],
				regs[i].r, regs[i].len);
	em28xx_gpio_set(dev, terratec_h5_end);
पूर्ण;

अटल व्योम terratec_htc_stick_init(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;

	/*
	 * GPIO configuration:
	 * 0xff: unknown (करोes not affect DVB-T).
	 * 0xf6: DRX-K (demodulator).
	 * 0xe6: unknown (करोes not affect DVB-T).
	 * 0xb6: unknown (करोes not affect DVB-T).
	 */
	अटल स्थिर काष्ठा em28xx_reg_seq terratec_htc_stick_init[] = अणु
		अणुEM2820_R08_GPIO_CTRL,		0xff,	0xff,	10पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	100पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xe6,	0xff,	50पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	100पूर्ण,
		अणु	-1,			-1,	-1,	-1पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा em28xx_reg_seq terratec_htc_stick_end[] = अणु
		अणुEM2874_R80_GPIO_P0_CTRL,	0xb6,	0xff,	100पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	50पूर्ण,
		अणु	-1,			-1,	-1,	-1पूर्ण,
	पूर्ण;

	/*
	 * Init the analog decoder (not yet supported), but
	 * it's probably still a good idea.
	 */
	अटल स्थिर काष्ठा अणु
		अचिन्हित अक्षर r[4];
		पूर्णांक len;
	पूर्ण regs[] = अणु
		अणुअणु 0x06, 0x02, 0x00, 0x31 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x02 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x02, 0x00, 0xc6 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x00, 0xff, 0xaf पूर्ण, 4पूर्ण,
	पूर्ण;

	em28xx_gpio_set(dev, terratec_htc_stick_init);

	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x40);
	usleep_range(10000, 11000);
	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x44);
	usleep_range(10000, 11000);

	dev->i2c_client[dev->def_i2c_bus].addr = 0x82 >> 1;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++)
		i2c_master_send(&dev->i2c_client[dev->def_i2c_bus],
				regs[i].r, regs[i].len);

	em28xx_gpio_set(dev, terratec_htc_stick_end);
पूर्ण;

अटल व्योम terratec_htc_usb_xs_init(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;

	अटल स्थिर काष्ठा em28xx_reg_seq terratec_htc_usb_xs_init[] = अणु
		अणुEM2820_R08_GPIO_CTRL,		0xff,	0xff,	10पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xb2,	0xff,	100पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xb2,	0xff,	50पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xb6,	0xff,	100पूर्ण,
		अणु	-1,			-1,	-1,	-1पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा em28xx_reg_seq terratec_htc_usb_xs_end[] = अणु
		अणुEM2874_R80_GPIO_P0_CTRL,	0xa6,	0xff,	100पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xa6,	0xff,	50पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xe6,	0xff,	100पूर्ण,
		अणु	-1,			-1,	-1,	-1पूर्ण,
	पूर्ण;

	/*
	 * Init the analog decoder (not yet supported), but
	 * it's probably still a good idea.
	 */
	अटल स्थिर काष्ठा अणु
		अचिन्हित अक्षर r[4];
		पूर्णांक len;
	पूर्ण regs[] = अणु
		अणुअणु 0x06, 0x02, 0x00, 0x31 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x02 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x02, 0x00, 0xc6 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x00, 0xff, 0xaf पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00, 0x03, 0xa0 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x00, 0x73, 0xaf पूर्ण, 4पूर्ण,
		अणुअणु 0x04, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x00, 0x04 पूर्ण, 2पूर्ण,
		अणुअणु 0x00, 0x04, 0x00, 0x0a पूर्ण, 4पूर्ण,
		अणुअणु 0x04, 0x14 पूर्ण, 2पूर्ण,
		अणुअणु 0x04, 0x14, 0x00, 0x00 पूर्ण, 4पूर्ण,
	पूर्ण;

	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x40);

	em28xx_gpio_set(dev, terratec_htc_usb_xs_init);

	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x40);
	usleep_range(10000, 11000);
	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x44);
	usleep_range(10000, 11000);

	dev->i2c_client[dev->def_i2c_bus].addr = 0x82 >> 1;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++)
		i2c_master_send(&dev->i2c_client[dev->def_i2c_bus],
				regs[i].r, regs[i].len);

	em28xx_gpio_set(dev, terratec_htc_usb_xs_end);
पूर्ण;

अटल व्योम pctv_520e_init(काष्ठा em28xx *dev)
अणु
	/*
	 * Init AVF4910B analog decoder. Looks like I2C traffic to
	 * digital demodulator and tuner are routed via AVF4910B.
	 */
	पूर्णांक i;
	अटल स्थिर काष्ठा अणु
		अचिन्हित अक्षर r[4];
		पूर्णांक len;
	पूर्ण regs[] = अणु
		अणुअणु 0x06, 0x02, 0x00, 0x31 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x02 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x02, 0x00, 0xc6 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x00, 0xff, 0xaf पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00, 0x03, 0xa0 पूर्ण, 4पूर्ण,
		अणुअणु 0x01, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x01, 0x00, 0x73, 0xaf पूर्ण, 4पूर्ण,
	पूर्ण;

	dev->i2c_client[dev->def_i2c_bus].addr = 0x82 >> 1; /* 0x41 */

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++)
		i2c_master_send(&dev->i2c_client[dev->def_i2c_bus],
				regs[i].r, regs[i].len);
पूर्ण;

अटल पूर्णांक em28xx_pctv_290e_set_lna(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा em28xx_i2c_bus *i2c_bus = fe->dvb->priv;
	काष्ठा em28xx *dev = i2c_bus->dev;
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (c->lna == 1)
		flags = GPIOF_OUT_INIT_HIGH; /* enable LNA */
	अन्यथा
		flags = GPIOF_OUT_INIT_LOW; /* disable LNA */

	ret = gpio_request_one(dvb->lna_gpio, flags, शून्य);
	अगर (ret)
		dev_err(&dev->पूर्णांकf->dev, "gpio request failed %d\n", ret);
	अन्यथा
		gpio_मुक्त(dvb->lna_gpio);

	वापस ret;
#अन्यथा
	dev_warn(&dev->पूर्णांकf->dev, "%s: LNA control is disabled (lna=%u)\n",
		 KBUILD_MODNAME, c->lna);
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक em28xx_pctv_292e_set_lna(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा em28xx_i2c_bus *i2c_bus = fe->dvb->priv;
	काष्ठा em28xx *dev = i2c_bus->dev;
	u8 lna;

	अगर (c->lna == 1)
		lna = 0x01;
	अन्यथा
		lna = 0x00;

	वापस em28xx_ग_लिखो_reg_bits(dev, EM2874_R80_GPIO_P0_CTRL, lna, 0x01);
पूर्ण

अटल पूर्णांक em28xx_mt352_terratec_xs_init(काष्ठा dvb_frontend *fe)
अणु
	/* Values extracted from a USB trace of the Terratec Winकरोws driver */
	अटल u8 घड़ी_config[]   = अणु CLOCK_CTL,  0x38, 0x2c पूर्ण;
	अटल u8 reset[]          = अणु RESET,      0x80 पूर्ण;
	अटल u8 adc_ctl_1_cfg[]  = अणु ADC_CTL_1,  0x40 पूर्ण;
	अटल u8 agc_cfg[]        = अणु AGC_TARGET, 0x28, 0xa0 पूर्ण;
	अटल u8 input_freq_cfg[] = अणु INPUT_FREQ_1, 0x31, 0xb8 पूर्ण;
	अटल u8 rs_err_cfg[]     = अणु RS_ERR_PER_1, 0x00, 0x4d पूर्ण;
	अटल u8 capt_range_cfg[] = अणु CAPT_RANGE, 0x32 पूर्ण;
	अटल u8 trl_nom_cfg[]    = अणु TRL_NOMINAL_RATE_1, 0x64, 0x00 पूर्ण;
	अटल u8 tps_given_cfg[]  = अणु TPS_GIVEN_1, 0x40, 0x80, 0x50 पूर्ण;
	अटल u8 tuner_go[]       = अणु TUNER_GO, 0x01पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	usleep_range(200, 250);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));
	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	mt352_ग_लिखो(fe, input_freq_cfg, माप(input_freq_cfg));
	mt352_ग_लिखो(fe, rs_err_cfg,     माप(rs_err_cfg));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));
	mt352_ग_लिखो(fe, trl_nom_cfg,    माप(trl_nom_cfg));
	mt352_ग_लिखो(fe, tps_given_cfg,  माप(tps_given_cfg));
	mt352_ग_लिखो(fe, tuner_go,       माप(tuner_go));
	वापस 0;
पूर्ण

अटल व्योम px_bcud_init(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;
	अटल स्थिर काष्ठा अणु
		अचिन्हित अक्षर r[4];
		पूर्णांक len;
	पूर्ण regs1[] = अणु
		अणुअणु 0x0e, 0x77 पूर्ण, 2पूर्ण,
		अणुअणु 0x0f, 0x77 पूर्ण, 2पूर्ण,
		अणुअणु 0x03, 0x90 पूर्ण, 2पूर्ण,
	पूर्ण, regs2[] = अणु
		अणुअणु 0x07, 0x01 पूर्ण, 2पूर्ण,
		अणुअणु 0x08, 0x10 पूर्ण, 2पूर्ण,
		अणुअणु 0x13, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x17, 0x00 पूर्ण, 2पूर्ण,
		अणुअणु 0x03, 0x01 पूर्ण, 2पूर्ण,
		अणुअणु 0x10, 0xb1 पूर्ण, 2पूर्ण,
		अणुअणु 0x11, 0x40 पूर्ण, 2पूर्ण,
		अणुअणु 0x85, 0x7a पूर्ण, 2पूर्ण,
		अणुअणु 0x87, 0x04 पूर्ण, 2पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा em28xx_reg_seq gpio[] = अणु
		अणुEM28XX_R06_I2C_CLK,		0x40,	0xff,	300पूर्ण,
		अणुEM2874_R80_GPIO_P0_CTRL,	0xfd,	0xff,	60पूर्ण,
		अणुEM28XX_R15_RGAIN,		0x20,	0xff,	0पूर्ण,
		अणुEM28XX_R16_GGAIN,		0x20,	0xff,	0पूर्ण,
		अणुEM28XX_R17_BGAIN,		0x20,	0xff,	0पूर्ण,
		अणुEM28XX_R18_ROFFSET,		0x00,	0xff,	0पूर्ण,
		अणुEM28XX_R19_GOFFSET,		0x00,	0xff,	0पूर्ण,
		अणुEM28XX_R1A_BOFFSET,		0x00,	0xff,	0पूर्ण,
		अणुEM28XX_R23_UOFFSET,		0x00,	0xff,	0पूर्ण,
		अणुEM28XX_R24_VOFFSET,		0x00,	0xff,	0पूर्ण,
		अणुEM28XX_R26_COMPR,		0x00,	0xff,	0पूर्ण,
		अणु0x13,				0x08,	0xff,	0पूर्ण,
		अणुEM28XX_R12_VINENABLE,		0x27,	0xff,	0पूर्ण,
		अणुEM28XX_R0C_USBSUSP,		0x10,	0xff,	0पूर्ण,
		अणुEM28XX_R27_OUTFMT,		0x00,	0xff,	0पूर्ण,
		अणुEM28XX_R10_VINMODE,		0x00,	0xff,	0पूर्ण,
		अणुEM28XX_R11_VINCTRL,		0x11,	0xff,	0पूर्ण,
		अणुEM2874_R50_IR_CONFIG,		0x01,	0xff,	0पूर्ण,
		अणुEM2874_R5F_TS_ENABLE,		0x80,	0xff,	0पूर्ण,
		अणुEM28XX_R06_I2C_CLK,		0x46,	0xff,	0पूर्ण,
	पूर्ण;
	em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, 0x46);
	/* sleeping ISDB-T */
	dev->dvb->i2c_client_demod->addr = 0x14;
	क्रम (i = 0; i < ARRAY_SIZE(regs1); i++)
		i2c_master_send(dev->dvb->i2c_client_demod,
				regs1[i].r, regs1[i].len);
	/* sleeping ISDB-S */
	dev->dvb->i2c_client_demod->addr = 0x15;
	क्रम (i = 0; i < ARRAY_SIZE(regs2); i++)
		i2c_master_send(dev->dvb->i2c_client_demod, regs2[i].r,
				regs2[i].len);
	क्रम (i = 0; i < ARRAY_SIZE(gpio); i++) अणु
		em28xx_ग_लिखो_reg_bits(dev, gpio[i].reg, gpio[i].val,
				      gpio[i].mask);
		अगर (gpio[i].sleep > 0)
			msleep(gpio[i].sleep);
	पूर्ण
पूर्ण;

अटल काष्ठा mt352_config terratec_xs_mt352_cfg = अणु
	.demod_address = (0x1e >> 1),
	.no_tuner = 1,
	.अगर2 = 45600,
	.demod_init = em28xx_mt352_terratec_xs_init,
पूर्ण;

अटल काष्ठा tda10023_config em28xx_tda10023_config = अणु
	.demod_address = 0x0c,
	.invert = 1,
पूर्ण;

अटल काष्ठा cxd2820r_config em28xx_cxd2820r_config = अणु
	.i2c_address = (0xd8 >> 1),
	.ts_mode = CXD2820R_TS_SERIAL,
पूर्ण;

अटल काष्ठा tda18271_config em28xx_cxd2820r_tda18271_config = अणु
	.output_opt = TDA18271_OUTPUT_LT_OFF,
	.gate = TDA18271_GATE_DIGITAL,
पूर्ण;

अटल काष्ठा zl10353_config em28xx_zl10353_no_i2c_gate_dev = अणु
	.demod_address = (0x1e >> 1),
	.disable_i2c_gate_ctrl = 1,
	.no_tuner = 1,
	.parallel_ts = 1,
पूर्ण;

अटल काष्ठा mt2060_config em28xx_mt2060_config = अणु
	.i2c_address = 0x60,
पूर्ण;

अटल काष्ठा qt1010_config em28xx_qt1010_config = अणु
	.i2c_address = 0x62
पूर्ण;

अटल स्थिर काष्ठा mb86a20s_config c3tech_duo_mb86a20s_config = अणु
	.demod_address = 0x10,
	.is_serial = true,
पूर्ण;

अटल काष्ठा tda18271_std_map mb86a20s_tda18271_config = अणु
	.dvbt_6   = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config c3tech_duo_tda18271_config = अणु
	.std_map = &mb86a20s_tda18271_config,
	.gate    = TDA18271_GATE_DIGITAL,
	.small_i2c = TDA18271_03_BYTE_CHUNK_INIT,
पूर्ण;

अटल काष्ठा tda18271_std_map drx_j_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 5000, .agc_mode = 3, .std = 0, .अगर_lvl = 1,
		      .rfagc_top = 0x37, पूर्ण,
	.qam_6    = अणु .अगर_freq = 5380, .agc_mode = 3, .std = 3, .अगर_lvl = 1,
		      .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config pinnacle_80e_dvb_config = अणु
	.std_map = &drx_j_std_map,
	.gate    = TDA18271_GATE_DIGITAL,
	.role    = TDA18271_MASTER,
पूर्ण;

अटल काष्ठा lgdt3306a_config hauppauge_01595_lgdt3306a_config = अणु
	.qam_अगर_khz         = 4000,
	.vsb_अगर_khz         = 3250,
	.spectral_inversion = 0,
	.deny_i2c_rptr      = 0,
	.mpeg_mode          = LGDT3306A_MPEG_SERIAL,
	.tpclk_edge         = LGDT3306A_TPCLK_RISING_EDGE,
	.tpvalid_polarity   = LGDT3306A_TP_VALID_HIGH,
	.xtalMHz            = 25,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल noअंतरभूत_क्रम_stack पूर्णांक em28xx_attach_xc3028(u8 addr, काष्ठा em28xx *dev)
अणु
	काष्ठा dvb_frontend *fe;
	काष्ठा xc2028_config cfg;
	काष्ठा xc2028_ctrl ctl;

	स_रखो(&cfg, 0, माप(cfg));
	cfg.i2c_adap  = &dev->i2c_adap[dev->def_i2c_bus];
	cfg.i2c_addr  = addr;

	स_रखो(&ctl, 0, माप(ctl));
	em28xx_setup_xc3028(dev, &ctl);
	cfg.ctrl  = &ctl;

	अगर (!dev->dvb->fe[0]) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"dvb frontend not attached. Can't attach xc3028\n");
		वापस -EINVAL;
	पूर्ण

	fe = dvb_attach(xc2028_attach, dev->dvb->fe[0], &cfg);
	अगर (!fe) अणु
		dev_err(&dev->पूर्णांकf->dev, "xc3028 attach failed\n");
		dvb_frontend_detach(dev->dvb->fe[0]);
		dev->dvb->fe[0] = शून्य;
		वापस -EINVAL;
	पूर्ण

	dev_info(&dev->पूर्णांकf->dev, "xc3028 attached\n");

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक em28xx_रेजिस्टर_dvb(काष्ठा em28xx_dvb *dvb, काष्ठा module *module,
			       काष्ठा em28xx *dev, काष्ठा device *device)
अणु
	पूर्णांक result;
	bool create_rf_connector = false;

	mutex_init(&dvb->lock);

	/* रेजिस्टर adapter */
	result = dvb_रेजिस्टर_adapter(&dvb->adapter,
				      dev_name(&dev->पूर्णांकf->dev), module,
				      device, adapter_nr);
	अगर (result < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "dvb_register_adapter failed (errno = %d)\n",
			 result);
		जाओ fail_adapter;
	पूर्ण
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	dvb->adapter.mdev = dev->media_dev;
#पूर्ण_अगर

	/* Ensure all frontends negotiate bus access */
	dvb->fe[0]->ops.ts_bus_ctrl = em28xx_dvb_bus_ctrl;
	अगर (dvb->fe[1])
		dvb->fe[1]->ops.ts_bus_ctrl = em28xx_dvb_bus_ctrl;

	dvb->adapter.priv = &dev->i2c_bus[dev->def_i2c_bus];

	/* रेजिस्टर frontend */
	result = dvb_रेजिस्टर_frontend(&dvb->adapter, dvb->fe[0]);
	अगर (result < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "dvb_register_frontend failed (errno = %d)\n",
			 result);
		जाओ fail_frontend0;
	पूर्ण

	/* रेजिस्टर 2nd frontend */
	अगर (dvb->fe[1]) अणु
		result = dvb_रेजिस्टर_frontend(&dvb->adapter, dvb->fe[1]);
		अगर (result < 0) अणु
			dev_warn(&dev->पूर्णांकf->dev,
				 "2nd dvb_register_frontend failed (errno = %d)\n",
				 result);
			जाओ fail_frontend1;
		पूर्ण
	पूर्ण

	/* रेजिस्टर demux stuff */
	dvb->demux.dmx.capabilities =
		DMX_TS_FILTERING | DMX_SECTION_FILTERING |
		DMX_MEMORY_BASED_FILTERING;
	dvb->demux.priv       = dvb;
	dvb->demux.filternum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.start_feed = em28xx_start_feed;
	dvb->demux.stop_feed  = em28xx_stop_feed;

	result = dvb_dmx_init(&dvb->demux);
	अगर (result < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "dvb_dmx_init failed (errno = %d)\n",
			 result);
		जाओ fail_dmx;
	पूर्ण

	dvb->dmxdev.filternum    = 256;
	dvb->dmxdev.demux        = &dvb->demux.dmx;
	dvb->dmxdev.capabilities = 0;
	result = dvb_dmxdev_init(&dvb->dmxdev, &dvb->adapter);
	अगर (result < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "dvb_dmxdev_init failed (errno = %d)\n",
			 result);
		जाओ fail_dmxdev;
	पूर्ण

	dvb->fe_hw.source = DMX_FRONTEND_0;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "add_frontend failed (DMX_FRONTEND_0, errno = %d)\n",
			 result);
		जाओ fail_fe_hw;
	पूर्ण

	dvb->fe_mem.source = DMX_MEMORY_FE;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	अगर (result < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "add_frontend failed (DMX_MEMORY_FE, errno = %d)\n",
			 result);
		जाओ fail_fe_mem;
	पूर्ण

	result = dvb->demux.dmx.connect_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "connect_frontend failed (errno = %d)\n",
			 result);
		जाओ fail_fe_conn;
	पूर्ण

	/* रेजिस्टर network adapter */
	dvb_net_init(&dvb->adapter, &dvb->net, &dvb->demux.dmx);

	/* If the analog part won't create RF connectors, DVB will करो it */
	अगर (!dev->has_video || dev->tuner_type == TUNER_ABSENT)
		create_rf_connector = true;

	result = dvb_create_media_graph(&dvb->adapter, create_rf_connector);
	अगर (result < 0)
		जाओ fail_create_graph;

	वापस 0;

fail_create_graph:
	dvb_net_release(&dvb->net);
fail_fe_conn:
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_mem);
fail_fe_mem:
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_hw);
fail_fe_hw:
	dvb_dmxdev_release(&dvb->dmxdev);
fail_dmxdev:
	dvb_dmx_release(&dvb->demux);
fail_dmx:
	अगर (dvb->fe[1])
		dvb_unरेजिस्टर_frontend(dvb->fe[1]);
	dvb_unरेजिस्टर_frontend(dvb->fe[0]);
fail_frontend1:
	अगर (dvb->fe[1])
		dvb_frontend_detach(dvb->fe[1]);
fail_frontend0:
	dvb_frontend_detach(dvb->fe[0]);
	dvb_unरेजिस्टर_adapter(&dvb->adapter);
fail_adapter:
	वापस result;
पूर्ण

अटल व्योम em28xx_unरेजिस्टर_dvb(काष्ठा em28xx_dvb *dvb)
अणु
	dvb_net_release(&dvb->net);
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	dvb_dmxdev_release(&dvb->dmxdev);
	dvb_dmx_release(&dvb->demux);
	अगर (dvb->fe[1])
		dvb_unरेजिस्टर_frontend(dvb->fe[1]);
	dvb_unरेजिस्टर_frontend(dvb->fe[0]);
	अगर (dvb->fe[1] && !dvb->करोnt_attach_fe1)
		dvb_frontend_detach(dvb->fe[1]);
	dvb_frontend_detach(dvb->fe[0]);
	dvb_unरेजिस्टर_adapter(&dvb->adapter);
पूर्ण

अटल पूर्णांक em28174_dvb_init_pctv_460e(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	काष्ठा tda10071_platक्रमm_data tda10071_pdata = अणुपूर्ण;
	काष्ठा a8293_platक्रमm_data a8293_pdata = अणुपूर्ण;

	/* attach demod + tuner combo */
	tda10071_pdata.clk = 40444000; /* 40.444 MHz */
	tda10071_pdata.i2c_wr_max = 64;
	tda10071_pdata.ts_mode = TDA10071_TS_SERIAL;
	tda10071_pdata.pll_multiplier = 20;
	tda10071_pdata.tuner_i2c_addr = 0x14;

	dvb->i2c_client_demod = dvb_module_probe("tda10071", "tda10071_cx24118",
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x55, &tda10071_pdata);
	अगर (!dvb->i2c_client_demod)
		वापस -ENODEV;

	dvb->fe[0] = tda10071_pdata.get_dvb_frontend(dvb->i2c_client_demod);

	/* attach SEC */
	a8293_pdata.dvb_frontend = dvb->fe[0];

	dvb->i2c_client_sec = dvb_module_probe("a8293", शून्य,
					       &dev->i2c_adap[dev->def_i2c_bus],
					       0x08, &a8293_pdata);
	अगर (!dvb->i2c_client_sec) अणु
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em28178_dvb_init_pctv_461e(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	काष्ठा i2c_adapter *i2c_adapter;
	काष्ठा m88ds3103_platक्रमm_data m88ds3103_pdata = अणुपूर्ण;
	काष्ठा ts2020_config ts2020_config = अणुपूर्ण;
	काष्ठा a8293_platक्रमm_data a8293_pdata = अणुपूर्ण;

	/* attach demod */
	m88ds3103_pdata.clk = 27000000;
	m88ds3103_pdata.i2c_wr_max = 33;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_PARALLEL;
	m88ds3103_pdata.ts_clk = 16000;
	m88ds3103_pdata.ts_clk_pol = 1;
	m88ds3103_pdata.agc = 0x99;

	dvb->i2c_client_demod = dvb_module_probe("m88ds3103", शून्य,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x68, &m88ds3103_pdata);
	अगर (!dvb->i2c_client_demod)
		वापस -ENODEV;

	dvb->fe[0] = m88ds3103_pdata.get_dvb_frontend(dvb->i2c_client_demod);
	i2c_adapter = m88ds3103_pdata.get_i2c_adapter(dvb->i2c_client_demod);

	/* attach tuner */
	ts2020_config.fe = dvb->fe[0];

	dvb->i2c_client_tuner = dvb_module_probe("ts2020", "ts2022",
						 i2c_adapter,
						 0x60, &ts2020_config);
	अगर (!dvb->i2c_client_tuner) अणु
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	/* delegate संकेत strength measurement to tuner */
	dvb->fe[0]->ops.पढ़ो_संकेत_strength =
			dvb->fe[0]->ops.tuner_ops.get_rf_strength;

	/* attach SEC */
	a8293_pdata.dvb_frontend = dvb->fe[0];
	dvb->i2c_client_sec = dvb_module_probe("a8293", शून्य,
					       &dev->i2c_adap[dev->def_i2c_bus],
					       0x08, &a8293_pdata);
	अगर (!dvb->i2c_client_sec) अणु
		dvb_module_release(dvb->i2c_client_tuner);
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em28178_dvb_init_pctv_461e_v2(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	काष्ठा i2c_adapter *i2c_adapter;
	काष्ठा m88ds3103_platक्रमm_data m88ds3103_pdata = अणुपूर्ण;
	काष्ठा ts2020_config ts2020_config = अणुपूर्ण;
	काष्ठा a8293_platक्रमm_data a8293_pdata = अणुपूर्ण;

	/* attach demod */
	m88ds3103_pdata.clk = 27000000;
	m88ds3103_pdata.i2c_wr_max = 33;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_PARALLEL;
	m88ds3103_pdata.ts_clk = 16000;
	m88ds3103_pdata.ts_clk_pol = 0;
	m88ds3103_pdata.agc = 0x99;
	m88ds3103_pdata.agc_inv = 0;
	m88ds3103_pdata.spec_inv = 0;
	dvb->i2c_client_demod = dvb_module_probe("m88ds3103", "m88ds3103b",
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x6a, &m88ds3103_pdata);

	अगर (!dvb->i2c_client_demod)
		वापस -ENODEV;

	dvb->fe[0] = m88ds3103_pdata.get_dvb_frontend(dvb->i2c_client_demod);
	i2c_adapter = m88ds3103_pdata.get_i2c_adapter(dvb->i2c_client_demod);

	/* attach tuner */
	ts2020_config.fe = dvb->fe[0];
	dvb->i2c_client_tuner = dvb_module_probe("ts2020", "ts2022",
						 i2c_adapter,
						 0x60, &ts2020_config);
	अगर (!dvb->i2c_client_tuner) अणु
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	/* delegate संकेत strength measurement to tuner */
	dvb->fe[0]->ops.पढ़ो_संकेत_strength =
			dvb->fe[0]->ops.tuner_ops.get_rf_strength;

	/* attach SEC */
	a8293_pdata.dvb_frontend = dvb->fe[0];
	dvb->i2c_client_sec = dvb_module_probe("a8293", शून्य,
					       &dev->i2c_adap[dev->def_i2c_bus],
					       0x08, &a8293_pdata);
	अगर (!dvb->i2c_client_sec) अणु
		dvb_module_release(dvb->i2c_client_tuner);
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em28178_dvb_init_pctv_292e(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	काष्ठा i2c_adapter *adapter;
	काष्ठा si2168_config si2168_config = अणुपूर्ण;
	काष्ठा si2157_config si2157_config = अणुपूर्ण;

	/* attach demod */
	si2168_config.i2c_adapter = &adapter;
	si2168_config.fe = &dvb->fe[0];
	si2168_config.ts_mode = SI2168_TS_PARALLEL;
	si2168_config.spectral_inversion = true;

	dvb->i2c_client_demod = dvb_module_probe("si2168", शून्य,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x64, &si2168_config);
	अगर (!dvb->i2c_client_demod)
		वापस -ENODEV;

	/* attach tuner */
	si2157_config.fe = dvb->fe[0];
	si2157_config.अगर_port = 1;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	si2157_config.mdev = dev->media_dev;
#पूर्ण_अगर
	dvb->i2c_client_tuner = dvb_module_probe("si2157", शून्य,
						 adapter,
						 0x60, &si2157_config);
	अगर (!dvb->i2c_client_tuner) अणु
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण
	dvb->fe[0]->ops.set_lna = em28xx_pctv_292e_set_lna;

	वापस 0;
पूर्ण

अटल पूर्णांक em28178_dvb_init_terratec_t2_stick_hd(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	काष्ठा i2c_adapter *adapter;
	काष्ठा si2168_config si2168_config = अणुपूर्ण;
	काष्ठा si2157_config si2157_config = अणुपूर्ण;

	/* attach demod */
	si2168_config.i2c_adapter = &adapter;
	si2168_config.fe = &dvb->fe[0];
	si2168_config.ts_mode = SI2168_TS_PARALLEL;

	dvb->i2c_client_demod = dvb_module_probe("si2168", शून्य,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x64, &si2168_config);
	अगर (!dvb->i2c_client_demod)
		वापस -ENODEV;

	/* attach tuner */
	स_रखो(&si2157_config, 0, माप(si2157_config));
	si2157_config.fe = dvb->fe[0];
	si2157_config.अगर_port = 0;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	si2157_config.mdev = dev->media_dev;
#पूर्ण_अगर
	dvb->i2c_client_tuner = dvb_module_probe("si2157", "si2146",
						 adapter,
						 0x60, &si2157_config);
	अगर (!dvb->i2c_client_tuner) अणु
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em28178_dvb_init_plex_px_bcud(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	काष्ठा tc90522_config tc90522_config = अणुपूर्ण;
	काष्ठा qm1d1c0042_config qm1d1c0042_config = अणुपूर्ण;

	/* attach demod */
	dvb->i2c_client_demod = dvb_module_probe("tc90522", "tc90522sat",
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x15, &tc90522_config);
	अगर (!dvb->i2c_client_demod)
		वापस -ENODEV;

	/* attach tuner */
	qm1d1c0042_config.fe = tc90522_config.fe;
	qm1d1c0042_config.lpf = 1;

	dvb->i2c_client_tuner = dvb_module_probe("qm1d1c0042", शून्य,
						 tc90522_config.tuner_i2c,
						 0x61, &qm1d1c0042_config);
	अगर (!dvb->i2c_client_tuner) अणु
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	dvb->fe[0] = tc90522_config.fe;
	px_bcud_init(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक em28174_dvb_init_hauppauge_wपूर्णांकv_dualhd_dvb(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	काष्ठा i2c_adapter *adapter;
	काष्ठा si2168_config si2168_config = अणुपूर्ण;
	काष्ठा si2157_config si2157_config = अणुपूर्ण;
	अचिन्हित अक्षर addr;

	/* attach demod */
	si2168_config.i2c_adapter = &adapter;
	si2168_config.fe = &dvb->fe[0];
	si2168_config.ts_mode = SI2168_TS_SERIAL;
	si2168_config.spectral_inversion = true;
	addr = (dev->ts == PRIMARY_TS) ? 0x64 : 0x67;

	dvb->i2c_client_demod = dvb_module_probe("si2168", शून्य,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 addr, &si2168_config);
	अगर (!dvb->i2c_client_demod)
		वापस -ENODEV;

	/* attach tuner */
	स_रखो(&si2157_config, 0, माप(si2157_config));
	si2157_config.fe = dvb->fe[0];
	si2157_config.अगर_port = 1;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	si2157_config.mdev = dev->media_dev;
#पूर्ण_अगर
	addr = (dev->ts == PRIMARY_TS) ? 0x60 : 0x63;

	dvb->i2c_client_tuner = dvb_module_probe("si2157", शून्य,
						 adapter,
						 addr, &si2157_config);
	अगर (!dvb->i2c_client_tuner) अणु
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em28174_dvb_init_hauppauge_wपूर्णांकv_dualhd_01595(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	काष्ठा i2c_adapter *adapter;
	काष्ठा lgdt3306a_config lgdt3306a_config =  अणुपूर्ण;
	काष्ठा si2157_config si2157_config = अणुपूर्ण;
	अचिन्हित अक्षर addr;

	/* attach demod */
	lgdt3306a_config = hauppauge_01595_lgdt3306a_config;
	lgdt3306a_config.fe = &dvb->fe[0];
	lgdt3306a_config.i2c_adapter = &adapter;
	addr = (dev->ts == PRIMARY_TS) ? 0x59 : 0x0e;

	dvb->i2c_client_demod = dvb_module_probe("lgdt3306a", शून्य,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 addr, &lgdt3306a_config);
	अगर (!dvb->i2c_client_demod)
		वापस -ENODEV;

	/* attach tuner */
	si2157_config.fe = dvb->fe[0];
	si2157_config.अगर_port = 1;
	si2157_config.inversion = 1;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	si2157_config.mdev = dev->media_dev;
#पूर्ण_अगर
	addr = (dev->ts == PRIMARY_TS) ? 0x60 : 0x62;

	dvb->i2c_client_tuner = dvb_module_probe("si2157", शून्य,
						 adapter,
						 addr, &si2157_config);
	अगर (!dvb->i2c_client_tuner) अणु
		dvb_module_release(dvb->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em2874_dvb_init_hauppauge_usb_quadhd(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb = dev->dvb;
	काष्ठा mxl692_config mxl692_config = अणुपूर्ण;
	अचिन्हित अक्षर addr;

	/* attach demod/tuner combo */
	mxl692_config.id = (dev->ts == PRIMARY_TS) ? 0 : 1;
	mxl692_config.fe = &dvb->fe[0];
	addr = (dev->ts == PRIMARY_TS) ? 0x60 : 0x63;

	dvb->i2c_client_demod = dvb_module_probe("mxl692", शून्य,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 addr, &mxl692_config);
	अगर (!dvb->i2c_client_demod)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_dvb_init(काष्ठा em28xx *dev)
अणु
	पूर्णांक result = 0, dvb_alt = 0;
	काष्ठा em28xx_dvb *dvb;
	काष्ठा usb_device *udev;

	अगर (dev->is_audio_only) अणु
		/* Shouldn't initialize IR क्रम this पूर्णांकerface */
		वापस 0;
	पूर्ण

	अगर (!dev->board.has_dvb) अणु
		/* This device करोes not support the extension */
		वापस 0;
	पूर्ण

	dev_info(&dev->पूर्णांकf->dev, "Binding DVB extension\n");

	dvb = kzalloc(माप(*dvb), GFP_KERNEL);
	अगर (!dvb)
		वापस -ENOMEM;

	dev->dvb = dvb;
	dvb->fe[0] = शून्य;
	dvb->fe[1] = शून्य;

	/* pre-allocate DVB usb transfer buffers */
	अगर (dev->dvb_xfer_bulk) अणु
		result = em28xx_alloc_urbs(dev, EM28XX_DIGITAL_MODE,
					   dev->dvb_xfer_bulk,
					   EM28XX_DVB_NUM_BUFS,
					   512,
					   EM28XX_DVB_BULK_PACKET_MULTIPLIER);
	पूर्ण अन्यथा अणु
		result = em28xx_alloc_urbs(dev, EM28XX_DIGITAL_MODE,
					   dev->dvb_xfer_bulk,
					   EM28XX_DVB_NUM_BUFS,
					   dev->dvb_max_pkt_size_isoc,
					   EM28XX_DVB_NUM_ISOC_PACKETS);
	पूर्ण
	अगर (result) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"failed to pre-allocate USB transfer buffers for DVB.\n");
		kमुक्त(dvb);
		dev->dvb = शून्य;
		वापस result;
	पूर्ण

	mutex_lock(&dev->lock);
	em28xx_set_mode(dev, EM28XX_DIGITAL_MODE);
	/* init frontend */
	चयन (dev->model) अणु
	हाल EM2874_BOARD_LEADERSHIP_ISDBT:
		dvb->fe[0] = dvb_attach(s921_attach,
					&sharp_isdbt,
					&dev->i2c_adap[dev->def_i2c_bus]);

		अगर (!dvb->fe[0]) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		अवरोध;
	हाल EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850:
	हाल EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950:
	हाल EM2880_BOARD_PINNACLE_PCTV_HD_PRO:
	हाल EM2880_BOARD_AMD_ATI_TV_WONDER_HD_600:
		dvb->fe[0] = dvb_attach(lgdt330x_attach,
					&em2880_lgdt3303_dev,
					0x0e,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (em28xx_attach_xc3028(0x61, dev) < 0) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM2880_BOARD_KWORLD_DVB_310U:
		dvb->fe[0] = dvb_attach(zl10353_attach,
					&em28xx_zl10353_with_xc3028,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (em28xx_attach_xc3028(0x61, dev) < 0) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900:
	हाल EM2882_BOARD_TERRATEC_HYBRID_XS:
	हाल EM2880_BOARD_EMPIRE_DUAL_TV:
	हाल EM2882_BOARD_ZOLID_HYBRID_TV_STICK:
		dvb->fe[0] = dvb_attach(zl10353_attach,
					&em28xx_zl10353_xc3028_no_i2c_gate,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (em28xx_attach_xc3028(0x61, dev) < 0) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM2880_BOARD_TERRATEC_HYBRID_XS:
	हाल EM2880_BOARD_TERRATEC_HYBRID_XS_FR:
	हाल EM2881_BOARD_PINNACLE_HYBRID_PRO:
	हाल EM2882_BOARD_DIKOM_DK300:
	हाल EM2882_BOARD_KWORLD_VS_DVBT:
		/*
		 * Those boards could have either a zl10353 or a mt352.
		 * If the chip id isn't क्रम zl10353, try mt352.
		 */
		dvb->fe[0] = dvb_attach(zl10353_attach,
					&em28xx_zl10353_xc3028_no_i2c_gate,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (!dvb->fe[0])
			dvb->fe[0] = dvb_attach(mt352_attach,
						&terratec_xs_mt352_cfg,
						&dev->i2c_adap[dev->def_i2c_bus]);

		अगर (em28xx_attach_xc3028(0x61, dev) < 0) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM2870_BOARD_TERRATEC_XS_MT2060:
		dvb->fe[0] = dvb_attach(zl10353_attach,
					&em28xx_zl10353_no_i2c_gate_dev,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (dvb->fe[0]) अणु
			dvb_attach(mt2060_attach, dvb->fe[0],
				   &dev->i2c_adap[dev->def_i2c_bus],
				   &em28xx_mt2060_config, 1220);
		पूर्ण
		अवरोध;
	हाल EM2870_BOARD_KWORLD_355U:
		dvb->fe[0] = dvb_attach(zl10353_attach,
					&em28xx_zl10353_no_i2c_gate_dev,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (dvb->fe[0])
			dvb_attach(qt1010_attach, dvb->fe[0],
				   &dev->i2c_adap[dev->def_i2c_bus],
				   &em28xx_qt1010_config);
		अवरोध;
	हाल EM2883_BOARD_KWORLD_HYBRID_330U:
	हाल EM2882_BOARD_EVGA_INDTUBE:
		dvb->fe[0] = dvb_attach(s5h1409_attach,
					&em28xx_s5h1409_with_xc3028,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (em28xx_attach_xc3028(0x61, dev) < 0) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM2882_BOARD_KWORLD_ATSC_315U:
		dvb->fe[0] = dvb_attach(lgdt330x_attach,
					&em2880_lgdt3303_dev,
					0x0e,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (dvb->fe[0]) अणु
			अगर (!dvb_attach(simple_tuner_attach, dvb->fe[0],
					&dev->i2c_adap[dev->def_i2c_bus],
					0x61, TUNER_THOMSON_DTT761X)) अणु
				result = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2:
	हाल EM2882_BOARD_PINNACLE_HYBRID_PRO_330E:
		dvb->fe[0] = dvb_attach(drxd_attach, &em28xx_drxd, शून्य,
					&dev->i2c_adap[dev->def_i2c_bus],
					&dev->पूर्णांकf->dev);
		अगर (em28xx_attach_xc3028(0x61, dev) < 0) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM2870_BOARD_REDDO_DVB_C_USB_BOX:
		/* Philips CU1216L NIM (Philips TDA10023 + Infineon TUA6034) */
		dvb->fe[0] = dvb_attach(tda10023_attach,
					&em28xx_tda10023_config,
					&dev->i2c_adap[dev->def_i2c_bus],
					0x48);
		अगर (dvb->fe[0]) अणु
			अगर (!dvb_attach(simple_tuner_attach, dvb->fe[0],
					&dev->i2c_adap[dev->def_i2c_bus],
					0x60, TUNER_PHILIPS_CU1216L)) अणु
				result = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल EM2870_BOARD_KWORLD_A340:
		dvb->fe[0] = dvb_attach(lgdt3305_attach,
					&em2870_lgdt3304_dev,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (!dvb->fe[0]) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अगर (!dvb_attach(tda18271_attach, dvb->fe[0], 0x60,
				&dev->i2c_adap[dev->def_i2c_bus],
				&kworld_a340_config)) अणु
			dvb_frontend_detach(dvb->fe[0]);
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM28174_BOARD_PCTV_290E:
		/* set शेष GPIO0 क्रम LNA, used अगर GPIOLIB is undefined */
		dvb->lna_gpio = CXD2820R_GPIO_E | CXD2820R_GPIO_O |
				CXD2820R_GPIO_L;
		dvb->fe[0] = dvb_attach(cxd2820r_attach,
					&em28xx_cxd2820r_config,
					&dev->i2c_adap[dev->def_i2c_bus],
					&dvb->lna_gpio);
		अगर (dvb->fe[0]) अणु
			/* FE 0 attach tuner */
			अगर (!dvb_attach(tda18271_attach,
					dvb->fe[0],
					0x60,
					&dev->i2c_adap[dev->def_i2c_bus],
					&em28xx_cxd2820r_tda18271_config)) अणु
				dvb_frontend_detach(dvb->fe[0]);
				result = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
			/* enable LNA क्रम DVB-T, DVB-T2 and DVB-C */
			result = gpio_request_one(dvb->lna_gpio,
						  GPIOF_OUT_INIT_LOW, शून्य);
			अगर (result)
				dev_err(&dev->पूर्णांकf->dev,
					"gpio request failed %d\n",
					result);
			अन्यथा
				gpio_मुक्त(dvb->lna_gpio);

			result = 0; /* जारी even set LNA fails */
#पूर्ण_अगर
			dvb->fe[0]->ops.set_lna = em28xx_pctv_290e_set_lna;
		पूर्ण

		अवरोध;
	हाल EM2884_BOARD_HAUPPAUGE_WINTV_HVR_930C:
	अणु
		काष्ठा xc5000_config cfg = अणुपूर्ण;

		hauppauge_hvr930c_init(dev);

		dvb->fe[0] = dvb_attach(drxk_attach,
					&hauppauge_930c_drxk,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (!dvb->fe[0]) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		/* FIXME: करो we need a pll semaphore? */
		dvb->fe[0]->sec_priv = dvb;
		sema_init(&dvb->pll_mutex, 1);
		dvb->gate_ctrl = dvb->fe[0]->ops.i2c_gate_ctrl;
		dvb->fe[0]->ops.i2c_gate_ctrl = drxk_gate_ctrl;

		/* Attach xc5000 */
		cfg.i2c_address  = 0x61;
		cfg.अगर_khz = 4000;

		अगर (dvb->fe[0]->ops.i2c_gate_ctrl)
			dvb->fe[0]->ops.i2c_gate_ctrl(dvb->fe[0], 1);
		अगर (!dvb_attach(xc5000_attach, dvb->fe[0],
				&dev->i2c_adap[dev->def_i2c_bus], &cfg)) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अगर (dvb->fe[0]->ops.i2c_gate_ctrl)
			dvb->fe[0]->ops.i2c_gate_ctrl(dvb->fe[0], 0);

		अवरोध;
	पूर्ण
	हाल EM2884_BOARD_TERRATEC_H5:
		terratec_h5_init(dev);

		dvb->fe[0] = dvb_attach(drxk_attach, &terratec_h5_drxk,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (!dvb->fe[0]) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		/* FIXME: करो we need a pll semaphore? */
		dvb->fe[0]->sec_priv = dvb;
		sema_init(&dvb->pll_mutex, 1);
		dvb->gate_ctrl = dvb->fe[0]->ops.i2c_gate_ctrl;
		dvb->fe[0]->ops.i2c_gate_ctrl = drxk_gate_ctrl;

		/* Attach tda18271 to DVB-C frontend */
		अगर (dvb->fe[0]->ops.i2c_gate_ctrl)
			dvb->fe[0]->ops.i2c_gate_ctrl(dvb->fe[0], 1);
		अगर (!dvb_attach(tda18271c2dd_attach, dvb->fe[0],
				&dev->i2c_adap[dev->def_i2c_bus], 0x60)) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अगर (dvb->fe[0]->ops.i2c_gate_ctrl)
			dvb->fe[0]->ops.i2c_gate_ctrl(dvb->fe[0], 0);

		अवरोध;
	हाल EM2884_BOARD_C3TECH_DIGITAL_DUO:
		dvb->fe[0] = dvb_attach(mb86a20s_attach,
					&c3tech_duo_mb86a20s_config,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (dvb->fe[0])
			dvb_attach(tda18271_attach, dvb->fe[0], 0x60,
				   &dev->i2c_adap[dev->def_i2c_bus],
				   &c3tech_duo_tda18271_config);
		अवरोध;
	हाल EM28174_BOARD_PCTV_460E:
		result = em28174_dvb_init_pctv_460e(dev);
		अगर (result)
			जाओ out_मुक्त;
		अवरोध;
	हाल EM2874_BOARD_DELOCK_61959:
	हाल EM2874_BOARD_MAXMEDIA_UB425_TC:
		/* attach demodulator */
		dvb->fe[0] = dvb_attach(drxk_attach, &maxmedia_ub425_tc_drxk,
					&dev->i2c_adap[dev->def_i2c_bus]);

		अगर (dvb->fe[0]) अणु
			/* disable I2C-gate */
			dvb->fe[0]->ops.i2c_gate_ctrl = शून्य;

			/* attach tuner */
			अगर (!dvb_attach(tda18271_attach, dvb->fe[0], 0x60,
					&dev->i2c_adap[dev->def_i2c_bus],
					&em28xx_cxd2820r_tda18271_config)) अणु
				dvb_frontend_detach(dvb->fe[0]);
				result = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल EM2884_BOARD_PCTV_510E:
	हाल EM2884_BOARD_PCTV_520E:
		pctv_520e_init(dev);

		/* attach demodulator */
		dvb->fe[0] = dvb_attach(drxk_attach, &pctv_520e_drxk,
					&dev->i2c_adap[dev->def_i2c_bus]);

		अगर (dvb->fe[0]) अणु
			/* attach tuner */
			अगर (!dvb_attach(tda18271_attach, dvb->fe[0], 0x60,
					&dev->i2c_adap[dev->def_i2c_bus],
					&em28xx_cxd2820r_tda18271_config)) अणु
				dvb_frontend_detach(dvb->fe[0]);
				result = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल EM2884_BOARD_ELGATO_EYETV_HYBRID_2008:
	हाल EM2884_BOARD_CINERGY_HTC_STICK:
	हाल EM2884_BOARD_TERRATEC_H6:
		terratec_htc_stick_init(dev);

		/* attach demodulator */
		dvb->fe[0] = dvb_attach(drxk_attach, &terratec_htc_stick_drxk,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (!dvb->fe[0]) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* Attach the demodulator. */
		अगर (!dvb_attach(tda18271_attach, dvb->fe[0], 0x60,
				&dev->i2c_adap[dev->def_i2c_bus],
				&em28xx_cxd2820r_tda18271_config)) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM2884_BOARD_TERRATEC_HTC_USB_XS:
		terratec_htc_usb_xs_init(dev);

		/* attach demodulator */
		dvb->fe[0] = dvb_attach(drxk_attach, &terratec_htc_stick_drxk,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (!dvb->fe[0]) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* Attach the demodulator. */
		अगर (!dvb_attach(tda18271_attach, dvb->fe[0], 0x60,
				&dev->i2c_adap[dev->def_i2c_bus],
				&em28xx_cxd2820r_tda18271_config)) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM2874_BOARD_KWORLD_UB435Q_V2:
		dvb->fe[0] = dvb_attach(lgdt3305_attach,
					&em2874_lgdt3305_dev,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (!dvb->fe[0]) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* Attach the demodulator. */
		अगर (!dvb_attach(tda18271_attach, dvb->fe[0], 0x60,
				&dev->i2c_adap[dev->def_i2c_bus],
				&kworld_ub435q_v2_config)) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल EM2874_BOARD_KWORLD_UB435Q_V3:
	अणु
		काष्ठा i2c_adapter *adapter = &dev->i2c_adap[dev->def_i2c_bus];

		dvb->fe[0] = dvb_attach(lgdt3305_attach,
					&em2874_lgdt3305_nogate_dev,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (!dvb->fe[0]) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* attach tuner */
		kworld_ub435q_v3_config.fe = dvb->fe[0];

		dvb->i2c_client_tuner = dvb_module_probe("tda18212", शून्य,
							 adapter, 0x60,
							 &kworld_ub435q_v3_config);
		अगर (!dvb->i2c_client_tuner) अणु
			dvb_frontend_detach(dvb->fe[0]);
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल EM2874_BOARD_PCTV_HD_MINI_80E:
		dvb->fe[0] = dvb_attach(drx39xxj_attach,
					&dev->i2c_adap[dev->def_i2c_bus]);
		अगर (dvb->fe[0]) अणु
			dvb->fe[0] = dvb_attach(tda18271_attach, dvb->fe[0],
						0x60,
						&dev->i2c_adap[dev->def_i2c_bus],
						&pinnacle_80e_dvb_config);
			अगर (!dvb->fe[0]) अणु
				result = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल EM28178_BOARD_PCTV_461E:
		result = em28178_dvb_init_pctv_461e(dev);
		अगर (result)
			जाओ out_मुक्त;
		अवरोध;
	हाल EM28178_BOARD_PCTV_461E_V2:
		result = em28178_dvb_init_pctv_461e_v2(dev);
		अगर (result)
			जाओ out_मुक्त;
		अवरोध;
	हाल EM28178_BOARD_PCTV_292E:
		result = em28178_dvb_init_pctv_292e(dev);
		अगर (result)
			जाओ out_मुक्त;
		अवरोध;
	हाल EM28178_BOARD_TERRATEC_T2_STICK_HD:
		result = em28178_dvb_init_terratec_t2_stick_hd(dev);
		अगर (result)
			जाओ out_मुक्त;
		अवरोध;
	हाल EM28178_BOARD_PLEX_PX_BCUD:
		result = em28178_dvb_init_plex_px_bcud(dev);
		अगर (result)
			जाओ out_मुक्त;
		अवरोध;
	हाल EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_DVB:
		result = em28174_dvb_init_hauppauge_wपूर्णांकv_dualhd_dvb(dev);
		अगर (result)
			जाओ out_मुक्त;
		अवरोध;
	हाल EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_01595:
		result = em28174_dvb_init_hauppauge_wपूर्णांकv_dualhd_01595(dev);
		अगर (result)
			जाओ out_मुक्त;
		अवरोध;
	हाल EM2874_BOARD_HAUPPAUGE_USB_QUADHD:
		result = em2874_dvb_init_hauppauge_usb_quadhd(dev);
		अगर (result)
			जाओ out_मुक्त;
		अवरोध;
	शेष:
		dev_err(&dev->पूर्णांकf->dev,
			"The frontend of your DVB/ATSC card isn't supported yet\n");
		अवरोध;
	पूर्ण
	अगर (!dvb->fe[0]) अणु
		dev_err(&dev->पूर्णांकf->dev, "frontend initialization failed\n");
		result = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	/* define general-purpose callback poपूर्णांकer */
	dvb->fe[0]->callback = em28xx_tuner_callback;
	अगर (dvb->fe[1])
		dvb->fe[1]->callback = em28xx_tuner_callback;

	/* रेजिस्टर everything */
	result = em28xx_रेजिस्टर_dvb(dvb, THIS_MODULE, dev, &dev->पूर्णांकf->dev);

	अगर (result < 0)
		जाओ out_मुक्त;

	अगर (dev->dvb_xfer_bulk) अणु
		dvb_alt = 0;
	पूर्ण अन्यथा अणु /* isoc */
		dvb_alt = dev->dvb_alt_isoc;
	पूर्ण

	udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	usb_set_पूर्णांकerface(udev, dev->अगरnum, dvb_alt);
	dev_info(&dev->पूर्णांकf->dev, "DVB extension successfully initialized\n");

	kref_get(&dev->ref);

ret:
	em28xx_set_mode(dev, EM28XX_SUSPEND);
	mutex_unlock(&dev->lock);
	वापस result;

out_मुक्त:
	em28xx_uninit_usb_xfer(dev, EM28XX_DIGITAL_MODE);
	kमुक्त(dvb);
	dev->dvb = शून्य;
	जाओ ret;
पूर्ण

अटल अंतरभूत व्योम prevent_sleep(काष्ठा dvb_frontend_ops *ops)
अणु
	ops->set_voltage = शून्य;
	ops->sleep = शून्य;
	ops->tuner_ops.sleep = शून्य;
पूर्ण

अटल पूर्णांक em28xx_dvb_fini(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_dvb *dvb;

	अगर (dev->is_audio_only) अणु
		/* Shouldn't initialize IR क्रम this पूर्णांकerface */
		वापस 0;
	पूर्ण

	अगर (!dev->board.has_dvb) अणु
		/* This device करोes not support the extension */
		वापस 0;
	पूर्ण

	अगर (!dev->dvb)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Closing DVB extension\n");

	dvb = dev->dvb;

	em28xx_uninit_usb_xfer(dev, EM28XX_DIGITAL_MODE);

	अगर (dev->disconnected) अणु
		/*
		 * We cannot tell the device to sleep
		 * once it has been unplugged.
		 */
		अगर (dvb->fe[0]) अणु
			prevent_sleep(&dvb->fe[0]->ops);
			dvb->fe[0]->निकास = DVB_FE_DEVICE_REMOVED;
		पूर्ण
		अगर (dvb->fe[1]) अणु
			prevent_sleep(&dvb->fe[1]->ops);
			dvb->fe[1]->निकास = DVB_FE_DEVICE_REMOVED;
		पूर्ण
	पूर्ण

	em28xx_unरेजिस्टर_dvb(dvb);

	/* release I2C module bindings */
	dvb_module_release(dvb->i2c_client_sec);
	dvb_module_release(dvb->i2c_client_tuner);
	dvb_module_release(dvb->i2c_client_demod);

	kमुक्त(dvb);
	dev->dvb = शून्य;
	kref_put(&dev->ref, em28xx_मुक्त_device);

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_dvb_suspend(काष्ठा em28xx *dev)
अणु
	पूर्णांक ret = 0;

	अगर (dev->is_audio_only)
		वापस 0;

	अगर (!dev->board.has_dvb)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Suspending DVB extension\n");
	अगर (dev->dvb) अणु
		काष्ठा em28xx_dvb *dvb = dev->dvb;

		अगर (dvb->fe[0]) अणु
			ret = dvb_frontend_suspend(dvb->fe[0]);
			dev_info(&dev->पूर्णांकf->dev, "fe0 suspend %d\n", ret);
		पूर्ण
		अगर (dvb->fe[1]) अणु
			dvb_frontend_suspend(dvb->fe[1]);
			dev_info(&dev->पूर्णांकf->dev, "fe1 suspend %d\n", ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_dvb_resume(काष्ठा em28xx *dev)
अणु
	पूर्णांक ret = 0;

	अगर (dev->is_audio_only)
		वापस 0;

	अगर (!dev->board.has_dvb)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Resuming DVB extension\n");
	अगर (dev->dvb) अणु
		काष्ठा em28xx_dvb *dvb = dev->dvb;

		अगर (dvb->fe[0]) अणु
			ret = dvb_frontend_resume(dvb->fe[0]);
			dev_info(&dev->पूर्णांकf->dev, "fe0 resume %d\n", ret);
		पूर्ण

		अगर (dvb->fe[1]) अणु
			ret = dvb_frontend_resume(dvb->fe[1]);
			dev_info(&dev->पूर्णांकf->dev, "fe1 resume %d\n", ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा em28xx_ops dvb_ops = अणु
	.id   = EM28XX_DVB,
	.name = "Em28xx dvb Extension",
	.init = em28xx_dvb_init,
	.fini = em28xx_dvb_fini,
	.suspend = em28xx_dvb_suspend,
	.resume = em28xx_dvb_resume,
पूर्ण;

अटल पूर्णांक __init em28xx_dvb_रेजिस्टर(व्योम)
अणु
	वापस em28xx_रेजिस्टर_extension(&dvb_ops);
पूर्ण

अटल व्योम __निकास em28xx_dvb_unरेजिस्टर(व्योम)
अणु
	em28xx_unरेजिस्टर_extension(&dvb_ops);
पूर्ण

module_init(em28xx_dvb_रेजिस्टर);
module_निकास(em28xx_dvb_unरेजिस्टर);
