<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ACPI PCI Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 * Copyright (C) 2002 Hiroshi Aono (h-aono@ap.jp.nec.com)
 * Copyright (C) 2002,2003 Takayoshi Kochi (t-kochi@bq.jp.nec.com)
 * Copyright (C) 2002,2003 NEC Corporation
 * Copyright (C) 2003-2005 Matthew Wilcox (willy@infradead.org)
 * Copyright (C) 2003-2005 Hewlett Packard
 *
 * All rights reserved.
 *
 * Send feedback to <kristen.c.accardi@पूर्णांकel.com>
 *
 */

#घोषणा pr_fmt(fmt) "acpiphp: " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश "acpiphp.h"

/* name size which is used क्रम entries in pcihpfs */
#घोषणा SLOT_NAME_SIZE  21              /* अणु_SUNपूर्ण */

bool acpiphp_disabled;

/* local variables */
अटल काष्ठा acpiphp_attention_info *attention_info;

#घोषणा DRIVER_VERSION	"0.5"
#घोषणा DRIVER_AUTHOR	"Greg Kroah-Hartman <gregkh@us.ibm.com>, Takayoshi Kochi <t-kochi@bq.jp.nec.com>, Matthew Wilcox <willy@infradead.org>"
#घोषणा DRIVER_DESC	"ACPI Hot Plug PCI Controller Driver"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_PARM_DESC(disable, "disable acpiphp driver");
module_param_named(disable, acpiphp_disabled, bool, 0444);

अटल पूर्णांक enable_slot(काष्ठा hotplug_slot *slot);
अटल पूर्णांक disable_slot(काष्ठा hotplug_slot *slot);
अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *slot, u8 value);
अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_attention_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_latch_status(काष्ठा hotplug_slot *slot, u8 *value);
अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *slot, u8 *value);

अटल स्थिर काष्ठा hotplug_slot_ops acpi_hotplug_slot_ops = अणु
	.enable_slot		= enable_slot,
	.disable_slot		= disable_slot,
	.set_attention_status	= set_attention_status,
	.get_घातer_status	= get_घातer_status,
	.get_attention_status	= get_attention_status,
	.get_latch_status	= get_latch_status,
	.get_adapter_status	= get_adapter_status,
पूर्ण;

/**
 * acpiphp_रेजिस्टर_attention - set attention LED callback
 * @info: must be completely filled with LED callbacks
 *
 * Description: This is used to रेजिस्टर a hardware specअगरic ACPI
 * driver that manipulates the attention LED.  All the fields in
 * info must be set.
 */
पूर्णांक acpiphp_रेजिस्टर_attention(काष्ठा acpiphp_attention_info *info)
अणु
	पूर्णांक retval = -EINVAL;

	अगर (info && info->owner && info->set_attn &&
			info->get_attn && !attention_info) अणु
		retval = 0;
		attention_info = info;
	पूर्ण
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(acpiphp_रेजिस्टर_attention);


/**
 * acpiphp_unरेजिस्टर_attention - unset attention LED callback
 * @info: must match the poपूर्णांकer used to रेजिस्टर
 *
 * Description: This is used to un-रेजिस्टर a hardware specअगरic acpi
 * driver that manipulates the attention LED.  The poपूर्णांकer to the
 * info काष्ठा must be the same as the one used to set it.
 */
पूर्णांक acpiphp_unरेजिस्टर_attention(काष्ठा acpiphp_attention_info *info)
अणु
	पूर्णांक retval = -EINVAL;

	अगर (info && attention_info == info) अणु
		attention_info = शून्य;
		retval = 0;
	पूर्ण
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(acpiphp_unरेजिस्टर_attention);


/**
 * enable_slot - घातer on and enable a slot
 * @hotplug_slot: slot to enable
 *
 * Actual tasks are करोne in acpiphp_enable_slot()
 */
अटल पूर्णांक enable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);

	pr_debug("%s - physical_slot = %s\n", __func__, slot_name(slot));

	/* enable the specअगरied slot */
	वापस acpiphp_enable_slot(slot->acpi_slot);
पूर्ण


/**
 * disable_slot - disable and घातer off a slot
 * @hotplug_slot: slot to disable
 *
 * Actual tasks are करोne in acpiphp_disable_slot()
 */
अटल पूर्णांक disable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);

	pr_debug("%s - physical_slot = %s\n", __func__, slot_name(slot));

	/* disable the specअगरied slot */
	वापस acpiphp_disable_slot(slot->acpi_slot);
पूर्ण


/**
 * set_attention_status - set attention LED
 * @hotplug_slot: slot to set attention LED on
 * @status: value to set attention LED to (0 or 1)
 *
 * attention status LED, so we use a callback that
 * was रेजिस्टरed with us.  This allows hardware specअगरic
 * ACPI implementations to blink the light क्रम us.
 */
अटल पूर्णांक set_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 status)
अणु
	पूर्णांक retval = -ENODEV;

	pr_debug("%s - physical_slot = %s\n", __func__,
		hotplug_slot_name(hotplug_slot));

	अगर (attention_info && try_module_get(attention_info->owner)) अणु
		retval = attention_info->set_attn(hotplug_slot, status);
		module_put(attention_info->owner);
	पूर्ण अन्यथा
		attention_info = शून्य;
	वापस retval;
पूर्ण


/**
 * get_घातer_status - get घातer status of a slot
 * @hotplug_slot: slot to get status
 * @value: poपूर्णांकer to store status
 *
 * Some platक्रमms may not implement _STA method properly.
 * In that हाल, the value वापसed may not be reliable.
 */
अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);

	pr_debug("%s - physical_slot = %s\n", __func__, slot_name(slot));

	*value = acpiphp_get_घातer_status(slot->acpi_slot);

	वापस 0;
पूर्ण


/**
 * get_attention_status - get attention LED status
 * @hotplug_slot: slot to get status from
 * @value: वापसs with value of attention LED
 *
 * ACPI करोesn't have known method to determine the state
 * of the attention status LED, so we use a callback that
 * was रेजिस्टरed with us.  This allows hardware specअगरic
 * ACPI implementations to determine its state.
 */
अटल पूर्णांक get_attention_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	पूर्णांक retval = -EINVAL;

	pr_debug("%s - physical_slot = %s\n", __func__,
		hotplug_slot_name(hotplug_slot));

	अगर (attention_info && try_module_get(attention_info->owner)) अणु
		retval = attention_info->get_attn(hotplug_slot, value);
		module_put(attention_info->owner);
	पूर्ण अन्यथा
		attention_info = शून्य;
	वापस retval;
पूर्ण


/**
 * get_latch_status - get latch status of a slot
 * @hotplug_slot: slot to get status
 * @value: poपूर्णांकer to store status
 *
 * ACPI करोesn't provide any क्रमmal means to access latch status.
 * Instead, we fake latch status from _STA.
 */
अटल पूर्णांक get_latch_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);

	pr_debug("%s - physical_slot = %s\n", __func__, slot_name(slot));

	*value = acpiphp_get_latch_status(slot->acpi_slot);

	वापस 0;
पूर्ण


/**
 * get_adapter_status - get adapter status of a slot
 * @hotplug_slot: slot to get status
 * @value: poपूर्णांकer to store status
 *
 * ACPI करोesn't provide any क्रमmal means to access adapter status.
 * Instead, we fake adapter status from _STA.
 */
अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा slot *slot = to_slot(hotplug_slot);

	pr_debug("%s - physical_slot = %s\n", __func__, slot_name(slot));

	*value = acpiphp_get_adapter_status(slot->acpi_slot);

	वापस 0;
पूर्ण

/* callback routine to initialize 'struct slot' क्रम each slot */
पूर्णांक acpiphp_रेजिस्टर_hotplug_slot(काष्ठा acpiphp_slot *acpiphp_slot,
				  अचिन्हित पूर्णांक sun)
अणु
	काष्ठा slot *slot;
	पूर्णांक retval = -ENOMEM;
	अक्षर name[SLOT_NAME_SIZE];

	slot = kzalloc(माप(*slot), GFP_KERNEL);
	अगर (!slot)
		जाओ error;

	slot->hotplug_slot.ops = &acpi_hotplug_slot_ops;

	slot->acpi_slot = acpiphp_slot;

	acpiphp_slot->slot = slot;
	slot->sun = sun;
	snम_लिखो(name, SLOT_NAME_SIZE, "%u", sun);

	retval = pci_hp_रेजिस्टर(&slot->hotplug_slot, acpiphp_slot->bus,
				 acpiphp_slot->device, name);
	अगर (retval == -EBUSY)
		जाओ error_slot;
	अगर (retval) अणु
		pr_err("pci_hp_register failed with error %d\n", retval);
		जाओ error_slot;
	पूर्ण

	pr_info("Slot [%s] registered\n", slot_name(slot));

	वापस 0;
error_slot:
	kमुक्त(slot);
error:
	वापस retval;
पूर्ण


व्योम acpiphp_unरेजिस्टर_hotplug_slot(काष्ठा acpiphp_slot *acpiphp_slot)
अणु
	काष्ठा slot *slot = acpiphp_slot->slot;

	pr_info("Slot [%s] unregistered\n", slot_name(slot));

	pci_hp_deरेजिस्टर(&slot->hotplug_slot);
	kमुक्त(slot);
पूर्ण


व्योम __init acpiphp_init(व्योम)
अणु
	pr_info(DRIVER_DESC " version: " DRIVER_VERSION "%s\n",
		acpiphp_disabled ? ", disabled by user; please report a bug"
				 : "");
पूर्ण
