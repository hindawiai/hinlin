<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018, Linaro Ltd.
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#अगर_अघोषित __LINUX_INTERCONNECT_PROVIDER_H
#घोषणा __LINUX_INTERCONNECT_PROVIDER_H

#समावेश <linux/पूर्णांकerconnect.h>

#घोषणा icc_units_to_bps(bw)  ((bw) * 1000ULL)

काष्ठा icc_node;
काष्ठा of_phandle_args;

/**
 * काष्ठा icc_node_data - icc node data
 *
 * @node: icc node
 * @tag: tag
 */
काष्ठा icc_node_data अणु
	काष्ठा icc_node *node;
	u32 tag;
पूर्ण;

/**
 * काष्ठा icc_onecell_data - driver data क्रम onecell पूर्णांकerconnect providers
 *
 * @num_nodes: number of nodes in this device
 * @nodes: array of poपूर्णांकers to the nodes in this device
 */
काष्ठा icc_onecell_data अणु
	अचिन्हित पूर्णांक num_nodes;
	काष्ठा icc_node *nodes[];
पूर्ण;

काष्ठा icc_node *of_icc_xlate_onecell(काष्ठा of_phandle_args *spec,
				      व्योम *data);

/**
 * काष्ठा icc_provider - पूर्णांकerconnect provider (controller) entity that might
 * provide multiple पूर्णांकerconnect controls
 *
 * @provider_list: list of the रेजिस्टरed पूर्णांकerconnect providers
 * @nodes: पूर्णांकernal list of the पूर्णांकerconnect provider nodes
 * @set: poपूर्णांकer to device specअगरic set operation function
 * @aggregate: poपूर्णांकer to device specअगरic aggregate operation function
 * @pre_aggregate: poपूर्णांकer to device specअगरic function that is called
 *		   beक्रमe the aggregation begins (optional)
 * @get_bw: poपूर्णांकer to device specअगरic function to get current bandwidth
 * @xlate: provider-specअगरic callback क्रम mapping nodes from phandle arguments
 * @xlate_extended: venकरोr-specअगरic callback क्रम mapping node data from phandle arguments
 * @dev: the device this पूर्णांकerconnect provider beदीर्घs to
 * @users: count of active users
 * @पूर्णांकer_set: whether पूर्णांकer-provider pairs will be configured with @set
 * @data: poपूर्णांकer to निजी data
 */
काष्ठा icc_provider अणु
	काष्ठा list_head	provider_list;
	काष्ठा list_head	nodes;
	पूर्णांक (*set)(काष्ठा icc_node *src, काष्ठा icc_node *dst);
	पूर्णांक (*aggregate)(काष्ठा icc_node *node, u32 tag, u32 avg_bw,
			 u32 peak_bw, u32 *agg_avg, u32 *agg_peak);
	व्योम (*pre_aggregate)(काष्ठा icc_node *node);
	पूर्णांक (*get_bw)(काष्ठा icc_node *node, u32 *avg, u32 *peak);
	काष्ठा icc_node* (*xlate)(काष्ठा of_phandle_args *spec, व्योम *data);
	काष्ठा icc_node_data* (*xlate_extended)(काष्ठा of_phandle_args *spec, व्योम *data);
	काष्ठा device		*dev;
	पूर्णांक			users;
	bool			पूर्णांकer_set;
	व्योम			*data;
पूर्ण;

/**
 * काष्ठा icc_node - entity that is part of the पूर्णांकerconnect topology
 *
 * @id: platक्रमm specअगरic node id
 * @name: node name used in debugfs
 * @links: a list of tarमाला_लो poपूर्णांकing to where we can go next when traversing
 * @num_links: number of links to other पूर्णांकerconnect nodes
 * @provider: poपूर्णांकs to the पूर्णांकerconnect provider of this node
 * @node_list: the list entry in the parent provider's "nodes" list
 * @search_list: list used when walking the nodes graph
 * @reverse: poपूर्णांकer to previous node when walking the nodes graph
 * @is_traversed: flag that is used when walking the nodes graph
 * @req_list: a list of QoS स्थिरraपूर्णांक requests associated with this node
 * @avg_bw: aggregated value of average bandwidth requests from all consumers
 * @peak_bw: aggregated value of peak bandwidth requests from all consumers
 * @init_avg: average bandwidth value that is पढ़ो from the hardware during init
 * @init_peak: peak bandwidth value that is पढ़ो from the hardware during init
 * @data: poपूर्णांकer to निजी data
 */
काष्ठा icc_node अणु
	पूर्णांक			id;
	स्थिर अक्षर              *name;
	काष्ठा icc_node		**links;
	माप_प्रकार			num_links;

	काष्ठा icc_provider	*provider;
	काष्ठा list_head	node_list;
	काष्ठा list_head	search_list;
	काष्ठा icc_node		*reverse;
	u8			is_traversed:1;
	काष्ठा hlist_head	req_list;
	u32			avg_bw;
	u32			peak_bw;
	u32			init_avg;
	u32			init_peak;
	व्योम			*data;
पूर्ण;

#अगर IS_ENABLED(CONFIG_INTERCONNECT)

पूर्णांक icc_std_aggregate(काष्ठा icc_node *node, u32 tag, u32 avg_bw,
		      u32 peak_bw, u32 *agg_avg, u32 *agg_peak);
काष्ठा icc_node *icc_node_create(पूर्णांक id);
व्योम icc_node_destroy(पूर्णांक id);
पूर्णांक icc_link_create(काष्ठा icc_node *node, स्थिर पूर्णांक dst_id);
पूर्णांक icc_link_destroy(काष्ठा icc_node *src, काष्ठा icc_node *dst);
व्योम icc_node_add(काष्ठा icc_node *node, काष्ठा icc_provider *provider);
व्योम icc_node_del(काष्ठा icc_node *node);
पूर्णांक icc_nodes_हटाओ(काष्ठा icc_provider *provider);
पूर्णांक icc_provider_add(काष्ठा icc_provider *provider);
पूर्णांक icc_provider_del(काष्ठा icc_provider *provider);
काष्ठा icc_node_data *of_icc_get_from_provider(काष्ठा of_phandle_args *spec);
व्योम icc_sync_state(काष्ठा device *dev);

#अन्यथा

अटल अंतरभूत पूर्णांक icc_std_aggregate(काष्ठा icc_node *node, u32 tag, u32 avg_bw,
				    u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा icc_node *icc_node_create(पूर्णांक id)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत व्योम icc_node_destroy(पूर्णांक id)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक icc_link_create(काष्ठा icc_node *node, स्थिर पूर्णांक dst_id)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक icc_link_destroy(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम icc_node_add(काष्ठा icc_node *node, काष्ठा icc_provider *provider)
अणु
पूर्ण

अटल अंतरभूत व्योम icc_node_del(काष्ठा icc_node *node)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक icc_nodes_हटाओ(काष्ठा icc_provider *provider)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक icc_provider_add(काष्ठा icc_provider *provider)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक icc_provider_del(काष्ठा icc_provider *provider)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा icc_node_data *of_icc_get_from_provider(काष्ठा of_phandle_args *spec)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

#पूर्ण_अगर /* CONFIG_INTERCONNECT */

#पूर्ण_अगर /* __LINUX_INTERCONNECT_PROVIDER_H */
