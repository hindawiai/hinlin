<शैली गुरु>
/*
 * Copyright (C) 2001 - 2003 Sistina Software
 * Copyright (C) 2004 - 2008 Red Hat, Inc. All rights reserved.
 *
 * kcopyd provides a simple पूर्णांकerface क्रम copying an area of one
 * block-device to one or more other block-devices, either synchronous
 * or with an asynchronous completion notअगरication.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित _LINUX_DM_KCOPYD_H
#घोषणा _LINUX_DM_KCOPYD_H

#अगर_घोषित __KERNEL__

#समावेश <linux/dm-पन.स>

/* FIXME: make this configurable */
#घोषणा DM_KCOPYD_MAX_REGIONS 8

#घोषणा DM_KCOPYD_IGNORE_ERROR 1
#घोषणा DM_KCOPYD_WRITE_SEQ    2

काष्ठा dm_kcopyd_throttle अणु
	अचिन्हित throttle;
	अचिन्हित num_io_jobs;
	अचिन्हित io_period;
	अचिन्हित total_period;
	अचिन्हित last_jअगरfies;
पूर्ण;

/*
 * kcopyd clients that want to support throttling must pass an initialised
 * dm_kcopyd_throttle काष्ठा पूर्णांकo dm_kcopyd_client_create().
 * Two or more clients may share the same instance of this काष्ठा between
 * them अगर they wish to be throttled as a group.
 *
 * This macro also creates a corresponding module parameter to configure
 * the amount of throttling.
 */
#घोषणा DECLARE_DM_KCOPYD_THROTTLE_WITH_MODULE_PARM(name, description)	\
अटल काष्ठा dm_kcopyd_throttle dm_kcopyd_throttle = अणु 100, 0, 0, 0, 0 पूर्ण; \
module_param_named(name, dm_kcopyd_throttle.throttle, uपूर्णांक, 0644); \
MODULE_PARM_DESC(name, description)

/*
 * To use kcopyd you must first create a dm_kcopyd_client object.
 * throttle can be शून्य अगर you करोn't want any throttling.
 */
काष्ठा dm_kcopyd_client;
काष्ठा dm_kcopyd_client *dm_kcopyd_client_create(काष्ठा dm_kcopyd_throttle *throttle);
व्योम dm_kcopyd_client_destroy(काष्ठा dm_kcopyd_client *kc);

/*
 * Submit a copy job to kcopyd.  This is built on top of the
 * previous three fns.
 *
 * पढ़ो_err is a boolean,
 * ग_लिखो_err is a bitset, with 1 bit क्रम each destination region
 */
प्रकार व्योम (*dm_kcopyd_notअगरy_fn)(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err,
				    व्योम *context);

व्योम dm_kcopyd_copy(काष्ठा dm_kcopyd_client *kc, काष्ठा dm_io_region *from,
		    अचिन्हित num_dests, काष्ठा dm_io_region *dests,
		    अचिन्हित flags, dm_kcopyd_notअगरy_fn fn, व्योम *context);

/*
 * Prepare a callback and submit it via the kcopyd thपढ़ो.
 *
 * dm_kcopyd_prepare_callback allocates a callback काष्ठाure and वापसs it.
 * It must not be called from पूर्णांकerrupt context.
 * The वापसed value should be passed पूर्णांकo dm_kcopyd_करो_callback.
 *
 * dm_kcopyd_करो_callback submits the callback.
 * It may be called from पूर्णांकerrupt context.
 * The callback is issued from the kcopyd thपढ़ो.
 */
व्योम *dm_kcopyd_prepare_callback(काष्ठा dm_kcopyd_client *kc,
				 dm_kcopyd_notअगरy_fn fn, व्योम *context);
व्योम dm_kcopyd_करो_callback(व्योम *job, पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err);

व्योम dm_kcopyd_zero(काष्ठा dm_kcopyd_client *kc,
		    अचिन्हित num_dests, काष्ठा dm_io_region *dests,
		    अचिन्हित flags, dm_kcopyd_notअगरy_fn fn, व्योम *context);

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _LINUX_DM_KCOPYD_H */
