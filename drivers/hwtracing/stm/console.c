<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple kernel console driver क्रम STM devices
 * Copyright (c) 2014, Intel Corporation.
 *
 * STM console will send kernel messages over STM devices to a trace host.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/slab.h>
#समावेश <linux/sपंचांग.h>

अटल पूर्णांक sपंचांग_console_link(काष्ठा sपंचांग_source_data *data);
अटल व्योम sपंचांग_console_unlink(काष्ठा sपंचांग_source_data *data);

अटल काष्ठा sपंचांग_console अणु
	काष्ठा sपंचांग_source_data	data;
	काष्ठा console		console;
पूर्ण sपंचांग_console = अणु
	.data	= अणु
		.name		= "console",
		.nr_chans	= 1,
		.link		= sपंचांग_console_link,
		.unlink		= sपंचांग_console_unlink,
	पूर्ण,
पूर्ण;

अटल व्योम
sपंचांग_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *buf, अचिन्हित len)
अणु
	काष्ठा sपंचांग_console *sc = container_of(con, काष्ठा sपंचांग_console, console);

	sपंचांग_source_ग_लिखो(&sc->data, 0, buf, len);
पूर्ण

अटल पूर्णांक sपंचांग_console_link(काष्ठा sपंचांग_source_data *data)
अणु
	काष्ठा sपंचांग_console *sc = container_of(data, काष्ठा sपंचांग_console, data);

	म_नकल(sc->console.name, "stm_console");
	sc->console.ग_लिखो = sपंचांग_console_ग_लिखो;
	sc->console.flags = CON_ENABLED | CON_PRINTBUFFER;
	रेजिस्टर_console(&sc->console);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग_console_unlink(काष्ठा sपंचांग_source_data *data)
अणु
	काष्ठा sपंचांग_console *sc = container_of(data, काष्ठा sपंचांग_console, data);

	unरेजिस्टर_console(&sc->console);
पूर्ण

अटल पूर्णांक sपंचांग_console_init(व्योम)
अणु
	वापस sपंचांग_source_रेजिस्टर_device(शून्य, &sपंचांग_console.data);
पूर्ण

अटल व्योम sपंचांग_console_निकास(व्योम)
अणु
	sपंचांग_source_unरेजिस्टर_device(&sपंचांग_console.data);
पूर्ण

module_init(sपंचांग_console_init);
module_निकास(sपंचांग_console_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("stm_console driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
