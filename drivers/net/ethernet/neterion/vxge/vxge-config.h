<शैली गुरु>
/******************************************************************************
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice.  This file is not
 * a complete program and may only be used when the entire operating
 * प्रणाली is licensed under the GPL.
 * See the file COPYING in this distribution क्रम more inक्रमmation.
 *
 * vxge-config.h: Driver क्रम Exar Corp's X3100 Series 10GbE PCIe I/O
 *                Virtualized Server Adapter.
 * Copyright(c) 2002-2010 Exar Corp.
 ******************************************************************************/
#अगर_अघोषित VXGE_CONFIG_H
#घोषणा VXGE_CONFIG_H
#समावेश <linux/hardirq.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

#अगर_अघोषित VXGE_CACHE_LINE_SIZE
#घोषणा VXGE_CACHE_LINE_SIZE 128
#पूर्ण_अगर

#अगर_अघोषित VXGE_ALIGN
#घोषणा VXGE_ALIGN(adrs, size) \
	(((size) - (((u64)adrs) & ((size)-1))) & ((size)-1))
#पूर्ण_अगर

#घोषणा VXGE_HW_MIN_MTU				ETH_MIN_MTU
#घोषणा VXGE_HW_MAX_MTU				9600
#घोषणा VXGE_HW_DEFAULT_MTU			1500

#घोषणा VXGE_HW_MAX_ROM_IMAGES			8

काष्ठा eprom_image अणु
	u8 is_valid:1;
	u8 index;
	u8 type;
	u16 version;
पूर्ण;

#अगर_घोषित VXGE_DEBUG_ASSERT
/**
 * vxge_निश्चित
 * @test: C-condition to check
 * @fmt: म_लिखो like क्रमmat string
 *
 * This function implements traditional निश्चित. By शेष निश्चितions
 * are enabled. It can be disabled by undefining VXGE_DEBUG_ASSERT macro in
 * compilation
 * समय.
 */
#घोषणा vxge_निश्चित(test) BUG_ON(!(test))
#अन्यथा
#घोषणा vxge_निश्चित(test)
#पूर्ण_अगर /* end of VXGE_DEBUG_ASSERT */

/**
 * क्रमागत vxge_debug_level
 * @VXGE_NONE: debug disabled
 * @VXGE_ERR: all errors going to be logged out
 * @VXGE_TRACE: all errors plus all kind of verbose tracing prपूर्णांक outs
 *                 going to be logged out. Very noisy.
 *
 * This क्रमागतeration going to be used to चयन between dअगरferent
 * debug levels during runसमय अगर DEBUG macro defined during
 * compilation. If DEBUG macro not defined than code will be
 * compiled out.
 */
क्रमागत vxge_debug_level अणु
	VXGE_NONE   = 0,
	VXGE_TRACE  = 1,
	VXGE_ERR    = 2
पूर्ण;

#घोषणा शून्य_VPID					0xFFFFFFFF
#अगर_घोषित CONFIG_VXGE_DEBUG_TRACE_ALL
#घोषणा VXGE_DEBUG_MODULE_MASK  0xffffffff
#घोषणा VXGE_DEBUG_TRACE_MASK   0xffffffff
#घोषणा VXGE_DEBUG_ERR_MASK     0xffffffff
#घोषणा VXGE_DEBUG_MASK         0x000001ff
#अन्यथा
#घोषणा VXGE_DEBUG_MODULE_MASK  0x20000000
#घोषणा VXGE_DEBUG_TRACE_MASK   0x20000000
#घोषणा VXGE_DEBUG_ERR_MASK     0x20000000
#घोषणा VXGE_DEBUG_MASK         0x00000001
#पूर्ण_अगर

/*
 * @VXGE_COMPONENT_LL: करो debug क्रम vxge link layer module
 * @VXGE_COMPONENT_ALL: activate debug क्रम all modules with no exceptions
 *
 * This क्रमागतeration going to be used to distinguish modules
 * or libraries during compilation and runसमय.  Makefile must declare
 * VXGE_DEBUG_MODULE_MASK macro and set it to proper value.
 */
#घोषणा	VXGE_COMPONENT_LL				0x20000000
#घोषणा	VXGE_COMPONENT_ALL				0xffffffff

#घोषणा VXGE_HW_BASE_INF	100
#घोषणा VXGE_HW_BASE_ERR	200
#घोषणा VXGE_HW_BASE_BADCFG	300

क्रमागत vxge_hw_status अणु
	VXGE_HW_OK				  = 0,
	VXGE_HW_FAIL				  = 1,
	VXGE_HW_PENDING				  = 2,
	VXGE_HW_COMPLETIONS_REMAIN		  = 3,

	VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS = VXGE_HW_BASE_INF + 1,
	VXGE_HW_INF_OUT_OF_DESCRIPTORS		  = VXGE_HW_BASE_INF + 2,

	VXGE_HW_ERR_INVALID_HANDLE		  = VXGE_HW_BASE_ERR + 1,
	VXGE_HW_ERR_OUT_OF_MEMORY		  = VXGE_HW_BASE_ERR + 2,
	VXGE_HW_ERR_VPATH_NOT_AVAILABLE	  	  = VXGE_HW_BASE_ERR + 3,
	VXGE_HW_ERR_VPATH_NOT_OPEN		  = VXGE_HW_BASE_ERR + 4,
	VXGE_HW_ERR_WRONG_IRQ			  = VXGE_HW_BASE_ERR + 5,
	VXGE_HW_ERR_SWAPPER_CTRL		  = VXGE_HW_BASE_ERR + 6,
	VXGE_HW_ERR_INVALID_MTU_SIZE		  = VXGE_HW_BASE_ERR + 7,
	VXGE_HW_ERR_INVALID_INDEX		  = VXGE_HW_BASE_ERR + 8,
	VXGE_HW_ERR_INVALID_TYPE		  = VXGE_HW_BASE_ERR + 9,
	VXGE_HW_ERR_INVALID_OFFSET		  = VXGE_HW_BASE_ERR + 10,
	VXGE_HW_ERR_INVALID_DEVICE		  = VXGE_HW_BASE_ERR + 11,
	VXGE_HW_ERR_VERSION_CONFLICT		  = VXGE_HW_BASE_ERR + 12,
	VXGE_HW_ERR_INVALID_PCI_INFO		  = VXGE_HW_BASE_ERR + 13,
	VXGE_HW_ERR_INVALID_TCODE 		  = VXGE_HW_BASE_ERR + 14,
	VXGE_HW_ERR_INVALID_BLOCK_SIZE		  = VXGE_HW_BASE_ERR + 15,
	VXGE_HW_ERR_INVALID_STATE		  = VXGE_HW_BASE_ERR + 16,
	VXGE_HW_ERR_PRIVILEGED_OPERATION	  = VXGE_HW_BASE_ERR + 17,
	VXGE_HW_ERR_INVALID_PORT 		  = VXGE_HW_BASE_ERR + 18,
	VXGE_HW_ERR_FIFO		 	  = VXGE_HW_BASE_ERR + 19,
	VXGE_HW_ERR_VPATH			  = VXGE_HW_BASE_ERR + 20,
	VXGE_HW_ERR_CRITICAL			  = VXGE_HW_BASE_ERR + 21,
	VXGE_HW_ERR_SLOT_FREEZE 		  = VXGE_HW_BASE_ERR + 22,

	VXGE_HW_BADCFG_RING_INDICATE_MAX_PKTS	  = VXGE_HW_BASE_BADCFG + 1,
	VXGE_HW_BADCFG_FIFO_BLOCKS		  = VXGE_HW_BASE_BADCFG + 2,
	VXGE_HW_BADCFG_VPATH_MTU		  = VXGE_HW_BASE_BADCFG + 3,
	VXGE_HW_BADCFG_VPATH_RPA_STRIP_VLAN_TAG	  = VXGE_HW_BASE_BADCFG + 4,
	VXGE_HW_BADCFG_VPATH_MIN_BANDWIDTH	  = VXGE_HW_BASE_BADCFG + 5,
	VXGE_HW_BADCFG_INTR_MODE		  = VXGE_HW_BASE_BADCFG + 6,
	VXGE_HW_BADCFG_RTS_MAC_EN		  = VXGE_HW_BASE_BADCFG + 7,

	VXGE_HW_खातापूर्ण_TRACE_BUF			  = -1
पूर्ण;

/**
 * क्रमागत क्रमागत vxge_hw_device_link_state - Link state क्रमागतeration.
 * @VXGE_HW_LINK_NONE: Invalid link state.
 * @VXGE_HW_LINK_DOWN: Link is करोwn.
 * @VXGE_HW_LINK_UP: Link is up.
 *
 */
क्रमागत vxge_hw_device_link_state अणु
	VXGE_HW_LINK_NONE,
	VXGE_HW_LINK_DOWN,
	VXGE_HW_LINK_UP
पूर्ण;

/**
 * क्रमागत क्रमागत vxge_hw_fw_upgrade_code - FW upgrade वापस codes.
 * @VXGE_HW_FW_UPGRADE_OK: All OK send next 16 bytes
 * @VXGE_HW_FW_UPGRADE_DONE:  upload completed
 * @VXGE_HW_FW_UPGRADE_ERR:  upload error
 * @VXGE_FW_UPGRADE_BYTES2SKIP:  skip bytes in the stream
 *
 */
क्रमागत vxge_hw_fw_upgrade_code अणु
	VXGE_HW_FW_UPGRADE_OK		= 0,
	VXGE_HW_FW_UPGRADE_DONE		= 1,
	VXGE_HW_FW_UPGRADE_ERR		= 2,
	VXGE_FW_UPGRADE_BYTES2SKIP	= 3
पूर्ण;

/**
 * क्रमागत क्रमागत vxge_hw_fw_upgrade_err_code - FW upgrade error codes.
 * @VXGE_HW_FW_UPGRADE_ERR_CORRUPT_DATA_1: corrupt data
 * @VXGE_HW_FW_UPGRADE_ERR_BUFFER_OVERFLOW: buffer overflow
 * @VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_3: invalid .ncf file
 * @VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_4: invalid .ncf file
 * @VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_5: invalid .ncf file
 * @VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_6: invalid .ncf file
 * @VXGE_HW_FW_UPGRADE_ERR_CORRUPT_DATA_7: corrupt data
 * @VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_8: invalid .ncf file
 * @VXGE_HW_FW_UPGRADE_ERR_GENERIC_ERROR_UNKNOWN: generic error unknown type
 * @VXGE_HW_FW_UPGRADE_ERR_FAILED_TO_FLASH: failed to flash image check failed
 */
क्रमागत vxge_hw_fw_upgrade_err_code अणु
	VXGE_HW_FW_UPGRADE_ERR_CORRUPT_DATA_1		= 1,
	VXGE_HW_FW_UPGRADE_ERR_BUFFER_OVERFLOW		= 2,
	VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_3		= 3,
	VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_4		= 4,
	VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_5		= 5,
	VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_6		= 6,
	VXGE_HW_FW_UPGRADE_ERR_CORRUPT_DATA_7		= 7,
	VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_8		= 8,
	VXGE_HW_FW_UPGRADE_ERR_GENERIC_ERROR_UNKNOWN	= 9,
	VXGE_HW_FW_UPGRADE_ERR_FAILED_TO_FLASH		= 10
पूर्ण;

/**
 * काष्ठा vxge_hw_device_date - Date Format
 * @day: Day
 * @month: Month
 * @year: Year
 * @date: Date in string क्रमmat
 *
 * Structure क्रम वापसing date
 */

#घोषणा VXGE_HW_FW_STRLEN	32
काष्ठा vxge_hw_device_date अणु
	u32     day;
	u32     month;
	u32     year;
	अक्षर    date[VXGE_HW_FW_STRLEN];
पूर्ण;

काष्ठा vxge_hw_device_version अणु
	u32     major;
	u32     minor;
	u32     build;
	अक्षर    version[VXGE_HW_FW_STRLEN];
पूर्ण;

/**
 * काष्ठा vxge_hw_fअगरo_config - Configuration of fअगरo.
 * @enable: Is this fअगरo to be commissioned
 * @fअगरo_blocks: Numbers of TxDL (that is, lists of Tx descriptors)
 * 		blocks per queue.
 * @max_frags: Max number of Tx buffers per TxDL (that is, per single
 *             transmit operation).
 *             No more than 256 transmit buffers can be specअगरied.
 * @memblock_size: Fअगरo descriptors are allocated in blocks of @mem_block_size
 *             bytes. Setting @memblock_size to page size ensures
 *             by-page allocation of descriptors. 128K bytes is the
 *             maximum supported block size.
 * @alignment_size: per Tx fragment DMA-able memory used to align transmit data
 *             (e.g., to align on a cache line).
 * @पूर्णांकr: Boolean. Use 1 to generate पूर्णांकerrupt क्रम each completed TxDL.
 *             Use 0 otherwise.
 * @no_snoop_bits: If non-zero, specअगरies no-snoop PCI operation,
 *             which generally improves latency of the host bridge operation
 *             (see PCI specअगरication). For valid values please refer
 *             to काष्ठा vxge_hw_fअगरo_configअणुपूर्ण in the driver sources.
 * Configuration of all Titan fअगरos.
 * Note: Valid (min, max) range क्रम each attribute is specअगरied in the body of
 * the काष्ठा vxge_hw_fअगरo_configअणुपूर्ण काष्ठाure.
 */
काष्ठा vxge_hw_fअगरo_config अणु
	u32				enable;
#घोषणा VXGE_HW_FIFO_ENABLE				1
#घोषणा VXGE_HW_FIFO_DISABLE				0

	u32				fअगरo_blocks;
#घोषणा VXGE_HW_MIN_FIFO_BLOCKS				2
#घोषणा VXGE_HW_MAX_FIFO_BLOCKS				128

	u32				max_frags;
#घोषणा VXGE_HW_MIN_FIFO_FRAGS				1
#घोषणा VXGE_HW_MAX_FIFO_FRAGS				256

	u32				memblock_size;
#घोषणा VXGE_HW_MIN_FIFO_MEMBLOCK_SIZE			VXGE_HW_BLOCK_SIZE
#घोषणा VXGE_HW_MAX_FIFO_MEMBLOCK_SIZE			131072
#घोषणा VXGE_HW_DEF_FIFO_MEMBLOCK_SIZE			8096

	u32		                alignment_size;
#घोषणा VXGE_HW_MIN_FIFO_ALIGNMENT_SIZE		0
#घोषणा VXGE_HW_MAX_FIFO_ALIGNMENT_SIZE		65536
#घोषणा VXGE_HW_DEF_FIFO_ALIGNMENT_SIZE		VXGE_CACHE_LINE_SIZE

	u32		                पूर्णांकr;
#घोषणा VXGE_HW_FIFO_QUEUE_INTR_ENABLE			1
#घोषणा VXGE_HW_FIFO_QUEUE_INTR_DISABLE			0
#घोषणा VXGE_HW_FIFO_QUEUE_INTR_DEFAULT			0

	u32				no_snoop_bits;
#घोषणा VXGE_HW_FIFO_NO_SNOOP_DISABLED			0
#घोषणा VXGE_HW_FIFO_NO_SNOOP_TXD			1
#घोषणा VXGE_HW_FIFO_NO_SNOOP_FRM			2
#घोषणा VXGE_HW_FIFO_NO_SNOOP_ALL			3
#घोषणा VXGE_HW_FIFO_NO_SNOOP_DEFAULT			0

पूर्ण;
/**
 * काष्ठा vxge_hw_ring_config - Ring configurations.
 * @enable: Is this ring to be commissioned
 * @ring_blocks: Numbers of RxD blocks in the ring
 * @buffer_mode: Receive buffer mode (1, 2, 3, or 5); क्रम details please refer
 *             to Titan User Guide.
 * @scatter_mode: Titan supports two receive scatter modes: A and B.
 *             For details please refer to Titan User Guide.
 * @rx_समयr_val: The number of 32ns periods that would be counted between two
 *             समयr पूर्णांकerrupts.
 * @greedy_वापस: If Set it क्रमces the device to वापस असलolutely all RxD
 *             that are consumed and still on board when a समयr पूर्णांकerrupt
 *             triggers. If Clear, then अगर the device has alपढ़ोy वापसed
 *             RxD beक्रमe current समयr पूर्णांकerrupt triggered and after the
 *             previous समयr पूर्णांकerrupt triggered, then the device is not
 *             क्रमced to वापसed the rest of the consumed RxD that it has
 *             on board which account क्रम a byte count less than the one
 *             programmed पूर्णांकo PRC_CFG6.RXD_CRXDT field
 * @rx_समयr_ci: TBD
 * @backoff_पूर्णांकerval_us: Time (in microseconds), after which Titan
 *             tries to करोwnload RxDs posted by the host.
 *             Note that the "backoff" करोes not happen अगर host posts receive
 *             descriptors in the समयly fashion.
 * Ring configuration.
 */
काष्ठा vxge_hw_ring_config अणु
	u32				enable;
#घोषणा VXGE_HW_RING_ENABLE					1
#घोषणा VXGE_HW_RING_DISABLE					0
#घोषणा VXGE_HW_RING_DEFAULT					1

	u32				ring_blocks;
#घोषणा VXGE_HW_MIN_RING_BLOCKS					1
#घोषणा VXGE_HW_MAX_RING_BLOCKS					128
#घोषणा VXGE_HW_DEF_RING_BLOCKS					2

	u32				buffer_mode;
#घोषणा VXGE_HW_RING_RXD_BUFFER_MODE_1				1
#घोषणा VXGE_HW_RING_RXD_BUFFER_MODE_3				3
#घोषणा VXGE_HW_RING_RXD_BUFFER_MODE_5				5
#घोषणा VXGE_HW_RING_RXD_BUFFER_MODE_DEFAULT			1

	u32				scatter_mode;
#घोषणा VXGE_HW_RING_SCATTER_MODE_A				0
#घोषणा VXGE_HW_RING_SCATTER_MODE_B				1
#घोषणा VXGE_HW_RING_SCATTER_MODE_C				2
#घोषणा VXGE_HW_RING_SCATTER_MODE_USE_FLASH_DEFAULT		0xffffffff

	u64				rxds_limit;
#घोषणा VXGE_HW_DEF_RING_RXDS_LIMIT				44
पूर्ण;

/**
 * काष्ठा vxge_hw_vp_config - Configuration of भव path
 * @vp_id: Virtual Path Id
 * @min_bandwidth: Minimum Guaranteed bandwidth
 * @ring: See काष्ठा vxge_hw_ring_configअणुपूर्ण.
 * @fअगरo: See काष्ठा vxge_hw_fअगरo_configअणुपूर्ण.
 * @tti: Configuration of पूर्णांकerrupt associated with Transmit.
 *             see काष्ठा vxge_hw_tim_पूर्णांकr_config();
 * @rti: Configuration of पूर्णांकerrupt associated with Receive.
 *              see काष्ठा vxge_hw_tim_पूर्णांकr_config();
 * @mtu: mtu size used on this port.
 * @rpa_strip_vlan_tag: Strip VLAN Tag enable/disable. Inकाष्ठाs the device to
 *             हटाओ the VLAN tag from all received tagged frames that are not
 *             replicated at the पूर्णांकernal L2 चयन.
 *             0 - Do not strip the VLAN tag.
 *             1 - Strip the VLAN tag. Regardless of this setting, VLAN tags are
 *                 always placed पूर्णांकo the RxDMA descriptor.
 *
 * This काष्ठाure is used by the driver to pass the configuration parameters to
 * configure Virtual Path.
 */
काष्ठा vxge_hw_vp_config अणु
	u32				vp_id;

#घोषणा	VXGE_HW_VPATH_PRIORITY_MIN			0
#घोषणा	VXGE_HW_VPATH_PRIORITY_MAX			16
#घोषणा	VXGE_HW_VPATH_PRIORITY_DEFAULT			0

	u32				min_bandwidth;
#घोषणा	VXGE_HW_VPATH_BANDWIDTH_MIN			0
#घोषणा	VXGE_HW_VPATH_BANDWIDTH_MAX			100
#घोषणा	VXGE_HW_VPATH_BANDWIDTH_DEFAULT			0

	काष्ठा vxge_hw_ring_config		ring;
	काष्ठा vxge_hw_fअगरo_config		fअगरo;
	काष्ठा vxge_hw_tim_पूर्णांकr_config	tti;
	काष्ठा vxge_hw_tim_पूर्णांकr_config	rti;

	u32				mtu;
#घोषणा VXGE_HW_VPATH_MIN_INITIAL_MTU			VXGE_HW_MIN_MTU
#घोषणा VXGE_HW_VPATH_MAX_INITIAL_MTU			VXGE_HW_MAX_MTU
#घोषणा VXGE_HW_VPATH_USE_FLASH_DEFAULT_INITIAL_MTU	0xffffffff

	u32				rpa_strip_vlan_tag;
#घोषणा VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_ENABLE			1
#घोषणा VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_DISABLE		0
#घोषणा VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_USE_FLASH_DEFAULT	0xffffffff

पूर्ण;
/**
 * काष्ठा vxge_hw_device_config - Device configuration.
 * @dma_blockpool_initial: Initial size of DMA Pool
 * @dma_blockpool_max: Maximum blocks in DMA pool
 * @पूर्णांकr_mode: Line, or MSI-X पूर्णांकerrupt.
 *
 * @rth_en: Enable Receive Traffic Hashing(RTH) using IT(Indirection Table).
 * @rth_it_type: RTH IT table programming type
 * @rts_mac_en: Enable Receive Traffic Steering using MAC destination address
 * @vp_config: Configuration क्रम भव paths
 * @device_poll_millis: Specअगरy the पूर्णांकerval (in mulliseconds)
 * 			to रुको क्रम रेजिस्टर पढ़ोs
 *
 * Titan configuration.
 * Contains per-device configuration parameters, including:
 * - stats sampling पूर्णांकerval, etc.
 *
 * In addition, काष्ठा vxge_hw_device_configअणुपूर्ण includes "subordinate"
 * configurations, including:
 * - fअगरos and rings;
 * - MAC (करोne at firmware level).
 *
 * See Titan User Guide क्रम more details.
 * Note: Valid (min, max) range क्रम each attribute is specअगरied in the body of
 * the काष्ठा vxge_hw_device_configअणुपूर्ण काष्ठाure. Please refer to the
 * corresponding include file.
 * See also: काष्ठा vxge_hw_tim_पूर्णांकr_configअणुपूर्ण.
 */
काष्ठा vxge_hw_device_config अणु
	u32					device_poll_millis;
#घोषणा VXGE_HW_MIN_DEVICE_POLL_MILLIS		1
#घोषणा VXGE_HW_MAX_DEVICE_POLL_MILLIS		100000
#घोषणा VXGE_HW_DEF_DEVICE_POLL_MILLIS		1000

	u32					dma_blockpool_initial;
	u32					dma_blockpool_max;
#घोषणा VXGE_HW_MIN_DMA_BLOCK_POOL_SIZE		0
#घोषणा VXGE_HW_INITIAL_DMA_BLOCK_POOL_SIZE	0
#घोषणा VXGE_HW_INCR_DMA_BLOCK_POOL_SIZE	4
#घोषणा VXGE_HW_MAX_DMA_BLOCK_POOL_SIZE		4096

#घोषणा	VXGE_HW_MAX_PAYLOAD_SIZE_512		2

	u32					पूर्णांकr_mode:2,
#घोषणा VXGE_HW_INTR_MODE_IRQLINE		0
#घोषणा VXGE_HW_INTR_MODE_MSIX			1
#घोषणा VXGE_HW_INTR_MODE_MSIX_ONE_SHOT		2

#घोषणा VXGE_HW_INTR_MODE_DEF			0

						rth_en:1,
#घोषणा VXGE_HW_RTH_DISABLE			0
#घोषणा VXGE_HW_RTH_ENABLE			1
#घोषणा VXGE_HW_RTH_DEFAULT			0

						rth_it_type:1,
#घोषणा VXGE_HW_RTH_IT_TYPE_SOLO_IT		0
#घोषणा VXGE_HW_RTH_IT_TYPE_MULTI_IT		1
#घोषणा VXGE_HW_RTH_IT_TYPE_DEFAULT		0

						rts_mac_en:1,
#घोषणा VXGE_HW_RTS_MAC_DISABLE			0
#घोषणा VXGE_HW_RTS_MAC_ENABLE			1
#घोषणा VXGE_HW_RTS_MAC_DEFAULT			0

						hwts_en:1;
#घोषणा	VXGE_HW_HWTS_DISABLE			0
#घोषणा	VXGE_HW_HWTS_ENABLE			1
#घोषणा	VXGE_HW_HWTS_DEFAULT			1

	काष्ठा vxge_hw_vp_config vp_config[VXGE_HW_MAX_VIRTUAL_PATHS];
पूर्ण;

/**
 * function vxge_uld_link_up_f - Link-Up callback provided by driver.
 * @devh: HW device handle.
 * Link-up notअगरication callback provided by the driver.
 * This is one of the per-driver callbacks, see काष्ठा vxge_hw_uld_cbsअणुपूर्ण.
 *
 * See also: काष्ठा vxge_hw_uld_cbsअणुपूर्ण, vxge_uld_link_करोwn_fअणुपूर्ण,
 * vxge_hw_driver_initialize().
 */

/**
 * function vxge_uld_link_करोwn_f - Link-Down callback provided by
 * driver.
 * @devh: HW device handle.
 *
 * Link-Down notअगरication callback provided by the driver.
 * This is one of the per-driver callbacks, see काष्ठा vxge_hw_uld_cbsअणुपूर्ण.
 *
 * See also: काष्ठा vxge_hw_uld_cbsअणुपूर्ण, vxge_uld_link_up_fअणुपूर्ण,
 * vxge_hw_driver_initialize().
 */

/**
 * function vxge_uld_crit_err_f - Critical Error notअगरication callback.
 * @devh: HW device handle.
 * (typically - at HW device iinitialization समय).
 * @type: Enumerated hw error, e.g.: द्विगुन ECC.
 * @serr_data: Titan status.
 * @ext_data: Extended data. The contents depends on the @type.
 *
 * Link-Down notअगरication callback provided by the driver.
 * This is one of the per-driver callbacks, see काष्ठा vxge_hw_uld_cbsअणुपूर्ण.
 *
 * See also: काष्ठा vxge_hw_uld_cbsअणुपूर्ण, क्रमागत vxge_hw_eventअणुपूर्ण,
 * vxge_hw_driver_initialize().
 */

/**
 * काष्ठा vxge_hw_uld_cbs - driver "slow-path" callbacks.
 * @link_up: See vxge_uld_link_up_fअणुपूर्ण.
 * @link_करोwn: See vxge_uld_link_करोwn_fअणुपूर्ण.
 * @crit_err: See vxge_uld_crit_err_fअणुपूर्ण.
 *
 * Driver slow-path (per-driver) callbacks.
 * Implemented by driver and provided to HW via
 * vxge_hw_driver_initialize().
 * Note that these callbacks are not mandatory: HW will not invoke
 * a callback अगर शून्य is specअगरied.
 *
 * See also: vxge_hw_driver_initialize().
 */
काष्ठा vxge_hw_uld_cbs अणु
	व्योम (*link_up)(काष्ठा __vxge_hw_device *devh);
	व्योम (*link_करोwn)(काष्ठा __vxge_hw_device *devh);
	व्योम (*crit_err)(काष्ठा __vxge_hw_device *devh,
			क्रमागत vxge_hw_event type, u64 ext_data);
पूर्ण;

/*
 * काष्ठा __vxge_hw_blockpool_entry - Block निजी data काष्ठाure
 * @item: List header used to link.
 * @length: Length of the block
 * @memblock: Virtual address block
 * @dma_addr: DMA Address of the block.
 * @dma_handle: DMA handle of the block.
 * @acc_handle: DMA acc handle
 *
 * Block is allocated with a header to put the blocks पूर्णांकo list.
 *
 */
काष्ठा __vxge_hw_blockpool_entry अणु
	काष्ठा list_head	item;
	u32			length;
	व्योम			*memblock;
	dma_addr_t		dma_addr;
	काष्ठा pci_dev 		*dma_handle;
	काष्ठा pci_dev 		*acc_handle;
पूर्ण;

/*
 * काष्ठा __vxge_hw_blockpool - Block Pool
 * @hldev: HW device
 * @block_size: size of each block.
 * @Pool_size: Number of blocks in the pool
 * @pool_max: Maximum number of blocks above which to मुक्त additional blocks
 * @req_out: Number of block requests with OS out standing
 * @मुक्त_block_list: List of मुक्त blocks
 *
 * Block pool contains the DMA blocks pपुनः_स्मृतिated.
 *
 */
काष्ठा __vxge_hw_blockpool अणु
	काष्ठा __vxge_hw_device *hldev;
	u32				block_size;
	u32				pool_size;
	u32				pool_max;
	u32				req_out;
	काष्ठा list_head		मुक्त_block_list;
	काष्ठा list_head		मुक्त_entry_list;
पूर्ण;

/*
 * क्रमागत क्रमागत __vxge_hw_channel_type - Enumerated channel types.
 * @VXGE_HW_CHANNEL_TYPE_UNKNOWN: Unknown channel.
 * @VXGE_HW_CHANNEL_TYPE_FIFO: fअगरo.
 * @VXGE_HW_CHANNEL_TYPE_RING: ring.
 * @VXGE_HW_CHANNEL_TYPE_MAX: Maximum number of HW-supported
 * (and recognized) channel types. Currently: 2.
 *
 * Enumerated channel types. Currently there are only two link-layer
 * channels - Titan fअगरo and Titan ring. In the future the list will grow.
 */
क्रमागत __vxge_hw_channel_type अणु
	VXGE_HW_CHANNEL_TYPE_UNKNOWN			= 0,
	VXGE_HW_CHANNEL_TYPE_FIFO			= 1,
	VXGE_HW_CHANNEL_TYPE_RING			= 2,
	VXGE_HW_CHANNEL_TYPE_MAX			= 3
पूर्ण;

/*
 * काष्ठा __vxge_hw_channel
 * @item: List item; used to मुख्यtain a list of खोलो channels.
 * @type: Channel type. See क्रमागत vxge_hw_channel_typeअणुपूर्ण.
 * @devh: Device handle. HW device object that contains _this_ channel.
 * @vph: Virtual path handle. Virtual Path Object that contains _this_ channel.
 * @length: Channel length. Currently allocated number of descriptors.
 *          The channel length "grows" when more descriptors get allocated.
 *          See _hw_mempool_grow.
 * @reserve_arr: Reserve array. Contains descriptors that can be reserved
 *               by driver क्रम the subsequent send or receive operation.
 *               See vxge_hw_fअगरo_txdl_reserve(),
 *               vxge_hw_ring_rxd_reserve().
 * @reserve_ptr: Current poपूर्णांकer in the resrve array
 * @reserve_top: Reserve top gives the maximum number of dtrs available in
 *          reserve array.
 * @work_arr: Work array. Contains descriptors posted to the channel.
 *            Note that at any poपूर्णांक in समय @work_arr contains 3 types of
 *            descriptors:
 *            1) posted but not yet consumed by Titan device;
 *            2) consumed but not yet completed;
 *            3) completed but not yet मुक्तd
 *            (via vxge_hw_fअगरo_txdl_मुक्त() or vxge_hw_ring_rxd_मुक्त())
 * @post_index: Post index. At any poपूर्णांक in समय poपूर्णांकs on the
 *              position in the channel, which'll contain next to-be-posted
 *              descriptor.
 * @compl_index: Completion index. At any poपूर्णांक in समय poपूर्णांकs on the
 *               position in the channel, which will contain next
 *               to-be-completed descriptor.
 * @मुक्त_arr: Free array. Contains completed descriptors that were मुक्तd
 *            (i.e., handed over back to HW) by driver.
 *            See vxge_hw_fअगरo_txdl_मुक्त(), vxge_hw_ring_rxd_मुक्त().
 * @मुक्त_ptr: current poपूर्णांकer in मुक्त array
 * @per_dtr_space: Per-descriptor space (in bytes) that channel user can utilize
 *                 to store per-operation control inक्रमmation.
 * @stats: Poपूर्णांकer to common statistics
 * @userdata: Per-channel opaque (व्योम*) user-defined context, which may be
 *            driver object, ULP connection, etc.
 *            Once channel is खोलो, @userdata is passed back to user via
 *            vxge_hw_channel_callback_f.
 *
 * HW channel object.
 *
 * See also: क्रमागत vxge_hw_channel_typeअणुपूर्ण, क्रमागत vxge_hw_channel_flag
 */
काष्ठा __vxge_hw_channel अणु
	काष्ठा list_head		item;
	क्रमागत __vxge_hw_channel_type	type;
	काष्ठा __vxge_hw_device 	*devh;
	काष्ठा __vxge_hw_vpath_handle 	*vph;
	u32			length;
	u32			vp_id;
	व्योम		**reserve_arr;
	u32			reserve_ptr;
	u32			reserve_top;
	व्योम		**work_arr;
	u32			post_index ____cacheline_aligned;
	u32			compl_index ____cacheline_aligned;
	व्योम		**मुक्त_arr;
	u32			मुक्त_ptr;
	व्योम		**orig_arr;
	u32			per_dtr_space;
	व्योम		*userdata;
	काष्ठा vxge_hw_common_reg	__iomem *common_reg;
	u32			first_vp_id;
	काष्ठा vxge_hw_vpath_stats_sw_common_info *stats;

पूर्ण ____cacheline_aligned;

/*
 * काष्ठा __vxge_hw_भवpath - Virtual Path
 *
 * @vp_id: Virtual path id
 * @vp_खोलो: This flag specअगरies अगर vxge_hw_vp_खोलो is called from LL Driver
 * @hldev: Hal device
 * @vp_config: Virtual Path Config
 * @vp_reg: VPATH Register map address in BAR0
 * @vpmgmt_reg: VPATH_MGMT रेजिस्टर map address
 * @max_mtu: Max mtu that can be supported
 * @vsport_number: vsport attached to this vpath
 * @max_kdfc_db: Maximum kernel mode करोorbells
 * @max_nofl_db: Maximum non offload करोorbells
 * @tx_पूर्णांकr_num: Interrupt Number associated with the TX

 * @ringh: Ring Queue
 * @fअगरoh: FIFO Queue
 * @vpath_handles: Virtual Path handles list
 * @stats_block: Memory क्रम DMAing stats
 * @stats: Vpath statistics
 *
 * Virtual path काष्ठाure to encapsulate the data related to a भव path.
 * Virtual paths are allocated by the HW upon getting configuration from the
 * driver and inserted पूर्णांकo the list of भव paths.
 */
काष्ठा __vxge_hw_भवpath अणु
	u32				vp_id;

	u32				vp_खोलो;
#घोषणा VXGE_HW_VP_NOT_OPEN	0
#घोषणा	VXGE_HW_VP_OPEN		1

	काष्ठा __vxge_hw_device		*hldev;
	काष्ठा vxge_hw_vp_config	*vp_config;
	काष्ठा vxge_hw_vpath_reg	__iomem *vp_reg;
	काष्ठा vxge_hw_vpmgmt_reg	__iomem *vpmgmt_reg;
	काष्ठा __vxge_hw_non_offload_db_wrapper	__iomem *nofl_db;

	u32				max_mtu;
	u32				vsport_number;
	u32				max_kdfc_db;
	u32				max_nofl_db;
	u64				tim_tti_cfg1_saved;
	u64				tim_tti_cfg3_saved;
	u64				tim_rti_cfg1_saved;
	u64				tim_rti_cfg3_saved;

	काष्ठा __vxge_hw_ring *____cacheline_aligned ringh;
	काष्ठा __vxge_hw_fअगरo *____cacheline_aligned fअगरoh;
	काष्ठा list_head		vpath_handles;
	काष्ठा __vxge_hw_blockpool_entry		*stats_block;
	काष्ठा vxge_hw_vpath_stats_hw_info	*hw_stats;
	काष्ठा vxge_hw_vpath_stats_hw_info	*hw_stats_sav;
	काष्ठा vxge_hw_vpath_stats_sw_info	*sw_stats;
	spinlock_t lock;
पूर्ण;

/*
 * काष्ठा __vxge_hw_vpath_handle - List item to store callback inक्रमmation
 * @item: List head to keep the item in linked list
 * @vpath: Virtual path to which this item beदीर्घs
 *
 * This काष्ठाure is used to store the callback inक्रमmation.
 */
काष्ठा __vxge_hw_vpath_handle अणु
	काष्ठा list_head	item;
	काष्ठा __vxge_hw_भवpath	*vpath;
पूर्ण;

/*
 * काष्ठा __vxge_hw_device
 *
 * HW device object.
 */
/**
 * काष्ठा __vxge_hw_device  - Hal device object
 * @magic: Magic Number
 * @bar0: BAR0 भव address.
 * @pdev: Physical device handle
 * @config: Confguration passed by the LL driver at initialization
 * @link_state: Link state
 *
 * HW device object. Represents Titan adapter
 */
काष्ठा __vxge_hw_device अणु
	u32				magic;
#घोषणा VXGE_HW_DEVICE_MAGIC		0x12345678
#घोषणा VXGE_HW_DEVICE_DEAD		0xDEADDEAD
	व्योम __iomem			*bar0;
	काष्ठा pci_dev			*pdev;
	काष्ठा net_device		*ndev;
	काष्ठा vxge_hw_device_config	config;
	क्रमागत vxge_hw_device_link_state	link_state;

	स्थिर काष्ठा vxge_hw_uld_cbs	*uld_callbacks;

	u32				host_type;
	u32				func_id;
	u32				access_rights;
#घोषणा VXGE_HW_DEVICE_ACCESS_RIGHT_VPATH      0x1
#घोषणा VXGE_HW_DEVICE_ACCESS_RIGHT_SRPCIM     0x2
#घोषणा VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM     0x4
	काष्ठा vxge_hw_legacy_reg	__iomem *legacy_reg;
	काष्ठा vxge_hw_toc_reg		__iomem *toc_reg;
	काष्ठा vxge_hw_common_reg	__iomem *common_reg;
	काष्ठा vxge_hw_mrpcim_reg	__iomem *mrpcim_reg;
	काष्ठा vxge_hw_srpcim_reg	__iomem *srpcim_reg \
					[VXGE_HW_TITAN_SRPCIM_REG_SPACES];
	काष्ठा vxge_hw_vpmgmt_reg	__iomem *vpmgmt_reg \
					[VXGE_HW_TITAN_VPMGMT_REG_SPACES];
	काष्ठा vxge_hw_vpath_reg	__iomem *vpath_reg \
					[VXGE_HW_TITAN_VPATH_REG_SPACES];
	u8				__iomem *kdfc;
	u8				__iomem *usdc;
	काष्ठा __vxge_hw_भवpath	भव_paths \
					[VXGE_HW_MAX_VIRTUAL_PATHS];
	u64				vpath_assignments;
	u64				vpaths_deployed;
	u32				first_vp_id;
	u64				tim_पूर्णांक_mask0[4];
	u32				tim_पूर्णांक_mask1[4];

	काष्ठा __vxge_hw_blockpool	block_pool;
	काष्ठा vxge_hw_device_stats	stats;
	u32				debug_module_mask;
	u32				debug_level;
	u32				level_err;
	u32				level_trace;
	u16 eprom_versions[VXGE_HW_MAX_ROM_IMAGES];
पूर्ण;

#घोषणा VXGE_HW_INFO_LEN	64
/**
 * काष्ठा vxge_hw_device_hw_info - Device inक्रमmation
 * @host_type: Host Type
 * @func_id: Function Id
 * @vpath_mask: vpath bit mask
 * @fw_version: Firmware version
 * @fw_date: Firmware Date
 * @flash_version: Firmware version
 * @flash_date: Firmware Date
 * @mac_addrs: Mac addresses क्रम each vpath
 * @mac_addr_masks: Mac address masks क्रम each vpath
 *
 * Returns the vpath mask that has the bits set क्रम each vpath allocated
 * क्रम the driver and the first mac address क्रम each vpath
 */
काष्ठा vxge_hw_device_hw_info अणु
	u32		host_type;
#घोषणा VXGE_HW_NO_MR_NO_SR_NORMAL_FUNCTION			0
#घोषणा VXGE_HW_MR_NO_SR_VH0_BASE_FUNCTION			1
#घोषणा VXGE_HW_NO_MR_SR_VH0_FUNCTION0				2
#घोषणा VXGE_HW_NO_MR_SR_VH0_VIRTUAL_FUNCTION			3
#घोषणा VXGE_HW_MR_SR_VH0_INVALID_CONFIG			4
#घोषणा VXGE_HW_SR_VH_FUNCTION0					5
#घोषणा VXGE_HW_SR_VH_VIRTUAL_FUNCTION				6
#घोषणा VXGE_HW_VH_NORMAL_FUNCTION				7
	u64		function_mode;
#घोषणा VXGE_HW_FUNCTION_MODE_SINGLE_FUNCTION			0
#घोषणा VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION			1
#घोषणा VXGE_HW_FUNCTION_MODE_SRIOV				2
#घोषणा VXGE_HW_FUNCTION_MODE_MRIOV				3
#घोषणा VXGE_HW_FUNCTION_MODE_MRIOV_8				4
#घोषणा VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION_17			5
#घोषणा VXGE_HW_FUNCTION_MODE_SRIOV_8				6
#घोषणा VXGE_HW_FUNCTION_MODE_SRIOV_4				7
#घोषणा VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION_2			8
#घोषणा VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION_4			9
#घोषणा VXGE_HW_FUNCTION_MODE_MRIOV_4				10

	u32		func_id;
	u64		vpath_mask;
	काष्ठा vxge_hw_device_version fw_version;
	काष्ठा vxge_hw_device_date    fw_date;
	काष्ठा vxge_hw_device_version flash_version;
	काष्ठा vxge_hw_device_date    flash_date;
	u8		serial_number[VXGE_HW_INFO_LEN];
	u8		part_number[VXGE_HW_INFO_LEN];
	u8		product_desc[VXGE_HW_INFO_LEN];
	u8 mac_addrs[VXGE_HW_MAX_VIRTUAL_PATHS][ETH_ALEN];
	u8 mac_addr_masks[VXGE_HW_MAX_VIRTUAL_PATHS][ETH_ALEN];
पूर्ण;

/**
 * काष्ठा vxge_hw_device_attr - Device memory spaces.
 * @bar0: BAR0 भव address.
 * @pdev: PCI device object.
 *
 * Device memory spaces. Includes configuration, BAR0 etc. per device
 * mapped memories. Also, includes a poपूर्णांकer to OS-specअगरic PCI device object.
 */
काष्ठा vxge_hw_device_attr अणु
	व्योम __iomem		*bar0;
	काष्ठा pci_dev 		*pdev;
	स्थिर काष्ठा vxge_hw_uld_cbs *uld_callbacks;
पूर्ण;

#घोषणा VXGE_HW_DEVICE_LINK_STATE_SET(hldev, ls)	(hldev->link_state = ls)

#घोषणा VXGE_HW_DEVICE_TIM_INT_MASK_SET(m0, m1, i) अणु	\
	अगर (i < 16) अणु				\
		m0[0] |= vxge_vBIT(0x8, (i*4), 4);	\
		m0[1] |= vxge_vBIT(0x4, (i*4), 4);	\
	पूर्ण			       		\
	अन्यथा अणु					\
		m1[0] = 0x80000000;		\
		m1[1] = 0x40000000;		\
	पूर्ण					\
पूर्ण

#घोषणा VXGE_HW_DEVICE_TIM_INT_MASK_RESET(m0, m1, i) अणु	\
	अगर (i < 16) अणु					\
		m0[0] &= ~vxge_vBIT(0x8, (i*4), 4);		\
		m0[1] &= ~vxge_vBIT(0x4, (i*4), 4);		\
	पूर्ण						\
	अन्यथा अणु						\
		m1[0] = 0;				\
		m1[1] = 0;				\
	पूर्ण						\
पूर्ण

#घोषणा VXGE_HW_DEVICE_STATS_PIO_READ(loc, offset) अणु		\
	status = vxge_hw_mrpcim_stats_access(hldev, \
				VXGE_HW_STATS_OP_READ, \
				loc, \
				offset, \
				&val64);			\
	अगर (status != VXGE_HW_OK)				\
		वापस status;						\
पूर्ण

/*
 * काष्ठा __vxge_hw_ring - Ring channel.
 * @channel: Channel "base" of this ring, the common part of all HW
 *           channels.
 * @mempool: Memory pool, the pool from which descriptors get allocated.
 *           (See vxge_hw_mm.h).
 * @config: Ring configuration, part of device configuration
 *          (see काष्ठा vxge_hw_device_configअणुपूर्ण).
 * @ring_length: Length of the ring
 * @buffer_mode: 1, 3, or 5. The value specअगरies a receive buffer mode,
 *          as per Titan User Guide.
 * @rxd_size: RxD sizes क्रम 1-, 3- or 5- buffer modes. As per Titan spec,
 *            1-buffer mode descriptor is 32 byte दीर्घ, etc.
 * @rxd_priv_size: Per RxD size reserved (by HW) क्रम driver to keep
 *                 per-descriptor data (e.g., DMA handle क्रम Solaris)
 * @per_rxd_space: Per rxd space requested by driver
 * @rxds_per_block: Number of descriptors per hardware-defined RxD
 *                  block. Depends on the (1-, 3-, 5-) buffer mode.
 * @rxdblock_priv_size: Reserved at the end of each RxD block. HW पूर्णांकernal
 *                      usage. Not to confuse with @rxd_priv_size.
 * @cmpl_cnt: Completion counter. Is reset to zero upon entering the ISR.
 * @callback: Channel completion callback. HW invokes the callback when there
 *            are new completions on that channel. In many implementations
 *            the @callback executes in the hw पूर्णांकerrupt context.
 * @rxd_init: Channel's descriptor-initialize callback.
 *            See vxge_hw_ring_rxd_init_fअणुपूर्ण.
 *            If not शून्य, HW invokes the callback when खोलोing
 *            the ring.
 * @rxd_term: Channel's descriptor-terminate callback. If not शून्य,
 *          HW invokes the callback when closing the corresponding channel.
 *          See also vxge_hw_channel_rxd_term_fअणुपूर्ण.
 * @stats: Statistics क्रम ring
 * Ring channel.
 *
 * Note: The काष्ठाure is cache line aligned to better utilize
 *       CPU cache perक्रमmance.
 */
काष्ठा __vxge_hw_ring अणु
	काष्ठा __vxge_hw_channel		channel;
	काष्ठा vxge_hw_mempool			*mempool;
	काष्ठा vxge_hw_vpath_reg		__iomem	*vp_reg;
	काष्ठा vxge_hw_common_reg		__iomem	*common_reg;
	u32					ring_length;
	u32					buffer_mode;
	u32					rxd_size;
	u32					rxd_priv_size;
	u32					per_rxd_space;
	u32					rxds_per_block;
	u32					rxdblock_priv_size;
	u32					cmpl_cnt;
	u32					vp_id;
	u32					करोorbell_cnt;
	u32					total_db_cnt;
	u64					rxds_limit;
	u32					rसमयr;
	u64					tim_rti_cfg1_saved;
	u64					tim_rti_cfg3_saved;

	क्रमागत vxge_hw_status (*callback)(
			काष्ठा __vxge_hw_ring *ringh,
			व्योम *rxdh,
			u8 t_code,
			व्योम *userdata);

	क्रमागत vxge_hw_status (*rxd_init)(
			व्योम *rxdh,
			व्योम *userdata);

	व्योम (*rxd_term)(
			व्योम *rxdh,
			क्रमागत vxge_hw_rxd_state state,
			व्योम *userdata);

	काष्ठा vxge_hw_vpath_stats_sw_ring_info *stats	____cacheline_aligned;
	काष्ठा vxge_hw_ring_config		*config;
पूर्ण ____cacheline_aligned;

/**
 * क्रमागत क्रमागत vxge_hw_txdl_state - Descriptor (TXDL) state.
 * @VXGE_HW_TXDL_STATE_NONE: Invalid state.
 * @VXGE_HW_TXDL_STATE_AVAIL: Descriptor is available क्रम reservation.
 * @VXGE_HW_TXDL_STATE_POSTED: Descriptor is posted क्रम processing by the
 * device.
 * @VXGE_HW_TXDL_STATE_FREED: Descriptor is मुक्त and can be reused क्रम
 * filling-in and posting later.
 *
 * Titan/HW descriptor states.
 *
 */
क्रमागत vxge_hw_txdl_state अणु
	VXGE_HW_TXDL_STATE_NONE	= 0,
	VXGE_HW_TXDL_STATE_AVAIL	= 1,
	VXGE_HW_TXDL_STATE_POSTED	= 2,
	VXGE_HW_TXDL_STATE_FREED	= 3
पूर्ण;
/*
 * काष्ठा __vxge_hw_fअगरo - Fअगरo.
 * @channel: Channel "base" of this fअगरo, the common part of all HW
 *             channels.
 * @mempool: Memory pool, from which descriptors get allocated.
 * @config: Fअगरo configuration, part of device configuration
 *             (see काष्ठा vxge_hw_device_configअणुपूर्ण).
 * @पूर्णांकerrupt_type: Interrupt type to be used
 * @no_snoop_bits: See काष्ठा vxge_hw_fअगरo_configअणुपूर्ण.
 * @txdl_per_memblock: Number of TxDLs (TxD lists) per memblock.
 *             on TxDL please refer to Titan UG.
 * @txdl_size: Configured TxDL size (i.e., number of TxDs in a list), plus
 *             per-TxDL HW निजी space (काष्ठा __vxge_hw_fअगरo_txdl_priv).
 * @priv_size: Per-Tx descriptor space reserved क्रम driver
 *             usage.
 * @per_txdl_space: Per txdl निजी space क्रम the driver
 * @callback: Fअगरo completion callback. HW invokes the callback when there
 *             are new completions on that fअगरo. In many implementations
 *             the @callback executes in the hw पूर्णांकerrupt context.
 * @txdl_term: Fअगरo's descriptor-terminate callback. If not शून्य,
 *             HW invokes the callback when closing the corresponding fअगरo.
 *             See also vxge_hw_fअगरo_txdl_term_fअणुपूर्ण.
 * @stats: Statistics of this fअगरo
 *
 * Fअगरo channel.
 * Note: The काष्ठाure is cache line aligned.
 */
काष्ठा __vxge_hw_fअगरo अणु
	काष्ठा __vxge_hw_channel		channel;
	काष्ठा vxge_hw_mempool			*mempool;
	काष्ठा vxge_hw_fअगरo_config		*config;
	काष्ठा vxge_hw_vpath_reg		__iomem *vp_reg;
	काष्ठा __vxge_hw_non_offload_db_wrapper	__iomem *nofl_db;
	u64					पूर्णांकerrupt_type;
	u32					no_snoop_bits;
	u32					txdl_per_memblock;
	u32					txdl_size;
	u32					priv_size;
	u32					per_txdl_space;
	u32					vp_id;
	u32					tx_पूर्णांकr_num;
	u32					rसमयr;
	u64					tim_tti_cfg1_saved;
	u64					tim_tti_cfg3_saved;

	क्रमागत vxge_hw_status (*callback)(
			काष्ठा __vxge_hw_fअगरo *fअगरo_handle,
			व्योम *txdlh,
			क्रमागत vxge_hw_fअगरo_tcode t_code,
			व्योम *userdata,
			काष्ठा sk_buff ***skb_ptr,
			पूर्णांक nr_skb,
			पूर्णांक *more);

	व्योम (*txdl_term)(
			व्योम *txdlh,
			क्रमागत vxge_hw_txdl_state state,
			व्योम *userdata);

	काष्ठा vxge_hw_vpath_stats_sw_fअगरo_info *stats ____cacheline_aligned;
पूर्ण ____cacheline_aligned;

/*
 * काष्ठा __vxge_hw_fअगरo_txdl_priv - Transmit descriptor HW-निजी data.
 * @dma_addr: DMA (mapped) address of _this_ descriptor.
 * @dma_handle: DMA handle used to map the descriptor onto device.
 * @dma_offset: Descriptor's offset in the memory block. HW allocates
 *	 descriptors in memory blocks (see काष्ठा vxge_hw_fअगरo_configअणुपूर्ण)
 *             Each memblock is a contiguous block of DMA-able memory.
 * @frags: Total number of fragments (that is, contiguous data buffers)
 * carried by this TxDL.
 * @align_vaddr_start: Aligned भव address start
 * @align_vaddr: Virtual address of the per-TxDL area in memory used क्रम
 *             alignement. Used to place one or more mis-aligned fragments
 * @align_dma_addr: DMA address translated from the @align_vaddr.
 * @align_dma_handle: DMA handle that corresponds to @align_dma_addr.
 * @align_dma_acch: DMA access handle corresponds to @align_dma_addr.
 * @align_dma_offset: The current offset पूर्णांकo the @align_vaddr area.
 * Grows जबतक filling the descriptor, माला_लो reset.
 * @align_used_frags: Number of fragments used.
 * @alloc_frags: Total number of fragments allocated.
 * @unused: TODO
 * @next_txdl_priv: (TODO).
 * @first_txdp: (TODO).
 * @linked_txdl_priv: Poपूर्णांकer to any linked TxDL क्रम creating contiguous
 *             TxDL list.
 * @txdlh: Corresponding txdlh to this TxDL.
 * @memblock: Poपूर्णांकer to the TxDL memory block or memory page.
 *             on the next send operation.
 * @dma_object: DMA address and handle of the memory block that contains
 *             the descriptor. This member is used only in the "checked"
 *             version of the HW (to enक्रमce certain निश्चितions);
 *             otherwise it माला_लो compiled out.
 * @allocated: True अगर the descriptor is reserved, 0 otherwise. Internal usage.
 *
 * Per-transmit decsriptor HW-निजी data. HW uses the space to keep DMA
 * inक्रमmation associated with the descriptor. Note that driver can ask HW
 * to allocate additional per-descriptor space क्रम its own (driver-specअगरic)
 * purposes.
 *
 * See also: काष्ठा vxge_hw_ring_rxd_privअणुपूर्ण.
 */
काष्ठा __vxge_hw_fअगरo_txdl_priv अणु
	dma_addr_t		dma_addr;
	काष्ठा pci_dev	*dma_handle;
	सूचक_भेद_प्रकार		dma_offset;
	u32				frags;
	u8				*align_vaddr_start;
	u8				*align_vaddr;
	dma_addr_t		align_dma_addr;
	काष्ठा pci_dev 	*align_dma_handle;
	काष्ठा pci_dev	*align_dma_acch;
	सूचक_भेद_प्रकार		align_dma_offset;
	u32				align_used_frags;
	u32				alloc_frags;
	u32				unused;
	काष्ठा __vxge_hw_fअगरo_txdl_priv	*next_txdl_priv;
	काष्ठा vxge_hw_fअगरo_txd		*first_txdp;
	व्योम			*memblock;
पूर्ण;

/*
 * काष्ठा __vxge_hw_non_offload_db_wrapper - Non-offload Doorbell Wrapper
 * @control_0: Bits 0 to 7 - Doorbell type.
 *             Bits 8 to 31 - Reserved.
 *             Bits 32 to 39 - The highest TxD in this TxDL.
 *             Bits 40 to 47 - Reserved.
	*	       Bits 48 to 55 - Reserved.
 *             Bits 56 to 63 - No snoop flags.
 * @txdl_ptr:  The starting location of the TxDL in host memory.
 *
 * Created by the host and written to the adapter via PIO to a Kernel Doorbell
 * FIFO. All non-offload करोorbell wrapper fields must be written by the host as
 * part of a करोorbell ग_लिखो. Consumed by the adapter but is not written by the
 * adapter.
 */
काष्ठा __vxge_hw_non_offload_db_wrapper अणु
	u64		control_0;
#घोषणा	VXGE_HW_NODBW_GET_TYPE(ctrl0)			vxge_bVALn(ctrl0, 0, 8)
#घोषणा VXGE_HW_NODBW_TYPE(val) vxge_vBIT(val, 0, 8)
#घोषणा	VXGE_HW_NODBW_TYPE_NODBW				0

#घोषणा	VXGE_HW_NODBW_GET_LAST_TXD_NUMBER(ctrl0)	vxge_bVALn(ctrl0, 32, 8)
#घोषणा VXGE_HW_NODBW_LAST_TXD_NUMBER(val) vxge_vBIT(val, 32, 8)

#घोषणा	VXGE_HW_NODBW_GET_NO_SNOOP(ctrl0)		vxge_bVALn(ctrl0, 56, 8)
#घोषणा VXGE_HW_NODBW_LIST_NO_SNOOP(val) vxge_vBIT(val, 56, 8)
#घोषणा	VXGE_HW_NODBW_LIST_NO_SNOOP_TXD_READ_TXD0_WRITE		0x2
#घोषणा	VXGE_HW_NODBW_LIST_NO_SNOOP_TX_FRAME_DATA_READ		0x1

	u64		txdl_ptr;
पूर्ण;

/*
 * TX Descriptor
 */

/**
 * काष्ठा vxge_hw_fअगरo_txd - Transmit Descriptor
 * @control_0: Bits 0 to 6 - Reserved.
 *             Bit 7 - List Ownership. This field should be initialized
 *             to '1' by the driver beक्रमe the transmit list poपूर्णांकer is
 *             written to the adapter. This field will be set to '0' by the
 *             adapter once it has completed transmitting the frame or frames in
 *             the list. Note - This field is only valid in TxD0. Additionally,
 *             क्रम multi-list sequences, the driver should not release any
 *             buffers until the ownership of the last list in the multi-list
 *             sequence has been वापसed to the host.
 *             Bits 8 to 11 - Reserved
 *             Bits 12 to 15 - Transfer_Code. This field is only valid in
 *             TxD0. It is used to describe the status of the transmit data
 *             buffer transfer. This field is always overwritten by the
 *             adapter, so this field may be initialized to any value.
 *             Bits 16 to 17 - Host steering. This field allows the host to
 *             override the selection of the physical transmit port.
 *             Attention:
 *             Normal sounds as अगर learned from the चयन rather than from
 *             the aggregation algorythms.
 *             00: Normal. Use Destination/MAC Address
 *             lookup to determine the transmit port.
 *             01: Send on physical Port1.
 *             10: Send on physical Port0.
 *	       11: Send on both ports.
 *             Bits 18 to 21 - Reserved
 *             Bits 22 to 23 - Gather_Code. This field is set by the host and
 *             is used to describe how inभागidual buffers comprise a frame.
 *             10: First descriptor of a frame.
 *             00: Middle of a multi-descriptor frame.
 *             01: Last descriptor of a frame.
 *             11: First and last descriptor of a frame (the entire frame
 *             resides in a single buffer).
 *             For multi-descriptor frames, the only valid gather code sequence
 *             is अणु10, [00], 01पूर्ण. In other words, the descriptors must be placed
 *             in the list in the correct order.
 *             Bits 24 to 27 - Reserved
 *             Bits 28 to 29 - LSO_Frm_Encap. LSO Frame Encapsulation
 *             definition. Only valid in TxD0. This field allows the host to
 *             indicate the Ethernet encapsulation of an outbound LSO packet.
 *             00 - classic mode (best guess)
 *             01 - LLC
 *             10 - SNAP
 *             11 - DIX
 *             If "classic mode" is selected, the adapter will attempt to
 *             decode the frame's Ethernet encapsulation by examining the L/T
 *             field as follows:
 *             <= 0x05DC LLC/SNAP encoding; must examine DSAP/SSAP to determine
 *             अगर packet is IPv4 or IPv6.
 *             0x8870 Jumbo-SNAP encoding.
 *             0x0800 IPv4 DIX encoding
 *             0x86DD IPv6 DIX encoding
 *             others illegal encapsulation
 *             Bits 30 - LSO_ Flag. Large Send Offload (LSO) flag.
 *             Set to 1 to perक्रमm segmentation offload क्रम TCP/UDP.
 *             This field is valid only in TxD0.
 *             Bits 31 to 33 - Reserved.
 *             Bits 34 to 47 - LSO_MSS. TCP/UDP LSO Maximum Segment Size
 *             This field is meaningful only when LSO_Control is non-zero.
 *             When LSO_Control is set to TCP_LSO, the single (possibly large)
 *             TCP segment described by this TxDL will be sent as a series of
 *             TCP segments each of which contains no more than LSO_MSS
 *             payload bytes.
 *             When LSO_Control is set to UDP_LSO, the single (possibly large)
 *             UDP datagram described by this TxDL will be sent as a series of
 *             UDP datagrams each of which contains no more than LSO_MSS
 *             payload bytes.
 *             All outgoing frames from this TxDL will have LSO_MSS bytes of UDP
 *             or TCP payload, with the exception of the last, which will have
 *             <= LSO_MSS bytes of payload.
 *             Bits 48 to 63 - Buffer_Size. Number of valid bytes in the
 *             buffer to be पढ़ो by the adapter. This field is written by the
 *             host. A value of 0 is illegal.
 *	       Bits 32 to 63 - This value is written by the adapter upon
 *	       completion of a UDP or TCP LSO operation and indicates the number
 *             of UDP or TCP payload bytes that were transmitted. 0x0000 will be
 *             वापसed क्रम any non-LSO operation.
 * @control_1: Bits 0 to 4 - Reserved.
 *             Bit 5 - Tx_CKO_IPv4 Set to a '1' to enable IPv4 header checksum
 *             offload. This field is only valid in the first TxD of a frame.
 *             Bit 6 - Tx_CKO_TCP Set to a '1' to enable TCP checksum offload.
 *             This field is only valid in the first TxD of a frame (the TxD's
 *             gather code must be 10 or 11). The driver should only set this
 *             bit अगर it can guarantee that TCP is present.
 *             Bit 7 - Tx_CKO_UDP Set to a '1' to enable UDP checksum offload.
 *             This field is only valid in the first TxD of a frame (the TxD's
 *             gather code must be 10 or 11). The driver should only set this
 *             bit अगर it can guarantee that UDP is present.
 *             Bits 8 to 14 - Reserved.
 *             Bit 15 - Tx_VLAN_Enable VLAN tag insertion flag. Set to a '1' to
 *             inकाष्ठा the adapter to insert the VLAN tag specअगरied by the
 *             Tx_VLAN_Tag field. This field is only valid in the first TxD of
 *             a frame.
 *             Bits 16 to 31 - Tx_VLAN_Tag. Variable portion of the VLAN tag
 *             to be inserted पूर्णांकo the frame by the adapter (the first two bytes
 *             of a VLAN tag are always 0x8100). This field is only valid अगर the
 *             Tx_VLAN_Enable field is set to '1'.
 *             Bits 32 to 33 - Reserved.
 *             Bits 34 to 39 - Tx_Int_Number. Indicates which Tx पूर्णांकerrupt
 *             number the frame associated with. This field is written by the
 *             host. It is only valid in the first TxD of a frame.
 *             Bits 40 to 42 - Reserved.
 *             Bit 43 - Set to 1 to exclude the frame from bandwidth metering
 *             functions. This field is valid only in the first TxD
 *             of a frame.
 *             Bits 44 to 45 - Reserved.
 *             Bit 46 - Tx_Int_Per_List Set to a '1' to inकाष्ठा the adapter to
 *             generate an पूर्णांकerrupt as soon as all of the frames in the list
 *             have been transmitted. In order to have per-frame पूर्णांकerrupts,
 *             the driver should place a maximum of one frame per list. This
 *             field is only valid in the first TxD of a frame.
 *             Bit 47 - Tx_Int_Utilization Set to a '1' to inकाष्ठा the adapter
 *             to count the frame toward the utilization पूर्णांकerrupt specअगरied in
 *             the Tx_Int_Number field. This field is only valid in the first
 *             TxD of a frame.
 *             Bits 48 to 63 - Reserved.
 * @buffer_poपूर्णांकer: Buffer start address.
 * @host_control: Host_Control.Opaque 64bit data stored by driver inside the
 *            Titan descriptor prior to posting the latter on the fअगरo
 *            via vxge_hw_fअगरo_txdl_post().The %host_control is वापसed as is
 *            to the driver with each completed descriptor.
 *
 * Transmit descriptor (TxD).Fअगरo descriptor contains configured number
 * (list) of TxDs. * For more details please refer to Titan User Guide,
 * Section 5.4.2 "Transmit Descriptor (TxD) Format".
 */
काष्ठा vxge_hw_fअगरo_txd अणु
	u64 control_0;
#घोषणा VXGE_HW_FIFO_TXD_LIST_OWN_ADAPTER		vxge_mBIT(7)

#घोषणा VXGE_HW_FIFO_TXD_T_CODE_GET(ctrl0)		vxge_bVALn(ctrl0, 12, 4)
#घोषणा VXGE_HW_FIFO_TXD_T_CODE(val) 			vxge_vBIT(val, 12, 4)
#घोषणा VXGE_HW_FIFO_TXD_T_CODE_UNUSED		VXGE_HW_FIFO_T_CODE_UNUSED


#घोषणा VXGE_HW_FIFO_TXD_GATHER_CODE(val) 		vxge_vBIT(val, 22, 2)
#घोषणा VXGE_HW_FIFO_TXD_GATHER_CODE_FIRST	VXGE_HW_FIFO_GATHER_CODE_FIRST
#घोषणा VXGE_HW_FIFO_TXD_GATHER_CODE_LAST	VXGE_HW_FIFO_GATHER_CODE_LAST


#घोषणा VXGE_HW_FIFO_TXD_LSO_EN				vxge_mBIT(30)

#घोषणा VXGE_HW_FIFO_TXD_LSO_MSS(val) 			vxge_vBIT(val, 34, 14)

#घोषणा VXGE_HW_FIFO_TXD_BUFFER_SIZE(val) 		vxge_vBIT(val, 48, 16)

	u64 control_1;
#घोषणा VXGE_HW_FIFO_TXD_TX_CKO_IPV4_EN			vxge_mBIT(5)
#घोषणा VXGE_HW_FIFO_TXD_TX_CKO_TCP_EN			vxge_mBIT(6)
#घोषणा VXGE_HW_FIFO_TXD_TX_CKO_UDP_EN			vxge_mBIT(7)
#घोषणा VXGE_HW_FIFO_TXD_VLAN_ENABLE			vxge_mBIT(15)

#घोषणा VXGE_HW_FIFO_TXD_VLAN_TAG(val) 			vxge_vBIT(val, 16, 16)

#घोषणा VXGE_HW_FIFO_TXD_INT_NUMBER(val) 		vxge_vBIT(val, 34, 6)

#घोषणा VXGE_HW_FIFO_TXD_INT_TYPE_PER_LIST		vxge_mBIT(46)
#घोषणा VXGE_HW_FIFO_TXD_INT_TYPE_UTILZ			vxge_mBIT(47)

	u64 buffer_poपूर्णांकer;

	u64 host_control;
पूर्ण;

/**
 * काष्ठा vxge_hw_ring_rxd_1 - One buffer mode RxD क्रम ring
 * @host_control: This field is exclusively क्रम host use and is "readonly"
 *             from the adapter's perspective.
 * @control_0:Bits 0 to 6 - RTH_Bucket get
 *	      Bit 7 - Own Descriptor ownership bit. This bit is set to 1
 *            by the host, and is set to 0 by the adapter.
 *	      0 - Host owns RxD and buffer.
 *	      1 - The adapter owns RxD and buffer.
 *	      Bit 8 - Fast_Path_Eligible When set, indicates that the
 *            received frame meets all of the criteria क्रम fast path processing.
 *            The required criteria are as follows:
 *            !SYN &
 *            (Transfer_Code == "Transfer OK") &
 *            (!Is_IP_Fragment) &
 *            ((Is_IPv4 & computed_L3_checksum == 0xFFFF) |
 *            (Is_IPv6)) &
 *            ((Is_TCP & computed_L4_checksum == 0xFFFF) |
 *            (Is_UDP & (computed_L4_checksum == 0xFFFF |
 *            computed _L4_checksum == 0x0000)))
 *            (same meaning क्रम all RxD buffer modes)
 *	      Bit 9 - L3 Checksum Correct
 *	      Bit 10 - L4 Checksum Correct
 *	      Bit 11 - Reserved
 *	      Bit 12 to 15 - This field is written by the adapter. It is
 *            used to report the status of the frame transfer to the host.
 *	      0x0 - Transfer OK
 *	      0x4 - RDA Failure During Transfer
 *	      0x5 - Unparseable Packet, such as unknown IPv6 header.
 *	      0x6 - Frame पूर्णांकegrity error (FCS or ECC).
 *	      0x7 - Buffer Size Error. The provided buffer(s) were not
 *                  appropriately sized and data loss occurred.
 *	      0x8 - Internal ECC Error. RxD corrupted.
 *	      0x9 - IPv4 Checksum error
 *	      0xA - TCP/UDP Checksum error
 *	      0xF - Unknown Error or Multiple Error. Indicates an
 *               unknown problem or that more than one of transfer codes is set.
 *	      Bit 16 - SYN The adapter sets this field to indicate that
 *                the incoming frame contained a TCP segment with its SYN bit
 *	          set and its ACK bit NOT set. (same meaning क्रम all RxD buffer
 *                modes)
 *	      Bit 17 - Is ICMP
 *	      Bit 18 - RTH_SPDM_HIT Set to 1 अगर there was a match in the
 *                Socket Pair Direct Match Table and the frame was steered based
 *                on SPDM.
 *	      Bit 19 - RTH_IT_HIT Set to 1 अगर there was a match in the
 *            Indirection Table and the frame was steered based on hash
 *            indirection.
 *	      Bit 20 to 23 - RTH_HASH_TYPE Indicates the function (hash
 *	          type) that was used to calculate the hash.
 *	      Bit 19 - IS_VLAN Set to '1' अगर the frame was/is VLAN
 *	          tagged.
 *	      Bit 25 to 26 - ETHER_ENCAP Reflects the Ethernet encapsulation
 *                of the received frame.
 *	      0x0 - Ethernet DIX
 *	      0x1 - LLC
 *	      0x2 - SNAP (includes Jumbo-SNAP)
 *	      0x3 - IPX
 *	      Bit 27 - IS_IPV4 Set to '1' अगर the frame contains an IPv4	packet.
 *	      Bit 28 - IS_IPV6 Set to '1' अगर the frame contains an IPv6 packet.
 *	      Bit 29 - IS_IP_FRAG Set to '1' अगर the frame contains a fragmented
 *            IP packet.
 *	      Bit 30 - IS_TCP Set to '1' अगर the frame contains a TCP segment.
 *	      Bit 31 - IS_UDP Set to '1' अगर the frame contains a UDP message.
 *	      Bit 32 to 47 - L3_Checksum[0:15] The IPv4 checksum value 	that
 *            arrived with the frame. If the resulting computed IPv4 header
 *            checksum क्रम the frame did not produce the expected 0xFFFF value,
 *            then the transfer code would be set to 0x9.
 *	      Bit 48 to 63 - L4_Checksum[0:15] The TCP/UDP checksum value that
 *            arrived with the frame. If the resulting computed TCP/UDP checksum
 *            क्रम the frame did not produce the expected 0xFFFF value, then the
 *            transfer code would be set to 0xA.
 * @control_1:Bits 0 to 1 - Reserved
 *            Bits 2 to 15 - Buffer0_Size.This field is set by the host and
 *            eventually overwritten by the adapter. The host ग_लिखोs the
 *            available buffer size in bytes when it passes the descriptor to
 *            the adapter. When a frame is delivered the host, the adapter
 *            populates this field with the number of bytes written पूर्णांकo the
 *            buffer. The largest supported buffer is 16, 383 bytes.
 *	      Bit 16 to 47 - RTH Hash Value 32-bit RTH hash value. Only valid अगर
 *	      RTH_HASH_TYPE (Control_0, bits 20:23) is nonzero.
 *	      Bit 48 to 63 - VLAN_Tag[0:15] The contents of the variable portion
 *            of the VLAN tag, अगर one was detected by the adapter. This field is
 *            populated even अगर VLAN-tag stripping is enabled.
 * @buffer0_ptr: Poपूर्णांकer to buffer. This field is populated by the driver.
 *
 * One buffer mode RxD क्रम ring काष्ठाure
 */
काष्ठा vxge_hw_ring_rxd_1 अणु
	u64 host_control;
	u64 control_0;
#घोषणा VXGE_HW_RING_RXD_RTH_BUCKET_GET(ctrl0)		vxge_bVALn(ctrl0, 0, 7)

#घोषणा VXGE_HW_RING_RXD_LIST_OWN_ADAPTER		vxge_mBIT(7)

#घोषणा VXGE_HW_RING_RXD_FAST_PATH_ELIGIBLE_GET(ctrl0)	vxge_bVALn(ctrl0, 8, 1)

#घोषणा VXGE_HW_RING_RXD_L3_CKSUM_CORRECT_GET(ctrl0)	vxge_bVALn(ctrl0, 9, 1)

#घोषणा VXGE_HW_RING_RXD_L4_CKSUM_CORRECT_GET(ctrl0)	vxge_bVALn(ctrl0, 10, 1)

#घोषणा VXGE_HW_RING_RXD_T_CODE_GET(ctrl0)		vxge_bVALn(ctrl0, 12, 4)
#घोषणा VXGE_HW_RING_RXD_T_CODE(val) 			vxge_vBIT(val, 12, 4)

#घोषणा VXGE_HW_RING_RXD_T_CODE_UNUSED		VXGE_HW_RING_T_CODE_UNUSED

#घोषणा VXGE_HW_RING_RXD_SYN_GET(ctrl0)		vxge_bVALn(ctrl0, 16, 1)

#घोषणा VXGE_HW_RING_RXD_IS_ICMP_GET(ctrl0)		vxge_bVALn(ctrl0, 17, 1)

#घोषणा VXGE_HW_RING_RXD_RTH_SPDM_HIT_GET(ctrl0)	vxge_bVALn(ctrl0, 18, 1)

#घोषणा VXGE_HW_RING_RXD_RTH_IT_HIT_GET(ctrl0)		vxge_bVALn(ctrl0, 19, 1)

#घोषणा VXGE_HW_RING_RXD_RTH_HASH_TYPE_GET(ctrl0)	vxge_bVALn(ctrl0, 20, 4)

#घोषणा VXGE_HW_RING_RXD_IS_VLAN_GET(ctrl0)		vxge_bVALn(ctrl0, 24, 1)

#घोषणा VXGE_HW_RING_RXD_ETHER_ENCAP_GET(ctrl0)		vxge_bVALn(ctrl0, 25, 2)

#घोषणा VXGE_HW_RING_RXD_FRAME_PROTO_GET(ctrl0)		vxge_bVALn(ctrl0, 27, 5)

#घोषणा VXGE_HW_RING_RXD_L3_CKSUM_GET(ctrl0)	vxge_bVALn(ctrl0, 32, 16)

#घोषणा VXGE_HW_RING_RXD_L4_CKSUM_GET(ctrl0)	vxge_bVALn(ctrl0, 48, 16)

	u64 control_1;

#घोषणा VXGE_HW_RING_RXD_1_BUFFER0_SIZE_GET(ctrl1)	vxge_bVALn(ctrl1, 2, 14)
#घोषणा VXGE_HW_RING_RXD_1_BUFFER0_SIZE(val) vxge_vBIT(val, 2, 14)
#घोषणा VXGE_HW_RING_RXD_1_BUFFER0_SIZE_MASK		vxge_vBIT(0x3FFF, 2, 14)

#घोषणा VXGE_HW_RING_RXD_1_RTH_HASH_VAL_GET(ctrl1)    vxge_bVALn(ctrl1, 16, 32)

#घोषणा VXGE_HW_RING_RXD_VLAN_TAG_GET(ctrl1)	vxge_bVALn(ctrl1, 48, 16)

	u64 buffer0_ptr;
पूर्ण;

क्रमागत vxge_hw_rth_algoriपंचांगs अणु
	RTH_ALG_JENKINS = 0,
	RTH_ALG_MS_RSS	= 1,
	RTH_ALG_CRC32C	= 2
पूर्ण;

/**
 * काष्ठा vxge_hw_rth_hash_types - RTH hash types.
 * @hash_type_tcpipv4_en: Enables RTH field type HashTypeTcpIPv4
 * @hash_type_ipv4_en: Enables RTH field type HashTypeIPv4
 * @hash_type_tcpipv6_en: Enables RTH field type HashTypeTcpIPv6
 * @hash_type_ipv6_en: Enables RTH field type HashTypeIPv6
 * @hash_type_tcpipv6ex_en: Enables RTH field type HashTypeTcpIPv6Ex
 * @hash_type_ipv6ex_en: Enables RTH field type HashTypeIPv6Ex
 *
 * Used to pass RTH hash types to rts_rts_set.
 *
 * See also: vxge_hw_vpath_rts_rth_set(), vxge_hw_vpath_rts_rth_get().
 */
काष्ठा vxge_hw_rth_hash_types अणु
	u8 hash_type_tcpipv4_en:1,
	   hash_type_ipv4_en:1,
	   hash_type_tcpipv6_en:1,
	   hash_type_ipv6_en:1,
	   hash_type_tcpipv6ex_en:1,
	   hash_type_ipv6ex_en:1;
पूर्ण;

व्योम vxge_hw_device_debug_set(
	काष्ठा __vxge_hw_device *devh,
	क्रमागत vxge_debug_level level,
	u32 mask);

u32
vxge_hw_device_error_level_get(काष्ठा __vxge_hw_device *devh);

u32
vxge_hw_device_trace_level_get(काष्ठा __vxge_hw_device *devh);

/**
 * vxge_hw_ring_rxd_size_get	- Get the size of ring descriptor.
 * @buf_mode: Buffer mode (1, 3 or 5)
 *
 * This function वापसs the size of RxD क्रम given buffer mode
 */
अटल अंतरभूत u32 vxge_hw_ring_rxd_size_get(u32 buf_mode)
अणु
	वापस माप(काष्ठा vxge_hw_ring_rxd_1);
पूर्ण

/**
 * vxge_hw_ring_rxds_per_block_get - Get the number of rxds per block.
 * @buf_mode: Buffer mode (1 buffer mode only)
 *
 * This function वापसs the number of RxD क्रम RxD block क्रम given buffer mode
 */
अटल अंतरभूत u32 vxge_hw_ring_rxds_per_block_get(u32 buf_mode)
अणु
	वापस (u32)((VXGE_HW_BLOCK_SIZE-16) /
		माप(काष्ठा vxge_hw_ring_rxd_1));
पूर्ण

/**
 * vxge_hw_ring_rxd_1b_set - Prepare 1-buffer-mode descriptor.
 * @rxdh: Descriptor handle.
 * @dma_poपूर्णांकer: DMA address of	a single receive buffer	this descriptor
 * should carry. Note that by the समय vxge_hw_ring_rxd_1b_set is called,
 * the receive buffer should be alपढ़ोy mapped to the device
 * @size: Size of the receive @dma_poपूर्णांकer buffer.
 *
 * Prepare 1-buffer-mode Rx	descriptor क्रम posting
 * (via	vxge_hw_ring_rxd_post()).
 *
 * This	अंतरभूत helper-function करोes not	वापस any parameters and always
 * succeeds.
 *
 */
अटल अंतरभूत
व्योम vxge_hw_ring_rxd_1b_set(
	व्योम *rxdh,
	dma_addr_t dma_poपूर्णांकer,
	u32 size)
अणु
	काष्ठा vxge_hw_ring_rxd_1 *rxdp = (काष्ठा vxge_hw_ring_rxd_1 *)rxdh;
	rxdp->buffer0_ptr = dma_poपूर्णांकer;
	rxdp->control_1	&= ~VXGE_HW_RING_RXD_1_BUFFER0_SIZE_MASK;
	rxdp->control_1	|= VXGE_HW_RING_RXD_1_BUFFER0_SIZE(size);
पूर्ण

/**
 * vxge_hw_ring_rxd_1b_get - Get data from the completed 1-buf
 * descriptor.
 * @vpath_handle: Virtual Path handle.
 * @rxdh: Descriptor handle.
 * @dma_poपूर्णांकer: DMA address of	a single receive buffer	this descriptor
 * carries. Returned by HW.
 * @pkt_length:	Length (in bytes) of the data in the buffer poपूर्णांकed by
 *
 * Retrieve protocol data from the completed 1-buffer-mode Rx descriptor.
 * This	अंतरभूत helper-function uses completed descriptor to populate receive
 * buffer poपूर्णांकer and other "out" parameters. The function always succeeds.
 *
 */
अटल अंतरभूत
व्योम vxge_hw_ring_rxd_1b_get(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम *rxdh,
	u32 *pkt_length)
अणु
	काष्ठा vxge_hw_ring_rxd_1 *rxdp = (काष्ठा vxge_hw_ring_rxd_1 *)rxdh;

	*pkt_length =
		(u32)VXGE_HW_RING_RXD_1_BUFFER0_SIZE_GET(rxdp->control_1);
पूर्ण

/**
 * vxge_hw_ring_rxd_1b_info_get - Get extended inक्रमmation associated with
 * a completed receive descriptor क्रम 1b mode.
 * @vpath_handle: Virtual Path handle.
 * @rxdh: Descriptor handle.
 * @rxd_info: Descriptor inक्रमmation
 *
 * Retrieve extended inक्रमmation associated with a completed receive descriptor.
 *
 */
अटल अंतरभूत
व्योम vxge_hw_ring_rxd_1b_info_get(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम *rxdh,
	काष्ठा vxge_hw_ring_rxd_info *rxd_info)
अणु

	काष्ठा vxge_hw_ring_rxd_1 *rxdp = (काष्ठा vxge_hw_ring_rxd_1 *)rxdh;
	rxd_info->syn_flag =
		(u32)VXGE_HW_RING_RXD_SYN_GET(rxdp->control_0);
	rxd_info->is_icmp =
		(u32)VXGE_HW_RING_RXD_IS_ICMP_GET(rxdp->control_0);
	rxd_info->fast_path_eligible =
		(u32)VXGE_HW_RING_RXD_FAST_PATH_ELIGIBLE_GET(rxdp->control_0);
	rxd_info->l3_cksum_valid =
		(u32)VXGE_HW_RING_RXD_L3_CKSUM_CORRECT_GET(rxdp->control_0);
	rxd_info->l3_cksum =
		(u32)VXGE_HW_RING_RXD_L3_CKSUM_GET(rxdp->control_0);
	rxd_info->l4_cksum_valid =
		(u32)VXGE_HW_RING_RXD_L4_CKSUM_CORRECT_GET(rxdp->control_0);
	rxd_info->l4_cksum =
		(u32)VXGE_HW_RING_RXD_L4_CKSUM_GET(rxdp->control_0);
	rxd_info->frame =
		(u32)VXGE_HW_RING_RXD_ETHER_ENCAP_GET(rxdp->control_0);
	rxd_info->proto =
		(u32)VXGE_HW_RING_RXD_FRAME_PROTO_GET(rxdp->control_0);
	rxd_info->is_vlan =
		(u32)VXGE_HW_RING_RXD_IS_VLAN_GET(rxdp->control_0);
	rxd_info->vlan =
		(u32)VXGE_HW_RING_RXD_VLAN_TAG_GET(rxdp->control_1);
	rxd_info->rth_bucket =
		(u32)VXGE_HW_RING_RXD_RTH_BUCKET_GET(rxdp->control_0);
	rxd_info->rth_it_hit =
		(u32)VXGE_HW_RING_RXD_RTH_IT_HIT_GET(rxdp->control_0);
	rxd_info->rth_spdm_hit =
		(u32)VXGE_HW_RING_RXD_RTH_SPDM_HIT_GET(rxdp->control_0);
	rxd_info->rth_hash_type =
		(u32)VXGE_HW_RING_RXD_RTH_HASH_TYPE_GET(rxdp->control_0);
	rxd_info->rth_value =
		(u32)VXGE_HW_RING_RXD_1_RTH_HASH_VAL_GET(rxdp->control_1);
पूर्ण

/**
 * vxge_hw_ring_rxd_निजी_get - Get driver निजी per-descriptor data
 *                      of 1b mode 3b mode ring.
 * @rxdh: Descriptor handle.
 *
 * Returns: निजी driver	info associated	with the descriptor.
 * driver requests	per-descriptor space via vxge_hw_ring_attr.
 *
 */
अटल अंतरभूत व्योम *vxge_hw_ring_rxd_निजी_get(व्योम *rxdh)
अणु
	काष्ठा vxge_hw_ring_rxd_1 *rxdp = (काष्ठा vxge_hw_ring_rxd_1 *)rxdh;
	वापस (व्योम *)(माप_प्रकार)rxdp->host_control;
पूर्ण

/**
 * vxge_hw_fअगरo_txdl_cksum_set_bits - Offload checksum.
 * @txdlh: Descriptor handle.
 * @cksum_bits: Specअगरies which checksums are to be offloaded: IPv4,
 *              and/or TCP and/or UDP.
 *
 * Ask Titan to calculate IPv4 & transport checksums क्रम _this_ transmit
 * descriptor.
 * This API is part of the preparation of the transmit descriptor क्रम posting
 * (via vxge_hw_fअगरo_txdl_post()). The related "preparation" APIs include
 * vxge_hw_fअगरo_txdl_mss_set(), vxge_hw_fअगरo_txdl_buffer_set_aligned(),
 * and vxge_hw_fअगरo_txdl_buffer_set().
 * All these APIs fill in the fields of the fअगरo descriptor,
 * in accordance with the Titan specअगरication.
 *
 */
अटल अंतरभूत व्योम vxge_hw_fअगरo_txdl_cksum_set_bits(व्योम *txdlh, u64 cksum_bits)
अणु
	काष्ठा vxge_hw_fअगरo_txd *txdp = (काष्ठा vxge_hw_fअगरo_txd *)txdlh;
	txdp->control_1 |= cksum_bits;
पूर्ण

/**
 * vxge_hw_fअगरo_txdl_mss_set - Set MSS.
 * @txdlh: Descriptor handle.
 * @mss: MSS size क्रम _this_ TCP connection. Passed by TCP stack करोwn to the
 *       driver, which in turn inserts the MSS पूर्णांकo the @txdlh.
 *
 * This API is part of the preparation of the transmit descriptor क्रम posting
 * (via vxge_hw_fअगरo_txdl_post()). The related "preparation" APIs include
 * vxge_hw_fअगरo_txdl_buffer_set(), vxge_hw_fअगरo_txdl_buffer_set_aligned(),
 * and vxge_hw_fअगरo_txdl_cksum_set_bits().
 * All these APIs fill in the fields of the fअगरo descriptor,
 * in accordance with the Titan specअगरication.
 *
 */
अटल अंतरभूत व्योम vxge_hw_fअगरo_txdl_mss_set(व्योम *txdlh, पूर्णांक mss)
अणु
	काष्ठा vxge_hw_fअगरo_txd *txdp = (काष्ठा vxge_hw_fअगरo_txd *)txdlh;

	txdp->control_0 |= VXGE_HW_FIFO_TXD_LSO_EN;
	txdp->control_0 |= VXGE_HW_FIFO_TXD_LSO_MSS(mss);
पूर्ण

/**
 * vxge_hw_fअगरo_txdl_vlan_set - Set VLAN tag.
 * @txdlh: Descriptor handle.
 * @vlan_tag: 16bit VLAN tag.
 *
 * Insert VLAN tag पूर्णांकo specअगरied transmit descriptor.
 * The actual insertion of the tag पूर्णांकo outgoing frame is करोne by the hardware.
 */
अटल अंतरभूत व्योम vxge_hw_fअगरo_txdl_vlan_set(व्योम *txdlh, u16 vlan_tag)
अणु
	काष्ठा vxge_hw_fअगरo_txd *txdp = (काष्ठा vxge_hw_fअगरo_txd *)txdlh;

	txdp->control_1 |= VXGE_HW_FIFO_TXD_VLAN_ENABLE;
	txdp->control_1 |= VXGE_HW_FIFO_TXD_VLAN_TAG(vlan_tag);
पूर्ण

/**
 * vxge_hw_fअगरo_txdl_निजी_get - Retrieve per-descriptor निजी data.
 * @txdlh: Descriptor handle.
 *
 * Retrieve per-descriptor निजी data.
 * Note that driver requests per-descriptor space via
 * काष्ठा vxge_hw_fअगरo_attr passed to
 * vxge_hw_vpath_खोलो().
 *
 * Returns: निजी driver data associated with the descriptor.
 */
अटल अंतरभूत व्योम *vxge_hw_fअगरo_txdl_निजी_get(व्योम *txdlh)
अणु
	काष्ठा vxge_hw_fअगरo_txd *txdp  = (काष्ठा vxge_hw_fअगरo_txd *)txdlh;

	वापस (व्योम *)(माप_प्रकार)txdp->host_control;
पूर्ण

/**
 * काष्ठा vxge_hw_ring_attr - Ring खोलो "template".
 * @callback: Ring completion callback. HW invokes the callback when there
 *            are new completions on that ring. In many implementations
 *            the @callback executes in the hw पूर्णांकerrupt context.
 * @rxd_init: Ring's descriptor-initialize callback.
 *            See vxge_hw_ring_rxd_init_fअणुपूर्ण.
 *            If not शून्य, HW invokes the callback when खोलोing
 *            the ring.
 * @rxd_term: Ring's descriptor-terminate callback. If not शून्य,
 *          HW invokes the callback when closing the corresponding ring.
 *          See also vxge_hw_ring_rxd_term_fअणुपूर्ण.
 * @userdata: User-defined "context" of _that_ ring. Passed back to the
 *            user as one of the @callback, @rxd_init, and @rxd_term arguments.
 * @per_rxd_space: If specअगरied (i.e., greater than zero): extra space
 *              reserved by HW per each receive descriptor.
 *              Can be used to store
 *              and retrieve on completion, inक्रमmation specअगरic
 *              to the driver.
 *
 * Ring खोलो "template". User fills the काष्ठाure with ring
 * attributes and passes it to vxge_hw_vpath_खोलो().
 */
काष्ठा vxge_hw_ring_attr अणु
	क्रमागत vxge_hw_status (*callback)(
			काष्ठा __vxge_hw_ring *ringh,
			व्योम *rxdh,
			u8 t_code,
			व्योम *userdata);

	क्रमागत vxge_hw_status (*rxd_init)(
			व्योम *rxdh,
			व्योम *userdata);

	व्योम (*rxd_term)(
			व्योम *rxdh,
			क्रमागत vxge_hw_rxd_state state,
			व्योम *userdata);

	व्योम		*userdata;
	u32		per_rxd_space;
पूर्ण;

/**
 * function vxge_hw_fअगरo_callback_f - FIFO callback.
 * @vpath_handle: Virtual path whose Fअगरo "containing" 1 or more completed
 *             descriptors.
 * @txdlh: First completed descriptor.
 * @txdl_priv: Poपूर्णांकer to per txdl space allocated
 * @t_code: Transfer code, as per Titan User Guide.
 *          Returned by HW.
 * @host_control: Opaque 64bit data stored by driver inside the Titan
 *            descriptor prior to posting the latter on the fअगरo
 *            via vxge_hw_fअगरo_txdl_post(). The @host_control is वापसed
 *            as is to the driver with each completed descriptor.
 * @userdata: Opaque per-fअगरo data specअगरied at fअगरo खोलो
 *            समय, via vxge_hw_vpath_खोलो().
 *
 * Fअगरo completion callback (type declaration). A single per-fअगरo
 * callback is specअगरied at fअगरo खोलो समय, via
 * vxge_hw_vpath_खोलो(). Typically माला_लो called as part of the processing
 * of the Interrupt Service Routine.
 *
 * Fअगरo callback माला_लो called by HW अगर, and only अगर, there is at least
 * one new completion on a given fअगरo. Upon processing the first @txdlh driver
 * is _supposed_ to जारी consuming completions using:
 *    - vxge_hw_fअगरo_txdl_next_completed()
 *
 * Note that failure to process new completions in a समयly fashion
 * leads to VXGE_HW_INF_OUT_OF_DESCRIPTORS condition.
 *
 * Non-zero @t_code means failure to process transmit descriptor.
 *
 * In the "transmit" हाल the failure could happen, क्रम instance, when the
 * link is करोwn, in which हाल Titan completes the descriptor because it
 * is not able to send the data out.
 *
 * For details please refer to Titan User Guide.
 *
 * See also: vxge_hw_fअगरo_txdl_next_completed(), vxge_hw_fअगरo_txdl_term_fअणुपूर्ण.
 */
/**
 * function vxge_hw_fअगरo_txdl_term_f - Terminate descriptor callback.
 * @txdlh: First completed descriptor.
 * @txdl_priv: Poपूर्णांकer to per txdl space allocated
 * @state: One of the क्रमागत vxge_hw_txdl_stateअणुपूर्ण क्रमागतerated states.
 * @userdata: Per-fअगरo user data (a.k.a. context) specअगरied at
 * fअगरo खोलो समय, via vxge_hw_vpath_खोलो().
 *
 * Terminate descriptor callback. Unless शून्य is specअगरied in the
 * काष्ठा vxge_hw_fअगरo_attrअणुपूर्ण काष्ठाure passed to vxge_hw_vpath_खोलो()),
 * HW invokes the callback as part of closing fअगरo, prior to
 * de-allocating the ring and associated data काष्ठाures
 * (including descriptors).
 * driver should utilize the callback to (क्रम instance) unmap
 * and मुक्त DMA data buffers associated with the posted (state =
 * VXGE_HW_TXDL_STATE_POSTED) descriptors,
 * as well as other relevant cleanup functions.
 *
 * See also: काष्ठा vxge_hw_fअगरo_attrअणुपूर्ण
 */
/**
 * काष्ठा vxge_hw_fअगरo_attr - Fअगरo खोलो "template".
 * @callback: Fअगरo completion callback. HW invokes the callback when there
 *            are new completions on that fअगरo. In many implementations
 *            the @callback executes in the hw पूर्णांकerrupt context.
 * @txdl_term: Fअगरo's descriptor-terminate callback. If not शून्य,
 *          HW invokes the callback when closing the corresponding fअगरo.
 *          See also vxge_hw_fअगरo_txdl_term_fअणुपूर्ण.
 * @userdata: User-defined "context" of _that_ fअगरo. Passed back to the
 *            user as one of the @callback, and @txdl_term arguments.
 * @per_txdl_space: If specअगरied (i.e., greater than zero): extra space
 *              reserved by HW per each transmit descriptor. Can be used to
 *              store, and retrieve on completion, inक्रमmation specअगरic
 *              to the driver.
 *
 * Fअगरo खोलो "template". User fills the काष्ठाure with fअगरo
 * attributes and passes it to vxge_hw_vpath_खोलो().
 */
काष्ठा vxge_hw_fअगरo_attr अणु

	क्रमागत vxge_hw_status (*callback)(
			काष्ठा __vxge_hw_fअगरo *fअगरo_handle,
			व्योम *txdlh,
			क्रमागत vxge_hw_fअगरo_tcode t_code,
			व्योम *userdata,
			काष्ठा sk_buff ***skb_ptr,
			पूर्णांक nr_skb, पूर्णांक *more);

	व्योम (*txdl_term)(
			व्योम *txdlh,
			क्रमागत vxge_hw_txdl_state state,
			व्योम *userdata);

	व्योम		*userdata;
	u32		per_txdl_space;
पूर्ण;

/**
 * काष्ठा vxge_hw_vpath_attr - Attributes of भव path
 * @vp_id: Identअगरier of Virtual Path
 * @ring_attr: Attributes of ring क्रम non-offload receive
 * @fअगरo_attr: Attributes of fअगरo क्रम non-offload transmit
 *
 * Attributes of भव path.  This काष्ठाure is passed as parameter
 * to the vxge_hw_vpath_खोलो() routine to set the attributes of ring and fअगरo.
 */
काष्ठा vxge_hw_vpath_attr अणु
	u32				vp_id;
	काष्ठा vxge_hw_ring_attr	ring_attr;
	काष्ठा vxge_hw_fअगरo_attr	fअगरo_attr;
पूर्ण;

क्रमागत vxge_hw_status vxge_hw_device_hw_info_get(
	व्योम __iomem *bar0,
	काष्ठा vxge_hw_device_hw_info *hw_info);

क्रमागत vxge_hw_status vxge_hw_device_config_शेष_get(
	काष्ठा vxge_hw_device_config *device_config);

/**
 * vxge_hw_device_link_state_get - Get link state.
 * @devh: HW device handle.
 *
 * Get link state.
 * Returns: link state.
 */
अटल अंतरभूत
क्रमागत vxge_hw_device_link_state vxge_hw_device_link_state_get(
	काष्ठा __vxge_hw_device *devh)
अणु
	वापस devh->link_state;
पूर्ण

व्योम vxge_hw_device_terminate(काष्ठा __vxge_hw_device *devh);

स्थिर u8 *
vxge_hw_device_serial_number_get(काष्ठा __vxge_hw_device *devh);

u16 vxge_hw_device_link_width_get(काष्ठा __vxge_hw_device *devh);

स्थिर u8 *
vxge_hw_device_product_name_get(काष्ठा __vxge_hw_device *devh);

क्रमागत vxge_hw_status vxge_hw_device_initialize(
	काष्ठा __vxge_hw_device **devh,
	काष्ठा vxge_hw_device_attr *attr,
	काष्ठा vxge_hw_device_config *device_config);

क्रमागत vxge_hw_status vxge_hw_device_getछोड़ो_data(
	 काष्ठा __vxge_hw_device *devh,
	 u32 port,
	 u32 *tx,
	 u32 *rx);

क्रमागत vxge_hw_status vxge_hw_device_setछोड़ो_data(
	काष्ठा __vxge_hw_device *devh,
	u32 port,
	u32 tx,
	u32 rx);

अटल अंतरभूत व्योम *vxge_os_dma_दो_स्मृति(काष्ठा pci_dev *pdev,
			अचिन्हित दीर्घ size,
			काष्ठा pci_dev **p_dmah,
			काष्ठा pci_dev **p_dma_acch)
अणु
	व्योम *vaddr;
	अचिन्हित दीर्घ misaligned = 0;
	पूर्णांक पुनः_स्मृति_flag = 0;
	*p_dma_acch = *p_dmah = शून्य;

पुनः_स्मृति:
	vaddr = kदो_स्मृति(size, GFP_KERNEL | GFP_DMA);
	अगर (vaddr == शून्य)
		वापस vaddr;
	misaligned = (अचिन्हित दीर्घ)VXGE_ALIGN((अचिन्हित दीर्घ)vaddr,
				VXGE_CACHE_LINE_SIZE);
	अगर (पुनः_स्मृति_flag)
		जाओ out;

	अगर (misaligned) अणु
		/* misaligned, मुक्त current one and try allocating
		 * size + VXGE_CACHE_LINE_SIZE memory
		 */
		kमुक्त(vaddr);
		size += VXGE_CACHE_LINE_SIZE;
		पुनः_स्मृति_flag = 1;
		जाओ पुनः_स्मृति;
	पूर्ण
out:
	*(अचिन्हित दीर्घ *)p_dma_acch = misaligned;
	vaddr = (व्योम *)((u8 *)vaddr + misaligned);
	वापस vaddr;
पूर्ण

अटल अंतरभूत व्योम vxge_os_dma_मुक्त(काष्ठा pci_dev *pdev, स्थिर व्योम *vaddr,
			काष्ठा pci_dev **p_dma_acch)
अणु
	अचिन्हित दीर्घ misaligned = *(अचिन्हित दीर्घ *)p_dma_acch;
	u8 *पंचांगp = (u8 *)vaddr;
	पंचांगp -= misaligned;
	kमुक्त((व्योम *)पंचांगp);
पूर्ण

/*
 * __vxge_hw_mempool_item_priv - will वापस poपूर्णांकer on per item निजी space
 */
अटल अंतरभूत व्योम*
__vxge_hw_mempool_item_priv(
	काष्ठा vxge_hw_mempool *mempool,
	u32 memblock_idx,
	व्योम *item,
	u32 *memblock_item_idx)
अणु
	सूचक_भेद_प्रकार offset;
	व्योम *memblock = mempool->memblocks_arr[memblock_idx];


	offset = (u32)((u8 *)item - (u8 *)memblock);
	vxge_निश्चित(offset >= 0 && (u32)offset < mempool->memblock_size);

	(*memblock_item_idx) = (u32) offset / mempool->item_size;
	vxge_निश्चित((*memblock_item_idx) < mempool->items_per_memblock);

	वापस (u8 *)mempool->memblocks_priv_arr[memblock_idx] +
			    (*memblock_item_idx) * mempool->items_priv_size;
पूर्ण

/*
 * __vxge_hw_fअगरo_txdl_priv - Return the max fragments allocated
 * क्रम the fअगरo.
 * @fअगरo: Fअगरo
 * @txdp: Poniter to a TxD
 */
अटल अंतरभूत काष्ठा __vxge_hw_fअगरo_txdl_priv *
__vxge_hw_fअगरo_txdl_priv(
	काष्ठा __vxge_hw_fअगरo *fअगरo,
	काष्ठा vxge_hw_fअगरo_txd *txdp)
अणु
	वापस (काष्ठा __vxge_hw_fअगरo_txdl_priv *)
			(((अक्षर *)((uदीर्घ)txdp->host_control)) +
				fअगरo->per_txdl_space);
पूर्ण

क्रमागत vxge_hw_status vxge_hw_vpath_खोलो(
	काष्ठा __vxge_hw_device *devh,
	काष्ठा vxge_hw_vpath_attr *attr,
	काष्ठा __vxge_hw_vpath_handle **vpath_handle);

क्रमागत vxge_hw_status vxge_hw_vpath_बंद(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

क्रमागत vxge_hw_status
vxge_hw_vpath_reset(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

क्रमागत vxge_hw_status
vxge_hw_vpath_recover_from_reset(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

व्योम
vxge_hw_vpath_enable(काष्ठा __vxge_hw_vpath_handle *vp);

क्रमागत vxge_hw_status
vxge_hw_vpath_check_leak(काष्ठा __vxge_hw_ring *ringh);

क्रमागत vxge_hw_status vxge_hw_vpath_mtu_set(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u32 new_mtu);

व्योम
vxge_hw_vpath_rx_करोorbell_init(काष्ठा __vxge_hw_vpath_handle *vp);

अटल अंतरभूत व्योम __vxge_hw_pio_mem_ग_लिखो32_upper(u32 val, व्योम __iomem *addr)
अणु
	ग_लिखोl(val, addr + 4);
पूर्ण

अटल अंतरभूत व्योम __vxge_hw_pio_mem_ग_लिखो32_lower(u32 val, व्योम __iomem *addr)
अणु
	ग_लिखोl(val, addr);
पूर्ण

क्रमागत vxge_hw_status
vxge_hw_device_flick_link_led(काष्ठा __vxge_hw_device *devh, u64 on_off);

क्रमागत vxge_hw_status
vxge_hw_vpath_strip_fcs_check(काष्ठा __vxge_hw_device *hldev, u64 vpath_mask);

/**
 * vxge_debug_ll
 * @level: level of debug verbosity.
 * @mask: mask क्रम the debug
 * @buf: Circular buffer क्रम tracing
 * @fmt: म_लिखो like क्रमmat string
 *
 * Provides logging facilities. Can be customized on per-module
 * basis or/and with debug levels. Input parameters, except
 * module and level, are the same as posix म_लिखो. This function
 * may be compiled out अगर DEBUG macro was never defined.
 * See also: क्रमागत vxge_debug_levelअणुपूर्ण.
 */
#अगर (VXGE_COMPONENT_LL & VXGE_DEBUG_MODULE_MASK)
#घोषणा vxge_debug_ll(level, mask, fmt, ...) करो अणु			       \
	अगर ((level >= VXGE_ERR && VXGE_COMPONENT_LL & VXGE_DEBUG_ERR_MASK) ||  \
	    (level >= VXGE_TRACE && VXGE_COMPONENT_LL & VXGE_DEBUG_TRACE_MASK))\
		अगर ((mask & VXGE_DEBUG_MASK) == mask)			       \
			prपूर्णांकk(fmt "\n", ##__VA_ARGS__);		       \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा vxge_debug_ll(level, mask, fmt, ...)
#पूर्ण_अगर

क्रमागत vxge_hw_status vxge_hw_vpath_rts_rth_itable_set(
			काष्ठा __vxge_hw_vpath_handle **vpath_handles,
			u32 vpath_count,
			u8 *mtable,
			u8 *itable,
			u32 itable_size);

क्रमागत vxge_hw_status vxge_hw_vpath_rts_rth_set(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	क्रमागत vxge_hw_rth_algoriपंचांगs algorithm,
	काष्ठा vxge_hw_rth_hash_types *hash_type,
	u16 bucket_size);

क्रमागत vxge_hw_status
__vxge_hw_device_is_privilaged(u32 host_type, u32 func_id);

#घोषणा VXGE_HW_MIN_SUCCESSIVE_IDLE_COUNT 5
#घोषणा VXGE_HW_MAX_POLLING_COUNT 100

व्योम
vxge_hw_device_रुको_receive_idle(काष्ठा __vxge_hw_device *hldev);

क्रमागत vxge_hw_status
vxge_hw_upgrade_पढ़ो_version(काष्ठा __vxge_hw_device *hldev, u32 *major,
			     u32 *minor, u32 *build);

क्रमागत vxge_hw_status vxge_hw_flash_fw(काष्ठा __vxge_hw_device *hldev);

क्रमागत vxge_hw_status
vxge_update_fw_image(काष्ठा __vxge_hw_device *hldev, स्थिर u8 *filebuf,
		     पूर्णांक size);

क्रमागत vxge_hw_status
vxge_hw_vpath_eprom_img_ver_get(काष्ठा __vxge_hw_device *hldev,
				काष्ठा eprom_image *eprom_image_data);

पूर्णांक vxge_hw_vpath_रुको_receive_idle(काष्ठा __vxge_hw_device *hldev, u32 vp_id);
#पूर्ण_अगर
