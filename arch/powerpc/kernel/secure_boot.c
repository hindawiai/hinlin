<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 IBM Corporation
 * Author: Nayna Jain
 */
#समावेश <linux/types.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/secure_boot.h>

अटल काष्ठा device_node *get_ppc_fw_sb_node(व्योम)
अणु
	अटल स्थिर काष्ठा of_device_id ids[] = अणु
		अणु .compatible = "ibm,secureboot", पूर्ण,
		अणु .compatible = "ibm,secureboot-v1", पूर्ण,
		अणु .compatible = "ibm,secureboot-v2", पूर्ण,
		अणुपूर्ण,
	पूर्ण;

	वापस of_find_matching_node(शून्य, ids);
पूर्ण

bool is_ppc_secureboot_enabled(व्योम)
अणु
	काष्ठा device_node *node;
	bool enabled = false;
	u32 secureboot;

	node = get_ppc_fw_sb_node();
	enabled = of_property_पढ़ो_bool(node, "os-secureboot-enforcing");
	of_node_put(node);

	अगर (enabled)
		जाओ out;

	अगर (!of_property_पढ़ो_u32(of_root, "ibm,secure-boot", &secureboot))
		enabled = (secureboot > 1);

out:
	pr_info("Secure boot mode %s\n", enabled ? "enabled" : "disabled");

	वापस enabled;
पूर्ण

bool is_ppc_trustedboot_enabled(व्योम)
अणु
	काष्ठा device_node *node;
	bool enabled = false;
	u32 trustedboot;

	node = get_ppc_fw_sb_node();
	enabled = of_property_पढ़ो_bool(node, "trusted-enabled");
	of_node_put(node);

	अगर (enabled)
		जाओ out;

	अगर (!of_property_पढ़ो_u32(of_root, "ibm,trusted-boot", &trustedboot))
		enabled = (trustedboot > 0);

out:
	pr_info("Trusted boot mode %s\n", enabled ? "enabled" : "disabled");

	वापस enabled;
पूर्ण
