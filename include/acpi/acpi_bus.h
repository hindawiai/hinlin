<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  acpi_bus.h - ACPI Bus Driver ($Revision: 22 $)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#अगर_अघोषित __ACPI_BUS_H__
#घोषणा __ACPI_BUS_H__

#समावेश <linux/device.h>
#समावेश <linux/property.h>

/* TBD: Make dynamic */
#घोषणा ACPI_MAX_HANDLES	10
काष्ठा acpi_handle_list अणु
	u32 count;
	acpi_handle handles[ACPI_MAX_HANDLES];
पूर्ण;

/* acpi_utils.h */
acpi_status
acpi_extract_package(जोड़ acpi_object *package,
		     काष्ठा acpi_buffer *क्रमmat, काष्ठा acpi_buffer *buffer);
acpi_status
acpi_evaluate_पूर्णांकeger(acpi_handle handle,
		      acpi_string pathname,
		      काष्ठा acpi_object_list *arguments, अचिन्हित दीर्घ दीर्घ *data);
acpi_status
acpi_evaluate_reference(acpi_handle handle,
			acpi_string pathname,
			काष्ठा acpi_object_list *arguments,
			काष्ठा acpi_handle_list *list);
acpi_status
acpi_evaluate_ost(acpi_handle handle, u32 source_event, u32 status_code,
		  काष्ठा acpi_buffer *status_buf);

acpi_status
acpi_get_physical_device_location(acpi_handle handle, काष्ठा acpi_pld_info **pld);

bool acpi_has_method(acpi_handle handle, अक्षर *name);
acpi_status acpi_execute_simple_method(acpi_handle handle, अक्षर *method,
				       u64 arg);
acpi_status acpi_evaluate_ej0(acpi_handle handle);
acpi_status acpi_evaluate_lck(acpi_handle handle, पूर्णांक lock);
acpi_status acpi_evaluate_reg(acpi_handle handle, u8 space_id, u32 function);
bool acpi_ata_match(acpi_handle handle);
bool acpi_bay_match(acpi_handle handle);
bool acpi_करोck_match(acpi_handle handle);

bool acpi_check_dsm(acpi_handle handle, स्थिर guid_t *guid, u64 rev, u64 funcs);
जोड़ acpi_object *acpi_evaluate_dsm(acpi_handle handle, स्थिर guid_t *guid,
			u64 rev, u64 func, जोड़ acpi_object *argv4);

अटल अंतरभूत जोड़ acpi_object *
acpi_evaluate_dsm_typed(acpi_handle handle, स्थिर guid_t *guid, u64 rev,
			u64 func, जोड़ acpi_object *argv4,
			acpi_object_type type)
अणु
	जोड़ acpi_object *obj;

	obj = acpi_evaluate_dsm(handle, guid, rev, func, argv4);
	अगर (obj && obj->type != type) अणु
		ACPI_FREE(obj);
		obj = शून्य;
	पूर्ण

	वापस obj;
पूर्ण

#घोषणा	ACPI_INIT_DSM_ARGV4(cnt, eles)			\
	अणु						\
	  .package.type = ACPI_TYPE_PACKAGE,		\
	  .package.count = (cnt),			\
	  .package.elements = (eles)			\
	पूर्ण

bool acpi_dev_found(स्थिर अक्षर *hid);
bool acpi_dev_present(स्थिर अक्षर *hid, स्थिर अक्षर *uid, s64 hrv);
bool acpi_reduced_hardware(व्योम);

#अगर_घोषित CONFIG_ACPI

काष्ठा proc_dir_entry;

#घोषणा ACPI_BUS_खाता_ROOT	"acpi"
बाह्य काष्ठा proc_dir_entry *acpi_root_dir;

क्रमागत acpi_bus_device_type अणु
	ACPI_BUS_TYPE_DEVICE = 0,
	ACPI_BUS_TYPE_POWER,
	ACPI_BUS_TYPE_PROCESSOR,
	ACPI_BUS_TYPE_THERMAL,
	ACPI_BUS_TYPE_POWER_BUTTON,
	ACPI_BUS_TYPE_SLEEP_BUTTON,
	ACPI_BUS_TYPE_ECDT_EC,
	ACPI_BUS_DEVICE_TYPE_COUNT
पूर्ण;

काष्ठा acpi_driver;
काष्ठा acpi_device;

/*
 * ACPI Scan Handler
 * -----------------
 */

काष्ठा acpi_hotplug_profile अणु
	काष्ठा kobject kobj;
	पूर्णांक (*scan_dependent)(काष्ठा acpi_device *adev);
	व्योम (*notअगरy_online)(काष्ठा acpi_device *adev);
	bool enabled:1;
	bool demand_offline:1;
पूर्ण;

अटल अंतरभूत काष्ठा acpi_hotplug_profile *to_acpi_hotplug_profile(
						काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा acpi_hotplug_profile, kobj);
पूर्ण

काष्ठा acpi_scan_handler अणु
	स्थिर काष्ठा acpi_device_id *ids;
	काष्ठा list_head list_node;
	bool (*match)(स्थिर अक्षर *idstr, स्थिर काष्ठा acpi_device_id **matchid);
	पूर्णांक (*attach)(काष्ठा acpi_device *dev, स्थिर काष्ठा acpi_device_id *id);
	व्योम (*detach)(काष्ठा acpi_device *dev);
	व्योम (*bind)(काष्ठा device *phys_dev);
	व्योम (*unbind)(काष्ठा device *phys_dev);
	काष्ठा acpi_hotplug_profile hotplug;
पूर्ण;

/*
 * ACPI Hotplug Context
 * --------------------
 */

काष्ठा acpi_hotplug_context अणु
	काष्ठा acpi_device *self;
	पूर्णांक (*notअगरy)(काष्ठा acpi_device *, u32);
	व्योम (*uevent)(काष्ठा acpi_device *, u32);
	व्योम (*fixup)(काष्ठा acpi_device *);
पूर्ण;

/*
 * ACPI Driver
 * -----------
 */

प्रकार पूर्णांक (*acpi_op_add) (काष्ठा acpi_device * device);
प्रकार पूर्णांक (*acpi_op_हटाओ) (काष्ठा acpi_device * device);
प्रकार व्योम (*acpi_op_notअगरy) (काष्ठा acpi_device * device, u32 event);

काष्ठा acpi_device_ops अणु
	acpi_op_add add;
	acpi_op_हटाओ हटाओ;
	acpi_op_notअगरy notअगरy;
पूर्ण;

#घोषणा ACPI_DRIVER_ALL_NOTIFY_EVENTS	0x1	/* प्रणाली AND device events */

काष्ठा acpi_driver अणु
	अक्षर name[80];
	अक्षर class[80];
	स्थिर काष्ठा acpi_device_id *ids; /* Supported Hardware IDs */
	अचिन्हित पूर्णांक flags;
	काष्ठा acpi_device_ops ops;
	काष्ठा device_driver drv;
	काष्ठा module *owner;
पूर्ण;

/*
 * ACPI Device
 * -----------
 */

/* Status (_STA) */

काष्ठा acpi_device_status अणु
	u32 present:1;
	u32 enabled:1;
	u32 show_in_ui:1;
	u32 functional:1;
	u32 battery_present:1;
	u32 reserved:27;
पूर्ण;

/* Flags */

काष्ठा acpi_device_flags अणु
	u32 dynamic_status:1;
	u32 removable:1;
	u32 ejectable:1;
	u32 घातer_manageable:1;
	u32 match_driver:1;
	u32 initialized:1;
	u32 visited:1;
	u32 hotplug_notअगरy:1;
	u32 is_करोck_station:1;
	u32 of_compatible_ok:1;
	u32 coherent_dma:1;
	u32 cca_seen:1;
	u32 क्रमागतeration_by_parent:1;
	u32 reserved:19;
पूर्ण;

/* File System */

काष्ठा acpi_device_dir अणु
	काष्ठा proc_dir_entry *entry;
पूर्ण;

#घोषणा acpi_device_dir(d)	((d)->dir.entry)

/* Plug and Play */

प्रकार अक्षर acpi_bus_id[8];
प्रकार u64 acpi_bus_address;
प्रकार अक्षर acpi_device_name[40];
प्रकार अक्षर acpi_device_class[20];

काष्ठा acpi_hardware_id अणु
	काष्ठा list_head list;
	स्थिर अक्षर *id;
पूर्ण;

काष्ठा acpi_pnp_type अणु
	u32 hardware_id:1;
	u32 bus_address:1;
	u32 platक्रमm_id:1;
	u32 reserved:29;
पूर्ण;

काष्ठा acpi_device_pnp अणु
	acpi_bus_id bus_id;		/* Object name */
	पूर्णांक instance_no;		/* Instance number of this object */
	काष्ठा acpi_pnp_type type;	/* ID type */
	acpi_bus_address bus_address;	/* _ADR */
	अक्षर *unique_id;		/* _UID */
	काष्ठा list_head ids;		/* _HID and _CIDs */
	acpi_device_name device_name;	/* Driver-determined */
	acpi_device_class device_class;	/*        "          */
	जोड़ acpi_object *str_obj;	/* unicode string क्रम _STR method */
पूर्ण;

#घोषणा acpi_device_bid(d)	((d)->pnp.bus_id)
#घोषणा acpi_device_adr(d)	((d)->pnp.bus_address)
स्थिर अक्षर *acpi_device_hid(काष्ठा acpi_device *device);
#घोषणा acpi_device_uid(d)	((d)->pnp.unique_id)
#घोषणा acpi_device_name(d)	((d)->pnp.device_name)
#घोषणा acpi_device_class(d)	((d)->pnp.device_class)

/* Power Management */

काष्ठा acpi_device_घातer_flags अणु
	u32 explicit_get:1;	/* _PSC present? */
	u32 घातer_resources:1;	/* Power resources */
	u32 inrush_current:1;	/* Serialize Dx->D0 */
	u32 घातer_हटाओd:1;	/* Optimize Dx->D0 */
	u32 ignore_parent:1;	/* Power is independent of parent घातer state */
	u32 dsw_present:1;	/* _DSW present? */
	u32 reserved:26;
पूर्ण;

काष्ठा acpi_device_घातer_state अणु
	काष्ठा अणु
		u8 valid:1;
		u8 explicit_set:1;	/* _PSx present? */
		u8 reserved:6;
	पूर्ण flags;
	पूर्णांक घातer;		/* % Power (compared to D0) */
	पूर्णांक latency;		/* Dx->D0 समय (microseconds) */
	काष्ठा list_head resources;	/* Power resources referenced */
पूर्ण;

काष्ठा acpi_device_घातer अणु
	पूर्णांक state;		/* Current state */
	काष्ठा acpi_device_घातer_flags flags;
	काष्ठा acpi_device_घातer_state states[ACPI_D_STATE_COUNT];	/* Power states (D0-D3Cold) */
पूर्ण;

/* Perक्रमmance Management */

काष्ठा acpi_device_perf_flags अणु
	u8 reserved:8;
पूर्ण;

काष्ठा acpi_device_perf_state अणु
	काष्ठा अणु
		u8 valid:1;
		u8 reserved:7;
	पूर्ण flags;
	u8 घातer;		/* % Power (compared to P0) */
	u8 perक्रमmance;		/* % Perक्रमmance (    "   ) */
	पूर्णांक latency;		/* Px->P0 समय (microseconds) */
पूर्ण;

काष्ठा acpi_device_perf अणु
	पूर्णांक state;
	काष्ठा acpi_device_perf_flags flags;
	पूर्णांक state_count;
	काष्ठा acpi_device_perf_state *states;
पूर्ण;

/* Wakeup Management */
काष्ठा acpi_device_wakeup_flags अणु
	u8 valid:1;		/* Can successfully enable wakeup? */
	u8 notअगरier_present:1;  /* Wake-up notअगरy handler has been installed */
पूर्ण;

काष्ठा acpi_device_wakeup_context अणु
	व्योम (*func)(काष्ठा acpi_device_wakeup_context *context);
	काष्ठा device *dev;
पूर्ण;

काष्ठा acpi_device_wakeup अणु
	acpi_handle gpe_device;
	u64 gpe_number;
	u64 sleep_state;
	काष्ठा list_head resources;
	काष्ठा acpi_device_wakeup_flags flags;
	काष्ठा acpi_device_wakeup_context context;
	काष्ठा wakeup_source *ws;
	पूर्णांक prepare_count;
	पूर्णांक enable_count;
पूर्ण;

काष्ठा acpi_device_physical_node अणु
	अचिन्हित पूर्णांक node_id;
	काष्ठा list_head node;
	काष्ठा device *dev;
	bool put_online:1;
पूर्ण;

काष्ठा acpi_device_properties अणु
	स्थिर guid_t *guid;
	स्थिर जोड़ acpi_object *properties;
	काष्ठा list_head list;
पूर्ण;

/* ACPI Device Specअगरic Data (_DSD) */
काष्ठा acpi_device_data अणु
	स्थिर जोड़ acpi_object *poपूर्णांकer;
	काष्ठा list_head properties;
	स्थिर जोड़ acpi_object *of_compatible;
	काष्ठा list_head subnodes;
पूर्ण;

काष्ठा acpi_gpio_mapping;

/* Device */
काष्ठा acpi_device अणु
	पूर्णांक device_type;
	acpi_handle handle;		/* no handle क्रम fixed hardware */
	काष्ठा fwnode_handle fwnode;
	काष्ठा acpi_device *parent;
	काष्ठा list_head children;
	काष्ठा list_head node;
	काष्ठा list_head wakeup_list;
	काष्ठा list_head del_list;
	काष्ठा acpi_device_status status;
	काष्ठा acpi_device_flags flags;
	काष्ठा acpi_device_pnp pnp;
	काष्ठा acpi_device_घातer घातer;
	काष्ठा acpi_device_wakeup wakeup;
	काष्ठा acpi_device_perf perक्रमmance;
	काष्ठा acpi_device_dir dir;
	काष्ठा acpi_device_data data;
	काष्ठा acpi_scan_handler *handler;
	काष्ठा acpi_hotplug_context *hp;
	काष्ठा acpi_driver *driver;
	स्थिर काष्ठा acpi_gpio_mapping *driver_gpios;
	व्योम *driver_data;
	काष्ठा device dev;
	अचिन्हित पूर्णांक physical_node_count;
	अचिन्हित पूर्णांक dep_unmet;
	काष्ठा list_head physical_node_list;
	काष्ठा mutex physical_node_lock;
	व्योम (*हटाओ)(काष्ठा acpi_device *);
पूर्ण;

/* Non-device subnode */
काष्ठा acpi_data_node अणु
	स्थिर अक्षर *name;
	acpi_handle handle;
	काष्ठा fwnode_handle fwnode;
	काष्ठा fwnode_handle *parent;
	काष्ठा acpi_device_data data;
	काष्ठा list_head sibling;
	काष्ठा kobject kobj;
	काष्ठा completion kobj_करोne;
पूर्ण;

बाह्य स्थिर काष्ठा fwnode_operations acpi_device_fwnode_ops;
बाह्य स्थिर काष्ठा fwnode_operations acpi_data_fwnode_ops;
बाह्य स्थिर काष्ठा fwnode_operations acpi_अटल_fwnode_ops;

bool is_acpi_device_node(स्थिर काष्ठा fwnode_handle *fwnode);
bool is_acpi_data_node(स्थिर काष्ठा fwnode_handle *fwnode);

अटल अंतरभूत bool is_acpi_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस (is_acpi_device_node(fwnode) || is_acpi_data_node(fwnode));
पूर्ण

#घोषणा to_acpi_device_node(__fwnode)					\
	(अणु								\
		typeof(__fwnode) __to_acpi_device_node_fwnode = __fwnode; \
									\
		is_acpi_device_node(__to_acpi_device_node_fwnode) ?	\
			container_of(__to_acpi_device_node_fwnode,	\
				     काष्ठा acpi_device, fwnode) :	\
			शून्य;						\
	पूर्ण)

#घोषणा to_acpi_data_node(__fwnode)					\
	(अणु								\
		typeof(__fwnode) __to_acpi_data_node_fwnode = __fwnode;	\
									\
		is_acpi_data_node(__to_acpi_data_node_fwnode) ?		\
			container_of(__to_acpi_data_node_fwnode,	\
				     काष्ठा acpi_data_node, fwnode) :	\
			शून्य;						\
	पूर्ण)

अटल अंतरभूत bool is_acpi_अटल_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस !IS_ERR_OR_शून्य(fwnode) &&
		fwnode->ops == &acpi_अटल_fwnode_ops;
पूर्ण

अटल अंतरभूत bool acpi_data_node_match(स्थिर काष्ठा fwnode_handle *fwnode,
					स्थिर अक्षर *name)
अणु
	वापस is_acpi_data_node(fwnode) ?
		(!म_भेद(to_acpi_data_node(fwnode)->name, name)) : false;
पूर्ण

अटल अंतरभूत काष्ठा fwnode_handle *acpi_fwnode_handle(काष्ठा acpi_device *adev)
अणु
	वापस &adev->fwnode;
पूर्ण

अटल अंतरभूत व्योम *acpi_driver_data(काष्ठा acpi_device *d)
अणु
	वापस d->driver_data;
पूर्ण

#घोषणा to_acpi_device(d)	container_of(d, काष्ठा acpi_device, dev)
#घोषणा to_acpi_driver(d)	container_of(d, काष्ठा acpi_driver, drv)

अटल अंतरभूत व्योम acpi_set_device_status(काष्ठा acpi_device *adev, u32 sta)
अणु
	*((u32 *)&adev->status) = sta;
पूर्ण

अटल अंतरभूत व्योम acpi_set_hp_context(काष्ठा acpi_device *adev,
				       काष्ठा acpi_hotplug_context *hp)
अणु
	hp->self = adev;
	adev->hp = hp;
पूर्ण

व्योम acpi_initialize_hp_context(काष्ठा acpi_device *adev,
				काष्ठा acpi_hotplug_context *hp,
				पूर्णांक (*notअगरy)(काष्ठा acpi_device *, u32),
				व्योम (*uevent)(काष्ठा acpi_device *, u32));

/* acpi_device.dev.bus == &acpi_bus_type */
बाह्य काष्ठा bus_type acpi_bus_type;

/*
 * Events
 * ------
 */

काष्ठा acpi_bus_event अणु
	काष्ठा list_head node;
	acpi_device_class device_class;
	acpi_bus_id bus_id;
	u32 type;
	u32 data;
पूर्ण;

बाह्य काष्ठा kobject *acpi_kobj;
बाह्य पूर्णांक acpi_bus_generate_netlink_event(स्थिर अक्षर*, स्थिर अक्षर*, u8, पूर्णांक);
व्योम acpi_bus_निजी_data_handler(acpi_handle, व्योम *);
पूर्णांक acpi_bus_get_निजी_data(acpi_handle, व्योम **);
पूर्णांक acpi_bus_attach_निजी_data(acpi_handle, व्योम *);
व्योम acpi_bus_detach_निजी_data(acpi_handle);
बाह्य पूर्णांक acpi_notअगरier_call_chain(काष्ठा acpi_device *, u32, u32);
बाह्य पूर्णांक रेजिस्टर_acpi_notअगरier(काष्ठा notअगरier_block *);
बाह्य पूर्णांक unरेजिस्टर_acpi_notअगरier(काष्ठा notअगरier_block *);

/*
 * External Functions
 */

पूर्णांक acpi_bus_get_device(acpi_handle handle, काष्ठा acpi_device **device);
काष्ठा acpi_device *acpi_bus_get_acpi_device(acpi_handle handle);
व्योम acpi_bus_put_acpi_device(काष्ठा acpi_device *adev);
acpi_status acpi_bus_get_status_handle(acpi_handle handle,
				       अचिन्हित दीर्घ दीर्घ *sta);
पूर्णांक acpi_bus_get_status(काष्ठा acpi_device *device);

पूर्णांक acpi_bus_set_घातer(acpi_handle handle, पूर्णांक state);
स्थिर अक्षर *acpi_घातer_state_string(पूर्णांक state);
पूर्णांक acpi_device_set_घातer(काष्ठा acpi_device *device, पूर्णांक state);
पूर्णांक acpi_bus_init_घातer(काष्ठा acpi_device *device);
पूर्णांक acpi_device_fix_up_घातer(काष्ठा acpi_device *device);
पूर्णांक acpi_bus_update_घातer(acpi_handle handle, पूर्णांक *state_p);
पूर्णांक acpi_device_update_घातer(काष्ठा acpi_device *device, पूर्णांक *state_p);
bool acpi_bus_घातer_manageable(acpi_handle handle);
पूर्णांक acpi_device_घातer_add_dependent(काष्ठा acpi_device *adev,
				    काष्ठा device *dev);
व्योम acpi_device_घातer_हटाओ_dependent(काष्ठा acpi_device *adev,
					काष्ठा device *dev);

#अगर_घोषित CONFIG_PM
bool acpi_bus_can_wakeup(acpi_handle handle);
#अन्यथा
अटल अंतरभूत bool acpi_bus_can_wakeup(acpi_handle handle) अणु वापस false; पूर्ण
#पूर्ण_अगर

व्योम acpi_scan_lock_acquire(व्योम);
व्योम acpi_scan_lock_release(व्योम);
व्योम acpi_lock_hp_context(व्योम);
व्योम acpi_unlock_hp_context(व्योम);
पूर्णांक acpi_scan_add_handler(काष्ठा acpi_scan_handler *handler);
पूर्णांक acpi_bus_रेजिस्टर_driver(काष्ठा acpi_driver *driver);
व्योम acpi_bus_unरेजिस्टर_driver(काष्ठा acpi_driver *driver);
पूर्णांक acpi_bus_scan(acpi_handle handle);
व्योम acpi_bus_trim(काष्ठा acpi_device *start);
acpi_status acpi_bus_get_ejd(acpi_handle handle, acpi_handle * ejd);
पूर्णांक acpi_match_device_ids(काष्ठा acpi_device *device,
			  स्थिर काष्ठा acpi_device_id *ids);
व्योम acpi_set_modalias(काष्ठा acpi_device *adev, स्थिर अक्षर *शेष_id,
		       अक्षर *modalias, माप_प्रकार len);
पूर्णांक acpi_create_dir(काष्ठा acpi_device *);
व्योम acpi_हटाओ_dir(काष्ठा acpi_device *);

अटल अंतरभूत bool acpi_device_क्रमागतerated(काष्ठा acpi_device *adev)
अणु
	वापस adev && adev->flags.initialized && adev->flags.visited;
पूर्ण

/**
 * module_acpi_driver(acpi_driver) - Helper macro क्रम रेजिस्टरing an ACPI driver
 * @__acpi_driver: acpi_driver काष्ठा
 *
 * Helper macro क्रम ACPI drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_acpi_driver(__acpi_driver) \
	module_driver(__acpi_driver, acpi_bus_रेजिस्टर_driver, \
		      acpi_bus_unरेजिस्टर_driver)

/*
 * Bind physical devices with ACPI devices
 */
काष्ठा acpi_bus_type अणु
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	bool (*match)(काष्ठा device *dev);
	काष्ठा acpi_device * (*find_companion)(काष्ठा device *);
	व्योम (*setup)(काष्ठा device *);
	व्योम (*cleanup)(काष्ठा device *);
पूर्ण;
पूर्णांक रेजिस्टर_acpi_bus_type(काष्ठा acpi_bus_type *);
पूर्णांक unरेजिस्टर_acpi_bus_type(काष्ठा acpi_bus_type *);
पूर्णांक acpi_bind_one(काष्ठा device *dev, काष्ठा acpi_device *adev);
पूर्णांक acpi_unbind_one(काष्ठा device *dev);

काष्ठा acpi_pci_root अणु
	काष्ठा acpi_device * device;
	काष्ठा pci_bus *bus;
	u16 segment;
	काष्ठा resource secondary;	/* करोwnstream bus range */

	u32 osc_support_set;	/* _OSC state of support bits */
	u32 osc_control_set;	/* _OSC state of control bits */
	phys_addr_t mcfg_addr;
पूर्ण;

/* helper */

bool acpi_dma_supported(काष्ठा acpi_device *adev);
क्रमागत dev_dma_attr acpi_get_dma_attr(काष्ठा acpi_device *adev);
पूर्णांक acpi_dma_get_range(काष्ठा device *dev, u64 *dma_addr, u64 *offset,
		       u64 *size);
पूर्णांक acpi_dma_configure_id(काष्ठा device *dev, क्रमागत dev_dma_attr attr,
			   स्थिर u32 *input_id);
अटल अंतरभूत पूर्णांक acpi_dma_configure(काष्ठा device *dev,
				     क्रमागत dev_dma_attr attr)
अणु
	वापस acpi_dma_configure_id(dev, attr, शून्य);
पूर्ण
काष्ठा acpi_device *acpi_find_child_device(काष्ठा acpi_device *parent,
					   u64 address, bool check_children);
पूर्णांक acpi_is_root_bridge(acpi_handle);
काष्ठा acpi_pci_root *acpi_pci_find_root(acpi_handle handle);

पूर्णांक acpi_enable_wakeup_device_घातer(काष्ठा acpi_device *dev, पूर्णांक state);
पूर्णांक acpi_disable_wakeup_device_घातer(काष्ठा acpi_device *dev);

#अगर_घोषित CONFIG_X86
bool acpi_device_always_present(काष्ठा acpi_device *adev);
#अन्यथा
अटल अंतरभूत bool acpi_device_always_present(काष्ठा acpi_device *adev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
व्योम acpi_pm_wakeup_event(काष्ठा device *dev);
acpi_status acpi_add_pm_notअगरier(काष्ठा acpi_device *adev, काष्ठा device *dev,
			व्योम (*func)(काष्ठा acpi_device_wakeup_context *context));
acpi_status acpi_हटाओ_pm_notअगरier(काष्ठा acpi_device *adev);
bool acpi_pm_device_can_wakeup(काष्ठा device *dev);
पूर्णांक acpi_pm_device_sleep_state(काष्ठा device *, पूर्णांक *, पूर्णांक);
पूर्णांक acpi_pm_set_device_wakeup(काष्ठा device *dev, bool enable);
#अन्यथा
अटल अंतरभूत व्योम acpi_pm_wakeup_event(काष्ठा device *dev)
अणु
पूर्ण
अटल अंतरभूत acpi_status acpi_add_pm_notअगरier(काष्ठा acpi_device *adev,
					       काष्ठा device *dev,
					       व्योम (*func)(काष्ठा acpi_device_wakeup_context *context))
अणु
	वापस AE_SUPPORT;
पूर्ण
अटल अंतरभूत acpi_status acpi_हटाओ_pm_notअगरier(काष्ठा acpi_device *adev)
अणु
	वापस AE_SUPPORT;
पूर्ण
अटल अंतरभूत bool acpi_pm_device_can_wakeup(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक acpi_pm_device_sleep_state(काष्ठा device *d, पूर्णांक *p, पूर्णांक m)
अणु
	अगर (p)
		*p = ACPI_STATE_D0;

	वापस (m >= ACPI_STATE_D0 && m <= ACPI_STATE_D3_COLD) ?
		m : ACPI_STATE_D0;
पूर्ण
अटल अंतरभूत पूर्णांक acpi_pm_set_device_wakeup(काष्ठा device *dev, bool enable)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_SYSTEM_POWER_STATES_SUPPORT
bool acpi_sleep_state_supported(u8 sleep_state);
#अन्यथा
अटल अंतरभूत bool acpi_sleep_state_supported(u8 sleep_state) अणु वापस false; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_SLEEP
u32 acpi_target_प्रणाली_state(व्योम);
#अन्यथा
अटल अंतरभूत u32 acpi_target_प्रणाली_state(व्योम) अणु वापस ACPI_STATE_S0; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool acpi_device_घातer_manageable(काष्ठा acpi_device *adev)
अणु
	वापस adev->flags.घातer_manageable;
पूर्ण

अटल अंतरभूत bool acpi_device_can_wakeup(काष्ठा acpi_device *adev)
अणु
	वापस adev->wakeup.flags.valid;
पूर्ण

अटल अंतरभूत bool acpi_device_can_घातeroff(काष्ठा acpi_device *adev)
अणु
	वापस adev->घातer.states[ACPI_STATE_D3_COLD].flags.valid ||
		((acpi_gbl_FADT.header.revision < 6) &&
		adev->घातer.states[ACPI_STATE_D3_HOT].flags.explicit_set);
पूर्ण

bool acpi_dev_hid_uid_match(काष्ठा acpi_device *adev, स्थिर अक्षर *hid2, स्थिर अक्षर *uid2);

काष्ठा acpi_device *
acpi_dev_get_next_match_dev(काष्ठा acpi_device *adev, स्थिर अक्षर *hid, स्थिर अक्षर *uid, s64 hrv);
काष्ठा acpi_device *
acpi_dev_get_first_match_dev(स्थिर अक्षर *hid, स्थिर अक्षर *uid, s64 hrv);

/**
 * क्रम_each_acpi_dev_match - iterate over ACPI devices that matching the criteria
 * @adev: poपूर्णांकer to the matching ACPI device, शून्य at the end of the loop
 * @hid: Hardware ID of the device.
 * @uid: Unique ID of the device, pass शून्य to not check _UID
 * @hrv: Hardware Revision of the device, pass -1 to not check _HRV
 *
 * The caller is responsible क्रम invoking acpi_dev_put() on the वापसed device.
 *
 * FIXME: Due to above requirement there is a winकरोw that may invalidate @adev
 * and next iteration will use a dangling poपूर्णांकer, e.g. in the हाल of a
 * hotplug event. That said, the caller should ensure that this will never
 * happen.
 */
#घोषणा क्रम_each_acpi_dev_match(adev, hid, uid, hrv)			\
	क्रम (adev = acpi_dev_get_first_match_dev(hid, uid, hrv);	\
	     adev;							\
	     adev = acpi_dev_get_next_match_dev(adev, hid, uid, hrv))

अटल अंतरभूत काष्ठा acpi_device *acpi_dev_get(काष्ठा acpi_device *adev)
अणु
	वापस adev ? to_acpi_device(get_device(&adev->dev)) : शून्य;
पूर्ण

अटल अंतरभूत व्योम acpi_dev_put(काष्ठा acpi_device *adev)
अणु
	put_device(&adev->dev);
पूर्ण
#अन्यथा	/* CONFIG_ACPI */

अटल अंतरभूत पूर्णांक रेजिस्टर_acpi_bus_type(व्योम *bus) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक unरेजिस्टर_acpi_bus_type(व्योम *bus) अणु वापस 0; पूर्ण

#पूर्ण_अगर				/* CONFIG_ACPI */

#पूर्ण_अगर /*__ACPI_BUS_H__*/
