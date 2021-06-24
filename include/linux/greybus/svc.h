<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus SVC code
 *
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */

#अगर_अघोषित __SVC_H
#घोषणा __SVC_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>

काष्ठा gb_svc_l2_समयr_cfg;

#घोषणा GB_SVC_CPORT_FLAG_E2EFC		BIT(0)
#घोषणा GB_SVC_CPORT_FLAG_CSD_N		BIT(1)
#घोषणा GB_SVC_CPORT_FLAG_CSV_N		BIT(2)

क्रमागत gb_svc_state अणु
	GB_SVC_STATE_RESET,
	GB_SVC_STATE_PROTOCOL_VERSION,
	GB_SVC_STATE_SVC_HELLO,
पूर्ण;

क्रमागत gb_svc_watchकरोg_bite अणु
	GB_SVC_WATCHDOG_BITE_RESET_UNIPRO = 0,
	GB_SVC_WATCHDOG_BITE_PANIC_KERNEL,
पूर्ण;

काष्ठा gb_svc_watchकरोg;

काष्ठा svc_debugfs_pwrmon_rail अणु
	u8 id;
	काष्ठा gb_svc *svc;
पूर्ण;

काष्ठा gb_svc अणु
	काष्ठा device		dev;

	काष्ठा gb_host_device	*hd;
	काष्ठा gb_connection	*connection;
	क्रमागत gb_svc_state	state;
	काष्ठा ida		device_id_map;
	काष्ठा workqueue_काष्ठा	*wq;

	u16 enकरो_id;
	u8 ap_पूर्णांकf_id;

	u8 protocol_major;
	u8 protocol_minor;

	काष्ठा gb_svc_watchकरोg	*watchकरोg;
	क्रमागत gb_svc_watchकरोg_bite action;

	काष्ठा dentry *debugfs_dentry;
	काष्ठा svc_debugfs_pwrmon_rail *pwrmon_rails;
पूर्ण;
#घोषणा to_gb_svc(d) container_of(d, काष्ठा gb_svc, dev)

काष्ठा gb_svc *gb_svc_create(काष्ठा gb_host_device *hd);
पूर्णांक gb_svc_add(काष्ठा gb_svc *svc);
व्योम gb_svc_del(काष्ठा gb_svc *svc);
व्योम gb_svc_put(काष्ठा gb_svc *svc);

पूर्णांक gb_svc_pwrmon_पूर्णांकf_sample_get(काष्ठा gb_svc *svc, u8 पूर्णांकf_id,
				  u8 measurement_type, u32 *value);
पूर्णांक gb_svc_पूर्णांकf_device_id(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u8 device_id);
पूर्णांक gb_svc_route_create(काष्ठा gb_svc *svc, u8 पूर्णांकf1_id, u8 dev1_id,
			       u8 पूर्णांकf2_id, u8 dev2_id);
व्योम gb_svc_route_destroy(काष्ठा gb_svc *svc, u8 पूर्णांकf1_id, u8 पूर्णांकf2_id);
पूर्णांक gb_svc_connection_create(काष्ठा gb_svc *svc, u8 पूर्णांकf1_id, u16 cport1_id,
			     u8 पूर्णांकf2_id, u16 cport2_id, u8 cport_flags);
व्योम gb_svc_connection_destroy(काष्ठा gb_svc *svc, u8 पूर्णांकf1_id, u16 cport1_id,
			       u8 पूर्णांकf2_id, u16 cport2_id);
पूर्णांक gb_svc_पूर्णांकf_eject(काष्ठा gb_svc *svc, u8 पूर्णांकf_id);
पूर्णांक gb_svc_पूर्णांकf_vsys_set(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, bool enable);
पूर्णांक gb_svc_पूर्णांकf_refclk_set(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, bool enable);
पूर्णांक gb_svc_पूर्णांकf_unipro_set(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, bool enable);
पूर्णांक gb_svc_पूर्णांकf_activate(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u8 *पूर्णांकf_type);
पूर्णांक gb_svc_पूर्णांकf_resume(काष्ठा gb_svc *svc, u8 पूर्णांकf_id);

पूर्णांक gb_svc_dme_peer_get(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u16 attr, u16 selector,
			u32 *value);
पूर्णांक gb_svc_dme_peer_set(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u16 attr, u16 selector,
			u32 value);
पूर्णांक gb_svc_पूर्णांकf_set_घातer_mode(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u8 hs_series,
			       u8 tx_mode, u8 tx_gear, u8 tx_nlanes,
			       u8 tx_amplitude, u8 tx_hs_equalizer,
			       u8 rx_mode, u8 rx_gear, u8 rx_nlanes,
			       u8 flags, u32 quirks,
			       काष्ठा gb_svc_l2_समयr_cfg *local,
			       काष्ठा gb_svc_l2_समयr_cfg *remote);
पूर्णांक gb_svc_पूर्णांकf_set_घातer_mode_hibernate(काष्ठा gb_svc *svc, u8 पूर्णांकf_id);
पूर्णांक gb_svc_ping(काष्ठा gb_svc *svc);
पूर्णांक gb_svc_watchकरोg_create(काष्ठा gb_svc *svc);
व्योम gb_svc_watchकरोg_destroy(काष्ठा gb_svc *svc);
bool gb_svc_watchकरोg_enabled(काष्ठा gb_svc *svc);
पूर्णांक gb_svc_watchकरोg_enable(काष्ठा gb_svc *svc);
पूर्णांक gb_svc_watchकरोg_disable(काष्ठा gb_svc *svc);

पूर्णांक gb_svc_protocol_init(व्योम);
व्योम gb_svc_protocol_निकास(व्योम);

#पूर्ण_अगर /* __SVC_H */
