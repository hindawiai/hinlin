<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Basic framing protocol क्रम STM devices.
 * Copyright (c) 2018, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/sपंचांग.h>
#समावेश "stm.h"

अटल sमाप_प्रकार basic_ग_लिखो(काष्ठा sपंचांग_data *data, काष्ठा sपंचांग_output *output,
			   अचिन्हित पूर्णांक chan, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक c = output->channel + chan;
	अचिन्हित पूर्णांक m = output->master;
	स्थिर अचिन्हित अक्षर nil = 0;
	sमाप_प्रकार sz;

	sz = sपंचांग_data_ग_लिखो(data, m, c, true, buf, count);
	अगर (sz > 0)
		data->packet(data, m, c, STP_PACKET_FLAG, 0, 0, &nil);

	वापस sz;
पूर्ण

अटल स्थिर काष्ठा sपंचांग_protocol_driver basic_pdrv = अणु
	.owner	= THIS_MODULE,
	.name	= "p_basic",
	.ग_लिखो	= basic_ग_लिखो,
पूर्ण;

अटल पूर्णांक basic_sपंचांग_init(व्योम)
अणु
	वापस sपंचांग_रेजिस्टर_protocol(&basic_pdrv);
पूर्ण

अटल व्योम basic_sपंचांग_निकास(व्योम)
अणु
	sपंचांग_unरेजिस्टर_protocol(&basic_pdrv);
पूर्ण

module_init(basic_sपंचांग_init);
module_निकास(basic_sपंचांग_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Basic STM framing protocol driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
