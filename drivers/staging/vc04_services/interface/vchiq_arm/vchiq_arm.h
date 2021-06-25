<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2014 Raspberry Pi (Trading) Ltd. All rights reserved.
 * Copyright (c) 2010-2012 Broadcom. All rights reserved.
 */

#अगर_अघोषित VCHIQ_ARM_H
#घोषणा VCHIQ_ARM_H

#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/atomic.h>
#समावेश "vchiq_core.h"
#समावेश "vchiq_debugfs.h"

क्रमागत USE_TYPE_E अणु
	USE_TYPE_SERVICE,
	USE_TYPE_VCHIQ
पूर्ण;

काष्ठा vchiq_arm_state अणु
	/* Keepalive-related data */
	काष्ठा task_काष्ठा *ka_thपढ़ो;
	काष्ठा completion ka_evt;
	atomic_t ka_use_count;
	atomic_t ka_use_ack_count;
	atomic_t ka_release_count;

	rwlock_t susp_res_lock;

	काष्ठा vchiq_state *state;

	/*
	 * Global use count क्रम videocore.
	 * This is equal to the sum of the use counts क्रम all services.  When
	 * this hits zero the videocore suspend procedure will be initiated.
	 */
	पूर्णांक videocore_use_count;

	/*
	 * Use count to track requests from videocore peer.
	 * This use count is not associated with a service, so needs to be
	 * tracked separately with the state.
	 */
	पूर्णांक peer_use_count;

	/*
	 * Flag to indicate that the first vchiq connect has made it through.
	 * This means that both sides should be fully पढ़ोy, and we should
	 * be able to suspend after this poपूर्णांक.
	 */
	पूर्णांक first_connect;
पूर्ण;

काष्ठा vchiq_drvdata अणु
	स्थिर अचिन्हित पूर्णांक cache_line_size;
	काष्ठा rpi_firmware *fw;
पूर्ण;

बाह्य पूर्णांक vchiq_arm_log_level;
बाह्य पूर्णांक vchiq_susp_log_level;

पूर्णांक vchiq_platक्रमm_init(काष्ठा platक्रमm_device *pdev,
			काष्ठा vchiq_state *state);

बाह्य काष्ठा vchiq_state *
vchiq_get_state(व्योम);

बाह्य क्रमागत vchiq_status
vchiq_arm_init_state(काष्ठा vchiq_state *state,
		     काष्ठा vchiq_arm_state *arm_state);

बाह्य व्योम
vchiq_check_suspend(काष्ठा vchiq_state *state);
क्रमागत vchiq_status
vchiq_use_service(अचिन्हित पूर्णांक handle);

बाह्य क्रमागत vchiq_status
vchiq_release_service(अचिन्हित पूर्णांक handle);

बाह्य क्रमागत vchiq_status
vchiq_check_service(काष्ठा vchiq_service *service);

बाह्य व्योम
vchiq_dump_platक्रमm_use_state(काष्ठा vchiq_state *state);

बाह्य व्योम
vchiq_dump_service_use_state(काष्ठा vchiq_state *state);

बाह्य काष्ठा vchiq_arm_state*
vchiq_platक्रमm_get_arm_state(काष्ठा vchiq_state *state);


बाह्य क्रमागत vchiq_status
vchiq_use_पूर्णांकernal(काष्ठा vchiq_state *state, काष्ठा vchiq_service *service,
		   क्रमागत USE_TYPE_E use_type);
बाह्य क्रमागत vchiq_status
vchiq_release_पूर्णांकernal(काष्ठा vchiq_state *state,
		       काष्ठा vchiq_service *service);

बाह्य काष्ठा vchiq_debugfs_node *
vchiq_instance_get_debugfs_node(काष्ठा vchiq_instance *instance);

बाह्य पूर्णांक
vchiq_instance_get_use_count(काष्ठा vchiq_instance *instance);

बाह्य पूर्णांक
vchiq_instance_get_pid(काष्ठा vchiq_instance *instance);

बाह्य पूर्णांक
vchiq_instance_get_trace(काष्ठा vchiq_instance *instance);

बाह्य व्योम
vchiq_instance_set_trace(काष्ठा vchiq_instance *instance, पूर्णांक trace);

#पूर्ण_अगर /* VCHIQ_ARM_H */
