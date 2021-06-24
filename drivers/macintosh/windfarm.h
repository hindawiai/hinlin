<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Windfarm PowerMac thermal control.
 *
 * (c) Copyright 2005 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#अगर_अघोषित __WINDFARM_H__
#घोषणा __WINDFARM_H__

#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/device.h>

/* Display a 16.16 fixed poपूर्णांक value */
#घोषणा FIX32TOPRINT(f)	(((s32)(f)) >> 16),(((((s32)(f)) & 0xffff) * 1000) >> 16)

/*
 * Control objects
 */

काष्ठा wf_control;

काष्ठा wf_control_ops अणु
	पूर्णांक			(*set_value)(काष्ठा wf_control *ct, s32 val);
	पूर्णांक			(*get_value)(काष्ठा wf_control *ct, s32 *val);
	s32			(*get_min)(काष्ठा wf_control *ct);
	s32			(*get_max)(काष्ठा wf_control *ct);
	व्योम			(*release)(काष्ठा wf_control *ct);
	काष्ठा module		*owner;
पूर्ण;

काष्ठा wf_control अणु
	काष्ठा list_head		link;
	स्थिर काष्ठा wf_control_ops	*ops;
	स्थिर अक्षर			*name;
	पूर्णांक				type;
	काष्ठा kref			ref;
	काष्ठा device_attribute		attr;
	व्योम				*priv;
पूर्ण;

#घोषणा WF_CONTROL_TYPE_GENERIC		0
#घोषणा WF_CONTROL_RPM_FAN		1
#घोषणा WF_CONTROL_PWM_FAN		2


/* Note about lअगरeसमय rules: wf_रेजिस्टर_control() will initialize
 * the kref and wf_unरेजिस्टर_control will decrement it, thus the
 * object creating/disposing a given control shouldn't assume it
 * still exists after wf_unरेजिस्टर_control has been called.
 */
बाह्य पूर्णांक wf_रेजिस्टर_control(काष्ठा wf_control *ct);
बाह्य व्योम wf_unरेजिस्टर_control(काष्ठा wf_control *ct);
बाह्य पूर्णांक wf_get_control(काष्ठा wf_control *ct);
बाह्य व्योम wf_put_control(काष्ठा wf_control *ct);

अटल अंतरभूत पूर्णांक wf_control_set_max(काष्ठा wf_control *ct)
अणु
	s32 vmax = ct->ops->get_max(ct);
	वापस ct->ops->set_value(ct, vmax);
पूर्ण

अटल अंतरभूत पूर्णांक wf_control_set_min(काष्ठा wf_control *ct)
अणु
	s32 vmin = ct->ops->get_min(ct);
	वापस ct->ops->set_value(ct, vmin);
पूर्ण

अटल अंतरभूत पूर्णांक wf_control_set(काष्ठा wf_control *ct, s32 val)
अणु
	वापस ct->ops->set_value(ct, val);
पूर्ण

अटल अंतरभूत पूर्णांक wf_control_get(काष्ठा wf_control *ct, s32 *val)
अणु
	वापस ct->ops->get_value(ct, val);
पूर्ण

अटल अंतरभूत s32 wf_control_get_min(काष्ठा wf_control *ct)
अणु
	वापस ct->ops->get_min(ct);
पूर्ण

अटल अंतरभूत s32 wf_control_get_max(काष्ठा wf_control *ct)
अणु
	वापस ct->ops->get_max(ct);
पूर्ण

/*
 * Sensor objects
 */

काष्ठा wf_sensor;

काष्ठा wf_sensor_ops अणु
	पूर्णांक			(*get_value)(काष्ठा wf_sensor *sr, s32 *val);
	व्योम			(*release)(काष्ठा wf_sensor *sr);
	काष्ठा module		*owner;
पूर्ण;

काष्ठा wf_sensor अणु
	काष्ठा list_head		link;
	स्थिर काष्ठा wf_sensor_ops	*ops;
	स्थिर अक्षर			*name;
	काष्ठा kref			ref;
	काष्ठा device_attribute		attr;
	व्योम				*priv;
पूर्ण;

/* Same lअगरeसमय rules as controls */
बाह्य पूर्णांक wf_रेजिस्टर_sensor(काष्ठा wf_sensor *sr);
बाह्य व्योम wf_unरेजिस्टर_sensor(काष्ठा wf_sensor *sr);
बाह्य पूर्णांक wf_get_sensor(काष्ठा wf_sensor *sr);
बाह्य व्योम wf_put_sensor(काष्ठा wf_sensor *sr);

अटल अंतरभूत पूर्णांक wf_sensor_get(काष्ठा wf_sensor *sr, s32 *val)
अणु
	वापस sr->ops->get_value(sr, val);
पूर्ण

/* For use by clients. Note that we are a bit racy here since
 * notअगरier_block करोesn't have a module owner field. I may fix
 * it one day ...
 *
 * LOCKING NOTE !
 *
 * All "events" except WF_EVENT_TICK are called with an पूर्णांकernal mutex
 * held which will deadlock अगर you call basically any core routine.
 * So करोn't ! Just take note of the event and करो your actual operations
 * from the ticker.
 *
 */
बाह्य पूर्णांक wf_रेजिस्टर_client(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक wf_unरेजिस्टर_client(काष्ठा notअगरier_block *nb);

/* Overtemp conditions. Those are refcounted */
बाह्य व्योम wf_set_overtemp(व्योम);
बाह्य व्योम wf_clear_overtemp(व्योम);

#घोषणा WF_EVENT_NEW_CONTROL	0 /* param is wf_control * */
#घोषणा WF_EVENT_NEW_SENSOR	1 /* param is wf_sensor * */
#घोषणा WF_EVENT_OVERTEMP	2 /* no param */
#घोषणा WF_EVENT_NORMALTEMP	3 /* overtemp condition cleared */
#घोषणा WF_EVENT_TICK		4 /* 1 second tick */

/* Note: If that driver माला_लो more broad use, we could replace the
 * simplistic overtemp bits with "environmental conditions". That
 * could then be used to also notअगरy of things like fan failure,
 * हाल खोलो, battery conditions, ...
 */

#पूर्ण_अगर /* __WINDFARM_H__ */
