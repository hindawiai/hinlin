<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Interconnect framework पूर्णांकernal काष्ठाs
 *
 * Copyright (c) 2019, Linaro Ltd.
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#अगर_अघोषित __DRIVERS_INTERCONNECT_INTERNAL_H
#घोषणा __DRIVERS_INTERCONNECT_INTERNAL_H

/**
 * काष्ठा icc_req - स्थिरraपूर्णांकs that are attached to each node
 * @req_node: entry in list of requests क्रम the particular @node
 * @node: the पूर्णांकerconnect node to which this स्थिरraपूर्णांक applies
 * @dev: reference to the device that sets the स्थिरraपूर्णांकs
 * @enabled: indicates whether the path with this request is enabled
 * @tag: path tag (optional)
 * @avg_bw: an पूर्णांकeger describing the average bandwidth in kBps
 * @peak_bw: an पूर्णांकeger describing the peak bandwidth in kBps
 */
काष्ठा icc_req अणु
	काष्ठा hlist_node req_node;
	काष्ठा icc_node *node;
	काष्ठा device *dev;
	bool enabled;
	u32 tag;
	u32 avg_bw;
	u32 peak_bw;
पूर्ण;

/**
 * काष्ठा icc_path - पूर्णांकerconnect path काष्ठाure
 * @name: a string name of the path (useful क्रम ftrace)
 * @num_nodes: number of hops (nodes)
 * @reqs: array of the requests applicable to this path of nodes
 */
काष्ठा icc_path अणु
	स्थिर अक्षर *name;
	माप_प्रकार num_nodes;
	काष्ठा icc_req reqs[];
पूर्ण;

#पूर्ण_अगर
