<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/coresight.h>
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/smp_plat.h>

#समावेश "coresight-priv.h"
/*
 * coresight_alloc_conns: Allocate connections record क्रम each output
 * port from the device.
 */
अटल पूर्णांक coresight_alloc_conns(काष्ठा device *dev,
				 काष्ठा coresight_platक्रमm_data *pdata)
अणु
	अगर (pdata->nr_outport) अणु
		pdata->conns = devm_kसुस्मृति(dev, pdata->nr_outport,
					    माप(*pdata->conns), GFP_KERNEL);
		अगर (!pdata->conns)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा device *
coresight_find_device_by_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *dev = शून्य;

	/*
	 * If we have a non-configurable replicator, it will be found on the
	 * platक्रमm bus.
	 */
	dev = bus_find_device_by_fwnode(&platक्रमm_bus_type, fwnode);
	अगर (dev)
		वापस dev;

	/*
	 * We have a configurable component - circle through the AMBA bus
	 * looking क्रम the device that matches the endpoपूर्णांक node.
	 */
	वापस bus_find_device_by_fwnode(&amba_bustype, fwnode);
पूर्ण

/*
 * Find a रेजिस्टरed coresight device from a device fwnode.
 * The node info is associated with the AMBA parent, but the
 * csdev keeps a copy so iterate round the coresight bus to
 * find the device.
 */
काष्ठा coresight_device *
coresight_find_csdev_by_fwnode(काष्ठा fwnode_handle *r_fwnode)
अणु
	काष्ठा device *dev;
	काष्ठा coresight_device *csdev = शून्य;

	dev = bus_find_device_by_fwnode(&coresight_bustype, r_fwnode);
	अगर (dev) अणु
		csdev = to_coresight_device(dev);
		put_device(dev);
	पूर्ण
	वापस csdev;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_find_csdev_by_fwnode);

#अगर_घोषित CONFIG_OF
अटल अंतरभूत bool of_coresight_legacy_ep_is_input(काष्ठा device_node *ep)
अणु
	वापस of_property_पढ़ो_bool(ep, "slave-mode");
पूर्ण

अटल व्योम of_coresight_get_ports_legacy(स्थिर काष्ठा device_node *node,
					  पूर्णांक *nr_inport, पूर्णांक *nr_outport)
अणु
	काष्ठा device_node *ep = शून्य;
	काष्ठा of_endpoपूर्णांक endpoपूर्णांक;
	पूर्णांक in = 0, out = 0;

	/*
	 * Aव्योम warnings in of_graph_get_next_endpoपूर्णांक()
	 * अगर the device करोesn't have any graph connections
	 */
	अगर (!of_graph_is_present(node))
		वापस;
	करो अणु
		ep = of_graph_get_next_endpoपूर्णांक(node, ep);
		अगर (!ep)
			अवरोध;

		अगर (of_graph_parse_endpoपूर्णांक(ep, &endpoपूर्णांक))
			जारी;

		अगर (of_coresight_legacy_ep_is_input(ep)) अणु
			in = (endpoपूर्णांक.port + 1 > in) ?
				endpoपूर्णांक.port + 1 : in;
		पूर्ण अन्यथा अणु
			out = (endpoपूर्णांक.port + 1) > out ?
				endpoपूर्णांक.port + 1 : out;
		पूर्ण

	पूर्ण जबतक (ep);

	*nr_inport = in;
	*nr_outport = out;
पूर्ण

अटल काष्ठा device_node *of_coresight_get_port_parent(काष्ठा device_node *ep)
अणु
	काष्ठा device_node *parent = of_graph_get_port_parent(ep);

	/*
	 * Skip one-level up to the real device node, अगर we
	 * are using the new bindings.
	 */
	अगर (of_node_name_eq(parent, "in-ports") ||
	    of_node_name_eq(parent, "out-ports"))
		parent = of_get_next_parent(parent);

	वापस parent;
पूर्ण

अटल अंतरभूत काष्ठा device_node *
of_coresight_get_input_ports_node(स्थिर काष्ठा device_node *node)
अणु
	वापस of_get_child_by_name(node, "in-ports");
पूर्ण

अटल अंतरभूत काष्ठा device_node *
of_coresight_get_output_ports_node(स्थिर काष्ठा device_node *node)
अणु
	वापस of_get_child_by_name(node, "out-ports");
पूर्ण

अटल अंतरभूत पूर्णांक
of_coresight_count_ports(काष्ठा device_node *port_parent)
अणु
	पूर्णांक i = 0;
	काष्ठा device_node *ep = शून्य;
	काष्ठा of_endpoपूर्णांक endpoपूर्णांक;

	जबतक ((ep = of_graph_get_next_endpoपूर्णांक(port_parent, ep))) अणु
		/* Defer error handling to parsing */
		अगर (of_graph_parse_endpoपूर्णांक(ep, &endpoपूर्णांक))
			जारी;
		अगर (endpoपूर्णांक.port + 1 > i)
			i = endpoपूर्णांक.port + 1;
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम of_coresight_get_ports(स्थिर काष्ठा device_node *node,
				   पूर्णांक *nr_inport, पूर्णांक *nr_outport)
अणु
	काष्ठा device_node *input_ports = शून्य, *output_ports = शून्य;

	input_ports = of_coresight_get_input_ports_node(node);
	output_ports = of_coresight_get_output_ports_node(node);

	अगर (input_ports || output_ports) अणु
		अगर (input_ports) अणु
			*nr_inport = of_coresight_count_ports(input_ports);
			of_node_put(input_ports);
		पूर्ण
		अगर (output_ports) अणु
			*nr_outport = of_coresight_count_ports(output_ports);
			of_node_put(output_ports);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Fall back to legacy DT bindings parsing */
		of_coresight_get_ports_legacy(node, nr_inport, nr_outport);
	पूर्ण
पूर्ण

अटल पूर्णांक of_coresight_get_cpu(काष्ठा device *dev)
अणु
	पूर्णांक cpu;
	काष्ठा device_node *dn;

	अगर (!dev->of_node)
		वापस -ENODEV;

	dn = of_parse_phandle(dev->of_node, "cpu", 0);
	अगर (!dn)
		वापस -ENODEV;

	cpu = of_cpu_node_to_id(dn);
	of_node_put(dn);

	वापस cpu;
पूर्ण

/*
 * of_coresight_parse_endpoपूर्णांक : Parse the given output endpoपूर्णांक @ep
 * and fill the connection inक्रमmation in @conn
 *
 * Parses the local port, remote device name and the remote port.
 *
 * Returns :
 *	 0	- If the parsing completed without any fatal errors.
 *	-Errno	- Fatal error, पात the scanning.
 */
अटल पूर्णांक of_coresight_parse_endpoपूर्णांक(काष्ठा device *dev,
				       काष्ठा device_node *ep,
				       काष्ठा coresight_platक्रमm_data *pdata)
अणु
	पूर्णांक ret = 0;
	काष्ठा of_endpoपूर्णांक endpoपूर्णांक, rendpoपूर्णांक;
	काष्ठा device_node *rparent = शून्य;
	काष्ठा device_node *rep = शून्य;
	काष्ठा device *rdev = शून्य;
	काष्ठा fwnode_handle *rdev_fwnode;
	काष्ठा coresight_connection *conn;

	करो अणु
		/* Parse the local port details */
		अगर (of_graph_parse_endpoपूर्णांक(ep, &endpoपूर्णांक))
			अवरोध;
		/*
		 * Get a handle on the remote endpoपूर्णांक and the device it is
		 * attached to.
		 */
		rep = of_graph_get_remote_endpoपूर्णांक(ep);
		अगर (!rep)
			अवरोध;
		rparent = of_coresight_get_port_parent(rep);
		अगर (!rparent)
			अवरोध;
		अगर (of_graph_parse_endpoपूर्णांक(rep, &rendpoपूर्णांक))
			अवरोध;

		rdev_fwnode = of_fwnode_handle(rparent);
		/* If the remote device is not available, defer probing */
		rdev = coresight_find_device_by_fwnode(rdev_fwnode);
		अगर (!rdev) अणु
			ret = -EPROBE_DEFER;
			अवरोध;
		पूर्ण

		conn = &pdata->conns[endpoपूर्णांक.port];
		अगर (conn->child_fwnode) अणु
			dev_warn(dev, "Duplicate output port %d\n",
				 endpoपूर्णांक.port);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		conn->outport = endpoपूर्णांक.port;
		/*
		 * Hold the refcount to the target device. This could be
		 * released via:
		 * 1) coresight_release_platक्रमm_data() अगर the probe fails or
		 *    this device is unरेजिस्टरed.
		 * 2) While removing the target device via
		 *    coresight_हटाओ_match()
		 */
		conn->child_fwnode = fwnode_handle_get(rdev_fwnode);
		conn->child_port = rendpoपूर्णांक.port;
		/* Connection record updated */
	पूर्ण जबतक (0);

	of_node_put(rparent);
	of_node_put(rep);
	put_device(rdev);

	वापस ret;
पूर्ण

अटल पूर्णांक of_get_coresight_platक्रमm_data(काष्ठा device *dev,
					  काष्ठा coresight_platक्रमm_data *pdata)
अणु
	पूर्णांक ret = 0;
	काष्ठा device_node *ep = शून्य;
	स्थिर काष्ठा device_node *parent = शून्य;
	bool legacy_binding = false;
	काष्ठा device_node *node = dev->of_node;

	/* Get the number of input and output port क्रम this component */
	of_coresight_get_ports(node, &pdata->nr_inport, &pdata->nr_outport);

	/* If there are no output connections, we are करोne */
	अगर (!pdata->nr_outport)
		वापस 0;

	ret = coresight_alloc_conns(dev, pdata);
	अगर (ret)
		वापस ret;

	parent = of_coresight_get_output_ports_node(node);
	/*
	 * If the DT uses obsoleted bindings, the ports are listed
	 * under the device and we need to filter out the input
	 * ports.
	 */
	अगर (!parent) अणु
		legacy_binding = true;
		parent = node;
		dev_warn_once(dev, "Uses obsolete Coresight DT bindings\n");
	पूर्ण

	/* Iterate through each output port to discover topology */
	जबतक ((ep = of_graph_get_next_endpoपूर्णांक(parent, ep))) अणु
		/*
		 * Legacy binding mixes input/output ports under the
		 * same parent. So, skip the input ports अगर we are dealing
		 * with legacy binding, as they processed with their
		 * connected output ports.
		 */
		अगर (legacy_binding && of_coresight_legacy_ep_is_input(ep))
			जारी;

		ret = of_coresight_parse_endpoपूर्णांक(dev, ep, pdata);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
of_get_coresight_platक्रमm_data(काष्ठा device *dev,
			       काष्ठा coresight_platक्रमm_data *pdata)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत पूर्णांक of_coresight_get_cpu(काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI

#समावेश <acpi/actypes.h>
#समावेश <acpi/processor.h>

/* ACPI Graph _DSD UUID : "ab02a46b-74c7-45a2-bd68-f7d344ef2153" */
अटल स्थिर guid_t acpi_graph_uuid = GUID_INIT(0xab02a46b, 0x74c7, 0x45a2,
						0xbd, 0x68, 0xf7, 0xd3,
						0x44, 0xef, 0x21, 0x53);
/* Coresight ACPI Graph UUID : "3ecbc8b6-1d0e-4fb3-8107-e627f805c6cd" */
अटल स्थिर guid_t coresight_graph_uuid = GUID_INIT(0x3ecbc8b6, 0x1d0e, 0x4fb3,
						     0x81, 0x07, 0xe6, 0x27,
						     0xf8, 0x05, 0xc6, 0xcd);
#घोषणा ACPI_CORESIGHT_LINK_SLAVE	0
#घोषणा ACPI_CORESIGHT_LINK_MASTER	1

अटल अंतरभूत bool is_acpi_guid(स्थिर जोड़ acpi_object *obj)
अणु
	वापस (obj->type == ACPI_TYPE_BUFFER) && (obj->buffer.length == 16);
पूर्ण

/*
 * acpi_guid_matches	- Checks अगर the given object is a GUID object and
 * that it matches the supplied the GUID.
 */
अटल अंतरभूत bool acpi_guid_matches(स्थिर जोड़ acpi_object *obj,
				   स्थिर guid_t *guid)
अणु
	वापस is_acpi_guid(obj) &&
	       guid_equal((guid_t *)obj->buffer.poपूर्णांकer, guid);
पूर्ण

अटल अंतरभूत bool is_acpi_dsd_graph_guid(स्थिर जोड़ acpi_object *obj)
अणु
	वापस acpi_guid_matches(obj, &acpi_graph_uuid);
पूर्ण

अटल अंतरभूत bool is_acpi_coresight_graph_guid(स्थिर जोड़ acpi_object *obj)
अणु
	वापस acpi_guid_matches(obj, &coresight_graph_uuid);
पूर्ण

अटल अंतरभूत bool is_acpi_coresight_graph(स्थिर जोड़ acpi_object *obj)
अणु
	स्थिर जोड़ acpi_object *graphid, *guid, *links;

	अगर (obj->type != ACPI_TYPE_PACKAGE ||
	    obj->package.count < 3)
		वापस false;

	graphid = &obj->package.elements[0];
	guid = &obj->package.elements[1];
	links = &obj->package.elements[2];

	अगर (graphid->type != ACPI_TYPE_INTEGER ||
	    links->type != ACPI_TYPE_INTEGER)
		वापस false;

	वापस is_acpi_coresight_graph_guid(guid);
पूर्ण

/*
 * acpi_validate_dsd_graph	- Make sure the given _DSD graph conक्रमms
 * to the ACPI _DSD Graph specअगरication.
 *
 * ACPI Devices Graph property has the following क्रमmat:
 *  अणु
 *	Revision	- Integer, must be 0
 *	NumberOfGraphs	- Integer, N indicating the following list.
 *	Graph[1],
 *	 ...
 *	Graph[N]
 *  पूर्ण
 *
 * And each Graph entry has the following क्रमmat:
 *  अणु
 *	GraphID		- Integer, identअगरying a graph the device beदीर्घs to.
 *	UUID		- UUID identअगरying the specअगरication that governs
 *			  this graph. (e.g, see is_acpi_coresight_graph())
 *	NumberOfLinks	- Number "N" of connections on this node of the graph.
 *	Links[1]
 *	...
 *	Links[N]
 *  पूर्ण
 *
 * Where each "Links" entry has the following क्रमmat:
 *
 * अणु
 *	SourcePortAddress	- Integer
 *	DestinationPortAddress	- Integer
 *	DestinationDeviceName	- Reference to another device
 *	( --- CoreSight specअगरic extensions below ---)
 *	DirectionOfFlow		- Integer 1 क्रम output(master)
 *				  0 क्रम input(slave)
 * पूर्ण
 *
 * e.g:
 * For a Funnel device
 *
 * Device(MFUN) अणु
 *   ...
 *
 *   Name (_DSD, Package() अणु
 *	// DSD Package contains tuples of अणु  Proeprty_Type_UUID, Package() पूर्ण
 *	ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"), //Std. Property UUID
 *	Package() अणु
 *		Package(2) अणु "property-name", <property-value> पूर्ण
 *	पूर्ण,
 *
 *	ToUUID("ab02a46b-74c7-45a2-bd68-f7d344ef2153"), // ACPI Graph UUID
 *	Package() अणु
 *	  0,		// Revision
 *	  1,		// NumberOfGraphs.
 *	  Package() अणु	// Graph[0] Package
 *	     1,		// GraphID
 *	     // Coresight Graph UUID
 *	     ToUUID("3ecbc8b6-1d0e-4fb3-8107-e627f805c6cd"),
 *	     3,		// NumberOfLinks aka ports
 *	     // Link[0]: Output_0 -> Replicator:Input_0
 *	     Package () अणु 0, 0, \_SB_.RPL0, 1 पूर्ण,
 *	     // Link[1]: Input_0 <- Cluster0_Funnel0:Output_0
 *	     Package () अणु 0, 0, \_SB_.CLU0.FUN0, 0 पूर्ण,
 *	     // Link[2]: Input_1 <- Cluster1_Funnel0:Output_0
 *	      Package () अणु 1, 0, \_SB_.CLU1.FUN0, 0 पूर्ण,
 *	  पूर्ण	// End of Graph[0] Package
 *
 *	पूर्ण, // End of ACPI Graph Property
 *  पूर्ण)
 */
अटल अंतरभूत bool acpi_validate_dsd_graph(स्थिर जोड़ acpi_object *graph)
अणु
	पूर्णांक i, n;
	स्थिर जोड़ acpi_object *rev, *nr_graphs;

	/* The graph must contain at least the Revision and Number of Graphs */
	अगर (graph->package.count < 2)
		वापस false;

	rev = &graph->package.elements[0];
	nr_graphs = &graph->package.elements[1];

	अगर (rev->type != ACPI_TYPE_INTEGER ||
	    nr_graphs->type != ACPI_TYPE_INTEGER)
		वापस false;

	/* We only support revision 0 */
	अगर (rev->पूर्णांकeger.value != 0)
		वापस false;

	n = nr_graphs->पूर्णांकeger.value;
	/* CoreSight devices are only part of a single Graph */
	अगर (n != 1)
		वापस false;

	/* Make sure the ACPI graph package has right number of elements */
	अगर (graph->package.count != (n + 2))
		वापस false;

	/*
	 * Each entry must be a graph package with at least 3 members :
	 * अणु GraphID, UUID, NumberOfLinks(n), Links[.],... पूर्ण
	 */
	क्रम (i = 2; i < n + 2; i++) अणु
		स्थिर जोड़ acpi_object *obj = &graph->package.elements[i];

		अगर (obj->type != ACPI_TYPE_PACKAGE ||
		    obj->package.count < 3)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* acpi_get_dsd_graph	- Find the _DSD Graph property क्रम the given device. */
अटल स्थिर जोड़ acpi_object *
acpi_get_dsd_graph(काष्ठा acpi_device *adev)
अणु
	पूर्णांक i;
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER पूर्ण;
	acpi_status status;
	स्थिर जोड़ acpi_object *dsd;

	status = acpi_evaluate_object_typed(adev->handle, "_DSD", शून्य,
					    &buf, ACPI_TYPE_PACKAGE);
	अगर (ACPI_FAILURE(status))
		वापस शून्य;

	dsd = buf.poपूर्णांकer;

	/*
	 * _DSD property consists tuples अणु Prop_UUID, Package() पूर्ण
	 * Iterate through all the packages and find the Graph.
	 */
	क्रम (i = 0; i + 1 < dsd->package.count; i += 2) अणु
		स्थिर जोड़ acpi_object *guid, *package;

		guid = &dsd->package.elements[i];
		package = &dsd->package.elements[i + 1];

		/* All _DSD elements must have a UUID and a Package */
		अगर (!is_acpi_guid(guid) || package->type != ACPI_TYPE_PACKAGE)
			अवरोध;
		/* Skip the non-Graph _DSD packages */
		अगर (!is_acpi_dsd_graph_guid(guid))
			जारी;
		अगर (acpi_validate_dsd_graph(package))
			वापस package;
		/* Invalid graph क्रमmat, जारी */
		dev_warn(&adev->dev, "Invalid Graph _DSD property\n");
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool
acpi_validate_coresight_graph(स्थिर जोड़ acpi_object *cs_graph)
अणु
	पूर्णांक nlinks;

	nlinks = cs_graph->package.elements[2].पूर्णांकeger.value;
	/*
	 * Graph must have the following fields :
	 * अणु GraphID, GraphUUID, NumberOfLinks, Links... पूर्ण
	 */
	अगर (cs_graph->package.count != (nlinks + 3))
		वापस false;
	/* The links are validated in acpi_coresight_parse_link() */
	वापस true;
पूर्ण

/*
 * acpi_get_coresight_graph	- Parse the device _DSD tables and find
 * the Graph property matching the CoreSight Graphs.
 *
 * Returns the poपूर्णांकer to the CoreSight Graph Package when found. Otherwise
 * वापसs शून्य.
 */
अटल स्थिर जोड़ acpi_object *
acpi_get_coresight_graph(काष्ठा acpi_device *adev)
अणु
	स्थिर जोड़ acpi_object *graph_list, *graph;
	पूर्णांक i, nr_graphs;

	graph_list = acpi_get_dsd_graph(adev);
	अगर (!graph_list)
		वापस graph_list;

	nr_graphs = graph_list->package.elements[1].पूर्णांकeger.value;

	क्रम (i = 2; i < nr_graphs + 2; i++) अणु
		graph = &graph_list->package.elements[i];
		अगर (!is_acpi_coresight_graph(graph))
			जारी;
		अगर (acpi_validate_coresight_graph(graph))
			वापस graph;
		/* Invalid graph क्रमmat */
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * acpi_coresight_parse_link	- Parse the given Graph connection
 * of the device and populate the coresight_connection क्रम an output
 * connection.
 *
 * CoreSight Graph specअगरication mandates that the direction of the data
 * flow must be specअगरied in the link. i.e,
 *
 *	SourcePortAddress,	// Integer
 *	DestinationPortAddress,	// Integer
 *	DestinationDeviceName,	// Reference to another device
 *	DirectionOfFlow,	// 1 क्रम output(master), 0 क्रम input(slave)
 *
 * Returns the direction of the data flow [ Input(slave) or Output(master) ]
 * upon success.
 * Returns an negative error number otherwise.
 */
अटल पूर्णांक acpi_coresight_parse_link(काष्ठा acpi_device *adev,
				     स्थिर जोड़ acpi_object *link,
				     काष्ठा coresight_connection *conn)
अणु
	पूर्णांक rc, dir;
	स्थिर जोड़ acpi_object *fields;
	काष्ठा acpi_device *r_adev;
	काष्ठा device *rdev;

	अगर (link->type != ACPI_TYPE_PACKAGE ||
	    link->package.count != 4)
		वापस -EINVAL;

	fields = link->package.elements;

	अगर (fields[0].type != ACPI_TYPE_INTEGER ||
	    fields[1].type != ACPI_TYPE_INTEGER ||
	    fields[2].type != ACPI_TYPE_LOCAL_REFERENCE ||
	    fields[3].type != ACPI_TYPE_INTEGER)
		वापस -EINVAL;

	rc = acpi_bus_get_device(fields[2].reference.handle, &r_adev);
	अगर (rc)
		वापस rc;

	dir = fields[3].पूर्णांकeger.value;
	अगर (dir == ACPI_CORESIGHT_LINK_MASTER) अणु
		conn->outport = fields[0].पूर्णांकeger.value;
		conn->child_port = fields[1].पूर्णांकeger.value;
		rdev = coresight_find_device_by_fwnode(&r_adev->fwnode);
		अगर (!rdev)
			वापस -EPROBE_DEFER;
		/*
		 * Hold the refcount to the target device. This could be
		 * released via:
		 * 1) coresight_release_platक्रमm_data() अगर the probe fails or
		 *    this device is unरेजिस्टरed.
		 * 2) While removing the target device via
		 *    coresight_हटाओ_match().
		 */
		conn->child_fwnode = fwnode_handle_get(&r_adev->fwnode);
	पूर्ण अन्यथा अगर (dir == ACPI_CORESIGHT_LINK_SLAVE) अणु
		/*
		 * We are only पूर्णांकerested in the port number
		 * क्रम the input ports at this component.
		 * Store the port number in child_port.
		 */
		conn->child_port = fields[0].पूर्णांकeger.value;
	पूर्ण अन्यथा अणु
		/* Invalid direction */
		वापस -EINVAL;
	पूर्ण

	वापस dir;
पूर्ण

/*
 * acpi_coresight_parse_graph	- Parse the _DSD CoreSight graph
 * connection inक्रमmation and populate the supplied coresight_platक्रमm_data
 * instance.
 */
अटल पूर्णांक acpi_coresight_parse_graph(काष्ठा acpi_device *adev,
				      काष्ठा coresight_platक्रमm_data *pdata)
अणु
	पूर्णांक rc, i, nlinks;
	स्थिर जोड़ acpi_object *graph;
	काष्ठा coresight_connection *conns, *ptr;

	pdata->nr_inport = pdata->nr_outport = 0;
	graph = acpi_get_coresight_graph(adev);
	अगर (!graph)
		वापस -ENOENT;

	nlinks = graph->package.elements[2].पूर्णांकeger.value;
	अगर (!nlinks)
		वापस 0;

	/*
	 * To aव्योम scanning the table twice (once क्रम finding the number of
	 * output links and then later क्रम parsing the output links),
	 * cache the links inक्रमmation in one go and then later copy
	 * it to the pdata.
	 */
	conns = devm_kसुस्मृति(&adev->dev, nlinks, माप(*conns), GFP_KERNEL);
	अगर (!conns)
		वापस -ENOMEM;
	ptr = conns;
	क्रम (i = 0; i < nlinks; i++) अणु
		स्थिर जोड़ acpi_object *link = &graph->package.elements[3 + i];
		पूर्णांक dir;

		dir = acpi_coresight_parse_link(adev, link, ptr);
		अगर (dir < 0)
			वापस dir;

		अगर (dir == ACPI_CORESIGHT_LINK_MASTER) अणु
			अगर (ptr->outport >= pdata->nr_outport)
				pdata->nr_outport = ptr->outport + 1;
			ptr++;
		पूर्ण अन्यथा अणु
			WARN_ON(pdata->nr_inport == ptr->child_port + 1);
			/*
			 * We करो not track input port connections क्रम a device.
			 * However we need the highest port number described,
			 * which can be recorded now and reuse this connection
			 * record क्रम an output connection. Hence, करो not move
			 * the ptr क्रम input connections
			 */
			अगर (ptr->child_port >= pdata->nr_inport)
				pdata->nr_inport = ptr->child_port + 1;
		पूर्ण
	पूर्ण

	rc = coresight_alloc_conns(&adev->dev, pdata);
	अगर (rc)
		वापस rc;

	/* Copy the connection inक्रमmation to the final location */
	क्रम (i = 0; conns + i < ptr; i++) अणु
		पूर्णांक port = conns[i].outport;

		/* Duplicate output port */
		WARN_ON(pdata->conns[port].child_fwnode);
		pdata->conns[port] = conns[i];
	पूर्ण

	devm_kमुक्त(&adev->dev, conns);
	वापस 0;
पूर्ण

/*
 * acpi_handle_to_logical_cpuid - Map a given acpi_handle to the
 * logical CPU id of the corresponding CPU device.
 *
 * Returns the logical CPU id when found. Otherwise वापसs >= nr_cpus_id.
 */
अटल पूर्णांक
acpi_handle_to_logical_cpuid(acpi_handle handle)
अणु
	पूर्णांक i;
	काष्ठा acpi_processor *pr;

	क्रम_each_possible_cpu(i) अणु
		pr = per_cpu(processors, i);
		अगर (pr && pr->handle == handle)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

/*
 * acpi_coresigh_get_cpu - Find the logical CPU id of the CPU associated
 * with this coresight device. With ACPI bindings, the CoreSight components
 * are listed as child device of the associated CPU.
 *
 * Returns the logical CPU id when found. Otherwise वापसs 0.
 */
अटल पूर्णांक acpi_coresight_get_cpu(काष्ठा device *dev)
अणु
	पूर्णांक cpu;
	acpi_handle cpu_handle;
	acpi_status status;
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);

	अगर (!adev)
		वापस -ENODEV;
	status = acpi_get_parent(adev->handle, &cpu_handle);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	cpu = acpi_handle_to_logical_cpuid(cpu_handle);
	अगर (cpu >= nr_cpu_ids)
		वापस -ENODEV;
	वापस cpu;
पूर्ण

अटल पूर्णांक
acpi_get_coresight_platक्रमm_data(काष्ठा device *dev,
				 काष्ठा coresight_platक्रमm_data *pdata)
अणु
	काष्ठा acpi_device *adev;

	adev = ACPI_COMPANION(dev);
	अगर (!adev)
		वापस -EINVAL;

	वापस acpi_coresight_parse_graph(adev, pdata);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक
acpi_get_coresight_platक्रमm_data(काष्ठा device *dev,
				 काष्ठा coresight_platक्रमm_data *pdata)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_coresight_get_cpu(काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

पूर्णांक coresight_get_cpu(काष्ठा device *dev)
अणु
	अगर (is_of_node(dev->fwnode))
		वापस of_coresight_get_cpu(dev);
	अन्यथा अगर (is_acpi_device_node(dev->fwnode))
		वापस acpi_coresight_get_cpu(dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_get_cpu);

काष्ठा coresight_platक्रमm_data *
coresight_get_platक्रमm_data(काष्ठा device *dev)
अणु
	पूर्णांक ret = -ENOENT;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);

	अगर (IS_ERR_OR_शून्य(fwnode))
		जाओ error;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (is_of_node(fwnode))
		ret = of_get_coresight_platक्रमm_data(dev, pdata);
	अन्यथा अगर (is_acpi_device_node(fwnode))
		ret = acpi_get_coresight_platक्रमm_data(dev, pdata);

	अगर (!ret)
		वापस pdata;
error:
	अगर (!IS_ERR_OR_शून्य(pdata))
		/* Cleanup the connection inक्रमmation */
		coresight_release_platक्रमm_data(शून्य, pdata);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(coresight_get_platक्रमm_data);
