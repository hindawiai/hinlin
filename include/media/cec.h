<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cec - HDMI Consumer Electronics Control support header
 *
 * Copyright 2016 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _MEDIA_CEC_H
#घोषणा _MEDIA_CEC_H

#समावेश <linux/poll.h>
#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/समयr.h>
#समावेश <linux/cec-funcs.h>
#समावेश <media/rc-core.h>

#घोषणा CEC_CAP_DEFAULTS (CEC_CAP_LOG_ADDRS | CEC_CAP_TRANSMIT | \
			  CEC_CAP_PASSTHROUGH | CEC_CAP_RC)

/**
 * काष्ठा cec_devnode - cec device node
 * @dev:	cec device
 * @cdev:	cec अक्षरacter device
 * @minor:	device node minor number
 * @रेजिस्टरed:	the device was correctly रेजिस्टरed
 * @unरेजिस्टरed: the device was unरेजिस्टरed
 * @fhs:	the list of खोलो filehandles (cec_fh)
 * @lock:	lock to control access to this काष्ठाure
 *
 * This काष्ठाure represents a cec-related device node.
 *
 * The @parent is a physical device. It must be set by core or device drivers
 * beक्रमe रेजिस्टरing the node.
 */
काष्ठा cec_devnode अणु
	/* sysfs */
	काष्ठा device dev;
	काष्ठा cdev cdev;

	/* device info */
	पूर्णांक minor;
	bool रेजिस्टरed;
	bool unरेजिस्टरed;
	काष्ठा list_head fhs;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा cec_adapter;
काष्ठा cec_data;
काष्ठा cec_pin;
काष्ठा cec_notअगरier;

काष्ठा cec_data अणु
	काष्ठा list_head list;
	काष्ठा list_head xfer_list;
	काष्ठा cec_adapter *adap;
	काष्ठा cec_msg msg;
	काष्ठा cec_fh *fh;
	काष्ठा delayed_work work;
	काष्ठा completion c;
	u8 attempts;
	bool blocking;
	bool completed;
पूर्ण;

काष्ठा cec_msg_entry अणु
	काष्ठा list_head	list;
	काष्ठा cec_msg		msg;
पूर्ण;

काष्ठा cec_event_entry अणु
	काष्ठा list_head	list;
	काष्ठा cec_event	ev;
पूर्ण;

#घोषणा CEC_NUM_CORE_EVENTS 2
#घोषणा CEC_NUM_EVENTS CEC_EVENT_PIN_5V_HIGH

काष्ठा cec_fh अणु
	काष्ठा list_head	list;
	काष्ठा list_head	xfer_list;
	काष्ठा cec_adapter	*adap;
	u8			mode_initiator;
	u8			mode_follower;

	/* Events */
	रुको_queue_head_t	रुको;
	काष्ठा mutex		lock;
	काष्ठा list_head	events[CEC_NUM_EVENTS]; /* queued events */
	u16			queued_events[CEC_NUM_EVENTS];
	अचिन्हित पूर्णांक		total_queued_events;
	काष्ठा cec_event_entry	core_events[CEC_NUM_CORE_EVENTS];
	काष्ठा list_head	msgs; /* queued messages */
	अचिन्हित पूर्णांक		queued_msgs;
पूर्ण;

#घोषणा CEC_SIGNAL_FREE_TIME_RETRY		3
#घोषणा CEC_SIGNAL_FREE_TIME_NEW_INITIATOR	5
#घोषणा CEC_SIGNAL_FREE_TIME_NEXT_XFER		7

/* The nominal data bit period is 2.4 ms */
#घोषणा CEC_FREE_TIME_TO_USEC(ft)		((ft) * 2400)

काष्ठा cec_adap_ops अणु
	/* Low-level callbacks */
	पूर्णांक (*adap_enable)(काष्ठा cec_adapter *adap, bool enable);
	पूर्णांक (*adap_monitor_all_enable)(काष्ठा cec_adapter *adap, bool enable);
	पूर्णांक (*adap_monitor_pin_enable)(काष्ठा cec_adapter *adap, bool enable);
	पूर्णांक (*adap_log_addr)(काष्ठा cec_adapter *adap, u8 logical_addr);
	पूर्णांक (*adap_transmit)(काष्ठा cec_adapter *adap, u8 attempts,
			     u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg);
	व्योम (*adap_status)(काष्ठा cec_adapter *adap, काष्ठा seq_file *file);
	व्योम (*adap_मुक्त)(काष्ठा cec_adapter *adap);

	/* Error injection callbacks */
	पूर्णांक (*error_inj_show)(काष्ठा cec_adapter *adap, काष्ठा seq_file *sf);
	bool (*error_inj_parse_line)(काष्ठा cec_adapter *adap, अक्षर *line);

	/* High-level CEC message callback */
	पूर्णांक (*received)(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg);
पूर्ण;

/*
 * The minimum message length you can receive (excepting poll messages) is 2.
 * With a transfer rate of at most 36 bytes per second this makes 18 messages
 * per second worst हाल.
 *
 * We queue at most 3 seconds worth of received messages. The CEC specअगरication
 * requires that messages are replied to within a second, so 3 seconds should
 * give more than enough margin. Since most messages are actually more than 2
 * bytes, this is in practice a lot more than 3 seconds.
 */
#घोषणा CEC_MAX_MSG_RX_QUEUE_SZ		(18 * 3)

/*
 * The transmit queue is limited to 1 second worth of messages (worst हाल).
 * Messages can be transmitted by userspace and kernel space. But क्रम both it
 * makes no sense to have a lot of messages queued up. One second seems
 * reasonable.
 */
#घोषणा CEC_MAX_MSG_TX_QUEUE_SZ		(18 * 1)

/**
 * काष्ठा cec_adapter - cec adapter काष्ठाure
 * @owner:		module owner
 * @name:		name of the CEC adapter
 * @devnode:		device node क्रम the /dev/cecX device
 * @lock:		mutex controlling access to this काष्ठाure
 * @rc:			remote control device
 * @transmit_queue:	queue of pending transmits
 * @transmit_queue_sz:	number of pending transmits
 * @रुको_queue:		queue of transmits रुकोing क्रम a reply
 * @transmitting:	CEC messages currently being transmitted
 * @transmit_in_progress: true अगर a transmit is in progress
 * @kthपढ़ो_config:	kthपढ़ो used to configure a CEC adapter
 * @config_completion:	used to संकेत completion of the config kthपढ़ो
 * @kthपढ़ो:		मुख्य CEC processing thपढ़ो
 * @kthपढ़ो_रुकोq:	मुख्य CEC processing रुको_queue
 * @ops:		cec adapter ops
 * @priv:		cec driver's निजी data
 * @capabilities:	cec adapter capabilities
 * @available_log_addrs: maximum number of available logical addresses
 * @phys_addr:		the current physical address
 * @needs_hpd:		अगर true, then the HDMI HotPlug Detect pin must be high
 *	in order to transmit or receive CEC messages. This is usually a HW
 *	limitation.
 * @is_configuring:	the CEC adapter is configuring (i.e. claiming LAs)
 * @is_configured:	the CEC adapter is configured (i.e. has claimed LAs)
 * @cec_pin_is_high:	अगर true then the CEC pin is high. Only used with the
 *	CEC pin framework.
 * @adap_controls_phys_addr: अगर true, then the CEC adapter controls the
 *	physical address, i.e. the CEC hardware can detect HPD changes and
 *	पढ़ो the EDID and is not dependent on an बाह्यal HDMI driver.
 *	Drivers that need this can set this field to true after the
 *	cec_allocate_adapter() call.
 * @last_initiator:	the initiator of the last transmitted message.
 * @monitor_all_cnt:	number of filehandles monitoring all msgs
 * @monitor_pin_cnt:	number of filehandles monitoring pin changes
 * @follower_cnt:	number of filehandles in follower mode
 * @cec_follower:	filehandle of the exclusive follower
 * @cec_initiator:	filehandle of the exclusive initiator
 * @passthrough:	अगर true, then the exclusive follower is in
 *	passthrough mode.
 * @log_addrs:		current logical addresses
 * @conn_info:		current connector info
 * @tx_समयouts:	number of transmit समयouts
 * @notअगरier:		CEC notअगरier
 * @pin:		CEC pin status काष्ठा
 * @cec_dir:		debugfs cec directory
 * @status_file:	debugfs cec status file
 * @error_inj_file:	debugfs cec error injection file
 * @sequence:		transmit sequence counter
 * @input_phys:		remote control input_phys name
 *
 * This काष्ठाure represents a cec adapter.
 */
काष्ठा cec_adapter अणु
	काष्ठा module *owner;
	अक्षर name[32];
	काष्ठा cec_devnode devnode;
	काष्ठा mutex lock;
	काष्ठा rc_dev *rc;

	काष्ठा list_head transmit_queue;
	अचिन्हित पूर्णांक transmit_queue_sz;
	काष्ठा list_head रुको_queue;
	काष्ठा cec_data *transmitting;
	bool transmit_in_progress;

	काष्ठा task_काष्ठा *kthपढ़ो_config;
	काष्ठा completion config_completion;

	काष्ठा task_काष्ठा *kthपढ़ो;
	रुको_queue_head_t kthपढ़ो_रुकोq;

	स्थिर काष्ठा cec_adap_ops *ops;
	व्योम *priv;
	u32 capabilities;
	u8 available_log_addrs;

	u16 phys_addr;
	bool needs_hpd;
	bool is_configuring;
	bool is_configured;
	bool cec_pin_is_high;
	bool adap_controls_phys_addr;
	u8 last_initiator;
	u32 monitor_all_cnt;
	u32 monitor_pin_cnt;
	u32 follower_cnt;
	काष्ठा cec_fh *cec_follower;
	काष्ठा cec_fh *cec_initiator;
	bool passthrough;
	काष्ठा cec_log_addrs log_addrs;
	काष्ठा cec_connector_info conn_info;

	u32 tx_समयouts;

#अगर_घोषित CONFIG_CEC_NOTIFIER
	काष्ठा cec_notअगरier *notअगरier;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CEC_PIN
	काष्ठा cec_pin *pin;
#पूर्ण_अगर

	काष्ठा dentry *cec_dir;

	u32 sequence;

	अक्षर input_phys[32];
पूर्ण;

अटल अंतरभूत व्योम *cec_get_drvdata(स्थिर काष्ठा cec_adapter *adap)
अणु
	वापस adap->priv;
पूर्ण

अटल अंतरभूत bool cec_has_log_addr(स्थिर काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	वापस adap->log_addrs.log_addr_mask & (1 << log_addr);
पूर्ण

अटल अंतरभूत bool cec_is_sink(स्थिर काष्ठा cec_adapter *adap)
अणु
	वापस adap->phys_addr == 0;
पूर्ण

/**
 * cec_is_रेजिस्टरed() - is the CEC adapter रेजिस्टरed?
 *
 * @adap:	the CEC adapter, may be शून्य.
 *
 * Return: true अगर the adapter is रेजिस्टरed, false otherwise.
 */
अटल अंतरभूत bool cec_is_रेजिस्टरed(स्थिर काष्ठा cec_adapter *adap)
अणु
	वापस adap && adap->devnode.रेजिस्टरed;
पूर्ण

#घोषणा cec_phys_addr_exp(pa) \
	((pa) >> 12), ((pa) >> 8) & 0xf, ((pa) >> 4) & 0xf, (pa) & 0xf

काष्ठा edid;
काष्ठा drm_connector;

#अगर IS_REACHABLE(CONFIG_CEC_CORE)
काष्ठा cec_adapter *cec_allocate_adapter(स्थिर काष्ठा cec_adap_ops *ops,
		व्योम *priv, स्थिर अक्षर *name, u32 caps, u8 available_las);
पूर्णांक cec_रेजिस्टर_adapter(काष्ठा cec_adapter *adap, काष्ठा device *parent);
व्योम cec_unरेजिस्टर_adapter(काष्ठा cec_adapter *adap);
व्योम cec_delete_adapter(काष्ठा cec_adapter *adap);

पूर्णांक cec_s_log_addrs(काष्ठा cec_adapter *adap, काष्ठा cec_log_addrs *log_addrs,
		    bool block);
व्योम cec_s_phys_addr(काष्ठा cec_adapter *adap, u16 phys_addr,
		     bool block);
व्योम cec_s_phys_addr_from_edid(काष्ठा cec_adapter *adap,
			       स्थिर काष्ठा edid *edid);
व्योम cec_s_conn_info(काष्ठा cec_adapter *adap,
		     स्थिर काष्ठा cec_connector_info *conn_info);
पूर्णांक cec_transmit_msg(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg,
		     bool block);

/* Called by the adapter */
व्योम cec_transmit_करोne_ts(काष्ठा cec_adapter *adap, u8 status,
			  u8 arb_lost_cnt, u8 nack_cnt, u8 low_drive_cnt,
			  u8 error_cnt, kसमय_प्रकार ts);

अटल अंतरभूत व्योम cec_transmit_करोne(काष्ठा cec_adapter *adap, u8 status,
				     u8 arb_lost_cnt, u8 nack_cnt,
				     u8 low_drive_cnt, u8 error_cnt)
अणु
	cec_transmit_करोne_ts(adap, status, arb_lost_cnt, nack_cnt,
			     low_drive_cnt, error_cnt, kसमय_get());
पूर्ण
/*
 * Simplअगरied version of cec_transmit_करोne क्रम hardware that करोesn't retry
 * failed transmits. So this is always just one attempt in which हाल
 * the status is sufficient.
 */
व्योम cec_transmit_attempt_करोne_ts(काष्ठा cec_adapter *adap,
				  u8 status, kसमय_प्रकार ts);

अटल अंतरभूत व्योम cec_transmit_attempt_करोne(काष्ठा cec_adapter *adap,
					     u8 status)
अणु
	cec_transmit_attempt_करोne_ts(adap, status, kसमय_get());
पूर्ण

व्योम cec_received_msg_ts(काष्ठा cec_adapter *adap,
			 काष्ठा cec_msg *msg, kसमय_प्रकार ts);

अटल अंतरभूत व्योम cec_received_msg(काष्ठा cec_adapter *adap,
				    काष्ठा cec_msg *msg)
अणु
	cec_received_msg_ts(adap, msg, kसमय_get());
पूर्ण

/**
 * cec_queue_pin_cec_event() - queue a CEC pin event with a given बारtamp.
 *
 * @adap:	poपूर्णांकer to the cec adapter
 * @is_high:	when true the CEC pin is high, otherwise it is low
 * @dropped_events: when true some events were dropped
 * @ts:		the बारtamp क्रम this event
 *
 */
व्योम cec_queue_pin_cec_event(काष्ठा cec_adapter *adap, bool is_high,
			     bool dropped_events, kसमय_प्रकार ts);

/**
 * cec_queue_pin_hpd_event() - queue a pin event with a given बारtamp.
 *
 * @adap:	poपूर्णांकer to the cec adapter
 * @is_high:	when true the HPD pin is high, otherwise it is low
 * @ts:		the बारtamp क्रम this event
 *
 */
व्योम cec_queue_pin_hpd_event(काष्ठा cec_adapter *adap, bool is_high, kसमय_प्रकार ts);

/**
 * cec_queue_pin_5v_event() - queue a pin event with a given बारtamp.
 *
 * @adap:	poपूर्णांकer to the cec adapter
 * @is_high:	when true the 5V pin is high, otherwise it is low
 * @ts:		the बारtamp क्रम this event
 *
 */
व्योम cec_queue_pin_5v_event(काष्ठा cec_adapter *adap, bool is_high, kसमय_प्रकार ts);

/**
 * cec_get_edid_phys_addr() - find and वापस the physical address
 *
 * @edid:	poपूर्णांकer to the EDID data
 * @size:	size in bytes of the EDID data
 * @offset:	If not %शून्य then the location of the physical address
 *		bytes in the EDID will be वापसed here. This is set to 0
 *		अगर there is no physical address found.
 *
 * Return: the physical address or CEC_PHYS_ADDR_INVALID अगर there is none.
 */
u16 cec_get_edid_phys_addr(स्थिर u8 *edid, अचिन्हित पूर्णांक size,
			   अचिन्हित पूर्णांक *offset);

व्योम cec_fill_conn_info_from_drm(काष्ठा cec_connector_info *conn_info,
				 स्थिर काष्ठा drm_connector *connector);

#अन्यथा

अटल अंतरभूत पूर्णांक cec_रेजिस्टर_adapter(काष्ठा cec_adapter *adap,
				       काष्ठा device *parent)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cec_unरेजिस्टर_adapter(काष्ठा cec_adapter *adap)
अणु
पूर्ण

अटल अंतरभूत व्योम cec_delete_adapter(काष्ठा cec_adapter *adap)
अणु
पूर्ण

अटल अंतरभूत व्योम cec_s_phys_addr(काष्ठा cec_adapter *adap, u16 phys_addr,
				   bool block)
अणु
पूर्ण

अटल अंतरभूत व्योम cec_s_phys_addr_from_edid(काष्ठा cec_adapter *adap,
					     स्थिर काष्ठा edid *edid)
अणु
पूर्ण

अटल अंतरभूत u16 cec_get_edid_phys_addr(स्थिर u8 *edid, अचिन्हित पूर्णांक size,
					 अचिन्हित पूर्णांक *offset)
अणु
	अगर (offset)
		*offset = 0;
	वापस CEC_PHYS_ADDR_INVALID;
पूर्ण

अटल अंतरभूत व्योम cec_s_conn_info(काष्ठा cec_adapter *adap,
				   स्थिर काष्ठा cec_connector_info *conn_info)
अणु
पूर्ण

अटल अंतरभूत व्योम
cec_fill_conn_info_from_drm(काष्ठा cec_connector_info *conn_info,
			    स्थिर काष्ठा drm_connector *connector)
अणु
	स_रखो(conn_info, 0, माप(*conn_info));
पूर्ण

#पूर्ण_अगर

/**
 * cec_phys_addr_invalidate() - set the physical address to INVALID
 *
 * @adap:	the CEC adapter
 *
 * This is a simple helper function to invalidate the physical
 * address.
 */
अटल अंतरभूत व्योम cec_phys_addr_invalidate(काष्ठा cec_adapter *adap)
अणु
	cec_s_phys_addr(adap, CEC_PHYS_ADDR_INVALID, false);
पूर्ण

/**
 * cec_get_edid_spa_location() - find location of the Source Physical Address
 *
 * @edid: the EDID
 * @size: the size of the EDID
 *
 * This EDID is expected to be a CEA-861 compliant, which means that there are
 * at least two blocks and one or more of the extensions blocks are CEA-861
 * blocks.
 *
 * The वापसed location is guaranteed to be <= size-2.
 *
 * This is an अंतरभूत function since it is used by both CEC and V4L2.
 * Ideally this would go in a module shared by both, but it is overसमाप्त to करो
 * that क्रम just a single function.
 */
अटल अंतरभूत अचिन्हित पूर्णांक cec_get_edid_spa_location(स्थिर u8 *edid,
						     अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक blocks = size / 128;
	अचिन्हित पूर्णांक block;
	u8 d;

	/* Sanity check: at least 2 blocks and a multiple of the block size */
	अगर (blocks < 2 || size % 128)
		वापस 0;

	/*
	 * If there are fewer extension blocks than the size, then update
	 * 'blocks'. It is allowed to have more extension blocks than the size,
	 * since some hardware can only पढ़ो e.g. 256 bytes of the EDID, even
	 * though more blocks are present. The first CEA-861 extension block
	 * should normally be in block 1 anyway.
	 */
	अगर (edid[0x7e] + 1 < blocks)
		blocks = edid[0x7e] + 1;

	क्रम (block = 1; block < blocks; block++) अणु
		अचिन्हित पूर्णांक offset = block * 128;

		/* Skip any non-CEA-861 extension blocks */
		अगर (edid[offset] != 0x02 || edid[offset + 1] != 0x03)
			जारी;

		/* search Venकरोr Specअगरic Data Block (tag 3) */
		d = edid[offset + 2] & 0x7f;
		/* Check अगर there are Data Blocks */
		अगर (d <= 4)
			जारी;
		अगर (d > 4) अणु
			अचिन्हित पूर्णांक i = offset + 4;
			अचिन्हित पूर्णांक end = offset + d;

			/* Note: 'end' is always < 'size' */
			करो अणु
				u8 tag = edid[i] >> 5;
				u8 len = edid[i] & 0x1f;

				अगर (tag == 3 && len >= 5 && i + len <= end &&
				    edid[i + 1] == 0x03 &&
				    edid[i + 2] == 0x0c &&
				    edid[i + 3] == 0x00)
					वापस i + 4;
				i += len + 1;
			पूर्ण जबतक (i < end);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _MEDIA_CEC_H */
