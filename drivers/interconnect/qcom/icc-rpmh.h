<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DRIVERS_INTERCONNECT_QCOM_ICC_RPMH_H__
#घोषणा __DRIVERS_INTERCONNECT_QCOM_ICC_RPMH_H__

#समावेश <dt-bindings/पूर्णांकerconnect/qcom,icc.h>

#घोषणा to_qcom_provider(_provider) \
	container_of(_provider, काष्ठा qcom_icc_provider, provider)

/**
 * काष्ठा qcom_icc_provider - Qualcomm specअगरic पूर्णांकerconnect provider
 * @provider: generic पूर्णांकerconnect provider
 * @dev: reference to the NoC device
 * @bcms: list of bcms that maps to the provider
 * @num_bcms: number of @bcms
 * @voter: bcm voter targeted by this provider
 */
काष्ठा qcom_icc_provider अणु
	काष्ठा icc_provider provider;
	काष्ठा device *dev;
	काष्ठा qcom_icc_bcm **bcms;
	माप_प्रकार num_bcms;
	काष्ठा bcm_voter *voter;
पूर्ण;

/**
 * काष्ठा bcm_db - Auxiliary data pertaining to each Bus Clock Manager (BCM)
 * @unit: भागisor used to convert bytes/sec bw value to an RPMh msg
 * @width: multiplier used to convert bytes/sec bw value to an RPMh msg
 * @vcd: भव घड़ी करोमुख्य that this bcm beदीर्घs to
 * @reserved: reserved field
 */
काष्ठा bcm_db अणु
	__le32 unit;
	__le16 width;
	u8 vcd;
	u8 reserved;
पूर्ण;

#घोषणा MAX_LINKS		128
#घोषणा MAX_BCMS		64
#घोषणा MAX_BCM_PER_NODE	3
#घोषणा MAX_VCD			10

/**
 * काष्ठा qcom_icc_node - Qualcomm specअगरic पूर्णांकerconnect nodes
 * @name: the node name used in debugfs
 * @links: an array of nodes where we can go next जबतक traversing
 * @id: a unique node identअगरier
 * @num_links: the total number of @links
 * @channels: num of channels at this node
 * @buswidth: width of the पूर्णांकerconnect between a node and the bus
 * @sum_avg: current sum aggregate value of all avg bw requests
 * @max_peak: current max aggregate value of all peak bw requests
 * @bcms: list of bcms associated with this logical node
 * @num_bcms: num of @bcms
 */
काष्ठा qcom_icc_node अणु
	स्थिर अक्षर *name;
	u16 links[MAX_LINKS];
	u16 id;
	u16 num_links;
	u16 channels;
	u16 buswidth;
	u64 sum_avg[QCOM_ICC_NUM_BUCKETS];
	u64 max_peak[QCOM_ICC_NUM_BUCKETS];
	काष्ठा qcom_icc_bcm *bcms[MAX_BCM_PER_NODE];
	माप_प्रकार num_bcms;
पूर्ण;

/**
 * काष्ठा qcom_icc_bcm - Qualcomm specअगरic hardware accelerator nodes
 * known as Bus Clock Manager (BCM)
 * @name: the bcm node name used to fetch BCM data from command db
 * @type: latency or bandwidth bcm
 * @addr: address offsets used when voting to RPMH
 * @vote_x: aggregated threshold values, represents sum_bw when @type is bw bcm
 * @vote_y: aggregated threshold values, represents peak_bw when @type is bw bcm
 * @vote_scale: scaling factor क्रम vote_x and vote_y
 * @dirty: flag used to indicate whether the bcm needs to be committed
 * @keepalive: flag used to indicate whether a keepalive is required
 * @aux_data: auxiliary data used when calculating threshold values and
 * communicating with RPMh
 * @list: used to link to other bcms when compiling lists क्रम commit
 * @ws_list: used to keep track of bcms that may transition between wake/sleep
 * @num_nodes: total number of @num_nodes
 * @nodes: list of qcom_icc_nodes that this BCM encapsulates
 */
काष्ठा qcom_icc_bcm अणु
	स्थिर अक्षर *name;
	u32 type;
	u32 addr;
	u64 vote_x[QCOM_ICC_NUM_BUCKETS];
	u64 vote_y[QCOM_ICC_NUM_BUCKETS];
	u64 vote_scale;
	bool dirty;
	bool keepalive;
	काष्ठा bcm_db aux_data;
	काष्ठा list_head list;
	काष्ठा list_head ws_list;
	माप_प्रकार num_nodes;
	काष्ठा qcom_icc_node *nodes[];
पूर्ण;

काष्ठा qcom_icc_fabric अणु
	काष्ठा qcom_icc_node **nodes;
	माप_प्रकार num_nodes;
पूर्ण;

काष्ठा qcom_icc_desc अणु
	काष्ठा qcom_icc_node **nodes;
	माप_प्रकार num_nodes;
	काष्ठा qcom_icc_bcm **bcms;
	माप_प्रकार num_bcms;
पूर्ण;

#घोषणा DEFINE_QNODE(_name, _id, _channels, _buswidth, ...)		\
		अटल काष्ठा qcom_icc_node _name = अणु			\
		.id = _id,						\
		.name = #_name,						\
		.channels = _channels,					\
		.buswidth = _buswidth,					\
		.num_links = ARRAY_SIZE(((पूर्णांक[])अणु __VA_ARGS__ पूर्ण)),	\
		.links = अणु __VA_ARGS__ पूर्ण,				\
	पूर्ण

पूर्णांक qcom_icc_aggregate(काष्ठा icc_node *node, u32 tag, u32 avg_bw,
		       u32 peak_bw, u32 *agg_avg, u32 *agg_peak);
पूर्णांक qcom_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst);
काष्ठा icc_node_data *qcom_icc_xlate_extended(काष्ठा of_phandle_args *spec, व्योम *data);
पूर्णांक qcom_icc_bcm_init(काष्ठा qcom_icc_bcm *bcm, काष्ठा device *dev);
व्योम qcom_icc_pre_aggregate(काष्ठा icc_node *node);

#पूर्ण_अगर
