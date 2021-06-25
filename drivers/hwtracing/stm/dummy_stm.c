<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A dummy STM device क्रम sपंचांग/sपंचांग_source class testing.
 * Copyright (c) 2014, Intel Corporation.
 *
 * STM class implements generic infraकाष्ठाure क्रम  System Trace Module devices
 * as defined in MIPI STPv2 specअगरication.
 */

#अघोषित DEBUG
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sपंचांग.h>
#समावेश <uapi/linux/sपंचांग.h>

अटल sमाप_प्रकार notrace
dummy_sपंचांग_packet(काष्ठा sपंचांग_data *sपंचांग_data, अचिन्हित पूर्णांक master,
		 अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक packet, अचिन्हित पूर्णांक flags,
		 अचिन्हित पूर्णांक size, स्थिर अचिन्हित अक्षर *payload)
अणु
#अगर_घोषित DEBUG
	u64 pl = 0;

	अगर (payload)
		pl = *(u64 *)payload;

	अगर (size < 8)
		pl &= (1ull << (size * 8)) - 1;
	trace_prपूर्णांकk("[%u:%u] [pkt: %x/%x] (%llx)\n", master, channel,
		     packet, size, pl);
#पूर्ण_अगर
	वापस size;
पूर्ण

#घोषणा DUMMY_STM_MAX 32

अटल काष्ठा sपंचांग_data dummy_sपंचांग[DUMMY_STM_MAX];

अटल पूर्णांक nr_dummies = 4;

module_param(nr_dummies, पूर्णांक, 0400);

अटल अचिन्हित पूर्णांक fail_mode;

module_param(fail_mode, पूर्णांक, 0600);

अटल अचिन्हित पूर्णांक master_min;

module_param(master_min, पूर्णांक, 0400);

अटल अचिन्हित पूर्णांक master_max = STP_MASTER_MAX;

module_param(master_max, पूर्णांक, 0400);

अटल अचिन्हित पूर्णांक nr_channels = STP_CHANNEL_MAX;

module_param(nr_channels, पूर्णांक, 0400);

अटल पूर्णांक dummy_sपंचांग_link(काष्ठा sपंचांग_data *data, अचिन्हित पूर्णांक master,
			  अचिन्हित पूर्णांक channel)
अणु
	अगर (fail_mode && (channel & fail_mode))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dummy_sपंचांग_init(व्योम)
अणु
	पूर्णांक i, ret = -ENOMEM;

	अगर (nr_dummies < 0 || nr_dummies > DUMMY_STM_MAX)
		वापस -EINVAL;

	अगर (master_min > master_max ||
	    master_max > STP_MASTER_MAX ||
	    nr_channels > STP_CHANNEL_MAX)
		वापस -EINVAL;

	क्रम (i = 0; i < nr_dummies; i++) अणु
		dummy_sपंचांग[i].name = kaप्र_लिखो(GFP_KERNEL, "dummy_stm.%d", i);
		अगर (!dummy_sपंचांग[i].name)
			जाओ fail_unरेजिस्टर;

		dummy_sपंचांग[i].sw_start		= master_min;
		dummy_sपंचांग[i].sw_end		= master_max;
		dummy_sपंचांग[i].sw_nchannels	= nr_channels;
		dummy_sपंचांग[i].packet		= dummy_sपंचांग_packet;
		dummy_sपंचांग[i].link		= dummy_sपंचांग_link;

		ret = sपंचांग_रेजिस्टर_device(शून्य, &dummy_sपंचांग[i], THIS_MODULE);
		अगर (ret)
			जाओ fail_मुक्त;
	पूर्ण

	वापस 0;

fail_unरेजिस्टर:
	क्रम (i--; i >= 0; i--) अणु
		sपंचांग_unरेजिस्टर_device(&dummy_sपंचांग[i]);
fail_मुक्त:
		kमुक्त(dummy_sपंचांग[i].name);
	पूर्ण

	वापस ret;

पूर्ण

अटल व्योम dummy_sपंचांग_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_dummies; i++) अणु
		sपंचांग_unरेजिस्टर_device(&dummy_sपंचांग[i]);
		kमुक्त(dummy_sपंचांग[i].name);
	पूर्ण
पूर्ण

module_init(dummy_sपंचांग_init);
module_निकास(dummy_sपंचांग_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("dummy_stm device");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
