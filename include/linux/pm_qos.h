<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions related to Power Management Quality of Service (PM QoS).
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * Authors:
 *	Mark Gross <mgross@linux.पूर्णांकel.com>
 *	Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#अगर_अघोषित _LINUX_PM_QOS_H
#घोषणा _LINUX_PM_QOS_H

#समावेश <linux/plist.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/device.h>

क्रमागत pm_qos_flags_status अणु
	PM_QOS_FLAGS_UNDEFINED = -1,
	PM_QOS_FLAGS_NONE,
	PM_QOS_FLAGS_SOME,
	PM_QOS_FLAGS_ALL,
पूर्ण;

#घोषणा PM_QOS_DEFAULT_VALUE	(-1)
#घोषणा PM_QOS_LATENCY_ANY	S32_MAX
#घोषणा PM_QOS_LATENCY_ANY_NS	((s64)PM_QOS_LATENCY_ANY * NSEC_PER_USEC)

#घोषणा PM_QOS_CPU_LATENCY_DEFAULT_VALUE	(2000 * USEC_PER_SEC)
#घोषणा PM_QOS_RESUME_LATENCY_DEFAULT_VALUE	PM_QOS_LATENCY_ANY
#घोषणा PM_QOS_RESUME_LATENCY_NO_CONSTRAINT	PM_QOS_LATENCY_ANY
#घोषणा PM_QOS_RESUME_LATENCY_NO_CONSTRAINT_NS	PM_QOS_LATENCY_ANY_NS
#घोषणा PM_QOS_LATENCY_TOLERANCE_DEFAULT_VALUE	0
#घोषणा PM_QOS_MIN_FREQUENCY_DEFAULT_VALUE	0
#घोषणा PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE	FREQ_QOS_MAX_DEFAULT_VALUE
#घोषणा PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT	(-1)

#घोषणा PM_QOS_FLAG_NO_POWER_OFF	(1 << 0)

क्रमागत pm_qos_type अणु
	PM_QOS_UNITIALIZED,
	PM_QOS_MAX,		/* वापस the largest value */
	PM_QOS_MIN,		/* वापस the smallest value */
पूर्ण;

/*
 * Note: The lockless पढ़ो path depends on the CPU accessing target_value
 * or effective_flags atomically.  Atomic access is only guaranteed on all CPU
 * types linux supports क्रम 32 bit quantites
 */
काष्ठा pm_qos_स्थिरraपूर्णांकs अणु
	काष्ठा plist_head list;
	s32 target_value;	/* Do not change to 64 bit */
	s32 शेष_value;
	s32 no_स्थिरraपूर्णांक_value;
	क्रमागत pm_qos_type type;
	काष्ठा blocking_notअगरier_head *notअगरiers;
पूर्ण;

काष्ठा pm_qos_request अणु
	काष्ठा plist_node node;
	काष्ठा pm_qos_स्थिरraपूर्णांकs *qos;
पूर्ण;

काष्ठा pm_qos_flags_request अणु
	काष्ठा list_head node;
	s32 flags;	/* Do not change to 64 bit */
पूर्ण;

काष्ठा pm_qos_flags अणु
	काष्ठा list_head list;
	s32 effective_flags;	/* Do not change to 64 bit */
पूर्ण;


#घोषणा FREQ_QOS_MIN_DEFAULT_VALUE	0
#घोषणा FREQ_QOS_MAX_DEFAULT_VALUE	S32_MAX

क्रमागत freq_qos_req_type अणु
	FREQ_QOS_MIN = 1,
	FREQ_QOS_MAX,
पूर्ण;

काष्ठा freq_स्थिरraपूर्णांकs अणु
	काष्ठा pm_qos_स्थिरraपूर्णांकs min_freq;
	काष्ठा blocking_notअगरier_head min_freq_notअगरiers;
	काष्ठा pm_qos_स्थिरraपूर्णांकs max_freq;
	काष्ठा blocking_notअगरier_head max_freq_notअगरiers;
पूर्ण;

काष्ठा freq_qos_request अणु
	क्रमागत freq_qos_req_type type;
	काष्ठा plist_node pnode;
	काष्ठा freq_स्थिरraपूर्णांकs *qos;
पूर्ण;


क्रमागत dev_pm_qos_req_type अणु
	DEV_PM_QOS_RESUME_LATENCY = 1,
	DEV_PM_QOS_LATENCY_TOLERANCE,
	DEV_PM_QOS_MIN_FREQUENCY,
	DEV_PM_QOS_MAX_FREQUENCY,
	DEV_PM_QOS_FLAGS,
पूर्ण;

काष्ठा dev_pm_qos_request अणु
	क्रमागत dev_pm_qos_req_type type;
	जोड़ अणु
		काष्ठा plist_node pnode;
		काष्ठा pm_qos_flags_request flr;
		काष्ठा freq_qos_request freq;
	पूर्ण data;
	काष्ठा device *dev;
पूर्ण;

काष्ठा dev_pm_qos अणु
	काष्ठा pm_qos_स्थिरraपूर्णांकs resume_latency;
	काष्ठा pm_qos_स्थिरraपूर्णांकs latency_tolerance;
	काष्ठा freq_स्थिरraपूर्णांकs freq;
	काष्ठा pm_qos_flags flags;
	काष्ठा dev_pm_qos_request *resume_latency_req;
	काष्ठा dev_pm_qos_request *latency_tolerance_req;
	काष्ठा dev_pm_qos_request *flags_req;
पूर्ण;

/* Action requested to pm_qos_update_target */
क्रमागत pm_qos_req_action अणु
	PM_QOS_ADD_REQ,		/* Add a new request */
	PM_QOS_UPDATE_REQ,	/* Update an existing request */
	PM_QOS_REMOVE_REQ	/* Remove an existing request */
पूर्ण;

अटल अंतरभूत पूर्णांक dev_pm_qos_request_active(काष्ठा dev_pm_qos_request *req)
अणु
	वापस req->dev != शून्य;
पूर्ण

s32 pm_qos_पढ़ो_value(काष्ठा pm_qos_स्थिरraपूर्णांकs *c);
पूर्णांक pm_qos_update_target(काष्ठा pm_qos_स्थिरraपूर्णांकs *c, काष्ठा plist_node *node,
			 क्रमागत pm_qos_req_action action, पूर्णांक value);
bool pm_qos_update_flags(काष्ठा pm_qos_flags *pqf,
			 काष्ठा pm_qos_flags_request *req,
			 क्रमागत pm_qos_req_action action, s32 val);

#अगर_घोषित CONFIG_CPU_IDLE
s32 cpu_latency_qos_limit(व्योम);
bool cpu_latency_qos_request_active(काष्ठा pm_qos_request *req);
व्योम cpu_latency_qos_add_request(काष्ठा pm_qos_request *req, s32 value);
व्योम cpu_latency_qos_update_request(काष्ठा pm_qos_request *req, s32 new_value);
व्योम cpu_latency_qos_हटाओ_request(काष्ठा pm_qos_request *req);
#अन्यथा
अटल अंतरभूत s32 cpu_latency_qos_limit(व्योम) अणु वापस पूर्णांक_उच्च; पूर्ण
अटल अंतरभूत bool cpu_latency_qos_request_active(काष्ठा pm_qos_request *req)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम cpu_latency_qos_add_request(काष्ठा pm_qos_request *req,
					       s32 value) अणुपूर्ण
अटल अंतरभूत व्योम cpu_latency_qos_update_request(काष्ठा pm_qos_request *req,
						  s32 new_value) अणुपूर्ण
अटल अंतरभूत व्योम cpu_latency_qos_हटाओ_request(काष्ठा pm_qos_request *req) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
क्रमागत pm_qos_flags_status __dev_pm_qos_flags(काष्ठा device *dev, s32 mask);
क्रमागत pm_qos_flags_status dev_pm_qos_flags(काष्ठा device *dev, s32 mask);
s32 __dev_pm_qos_resume_latency(काष्ठा device *dev);
s32 dev_pm_qos_पढ़ो_value(काष्ठा device *dev, क्रमागत dev_pm_qos_req_type type);
पूर्णांक dev_pm_qos_add_request(काष्ठा device *dev, काष्ठा dev_pm_qos_request *req,
			   क्रमागत dev_pm_qos_req_type type, s32 value);
पूर्णांक dev_pm_qos_update_request(काष्ठा dev_pm_qos_request *req, s32 new_value);
पूर्णांक dev_pm_qos_हटाओ_request(काष्ठा dev_pm_qos_request *req);
पूर्णांक dev_pm_qos_add_notअगरier(काष्ठा device *dev,
			    काष्ठा notअगरier_block *notअगरier,
			    क्रमागत dev_pm_qos_req_type type);
पूर्णांक dev_pm_qos_हटाओ_notअगरier(काष्ठा device *dev,
			       काष्ठा notअगरier_block *notअगरier,
			       क्रमागत dev_pm_qos_req_type type);
व्योम dev_pm_qos_स्थिरraपूर्णांकs_init(काष्ठा device *dev);
व्योम dev_pm_qos_स्थिरraपूर्णांकs_destroy(काष्ठा device *dev);
पूर्णांक dev_pm_qos_add_ancestor_request(काष्ठा device *dev,
				    काष्ठा dev_pm_qos_request *req,
				    क्रमागत dev_pm_qos_req_type type, s32 value);
पूर्णांक dev_pm_qos_expose_latency_limit(काष्ठा device *dev, s32 value);
व्योम dev_pm_qos_hide_latency_limit(काष्ठा device *dev);
पूर्णांक dev_pm_qos_expose_flags(काष्ठा device *dev, s32 value);
व्योम dev_pm_qos_hide_flags(काष्ठा device *dev);
पूर्णांक dev_pm_qos_update_flags(काष्ठा device *dev, s32 mask, bool set);
s32 dev_pm_qos_get_user_latency_tolerance(काष्ठा device *dev);
पूर्णांक dev_pm_qos_update_user_latency_tolerance(काष्ठा device *dev, s32 val);
पूर्णांक dev_pm_qos_expose_latency_tolerance(काष्ठा device *dev);
व्योम dev_pm_qos_hide_latency_tolerance(काष्ठा device *dev);

अटल अंतरभूत s32 dev_pm_qos_requested_resume_latency(काष्ठा device *dev)
अणु
	वापस dev->घातer.qos->resume_latency_req->data.pnode.prio;
पूर्ण

अटल अंतरभूत s32 dev_pm_qos_requested_flags(काष्ठा device *dev)
अणु
	वापस dev->घातer.qos->flags_req->data.flr.flags;
पूर्ण

अटल अंतरभूत s32 dev_pm_qos_raw_resume_latency(काष्ठा device *dev)
अणु
	वापस IS_ERR_OR_शून्य(dev->घातer.qos) ?
		PM_QOS_RESUME_LATENCY_NO_CONSTRAINT :
		pm_qos_पढ़ो_value(&dev->घातer.qos->resume_latency);
पूर्ण
#अन्यथा
अटल अंतरभूत क्रमागत pm_qos_flags_status __dev_pm_qos_flags(काष्ठा device *dev,
							  s32 mask)
			अणु वापस PM_QOS_FLAGS_UNDEFINED; पूर्ण
अटल अंतरभूत क्रमागत pm_qos_flags_status dev_pm_qos_flags(काष्ठा device *dev,
							s32 mask)
			अणु वापस PM_QOS_FLAGS_UNDEFINED; पूर्ण
अटल अंतरभूत s32 __dev_pm_qos_resume_latency(काष्ठा device *dev)
			अणु वापस PM_QOS_RESUME_LATENCY_NO_CONSTRAINT; पूर्ण
अटल अंतरभूत s32 dev_pm_qos_पढ़ो_value(काष्ठा device *dev,
					क्रमागत dev_pm_qos_req_type type)
अणु
	चयन (type) अणु
	हाल DEV_PM_QOS_RESUME_LATENCY:
		वापस PM_QOS_RESUME_LATENCY_NO_CONSTRAINT;
	हाल DEV_PM_QOS_MIN_FREQUENCY:
		वापस PM_QOS_MIN_FREQUENCY_DEFAULT_VALUE;
	हाल DEV_PM_QOS_MAX_FREQUENCY:
		वापस PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE;
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_qos_add_request(काष्ठा device *dev,
					 काष्ठा dev_pm_qos_request *req,
					 क्रमागत dev_pm_qos_req_type type,
					 s32 value)
			अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_update_request(काष्ठा dev_pm_qos_request *req,
					    s32 new_value)
			अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_हटाओ_request(काष्ठा dev_pm_qos_request *req)
			अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_add_notअगरier(काष्ठा device *dev,
					  काष्ठा notअगरier_block *notअगरier,
					  क्रमागत dev_pm_qos_req_type type)
			अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_हटाओ_notअगरier(काष्ठा device *dev,
					     काष्ठा notअगरier_block *notअगरier,
					     क्रमागत dev_pm_qos_req_type type)
			अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dev_pm_qos_स्थिरraपूर्णांकs_init(काष्ठा device *dev)
अणु
	dev->घातer.घातer_state = PMSG_ON;
पूर्ण
अटल अंतरभूत व्योम dev_pm_qos_स्थिरraपूर्णांकs_destroy(काष्ठा device *dev)
अणु
	dev->घातer.घातer_state = PMSG_INVALID;
पूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_add_ancestor_request(काष्ठा device *dev,
						  काष्ठा dev_pm_qos_request *req,
						  क्रमागत dev_pm_qos_req_type type,
						  s32 value)
			अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_expose_latency_limit(काष्ठा device *dev, s32 value)
			अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dev_pm_qos_hide_latency_limit(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_expose_flags(काष्ठा device *dev, s32 value)
			अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dev_pm_qos_hide_flags(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_update_flags(काष्ठा device *dev, s32 m, bool set)
			अणु वापस 0; पूर्ण
अटल अंतरभूत s32 dev_pm_qos_get_user_latency_tolerance(काष्ठा device *dev)
			अणु वापस PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT; पूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_update_user_latency_tolerance(काष्ठा device *dev, s32 val)
			अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dev_pm_qos_expose_latency_tolerance(काष्ठा device *dev)
			अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dev_pm_qos_hide_latency_tolerance(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत s32 dev_pm_qos_requested_resume_latency(काष्ठा device *dev)
अणु
	वापस PM_QOS_RESUME_LATENCY_NO_CONSTRAINT;
पूर्ण
अटल अंतरभूत s32 dev_pm_qos_requested_flags(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत s32 dev_pm_qos_raw_resume_latency(काष्ठा device *dev)
अणु
	वापस PM_QOS_RESUME_LATENCY_NO_CONSTRAINT;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक freq_qos_request_active(काष्ठा freq_qos_request *req)
अणु
	वापस !IS_ERR_OR_शून्य(req->qos);
पूर्ण

व्योम freq_स्थिरraपूर्णांकs_init(काष्ठा freq_स्थिरraपूर्णांकs *qos);

s32 freq_qos_पढ़ो_value(काष्ठा freq_स्थिरraपूर्णांकs *qos,
			क्रमागत freq_qos_req_type type);

पूर्णांक freq_qos_add_request(काष्ठा freq_स्थिरraपूर्णांकs *qos,
			 काष्ठा freq_qos_request *req,
			 क्रमागत freq_qos_req_type type, s32 value);
पूर्णांक freq_qos_update_request(काष्ठा freq_qos_request *req, s32 new_value);
पूर्णांक freq_qos_हटाओ_request(काष्ठा freq_qos_request *req);
पूर्णांक freq_qos_apply(काष्ठा freq_qos_request *req,
		   क्रमागत pm_qos_req_action action, s32 value);

पूर्णांक freq_qos_add_notअगरier(काष्ठा freq_स्थिरraपूर्णांकs *qos,
			  क्रमागत freq_qos_req_type type,
			  काष्ठा notअगरier_block *notअगरier);
पूर्णांक freq_qos_हटाओ_notअगरier(काष्ठा freq_स्थिरraपूर्णांकs *qos,
			     क्रमागत freq_qos_req_type type,
			     काष्ठा notअगरier_block *notअगरier);

#पूर्ण_अगर
