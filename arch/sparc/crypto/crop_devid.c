<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

/* This is a dummy device table linked पूर्णांकo all of the crypto
 * opcode drivers.  It serves to trigger the module स्वतःloading
 * mechanisms in userspace which scan the OF device tree and
 * load any modules which have device table entries that
 * match OF device nodes.
 */
अटल स्थिर काष्ठा of_device_id crypto_opcode_match[] = अणु
	अणु .name = "cpu", .compatible = "sun4v", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, crypto_opcode_match);
