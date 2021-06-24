<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/* Copyright(c) 2015-17 Intel Corporation. */

#अगर_अघोषित __SDW_BUS_H
#घोषणा __SDW_BUS_H

#घोषणा DEFAULT_BANK_SWITCH_TIMEOUT 3000
#घोषणा DEFAULT_PROBE_TIMEOUT       2000

u64 sdw_dmi_override_adr(काष्ठा sdw_bus *bus, u64 addr);

#अगर IS_ENABLED(CONFIG_ACPI)
पूर्णांक sdw_acpi_find_slaves(काष्ठा sdw_bus *bus);
#अन्यथा
अटल अंतरभूत पूर्णांक sdw_acpi_find_slaves(काष्ठा sdw_bus *bus)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

पूर्णांक sdw_of_find_slaves(काष्ठा sdw_bus *bus);
व्योम sdw_extract_slave_id(काष्ठा sdw_bus *bus,
			  u64 addr, काष्ठा sdw_slave_id *id);
पूर्णांक sdw_slave_add(काष्ठा sdw_bus *bus, काष्ठा sdw_slave_id *id,
		  काष्ठा fwnode_handle *fwnode);
पूर्णांक sdw_master_device_add(काष्ठा sdw_bus *bus, काष्ठा device *parent,
			  काष्ठा fwnode_handle *fwnode);
पूर्णांक sdw_master_device_del(काष्ठा sdw_bus *bus);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम sdw_bus_debugfs_init(काष्ठा sdw_bus *bus);
व्योम sdw_bus_debugfs_निकास(काष्ठा sdw_bus *bus);
व्योम sdw_slave_debugfs_init(काष्ठा sdw_slave *slave);
व्योम sdw_slave_debugfs_निकास(काष्ठा sdw_slave *slave);
व्योम sdw_debugfs_init(व्योम);
व्योम sdw_debugfs_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम sdw_bus_debugfs_init(काष्ठा sdw_bus *bus) अणुपूर्ण
अटल अंतरभूत व्योम sdw_bus_debugfs_निकास(काष्ठा sdw_bus *bus) अणुपूर्ण
अटल अंतरभूत व्योम sdw_slave_debugfs_init(काष्ठा sdw_slave *slave) अणुपूर्ण
अटल अंतरभूत व्योम sdw_slave_debugfs_निकास(काष्ठा sdw_slave *slave) अणुपूर्ण
अटल अंतरभूत व्योम sdw_debugfs_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम sdw_debugfs_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर

क्रमागत अणु
	SDW_MSG_FLAG_READ = 0,
	SDW_MSG_FLAG_WRITE,
पूर्ण;

/**
 * काष्ठा sdw_msg - Message काष्ठाure
 * @addr: Register address accessed in the Slave
 * @len: number of messages
 * @dev_num: Slave device number
 * @addr_page1: SCP address page 1 Slave रेजिस्टर
 * @addr_page2: SCP address page 2 Slave रेजिस्टर
 * @flags: transfer flags, indicate अगर xfer is पढ़ो or ग_लिखो
 * @buf: message data buffer
 * @ssp_sync: Send message at SSP (Stream Synchronization Poपूर्णांक)
 * @page: address requires paging
 */
काष्ठा sdw_msg अणु
	u16 addr;
	u16 len;
	u8 dev_num;
	u8 addr_page1;
	u8 addr_page2;
	u8 flags;
	u8 *buf;
	bool ssp_sync;
	bool page;
पूर्ण;

#घोषणा SDW_DOUBLE_RATE_FACTOR		2
#घोषणा SDW_STRM_RATE_GROUPING		1

बाह्य पूर्णांक sdw_rows[SDW_FRAME_ROWS];
बाह्य पूर्णांक sdw_cols[SDW_FRAME_COLS];

पूर्णांक sdw_find_row_index(पूर्णांक row);
पूर्णांक sdw_find_col_index(पूर्णांक col);

/**
 * sdw_port_runसमय: Runसमय port parameters क्रम Master or Slave
 *
 * @num: Port number. For audio streams, valid port number ranges from
 * [1,14]
 * @ch_mask: Channel mask
 * @transport_params: Transport parameters
 * @port_params: Port parameters
 * @port_node: List node क्रम Master or Slave port_list
 *
 * SoundWire spec has no mention of ports क्रम Master पूर्णांकerface but the
 * concept is logically extended.
 */
काष्ठा sdw_port_runसमय अणु
	पूर्णांक num;
	पूर्णांक ch_mask;
	काष्ठा sdw_transport_params transport_params;
	काष्ठा sdw_port_params port_params;
	काष्ठा list_head port_node;
पूर्ण;

/**
 * sdw_slave_runसमय: Runसमय Stream parameters क्रम Slave
 *
 * @slave: Slave handle
 * @direction: Data direction क्रम Slave
 * @ch_count: Number of channels handled by the Slave क्रम
 * this stream
 * @m_rt_node: sdw_master_runसमय list node
 * @port_list: List of Slave Ports configured क्रम this stream
 */
काष्ठा sdw_slave_runसमय अणु
	काष्ठा sdw_slave *slave;
	क्रमागत sdw_data_direction direction;
	अचिन्हित पूर्णांक ch_count;
	काष्ठा list_head m_rt_node;
	काष्ठा list_head port_list;
पूर्ण;

/**
 * sdw_master_runसमय: Runसमय stream parameters क्रम Master
 *
 * @bus: Bus handle
 * @stream: Stream runसमय handle
 * @direction: Data direction क्रम Master
 * @ch_count: Number of channels handled by the Master क्रम
 * this stream, can be zero.
 * @slave_rt_list: Slave runसमय list
 * @port_list: List of Master Ports configured क्रम this stream, can be zero.
 * @stream_node: sdw_stream_runसमय master_list node
 * @bus_node: sdw_bus m_rt_list node
 */
काष्ठा sdw_master_runसमय अणु
	काष्ठा sdw_bus *bus;
	काष्ठा sdw_stream_runसमय *stream;
	क्रमागत sdw_data_direction direction;
	अचिन्हित पूर्णांक ch_count;
	काष्ठा list_head slave_rt_list;
	काष्ठा list_head port_list;
	काष्ठा list_head stream_node;
	काष्ठा list_head bus_node;
पूर्ण;

काष्ठा sdw_dpn_prop *sdw_get_slave_dpn_prop(काष्ठा sdw_slave *slave,
					    क्रमागत sdw_data_direction direction,
					    अचिन्हित पूर्णांक port_num);
पूर्णांक sdw_configure_dpn_पूर्णांकr(काष्ठा sdw_slave *slave, पूर्णांक port,
			   bool enable, पूर्णांक mask);

पूर्णांक sdw_transfer(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg);
पूर्णांक sdw_transfer_defer(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg,
		       काष्ठा sdw_defer *defer);

#घोषणा SDW_READ_INTR_CLEAR_RETRY	10

पूर्णांक sdw_fill_msg(काष्ठा sdw_msg *msg, काष्ठा sdw_slave *slave,
		 u32 addr, माप_प्रकार count, u16 dev_num, u8 flags, u8 *buf);

/* Retrieve and वापस channel count from channel mask */
अटल अंतरभूत पूर्णांक sdw_ch_mask_to_ch(पूर्णांक ch_mask)
अणु
	पूर्णांक c = 0;

	क्रम (c = 0; ch_mask; ch_mask >>= 1)
		c += ch_mask & 1;

	वापस c;
पूर्ण

/* Fill transport parameter data काष्ठाure */
अटल अंतरभूत व्योम sdw_fill_xport_params(काष्ठा sdw_transport_params *params,
					 पूर्णांक port_num, bool grp_ctrl_valid,
					 पूर्णांक grp_ctrl, पूर्णांक sample_पूर्णांक,
					 पूर्णांक off1, पूर्णांक off2,
					 पूर्णांक hstart, पूर्णांक hstop,
					 पूर्णांक pack_mode, पूर्णांक lane_ctrl)
अणु
	params->port_num = port_num;
	params->blk_grp_ctrl_valid = grp_ctrl_valid;
	params->blk_grp_ctrl = grp_ctrl;
	params->sample_पूर्णांकerval = sample_पूर्णांक;
	params->offset1 = off1;
	params->offset2 = off2;
	params->hstart = hstart;
	params->hstop = hstop;
	params->blk_pkg_mode = pack_mode;
	params->lane_ctrl = lane_ctrl;
पूर्ण

/* Fill port parameter data काष्ठाure */
अटल अंतरभूत व्योम sdw_fill_port_params(काष्ठा sdw_port_params *params,
					पूर्णांक port_num, पूर्णांक bps,
					पूर्णांक flow_mode, पूर्णांक data_mode)
अणु
	params->num = port_num;
	params->bps = bps;
	params->flow_mode = flow_mode;
	params->data_mode = data_mode;
पूर्ण

/* Read-Modअगरy-Write Slave रेजिस्टर */
अटल अंतरभूत पूर्णांक sdw_update(काष्ठा sdw_slave *slave, u32 addr, u8 mask, u8 val)
अणु
	पूर्णांक पंचांगp;

	पंचांगp = sdw_पढ़ो(slave, addr);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	पंचांगp = (पंचांगp & ~mask) | val;
	वापस sdw_ग_लिखो(slave, addr, पंचांगp);
पूर्ण

/* broadcast पढ़ो/ग_लिखो क्रम tests */
पूर्णांक sdw_bपढ़ो_no_pm_unlocked(काष्ठा sdw_bus *bus, u16 dev_num, u32 addr);
पूर्णांक sdw_bग_लिखो_no_pm_unlocked(काष्ठा sdw_bus *bus, u16 dev_num, u32 addr, u8 value);

/*
 * At the moment we only track Master-initiated hw_reset.
 * Additional fields can be added as needed
 */
#घोषणा SDW_UNATTACH_REQUEST_MASTER_RESET	BIT(0)

व्योम sdw_clear_slave_status(काष्ठा sdw_bus *bus, u32 request);
पूर्णांक sdw_slave_modalias(स्थिर काष्ठा sdw_slave *slave, अक्षर *buf, माप_प्रकार size);

#पूर्ण_अगर /* __SDW_BUS_H */
