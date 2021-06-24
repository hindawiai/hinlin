<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  FiberChannel transport specअगरic attributes exported to sysfs.
 *
 *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.
 *  Copyright (C) 2004-2007   James Smart, Emulex Corporation
 *    Reग_लिखो क्रम host, target, device, and remote port attributes,
 *    statistics, and service functions...
 *    Add vports, etc
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bsg-lib.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <net/netlink.h>
#समावेश <scsi/scsi_netlink_fc.h>
#समावेश <scsi/scsi_bsg_fc.h>
#समावेश <uapi/scsi/fc/fc_els.h>
#समावेश "scsi_priv.h"

अटल पूर्णांक fc_queue_work(काष्ठा Scsi_Host *, काष्ठा work_काष्ठा *);
अटल व्योम fc_vport_sched_delete(काष्ठा work_काष्ठा *work);
अटल पूर्णांक fc_vport_setup(काष्ठा Scsi_Host *shost, पूर्णांक channel,
	काष्ठा device *pdev, काष्ठा fc_vport_identअगरiers  *ids,
	काष्ठा fc_vport **vport);
अटल पूर्णांक fc_bsg_hostadd(काष्ठा Scsi_Host *, काष्ठा fc_host_attrs *);
अटल पूर्णांक fc_bsg_rportadd(काष्ठा Scsi_Host *, काष्ठा fc_rport *);
अटल व्योम fc_bsg_हटाओ(काष्ठा request_queue *);
अटल व्योम fc_bsg_goose_queue(काष्ठा fc_rport *);
अटल व्योम fc_li_stats_update(काष्ठा fc_fn_li_desc *li_desc,
			       काष्ठा fc_fpin_stats *stats);
अटल व्योम fc_delivery_stats_update(u32 reason_code,
				     काष्ठा fc_fpin_stats *stats);
अटल व्योम fc_cn_stats_update(u16 event_type, काष्ठा fc_fpin_stats *stats);

/*
 * Module Parameters
 */

/*
 * dev_loss_पंचांगo: the शेष number of seconds that the FC transport
 *   should insulate the loss of a remote port.
 *   The maximum will be capped by the value of SCSI_DEVICE_BLOCK_MAX_TIMEOUT.
 */
अटल अचिन्हित पूर्णांक fc_dev_loss_पंचांगo = 60;		/* seconds */

module_param_named(dev_loss_पंचांगo, fc_dev_loss_पंचांगo, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(dev_loss_पंचांगo,
		 "Maximum number of seconds that the FC transport should"
		 " insulate the loss of a remote port. Once this value is"
		 " exceeded, the scsi target is removed. Value should be"
		 " between 1 and SCSI_DEVICE_BLOCK_MAX_TIMEOUT if"
		 " fast_io_fail_tmo is not set.");

/*
 * Redefine so that we can have same named attributes in the
 * sdev/starget/host objects.
 */
#घोषणा FC_DEVICE_ATTR(_prefix,_name,_mode,_show,_store)		\
काष्ठा device_attribute device_attr_##_prefix##_##_name = 	\
	__ATTR(_name,_mode,_show,_store)

#घोषणा fc_क्रमागत_name_search(title, table_type, table)			\
अटल स्थिर अक्षर *get_fc_##title##_name(क्रमागत table_type table_key)	\
अणु									\
	पूर्णांक i;								\
	अक्षर *name = शून्य;						\
									\
	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु			\
		अगर (table[i].value == table_key) अणु			\
			name = table[i].name;				\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
	वापस name;							\
पूर्ण

#घोषणा fc_क्रमागत_name_match(title, table_type, table)			\
अटल पूर्णांक get_fc_##title##_match(स्थिर अक्षर *table_key,		\
		क्रमागत table_type *value)					\
अणु									\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु			\
		अगर (म_भेदन(table_key, table[i].name,			\
				table[i].matchlen) == 0) अणु		\
			*value = table[i].value;			\
			वापस 0; /* success */				\
		पूर्ण							\
	पूर्ण								\
	वापस 1; /* failure */						\
पूर्ण


/* Convert fc_port_type values to ascii string name */
अटल काष्ठा अणु
	क्रमागत fc_port_type	value;
	अक्षर			*name;
पूर्ण fc_port_type_names[] = अणु
	अणु FC_PORTTYPE_UNKNOWN,		"Unknown" पूर्ण,
	अणु FC_PORTTYPE_OTHER,		"Other" पूर्ण,
	अणु FC_PORTTYPE_NOTPRESENT,	"Not Present" पूर्ण,
	अणु FC_PORTTYPE_NPORT,	"NPort (fabric via point-to-point)" पूर्ण,
	अणु FC_PORTTYPE_NLPORT,	"NLPort (fabric via loop)" पूर्ण,
	अणु FC_PORTTYPE_LPORT,	"LPort (private loop)" पूर्ण,
	अणु FC_PORTTYPE_PTP,	"Point-To-Point (direct nport connection)" पूर्ण,
	अणु FC_PORTTYPE_NPIV,		"NPIV VPORT" पूर्ण,
पूर्ण;
fc_क्रमागत_name_search(port_type, fc_port_type, fc_port_type_names)
#घोषणा FC_PORTTYPE_MAX_NAMELEN		50

/* Reuse fc_port_type क्रमागत function क्रम vport_type */
#घोषणा get_fc_vport_type_name get_fc_port_type_name


/* Convert fc_host_event_code values to ascii string name */
अटल स्थिर काष्ठा अणु
	क्रमागत fc_host_event_code		value;
	अक्षर				*name;
पूर्ण fc_host_event_code_names[] = अणु
	अणु FCH_EVT_LIP,			"lip" पूर्ण,
	अणु FCH_EVT_LINKUP,		"link_up" पूर्ण,
	अणु FCH_EVT_LINKDOWN,		"link_down" पूर्ण,
	अणु FCH_EVT_LIPRESET,		"lip_reset" पूर्ण,
	अणु FCH_EVT_RSCN,			"rscn" पूर्ण,
	अणु FCH_EVT_ADAPTER_CHANGE,	"adapter_chg" पूर्ण,
	अणु FCH_EVT_PORT_UNKNOWN,		"port_unknown" पूर्ण,
	अणु FCH_EVT_PORT_ONLINE,		"port_online" पूर्ण,
	अणु FCH_EVT_PORT_OFFLINE,		"port_offline" पूर्ण,
	अणु FCH_EVT_PORT_FABRIC,		"port_fabric" पूर्ण,
	अणु FCH_EVT_LINK_UNKNOWN,		"link_unknown" पूर्ण,
	अणु FCH_EVT_LINK_FPIN,		"link_FPIN" पूर्ण,
	अणु FCH_EVT_VENDOR_UNIQUE,	"vendor_unique" पूर्ण,
पूर्ण;
fc_क्रमागत_name_search(host_event_code, fc_host_event_code,
		fc_host_event_code_names)
#घोषणा FC_HOST_EVENT_CODE_MAX_NAMELEN	30


/* Convert fc_port_state values to ascii string name */
अटल काष्ठा अणु
	क्रमागत fc_port_state	value;
	अक्षर			*name;
	पूर्णांक			matchlen;
पूर्ण fc_port_state_names[] = अणु
	अणु FC_PORTSTATE_UNKNOWN,		"Unknown", 7पूर्ण,
	अणु FC_PORTSTATE_NOTPRESENT,	"Not Present", 11 पूर्ण,
	अणु FC_PORTSTATE_ONLINE,		"Online", 6 पूर्ण,
	अणु FC_PORTSTATE_OFFLINE,		"Offline", 7 पूर्ण,
	अणु FC_PORTSTATE_BLOCKED,		"Blocked", 7 पूर्ण,
	अणु FC_PORTSTATE_BYPASSED,	"Bypassed", 8 पूर्ण,
	अणु FC_PORTSTATE_DIAGNOSTICS,	"Diagnostics", 11 पूर्ण,
	अणु FC_PORTSTATE_LINKDOWN,	"Linkdown", 8 पूर्ण,
	अणु FC_PORTSTATE_ERROR,		"Error", 5 पूर्ण,
	अणु FC_PORTSTATE_LOOPBACK,	"Loopback", 8 पूर्ण,
	अणु FC_PORTSTATE_DELETED,		"Deleted", 7 पूर्ण,
	अणु FC_PORTSTATE_MARGINAL,	"Marginal", 8 पूर्ण,
पूर्ण;
fc_क्रमागत_name_search(port_state, fc_port_state, fc_port_state_names)
fc_क्रमागत_name_match(port_state, fc_port_state, fc_port_state_names)
#घोषणा FC_PORTSTATE_MAX_NAMELEN	20


/* Convert fc_vport_state values to ascii string name */
अटल काष्ठा अणु
	क्रमागत fc_vport_state	value;
	अक्षर			*name;
पूर्ण fc_vport_state_names[] = अणु
	अणु FC_VPORT_UNKNOWN,		"Unknown" पूर्ण,
	अणु FC_VPORT_ACTIVE,		"Active" पूर्ण,
	अणु FC_VPORT_DISABLED,		"Disabled" पूर्ण,
	अणु FC_VPORT_LINKDOWN,		"Linkdown" पूर्ण,
	अणु FC_VPORT_INITIALIZING,	"Initializing" पूर्ण,
	अणु FC_VPORT_NO_FABRIC_SUPP,	"No Fabric Support" पूर्ण,
	अणु FC_VPORT_NO_FABRIC_RSCS,	"No Fabric Resources" पूर्ण,
	अणु FC_VPORT_FABRIC_LOGOUT,	"Fabric Logout" पूर्ण,
	अणु FC_VPORT_FABRIC_REJ_WWN,	"Fabric Rejected WWN" पूर्ण,
	अणु FC_VPORT_FAILED,		"VPort Failed" पूर्ण,
पूर्ण;
fc_क्रमागत_name_search(vport_state, fc_vport_state, fc_vport_state_names)
#घोषणा FC_VPORTSTATE_MAX_NAMELEN	24

/* Reuse fc_vport_state क्रमागत function क्रम vport_last_state */
#घोषणा get_fc_vport_last_state_name get_fc_vport_state_name


/* Convert fc_tgtid_binding_type values to ascii string name */
अटल स्थिर काष्ठा अणु
	क्रमागत fc_tgtid_binding_type	value;
	अक्षर				*name;
	पूर्णांक				matchlen;
पूर्ण fc_tgtid_binding_type_names[] = अणु
	अणु FC_TGTID_BIND_NONE, "none", 4 पूर्ण,
	अणु FC_TGTID_BIND_BY_WWPN, "wwpn (World Wide Port Name)", 4 पूर्ण,
	अणु FC_TGTID_BIND_BY_WWNN, "wwnn (World Wide Node Name)", 4 पूर्ण,
	अणु FC_TGTID_BIND_BY_ID, "port_id (FC Address)", 7 पूर्ण,
पूर्ण;
fc_क्रमागत_name_search(tgtid_bind_type, fc_tgtid_binding_type,
		fc_tgtid_binding_type_names)
fc_क्रमागत_name_match(tgtid_bind_type, fc_tgtid_binding_type,
		fc_tgtid_binding_type_names)
#घोषणा FC_BINDTYPE_MAX_NAMELEN	30


#घोषणा fc_bitfield_name_search(title, table)			\
अटल sमाप_प्रकार							\
get_fc_##title##_names(u32 table_key, अक्षर *buf)		\
अणु								\
	अक्षर *prefix = "";					\
	sमाप_प्रकार len = 0;					\
	पूर्णांक i;							\
								\
	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु		\
		अगर (table[i].value & table_key) अणु		\
			len += प्र_लिखो(buf + len, "%s%s",	\
				prefix, table[i].name);		\
			prefix = ", ";				\
		पूर्ण						\
	पूर्ण							\
	len += प्र_लिखो(buf + len, "\n");			\
	वापस len;						\
पूर्ण


/* Convert FC_COS bit values to ascii string name */
अटल स्थिर काष्ठा अणु
	u32 			value;
	अक्षर			*name;
पूर्ण fc_cos_names[] = अणु
	अणु FC_COS_CLASS1,	"Class 1" पूर्ण,
	अणु FC_COS_CLASS2,	"Class 2" पूर्ण,
	अणु FC_COS_CLASS3,	"Class 3" पूर्ण,
	अणु FC_COS_CLASS4,	"Class 4" पूर्ण,
	अणु FC_COS_CLASS6,	"Class 6" पूर्ण,
पूर्ण;
fc_bitfield_name_search(cos, fc_cos_names)


/* Convert FC_PORTSPEED bit values to ascii string name */
अटल स्थिर काष्ठा अणु
	u32 			value;
	अक्षर			*name;
पूर्ण fc_port_speed_names[] = अणु
	अणु FC_PORTSPEED_1GBIT,		"1 Gbit" पूर्ण,
	अणु FC_PORTSPEED_2GBIT,		"2 Gbit" पूर्ण,
	अणु FC_PORTSPEED_4GBIT,		"4 Gbit" पूर्ण,
	अणु FC_PORTSPEED_10GBIT,		"10 Gbit" पूर्ण,
	अणु FC_PORTSPEED_8GBIT,		"8 Gbit" पूर्ण,
	अणु FC_PORTSPEED_16GBIT,		"16 Gbit" पूर्ण,
	अणु FC_PORTSPEED_32GBIT,		"32 Gbit" पूर्ण,
	अणु FC_PORTSPEED_20GBIT,		"20 Gbit" पूर्ण,
	अणु FC_PORTSPEED_40GBIT,		"40 Gbit" पूर्ण,
	अणु FC_PORTSPEED_50GBIT,		"50 Gbit" पूर्ण,
	अणु FC_PORTSPEED_100GBIT,		"100 Gbit" पूर्ण,
	अणु FC_PORTSPEED_25GBIT,		"25 Gbit" पूर्ण,
	अणु FC_PORTSPEED_64GBIT,		"64 Gbit" पूर्ण,
	अणु FC_PORTSPEED_128GBIT,		"128 Gbit" पूर्ण,
	अणु FC_PORTSPEED_256GBIT,		"256 Gbit" पूर्ण,
	अणु FC_PORTSPEED_NOT_NEGOTIATED,	"Not Negotiated" पूर्ण,
पूर्ण;
fc_bitfield_name_search(port_speed, fc_port_speed_names)


अटल पूर्णांक
show_fc_fc4s (अक्षर *buf, u8 *fc4_list)
अणु
	पूर्णांक i, len=0;

	क्रम (i = 0; i < FC_FC4_LIST_SIZE; i++, fc4_list++)
		len += प्र_लिखो(buf + len , "0x%02x ", *fc4_list);
	len += प्र_लिखो(buf + len, "\n");
	वापस len;
पूर्ण


/* Convert FC_PORT_ROLE bit values to ascii string name */
अटल स्थिर काष्ठा अणु
	u32 			value;
	अक्षर			*name;
पूर्ण fc_port_role_names[] = अणु
	अणु FC_PORT_ROLE_FCP_TARGET,		"FCP Target" पूर्ण,
	अणु FC_PORT_ROLE_FCP_INITIATOR,		"FCP Initiator" पूर्ण,
	अणु FC_PORT_ROLE_IP_PORT,			"IP Port" पूर्ण,
	अणु FC_PORT_ROLE_FCP_DUMMY_INITIATOR,	"FCP Dummy Initiator" पूर्ण,
	अणु FC_PORT_ROLE_NVME_INITIATOR,		"NVMe Initiator" पूर्ण,
	अणु FC_PORT_ROLE_NVME_TARGET,		"NVMe Target" पूर्ण,
	अणु FC_PORT_ROLE_NVME_DISCOVERY,		"NVMe Discovery" पूर्ण,
पूर्ण;
fc_bitfield_name_search(port_roles, fc_port_role_names)

/*
 * Define roles that are specअगरic to port_id. Values are relative to ROLE_MASK.
 */
#घोषणा FC_WELLKNOWN_PORTID_MASK	0xfffff0
#घोषणा FC_WELLKNOWN_ROLE_MASK  	0x00000f
#घोषणा FC_FPORT_PORTID			0x00000e
#घोषणा FC_FABCTLR_PORTID		0x00000d
#घोषणा FC_सूचीSRVR_PORTID		0x00000c
#घोषणा FC_TIMESRVR_PORTID		0x00000b
#घोषणा FC_MGMTSRVR_PORTID		0x00000a


अटल व्योम fc_समयout_deleted_rport(काष्ठा work_काष्ठा *work);
अटल व्योम fc_समयout_fail_rport_io(काष्ठा work_काष्ठा *work);
अटल व्योम fc_scsi_scan_rport(काष्ठा work_काष्ठा *work);

/*
 * Attribute counts pre object type...
 * Increase these values अगर you add attributes
 */
#घोषणा FC_STARGET_NUM_ATTRS 	3
#घोषणा FC_RPORT_NUM_ATTRS	10
#घोषणा FC_VPORT_NUM_ATTRS	9
#घोषणा FC_HOST_NUM_ATTRS	29

काष्ठा fc_पूर्णांकernal अणु
	काष्ठा scsi_transport_ढाँचा t;
	काष्ठा fc_function_ढाँचा *f;

	/*
	 * For attributes : each object has :
	 *   An array of the actual attributes काष्ठाures
	 *   An array of null-terminated poपूर्णांकers to the attribute
	 *     काष्ठाures - used क्रम mid-layer पूर्णांकeraction.
	 *
	 * The attribute containers क्रम the starget and host are are
	 * part of the midlayer. As the remote port is specअगरic to the
	 * fc transport, we must provide the attribute container.
	 */
	काष्ठा device_attribute निजी_starget_attrs[
							FC_STARGET_NUM_ATTRS];
	काष्ठा device_attribute *starget_attrs[FC_STARGET_NUM_ATTRS + 1];

	काष्ठा device_attribute निजी_host_attrs[FC_HOST_NUM_ATTRS];
	काष्ठा device_attribute *host_attrs[FC_HOST_NUM_ATTRS + 1];

	काष्ठा transport_container rport_attr_cont;
	काष्ठा device_attribute निजी_rport_attrs[FC_RPORT_NUM_ATTRS];
	काष्ठा device_attribute *rport_attrs[FC_RPORT_NUM_ATTRS + 1];

	काष्ठा transport_container vport_attr_cont;
	काष्ठा device_attribute निजी_vport_attrs[FC_VPORT_NUM_ATTRS];
	काष्ठा device_attribute *vport_attrs[FC_VPORT_NUM_ATTRS + 1];
पूर्ण;

#घोषणा to_fc_पूर्णांकernal(पंचांगpl)	container_of(पंचांगpl, काष्ठा fc_पूर्णांकernal, t)

अटल पूर्णांक fc_target_setup(काष्ठा transport_container *tc, काष्ठा device *dev,
			   काष्ठा device *cdev)
अणु
	काष्ठा scsi_target *starget = to_scsi_target(dev);
	काष्ठा fc_rport *rport = starget_to_rport(starget);

	/*
	 * अगर parent is remote port, use values from remote port.
	 * Otherwise, this host uses the fc_transport, but not the
	 * remote port पूर्णांकerface. As such, initialize to known non-values.
	 */
	अगर (rport) अणु
		fc_starget_node_name(starget) = rport->node_name;
		fc_starget_port_name(starget) = rport->port_name;
		fc_starget_port_id(starget) = rport->port_id;
	पूर्ण अन्यथा अणु
		fc_starget_node_name(starget) = -1;
		fc_starget_port_name(starget) = -1;
		fc_starget_port_id(starget) = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल DECLARE_TRANSPORT_CLASS(fc_transport_class,
			       "fc_transport",
			       fc_target_setup,
			       शून्य,
			       शून्य);

अटल पूर्णांक fc_host_setup(काष्ठा transport_container *tc, काष्ठा device *dev,
			 काष्ठा device *cdev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);

	/*
	 * Set शेष values easily detected by the midlayer as
	 * failure हालs.  The scsi lldd is responsible क्रम initializing
	 * all transport attributes to valid values per host.
	 */
	fc_host->node_name = -1;
	fc_host->port_name = -1;
	fc_host->permanent_port_name = -1;
	fc_host->supported_classes = FC_COS_UNSPECIFIED;
	स_रखो(fc_host->supported_fc4s, 0,
		माप(fc_host->supported_fc4s));
	fc_host->supported_speeds = FC_PORTSPEED_UNKNOWN;
	fc_host->maxframe_size = -1;
	fc_host->max_npiv_vports = 0;
	स_रखो(fc_host->serial_number, 0,
		माप(fc_host->serial_number));
	स_रखो(fc_host->manufacturer, 0,
		माप(fc_host->manufacturer));
	स_रखो(fc_host->model, 0,
		माप(fc_host->model));
	स_रखो(fc_host->model_description, 0,
		माप(fc_host->model_description));
	स_रखो(fc_host->hardware_version, 0,
		माप(fc_host->hardware_version));
	स_रखो(fc_host->driver_version, 0,
		माप(fc_host->driver_version));
	स_रखो(fc_host->firmware_version, 0,
		माप(fc_host->firmware_version));
	स_रखो(fc_host->optionrom_version, 0,
		माप(fc_host->optionrom_version));

	fc_host->port_id = -1;
	fc_host->port_type = FC_PORTTYPE_UNKNOWN;
	fc_host->port_state = FC_PORTSTATE_UNKNOWN;
	स_रखो(fc_host->active_fc4s, 0,
		माप(fc_host->active_fc4s));
	fc_host->speed = FC_PORTSPEED_UNKNOWN;
	fc_host->fabric_name = -1;
	स_रखो(fc_host->symbolic_name, 0, माप(fc_host->symbolic_name));
	स_रखो(fc_host->प्रणाली_hostname, 0, माप(fc_host->प्रणाली_hostname));
	स_रखो(&fc_host->fpin_stats, 0, माप(fc_host->fpin_stats));

	fc_host->tgtid_bind_type = FC_TGTID_BIND_BY_WWPN;

	INIT_LIST_HEAD(&fc_host->rports);
	INIT_LIST_HEAD(&fc_host->rport_bindings);
	INIT_LIST_HEAD(&fc_host->vports);
	fc_host->next_rport_number = 0;
	fc_host->next_target_id = 0;
	fc_host->next_vport_number = 0;
	fc_host->npiv_vports_inuse = 0;

	snम_लिखो(fc_host->work_q_name, माप(fc_host->work_q_name),
		 "fc_wq_%d", shost->host_no);
	fc_host->work_q = alloc_workqueue("%s", 0, 0, fc_host->work_q_name);
	अगर (!fc_host->work_q)
		वापस -ENOMEM;

	fc_host->dev_loss_पंचांगo = fc_dev_loss_पंचांगo;
	snम_लिखो(fc_host->devloss_work_q_name,
		 माप(fc_host->devloss_work_q_name),
		 "fc_dl_%d", shost->host_no);
	fc_host->devloss_work_q = alloc_workqueue("%s", 0, 0,
					fc_host->devloss_work_q_name);
	अगर (!fc_host->devloss_work_q) अणु
		destroy_workqueue(fc_host->work_q);
		fc_host->work_q = शून्य;
		वापस -ENOMEM;
	पूर्ण

	fc_bsg_hostadd(shost, fc_host);
	/* ignore any bsg add error - we just can't करो sgio */

	वापस 0;
पूर्ण

अटल पूर्णांक fc_host_हटाओ(काष्ठा transport_container *tc, काष्ठा device *dev,
			 काष्ठा device *cdev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);

	fc_bsg_हटाओ(fc_host->rqst_q);
	वापस 0;
पूर्ण

अटल DECLARE_TRANSPORT_CLASS(fc_host_class,
			       "fc_host",
			       fc_host_setup,
			       fc_host_हटाओ,
			       शून्य);

/*
 * Setup and Remove actions क्रम remote ports are handled
 * in the service functions below.
 */
अटल DECLARE_TRANSPORT_CLASS(fc_rport_class,
			       "fc_remote_ports",
			       शून्य,
			       शून्य,
			       शून्य);

/*
 * Setup and Remove actions क्रम भव ports are handled
 * in the service functions below.
 */
अटल DECLARE_TRANSPORT_CLASS(fc_vport_class,
			       "fc_vports",
			       शून्य,
			       शून्य,
			       शून्य);

/*
 * Netlink Infraकाष्ठाure
 */

अटल atomic_t fc_event_seq;

/**
 * fc_get_event_number - Obtain the next sequential FC event number
 *
 * Notes:
 *   We could have अंतरभूतd this, but it would have required fc_event_seq to
 *   be exposed. For now, live with the subroutine call.
 *   Atomic used to aव्योम lock/unlock...
 */
u32
fc_get_event_number(व्योम)
अणु
	वापस atomic_add_वापस(1, &fc_event_seq);
पूर्ण
EXPORT_SYMBOL(fc_get_event_number);

/**
 * fc_host_post_fc_event - routine to करो the work of posting an event
 *                      on an fc_host.
 * @shost:		host the event occurred on
 * @event_number:	fc event number obtained from get_fc_event_number()
 * @event_code:		fc_host event being posted
 * @data_len:		amount, in bytes, of event data
 * @data_buf:		poपूर्णांकer to event data
 * @venकरोr_id:          value क्रम Venकरोr id
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
व्योम
fc_host_post_fc_event(काष्ठा Scsi_Host *shost, u32 event_number,
		क्रमागत fc_host_event_code event_code,
		u32 data_len, अक्षर *data_buf, u64 venकरोr_id)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nlmsghdr	*nlh;
	काष्ठा fc_nl_event *event;
	स्थिर अक्षर *name;
	u32 len;
	पूर्णांक err;

	अगर (!data_buf || data_len < 4)
		data_len = 0;

	अगर (!scsi_nl_sock) अणु
		err = -ENOENT;
		जाओ send_fail;
	पूर्ण

	len = FC_NL_MSGALIGN(माप(*event) + data_len);

	skb = nlmsg_new(len, GFP_KERNEL);
	अगर (!skb) अणु
		err = -ENOBUFS;
		जाओ send_fail;
	पूर्ण

	nlh = nlmsg_put(skb, 0, 0, SCSI_TRANSPORT_MSG, len, 0);
	अगर (!nlh) अणु
		err = -ENOBUFS;
		जाओ send_fail_skb;
	पूर्ण
	event = nlmsg_data(nlh);

	INIT_SCSI_NL_HDR(&event->snlh, SCSI_NL_TRANSPORT_FC,
				FC_NL_ASYNC_EVENT, len);
	event->seconds = kसमय_get_real_seconds();
	event->venकरोr_id = venकरोr_id;
	event->host_no = shost->host_no;
	event->event_datalen = data_len;	/* bytes */
	event->event_num = event_number;
	event->event_code = event_code;
	अगर (data_len)
		स_नकल(&event->event_data, data_buf, data_len);

	nlmsg_multicast(scsi_nl_sock, skb, 0, SCSI_NL_GRP_FC_EVENTS,
			GFP_KERNEL);
	वापस;

send_fail_skb:
	kमुक्त_skb(skb);
send_fail:
	name = get_fc_host_event_code_name(event_code);
	prपूर्णांकk(KERN_WARNING
		"%s: Dropped Event : host %d %s data 0x%08x - err %d\n",
		__func__, shost->host_no,
		(name) ? name : "<unknown>",
		(data_len) ? *((u32 *)data_buf) : 0xFFFFFFFF, err);
	वापस;
पूर्ण
EXPORT_SYMBOL(fc_host_post_fc_event);

/**
 * fc_host_post_event - called to post an even on an fc_host.
 * @shost:		host the event occurred on
 * @event_number:	fc event number obtained from get_fc_event_number()
 * @event_code:		fc_host event being posted
 * @event_data:		32bits of data क्रम the event being posted
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
व्योम
fc_host_post_event(काष्ठा Scsi_Host *shost, u32 event_number,
		क्रमागत fc_host_event_code event_code, u32 event_data)
अणु
	fc_host_post_fc_event(shost, event_number, event_code,
		(u32)माप(u32), (अक्षर *)&event_data, 0);
पूर्ण
EXPORT_SYMBOL(fc_host_post_event);


/**
 * fc_host_post_venकरोr_event - called to post a venकरोr unique event
 *                      on an fc_host
 * @shost:		host the event occurred on
 * @event_number:	fc event number obtained from get_fc_event_number()
 * @data_len:		amount, in bytes, of venकरोr unique data
 * @data_buf:		poपूर्णांकer to venकरोr unique data
 * @venकरोr_id:          Venकरोr id
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
व्योम
fc_host_post_venकरोr_event(काष्ठा Scsi_Host *shost, u32 event_number,
		u32 data_len, अक्षर * data_buf, u64 venकरोr_id)
अणु
	fc_host_post_fc_event(shost, event_number, FCH_EVT_VENDOR_UNIQUE,
		data_len, data_buf, venकरोr_id);
पूर्ण
EXPORT_SYMBOL(fc_host_post_venकरोr_event);

/**
 * fc_find_rport_by_wwpn - find the fc_rport poपूर्णांकer क्रम a given wwpn
 * @shost:		host the fc_rport is associated with
 * @wwpn:		wwpn of the fc_rport device
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
काष्ठा fc_rport *
fc_find_rport_by_wwpn(काष्ठा Scsi_Host *shost, u64 wwpn)
अणु
	काष्ठा fc_rport *rport;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);

	list_क्रम_each_entry(rport, &fc_host_rports(shost), peers) अणु
		अगर (rport->port_state != FC_PORTSTATE_ONLINE)
			जारी;

		अगर (rport->port_name == wwpn) अणु
			spin_unlock_irqrestore(shost->host_lock, flags);
			वापस rport;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(fc_find_rport_by_wwpn);

अटल व्योम
fc_li_stats_update(काष्ठा fc_fn_li_desc *li_desc,
		   काष्ठा fc_fpin_stats *stats)
अणु
	stats->li += be32_to_cpu(li_desc->event_count);
	चयन (be16_to_cpu(li_desc->event_type)) अणु
	हाल FPIN_LI_UNKNOWN:
		stats->li_failure_unknown +=
		    be32_to_cpu(li_desc->event_count);
		अवरोध;
	हाल FPIN_LI_LINK_FAILURE:
		stats->li_link_failure_count +=
		    be32_to_cpu(li_desc->event_count);
		अवरोध;
	हाल FPIN_LI_LOSS_OF_SYNC:
		stats->li_loss_of_sync_count +=
		    be32_to_cpu(li_desc->event_count);
		अवरोध;
	हाल FPIN_LI_LOSS_OF_SIG:
		stats->li_loss_of_संकेतs_count +=
		    be32_to_cpu(li_desc->event_count);
		अवरोध;
	हाल FPIN_LI_PRIM_SEQ_ERR:
		stats->li_prim_seq_err_count +=
		    be32_to_cpu(li_desc->event_count);
		अवरोध;
	हाल FPIN_LI_INVALID_TX_WD:
		stats->li_invalid_tx_word_count +=
		    be32_to_cpu(li_desc->event_count);
		अवरोध;
	हाल FPIN_LI_INVALID_CRC:
		stats->li_invalid_crc_count +=
		    be32_to_cpu(li_desc->event_count);
		अवरोध;
	हाल FPIN_LI_DEVICE_SPEC:
		stats->li_device_specअगरic +=
		    be32_to_cpu(li_desc->event_count);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
fc_delivery_stats_update(u32 reason_code, काष्ठा fc_fpin_stats *stats)
अणु
	stats->dn++;
	चयन (reason_code) अणु
	हाल FPIN_DELI_UNKNOWN:
		stats->dn_unknown++;
		अवरोध;
	हाल FPIN_DELI_TIMEOUT:
		stats->dn_समयout++;
		अवरोध;
	हाल FPIN_DELI_UNABLE_TO_ROUTE:
		stats->dn_unable_to_route++;
		अवरोध;
	हाल FPIN_DELI_DEVICE_SPEC:
		stats->dn_device_specअगरic++;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
fc_cn_stats_update(u16 event_type, काष्ठा fc_fpin_stats *stats)
अणु
	stats->cn++;
	चयन (event_type) अणु
	हाल FPIN_CONGN_CLEAR:
		stats->cn_clear++;
		अवरोध;
	हाल FPIN_CONGN_LOST_CREDIT:
		stats->cn_lost_credit++;
		अवरोध;
	हाल FPIN_CONGN_CREDIT_STALL:
		stats->cn_credit_stall++;
		अवरोध;
	हाल FPIN_CONGN_OVERSUBSCRIPTION:
		stats->cn_oversubscription++;
		अवरोध;
	हाल FPIN_CONGN_DEVICE_SPEC:
		stats->cn_device_specअगरic++;
	पूर्ण
पूर्ण

/*
 * fc_fpin_li_stats_update - routine to update Link Integrity
 * event statistics.
 * @shost:		host the FPIN was received on
 * @tlv:		poपूर्णांकer to link पूर्णांकegrity descriptor
 *
 */
अटल व्योम
fc_fpin_li_stats_update(काष्ठा Scsi_Host *shost, काष्ठा fc_tlv_desc *tlv)
अणु
	u8 i;
	काष्ठा fc_rport *rport = शून्य;
	काष्ठा fc_rport *attach_rport = शून्य;
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	काष्ठा fc_fn_li_desc *li_desc = (काष्ठा fc_fn_li_desc *)tlv;
	u64 wwpn;

	rport = fc_find_rport_by_wwpn(shost,
				      be64_to_cpu(li_desc->attached_wwpn));
	अगर (rport &&
	    (rport->roles & FC_PORT_ROLE_FCP_TARGET ||
	     rport->roles & FC_PORT_ROLE_NVME_TARGET)) अणु
		attach_rport = rport;
		fc_li_stats_update(li_desc, &attach_rport->fpin_stats);
	पूर्ण

	अगर (be32_to_cpu(li_desc->pname_count) > 0) अणु
		क्रम (i = 0;
		    i < be32_to_cpu(li_desc->pname_count);
		    i++) अणु
			wwpn = be64_to_cpu(li_desc->pname_list[i]);
			rport = fc_find_rport_by_wwpn(shost, wwpn);
			अगर (rport &&
			    (rport->roles & FC_PORT_ROLE_FCP_TARGET ||
			    rport->roles & FC_PORT_ROLE_NVME_TARGET)) अणु
				अगर (rport == attach_rport)
					जारी;
				fc_li_stats_update(li_desc,
						   &rport->fpin_stats);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (fc_host->port_name == be64_to_cpu(li_desc->attached_wwpn))
		fc_li_stats_update(li_desc, &fc_host->fpin_stats);
पूर्ण

/*
 * fc_fpin_delivery_stats_update - routine to update Delivery Notअगरication
 * event statistics.
 * @shost:		host the FPIN was received on
 * @tlv:		poपूर्णांकer to delivery descriptor
 *
 */
अटल व्योम
fc_fpin_delivery_stats_update(काष्ठा Scsi_Host *shost,
			      काष्ठा fc_tlv_desc *tlv)
अणु
	काष्ठा fc_rport *rport = शून्य;
	काष्ठा fc_rport *attach_rport = शून्य;
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	काष्ठा fc_fn_deli_desc *dn_desc = (काष्ठा fc_fn_deli_desc *)tlv;
	u32 reason_code = be32_to_cpu(dn_desc->deli_reason_code);

	rport = fc_find_rport_by_wwpn(shost,
				      be64_to_cpu(dn_desc->attached_wwpn));
	अगर (rport &&
	    (rport->roles & FC_PORT_ROLE_FCP_TARGET ||
	     rport->roles & FC_PORT_ROLE_NVME_TARGET)) अणु
		attach_rport = rport;
		fc_delivery_stats_update(reason_code,
					 &attach_rport->fpin_stats);
	पूर्ण

	अगर (fc_host->port_name == be64_to_cpu(dn_desc->attached_wwpn))
		fc_delivery_stats_update(reason_code, &fc_host->fpin_stats);
पूर्ण

/*
 * fc_fpin_peer_congn_stats_update - routine to update Peer Congestion
 * event statistics.
 * @shost:		host the FPIN was received on
 * @tlv:		poपूर्णांकer to peer congestion descriptor
 *
 */
अटल व्योम
fc_fpin_peer_congn_stats_update(काष्ठा Scsi_Host *shost,
				काष्ठा fc_tlv_desc *tlv)
अणु
	u8 i;
	काष्ठा fc_rport *rport = शून्य;
	काष्ठा fc_rport *attach_rport = शून्य;
	काष्ठा fc_fn_peer_congn_desc *pc_desc =
	    (काष्ठा fc_fn_peer_congn_desc *)tlv;
	u16 event_type = be16_to_cpu(pc_desc->event_type);
	u64 wwpn;

	rport = fc_find_rport_by_wwpn(shost,
				      be64_to_cpu(pc_desc->attached_wwpn));
	अगर (rport &&
	    (rport->roles & FC_PORT_ROLE_FCP_TARGET ||
	     rport->roles & FC_PORT_ROLE_NVME_TARGET)) अणु
		attach_rport = rport;
		fc_cn_stats_update(event_type, &attach_rport->fpin_stats);
	पूर्ण

	अगर (be32_to_cpu(pc_desc->pname_count) > 0) अणु
		क्रम (i = 0;
		    i < be32_to_cpu(pc_desc->pname_count);
		    i++) अणु
			wwpn = be64_to_cpu(pc_desc->pname_list[i]);
			rport = fc_find_rport_by_wwpn(shost, wwpn);
			अगर (rport &&
			    (rport->roles & FC_PORT_ROLE_FCP_TARGET ||
			     rport->roles & FC_PORT_ROLE_NVME_TARGET)) अणु
				अगर (rport == attach_rport)
					जारी;
				fc_cn_stats_update(event_type,
						   &rport->fpin_stats);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * fc_fpin_congn_stats_update - routine to update Congestion
 * event statistics.
 * @shost:		host the FPIN was received on
 * @tlv:		poपूर्णांकer to congestion descriptor
 *
 */
अटल व्योम
fc_fpin_congn_stats_update(काष्ठा Scsi_Host *shost,
			   काष्ठा fc_tlv_desc *tlv)
अणु
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	काष्ठा fc_fn_congn_desc *congn = (काष्ठा fc_fn_congn_desc *)tlv;

	fc_cn_stats_update(be16_to_cpu(congn->event_type),
			   &fc_host->fpin_stats);
पूर्ण

/**
 * fc_host_fpin_rcv - routine to process a received FPIN.
 * @shost:		host the FPIN was received on
 * @fpin_len:		length of FPIN payload, in bytes
 * @fpin_buf:		poपूर्णांकer to FPIN payload
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
व्योम
fc_host_fpin_rcv(काष्ठा Scsi_Host *shost, u32 fpin_len, अक्षर *fpin_buf)
अणु
	काष्ठा fc_els_fpin *fpin = (काष्ठा fc_els_fpin *)fpin_buf;
	काष्ठा fc_tlv_desc *tlv;
	u32 desc_cnt = 0, bytes_reमुख्य;
	u32 dtag;

	/* Update Statistics */
	tlv = (काष्ठा fc_tlv_desc *)&fpin->fpin_desc[0];
	bytes_reमुख्य = fpin_len - दुरत्व(काष्ठा fc_els_fpin, fpin_desc);
	bytes_reमुख्य = min_t(u32, bytes_reमुख्य, be32_to_cpu(fpin->desc_len));

	जबतक (bytes_reमुख्य >= FC_TLV_DESC_HDR_SZ &&
	       bytes_reमुख्य >= FC_TLV_DESC_SZ_FROM_LENGTH(tlv)) अणु
		dtag = be32_to_cpu(tlv->desc_tag);
		चयन (dtag) अणु
		हाल ELS_DTAG_LNK_INTEGRITY:
			fc_fpin_li_stats_update(shost, tlv);
			अवरोध;
		हाल ELS_DTAG_DELIVERY:
			fc_fpin_delivery_stats_update(shost, tlv);
			अवरोध;
		हाल ELS_DTAG_PEER_CONGEST:
			fc_fpin_peer_congn_stats_update(shost, tlv);
			अवरोध;
		हाल ELS_DTAG_CONGESTION:
			fc_fpin_congn_stats_update(shost, tlv);
		पूर्ण

		desc_cnt++;
		bytes_reमुख्य -= FC_TLV_DESC_SZ_FROM_LENGTH(tlv);
		tlv = fc_tlv_next_desc(tlv);
	पूर्ण

	fc_host_post_fc_event(shost, fc_get_event_number(),
				FCH_EVT_LINK_FPIN, fpin_len, fpin_buf, 0);
पूर्ण
EXPORT_SYMBOL(fc_host_fpin_rcv);


अटल __init पूर्णांक fc_transport_init(व्योम)
अणु
	पूर्णांक error;

	atomic_set(&fc_event_seq, 0);

	error = transport_class_रेजिस्टर(&fc_host_class);
	अगर (error)
		वापस error;
	error = transport_class_रेजिस्टर(&fc_vport_class);
	अगर (error)
		जाओ unreg_host_class;
	error = transport_class_रेजिस्टर(&fc_rport_class);
	अगर (error)
		जाओ unreg_vport_class;
	error = transport_class_रेजिस्टर(&fc_transport_class);
	अगर (error)
		जाओ unreg_rport_class;
	वापस 0;

unreg_rport_class:
	transport_class_unरेजिस्टर(&fc_rport_class);
unreg_vport_class:
	transport_class_unरेजिस्टर(&fc_vport_class);
unreg_host_class:
	transport_class_unरेजिस्टर(&fc_host_class);
	वापस error;
पूर्ण

अटल व्योम __निकास fc_transport_निकास(व्योम)
अणु
	transport_class_unरेजिस्टर(&fc_transport_class);
	transport_class_unरेजिस्टर(&fc_rport_class);
	transport_class_unरेजिस्टर(&fc_host_class);
	transport_class_unरेजिस्टर(&fc_vport_class);
पूर्ण

/*
 * FC Remote Port Attribute Management
 */

#घोषणा fc_rport_show_function(field, क्रमmat_string, sz, cast)		\
अटल sमाप_प्रकार								\
show_fc_rport_##field (काष्ठा device *dev, 				\
		       काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);		\
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);		\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	अगर ((i->f->get_rport_##field) &&				\
	    !((rport->port_state == FC_PORTSTATE_BLOCKED) ||		\
	      (rport->port_state == FC_PORTSTATE_DELETED) ||		\
	      (rport->port_state == FC_PORTSTATE_NOTPRESENT)))		\
		i->f->get_rport_##field(rport);				\
	वापस snम_लिखो(buf, sz, क्रमmat_string, cast rport->field); 	\
पूर्ण

#घोषणा fc_rport_store_function(field)					\
अटल sमाप_प्रकार								\
store_fc_rport_##field(काष्ठा device *dev,				\
		       काष्ठा device_attribute *attr,			\
		       स्थिर अक्षर *buf,	माप_प्रकार count)			\
अणु									\
	पूर्णांक val;							\
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);		\
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);		\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	अक्षर *cp;							\
	अगर ((rport->port_state == FC_PORTSTATE_BLOCKED) ||		\
	    (rport->port_state == FC_PORTSTATE_DELETED) ||		\
	    (rport->port_state == FC_PORTSTATE_NOTPRESENT))		\
		वापस -EBUSY;						\
	val = simple_म_से_अदीर्घ(buf, &cp, 0);				\
	अगर (*cp && (*cp != '\n'))					\
		वापस -EINVAL;						\
	i->f->set_rport_##field(rport, val);				\
	वापस count;							\
पूर्ण

#घोषणा fc_rport_rd_attr(field, क्रमmat_string, sz)			\
	fc_rport_show_function(field, क्रमmat_string, sz, )		\
अटल FC_DEVICE_ATTR(rport, field, S_IRUGO,			\
			 show_fc_rport_##field, शून्य)

#घोषणा fc_rport_rd_attr_cast(field, क्रमmat_string, sz, cast)		\
	fc_rport_show_function(field, क्रमmat_string, sz, (cast))	\
अटल FC_DEVICE_ATTR(rport, field, S_IRUGO,			\
			  show_fc_rport_##field, शून्य)

#घोषणा fc_rport_rw_attr(field, क्रमmat_string, sz)			\
	fc_rport_show_function(field, क्रमmat_string, sz, )		\
	fc_rport_store_function(field)					\
अटल FC_DEVICE_ATTR(rport, field, S_IRUGO | S_IWUSR,		\
			show_fc_rport_##field,				\
			store_fc_rport_##field)


#घोषणा fc_निजी_rport_show_function(field, क्रमmat_string, sz, cast)	\
अटल sमाप_प्रकार								\
show_fc_rport_##field (काष्ठा device *dev, 				\
		       काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);		\
	वापस snम_लिखो(buf, sz, क्रमmat_string, cast rport->field); 	\
पूर्ण

#घोषणा fc_निजी_rport_rd_attr(field, क्रमmat_string, sz)		\
	fc_निजी_rport_show_function(field, क्रमmat_string, sz, )	\
अटल FC_DEVICE_ATTR(rport, field, S_IRUGO,			\
			 show_fc_rport_##field, शून्य)

#घोषणा fc_निजी_rport_rd_attr_cast(field, क्रमmat_string, sz, cast)	\
	fc_निजी_rport_show_function(field, क्रमmat_string, sz, (cast)) \
अटल FC_DEVICE_ATTR(rport, field, S_IRUGO,			\
			  show_fc_rport_##field, शून्य)


#घोषणा fc_निजी_rport_rd_क्रमागत_attr(title, maxlen)			\
अटल sमाप_प्रकार								\
show_fc_rport_##title (काष्ठा device *dev,				\
		       काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);		\
	स्थिर अक्षर *name;						\
	name = get_fc_##title##_name(rport->title);			\
	अगर (!name)							\
		वापस -EINVAL;						\
	वापस snम_लिखो(buf, maxlen, "%s\n", name);			\
पूर्ण									\
अटल FC_DEVICE_ATTR(rport, title, S_IRUGO,			\
			show_fc_rport_##title, शून्य)


#घोषणा SETUP_RPORT_ATTRIBUTE_RD(field)					\
	i->निजी_rport_attrs[count] = device_attr_rport_##field; \
	i->निजी_rport_attrs[count].attr.mode = S_IRUGO;		\
	i->निजी_rport_attrs[count].store = शून्य;			\
	i->rport_attrs[count] = &i->निजी_rport_attrs[count];		\
	अगर (i->f->show_rport_##field)					\
		count++

#घोषणा SETUP_PRIVATE_RPORT_ATTRIBUTE_RD(field)				\
	i->निजी_rport_attrs[count] = device_attr_rport_##field; \
	i->निजी_rport_attrs[count].attr.mode = S_IRUGO;		\
	i->निजी_rport_attrs[count].store = शून्य;			\
	i->rport_attrs[count] = &i->निजी_rport_attrs[count];		\
	count++

#घोषणा SETUP_RPORT_ATTRIBUTE_RW(field)					\
	i->निजी_rport_attrs[count] = device_attr_rport_##field; \
	अगर (!i->f->set_rport_##field) अणु					\
		i->निजी_rport_attrs[count].attr.mode = S_IRUGO;	\
		i->निजी_rport_attrs[count].store = शून्य;		\
	पूर्ण								\
	i->rport_attrs[count] = &i->निजी_rport_attrs[count];		\
	अगर (i->f->show_rport_##field)					\
		count++

#घोषणा SETUP_PRIVATE_RPORT_ATTRIBUTE_RW(field)				\
अणु									\
	i->निजी_rport_attrs[count] = device_attr_rport_##field; \
	i->rport_attrs[count] = &i->निजी_rport_attrs[count];		\
	count++;							\
पूर्ण


/* The FC Transport Remote Port Attributes: */

/* Fixed Remote Port Attributes */

fc_निजी_rport_rd_attr(maxframe_size, "%u bytes\n", 20);

अटल sमाप_प्रकार
show_fc_rport_supported_classes (काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);
	अगर (rport->supported_classes == FC_COS_UNSPECIFIED)
		वापस snम_लिखो(buf, 20, "unspecified\n");
	वापस get_fc_cos_names(rport->supported_classes, buf);
पूर्ण
अटल FC_DEVICE_ATTR(rport, supported_classes, S_IRUGO,
		show_fc_rport_supported_classes, शून्य);

/* Dynamic Remote Port Attributes */

/*
 * dev_loss_पंचांगo attribute
 */
अटल पूर्णांक fc_str_to_dev_loss(स्थिर अक्षर *buf, अचिन्हित दीर्घ *val)
अणु
	अक्षर *cp;

	*val = simple_म_से_अदीर्घ(buf, &cp, 0);
	अगर (*cp && (*cp != '\n'))
		वापस -EINVAL;
	/*
	 * Check क्रम overflow; dev_loss_पंचांगo is u32
	 */
	अगर (*val > अच_पूर्णांक_उच्च)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक fc_rport_set_dev_loss_पंचांगo(काष्ठा fc_rport *rport,
				     अचिन्हित दीर्घ val)
अणु
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);

	अगर ((rport->port_state == FC_PORTSTATE_BLOCKED) ||
	    (rport->port_state == FC_PORTSTATE_DELETED) ||
	    (rport->port_state == FC_PORTSTATE_NOTPRESENT))
		वापस -EBUSY;
	/*
	 * Check क्रम overflow; dev_loss_पंचांगo is u32
	 */
	अगर (val > अच_पूर्णांक_उच्च)
		वापस -EINVAL;

	/*
	 * If fast_io_fail is off we have to cap
	 * dev_loss_पंचांगo at SCSI_DEVICE_BLOCK_MAX_TIMEOUT
	 */
	अगर (rport->fast_io_fail_पंचांगo == -1 &&
	    val > SCSI_DEVICE_BLOCK_MAX_TIMEOUT)
		वापस -EINVAL;

	i->f->set_rport_dev_loss_पंचांगo(rport, val);
	वापस 0;
पूर्ण

fc_rport_show_function(dev_loss_पंचांगo, "%d\n", 20, )
अटल sमाप_प्रकार
store_fc_rport_dev_loss_पंचांगo(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	rc = fc_str_to_dev_loss(buf, &val);
	अगर (rc)
		वापस rc;

	rc = fc_rport_set_dev_loss_पंचांगo(rport, val);
	अगर (rc)
		वापस rc;
	वापस count;
पूर्ण
अटल FC_DEVICE_ATTR(rport, dev_loss_पंचांगo, S_IRUGO | S_IWUSR,
		show_fc_rport_dev_loss_पंचांगo, store_fc_rport_dev_loss_पंचांगo);


/* Private Remote Port Attributes */

fc_निजी_rport_rd_attr_cast(node_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fc_निजी_rport_rd_attr_cast(port_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fc_निजी_rport_rd_attr(port_id, "0x%06x\n", 20);

अटल sमाप_प्रकार
show_fc_rport_roles (काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);

	/* identअगरy any roles that are port_id specअगरic */
	अगर ((rport->port_id != -1) &&
	    (rport->port_id & FC_WELLKNOWN_PORTID_MASK) ==
					FC_WELLKNOWN_PORTID_MASK) अणु
		चयन (rport->port_id & FC_WELLKNOWN_ROLE_MASK) अणु
		हाल FC_FPORT_PORTID:
			वापस snम_लिखो(buf, 30, "Fabric Port\n");
		हाल FC_FABCTLR_PORTID:
			वापस snम_लिखो(buf, 30, "Fabric Controller\n");
		हाल FC_सूचीSRVR_PORTID:
			वापस snम_लिखो(buf, 30, "Directory Server\n");
		हाल FC_TIMESRVR_PORTID:
			वापस snम_लिखो(buf, 30, "Time Server\n");
		हाल FC_MGMTSRVR_PORTID:
			वापस snम_लिखो(buf, 30, "Management Server\n");
		शेष:
			वापस snम_लिखो(buf, 30, "Unknown Fabric Entity\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rport->roles == FC_PORT_ROLE_UNKNOWN)
			वापस snम_लिखो(buf, 20, "unknown\n");
		वापस get_fc_port_roles_names(rport->roles, buf);
	पूर्ण
पूर्ण
अटल FC_DEVICE_ATTR(rport, roles, S_IRUGO,
		show_fc_rport_roles, शून्य);

अटल sमाप_प्रकार fc_rport_set_marginal_state(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);
	क्रमागत fc_port_state port_state;
	पूर्णांक ret = 0;

	ret = get_fc_port_state_match(buf, &port_state);
	अगर (ret)
		वापस -EINVAL;
	अगर (port_state == FC_PORTSTATE_MARGINAL) अणु
		/*
		 * Change the state to Marginal only अगर the
		 * current rport state is Online
		 * Allow only Online->Marginal
		 */
		अगर (rport->port_state == FC_PORTSTATE_ONLINE)
			rport->port_state = port_state;
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (port_state == FC_PORTSTATE_ONLINE) अणु
		/*
		 * Change the state to Online only अगर the
		 * current rport state is Marginal
		 * Allow only Marginal->Online
		 */
		अगर (rport->port_state == FC_PORTSTATE_MARGINAL)
			rport->port_state = port_state;
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस -EINVAL;
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_fc_rport_port_state(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *name;
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);

	name = get_fc_port_state_name(rport->port_state);
	अगर (!name)
		वापस -EINVAL;

	वापस snम_लिखो(buf, 20, "%s\n", name);
पूर्ण

अटल FC_DEVICE_ATTR(rport, port_state, 0444 | 0200,
			show_fc_rport_port_state, fc_rport_set_marginal_state);

fc_निजी_rport_rd_attr(scsi_target_id, "%d\n", 20);

/*
 * fast_io_fail_पंचांगo attribute
 */
अटल sमाप_प्रकार
show_fc_rport_fast_io_fail_पंचांगo (काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);

	अगर (rport->fast_io_fail_पंचांगo == -1)
		वापस snम_लिखो(buf, 5, "off\n");
	वापस snम_लिखो(buf, 20, "%d\n", rport->fast_io_fail_पंचांगo);
पूर्ण

अटल sमाप_प्रकार
store_fc_rport_fast_io_fail_पंचांगo(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	पूर्णांक val;
	अक्षर *cp;
	काष्ठा fc_rport *rport = transport_class_to_rport(dev);

	अगर ((rport->port_state == FC_PORTSTATE_BLOCKED) ||
	    (rport->port_state == FC_PORTSTATE_DELETED) ||
	    (rport->port_state == FC_PORTSTATE_NOTPRESENT))
		वापस -EBUSY;
	अगर (म_भेदन(buf, "off", 3) == 0)
		rport->fast_io_fail_पंचांगo = -1;
	अन्यथा अणु
		val = simple_म_से_अदीर्घ(buf, &cp, 0);
		अगर ((*cp && (*cp != '\n')) || (val < 0))
			वापस -EINVAL;
		/*
		 * Cap fast_io_fail by dev_loss_पंचांगo or
		 * SCSI_DEVICE_BLOCK_MAX_TIMEOUT.
		 */
		अगर ((val >= rport->dev_loss_पंचांगo) ||
		    (val > SCSI_DEVICE_BLOCK_MAX_TIMEOUT))
			वापस -EINVAL;

		rport->fast_io_fail_पंचांगo = val;
	पूर्ण
	वापस count;
पूर्ण
अटल FC_DEVICE_ATTR(rport, fast_io_fail_पंचांगo, S_IRUGO | S_IWUSR,
	show_fc_rport_fast_io_fail_पंचांगo, store_fc_rport_fast_io_fail_पंचांगo);

#घोषणा fc_rport_fpin_statistic(name)					\
अटल sमाप_प्रकार fc_rport_fpinstat_##name(काष्ठा device *cd,		\
				  काष्ठा device_attribute *attr,	\
				  अक्षर *buf)				\
अणु									\
	काष्ठा fc_rport *rport = transport_class_to_rport(cd);		\
									\
	वापस snम_लिखो(buf, 20, "0x%llx\n", rport->fpin_stats.name);	\
पूर्ण									\
अटल FC_DEVICE_ATTR(rport, fpin_##name, 0444, fc_rport_fpinstat_##name, शून्य)

fc_rport_fpin_statistic(dn);
fc_rport_fpin_statistic(dn_unknown);
fc_rport_fpin_statistic(dn_समयout);
fc_rport_fpin_statistic(dn_unable_to_route);
fc_rport_fpin_statistic(dn_device_specअगरic);
fc_rport_fpin_statistic(cn);
fc_rport_fpin_statistic(cn_clear);
fc_rport_fpin_statistic(cn_lost_credit);
fc_rport_fpin_statistic(cn_credit_stall);
fc_rport_fpin_statistic(cn_oversubscription);
fc_rport_fpin_statistic(cn_device_specअगरic);
fc_rport_fpin_statistic(li);
fc_rport_fpin_statistic(li_failure_unknown);
fc_rport_fpin_statistic(li_link_failure_count);
fc_rport_fpin_statistic(li_loss_of_sync_count);
fc_rport_fpin_statistic(li_loss_of_संकेतs_count);
fc_rport_fpin_statistic(li_prim_seq_err_count);
fc_rport_fpin_statistic(li_invalid_tx_word_count);
fc_rport_fpin_statistic(li_invalid_crc_count);
fc_rport_fpin_statistic(li_device_specअगरic);

अटल काष्ठा attribute *fc_rport_statistics_attrs[] = अणु
	&device_attr_rport_fpin_dn.attr,
	&device_attr_rport_fpin_dn_unknown.attr,
	&device_attr_rport_fpin_dn_समयout.attr,
	&device_attr_rport_fpin_dn_unable_to_route.attr,
	&device_attr_rport_fpin_dn_device_specअगरic.attr,
	&device_attr_rport_fpin_li.attr,
	&device_attr_rport_fpin_li_failure_unknown.attr,
	&device_attr_rport_fpin_li_link_failure_count.attr,
	&device_attr_rport_fpin_li_loss_of_sync_count.attr,
	&device_attr_rport_fpin_li_loss_of_संकेतs_count.attr,
	&device_attr_rport_fpin_li_prim_seq_err_count.attr,
	&device_attr_rport_fpin_li_invalid_tx_word_count.attr,
	&device_attr_rport_fpin_li_invalid_crc_count.attr,
	&device_attr_rport_fpin_li_device_specअगरic.attr,
	&device_attr_rport_fpin_cn.attr,
	&device_attr_rport_fpin_cn_clear.attr,
	&device_attr_rport_fpin_cn_lost_credit.attr,
	&device_attr_rport_fpin_cn_credit_stall.attr,
	&device_attr_rport_fpin_cn_oversubscription.attr,
	&device_attr_rport_fpin_cn_device_specअगरic.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group fc_rport_statistics_group = अणु
	.name = "statistics",
	.attrs = fc_rport_statistics_attrs,
पूर्ण;


/*
 * FC SCSI Target Attribute Management
 */

/*
 * Note: in the target show function we recognize when the remote
 *  port is in the hierarchy and करो not allow the driver to get
 *  involved in sysfs functions. The driver only माला_लो involved अगर
 *  it's the "old" style that doesn't use rports.
 */
#घोषणा fc_starget_show_function(field, क्रमmat_string, sz, cast)	\
अटल sमाप_प्रकार								\
show_fc_starget_##field (काष्ठा device *dev, 				\
			 काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा scsi_target *starget = transport_class_to_starget(dev);	\
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);	\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	काष्ठा fc_rport *rport = starget_to_rport(starget);		\
	अगर (rport)							\
		fc_starget_##field(starget) = rport->field;		\
	अन्यथा अगर (i->f->get_starget_##field)				\
		i->f->get_starget_##field(starget);			\
	वापस snम_लिखो(buf, sz, क्रमmat_string, 			\
		cast fc_starget_##field(starget)); 			\
पूर्ण

#घोषणा fc_starget_rd_attr(field, क्रमmat_string, sz)			\
	fc_starget_show_function(field, क्रमmat_string, sz, )		\
अटल FC_DEVICE_ATTR(starget, field, S_IRUGO,			\
			 show_fc_starget_##field, शून्य)

#घोषणा fc_starget_rd_attr_cast(field, क्रमmat_string, sz, cast)		\
	fc_starget_show_function(field, क्रमmat_string, sz, (cast))	\
अटल FC_DEVICE_ATTR(starget, field, S_IRUGO,			\
			  show_fc_starget_##field, शून्य)

#घोषणा SETUP_STARGET_ATTRIBUTE_RD(field)				\
	i->निजी_starget_attrs[count] = device_attr_starget_##field; \
	i->निजी_starget_attrs[count].attr.mode = S_IRUGO;		\
	i->निजी_starget_attrs[count].store = शून्य;			\
	i->starget_attrs[count] = &i->निजी_starget_attrs[count];	\
	अगर (i->f->show_starget_##field)					\
		count++

#घोषणा SETUP_STARGET_ATTRIBUTE_RW(field)				\
	i->निजी_starget_attrs[count] = device_attr_starget_##field; \
	अगर (!i->f->set_starget_##field) अणु				\
		i->निजी_starget_attrs[count].attr.mode = S_IRUGO;	\
		i->निजी_starget_attrs[count].store = शून्य;		\
	पूर्ण								\
	i->starget_attrs[count] = &i->निजी_starget_attrs[count];	\
	अगर (i->f->show_starget_##field)					\
		count++

/* The FC Transport SCSI Target Attributes: */
fc_starget_rd_attr_cast(node_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fc_starget_rd_attr_cast(port_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fc_starget_rd_attr(port_id, "0x%06x\n", 20);


/*
 * FC Virtual Port Attribute Management
 */

#घोषणा fc_vport_show_function(field, क्रमmat_string, sz, cast)		\
अटल sमाप_प्रकार								\
show_fc_vport_##field (काष्ठा device *dev, 				\
		       काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा fc_vport *vport = transport_class_to_vport(dev);		\
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);		\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	अगर ((i->f->get_vport_##field) &&				\
	    !(vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING)))	\
		i->f->get_vport_##field(vport);				\
	वापस snम_लिखो(buf, sz, क्रमmat_string, cast vport->field); 	\
पूर्ण

#घोषणा fc_vport_store_function(field)					\
अटल sमाप_प्रकार								\
store_fc_vport_##field(काष्ठा device *dev,				\
		       काष्ठा device_attribute *attr,			\
		       स्थिर अक्षर *buf,	माप_प्रकार count)			\
अणु									\
	पूर्णांक val;							\
	काष्ठा fc_vport *vport = transport_class_to_vport(dev);		\
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);		\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	अक्षर *cp;							\
	अगर (vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING))	\
		वापस -EBUSY;						\
	val = simple_म_से_अदीर्घ(buf, &cp, 0);				\
	अगर (*cp && (*cp != '\n'))					\
		वापस -EINVAL;						\
	i->f->set_vport_##field(vport, val);				\
	वापस count;							\
पूर्ण

#घोषणा fc_vport_store_str_function(field, slen)			\
अटल sमाप_प्रकार								\
store_fc_vport_##field(काष्ठा device *dev,				\
		       काष्ठा device_attribute *attr, 			\
		       स्थिर अक्षर *buf,	माप_प्रकार count)			\
अणु									\
	काष्ठा fc_vport *vport = transport_class_to_vport(dev);		\
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);		\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	अचिन्हित पूर्णांक cnt=count;						\
									\
	/* count may include a LF at end of string */			\
	अगर (buf[cnt-1] == '\n')						\
		cnt--;							\
	अगर (cnt > ((slen) - 1))						\
		वापस -EINVAL;						\
	स_नकल(vport->field, buf, cnt);					\
	i->f->set_vport_##field(vport);					\
	वापस count;							\
पूर्ण

#घोषणा fc_vport_rd_attr(field, क्रमmat_string, sz)			\
	fc_vport_show_function(field, क्रमmat_string, sz, )		\
अटल FC_DEVICE_ATTR(vport, field, S_IRUGO,			\
			 show_fc_vport_##field, शून्य)

#घोषणा fc_vport_rd_attr_cast(field, क्रमmat_string, sz, cast)		\
	fc_vport_show_function(field, क्रमmat_string, sz, (cast))	\
अटल FC_DEVICE_ATTR(vport, field, S_IRUGO,			\
			  show_fc_vport_##field, शून्य)

#घोषणा fc_vport_rw_attr(field, क्रमmat_string, sz)			\
	fc_vport_show_function(field, क्रमmat_string, sz, )		\
	fc_vport_store_function(field)					\
अटल FC_DEVICE_ATTR(vport, field, S_IRUGO | S_IWUSR,		\
			show_fc_vport_##field,				\
			store_fc_vport_##field)

#घोषणा fc_निजी_vport_show_function(field, क्रमmat_string, sz, cast)	\
अटल sमाप_प्रकार								\
show_fc_vport_##field (काष्ठा device *dev,				\
		       काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा fc_vport *vport = transport_class_to_vport(dev);		\
	वापस snम_लिखो(buf, sz, क्रमmat_string, cast vport->field); 	\
पूर्ण

#घोषणा fc_निजी_vport_store_u32_function(field)			\
अटल sमाप_प्रकार								\
store_fc_vport_##field(काष्ठा device *dev,				\
		       काष्ठा device_attribute *attr,			\
		       स्थिर अक्षर *buf,	माप_प्रकार count)			\
अणु									\
	u32 val;							\
	काष्ठा fc_vport *vport = transport_class_to_vport(dev);		\
	अक्षर *cp;							\
	अगर (vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING))		\
		वापस -EBUSY;						\
	val = simple_म_से_अदीर्घ(buf, &cp, 0);				\
	अगर (*cp && (*cp != '\n'))					\
		वापस -EINVAL;						\
	vport->field = val;						\
	वापस count;							\
पूर्ण


#घोषणा fc_निजी_vport_rd_attr(field, क्रमmat_string, sz)		\
	fc_निजी_vport_show_function(field, क्रमmat_string, sz, )	\
अटल FC_DEVICE_ATTR(vport, field, S_IRUGO,			\
			 show_fc_vport_##field, शून्य)

#घोषणा fc_निजी_vport_rd_attr_cast(field, क्रमmat_string, sz, cast)	\
	fc_निजी_vport_show_function(field, क्रमmat_string, sz, (cast)) \
अटल FC_DEVICE_ATTR(vport, field, S_IRUGO,			\
			  show_fc_vport_##field, शून्य)

#घोषणा fc_निजी_vport_rw_u32_attr(field, क्रमmat_string, sz)		\
	fc_निजी_vport_show_function(field, क्रमmat_string, sz, )	\
	fc_निजी_vport_store_u32_function(field)			\
अटल FC_DEVICE_ATTR(vport, field, S_IRUGO | S_IWUSR,		\
			show_fc_vport_##field,				\
			store_fc_vport_##field)


#घोषणा fc_निजी_vport_rd_क्रमागत_attr(title, maxlen)			\
अटल sमाप_प्रकार								\
show_fc_vport_##title (काष्ठा device *dev,				\
		       काष्ठा device_attribute *attr,			\
		       अक्षर *buf)					\
अणु									\
	काष्ठा fc_vport *vport = transport_class_to_vport(dev);		\
	स्थिर अक्षर *name;						\
	name = get_fc_##title##_name(vport->title);			\
	अगर (!name)							\
		वापस -EINVAL;						\
	वापस snम_लिखो(buf, maxlen, "%s\n", name);			\
पूर्ण									\
अटल FC_DEVICE_ATTR(vport, title, S_IRUGO,			\
			show_fc_vport_##title, शून्य)


#घोषणा SETUP_VPORT_ATTRIBUTE_RD(field)					\
	i->निजी_vport_attrs[count] = device_attr_vport_##field; \
	i->निजी_vport_attrs[count].attr.mode = S_IRUGO;		\
	i->निजी_vport_attrs[count].store = शून्य;			\
	i->vport_attrs[count] = &i->निजी_vport_attrs[count];		\
	अगर (i->f->get_##field)						\
		count++
	/* NOTE: Above MACRO dअगरfers: checks function not show bit */

#घोषणा SETUP_PRIVATE_VPORT_ATTRIBUTE_RD(field)				\
	i->निजी_vport_attrs[count] = device_attr_vport_##field; \
	i->निजी_vport_attrs[count].attr.mode = S_IRUGO;		\
	i->निजी_vport_attrs[count].store = शून्य;			\
	i->vport_attrs[count] = &i->निजी_vport_attrs[count];		\
	count++

#घोषणा SETUP_VPORT_ATTRIBUTE_WR(field)					\
	i->निजी_vport_attrs[count] = device_attr_vport_##field; \
	i->vport_attrs[count] = &i->निजी_vport_attrs[count];		\
	अगर (i->f->field)						\
		count++
	/* NOTE: Above MACRO dअगरfers: checks function */

#घोषणा SETUP_VPORT_ATTRIBUTE_RW(field)					\
	i->निजी_vport_attrs[count] = device_attr_vport_##field; \
	अगर (!i->f->set_vport_##field) अणु					\
		i->निजी_vport_attrs[count].attr.mode = S_IRUGO;	\
		i->निजी_vport_attrs[count].store = शून्य;		\
	पूर्ण								\
	i->vport_attrs[count] = &i->निजी_vport_attrs[count];		\
	count++
	/* NOTE: Above MACRO dअगरfers: करोes not check show bit */

#घोषणा SETUP_PRIVATE_VPORT_ATTRIBUTE_RW(field)				\
अणु									\
	i->निजी_vport_attrs[count] = device_attr_vport_##field; \
	i->vport_attrs[count] = &i->निजी_vport_attrs[count];		\
	count++;							\
पूर्ण


/* The FC Transport Virtual Port Attributes: */

/* Fixed Virtual Port Attributes */

/* Dynamic Virtual Port Attributes */

/* Private Virtual Port Attributes */

fc_निजी_vport_rd_क्रमागत_attr(vport_state, FC_VPORTSTATE_MAX_NAMELEN);
fc_निजी_vport_rd_क्रमागत_attr(vport_last_state, FC_VPORTSTATE_MAX_NAMELEN);
fc_निजी_vport_rd_attr_cast(node_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fc_निजी_vport_rd_attr_cast(port_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);

अटल sमाप_प्रकार
show_fc_vport_roles (काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा fc_vport *vport = transport_class_to_vport(dev);

	अगर (vport->roles == FC_PORT_ROLE_UNKNOWN)
		वापस snम_लिखो(buf, 20, "unknown\n");
	वापस get_fc_port_roles_names(vport->roles, buf);
पूर्ण
अटल FC_DEVICE_ATTR(vport, roles, S_IRUGO, show_fc_vport_roles, शून्य);

fc_निजी_vport_rd_क्रमागत_attr(vport_type, FC_PORTTYPE_MAX_NAMELEN);

fc_निजी_vport_show_function(symbolic_name, "%s\n",
		FC_VPORT_SYMBOLIC_NAMELEN + 1, )
fc_vport_store_str_function(symbolic_name, FC_VPORT_SYMBOLIC_NAMELEN)
अटल FC_DEVICE_ATTR(vport, symbolic_name, S_IRUGO | S_IWUSR,
		show_fc_vport_symbolic_name, store_fc_vport_symbolic_name);

अटल sमाप_प्रकार
store_fc_vport_delete(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fc_vport *vport = transport_class_to_vport(dev);
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING | FC_VPORT_DELETING)) अणु
		spin_unlock_irqrestore(shost->host_lock, flags);
		वापस -EBUSY;
	पूर्ण
	vport->flags |= FC_VPORT_DELETING;
	spin_unlock_irqrestore(shost->host_lock, flags);

	fc_queue_work(shost, &vport->vport_delete_work);
	वापस count;
पूर्ण
अटल FC_DEVICE_ATTR(vport, vport_delete, S_IWUSR,
			शून्य, store_fc_vport_delete);


/*
 * Enable/Disable vport
 *  Write "1" to disable, ग_लिखो "0" to enable
 */
अटल sमाप_प्रकार
store_fc_vport_disable(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	काष्ठा fc_vport *vport = transport_class_to_vport(dev);
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	पूर्णांक stat;

	अगर (vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING))
		वापस -EBUSY;

	अगर (*buf == '0') अणु
		अगर (vport->vport_state != FC_VPORT_DISABLED)
			वापस -EALREADY;
	पूर्ण अन्यथा अगर (*buf == '1') अणु
		अगर (vport->vport_state == FC_VPORT_DISABLED)
			वापस -EALREADY;
	पूर्ण अन्यथा
		वापस -EINVAL;

	stat = i->f->vport_disable(vport, ((*buf == '0') ? false : true));
	वापस stat ? stat : count;
पूर्ण
अटल FC_DEVICE_ATTR(vport, vport_disable, S_IWUSR,
			शून्य, store_fc_vport_disable);


/*
 * Host Attribute Management
 */

#घोषणा fc_host_show_function(field, क्रमmat_string, sz, cast)		\
अटल sमाप_प्रकार								\
show_fc_host_##field (काष्ठा device *dev,				\
		      काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);	\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	अगर (i->f->get_host_##field)					\
		i->f->get_host_##field(shost);				\
	वापस snम_लिखो(buf, sz, क्रमmat_string, cast fc_host_##field(shost)); \
पूर्ण

#घोषणा fc_host_store_function(field)					\
अटल sमाप_प्रकार								\
store_fc_host_##field(काष्ठा device *dev, 				\
		      काष्ठा device_attribute *attr,			\
		      स्थिर अक्षर *buf,	माप_प्रकार count)			\
अणु									\
	पूर्णांक val;							\
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);	\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	अक्षर *cp;							\
									\
	val = simple_म_से_अदीर्घ(buf, &cp, 0);				\
	अगर (*cp && (*cp != '\n'))					\
		वापस -EINVAL;						\
	i->f->set_host_##field(shost, val);				\
	वापस count;							\
पूर्ण

#घोषणा fc_host_store_str_function(field, slen)				\
अटल sमाप_प्रकार								\
store_fc_host_##field(काष्ठा device *dev,				\
		      काष्ठा device_attribute *attr,			\
		      स्थिर अक्षर *buf, माप_प्रकार count)			\
अणु									\
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);	\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	अचिन्हित पूर्णांक cnt=count;						\
									\
	/* count may include a LF at end of string */			\
	अगर (buf[cnt-1] == '\n')						\
		cnt--;							\
	अगर (cnt > ((slen) - 1))						\
		वापस -EINVAL;						\
	स_नकल(fc_host_##field(shost), buf, cnt);			\
	i->f->set_host_##field(shost);					\
	वापस count;							\
पूर्ण

#घोषणा fc_host_rd_attr(field, क्रमmat_string, sz)			\
	fc_host_show_function(field, क्रमmat_string, sz, )		\
अटल FC_DEVICE_ATTR(host, field, S_IRUGO,			\
			 show_fc_host_##field, शून्य)

#घोषणा fc_host_rd_attr_cast(field, क्रमmat_string, sz, cast)		\
	fc_host_show_function(field, क्रमmat_string, sz, (cast))		\
अटल FC_DEVICE_ATTR(host, field, S_IRUGO,			\
			  show_fc_host_##field, शून्य)

#घोषणा fc_host_rw_attr(field, क्रमmat_string, sz)			\
	fc_host_show_function(field, क्रमmat_string, sz, )		\
	fc_host_store_function(field)					\
अटल FC_DEVICE_ATTR(host, field, S_IRUGO | S_IWUSR,		\
			show_fc_host_##field,				\
			store_fc_host_##field)

#घोषणा fc_host_rd_क्रमागत_attr(title, maxlen)				\
अटल sमाप_प्रकार								\
show_fc_host_##title (काष्ठा device *dev,				\
		      काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);	\
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);	\
	स्थिर अक्षर *name;						\
	अगर (i->f->get_host_##title)					\
		i->f->get_host_##title(shost);				\
	name = get_fc_##title##_name(fc_host_##title(shost));		\
	अगर (!name)							\
		वापस -EINVAL;						\
	वापस snम_लिखो(buf, maxlen, "%s\n", name);			\
पूर्ण									\
अटल FC_DEVICE_ATTR(host, title, S_IRUGO, show_fc_host_##title, शून्य)

#घोषणा SETUP_HOST_ATTRIBUTE_RD(field)					\
	i->निजी_host_attrs[count] = device_attr_host_##field;	\
	i->निजी_host_attrs[count].attr.mode = S_IRUGO;		\
	i->निजी_host_attrs[count].store = शून्य;			\
	i->host_attrs[count] = &i->निजी_host_attrs[count];		\
	अगर (i->f->show_host_##field)					\
		count++

#घोषणा SETUP_HOST_ATTRIBUTE_RD_NS(field)				\
	i->निजी_host_attrs[count] = device_attr_host_##field;	\
	i->निजी_host_attrs[count].attr.mode = S_IRUGO;		\
	i->निजी_host_attrs[count].store = शून्य;			\
	i->host_attrs[count] = &i->निजी_host_attrs[count];		\
	count++

#घोषणा SETUP_HOST_ATTRIBUTE_RW(field)					\
	i->निजी_host_attrs[count] = device_attr_host_##field;	\
	अगर (!i->f->set_host_##field) अणु					\
		i->निजी_host_attrs[count].attr.mode = S_IRUGO;	\
		i->निजी_host_attrs[count].store = शून्य;		\
	पूर्ण								\
	i->host_attrs[count] = &i->निजी_host_attrs[count];		\
	अगर (i->f->show_host_##field)					\
		count++


#घोषणा fc_निजी_host_show_function(field, क्रमmat_string, sz, cast)	\
अटल sमाप_प्रकार								\
show_fc_host_##field (काष्ठा device *dev,				\
		      काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);	\
	वापस snम_लिखो(buf, sz, क्रमmat_string, cast fc_host_##field(shost)); \
पूर्ण

#घोषणा fc_निजी_host_rd_attr(field, क्रमmat_string, sz)		\
	fc_निजी_host_show_function(field, क्रमmat_string, sz, )	\
अटल FC_DEVICE_ATTR(host, field, S_IRUGO,			\
			 show_fc_host_##field, शून्य)

#घोषणा fc_निजी_host_rd_attr_cast(field, क्रमmat_string, sz, cast)	\
	fc_निजी_host_show_function(field, क्रमmat_string, sz, (cast)) \
अटल FC_DEVICE_ATTR(host, field, S_IRUGO,			\
			  show_fc_host_##field, शून्य)

#घोषणा SETUP_PRIVATE_HOST_ATTRIBUTE_RD(field)			\
	i->निजी_host_attrs[count] = device_attr_host_##field;	\
	i->निजी_host_attrs[count].attr.mode = S_IRUGO;		\
	i->निजी_host_attrs[count].store = शून्य;			\
	i->host_attrs[count] = &i->निजी_host_attrs[count];		\
	count++

#घोषणा SETUP_PRIVATE_HOST_ATTRIBUTE_RW(field)			\
अणु									\
	i->निजी_host_attrs[count] = device_attr_host_##field;	\
	i->host_attrs[count] = &i->निजी_host_attrs[count];		\
	count++;							\
पूर्ण


/* Fixed Host Attributes */

अटल sमाप_प्रकार
show_fc_host_supported_classes (काष्ठा device *dev,
			        काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);

	अगर (fc_host_supported_classes(shost) == FC_COS_UNSPECIFIED)
		वापस snम_लिखो(buf, 20, "unspecified\n");

	वापस get_fc_cos_names(fc_host_supported_classes(shost), buf);
पूर्ण
अटल FC_DEVICE_ATTR(host, supported_classes, S_IRUGO,
		show_fc_host_supported_classes, शून्य);

अटल sमाप_प्रकार
show_fc_host_supported_fc4s (काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	वापस (sमाप_प्रकार)show_fc_fc4s(buf, fc_host_supported_fc4s(shost));
पूर्ण
अटल FC_DEVICE_ATTR(host, supported_fc4s, S_IRUGO,
		show_fc_host_supported_fc4s, शून्य);

अटल sमाप_प्रकार
show_fc_host_supported_speeds (काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);

	अगर (fc_host_supported_speeds(shost) == FC_PORTSPEED_UNKNOWN)
		वापस snम_लिखो(buf, 20, "unknown\n");

	वापस get_fc_port_speed_names(fc_host_supported_speeds(shost), buf);
पूर्ण
अटल FC_DEVICE_ATTR(host, supported_speeds, S_IRUGO,
		show_fc_host_supported_speeds, शून्य);


fc_निजी_host_rd_attr_cast(node_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fc_निजी_host_rd_attr_cast(port_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fc_निजी_host_rd_attr_cast(permanent_port_name, "0x%llx\n", 20,
			     अचिन्हित दीर्घ दीर्घ);
fc_निजी_host_rd_attr(maxframe_size, "%u bytes\n", 20);
fc_निजी_host_rd_attr(max_npiv_vports, "%u\n", 20);
fc_निजी_host_rd_attr(serial_number, "%s\n", (FC_SERIAL_NUMBER_SIZE +1));
fc_निजी_host_rd_attr(manufacturer, "%s\n", FC_SERIAL_NUMBER_SIZE + 1);
fc_निजी_host_rd_attr(model, "%s\n", FC_SYMBOLIC_NAME_SIZE + 1);
fc_निजी_host_rd_attr(model_description, "%s\n", FC_SYMBOLIC_NAME_SIZE + 1);
fc_निजी_host_rd_attr(hardware_version, "%s\n", FC_VERSION_STRING_SIZE + 1);
fc_निजी_host_rd_attr(driver_version, "%s\n", FC_VERSION_STRING_SIZE + 1);
fc_निजी_host_rd_attr(firmware_version, "%s\n", FC_VERSION_STRING_SIZE + 1);
fc_निजी_host_rd_attr(optionrom_version, "%s\n", FC_VERSION_STRING_SIZE + 1);


/* Dynamic Host Attributes */

अटल sमाप_प्रकार
show_fc_host_active_fc4s (काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);

	अगर (i->f->get_host_active_fc4s)
		i->f->get_host_active_fc4s(shost);

	वापस (sमाप_प्रकार)show_fc_fc4s(buf, fc_host_active_fc4s(shost));
पूर्ण
अटल FC_DEVICE_ATTR(host, active_fc4s, S_IRUGO,
		show_fc_host_active_fc4s, शून्य);

अटल sमाप_प्रकार
show_fc_host_speed (काष्ठा device *dev,
		    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);

	अगर (i->f->get_host_speed)
		i->f->get_host_speed(shost);

	अगर (fc_host_speed(shost) == FC_PORTSPEED_UNKNOWN)
		वापस snम_लिखो(buf, 20, "unknown\n");

	वापस get_fc_port_speed_names(fc_host_speed(shost), buf);
पूर्ण
अटल FC_DEVICE_ATTR(host, speed, S_IRUGO,
		show_fc_host_speed, शून्य);


fc_host_rd_attr(port_id, "0x%06x\n", 20);
fc_host_rd_क्रमागत_attr(port_type, FC_PORTTYPE_MAX_NAMELEN);
fc_host_rd_क्रमागत_attr(port_state, FC_PORTSTATE_MAX_NAMELEN);
fc_host_rd_attr_cast(fabric_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fc_host_rd_attr(symbolic_name, "%s\n", FC_SYMBOLIC_NAME_SIZE + 1);

fc_निजी_host_show_function(प्रणाली_hostname, "%s\n",
		FC_SYMBOLIC_NAME_SIZE + 1, )
fc_host_store_str_function(प्रणाली_hostname, FC_SYMBOLIC_NAME_SIZE)
अटल FC_DEVICE_ATTR(host, प्रणाली_hostname, S_IRUGO | S_IWUSR,
		show_fc_host_प्रणाली_hostname, store_fc_host_प्रणाली_hostname);


/* Private Host Attributes */

अटल sमाप_प्रकार
show_fc_निजी_host_tgtid_bind_type(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	स्थिर अक्षर *name;

	name = get_fc_tgtid_bind_type_name(fc_host_tgtid_bind_type(shost));
	अगर (!name)
		वापस -EINVAL;
	वापस snम_लिखो(buf, FC_BINDTYPE_MAX_NAMELEN, "%s\n", name);
पूर्ण

#घोषणा get_list_head_entry(pos, head, member) 		\
	pos = list_entry((head)->next, typeof(*pos), member)

अटल sमाप_प्रकार
store_fc_निजी_host_tgtid_bind_type(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा fc_rport *rport;
 	क्रमागत fc_tgtid_binding_type val;
	अचिन्हित दीर्घ flags;

	अगर (get_fc_tgtid_bind_type_match(buf, &val))
		वापस -EINVAL;

	/* अगर changing bind type, purge all unused consistent bindings */
	अगर (val != fc_host_tgtid_bind_type(shost)) अणु
		spin_lock_irqsave(shost->host_lock, flags);
		जबतक (!list_empty(&fc_host_rport_bindings(shost))) अणु
			get_list_head_entry(rport,
				&fc_host_rport_bindings(shost), peers);
			list_del(&rport->peers);
			rport->port_state = FC_PORTSTATE_DELETED;
			fc_queue_work(shost, &rport->rport_delete_work);
		पूर्ण
		spin_unlock_irqrestore(shost->host_lock, flags);
	पूर्ण

	fc_host_tgtid_bind_type(shost) = val;
	वापस count;
पूर्ण

अटल FC_DEVICE_ATTR(host, tgtid_bind_type, S_IRUGO | S_IWUSR,
			show_fc_निजी_host_tgtid_bind_type,
			store_fc_निजी_host_tgtid_bind_type);

अटल sमाप_प्रकार
store_fc_निजी_host_issue_lip(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	पूर्णांक ret;

	/* ignore any data value written to the attribute */
	अगर (i->f->issue_fc_host_lip) अणु
		ret = i->f->issue_fc_host_lip(shost);
		वापस ret ? ret: count;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल FC_DEVICE_ATTR(host, issue_lip, S_IWUSR, शून्य,
			store_fc_निजी_host_issue_lip);

अटल sमाप_प्रकार
store_fc_निजी_host_dev_loss_पंचांगo(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	काष्ठा fc_rport *rport;
	अचिन्हित दीर्घ val, flags;
	पूर्णांक rc;

	rc = fc_str_to_dev_loss(buf, &val);
	अगर (rc)
		वापस rc;

	fc_host_dev_loss_पंचांगo(shost) = val;
	spin_lock_irqsave(shost->host_lock, flags);
	list_क्रम_each_entry(rport, &fc_host->rports, peers)
		fc_rport_set_dev_loss_पंचांगo(rport, val);
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस count;
पूर्ण

fc_निजी_host_show_function(dev_loss_पंचांगo, "%d\n", 20, );
अटल FC_DEVICE_ATTR(host, dev_loss_पंचांगo, S_IRUGO | S_IWUSR,
		      show_fc_host_dev_loss_पंचांगo,
		      store_fc_निजी_host_dev_loss_पंचांगo);

fc_निजी_host_rd_attr(npiv_vports_inuse, "%u\n", 20);

/*
 * Host Statistics Management
 */

/* Show a given attribute in the statistics group */
अटल sमाप_प्रकार
fc_stat_show(स्थिर काष्ठा device *dev, अक्षर *buf, अचिन्हित दीर्घ offset)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा fc_host_statistics *stats;
	sमाप_प्रकार ret = -ENOENT;

	अगर (offset > माप(काष्ठा fc_host_statistics) ||
	    offset % माप(u64) != 0)
		WARN_ON(1);

	अगर (i->f->get_fc_host_stats) अणु
		stats = (i->f->get_fc_host_stats)(shost);
		अगर (stats)
			ret = snम_लिखो(buf, 20, "0x%llx\n",
			      (अचिन्हित दीर्घ दीर्घ)*(u64 *)(((u8 *) stats) + offset));
	पूर्ण
	वापस ret;
पूर्ण


/* generate a पढ़ो-only statistics attribute */
#घोषणा fc_host_statistic(name)						\
अटल sमाप_प्रकार show_fcstat_##name(काष्ठा device *cd,			\
				  काष्ठा device_attribute *attr,	\
				  अक्षर *buf)				\
अणु									\
	वापस fc_stat_show(cd, buf, 					\
			    दुरत्व(काष्ठा fc_host_statistics, name));	\
पूर्ण									\
अटल FC_DEVICE_ATTR(host, name, S_IRUGO, show_fcstat_##name, शून्य)

fc_host_statistic(seconds_since_last_reset);
fc_host_statistic(tx_frames);
fc_host_statistic(tx_words);
fc_host_statistic(rx_frames);
fc_host_statistic(rx_words);
fc_host_statistic(lip_count);
fc_host_statistic(nos_count);
fc_host_statistic(error_frames);
fc_host_statistic(dumped_frames);
fc_host_statistic(link_failure_count);
fc_host_statistic(loss_of_sync_count);
fc_host_statistic(loss_of_संकेत_count);
fc_host_statistic(prim_seq_protocol_err_count);
fc_host_statistic(invalid_tx_word_count);
fc_host_statistic(invalid_crc_count);
fc_host_statistic(fcp_input_requests);
fc_host_statistic(fcp_output_requests);
fc_host_statistic(fcp_control_requests);
fc_host_statistic(fcp_input_megabytes);
fc_host_statistic(fcp_output_megabytes);
fc_host_statistic(fcp_packet_alloc_failures);
fc_host_statistic(fcp_packet_पातs);
fc_host_statistic(fcp_frame_alloc_failures);
fc_host_statistic(fc_no_मुक्त_exch);
fc_host_statistic(fc_no_मुक्त_exch_xid);
fc_host_statistic(fc_xid_not_found);
fc_host_statistic(fc_xid_busy);
fc_host_statistic(fc_seq_not_found);
fc_host_statistic(fc_non_bls_resp);
fc_host_statistic(cn_sig_warn);
fc_host_statistic(cn_sig_alarm);


#घोषणा fc_host_fpin_statistic(name)					\
अटल sमाप_प्रकार fc_host_fpinstat_##name(काष्ठा device *cd,		\
				  काष्ठा device_attribute *attr,	\
				  अक्षर *buf)				\
अणु									\
	काष्ठा Scsi_Host *shost = transport_class_to_shost(cd);		\
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);	\
									\
	वापस snम_लिखो(buf, 20, "0x%llx\n", fc_host->fpin_stats.name);	\
पूर्ण									\
अटल FC_DEVICE_ATTR(host, fpin_##name, 0444, fc_host_fpinstat_##name, शून्य)

fc_host_fpin_statistic(dn);
fc_host_fpin_statistic(dn_unknown);
fc_host_fpin_statistic(dn_समयout);
fc_host_fpin_statistic(dn_unable_to_route);
fc_host_fpin_statistic(dn_device_specअगरic);
fc_host_fpin_statistic(cn);
fc_host_fpin_statistic(cn_clear);
fc_host_fpin_statistic(cn_lost_credit);
fc_host_fpin_statistic(cn_credit_stall);
fc_host_fpin_statistic(cn_oversubscription);
fc_host_fpin_statistic(cn_device_specअगरic);
fc_host_fpin_statistic(li);
fc_host_fpin_statistic(li_failure_unknown);
fc_host_fpin_statistic(li_link_failure_count);
fc_host_fpin_statistic(li_loss_of_sync_count);
fc_host_fpin_statistic(li_loss_of_संकेतs_count);
fc_host_fpin_statistic(li_prim_seq_err_count);
fc_host_fpin_statistic(li_invalid_tx_word_count);
fc_host_fpin_statistic(li_invalid_crc_count);
fc_host_fpin_statistic(li_device_specअगरic);

अटल sमाप_प्रकार
fc_reset_statistics(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);

	/* ignore any data value written to the attribute */
	अगर (i->f->reset_fc_host_stats) अणु
		i->f->reset_fc_host_stats(shost);
		वापस count;
	पूर्ण

	वापस -ENOENT;
पूर्ण
अटल FC_DEVICE_ATTR(host, reset_statistics, S_IWUSR, शून्य,
				fc_reset_statistics);

अटल काष्ठा attribute *fc_statistics_attrs[] = अणु
	&device_attr_host_seconds_since_last_reset.attr,
	&device_attr_host_tx_frames.attr,
	&device_attr_host_tx_words.attr,
	&device_attr_host_rx_frames.attr,
	&device_attr_host_rx_words.attr,
	&device_attr_host_lip_count.attr,
	&device_attr_host_nos_count.attr,
	&device_attr_host_error_frames.attr,
	&device_attr_host_dumped_frames.attr,
	&device_attr_host_link_failure_count.attr,
	&device_attr_host_loss_of_sync_count.attr,
	&device_attr_host_loss_of_संकेत_count.attr,
	&device_attr_host_prim_seq_protocol_err_count.attr,
	&device_attr_host_invalid_tx_word_count.attr,
	&device_attr_host_invalid_crc_count.attr,
	&device_attr_host_fcp_input_requests.attr,
	&device_attr_host_fcp_output_requests.attr,
	&device_attr_host_fcp_control_requests.attr,
	&device_attr_host_fcp_input_megabytes.attr,
	&device_attr_host_fcp_output_megabytes.attr,
	&device_attr_host_fcp_packet_alloc_failures.attr,
	&device_attr_host_fcp_packet_पातs.attr,
	&device_attr_host_fcp_frame_alloc_failures.attr,
	&device_attr_host_fc_no_मुक्त_exch.attr,
	&device_attr_host_fc_no_मुक्त_exch_xid.attr,
	&device_attr_host_fc_xid_not_found.attr,
	&device_attr_host_fc_xid_busy.attr,
	&device_attr_host_fc_seq_not_found.attr,
	&device_attr_host_fc_non_bls_resp.attr,
	&device_attr_host_cn_sig_warn.attr,
	&device_attr_host_cn_sig_alarm.attr,
	&device_attr_host_reset_statistics.attr,
	&device_attr_host_fpin_dn.attr,
	&device_attr_host_fpin_dn_unknown.attr,
	&device_attr_host_fpin_dn_समयout.attr,
	&device_attr_host_fpin_dn_unable_to_route.attr,
	&device_attr_host_fpin_dn_device_specअगरic.attr,
	&device_attr_host_fpin_li.attr,
	&device_attr_host_fpin_li_failure_unknown.attr,
	&device_attr_host_fpin_li_link_failure_count.attr,
	&device_attr_host_fpin_li_loss_of_sync_count.attr,
	&device_attr_host_fpin_li_loss_of_संकेतs_count.attr,
	&device_attr_host_fpin_li_prim_seq_err_count.attr,
	&device_attr_host_fpin_li_invalid_tx_word_count.attr,
	&device_attr_host_fpin_li_invalid_crc_count.attr,
	&device_attr_host_fpin_li_device_specअगरic.attr,
	&device_attr_host_fpin_cn.attr,
	&device_attr_host_fpin_cn_clear.attr,
	&device_attr_host_fpin_cn_lost_credit.attr,
	&device_attr_host_fpin_cn_credit_stall.attr,
	&device_attr_host_fpin_cn_oversubscription.attr,
	&device_attr_host_fpin_cn_device_specअगरic.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group fc_statistics_group = अणु
	.name = "statistics",
	.attrs = fc_statistics_attrs,
पूर्ण;


/* Host Vport Attributes */

अटल पूर्णांक
fc_parse_wwn(स्थिर अक्षर *ns, u64 *nm)
अणु
	अचिन्हित पूर्णांक i, j;
	u8 wwn[8];

	स_रखो(wwn, 0, माप(wwn));

	/* Validate and store the new name */
	क्रम (i=0, j=0; i < 16; i++) अणु
		पूर्णांक value;

		value = hex_to_bin(*ns++);
		अगर (value >= 0)
			j = (j << 4) | value;
		अन्यथा
			वापस -EINVAL;
		अगर (i % 2) अणु
			wwn[i/2] = j & 0xff;
			j = 0;
		पूर्ण
	पूर्ण

	*nm = wwn_to_u64(wwn);

	वापस 0;
पूर्ण


/*
 * "Short-cut" sysfs variable to create a new vport on a FC Host.
 * Input is a string of the क्रमm "<WWPN>:<WWNN>". Other attributes
 * will शेष to a NPIV-based FCP_Initiator; The WWNs are specअगरied
 * as hex अक्षरacters, and may *not* contain any prefixes (e.g. 0x, x, etc)
 */
अटल sमाप_प्रकार
store_fc_host_vport_create(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा fc_vport_identअगरiers vid;
	काष्ठा fc_vport *vport;
	अचिन्हित पूर्णांक cnt=count;
	पूर्णांक stat;

	स_रखो(&vid, 0, माप(vid));

	/* count may include a LF at end of string */
	अगर (buf[cnt-1] == '\n')
		cnt--;

	/* validate we have enough अक्षरacters क्रम WWPN */
	अगर ((cnt != (16+1+16)) || (buf[16] != ':'))
		वापस -EINVAL;

	stat = fc_parse_wwn(&buf[0], &vid.port_name);
	अगर (stat)
		वापस stat;

	stat = fc_parse_wwn(&buf[17], &vid.node_name);
	अगर (stat)
		वापस stat;

	vid.roles = FC_PORT_ROLE_FCP_INITIATOR;
	vid.vport_type = FC_PORTTYPE_NPIV;
	/* vid.symbolic_name is alपढ़ोy zero/शून्य's */
	vid.disable = false;		/* always enabled */

	/* we only allow support on Channel 0 !!! */
	stat = fc_vport_setup(shost, 0, &shost->shost_gendev, &vid, &vport);
	वापस stat ? stat : count;
पूर्ण
अटल FC_DEVICE_ATTR(host, vport_create, S_IWUSR, शून्य,
			store_fc_host_vport_create);


/*
 * "Short-cut" sysfs variable to delete a vport on a FC Host.
 * Vport is identअगरied by a string containing "<WWPN>:<WWNN>".
 * The WWNs are specअगरied as hex अक्षरacters, and may *not* contain
 * any prefixes (e.g. 0x, x, etc)
 */
अटल sमाप_प्रकार
store_fc_host_vport_delete(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	काष्ठा fc_vport *vport;
	u64 wwpn, wwnn;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cnt=count;
	पूर्णांक stat, match;

	/* count may include a LF at end of string */
	अगर (buf[cnt-1] == '\n')
		cnt--;

	/* validate we have enough अक्षरacters क्रम WWPN */
	अगर ((cnt != (16+1+16)) || (buf[16] != ':'))
		वापस -EINVAL;

	stat = fc_parse_wwn(&buf[0], &wwpn);
	अगर (stat)
		वापस stat;

	stat = fc_parse_wwn(&buf[17], &wwnn);
	अगर (stat)
		वापस stat;

	spin_lock_irqsave(shost->host_lock, flags);
	match = 0;
	/* we only allow support on Channel 0 !!! */
	list_क्रम_each_entry(vport, &fc_host->vports, peers) अणु
		अगर ((vport->channel == 0) &&
		    (vport->port_name == wwpn) && (vport->node_name == wwnn)) अणु
			अगर (vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING))
				अवरोध;
			vport->flags |= FC_VPORT_DELETING;
			match = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	अगर (!match)
		वापस -ENODEV;

	stat = fc_vport_terminate(vport);
	वापस stat ? stat : count;
पूर्ण
अटल FC_DEVICE_ATTR(host, vport_delete, S_IWUSR, शून्य,
			store_fc_host_vport_delete);


अटल पूर्णांक fc_host_match(काष्ठा attribute_container *cont,
			  काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा fc_पूर्णांकernal *i;

	अगर (!scsi_is_host_device(dev))
		वापस 0;

	shost = dev_to_shost(dev);
	अगर (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &fc_host_class.class)
		वापस 0;

	i = to_fc_पूर्णांकernal(shost->transportt);

	वापस &i->t.host_attrs.ac == cont;
पूर्ण

अटल पूर्णांक fc_target_match(काष्ठा attribute_container *cont,
			    काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा fc_पूर्णांकernal *i;

	अगर (!scsi_is_target_device(dev))
		वापस 0;

	shost = dev_to_shost(dev->parent);
	अगर (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &fc_host_class.class)
		वापस 0;

	i = to_fc_पूर्णांकernal(shost->transportt);

	वापस &i->t.target_attrs.ac == cont;
पूर्ण

अटल व्योम fc_rport_dev_release(काष्ठा device *dev)
अणु
	काष्ठा fc_rport *rport = dev_to_rport(dev);
	put_device(dev->parent);
	kमुक्त(rport);
पूर्ण

पूर्णांक scsi_is_fc_rport(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == fc_rport_dev_release;
पूर्ण
EXPORT_SYMBOL(scsi_is_fc_rport);

अटल पूर्णांक fc_rport_match(काष्ठा attribute_container *cont,
			    काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा fc_पूर्णांकernal *i;

	अगर (!scsi_is_fc_rport(dev))
		वापस 0;

	shost = dev_to_shost(dev->parent);
	अगर (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &fc_host_class.class)
		वापस 0;

	i = to_fc_पूर्णांकernal(shost->transportt);

	वापस &i->rport_attr_cont.ac == cont;
पूर्ण


अटल व्योम fc_vport_dev_release(काष्ठा device *dev)
अणु
	काष्ठा fc_vport *vport = dev_to_vport(dev);
	put_device(dev->parent);		/* release kobj parent */
	kमुक्त(vport);
पूर्ण

अटल पूर्णांक scsi_is_fc_vport(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == fc_vport_dev_release;
पूर्ण

अटल पूर्णांक fc_vport_match(काष्ठा attribute_container *cont,
			    काष्ठा device *dev)
अणु
	काष्ठा fc_vport *vport;
	काष्ठा Scsi_Host *shost;
	काष्ठा fc_पूर्णांकernal *i;

	अगर (!scsi_is_fc_vport(dev))
		वापस 0;
	vport = dev_to_vport(dev);

	shost = vport_to_shost(vport);
	अगर (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &fc_host_class.class)
		वापस 0;

	i = to_fc_पूर्णांकernal(shost->transportt);
	वापस &i->vport_attr_cont.ac == cont;
पूर्ण


/**
 * fc_eh_समयd_out - FC Transport I/O समयout पूर्णांकercept handler
 * @scmd:	The SCSI command which समयd out
 *
 * This routine protects against error handlers getting invoked जबतक a
 * rport is in a blocked state, typically due to a temporarily loss of
 * connectivity. If the error handlers are allowed to proceed, requests
 * to पात i/o, reset the target, etc will likely fail as there is no way
 * to communicate with the device to perक्रमm the requested function. These
 * failures may result in the midlayer taking the device offline, requiring
 * manual पूर्णांकervention to restore operation.
 *
 * This routine, called whenever an i/o बार out, validates the state of
 * the underlying rport. If the rport is blocked, it वापसs
 * EH_RESET_TIMER, which will जारी to reschedule the समयout.
 * Eventually, either the device will वापस, or devloss_पंचांगo will fire,
 * and when the समयout then fires, it will be handled normally.
 * If the rport is not blocked, normal error handling जारीs.
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
क्रमागत blk_eh_समयr_वापस
fc_eh_समयd_out(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(scmd->device));

	अगर (rport->port_state == FC_PORTSTATE_BLOCKED)
		वापस BLK_EH_RESET_TIMER;

	वापस BLK_EH_DONE;
पूर्ण
EXPORT_SYMBOL(fc_eh_समयd_out);

/*
 * Called by fc_user_scan to locate an rport on the shost that
 * matches the channel and target id, and invoke scsi_scan_target()
 * on the rport.
 */
अटल व्योम
fc_user_scan_tgt(काष्ठा Scsi_Host *shost, uपूर्णांक channel, uपूर्णांक id, u64 lun)
अणु
	काष्ठा fc_rport *rport;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);

	list_क्रम_each_entry(rport, &fc_host_rports(shost), peers) अणु
		अगर (rport->scsi_target_id == -1)
			जारी;

		अगर ((rport->port_state != FC_PORTSTATE_ONLINE) &&
			(rport->port_state != FC_PORTSTATE_MARGINAL))
			जारी;

		अगर ((channel == rport->channel) &&
		    (id == rport->scsi_target_id)) अणु
			spin_unlock_irqrestore(shost->host_lock, flags);
			scsi_scan_target(&rport->dev, channel, id, lun,
					 SCSI_SCAN_MANUAL);
			वापस;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

/*
 * Called via sysfs scan routines. Necessary, as the FC transport
 * wants to place all target objects below the rport object. So this
 * routine must invoke the scsi_scan_target() routine with the rport
 * object as the parent.
 */
अटल पूर्णांक
fc_user_scan(काष्ठा Scsi_Host *shost, uपूर्णांक channel, uपूर्णांक id, u64 lun)
अणु
	uपूर्णांक chlo, chhi;
	uपूर्णांक tgtlo, tgthi;

	अगर (((channel != SCAN_WILD_CARD) && (channel > shost->max_channel)) ||
	    ((id != SCAN_WILD_CARD) && (id >= shost->max_id)) ||
	    ((lun != SCAN_WILD_CARD) && (lun > shost->max_lun)))
		वापस -EINVAL;

	अगर (channel == SCAN_WILD_CARD) अणु
		chlo = 0;
		chhi = shost->max_channel + 1;
	पूर्ण अन्यथा अणु
		chlo = channel;
		chhi = channel + 1;
	पूर्ण

	अगर (id == SCAN_WILD_CARD) अणु
		tgtlo = 0;
		tgthi = shost->max_id;
	पूर्ण अन्यथा अणु
		tgtlo = id;
		tgthi = id + 1;
	पूर्ण

	क्रम ( ; chlo < chhi; chlo++)
		क्रम ( ; tgtlo < tgthi; tgtlo++)
			fc_user_scan_tgt(shost, chlo, tgtlo, lun);

	वापस 0;
पूर्ण

काष्ठा scsi_transport_ढाँचा *
fc_attach_transport(काष्ठा fc_function_ढाँचा *ft)
अणु
	पूर्णांक count;
	काष्ठा fc_पूर्णांकernal *i = kzalloc(माप(काष्ठा fc_पूर्णांकernal),
					GFP_KERNEL);

	अगर (unlikely(!i))
		वापस शून्य;

	i->t.target_attrs.ac.attrs = &i->starget_attrs[0];
	i->t.target_attrs.ac.class = &fc_transport_class.class;
	i->t.target_attrs.ac.match = fc_target_match;
	i->t.target_size = माप(काष्ठा fc_starget_attrs);
	transport_container_रेजिस्टर(&i->t.target_attrs);

	i->t.host_attrs.ac.attrs = &i->host_attrs[0];
	i->t.host_attrs.ac.class = &fc_host_class.class;
	i->t.host_attrs.ac.match = fc_host_match;
	i->t.host_size = माप(काष्ठा fc_host_attrs);
	अगर (ft->get_fc_host_stats)
		i->t.host_attrs.statistics = &fc_statistics_group;
	transport_container_रेजिस्टर(&i->t.host_attrs);

	i->rport_attr_cont.ac.attrs = &i->rport_attrs[0];
	i->rport_attr_cont.ac.class = &fc_rport_class.class;
	i->rport_attr_cont.ac.match = fc_rport_match;
	i->rport_attr_cont.statistics = &fc_rport_statistics_group;
	transport_container_रेजिस्टर(&i->rport_attr_cont);

	i->vport_attr_cont.ac.attrs = &i->vport_attrs[0];
	i->vport_attr_cont.ac.class = &fc_vport_class.class;
	i->vport_attr_cont.ac.match = fc_vport_match;
	transport_container_रेजिस्टर(&i->vport_attr_cont);

	i->f = ft;

	/* Transport uses the shost workq क्रम scsi scanning */
	i->t.create_work_queue = 1;

	i->t.user_scan = fc_user_scan;

	/*
	 * Setup SCSI Target Attributes.
	 */
	count = 0;
	SETUP_STARGET_ATTRIBUTE_RD(node_name);
	SETUP_STARGET_ATTRIBUTE_RD(port_name);
	SETUP_STARGET_ATTRIBUTE_RD(port_id);

	BUG_ON(count > FC_STARGET_NUM_ATTRS);

	i->starget_attrs[count] = शून्य;


	/*
	 * Setup SCSI Host Attributes.
	 */
	count=0;
	SETUP_HOST_ATTRIBUTE_RD(node_name);
	SETUP_HOST_ATTRIBUTE_RD(port_name);
	SETUP_HOST_ATTRIBUTE_RD(permanent_port_name);
	SETUP_HOST_ATTRIBUTE_RD(supported_classes);
	SETUP_HOST_ATTRIBUTE_RD(supported_fc4s);
	SETUP_HOST_ATTRIBUTE_RD(supported_speeds);
	SETUP_HOST_ATTRIBUTE_RD(maxframe_size);
	अगर (ft->vport_create) अणु
		SETUP_HOST_ATTRIBUTE_RD_NS(max_npiv_vports);
		SETUP_HOST_ATTRIBUTE_RD_NS(npiv_vports_inuse);
	पूर्ण
	SETUP_HOST_ATTRIBUTE_RD(serial_number);
	SETUP_HOST_ATTRIBUTE_RD(manufacturer);
	SETUP_HOST_ATTRIBUTE_RD(model);
	SETUP_HOST_ATTRIBUTE_RD(model_description);
	SETUP_HOST_ATTRIBUTE_RD(hardware_version);
	SETUP_HOST_ATTRIBUTE_RD(driver_version);
	SETUP_HOST_ATTRIBUTE_RD(firmware_version);
	SETUP_HOST_ATTRIBUTE_RD(optionrom_version);

	SETUP_HOST_ATTRIBUTE_RD(port_id);
	SETUP_HOST_ATTRIBUTE_RD(port_type);
	SETUP_HOST_ATTRIBUTE_RD(port_state);
	SETUP_HOST_ATTRIBUTE_RD(active_fc4s);
	SETUP_HOST_ATTRIBUTE_RD(speed);
	SETUP_HOST_ATTRIBUTE_RD(fabric_name);
	SETUP_HOST_ATTRIBUTE_RD(symbolic_name);
	SETUP_HOST_ATTRIBUTE_RW(प्रणाली_hostname);

	/* Transport-managed attributes */
	SETUP_PRIVATE_HOST_ATTRIBUTE_RW(dev_loss_पंचांगo);
	SETUP_PRIVATE_HOST_ATTRIBUTE_RW(tgtid_bind_type);
	अगर (ft->issue_fc_host_lip)
		SETUP_PRIVATE_HOST_ATTRIBUTE_RW(issue_lip);
	अगर (ft->vport_create)
		SETUP_PRIVATE_HOST_ATTRIBUTE_RW(vport_create);
	अगर (ft->vport_delete)
		SETUP_PRIVATE_HOST_ATTRIBUTE_RW(vport_delete);

	BUG_ON(count > FC_HOST_NUM_ATTRS);

	i->host_attrs[count] = शून्य;

	/*
	 * Setup Remote Port Attributes.
	 */
	count=0;
	SETUP_RPORT_ATTRIBUTE_RD(maxframe_size);
	SETUP_RPORT_ATTRIBUTE_RD(supported_classes);
	SETUP_RPORT_ATTRIBUTE_RW(dev_loss_पंचांगo);
	SETUP_PRIVATE_RPORT_ATTRIBUTE_RD(node_name);
	SETUP_PRIVATE_RPORT_ATTRIBUTE_RD(port_name);
	SETUP_PRIVATE_RPORT_ATTRIBUTE_RD(port_id);
	SETUP_PRIVATE_RPORT_ATTRIBUTE_RD(roles);
	SETUP_PRIVATE_RPORT_ATTRIBUTE_RW(port_state);
	SETUP_PRIVATE_RPORT_ATTRIBUTE_RD(scsi_target_id);
	SETUP_PRIVATE_RPORT_ATTRIBUTE_RW(fast_io_fail_पंचांगo);

	BUG_ON(count > FC_RPORT_NUM_ATTRS);

	i->rport_attrs[count] = शून्य;

	/*
	 * Setup Virtual Port Attributes.
	 */
	count=0;
	SETUP_PRIVATE_VPORT_ATTRIBUTE_RD(vport_state);
	SETUP_PRIVATE_VPORT_ATTRIBUTE_RD(vport_last_state);
	SETUP_PRIVATE_VPORT_ATTRIBUTE_RD(node_name);
	SETUP_PRIVATE_VPORT_ATTRIBUTE_RD(port_name);
	SETUP_PRIVATE_VPORT_ATTRIBUTE_RD(roles);
	SETUP_PRIVATE_VPORT_ATTRIBUTE_RD(vport_type);
	SETUP_VPORT_ATTRIBUTE_RW(symbolic_name);
	SETUP_VPORT_ATTRIBUTE_WR(vport_delete);
	SETUP_VPORT_ATTRIBUTE_WR(vport_disable);

	BUG_ON(count > FC_VPORT_NUM_ATTRS);

	i->vport_attrs[count] = शून्य;

	वापस &i->t;
पूर्ण
EXPORT_SYMBOL(fc_attach_transport);

व्योम fc_release_transport(काष्ठा scsi_transport_ढाँचा *t)
अणु
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(t);

	transport_container_unरेजिस्टर(&i->t.target_attrs);
	transport_container_unरेजिस्टर(&i->t.host_attrs);
	transport_container_unरेजिस्टर(&i->rport_attr_cont);
	transport_container_unरेजिस्टर(&i->vport_attr_cont);

	kमुक्त(i);
पूर्ण
EXPORT_SYMBOL(fc_release_transport);

/**
 * fc_queue_work - Queue work to the fc_host workqueue.
 * @shost:	Poपूर्णांकer to Scsi_Host bound to fc_host.
 * @work:	Work to queue क्रम execution.
 *
 * Return value:
 * 	1 - work queued क्रम execution
 *	0 - work is alपढ़ोy queued
 *	-EINVAL - work queue करोesn't exist
 */
अटल पूर्णांक
fc_queue_work(काष्ठा Scsi_Host *shost, काष्ठा work_काष्ठा *work)
अणु
	अगर (unlikely(!fc_host_work_q(shost))) अणु
		prपूर्णांकk(KERN_ERR
			"ERROR: FC host '%s' attempted to queue work, "
			"when no workqueue created.\n", shost->hostt->name);
		dump_stack();

		वापस -EINVAL;
	पूर्ण

	वापस queue_work(fc_host_work_q(shost), work);
पूर्ण

/**
 * fc_flush_work - Flush a fc_host's workqueue.
 * @shost:	Poपूर्णांकer to Scsi_Host bound to fc_host.
 */
अटल व्योम
fc_flush_work(काष्ठा Scsi_Host *shost)
अणु
	अगर (!fc_host_work_q(shost)) अणु
		prपूर्णांकk(KERN_ERR
			"ERROR: FC host '%s' attempted to flush work, "
			"when no workqueue created.\n", shost->hostt->name);
		dump_stack();
		वापस;
	पूर्ण

	flush_workqueue(fc_host_work_q(shost));
पूर्ण

/**
 * fc_queue_devloss_work - Schedule work क्रम the fc_host devloss workqueue.
 * @shost:	Poपूर्णांकer to Scsi_Host bound to fc_host.
 * @work:	Work to queue क्रम execution.
 * @delay:	jअगरfies to delay the work queuing
 *
 * Return value:
 * 	1 on success / 0 alपढ़ोy queued / < 0 क्रम error
 */
अटल पूर्णांक
fc_queue_devloss_work(काष्ठा Scsi_Host *shost, काष्ठा delayed_work *work,
				अचिन्हित दीर्घ delay)
अणु
	अगर (unlikely(!fc_host_devloss_work_q(shost))) अणु
		prपूर्णांकk(KERN_ERR
			"ERROR: FC host '%s' attempted to queue work, "
			"when no workqueue created.\n", shost->hostt->name);
		dump_stack();

		वापस -EINVAL;
	पूर्ण

	वापस queue_delayed_work(fc_host_devloss_work_q(shost), work, delay);
पूर्ण

/**
 * fc_flush_devloss - Flush a fc_host's devloss workqueue.
 * @shost:	Poपूर्णांकer to Scsi_Host bound to fc_host.
 */
अटल व्योम
fc_flush_devloss(काष्ठा Scsi_Host *shost)
अणु
	अगर (!fc_host_devloss_work_q(shost)) अणु
		prपूर्णांकk(KERN_ERR
			"ERROR: FC host '%s' attempted to flush work, "
			"when no workqueue created.\n", shost->hostt->name);
		dump_stack();
		वापस;
	पूर्ण

	flush_workqueue(fc_host_devloss_work_q(shost));
पूर्ण


/**
 * fc_हटाओ_host - called to terminate any fc_transport-related elements क्रम a scsi host.
 * @shost:	Which &Scsi_Host
 *
 * This routine is expected to be called immediately preceding the
 * a driver's call to scsi_हटाओ_host().
 *
 * WARNING: A driver utilizing the fc_transport, which fails to call
 *   this routine prior to scsi_हटाओ_host(), will leave dangling
 *   objects in /sys/class/fc_remote_ports. Access to any of these
 *   objects can result in a प्रणाली crash !!!
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
व्योम
fc_हटाओ_host(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_vport *vport = शून्य, *next_vport = शून्य;
	काष्ठा fc_rport *rport = शून्य, *next_rport = शून्य;
	काष्ठा workqueue_काष्ठा *work_q;
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);

	/* Remove any vports */
	list_क्रम_each_entry_safe(vport, next_vport, &fc_host->vports, peers) अणु
		vport->flags |= FC_VPORT_DELETING;
		fc_queue_work(shost, &vport->vport_delete_work);
	पूर्ण

	/* Remove any remote ports */
	list_क्रम_each_entry_safe(rport, next_rport,
			&fc_host->rports, peers) अणु
		list_del(&rport->peers);
		rport->port_state = FC_PORTSTATE_DELETED;
		fc_queue_work(shost, &rport->rport_delete_work);
	पूर्ण

	list_क्रम_each_entry_safe(rport, next_rport,
			&fc_host->rport_bindings, peers) अणु
		list_del(&rport->peers);
		rport->port_state = FC_PORTSTATE_DELETED;
		fc_queue_work(shost, &rport->rport_delete_work);
	पूर्ण

	spin_unlock_irqrestore(shost->host_lock, flags);

	/* flush all scan work items */
	scsi_flush_work(shost);

	/* flush all stgt delete, and rport delete work items, then समाप्त it  */
	अगर (fc_host->work_q) अणु
		work_q = fc_host->work_q;
		fc_host->work_q = शून्य;
		destroy_workqueue(work_q);
	पूर्ण

	/* flush all devloss work items, then समाप्त it  */
	अगर (fc_host->devloss_work_q) अणु
		work_q = fc_host->devloss_work_q;
		fc_host->devloss_work_q = शून्य;
		destroy_workqueue(work_q);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fc_हटाओ_host);

अटल व्योम fc_terminate_rport_io(काष्ठा fc_rport *rport)
अणु
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);

	/* Involve the LLDD अगर possible to terminate all io on the rport. */
	अगर (i->f->terminate_rport_io)
		i->f->terminate_rport_io(rport);

	/*
	 * Must unblock to flush queued IO. scsi-ml will fail incoming reqs.
	 */
	scsi_target_unblock(&rport->dev, SDEV_TRANSPORT_OFFLINE);
पूर्ण

/**
 * fc_starget_delete - called to delete the scsi descendants of an rport
 * @work:	remote port to be operated on.
 *
 * Deletes target and all sdevs.
 */
अटल व्योम
fc_starget_delete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_rport *rport =
		container_of(work, काष्ठा fc_rport, stgt_delete_work);

	fc_terminate_rport_io(rport);
	scsi_हटाओ_target(&rport->dev);
पूर्ण


/**
 * fc_rport_final_delete - finish rport termination and delete it.
 * @work:	remote port to be deleted.
 */
अटल व्योम
fc_rport_final_delete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_rport *rport =
		container_of(work, काष्ठा fc_rport, rport_delete_work);
	काष्ठा device *dev = &rport->dev;
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	अचिन्हित दीर्घ flags;
	पूर्णांक करो_callback = 0;

	fc_terminate_rport_io(rport);

	/*
	 * अगर a scan is pending, flush the SCSI Host work_q so that
	 * that we can reclaim the rport scan work element.
	 */
	अगर (rport->flags & FC_RPORT_SCAN_PENDING)
		scsi_flush_work(shost);

	/*
	 * Cancel any outstanding समयrs. These should really exist
	 * only when rmmod'ing the LLDD and we're asking क्रम
	 * immediate termination of the rports
	 */
	spin_lock_irqsave(shost->host_lock, flags);
	अगर (rport->flags & FC_RPORT_DEVLOSS_PENDING) अणु
		spin_unlock_irqrestore(shost->host_lock, flags);
		अगर (!cancel_delayed_work(&rport->fail_io_work))
			fc_flush_devloss(shost);
		अगर (!cancel_delayed_work(&rport->dev_loss_work))
			fc_flush_devloss(shost);
		cancel_work_sync(&rport->scan_work);
		spin_lock_irqsave(shost->host_lock, flags);
		rport->flags &= ~FC_RPORT_DEVLOSS_PENDING;
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	/* Delete SCSI target and sdevs */
	अगर (rport->scsi_target_id != -1)
		fc_starget_delete(&rport->stgt_delete_work);

	/*
	 * Notअगरy the driver that the rport is now dead. The LLDD will
	 * also guarantee that any communication to the rport is terminated
	 *
	 * Aव्योम this call अगर we alपढ़ोy called it when we preserved the
	 * rport क्रम the binding.
	 */
	spin_lock_irqsave(shost->host_lock, flags);
	अगर (!(rport->flags & FC_RPORT_DEVLOSS_CALLBK_DONE) &&
	    (i->f->dev_loss_पंचांगo_callbk)) अणु
		rport->flags |= FC_RPORT_DEVLOSS_CALLBK_DONE;
		करो_callback = 1;
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	अगर (करो_callback)
		i->f->dev_loss_पंचांगo_callbk(rport);

	fc_bsg_हटाओ(rport->rqst_q);

	transport_हटाओ_device(dev);
	device_del(dev);
	transport_destroy_device(dev);
	scsi_host_put(shost);			/* क्रम fc_host->rport list */
	put_device(dev);			/* क्रम self-reference */
पूर्ण


/**
 * fc_remote_port_create - allocates and creates a remote FC port.
 * @shost:	scsi host the remote port is connected to.
 * @channel:	Channel on shost port connected to.
 * @ids:	The world wide names, fc address, and FC4 port
 *		roles क्रम the remote port.
 *
 * Allocates and creates the remoter port काष्ठाure, including the
 * class and sysfs creation.
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
अटल काष्ठा fc_rport *
fc_remote_port_create(काष्ठा Scsi_Host *shost, पूर्णांक channel,
		      काष्ठा fc_rport_identअगरiers  *ids)
अणु
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	काष्ठा fc_पूर्णांकernal *fci = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा fc_rport *rport;
	काष्ठा device *dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;
	माप_प्रकार size;

	size = (माप(काष्ठा fc_rport) + fci->f->dd_fcrport_size);
	rport = kzalloc(size, GFP_KERNEL);
	अगर (unlikely(!rport)) अणु
		prपूर्णांकk(KERN_ERR "%s: allocation failure\n", __func__);
		वापस शून्य;
	पूर्ण

	rport->maxframe_size = -1;
	rport->supported_classes = FC_COS_UNSPECIFIED;
	rport->dev_loss_पंचांगo = fc_host->dev_loss_पंचांगo;
	स_नकल(&rport->node_name, &ids->node_name, माप(rport->node_name));
	स_नकल(&rport->port_name, &ids->port_name, माप(rport->port_name));
	rport->port_id = ids->port_id;
	rport->roles = ids->roles;
	rport->port_state = FC_PORTSTATE_ONLINE;
	अगर (fci->f->dd_fcrport_size)
		rport->dd_data = &rport[1];
	rport->channel = channel;
	rport->fast_io_fail_पंचांगo = -1;

	INIT_DELAYED_WORK(&rport->dev_loss_work, fc_समयout_deleted_rport);
	INIT_DELAYED_WORK(&rport->fail_io_work, fc_समयout_fail_rport_io);
	INIT_WORK(&rport->scan_work, fc_scsi_scan_rport);
	INIT_WORK(&rport->stgt_delete_work, fc_starget_delete);
	INIT_WORK(&rport->rport_delete_work, fc_rport_final_delete);

	spin_lock_irqsave(shost->host_lock, flags);

	rport->number = fc_host->next_rport_number++;
	अगर ((rport->roles & FC_PORT_ROLE_FCP_TARGET) ||
	    (rport->roles & FC_PORT_ROLE_FCP_DUMMY_INITIATOR))
		rport->scsi_target_id = fc_host->next_target_id++;
	अन्यथा
		rport->scsi_target_id = -1;
	list_add_tail(&rport->peers, &fc_host->rports);
	scsi_host_get(shost);			/* क्रम fc_host->rport list */

	spin_unlock_irqrestore(shost->host_lock, flags);

	dev = &rport->dev;
	device_initialize(dev);			/* takes self reference */
	dev->parent = get_device(&shost->shost_gendev); /* parent reference */
	dev->release = fc_rport_dev_release;
	dev_set_name(dev, "rport-%d:%d-%d",
		     shost->host_no, channel, rport->number);
	transport_setup_device(dev);

	error = device_add(dev);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "FC Remote Port device_add failed\n");
		जाओ delete_rport;
	पूर्ण
	transport_add_device(dev);
	transport_configure_device(dev);

	fc_bsg_rportadd(shost, rport);
	/* ignore any bsg add error - we just can't करो sgio */

	अगर (rport->roles & FC_PORT_ROLE_FCP_TARGET) अणु
		/* initiate a scan of the target */
		rport->flags |= FC_RPORT_SCAN_PENDING;
		scsi_queue_work(shost, &rport->scan_work);
	पूर्ण

	वापस rport;

delete_rport:
	transport_destroy_device(dev);
	spin_lock_irqsave(shost->host_lock, flags);
	list_del(&rport->peers);
	scsi_host_put(shost);			/* क्रम fc_host->rport list */
	spin_unlock_irqrestore(shost->host_lock, flags);
	put_device(dev->parent);
	kमुक्त(rport);
	वापस शून्य;
पूर्ण

/**
 * fc_remote_port_add - notअगरy fc transport of the existence of a remote FC port.
 * @shost:	scsi host the remote port is connected to.
 * @channel:	Channel on shost port connected to.
 * @ids:	The world wide names, fc address, and FC4 port
 *		roles क्रम the remote port.
 *
 * The LLDD calls this routine to notअगरy the transport of the existence
 * of a remote port. The LLDD provides the unique identअगरiers (wwpn,wwn)
 * of the port, it's FC address (port_id), and the FC4 roles that are
 * active क्रम the port.
 *
 * For ports that are FCP tarमाला_लो (aka scsi tarमाला_लो), the FC transport
 * मुख्यtains consistent target id bindings on behalf of the LLDD.
 * A consistent target id binding is an assignment of a target id to
 * a remote port identअगरier, which persists जबतक the scsi host is
 * attached. The remote port can disappear, then later reappear, and
 * it's target id assignment reमुख्यs the same. This allows क्रम shअगरts
 * in FC addressing (अगर binding by wwpn or wwnn) with no apparent
 * changes to the scsi subप्रणाली which is based on scsi host number and
 * target id values.  Bindings are only valid during the attachment of
 * the scsi host. If the host detaches, then later re-attaches, target
 * id bindings may change.
 *
 * This routine is responsible क्रम वापसing a remote port काष्ठाure.
 * The routine will search the list of remote ports it मुख्यtains
 * पूर्णांकernally on behalf of consistent target id mappings. If found, the
 * remote port काष्ठाure will be reused. Otherwise, a new remote port
 * काष्ठाure will be allocated.
 *
 * Whenever a remote port is allocated, a new fc_remote_port class
 * device is created.
 *
 * Should not be called from पूर्णांकerrupt context.
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
काष्ठा fc_rport *
fc_remote_port_add(काष्ठा Scsi_Host *shost, पूर्णांक channel,
	काष्ठा fc_rport_identअगरiers  *ids)
अणु
	काष्ठा fc_पूर्णांकernal *fci = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	काष्ठा fc_rport *rport;
	अचिन्हित दीर्घ flags;
	पूर्णांक match = 0;

	/* ensure any stgt delete functions are करोne */
	fc_flush_work(shost);

	/*
	 * Search the list of "active" rports, क्रम an rport that has been
	 * deleted, but we've held off the real delete जबतक the target
	 * is in a "blocked" state.
	 */
	spin_lock_irqsave(shost->host_lock, flags);

	list_क्रम_each_entry(rport, &fc_host->rports, peers) अणु

		अगर ((rport->port_state == FC_PORTSTATE_BLOCKED ||
		     rport->port_state == FC_PORTSTATE_NOTPRESENT) &&
			(rport->channel == channel)) अणु

			चयन (fc_host->tgtid_bind_type) अणु
			हाल FC_TGTID_BIND_BY_WWPN:
			हाल FC_TGTID_BIND_NONE:
				अगर (rport->port_name == ids->port_name)
					match = 1;
				अवरोध;
			हाल FC_TGTID_BIND_BY_WWNN:
				अगर (rport->node_name == ids->node_name)
					match = 1;
				अवरोध;
			हाल FC_TGTID_BIND_BY_ID:
				अगर (rport->port_id == ids->port_id)
					match = 1;
				अवरोध;
			पूर्ण

			अगर (match) अणु

				स_नकल(&rport->node_name, &ids->node_name,
					माप(rport->node_name));
				स_नकल(&rport->port_name, &ids->port_name,
					माप(rport->port_name));
				rport->port_id = ids->port_id;

				rport->port_state = FC_PORTSTATE_ONLINE;
				rport->roles = ids->roles;

				spin_unlock_irqrestore(shost->host_lock, flags);

				अगर (fci->f->dd_fcrport_size)
					स_रखो(rport->dd_data, 0,
						fci->f->dd_fcrport_size);

				/*
				 * If we were not a target, cancel the
				 * io terminate and rport समयrs, and
				 * we're करोne.
				 *
				 * If we were a target, but our new role
				 * करोesn't indicate a target, leave the
				 * समयrs running expecting the role to
				 * change as the target fully logs in. If
				 * it करोesn't, the target will be torn करोwn.
				 *
				 * If we were a target, and our role shows
				 * we're still a target, cancel the समयrs
				 * and kick off a scan.
				 */

				/* was a target, not in roles */
				अगर ((rport->scsi_target_id != -1) &&
				    (!(ids->roles & FC_PORT_ROLE_FCP_TARGET)))
					वापस rport;

				/*
				 * Stop the fail io and dev_loss समयrs.
				 * If they flush, the port_state will
				 * be checked and will NOOP the function.
				 */
				अगर (!cancel_delayed_work(&rport->fail_io_work))
					fc_flush_devloss(shost);
				अगर (!cancel_delayed_work(&rport->dev_loss_work))
					fc_flush_devloss(shost);

				spin_lock_irqsave(shost->host_lock, flags);

				rport->flags &= ~(FC_RPORT_FAST_FAIL_TIMEDOUT |
						  FC_RPORT_DEVLOSS_PENDING |
						  FC_RPORT_DEVLOSS_CALLBK_DONE);

				spin_unlock_irqrestore(shost->host_lock, flags);

				/* अगर target, initiate a scan */
				अगर (rport->scsi_target_id != -1) अणु
					scsi_target_unblock(&rport->dev,
							    SDEV_RUNNING);
					spin_lock_irqsave(shost->host_lock,
							  flags);
					rport->flags |= FC_RPORT_SCAN_PENDING;
					scsi_queue_work(shost,
							&rport->scan_work);
					spin_unlock_irqrestore(shost->host_lock,
							flags);
				पूर्ण

				fc_bsg_goose_queue(rport);

				वापस rport;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Search the bindings array
	 * Note: अगर never a FCP target, you won't be on this list
	 */
	अगर (fc_host->tgtid_bind_type != FC_TGTID_BIND_NONE) अणु

		/* search क्रम a matching consistent binding */

		list_क्रम_each_entry(rport, &fc_host->rport_bindings,
					peers) अणु
			अगर (rport->channel != channel)
				जारी;

			चयन (fc_host->tgtid_bind_type) अणु
			हाल FC_TGTID_BIND_BY_WWPN:
				अगर (rport->port_name == ids->port_name)
					match = 1;
				अवरोध;
			हाल FC_TGTID_BIND_BY_WWNN:
				अगर (rport->node_name == ids->node_name)
					match = 1;
				अवरोध;
			हाल FC_TGTID_BIND_BY_ID:
				अगर (rport->port_id == ids->port_id)
					match = 1;
				अवरोध;
			हाल FC_TGTID_BIND_NONE: /* to keep compiler happy */
				अवरोध;
			पूर्ण

			अगर (match) अणु
				list_move_tail(&rport->peers, &fc_host->rports);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (match) अणु
			स_नकल(&rport->node_name, &ids->node_name,
				माप(rport->node_name));
			स_नकल(&rport->port_name, &ids->port_name,
				माप(rport->port_name));
			rport->port_id = ids->port_id;
			rport->port_state = FC_PORTSTATE_ONLINE;
			rport->flags &= ~FC_RPORT_FAST_FAIL_TIMEDOUT;

			अगर (fci->f->dd_fcrport_size)
				स_रखो(rport->dd_data, 0,
						fci->f->dd_fcrport_size);
			spin_unlock_irqrestore(shost->host_lock, flags);

			fc_remote_port_rolechg(rport, ids->roles);
			वापस rport;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(shost->host_lock, flags);

	/* No consistent binding found - create new remote port entry */
	rport = fc_remote_port_create(shost, channel, ids);

	वापस rport;
पूर्ण
EXPORT_SYMBOL(fc_remote_port_add);


/**
 * fc_remote_port_delete - notअगरies the fc transport that a remote port is no दीर्घer in existence.
 * @rport:	The remote port that no दीर्घer exists
 *
 * The LLDD calls this routine to notअगरy the transport that a remote
 * port is no दीर्घer part of the topology. Note: Although a port
 * may no दीर्घer be part of the topology, it may persist in the remote
 * ports displayed by the fc_host. We करो this under 2 conditions:
 *
 * 1) If the port was a scsi target, we delay its deletion by "blocking" it.
 *    This allows the port to temporarily disappear, then reappear without
 *    disrupting the SCSI device tree attached to it. During the "blocked"
 *    period the port will still exist.
 *
 * 2) If the port was a scsi target and disappears क्रम दीर्घer than we
 *    expect, we'll delete the port and the tear करोwn the SCSI device tree
 *    attached to it. However, we want to semi-persist the target id asचिन्हित
 *    to that port अगर it eventually करोes exist. The port काष्ठाure will
 *    reमुख्य (although with minimal inक्रमmation) so that the target id
 *    bindings also reमुख्य.
 *
 * If the remote port is not an FCP Target, it will be fully torn करोwn
 * and deallocated, including the fc_remote_port class device.
 *
 * If the remote port is an FCP Target, the port will be placed in a
 * temporary blocked state. From the LLDD's perspective, the rport no
 * दीर्घer exists. From the SCSI midlayer's perspective, the SCSI target
 * exists, but all sdevs on it are blocked from further I/O. The following
 * is then expected.
 *
 *   If the remote port करोes not वापस (संकेतed by a LLDD call to
 *   fc_remote_port_add()) within the dev_loss_पंचांगo समयout, then the
 *   scsi target is हटाओd - समाप्तing all outstanding i/o and removing the
 *   scsi devices attached to it. The port काष्ठाure will be marked Not
 *   Present and be partially cleared, leaving only enough inक्रमmation to
 *   recognize the remote port relative to the scsi target id binding अगर
 *   it later appears.  The port will reमुख्य as दीर्घ as there is a valid
 *   binding (e.g. until the user changes the binding type or unloads the
 *   scsi host with the binding).
 *
 *   If the remote port वापसs within the dev_loss_पंचांगo value (and matches
 *   according to the target id binding type), the port काष्ठाure will be
 *   reused. If it is no दीर्घer a SCSI target, the target will be torn
 *   करोwn. If it जारीs to be a SCSI target, then the target will be
 *   unblocked (allowing i/o to be resumed), and a scan will be activated
 *   to ensure that all luns are detected.
 *
 * Called from normal process context only - cannot be called from पूर्णांकerrupt.
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
व्योम
fc_remote_port_delete(काष्ठा fc_rport  *rport)
अणु
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	अचिन्हित दीर्घ समयout = rport->dev_loss_पंचांगo;
	अचिन्हित दीर्घ flags;

	/*
	 * No need to flush the fc_host work_q's, as all adds are synchronous.
	 *
	 * We करो need to reclaim the rport scan work element, so eventually
	 * (in fc_rport_final_delete()) we'll flush the scsi host work_q अगर
	 * there's still a scan pending.
	 */

	spin_lock_irqsave(shost->host_lock, flags);

	अगर ((rport->port_state != FC_PORTSTATE_ONLINE) &&
		(rport->port_state != FC_PORTSTATE_MARGINAL)) अणु
		spin_unlock_irqrestore(shost->host_lock, flags);
		वापस;
	पूर्ण

	/*
	 * In the past, we अगर this was not an FCP-Target, we would
	 * unconditionally just jump to deleting the rport.
	 * However, rports can be used as node containers by the LLDD,
	 * and its not appropriate to just terminate the rport at the
	 * first sign of a loss in connectivity. The LLDD may want to
	 * send ELS traffic to re-validate the login. If the rport is
	 * immediately deleted, it makes it inappropriate क्रम a node
	 * container.
	 * So... we now unconditionally रुको dev_loss_पंचांगo beक्रमe
	 * destroying an rport.
	 */

	rport->port_state = FC_PORTSTATE_BLOCKED;

	rport->flags |= FC_RPORT_DEVLOSS_PENDING;

	spin_unlock_irqrestore(shost->host_lock, flags);

	scsi_target_block(&rport->dev);

	/* see अगर we need to समाप्त io faster than रुकोing क्रम device loss */
	अगर ((rport->fast_io_fail_पंचांगo != -1) &&
	    (rport->fast_io_fail_पंचांगo < समयout))
		fc_queue_devloss_work(shost, &rport->fail_io_work,
					rport->fast_io_fail_पंचांगo * HZ);

	/* cap the length the devices can be blocked until they are deleted */
	fc_queue_devloss_work(shost, &rport->dev_loss_work, समयout * HZ);
पूर्ण
EXPORT_SYMBOL(fc_remote_port_delete);

/**
 * fc_remote_port_rolechg - notअगरies the fc transport that the roles on a remote may have changed.
 * @rport:	The remote port that changed.
 * @roles:      New roles क्रम this port.
 *
 * Description: The LLDD calls this routine to notअगरy the transport that the
 * roles on a remote port may have changed. The largest effect of this is
 * अगर a port now becomes a FCP Target, it must be allocated a
 * scsi target id.  If the port is no दीर्घer a FCP target, any
 * scsi target id value asचिन्हित to it will persist in हाल the
 * role changes back to include FCP Target. No changes in the scsi
 * midlayer will be invoked अगर the role changes (in the expectation
 * that the role will be resumed. If it करोesn't normal error processing
 * will take place).
 *
 * Should not be called from पूर्णांकerrupt context.
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
व्योम
fc_remote_port_rolechg(काष्ठा fc_rport  *rport, u32 roles)
अणु
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	अचिन्हित दीर्घ flags;
	पूर्णांक create = 0;

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (roles & FC_PORT_ROLE_FCP_TARGET) अणु
		अगर (rport->scsi_target_id == -1) अणु
			rport->scsi_target_id = fc_host->next_target_id++;
			create = 1;
		पूर्ण अन्यथा अगर (!(rport->roles & FC_PORT_ROLE_FCP_TARGET))
			create = 1;
	पूर्ण

	rport->roles = roles;

	spin_unlock_irqrestore(shost->host_lock, flags);

	अगर (create) अणु
		/*
		 * There may have been a delete समयr running on the
		 * port. Ensure that it is cancelled as we now know
		 * the port is an FCP Target.
		 * Note: we know the rport exists and is in an online
		 *  state as the LLDD would not have had an rport
		 *  reference to pass us.
		 *
		 * Take no action on the del_समयr failure as the state
		 * machine state change will validate the
		 * transaction.
		 */
		अगर (!cancel_delayed_work(&rport->fail_io_work))
			fc_flush_devloss(shost);
		अगर (!cancel_delayed_work(&rport->dev_loss_work))
			fc_flush_devloss(shost);

		spin_lock_irqsave(shost->host_lock, flags);
		rport->flags &= ~(FC_RPORT_FAST_FAIL_TIMEDOUT |
				  FC_RPORT_DEVLOSS_PENDING |
				  FC_RPORT_DEVLOSS_CALLBK_DONE);
		spin_unlock_irqrestore(shost->host_lock, flags);

		/* ensure any stgt delete functions are करोne */
		fc_flush_work(shost);

		scsi_target_unblock(&rport->dev, SDEV_RUNNING);
		/* initiate a scan of the target */
		spin_lock_irqsave(shost->host_lock, flags);
		rport->flags |= FC_RPORT_SCAN_PENDING;
		scsi_queue_work(shost, &rport->scan_work);
		spin_unlock_irqrestore(shost->host_lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fc_remote_port_rolechg);

/**
 * fc_समयout_deleted_rport - Timeout handler क्रम a deleted remote port.
 * @work:	rport target that failed to reappear in the allotted समय.
 *
 * Description: An attempt to delete a remote port blocks, and अगर it fails
 *              to वापस in the allotted समय this माला_लो called.
 */
अटल व्योम
fc_समयout_deleted_rport(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_rport *rport =
		container_of(work, काष्ठा fc_rport, dev_loss_work.work);
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	अचिन्हित दीर्घ flags;
	पूर्णांक करो_callback = 0;

	spin_lock_irqsave(shost->host_lock, flags);

	rport->flags &= ~FC_RPORT_DEVLOSS_PENDING;

	/*
	 * If the port is ONLINE, then it came back. If it was a SCSI
	 * target, validate it still is. If not, tear करोwn the
	 * scsi_target on it.
	 */
	अगर (((rport->port_state == FC_PORTSTATE_ONLINE) ||
		(rport->port_state == FC_PORTSTATE_MARGINAL)) &&
	    (rport->scsi_target_id != -1) &&
	    !(rport->roles & FC_PORT_ROLE_FCP_TARGET)) अणु
		dev_prपूर्णांकk(KERN_ERR, &rport->dev,
			"blocked FC remote port time out: no longer"
			" a FCP target, removing starget\n");
		spin_unlock_irqrestore(shost->host_lock, flags);
		scsi_target_unblock(&rport->dev, SDEV_TRANSPORT_OFFLINE);
		fc_queue_work(shost, &rport->stgt_delete_work);
		वापस;
	पूर्ण

	/* NOOP state - we're flushing workq's */
	अगर (rport->port_state != FC_PORTSTATE_BLOCKED) अणु
		spin_unlock_irqrestore(shost->host_lock, flags);
		dev_prपूर्णांकk(KERN_ERR, &rport->dev,
			"blocked FC remote port time out: leaving"
			" rport%s alone\n",
			(rport->scsi_target_id != -1) ?  " and starget" : "");
		वापस;
	पूर्ण

	अगर ((fc_host->tgtid_bind_type == FC_TGTID_BIND_NONE) ||
	    (rport->scsi_target_id == -1)) अणु
		list_del(&rport->peers);
		rport->port_state = FC_PORTSTATE_DELETED;
		dev_prपूर्णांकk(KERN_ERR, &rport->dev,
			"blocked FC remote port time out: removing"
			" rport%s\n",
			(rport->scsi_target_id != -1) ?  " and starget" : "");
		fc_queue_work(shost, &rport->rport_delete_work);
		spin_unlock_irqrestore(shost->host_lock, flags);
		वापस;
	पूर्ण

	dev_prपूर्णांकk(KERN_ERR, &rport->dev,
		"blocked FC remote port time out: removing target and "
		"saving binding\n");

	list_move_tail(&rport->peers, &fc_host->rport_bindings);

	/*
	 * Note: We करो not हटाओ or clear the hostdata area. This allows
	 *   host-specअगरic target data to persist aदीर्घ with the
	 *   scsi_target_id. It's up to the host to manage it's hostdata area.
	 */

	/*
	 * Reinitialize port attributes that may change अगर the port comes back.
	 */
	rport->maxframe_size = -1;
	rport->supported_classes = FC_COS_UNSPECIFIED;
	rport->roles = FC_PORT_ROLE_UNKNOWN;
	rport->port_state = FC_PORTSTATE_NOTPRESENT;
	rport->flags &= ~FC_RPORT_FAST_FAIL_TIMEDOUT;

	/*
	 * Pre-emptively समाप्त I/O rather than रुकोing क्रम the work queue
	 * item to tearकरोwn the starget. (FCOE libFC folks prefer this
	 * and to have the rport_port_id still set when it's करोne).
	 */
	spin_unlock_irqrestore(shost->host_lock, flags);
	fc_terminate_rport_io(rport);

	spin_lock_irqsave(shost->host_lock, flags);

	अगर (rport->port_state == FC_PORTSTATE_NOTPRESENT) अणु	/* still missing */

		/* हटाओ the identअगरiers that aren't used in the consisting binding */
		चयन (fc_host->tgtid_bind_type) अणु
		हाल FC_TGTID_BIND_BY_WWPN:
			rport->node_name = -1;
			rport->port_id = -1;
			अवरोध;
		हाल FC_TGTID_BIND_BY_WWNN:
			rport->port_name = -1;
			rport->port_id = -1;
			अवरोध;
		हाल FC_TGTID_BIND_BY_ID:
			rport->node_name = -1;
			rport->port_name = -1;
			अवरोध;
		हाल FC_TGTID_BIND_NONE:	/* to keep compiler happy */
			अवरोध;
		पूर्ण

		/*
		 * As this only occurs अगर the remote port (scsi target)
		 * went away and didn't come back - we'll हटाओ
		 * all attached scsi devices.
		 */
		rport->flags |= FC_RPORT_DEVLOSS_CALLBK_DONE;
		fc_queue_work(shost, &rport->stgt_delete_work);

		करो_callback = 1;
	पूर्ण

	spin_unlock_irqrestore(shost->host_lock, flags);

	/*
	 * Notअगरy the driver that the rport is now dead. The LLDD will
	 * also guarantee that any communication to the rport is terminated
	 *
	 * Note: we set the CALLBK_DONE flag above to correspond
	 */
	अगर (करो_callback && i->f->dev_loss_पंचांगo_callbk)
		i->f->dev_loss_पंचांगo_callbk(rport);
पूर्ण


/**
 * fc_समयout_fail_rport_io - Timeout handler क्रम a fast io failing on a disconnected SCSI target.
 * @work:	rport to terminate io on.
 *
 * Notes: Only requests the failure of the io, not that all are flushed
 *    prior to वापसing.
 */
अटल व्योम
fc_समयout_fail_rport_io(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_rport *rport =
		container_of(work, काष्ठा fc_rport, fail_io_work.work);

	अगर (rport->port_state != FC_PORTSTATE_BLOCKED)
		वापस;

	rport->flags |= FC_RPORT_FAST_FAIL_TIMEDOUT;
	fc_terminate_rport_io(rport);
पूर्ण

/**
 * fc_scsi_scan_rport - called to perक्रमm a scsi scan on a remote port.
 * @work:	remote port to be scanned.
 */
अटल व्योम
fc_scsi_scan_rport(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_rport *rport =
		container_of(work, काष्ठा fc_rport, scan_work);
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	अचिन्हित दीर्घ flags;

	अगर (((rport->port_state == FC_PORTSTATE_ONLINE) ||
		(rport->port_state == FC_PORTSTATE_MARGINAL)) &&
	    (rport->roles & FC_PORT_ROLE_FCP_TARGET) &&
	    !(i->f->disable_target_scan)) अणु
		scsi_scan_target(&rport->dev, rport->channel,
				 rport->scsi_target_id, SCAN_WILD_CARD,
				 SCSI_SCAN_RESCAN);
	पूर्ण

	spin_lock_irqsave(shost->host_lock, flags);
	rport->flags &= ~FC_RPORT_SCAN_PENDING;
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

/**
 * fc_block_rport() - Block SCSI eh thपढ़ो क्रम blocked fc_rport.
 * @rport: Remote port that scsi_eh is trying to recover.
 *
 * This routine can be called from a FC LLD scsi_eh callback. It
 * blocks the scsi_eh thपढ़ो until the fc_rport leaves the
 * FC_PORTSTATE_BLOCKED, or the fast_io_fail_पंचांगo fires. This is
 * necessary to aव्योम the scsi_eh failing recovery actions क्रम blocked
 * rports which would lead to offlined SCSI devices.
 *
 * Returns: 0 अगर the fc_rport left the state FC_PORTSTATE_BLOCKED.
 *	    FAST_IO_FAIL अगर the fast_io_fail_पंचांगo fired, this should be
 *	    passed back to scsi_eh.
 */
पूर्णांक fc_block_rport(काष्ठा fc_rport *rport)
अणु
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	जबतक (rport->port_state == FC_PORTSTATE_BLOCKED &&
	       !(rport->flags & FC_RPORT_FAST_FAIL_TIMEDOUT)) अणु
		spin_unlock_irqrestore(shost->host_lock, flags);
		msleep(1000);
		spin_lock_irqsave(shost->host_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	अगर (rport->flags & FC_RPORT_FAST_FAIL_TIMEDOUT)
		वापस FAST_IO_FAIL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_block_rport);

/**
 * fc_block_scsi_eh - Block SCSI eh thपढ़ो क्रम blocked fc_rport
 * @cmnd: SCSI command that scsi_eh is trying to recover
 *
 * This routine can be called from a FC LLD scsi_eh callback. It
 * blocks the scsi_eh thपढ़ो until the fc_rport leaves the
 * FC_PORTSTATE_BLOCKED, or the fast_io_fail_पंचांगo fires. This is
 * necessary to aव्योम the scsi_eh failing recovery actions क्रम blocked
 * rports which would lead to offlined SCSI devices.
 *
 * Returns: 0 अगर the fc_rport left the state FC_PORTSTATE_BLOCKED.
 *	    FAST_IO_FAIL अगर the fast_io_fail_पंचांगo fired, this should be
 *	    passed back to scsi_eh.
 */
पूर्णांक fc_block_scsi_eh(काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(cmnd->device));

	अगर (WARN_ON_ONCE(!rport))
		वापस FAST_IO_FAIL;

	वापस fc_block_rport(rport);
पूर्ण
EXPORT_SYMBOL(fc_block_scsi_eh);

/*
 * fc_eh_should_retry_cmd - Checks अगर the cmd should be retried or not
 * @scmd:        The SCSI command to be checked
 *
 * This checks the rport state to decide अगर a cmd is
 * retryable.
 *
 * Returns: true अगर the rport state is not in marginal state.
 */
bool fc_eh_should_retry_cmd(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(scmd->device));

	अगर ((rport->port_state != FC_PORTSTATE_ONLINE) &&
		(scmd->request->cmd_flags & REQ_FAILFAST_TRANSPORT)) अणु
		set_host_byte(scmd, DID_TRANSPORT_MARGINAL);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(fc_eh_should_retry_cmd);

/**
 * fc_vport_setup - allocates and creates a FC भव port.
 * @shost:	scsi host the भव port is connected to.
 * @channel:	Channel on shost port connected to.
 * @pdev:	parent device क्रम vport
 * @ids:	The world wide names, FC4 port roles, etc क्रम
 *              the भव port.
 * @ret_vport:	The poपूर्णांकer to the created vport.
 *
 * Allocates and creates the vport काष्ठाure, calls the parent host
 * to instantiate the vport, this completes w/ class and sysfs creation.
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
अटल पूर्णांक
fc_vport_setup(काष्ठा Scsi_Host *shost, पूर्णांक channel, काष्ठा device *pdev,
	काष्ठा fc_vport_identअगरiers  *ids, काष्ठा fc_vport **ret_vport)
अणु
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	काष्ठा fc_पूर्णांकernal *fci = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा fc_vport *vport;
	काष्ठा device *dev;
	अचिन्हित दीर्घ flags;
	माप_प्रकार size;
	पूर्णांक error;

	*ret_vport = शून्य;

	अगर ( ! fci->f->vport_create)
		वापस -ENOENT;

	size = (माप(काष्ठा fc_vport) + fci->f->dd_fcvport_size);
	vport = kzalloc(size, GFP_KERNEL);
	अगर (unlikely(!vport)) अणु
		prपूर्णांकk(KERN_ERR "%s: allocation failure\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	vport->vport_state = FC_VPORT_UNKNOWN;
	vport->vport_last_state = FC_VPORT_UNKNOWN;
	vport->node_name = ids->node_name;
	vport->port_name = ids->port_name;
	vport->roles = ids->roles;
	vport->vport_type = ids->vport_type;
	अगर (fci->f->dd_fcvport_size)
		vport->dd_data = &vport[1];
	vport->shost = shost;
	vport->channel = channel;
	vport->flags = FC_VPORT_CREATING;
	INIT_WORK(&vport->vport_delete_work, fc_vport_sched_delete);

	spin_lock_irqsave(shost->host_lock, flags);

	अगर (fc_host->npiv_vports_inuse >= fc_host->max_npiv_vports) अणु
		spin_unlock_irqrestore(shost->host_lock, flags);
		kमुक्त(vport);
		वापस -ENOSPC;
	पूर्ण
	fc_host->npiv_vports_inuse++;
	vport->number = fc_host->next_vport_number++;
	list_add_tail(&vport->peers, &fc_host->vports);
	scsi_host_get(shost);			/* क्रम fc_host->vport list */

	spin_unlock_irqrestore(shost->host_lock, flags);

	dev = &vport->dev;
	device_initialize(dev);			/* takes self reference */
	dev->parent = get_device(pdev);		/* takes parent reference */
	dev->release = fc_vport_dev_release;
	dev_set_name(dev, "vport-%d:%d-%d",
		     shost->host_no, channel, vport->number);
	transport_setup_device(dev);

	error = device_add(dev);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "FC Virtual Port device_add failed\n");
		जाओ delete_vport;
	पूर्ण
	transport_add_device(dev);
	transport_configure_device(dev);

	error = fci->f->vport_create(vport, ids->disable);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "FC Virtual Port LLDD Create failed\n");
		जाओ delete_vport_all;
	पूर्ण

	/*
	 * अगर the parent isn't the physical adapter's Scsi_Host, ensure
	 * the Scsi_Host at least contains a symlink to the vport.
	 */
	अगर (pdev != &shost->shost_gendev) अणु
		error = sysfs_create_link(&shost->shost_gendev.kobj,
				 &dev->kobj, dev_name(dev));
		अगर (error)
			prपूर्णांकk(KERN_ERR
				"%s: Cannot create vport symlinks for "
				"%s, err=%d\n",
				__func__, dev_name(dev), error);
	पूर्ण
	spin_lock_irqsave(shost->host_lock, flags);
	vport->flags &= ~FC_VPORT_CREATING;
	spin_unlock_irqrestore(shost->host_lock, flags);

	dev_prपूर्णांकk(KERN_NOTICE, pdev,
			"%s created via shost%d channel %d\n", dev_name(dev),
			shost->host_no, channel);

	*ret_vport = vport;

	वापस 0;

delete_vport_all:
	transport_हटाओ_device(dev);
	device_del(dev);
delete_vport:
	transport_destroy_device(dev);
	spin_lock_irqsave(shost->host_lock, flags);
	list_del(&vport->peers);
	scsi_host_put(shost);			/* क्रम fc_host->vport list */
	fc_host->npiv_vports_inuse--;
	spin_unlock_irqrestore(shost->host_lock, flags);
	put_device(dev->parent);
	kमुक्त(vport);

	वापस error;
पूर्ण

/**
 * fc_vport_create - Admin App or LLDD requests creation of a vport
 * @shost:	scsi host the भव port is connected to.
 * @channel:	channel on shost port connected to.
 * @ids:	The world wide names, FC4 port roles, etc क्रम
 *              the भव port.
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
काष्ठा fc_vport *
fc_vport_create(काष्ठा Scsi_Host *shost, पूर्णांक channel,
	काष्ठा fc_vport_identअगरiers *ids)
अणु
	पूर्णांक stat;
	काष्ठा fc_vport *vport;

	stat = fc_vport_setup(shost, channel, &shost->shost_gendev,
		 ids, &vport);
	वापस stat ? शून्य : vport;
पूर्ण
EXPORT_SYMBOL(fc_vport_create);

/**
 * fc_vport_terminate - Admin App or LLDD requests termination of a vport
 * @vport:	fc_vport to be terminated
 *
 * Calls the LLDD vport_delete() function, then deallocates and हटाओs
 * the vport from the shost and object tree.
 *
 * Notes:
 *	This routine assumes no locks are held on entry.
 */
पूर्णांक
fc_vport_terminate(काष्ठा fc_vport *vport)
अणु
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(shost);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा device *dev = &vport->dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक stat;

	अगर (i->f->vport_delete)
		stat = i->f->vport_delete(vport);
	अन्यथा
		stat = -ENOENT;

	spin_lock_irqsave(shost->host_lock, flags);
	vport->flags &= ~FC_VPORT_DELETING;
	अगर (!stat) अणु
		vport->flags |= FC_VPORT_DELETED;
		list_del(&vport->peers);
		fc_host->npiv_vports_inuse--;
		scsi_host_put(shost);		/* क्रम fc_host->vport list */
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	अगर (stat)
		वापस stat;

	अगर (dev->parent != &shost->shost_gendev)
		sysfs_हटाओ_link(&shost->shost_gendev.kobj, dev_name(dev));
	transport_हटाओ_device(dev);
	device_del(dev);
	transport_destroy_device(dev);

	/*
	 * Removing our self-reference should mean our
	 * release function माला_लो called, which will drop the reमुख्यing
	 * parent reference and मुक्त the data काष्ठाure.
	 */
	put_device(dev);			/* क्रम self-reference */

	वापस 0; /* SUCCESS */
पूर्ण
EXPORT_SYMBOL(fc_vport_terminate);

/**
 * fc_vport_sched_delete - workq-based delete request क्रम a vport
 * @work:	vport to be deleted.
 */
अटल व्योम
fc_vport_sched_delete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_vport *vport =
		container_of(work, काष्ठा fc_vport, vport_delete_work);
	पूर्णांक stat;

	stat = fc_vport_terminate(vport);
	अगर (stat)
		dev_prपूर्णांकk(KERN_ERR, vport->dev.parent,
			"%s: %s could not be deleted created via "
			"shost%d channel %d - error %d\n", __func__,
			dev_name(&vport->dev), vport->shost->host_no,
			vport->channel, stat);
पूर्ण


/*
 * BSG support
 */

/**
 * fc_bsg_job_समयout - handler क्रम when a bsg request बारout
 * @req:	request that समयd out
 */
अटल क्रमागत blk_eh_समयr_वापस
fc_bsg_job_समयout(काष्ठा request *req)
अणु
	काष्ठा bsg_job *job = blk_mq_rq_to_pdu(req);
	काष्ठा Scsi_Host *shost = fc_bsg_to_shost(job);
	काष्ठा fc_rport *rport = fc_bsg_to_rport(job);
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	पूर्णांक err = 0, inflight = 0;

	अगर (rport && rport->port_state == FC_PORTSTATE_BLOCKED)
		वापस BLK_EH_RESET_TIMER;

	inflight = bsg_job_get(job);

	अगर (inflight && i->f->bsg_समयout) अणु
		/* call LLDD to पात the i/o as it has समयd out */
		err = i->f->bsg_समयout(job);
		अगर (err == -EAGAIN) अणु
			bsg_job_put(job);
			वापस BLK_EH_RESET_TIMER;
		पूर्ण अन्यथा अगर (err)
			prपूर्णांकk(KERN_ERR "ERROR: FC BSG request timeout - LLD "
				"abort failed with status %d\n", err);
	पूर्ण

	/* the blk_end_sync_io() करोesn't check the error */
	अगर (inflight)
		blk_mq_end_request(req, BLK_STS_IOERR);
	वापस BLK_EH_DONE;
पूर्ण

/**
 * fc_bsg_host_dispatch - process fc host bsg requests and dispatch to LLDD
 * @shost:	scsi host rport attached to
 * @job:	bsg job to be processed
 */
अटल पूर्णांक fc_bsg_host_dispatch(काष्ठा Scsi_Host *shost, काष्ठा bsg_job *job)
अणु
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा fc_bsg_reply *bsg_reply = job->reply;
	पूर्णांक cmdlen = माप(uपूर्णांक32_t);	/* start with length of msgcode */
	पूर्णांक ret;

	/* check अगर we really have all the request data needed */
	अगर (job->request_len < cmdlen) अणु
		ret = -ENOMSG;
		जाओ fail_host_msg;
	पूर्ण

	/* Validate the host command */
	चयन (bsg_request->msgcode) अणु
	हाल FC_BSG_HST_ADD_RPORT:
		cmdlen += माप(काष्ठा fc_bsg_host_add_rport);
		अवरोध;

	हाल FC_BSG_HST_DEL_RPORT:
		cmdlen += माप(काष्ठा fc_bsg_host_del_rport);
		अवरोध;

	हाल FC_BSG_HST_ELS_NOLOGIN:
		cmdlen += माप(काष्ठा fc_bsg_host_els);
		/* there better be a xmt and rcv payloads */
		अगर ((!job->request_payload.payload_len) ||
		    (!job->reply_payload.payload_len)) अणु
			ret = -EINVAL;
			जाओ fail_host_msg;
		पूर्ण
		अवरोध;

	हाल FC_BSG_HST_CT:
		cmdlen += माप(काष्ठा fc_bsg_host_ct);
		/* there better be xmt and rcv payloads */
		अगर ((!job->request_payload.payload_len) ||
		    (!job->reply_payload.payload_len)) अणु
			ret = -EINVAL;
			जाओ fail_host_msg;
		पूर्ण
		अवरोध;

	हाल FC_BSG_HST_VENDOR:
		cmdlen += माप(काष्ठा fc_bsg_host_venकरोr);
		अगर ((shost->hostt->venकरोr_id == 0L) ||
		    (bsg_request->rqst_data.h_venकरोr.venकरोr_id !=
			shost->hostt->venकरोr_id)) अणु
			ret = -ESRCH;
			जाओ fail_host_msg;
		पूर्ण
		अवरोध;

	शेष:
		ret = -EBADR;
		जाओ fail_host_msg;
	पूर्ण

	ret = i->f->bsg_request(job);
	अगर (!ret)
		वापस 0;

fail_host_msg:
	/* वापस the त्रुटि_सं failure code as the only status */
	BUG_ON(job->reply_len < माप(uपूर्णांक32_t));
	bsg_reply->reply_payload_rcv_len = 0;
	bsg_reply->result = ret;
	job->reply_len = माप(uपूर्णांक32_t);
	bsg_job_करोne(job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस 0;
पूर्ण


/*
 * fc_bsg_goose_queue - restart rport queue in हाल it was stopped
 * @rport:	rport to be restarted
 */
अटल व्योम
fc_bsg_goose_queue(काष्ठा fc_rport *rport)
अणु
	काष्ठा request_queue *q = rport->rqst_q;

	अगर (q)
		blk_mq_run_hw_queues(q, true);
पूर्ण

/**
 * fc_bsg_rport_dispatch - process rport bsg requests and dispatch to LLDD
 * @shost:	scsi host rport attached to
 * @job:	bsg job to be processed
 */
अटल पूर्णांक fc_bsg_rport_dispatch(काष्ठा Scsi_Host *shost, काष्ठा bsg_job *job)
अणु
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा fc_bsg_reply *bsg_reply = job->reply;
	पूर्णांक cmdlen = माप(uपूर्णांक32_t);	/* start with length of msgcode */
	पूर्णांक ret;

	/* check अगर we really have all the request data needed */
	अगर (job->request_len < cmdlen) अणु
		ret = -ENOMSG;
		जाओ fail_rport_msg;
	पूर्ण

	/* Validate the rport command */
	चयन (bsg_request->msgcode) अणु
	हाल FC_BSG_RPT_ELS:
		cmdlen += माप(काष्ठा fc_bsg_rport_els);
		जाओ check_bidi;

	हाल FC_BSG_RPT_CT:
		cmdlen += माप(काष्ठा fc_bsg_rport_ct);
check_bidi:
		/* there better be xmt and rcv payloads */
		अगर ((!job->request_payload.payload_len) ||
		    (!job->reply_payload.payload_len)) अणु
			ret = -EINVAL;
			जाओ fail_rport_msg;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EBADR;
		जाओ fail_rport_msg;
	पूर्ण

	ret = i->f->bsg_request(job);
	अगर (!ret)
		वापस 0;

fail_rport_msg:
	/* वापस the त्रुटि_सं failure code as the only status */
	BUG_ON(job->reply_len < माप(uपूर्णांक32_t));
	bsg_reply->reply_payload_rcv_len = 0;
	bsg_reply->result = ret;
	job->reply_len = माप(uपूर्णांक32_t);
	bsg_job_करोne(job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस 0;
पूर्ण

अटल पूर्णांक fc_bsg_dispatch(काष्ठा bsg_job *job)
अणु
	काष्ठा Scsi_Host *shost = fc_bsg_to_shost(job);

	अगर (scsi_is_fc_rport(job->dev))
		वापस fc_bsg_rport_dispatch(shost, job);
	अन्यथा
		वापस fc_bsg_host_dispatch(shost, job);
पूर्ण

अटल blk_status_t fc_bsg_rport_prep(काष्ठा fc_rport *rport)
अणु
	अगर (rport->port_state == FC_PORTSTATE_BLOCKED &&
	    !(rport->flags & FC_RPORT_FAST_FAIL_TIMEDOUT))
		वापस BLK_STS_RESOURCE;

	अगर ((rport->port_state != FC_PORTSTATE_ONLINE) &&
		(rport->port_state != FC_PORTSTATE_MARGINAL))
		वापस BLK_STS_IOERR;

	वापस BLK_STS_OK;
पूर्ण


अटल पूर्णांक fc_bsg_dispatch_prep(काष्ठा bsg_job *job)
अणु
	काष्ठा fc_rport *rport = fc_bsg_to_rport(job);
	blk_status_t ret;

	ret = fc_bsg_rport_prep(rport);
	चयन (ret) अणु
	हाल BLK_STS_OK:
		अवरोध;
	हाल BLK_STS_RESOURCE:
		वापस -EAGAIN;
	शेष:
		वापस -EIO;
	पूर्ण

	वापस fc_bsg_dispatch(job);
पूर्ण

/**
 * fc_bsg_hostadd - Create and add the bsg hooks so we can receive requests
 * @shost:	shost क्रम fc_host
 * @fc_host:	fc_host adding the काष्ठाures to
 */
अटल पूर्णांक
fc_bsg_hostadd(काष्ठा Scsi_Host *shost, काष्ठा fc_host_attrs *fc_host)
अणु
	काष्ठा device *dev = &shost->shost_gendev;
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा request_queue *q;
	अक्षर bsg_name[20];

	fc_host->rqst_q = शून्य;

	अगर (!i->f->bsg_request)
		वापस -ENOTSUPP;

	snम_लिखो(bsg_name, माप(bsg_name),
		 "fc_host%d", shost->host_no);

	q = bsg_setup_queue(dev, bsg_name, fc_bsg_dispatch, fc_bsg_job_समयout,
				i->f->dd_bsg_size);
	अगर (IS_ERR(q)) अणु
		dev_err(dev,
			"fc_host%d: bsg interface failed to initialize - setup queue\n",
			shost->host_no);
		वापस PTR_ERR(q);
	पूर्ण
	__scsi_init_queue(shost, q);
	blk_queue_rq_समयout(q, FC_DEFAULT_BSG_TIMEOUT);
	fc_host->rqst_q = q;
	वापस 0;
पूर्ण

/**
 * fc_bsg_rportadd - Create and add the bsg hooks so we can receive requests
 * @shost:	shost that rport is attached to
 * @rport:	rport that the bsg hooks are being attached to
 */
अटल पूर्णांक
fc_bsg_rportadd(काष्ठा Scsi_Host *shost, काष्ठा fc_rport *rport)
अणु
	काष्ठा device *dev = &rport->dev;
	काष्ठा fc_पूर्णांकernal *i = to_fc_पूर्णांकernal(shost->transportt);
	काष्ठा request_queue *q;

	rport->rqst_q = शून्य;

	अगर (!i->f->bsg_request)
		वापस -ENOTSUPP;

	q = bsg_setup_queue(dev, dev_name(dev), fc_bsg_dispatch_prep,
				fc_bsg_job_समयout, i->f->dd_bsg_size);
	अगर (IS_ERR(q)) अणु
		dev_err(dev, "failed to setup bsg queue\n");
		वापस PTR_ERR(q);
	पूर्ण
	__scsi_init_queue(shost, q);
	blk_queue_rq_समयout(q, BLK_DEFAULT_SG_TIMEOUT);
	rport->rqst_q = q;
	वापस 0;
पूर्ण


/**
 * fc_bsg_हटाओ - Deletes the bsg hooks on fchosts/rports
 * @q:	the request_queue that is to be torn करोwn.
 *
 * Notes:
 *   Beक्रमe unरेजिस्टरing the queue empty any requests that are blocked
 *
 *
 */
अटल व्योम
fc_bsg_हटाओ(काष्ठा request_queue *q)
अणु
	bsg_हटाओ_queue(q);
पूर्ण


/* Original Author:  Martin Hicks */
MODULE_AUTHOR("James Smart");
MODULE_DESCRIPTION("FC Transport Attributes");
MODULE_LICENSE("GPL");

module_init(fc_transport_init);
module_निकास(fc_transport_निकास);
