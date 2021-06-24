<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर IS_ENABLED(CONFIG_NET_DEVLINK)

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM devlink

#अगर !defined(_TRACE_DEVLINK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_DEVLINK_H

#समावेश <linux/device.h>
#समावेश <net/devlink.h>
#समावेश <linux/tracepoपूर्णांक.h>

/*
 * Tracepoपूर्णांक क्रम devlink hardware message:
 */
TRACE_EVENT(devlink_hwmsg,
	TP_PROTO(स्थिर काष्ठा devlink *devlink, bool incoming,
		 अचिन्हित दीर्घ type, स्थिर u8 *buf, माप_प्रकार len),

	TP_ARGS(devlink, incoming, type, buf, len),

	TP_STRUCT__entry(
		__string(bus_name, devlink->dev->bus->name)
		__string(dev_name, dev_name(devlink->dev))
		__string(driver_name, devlink->dev->driver->name)
		__field(bool, incoming)
		__field(अचिन्हित दीर्घ, type)
		__dynamic_array(u8, buf, len)
		__field(माप_प्रकार, len)
	),

	TP_fast_assign(
		__assign_str(bus_name, devlink->dev->bus->name);
		__assign_str(dev_name, dev_name(devlink->dev));
		__assign_str(driver_name, devlink->dev->driver->name);
		__entry->incoming = incoming;
		__entry->type = type;
		स_नकल(__get_dynamic_array(buf), buf, len);
		__entry->len = len;
	),

	TP_prपूर्णांकk("bus_name=%s dev_name=%s driver_name=%s incoming=%d type=%lu buf=0x[%*phD] len=%zu",
		  __get_str(bus_name), __get_str(dev_name),
		  __get_str(driver_name), __entry->incoming, __entry->type,
		  (पूर्णांक) __entry->len, __get_dynamic_array(buf), __entry->len)
);

/*
 * Tracepoपूर्णांक क्रम devlink hardware error:
 */
TRACE_EVENT(devlink_hwerr,
	TP_PROTO(स्थिर काष्ठा devlink *devlink, पूर्णांक err, स्थिर अक्षर *msg),

	TP_ARGS(devlink, err, msg),

	TP_STRUCT__entry(
		__string(bus_name, devlink->dev->bus->name)
		__string(dev_name, dev_name(devlink->dev))
		__string(driver_name, devlink->dev->driver->name)
		__field(पूर्णांक, err)
		__string(msg, msg)
		),

	TP_fast_assign(
		__assign_str(bus_name, devlink->dev->bus->name);
		__assign_str(dev_name, dev_name(devlink->dev));
		__assign_str(driver_name, devlink->dev->driver->name);
		__entry->err = err;
		__assign_str(msg, msg);
		),

	TP_prपूर्णांकk("bus_name=%s dev_name=%s driver_name=%s err=%d %s",
			__get_str(bus_name), __get_str(dev_name),
			__get_str(driver_name), __entry->err, __get_str(msg))
);

/*
 * Tracepoपूर्णांक क्रम devlink health message:
 */
TRACE_EVENT(devlink_health_report,
	TP_PROTO(स्थिर काष्ठा devlink *devlink, स्थिर अक्षर *reporter_name,
		 स्थिर अक्षर *msg),

	TP_ARGS(devlink, reporter_name, msg),

	TP_STRUCT__entry(
		__string(bus_name, devlink->dev->bus->name)
		__string(dev_name, dev_name(devlink->dev))
		__string(driver_name, devlink->dev->driver->name)
		__string(reporter_name, msg)
		__string(msg, msg)
	),

	TP_fast_assign(
		__assign_str(bus_name, devlink->dev->bus->name);
		__assign_str(dev_name, dev_name(devlink->dev));
		__assign_str(driver_name, devlink->dev->driver->name);
		__assign_str(reporter_name, reporter_name);
		__assign_str(msg, msg);
	),

	TP_prपूर्णांकk("bus_name=%s dev_name=%s driver_name=%s reporter_name=%s: %s",
		  __get_str(bus_name), __get_str(dev_name),
		  __get_str(driver_name), __get_str(reporter_name),
		  __get_str(msg))
);

/*
 * Tracepoपूर्णांक क्रम devlink health recover पातed message:
 */
TRACE_EVENT(devlink_health_recover_पातed,
	TP_PROTO(स्थिर काष्ठा devlink *devlink, स्थिर अक्षर *reporter_name,
		 bool health_state, u64 समय_since_last_recover),

	TP_ARGS(devlink, reporter_name, health_state, समय_since_last_recover),

	TP_STRUCT__entry(
		__string(bus_name, devlink->dev->bus->name)
		__string(dev_name, dev_name(devlink->dev))
		__string(driver_name, devlink->dev->driver->name)
		__string(reporter_name, reporter_name)
		__field(bool, health_state)
		__field(u64, समय_since_last_recover)
	),

	TP_fast_assign(
		__assign_str(bus_name, devlink->dev->bus->name);
		__assign_str(dev_name, dev_name(devlink->dev));
		__assign_str(driver_name, devlink->dev->driver->name);
		__assign_str(reporter_name, reporter_name);
		__entry->health_state = health_state;
		__entry->समय_since_last_recover = समय_since_last_recover;
	),

	TP_prपूर्णांकk("bus_name=%s dev_name=%s driver_name=%s reporter_name=%s: health_state=%d time_since_last_recover=%llu recover aborted",
		  __get_str(bus_name), __get_str(dev_name),
		  __get_str(driver_name), __get_str(reporter_name),
		  __entry->health_state,
		  __entry->समय_since_last_recover)
);

/*
 * Tracepoपूर्णांक क्रम devlink health reporter state update:
 */
TRACE_EVENT(devlink_health_reporter_state_update,
	TP_PROTO(स्थिर काष्ठा devlink *devlink, स्थिर अक्षर *reporter_name,
		 bool new_state),

	TP_ARGS(devlink, reporter_name, new_state),

	TP_STRUCT__entry(
		__string(bus_name, devlink->dev->bus->name)
		__string(dev_name, dev_name(devlink->dev))
		__string(driver_name, devlink->dev->driver->name)
		__string(reporter_name, reporter_name)
		__field(u8, new_state)
	),

	TP_fast_assign(
		__assign_str(bus_name, devlink->dev->bus->name);
		__assign_str(dev_name, dev_name(devlink->dev));
		__assign_str(driver_name, devlink->dev->driver->name);
		__assign_str(reporter_name, reporter_name);
		__entry->new_state = new_state;
	),

	TP_prपूर्णांकk("bus_name=%s dev_name=%s driver_name=%s reporter_name=%s: new_state=%d",
		  __get_str(bus_name), __get_str(dev_name),
		  __get_str(driver_name), __get_str(reporter_name),
		  __entry->new_state)
);

/*
 * Tracepoपूर्णांक क्रम devlink packet trap:
 */
TRACE_EVENT(devlink_trap_report,
	TP_PROTO(स्थिर काष्ठा devlink *devlink, काष्ठा sk_buff *skb,
		 स्थिर काष्ठा devlink_trap_metadata *metadata),

	TP_ARGS(devlink, skb, metadata),

	TP_STRUCT__entry(
		__string(bus_name, devlink->dev->bus->name)
		__string(dev_name, dev_name(devlink->dev))
		__string(driver_name, devlink->dev->driver->name)
		__string(trap_name, metadata->trap_name)
		__string(trap_group_name, metadata->trap_group_name)
		__dynamic_array(अक्षर, input_dev_name, IFNAMSIZ)
	),

	TP_fast_assign(
		काष्ठा net_device *input_dev = metadata->input_dev;

		__assign_str(bus_name, devlink->dev->bus->name);
		__assign_str(dev_name, dev_name(devlink->dev));
		__assign_str(driver_name, devlink->dev->driver->name);
		__assign_str(trap_name, metadata->trap_name);
		__assign_str(trap_group_name, metadata->trap_group_name);
		__assign_str(input_dev_name,
			     (input_dev ? input_dev->name : "NULL"));
	),

	TP_prपूर्णांकk("bus_name=%s dev_name=%s driver_name=%s trap_name=%s "
		  "trap_group_name=%s input_dev_name=%s", __get_str(bus_name),
		  __get_str(dev_name), __get_str(driver_name),
		  __get_str(trap_name), __get_str(trap_group_name),
		  __get_str(input_dev_name))
);

#पूर्ण_अगर /* _TRACE_DEVLINK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>

#अन्यथा /* CONFIG_NET_DEVLINK */

#अगर !defined(_TRACE_DEVLINK_H)
#घोषणा _TRACE_DEVLINK_H

#समावेश <net/devlink.h>

अटल अंतरभूत व्योम trace_devlink_hwmsg(स्थिर काष्ठा devlink *devlink,
				       bool incoming, अचिन्हित दीर्घ type,
				       स्थिर u8 *buf, माप_प्रकार len)
अणु
पूर्ण

अटल अंतरभूत व्योम trace_devlink_hwerr(स्थिर काष्ठा devlink *devlink,
				       पूर्णांक err, स्थिर अक्षर *msg)
अणु
पूर्ण
#पूर्ण_अगर /* _TRACE_DEVLINK_H */

#पूर्ण_अगर
