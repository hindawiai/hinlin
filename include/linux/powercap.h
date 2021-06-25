<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * घातercap.h: Data types and headers क्रम sysfs घातer capping पूर्णांकerface
 * Copyright (c) 2013, Intel Corporation.
 */

#अगर_अघोषित __POWERCAP_H__
#घोषणा __POWERCAP_H__

#समावेश <linux/device.h>
#समावेश <linux/idr.h>

/*
 * A घातer cap class device can contain multiple घातercap control_types.
 * Each control_type can have multiple घातer zones, which can be independently
 * controlled. Each घातer zone can have one or more स्थिरraपूर्णांकs.
 */

काष्ठा घातercap_control_type;
काष्ठा घातercap_zone;
काष्ठा घातercap_zone_स्थिरraपूर्णांक;

/**
 * काष्ठा घातercap_control_type_ops - Define control type callbacks
 * @set_enable:		Enable/Disable whole control type.
 *			Default is enabled. But this callback allows all zones
 *			to be in disable state and हटाओ any applied घातer
 *			limits. If disabled घातer zone can only be monitored
 *			not controlled.
 * @get_enable:		get Enable/Disable status.
 * @release:		Callback to inक्रमm that last reference to this
 *			control type is बंदd. So it is safe to मुक्त data
 *			काष्ठाure associated with this control type.
 *			This callback is mandatory अगर the client own memory
 *			क्रम the control type.
 *
 * This काष्ठाure defines control type callbacks to be implemented by client
 * drivers
 */
काष्ठा घातercap_control_type_ops अणु
	पूर्णांक (*set_enable) (काष्ठा घातercap_control_type *, bool mode);
	पूर्णांक (*get_enable) (काष्ठा घातercap_control_type *, bool *mode);
	पूर्णांक (*release) (काष्ठा घातercap_control_type *);
पूर्ण;

/**
 * काष्ठा घातercap_control_type - Defines a घातercap control_type
 * @dev:		device क्रम this control_type
 * @idr:		idr to have unique id क्रम its child
 * @nr_zones:		counter क्रम number of zones of this type
 * @ops:		Poपूर्णांकer to callback काष्ठा
 * @lock:		mutex क्रम control type
 * @allocated:		This is possible that client owns the memory
 *			used by this काष्ठाure. In this हाल
 *			this flag is set to false by framework to
 *			prevent deallocation during release process.
 *			Otherwise this flag is set to true.
 * @node:		linked-list node
 *
 * Defines घातercap control_type. This acts as a container क्रम घातer
 * zones, which use same method to control घातer. E.g. RAPL, RAPL-PCI etc.
 * All fields are निजी and should not be used by client drivers.
 */
काष्ठा घातercap_control_type अणु
	काष्ठा device dev;
	काष्ठा idr idr;
	पूर्णांक nr_zones;
	स्थिर काष्ठा घातercap_control_type_ops *ops;
	काष्ठा mutex lock;
	bool allocated;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा घातercap_zone_ops - Define घातer zone callbacks
 * @get_max_energy_range_uj:	Get maximum range of energy counter in
 *				micro-joules.
 * @get_energy_uj:		Get current energy counter in micro-joules.
 * @reset_energy_uj:		Reset micro-joules energy counter.
 * @get_max_घातer_range_uw:	Get maximum range of घातer counter in
 *				micro-watts.
 * @get_घातer_uw:		Get current घातer counter in micro-watts.
 * @set_enable:			Enable/Disable घातer zone controls.
 *				Default is enabled.
 * @get_enable:			get Enable/Disable status.
 * @release:			Callback to inक्रमm that last reference to this
 *				control type is बंदd. So it is safe to मुक्त
 *				data काष्ठाure associated with this
 *				control type. Mandatory, अगर client driver owns
 *				the घातer_zone memory.
 *
 * This काष्ठाure defines zone callbacks to be implemented by client drivers.
 * Client drives can define both energy and घातer related callbacks. But at
 * the least one type (either घातer or energy) is mandatory. Client drivers
 * should handle mutual exclusion, अगर required in callbacks.
 */
काष्ठा घातercap_zone_ops अणु
	पूर्णांक (*get_max_energy_range_uj) (काष्ठा घातercap_zone *, u64 *);
	पूर्णांक (*get_energy_uj) (काष्ठा घातercap_zone *, u64 *);
	पूर्णांक (*reset_energy_uj) (काष्ठा घातercap_zone *);
	पूर्णांक (*get_max_घातer_range_uw) (काष्ठा घातercap_zone *, u64 *);
	पूर्णांक (*get_घातer_uw) (काष्ठा घातercap_zone *, u64 *);
	पूर्णांक (*set_enable) (काष्ठा घातercap_zone *, bool mode);
	पूर्णांक (*get_enable) (काष्ठा घातercap_zone *, bool *mode);
	पूर्णांक (*release) (काष्ठा घातercap_zone *);
पूर्ण;

#घोषणा	POWERCAP_ZONE_MAX_ATTRS		6
#घोषणा	POWERCAP_CONSTRAINTS_ATTRS	8
#घोषणा MAX_CONSTRAINTS_PER_ZONE	10
/**
 * काष्ठा घातercap_zone- Defines instance of a घातer cap zone
 * @id:			Unique id
 * @name:		Power zone name.
 * @control_type_inst:	Control type instance क्रम this zone.
 * @ops:		Poपूर्णांकer to the zone operation काष्ठाure.
 * @dev:		Instance of a device.
 * @स्थिर_id_cnt:	Number of स्थिरraपूर्णांक defined.
 * @idr:		Instance to an idr entry क्रम children zones.
 * @parent_idr:		To हटाओ reference from the parent idr.
 * @निजी_data:	Private data poपूर्णांकer अगर any क्रम this zone.
 * @zone_dev_attrs:	Attributes associated with this device.
 * @zone_attr_count:	Attribute count.
 * @dev_zone_attr_group: Attribute group क्रम attributes.
 * @dev_attr_groups:	Attribute group store to रेजिस्टर with device.
 * @allocated:		This is possible that client owns the memory
 *			used by this काष्ठाure. In this हाल
 *			this flag is set to false by framework to
 *			prevent deallocation during release process.
 *			Otherwise this flag is set to true.
 * @स्थिरraपूर्णांकs:	List of स्थिरraपूर्णांकs क्रम this zone.
 *
 * This defines a घातer zone instance. The fields of this काष्ठाure are
 * निजी, and should not be used by client drivers.
 */
काष्ठा घातercap_zone अणु
	पूर्णांक id;
	अक्षर *name;
	व्योम *control_type_inst;
	स्थिर काष्ठा घातercap_zone_ops *ops;
	काष्ठा device dev;
	पूर्णांक स्थिर_id_cnt;
	काष्ठा idr idr;
	काष्ठा idr *parent_idr;
	व्योम *निजी_data;
	काष्ठा attribute **zone_dev_attrs;
	पूर्णांक zone_attr_count;
	काष्ठा attribute_group dev_zone_attr_group;
	स्थिर काष्ठा attribute_group *dev_attr_groups[2]; /* 1 group + शून्य */
	bool allocated;
	काष्ठा घातercap_zone_स्थिरraपूर्णांक *स्थिरraपूर्णांकs;
पूर्ण;

/**
 * काष्ठा घातercap_zone_स्थिरraपूर्णांक_ops - Define स्थिरraपूर्णांक callbacks
 * @set_घातer_limit_uw:		Set घातer limit in micro-watts.
 * @get_घातer_limit_uw:		Get घातer limit in micro-watts.
 * @set_समय_winकरोw_us:		Set समय winकरोw in micro-seconds.
 * @get_समय_winकरोw_us:		Get समय winकरोw in micro-seconds.
 * @get_max_घातer_uw:		Get max घातer allowed in micro-watts.
 * @get_min_घातer_uw:		Get min घातer allowed in micro-watts.
 * @get_max_समय_winकरोw_us:	Get max समय winकरोw allowed in micro-seconds.
 * @get_min_समय_winकरोw_us:	Get min समय winकरोw allowed in micro-seconds.
 * @get_name:			Get the name of स्थिरraपूर्णांक
 *
 * This काष्ठाure is used to define the स्थिरraपूर्णांक callbacks क्रम the client
 * drivers. The following callbacks are mandatory and can't be शून्य:
 *  set_घातer_limit_uw
 *  get_घातer_limit_uw
 *  set_समय_winकरोw_us
 *  get_समय_winकरोw_us
 *  get_name
 *  Client drivers should handle mutual exclusion, अगर required in callbacks.
 */
काष्ठा घातercap_zone_स्थिरraपूर्णांक_ops अणु
	पूर्णांक (*set_घातer_limit_uw) (काष्ठा घातercap_zone *, पूर्णांक, u64);
	पूर्णांक (*get_घातer_limit_uw) (काष्ठा घातercap_zone *, पूर्णांक, u64 *);
	पूर्णांक (*set_समय_winकरोw_us) (काष्ठा घातercap_zone *, पूर्णांक, u64);
	पूर्णांक (*get_समय_winकरोw_us) (काष्ठा घातercap_zone *, पूर्णांक, u64 *);
	पूर्णांक (*get_max_घातer_uw) (काष्ठा घातercap_zone *, पूर्णांक, u64 *);
	पूर्णांक (*get_min_घातer_uw) (काष्ठा घातercap_zone *, पूर्णांक, u64 *);
	पूर्णांक (*get_max_समय_winकरोw_us) (काष्ठा घातercap_zone *, पूर्णांक, u64 *);
	पूर्णांक (*get_min_समय_winकरोw_us) (काष्ठा घातercap_zone *, पूर्णांक, u64 *);
	स्थिर अक्षर *(*get_name) (काष्ठा घातercap_zone *, पूर्णांक);
पूर्ण;

/**
 * काष्ठा घातercap_zone_स्थिरraपूर्णांक- Defines instance of a स्थिरraपूर्णांक
 * @id:			Instance Id of this स्थिरraपूर्णांक.
 * @घातer_zone:		Poपूर्णांकer to the घातer zone क्रम this स्थिरraपूर्णांक.
 * @ops:		Poपूर्णांकer to the स्थिरraपूर्णांक callbacks.
 *
 * This defines a स्थिरraपूर्णांक instance.
 */
काष्ठा घातercap_zone_स्थिरraपूर्णांक अणु
	पूर्णांक id;
	काष्ठा घातercap_zone *घातer_zone;
	स्थिर काष्ठा घातercap_zone_स्थिरraपूर्णांक_ops *ops;
पूर्ण;


/* For clients to get their device poपूर्णांकer, may be used क्रम dev_dbgs */
#घोषणा POWERCAP_GET_DEV(घातer_zone)	(&घातer_zone->dev)

/**
* घातercap_set_zone_data() - Set निजी data क्रम a zone
* @घातer_zone:	A poपूर्णांकer to the valid zone instance.
* @pdata:	A poपूर्णांकer to the user निजी data.
*
* Allows client drivers to associate some निजी data to zone instance.
*/
अटल अंतरभूत व्योम घातercap_set_zone_data(काष्ठा घातercap_zone *घातer_zone,
						व्योम *pdata)
अणु
	अगर (घातer_zone)
		घातer_zone->निजी_data = pdata;
पूर्ण

/**
* घातercap_get_zone_data() - Get निजी data क्रम a zone
* @घातer_zone:	A poपूर्णांकer to the valid zone instance.
*
* Allows client drivers to get निजी data associate with a zone,
* using call to घातercap_set_zone_data.
*/
अटल अंतरभूत व्योम *घातercap_get_zone_data(काष्ठा घातercap_zone *घातer_zone)
अणु
	अगर (घातer_zone)
		वापस घातer_zone->निजी_data;
	वापस शून्य;
पूर्ण

/**
* घातercap_रेजिस्टर_control_type() - Register a control_type with framework
* @control_type:	Poपूर्णांकer to client allocated memory क्रम the control type
*			काष्ठाure storage. If this is शून्य, घातercap framework
*			will allocate memory and own it.
*			Advantage of this parameter is that client can embed
*			this data in its data काष्ठाures and allocate in a
*			single call, preventing multiple allocations.
* @control_type_name:	The Name of this control_type, which will be shown
*			in the sysfs Interface.
* @ops:			Callbacks क्रम control type. This parameter is optional.
*
* Used to create a control_type with the घातer capping class. Here control_type
* can represent a type of technology, which can control a range of घातer zones.
* For example a control_type can be RAPL (Running Average Power Limit)
* Intelतऍ 64 and IA-32 Processor Architectures. The name can be any string
* which must be unique, otherwise this function वापसs शून्य.
* A poपूर्णांकer to the control_type instance is वापसed on success.
*/
काष्ठा घातercap_control_type *घातercap_रेजिस्टर_control_type(
				काष्ठा घातercap_control_type *control_type,
				स्थिर अक्षर *name,
				स्थिर काष्ठा घातercap_control_type_ops *ops);

/**
* घातercap_unरेजिस्टर_control_type() - Unरेजिस्टर a control_type from framework
* @instance:	A poपूर्णांकer to the valid control_type instance.
*
* Used to unरेजिस्टर a control_type with the घातer capping class.
* All घातer zones रेजिस्टरed under this control type have to be unरेजिस्टरed
* beक्रमe calling this function, or it will fail with an error code.
*/
पूर्णांक घातercap_unरेजिस्टर_control_type(काष्ठा घातercap_control_type *instance);

/* Zone रेजिस्टर/unरेजिस्टर API */

/**
* घातercap_रेजिस्टर_zone() - Register a घातer zone
* @घातer_zone:	Poपूर्णांकer to client allocated memory क्रम the घातer zone काष्ठाure
*		storage. If this is शून्य, घातercap framework will allocate
*		memory and own it. Advantage of this parameter is that client
*		can embed this data in its data काष्ठाures and allocate in a
*		single call, preventing multiple allocations.
* @control_type: A control_type instance under which this zone operates.
* @name:	A name क्रम this zone.
* @parent:	A poपूर्णांकer to the parent घातer zone instance अगर any or शून्य
* @ops:		Poपूर्णांकer to zone operation callback काष्ठाure.
* @no_स्थिरraपूर्णांकs: Number of स्थिरraपूर्णांकs क्रम this zone
* @स्थिर_ops:	Poपूर्णांकer to स्थिरraपूर्णांक callback काष्ठाure
*
* Register a घातer zone under a given control type. A घातer zone must रेजिस्टर
* a poपूर्णांकer to a काष्ठाure representing zone callbacks.
* A घातer zone can be located under a parent घातer zone, in which हाल @parent
* should poपूर्णांक to it.  Otherwise, अगर @parent is शून्य, the new घातer zone will
* be located directly under the given control type
* For each घातer zone there may be a number of स्थिरraपूर्णांकs that appear in the
* sysfs under that zone as attributes with unique numeric IDs.
* Returns poपूर्णांकer to the घातer_zone on success.
*/
काष्ठा घातercap_zone *घातercap_रेजिस्टर_zone(
			काष्ठा घातercap_zone *घातer_zone,
			काष्ठा घातercap_control_type *control_type,
			स्थिर अक्षर *name,
			काष्ठा घातercap_zone *parent,
			स्थिर काष्ठा घातercap_zone_ops *ops,
			पूर्णांक nr_स्थिरraपूर्णांकs,
			स्थिर काष्ठा घातercap_zone_स्थिरraपूर्णांक_ops *स्थिर_ops);

/**
* घातercap_unरेजिस्टर_zone() - Unरेजिस्टर a zone device
* @control_type:	A poपूर्णांकer to the valid instance of a control_type.
* @घातer_zone:	A poपूर्णांकer to the valid zone instance क्रम a control_type
*
* Used to unरेजिस्टर a zone device क्रम a control_type.  Caller should
* make sure that children क्रम this zone are unरेजिस्टरed first.
*/
पूर्णांक घातercap_unरेजिस्टर_zone(काष्ठा घातercap_control_type *control_type,
				काष्ठा घातercap_zone *घातer_zone);

#पूर्ण_अगर
