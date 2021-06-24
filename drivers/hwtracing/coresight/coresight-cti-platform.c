<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, The Linaro Limited. All rights reserved.
 */
#समावेश <linux/coresight.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/arm/coresight-cti-dt.h>

#समावेश "coresight-cti.h"
#समावेश "coresight-priv.h"

/* Number of CTI संकेतs in the v8 architecturally defined connection */
#घोषणा NR_V8PE_IN_SIGS		2
#घोषणा NR_V8PE_OUT_SIGS	3
#घोषणा NR_V8ETM_INOUT_SIGS	4

/* CTI device tree trigger connection node keyword */
#घोषणा CTI_DT_CONNS		"trig-conns"

/* CTI device tree connection property keywords */
#घोषणा CTI_DT_V8ARCH_COMPAT	"arm,coresight-cti-v8-arch"
#घोषणा CTI_DT_CSDEV_ASSOC	"arm,cs-dev-assoc"
#घोषणा CTI_DT_TRIGIN_SIGS	"arm,trig-in-sigs"
#घोषणा CTI_DT_TRIGOUT_SIGS	"arm,trig-out-sigs"
#घोषणा CTI_DT_TRIGIN_TYPES	"arm,trig-in-types"
#घोषणा CTI_DT_TRIGOUT_TYPES	"arm,trig-out-types"
#घोषणा CTI_DT_FILTER_OUT_SIGS	"arm,trig-filters"
#घोषणा CTI_DT_CONN_NAME	"arm,trig-conn-name"
#घोषणा CTI_DT_CTM_ID		"arm,cti-ctm-id"

#अगर_घोषित CONFIG_OF
/*
 * CTI can be bound to a CPU, or a प्रणाली device.
 * CPU can be declared at the device top level or in a connections node
 * so need to check relative to node not device.
 */
अटल पूर्णांक of_cti_get_cpu_at_node(स्थिर काष्ठा device_node *node)
अणु
	पूर्णांक cpu;
	काष्ठा device_node *dn;

	अगर (node == शून्य)
		वापस -1;

	dn = of_parse_phandle(node, "cpu", 0);
	/* CTI affinity शेषs to no cpu */
	अगर (!dn)
		वापस -1;
	cpu = of_cpu_node_to_id(dn);
	of_node_put(dn);

	/* No Affinity  अगर no cpu nodes are found */
	वापस (cpu < 0) ? -1 : cpu;
पूर्ण

#अन्यथा
अटल पूर्णांक of_cti_get_cpu_at_node(स्थिर काष्ठा device_node *node)
अणु
	वापस -1;
पूर्ण

#पूर्ण_अगर

/*
 * CTI can be bound to a CPU, or a प्रणाली device.
 * CPU can be declared at the device top level or in a connections node
 * so need to check relative to node not device.
 */
अटल पूर्णांक cti_plat_get_cpu_at_node(काष्ठा fwnode_handle *fwnode)
अणु
	अगर (is_of_node(fwnode))
		वापस of_cti_get_cpu_at_node(to_of_node(fwnode));
	वापस -1;
पूर्ण

स्थिर अक्षर *cti_plat_get_node_name(काष्ठा fwnode_handle *fwnode)
अणु
	अगर (is_of_node(fwnode))
		वापस of_node_full_name(to_of_node(fwnode));
	वापस "unknown";
पूर्ण

/*
 * Extract a name from the fwnode.
 * If the device associated with the node is a coresight_device, then वापस
 * that name and the coresight_device poपूर्णांकer, otherwise वापस the node name.
 */
अटल स्थिर अक्षर *
cti_plat_get_csdev_or_node_name(काष्ठा fwnode_handle *fwnode,
				काष्ठा coresight_device **csdev)
अणु
	स्थिर अक्षर *name = शून्य;
	*csdev = coresight_find_csdev_by_fwnode(fwnode);
	अगर (*csdev)
		name = dev_name(&(*csdev)->dev);
	अन्यथा
		name = cti_plat_get_node_name(fwnode);
	वापस name;
पूर्ण

अटल bool cti_plat_node_name_eq(काष्ठा fwnode_handle *fwnode,
				  स्थिर अक्षर *name)
अणु
	अगर (is_of_node(fwnode))
		वापस of_node_name_eq(to_of_node(fwnode), name);
	वापस false;
पूर्ण

अटल पूर्णांक cti_plat_create_v8_eपंचांग_connection(काष्ठा device *dev,
					     काष्ठा cti_drvdata *drvdata)
अणु
	पूर्णांक ret = -ENOMEM, i;
	काष्ठा fwnode_handle *root_fwnode, *cs_fwnode;
	स्थिर अक्षर *assoc_name = शून्य;
	काष्ठा coresight_device *csdev;
	काष्ठा cti_trig_con *tc = शून्य;

	root_fwnode = dev_fwnode(dev);
	अगर (IS_ERR_OR_शून्य(root_fwnode))
		वापस -EINVAL;

	/* Can optionally have an eपंचांग node - वापस अगर not  */
	cs_fwnode = fwnode_find_reference(root_fwnode, CTI_DT_CSDEV_ASSOC, 0);
	अगर (IS_ERR(cs_fwnode))
		वापस 0;

	/* allocate memory */
	tc = cti_allocate_trig_con(dev, NR_V8ETM_INOUT_SIGS,
				   NR_V8ETM_INOUT_SIGS);
	अगर (!tc)
		जाओ create_v8_eपंचांग_out;

	/* build connection data */
	tc->con_in->used_mask = 0xF0; /* sigs <4,5,6,7> */
	tc->con_out->used_mask = 0xF0; /* sigs <4,5,6,7> */

	/*
	 * The EXTOUT type संकेतs from the ETM are connected to a set of input
	 * triggers on the CTI, the EXTIN being connected to output triggers.
	 */
	क्रम (i = 0; i < NR_V8ETM_INOUT_SIGS; i++) अणु
		tc->con_in->sig_types[i] = ETM_EXTOUT;
		tc->con_out->sig_types[i] = ETM_EXTIN;
	पूर्ण

	/*
	 * We look to see अगर the ETM coresight device associated with this
	 * handle has been रेजिस्टरed with the प्रणाली - i.e. probed beक्रमe
	 * this CTI. If so csdev will be non शून्य and we can use the device
	 * name and pass the csdev to the connection entry function where
	 * the association will be recorded.
	 * If not, then simply record the name in the connection data, the
	 * probing of the ETM will call पूर्णांकo the CTI driver API to update the
	 * association then.
	 */
	assoc_name = cti_plat_get_csdev_or_node_name(cs_fwnode, &csdev);
	ret = cti_add_connection_entry(dev, drvdata, tc, csdev, assoc_name);

create_v8_eपंचांग_out:
	fwnode_handle_put(cs_fwnode);
	वापस ret;
पूर्ण

/*
 * Create an architecturally defined v8 connection
 * must have a cpu, can have an ETM.
 */
अटल पूर्णांक cti_plat_create_v8_connections(काष्ठा device *dev,
					  काष्ठा cti_drvdata *drvdata)
अणु
	काष्ठा cti_device *cti_dev = &drvdata->ctidev;
	काष्ठा cti_trig_con *tc = शून्य;
	पूर्णांक cpuid = 0;
	अक्षर cpu_name_str[16];
	पूर्णांक ret = -ENOMEM;

	/* Must have a cpu node */
	cpuid = cti_plat_get_cpu_at_node(dev_fwnode(dev));
	अगर (cpuid < 0) अणु
		dev_warn(dev,
			 "ARM v8 architectural CTI connection: missing cpu\n");
		वापस -EINVAL;
	पूर्ण
	cti_dev->cpu = cpuid;

	/* Allocate the v8 cpu connection memory */
	tc = cti_allocate_trig_con(dev, NR_V8PE_IN_SIGS, NR_V8PE_OUT_SIGS);
	अगर (!tc)
		जाओ of_create_v8_out;

	/* Set the v8 PE CTI connection data */
	tc->con_in->used_mask = 0x3; /* sigs <0 1> */
	tc->con_in->sig_types[0] = PE_DBGTRIGGER;
	tc->con_in->sig_types[1] = PE_PMUIRQ;
	tc->con_out->used_mask = 0x7; /* sigs <0 1 2 > */
	tc->con_out->sig_types[0] = PE_EDBGREQ;
	tc->con_out->sig_types[1] = PE_DBGRESTART;
	tc->con_out->sig_types[2] = PE_CTIIRQ;
	scnम_लिखो(cpu_name_str, माप(cpu_name_str), "cpu%d", cpuid);

	ret = cti_add_connection_entry(dev, drvdata, tc, शून्य, cpu_name_str);
	अगर (ret)
		जाओ of_create_v8_out;

	/* Create the v8 ETM associated connection */
	ret = cti_plat_create_v8_eपंचांग_connection(dev, drvdata);
	अगर (ret)
		जाओ of_create_v8_out;

	/* filter pe_edbgreq - PE trigout sig <0> */
	drvdata->config.trig_out_filter |= 0x1;

of_create_v8_out:
	वापस ret;
पूर्ण

अटल पूर्णांक cti_plat_check_v8_arch_compatible(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);

	अगर (is_of_node(fwnode))
		वापस of_device_is_compatible(to_of_node(fwnode),
					       CTI_DT_V8ARCH_COMPAT);
	वापस 0;
पूर्ण

अटल पूर्णांक cti_plat_count_sig_elements(स्थिर काष्ठा fwnode_handle *fwnode,
				       स्थिर अक्षर *name)
अणु
	पूर्णांक nr_elem = fwnode_property_count_u32(fwnode, name);

	वापस (nr_elem < 0 ? 0 : nr_elem);
पूर्ण

अटल पूर्णांक cti_plat_पढ़ो_trig_group(काष्ठा cti_trig_grp *tgrp,
				    स्थिर काष्ठा fwnode_handle *fwnode,
				    स्थिर अक्षर *grp_name)
अणु
	पूर्णांक idx, err = 0;
	u32 *values;

	अगर (!tgrp->nr_sigs)
		वापस 0;

	values = kसुस्मृति(tgrp->nr_sigs, माप(u32), GFP_KERNEL);
	अगर (!values)
		वापस -ENOMEM;

	err = fwnode_property_पढ़ो_u32_array(fwnode, grp_name,
					     values, tgrp->nr_sigs);

	अगर (!err) अणु
		/* set the संकेत usage mask */
		क्रम (idx = 0; idx < tgrp->nr_sigs; idx++)
			tgrp->used_mask |= BIT(values[idx]);
	पूर्ण

	kमुक्त(values);
	वापस err;
पूर्ण

अटल पूर्णांक cti_plat_पढ़ो_trig_types(काष्ठा cti_trig_grp *tgrp,
				    स्थिर काष्ठा fwnode_handle *fwnode,
				    स्थिर अक्षर *type_name)
अणु
	पूर्णांक items, err = 0, nr_sigs;
	u32 *values = शून्य, i;

	/* allocate an array according to number of संकेतs in connection */
	nr_sigs = tgrp->nr_sigs;
	अगर (!nr_sigs)
		वापस 0;

	/* see अगर any types have been included in the device description */
	items = cti_plat_count_sig_elements(fwnode, type_name);
	अगर (items > nr_sigs)
		वापस -EINVAL;

	/* need an array to store the values अगरf there are any */
	अगर (items) अणु
		values = kसुस्मृति(items, माप(u32), GFP_KERNEL);
		अगर (!values)
			वापस -ENOMEM;

		err = fwnode_property_पढ़ो_u32_array(fwnode, type_name,
						     values, items);
		अगर (err)
			जाओ पढ़ो_trig_types_out;
	पूर्ण

	/*
	 * Match type id to संकेत index, 1st type to 1st index etc.
	 * If fewer types than संकेतs शेष reमुख्यder to GEN_IO.
	 */
	क्रम (i = 0; i < nr_sigs; i++) अणु
		अगर (i < items) अणु
			tgrp->sig_types[i] =
				values[i] < CTI_TRIG_MAX ? values[i] : GEN_IO;
		पूर्ण अन्यथा अणु
			tgrp->sig_types[i] = GEN_IO;
		पूर्ण
	पूर्ण

पढ़ो_trig_types_out:
	kमुक्त(values);
	वापस err;
पूर्ण

अटल पूर्णांक cti_plat_process_filter_sigs(काष्ठा cti_drvdata *drvdata,
					स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा cti_trig_grp *tg = शून्य;
	पूर्णांक err = 0, nr_filter_sigs;

	nr_filter_sigs = cti_plat_count_sig_elements(fwnode,
						     CTI_DT_FILTER_OUT_SIGS);
	अगर (nr_filter_sigs == 0)
		वापस 0;

	अगर (nr_filter_sigs > drvdata->config.nr_trig_max)
		वापस -EINVAL;

	tg = kzalloc(माप(*tg), GFP_KERNEL);
	अगर (!tg)
		वापस -ENOMEM;

	err = cti_plat_पढ़ो_trig_group(tg, fwnode, CTI_DT_FILTER_OUT_SIGS);
	अगर (!err)
		drvdata->config.trig_out_filter |= tg->used_mask;

	kमुक्त(tg);
	वापस err;
पूर्ण

अटल पूर्णांक cti_plat_create_connection(काष्ठा device *dev,
				      काष्ठा cti_drvdata *drvdata,
				      काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा cti_trig_con *tc = शून्य;
	पूर्णांक cpuid = -1, err = 0;
	काष्ठा coresight_device *csdev = शून्य;
	स्थिर अक्षर *assoc_name = "unknown";
	अक्षर cpu_name_str[16];
	पूर्णांक nr_sigs_in, nr_sigs_out;

	/* look to see how many in and out संकेतs we have */
	nr_sigs_in = cti_plat_count_sig_elements(fwnode, CTI_DT_TRIGIN_SIGS);
	nr_sigs_out = cti_plat_count_sig_elements(fwnode, CTI_DT_TRIGOUT_SIGS);

	अगर ((nr_sigs_in > drvdata->config.nr_trig_max) ||
	    (nr_sigs_out > drvdata->config.nr_trig_max))
		वापस -EINVAL;

	tc = cti_allocate_trig_con(dev, nr_sigs_in, nr_sigs_out);
	अगर (!tc)
		वापस -ENOMEM;

	/* look क्रम the संकेतs properties. */
	err = cti_plat_पढ़ो_trig_group(tc->con_in, fwnode,
				       CTI_DT_TRIGIN_SIGS);
	अगर (err)
		जाओ create_con_err;

	err = cti_plat_पढ़ो_trig_types(tc->con_in, fwnode,
				       CTI_DT_TRIGIN_TYPES);
	अगर (err)
		जाओ create_con_err;

	err = cti_plat_पढ़ो_trig_group(tc->con_out, fwnode,
				       CTI_DT_TRIGOUT_SIGS);
	अगर (err)
		जाओ create_con_err;

	err = cti_plat_पढ़ो_trig_types(tc->con_out, fwnode,
				       CTI_DT_TRIGOUT_TYPES);
	अगर (err)
		जाओ create_con_err;

	err = cti_plat_process_filter_sigs(drvdata, fwnode);
	अगर (err)
		जाओ create_con_err;

	/* पढ़ो the connection name अगर set - may be overridden by later */
	fwnode_property_पढ़ो_string(fwnode, CTI_DT_CONN_NAME, &assoc_name);

	/* associated cpu ? */
	cpuid = cti_plat_get_cpu_at_node(fwnode);
	अगर (cpuid >= 0) अणु
		drvdata->ctidev.cpu = cpuid;
		scnम_लिखो(cpu_name_str, माप(cpu_name_str), "cpu%d", cpuid);
		assoc_name = cpu_name_str;
	पूर्ण अन्यथा अणु
		/* associated device ? */
		काष्ठा fwnode_handle *cs_fwnode = fwnode_find_reference(fwnode,
									CTI_DT_CSDEV_ASSOC,
									0);
		अगर (!IS_ERR(cs_fwnode)) अणु
			assoc_name = cti_plat_get_csdev_or_node_name(cs_fwnode,
								     &csdev);
			fwnode_handle_put(cs_fwnode);
		पूर्ण
	पूर्ण
	/* set up a connection */
	err = cti_add_connection_entry(dev, drvdata, tc, csdev, assoc_name);

create_con_err:
	वापस err;
पूर्ण

अटल पूर्णांक cti_plat_create_impdef_connections(काष्ठा device *dev,
					      काष्ठा cti_drvdata *drvdata)
अणु
	पूर्णांक rc = 0;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	काष्ठा fwnode_handle *child = शून्य;

	अगर (IS_ERR_OR_शून्य(fwnode))
		वापस -EINVAL;

	fwnode_क्रम_each_child_node(fwnode, child) अणु
		अगर (cti_plat_node_name_eq(child, CTI_DT_CONNS))
			rc = cti_plat_create_connection(dev, drvdata,
							child);
		अगर (rc != 0)
			अवरोध;
	पूर्ण
	fwnode_handle_put(child);

	वापस rc;
पूर्ण

/* get the hardware configuration & connection data. */
अटल पूर्णांक cti_plat_get_hw_data(काष्ठा device *dev, काष्ठा cti_drvdata *drvdata)
अणु
	पूर्णांक rc = 0;
	काष्ठा cti_device *cti_dev = &drvdata->ctidev;

	/* get any CTM ID - शेषs to 0 */
	device_property_पढ़ो_u32(dev, CTI_DT_CTM_ID, &cti_dev->cपंचांग_id);

	/* check क्रम a v8 architectural CTI device */
	अगर (cti_plat_check_v8_arch_compatible(dev))
		rc = cti_plat_create_v8_connections(dev, drvdata);
	अन्यथा
		rc = cti_plat_create_impdef_connections(dev, drvdata);
	अगर (rc)
		वापस rc;

	/* अगर no connections, just add a single शेष based on max IN-OUT */
	अगर (cti_dev->nr_trig_con == 0)
		rc = cti_add_शेष_connection(dev, drvdata);
	वापस rc;
पूर्ण

काष्ठा coresight_platक्रमm_data *
coresight_cti_get_platक्रमm_data(काष्ठा device *dev)
अणु
	पूर्णांक ret = -ENOENT;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (IS_ERR_OR_शून्य(fwnode))
		जाओ error;

	/*
	 * Alloc platक्रमm data but leave it zero init. CTI करोes not use the
	 * same connection infraकाष्ठाuree as trace path components but an
	 * empty काष्ठा enables us to use the standard coresight component
	 * registration code.
	 */
	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	/* get some CTI specअगरics */
	ret = cti_plat_get_hw_data(dev, drvdata);

	अगर (!ret)
		वापस pdata;
error:
	वापस ERR_PTR(ret);
पूर्ण
