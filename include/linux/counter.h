<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Counter पूर्णांकerface
 * Copyright (C) 2018 William Breathitt Gray
 */
#अगर_अघोषित _COUNTER_H_
#घोषणा _COUNTER_H_

#समावेश <linux/counter_क्रमागत.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>

क्रमागत counter_count_direction अणु
	COUNTER_COUNT_सूचीECTION_FORWARD = 0,
	COUNTER_COUNT_सूचीECTION_BACKWARD
पूर्ण;
बाह्य स्थिर अक्षर *स्थिर counter_count_direction_str[2];

क्रमागत counter_count_mode अणु
	COUNTER_COUNT_MODE_NORMAL = 0,
	COUNTER_COUNT_MODE_RANGE_LIMIT,
	COUNTER_COUNT_MODE_NON_RECYCLE,
	COUNTER_COUNT_MODE_MODULO_N
पूर्ण;
बाह्य स्थिर अक्षर *स्थिर counter_count_mode_str[4];

काष्ठा counter_device;
काष्ठा counter_संकेत;

/**
 * काष्ठा counter_संकेत_ext - Counter Signal extensions
 * @name:	attribute name
 * @पढ़ो:	पढ़ो callback क्रम this attribute; may be शून्य
 * @ग_लिखो:	ग_लिखो callback क्रम this attribute; may be शून्य
 * @priv:	data निजी to the driver
 */
काष्ठा counter_संकेत_ext अणु
	स्थिर अक्षर *name;
	sमाप_प्रकार (*पढ़ो)(काष्ठा counter_device *counter,
			काष्ठा counter_संकेत *संकेत, व्योम *priv, अक्षर *buf);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा counter_device *counter,
			 काष्ठा counter_संकेत *संकेत, व्योम *priv,
			 स्थिर अक्षर *buf, माप_प्रकार len);
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा counter_संकेत - Counter Signal node
 * @id:		unique ID used to identअगरy संकेत
 * @name:	device-specअगरic Signal name; ideally, this should match the name
 *		as it appears in the datasheet करोcumentation
 * @ext:	optional array of Counter Signal extensions
 * @num_ext:	number of Counter Signal extensions specअगरied in @ext
 * @priv:	optional निजी data supplied by driver
 */
काष्ठा counter_संकेत अणु
	पूर्णांक id;
	स्थिर अक्षर *name;

	स्थिर काष्ठा counter_संकेत_ext *ext;
	माप_प्रकार num_ext;

	व्योम *priv;
पूर्ण;

/**
 * काष्ठा counter_संकेत_क्रमागत_ext - Signal क्रमागत extension attribute
 * @items:	Array of strings
 * @num_items:	Number of items specअगरied in @items
 * @set:	Set callback function; may be शून्य
 * @get:	Get callback function; may be शून्य
 *
 * The counter_संकेत_क्रमागत_ext काष्ठाure can be used to implement क्रमागत style
 * Signal extension attributes. Enum style attributes are those which have a set
 * of strings that map to अचिन्हित पूर्णांकeger values. The Generic Counter Signal
 * क्रमागत extension helper code takes care of mapping between value and string, as
 * well as generating a "_available" file which contains a list of all available
 * items. The get callback is used to query the currently active item; the index
 * of the item within the respective items array is वापसed via the 'item'
 * parameter. The set callback is called when the attribute is updated; the
 * 'item' parameter contains the index of the newly activated item within the
 * respective items array.
 */
काष्ठा counter_संकेत_क्रमागत_ext अणु
	स्थिर अक्षर * स्थिर *items;
	माप_प्रकार num_items;
	पूर्णांक (*get)(काष्ठा counter_device *counter,
		   काष्ठा counter_संकेत *संकेत, माप_प्रकार *item);
	पूर्णांक (*set)(काष्ठा counter_device *counter,
		   काष्ठा counter_संकेत *संकेत, माप_प्रकार item);
पूर्ण;

/**
 * COUNTER_SIGNAL_ENUM() - Initialize Signal क्रमागत extension
 * @_name:	Attribute name
 * @_e:		Poपूर्णांकer to a counter_संकेत_क्रमागत_ext काष्ठाure
 *
 * This should usually be used together with COUNTER_SIGNAL_ENUM_AVAILABLE()
 */
#घोषणा COUNTER_SIGNAL_ENUM(_name, _e) \
अणु \
	.name = (_name), \
	.पढ़ो = counter_संकेत_क्रमागत_पढ़ो, \
	.ग_लिखो = counter_संकेत_क्रमागत_ग_लिखो, \
	.priv = (_e) \
पूर्ण

/**
 * COUNTER_SIGNAL_ENUM_AVAILABLE() - Initialize Signal क्रमागत available extension
 * @_name:	Attribute name ("_available" will be appended to the name)
 * @_e:		Poपूर्णांकer to a counter_संकेत_क्रमागत_ext काष्ठाure
 *
 * Creates a पढ़ो only attribute that lists all the available क्रमागत items in a
 * newline separated list. This should usually be used together with
 * COUNTER_SIGNAL_ENUM()
 */
#घोषणा COUNTER_SIGNAL_ENUM_AVAILABLE(_name, _e) \
अणु \
	.name = (_name "_available"), \
	.पढ़ो = counter_संकेत_क्रमागत_available_पढ़ो, \
	.priv = (_e) \
पूर्ण

क्रमागत counter_synapse_action अणु
	COUNTER_SYNAPSE_ACTION_NONE = 0,
	COUNTER_SYNAPSE_ACTION_RISING_EDGE,
	COUNTER_SYNAPSE_ACTION_FALLING_EDGE,
	COUNTER_SYNAPSE_ACTION_BOTH_EDGES
पूर्ण;

/**
 * काष्ठा counter_synapse - Counter Synapse node
 * @action:		index of current action mode
 * @actions_list:	array of available action modes
 * @num_actions:	number of action modes specअगरied in @actions_list
 * @संकेत:		poपूर्णांकer to associated संकेत
 */
काष्ठा counter_synapse अणु
	माप_प्रकार action;
	स्थिर क्रमागत counter_synapse_action *actions_list;
	माप_प्रकार num_actions;

	काष्ठा counter_संकेत *संकेत;
पूर्ण;

काष्ठा counter_count;

/**
 * काष्ठा counter_count_ext - Counter Count extension
 * @name:	attribute name
 * @पढ़ो:	पढ़ो callback क्रम this attribute; may be शून्य
 * @ग_लिखो:	ग_लिखो callback क्रम this attribute; may be शून्य
 * @priv:	data निजी to the driver
 */
काष्ठा counter_count_ext अणु
	स्थिर अक्षर *name;
	sमाप_प्रकार (*पढ़ो)(काष्ठा counter_device *counter,
			काष्ठा counter_count *count, व्योम *priv, अक्षर *buf);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा counter_device *counter,
			 काष्ठा counter_count *count, व्योम *priv,
			 स्थिर अक्षर *buf, माप_प्रकार len);
	व्योम *priv;
पूर्ण;

क्रमागत counter_count_function अणु
	COUNTER_COUNT_FUNCTION_INCREASE = 0,
	COUNTER_COUNT_FUNCTION_DECREASE,
	COUNTER_COUNT_FUNCTION_PULSE_सूचीECTION,
	COUNTER_COUNT_FUNCTION_QUADRATURE_X1_A,
	COUNTER_COUNT_FUNCTION_QUADRATURE_X1_B,
	COUNTER_COUNT_FUNCTION_QUADRATURE_X2_A,
	COUNTER_COUNT_FUNCTION_QUADRATURE_X2_B,
	COUNTER_COUNT_FUNCTION_QUADRATURE_X4
पूर्ण;

/**
 * काष्ठा counter_count - Counter Count node
 * @id:			unique ID used to identअगरy Count
 * @name:		device-specअगरic Count name; ideally, this should match
 *			the name as it appears in the datasheet करोcumentation
 * @function:		index of current function mode
 * @functions_list:	array available function modes
 * @num_functions:	number of function modes specअगरied in @functions_list
 * @synapses:		array of synapses क्रम initialization
 * @num_synapses:	number of synapses specअगरied in @synapses
 * @ext:		optional array of Counter Count extensions
 * @num_ext:		number of Counter Count extensions specअगरied in @ext
 * @priv:		optional निजी data supplied by driver
 */
काष्ठा counter_count अणु
	पूर्णांक id;
	स्थिर अक्षर *name;

	माप_प्रकार function;
	स्थिर क्रमागत counter_count_function *functions_list;
	माप_प्रकार num_functions;

	काष्ठा counter_synapse *synapses;
	माप_प्रकार num_synapses;

	स्थिर काष्ठा counter_count_ext *ext;
	माप_प्रकार num_ext;

	व्योम *priv;
पूर्ण;

/**
 * काष्ठा counter_count_क्रमागत_ext - Count क्रमागत extension attribute
 * @items:	Array of strings
 * @num_items:	Number of items specअगरied in @items
 * @set:	Set callback function; may be शून्य
 * @get:	Get callback function; may be शून्य
 *
 * The counter_count_क्रमागत_ext काष्ठाure can be used to implement क्रमागत style
 * Count extension attributes. Enum style attributes are those which have a set
 * of strings that map to अचिन्हित पूर्णांकeger values. The Generic Counter Count
 * क्रमागत extension helper code takes care of mapping between value and string, as
 * well as generating a "_available" file which contains a list of all available
 * items. The get callback is used to query the currently active item; the index
 * of the item within the respective items array is वापसed via the 'item'
 * parameter. The set callback is called when the attribute is updated; the
 * 'item' parameter contains the index of the newly activated item within the
 * respective items array.
 */
काष्ठा counter_count_क्रमागत_ext अणु
	स्थिर अक्षर * स्थिर *items;
	माप_प्रकार num_items;
	पूर्णांक (*get)(काष्ठा counter_device *counter, काष्ठा counter_count *count,
		   माप_प्रकार *item);
	पूर्णांक (*set)(काष्ठा counter_device *counter, काष्ठा counter_count *count,
		   माप_प्रकार item);
पूर्ण;

/**
 * COUNTER_COUNT_ENUM() - Initialize Count क्रमागत extension
 * @_name:	Attribute name
 * @_e:		Poपूर्णांकer to a counter_count_क्रमागत_ext काष्ठाure
 *
 * This should usually be used together with COUNTER_COUNT_ENUM_AVAILABLE()
 */
#घोषणा COUNTER_COUNT_ENUM(_name, _e) \
अणु \
	.name = (_name), \
	.पढ़ो = counter_count_क्रमागत_पढ़ो, \
	.ग_लिखो = counter_count_क्रमागत_ग_लिखो, \
	.priv = (_e) \
पूर्ण

/**
 * COUNTER_COUNT_ENUM_AVAILABLE() - Initialize Count क्रमागत available extension
 * @_name:	Attribute name ("_available" will be appended to the name)
 * @_e:		Poपूर्णांकer to a counter_count_क्रमागत_ext काष्ठाure
 *
 * Creates a पढ़ो only attribute that lists all the available क्रमागत items in a
 * newline separated list. This should usually be used together with
 * COUNTER_COUNT_ENUM()
 */
#घोषणा COUNTER_COUNT_ENUM_AVAILABLE(_name, _e) \
अणु \
	.name = (_name "_available"), \
	.पढ़ो = counter_count_क्रमागत_available_पढ़ो, \
	.priv = (_e) \
पूर्ण

/**
 * काष्ठा counter_device_attr_group - पूर्णांकernal container क्रम attribute group
 * @attr_group:	Counter sysfs attributes group
 * @attr_list:	list to keep track of created Counter sysfs attributes
 * @num_attr:	number of Counter sysfs attributes
 */
काष्ठा counter_device_attr_group अणु
	काष्ठा attribute_group attr_group;
	काष्ठा list_head attr_list;
	माप_प्रकार num_attr;
पूर्ण;

/**
 * काष्ठा counter_device_state - पूर्णांकernal state container क्रम a Counter device
 * @id:			unique ID used to identअगरy the Counter
 * @dev:		पूर्णांकernal device काष्ठाure
 * @groups_list:	attribute groups list (क्रम Signals, Counts, and ext)
 * @num_groups:		number of attribute groups containers
 * @groups:		Counter sysfs attribute groups (to populate @dev.groups)
 */
काष्ठा counter_device_state अणु
	पूर्णांक id;
	काष्ठा device dev;
	काष्ठा counter_device_attr_group *groups_list;
	माप_प्रकार num_groups;
	स्थिर काष्ठा attribute_group **groups;
पूर्ण;

क्रमागत counter_संकेत_value अणु
	COUNTER_SIGNAL_LOW = 0,
	COUNTER_SIGNAL_HIGH
पूर्ण;

/**
 * काष्ठा counter_ops - Callbacks from driver
 * @संकेत_पढ़ो:	optional पढ़ो callback क्रम Signal attribute. The पढ़ो
 *			value of the respective Signal should be passed back via
 *			the val parameter.
 * @count_पढ़ो:		optional पढ़ो callback क्रम Count attribute. The पढ़ो
 *			value of the respective Count should be passed back via
 *			the val parameter.
 * @count_ग_लिखो:	optional ग_लिखो callback क्रम Count attribute. The ग_लिखो
 *			value क्रम the respective Count is passed in via the val
 *			parameter.
 * @function_get:	function to get the current count function mode. Returns
 *			0 on success and negative error code on error. The index
 *			of the respective Count's वापसed function mode should
 *			be passed back via the function parameter.
 * @function_set:	function to set the count function mode. function is the
 *			index of the requested function mode from the respective
 *			Count's functions_list array.
 * @action_get:		function to get the current action mode. Returns 0 on
 *			success and negative error code on error. The index of
 *			the respective Synapse's वापसed action mode should be
 *			passed back via the action parameter.
 * @action_set:		function to set the action mode. action is the index of
 *			the requested action mode from the respective Synapse's
 *			actions_list array.
 */
काष्ठा counter_ops अणु
	पूर्णांक (*संकेत_पढ़ो)(काष्ठा counter_device *counter,
			   काष्ठा counter_संकेत *संकेत,
			   क्रमागत counter_संकेत_value *val);
	पूर्णांक (*count_पढ़ो)(काष्ठा counter_device *counter,
			  काष्ठा counter_count *count, अचिन्हित दीर्घ *val);
	पूर्णांक (*count_ग_लिखो)(काष्ठा counter_device *counter,
			   काष्ठा counter_count *count, अचिन्हित दीर्घ val);
	पूर्णांक (*function_get)(काष्ठा counter_device *counter,
			    काष्ठा counter_count *count, माप_प्रकार *function);
	पूर्णांक (*function_set)(काष्ठा counter_device *counter,
			    काष्ठा counter_count *count, माप_प्रकार function);
	पूर्णांक (*action_get)(काष्ठा counter_device *counter,
			  काष्ठा counter_count *count,
			  काष्ठा counter_synapse *synapse, माप_प्रकार *action);
	पूर्णांक (*action_set)(काष्ठा counter_device *counter,
			  काष्ठा counter_count *count,
			  काष्ठा counter_synapse *synapse, माप_प्रकार action);
पूर्ण;

/**
 * काष्ठा counter_device_ext - Counter device extension
 * @name:	attribute name
 * @पढ़ो:	पढ़ो callback क्रम this attribute; may be शून्य
 * @ग_लिखो:	ग_लिखो callback क्रम this attribute; may be शून्य
 * @priv:	data निजी to the driver
 */
काष्ठा counter_device_ext अणु
	स्थिर अक्षर *name;
	sमाप_प्रकार (*पढ़ो)(काष्ठा counter_device *counter, व्योम *priv, अक्षर *buf);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा counter_device *counter, व्योम *priv,
			 स्थिर अक्षर *buf, माप_प्रकार len);
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा counter_device_क्रमागत_ext - Counter क्रमागत extension attribute
 * @items:	Array of strings
 * @num_items:	Number of items specअगरied in @items
 * @set:	Set callback function; may be शून्य
 * @get:	Get callback function; may be शून्य
 *
 * The counter_device_क्रमागत_ext काष्ठाure can be used to implement क्रमागत style
 * Counter extension attributes. Enum style attributes are those which have a
 * set of strings that map to अचिन्हित पूर्णांकeger values. The Generic Counter क्रमागत
 * extension helper code takes care of mapping between value and string, as well
 * as generating a "_available" file which contains a list of all available
 * items. The get callback is used to query the currently active item; the index
 * of the item within the respective items array is वापसed via the 'item'
 * parameter. The set callback is called when the attribute is updated; the
 * 'item' parameter contains the index of the newly activated item within the
 * respective items array.
 */
काष्ठा counter_device_क्रमागत_ext अणु
	स्थिर अक्षर * स्थिर *items;
	माप_प्रकार num_items;
	पूर्णांक (*get)(काष्ठा counter_device *counter, माप_प्रकार *item);
	पूर्णांक (*set)(काष्ठा counter_device *counter, माप_प्रकार item);
पूर्ण;

/**
 * COUNTER_DEVICE_ENUM() - Initialize Counter क्रमागत extension
 * @_name:	Attribute name
 * @_e:		Poपूर्णांकer to a counter_device_क्रमागत_ext काष्ठाure
 *
 * This should usually be used together with COUNTER_DEVICE_ENUM_AVAILABLE()
 */
#घोषणा COUNTER_DEVICE_ENUM(_name, _e) \
अणु \
	.name = (_name), \
	.पढ़ो = counter_device_क्रमागत_पढ़ो, \
	.ग_लिखो = counter_device_क्रमागत_ग_लिखो, \
	.priv = (_e) \
पूर्ण

/**
 * COUNTER_DEVICE_ENUM_AVAILABLE() - Initialize Counter क्रमागत available extension
 * @_name:	Attribute name ("_available" will be appended to the name)
 * @_e:		Poपूर्णांकer to a counter_device_क्रमागत_ext काष्ठाure
 *
 * Creates a पढ़ो only attribute that lists all the available क्रमागत items in a
 * newline separated list. This should usually be used together with
 * COUNTER_DEVICE_ENUM()
 */
#घोषणा COUNTER_DEVICE_ENUM_AVAILABLE(_name, _e) \
अणु \
	.name = (_name "_available"), \
	.पढ़ो = counter_device_क्रमागत_available_पढ़ो, \
	.priv = (_e) \
पूर्ण

/**
 * काष्ठा counter_device - Counter data काष्ठाure
 * @name:		name of the device as it appears in the datasheet
 * @parent:		optional parent device providing the counters
 * @device_state:	पूर्णांकernal device state container
 * @ops:		callbacks from driver
 * @संकेतs:		array of Signals
 * @num_संकेतs:	number of Signals specअगरied in @संकेतs
 * @counts:		array of Counts
 * @num_counts:		number of Counts specअगरied in @counts
 * @ext:		optional array of Counter device extensions
 * @num_ext:		number of Counter device extensions specअगरied in @ext
 * @priv:		optional निजी data supplied by driver
 */
काष्ठा counter_device अणु
	स्थिर अक्षर *name;
	काष्ठा device *parent;
	काष्ठा counter_device_state *device_state;

	स्थिर काष्ठा counter_ops *ops;

	काष्ठा counter_संकेत *संकेतs;
	माप_प्रकार num_संकेतs;
	काष्ठा counter_count *counts;
	माप_प्रकार num_counts;

	स्थिर काष्ठा counter_device_ext *ext;
	माप_प्रकार num_ext;

	व्योम *priv;
पूर्ण;

पूर्णांक counter_रेजिस्टर(काष्ठा counter_device *स्थिर counter);
व्योम counter_unरेजिस्टर(काष्ठा counter_device *स्थिर counter);
पूर्णांक devm_counter_रेजिस्टर(काष्ठा device *dev,
			  काष्ठा counter_device *स्थिर counter);
व्योम devm_counter_unरेजिस्टर(काष्ठा device *dev,
			     काष्ठा counter_device *स्थिर counter);

#पूर्ण_अगर /* _COUNTER_H_ */
