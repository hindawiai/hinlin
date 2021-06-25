<शैली गुरु>
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop.c - मुख्य module part
 * Copyright (C) 2004-9 Patrick Boettcher <patrick.boettcher@posteo.de>
 * based on skystar2-driver Copyright (C) 2003 Vadim Catana, skystar@molकरोva.cc
 *
 * Acknowledgements:
 *   John Jurrius from BBTI, Inc. क्रम extensive support
 *                    with code examples and data books
 *   Bjarne Steinsbo, bjarne at steinsbo.com (some ideas क्रम rewriting)
 *
 * Contributions to the skystar2-driver have been करोne by
 *   Vincenzo Di Massa, hawk.it at tiscalinet.it (several DiSEqC fixes)
 *   Roberto Ragusa, r.ragusa at libero.it (polishing, restyling the code)
 *   Uwe Bugla, uwe.bugla at gmx.de (करोing tests, restyling code, writing करोcu)
 *   Niklas Peinecke, peinecke at gdv.uni-hannover.de (hardware pid/mac
 *               filtering)
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
 */

#समावेश "flexcop.h"

#घोषणा DRIVER_NAME "B2C2 FlexcopII/II(b)/III digital TV receiver chip"
#घोषणा DRIVER_AUTHOR "Patrick Boettcher <patrick.boettcher@posteo.de"

#अगर_घोषित CONFIG_DVB_B2C2_FLEXCOP_DEBUG
#घोषणा DEBSTATUS ""
#अन्यथा
#घोषणा DEBSTATUS " (debugging is not enabled)"
#पूर्ण_अगर

पूर्णांक b2c2_flexcop_debug;
EXPORT_SYMBOL_GPL(b2c2_flexcop_debug);
module_param_named(debug, b2c2_flexcop_debug,  पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		"set debug level (1=info,2=tuner,4=i2c,8=ts,16=sram,32=reg,64=i2cdump (|-able))."
		DEBSTATUS);
#अघोषित DEBSTATUS

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

/* global zero क्रम ibi values */
flexcop_ibi_value ibi_zero;

अटल पूर्णांक flexcop_dvb_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा flexcop_device *fc = dvbdmxfeed->demux->priv;
	वापस flexcop_pid_feed_control(fc, dvbdmxfeed, 1);
पूर्ण

अटल पूर्णांक flexcop_dvb_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा flexcop_device *fc = dvbdmxfeed->demux->priv;
	वापस flexcop_pid_feed_control(fc, dvbdmxfeed, 0);
पूर्ण

अटल पूर्णांक flexcop_dvb_init(काष्ठा flexcop_device *fc)
अणु
	पूर्णांक ret = dvb_रेजिस्टर_adapter(&fc->dvb_adapter,
			"FlexCop Digital TV device", fc->owner,
			fc->dev, adapter_nr);
	अगर (ret < 0) अणु
		err("error registering DVB adapter");
		वापस ret;
	पूर्ण
	fc->dvb_adapter.priv = fc;

	fc->demux.dmx.capabilities = (DMX_TS_FILTERING | DMX_SECTION_FILTERING
			| DMX_MEMORY_BASED_FILTERING);
	fc->demux.priv = fc;
	fc->demux.filternum = fc->demux.feednum = FC_MAX_FEED;
	fc->demux.start_feed = flexcop_dvb_start_feed;
	fc->demux.stop_feed = flexcop_dvb_stop_feed;
	fc->demux.ग_लिखो_to_decoder = शून्य;

	ret = dvb_dmx_init(&fc->demux);
	अगर (ret < 0) अणु
		err("dvb_dmx failed: error %d", ret);
		जाओ err_dmx;
	पूर्ण

	fc->hw_frontend.source = DMX_FRONTEND_0;

	fc->dmxdev.filternum = fc->demux.feednum;
	fc->dmxdev.demux = &fc->demux.dmx;
	fc->dmxdev.capabilities = 0;
	ret = dvb_dmxdev_init(&fc->dmxdev, &fc->dvb_adapter);
	अगर (ret < 0) अणु
		err("dvb_dmxdev_init failed: error %d", ret);
		जाओ err_dmx_dev;
	पूर्ण

	ret = fc->demux.dmx.add_frontend(&fc->demux.dmx, &fc->hw_frontend);
	अगर (ret < 0) अणु
		err("adding hw_frontend to dmx failed: error %d", ret);
		जाओ err_dmx_add_hw_frontend;
	पूर्ण

	fc->mem_frontend.source = DMX_MEMORY_FE;
	ret = fc->demux.dmx.add_frontend(&fc->demux.dmx, &fc->mem_frontend);
	अगर (ret < 0) अणु
		err("adding mem_frontend to dmx failed: error %d", ret);
		जाओ err_dmx_add_mem_frontend;
	पूर्ण

	ret = fc->demux.dmx.connect_frontend(&fc->demux.dmx, &fc->hw_frontend);
	अगर (ret < 0) अणु
		err("connect frontend failed: error %d", ret);
		जाओ err_connect_frontend;
	पूर्ण

	ret = dvb_net_init(&fc->dvb_adapter, &fc->dvbnet, &fc->demux.dmx);
	अगर (ret < 0) अणु
		err("dvb_net_init failed: error %d", ret);
		जाओ err_net;
	पूर्ण

	fc->init_state |= FC_STATE_DVB_INIT;
	वापस 0;

err_net:
	fc->demux.dmx.disconnect_frontend(&fc->demux.dmx);
err_connect_frontend:
	fc->demux.dmx.हटाओ_frontend(&fc->demux.dmx, &fc->mem_frontend);
err_dmx_add_mem_frontend:
	fc->demux.dmx.हटाओ_frontend(&fc->demux.dmx, &fc->hw_frontend);
err_dmx_add_hw_frontend:
	dvb_dmxdev_release(&fc->dmxdev);
err_dmx_dev:
	dvb_dmx_release(&fc->demux);
err_dmx:
	dvb_unरेजिस्टर_adapter(&fc->dvb_adapter);
	वापस ret;
पूर्ण

अटल व्योम flexcop_dvb_निकास(काष्ठा flexcop_device *fc)
अणु
	अगर (fc->init_state & FC_STATE_DVB_INIT) अणु
		dvb_net_release(&fc->dvbnet);

		fc->demux.dmx.बंद(&fc->demux.dmx);
		fc->demux.dmx.हटाओ_frontend(&fc->demux.dmx,
			&fc->mem_frontend);
		fc->demux.dmx.हटाओ_frontend(&fc->demux.dmx,
			&fc->hw_frontend);
		dvb_dmxdev_release(&fc->dmxdev);
		dvb_dmx_release(&fc->demux);
		dvb_unरेजिस्टर_adapter(&fc->dvb_adapter);
		deb_info("deinitialized dvb stuff\n");
	पूर्ण
	fc->init_state &= ~FC_STATE_DVB_INIT;
पूर्ण

/* these methods are necessary to achieve the दीर्घ-term-goal of hiding the
 * काष्ठा flexcop_device from the bus-parts */
व्योम flexcop_pass_dmx_data(काष्ठा flexcop_device *fc, u8 *buf, u32 len)
अणु
	dvb_dmx_swfilter(&fc->demux, buf, len);
पूर्ण
EXPORT_SYMBOL(flexcop_pass_dmx_data);

व्योम flexcop_pass_dmx_packets(काष्ठा flexcop_device *fc, u8 *buf, u32 no)
अणु
	dvb_dmx_swfilter_packets(&fc->demux, buf, no);
पूर्ण
EXPORT_SYMBOL(flexcop_pass_dmx_packets);

अटल व्योम flexcop_reset(काष्ठा flexcop_device *fc)
अणु
	flexcop_ibi_value v210, v204;

	/* reset the flexcop itself */
	fc->ग_लिखो_ibi_reg(fc,ctrl_208,ibi_zero);

	v210.raw = 0;
	v210.sw_reset_210.reset_block_000 = 1;
	v210.sw_reset_210.reset_block_100 = 1;
	v210.sw_reset_210.reset_block_200 = 1;
	v210.sw_reset_210.reset_block_300 = 1;
	v210.sw_reset_210.reset_block_400 = 1;
	v210.sw_reset_210.reset_block_500 = 1;
	v210.sw_reset_210.reset_block_600 = 1;
	v210.sw_reset_210.reset_block_700 = 1;
	v210.sw_reset_210.Block_reset_enable = 0xb2;
	v210.sw_reset_210.Special_controls = 0xc259;
	fc->ग_लिखो_ibi_reg(fc,sw_reset_210,v210);
	msleep(1);

	/* reset the periphical devices */

	v204 = fc->पढ़ो_ibi_reg(fc,misc_204);
	v204.misc_204.Per_reset_sig = 0;
	fc->ग_लिखो_ibi_reg(fc,misc_204,v204);
	msleep(1);
	v204.misc_204.Per_reset_sig = 1;
	fc->ग_लिखो_ibi_reg(fc,misc_204,v204);
पूर्ण

व्योम flexcop_reset_block_300(काष्ठा flexcop_device *fc)
अणु
	flexcop_ibi_value v208_save = fc->पढ़ो_ibi_reg(fc, ctrl_208),
			  v210 = fc->पढ़ो_ibi_reg(fc, sw_reset_210);

	deb_rdump("208: %08x, 210: %08x\n", v208_save.raw, v210.raw);
	fc->ग_लिखो_ibi_reg(fc,ctrl_208,ibi_zero);

	v210.sw_reset_210.reset_block_300 = 1;
	v210.sw_reset_210.Block_reset_enable = 0xb2;

	fc->ग_लिखो_ibi_reg(fc,sw_reset_210,v210);
	fc->ग_लिखो_ibi_reg(fc,ctrl_208,v208_save);
पूर्ण

काष्ठा flexcop_device *flexcop_device_kदो_स्मृति(माप_प्रकार bus_specअगरic_len)
अणु
	व्योम *bus;
	काष्ठा flexcop_device *fc = kzalloc(माप(काष्ठा flexcop_device),
				GFP_KERNEL);
	अगर (!fc) अणु
		err("no memory");
		वापस शून्य;
	पूर्ण

	bus = kzalloc(bus_specअगरic_len, GFP_KERNEL);
	अगर (!bus) अणु
		err("no memory");
		kमुक्त(fc);
		वापस शून्य;
	पूर्ण

	fc->bus_specअगरic = bus;

	वापस fc;
पूर्ण
EXPORT_SYMBOL(flexcop_device_kदो_स्मृति);

व्योम flexcop_device_kमुक्त(काष्ठा flexcop_device *fc)
अणु
	kमुक्त(fc->bus_specअगरic);
	kमुक्त(fc);
पूर्ण
EXPORT_SYMBOL(flexcop_device_kमुक्त);

पूर्णांक flexcop_device_initialize(काष्ठा flexcop_device *fc)
अणु
	पूर्णांक ret;
	ibi_zero.raw = 0;

	flexcop_reset(fc);
	flexcop_determine_revision(fc);
	flexcop_sram_init(fc);
	flexcop_hw_filter_init(fc);
	flexcop_smc_ctrl(fc, 0);

	ret = flexcop_dvb_init(fc);
	अगर (ret)
		जाओ error;

	/* i2c has to be करोne beक्रमe करोing EEProm stuff -
	 * because the EEProm is accessed via i2c */
	ret = flexcop_i2c_init(fc);
	अगर (ret)
		जाओ error;

	/* करो the MAC address पढ़ोing after initializing the dvb_adapter */
	अगर (fc->get_mac_addr(fc, 0) == 0) अणु
		u8 *b = fc->dvb_adapter.proposed_mac;
		info("MAC address = %pM", b);
		flexcop_set_mac_filter(fc,b);
		flexcop_mac_filter_ctrl(fc,1);
	पूर्ण अन्यथा
		warn("reading of MAC address failed.\n");

	ret = flexcop_frontend_init(fc);
	अगर (ret)
		जाओ error;

	flexcop_device_name(fc,"initialization of","complete");
	वापस 0;

error:
	flexcop_device_निकास(fc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(flexcop_device_initialize);

व्योम flexcop_device_निकास(काष्ठा flexcop_device *fc)
अणु
	flexcop_frontend_निकास(fc);
	flexcop_i2c_निकास(fc);
	flexcop_dvb_निकास(fc);
पूर्ण
EXPORT_SYMBOL(flexcop_device_निकास);

अटल पूर्णांक flexcop_module_init(व्योम)
अणु
	info(DRIVER_NAME " loaded successfully");
	वापस 0;
पूर्ण

अटल व्योम flexcop_module_cleanup(व्योम)
अणु
	info(DRIVER_NAME " unloaded successfully");
पूर्ण

module_init(flexcop_module_init);
module_निकास(flexcop_module_cleanup);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_NAME);
MODULE_LICENSE("GPL");
