<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2021 Linaro Ltd.
 */
#अगर_अघोषित _IPA_DATA_H_
#घोषणा _IPA_DATA_H_

#समावेश <linux/types.h>

#समावेश "ipa_version.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_mem.h"

/**
 * DOC: IPA/GSI Configuration Data
 *
 * Boot-समय configuration data is used to define the configuration of the
 * IPA and GSI resources to use क्रम a given platक्रमm.  This data is supplied
 * via the Device Tree match table, associated with a particular compatible
 * string.  The data defines inक्रमmation about how resources, endpoपूर्णांकs and
 * channels, memory, घड़ीing and so on are allocated and used क्रम the
 * platक्रमm.
 *
 * Resources are data काष्ठाures used पूर्णांकernally by the IPA hardware.  The
 * configuration data defines the number (or limits of the number) of various
 * types of these resources.
 *
 * Endpoपूर्णांक configuration data defines properties of both IPA endpoपूर्णांकs and
 * GSI channels.  A channel is a GSI स्थिरruct, and represents a single
 * communication path between the IPA and a particular execution environment
 * (EE), such as the AP or Modem.  Each EE has a set of channels associated
 * with it, and each channel has an ID unique क्रम that EE.  For the most part
 * the only GSI channels of concern to this driver beदीर्घ to the AP
 *
 * An endpoपूर्णांक is an IPA स्थिरruct representing a single channel anywhere
 * in the प्रणाली.  An IPA endpoपूर्णांक ID maps directly to an (EE, channel_id)
 * pair.  Generally, this driver is concerned with only endpoपूर्णांकs associated
 * with the AP, however this will change when support क्रम routing (etc.) is
 * added.  IPA endpoपूर्णांक and GSI channel configuration data are defined
 * together, establishing the endpoपूर्णांक_id->(EE, channel_id) mapping.
 *
 * Endpoपूर्णांक configuration data consists of three parts:  properties that
 * are common to IPA and GSI (EE ID, channel ID, endpoपूर्णांक ID, and direction);
 * properties associated with the GSI channel; and properties associated with
 * the IPA endpoपूर्णांक.
 */

/* The maximum possible number of source or destination resource groups */
#घोषणा IPA_RESOURCE_GROUP_MAX	8

/** क्रमागत ipa_qsb_master_id - array index क्रम IPA QSB configuration data */
क्रमागत ipa_qsb_master_id अणु
	IPA_QSB_MASTER_DDR,
	IPA_QSB_MASTER_PCIE,
पूर्ण;

/**
 * काष्ठा ipa_qsb_data - Qualcomm System Bus configuration data
 * @max_ग_लिखोs:	Maximum outstanding ग_लिखो requests क्रम this master
 * @max_पढ़ोs:	Maximum outstanding पढ़ो requests क्रम this master
 * @max_पढ़ोs_beats: Max outstanding पढ़ो bytes in 8-byte "beats" (अगर non-zero)
 */
काष्ठा ipa_qsb_data अणु
	u8 max_ग_लिखोs;
	u8 max_पढ़ोs;
	u8 max_पढ़ोs_beats;		/* Not present क्रम IPA v3.5.1 */
पूर्ण;

/**
 * काष्ठा gsi_channel_data - GSI channel configuration data
 * @tre_count:		number of TREs in the channel ring
 * @event_count:	number of slots in the associated event ring
 * @tlv_count:		number of entries in channel's TLV FIFO
 *
 * A GSI channel is a unidirectional means of transferring data to or
 * from (and through) the IPA.  A GSI channel has a ring buffer made
 * up of "transfer ring elements" (TREs) that specअगरy inभागidual data
 * transfers or IPA immediate commands.  TREs are filled by the AP,
 * and control is passed to IPA hardware by writing the last written
 * element पूर्णांकo a करोorbell रेजिस्टर.
 *
 * When data transfer commands have completed the GSI generates an
 * event (a काष्ठाure of data) and optionally संकेतs the AP with
 * an पूर्णांकerrupt.  Event काष्ठाures are implemented by another ring
 * buffer, directed toward the AP from the IPA.
 *
 * The input to a GSI channel is a FIFO of type/length/value (TLV)
 * elements, and the size of this FIFO limits the number of TREs
 * that can be included in a single transaction.
 */
काष्ठा gsi_channel_data अणु
	u16 tre_count;			/* must be a घातer of 2 */
	u16 event_count;		/* must be a घातer of 2 */
	u8 tlv_count;
पूर्ण;

/**
 * काष्ठा ipa_endpoपूर्णांक_tx_data - configuration data क्रम TX endpoपूर्णांकs
 * @seq_type:		primary packet processing sequencer type
 * @seq_rep_type:	sequencer type क्रम replication processing
 * @status_endpoपूर्णांक:	endpoपूर्णांक to which status elements are sent
 *
 * The @status_endpoपूर्णांक is only valid अगर the endpoपूर्णांक's @status_enable
 * flag is set.
 */
काष्ठा ipa_endpoपूर्णांक_tx_data अणु
	क्रमागत ipa_seq_type seq_type;
	क्रमागत ipa_seq_rep_type seq_rep_type;
	क्रमागत ipa_endpoपूर्णांक_name status_endpoपूर्णांक;
पूर्ण;

/**
 * काष्ठा ipa_endpoपूर्णांक_rx_data - configuration data क्रम RX endpoपूर्णांकs
 * @pad_align:	घातer-of-2 boundary to which packet payload is aligned
 * @aggr_बंद_eof: whether aggregation बंदs on end-of-frame
 *
 * With each packet it transfers, the IPA hardware can perक्रमm certain
 * transक्रमmations of its packet data.  One of these is adding pad bytes
 * to the end of the packet data so the result ends on a घातer-of-2 boundary.
 *
 * It is also able to aggregate multiple packets पूर्णांकo a single receive buffer.
 * Aggregation is "open" जबतक a buffer is being filled, and "closes" when
 * certain criteria are met.  One of those criteria is the sender indicating
 * a "frame" consisting of several transfers has ended.
 */
काष्ठा ipa_endpoपूर्णांक_rx_data अणु
	u32 pad_align;
	bool aggr_बंद_eof;
पूर्ण;

/**
 * काष्ठा ipa_endpoपूर्णांक_config_data - IPA endpoपूर्णांक hardware configuration
 * @resource_group:	resource group to assign endpoपूर्णांक to
 * @checksum:		whether checksum offload is enabled
 * @qmap:		whether endpoपूर्णांक uses QMAP protocol
 * @aggregation:	whether endpoपूर्णांक supports aggregation
 * @status_enable:	whether endpoपूर्णांक uses status elements
 * @dma_mode:		whether endpoपूर्णांक operates in DMA mode
 * @dma_endpoपूर्णांक:	peer endpoपूर्णांक, अगर operating in DMA mode
 * @tx:			TX-specअगरic endpoपूर्णांक inक्रमmation (see above)
 * @rx:			RX-specअगरic endpoपूर्णांक inक्रमmation (see above)
 */
काष्ठा ipa_endpoपूर्णांक_config_data अणु
	u32 resource_group;
	bool checksum;
	bool qmap;
	bool aggregation;
	bool status_enable;
	bool dma_mode;
	क्रमागत ipa_endpoपूर्णांक_name dma_endpoपूर्णांक;
	जोड़ अणु
		काष्ठा ipa_endpoपूर्णांक_tx_data tx;
		काष्ठा ipa_endpoपूर्णांक_rx_data rx;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा ipa_endpoपूर्णांक_data - IPA endpoपूर्णांक configuration data
 * @filter_support:	whether endpoपूर्णांक supports filtering
 * @config:		hardware configuration (see above)
 *
 * Not all endpoपूर्णांकs support the IPA filtering capability.  A filter table
 * defines the filters to apply क्रम those endpoपूर्णांकs that support it.  The
 * AP is responsible क्रम initializing this table, and it must include entries
 * क्रम non-AP endpoपूर्णांकs.  For this reason we define *all* endpoपूर्णांकs used
 * in the प्रणाली, and indicate whether they support filtering.
 *
 * The reमुख्यing endpoपूर्णांक configuration data applies only to AP endpoपूर्णांकs.
 */
काष्ठा ipa_endpoपूर्णांक_data अणु
	bool filter_support;
	/* Everything अन्यथा is specअगरied only क्रम AP endpoपूर्णांकs */
	काष्ठा ipa_endpoपूर्णांक_config_data config;
पूर्ण;

/**
 * काष्ठा ipa_gsi_endpoपूर्णांक_data - GSI channel/IPA endpoपूर्णांक data
 * @ee_id:	GSI execution environment ID
 * @channel_id:	GSI channel ID
 * @endpoपूर्णांक_id: IPA endpoपूर्णांक ID
 * @toward_ipa:	direction of data transfer
 * @channel:	GSI channel configuration data (see above)
 * @endpoपूर्णांक:	IPA endpoपूर्णांक configuration data (see above)
 */
काष्ठा ipa_gsi_endpoपूर्णांक_data अणु
	u8 ee_id;		/* क्रमागत gsi_ee_id */
	u8 channel_id;
	u8 endpoपूर्णांक_id;
	bool toward_ipa;

	काष्ठा gsi_channel_data channel;
	काष्ठा ipa_endpoपूर्णांक_data endpoपूर्णांक;
पूर्ण;

/**
 * काष्ठा ipa_resource_limits - minimum and maximum resource counts
 * @min:	minimum number of resources of a given type
 * @max:	maximum number of resources of a given type
 */
काष्ठा ipa_resource_limits अणु
	u32 min;
	u32 max;
पूर्ण;

/**
 * काष्ठा ipa_resource - resource group source or destination resource usage
 * @limits:	array of resource limits, indexed by group
 */
काष्ठा ipa_resource अणु
	काष्ठा ipa_resource_limits limits[IPA_RESOURCE_GROUP_MAX];
पूर्ण;

/**
 * काष्ठा ipa_resource_data - IPA resource configuration data
 * @rsrc_group_src_count: number of source resource groups supported
 * @rsrc_group_dst_count: number of destination resource groups supported
 * @resource_src_count:	number of entries in the resource_src array
 * @resource_src:	source endpoपूर्णांक group resources
 * @resource_dst_count:	number of entries in the resource_dst array
 * @resource_dst:	destination endpoपूर्णांक group resources
 *
 * In order to manage quality of service between endpoपूर्णांकs, certain resources
 * required क्रम operation are allocated to groups of endpoपूर्णांकs.  Generally
 * this inक्रमmation is invisible to the AP, but the AP is responsible क्रम
 * programming it at initialization समय, so we specअगरy it here.
 */
काष्ठा ipa_resource_data अणु
	u32 rsrc_group_src_count;
	u32 rsrc_group_dst_count;
	u32 resource_src_count;
	स्थिर काष्ठा ipa_resource *resource_src;
	u32 resource_dst_count;
	स्थिर काष्ठा ipa_resource *resource_dst;
पूर्ण;

/**
 * काष्ठा ipa_mem_data - description of IPA memory regions
 * @local_count:	number of regions defined in the local[] array
 * @local:		array of IPA-local memory region descriptors
 * @imem_addr:		physical address of IPA region within IMEM
 * @imem_size:		size in bytes of IPA IMEM region
 * @smem_id:		item identअगरier क्रम IPA region within SMEM memory
 * @smem_size:		size in bytes of the IPA SMEM region
 */
काष्ठा ipa_mem_data अणु
	u32 local_count;
	स्थिर काष्ठा ipa_mem *local;
	u32 imem_addr;
	u32 imem_size;
	u32 smem_id;
	u32 smem_size;
पूर्ण;

/**
 * काष्ठा ipa_पूर्णांकerconnect_data - description of IPA पूर्णांकerconnect bandwidths
 * @name:		Interconnect name (matches पूर्णांकerconnect-name in DT)
 * @peak_bandwidth:	Peak पूर्णांकerconnect bandwidth (in 1000 byte/sec units)
 * @average_bandwidth:	Average पूर्णांकerconnect bandwidth (in 1000 byte/sec units)
 */
काष्ठा ipa_पूर्णांकerconnect_data अणु
	स्थिर अक्षर *name;
	u32 peak_bandwidth;
	u32 average_bandwidth;
पूर्ण;

/**
 * काष्ठा ipa_घड़ी_data - description of IPA घड़ी and पूर्णांकerconnect rates
 * @core_घड़ी_rate:	Core घड़ी rate (Hz)
 * @पूर्णांकerconnect_count:	Number of entries in the पूर्णांकerconnect_data array
 * @पूर्णांकerconnect_data:	IPA पूर्णांकerconnect configuration data
 */
काष्ठा ipa_घड़ी_data अणु
	u32 core_घड़ी_rate;
	u32 पूर्णांकerconnect_count;		/* # entries in पूर्णांकerconnect_data[] */
	स्थिर काष्ठा ipa_पूर्णांकerconnect_data *पूर्णांकerconnect_data;
पूर्ण;

/**
 * काष्ठा ipa_data - combined IPA/GSI configuration data
 * @version:		IPA hardware version
 * @backward_compat:	BCR रेजिस्टर value (prior to IPA v4.5 only)
 * @qsb_count:		number of entries in the qsb_data array
 * @qsb_data:		Qualcomm System Bus configuration data
 * @endpoपूर्णांक_count:	number of entries in the endpoपूर्णांक_data array
 * @endpoपूर्णांक_data:	IPA endpoपूर्णांक/GSI channel data
 * @resource_data:	IPA resource configuration data
 * @mem_data:		IPA memory region data
 * @घड़ी_data:		IPA घड़ी and पूर्णांकerconnect data
 */
काष्ठा ipa_data अणु
	क्रमागत ipa_version version;
	u32 backward_compat;
	u32 qsb_count;		/* number of entries in qsb_data[] */
	स्थिर काष्ठा ipa_qsb_data *qsb_data;
	u32 endpoपूर्णांक_count;	/* number of entries in endpoपूर्णांक_data[] */
	स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *endpoपूर्णांक_data;
	स्थिर काष्ठा ipa_resource_data *resource_data;
	स्थिर काष्ठा ipa_mem_data *mem_data;
	स्थिर काष्ठा ipa_घड़ी_data *घड़ी_data;
पूर्ण;

बाह्य स्थिर काष्ठा ipa_data ipa_data_v3_5_1;
बाह्य स्थिर काष्ठा ipa_data ipa_data_v4_2;
बाह्य स्थिर काष्ठा ipa_data ipa_data_v4_5;
बाह्य स्थिर काष्ठा ipa_data ipa_data_v4_9;
बाह्य स्थिर काष्ठा ipa_data ipa_data_v4_11;

#पूर्ण_अगर /* _IPA_DATA_H_ */
