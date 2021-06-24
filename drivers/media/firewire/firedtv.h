<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * FireDTV driver (क्रमmerly known as FireSAT)
 *
 * Copyright (C) 2004 Andreas Monitzer <andy@monitzer.com>
 * Copyright (C) 2008 Henrik Kurelid <henrik@kurelid.se>
 */

#अगर_अघोषित _FIREDTV_H
#घोषणा _FIREDTV_H

#समावेश <linux/समय.स>
#समावेश <linux/dvb/dmx.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/list.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

#समावेश <media/demux.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvbdev.h>

काष्ठा firedtv_tuner_status अणु
	अचिन्हित active_प्रणाली:8;
	अचिन्हित searching:1;
	अचिन्हित moving:1;
	अचिन्हित no_rf:1;
	अचिन्हित input:1;
	अचिन्हित selected_antenna:7;
	अचिन्हित ber:32;
	अचिन्हित संकेत_strength:8;
	अचिन्हित raster_frequency:2;
	अचिन्हित rf_frequency:22;
	अचिन्हित man_dep_info_length:8;
	अचिन्हित front_end_error:1;
	अचिन्हित antenna_error:1;
	अचिन्हित front_end_घातer_status:1;
	अचिन्हित घातer_supply:1;
	अचिन्हित carrier_noise_ratio:16;
	अचिन्हित घातer_supply_voltage:8;
	अचिन्हित antenna_voltage:8;
	अचिन्हित firewire_bus_voltage:8;
	अचिन्हित ca_mmi:1;
	अचिन्हित ca_pmt_reply:1;
	अचिन्हित ca_date_समय_request:1;
	अचिन्हित ca_application_info:1;
	अचिन्हित ca_module_present_status:1;
	अचिन्हित ca_dvb_flag:1;
	अचिन्हित ca_error_flag:1;
	अचिन्हित ca_initialization_status:1;
पूर्ण;

क्रमागत model_type अणु
	FIREDTV_UNKNOWN = 0,
	FIREDTV_DVB_S   = 1,
	FIREDTV_DVB_C   = 2,
	FIREDTV_DVB_T   = 3,
	FIREDTV_DVB_S2  = 4,
पूर्ण;

काष्ठा device;
काष्ठा input_dev;
काष्ठा fdtv_ir_context;

काष्ठा firedtv अणु
	काष्ठा device *device;
	काष्ठा list_head list;

	काष्ठा dvb_adapter	adapter;
	काष्ठा dmxdev		dmxdev;
	काष्ठा dvb_demux	demux;
	काष्ठा dmx_frontend	frontend;
	काष्ठा dvb_net		dvbnet;
	काष्ठा dvb_frontend	fe;

	काष्ठा dvb_device	*cadev;
	पूर्णांक			ca_last_command;
	पूर्णांक			ca_समय_पूर्णांकerval;

	काष्ठा mutex		avc_mutex;
	रुको_queue_head_t	avc_रुको;
	bool			avc_reply_received;
	काष्ठा work_काष्ठा	remote_ctrl_work;
	काष्ठा input_dev	*remote_ctrl_dev;

	क्रमागत model_type		type;
	अक्षर			subunit;
	s8			isochannel;
	काष्ठा fdtv_ir_context	*ir_context;

	क्रमागत fe_sec_voltage	voltage;
	क्रमागत fe_sec_tone_mode	tone;

	काष्ठा mutex		demux_mutex;
	अचिन्हित दीर्घ		channel_active;
	u16			channel_pid[16];

	पूर्णांक			avc_data_length;
	u8			avc_data[512];
पूर्ण;

/* firedtv-avc.c */
पूर्णांक avc_recv(काष्ठा firedtv *fdtv, व्योम *data, माप_प्रकार length);
पूर्णांक avc_tuner_status(काष्ठा firedtv *fdtv, काष्ठा firedtv_tuner_status *stat);
काष्ठा dtv_frontend_properties;
पूर्णांक avc_tuner_dsd(काष्ठा firedtv *fdtv, काष्ठा dtv_frontend_properties *params);
पूर्णांक avc_tuner_set_pids(काष्ठा firedtv *fdtv, अचिन्हित अक्षर pidc, u16 pid[]);
पूर्णांक avc_tuner_get_ts(काष्ठा firedtv *fdtv);
पूर्णांक avc_identअगरy_subunit(काष्ठा firedtv *fdtv);
काष्ठा dvb_diseqc_master_cmd;
पूर्णांक avc_lnb_control(काष्ठा firedtv *fdtv, अक्षर voltage, अक्षर burst,
		    अक्षर conttone, अक्षर nrdiseq,
		    काष्ठा dvb_diseqc_master_cmd *diseqcmd);
व्योम avc_remote_ctrl_work(काष्ठा work_काष्ठा *work);
पूर्णांक avc_रेजिस्टर_remote_control(काष्ठा firedtv *fdtv);
पूर्णांक avc_ca_app_info(काष्ठा firedtv *fdtv, अचिन्हित अक्षर *app_info,
		    अचिन्हित पूर्णांक *len);
पूर्णांक avc_ca_info(काष्ठा firedtv *fdtv, अचिन्हित अक्षर *app_info,
		अचिन्हित पूर्णांक *len);
पूर्णांक avc_ca_reset(काष्ठा firedtv *fdtv);
पूर्णांक avc_ca_pmt(काष्ठा firedtv *fdtv, अक्षर *app_info, पूर्णांक length);
पूर्णांक avc_ca_get_समय_date(काष्ठा firedtv *fdtv, पूर्णांक *पूर्णांकerval);
पूर्णांक avc_ca_enter_menu(काष्ठा firedtv *fdtv);
पूर्णांक avc_ca_get_mmi(काष्ठा firedtv *fdtv, अक्षर *mmi_object, अचिन्हित पूर्णांक *len);
पूर्णांक cmp_establish_pp_connection(काष्ठा firedtv *fdtv, पूर्णांक plug, पूर्णांक channel);
व्योम cmp_अवरोध_pp_connection(काष्ठा firedtv *fdtv, पूर्णांक plug, पूर्णांक channel);

/* firedtv-ci.c */
पूर्णांक fdtv_ca_रेजिस्टर(काष्ठा firedtv *fdtv);
व्योम fdtv_ca_release(काष्ठा firedtv *fdtv);

/* firedtv-dvb.c */
पूर्णांक fdtv_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed);
पूर्णांक fdtv_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed);
पूर्णांक fdtv_dvb_रेजिस्टर(काष्ठा firedtv *fdtv, स्थिर अक्षर *name);
व्योम fdtv_dvb_unरेजिस्टर(काष्ठा firedtv *fdtv);

/* firedtv-fe.c */
व्योम fdtv_frontend_init(काष्ठा firedtv *fdtv, स्थिर अक्षर *name);

/* firedtv-fw.c */
पूर्णांक fdtv_lock(काष्ठा firedtv *fdtv, u64 addr, व्योम *data);
पूर्णांक fdtv_पढ़ो(काष्ठा firedtv *fdtv, u64 addr, व्योम *data);
पूर्णांक fdtv_ग_लिखो(काष्ठा firedtv *fdtv, u64 addr, व्योम *data, माप_प्रकार len);
पूर्णांक fdtv_start_iso(काष्ठा firedtv *fdtv);
व्योम fdtv_stop_iso(काष्ठा firedtv *fdtv);

/* firedtv-rc.c */
#अगर_घोषित CONFIG_DVB_FIREDTV_INPUT
पूर्णांक fdtv_रेजिस्टर_rc(काष्ठा firedtv *fdtv, काष्ठा device *dev);
व्योम fdtv_unरेजिस्टर_rc(काष्ठा firedtv *fdtv);
व्योम fdtv_handle_rc(काष्ठा firedtv *fdtv, अचिन्हित पूर्णांक code);
#अन्यथा
अटल अंतरभूत पूर्णांक fdtv_रेजिस्टर_rc(काष्ठा firedtv *fdtv,
				   काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम fdtv_unरेजिस्टर_rc(काष्ठा firedtv *fdtv) अणुपूर्ण
अटल अंतरभूत व्योम fdtv_handle_rc(काष्ठा firedtv *fdtv, अचिन्हित पूर्णांक code) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _FIREDTV_H */
