<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2012  AudioScience Inc. <support@audioscience.com>


HPI पूर्णांकernal definitions

(C) Copyright AudioScience Inc. 1996-2009
******************************************************************************/

#अगर_अघोषित _HPI_INTERNAL_H_
#घोषणा _HPI_INTERNAL_H_

#समावेश "hpi.h"

/** maximum number of memory regions mapped to an adapter */
#घोषणा HPI_MAX_ADAPTER_MEM_SPACES (2)

/* Each OS needs its own hpios.h */
#समावेश "hpios.h"

/* physical memory allocation */

/** Allocate and map an area of locked memory क्रम bus master DMA operations.

On success, *pLockedMemeHandle is a valid handle, and 0 is वापसed
On error *pLockedMemHandle marked invalid, non-zero वापसed.

If this function succeeds, then HpiOs_LockedMem_GetVirtAddr() and
HpiOs_LockedMem_GetPyhsAddr() will always succed on the वापसed handle.
*/
u16 hpios_locked_mem_alloc(काष्ठा consistent_dma_area *p_locked_mem_handle,
							   /**< memory handle */
	u32 size, /**< Size in bytes to allocate */
	काष्ठा pci_dev *p_os_reference
	/**< OS specअगरic data required क्रम memory allocation */
	);

/** Free mapping and memory represented by LockedMemHandle

Frees any resources, then invalidates the handle.
Returns 0 on success, 1 अगर handle is invalid.

*/
u16 hpios_locked_mem_मुक्त(काष्ठा consistent_dma_area *locked_mem_handle);

/** Get the physical PCI address of memory represented by LockedMemHandle.

If handle is invalid *pPhysicalAddr is set to zero and वापस 1
*/
u16 hpios_locked_mem_get_phys_addr(काष्ठा consistent_dma_area
	*locked_mem_handle, u32 *p_physical_addr);

/** Get the CPU address of memory represented by LockedMemHandle.

If handle is शून्य *ppvVirtualAddr is set to शून्य and वापस 1
*/
u16 hpios_locked_mem_get_virt_addr(काष्ठा consistent_dma_area
	*locked_mem_handle, व्योम **ppv_भव_addr);

/** Check that handle is valid
i.e it represents a valid memory area
*/
u16 hpios_locked_mem_valid(काष्ठा consistent_dma_area *locked_mem_handle);

/* timing/delay */
व्योम hpios_delay_micro_seconds(u32 num_micro_sec);

काष्ठा hpi_message;
काष्ठा hpi_response;

प्रकार व्योम hpi_handler_func(काष्ठा hpi_message *, काष्ठा hpi_response *);

/* If the निश्चित fails, compiler complains
   something like size of array `msg' is negative.
   Unlike linux BUILD_BUG_ON, this works outside function scope.
*/
#घोषणा compile_समय_निश्चित(cond, msg) \
    प्रकार अक्षर ASSERT_##msg[(cond) ? 1 : -1]

/******************************************* bus types */
क्रमागत HPI_BUSES अणु
	HPI_BUS_ISAPNP = 1,
	HPI_BUS_PCI = 2,
	HPI_BUS_USB = 3,
	HPI_BUS_NET = 4
पूर्ण;

क्रमागत HPI_SUBSYS_OPTIONS अणु
	/* 0, 256 are invalid, 1..255 reserved क्रम global options */
	HPI_SUBSYS_OPT_NET_ENABLE = 257,
	HPI_SUBSYS_OPT_NET_BROADCAST = 258,
	HPI_SUBSYS_OPT_NET_UNICAST = 259,
	HPI_SUBSYS_OPT_NET_ADDR = 260,
	HPI_SUBSYS_OPT_NET_MASK = 261,
	HPI_SUBSYS_OPT_NET_ADAPTER_ADDRESS_ADD = 262
पूर्ण;

/** Volume flags
*/
क्रमागत HPI_VOLUME_FLAGS अणु
	/** Set अगर the volume control is muted */
	HPI_VOLUME_FLAG_MUTED = (1 << 0),
	/** Set अगर the volume control has a mute function */
	HPI_VOLUME_FLAG_HAS_MUTE = (1 << 1),
	/** Set अगर volume control can करो स्वतःfading */
	HPI_VOLUME_FLAG_HAS_AUTOFADE = (1 << 2)
		/* Note Flags >= (1<<8) are क्रम DSP पूर्णांकernal use only */
पूर्ण;

/******************************************* CONTROL ATTRIBUTES ****/
/* (in order of control type ID */

/* This allows क्रम 255 control types, 256 unique attributes each */
#घोषणा HPI_CTL_ATTR(ctl, ai) ((HPI_CONTROL_##ctl << 8) + ai)

/* Get the sub-index of the attribute क्रम a control type */
#घोषणा HPI_CTL_ATTR_INDEX(i) (i & 0xff)

/* Extract the control from the control attribute */
#घोषणा HPI_CTL_ATTR_CONTROL(i) (i >> 8)

/** Enable event generation क्रम a control.
0=disable, 1=enable
\नote generic to all controls that can generate events
*/

/** Unique identअगरiers क्रम every control attribute
*/
क्रमागत HPI_CONTROL_ATTRIBUTES अणु
	HPI_GENERIC_ENABLE = HPI_CTL_ATTR(GENERIC, 1),
	HPI_GENERIC_EVENT_ENABLE = HPI_CTL_ATTR(GENERIC, 2),

	HPI_VOLUME_GAIN = HPI_CTL_ATTR(VOLUME, 1),
	HPI_VOLUME_AUTOFADE = HPI_CTL_ATTR(VOLUME, 2),
	HPI_VOLUME_MUTE = HPI_CTL_ATTR(VOLUME, 3),
	HPI_VOLUME_GAIN_AND_FLAGS = HPI_CTL_ATTR(VOLUME, 4),
	HPI_VOLUME_NUM_CHANNELS = HPI_CTL_ATTR(VOLUME, 6),
	HPI_VOLUME_RANGE = HPI_CTL_ATTR(VOLUME, 10),

	HPI_METER_RMS = HPI_CTL_ATTR(METER, 1),
	HPI_METER_PEAK = HPI_CTL_ATTR(METER, 2),
	HPI_METER_RMS_BALLISTICS = HPI_CTL_ATTR(METER, 3),
	HPI_METER_PEAK_BALLISTICS = HPI_CTL_ATTR(METER, 4),
	HPI_METER_NUM_CHANNELS = HPI_CTL_ATTR(METER, 5),

	HPI_MULTIPLEXER_SOURCE = HPI_CTL_ATTR(MULTIPLEXER, 1),
	HPI_MULTIPLEXER_QUERYSOURCE = HPI_CTL_ATTR(MULTIPLEXER, 2),

	HPI_AESEBUTX_FORMAT = HPI_CTL_ATTR(AESEBUTX, 1),
	HPI_AESEBUTX_SAMPLERATE = HPI_CTL_ATTR(AESEBUTX, 3),
	HPI_AESEBUTX_CHANNELSTATUS = HPI_CTL_ATTR(AESEBUTX, 4),
	HPI_AESEBUTX_USERDATA = HPI_CTL_ATTR(AESEBUTX, 5),

	HPI_AESEBURX_FORMAT = HPI_CTL_ATTR(AESEBURX, 1),
	HPI_AESEBURX_ERRORSTATUS = HPI_CTL_ATTR(AESEBURX, 2),
	HPI_AESEBURX_SAMPLERATE = HPI_CTL_ATTR(AESEBURX, 3),
	HPI_AESEBURX_CHANNELSTATUS = HPI_CTL_ATTR(AESEBURX, 4),
	HPI_AESEBURX_USERDATA = HPI_CTL_ATTR(AESEBURX, 5),

	HPI_LEVEL_GAIN = HPI_CTL_ATTR(LEVEL, 1),
	HPI_LEVEL_RANGE = HPI_CTL_ATTR(LEVEL, 10),

	HPI_TUNER_BAND = HPI_CTL_ATTR(TUNER, 1),
	HPI_TUNER_FREQ = HPI_CTL_ATTR(TUNER, 2),
	HPI_TUNER_LEVEL_AVG = HPI_CTL_ATTR(TUNER, 3),
	HPI_TUNER_LEVEL_RAW = HPI_CTL_ATTR(TUNER, 4),
	HPI_TUNER_SNR = HPI_CTL_ATTR(TUNER, 5),
	HPI_TUNER_GAIN = HPI_CTL_ATTR(TUNER, 6),
	HPI_TUNER_STATUS = HPI_CTL_ATTR(TUNER, 7),
	HPI_TUNER_MODE = HPI_CTL_ATTR(TUNER, 8),
	HPI_TUNER_RDS = HPI_CTL_ATTR(TUNER, 9),
	HPI_TUNER_DEEMPHASIS = HPI_CTL_ATTR(TUNER, 10),
	HPI_TUNER_PROGRAM = HPI_CTL_ATTR(TUNER, 11),
	HPI_TUNER_HDRADIO_SIGNAL_QUALITY = HPI_CTL_ATTR(TUNER, 12),
	HPI_TUNER_HDRADIO_SDK_VERSION = HPI_CTL_ATTR(TUNER, 13),
	HPI_TUNER_HDRADIO_DSP_VERSION = HPI_CTL_ATTR(TUNER, 14),
	HPI_TUNER_HDRADIO_BLEND = HPI_CTL_ATTR(TUNER, 15),

	HPI_VOX_THRESHOLD = HPI_CTL_ATTR(VOX, 1),

	HPI_CHANNEL_MODE_MODE = HPI_CTL_ATTR(CHANNEL_MODE, 1),

	HPI_BITSTREAM_DATA_POLARITY = HPI_CTL_ATTR(BITSTREAM, 1),
	HPI_BITSTREAM_CLOCK_EDGE = HPI_CTL_ATTR(BITSTREAM, 2),
	HPI_BITSTREAM_CLOCK_SOURCE = HPI_CTL_ATTR(BITSTREAM, 3),
	HPI_BITSTREAM_ACTIVITY = HPI_CTL_ATTR(BITSTREAM, 4),

	HPI_SAMPLECLOCK_SOURCE = HPI_CTL_ATTR(SAMPLECLOCK, 1),
	HPI_SAMPLECLOCK_SAMPLERATE = HPI_CTL_ATTR(SAMPLECLOCK, 2),
	HPI_SAMPLECLOCK_SOURCE_INDEX = HPI_CTL_ATTR(SAMPLECLOCK, 3),
	HPI_SAMPLECLOCK_LOCAL_SAMPLERATE = HPI_CTL_ATTR(SAMPLECLOCK, 4),
	HPI_SAMPLECLOCK_AUTO = HPI_CTL_ATTR(SAMPLECLOCK, 5),
	HPI_SAMPLECLOCK_LOCAL_LOCK = HPI_CTL_ATTR(SAMPLECLOCK, 6),

	HPI_MICROPHONE_PHANTOM_POWER = HPI_CTL_ATTR(MICROPHONE, 1),

	HPI_EQUALIZER_NUM_FILTERS = HPI_CTL_ATTR(EQUALIZER, 1),
	HPI_EQUALIZER_FILTER = HPI_CTL_ATTR(EQUALIZER, 2),
	HPI_EQUALIZER_COEFFICIENTS = HPI_CTL_ATTR(EQUALIZER, 3),

	HPI_COMPANDER_PARAMS = HPI_CTL_ATTR(COMPANDER, 1),
	HPI_COMPANDER_MAKEUPGAIN = HPI_CTL_ATTR(COMPANDER, 2),
	HPI_COMPANDER_THRESHOLD = HPI_CTL_ATTR(COMPANDER, 3),
	HPI_COMPANDER_RATIO = HPI_CTL_ATTR(COMPANDER, 4),
	HPI_COMPANDER_ATTACK = HPI_CTL_ATTR(COMPANDER, 5),
	HPI_COMPANDER_DECAY = HPI_CTL_ATTR(COMPANDER, 6),

	HPI_COBRANET_SET = HPI_CTL_ATTR(COBRANET, 1),
	HPI_COBRANET_GET = HPI_CTL_ATTR(COBRANET, 2),
	HPI_COBRANET_GET_STATUS = HPI_CTL_ATTR(COBRANET, 5),
	HPI_COBRANET_SEND_PACKET = HPI_CTL_ATTR(COBRANET, 6),
	HPI_COBRANET_GET_PACKET = HPI_CTL_ATTR(COBRANET, 7),

	HPI_TONEDETECTOR_THRESHOLD = HPI_CTL_ATTR(TONEDETECTOR, 1),
	HPI_TONEDETECTOR_STATE = HPI_CTL_ATTR(TONEDETECTOR, 2),
	HPI_TONEDETECTOR_FREQUENCY = HPI_CTL_ATTR(TONEDETECTOR, 3),

	HPI_SILENCEDETECTOR_THRESHOLD = HPI_CTL_ATTR(SILENCEDETECTOR, 1),
	HPI_SILENCEDETECTOR_STATE = HPI_CTL_ATTR(SILENCEDETECTOR, 2),
	HPI_SILENCEDETECTOR_DELAY = HPI_CTL_ATTR(SILENCEDETECTOR, 3),

	HPI_PAD_CHANNEL_NAME = HPI_CTL_ATTR(PAD, 1),
	HPI_PAD_ARTIST = HPI_CTL_ATTR(PAD, 2),
	HPI_PAD_TITLE = HPI_CTL_ATTR(PAD, 3),
	HPI_PAD_COMMENT = HPI_CTL_ATTR(PAD, 4),
	HPI_PAD_PROGRAM_TYPE = HPI_CTL_ATTR(PAD, 5),
	HPI_PAD_PROGRAM_ID = HPI_CTL_ATTR(PAD, 6),
	HPI_PAD_TA_SUPPORT = HPI_CTL_ATTR(PAD, 7),
	HPI_PAD_TA_ACTIVE = HPI_CTL_ATTR(PAD, 8),

	HPI_UNIVERSAL_ENTITY = HPI_CTL_ATTR(UNIVERSAL, 1)
पूर्ण;

#घोषणा HPI_POLARITY_POSITIVE           0
#घोषणा HPI_POLARITY_NEGATIVE           1

/*------------------------------------------------------------
 Cobranet Chip Bridge - copied from HMI.H
------------------------------------------------------------*/
#घोषणा  HPI_COBRANET_HMI_cobra_bridge           0x20000
#घोषणा  HPI_COBRANET_HMI_cobra_bridge_tx_pkt_buf \
	(HPI_COBRANET_HMI_cobra_bridge + 0x1000)
#घोषणा  HPI_COBRANET_HMI_cobra_bridge_rx_pkt_buf \
	(HPI_COBRANET_HMI_cobra_bridge + 0x2000)
#घोषणा  HPI_COBRANET_HMI_cobra_अगर_table1         0x110000
#घोषणा  HPI_COBRANET_HMI_cobra_अगर_phy_address \
	(HPI_COBRANET_HMI_cobra_अगर_table1 + 0xd)
#घोषणा  HPI_COBRANET_HMI_cobra_protocolIP       0x72000
#घोषणा  HPI_COBRANET_HMI_cobra_ip_mon_currentIP \
	(HPI_COBRANET_HMI_cobra_protocolIP + 0x0)
#घोषणा  HPI_COBRANET_HMI_cobra_ip_mon_अटलIP \
	(HPI_COBRANET_HMI_cobra_protocolIP + 0x2)
#घोषणा  HPI_COBRANET_HMI_cobra_sys              0x100000
#घोषणा  HPI_COBRANET_HMI_cobra_sys_desc \
		(HPI_COBRANET_HMI_cobra_sys + 0x0)
#घोषणा  HPI_COBRANET_HMI_cobra_sys_objectID \
	(HPI_COBRANET_HMI_cobra_sys + 0x100)
#घोषणा  HPI_COBRANET_HMI_cobra_sys_contact \
	(HPI_COBRANET_HMI_cobra_sys + 0x200)
#घोषणा  HPI_COBRANET_HMI_cobra_sys_name \
		(HPI_COBRANET_HMI_cobra_sys + 0x300)
#घोषणा  HPI_COBRANET_HMI_cobra_sys_location \
	(HPI_COBRANET_HMI_cobra_sys + 0x400)

/*------------------------------------------------------------
 Cobranet Chip Status bits
------------------------------------------------------------*/
#घोषणा HPI_COBRANET_HMI_STATUS_RXPACKET 2
#घोषणा HPI_COBRANET_HMI_STATUS_TXPACKET 3

/*------------------------------------------------------------
 Ethernet header size
------------------------------------------------------------*/
#घोषणा HPI_ETHERNET_HEADER_SIZE (16)

/* These defines are used to fill in protocol inक्रमmation क्रम an Ethernet packet
    sent using HMI on CS18102 */
/** ID supplied by Cirrus क्रम ASI packets. */
#घोषणा HPI_ETHERNET_PACKET_ID                  0x85
/** Simple packet - no special routing required */
#घोषणा HPI_ETHERNET_PACKET_V1                  0x01
/** This packet must make its way to the host across the HPI पूर्णांकerface */
#घोषणा HPI_ETHERNET_PACKET_HOSTED_VIA_HMI      0x20
/** This packet must make its way to the host across the HPI पूर्णांकerface */
#घोषणा HPI_ETHERNET_PACKET_HOSTED_VIA_HMI_V1   0x21
/** This packet must make its way to the host across the HPI पूर्णांकerface */
#घोषणा HPI_ETHERNET_PACKET_HOSTED_VIA_HPI      0x40
/** This packet must make its way to the host across the HPI पूर्णांकerface */
#घोषणा HPI_ETHERNET_PACKET_HOSTED_VIA_HPI_V1   0x41

#घोषणा HPI_ETHERNET_UDP_PORT 44600 /**< HPI UDP service */

/** Default network समयout in milli-seconds. */
#घोषणा HPI_ETHERNET_TIMEOUT_MS 500

/** Locked memory buffer alloc/मुक्त phases */
क्रमागत HPI_BUFFER_CMDS अणु
	/** use one message to allocate or मुक्त physical memory */
	HPI_BUFFER_CMD_EXTERNAL = 0,
	/** alloc physical memory */
	HPI_BUFFER_CMD_INTERNAL_ALLOC = 1,
	/** send physical memory address to adapter */
	HPI_BUFFER_CMD_INTERNAL_GRANTADAPTER = 2,
	/** notअगरy adapter to stop using physical buffer */
	HPI_BUFFER_CMD_INTERNAL_REVOKEADAPTER = 3,
	/** मुक्त physical buffer */
	HPI_BUFFER_CMD_INTERNAL_FREE = 4
पूर्ण;

/*****************************************************************************/
/*****************************************************************************/
/********               HPI LOW LEVEL MESSAGES                  *******/
/*****************************************************************************/
/*****************************************************************************/
/** Pnp ids */
/** "ASI"  - actual is "ASX" - need to change */
#घोषणा HPI_ID_ISAPNP_AUDIOSCIENCE      0x0669
/** PCI venकरोr ID that AudioScience uses */
#घोषणा HPI_PCI_VENDOR_ID_AUDIOSCIENCE  0x175C
/** PCI venकरोr ID that the DSP56301 has */
#घोषणा HPI_PCI_VENDOR_ID_MOTOROLA      0x1057
/** PCI venकरोr ID that TI uses */
#घोषणा HPI_PCI_VENDOR_ID_TI            0x104C

#घोषणा HPI_PCI_DEV_ID_PCI2040          0xAC60
/** TI's C6205 PCI पूर्णांकerface has this ID */
#घोषणा HPI_PCI_DEV_ID_DSP6205          0xA106

#घोषणा HPI_USB_VENDOR_ID_AUDIOSCIENCE  0x1257
#घोषणा HPI_USB_W2K_TAG                 0x57495341	/* "ASIW"       */
#घोषणा HPI_USB_LINUX_TAG               0x4C495341	/* "ASIL"       */

/** Invalid Adapter index
Used in HPI messages that are not addressed to a specअगरic adapter
Used in DLL to indicate device not present
*/
#घोषणा HPI_ADAPTER_INDEX_INVALID 0xFFFF

/** First 2 hex digits define the adapter family */
#घोषणा HPI_ADAPTER_FAMILY_MASK         0xff00
#घोषणा HPI_MODULE_FAMILY_MASK          0xfff0

#घोषणा HPI_ADAPTER_FAMILY_ASI(f)   (f & HPI_ADAPTER_FAMILY_MASK)
#घोषणा HPI_MODULE_FAMILY_ASI(f)   (f & HPI_MODULE_FAMILY_MASK)
#घोषणा HPI_ADAPTER_ASI(f)   (f)

क्रमागत HPI_MESSAGE_TYPES अणु
	HPI_TYPE_REQUEST = 1,
	HPI_TYPE_RESPONSE = 2,
	HPI_TYPE_DATA = 3,
	HPI_TYPE_SSX2BYPASS_MESSAGE = 4,
	HPI_TYPE_COMMAND = 5,
	HPI_TYPE_NOTIFICATION = 6
पूर्ण;

क्रमागत HPI_OBJECT_TYPES अणु
	HPI_OBJ_SUBSYSTEM = 1,
	HPI_OBJ_ADAPTER = 2,
	HPI_OBJ_OSTREAM = 3,
	HPI_OBJ_ISTREAM = 4,
	HPI_OBJ_MIXER = 5,
	HPI_OBJ_NODE = 6,
	HPI_OBJ_CONTROL = 7,
	HPI_OBJ_NVMEMORY = 8,
	HPI_OBJ_GPIO = 9,
	HPI_OBJ_WATCHDOG = 10,
	HPI_OBJ_CLOCK = 11,
	HPI_OBJ_PROखाता = 12,
	/* HPI_ OBJ_ CONTROLEX  = 13, */
	HPI_OBJ_ASYNCEVENT = 14
#घोषणा HPI_OBJ_MAXINDEX 14
पूर्ण;

#घोषणा HPI_OBJ_FUNCTION_SPACING 0x100
#घोषणा HPI_FUNC_ID(obj, i) (HPI_OBJ_##obj * HPI_OBJ_FUNCTION_SPACING + i)

#घोषणा HPI_EXTRACT_INDEX(fn) (fn & 0xff)

क्रमागत HPI_FUNCTION_IDS अणु
	HPI_SUBSYS_OPEN = HPI_FUNC_ID(SUBSYSTEM, 1),
	HPI_SUBSYS_GET_VERSION = HPI_FUNC_ID(SUBSYSTEM, 2),
	HPI_SUBSYS_GET_INFO = HPI_FUNC_ID(SUBSYSTEM, 3),
	HPI_SUBSYS_CREATE_ADAPTER = HPI_FUNC_ID(SUBSYSTEM, 5),
	HPI_SUBSYS_CLOSE = HPI_FUNC_ID(SUBSYSTEM, 6),
	HPI_SUBSYS_DRIVER_LOAD = HPI_FUNC_ID(SUBSYSTEM, 8),
	HPI_SUBSYS_DRIVER_UNLOAD = HPI_FUNC_ID(SUBSYSTEM, 9),
	HPI_SUBSYS_GET_NUM_ADAPTERS = HPI_FUNC_ID(SUBSYSTEM, 12),
	HPI_SUBSYS_GET_ADAPTER = HPI_FUNC_ID(SUBSYSTEM, 13),
	HPI_SUBSYS_SET_NETWORK_INTERFACE = HPI_FUNC_ID(SUBSYSTEM, 14),
	HPI_SUBSYS_OPTION_INFO = HPI_FUNC_ID(SUBSYSTEM, 15),
	HPI_SUBSYS_OPTION_GET = HPI_FUNC_ID(SUBSYSTEM, 16),
	HPI_SUBSYS_OPTION_SET = HPI_FUNC_ID(SUBSYSTEM, 17),
#घोषणा HPI_SUBSYS_FUNCTION_COUNT 17

	HPI_ADAPTER_OPEN = HPI_FUNC_ID(ADAPTER, 1),
	HPI_ADAPTER_CLOSE = HPI_FUNC_ID(ADAPTER, 2),
	HPI_ADAPTER_GET_INFO = HPI_FUNC_ID(ADAPTER, 3),
	HPI_ADAPTER_GET_ASSERT = HPI_FUNC_ID(ADAPTER, 4),
	HPI_ADAPTER_TEST_ASSERT = HPI_FUNC_ID(ADAPTER, 5),
	HPI_ADAPTER_SET_MODE = HPI_FUNC_ID(ADAPTER, 6),
	HPI_ADAPTER_GET_MODE = HPI_FUNC_ID(ADAPTER, 7),
	HPI_ADAPTER_ENABLE_CAPABILITY = HPI_FUNC_ID(ADAPTER, 8),
	HPI_ADAPTER_SELFTEST = HPI_FUNC_ID(ADAPTER, 9),
	HPI_ADAPTER_FIND_OBJECT = HPI_FUNC_ID(ADAPTER, 10),
	HPI_ADAPTER_QUERY_FLASH = HPI_FUNC_ID(ADAPTER, 11),
	HPI_ADAPTER_START_FLASH = HPI_FUNC_ID(ADAPTER, 12),
	HPI_ADAPTER_PROGRAM_FLASH = HPI_FUNC_ID(ADAPTER, 13),
	HPI_ADAPTER_SET_PROPERTY = HPI_FUNC_ID(ADAPTER, 14),
	HPI_ADAPTER_GET_PROPERTY = HPI_FUNC_ID(ADAPTER, 15),
	HPI_ADAPTER_ENUM_PROPERTY = HPI_FUNC_ID(ADAPTER, 16),
	HPI_ADAPTER_MODULE_INFO = HPI_FUNC_ID(ADAPTER, 17),
	HPI_ADAPTER_DEBUG_READ = HPI_FUNC_ID(ADAPTER, 18),
	HPI_ADAPTER_IRQ_QUERY_AND_CLEAR = HPI_FUNC_ID(ADAPTER, 19),
	HPI_ADAPTER_IRQ_CALLBACK = HPI_FUNC_ID(ADAPTER, 20),
	HPI_ADAPTER_DELETE = HPI_FUNC_ID(ADAPTER, 21),
	HPI_ADAPTER_READ_FLASH = HPI_FUNC_ID(ADAPTER, 22),
	HPI_ADAPTER_END_FLASH = HPI_FUNC_ID(ADAPTER, 23),
	HPI_ADAPTER_खाताSTORE_DELETE_ALL = HPI_FUNC_ID(ADAPTER, 24),
#घोषणा HPI_ADAPTER_FUNCTION_COUNT 24

	HPI_OSTREAM_OPEN = HPI_FUNC_ID(OSTREAM, 1),
	HPI_OSTREAM_CLOSE = HPI_FUNC_ID(OSTREAM, 2),
	HPI_OSTREAM_WRITE = HPI_FUNC_ID(OSTREAM, 3),
	HPI_OSTREAM_START = HPI_FUNC_ID(OSTREAM, 4),
	HPI_OSTREAM_STOP = HPI_FUNC_ID(OSTREAM, 5),
	HPI_OSTREAM_RESET = HPI_FUNC_ID(OSTREAM, 6),
	HPI_OSTREAM_GET_INFO = HPI_FUNC_ID(OSTREAM, 7),
	HPI_OSTREAM_QUERY_FORMAT = HPI_FUNC_ID(OSTREAM, 8),
	HPI_OSTREAM_DATA = HPI_FUNC_ID(OSTREAM, 9),
	HPI_OSTREAM_SET_VELOCITY = HPI_FUNC_ID(OSTREAM, 10),
	HPI_OSTREAM_SET_PUNCHINOUT = HPI_FUNC_ID(OSTREAM, 11),
	HPI_OSTREAM_SINEGEN = HPI_FUNC_ID(OSTREAM, 12),
	HPI_OSTREAM_ANC_RESET = HPI_FUNC_ID(OSTREAM, 13),
	HPI_OSTREAM_ANC_GET_INFO = HPI_FUNC_ID(OSTREAM, 14),
	HPI_OSTREAM_ANC_READ = HPI_FUNC_ID(OSTREAM, 15),
	HPI_OSTREAM_SET_TIMESCALE = HPI_FUNC_ID(OSTREAM, 16),
	HPI_OSTREAM_SET_FORMAT = HPI_FUNC_ID(OSTREAM, 17),
	HPI_OSTREAM_HOSTBUFFER_ALLOC = HPI_FUNC_ID(OSTREAM, 18),
	HPI_OSTREAM_HOSTBUFFER_FREE = HPI_FUNC_ID(OSTREAM, 19),
	HPI_OSTREAM_GROUP_ADD = HPI_FUNC_ID(OSTREAM, 20),
	HPI_OSTREAM_GROUP_GETMAP = HPI_FUNC_ID(OSTREAM, 21),
	HPI_OSTREAM_GROUP_RESET = HPI_FUNC_ID(OSTREAM, 22),
	HPI_OSTREAM_HOSTBUFFER_GET_INFO = HPI_FUNC_ID(OSTREAM, 23),
	HPI_OSTREAM_WAIT_START = HPI_FUNC_ID(OSTREAM, 24),
	HPI_OSTREAM_WAIT = HPI_FUNC_ID(OSTREAM, 25),
#घोषणा HPI_OSTREAM_FUNCTION_COUNT 25

	HPI_ISTREAM_OPEN = HPI_FUNC_ID(ISTREAM, 1),
	HPI_ISTREAM_CLOSE = HPI_FUNC_ID(ISTREAM, 2),
	HPI_ISTREAM_SET_FORMAT = HPI_FUNC_ID(ISTREAM, 3),
	HPI_ISTREAM_READ = HPI_FUNC_ID(ISTREAM, 4),
	HPI_ISTREAM_START = HPI_FUNC_ID(ISTREAM, 5),
	HPI_ISTREAM_STOP = HPI_FUNC_ID(ISTREAM, 6),
	HPI_ISTREAM_RESET = HPI_FUNC_ID(ISTREAM, 7),
	HPI_ISTREAM_GET_INFO = HPI_FUNC_ID(ISTREAM, 8),
	HPI_ISTREAM_QUERY_FORMAT = HPI_FUNC_ID(ISTREAM, 9),
	HPI_ISTREAM_ANC_RESET = HPI_FUNC_ID(ISTREAM, 10),
	HPI_ISTREAM_ANC_GET_INFO = HPI_FUNC_ID(ISTREAM, 11),
	HPI_ISTREAM_ANC_WRITE = HPI_FUNC_ID(ISTREAM, 12),
	HPI_ISTREAM_HOSTBUFFER_ALLOC = HPI_FUNC_ID(ISTREAM, 13),
	HPI_ISTREAM_HOSTBUFFER_FREE = HPI_FUNC_ID(ISTREAM, 14),
	HPI_ISTREAM_GROUP_ADD = HPI_FUNC_ID(ISTREAM, 15),
	HPI_ISTREAM_GROUP_GETMAP = HPI_FUNC_ID(ISTREAM, 16),
	HPI_ISTREAM_GROUP_RESET = HPI_FUNC_ID(ISTREAM, 17),
	HPI_ISTREAM_HOSTBUFFER_GET_INFO = HPI_FUNC_ID(ISTREAM, 18),
	HPI_ISTREAM_WAIT_START = HPI_FUNC_ID(ISTREAM, 19),
	HPI_ISTREAM_WAIT = HPI_FUNC_ID(ISTREAM, 20),
#घोषणा HPI_ISTREAM_FUNCTION_COUNT 20

/* NOTE:
   GET_NODE_INFO, SET_CONNECTION, GET_CONNECTIONS are not currently used */
	HPI_MIXER_OPEN = HPI_FUNC_ID(MIXER, 1),
	HPI_MIXER_CLOSE = HPI_FUNC_ID(MIXER, 2),
	HPI_MIXER_GET_INFO = HPI_FUNC_ID(MIXER, 3),
	HPI_MIXER_GET_NODE_INFO = HPI_FUNC_ID(MIXER, 4),
	HPI_MIXER_GET_CONTROL = HPI_FUNC_ID(MIXER, 5),
	HPI_MIXER_SET_CONNECTION = HPI_FUNC_ID(MIXER, 6),
	HPI_MIXER_GET_CONNECTIONS = HPI_FUNC_ID(MIXER, 7),
	HPI_MIXER_GET_CONTROL_BY_INDEX = HPI_FUNC_ID(MIXER, 8),
	HPI_MIXER_GET_CONTROL_ARRAY_BY_INDEX = HPI_FUNC_ID(MIXER, 9),
	HPI_MIXER_GET_CONTROL_MULTIPLE_VALUES = HPI_FUNC_ID(MIXER, 10),
	HPI_MIXER_STORE = HPI_FUNC_ID(MIXER, 11),
	HPI_MIXER_GET_CACHE_INFO = HPI_FUNC_ID(MIXER, 12),
	HPI_MIXER_GET_BLOCK_HANDLE = HPI_FUNC_ID(MIXER, 13),
	HPI_MIXER_GET_PARAMETER_HANDLE = HPI_FUNC_ID(MIXER, 14),
#घोषणा HPI_MIXER_FUNCTION_COUNT 14

	HPI_CONTROL_GET_INFO = HPI_FUNC_ID(CONTROL, 1),
	HPI_CONTROL_GET_STATE = HPI_FUNC_ID(CONTROL, 2),
	HPI_CONTROL_SET_STATE = HPI_FUNC_ID(CONTROL, 3),
#घोषणा HPI_CONTROL_FUNCTION_COUNT 3

	HPI_NVMEMORY_OPEN = HPI_FUNC_ID(NVMEMORY, 1),
	HPI_NVMEMORY_READ_BYTE = HPI_FUNC_ID(NVMEMORY, 2),
	HPI_NVMEMORY_WRITE_BYTE = HPI_FUNC_ID(NVMEMORY, 3),
#घोषणा HPI_NVMEMORY_FUNCTION_COUNT 3

	HPI_GPIO_OPEN = HPI_FUNC_ID(GPIO, 1),
	HPI_GPIO_READ_BIT = HPI_FUNC_ID(GPIO, 2),
	HPI_GPIO_WRITE_BIT = HPI_FUNC_ID(GPIO, 3),
	HPI_GPIO_READ_ALL = HPI_FUNC_ID(GPIO, 4),
	HPI_GPIO_WRITE_STATUS = HPI_FUNC_ID(GPIO, 5),
#घोषणा HPI_GPIO_FUNCTION_COUNT 5

	HPI_ASYNCEVENT_OPEN = HPI_FUNC_ID(ASYNCEVENT, 1),
	HPI_ASYNCEVENT_CLOSE = HPI_FUNC_ID(ASYNCEVENT, 2),
	HPI_ASYNCEVENT_WAIT = HPI_FUNC_ID(ASYNCEVENT, 3),
	HPI_ASYNCEVENT_GETCOUNT = HPI_FUNC_ID(ASYNCEVENT, 4),
	HPI_ASYNCEVENT_GET = HPI_FUNC_ID(ASYNCEVENT, 5),
	HPI_ASYNCEVENT_SENDEVENTS = HPI_FUNC_ID(ASYNCEVENT, 6),
#घोषणा HPI_ASYNCEVENT_FUNCTION_COUNT 6

	HPI_WATCHDOG_OPEN = HPI_FUNC_ID(WATCHDOG, 1),
	HPI_WATCHDOG_SET_TIME = HPI_FUNC_ID(WATCHDOG, 2),
	HPI_WATCHDOG_PING = HPI_FUNC_ID(WATCHDOG, 3),

	HPI_CLOCK_OPEN = HPI_FUNC_ID(CLOCK, 1),
	HPI_CLOCK_SET_TIME = HPI_FUNC_ID(CLOCK, 2),
	HPI_CLOCK_GET_TIME = HPI_FUNC_ID(CLOCK, 3),

	HPI_PROखाता_OPEN_ALL = HPI_FUNC_ID(PROखाता, 1),
	HPI_PROखाता_START_ALL = HPI_FUNC_ID(PROखाता, 2),
	HPI_PROखाता_STOP_ALL = HPI_FUNC_ID(PROखाता, 3),
	HPI_PROखाता_GET = HPI_FUNC_ID(PROखाता, 4),
	HPI_PROखाता_GET_IDLECOUNT = HPI_FUNC_ID(PROखाता, 5),
	HPI_PROखाता_GET_NAME = HPI_FUNC_ID(PROखाता, 6),
	HPI_PROखाता_GET_UTILIZATION = HPI_FUNC_ID(PROखाता, 7)
#घोषणा HPI_PROखाता_FUNCTION_COUNT 7
पूर्ण;

/* ////////////////////////////////////////////////////////////////////// */
/* STRUCTURES */
#अगर_अघोषित DISABLE_PRAGMA_PACK1
#आशय pack(push, 1)
#पूर्ण_अगर

/** PCI bus resource */
काष्ठा hpi_pci अणु
	u32 __iomem *ap_mem_base[HPI_MAX_ADAPTER_MEM_SPACES];
	काष्ठा pci_dev *pci_dev;
पूर्ण;

/** Adapter specअगरication resource */
काष्ठा hpi_adapter_specअगरication अणु
	u32 type;
	u8 modules[4];
पूर्ण;

काष्ठा hpi_resource अणु
	जोड़ अणु
		स्थिर काष्ठा hpi_pci *pci;
		स्थिर अक्षर *net_अगर;
		काष्ठा hpi_adapter_specअगरication adapter_spec;
		स्थिर व्योम *sw_अगर;
	पूर्ण r;
	u16 bus_type;		/* HPI_BUS_PNPISA, _PCI, _USB etc */
	u16 padding;
पूर्ण;

/** Format info used inside काष्ठा hpi_message
    Not the same as खुला API काष्ठा hpi_क्रमmat */
काष्ठा hpi_msg_क्रमmat अणु
	u32 sample_rate; /**< 11025, 32000, 44100 etc. */
	u32 bit_rate; /**< क्रम MPEG */
	u32 attributes;	/**< stereo/joपूर्णांक_stereo/mono */
	u16 channels; /**< 1,2..., (or ancillary mode or idle bit */
	u16 क्रमmat; /**< HPI_FORMAT_PCM16, _MPEG etc. see \लef HPI_FORMATS. */
पूर्ण;

/**  Buffer+क्रमmat काष्ठाure.
	 Must be kept 7 * 32 bits to match खुला काष्ठा hpi_dataकाष्ठा */
काष्ठा hpi_msg_data अणु
	काष्ठा hpi_msg_क्रमmat क्रमmat;
	u8 *pb_data;
#अगर_अघोषित CONFIG_64BIT
	u32 padding;
#पूर्ण_अगर
	u32 data_size;
पूर्ण;

/** काष्ठा hpi_dataकाष्ठाure used up to 3.04 driver */
काष्ठा hpi_data_legacy32 अणु
	काष्ठा hpi_क्रमmat क्रमmat;
	u32 pb_data;
	u32 data_size;
पूर्ण;

#अगर_घोषित CONFIG_64BIT
/* Compatibility version of काष्ठा hpi_data*/
काष्ठा hpi_data_compat32 अणु
	काष्ठा hpi_msg_क्रमmat क्रमmat;
	u32 pb_data;
	u32 padding;
	u32 data_size;
पूर्ण;
#पूर्ण_अगर

काष्ठा hpi_buffer अणु
  /** placeholder क्रम backward compatibility (see dwBufferSize) */
	काष्ठा hpi_msg_क्रमmat reserved;
	u32 command; /**< HPI_BUFFER_CMD_xxx*/
	u32 pci_address; /**< PCI physical address of buffer क्रम DSP DMA */
	u32 buffer_size; /**< must line up with data_size of HPI_DATA*/
पूर्ण;

/*/////////////////////////////////////////////////////////////////////////// */
/* This is used क्रम background buffer bus mastering stream buffers.           */
काष्ठा hpi_hostbuffer_status अणु
	u32 samples_processed;
	u32 auxiliary_data_available;
	u32 stream_state;
	/* DSP index in to the host bus master buffer. */
	u32 dsp_index;
	/* Host index in to the host bus master buffer. */
	u32 host_index;
	u32 size_in_bytes;
पूर्ण;

काष्ठा hpi_streamid अणु
	u16 object_type;
		    /**< Type of object, HPI_OBJ_OSTREAM or HPI_OBJ_ISTREAM. */
	u16 stream_index; /**< outstream or instream index. */
पूर्ण;

काष्ठा hpi_punchinout अणु
	u32 punch_in_sample;
	u32 punch_out_sample;
पूर्ण;

काष्ठा hpi_subsys_msg अणु
	काष्ठा hpi_resource resource;
पूर्ण;

काष्ठा hpi_subsys_res अणु
	u32 version;
	u32 data;		/* extended version */
	u16 num_adapters;
	u16 adapter_index;
	u16 adapter_type;
	u16 pad16;
पूर्ण;

जोड़ hpi_adapterx_msg अणु
	काष्ठा अणु
		u32 dsp_address;
		u32 count_bytes;
	पूर्ण debug_पढ़ो;
	काष्ठा अणु
		u32 adapter_mode;
		u16 query_or_set;
	पूर्ण mode;
	काष्ठा अणु
		u16 index;
	पूर्ण module_info;
	काष्ठा अणु
		u16 index;
		u16 what;
		u16 property_index;
	पूर्ण property_क्रमागत;
	काष्ठा अणु
		u16 property;
		u16 parameter1;
		u16 parameter2;
	पूर्ण property_set;
	काष्ठा अणु
		u32 pad32;
		u16 key1;
		u16 key2;
	पूर्ण restart;
	काष्ठा अणु
		u32 pad32;
		u16 value;
	पूर्ण test_निश्चित;
	काष्ठा अणु
		u32 message;
	पूर्ण irq;
	u32 pad[3];
पूर्ण;

काष्ठा hpi_adapter_res अणु
	u32 serial_number;
	u16 adapter_type;
	u16 adapter_index;
	u16 num_instreams;
	u16 num_outstreams;
	u16 num_mixers;
	u16 version;
	u8 sz_adapter_निश्चित[HPI_STRING_LEN];
पूर्ण;

जोड़ hpi_adapterx_res अणु
	काष्ठा hpi_adapter_res info;
	काष्ठा अणु
		u32 p1;
		u16 count;
		u16 dsp_index;
		u32 p2;
		u32 dsp_msg_addr;
		अक्षर sz_message[HPI_STRING_LEN];
	पूर्ण निश्चित;
	काष्ठा अणु
		u32 adapter_mode;
	पूर्ण mode;
	काष्ठा अणु
		u16 parameter1;
		u16 parameter2;
	पूर्ण property_get;
	काष्ठा अणु
		u32 yes;
	पूर्ण irq_query;
पूर्ण;

काष्ठा hpi_stream_msg अणु
	जोड़ अणु
		काष्ठा hpi_msg_data data;
		काष्ठा hpi_data_legacy32 data32;
		u16 velocity;
		काष्ठा hpi_punchinout pio;
		u32 समय_scale;
		काष्ठा hpi_buffer buffer;
		काष्ठा hpi_streamid stream;
		u32 threshold_bytes;
	पूर्ण u;
पूर्ण;

काष्ठा hpi_stream_res अणु
	जोड़ अणु
		काष्ठा अणु
			/* size of hardware buffer */
			u32 buffer_size;
			/* OutStream - data to play,
			   InStream - data recorded */
			u32 data_available;
			/* OutStream - samples played,
			   InStream - samples recorded */
			u32 samples_transferred;
			/* Adapter - OutStream - data to play,
			   InStream - data recorded */
			u32 auxiliary_data_available;
			u16 state;	/* HPI_STATE_PLAYING, _STATE_STOPPED */
			u16 padding;
		पूर्ण stream_info;
		काष्ठा अणु
			u32 buffer_size;
			u32 data_available;
			u32 samples_transfered;
			u16 state;
			u16 outstream_index;
			u16 instream_index;
			u16 padding;
			u32 auxiliary_data_available;
		पूर्ण legacy_stream_info;
		काष्ठा अणु
			/* biपंचांगap of grouped OutStreams */
			u32 outstream_group_map;
			/* biपंचांगap of grouped InStreams */
			u32 instream_group_map;
		पूर्ण group_info;
		काष्ठा अणु
			/* poपूर्णांकer to the buffer */
			u8 *p_buffer;
			/* poपूर्णांकer to the hostbuffer status */
			काष्ठा hpi_hostbuffer_status *p_status;
		पूर्ण hostbuffer_info;
	पूर्ण u;
पूर्ण;

काष्ठा hpi_mixer_msg अणु
	u16 control_index;
	u16 control_type;	/* = HPI_CONTROL_METER _VOLUME etc */
	u16 padding1;		/* Maपूर्णांकain alignment of subsequent fields */
	u16 node_type1;		/* = HPI_SOURCENODE_LINEIN etc */
	u16 node_index1;	/* = 0..N */
	u16 node_type2;
	u16 node_index2;
	u16 padding2;		/* round to 4 bytes */
पूर्ण;

काष्ठा hpi_mixer_res अणु
	u16 src_node_type;	/* = HPI_SOURCENODE_LINEIN etc */
	u16 src_node_index;	/* = 0..N */
	u16 dst_node_type;
	u16 dst_node_index;
	/* Also controlType क्रम MixerGetControlByIndex */
	u16 control_index;
	/* may indicate which DSP the control is located on */
	u16 dsp_index;
पूर्ण;

जोड़ hpi_mixerx_msg अणु
	काष्ठा अणु
		u16 starting_index;
		u16 flags;
		u32 length_in_bytes;	/* length in bytes of p_data */
		u32 p_data;	/* poपूर्णांकer to a data array */
	पूर्ण gcabi;
	काष्ठा अणु
		u16 command;
		u16 index;
	पूर्ण store;		/* क्रम HPI_MIXER_STORE message */
पूर्ण;

जोड़ hpi_mixerx_res अणु
	काष्ठा अणु
		u32 bytes_वापसed;	/* size of items वापसed */
		u32 p_data;	/* poपूर्णांकer to data array */
		u16 more_to_करो;	/* indicates अगर there is more to करो */
	पूर्ण gcabi;
	काष्ठा अणु
		u32 total_controls;	/* count of controls in the mixer */
		u32 cache_controls;	/* count of controls in the cac */
		u32 cache_bytes;	/* size of cache */
	पूर्ण cache_info;
पूर्ण;

काष्ठा hpi_control_msg अणु
	u16 attribute;		/* control attribute or property */
	u16 saved_index;
	u32 param1;		/* generic parameter 1 */
	u32 param2;		/* generic parameter 2 */
	लघु an_log_value[HPI_MAX_CHANNELS];
पूर्ण;

काष्ठा hpi_control_जोड़_msg अणु
	u16 attribute;		/* control attribute or property */
	u16 saved_index;	/* only used in ctrl save/restore */
	जोड़ अणु
		काष्ठा अणु
			u32 param1;	/* generic parameter 1 */
			u32 param2;	/* generic parameter 2 */
			लघु an_log_value[HPI_MAX_CHANNELS];
		पूर्ण old;
		जोड़ अणु
			u32 frequency;
			u32 gain;
			u32 band;
			u32 deemphasis;
			u32 program;
			काष्ठा अणु
				u32 mode;
				u32 value;
			पूर्ण mode;
			u32 blend;
		पूर्ण tuner;
	पूर्ण u;
पूर्ण;

काष्ठा hpi_control_res अणु
	/* Could make जोड़. dwParam, anLogValue never used in same response */
	u32 param1;
	u32 param2;
	लघु an_log_value[HPI_MAX_CHANNELS];
पूर्ण;

जोड़ hpi_control_जोड़_res अणु
	काष्ठा अणु
		u32 param1;
		u32 param2;
		लघु an_log_value[HPI_MAX_CHANNELS];
	पूर्ण old;
	जोड़ अणु
		u32 band;
		u32 frequency;
		u32 gain;
		u32 deemphasis;
		काष्ठा अणु
			u32 data[2];
			u32 bLER;
		पूर्ण rds;
		लघु s_level;
		काष्ठा अणु
			u16 value;
			u16 mask;
		पूर्ण status;
	पूर्ण tuner;
	काष्ठा अणु
		अक्षर sz_data[8];
		u32 reमुख्यing_अक्षरs;
	पूर्ण अक्षरs8;
	अक्षर c_data12[12];
	जोड़ अणु
		काष्ठा अणु
			u32 status;
			u32 पढ़ोable_size;
			u32 ग_लिखोable_size;
		पूर्ण status;
	पूर्ण cobranet;
पूर्ण;

काष्ठा hpi_nvmemory_msg अणु
	u16 address;
	u16 data;
पूर्ण;

काष्ठा hpi_nvmemory_res अणु
	u16 size_in_bytes;
	u16 data;
पूर्ण;

काष्ठा hpi_gpio_msg अणु
	u16 bit_index;
	u16 bit_data;
पूर्ण;

काष्ठा hpi_gpio_res अणु
	u16 number_input_bits;
	u16 number_output_bits;
	u16 bit_data[4];
पूर्ण;

काष्ठा hpi_async_msg अणु
	u32 events;
	u16 maximum_events;
	u16 padding;
पूर्ण;

काष्ठा hpi_async_res अणु
	जोड़ अणु
		काष्ठा अणु
			u16 count;
		पूर्ण count;
		काष्ठा अणु
			u32 events;
			u16 number_वापसed;
			u16 padding;
		पूर्ण get;
		काष्ठा hpi_async_event event;
	पूर्ण u;
पूर्ण;

काष्ठा hpi_watchकरोg_msg अणु
	u32 समय_ms;
पूर्ण;

काष्ठा hpi_watchकरोg_res अणु
	u32 समय_ms;
पूर्ण;

काष्ठा hpi_घड़ी_msg अणु
	u16 hours;
	u16 minutes;
	u16 seconds;
	u16 milli_seconds;
पूर्ण;

काष्ठा hpi_घड़ी_res अणु
	u16 size_in_bytes;
	u16 hours;
	u16 minutes;
	u16 seconds;
	u16 milli_seconds;
	u16 padding;
पूर्ण;

काष्ठा hpi_profile_msg अणु
	u16 bin_index;
	u16 padding;
पूर्ण;

काष्ठा hpi_profile_res_खोलो अणु
	u16 max_profiles;
पूर्ण;

काष्ठा hpi_profile_res_समय अणु
	u32 total_tick_count;
	u32 call_count;
	u32 max_tick_count;
	u32 ticks_per_millisecond;
	u16 profile_पूर्णांकerval;
पूर्ण;

काष्ठा hpi_profile_res_name अणु
	u8 sz_name[32];
पूर्ण;

काष्ठा hpi_profile_res अणु
	जोड़ अणु
		काष्ठा hpi_profile_res_खोलो o;
		काष्ठा hpi_profile_res_समय t;
		काष्ठा hpi_profile_res_name n;
	पूर्ण u;
पूर्ण;

काष्ठा hpi_message_header अणु
	u16 size;		/* total size in bytes */
	u8 type;		/* HPI_TYPE_MESSAGE  */
	u8 version;		/* message version */
	u16 object;		/* HPI_OBJ_* */
	u16 function;		/* HPI_SUBSYS_xxx, HPI_ADAPTER_xxx */
	u16 adapter_index;	/* the adapter index */
	u16 obj_index;		/* */
पूर्ण;

काष्ठा hpi_message अणु
	/* following fields must match HPI_MESSAGE_HEADER */
	u16 size;		/* total size in bytes */
	u8 type;		/* HPI_TYPE_MESSAGE  */
	u8 version;		/* message version */
	u16 object;		/* HPI_OBJ_* */
	u16 function;		/* HPI_SUBSYS_xxx, HPI_ADAPTER_xxx */
	u16 adapter_index;	/* the adapter index */
	u16 obj_index;		/*  */
	जोड़ अणु
		काष्ठा hpi_subsys_msg s;
		जोड़ hpi_adapterx_msg ax;
		काष्ठा hpi_stream_msg d;
		काष्ठा hpi_mixer_msg m;
		जोड़ hpi_mixerx_msg mx;	/* extended mixer; */
		काष्ठा hpi_control_msg c;	/* mixer control; */
		/* identical to काष्ठा hpi_control_msg,
		   but field naming is improved */
		काष्ठा hpi_control_जोड़_msg cu;
		काष्ठा hpi_nvmemory_msg n;
		काष्ठा hpi_gpio_msg l;	/* digital i/o */
		काष्ठा hpi_watchकरोg_msg w;
		काष्ठा hpi_घड़ी_msg t;	/* dsp समय */
		काष्ठा hpi_profile_msg p;
		काष्ठा hpi_async_msg as;
		अक्षर fixed_size[32];
	पूर्ण u;
पूर्ण;

#घोषणा HPI_MESSAGE_SIZE_BY_OBJECT अणु \
	माप(काष्ठा hpi_message_header) ,   /* Default, no object type 0 */ \
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_subsys_msg),\
	माप(काष्ठा hpi_message_header) + माप(जोड़ hpi_adapterx_msg),\
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_stream_msg),\
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_stream_msg),\
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_mixer_msg),\
	माप(काष्ठा hpi_message_header) ,   /* no node message */ \
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_control_msg),\
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_nvmemory_msg),\
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_gpio_msg),\
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_watchकरोg_msg),\
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_घड़ी_msg),\
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_profile_msg),\
	माप(काष्ठा hpi_message_header), /* controlx obj हटाओd */ \
	माप(काष्ठा hpi_message_header) + माप(काष्ठा hpi_async_msg) \
पूर्ण

/*
Note that the wSpecअगरicError error field should be inspected and potentially
reported whenever HPI_ERROR_DSP_COMMUNICATION or HPI_ERROR_DSP_BOOTLOAD is
वापसed in wError.
*/
काष्ठा hpi_response_header अणु
	u16 size;
	u8 type;		/* HPI_TYPE_RESPONSE  */
	u8 version;		/* response version */
	u16 object;		/* HPI_OBJ_* */
	u16 function;		/* HPI_SUBSYS_xxx, HPI_ADAPTER_xxx */
	u16 error;		/* HPI_ERROR_xxx */
	u16 specअगरic_error;	/* adapter specअगरic error */
पूर्ण;

काष्ठा hpi_response अणु
/* following fields must match HPI_RESPONSE_HEADER */
	u16 size;
	u8 type;		/* HPI_TYPE_RESPONSE  */
	u8 version;		/* response version */
	u16 object;		/* HPI_OBJ_* */
	u16 function;		/* HPI_SUBSYS_xxx, HPI_ADAPTER_xxx */
	u16 error;		/* HPI_ERROR_xxx */
	u16 specअगरic_error;	/* adapter specअगरic error */
	जोड़ अणु
		काष्ठा hpi_subsys_res s;
		जोड़ hpi_adapterx_res ax;
		काष्ठा hpi_stream_res d;
		काष्ठा hpi_mixer_res m;
		जोड़ hpi_mixerx_res mx;	/* extended mixer; */
		काष्ठा hpi_control_res c;	/* mixer control; */
		/* identical to hpi_control_res, but field naming is improved */
		जोड़ hpi_control_जोड़_res cu;
		काष्ठा hpi_nvmemory_res n;
		काष्ठा hpi_gpio_res l;	/* digital i/o */
		काष्ठा hpi_watchकरोg_res w;
		काष्ठा hpi_घड़ी_res t;	/* dsp समय */
		काष्ठा hpi_profile_res p;
		काष्ठा hpi_async_res as;
		u8 bytes[52];
	पूर्ण u;
पूर्ण;

#घोषणा HPI_RESPONSE_SIZE_BY_OBJECT अणु \
	माप(काष्ठा hpi_response_header) ,/* Default, no object type 0 */ \
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_subsys_res),\
	माप(काष्ठा hpi_response_header) + माप(जोड़  hpi_adapterx_res),\
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_stream_res),\
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_stream_res),\
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_mixer_res),\
	माप(काष्ठा hpi_response_header) , /* no node response */ \
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_control_res),\
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_nvmemory_res),\
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_gpio_res),\
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_watchकरोg_res),\
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_घड़ी_res),\
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_profile_res),\
	माप(काष्ठा hpi_response_header), /* controlx obj हटाओd */ \
	माप(काष्ठा hpi_response_header) + माप(काष्ठा hpi_async_res) \
पूर्ण

/*********************** version 1 message/response **************************/
#घोषणा HPINET_ETHERNET_DATA_SIZE (1500)
#घोषणा HPINET_IP_HDR_SIZE (20)
#घोषणा HPINET_IP_DATA_SIZE (HPINET_ETHERNET_DATA_SIZE - HPINET_IP_HDR_SIZE)
#घोषणा HPINET_UDP_HDR_SIZE (8)
#घोषणा HPINET_UDP_DATA_SIZE (HPINET_IP_DATA_SIZE - HPINET_UDP_HDR_SIZE)
#घोषणा HPINET_ASI_HDR_SIZE (2)
#घोषणा HPINET_ASI_DATA_SIZE (HPINET_UDP_DATA_SIZE - HPINET_ASI_HDR_SIZE)

#घोषणा HPI_MAX_PAYLOAD_SIZE (HPINET_ASI_DATA_SIZE - 2)

/* New style message/response, but still V0 compatible */
काष्ठा hpi_msg_adapter_get_info अणु
	काष्ठा hpi_message_header h;
पूर्ण;

काष्ठा hpi_res_adapter_get_info अणु
	काष्ठा hpi_response_header h;	/*v0 */
	काष्ठा hpi_adapter_res p;
पूर्ण;

काष्ठा hpi_res_adapter_debug_पढ़ो अणु
	काष्ठा hpi_response_header h;
	u8 bytes[1024];
पूर्ण;

काष्ठा hpi_msg_cobranet_hmi अणु
	u16 attribute;
	u16 padding;
	u32 hmi_address;
	u32 byte_count;
पूर्ण;

काष्ठा hpi_msg_cobranet_hmiग_लिखो अणु
	काष्ठा hpi_message_header h;
	काष्ठा hpi_msg_cobranet_hmi p;
	u8 bytes[256];
पूर्ण;

काष्ठा hpi_msg_cobranet_hmiपढ़ो अणु
	काष्ठा hpi_message_header h;
	काष्ठा hpi_msg_cobranet_hmi p;
पूर्ण;

काष्ठा hpi_res_cobranet_hmiपढ़ो अणु
	काष्ठा hpi_response_header h;
	u32 byte_count;
	u8 bytes[256];
पूर्ण;

#अगर 1
#घोषणा hpi_message_header_v1 hpi_message_header
#घोषणा hpi_response_header_v1 hpi_response_header
#अन्यथा
/* V1 headers in Addition to v0 headers */
काष्ठा hpi_message_header_v1 अणु
	काष्ठा hpi_message_header h0;
/* काष्ठा अणु
पूर्ण h1; */
पूर्ण;

काष्ठा hpi_response_header_v1 अणु
	काष्ठा hpi_response_header h0;
	काष्ठा अणु
		u16 adapter_index;	/* the adapter index */
		u16 obj_index;	/* object index */
	पूर्ण h1;
पूर्ण;
#पूर्ण_अगर

काष्ठा hpi_msg_payload_v0 अणु
	काष्ठा hpi_message_header h;
	जोड़ अणु
		काष्ठा hpi_subsys_msg s;
		जोड़ hpi_adapterx_msg ax;
		काष्ठा hpi_stream_msg d;
		काष्ठा hpi_mixer_msg m;
		जोड़ hpi_mixerx_msg mx;
		काष्ठा hpi_control_msg c;
		काष्ठा hpi_control_जोड़_msg cu;
		काष्ठा hpi_nvmemory_msg n;
		काष्ठा hpi_gpio_msg l;
		काष्ठा hpi_watchकरोg_msg w;
		काष्ठा hpi_घड़ी_msg t;
		काष्ठा hpi_profile_msg p;
		काष्ठा hpi_async_msg as;
	पूर्ण u;
पूर्ण;

काष्ठा hpi_res_payload_v0 अणु
	काष्ठा hpi_response_header h;
	जोड़ अणु
		काष्ठा hpi_subsys_res s;
		जोड़ hpi_adapterx_res ax;
		काष्ठा hpi_stream_res d;
		काष्ठा hpi_mixer_res m;
		जोड़ hpi_mixerx_res mx;
		काष्ठा hpi_control_res c;
		जोड़ hpi_control_जोड़_res cu;
		काष्ठा hpi_nvmemory_res n;
		काष्ठा hpi_gpio_res l;
		काष्ठा hpi_watchकरोg_res w;
		काष्ठा hpi_घड़ी_res t;
		काष्ठा hpi_profile_res p;
		काष्ठा hpi_async_res as;
	पूर्ण u;
पूर्ण;

जोड़ hpi_message_buffer_v1 अणु
	काष्ठा hpi_message m0;	/* version 0 */
	काष्ठा hpi_message_header_v1 h;
	u8 buf[HPI_MAX_PAYLOAD_SIZE];
पूर्ण;

जोड़ hpi_response_buffer_v1 अणु
	काष्ठा hpi_response r0;	/* version 0 */
	काष्ठा hpi_response_header_v1 h;
	u8 buf[HPI_MAX_PAYLOAD_SIZE];
पूर्ण;

compile_समय_निश्चित((माप(जोड़ hpi_message_buffer_v1) <=
		HPI_MAX_PAYLOAD_SIZE), message_buffer_ok);
compile_समय_निश्चित((माप(जोड़ hpi_response_buffer_v1) <=
		HPI_MAX_PAYLOAD_SIZE), response_buffer_ok);

/*////////////////////////////////////////////////////////////////////////// */
/* declarations क्रम compact control calls  */
काष्ठा hpi_control_defn अणु
	u8 type;
	u8 channels;
	u8 src_node_type;
	u8 src_node_index;
	u8 dest_node_type;
	u8 dest_node_index;
पूर्ण;

/*////////////////////////////////////////////////////////////////////////// */
/* declarations क्रम control caching (पूर्णांकernal to HPI<->DSP पूर्णांकeraction)      */

/** indicates a cached u16 value is invalid. */
#घोषणा HPI_CACHE_INVALID_UINT16 0xFFFF
/** indicates a cached लघु value is invalid. */
#घोषणा HPI_CACHE_INVALID_SHORT -32768

/** A compact representation of (part of) a controls state.
Used क्रम efficient transfer of the control state
between DSP and host or across a network
*/
काष्ठा hpi_control_cache_info अणु
	/** one of HPI_CONTROL_* */
	u8 control_type;
	/** The total size of cached inक्रमmation in 32-bit words. */
	u8 size_in32bit_words;
	/** The original index of the control on the DSP */
	u16 control_index;
पूर्ण;

काष्ठा hpi_control_cache_vol अणु
	काष्ठा hpi_control_cache_info i;
	लघु an_log[2];
	अचिन्हित लघु flags;
	अक्षर padding[2];
पूर्ण;

काष्ठा hpi_control_cache_meter अणु
	काष्ठा hpi_control_cache_info i;
	लघु an_log_peak[2];
	लघु an_logRMS[2];
पूर्ण;

काष्ठा hpi_control_cache_channelmode अणु
	काष्ठा hpi_control_cache_info i;
	u16 mode;
	अक्षर temp_padding[6];
पूर्ण;

काष्ठा hpi_control_cache_mux अणु
	काष्ठा hpi_control_cache_info i;
	u16 source_node_type;
	u16 source_node_index;
	अक्षर temp_padding[4];
पूर्ण;

काष्ठा hpi_control_cache_level अणु
	काष्ठा hpi_control_cache_info i;
	लघु an_log[2];
	अक्षर temp_padding[4];
पूर्ण;

काष्ठा hpi_control_cache_tuner अणु
	काष्ठा hpi_control_cache_info i;
	u32 freq_ink_hz;
	u16 band;
	लघु s_level_avg;
पूर्ण;

काष्ठा hpi_control_cache_aes3rx अणु
	काष्ठा hpi_control_cache_info i;
	u32 error_status;
	u32 क्रमmat;
पूर्ण;

काष्ठा hpi_control_cache_aes3tx अणु
	काष्ठा hpi_control_cache_info i;
	u32 क्रमmat;
	अक्षर temp_padding[4];
पूर्ण;

काष्ठा hpi_control_cache_tonedetector अणु
	काष्ठा hpi_control_cache_info i;
	u16 state;
	अक्षर temp_padding[6];
पूर्ण;

काष्ठा hpi_control_cache_silencedetector अणु
	काष्ठा hpi_control_cache_info i;
	u32 state;
	अक्षर temp_padding[4];
पूर्ण;

काष्ठा hpi_control_cache_sampleघड़ी अणु
	काष्ठा hpi_control_cache_info i;
	u16 source;
	u16 source_index;
	u32 sample_rate;
पूर्ण;

काष्ठा hpi_control_cache_microphone अणु
	काष्ठा hpi_control_cache_info i;
	u16 phantom_state;
	अक्षर temp_padding[6];
पूर्ण;

काष्ठा hpi_control_cache_single अणु
	जोड़ अणु
		काष्ठा hpi_control_cache_info i;
		काष्ठा hpi_control_cache_vol vol;
		काष्ठा hpi_control_cache_meter meter;
		काष्ठा hpi_control_cache_channelmode mode;
		काष्ठा hpi_control_cache_mux mux;
		काष्ठा hpi_control_cache_level level;
		काष्ठा hpi_control_cache_tuner tuner;
		काष्ठा hpi_control_cache_aes3rx aes3rx;
		काष्ठा hpi_control_cache_aes3tx aes3tx;
		काष्ठा hpi_control_cache_tonedetector tone;
		काष्ठा hpi_control_cache_silencedetector silence;
		काष्ठा hpi_control_cache_sampleघड़ी clk;
		काष्ठा hpi_control_cache_microphone microphone;
	पूर्ण u;
पूर्ण;

काष्ठा hpi_control_cache_pad अणु
	काष्ठा hpi_control_cache_info i;
	u32 field_valid_flags;
	u8 c_channel[40];
	u8 c_artist[100];
	u8 c_title[100];
	u8 c_comment[200];
	u32 pTY;
	u32 pI;
	u32 traffic_supported;
	u32 traffic_anouncement;
पूर्ण;

/* 2^N sized FIFO buffer (पूर्णांकernal to HPI<->DSP पूर्णांकeraction) */
काष्ठा hpi_fअगरo_buffer अणु
	u32 size;
	u32 dsp_index;
	u32 host_index;
पूर्ण;

#अगर_अघोषित DISABLE_PRAGMA_PACK1
#आशय pack(pop)
#पूर्ण_अगर

/* skip host side function declarations क्रम DSP
   compile and करोcumentation extraction */

अक्षर hpi_handle_object(स्थिर u32 handle);

व्योम hpi_handle_to_indexes(स्थिर u32 handle, u16 *pw_adapter_index,
	u16 *pw_object_index);

u32 hpi_indexes_to_handle(स्थिर अक्षर c_object, स्थिर u16 adapter_index,
	स्थिर u16 object_index);

/*////////////////////////////////////////////////////////////////////////// */

/* मुख्य HPI entry poपूर्णांक */
व्योम hpi_send_recv(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

/* used in PnP OS/driver */
u16 hpi_subsys_create_adapter(स्थिर काष्ठा hpi_resource *p_resource,
	u16 *pw_adapter_index);

u16 hpi_outstream_host_buffer_get_info(u32 h_outstream, u8 **pp_buffer,
	काष्ठा hpi_hostbuffer_status **pp_status);

u16 hpi_instream_host_buffer_get_info(u32 h_instream, u8 **pp_buffer,
	काष्ठा hpi_hostbuffer_status **pp_status);

u16 hpi_adapter_restart(u16 adapter_index);

/*
The following 3 functions were last declared in header files क्रम
driver 3.10. HPI_ControlQuery() used to be the recommended way
of getting a volume range. Declared here क्रम binary asihpi32.dll
compatibility.
*/

व्योम hpi_क्रमmat_to_msg(काष्ठा hpi_msg_क्रमmat *pMF,
	स्थिर काष्ठा hpi_क्रमmat *pF);
व्योम hpi_stream_response_to_legacy(काष्ठा hpi_stream_res *pSR);

/*////////////////////////////////////////////////////////////////////////// */
/* declarations क्रम inभागidual HPI entry poपूर्णांकs */
hpi_handler_func HPI_6000;
hpi_handler_func HPI_6205;

#पूर्ण_अगर				/* _HPI_INTERNAL_H_ */
