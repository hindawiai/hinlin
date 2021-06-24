<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Zynq UltraScale+ MPSoC घड़ी controller
 *
 *  Copyright (C) 2016-2019 Xilinx
 *
 * Based on drivers/clk/zynq/clkc.c
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "clk-zynqmp.h"

#घोषणा MAX_PARENT			100
#घोषणा MAX_NODES			6
#घोषणा MAX_NAME_LEN			50

/* Flags क्रम parents */
#घोषणा PARENT_CLK_SELF			0
#घोषणा PARENT_CLK_NODE1		1
#घोषणा PARENT_CLK_NODE2		2
#घोषणा PARENT_CLK_NODE3		3
#घोषणा PARENT_CLK_NODE4		4
#घोषणा PARENT_CLK_EXTERNAL		5

#घोषणा END_OF_CLK_NAME			"END_OF_CLK"
#घोषणा END_OF_TOPOLOGY_NODE		1
#घोषणा END_OF_PARENTS			1
#घोषणा RESERVED_CLK_NAME		""

#घोषणा CLK_GET_NAME_RESP_LEN		16
#घोषणा CLK_GET_TOPOLOGY_RESP_WORDS	3
#घोषणा CLK_GET_PARENTS_RESP_WORDS	3
#घोषणा CLK_GET_ATTR_RESP_WORDS		1

क्रमागत clk_type अणु
	CLK_TYPE_OUTPUT,
	CLK_TYPE_EXTERNAL,
पूर्ण;

/**
 * काष्ठा घड़ी_parent - Clock parent
 * @name:	Parent name
 * @id:		Parent घड़ी ID
 * @flag:	Parent flags
 */
काष्ठा घड़ी_parent अणु
	अक्षर name[MAX_NAME_LEN];
	पूर्णांक id;
	u32 flag;
पूर्ण;

/**
 * काष्ठा zynqmp_घड़ी - Clock
 * @clk_name:		Clock name
 * @valid:		Validity flag of घड़ी
 * @type:		Clock type (Output/External)
 * @node:		Clock topology nodes
 * @num_nodes:		Number of nodes present in topology
 * @parent:		Parent of घड़ी
 * @num_parents:	Number of parents of घड़ी
 * @clk_id:		Clock id
 */
काष्ठा zynqmp_घड़ी अणु
	अक्षर clk_name[MAX_NAME_LEN];
	u32 valid;
	क्रमागत clk_type type;
	काष्ठा घड़ी_प्रकारopology node[MAX_NODES];
	u32 num_nodes;
	काष्ठा घड़ी_parent parent[MAX_PARENT];
	u32 num_parents;
	u32 clk_id;
पूर्ण;

काष्ठा name_resp अणु
	अक्षर name[CLK_GET_NAME_RESP_LEN];
पूर्ण;

काष्ठा topology_resp अणु
#घोषणा CLK_TOPOLOGY_TYPE		GENMASK(3, 0)
#घोषणा CLK_TOPOLOGY_CUSTOM_TYPE_FLAGS	GENMASK(7, 4)
#घोषणा CLK_TOPOLOGY_FLAGS		GENMASK(23, 8)
#घोषणा CLK_TOPOLOGY_TYPE_FLAGS		GENMASK(31, 24)
	u32 topology[CLK_GET_TOPOLOGY_RESP_WORDS];
पूर्ण;

काष्ठा parents_resp अणु
#घोषणा NA_PARENT			0xFFFFFFFF
#घोषणा DUMMY_PARENT			0xFFFFFFFE
#घोषणा CLK_PARENTS_ID			GENMASK(15, 0)
#घोषणा CLK_PARENTS_FLAGS		GENMASK(31, 16)
	u32 parents[CLK_GET_PARENTS_RESP_WORDS];
पूर्ण;

काष्ठा attr_resp अणु
#घोषणा CLK_ATTR_VALID			BIT(0)
#घोषणा CLK_ATTR_TYPE			BIT(2)
#घोषणा CLK_ATTR_NODE_INDEX		GENMASK(13, 0)
#घोषणा CLK_ATTR_NODE_TYPE		GENMASK(19, 14)
#घोषणा CLK_ATTR_NODE_SUBCLASS		GENMASK(25, 20)
#घोषणा CLK_ATTR_NODE_CLASS		GENMASK(31, 26)
	u32 attr[CLK_GET_ATTR_RESP_WORDS];
पूर्ण;

अटल स्थिर अक्षर clk_type_postfix[][10] = अणु
	[TYPE_INVALID] = "",
	[TYPE_MUX] = "_mux",
	[TYPE_GATE] = "",
	[TYPE_DIV1] = "_div1",
	[TYPE_DIV2] = "_div2",
	[TYPE_FIXEDFACTOR] = "_ff",
	[TYPE_PLL] = ""
पूर्ण;

अटल काष्ठा clk_hw *(* स्थिर clk_topology[]) (स्थिर अक्षर *name, u32 clk_id,
					स्थिर अक्षर * स्थिर *parents,
					u8 num_parents,
					स्थिर काष्ठा घड़ी_प्रकारopology *nodes)
					= अणु
	[TYPE_INVALID] = शून्य,
	[TYPE_MUX] = zynqmp_clk_रेजिस्टर_mux,
	[TYPE_PLL] = zynqmp_clk_रेजिस्टर_pll,
	[TYPE_FIXEDFACTOR] = zynqmp_clk_रेजिस्टर_fixed_factor,
	[TYPE_DIV1] = zynqmp_clk_रेजिस्टर_भागider,
	[TYPE_DIV2] = zynqmp_clk_रेजिस्टर_भागider,
	[TYPE_GATE] = zynqmp_clk_रेजिस्टर_gate
पूर्ण;

अटल काष्ठा zynqmp_घड़ी *घड़ी;
अटल काष्ठा clk_hw_onecell_data *zynqmp_data;
अटल अचिन्हित पूर्णांक घड़ी_max_idx;

/**
 * zynqmp_is_valid_घड़ी() - Check whether घड़ी is valid or not
 * @clk_id:	Clock index
 *
 * Return: 1 अगर घड़ी is valid, 0 अगर घड़ी is invalid अन्यथा error code
 */
अटल अंतरभूत पूर्णांक zynqmp_is_valid_घड़ी(u32 clk_id)
अणु
	अगर (clk_id >= घड़ी_max_idx)
		वापस -ENODEV;

	वापस घड़ी[clk_id].valid;
पूर्ण

/**
 * zynqmp_get_घड़ी_name() - Get name of घड़ी from Clock index
 * @clk_id:	Clock index
 * @clk_name:	Name of घड़ी
 *
 * Return: 0 on success अन्यथा error code
 */
अटल पूर्णांक zynqmp_get_घड़ी_name(u32 clk_id, अक्षर *clk_name)
अणु
	पूर्णांक ret;

	ret = zynqmp_is_valid_घड़ी(clk_id);
	अगर (ret == 1) अणु
		म_नकलन(clk_name, घड़ी[clk_id].clk_name, MAX_NAME_LEN);
		वापस 0;
	पूर्ण

	वापस ret == 0 ? -EINVAL : ret;
पूर्ण

/**
 * zynqmp_get_घड़ी_प्रकारype() - Get type of घड़ी
 * @clk_id:	Clock index
 * @type:	Clock type: CLK_TYPE_OUTPUT or CLK_TYPE_EXTERNAL
 *
 * Return: 0 on success अन्यथा error code
 */
अटल पूर्णांक zynqmp_get_घड़ी_प्रकारype(u32 clk_id, u32 *type)
अणु
	पूर्णांक ret;

	ret = zynqmp_is_valid_घड़ी(clk_id);
	अगर (ret == 1) अणु
		*type = घड़ी[clk_id].type;
		वापस 0;
	पूर्ण

	वापस ret == 0 ? -EINVAL : ret;
पूर्ण

/**
 * zynqmp_pm_घड़ी_get_num_घड़ीs() - Get number of घड़ीs in प्रणाली
 * @nघड़ीs:	Number of घड़ीs in प्रणाली/board.
 *
 * Call firmware API to get number of घड़ीs.
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pm_घड़ी_get_num_घड़ीs(u32 *nघड़ीs)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_CLOCK_GET_NUM_CLOCKS;

	ret = zynqmp_pm_query_data(qdata, ret_payload);
	*nघड़ीs = ret_payload[1];

	वापस ret;
पूर्ण

/**
 * zynqmp_pm_घड़ी_get_name() - Get the name of घड़ी क्रम given id
 * @घड़ी_id:	ID of the घड़ी to be queried
 * @response:	Name of the घड़ी with the given id
 *
 * This function is used to get name of घड़ी specअगरied by given
 * घड़ी ID.
 *
 * Return: Returns 0
 */
अटल पूर्णांक zynqmp_pm_घड़ी_get_name(u32 घड़ी_id,
				    काष्ठा name_resp *response)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 ret_payload[PAYLOAD_ARG_CNT];

	qdata.qid = PM_QID_CLOCK_GET_NAME;
	qdata.arg1 = घड़ी_id;

	zynqmp_pm_query_data(qdata, ret_payload);
	स_नकल(response, ret_payload, माप(*response));

	वापस 0;
पूर्ण

/**
 * zynqmp_pm_घड़ी_get_topology() - Get the topology of घड़ी क्रम given id
 * @घड़ी_id:	ID of the घड़ी to be queried
 * @index:	Node index of घड़ी topology
 * @response:	Buffer used क्रम the topology response
 *
 * This function is used to get topology inक्रमmation क्रम the घड़ी
 * specअगरied by given घड़ी ID.
 *
 * This API will वापस 3 node of topology with a single response. To get
 * other nodes, master should call same API in loop with new
 * index till error is वापसed. E.g First call should have
 * index 0 which will वापस nodes 0,1 and 2. Next call, index
 * should be 3 which will वापस nodes 3,4 and 5 and so on.
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक zynqmp_pm_घड़ी_get_topology(u32 घड़ी_id, u32 index,
					काष्ठा topology_resp *response)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_CLOCK_GET_TOPOLOGY;
	qdata.arg1 = घड़ी_id;
	qdata.arg2 = index;

	ret = zynqmp_pm_query_data(qdata, ret_payload);
	स_नकल(response, &ret_payload[1], माप(*response));

	वापस ret;
पूर्ण

/**
 * zynqmp_clk_रेजिस्टर_fixed_factor() - Register fixed factor with the
 *					घड़ी framework
 * @name:		Name of this घड़ी
 * @clk_id:		Clock ID
 * @parents:		Name of this घड़ी's parents
 * @num_parents:	Number of parents
 * @nodes:		Clock topology node
 *
 * Return: घड़ी hardware to the रेजिस्टरed घड़ी
 */
काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_fixed_factor(स्थिर अक्षर *name, u32 clk_id,
					स्थिर अक्षर * स्थिर *parents,
					u8 num_parents,
					स्थिर काष्ठा घड़ी_प्रकारopology *nodes)
अणु
	u32 mult, भाग;
	काष्ठा clk_hw *hw;
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_CLOCK_GET_FIXEDFACTOR_PARAMS;
	qdata.arg1 = clk_id;

	ret = zynqmp_pm_query_data(qdata, ret_payload);
	अगर (ret)
		वापस ERR_PTR(ret);

	mult = ret_payload[1];
	भाग = ret_payload[2];

	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, name,
					  parents[0],
					  nodes->flag, mult,
					  भाग);

	वापस hw;
पूर्ण

/**
 * zynqmp_pm_घड़ी_get_parents() - Get the first 3 parents of घड़ी क्रम given id
 * @घड़ी_id:	Clock ID
 * @index:	Parent index
 * @response:	Parents of the given घड़ी
 *
 * This function is used to get 3 parents क्रम the घड़ी specअगरied by
 * given घड़ी ID.
 *
 * This API will वापस 3 parents with a single response. To get
 * other parents, master should call same API in loop with new
 * parent index till error is वापसed. E.g First call should have
 * index 0 which will वापस parents 0,1 and 2. Next call, index
 * should be 3 which will वापस parent 3,4 and 5 and so on.
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक zynqmp_pm_घड़ी_get_parents(u32 घड़ी_id, u32 index,
				       काष्ठा parents_resp *response)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_CLOCK_GET_PARENTS;
	qdata.arg1 = घड़ी_id;
	qdata.arg2 = index;

	ret = zynqmp_pm_query_data(qdata, ret_payload);
	स_नकल(response, &ret_payload[1], माप(*response));

	वापस ret;
पूर्ण

/**
 * zynqmp_pm_घड़ी_get_attributes() - Get the attributes of घड़ी क्रम given id
 * @घड़ी_id:	Clock ID
 * @response:	Clock attributes response
 *
 * This function is used to get घड़ी's attributes(e.g. valid, घड़ी type, etc).
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक zynqmp_pm_घड़ी_get_attributes(u32 घड़ी_id,
					  काष्ठा attr_resp *response)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_CLOCK_GET_ATTRIBUTES;
	qdata.arg1 = घड़ी_id;

	ret = zynqmp_pm_query_data(qdata, ret_payload);
	स_नकल(response, &ret_payload[1], माप(*response));

	वापस ret;
पूर्ण

/**
 * __zynqmp_घड़ी_get_topology() - Get topology data of घड़ी from firmware
 *				   response data
 * @topology:		Clock topology
 * @response:		Clock topology data received from firmware
 * @nnodes:		Number of nodes
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक __zynqmp_घड़ी_get_topology(काष्ठा घड़ी_प्रकारopology *topology,
				       काष्ठा topology_resp *response,
				       u32 *nnodes)
अणु
	पूर्णांक i;
	u32 type;

	क्रम (i = 0; i < ARRAY_SIZE(response->topology); i++) अणु
		type = FIELD_GET(CLK_TOPOLOGY_TYPE, response->topology[i]);
		अगर (type == TYPE_INVALID)
			वापस END_OF_TOPOLOGY_NODE;
		topology[*nnodes].type = type;
		topology[*nnodes].flag = FIELD_GET(CLK_TOPOLOGY_FLAGS,
						   response->topology[i]);
		topology[*nnodes].type_flag =
				FIELD_GET(CLK_TOPOLOGY_TYPE_FLAGS,
					  response->topology[i]);
		topology[*nnodes].custom_type_flag =
			FIELD_GET(CLK_TOPOLOGY_CUSTOM_TYPE_FLAGS,
				  response->topology[i]);
		(*nnodes)++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_घड़ी_get_topology() - Get topology of घड़ी from firmware using
 *				 PM_API
 * @clk_id:		Clock index
 * @topology:		Clock topology
 * @num_nodes:		Number of nodes
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक zynqmp_घड़ी_get_topology(u32 clk_id,
				     काष्ठा घड़ी_प्रकारopology *topology,
				     u32 *num_nodes)
अणु
	पूर्णांक j, ret;
	काष्ठा topology_resp response = अणु पूर्ण;

	*num_nodes = 0;
	क्रम (j = 0; j <= MAX_NODES; j += ARRAY_SIZE(response.topology)) अणु
		ret = zynqmp_pm_घड़ी_get_topology(घड़ी[clk_id].clk_id, j,
						   &response);
		अगर (ret)
			वापस ret;
		ret = __zynqmp_घड़ी_get_topology(topology, &response,
						  num_nodes);
		अगर (ret == END_OF_TOPOLOGY_NODE)
			वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __zynqmp_घड़ी_get_parents() - Get parents info of घड़ी from firmware
 *				   response data
 * @parents:		Clock parents
 * @response:		Clock parents data received from firmware
 * @nparent:		Number of parent
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक __zynqmp_घड़ी_get_parents(काष्ठा घड़ी_parent *parents,
				      काष्ठा parents_resp *response,
				      u32 *nparent)
अणु
	पूर्णांक i;
	काष्ठा घड़ी_parent *parent;

	क्रम (i = 0; i < ARRAY_SIZE(response->parents); i++) अणु
		अगर (response->parents[i] == NA_PARENT)
			वापस END_OF_PARENTS;

		parent = &parents[i];
		parent->id = FIELD_GET(CLK_PARENTS_ID, response->parents[i]);
		अगर (response->parents[i] == DUMMY_PARENT) अणु
			म_नकल(parent->name, "dummy_name");
			parent->flag = 0;
		पूर्ण अन्यथा अणु
			parent->flag = FIELD_GET(CLK_PARENTS_FLAGS,
						 response->parents[i]);
			अगर (zynqmp_get_घड़ी_name(parent->id, parent->name))
				जारी;
		पूर्ण
		*nparent += 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_घड़ी_get_parents() - Get parents info from firmware using PM_API
 * @clk_id:		Clock index
 * @parents:		Clock parents
 * @num_parents:	Total number of parents
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक zynqmp_घड़ी_get_parents(u32 clk_id, काष्ठा घड़ी_parent *parents,
				    u32 *num_parents)
अणु
	पूर्णांक j = 0, ret;
	काष्ठा parents_resp response = अणु पूर्ण;

	*num_parents = 0;
	करो अणु
		/* Get parents from firmware */
		ret = zynqmp_pm_घड़ी_get_parents(घड़ी[clk_id].clk_id, j,
						  &response);
		अगर (ret)
			वापस ret;

		ret = __zynqmp_घड़ी_get_parents(&parents[j], &response,
						 num_parents);
		अगर (ret == END_OF_PARENTS)
			वापस 0;
		j += ARRAY_SIZE(response.parents);
	पूर्ण जबतक (*num_parents <= MAX_PARENT);

	वापस 0;
पूर्ण

/**
 * zynqmp_get_parent_list() - Create list of parents name
 * @np:			Device node
 * @clk_id:		Clock index
 * @parent_list:	List of parent's name
 * @num_parents:	Total number of parents
 *
 * Return: 0 on success अन्यथा error+reason
 */
अटल पूर्णांक zynqmp_get_parent_list(काष्ठा device_node *np, u32 clk_id,
				  स्थिर अक्षर **parent_list, u32 *num_parents)
अणु
	पूर्णांक i = 0, ret;
	u32 total_parents = घड़ी[clk_id].num_parents;
	काष्ठा घड़ी_प्रकारopology *clk_nodes;
	काष्ठा घड़ी_parent *parents;

	clk_nodes = घड़ी[clk_id].node;
	parents = घड़ी[clk_id].parent;

	क्रम (i = 0; i < total_parents; i++) अणु
		अगर (!parents[i].flag) अणु
			parent_list[i] = parents[i].name;
		पूर्ण अन्यथा अगर (parents[i].flag == PARENT_CLK_EXTERNAL) अणु
			ret = of_property_match_string(np, "clock-names",
						       parents[i].name);
			अगर (ret < 0)
				म_नकल(parents[i].name, "dummy_name");
			parent_list[i] = parents[i].name;
		पूर्ण अन्यथा अणु
			म_जोड़ो(parents[i].name,
			       clk_type_postfix[clk_nodes[parents[i].flag - 1].
			       type]);
			parent_list[i] = parents[i].name;
		पूर्ण
	पूर्ण

	*num_parents = total_parents;
	वापस 0;
पूर्ण

/**
 * zynqmp_रेजिस्टर_clk_topology() - Register घड़ी topology
 * @clk_id:		Clock index
 * @clk_name:		Clock Name
 * @num_parents:	Total number of parents
 * @parent_names:	List of parents name
 *
 * Return: Returns either घड़ी hardware or error+reason
 */
अटल काष्ठा clk_hw *zynqmp_रेजिस्टर_clk_topology(पूर्णांक clk_id, अक्षर *clk_name,
						   पूर्णांक num_parents,
						   स्थिर अक्षर **parent_names)
अणु
	पूर्णांक j;
	u32 num_nodes, clk_dev_id;
	अक्षर *clk_out[MAX_NODES];
	काष्ठा घड़ी_प्रकारopology *nodes;
	काष्ठा clk_hw *hw = शून्य;

	nodes = घड़ी[clk_id].node;
	num_nodes = घड़ी[clk_id].num_nodes;
	clk_dev_id = घड़ी[clk_id].clk_id;

	क्रम (j = 0; j < num_nodes; j++) अणु
		/*
		 * Clock name received from firmware is output घड़ी name.
		 * Intermediate घड़ी names are postfixed with type of घड़ी.
		 */
		अगर (j != (num_nodes - 1)) अणु
			clk_out[j] = kaप्र_लिखो(GFP_KERNEL, "%s%s", clk_name,
					    clk_type_postfix[nodes[j].type]);
		पूर्ण अन्यथा अणु
			clk_out[j] = kaप्र_लिखो(GFP_KERNEL, "%s", clk_name);
		पूर्ण

		अगर (!clk_topology[nodes[j].type])
			जारी;

		hw = (*clk_topology[nodes[j].type])(clk_out[j], clk_dev_id,
						    parent_names,
						    num_parents,
						    &nodes[j]);
		अगर (IS_ERR(hw))
			pr_warn_once("%s() 0x%x: %s register fail with %ld\n",
				     __func__,  clk_dev_id, clk_name,
				     PTR_ERR(hw));

		parent_names[0] = clk_out[j];
	पूर्ण

	क्रम (j = 0; j < num_nodes; j++)
		kमुक्त(clk_out[j]);

	वापस hw;
पूर्ण

/**
 * zynqmp_रेजिस्टर_घड़ीs() - Register घड़ीs
 * @np:		Device node
 *
 * Return: 0 on success अन्यथा error code
 */
अटल पूर्णांक zynqmp_रेजिस्टर_घड़ीs(काष्ठा device_node *np)
अणु
	पूर्णांक ret;
	u32 i, total_parents = 0, type = 0;
	स्थिर अक्षर *parent_names[MAX_PARENT];

	क्रम (i = 0; i < घड़ी_max_idx; i++) अणु
		अक्षर clk_name[MAX_NAME_LEN];

		/* get घड़ी name, जारी to next घड़ी अगर name not found */
		अगर (zynqmp_get_घड़ी_name(i, clk_name))
			जारी;

		/* Check अगर घड़ी is valid and output घड़ी.
		 * Do not रेजिस्टर invalid or बाह्यal घड़ी.
		 */
		ret = zynqmp_get_घड़ी_प्रकारype(i, &type);
		अगर (ret || type != CLK_TYPE_OUTPUT)
			जारी;

		/* Get parents of घड़ी*/
		अगर (zynqmp_get_parent_list(np, i, parent_names,
					   &total_parents)) अणु
			WARN_ONCE(1, "No parents found for %s\n",
				  घड़ी[i].clk_name);
			जारी;
		पूर्ण

		zynqmp_data->hws[i] =
			zynqmp_रेजिस्टर_clk_topology(i, clk_name,
						     total_parents,
						     parent_names);
	पूर्ण

	क्रम (i = 0; i < घड़ी_max_idx; i++) अणु
		अगर (IS_ERR(zynqmp_data->hws[i])) अणु
			pr_err("Zynq Ultrascale+ MPSoC clk %s: register failed with %ld\n",
			       घड़ी[i].clk_name, PTR_ERR(zynqmp_data->hws[i]));
			WARN_ON(1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * zynqmp_get_घड़ी_info() - Get घड़ी inक्रमmation from firmware using PM_API
 */
अटल व्योम zynqmp_get_घड़ी_info(व्योम)
अणु
	पूर्णांक i, ret;
	u32 type = 0;
	u32 nodetype, subclass, class;
	काष्ठा attr_resp attr;
	काष्ठा name_resp name;

	क्रम (i = 0; i < घड़ी_max_idx; i++) अणु
		ret = zynqmp_pm_घड़ी_get_attributes(i, &attr);
		अगर (ret)
			जारी;

		घड़ी[i].valid = FIELD_GET(CLK_ATTR_VALID, attr.attr[0]);
		/* skip query क्रम Invalid घड़ी */
		ret = zynqmp_is_valid_घड़ी(i);
		अगर (ret != CLK_ATTR_VALID)
			जारी;

		घड़ी[i].type = FIELD_GET(CLK_ATTR_TYPE, attr.attr[0]) ?
			CLK_TYPE_EXTERNAL : CLK_TYPE_OUTPUT;

		nodetype = FIELD_GET(CLK_ATTR_NODE_TYPE, attr.attr[0]);
		subclass = FIELD_GET(CLK_ATTR_NODE_SUBCLASS, attr.attr[0]);
		class = FIELD_GET(CLK_ATTR_NODE_CLASS, attr.attr[0]);

		घड़ी[i].clk_id = FIELD_PREP(CLK_ATTR_NODE_CLASS, class) |
				  FIELD_PREP(CLK_ATTR_NODE_SUBCLASS, subclass) |
				  FIELD_PREP(CLK_ATTR_NODE_TYPE, nodetype) |
				  FIELD_PREP(CLK_ATTR_NODE_INDEX, i);

		zynqmp_pm_घड़ी_get_name(घड़ी[i].clk_id, &name);
		अगर (!म_भेद(name.name, RESERVED_CLK_NAME))
			जारी;
		म_नकलन(घड़ी[i].clk_name, name.name, MAX_NAME_LEN);
	पूर्ण

	/* Get topology of all घड़ी */
	क्रम (i = 0; i < घड़ी_max_idx; i++) अणु
		ret = zynqmp_get_घड़ी_प्रकारype(i, &type);
		अगर (ret || type != CLK_TYPE_OUTPUT)
			जारी;

		ret = zynqmp_घड़ी_get_topology(i, घड़ी[i].node,
						&घड़ी[i].num_nodes);
		अगर (ret)
			जारी;

		ret = zynqmp_घड़ी_get_parents(i, घड़ी[i].parent,
					       &घड़ी[i].num_parents);
		अगर (ret)
			जारी;
	पूर्ण
पूर्ण

/**
 * zynqmp_clk_setup() - Setup the घड़ी framework and रेजिस्टर घड़ीs
 * @np:		Device node
 *
 * Return: 0 on success अन्यथा error code
 */
अटल पूर्णांक zynqmp_clk_setup(काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	ret = zynqmp_pm_घड़ी_get_num_घड़ीs(&घड़ी_max_idx);
	अगर (ret)
		वापस ret;

	zynqmp_data = kzalloc(काष्ठा_size(zynqmp_data, hws, घड़ी_max_idx),
			      GFP_KERNEL);
	अगर (!zynqmp_data)
		वापस -ENOMEM;

	घड़ी = kसुस्मृति(घड़ी_max_idx, माप(*घड़ी), GFP_KERNEL);
	अगर (!घड़ी) अणु
		kमुक्त(zynqmp_data);
		वापस -ENOMEM;
	पूर्ण

	zynqmp_get_घड़ी_info();
	zynqmp_रेजिस्टर_घड़ीs(np);

	zynqmp_data->num = घड़ी_max_idx;
	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, zynqmp_data);

	वापस 0;
पूर्ण

अटल पूर्णांक zynqmp_घड़ी_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;

	ret = zynqmp_clk_setup(dev->of_node);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_घड़ी_of_match[] = अणु
	अणु.compatible = "xlnx,zynqmp-clk"पूर्ण,
	अणु.compatible = "xlnx,versal-clk"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zynqmp_घड़ी_of_match);

अटल काष्ठा platक्रमm_driver zynqmp_घड़ी_driver = अणु
	.driver = अणु
		.name = "zynqmp_clock",
		.of_match_table = zynqmp_घड़ी_of_match,
	पूर्ण,
	.probe = zynqmp_घड़ी_probe,
पूर्ण;
module_platक्रमm_driver(zynqmp_घड़ी_driver);
