<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple kernel driver to link kernel Ftrace and an STM device
 * Copyright (c) 2016, Linaro Ltd.
 *
 * STM Ftrace will be रेजिस्टरed as a trace_export.
 */

#समावेश <linux/module.h>
#समावेश <linux/sपंचांग.h>
#समावेश <linux/trace.h>

#घोषणा STM_FTRACE_NR_CHANNELS 1
#घोषणा STM_FTRACE_CHAN 0

अटल पूर्णांक sपंचांग_ftrace_link(काष्ठा sपंचांग_source_data *data);
अटल व्योम sपंचांग_ftrace_unlink(काष्ठा sपंचांग_source_data *data);

अटल काष्ठा sपंचांग_ftrace अणु
	काष्ठा sपंचांग_source_data	data;
	काष्ठा trace_export	ftrace;
पूर्ण sपंचांग_ftrace = अणु
	.data	= अणु
		.name		= "ftrace",
		.nr_chans	= STM_FTRACE_NR_CHANNELS,
		.link		= sपंचांग_ftrace_link,
		.unlink		= sपंचांग_ftrace_unlink,
	पूर्ण,
पूर्ण;

/**
 * sपंचांग_ftrace_ग_लिखो() - ग_लिखो data to STM via 'stm_ftrace' source
 * @buf:	buffer containing the data packet
 * @len:	length of the data packet
 */
अटल व्योम notrace
sपंचांग_ftrace_ग_लिखो(काष्ठा trace_export *export, स्थिर व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा sपंचांग_ftrace *sपंचांग = container_of(export, काष्ठा sपंचांग_ftrace, ftrace);
	/* This is called from trace प्रणाली with preemption disabled */
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	sपंचांग_source_ग_लिखो(&sपंचांग->data, STM_FTRACE_CHAN + cpu, buf, len);
पूर्ण

अटल पूर्णांक sपंचांग_ftrace_link(काष्ठा sपंचांग_source_data *data)
अणु
	काष्ठा sपंचांग_ftrace *sf = container_of(data, काष्ठा sपंचांग_ftrace, data);

	sf->ftrace.ग_लिखो = sपंचांग_ftrace_ग_लिखो;
	sf->ftrace.flags = TRACE_EXPORT_FUNCTION | TRACE_EXPORT_EVENT
			| TRACE_EXPORT_MARKER;

	वापस रेजिस्टर_ftrace_export(&sf->ftrace);
पूर्ण

अटल व्योम sपंचांग_ftrace_unlink(काष्ठा sपंचांग_source_data *data)
अणु
	काष्ठा sपंचांग_ftrace *sf = container_of(data, काष्ठा sपंचांग_ftrace, data);

	unरेजिस्टर_ftrace_export(&sf->ftrace);
पूर्ण

अटल पूर्णांक __init sपंचांग_ftrace_init(व्योम)
अणु
	पूर्णांक ret;

	sपंचांग_ftrace.data.nr_chans = roundup_घात_of_two(num_possible_cpus());
	ret = sपंचांग_source_रेजिस्टर_device(शून्य, &sपंचांग_ftrace.data);
	अगर (ret)
		pr_err("Failed to register stm_source - ftrace.\n");

	वापस ret;
पूर्ण

अटल व्योम __निकास sपंचांग_ftrace_निकास(व्योम)
अणु
	sपंचांग_source_unरेजिस्टर_device(&sपंचांग_ftrace.data);
पूर्ण

module_init(sपंचांग_ftrace_init);
module_निकास(sपंचांग_ftrace_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("stm_ftrace driver");
MODULE_AUTHOR("Chunyan Zhang <zhang.chunyan@linaro.org>");
