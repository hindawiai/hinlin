<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * async.h: Asynchronous function calls क्रम boot perक्रमmance
 *
 * (C) Copyright 2009 Intel Corporation
 * Author: Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */
#अगर_अघोषित __ASYNC_H__
#घोषणा __ASYNC_H__

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/numa.h>
#समावेश <linux/device.h>

प्रकार u64 async_cookie_t;
प्रकार व्योम (*async_func_t) (व्योम *data, async_cookie_t cookie);
काष्ठा async_करोमुख्य अणु
	काष्ठा list_head pending;
	अचिन्हित रेजिस्टरed:1;
पूर्ण;

/*
 * करोमुख्य participates in global async_synchronize_full
 */
#घोषणा ASYNC_DOMAIN(_name) \
	काष्ठा async_करोमुख्य _name = अणु .pending = LIST_HEAD_INIT(_name.pending),	\
				      .रेजिस्टरed = 1 पूर्ण

/*
 * करोमुख्य is मुक्त to go out of scope as soon as all pending work is
 * complete, this करोमुख्य करोes not participate in async_synchronize_full
 */
#घोषणा ASYNC_DOMAIN_EXCLUSIVE(_name) \
	काष्ठा async_करोमुख्य _name = अणु .pending = LIST_HEAD_INIT(_name.pending), \
				      .रेजिस्टरed = 0 पूर्ण

async_cookie_t async_schedule_node(async_func_t func, व्योम *data,
				   पूर्णांक node);
async_cookie_t async_schedule_node_करोमुख्य(async_func_t func, व्योम *data,
					  पूर्णांक node,
					  काष्ठा async_करोमुख्य *करोमुख्य);

/**
 * async_schedule - schedule a function क्रम asynchronous execution
 * @func: function to execute asynchronously
 * @data: data poपूर्णांकer to pass to the function
 *
 * Returns an async_cookie_t that may be used क्रम checkpoपूर्णांकing later.
 * Note: This function may be called from atomic or non-atomic contexts.
 */
अटल अंतरभूत async_cookie_t async_schedule(async_func_t func, व्योम *data)
अणु
	वापस async_schedule_node(func, data, NUMA_NO_NODE);
पूर्ण

/**
 * async_schedule_करोमुख्य - schedule a function क्रम asynchronous execution within a certain करोमुख्य
 * @func: function to execute asynchronously
 * @data: data poपूर्णांकer to pass to the function
 * @करोमुख्य: the करोमुख्य
 *
 * Returns an async_cookie_t that may be used क्रम checkpoपूर्णांकing later.
 * @करोमुख्य may be used in the async_synchronize_*_करोमुख्य() functions to
 * रुको within a certain synchronization करोमुख्य rather than globally.
 * Note: This function may be called from atomic or non-atomic contexts.
 */
अटल अंतरभूत async_cookie_t
async_schedule_करोमुख्य(async_func_t func, व्योम *data,
		      काष्ठा async_करोमुख्य *करोमुख्य)
अणु
	वापस async_schedule_node_करोमुख्य(func, data, NUMA_NO_NODE, करोमुख्य);
पूर्ण

/**
 * async_schedule_dev - A device specअगरic version of async_schedule
 * @func: function to execute asynchronously
 * @dev: device argument to be passed to function
 *
 * Returns an async_cookie_t that may be used क्रम checkpoपूर्णांकing later.
 * @dev is used as both the argument क्रम the function and to provide NUMA
 * context क्रम where to run the function. By करोing this we can try to
 * provide क्रम the best possible outcome by operating on the device on the
 * CPUs बंदst to the device.
 * Note: This function may be called from atomic or non-atomic contexts.
 */
अटल अंतरभूत async_cookie_t
async_schedule_dev(async_func_t func, काष्ठा device *dev)
अणु
	वापस async_schedule_node(func, dev, dev_to_node(dev));
पूर्ण

/**
 * async_schedule_dev_करोमुख्य - A device specअगरic version of async_schedule_करोमुख्य
 * @func: function to execute asynchronously
 * @dev: device argument to be passed to function
 * @करोमुख्य: the करोमुख्य
 *
 * Returns an async_cookie_t that may be used क्रम checkpoपूर्णांकing later.
 * @dev is used as both the argument क्रम the function and to provide NUMA
 * context क्रम where to run the function. By करोing this we can try to
 * provide क्रम the best possible outcome by operating on the device on the
 * CPUs बंदst to the device.
 * @करोमुख्य may be used in the async_synchronize_*_करोमुख्य() functions to
 * रुको within a certain synchronization करोमुख्य rather than globally.
 * Note: This function may be called from atomic or non-atomic contexts.
 */
अटल अंतरभूत async_cookie_t
async_schedule_dev_करोमुख्य(async_func_t func, काष्ठा device *dev,
			  काष्ठा async_करोमुख्य *करोमुख्य)
अणु
	वापस async_schedule_node_करोमुख्य(func, dev, dev_to_node(dev), करोमुख्य);
पूर्ण

बाह्य व्योम async_synchronize_full(व्योम);
बाह्य व्योम async_synchronize_full_करोमुख्य(काष्ठा async_करोमुख्य *करोमुख्य);
बाह्य व्योम async_synchronize_cookie(async_cookie_t cookie);
बाह्य व्योम async_synchronize_cookie_करोमुख्य(async_cookie_t cookie,
					    काष्ठा async_करोमुख्य *करोमुख्य);
बाह्य bool current_is_async(व्योम);
#पूर्ण_अगर
