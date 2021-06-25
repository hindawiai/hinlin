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
/*! \पile  octeon_config.h
 *  \मrief Host Driver: Configuration data काष्ठाures क्रम the host driver.
 */

#अगर_अघोषित __OCTEON_CONFIG_H__
#घोषणा __OCTEON_CONFIG_H__

/*--------------------------CONFIG VALUES------------------------*/

/* The following macros affect the way the driver data काष्ठाures
 * are generated क्रम Octeon devices.
 * They can be modअगरied.
 */

/* Maximum octeon devices defined as MAX_OCTEON_NICIF to support
 * multiple(<= MAX_OCTEON_NICIF) Miniports
 */
#घोषणा   MAX_OCTEON_NICIF             128
#घोषणा   MAX_OCTEON_DEVICES           MAX_OCTEON_NICIF
#घोषणा   MAX_OCTEON_LINKS	       MAX_OCTEON_NICIF
#घोषणा   MAX_OCTEON_MULTICAST_ADDR    32

#घोषणा   MAX_OCTEON_FILL_COUNT        8

/* CN6xxx IQ configuration macros */
#घोषणा   CN6XXX_MAX_INPUT_QUEUES      32
#घोषणा   CN6XXX_MAX_IQ_DESCRIPTORS    2048
#घोषणा   CN6XXX_DB_MIN                1
#घोषणा   CN6XXX_DB_MAX                8
#घोषणा   CN6XXX_DB_TIMEOUT            1

/* CN6xxx OQ configuration macros */
#घोषणा   CN6XXX_MAX_OUTPUT_QUEUES     32
#घोषणा   CN6XXX_MAX_OQ_DESCRIPTORS    2048
#घोषणा   CN6XXX_OQ_BUF_SIZE           1664
#घोषणा   CN6XXX_OQ_PKTSPER_INTR       ((CN6XXX_MAX_OQ_DESCRIPTORS < 512) ? \
					(CN6XXX_MAX_OQ_DESCRIPTORS / 4) : 128)
#घोषणा   CN6XXX_OQ_REFIL_THRESHOLD    ((CN6XXX_MAX_OQ_DESCRIPTORS < 512) ? \
					(CN6XXX_MAX_OQ_DESCRIPTORS / 4) : 128)

#घोषणा   CN6XXX_OQ_INTR_PKT           64
#घोषणा   CN6XXX_OQ_INTR_TIME          100
#घोषणा   DEFAULT_NUM_NIC_PORTS_66XX   2
#घोषणा   DEFAULT_NUM_NIC_PORTS_68XX   4
#घोषणा   DEFAULT_NUM_NIC_PORTS_68XX_210NV  2

/* CN23xx  IQ configuration macros */
#घोषणा   CN23XX_MAX_VFS_PER_PF_PASS_1_0 8
#घोषणा   CN23XX_MAX_VFS_PER_PF_PASS_1_1 31
#घोषणा   CN23XX_MAX_VFS_PER_PF          63
#घोषणा   CN23XX_MAX_RINGS_PER_VF        8

#घोषणा   CN23XX_MAX_RINGS_PER_PF_PASS_1_0 12
#घोषणा   CN23XX_MAX_RINGS_PER_PF_PASS_1_1 32
#घोषणा   CN23XX_MAX_RINGS_PER_PF          64
#घोषणा   CN23XX_MAX_RINGS_PER_VF          8

#घोषणा   CN23XX_MAX_INPUT_QUEUES	CN23XX_MAX_RINGS_PER_PF
#घोषणा   CN23XX_MAX_IQ_DESCRIPTORS	2048
#घोषणा   CN23XX_DEFAULT_IQ_DESCRIPTORS	512
#घोषणा   CN23XX_MIN_IQ_DESCRIPTORS	128
#घोषणा   CN23XX_DB_MIN                 1
#घोषणा   CN23XX_DB_MAX                 8
#घोषणा   CN23XX_DB_TIMEOUT             1

#घोषणा   CN23XX_MAX_OUTPUT_QUEUES	CN23XX_MAX_RINGS_PER_PF
#घोषणा   CN23XX_MAX_OQ_DESCRIPTORS	2048
#घोषणा   CN23XX_DEFAULT_OQ_DESCRIPTORS	512
#घोषणा   CN23XX_MIN_OQ_DESCRIPTORS	128
#घोषणा   CN23XX_OQ_BUF_SIZE		1664
#घोषणा   CN23XX_OQ_PKTSPER_INTR	128
/*#घोषणा CAVIUM_ONLY_CN23XX_RX_PERF*/
#घोषणा   CN23XX_OQ_REFIL_THRESHOLD	16

#घोषणा   CN23XX_OQ_INTR_PKT		64
#घोषणा   CN23XX_OQ_INTR_TIME		100
#घोषणा   DEFAULT_NUM_NIC_PORTS_23XX	1

#घोषणा   CN23XX_CFG_IO_QUEUES		CN23XX_MAX_RINGS_PER_PF
/* PEMs count */
#घोषणा   CN23XX_MAX_MACS		4

#घोषणा   CN23XX_DEF_IQ_INTR_THRESHOLD	32
#घोषणा   CN23XX_DEF_IQ_INTR_BYTE_THRESHOLD   (64 * 1024)
/* common OCTEON configuration macros */
#घोषणा   CN6XXX_CFG_IO_QUEUES         32
#घोषणा   OCTEON_32BYTE_INSTR          32
#घोषणा   OCTEON_64BYTE_INSTR          64
#घोषणा   OCTEON_MAX_BASE_IOQ          4

#घोषणा   OCTEON_DMA_INTR_PKT          64
#घोषणा   OCTEON_DMA_INTR_TIME         1000

#घोषणा MAX_TXQS_PER_INTF  8
#घोषणा MAX_RXQS_PER_INTF  8
#घोषणा DEF_TXQS_PER_INTF  4
#घोषणा DEF_RXQS_PER_INTF  4

#घोषणा INVALID_IOQ_NO          0xff

#घोषणा   DEFAULT_POW_GRP       0

/* Macros to get octeon config params */
#घोषणा CFG_GET_IQ_CFG(cfg)                      ((cfg)->iq)
#घोषणा CFG_GET_IQ_MAX_Q(cfg)                    ((cfg)->iq.max_iqs)
#घोषणा CFG_GET_IQ_PENDING_LIST_SIZE(cfg)        ((cfg)->iq.pending_list_size)
#घोषणा CFG_GET_IQ_INSTR_TYPE(cfg)               ((cfg)->iq.instr_type)
#घोषणा CFG_GET_IQ_DB_MIN(cfg)                   ((cfg)->iq.db_min)
#घोषणा CFG_GET_IQ_DB_TIMEOUT(cfg)               ((cfg)->iq.db_समयout)

#घोषणा CFG_GET_IQ_INTR_PKT(cfg)                 ((cfg)->iq.iq_पूर्णांकr_pkt)
#घोषणा CFG_SET_IQ_INTR_PKT(cfg, val)            (cfg)->iq.iq_पूर्णांकr_pkt = val

#घोषणा CFG_GET_OQ_MAX_Q(cfg)                    ((cfg)->oq.max_oqs)
#घोषणा CFG_GET_OQ_PKTS_PER_INTR(cfg)            ((cfg)->oq.pkts_per_पूर्णांकr)
#घोषणा CFG_GET_OQ_REFILL_THRESHOLD(cfg)         ((cfg)->oq.refill_threshold)
#घोषणा CFG_GET_OQ_INTR_PKT(cfg)                 ((cfg)->oq.oq_पूर्णांकr_pkt)
#घोषणा CFG_GET_OQ_INTR_TIME(cfg)                ((cfg)->oq.oq_पूर्णांकr_समय)
#घोषणा CFG_SET_OQ_INTR_PKT(cfg, val)            (cfg)->oq.oq_पूर्णांकr_pkt = val
#घोषणा CFG_SET_OQ_INTR_TIME(cfg, val)           (cfg)->oq.oq_पूर्णांकr_समय = val

#घोषणा CFG_GET_DMA_INTR_PKT(cfg)                ((cfg)->dma.dma_पूर्णांकr_pkt)
#घोषणा CFG_GET_DMA_INTR_TIME(cfg)               ((cfg)->dma.dma_पूर्णांकr_समय)
#घोषणा CFG_GET_NUM_NIC_PORTS(cfg)               ((cfg)->num_nic_ports)
#घोषणा CFG_GET_NUM_DEF_TX_DESCS(cfg)            ((cfg)->num_def_tx_descs)
#घोषणा CFG_GET_NUM_DEF_RX_DESCS(cfg)            ((cfg)->num_def_rx_descs)
#घोषणा CFG_GET_DEF_RX_BUF_SIZE(cfg)             ((cfg)->def_rx_buf_size)

#घोषणा CFG_GET_MAX_TXQS_NIC_IF(cfg, idx) \
				((cfg)->nic_अगर_cfg[idx].max_txqs)
#घोषणा CFG_GET_NUM_TXQS_NIC_IF(cfg, idx) \
				((cfg)->nic_अगर_cfg[idx].num_txqs)
#घोषणा CFG_GET_MAX_RXQS_NIC_IF(cfg, idx) \
				((cfg)->nic_अगर_cfg[idx].max_rxqs)
#घोषणा CFG_GET_NUM_RXQS_NIC_IF(cfg, idx) \
				((cfg)->nic_अगर_cfg[idx].num_rxqs)
#घोषणा CFG_GET_NUM_RX_DESCS_NIC_IF(cfg, idx) \
				((cfg)->nic_अगर_cfg[idx].num_rx_descs)
#घोषणा CFG_GET_NUM_TX_DESCS_NIC_IF(cfg, idx) \
				((cfg)->nic_अगर_cfg[idx].num_tx_descs)
#घोषणा CFG_GET_NUM_RX_BUF_SIZE_NIC_IF(cfg, idx) \
				((cfg)->nic_अगर_cfg[idx].rx_buf_size)
#घोषणा CFG_GET_BASE_QUE_NIC_IF(cfg, idx) \
				((cfg)->nic_अगर_cfg[idx].base_queue)
#घोषणा CFG_GET_GMXID_NIC_IF(cfg, idx) \
				((cfg)->nic_अगर_cfg[idx].gmx_port_id)

#घोषणा CFG_GET_CTRL_Q_GRP(cfg)                  ((cfg)->misc.ctrlq_grp)
#घोषणा CFG_GET_HOST_LINK_QUERY_INTERVAL(cfg) \
				((cfg)->misc.host_link_query_पूर्णांकerval)
#घोषणा CFG_GET_OCT_LINK_QUERY_INTERVAL(cfg) \
				((cfg)->misc.oct_link_query_पूर्णांकerval)
#घोषणा CFG_GET_IS_SLI_BP_ON(cfg)                ((cfg)->misc.enable_sli_oq_bp)

#घोषणा CFG_SET_NUM_RX_DESCS_NIC_IF(cfg, idx, value) \
				((cfg)->nic_अगर_cfg[idx].num_rx_descs = value)
#घोषणा CFG_SET_NUM_TX_DESCS_NIC_IF(cfg, idx, value) \
				((cfg)->nic_अगर_cfg[idx].num_tx_descs = value)

/* Max IOQs per OCTEON Link */
#घोषणा MAX_IOQS_PER_NICIF              64

क्रमागत lio_card_type अणु
	LIO_210SV = 0, /* Two port, 66xx */
	LIO_210NV,     /* Two port, 68xx */
	LIO_410NV,     /* Four port, 68xx */
	LIO_23XX       /* 23xx */
पूर्ण;

#घोषणा LIO_210SV_NAME "210sv"
#घोषणा LIO_210NV_NAME "210nv"
#घोषणा LIO_410NV_NAME "410nv"
#घोषणा LIO_23XX_NAME  "23xx"

/** Structure to define the configuration attributes क्रम each Input queue.
 *  Applicable to all Octeon processors
 **/
काष्ठा octeon_iq_config अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u64 reserved:16;

	/** Tx पूर्णांकerrupt packets. Applicable to 23xx only */
	u64 iq_पूर्णांकr_pkt:16;

	/** Minimum ticks to रुको beक्रमe checking क्रम pending inकाष्ठाions. */
	u64 db_समयout:16;

	/** Minimum number of commands pending to be posted to Octeon
	 *  beक्रमe driver hits the Input queue करोorbell.
	 */
	u64 db_min:8;

	/** Command size - 32 or 64 bytes */
	u64 instr_type:32;

	/** Pending list size (usually set to the sum of the size of all Input
	 *  queues)
	 */
	u64 pending_list_size:32;

	/* Max number of IQs available */
	u64 max_iqs:8;
#अन्यथा
	/* Max number of IQs available */
	u64 max_iqs:8;

	/** Pending list size (usually set to the sum of the size of all Input
	 *  queues)
	 */
	u64 pending_list_size:32;

	/** Command size - 32 or 64 bytes */
	u64 instr_type:32;

	/** Minimum number of commands pending to be posted to Octeon
	 *  beक्रमe driver hits the Input queue करोorbell.
	 */
	u64 db_min:8;

	/** Minimum ticks to रुको beक्रमe checking क्रम pending inकाष्ठाions. */
	u64 db_समयout:16;

	/** Tx पूर्णांकerrupt packets. Applicable to 23xx only */
	u64 iq_पूर्णांकr_pkt:16;

	u64 reserved:16;
#पूर्ण_अगर
पूर्ण;

/** Structure to define the configuration attributes क्रम each Output queue.
 *  Applicable to all Octeon processors
 **/
काष्ठा octeon_oq_config अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u64 reserved:16;

	u64 pkts_per_पूर्णांकr:16;

	/** Interrupt Coalescing (Time Interval). Octeon will पूर्णांकerrupt the
	 *  host अगर atleast one packet was sent in the समय पूर्णांकerval specअगरied
	 *  by this field. The driver uses समय पूर्णांकerval पूर्णांकerrupt coalescing
	 *  by शेष. The समय is specअगरied in microseconds.
	 */
	u64 oq_पूर्णांकr_समय:16;

	/** Interrupt Coalescing (Packet Count). Octeon will पूर्णांकerrupt the host
	 *  only अगर it sent as many packets as specअगरied by this field.
	 *  The driver
	 *  usually करोes not use packet count पूर्णांकerrupt coalescing.
	 */
	u64 oq_पूर्णांकr_pkt:16;

	/** The number of buffers that were consumed during packet processing by
	 *   the driver on this Output queue beक्रमe the driver attempts to
	 *   replenish
	 *   the descriptor ring with new buffers.
	 */
	u64 refill_threshold:16;

	/* Max number of OQs available */
	u64 max_oqs:8;

#अन्यथा
	/* Max number of OQs available */
	u64 max_oqs:8;

	/** The number of buffers that were consumed during packet processing by
	 *   the driver on this Output queue beक्रमe the driver attempts to
	 *   replenish
	 *   the descriptor ring with new buffers.
	 */
	u64 refill_threshold:16;

	/** Interrupt Coalescing (Packet Count). Octeon will पूर्णांकerrupt the host
	 *  only अगर it sent as many packets as specअगरied by this field.
	 *  The driver
	 *  usually करोes not use packet count पूर्णांकerrupt coalescing.
	 */
	u64 oq_पूर्णांकr_pkt:16;

	/** Interrupt Coalescing (Time Interval). Octeon will पूर्णांकerrupt the
	 *  host अगर atleast one packet was sent in the समय पूर्णांकerval specअगरied
	 *  by this field. The driver uses समय पूर्णांकerval पूर्णांकerrupt coalescing
	 *  by शेष.  The समय is specअगरied in microseconds.
	 */
	u64 oq_पूर्णांकr_समय:16;

	u64 pkts_per_पूर्णांकr:16;

	u64 reserved:16;
#पूर्ण_अगर

पूर्ण;

/** This काष्ठाure conatins the NIC link configuration attributes,
 *  common क्रम all the OCTEON Modles.
 */
काष्ठा octeon_nic_अगर_config अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u64 reserved:56;

	u64 base_queue:16;

	u64 gmx_port_id:8;

	/* SKB size, We need not change buf size even क्रम Jumbo frames.
	 * Octeon can send jumbo frames in 4 consecutive descriptors,
	 */
	u64 rx_buf_size:16;

	/* Num of desc क्रम tx rings */
	u64 num_tx_descs:16;

	/* Num of desc क्रम rx rings */
	u64 num_rx_descs:16;

	/* Actual configured value. Range could be: 1...max_rxqs */
	u64 num_rxqs:16;

	/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
	u64 max_rxqs:16;

	/* Actual configured value. Range could be: 1...max_txqs */
	u64 num_txqs:16;

	/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
	u64 max_txqs:16;
#अन्यथा
	/* Max Txqs: Half क्रम each of the two ports :max_iq/2 */
	u64 max_txqs:16;

	/* Actual configured value. Range could be: 1...max_txqs */
	u64 num_txqs:16;

	/* Max Rxqs: Half क्रम each of the two ports :max_oq/2  */
	u64 max_rxqs:16;

	/* Actual configured value. Range could be: 1...max_rxqs */
	u64 num_rxqs:16;

	/* Num of desc क्रम rx rings */
	u64 num_rx_descs:16;

	/* Num of desc क्रम tx rings */
	u64 num_tx_descs:16;

	/* SKB size, We need not change buf size even क्रम Jumbo frames.
	 * Octeon can send jumbo frames in 4 consecutive descriptors,
	 */
	u64 rx_buf_size:16;

	u64 gmx_port_id:8;

	u64 base_queue:16;

	u64 reserved:56;
#पूर्ण_अगर

पूर्ण;

/** Structure to define the configuration attributes क्रम meta data.
 *  Applicable to all Octeon processors.
 */

काष्ठा octeon_misc_config अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	/** Host link status polling period */
	u64 host_link_query_पूर्णांकerval:32;
	/** Oct link status polling period */
	u64 oct_link_query_पूर्णांकerval:32;

	u64 enable_sli_oq_bp:1;
	/** Control IQ Group */
	u64 ctrlq_grp:4;
#अन्यथा
	/** Control IQ Group */
	u64 ctrlq_grp:4;
	/** BP क्रम SLI OQ */
	u64 enable_sli_oq_bp:1;
	/** Host link status polling period */
	u64 oct_link_query_पूर्णांकerval:32;
	/** Oct link status polling period */
	u64 host_link_query_पूर्णांकerval:32;
#पूर्ण_अगर
पूर्ण;

/** Structure to define the configuration क्रम all OCTEON processors. */
काष्ठा octeon_config अणु
	u16 card_type;
	अक्षर *card_name;

	/** Input Queue attributes. */
	काष्ठा octeon_iq_config iq;

	/** Output Queue attributes. */
	काष्ठा octeon_oq_config oq;

	/** NIC Port Configuration */
	काष्ठा octeon_nic_अगर_config nic_अगर_cfg[MAX_OCTEON_NICIF];

	/** Miscellaneous attributes */
	काष्ठा octeon_misc_config misc;

	पूर्णांक num_nic_ports;

	पूर्णांक num_def_tx_descs;

	/* Num of desc क्रम rx rings */
	पूर्णांक num_def_rx_descs;

	पूर्णांक def_rx_buf_size;

पूर्ण;

/* The following config values are fixed and should not be modअगरied. */

#घोषणा  BAR1_INDEX_DYNAMIC_MAP          2
#घोषणा  BAR1_INDEX_STATIC_MAP          15
#घोषणा  OCTEON_BAR1_ENTRY_SIZE         (4 * 1024 * 1024)

#घोषणा  MAX_BAR1_IOREMAP_SIZE  (16 * OCTEON_BAR1_ENTRY_SIZE)

/* Response lists - 1 ordered, 1 unordered-blocking, 1 unordered-nonblocking
 *                  1 process करोne list, 1 zombie lists(समयouted sc list)
 * NoResponse Lists are now मुख्यtained with each IQ. (Dec' 2007).
 */
#घोषणा MAX_RESPONSE_LISTS           6

/* Opcode hash bits. The opcode is hashed on the lower 6-bits to lookup the
 * dispatch table.
 */
#घोषणा OPCODE_MASK_BITS             6

/* Mask क्रम the 6-bit lookup hash */
#घोषणा OCTEON_OPCODE_MASK           0x3f

/* Size of the dispatch table. The 6-bit hash can index पूर्णांकo 2^6 entries */
#घोषणा DISPATCH_LIST_SIZE                      BIT(OPCODE_MASK_BITS)

/* Maximum number of Octeon Inकाष्ठाion (command) queues */
#घोषणा MAX_OCTEON_INSTR_QUEUES(oct)		\
		(OCTEON_CN23XX_PF(oct) ? CN23XX_MAX_INPUT_QUEUES : \
					CN6XXX_MAX_INPUT_QUEUES)

/* Maximum number of Octeon Inकाष्ठाion (command) queues */
#घोषणा MAX_OCTEON_OUTPUT_QUEUES(oct)		\
		(OCTEON_CN23XX_PF(oct) ? CN23XX_MAX_OUTPUT_QUEUES : \
					CN6XXX_MAX_OUTPUT_QUEUES)

#घोषणा MAX_POSSIBLE_OCTEON_INSTR_QUEUES	CN23XX_MAX_INPUT_QUEUES
#घोषणा MAX_POSSIBLE_OCTEON_OUTPUT_QUEUES	CN23XX_MAX_OUTPUT_QUEUES

#घोषणा MAX_POSSIBLE_VFS			64

#पूर्ण_अगर /* __OCTEON_CONFIG_H__  */
