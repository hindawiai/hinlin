<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/net/devlink.h - Network physical device Netlink पूर्णांकerface
 * Copyright (c) 2016 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016 Jiri Pirko <jiri@mellanox.com>
 */
#अगर_अघोषित _NET_DEVLINK_H_
#घोषणा _NET_DEVLINK_H_

#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gfp.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/refcount.h>
#समावेश <net/net_namespace.h>
#समावेश <net/flow_offload.h>
#समावेश <uapi/linux/devlink.h>
#समावेश <linux/xarray.h>
#समावेश <linux/firmware.h>

#घोषणा DEVLINK_RELOAD_STATS_ARRAY_SIZE \
	(__DEVLINK_RELOAD_LIMIT_MAX * __DEVLINK_RELOAD_ACTION_MAX)

काष्ठा devlink_dev_stats अणु
	u32 reload_stats[DEVLINK_RELOAD_STATS_ARRAY_SIZE];
	u32 remote_reload_stats[DEVLINK_RELOAD_STATS_ARRAY_SIZE];
पूर्ण;

काष्ठा devlink_ops;

काष्ठा devlink अणु
	काष्ठा list_head list;
	काष्ठा list_head port_list;
	काष्ठा list_head sb_list;
	काष्ठा list_head dpipe_table_list;
	काष्ठा list_head resource_list;
	काष्ठा list_head param_list;
	काष्ठा list_head region_list;
	काष्ठा list_head reporter_list;
	काष्ठा mutex reporters_lock; /* protects reporter_list */
	काष्ठा devlink_dpipe_headers *dpipe_headers;
	काष्ठा list_head trap_list;
	काष्ठा list_head trap_group_list;
	काष्ठा list_head trap_policer_list;
	स्थिर काष्ठा devlink_ops *ops;
	काष्ठा xarray snapshot_ids;
	काष्ठा devlink_dev_stats stats;
	काष्ठा device *dev;
	possible_net_t _net;
	काष्ठा mutex lock; /* Serializes access to devlink instance specअगरic objects such as
			    * port, sb, dpipe, resource, params, region, traps and more.
			    */
	u8 reload_failed:1,
	   reload_enabled:1,
	   रेजिस्टरed:1;
	अक्षर priv[0] __aligned(NETDEV_ALIGN);
पूर्ण;

काष्ठा devlink_port_phys_attrs अणु
	u32 port_number; /* Same value as "split group".
			  * A physical port which is visible to the user
			  * क्रम a given port flavour.
			  */
	u32 split_subport_number; /* If the port is split, this is the number of subport. */
पूर्ण;

/**
 * काष्ठा devlink_port_pci_pf_attrs - devlink port's PCI PF attributes
 * @controller: Associated controller number
 * @pf: Associated PCI PF number क्रम this port.
 * @बाह्यal: when set, indicates अगर a port is क्रम an बाह्यal controller
 */
काष्ठा devlink_port_pci_pf_attrs अणु
	u32 controller;
	u16 pf;
	u8 बाह्यal:1;
पूर्ण;

/**
 * काष्ठा devlink_port_pci_vf_attrs - devlink port's PCI VF attributes
 * @controller: Associated controller number
 * @pf: Associated PCI PF number क्रम this port.
 * @vf: Associated PCI VF क्रम of the PCI PF क्रम this port.
 * @बाह्यal: when set, indicates अगर a port is क्रम an बाह्यal controller
 */
काष्ठा devlink_port_pci_vf_attrs अणु
	u32 controller;
	u16 pf;
	u16 vf;
	u8 बाह्यal:1;
पूर्ण;

/**
 * काष्ठा devlink_port_pci_sf_attrs - devlink port's PCI SF attributes
 * @controller: Associated controller number
 * @sf: Associated PCI SF क्रम of the PCI PF क्रम this port.
 * @pf: Associated PCI PF number क्रम this port.
 * @बाह्यal: when set, indicates अगर a port is क्रम an बाह्यal controller
 */
काष्ठा devlink_port_pci_sf_attrs अणु
	u32 controller;
	u32 sf;
	u16 pf;
	u8 बाह्यal:1;
पूर्ण;

/**
 * काष्ठा devlink_port_attrs - devlink port object
 * @flavour: flavour of the port
 * @split: indicates अगर this is split port
 * @splittable: indicates अगर the port can be split.
 * @lanes: maximum number of lanes the port supports. 0 value is not passed to netlink.
 * @चयन_id: अगर the port is part of चयन, this is buffer with ID, otherwise this is शून्य
 * @phys: physical port attributes
 * @pci_pf: PCI PF port attributes
 * @pci_vf: PCI VF port attributes
 * @pci_sf: PCI SF port attributes
 */
काष्ठा devlink_port_attrs अणु
	u8 split:1,
	   splittable:1;
	u32 lanes;
	क्रमागत devlink_port_flavour flavour;
	काष्ठा netdev_phys_item_id चयन_id;
	जोड़ अणु
		काष्ठा devlink_port_phys_attrs phys;
		काष्ठा devlink_port_pci_pf_attrs pci_pf;
		काष्ठा devlink_port_pci_vf_attrs pci_vf;
		काष्ठा devlink_port_pci_sf_attrs pci_sf;
	पूर्ण;
पूर्ण;

काष्ठा devlink_port अणु
	काष्ठा list_head list;
	काष्ठा list_head param_list;
	काष्ठा list_head region_list;
	काष्ठा devlink *devlink;
	अचिन्हित पूर्णांक index;
	bool रेजिस्टरed;
	spinlock_t type_lock; /* Protects type and type_dev
			       * poपूर्णांकer consistency.
			       */
	क्रमागत devlink_port_type type;
	क्रमागत devlink_port_type desired_type;
	व्योम *type_dev;
	काष्ठा devlink_port_attrs attrs;
	u8 attrs_set:1,
	   चयन_port:1;
	काष्ठा delayed_work type_warn_dw;
	काष्ठा list_head reporter_list;
	काष्ठा mutex reporters_lock; /* Protects reporter_list */
पूर्ण;

काष्ठा devlink_port_new_attrs अणु
	क्रमागत devlink_port_flavour flavour;
	अचिन्हित पूर्णांक port_index;
	u32 controller;
	u32 sfnum;
	u16 pfnum;
	u8 port_index_valid:1,
	   controller_valid:1,
	   sfnum_valid:1;
पूर्ण;

काष्ठा devlink_sb_pool_info अणु
	क्रमागत devlink_sb_pool_type pool_type;
	u32 size;
	क्रमागत devlink_sb_threshold_type threshold_type;
	u32 cell_size;
पूर्ण;

/**
 * काष्ठा devlink_dpipe_field - dpipe field object
 * @name: field name
 * @id: index inside the headers field array
 * @bitwidth: bitwidth
 * @mapping_type: mapping type
 */
काष्ठा devlink_dpipe_field अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक bitwidth;
	क्रमागत devlink_dpipe_field_mapping_type mapping_type;
पूर्ण;

/**
 * काष्ठा devlink_dpipe_header - dpipe header object
 * @name: header name
 * @id: index, global/local detrmined by global bit
 * @fields: fields
 * @fields_count: number of fields
 * @global: indicates अगर header is shared like most protocol header
 *	    or driver specअगरic
 */
काष्ठा devlink_dpipe_header अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
	काष्ठा devlink_dpipe_field *fields;
	अचिन्हित पूर्णांक fields_count;
	bool global;
पूर्ण;

/**
 * काष्ठा devlink_dpipe_match - represents match operation
 * @type: type of match
 * @header_index: header index (packets can have several headers of same
 *		  type like in हाल of tunnels)
 * @header: header
 * @fieled_id: field index
 */
काष्ठा devlink_dpipe_match अणु
	क्रमागत devlink_dpipe_match_type type;
	अचिन्हित पूर्णांक header_index;
	काष्ठा devlink_dpipe_header *header;
	अचिन्हित पूर्णांक field_id;
पूर्ण;

/**
 * काष्ठा devlink_dpipe_action - represents action operation
 * @type: type of action
 * @header_index: header index (packets can have several headers of same
 *		  type like in हाल of tunnels)
 * @header: header
 * @fieled_id: field index
 */
काष्ठा devlink_dpipe_action अणु
	क्रमागत devlink_dpipe_action_type type;
	अचिन्हित पूर्णांक header_index;
	काष्ठा devlink_dpipe_header *header;
	अचिन्हित पूर्णांक field_id;
पूर्ण;

/**
 * काष्ठा devlink_dpipe_value - represents value of match/action
 * @action: action
 * @match: match
 * @mapping_value: in हाल the field has some mapping this value
 *                 specअगरied the mapping value
 * @mapping_valid: specअगरy अगर mapping value is valid
 * @value_size: value size
 * @value: value
 * @mask: bit mask
 */
काष्ठा devlink_dpipe_value अणु
	जोड़ अणु
		काष्ठा devlink_dpipe_action *action;
		काष्ठा devlink_dpipe_match *match;
	पूर्ण;
	अचिन्हित पूर्णांक mapping_value;
	bool mapping_valid;
	अचिन्हित पूर्णांक value_size;
	व्योम *value;
	व्योम *mask;
पूर्ण;

/**
 * काष्ठा devlink_dpipe_entry - table entry object
 * @index: index of the entry in the table
 * @match_values: match values
 * @matche_values_count: count of matches tuples
 * @action_values: actions values
 * @action_values_count: count of actions values
 * @counter: value of counter
 * @counter_valid: Specअगरy अगर value is valid from hardware
 */
काष्ठा devlink_dpipe_entry अणु
	u64 index;
	काष्ठा devlink_dpipe_value *match_values;
	अचिन्हित पूर्णांक match_values_count;
	काष्ठा devlink_dpipe_value *action_values;
	अचिन्हित पूर्णांक action_values_count;
	u64 counter;
	bool counter_valid;
पूर्ण;

/**
 * काष्ठा devlink_dpipe_dump_ctx - context provided to driver in order
 *				   to dump
 * @info: info
 * @cmd: devlink command
 * @skb: skb
 * @nest: top attribute
 * @hdr: hdr
 */
काष्ठा devlink_dpipe_dump_ctx अणु
	काष्ठा genl_info *info;
	क्रमागत devlink_command cmd;
	काष्ठा sk_buff *skb;
	काष्ठा nlattr *nest;
	व्योम *hdr;
पूर्ण;

काष्ठा devlink_dpipe_table_ops;

/**
 * काष्ठा devlink_dpipe_table - table object
 * @priv: निजी
 * @name: table name
 * @counters_enabled: indicates अगर counters are active
 * @counter_control_बाह्य: indicates अगर counter control is in dpipe or
 *			    बाह्यal tool
 * @resource_valid: Indicate that the resource id is valid
 * @resource_id: relative resource this table is related to
 * @resource_units: number of resource's unit consumed per table's entry
 * @table_ops: table operations
 * @rcu: rcu
 */
काष्ठा devlink_dpipe_table अणु
	व्योम *priv;
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	bool counters_enabled;
	bool counter_control_बाह्य;
	bool resource_valid;
	u64 resource_id;
	u64 resource_units;
	काष्ठा devlink_dpipe_table_ops *table_ops;
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा devlink_dpipe_table_ops - dpipe_table ops
 * @actions_dump - dumps all tables actions
 * @matches_dump - dumps all tables matches
 * @entries_dump - dumps all active entries in the table
 * @counters_set_update - when changing the counter status hardware sync
 *			  maybe needed to allocate/मुक्त counter related
 *			  resources
 * @size_get - get size
 */
काष्ठा devlink_dpipe_table_ops अणु
	पूर्णांक (*actions_dump)(व्योम *priv, काष्ठा sk_buff *skb);
	पूर्णांक (*matches_dump)(व्योम *priv, काष्ठा sk_buff *skb);
	पूर्णांक (*entries_dump)(व्योम *priv, bool counters_enabled,
			    काष्ठा devlink_dpipe_dump_ctx *dump_ctx);
	पूर्णांक (*counters_set_update)(व्योम *priv, bool enable);
	u64 (*size_get)(व्योम *priv);
पूर्ण;

/**
 * काष्ठा devlink_dpipe_headers - dpipe headers
 * @headers - header array can be shared (global bit) or driver specअगरic
 * @headers_count - count of headers
 */
काष्ठा devlink_dpipe_headers अणु
	काष्ठा devlink_dpipe_header **headers;
	अचिन्हित पूर्णांक headers_count;
पूर्ण;

/**
 * काष्ठा devlink_resource_size_params - resource's size parameters
 * @size_min: minimum size which can be set
 * @size_max: maximum size which can be set
 * @size_granularity: size granularity
 * @size_unit: resource's basic unit
 */
काष्ठा devlink_resource_size_params अणु
	u64 size_min;
	u64 size_max;
	u64 size_granularity;
	क्रमागत devlink_resource_unit unit;
पूर्ण;

अटल अंतरभूत व्योम
devlink_resource_size_params_init(काष्ठा devlink_resource_size_params *size_params,
				  u64 size_min, u64 size_max,
				  u64 size_granularity,
				  क्रमागत devlink_resource_unit unit)
अणु
	size_params->size_min = size_min;
	size_params->size_max = size_max;
	size_params->size_granularity = size_granularity;
	size_params->unit = unit;
पूर्ण

प्रकार u64 devlink_resource_occ_get_t(व्योम *priv);

/**
 * काष्ठा devlink_resource - devlink resource
 * @name: name of the resource
 * @id: id, per devlink instance
 * @size: size of the resource
 * @size_new: updated size of the resource, reload is needed
 * @size_valid: valid in हाल the total size of the resource is valid
 *              including its children
 * @parent: parent resource
 * @size_params: size parameters
 * @list: parent list
 * @resource_list: list of child resources
 */
काष्ठा devlink_resource अणु
	स्थिर अक्षर *name;
	u64 id;
	u64 size;
	u64 size_new;
	bool size_valid;
	काष्ठा devlink_resource *parent;
	काष्ठा devlink_resource_size_params size_params;
	काष्ठा list_head list;
	काष्ठा list_head resource_list;
	devlink_resource_occ_get_t *occ_get;
	व्योम *occ_get_priv;
पूर्ण;

#घोषणा DEVLINK_RESOURCE_ID_PARENT_TOP 0

#घोषणा DEVLINK_RESOURCE_GENERIC_NAME_PORTS "physical_ports"

#घोषणा __DEVLINK_PARAM_MAX_STRING_VALUE 32
क्रमागत devlink_param_type अणु
	DEVLINK_PARAM_TYPE_U8,
	DEVLINK_PARAM_TYPE_U16,
	DEVLINK_PARAM_TYPE_U32,
	DEVLINK_PARAM_TYPE_STRING,
	DEVLINK_PARAM_TYPE_BOOL,
पूर्ण;

जोड़ devlink_param_value अणु
	u8 vu8;
	u16 vu16;
	u32 vu32;
	अक्षर vstr[__DEVLINK_PARAM_MAX_STRING_VALUE];
	bool vbool;
पूर्ण;

काष्ठा devlink_param_gset_ctx अणु
	जोड़ devlink_param_value val;
	क्रमागत devlink_param_cmode cmode;
पूर्ण;

/**
 * काष्ठा devlink_flash_notअगरy - devlink dev flash notअगरy data
 * @status_msg: current status string
 * @component: firmware component being updated
 * @करोne: amount of work completed of total amount
 * @total: amount of work expected to be करोne
 * @समयout: expected max समयout in seconds
 *
 * These are values to be given to userland to be displayed in order
 * to show current activity in a firmware update process.
 */
काष्ठा devlink_flash_notअगरy अणु
	स्थिर अक्षर *status_msg;
	स्थिर अक्षर *component;
	अचिन्हित दीर्घ करोne;
	अचिन्हित दीर्घ total;
	अचिन्हित दीर्घ समयout;
पूर्ण;

/**
 * काष्ठा devlink_param - devlink configuration parameter data
 * @name: name of the parameter
 * @generic: indicates अगर the parameter is generic or driver specअगरic
 * @type: parameter type
 * @supported_cmodes: biपंचांगap of supported configuration modes
 * @get: get parameter value, used क्रम runसमय and permanent
 *       configuration modes
 * @set: set parameter value, used क्रम runसमय and permanent
 *       configuration modes
 * @validate: validate input value is applicable (within value range, etc.)
 *
 * This काष्ठा should be used by the driver to fill the data क्रम
 * a parameter it रेजिस्टरs.
 */
काष्ठा devlink_param अणु
	u32 id;
	स्थिर अक्षर *name;
	bool generic;
	क्रमागत devlink_param_type type;
	अचिन्हित दीर्घ supported_cmodes;
	पूर्णांक (*get)(काष्ठा devlink *devlink, u32 id,
		   काष्ठा devlink_param_gset_ctx *ctx);
	पूर्णांक (*set)(काष्ठा devlink *devlink, u32 id,
		   काष्ठा devlink_param_gset_ctx *ctx);
	पूर्णांक (*validate)(काष्ठा devlink *devlink, u32 id,
			जोड़ devlink_param_value val,
			काष्ठा netlink_ext_ack *extack);
पूर्ण;

काष्ठा devlink_param_item अणु
	काष्ठा list_head list;
	स्थिर काष्ठा devlink_param *param;
	जोड़ devlink_param_value driverinit_value;
	bool driverinit_value_valid;
	bool published;
पूर्ण;

क्रमागत devlink_param_generic_id अणु
	DEVLINK_PARAM_GENERIC_ID_INT_ERR_RESET,
	DEVLINK_PARAM_GENERIC_ID_MAX_MACS,
	DEVLINK_PARAM_GENERIC_ID_ENABLE_SRIOV,
	DEVLINK_PARAM_GENERIC_ID_REGION_SNAPSHOT,
	DEVLINK_PARAM_GENERIC_ID_IGNORE_ARI,
	DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MAX,
	DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MIN,
	DEVLINK_PARAM_GENERIC_ID_FW_LOAD_POLICY,
	DEVLINK_PARAM_GENERIC_ID_RESET_DEV_ON_DRV_PROBE,
	DEVLINK_PARAM_GENERIC_ID_ENABLE_ROCE,
	DEVLINK_PARAM_GENERIC_ID_ENABLE_REMOTE_DEV_RESET,

	/* add new param generic ids above here*/
	__DEVLINK_PARAM_GENERIC_ID_MAX,
	DEVLINK_PARAM_GENERIC_ID_MAX = __DEVLINK_PARAM_GENERIC_ID_MAX - 1,
पूर्ण;

#घोषणा DEVLINK_PARAM_GENERIC_INT_ERR_RESET_NAME "internal_error_reset"
#घोषणा DEVLINK_PARAM_GENERIC_INT_ERR_RESET_TYPE DEVLINK_PARAM_TYPE_BOOL

#घोषणा DEVLINK_PARAM_GENERIC_MAX_MACS_NAME "max_macs"
#घोषणा DEVLINK_PARAM_GENERIC_MAX_MACS_TYPE DEVLINK_PARAM_TYPE_U32

#घोषणा DEVLINK_PARAM_GENERIC_ENABLE_SRIOV_NAME "enable_sriov"
#घोषणा DEVLINK_PARAM_GENERIC_ENABLE_SRIOV_TYPE DEVLINK_PARAM_TYPE_BOOL

#घोषणा DEVLINK_PARAM_GENERIC_REGION_SNAPSHOT_NAME "region_snapshot_enable"
#घोषणा DEVLINK_PARAM_GENERIC_REGION_SNAPSHOT_TYPE DEVLINK_PARAM_TYPE_BOOL

#घोषणा DEVLINK_PARAM_GENERIC_IGNORE_ARI_NAME "ignore_ari"
#घोषणा DEVLINK_PARAM_GENERIC_IGNORE_ARI_TYPE DEVLINK_PARAM_TYPE_BOOL

#घोषणा DEVLINK_PARAM_GENERIC_MSIX_VEC_PER_PF_MAX_NAME "msix_vec_per_pf_max"
#घोषणा DEVLINK_PARAM_GENERIC_MSIX_VEC_PER_PF_MAX_TYPE DEVLINK_PARAM_TYPE_U32

#घोषणा DEVLINK_PARAM_GENERIC_MSIX_VEC_PER_PF_MIN_NAME "msix_vec_per_pf_min"
#घोषणा DEVLINK_PARAM_GENERIC_MSIX_VEC_PER_PF_MIN_TYPE DEVLINK_PARAM_TYPE_U32

#घोषणा DEVLINK_PARAM_GENERIC_FW_LOAD_POLICY_NAME "fw_load_policy"
#घोषणा DEVLINK_PARAM_GENERIC_FW_LOAD_POLICY_TYPE DEVLINK_PARAM_TYPE_U8

#घोषणा DEVLINK_PARAM_GENERIC_RESET_DEV_ON_DRV_PROBE_NAME \
	"reset_dev_on_drv_probe"
#घोषणा DEVLINK_PARAM_GENERIC_RESET_DEV_ON_DRV_PROBE_TYPE DEVLINK_PARAM_TYPE_U8

#घोषणा DEVLINK_PARAM_GENERIC_ENABLE_ROCE_NAME "enable_roce"
#घोषणा DEVLINK_PARAM_GENERIC_ENABLE_ROCE_TYPE DEVLINK_PARAM_TYPE_BOOL

#घोषणा DEVLINK_PARAM_GENERIC_ENABLE_REMOTE_DEV_RESET_NAME "enable_remote_dev_reset"
#घोषणा DEVLINK_PARAM_GENERIC_ENABLE_REMOTE_DEV_RESET_TYPE DEVLINK_PARAM_TYPE_BOOL

#घोषणा DEVLINK_PARAM_GENERIC(_id, _cmodes, _get, _set, _validate)	\
अणु									\
	.id = DEVLINK_PARAM_GENERIC_ID_##_id,				\
	.name = DEVLINK_PARAM_GENERIC_##_id##_NAME,			\
	.type = DEVLINK_PARAM_GENERIC_##_id##_TYPE,			\
	.generic = true,						\
	.supported_cmodes = _cmodes,					\
	.get = _get,							\
	.set = _set,							\
	.validate = _validate,						\
पूर्ण

#घोषणा DEVLINK_PARAM_DRIVER(_id, _name, _type, _cmodes, _get, _set, _validate)	\
अणु									\
	.id = _id,							\
	.name = _name,							\
	.type = _type,							\
	.supported_cmodes = _cmodes,					\
	.get = _get,							\
	.set = _set,							\
	.validate = _validate,						\
पूर्ण

/* Part number, identअगरier of board design */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_BOARD_ID	"board.id"
/* Revision of board design */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_BOARD_REV	"board.rev"
/* Maker of the board */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_BOARD_MANUFACTURE	"board.manufacture"

/* Part number, identअगरier of asic design */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_ASIC_ID	"asic.id"
/* Revision of asic design */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_ASIC_REV	"asic.rev"

/* Overall FW version */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_FW		"fw"
/* Control processor FW version */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_FW_MGMT	"fw.mgmt"
/* FW पूर्णांकerface specअगरication version */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_FW_MGMT_API	"fw.mgmt.api"
/* Data path microcode controlling high-speed packet processing */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_FW_APP	"fw.app"
/* UNDI software version */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_FW_UNDI	"fw.undi"
/* NCSI support/handler version */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_FW_NCSI	"fw.ncsi"
/* FW parameter set id */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_FW_PSID	"fw.psid"
/* RoCE FW version */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_FW_ROCE	"fw.roce"
/* Firmware bundle identअगरier */
#घोषणा DEVLINK_INFO_VERSION_GENERIC_FW_BUNDLE_ID	"fw.bundle_id"

/**
 * काष्ठा devlink_flash_update_params - Flash Update parameters
 * @fw: poपूर्णांकer to the firmware data to update from
 * @component: the flash component to update
 *
 * With the exception of fw, drivers must opt-in to parameters by
 * setting the appropriate bit in the supported_flash_update_params field in
 * their devlink_ops काष्ठाure.
 */
काष्ठा devlink_flash_update_params अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *component;
	u32 overग_लिखो_mask;
पूर्ण;

#घोषणा DEVLINK_SUPPORT_FLASH_UPDATE_COMPONENT		BIT(0)
#घोषणा DEVLINK_SUPPORT_FLASH_UPDATE_OVERWRITE_MASK	BIT(1)

काष्ठा devlink_region;
काष्ठा devlink_info_req;

/**
 * काष्ठा devlink_region_ops - Region operations
 * @name: region name
 * @deकाष्ठाor: callback used to मुक्त snapshot memory when deleting
 * @snapshot: callback to request an immediate snapshot. On success,
 *            the data variable must be updated to poपूर्णांक to the snapshot data.
 *            The function will be called जबतक the devlink instance lock is
 *            held.
 * @priv: Poपूर्णांकer to driver निजी data क्रम the region operation
 */
काष्ठा devlink_region_ops अणु
	स्थिर अक्षर *name;
	व्योम (*deकाष्ठाor)(स्थिर व्योम *data);
	पूर्णांक (*snapshot)(काष्ठा devlink *devlink,
			स्थिर काष्ठा devlink_region_ops *ops,
			काष्ठा netlink_ext_ack *extack,
			u8 **data);
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा devlink_port_region_ops - Region operations क्रम a port
 * @name: region name
 * @deकाष्ठाor: callback used to मुक्त snapshot memory when deleting
 * @snapshot: callback to request an immediate snapshot. On success,
 *            the data variable must be updated to poपूर्णांक to the snapshot data.
 *            The function will be called जबतक the devlink instance lock is
 *            held.
 * @priv: Poपूर्णांकer to driver निजी data क्रम the region operation
 */
काष्ठा devlink_port_region_ops अणु
	स्थिर अक्षर *name;
	व्योम (*deकाष्ठाor)(स्थिर व्योम *data);
	पूर्णांक (*snapshot)(काष्ठा devlink_port *port,
			स्थिर काष्ठा devlink_port_region_ops *ops,
			काष्ठा netlink_ext_ack *extack,
			u8 **data);
	व्योम *priv;
पूर्ण;

काष्ठा devlink_fmsg;
काष्ठा devlink_health_reporter;

क्रमागत devlink_health_reporter_state अणु
	DEVLINK_HEALTH_REPORTER_STATE_HEALTHY,
	DEVLINK_HEALTH_REPORTER_STATE_ERROR,
पूर्ण;

/**
 * काष्ठा devlink_health_reporter_ops - Reporter operations
 * @name: reporter name
 * @recover: callback to recover from reported error
 *           अगर priv_ctx is शून्य, run a full recover
 * @dump: callback to dump an object
 *        अगर priv_ctx is शून्य, run a full dump
 * @diagnose: callback to diagnose the current status
 * @test: callback to trigger a test event
 */

काष्ठा devlink_health_reporter_ops अणु
	अक्षर *name;
	पूर्णांक (*recover)(काष्ठा devlink_health_reporter *reporter,
		       व्योम *priv_ctx, काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*dump)(काष्ठा devlink_health_reporter *reporter,
		    काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
		    काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*diagnose)(काष्ठा devlink_health_reporter *reporter,
			काष्ठा devlink_fmsg *fmsg,
			काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*test)(काष्ठा devlink_health_reporter *reporter,
		    काष्ठा netlink_ext_ack *extack);
पूर्ण;

/**
 * काष्ठा devlink_trap_metadata - Packet trap metadata.
 * @trap_name: Trap name.
 * @trap_group_name: Trap group name.
 * @input_dev: Input netdevice.
 * @fa_cookie: Flow action user cookie.
 * @trap_type: Trap type.
 */
काष्ठा devlink_trap_metadata अणु
	स्थिर अक्षर *trap_name;
	स्थिर अक्षर *trap_group_name;
	काष्ठा net_device *input_dev;
	स्थिर काष्ठा flow_action_cookie *fa_cookie;
	क्रमागत devlink_trap_type trap_type;
पूर्ण;

/**
 * काष्ठा devlink_trap_policer - Immutable packet trap policer attributes.
 * @id: Policer identअगरier.
 * @init_rate: Initial rate in packets / sec.
 * @init_burst: Initial burst size in packets.
 * @max_rate: Maximum rate.
 * @min_rate: Minimum rate.
 * @max_burst: Maximum burst size.
 * @min_burst: Minimum burst size.
 *
 * Describes immutable attributes of packet trap policers that drivers रेजिस्टर
 * with devlink.
 */
काष्ठा devlink_trap_policer अणु
	u32 id;
	u64 init_rate;
	u64 init_burst;
	u64 max_rate;
	u64 min_rate;
	u64 max_burst;
	u64 min_burst;
पूर्ण;

/**
 * काष्ठा devlink_trap_group - Immutable packet trap group attributes.
 * @name: Trap group name.
 * @id: Trap group identअगरier.
 * @generic: Whether the trap group is generic or not.
 * @init_policer_id: Initial policer identअगरier.
 *
 * Describes immutable attributes of packet trap groups that drivers रेजिस्टर
 * with devlink.
 */
काष्ठा devlink_trap_group अणु
	स्थिर अक्षर *name;
	u16 id;
	bool generic;
	u32 init_policer_id;
पूर्ण;

#घोषणा DEVLINK_TRAP_METADATA_TYPE_F_IN_PORT	BIT(0)
#घोषणा DEVLINK_TRAP_METADATA_TYPE_F_FA_COOKIE	BIT(1)

/**
 * काष्ठा devlink_trap - Immutable packet trap attributes.
 * @type: Trap type.
 * @init_action: Initial trap action.
 * @generic: Whether the trap is generic or not.
 * @id: Trap identअगरier.
 * @name: Trap name.
 * @init_group_id: Initial group identअगरier.
 * @metadata_cap: Metadata types that can be provided by the trap.
 *
 * Describes immutable attributes of packet traps that drivers रेजिस्टर with
 * devlink.
 */
काष्ठा devlink_trap अणु
	क्रमागत devlink_trap_type type;
	क्रमागत devlink_trap_action init_action;
	bool generic;
	u16 id;
	स्थिर अक्षर *name;
	u16 init_group_id;
	u32 metadata_cap;
पूर्ण;

/* All traps must be करोcumented in
 * Documentation/networking/devlink/devlink-trap.rst
 */
क्रमागत devlink_trap_generic_id अणु
	DEVLINK_TRAP_GENERIC_ID_SMAC_MC,
	DEVLINK_TRAP_GENERIC_ID_VLAN_TAG_MISMATCH,
	DEVLINK_TRAP_GENERIC_ID_INGRESS_VLAN_FILTER,
	DEVLINK_TRAP_GENERIC_ID_INGRESS_STP_FILTER,
	DEVLINK_TRAP_GENERIC_ID_EMPTY_TX_LIST,
	DEVLINK_TRAP_GENERIC_ID_PORT_LOOPBACK_FILTER,
	DEVLINK_TRAP_GENERIC_ID_BLACKHOLE_ROUTE,
	DEVLINK_TRAP_GENERIC_ID_TTL_ERROR,
	DEVLINK_TRAP_GENERIC_ID_TAIL_DROP,
	DEVLINK_TRAP_GENERIC_ID_NON_IP_PACKET,
	DEVLINK_TRAP_GENERIC_ID_UC_DIP_MC_DMAC,
	DEVLINK_TRAP_GENERIC_ID_DIP_LB,
	DEVLINK_TRAP_GENERIC_ID_SIP_MC,
	DEVLINK_TRAP_GENERIC_ID_SIP_LB,
	DEVLINK_TRAP_GENERIC_ID_CORRUPTED_IP_HDR,
	DEVLINK_TRAP_GENERIC_ID_IPV4_SIP_BC,
	DEVLINK_TRAP_GENERIC_ID_IPV6_MC_DIP_RESERVED_SCOPE,
	DEVLINK_TRAP_GENERIC_ID_IPV6_MC_DIP_INTERFACE_LOCAL_SCOPE,
	DEVLINK_TRAP_GENERIC_ID_MTU_ERROR,
	DEVLINK_TRAP_GENERIC_ID_UNRESOLVED_NEIGH,
	DEVLINK_TRAP_GENERIC_ID_RPF,
	DEVLINK_TRAP_GENERIC_ID_REJECT_ROUTE,
	DEVLINK_TRAP_GENERIC_ID_IPV4_LPM_UNICAST_MISS,
	DEVLINK_TRAP_GENERIC_ID_IPV6_LPM_UNICAST_MISS,
	DEVLINK_TRAP_GENERIC_ID_NON_ROUTABLE,
	DEVLINK_TRAP_GENERIC_ID_DECAP_ERROR,
	DEVLINK_TRAP_GENERIC_ID_OVERLAY_SMAC_MC,
	DEVLINK_TRAP_GENERIC_ID_INGRESS_FLOW_ACTION_DROP,
	DEVLINK_TRAP_GENERIC_ID_EGRESS_FLOW_ACTION_DROP,
	DEVLINK_TRAP_GENERIC_ID_STP,
	DEVLINK_TRAP_GENERIC_ID_LACP,
	DEVLINK_TRAP_GENERIC_ID_LLDP,
	DEVLINK_TRAP_GENERIC_ID_IGMP_QUERY,
	DEVLINK_TRAP_GENERIC_ID_IGMP_V1_REPORT,
	DEVLINK_TRAP_GENERIC_ID_IGMP_V2_REPORT,
	DEVLINK_TRAP_GENERIC_ID_IGMP_V3_REPORT,
	DEVLINK_TRAP_GENERIC_ID_IGMP_V2_LEAVE,
	DEVLINK_TRAP_GENERIC_ID_MLD_QUERY,
	DEVLINK_TRAP_GENERIC_ID_MLD_V1_REPORT,
	DEVLINK_TRAP_GENERIC_ID_MLD_V2_REPORT,
	DEVLINK_TRAP_GENERIC_ID_MLD_V1_DONE,
	DEVLINK_TRAP_GENERIC_ID_IPV4_DHCP,
	DEVLINK_TRAP_GENERIC_ID_IPV6_DHCP,
	DEVLINK_TRAP_GENERIC_ID_ARP_REQUEST,
	DEVLINK_TRAP_GENERIC_ID_ARP_RESPONSE,
	DEVLINK_TRAP_GENERIC_ID_ARP_OVERLAY,
	DEVLINK_TRAP_GENERIC_ID_IPV6_NEIGH_SOLICIT,
	DEVLINK_TRAP_GENERIC_ID_IPV6_NEIGH_ADVERT,
	DEVLINK_TRAP_GENERIC_ID_IPV4_BFD,
	DEVLINK_TRAP_GENERIC_ID_IPV6_BFD,
	DEVLINK_TRAP_GENERIC_ID_IPV4_OSPF,
	DEVLINK_TRAP_GENERIC_ID_IPV6_OSPF,
	DEVLINK_TRAP_GENERIC_ID_IPV4_BGP,
	DEVLINK_TRAP_GENERIC_ID_IPV6_BGP,
	DEVLINK_TRAP_GENERIC_ID_IPV4_VRRP,
	DEVLINK_TRAP_GENERIC_ID_IPV6_VRRP,
	DEVLINK_TRAP_GENERIC_ID_IPV4_PIM,
	DEVLINK_TRAP_GENERIC_ID_IPV6_PIM,
	DEVLINK_TRAP_GENERIC_ID_UC_LB,
	DEVLINK_TRAP_GENERIC_ID_LOCAL_ROUTE,
	DEVLINK_TRAP_GENERIC_ID_EXTERNAL_ROUTE,
	DEVLINK_TRAP_GENERIC_ID_IPV6_UC_DIP_LINK_LOCAL_SCOPE,
	DEVLINK_TRAP_GENERIC_ID_IPV6_DIP_ALL_NODES,
	DEVLINK_TRAP_GENERIC_ID_IPV6_DIP_ALL_ROUTERS,
	DEVLINK_TRAP_GENERIC_ID_IPV6_ROUTER_SOLICIT,
	DEVLINK_TRAP_GENERIC_ID_IPV6_ROUTER_ADVERT,
	DEVLINK_TRAP_GENERIC_ID_IPV6_REसूचीECT,
	DEVLINK_TRAP_GENERIC_ID_IPV4_ROUTER_ALERT,
	DEVLINK_TRAP_GENERIC_ID_IPV6_ROUTER_ALERT,
	DEVLINK_TRAP_GENERIC_ID_PTP_EVENT,
	DEVLINK_TRAP_GENERIC_ID_PTP_GENERAL,
	DEVLINK_TRAP_GENERIC_ID_FLOW_ACTION_SAMPLE,
	DEVLINK_TRAP_GENERIC_ID_FLOW_ACTION_TRAP,
	DEVLINK_TRAP_GENERIC_ID_EARLY_DROP,
	DEVLINK_TRAP_GENERIC_ID_VXLAN_PARSING,
	DEVLINK_TRAP_GENERIC_ID_LLC_SNAP_PARSING,
	DEVLINK_TRAP_GENERIC_ID_VLAN_PARSING,
	DEVLINK_TRAP_GENERIC_ID_PPPOE_PPP_PARSING,
	DEVLINK_TRAP_GENERIC_ID_MPLS_PARSING,
	DEVLINK_TRAP_GENERIC_ID_ARP_PARSING,
	DEVLINK_TRAP_GENERIC_ID_IP_1_PARSING,
	DEVLINK_TRAP_GENERIC_ID_IP_N_PARSING,
	DEVLINK_TRAP_GENERIC_ID_GRE_PARSING,
	DEVLINK_TRAP_GENERIC_ID_UDP_PARSING,
	DEVLINK_TRAP_GENERIC_ID_TCP_PARSING,
	DEVLINK_TRAP_GENERIC_ID_IPSEC_PARSING,
	DEVLINK_TRAP_GENERIC_ID_SCTP_PARSING,
	DEVLINK_TRAP_GENERIC_ID_DCCP_PARSING,
	DEVLINK_TRAP_GENERIC_ID_GTP_PARSING,
	DEVLINK_TRAP_GENERIC_ID_ESP_PARSING,
	DEVLINK_TRAP_GENERIC_ID_BLACKHOLE_NEXTHOP,
	DEVLINK_TRAP_GENERIC_ID_DMAC_FILTER,

	/* Add new generic trap IDs above */
	__DEVLINK_TRAP_GENERIC_ID_MAX,
	DEVLINK_TRAP_GENERIC_ID_MAX = __DEVLINK_TRAP_GENERIC_ID_MAX - 1,
पूर्ण;

/* All trap groups must be करोcumented in
 * Documentation/networking/devlink/devlink-trap.rst
 */
क्रमागत devlink_trap_group_generic_id अणु
	DEVLINK_TRAP_GROUP_GENERIC_ID_L2_DROPS,
	DEVLINK_TRAP_GROUP_GENERIC_ID_L3_DROPS,
	DEVLINK_TRAP_GROUP_GENERIC_ID_L3_EXCEPTIONS,
	DEVLINK_TRAP_GROUP_GENERIC_ID_BUFFER_DROPS,
	DEVLINK_TRAP_GROUP_GENERIC_ID_TUNNEL_DROPS,
	DEVLINK_TRAP_GROUP_GENERIC_ID_ACL_DROPS,
	DEVLINK_TRAP_GROUP_GENERIC_ID_STP,
	DEVLINK_TRAP_GROUP_GENERIC_ID_LACP,
	DEVLINK_TRAP_GROUP_GENERIC_ID_LLDP,
	DEVLINK_TRAP_GROUP_GENERIC_ID_MC_SNOOPING,
	DEVLINK_TRAP_GROUP_GENERIC_ID_DHCP,
	DEVLINK_TRAP_GROUP_GENERIC_ID_NEIGH_DISCOVERY,
	DEVLINK_TRAP_GROUP_GENERIC_ID_BFD,
	DEVLINK_TRAP_GROUP_GENERIC_ID_OSPF,
	DEVLINK_TRAP_GROUP_GENERIC_ID_BGP,
	DEVLINK_TRAP_GROUP_GENERIC_ID_VRRP,
	DEVLINK_TRAP_GROUP_GENERIC_ID_PIM,
	DEVLINK_TRAP_GROUP_GENERIC_ID_UC_LB,
	DEVLINK_TRAP_GROUP_GENERIC_ID_LOCAL_DELIVERY,
	DEVLINK_TRAP_GROUP_GENERIC_ID_EXTERNAL_DELIVERY,
	DEVLINK_TRAP_GROUP_GENERIC_ID_IPV6,
	DEVLINK_TRAP_GROUP_GENERIC_ID_PTP_EVENT,
	DEVLINK_TRAP_GROUP_GENERIC_ID_PTP_GENERAL,
	DEVLINK_TRAP_GROUP_GENERIC_ID_ACL_SAMPLE,
	DEVLINK_TRAP_GROUP_GENERIC_ID_ACL_TRAP,
	DEVLINK_TRAP_GROUP_GENERIC_ID_PARSER_ERROR_DROPS,

	/* Add new generic trap group IDs above */
	__DEVLINK_TRAP_GROUP_GENERIC_ID_MAX,
	DEVLINK_TRAP_GROUP_GENERIC_ID_MAX =
		__DEVLINK_TRAP_GROUP_GENERIC_ID_MAX - 1,
पूर्ण;

#घोषणा DEVLINK_TRAP_GENERIC_NAME_SMAC_MC \
	"source_mac_is_multicast"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_VLAN_TAG_MISMATCH \
	"vlan_tag_mismatch"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_INGRESS_VLAN_FILTER \
	"ingress_vlan_filter"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_INGRESS_STP_FILTER \
	"ingress_spanning_tree_filter"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_EMPTY_TX_LIST \
	"port_list_is_empty"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_PORT_LOOPBACK_FILTER \
	"port_loopback_filter"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_BLACKHOLE_ROUTE \
	"blackhole_route"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_TTL_ERROR \
	"ttl_value_is_too_small"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_TAIL_DROP \
	"tail_drop"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_NON_IP_PACKET \
	"non_ip"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_UC_DIP_MC_DMAC \
	"uc_dip_over_mc_dmac"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_DIP_LB \
	"dip_is_loopback_address"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_SIP_MC \
	"sip_is_mc"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_SIP_LB \
	"sip_is_loopback_address"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_CORRUPTED_IP_HDR \
	"ip_header_corrupted"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV4_SIP_BC \
	"ipv4_sip_is_limited_bc"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_MC_DIP_RESERVED_SCOPE \
	"ipv6_mc_dip_reserved_scope"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_MC_DIP_INTERFACE_LOCAL_SCOPE \
	"ipv6_mc_dip_interface_local_scope"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_MTU_ERROR \
	"mtu_value_is_too_small"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_UNRESOLVED_NEIGH \
	"unresolved_neigh"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_RPF \
	"mc_reverse_path_forwarding"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_REJECT_ROUTE \
	"reject_route"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV4_LPM_UNICAST_MISS \
	"ipv4_lpm_miss"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_LPM_UNICAST_MISS \
	"ipv6_lpm_miss"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_NON_ROUTABLE \
	"non_routable_packet"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_DECAP_ERROR \
	"decap_error"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_OVERLAY_SMAC_MC \
	"overlay_smac_is_mc"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_INGRESS_FLOW_ACTION_DROP \
	"ingress_flow_action_drop"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_EGRESS_FLOW_ACTION_DROP \
	"egress_flow_action_drop"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_STP \
	"stp"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_LACP \
	"lacp"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_LLDP \
	"lldp"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IGMP_QUERY \
	"igmp_query"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IGMP_V1_REPORT \
	"igmp_v1_report"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IGMP_V2_REPORT \
	"igmp_v2_report"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IGMP_V3_REPORT \
	"igmp_v3_report"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IGMP_V2_LEAVE \
	"igmp_v2_leave"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_MLD_QUERY \
	"mld_query"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_MLD_V1_REPORT \
	"mld_v1_report"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_MLD_V2_REPORT \
	"mld_v2_report"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_MLD_V1_DONE \
	"mld_v1_done"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV4_DHCP \
	"ipv4_dhcp"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_DHCP \
	"ipv6_dhcp"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_ARP_REQUEST \
	"arp_request"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_ARP_RESPONSE \
	"arp_response"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_ARP_OVERLAY \
	"arp_overlay"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_NEIGH_SOLICIT \
	"ipv6_neigh_solicit"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_NEIGH_ADVERT \
	"ipv6_neigh_advert"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV4_BFD \
	"ipv4_bfd"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_BFD \
	"ipv6_bfd"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV4_OSPF \
	"ipv4_ospf"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_OSPF \
	"ipv6_ospf"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV4_BGP \
	"ipv4_bgp"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_BGP \
	"ipv6_bgp"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV4_VRRP \
	"ipv4_vrrp"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_VRRP \
	"ipv6_vrrp"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV4_PIM \
	"ipv4_pim"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_PIM \
	"ipv6_pim"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_UC_LB \
	"uc_loopback"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_LOCAL_ROUTE \
	"local_route"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_EXTERNAL_ROUTE \
	"external_route"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_UC_DIP_LINK_LOCAL_SCOPE \
	"ipv6_uc_dip_link_local_scope"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_DIP_ALL_NODES \
	"ipv6_dip_all_nodes"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_DIP_ALL_ROUTERS \
	"ipv6_dip_all_routers"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_ROUTER_SOLICIT \
	"ipv6_router_solicit"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_ROUTER_ADVERT \
	"ipv6_router_advert"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_REसूचीECT \
	"ipv6_redirect"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV4_ROUTER_ALERT \
	"ipv4_router_alert"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPV6_ROUTER_ALERT \
	"ipv6_router_alert"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_PTP_EVENT \
	"ptp_event"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_PTP_GENERAL \
	"ptp_general"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_FLOW_ACTION_SAMPLE \
	"flow_action_sample"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_FLOW_ACTION_TRAP \
	"flow_action_trap"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_EARLY_DROP \
	"early_drop"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_VXLAN_PARSING \
	"vxlan_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_LLC_SNAP_PARSING \
	"llc_snap_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_VLAN_PARSING \
	"vlan_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_PPPOE_PPP_PARSING \
	"pppoe_ppp_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_MPLS_PARSING \
	"mpls_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_ARP_PARSING \
	"arp_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IP_1_PARSING \
	"ip_1_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IP_N_PARSING \
	"ip_n_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_GRE_PARSING \
	"gre_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_UDP_PARSING \
	"udp_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_TCP_PARSING \
	"tcp_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_IPSEC_PARSING \
	"ipsec_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_SCTP_PARSING \
	"sctp_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_DCCP_PARSING \
	"dccp_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_GTP_PARSING \
	"gtp_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_ESP_PARSING \
	"esp_parsing"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_BLACKHOLE_NEXTHOP \
	"blackhole_nexthop"
#घोषणा DEVLINK_TRAP_GENERIC_NAME_DMAC_FILTER \
	"dmac_filter"

#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_L2_DROPS \
	"l2_drops"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_L3_DROPS \
	"l3_drops"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_L3_EXCEPTIONS \
	"l3_exceptions"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_BUFFER_DROPS \
	"buffer_drops"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_TUNNEL_DROPS \
	"tunnel_drops"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_ACL_DROPS \
	"acl_drops"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_STP \
	"stp"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_LACP \
	"lacp"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_LLDP \
	"lldp"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_MC_SNOOPING  \
	"mc_snooping"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_DHCP \
	"dhcp"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_NEIGH_DISCOVERY \
	"neigh_discovery"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_BFD \
	"bfd"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_OSPF \
	"ospf"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_BGP \
	"bgp"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_VRRP \
	"vrrp"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_PIM \
	"pim"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_UC_LB \
	"uc_loopback"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_LOCAL_DELIVERY \
	"local_delivery"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_EXTERNAL_DELIVERY \
	"external_delivery"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_IPV6 \
	"ipv6"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_PTP_EVENT \
	"ptp_event"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_PTP_GENERAL \
	"ptp_general"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_ACL_SAMPLE \
	"acl_sample"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_ACL_TRAP \
	"acl_trap"
#घोषणा DEVLINK_TRAP_GROUP_GENERIC_NAME_PARSER_ERROR_DROPS \
	"parser_error_drops"

#घोषणा DEVLINK_TRAP_GENERIC(_type, _init_action, _id, _group_id,	      \
			     _metadata_cap)				      \
	अणु								      \
		.type = DEVLINK_TRAP_TYPE_##_type,			      \
		.init_action = DEVLINK_TRAP_ACTION_##_init_action,	      \
		.generic = true,					      \
		.id = DEVLINK_TRAP_GENERIC_ID_##_id,			      \
		.name = DEVLINK_TRAP_GENERIC_NAME_##_id,		      \
		.init_group_id = _group_id,				      \
		.metadata_cap = _metadata_cap,				      \
	पूर्ण

#घोषणा DEVLINK_TRAP_DRIVER(_type, _init_action, _id, _name, _group_id,	      \
			    _metadata_cap)				      \
	अणु								      \
		.type = DEVLINK_TRAP_TYPE_##_type,			      \
		.init_action = DEVLINK_TRAP_ACTION_##_init_action,	      \
		.generic = false,					      \
		.id = _id,						      \
		.name = _name,						      \
		.init_group_id = _group_id,				      \
		.metadata_cap = _metadata_cap,				      \
	पूर्ण

#घोषणा DEVLINK_TRAP_GROUP_GENERIC(_id, _policer_id)			      \
	अणु								      \
		.name = DEVLINK_TRAP_GROUP_GENERIC_NAME_##_id,		      \
		.id = DEVLINK_TRAP_GROUP_GENERIC_ID_##_id,		      \
		.generic = true,					      \
		.init_policer_id = _policer_id,				      \
	पूर्ण

#घोषणा DEVLINK_TRAP_POLICER(_id, _rate, _burst, _max_rate, _min_rate,	      \
			     _max_burst, _min_burst)			      \
	अणु								      \
		.id = _id,						      \
		.init_rate = _rate,					      \
		.init_burst = _burst,					      \
		.max_rate = _max_rate,					      \
		.min_rate = _min_rate,					      \
		.max_burst = _max_burst,				      \
		.min_burst = _min_burst,				      \
	पूर्ण

काष्ठा devlink_ops अणु
	/**
	 * @supported_flash_update_params:
	 * mask of parameters supported by the driver's .flash_update
	 * implemementation.
	 */
	u32 supported_flash_update_params;
	अचिन्हित दीर्घ reload_actions;
	अचिन्हित दीर्घ reload_limits;
	पूर्णांक (*reload_करोwn)(काष्ठा devlink *devlink, bool netns_change,
			   क्रमागत devlink_reload_action action,
			   क्रमागत devlink_reload_limit limit,
			   काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*reload_up)(काष्ठा devlink *devlink, क्रमागत devlink_reload_action action,
			 क्रमागत devlink_reload_limit limit, u32 *actions_perक्रमmed,
			 काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*port_type_set)(काष्ठा devlink_port *devlink_port,
			     क्रमागत devlink_port_type port_type);
	पूर्णांक (*port_split)(काष्ठा devlink *devlink, अचिन्हित पूर्णांक port_index,
			  अचिन्हित पूर्णांक count, काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*port_unsplit)(काष्ठा devlink *devlink, अचिन्हित पूर्णांक port_index,
			    काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*sb_pool_get)(काष्ठा devlink *devlink, अचिन्हित पूर्णांक sb_index,
			   u16 pool_index,
			   काष्ठा devlink_sb_pool_info *pool_info);
	पूर्णांक (*sb_pool_set)(काष्ठा devlink *devlink, अचिन्हित पूर्णांक sb_index,
			   u16 pool_index, u32 size,
			   क्रमागत devlink_sb_threshold_type threshold_type,
			   काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*sb_port_pool_get)(काष्ठा devlink_port *devlink_port,
				अचिन्हित पूर्णांक sb_index, u16 pool_index,
				u32 *p_threshold);
	पूर्णांक (*sb_port_pool_set)(काष्ठा devlink_port *devlink_port,
				अचिन्हित पूर्णांक sb_index, u16 pool_index,
				u32 threshold, काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*sb_tc_pool_bind_get)(काष्ठा devlink_port *devlink_port,
				   अचिन्हित पूर्णांक sb_index,
				   u16 tc_index,
				   क्रमागत devlink_sb_pool_type pool_type,
				   u16 *p_pool_index, u32 *p_threshold);
	पूर्णांक (*sb_tc_pool_bind_set)(काष्ठा devlink_port *devlink_port,
				   अचिन्हित पूर्णांक sb_index,
				   u16 tc_index,
				   क्रमागत devlink_sb_pool_type pool_type,
				   u16 pool_index, u32 threshold,
				   काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*sb_occ_snapshot)(काष्ठा devlink *devlink,
			       अचिन्हित पूर्णांक sb_index);
	पूर्णांक (*sb_occ_max_clear)(काष्ठा devlink *devlink,
				अचिन्हित पूर्णांक sb_index);
	पूर्णांक (*sb_occ_port_pool_get)(काष्ठा devlink_port *devlink_port,
				    अचिन्हित पूर्णांक sb_index, u16 pool_index,
				    u32 *p_cur, u32 *p_max);
	पूर्णांक (*sb_occ_tc_port_bind_get)(काष्ठा devlink_port *devlink_port,
				       अचिन्हित पूर्णांक sb_index,
				       u16 tc_index,
				       क्रमागत devlink_sb_pool_type pool_type,
				       u32 *p_cur, u32 *p_max);

	पूर्णांक (*eचयन_mode_get)(काष्ठा devlink *devlink, u16 *p_mode);
	पूर्णांक (*eचयन_mode_set)(काष्ठा devlink *devlink, u16 mode,
				काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*eचयन_अंतरभूत_mode_get)(काष्ठा devlink *devlink, u8 *p_अंतरभूत_mode);
	पूर्णांक (*eचयन_अंतरभूत_mode_set)(काष्ठा devlink *devlink, u8 अंतरभूत_mode,
				       काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*eचयन_encap_mode_get)(काष्ठा devlink *devlink,
				      क्रमागत devlink_eचयन_encap_mode *p_encap_mode);
	पूर्णांक (*eचयन_encap_mode_set)(काष्ठा devlink *devlink,
				      क्रमागत devlink_eचयन_encap_mode encap_mode,
				      काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*info_get)(काष्ठा devlink *devlink, काष्ठा devlink_info_req *req,
			काष्ठा netlink_ext_ack *extack);
	/**
	 * @flash_update: Device flash update function
	 *
	 * Used to perक्रमm a flash update क्रम the device. The set of
	 * parameters supported by the driver should be set in
	 * supported_flash_update_params.
	 */
	पूर्णांक (*flash_update)(काष्ठा devlink *devlink,
			    काष्ठा devlink_flash_update_params *params,
			    काष्ठा netlink_ext_ack *extack);
	/**
	 * @trap_init: Trap initialization function.
	 *
	 * Should be used by device drivers to initialize the trap in the
	 * underlying device. Drivers should also store the provided trap
	 * context, so that they could efficiently pass it to
	 * devlink_trap_report() when the trap is triggered.
	 */
	पूर्णांक (*trap_init)(काष्ठा devlink *devlink,
			 स्थिर काष्ठा devlink_trap *trap, व्योम *trap_ctx);
	/**
	 * @trap_fini: Trap de-initialization function.
	 *
	 * Should be used by device drivers to de-initialize the trap in the
	 * underlying device.
	 */
	व्योम (*trap_fini)(काष्ठा devlink *devlink,
			  स्थिर काष्ठा devlink_trap *trap, व्योम *trap_ctx);
	/**
	 * @trap_action_set: Trap action set function.
	 */
	पूर्णांक (*trap_action_set)(काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_trap *trap,
			       क्रमागत devlink_trap_action action,
			       काष्ठा netlink_ext_ack *extack);
	/**
	 * @trap_group_init: Trap group initialization function.
	 *
	 * Should be used by device drivers to initialize the trap group in the
	 * underlying device.
	 */
	पूर्णांक (*trap_group_init)(काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_trap_group *group);
	/**
	 * @trap_group_set: Trap group parameters set function.
	 *
	 * Note: @policer can be शून्य when a policer is being unbound from
	 * @group.
	 */
	पूर्णांक (*trap_group_set)(काष्ठा devlink *devlink,
			      स्थिर काष्ठा devlink_trap_group *group,
			      स्थिर काष्ठा devlink_trap_policer *policer,
			      काष्ठा netlink_ext_ack *extack);
	/**
	 * @trap_group_action_set: Trap group action set function.
	 *
	 * If this callback is populated, it will take precedence over looping
	 * over all traps in a group and calling .trap_action_set().
	 */
	पूर्णांक (*trap_group_action_set)(काष्ठा devlink *devlink,
				     स्थिर काष्ठा devlink_trap_group *group,
				     क्रमागत devlink_trap_action action,
				     काष्ठा netlink_ext_ack *extack);
	/**
	 * @trap_policer_init: Trap policer initialization function.
	 *
	 * Should be used by device drivers to initialize the trap policer in
	 * the underlying device.
	 */
	पूर्णांक (*trap_policer_init)(काष्ठा devlink *devlink,
				 स्थिर काष्ठा devlink_trap_policer *policer);
	/**
	 * @trap_policer_fini: Trap policer de-initialization function.
	 *
	 * Should be used by device drivers to de-initialize the trap policer
	 * in the underlying device.
	 */
	व्योम (*trap_policer_fini)(काष्ठा devlink *devlink,
				  स्थिर काष्ठा devlink_trap_policer *policer);
	/**
	 * @trap_policer_set: Trap policer parameters set function.
	 */
	पूर्णांक (*trap_policer_set)(काष्ठा devlink *devlink,
				स्थिर काष्ठा devlink_trap_policer *policer,
				u64 rate, u64 burst,
				काष्ठा netlink_ext_ack *extack);
	/**
	 * @trap_policer_counter_get: Trap policer counter get function.
	 *
	 * Should be used by device drivers to report number of packets dropped
	 * by the policer.
	 */
	पूर्णांक (*trap_policer_counter_get)(काष्ठा devlink *devlink,
					स्थिर काष्ठा devlink_trap_policer *policer,
					u64 *p_drops);
	/**
	 * @port_function_hw_addr_get: Port function's hardware address get function.
	 *
	 * Should be used by device drivers to report the hardware address of a function managed
	 * by the devlink port. Driver should वापस -EOPNOTSUPP अगर it करोesn't support port
	 * function handling क्रम a particular port.
	 *
	 * Note: @extack can be शून्य when port notअगरier queries the port function.
	 */
	पूर्णांक (*port_function_hw_addr_get)(काष्ठा devlink *devlink, काष्ठा devlink_port *port,
					 u8 *hw_addr, पूर्णांक *hw_addr_len,
					 काष्ठा netlink_ext_ack *extack);
	/**
	 * @port_function_hw_addr_set: Port function's hardware address set function.
	 *
	 * Should be used by device drivers to set the hardware address of a function managed
	 * by the devlink port. Driver should वापस -EOPNOTSUPP अगर it करोesn't support port
	 * function handling क्रम a particular port.
	 */
	पूर्णांक (*port_function_hw_addr_set)(काष्ठा devlink *devlink, काष्ठा devlink_port *port,
					 स्थिर u8 *hw_addr, पूर्णांक hw_addr_len,
					 काष्ठा netlink_ext_ack *extack);
	/**
	 * port_new() - Add a new port function of a specअगरied flavor
	 * @devlink: Devlink instance
	 * @attrs: attributes of the new port
	 * @extack: extack क्रम reporting error messages
	 * @new_port_index: index of the new port
	 *
	 * Devlink core will call this device driver function upon user request
	 * to create a new port function of a specअगरied flavor and optional
	 * attributes
	 *
	 * Notes:
	 *	- Called without devlink instance lock being held. Drivers must
	 *	  implement own means of synchronization
	 *	- On success, drivers must रेजिस्टर a port with devlink core
	 *
	 * Return: 0 on success, negative value otherwise.
	 */
	पूर्णांक (*port_new)(काष्ठा devlink *devlink,
			स्थिर काष्ठा devlink_port_new_attrs *attrs,
			काष्ठा netlink_ext_ack *extack,
			अचिन्हित पूर्णांक *new_port_index);
	/**
	 * port_del() - Delete a port function
	 * @devlink: Devlink instance
	 * @port_index: port function index to delete
	 * @extack: extack क्रम reporting error messages
	 *
	 * Devlink core will call this device driver function upon user request
	 * to delete a previously created port function
	 *
	 * Notes:
	 *	- Called without devlink instance lock being held. Drivers must
	 *	  implement own means of synchronization
	 *	- On success, drivers must unरेजिस्टर the corresponding devlink
	 *	  port
	 *
	 * Return: 0 on success, negative value otherwise.
	 */
	पूर्णांक (*port_del)(काष्ठा devlink *devlink, अचिन्हित पूर्णांक port_index,
			काष्ठा netlink_ext_ack *extack);
	/**
	 * port_fn_state_get() - Get the state of a port function
	 * @devlink: Devlink instance
	 * @port: The devlink port
	 * @state: Admin configured state
	 * @opstate: Current operational state
	 * @extack: extack क्रम reporting error messages
	 *
	 * Reports the admin and operational state of a devlink port function
	 *
	 * Return: 0 on success, negative value otherwise.
	 */
	पूर्णांक (*port_fn_state_get)(काष्ठा devlink *devlink,
				 काष्ठा devlink_port *port,
				 क्रमागत devlink_port_fn_state *state,
				 क्रमागत devlink_port_fn_opstate *opstate,
				 काष्ठा netlink_ext_ack *extack);
	/**
	 * port_fn_state_set() - Set the admin state of a port function
	 * @devlink: Devlink instance
	 * @port: The devlink port
	 * @state: Admin state
	 * @extack: extack क्रम reporting error messages
	 *
	 * Set the admin state of a devlink port function
	 *
	 * Return: 0 on success, negative value otherwise.
	 */
	पूर्णांक (*port_fn_state_set)(काष्ठा devlink *devlink,
				 काष्ठा devlink_port *port,
				 क्रमागत devlink_port_fn_state state,
				 काष्ठा netlink_ext_ack *extack);
पूर्ण;

अटल अंतरभूत व्योम *devlink_priv(काष्ठा devlink *devlink)
अणु
	BUG_ON(!devlink);
	वापस &devlink->priv;
पूर्ण

अटल अंतरभूत काष्ठा devlink *priv_to_devlink(व्योम *priv)
अणु
	BUG_ON(!priv);
	वापस container_of(priv, काष्ठा devlink, priv);
पूर्ण

अटल अंतरभूत काष्ठा devlink_port *
netdev_to_devlink_port(काष्ठा net_device *dev)
अणु
	अगर (dev->netdev_ops->nकरो_get_devlink_port)
		वापस dev->netdev_ops->nकरो_get_devlink_port(dev);
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा devlink *netdev_to_devlink(काष्ठा net_device *dev)
अणु
	काष्ठा devlink_port *devlink_port = netdev_to_devlink_port(dev);

	अगर (devlink_port)
		वापस devlink_port->devlink;
	वापस शून्य;
पूर्ण

काष्ठा ib_device;

काष्ठा net *devlink_net(स्थिर काष्ठा devlink *devlink);
व्योम devlink_net_set(काष्ठा devlink *devlink, काष्ठा net *net);
काष्ठा devlink *devlink_alloc(स्थिर काष्ठा devlink_ops *ops, माप_प्रकार priv_size);
पूर्णांक devlink_रेजिस्टर(काष्ठा devlink *devlink, काष्ठा device *dev);
व्योम devlink_unरेजिस्टर(काष्ठा devlink *devlink);
व्योम devlink_reload_enable(काष्ठा devlink *devlink);
व्योम devlink_reload_disable(काष्ठा devlink *devlink);
व्योम devlink_मुक्त(काष्ठा devlink *devlink);
पूर्णांक devlink_port_रेजिस्टर(काष्ठा devlink *devlink,
			  काष्ठा devlink_port *devlink_port,
			  अचिन्हित पूर्णांक port_index);
व्योम devlink_port_unरेजिस्टर(काष्ठा devlink_port *devlink_port);
व्योम devlink_port_type_eth_set(काष्ठा devlink_port *devlink_port,
			       काष्ठा net_device *netdev);
व्योम devlink_port_type_ib_set(काष्ठा devlink_port *devlink_port,
			      काष्ठा ib_device *ibdev);
व्योम devlink_port_type_clear(काष्ठा devlink_port *devlink_port);
व्योम devlink_port_attrs_set(काष्ठा devlink_port *devlink_port,
			    काष्ठा devlink_port_attrs *devlink_port_attrs);
व्योम devlink_port_attrs_pci_pf_set(काष्ठा devlink_port *devlink_port, u32 controller,
				   u16 pf, bool बाह्यal);
व्योम devlink_port_attrs_pci_vf_set(काष्ठा devlink_port *devlink_port, u32 controller,
				   u16 pf, u16 vf, bool बाह्यal);
व्योम devlink_port_attrs_pci_sf_set(काष्ठा devlink_port *devlink_port,
				   u32 controller, u16 pf, u32 sf,
				   bool बाह्यal);
पूर्णांक devlink_sb_रेजिस्टर(काष्ठा devlink *devlink, अचिन्हित पूर्णांक sb_index,
			u32 size, u16 ingress_pools_count,
			u16 egress_pools_count, u16 ingress_tc_count,
			u16 egress_tc_count);
व्योम devlink_sb_unरेजिस्टर(काष्ठा devlink *devlink, अचिन्हित पूर्णांक sb_index);
पूर्णांक devlink_dpipe_table_रेजिस्टर(काष्ठा devlink *devlink,
				 स्थिर अक्षर *table_name,
				 काष्ठा devlink_dpipe_table_ops *table_ops,
				 व्योम *priv, bool counter_control_बाह्य);
व्योम devlink_dpipe_table_unरेजिस्टर(काष्ठा devlink *devlink,
				    स्थिर अक्षर *table_name);
पूर्णांक devlink_dpipe_headers_रेजिस्टर(काष्ठा devlink *devlink,
				   काष्ठा devlink_dpipe_headers *dpipe_headers);
व्योम devlink_dpipe_headers_unरेजिस्टर(काष्ठा devlink *devlink);
bool devlink_dpipe_table_counter_enabled(काष्ठा devlink *devlink,
					 स्थिर अक्षर *table_name);
पूर्णांक devlink_dpipe_entry_ctx_prepare(काष्ठा devlink_dpipe_dump_ctx *dump_ctx);
पूर्णांक devlink_dpipe_entry_ctx_append(काष्ठा devlink_dpipe_dump_ctx *dump_ctx,
				   काष्ठा devlink_dpipe_entry *entry);
पूर्णांक devlink_dpipe_entry_ctx_बंद(काष्ठा devlink_dpipe_dump_ctx *dump_ctx);
व्योम devlink_dpipe_entry_clear(काष्ठा devlink_dpipe_entry *entry);
पूर्णांक devlink_dpipe_action_put(काष्ठा sk_buff *skb,
			     काष्ठा devlink_dpipe_action *action);
पूर्णांक devlink_dpipe_match_put(काष्ठा sk_buff *skb,
			    काष्ठा devlink_dpipe_match *match);
बाह्य काष्ठा devlink_dpipe_header devlink_dpipe_header_ethernet;
बाह्य काष्ठा devlink_dpipe_header devlink_dpipe_header_ipv4;
बाह्य काष्ठा devlink_dpipe_header devlink_dpipe_header_ipv6;

पूर्णांक devlink_resource_रेजिस्टर(काष्ठा devlink *devlink,
			      स्थिर अक्षर *resource_name,
			      u64 resource_size,
			      u64 resource_id,
			      u64 parent_resource_id,
			      स्थिर काष्ठा devlink_resource_size_params *size_params);
व्योम devlink_resources_unरेजिस्टर(काष्ठा devlink *devlink,
				  काष्ठा devlink_resource *resource);
पूर्णांक devlink_resource_size_get(काष्ठा devlink *devlink,
			      u64 resource_id,
			      u64 *p_resource_size);
पूर्णांक devlink_dpipe_table_resource_set(काष्ठा devlink *devlink,
				     स्थिर अक्षर *table_name, u64 resource_id,
				     u64 resource_units);
व्योम devlink_resource_occ_get_रेजिस्टर(काष्ठा devlink *devlink,
				       u64 resource_id,
				       devlink_resource_occ_get_t *occ_get,
				       व्योम *occ_get_priv);
व्योम devlink_resource_occ_get_unरेजिस्टर(काष्ठा devlink *devlink,
					 u64 resource_id);
पूर्णांक devlink_params_रेजिस्टर(काष्ठा devlink *devlink,
			    स्थिर काष्ठा devlink_param *params,
			    माप_प्रकार params_count);
व्योम devlink_params_unरेजिस्टर(काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_param *params,
			       माप_प्रकार params_count);
व्योम devlink_params_publish(काष्ठा devlink *devlink);
व्योम devlink_params_unpublish(काष्ठा devlink *devlink);
पूर्णांक devlink_port_params_रेजिस्टर(काष्ठा devlink_port *devlink_port,
				 स्थिर काष्ठा devlink_param *params,
				 माप_प्रकार params_count);
व्योम devlink_port_params_unरेजिस्टर(काष्ठा devlink_port *devlink_port,
				    स्थिर काष्ठा devlink_param *params,
				    माप_प्रकार params_count);
पूर्णांक devlink_param_driverinit_value_get(काष्ठा devlink *devlink, u32 param_id,
				       जोड़ devlink_param_value *init_val);
पूर्णांक devlink_param_driverinit_value_set(काष्ठा devlink *devlink, u32 param_id,
				       जोड़ devlink_param_value init_val);
पूर्णांक
devlink_port_param_driverinit_value_get(काष्ठा devlink_port *devlink_port,
					u32 param_id,
					जोड़ devlink_param_value *init_val);
पूर्णांक devlink_port_param_driverinit_value_set(काष्ठा devlink_port *devlink_port,
					    u32 param_id,
					    जोड़ devlink_param_value init_val);
व्योम devlink_param_value_changed(काष्ठा devlink *devlink, u32 param_id);
व्योम devlink_port_param_value_changed(काष्ठा devlink_port *devlink_port,
				      u32 param_id);
व्योम devlink_param_value_str_fill(जोड़ devlink_param_value *dst_val,
				  स्थिर अक्षर *src);
काष्ठा devlink_region *
devlink_region_create(काष्ठा devlink *devlink,
		      स्थिर काष्ठा devlink_region_ops *ops,
		      u32 region_max_snapshots, u64 region_size);
काष्ठा devlink_region *
devlink_port_region_create(काष्ठा devlink_port *port,
			   स्थिर काष्ठा devlink_port_region_ops *ops,
			   u32 region_max_snapshots, u64 region_size);
व्योम devlink_region_destroy(काष्ठा devlink_region *region);
व्योम devlink_port_region_destroy(काष्ठा devlink_region *region);

पूर्णांक devlink_region_snapshot_id_get(काष्ठा devlink *devlink, u32 *id);
व्योम devlink_region_snapshot_id_put(काष्ठा devlink *devlink, u32 id);
पूर्णांक devlink_region_snapshot_create(काष्ठा devlink_region *region,
				   u8 *data, u32 snapshot_id);
पूर्णांक devlink_info_serial_number_put(काष्ठा devlink_info_req *req,
				   स्थिर अक्षर *sn);
पूर्णांक devlink_info_driver_name_put(काष्ठा devlink_info_req *req,
				 स्थिर अक्षर *name);
पूर्णांक devlink_info_board_serial_number_put(काष्ठा devlink_info_req *req,
					 स्थिर अक्षर *bsn);
पूर्णांक devlink_info_version_fixed_put(काष्ठा devlink_info_req *req,
				   स्थिर अक्षर *version_name,
				   स्थिर अक्षर *version_value);
पूर्णांक devlink_info_version_stored_put(काष्ठा devlink_info_req *req,
				    स्थिर अक्षर *version_name,
				    स्थिर अक्षर *version_value);
पूर्णांक devlink_info_version_running_put(काष्ठा devlink_info_req *req,
				     स्थिर अक्षर *version_name,
				     स्थिर अक्षर *version_value);

पूर्णांक devlink_fmsg_obj_nest_start(काष्ठा devlink_fmsg *fmsg);
पूर्णांक devlink_fmsg_obj_nest_end(काष्ठा devlink_fmsg *fmsg);

पूर्णांक devlink_fmsg_pair_nest_start(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name);
पूर्णांक devlink_fmsg_pair_nest_end(काष्ठा devlink_fmsg *fmsg);

पूर्णांक devlink_fmsg_arr_pair_nest_start(काष्ठा devlink_fmsg *fmsg,
				     स्थिर अक्षर *name);
पूर्णांक devlink_fmsg_arr_pair_nest_end(काष्ठा devlink_fmsg *fmsg);
पूर्णांक devlink_fmsg_binary_pair_nest_start(काष्ठा devlink_fmsg *fmsg,
					स्थिर अक्षर *name);
पूर्णांक devlink_fmsg_binary_pair_nest_end(काष्ठा devlink_fmsg *fmsg);

पूर्णांक devlink_fmsg_bool_put(काष्ठा devlink_fmsg *fmsg, bool value);
पूर्णांक devlink_fmsg_u8_put(काष्ठा devlink_fmsg *fmsg, u8 value);
पूर्णांक devlink_fmsg_u32_put(काष्ठा devlink_fmsg *fmsg, u32 value);
पूर्णांक devlink_fmsg_u64_put(काष्ठा devlink_fmsg *fmsg, u64 value);
पूर्णांक devlink_fmsg_string_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *value);
पूर्णांक devlink_fmsg_binary_put(काष्ठा devlink_fmsg *fmsg, स्थिर व्योम *value,
			    u16 value_len);

पूर्णांक devlink_fmsg_bool_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
			       bool value);
पूर्णांक devlink_fmsg_u8_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
			     u8 value);
पूर्णांक devlink_fmsg_u32_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
			      u32 value);
पूर्णांक devlink_fmsg_u64_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
			      u64 value);
पूर्णांक devlink_fmsg_string_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
				 स्थिर अक्षर *value);
पूर्णांक devlink_fmsg_binary_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
				 स्थिर व्योम *value, u32 value_len);

काष्ठा devlink_health_reporter *
devlink_health_reporter_create(काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_health_reporter_ops *ops,
			       u64 graceful_period, व्योम *priv);

काष्ठा devlink_health_reporter *
devlink_port_health_reporter_create(काष्ठा devlink_port *port,
				    स्थिर काष्ठा devlink_health_reporter_ops *ops,
				    u64 graceful_period, व्योम *priv);

व्योम
devlink_health_reporter_destroy(काष्ठा devlink_health_reporter *reporter);

व्योम
devlink_port_health_reporter_destroy(काष्ठा devlink_health_reporter *reporter);

व्योम *
devlink_health_reporter_priv(काष्ठा devlink_health_reporter *reporter);
पूर्णांक devlink_health_report(काष्ठा devlink_health_reporter *reporter,
			  स्थिर अक्षर *msg, व्योम *priv_ctx);
व्योम
devlink_health_reporter_state_update(काष्ठा devlink_health_reporter *reporter,
				     क्रमागत devlink_health_reporter_state state);
व्योम
devlink_health_reporter_recovery_करोne(काष्ठा devlink_health_reporter *reporter);

bool devlink_is_reload_failed(स्थिर काष्ठा devlink *devlink);
व्योम devlink_remote_reload_actions_perक्रमmed(काष्ठा devlink *devlink,
					     क्रमागत devlink_reload_limit limit,
					     u32 actions_perक्रमmed);

व्योम devlink_flash_update_status_notअगरy(काष्ठा devlink *devlink,
					स्थिर अक्षर *status_msg,
					स्थिर अक्षर *component,
					अचिन्हित दीर्घ करोne,
					अचिन्हित दीर्घ total);
व्योम devlink_flash_update_समयout_notअगरy(काष्ठा devlink *devlink,
					 स्थिर अक्षर *status_msg,
					 स्थिर अक्षर *component,
					 अचिन्हित दीर्घ समयout);

पूर्णांक devlink_traps_रेजिस्टर(काष्ठा devlink *devlink,
			   स्थिर काष्ठा devlink_trap *traps,
			   माप_प्रकार traps_count, व्योम *priv);
व्योम devlink_traps_unरेजिस्टर(काष्ठा devlink *devlink,
			      स्थिर काष्ठा devlink_trap *traps,
			      माप_प्रकार traps_count);
व्योम devlink_trap_report(काष्ठा devlink *devlink, काष्ठा sk_buff *skb,
			 व्योम *trap_ctx, काष्ठा devlink_port *in_devlink_port,
			 स्थिर काष्ठा flow_action_cookie *fa_cookie);
व्योम *devlink_trap_ctx_priv(व्योम *trap_ctx);
पूर्णांक devlink_trap_groups_रेजिस्टर(काष्ठा devlink *devlink,
				 स्थिर काष्ठा devlink_trap_group *groups,
				 माप_प्रकार groups_count);
व्योम devlink_trap_groups_unरेजिस्टर(काष्ठा devlink *devlink,
				    स्थिर काष्ठा devlink_trap_group *groups,
				    माप_प्रकार groups_count);
पूर्णांक
devlink_trap_policers_रेजिस्टर(काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_trap_policer *policers,
			       माप_प्रकार policers_count);
व्योम
devlink_trap_policers_unरेजिस्टर(काष्ठा devlink *devlink,
				 स्थिर काष्ठा devlink_trap_policer *policers,
				 माप_प्रकार policers_count);

#अगर IS_ENABLED(CONFIG_NET_DEVLINK)

व्योम devlink_compat_running_version(काष्ठा net_device *dev,
				    अक्षर *buf, माप_प्रकार len);
पूर्णांक devlink_compat_flash_update(काष्ठा net_device *dev, स्थिर अक्षर *file_name);
पूर्णांक devlink_compat_phys_port_name_get(काष्ठा net_device *dev,
				      अक्षर *name, माप_प्रकार len);
पूर्णांक devlink_compat_चयन_id_get(काष्ठा net_device *dev,
				 काष्ठा netdev_phys_item_id *ppid);

#अन्यथा

अटल अंतरभूत व्योम
devlink_compat_running_version(काष्ठा net_device *dev, अक्षर *buf, माप_प्रकार len)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
devlink_compat_flash_update(काष्ठा net_device *dev, स्थिर अक्षर *file_name)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
devlink_compat_phys_port_name_get(काष्ठा net_device *dev,
				  अक्षर *name, माप_प्रकार len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
devlink_compat_चयन_id_get(काष्ठा net_device *dev,
			     काष्ठा netdev_phys_item_id *ppid)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _NET_DEVLINK_H_ */
