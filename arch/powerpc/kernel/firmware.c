<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Extracted from cputable.c
 *
 *  Copyright (C) 2001 Ben. Herrenschmidt (benh@kernel.crashing.org)
 *
 *  Modअगरications क्रम ppc64:
 *      Copyright (C) 2003 Dave Engebretsen <engebret@us.ibm.com>
 *  Copyright (C) 2005 Stephen Rothwell, IBM Corporation
 */

#समावेश <linux/export.h>
#समावेश <linux/cache.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/kvm_guest.h>

#अगर_घोषित CONFIG_PPC64
अचिन्हित दीर्घ घातerpc_firmware_features __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(घातerpc_firmware_features);
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_PSERIES) || defined(CONFIG_KVM_GUEST)
DEFINE_STATIC_KEY_FALSE(kvm_guest);
bool check_kvm_guest(व्योम)
अणु
	काष्ठा device_node *hyper_node;

	hyper_node = of_find_node_by_path("/hypervisor");
	अगर (!hyper_node)
		वापस false;

	अगर (!of_device_is_compatible(hyper_node, "linux,kvm"))
		वापस false;

	अटल_branch_enable(&kvm_guest);
	वापस true;
पूर्ण
#पूर्ण_अगर
