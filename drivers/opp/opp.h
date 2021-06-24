<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Generic OPP Interface
 *
 * Copyright (C) 2009-2010 Texas Instruments Incorporated.
 *	Nishanth Menon
 *	Romit Dasgupta
 *	Kevin Hilman
 */

#अगर_अघोषित __DRIVER_OPP_H__
#घोषणा __DRIVER_OPP_H__

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/pm_opp.h>
#समावेश <linux/notअगरier.h>

काष्ठा clk;
काष्ठा regulator;

/* Lock to allow exclusive modअगरication to the device and opp lists */
बाह्य काष्ठा mutex opp_table_lock;

बाह्य काष्ठा list_head opp_tables, lazy_opp_tables;

/*
 * Internal data काष्ठाure organization with the OPP layer library is as
 * follows:
 * opp_tables (root)
 *	|- device 1 (represents voltage करोमुख्य 1)
 *	|	|- opp 1 (availability, freq, voltage)
 *	|	|- opp 2 ..
 *	...	...
 *	|	`- opp n ..
 *	|- device 2 (represents the next voltage करोमुख्य)
 *	...
 *	`- device m (represents mth voltage करोमुख्य)
 * device 1, 2.. are represented by opp_table काष्ठाure जबतक each opp
 * is represented by the opp काष्ठाure.
 */

/**
 * काष्ठा dev_pm_opp - Generic OPP description काष्ठाure
 * @node:	opp table node. The nodes are मुख्यtained throughout the lअगरeसमय
 *		of boot. It is expected only an optimal set of OPPs are
 *		added to the library by the SoC framework.
 *		IMPORTANT: the opp nodes should be मुख्यtained in increasing
 *		order.
 * @kref:	क्रम reference count of the OPP.
 * @available:	true/false - marks अगर this OPP as available or not
 * @dynamic:	not-created from अटल DT entries.
 * @turbo:	true अगर turbo (boost) OPP
 * @suspend:	true अगर suspend OPP
 * @हटाओd:	flag indicating that OPP's reference is dropped by OPP core.
 * @pstate: Device's power domain's perक्रमmance state.
 * @rate:	Frequency in hertz
 * @level:	Perक्रमmance level
 * @supplies:	Power supplies voltage/current values
 * @bandwidth:	Interconnect bandwidth values
 * @घड़ी_latency_ns: Latency (in nanoseconds) of चयनing to this OPP's
 *		frequency from any other OPP's frequency.
 * @required_opps: List of OPPs that are required by this OPP.
 * @opp_table:	poपूर्णांकs back to the opp_table काष्ठा this opp beदीर्घs to
 * @np:		OPP's device node.
 * @dentry:	debugfs dentry poपूर्णांकer (per opp)
 *
 * This काष्ठाure stores the OPP inक्रमmation क्रम a given device.
 */
काष्ठा dev_pm_opp अणु
	काष्ठा list_head node;
	काष्ठा kref kref;

	bool available;
	bool dynamic;
	bool turbo;
	bool suspend;
	bool हटाओd;
	अचिन्हित पूर्णांक pstate;
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक level;

	काष्ठा dev_pm_opp_supply *supplies;
	काष्ठा dev_pm_opp_icc_bw *bandwidth;

	अचिन्हित दीर्घ घड़ी_latency_ns;

	काष्ठा dev_pm_opp **required_opps;
	काष्ठा opp_table *opp_table;

	काष्ठा device_node *np;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dentry;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा opp_device - devices managed by 'struct opp_table'
 * @node:	list node
 * @dev:	device to which the काष्ठा object beदीर्घs
 * @dentry:	debugfs dentry poपूर्णांकer (per device)
 *
 * This is an पूर्णांकernal data काष्ठाure मुख्यtaining the devices that are managed
 * by 'struct opp_table'.
 */
काष्ठा opp_device अणु
	काष्ठा list_head node;
	स्थिर काष्ठा device *dev;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dentry;
#पूर्ण_अगर
पूर्ण;

क्रमागत opp_table_access अणु
	OPP_TABLE_ACCESS_UNKNOWN = 0,
	OPP_TABLE_ACCESS_EXCLUSIVE = 1,
	OPP_TABLE_ACCESS_SHARED = 2,
पूर्ण;

/**
 * काष्ठा opp_table - Device opp काष्ठाure
 * @node:	table node - contains the devices with OPPs that
 *		have been रेजिस्टरed. Nodes once added are not modअगरied in this
 *		table.
 * @head:	notअगरier head to notअगरy the OPP availability changes.
 * @dev_list:	list of devices that share these OPPs
 * @opp_list:	table of opps
 * @kref:	क्रम reference count of the table.
 * @lock:	mutex protecting the opp_list and dev_list.
 * @np:		काष्ठा device_node poपूर्णांकer क्रम opp's DT node.
 * @घड़ी_latency_ns_max: Max घड़ी latency in nanoseconds.
 * @parsed_अटल_opps: Count of devices क्रम which OPPs are initialized from DT.
 * @shared_opp: OPP is shared between multiple devices.
 * @current_rate: Currently configured frequency.
 * @current_opp: Currently configured OPP क्रम the table.
 * @suspend_opp: Poपूर्णांकer to OPP to be used during device suspend.
 * @genpd_virt_dev_lock: Mutex protecting the genpd भव device poपूर्णांकers.
 * @genpd_virt_devs: List of भव devices क्रम multiple genpd support.
 * @required_opp_tables: List of device OPP tables that are required by OPPs in
 *		this table.
 * @required_opp_count: Number of required devices.
 * @supported_hw: Array of version number to support.
 * @supported_hw_count: Number of elements in supported_hw array.
 * @prop_name: A name to postfix to many DT properties, जबतक parsing them.
 * @clk: Device's घड़ी handle
 * @regulators: Supply regulators
 * @regulator_count: Number of घातer supply regulators. Its value can be -1
 * (uninitialized), 0 (no opp-microvolt property) or > 0 (has opp-microvolt
 * property).
 * @paths: Interconnect path handles
 * @path_count: Number of पूर्णांकerconnect paths
 * @enabled: Set to true अगर the device's resources are enabled/configured.
 * @genpd_perक्रमmance_state: Device's घातer करोमुख्य support perक्रमmance state.
 * @is_genpd: Marks अगर the OPP table beदीर्घs to a genpd.
 * @set_opp: Platक्रमm specअगरic set_opp callback
 * @sod_supplies: Set opp data supplies
 * @set_opp_data: Data to be passed to set_opp callback
 * @dentry:	debugfs dentry poपूर्णांकer of the real device directory (not links).
 * @dentry_name: Name of the real dentry.
 *
 * @voltage_tolerance_v1: In percentage, क्रम v1 bindings only.
 *
 * This is an पूर्णांकernal data काष्ठाure मुख्यtaining the link to opps attached to
 * a device. This काष्ठाure is not meant to be shared to users as it is
 * meant क्रम book keeping and निजी to OPP library.
 */
काष्ठा opp_table अणु
	काष्ठा list_head node, lazy;

	काष्ठा blocking_notअगरier_head head;
	काष्ठा list_head dev_list;
	काष्ठा list_head opp_list;
	काष्ठा kref kref;
	काष्ठा mutex lock;

	काष्ठा device_node *np;
	अचिन्हित दीर्घ घड़ी_latency_ns_max;

	/* For backward compatibility with v1 bindings */
	अचिन्हित पूर्णांक voltage_tolerance_v1;

	अचिन्हित पूर्णांक parsed_अटल_opps;
	क्रमागत opp_table_access shared_opp;
	अचिन्हित दीर्घ current_rate;
	काष्ठा dev_pm_opp *current_opp;
	काष्ठा dev_pm_opp *suspend_opp;

	काष्ठा mutex genpd_virt_dev_lock;
	काष्ठा device **genpd_virt_devs;
	काष्ठा opp_table **required_opp_tables;
	अचिन्हित पूर्णांक required_opp_count;

	अचिन्हित पूर्णांक *supported_hw;
	अचिन्हित पूर्णांक supported_hw_count;
	स्थिर अक्षर *prop_name;
	काष्ठा clk *clk;
	काष्ठा regulator **regulators;
	पूर्णांक regulator_count;
	काष्ठा icc_path **paths;
	अचिन्हित पूर्णांक path_count;
	bool enabled;
	bool genpd_perक्रमmance_state;
	bool is_genpd;

	पूर्णांक (*set_opp)(काष्ठा dev_pm_set_opp_data *data);
	काष्ठा dev_pm_opp_supply *sod_supplies;
	काष्ठा dev_pm_set_opp_data *set_opp_data;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dentry;
	अक्षर dentry_name[NAME_MAX];
#पूर्ण_अगर
पूर्ण;

/* Routines पूर्णांकernal to opp core */
व्योम dev_pm_opp_get(काष्ठा dev_pm_opp *opp);
bool _opp_हटाओ_all_अटल(काष्ठा opp_table *opp_table);
व्योम _get_opp_table_kref(काष्ठा opp_table *opp_table);
पूर्णांक _get_opp_count(काष्ठा opp_table *opp_table);
काष्ठा opp_table *_find_opp_table(काष्ठा device *dev);
काष्ठा opp_device *_add_opp_dev(स्थिर काष्ठा device *dev, काष्ठा opp_table *opp_table);
काष्ठा dev_pm_opp *_opp_allocate(काष्ठा opp_table *opp_table);
व्योम _opp_मुक्त(काष्ठा dev_pm_opp *opp);
पूर्णांक _opp_compare_key(काष्ठा dev_pm_opp *opp1, काष्ठा dev_pm_opp *opp2);
पूर्णांक _opp_add(काष्ठा device *dev, काष्ठा dev_pm_opp *new_opp, काष्ठा opp_table *opp_table, bool rate_not_available);
पूर्णांक _opp_add_v1(काष्ठा opp_table *opp_table, काष्ठा device *dev, अचिन्हित दीर्घ freq, दीर्घ u_volt, bool dynamic);
व्योम _dev_pm_opp_cpumask_हटाओ_table(स्थिर काष्ठा cpumask *cpumask, पूर्णांक last_cpu);
काष्ठा opp_table *_add_opp_table_indexed(काष्ठा device *dev, पूर्णांक index, bool अ_लोlk);
व्योम _put_opp_list_kref(काष्ठा opp_table *opp_table);
व्योम _required_opps_available(काष्ठा dev_pm_opp *opp, पूर्णांक count);

अटल अंतरभूत bool lazy_linking_pending(काष्ठा opp_table *opp_table)
अणु
	वापस unlikely(!list_empty(&opp_table->lazy));
पूर्ण

#अगर_घोषित CONFIG_OF
व्योम _of_init_opp_table(काष्ठा opp_table *opp_table, काष्ठा device *dev, पूर्णांक index);
व्योम _of_clear_opp_table(काष्ठा opp_table *opp_table);
काष्ठा opp_table *_managed_opp(काष्ठा device *dev, पूर्णांक index);
व्योम _of_opp_मुक्त_required_opps(काष्ठा opp_table *opp_table,
				काष्ठा dev_pm_opp *opp);
#अन्यथा
अटल अंतरभूत व्योम _of_init_opp_table(काष्ठा opp_table *opp_table, काष्ठा device *dev, पूर्णांक index) अणुपूर्ण
अटल अंतरभूत व्योम _of_clear_opp_table(काष्ठा opp_table *opp_table) अणुपूर्ण
अटल अंतरभूत काष्ठा opp_table *_managed_opp(काष्ठा device *dev, पूर्णांक index) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम _of_opp_मुक्त_required_opps(काष्ठा opp_table *opp_table,
					      काष्ठा dev_pm_opp *opp) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS
व्योम opp_debug_हटाओ_one(काष्ठा dev_pm_opp *opp);
व्योम opp_debug_create_one(काष्ठा dev_pm_opp *opp, काष्ठा opp_table *opp_table);
व्योम opp_debug_रेजिस्टर(काष्ठा opp_device *opp_dev, काष्ठा opp_table *opp_table);
व्योम opp_debug_unरेजिस्टर(काष्ठा opp_device *opp_dev, काष्ठा opp_table *opp_table);
#अन्यथा
अटल अंतरभूत व्योम opp_debug_हटाओ_one(काष्ठा dev_pm_opp *opp) अणुपूर्ण

अटल अंतरभूत व्योम opp_debug_create_one(काष्ठा dev_pm_opp *opp,
					काष्ठा opp_table *opp_table) अणु पूर्ण

अटल अंतरभूत व्योम opp_debug_रेजिस्टर(काष्ठा opp_device *opp_dev,
				      काष्ठा opp_table *opp_table) अणु पूर्ण

अटल अंतरभूत व्योम opp_debug_unरेजिस्टर(काष्ठा opp_device *opp_dev,
					काष्ठा opp_table *opp_table)
अणु पूर्ण
#पूर्ण_अगर		/* DEBUG_FS */

#पूर्ण_अगर		/* __DRIVER_OPP_H__ */
