<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_main.h"
#समावेश "octeon_network.h"
#समावेश "cn66xx_regs.h"
#समावेश "cn66xx_device.h"
#समावेश "cn23xx_pf_device.h"
#समावेश "cn23xx_vf_device.h"

/** Default configuration
 *  क्रम CN66XX OCTEON Models.
 */
अटल काष्ठा octeon_config शेष_cn66xx_conf = अणु
	.card_type                              = LIO_210SV,
	.card_name                              = LIO_210SV_NAME,

	/** IQ attributes */
	.iq					= अणु
		.max_iqs			= CN6XXX_CFG_IO_QUEUES,
		.pending_list_size		=
			(CN6XXX_MAX_IQ_DESCRIPTORS * CN6XXX_CFG_IO_QUEUES),
		.instr_type			= OCTEON_64BYTE_INSTR,
		.db_min				= CN6XXX_DB_MIN,
		.db_समयout			= CN6XXX_DB_TIMEOUT,
	पूर्ण
	,

	/** OQ attributes */
	.oq					= अणु
		.max_oqs			= CN6XXX_CFG_IO_QUEUES,
		.refill_threshold		= CN6XXX_OQ_REFIL_THRESHOLD,
		.oq_पूर्णांकr_pkt			= CN6XXX_OQ_INTR_PKT,
		.oq_पूर्णांकr_समय			= CN6XXX_OQ_INTR_TIME,
		.pkts_per_पूर्णांकr			= CN6XXX_OQ_PKTSPER_INTR,
	पूर्ण
	,

	.num_nic_ports				= DEFAULT_NUM_NIC_PORTS_66XX,
	.num_def_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,
	.num_def_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,
	.def_rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

	/* For ethernet पूर्णांकerface 0:  Port cfg Attributes */
	.nic_अगर_cfg[0] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 0,
	पूर्ण,

	.nic_अगर_cfg[1] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 1,
	पूर्ण,

	/** Miscellaneous attributes */
	.misc					= अणु
		/* Host driver link query पूर्णांकerval */
		.oct_link_query_पूर्णांकerval	= 100,

		/* Octeon link query पूर्णांकerval */
		.host_link_query_पूर्णांकerval	= 500,

		.enable_sli_oq_bp		= 0,

		/* Control queue group */
		.ctrlq_grp			= 1,
	पूर्ण
	,
पूर्ण;

/** Default configuration
 *  क्रम CN68XX OCTEON Model.
 */

अटल काष्ठा octeon_config शेष_cn68xx_conf = अणु
	.card_type                              = LIO_410NV,
	.card_name                              = LIO_410NV_NAME,

	/** IQ attributes */
	.iq					= अणु
		.max_iqs			= CN6XXX_CFG_IO_QUEUES,
		.pending_list_size		=
			(CN6XXX_MAX_IQ_DESCRIPTORS * CN6XXX_CFG_IO_QUEUES),
		.instr_type			= OCTEON_64BYTE_INSTR,
		.db_min				= CN6XXX_DB_MIN,
		.db_समयout			= CN6XXX_DB_TIMEOUT,
	पूर्ण
	,

	/** OQ attributes */
	.oq					= अणु
		.max_oqs			= CN6XXX_CFG_IO_QUEUES,
		.refill_threshold		= CN6XXX_OQ_REFIL_THRESHOLD,
		.oq_पूर्णांकr_pkt			= CN6XXX_OQ_INTR_PKT,
		.oq_पूर्णांकr_समय			= CN6XXX_OQ_INTR_TIME,
		.pkts_per_पूर्णांकr			= CN6XXX_OQ_PKTSPER_INTR,
	पूर्ण
	,

	.num_nic_ports				= DEFAULT_NUM_NIC_PORTS_68XX,
	.num_def_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,
	.num_def_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,
	.def_rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

	.nic_अगर_cfg[0] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 0,
	पूर्ण,

	.nic_अगर_cfg[1] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 1,
	पूर्ण,

	.nic_अगर_cfg[2] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 2,
	पूर्ण,

	.nic_अगर_cfg[3] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 3,
	पूर्ण,

	/** Miscellaneous attributes */
	.misc					= अणु
		/* Host driver link query पूर्णांकerval */
		.oct_link_query_पूर्णांकerval	= 100,

		/* Octeon link query पूर्णांकerval */
		.host_link_query_पूर्णांकerval	= 500,

		.enable_sli_oq_bp		= 0,

		/* Control queue group */
		.ctrlq_grp			= 1,
	पूर्ण
	,
पूर्ण;

/** Default configuration
 *  क्रम CN68XX OCTEON Model.
 */
अटल काष्ठा octeon_config शेष_cn68xx_210nv_conf = अणु
	.card_type                              = LIO_210NV,
	.card_name                              = LIO_210NV_NAME,

	/** IQ attributes */

	.iq					= अणु
		.max_iqs			= CN6XXX_CFG_IO_QUEUES,
		.pending_list_size		=
			(CN6XXX_MAX_IQ_DESCRIPTORS * CN6XXX_CFG_IO_QUEUES),
		.instr_type			= OCTEON_64BYTE_INSTR,
		.db_min				= CN6XXX_DB_MIN,
		.db_समयout			= CN6XXX_DB_TIMEOUT,
	पूर्ण
	,

	/** OQ attributes */
	.oq					= अणु
		.max_oqs			= CN6XXX_CFG_IO_QUEUES,
		.refill_threshold		= CN6XXX_OQ_REFIL_THRESHOLD,
		.oq_पूर्णांकr_pkt			= CN6XXX_OQ_INTR_PKT,
		.oq_पूर्णांकr_समय			= CN6XXX_OQ_INTR_TIME,
		.pkts_per_पूर्णांकr			= CN6XXX_OQ_PKTSPER_INTR,
	पूर्ण
	,

	.num_nic_ports			= DEFAULT_NUM_NIC_PORTS_68XX_210NV,
	.num_def_rx_descs		= CN6XXX_MAX_OQ_DESCRIPTORS,
	.num_def_tx_descs		= CN6XXX_MAX_IQ_DESCRIPTORS,
	.def_rx_buf_size		= CN6XXX_OQ_BUF_SIZE,

	.nic_अगर_cfg[0] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 0,
	पूर्ण,

	.nic_अगर_cfg[1] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN6XXX_MAX_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 1,
	पूर्ण,

	/** Miscellaneous attributes */
	.misc					= अणु
		/* Host driver link query पूर्णांकerval */
		.oct_link_query_पूर्णांकerval	= 100,

		/* Octeon link query पूर्णांकerval */
		.host_link_query_पूर्णांकerval	= 500,

		.enable_sli_oq_bp		= 0,

		/* Control queue group */
		.ctrlq_grp			= 1,
	पूर्ण
	,
पूर्ण;

अटल काष्ठा octeon_config शेष_cn23xx_conf = अणु
	.card_type                              = LIO_23XX,
	.card_name                              = LIO_23XX_NAME,
	/** IQ attributes */
	.iq = अणु
		.max_iqs		= CN23XX_CFG_IO_QUEUES,
		.pending_list_size	= (CN23XX_DEFAULT_IQ_DESCRIPTORS *
					   CN23XX_CFG_IO_QUEUES),
		.instr_type		= OCTEON_64BYTE_INSTR,
		.db_min			= CN23XX_DB_MIN,
		.db_समयout		= CN23XX_DB_TIMEOUT,
		.iq_पूर्णांकr_pkt		= CN23XX_DEF_IQ_INTR_THRESHOLD,
	पूर्ण,

	/** OQ attributes */
	.oq = अणु
		.max_oqs		= CN23XX_CFG_IO_QUEUES,
		.pkts_per_पूर्णांकr	= CN23XX_OQ_PKTSPER_INTR,
		.refill_threshold	= CN23XX_OQ_REFIL_THRESHOLD,
		.oq_पूर्णांकr_pkt	= CN23XX_OQ_INTR_PKT,
		.oq_पूर्णांकr_समय	= CN23XX_OQ_INTR_TIME,
	पूर्ण,

	.num_nic_ports				= DEFAULT_NUM_NIC_PORTS_23XX,
	.num_def_rx_descs			= CN23XX_DEFAULT_OQ_DESCRIPTORS,
	.num_def_tx_descs			= CN23XX_DEFAULT_IQ_DESCRIPTORS,
	.def_rx_buf_size			= CN23XX_OQ_BUF_SIZE,

	/* For ethernet पूर्णांकerface 0:  Port cfg Attributes */
	.nic_अगर_cfg[0] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN23XX_DEFAULT_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN23XX_DEFAULT_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN23XX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 0,
	पूर्ण,

	.nic_अगर_cfg[1] = अणु
		/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
		.max_txqs			= MAX_TXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PER_INTF,

		/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
		.max_rxqs			= MAX_RXQS_PER_INTF,

		/* Actual configured value. Range could be: 1...max_rxqs */
		.num_rxqs			= DEF_RXQS_PER_INTF,

		/* Num of desc क्रम rx rings */
		.num_rx_descs			= CN23XX_DEFAULT_OQ_DESCRIPTORS,

		/* Num of desc क्रम tx rings */
		.num_tx_descs			= CN23XX_DEFAULT_IQ_DESCRIPTORS,

		/* SKB size, We need not change buf size even क्रम Jumbo frames.
		 * Octeon can send jumbo frames in 4 consecutive descriptors,
		 */
		.rx_buf_size			= CN23XX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_REQUESTED,

		.gmx_port_id			= 1,
	पूर्ण,

	.misc					= अणु
		/* Host driver link query पूर्णांकerval */
		.oct_link_query_पूर्णांकerval	= 100,

		/* Octeon link query पूर्णांकerval */
		.host_link_query_पूर्णांकerval	= 500,

		.enable_sli_oq_bp		= 0,

		/* Control queue group */
		.ctrlq_grp			= 1,
	पूर्ण
पूर्ण;

अटल काष्ठा octeon_config_ptr अणु
	u32 conf_type;
पूर्ण oct_conf_info[MAX_OCTEON_DEVICES] = अणु
	अणु
		OCTEON_CONFIG_TYPE_DEFAULT,
	पूर्ण, अणु
		OCTEON_CONFIG_TYPE_DEFAULT,
	पूर्ण, अणु
		OCTEON_CONFIG_TYPE_DEFAULT,
	पूर्ण, अणु
		OCTEON_CONFIG_TYPE_DEFAULT,
	पूर्ण,
पूर्ण;

अटल अक्षर oct_dev_state_str[OCT_DEV_STATES + 1][32] = अणु
	"BEGIN", "PCI-ENABLE-DONE", "PCI-MAP-DONE", "DISPATCH-INIT-DONE",
	"IQ-INIT-DONE", "SCBUFF-POOL-INIT-DONE", "RESPLIST-INIT-DONE",
	"DROQ-INIT-DONE", "MBOX-SETUP-DONE", "MSIX-ALLOC-VECTOR-DONE",
	"INTR-SET-DONE", "IO-QUEUES-INIT-DONE", "CONSOLE-INIT-DONE",
	"HOST-READY", "CORE-READY", "RUNNING", "IN-RESET",
	"INVALID"
पूर्ण;

अटल अक्षर oct_dev_app_str[CVM_DRV_APP_COUNT + 1][32] = अणु
	"BASE", "NIC", "UNKNOWN"पूर्ण;

अटल काष्ठा octeon_device *octeon_device[MAX_OCTEON_DEVICES];
अटल atomic_t adapter_refcounts[MAX_OCTEON_DEVICES];
अटल atomic_t adapter_fw_states[MAX_OCTEON_DEVICES];

अटल u32 octeon_device_count;
/* locks device array (i.e. octeon_device[]) */
अटल DEFINE_SPINLOCK(octeon_devices_lock);

अटल काष्ठा octeon_core_setup core_setup[MAX_OCTEON_DEVICES];

अटल व्योम oct_set_config_info(पूर्णांक oct_id, पूर्णांक conf_type)
अणु
	अगर (conf_type < 0 || conf_type > (NUM_OCTEON_CONFS - 1))
		conf_type = OCTEON_CONFIG_TYPE_DEFAULT;
	oct_conf_info[oct_id].conf_type = conf_type;
पूर्ण

व्योम octeon_init_device_list(पूर्णांक conf_type)
अणु
	पूर्णांक i;

	स_रखो(octeon_device, 0, (माप(व्योम *) * MAX_OCTEON_DEVICES));
	क्रम (i = 0; i <  MAX_OCTEON_DEVICES; i++)
		oct_set_config_info(i, conf_type);
पूर्ण

अटल व्योम *__retrieve_octeon_config_info(काष्ठा octeon_device *oct,
					   u16 card_type)
अणु
	u32 oct_id = oct->octeon_id;
	व्योम *ret = शून्य;

	चयन (oct_conf_info[oct_id].conf_type) अणु
	हाल OCTEON_CONFIG_TYPE_DEFAULT:
		अगर (oct->chip_id == OCTEON_CN66XX) अणु
			ret = &शेष_cn66xx_conf;
		पूर्ण अन्यथा अगर ((oct->chip_id == OCTEON_CN68XX) &&
			   (card_type == LIO_210NV)) अणु
			ret = &शेष_cn68xx_210nv_conf;
		पूर्ण अन्यथा अगर ((oct->chip_id == OCTEON_CN68XX) &&
			   (card_type == LIO_410NV)) अणु
			ret = &शेष_cn68xx_conf;
		पूर्ण अन्यथा अगर (oct->chip_id == OCTEON_CN23XX_PF_VID) अणु
			ret = &शेष_cn23xx_conf;
		पूर्ण अन्यथा अगर (oct->chip_id == OCTEON_CN23XX_VF_VID) अणु
			ret = &शेष_cn23xx_conf;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __verअगरy_octeon_config_info(काष्ठा octeon_device *oct, व्योम *conf)
अणु
	चयन (oct->chip_id) अणु
	हाल OCTEON_CN66XX:
	हाल OCTEON_CN68XX:
		वापस lio_validate_cn6xxx_config_info(oct, conf);
	हाल OCTEON_CN23XX_PF_VID:
	हाल OCTEON_CN23XX_VF_VID:
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

व्योम *oct_get_config_info(काष्ठा octeon_device *oct, u16 card_type)
अणु
	व्योम *conf = शून्य;

	conf = __retrieve_octeon_config_info(oct, card_type);
	अगर (!conf)
		वापस शून्य;

	अगर (__verअगरy_octeon_config_info(oct, conf)) अणु
		dev_err(&oct->pci_dev->dev, "Configuration verification failed\n");
		वापस शून्य;
	पूर्ण

	वापस conf;
पूर्ण

अक्षर *lio_get_state_string(atomic_t *state_ptr)
अणु
	s32 istate = (s32)atomic_पढ़ो(state_ptr);

	अगर (istate > OCT_DEV_STATES || istate < 0)
		वापस oct_dev_state_str[OCT_DEV_STATE_INVALID];
	वापस oct_dev_state_str[istate];
पूर्ण

अटल अक्षर *get_oct_app_string(u32 app_mode)
अणु
	अगर (app_mode <= CVM_DRV_APP_END)
		वापस oct_dev_app_str[app_mode - CVM_DRV_APP_START];
	वापस oct_dev_app_str[CVM_DRV_INVALID_APP - CVM_DRV_APP_START];
पूर्ण

व्योम octeon_मुक्त_device_mem(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct); i++) अणु
		अगर (oct->io_qmask.oq & BIT_ULL(i))
			vमुक्त(oct->droq[i]);
	पूर्ण

	क्रम (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) अणु
		अगर (oct->io_qmask.iq & BIT_ULL(i))
			vमुक्त(oct->instr_queue[i]);
	पूर्ण

	i = oct->octeon_id;
	vमुक्त(oct);

	octeon_device[i] = शून्य;
	octeon_device_count--;
पूर्ण

अटल काष्ठा octeon_device *octeon_allocate_device_mem(u32 pci_id,
							u32 priv_size)
अणु
	काष्ठा octeon_device *oct;
	u8 *buf = शून्य;
	u32 octdevsize = 0, configsize = 0, size;

	चयन (pci_id) अणु
	हाल OCTEON_CN68XX:
	हाल OCTEON_CN66XX:
		configsize = माप(काष्ठा octeon_cn6xxx);
		अवरोध;

	हाल OCTEON_CN23XX_PF_VID:
		configsize = माप(काष्ठा octeon_cn23xx_pf);
		अवरोध;
	हाल OCTEON_CN23XX_VF_VID:
		configsize = माप(काष्ठा octeon_cn23xx_vf);
		अवरोध;
	शेष:
		pr_err("%s: Unknown PCI Device: 0x%x\n",
		       __func__,
		       pci_id);
		वापस शून्य;
	पूर्ण

	अगर (configsize & 0x7)
		configsize += (8 - (configsize & 0x7));

	octdevsize = माप(काष्ठा octeon_device);
	अगर (octdevsize & 0x7)
		octdevsize += (8 - (octdevsize & 0x7));

	अगर (priv_size & 0x7)
		priv_size += (8 - (priv_size & 0x7));

	size = octdevsize + priv_size + configsize +
		(माप(काष्ठा octeon_dispatch) * DISPATCH_LIST_SIZE);

	buf = vzalloc(size);
	अगर (!buf)
		वापस शून्य;

	oct = (काष्ठा octeon_device *)buf;
	oct->priv = (व्योम *)(buf + octdevsize);
	oct->chip = (व्योम *)(buf + octdevsize + priv_size);
	oct->dispatch.dlist = (काष्ठा octeon_dispatch *)
		(buf + octdevsize + priv_size + configsize);

	वापस oct;
पूर्ण

काष्ठा octeon_device *octeon_allocate_device(u32 pci_id,
					     u32 priv_size)
अणु
	u32 oct_idx = 0;
	काष्ठा octeon_device *oct = शून्य;

	spin_lock(&octeon_devices_lock);

	क्रम (oct_idx = 0; oct_idx < MAX_OCTEON_DEVICES; oct_idx++)
		अगर (!octeon_device[oct_idx])
			अवरोध;

	अगर (oct_idx < MAX_OCTEON_DEVICES) अणु
		oct = octeon_allocate_device_mem(pci_id, priv_size);
		अगर (oct) अणु
			octeon_device_count++;
			octeon_device[oct_idx] = oct;
		पूर्ण
	पूर्ण

	spin_unlock(&octeon_devices_lock);
	अगर (!oct)
		वापस शून्य;

	spin_lock_init(&oct->pci_win_lock);
	spin_lock_init(&oct->mem_access_lock);

	oct->octeon_id = oct_idx;
	snम_लिखो(oct->device_name, माप(oct->device_name),
		 "LiquidIO%d", (oct->octeon_id));

	वापस oct;
पूर्ण

/** Register a device's bus location at initialization समय.
 *  @param octeon_dev - poपूर्णांकer to the octeon device काष्ठाure.
 *  @param bus        - PCIe bus #
 *  @param dev        - PCIe device #
 *  @param func       - PCIe function #
 *  @param is_pf      - TRUE क्रम PF, FALSE क्रम VF
 *  @वापस reference count of device's adapter
 */
पूर्णांक octeon_रेजिस्टर_device(काष्ठा octeon_device *oct,
			   पूर्णांक bus, पूर्णांक dev, पूर्णांक func, पूर्णांक is_pf)
अणु
	पूर्णांक idx, refcount;

	oct->loc.bus = bus;
	oct->loc.dev = dev;
	oct->loc.func = func;

	oct->adapter_refcount = &adapter_refcounts[oct->octeon_id];
	atomic_set(oct->adapter_refcount, 0);

	/* Like the reference count, the f/w state is shared 'per-adapter' */
	oct->adapter_fw_state = &adapter_fw_states[oct->octeon_id];
	atomic_set(oct->adapter_fw_state, FW_NEEDS_TO_BE_LOADED);

	spin_lock(&octeon_devices_lock);
	क्रम (idx = (पूर्णांक)oct->octeon_id - 1; idx >= 0; idx--) अणु
		अगर (!octeon_device[idx]) अणु
			dev_err(&oct->pci_dev->dev,
				"%s: Internal driver error, missing dev",
				__func__);
			spin_unlock(&octeon_devices_lock);
			atomic_inc(oct->adapter_refcount);
			वापस 1; /* here, refcount is guaranteed to be 1 */
		पूर्ण
		/* If another device is at same bus/dev, use its refcounter
		 * (and f/w state variable).
		 */
		अगर ((octeon_device[idx]->loc.bus == bus) &&
		    (octeon_device[idx]->loc.dev == dev)) अणु
			oct->adapter_refcount =
				octeon_device[idx]->adapter_refcount;
			oct->adapter_fw_state =
				octeon_device[idx]->adapter_fw_state;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&octeon_devices_lock);

	atomic_inc(oct->adapter_refcount);
	refcount = atomic_पढ़ो(oct->adapter_refcount);

	dev_dbg(&oct->pci_dev->dev, "%s: %02x:%02x:%d refcount %u", __func__,
		oct->loc.bus, oct->loc.dev, oct->loc.func, refcount);

	वापस refcount;
पूर्ण

/** Deरेजिस्टर a device at de-initialization समय.
 *  @param octeon_dev - poपूर्णांकer to the octeon device काष्ठाure.
 *  @वापस reference count of device's adapter
 */
पूर्णांक octeon_deरेजिस्टर_device(काष्ठा octeon_device *oct)
अणु
	पूर्णांक refcount;

	atomic_dec(oct->adapter_refcount);
	refcount = atomic_पढ़ो(oct->adapter_refcount);

	dev_dbg(&oct->pci_dev->dev, "%s: %04d:%02d:%d refcount %u", __func__,
		oct->loc.bus, oct->loc.dev, oct->loc.func, refcount);

	वापस refcount;
पूर्ण

पूर्णांक
octeon_allocate_ioq_vector(काष्ठा octeon_device *oct, u32 num_ioqs)
अणु
	काष्ठा octeon_ioq_vector *ioq_vector;
	पूर्णांक cpu_num;
	पूर्णांक size;
	पूर्णांक i;

	size = माप(काष्ठा octeon_ioq_vector) * num_ioqs;

	oct->ioq_vector = vzalloc(size);
	अगर (!oct->ioq_vector)
		वापस -1;
	क्रम (i = 0; i < num_ioqs; i++) अणु
		ioq_vector		= &oct->ioq_vector[i];
		ioq_vector->oct_dev	= oct;
		ioq_vector->iq_index	= i;
		ioq_vector->droq_index	= i;
		ioq_vector->mbox	= oct->mbox[i];

		cpu_num = i % num_online_cpus();
		cpumask_set_cpu(cpu_num, &ioq_vector->affinity_mask);

		अगर (oct->chip_id == OCTEON_CN23XX_PF_VID)
			ioq_vector->ioq_num	= i + oct->sriov_info.pf_srn;
		अन्यथा
			ioq_vector->ioq_num	= i;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
octeon_मुक्त_ioq_vector(काष्ठा octeon_device *oct)
अणु
	vमुक्त(oct->ioq_vector);
पूर्ण

/* this function is only क्रम setting up the first queue */
पूर्णांक octeon_setup_instr_queues(काष्ठा octeon_device *oct)
अणु
	u32 num_descs = 0;
	u32 iq_no = 0;
	जोड़ oct_txpciq txpciq;
	पूर्णांक numa_node = dev_to_node(&oct->pci_dev->dev);

	अगर (OCTEON_CN6XXX(oct))
		num_descs =
			CFG_GET_NUM_DEF_TX_DESCS(CHIP_CONF(oct, cn6xxx));
	अन्यथा अगर (OCTEON_CN23XX_PF(oct))
		num_descs = CFG_GET_NUM_DEF_TX_DESCS(CHIP_CONF(oct, cn23xx_pf));
	अन्यथा अगर (OCTEON_CN23XX_VF(oct))
		num_descs = CFG_GET_NUM_DEF_TX_DESCS(CHIP_CONF(oct, cn23xx_vf));

	oct->num_iqs = 0;

	oct->instr_queue[0] = vzalloc_node(माप(*oct->instr_queue[0]),
				numa_node);
	अगर (!oct->instr_queue[0])
		oct->instr_queue[0] =
			vzalloc(माप(काष्ठा octeon_instr_queue));
	अगर (!oct->instr_queue[0])
		वापस 1;
	स_रखो(oct->instr_queue[0], 0, माप(काष्ठा octeon_instr_queue));
	oct->instr_queue[0]->q_index = 0;
	oct->instr_queue[0]->app_ctx = (व्योम *)(माप_प्रकार)0;
	oct->instr_queue[0]->अगरidx = 0;
	txpciq.u64 = 0;
	txpciq.s.q_no = iq_no;
	txpciq.s.pkind = oct->pfvf_hsword.pkind;
	txpciq.s.use_qpg = 0;
	txpciq.s.qpg = 0;
	अगर (octeon_init_instr_queue(oct, txpciq, num_descs)) अणु
		/* prevent memory leak */
		vमुक्त(oct->instr_queue[0]);
		oct->instr_queue[0] = शून्य;
		वापस 1;
	पूर्ण

	oct->num_iqs++;
	वापस 0;
पूर्ण

पूर्णांक octeon_setup_output_queues(काष्ठा octeon_device *oct)
अणु
	u32 num_descs = 0;
	u32 desc_size = 0;
	u32 oq_no = 0;
	पूर्णांक numa_node = dev_to_node(&oct->pci_dev->dev);

	अगर (OCTEON_CN6XXX(oct)) अणु
		num_descs =
			CFG_GET_NUM_DEF_RX_DESCS(CHIP_CONF(oct, cn6xxx));
		desc_size =
			CFG_GET_DEF_RX_BUF_SIZE(CHIP_CONF(oct, cn6xxx));
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_PF(oct)) अणु
		num_descs = CFG_GET_NUM_DEF_RX_DESCS(CHIP_CONF(oct, cn23xx_pf));
		desc_size = CFG_GET_DEF_RX_BUF_SIZE(CHIP_CONF(oct, cn23xx_pf));
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_VF(oct)) अणु
		num_descs = CFG_GET_NUM_DEF_RX_DESCS(CHIP_CONF(oct, cn23xx_vf));
		desc_size = CFG_GET_DEF_RX_BUF_SIZE(CHIP_CONF(oct, cn23xx_vf));
	पूर्ण
	oct->num_oqs = 0;
	oct->droq[0] = vzalloc_node(माप(*oct->droq[0]), numa_node);
	अगर (!oct->droq[0])
		oct->droq[0] = vzalloc(माप(*oct->droq[0]));
	अगर (!oct->droq[0])
		वापस 1;

	अगर (octeon_init_droq(oct, oq_no, num_descs, desc_size, शून्य)) अणु
		vमुक्त(oct->droq[oq_no]);
		oct->droq[oq_no] = शून्य;
		वापस 1;
	पूर्ण
	oct->num_oqs++;

	वापस 0;
पूर्ण

पूर्णांक octeon_set_io_queues_off(काष्ठा octeon_device *oct)
अणु
	पूर्णांक loop = BUSY_READING_REG_VF_LOOP_COUNT;

	अगर (OCTEON_CN6XXX(oct)) अणु
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_INSTR_ENB, 0);
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_OUT_ENB, 0);
	पूर्ण अन्यथा अगर (oct->chip_id == OCTEON_CN23XX_VF_VID) अणु
		u32 q_no;

		/* IOQs will alपढ़ोy be in reset.
		 * If RST bit is set, रुको क्रम quiet bit to be set.
		 * Once quiet bit is set, clear the RST bit.
		 */
		क्रम (q_no = 0; q_no < oct->sriov_info.rings_per_vf; q_no++) अणु
			u64 reg_val = octeon_पढ़ो_csr64(
				oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no));

			जबतक ((reg_val & CN23XX_PKT_INPUT_CTL_RST) &&
			       !(reg_val &  CN23XX_PKT_INPUT_CTL_QUIET) &&
			       loop) अणु
				reg_val = octeon_पढ़ो_csr64(
					oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
				loop--;
			पूर्ण
			अगर (!loop) अणु
				dev_err(&oct->pci_dev->dev,
					"clearing the reset reg failed or setting the quiet reg failed for qno: %u\n",
					q_no);
				वापस -1;
			पूर्ण

			reg_val = reg_val & ~CN23XX_PKT_INPUT_CTL_RST;
			octeon_ग_लिखो_csr64(oct,
					   CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
					   reg_val);

			reg_val = octeon_पढ़ो_csr64(
					oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
			अगर (reg_val & CN23XX_PKT_INPUT_CTL_RST) अणु
				dev_err(&oct->pci_dev->dev,
					"unable to reset qno %u\n", q_no);
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम octeon_set_droq_pkt_op(काष्ठा octeon_device *oct,
			    u32 q_no,
			    u32 enable)
अणु
	u32 reg_val = 0;

	/* Disable the i/p and o/p queues क्रम this Octeon. */
	अगर (OCTEON_CN6XXX(oct)) अणु
		reg_val = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_OUT_ENB);

		अगर (enable)
			reg_val = reg_val | (1 << q_no);
		अन्यथा
			reg_val = reg_val & (~(1 << q_no));

		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_OUT_ENB, reg_val);
	पूर्ण
पूर्ण

पूर्णांक octeon_init_dispatch_list(काष्ठा octeon_device *oct)
अणु
	u32 i;

	oct->dispatch.count = 0;

	क्रम (i = 0; i < DISPATCH_LIST_SIZE; i++) अणु
		oct->dispatch.dlist[i].opcode = 0;
		INIT_LIST_HEAD(&oct->dispatch.dlist[i].list);
	पूर्ण

	क्रम (i = 0; i <= REQTYPE_LAST; i++)
		octeon_रेजिस्टर_reqtype_मुक्त_fn(oct, i, शून्य);

	spin_lock_init(&oct->dispatch.lock);

	वापस 0;
पूर्ण

व्योम octeon_delete_dispatch_list(काष्ठा octeon_device *oct)
अणु
	u32 i;
	काष्ठा list_head मुक्तlist, *temp, *पंचांगp2;

	INIT_LIST_HEAD(&मुक्तlist);

	spin_lock_bh(&oct->dispatch.lock);

	क्रम (i = 0; i < DISPATCH_LIST_SIZE; i++) अणु
		काष्ठा list_head *dispatch;

		dispatch = &oct->dispatch.dlist[i].list;
		जबतक (dispatch->next != dispatch) अणु
			temp = dispatch->next;
			list_move_tail(temp, &मुक्तlist);
		पूर्ण

		oct->dispatch.dlist[i].opcode = 0;
	पूर्ण

	oct->dispatch.count = 0;

	spin_unlock_bh(&oct->dispatch.lock);

	list_क्रम_each_safe(temp, पंचांगp2, &मुक्तlist) अणु
		list_del(temp);
		kमुक्त(temp);
	पूर्ण
पूर्ण

octeon_dispatch_fn_t
octeon_get_dispatch(काष्ठा octeon_device *octeon_dev, u16 opcode,
		    u16 subcode)
अणु
	u32 idx;
	काष्ठा list_head *dispatch;
	octeon_dispatch_fn_t fn = शून्य;
	u16 combined_opcode = OPCODE_SUBCODE(opcode, subcode);

	idx = combined_opcode & OCTEON_OPCODE_MASK;

	spin_lock_bh(&octeon_dev->dispatch.lock);

	अगर (octeon_dev->dispatch.count == 0) अणु
		spin_unlock_bh(&octeon_dev->dispatch.lock);
		वापस शून्य;
	पूर्ण

	अगर (!(octeon_dev->dispatch.dlist[idx].opcode)) अणु
		spin_unlock_bh(&octeon_dev->dispatch.lock);
		वापस शून्य;
	पूर्ण

	अगर (octeon_dev->dispatch.dlist[idx].opcode == combined_opcode) अणु
		fn = octeon_dev->dispatch.dlist[idx].dispatch_fn;
	पूर्ण अन्यथा अणु
		list_क्रम_each(dispatch,
			      &octeon_dev->dispatch.dlist[idx].list) अणु
			अगर (((काष्ठा octeon_dispatch *)dispatch)->opcode ==
			    combined_opcode) अणु
				fn = ((काष्ठा octeon_dispatch *)
				      dispatch)->dispatch_fn;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&octeon_dev->dispatch.lock);
	वापस fn;
पूर्ण

/* octeon_रेजिस्टर_dispatch_fn
 * Parameters:
 *   octeon_id - id of the octeon device.
 *   opcode    - opcode क्रम which driver should call the रेजिस्टरed function
 *   subcode   - subcode क्रम which driver should call the रेजिस्टरed function
 *   fn        - The function to call when a packet with "opcode" arrives in
 *		  octeon output queues.
 *   fn_arg    - The argument to be passed when calling function "fn".
 * Description:
 *   Registers a function and its argument to be called when a packet
 *   arrives in Octeon output queues with "opcode".
 * Returns:
 *   Success: 0
 *   Failure: 1
 * Locks:
 *   No locks are held.
 */
पूर्णांक
octeon_रेजिस्टर_dispatch_fn(काष्ठा octeon_device *oct,
			    u16 opcode,
			    u16 subcode,
			    octeon_dispatch_fn_t fn, व्योम *fn_arg)
अणु
	u32 idx;
	octeon_dispatch_fn_t pfn;
	u16 combined_opcode = OPCODE_SUBCODE(opcode, subcode);

	idx = combined_opcode & OCTEON_OPCODE_MASK;

	spin_lock_bh(&oct->dispatch.lock);
	/* Add dispatch function to first level of lookup table */
	अगर (oct->dispatch.dlist[idx].opcode == 0) अणु
		oct->dispatch.dlist[idx].opcode = combined_opcode;
		oct->dispatch.dlist[idx].dispatch_fn = fn;
		oct->dispatch.dlist[idx].arg = fn_arg;
		oct->dispatch.count++;
		spin_unlock_bh(&oct->dispatch.lock);
		वापस 0;
	पूर्ण

	spin_unlock_bh(&oct->dispatch.lock);

	/* Check अगर there was a function alपढ़ोy रेजिस्टरed क्रम this
	 * opcode/subcode.
	 */
	pfn = octeon_get_dispatch(oct, opcode, subcode);
	अगर (!pfn) अणु
		काष्ठा octeon_dispatch *dispatch;

		dev_dbg(&oct->pci_dev->dev,
			"Adding opcode to dispatch list linked list\n");
		dispatch = kदो_स्मृति(माप(*dispatch), GFP_KERNEL);
		अगर (!dispatch)
			वापस 1;

		dispatch->opcode = combined_opcode;
		dispatch->dispatch_fn = fn;
		dispatch->arg = fn_arg;

		/* Add dispatch function to linked list of fn ptrs
		 * at the hashed index.
		 */
		spin_lock_bh(&oct->dispatch.lock);
		list_add(&dispatch->list, &oct->dispatch.dlist[idx].list);
		oct->dispatch.count++;
		spin_unlock_bh(&oct->dispatch.lock);

	पूर्ण अन्यथा अणु
		अगर (pfn == fn &&
		    octeon_get_dispatch_arg(oct, opcode, subcode) == fn_arg)
			वापस 0;

		dev_err(&oct->pci_dev->dev,
			"Found previously registered dispatch fn for opcode/subcode: %x/%x\n",
			opcode, subcode);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक octeon_core_drv_init(काष्ठा octeon_recv_info *recv_info, व्योम *buf)
अणु
	u32 i;
	अक्षर app_name[16];
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)buf;
	काष्ठा octeon_recv_pkt *recv_pkt = recv_info->recv_pkt;
	काष्ठा octeon_core_setup *cs = शून्य;
	u32 num_nic_ports = 0;

	अगर (OCTEON_CN6XXX(oct))
		num_nic_ports =
			CFG_GET_NUM_NIC_PORTS(CHIP_CONF(oct, cn6xxx));
	अन्यथा अगर (OCTEON_CN23XX_PF(oct))
		num_nic_ports =
			CFG_GET_NUM_NIC_PORTS(CHIP_CONF(oct, cn23xx_pf));

	अगर (atomic_पढ़ो(&oct->status) >= OCT_DEV_RUNNING) अणु
		dev_err(&oct->pci_dev->dev, "Received CORE OK when device state is 0x%x\n",
			atomic_पढ़ो(&oct->status));
		जाओ core_drv_init_err;
	पूर्ण

	म_नकलन(app_name,
		get_oct_app_string(
		(u32)recv_pkt->rh.r_core_drv_init.app_mode),
		माप(app_name) - 1);
	oct->app_mode = (u32)recv_pkt->rh.r_core_drv_init.app_mode;
	अगर (recv_pkt->rh.r_core_drv_init.app_mode == CVM_DRV_NIC_APP) अणु
		oct->fw_info.max_nic_ports =
			(u32)recv_pkt->rh.r_core_drv_init.max_nic_ports;
		oct->fw_info.num_gmx_ports =
			(u32)recv_pkt->rh.r_core_drv_init.num_gmx_ports;
	पूर्ण

	अगर (oct->fw_info.max_nic_ports < num_nic_ports) अणु
		dev_err(&oct->pci_dev->dev,
			"Config has more ports than firmware allows (%d > %d).\n",
			num_nic_ports, oct->fw_info.max_nic_ports);
		जाओ core_drv_init_err;
	पूर्ण
	oct->fw_info.app_cap_flags = recv_pkt->rh.r_core_drv_init.app_cap_flags;
	oct->fw_info.app_mode = (u32)recv_pkt->rh.r_core_drv_init.app_mode;
	oct->pfvf_hsword.app_mode = (u32)recv_pkt->rh.r_core_drv_init.app_mode;

	oct->pfvf_hsword.pkind = recv_pkt->rh.r_core_drv_init.pkind;

	क्रम (i = 0; i < oct->num_iqs; i++)
		oct->instr_queue[i]->txpciq.s.pkind = oct->pfvf_hsword.pkind;

	atomic_set(&oct->status, OCT_DEV_CORE_OK);

	cs = &core_setup[oct->octeon_id];

	अगर (recv_pkt->buffer_size[0] != (माप(*cs) + OCT_DROQ_INFO_SIZE)) अणु
		dev_dbg(&oct->pci_dev->dev, "Core setup bytes expected %u found %d\n",
			(u32)माप(*cs),
			recv_pkt->buffer_size[0]);
	पूर्ण

	स_नकल(cs, get_rbd(
	       recv_pkt->buffer_ptr[0]) + OCT_DROQ_INFO_SIZE, माप(*cs));

	म_नकलन(oct->boardinfo.name, cs->boardname, OCT_BOARD_NAME);
	म_नकलन(oct->boardinfo.serial_number, cs->board_serial_number,
		OCT_SERIAL_LEN);

	octeon_swap_8B_data((u64 *)cs, (माप(*cs) >> 3));

	oct->boardinfo.major = cs->board_rev_major;
	oct->boardinfo.minor = cs->board_rev_minor;

	dev_info(&oct->pci_dev->dev,
		 "Running %s (%llu Hz)\n",
		 app_name, CVM_CAST64(cs->corefreq));

core_drv_init_err:
	क्रम (i = 0; i < recv_pkt->buffer_count; i++)
		recv_buffer_मुक्त(recv_pkt->buffer_ptr[i]);
	octeon_मुक्त_recv_info(recv_info);
	वापस 0;
पूर्ण

पूर्णांक octeon_get_tx_qsize(काष्ठा octeon_device *oct, u32 q_no)

अणु
	अगर (oct && (q_no < MAX_OCTEON_INSTR_QUEUES(oct)) &&
	    (oct->io_qmask.iq & BIT_ULL(q_no)))
		वापस oct->instr_queue[q_no]->max_count;

	वापस -1;
पूर्ण

पूर्णांक octeon_get_rx_qsize(काष्ठा octeon_device *oct, u32 q_no)
अणु
	अगर (oct && (q_no < MAX_OCTEON_OUTPUT_QUEUES(oct)) &&
	    (oct->io_qmask.oq & BIT_ULL(q_no)))
		वापस oct->droq[q_no]->max_count;
	वापस -1;
पूर्ण

/* Retruns the host firmware handshake OCTEON specअगरic configuration */
काष्ठा octeon_config *octeon_get_conf(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_config *शेष_oct_conf = शून्य;

	/* check the OCTEON Device model & वापस the corresponding octeon
	 * configuration
	 */

	अगर (OCTEON_CN6XXX(oct)) अणु
		शेष_oct_conf =
			(काष्ठा octeon_config *)(CHIP_CONF(oct, cn6xxx));
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_PF(oct)) अणु
		शेष_oct_conf = (काष्ठा octeon_config *)
			(CHIP_CONF(oct, cn23xx_pf));
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_VF(oct)) अणु
		शेष_oct_conf = (काष्ठा octeon_config *)
			(CHIP_CONF(oct, cn23xx_vf));
	पूर्ण
	वापस शेष_oct_conf;
पूर्ण

/* scratch रेजिस्टर address is same in all the OCT-II and CN70XX models */
#घोषणा CNXX_SLI_SCRATCH1   0x3C0

/* Get the octeon device poपूर्णांकer.
 *  @param octeon_id  - The id क्रम which the octeon device poपूर्णांकer is required.
 *  @वापस Success: Octeon device poपूर्णांकer.
 *  @वापस Failure: शून्य.
 */
काष्ठा octeon_device *lio_get_device(u32 octeon_id)
अणु
	अगर (octeon_id >= MAX_OCTEON_DEVICES)
		वापस शून्य;
	अन्यथा
		वापस octeon_device[octeon_id];
पूर्ण

u64 lio_pci_पढ़ोq(काष्ठा octeon_device *oct, u64 addr)
अणु
	u64 val64;
	अचिन्हित दीर्घ flags;
	u32 addrhi;

	spin_lock_irqsave(&oct->pci_win_lock, flags);

	/* The winकरोwed पढ़ो happens when the LSB of the addr is written.
	 * So ग_लिखो MSB first
	 */
	addrhi = (addr >> 32);
	अगर ((oct->chip_id == OCTEON_CN66XX) ||
	    (oct->chip_id == OCTEON_CN68XX) ||
	    (oct->chip_id == OCTEON_CN23XX_PF_VID))
		addrhi |= 0x00060000;
	ग_लिखोl(addrhi, oct->reg_list.pci_win_rd_addr_hi);

	/* Read back to preserve ordering of ग_लिखोs */
	पढ़ोl(oct->reg_list.pci_win_rd_addr_hi);

	ग_लिखोl(addr & 0xffffffff, oct->reg_list.pci_win_rd_addr_lo);
	पढ़ोl(oct->reg_list.pci_win_rd_addr_lo);

	val64 = पढ़ोq(oct->reg_list.pci_win_rd_data);

	spin_unlock_irqrestore(&oct->pci_win_lock, flags);

	वापस val64;
पूर्ण

व्योम lio_pci_ग_लिखोq(काष्ठा octeon_device *oct,
		    u64 val,
		    u64 addr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&oct->pci_win_lock, flags);

	ग_लिखोq(addr, oct->reg_list.pci_win_wr_addr);

	/* The ग_लिखो happens when the LSB is written. So ग_लिखो MSB first. */
	ग_लिखोl(val >> 32, oct->reg_list.pci_win_wr_data_hi);
	/* Read the MSB to ensure ordering of ग_लिखोs. */
	पढ़ोl(oct->reg_list.pci_win_wr_data_hi);

	ग_लिखोl(val & 0xffffffff, oct->reg_list.pci_win_wr_data_lo);

	spin_unlock_irqrestore(&oct->pci_win_lock, flags);
पूर्ण

पूर्णांक octeon_mem_access_ok(काष्ठा octeon_device *oct)
अणु
	u64 access_okay = 0;
	u64 lmc0_reset_ctl;

	/* Check to make sure a DDR पूर्णांकerface is enabled */
	अगर (OCTEON_CN23XX_PF(oct)) अणु
		lmc0_reset_ctl = lio_pci_पढ़ोq(oct, CN23XX_LMC0_RESET_CTL);
		access_okay =
			(lmc0_reset_ctl & CN23XX_LMC0_RESET_CTL_DDR3RST_MASK);
	पूर्ण अन्यथा अणु
		lmc0_reset_ctl = lio_pci_पढ़ोq(oct, CN6XXX_LMC0_RESET_CTL);
		access_okay =
			(lmc0_reset_ctl & CN6XXX_LMC0_RESET_CTL_DDR3RST_MASK);
	पूर्ण

	वापस access_okay ? 0 : 1;
पूर्ण

पूर्णांक octeon_रुको_क्रम_ddr_init(काष्ठा octeon_device *oct, u32 *समयout)
अणु
	पूर्णांक ret = 1;
	u32 ms;

	अगर (!समयout)
		वापस ret;

	क्रम (ms = 0; (ret != 0) && ((*समयout == 0) || (ms <= *समयout));
	     ms += HZ / 10) अणु
		ret = octeon_mem_access_ok(oct);

		/* रुको 100 ms */
		अगर (ret)
			schedule_समयout_unपूर्णांकerruptible(HZ / 10);
	पूर्ण

	वापस ret;
पूर्ण

/* Get the octeon id asचिन्हित to the octeon device passed as argument.
 *  This function is exported to other modules.
 *  @param dev - octeon device poपूर्णांकer passed as a व्योम *.
 *  @वापस octeon device id
 */
पूर्णांक lio_get_device_id(व्योम *dev)
अणु
	काष्ठा octeon_device *octeon_dev = (काष्ठा octeon_device *)dev;
	u32 i;

	क्रम (i = 0; i < MAX_OCTEON_DEVICES; i++)
		अगर (octeon_device[i] == octeon_dev)
			वापस octeon_dev->octeon_id;
	वापस -1;
पूर्ण

व्योम lio_enable_irq(काष्ठा octeon_droq *droq, काष्ठा octeon_instr_queue *iq)
अणु
	u64 instr_cnt;
	u32 pkts_pend;
	काष्ठा octeon_device *oct = शून्य;

	/* the whole thing needs to be atomic, ideally */
	अगर (droq) अणु
		pkts_pend = (u32)atomic_पढ़ो(&droq->pkts_pending);
		ग_लिखोl(droq->pkt_count - pkts_pend, droq->pkts_sent_reg);
		droq->pkt_count = pkts_pend;
		oct = droq->oct_dev;
	पूर्ण
	अगर (iq) अणु
		spin_lock_bh(&iq->lock);
		ग_लिखोl(iq->pkts_processed, iq->inst_cnt_reg);
		iq->pkt_in_करोne -= iq->pkts_processed;
		iq->pkts_processed = 0;
		/* this ग_लिखो needs to be flushed beक्रमe we release the lock */
		spin_unlock_bh(&iq->lock);
		oct = iq->oct_dev;
	पूर्ण
	/*ग_लिखो resend. Writing RESEND in SLI_PKTX_CNTS should be enough
	 *to trigger tx पूर्णांकerrupts as well, अगर they are pending.
	 */
	अगर (oct && (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct))) अणु
		अगर (droq)
			ग_लिखोq(CN23XX_INTR_RESEND, droq->pkts_sent_reg);
		/*we race with firmrware here. पढ़ो and ग_लिखो the IN_DONE_CNTS*/
		अन्यथा अगर (iq) अणु
			instr_cnt =  पढ़ोq(iq->inst_cnt_reg);
			ग_लिखोq(((instr_cnt & 0xFFFFFFFF00000000ULL) |
				CN23XX_INTR_RESEND),
			       iq->inst_cnt_reg);
		पूर्ण
	पूर्ण
पूर्ण
