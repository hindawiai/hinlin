<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 IBM Corporation
 *
 * Author: Ashley Lai <ashleydlai@gmail.com>
 *         Nayna Jain <nayna@linux.vnet.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Read the event log created by the firmware on PPC64
 */

#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/tpm_eventlog.h>

#समावेश "../tpm.h"
#समावेश "common.h"

पूर्णांक tpm_पढ़ो_log_of(काष्ठा tpm_chip *chip)
अणु
	काष्ठा device_node *np;
	स्थिर u32 *sizep;
	स्थिर u64 *basep;
	काष्ठा tpm_bios_log *log;
	u32 size;
	u64 base;

	log = &chip->log;
	अगर (chip->dev.parent && chip->dev.parent->of_node)
		np = chip->dev.parent->of_node;
	अन्यथा
		वापस -ENODEV;

	अगर (of_property_पढ़ो_bool(np, "powered-while-suspended"))
		chip->flags |= TPM_CHIP_FLAG_ALWAYS_POWERED;

	sizep = of_get_property(np, "linux,sml-size", शून्य);
	basep = of_get_property(np, "linux,sml-base", शून्य);
	अगर (sizep == शून्य && basep == शून्य)
		वापस -ENODEV;
	अगर (sizep == शून्य || basep == शून्य)
		वापस -EIO;

	/*
	 * For both vtpm/tpm, firmware has log addr and log size in big
	 * endian क्रमmat. But in हाल of vtpm, there is a method called
	 * sml-hanकरोver which is run during kernel init even beक्रमe
	 * device tree is setup. This sml-hanकरोver function takes care
	 * of endianness and ग_लिखोs to sml-base and sml-size in little
	 * endian क्रमmat. For this reason, vtpm करोesn't need conversion
	 * but physical tpm needs the conversion.
	 */
	अगर (of_property_match_string(np, "compatible", "IBM,vtpm") < 0 &&
	    of_property_match_string(np, "compatible", "IBM,vtpm20") < 0) अणु
		size = be32_to_cpup((__क्रमce __be32 *)sizep);
		base = be64_to_cpup((__क्रमce __be64 *)basep);
	पूर्ण अन्यथा अणु
		size = *sizep;
		base = *basep;
	पूर्ण

	अगर (size == 0) अणु
		dev_warn(&chip->dev, "%s: Event log area empty\n", __func__);
		वापस -EIO;
	पूर्ण

	log->bios_event_log = kmemdup(__va(base), size, GFP_KERNEL);
	अगर (!log->bios_event_log)
		वापस -ENOMEM;

	log->bios_event_log_end = log->bios_event_log + size;

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		वापस EFI_TCG2_EVENT_LOG_FORMAT_TCG_2;
	वापस EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2;
पूर्ण
