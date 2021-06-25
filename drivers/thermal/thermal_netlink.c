<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 Linaro Limited
 *
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 *
 * Generic netlink क्रम thermal management framework
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <net/genetlink.h>
#समावेश <uapi/linux/thermal.h>

#समावेश "thermal_core.h"

अटल स्थिर काष्ठा genl_multicast_group thermal_genl_mcgrps[] = अणु
	अणु .name = THERMAL_GENL_SAMPLING_GROUP_NAME, पूर्ण,
	अणु .name = THERMAL_GENL_EVENT_GROUP_NAME,  पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy thermal_genl_policy[THERMAL_GENL_ATTR_MAX + 1] = अणु
	/* Thermal zone */
	[THERMAL_GENL_ATTR_TZ]			= अणु .type = NLA_NESTED पूर्ण,
	[THERMAL_GENL_ATTR_TZ_ID]		= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_TZ_TEMP]		= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_TZ_TRIP]		= अणु .type = NLA_NESTED पूर्ण,
	[THERMAL_GENL_ATTR_TZ_TRIP_ID]		= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_TZ_TRIP_TEMP]	= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_TZ_TRIP_TYPE]	= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_TZ_TRIP_HYST]	= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_TZ_MODE]		= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_TZ_CDEV_WEIGHT]	= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_TZ_NAME]		= अणु .type = NLA_STRING,
						    .len = THERMAL_NAME_LENGTH पूर्ण,
	/* Governor(s) */
	[THERMAL_GENL_ATTR_TZ_GOV]		= अणु .type = NLA_NESTED पूर्ण,
	[THERMAL_GENL_ATTR_TZ_GOV_NAME]		= अणु .type = NLA_STRING,
						    .len = THERMAL_NAME_LENGTH पूर्ण,
	/* Cooling devices */
	[THERMAL_GENL_ATTR_CDEV]		= अणु .type = NLA_NESTED पूर्ण,
	[THERMAL_GENL_ATTR_CDEV_ID]		= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_CDEV_CUR_STATE]	= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_CDEV_MAX_STATE]	= अणु .type = NLA_U32 पूर्ण,
	[THERMAL_GENL_ATTR_CDEV_NAME]		= अणु .type = NLA_STRING,
						    .len = THERMAL_NAME_LENGTH पूर्ण,
पूर्ण;

काष्ठा param अणु
	काष्ठा nlattr **attrs;
	काष्ठा sk_buff *msg;
	स्थिर अक्षर *name;
	पूर्णांक tz_id;
	पूर्णांक cdev_id;
	पूर्णांक trip_id;
	पूर्णांक trip_temp;
	पूर्णांक trip_type;
	पूर्णांक trip_hyst;
	पूर्णांक temp;
	पूर्णांक cdev_state;
	पूर्णांक cdev_max_state;
पूर्ण;

प्रकार पूर्णांक (*cb_t)(काष्ठा param *);

अटल काष्ठा genl_family thermal_gnl_family;

/************************** Sampling encoding *******************************/

पूर्णांक thermal_genl_sampling_temp(पूर्णांक id, पूर्णांक temp)
अणु
	काष्ठा sk_buff *skb;
	व्योम *hdr;

	skb = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = genlmsg_put(skb, 0, 0, &thermal_gnl_family, 0,
			  THERMAL_GENL_SAMPLING_TEMP);
	अगर (!hdr)
		जाओ out_मुक्त;

	अगर (nla_put_u32(skb, THERMAL_GENL_ATTR_TZ_ID, id))
		जाओ out_cancel;

	अगर (nla_put_u32(skb, THERMAL_GENL_ATTR_TZ_TEMP, temp))
		जाओ out_cancel;

	genlmsg_end(skb, hdr);

	genlmsg_multicast(&thermal_gnl_family, skb, 0, 0, GFP_KERNEL);

	वापस 0;
out_cancel:
	genlmsg_cancel(skb, hdr);
out_मुक्त:
	nlmsg_मुक्त(skb);

	वापस -EMSGSIZE;
पूर्ण

/**************************** Event encoding *********************************/

अटल पूर्णांक thermal_genl_event_tz_create(काष्ठा param *p)
अणु
	अगर (nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_ID, p->tz_id) ||
	    nla_put_string(p->msg, THERMAL_GENL_ATTR_TZ_NAME, p->name))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_event_tz(काष्ठा param *p)
अणु
	अगर (nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_ID, p->tz_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_event_tz_trip_up(काष्ठा param *p)
अणु
	अगर (nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_ID, p->tz_id) ||
	    nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_TRIP_ID, p->trip_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_event_tz_trip_add(काष्ठा param *p)
अणु
	अगर (nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_ID, p->tz_id) ||
	    nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_TRIP_ID, p->trip_id) ||
	    nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_TRIP_TYPE, p->trip_type) ||
	    nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_TRIP_TEMP, p->trip_temp) ||
	    nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_TRIP_HYST, p->trip_hyst))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_event_tz_trip_delete(काष्ठा param *p)
अणु
	अगर (nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_ID, p->tz_id) ||
	    nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_TRIP_ID, p->trip_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_event_cdev_add(काष्ठा param *p)
अणु
	अगर (nla_put_string(p->msg, THERMAL_GENL_ATTR_CDEV_NAME,
			   p->name) ||
	    nla_put_u32(p->msg, THERMAL_GENL_ATTR_CDEV_ID,
			p->cdev_id) ||
	    nla_put_u32(p->msg, THERMAL_GENL_ATTR_CDEV_MAX_STATE,
			p->cdev_max_state))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_event_cdev_delete(काष्ठा param *p)
अणु
	अगर (nla_put_u32(p->msg, THERMAL_GENL_ATTR_CDEV_ID, p->cdev_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_event_cdev_state_update(काष्ठा param *p)
अणु
	अगर (nla_put_u32(p->msg, THERMAL_GENL_ATTR_CDEV_ID,
			p->cdev_id) ||
	    nla_put_u32(p->msg, THERMAL_GENL_ATTR_CDEV_CUR_STATE,
			p->cdev_state))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_event_gov_change(काष्ठा param *p)
अणु
	अगर (nla_put_u32(p->msg, THERMAL_GENL_ATTR_TZ_ID, p->tz_id) ||
	    nla_put_string(p->msg, THERMAL_GENL_ATTR_GOV_NAME, p->name))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

पूर्णांक thermal_genl_event_tz_delete(काष्ठा param *p)
	__attribute__((alias("thermal_genl_event_tz")));

पूर्णांक thermal_genl_event_tz_enable(काष्ठा param *p)
	__attribute__((alias("thermal_genl_event_tz")));

पूर्णांक thermal_genl_event_tz_disable(काष्ठा param *p)
	__attribute__((alias("thermal_genl_event_tz")));

पूर्णांक thermal_genl_event_tz_trip_करोwn(काष्ठा param *p)
	__attribute__((alias("thermal_genl_event_tz_trip_up")));

पूर्णांक thermal_genl_event_tz_trip_change(काष्ठा param *p)
	__attribute__((alias("thermal_genl_event_tz_trip_add")));

अटल cb_t event_cb[] = अणु
	[THERMAL_GENL_EVENT_TZ_CREATE]		= thermal_genl_event_tz_create,
	[THERMAL_GENL_EVENT_TZ_DELETE]		= thermal_genl_event_tz_delete,
	[THERMAL_GENL_EVENT_TZ_ENABLE]		= thermal_genl_event_tz_enable,
	[THERMAL_GENL_EVENT_TZ_DISABLE]		= thermal_genl_event_tz_disable,
	[THERMAL_GENL_EVENT_TZ_TRIP_UP]		= thermal_genl_event_tz_trip_up,
	[THERMAL_GENL_EVENT_TZ_TRIP_DOWN]	= thermal_genl_event_tz_trip_करोwn,
	[THERMAL_GENL_EVENT_TZ_TRIP_CHANGE]	= thermal_genl_event_tz_trip_change,
	[THERMAL_GENL_EVENT_TZ_TRIP_ADD]	= thermal_genl_event_tz_trip_add,
	[THERMAL_GENL_EVENT_TZ_TRIP_DELETE]	= thermal_genl_event_tz_trip_delete,
	[THERMAL_GENL_EVENT_CDEV_ADD]		= thermal_genl_event_cdev_add,
	[THERMAL_GENL_EVENT_CDEV_DELETE]	= thermal_genl_event_cdev_delete,
	[THERMAL_GENL_EVENT_CDEV_STATE_UPDATE]	= thermal_genl_event_cdev_state_update,
	[THERMAL_GENL_EVENT_TZ_GOV_CHANGE]	= thermal_genl_event_gov_change,
पूर्ण;

/*
 * Generic netlink event encoding
 */
अटल पूर्णांक thermal_genl_send_event(क्रमागत thermal_genl_event event,
				   काष्ठा param *p)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक ret = -EMSGSIZE;
	व्योम *hdr;

	msg = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;
	p->msg = msg;

	hdr = genlmsg_put(msg, 0, 0, &thermal_gnl_family, 0, event);
	अगर (!hdr)
		जाओ out_मुक्त_msg;

	ret = event_cb[event](p);
	अगर (ret)
		जाओ out_cancel_msg;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&thermal_gnl_family, msg, 0, 1, GFP_KERNEL);

	वापस 0;

out_cancel_msg:
	genlmsg_cancel(msg, hdr);
out_मुक्त_msg:
	nlmsg_मुक्त(msg);

	वापस ret;
पूर्ण

पूर्णांक thermal_notअगरy_tz_create(पूर्णांक tz_id, स्थिर अक्षर *name)
अणु
	काष्ठा param p = अणु .tz_id = tz_id, .name = name पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_CREATE, &p);
पूर्ण

पूर्णांक thermal_notअगरy_tz_delete(पूर्णांक tz_id)
अणु
	काष्ठा param p = अणु .tz_id = tz_id पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_DELETE, &p);
पूर्ण

पूर्णांक thermal_notअगरy_tz_enable(पूर्णांक tz_id)
अणु
	काष्ठा param p = अणु .tz_id = tz_id पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_ENABLE, &p);
पूर्ण

पूर्णांक thermal_notअगरy_tz_disable(पूर्णांक tz_id)
अणु
	काष्ठा param p = अणु .tz_id = tz_id पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_DISABLE, &p);
पूर्ण

पूर्णांक thermal_notअगरy_tz_trip_करोwn(पूर्णांक tz_id, पूर्णांक trip_id)
अणु
	काष्ठा param p = अणु .tz_id = tz_id, .trip_id = trip_id पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_TRIP_DOWN, &p);
पूर्ण

पूर्णांक thermal_notअगरy_tz_trip_up(पूर्णांक tz_id, पूर्णांक trip_id)
अणु
	काष्ठा param p = अणु .tz_id = tz_id, .trip_id = trip_id पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_TRIP_UP, &p);
पूर्ण

पूर्णांक thermal_notअगरy_tz_trip_add(पूर्णांक tz_id, पूर्णांक trip_id, पूर्णांक trip_type,
			       पूर्णांक trip_temp, पूर्णांक trip_hyst)
अणु
	काष्ठा param p = अणु .tz_id = tz_id, .trip_id = trip_id,
			   .trip_type = trip_type, .trip_temp = trip_temp,
			   .trip_hyst = trip_hyst पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_TRIP_ADD, &p);
पूर्ण

पूर्णांक thermal_notअगरy_tz_trip_delete(पूर्णांक tz_id, पूर्णांक trip_id)
अणु
	काष्ठा param p = अणु .tz_id = tz_id, .trip_id = trip_id पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_TRIP_DELETE, &p);
पूर्ण

पूर्णांक thermal_notअगरy_tz_trip_change(पूर्णांक tz_id, पूर्णांक trip_id, पूर्णांक trip_type,
				  पूर्णांक trip_temp, पूर्णांक trip_hyst)
अणु
	काष्ठा param p = अणु .tz_id = tz_id, .trip_id = trip_id,
			   .trip_type = trip_type, .trip_temp = trip_temp,
			   .trip_hyst = trip_hyst पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_TRIP_CHANGE, &p);
पूर्ण

पूर्णांक thermal_notअगरy_cdev_state_update(पूर्णांक cdev_id, पूर्णांक cdev_state)
अणु
	काष्ठा param p = अणु .cdev_id = cdev_id, .cdev_state = cdev_state पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_CDEV_STATE_UPDATE, &p);
पूर्ण

पूर्णांक thermal_notअगरy_cdev_add(पूर्णांक cdev_id, स्थिर अक्षर *name, पूर्णांक cdev_max_state)
अणु
	काष्ठा param p = अणु .cdev_id = cdev_id, .name = name,
			   .cdev_max_state = cdev_max_state पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_CDEV_ADD, &p);
पूर्ण

पूर्णांक thermal_notअगरy_cdev_delete(पूर्णांक cdev_id)
अणु
	काष्ठा param p = अणु .cdev_id = cdev_id पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_CDEV_DELETE, &p);
पूर्ण

पूर्णांक thermal_notअगरy_tz_gov_change(पूर्णांक tz_id, स्थिर अक्षर *name)
अणु
	काष्ठा param p = अणु .tz_id = tz_id, .name = name पूर्ण;

	वापस thermal_genl_send_event(THERMAL_GENL_EVENT_TZ_GOV_CHANGE, &p);
पूर्ण

/*************************** Command encoding ********************************/

अटल पूर्णांक __thermal_genl_cmd_tz_get_id(काष्ठा thermal_zone_device *tz,
					व्योम *data)
अणु
	काष्ठा sk_buff *msg = data;

	अगर (nla_put_u32(msg, THERMAL_GENL_ATTR_TZ_ID, tz->id) ||
	    nla_put_string(msg, THERMAL_GENL_ATTR_TZ_NAME, tz->type))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_cmd_tz_get_id(काष्ठा param *p)
अणु
	काष्ठा sk_buff *msg = p->msg;
	काष्ठा nlattr *start_tz;
	पूर्णांक ret;

	start_tz = nla_nest_start(msg, THERMAL_GENL_ATTR_TZ);
	अगर (!start_tz)
		वापस -EMSGSIZE;

	ret = क्रम_each_thermal_zone(__thermal_genl_cmd_tz_get_id, msg);
	अगर (ret)
		जाओ out_cancel_nest;

	nla_nest_end(msg, start_tz);

	वापस 0;

out_cancel_nest:
	nla_nest_cancel(msg, start_tz);

	वापस ret;
पूर्ण

अटल पूर्णांक thermal_genl_cmd_tz_get_trip(काष्ठा param *p)
अणु
	काष्ठा sk_buff *msg = p->msg;
	काष्ठा thermal_zone_device *tz;
	काष्ठा nlattr *start_trip;
	पूर्णांक i, id;

	अगर (!p->attrs[THERMAL_GENL_ATTR_TZ_ID])
		वापस -EINVAL;

	id = nla_get_u32(p->attrs[THERMAL_GENL_ATTR_TZ_ID]);

	tz = thermal_zone_get_by_id(id);
	अगर (!tz)
		वापस -EINVAL;

	start_trip = nla_nest_start(msg, THERMAL_GENL_ATTR_TZ_TRIP);
	अगर (!start_trip)
		वापस -EMSGSIZE;

	mutex_lock(&tz->lock);

	क्रम (i = 0; i < tz->trips; i++) अणु

		क्रमागत thermal_trip_type type;
		पूर्णांक temp, hyst;

		tz->ops->get_trip_type(tz, i, &type);
		tz->ops->get_trip_temp(tz, i, &temp);
		tz->ops->get_trip_hyst(tz, i, &hyst);

		अगर (nla_put_u32(msg, THERMAL_GENL_ATTR_TZ_TRIP_ID, i) ||
		    nla_put_u32(msg, THERMAL_GENL_ATTR_TZ_TRIP_TYPE, type) ||
		    nla_put_u32(msg, THERMAL_GENL_ATTR_TZ_TRIP_TEMP, temp) ||
		    nla_put_u32(msg, THERMAL_GENL_ATTR_TZ_TRIP_HYST, hyst))
			जाओ out_cancel_nest;
	पूर्ण

	mutex_unlock(&tz->lock);

	nla_nest_end(msg, start_trip);

	वापस 0;

out_cancel_nest:
	mutex_unlock(&tz->lock);

	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक thermal_genl_cmd_tz_get_temp(काष्ठा param *p)
अणु
	काष्ठा sk_buff *msg = p->msg;
	काष्ठा thermal_zone_device *tz;
	पूर्णांक temp, ret, id;

	अगर (!p->attrs[THERMAL_GENL_ATTR_TZ_ID])
		वापस -EINVAL;

	id = nla_get_u32(p->attrs[THERMAL_GENL_ATTR_TZ_ID]);

	tz = thermal_zone_get_by_id(id);
	अगर (!tz)
		वापस -EINVAL;

	ret = thermal_zone_get_temp(tz, &temp);
	अगर (ret)
		वापस ret;

	अगर (nla_put_u32(msg, THERMAL_GENL_ATTR_TZ_ID, id) ||
	    nla_put_u32(msg, THERMAL_GENL_ATTR_TZ_TEMP, temp))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_cmd_tz_get_gov(काष्ठा param *p)
अणु
	काष्ठा sk_buff *msg = p->msg;
	काष्ठा thermal_zone_device *tz;
	पूर्णांक id, ret = 0;

	अगर (!p->attrs[THERMAL_GENL_ATTR_TZ_ID])
		वापस -EINVAL;

	id = nla_get_u32(p->attrs[THERMAL_GENL_ATTR_TZ_ID]);

	tz = thermal_zone_get_by_id(id);
	अगर (!tz)
		वापस -EINVAL;

	mutex_lock(&tz->lock);

	अगर (nla_put_u32(msg, THERMAL_GENL_ATTR_TZ_ID, id) ||
	    nla_put_string(msg, THERMAL_GENL_ATTR_TZ_GOV_NAME,
			   tz->governor->name))
		ret = -EMSGSIZE;

	mutex_unlock(&tz->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक __thermal_genl_cmd_cdev_get(काष्ठा thermal_cooling_device *cdev,
				       व्योम *data)
अणु
	काष्ठा sk_buff *msg = data;

	अगर (nla_put_u32(msg, THERMAL_GENL_ATTR_CDEV_ID, cdev->id))
		वापस -EMSGSIZE;

	अगर (nla_put_string(msg, THERMAL_GENL_ATTR_CDEV_NAME, cdev->type))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक thermal_genl_cmd_cdev_get(काष्ठा param *p)
अणु
	काष्ठा sk_buff *msg = p->msg;
	काष्ठा nlattr *start_cdev;
	पूर्णांक ret;

	start_cdev = nla_nest_start(msg, THERMAL_GENL_ATTR_CDEV);
	अगर (!start_cdev)
		वापस -EMSGSIZE;

	ret = क्रम_each_thermal_cooling_device(__thermal_genl_cmd_cdev_get, msg);
	अगर (ret)
		जाओ out_cancel_nest;

	nla_nest_end(msg, start_cdev);

	वापस 0;
out_cancel_nest:
	nla_nest_cancel(msg, start_cdev);

	वापस ret;
पूर्ण

अटल cb_t cmd_cb[] = अणु
	[THERMAL_GENL_CMD_TZ_GET_ID]	= thermal_genl_cmd_tz_get_id,
	[THERMAL_GENL_CMD_TZ_GET_TRIP]	= thermal_genl_cmd_tz_get_trip,
	[THERMAL_GENL_CMD_TZ_GET_TEMP]	= thermal_genl_cmd_tz_get_temp,
	[THERMAL_GENL_CMD_TZ_GET_GOV]	= thermal_genl_cmd_tz_get_gov,
	[THERMAL_GENL_CMD_CDEV_GET]	= thermal_genl_cmd_cdev_get,
पूर्ण;

अटल पूर्णांक thermal_genl_cmd_dumpit(काष्ठा sk_buff *skb,
				   काष्ठा netlink_callback *cb)
अणु
	काष्ठा param p = अणु .msg = skb पूर्ण;
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	पूर्णांक cmd = info->op.cmd;
	पूर्णांक ret;
	व्योम *hdr;

	hdr = genlmsg_put(skb, 0, 0, &thermal_gnl_family, 0, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	ret = cmd_cb[cmd](&p);
	अगर (ret)
		जाओ out_cancel_msg;

	genlmsg_end(skb, hdr);

	वापस 0;

out_cancel_msg:
	genlmsg_cancel(skb, hdr);

	वापस ret;
पूर्ण

अटल पूर्णांक thermal_genl_cmd_करोit(काष्ठा sk_buff *skb,
				 काष्ठा genl_info *info)
अणु
	काष्ठा param p = अणु .attrs = info->attrs पूर्ण;
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	पूर्णांक cmd = info->genlhdr->cmd;
	पूर्णांक ret = -EMSGSIZE;

	msg = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;
	p.msg = msg;

	hdr = genlmsg_put_reply(msg, info, &thermal_gnl_family, 0, cmd);
	अगर (!hdr)
		जाओ out_मुक्त_msg;

	ret = cmd_cb[cmd](&p);
	अगर (ret)
		जाओ out_cancel_msg;

	genlmsg_end(msg, hdr);

	वापस genlmsg_reply(msg, info);

out_cancel_msg:
	genlmsg_cancel(msg, hdr);
out_मुक्त_msg:
	nlmsg_मुक्त(msg);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops thermal_genl_ops[] = अणु
	अणु
		.cmd = THERMAL_GENL_CMD_TZ_GET_ID,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit = thermal_genl_cmd_dumpit,
	पूर्ण,
	अणु
		.cmd = THERMAL_GENL_CMD_TZ_GET_TRIP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = thermal_genl_cmd_करोit,
	पूर्ण,
	अणु
		.cmd = THERMAL_GENL_CMD_TZ_GET_TEMP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = thermal_genl_cmd_करोit,
	पूर्ण,
	अणु
		.cmd = THERMAL_GENL_CMD_TZ_GET_GOV,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = thermal_genl_cmd_करोit,
	पूर्ण,
	अणु
		.cmd = THERMAL_GENL_CMD_CDEV_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit = thermal_genl_cmd_dumpit,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family thermal_gnl_family __ro_after_init = अणु
	.hdrsize	= 0,
	.name		= THERMAL_GENL_FAMILY_NAME,
	.version	= THERMAL_GENL_VERSION,
	.maxattr	= THERMAL_GENL_ATTR_MAX,
	.policy		= thermal_genl_policy,
	.small_ops	= thermal_genl_ops,
	.n_small_ops	= ARRAY_SIZE(thermal_genl_ops),
	.mcgrps		= thermal_genl_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(thermal_genl_mcgrps),
पूर्ण;

पूर्णांक __init thermal_netlink_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&thermal_gnl_family);
पूर्ण
