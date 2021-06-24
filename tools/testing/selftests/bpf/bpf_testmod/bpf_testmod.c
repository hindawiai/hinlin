<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <linux/error-injection.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/percpu-defs.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "bpf_testmod.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "bpf_testmod-events.h"

DEFINE_PER_CPU(पूर्णांक, bpf_tesपंचांगod_ksym_percpu) = 123;

noअंतरभूत sमाप_प्रकार
bpf_tesपंचांगod_test_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
		      काष्ठा bin_attribute *bin_attr,
		      अक्षर *buf, loff_t off, माप_प्रकार len)
अणु
	काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx ctx = अणु
		.buf = buf,
		.off = off,
		.len = len,
	पूर्ण;

	trace_bpf_tesपंचांगod_test_पढ़ो(current, &ctx);

	वापस -EIO; /* always fail */
पूर्ण
EXPORT_SYMBOL(bpf_tesपंचांगod_test_पढ़ो);
ALLOW_ERROR_INJECTION(bpf_tesपंचांगod_test_पढ़ो, ERRNO);

noअंतरभूत sमाप_प्रकार
bpf_tesपंचांगod_test_ग_लिखो(काष्ठा file *file, काष्ठा kobject *kobj,
		      काष्ठा bin_attribute *bin_attr,
		      अक्षर *buf, loff_t off, माप_प्रकार len)
अणु
	काष्ठा bpf_tesपंचांगod_test_ग_लिखो_ctx ctx = अणु
		.buf = buf,
		.off = off,
		.len = len,
	पूर्ण;

	trace_bpf_tesपंचांगod_test_ग_लिखो_bare(current, &ctx);

	वापस -EIO; /* always fail */
पूर्ण
EXPORT_SYMBOL(bpf_tesपंचांगod_test_ग_लिखो);
ALLOW_ERROR_INJECTION(bpf_tesपंचांगod_test_ग_लिखो, ERRNO);

अटल काष्ठा bin_attribute bin_attr_bpf_tesपंचांगod_file __ro_after_init = अणु
	.attr = अणु .name = "bpf_testmod", .mode = 0666, पूर्ण,
	.पढ़ो = bpf_tesपंचांगod_test_पढ़ो,
	.ग_लिखो = bpf_tesपंचांगod_test_ग_लिखो,
पूर्ण;

अटल पूर्णांक bpf_tesपंचांगod_init(व्योम)
अणु
	वापस sysfs_create_bin_file(kernel_kobj, &bin_attr_bpf_tesपंचांगod_file);
पूर्ण

अटल व्योम bpf_tesपंचांगod_निकास(व्योम)
अणु
	वापस sysfs_हटाओ_bin_file(kernel_kobj, &bin_attr_bpf_tesपंचांगod_file);
पूर्ण

module_init(bpf_tesपंचांगod_init);
module_निकास(bpf_tesपंचांगod_निकास);

MODULE_AUTHOR("Andrii Nakryiko");
MODULE_DESCRIPTION("BPF selftests module");
MODULE_LICENSE("Dual BSD/GPL");

