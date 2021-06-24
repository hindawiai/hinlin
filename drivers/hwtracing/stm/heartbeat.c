<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple heartbeat STM source driver
 * Copyright (c) 2016, Intel Corporation.
 *
 * Heartbeat STM source will send repetitive messages over STM devices to a
 * trace host.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/sपंचांग.h>

#घोषणा STM_HEARTBEAT_MAX	32

अटल पूर्णांक nr_devs = 4;
अटल पूर्णांक पूर्णांकerval_ms = 10;

module_param(nr_devs, पूर्णांक, 0400);
module_param(पूर्णांकerval_ms, पूर्णांक, 0600);

अटल काष्ठा sपंचांग_heartbeat अणु
	काष्ठा sपंचांग_source_data	data;
	काष्ठा hrसमयr		hrसमयr;
	अचिन्हित पूर्णांक		active;
पूर्ण sपंचांग_heartbeat[STM_HEARTBEAT_MAX];

अटल स्थिर अक्षर str[] = "heartbeat stm source driver is here to serve you";

अटल क्रमागत hrसमयr_restart sपंचांग_heartbeat_hrसमयr_handler(काष्ठा hrसमयr *hr)
अणु
	काष्ठा sपंचांग_heartbeat *heartbeat = container_of(hr, काष्ठा sपंचांग_heartbeat,
						       hrसमयr);

	sपंचांग_source_ग_लिखो(&heartbeat->data, 0, str, माप str);
	अगर (heartbeat->active)
		hrसमयr_क्रमward_now(hr, ms_to_kसमय(पूर्णांकerval_ms));

	वापस heartbeat->active ? HRTIMER_RESTART : HRTIMER_NORESTART;
पूर्ण

अटल पूर्णांक sपंचांग_heartbeat_link(काष्ठा sपंचांग_source_data *data)
अणु
	काष्ठा sपंचांग_heartbeat *heartbeat =
		container_of(data, काष्ठा sपंचांग_heartbeat, data);

	heartbeat->active = 1;
	hrसमयr_start(&heartbeat->hrसमयr, ms_to_kसमय(पूर्णांकerval_ms),
		      HRTIMER_MODE_ABS);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग_heartbeat_unlink(काष्ठा sपंचांग_source_data *data)
अणु
	काष्ठा sपंचांग_heartbeat *heartbeat =
		container_of(data, काष्ठा sपंचांग_heartbeat, data);

	heartbeat->active = 0;
	hrसमयr_cancel(&heartbeat->hrसमयr);
पूर्ण

अटल पूर्णांक sपंचांग_heartbeat_init(व्योम)
अणु
	पूर्णांक i, ret;

	अगर (nr_devs < 0 || nr_devs > STM_HEARTBEAT_MAX)
		वापस -EINVAL;

	क्रम (i = 0; i < nr_devs; i++) अणु
		sपंचांग_heartbeat[i].data.name =
			kaप्र_लिखो(GFP_KERNEL, "heartbeat.%d", i);
		अगर (!sपंचांग_heartbeat[i].data.name) अणु
			ret = -ENOMEM;
			जाओ fail_unरेजिस्टर;
		पूर्ण

		sपंचांग_heartbeat[i].data.nr_chans	= 1;
		sपंचांग_heartbeat[i].data.link	= sपंचांग_heartbeat_link;
		sपंचांग_heartbeat[i].data.unlink	= sपंचांग_heartbeat_unlink;
		hrसमयr_init(&sपंचांग_heartbeat[i].hrसमयr, CLOCK_MONOTONIC,
			     HRTIMER_MODE_ABS);
		sपंचांग_heartbeat[i].hrसमयr.function =
			sपंचांग_heartbeat_hrसमयr_handler;

		ret = sपंचांग_source_रेजिस्टर_device(शून्य, &sपंचांग_heartbeat[i].data);
		अगर (ret)
			जाओ fail_मुक्त;
	पूर्ण

	वापस 0;

fail_unरेजिस्टर:
	क्रम (i--; i >= 0; i--) अणु
		sपंचांग_source_unरेजिस्टर_device(&sपंचांग_heartbeat[i].data);
fail_मुक्त:
		kमुक्त(sपंचांग_heartbeat[i].data.name);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sपंचांग_heartbeat_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_devs; i++) अणु
		sपंचांग_source_unरेजिस्टर_device(&sपंचांग_heartbeat[i].data);
		kमुक्त(sपंचांग_heartbeat[i].data.name);
	पूर्ण
पूर्ण

module_init(sपंचांग_heartbeat_init);
module_निकास(sपंचांग_heartbeat_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("stm_heartbeat driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
